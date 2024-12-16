/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Mem MGR.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/** @note Memory Pools: A pool is created for each power of 2 greater than 8, and for the 3 most significant binary values after them (i.e. 10000, 10100, 11000, 11100) - up to
    MAXPOOL count. If the OS Page_Size is less than the normal MaxAlloc size number of pools and MaxAlloc are correspondingly modified so that MaxAlloc matches Page_Size. The
    reason for this is to reduce internal fragmentation and because no time savings would be incurred. */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

#if !defined(TgBUILD_FEATURE__MALLOC_OVERRIDE)
#include "TgS Common - Preload - Internal.h"
#endif


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Types                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#if defined(TgCOMPILE__MEM_TRACK)
TgTYPE_STRUCT(TgTRACE_ENTRY,)
{
    TgCHAR_U8_CP                                m_uszFile;
    TgRSIZE                                     m_uiReserve;
    TgRSIZE                                     m_uiCommit;
    TgUINT_E32                                  m_uiLine;
    ETgMM_ALLOCATOR                             m_enAllocator;
    TgCHAR_U8                                   m_uszComment[24];
};
TgCOMPILER_ASSERT(56 == sizeof(TgTRACE_ENTRY),);
/*# defined(TgCOMPILE__MEM_TRACK) */
#endif


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* Memory Manager */

#if defined(TgCOMPILE__MEM_TRACK)

static TgVOID
tgMM_Print_Trace_Header(
    STg2_Output_PC psOUT );

static TgVOID
tgMM_Print_Trace_Entry(
    STg2_Output_PC, TgUINT_E08_CPC );

static TgUINT_PTR
tgMM_Hash_Trace_Entry(
    TgUINT_PTR_C );

/*# defined(TgCOMPILE__MEM_TRACK) */
#endif


/** @note To make life simple - the allocation granularity and the page granularity are assumed to be the same.  Thus, on the X360 all allocations are made using the large memory
    page size option (64K pages). */

static ETgMODULE_STATE                      s_enMem_MGR_State = ETgMODULE_STATE__FREED;

#if defined(TgCOMPILE__MEM_TRACK)
static STg2_UT_LF__HT_RW                    s_sTrace_Table;
static TgUINT_E08                           s_sTrace_Table_Buffer[1024*1024];
/*# defined(TgCOMPILE__MEM_TRACK) */
#endif




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgMM_Init_MGR ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgMM_Init_MGR( TgVOID )
{
    #if !defined(TgBUILD_FEATURE__MALLOC_OVERRIDE)
    tgMM_Init_MGR_Preload();
    #endif

    TgERROR(ETgMODULE_STATE__FREED == s_enMem_MGR_State);
    s_enMem_MGR_State = ETgMODULE_STATE__INITIALIZING;

#if defined(TgCOMPILE__MEM_TRACK)
    TgVERIFY(KTgS_OK == tgCM_UT_LF__HT_RW__Init_Fixed( &s_sTrace_Table, sizeof( TgTRACE_ENTRY ), 4096, sizeof( s_sTrace_Table_Buffer ), s_sTrace_Table_Buffer ));
/*# defined(TgCOMPILE__MEM_TRACK) */
#endif

    s_enMem_MGR_State = ETgMODULE_STATE__BOOTED;

    return (KTgS_OK);
}


/* ---- tgMM_Boot_MGR ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgMM_Boot_MGR( TgVOID )
{
#if TgCOMPILE__CONSOLE
    tgMM_Set_CN_PrintF( tgCN_PrintF );

    if (tgGB_CMD_Query_Argument_Index( u8"-//stat/boot/memory" ) >= 0)
    {
        tgMM_Stats( &g_sOutCon );
    };
/*# TgCOMPILE__CONSOLE */
#endif

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

    TgERROR(ETgMODULE_STATE__BOOTED == s_enMem_MGR_State);
    s_enMem_MGR_State = ETgMODULE_STATE__FREEING;

#if TgCOMPILE__CONSOLE
    if (tgGB_CMD_Query_Argument_Index( u8"-//stat/free/memory" ) >= 0)
    {
        tgMM_Stats( &g_sOutCon );
    };

    tgMM_Set_CN_PrintF( nullptr );
/*# TgCOMPILE__CONSOLE */
#endif

