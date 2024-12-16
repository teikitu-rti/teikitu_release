/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Mem MGR.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/** @note Memory Pools: A pool is created for each power of 2 greater than 8, and for the 3 most significant binary values after them (i.e. 10000, 10100, 11000, 11100) - up to
    MAXPOOL count. If the OS Page_Size is less than the normal MaxAlloc size number of pools and MaxAlloc are correspondingly modified so that MaxAlloc matches Page_Size. The
    reason for this is to reduce internal fragmentation and because no time savings would be incurred. */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Platform Functions                                                                                                                                                    */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TgEXTN TgUINT_F32
tgMM_PM_Page_Size( TgVOID );

TgEXTN TgVOID_P
tgMM_PM_Virtual_Reserve(
    TgRSIZE_C );

TgEXTN TgVOID_P
tgMM_PM_Virtual_Commit(
    TgVOID_PC, TgRSIZE_C );

TgEXTN TgVOID
tgMM_PM_Virtual_Free( TgVOID_PC );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Constants                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

enum { KTgMIN_ALLOC_BIT                     = 4 }; /* This can not be smaller than sizeof(void*) */
enum { KTgMIN_BLOCK_SIZE                    = 1 << KTgMIN_ALLOC_BIT };
enum { KTgMAX_BLOCK_SIZE                    = 1024 }; /* Pools have a range of [16, 1024] */
enum { KTgMAX_POOLS                         = 25 }; /* Number of pools to fit max block size of 1024 */

TgCOMPILER_ASSERT(16 == KTgMIN_BLOCK_SIZE,);

TgTYPE_ENUM(ETgMM_PAGE_STATE,TgSINT_E32,
    ETgMM_PAGE_STATE_OPENED = 0x10,
    ETgMM_PAGE_STATE_REOPENED = 0x11,
    ETgMM_PAGE_STATE_CLOSED = 0x20,
    ETgMM_PAGE_STATE_REOPENED_QUEUED = 0x30,
);



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
    STg2_UT_ST__ST_Node                         m_sStack_Header;                                    /* Used to track open pages */
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

#if defined(TgS_COMPILE__MEMORY_TRACE) && TgS_COMPILE__MEMORY_TRACE
TgTYPE_STRUCT(TgTRACE_ENTRY,)
{
    TgCHAR_U8_CP                                m_pmbzFile;
    TgRSIZE                                     m_uiSize;
    TgUINT_E32                                  m_uiLine;
    ETgMM_ALLOCATOR                             m_enAllocator;
};
/*# defined(TgS_COMPILE__MEMORY_TRACE) && TgS_COMPILE__MEMORY_TRACE */
#endif



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
    TgUINT_F32_P NONULL, TgUINT_F32_P NONULL, TgVOID_CPC NONULL );

static TgRESULT
tgMM_OS__Malloc(
    TgMEM_INFO_HEADER_P NONULL, TgVOID_PP NONULL, TgRSIZE_C );

static TgRESULT
tgMM_OS__Reserve(
    TgMEM_INFO_HEADER_P NONULL, TgVOID_PP NONULL, TgRSIZE_C );

static TgRESULT
tgMM_OS__Commit(
    TgMEM_INFO_HEADER_P NONULL, TgVOID_PP NONULL, TgRSIZE_C );

static TgRESULT
tgMM_OS__Free(
    TgMEM_INFO_HEADER_P NONULL, TgVOID_PC NONULL );


/* Memory Pool */

static TgRESULT
tgMM_Pool__Init_MGR( TgVOID );

static TgRESULT
tgMM_Pool__Free_MGR( TgVOID );

static TgRESULT
tgMM_Pool__Size(
    TgUINT_F32_P NONULL, TgUINT_F32_P NONULL, TgVOID_CPC NONULL );

static TgRESULT
tgMM_Pool__Malloc(
    TgMEM_INFO_HEADER_P NONULL, TgVOID_PP NONULL, TgRSIZE_C );

static TgRESULT
tgMM_Pool__Free(
    TgMEM_INFO_HEADER_P NONULL, TgVOID_PC NONULL );

static TgRESULT
tgMM_Pool__Realloc(
    TgMEM_INFO_HEADER_P NONULL, TgVOID_PP NONULL, TgMEM_INFO_HEADER_P NONULL, TgVOID_PC NONULL, TgRSIZE_C );

static TgBOOL
tgMM_Pool__Check_Page_Is_Empty(
    TgMEM_PAGE_HEADER_P );


#if TgS_STAT__COMMON

TgINLINE TgVOID
tgMM_Stat_Internal__Entry(
    ETgMM_ALLOCATOR_C, TgMEM_INFO_HEADER_P NONULL );

static TgVOID
tgMM_Pool__Stats(
    STg2_Output_PC NONULL );

static TgVOID
tgMM_Pool__Stats_Pool(
    TgRSIZE_C, TgRSIZE_P, TgRSIZE_P, TgRSIZE_P );

/*# TgS_STAT__COMMON */
#endif


#if defined(TgS_COMPILE__MEMORY_TRACE) && TgS_COMPILE__MEMORY_TRACE

static TgVOID
tgMM_Print_Trace_Header(
    STg2_Output_PC psOUT );

static TgVOID
tgMM_Print_Trace_Entry(
    STg2_Output_PC, TgUINT_E08_CPC );

static TgUINT_PTR
tgMM_Hash_Trace_Entry(
    TgUINT_PTR_C );

/*# defined(TgS_COMPILE__MEMORY_TRACE) && TgS_COMPILE__MEMORY_TRACE */
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

#if defined(TgS_COMPILE__MEMORY_TRACE) && TgS_COMPILE__MEMORY_TRACE
static STg2_UT_LF__HT_RW                    s_sTrace_Table;
static TgUINT_E08                           s_sTrace_Table_Buffer[1024*1024];
/*# defined(TgS_COMPILE__MEMORY_TRACE) && TgS_COMPILE__MEMORY_TRACE */
#endif

