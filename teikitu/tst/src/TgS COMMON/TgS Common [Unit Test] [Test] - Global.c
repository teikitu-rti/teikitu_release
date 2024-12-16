/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common [Unit Test] [Test] - Global.c
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

TEST_METHOD( UNIT_TEST__TEST__GB_Init );
TEST_METHOD( UNIT_TEST__TEST__GB_Boot );
TEST_METHOD( UNIT_TEST__TEST__GB_Stop );
TEST_METHOD( UNIT_TEST__TEST__GB_Free );
TEST_METHOD( UNIT_TEST__TEST__GB_Update );
TEST_METHOD( UNIT_TEST__TEST__GB_Query_Init );
TEST_METHOD( UNIT_TEST__TEST__GB_Query_Boot );
TEST_METHOD( UNIT_TEST__TEST__GB_Query_Fixed_Memory );
TEST_METHOD( UNIT_TEST__TEST__GB_Init_OS );
TEST_METHOD( UNIT_TEST__TEST__GB_Boot_OS );
TEST_METHOD( UNIT_TEST__TEST__GB_Stop_OS );
TEST_METHOD( UNIT_TEST__TEST__GB_Free_OS );
TEST_METHOD( UNIT_TEST__TEST__GB_Stats );
TEST_METHOD( UNIT_TEST__TEST__GB_CMD_Set_Command_Line );
TEST_METHOD( UNIT_TEST__TEST__GB_CMD_Query_Argument_Count );
TEST_METHOD( UNIT_TEST__TEST__GB_CMD_Query_Argument );
TEST_METHOD( UNIT_TEST__TEST__GB_CMD_Query_Argument_Index );
TEST_METHOD( UNIT_TEST__TEST__GB_CMD_Push_Argument );
TEST_METHOD( UNIT_TEST__TEST__GB_Reset_Frame_Time );
TEST_METHOD( UNIT_TEST__TEST__GB_Set_Frame_Time );
TEST_METHOD( UNIT_TEST__TEST__GB_Inc_Frame_Time );
TEST_METHOD( UNIT_TEST__TEST__GB_Set_Client );
TEST_METHOD( UNIT_TEST__TEST__GB_Set_Server );
TEST_METHOD( UNIT_TEST__TEST__GB_Set_Console_HW );
TEST_METHOD( UNIT_TEST__TEST__GB_Set_Free_On_Quit );
TEST_METHOD( UNIT_TEST__TEST__GB_Get_Unique_Name );
TEST_METHOD( UNIT_TEST__TEST__GB_Parse_Command_Line );
TEST_METHOD( UNIT_TEST__TEST__GB_Verify_Version );
TEST_METHOD( UNIT_TEST__TEST__GB_Query_Frame_Time );
TEST_METHOD( UNIT_TEST__TEST__GB_Query_Total_Frame );
TEST_METHOD( UNIT_TEST__TEST__GB_Query_Total_Time );
TEST_METHOD( UNIT_TEST__TEST__GB_Query_Client );
TEST_METHOD( UNIT_TEST__TEST__GB_Query_Server );
TEST_METHOD( UNIT_TEST__TEST__GB_Query_Console_HW );
TEST_METHOD( UNIT_TEST__TEST__GB_Query_Free_On_Quit );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- UNIT_TEST__TEST__COMMON_Global ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( UNIT_TEST__TEST__COMMON_Global )
{
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__GB_Init());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__GB_Boot());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__GB_Stop());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__GB_Free());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__GB_Update());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__GB_Query_Init());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__GB_Query_Boot());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__GB_Query_Fixed_Memory());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__GB_Init_OS());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__GB_Boot_OS());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__GB_Stop_OS());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__GB_Free_OS());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__GB_Stats());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__GB_CMD_Set_Command_Line());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__GB_CMD_Query_Argument_Count());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__GB_CMD_Query_Argument());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__GB_CMD_Query_Argument_Index());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__GB_CMD_Push_Argument());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__GB_Reset_Frame_Time());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__GB_Set_Frame_Time());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__GB_Inc_Frame_Time());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__GB_Set_Client());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__GB_Set_Server());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__GB_Set_Console_HW());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__GB_Set_Free_On_Quit());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__GB_Get_Unique_Name());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__GB_Parse_Command_Line());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__GB_Verify_Version());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__GB_Query_Frame_Time());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__GB_Query_Total_Frame());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__GB_Query_Total_Time());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__GB_Query_Client());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__GB_Query_Server());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__GB_Query_Console_HW());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__GB_Query_Free_On_Quit());
    TEST_END_METHOD( KTgS_OK );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- UNIT_TEST__TEST__GB_Init ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__GB_Init )
{
    /* Due to their nature, module management functions can not be unit tested */

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__GB_Boot ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__GB_Boot )
{
    /* Due to their nature, module management functions can not be unit tested */

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__GB_Stop ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__GB_Stop )
{
    /* Due to their nature, module management functions can not be unit tested */

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__GB_Free ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__GB_Free )
{
    /* Due to their nature, module management functions can not be unit tested */

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__GB_Update ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__GB_Update )
{
    /* Due to their nature, module management functions can not be unit tested */

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__GB_Query_Init ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__GB_Query_Init )
{
    tgGB_Query_Init();

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__GB_Query_Boot ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__GB_Query_Boot )
{
    tgGB_Query_Boot();

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__GB_Query_Fixed_Memory ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__GB_Query_Fixed_Memory )
{
    tgGB_Query_Fixed_Memory();

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__GB_Init_OS ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__GB_Init_OS )
{
    /* Due to their nature, module management functions can not be unit tested */

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__GB_Boot_OS ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__GB_Boot_OS )
{
    /* Due to their nature, module management functions can not be unit tested */

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__GB_Stop_OS ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__GB_Stop_OS )
{
    /* Due to their nature, module management functions can not be unit tested */

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__GB_Free_OS ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__GB_Free_OS )
{
    /* Due to their nature, module management functions can not be unit tested */

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__GB_Stats ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__GB_Stats )
{
#if TgS_STAT__COMMON
    tgGB_Stats( nullptr );
#endif

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__GB_CMD_Set_Command_Line --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__GB_CMD_Set_Command_Line )
{
    TgCHAR_U8                           szCmdLine[256];

    tgUSZ_Copy( szCmdLine, TgARRAY_COUNT( szCmdLine ), u8"test.exe -arg0 -arg1 parameter -arg2 \"test this as well\" -arg3", KTgMAX_RSIZE );

    tgGB_CMD_Set_Command_Line( szCmdLine );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__GB_CMD_Query_Argument_Count ----------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__GB_CMD_Query_Argument_Count )
{
    TgCHAR_U8                           szCmdLine[256];

    tgUSZ_Copy( szCmdLine, TgARRAY_COUNT( szCmdLine ), u8"test.exe -arg0 -arg1 parameter -arg2 \"test this as well\" -arg3", KTgMAX_RSIZE );
    tgGB_CMD_Set_Command_Line( szCmdLine );

    tgGB_CMD_Query_Argument_Count();

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__GB_CMD_Query_Argument ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__GB_CMD_Query_Argument )
{
    TgCHAR_U8                           szCmdLine[256];

    tgUSZ_Copy( szCmdLine, TgARRAY_COUNT( szCmdLine ), u8"test.exe -arg0 -arg1 parameter -arg2 \"test this as well\" -arg3", KTgMAX_RSIZE );
    tgGB_CMD_Set_Command_Line( szCmdLine );

    tgGB_CMD_Query_Argument( 0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__GB_CMD_Query_Argument_Index ----------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__GB_CMD_Query_Argument_Index )
{
    TgCHAR_U8                           szCmdLine[256];

    tgUSZ_Copy( szCmdLine, TgARRAY_COUNT( szCmdLine ), u8"test.exe -arg0 -arg1 parameter -arg2 \"test this as well\" -arg3", KTgMAX_RSIZE );
    tgGB_CMD_Set_Command_Line( szCmdLine );

    tgGB_CMD_Query_Argument_Index( u8"test" );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__GB_CMD_Push_Argument ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__GB_CMD_Push_Argument )
{
    TgCHAR_U8                           szCmdLine[256];
    TgSINT_F08                          iRet;

    tgUSZ_Copy( szCmdLine, TgARRAY_COUNT( szCmdLine ), u8"test.exe", KTgMAX_RSIZE );
    tgGB_CMD_Set_Command_Line( szCmdLine );

    tgGB_CMD_Push_Argument( u8"-arg0" );
    tgGB_CMD_Push_Argument( u8"-arg1 parameter" );
    tgGB_CMD_Push_Argument( u8"-arg2 \"test this as well\"" );
    tgGB_CMD_Push_Argument( u8"-arg3" );

#if TgCOMPILE__CONSOLE
    tgCN_Set_Severity_Filter( KTgCN_CHANEL_MESSAGE, KTgCN_SEVERITY_0 );
#endif
    Test__Expect_EQ(7, tgGB_CMD_Query_Argument_Count());
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, u8"test.exe", KTgMAX_RSIZE, 0, tgGB_CMD_Query_Argument(0), KTgMAX_RSIZE, 0 )) && (0 == iRet));
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, u8"-arg0", KTgMAX_RSIZE, 0, tgGB_CMD_Query_Argument(1), KTgMAX_RSIZE, 0 )) && (0 == iRet));
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, u8"-arg1", KTgMAX_RSIZE, 0, tgGB_CMD_Query_Argument(2), KTgMAX_RSIZE, 0 )) && (0 == iRet));
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, u8"parameter", KTgMAX_RSIZE, 0, tgGB_CMD_Query_Argument(3), KTgMAX_RSIZE, 0 )) && (0 == iRet));
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, u8"-arg2", KTgMAX_RSIZE, 0, tgGB_CMD_Query_Argument(4), KTgMAX_RSIZE, 0 )) && (0 == iRet));
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, u8"\"test this as well\"", KTgMAX_RSIZE, 0, tgGB_CMD_Query_Argument(5), KTgMAX_RSIZE, 0 )) && (0 == iRet));
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, u8"-arg3", KTgMAX_RSIZE, 0, tgGB_CMD_Query_Argument(6), KTgMAX_RSIZE, 0 )) && (0 == iRet));
#if TgCOMPILE__CONSOLE
    tgCN_Set_Severity_Filter( KTgCN_CHANEL_MESSAGE, KTgCN_MAX_SEVERITY );
