/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common [Unit Test] [Test] - Util MT - Spin Lock.c
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

TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__SN__Init );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__SN__Free );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__SN__Lock_Yield );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__SN__Lock_Spin );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__SN__Lock_Test );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__SN__Signal );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__SN__SLOW_THREAD );

TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__SN_CNT__Init );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__SN__CNTC_Free );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__SN_CNT__Lock_Or_Increment_Count );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__SN_CNT__Signal_Or_Reset_Count );

TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__SN_ID__Init );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__SN_ID__Free );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__SN_ID__Lock_Yield );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__SN_ID__Lock_Spin );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__SN_ID__Lock_Test );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__SN_ID__Signal );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
#if TgCOMPILE__THREAD

TEST_LOCAL TgUINT_E32
Spin_Unit_Test(
    TgUINT_PTR_C ) TgATTRIBUTE_NO_EXCEPT;

TEST_LOCAL TgUINT_E32
Suspend_Resume_Unit_Test(
    TgUINT_PTR_C ) TgATTRIBUTE_NO_EXCEPT;

TEST_LOCAL TgSINT_E32_A                     s_iTest;
TEST_LOCAL STg2_UT_LF__SN                   s_sUT_MP_SN_0;
TEST_LOCAL STg2_UT_LF__SN                   s_sUT_MP_SN_1;

/*# TgCOMPILE__THREAD */
#endif




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- UNIT_TEST__TEST__UTIL_MT_Spin_Lock --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( UNIT_TEST__TEST__UTIL_MT_Spin_Lock )
{
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__SN__Init());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__SN__Init());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__SN__Free());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__SN__Lock_Yield());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__SN__Lock_Spin());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__SN__Lock_Test());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__SN__Signal());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__SN__SLOW_THREAD());

    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__SN_CNT__Init());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__SN__CNTC_Free());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__SN_CNT__Lock_Or_Increment_Count());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__SN_CNT__Signal_Or_Reset_Count());

    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__SN_ID__Init());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__SN_ID__Free());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__SN_ID__Lock_Yield());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__SN_ID__Lock_Spin());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__SN_ID__Lock_Test());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__SN_ID__Signal());

    TEST_END_METHOD( KTgS_OK );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */


