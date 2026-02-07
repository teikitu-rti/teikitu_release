/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Preload - Mem MGR.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.21 | »GUID« AEEC8393-9780-4ECA-918D-E3E11F7E2744 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/** @note Memory Pools: A pool is created for each power of 2 greater than 8, and for the 3 most significant binary values after them (i.e. 10000, 10100, 11000, 11100) - up to
    MAXPOOL count. If the OS Page_Size is less than the normal MaxAlloc size number of pools and MaxAlloc are correspondingly modified so that MaxAlloc matches Page_Size. The
    reason for this is to reduce internal fragmentation and because no time savings would be incurred. */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

#include "TgS COMMON/TgS Common - Mimalloc.h"




/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Platform Functions                                                                                                                                                    */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @brief Retrieve the number of bytes in the default (standard) memory page of the OS memory manager.
    @return see brief. */
TgEXTN TgRSIZE
tgMM_PM_Page_Size( TgVOID );

/** @brief Function wrapper for the operating system virtual memory allocation. 
    @param [in] ARG0 Integer holding the amount of memory to allocate.
    @return Pointer to the block of memory allocated (may not be committed), or NULL otherwise. */
TgEXTN TgVOID_P
tgMM_PM_Virtual_Reserve(
    TgRSIZE_C ARG0 );

/** @brief Function wrapper for the operating system virtual memory commit. 
    @param [in] ARG0 Pointer to the start of a reserved region, or null for a new allocation.
    @param [in] ARG1 Offset from the pointer base to the start of the region to commit.
    @param [in] ARG2 Size of the region to commit.
    @return Pointer to the block of memory committed, or NULL otherwise. */
TgEXTN TgVOID_P
tgMM_PM_Virtual_Commit(
    TgVOID_PC ARG0, TgRSIZE_C ARG1, TgRSIZE_C ARG2 );

/** @brief Function wrapper for the operating system free. 
    @param [in] ARG0 Pointer to the start of the memory to free. */
TgEXTN TgVOID
tgMM_PM_Virtual_Free( TgVOID_PC ARG0 );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Constants                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

enum { KTgMIN_ALLOC_BIT                     = 4 }; /* This can not be smaller than sizeof(void*) */
enum { KTgMIN_BLOCK_SIZE                    = 1 << KTgMIN_ALLOC_BIT };
enum { KTgMAX_BLOCK_SIZE                    = 1024 }; /* Pools have a range of [16, 1024] */
enum { KTgMAX_POOLS                         = 25 }; /* Number of pools to fit max block size of 1024 */

TgCOMPILER_ASSERT(16 == KTgMIN_BLOCK_SIZE,);

typedef enum TgATTRIBUTE_ENUM
{
    ETgMM_PAGE_STATE_OPENED = 0x10,
    ETgMM_PAGE_STATE_REOPENED = 0x11,
    ETgMM_PAGE_STATE_CLOSED = 0x20,
    ETgMM_PAGE_STATE_REOPENED_QUEUED = 0x30,
} ETgMM_PAGE_STATE;
TgTYPE_MODIFIER_DEFAULT(ETgMM_PAGE_STATE);

typedef enum TgATTRIBUTE_ENUM_FLAG
{
    ETgMM_ALLOCATION_FLAG_SMALL_ALLOCATOR = 0x1,
} ETgMM_ALLOCATION_FLAG;
TgTYPE_MODIFIER_DEFAULT(ETgMM_ALLOCATION_FLAG);




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Types                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TgTYPE_STRUCT(TgMEM_OS_HEADER,) /* 32 Byte Header Block */
{
    STg2_UT_ST__LT_Node                         m_sList_Header__Page;                       /* 16 Bytes */
    TgMEM_INFO_HEADER                           m_sInfo_Header;                             /*  6 Bytes */
    TgUINT_E16                                  m_uiPad[5];                                 /* 10 Bytes */
    TgUINT_E08                                  m_auiData[];
};
TgCOMPILER_ASSERT( sizeof(TgMEM_OS_HEADER) == 32, 0 );

TgTYPE_UNION(TgMEM_PAGE_HEADER,) /* 32 Byte Header Block */
{
    STg2_UT_ST__ST_Node_Unaligned               m_sStack_Header;                                    /* Used to track open pages */
    STg2_UT_ST__LT_Node                         m_sList_Header;                                     /* Used to track closed pages */
    TgMEM_OS_HEADER                             m_sOS_Header;
    struct
    {
        TgUINT_PTR                                  m_uiHeader[2];              /* 16 bytes */
        TgMEM_INFO_HEADER                           m_sInfo_Header;             /*  6 Bytes */      /* Memory location must match that of the OS Header*/
        TgUINT_E16                                  m_uiBlock_End;              /*  2 Bytes */      /* Modified only on initialization */
        TgUINT_E16                                  m_uiBlock_Last;             /*  2 Bytes */      /* Modified only by Malloc */
        TgUINT_E16_A                                m_uiBlock_Free;             /*  2 Bytes */      /* Modified by both Malloc and Free */
        TgUINT_E16                                  m_uiBlock_Size;             /*  4 Bytes */      /* Modified only on initialization */
        TgUINT_E16                                  m_uiState;
        TgUINT_E08                                  m_auiData[];
    };
};
TgCOMPILER_ASSERT( sizeof(STg2_UT_ST__LT_Node) == sizeof(TgUINT_PTR)*2, 0 );
TgCOMPILER_ASSERT( sizeof(TgMEM_PAGE_HEADER) == 32, 0 );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* Base OS Allocator */

static TgRESULT
tgMM_OS__Init_MGR( TgVOID );

static TgRESULT
tgMM_OS__Free_MGR( TgVOID );

static TgRESULT
tgMM_OS__Size(
    TgUINT_E32_P TgANALYSIS_NO_NULL, TgUINT_E32_P TgANALYSIS_NO_NULL, TgVOID_CPC TgANALYSIS_NO_NULL );

static TgRESULT
tgMM_OS__Malloc(
    TgMEM_INFO_HEADER_P TgANALYSIS_NO_NULL, TgVOID_PP TgANALYSIS_NO_NULL, TgRSIZE_C, TgRSIZE_C );

static TgRESULT
tgMM_OS__Reserve(
    TgMEM_INFO_HEADER_P TgANALYSIS_NO_NULL, TgVOID_PP TgANALYSIS_NO_NULL, TgRSIZE_C );

static TgRESULT
tgMM_OS__Commit(
    TgMEM_INFO_HEADER_P TgANALYSIS_NO_NULL, TgVOID_PP TgANALYSIS_NO_NULL, TgRSIZE_C, TgRSIZE_C );

static TgRESULT
tgMM_OS__Free(
    TgMEM_INFO_HEADER_P TgANALYSIS_NO_NULL, TgVOID_PC TgANALYSIS_NO_NULL );


/* Memory Pool */

static TgRESULT
tgMM_Pool__Init_MGR( TgVOID );

static TgRESULT
tgMM_Pool__Free_MGR( TgVOID );

static TgRESULT
tgMM_Pool__Size(
    TgUINT_E32_P TgANALYSIS_NO_NULL, TgUINT_E32_P TgANALYSIS_NO_NULL, TgVOID_CPC TgANALYSIS_NO_NULL );

static TgRESULT
tgMM_Pool__Malloc(
    TgMEM_INFO_HEADER_P TgANALYSIS_NO_NULL, TgVOID_PP TgANALYSIS_NO_NULL, TgRSIZE_C, TgRSIZE_C );

static TgRESULT
tgMM_Pool__Free(
    TgMEM_INFO_HEADER_P TgANALYSIS_NO_NULL, TgVOID_PC TgANALYSIS_NO_NULL );

static TgRESULT
tgMM_Pool__Realloc(
    TgMEM_INFO_HEADER_P TgANALYSIS_NO_NULL, TgVOID_PP TgANALYSIS_NO_NULL, TgMEM_INFO_HEADER_P TgANALYSIS_NO_NULL, TgVOID_PC TgANALYSIS_NO_NULL, TgRSIZE_C, TgRSIZE_C );

#if TgS_STAT__COMMON

static TgVOID
tgMM_Pool__Stats(
    TgRSIZE (*)( STg2_Output_PC TgANALYSIS_NO_NULL, TgCHAR_U8_CPC TgANALYSIS_NO_NULL, ... ), STg2_Output_PC TgANALYSIS_NO_NULL );

static TgVOID
tgMM_Pool__Stats_Pool(
    TgRSIZE_C, TgRSIZE_P, TgRSIZE_P, TgRSIZE_P );

/*# TgS_STAT__COMMON */
#endif


/* Memory Manager */

static TgBOOL
tgMM_Pool__Check_Page_Is_Empty(
    TgMEM_PAGE_HEADER_P );


#if TgS_STAT__COMMON

TgINLINE TgVOID
tgMM_Stat_Internal__Entry(
    TgMEM_INFO_HEADER_P TgANALYSIS_NO_NULL );

/*# TgS_STAT__COMMON */
#endif


static STg2_UT_LF_ISO__SN                   s_sOS_Spin_Lock;
static STg2_UT_ST__LT                       s_sOS_List;