#endif

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__GB_Reset_Frame_Time ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__GB_Reset_Frame_Time )
{
    /* Validate the frame time (test the entire float range).  Hrm, negative time - sure why not? */
    tgGB_Reset_Frame_Time();

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__GB_Set_Frame_Time --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__GB_Set_Frame_Time )
{
    tgGB_Set_Frame_Time( -FLT_MIN );
    Test__Expect_EQ(-FLT_MIN, tgGB_Query_Total_Time());

    tgGB_Set_Frame_Time( -FLT_MAX );
    Test__Expect_EQ(-FLT_MAX, tgGB_Query_Total_Time());

    tgGB_Set_Frame_Time( 0.0F );
    Test__Expect_EQ(0.0F, tgGB_Query_Total_Time());

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__GB_Inc_Frame_Time --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__GB_Inc_Frame_Time )
{
    tgGB_Inc_Frame_Time( FLT_MIN );
    Test__Expect_EQ(FLT_MIN, tgGB_Query_Total_Time());

    tgGB_Inc_Frame_Time( FLT_MAX );
    Test__Expect_EQ(FLT_MAX, tgGB_Query_Total_Time());

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__GB_Set_Client ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__GB_Set_Client )
{
    TgBOOL                              bOriginalFlag;

    bOriginalFlag = tgGB_Query_Client();
    Test__Expect_EQ(false, tgGB_Query_Client());

    tgGB_Set_Client( true );
    Test__Expect_EQ(true, tgGB_Query_Client());

    tgGB_Set_Client( false );
    Test__Expect_EQ(false, tgGB_Query_Client());

    tgGB_Set_Client( bOriginalFlag );
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__GB_Set_Server ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__GB_Set_Server )
{
    TgBOOL                              bOriginalFlag;

    bOriginalFlag = tgGB_Query_Server();
    Test__Expect_EQ(false, tgGB_Query_Server());

    tgGB_Set_Server( true );
    Test__Expect_EQ(true, tgGB_Query_Server());

    tgGB_Set_Server( false );
    Test__Expect_EQ(false, tgGB_Query_Server());

    tgGB_Set_Server( bOriginalFlag );
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__GB_Set_Console_HW --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__GB_Set_Console_HW )
{
    TgBOOL                              bOriginalFlag;

    bOriginalFlag = tgGB_Query_Console_HW();
    Test__Expect_EQ(false, tgGB_Query_Console_HW());

    tgGB_Set_Console_HW( true );
    Test__Expect_EQ(true, tgGB_Query_Console_HW());

    tgGB_Set_Console_HW( false );
    Test__Expect_EQ(false, tgGB_Query_Console_HW());

    tgGB_Set_Console_HW( bOriginalFlag );
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__GB_Set_Free_On_Quit ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__GB_Set_Free_On_Quit )
{
    TgBOOL                              bOriginalFlag;

    bOriginalFlag = tgGB_Query_Free_On_Quit();
    Test__Expect_EQ(false, tgGB_Query_Free_On_Quit());

    tgGB_Set_Free_On_Quit( true );
    Test__Expect_EQ(true, tgGB_Query_Free_On_Quit());

    tgGB_Set_Free_On_Quit( false );
    Test__Expect_EQ(false, tgGB_Query_Free_On_Quit());

    tgGB_Set_Free_On_Quit( bOriginalFlag );
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__GB_Get_Unique_Name -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__GB_Get_Unique_Name )
{
    TgCHAR_U8                           szUnique_Name_0[64], szUnique_Name_1[64];
    TgSINT_F08                          iRet;

    /* Technically it is possible for the name to repeat. (After an unsigned 64bit integer number of queries. Not holding my breath.) I used a 64bit number because it is possible */
    /* for persistent games (like MMOs) to hit the 32bit limitations.  Wacky! */
    for (TgRSIZE uiIndex = 0; uiIndex < 1024; ++uiIndex)
    {
        Test__Expect_EQ(true, tgGB_Get_Unique_Name( szUnique_Name_0, 64 ));
        Test__Expect_EQ(true, tgGB_Get_Unique_Name( szUnique_Name_1, 64 ));
        Test__Expect_NE(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, szUnique_Name_0, KTgMAX_RSIZE, 0, szUnique_Name_1, KTgMAX_RSIZE, 0 )) && (0 == iRet));
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__GB_Parse_Command_Line ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__GB_Parse_Command_Line )
{
    TgCHAR_U8                           szCmdLine[256];
    TgCHAR_U8_CP                        aszCmd[KTgMAX_CMD_LINE_COUNT];
    TgSINT_F08                          iRet;

    tgUSZ_Copy( szCmdLine, TgARRAY_COUNT( szCmdLine ), u8"test.exe -arg0 -arg1 parameter -arg2 \"test this as well\" -arg3", KTgMAX_RSIZE );

#if TgCOMPILE__CONSOLE
    tgCN_Set_Severity_Filter( KTgCN_CHANEL_MESSAGE, KTgCN_SEVERITY_0 );
#endif
    Test__Expect_EQ(7, tgGB_Parse_Command_Line( aszCmd, KTgMAX_CMD_LINE_COUNT, szCmdLine ));
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, u8"test.exe", KTgMAX_RSIZE, 0, aszCmd[0], KTgMAX_RSIZE, 0 )) && (0 == iRet));
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, u8"-arg0", KTgMAX_RSIZE, 0, aszCmd[1], KTgMAX_RSIZE, 0 )) && (0 == iRet));
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, u8"-arg1", KTgMAX_RSIZE, 0, aszCmd[2], KTgMAX_RSIZE, 0 )) && (0 == iRet));
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, u8"parameter", KTgMAX_RSIZE, 0, aszCmd[3], KTgMAX_RSIZE, 0 )) && (0 == iRet));
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, u8"-arg2", KTgMAX_RSIZE, 0, aszCmd[4], KTgMAX_RSIZE, 0 )) && (0 == iRet));
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, u8"\"test this as well\"", KTgMAX_RSIZE, 0, aszCmd[5], KTgMAX_RSIZE, 0 )) && (0 == iRet));
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, u8"-arg3", KTgMAX_RSIZE, 0, aszCmd[6], KTgMAX_RSIZE, 0 )) && (0 == iRet));
#if TgCOMPILE__CONSOLE
    tgCN_Set_Severity_Filter( KTgCN_CHANEL_MESSAGE, KTgCN_MAX_SEVERITY );
