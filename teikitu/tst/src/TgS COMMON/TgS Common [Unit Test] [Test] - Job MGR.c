/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common [Unit Test] [Test] - Job MGR.c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TEST_METHOD( UNIT_TEST__TEST__JM_Init_MGR );
TEST_METHOD( UNIT_TEST__TEST__JM_Boot_MGR );
TEST_METHOD( UNIT_TEST__TEST__JM_Stop_MGR );
TEST_METHOD( UNIT_TEST__TEST__JM_Free_MGR );
TEST_METHOD( UNIT_TEST__TEST__JM_Query_Init );
TEST_METHOD( UNIT_TEST__TEST__JM_Query_Boot );
TEST_METHOD( UNIT_TEST__TEST__JM_Query_Fixed_Memory );
TEST_METHOD( UNIT_TEST__TEST__JM_Init_Job_Queue );
TEST_METHOD( UNIT_TEST__TEST__JM_Stop_Job_Queue );
TEST_METHOD( UNIT_TEST__TEST__JM_Free_Job_Queue );
TEST_METHOD( UNIT_TEST__TEST__JM_Queue_Job );
TEST_METHOD( UNIT_TEST__TEST__JM_Spawn_Job_Thread );
TEST_METHOD( UNIT_TEST__TEST__JM_Stop_Job_Thread );
TEST_METHOD( UNIT_TEST__TEST__JM_Query_Thread_Id );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Types                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

enum { KTgJOB_TEST_MAX = KTgMAX_NUM_JOB * 8 };

TgTYPE_STRUCT(UNIT_TEST_JOB_DATA,)
{
    TgTHREAD_ID_P                       ptiThread;
};




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

static TgRESULT                             Job_Unit_Test__JM_Queue_Job( STg2_Job_PC psJob );
static TgRESULT                             Job_Unit_Test__JM_Query_Thread_Id( STg2_Job_PC psJob );

