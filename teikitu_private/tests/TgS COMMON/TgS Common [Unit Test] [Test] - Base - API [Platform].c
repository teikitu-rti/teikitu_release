/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common [Unit Test] [Test] - Base - API [Platform].c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Common ===================================================================================================================================================================== */
/* MARK: Unit Test Complete 00D008E0-5616-4AAF-8989-24865B450F52                                                                                                                   */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TEST_METHOD( UNIT_TEST__TEST__TR_Register_Main_Thread );
TEST_METHOD( UNIT_TEST__TEST__TR_Create );
TEST_METHOD( UNIT_TEST__TEST__TR_Query_Id );
TEST_METHOD( UNIT_TEST__TEST__TR_Close );
TEST_METHOD( UNIT_TEST__TEST__TR_Status );
TEST_METHOD( UNIT_TEST__TEST__TR_Stack_Size );
TEST_METHOD( UNIT_TEST__TEST__TR_Yield );
TEST_METHOD( UNIT_TEST__TEST__TR_Pause );
TEST_METHOD( UNIT_TEST__TEST__TR_Sleep );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TEST_LOCAL TgSINT_E32_A                     s_iTest;
TEST_LOCAL TgSINT_E32_A                     s_iTest_Enabled;
TEST_LOCAL TgTHREAD_ID                      s_tiTest_Thread;




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- UNIT_TEST__TEST__Base_API_PM_Thread -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( UNIT_TEST__TEST__Base_API_PM_Thread )
{
    Test__Expect_EQ( KTgS_OK, UNIT_TEST__TEST__TR_Register_Main_Thread() );
    Test__Expect_EQ( KTgS_OK, UNIT_TEST__TEST__TR_Create() );
    Test__Expect_EQ( KTgS_OK, UNIT_TEST__TEST__TR_Query_Id() );
    Test__Expect_EQ( KTgS_OK, UNIT_TEST__TEST__TR_Close() );
    Test__Expect_EQ( KTgS_OK, UNIT_TEST__TEST__TR_Status() );
    Test__Expect_EQ( KTgS_OK, UNIT_TEST__TEST__TR_Stack_Size() );
    Test__Expect_EQ( KTgS_OK, UNIT_TEST__TEST__TR_Yield() );
    Test__Expect_EQ( KTgS_OK, UNIT_TEST__TEST__TR_Pause() );
    Test__Expect_EQ( KTgS_OK, UNIT_TEST__TEST__TR_Sleep() );

    TEST_END_METHOD( KTgS_OK );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#if TgCOMPILE__THREAD

TEST_LOCAL TgUINT_E32 Thread_Unit_Test( TgATTRIBUTE_UNUSED TgUINT_PTR_C uiUnused ) TgATTRIBUTE_NO_EXCEPT
{
    tgTR_Yield();
    TgSTD_ATOMIC(fetch_add)( &s_iTest, 1 );
    s_tiTest_Thread = tgTR_Query_Id();
    return (0);
}


TEST_LOCAL TgUINT_E32 Thread_Unit_Test_Gated( TgATTRIBUTE_UNUSED TgUINT_PTR_C uiUnused ) TgATTRIBUTE_NO_EXCEPT
{
    TgSTD_ATOMIC(store)( &s_iTest_Enabled, 1 );
    while (0 != TgSTD_ATOMIC(load)( &s_iTest_Enabled ))
    {
        tgTR_Yield();
    }
    return (0);
}


TEST_LOCAL TgUINT_E32 Thread_Unit_Test_Noop( TgATTRIBUTE_UNUSED TgUINT_PTR_C uiUnused ) TgATTRIBUTE_NO_EXCEPT
{
    return (0);
}


TEST_LOCAL TgUINT_E32 Thread_Unit_Test_Sleep( TgATTRIBUTE_UNUSED TgUINT_PTR_C uiUnused ) TgATTRIBUTE_NO_EXCEPT
{
    tgTR_Sleep(1000000);
    return (0);
}

/*# TgCOMPILE__THREAD */
#endif


/* ---- UNIT_TEST__TEST__TR_Register_Main_Thread --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__TR_Register_Main_Thread )
{
    /* This is a function that uses the other function calls to kick off the main thread. */
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__TR_Create ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__TR_Create )
{
#if TgCOMPILE__THREAD
    TgTHREAD_ID                         tiThread;

    /* Create a thread whose function will increment the global atomic value, and then close the thread, validate the value. */
    TgSTD_ATOMIC(store)( &s_iTest, 0 );
    tiThread = tgTR_Create( Thread_Unit_Test, 0, 0, ETgTHREAD_PRIORITY__NORMAL, u8"Thread_Unit_Test" );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiThread.m_uiKI);
    tgTR_Close( tiThread );
    Test__Expect_EQ(1, TgSTD_ATOMIC(load)( &s_iTest ));
