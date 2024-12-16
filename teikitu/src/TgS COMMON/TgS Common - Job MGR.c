/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Job MGR.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Data                                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TgCN_VAR_ID                                 g_tiCVAR_Job_MGR_Enabled;
TgJOB_QUEUE_ID                              g_tiJob_Queue__OS;

#define DEBUG_STg2_Job_Queue                0




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Type */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TgTYPE_STRUCT(STg2_Job_Thread,)
{
    TgJOB_THREAD_ID TgALIGN(16)                 m_tiThread_NoSingleton; /**< Management of the thread pool is under a lock */
    TgTHREAD_ID                                 m_tiOS_Thread;
    TgSINT_F32_A                                m_iEnabled;
    TgSINT_F32                                  m_iPad0;
    TgJOB_QUEUE_ID                              m_atiQueue[KTgMAX_NUM_QUEUE+1];
};


TgTYPE_STRUCT(STg2_Job_Queue,)
{
    STg2_UT_LF_ISO__ST                          m_sFree;
    STg2_UT_LF_ISO__SN_ID                       m_sLock_Queue_Execute;
    STg2_UT_LF_ISO__SN_ID                       m_sLock_Queue_Add;

    STg2_Job                                    m_asJob[KTgMAX_NUM_JOB];
    STg2_UT_ST__QU                              m_sQueue_Add;
    STg2_UT_ST__QU                              m_sQueue_Execute;
    TgJOB_QUEUE_ID_SINGLETON                    m_xtiQueue_Singleton; /**< Managing and Atomic identifier */
    TgSINT_F64_A                                m_xniQueued;
    TgRSIZE_A                                   m_xuiRef; /**< Number of threads that process this queue. */
    TgUINT_F08                                  m_uiPad0[8];
};




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

static TgBOOL                               tgJM_Is_Enabled( TgVOID );
static STg2_Job_P                           tgJM_Execute_Next_Job( TgJOB_QUEUE_ID );
static TgRESULT                             tgJM_Execute_Job( STg2_Job_P );

static ETgMODULE_STATE                      s_enJob_MGR_State = ETgMODULE_STATE__FREED;
static STg2_UT_LF_ISO__SN                   s_asLock_Job_Queue;
static STg2_Job_Queue                       s_asJob_Queue[KTgMAX_NUM_QUEUE];
static TgRSIZE_A                            s_xnuiJob_Queue;

#if TgCOMPILE__THREAD
static TgNOTHROW TgUINT_F32                 tgJM_Run_Job_Scheduler( TgUINT_PTR_C );
static STg2_UT_LF_ISO__SN                   s_asLock_Job_Thread;
static STg2_Job_Thread                      s_asJob_Thread[KTgMAX_NUM_THREAD];
static TgRSIZE_A                            s_xnuiJob_Thread;
/*# TgCOMPILE__THREAD */
#endif

TgCOMPILER_ASSERT( sizeof( STg2_Job_Queue ) * KTgMAX_NUM_QUEUE == sizeof( s_asJob_Queue ), 0 );
TgCOMPILER_ASSERT( sizeof( STg2_Job_Thread ) * KTgMAX_NUM_THREAD == sizeof( s_asJob_Thread ), 0 );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgJM_Init_MGR ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgJM_Init_MGR( TgVOID )
{
    TgJOB_QUEUE_ID_SINGLETON            xtiTest_Singleton;

    /* Verify the state of the system */
    TgERROR(ETgMODULE_STATE__FREED == s_enJob_MGR_State);
    s_enJob_MGR_State = ETgMODULE_STATE__INITIALIZING;

    tgJOB_QUEUE_ID_Init( &xtiTest_Singleton, 0 ); /* Warm the ID system specifically to invalidate 0, 0 */

    tgCM_UT_LF__SN__Init( &s_asLock_Job_Queue.m_sLock );
    tgMM_Set_U08_0x00( s_asJob_Queue, sizeof( s_asJob_Queue ) );
    atomic_store( &s_xnuiJob_Queue, 0 );

#if TgCOMPILE__THREAD
    tgCM_UT_LF__SN__Init( &s_asLock_Job_Thread.m_sLock );
    tgMM_Set_U08_0x00( s_asJob_Thread, sizeof( s_asJob_Thread ) );
    atomic_store( &s_xnuiJob_Thread, 0 );
/*# TgCOMPILE__THREAD */
#endif

    g_tiCVAR_Job_MGR_Enabled = tgCN_Var_Init_Bool( u8"Job_MGR_Enabled", KTgMAX_RSIZE, u8"When disabled, all jobs are executed immediately (no queuing)", KTgMAX_RSIZE, 0, true );

    atomic_thread_fence( cxx__memory_order_seq_cst );

    s_enJob_MGR_State = ETgMODULE_STATE__INITIALIZED;
    return (KTgS_OK);
}