#endif

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__GB_Verify_Version --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__GB_Verify_Version )
{
    TgUINT_F32                          uiVersion;

    uiVersion =  (TGS_VERSION__MAJOR & 0xFF) | ((TGS_VERSION__MINOR & 0xFF) << 8) | ((TGS_VERSION__PATCH & 0xFF) << 16) | ((TGS_VERSION__TWEAK & 0xFF) << 24);
    Test__Expect_EQ(true,tgGB_Verify_Version( uiVersion ));

    uiVersion =  ((TGS_VERSION__MINOR & 0xFF) << 8) | ((TGS_VERSION__PATCH & 0xFF) << 16) | ((TGS_VERSION__TWEAK & 0xFF) << 24);
    Test__Expect_EQ(false,tgGB_Verify_Version( uiVersion ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__GB_Query_Frame_Time ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__GB_Query_Frame_Time )
{
    tgGB_Query_Frame_Time();

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__GB_Query_Total_Frame ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__GB_Query_Total_Frame )
{
    /* The following functions can only be link tested */
    tgGB_Query_Total_Frame();

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__GB_Query_Total_Time ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__GB_Query_Total_Time )
{
    /* The following functions can only be link tested */
    tgGB_Query_Total_Time();

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__GB_Query_Client ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__GB_Query_Client )
{
    return (UNIT_TEST__TEST__GB_Set_Client());
}


/* ---- UNIT_TEST__TEST__GB_Query_Server ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__GB_Query_Server )
{
    return (UNIT_TEST__TEST__GB_Set_Server());
}


/* ---- UNIT_TEST__TEST__GB_Query_Console_HW ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__GB_Query_Console_HW )
{
    return (UNIT_TEST__TEST__GB_Set_Console_HW());
}


/* ---- UNIT_TEST__TEST__GB_Query_Free_On_Quit ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__GB_Query_Free_On_Quit )
{
    return (UNIT_TEST__TEST__GB_Set_Free_On_Quit());
}