#if TgS_STAT__COMMON
static TgCHAR_U8_C                          s_ambzStat_Name[ETgMM_ALLOCATOR_COUNT][8] = { u8"OS", u8"Pool", u8"User 0", u8"User 1", u8"User 2", u8"User 3" };
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

/* ---- tgMM_Init_MGR ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgMM_Init_MGR( TgVOID )
{
    STg2_MM_MGR                         sMGR;

    TgERROR(ETgMODULE_STATE__FREED == s_enMem_MGR_State);
    s_enMem_MGR_State = ETgMODULE_STATE__INITIALIZING;

    tgMM_Set_U08_0x00( s_asAllocator, sizeof( s_asAllocator ) );
    s_uiPageSize = tgMM_Page_Size();

#if defined(TgS_COMPILE__MEMORY_TRACE) && TgS_COMPILE__MEMORY_TRACE
    TgVERIFY(KTgS_OK == tgCM_UT_LF__HT_RW__Init_Fixed( &s_sTrace_Table, sizeof( TgTRACE_ENTRY ), 4096, sizeof( s_sTrace_Table_Buffer ), s_sTrace_Table_Buffer ));
/*# defined(TgS_COMPILE__MEMORY_TRACE) && TgS_COMPILE__MEMORY_TRACE */
#endif

#if TgS_STAT__COMMON
    for (TgRSIZE uiIndex = 0; uiIndex < ETgMM_ALLOCATOR_COUNT; ++uiIndex)
    {
        atomic_store( s_anuiStat_Allocations + uiIndex, 0 );
        atomic_store( s_anuiStat_Max_Allocations + uiIndex, 0 );
        atomic_store( s_auiStat_Allocated + uiIndex, 0 );
        atomic_store( s_auiStat_Max_Allocated + uiIndex, 0 );
        atomic_store( s_auiStat_Reserved + uiIndex, 0 );
        atomic_store( s_auiStat_Max_Reserved + uiIndex, 0 );
    };
/*# TgS_STAT__COMMON */
#endif


    /* Register the default allocators */

    tgMM_Set_U08_0x00( &sMGR, sizeof( STg2_MM_MGR ) );
    sMGR.m_pfnInit_MGR = tgMM_OS__Init_MGR;
    sMGR.m_pfnFree_MGR = tgMM_OS__Free_MGR;
    sMGR.m_pfnSize = tgMM_OS__Size;
    sMGR.m_pfnMalloc = tgMM_OS__Malloc;
    sMGR.m_pfnReserve = tgMM_OS__Reserve;
    sMGR.m_pfnCommit = tgMM_OS__Commit;
    sMGR.m_pfnFree = tgMM_OS__Free;
    tgMM_Register_Allocator( ETgMM_ALLOCATOR_OS, &sMGR );

    tgMM_Set_U08_0x00( &sMGR, sizeof( STg2_MM_MGR ) );
    sMGR.m_pfnInit_MGR = tgMM_Pool__Init_MGR;
    sMGR.m_pfnFree_MGR = tgMM_Pool__Free_MGR;
#if TgS_STAT__COMMON
    sMGR.m_pfnStats = tgMM_Pool__Stats;
#endif
    sMGR.m_pfnSize = tgMM_Pool__Size;
    sMGR.m_pfnMalloc = tgMM_Pool__Malloc;
    sMGR.m_pfnFree = tgMM_Pool__Free;
    sMGR.m_pfnRealloc = tgMM_Pool__Realloc;
    //sMGR.m_pfnClear_Thread_Local_Cache
    tgMM_Register_Allocator( ETgMM_ALLOCATOR_POOL, &sMGR );


    /* Sanity Checks */

    TgCRITICAL(tgCM_IS_PW2_UMAX( s_uiPageSize ) && tgMM_Page_Size() == s_uiPageSize);


    /* Initialize the allocators */

    for (TgRSIZE uiIndex = 0; uiIndex < ETgMM_ALLOCATOR_COUNT; ++uiIndex)
    {
        if (nullptr != s_asAllocator[uiIndex].m_pfnInit_MGR)
        {
            s_asAllocator[uiIndex].m_pfnInit_MGR();
        };
    };

    s_enMem_MGR_State = ETgMODULE_STATE__BOOTED;


#if TgCOMPILE__CONSOLE
    if (tgGB_CMD_Query_Argument_Index( u8"-//stat/boot/memory" ) >= 0)
    {
        tgMM_Stats( &g_sOutCon );
    };
/*# TgCOMPILE__CONSOLE */
#endif

    return (KTgS_OK);
}


/* ---- tgMM_Boot_MGR ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgMM_Boot_MGR( TgVOID )
{
    TgERROR_MSG( false, u8"This function should never be executed." );
    return (KTgS_OK);
}


/* ---- tgMM_Stop_MGR ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgMM_Stop_MGR( TgVOID )
{
    TgERROR_MSG( false, u8"This function should never be executed." );
    return (KTgS_OK);
}


/* ---- tgMM_Free_MGR ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgMM_Free_MGR( TgVOID )
{
    if (ETgMODULE_STATE__FREED == s_enMem_MGR_State)
    {
        return (KTgS_OK);
    };

#if TgCOMPILE__CONSOLE
    if (tgGB_CMD_Query_Argument_Index( u8"-//stat/free/memory" ) >= 0)
    {
        tgMM_Stats( &g_sOutCon );
    };
/*# TgCOMPILE__CONSOLE */
#endif

    TgERROR(ETgMODULE_STATE__BOOTED == s_enMem_MGR_State);

#if defined(TgS_COMPILE__MEMORY_TRACE) && TgS_COMPILE__MEMORY_TRACE
    if (s_sTrace_Table.m_nuiNode_Active)
    {
        tgMM_Print_Trace_Header( &g_sOutCon );
        tgCM_UT_LF__HT_RW__Output_List( &s_sTrace_Table, &g_sOutCon, tgMM_Print_Trace_Entry );
        tgIO_PrintF( &g_sOutCon, u8"\n" );
    };
    tgCM_UT_LF__HT_RW__Free( &s_sTrace_Table );