#if defined(TgCOMPILE__MEM_TRACK)
    if (s_sTrace_Table.m_nuiNode_Active)
    {
        tgMM_Print_Trace_Header( &g_sOutCon );
        tgCM_UT_LF__HT_RW__Output_List( &s_sTrace_Table, &g_sOutCon, tgMM_Print_Trace_Entry );
        tgIO_PrintF( &g_sOutCon, u8"\n" );
    };
    tgCM_UT_LF__HT_RW__Free( &s_sTrace_Table );
/*# defined(TgCOMPILE__MEM_TRACK) */
#endif

    s_enMem_MGR_State = ETgMODULE_STATE__FREED;

    #if !defined(TgBUILD_FEATURE__MALLOC_OVERRIDE)
    tgMM_Free_MGR_Preload();
    #endif

    return (KTgS_OK);
}


/* ---- tgMM_Update_MGR ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgMM_Update_MGR( TgATTRIBUTE_UNUSED TgFLOAT32_C fDT )
{
    return (KTgS_OK);
}


/* ---- tgMM_Query_Fixed_Memory -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRSIZE tgMM_Query_Fixed_Memory( TgVOID )
{
    return (   tgMM_Query_Fixed_Memory_Preload()
             + sizeof( s_enMem_MGR_State )

        #if defined(TgCOMPILE__MEM_TRACK)
             + sizeof( s_sTrace_Table )
             + sizeof( s_sTrace_Table_Buffer )
        /*# defined(TgCOMPILE__MEM_TRACK) */
        #endif
    );
}


/* ---- tgMM_Stats --------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if TgS_STAT__COMMON
TgVOID tgMM_Stats( STg2_Output_PC psOUT )
{
    STg2_MM_Preload_Stats               sMM_Stats;
    TgCHAR_U8                           mbzCol[6][32];
    TgRSIZE                             uiIndex;

    TgERROR(nullptr != psOUT);

    /* Retrieve the stats from the low level memory manager (preload). */
    if (TgFAILED(tgMM_Query_Stats( &sMM_Stats )))
    {
        return;
    }

    tgIO_PrintF( psOUT, u8"\n");
    tgIO_PrintF( psOUT, u8"*******************************************************************************************************************************\n");
    tgIO_PrintF( psOUT, u8"                                                      MEMORY MANAGER STATS                                                     \n");
    tgIO_PrintF( psOUT, u8"*******************************************************************************************************************************\n");
    tgIO_PrintF( psOUT, u8"\n");

    tgIO_PrintF( psOUT, u8"%8.8s %16.16s %16.16s %16.16s %16.16s %16.16s %16.16s\n",
                 u8"", u8"  Allocations  ", u8"      Max      ", u8"   Allocated   ", u8"      Max      ", u8"    Reserve    ", u8"      Max      " );
    tgIO_PrintF( psOUT, u8"%8.8s %16.16s %16.16s %16.16s %16.16s %16.16s %16.16s\n",
                 u8"", u8"---------------", u8"---------------", u8"---------------", u8"---------------", u8"---------------", u8"---------------" );

    for (uiIndex = 0; uiIndex < ETgMM_ALLOCATOR_COUNT; ++uiIndex)
    {
        tgUSZ_Formatted_From_U64( mbzCol[0], sizeof( mbzCol[0] ), sMM_Stats.m_anuiStat_Allocations[uiIndex] );
        tgUSZ_Formatted_From_U64( mbzCol[1], sizeof( mbzCol[1] ), sMM_Stats.m_anuiStat_Max_Allocations[uiIndex] );
        tgUSZ_Formatted_From_U64( mbzCol[2], sizeof( mbzCol[2] ), sMM_Stats.m_auiStat_Allocated[uiIndex] );
        tgUSZ_Formatted_From_U64( mbzCol[3], sizeof( mbzCol[3] ), sMM_Stats.m_auiStat_Max_Allocated[uiIndex] );
        tgUSZ_Formatted_From_U64( mbzCol[4], sizeof( mbzCol[4] ), sMM_Stats.m_auiStat_Reserved[uiIndex] );
        tgUSZ_Formatted_From_U64( mbzCol[5], sizeof( mbzCol[5] ), sMM_Stats.m_auiStat_Max_Reserved[uiIndex] );

        tgIO_PrintF( psOUT, u8"%8.8s %16.16s %16.16s %16.16s %16.16s %16.16s %16.16s\n",
                     sMM_Stats.m_ambzStat_Name[uiIndex], mbzCol[0], mbzCol[1], mbzCol[2], mbzCol[3], mbzCol[4], mbzCol[5] );
    };

    tgIO_PrintF( psOUT, u8"\n" );