static TgRSIZE                              s_nuiMaxPools, s_uiMaxBlock;
static STg2_UT_LF_ISO__SN                   s_asPage_Spin_Lock[KTgMAX_POOLS], s_sPage_Cache_Spin_Lock;
static STg2_UT_LF_ISO__ST                   s_asPage_Open[KTgMAX_POOLS];
static STg2_UT_ST__LT                       s_asPage_Closed[KTgMAX_POOLS], s_sPage_Cache;
static STg2_UT_LF_ISO__RW                   s_rwPage_Stat_Lock;
TgTLS static TgMEM_PAGE_HEADER_P            tls_apsPage_Open[KTgMAX_POOLS];

/** @note To make life simple - the allocation granularity and the page granularity are assumed to be the same.  Thus, on the X360 all allocations are made using the large memory
    page size option (64K pages). */

static ETgMODULE_STATE                      s_enMem_MGR_State = ETgMODULE_STATE__FREED;

static STg2_MM_MGR                          s_asAllocator[ETgMM_ALLOCATOR_COUNT];
static TgRSIZE                              s_uiPageSize;

#if TgS_STAT__COMMON
static TgCHAR_U8_C                          s_ambzStat_Name[ETgMM_ALLOCATOR_COUNT][10] = { u8"OS", u8"Pool", u8"Mimalloc", u8"User 0", u8"User 1", u8"User 2", u8"User 3" };
static TgRSIZE_A                            s_anuiStat_Allocations[ETgMM_ALLOCATOR_COUNT];
static TgRSIZE_A                            s_anuiStat_Max_Allocations[ETgMM_ALLOCATOR_COUNT];
static TgRSIZE_A                            s_auiStat_Allocated[ETgMM_ALLOCATOR_COUNT];
static TgRSIZE_A                            s_auiStat_Max_Allocated[ETgMM_ALLOCATOR_COUNT];
static TgRSIZE_A                            s_auiStat_Reserved[ETgMM_ALLOCATOR_COUNT];
static TgRSIZE_A                            s_auiStat_Max_Reserved[ETgMM_ALLOCATOR_COUNT];
/*# TgS_STAT__COMMON */
#endif




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgMM_Set_CN_PrintF ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgMM_Set_CN_PrintF( TgVOID (*pfnCN_PrintF)( TgUINT_E32_C, TgCHAR_U8_CP, ... ) )
{
#if defined(TgBUILD_PRELOAD__HAS_CONSOLE)
    g_pfnCN_PrintF = pfnCN_PrintF;
#endif
#if defined(TgBUILD_FEATURE__MIMALLOC_ALLOCATOR)
    tgMM_MI_Set_CN_PrintF( pfnCN_PrintF );
#endif
}


/* ---- tgMM_Query_Init ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgMM_Query_Init( TgVOID )
{
    return (ETgMODULE_STATE__INITIALIZED <= s_enMem_MGR_State && s_enMem_MGR_State <= ETgMODULE_STATE__STOPPED);
}


/* ---- tgMM_Query_Fixed_Memory_Preload -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRSIZE tgMM_Query_Fixed_Memory_Preload( TgVOID )
{
    return (0
             + sizeof( s_sOS_Spin_Lock )
             + sizeof( s_sOS_List )

             + sizeof( s_nuiMaxPools )
             + sizeof( s_uiMaxBlock )
             + sizeof( s_asPage_Spin_Lock )
             + sizeof( s_sPage_Cache_Spin_Lock )
             + sizeof( s_asPage_Open )
             + sizeof( s_asPage_Closed )
             + sizeof( s_sPage_Cache )
             + sizeof( s_rwPage_Stat_Lock )
             + sizeof( tls_apsPage_Open )

             + sizeof( s_enMem_MGR_State )
             + sizeof( s_asAllocator )
             + sizeof( s_uiPageSize )

        #if TgS_STAT__COMMON
             + sizeof( s_ambzStat_Name )
             + sizeof( s_anuiStat_Allocations )
             + sizeof( s_anuiStat_Max_Allocations )
             + sizeof( s_auiStat_Allocated )
             + sizeof( s_auiStat_Max_Allocated )
             + sizeof( s_auiStat_Reserved )
             + sizeof( s_auiStat_Max_Reserved )
        /*# TgS_STAT__COMMON */
        #endif
    );
}


/* ---- tgMM_Query_Stats --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if TgS_STAT__COMMON
TgRESULT tgMM_Query_Stats( STg2_MM_Preload_Stats_P pMM_Stats )
{
    TgRSIZE                             uiIndex;

    TgPARAM_CHECK(pMM_Stats);
    if (!pMM_Stats)
    {
        return KTgE_FAIL;
    }

    for (uiIndex = 0; uiIndex < ETgMM_ALLOCATOR_COUNT; ++uiIndex)
    {
        pMM_Stats->m_ambzStat_Name[uiIndex] = s_ambzStat_Name[uiIndex];
        pMM_Stats->m_anuiStat_Allocations[uiIndex] = TgSTD_ATOMIC(load)(s_anuiStat_Allocations + uiIndex);
        pMM_Stats->m_anuiStat_Max_Allocations[uiIndex] = TgSTD_ATOMIC(load)(s_anuiStat_Max_Allocations + uiIndex);
        pMM_Stats->m_auiStat_Allocated[uiIndex] = TgSTD_ATOMIC(load)(s_auiStat_Allocated + uiIndex);
        pMM_Stats->m_auiStat_Max_Allocated[uiIndex] = TgSTD_ATOMIC(load)(s_auiStat_Max_Allocated + uiIndex);
        pMM_Stats->m_auiStat_Reserved[uiIndex] = TgSTD_ATOMIC(load)(s_auiStat_Reserved + uiIndex);
        pMM_Stats->m_auiStat_Max_Reserved[uiIndex] = TgSTD_ATOMIC(load)(s_auiStat_Max_Reserved + uiIndex);
    };

    return KTgS_OK;
}
/*# TgS_STAT__COMMON */
#endif


/* ---- tgMM_Stats_Allocator ------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if TgS_STAT__COMMON
TgVOID tgMM_Stats_Allocator( TgRSIZE (*pfnIO_PrintF)( STg2_Output_PC TgANALYSIS_NO_NULL, TgCHAR_U8_CPC, ... ), STg2_Output_PC psOUT )
{
    TgRSIZE                             uiIndex;

    for (uiIndex = 0; uiIndex < ETgMM_ALLOCATOR_COUNT; ++uiIndex)
    {
        if (s_asAllocator[uiIndex].m_pfnStats)
        {
            s_asAllocator[uiIndex].m_pfnStats( pfnIO_PrintF, psOUT );
        };
    };
}
/*# TgS_STAT__COMMON */
#endif


/* ---- tgMM_OS__Preload_Malloc_Redirected --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgATTRIBUTE_NO_DISCARD TgBOOL
tgMM_OS__Preload_Malloc_Redirected( TgVOID ) TgATTRIBUTE_NO_EXCEPT
{
    return g_bOS_MM_Redirected;
}


/* ---- tgMM_Page_Size ----------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRSIZE tgMM_Page_Size( TgVOID )
{
    return (tgMM_PM_Page_Size());
}


/* ---- tgMM_Register_Allocator -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgMM_Register_Allocator( ETgMM_ALLOCATOR_C enAllocator, STg2_MM_MGR_P psMem_MGR )
{
    TgPARAM_CHECK_INDEX( enAllocator, s_asAllocator );

    TgCRITICAL( psMem_MGR && psMem_MGR->m_pfnFree && psMem_MGR->m_pfnMalloc && psMem_MGR->m_pfnSize );

    tgMM_Copy( s_asAllocator + enAllocator, sizeof( s_asAllocator[0] ), psMem_MGR, sizeof( STg2_MM_MGR ) );
}


/* ---- tgMM_Is_Allocator_Registered --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgMM_Is_Allocator_Registered( ETgMM_ALLOCATOR_C enAllocator )
{
    TgPARAM_CHECK_INDEX( enAllocator, s_asAllocator );

    return (s_asAllocator[enAllocator].m_pfnFree && s_asAllocator[enAllocator].m_pfnMalloc && s_asAllocator[enAllocator].m_pfnSize);
}


/* ---- tgMM_Free_Thread_Local --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgMM_Free_Thread_Local( TgVOID ) TgATTRIBUTE_NO_EXCEPT
{
    TgRSIZE                             uiIndex;

    for (uiIndex = 0; uiIndex < ETgMM_ALLOCATOR_COUNT; ++uiIndex)
    {
        if (s_asAllocator[uiIndex].m_pfnFree_Thread_Local)
        {
            s_asAllocator[uiIndex].m_pfnFree_Thread_Local();
        };
    };
}


/* ---- tgMM_Size ---------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRSIZE tgMM_Size( ETgMM_ALLOCATOR_C enAllocator, TgVOID_CPC pMem )
{
    TgUINT_E32                          nbyReserved, nbyAllocated;

    TgERROR(ETgMODULE_STATE__BOOTED == s_enMem_MGR_State);
    TgPARAM_CHECK_INDEX( enAllocator, s_asAllocator );

    if (nullptr == pMem)
    {
        return (0u);
    };

    if (!s_asAllocator[enAllocator].m_pfnSize || TgFAILED(s_asAllocator[enAllocator].m_pfnSize( &nbyReserved, &nbyAllocated, pMem )))
    {
        return (KTgMAX_RSIZE);
    };

    return (tgCM_MAX_U32( nbyReserved, nbyAllocated ));
}


/* ---- tgMM_Malloc -------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID_P tgMM_Malloc( ETgMM_ALLOCATOR_C enAllocator, TgRSIZE_C uiSize, TgRSIZE_C uiAlignment )
{
    TgMEM_INFO_HEADER                   sInfo;
    TgVOID_P                            pMem;

    TgERROR(ETgMODULE_STATE__BOOTED == s_enMem_MGR_State);
    TgPARAM_CHECK_INDEX( enAllocator, s_asAllocator );

    if (!s_asAllocator[enAllocator].m_pfnMalloc)
    {
        return (nullptr);
    };

    if (TgFAILED(s_asAllocator[enAllocator].m_pfnMalloc( &sInfo, &pMem, uiSize, uiAlignment )))
    {
        return (nullptr);
    };
    TgERROR(sInfo.m_uiSize >= uiSize);

#if TgS_STAT__COMMON
    tgMM_Stat_Internal__Entry( &sInfo );
#endif

    return (pMem);
}


/* ---- tgMM_Required_Virtual_Size -----------------------------------------------------------------------------------------------------------------------------------------------  */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
 TgRSIZE tgMM_Required_Virtual_Size( TgRSIZE_C uiSize )
{
    return (((sizeof( TgMEM_OS_HEADER ) + uiSize + tgMM_Page_Size() - 1) / tgMM_Page_Size()) * tgMM_Page_Size());
}