/*# defined(TgS_COMPILE__MEMORY_TRACE) && TgS_COMPILE__MEMORY_TRACE */
#endif

    s_enMem_MGR_State = ETgMODULE_STATE__FREEING;

    for (TgRSIZE uiIndex = 0; uiIndex < ETgMM_ALLOCATOR_COUNT; ++uiIndex)
    {
        if (nullptr != s_asAllocator[uiIndex].m_pfnFree_MGR)
        {
            s_asAllocator[uiIndex].m_pfnFree_MGR();
        };

    #if TgS_STAT__COMMON
        TgCRITICAL( 0 == atomic_load( s_anuiStat_Allocations + uiIndex ) );
        TgCRITICAL( 0 == atomic_load( s_auiStat_Allocated + uiIndex ) );
        TgCRITICAL( 0 == atomic_load( s_auiStat_Reserved + uiIndex ) );
    /*# TgS_STAT__COMMON */
    #endif
    };

    s_enMem_MGR_State = ETgMODULE_STATE__FREED;

    return (KTgS_OK);
}


/* ---- tgMM_Update_MGR ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgMM_Update_MGR( TgFLOAT32_C UNUSED_PARAM fDT )
{
    return (KTgS_OK);
}


/* ---- tgMM_Query_Init ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgMM_Query_Init( TgVOID )
{
    return (ETgMODULE_STATE__INITIALIZED <= s_enMem_MGR_State && s_enMem_MGR_State <= ETgMODULE_STATE__STOPPED);
}


/* ---- tgMM_Query_Boot ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgMM_Query_Boot( TgVOID )
{
    return (ETgMODULE_STATE__BOOTED == s_enMem_MGR_State);
}


/* ---- tgMM_Query_Fixed_Memory -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRSIZE tgMM_Query_Fixed_Memory( TgVOID )
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

        #if defined(TgS_COMPILE__MEMORY_TRACE) && TgS_COMPILE__MEMORY_TRACE
             + sizeof( s_sTrace_Table )
             + sizeof( s_sTrace_Table_Buffer )
        /*# defined(TgS_COMPILE__MEMORY_TRACE) && TgS_COMPILE__MEMORY_TRACE */
        #endif

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


/* ---- tgMM_Page_Size ----------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgUINT_F32 tgMM_Page_Size( TgVOID )
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


/* ---- tgMM_Clear_Thread_Local_Cache -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgMM_Clear_Thread_Local_Cache( TgVOID )
{
    for (TgRSIZE uiIndex = 0; uiIndex < ETgMM_ALLOCATOR_COUNT; ++uiIndex)
    {
        if (s_asAllocator[uiIndex].m_pfnClear_Thread_Local_Cache)
        {
            s_asAllocator[uiIndex].m_pfnClear_Thread_Local_Cache();
        };
    };
}


/* ---- tgMM_Stats --------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if TgS_STAT__COMMON
TgVOID tgMM_Stats( STg2_Output_PC psOUT )
{
    TgCHAR_U8                           mbzCol[6][32];

    TgERROR(nullptr != psOUT);

    tgIO_PrintF( psOUT, u8"%8.8s %16.16s %16.16s %16.16s %16.16s %16.16s %16.16s\n",
                 u8"", u8"  Allocations  ", u8"      Max      ", u8"   Allocated   ", u8"      Max      ", u8"    Reserve    ", u8"      Max      " );
    tgIO_PrintF( psOUT, u8"%8.8s %16.16s %16.16s %16.16s %16.16s %16.16s %16.16s\n",
                 u8"", u8"---------------", u8"---------------", u8"---------------", u8"---------------", u8"---------------", u8"---------------" );

    for (TgRSIZE uiIndex = 0; uiIndex < ETgMM_ALLOCATOR_COUNT; ++uiIndex)
    {
        tgUSZ_Formatted_From_U64( mbzCol[0], sizeof( mbzCol[0] ), atomic_load(s_anuiStat_Allocations + uiIndex) );
        tgUSZ_Formatted_From_U64( mbzCol[1], sizeof( mbzCol[1] ), atomic_load(s_anuiStat_Max_Allocations + uiIndex) );
        tgUSZ_Formatted_From_U64( mbzCol[2], sizeof( mbzCol[2] ), atomic_load(s_auiStat_Allocated + uiIndex) );
        tgUSZ_Formatted_From_U64( mbzCol[3], sizeof( mbzCol[3] ), atomic_load(s_auiStat_Max_Allocated + uiIndex) );
        tgUSZ_Formatted_From_U64( mbzCol[4], sizeof( mbzCol[4] ), atomic_load(s_auiStat_Reserved + uiIndex) );
        tgUSZ_Formatted_From_U64( mbzCol[5], sizeof( mbzCol[5] ), atomic_load(s_auiStat_Max_Reserved + uiIndex) );

        tgIO_PrintF( psOUT, u8"%8.8s %16.16s %16.16s %16.16s %16.16s %16.16s %16.16s\n",
                     s_ambzStat_Name[uiIndex], mbzCol[0], mbzCol[1], mbzCol[2], mbzCol[3], mbzCol[4], mbzCol[5] );
    };

    tgIO_PrintF( psOUT, u8"\n" );

#if defined(TgS_COMPILE__MEMORY_TRACE) && TgS_COMPILE__MEMORY_TRACE
    tgCM_UT_LF__HT_RW__Output_List( &s_sTrace_Table, psOUT, tgMM_Print_Trace_Entry );
    tgIO_PrintF( psOUT, u8"\n" );
/*# defined(TgS_COMPILE__MEMORY_TRACE) && TgS_COMPILE__MEMORY_TRACE */
#endif
}
/*# TgS_STAT__COMMON */
#endif


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


