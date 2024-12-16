/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common [Unit Test] [Test] - Util MT - Profile Sample.c
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

TEST_METHOD( UNIT_TEST__TEST__Profile_Sample_Reset );
TEST_METHOD( UNIT_TEST__TEST__Profile_Sample_Start );
TEST_METHOD( UNIT_TEST__TEST__Profile_Sample_Stop );
TEST_METHOD( UNIT_TEST__TEST__Profile_Sample_Report );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- UNIT_TEST__TEST__UTIL_MT_Profile_Sample ---------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( UNIT_TEST__TEST__UTIL_MT_Profile_Sample )
{
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__Profile_Sample_Reset());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__Profile_Sample_Start());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__Profile_Sample_Stop());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__Profile_Sample_Report());

    TEST_END_METHOD( KTgS_OK );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- UNIT_TEST__TEST__Profile_Sample_Reset ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__Profile_Sample_Reset )
{
    STg2_Profile_Record                 sRecord;

    tgProfile_Sample_Reset( &sRecord );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__Profile_Sample_Start ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__Profile_Sample_Start )
{
    STg2_Profile_Record                 sRecord;
    TgSINT_E64                          iStart;

    tgProfile_Sample_Reset( &sRecord );
    iStart = tgProfile_Sample_Start( &sRecord );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__Profile_Sample_Stop ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__Profile_Sample_Stop )
{
    STg2_Profile_Record                 sRecord;
    TgSINT_E64                          iStart;
    TgSINT_E64                          iEnd;

    tgProfile_Sample_Reset( &sRecord );
    iStart = tgProfile_Sample_Start( &sRecord );
    Unit_Test__Sleep( 1000000 );
    iEnd = tgProfile_Sample_Stop( &sRecord );
    Test__Expect_EQ(true, iEnd > iStart);

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__Profile_Sample_Report ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__Profile_Sample_Report )
{
    STg2_Profile_Record                 sRecord;
    TgSINT_E64                          iStart;
    TgSINT_E64                          iEnd;

    tgProfile_Sample_Reset( &sRecord );
    iStart = tgProfile_Sample_Start( &sRecord );
    Unit_Test__Sleep( 1000000 );
    iEnd = tgProfile_Sample_Stop( &sRecord );
    Test__Expect_EQ(true, iEnd > iStart);
    tgProfile_Sample_Report( &sRecord );
    Test__Expect_EQ(true, sRecord.m_fReport_Total > 0.0F);
    Test__Expect_EQ(true, sRecord.m_fReport_Idle > 0.0F);
    Test__Expect_EQ(true, sRecord.m_fReport_Sample > 0.0F);

    TEST_END_METHOD( KTgS_OK );
}
