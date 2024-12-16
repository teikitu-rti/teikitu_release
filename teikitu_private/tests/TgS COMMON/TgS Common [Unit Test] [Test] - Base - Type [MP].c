/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common [Unit Test] [Test] - Base - Type [MP].c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TEST_METHOD( UNIT_TEST__PM_MT_MX_Init );
TEST_METHOD( UNIT_TEST__PM_MT_MX_Free );
TEST_METHOD( UNIT_TEST__PM_MT_MX_Wait_Block );
TEST_METHOD( UNIT_TEST__PM_MT_MX_Wait );
TEST_METHOD( UNIT_TEST__PM_MT_MX_Release );
TEST_METHOD( UNIT_TEST__PM_MT_SM_Init );
TEST_METHOD( UNIT_TEST__PM_MT_SM_Free );
TEST_METHOD( UNIT_TEST__PM_MT_SM_Wait_Block );
TEST_METHOD( UNIT_TEST__PM_MT_SM_Wait );
TEST_METHOD( UNIT_TEST__PM_MT_SM_Signal );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#if TgCOMPILE__THREAD

TEST_LOCAL TgUINT_E32
UNIT_TEST__TEST__MUTEX(
    TgATTRIBUTE_UNUSED TgUINT_PTR_C uiUnused ) TgATTRIBUTE_NO_EXCEPT;

TEST_LOCAL TgUINT_E32
UNIT_TEST__TEST__SEMAPHORE(
    TgATTRIBUTE_UNUSED TgUINT_PTR_C uiUnused ) TgATTRIBUTE_NO_EXCEPT;

/*# TgCOMPILE__THREAD */
#endif

TEST_LOCAL STg1_MT_MX                       s_sMP_MX;
TEST_LOCAL STg1_MT_SM                       s_sMP_SM;
TEST_LOCAL TgSINT_E32_A                     s_iTest_Enabled;




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- UNIT_TEST__TEST__Base_Type_MP -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( UNIT_TEST__TEST__Base_Type_MP )
{
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__PM_MT_MX_Init() );
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__PM_MT_MX_Free() );
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__PM_MT_MX_Wait_Block() );
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__PM_MT_MX_Wait() );
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__PM_MT_MX_Release() );
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__PM_MT_SM_Init() );
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__PM_MT_SM_Free() );
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__PM_MT_SM_Wait_Block() );
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__PM_MT_SM_Wait() );
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__PM_MT_SM_Signal() );

    TEST_END_METHOD( KTgS_OK );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#if TgCOMPILE__THREAD

TEST_LOCAL TgUINT_E32 UNIT_TEST__TEST__MUTEX( TgATTRIBUTE_UNUSED TgUINT_PTR_C uiUnused ) TgATTRIBUTE_NO_EXCEPT
{
    TgSTD_ATOMIC(store)( &s_iTest_Enabled, 1 );
    tgPM_MT_MX_Wait_Block( &s_sMP_MX );
    TgSTD_ATOMIC(store)( &s_iTest_Enabled, 2 );
    tgPM_MT_MX_Release( &s_sMP_MX );
    TgSTD_ATOMIC(store)( &s_iTest_Enabled, 3 );

    return (0);
}


TEST_LOCAL TgUINT_E32 UNIT_TEST__TEST__SEMAPHORE( TgATTRIBUTE_UNUSED TgUINT_PTR_C uiUnused ) TgATTRIBUTE_NO_EXCEPT
{
    TgSTD_ATOMIC(store)( &s_iTest_Enabled, 1 );
    tgPM_MT_SM_Wait_Block( &s_sMP_SM );
    TgSTD_ATOMIC(store)( &s_iTest_Enabled, 2 );
    tgPM_MT_SM_Signal( &s_sMP_SM, 1 );
    TgSTD_ATOMIC(store)( &s_iTest_Enabled, 3 );

    return (0);
}

/*# TgCOMPILE__THREAD */
#endif


/* ---- UNIT_TEST__PM_MT_MX_Init ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__PM_MT_MX_Init )
{
#if TgCOMPILE__THREAD
    Test__Expect_EQ(KTgS_OK, tgPM_MT_MX_Init( &s_sMP_MX, TgOS_TEXT("MutexTest001") ));
    tgPM_MT_MX_Free( &s_sMP_MX );

/*# TgCOMPILE__THREAD */
#endif

    return (KTgS_OK);
}