/* ---- tgMM_Malloc_With_Trace --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID_P tgMM_Malloc_With_Trace( ETgMM_ALLOCATOR_C enAllocator, TgRSIZE_C uiSize, TgCHAR_U8_CPC mbzF, TgUINT_E32_C uiL )
{
    TgVOID_P                            pReturn;

    pReturn = tgMM_Malloc( enAllocator, uiSize );

#if defined(TgS_COMPILE__MEMORY_TRACE) && TgS_COMPILE__MEMORY_TRACE
    {
        TgTRACE_ENTRY                       sTrace;
        TgUN_PTR                            sHash;

        sTrace.m_pmbzFile = mbzF;
        sTrace.m_uiSize = uiSize;
        sTrace.m_uiLine = uiL;
        sTrace.m_enAllocator = enAllocator;

        sHash.m_pVoid = pReturn;

        TgVERIFY(KTgS_OK == tgCM_UT_LF__HT_RW__Insert_Spin( &s_sTrace_Table, tgMM_Hash_Trace_Entry( sHash.m_uiPTR ), &sTrace ));
    }
/*# defined(TgS_COMPILE__MEMORY_TRACE) && TgS_COMPILE__MEMORY_TRACE */
#endif

    TgLOG_MEM( u8"Address: % 16p Size: % 16X File: % 128.128s Line % 5d\n", pReturn, uiSize, mbzF, uiL );
    return (pReturn);
}


/* ---- tgMM_Malloc -------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID_P tgMM_Malloc( ETgMM_ALLOCATOR_C enAllocator, TgRSIZE_C uiSize )
{
    TgMEM_INFO_HEADER                   sInfo;
    TgVOID_P                            pMem;

    TgERROR(ETgMODULE_STATE__BOOTED == s_enMem_MGR_State);
    TgPARAM_CHECK_INDEX( enAllocator, s_asAllocator );

    if (!s_asAllocator[enAllocator].m_pfnMalloc || (0 == uiSize))
    {
        return (nullptr);
    };

    if (TgFAILED(s_asAllocator[enAllocator].m_pfnMalloc( &sInfo, &pMem, uiSize )))
    {
        return (nullptr);
    };
    TgERROR(sInfo.m_uiSize >= uiSize);

#if TgS_STAT__COMMON
    tgMM_Stat_Internal__Entry( enAllocator, &sInfo );
#endif

    return (pMem);
}


/* ---- tgMM_Reserve_With_Trace -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID_P tgMM_Reserve_With_Trace( ETgMM_ALLOCATOR_C enAllocator, TgRSIZE_C uiSize, TgCHAR_U8_CPC mbzF, TgUINT_F32_C uiL )
{
    TgVOID_P                            pReturn;

    pReturn = tgMM_Reserve( enAllocator, uiSize );

#if defined(TgS_COMPILE__MEMORY_TRACE) && TgS_COMPILE__MEMORY_TRACE
    {
        TgTRACE_ENTRY                       sTrace;
        TgUN_PTR                            sHash;

        sTrace.m_pmbzFile = mbzF;
        sTrace.m_uiSize = uiSize;
        sTrace.m_uiLine = uiL;
        sTrace.m_enAllocator = enAllocator;

        sHash.m_pVoid = pReturn;

        TgVERIFY(KTgS_OK == tgCM_UT_LF__HT_RW__Insert_Spin( &s_sTrace_Table, tgMM_Hash_Trace_Entry( sHash.m_uiPTR ), &sTrace ));
    }
/*# defined(TgS_COMPILE__MEMORY_TRACE) && TgS_COMPILE__MEMORY_TRACE */
#endif

    TgLOG_MEM( u8"Address: % 16p Size: % 16X File: % 128.128s Line % 5d\n", pReturn, uiSize, mbzF, uiL );
    return (pReturn);
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
    tgMM_Stat_Internal__Entry( enAllocator, &sInfo );
#endif

    return (pMem);
}


/* ---- tgMM_Commit_With_Trace --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID_P tgMM_Commit_With_Trace( ETgMM_ALLOCATOR_C enAllocator, TgVOID_PC pMem, TgRSIZE_C uiSize, TgCHAR_U8_CPC mbzF, TgUINT_F32_C uiL )
{
    TgVOID_P                            pReturn;

    pReturn = tgMM_Commit( enAllocator, pMem, uiSize );

#if defined(TgS_COMPILE__MEMORY_TRACE) && TgS_COMPILE__MEMORY_TRACE
    if (nullptr == pMem)
    {
        TgTRACE_ENTRY                       sTrace;
        TgUN_PTR                            sHash;

        sTrace.m_pmbzFile = mbzF;
        sTrace.m_uiSize = uiSize;
        sTrace.m_uiLine = uiL;
        sTrace.m_enAllocator = enAllocator;

        sHash.m_pVoid = pReturn;

        TgVERIFY(KTgS_OK == tgCM_UT_LF__HT_RW__Insert_Spin( &s_sTrace_Table, tgMM_Hash_Trace_Entry( sHash.m_uiPTR ), &sTrace ));
    }
/*# defined(TgS_COMPILE__MEMORY_TRACE) && TgS_COMPILE__MEMORY_TRACE */
#endif

    TgLOG_MEM( u8"Address: % 16p Size: % 16X File: % 128.128s Line % 5d\n", pReturn, uiSize, mbzF, uiL );
    return (nullptr == pReturn ? pReturn : pMem);
}