#if defined(TgCOMPILE__MEM_TRACK)
    tgIO_PrintF( psOUT, u8"ALLOCATION LIST:\n" );
    tgMM_Print_Trace_Header( psOUT );
    tgCM_UT_LF__HT_RW__Output_List( &s_sTrace_Table, psOUT, tgMM_Print_Trace_Entry );
    tgIO_PrintF( psOUT, u8"\n" );
/*# defined(TgCOMPILE__MEM_TRACK) */

    tgMM_Stats_Allocator( tgIO_PrintF, psOUT );
#endif
}
/*# TgS_STAT__COMMON */
#endif



/* ---- tgMM_Malloc_With_Trace_Comment ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if defined(TgCOMPILE__MEM_TRACK)
TgVOID_P tgMM_Malloc_With_Trace_Comment( ETgMM_ALLOCATOR_C enAllocator, TgRSIZE_C uiSize, TgRSIZE_C uiAlignment, TgCHAR_U8_CPC uszFile, TgUINT_E32_C uiL, TgCHAR_U8_CPC uszComment )
{
    TgVOID_P                            pReturn;
    TgTRACE_ENTRY                       sTrace;
    TgUN_PTR                            sHash;

    (void)uszComment;
    pReturn = tgMM_Malloc( enAllocator, uiSize, uiAlignment );

    sTrace.m_uszFile = uszFile;
    sTrace.m_uiReserve = uiSize;
    sTrace.m_uiCommit = uiSize;
    sTrace.m_uiLine = uiL;
    sTrace.m_enAllocator = enAllocator;
    tgMM_Copy( sTrace.m_uszComment, sizeof(sTrace.m_uszComment), uszComment, KTgMAX_RSIZE );

    sHash.m_pVoid = pReturn;

    TgVERIFY(KTgS_OK == tgCM_UT_LF__HT_RW__Insert_Spin( &s_sTrace_Table, tgMM_Hash_Trace_Entry( sHash.m_uiPTR ), &sTrace ));

    TgLOG_MEM( u8"Address: % 16p Size: % 16X File: % 128.128s Line % 5d\n", pReturn, uiSize, uszFile, uiL );
    return (pReturn);
}
/*# defined(TgCOMPILE__MEM_TRACK) */
#endif


/* ---- tgMM_Malloc_With_Trace --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if defined(TgCOMPILE__MEM_TRACK)
TgVOID_P tgMM_Malloc_With_Trace( ETgMM_ALLOCATOR_C enAllocator, TgRSIZE_C uiSize, TgRSIZE_C uiAlignment, TgCHAR_U8_CPC uszFile, TgUINT_E32_C uiL )
{
    TgVOID_P                            pReturn;
    TgTRACE_ENTRY                       sTrace;
    TgUN_PTR                            sHash;

    pReturn = tgMM_Malloc( enAllocator, uiSize, uiAlignment );
 
    sTrace.m_uszFile = uszFile;
    sTrace.m_uiReserve = uiSize;
    sTrace.m_uiCommit = uiSize;
    sTrace.m_uiLine = uiL;
    sTrace.m_enAllocator = enAllocator;
    sTrace.m_uszComment[0] = 0;

    sHash.m_pVoid = pReturn;

    TgVERIFY(KTgS_OK == tgCM_UT_LF__HT_RW__Insert_Spin( &s_sTrace_Table, tgMM_Hash_Trace_Entry( sHash.m_uiPTR ), &sTrace ));

    TgLOG_MEM( u8"Address: % 16p Size: % 16X File: % 128.128s Line % 5d\n", pReturn, uiSize, uszFile, uiL );
    return (pReturn);
}
/*# defined(TgCOMPILE__MEM_TRACK) */
#endif