/* ---- UNIT_TEST__TEST__CM_UT_LF__SN__Init -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__SN__Init )
{
    STg2_UT_LF_ISO__SN                  sSN;

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__SN__Init( &sSN.m_sLock ));
    tgCM_UT_LF__SN__Free_Unsafe( &sSN.m_sLock );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_LF__SN__Free -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__SN__Free )
{
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__SN__Init());
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_LF__SN__Lock_Yield -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__SN__Lock_Yield )
{
    STg2_UT_LF_ISO__SN                  sSN;

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__SN__Init( &sSN.m_sLock ));

    tgCM_UT_LF__SN__Lock_Yield( &sSN.m_sLock );

    Test__Expect_NE(KTgS_OK, tgCM_UT_LF__SN__Lock_Test( &sSN.m_sLock ));
    tgCM_UT_LF__SN__Signal( &sSN.m_sLock );
    tgCM_UT_LF__SN__Free_Unsafe( &sSN.m_sLock );
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_LF__SN__Lock_Spin --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__SN__Lock_Spin )
{
    STg2_UT_LF_ISO__SN                  sSN;

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__SN__Init( &sSN.m_sLock ));

    tgCM_UT_LF__SN__Lock_Spin( &sSN.m_sLock );

    Test__Expect_NE(KTgS_OK, tgCM_UT_LF__SN__Lock_Test( &sSN.m_sLock ));
    tgCM_UT_LF__SN__Signal( &sSN.m_sLock );
    tgCM_UT_LF__SN__Free_Unsafe( &sSN.m_sLock );
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_LF__SN__Lock_Test --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__SN__Lock_Test )
{
    STg2_UT_LF_ISO__SN                  sSN;

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__SN__Init( &sSN.m_sLock ));

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__SN__Lock_Test( &sSN.m_sLock ));
    Test__Expect_NE(KTgS_OK, tgCM_UT_LF__SN__Lock_Test( &sSN.m_sLock ));

    tgCM_UT_LF__SN__Signal( &sSN.m_sLock );
    tgCM_UT_LF__SN__Free_Unsafe( &sSN.m_sLock );
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_LF__SN__Signal ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__SN__Signal )
{
    STg2_UT_LF_ISO__SN                  sSN;

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__SN__Init( &sSN.m_sLock ));
    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__SN__Lock_Test( &sSN.m_sLock ));
    Test__Expect_NE(KTgS_OK, tgCM_UT_LF__SN__Lock_Test( &sSN.m_sLock ));

    tgCM_UT_LF__SN__Signal( &sSN.m_sLock );

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__SN__Lock_Test( &sSN.m_sLock ));
    Test__Expect_NE(KTgS_OK, tgCM_UT_LF__SN__Lock_Test( &sSN.m_sLock ));
    tgCM_UT_LF__SN__Signal( &sSN.m_sLock );
    tgCM_UT_LF__SN__Free_Unsafe( &sSN.m_sLock );
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_LF__SN__SLOW_THREAD ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__SN__SLOW_THREAD )
{
#if TgCOMPILE__THREAD
    TgTHREAD_ID                         tiThread;
    TgUINT_E32                          uiIndex;

    TgSTD_ATOMIC(store)( &s_iTest, 0 );

    tgCM_UT_LF__SN__Init( &s_sUT_MP_SN_0 );
    tgCM_UT_LF__SN__Lock_Spin( &s_sUT_MP_SN_0 ); /* tgTR_Pause() tested as part of the spin */
    tgCM_UT_LF__SN__Init( &s_sUT_MP_SN_1 );
    tgCM_UT_LF__SN__Lock_Spin( &s_sUT_MP_SN_1 );

    tiThread = tgTR_Create( Spin_Unit_Test, 0, 0, ETgTHREAD_PRIORITY__NORMAL, u8"Thread_Unit_Test" );
    tgTR_Status( tiThread );
    for (uiIndex = 0; uiIndex < (TgUINT_E32)KTgMAX_U16; ++uiIndex)
    {
        tgCM_UT_LF__SN__Signal( &s_sUT_MP_SN_1 );
        tgTR_Yield();
        tgCM_UT_LF__SN__Lock_Spin( &s_sUT_MP_SN_0 );
    };
    tgTR_Close( tiThread );

    tgCM_UT_LF__SN__Signal( &s_sUT_MP_SN_1 );
    tgCM_UT_LF__SN__Free_Unsafe( &s_sUT_MP_SN_1 );
    tgCM_UT_LF__SN__Signal( &s_sUT_MP_SN_0 );
    tgCM_UT_LF__SN__Free_Unsafe( &s_sUT_MP_SN_0 );


    tgCM_UT_LF__SN__Init( &s_sUT_MP_SN_0 );
    tgCM_UT_LF__SN__Lock_Spin( &s_sUT_MP_SN_0 ); /* tgTR_Pause() tested as part of the spin */
    tgCM_UT_LF__SN__Init( &s_sUT_MP_SN_1 );
    tgCM_UT_LF__SN__Lock_Spin( &s_sUT_MP_SN_1 );

    tiThread = tgTR_Create( Suspend_Resume_Unit_Test, 0, 0, ETgTHREAD_PRIORITY__NORMAL, u8"Thread_Unit_Test" );
    for (uiIndex = 0; uiIndex < 12; ++uiIndex)
    {
        tgCM_UT_LF__SN__Lock_Spin( &s_sUT_MP_SN_0 );
        Unit_Test__Sleep( 3 );
        tgCM_UT_LF__SN__Signal( &s_sUT_MP_SN_1 );
    };
    tgTR_Close( tiThread );

    tgCM_UT_LF__SN__Signal( &s_sUT_MP_SN_1 );
    tgCM_UT_LF__SN__Free_Unsafe( &s_sUT_MP_SN_1 );
    tgCM_UT_LF__SN__Signal( &s_sUT_MP_SN_0 );
    tgCM_UT_LF__SN__Free_Unsafe( &s_sUT_MP_SN_0 );

    Test__Expect_EQ(true, tgTR_Stack_Size() > 0);