/* ---- tgMM_Commit -------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID_P tgMM_Commit( ETgMM_ALLOCATOR_C enAllocator, TgVOID_P pMem, TgRSIZE_C uiSize )
{
    TgMEM_INFO_HEADER                   sInfo;

    TgERROR(ETgMODULE_STATE__BOOTED == s_enMem_MGR_State);
    TgPARAM_CHECK_INDEX( enAllocator, s_asAllocator );

    if (!s_asAllocator[enAllocator].m_pfnCommit || (0 == uiSize))
    {
        return (nullptr);
    };

    if (TgFAILED(s_asAllocator[enAllocator].m_pfnCommit( &sInfo, &pMem, uiSize )))
    {
        return (nullptr);
    };

#if TgS_STAT__COMMON
    if (0 != sInfo.m_uiSize)
    {
        tgMM_Stat_Internal__Entry( enAllocator, &sInfo );
    };
#endif

    return (pMem);
}


/* ---- tgMM_Free_With_Trace ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgMM_Free_With_Trace( ETgMM_ALLOCATOR_C enAllocator, TgVOID_PC pMem, TgCHAR_U8_CPC mbzF, TgUINT_F32_C uiL )
{
    tgMM_Free( enAllocator, pMem );

#if defined(TgS_COMPILE__MEMORY_TRACE) && TgS_COMPILE__MEMORY_TRACE
    {
        TgUN_PTR                            sHash;

        sHash.m_pVoid = pMem;

        TgVERIFY(KTgS_OK == tgCM_UT_LF__HT_RW__Remove_Spin( &s_sTrace_Table, tgMM_Hash_Trace_Entry( sHash.m_uiPTR )));
    }
/*# defined(TgS_COMPILE__MEMORY_TRACE) && TgS_COMPILE__MEMORY_TRACE */
#endif

    TgLOG_MEM( u8"Address: % 16p                        File: % 128.128s Line % 5d\n", pMem, mbzF, uiL );
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
    atomic_fetch_sub( s_anuiStat_Allocations + enAllocator, 1 );
    if (TgSUCCEEDED(iResult))
    {
        TgRSIZE                             uiValue;

        uiValue = sInfo.m_bReserved ? sInfo.m_uiSize : 0;
        atomic_fetch_sub( s_auiStat_Reserved + enAllocator, uiValue );
        uiValue = sInfo.m_bReserved ? 0 : sInfo.m_uiSize;
        atomic_fetch_sub( s_auiStat_Allocated + enAllocator, uiValue );
    };
#else
    (void)iResult;
#endif
}


/* ---- tgMM_Realloc_With_Trace -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID_P tgMM_Realloc_With_Trace( ETgMM_ALLOCATOR_C enAllocator, TgVOID_PC pMem, TgRSIZE_C uiSize, TgCHAR_U8_CPC mbzF, TgUINT_F32_C uiL )
{
    TgVOID_P                            pReturn;

    if (nullptr == pMem)
    {
        return (tgMM_Malloc_With_Trace( enAllocator, uiSize, mbzF, uiL ));
    };

    pReturn = tgMM_Realloc( enAllocator, pMem, uiSize );

#if defined(TgS_COMPILE__MEMORY_TRACE) && TgS_COMPILE__MEMORY_TRACE
    if (pReturn != pMem)
    {
        TgTRACE_ENTRY                       sTrace;
        TgUN_PTR                            sHash;

        sTrace.m_pmbzFile = mbzF;
        sTrace.m_uiSize = uiSize;
        sTrace.m_uiLine = uiL;
        sTrace.m_enAllocator = enAllocator;

        sHash.m_pVoid = pReturn;
        TgVERIFY(KTgS_OK == tgCM_UT_LF__HT_RW__Insert_Spin( &s_sTrace_Table, tgMM_Hash_Trace_Entry( sHash.m_uiPTR ), &sTrace ));

        sHash.m_pVoid = pMem;
        TgVERIFY(KTgS_OK == tgCM_UT_LF__HT_RW__Remove_Spin( &s_sTrace_Table, tgMM_Hash_Trace_Entry( sHash.m_uiPTR ) ));
    }
/*# defined(TgS_COMPILE__MEMORY_TRACE) && TgS_COMPILE__MEMORY_TRACE */
#endif

    TgLOG_MEM( u8"Address: % 16p Size: % 16X File: % 128.128s Line % 5d\n", pReturn, uiSize, mbzF, uiL );
    return (pReturn);
}


/* ---- tgMM_Realloc ------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID_P tgMM_Realloc( ETgMM_ALLOCATOR_C enAllocator, TgVOID_PC pMem, TgRSIZE_C uiSize )
{
    TgMEM_INFO_HEADER                   sOld_Info, sNew_Info;
    TgVOID_P                            pReturn;

    TgERROR(ETgMODULE_STATE__BOOTED == s_enMem_MGR_State);
    TgPARAM_CHECK_INDEX( enAllocator, s_asAllocator );

    if (nullptr == pMem)
    {
        return (tgMM_Malloc( enAllocator, uiSize ));
    };

    if (!s_asAllocator[enAllocator].m_pfnRealloc || (0 == uiSize))
    {
        return (nullptr);
    };

    if (TgFAILED(s_asAllocator[enAllocator].m_pfnRealloc( &sNew_Info, &pReturn, &sOld_Info, pMem, uiSize )))
    {
        return (nullptr);
    };

#if TgS_STAT__COMMON
    if (pReturn != pMem)
    {
        TgRSIZE                             uiValue;

        tgMM_Stat_Internal__Entry( enAllocator, &sNew_Info );
        atomic_fetch_sub( s_anuiStat_Allocations + enAllocator, 1 );

        uiValue = sOld_Info.m_bReserved ? sOld_Info.m_uiSize : 0;
        atomic_fetch_sub( s_auiStat_Reserved + enAllocator, uiValue );
        uiValue = sOld_Info.m_bReserved ? 0 : sOld_Info.m_uiSize;
        atomic_fetch_sub( s_auiStat_Allocated + enAllocator, uiValue );
    }
#endif

    return (pReturn);
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#if defined(TgS_COMPILE__MEMORY_TRACE) && TgS_COMPILE__MEMORY_TRACE
/* ---- tgMM_Print_Trace_Header -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgMM_Print_Trace_Header( STg2_Output_PC psOUT )
{
    tgIO_PrintF( psOUT, u8"%96.96s %16.16s %16.16s\n", u8"             File             ", u8"      Line     ", u8"      Size     " );
    tgIO_PrintF( psOUT, u8"%96.96s %16.16s %16.16s\n", u8"------------------------------", u8"---------------", u8"---------------" );
}


/* ---- tgMM_Print_Trace_Entry --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgMM_Print_Trace_Entry( STg2_Output_PC psOUT, TgUINT_E08_CPC puiData )
{
    union
    {
        TgTRACE_ENTRY_CP                    psEntry;
        TgUINT_E08_CP                       puiE08;
    }                                   uMem;
    TgCHAR_U8                           mbzCol[2][16];

    TgERROR(nullptr != psOUT);
    uMem.puiE08 = puiData;

    tgUSZ_Formatted_From_U64( mbzCol[0], sizeof( mbzCol[0] ), (TgUINT_E64)uMem.psEntry->m_uiLine );
    tgUSZ_Formatted_From_U64( mbzCol[1], sizeof( mbzCol[1] ), (TgUINT_E64)uMem.psEntry->m_uiSize );

    tgIO_PrintF( psOUT, u8"%96.96s %16.16s %16.16s\n", uMem.psEntry->m_pmbzFile, mbzCol[0], mbzCol[1] );
}
/*# defined(TgS_COMPILE__MEMORY_TRACE) && TgS_COMPILE__MEMORY_TRACE */
#endif