/* ---- tgJM_Boot_MGR ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgJM_Boot_MGR( TgVOID )
{
    /* Verify the state of the system */
    TgERROR(ETgMODULE_STATE__INITIALIZED == s_enJob_MGR_State);
    s_enJob_MGR_State = ETgMODULE_STATE__BOOTING;

    /* Test for number of cores available to determine if job system should be shut down */

    /* Create the default OS queue used by low level systems */
    g_tiJob_Queue__OS = tgJM_Init_Job_Queue();
    if (g_tiJob_Queue__OS.m_uiKI == KTgID__INVALID_VALUE)
    {
        TgCRITICAL_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to init OS Job Queue." );
        s_enJob_MGR_State = ETgMODULE_STATE__INITIALIZED;
        return (KTgE_FAIL);
    }

    s_enJob_MGR_State = ETgMODULE_STATE__BOOTED;
    return (KTgS_OK);
}


/* ---- tgJM_Stop_MGR ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgJM_Stop_MGR( TgVOID )
{
    TgSINT_F32                          iIndex;

    if ((ETgMODULE_STATE__FREED == s_enJob_MGR_State) || (ETgMODULE_STATE__INITIALIZED == s_enJob_MGR_State))
    {
        return (KTgS_OK);
    };

    /* Verify the state of the system */
    TgERROR(ETgMODULE_STATE__BOOTED == s_enJob_MGR_State);
    s_enJob_MGR_State = ETgMODULE_STATE__STOPPING;

    atomic_thread_fence( cxx__memory_order_seq_cst );

    tgCM_UT_LF__SN__Lock_Spin( &s_asLock_Job_Queue.m_sLock );
    for (iIndex = 0; iIndex < KTgMAX_NUM_QUEUE; ++iIndex)
    {
        TgJOB_QUEUE_ID                      tiQueue_NoSingleton;
        
        if (!tgJOB_QUEUE_ID_Fetch_And_Is_Valid( &tiQueue_NoSingleton, &s_asJob_Queue[iIndex].m_xtiQueue_Singleton ))
            continue;
        tgJM_Stop_Job_Queue( tiQueue_NoSingleton, true );
    };
    tgCM_UT_LF__SN__Signal( &s_asLock_Job_Queue.m_sLock );

    atomic_thread_fence( cxx__memory_order_seq_cst );

    s_enJob_MGR_State = ETgMODULE_STATE__STOPPED;
    return (KTgS_OK);
}


/* ---- tgJM_Free_MGR ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgJM_Free_MGR( TgVOID )
{
    TgSINT_F32                          iIndex;

    if (ETgMODULE_STATE__FREED == s_enJob_MGR_State)
    {
        return (KTgS_OK);
    };

    /* Verify the state of the system */
    TgERROR((ETgMODULE_STATE__STOPPED == s_enJob_MGR_State) || (ETgMODULE_STATE__INITIALIZED == s_enJob_MGR_State));
    s_enJob_MGR_State = ETgMODULE_STATE__FREEING;

    atomic_thread_fence( cxx__memory_order_seq_cst );

    tgCM_UT_LF__SN__Lock_Spin( &s_asLock_Job_Queue.m_sLock );
    for (iIndex = 0; iIndex < KTgMAX_NUM_QUEUE; ++iIndex)
    {
        TgJOB_QUEUE_ID                      tiQueue_NoSingleton;
        
        if (!tgJOB_QUEUE_ID_Fetch_And_Is_Valid( &tiQueue_NoSingleton, &s_asJob_Queue[iIndex].m_xtiQueue_Singleton ))
            continue;
        tgJM_Free_Job_Queue( tiQueue_NoSingleton );
    };
    tgCM_UT_LF__SN__Signal( &s_asLock_Job_Queue.m_sLock );

    TgERROR(0 == atomic_load( &s_xnuiJob_Queue ));

#if TgCOMPILE__THREAD
    tgCM_UT_LF__SN__Lock_Yield( &s_asLock_Job_Thread.m_sLock );
    for (iIndex = 0; iIndex < KTgMAX_NUM_THREAD; ++iIndex)
    {
        if (s_asJob_Thread[iIndex].m_tiThread_NoSingleton.m_uiKI == KTgID__INVALID_VALUE)
            continue;
        atomic_store( &s_asJob_Thread[iIndex].m_iEnabled, 0 );
        tgTR_Close( s_asJob_Thread[iIndex].m_tiOS_Thread );
    };
    tgCM_UT_LF__SN__Free_Unsafe( &s_asLock_Job_Thread.m_sLock );
    TgERROR(0 == atomic_load( &s_xnuiJob_Thread ));
/*# TgCOMPILE__THREAD */
#endif
    
    tgCM_UT_LF__SN__Free_Unsafe( &s_asLock_Job_Queue.m_sLock );

    s_enJob_MGR_State = ETgMODULE_STATE__FREED;
    return (KTgS_OK);
}