/* ---- tgMM_Reserve ------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID_P tgMM_Reserve( ETgMM_ALLOCATOR_C enAllocator, TgRSIZE_C uiSize )
{
    TgMEM_INFO_HEADER                   sInfo;
    TgVOID_P                            pMem;

    TgERROR(ETgMODULE_STATE__BOOTED == s_enMem_MGR_State);
    TgPARAM_CHECK_INDEX( enAllocator, s_asAllocator );

    if (!s_asAllocator[enAllocator].m_pfnReserve || (0 == uiSize))
    {
        return (nullptr);
    };

    if (TgFAILED(s_asAllocator[enAllocator].m_pfnReserve( &sInfo, &pMem, uiSize )))
    {
        return (nullptr);
    };
    TgERROR(sInfo.m_uiSize >= uiSize);

#if TgS_STAT__COMMON
    tgMM_Stat_Internal__Entry( &sInfo );
#endif

    return (pMem);
}


/* ---- tgMM_Commit -------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID_P tgMM_Commit( ETgMM_ALLOCATOR_C enAllocator, TgVOID_P pMem, TgRSIZE_C uiOffset, TgRSIZE_C uiSize )
{
    TgMEM_INFO_HEADER                   sInfo;

    TgERROR(ETgMODULE_STATE__BOOTED == s_enMem_MGR_State);
    TgPARAM_CHECK_INDEX( enAllocator, s_asAllocator );

    /* Confirm that this allocator has a Commit function (i.e. is capable of managing virtual memory). */
    if (!s_asAllocator[enAllocator].m_pfnCommit || (0 == uiSize))
    {
        return (nullptr);
    };

    /* Execute the Commit function. */
    if (TgFAILED(s_asAllocator[enAllocator].m_pfnCommit( &sInfo, &pMem, uiOffset, uiSize )))
    {
        return (nullptr);
    };

    /* Make sure that we do not return a pointer that addresses the allocation header. */

#if TgS_STAT__COMMON
    if (0 != sInfo.m_uiSize)
    {
        tgMM_Stat_Internal__Entry( &sInfo );
    };
#endif

    return (pMem);
}


/* ---- tgMM_Free ---------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgMM_Free( ETgMM_ALLOCATOR_C enAllocator, TgVOID_PC pMem )
{
    TgMEM_INFO_HEADER                   sInfo;
    TgRESULT                            iResult;

    TgERROR(ETgMODULE_STATE__BOOTED == s_enMem_MGR_State);
    TgPARAM_CHECK_INDEX( enAllocator, s_asAllocator );

    if (!s_asAllocator[enAllocator].m_pfnFree || (nullptr == pMem))
    {
        return;
    };

    iResult = s_asAllocator[enAllocator].m_pfnFree( &sInfo, pMem ) ;

#if TgS_STAT__COMMON
    TgSTD_ATOMIC(fetch_sub)( s_anuiStat_Allocations + sInfo.m_enAllocator, 1 );
    if (TgSUCCEEDED(iResult))
    {
        TgRSIZE                             uiValue;

        uiValue = sInfo.m_bReserved ? sInfo.m_uiSize : 0;
        TgSTD_ATOMIC(fetch_sub)( s_auiStat_Reserved + sInfo.m_enAllocator, uiValue );
        uiValue = sInfo.m_bReserved ? 0 : sInfo.m_uiSize;
        TgSTD_ATOMIC(fetch_sub)( s_auiStat_Allocated + sInfo.m_enAllocator, uiValue );
    };
#else
    (void)iResult;
#endif
}


/* ---- tgMM_Realloc ------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID_P tgMM_Realloc( ETgMM_ALLOCATOR_C enAllocator, TgVOID_PC pMem, TgRSIZE_C uiSize, TgRSIZE_C uiAlignment )
{
    TgMEM_INFO_HEADER                   sOld_Info, sNew_Info;
    TgVOID_P                            pReturn;

    TgERROR(ETgMODULE_STATE__BOOTED == s_enMem_MGR_State);
    TgPARAM_CHECK_INDEX( enAllocator, s_asAllocator );

    if (nullptr == pMem)
    {
        return (tgMM_Malloc( enAllocator, uiSize, uiAlignment ));
    };

    if (!s_asAllocator[enAllocator].m_pfnRealloc || (0 == uiSize))
    {
        return (nullptr);
    };

    if (TgFAILED(s_asAllocator[enAllocator].m_pfnRealloc( &sNew_Info, &pReturn, &sOld_Info, pMem, uiSize, uiAlignment )))
    {
        return (nullptr);
    };

#if TgS_STAT__COMMON
    if (pReturn != pMem)
    {
        TgRSIZE                             uiValue;

        tgMM_Stat_Internal__Entry( &sNew_Info );
        TgSTD_ATOMIC(fetch_sub)( s_anuiStat_Allocations + sOld_Info.m_enAllocator, 1 );

        uiValue = sOld_Info.m_bReserved ? sOld_Info.m_uiSize : 0;
        TgSTD_ATOMIC(fetch_sub)( s_auiStat_Reserved + sOld_Info.m_enAllocator, uiValue );
        uiValue = sOld_Info.m_bReserved ? 0 : sOld_Info.m_uiSize;
        TgSTD_ATOMIC(fetch_sub)( s_auiStat_Allocated + sOld_Info.m_enAllocator, uiValue );
    }
#endif

    return (pReturn);
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgMM_Init_MGR ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if defined(TgBUILD_FEATURE__MALLOC_OVERRIDE)
TgRESULT tgMM_Init_MGR( TgVOID )
#else
TgRESULT tgMM_Init_MGR_Preload( TgVOID )
#endif
{
    STg2_MM_MGR                         sMGR;
    TgRSIZE                             uiIndex;

    TgERROR(ETgMODULE_STATE__FREED == s_enMem_MGR_State);
    s_enMem_MGR_State = ETgMODULE_STATE__INITIALIZING;

    tgMM_Set_U08_0x00( s_asAllocator, sizeof( s_asAllocator ) );
    s_uiPageSize = tgMM_Page_Size();


    /* Register the default allocators */

    tgMM_Set_U08_0x00( &sMGR, sizeof( STg2_MM_MGR ) );
    sMGR.m_pfnInit_MGR = tgMM_OS__Init_MGR;
    sMGR.m_pfnFree_MGR = tgMM_OS__Free_MGR;
    sMGR.m_pfnSize = tgMM_OS__Size;
    sMGR.m_pfnMalloc = tgMM_OS__Malloc;
    sMGR.m_pfnReserve = tgMM_OS__Reserve;
    sMGR.m_pfnCommit = tgMM_OS__Commit;
    sMGR.m_pfnFree = tgMM_OS__Free;
    //sMGR.m_pfnFree_Thread_Local
    tgMM_Register_Allocator( ETgMM_ALLOCATOR_OS, &sMGR );

#if defined(TgBUILD_FEATURE__MIMALLOC_ALLOCATOR)
    tgMM_Set_U08_0x00( &sMGR, sizeof( STg2_MM_MGR ) );
    sMGR.m_pfnInit_MGR = tgMM_MI__Init_MGR;
    sMGR.m_pfnFree_MGR = tgMM_MI__Free_MGR;
    sMGR.m_pfnSize = tgMM_MI__Size;
    sMGR.m_pfnMalloc = tgMM_MI__Malloc;
    sMGR.m_pfnFree = tgMM_MI__Free;
    sMGR.m_pfnRealloc = tgMM_MI__Realloc;
    sMGR.m_pfnFree_Thread_Local = tgMM_MI__Internal__Thread_Done;
#if TgS_STAT__COMMON
    sMGR.m_pfnStats = tgMM_MI__Stats;
#endif
    tgMM_Register_Allocator( ETgMM_ALLOCATOR_MIMALLOC, &sMGR );
#endif

    tgMM_Set_U08_0x00( &sMGR, sizeof( STg2_MM_MGR ) );
    sMGR.m_pfnInit_MGR = tgMM_Pool__Init_MGR;
    sMGR.m_pfnFree_MGR = tgMM_Pool__Free_MGR;
    sMGR.m_pfnSize = tgMM_Pool__Size;
    sMGR.m_pfnMalloc = tgMM_Pool__Malloc;
    sMGR.m_pfnFree = tgMM_Pool__Free;
    sMGR.m_pfnRealloc = tgMM_Pool__Realloc;
    //sMGR.m_pfnFree_Thread_Local
