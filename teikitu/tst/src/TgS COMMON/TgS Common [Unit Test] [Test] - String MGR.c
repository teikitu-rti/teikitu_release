/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common [Unit Test] [Test] - String MGR.c
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

TEST_METHOD( UNIT_TEST__TEST__SM_Init_MGR );
TEST_METHOD( UNIT_TEST__TEST__SM_Boot_MGR );
TEST_METHOD( UNIT_TEST__TEST__SM_Stop_MGR );
TEST_METHOD( UNIT_TEST__TEST__SM_Free_MGR );
TEST_METHOD( UNIT_TEST__TEST__SM_Update_MGR );
TEST_METHOD( UNIT_TEST__TEST__SM_Query_Init );
TEST_METHOD( UNIT_TEST__TEST__SM_Query_Boot );
TEST_METHOD( UNIT_TEST__TEST__SM_Query_Fixed_Memory );
TEST_METHOD( UNIT_TEST__TEST__SM_Stats );
TEST_METHOD( UNIT_TEST__TEST__SM_UID_Init_String );
TEST_METHOD( UNIT_TEST__TEST__SM_UID_Query_String );
TEST_METHOD( UNIT_TEST__TEST__SM_Dict_Insert_String_Hash );
TEST_METHOD( UNIT_TEST__TEST__SM_Dict_Insert_String );
TEST_METHOD( UNIT_TEST__TEST__SM_Dict_Find_Id_By_Hash );
TEST_METHOD( UNIT_TEST__TEST__SM_Dict_Find_Id_By_String );
TEST_METHOD( UNIT_TEST__TEST__SM_Dict_Query_String );
TEST_METHOD( UNIT_TEST__TEST__SM_Table_Load );
TEST_METHOD( UNIT_TEST__TEST__SM_Table_Free );
TEST_METHOD( UNIT_TEST__TEST__SM_Table_Is_Loaded );
TEST_METHOD( UNIT_TEST__TEST__SM_Table_Query_String );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