/* ---- tgJM_Query_Init ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgJM_Query_Init( TgVOID )
{
    return (ETgMODULE_STATE__INITIALIZED <= s_enJob_MGR_State && s_enJob_MGR_State <= ETgMODULE_STATE__STOPPED);
}


/* ---- tgJM_Query_Boot ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgJM_Query_Boot( TgVOID )
{
    return (ETgMODULE_STATE__BOOTED == s_enJob_MGR_State);
}


/* ---- tgJM_Query_Fixed_Memory -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRSIZE tgJM_Query_Fixed_Memory( TgVOID )
{
    return (0
             + sizeof( s_enJob_MGR_State )
             + sizeof( s_asLock_Job_Queue )
             + sizeof( s_asJob_Queue )
             + sizeof( s_xnuiJob_Queue )
#if TgCOMPILE__THREAD
             + sizeof( s_asLock_Job_Thread )
             + sizeof( s_asJob_Thread )
             + sizeof( s_xnuiJob_Thread )
/*# TgCOMPILE__THREAD */
#endif
    );
}


/* ---- tgJM_Init_Job_Queue ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgJOB_QUEUE_ID tgJM_Init_Job_Queue( TgVOID )
{
    TgSINT_F32                          iIndex_Queue;
    TgSINT_F32                          iIndex_Job;
    TgJOB_QUEUE_ID                      tiQueue;

    tgCM_UT_LF__SN__Lock_Spin( &s_asLock_Job_Queue.m_sLock );

    if ((ETgMODULE_STATE__BOOTING != s_enJob_MGR_State) && (ETgMODULE_STATE__BOOTED != s_enJob_MGR_State))
    {
        tgCM_UT_LF__SN__Signal( &s_asLock_Job_Queue.m_sLock );
        return (KTgJOB_QUEUE_ID__INVALID);
    };

    /* TODO: Can make this faster by putting the queues onto a free stack. */
    /* Find an available slot for a new job thread */
    for (iIndex_Queue = 0; iIndex_Queue < KTgMAX_NUM_QUEUE; ++iIndex_Queue)
    {
        if (tgJOB_QUEUE_ID_Is_Equal_U64( &s_asJob_Queue[iIndex_Queue].m_xtiQueue_Singleton, KTgID__INVALID_VALUE ))
            break;
    };

    if (KTgMAX_NUM_QUEUE == iIndex_Queue)
    {
        TgCRITICAL_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Exceeded number of allowable job queues." );
        tgCM_UT_LF__SN__Signal( &s_asLock_Job_Queue.m_sLock );
        return (KTgJOB_QUEUE_ID__INVALID);
    };

    tiQueue = tgJOB_QUEUE_ID_Init( &s_asJob_Queue[iIndex_Queue].m_xtiQueue_Singleton, (TgUINT_F32)iIndex_Queue );

    tgCM_UT_LF__ST__Init( &s_asJob_Queue[iIndex_Queue].m_sFree.m_sStack );
    tgCM_UT_LF__SN_ID__Init( &s_asJob_Queue[iIndex_Queue].m_sLock_Queue_Execute.m_sLock, tiQueue.m_uiKI );
    tgCM_UT_LF__SN_ID__Init( &s_asJob_Queue[iIndex_Queue].m_sLock_Queue_Add.m_sLock, tiQueue.m_uiKI );
    tgCM_UT_ST__QU__Init( &s_asJob_Queue[iIndex_Queue].m_sQueue_Add );
    tgCM_UT_ST__QU__Init( &s_asJob_Queue[iIndex_Queue].m_sQueue_Execute );

    atomic_store( &s_asJob_Queue[iIndex_Queue].m_xniQueued, 0 );
    atomic_store( &s_asJob_Queue[iIndex_Queue].m_xuiRef, 0 );

    for (iIndex_Job = KTgMAX_NUM_JOB - 1; iIndex_Job >= 0; --iIndex_Job)
    {
        tgCM_UT_LF__ST__Push( &s_asJob_Queue[iIndex_Queue].m_sFree.m_sStack, &s_asJob_Queue[iIndex_Queue].m_asJob[iIndex_Job].m_sNode.m_sStack );
    };

    atomic_fetch_add( &s_xnuiJob_Queue, 1 );
    atomic_thread_fence( cxx__memory_order_seq_cst );
    tgCM_UT_LF__SN__Signal( &s_asLock_Job_Queue.m_sLock );
    return (tiQueue);
}