#if defined(TgS_COMPILE__MEMORY_TRACE) && TgS_COMPILE__MEMORY_TRACE
/* ---- tgMM_Print_Trace_Entry --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgUINT_PTR tgMM_Hash_Trace_Entry( TgUINT_PTR_C uiValue )
{
    return (uiValue >> 16) | (uiValue << 48);
}
/*# defined(TgS_COMPILE__MEMORY_TRACE) && TgS_COMPILE__MEMORY_TRACE */
#endif


/* ---- tgMM_Stat_Internal__Entry ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if TgS_STAT__COMMON
TgINLINE TgVOID tgMM_Stat_Internal__Entry( ETgMM_ALLOCATOR_C enAllocator, TgMEM_INFO_HEADER_P psInfo )
{
    TgRSIZE                             nbyReserved, nbyAllocated, uiValue, uiUpdate;

    uiValue = atomic_fetch_add( s_anuiStat_Allocations + enAllocator, 1 ) + 1;
    if (uiValue > (uiUpdate = atomic_load( s_anuiStat_Max_Allocations + enAllocator )))
    {
        while (!atomic_compare_exchange_strong( s_anuiStat_Max_Allocations + enAllocator, &uiUpdate, uiValue) && (uiValue > uiUpdate));
    };

    nbyReserved = psInfo->m_bReserved ? psInfo->m_uiSize : 0;
    nbyAllocated = psInfo->m_bReserved ? 0 : psInfo->m_uiSize;

    uiValue = atomic_fetch_add( s_auiStat_Reserved + enAllocator, nbyReserved ) + nbyReserved;
    if (uiValue > (uiUpdate = atomic_load( s_auiStat_Max_Reserved + enAllocator )))
    {
        while (!atomic_compare_exchange_strong( s_auiStat_Max_Reserved + enAllocator, &uiUpdate, uiValue) && (uiValue > uiUpdate));
    };

    uiValue = atomic_fetch_add( s_auiStat_Allocated + enAllocator, nbyAllocated ) + nbyAllocated;
    if (uiValue > (uiUpdate = atomic_load( s_auiStat_Max_Allocated + enAllocator )))
    {
        while (!atomic_compare_exchange_strong( s_auiStat_Max_Allocated + enAllocator, &uiUpdate, uiValue) && (uiValue > uiUpdate));
    };
}
/*# TgS_STAT__COMMON */
#endif


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
static TgRESULT tgMM_OS__Size( TgUINT_F32_P pnbyReserve, TgUINT_F32_P pnbyAllocated, TgVOID_CPC pMem )
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
static TgRESULT tgMM_OS__Malloc( TgMEM_INFO_HEADER_P psInfo, TgVOID_PP ppReturn, TgRSIZE_C uiSize )
{
    TgMEM_OS_HEADER_P                   psMem_OS;

    /* Create an OS Allocation for this request */
    psMem_OS = (TgMEM_OS_HEADER_P)tgMM_PM_Virtual_Commit( nullptr, sizeof(TgMEM_OS_HEADER) + uiSize );
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

    psMem_OS = (TgMEM_OS_HEADER_P)tgMM_PM_Virtual_Commit( psMem_Reserve, sizeof( TgMEM_OS_HEADER ) );
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

    *psInfo = psMem_OS->m_sInfo_Header;
    *ppReturn = psMem_OS->m_auiData;

    tgCM_UT_LF__SN__Lock_Spin( &s_sOS_Spin_Lock.m_sLock );
    tgCM_UT_ST__LT__Push_Front( &s_sOS_List, &psMem_OS->m_sList_Header__Page );
    tgCM_UT_LF__SN__Signal( &s_sOS_Spin_Lock.m_sLock );

    return (KTgS_OK);
}


/* ---- tgMM_OS__Commit ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT tgMM_OS__Commit( TgMEM_INFO_HEADER_P psInfo, TgVOID_PP pMem, TgRSIZE_C uiSize )
{
    psInfo->m_uiSize = 0;

    if ((nullptr == *pMem) && TgFAILED(tgMM_OS__Reserve( psInfo, pMem, uiSize )))
    {
        return (KTgE_FAIL);
    };

    /* Cannot clear the memory of a commit since it may overlap existing committed memory */
    if (nullptr == tgMM_PM_Virtual_Commit( *pMem, uiSize ))
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

    tgCM_UT_ST__LT__Remove( &uMem.psMem_OS->m_sList_Header__Page );

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