/*# TgCOMPILE__THREAD */
#endif

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_LF__SN_CNT__Init ---------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__SN_CNT__Init )
{
    STg2_UT_LF__SN_CNT                  sSN_CNT;

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__SN_CNT__Init( &sSN_CNT ));
    tgCM_UT_LF__SN_CNT__Free_Unsafe( &sSN_CNT );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_LF__SN_CNT__Free ---------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__SN__CNTC_Free )
{
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__SN_CNT__Init());
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_LF__SN_CNT__Lock_Or_Increment_Count --------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__SN_CNT__Lock_Or_Increment_Count )
{
    STg2_UT_LF__SN_CNT                  sSN_CNT;

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__SN_CNT__Init( &sSN_CNT ));
    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__SN_CNT__Lock_Or_Increment_Count( &sSN_CNT ));
    Test__Expect_NE(KTgS_OK, tgCM_UT_LF__SN_CNT__Lock_Or_Increment_Count( &sSN_CNT ));
    Test__Expect_EQ(1,tgCM_UT_LF__SN_CNT__Signal_Or_Reset_Count( &sSN_CNT ));
    Test__Expect_EQ(0,tgCM_UT_LF__SN_CNT__Signal_Or_Reset_Count( &sSN_CNT ));
    tgCM_UT_LF__SN_CNT__Free_Unsafe( &sSN_CNT );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_LF__SN_CNT__Signal_Or_Reset_Count ----------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__SN_CNT__Signal_Or_Reset_Count )
{
    STg2_UT_LF__SN_CNT                  sSN_CNT;

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__SN_CNT__Init( &sSN_CNT ));
    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__SN_CNT__Lock_Or_Increment_Count( &sSN_CNT ));
    Test__Expect_NE(KTgS_OK, tgCM_UT_LF__SN_CNT__Lock_Or_Increment_Count( &sSN_CNT ));
    Test__Expect_NE(KTgS_OK, tgCM_UT_LF__SN_CNT__Lock_Or_Increment_Count( &sSN_CNT ));
    Test__Expect_EQ(2,tgCM_UT_LF__SN_CNT__Signal_Or_Reset_Count( &sSN_CNT ));
    Test__Expect_EQ(0,tgCM_UT_LF__SN_CNT__Signal_Or_Reset_Count( &sSN_CNT ));
    tgCM_UT_LF__SN_CNT__Free_Unsafe( &sSN_CNT );

    TEST_END_METHOD( KTgS_OK );
}



