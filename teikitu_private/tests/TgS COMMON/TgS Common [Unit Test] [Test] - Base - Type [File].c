/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common [Unit Test] [Test] - Base - Type [File].c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include <stdlib.h>


/* == Common ===================================================================================================================================================================== */
/* MARK: Unit Test Complete 00D008E0-5616-4AAF-8989-24865B450F52                                                                                                                   */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Macros                                                                                                                                                              */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#define ROOT                                    TEST__ROOT_DIRECTORY
#define PSEP                                    TgPLATFORM__U8_PATH_SEPARATOR
#define P01                                     u8"Test01"
#define P02                                     KTgU8_LIT_TEST__BURMESE
#define P03                                     KTgU8_LIT_TEST__RUSSIAN
#define P04                                     KTgU8_LIT_TEST__KOREAN

#define FSEP                                    TgPLATFORM__U8_FILE_SEPARATOR
#define NAME                                    KTgU8_LIT_TEST__CHINESE_SIMPLIFIED
#define EXT_01                                  KTgU8_LIT_TEST__JAPANESE
#define EXT_02                                  KTgU8_LIT_TEST__KOREAN




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TEST_METHOD( UNIT_TEST__TEST__CM_Path_Add_Separator );
TEST_METHOD( UNIT_TEST__TEST__CM_Path_Add_Extension );
TEST_METHOD( UNIT_TEST__TEST__CM_Path_Copy );
TEST_METHOD( UNIT_TEST__TEST__CM_Path_Append );
TEST_METHOD( UNIT_TEST__TEST__CM_Path_Common_Prefix_Size_U08 );
TEST_METHOD( UNIT_TEST__TEST__CM_Path_Common_Prefix_Size_Count );
TEST_METHOD( UNIT_TEST__TEST__CM_Path_Common_Prefix );
TEST_METHOD( UNIT_TEST__TEST__CM_Path_Remove_Separator );
TEST_METHOD( UNIT_TEST__TEST__CM_Path_Remove_Extension );
TEST_METHOD( UNIT_TEST__TEST__CM_Path_Remove_File_Name );
TEST_METHOD( UNIT_TEST__TEST__CM_Path_Rename_Extension );
TEST_METHOD( UNIT_TEST__TEST__CM_Path_Remove_Folder );
TEST_METHOD( UNIT_TEST__TEST__CM_Path_Init );
TEST_METHOD( UNIT_TEST__TEST__CM_Path_Find_Extension );
TEST_METHOD( UNIT_TEST__TEST__CM_Path_Find_File_Name );
TEST_METHOD( UNIT_TEST__TEST__CM_Path_IsAbsolute );
TEST_METHOD( UNIT_TEST__TEST__CM_File_Output_Header );
TEST_METHOD( UNIT_TEST__TEST__CM_File_Output_Data_Headers );
TEST_METHOD( UNIT_TEST__TEST__CM_File_Query_Data );
TEST_METHOD( UNIT_TEST__TEST__CM_File_Query_Data_Size );
TEST_METHOD( UNIT_TEST__TEST__CM_File_Query_Data_Count );
TEST_METHOD( UNIT_TEST__TEST__CM_File_Check_Block );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TEST_LOCAL TgUINT_E08_P                     tgUNIT_TEST_INTERNAL__File_Data_Setup( TgVOID );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- UNIT_TEST__TEST__Base_Type_File_Path ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( UNIT_TEST__TEST__Base_Type_File_Path )
{
    tgCN_Set_Severity_Filter( KTgCN_CHANEL_MESSAGE, 0xC );

    Test__Expect_EQ( KTgS_OK, UNIT_TEST__TEST__CM_Path_Add_Separator() );
    Test__Expect_EQ( KTgS_OK, UNIT_TEST__TEST__CM_Path_Add_Extension() );
    Test__Expect_EQ( KTgS_OK, UNIT_TEST__TEST__CM_Path_Copy() );
    Test__Expect_EQ( KTgS_OK, UNIT_TEST__TEST__CM_Path_Append() );
    Test__Expect_EQ( KTgS_OK, UNIT_TEST__TEST__CM_Path_Common_Prefix_Size_U08() );
    Test__Expect_EQ( KTgS_OK, UNIT_TEST__TEST__CM_Path_Common_Prefix_Size_Count() );
    Test__Expect_EQ( KTgS_OK, UNIT_TEST__TEST__CM_Path_Common_Prefix() );
    Test__Expect_EQ( KTgS_OK, UNIT_TEST__TEST__CM_Path_Remove_Separator() );
    Test__Expect_EQ( KTgS_OK, UNIT_TEST__TEST__CM_Path_Remove_Extension() );
    Test__Expect_EQ( KTgS_OK, UNIT_TEST__TEST__CM_Path_Remove_File_Name() );
    Test__Expect_EQ( KTgS_OK, UNIT_TEST__TEST__CM_Path_Rename_Extension() );
    Test__Expect_EQ( KTgS_OK, UNIT_TEST__TEST__CM_Path_Remove_Folder() );
    Test__Expect_EQ( KTgS_OK, UNIT_TEST__TEST__CM_Path_Init() );
    Test__Expect_EQ( KTgS_OK, UNIT_TEST__TEST__CM_Path_Find_Extension() );
    Test__Expect_EQ( KTgS_OK, UNIT_TEST__TEST__CM_Path_Find_File_Name() );
    Test__Expect_EQ( KTgS_OK, UNIT_TEST__TEST__CM_Path_IsAbsolute() );

    tgCN_Set_Severity_Filter( KTgCN_CHANEL_MESSAGE, 0xF );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__Base_Type_File_File ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( UNIT_TEST__TEST__Base_Type_File_File )
{
    Test__Expect_EQ( KTgS_OK, UNIT_TEST__TEST__CM_File_Output_Header() );
    Test__Expect_EQ( KTgS_OK, UNIT_TEST__TEST__CM_File_Output_Data_Headers() );
    Test__Expect_EQ( KTgS_OK, UNIT_TEST__TEST__CM_File_Query_Data() );
    Test__Expect_EQ( KTgS_OK, UNIT_TEST__TEST__CM_File_Query_Data_Size() );
    Test__Expect_EQ( KTgS_OK, UNIT_TEST__TEST__CM_File_Query_Data_Count() );
    Test__Expect_EQ( KTgS_OK, UNIT_TEST__TEST__CM_File_Check_Block() );

    TEST_END_METHOD( KTgS_OK );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- UNIT_TEST__TEST__CM_Path_Add_Separator ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_Path_Add_Separator )
{
    TgCHAR_U8                           mbzPath_Test[KTgMAX_FILE_PATH] = { 0 };
    TgSINT_E08                          iRet;

    tgMM_Set_U08_0x00( mbzPath_Test, sizeof mbzPath_Test );
    Test__Expect_EQ(KTgS_OK, tgUSZ_Copy( mbzPath_Test, KTgMAX_FILE_PATH, ROOT P01 PSEP P02, KTgMAX_RSIZE ));
    Test__Expect_EQ(KTgS_OK, tgCM_Path_Add_Separator( mbzPath_Test, KTgMAX_FILE_PATH ));
    TgMSGF( 0xC, UNIT_TEST__MSG_LITERAL_3, u8"TEST:", u8"", u8"", u8"tgCM_Path_Add_Separator", mbzPath_Test );
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, mbzPath_Test, KTgMAX_RSIZE, 0, ROOT P01 PSEP P02 PSEP, KTgMAX_RSIZE, 0 )) && (0 == iRet));

    tgMM_Set_U08_0x00( mbzPath_Test, sizeof mbzPath_Test );
    Test__Expect_EQ(KTgS_OK, tgUSZ_Copy( mbzPath_Test, KTgMAX_FILE_PATH, ROOT P01 PSEP P02 PSEP, KTgMAX_RSIZE ));
    Test__Expect_EQ(KTgS_OK, tgCM_Path_Add_Separator( mbzPath_Test, KTgMAX_FILE_PATH ));
    TgMSGF( 0xC, UNIT_TEST__MSG_LITERAL_3, u8"TEST:", u8"", u8"", u8"tgCM_Path_Add_Separator", mbzPath_Test );
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, mbzPath_Test, KTgMAX_RSIZE, 0, ROOT P01 PSEP P02 PSEP, KTgMAX_RSIZE, 0 )) && (0 == iRet));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_Path_Add_Extension ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_Path_Add_Extension )
{
    TgCHAR_U8                           mbzPath_Test[KTgMAX_FILE_PATH] = { 0 };
    TgSINT_E08                          iRet;

    tgMM_Set_U08_0x00( mbzPath_Test, sizeof mbzPath_Test );
    Test__Expect_EQ(KTgS_OK, tgUSZ_Copy( mbzPath_Test, KTgMAX_FILE_PATH, ROOT P01 PSEP NAME, KTgMAX_RSIZE ));
    Test__Expect_EQ(KTgS_OK, tgCM_Path_Add_Extension( mbzPath_Test, KTgMAX_FILE_PATH, EXT_01, KTgMAX_RSIZE ));
    TgMSGF( 0xC, UNIT_TEST__MSG_LITERAL_3, u8"TEST:", u8"", u8"", u8"tgCM_Path_Add_Extension", mbzPath_Test );
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, mbzPath_Test, KTgMAX_RSIZE, 0, ROOT P01 PSEP NAME FSEP EXT_01, KTgMAX_RSIZE, 0 )) && (0 == iRet));

    tgMM_Set_U08_0x00( mbzPath_Test, sizeof mbzPath_Test );
    Test__Expect_EQ(KTgS_OK, tgUSZ_Copy( mbzPath_Test, KTgMAX_FILE_PATH, ROOT P01 PSEP NAME FSEP EXT_01, KTgMAX_RSIZE ));
    Test__Expect_EQ(KTgS_OK, tgCM_Path_Add_Extension( mbzPath_Test, KTgMAX_FILE_PATH, EXT_02, KTgMAX_RSIZE ));
    TgMSGF( 0xC, UNIT_TEST__MSG_LITERAL_3, u8"TEST:", u8"", u8"", u8"tgCM_Path_Add_Extension", mbzPath_Test );
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, mbzPath_Test, KTgMAX_RSIZE, 0, ROOT P01 PSEP NAME FSEP EXT_01 FSEP EXT_02, KTgMAX_RSIZE, 0 )) && (0 == iRet));

    tgMM_Set_U08_0x00( mbzPath_Test, sizeof mbzPath_Test );
    Test__Expect_EQ(KTgS_OK, tgUSZ_Copy( mbzPath_Test, KTgMAX_FILE_PATH, ROOT P01 PSEP NAME FSEP, KTgMAX_RSIZE ));
    Test__Expect_EQ(KTgS_OK, tgCM_Path_Add_Extension( mbzPath_Test, KTgMAX_FILE_PATH, EXT_02, KTgMAX_RSIZE ));
    TgMSGF( 0xC, UNIT_TEST__MSG_LITERAL_3, u8"TEST:", u8"", u8"", u8"tgCM_Path_Add_Extension", mbzPath_Test );
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, mbzPath_Test, KTgMAX_RSIZE, 0, ROOT P01 PSEP NAME FSEP FSEP EXT_02, KTgMAX_RSIZE, 0 )) && (0 == iRet));

    tgMM_Set_U08_0x00( mbzPath_Test, sizeof mbzPath_Test );
    Test__Expect_EQ(KTgS_OK, tgUSZ_Copy( mbzPath_Test, KTgMAX_FILE_PATH, ROOT P01 PSEP NAME PSEP, KTgMAX_RSIZE ));
    Test__Expect_EQ(KTgS_OK, tgCM_Path_Add_Extension( mbzPath_Test, KTgMAX_FILE_PATH, EXT_02, KTgMAX_RSIZE ));
    TgMSGF( 0xC, UNIT_TEST__MSG_LITERAL_3, u8"TEST:", u8"", u8"", u8"tgCM_Path_Add_Extension", mbzPath_Test );
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, mbzPath_Test, KTgMAX_RSIZE, 0, ROOT P01 PSEP NAME PSEP FSEP EXT_02, KTgMAX_RSIZE, 0 )) && (0 == iRet));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_Path_Copy -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_Path_Copy )
{
    TgCHAR_U8                           mbzPath_Test[KTgMAX_FILE_PATH] = { 0 };
    TgSINT_E08                          iRet;

    tgMM_Set_U08_0x00( mbzPath_Test, sizeof mbzPath_Test );
    Test__Expect_EQ(KTgS_OK, tgCM_Path_Copy( mbzPath_Test, KTgMAX_FILE_PATH, ROOT P01 PSEP P02 PSEP, KTgMAX_RSIZE ));
    TgMSGF( 0xC, UNIT_TEST__MSG_LITERAL_3, u8"TEST:", u8"", u8"", u8"tgCM_Path_Copy", mbzPath_Test );
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, mbzPath_Test, KTgMAX_RSIZE, 0, ROOT P01 PSEP P02 PSEP, KTgMAX_RSIZE, 0 )) && (0 == iRet));

    tgMM_Set_U08_0x00( mbzPath_Test, sizeof mbzPath_Test );
    Test__Expect_EQ(KTgS_OK, tgCM_Path_Copy( mbzPath_Test, KTgMAX_FILE_PATH, ROOT P01 PSEP P02, KTgMAX_RSIZE ));
    TgMSGF( 0xC, UNIT_TEST__MSG_LITERAL_3, u8"TEST:", u8"", u8"", u8"tgCM_Path_Copy", mbzPath_Test );
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, mbzPath_Test, KTgMAX_RSIZE, 0, ROOT P01 PSEP P02, KTgMAX_RSIZE, 0 )) && (0 == iRet));

    tgMM_Set_U08_0x00( mbzPath_Test, sizeof mbzPath_Test );
    Test__Expect_EQ(KTgS_OK, tgCM_Path_Copy( mbzPath_Test, KTgMAX_FILE_PATH, ROOT P01 PSEP NAME FSEP EXT_01, KTgMAX_RSIZE ));
    TgMSGF( 0xC, UNIT_TEST__MSG_LITERAL_3, u8"TEST:", u8"", u8"", u8"tgCM_Path_Copy", mbzPath_Test );
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, mbzPath_Test, KTgMAX_RSIZE, 0, ROOT P01 PSEP NAME FSEP EXT_01, KTgMAX_RSIZE, 0 )) && (0 == iRet));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_Path_Append ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_Path_Append )
{
    TgCHAR_U8                           mbzPath_Test[KTgMAX_FILE_PATH] = { 0 };
    TgSINT_E08                          iRet;

    tgMM_Set_U08_0x00( mbzPath_Test, sizeof mbzPath_Test );
    Test__Expect_EQ(KTgS_OK, tgUSZ_Copy( mbzPath_Test, KTgMAX_FILE_PATH, ROOT P01 PSEP, KTgMAX_RSIZE ));
    Test__Expect_EQ(KTgS_OK, tgCM_Path_Append( mbzPath_Test, KTgMAX_FILE_PATH, P02 PSEP, KTgMAX_RSIZE ));
    TgMSGF( 0xC, UNIT_TEST__MSG_LITERAL_3, u8"TEST:", u8"", u8"", u8"tgCM_Path_Append", mbzPath_Test );
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, mbzPath_Test, KTgMAX_RSIZE, 0, ROOT P01 PSEP P02 PSEP, KTgMAX_RSIZE, 0 )) && (0 == iRet));

    tgMM_Set_U08_0x00( mbzPath_Test, sizeof mbzPath_Test );
    Test__Expect_EQ(KTgS_OK, tgUSZ_Copy( mbzPath_Test, KTgMAX_FILE_PATH, ROOT P01 PSEP, KTgMAX_RSIZE ));
    Test__Expect_EQ(KTgS_OK, tgCM_Path_Append( mbzPath_Test, KTgMAX_FILE_PATH, PSEP P02 PSEP, KTgMAX_RSIZE ));
    TgMSGF( 0xC, UNIT_TEST__MSG_LITERAL_3, u8"TEST:", u8"", u8"", u8"tgCM_Path_Append", mbzPath_Test );
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, mbzPath_Test, KTgMAX_RSIZE, 0, ROOT P01 PSEP P02 PSEP, KTgMAX_RSIZE, 0 )) && (0 == iRet));

    tgMM_Set_U08_0x00( mbzPath_Test, sizeof mbzPath_Test );
    Test__Expect_EQ(KTgS_OK, tgUSZ_Copy( mbzPath_Test, KTgMAX_FILE_PATH, ROOT P01, KTgMAX_RSIZE ));
    Test__Expect_EQ(KTgS_OK, tgCM_Path_Append( mbzPath_Test, KTgMAX_FILE_PATH, P02 PSEP, KTgMAX_RSIZE ));
    TgMSGF( 0xC, UNIT_TEST__MSG_LITERAL_3, u8"TEST:", u8"", u8"", u8"tgCM_Path_Append", mbzPath_Test );
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, mbzPath_Test, KTgMAX_RSIZE, 0, ROOT P01 PSEP P02 PSEP, KTgMAX_RSIZE, 0 )) && (0 == iRet));

    tgMM_Set_U08_0x00( mbzPath_Test, sizeof mbzPath_Test );
    Test__Expect_EQ(KTgS_OK, tgUSZ_Copy( mbzPath_Test, KTgMAX_FILE_PATH, ROOT P01, KTgMAX_RSIZE ));
    Test__Expect_EQ(KTgS_OK, tgCM_Path_Append( mbzPath_Test, KTgMAX_FILE_PATH, PSEP P02 PSEP, KTgMAX_RSIZE ));
    TgMSGF( 0xC, UNIT_TEST__MSG_LITERAL_3, u8"TEST:", u8"", u8"", u8"tgCM_Path_Append", mbzPath_Test );
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, mbzPath_Test, KTgMAX_RSIZE, 0, ROOT P01 PSEP P02 PSEP, KTgMAX_RSIZE, 0 )) && (0 == iRet));

    tgMM_Set_U08_0x00( mbzPath_Test, sizeof mbzPath_Test );
    Test__Expect_EQ(KTgS_OK, tgUSZ_Copy( mbzPath_Test, KTgMAX_FILE_PATH, ROOT P01 PSEP, KTgMAX_RSIZE ));
    Test__Expect_EQ(KTgS_OK, tgCM_Path_Append( mbzPath_Test, KTgMAX_FILE_PATH, NAME FSEP EXT_01, KTgMAX_RSIZE ));
    TgMSGF( 0xC, UNIT_TEST__MSG_LITERAL_3, u8"TEST:", u8"", u8"", u8"tgCM_Path_Append", mbzPath_Test );
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, mbzPath_Test, KTgMAX_RSIZE, 0, ROOT P01 PSEP NAME FSEP EXT_01, KTgMAX_RSIZE, 0 )) && (0 == iRet));

    tgMM_Set_U08_0x00( mbzPath_Test, sizeof mbzPath_Test );
    Test__Expect_EQ(KTgS_OK, tgUSZ_Copy( mbzPath_Test, KTgMAX_FILE_PATH, ROOT P01 PSEP, KTgMAX_RSIZE ));
    Test__Expect_EQ(KTgS_OK, tgCM_Path_Append( mbzPath_Test, KTgMAX_FILE_PATH, PSEP NAME FSEP EXT_01, KTgMAX_RSIZE ));
    TgMSGF( 0xC, UNIT_TEST__MSG_LITERAL_3, u8"TEST:", u8"", u8"", u8"tgCM_Path_Append", mbzPath_Test );
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, mbzPath_Test, KTgMAX_RSIZE, 0, ROOT P01 PSEP NAME FSEP EXT_01, KTgMAX_RSIZE, 0 )) && (0 == iRet));

    tgMM_Set_U08_0x00( mbzPath_Test, sizeof mbzPath_Test );
    Test__Expect_EQ(KTgS_OK, tgUSZ_Copy( mbzPath_Test, KTgMAX_FILE_PATH, ROOT P01, KTgMAX_RSIZE ));
    Test__Expect_EQ(KTgS_OK, tgCM_Path_Append( mbzPath_Test, KTgMAX_FILE_PATH, NAME FSEP EXT_01, KTgMAX_RSIZE ));
    TgMSGF( 0xC, UNIT_TEST__MSG_LITERAL_3, u8"TEST:", u8"", u8"", u8"tgCM_Path_Append", mbzPath_Test );
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, mbzPath_Test, KTgMAX_RSIZE, 0, ROOT P01 PSEP NAME FSEP EXT_01, KTgMAX_RSIZE, 0 )) && (0 == iRet));

    tgMM_Set_U08_0x00( mbzPath_Test, sizeof mbzPath_Test );
    Test__Expect_EQ(KTgS_OK, tgUSZ_Copy( mbzPath_Test, KTgMAX_FILE_PATH, ROOT P01, KTgMAX_RSIZE ));
    Test__Expect_EQ(KTgS_OK, tgCM_Path_Append( mbzPath_Test, KTgMAX_FILE_PATH, PSEP NAME FSEP EXT_01, KTgMAX_RSIZE ));
    TgMSGF( 0xC, UNIT_TEST__MSG_LITERAL_3, u8"TEST:", u8"", u8"", u8"tgCM_Path_Append", mbzPath_Test );
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, mbzPath_Test, KTgMAX_RSIZE, 0, ROOT P01 PSEP NAME FSEP EXT_01, KTgMAX_RSIZE, 0 )) && (0 == iRet));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_Path_Common_Prefix_Size_U08 -------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_Path_Common_Prefix_Size_U08 )
{
    TgCHAR_U8                           mbzPath_ARG[KTgMAX_FILE_PATH] = { 0 };
    TgRSIZE                             nbyPath_ARG;

    tgMM_Set_U08_0x00( mbzPath_ARG, sizeof mbzPath_ARG );
    Test__Expect_EQ(KTgS_OK, tgUSZ_Copy( mbzPath_ARG, KTgMAX_FILE_PATH, ROOT P01 PSEP P02, KTgMAX_RSIZE ));
    nbyPath_ARG = tgUSZ_Length_U08( mbzPath_ARG, KTgMAX_FILE_PATH );
    Test__Expect_EQ( nbyPath_ARG, tgCM_Path_Common_Prefix_Size_U08( mbzPath_ARG, KTgMAX_FILE_PATH, ROOT P01 PSEP P02 PSEP P03 PSEP P04, KTgMAX_RSIZE ));

    tgMM_Set_U08_0x00( mbzPath_ARG, sizeof mbzPath_ARG );
    Test__Expect_EQ(KTgS_OK, tgUSZ_Copy( mbzPath_ARG, KTgMAX_FILE_PATH, ROOT P01 PSEP P03, KTgMAX_RSIZE ));
    nbyPath_ARG = tgUSZ_Length_U08( mbzPath_ARG, KTgMAX_FILE_PATH ); /* Last code point in P03 is two bytes */
    mbzPath_ARG[nbyPath_ARG-1] ^= 3;
    Test__Expect_EQ(nbyPath_ARG - 2, tgCM_Path_Common_Prefix_Size_U08( mbzPath_ARG, KTgMAX_FILE_PATH, ROOT P01 PSEP P03 PSEP P03 PSEP P04, KTgMAX_RSIZE ));

    tgMM_Set_U08_0x00( mbzPath_ARG, sizeof mbzPath_ARG );
    Test__Expect_EQ(KTgS_OK, tgUSZ_Copy( mbzPath_ARG, KTgMAX_FILE_PATH, ROOT P01 PSEP P02, KTgMAX_RSIZE ));
    nbyPath_ARG = tgUSZ_Length_U08( mbzPath_ARG, KTgMAX_FILE_PATH );
    Test__Expect_EQ(nbyPath_ARG, tgCM_Path_Common_Prefix_Size_U08( mbzPath_ARG, KTgMAX_FILE_PATH,  ROOT P01 PSEP P02 PSEP P03, KTgMAX_RSIZE ));

    tgMM_Set_U08_0x00( mbzPath_ARG, sizeof mbzPath_ARG );
    Test__Expect_EQ(KTgS_OK, tgUSZ_Copy( mbzPath_ARG, KTgMAX_FILE_PATH, ROOT P01 PSEP P02 PSEP P03 PSEP P04, KTgMAX_RSIZE ));
    nbyPath_ARG = tgUSZ_Length_U08( mbzPath_ARG, KTgMAX_FILE_PATH );
    Test__Expect_EQ(nbyPath_ARG, tgCM_Path_Common_Prefix_Size_U08( ROOT P01 PSEP P02 PSEP P03 PSEP P04 PSEP, KTgMAX_RSIZE, mbzPath_ARG, KTgMAX_FILE_PATH ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_Path_Common_Prefix_Size_Count ------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_Path_Common_Prefix_Size_Count )
{
    TgCHAR_U8                           mbzPath_ARG[KTgMAX_FILE_PATH] = { 0 };
    TgRSIZE                             nbyPath_ARG;
    TgRSIZE                             nuiPath_ARG;

    tgMM_Set_U08_0x00( mbzPath_ARG, sizeof mbzPath_ARG );
    Test__Expect_EQ(KTgS_OK, tgUSZ_Copy( mbzPath_ARG, KTgMAX_FILE_PATH, ROOT P01 PSEP P02, KTgMAX_RSIZE ));
    Test__Expect_EQ(KTgS_OK, tgUSZ_Length_Count( &nuiPath_ARG, mbzPath_ARG, KTgMAX_FILE_PATH ));
    Test__Expect_EQ(nuiPath_ARG, tgCM_Path_Common_Prefix_Size_Count( mbzPath_ARG, KTgMAX_FILE_PATH, ROOT P01 PSEP P02 PSEP P03 PSEP P04, KTgMAX_RSIZE ));

    tgMM_Set_U08_0x00( mbzPath_ARG, sizeof mbzPath_ARG );
    Test__Expect_EQ(KTgS_OK, tgUSZ_Copy( mbzPath_ARG, KTgMAX_FILE_PATH, ROOT P01 PSEP P03, KTgMAX_RSIZE ));
    Test__Expect_EQ(KTgS_OK, tgUSZ_Length_Count( &nuiPath_ARG, mbzPath_ARG, KTgMAX_FILE_PATH ));
    nbyPath_ARG = tgUSZ_Length_U08( mbzPath_ARG, KTgMAX_FILE_PATH ); /* Last code point in P03 is two bytes */
    mbzPath_ARG[nbyPath_ARG-1] ^= 3;
    Test__Expect_EQ(nuiPath_ARG - 1, tgCM_Path_Common_Prefix_Size_Count( mbzPath_ARG, KTgMAX_FILE_PATH, ROOT P01 PSEP P03 PSEP P03 PSEP P04, KTgMAX_RSIZE ));

    tgMM_Set_U08_0x00( mbzPath_ARG, sizeof mbzPath_ARG );
    Test__Expect_EQ(KTgS_OK, tgUSZ_Copy( mbzPath_ARG, KTgMAX_FILE_PATH, ROOT P01 PSEP P02, KTgMAX_RSIZE ));
    Test__Expect_EQ(KTgS_OK, tgUSZ_Length_Count( &nuiPath_ARG, mbzPath_ARG, KTgMAX_FILE_PATH ));
    Test__Expect_EQ(nuiPath_ARG, tgCM_Path_Common_Prefix_Size_Count( mbzPath_ARG, KTgMAX_FILE_PATH,  ROOT P01 PSEP P02 PSEP P03, KTgMAX_RSIZE ));

    tgMM_Set_U08_0x00( mbzPath_ARG, sizeof mbzPath_ARG );
    Test__Expect_EQ(KTgS_OK, tgUSZ_Copy( mbzPath_ARG, KTgMAX_FILE_PATH, ROOT P01 PSEP P02 PSEP P03 PSEP P04, KTgMAX_RSIZE ));
    Test__Expect_EQ(KTgS_OK, tgUSZ_Length_Count( &nuiPath_ARG, mbzPath_ARG, KTgMAX_FILE_PATH ));
    Test__Expect_EQ(nuiPath_ARG, tgCM_Path_Common_Prefix_Size_Count( ROOT P01 PSEP P02 PSEP P03 PSEP P04 PSEP, KTgMAX_RSIZE, mbzPath_ARG, KTgMAX_FILE_PATH ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_Path_Common_Prefix ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_Path_Common_Prefix )
{
    TgCHAR_U8                           mbzPath_Test[KTgMAX_FILE_PATH] = { 0 };
    TgCHAR_U8                           mbzPath_ARG[KTgMAX_FILE_PATH] = { 0 };
    TgSINT_E08                          iRet;

    tgMM_Set_U08_0x00( mbzPath_Test, sizeof mbzPath_Test );
    Test__Expect_EQ(KTgS_OK, tgCM_Path_Common_Prefix( mbzPath_Test, KTgMAX_FILE_PATH, ROOT P01 PSEP P02, KTgMAX_RSIZE, ROOT P01 PSEP P02 PSEP P03 PSEP P04, KTgMAX_RSIZE ));
    TgMSGF( 0xC, UNIT_TEST__MSG_LITERAL_3, u8"TEST:", u8"", u8"", u8"tgCM_Path_Common_Prefix", mbzPath_Test );
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, mbzPath_Test, KTgMAX_RSIZE, 0, ROOT P01 PSEP P02, KTgMAX_RSIZE, 0 )) && (0 == iRet));

    tgMM_Set_U08_0x00( mbzPath_Test, sizeof mbzPath_Test );
    Test__Expect_EQ(KTgS_OK, tgUSZ_Copy( mbzPath_ARG, KTgMAX_FILE_PATH, ROOT P01 PSEP P03, KTgMAX_RSIZE ));
    mbzPath_ARG[tgUSZ_Length_U08( mbzPath_ARG, KTgMAX_FILE_PATH)-1] ^= 3;
    Test__Expect_EQ(KTgS_OK, tgCM_Path_Common_Prefix( mbzPath_Test, KTgMAX_FILE_PATH, mbzPath_ARG, KTgMAX_FILE_PATH, ROOT P01 PSEP P03 PSEP P03 PSEP P04, KTgMAX_RSIZE ));
    TgMSGF( 0xC, UNIT_TEST__MSG_LITERAL_3, u8"TEST:", u8"", u8"", u8"tgCM_Path_Common_Prefix", mbzPath_Test );
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, mbzPath_Test, KTgMAX_RSIZE, 0, ROOT P01 PSEP u8"тестовое задан", KTgMAX_RSIZE, 0 )) && (0 == iRet));

    tgMM_Set_U08_0x00( mbzPath_Test, sizeof mbzPath_Test );
    Test__Expect_EQ(KTgS_OK, tgCM_Path_Common_Prefix( mbzPath_Test, KTgMAX_FILE_PATH, ROOT P01 PSEP P02, KTgMAX_RSIZE, ROOT P01 PSEP P02 PSEP P03, KTgMAX_RSIZE ));
    TgMSGF( 0xC, UNIT_TEST__MSG_LITERAL_3, u8"TEST:", u8"", u8"", u8"tgCM_Path_Common_Prefix", mbzPath_Test );
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, mbzPath_Test, KTgMAX_RSIZE, 0, ROOT P01 PSEP P02, KTgMAX_RSIZE, 0 )) && (0 == iRet));

    tgMM_Set_U08_0x00( mbzPath_Test, sizeof mbzPath_Test );
    Test__Expect_EQ(KTgS_OK, tgCM_Path_Common_Prefix( mbzPath_Test, KTgMAX_FILE_PATH, ROOT P01 PSEP P02 PSEP P03 PSEP P04, KTgMAX_RSIZE, ROOT P01 PSEP P02, KTgMAX_RSIZE ));
    TgMSGF( 0xC, UNIT_TEST__MSG_LITERAL_3, u8"TEST:", u8"", u8"", u8"tgCM_Path_Common_Prefix", mbzPath_Test );
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, mbzPath_Test, KTgMAX_RSIZE, 0, ROOT P01 PSEP P02, KTgMAX_RSIZE, 0 )) && (0 == iRet));

    tgMM_Set_U08_0x00( mbzPath_Test, sizeof mbzPath_Test );
    Test__Expect_EQ(KTgS_OK, tgCM_Path_Common_Prefix( mbzPath_Test, KTgMAX_FILE_PATH, ROOT P01 PSEP P02 PSEP P03, KTgMAX_RSIZE, ROOT P01 PSEP P02, KTgMAX_RSIZE ));
    TgMSGF( 0xC, UNIT_TEST__MSG_LITERAL_3, u8"TEST:", u8"", u8"", u8"tgCM_Path_Common_Prefix", mbzPath_Test );
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, mbzPath_Test, KTgMAX_RSIZE, 0, ROOT P01 PSEP P02, KTgMAX_RSIZE, 0 )) && (0 == iRet));

    tgMM_Set_U08_0x00( mbzPath_Test, sizeof mbzPath_Test );
    Test__Expect_EQ(KTgS_OK, tgCM_Path_Common_Prefix( mbzPath_Test, KTgMAX_FILE_PATH, ROOT P01 PSEP P02, KTgMAX_RSIZE, ROOT P01 PSEP P02, KTgMAX_RSIZE ));
    TgMSGF( 0xC, UNIT_TEST__MSG_LITERAL_3, u8"TEST:", u8"", u8"", u8"tgCM_Path_Common_Prefix", mbzPath_Test );
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, mbzPath_Test, KTgMAX_RSIZE, 0, ROOT P01 PSEP P02, KTgMAX_RSIZE, 0 )) && (0 == iRet));

    tgMM_Set_U08_0x00( mbzPath_Test, sizeof mbzPath_Test );
    Test__Expect_EQ(KTgS_OK, tgCM_Path_Common_Prefix( mbzPath_Test, KTgMAX_FILE_PATH, ROOT P01 PSEP P02 FSEP EXT_01, KTgMAX_RSIZE, ROOT P01 PSEP P02, KTgMAX_RSIZE ));
    TgMSGF( 0xC, UNIT_TEST__MSG_LITERAL_3, u8"TEST:", u8"", u8"", u8"tgCM_Path_Common_Prefix", mbzPath_Test );
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, mbzPath_Test, KTgMAX_RSIZE, 0, ROOT P01 PSEP P02, KTgMAX_RSIZE, 0 )) && (0 == iRet));

    tgMM_Set_U08_0x00( mbzPath_Test, sizeof mbzPath_Test );
    Test__Expect_EQ(KTgS_OK, tgCM_Path_Common_Prefix( mbzPath_Test, KTgMAX_FILE_PATH, ROOT P01 PSEP NAME FSEP EXT_01, KTgMAX_RSIZE, ROOT P01, KTgMAX_RSIZE ));
    TgMSGF( 0xC, UNIT_TEST__MSG_LITERAL_3, u8"TEST:", u8"", u8"", u8"tgCM_Path_Common_Prefix", mbzPath_Test );
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, mbzPath_Test, KTgMAX_RSIZE, 0, ROOT P01, KTgMAX_RSIZE, 0 )) && (0 == iRet));

    tgMM_Set_U08_0x00( mbzPath_Test, sizeof mbzPath_Test );
    Test__Expect_EQ(KTgS_OK, tgCM_Path_Common_Prefix( mbzPath_Test, KTgMAX_FILE_PATH, ROOT P01 PSEP NAME FSEP EXT_01, KTgMAX_RSIZE, ROOT, KTgMAX_RSIZE ));
    TgMSGF( 0xC, UNIT_TEST__MSG_LITERAL_3, u8"TEST:", u8"", u8"", u8"tgCM_Path_Common_Prefix", mbzPath_Test );
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, mbzPath_Test, KTgMAX_RSIZE, 0, ROOT, KTgMAX_RSIZE, 0 )) && (0 == iRet));

    tgMM_Set_U08_0x00( mbzPath_Test, sizeof mbzPath_Test );
    Test__Expect_EQ(KTgS_OK, tgCM_Path_Common_Prefix( mbzPath_Test, KTgMAX_FILE_PATH, ROOT P01 PSEP P02, KTgMAX_RSIZE, ROOT P01 PSEP P02 FSEP EXT_01, KTgMAX_RSIZE ));
    TgMSGF( 0xC, UNIT_TEST__MSG_LITERAL_3, u8"TEST:", u8"", u8"", u8"tgCM_Path_Common_Prefix", mbzPath_Test );
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, mbzPath_Test, KTgMAX_RSIZE, 0, ROOT P01 PSEP P02, KTgMAX_RSIZE, 0 )) && (0 == iRet));

    tgMM_Set_U08_0x00( mbzPath_Test, sizeof mbzPath_Test );
    Test__Expect_EQ(KTgS_OK, tgCM_Path_Common_Prefix( mbzPath_Test, KTgMAX_FILE_PATH, ROOT P01, KTgMAX_RSIZE, ROOT P01 PSEP NAME FSEP EXT_01, KTgMAX_RSIZE ));
    TgMSGF( 0xC, UNIT_TEST__MSG_LITERAL_3, u8"TEST:", u8"", u8"", u8"tgCM_Path_Common_Prefix", mbzPath_Test );
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, mbzPath_Test, KTgMAX_RSIZE, 0, ROOT P01, KTgMAX_RSIZE, 0 )) && (0 == iRet));

    tgMM_Set_U08_0x00( mbzPath_Test, sizeof mbzPath_Test );
    Test__Expect_EQ(KTgS_OK, tgCM_Path_Common_Prefix( mbzPath_Test, KTgMAX_FILE_PATH, ROOT, KTgMAX_RSIZE, ROOT P01 PSEP NAME FSEP EXT_01, KTgMAX_RSIZE ));
    TgMSGF( 0xC, UNIT_TEST__MSG_LITERAL_3, u8"TEST:", u8"", u8"", u8"tgCM_Path_Common_Prefix", mbzPath_Test );
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, mbzPath_Test, KTgMAX_RSIZE, 0, ROOT, KTgMAX_RSIZE, 0 )) && (0 == iRet));

    tgMM_Set_U08_0x00( mbzPath_Test, sizeof mbzPath_Test );
    Test__Expect_EQ(KTgS_OK, tgCM_Path_Common_Prefix( mbzPath_Test, KTgMAX_FILE_PATH, ROOT P01 PSEP P02 PSEP P03 PSEP P04 PSEP, KTgMAX_RSIZE, ROOT P01 PSEP P02 PSEP P03 PSEP P04, KTgMAX_RSIZE ));
    TgMSGF( 0xC, UNIT_TEST__MSG_LITERAL_3, u8"TEST:", u8"", u8"", u8"tgCM_Path_Common_Prefix", mbzPath_Test );
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, mbzPath_Test, KTgMAX_RSIZE, 0, ROOT P01 PSEP P02 PSEP P03 PSEP P04, KTgMAX_RSIZE, 0 )) && (0 == iRet));

    tgMM_Set_U08_0x00( mbzPath_Test, sizeof mbzPath_Test );
    Test__Expect_EQ(KTgS_OK, tgCM_Path_Common_Prefix( mbzPath_Test, KTgMAX_FILE_PATH, ROOT P01 PSEP P02 PSEP P03 PSEP P04, KTgMAX_RSIZE, ROOT P01 PSEP P02 PSEP P03 PSEP P04, KTgMAX_RSIZE ));
    TgMSGF( 0xC, UNIT_TEST__MSG_LITERAL_3, u8"TEST:", u8"", u8"", u8"tgCM_Path_Common_Prefix", mbzPath_Test );
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, mbzPath_Test, KTgMAX_RSIZE, 0, ROOT P01 PSEP P02 PSEP P03 PSEP P04, KTgMAX_RSIZE, 0 )) && (0 == iRet));

    tgMM_Set_U08_0x00( mbzPath_Test, sizeof mbzPath_Test );
    Test__Expect_EQ(KTgS_OK, tgCM_Path_Common_Prefix( mbzPath_Test, KTgMAX_FILE_PATH, ROOT P01 PSEP P02 PSEP P03 PSEP P04 FSEP P03, KTgMAX_RSIZE, ROOT P01 PSEP P02 PSEP P03 PSEP P04, KTgMAX_RSIZE ));
    TgMSGF( 0xC, UNIT_TEST__MSG_LITERAL_3, u8"TEST:", u8"", u8"", u8"tgCM_Path_Common_Prefix", mbzPath_Test );
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, mbzPath_Test, KTgMAX_RSIZE, 0, ROOT P01 PSEP P02 PSEP P03 PSEP P04, KTgMAX_RSIZE, 0 )) && (0 == iRet));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_Path_Remove_Separator -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_Path_Remove_Separator )
{
    TgCHAR_U8                           mbzPath_Test[KTgMAX_FILE_PATH] = { 0 };
    TgSINT_E08                          iRet;

    tgMM_Set_U08_0x00( mbzPath_Test, sizeof mbzPath_Test );
    Test__Expect_EQ(KTgS_OK, tgUSZ_Copy( mbzPath_Test, KTgMAX_FILE_PATH, ROOT P01 PSEP P02, KTgMAX_RSIZE ));
    Test__Expect_EQ(KTgS_OK, tgCM_Path_Remove_Separator( mbzPath_Test, KTgMAX_FILE_PATH ));
    TgMSGF( 0xC, UNIT_TEST__MSG_LITERAL_3, u8"TEST:", u8"", u8"", u8"tgCM_Path_Remove_Separator", mbzPath_Test );
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, mbzPath_Test, KTgMAX_RSIZE, 0, ROOT P01 PSEP P02, KTgMAX_RSIZE, 0 )) && (0 == iRet));

    tgMM_Set_U08_0x00( mbzPath_Test, sizeof mbzPath_Test );
    Test__Expect_EQ(KTgS_OK, tgUSZ_Copy( mbzPath_Test, KTgMAX_FILE_PATH, ROOT P01 PSEP P02 PSEP, KTgMAX_RSIZE ));
    Test__Expect_EQ(KTgS_OK, tgCM_Path_Remove_Separator( mbzPath_Test, KTgMAX_FILE_PATH ));
    TgMSGF( 0xC, UNIT_TEST__MSG_LITERAL_3, u8"TEST:", u8"", u8"", u8"tgCM_Path_Remove_Separator", mbzPath_Test );
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, mbzPath_Test, KTgMAX_RSIZE, 0, ROOT P01 PSEP P02, KTgMAX_RSIZE, 0 )) && (0 == iRet));

    tgMM_Set_U08_0x00( mbzPath_Test, sizeof mbzPath_Test );
    Test__Expect_EQ(KTgS_OK, tgUSZ_Copy( mbzPath_Test, KTgMAX_FILE_PATH, ROOT P01 PSEP NAME FSEP EXT_01, KTgMAX_RSIZE ));
    Test__Expect_EQ(KTgS_OK, tgCM_Path_Remove_Separator( mbzPath_Test, KTgMAX_FILE_PATH ));
    TgMSGF( 0xC, UNIT_TEST__MSG_LITERAL_3, u8"TEST:", u8"", u8"", u8"tgCM_Path_Remove_Separator", mbzPath_Test );
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, mbzPath_Test, KTgMAX_RSIZE, 0, ROOT P01 PSEP NAME FSEP EXT_01, KTgMAX_RSIZE, 0 )) && (0 == iRet));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_Path_Remove_Extension -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_Path_Remove_Extension )
{
    TgCHAR_U8                           mbzPath_Test[KTgMAX_FILE_PATH] = { 0 };
    TgSINT_E08                          iRet;

    tgMM_Set_U08_0x00( mbzPath_Test, sizeof mbzPath_Test );
    Test__Expect_EQ(KTgS_OK, tgUSZ_Copy( mbzPath_Test, KTgMAX_FILE_PATH, ROOT P01 PSEP NAME, KTgMAX_RSIZE ));
    Test__Expect_EQ(KTgE_FAIL, tgCM_Path_Remove_Extension( mbzPath_Test, KTgMAX_FILE_PATH ));
    TgMSGF( 0xC, UNIT_TEST__MSG_LITERAL_3, u8"TEST:", u8"", u8"", u8"tgCM_Path_Remove_Extension", mbzPath_Test );
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, mbzPath_Test, KTgMAX_RSIZE, 0, ROOT P01 PSEP NAME, KTgMAX_RSIZE, 0 )) && (0 == iRet));

    tgMM_Set_U08_0x00( mbzPath_Test, sizeof mbzPath_Test );
    Test__Expect_EQ(KTgS_OK, tgUSZ_Copy( mbzPath_Test, KTgMAX_FILE_PATH, ROOT P01 PSEP NAME FSEP EXT_01, KTgMAX_RSIZE ));
    Test__Expect_EQ(KTgS_OK, tgCM_Path_Remove_Extension( mbzPath_Test, KTgMAX_FILE_PATH ));
    TgMSGF( 0xC, UNIT_TEST__MSG_LITERAL_3, u8"TEST:", u8"", u8"", u8"tgCM_Path_Remove_Extension", mbzPath_Test );
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, mbzPath_Test, KTgMAX_RSIZE, 0, ROOT P01 PSEP NAME, KTgMAX_RSIZE, 0 )) && (0 == iRet));

    tgMM_Set_U08_0x00( mbzPath_Test, sizeof mbzPath_Test );
    Test__Expect_EQ(KTgS_OK, tgUSZ_Copy( mbzPath_Test, KTgMAX_FILE_PATH, ROOT P01 PSEP NAME FSEP EXT_01 FSEP EXT_02, KTgMAX_RSIZE ));
    Test__Expect_EQ(KTgS_OK, tgCM_Path_Remove_Extension( mbzPath_Test, KTgMAX_FILE_PATH ));
    TgMSGF( 0xC, UNIT_TEST__MSG_LITERAL_3, u8"TEST:", u8"", u8"", u8"tgCM_Path_Remove_Extension", mbzPath_Test );
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, mbzPath_Test, KTgMAX_RSIZE, 0, ROOT P01 PSEP NAME FSEP EXT_01, KTgMAX_RSIZE, 0 )) && (0 == iRet));

    tgMM_Set_U08_0x00( mbzPath_Test, sizeof mbzPath_Test );
    Test__Expect_EQ(KTgS_OK, tgUSZ_Copy( mbzPath_Test, KTgMAX_FILE_PATH, ROOT P01 PSEP P02 PSEP, KTgMAX_RSIZE ));
    Test__Expect_EQ(KTgE_FAIL, tgCM_Path_Remove_Extension( mbzPath_Test, KTgMAX_FILE_PATH ));
    TgMSGF( 0xC, UNIT_TEST__MSG_LITERAL_3, u8"TEST:", u8"", u8"", u8"tgCM_Path_Remove_Extension", mbzPath_Test );
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, mbzPath_Test, KTgMAX_RSIZE, 0, ROOT P01 PSEP P02 PSEP, KTgMAX_RSIZE, 0 )) && (0 == iRet));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_Path_Remove_File_Name -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_Path_Remove_File_Name )
{
    TgCHAR_U8                           mbzPath_Test[KTgMAX_FILE_PATH] = { 0 };
    TgSINT_E08                          iRet;

    tgMM_Set_U08_0x00( mbzPath_Test, sizeof mbzPath_Test );
    Test__Expect_EQ(KTgS_OK, tgUSZ_Copy( mbzPath_Test, KTgMAX_FILE_PATH, ROOT P01 PSEP P02, KTgMAX_RSIZE ));
    Test__Expect_EQ(KTgS_OK, tgCM_Path_Remove_File_Name( mbzPath_Test, KTgMAX_FILE_PATH ));
    TgMSGF( 0xC, UNIT_TEST__MSG_LITERAL_3, u8"TEST:", u8"", u8"", u8"tgCM_Path_Remove_File_Name", mbzPath_Test );
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, mbzPath_Test, KTgMAX_RSIZE, 0, ROOT P01 PSEP, KTgMAX_RSIZE, 0 )) && (0 == iRet));

    tgMM_Set_U08_0x00( mbzPath_Test, sizeof mbzPath_Test );
    Test__Expect_EQ(KTgS_OK, tgUSZ_Copy( mbzPath_Test, KTgMAX_FILE_PATH, ROOT P01 PSEP P02 PSEP, KTgMAX_RSIZE ));
    Test__Expect_NE(KTgS_OK, tgCM_Path_Remove_File_Name( mbzPath_Test, KTgMAX_FILE_PATH ));
    TgMSGF( 0xC, UNIT_TEST__MSG_LITERAL_3, u8"TEST:", u8"", u8"", u8"tgCM_Path_Remove_File_Name", mbzPath_Test );
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, mbzPath_Test, KTgMAX_RSIZE, 0, ROOT P01 PSEP P02 PSEP, KTgMAX_RSIZE, 0 )) && (0 == iRet));

    tgMM_Set_U08_0x00( mbzPath_Test, sizeof mbzPath_Test );
    Test__Expect_EQ(KTgS_OK, tgUSZ_Copy( mbzPath_Test, KTgMAX_FILE_PATH, ROOT P01 PSEP NAME FSEP EXT_01, KTgMAX_RSIZE ));
    Test__Expect_EQ(KTgS_OK, tgCM_Path_Remove_File_Name( mbzPath_Test, KTgMAX_FILE_PATH ));
    TgMSGF( 0xC, UNIT_TEST__MSG_LITERAL_3, u8"TEST:", u8"", u8"", u8"tgCM_Path_Remove_File_Name", mbzPath_Test );
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, mbzPath_Test, KTgMAX_RSIZE, 0, ROOT P01 PSEP, KTgMAX_RSIZE, 0 )) && (0 == iRet));

    tgMM_Set_U08_0x00( mbzPath_Test, sizeof mbzPath_Test );
    Test__Expect_EQ(KTgS_OK, tgUSZ_Copy( mbzPath_Test, KTgMAX_FILE_PATH, ROOT P01 PSEP P02, KTgMAX_RSIZE ));
    Test__Expect_EQ(KTgS_OK, tgCM_Path_Remove_File_Name( mbzPath_Test, KTgMAX_FILE_PATH ));
    TgMSGF( 0xC, UNIT_TEST__MSG_LITERAL_3, u8"TEST:", u8"", u8"", u8"tgCM_Path_Remove_File_Name", mbzPath_Test );
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, mbzPath_Test, KTgMAX_RSIZE, 0, ROOT P01 PSEP, KTgMAX_RSIZE, 0 )) && (0 == iRet));

    tgMM_Set_U08_0x00( mbzPath_Test, sizeof mbzPath_Test );
    Test__Expect_EQ(KTgS_OK, tgUSZ_Copy( mbzPath_Test, KTgMAX_FILE_PATH, ROOT P01 PSEP NAME FSEP EXT_01 FSEP EXT_02, KTgMAX_RSIZE ));
    Test__Expect_EQ(KTgS_OK, tgCM_Path_Remove_File_Name( mbzPath_Test, KTgMAX_FILE_PATH ));
    TgMSGF( 0xC, UNIT_TEST__MSG_LITERAL_3, u8"TEST:", u8"", u8"", u8"tgCM_Path_Remove_File_Name", mbzPath_Test );
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, mbzPath_Test, KTgMAX_RSIZE, 0, ROOT P01 PSEP, KTgMAX_RSIZE, 0 )) && (0 == iRet));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_Path_Rename_Extension -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_Path_Rename_Extension )
{
    TgCHAR_U8                           mbzPath_Test[KTgMAX_FILE_PATH] = { 0 };
    TgSINT_E08                          iRet;

    tgMM_Set_U08_0x00( mbzPath_Test, sizeof mbzPath_Test );
    Test__Expect_EQ(KTgS_OK, tgUSZ_Copy( mbzPath_Test, KTgMAX_FILE_PATH, ROOT P01 PSEP P02, KTgMAX_RSIZE ));
    Test__Expect_EQ(KTgE_FAIL, tgCM_Path_Rename_Extension( mbzPath_Test, KTgMAX_FILE_PATH, EXT_02, KTgMAX_RSIZE ));
    TgMSGF( 0xC, UNIT_TEST__MSG_LITERAL_3, u8"TEST:", u8"", u8"", u8"tgCM_Path_Rename_Extension", mbzPath_Test );
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, mbzPath_Test, KTgMAX_RSIZE, 0, ROOT P01 PSEP P02, KTgMAX_RSIZE, 0 )) && (0 == iRet));

    tgMM_Set_U08_0x00( mbzPath_Test, sizeof mbzPath_Test );
    Test__Expect_EQ(KTgS_OK, tgUSZ_Copy( mbzPath_Test, KTgMAX_FILE_PATH, ROOT P01 PSEP NAME FSEP EXT_01, KTgMAX_RSIZE ));
    Test__Expect_EQ(KTgS_OK, tgCM_Path_Rename_Extension( mbzPath_Test, KTgMAX_FILE_PATH, EXT_02, KTgMAX_RSIZE ));
    TgMSGF( 0xC, UNIT_TEST__MSG_LITERAL_3, u8"TEST:", u8"", u8"", u8"tgCM_Path_Rename_Extension", mbzPath_Test );
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, mbzPath_Test, KTgMAX_RSIZE, 0, ROOT P01 PSEP NAME FSEP EXT_02, KTgMAX_RSIZE, 0 )) && (0 == iRet));

    tgMM_Set_U08_0x00( mbzPath_Test, sizeof mbzPath_Test );
    Test__Expect_EQ(KTgS_OK, tgUSZ_Copy( mbzPath_Test, KTgMAX_FILE_PATH, ROOT P01 PSEP P02 PSEP, KTgMAX_RSIZE ));
    Test__Expect_EQ(KTgE_FAIL, tgCM_Path_Rename_Extension( mbzPath_Test, KTgMAX_FILE_PATH, EXT_02, KTgMAX_RSIZE ));
    TgMSGF( 0xC, UNIT_TEST__MSG_LITERAL_3, u8"TEST:", u8"", u8"", u8"tgCM_Path_Rename_Extension", mbzPath_Test );
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, mbzPath_Test, KTgMAX_RSIZE, 0, ROOT P01 PSEP P02 PSEP, KTgMAX_RSIZE, 0 )) && (0 == iRet));

    tgMM_Set_U08_0x00( mbzPath_Test, sizeof mbzPath_Test );
    Test__Expect_EQ(KTgS_OK, tgUSZ_Copy( mbzPath_Test, KTgMAX_FILE_PATH, FSEP EXT_01, KTgMAX_RSIZE ));
    Test__Expect_EQ(KTgS_OK, tgCM_Path_Rename_Extension( mbzPath_Test, KTgMAX_FILE_PATH, EXT_02, KTgMAX_RSIZE ));
    TgMSGF( 0xC, UNIT_TEST__MSG_LITERAL_3, u8"TEST:", u8"", u8"", u8"tgCM_Path_Rename_Extension", mbzPath_Test );
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, mbzPath_Test, KTgMAX_RSIZE, 0, FSEP EXT_02, KTgMAX_RSIZE, 0 )) && (0 == iRet));

    tgMM_Set_U08_0x00( mbzPath_Test, sizeof mbzPath_Test );
    Test__Expect_EQ(KTgS_OK, tgUSZ_Copy( mbzPath_Test, KTgMAX_FILE_PATH, NAME FSEP EXT_01, KTgMAX_RSIZE ));
    Test__Expect_EQ(KTgE_FAIL, tgCM_Path_Rename_Extension( mbzPath_Test, 5, EXT_02 EXT_02, KTgMAX_RSIZE ) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_Path_Remove_Folder ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_Path_Remove_Folder )
{
    TgCHAR_U8                           mbzPath_Test[KTgMAX_FILE_PATH] = { 0 };
    TgSINT_E08                          iRet;

    tgMM_Set_U08_0x00( mbzPath_Test, sizeof mbzPath_Test );
    Test__Expect_EQ(KTgS_OK, tgUSZ_Copy( mbzPath_Test, KTgMAX_FILE_PATH, ROOT P01 PSEP P02, KTgMAX_RSIZE ));
    Test__Expect_EQ(KTgS_OK, tgCM_Path_Remove_Folder( mbzPath_Test, KTgMAX_FILE_PATH ));
    TgMSGF( 0xC, UNIT_TEST__MSG_LITERAL_3, u8"TEST:", u8"", u8"", u8"tgCM_Path_Remove_Folder", mbzPath_Test );
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, mbzPath_Test, KTgMAX_RSIZE, 0, P02, KTgMAX_RSIZE, 0 )) && (0 == iRet));

    tgMM_Set_U08_0x00( mbzPath_Test, sizeof mbzPath_Test );
    Test__Expect_EQ(KTgS_OK, tgUSZ_Copy( mbzPath_Test, KTgMAX_FILE_PATH, ROOT P01 PSEP NAME FSEP EXT_01, KTgMAX_RSIZE ));
    Test__Expect_EQ(KTgS_OK, tgCM_Path_Remove_Folder( mbzPath_Test, KTgMAX_FILE_PATH  ));
    TgMSGF( 0xC, UNIT_TEST__MSG_LITERAL_3, u8"TEST:", u8"", u8"", u8"tgCM_Path_Remove_Folder", mbzPath_Test );
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, mbzPath_Test, KTgMAX_RSIZE, 0, NAME FSEP EXT_01, KTgMAX_RSIZE, 0 )) && (0 == iRet));

    tgMM_Set_U08_0x00( mbzPath_Test, sizeof mbzPath_Test );
    Test__Expect_EQ(KTgS_OK, tgUSZ_Copy( mbzPath_Test, KTgMAX_FILE_PATH, ROOT P01 PSEP P02 PSEP, KTgMAX_RSIZE ));
    Test__Expect_EQ(KTgS_OK, tgCM_Path_Remove_Folder( mbzPath_Test, KTgMAX_FILE_PATH ));
    TgMSGF( 0xC, UNIT_TEST__MSG_LITERAL_3, u8"TEST:", u8"", u8"", u8"tgCM_Path_Remove_Folder", mbzPath_Test );
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, mbzPath_Test, KTgMAX_RSIZE, 0, u8"", KTgMAX_RSIZE, 0 )) && (0 == iRet));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_Path_Init -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_Path_Init )
{
    TgCHAR_U8                           mbzPath_Test[KTgMAX_FILE_PATH] = { 0 };
    TgSINT_E08                          iRet;

    tgMM_Set_U08_0x00( mbzPath_Test, sizeof mbzPath_Test );
    Test__Expect_EQ(KTgS_OK, tgCM_Path_Init( mbzPath_Test, KTgMAX_FILE_PATH, ROOT, u8"" ));
    TgMSGF( 0xC, UNIT_TEST__MSG_LITERAL_3, u8"TEST:", u8"", u8"", u8"tgCM_Path_Init", mbzPath_Test );
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, mbzPath_Test, KTgMAX_RSIZE, 0, ROOT, KTgMAX_RSIZE, 0 )) && (0 == iRet));

    tgMM_Set_U08_0x00( mbzPath_Test, sizeof mbzPath_Test );
    Test__Expect_EQ(KTgS_OK, tgCM_Path_Init( mbzPath_Test, KTgMAX_FILE_PATH, ROOT, u8"" ));
    TgMSGF( 0xC, UNIT_TEST__MSG_LITERAL_3, u8"TEST:", u8"", u8"", u8"tgCM_Path_Init", mbzPath_Test );
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, mbzPath_Test, KTgMAX_RSIZE, 0, ROOT, KTgMAX_RSIZE, 0 )) && (0 == iRet));

    tgMM_Set_U08_0x00( mbzPath_Test, sizeof mbzPath_Test );
    Test__Expect_EQ(KTgS_OK, tgCM_Path_Init( mbzPath_Test, KTgMAX_FILE_PATH, P01, u8"" ));
    TgMSGF( 0xC, UNIT_TEST__MSG_LITERAL_3, u8"TEST:", u8"", u8"", u8"tgCM_Path_Init", mbzPath_Test );
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, mbzPath_Test, KTgMAX_RSIZE, 0, P01 PSEP, KTgMAX_RSIZE, 0 )) && (0 == iRet));

    tgMM_Set_U08_0x00( mbzPath_Test, sizeof mbzPath_Test );
    Test__Expect_EQ(KTgS_OK, tgCM_Path_Init( mbzPath_Test, KTgMAX_FILE_PATH, ROOT, P01, u8"" ));
    TgMSGF( 0xC, UNIT_TEST__MSG_LITERAL_3, u8"TEST:", u8"", u8"", u8"tgCM_Path_Init", mbzPath_Test );
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, mbzPath_Test, KTgMAX_RSIZE, 0, ROOT P01 PSEP, KTgMAX_RSIZE, 0 )) && (0 == iRet));

    tgMM_Set_U08_0x00( mbzPath_Test, sizeof mbzPath_Test );
    Test__Expect_EQ(KTgS_OK, tgCM_Path_Init( mbzPath_Test, KTgMAX_FILE_PATH, P01, P02, u8"" ));
    TgMSGF( 0xC, UNIT_TEST__MSG_LITERAL_3, u8"TEST:", u8"", u8"", u8"tgCM_Path_Init", mbzPath_Test );
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, mbzPath_Test, KTgMAX_RSIZE, 0, P01 PSEP P02 PSEP, KTgMAX_RSIZE, 0 )) && (0 == iRet));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_Path_Find_Extension ---------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_Path_Find_Extension )
{
    TgCHAR_U8                           mbzPath_Test[KTgMAX_FILE_PATH] = { 0 };
    TgRSIZE                             nbyOffset;
    TgSINT_E08                          iRet;

    tgMM_Set_U08_0x00( mbzPath_Test, sizeof mbzPath_Test );
    Test__Expect_EQ(KTgS_OK, tgUSZ_Copy( mbzPath_Test, KTgMAX_FILE_PATH, ROOT P01 PSEP P02, KTgMAX_RSIZE ));
    Test__Expect_NE(KTgS_OK, tgCM_Path_Find_Extension( &nbyOffset, mbzPath_Test, KTgMAX_FILE_PATH ));

    tgMM_Set_U08_0x00( mbzPath_Test, sizeof mbzPath_Test );
    Test__Expect_EQ(KTgS_OK, tgUSZ_Copy( mbzPath_Test, KTgMAX_FILE_PATH, ROOT P01 PSEP P02 PSEP, KTgMAX_RSIZE ));
    Test__Expect_NE(KTgS_OK, tgCM_Path_Find_Extension( &nbyOffset, mbzPath_Test, KTgMAX_FILE_PATH ));

    tgMM_Set_U08_0x00( mbzPath_Test, sizeof mbzPath_Test );
    Test__Expect_EQ(KTgS_OK, tgUSZ_Copy( mbzPath_Test, KTgMAX_FILE_PATH, ROOT P01 PSEP NAME FSEP EXT_01, KTgMAX_RSIZE ));
    Test__Expect_EQ(KTgS_OK, tgCM_Path_Find_Extension( &nbyOffset, mbzPath_Test, KTgMAX_FILE_PATH ));
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, mbzPath_Test + nbyOffset, KTgMAX_RSIZE, 0, FSEP EXT_01, KTgMAX_RSIZE, 0 )) && (0 == iRet));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_Path_Find_File_Name ---------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_Path_Find_File_Name )
{
    TgCHAR_U8                           mbzPath_Test[KTgMAX_FILE_PATH] = { 0 };
    TgRSIZE                             nbyOffset;
    TgSINT_E08                          iRet;

    tgMM_Set_U08_0x00( mbzPath_Test, sizeof mbzPath_Test );
    Test__Expect_EQ(KTgS_OK, tgUSZ_Copy( mbzPath_Test, KTgMAX_FILE_PATH, ROOT P01 PSEP P02 PSEP, KTgMAX_RSIZE ));
    Test__Expect_NE(KTgS_OK, tgCM_Path_Find_File_Name( &nbyOffset, mbzPath_Test, KTgMAX_FILE_PATH ));

    tgMM_Set_U08_0x00( mbzPath_Test, sizeof mbzPath_Test );
    Test__Expect_EQ(KTgS_OK, tgUSZ_Copy( mbzPath_Test, KTgMAX_FILE_PATH, ROOT P01 PSEP P02, KTgMAX_RSIZE ));
    Test__Expect_EQ(KTgS_OK, tgCM_Path_Find_File_Name( &nbyOffset, mbzPath_Test, KTgMAX_FILE_PATH ));
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, mbzPath_Test + nbyOffset, KTgMAX_RSIZE, 0, P02, KTgMAX_RSIZE, 0 )) && (0 == iRet));

    tgMM_Set_U08_0x00( mbzPath_Test, sizeof mbzPath_Test );
    Test__Expect_EQ(KTgS_OK, tgUSZ_Copy( mbzPath_Test, KTgMAX_FILE_PATH, ROOT P01 PSEP NAME FSEP EXT_01, KTgMAX_RSIZE ));
    Test__Expect_EQ(KTgS_OK, tgCM_Path_Find_File_Name( &nbyOffset, mbzPath_Test, KTgMAX_FILE_PATH ));
    Test__Expect_EQ(true, TgSUCCEEDED(tgUSZ_Compare( &iRet, mbzPath_Test + nbyOffset, KTgMAX_RSIZE, 0, NAME FSEP EXT_01, KTgMAX_RSIZE, 0 )) && (0 == iRet));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_Path_IsAbsolute -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_Path_IsAbsolute )
{
#if defined(TgCOMPILE_PLATFORM_WIN)
    Test__Expect_NE(false, tgCM_Path_IsAbsolute( ROOT P01 PSEP NAME FSEP EXT_01, KTgMAX_RSIZE ));
#endif
    Test__Expect_NE(false, tgCM_Path_IsAbsolute( PSEP P01 PSEP NAME FSEP EXT_01, KTgMAX_RSIZE ));
    Test__Expect_EQ(false, tgCM_Path_IsAbsolute( P01 PSEP NAME FSEP EXT_01, KTgMAX_RSIZE ));

    TEST_END_METHOD( KTgS_OK );
}