/* ---- tgMM_Pool__Size ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT tgMM_Pool__Size( TgUINT_F32_P pnbyReserve, TgUINT_F32_P pnbyAllocated, TgVOID_CPC pMem )
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
static TgRESULT tgMM_Pool__Malloc( TgMEM_INFO_HEADER_P psInfo, TgVOID_PP ppReturn, TgRSIZE_C uiSize )
{
    TgRSIZE                             uiBitPool, uiSize_Align, uiPool_MSD, uiPool_LSD, uiIndex_Pool;
    union
    {
        STg2_UT_ST__ST_Node_P               psStack_Header;
        TgVOID_P                            pVoid;
        TgMEM_PAGE_HEADER_P                 psMem_Page;
    }                                   uMem;
    TgUN_PTR                            uRet;
    TgUINT_E16                          uiFree, uiNext;

    if (uiSize > s_uiMaxBlock) /* Use the OS allocator (can always replace later) */
    {
        return (tgMM_OS__Malloc( psInfo, ppReturn, uiSize ));
    };

    /* Retrieve a Block of Memory from the corresponding pool */

    uiBitPool = (TgRSIZE)tgPM_BSR_UMAX( uiSize | KTgMIN_BLOCK_SIZE ); /* Guaranteed to be at least 4 */
    uiSize_Align = tgCM_CEL_ALGN_PW2_UMAX( uiSize, ((TgRSIZE)1 << (uiBitPool - 2)) );
    uiBitPool = (TgRSIZE)tgPM_BSR_UMAX( uiSize_Align | KTgMIN_BLOCK_SIZE );
    uiSize_Align = tgCM_CEL_ALGN_PW2_UMAX( uiSize, ((TgRSIZE)1 << (uiBitPool - 2)) );

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
            TgRSIZE                             uiBlock_Size, uiBlock_End;

            /* If still null then allocate a new page */
            uMem.pVoid = tgMM_PM_Virtual_Commit( nullptr, s_uiPageSize );
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
            uMem.psMem_Page->m_uiState = ETgMM_PAGE_STATE_OPENED;

            uiBlock_Size = (1 << (uiBitPool)) + (TgUINT_F32)uiPool_LSD*(1 << (uiBitPool - 2));
            uiBlock_End = (s_uiPageSize - sizeof(TgMEM_PAGE_HEADER)) / uiBlock_Size;
            TgCRITICAL(uiBlock_End < KTgMAX_U16);

            uMem.psMem_Page->m_uiBlock_End = (TgUINT_E16)(uiBlock_End & KTgMAX_U16);
            uMem.psMem_Page->m_uiBlock_Last = 0;
            atomic_store( &uMem.psMem_Page->m_uiBlock_Free, KTgMAX_U16 );
            TgVERIFY(uiBlock_Size < KTgMAX_U16);
            uMem.psMem_Page->m_uiBlock_Size = (TgUINT_E16)(uiBlock_Size & KTgMAX_U16);

            tls_apsPage_Open[uiIndex_Pool] = uMem.psMem_Page;
        };

        tgCM_UT_LF__SN__Lock_Spin( &s_sPage_Cache_Spin_Lock.m_sLock );
        tgCM_UT_ST__LT__Push_Front( &s_sPage_Cache, &uMem.psMem_Page->m_sList_Header );
        tgCM_UT_LF__SN__Signal( &s_sPage_Cache_Spin_Lock.m_sLock );
    };

    TgVERIFY(uMem.psMem_Page->m_uiState == ETgMM_PAGE_STATE_OPENED || uMem.psMem_Page->m_uiState == ETgMM_PAGE_STATE_REOPENED)
    TgCRITICAL( uMem.psMem_Page->m_uiBlock_Size >= uiSize );

    /* At this point we have a thread local pointer to a global memory structure (the memory page). Allocations that were made from this page could be freed at any point of time
       on other threads. Therefore, any fields that may be modified by the free routine need to be treated with standard multi-threaded precautions. However, those that are used
       only during allocation can be treated as being thread local (single thread safe). We can safely assume that this thread is the only thread allocating memory. */


    tgCM_UT_LF__RW__Enter_Read_Wait_Yield( &s_rwPage_Stat_Lock.m_sLock );

    uiFree = atomic_load( &uMem.psMem_Page->m_uiBlock_Free );
    uRet.m_uiPTR = 0;
    while (uiFree != KTgMAX_U16)
    {
        uRet.m_puiE08 = uMem.psMem_Page->m_auiData;
        uRet.m_uiPTR += uiFree * uMem.psMem_Page->m_uiBlock_Size;
        uiNext = *uRet.m_puiE16;
        if (atomic_compare_exchange_strong( &uMem.psMem_Page->m_uiBlock_Free, &uiFree, uiNext ))
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
        if (KTgMAX_U16 == atomic_load( &uMem.psMem_Page->m_uiBlock_Free ))
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

    if (uMem.psMem_Page->m_uiBlock_Size > (TgUINT_F32)s_uiMaxBlock)
    {
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

        tgCM_UT_LF__RW__Enter_Read_Wait_Yield( &s_rwPage_Stat_Lock.m_sLock );

        /* Add the block to the free list */
        tgCM_UT_LF__SN__Lock_Spin( &s_asPage_Spin_Lock[uiIndex_Pool].m_sLock );
        uiFree = atomic_load( &uMem.psMem_Page->m_uiBlock_Free );
        uFree.m_pVoid = pMem;
        do
        {
            *uFree.m_puiE16 = uiFree;
        }
        while (!atomic_compare_exchange_strong( &uMem.psMem_Page->m_uiBlock_Free, &uiFree, uiBlock_Index ));

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
            tgCM_UT_LF__ST__Push( &s_asPage_Open[uiIndex_Pool].m_sStack, &uMem.psMem_Page->m_sStack_Header );
        };
        tgCM_UT_LF__SN__Signal( &s_asPage_Spin_Lock[uiIndex_Pool].m_sLock );

        tgCM_UT_LF__RW__Exit_Read( &s_rwPage_Stat_Lock.m_sLock );
    };
    
    return (KTgS_OK);
}