/* ---- UNIT_TEST__TEST__CM_UT_LF__SN_ID__Init ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__SN_ID__Init )
{
    STg2_UT_LF__SN_ID                   sSN_ID;

    Test__Expect_NE(KTgS_OK, tgCM_UT_LF__SN_ID__Init( &sSN_ID, KTgID__INVALID_VALUE ));
    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__SN_ID__Init( &sSN_ID, 1 ));
    tgCM_UT_LF__SN_ID__Free_Yield( &sSN_ID );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_LF__SN_ID__Free ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__SN_ID__Free )
{
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__SN_ID__Init());
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_LF__SN_ID__Lock_Yield ----------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__SN_ID__Lock_Yield )
{
    STg2_UT_LF__SN_ID                   sSN_ID;

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__SN_ID__Init( &sSN_ID, 1 ));

    Test__Expect_NE(KTgS_OK, tgCM_UT_LF__SN_ID__Lock_Yield( &sSN_ID, KTgID__INVALID_VALUE ));
    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__SN_ID__Lock_Test( &sSN_ID, 1 ));
    tgCM_UT_LF__SN_ID__Signal( &sSN_ID );

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__SN_ID__Lock_Yield( &sSN_ID, 1 ));
    Test__Expect_NE(KTgS_OK, tgCM_UT_LF__SN_ID__Lock_Test( &sSN_ID, 1 ));
    Test__Expect_NE(KTgS_OK, tgCM_UT_LF__SN_ID__Lock_Test( &sSN_ID, KTgID__INVALID_VALUE ));
    tgCM_UT_LF__SN_ID__Signal( &sSN_ID );
    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__SN_ID__Lock_Test( &sSN_ID, 1 ));
    Test__Expect_NE(KTgS_OK, tgCM_UT_LF__SN_ID__Lock_Test( &sSN_ID, KTgID__INVALID_VALUE ));
    tgCM_UT_LF__SN_ID__Signal( &sSN_ID );

    tgCM_UT_LF__SN_ID__Free_Yield( &sSN_ID );
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_LF__SN_ID__Lock_Spin ------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__SN_ID__Lock_Spin )
{
    STg2_UT_LF__SN_ID                   sSN_ID;

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__SN_ID__Init( &sSN_ID, 1 ));

    Test__Expect_NE(KTgS_OK, tgCM_UT_LF__SN_ID__Lock_Spin( &sSN_ID, KTgID__INVALID_VALUE ));
    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__SN_ID__Lock_Test( &sSN_ID, 1 ));
    tgCM_UT_LF__SN_ID__Signal( &sSN_ID );

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__SN_ID__Lock_Spin( &sSN_ID, 1 ));
    Test__Expect_NE(KTgS_OK, tgCM_UT_LF__SN_ID__Lock_Test( &sSN_ID, 1 ));
    Test__Expect_NE(KTgS_OK, tgCM_UT_LF__SN_ID__Lock_Test( &sSN_ID, KTgID__INVALID_VALUE ));
    tgCM_UT_LF__SN_ID__Signal( &sSN_ID );
    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__SN_ID__Lock_Test( &sSN_ID, 1 ));
    Test__Expect_NE(KTgS_OK, tgCM_UT_LF__SN_ID__Lock_Test( &sSN_ID, KTgID__INVALID_VALUE ));
    tgCM_UT_LF__SN_ID__Signal( &sSN_ID );

    tgCM_UT_LF__SN_ID__Free_Yield( &sSN_ID );
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_LF__SN_ID__Lock_Test ------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__SN_ID__Lock_Test )
{
    STg2_UT_LF__SN_ID                   sSN_ID;

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__SN_ID__Init( &sSN_ID, 1 ));
    Test__Expect_NE(KTgS_OK, tgCM_UT_LF__SN_ID__Lock_Test( &sSN_ID, KTgID__INVALID_VALUE ));
    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__SN_ID__Lock_Test( &sSN_ID, 1 ));
    Test__Expect_NE(KTgS_OK, tgCM_UT_LF__SN_ID__Lock_Test( &sSN_ID, 1 ));
    Test__Expect_NE(KTgS_OK, tgCM_UT_LF__SN_ID__Lock_Test( &sSN_ID, KTgID__INVALID_VALUE ));
    tgCM_UT_LF__SN_ID__Signal( &sSN_ID );
    tgCM_UT_LF__SN_ID__Free_Yield( &sSN_ID );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_LF__SN_ID__Signal --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__SN_ID__Signal )
{
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__SN_ID__Lock_Test());
    TEST_END_METHOD( KTgS_OK );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
#if TgCOMPILE__THREAD

/* ---- Spin_Unit_Test ----------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgUINT_E32 Spin_Unit_Test( TgATTRIBUTE_UNUSED TgUINT_PTR_C uiUnused ) TgATTRIBUTE_NO_EXCEPT
{
    TgUINT_E32                          uiIndex;

    for (uiIndex = 0; uiIndex < (TgUINT_E32)KTgMAX_U16; ++uiIndex)
    {
        tgCM_UT_LF__SN__Lock_Spin( &s_sUT_MP_SN_1 );
        tgTR_Yield();
        tgCM_UT_LF__SN__Signal( &s_sUT_MP_SN_0 );
    };

    return (0);
}


/* ---- Suspend_Resume_Unit_Test ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgUINT_E32 Suspend_Resume_Unit_Test( TgATTRIBUTE_UNUSED TgUINT_PTR_C uiUnused ) TgATTRIBUTE_NO_EXCEPT
{
    TgUINT_E32                          uiIndex;

    for (uiIndex = 0; uiIndex < 12; ++uiIndex)
    {
        tgCM_UT_LF__SN__Signal( &s_sUT_MP_SN_0 );
        tgCM_UT_LF__SN__Lock_Spin( &s_sUT_MP_SN_1 );
    };

    return (0);
}

/*# TgCOMPILE__THREAD */
#endif