static TgVOID                               UNIT_TEST__TEST__SM_Setup_Table_Input( TgCHAR_U8_P, TgRSIZE_C, STg2_Input_MEM_P );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- UNIT_TEST__TEST__COMMON_String_MGR --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( UNIT_TEST__TEST__COMMON_String_MGR )
{
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__SM_Init_MGR());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__SM_Boot_MGR());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__SM_Stop_MGR());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__SM_Free_MGR());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__SM_Update_MGR());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__SM_Query_Init());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__SM_Query_Boot());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__SM_Query_Fixed_Memory());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__SM_Stats());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__SM_UID_Init_String());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__SM_UID_Query_String());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__SM_Dict_Insert_String_Hash());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__SM_Dict_Insert_String());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__SM_Dict_Find_Id_By_Hash());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__SM_Dict_Find_Id_By_String());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__SM_Dict_Query_String());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__SM_Table_Load());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__SM_Table_Free());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__SM_Table_Is_Loaded());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__SM_Table_Query_String());

    TEST_END_METHOD( KTgS_OK );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- UNIT_TEST__TEST__SM_Init_MGR --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__SM_Init_MGR )
{
    /* Due to their nature, module management functions can not be unit tested */

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__SM_Boot_MGR --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__SM_Boot_MGR )
{
    /* Due to their nature, module management functions can not be unit tested */

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__SM_Stop_MGR --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__SM_Stop_MGR )
{
    /* Due to their nature, module management functions can not be unit tested */

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__SM_Free_MGR --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__SM_Free_MGR )
{
    /* Due to their nature, module management functions can not be unit tested */

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__SM_Update_MGR ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__SM_Update_MGR )
{
    /* Due to their nature, module management functions can not be unit tested */

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__SM_Query_Init ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__SM_Query_Init )
{
    Test__Expect_EQ(true, tgSM_Query_Init());

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__SM_Query_Boot ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__SM_Query_Boot )
{
    Test__Expect_EQ(true, tgSM_Query_Boot());


    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__SM_Query_Fixed_Memory ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__SM_Query_Fixed_Memory )
{
    tgSM_Query_Fixed_Memory();

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__SM_Stats ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__SM_Stats )
{
#if TgS_STAT__COMMON
    TgCHAR_U8                           mbzBuffer[256];
    STg2_Output_MEM                     sOutput;
    TgUN_POINTER                        sBuffer;

    sBuffer.m_mbz = mbzBuffer;

    /* Create a memory base output object to be used when testing the console output systems */
    tgIO_OM__Open( &sOutput, sBuffer.m_puiE08, sizeof( mbzBuffer ), nullptr );
    mbzBuffer[0] = 0;

    tgSM_Stats( &sOutput.m_sOutput );

/*# TgS_STAT__COMMON */
#endif

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__SM_UID_Init_String -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__SM_UID_Init_String )
{
    Test__Expect_EQ(KTgSM_MAX_NATIVE_ENTRIES - 1, tgSM_UID_Init_String( u8"Unit Test 1", KTgSM_MAX_NATIVE_ENTRIES - 1 ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__SM_UID_Query_String ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__SM_UID_Query_String )
{
    TgCHAR_U8_CP                        mbzBuffer;
    TgSINT_F08                          iRet;

    Test__Expect_EQ(KTgSM_MAX_NATIVE_ENTRIES - 2, tgSM_UID_Init_String( u8"Unit Test 2", KTgSM_MAX_NATIVE_ENTRIES - 2 ));
    mbzBuffer = tgSM_UID_Query_String( KTgSM_MAX_NATIVE_ENTRIES - 2 );
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, u8"Unit Test 2", KTgMAX_RSIZE, 0, mbzBuffer, KTgMAX_RSIZE, 0 )) && (0 == iRet));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__SM_Dict_Insert_String_Hash ------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__SM_Dict_Insert_String_Hash )
{
    TgSTRING_DICT_ID                    tiString_Dict;
    TgUINT_MAX                          uiHash;

    Test__Expect_EQ(KTgS_OK, tgUSZ_Hash( &uiHash, u8"Unit Test 3", KTgMAX_RSIZE ));
    tiString_Dict = tgSM_Dict_Insert_String_Hash( u8"Unit Test 3", KTgMAX_RSIZE, uiHash );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiString_Dict.m_uiKI);

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__SM_Dict_Insert_String ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__SM_Dict_Insert_String )
{
    TgSTRING_DICT_ID                    tiString_Dict;

    tiString_Dict = tgSM_Dict_Insert_String( u8"Unit Test 4", KTgMAX_RSIZE );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiString_Dict.m_uiKI);

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__SM_Dict_Find_Id_By_Hash --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__SM_Dict_Find_Id_By_Hash )
{
    TgSTRING_DICT_ID                    tiString_Dict;
    TgUINT_MAX                          uiHash;

    Test__Expect_EQ(KTgS_OK, tgUSZ_Hash( &uiHash, u8"Unit Test 5", KTgMAX_RSIZE ));
    tiString_Dict = tgSM_Dict_Insert_String_Hash( u8"Unit Test 5", KTgMAX_RSIZE, uiHash );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiString_Dict.m_uiKI);
    Test__Expect_NE(tiString_Dict.m_uiKI, tgSM_Dict_Find_Id_By_Hash( u8"Unit Test 5", KTgEMPTY_HASH ).m_uiKI );
    Test__Expect_EQ(tiString_Dict.m_uiKI, tgSM_Dict_Find_Id_By_Hash( u8"Unit Test 5", uiHash ).m_uiKI );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__SM_Dict_Find_Id_By_String ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__SM_Dict_Find_Id_By_String )
{
    TgSTRING_DICT_ID                    tiString_Dict;

    tiString_Dict = tgSM_Dict_Insert_String( u8"Unit Test 6", KTgMAX_RSIZE );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiString_Dict.m_uiKI);
    Test__Expect_EQ(tiString_Dict.m_uiKI, tgSM_Dict_Find_Id_By_String( u8"Unit Test 6", KTgMAX_RSIZE ).m_uiKI );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__SM_Dict_Query_String ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__SM_Dict_Query_String )
{
    TgSTRING_DICT_ID                    tiString_Dict;
    TgCHAR_U8_CP                        mbzValue;
    TgRSIZE                             nbyValue;
    TgSINT_F08                          iRet;

    tiString_Dict = tgSM_Dict_Insert_String( u8"Unit Test 7", KTgMAX_RSIZE );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiString_Dict.m_uiKI);
    tiString_Dict = tgSM_Dict_Insert_String( u8"Unit Test 8", KTgMAX_RSIZE );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiString_Dict.m_uiKI);


    mbzValue = nullptr;
    tgSM_Dict_Query_String( &mbzValue, &nbyValue, tiString_Dict );
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, u8"Unit Test 8", KTgMAX_RSIZE, 0, mbzValue, nbyValue, 0 )) && (0 == iRet));
    Test__Expect_EQ(11, nbyValue);

    mbzValue = nullptr;
    tgSM_Dict_Query_String( &mbzValue, &nbyValue, tgSM_Dict_Find_Id_By_String( u8"Unit Test 7", KTgMAX_RSIZE ) );
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, u8"Unit Test 7", KTgMAX_RSIZE, 0, mbzValue, nbyValue, 0 )) && (0 == iRet));
    Test__Expect_EQ(11, nbyValue);

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__SM_Table_Load ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__SM_Table_Load )
{
    TgCHAR_U8 TgALIGN(16)               mbzBuffer[128];
    TgSTRING_TABLE_ID                   tiString_Table;
    STg2_Input_MEM                      sInput;

    tgMM_Set_U08_0x00( mbzBuffer, sizeof( mbzBuffer ) );
    tgIO_IM__Open( &sInput, mbzBuffer, sizeof( mbzBuffer ), nullptr );
    tiString_Table = tgSM_Table_Load( &sInput.m_sInput, 0 );
    tgIO_IM__Close( &sInput.m_sInput );
    Test__Expect_EQ(KTgID__INVALID_VALUE, tiString_Table.m_uiKI);

    UNIT_TEST__TEST__SM_Setup_Table_Input( mbzBuffer, sizeof(mbzBuffer), &sInput );
    tiString_Table = tgSM_Table_Load( &sInput.m_sInput, 0 );
    tgIO_IM__Close( &sInput.m_sInput );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiString_Table.m_uiKI);

    Test__Expect_EQ(true, tgSM_Table_Free( tiString_Table ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__SM_Table_Free ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__SM_Table_Free )
{
    TgCHAR_U8 TgALIGN(16)               mbzBuffer[128];
    TgSTRING_TABLE_ID                   tiString_Table;
    STg2_Input_MEM                      sInput;

    UNIT_TEST__TEST__SM_Setup_Table_Input( mbzBuffer, sizeof(mbzBuffer), &sInput );
    tiString_Table = tgSM_Table_Load( &sInput.m_sInput, 0 );
    tgIO_IM__Close( &sInput.m_sInput );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiString_Table.m_uiKI);

    Test__Expect_EQ(true, tgSM_Table_Free( tiString_Table ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__SM_Table_Is_Loaded -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__SM_Table_Is_Loaded )
{
    TgCHAR_U8 TgALIGN(16)               mbzBuffer[128];
    TgSTRING_TABLE_ID                   tiString_Table;
    STg2_Input_MEM                      sInput;

    UNIT_TEST__TEST__SM_Setup_Table_Input( mbzBuffer, sizeof(mbzBuffer), &sInput );
    tiString_Table = tgSM_Table_Load( &sInput.m_sInput, 0 );
    tgIO_IM__Close( &sInput.m_sInput );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiString_Table.m_uiKI);

    Test__Expect_EQ(true, tgSM_Table_Is_Loaded( tiString_Table ));
    Test__Expect_EQ(true, tgSM_Table_Free( tiString_Table ));
    Test__Expect_NE(true, tgSM_Table_Is_Loaded( tiString_Table ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__SM_Table_Query_String ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__SM_Table_Query_String )
{
    TgCHAR_U8 TgALIGN(16)               mbzBuffer[128];
    TgSTRING_TABLE_ID                   tiString_Table;
    TgCHAR_U8_CP                        mbzValue;
    TgRSIZE                             nbyValue;
    STg2_Input_MEM                      sInput;
    TgSINT_F08                          iRet;

    UNIT_TEST__TEST__SM_Setup_Table_Input( mbzBuffer, sizeof(mbzBuffer), &sInput );
    tiString_Table = tgSM_Table_Load( &sInput.m_sInput, 0 );
    tgIO_IM__Close( &sInput.m_sInput );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiString_Table.m_uiKI);

    Test__Expect_EQ(true, tgSM_Table_Query_String( &mbzValue, &nbyValue, tiString_Table, 0 ));
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, u8"Unit Test 9", KTgMAX_RSIZE, 0, mbzValue, nbyValue, 0 )) && (0 == iRet));
    Test__Expect_EQ(11, nbyValue);
    Test__Expect_EQ(true, tgSM_Table_Query_String( &mbzValue, &nbyValue, tiString_Table, 1 ));
    Test__Expect_EQ(true,  TgSUCCEEDED(tgUSZ_Compare( &iRet, u8"Unit Test 10", KTgMAX_RSIZE, 0, mbzValue, nbyValue, 0 )) && (0 == iRet));
    Test__Expect_EQ(11, nbyValue);
    Test__Expect_EQ(true, tgSM_Table_Query_String( &mbzValue, &nbyValue, tiString_Table, 2 ));
    Test__Expect_EQ(true,  TgSUCCEEDED(tgUSZ_Compare( &iRet, u8"Unit Test 11", KTgMAX_RSIZE, 0, mbzValue, nbyValue, 0 )) && (0 == iRet));
    Test__Expect_EQ(11, nbyValue);
    Test__Expect_NE(true, tgSM_Table_Query_String( &mbzValue, &nbyValue, tiString_Table, 3 ));

    Test__Expect_EQ(true, tgSM_Table_Free( tiString_Table ));

    TEST_END_METHOD( KTgS_OK );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- UNIT_TEST__TEST__SM_Setup_Table_Input ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID UNIT_TEST__TEST__SM_Setup_Table_Input( TgCHAR_U8_PC mbzBuffer, TgRSIZE_C nbyBuffer, STg2_Input_MEM_P psInput )
{
    TgUN_POINTER                        sBuffer, sHold;
    STg2_String_Table_Entry_Id          sEntry_Id;

    sEntry_Id.m_uiEntry_Id = 0;
    sEntry_Id.m_uiSize = 12;

    sBuffer.m_mbz = mbzBuffer;

    *sBuffer.m_puiRSIZE++ = 3;
    *sBuffer.m_puiRSIZE++ = 0;
    *sBuffer.m_puiRSIZE++ = 0;

    sEntry_Id.m_uiAddress = 0;
    sEntry_Id.m_uiIndex = 0;
    *sBuffer.m_puiE64++ = sEntry_Id.m_uiEntry_Id;
    tgMM_Copy( sBuffer.m_puiE08, 12, u8"Unit Test 9", 12 );
    sBuffer.m_puiE08 += 12;

    sEntry_Id.m_uiAddress = 20;
    sEntry_Id.m_uiIndex = 2;
    *sBuffer.m_puiE64++ = sEntry_Id.m_uiEntry_Id;
    tgMM_Copy( sBuffer.m_puiE08, 12, u8"Unit Test 10", 12 );
    sBuffer.m_puiE08 += 12;

    sEntry_Id.m_uiAddress = 40;
    sEntry_Id.m_uiIndex = 1;
    *sBuffer.m_puiE64++ = sEntry_Id.m_uiEntry_Id;
    tgMM_Copy( sBuffer.m_puiE08, 12, u8"Unit Test 11", 12 );
    sBuffer.m_puiE08 += 12;

    sBuffer.m_uiPTR = (sBuffer.m_uiPTR + 7) & ~(TgUINT_PTR)7;
    
    sHold = sBuffer;
    sBuffer.m_mbz = mbzBuffer + 2 * sizeof( TgRSIZE );
    *sBuffer.m_puiRSIZE = (TgRSIZE)(sHold.m_mbz - mbzBuffer);
    sBuffer = sHold;

    sEntry_Id.m_uiAddress = 0;
    sEntry_Id.m_uiIndex = 0;
    *sBuffer.m_puiE64++ = sEntry_Id.m_uiEntry_Id;

    sEntry_Id.m_uiAddress = 40;
    sEntry_Id.m_uiIndex = 1;
    *sBuffer.m_puiE64++ = sEntry_Id.m_uiEntry_Id;

    sEntry_Id.m_uiAddress = 20;
    sEntry_Id.m_uiIndex = 2;
    *sBuffer.m_puiE64++ = sEntry_Id.m_uiEntry_Id;

    sHold = sBuffer;
    sBuffer.m_mbz = mbzBuffer + 1 * sizeof( TgRSIZE );
    *sBuffer.m_puiRSIZE = (TgRSIZE)(sHold.m_mbz - mbzBuffer);

    sBuffer.m_mbz = mbzBuffer;

    TgERROR( (TgRSIZE)(sBuffer.m_mbz - mbzBuffer)< nbyBuffer );
    sBuffer.m_mbz = mbzBuffer;
    tgIO_IM__Open( psInput, sBuffer.m_puiE08, nbyBuffer, nullptr );
}