/* ---- UNIT_TEST__PM_MT_MX_Free ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__PM_MT_MX_Free )
{
#if TgCOMPILE__THREAD
    Test__Expect_EQ(KTgS_OK, tgPM_MT_MX_Init( &s_sMP_MX, TgOS_TEXT("MutexTest001") ));
    tgPM_MT_MX_Free( &s_sMP_MX );
    Test__Expect_EQ(KTgS_OK, tgPM_MT_MX_Init( &s_sMP_MX, TgOS_TEXT("MutexTest001") ));
    tgPM_MT_MX_Free( &s_sMP_MX );

/*# TgCOMPILE__THREAD */
#endif

    return (KTgS_OK);
}


/* ---- UNIT_TEST__PM_MT_MX_Wait_Block ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__PM_MT_MX_Wait_Block )
{
#if TgCOMPILE__THREAD
    TgTHREAD_ID                         tiThread;

    Test__Expect_EQ(KTgS_OK, tgPM_MT_MX_Init( &s_sMP_MX, TgOS_TEXT("MutexTest001") ));
    Test__Expect_EQ(KTgS_OK, tgPM_MT_MX_Wait( &s_sMP_MX ));

    TgSTD_ATOMIC(store)( &s_iTest_Enabled, 0 );
    tiThread = tgTR_Create( UNIT_TEST__TEST__MUTEX, 0, 0, ETgTHREAD_PRIORITY__NORMAL, u8"UNIT_TEST__TEST__MUTEX" );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiThread.m_uiKI);

    while (0 == TgSTD_ATOMIC(load)( &s_iTest_Enabled ))
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(KTgS_OK, tgPM_MT_MX_Wait( &s_sMP_MX )); /* Re-entrant (recursive) */
    tgPM_MT_MX_Release( &s_sMP_MX );
    tgPM_MT_MX_Release( &s_sMP_MX );
    while (0 == TgSTD_ATOMIC(load)( &s_iTest_Enabled ))
    {
        tgTR_Yield();
    };

    tgTR_Close( tiThread );

    tgPM_MT_MX_Free( &s_sMP_MX );

/*# TgCOMPILE__THREAD */
#endif

    return (KTgS_OK);
}


/* ---- UNIT_TEST__PM_MT_MX_Wait ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__PM_MT_MX_Wait )
{
#if TgCOMPILE__THREAD
    Test__Expect_EQ(KTgS_OK, tgPM_MT_MX_Init( &s_sMP_MX, TgOS_TEXT("MutexTest001") ));
    Test__Expect_EQ(KTgS_OK, tgPM_MT_MX_Wait( &s_sMP_MX ));
    Test__Expect_EQ(KTgS_OK, tgPM_MT_MX_Wait( &s_sMP_MX )); /* Re-entrant (recursive) */
    tgPM_MT_MX_Release( &s_sMP_MX );
    tgPM_MT_MX_Release( &s_sMP_MX );
    tgPM_MT_MX_Free( &s_sMP_MX );

/*# TgCOMPILE__THREAD */
#endif

    return (KTgS_OK);
}


/* ---- UNIT_TEST__PM_MT_MX_Release ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__PM_MT_MX_Release )
{
#if TgCOMPILE__THREAD
    Test__Expect_EQ(KTgS_OK, tgPM_MT_MX_Init( &s_sMP_MX, TgOS_TEXT("MutexTest001") ));
    Test__Expect_EQ(KTgS_OK, tgPM_MT_MX_Wait( &s_sMP_MX ));
    Test__Expect_EQ(KTgS_OK, tgPM_MT_MX_Wait( &s_sMP_MX )); /* Re-entrant (recursive) */
    tgPM_MT_MX_Release( &s_sMP_MX );
    tgPM_MT_MX_Release( &s_sMP_MX );
    Test__Expect_EQ(KTgS_OK, tgPM_MT_MX_Wait( &s_sMP_MX ));
    Test__Expect_EQ(KTgS_OK, tgPM_MT_MX_Wait( &s_sMP_MX )); /* Re-entrant (recursive) */
    tgPM_MT_MX_Release( &s_sMP_MX );
    tgPM_MT_MX_Release( &s_sMP_MX );
    tgPM_MT_MX_Free( &s_sMP_MX );

/*# TgCOMPILE__THREAD */
#endif

    return (KTgS_OK);
}