/* ---- tgJM_Stop_Job_Queue ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgJM_Stop_Job_Queue( TgJOB_QUEUE_ID tiQueue, TgBOOL_C bAbort )
{
    if(TgFAILED( tgCM_UT_LF__SN_ID__Invalidate_Index_Spin( &s_asJob_Queue[tiQueue.m_uiI].m_sLock_Queue_Execute.m_sLock, tiQueue.m_uiKI ) ))
    {
        return;
    };

    if(TgFAILED( tgCM_UT_LF__SN_ID__Invalidate_Index_Spin( &s_asJob_Queue[tiQueue.m_uiI].m_sLock_Queue_Add.m_sLock, tiQueue.m_uiKI ) ))
    {
        return;
    };

    tgCM_UT_ST__QU__Merge( &s_asJob_Queue[tiQueue.m_uiI].m_sQueue_Execute, &s_asJob_Queue[tiQueue.m_uiI].m_sQueue_Add );

    while (1)
    {
        union
        
        {
            STg2_UT_ST__QU_Node_P               psNode;
            STg2_Job_P                          psJob;
        }                                   sUnion;

        sUnion.psNode = tgCM_UT_ST__QU__Dequeue( &s_asJob_Queue[tiQueue.m_uiI].m_sQueue_Execute );
        if (nullptr == sUnion.psNode)
            break;

        if ((bAbort) && sUnion.psJob->m_pfnAbort)
        {
            sUnion.psJob->m_pfnAbort( sUnion.psJob );
        };

        if (sUnion.psJob->m_pxuiFinish)
        {
            atomic_fetch_sub( sUnion.psJob->m_pxuiFinish, 1 );
        };

        tgCM_UT_LF__ST__Push( &s_asJob_Queue[tiQueue.m_uiI].m_sFree.m_sStack, &sUnion.psJob->m_sNode.m_sStack );
    };
}


/* ---- tgJM_Free_Job_Queue ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgJM_Free_Job_Queue( TgJOB_QUEUE_ID tiQueue )
{
    TgERROR(tgCM_UT_ST__QU__Is_Empty( &s_asJob_Queue[tiQueue.m_uiI].m_sQueue_Execute ));
    TgERROR(tgCM_UT_ST__QU__Is_Empty( &s_asJob_Queue[tiQueue.m_uiI].m_sQueue_Add ));

    if (tiQueue.m_uiI >= KTgMAX_NUM_QUEUE)
        return;

    tgCM_UT_LF__ST__Free( &s_asJob_Queue[tiQueue.m_uiI].m_sFree.m_sStack );
    tgCM_UT_LF__SN_ID__Free_Yield( &s_asJob_Queue[tiQueue.m_uiI].m_sLock_Queue_Execute.m_sLock );
    tgCM_UT_LF__SN_ID__Free_Yield( &s_asJob_Queue[tiQueue.m_uiI].m_sLock_Queue_Add.m_sLock );
    tgCM_UT_ST__QU__Free( &s_asJob_Queue[tiQueue.m_uiI].m_sQueue_Add );
    tgCM_UT_ST__QU__Free( &s_asJob_Queue[tiQueue.m_uiI].m_sQueue_Execute );

    tgMM_Set_U08_0x00( s_asJob_Queue[tiQueue.m_uiI].m_asJob, sizeof( s_asJob_Queue[tiQueue.m_uiI].m_asJob ) );
    tgJOB_QUEUE_ID_Invalidate( &s_asJob_Queue[tiQueue.m_uiI].m_xtiQueue_Singleton );

    atomic_fetch_sub( &s_xnuiJob_Queue, 1 );
    atomic_thread_fence( cxx__memory_order_seq_cst );
}


/* ---- tgJM_Queue_Job ----------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgJM_Queue_Job( TgJOB_QUEUE_ID tiQueue, STg2_Job_P psJobSrc )
{
    union
    {
        STg2_UT_ST__ST_Node_P               psNode;
        STg2_Job_P                          psJob;
    }                                   sUnion;

    TgPARAM_CHECK(psJobSrc);

    /* Allow for runtime disable of the job system - this will force all queues to execute immediately */
    if (!tgJM_Is_Enabled())
    {
        return (TgSUCCEEDED(tgJM_Execute_Job( psJobSrc )) ? KTgS_JOB_EXECUTED: KTgE_FAIL);
    };

    /* Validate that we have a working queue */
    if((tiQueue.m_uiI >= KTgMAX_NUM_QUEUE) || TgFAILED( tgCM_UT_LF__SN_ID__Lock_Spin( &s_asJob_Queue[tiQueue.m_uiI].m_sLock_Queue_Add.m_sLock, tiQueue.m_uiKI ) ))
    {
        tgCM_UT_LF__SN_ID__Signal( &s_asJob_Queue[tiQueue.m_uiI].m_sLock_Queue_Execute.m_sLock );
        TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Invalid Queue." );
        return (KTgE_FAIL);
    };

    /* Run the job in-place if there are no threads that are processing this queue. */
    if (0 == atomic_load( &s_asJob_Queue[tiQueue.m_uiI].m_xuiRef ))
    {
        TgRESULT                            iRet;

        iRet = tgJM_Execute_Job( psJobSrc );
        tgCM_UT_LF__SN_ID__Signal( &s_asJob_Queue[tiQueue.m_uiI].m_sLock_Queue_Add.m_sLock );
        return (iRet);
    };

    sUnion.psNode = tgCM_UT_LF__ST__Pop( &s_asJob_Queue[tiQueue.m_uiI].m_sFree.m_sStack );
    if (nullptr == sUnion.psNode)
    {
        tgCM_UT_LF__SN_ID__Signal( &s_asJob_Queue[tiQueue.m_uiI].m_sLock_Queue_Add.m_sLock );
        return (KTgE_JOB_QUEUE_FULL);
    };
    sUnion.psJob->m_sNode.m_sStack.m_pNext_Node = (TgVOID_P)nullptr;
    tgMM_Copy( sUnion.psJob, sizeof( STg2_Job ), psJobSrc, sizeof( STg2_Job ) );

    /* Add job to queue */
    tgCM_UT_ST__QU__Enqueue( &s_asJob_Queue[tiQueue.m_uiI].m_sQueue_Add, &sUnion.psJob->m_sNode.m_sQueue );
    tgCM_UT_LF__SN_ID__Signal( &s_asJob_Queue[tiQueue.m_uiI].m_sLock_Queue_Add.m_sLock );