/* ---- tgMM_Reserve_With_Trace -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if defined(TgCOMPILE__MEM_TRACK)
TgVOID_P tgMM_Reserve_With_Trace( ETgMM_ALLOCATOR_C enAllocator, TgRSIZE_C uiSize, TgCHAR_U8_CPC uszFile, TgUINT_E32_C uiL )
{
    TgVOID_P                            pReturn;
    TgTRACE_ENTRY                       sTrace;
    TgUN_PTR                            sHash;

    pReturn = tgMM_Reserve( enAllocator, uiSize );

    sTrace.m_uszFile = uszFile;
    sTrace.m_uiReserve = uiSize;
    sTrace.m_uiCommit = 0;
    sTrace.m_uiLine = uiL;
    sTrace.m_enAllocator = enAllocator;
    sTrace.m_uszComment[0] = 0;

    sHash.m_pVoid = pReturn;

    TgVERIFY(KTgS_OK == tgCM_UT_LF__HT_RW__Insert_Spin( &s_sTrace_Table, tgMM_Hash_Trace_Entry( sHash.m_uiPTR ), &sTrace ));

    TgLOG_MEM( u8"Address: % 16p Size: % 16X File: % 128.128s Line % 5d\n", pReturn, uiSize, uszFile, uiL );
    return (pReturn);
}
/*# defined(TgCOMPILE__MEM_TRACK) */
#endif


/* ---- tgMM_Commit_With_Trace --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if defined(TgCOMPILE__MEM_TRACK)
TgVOID_P tgMM_Commit_With_Trace( ETgMM_ALLOCATOR_C enAllocator, TgVOID_PC pMem, TgRSIZE_C uiOffset, TgRSIZE_C uiSize, TgCHAR_U8_CPC uszFile, TgUINT_E32_C uiL )
{
    TgVOID_P                            pReturn;

    pReturn = tgMM_Commit( enAllocator, pMem, uiOffset, uiSize );

    if (nullptr == pMem && nullptr != pReturn)
    {
        TgTRACE_ENTRY                       sTrace;
        TgUN_PTR                            sHash;

        sTrace.m_uszFile = uszFile;
        sTrace.m_uiReserve = uiSize;
        sTrace.m_uiCommit = uiSize;
        sTrace.m_uiLine = uiL;
        sTrace.m_enAllocator = enAllocator;
        sTrace.m_uszComment[0] = 0;

        sHash.m_pVoid = pReturn;

        /* Commit acts as a general allocator when there is no existing reserve space that is passed into the function. */
        TgVERIFY(KTgS_OK == tgCM_UT_LF__HT_RW__Insert_Spin( &s_sTrace_Table, tgMM_Hash_Trace_Entry( sHash.m_uiPTR ), &sTrace ));
    }
    else if (nullptr != pMem && nullptr != pReturn)
    {
        TgTRACE_ENTRY                       sTrace;
        TgUN_PTR                            sHash;

        sHash.m_pVoid = pMem;
        TgVERIFY(KTgS_OK == tgCM_UT_LF__HT_RW__Find_Spin( &sTrace, &s_sTrace_Table, tgMM_Hash_Trace_Entry( sHash.m_uiPTR ) ));

        sTrace.m_uszFile = uszFile;
        sTrace.m_uiCommit = sTrace.m_uiCommit > uiSize? sTrace.m_uiCommit : uiSize;
        sTrace.m_uiLine = uiL;

        /* It is "hard" to accurately measure the commit size in a region (without doing a page walk). */
        TgVERIFY(KTgS_OK == tgCM_UT_LF__HT_RW__Update_Spin( &s_sTrace_Table, tgMM_Hash_Trace_Entry( sHash.m_uiPTR ), &sTrace ));
    }

    TgLOG_MEM( u8"Address: % 16p Size: % 16X File: % 128.128s Line % 5d\n", pReturn, uiSize, uszFile, uiL );
    return (pReturn);
}
/*# defined(TgCOMPILE__MEM_TRACK) */
#endif


/* ---- tgMM_Free_With_Trace ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if defined(TgCOMPILE__MEM_TRACK)
TgVOID tgMM_Free_With_Trace( ETgMM_ALLOCATOR_C enAllocator, TgVOID_PC pMem, TgATTRIBUTE_UNUSED TgCHAR_U8_CPC uszFile, TgATTRIBUTE_UNUSED TgUINT_E32_C uiL )
{
    TgUN_PTR                            sHash;

    tgMM_Free( enAllocator, pMem );
    sHash.m_pVoid = pMem;
    TgVERIFY(KTgS_OK == tgCM_UT_LF__HT_RW__Remove_Spin( &s_sTrace_Table, tgMM_Hash_Trace_Entry( sHash.m_uiPTR )));
}
/*# defined(TgCOMPILE__MEM_TRACK) */
#endif