/*# TgCOMPILE__THREAD */
#endif

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__TR_Query_Id --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__TR_Query_Id )
{
#if TgCOMPILE__THREAD
    TgTHREAD_ID                         tiThread;

    /* Create a thread whose function will set the thread id in the thread, and then close the thread, validate the value. */
    TgSTD_ATOMIC(store)( &s_iTest, 0 );
    tiThread = tgTR_Create( Thread_Unit_Test, 0, 0, ETgTHREAD_PRIORITY__NORMAL, u8"Thread_Unit_Test" );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiThread.m_uiKI);
    tgTR_Close( tiThread );
    Test__Expect_EQ(tiThread.m_uiKI, s_tiTest_Thread.m_uiKI );
/*# TgCOMPILE__THREAD */
#endif

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__TR_Close ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__TR_Close )
{
#if TgCOMPILE__THREAD
    TgTHREAD_ID                         tiThread;

    tiThread = tgTR_Create( Thread_Unit_Test, 0, 0, ETgTHREAD_PRIORITY__NORMAL, u8"Thread_Unit_Test" );
    tgTR_Close( tiThread ); /* Cannot think of any great way to test for thread termination */
/*# TgCOMPILE__THREAD */
#endif

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__TR_Status ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__TR_Status )
{
#if TgCOMPILE__THREAD
    TgTHREAD_ID                         tiThread;
    ETgTHREAD_STATUS                    enStatus;

    /* Create a thread whose function will increment the global atomic value, and then close the thread, validate the value. */
    TgSTD_ATOMIC(store)( &s_iTest_Enabled, 2 );
    tiThread = tgTR_Create( Thread_Unit_Test_Gated, 0, 0, ETgTHREAD_PRIORITY__NORMAL, u8"Thread_Unit_Test" );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiThread.m_uiKI);
    
    while (1 != TgSTD_ATOMIC(load)( &s_iTest_Enabled ))
    {
        tgTR_Yield();
    }
    enStatus = tgTR_Status( tiThread );
    Test__Expect_EQ(ETgTHREAD_STATUS__EXEC, enStatus);
    
    TgSTD_ATOMIC(store)( &s_iTest_Enabled, 0 );
    tgTR_Close( tiThread );
    
    enStatus = tgTR_Status( tiThread );
    Test__Expect_EQ(ETgTHREAD_STATUS__INVALID, enStatus);
/*# TgCOMPILE__THREAD */
#endif

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__TR_Stack_Size ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__TR_Stack_Size )
{
    /* Testing to validate stack size may generate indeterminate behaviour. */
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__TR_Yield ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__TR_Yield )
{
    /* Yielding implies giving up the remaining time in the time slice. It does not guarantee that the scheduler will select a different thread to execute next. Therefore, it is
       difficult to test for the right behaviour. */
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__TR_Pause ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__TR_Pause )
{
    /* The pause instruction on X86 is meant for short spin test like scenarios without stressing the CPU. It causes time to elapse on the CPU (think of a extended series of
       no-ops, allowing for time to elapse on the thread without requiring it to yield its time slice. */
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__TR_Sleep ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__TR_Sleep )
{
#if TgCOMPILE__THREAD
    TgTHREAD_ID                         tiThread;
    TgRSIZE                             uiIndex;
    TgFLOAT32                           fStart, fEnd, fElapsed_No_Sleep, fElapsed_Sleep;

    fElapsed_No_Sleep = 0.0F;
    fStart = tgTM_Query_Time();
    for (uiIndex = 0; uiIndex < 1000; ++uiIndex)
    {
        tiThread = tgTR_Create( Thread_Unit_Test_Noop, 0, 0, ETgTHREAD_PRIORITY__NORMAL, u8"Thread_Unit_Test" );
        Test__Expect_NE(KTgID__INVALID_VALUE, tiThread.m_uiKI);
        tgTR_Close( tiThread );
    };
    fEnd = tgTM_Query_Time();
    fElapsed_No_Sleep += fEnd - fStart;
    fElapsed_No_Sleep /= 1000.0F;

    fElapsed_Sleep = 0.0F;
    fStart = tgTM_Query_Time();
    for (uiIndex = 0; uiIndex < 1000; ++uiIndex)
    {
        tiThread = tgTR_Create( Thread_Unit_Test_Sleep, 0, 0, ETgTHREAD_PRIORITY__NORMAL, u8"Thread_Unit_Test" );
        Test__Expect_NE(KTgID__INVALID_VALUE, tiThread.m_uiKI);
        tgTR_Close( tiThread );
    };
    fEnd = tgTM_Query_Time();
    fElapsed_Sleep += fEnd - fStart;
    fElapsed_Sleep /= 1000.0F;

    Test__Expect_EQ(true, fElapsed_Sleep >fElapsed_No_Sleep + 0.9F ); /* Allow for a 10% margin of error */
/*# TgCOMPILE__THREAD */
#endif

    TEST_END_METHOD( KTgS_OK );
}
