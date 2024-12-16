/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common [Unit Test] [Test] - Util ST - List.c
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

TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__LT__Init );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__LT__Free );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__LT__Push_Front );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__LT__Push_Back );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__LT__Pop_Front );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__LT__Pop_Back );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__LT__Insert );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__LT__Remove );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__LT__Is_Empty );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- UNIT_TEST__TEST__UTIL_ST_List -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( UNIT_TEST__TEST__UTIL_ST_List )
{
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__LT__Init());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__LT__Free());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__LT__Push_Front());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__LT__Push_Back());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__LT__Pop_Front());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__LT__Pop_Back());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__LT__Insert());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__LT__Remove());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__LT__Is_Empty());

    TEST_END_METHOD( KTgS_OK );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- UNIT_TEST__TEST__CM_UT_ST__LT__Init -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__LT__Init )
{
    STg2_UT_ST__LT                      sLT;

    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__LT__Init( &sLT ));
    tgCM_UT_ST__LT__Free( &sLT );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__LT__Free -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__LT__Free )
{
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__LT__Init());
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__LT__Push_Front -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__LT__Push_Front )
{
    STg2_UT_ST__LT                      sLT;
    STg2_UT_ST__LT_Node                 sData[4];

    Test__Expect_EQ(KTgS_OK,tgCM_UT_ST__LT__Init( &sLT ));

    tgCM_UT_ST__LT__Push_Front( &sLT, sData + 0 );
    Test__Expect_EQ(false, tgCM_UT_ST__LT__Is_Empty( &sLT ));
    Test__Expect_EQ(true, sData == tgCM_UT_ST__LT__Pop_Front( &sLT ));
    Test__Expect_EQ(true, tgCM_UT_ST__LT__Is_Empty( &sLT ));
    Test__Expect_EQ(true, nullptr == tgCM_UT_ST__LT__Pop_Front( &sLT ));

    tgCM_UT_ST__LT__Push_Front( &sLT, sData + 0 );
    Test__Expect_EQ(false, tgCM_UT_ST__LT__Is_Empty( &sLT ));
    Test__Expect_EQ(true, sData == tgCM_UT_ST__LT__Pop_Back( &sLT ));
    Test__Expect_EQ(true, tgCM_UT_ST__LT__Is_Empty( &sLT ));
    Test__Expect_EQ(true, nullptr == tgCM_UT_ST__LT__Pop_Back( &sLT ));

    tgCM_UT_ST__LT__Push_Front( &sLT, sData + 0 );
    tgCM_UT_ST__LT__Push_Front( &sLT, sData + 1 );
    tgCM_UT_ST__LT__Push_Front( &sLT, sData + 2 );
    Test__Expect_EQ(true, sData + 2 == tgCM_UT_ST__LT__Pop_Front( &sLT ));
    Test__Expect_EQ(true, sData + 1 == tgCM_UT_ST__LT__Pop_Front( &sLT ));
    Test__Expect_EQ(true, sData + 0 == tgCM_UT_ST__LT__Pop_Front( &sLT ));

    tgCM_UT_ST__LT__Push_Front( &sLT, sData + 0 );
    tgCM_UT_ST__LT__Push_Front( &sLT, sData + 1 );
    tgCM_UT_ST__LT__Push_Front( &sLT, sData + 2 );
    Test__Expect_EQ(true, sData + 0 == tgCM_UT_ST__LT__Pop_Back( &sLT ));
    Test__Expect_EQ(true, sData + 1 == tgCM_UT_ST__LT__Pop_Back( &sLT ));
    Test__Expect_EQ(true, sData + 2 == tgCM_UT_ST__LT__Pop_Back( &sLT ));

    tgCM_UT_ST__LT__Free( &sLT );
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__LT__Push_Back --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__LT__Push_Back )
{
    STg2_UT_ST__LT                      sLT;
    STg2_UT_ST__LT_Node                 sData[4];

    Test__Expect_EQ(KTgS_OK,tgCM_UT_ST__LT__Init( &sLT ));

    tgCM_UT_ST__LT__Push_Back( &sLT, sData + 0 );
    Test__Expect_EQ(false, tgCM_UT_ST__LT__Is_Empty( &sLT ));
    Test__Expect_EQ(true, sData == tgCM_UT_ST__LT__Pop_Back( &sLT ));
    Test__Expect_EQ(true, tgCM_UT_ST__LT__Is_Empty( &sLT ));
    Test__Expect_EQ(true, nullptr == tgCM_UT_ST__LT__Pop_Back( &sLT ));

    tgCM_UT_ST__LT__Push_Back( &sLT, sData + 0 );
    Test__Expect_EQ(false, tgCM_UT_ST__LT__Is_Empty( &sLT ));
    Test__Expect_EQ(true, sData == tgCM_UT_ST__LT__Pop_Front( &sLT ));
    Test__Expect_EQ(true, tgCM_UT_ST__LT__Is_Empty( &sLT ));
    Test__Expect_EQ(true, nullptr == tgCM_UT_ST__LT__Pop_Front( &sLT ));

    tgCM_UT_ST__LT__Push_Back( &sLT, sData + 0 );
    tgCM_UT_ST__LT__Push_Back( &sLT, sData + 1 );
    tgCM_UT_ST__LT__Push_Back( &sLT, sData + 2 );
    Test__Expect_EQ(true, sData + 2 == tgCM_UT_ST__LT__Pop_Back( &sLT ));
    Test__Expect_EQ(true, sData + 1 == tgCM_UT_ST__LT__Pop_Back( &sLT ));
    Test__Expect_EQ(true, sData + 0 == tgCM_UT_ST__LT__Pop_Back( &sLT ));

    tgCM_UT_ST__LT__Push_Back( &sLT, sData + 0 );
    tgCM_UT_ST__LT__Push_Back( &sLT, sData + 1 );
    tgCM_UT_ST__LT__Push_Back( &sLT, sData + 2 );
    Test__Expect_EQ(true, sData + 0 == tgCM_UT_ST__LT__Pop_Front( &sLT ));
    Test__Expect_EQ(true, sData + 1 == tgCM_UT_ST__LT__Pop_Front( &sLT ));
    Test__Expect_EQ(true, sData + 2 == tgCM_UT_ST__LT__Pop_Front( &sLT ));

    tgCM_UT_ST__LT__Free( &sLT );
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__LT__Pop_Front --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__LT__Pop_Front )
{
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__LT__Push_Front());
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__LT__Pop_Back ---------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__LT__Pop_Back )
{
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__LT__Push_Back());
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__LT__Insert ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__LT__Insert )
{
    STg2_UT_ST__LT                      sLT;
    STg2_UT_ST__LT_Node                 sData[4];

    Test__Expect_EQ(KTgS_OK,tgCM_UT_ST__LT__Init( &sLT ));

    tgCM_UT_ST__LT__Push_Front( &sLT, sData + 0 );
    tgCM_UT_ST__LT__Push_Front( &sLT, sData + 1 );
    tgCM_UT_ST__LT__Push_Front( &sLT, sData + 2 );
    tgCM_UT_ST__LT__Insert( sData + 1, sData + 3 );
    Test__Expect_EQ(true, sData + 2 == tgCM_UT_ST__LT__Pop_Front( &sLT ));
    Test__Expect_EQ(true, sData + 3 == tgCM_UT_ST__LT__Pop_Front( &sLT ));
    Test__Expect_EQ(true, sData + 1 == tgCM_UT_ST__LT__Pop_Front( &sLT ));
    Test__Expect_EQ(true, sData + 0 == tgCM_UT_ST__LT__Pop_Front( &sLT ));

    tgCM_UT_ST__LT__Free( &sLT );
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__LT__Remove ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__LT__Remove )
{
    STg2_UT_ST__LT                      sLT;
    STg2_UT_ST__LT_Node                 sData[4];

    Test__Expect_EQ(KTgS_OK,tgCM_UT_ST__LT__Init( &sLT ));

    tgCM_UT_ST__LT__Push_Front( &sLT, sData + 0 );
    tgCM_UT_ST__LT__Push_Front( &sLT, sData + 1 );
    tgCM_UT_ST__LT__Push_Front( &sLT, sData + 2 );
    tgCM_UT_ST__LT__Remove( sData + 1 );
    Test__Expect_EQ(true, sData + 2 == tgCM_UT_ST__LT__Pop_Front( &sLT ));
    Test__Expect_EQ(true, sData + 0 == tgCM_UT_ST__LT__Pop_Front( &sLT ));

    tgCM_UT_ST__LT__Free( &sLT );
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__LT__Is_Empty ---------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__LT__Is_Empty )
{
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__LT__Push_Front());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__LT__Push_Back());
    TEST_END_METHOD( KTgS_OK );
}