static TgSINT_F32_A                         s_iTest;




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- UNIT_TEST__TEST__COMMON_Job_MGR ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( UNIT_TEST__TEST__COMMON_Job_MGR )
{
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__JM_Init_MGR());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__JM_Boot_MGR());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__JM_Stop_MGR());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__JM_Free_MGR());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__JM_Query_Init());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__JM_Query_Boot());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__JM_Query_Fixed_Memory());

    tgCN_Var_Set_Bool( g_tiCVAR_Job_MGR_Enabled, false );

    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__JM_Init_Job_Queue());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__JM_Stop_Job_Queue());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__JM_Free_Job_Queue());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__JM_Queue_Job());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__JM_Spawn_Job_Thread());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__JM_Stop_Job_Thread());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__JM_Query_Thread_Id());

    tgCN_Var_Set_Bool( g_tiCVAR_Job_MGR_Enabled, true );

    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__JM_Init_Job_Queue());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__JM_Stop_Job_Queue());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__JM_Free_Job_Queue());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__JM_Queue_Job());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__JM_Spawn_Job_Thread());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__JM_Stop_Job_Thread());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__JM_Query_Thread_Id());

    TEST_END_METHOD( KTgS_OK );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- UNIT_TEST__TEST__JM_Init_MGR --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__JM_Init_MGR )
{
    /* Due to their nature, module management functions can not be unit tested */

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__JM_Boot_MGR --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__JM_Boot_MGR )
{
    /* Due to their nature, module management functions can not be unit tested */

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__JM_Stop_MGR --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__JM_Stop_MGR )
{
    /* Due to their nature, module management functions can not be unit tested */

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__JM_Free_MGR --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__JM_Free_MGR )
{
    /* Due to their nature, module management functions can not be unit tested */

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__JM_Query_Init ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__JM_Query_Init )
{
    Test__Expect_EQ(true, tgJM_Query_Init());

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__JM_Query_Boot ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__JM_Query_Boot )
{
    Test__Expect_EQ(true, tgJM_Query_Boot());

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__JM_Query_Fixed_Memory ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__JM_Query_Fixed_Memory )
{
    tgJM_Query_Fixed_Memory();

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__JM_Init_Job_Queue --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__JM_Init_Job_Queue )
{
    STg2_Job                            sJob_Test;
#if TgCOMPILE__THREAD
    TgJOB_QUEUE_ID                      atiQueueList[3];
    TgJOB_THREAD_ID                     tiJob_Thread;

    atiQueueList[0] = g_tiJob_Queue__OS;
    atiQueueList[1] = tgJM_Init_Job_Queue();
    atiQueueList[2] = KTgJOB_QUEUE_ID__INVALID;
    Test__Expect_NE(KTgID__INVALID_VALUE, atiQueueList[1].m_uiKI);

    tiJob_Thread = tgJM_Spawn_Job_Thread( atiQueueList, 4, ETgTHREAD_PRIORITY__NORMAL, u8"Job_Unit_Test" );

/*# TgCOMPILE__THREAD */
#endif

    tgMM_Set_U08_0x00( &sJob_Test, sizeof( sJob_Test ) );
    sJob_Test.m_pfnExecute = Job_Unit_Test__JM_Queue_Job;
    atomic_store( &s_iTest, 0 );

    for (TgRSIZE iJob = 0; iJob < KTgJOB_TEST_MAX; ++iJob)
    {
        TgRESULT                            iResult;

        iResult = tgJM_Queue_Job( atiQueueList[iJob % 2], &sJob_Test );
        while (KTgE_JOB_QUEUE_FULL == iResult)
        {
            Unit_Test__Sleep(1000000);
            iResult = tgJM_Queue_Job( atiQueueList[iJob % 2], &sJob_Test );
        };

        if (TgFAILED( iResult ))
        {
            atomic_fetch_add( &s_iTest, 1 );
        };
    };

    while (KTgJOB_TEST_MAX != atomic_load( &s_iTest ))
    {
        Unit_Test__Sleep( 1000000 );
    };

#if TgCOMPILE__THREAD
    tgJM_Stop_Job_Queue( atiQueueList[1], true );
    tgJM_Free_Job_Queue( atiQueueList[1] );
    tgJM_Stop_Job_Thread( tiJob_Thread );

/*# TgCOMPILE__THREAD */
#endif
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__JM_Stop_Job_Queue --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__JM_Stop_Job_Queue )
{
    /* Tested as part of UNIT_TEST__TEST__JM_Init_Job_Queue */

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__JM_Free_Job_Queue --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__JM_Free_Job_Queue )
{
    /* Tested as part of UNIT_TEST__TEST__JM_Init_Job_Queue */

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__JM_Queue_Job -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__JM_Queue_Job )
{
    /* Single job tested in UNIT_TEST__TEST__JM_Query_Thread_Id */
    STg2_Job                            sJob_Test;
    TgTHREAD_ID                         tiThread_Test;
    union
    {
        UNIT_TEST_JOB_DATA_P                psJob_Data;
        TgUINT_E08_P                        puiE08;
    }                                   uJob_Data;
#if TgCOMPILE__THREAD
    TgJOB_QUEUE_ID                      atiQueueList[3];
    TgJOB_THREAD_ID                     tiJob_Thread;

    atiQueueList[0] = g_tiJob_Queue__OS;
    atiQueueList[1] = KTgJOB_QUEUE_ID__INVALID;

    tiJob_Thread = tgJM_Spawn_Job_Thread( atiQueueList, 4, ETgTHREAD_PRIORITY__NORMAL, u8"Job_Unit_Test" );

/*# TgCOMPILE__THREAD */
#endif

    tgMM_Set_U08_0x00( &sJob_Test, sizeof( sJob_Test ) );
    sJob_Test.m_pfnExecute = Job_Unit_Test__JM_Queue_Job;
    uJob_Data.puiE08 = sJob_Test.m_auiData;
    uJob_Data.psJob_Data->ptiThread = &tiThread_Test;
    tiThread_Test.m_uiKI = KTgTHREAD_ID__INVALID.m_uiKI;
    atomic_store( &s_iTest, 0 );

    for (TgRSIZE iJob = 0; iJob < KTgJOB_TEST_MAX; ++iJob)
    {
        TgRESULT                            iResult;

        iResult = tgJM_Queue_Job( g_tiJob_Queue__OS, &sJob_Test );
        while (KTgE_JOB_QUEUE_FULL == iResult)
        {
            Unit_Test__Sleep( 1000 );
            iResult = tgJM_Queue_Job( g_tiJob_Queue__OS, &sJob_Test );
        };

        if (TgFAILED( iResult ))
        {
            atomic_fetch_add( &s_iTest, 1 );
        };
    };

    while (KTgJOB_TEST_MAX != atomic_load( &s_iTest ))
    {
        Unit_Test__Sleep( 1000 );
    };

#if TgCOMPILE__THREAD
    tgJM_Stop_Job_Thread( tiJob_Thread );

/*# TgCOMPILE__THREAD */
#endif

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__JM_Spawn_Job_Thread ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__JM_Spawn_Job_Thread )
{
    STg2_Job                            sJob_Test;
    TgFLOAT32                           fTime;
    TgCHAR_U8                           szBuffer[2048];
    TgCHAR_U8                           szExecuteTime[256];
    TgBOOL                              bMT_Enabled;

#if TgCOMPILE__THREAD
    TgJOB_THREAD_ID                     atiJob_Thread[KTgMAX_NUM_THREAD + 1];
    TgJOB_QUEUE_ID                      atiQueueList[3];

    atiQueueList[0] = g_tiJob_Queue__OS;
    atiQueueList[1] = KTgJOB_QUEUE_ID__INVALID;

    for (TgRSIZE uiJobThread = 0; uiJobThread < KTgMAX_NUM_THREAD; ++uiJobThread)
    {
        atiJob_Thread[uiJobThread] = tgJM_Spawn_Job_Thread( atiQueueList, 4, ETgTHREAD_PRIORITY__NORMAL, u8"Job_Unit_Test" );
        Test__Expect_NE(KTgID__INVALID_VALUE, atiJob_Thread[uiJobThread].m_uiKI);
    };

    tgCN_Remove_Default_Break( KTgCN_CHANEL_ERROR );
    g_bUnit_Test__Enabled_ERR_Write = false;
    atiJob_Thread[KTgMAX_NUM_THREAD] = tgJM_Spawn_Job_Thread( atiQueueList, 4, ETgTHREAD_PRIORITY__NORMAL, u8"Job_Unit_Test" );
    Test__Expect_EQ(KTgID__INVALID_VALUE, atiJob_Thread[KTgMAX_NUM_THREAD].m_uiKI);
    g_bUnit_Test__Enabled_ERR_Write = true;
    tgCN_Attach_Default_Break( KTgCN_CHANEL_ERROR );

/*# TgCOMPILE__THREAD */
#endif

    tgMM_Set_U08_0x00( &sJob_Test, sizeof( sJob_Test ) );
    sJob_Test.m_pfnExecute = Job_Unit_Test__JM_Queue_Job;
    atomic_store( &s_iTest, 0 );

    fTime = tgTM_Query_Time();

    for (TgRSIZE iJob = 0; iJob < KTgJOB_TEST_MAX; ++iJob)
    {
        TgRESULT                            iResult;

        iResult = tgJM_Queue_Job( g_tiJob_Queue__OS, &sJob_Test );
        while (KTgE_JOB_QUEUE_FULL == iResult)
        {
            Unit_Test__Sleep( 1 );
            iResult = tgJM_Queue_Job( g_tiJob_Queue__OS, &sJob_Test );
        };

        if (TgFAILED( iResult ))
        {
            atomic_fetch_add( &s_iTest, 1 );
        };
    };

    while (KTgJOB_TEST_MAX != atomic_load( &s_iTest ))
    {
        Unit_Test__Sleep( 1 );
    };

    tgUSZ_PrintF( szExecuteTime, TgARRAY_COUNT( szExecuteTime ), u8"% 8.3f ms", (TgFLOAT64)(tgTM_Query_Time() - fTime) );
    bMT_Enabled = false;
    bMT_Enabled &= tgCN_Var_Query_Bool( &bMT_Enabled, g_tiCVAR_Job_MGR_Enabled );
    if (bMT_Enabled)
    {
        tgUSZ_PrintF( szBuffer, TgARRAY_COUNT( szBuffer ), UNIT_TEST__MSG_LITERAL_3, u8"INFO:", u8"Common: Common", u8"Common", u8"Job MGR (MT)", szExecuteTime );
    }
    else
    {
        tgUSZ_PrintF( szBuffer, TgARRAY_COUNT( szBuffer ), UNIT_TEST__MSG_LITERAL_3, u8"INFO:", u8"Common: Common", u8"Common", u8"Job MGR (ST)", szExecuteTime );
    };
    TgMSGF( 0, u8"%s", szBuffer );

#if TgCOMPILE__THREAD
    for (TgRSIZE uiJobThread = 0; uiJobThread < KTgMAX_NUM_THREAD; ++uiJobThread)
    {
        tgJM_Stop_Job_Thread( atiJob_Thread[uiJobThread] );
    };

/*# TgCOMPILE__THREAD */
#endif

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__JM_Stop_Job_Thread -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__JM_Stop_Job_Thread )
{
    /* Tested in UNIT_TEST__TEST__JM_Spawn_Job_Thread */

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__JM_Query_Thread_Id -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__JM_Query_Thread_Id )
{
#if TgCOMPILE__THREAD
    STg2_Job                            sJob_Test;
    union
    {
        UNIT_TEST_JOB_DATA_P                psJob_Data;
        TgUINT_E08_P                        puiE08;
    }                                   uJob_Data;
    TgTHREAD_ID                         tiThread_Test, tiThread_Q;
    TgJOB_QUEUE_ID                      atiQueueList[3];
    TgJOB_THREAD_ID                     tiJob_Thread;
    TgBOOL                              bMT_Enabled, bMT_Test;

    atiQueueList[0] = g_tiJob_Queue__OS;
    atiQueueList[1] = KTgJOB_QUEUE_ID__INVALID;

    tiJob_Thread = tgJM_Spawn_Job_Thread( atiQueueList, 4, ETgTHREAD_PRIORITY__NORMAL, u8"Job_Unit_Test" );

    tgMM_Set_U08_0x00( &sJob_Test, sizeof( sJob_Test ) );
    sJob_Test.m_pfnExecute = Job_Unit_Test__JM_Query_Thread_Id;
    uJob_Data.puiE08 = sJob_Test.m_auiData;
    uJob_Data.psJob_Data->ptiThread = &tiThread_Test;
    tiThread_Test.m_uiKI = KTgTHREAD_ID__INVALID.m_uiKI;
    atomic_store( &s_iTest, 0 );

    Test__Expect_EQ(true, TgSUCCEEDED(tgJM_Queue_Job( g_tiJob_Queue__OS, &sJob_Test )));

    while (0 == atomic_load( &s_iTest ))
    {
        Unit_Test__Sleep( 1000000 );
    };

    bMT_Enabled = false;
    bMT_Test = tgCN_Var_Query_Bool( &bMT_Enabled, g_tiCVAR_Job_MGR_Enabled );
    bMT_Enabled &= bMT_Test;
    tiThread_Q = bMT_Enabled ? tgJM_Query_Thread_Id( tiJob_Thread ) : tgTR_Query_Id();
    Test__Expect_EQ(tiThread_Test.m_uiKI, tiThread_Q.m_uiKI);

    tgJM_Stop_Job_Thread( tiJob_Thread );

/*# TgCOMPILE__THREAD */
#endif

    TEST_END_METHOD( KTgS_OK );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- Job_Unit_Test__JM_Queue_Job ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT Job_Unit_Test__JM_Queue_Job( STg2_Job_PC UNUSED_PARAM psJob )
{
    atomic_fetch_add( &s_iTest, 1 );

    return (KTgS_OK);
}


/* ---- Job_Unit_Test__JM_Query_Thread_Id ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT Job_Unit_Test__JM_Query_Thread_Id( STg2_Job_PC psJob )
{
    TgSINT_F32                          iIndex;
    union
    {
        UNIT_TEST_JOB_DATA_P                psJob_Data;
        TgUINT_E08_P                        puiE08;
    }                                   uJob_Data;

    iIndex = atomic_fetch_add( &s_iTest, 1 );

    uJob_Data.puiE08 = psJob->m_auiData;
    *uJob_Data.psJob_Data->ptiThread = tgTR_Query_Id();

    return (KTgS_OK);
}