#if TgS_STAT__COMMON
    sMGR.m_pfnStats = tgMM_Pool__Stats;
#endif
    tgMM_Register_Allocator( ETgMM_ALLOCATOR_POOL, &sMGR );


    /* Sanity Checks */

    TgCRITICAL(tgCM_IS_PW2_UMAX( s_uiPageSize ) && tgMM_Page_Size() == s_uiPageSize);


    /* Initialize the allocators */

    for (uiIndex = 0; uiIndex < ETgMM_ALLOCATOR_COUNT; ++uiIndex)
    {
        if (nullptr != s_asAllocator[uiIndex].m_pfnInit_MGR)
        {
            s_asAllocator[uiIndex].m_pfnInit_MGR();
        };
    };

#if TgS_STAT__COMMON
    for (uiIndex = 0; uiIndex < ETgMM_ALLOCATOR_COUNT; ++uiIndex)
    {
        TgSTD_ATOMIC(store)( s_anuiStat_Allocations + uiIndex, 0 );
        TgSTD_ATOMIC(store)( s_anuiStat_Max_Allocations + uiIndex, 0 );
        TgSTD_ATOMIC(store)( s_auiStat_Allocated + uiIndex, 0 );
        TgSTD_ATOMIC(store)( s_auiStat_Max_Allocated + uiIndex, 0 );
        TgSTD_ATOMIC(store)( s_auiStat_Reserved + uiIndex, 0 );
        TgSTD_ATOMIC(store)( s_auiStat_Max_Reserved + uiIndex, 0 );
    };
/*# TgS_STAT__COMMON */
#endif

    s_enMem_MGR_State = ETgMODULE_STATE__BOOTED;

    return (KTgS_OK);
}


/* ---- tgMM_Free_MGR ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if defined(TgBUILD_FEATURE__MALLOC_OVERRIDE)
TgRESULT tgMM_Free_MGR( TgVOID )
#else
TgRESULT tgMM_Free_MGR_Preload( TgVOID )
#endif
{
    TgRSIZE                             uiIndex;

    if (ETgMODULE_STATE__FREED == s_enMem_MGR_State)
    {
        return (KTgS_OK);
    };

    TgERROR(ETgMODULE_STATE__BOOTED == s_enMem_MGR_State);

    s_enMem_MGR_State = ETgMODULE_STATE__FREEING;

    for (uiIndex = 0; uiIndex < ETgMM_ALLOCATOR_COUNT; ++uiIndex)
    {
        if (nullptr != s_asAllocator[uiIndex].m_pfnFree_MGR)
        {
            s_asAllocator[uiIndex].m_pfnFree_MGR();
        };
    };

    for (uiIndex = 0; uiIndex < ETgMM_ALLOCATOR_COUNT; ++uiIndex)
    {
    #if TgS_STAT__COMMON
        TgCRITICAL( 0 == TgSTD_ATOMIC(load)( s_anuiStat_Allocations + uiIndex ) );
        TgCRITICAL( 0 == TgSTD_ATOMIC(load)( s_auiStat_Allocated + uiIndex ) );
        TgCRITICAL( 0 == TgSTD_ATOMIC(load)( s_auiStat_Reserved + uiIndex ) );
    /*# TgS_STAT__COMMON */
    #endif
    };

    s_enMem_MGR_State = ETgMODULE_STATE__FREED;

    return (KTgS_OK);
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgMM_OS__Init_MGR -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT tgMM_OS__Init_MGR( TgVOID )
{
    TgVERIFY(KTgS_OK == tgCM_UT_LF__SN__Init( &s_sOS_Spin_Lock.m_sLock ));
    TgVERIFY(KTgS_OK == tgCM_UT_ST__LT__Init( &s_sOS_List ));

    return (KTgS_OK);
}


/* ---- tgMM_OS__Free_MGR -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT tgMM_OS__Free_MGR( TgVOID )
{
    tgCM_UT_LF__SN__Free_Unsafe( &s_sOS_Spin_Lock.m_sLock );
    tgCM_UT_ST__LT__Free( &s_sOS_List );

    return (KTgS_OK);
}


/* ---- tgMM_OS__Size ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT tgMM_OS__Size( TgUINT_E32_P pnbyReserve, TgUINT_E32_P pnbyAllocated, TgVOID_CPC pMem )
{
    union
    {
        TgVOID_CP                           pVoid;
        TgUINT_PTR                          uiPTR;
        TgMEM_OS_HEADER_CP                  psMem_OS;
    }                                   uMem;

    uMem.uiPTR = tgCM_FLR_ALGN_PW2_UMAX( (TgUINT_PTR)pMem, s_uiPageSize );
    TgCRITICAL( 0 == (uMem.uiPTR % s_uiPageSize) );
    TgCRITICAL( (TgUINT_PTR)pMem == uMem.uiPTR +sizeof(TgMEM_OS_HEADER) );

    if ((nullptr != pnbyReserve) && (nullptr != uMem.pVoid) && uMem.psMem_OS->m_sInfo_Header.m_bReserved)
    {
        *pnbyReserve = uMem.psMem_OS->m_sInfo_Header.m_uiSize;
    }
    else if (nullptr != pnbyReserve)
    {
        *pnbyReserve = 0;
    };

    if ((nullptr != pnbyAllocated) && (nullptr != uMem.pVoid) && !uMem.psMem_OS->m_sInfo_Header.m_bReserved)
    {
        *pnbyAllocated = uMem.psMem_OS->m_sInfo_Header.m_uiSize;
    }
    else if (nullptr != pnbyAllocated)
    {
        *pnbyAllocated = 0;
    };

    return (KTgS_OK);
}


/* ---- tgMM_OS__Malloc ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT tgMM_OS__Malloc( TgMEM_INFO_HEADER_P psInfo, TgVOID_PP ppReturn, TgRSIZE_C uiSize, TgRSIZE_C uiAlignment )
{
    TgMEM_OS_HEADER_P                   psMem_OS;

    (void)uiAlignment;

    /* Create an OS Allocation for this request */
    psMem_OS = (TgMEM_OS_HEADER_P)tgMM_PM_Virtual_Commit( nullptr, 0, sizeof(TgMEM_OS_HEADER) + uiSize );
    if (nullptr == psMem_OS)
    {
        TgCRITICAL_MSGF( 0, STD_MSG_PREFIX u8"Unable to commit (%d).\n", STD_MSG_POST, uiSize );
        return (KTgE_FAIL);
    };

#if TgCOMPILE__MEM_MALLOC_CLEAR
    tgMM_Set_U08( psMem_OS, sizeof(TgMEM_OS_HEADER) + uiSize, 0xCC );
#endif

    psMem_OS->m_sList_Header__Page.m_pPrev_Node = nullptr;
    psMem_OS->m_sList_Header__Page.m_pNext_Node = nullptr;
    psMem_OS->m_sInfo_Header.m_uiSize = (TgUINT_E32)uiSize;
    psMem_OS->m_sInfo_Header.m_uiFlags = 0;
    TgVERIFY(ETgMM_ALLOCATOR_OS == (ETgMM_ALLOCATOR)psMem_OS->m_sInfo_Header.m_enAllocator);

    *psInfo = psMem_OS->m_sInfo_Header;
    *ppReturn = psMem_OS->m_auiData;

    tgCM_UT_LF__SN__Lock_Spin( &s_sOS_Spin_Lock.m_sLock );
    tgCM_UT_ST__LT__Push_Front( &s_sOS_List, &psMem_OS->m_sList_Header__Page );
    tgCM_UT_LF__SN__Signal( &s_sOS_Spin_Lock.m_sLock );

    return (KTgS_OK);
}


/* ---- tgMM_OS__Reserve --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT tgMM_OS__Reserve( TgMEM_INFO_HEADER_P psInfo, TgVOID_PP ppReturn, TgRSIZE_C uiSize )
{
    TgMEM_OS_HEADER_P                   psMem_OS, psMem_Reserve;

    /* Create an OS Allocation for this request */
    psMem_Reserve = (TgMEM_OS_HEADER_P)tgMM_PM_Virtual_Reserve( sizeof( TgMEM_OS_HEADER ) + uiSize );
    if (nullptr == psMem_Reserve)
    {
        TgCRITICAL_MSGF( 0, STD_MSG_PREFIX u8"Unable to reserve (%d).\n", STD_MSG_POST, uiSize );
        return (KTgE_FAIL);
    };

    psMem_OS = (TgMEM_OS_HEADER_P)tgMM_PM_Virtual_Commit( psMem_Reserve, 0, sizeof( TgMEM_OS_HEADER ) );
    if (nullptr == psMem_OS)
    {
        tgMM_PM_Virtual_Free( psMem_Reserve );
        TgCRITICAL_MSGF( 0, STD_MSG_PREFIX u8"Unable to commit (%d).\n", STD_MSG_POST, uiSize );
        return (KTgE_FAIL);
    };

    psMem_OS->m_sList_Header__Page.m_pPrev_Node = nullptr;
    psMem_OS->m_sList_Header__Page.m_pNext_Node = nullptr;
    psMem_OS->m_sInfo_Header.m_uiSize = (TgUINT_E32)uiSize;
    psMem_OS->m_sInfo_Header.m_uiFlags = 0;
    psMem_OS->m_sInfo_Header.m_bReserved = true;
    TgVERIFY(ETgMM_ALLOCATOR_OS == (ETgMM_ALLOCATOR)psMem_OS->m_sInfo_Header.m_enAllocator);

    *psInfo = psMem_OS->m_sInfo_Header;
    *ppReturn = psMem_OS->m_auiData;

    tgCM_UT_LF__SN__Lock_Spin( &s_sOS_Spin_Lock.m_sLock );
    tgCM_UT_ST__LT__Push_Front( &s_sOS_List, &psMem_OS->m_sList_Header__Page );
    tgCM_UT_LF__SN__Signal( &s_sOS_Spin_Lock.m_sLock );

    return (KTgS_OK);
}