#if defined(DEBUG_STg2_Job_Queue)
    atomic_fetch_add( &s_asJob_Queue[tiQueue.m_uiI].m_xniQueued, 1 );
#endif

    /* #REVIEW: Do I need to Wake job threads */
    return (KTgS_OK);
}


/* ---- tgJM_Spawn_Job_Thread ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgJOB_THREAD_ID tgJM_Spawn_Job_Thread( TgJOB_QUEUE_ID_CPC atiQueueList, TgUINT_F32 niQueue, ETgTHREAD_PRIORITY_C enPriority, TgCHAR_U8_CPC szName )
{
#if TgCOMPILE__THREAD
    TgRSIZE                             uiIndex;
    TgJOB_THREAD_ID_SINGLETON           xtiJob_Thread_Singleton;

    tgCM_UT_LF__SN__Lock_Spin( &s_asLock_Job_Thread.m_sLock );

    if (ETgMODULE_STATE__BOOTED != s_enJob_MGR_State)
    {
        tgCM_UT_LF__SN__Signal( &s_asLock_Job_Thread.m_sLock );
        return (KTgJOB_THREAD_ID__INVALID);
    };

    /* Find an available slot for a new job thread */
    for (uiIndex = 0; uiIndex < KTgMAX_NUM_THREAD; ++uiIndex)
    {
        if (s_asJob_Thread[uiIndex].m_tiThread_NoSingleton.m_uiKI == KTgID__INVALID_VALUE)
            break;
    };

    if (KTgMAX_NUM_THREAD == uiIndex)
    {
        TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Exceeded number of allowable job threads." );
        tgCM_UT_LF__SN__Signal( &s_asLock_Job_Thread.m_sLock );
        return (KTgJOB_THREAD_ID__INVALID);
    };

    /* Initialize the thread data structure */
    tgMM_Set_U08_0x00( s_asJob_Thread + uiIndex, sizeof( STg2_Job_Thread ) );
    tgMM_Copy( &s_asJob_Thread[uiIndex].m_atiQueue, sizeof( s_asJob_Thread[uiIndex].m_atiQueue ), atiQueueList, niQueue*sizeof( TgJOB_QUEUE_ID ) );
    atomic_store( &s_asJob_Thread[uiIndex].m_iEnabled, 1 );
    s_asJob_Thread[uiIndex].m_tiThread_NoSingleton = tgJOB_THREAD_ID_Init( &xtiJob_Thread_Singleton, (TgUINT_F32)uiIndex );

    atomic_thread_fence( cxx__memory_order_seq_cst );
    tgCM_UT_LF__SN__Signal( &s_asLock_Job_Thread.m_sLock );

    /* Create the OS thread */
    s_asJob_Thread[uiIndex].m_tiOS_Thread = tgTR_Create( tgJM_Run_Job_Scheduler, s_asJob_Thread[uiIndex].m_tiThread_NoSingleton.m_uiKI, 0, enPriority, szName );
    if (s_asJob_Thread[uiIndex].m_tiOS_Thread.m_uiKI == KTgID__INVALID_VALUE)
    {
        /* On fail - clean it all up and return the slot reservation */
        s_asJob_Thread[uiIndex].m_tiThread_NoSingleton = KTgJOB_THREAD_ID__INVALID;
        atomic_store( &s_asJob_Thread[uiIndex].m_iEnabled, 0 );
        s_asJob_Thread[uiIndex].m_tiOS_Thread = KTgTHREAD_ID__INVALID;

        atomic_thread_fence( cxx__memory_order_seq_cst );
        return (KTgJOB_THREAD_ID__INVALID);
    };

    atomic_fetch_add( &s_xnuiJob_Thread, 1 );
    return (s_asJob_Thread[uiIndex].m_tiThread_NoSingleton);
#else
    (TgVOID)atiQueueList;
    (TgVOID)niQueue;
    (TgVOID)enPriority;
    (TgVOID)szName;
    return (KTgJOB_THREAD_ID__INVALID);
    