/* ---- tgUNIT_TEST_INTERNAL__File_Data_Setup ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_LOCAL TgUINT_E08_P tgUNIT_TEST_INTERNAL__File_Data_Setup( TgVOID )
{
    TgUINT_E08_P                        puiData;
    TgRSIZE                             nuiData;
    union
    {
        STg2_File_Block_P                   ps;
        TgUINT_E08_P                        pui;
    }                                   sFileBlock;
    union
    {
        STg2_File_Data_P                    ps;
        TgUINT_E08_P                        pui;
    }                                   sFileData;
    union
    {
        STg2_File_Data__TEST_P              ps;
        TgUINT_E08_P                        pui;
    }                                   sFileTest;

    nuiData  = sizeof( STg2_File_Block ) + 4 * sizeof( STg2_File_Section );
    nuiData += 4 * (sizeof( STg2_File_Data ) + sizeof( STg2_File_Data__TEST ) );
    puiData = (TgUINT_E08_P)malloc( nuiData );
    if (nullptr == puiData)
        return (nullptr);

    sFileBlock.pui = puiData;
    sFileBlock.ps->m_uiFourCC_Tool = TgMAKE_4CC( 'T', 'G', 'S', 'F' );
    sFileBlock.ps->m_uiFourCC_Data = TgMAKE_4CC( 'T', 'E', 'S', 'T' );
    sFileBlock.ps->m_uiSize = sizeof( STg2_File_Block );
    sFileBlock.ps->m_uiVersion = 1;
    sFileBlock.ps->m_uiMachine = ETgFILE_PLATFORM_W64;
    sFileBlock.ps->m_uiFlags = 0;
    sFileBlock.ps->m_uiTool_Version = 1;
    sFileBlock.ps->m_uiTool_ID = 1;
    sFileBlock.ps->m_uiSection_Version = 1;
    sFileBlock.ps->m_uiSection_Count = 4;
    sFileBlock.ps->m_uiSection_Size = sizeof( STg2_File_Section );
    sFileBlock.ps->m_asSection[0].m_uiFourCC_Tool = TgMAKE_4CC( 'T', 'G', 'S', 'F' );
    sFileBlock.ps->m_asSection[0].m_uiFourCC_Data = TgMAKE_4CC( 'T', 'E', 'S', 'T' );
    sFileBlock.ps->m_asSection[0].m_uiOffset = sizeof( STg2_File_Block ) + 4 * sizeof( STg2_File_Section );
    sFileBlock.ps->m_asSection[1].m_uiFourCC_Tool = TgMAKE_4CC( 'T', 'G', 'S', 'F' );
    sFileBlock.ps->m_asSection[1].m_uiFourCC_Data = TgMAKE_4CC( 'T', 'E', 'S', 'T' );
    sFileBlock.ps->m_asSection[1].m_uiOffset = sFileBlock.ps->m_asSection[0].m_uiOffset + sizeof( STg2_File_Data ) + sizeof( STg2_File_Data__TEST );
    sFileBlock.ps->m_asSection[2].m_uiFourCC_Tool = TgMAKE_4CC( 'T', 'G', 'S', 'F' );
    sFileBlock.ps->m_asSection[2].m_uiFourCC_Data = TgMAKE_4CC( 'T', 'E', 'S', 'T' );
    sFileBlock.ps->m_asSection[2].m_uiOffset = sFileBlock.ps->m_asSection[1].m_uiOffset + sizeof( STg2_File_Data ) + sizeof( STg2_File_Data__TEST );
    sFileBlock.ps->m_asSection[3].m_uiFourCC_Tool = TgMAKE_4CC( 'T', 'G', 'S', 'F' );
    sFileBlock.ps->m_asSection[3].m_uiFourCC_Data = TgMAKE_4CC( 'T', 'E', 'S', 'T' );
    sFileBlock.ps->m_asSection[3].m_uiOffset = sFileBlock.ps->m_asSection[2].m_uiOffset + sizeof( STg2_File_Data ) + sizeof( STg2_File_Data__TEST );

    sFileData.pui = puiData + sizeof( STg2_File_Block ) + 4 * sizeof( STg2_File_Section );
    sFileData.ps->m_uiFourCC_Data = TgMAKE_4CC( 'T', 'E', 'S', 'T' );
    sFileData.ps->m_iOffset = (TgSINT_E32 )sizeof( STg2_File_Data );
    sFileData.ps->m_uiSize = (TgUINT_E32)sizeof( STg2_File_Data__TEST );
    sFileData.ps->m_uiVersion = 1;
    sFileTest.pui = sFileData.pui + sFileData.ps->m_iOffset;
    sFileTest.ps->m_uiTest = 0;
    sFileTest.ps->m_nuiData = 0;

    sFileData.pui = sFileData.pui + sizeof( STg2_File_Data ) + sizeof( STg2_File_Data__TEST );
    sFileData.ps->m_uiFourCC_Data = TgMAKE_4CC( 'T', 'E', 'S', 'T' );
    sFileData.ps->m_iOffset = (TgSINT_E32 )sizeof( STg2_File_Data );
    sFileData.ps->m_uiSize = (TgUINT_E32)sizeof( STg2_File_Data__TEST );
    sFileData.ps->m_uiVersion = 1;
    sFileTest.pui = sFileData.pui + sFileData.ps->m_iOffset;
    sFileTest.ps->m_uiTest = 1;
    sFileTest.ps->m_nuiData = 0;

    sFileData.pui = sFileData.pui + sizeof( STg2_File_Data ) + sizeof( STg2_File_Data__TEST );
    sFileData.ps->m_uiFourCC_Data = TgMAKE_4CC( 'T', 'E', 'S', 'T' );
    sFileData.ps->m_iOffset = (TgSINT_E32 )sizeof( STg2_File_Data );
    sFileData.ps->m_uiSize = (TgUINT_E32)sizeof( STg2_File_Data__TEST );
    sFileData.ps->m_uiVersion = 1;
    sFileTest.pui = sFileData.pui + sFileData.ps->m_iOffset;
    sFileTest.ps->m_uiTest = 2;
    sFileTest.ps->m_nuiData = 0;

    sFileData.pui = sFileData.pui + sizeof( STg2_File_Data ) + sizeof( STg2_File_Data__TEST );
    sFileData.ps->m_uiFourCC_Data = TgMAKE_4CC( 'T', 'E', 'S', 'T' );
    sFileData.ps->m_iOffset = (TgSINT_E32 )sizeof( STg2_File_Data );
    sFileData.ps->m_uiSize = (TgUINT_E32)sizeof( STg2_File_Data__TEST );
    sFileData.ps->m_uiVersion = 1;
    sFileTest.pui = sFileData.pui + sFileData.ps->m_iOffset;
    sFileTest.ps->m_uiTest = 3;
    sFileTest.ps->m_nuiData = 0;

    TgCRITICAL( nuiData >= ((TgUINT_PTR)(sFileData.pui - puiData)) + sizeof( STg2_File_Data ) + sizeof( STg2_File_Data__TEST ) );
    return (puiData);
}


/* ---- UNIT_TEST__TEST__CM_File_Output_Header ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_File_Output_Header )
{
    TgUINT_E08_P                        puiData;
    TgCHAR_U8                           sOutput_Buffer[8192];
    STg2_Output_MEM                     sOutput;
    union
    {
        STg2_File_Block_P                   ps;
        TgUINT_E08_P                        pui;
    }                                   sFileBlock;
    TgCHAR_U8_C                         aResult[] = u8"File Header\n"
                                                    u8" - FourCC Tool: 1179862868\n"
                                                    u8" - FourCC Data: 1414743380\n"
                                                    u8" - Version: 1\n"
                                                    u8" - Machine: 2\n"
                                                    u8" - Flags: 0\n"
                                                    u8" - Tools Version: 1\n"
                                                    u8" - Tool Id: 1\n"
                                                    u8" - Section Version: 1\n"
                                                    u8" - Section Count: 4\n"
                                                    u8" - Section Size: 16\n"
                                                    u8" - Section (   0) FourCC Tool: 1179862868\n"
                                                    u8" - Section (   0) FourCC Data: 1414743380\n"
                                                    u8" - Section (   0) Offset: 96\n"
                                                    u8" - Section (   1) FourCC Tool: 1179862868\n"
                                                    u8" - Section (   1) FourCC Data: 1414743380\n"
                                                    u8" - Section (   1) Offset: 128\n"
                                                    u8" - Section (   2) FourCC Tool: 1179862868\n"
                                                    u8" - Section (   2) FourCC Data: 1414743380\n"
                                                    u8" - Section (   2) Offset: 160\n"
                                                    u8" - Section (   3) FourCC Tool: 1179862868\n"
                                                    u8" - Section (   3) FourCC Data: 1414743380\n"
                                                    u8" - Section (   3) Offset: 192\n";

    puiData = tgUNIT_TEST_INTERNAL__File_Data_Setup();
    if (nullptr == puiData)
    {
        TEST_END_METHOD( KTgE_FAIL );
    };
    sFileBlock.pui = puiData;

    /* Create a memory base output object to be used when testing the console output systems */
    tgIO_OM__Open( &sOutput, (TgUINT_E08_P)sOutput_Buffer, sizeof( sOutput_Buffer ), nullptr );
    tgMM_Set_U08_0x00( sOutput_Buffer, sizeof sOutput_Buffer );

    tgCM_File_Output_Header( &sOutput.m_sOutput, sFileBlock.ps );
    Test__Expect_EQ(0, memcmp( aResult, sOutput_Buffer, sizeof( aResult ) - 1 ));

    free( puiData );
    tgIO_OM__Close( &sOutput.m_sOutput );
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_File_Output_Data_Headers ----------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_File_Output_Data_Headers )
{
    TgUINT_E08_P                        puiData;
    TgCHAR_U8                           sOutput_Buffer[8192];
    STg2_Output_MEM                     sOutput;
    union
    {
        STg2_File_Block_P                   ps;
        TgUINT_E08_P                        pui;
    }                                   sFileBlock;
    TgCHAR_U8_C                         aResult[] = u8" - Section Data (   0) FourCC Data: 1414743380\n"
                                                    u8" - Section Data (   0) Offset: 16\n"
                                                    u8" - Section Data (   0) Size: 16\n"
                                                    u8" - Section Data (   0) Version: 1\n"
                                                    u8" - Section Data (   1) FourCC Data: 1414743380\n"
                                                    u8" - Section Data (   1) Offset: 16\n"
                                                    u8" - Section Data (   1) Size: 16\n"
                                                    u8" - Section Data (   1) Version: 1\n"
                                                    u8" - Section Data (   2) FourCC Data: 1414743380\n"
                                                    u8" - Section Data (   2) Offset: 16\n"
                                                    u8" - Section Data (   2) Size: 16\n"
                                                    u8" - Section Data (   2) Version: 1\n"
                                                    u8" - Section Data (   3) FourCC Data: 1414743380\n"
                                                    u8" - Section Data (   3) Offset: 16\n"
                                                    u8" - Section Data (   3) Size: 16\n"
                                                    u8" - Section Data (   3) Version: 1\n";

    puiData = tgUNIT_TEST_INTERNAL__File_Data_Setup();
    if (nullptr == puiData)
    {
        TEST_END_METHOD( KTgE_FAIL );
    };
    sFileBlock.pui = puiData;

    /* Create a memory base output object to be used when testing the console output systems */
    tgIO_OM__Open( &sOutput, (TgUINT_E08_P)sOutput_Buffer, sizeof( sOutput_Buffer ), nullptr );
    sOutput_Buffer[0] = 0;

    tgCM_File_Output_Data_Headers( &sOutput.m_sOutput, sFileBlock.ps );
    Test__Expect_EQ(0, memcmp( aResult, sOutput_Buffer, sizeof( aResult ) - 1 ));

    free( puiData );
    tgIO_OM__Close( &sOutput.m_sOutput );
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_File_Query_Data -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_File_Query_Data )
{
    TgUINT_E08_P                        puiData;
    union
    {
        STg2_File_Block_P                   ps;
        TgUINT_E08_P                        pui;
    }                                   sFileBlock;
    TgVOID_CP                           pTest;

    puiData = tgUNIT_TEST_INTERNAL__File_Data_Setup();
    if (nullptr == puiData)
    {
        TEST_END_METHOD( KTgE_FAIL );
    };
    sFileBlock.pui = puiData;

    Test__Expect_EQ(true, tgCM_File_Query_Data( &pTest, sFileBlock.ps, 0 ));
    Test__Expect_EQ((TgUINT_PTR)pTest, (TgUINT_PTR)sFileBlock.pui + sizeof( STg2_File_Block ) + 4 * sizeof( STg2_File_Section ) + sizeof( STg2_File_Data ) );
    Test__Expect_EQ(false, tgCM_File_Query_Data( &pTest, sFileBlock.ps, 5 ));

    free( puiData );
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_File_Query_Data_Size --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_File_Query_Data_Size )
{
    TgUINT_E08_P                        puiData;
    union
    {
        STg2_File_Block_P                   ps;
        TgUINT_E08_P                        pui;
    }                                   sFileBlock;
    TgRSIZE                             nbyData;

    puiData = tgUNIT_TEST_INTERNAL__File_Data_Setup();
    if (nullptr == puiData)
    {
        TEST_END_METHOD( KTgE_FAIL );
    };
    sFileBlock.pui = puiData;

    Test__Expect_EQ(true, tgCM_File_Query_Data_Size( &nbyData, sFileBlock.ps, 0 ));
    Test__Expect_EQ(nbyData, sizeof( STg2_File_Data__TEST ));
    Test__Expect_EQ(false, tgCM_File_Query_Data_Size( &nbyData, sFileBlock.ps, 5 ));

    free( puiData );
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_File_Query_Data_Count -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_File_Query_Data_Count )
{
    TgUINT_E08_P                        puiData;
    union
    {
        STg2_File_Block_P                   ps;
        TgUINT_E08_P                        pui;
    }                                   sFileBlock;

    puiData = tgUNIT_TEST_INTERNAL__File_Data_Setup();
    if (nullptr == puiData)
    {
        TEST_END_METHOD( KTgE_FAIL );
    };
    sFileBlock.pui = puiData;

    Test__Expect_EQ(4, tgCM_File_Query_Data_Count( sFileBlock.ps ));

    free( puiData );
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_File_Check_Block ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_File_Check_Block )
{
    TgUINT_E08_P                        puiData;
    union
    {
        STg2_File_Block_P                   ps;
        TgUINT_E08_P                        pui;
    }                                   sFileBlock;

    puiData = tgUNIT_TEST_INTERNAL__File_Data_Setup();
    if (nullptr == puiData)
    {
        TEST_END_METHOD( KTgE_FAIL );
    };
    sFileBlock.pui = puiData;

    Test__Expect_EQ(KTgS_OK, tgCM_File_Check_Block( sFileBlock.ps ));

    free( puiData );
    TEST_END_METHOD( KTgS_OK );
}