/* ---- tgMM_OS__Commit ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT tgMM_OS__Commit( TgMEM_INFO_HEADER_P psInfo, TgVOID_PP pMem, TgRSIZE_C uiOffset, TgRSIZE_C uiSize )
{
    psInfo->m_uiSize = 0;

    if ((nullptr == *pMem) && TgFAILED(tgMM_OS__Reserve( psInfo, pMem, uiSize )))
    {
        return (KTgE_FAIL);
    };

    /* Cannot clear the memory of a commit since it may overlap existing committed memory. The memory pointer is not reassigned once the initial reservation is done. This is 
       because that the underlying implementations may be returned transformed pointers that are problematic. Specific example is windows: VirtualAlloc on a commit will return
       the base of the page where the commit range starts. Given that we do store a small header on a allocation that is an issue. Since we can not "easily" determine if the 
       pointer we are given is the base of a virtual reservation or somewhere in the range of one, it is thus, not trivial to decide when to pass back the page aligned pointer.
       Taking the easier route, the spec is that the commit will encompass all pages required to back the range requested. Thus, easiest to leave the pointer as is or null 
       in the case of a failure. */
    if (nullptr == tgMM_PM_Virtual_Commit( *pMem, uiOffset, uiSize ))
    {
        return (KTgE_FAIL);
    };

    return (KTgS_OK);
}


/* ---- tgMM_OS__Free ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT tgMM_OS__Free( TgMEM_INFO_HEADER_P psInfo, TgVOID_PC pMem )
{
    union
    {
        TgVOID_P                            pVoid;
        TgUINT_PTR                          uiPTR;
        TgMEM_OS_HEADER_P                   psMem_OS;
    }                                   uMem;

    uMem.uiPTR = tgCM_FLR_ALGN_PW2_UMAX( (TgUINT_PTR)pMem, s_uiPageSize );
    TgCRITICAL( 0 == (uMem.uiPTR % s_uiPageSize) );
    TgCRITICAL( (TgUINT_PTR)pMem == uMem.uiPTR +sizeof(TgMEM_OS_HEADER) );

    tgCM_UT_LF__SN__Lock_Spin( &s_sOS_Spin_Lock.m_sLock );
    tgCM_UT_ST__LT__Remove( &uMem.psMem_OS->m_sList_Header__Page );
    tgCM_UT_LF__SN__Signal( &s_sOS_Spin_Lock.m_sLock );

    psInfo->m_uiSize = uMem.psMem_OS->m_sInfo_Header.m_uiSize;
    psInfo->m_uiFlags = uMem.psMem_OS->m_sInfo_Header.m_uiFlags;

#if TgCOMPILE__MEM_FREE_CLEAR
    tgMM_Set_U08( uMem.pVoid, sizeof(TgMEM_OS_HEADER) + (uMem.psMem_OS->m_sInfo_Header.m_bReserved ? 0 : uMem.psMem_OS->m_sInfo_Header.m_uiSize), 0xDD );
#endif

    tgMM_PM_Virtual_Free( uMem.pVoid );

    return (KTgS_OK);
}




/* ---- tgMM_Pool__Init_MGR ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT tgMM_Pool__Init_MGR( TgVOID )
{
    TgCRITICAL(s_uiPageSize / KTgMIN_BLOCK_SIZE < KTgMAX_U16);

    /* Set the memory page size and reset the allocation sizes and pool counts if the page size is smaller than expected */
    s_uiMaxBlock = tgCM_MIN_UMAX( 1024, s_uiPageSize >> 2 );
    s_nuiMaxPools = 1 + 4 * ((TgRSIZE)tgPM_BSR_UMAX( s_uiMaxBlock ) - KTgMIN_ALLOC_BIT);

    TgCRITICAL(s_nuiMaxPools > 0 && s_nuiMaxPools <= KTgMAX_POOLS);
    TgCRITICAL(s_uiMaxBlock >= KTgMIN_BLOCK_SIZE && s_uiMaxBlock <= KTgMAX_BLOCK_SIZE);
    TgCRITICAL((s_uiPageSize / KTgMIN_BLOCK_SIZE) < KTgMAX_U16);

    for (TgRSIZE uiIndex = 0; uiIndex < KTgMAX_POOLS; ++uiIndex)
    {
        TgVERIFY(KTgS_OK == tgCM_UT_LF__SN__Init( &s_asPage_Spin_Lock[uiIndex].m_sLock ));
        tgCM_UT_LF__ST__Init( &s_asPage_Open[uiIndex].m_sStack );
        TgVERIFY(KTgS_OK == tgCM_UT_ST__LT__Init( s_asPage_Closed + uiIndex ));
    };
    
    TgVERIFY(KTgS_OK == tgCM_UT_LF__SN__Init( &s_sPage_Cache_Spin_Lock.m_sLock ));
    TgVERIFY(KTgS_OK == tgCM_UT_ST__LT__Init( &s_sPage_Cache ));

    tgCM_UT_LF__RW__Init( &s_rwPage_Stat_Lock.m_sLock );

    return (KTgS_OK);
}


/* ---- tgMM_Pool__Free_MGR ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT tgMM_Pool__Free_MGR( TgVOID )
{
    union
    {
        STg2_UT_ST__ST_Node_P               psStack_Header;
        STg2_UT_ST__LT_Node_P               psList_Header;
        TgVOID_P                            pVoid;
        TgMEM_PAGE_HEADER_P                 psMem_Page;
    }                                   uMem;

    /* Look for unfreed allocation to report */
    for (TgRSIZE uiIndex = 0; uiIndex < KTgMAX_POOLS; ++uiIndex)
    {
        if (nullptr != tls_apsPage_Open[uiIndex])
        {
            tls_apsPage_Open[uiIndex] = nullptr;
        };

        while (nullptr != (uMem.psStack_Header = tgCM_UT_LF__ST__Pop( &s_asPage_Open[uiIndex].m_sStack )))
        {
            tgMM_Pool__Check_Page_Is_Empty( uMem.psMem_Page );
            tgMM_PM_Virtual_Free( uMem.psMem_Page );
        };

        TgERROR( tgCM_UT_ST__LT__Is_Empty( s_asPage_Closed + uiIndex ) );

        while (nullptr != (uMem.psList_Header = tgCM_UT_ST__LT__Pop_Front( s_asPage_Closed + uiIndex )))
        {
            tgMM_PM_Virtual_Free( uMem.psMem_Page );
        };

        /* Free the Critical Sections (nullptr Function if MP Safe not define-flagged ) */
        tgCM_UT_LF__SN__Free_Unsafe( &s_asPage_Spin_Lock[uiIndex].m_sLock );
    };

    tgCM_UT_LF__SN__Free_Unsafe( &s_sPage_Cache_Spin_Lock.m_sLock );

    while (nullptr != (uMem.psList_Header = tgCM_UT_ST__LT__Pop_Front( &s_sPage_Cache )))
    {
        tgMM_Pool__Check_Page_Is_Empty( uMem.psMem_Page );
        tgMM_PM_Virtual_Free( uMem.psMem_Page );
    };
    tgCM_UT_ST__LT__Free( &s_sPage_Cache );

    tgCM_UT_LF__RW__Free( &s_rwPage_Stat_Lock.m_sLock );

    return (KTgS_OK);
}


/* ---- tgMM_Pool__Stats --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if TgS_STAT__COMMON
TgVOID tgMM_Pool__Stats( TgRSIZE (*pfnIO_PrintF)( STg2_Output_PC, TgCHAR_U8_CPC, ... ), STg2_Output_PC psOUT )
{
    TgRSIZE                             uiIndex;

    pfnIO_PrintF( psOUT, u8"\n");
    pfnIO_PrintF( psOUT, u8"*******************************************************************************************************************************\n");
    pfnIO_PrintF( psOUT, u8"                                                          POOL STATS                                                           \n");
    pfnIO_PrintF( psOUT, u8"*******************************************************************************************************************************\n");
    pfnIO_PrintF( psOUT, u8"\n");
    for (uiIndex = 0; uiIndex < KTgMAX_POOLS; ++uiIndex)
    {
        TgRSIZE                             uiBlockSize, uiTotalSize, nuiAlloc;

        tgMM_Pool__Stats_Pool( uiIndex, &uiBlockSize, &uiTotalSize, &nuiAlloc );
        pfnIO_PrintF( psOUT, u8"Pool(% 8d)               % 8d    % 8d\n", uiBlockSize, uiTotalSize, nuiAlloc );
    };
    pfnIO_PrintF( psOUT, u8"\n");
    pfnIO_PrintF( psOUT, u8"\n");
}
/*# TgS_STAT__COMMON */
#endif