/*# TgCOMPILE__THREAD */
#endif
}


/* ---- tgJM_Stop_Job_Thread ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgJM_Stop_Job_Thread( TgJOB_THREAD_ID tiJob_Thread )
{
#if TgCOMPILE__THREAD
    tgCM_UT_LF__SN__Lock_Yield( &s_asLock_Job_Thread.m_sLock );

    TgERROR( tiJob_Thread.m_uiKI != KTgID__INVALID_VALUE );

    if ((tiJob_Thread.m_uiI >= KTgMAX_NUM_THREAD) || (s_asJob_Thread[tiJob_Thread.m_uiI].m_tiThread_NoSingleton.m_uiKI != tiJob_Thread.m_uiKI ))
    {
        TgCRITICAL_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Job Thread ID Mismatch." );
        tgCM_UT_LF__SN__Signal( &s_asLock_Job_Thread.m_sLock );
        return;
    };

    atomic_store( &s_asJob_Thread[tiJob_Thread.m_uiI].m_iEnabled, 0 );
    tgTR_Close( s_asJob_Thread[tiJob_Thread.m_uiI].m_tiOS_Thread );

    s_asJob_Thread[tiJob_Thread.m_uiI].m_tiOS_Thread = KTgTHREAD_ID__INVALID;
    s_asJob_Thread[tiJob_Thread.m_uiI].m_tiThread_NoSingleton.m_uiKI = KTgID__INVALID_VALUE;

    atomic_thread_fence( cxx__memory_order_seq_cst );
    tgCM_UT_LF__SN__Signal( &s_asLock_Job_Thread.m_sLock );
#else
    (void)tiJob_Thread;
/*# TgCOMPILE__THREAD */
#endif
}


/* ---- tgJM_Stop_Job_Thread ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgTHREAD_ID tgJM_Query_Thread_Id( TgJOB_THREAD_ID tiJob_Thread )
{
    TgTHREAD_ID                         tiThread;

    TgPARAM_CHECK( tiJob_Thread.m_uiKI != KTgID__INVALID_VALUE );
    TgPARAM_CHECK( tiJob_Thread.m_uiI < KTgMAX_NUM_THREAD );
    tiThread.m_uiKI = KTgID__INVALID_VALUE;

#if TgCOMPILE__THREAD
    tgCM_UT_LF__SN__Lock_Yield( &s_asLock_Job_Thread.m_sLock );
    if ((tiJob_Thread.m_uiI < KTgMAX_NUM_THREAD) && (s_asJob_Thread[tiJob_Thread.m_uiI].m_tiThread_NoSingleton.m_uiKI == tiJob_Thread.m_uiKI) )
    {
        tiThread = s_asJob_Thread[tiJob_Thread.m_uiI].m_tiOS_Thread;
    };
    tgCM_UT_LF__SN__Signal( &s_asLock_Job_Thread.m_sLock );
#else
    (void)tiThread;
/*# TgCOMPILE__THREAD */
#endif
    
    return (tiThread);
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgJM_Is_Enabled ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgBOOL tgJM_Is_Enabled( TgVOID )
{
#if TgCOMPILE__JOB_THREAD
    TgBOOL                              bValue;

    if (!tgCN_Var_Query_Bool( &bValue, g_tiCVAR_Job_MGR_Enabled ))
    {
        return (false);
    };

    return (((bValue == true) && (atomic_load( &s_xnuiJob_Thread ) > 0))? true : false);
/*# TgCOMPILE__JOB_THREAD */
#else
    return (false);
/*# TgCOMPILE__JOB_THREAD */
#endif
}