/* ---- tgMM_Pool__Realloc ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT tgMM_Pool__Realloc( TgMEM_INFO_HEADER_P psNew_Info, TgVOID_PP ppNew, TgMEM_INFO_HEADER_P psOld_Info, TgVOID_PC pOld, TgRSIZE_C uiNewSize )
{
    union
    {
        TgUINT_PTR                          uiPTR;
        STg2_UT_ST__ST_Node_P               psStack_Header;
        TgVOID_P                            pVoid;
        TgMEM_PAGE_HEADER_P                 psMem_Page;
    }                                   uPage;

    if (nullptr == pOld)
    {
        return (KTgE_FAIL);
    };

    uPage.uiPTR = tgCM_FLR_ALGN_PW2_UMAX( (TgUINT_PTR)pOld, s_uiPageSize );
    TgVERIFY(uPage.uiPTR == tgCM_CEL_ALGN_PW2_UMAX( (TgUINT_PTR)pOld, s_uiPageSize ) - s_uiPageSize);
    psOld_Info->m_uiFlags = uPage.psMem_Page->m_sInfo_Header.m_uiFlags;
    psOld_Info->m_uiSize = uPage.psMem_Page->m_uiBlock_Size;

    if (uPage.psMem_Page->m_uiBlock_Size >= uiNewSize)
    {
        psNew_Info->m_uiFlags = uPage.psMem_Page->m_sInfo_Header.m_uiFlags;
        psNew_Info->m_uiSize = uPage.psMem_Page->m_uiBlock_Size;
        *ppNew = pOld;
        return (KTgS_OK);
    };

    /* Allocate the New Size, and copy the data from the old Allocation to the new Allocation */

    if (TgFAILED(tgMM_Pool__Malloc( psNew_Info, ppNew, uiNewSize )))
    {
        return (KTgE_FAIL);
    };

    tgMM_Copy( *ppNew, uiNewSize, pOld, uPage.psMem_Page->m_uiBlock_Size );

    tgMM_Pool__Free( psOld_Info, pOld );

    return (KTgS_OK);
}


/* ---- tgMM_Pool__Stats --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if TgS_STAT__COMMON
TgVOID tgMM_Pool__Stats( STg2_Output_PC psOUT )
{
    for (TgRSIZE uiIndex = 0; uiIndex < KTgMAX_POOLS; ++uiIndex)
    {
        TgRSIZE                             uiBlockSize, uiTotalSize, nuiAlloc;

        tgMM_Pool__Stats_Pool( uiIndex, &uiBlockSize, &uiTotalSize, &nuiAlloc );
        tgIO_PrintF( psOUT, u8"Pool(% 8d)               % 8d    % 8d\n", uiBlockSize, uiTotalSize, nuiAlloc );
    };
}
/*# TgS_STAT__COMMON */
#endif


/* ---- tgMM_Pool_Stats ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if TgS_STAT__COMMON
TgVOID tgMM_Pool__Stats_Pool( TgRSIZE_C uiPoolIndex, TgRSIZE_P puiBlock_Size, TgRSIZE_P puiTotal_Size, TgRSIZE_P pnuiAlloc )
{
    TgUINT_F32                          nuiAlloc, uiBlock_Size, uiBitPool, uiPool_MSD, uiPool_LSD;
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

    tgCM_UT_LF__RW__Enter_Write_Wait_Yield( &s_rwPage_Stat_Lock.m_sLock );

    sStack_Top = atomic_load( &s_asPage_Open[uiPoolIndex].m_sStack.m_sTop );
    uPage.psStack_Header = sStack_Top.m_pHead;

    for (; nullptr != uPage.psMem_Page; uPage.pVoid = uPage.psMem_Page->m_sStack_Header.m_pNext_Node)
    {

        TgERROR(uiBlock_Size == uPage.psMem_Page->m_uiBlock_Size);

        nuiAlloc += uPage.psMem_Page->m_uiBlock_Last;

        uiFree = atomic_load( &uPage.psMem_Page->m_uiBlock_Free );
        while (KTgMAX_U16 != uiFree)
        {
            TgUN_POINTER                        sUnion;

            sUnion.m_pui08 = uPage.psMem_Page->m_auiData + uiFree * uiBlock_Size;
            uiFree = *(sUnion.m_puiE16);
            --nuiAlloc;
        };
    };

    uPage.psList_Header = s_asPage_Closed[uiPoolIndex].m_sNode.m_pNext_Node;
    while (uPage.psList_Header != &s_asPage_Closed[uiPoolIndex].m_sNode)
    {
        TgERROR(uiBlock_Size == uPage.psMem_Page->m_uiBlock_Size);
        nuiAlloc += uPage.psMem_Page->m_uiBlock_End;
        uPage.psList_Header = uPage.psList_Header->m_pNext_Node;
    };

    tgCM_UT_LF__SN__Lock_Spin( &s_sPage_Cache_Spin_Lock.m_sLock );
    uPage.psList_Header = s_sPage_Cache.m_sNode.m_pNext_Node;
    while (uPage.psList_Header != &s_sPage_Cache.m_sNode)
    {
        if (uiBlock_Size != uPage.psMem_Page->m_uiBlock_Size)
        {
            continue;
        };

        nuiAlloc += uPage.psMem_Page->m_uiBlock_Last;

        uiFree = atomic_load( &uPage.psMem_Page->m_uiBlock_Free );
        while (KTgMAX_U16 != uiFree)
        {
            TgUN_POINTER                        sUnion;

            sUnion.m_pui08 = uPage.psMem_Page->m_auiData + uiFree * uiBlock_Size;
            uiFree = *(sUnion.m_puiE16);
            --nuiAlloc;
        };
        uPage.psList_Header = uPage.psList_Header->m_pNext_Node;
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

    if ((0 == psMem_Page->m_uiBlock_Last) && (KTgMAX_U16 == atomic_load( &psMem_Page->m_uiBlock_Free )))
    {
        return (true);
    };

    /* Count the number of free blocks */
    nuiFree = 0;
    for (TgUINT_E16 uiFree = atomic_load( &psMem_Page->m_uiBlock_Free ); (KTgMAX_U16 != uiFree); ++nuiFree)
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

        for (uiFree = atomic_load( &psMem_Page->m_uiBlock_Free ); (KTgMAX_U16 != uiFree) && (uiFree != uiCheck);)
        {
            sUnion.m_pui08 = psMem_Page->m_auiData;
            sUnion.m_uiPTR += uiFree * psMem_Page->m_uiBlock_Size;
            uiFree = *(sUnion.m_puiE16);
        };

        if (uiFree == uiCheck)
        {
            continue;
        };

        TgLOG_MEM( u8"Unfreed Memory Allocation at (% 16p).\n", u8"Common", u8"MM_Free_MGR", sUnion.m_pVoid );
    };

    return (false);
}