/* ---- tgMM_Pool__Size ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT tgMM_Pool__Size( TgUINT_E32_P pnbyReserve, TgUINT_E32_P pnbyAllocated, TgVOID_CPC pMem )
{
    union
    {
        TgVOID_CP                           pVoid;
        TgUINT_PTR                          uiPTR;
        TgMEM_OS_HEADER_CP                  psMem_OS;
    }                                   uMem;

    uMem.uiPTR = tgCM_FLR_ALGN_PW2_UMAX( (TgUINT_PTR)pMem, s_uiPageSize );
    TgCRITICAL( 0 == (uMem.uiPTR % s_uiPageSize) );

    if ((nullptr != pnbyReserve) && (nullptr != uMem.pVoid) && uMem.psMem_OS->m_sInfo_Header.m_bReserved)
    {
        *pnbyReserve = uMem.psMem_OS->m_sInfo_Header.m_uiSize;
    }
    else if (nullptr != pnbyReserve)
    {
        *pnbyReserve = 0;
    };

    if ((nullptr != pnbyAllocated) && (nullptr != uMem.pVoid) && !uMem.psMem_OS->m_sInfo_Header.m_bReserved)
    {
        *pnbyAllocated = uMem.psMem_OS->m_sInfo_Header.m_uiSize;
    }
    else if (nullptr != pnbyAllocated)
    {
        *pnbyAllocated = 0;
    };

    return (KTgS_OK);
}


/* ---- tgMM_Pool__Malloc -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT tgMM_Pool__Malloc( TgMEM_INFO_HEADER_P psInfo, TgVOID_PP ppReturn, TgRSIZE_C uiSize, TgRSIZE_C uiAlignment )
{
    TgRSIZE                             uiAligned_Size, uiBitPool, uiSize_Align, uiPool_MSD, uiPool_LSD, uiIndex_Pool;
    union
    {
        STg2_UT_ST__ST_Node_P               psStack_Header;
        TgVOID_P                            pVoid;
        TgMEM_PAGE_HEADER_P                 psMem_Page;
    }                                   uMem;
    TgUN_PTR                            uRet;
    TgUINT_E16                          uiFree, uiNext;

    uiAligned_Size = tgCM_CEL_ALGN_PW2_UMAX(uiSize, uiAlignment);
    if (uiAligned_Size > s_uiMaxBlock) /* Use the OS allocator (can always replace later) */
    {
        return (tgMM_OS__Malloc( psInfo, ppReturn, uiSize, uiAlignment ));
    };

    /* Retrieve a Block of Memory from the corresponding pool */

    uiBitPool = (TgRSIZE)tgPM_BSR_UMAX(uiAligned_Size | KTgMIN_BLOCK_SIZE ); /* Guaranteed to be at least 4 */
    uiSize_Align = tgCM_CEL_ALGN_PW2_UMAX(uiAligned_Size, ((TgRSIZE)1 << (uiBitPool - 2)) );
    uiBitPool = (TgRSIZE)tgPM_BSR_UMAX( uiSize_Align | KTgMIN_BLOCK_SIZE );
    uiSize_Align = tgCM_CEL_ALGN_PW2_UMAX(uiAligned_Size, ((TgRSIZE)1 << (uiBitPool - 2)) );

    TgCRITICAL( uiSize_Align <= 1024 );
    TgCRITICAL( uiBitPool <= 10 );

    uiPool_MSD = uiBitPool - KTgMIN_ALLOC_BIT;
    uiPool_LSD = (uiSize_Align >> (uiBitPool - 2)) & 3;
    uiIndex_Pool = uiPool_MSD * 4 + uiPool_LSD;

    TgCRITICAL( uiIndex_Pool < s_nuiMaxPools );

    uMem.psMem_Page = tls_apsPage_Open[uiIndex_Pool];

    if (nullptr == uMem.psMem_Page)
    {
        /* Attempt to grab a free page from the global open stack */
        uMem.psStack_Header = tgCM_UT_LF__ST__Pop( &s_asPage_Open[uiIndex_Pool].m_sStack );
        tls_apsPage_Open[uiIndex_Pool] = uMem.psMem_Page;
        if (nullptr != uMem.psMem_Page)
        {
            uMem.psMem_Page->m_sStack_Header.m_pNext_Node = nullptr;
            uMem.psMem_Page->m_uiState = ETgMM_PAGE_STATE_REOPENED;
        }
        else
        {
            TgRSIZE_C                           uiBlock_Size = (1 << (uiBitPool)) + (TgUINT_E32)uiPool_LSD*(1 << (uiBitPool - 2));
            TgRSIZE_C                           uiBlock_End = (s_uiPageSize - sizeof(TgMEM_PAGE_HEADER)) / uiBlock_Size;

            /* If still null then allocate a new page */
            uMem.pVoid = tgMM_PM_Virtual_Commit( nullptr, 0, s_uiPageSize );
            if (nullptr == uMem.pVoid)
            {
                TgCRITICAL( false );
                return (KTgE_FAIL);
            };

        #if TgCOMPILE__MEM_MALLOC_CLEAR
            tgMM_Set_U08( uMem.pVoid, s_uiPageSize, 0xAA );
            tgMM_Set_U08( uMem.pVoid, sizeof(TgMEM_PAGE_HEADER), 0xFF );
        #endif

            uMem.psMem_Page->m_sList_Header.m_pNext_Node = nullptr;
            uMem.psMem_Page->m_sList_Header.m_pPrev_Node = nullptr;
            uMem.psMem_Page->m_sInfo_Header.m_uiSize = (TgUINT_E32)s_uiPageSize;
            uMem.psMem_Page->m_sInfo_Header.m_uiFlags = 0;
            uMem.psMem_Page->m_sInfo_Header.m_enAllocator = ETgMM_ALLOCATOR_POOL;
            uMem.psMem_Page->m_uiState = ETgMM_PAGE_STATE_OPENED;
            uMem.psMem_Page->m_uiBlock_End = (TgUINT_E16)(uiBlock_End & KTgMAX_U16);
            uMem.psMem_Page->m_uiBlock_Last = 0;
            TgSTD_ATOMIC(store)( &uMem.psMem_Page->m_uiBlock_Free, KTgMAX_U16 );
            uMem.psMem_Page->m_uiBlock_Size = (TgUINT_E16)(uiBlock_Size & KTgMAX_U16);

            TgCRITICAL(uiBlock_End < KTgMAX_U16);
            TgVERIFY(uiBlock_Size < KTgMAX_U16);

            tls_apsPage_Open[uiIndex_Pool] = uMem.psMem_Page;
        };

        tgCM_UT_LF__SN__Lock_Spin( &s_sPage_Cache_Spin_Lock.m_sLock );
        tgCM_UT_ST__LT__Push_Front( &s_sPage_Cache, &uMem.psMem_Page->m_sList_Header );
        tgCM_UT_LF__SN__Signal( &s_sPage_Cache_Spin_Lock.m_sLock );
    };

    TgVERIFY(uMem.psMem_Page->m_uiState == ETgMM_PAGE_STATE_OPENED || uMem.psMem_Page->m_uiState == ETgMM_PAGE_STATE_REOPENED)
    TgCRITICAL( uMem.psMem_Page->m_uiBlock_Size >= uiAligned_Size);

    /* At this point we have a thread local pointer to a global memory structure (the memory page). Allocations that were made from this page could be freed at any point of time
       on other threads. Therefore, any fields that may be modified by the free routine need to be treated with standard multi-threaded precautions. However, those that are used
       only during allocation can be treated as being thread local (single thread safe). We can safely assume that this thread is the only thread allocating memory. */


    tgCM_UT_LF__RW__Enter_Read_Yield_Block( &s_rwPage_Stat_Lock.m_sLock );

    uiFree = TgSTD_ATOMIC(load)( &uMem.psMem_Page->m_uiBlock_Free );
    uRet.m_uiPTR = 0;
    while (uiFree != KTgMAX_U16)
    {
        uRet.m_puiE08 = uMem.psMem_Page->m_auiData;
        uRet.m_uiPTR += uiFree * uMem.psMem_Page->m_uiBlock_Size;
        uiNext = *uRet.m_puiE16;
        if (TgSTD_ATOMIC(compare_exchange_strong)( &uMem.psMem_Page->m_uiBlock_Free, &uiFree, uiNext ))
        {
            break;
        };
    };

    if (0 == uRet.m_uiPTR)
    {
        uRet.m_puiE08 = uMem.psMem_Page->m_auiData;
        uRet.m_uiPTR += uMem.psMem_Page->m_uiBlock_Last * uMem.psMem_Page->m_uiBlock_Size;
        ++uMem.psMem_Page->m_uiBlock_Last;
    };

    *psInfo = uMem.psMem_Page->m_sInfo_Header;
    psInfo->m_uiSize = uMem.psMem_Page->m_uiBlock_Size;
    *ppReturn = uRet.m_pVoid;

    /* Close the Page if no free memory available in it after this last allocation */
    if (uMem.psMem_Page->m_uiBlock_Last >= uMem.psMem_Page->m_uiBlock_End)
    {
        tgCM_UT_LF__SN__Lock_Spin( &s_asPage_Spin_Lock[uiIndex_Pool].m_sLock );
        if (KTgMAX_U16 == TgSTD_ATOMIC(load)( &uMem.psMem_Page->m_uiBlock_Free ))
        {
            tgCM_UT_LF__SN__Lock_Spin( &s_sPage_Cache_Spin_Lock.m_sLock );
            tgCM_UT_ST__LT__Remove( &uMem.psMem_Page->m_sList_Header );
            tgCM_UT_LF__SN__Signal( &s_sPage_Cache_Spin_Lock.m_sLock );
            uMem.psMem_Page->m_uiState = ETgMM_PAGE_STATE_CLOSED;
            tls_apsPage_Open[uiIndex_Pool] = nullptr;
            TgVERIFY(nullptr == uMem.psMem_Page->m_sList_Header.m_pNext_Node);
            TgVERIFY(nullptr == uMem.psMem_Page->m_sList_Header.m_pPrev_Node);
            tgCM_UT_ST__LT__Push_Front( s_asPage_Closed + uiIndex_Pool, &uMem.psMem_Page->m_sList_Header );
        };
        tgCM_UT_LF__SN__Signal( &s_asPage_Spin_Lock[uiIndex_Pool].m_sLock );
    };