/* ---- tgJM_Execute_Next_Job ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static STg2_Job_P tgJM_Execute_Next_Job( TgJOB_QUEUE_ID tiQueue )
{
    union
    {
        STg2_UT_ST__QU_Node_P               psNode;
        STg2_Job_P                          psJob;
    }                                   sUnion;
    STg2_UT_ST__QU_Node_P               psPrev_Node;

    if (tiQueue.m_uiI >= KTgMAX_NUM_QUEUE)
        return (nullptr);
    
    /* Merge the new jobs into the execute queue.  The empty check is not thread safe but conservative.  It will eventually post ... */
    if (!tgCM_UT_ST__QU__Is_Empty( &s_asJob_Queue[tiQueue.m_uiI].m_sQueue_Add ))
    {
        if (TgFAILED( tgCM_UT_LF__SN_ID__Lock_Yield( &s_asJob_Queue[tiQueue.m_uiI].m_sLock_Queue_Add.m_sLock, tiQueue.m_uiKI ) ))
        {
            return (nullptr);
        }
        tgCM_UT_ST__QU__Merge( &s_asJob_Queue[tiQueue.m_uiI].m_sQueue_Execute, &s_asJob_Queue[tiQueue.m_uiI].m_sQueue_Add );
        tgCM_UT_LF__SN_ID__Signal( &s_asJob_Queue[tiQueue.m_uiI].m_sLock_Queue_Add.m_sLock );
    };

    sUnion.psNode = s_asJob_Queue[tiQueue.m_uiI].m_sQueue_Execute.m_sNode.m_pNext_Node;
    psPrev_Node = nullptr;

    /* Iterate through the execute queue for the first valid job */
    for (; &s_asJob_Queue[tiQueue.m_uiI].m_sQueue_Execute.m_sNode != sUnion.psNode; psPrev_Node = sUnion.psNode, sUnion.psNode = sUnion.psNode->m_pNext_Node)
    {
        
        if (sUnion.psJob->m_pxuiAbort && (0 != atomic_load(sUnion.psJob->m_pxuiAbort)))
        {
            break;
        };

        if (sUnion.psJob->m_pxuiTrigger && (0 != atomic_load(sUnion.psJob->m_pxuiTrigger)))
        {
            continue;
        };

        if (sUnion.psJob->m_pfnRunTest && (KTgS_OK != sUnion.psJob->m_pfnRunTest( sUnion.psJob )))
        {
            continue;
        };

        break;
    };

    /* Check to see if all jobs were invalid for execution (or queue was empty) */
    if (&s_asJob_Queue[tiQueue.m_uiI].m_sQueue_Execute.m_sNode == sUnion.psNode)
    {
        tgCM_UT_LF__SN_ID__Signal( &s_asJob_Queue[tiQueue.m_uiI].m_sLock_Queue_Execute.m_sLock );
        return (nullptr);
    }

#if defined(DEBUG_STg2_Job_Queue)
    atomic_fetch_sub( &s_asJob_Queue[tiQueue.m_uiI].m_xniQueued, 1 );
#endif

    /* Remove the node from the queue */
    if (nullptr == psPrev_Node)
    {
        TgVERIFY(sUnion.psNode == tgCM_UT_ST__QU__Dequeue( &s_asJob_Queue[tiQueue.m_uiI].m_sQueue_Execute ));
    }
    else
    {
        if (s_asJob_Queue[tiQueue.m_uiI].m_sQueue_Execute.m_psTail_Node == sUnion.psNode)
        {
            TgERROR(sUnion.psNode->m_pNext_Node == &s_asJob_Queue[tiQueue.m_uiI].m_sQueue_Execute.m_sNode);
            s_asJob_Queue[tiQueue.m_uiI].m_sQueue_Execute.m_psTail_Node = psPrev_Node;
        }
        psPrev_Node->m_pNext_Node = sUnion.psNode->m_pNext_Node;
    };

    atomic_thread_fence( cxx__memory_order_seq_cst );
    TgERROR( tgCM_UT_ST__QU__Is_Valid( &s_asJob_Queue[tiQueue.m_uiI].m_sQueue_Execute ) );

    tgCM_UT_LF__SN_ID__Signal( &s_asJob_Queue[tiQueue.m_uiI].m_sLock_Queue_Execute.m_sLock );

    /* Execute the Job */
    sUnion.psJob->m_pxuiTrigger = nullptr;
    sUnion.psJob->m_pfnRunTest = nullptr;
    tgJM_Execute_Job( sUnion.psJob );

    /* Put the node back into the free pool */
    tgMM_Set_U08_0x00( sUnion.psJob, sizeof( STg2_Job ) );

    return (sUnion.psJob);
}


