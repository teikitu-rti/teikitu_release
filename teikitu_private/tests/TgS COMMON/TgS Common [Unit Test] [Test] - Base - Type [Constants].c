/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common [Unit Test] [Test] - Base - Type [Constants].c
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
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- UNIT_TEST__TEST__Base_Type_Constants ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( UNIT_TEST__TEST__Base_Type_Constants )
{
    Test__Expect_EQ(0.0F, tgCM_CL_F32_Query_R_F32(KTg_BLACK_G10_P709_F32_04));
    Test__Expect_EQ(0.0F, tgCM_CL_F32_Query_G_F32(KTg_BLACK_G10_P709_F32_04));
    Test__Expect_EQ(0.0F, tgCM_CL_F32_Query_B_F32(KTg_BLACK_G10_P709_F32_04));
    Test__Expect_EQ(1.0F, tgCM_CL_F32_Query_A_F32(KTg_BLACK_G10_P709_F32_04));

    Test__Expect_EQ(1.0F, tgCM_CL_F32_Query_R_F32(KTg_WHITE_G10_P709_F32_04));
    Test__Expect_EQ(1.0F, tgCM_CL_F32_Query_G_F32(KTg_WHITE_G10_P709_F32_04));
    Test__Expect_EQ(1.0F, tgCM_CL_F32_Query_B_F32(KTg_WHITE_G10_P709_F32_04));
    Test__Expect_EQ(1.0F, tgCM_CL_F32_Query_A_F32(KTg_WHITE_G10_P709_F32_04));

    Test__Expect_EQ(1.0F, tgCM_CL_F32_Query_R_F32(KTg_RED_G10_P709_F32_04));
    Test__Expect_EQ(0.0F, tgCM_CL_F32_Query_G_F32(KTg_RED_G10_P709_F32_04));
    Test__Expect_EQ(0.0F, tgCM_CL_F32_Query_B_F32(KTg_RED_G10_P709_F32_04));
    Test__Expect_EQ(1.0F, tgCM_CL_F32_Query_A_F32(KTg_RED_G10_P709_F32_04));

    Test__Expect_EQ(0.0F, tgCM_CL_F32_Query_R_F32(KTg_GREEN_G10_P709_F32_04));
    Test__Expect_EQ(1.0F, tgCM_CL_F32_Query_G_F32(KTg_GREEN_G10_P709_F32_04));
    Test__Expect_EQ(0.0F, tgCM_CL_F32_Query_B_F32(KTg_GREEN_G10_P709_F32_04));
    Test__Expect_EQ(1.0F, tgCM_CL_F32_Query_A_F32(KTg_GREEN_G10_P709_F32_04));

    Test__Expect_EQ(0.0F, tgCM_CL_F32_Query_R_F32(KTg_BLUE_G10_P709_F32_04));
    Test__Expect_EQ(0.0F, tgCM_CL_F32_Query_G_F32(KTg_BLUE_G10_P709_F32_04));
    Test__Expect_EQ(1.0F, tgCM_CL_F32_Query_B_F32(KTg_BLUE_G10_P709_F32_04));
    Test__Expect_EQ(1.0F, tgCM_CL_F32_Query_A_F32(KTg_BLUE_G10_P709_F32_04));

    Test__Expect_EQ(1.0F, tgCM_CL_F32_Query_R_F32(KTg_YELLOW_G10_P709_F32_04));
    Test__Expect_EQ(1.0F, tgCM_CL_F32_Query_G_F32(KTg_YELLOW_G10_P709_F32_04));
    Test__Expect_EQ(0.0F, tgCM_CL_F32_Query_B_F32(KTg_YELLOW_G10_P709_F32_04));
    Test__Expect_EQ(1.0F, tgCM_CL_F32_Query_A_F32(KTg_YELLOW_G10_P709_F32_04));

    Test__Expect_EQ(1.0F, tgCM_CL_F32_Query_R_F32(KTg_MAGENTA_G10_P709_F32_04));
    Test__Expect_EQ(0.0F, tgCM_CL_F32_Query_G_F32(KTg_MAGENTA_G10_P709_F32_04));
    Test__Expect_EQ(1.0F, tgCM_CL_F32_Query_B_F32(KTg_MAGENTA_G10_P709_F32_04));
    Test__Expect_EQ(1.0F, tgCM_CL_F32_Query_A_F32(KTg_MAGENTA_G10_P709_F32_04));

    Test__Expect_EQ(0.0F, tgCM_CL_F32_Query_R_F32(KTg_CYAN_G10_P709_F32_04));
    Test__Expect_EQ(1.0F, tgCM_CL_F32_Query_G_F32(KTg_CYAN_G10_P709_F32_04));
    Test__Expect_EQ(1.0F, tgCM_CL_F32_Query_B_F32(KTg_CYAN_G10_P709_F32_04));
    Test__Expect_EQ(1.0F, tgCM_CL_F32_Query_A_F32(KTg_CYAN_G10_P709_F32_04));


    Test__Expect_EQ(0x00u, KTg_BLACK_G10_P709_U32.m_uiRed);
    Test__Expect_EQ(0x00u, KTg_BLACK_G10_P709_U32.m_uiGreen);
    Test__Expect_EQ(0x00u, KTg_BLACK_G10_P709_U32.m_uiBlue);
    Test__Expect_EQ(0xFFu, KTg_BLACK_G10_P709_U32.m_uiAlpha);

    Test__Expect_EQ(0xFFu, KTg_WHITE_G10_P709_U32.m_uiRed);
    Test__Expect_EQ(0xFFu, KTg_WHITE_G10_P709_U32.m_uiGreen);
    Test__Expect_EQ(0xFFu, KTg_WHITE_G10_P709_U32.m_uiBlue);
    Test__Expect_EQ(0xFFu, KTg_WHITE_G10_P709_U32.m_uiAlpha);

    Test__Expect_EQ(0xFFu, KTg_RED_G10_P709_U32.m_uiRed);
    Test__Expect_EQ(0x00u, KTg_RED_G10_P709_U32.m_uiGreen);
    Test__Expect_EQ(0x00u, KTg_RED_G10_P709_U32.m_uiBlue);
    Test__Expect_EQ(0xFFu, KTg_RED_G10_P709_U32.m_uiAlpha);

    Test__Expect_EQ(0x00u, KTg_GREEN_G10_P709_U32.m_uiRed);
    Test__Expect_EQ(0xFFu, KTg_GREEN_G10_P709_U32.m_uiGreen);
    Test__Expect_EQ(0x00u, KTg_GREEN_G10_P709_U32.m_uiBlue);
    Test__Expect_EQ(0xFFu, KTg_GREEN_G10_P709_U32.m_uiAlpha);

    Test__Expect_EQ(0x00u, KTg_BLUE_G10_P709_U32.m_uiRed);
    Test__Expect_EQ(0x00u, KTg_BLUE_G10_P709_U32.m_uiGreen);
    Test__Expect_EQ(0xFFu, KTg_BLUE_G10_P709_U32.m_uiBlue);
    Test__Expect_EQ(0xFFu, KTg_BLUE_G10_P709_U32.m_uiAlpha);

    Test__Expect_EQ(0xFFu, KTg_YELLOW_G10_P709_U32.m_uiRed);
    Test__Expect_EQ(0xFFu, KTg_YELLOW_G10_P709_U32.m_uiGreen);
    Test__Expect_EQ(0x00u, KTg_YELLOW_G10_P709_U32.m_uiBlue);
    Test__Expect_EQ(0xFFu, KTg_YELLOW_G10_P709_U32.m_uiAlpha);

    Test__Expect_EQ(0xFFu, KTg_MAGENTA_G10_P709_U32.m_uiRed);
    Test__Expect_EQ(0x00u, KTg_MAGENTA_G10_P709_U32.m_uiGreen);
    Test__Expect_EQ(0xFFu, KTg_MAGENTA_G10_P709_U32.m_uiBlue);
    Test__Expect_EQ(0xFFu, KTg_MAGENTA_G10_P709_U32.m_uiAlpha);

    Test__Expect_EQ(0x00u, KTg_CYAN_G10_P709_U32.m_uiRed);
    Test__Expect_EQ(0xFFu, KTg_CYAN_G10_P709_U32.m_uiGreen);
    Test__Expect_EQ(0xFFu, KTg_CYAN_G10_P709_U32.m_uiBlue);
    Test__Expect_EQ(0xFFu, KTg_CYAN_G10_P709_U32.m_uiAlpha);

    TEST_END_METHOD( KTgS_OK );
}