#if TgCOMPILE__MEM_MALLOC_CLEAR
    tgMM_Set_U08( uRet.m_pVoid, uMem.psMem_Page->m_uiBlock_Size, 0xBB );
#endif

    tgCM_UT_LF__RW__Exit_Read( &s_rwPage_Stat_Lock.m_sLock );

    return (KTgS_OK);
}


/* ---- tgMM_Pool__Free ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT tgMM_Pool__Free( TgMEM_INFO_HEADER_P psInfo, TgVOID_PC pMem )
{
    union
    {
        TgUINT_PTR                          uiPTR;
        STg2_UT_ST__ST_Node_P               psStack_Header;
        TgVOID_P                            pVoid;
        TgMEM_PAGE_HEADER_P                 psMem_Page;
    }                                   uMem;

    uMem.uiPTR = tgCM_FLR_ALGN_PW2_UMAX( (TgUINT_PTR)pMem, s_uiPageSize );
    TgVERIFY(uMem.uiPTR == tgCM_CEL_ALGN_PW2_UMAX( (TgUINT_PTR)pMem, s_uiPageSize ) - s_uiPageSize);

    if (ETgMM_ALLOCATOR_POOL != (ETgMM_ALLOCATOR)uMem.psMem_Page->m_sInfo_Header.m_enAllocator)
    {
        TgERROR(ETgMM_ALLOCATOR_OS == (ETgMM_ALLOCATOR)uMem.psMem_Page->m_sInfo_Header.m_enAllocator); // OS Allocator is the only expected fallback.
        return (tgMM_OS__Free( psInfo, pMem ));
    }
    else
    {
        TgRSIZE                             uiBitPool, uiPool_MSD, uiPool_LSD, uiIndex_Pool;
        TgUN_PTR                            uBlock_Index, uFree;
        TgUINT_E16                          uiBlock_Index, uiFree;

        uBlock_Index.m_pVoid = pMem;
        uBlock_Index.m_iPTR = uBlock_Index.m_puiE08 - uMem.psMem_Page->m_auiData;
        TgERROR(0 == (uBlock_Index.m_uiRSIZE % uMem.psMem_Page->m_uiBlock_Size));
        uBlock_Index.m_uiRSIZE /= uMem.psMem_Page->m_uiBlock_Size;
        TgERROR(uBlock_Index.m_uiRSIZE < (TgRSIZE)uMem.psMem_Page->m_uiBlock_Last);
        uiBlock_Index = (TgUINT_E16)(uBlock_Index.m_uiRSIZE & KTgMAX_U16);
        TgERROR( (TgVOID_P)(uMem.psMem_Page->m_auiData + uBlock_Index.m_uiRSIZE*uMem.psMem_Page->m_uiBlock_Size) == pMem );

        uiBitPool = (TgRSIZE)tgPM_BSR_UMAX( uMem.psMem_Page->m_uiBlock_Size );
        uiPool_MSD = uiBitPool - KTgMIN_ALLOC_BIT;
        uiPool_LSD = (uMem.psMem_Page->m_uiBlock_Size >> (uiBitPool - 2)) & 3u;
        uiIndex_Pool = uiPool_MSD * 4 + uiPool_LSD;

    #if TgCOMPILE__MEM_FREE_CLEAR
        tgMM_Set_U08( pMem, uMem.psMem_Page->m_uiBlock_Size, 0xEE );
    #endif

        tgCM_UT_LF__RW__Enter_Read_Yield_Block( &s_rwPage_Stat_Lock.m_sLock );

        /* Add the block to the free list */
        tgCM_UT_LF__SN__Lock_Spin( &s_asPage_Spin_Lock[uiIndex_Pool].m_sLock );
        uiFree = TgSTD_ATOMIC(load)( &uMem.psMem_Page->m_uiBlock_Free );
        uFree.m_pVoid = pMem;
        do
        {
            *uFree.m_puiE16 = uiFree;
        }
        while (!TgSTD_ATOMIC(compare_exchange_strong)( &uMem.psMem_Page->m_uiBlock_Free, &uiFree, uiBlock_Index ));

        psInfo->m_uiSize = uMem.psMem_Page->m_uiBlock_Size;
        psInfo->m_uiFlags = uMem.psMem_Page->m_sInfo_Header.m_uiFlags;

        /* Check to see if this has re-opened a formerly closed page. */
        if (uMem.psMem_Page->m_uiBlock_Last >= uMem.psMem_Page->m_uiBlock_End && KTgMAX_U16 == uiFree)
        {
            TgVERIFY(ETgMM_PAGE_STATE_CLOSED == uMem.psMem_Page->m_uiState);
            tgCM_UT_ST__LT__Remove( &uMem.psMem_Page->m_sList_Header );
            TgVERIFY(nullptr == uMem.psMem_Page->m_sList_Header.m_pNext_Node);
            TgVERIFY(nullptr == uMem.psMem_Page->m_sList_Header.m_pPrev_Node);
            TgVERIFY(nullptr == uMem.psMem_Page->m_sStack_Header.m_pNext_Node);
            uMem.psMem_Page->m_uiState = ETgMM_PAGE_STATE_REOPENED_QUEUED;
            tgCM_UT_LF__ST__Push( &s_asPage_Open[uiIndex_Pool].m_sStack, uMem.psStack_Header );
        };
        tgCM_UT_LF__SN__Signal( &s_asPage_Spin_Lock[uiIndex_Pool].m_sLock );

        tgCM_UT_LF__RW__Exit_Read( &s_rwPage_Stat_Lock.m_sLock );
    };
    
    return (KTgS_OK);
}
TgCOMPILER_ASSERT(0 == offsetof(TgMEM_PAGE_HEADER,m_sStack_Header), 0);

/* ---- tgMM_Pool__Realloc ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT tgMM_Pool__Realloc( TgMEM_INFO_HEADER_P psNew_Info, TgVOID_PP ppNew, TgMEM_INFO_HEADER_P psOld_Info, TgVOID_PC pOld, TgRSIZE_C uiNewSize, TgRSIZE_C uiNewAlignment )
{
    union
    {
        TgUINT_PTR                          uiPTR;
        STg2_UT_ST__ST_Node_P               psStack_Header;
        TgVOID_P                            pVoid;
        TgMEM_PAGE_HEADER_P                 psMem_Page;
    }                                   uMem;
    TgBOOL                              bIs_Pool_Allocation;

    if (nullptr == pOld)
    {
        return (KTgE_FAIL);
    };

    uMem.uiPTR = tgCM_FLR_ALGN_PW2_UMAX( (TgUINT_PTR)pOld, s_uiPageSize );
    TgVERIFY(uMem.uiPTR == tgCM_CEL_ALGN_PW2_UMAX( (TgUINT_PTR)pOld, s_uiPageSize ) - s_uiPageSize);
    psOld_Info->m_uiFlags = uMem.psMem_Page->m_sInfo_Header.m_uiFlags;
    psOld_Info->m_uiSize = uMem.psMem_Page->m_uiBlock_Size;

    bIs_Pool_Allocation = ETgMM_ALLOCATOR_POOL == (ETgMM_ALLOCATOR)uMem.psMem_Page->m_sInfo_Header.m_enAllocator;

    if (bIs_Pool_Allocation && uMem.psMem_Page->m_uiBlock_Size >= uiNewSize)
    {
        psNew_Info->m_uiFlags = uMem.psMem_Page->m_sInfo_Header.m_uiFlags;
        psNew_Info->m_uiSize = uMem.psMem_Page->m_uiBlock_Size;
        *ppNew = pOld;
        return (KTgS_OK);
    };

    /* Allocate the New Size, and copy the data from the old Allocation to the new Allocation */

    if (TgFAILED(tgMM_Pool__Malloc( psNew_Info, ppNew, uiNewSize, uiNewAlignment )))
    {
        return (KTgE_FAIL);
    };

    if (bIs_Pool_Allocation)
    {
        tgMM_Copy( *ppNew, uiNewSize, pOld, uMem.psMem_Page->m_uiBlock_Size );
    }
    else
    {
        tgMM_Copy( *ppNew, uiNewSize, pOld, uMem.psMem_Page->m_sInfo_Header.m_uiSize );
    };

    tgMM_Pool__Free( psOld_Info, pOld );

    return (KTgS_OK);
}


