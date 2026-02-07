/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common [Unit Test] [Test] - Profile.c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if TgCOMPILE__PROFILE
/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TEST_METHOD( UNIT_TEST__TEST__PF_Init );
TEST_METHOD( UNIT_TEST__TEST__PF_Boot );
TEST_METHOD( UNIT_TEST__TEST__PF_Stop );
TEST_METHOD( UNIT_TEST__TEST__PF_Free );
TEST_METHOD( UNIT_TEST__TEST__PF_Update );
TEST_METHOD( UNIT_TEST__TEST__PF_Query_Init );
TEST_METHOD( UNIT_TEST__TEST__PF_Query_Boot );
TEST_METHOD( UNIT_TEST__TEST__PF_Query_Fixed_Memory );
TEST_METHOD( UNIT_TEST__TEST__PF_Report_Module );
TEST_METHOD( UNIT_TEST__TEST__PF_Mark_Init );
TEST_METHOD( UNIT_TEST__TEST__PF_Mark_Start );
TEST_METHOD( UNIT_TEST__TEST__PF_Mark_Stop );
TEST_METHOD( UNIT_TEST__TEST__PF_Mark_Reset );
TEST_METHOD( UNIT_TEST__TEST__PF_Query_Name );
TEST_METHOD( UNIT_TEST__TEST__PF_Query_Total_Time_Cached );
TEST_METHOD( UNIT_TEST__TEST__PF_TL_Init );
TEST_METHOD( UNIT_TEST__TEST__PF_TL_Boot );
TEST_METHOD( UNIT_TEST__TEST__PF_TL_Stop );
TEST_METHOD( UNIT_TEST__TEST__PF_TL_Free );
TEST_METHOD( UNIT_TEST__TEST__PF_TL_Update );
TEST_METHOD( UNIT_TEST__TEST__PF_TL_Query_Init );
TEST_METHOD( UNIT_TEST__TEST__PF_TL_Query_Boot );
TEST_METHOD( UNIT_TEST__TEST__PF_TL_Query_Fixed_Memory );
TEST_METHOD( UNIT_TEST__TEST__PF_TL_Report_Module );
TEST_METHOD( UNIT_TEST__TEST__PF_TL_Mark_Init );
TEST_METHOD( UNIT_TEST__TEST__PF_TL_Mark_Start );
TEST_METHOD( UNIT_TEST__TEST__PF_TL_Mark_Stop );
TEST_METHOD( UNIT_TEST__TEST__PF_TL_Mark_Reset );
TEST_METHOD( UNIT_TEST__TEST__PF_TL_Query_Name );
TEST_METHOD( UNIT_TEST__TEST__PF_TL_Query_Total_Time_Cached );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