/* ---- UNIT_TEST__PM_MT_SM_Init ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__PM_MT_SM_Init )
{
#if TgCOMPILE__THREAD
    Test__Expect_EQ(KTgS_OK, tgPM_MT_SM_Init( &s_sMP_SM, u8"SemTest001", 0, TgPLATFORM__SEMAPHORE_MAX_VALUE ));
    tgPM_MT_SM_Free( &s_sMP_SM );

    Test__Expect_EQ(KTgS_OK, tgPM_MT_SM_Init( &s_sMP_SM, u8"SemTest001", 1, 2 ));
    Test__Expect_EQ(KTgS_OK, tgPM_MT_SM_Wait( &s_sMP_SM ));
    Test__Expect_NE(KTgS_OK, tgPM_MT_SM_Wait( &s_sMP_SM ));
    tgPM_MT_SM_Free( &s_sMP_SM );

/*# TgCOMPILE__THREAD */
#endif

    return (KTgS_OK);
}


/* ---- UNIT_TEST__PM_MT_SM_Free ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__PM_MT_SM_Free )
{
    Test__Expect_EQ(KTgS_OK, tgPM_MT_SM_Init( &s_sMP_SM, u8"SemTest001", 0, TgPLATFORM__SEMAPHORE_MAX_VALUE ));
    tgPM_MT_SM_Free( &s_sMP_SM );
    Test__Expect_EQ(KTgS_OK, tgPM_MT_SM_Init( &s_sMP_SM, u8"SemTest001", 0, TgPLATFORM__SEMAPHORE_MAX_VALUE ));
    tgPM_MT_SM_Free( &s_sMP_SM );

    return (KTgS_OK);
}


/* ---- UNIT_TEST__PM_MT_SM_Wait_Block ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__PM_MT_SM_Wait_Block )
{
#if TgCOMPILE__THREAD
    TgTHREAD_ID                         tiThread;

    Test__Expect_EQ(KTgS_OK, tgPM_MT_SM_Init( &s_sMP_SM, u8"SemTest001", 0, TgPLATFORM__SEMAPHORE_MAX_VALUE ));

    TgSTD_ATOMIC(store)( &s_iTest_Enabled, 0 );
    tiThread = tgTR_Create( UNIT_TEST__TEST__SEMAPHORE, 0, 0, ETgTHREAD_PRIORITY__NORMAL, u8"UNIT_TEST__TEST__SEMAPHORE" );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiThread.m_uiKI);

    while (0 == TgSTD_ATOMIC(load)( &s_iTest_Enabled ))
    {
        tgTR_Yield();
    };

    tgPM_MT_SM_Signal( &s_sMP_SM, 1 );
    while (0 == TgSTD_ATOMIC(load)( &s_iTest_Enabled ))
    {
        tgTR_Yield();
    };

    tgTR_Close( tiThread );

    tgPM_MT_SM_Free( &s_sMP_SM );

/*# TgCOMPILE__THREAD */
#endif

    return (KTgS_OK);
}


/* ---- UNIT_TEST__PM_MT_SM_Wait ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__PM_MT_SM_Wait )
{
    Test__Expect_EQ(KTgS_OK, tgPM_MT_SM_Init( &s_sMP_SM, u8"SemTest001", 1, 2 ));
    Test__Expect_EQ(KTgS_OK, tgPM_MT_SM_Wait( &s_sMP_SM ));
    Test__Expect_NE(KTgS_OK, tgPM_MT_SM_Wait( &s_sMP_SM ));
    tgPM_MT_SM_Free( &s_sMP_SM );

    return (KTgS_OK);
}


/* ---- UNIT_TEST__PM_MT_SM_Signal ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__PM_MT_SM_Signal )
{
    Test__Expect_EQ(KTgS_OK, tgPM_MT_SM_Init( &s_sMP_SM, u8"SemTest001", 1, 2 ));
    tgPM_MT_SM_Signal( &s_sMP_SM, 1 );
    Test__Expect_EQ(KTgS_OK, tgPM_MT_SM_Wait( &s_sMP_SM ));
    Test__Expect_EQ(KTgS_OK, tgPM_MT_SM_Wait( &s_sMP_SM ));
    Test__Expect_NE(KTgS_OK, tgPM_MT_SM_Wait( &s_sMP_SM ));
    tgPM_MT_SM_Signal( &s_sMP_SM, 2 );
    Test__Expect_EQ(KTgS_OK, tgPM_MT_SM_Wait( &s_sMP_SM ));
    Test__Expect_EQ(KTgS_OK, tgPM_MT_SM_Wait( &s_sMP_SM ));
    Test__Expect_NE(KTgS_OK, tgPM_MT_SM_Wait( &s_sMP_SM ));
    tgPM_MT_SM_Free( &s_sMP_SM );

    return (KTgS_OK);
}