/* ---- tgMM_Realloc_With_Trace -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if defined(TgCOMPILE__MEM_TRACK)
TgVOID_P tgMM_Realloc_With_Trace( ETgMM_ALLOCATOR_C enAllocator, TgVOID_PC pMem, TgRSIZE_C uiSize, TgRSIZE_C uiAlignment, TgCHAR_U8_CPC uszFile, TgUINT_E32_C uiL )
{
    TgVOID_P                            pReturn;

    if (nullptr == pMem)
    {
        return (tgMM_Malloc_With_Trace( enAllocator, uiSize, uiAlignment, uszFile, uiL ));
    };

    pReturn = tgMM_Realloc( enAllocator, pMem, uiSize, uiAlignment );

    if (pReturn != pMem)
    {
        TgTRACE_ENTRY                       sTrace;
        TgUN_PTR                            sHash;

        sTrace.m_uszFile = uszFile;
        sTrace.m_uiReserve = uiSize;
        sTrace.m_uiCommit = uiSize;
        sTrace.m_uiLine = uiL;
        sTrace.m_enAllocator = enAllocator;
        sTrace.m_uszComment[0] = 0;

        sHash.m_pVoid = pReturn;
        if (pReturn == pMem)
        {
            TgVERIFY(KTgS_OK == tgCM_UT_LF__HT_RW__Update_Spin( &s_sTrace_Table, tgMM_Hash_Trace_Entry( sHash.m_uiPTR ), &sTrace ));
        }
        else
        {
            TgVERIFY(KTgS_OK == tgCM_UT_LF__HT_RW__Insert_Spin( &s_sTrace_Table, tgMM_Hash_Trace_Entry( sHash.m_uiPTR ), &sTrace ));
            sHash.m_pVoid = pMem;
            TgVERIFY(KTgS_OK == tgCM_UT_LF__HT_RW__Remove_Spin( &s_sTrace_Table, tgMM_Hash_Trace_Entry( sHash.m_uiPTR ) ));
        }
    }

    TgLOG_MEM( u8"Address: % 16p Size: % 16X File: % 128.128s Line % 5d\n", pReturn, uiSize, uszFile, uiL );
    return (pReturn);
}
/*# defined(TgCOMPILE__MEM_TRACK) */
#endif




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#if defined(TgCOMPILE__MEM_TRACK)
/* ---- tgMM_Print_Trace_Header -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgMM_Print_Trace_Header( STg2_Output_PC psOUT )
{
    tgIO_PrintF( psOUT, u8"%75.75s %24.24s %8.8s %16.16s\n",
        u8"                                    File                                   ", u8"         Comment        ", u8"  Line  ", u8"      Size      " );
    tgIO_PrintF( psOUT, u8"%75.75s %24.24s %8.8s %16.16s\n",
        u8"---------------------------------------------------------------------------", u8"------------------------", u8"--------", u8"----------------" );
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
    TgRSIZE                             nuiLength;
    TgCHAR_U8_CP                        puszStart, puszLast;

    TgERROR(nullptr != psOUT);
    uMem.puiE08 = puiData;

    tgUSZ_Formatted_From_U64( mbzCol[0], sizeof( mbzCol[0] ), (TgUINT_E64)uMem.psEntry->m_uiLine );
    tgUSZ_Formatted_From_U64( mbzCol[1], sizeof( mbzCol[1] ), (TgUINT_E64)uMem.psEntry->m_uiCommit );
    tgUSZ_Length_Count( &nuiLength, uMem.psEntry->m_uszFile, KTgMAX_RSIZE );
    tgUSZ_Query_Region( &puszStart, &puszLast, uMem.psEntry->m_uszFile, KTgMAX_RSIZE, nuiLength >= 75 ? nuiLength - 75 : 0, 75 );
    tgIO_PrintF( psOUT, u8"%75.75s %24.24s %8.8s %16.16s\n", puszStart, uMem.psEntry->m_uszComment, mbzCol[0], mbzCol[1] );
}
/*# defined(TgCOMPILE__MEM_TRACK) */
#endif


#if defined(TgCOMPILE__MEM_TRACK)
/* ---- tgMM_Print_Trace_Entry --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgUINT_PTR tgMM_Hash_Trace_Entry( TgUINT_PTR_C uiValue )
{
    return (uiValue >> 16) | (uiValue << 48);
}
/*# defined(TgCOMPILE__MEM_TRACK) */
#endif
