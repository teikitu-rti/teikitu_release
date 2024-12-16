/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common [Unit Test] [Test] - Util ST - Colour.c
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

TEST_METHOD( UNIT_TEST__TEST__CM_CL_F32_Init_F32 );
TEST_METHOD( UNIT_TEST__TEST__CM_CL_F32_Init_U32 );
TEST_METHOD( UNIT_TEST__TEST__CM_CL_F32_Brightness_U16 );
TEST_METHOD( UNIT_TEST__TEST__CM_CL_F32_Brightness_F32 );
TEST_METHOD( UNIT_TEST__TEST__CM_CL_F32_Lightness );
TEST_METHOD( UNIT_TEST__TEST__CM_CL_F32_Luminance );
TEST_METHOD( UNIT_TEST__TEST__CM_CL_F32_Query_R_F32 );
TEST_METHOD( UNIT_TEST__TEST__CM_CL_F32_Query_G_F32 );
TEST_METHOD( UNIT_TEST__TEST__CM_CL_F32_Query_B_F32 );
TEST_METHOD( UNIT_TEST__TEST__CM_CL_F32_Query_A_F32 );

TEST_METHOD( UNIT_TEST__TEST__CM_CL_U32_Init_U08 );
TEST_METHOD( UNIT_TEST__TEST__CM_CL_U32_Init_U32 );
TEST_METHOD( UNIT_TEST__TEST__CM_CL_U32_Init_F32 );
TEST_METHOD( UNIT_TEST__TEST__CM_CL_U32_Brightness_U16 );
TEST_METHOD( UNIT_TEST__TEST__CM_CL_U32_Brightness_F32 );
TEST_METHOD( UNIT_TEST__TEST__CM_CL_U32_Lightness );
TEST_METHOD( UNIT_TEST__TEST__CM_CL_U32_Luminance );
TEST_METHOD( UNIT_TEST__TEST__CM_CL_U32_Query_R_U32 );
TEST_METHOD( UNIT_TEST__TEST__CM_CL_U32_Query_G_U32 );
TEST_METHOD( UNIT_TEST__TEST__CM_CL_U32_Query_B_U32 );
TEST_METHOD( UNIT_TEST__TEST__CM_CL_U32_Query_A_U32 );
TEST_METHOD( UNIT_TEST__TEST__CM_CL_U32_Query_R_F32 );
TEST_METHOD( UNIT_TEST__TEST__CM_CL_U32_Query_G_F32 );
TEST_METHOD( UNIT_TEST__TEST__CM_CL_U32_Query_B_F32 );
TEST_METHOD( UNIT_TEST__TEST__CM_CL_U32_Query_A_F32 );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- UNIT_TEST__TEST__UTIL_ST_Colour ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( UNIT_TEST__TEST__UTIL_ST_Colour )
{
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_CL_F32_Init_F32());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_CL_F32_Init_U32());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_CL_F32_Brightness_U16());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_CL_F32_Brightness_F32());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_CL_F32_Lightness());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_CL_F32_Luminance());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_CL_F32_Query_R_F32());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_CL_F32_Query_G_F32());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_CL_F32_Query_B_F32());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_CL_F32_Query_A_F32());

    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_CL_U32_Init_U08());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_CL_U32_Init_U32());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_CL_U32_Init_F32());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_CL_U32_Brightness_U16());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_CL_U32_Brightness_F32());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_CL_U32_Lightness());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_CL_U32_Luminance());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_CL_U32_Query_R_U32());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_CL_U32_Query_G_U32());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_CL_U32_Query_B_U32());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_CL_U32_Query_A_U32());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_CL_U32_Query_R_F32());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_CL_U32_Query_G_F32());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_CL_U32_Query_B_F32());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_CL_U32_Query_A_F32());


    TEST_END_METHOD( KTgS_OK );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- UNIT_TEST__TEST__CM_CL_F32_Init_F32 -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_CL_F32_Init_F32 )
{
    TgVEC_F32_04_1                      v4_0;

    v4_0 = tgCM_CL_F32_Init_F32( 0.1F, 0.15F, 0.5F, 1.0F );

    Test__Expect_EQ(true, tgCM_NR0_F32( 0.1F - tgCM_CL_F32_Query_R_F32( v4_0 )));
    Test__Expect_EQ(true, tgCM_NR0_F32( 0.15F - tgCM_CL_F32_Query_G_F32( v4_0 )));
    Test__Expect_EQ(true, tgCM_NR0_F32( 0.5F - tgCM_CL_F32_Query_B_F32( v4_0 )));
    Test__Expect_EQ(true, tgCM_NR0_F32( 1.0F - tgCM_CL_F32_Query_A_F32( v4_0 )));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_CL_F32_Init_U32 -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_CL_F32_Init_U32 )
{
    TgVEC_F32_04_1                      v4_0;

    v4_0 = tgCM_CL_F32_Init_U32( TgCOLOUR_FROM_RGBA( 0x10u, 0x15u, 0x50u, 0xFFu ) );

    Test__Expect_EQ(true, tgCM_NR0_F32( 16.0F / 255.0F - tgCM_CL_F32_Query_R_F32( v4_0 ) ));
    Test__Expect_EQ(true, tgCM_NR0_F32( 21.0F / 255.0F - tgCM_CL_F32_Query_G_F32( v4_0 ) ));
    Test__Expect_EQ(true, tgCM_NR0_F32( 80.0F / 255.0F - tgCM_CL_F32_Query_B_F32( v4_0 ) ));
    Test__Expect_EQ(1.0F, tgCM_CL_F32_Query_A_F32( v4_0 ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_CL_F32_Brightness_U16 -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_CL_F32_Brightness_U16 )
{
    TgVEC_F32_04_1                      v4_0;

    v4_0 = tgCM_CL_F32_Init_F32( 0.1F, 0.15F, 0.5F, 1.0F );

    Test__Expect_EQ(16383u, tgCM_CL_F32_Brightness_U16( v4_0 ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_CL_F32_Brightness_F32 -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_CL_F32_Brightness_F32 )
{
    TgVEC_F32_04_1                      v4_0;

    v4_0 = tgCM_CL_F32_Init_F32( 0.1F, 0.15F, 0.5F, 1.0F );

    Test__Expect_EQ(0.25F, tgCM_CL_F32_Brightness_F32( v4_0 ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_CL_F32_Lightness ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_CL_F32_Lightness )
{
    TgVEC_F32_04_1                      v4_0;

    v4_0 = tgCM_CL_F32_Init_F32( 0.1F, 0.15F, 0.5F, 1.0F );

    Test__Expect_NE(0, tgCM_NR0_F32( tgCM_CL_F32_Lightness( v4_0 ) - 0.3F ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_CL_F32_Luminance ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_CL_F32_Luminance )
{
    TgVEC_F32_04_1                      v4_0;

    v4_0 = tgCM_CL_F32_Init_F32( 0.1F, 0.15F, 0.5F, 1.0F );

    Test__Expect_EQ(true, tgCM_NR0_F32( 0.3f*0.1F + 0.59f*0.15F + 0.11f*0.5F - tgCM_CL_F32_Luminance( v4_0 )));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_CL_F32_Query_R_F32 ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_CL_F32_Query_R_F32 )
{
    TgVEC_F32_04_1                      v4_0;

    v4_0 = tgCM_CL_F32_Init_F32( 0.1F, 0.15F, 0.5F, 1.0F );

    Test__Expect_EQ(true, tgCM_NR0_F32( 0.1F - tgCM_CL_F32_Query_R_F32( v4_0 )));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_CL_F32_Query_G_F32 ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_CL_F32_Query_G_F32 )
{
    TgVEC_F32_04_1                      v4_0;

    v4_0 = tgCM_CL_F32_Init_F32( 0.1F, 0.15F, 0.5F, 1.0F );

    Test__Expect_EQ(true, tgCM_NR0_F32( 0.15F - tgCM_CL_F32_Query_G_F32( v4_0 )));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_CL_F32_Query_B_F32 ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_CL_F32_Query_B_F32 )
{
    TgVEC_F32_04_1                      v4_0;

    v4_0 = tgCM_CL_F32_Init_F32( 0.1F, 0.15F, 0.5F, 1.0F );

    Test__Expect_EQ(true, tgCM_NR0_F32( 0.5F - tgCM_CL_F32_Query_B_F32( v4_0 )));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_CL_F32_Query_A_F32 ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_CL_F32_Query_A_F32 )
{
    TgVEC_F32_04_1                      v4_0;

    v4_0 = tgCM_CL_F32_Init_F32( 0.1F, 0.15F, 0.5F, 1.0F );

    Test__Expect_EQ(true, tgCM_NR0_F32( 1.0F - tgCM_CL_F32_Query_A_F32( v4_0 )));

    TEST_END_METHOD( KTgS_OK );
}



/* ---- UNIT_TEST__TEST__CM_CL_U32_Init_U08 -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_CL_U32_Init_U08 )
{
    TgCOLOUR32                          uiCol;

    uiCol = tgCM_CL_U32_Init_U08( 0x10u, 0x15u, 0x50u, 0xFFu );

    Test__Expect_EQ(0x10u, uiCol.m_uiRed);
    Test__Expect_EQ(0x15u, uiCol.m_uiGreen);
    Test__Expect_EQ(0x50u, uiCol.m_uiBlue);
    Test__Expect_EQ(0xFFu, uiCol.m_uiAlpha);

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_CL_U32_Init_U32 -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_CL_U32_Init_U32 )
{
    TgCOLOUR32                          uiCol;

    uiCol = tgCM_CL_U32_Init_U32( TgCOLOUR_FROM_RGBA( 0x10u, 0x15u, 0x50u, 0xFFu ) );

    Test__Expect_EQ(0x10u, uiCol.m_uiRed);
    Test__Expect_EQ(0x15u, uiCol.m_uiGreen);
    Test__Expect_EQ(0x50u, uiCol.m_uiBlue);
    Test__Expect_EQ(0xFFu, uiCol.m_uiAlpha);

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_CL_U32_Init_F32 -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_CL_U32_Init_F32 )
{
    TgCOLOUR32                          uiCol;
    TgVEC_F32_04_1                      v4_0;

    v4_0 = tgCM_CL_F32_Init_F32( 16.0F / 255.0F, 21.0F / 255.0F, 80.0F / 255.0F, 1.0F );
    uiCol = tgCM_CL_U32_Init_F32( v4_0 );
    Test__Expect_EQ(0x10u, uiCol.m_uiRed);
    Test__Expect_EQ(0x15u, uiCol.m_uiGreen);
    Test__Expect_EQ(0x50u, uiCol.m_uiBlue);
    Test__Expect_EQ(0xFFu, uiCol.m_uiAlpha);

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_CL_U32_Brightness_U16 -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_CL_U32_Brightness_U16 )
{
    TgCOLOUR32                          uiCol;

    uiCol = tgCM_CL_U32_Init_U08( 0xC8, 0x64, 0xB4, 0xFF );

    Test__Expect_EQ(41120u, tgCM_CL_U32_Brightness_U16( uiCol ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_CL_U32_Brightness_F32 -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_CL_U32_Brightness_F32 )
{
    TgCOLOUR32                          uiCol;

    uiCol = tgCM_CL_U32_Init_U08( 0xC8, 0x64, 0xB4, 0xFF );

    Test__Expect_NE(0, tgCM_NR0_F32( tgCM_CL_U32_Brightness_F32( uiCol ) - 160.0F / 255.0F ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_CL_U32_Lightness ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_CL_U32_Lightness )
{
    TgCOLOUR32                          uiCol;

    uiCol = tgCM_CL_U32_Init_U08( 0xC8, 0x64, 0xB4, 0xFF );

    Test__Expect_NE(0, tgCM_NR0_F32( tgCM_CL_U32_Lightness( uiCol ) - 150.0F / 255.0F ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_CL_U32_Luminance ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_CL_U32_Luminance )
{
    TgCOLOUR32                          uiCol;

    uiCol = tgCM_CL_U32_Init_U08( 0xC8, 0x64, 0xB4, 0xFF );

    Test__Expect_NE(0, tgCM_NR0_F32( tgCM_CL_U32_Luminance( uiCol ) - 0.54431373F ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_CL_U32_Query_R_U32 ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_CL_U32_Query_R_U32 )
{
    TgCOLOUR32                          uiCol;

    uiCol = tgCM_CL_U32_Init_U08( 0xC8, 0x64, 0xB4, 0xFF );

    Test__Expect_EQ(0xC8u, tgCM_CL_U32_Query_R_U32( uiCol ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_CL_U32_Query_G_U32 ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_CL_U32_Query_G_U32 )
{
    TgCOLOUR32                          uiCol;

    uiCol = tgCM_CL_U32_Init_U08( 0xC8, 0x64, 0xB4, 0xFF );

    Test__Expect_EQ(0x64u, tgCM_CL_U32_Query_G_U32( uiCol ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_CL_U32_Query_B_U32 ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_CL_U32_Query_B_U32 )
{
    TgCOLOUR32                          uiCol;

    uiCol = tgCM_CL_U32_Init_U08( 0xC8, 0x64, 0xB4, 0xFF );

    Test__Expect_EQ(0xB4u, tgCM_CL_U32_Query_B_U32( uiCol ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_CL_U32_Query_A_U32 ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_CL_U32_Query_A_U32 )
{
    TgCOLOUR32                          uiCol;

    uiCol = tgCM_CL_U32_Init_U08( 0xC8, 0x64, 0xB4, 0xFF );

    Test__Expect_EQ(0xFFu, tgCM_CL_U32_Query_A_U32( uiCol ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_CL_U32_Query_R_F32 ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_CL_U32_Query_R_F32 )
{
    TgCOLOUR32                          uiCol;

    uiCol = tgCM_CL_U32_Init_U08( 0xC8, 0x64, 0xB4, 0xFF );

    Test__Expect_NE(0, tgCM_NR0_F32( tgCM_CL_U32_Query_R_F32( uiCol ) - 200.0F / 255.0F ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_CL_U32_Query_G_F32 ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_CL_U32_Query_G_F32 )
{
    TgCOLOUR32                          uiCol;

    uiCol = tgCM_CL_U32_Init_U08( 0xC8, 0x64, 0xB4, 0xFF );

    Test__Expect_NE(0, tgCM_NR0_F32( tgCM_CL_U32_Query_G_F32( uiCol ) - 100.0F / 255.0F ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_CL_U32_Query_B_F32 ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_CL_U32_Query_B_F32 )
{
    TgCOLOUR32                          uiCol;

    uiCol = tgCM_CL_U32_Init_U08( 0xC8, 0x64, 0xB4, 0xFF );

    Test__Expect_NE(0, tgCM_NR0_F32( tgCM_CL_U32_Query_B_F32( uiCol ) - 180.0F / 255.0F ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_CL_U32_Query_A_F32 ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_CL_U32_Query_A_F32 )
{
    TgCOLOUR32                          uiCol;

    uiCol = tgCM_CL_U32_Init_U08( 0xC8, 0x64, 0xB4, 0xFF );

    Test__Expect_NE(0, tgCM_NR0_F32( tgCM_CL_U32_Query_A_F32( uiCol ) - 255.0F / 255.0F ));

    TEST_END_METHOD( KTgS_OK );
}