/* ---- tgMM_Pool_Stats ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if TgS_STAT__COMMON
TgVOID tgMM_Pool__Stats_Pool( TgRSIZE_C uiPoolIndex, TgRSIZE_P puiBlock_Size, TgRSIZE_P puiTotal_Size, TgRSIZE_P pnuiAlloc )
{
    TgUINT_E32                          nuiAlloc, uiBlock_Size, uiBitPool, uiPool_MSD, uiPool_LSD;
    STg2_UT_ST__PTR_TKT                 sStack_Top;
    union
    {
        TgUINT_PTR                          uiPTR;
        STg2_UT_ST__ST_Node_P               psStack_Header;
        STg2_UT_ST__LT_Node_P               psList_Header;
        TgVOID_P                            pVoid;
        TgMEM_PAGE_HEADER_P                 psMem_Page;
    }                                   uPage;
    TgUINT_E16                          uiFree;

    uiPool_MSD = (TgUINT_E32)(uiPoolIndex >> 2);
    uiBitPool = uiPool_MSD + KTgMIN_ALLOC_BIT;
    uiBlock_Size = 1u << uiBitPool;
    uiPool_LSD = uiPoolIndex & 3;
    uiBlock_Size += uiPool_LSD << (uiBitPool - 2);

    nuiAlloc = 0;

    tgCM_UT_LF__RW__Enter_Write_Yield_Block( &s_rwPage_Stat_Lock.m_sLock );

    /* Walk through all of the open pages associated with this pool. */
    sStack_Top = TgSTD_ATOMIC(load)( &s_asPage_Open[uiPoolIndex].m_sStack.m_sTop );
    uPage.psStack_Header = sStack_Top.m_pHead;
    for (; nullptr != uPage.psMem_Page; uPage.pVoid = uPage.psMem_Page->m_sStack_Header.m_pNext_Node)
    {
        TgERROR(uiBlock_Size == uPage.psMem_Page->m_uiBlock_Size);

        /* Start with assuming that all blocks from start to last are continuously allocated. */
        nuiAlloc += uPage.psMem_Page->m_uiBlock_Last;

        /* Walk the free list to count the number of allocations that were not allocated. */
        uiFree = TgSTD_ATOMIC(load)( &uPage.psMem_Page->m_uiBlock_Free );
        while (KTgMAX_U16 != uiFree)
        {
            TgUN_POINTER                        sUnion;

            sUnion.m_pui08 = uPage.psMem_Page->m_auiData + uiFree * uiBlock_Size;
            uiFree = *(sUnion.m_puiE16);
            --nuiAlloc;
        };
    };

    /* Count all the allocations that are on closed pages. */
    uPage.psList_Header = s_asPage_Closed[uiPoolIndex].m_sNode.m_pNext_Node;
    while (uPage.psList_Header != &s_asPage_Closed[uiPoolIndex].m_sNode)
    {
        TgERROR(uiBlock_Size == uPage.psMem_Page->m_uiBlock_Size);
        nuiAlloc += uPage.psMem_Page->m_uiBlock_End;
        uPage.psList_Header = uPage.psList_Header->m_pNext_Node;
    };

    /* Walk through the page cache for pages that match the pool's size. */
    tgCM_UT_LF__SN__Lock_Spin( &s_sPage_Cache_Spin_Lock.m_sLock );
    uPage.psList_Header = s_sPage_Cache.m_sNode.m_pNext_Node;
    for (;uPage.psList_Header != &s_sPage_Cache.m_sNode; uPage.psList_Header = uPage.psList_Header->m_pNext_Node)
    {
        if (uiBlock_Size != uPage.psMem_Page->m_uiBlock_Size)
        {
            continue;
        };

        /* Start with assuming that all blocks from start to last are continuously allocated. */
        nuiAlloc += uPage.psMem_Page->m_uiBlock_Last;

        /* Walk the free list to count the number of allocations that were not allocated. */
        uiFree = TgSTD_ATOMIC(load)( &uPage.psMem_Page->m_uiBlock_Free );
        while (KTgMAX_U16 != uiFree)
        {
            TgUN_POINTER                        sUnion;

            sUnion.m_pui08 = uPage.psMem_Page->m_auiData + uiFree * uiBlock_Size;
            uiFree = *(sUnion.m_puiE16);
            --nuiAlloc;
        };
    };
    tgCM_UT_LF__SN__Signal( &s_sPage_Cache_Spin_Lock.m_sLock );

    *puiBlock_Size = uiBlock_Size;
    *puiTotal_Size = nuiAlloc * uiBlock_Size;
    *pnuiAlloc = nuiAlloc;

    tgCM_UT_LF__RW__Exit_Write( &s_rwPage_Stat_Lock.m_sLock );
}
/*# TgS_STAT__COMMON */
#endif


/* ---- tgMM_Pool__Check_Page_Is_Empty ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgBOOL tgMM_Pool__Check_Page_Is_Empty( TgMEM_PAGE_HEADER_P psMem_Page )
{
    TgUN_POINTER                        sUnion;
    TgRSIZE                             nuiFree;

    sUnion.m_pVoid = nullptr;

    if ((0 == psMem_Page->m_uiBlock_Last) && (KTgMAX_U16 == TgSTD_ATOMIC(load)( &psMem_Page->m_uiBlock_Free )))
    {
        return (true);
    };

    /* Count the number of free blocks */
    nuiFree = 0;
    for (TgUINT_E16 uiFree = TgSTD_ATOMIC(load)( &psMem_Page->m_uiBlock_Free ); (KTgMAX_U16 != uiFree); ++nuiFree)
    {
        TgERROR(uiFree < psMem_Page->m_uiBlock_Last);
        sUnion.m_pui08 = psMem_Page->m_auiData;
        sUnion.m_uiPTR += uiFree * psMem_Page->m_uiBlock_Size;
        uiFree = *(sUnion.m_puiE16);
    };

    /* Check to see the total free list matches the current high water mark */
    TgERROR(psMem_Page->m_uiBlock_Last >= nuiFree);
    if (0 == (psMem_Page->m_uiBlock_Last - nuiFree))
    {
        return (true);
    };

    /* Pool is not empty - find the unfreed allocations */
    for (TgUINT_E16 uiCheck = 0; uiCheck < psMem_Page->m_uiBlock_Last; ++uiCheck)
    {
        TgUINT_E16                          uiFree;

        for (uiFree = TgSTD_ATOMIC(load)( &psMem_Page->m_uiBlock_Free ); (KTgMAX_U16 != uiFree) && (uiFree != uiCheck);)
        {
            sUnion.m_pui08 = psMem_Page->m_auiData;
            sUnion.m_uiPTR += uiFree * psMem_Page->m_uiBlock_Size;
            uiFree = *(sUnion.m_puiE16);
        };

        if (uiFree == uiCheck)
        {
            continue;
        };

        tgCN_PrintF( KTgCN_CHANEL_LOG_MEM, STD_MSG_PREFIX, STD_MSG_POST);
        tgCN_PrintF( KTgCN_CHANEL_LOG_MEM, u8"Unfreed Memory Allocation at (% 16p).\n", u8"Common", u8"MM_Free_MGR", sUnion.m_pVoid );
    };

    return (false);
}

/* ---- tgMM_Stat_Internal__Entry ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if TgS_STAT__COMMON
TgINLINE TgVOID tgMM_Stat_Internal__Entry( TgMEM_INFO_HEADER_P psInfo )
{
    TgRSIZE                             nbyReserved, nbyAllocated, uiValue, uiUpdate;

    uiValue = TgSTD_ATOMIC(fetch_add)( s_anuiStat_Allocations + psInfo->m_enAllocator, 1 ) + 1;
    if (uiValue > (uiUpdate = TgSTD_ATOMIC(load)( s_anuiStat_Max_Allocations + psInfo->m_enAllocator )))
    {
        while (!TgSTD_ATOMIC(compare_exchange_strong)( s_anuiStat_Max_Allocations + psInfo->m_enAllocator, &uiUpdate, uiValue) && (uiValue > uiUpdate));
    };

    nbyReserved = psInfo->m_bReserved ? psInfo->m_uiSize : 0;
    nbyAllocated = psInfo->m_bReserved ? 0 : psInfo->m_uiSize;

    uiValue = TgSTD_ATOMIC(fetch_add)( s_auiStat_Reserved + psInfo->m_enAllocator, nbyReserved ) + nbyReserved;
    if (uiValue > (uiUpdate = TgSTD_ATOMIC(load)( s_auiStat_Max_Reserved + psInfo->m_enAllocator )))
    {
        while (!TgSTD_ATOMIC(compare_exchange_strong)( s_auiStat_Max_Reserved + psInfo->m_enAllocator, &uiUpdate, uiValue) && (uiValue > uiUpdate));
    };

    uiValue = TgSTD_ATOMIC(fetch_add)( s_auiStat_Allocated + psInfo->m_enAllocator, nbyAllocated ) + nbyAllocated;
    if (uiValue > (uiUpdate = TgSTD_ATOMIC(load)( s_auiStat_Max_Allocated + psInfo->m_enAllocator )))
    {
        while (!TgSTD_ATOMIC(compare_exchange_strong)( s_auiStat_Max_Allocated + psInfo->m_enAllocator, &uiUpdate, uiValue) && (uiValue > uiUpdate));
    };
}
/*# TgS_STAT__COMMON */
#endif