/* ---- tgJM_Execute_Job --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT tgJM_Execute_Job( STg2_Job_P psJob )
{
    TgERROR(nullptr != psJob);

    if (psJob->m_pxuiAbort && (0 != atomic_load( psJob->m_pxuiAbort )))
    {
        if (psJob->m_pfnAbort)
        {
            psJob->m_pfnAbort( psJob );
        };
    }
    else if (psJob->m_pfnExecute)
    {
        if (psJob->m_pxuiTrigger && (0 != atomic_load( psJob->m_pxuiTrigger )))
        {
            return (KTgE_FAIL);
        };

        if (psJob->m_pfnRunTest && (KTgS_OK != psJob->m_pfnRunTest( psJob )))
        {
            return (KTgE_FAIL);
        };

        if (psJob->m_pxuiExecute)
        {
            atomic_fetch_add( psJob->m_pxuiExecute, 1 );
            psJob->m_pfnExecute( psJob );
            atomic_fetch_sub( psJob->m_pxuiExecute, 1 );
        }
        else
        {
            psJob->m_pfnExecute( psJob );
        };
    };

    if (psJob->m_pxuiFinish)
    {
        atomic_fetch_sub( psJob->m_pxuiFinish, 1 );
    };

    return (KTgS_OK);
}


/* ---- tgJM_Run_Job_Scheduler --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if TgCOMPILE__THREAD
static TgNOTHROW TgUINT_F32 tgJM_Run_Job_Scheduler( TgUINT_PTR_C uiJob_Thread )
{
    TgJOB_THREAD_ID                     tiJob_Thread;
    STg2_Job_Thread_P                   psJob_Thread;
    TgRSIZE                             uiQueue;
    TgJOB_QUEUE_ID                      tiQueue;

    /* Verify parameter is valid, and data passes basic integrity check */
    tiJob_Thread.m_uiKI = uiJob_Thread;

    if ((tiJob_Thread.m_uiI >= KTgMAX_NUM_THREAD) || (tiJob_Thread.m_uiKI == KTgID__INVALID_VALUE))
    {
        TgCRITICAL_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Invalid Job Thread ID as Parameter." );
        atomic_fetch_sub( &s_xnuiJob_Thread, 1 );
        return (1);
    };

    if (s_asJob_Thread[tiJob_Thread.m_uiI].m_tiThread_NoSingleton.m_uiKI != tiJob_Thread.m_uiKI)
    {
        TgCRITICAL_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Job Thread ID Mismatch." );
        atomic_fetch_sub( &s_xnuiJob_Thread, 1 );
        return (1);
    };

    psJob_Thread = s_asJob_Thread + tiJob_Thread.m_uiI;

    for (uiQueue = 0; uiQueue < KTgMAX_NUM_QUEUE; ++uiQueue)
    {
        tiQueue = psJob_Thread->m_atiQueue[uiQueue];

        /* Stop processing the thread's queue list when we have reached a terminus. */
        if (tiQueue.m_uiKI == KTgID__INVALID_VALUE)
            break;

        atomic_fetch_add( &s_asJob_Queue[tiQueue.m_uiI].m_xuiRef, 1 );
    };

    /* Primary loop */
    while (atomic_load( &psJob_Thread->m_iEnabled ))
    {
        STg2_Job_P                          psJob;
        TgRESULT                            iResult;

        for (uiQueue = 0; uiQueue < KTgMAX_NUM_QUEUE; ++uiQueue)
        {
            tiQueue = psJob_Thread->m_atiQueue[uiQueue];

            /* Stop processing the thread's queue list when we have reached a terminus. */
            if (tiQueue.m_uiKI == KTgID__INVALID_VALUE)
                break;

            /* #REVIEW: For now, rather than deal with contention - if another thread is processing the queue, move onto the next queue */
            /* Note: This "should" work for small number of threads, but will definitely fail as that number increases */
            /* The attempt to acquire the lock will also validate the queue identifier */
            iResult = tgCM_UT_LF__SN_ID__Lock_Yield( &s_asJob_Queue[tiQueue.m_uiI].m_sLock_Queue_Execute.m_sLock, tiQueue.m_uiKI );

            if (KTgE_SN_INVALID_ID == iResult)
            {
                TgRSIZE                             uiQueue_Compact = uiQueue;

                for (++uiQueue_Compact; uiQueue_Compact < KTgMAX_NUM_QUEUE; ++uiQueue_Compact)
                {
                    tiQueue = psJob_Thread->m_atiQueue[uiQueue_Compact];
                    if (tiQueue.m_uiKI == KTgID__INVALID_VALUE)
                        break;
                    psJob_Thread->m_atiQueue[uiQueue_Compact - 1] = tiQueue;
                };
                psJob_Thread->m_atiQueue[uiQueue_Compact - 1] = KTgJOB_QUEUE_ID__INVALID;
                
                if (0 == uiQueue)
                    break;
                else
                    --uiQueue;

                continue;
            }
            else if (TgFAILED( iResult ))
            {
                continue;
            }

            psJob = tgJM_Execute_Next_Job( tiQueue );
            if (nullptr == psJob)
                continue;
            tgCM_UT_LF__ST__Push( &s_asJob_Queue[tiQueue.m_uiI].m_sFree.m_sStack, &psJob->m_sNode.m_sStack );

            /* We always want to restart searching for a job at the top of the queue list */
            break;
        };

        if (uiQueue == KTgMAX_NUM_QUEUE || KTgID__INVALID_VALUE == psJob_Thread->m_atiQueue[uiQueue].m_uiKI)
        {
            /* With a large number of threads, the amount of contention on the queue's becomes a bottle neck. */
            //tgTR_Yield();
            tgTR_Sleep( tgCM_RAND_U32() );
        }
    };

    for (uiQueue = 0; uiQueue < KTgMAX_NUM_QUEUE; ++uiQueue)
    {
        tiQueue = psJob_Thread->m_atiQueue[uiQueue];

        /* Stop processing the thread's queue list when we have reached a terminus. */
        if (tiQueue.m_uiKI == KTgID__INVALID_VALUE)
            break;

        atomic_fetch_sub( &s_asJob_Queue[tiQueue.m_uiI].m_xuiRef, 1 );
    };

    atomic_fetch_sub( &s_xnuiJob_Thread, 1 );
    return (0);
}
/*# TgCOMPILE__THREAD */
#endif
