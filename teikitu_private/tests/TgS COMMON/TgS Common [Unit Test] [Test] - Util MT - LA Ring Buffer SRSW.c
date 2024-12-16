/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common [Unit Test] [Test] - Util MT - LA Ring Buffer SRSW.c
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

TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__LA_RB_SRSW__Init );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__LA_RB_SRSW__Query_Used_Size );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__LA_RB_SRSW__Query_Free_Size );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__LA_RB_SRSW__Query_Max_Size );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__LA_RB_SRSW__Push_Next_Index );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__LA_RB_SRSW__Push_Commit );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__LA_RB_SRSW__Pop_Next_Index );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__LA_RB_SRSW__Pop_Commit );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- UNIT_TEST__TEST__UTIL_MT_LA_Ring_Buffer_SRSW ----------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( UNIT_TEST__TEST__UTIL_MT_LA_Ring_Buffer_SRSW )
{
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__LA_RB_SRSW__Init());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__LA_RB_SRSW__Query_Used_Size());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__LA_RB_SRSW__Query_Free_Size());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__LA_RB_SRSW__Query_Max_Size());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__LA_RB_SRSW__Push_Next_Index());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__LA_RB_SRSW__Push_Commit());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__LA_RB_SRSW__Pop_Next_Index());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__LA_RB_SRSW__Pop_Commit());

    TEST_END_METHOD( KTgS_OK );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- UNIT_TEST__TEST__CM_UT_LF__LA_RB_SRSW__Init ------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__LA_RB_SRSW__Init )
{
    STg2_UT_LF__LA_RB_SRSW              sSRSW;

    tgCM_UT_LF__LA_RB_SRSW__Init( &sSRSW, 10 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_LF__LA_RB_SRSW__Query_Used_Size ------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__LA_RB_SRSW__Query_Used_Size )
{
    STg2_UT_LF__LA_RB_SRSW              sSRSW;

    tgCM_UT_LF__LA_RB_SRSW__Init( &sSRSW, 10 );

    Test__Expect_EQ(0,tgCM_UT_LF__LA_RB_SRSW__Query_Used_Size( &sSRSW ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_LF__LA_RB_SRSW__Query_Free_Size ------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__LA_RB_SRSW__Query_Free_Size )
{
    STg2_UT_LF__LA_RB_SRSW              sSRSW;

    tgCM_UT_LF__LA_RB_SRSW__Init( &sSRSW, 10 );

    Test__Expect_EQ(10,tgCM_UT_LF__LA_RB_SRSW__Query_Free_Size( &sSRSW ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_LF__LA_RB_SRSW__Query_Max_Size -------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__LA_RB_SRSW__Query_Max_Size )
{
    STg2_UT_LF__LA_RB_SRSW              sSRSW;

    tgCM_UT_LF__LA_RB_SRSW__Init( &sSRSW, 10 );

    Test__Expect_EQ(10,tgCM_UT_LF__LA_RB_SRSW__Query_Max_Size( &sSRSW ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_LF__LA_RB_SRSW__Push_Next_Index ------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__LA_RB_SRSW__Push_Next_Index )
{
    STg2_UT_LF__LA_RB_SRSW              sSRSW;

    tgCM_UT_LF__LA_RB_SRSW__Init( &sSRSW, 10 );

    Test__Expect_EQ(0,tgCM_UT_LF__LA_RB_SRSW__Push_Next_Index( &sSRSW ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_LF__LA_RB_SRSW__Push_Commit ----------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__LA_RB_SRSW__Push_Commit )
{
    STg2_UT_LF__LA_RB_SRSW              sSRSW;

    tgCM_UT_LF__LA_RB_SRSW__Init( &sSRSW, 10 );

    tgCM_UT_LF__LA_RB_SRSW__Push_Commit( &sSRSW );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_LF__LA_RB_SRSW__Pop_Next_Index -------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__LA_RB_SRSW__Pop_Next_Index )
{
    STg2_UT_LF__LA_RB_SRSW              sSRSW;

    tgCM_UT_LF__LA_RB_SRSW__Init( &sSRSW, 10 );

    tgCM_UT_LF__LA_RB_SRSW__Push_Commit( &sSRSW );
    Test__Expect_EQ(0,tgCM_UT_LF__LA_RB_SRSW__Pop_Next_Index( &sSRSW ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_LF__LA_RB_SRSW__Pop_Commit ------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__LA_RB_SRSW__Pop_Commit )
{
    STg2_UT_LF__LA_RB_SRSW              sSRSW;

    tgCM_UT_LF__LA_RB_SRSW__Init( &sSRSW, 10 );

    tgCM_UT_LF__LA_RB_SRSW__Push_Commit( &sSRSW );
    Test__Expect_EQ(0,tgCM_UT_LF__LA_RB_SRSW__Pop_Next_Index( &sSRSW ));
    tgCM_UT_LF__LA_RB_SRSW__Pop_Commit( &sSRSW );

    TEST_END_METHOD( KTgS_OK );
}