static TgUINT_E32_A                         g_nuiProfile_Tag, g_nuiProfile_TL_Tag;




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- UNIT_TEST__TEST__COMMON_Profile ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( UNIT_TEST__TEST__COMMON_Profile )
{
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__PF_Init());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__PF_Boot());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__PF_Stop());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__PF_Free());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__PF_Update());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__PF_Query_Init());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__PF_Query_Boot());

    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__PF_Query_Fixed_Memory());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__PF_Report_Module());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__PF_Mark_Init());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__PF_Mark_Start());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__PF_Mark_Stop());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__PF_Mark_Reset());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__PF_Query_Name());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__PF_Query_Total_Time_Cached());

    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__PF_TL_Init());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__PF_TL_Boot());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__PF_TL_Stop());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__PF_TL_Free());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__PF_TL_Update());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__PF_TL_Query_Init());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__PF_TL_Query_Boot());
    
    tgPF_TL_Init();
    tgPF_TL_Boot();

    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__PF_TL_Query_Fixed_Memory());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__PF_TL_Report_Module());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__PF_TL_Mark_Init());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__PF_TL_Mark_Start());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__PF_TL_Mark_Stop());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__PF_TL_Mark_Reset());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__PF_TL_Query_Name());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__PF_TL_Query_Total_Time_Cached());

    tgPF_TL_Stop();
    tgPF_TL_Free();

    TEST_END_METHOD( KTgS_OK );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- UNIT_TEST__TEST__PF_Init ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__PF_Init )
{
    /* Due to their nature, module management functions can not be unit tested */

   TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__PF_Boot ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__PF_Boot )
{
    /* Due to their nature, module management functions can not be unit tested */

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__PF_Stop ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__PF_Stop )
{
    /* Due to their nature, module management functions can not be unit tested */

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__PF_Free ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__PF_Free )
{
    /* Due to their nature, module management functions can not be unit tested */

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__PF_Update ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__PF_Update )
{
    /* Due to their nature, module management functions can not be unit tested */

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__PF_Query_Init ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__PF_Query_Init )
{
    Test__Expect_EQ(true, tgPF_Query_Init());

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__PF_Query_Boot ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__PF_Query_Boot )
{
    Test__Expect_EQ(true, tgPF_Query_Boot());

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__PF_Query_Fixed_Memory ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__PF_Query_Fixed_Memory )
{
    tgPF_Query_Fixed_Memory();

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__PF_Report_Module ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__PF_Report_Module )
{
    TgCHAR_U8                           sOutput_Buffer[4096];
    STg2_Output_MEM                     sOutput;

    tgIO_OM__Open( &sOutput, (TgUINT_E08_P)sOutput_Buffer, 4096 * sizeof( TgCHAR_U8 ), nullptr );
    tgPF_Report_Module( (STg2_Output_P)&sOutput );
    sOutput_Buffer[sOutput.m_nbyData_Current < 4096 ? sOutput.m_nbyData_Current : 4095] = 0;
    tgIO_OM__Close( &sOutput.m_sOutput );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__PF_Mark_Init -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__PF_Mark_Init )
{
    TgCHAR_U8                           szTagName[64];
    TgPROFILE_ID                        tiProfile;

    tgUSZ_PrintF( szTagName, 64, u8"PROFILE_TEST_%d", TgSTD_ATOMIC(fetch_add)( &g_nuiProfile_Tag, 1 ) );
    tiProfile = tgPF_Mark_Init( szTagName );
    Test__Expect_EQ(true, tiProfile.m_uiKI != KTgPROFILE_ID__INVALID.m_uiKI)

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__PF_Mark_Start ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__PF_Mark_Start )
{
    TgCHAR_U8                           szTagName[64];
    TgPROFILE_ID                        tiProfile;
    TgPROFILE_CALL_ID                   tiProfile_Call;

    tgUSZ_PrintF( szTagName, 64, u8"PROFILE_TEST_%d", TgSTD_ATOMIC(fetch_add)( &g_nuiProfile_Tag, 1 ) );
    tiProfile = tgPF_Mark_Init( szTagName );
    Test__Expect_EQ(true, tiProfile.m_uiKI != KTgPROFILE_ID__INVALID.m_uiKI)

    tiProfile_Call = tgPF_Mark_Start( tiProfile );
    Test__Expect_EQ(true, tiProfile_Call.m_uiKI != KTgPROFILE_CALL_ID__INVALID.m_uiKI)

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__PF_Mark_Stop -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__PF_Mark_Stop )
{
    TgCHAR_U8                           szTagName[64];
    TgPROFILE_ID                        tiProfile;
    TgPROFILE_CALL_ID                   tiProfile_Call;

    tgUSZ_PrintF( szTagName, 64, u8"PROFILE_TEST_%d", TgSTD_ATOMIC(fetch_add)( &g_nuiProfile_Tag, 1 ) );
    tiProfile = tgPF_Mark_Init( szTagName );
    Test__Expect_EQ(true, tiProfile.m_uiKI != KTgPROFILE_ID__INVALID.m_uiKI)

    tiProfile_Call = tgPF_Mark_Start( tiProfile );
    Test__Expect_EQ(true, tiProfile_Call.m_uiKI != KTgPROFILE_CALL_ID__INVALID.m_uiKI);

    Unit_Test__Sleep( 3000000 );
    tgPF_Mark_Stop( tiProfile, tiProfile_Call );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__PF_Mark_Reset ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__PF_Mark_Reset )
{
    TgCHAR_U8                           szTagName[64];
    TgPROFILE_ID                        tiProfile;
    TgPROFILE_CALL_ID                   tiProfile_Call;

    tgUSZ_PrintF( szTagName, 64, u8"PROFILE_TEST_%d", TgSTD_ATOMIC(fetch_add)( &g_nuiProfile_Tag, 1 ) );
    tiProfile = tgPF_Mark_Init( szTagName );
    Test__Expect_EQ(true, tiProfile.m_uiKI != KTgPROFILE_ID__INVALID.m_uiKI)

    tiProfile_Call = tgPF_Mark_Start( tiProfile );
    Test__Expect_EQ(true, tiProfile_Call.m_uiKI != KTgPROFILE_CALL_ID__INVALID.m_uiKI);

    Unit_Test__Sleep( 3000000 );
    tgPF_Mark_Stop( tiProfile, tiProfile_Call );
    Test__Expect_EQ(0.0, tgPF_Query_Total_Time_Cached( tiProfile ));

    tgPF_Update( 0.0F );
    Test__Expect_NE(0.0, tgPF_Query_Total_Time_Cached( tiProfile ));

    tgPF_Mark_Reset( tiProfile );
    Test__Expect_EQ(0.0, tgPF_Query_Total_Time_Cached( tiProfile ));

    tiProfile_Call = tgPF_Mark_Start( tiProfile );
    Test__Expect_EQ(true, tiProfile_Call.m_uiKI != KTgPROFILE_CALL_ID__INVALID.m_uiKI);

    Unit_Test__Sleep( 3000000 );
    tgPF_Mark_Stop( tiProfile, tiProfile_Call );
    Test__Expect_EQ(0.0, tgPF_Query_Total_Time_Cached( tiProfile ));

    tgPF_Update( 0.0F );
    Test__Expect_NE(0.0, tgPF_Query_Total_Time_Cached( tiProfile ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__PF_Query_Name ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__PF_Query_Name )
{
    TgCHAR_U8                           szTagName[2][64];
    TgPROFILE_ID                        tiProfile[2];
    TgSINT_E08                          iRet;

    TgCOMPILER_ASSERT(64 == sizeof(szTagName[0]),);

    tgUSZ_PrintF( szTagName[0], sizeof(szTagName[0]), u8"PROFILE_TEST_%d", TgSTD_ATOMIC(fetch_add)( &g_nuiProfile_Tag, 1 ) );
    tiProfile[0] = tgPF_Mark_Init( szTagName[0] );
    Test__Expect_EQ(true, tiProfile[0].m_uiKI != KTgPROFILE_ID__INVALID.m_uiKI)

    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, tgPF_Query_Name( tiProfile[0] ), KTgMAX_RSIZE, 0, szTagName[0], sizeof( szTagName[0] ), 0 )) && (0 == iRet));

    tgUSZ_PrintF( szTagName[1], sizeof(szTagName[1]), u8"PROFILE_TEST_%d", TgSTD_ATOMIC(fetch_add)( &g_nuiProfile_Tag, 1 ) );
    tiProfile[1] = tgPF_Mark_Init( szTagName[1] );
    Test__Expect_EQ(true, tiProfile[1].m_uiKI != KTgPROFILE_ID__INVALID.m_uiKI)

    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, tgPF_Query_Name( tiProfile[1] ), KTgMAX_RSIZE, 0, szTagName[1], sizeof( szTagName[1] ), 0 )) && (0 == iRet));
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, tgPF_Query_Name( tiProfile[0] ), KTgMAX_RSIZE, 0, szTagName[0], sizeof( szTagName[0] ), 0 )) && (0 == iRet));

    tgUSZ_Copy( szTagName[1], sizeof( szTagName[1] ), szTagName[0], sizeof( szTagName[0] ) );
    tgMM_Set_U08_0x00( szTagName[0], sizeof( szTagName[0] ) );
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, tgPF_Query_Name( tiProfile[0] ), KTgMAX_RSIZE, 0, szTagName[1], sizeof( szTagName[1] ), 0 )) && (0 == iRet));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__PF_Query_Total_Time_Cached ------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__PF_Query_Total_Time_Cached )
{
    TgCHAR_U8                           szTagName[64];
    TgPROFILE_ID                        tiProfile;
    TgPROFILE_CALL_ID                   tiProfile_Call;

    tgUSZ_PrintF( szTagName, 64, u8"PROFILE_TEST_%d", TgSTD_ATOMIC(fetch_add)( &g_nuiProfile_Tag, 1 ) );
    tiProfile = tgPF_Mark_Init( szTagName );
    Test__Expect_EQ(true, tiProfile.m_uiKI != KTgPROFILE_ID__INVALID.m_uiKI)

    tiProfile_Call = tgPF_Mark_Start( tiProfile );
    Test__Expect_EQ(true, tiProfile_Call.m_uiKI != KTgPROFILE_CALL_ID__INVALID.m_uiKI);

    Unit_Test__Sleep( 3000000 );
    tgPF_Mark_Stop( tiProfile, tiProfile_Call );
    Test__Expect_EQ(0.0, tgPF_Query_Total_Time_Cached( tiProfile ));

    tgPF_Update( 0.0F );
    Test__Expect_NE(0.0, tgPF_Query_Total_Time_Cached( tiProfile ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__PF_TL_Init ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__PF_TL_Init )
{
    /* Due to their nature, module management functions can not be unit tested */

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__PF_TL_Boot ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__PF_TL_Boot )
{
    /* Due to their nature, module management functions can not be unit tested */

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__PF_TL_Stop ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__PF_TL_Stop )
{
    /* Due to their nature, module management functions can not be unit tested */

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__PF_TL_Free ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__PF_TL_Free )
{
    /* Due to their nature, module management functions can not be unit tested */

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__PF_TL_Update -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__PF_TL_Update )
{
    /* Due to their nature, module management functions can not be unit tested */

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__PF_TL_Query_Init ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__PF_TL_Query_Init )
{
    Test__Expect_EQ(false, tgPF_TL_Query_Init());

    tgPF_TL_Init();
    Test__Expect_EQ(true, tgPF_TL_Query_Init());

    tgPF_TL_Free();
    Test__Expect_EQ(false, tgPF_TL_Query_Init());

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__PF_TL_Query_Boot ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__PF_TL_Query_Boot )
{
    Test__Expect_EQ(false, tgPF_TL_Query_Boot());

    tgPF_TL_Init();
    tgPF_TL_Boot();
    Test__Expect_EQ(true, tgPF_TL_Query_Boot());

    tgPF_TL_Stop();
    tgPF_TL_Free();
    Test__Expect_EQ(false, tgPF_TL_Query_Boot());

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__PF_TL_Query_Fixed_Memory -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__PF_TL_Query_Fixed_Memory )
{
    tgPF_TL_Query_Fixed_Memory();

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__PF_TL_Report_Module ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__PF_TL_Report_Module )
{
    TgCHAR_U8                           sOutput_Buffer[4096];
    STg2_Output_MEM                     sOutput;

    tgIO_OM__Open( &sOutput, (TgUINT_E08_P)sOutput_Buffer, 4096 * sizeof( TgCHAR_U8 ), nullptr );
    tgPF_TL_Report_Module( (STg2_Output_P)&sOutput );
    sOutput_Buffer[sOutput.m_nbyData_Current < 4096 ? sOutput.m_nbyData_Current : 4095] = 0;
    tgIO_OM__Close( &sOutput.m_sOutput );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__PF_TL_Mark_Init ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__PF_TL_Mark_Init )
{
    TgCHAR_U8                           szTagName[64];
    TgPROFILE_TL_ID                     tiProfile_TL;

    tgUSZ_PrintF( szTagName, 64, u8"PROFILE_TEST_%d", TgSTD_ATOMIC(fetch_add)( &g_nuiProfile_Tag, 1 ) );
    tiProfile_TL = tgPF_TL_Mark_Init( szTagName );
    Test__Expect_EQ(true, tiProfile_TL.m_uiKI != KTgPROFILE_ID__INVALID.m_uiKI)

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__PF_TL_Mark_Start ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__PF_TL_Mark_Start )
{
    TgCHAR_U8                           szTagName[64];
    TgPROFILE_TL_ID                     tiProfile_TL;
    TgPROFILE_TL_CALL_ID                tiProfile_TL_Call;

    tgUSZ_PrintF( szTagName, 64, u8"PROFILE_TEST_%d", TgSTD_ATOMIC(fetch_add)( &g_nuiProfile_Tag, 1 ) );
    tiProfile_TL = tgPF_TL_Mark_Init( szTagName );
    Test__Expect_EQ(true, tiProfile_TL.m_uiKI != KTgPROFILE_ID__INVALID.m_uiKI)

    tiProfile_TL_Call = tgPF_TL_Mark_Start( tiProfile_TL );
    Test__Expect_EQ(true, tiProfile_TL_Call.m_uiKI != KTgPROFILE_TL_CALL_ID__INVALID.m_uiKI);

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__PF_TL_Mark_Stop ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__PF_TL_Mark_Stop )
{
    TgCHAR_U8                           szTagName[64];
    TgPROFILE_TL_ID                     tiProfile_TL;
    TgPROFILE_TL_CALL_ID                tiProfile_TL_Call;

    tgUSZ_PrintF( szTagName, 64, u8"PROFILE_TEST_%d", TgSTD_ATOMIC(fetch_add)( &g_nuiProfile_Tag, 1 ) );
    tiProfile_TL = tgPF_TL_Mark_Init( szTagName );
    Test__Expect_EQ(true, tiProfile_TL.m_uiKI != KTgPROFILE_ID__INVALID.m_uiKI)

    tiProfile_TL_Call = tgPF_TL_Mark_Start( tiProfile_TL );
    Test__Expect_EQ(true, tiProfile_TL_Call.m_uiKI != KTgPROFILE_TL_CALL_ID__INVALID.m_uiKI);

    Unit_Test__Sleep( 3000000 );
    tgPF_TL_Mark_Stop( tiProfile_TL, tiProfile_TL_Call );
    Test__Expect_EQ(0.0, tgPF_TL_Query_Total_Time_Cached( tiProfile_TL ));

    tgPF_TL_Update( 0.0F );
    Test__Expect_NE(0.0, tgPF_TL_Query_Total_Time_Cached( tiProfile_TL ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__PF_TL_Mark_Reset ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__PF_TL_Mark_Reset )
{
    TgCHAR_U8                           szTagName[64];
    TgPROFILE_TL_ID                     tiProfile_TL;
    TgPROFILE_TL_CALL_ID                tiProfile_TL_Call;

    tgUSZ_PrintF( szTagName, 64, u8"PROFILE_TEST_%d", TgSTD_ATOMIC(fetch_add)( &g_nuiProfile_Tag, 1 ) );
    tiProfile_TL = tgPF_TL_Mark_Init( szTagName );
    Test__Expect_EQ(true, tiProfile_TL.m_uiKI != KTgPROFILE_ID__INVALID.m_uiKI)

    tiProfile_TL_Call = tgPF_TL_Mark_Start( tiProfile_TL );
    Test__Expect_EQ(true, tiProfile_TL_Call.m_uiKI != KTgPROFILE_TL_CALL_ID__INVALID.m_uiKI);

    Unit_Test__Sleep( 3000000 );
    tgPF_TL_Mark_Stop( tiProfile_TL, tiProfile_TL_Call );
    Test__Expect_EQ(0.0, tgPF_TL_Query_Total_Time_Cached( tiProfile_TL ));

    tgPF_TL_Update( 0.0F );
    Test__Expect_NE(0.0, tgPF_TL_Query_Total_Time_Cached( tiProfile_TL ));

    tgPF_TL_Mark_Reset( tiProfile_TL );
    Test__Expect_EQ(0.0, tgPF_TL_Query_Total_Time_Cached( tiProfile_TL ));

    tiProfile_TL_Call = tgPF_TL_Mark_Start( tiProfile_TL );
    Test__Expect_EQ(true, tiProfile_TL_Call.m_uiKI != KTgPROFILE_TL_CALL_ID__INVALID.m_uiKI);

    Unit_Test__Sleep( 3000000 );
    tgPF_TL_Mark_Stop( tiProfile_TL, tiProfile_TL_Call );
    Test__Expect_EQ(0.0, tgPF_TL_Query_Total_Time_Cached( tiProfile_TL ));

    tgPF_TL_Update( 0.0F );
    Test__Expect_NE(0.0, tgPF_TL_Query_Total_Time_Cached( tiProfile_TL ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__PF_TL_Query_Name ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__PF_TL_Query_Name )
{
    TgCHAR_U8                           szTagName[2][64];
    TgPROFILE_TL_ID                     tiProfile_TL[2];
    TgSINT_E08                          iRet;

    TgCOMPILER_ASSERT(64 == sizeof(szTagName[0]),);

    tgUSZ_PrintF( szTagName[0], sizeof(szTagName[0]), u8"PROFILE_TEST_%d", TgSTD_ATOMIC(fetch_add)( &g_nuiProfile_Tag, 1 ) );
    tiProfile_TL[0] = tgPF_TL_Mark_Init( szTagName[0] );
    Test__Expect_EQ(true, tiProfile_TL[0].m_uiKI != KTgPROFILE_ID__INVALID.m_uiKI)

    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, tgPF_TL_Query_Name( tiProfile_TL[0] ), KTgMAX_RSIZE, 0, szTagName[0], sizeof( szTagName[0] ), 0 )) && (0 == iRet));

    tgUSZ_PrintF( szTagName[1], sizeof(szTagName[1]), u8"PROFILE_TEST_%d", TgSTD_ATOMIC(fetch_add)( &g_nuiProfile_Tag, 1 ) );
    tiProfile_TL[1] = tgPF_TL_Mark_Init( szTagName[1] );
    Test__Expect_EQ(true, tiProfile_TL[1].m_uiKI != KTgPROFILE_ID__INVALID.m_uiKI)

    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, tgPF_TL_Query_Name( tiProfile_TL[1] ), KTgMAX_RSIZE, 0, szTagName[1], sizeof( szTagName[1] ), 0 )) && (0 == iRet));
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, tgPF_TL_Query_Name( tiProfile_TL[0] ), KTgMAX_RSIZE, 0, szTagName[0], sizeof( szTagName[0] ), 0 )) && (0 == iRet));

    tgUSZ_Copy( szTagName[1], sizeof( szTagName[1] ), szTagName[0], sizeof( szTagName[0] ) );
    tgMM_Set_U08_0x00( szTagName[0], sizeof( szTagName[0] ) );
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, tgPF_TL_Query_Name( tiProfile_TL[0] ), KTgMAX_RSIZE, 0, szTagName[1], sizeof( szTagName[1] ), 0 )) && (0 == iRet));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__PF_TL_Query_Total_Time_Cached --------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__PF_TL_Query_Total_Time_Cached )
{
    TgCHAR_U8                           szTagName[64];
    TgPROFILE_TL_ID                     tiProfile_TL;
    TgPROFILE_TL_CALL_ID                tiProfile_TL_Call;

    tgUSZ_PrintF( szTagName, 64, u8"PROFILE_TEST_%d", TgSTD_ATOMIC(fetch_add)( &g_nuiProfile_TL_Tag, 1 ) );
    tiProfile_TL = tgPF_TL_Mark_Init( szTagName );
    Test__Expect_EQ(true, tiProfile_TL.m_uiKI != KTgPROFILE_TL_ID__INVALID.m_uiKI)

    tiProfile_TL_Call = tgPF_TL_Mark_Start( tiProfile_TL );
    Test__Expect_EQ(true, tiProfile_TL_Call.m_uiKI != KTgPROFILE_TL_CALL_ID__INVALID.m_uiKI);

    Unit_Test__Sleep( 3000000 );
    tgPF_TL_Mark_Stop( tiProfile_TL, tiProfile_TL_Call );
    Test__Expect_EQ(0.0, tgPF_TL_Query_Total_Time_Cached( tiProfile_TL ));

    tgPF_TL_Update( 0.0F );
    Test__Expect_NE(0.0, tgPF_TL_Query_Total_Time_Cached( tiProfile_TL ));

    TEST_END_METHOD( KTgS_OK );
}

#else

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- UNIT_TEST__TEST__COMMON_Profile ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( UNIT_TEST__TEST__COMMON_Profile )
{
    TEST_END_METHOD( KTgS_OK );
}


/* =============================================================================================================================================================================== */
/*# TgCOMPILE__PROFILE */
#endif
