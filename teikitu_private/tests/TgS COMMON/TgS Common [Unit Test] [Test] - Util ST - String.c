/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common [Unit Test] [Test] - Util ST - String.c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include <math.h>


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__Init );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__Free );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SZ_Init );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SN_Init );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__PT_Init );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__ST_Init );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SO_Init );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SF_Init );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SZ_Assign );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SN_Assign );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__PT_Assign );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__ST_Assign );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SO_Assign );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SF_Assign );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SZ_Append );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SN_Append );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__PT_Append );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__ST_Append );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SO_Append );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SF_Append );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SZ_Insert );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SN_Insert );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__PT_Insert );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__ST_Insert );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SO_Insert );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SF_Insert );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SZ_Replace );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SN_Replace );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__PT_Replace );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__ST_Replace );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SO_Replace );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SF_Replace );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__Erase );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__Clear );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__To_Upper );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__To_Lower );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__Format );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__Query_String );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__Is_Empty );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__Capacity );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__Max_Size );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__Length_U08 );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__Length_Count );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__Resize_NCS );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__Reserve );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__Swap );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__Is_Inside );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__ST_SZ_Compare );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__ST_SN_Compare );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__ST_ST_Compare );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__ST_SF_Compare );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SF_SZ_Compare );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SF_SN_Compare );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SF_ST_Compare );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SF_SF_Compare );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SO_SZ_Find_String );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SO_SN_Find_String );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SO_ST_Find_String );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SO_SF_Find_String );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SO_SZ_Find_Set );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SO_SN_Find_Set );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SO_ST_Find_Set );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SO_SZ_Find_Not_Set );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SO_SN_Find_Not_Set );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SO_ST_Find_Not_Set );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SO_SZ_RFind_String );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SO_SN_RFind_String );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SO_ST_RFind_String );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SO_SF_RFind_String );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SO_SZ_RFind_Set );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SO_SN_RFind_Set );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SO_ST_RFind_Set );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SO_SZ_RFind_Not_Set );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SO_SN_RFind_Not_Set );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SO_ST_RFind_Not_Set );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__Trim_Start_Set );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__Trim_End_Set );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

static TgCHAR_U8                            s_mbzTest_6[] = u8"0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
static TgCHAR_U8                            s_mbzTest_5[] = u8"AbCdEfGhIZZjKlMnOpQrStUvWxYzZZ";
static TgCHAR_U8                            s_mbzTest_4[] = KTgU8_LIT_TEST__RUSSIAN;
static TgCHAR_U8                            s_mbzTest_3[] = u8"AbCdEfGhIjKlMnOpQrStUvWxYz";
static TgCHAR_U8                            s_mbzTest_2[] = KTgU8_LIT_TEST__BURMESE;
static TgCHAR_U8                            s_mbzTest_1[] = u8"Za4";
static TgCHAR_U8                            s_mbzTest_0[] = u8"~";
static TgCHAR_U8_CP                         s_ambzTest[] = { s_mbzTest_0, s_mbzTest_1, s_mbzTest_2, s_mbzTest_3, s_mbzTest_4, s_mbzTest_5, s_mbzTest_6 };
static STg1_Text_Length                     s_asTest_Length[TgARRAY_COUNT(s_ambzTest)];

static TgCHAR_U8                            s_mbzCmp_Test_1[] = u8"AZAA";
static TgCHAR_U8                            s_mbzCmp_Test_2[] = u8"BYAA";
static TgCHAR_U8                            s_mbzCmp_Test_3[] = u8"CXAA";
static TgCHAR_U8                            s_mbzCmp_Test_4[] = u8"DWAA";
static TgCHAR_U8                            s_mbzCmp_Test_5[] = u8"azAa";
static TgCHAR_U8                            s_mbzCmp_Test_6[] = u8"byAa";
static TgCHAR_U8                            s_mbzCmp_Test_7[] = u8"cxAa";
static TgCHAR_U8                            s_mbzCmp_Test_8[] = u8"dwAa";

TgCOMPILER_ASSERT(sizeof(s_mbzCmp_Test_1) < KTgSTRING_STATIC_BUFFER_SIZE, );

static TgCHAR_U8_CP                         s_ambzCmp_Test[] = { s_mbzCmp_Test_1, s_mbzCmp_Test_2, s_mbzCmp_Test_3, s_mbzCmp_Test_4,
                                                                 s_mbzCmp_Test_5, s_mbzCmp_Test_6, s_mbzCmp_Test_7, s_mbzCmp_Test_8 };

#define TgMACRO_STEP_INDEX(A,B,C)           A = (TgRSIZE)llrintf(tgPM_CEIL_F32( (float)(B) * ( 1.0F / (1.0F + tgPM_EXP_F32( -((float)(A##_Step++) - 0.5F*((float)(C))) )) ) )); \
                                            A = tgCM_MIN_UMAX( B, A );


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- UNIT_TEST__TEST__UTIL_ST_String ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( UNIT_TEST__TEST__UTIL_ST_String )
{
    /* Initialize some of the static global variables with the required data */
    for (TgRSIZE uiIndex = 0; uiIndex < TgARRAY_COUNT(s_ambzTest); ++uiIndex)
    {
        tgUSZ_Length( s_asTest_Length + uiIndex, s_ambzTest[uiIndex], KTgMAX_RSIZE );
    };

    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__Init());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__Free());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__SZ_Init());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__SN_Init());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__PT_Init());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__ST_Init());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__SO_Init());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__SF_Init());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__SZ_Assign());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__SN_Assign());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__PT_Assign());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__ST_Assign());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__SO_Assign());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__SF_Assign());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__SZ_Append());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__SN_Append());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__PT_Append());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__ST_Append());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__SO_Append());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__SF_Append());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__SZ_Insert());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__SN_Insert());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__PT_Insert());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__ST_Insert());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__SO_Insert());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__SF_Insert());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__SZ_Replace());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__SN_Replace());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__PT_Replace());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__ST_Replace());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__SO_Replace());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__SF_Replace());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__Erase());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__Clear());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__To_Upper());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__To_Lower());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__Format());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__Query_String());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__Is_Empty());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__Capacity());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__Max_Size());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__Length_U08());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__Length_Count());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__Resize_NCS());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__Reserve());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__Swap());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__Is_Inside());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__ST_SZ_Compare());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__ST_SN_Compare());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__ST_ST_Compare());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__ST_SF_Compare());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__SF_SZ_Compare());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__SF_SN_Compare());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__SF_ST_Compare());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__SF_SF_Compare());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__SO_SZ_Find_String());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__SO_SN_Find_String());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__SO_ST_Find_String());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__SO_SF_Find_String());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__SO_SZ_Find_Set());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__SO_SN_Find_Set());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__SO_ST_Find_Set());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__SO_SZ_Find_Not_Set());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__SO_SN_Find_Not_Set());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__SO_ST_Find_Not_Set());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__SO_SZ_RFind_String());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__SO_SN_RFind_String());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__SO_ST_RFind_String());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__SO_SF_RFind_String());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__SO_SZ_RFind_Set());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__SO_SN_RFind_Set());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__SO_ST_RFind_Set());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__SO_SZ_RFind_Not_Set());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__SO_SN_RFind_Not_Set());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__SO_ST_RFind_Not_Set());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__Trim_Start_Set());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__ST__Trim_End_Set());

    TEST_END_METHOD( KTgS_OK );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/* File Local Functions                                                                                                                                                            */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__Init -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__Init )
{
    STg2_UT_ST__ST                      tgKB;

    tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[1] );
    tgCM_UT_ST__ST__Free( &tgKB );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__Free -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__Free )
{
    STg2_UT_ST__ST                      tgKB;

    tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[1] );
    tgCM_UT_ST__ST__Free( &tgKB );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__SZ_Init ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SZ_Init )
{
    for (TgRSIZE uiIndex = 0; uiIndex < TgARRAY_COUNT(s_ambzTest); ++uiIndex)
    {
        TgRSIZE_C                           nbyMaxTest = s_asTest_Length[uiIndex].m_nbyCharacters;

        STg2_UT_ST__ST                      tgKB;
        TgCHAR_U8_CP                        mbzKB;

        tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[uiIndex] );
        mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );

        Test__Expect_EQ(0, memcmp( mbzKB, s_ambzTest[uiIndex], nbyMaxTest ));
        Test__Expect_EQ(tgKB.m_nbyBuffer, nbyMaxTest);
        Test__Expect_EQ(tgKB.m_nbyBuffer, tgCM_UT_ST__ST__Length_U08( &tgKB ));
        Test__Expect_EQ(tgKB.m_nbyBuffer, tgUSZ_Length_U08( mbzKB, nbyMaxTest ));

        tgCM_UT_ST__ST__Free( &tgKB );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__SN_Init ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SN_Init )
{
    for (TgRSIZE uiIndex = 0; uiIndex < TgARRAY_COUNT(s_ambzTest); ++uiIndex)
    {
        TgRSIZE_C                           nbyMaxTest = s_asTest_Length[uiIndex].m_nbyCharacters;
        TgRSIZE_C       uiMaxStep_nbyTest = tgCM_MIN_UMAX( nbyMaxTest, 10 );

        for (TgRSIZE nbySize = 0, nbySize_Step = 0; nbySize_Step <= uiMaxStep_nbyTest; ++nbySize_Step)
        {
            STg2_UT_ST__ST                      tgKB;
            TgCHAR_U8_CP                        mbzKB;

            TgCHAR_U8_CPC   mbzTest_Size_End = tgUSZ_Query_End( s_ambzTest[uiIndex], nbySize, KTgMAX_RSIZE );
            TgRSIZE_C                           nbyTest = (TgRSIZE)(mbzTest_Size_End - s_ambzTest[uiIndex]);

            tgCM_UT_ST__ST__SN_Init( &tgKB, s_ambzTest[uiIndex], nbySize );
            mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );

            Test__Expect_EQ(0, memcmp( mbzKB, s_ambzTest[uiIndex], nbyTest));
            Test__Expect_EQ(tgKB.m_nbyBuffer, nbyTest);
            Test__Expect_EQ(tgKB.m_nbyBuffer, tgCM_UT_ST__ST__Length_U08( &tgKB ));
            Test__Expect_EQ(tgKB.m_nbyBuffer, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

            tgCM_UT_ST__ST__Free( &tgKB );

            TgMACRO_STEP_INDEX( nbySize, nbyMaxTest, uiMaxStep_nbyTest );
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__PT_Init ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__PT_Init )
{
    for (TgRSIZE uiIndex = 0; uiIndex < TgARRAY_COUNT(s_ambzTest); ++uiIndex)
    {
        TgRSIZE_C                           nbyMaxTest = s_asTest_Length[uiIndex].m_nbyCharacters;
        TgRSIZE_C                           nuiMaxTest = s_asTest_Length[uiIndex].m_nuiCharacters;
        TgRSIZE_C       uiMaxStep_nuiTest = tgCM_MIN_UMAX( nuiMaxTest, 10 );

        for (TgRSIZE uiTest_Start = 0, uiTest_Start_Step = 0; uiTest_Start_Step <= uiMaxStep_nuiTest; ++uiTest_Start_Step)
        {
            TgCHAR_U8_CPC   mbzTest_Start = tgUSZ_Query_At( s_ambzTest[uiIndex], nbyMaxTest + 1, uiTest_Start );

            for (TgRSIZE uiTest_End = uiTest_Start, uiTest_End_Step = uiTest_Start_Step; uiTest_End_Step <= uiMaxStep_nuiTest; ++uiTest_End_Step)
            {
                STg2_UT_ST__ST                      tgKB;
                TgCHAR_U8_CP                        mbzKB;

                TgCHAR_U8_CPC   mbzTest_End = tgUSZ_Query_At( s_ambzTest[uiIndex], nbyMaxTest + 1, uiTest_End );
                TgRSIZE_C                           nbyTest = mbzTest_End >= mbzTest_Start ? (TgRSIZE)(mbzTest_End - mbzTest_Start) : 0;

                tgCM_UT_ST__ST__PT_Init( &tgKB, mbzTest_Start, mbzTest_End );
                mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );

                Test__Expect_EQ(0, memcmp( mbzKB, mbzTest_Start, nbyTest ));
                Test__Expect_EQ(tgKB.m_nbyBuffer, nbyTest);
                Test__Expect_EQ(tgKB.m_nbyBuffer, tgCM_UT_ST__ST__Length_U08( &tgKB ));
                Test__Expect_EQ(tgKB.m_nbyBuffer, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

                tgCM_UT_ST__ST__Free( &tgKB );

                TgMACRO_STEP_INDEX( uiTest_End, nuiMaxTest, uiMaxStep_nuiTest );
            };

            TgMACRO_STEP_INDEX( uiTest_Start, nuiMaxTest, uiMaxStep_nuiTest );
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__ST_Init ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__ST_Init )
{
    for (TgRSIZE uiIndex = 0; uiIndex < TgARRAY_COUNT(s_ambzTest); ++uiIndex)
    {
        STg2_UT_ST__ST                      tgKB, tgKC;
        TgCHAR_U8_CP                        mbzKB;

        TgRSIZE_C                           nbyMaxTest = s_asTest_Length[uiIndex].m_nbyCharacters;

        /* Assign with pointer to non-self, with empty string */
        tgCM_UT_ST__ST__SZ_Init( &tgKC, s_ambzTest[uiIndex] );
        tgCM_UT_ST__ST__ST_Init( &tgKB, &tgKC );
        mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );

        Test__Expect_EQ(0, memcmp( mbzKB, s_ambzTest[uiIndex], nbyMaxTest ));
        Test__Expect_EQ(tgKB.m_nbyBuffer, nbyMaxTest);
        Test__Expect_EQ(tgKB.m_nbyBuffer, tgCM_UT_ST__ST__Length_U08( &tgKB ));
        Test__Expect_EQ(tgKB.m_nbyBuffer, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

        tgCM_UT_ST__ST__Free( &tgKC );
        tgCM_UT_ST__ST__Free( &tgKB );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__SO_Init ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SO_Init )
{
    for (TgRSIZE uiIndex = 0; uiIndex < TgARRAY_COUNT(s_ambzTest); ++uiIndex)
    {
        TgRSIZE_C                           nbyMaxTest = s_asTest_Length[uiIndex].m_nbyCharacters;
        TgRSIZE_C                           nuiMaxTest = s_asTest_Length[uiIndex].m_nuiCharacters;
        TgRSIZE_C       uiMaxStep_nuiTest = tgCM_MIN_UMAX( nuiMaxTest, 10 );

        for (TgRSIZE uiTest_Start = 0, uiTest_Start_Step = 0; uiTest_Start_Step <= uiMaxStep_nuiTest; ++uiTest_Start_Step)
        {
            STg2_UT_ST__ST                      tgKB, tgKC;
            TgCHAR_U8_CP                        mbzKB;

            TgCHAR_U8_CPC   mbzTest_Start = tgUSZ_Query_At( s_ambzTest[uiIndex], nbyMaxTest + 1, uiTest_Start );
            TgRSIZE_C                           nbyTest = nbyMaxTest - (TgRSIZE)(mbzTest_Start - s_ambzTest[uiIndex]);

            /* Assign with pointer to non-self, with empty string */
            tgCM_UT_ST__ST__SZ_Init( &tgKC, s_ambzTest[uiIndex] );
            tgCM_UT_ST__ST__SO_Init( &tgKB, &tgKC, uiTest_Start );
            mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );

            Test__Expect_EQ(0, memcmp( mbzKB, mbzTest_Start, nbyTest ));
            Test__Expect_EQ(tgKB.m_nbyBuffer, nbyTest);
            Test__Expect_EQ(tgKB.m_nbyBuffer, tgCM_UT_ST__ST__Length_U08( &tgKB ));
            Test__Expect_EQ(tgKB.m_nbyBuffer, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

            tgCM_UT_ST__ST__Free( &tgKC );
            tgCM_UT_ST__ST__Free( &tgKB );

            TgMACRO_STEP_INDEX( uiTest_Start, nuiMaxTest, uiMaxStep_nuiTest );
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__SF_Init ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SF_Init )
{
    for (TgRSIZE uiIndex = 0; uiIndex < TgARRAY_COUNT(s_ambzTest); ++uiIndex)
    {
        TgRSIZE_C                           nbyMaxTest = s_asTest_Length[uiIndex].m_nbyCharacters;
        TgRSIZE_C                           nuiMaxTest = s_asTest_Length[uiIndex].m_nuiCharacters;
        TgRSIZE_C       uiMaxStep_nuiTest = tgCM_MIN_UMAX( nuiMaxTest, 10 );

        for (TgRSIZE uiTest_Start = 0, uiTest_Start_Step = 0; uiTest_Start_Step <= uiMaxStep_nuiTest; ++uiTest_Start_Step)
        {
            TgCHAR_U8_CPC   mbzTest_Start = tgUSZ_Query_At( s_ambzTest[uiIndex], nbyMaxTest + 1, uiTest_Start );

            for (TgRSIZE uiTest_End = uiTest_Start, uiTest_End_Step = uiTest_Start_Step; uiTest_End_Step <= uiMaxStep_nuiTest; ++uiTest_End_Step)
            {
                STg2_UT_ST__ST                      tgKB, tgKC;
                TgCHAR_U8_CP                        mbzKB;

                TgCHAR_U8_CPC   mbzTest_End = tgUSZ_Query_At( s_ambzTest[uiIndex], nbyMaxTest + 1, uiTest_End );
                TgRSIZE_C                           nbyTest = mbzTest_End >= mbzTest_Start ? (TgRSIZE)(mbzTest_End - mbzTest_Start) : 0;

                /* Assign with pointer to non-self, with empty string */
                tgCM_UT_ST__ST__SZ_Init( &tgKC, s_ambzTest[uiIndex] );
                tgCM_UT_ST__ST__SF_Init( &tgKB, &tgKC, uiTest_Start, uiTest_End - uiTest_Start );
                mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );

                Test__Expect_EQ(0, memcmp( mbzKB, mbzTest_Start, nbyTest ));
                Test__Expect_EQ(tgKB.m_nbyBuffer, nbyTest);
                Test__Expect_EQ(tgKB.m_nbyBuffer, tgCM_UT_ST__ST__Length_U08( &tgKB ));
                Test__Expect_EQ(tgKB.m_nbyBuffer, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

                tgCM_UT_ST__ST__Free( &tgKC );
                tgCM_UT_ST__ST__Free( &tgKB );

                TgMACRO_STEP_INDEX( uiTest_End, nuiMaxTest, uiMaxStep_nuiTest );
            };

            TgMACRO_STEP_INDEX( uiTest_Start, nuiMaxTest, uiMaxStep_nuiTest );
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__SZ_Assign --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SZ_Assign )
{
    for (TgRSIZE uiIndex = 0; uiIndex < TgARRAY_COUNT(s_ambzTest); ++uiIndex)
    {
        TgCHAR_U8_CP                        mbzKB;
        STg2_UT_ST__ST                      tgKB;

        TgRSIZE_C                           nbyMaxTest = s_asTest_Length[uiIndex].m_nbyCharacters;

        /* Assign with pointer to self */
        tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[uiIndex] );
        mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );

        tgCM_UT_ST__ST__SZ_Assign( &tgKB, mbzKB );
        mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );

        Test__Expect_EQ(0, memcmp( mbzKB, s_ambzTest[uiIndex], nbyMaxTest ));
        Test__Expect_EQ(tgKB.m_nbyBuffer, nbyMaxTest);
        Test__Expect_EQ(tgKB.m_nbyBuffer, tgCM_UT_ST__ST__Length_U08( &tgKB ));
        Test__Expect_EQ(tgKB.m_nbyBuffer, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

        tgCM_UT_ST__ST__Free( &tgKB );


        /* Assign with pointer to non-self */
        for (TgRSIZE uiIndex2 = 0; uiIndex2 < TgARRAY_COUNT(s_ambzTest); ++uiIndex2)
        {
            tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[uiIndex2] );
            tgCM_UT_ST__ST__SZ_Assign( &tgKB, s_ambzTest[uiIndex] );
            mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );

            Test__Expect_EQ(0, memcmp( mbzKB, s_ambzTest[uiIndex], nbyMaxTest ));
            Test__Expect_EQ(tgKB.m_nbyBuffer, nbyMaxTest );
            Test__Expect_EQ(tgKB.m_nbyBuffer, tgCM_UT_ST__ST__Length_U08( &tgKB ));
            Test__Expect_EQ(tgKB.m_nbyBuffer, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

            tgCM_UT_ST__ST__Free( &tgKB );
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__SN_Assign --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SN_Assign )
{
    for (TgRSIZE uiIndex = 0; uiIndex < TgARRAY_COUNT(s_ambzTest); ++uiIndex)
    {
        TgRSIZE_C                           nbyMaxTest = s_asTest_Length[uiIndex].m_nbyCharacters;
        TgRSIZE_C       uiMaxStep_nbyTest = tgCM_MIN_UMAX( nbyMaxTest, 10 );

        for (TgRSIZE nbySize = 0, nbySize_Step = 0; nbySize_Step <= uiMaxStep_nbyTest; ++nbySize_Step)
        {
            STg2_UT_ST__ST                      tgKB;
            TgCHAR_U8_CP                        mbzKB;

            TgCHAR_U8_CPC   mbzTest_End = tgUSZ_Query_End( s_ambzTest[uiIndex], nbySize, KTgMAX_RSIZE );
            TgRSIZE_C                           nbyTest = (TgRSIZE)(mbzTest_End - s_ambzTest[uiIndex]);

            /* Assign with pointer to self */
            tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[uiIndex] );
            mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );

            tgCM_UT_ST__ST__SN_Assign( &tgKB, mbzKB, nbySize );
            mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );

            Test__Expect_EQ(0, memcmp( mbzKB, s_ambzTest[uiIndex], nbyTest ));
            Test__Expect_EQ(tgKB.m_nbyBuffer, nbyTest);
            Test__Expect_EQ(tgKB.m_nbyBuffer, tgCM_UT_ST__ST__Length_U08( &tgKB ));
            Test__Expect_EQ(tgKB.m_nbyBuffer, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

            tgCM_UT_ST__ST__Free( &tgKB );


            /* Assign with pointer to non-self, with initialized string */
            for (TgRSIZE uiIndex2 = 0; uiIndex2 < TgARRAY_COUNT(s_ambzTest); ++uiIndex2)
            {
                tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[uiIndex2] );

                tgCM_UT_ST__ST__SN_Assign( &tgKB, s_ambzTest[uiIndex], nbySize );
                mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );

                Test__Expect_EQ(0, memcmp( mbzKB, s_ambzTest[uiIndex], nbyTest ));
                Test__Expect_EQ(tgKB.m_nbyBuffer, nbyTest);
                Test__Expect_EQ(tgKB.m_nbyBuffer, tgCM_UT_ST__ST__Length_U08( &tgKB ));
                Test__Expect_EQ(tgKB.m_nbyBuffer, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

                tgCM_UT_ST__ST__Free( &tgKB );
            };

            TgMACRO_STEP_INDEX( nbySize, nbyMaxTest, uiMaxStep_nbyTest );
        };
    };


    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__PT_Assign --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__PT_Assign )
{
    for (TgRSIZE uiIndex = 0; uiIndex < TgARRAY_COUNT(s_ambzTest); ++uiIndex)
    {
        TgRSIZE_C                           nbyMaxTest = s_asTest_Length[uiIndex].m_nbyCharacters;
        TgRSIZE_C                           nuiMaxTest = s_asTest_Length[uiIndex].m_nuiCharacters;
        TgRSIZE_C       uiMaxStep_nuiTest = tgCM_MIN_UMAX( nuiMaxTest, 10 );

        for (TgRSIZE uiTest_Start = 0, uiTest_Start_Step = 0; uiTest_Start_Step <= uiMaxStep_nuiTest; ++uiTest_Start_Step)
        {
            TgCHAR_U8_CPC   mbzTest_Start = tgUSZ_Query_At( s_ambzTest[uiIndex], nbyMaxTest + 1, uiTest_Start );

            for (TgRSIZE uiTest_End = uiTest_Start, uiTest_End_Step = uiTest_Start_Step; uiTest_End_Step <= uiMaxStep_nuiTest; ++uiTest_End_Step)
            {
                STg2_UT_ST__ST                      tgKB;
                TgCHAR_U8_CP                        mbzKB, mbzKB_Start, mbzKB_End;

                TgCHAR_U8_CPC   mbzTest_End = tgUSZ_Query_At( s_ambzTest[uiIndex], nbyMaxTest + 1, uiTest_End );
                TgRSIZE_C                           nbyTest = mbzTest_End >= mbzTest_Start ? (TgRSIZE)(mbzTest_End - mbzTest_Start) : 0;

                /* Assign with pointer to self (start) */
                tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[uiIndex] );
                mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );
                mbzKB_Start = tgUSZ_Query_At( mbzKB, tgKB.m_nbyBuffer + 1, uiTest_Start );
                mbzKB_End = tgUSZ_Query_At( mbzKB, tgKB.m_nbyBuffer + 1, uiTest_End );

                tgCM_UT_ST__ST__PT_Assign( &tgKB, mbzKB_Start, mbzKB_End );
                mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );

                Test__Expect_EQ(0, memcmp( mbzKB, mbzTest_Start, nbyTest ));
                Test__Expect_EQ(tgKB.m_nbyBuffer, nbyTest);
                Test__Expect_EQ(tgKB.m_nbyBuffer, tgCM_UT_ST__ST__Length_U08( &tgKB ));
                Test__Expect_EQ(tgKB.m_nbyBuffer, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

                tgCM_UT_ST__ST__Free( &tgKB );


                /* Assign with pointer to non-self, with initialized string */
                for (TgRSIZE uiIndex2 = 0; uiIndex2 < TgARRAY_COUNT(s_ambzTest); ++uiIndex2)
                {
                    tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[uiIndex2] );
                    tgCM_UT_ST__ST__PT_Assign( &tgKB, mbzTest_Start, mbzTest_End );
                    mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );

                    Test__Expect_EQ(0, memcmp( mbzKB, mbzTest_Start, nbyTest ));
                    Test__Expect_EQ(tgKB.m_nbyBuffer, nbyTest);
                    Test__Expect_EQ(tgKB.m_nbyBuffer, tgCM_UT_ST__ST__Length_U08( &tgKB ));
                    Test__Expect_EQ(tgKB.m_nbyBuffer, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

                    tgCM_UT_ST__ST__Free( &tgKB );
                };

                TgMACRO_STEP_INDEX( uiTest_End, nuiMaxTest, uiMaxStep_nuiTest );
            };

            TgMACRO_STEP_INDEX( uiTest_Start, nuiMaxTest, uiMaxStep_nuiTest );
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__ST_Assign --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__ST_Assign )
{
    for (TgRSIZE uiIndex = 0; uiIndex < TgARRAY_COUNT(s_ambzTest); ++uiIndex)
    {
        STg2_UT_ST__ST                      tgKB;
        TgCHAR_U8_CP                        mbzKB;

        TgRSIZE_C                           nbyMaxTest = s_asTest_Length[uiIndex].m_nbyCharacters;

        /* Assign with pointer to self */
        tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[uiIndex] );
        tgCM_UT_ST__ST__ST_Assign( &tgKB, &tgKB );
        mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );

        Test__Expect_EQ(0, memcmp( mbzKB, s_ambzTest[uiIndex], nbyMaxTest ));
        Test__Expect_EQ(tgKB.m_nbyBuffer, nbyMaxTest);
        Test__Expect_EQ(tgKB.m_nbyBuffer, tgCM_UT_ST__ST__Length_U08( &tgKB ));
        Test__Expect_EQ(tgKB.m_nbyBuffer, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

        tgCM_UT_ST__ST__Free( &tgKB );


        /* Assign with pointer to non-self, with empty string */
        for (TgRSIZE uiIndex2 = 0; uiIndex2 < TgARRAY_COUNT(s_ambzTest); ++uiIndex2)
        {
            STg2_UT_ST__ST                      tgKC;

            tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[uiIndex2] );
            tgCM_UT_ST__ST__SZ_Init( &tgKC, s_ambzTest[uiIndex] );
            tgCM_UT_ST__ST__ST_Assign( &tgKB, &tgKC );
            mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );

            Test__Expect_EQ(0, memcmp( mbzKB, s_ambzTest[uiIndex], nbyMaxTest ));
            Test__Expect_EQ(tgKB.m_nbyBuffer, nbyMaxTest);
            Test__Expect_EQ(tgKB.m_nbyBuffer, tgCM_UT_ST__ST__Length_U08( &tgKB ));
            Test__Expect_EQ(tgKB.m_nbyBuffer, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

            tgCM_UT_ST__ST__Free( &tgKC );
            tgCM_UT_ST__ST__Free( &tgKB );
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__SO_Assign --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SO_Assign )
{
    for (TgRSIZE uiIndex = 0; uiIndex < TgARRAY_COUNT(s_ambzTest); ++uiIndex)
    {
        TgRSIZE_C                           nbyMaxTest = s_asTest_Length[uiIndex].m_nbyCharacters;
        TgRSIZE_C                           nuiMaxTest = s_asTest_Length[uiIndex].m_nuiCharacters;
        TgRSIZE_C       uiMaxStep_nuiTest = tgCM_MIN_UMAX( nuiMaxTest, 10 );

        for (TgRSIZE uiTest_Start = 0, uiTest_Start_Step = 0; uiTest_Start_Step <= uiMaxStep_nuiTest; ++uiTest_Start_Step)
        {
            STg2_UT_ST__ST                      tgKB;
            TgCHAR_U8_CP                        mbzKB;

            TgCHAR_U8_CPC   mbzTest_Start = tgUSZ_Query_At( s_ambzTest[uiIndex], nbyMaxTest + 1, uiTest_Start );
            TgRSIZE_C                           nbyTest = nbyMaxTest - (TgRSIZE)(mbzTest_Start - s_ambzTest[uiIndex]);

            /* Assign with pointer to self */
            tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[uiIndex] );
            tgCM_UT_ST__ST__SO_Assign( &tgKB, &tgKB, uiTest_Start );
            mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );

            Test__Expect_EQ(0, memcmp( mbzKB, mbzTest_Start, nbyTest ));
            Test__Expect_EQ(tgKB.m_nbyBuffer, nbyTest);
            Test__Expect_EQ(tgKB.m_nbyBuffer, tgCM_UT_ST__ST__Length_U08( &tgKB ));
            Test__Expect_EQ(tgKB.m_nbyBuffer, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

            tgCM_UT_ST__ST__Free( &tgKB );


            /* Assign with pointer to non-self, with empty string */
            for (TgRSIZE uiIndex2 = 0; uiIndex2 < TgARRAY_COUNT(s_ambzTest); ++uiIndex2)
            {
                STg2_UT_ST__ST                      tgKC;

                tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[uiIndex2] );
                tgCM_UT_ST__ST__SZ_Init( &tgKC, s_ambzTest[uiIndex] );
                tgCM_UT_ST__ST__SO_Assign( &tgKB, &tgKC, uiTest_Start );
                mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );

                Test__Expect_EQ(0, memcmp( mbzKB, mbzTest_Start, nbyTest ));
                Test__Expect_EQ(tgKB.m_nbyBuffer, nbyTest);
                Test__Expect_EQ(tgKB.m_nbyBuffer, tgCM_UT_ST__ST__Length_U08( &tgKB ));
                Test__Expect_EQ(tgKB.m_nbyBuffer, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

                tgCM_UT_ST__ST__Free( &tgKC );
                tgCM_UT_ST__ST__Free( &tgKB );
            };

            TgMACRO_STEP_INDEX( uiTest_Start, nuiMaxTest, uiMaxStep_nuiTest );
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__SF_Assign --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SF_Assign )
{
    for (TgRSIZE uiIndex = 0; uiIndex < TgARRAY_COUNT(s_ambzTest); ++uiIndex)
    {
        TgRSIZE_C                           nbyMaxTest = s_asTest_Length[uiIndex].m_nbyCharacters;
        TgRSIZE_C                           nuiMaxTest = s_asTest_Length[uiIndex].m_nuiCharacters;
        TgRSIZE_C       uiMaxStep_nuiTest = tgCM_MIN_UMAX( nuiMaxTest, 10 );

        for (TgRSIZE uiTest_Start = 0, uiTest_Start_Step = 0; uiTest_Start_Step <= uiMaxStep_nuiTest; ++uiTest_Start_Step)
        {
            TgCHAR_U8_CPC   mbzTest_Start = tgUSZ_Query_At( s_ambzTest[uiIndex], nbyMaxTest + 1, uiTest_Start );

            for (TgRSIZE uiTest_End = uiTest_Start, uiTest_End_Step = uiTest_Start_Step; uiTest_End_Step <= uiMaxStep_nuiTest; ++uiTest_End_Step)
            {
                STg2_UT_ST__ST                      tgKB;
                TgCHAR_U8_CP                        mbzKB;

                TgCHAR_U8_CPC   mbzTest_End = tgUSZ_Query_At( s_ambzTest[uiIndex], nbyMaxTest + 1, uiTest_End );
                TgRSIZE_C                           nbyTest = mbzTest_End >= mbzTest_Start ? (TgRSIZE)(mbzTest_End - mbzTest_Start) : 0;

                /* Assign with pointer to self */
                tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[uiIndex] );
                tgCM_UT_ST__ST__SF_Assign( &tgKB, &tgKB, uiTest_Start, uiTest_End - uiTest_Start );
                mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );

                Test__Expect_EQ(0, memcmp( mbzKB, mbzTest_Start, nbyTest ));
                Test__Expect_EQ(tgKB.m_nbyBuffer, nbyTest);
                Test__Expect_EQ(tgKB.m_nbyBuffer, tgCM_UT_ST__ST__Length_U08( &tgKB ));
                Test__Expect_EQ(tgKB.m_nbyBuffer, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

                tgCM_UT_ST__ST__Free( &tgKB );


                /* Assign with pointer to non-self, with empty string */
                for (TgRSIZE uiIndex2 = 0; uiIndex2 < TgARRAY_COUNT(s_ambzTest); ++uiIndex2)
                {
                    STg2_UT_ST__ST                      tgKC;

                    tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[uiIndex2] );
                    tgCM_UT_ST__ST__SZ_Init( &tgKC, s_ambzTest[uiIndex] );
                    tgCM_UT_ST__ST__SF_Assign( &tgKB, &tgKC, uiTest_Start, uiTest_End - uiTest_Start );
                    mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );

                    Test__Expect_EQ(0, memcmp( mbzKB, mbzTest_Start, nbyTest ));
                    Test__Expect_EQ(tgKB.m_nbyBuffer, nbyTest);
                    Test__Expect_EQ(tgKB.m_nbyBuffer, tgCM_UT_ST__ST__Length_U08( &tgKB ));
                    Test__Expect_EQ(tgKB.m_nbyBuffer, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

                    tgCM_UT_ST__ST__Free( &tgKC );
                    tgCM_UT_ST__ST__Free( &tgKB );
                };

                TgMACRO_STEP_INDEX( uiTest_End, nuiMaxTest, uiMaxStep_nuiTest );
            };

            TgMACRO_STEP_INDEX( uiTest_Start, nuiMaxTest, uiMaxStep_nuiTest );
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__SZ_Append --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SZ_Append )
{
    for (TgRSIZE uiIndex = 0; uiIndex < TgARRAY_COUNT(s_ambzTest); ++uiIndex)
    {
        TgRSIZE_C                           nbyMaxTest = s_asTest_Length[uiIndex].m_nbyCharacters;
        TgRSIZE_C                           nuiMaxTest = s_asTest_Length[uiIndex].m_nuiCharacters;
        TgRSIZE_C       uiMaxStep_nuiTest = tgCM_MIN_UMAX( nuiMaxTest, 10 );

        /* Assign with pointer to self */
        for (TgRSIZE uiTest_Start = 0, uiTest_Start_Step = 0; uiTest_Start_Step <= uiMaxStep_nuiTest; ++uiTest_Start_Step)
        {
            STg2_UT_ST__ST                      tgKB;
            TgCHAR_U8_CP                        mbzKB, mbzKB_Start;

            TgCHAR_U8_CPC   mbzTest_Start = tgUSZ_Query_At( s_ambzTest[uiIndex], nbyMaxTest + 1, uiTest_Start );
            TgRSIZE_C                           nbyTest = nbyMaxTest - (TgRSIZE)(mbzTest_Start - s_ambzTest[uiIndex]);

            tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[uiIndex] );
            mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );
            mbzKB_Start = tgUSZ_Query_At( mbzKB, tgKB.m_nbyBuffer + 1, uiTest_Start );
            tgCM_UT_ST__ST__SZ_Append( &tgKB, mbzKB_Start );
            mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );

            Test__Expect_EQ(0, memcmp( mbzKB, s_ambzTest[uiIndex], nbyMaxTest ));
            Test__Expect_EQ(0, memcmp( mbzKB + nbyMaxTest, mbzTest_Start, nbyTest ));
            Test__Expect_EQ(tgKB.m_nbyBuffer, nbyMaxTest + nbyTest);
            Test__Expect_EQ(tgKB.m_nbyBuffer, tgCM_UT_ST__ST__Length_U08( &tgKB ));
            Test__Expect_EQ(tgKB.m_nbyBuffer, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

            tgCM_UT_ST__ST__Free( &tgKB );


            /* Append with pointer to non-self */
            for (TgRSIZE uiIndex2 = 0; uiIndex2 < TgARRAY_COUNT(s_ambzTest); ++uiIndex2)
            {
                TgRSIZE_C                           nbyMaxTest2 = s_asTest_Length[uiIndex2].m_nbyCharacters;

                tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[uiIndex2] );
                tgCM_UT_ST__ST__SZ_Append( &tgKB, mbzTest_Start );
                mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );

                Test__Expect_EQ(0, memcmp( mbzKB, s_ambzTest[uiIndex2], nbyMaxTest2 ));
                Test__Expect_EQ(0, memcmp( mbzKB + nbyMaxTest2, mbzTest_Start, nbyTest ));
                Test__Expect_EQ(tgKB.m_nbyBuffer, nbyMaxTest2 + nbyTest);
                Test__Expect_EQ(tgKB.m_nbyBuffer, tgCM_UT_ST__ST__Length_U08( &tgKB ));
                Test__Expect_EQ(tgKB.m_nbyBuffer, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

                tgCM_UT_ST__ST__Free( &tgKB );
            };

            TgMACRO_STEP_INDEX( uiTest_Start, nuiMaxTest, uiMaxStep_nuiTest );
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__SN_Append --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SN_Append )
{
    for (TgRSIZE uiIndex = 0; uiIndex < TgARRAY_COUNT(s_ambzTest); ++uiIndex)
    {
        TgRSIZE_C                           nbyMaxTest = s_asTest_Length[uiIndex].m_nbyCharacters;
        TgRSIZE_C       uiMaxStep_nbyTest = tgCM_MIN_UMAX( nbyMaxTest, 10 );
        TgRSIZE_C                           nuiMaxTest = s_asTest_Length[uiIndex].m_nuiCharacters;
        TgRSIZE_C       uiMaxStep_nuiTest = tgCM_MIN_UMAX( nuiMaxTest, 10 );

        for (TgRSIZE nbySize = 0, nbySize_Step = 0; nbySize_Step <= uiMaxStep_nbyTest; ++nbySize_Step)
        {
            /* Append with pointer to self */
            for (TgRSIZE uiTest_Start = 0, uiTest_Start_Step = 0; uiTest_Start_Step <= uiMaxStep_nuiTest; ++uiTest_Start_Step)
            {
                TgCHAR_U8_CPC   mbzTest_Start = tgUSZ_Query_At( s_ambzTest[uiIndex], nbyMaxTest + 1, uiTest_Start );
                TgCHAR_U8_CPC   mbzTest_End = tgUSZ_Query_End( mbzTest_Start, nbySize, KTgMAX_RSIZE );
                TgRSIZE_C                           nbyTest = mbzTest_End >= mbzTest_Start ? (TgRSIZE)(mbzTest_End - mbzTest_Start) : 0;

                STg2_UT_ST__ST                      tgKB;
                TgCHAR_U8_CP                        mbzKB, mbzKB_Start;

                tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[uiIndex] );
                mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );
                mbzKB_Start = tgUSZ_Query_At( mbzKB, tgKB.m_nbyBuffer + 1, uiTest_Start );
                tgCM_UT_ST__ST__SN_Append( &tgKB, mbzKB_Start, nbySize );
                mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );

                Test__Expect_EQ(0, memcmp( mbzKB, s_ambzTest[uiIndex], nbyMaxTest ));
                Test__Expect_EQ(0, memcmp( mbzKB + nbyMaxTest, mbzTest_Start, nbyTest ));
                Test__Expect_EQ(tgKB.m_nbyBuffer, nbyMaxTest + nbyTest);
                Test__Expect_EQ(tgKB.m_nbyBuffer, tgCM_UT_ST__ST__Length_U08( &tgKB ));
                Test__Expect_EQ(tgKB.m_nbyBuffer, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

                tgCM_UT_ST__ST__Free( &tgKB );


                /* Append with pointer to non-self, with initialized string */
                for (TgRSIZE uiIndex2 = 0; uiIndex2 < TgARRAY_COUNT(s_ambzTest); ++uiIndex2)
                {
                    TgRSIZE_C                           nbyMaxTest2 = s_asTest_Length[uiIndex2].m_nbyCharacters;

                    tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[uiIndex2] );
                    tgCM_UT_ST__ST__SN_Append( &tgKB, mbzTest_Start, nbySize );
                    mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );

                    Test__Expect_EQ(0, memcmp( mbzKB, s_ambzTest[uiIndex2], nbyMaxTest2 ));
                    Test__Expect_EQ(0, memcmp( mbzKB + nbyMaxTest2, mbzTest_Start, nbyTest ));
                    Test__Expect_EQ(tgKB.m_nbyBuffer, nbyMaxTest2 + nbyTest);
                    Test__Expect_EQ(tgKB.m_nbyBuffer, tgCM_UT_ST__ST__Length_U08( &tgKB ));
                    Test__Expect_EQ(tgKB.m_nbyBuffer, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

                    tgCM_UT_ST__ST__Free( &tgKB );
                };

                TgMACRO_STEP_INDEX( uiTest_Start, nuiMaxTest, uiMaxStep_nuiTest );
            };

            TgMACRO_STEP_INDEX( nbySize, nbyMaxTest, uiMaxStep_nbyTest );
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__PT_Append --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__PT_Append )
{
    for (TgRSIZE uiIndex = 0; uiIndex < TgARRAY_COUNT(s_ambzTest); ++uiIndex)
    {
        TgRSIZE_C                           nbyMaxTest = s_asTest_Length[uiIndex].m_nbyCharacters;
        TgRSIZE_C                           nuiMaxTest = s_asTest_Length[uiIndex].m_nuiCharacters;
        TgRSIZE_C       uiMaxStep_nuiTest = tgCM_MIN_UMAX( nuiMaxTest, 10 );

        /* Assign with pointer to self */

        for (TgRSIZE uiTest_Start = 0, uiTest_Start_Step = 0; uiTest_Start_Step <= uiMaxStep_nuiTest; ++uiTest_Start_Step)
        {
            TgCHAR_U8_CPC   mbzTest_Start = tgUSZ_Query_At( s_ambzTest[uiIndex], nbyMaxTest + 1, uiTest_Start );

            for (TgRSIZE uiTest_End = uiTest_Start, uiTest_End_Step = uiTest_Start_Step; uiTest_End_Step <= uiMaxStep_nuiTest; ++uiTest_End_Step)
            {
                TgCHAR_U8_CPC   mbzTest_End = tgUSZ_Query_At( s_ambzTest[uiIndex], nbyMaxTest + 1, uiTest_End );
                TgRSIZE_C                           nbyTest = mbzTest_End >= mbzTest_Start ? (TgRSIZE)(mbzTest_End - mbzTest_Start) : 0;

                STg2_UT_ST__ST                      tgKB;
                TgCHAR_U8_CP                        mbzKB, mbzKB_Start, mbzKB_End;

                /* Append with pointer to self (start) */

                tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[uiIndex] );
                mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );
                mbzKB_Start = tgUSZ_Query_At( mbzKB, tgKB.m_nbyBuffer + 1, uiTest_Start );
                mbzKB_End = tgUSZ_Query_At( mbzKB, tgKB.m_nbyBuffer + 1, uiTest_End );
                tgCM_UT_ST__ST__PT_Append( &tgKB, mbzKB_Start, mbzKB_End );
                mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );

                Test__Expect_EQ(0, memcmp( mbzKB, s_ambzTest[uiIndex], nbyMaxTest ));
                Test__Expect_EQ( 0, memcmp( mbzKB + nbyMaxTest, mbzTest_Start, nbyTest ) );
                Test__Expect_EQ(tgKB.m_nbyBuffer, nbyMaxTest + nbyTest);
                Test__Expect_EQ(nbyMaxTest + nbyTest, tgCM_UT_ST__ST__Length_U08( &tgKB ));
                Test__Expect_EQ(nbyMaxTest + nbyTest, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

                tgCM_UT_ST__ST__Free( &tgKB );


                /* Append with pointer to non-self, with initialized string */

                for (TgRSIZE uiIndex2 = 0; uiIndex2 < TgARRAY_COUNT(s_ambzTest); ++uiIndex2)
                {
                    TgRSIZE_C                           nbyMaxTest2 = s_asTest_Length[uiIndex2].m_nbyCharacters;

                    tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[uiIndex2] );
                    tgCM_UT_ST__ST__PT_Append( &tgKB, mbzTest_Start, mbzTest_End );
                    mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );

                    Test__Expect_EQ(0, memcmp( mbzKB, s_ambzTest[uiIndex2], nbyMaxTest2 ));
                    Test__Expect_EQ( 0, memcmp( mbzKB + nbyMaxTest2, mbzTest_Start, nbyTest ) );
                    Test__Expect_EQ(tgKB.m_nbyBuffer, nbyMaxTest2 + nbyTest);
                    Test__Expect_EQ(nbyMaxTest2 + nbyTest, tgCM_UT_ST__ST__Length_U08( &tgKB ));
                    Test__Expect_EQ(nbyMaxTest2 + nbyTest, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

                    tgCM_UT_ST__ST__Free( &tgKB );
                };

                TgMACRO_STEP_INDEX( uiTest_End, nuiMaxTest, uiMaxStep_nuiTest );
            };

            TgMACRO_STEP_INDEX( uiTest_Start, nuiMaxTest, uiMaxStep_nuiTest );
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__ST_Append --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__ST_Append )
{
    for (TgRSIZE uiIndex = 0; uiIndex < TgARRAY_COUNT(s_ambzTest); ++uiIndex)
    {
        TgRSIZE_C                           nbyMaxTest = s_asTest_Length[uiIndex].m_nbyCharacters;

        STg2_UT_ST__ST                      tgKB;
        TgCHAR_U8_CP                        mbzKB;

        /* Append with pointer to self */

        tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[uiIndex] );
        tgCM_UT_ST__ST__ST_Append( &tgKB, &tgKB );
        mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );

        Test__Expect_EQ(0, memcmp( mbzKB, s_ambzTest[uiIndex], nbyMaxTest ));
        Test__Expect_EQ(0, memcmp( mbzKB + nbyMaxTest, s_ambzTest[uiIndex], nbyMaxTest ));
        Test__Expect_EQ(tgKB.m_nbyBuffer, nbyMaxTest + nbyMaxTest);
        Test__Expect_EQ(nbyMaxTest + nbyMaxTest, tgCM_UT_ST__ST__Length_U08( &tgKB ));
        Test__Expect_EQ(nbyMaxTest + nbyMaxTest, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

        tgCM_UT_ST__ST__Free( &tgKB );


        /* Append with pointer to non-self, with empty string */

        for (TgRSIZE uiIndex2 = 0; uiIndex2 < TgARRAY_COUNT(s_ambzTest); ++uiIndex2)
        {
            TgRSIZE_C                           nbyMaxTest2 = s_asTest_Length[uiIndex2].m_nbyCharacters;

            STg2_UT_ST__ST                      tgKC;
            
            tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[uiIndex2] );
            tgCM_UT_ST__ST__SZ_Init( &tgKC, s_ambzTest[uiIndex] );
            tgCM_UT_ST__ST__ST_Append( &tgKB, &tgKC );
            mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );

            Test__Expect_EQ(0, memcmp( mbzKB, s_ambzTest[uiIndex2], nbyMaxTest2 ));
            Test__Expect_EQ(0, memcmp( mbzKB + nbyMaxTest2, s_ambzTest[uiIndex], nbyMaxTest ));
            Test__Expect_EQ(tgKB.m_nbyBuffer, nbyMaxTest2 + nbyMaxTest);
            Test__Expect_EQ(tgKB.m_nbyBuffer, tgCM_UT_ST__ST__Length_U08( &tgKB ));
            Test__Expect_EQ(tgKB.m_nbyBuffer, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

            tgCM_UT_ST__ST__Free( &tgKC );
            tgCM_UT_ST__ST__Free( &tgKB );
        };
    };


    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__SO_Append --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SO_Append )
{
    for (TgRSIZE uiIndex = 0; uiIndex < TgARRAY_COUNT(s_ambzTest); ++uiIndex)
    {
        TgRSIZE_C                           nbyMaxTest = s_asTest_Length[uiIndex].m_nbyCharacters;
        TgRSIZE_C                           nuiMaxTest = s_asTest_Length[uiIndex].m_nuiCharacters;
        TgRSIZE_C       uiMaxStep_nuiTest = tgCM_MIN_UMAX( nuiMaxTest, 10 );

        for (TgRSIZE uiTest_Start = 0, uiTest_Start_Step = 0; uiTest_Start_Step <= uiMaxStep_nuiTest; ++uiTest_Start_Step)
        {
            TgCHAR_U8_CPC   mbzTest_Start = tgUSZ_Query_At( s_ambzTest[uiIndex], nbyMaxTest + 1, uiTest_Start );
            TgRSIZE_C                           nbyTest = nbyMaxTest - (TgRSIZE)(mbzTest_Start - s_ambzTest[uiIndex]);

            STg2_UT_ST__ST                      tgKB;
            TgCHAR_U8_CP                        mbzKB;

            /* Append with pointer to self */

            tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[uiIndex] );
            tgCM_UT_ST__ST__SO_Append( &tgKB, &tgKB, uiTest_Start );
            mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );

            Test__Expect_EQ(0, memcmp( mbzKB, s_ambzTest[uiIndex], nbyMaxTest ));
            Test__Expect_EQ(0, memcmp( mbzKB + nbyMaxTest, mbzTest_Start, nbyTest ));
            Test__Expect_EQ(tgKB.m_nbyBuffer, nbyMaxTest + nbyTest);
            Test__Expect_EQ(tgKB.m_nbyBuffer, tgCM_UT_ST__ST__Length_U08( &tgKB ));
            Test__Expect_EQ(tgKB.m_nbyBuffer, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

            tgCM_UT_ST__ST__Free( &tgKB );


            /* Append with pointer to non-self, with empty string */
            for (TgRSIZE uiIndex2 = 0; uiIndex2 < TgARRAY_COUNT(s_ambzTest); ++uiIndex2)
            {
                TgRSIZE_C                           nbyMaxTest2 = s_asTest_Length[uiIndex2].m_nbyCharacters;

                STg2_UT_ST__ST                      tgKC;
                
                tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[uiIndex2] );
                tgCM_UT_ST__ST__SZ_Init( &tgKC, s_ambzTest[uiIndex] );
                tgCM_UT_ST__ST__SO_Append( &tgKB, &tgKC, uiTest_Start );
                mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );

                Test__Expect_EQ(0, memcmp( mbzKB, s_ambzTest[uiIndex2], nbyMaxTest2 ));
                Test__Expect_EQ(0, memcmp( mbzKB + nbyMaxTest2, mbzTest_Start, nbyTest ));
                Test__Expect_EQ(tgKB.m_nbyBuffer, nbyMaxTest2 + nbyTest);
                Test__Expect_EQ(tgKB.m_nbyBuffer, tgCM_UT_ST__ST__Length_U08( &tgKB ));
                Test__Expect_EQ(tgKB.m_nbyBuffer, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

                tgCM_UT_ST__ST__Free( &tgKC );
                tgCM_UT_ST__ST__Free( &tgKB );
            };

            TgMACRO_STEP_INDEX( uiTest_Start, nuiMaxTest, uiMaxStep_nuiTest );
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__SF_Append --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SF_Append )
{
    for (TgRSIZE uiIndex = 0; uiIndex < TgARRAY_COUNT(s_ambzTest); ++uiIndex)
    {
        TgRSIZE_C                           nbyMaxTest = s_asTest_Length[uiIndex].m_nbyCharacters;
        TgRSIZE_C                           nuiMaxTest = s_asTest_Length[uiIndex].m_nuiCharacters;
        TgRSIZE_C       uiMaxStep_nuiTest = tgCM_MIN_UMAX( nuiMaxTest, 10 );

        /* Assign with pointer to self */

        for (TgRSIZE uiTest_Start = 0, uiTest_Start_Step = 0; uiTest_Start_Step <= uiMaxStep_nuiTest; ++uiTest_Start_Step)
        {
            TgCHAR_U8_CPC   mbzTest_Start = tgUSZ_Query_At( s_ambzTest[uiIndex], nbyMaxTest + 1, uiTest_Start );

            for (TgRSIZE uiTest_End = uiTest_Start, uiTest_End_Step = uiTest_Start_Step; uiTest_End_Step <= uiMaxStep_nuiTest; ++uiTest_End_Step)
            {
                TgCHAR_U8_CPC   mbzTest_End = tgUSZ_Query_At( s_ambzTest[uiIndex], nbyMaxTest + 1, uiTest_End );
                TgRSIZE_C                           nbyTest = mbzTest_End >= mbzTest_Start ? (TgRSIZE)(mbzTest_End - mbzTest_Start) : 0;

                STg2_UT_ST__ST                      tgKB;
                TgCHAR_U8_CP                        mbzKB;

                tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[uiIndex] );
                tgCM_UT_ST__ST__SF_Append( &tgKB, &tgKB, uiTest_Start, uiTest_End - uiTest_Start );
                mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );

                Test__Expect_EQ(0, memcmp( mbzKB, s_ambzTest[uiIndex], nbyMaxTest ));
                Test__Expect_EQ(0, memcmp( mbzKB + nbyMaxTest, mbzTest_Start, nbyTest ));
                Test__Expect_EQ(tgKB.m_nbyBuffer, nbyMaxTest + nbyTest);
                Test__Expect_EQ(tgKB.m_nbyBuffer, tgCM_UT_ST__ST__Length_U08( &tgKB ));
                Test__Expect_EQ(tgKB.m_nbyBuffer, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

                tgCM_UT_ST__ST__Free( &tgKB );


                /* Append with pointer to non-self, with empty string */

                for (TgRSIZE uiIndex2 = 0; uiIndex2 < TgARRAY_COUNT(s_ambzTest); ++uiIndex2)
                {
                    TgRSIZE_C                           nbyMaxTest2 = s_asTest_Length[uiIndex2].m_nbyCharacters;

                    STg2_UT_ST__ST                      tgKC;
                    
                    tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[uiIndex2] );
                    tgCM_UT_ST__ST__SZ_Init( &tgKC, s_ambzTest[uiIndex] );
                    tgCM_UT_ST__ST__SF_Append( &tgKB, &tgKC, uiTest_Start, uiTest_End - uiTest_Start );
                    mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );

                    Test__Expect_EQ(0, memcmp( mbzKB, s_ambzTest[uiIndex2], nbyMaxTest2 ));
                    Test__Expect_EQ(0, memcmp( mbzKB + nbyMaxTest2, mbzTest_Start, nbyTest ));
                    Test__Expect_EQ(tgKB.m_nbyBuffer, nbyMaxTest2 + nbyTest);
                    Test__Expect_EQ(tgKB.m_nbyBuffer, tgCM_UT_ST__ST__Length_U08( &tgKB ));
                    Test__Expect_EQ(tgKB.m_nbyBuffer, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

                    tgCM_UT_ST__ST__Free( &tgKC );
                    tgCM_UT_ST__ST__Free( &tgKB );
                };

                TgMACRO_STEP_INDEX( uiTest_End, nuiMaxTest, uiMaxStep_nuiTest );
            };

            TgMACRO_STEP_INDEX( uiTest_Start, nuiMaxTest, uiMaxStep_nuiTest );
        };
    };


    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__SZ_Insert --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SZ_Insert )
{
    for (TgRSIZE uiIndex = 0; uiIndex < TgARRAY_COUNT(s_ambzTest); ++uiIndex)
    {
        TgRSIZE_C                           nbyMaxTest = s_asTest_Length[uiIndex].m_nbyCharacters;
        TgRSIZE_C                           nuiMaxTest = s_asTest_Length[uiIndex].m_nuiCharacters;
        TgRSIZE_C       uiMaxStep_nuiTest = tgCM_MIN_UMAX( nuiMaxTest, 10 );

        /* Assign with pointer to self */
        for (TgRSIZE uiTest_Start = 0, uiTest_Start_Step = 0; uiTest_Start_Step <= uiMaxStep_nuiTest; ++uiTest_Start_Step)
        {
            TgCHAR_U8_CPC   mbzTest_Start = tgUSZ_Query_At( s_ambzTest[uiIndex], nbyMaxTest + 1, uiTest_Start );
            TgRSIZE_C                           nbyTest = nbyMaxTest - (TgRSIZE)(mbzTest_Start - s_ambzTest[uiIndex]);

            for (TgRSIZE uiInsert_Index = 0, uiInsert_Index_Step = 0; uiInsert_Index_Step <= uiMaxStep_nuiTest; ++uiInsert_Index_Step)
            {
                STg2_UT_ST__ST                      tgKB;
                TgCHAR_U8_CP                        mbzKB, mbzKB_Start;
                TgRSIZE                             nbyKB_Start;

                tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[uiIndex] );
                mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );
                mbzKB_Start = tgUSZ_Query_At( mbzKB, tgKB.m_nbyBuffer + 1, uiTest_Start );
                tgCM_UT_ST__ST__SZ_Insert( &tgKB, uiInsert_Index, mbzKB_Start );

                mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );
                mbzKB_Start = tgUSZ_Query_At( mbzKB, tgKB.m_nbyBuffer + 1, uiInsert_Index );
                nbyKB_Start = (TgRSIZE)(mbzKB_Start - mbzKB);

                Test__Expect_EQ(0, memcmp( mbzKB, s_ambzTest[uiIndex], nbyKB_Start ));
                Test__Expect_EQ(0, memcmp( mbzKB_Start, mbzTest_Start, nbyTest ));
                Test__Expect_EQ(0, memcmp( mbzKB_Start + nbyTest, s_ambzTest[uiIndex] + nbyKB_Start, nbyMaxTest - nbyKB_Start ) );
                Test__Expect_EQ(tgKB.m_nbyBuffer, nbyMaxTest + nbyTest);
                Test__Expect_EQ(nbyMaxTest + nbyTest, tgCM_UT_ST__ST__Length_U08( &tgKB ));
                Test__Expect_EQ(nbyMaxTest + nbyTest, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

                tgCM_UT_ST__ST__Free( &tgKB );

                TgMACRO_STEP_INDEX( uiInsert_Index, nuiMaxTest, uiMaxStep_nuiTest );
            };


            /* Insert with pointer to non-self */
            for (TgRSIZE uiIndex2 = 0; uiIndex2 < TgARRAY_COUNT(s_ambzTest); ++uiIndex2)
            {
                for (TgRSIZE uiInsert_Index = 0, uiInsert_Index_Step = 0; uiInsert_Index_Step <= uiMaxStep_nuiTest; ++uiInsert_Index_Step)
                {
                    TgRSIZE_C                           nbyMaxTest2 = s_asTest_Length[uiIndex2].m_nbyCharacters;
                    TgRSIZE_C                           nuiMaxTest2 = s_asTest_Length[uiIndex2].m_nuiCharacters;
                    TgRSIZE_C       uiMaxStep_nuiTest2 = tgCM_MIN_UMAX( nuiMaxTest2, 10 );

                    STg2_UT_ST__ST                      tgKB;
                    TgCHAR_U8_CP                        mbzKB, mbzKB_Start;
                    TgRSIZE                             nbyKB_Start;

                    tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[uiIndex2] );
                    tgCM_UT_ST__ST__SZ_Insert( &tgKB, uiInsert_Index, mbzTest_Start );

                    mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );
                    mbzKB_Start = tgUSZ_Query_At( mbzKB, tgKB.m_nbyBuffer + 1, uiInsert_Index );
                    nbyKB_Start = (TgRSIZE)(mbzKB_Start - mbzKB);

                    Test__Expect_EQ(0, memcmp( mbzKB, s_ambzTest[uiIndex2], nbyKB_Start ));
                    Test__Expect_EQ(0, memcmp( mbzKB_Start, mbzTest_Start, nbyTest ));
                    Test__Expect_EQ(0, memcmp( mbzKB_Start + nbyTest, s_ambzTest[uiIndex2] + nbyKB_Start, nbyMaxTest2 - nbyKB_Start ) );
                    Test__Expect_EQ(tgKB.m_nbyBuffer, nbyMaxTest2 + nbyTest);
                    Test__Expect_EQ(tgKB.m_nbyBuffer, tgCM_UT_ST__ST__Length_U08( &tgKB ));
                    Test__Expect_EQ(tgKB.m_nbyBuffer, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

                    tgCM_UT_ST__ST__Free( &tgKB );

                    TgMACRO_STEP_INDEX( uiInsert_Index, nuiMaxTest2, uiMaxStep_nuiTest2 );
                };
            };

            TgMACRO_STEP_INDEX( uiTest_Start, nuiMaxTest, uiMaxStep_nuiTest );
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__SN_Insert --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SN_Insert )
{
    for (TgRSIZE uiIndex = 0; uiIndex < TgARRAY_COUNT(s_ambzTest); ++uiIndex)
    {
        TgRSIZE_C                           nbyMaxTest = s_asTest_Length[uiIndex].m_nbyCharacters;
        TgRSIZE_C       uiMaxStep_nbyTest = tgCM_MIN_UMAX( nbyMaxTest, 10 );
        TgRSIZE_C                           nuiMaxTest = s_asTest_Length[uiIndex].m_nuiCharacters;
        TgRSIZE_C       uiMaxStep_nuiTest = tgCM_MIN_UMAX( nuiMaxTest, 10 );

        for (TgRSIZE nbySize = 0, nbySize_Step = 0; nbySize_Step <= uiMaxStep_nbyTest; ++nbySize_Step)
        {
            for (TgRSIZE uiTest_Start = 0, uiTest_Start_Step = 0; uiTest_Start_Step <= uiMaxStep_nuiTest; ++uiTest_Start_Step)
            {
                TgCHAR_U8_CPC   mbzTest_Start = tgUSZ_Query_At( s_ambzTest[uiIndex], nbyMaxTest + 1, uiTest_Start );
                TgCHAR_U8_CPC   mbzTest_End = tgUSZ_Query_End( mbzTest_Start, nbySize, KTgMAX_RSIZE );
                TgRSIZE_C                           nbyTest = (TgRSIZE)(mbzTest_End - mbzTest_Start);

                for (TgRSIZE uiInsert_Index = 0, uiInsert_Index_Step = 0; uiInsert_Index_Step <= uiMaxStep_nuiTest; ++uiInsert_Index_Step)
                {
                    STg2_UT_ST__ST                      tgKB;
                    TgCHAR_U8_CP                        mbzKB, mbzKB_Start;
                    TgRSIZE                             nbyKB_Start;

                    /* Insert with pointer to self */
                    tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[uiIndex] );
                    mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );
                    mbzKB_Start = tgUSZ_Query_At( mbzKB, tgKB.m_nbyBuffer + 1, uiTest_Start );
                    tgCM_UT_ST__ST__SN_Insert( &tgKB, uiInsert_Index, mbzKB_Start, nbySize );

                    mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );
                    mbzKB_Start = tgUSZ_Query_At( mbzKB, tgKB.m_nbyBuffer + 1, uiInsert_Index );
                    nbyKB_Start = (TgRSIZE)(mbzKB_Start - mbzKB);

                    Test__Expect_EQ(0, memcmp( mbzKB, s_ambzTest[uiIndex], nbyKB_Start ));
                    Test__Expect_EQ(0, memcmp( mbzKB_Start, mbzTest_Start, nbyTest ));
                    Test__Expect_EQ(0, memcmp( mbzKB_Start + nbyTest, s_ambzTest[uiIndex] + nbyKB_Start, nbyMaxTest - nbyKB_Start ) );
                    Test__Expect_EQ(tgKB.m_nbyBuffer, nbyMaxTest + nbyTest);
                    Test__Expect_EQ(tgKB.m_nbyBuffer, tgCM_UT_ST__ST__Length_U08( &tgKB ));
                    Test__Expect_EQ(tgKB.m_nbyBuffer, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

                    tgCM_UT_ST__ST__Free( &tgKB );

                    TgMACRO_STEP_INDEX( uiInsert_Index, nuiMaxTest, uiMaxStep_nuiTest );
                };


                for (TgRSIZE uiIndex2 = 0; uiIndex2 < TgARRAY_COUNT(s_ambzTest); ++uiIndex2)
                {
                    for (TgRSIZE uiInsert_Index = 0, uiInsert_Index_Step = 0; uiInsert_Index_Step <= uiMaxStep_nuiTest; ++uiInsert_Index_Step)
                    {
                        TgRSIZE_C                           nbyMaxTest2 = s_asTest_Length[uiIndex2].m_nbyCharacters;
                        TgRSIZE_C                           nuiMaxTest2 = s_asTest_Length[uiIndex2].m_nuiCharacters;
                        TgRSIZE_C       uiMaxStep_nuiTest2 = tgCM_MIN_UMAX( nuiMaxTest2, 10 );

                        STg2_UT_ST__ST                      tgKB;
                        TgCHAR_U8_CP                        mbzKB, mbzKB_Start;
                        TgRSIZE                             nbyKB_Start;

                        /* Insert with pointer to non-self, with initialized string */
                        tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[uiIndex2] );
                        tgCM_UT_ST__ST__SN_Insert( &tgKB, uiInsert_Index, mbzTest_Start, nbySize );

                        mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );
                        mbzKB_Start = tgUSZ_Query_At( mbzKB, tgKB.m_nbyBuffer + 1, uiInsert_Index );
                        nbyKB_Start = (TgRSIZE)(mbzKB_Start - mbzKB);

                        Test__Expect_EQ(0, memcmp( mbzKB, s_ambzTest[uiIndex2], nbyKB_Start ));
                        Test__Expect_EQ(0, memcmp( mbzKB_Start, mbzTest_Start, nbyTest ));
                        Test__Expect_EQ(0, memcmp( mbzKB_Start + nbyTest, s_ambzTest[uiIndex2] + nbyKB_Start, nbyMaxTest2 - nbyKB_Start ) );
                        Test__Expect_EQ(tgKB.m_nbyBuffer, nbyMaxTest2 + nbyTest);
                        Test__Expect_EQ(tgKB.m_nbyBuffer, tgCM_UT_ST__ST__Length_U08( &tgKB ));
                        Test__Expect_EQ(tgKB.m_nbyBuffer, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

                        tgCM_UT_ST__ST__Free( &tgKB );

                        TgMACRO_STEP_INDEX( uiInsert_Index, nuiMaxTest2, uiMaxStep_nuiTest2 );
                    };
                };

                TgMACRO_STEP_INDEX( uiTest_Start, nuiMaxTest, uiMaxStep_nuiTest );
            };

            TgMACRO_STEP_INDEX( nbySize, nbyMaxTest, uiMaxStep_nbyTest );
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__PT_Insert --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__PT_Insert )
{
    for (TgRSIZE uiIndex = 0; uiIndex < TgARRAY_COUNT(s_ambzTest); ++uiIndex)
    {
        TgRSIZE_C                           nbyMaxTest = s_asTest_Length[uiIndex].m_nbyCharacters;
        TgRSIZE_C                           nuiMaxTest = s_asTest_Length[uiIndex].m_nuiCharacters;
        TgRSIZE_C       uiMaxStep_nuiTest = tgCM_MIN_UMAX( nuiMaxTest, 10 );

        for (TgRSIZE uiTest_Start = 0, uiTest_Start_Step = 0; uiTest_Start_Step <= uiMaxStep_nuiTest; ++uiTest_Start_Step)
        {
            TgCHAR_U8_CPC   mbzTest_Start = tgUSZ_Query_At( s_ambzTest[uiIndex], nbyMaxTest + 1, uiTest_Start );

            for (TgRSIZE uiTest_End = uiTest_Start, uiTest_End_Step = uiTest_Start_Step; uiTest_End_Step <= uiMaxStep_nuiTest; ++uiTest_End_Step)
            {
                TgCHAR_U8_CPC   mbzTest_End = tgUSZ_Query_At( s_ambzTest[uiIndex], nbyMaxTest + 1, uiTest_End );
                TgRSIZE_C                           nbyTest = mbzTest_End >= mbzTest_Start ? (TgRSIZE)(mbzTest_End - mbzTest_Start) : 0;

                for (TgRSIZE uiInsert_Index = 0, uiInsert_Index_Step = 0; uiInsert_Index_Step <= uiMaxStep_nuiTest; ++uiInsert_Index_Step)
                {
                    STg2_UT_ST__ST                      tgKB;
                    TgCHAR_U8_CP                        mbzKB, mbzKB_Start, mbzKB_End;
                    TgRSIZE                             nbyKB_Start;

                    /* Insert with pointer to self (start) */
                    tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[uiIndex] );
                    mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );
                    mbzKB_Start = tgUSZ_Query_At( mbzKB, nbyMaxTest + 1, uiTest_Start );
                    mbzKB_End = tgUSZ_Query_At( mbzKB, nbyMaxTest + 1, uiTest_End );
                    tgCM_UT_ST__ST__PT_Insert( &tgKB, uiInsert_Index, mbzKB_Start, mbzKB_End );

                    mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );
                    mbzKB_Start = tgUSZ_Query_At( mbzKB, tgKB.m_nbyBuffer + 1, uiInsert_Index );
                    nbyKB_Start = (TgRSIZE)(mbzKB_Start - mbzKB);

                    Test__Expect_EQ(0, memcmp( mbzKB, s_ambzTest[uiIndex], nbyKB_Start ));
                    Test__Expect_EQ(0, memcmp( mbzKB_Start, mbzTest_Start, nbyTest ) );
                    Test__Expect_EQ(0, memcmp( mbzKB_Start + nbyTest, s_ambzTest[uiIndex] + nbyKB_Start, nbyMaxTest - nbyKB_Start ));
                    Test__Expect_EQ(tgKB.m_nbyBuffer, nbyMaxTest + nbyTest);
                    Test__Expect_EQ(tgKB.m_nbyBuffer, tgCM_UT_ST__ST__Length_U08( &tgKB ));
                    Test__Expect_EQ(tgKB.m_nbyBuffer, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

                    tgCM_UT_ST__ST__Free( &tgKB );

                    TgMACRO_STEP_INDEX( uiInsert_Index, nuiMaxTest, uiMaxStep_nuiTest );
                };


                for (TgRSIZE uiIndex2 = 0; uiIndex2 < TgARRAY_COUNT(s_ambzTest); ++uiIndex2)
                {
                    for (TgRSIZE uiInsert_Index = 0, uiInsert_Index_Step = 0; uiInsert_Index_Step <= uiMaxStep_nuiTest; ++uiInsert_Index_Step)
                    {
                        TgRSIZE_C                           nbyMaxTest2 = s_asTest_Length[uiIndex2].m_nbyCharacters;
                        TgRSIZE_C                           nuiMaxTest2 = s_asTest_Length[uiIndex2].m_nuiCharacters;
                        TgRSIZE_C       uiMaxStep_nuiTest2 = tgCM_MIN_UMAX( nuiMaxTest2, 10 );

                        STg2_UT_ST__ST                      tgKB;
                        TgCHAR_U8_CP                        mbzKB, mbzKB_Start;
                        TgRSIZE                             nbyKB_Start;

                        /* Insert with pointer to non-self, with initialized string */
                        tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[uiIndex2] );
                        tgCM_UT_ST__ST__PT_Insert( &tgKB, uiInsert_Index, mbzTest_Start, mbzTest_End );

                        mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );
                        mbzKB_Start = tgUSZ_Query_At( mbzKB, tgKB.m_nbyBuffer + 1, uiInsert_Index );
                        nbyKB_Start = (TgRSIZE)(mbzKB_Start - mbzKB);

                        Test__Expect_EQ(0, memcmp( mbzKB, s_ambzTest[uiIndex2], nbyKB_Start ));
                        Test__Expect_EQ(0, memcmp( mbzKB_Start, mbzTest_Start, nbyTest ) );
                        Test__Expect_EQ(0, memcmp( mbzKB_Start + nbyTest, s_ambzTest[uiIndex2] + nbyKB_Start, nbyMaxTest2 - nbyKB_Start ));
                        Test__Expect_EQ(tgKB.m_nbyBuffer, nbyMaxTest2 + nbyTest);
                        Test__Expect_EQ(tgKB.m_nbyBuffer, tgCM_UT_ST__ST__Length_U08( &tgKB ));
                        Test__Expect_EQ(tgKB.m_nbyBuffer, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

                        tgCM_UT_ST__ST__Free( &tgKB );

                        TgMACRO_STEP_INDEX( uiInsert_Index, nuiMaxTest2, uiMaxStep_nuiTest2 );
                    };
                };

                TgMACRO_STEP_INDEX( uiTest_End, nuiMaxTest, uiMaxStep_nuiTest );
            };

            TgMACRO_STEP_INDEX( uiTest_Start, nuiMaxTest, uiMaxStep_nuiTest );
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__ST_Insert --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__ST_Insert )
{
    for (TgRSIZE uiIndex = 0; uiIndex < TgARRAY_COUNT(s_ambzTest); ++uiIndex)
    {
        TgRSIZE_C                           nbyMaxTest = s_asTest_Length[uiIndex].m_nbyCharacters;
        TgRSIZE_C                           nuiMaxTest = s_asTest_Length[uiIndex].m_nuiCharacters;
        TgRSIZE_C       uiMaxStep_nuiTest = tgCM_MIN_UMAX( nuiMaxTest, 10 );

        for (TgRSIZE uiInsert_Index = 0, uiInsert_Index_Step = 0; uiInsert_Index_Step <= uiMaxStep_nuiTest; ++uiInsert_Index_Step)
        {
            STg2_UT_ST__ST                      tgKB;
            TgCHAR_U8_CP                        mbzKB, mbzKB_Start;
            TgRSIZE                             nbyKB_Start;

            /* Insert with pointer to self */
            tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[uiIndex] );
            tgCM_UT_ST__ST__ST_Insert( &tgKB, uiInsert_Index, &tgKB );

            mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );
            mbzKB_Start = tgUSZ_Query_At( mbzKB, tgKB.m_nbyBuffer + 1, uiInsert_Index );
            nbyKB_Start = (TgRSIZE)(mbzKB_Start - mbzKB);

            Test__Expect_EQ(0, memcmp( mbzKB, s_ambzTest[uiIndex], nbyKB_Start ));
            Test__Expect_EQ(0, memcmp( mbzKB_Start, s_ambzTest[uiIndex], nbyMaxTest ));
            Test__Expect_EQ(0, memcmp( mbzKB_Start + nbyMaxTest, s_ambzTest[uiIndex] + nbyKB_Start, nbyMaxTest - nbyKB_Start ));
            Test__Expect_EQ(tgKB.m_nbyBuffer, nbyMaxTest + nbyMaxTest);
            Test__Expect_EQ(tgKB.m_nbyBuffer, tgCM_UT_ST__ST__Length_U08( &tgKB ));
            Test__Expect_EQ(tgKB.m_nbyBuffer, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

            tgCM_UT_ST__ST__Free( &tgKB );

            TgMACRO_STEP_INDEX( uiInsert_Index, nuiMaxTest, uiMaxStep_nuiTest );
        };


        for (TgRSIZE uiIndex2 = 0; uiIndex2 < TgARRAY_COUNT(s_ambzTest); ++uiIndex2)
        {
            for (TgRSIZE uiInsert_Index = 0, uiInsert_Index_Step = 0; uiInsert_Index_Step <= uiMaxStep_nuiTest; ++uiInsert_Index_Step)
            {
                TgRSIZE_C                           nbyMaxTest2 = s_asTest_Length[uiIndex2].m_nbyCharacters;
                TgRSIZE_C                           nuiMaxTest2 = s_asTest_Length[uiIndex2].m_nuiCharacters;
                TgRSIZE_C       uiMaxStep_nuiTest2 = tgCM_MIN_UMAX( nuiMaxTest2, 10 );

                STg2_UT_ST__ST                      tgKB, tgKC;
                TgCHAR_U8_CP                        mbzKB, mbzKB_Start;
                TgRSIZE                             nbyKB_Start;

                /* Insert with pointer to non-self, with empty string */
                tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[uiIndex2] );
                tgCM_UT_ST__ST__SZ_Init( &tgKC, s_ambzTest[uiIndex] );
                tgCM_UT_ST__ST__ST_Insert( &tgKB, uiInsert_Index, &tgKC );

                mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );
                mbzKB_Start = tgUSZ_Query_At( mbzKB, tgKB.m_nbyBuffer + 1, uiInsert_Index );
                nbyKB_Start = (TgRSIZE)(mbzKB_Start - mbzKB);

                Test__Expect_EQ(0, memcmp( mbzKB, s_ambzTest[uiIndex2], nbyKB_Start ));
                Test__Expect_EQ(0, memcmp( mbzKB_Start, s_ambzTest[uiIndex], nbyMaxTest ));
                Test__Expect_EQ(0, memcmp( mbzKB_Start + nbyMaxTest, s_ambzTest[uiIndex2] + nbyKB_Start, nbyMaxTest2 - nbyKB_Start ));
                Test__Expect_EQ(tgKB.m_nbyBuffer, nbyMaxTest2 + nbyMaxTest);
                Test__Expect_EQ(tgKB.m_nbyBuffer, tgCM_UT_ST__ST__Length_U08( &tgKB ));
                Test__Expect_EQ(tgKB.m_nbyBuffer, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

                tgCM_UT_ST__ST__Free( &tgKC );
                tgCM_UT_ST__ST__Free( &tgKB );
            
                TgMACRO_STEP_INDEX( uiInsert_Index, nuiMaxTest2, uiMaxStep_nuiTest2 );
            };
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__SO_Insert --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SO_Insert )
{
    for (TgRSIZE uiIndex = 0; uiIndex < TgARRAY_COUNT(s_ambzTest); ++uiIndex)
    {
        TgRSIZE_C                           nbyMaxTest = s_asTest_Length[uiIndex].m_nbyCharacters;
        TgRSIZE_C                           nuiMaxTest = s_asTest_Length[uiIndex].m_nuiCharacters;
        TgRSIZE_C       uiMaxStep_nuiTest = tgCM_MIN_UMAX( nuiMaxTest, 10 );

        for (TgRSIZE uiTest_Start = 0, uiTest_Start_Step = 0; uiTest_Start_Step <= uiMaxStep_nuiTest; ++uiTest_Start_Step)
        {
            TgCHAR_U8_CPC   mbzTest_Start = tgUSZ_Query_At( s_ambzTest[uiIndex], nbyMaxTest + 1, uiTest_Start );
            TgRSIZE_C                           nbyTest = nbyMaxTest - (TgRSIZE)(mbzTest_Start - s_ambzTest[uiIndex]);

            for (TgRSIZE uiInsert_Index = 0, uiInsert_Index_Step = 0; uiInsert_Index_Step <= uiMaxStep_nuiTest; ++uiInsert_Index_Step)
            {
                STg2_UT_ST__ST                      tgKB;
                TgCHAR_U8_CP                        mbzKB, mbzKB_Start;
                TgRSIZE                             nbyKB_Start;

                /* Assign with pointer to self */
                tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[uiIndex] );
                tgCM_UT_ST__ST__SO_Insert( &tgKB, uiInsert_Index, &tgKB, uiTest_Start );

                mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );
                mbzKB_Start = tgUSZ_Query_At( mbzKB, tgKB.m_nbyBuffer + 1, uiInsert_Index );
                nbyKB_Start = (TgRSIZE)(mbzKB_Start - mbzKB);

                Test__Expect_EQ(0, memcmp( mbzKB, s_ambzTest[uiIndex], nbyKB_Start ));
                Test__Expect_EQ(0, memcmp( mbzKB_Start, mbzTest_Start, nbyTest ));
                Test__Expect_EQ(0, memcmp( mbzKB_Start + nbyTest, s_ambzTest[uiIndex] + nbyKB_Start, nbyMaxTest - nbyKB_Start ));
                Test__Expect_EQ(tgKB.m_nbyBuffer, nbyMaxTest + nbyTest);
                Test__Expect_EQ(tgKB.m_nbyBuffer, tgCM_UT_ST__ST__Length_U08( &tgKB ));
                Test__Expect_EQ(tgKB.m_nbyBuffer, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

                tgCM_UT_ST__ST__Free( &tgKB );

                TgMACRO_STEP_INDEX( uiInsert_Index, nuiMaxTest, uiMaxStep_nuiTest );
            };


            for (TgRSIZE uiIndex2 = 0; uiIndex2 < TgARRAY_COUNT(s_ambzTest); ++uiIndex2)
            {
                for (TgRSIZE uiInsert_Index = 0, uiInsert_Index_Step = 0; uiInsert_Index_Step <= uiMaxStep_nuiTest; ++uiInsert_Index_Step)
                {
                    TgRSIZE_C                           nbyMaxTest2 = s_asTest_Length[uiIndex2].m_nbyCharacters;
                    TgRSIZE_C                           nuiMaxTest2 = s_asTest_Length[uiIndex2].m_nuiCharacters;
                    TgRSIZE_C       uiMaxStep_nuiTest2 = tgCM_MIN_UMAX( nuiMaxTest2, 10 );

                    STg2_UT_ST__ST                      tgKB, tgKC;
                    TgCHAR_U8_CP                        mbzKB, mbzKB_Start;
                    TgRSIZE                             nbyKB_Start;

                    /* Insert with pointer to non-self, with empty string */
                    tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[uiIndex2] );
                    tgCM_UT_ST__ST__SZ_Init( &tgKC, s_ambzTest[uiIndex] );
                    tgCM_UT_ST__ST__SO_Insert( &tgKB, uiInsert_Index, &tgKC, uiTest_Start );

                    mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );
                    mbzKB_Start = tgUSZ_Query_At( mbzKB, tgKB.m_nbyBuffer + 1, uiInsert_Index );
                    nbyKB_Start = (TgRSIZE)(mbzKB_Start - mbzKB);

                    Test__Expect_EQ(0, memcmp( mbzKB, s_ambzTest[uiIndex2], nbyKB_Start ));
                    Test__Expect_EQ(0, memcmp( mbzKB_Start, mbzTest_Start, nbyTest ));
                    Test__Expect_EQ(0, memcmp( mbzKB_Start + nbyTest, s_ambzTest[uiIndex2] + nbyKB_Start, nbyMaxTest2 - nbyKB_Start ));
                    Test__Expect_EQ(tgKB.m_nbyBuffer, nbyMaxTest2 + nbyTest);
                    Test__Expect_EQ(tgKB.m_nbyBuffer, tgCM_UT_ST__ST__Length_U08( &tgKB ));
                    Test__Expect_EQ(tgKB.m_nbyBuffer, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

                    tgCM_UT_ST__ST__Free( &tgKC );
                    tgCM_UT_ST__ST__Free( &tgKB );

                    TgMACRO_STEP_INDEX( uiInsert_Index, nuiMaxTest2, uiMaxStep_nuiTest2 );
                };
            };

            TgMACRO_STEP_INDEX( uiTest_Start, nuiMaxTest, uiMaxStep_nuiTest );
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__SF_Insert --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SF_Insert )
{
    for (TgRSIZE uiIndex = 0; uiIndex < TgARRAY_COUNT(s_ambzTest); ++uiIndex)
    {
        TgRSIZE_C                           nbyMaxTest = s_asTest_Length[uiIndex].m_nbyCharacters;
        TgRSIZE_C                           nuiMaxTest = s_asTest_Length[uiIndex].m_nuiCharacters;
        TgRSIZE_C       uiMaxStep_nuiTest = tgCM_MIN_UMAX( nuiMaxTest, 10 );

        for (TgRSIZE uiTest_Start = 0, uiTest_Start_Step = 0; uiTest_Start_Step <= uiMaxStep_nuiTest; ++uiTest_Start_Step)
        {
            TgCHAR_U8_CPC   mbzTest_Start = tgUSZ_Query_At( s_ambzTest[uiIndex], nbyMaxTest + 1, uiTest_Start );

            for (TgRSIZE uiTest_End = uiTest_Start, uiTest_End_Step = uiTest_Start_Step; uiTest_End_Step <= uiMaxStep_nuiTest; ++uiTest_End_Step)
            {
                TgCHAR_U8_CPC   mbzTest_End = tgUSZ_Query_At( s_ambzTest[uiIndex], nbyMaxTest + 1, uiTest_End );
                TgRSIZE_C                           nbyTest = mbzTest_End >= mbzTest_Start ? (TgRSIZE)(mbzTest_End - mbzTest_Start) : 0;

                for (TgRSIZE uiInsert_Index = 0, uiInsert_Index_Step = 0; uiInsert_Index_Step <= uiMaxStep_nuiTest; ++uiInsert_Index_Step)
                {
                    STg2_UT_ST__ST                      tgKB;
                    TgCHAR_U8_CP                        mbzKB, mbzKB_Start;
                    TgRSIZE                             nbyKB_Start;

                    /* Insert with pointer to self */
                    tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[uiIndex] );
                    tgCM_UT_ST__ST__SF_Insert( &tgKB, uiInsert_Index, &tgKB, uiTest_Start, uiTest_End - uiTest_Start );

                    mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );
                    mbzKB_Start = tgUSZ_Query_At( mbzKB, tgKB.m_nbyBuffer + 1, uiInsert_Index );
                    nbyKB_Start = (TgRSIZE)(mbzKB_Start - mbzKB);

                    Test__Expect_EQ(0, memcmp( mbzKB, s_ambzTest[uiIndex], nbyKB_Start ));
                    Test__Expect_EQ(0, memcmp( mbzKB_Start, mbzTest_Start, nbyTest ) );
                    Test__Expect_EQ(0, memcmp( mbzKB_Start + nbyTest, s_ambzTest[uiIndex] + nbyKB_Start, nbyMaxTest - nbyKB_Start ));
                    Test__Expect_EQ(tgKB.m_nbyBuffer, nbyMaxTest + nbyTest);
                    Test__Expect_EQ(nbyMaxTest + nbyTest, tgCM_UT_ST__ST__Length_U08( &tgKB ));
                    Test__Expect_EQ(nbyMaxTest + nbyTest, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

                    tgCM_UT_ST__ST__Free( &tgKB );

                    TgMACRO_STEP_INDEX( uiInsert_Index, nuiMaxTest, uiMaxStep_nuiTest );
                };

                for (TgRSIZE uiIndex2 = 0; uiIndex2 < TgARRAY_COUNT(s_ambzTest); ++uiIndex2)
                {
                    for (TgRSIZE uiInsert_Index = 0, uiInsert_Index_Step = 0; uiInsert_Index_Step <= uiMaxStep_nuiTest; ++uiInsert_Index_Step)
                    {
                        TgRSIZE_C                           nbyMaxTest2 = s_asTest_Length[uiIndex2].m_nbyCharacters;
                        TgRSIZE_C                           nuiMaxTest2 = s_asTest_Length[uiIndex2].m_nuiCharacters;
                        TgRSIZE_C       uiMaxStep_nuiTest2 = tgCM_MIN_UMAX( nuiMaxTest2, 10 );

                        STg2_UT_ST__ST                      tgKB, tgKC;
                        TgCHAR_U8_CP                        mbzKB, mbzKB_Start;
                        TgRSIZE                             nbyKB_Start;

                        /* Insert with pointer to non-self, with empty string */
                        tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[uiIndex2] );
                        tgCM_UT_ST__ST__SZ_Init( &tgKC, s_ambzTest[uiIndex] );
                        tgCM_UT_ST__ST__SF_Insert( &tgKB, uiInsert_Index, &tgKC, uiTest_Start, uiTest_End - uiTest_Start );

                        mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );
                        mbzKB_Start = tgUSZ_Query_At( mbzKB, tgKB.m_nbyBuffer + 1, uiInsert_Index );
                        nbyKB_Start = (TgRSIZE)(mbzKB_Start - mbzKB);

                        Test__Expect_EQ(0, memcmp( mbzKB, s_ambzTest[uiIndex2], nbyKB_Start ));
                        Test__Expect_EQ(0, memcmp( mbzKB_Start, mbzTest_Start, nbyTest ) );
                        Test__Expect_EQ(0, memcmp( mbzKB_Start + nbyTest, s_ambzTest[uiIndex2] + nbyKB_Start, nbyMaxTest2 - nbyKB_Start ));
                        Test__Expect_EQ(tgKB.m_nbyBuffer, nbyMaxTest2 + nbyTest);
                        Test__Expect_EQ(tgKB.m_nbyBuffer, tgCM_UT_ST__ST__Length_U08( &tgKB ));
                        Test__Expect_EQ(tgKB.m_nbyBuffer, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

                        tgCM_UT_ST__ST__Free( &tgKC );
                        tgCM_UT_ST__ST__Free( &tgKB );

                        TgMACRO_STEP_INDEX( uiInsert_Index, nuiMaxTest2, uiMaxStep_nuiTest2 );
                    };
                };

                TgMACRO_STEP_INDEX( uiTest_End, nuiMaxTest, uiMaxStep_nuiTest );
            };

            TgMACRO_STEP_INDEX( uiTest_Start, nuiMaxTest, uiMaxStep_nuiTest );
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__SZ_Replace -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SZ_Replace )
{
    for (TgRSIZE uiIndex = 0; uiIndex < TgARRAY_COUNT(s_ambzTest); ++uiIndex)
    {
        TgRSIZE_C                           nbyMaxTest = s_asTest_Length[uiIndex].m_nbyCharacters;
        TgRSIZE_C                           nuiMaxTest = s_asTest_Length[uiIndex].m_nuiCharacters;
        TgRSIZE_C       uiMaxStep_nuiTest = tgCM_MIN_UMAX( nuiMaxTest, 10 );

        for (TgRSIZE uiTest_Start = 0, uiTest_Start_Step = 0; uiTest_Start_Step <= uiMaxStep_nuiTest; ++uiTest_Start_Step)
        {
            TgCHAR_U8_CPC   mbzTest_Start = tgUSZ_Query_At( s_ambzTest[uiIndex], nbyMaxTest + 1, uiTest_Start );
            TgRSIZE_C                           nbyTest = nbyMaxTest - (TgRSIZE)(mbzTest_Start - s_ambzTest[uiIndex]);

            TgCHAR_U8_CP                        mbzDest_Start, mbzDest_End;
            TgRSIZE                             nbyDest_Start, nbyDest_End;

            for (TgRSIZE uiDest_Start = 0, uiDest_Start_Step = 0; uiDest_Start_Step <= uiMaxStep_nuiTest; ++uiDest_Start_Step)
            {
                for (TgRSIZE uiDest_End = uiDest_Start, uiDest_End_Step = uiDest_Start_Step; uiDest_End_Step <= uiMaxStep_nuiTest; ++uiDest_End_Step)
                {
                    STg2_UT_ST__ST                      tgKB;
                    TgCHAR_U8_CP                        mbzKB, mbzKB_Start;

                    /* Assign with pointer to self */
                    tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[uiIndex] );
                    mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );
                    mbzKB_Start = tgUSZ_Query_At( mbzKB, tgKB.m_nbyBuffer + 1, uiTest_Start );

                    tgCM_UT_ST__ST__SZ_Replace( &tgKB, uiDest_Start, uiDest_End, mbzKB_Start );
                    mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );
                    mbzKB_Start = tgUSZ_Query_At( mbzKB, tgKB.m_nbyBuffer + 1, uiDest_Start );

                    mbzDest_Start = tgUSZ_Query_At( s_ambzTest[uiIndex], nbyMaxTest + 1, uiDest_Start );
                    nbyDest_Start = (TgRSIZE)(mbzDest_Start - s_ambzTest[uiIndex]);
                    mbzDest_End = tgUSZ_Query_At( s_ambzTest[uiIndex], nbyMaxTest + 1, uiDest_End );
                    nbyDest_End = (TgRSIZE)(mbzDest_End - s_ambzTest[uiIndex]);

                    Test__Expect_EQ(0, memcmp( mbzKB, s_ambzTest[uiIndex], nbyDest_Start ));
                    Test__Expect_EQ(0, memcmp( mbzKB_Start, mbzTest_Start, nbyTest ) );
                    Test__Expect_EQ(0, memcmp( mbzKB_Start + nbyTest, mbzDest_End, nbyMaxTest - nbyDest_End ));
                    Test__Expect_EQ(tgKB.m_nbyBuffer, nbyDest_Start + nbyTest + nbyMaxTest - nbyDest_End);
                    Test__Expect_EQ(tgKB.m_nbyBuffer, tgCM_UT_ST__ST__Length_U08( &tgKB ));
                    Test__Expect_EQ(tgKB.m_nbyBuffer, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

                    tgCM_UT_ST__ST__Free( &tgKB );

                    TgMACRO_STEP_INDEX( uiDest_End, nuiMaxTest, uiMaxStep_nuiTest );
                };

                TgMACRO_STEP_INDEX( uiDest_Start, nuiMaxTest, uiMaxStep_nuiTest );
            };

            for (TgRSIZE uiIndex2 = 0; uiIndex2 < TgARRAY_COUNT(s_ambzTest); ++uiIndex2)
            {
                TgRSIZE_C                           nbyMaxTest2 = s_asTest_Length[uiIndex2].m_nbyCharacters;
                TgRSIZE_C                           nuiMaxTest2 = s_asTest_Length[uiIndex2].m_nuiCharacters;
                TgRSIZE_C       uiMaxStep_nuiTest2 = tgCM_MIN_UMAX( nuiMaxTest2, 10 );

                for (TgRSIZE uiDest_Start = 0, uiDest_Start_Step = 0; uiDest_Start_Step <= uiMaxStep_nuiTest; ++uiDest_Start_Step)
                {
                    for (TgRSIZE uiDest_End = uiDest_Start, uiDest_End_Step = uiDest_Start_Step; uiDest_End_Step <= uiMaxStep_nuiTest; ++uiDest_End_Step)
                    {
                        STg2_UT_ST__ST                      tgKB;
                        TgCHAR_U8_CP                        mbzKB, mbzKB_Start;

                        /* Replace with pointer to non-self */
                        tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[uiIndex2] );

                        tgCM_UT_ST__ST__SZ_Replace( &tgKB, uiDest_Start, uiDest_End, mbzTest_Start );
                        mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );
                        mbzKB_Start = tgUSZ_Query_At( mbzKB, tgKB.m_nbyBuffer + 1, uiDest_Start );

                        mbzDest_Start = tgUSZ_Query_At( s_ambzTest[uiIndex2], nbyMaxTest2 + 1, uiDest_Start );
                        nbyDest_Start = (TgRSIZE)(mbzDest_Start - s_ambzTest[uiIndex2]);
                        mbzDest_End = tgUSZ_Query_At( s_ambzTest[uiIndex2], nbyMaxTest2 + 1, uiDest_End );
                        nbyDest_End = (TgRSIZE)(mbzDest_End - s_ambzTest[uiIndex2]);

                        Test__Expect_EQ(0, memcmp( mbzKB, s_ambzTest[uiIndex2], nbyDest_Start ));
                        Test__Expect_EQ(0, memcmp( mbzKB_Start, mbzTest_Start, nbyTest ) );
                        Test__Expect_EQ(0, memcmp( mbzKB_Start + nbyTest, mbzDest_End, nbyMaxTest2 - nbyDest_End ));
                        Test__Expect_EQ(tgKB.m_nbyBuffer, nbyDest_Start + nbyTest + nbyMaxTest2 - nbyDest_End);
                        Test__Expect_EQ(tgKB.m_nbyBuffer, tgCM_UT_ST__ST__Length_U08( &tgKB ));
                        Test__Expect_EQ(tgKB.m_nbyBuffer, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

                        tgCM_UT_ST__ST__Free( &tgKB );

                        TgMACRO_STEP_INDEX( uiDest_End, nuiMaxTest2, uiMaxStep_nuiTest2 );
                    };

                    TgMACRO_STEP_INDEX( uiDest_Start, nuiMaxTest2, uiMaxStep_nuiTest2 );
                };
            };

            TgMACRO_STEP_INDEX( uiTest_Start, nuiMaxTest, uiMaxStep_nuiTest );
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__SN_Replace -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SN_Replace )
{
    for (TgRSIZE uiIndex = 0; uiIndex < TgARRAY_COUNT(s_ambzTest); ++uiIndex)
    {
        TgRSIZE_C                           nbyMaxTest = s_asTest_Length[uiIndex].m_nbyCharacters;
        TgRSIZE_C       uiMaxStep_nbyTest = tgCM_MIN_UMAX( nbyMaxTest, 10 );
        TgRSIZE_C                           nuiMaxTest = s_asTest_Length[uiIndex].m_nuiCharacters;
        TgRSIZE_C       uiMaxStep_nuiTest = tgCM_MIN_UMAX( nuiMaxTest, 10 );

        /* Replace with pointer to self */
        for (TgRSIZE nbySize = 0, nbySize_Step = 0; nbySize_Step <= uiMaxStep_nbyTest; ++nbySize_Step)
        {
            for (TgRSIZE uiTest_Start = 0, uiTest_Start_Step = 0; uiTest_Start_Step <= uiMaxStep_nuiTest; ++uiTest_Start_Step)
            {
                TgCHAR_U8_CPC   mbzTest_Start = tgUSZ_Query_At( s_ambzTest[uiIndex], nbyMaxTest + 1, uiTest_Start );
                TgCHAR_U8_CPC   mbzTest_End = tgUSZ_Query_End( mbzTest_Start, nbySize, KTgMAX_RSIZE );
                TgRSIZE_C                           nbyTest = (TgRSIZE)(mbzTest_End - mbzTest_Start);

                TgCHAR_U8_CP                        mbzDest_Start, mbzDest_End;
                TgRSIZE                             nbyDest_Start, nbyDest_End;

                for (TgRSIZE uiDest_Start = 0, uiDest_Start_Step = 0; uiDest_Start_Step <= uiMaxStep_nuiTest; ++uiDest_Start_Step)
                {
                    for (TgRSIZE uiDest_End = uiDest_Start, uiDest_End_Step = uiDest_Start_Step; uiDest_End_Step <= uiMaxStep_nuiTest; ++uiDest_End_Step)
                    {
                        STg2_UT_ST__ST                      tgKB;
                        TgCHAR_U8_CP                        mbzKB, mbzKB_Start;

                        /* Assign with pointer to self */
                        tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[uiIndex] );
                        mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );
                        mbzKB_Start = tgUSZ_Query_At( mbzKB, tgKB.m_nbyBuffer + 1, uiTest_Start );

                        tgCM_UT_ST__ST__SN_Replace( &tgKB, uiDest_Start, uiDest_End, mbzKB_Start, nbySize );
                        mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );
                        mbzKB_Start = tgUSZ_Query_At( mbzKB, tgKB.m_nbyBuffer + 1, uiDest_Start );

                        mbzDest_Start = tgUSZ_Query_At( s_ambzTest[uiIndex], nbyMaxTest + 1, uiDest_Start );
                        nbyDest_Start = (TgRSIZE)(mbzDest_Start - s_ambzTest[uiIndex]);
                        mbzDest_End = tgUSZ_Query_At( s_ambzTest[uiIndex], nbyMaxTest + 1, uiDest_End );
                        nbyDest_End = (TgRSIZE)(mbzDest_End - s_ambzTest[uiIndex]);

                        Test__Expect_EQ(0, memcmp( mbzKB, s_ambzTest[uiIndex], nbyDest_Start ));
                        Test__Expect_EQ(0, memcmp( mbzKB_Start, mbzTest_Start, nbyTest ) );
                        Test__Expect_EQ(0, memcmp( mbzKB_Start + nbyTest, mbzDest_End, nbyMaxTest - nbyDest_End ));
                        Test__Expect_EQ(tgKB.m_nbyBuffer, nbyDest_Start + nbyTest + (nbyMaxTest - nbyDest_End));
                        Test__Expect_EQ(tgKB.m_nbyBuffer, tgCM_UT_ST__ST__Length_U08( &tgKB ));
                        Test__Expect_EQ(tgKB.m_nbyBuffer, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

                        tgCM_UT_ST__ST__Free( &tgKB );

                        TgMACRO_STEP_INDEX( uiDest_End, nuiMaxTest, uiMaxStep_nuiTest );
                    };

                    TgMACRO_STEP_INDEX( uiDest_Start, nuiMaxTest, uiMaxStep_nuiTest );
                };

                for (TgRSIZE uiIndex2 = 0; uiIndex2 < TgARRAY_COUNT(s_ambzTest); ++uiIndex2)
                {
                    TgRSIZE_C                           nbyMaxTest2 = s_asTest_Length[uiIndex2].m_nbyCharacters;
                    TgRSIZE_C                           nuiMaxTest2 = s_asTest_Length[uiIndex2].m_nuiCharacters;
                    TgRSIZE_C       uiMaxStep_nuiTest2 = tgCM_MIN_UMAX( nuiMaxTest2, 10 );

                    for (TgRSIZE uiDest_Start = 0, uiDest_Start_Step = 0; uiDest_Start_Step <= uiMaxStep_nuiTest; ++uiDest_Start_Step)
                    {
                        for (TgRSIZE uiDest_End = uiDest_Start, uiDest_End_Step = uiDest_Start_Step; uiDest_End_Step <= uiMaxStep_nuiTest; ++uiDest_End_Step)
                        {
                            STg2_UT_ST__ST                      tgKB;
                            TgCHAR_U8_CP                        mbzKB, mbzKB_Start;

                            /* Replace with pointer to non-self */
                            tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[uiIndex2] );

                            tgCM_UT_ST__ST__SN_Replace( &tgKB, uiDest_Start, uiDest_End, mbzTest_Start, nbySize );
                            mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );
                            mbzKB_Start = tgUSZ_Query_At( mbzKB, tgKB.m_nbyBuffer + 1, uiDest_Start );

                            mbzDest_Start = tgUSZ_Query_At( s_ambzTest[uiIndex2], nbyMaxTest2 + 1, uiDest_Start );
                            nbyDest_Start = (TgRSIZE)(mbzDest_Start - s_ambzTest[uiIndex2]);
                            mbzDest_End = tgUSZ_Query_At( s_ambzTest[uiIndex2], nbyMaxTest2 + 1, uiDest_End );
                            nbyDest_End = (TgRSIZE)(mbzDest_End - s_ambzTest[uiIndex2]);

                            Test__Expect_EQ(0, memcmp( mbzKB, s_ambzTest[uiIndex2], nbyDest_Start ));
                            Test__Expect_EQ(0, memcmp( mbzKB_Start, mbzTest_Start, nbyTest ) );
                            Test__Expect_EQ(0, memcmp( mbzKB_Start + nbyTest, mbzDest_End, nbyMaxTest2 - nbyDest_End ));
                            Test__Expect_EQ(tgKB.m_nbyBuffer, nbyDest_Start + nbyTest + (nbyMaxTest2 - nbyDest_End));
                            Test__Expect_EQ(tgKB.m_nbyBuffer, tgCM_UT_ST__ST__Length_U08( &tgKB ));
                            Test__Expect_EQ(tgKB.m_nbyBuffer, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

                            tgCM_UT_ST__ST__Free( &tgKB );

                            TgMACRO_STEP_INDEX( uiDest_End, nuiMaxTest2, uiMaxStep_nuiTest2 );
                        };

                        TgMACRO_STEP_INDEX( uiDest_Start, nuiMaxTest2, uiMaxStep_nuiTest2 );
                    };
                };

                TgMACRO_STEP_INDEX( uiTest_Start, nuiMaxTest, uiMaxStep_nuiTest );
            };

            TgMACRO_STEP_INDEX( nbySize, nbyMaxTest, uiMaxStep_nbyTest );
        };
    };


    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__PT_Replace -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__PT_Replace )
{
    for (TgRSIZE uiIndex = 0; uiIndex < TgARRAY_COUNT(s_ambzTest); ++uiIndex)
    {
        TgRSIZE_C                           nbyMaxTest = s_asTest_Length[uiIndex].m_nbyCharacters;
        TgRSIZE_C                           nuiMaxTest = s_asTest_Length[uiIndex].m_nuiCharacters;
        TgRSIZE_C       uiMaxStep_nuiTest = tgCM_MIN_UMAX( nuiMaxTest, 10 );

        for (TgRSIZE uiTest_Start = 0, uiTest_Start_Step = 0; uiTest_Start_Step <= uiMaxStep_nuiTest; ++uiTest_Start_Step)
        {
            TgCHAR_U8_CPC   mbzTest_Start = tgUSZ_Query_At( s_ambzTest[uiIndex], nbyMaxTest + 1, uiTest_Start );

            for (TgRSIZE uiTest_End = uiTest_Start, uiTest_End_Step = uiTest_Start_Step; uiTest_End_Step <= uiMaxStep_nuiTest; ++uiTest_End_Step)
            {
                TgCHAR_U8_CPC   mbzTest_End = tgUSZ_Query_At( s_ambzTest[uiIndex], nbyMaxTest + 1, uiTest_End );
                TgRSIZE_C                           nbyTest = mbzTest_End >= mbzTest_Start ? (TgRSIZE)(mbzTest_End - mbzTest_Start) : 0;

                TgCHAR_U8_CP                        mbzDest_Start, mbzDest_End;
                TgRSIZE                             nbyDest_Start, nbyDest_End;

                for (TgRSIZE uiDest_Start = 0, uiDest_Start_Step = 0; uiDest_Start_Step <= uiMaxStep_nuiTest; ++uiDest_Start_Step)
                {
                    for (TgRSIZE uiDest_End = uiDest_Start, uiDest_End_Step = uiDest_Start_Step; uiDest_End_Step <= uiMaxStep_nuiTest; ++uiDest_End_Step)
                    {
                        STg2_UT_ST__ST                      tgKB;
                        TgCHAR_U8_CP                        mbzKB, mbzKB_Start;

                        /* Assign with pointer to self */
                        tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[uiIndex] );
                        mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );
                        mbzDest_Start = tgUSZ_Query_At( mbzKB, nbyMaxTest + 1, uiTest_Start );
                        mbzDest_End = tgUSZ_Query_At( mbzKB, nbyMaxTest + 1, uiTest_End );

                        tgCM_UT_ST__ST__PT_Replace( &tgKB, uiDest_Start, uiDest_End, mbzDest_Start, mbzDest_End );
                        mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );
                        mbzKB_Start = tgUSZ_Query_At( mbzKB, tgKB.m_nbyBuffer + 1, uiDest_Start );

                        mbzDest_Start = tgUSZ_Query_At( s_ambzTest[uiIndex], nbyMaxTest + 1, uiDest_Start );
                        nbyDest_Start = (TgRSIZE)(mbzDest_Start - s_ambzTest[uiIndex]);
                        mbzDest_End = tgUSZ_Query_At( s_ambzTest[uiIndex], nbyMaxTest + 1, uiDest_End );
                        nbyDest_End = (TgRSIZE)(mbzDest_End - s_ambzTest[uiIndex]);

                        Test__Expect_EQ(0, memcmp( mbzKB, s_ambzTest[uiIndex], nbyDest_Start ));
                        Test__Expect_EQ(0, memcmp( mbzKB_Start, mbzTest_Start, nbyTest ));
                        Test__Expect_EQ(0, memcmp( mbzKB_Start + nbyTest, mbzDest_End, nbyMaxTest - nbyDest_End ));
                        Test__Expect_EQ(tgKB.m_nbyBuffer, nbyDest_Start + nbyTest + (nbyMaxTest - nbyDest_End));
                        Test__Expect_EQ(tgKB.m_nbyBuffer, tgCM_UT_ST__ST__Length_U08( &tgKB ));
                        Test__Expect_EQ(tgKB.m_nbyBuffer, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

                        tgCM_UT_ST__ST__Free( &tgKB );

                        TgMACRO_STEP_INDEX( uiDest_End, nuiMaxTest, uiMaxStep_nuiTest );
                    };

                    TgMACRO_STEP_INDEX( uiDest_Start, nuiMaxTest, uiMaxStep_nuiTest );
                };


                for (TgRSIZE uiIndex2 = 0; uiIndex2 < TgARRAY_COUNT(s_ambzTest); ++uiIndex2)
                {
                    TgRSIZE_C                           nbyMaxTest2 = s_asTest_Length[uiIndex2].m_nbyCharacters;
                    TgRSIZE_C                           nuiMaxTest2 = s_asTest_Length[uiIndex2].m_nuiCharacters;
                    TgRSIZE_C       uiMaxStep_nuiTest2 = tgCM_MIN_UMAX( nuiMaxTest2, 10 );

                    for (TgRSIZE uiDest_Start = 0, uiDest_Start_Step = 0; uiDest_Start_Step <= uiMaxStep_nuiTest; ++uiDest_Start_Step)
                    {
                        for (TgRSIZE uiDest_End = uiDest_Start, uiDest_End_Step = uiDest_Start_Step; uiDest_End_Step <= uiMaxStep_nuiTest; ++uiDest_End_Step)
                        {
                            STg2_UT_ST__ST                      tgKB;
                            TgCHAR_U8_CP                        mbzKB, mbzKB_Start;

                            /* Replace with pointer to non-self */
                            tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[uiIndex2] );

                            tgCM_UT_ST__ST__PT_Replace( &tgKB, uiDest_Start, uiDest_End, mbzTest_Start, mbzTest_End );
                            mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );
                            mbzKB_Start = tgUSZ_Query_At( mbzKB, tgKB.m_nbyBuffer + 1, uiDest_Start );

                            mbzDest_Start = tgUSZ_Query_At( s_ambzTest[uiIndex2], nbyMaxTest2 + 1, uiDest_Start );
                            nbyDest_Start = (TgRSIZE)(mbzDest_Start - s_ambzTest[uiIndex2]);
                            mbzDest_End = tgUSZ_Query_At( s_ambzTest[uiIndex2], nbyMaxTest2 + 1, uiDest_End );
                            nbyDest_End = (TgRSIZE)(mbzDest_End - s_ambzTest[uiIndex2]);

                            Test__Expect_EQ(0, memcmp( mbzKB, s_ambzTest[uiIndex2], nbyDest_Start ));
                            Test__Expect_EQ(0, memcmp( mbzKB_Start, mbzTest_Start, nbyTest ) );
                            Test__Expect_EQ(0, memcmp( mbzKB_Start + nbyTest, mbzDest_End, nbyMaxTest2 - nbyDest_End ));
                            Test__Expect_EQ(tgKB.m_nbyBuffer, nbyDest_Start + nbyTest + (nbyMaxTest2 - nbyDest_End));
                            Test__Expect_EQ(tgKB.m_nbyBuffer, tgCM_UT_ST__ST__Length_U08( &tgKB ));
                            Test__Expect_EQ(tgKB.m_nbyBuffer, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

                            tgCM_UT_ST__ST__Free( &tgKB );

                            TgMACRO_STEP_INDEX( uiDest_End, nuiMaxTest2, uiMaxStep_nuiTest2 );
                        };

                        TgMACRO_STEP_INDEX( uiDest_Start, nuiMaxTest2, uiMaxStep_nuiTest2 );
                    };
                };

                TgMACRO_STEP_INDEX( uiTest_End, nuiMaxTest, uiMaxStep_nuiTest );
            };

            TgMACRO_STEP_INDEX( uiTest_Start, nuiMaxTest, uiMaxStep_nuiTest );
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__ST_Replace -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__ST_Replace )
{
    for (TgRSIZE uiIndex = 0; uiIndex < TgARRAY_COUNT(s_ambzTest); ++uiIndex)
    {
        TgRSIZE_C                           nbyMaxTest = s_asTest_Length[uiIndex].m_nbyCharacters;
        TgRSIZE_C                           nuiMaxTest = s_asTest_Length[uiIndex].m_nuiCharacters;
        TgRSIZE_C       uiMaxStep_nuiTest = tgCM_MIN_UMAX( nuiMaxTest, 10 );
        TgCHAR_U8_CPC   mbzTest_Start = s_ambzTest[uiIndex];
        TgRSIZE_C                           nbyTest = s_asTest_Length[uiIndex].m_nbyCharacters;

        TgCHAR_U8_CP                        mbzDest_Start, mbzDest_End;
        TgRSIZE                             nbyDest_Start, nbyDest_End;

        /* Replace with pointer to self */
        for (TgRSIZE uiDest_Start = 0, uiDest_Start_Step = 0; uiDest_Start_Step <= uiMaxStep_nuiTest; ++uiDest_Start_Step)
        {
            for (TgRSIZE uiDest_End = uiDest_Start, uiDest_End_Step = uiDest_Start_Step; uiDest_End_Step <= uiMaxStep_nuiTest; ++uiDest_End_Step)
            {
                STg2_UT_ST__ST                      tgKB;
                TgCHAR_U8_CP                        mbzKB, mbzKB_Start;

                tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[uiIndex] );

                tgCM_UT_ST__ST__ST_Replace( &tgKB, uiDest_Start, uiDest_End, &tgKB );
                mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );
                mbzKB_Start = tgUSZ_Query_At( mbzKB, tgKB.m_nbyBuffer + 1, uiDest_Start );

                mbzDest_Start = tgUSZ_Query_At( s_ambzTest[uiIndex], nbyMaxTest + 1, uiDest_Start );
                nbyDest_Start = (TgRSIZE)(mbzDest_Start - s_ambzTest[uiIndex]);
                mbzDest_End = tgUSZ_Query_At( s_ambzTest[uiIndex], nbyMaxTest + 1, uiDest_End );
                nbyDest_End = (TgRSIZE)(mbzDest_End - s_ambzTest[uiIndex]);

                Test__Expect_EQ(0, memcmp( mbzKB, s_ambzTest[uiIndex], nbyDest_Start ));
                Test__Expect_EQ(0, memcmp( mbzKB_Start, mbzTest_Start, nbyTest ));
                Test__Expect_EQ(0, memcmp( mbzKB_Start + nbyTest, mbzDest_End, nbyMaxTest - nbyDest_End ));
                Test__Expect_EQ(tgKB.m_nbyBuffer, nbyDest_Start + nbyTest + (nbyMaxTest - nbyDest_End));
                Test__Expect_EQ(tgKB.m_nbyBuffer, tgCM_UT_ST__ST__Length_U08( &tgKB ));
                Test__Expect_EQ(tgKB.m_nbyBuffer, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

                tgCM_UT_ST__ST__Free( &tgKB );

                TgMACRO_STEP_INDEX( uiDest_End, nuiMaxTest, uiMaxStep_nuiTest );
            };

            TgMACRO_STEP_INDEX( uiDest_Start, nuiMaxTest, uiMaxStep_nuiTest );
        };

        for (TgRSIZE uiIndex2 = 0; uiIndex2 < TgARRAY_COUNT(s_ambzTest); ++uiIndex2)
        {
            TgRSIZE_C                           nbyMaxTest2 = s_asTest_Length[uiIndex2].m_nbyCharacters;
            TgRSIZE_C                           nuiMaxTest2 = s_asTest_Length[uiIndex2].m_nuiCharacters;
            TgRSIZE_C       uiMaxStep_nuiTest2 = tgCM_MIN_UMAX( nuiMaxTest2, 10 );

            for (TgRSIZE uiDest_Start = 0, uiDest_Start_Step = 0; uiDest_Start_Step <= uiMaxStep_nuiTest; ++uiDest_Start_Step)
            {
                for (TgRSIZE uiDest_End = uiDest_Start, uiDest_End_Step = uiDest_Start_Step; uiDest_End_Step <= uiMaxStep_nuiTest; ++uiDest_End_Step)
                {
                    STg2_UT_ST__ST                      tgKB, tgKC;
                    TgCHAR_U8_CP                        mbzKB, mbzKB_Start;

                    tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[uiIndex2] );
                    tgCM_UT_ST__ST__SZ_Init( &tgKC, s_ambzTest[uiIndex] );

                    tgCM_UT_ST__ST__ST_Replace( &tgKB, uiDest_Start, uiDest_End, &tgKC );
                    mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );
                    mbzKB_Start = tgUSZ_Query_At( mbzKB, tgKB.m_nbyBuffer + 1, uiDest_Start );

                    mbzDest_Start = tgUSZ_Query_At( s_ambzTest[uiIndex2], nbyMaxTest2 + 1, uiDest_Start );
                    nbyDest_Start = (TgRSIZE)(mbzDest_Start - s_ambzTest[uiIndex2]);
                    mbzDest_End = tgUSZ_Query_At( s_ambzTest[uiIndex2], nbyMaxTest2 + 1, uiDest_End );
                    nbyDest_End = (TgRSIZE)(mbzDest_End - s_ambzTest[uiIndex2]);

                    Test__Expect_EQ(0, memcmp( mbzKB, s_ambzTest[uiIndex2], nbyDest_Start ));
                    Test__Expect_EQ(0, memcmp( mbzKB_Start, mbzTest_Start, nbyTest ) );
                    Test__Expect_EQ(0, memcmp( mbzKB_Start + nbyTest, mbzDest_End, nbyMaxTest2 - nbyDest_End ));
                    Test__Expect_EQ(tgKB.m_nbyBuffer, nbyDest_Start + nbyTest + (nbyMaxTest2 - nbyDest_End));
                    Test__Expect_EQ(tgKB.m_nbyBuffer, tgCM_UT_ST__ST__Length_U08( &tgKB ));
                    Test__Expect_EQ(tgKB.m_nbyBuffer, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

                    tgCM_UT_ST__ST__Free( &tgKC );
                    tgCM_UT_ST__ST__Free( &tgKB );

                    TgMACRO_STEP_INDEX( uiDest_End, nuiMaxTest2, uiMaxStep_nuiTest2 );
                };

                TgMACRO_STEP_INDEX( uiDest_Start, nuiMaxTest2, uiMaxStep_nuiTest2 );
            };
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__SO_Replace -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SO_Replace )
{
    for (TgRSIZE uiIndex = 0; uiIndex < TgARRAY_COUNT(s_ambzTest); ++uiIndex)
    {
        TgRSIZE_C                           nbyMaxTest = s_asTest_Length[uiIndex].m_nbyCharacters;
        TgRSIZE_C                           nuiMaxTest = s_asTest_Length[uiIndex].m_nuiCharacters;
        TgRSIZE_C       uiMaxStep_nuiTest = tgCM_MIN_UMAX( nuiMaxTest, 10 );

        for (TgRSIZE uiTest_Start = 0, uiTest_Start_Step = 0; uiTest_Start_Step <= uiMaxStep_nuiTest; ++uiTest_Start_Step)
        {
            TgCHAR_U8_CPC   mbzTest_Start = tgUSZ_Query_At( s_ambzTest[uiIndex], nbyMaxTest + 1, uiTest_Start );
            TgRSIZE_C                           nbyTest = nbyMaxTest - (TgRSIZE)(mbzTest_Start - s_ambzTest[uiIndex]);

            TgCHAR_U8_CP                        mbzDest_Start, mbzDest_End;
            TgRSIZE                             nbyDest_Start, nbyDest_End;

            for (TgRSIZE uiDest_Start = 0, uiDest_Start_Step = 0; uiDest_Start_Step <= uiMaxStep_nuiTest; ++uiDest_Start_Step)
            {
                for (TgRSIZE uiDest_End = uiDest_Start, uiDest_End_Step = uiDest_Start_Step; uiDest_End_Step <= uiMaxStep_nuiTest; ++uiDest_End_Step)
                {
                    STg2_UT_ST__ST                      tgKB;
                    TgCHAR_U8_CP                        mbzKB, mbzKB_Start;

                    /* Assign with pointer to self */
                    tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[uiIndex] );

                    tgCM_UT_ST__ST__SO_Replace( &tgKB, uiDest_Start, uiDest_End, &tgKB, uiTest_Start );
                    mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );
                    mbzKB_Start = tgUSZ_Query_At( mbzKB, tgKB.m_nbyBuffer + 1, uiDest_Start );

                    mbzDest_Start = tgUSZ_Query_At( s_ambzTest[uiIndex], nbyMaxTest + 1, uiDest_Start );
                    nbyDest_Start = (TgRSIZE)(mbzDest_Start - s_ambzTest[uiIndex]);
                    mbzDest_End = tgUSZ_Query_At( s_ambzTest[uiIndex], nbyMaxTest + 1, uiDest_End );
                    nbyDest_End = (TgRSIZE)(mbzDest_End - s_ambzTest[uiIndex]);

                    Test__Expect_EQ(0, memcmp( mbzKB, s_ambzTest[uiIndex], nbyDest_Start ));
                    Test__Expect_EQ(0, memcmp( mbzKB_Start, mbzTest_Start, nbyTest ));
                    Test__Expect_EQ(0, memcmp( mbzKB_Start + nbyTest, mbzDest_End, nbyMaxTest - nbyDest_End ));
                    Test__Expect_EQ(tgKB.m_nbyBuffer, nbyDest_Start + nbyTest + (nbyMaxTest - nbyDest_End));
                    Test__Expect_EQ(tgKB.m_nbyBuffer, tgCM_UT_ST__ST__Length_U08( &tgKB ));
                    Test__Expect_EQ(tgKB.m_nbyBuffer, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

                    tgCM_UT_ST__ST__Free( &tgKB );

                    TgMACRO_STEP_INDEX( uiDest_End, nuiMaxTest, uiMaxStep_nuiTest );
                };

                TgMACRO_STEP_INDEX( uiDest_Start, nuiMaxTest, uiMaxStep_nuiTest );
            };


            for (TgRSIZE uiIndex2 = 0; uiIndex2 < TgARRAY_COUNT(s_ambzTest); ++uiIndex2)
            {
                TgRSIZE_C                           nbyMaxTest2 = s_asTest_Length[uiIndex2].m_nbyCharacters;
                TgRSIZE_C                           nuiMaxTest2 = s_asTest_Length[uiIndex2].m_nuiCharacters;
                TgRSIZE_C       uiMaxStep_nuiTest2 = tgCM_MIN_UMAX( nuiMaxTest2, 10 );

                for (TgRSIZE uiDest_Start = 0, uiDest_Start_Step = 0; uiDest_Start_Step <= uiMaxStep_nuiTest; ++uiDest_Start_Step)
                {
                    for (TgRSIZE uiDest_End = uiDest_Start, uiDest_End_Step = uiDest_Start_Step; uiDest_End_Step <= uiMaxStep_nuiTest; ++uiDest_End_Step)
                    {
                        STg2_UT_ST__ST                      tgKB, tgKC;
                        TgCHAR_U8_CP                        mbzKB, mbzKB_Start;

                        tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[uiIndex2] );
                        tgCM_UT_ST__ST__SZ_Init( &tgKC, s_ambzTest[uiIndex] );

                        tgCM_UT_ST__ST__SO_Replace( &tgKB, uiDest_Start, uiDest_End, &tgKC, uiTest_Start );
                        mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );
                        mbzKB_Start = tgUSZ_Query_At( mbzKB, tgKB.m_nbyBuffer + 1, uiDest_Start );

                        mbzDest_Start = tgUSZ_Query_At( s_ambzTest[uiIndex2], nbyMaxTest2 + 1, uiDest_Start );
                        nbyDest_Start = (TgRSIZE)(mbzDest_Start - s_ambzTest[uiIndex2]);
                        mbzDest_End = tgUSZ_Query_At( s_ambzTest[uiIndex2], nbyMaxTest2 + 1, uiDest_End );
                        nbyDest_End = (TgRSIZE)(mbzDest_End - s_ambzTest[uiIndex2]);

                        Test__Expect_EQ(0, memcmp( mbzKB, s_ambzTest[uiIndex2], nbyDest_Start ));
                        Test__Expect_EQ(0, memcmp( mbzKB_Start, mbzTest_Start, nbyTest ) );
                        Test__Expect_EQ(0, memcmp( mbzKB_Start + nbyTest, mbzDest_End, nbyMaxTest2 - nbyDest_End ));
                        Test__Expect_EQ(tgKB.m_nbyBuffer, nbyDest_Start + nbyTest + (nbyMaxTest2 - nbyDest_End));
                        Test__Expect_EQ(tgKB.m_nbyBuffer, tgCM_UT_ST__ST__Length_U08( &tgKB ));
                        Test__Expect_EQ(tgKB.m_nbyBuffer, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

                        tgCM_UT_ST__ST__Free( &tgKC );
                        tgCM_UT_ST__ST__Free( &tgKB );

                        TgMACRO_STEP_INDEX( uiDest_End, nuiMaxTest2, uiMaxStep_nuiTest2 );
                    };

                    TgMACRO_STEP_INDEX( uiDest_Start, nuiMaxTest2, uiMaxStep_nuiTest2 );
                };
            };

            TgMACRO_STEP_INDEX( uiTest_Start, nuiMaxTest, uiMaxStep_nuiTest );
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__SF_Replace -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SF_Replace )
{
     for (TgRSIZE uiIndex = 0; uiIndex < TgARRAY_COUNT(s_ambzTest); ++uiIndex)
     {
         TgRSIZE_C                           nbyMaxTest = s_asTest_Length[uiIndex].m_nbyCharacters;
         TgRSIZE_C                           nuiMaxTest = s_asTest_Length[uiIndex].m_nuiCharacters;
         TgRSIZE_C       uiMaxStep_nuiTest = tgCM_MIN_UMAX( nuiMaxTest, 10 );

         /* Assign with pointer to self */

         for (TgRSIZE uiTest_Start = 0, uiTest_Start_Step = 0; uiTest_Start_Step <= uiMaxStep_nuiTest; ++uiTest_Start_Step)
         {
             TgCHAR_U8_CPC   mbzTest_Start = tgUSZ_Query_At( s_ambzTest[uiIndex], nbyMaxTest + 1, uiTest_Start );

             for (TgRSIZE uiTest_End = uiTest_Start, uiTest_End_Step = uiTest_Start_Step; uiTest_End_Step <= uiMaxStep_nuiTest; ++uiTest_End_Step)
             {
                 TgCHAR_U8_CPC   mbzTest_End = tgUSZ_Query_At( s_ambzTest[uiIndex], nbyMaxTest + 1, uiTest_End );
                 TgRSIZE_C                           nbyTest = mbzTest_End >= mbzTest_Start ? (TgRSIZE)(mbzTest_End - mbzTest_Start) : 0;

                 TgCHAR_U8_CP                        mbzDest_Start, mbzDest_End;
                 TgRSIZE                             nbyDest_Start, nbyDest_End;

                 for (TgRSIZE uiDest_Start = 0, uiDest_Start_Step = 0; uiDest_Start_Step <= uiMaxStep_nuiTest; ++uiDest_Start_Step)
                 {
                     for (TgRSIZE uiDest_End = uiDest_Start, uiDest_End_Step = uiDest_Start_Step; uiDest_End_Step <= uiMaxStep_nuiTest; ++uiDest_End_Step)
                     {
                         STg2_UT_ST__ST                      tgKB;
                         TgCHAR_U8_CP                        mbzKB, mbzKB_Start;

                         tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[uiIndex] );

                         tgCM_UT_ST__ST__SF_Replace( &tgKB, uiDest_Start, uiDest_End, &tgKB, uiTest_Start, uiTest_End - uiTest_Start );
                         mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );
                         mbzKB_Start = tgUSZ_Query_At( mbzKB, tgKB.m_nbyBuffer + 1, uiDest_Start );

                         mbzDest_Start = tgUSZ_Query_At( s_ambzTest[uiIndex], nbyMaxTest + 1, uiDest_Start );
                         nbyDest_Start = (TgRSIZE)(mbzDest_Start - s_ambzTest[uiIndex]);
                         mbzDest_End = tgUSZ_Query_At( s_ambzTest[uiIndex], nbyMaxTest + 1, uiDest_End );
                         nbyDest_End = (TgRSIZE)(mbzDest_End - s_ambzTest[uiIndex]);

                         Test__Expect_EQ(0, memcmp( mbzKB, s_ambzTest[uiIndex], nbyDest_Start ));
                         Test__Expect_EQ(0, memcmp( mbzKB_Start, mbzTest_Start, nbyTest ));
                         Test__Expect_EQ(0, memcmp( mbzKB_Start + nbyTest, mbzDest_End, nbyMaxTest - nbyDest_End ));
                         Test__Expect_EQ(tgKB.m_nbyBuffer, nbyDest_Start + nbyTest + (nbyMaxTest - nbyDest_End));
                         Test__Expect_EQ(tgKB.m_nbyBuffer, tgCM_UT_ST__ST__Length_U08( &tgKB ));
                         Test__Expect_EQ(tgKB.m_nbyBuffer, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

                         tgCM_UT_ST__ST__Free( &tgKB );

                         TgMACRO_STEP_INDEX( uiDest_End, nuiMaxTest, uiMaxStep_nuiTest );
                     };

                     TgMACRO_STEP_INDEX( uiDest_Start, nuiMaxTest, uiMaxStep_nuiTest );
                 };

                 for (TgRSIZE uiIndex2 = 0; uiIndex2 < TgARRAY_COUNT(s_ambzTest); ++uiIndex2)
                 {
                     TgRSIZE_C                           nbyMaxTest2 = s_asTest_Length[uiIndex2].m_nbyCharacters;
                     TgRSIZE_C                           nuiMaxTest2 = s_asTest_Length[uiIndex2].m_nuiCharacters;
                     TgRSIZE_C       uiMaxStep_nuiTest2 = tgCM_MIN_UMAX( nuiMaxTest2, 10 );

                     for (TgRSIZE uiDest_Start = 0, uiDest_Start_Step = 0; uiDest_Start_Step <= uiMaxStep_nuiTest; ++uiDest_Start_Step)
                     {
                         for (TgRSIZE uiDest_End = uiDest_Start, uiDest_End_Step = uiDest_Start_Step; uiDest_End_Step <= uiMaxStep_nuiTest; ++uiDest_End_Step)
                         {
                             STg2_UT_ST__ST                      tgKB, tgKC;
                             TgCHAR_U8_CP                        mbzKB, mbzKB_Start;

                             tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[uiIndex2] );
                             tgCM_UT_ST__ST__SZ_Init( &tgKC, s_ambzTest[uiIndex] );

                             tgCM_UT_ST__ST__SF_Replace( &tgKB, uiDest_Start, uiDest_End, &tgKC, uiTest_Start, uiTest_End - uiTest_Start );
                             mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );
                             mbzKB_Start = tgUSZ_Query_At( mbzKB, tgKB.m_nbyBuffer + 1, uiDest_Start );

                             mbzDest_Start = tgUSZ_Query_At( s_ambzTest[uiIndex2], nbyMaxTest2 + 1, uiDest_Start );
                             nbyDest_Start = (TgRSIZE)(mbzDest_Start - s_ambzTest[uiIndex2]);
                             mbzDest_End = tgUSZ_Query_At( s_ambzTest[uiIndex2], nbyMaxTest2 + 1, uiDest_End );
                             nbyDest_End = (TgRSIZE)(mbzDest_End - s_ambzTest[uiIndex2]);

                             Test__Expect_EQ(0, memcmp( mbzKB, s_ambzTest[uiIndex2], nbyDest_Start ));
                             Test__Expect_EQ(0, memcmp( mbzKB_Start, mbzTest_Start, nbyTest ) );
                             Test__Expect_EQ(0, memcmp( mbzKB_Start + nbyTest, mbzDest_End, nbyMaxTest2 - nbyDest_End ));
                             Test__Expect_EQ(tgKB.m_nbyBuffer, nbyDest_Start + nbyTest + (nbyMaxTest2 - nbyDest_End));
                             Test__Expect_EQ(tgKB.m_nbyBuffer, tgCM_UT_ST__ST__Length_U08( &tgKB ));
                             Test__Expect_EQ(tgKB.m_nbyBuffer, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

                             tgCM_UT_ST__ST__Free( &tgKC );
                             tgCM_UT_ST__ST__Free( &tgKB );

                             TgMACRO_STEP_INDEX( uiDest_End, nuiMaxTest2, uiMaxStep_nuiTest2 );
                         };

                         TgMACRO_STEP_INDEX( uiDest_Start, nuiMaxTest2, uiMaxStep_nuiTest2 );
                     };
                 };

                 TgMACRO_STEP_INDEX( uiTest_End, nuiMaxTest, uiMaxStep_nuiTest );
             };

             TgMACRO_STEP_INDEX( uiTest_Start, nuiMaxTest, uiMaxStep_nuiTest );
         };
     };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__Erase ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__Erase )
{
    for (TgRSIZE uiIndex = 0; uiIndex < TgARRAY_COUNT(s_ambzTest); ++uiIndex)
    {
        TgRSIZE_C                           nbyMaxTest = s_asTest_Length[uiIndex].m_nbyCharacters;
        TgRSIZE_C                           nuiMaxTest = s_asTest_Length[uiIndex].m_nuiCharacters;
        TgRSIZE_C       uiMaxStep_nuiTest = tgCM_MIN_UMAX( nuiMaxTest, 10 );

        for (TgRSIZE uiDest_Start = 0, uiDest_Start_Step = 0; uiDest_Start_Step <= uiMaxStep_nuiTest; ++uiDest_Start_Step)
        {
            for (TgRSIZE uiDest_End = uiDest_Start, uiDest_End_Step = uiDest_Start_Step; uiDest_End_Step <= uiMaxStep_nuiTest; ++uiDest_End_Step)
            {
                STg2_UT_ST__ST                      tgKB;
                TgCHAR_U8_CP                        mbzKB;

                TgCHAR_U8_CPC   mbzDest_Start = tgUSZ_Query_At( s_ambzTest[uiIndex], nbyMaxTest + 1, uiDest_Start );
                TgRSIZE_C                           nbyDest_Start = (TgRSIZE)(mbzDest_Start - s_ambzTest[uiIndex]);
                TgCHAR_U8_CPC   mbzDest_End = tgUSZ_Query_At( s_ambzTest[uiIndex], nbyMaxTest + 1, uiDest_End );
                TgRSIZE_C                           nbyDest_End = (TgRSIZE)(mbzDest_End - s_ambzTest[uiIndex]);
                TgRSIZE_C                           nbyDest = mbzDest_End >= mbzDest_Start ? (TgRSIZE)(mbzDest_End - mbzDest_Start) : 0;

                tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[uiIndex] );

                tgCM_UT_ST__ST__Erase( &tgKB, uiDest_Start, uiDest_End - uiDest_Start );
                mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );

                Test__Expect_EQ(0, memcmp( mbzKB, s_ambzTest[uiIndex], nbyDest_Start ));
                Test__Expect_EQ(0, memcmp( mbzKB + nbyDest_Start, mbzDest_End, nbyMaxTest - nbyDest_End ));
                Test__Expect_EQ(tgKB.m_nbyBuffer, nbyMaxTest - nbyDest);
                Test__Expect_EQ(tgKB.m_nbyBuffer, tgCM_UT_ST__ST__Length_U08( &tgKB ));
                Test__Expect_EQ(tgKB.m_nbyBuffer, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

                tgCM_UT_ST__ST__Free( &tgKB );

                TgMACRO_STEP_INDEX( uiDest_End, nuiMaxTest, uiMaxStep_nuiTest );
            };

            TgMACRO_STEP_INDEX( uiDest_Start, nuiMaxTest, uiMaxStep_nuiTest );
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__Clear ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__Clear )
{
    for (TgRSIZE uiIndex = 0; uiIndex < TgARRAY_COUNT(s_ambzTest); ++uiIndex)
    {
        STg2_UT_ST__ST                      tgKB;
        TgCHAR_U8_CP                        mbzKB;

        tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[uiIndex] );

        tgCM_UT_ST__ST__Clear( &tgKB );

        mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );

        Test__Expect_EQ('\0', mbzKB[0]);
        Test__Expect_EQ((TgRSIZE)0, tgCM_UT_ST__ST__Length_U08( &tgKB ));
        Test__Expect_EQ((TgRSIZE)0, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

        tgCM_UT_ST__ST__Free( &tgKB );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__To_Upper ---------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__To_Upper )
{
    for (TgRSIZE uiIndex = 1; uiIndex < TgARRAY_COUNT(s_ambzTest); ++uiIndex)
    {
        TgRSIZE_C                           nbyMaxTest = s_asTest_Length[uiIndex].m_nbyCharacters;
        TgCHAR_U8_P                         mbzTemp;
        STg2_UT_ST__ST                      tgKB;
        TgCHAR_U8_CP                        mbzKB;

        tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[uiIndex] );

        tgCM_UT_ST__ST__To_Upper( &tgKB );
        mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );
        mbzTemp = (TgCHAR_U8_P)TgMALLOC_POOL( nbyMaxTest + 1 );
        tgUSZ_To_Upper( mbzTemp, nbyMaxTest + 1, s_ambzTest[uiIndex], nbyMaxTest + 1 );

        for (TgRSIZE uiCheck = 0; uiCheck < nbyMaxTest; ++uiCheck)
        {
            Test__Expect_EQ(mbzTemp[uiCheck], mbzKB[uiCheck]);
        };

        TgFREE_POOL( mbzTemp );

        tgCM_UT_ST__ST__Free( &tgKB );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__To_Lower ---------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__To_Lower )
{
    for (TgRSIZE uiIndex = 1; uiIndex < TgARRAY_COUNT(s_ambzTest); ++uiIndex)
    {
        TgCHAR_U8_P                         mbzTemp;
        STg2_UT_ST__ST                      tgKB;
        TgCHAR_U8_CP                        mbzKB;

        TgRSIZE_C                           nbyMaxTest = s_asTest_Length[uiIndex].m_nbyCharacters;

        tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[uiIndex] );

        tgCM_UT_ST__ST__To_Lower( &tgKB );
        mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );
        mbzTemp = (TgCHAR_U8_P)TgMALLOC_POOL( nbyMaxTest + 1 );
        tgUSZ_To_Lower( mbzTemp, nbyMaxTest + 1, s_ambzTest[uiIndex], nbyMaxTest + 1 );

        for (TgRSIZE uiCheck = 0; uiCheck < nbyMaxTest; ++uiCheck)
        {
            Test__Expect_EQ(mbzTemp[uiCheck], mbzKB[uiCheck]);
        };

        TgFREE_POOL( mbzTemp );

        tgCM_UT_ST__ST__Free( &tgKB );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__Format ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__Format )
{
    STg2_UT_ST__ST                      tgKB;

    tgCM_UT_ST__ST__Init( &tgKB );
    tgCM_UT_ST__ST__Format( &tgKB, u8"Test %d", 1 );
    Test__Expect_EQ(0, strcmp( (TgCHAR_NC_CP)tgCM_UT_ST__ST__Query_String( &tgKB ), "Test 1" ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__Query_String ------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__Query_String )
{
    STg2_UT_ST__ST                      tgKB;

    tgCM_UT_ST__ST__Init( &tgKB );
    Test__Expect_NE(nullptr, tgCM_UT_ST__ST__Query_String( &tgKB ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__Is_Empty ---------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__Is_Empty )
{
    STg2_UT_ST__ST                      tgKB;

    tgCM_UT_ST__ST__Init( &tgKB );
    Test__Expect_EQ(true, tgCM_UT_ST__ST__Is_Empty( &tgKB ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__Capacity ---------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__Capacity )
{
    for (TgRSIZE uiIndex = 0; uiIndex < TgARRAY_COUNT(s_ambzTest); ++uiIndex)
    {
        STg2_UT_ST__ST                      tgKB;

        TgRSIZE_C                           nbyMaxTest = s_asTest_Length[uiIndex].m_nbyCharacters;
        TgRSIZE_C                           nuiMaxTest = s_asTest_Length[uiIndex].m_nuiCharacters;
        TgRSIZE_C       uiCapacity = tgCM_MAX_UMAX( KTgSTRING_STATIC_BUFFER_SIZE - 1, nbyMaxTest );

        tgCM_UT_ST__ST__Init( &tgKB );

        Test__Expect_EQ((TgRSIZE)(KTgSTRING_STATIC_BUFFER_SIZE - 1), tgCM_UT_ST__ST__Capacity( &tgKB ));

        tgCM_UT_ST__ST__SZ_Assign( &tgKB, s_ambzTest[uiIndex] );

        Test__Expect_EQ(uiCapacity, tgCM_UT_ST__ST__Capacity( &tgKB ));

        if (0 == nbyMaxTest)
        {
            continue;
        };

        tgCM_UT_ST__ST__Erase( &tgKB, 1, nuiMaxTest - 1 );

        Test__Expect_EQ(uiCapacity, tgCM_UT_ST__ST__Capacity( &tgKB ));

        tgCM_UT_ST__ST__Free( &tgKB );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__Max_Size ---------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__Max_Size )
{
    STg2_UT_ST__ST                      tgKB;

    tgCM_UT_ST__ST__Init( &tgKB );
    tgCM_UT_ST__ST__Max_Size( &tgKB );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__Length_U08 -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__Length_U08 )
{
    for (TgRSIZE uiIndex = 0; uiIndex < TgARRAY_COUNT(s_ambzTest); ++uiIndex)
    {
        TgRSIZE_C                           nbyMaxTest = s_asTest_Length[uiIndex].m_nbyCharacters;

        STg2_UT_ST__ST                      tgKB;

        tgCM_UT_ST__ST__Init( &tgKB );

        Test__Expect_EQ((TgRSIZE)0, tgCM_UT_ST__ST__Length_U08( &tgKB ));

        tgCM_UT_ST__ST__SZ_Assign( &tgKB, s_ambzTest[uiIndex] );

        Test__Expect_EQ(nbyMaxTest, tgCM_UT_ST__ST__Length_U08( &tgKB ));

        tgCM_UT_ST__ST__Free( &tgKB );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__Length_Count ------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__Length_Count )
{
    for (TgRSIZE uiIndex = 0; uiIndex < TgARRAY_COUNT(s_ambzTest); ++uiIndex)
    {
        TgRSIZE_C                           nbyMaxTest = s_asTest_Length[uiIndex].m_nbyCharacters;
        TgRSIZE_C                           nuiMaxTest = s_asTest_Length[uiIndex].m_nuiCharacters;

        STg2_UT_ST__ST                      tgKB;
        TgRSIZE                             uiCount;

        tgCM_UT_ST__ST__Init( &tgKB );

        Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__Length_Count( &uiCount, &tgKB ));
        Test__Expect_EQ((TgRSIZE)0, uiCount);

        tgCM_UT_ST__ST__SZ_Assign( &tgKB, s_ambzTest[uiIndex] );

        Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__Length_Count( &uiCount, &tgKB ));
        Test__Expect_EQ(nuiMaxTest, uiCount);

        if (0 == nbyMaxTest)
        {
            continue;
        };

        tgCM_UT_ST__ST__Erase( &tgKB, 1, nuiMaxTest - 1 );

        Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__Length_Count( &uiCount, &tgKB ));
        Test__Expect_EQ((TgRSIZE)1, uiCount);

        tgCM_UT_ST__ST__Free( &tgKB );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__Resize_NCS -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__Resize_NCS )
{
    for (TgRSIZE uiIndex2 = 0; uiIndex2 < TgARRAY_COUNT(s_ambzTest); ++uiIndex2)
    {
        TgRSIZE_C                           nbyMaxTest2 = s_asTest_Length[uiIndex2].m_nbyCharacters;

        for (TgRSIZE uiIndex = 0; uiIndex < TgARRAY_COUNT(s_ambzTest); ++uiIndex)
        {
            TgRSIZE_C                           nbyMaxTest = s_asTest_Length[uiIndex].m_nbyCharacters;

            STg2_UT_ST__ST                      tgKB;
            TgCHAR_U8_CP                        mbzKB;
            TgRSIZE                             uiCheck;

            tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[uiIndex2] );

            tgCM_UT_ST__ST__Resize_NCS( &tgKB, nbyMaxTest, '#' );
            mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );

            for (uiCheck = 0; uiCheck < tgCM_MIN_UMAX( nbyMaxTest2, tgKB.m_nbyBuffer ); ++uiCheck)
            {
                Test__Expect_EQ(s_ambzTest[uiIndex2][uiCheck], mbzKB[uiCheck]);
            };

            for (; uiCheck < nbyMaxTest; ++uiCheck)
            {
                Test__Expect_EQ('#', mbzKB[uiCheck]);
            };

            Test__Expect_EQ(tgKB.m_nbyBuffer, nbyMaxTest);
            Test__Expect_EQ(tgKB.m_nbyBuffer, tgCM_UT_ST__ST__Length_U08( &tgKB ));
            Test__Expect_EQ(tgKB.m_nbyBuffer, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

            Test__Expect_EQ(tgCM_MAX_UMAX( KTgSTRING_STATIC_BUFFER_SIZE - 1, nbyMaxTest ), tgCM_UT_ST__ST__Capacity( &tgKB ));

            tgCM_UT_ST__ST__Free( &tgKB );

            tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[uiIndex2] );

            tgCM_UT_ST__ST__Resize_NCS( &tgKB, nbyMaxTest, '\0' );
            mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );

            for (uiCheck = 0; uiCheck < tgCM_MIN_UMAX( nbyMaxTest2, tgKB.m_nbyBuffer ); ++uiCheck)
            {
                Test__Expect_EQ(s_ambzTest[uiIndex2][uiCheck], mbzKB[uiCheck]);
            };

            Test__Expect_EQ(tgKB.m_nbyBuffer, tgCM_MIN_UMAX( nbyMaxTest2, tgKB.m_nbyBuffer ));
            Test__Expect_EQ(tgKB.m_nbyBuffer, tgCM_UT_ST__ST__Length_U08( &tgKB ));
            Test__Expect_EQ(tgKB.m_nbyBuffer, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

            Test__Expect_EQ(tgCM_MAX_UMAX( KTgSTRING_STATIC_BUFFER_SIZE - 1, nbyMaxTest ), tgCM_UT_ST__ST__Capacity( &tgKB ));

            tgCM_UT_ST__ST__Free( &tgKB );
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__Reserve ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__Reserve )
{
    for (TgRSIZE uiIndex2 = 0; uiIndex2 < TgARRAY_COUNT(s_ambzTest); ++uiIndex2)
    {
        for (TgRSIZE uiIndex = 0; uiIndex < TgARRAY_COUNT(s_ambzTest); ++uiIndex)
        {
            TgRSIZE_C                           nbyMaxTest = s_asTest_Length[uiIndex].m_nbyCharacters;

            STg2_UT_ST__ST                      tgKB;
            TgCHAR_U8_CP                        mbzKB;
            TgRSIZE                             uiCheck;

            tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[uiIndex2] );
            tgCM_UT_ST__ST__Reserve( &tgKB, nbyMaxTest );

            mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );

            for (uiCheck = 0; uiCheck < s_asTest_Length[uiIndex2].m_nbyCharacters; ++uiCheck)
            {
                Test__Expect_EQ(s_ambzTest[uiIndex2][uiCheck], mbzKB[uiCheck]);
            };

            Test__Expect_EQ(tgKB.m_nbyBuffer, s_asTest_Length[uiIndex2].m_nbyCharacters);
            Test__Expect_EQ(tgKB.m_nbyBuffer, tgCM_UT_ST__ST__Length_U08( &tgKB ));
            Test__Expect_EQ(tgKB.m_nbyBuffer, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

            Test__Expect_EQ(
                tgCM_MAX_UMAX( KTgSTRING_STATIC_BUFFER_SIZE - 1, tgCM_MAX_UMAX( s_asTest_Length[uiIndex2].m_nbyCharacters, nbyMaxTest ) ),
                tgCM_UT_ST__ST__Capacity( &tgKB ) );

            tgCM_UT_ST__ST__Free( &tgKB );
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__Swap -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__Swap )
{
    for (TgRSIZE uiIndex = 0; uiIndex < TgARRAY_COUNT(s_ambzTest); ++uiIndex)
    {
        TgRSIZE_C                           nbyMaxTest = s_asTest_Length[uiIndex].m_nbyCharacters;

        STg2_UT_ST__ST                      tgKB, tgKC;
        TgCHAR_U8_CP                        mbzKB;
        TgRSIZE                             uiCheck;

        tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[uiIndex] );
        tgCM_UT_ST__ST__Init( &tgKC );

        mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );
        uiCheck = nbyMaxTest;

        Test__Expect_EQ(0, memcmp( mbzKB, s_ambzTest[uiIndex], nbyMaxTest ));
        Test__Expect_EQ('\0', mbzKB[uiCheck]);
        Test__Expect_EQ(uiCheck, tgCM_UT_ST__ST__Length_U08( &tgKB ));
        Test__Expect_EQ(uiCheck, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

        mbzKB = tgCM_UT_ST__ST__Query_String( &tgKC );
        uiCheck = 0;

        Test__Expect_EQ('\0', mbzKB[uiCheck]);
        Test__Expect_EQ(uiCheck, tgCM_UT_ST__ST__Length_U08( &tgKC ));
        Test__Expect_EQ(uiCheck, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

        tgCM_UT_ST__ST__Swap( &tgKB, &tgKC );

        mbzKB = tgCM_UT_ST__ST__Query_String( &tgKC );
        uiCheck = nbyMaxTest;

        Test__Expect_EQ(0, memcmp( mbzKB, s_ambzTest[uiIndex], nbyMaxTest ));
        Test__Expect_EQ('\0', mbzKB[uiCheck]);
        Test__Expect_EQ(uiCheck, tgCM_UT_ST__ST__Length_U08( &tgKC ));
        Test__Expect_EQ(uiCheck, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

        mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );
        uiCheck = 0;

        Test__Expect_EQ('\0', mbzKB[uiCheck]);
        Test__Expect_EQ(uiCheck, tgCM_UT_ST__ST__Length_U08( &tgKB ));
        Test__Expect_EQ(uiCheck, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

        tgCM_UT_ST__ST__Free( &tgKB );
        tgCM_UT_ST__ST__Free( &tgKC );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__Is_Inside --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__Is_Inside )
{
    for (TgRSIZE uiSrc = 0; uiSrc < TgARRAY_COUNT(s_ambzCmp_Test); ++uiSrc)
    {
        STg2_UT_ST__ST                      tgKB;
        TgCHAR_U8_CP                        mbzKB;

        tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzCmp_Test[uiSrc] );

        mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );
        Test__Expect_EQ(true, tgCM_UT_ST__ST__Is_Inside( &tgKB, mbzKB ));
        Test__Expect_EQ(false, tgCM_UT_ST__ST__Is_Inside( &tgKB, mbzKB - 1 ));
        Test__Expect_EQ(true, tgCM_UT_ST__ST__Is_Inside( &tgKB, mbzKB + 1 ));
        Test__Expect_EQ(false, tgCM_UT_ST__ST__Is_Inside( &tgKB, s_ambzCmp_Test[uiSrc] ));
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__ST_SZ_Compare ----------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__ST_SZ_Compare )
{
    for (TgRSIZE uiSrc = 0; uiSrc < TgARRAY_COUNT(s_ambzCmp_Test); ++uiSrc)
    {
        for (TgRSIZE uiCmp = 0; uiCmp < TgARRAY_COUNT(s_ambzCmp_Test); ++uiCmp)
        {
            STg2_UT_ST__ST                      tgKB, tgKC;
            TgCHAR_U8_CP                        mbzKC;
            TgSINT_E08                          iRet;

            tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzCmp_Test[uiSrc] );
            tgCM_UT_ST__ST__SZ_Init( &tgKC, s_ambzCmp_Test[uiCmp] );
            mbzKC = tgCM_UT_ST__ST__Query_String( &tgKC );
            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__ST_SZ_Compare( &iRet, &tgKB, mbzKC ));
            Test__Expect_EQ(uiSrc == uiCmp ? 0 : ((uiSrc < uiCmp) ? -1 :  1), tgCM_SGN_S32( iRet ));

            tgCM_UT_ST__ST__Erase( &tgKB, 0, 1 );
            tgCM_UT_ST__ST__Erase( &tgKC, 0, 1 );
            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__ST_SZ_Compare( &iRet, &tgKB, mbzKC ));
            Test__Expect_EQ(uiSrc == uiCmp ? 0 : (((uiSrc < 4) ^ (uiCmp < 4)) ? (uiSrc < uiCmp ? -1 :  1) : (uiSrc < uiCmp ?  1 : -1)), tgCM_SGN_S32( iRet ));

            tgCM_UT_ST__ST__Erase( &tgKB, 0, 1 );
            tgCM_UT_ST__ST__Erase( &tgKC, 0, 1 );
            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__ST_SZ_Compare( &iRet, &tgKB, mbzKC ));
            Test__Expect_EQ((((uiSrc < 4) ^ (uiCmp < 4)) ? (uiSrc < uiCmp ? -1 :  1) : 0), tgCM_SGN_S32( iRet ));

            tgCM_UT_ST__ST__Erase( &tgKB, 0, 1 );
            tgCM_UT_ST__ST__Erase( &tgKC, 0, 1 );
            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__ST_SZ_Compare( &iRet, &tgKB, mbzKC ));
            Test__Expect_EQ((((uiSrc < 4) ^ (uiCmp < 4)) ? (uiSrc < uiCmp ? -1 :  1) : 0), tgCM_SGN_S32( iRet ));

            tgCM_UT_ST__ST__Free( &tgKB );
            tgCM_UT_ST__ST__Free( &tgKC );
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__ST_SN_Compare ----------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__ST_SN_Compare )
{
    for (TgRSIZE uiSrc = 0; uiSrc < TgARRAY_COUNT(s_ambzCmp_Test); ++uiSrc)
    {
        for (TgRSIZE uiCmp = 0; uiCmp < TgARRAY_COUNT(s_ambzCmp_Test); ++uiCmp)
        {
            STg2_UT_ST__ST                      tgKB, tgKC;
            TgCHAR_U8_CP                        mbzKC;
            TgSINT_E08                          iRet;

            tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzCmp_Test[uiSrc] );
            tgCM_UT_ST__ST__SZ_Init( &tgKC, s_ambzCmp_Test[uiCmp] );
            mbzKC = tgCM_UT_ST__ST__Query_String( &tgKC );
            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__ST_SN_Compare( &iRet, &tgKB, mbzKC, 1 ));
            Test__Expect_EQ(uiSrc == uiCmp ? 0 : ((uiSrc < uiCmp) ? -1 :  1), tgCM_SGN_S32( iRet ));

            tgCM_UT_ST__ST__Erase( &tgKB, 0, 1 );
            tgCM_UT_ST__ST__Erase( &tgKC, 0, 1 );
            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__ST_SN_Compare( &iRet, &tgKB, mbzKC, 1 ));
            Test__Expect_EQ(uiSrc == uiCmp ? 0 : (((uiSrc < 4) ^ (uiCmp < 4)) ? (uiSrc < uiCmp ? -1 :  1) : (uiSrc < uiCmp ?  1 : -1)), tgCM_SGN_S32( iRet ));

            tgCM_UT_ST__ST__Erase( &tgKB, 0, 1 );
            tgCM_UT_ST__ST__Erase( &tgKC, 0, 1 );
            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__ST_SN_Compare( &iRet, &tgKB, mbzKC, 1 ));
            Test__Expect_EQ(0, tgCM_SGN_S32( iRet ));

            tgCM_UT_ST__ST__Erase( &tgKB, 0, 1 );
            tgCM_UT_ST__ST__Erase( &tgKC, 0, 1 );
            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__ST_SN_Compare( &iRet, &tgKB, mbzKC, 1 ));
            Test__Expect_EQ((((uiSrc < 4) ^ (uiCmp < 4)) ? (uiSrc < uiCmp ? -1 :  1) : 0), tgCM_SGN_S32( iRet ));

            tgCM_UT_ST__ST__Free( &tgKB );
            tgCM_UT_ST__ST__Free( &tgKC );
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__ST_ST_Compare ----------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__ST_ST_Compare )
{
    for (TgRSIZE uiSrc = 0; uiSrc < TgARRAY_COUNT(s_ambzCmp_Test); ++uiSrc)
    {
        for (TgRSIZE uiCmp = 0; uiCmp < TgARRAY_COUNT(s_ambzCmp_Test); ++uiCmp)
        {
            STg2_UT_ST__ST                      tgKB, tgKC;
            TgSINT_E08                          iRet;

            tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzCmp_Test[uiSrc] );
            tgCM_UT_ST__ST__SZ_Init( &tgKC, s_ambzCmp_Test[uiCmp] );
            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__ST_ST_Compare( &iRet, &tgKB, &tgKC ));
            Test__Expect_EQ(uiSrc == uiCmp ? 0 : ((uiSrc < uiCmp) ? -1 :  1), tgCM_SGN_S32( iRet ));

            tgCM_UT_ST__ST__Erase( &tgKB, 0, 1 );
            tgCM_UT_ST__ST__Erase( &tgKC, 0, 1 );
            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__ST_ST_Compare( &iRet, &tgKB, &tgKC ));
            Test__Expect_EQ(uiSrc == uiCmp ? 0 : (((uiSrc < 4) ^ (uiCmp < 4)) ? (uiSrc < uiCmp ? -1 :  1) : (uiSrc < uiCmp ?  1 : -1)), tgCM_SGN_S32( iRet ));

            tgCM_UT_ST__ST__Erase( &tgKB, 0, 1 );
            tgCM_UT_ST__ST__Erase( &tgKC, 0, 1 );
            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__ST_ST_Compare( &iRet, &tgKB, &tgKC ));
            Test__Expect_EQ((((uiSrc < 4) ^ (uiCmp < 4)) ? (uiSrc < uiCmp ? -1 :  1) : 0), tgCM_SGN_S32( iRet ));

            tgCM_UT_ST__ST__Erase( &tgKB, 0, 1 );
            tgCM_UT_ST__ST__Erase( &tgKC, 0, 1 );
            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__ST_ST_Compare( &iRet, &tgKB, &tgKC ));
            Test__Expect_EQ((((uiSrc < 4) ^ (uiCmp < 4)) ? (uiSrc < uiCmp ? -1 :  1) : 0), tgCM_SGN_S32( iRet ));

            tgCM_UT_ST__ST__Free( &tgKB );
            tgCM_UT_ST__ST__Free( &tgKC );
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__ST_SF_Compare ----------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__ST_SF_Compare )
{
    for (TgRSIZE uiSrc = 0; uiSrc < TgARRAY_COUNT(s_ambzCmp_Test); ++uiSrc)
    {
        for (TgRSIZE uiCmp = 0; uiCmp < TgARRAY_COUNT(s_ambzCmp_Test); ++uiCmp)
        {
            STg2_UT_ST__ST                      tgKB, tgKC;
            TgSINT_E08                          iRet;

            tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzCmp_Test[uiSrc] );
            tgCM_UT_ST__ST__SZ_Init( &tgKC, s_ambzCmp_Test[uiCmp] );
            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__ST_SF_Compare( &iRet, &tgKB, &tgKC, 0, 4 ));
            Test__Expect_EQ(uiSrc == uiCmp ? 0 : ((uiSrc < uiCmp) ? -1 :  1), tgCM_SGN_S32( iRet ));

            tgCM_UT_ST__ST__Erase( &tgKB, 0, 1 );
            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__ST_SF_Compare( &iRet, &tgKB, &tgKC, 1, 3 ));
            Test__Expect_EQ(uiSrc == uiCmp ? 0 : (((uiSrc < 4) ^ (uiCmp < 4)) ? (uiSrc < uiCmp ? -1 :  1) : (uiSrc < uiCmp ?  1 : -1)), tgCM_SGN_S32( iRet ));

            tgCM_UT_ST__ST__Erase( &tgKB, 0, 1 );
            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__ST_SF_Compare( &iRet, &tgKB, &tgKC, 2, 2 ));
            Test__Expect_EQ((((uiSrc < 4) ^ (uiCmp < 4)) ? (uiSrc < uiCmp ? -1 :  1) : 0), tgCM_SGN_S32( iRet ));

            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__ST_SF_Compare( &iRet, &tgKB, &tgKC, 2, 1 ));
            Test__Expect_EQ(0, tgCM_SGN_S32( iRet ));

            tgCM_UT_ST__ST__Erase( &tgKB, 0, 1 );
            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__ST_SF_Compare( &iRet, &tgKB, &tgKC, 3, 1 ));
            Test__Expect_EQ((((uiSrc < 4) ^ (uiCmp < 4)) ? (uiSrc < uiCmp ? -1 :  1) : 0), tgCM_SGN_S32( iRet ));

            tgCM_UT_ST__ST__Free( &tgKB );
            tgCM_UT_ST__ST__Free( &tgKC );
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__SF_SZ_Compare ----------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SF_SZ_Compare )
{
    for (TgRSIZE uiSrc = 0; uiSrc < TgARRAY_COUNT(s_ambzCmp_Test); ++uiSrc)
    {
        for (TgRSIZE uiCmp = 0; uiCmp < TgARRAY_COUNT(s_ambzCmp_Test); ++uiCmp)
        {
            STg2_UT_ST__ST                      tgKB, tgKC;
            TgCHAR_U8_CP                        mbzKC;
            TgSINT_E08                          iRet;

            tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzCmp_Test[uiSrc] );
            tgCM_UT_ST__ST__SZ_Init( &tgKC, s_ambzCmp_Test[uiCmp] );
            mbzKC = tgCM_UT_ST__ST__Query_String( &tgKC );
            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SF_SZ_Compare( &iRet, &tgKB, 0, 3, mbzKC ));
            Test__Expect_EQ(uiSrc == uiCmp ? 0 : ((uiSrc < uiCmp) ? -1 :  1), tgCM_SGN_S32( iRet ));

            tgCM_UT_ST__ST__Erase( &tgKC, 0, 1 );
            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SF_SZ_Compare( &iRet, &tgKB, 1, 2, mbzKC ));
            Test__Expect_EQ(uiSrc == uiCmp ? 0 : (((uiSrc < 4) ^ (uiCmp < 4)) ? (uiSrc < uiCmp ? -1 :  1) : (uiSrc < uiCmp ?  1 : -1)), tgCM_SGN_S32( iRet ));

            tgCM_UT_ST__ST__Erase( &tgKC, 0, 1 );
            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SF_SZ_Compare( &iRet, &tgKB, 2, 2, mbzKC ));
            Test__Expect_EQ((((uiSrc < 4) ^ (uiCmp < 4)) ? (uiSrc < uiCmp ? -1 :  1) : 0), tgCM_SGN_S32( iRet ));

            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SF_SZ_Compare( &iRet, &tgKB, 2, 1, mbzKC ));
            Test__Expect_EQ(0, tgCM_SGN_S32( iRet ));

            tgCM_UT_ST__ST__Erase( &tgKC, 0, 1 );
            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SF_SZ_Compare( &iRet, &tgKB, 3, 1, mbzKC ));
            Test__Expect_EQ((((uiSrc < 4) ^ (uiCmp < 4)) ? (uiSrc < uiCmp ? -1 :  1) : 0), tgCM_SGN_S32( iRet ));

            tgCM_UT_ST__ST__Free( &tgKB );
            tgCM_UT_ST__ST__Free( &tgKC );
        };
    };


    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__SF_SN_Compare ----------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SF_SN_Compare )
{
    for (TgRSIZE uiSrc = 0; uiSrc < TgARRAY_COUNT(s_ambzCmp_Test); ++uiSrc)
    {
        for (TgRSIZE uiCmp = 0; uiCmp < TgARRAY_COUNT(s_ambzCmp_Test); ++uiCmp)
        {
            STg2_UT_ST__ST                      tgKB, tgKC;
            TgSINT_E08                          iRet;

            tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzCmp_Test[uiSrc] );
            tgCM_UT_ST__ST__SZ_Init( &tgKC, s_ambzCmp_Test[uiCmp] );
            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SF_ST_Compare( &iRet, &tgKB, 0, 3, &tgKC ));
            Test__Expect_EQ(uiSrc == uiCmp ? 0 : ((uiSrc < uiCmp) ? -1 :  1), tgCM_SGN_S32( iRet ));

            tgCM_UT_ST__ST__Erase( &tgKC, 0, 1 );
            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SF_ST_Compare( &iRet, &tgKB, 1, 2, &tgKC ));
            Test__Expect_EQ(uiSrc == uiCmp ? 0 : (((uiSrc < 4) ^ (uiCmp < 4)) ? (uiSrc < uiCmp ? -1 :  1) : (uiSrc < uiCmp ?  1 : -1)), tgCM_SGN_S32( iRet ));

            tgCM_UT_ST__ST__Erase( &tgKC, 0, 1 );
            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SF_ST_Compare( &iRet, &tgKB, 2, 2, &tgKC ));
            Test__Expect_EQ((((uiSrc < 4) ^ (uiCmp < 4)) ? (uiSrc < uiCmp ? -1 :  1) : 0), tgCM_SGN_S32( iRet ));

            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SF_ST_Compare( &iRet, &tgKB, 2, 1, &tgKC ));
            Test__Expect_EQ(0, tgCM_SGN_S32( iRet ));

            tgCM_UT_ST__ST__Erase( &tgKC, 0, 1 );
            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SF_ST_Compare( &iRet, &tgKB, 3, 1, &tgKC ));
            Test__Expect_EQ((((uiSrc < 4) ^ (uiCmp < 4)) ? (uiSrc < uiCmp ? -1 :  1) : 0), tgCM_SGN_S32( iRet ));

            tgCM_UT_ST__ST__Free( &tgKB );
            tgCM_UT_ST__ST__Free( &tgKC );
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__SF_ST_Compare ----------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SF_ST_Compare )
{
    for (TgRSIZE uiSrc = 0; uiSrc < TgARRAY_COUNT(s_ambzCmp_Test); ++uiSrc)
    {
        for (TgRSIZE uiCmp = 0; uiCmp < TgARRAY_COUNT(s_ambzCmp_Test); ++uiCmp)
        {
            STg2_UT_ST__ST                      tgKB, tgKC;
            TgSINT_E08                          iRet;

            tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzCmp_Test[uiSrc] );
            tgCM_UT_ST__ST__SZ_Init( &tgKC, s_ambzCmp_Test[uiCmp] );
            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SF_ST_Compare( &iRet, &tgKB, 0, 4, &tgKC ));
            Test__Expect_EQ(uiSrc == uiCmp ? 0 : ((uiSrc < uiCmp) ? -1 :  1), tgCM_SGN_S32( iRet ));

            tgCM_UT_ST__ST__Erase( &tgKC, 0, 1 );
            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SF_ST_Compare( &iRet, &tgKB, 1, 3, &tgKC ));
            Test__Expect_EQ(uiSrc == uiCmp ? 0 : (((uiSrc < 4) ^ (uiCmp < 4)) ? (uiSrc < uiCmp ? -1 :  1) : (uiSrc < uiCmp ?  1 : -1)), tgCM_SGN_S32( iRet ));

            tgCM_UT_ST__ST__Erase( &tgKC, 0, 1 );
            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SF_ST_Compare( &iRet, &tgKB, 2, 2, &tgKC ));
            Test__Expect_EQ((((uiSrc < 4) ^ (uiCmp < 4)) ? (uiSrc < uiCmp ? -1 :  1) : 0), tgCM_SGN_S32( iRet ));

            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SF_ST_Compare( &iRet, &tgKB, 2, 1, &tgKC ));
            Test__Expect_EQ(0, tgCM_SGN_S32( iRet ));

            tgCM_UT_ST__ST__Erase( &tgKC, 0, 1 );
            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SF_ST_Compare( &iRet, &tgKB, 3, 1, &tgKC ));
            Test__Expect_EQ((((uiSrc < 4) ^ (uiCmp < 4)) ? (uiSrc < uiCmp ? -1 :  1) : 0), tgCM_SGN_S32( iRet ));

            tgCM_UT_ST__ST__Free( &tgKB );
            tgCM_UT_ST__ST__Free( &tgKC );
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__SF_SF_Compare ----------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SF_SF_Compare )
{
    for (TgRSIZE uiSrc = 0; uiSrc < TgARRAY_COUNT(s_ambzCmp_Test); ++uiSrc)
    {
        for (TgRSIZE uiCmp = 0; uiCmp < TgARRAY_COUNT(s_ambzCmp_Test); ++uiCmp)
        {
            STg2_UT_ST__ST                      tgKB, tgKC;
            TgSINT_E08                          iRet;

            tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzCmp_Test[uiSrc] );
            tgCM_UT_ST__ST__SZ_Init( &tgKC, s_ambzCmp_Test[uiCmp] );
            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SF_SF_Compare( &iRet, &tgKB, 0, 4, &tgKC, 0 ));
            Test__Expect_EQ(uiSrc == uiCmp ? 0 : ((uiSrc < uiCmp) ? -1 :  1), tgCM_SGN_S32( iRet ));

            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SF_SF_Compare( &iRet, &tgKB, 1, 3, &tgKC, 1 ));
            Test__Expect_EQ(uiSrc == uiCmp ? 0 : (((uiSrc < 4) ^ (uiCmp < 4)) ? (uiSrc < uiCmp ? -1 :  1) : (uiSrc < uiCmp ?  1 : -1)), tgCM_SGN_S32( iRet ));

            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SF_SF_Compare( &iRet, &tgKB, 2, 2, &tgKC, 2 ));
            Test__Expect_EQ((((uiSrc < 4) ^ (uiCmp < 4)) ? (uiSrc < uiCmp ? -1 :  1) : 0), tgCM_SGN_S32( iRet ));

            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SF_SF_Compare( &iRet, &tgKB, 2, 1, &tgKC, 2 ));
            Test__Expect_EQ(0, tgCM_SGN_S32( iRet ));

            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SF_SF_Compare( &iRet, &tgKB, 3, 1, &tgKC, 3 ));
            Test__Expect_EQ((((uiSrc < 4) ^ (uiCmp < 4)) ? (uiSrc < uiCmp ? -1 :  1) : 0), tgCM_SGN_S32( iRet ));

            tgCM_UT_ST__ST__Free( &tgKB );
            tgCM_UT_ST__ST__Free( &tgKC );
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__SO_SZ_Find_String ------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SO_SZ_Find_String )
{
    for (TgRSIZE uiSrc = 0; uiSrc < TgARRAY_COUNT(s_ambzTest); ++uiSrc)
    {
        for (TgRSIZE uiCmp = 0; uiCmp < TgARRAY_COUNT(s_ambzTest); ++uiCmp)
        {
            TgRSIZE_C                           nuiCmp_MaxTest = s_asTest_Length[uiCmp].m_nuiCharacters;
            TgRSIZE_C       uiRes0 = (uiSrc == uiCmp) ? nuiCmp_MaxTest * 0 : nuiCmp_MaxTest * 2;
            TgRSIZE_C       uiRes1 = (uiSrc == uiCmp) ? nuiCmp_MaxTest * 1 : nuiCmp_MaxTest * 2;
            TgRSIZE_C       uiRes2 = (uiSrc == uiCmp) ? nuiCmp_MaxTest * 2 : nuiCmp_MaxTest * 2;
            TgRSIZE_C       uiRes3 = (uiSrc == uiCmp) ? nuiCmp_MaxTest * 3 : KTgMAX_RSIZE;

            STg2_UT_ST__ST                      tgKA, tgKB;
            TgCHAR_U8_CP                        mbzKA;
            STg1_Text_Length                    sOffset;

            tgCM_UT_ST__ST__SZ_Init( &tgKA, s_ambzTest[uiSrc] );
            mbzKA = tgCM_UT_ST__ST__Query_String( &tgKA );

            tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[uiCmp] );
            tgCM_UT_ST__ST__SZ_Append( &tgKB, s_ambzTest[uiCmp] );
            tgCM_UT_ST__ST__SZ_Append( &tgKB, s_ambzTest[uiSrc] );
            tgCM_UT_ST__ST__SZ_Append( &tgKB, s_ambzTest[uiCmp] );

            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SO_SZ_Find_String( &sOffset, &tgKB, nuiCmp_MaxTest * 0, mbzKA ));
            Test__Expect_EQ(uiRes0, sOffset.m_nuiCharacters);

            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SO_SZ_Find_String( &sOffset, &tgKB, nuiCmp_MaxTest * 1, mbzKA ));
            Test__Expect_EQ(uiRes1, sOffset.m_nuiCharacters);

            Test__Expect_EQ(KTgMAX_RSIZE == uiRes2 ? KTgE_FAIL : KTgS_OK, tgCM_UT_ST__ST__SO_SZ_Find_String( &sOffset, &tgKB, nuiCmp_MaxTest * 2, mbzKA ));
            Test__Expect_EQ(uiRes2, KTgMAX_RSIZE == uiRes2 ? KTgMAX_RSIZE : sOffset.m_nuiCharacters);

            Test__Expect_EQ(KTgMAX_RSIZE == uiRes3 ? KTgE_FAIL : KTgS_OK, tgCM_UT_ST__ST__SO_SZ_Find_String( &sOffset, &tgKB, nuiCmp_MaxTest * 3, mbzKA ));
            Test__Expect_EQ(uiRes3, KTgMAX_RSIZE == uiRes3 ? KTgMAX_RSIZE : sOffset.m_nuiCharacters);

            tgCM_UT_ST__ST__Free( &tgKA );
            tgCM_UT_ST__ST__Free( &tgKB );
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__SO_SN_Find_String ------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SO_SN_Find_String )
{
    for (TgRSIZE uiSrc = 0; uiSrc < TgARRAY_COUNT(s_ambzTest); ++uiSrc)
    {
        TgRSIZE_C                           nuiSrc_MaxTest = s_asTest_Length[uiSrc].m_nuiCharacters;

        for (TgRSIZE uiCmp = 0; uiCmp < TgARRAY_COUNT(s_ambzTest); ++uiCmp)
        {
            TgRSIZE_C                           nuiCmp_MaxTest = s_asTest_Length[uiCmp].m_nuiCharacters;
            TgRSIZE_C       uiRes0 = (uiSrc == uiCmp) ? nuiCmp_MaxTest * 0 : nuiCmp_MaxTest * 2;
            TgRSIZE_C       uiRes1 = (uiSrc == uiCmp) ? nuiCmp_MaxTest * 1 : nuiCmp_MaxTest * 2;
            TgRSIZE_C       uiRes2 = (uiSrc == uiCmp) ? nuiCmp_MaxTest * 2 : nuiCmp_MaxTest * 2;
            TgRSIZE_C       uiRes3 = (uiSrc == uiCmp) ? nuiCmp_MaxTest * 3 : KTgMAX_RSIZE;

            STg2_UT_ST__ST                      tgKA, tgKB;
            TgCHAR_U8_CP                        mbzKA;
            STg1_Text_Length                    sOffset;

            tgCM_UT_ST__ST__SZ_Init( &tgKA, s_ambzTest[uiSrc] );
            mbzKA = tgCM_UT_ST__ST__Query_String( &tgKA );

            tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[uiCmp] );
            tgCM_UT_ST__ST__SZ_Append( &tgKB, s_ambzTest[uiCmp] );
            tgCM_UT_ST__ST__SZ_Append( &tgKB, s_ambzTest[uiSrc] );
            tgCM_UT_ST__ST__SZ_Append( &tgKB, s_ambzTest[uiCmp] );

            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SO_SN_Find_String( &sOffset, &tgKB, nuiCmp_MaxTest * 0, mbzKA, nuiSrc_MaxTest ));
            Test__Expect_EQ(uiRes0, sOffset.m_nuiCharacters);

            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SO_SN_Find_String( &sOffset, &tgKB, nuiCmp_MaxTest * 1, mbzKA, nuiSrc_MaxTest ));
            Test__Expect_EQ(uiRes1, sOffset.m_nuiCharacters);

            Test__Expect_EQ(KTgMAX_RSIZE == uiRes2 ? KTgE_FAIL : KTgS_OK, tgCM_UT_ST__ST__SO_SN_Find_String( &sOffset, &tgKB, nuiCmp_MaxTest * 2, mbzKA, nuiSrc_MaxTest ));
            Test__Expect_EQ(uiRes2, KTgMAX_RSIZE == uiRes2 ? KTgMAX_RSIZE : sOffset.m_nuiCharacters);

            Test__Expect_EQ(KTgMAX_RSIZE == uiRes3 ? KTgE_FAIL : KTgS_OK, tgCM_UT_ST__ST__SO_SN_Find_String( &sOffset, &tgKB, nuiCmp_MaxTest * 3, mbzKA, nuiSrc_MaxTest ));
            Test__Expect_EQ(uiRes3, KTgMAX_RSIZE == uiRes3 ? KTgMAX_RSIZE : sOffset.m_nuiCharacters);

            tgCM_UT_ST__ST__Free( &tgKA );
            tgCM_UT_ST__ST__Free( &tgKB );
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__SO_ST_Find_String ------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SO_ST_Find_String )
{
    for (TgRSIZE uiSrc = 0; uiSrc < TgARRAY_COUNT(s_ambzTest); ++uiSrc)
    {
        for (TgRSIZE uiCmp = 0; uiCmp < TgARRAY_COUNT(s_ambzTest); ++uiCmp)
        {
            TgRSIZE_C                           nuiCmp_MaxTest = s_asTest_Length[uiCmp].m_nuiCharacters;
            TgRSIZE_C       uiRes0 = (uiSrc == uiCmp) ? nuiCmp_MaxTest * 0 : nuiCmp_MaxTest * 2;
            TgRSIZE_C       uiRes1 = (uiSrc == uiCmp) ? nuiCmp_MaxTest * 1 : nuiCmp_MaxTest * 2;
            TgRSIZE_C       uiRes2 = (uiSrc == uiCmp) ? nuiCmp_MaxTest * 2 : nuiCmp_MaxTest * 2;
            TgRSIZE_C       uiRes3 = (uiSrc == uiCmp) ? nuiCmp_MaxTest * 3 : KTgMAX_RSIZE;

            STg2_UT_ST__ST                      tgKA, tgKB;
            STg1_Text_Length                    sOffset;

            tgCM_UT_ST__ST__SZ_Init( &tgKA, s_ambzTest[uiSrc] );

            tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[uiCmp] );
            tgCM_UT_ST__ST__SZ_Append( &tgKB, s_ambzTest[uiCmp] );
            tgCM_UT_ST__ST__SZ_Append( &tgKB, s_ambzTest[uiSrc] );
            tgCM_UT_ST__ST__SZ_Append( &tgKB, s_ambzTest[uiCmp] );

            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SO_ST_Find_String( &sOffset, &tgKB, nuiCmp_MaxTest * 0, &tgKA ));
            Test__Expect_EQ(uiRes0, sOffset.m_nuiCharacters);

            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SO_ST_Find_String( &sOffset, &tgKB, nuiCmp_MaxTest * 1, &tgKA ));
            Test__Expect_EQ(uiRes1, sOffset.m_nuiCharacters);

            Test__Expect_EQ(KTgMAX_RSIZE == uiRes2 ? KTgE_FAIL : KTgS_OK, tgCM_UT_ST__ST__SO_ST_Find_String( &sOffset, &tgKB, nuiCmp_MaxTest * 2, &tgKA ));
            Test__Expect_EQ(uiRes2, KTgMAX_RSIZE == uiRes2 ? KTgMAX_RSIZE : sOffset.m_nuiCharacters);

            Test__Expect_EQ(KTgMAX_RSIZE == uiRes3 ? KTgE_FAIL : KTgS_OK, tgCM_UT_ST__ST__SO_ST_Find_String( &sOffset, &tgKB, nuiCmp_MaxTest * 3, &tgKA ));
            Test__Expect_EQ(uiRes3, KTgMAX_RSIZE == uiRes3 ? KTgMAX_RSIZE : sOffset.m_nuiCharacters);

            tgCM_UT_ST__ST__Free( &tgKA );
            tgCM_UT_ST__ST__Free( &tgKB );
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__SO_SF_Find_String ------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SO_SF_Find_String )
{
    for (TgRSIZE uiSrc = 0; uiSrc < TgARRAY_COUNT(s_ambzTest); ++uiSrc)
    {
        TgRSIZE_C                           nuiSrc_MaxTest = s_asTest_Length[uiSrc].m_nuiCharacters;

        for (TgRSIZE uiCmp = 0; uiCmp < TgARRAY_COUNT(s_ambzTest); ++uiCmp)
        {
            STg2_UT_ST__ST                      tgKA, tgKB, tgKC;
            STg1_Text_Length                    sOffset;

            TgRSIZE_C                           nuiCmp_MaxTest = s_asTest_Length[uiCmp].m_nuiCharacters;
            TgRSIZE_C       uiRes0 = (uiSrc == uiCmp) ? nuiCmp_MaxTest * 0 : nuiCmp_MaxTest * 2;
            TgRSIZE_C       uiRes1 = (uiSrc == uiCmp) ? nuiCmp_MaxTest * 1 : nuiCmp_MaxTest * 2;
            TgRSIZE_C       uiRes2 = (uiSrc == uiCmp) ? nuiCmp_MaxTest * 2 : nuiCmp_MaxTest * 2;
            TgRSIZE_C       uiRes3 = (uiSrc == uiCmp) ? nuiCmp_MaxTest * 3 : KTgMAX_RSIZE;

            tgCM_UT_ST__ST__SZ_Init( &tgKA, s_ambzTest[uiSrc] );

            tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[uiCmp] );
            tgCM_UT_ST__ST__SZ_Append( &tgKB, s_ambzTest[uiCmp] );
            tgCM_UT_ST__ST__SZ_Append( &tgKB, s_ambzTest[uiSrc] );
            tgCM_UT_ST__ST__SZ_Append( &tgKB, s_ambzTest[uiCmp] );

            tgCM_UT_ST__ST__SZ_Init( &tgKC, s_ambzTest[uiSrc] );
            tgCM_UT_ST__ST__SZ_Append( &tgKC, s_ambzTest[uiSrc] );


            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SO_SF_Find_String( &sOffset, &tgKB, nuiCmp_MaxTest * 0, &tgKA, 0, nuiSrc_MaxTest ));
            Test__Expect_EQ(uiRes0, sOffset.m_nuiCharacters);

            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SO_SF_Find_String( &sOffset, &tgKB, nuiCmp_MaxTest * 1, &tgKA, 0, nuiSrc_MaxTest ));
            Test__Expect_EQ(uiRes1, sOffset.m_nuiCharacters);

            Test__Expect_EQ(KTgMAX_RSIZE == uiRes2 ? KTgE_FAIL : KTgS_OK, tgCM_UT_ST__ST__SO_SF_Find_String( &sOffset, &tgKB, nuiCmp_MaxTest * 2, &tgKA, 0, nuiSrc_MaxTest ));
            Test__Expect_EQ(uiRes2, KTgMAX_RSIZE == uiRes2 ? KTgMAX_RSIZE : sOffset.m_nuiCharacters);

            Test__Expect_EQ(KTgMAX_RSIZE == uiRes3 ? KTgE_FAIL : KTgS_OK, tgCM_UT_ST__ST__SO_SF_Find_String( &sOffset, &tgKB, nuiCmp_MaxTest * 3, &tgKA, 0, nuiSrc_MaxTest ));
            Test__Expect_EQ(uiRes3, KTgMAX_RSIZE == uiRes3 ? KTgMAX_RSIZE : sOffset.m_nuiCharacters);


            if (uiSrc != uiCmp)
            {
                Test__Expect_NE(KTgS_OK, tgCM_UT_ST__ST__SO_SF_Find_String( &sOffset, &tgKB, nuiCmp_MaxTest * 1, &tgKC, 0, nuiSrc_MaxTest*2 ));

                Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SO_SF_Find_String( &sOffset, &tgKB, nuiCmp_MaxTest * 1, &tgKC, nuiSrc_MaxTest, nuiSrc_MaxTest ));
                Test__Expect_EQ(uiRes1, sOffset.m_nuiCharacters);
                
                Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SO_SF_Find_String( &sOffset, &tgKB, nuiCmp_MaxTest * 1, &tgKC, 0, nuiSrc_MaxTest ));
                Test__Expect_EQ(uiRes1, sOffset.m_nuiCharacters);
            };


            tgCM_UT_ST__ST__Free( &tgKA );
            tgCM_UT_ST__ST__Free( &tgKB );
            tgCM_UT_ST__ST__Free( &tgKC );
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__SO_SZ_Find_Set ---------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SO_SZ_Find_Set )
{
    TgCHAR_U8_C                         mbzTest_0[] = KTgU8_LIT_TEST__BURMESE;
    TgCHAR_U8_C                         mbzTest_A[] = u8"\U0000103a";
    TgCHAR_U8_C                         mbzTest_1[] = u8"AbCdEfGhIjKlMnOpQrStUvWxYz";
    TgCHAR_U8_C                         mbzTest_B[] = u8"dKt";

    STg2_UT_ST__ST                      tgKA, tgKB;
    TgCHAR_U8_CP                        mbzKA;
    STg1_Text_Length                    sOffset;

    tgCM_UT_ST__ST__SZ_Init( &tgKA, mbzTest_A );
    mbzKA = tgCM_UT_ST__ST__Query_String( &tgKA );
    tgCM_UT_ST__ST__SZ_Init( &tgKB, mbzTest_0 );

    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SO_SZ_Find_Set( &sOffset, &tgKB, 0, mbzKA ));
    Test__Expect_EQ((TgRSIZE)2, sOffset.m_nuiCharacters);

    Test__Expect_NE(KTgS_OK, tgCM_UT_ST__ST__SO_SZ_Find_Set( &sOffset, &tgKB, 0, u8"" ));

    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SO_SZ_Find_Set( &sOffset, &tgKB, 0, u8"\U00001005" ));
    Test__Expect_EQ((TgRSIZE)0, sOffset.m_nuiCharacters);

    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SO_SZ_Find_Set( &sOffset, &tgKB, 0, u8"\U00001019" ));
    Test__Expect_EQ((TgRSIZE)1, sOffset.m_nuiCharacters);

    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SO_SZ_Find_Set( &sOffset, &tgKB, 1, u8"\U00001019" ));
    Test__Expect_EQ((TgRSIZE)1, sOffset.m_nuiCharacters);

    tgCM_UT_ST__ST__Free( &tgKA );
    tgCM_UT_ST__ST__Free( &tgKB );



    tgCM_UT_ST__ST__SZ_Init( &tgKA, mbzTest_B );
    mbzKA = tgCM_UT_ST__ST__Query_String( &tgKA );
    tgCM_UT_ST__ST__SZ_Init( &tgKB, mbzTest_1 );

    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SO_SZ_Find_Set( &sOffset, &tgKB, 0, mbzKA ));
    Test__Expect_EQ((TgRSIZE)3, sOffset.m_nuiCharacters);

    tgCM_UT_ST__ST__Free( &tgKA );
    tgCM_UT_ST__ST__Free( &tgKB );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__SO_SN_Find_Set ---------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SO_SN_Find_Set )
{
    TgCHAR_U8_C                         mbzTest_0[] = KTgU8_LIT_TEST__BURMESE;
    TgCHAR_U8_C                         mbzTest_A[] = u8"\U0000103a";
    TgCHAR_U8_C                         mbzTest_1[] = u8"AbCdEfGhIjKlMnOpQrStUvWxYz";
    TgCHAR_U8_C                         mbzTest_B[] = u8"Ktd";

    STg2_UT_ST__ST                      tgKA, tgKB;
    TgCHAR_U8_CP                        mbzKA;
    STg1_Text_Length                    sOffset;

    tgCM_UT_ST__ST__SZ_Init( &tgKA, mbzTest_A );
    mbzKA = tgCM_UT_ST__ST__Query_String( &tgKA );
    tgCM_UT_ST__ST__SZ_Init( &tgKB, mbzTest_0 );

    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SO_SN_Find_Set( &sOffset, &tgKB, 0, mbzKA, 3 ));
    Test__Expect_EQ((TgRSIZE)2, sOffset.m_nuiCharacters);

    tgCM_UT_ST__ST__Free( &tgKA );
    tgCM_UT_ST__ST__Free( &tgKB );



    tgCM_UT_ST__ST__SZ_Init( &tgKA, mbzTest_B );
    mbzKA = tgCM_UT_ST__ST__Query_String( &tgKA );
    tgCM_UT_ST__ST__SZ_Init( &tgKB, mbzTest_1 );

    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SO_SN_Find_Set( &sOffset, &tgKB, 0, mbzKA, 3 ));
    Test__Expect_EQ((TgRSIZE)3, sOffset.m_nuiCharacters);

    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SO_SN_Find_Set( &sOffset, &tgKB, 0, mbzKA, 2 ));
    Test__Expect_EQ((TgRSIZE)10, sOffset.m_nuiCharacters);

    tgCM_UT_ST__ST__Free( &tgKA );
    tgCM_UT_ST__ST__Free( &tgKB );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__SO_ST_Find_Set ---------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SO_ST_Find_Set )
{
    TgCHAR_U8_C                         mbzTest_0[] = KTgU8_LIT_TEST__BURMESE;
    TgCHAR_U8_C                         mbzTest_A[] = u8"\U0000103a";
    TgCHAR_U8_C                         mbzTest_1[] = u8"AbCdEfGhIjKlMnOpQrStUvWxYz";
    TgCHAR_U8_C                         mbzTest_B[] = u8"Ktd";

    STg2_UT_ST__ST                      tgKA, tgKB;
    STg1_Text_Length                    sOffset;

    tgCM_UT_ST__ST__SZ_Init( &tgKA, mbzTest_A );
    tgCM_UT_ST__ST__SZ_Init( &tgKB, mbzTest_0 );

    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SO_ST_Find_Set( &sOffset, &tgKB, 0, &tgKA ));
    Test__Expect_EQ((TgRSIZE)2, sOffset.m_nuiCharacters);

    tgCM_UT_ST__ST__Free( &tgKA );
    tgCM_UT_ST__ST__Free( &tgKB );



    tgCM_UT_ST__ST__SZ_Init( &tgKA, mbzTest_B );
    tgCM_UT_ST__ST__SZ_Init( &tgKB, mbzTest_1 );

    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SO_ST_Find_Set( &sOffset, &tgKB, 0, &tgKA ));
    Test__Expect_EQ((TgRSIZE)3, sOffset.m_nuiCharacters);

    tgCM_UT_ST__ST__Free( &tgKA );
    tgCM_UT_ST__ST__Free( &tgKB );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__SO_SZ_Find_Not_Set ------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SO_SZ_Find_Not_Set )
{
    TgCHAR_U8_C                         mbzTest_0[] = KTgU8_LIT_TEST__BURMESE;
    TgCHAR_U8_C                         mbzTest_A[] = u8"\U00001005";
    TgCHAR_U8_C                         mbzTest_1[] = u8"AbCdEfGhIjKlMnOpQrStUvWxYz";
    TgCHAR_U8_C                         mbzTest_B[] = u8"Ab";

    STg2_UT_ST__ST                      tgKA, tgKB;
    TgCHAR_U8_CP                        mbzKA;
    STg1_Text_Length                    sOffset;

    tgCM_UT_ST__ST__SZ_Init( &tgKA, mbzTest_A );
    mbzKA = tgCM_UT_ST__ST__Query_String( &tgKA );
    tgCM_UT_ST__ST__SZ_Init( &tgKB, mbzTest_0 );

    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SO_SZ_Find_Not_Set( &sOffset, &tgKB, 0, mbzKA ));
    Test__Expect_EQ((TgRSIZE)1, sOffset.m_nuiCharacters);

    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SO_SZ_Find_Not_Set( &sOffset, &tgKB, 0, u8"" ));
    Test__Expect_EQ((TgRSIZE)0, sOffset.m_nuiCharacters);

    tgCM_UT_ST__ST__Free( &tgKA );
    tgCM_UT_ST__ST__Free( &tgKB );



    tgCM_UT_ST__ST__SZ_Init( &tgKA, mbzTest_B );
    mbzKA = tgCM_UT_ST__ST__Query_String( &tgKA );
    tgCM_UT_ST__ST__SZ_Init( &tgKB, mbzTest_1 );

    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SO_SZ_Find_Not_Set( &sOffset, &tgKB, 0, mbzKA ));
    Test__Expect_EQ((TgRSIZE)2, sOffset.m_nuiCharacters);

    tgCM_UT_ST__ST__Free( &tgKA );
    tgCM_UT_ST__ST__Free( &tgKB );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__SO_SN_Find_Not_Set ------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SO_SN_Find_Not_Set )
{
    TgCHAR_U8_C                         mbzTest_0[] = KTgU8_LIT_TEST__BURMESE;
    TgCHAR_U8_C                         mbzTest_A[] = u8"\U00001005";
    TgCHAR_U8_C                         mbzTest_1[] = u8"AbCdEfGhIjKlMnOpQrStUvWxYz";
    TgCHAR_U8_C                         mbzTest_B[] = u8"Ab";

    STg2_UT_ST__ST                      tgKA, tgKB;
    TgCHAR_U8_CP                        mbzKA;
    STg1_Text_Length                    sOffset;

    tgCM_UT_ST__ST__SZ_Init( &tgKA, mbzTest_A );
    mbzKA = tgCM_UT_ST__ST__Query_String( &tgKA );
    tgCM_UT_ST__ST__SZ_Init( &tgKB, mbzTest_0 );

    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SO_SN_Find_Not_Set( &sOffset, &tgKB, 0, mbzKA, 3 ));
    Test__Expect_EQ((TgRSIZE)1, sOffset.m_nuiCharacters);

    tgCM_UT_ST__ST__Free( &tgKA );
    tgCM_UT_ST__ST__Free( &tgKB );



    tgCM_UT_ST__ST__SZ_Init( &tgKA, mbzTest_B );
    mbzKA = tgCM_UT_ST__ST__Query_String( &tgKA );
    tgCM_UT_ST__ST__SZ_Init( &tgKB, mbzTest_1 );

    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SO_SN_Find_Not_Set(  &sOffset, &tgKB, 0, mbzKA, 2 ));
    Test__Expect_EQ((TgRSIZE)2, sOffset.m_nuiCharacters);

    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SO_SN_Find_Not_Set(  &sOffset, &tgKB, 0, mbzKA, 1 ));
    Test__Expect_EQ((TgRSIZE)1, sOffset.m_nuiCharacters);

    tgCM_UT_ST__ST__Free( &tgKA );
    tgCM_UT_ST__ST__Free( &tgKB );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__SO_ST_Find_Not_Set ------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SO_ST_Find_Not_Set )
{
    TgCHAR_U8_C                         mbzTest_0[] = KTgU8_LIT_TEST__BURMESE;
    TgCHAR_U8_C                         mbzTest_A[] = u8"\U00001005";
    TgCHAR_U8_C                         mbzTest_1[] = u8"AbCdEfGhIjKlMnOpQrStUvWxYz";
    TgCHAR_U8_C                         mbzTest_B[] = u8"Ab";

    STg2_UT_ST__ST                      tgKA, tgKB;
    STg1_Text_Length                    sOffset;

    tgCM_UT_ST__ST__SZ_Init( &tgKA, mbzTest_A );
    tgCM_UT_ST__ST__SZ_Init( &tgKB, mbzTest_0 );

    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SO_ST_Find_Not_Set( &sOffset, &tgKB, 0, &tgKA ));
    Test__Expect_EQ((TgRSIZE)1, sOffset.m_nuiCharacters);

    tgCM_UT_ST__ST__Free( &tgKA );
    tgCM_UT_ST__ST__Free( &tgKB );



    tgCM_UT_ST__ST__SZ_Init( &tgKA, mbzTest_B );
    tgCM_UT_ST__ST__SZ_Init( &tgKB, mbzTest_1 );

    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SO_ST_Find_Not_Set( &sOffset, &tgKB, 0, &tgKA ));
    Test__Expect_EQ((TgRSIZE)2, sOffset.m_nuiCharacters);

    tgCM_UT_ST__ST__Free( &tgKA );
    tgCM_UT_ST__ST__Free( &tgKB );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__SO_SZ_RFind_String ------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SO_SZ_RFind_String )
{
    for (TgRSIZE uiSrc = 0; uiSrc < TgARRAY_COUNT(s_ambzTest); ++uiSrc)
    {
        for (TgRSIZE uiCmp = 0; uiCmp < TgARRAY_COUNT(s_ambzTest); ++uiCmp)
        {
            TgRSIZE_C                           nuiCmp_MaxTest = s_asTest_Length[uiCmp].m_nuiCharacters;
            TgRSIZE_C       uiRes0 = (uiSrc == uiCmp) ? nuiCmp_MaxTest * 3 : nuiCmp_MaxTest * 2;
            TgRSIZE_C       uiRes1 = (uiSrc == uiCmp) ? nuiCmp_MaxTest * 2 : nuiCmp_MaxTest * 2;
            TgRSIZE_C       uiRes2 = (uiSrc == uiCmp) ? nuiCmp_MaxTest * 1 : KTgMAX_RSIZE;
            TgRSIZE_C       uiRes3 = (uiSrc == uiCmp) ? nuiCmp_MaxTest * 0 : KTgMAX_RSIZE;

            STg2_UT_ST__ST                      tgKA, tgKB;
            TgCHAR_U8_CP                        mbzKA;
            STg1_Text_Length                    sOffset;

            tgCM_UT_ST__ST__SZ_Init( &tgKA, s_ambzTest[uiSrc] );
            mbzKA = tgCM_UT_ST__ST__Query_String( &tgKA );

            tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[uiCmp] );
            tgCM_UT_ST__ST__SZ_Append( &tgKB, s_ambzTest[uiCmp] );
            tgCM_UT_ST__ST__SZ_Append( &tgKB, s_ambzTest[uiSrc] );
            tgCM_UT_ST__ST__SZ_Append( &tgKB, s_ambzTest[uiCmp] );

            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SO_SZ_RFind_String( &sOffset, &tgKB, nuiCmp_MaxTest * 0, mbzKA ));
            Test__Expect_EQ(uiRes0, sOffset.m_nuiCharacters);

            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SO_SZ_RFind_String( &sOffset, &tgKB, nuiCmp_MaxTest * 1, mbzKA ));
            Test__Expect_EQ(uiRes1, sOffset.m_nuiCharacters);

            Test__Expect_EQ(KTgMAX_RSIZE == uiRes2 ? KTgE_FAIL : KTgS_OK, tgCM_UT_ST__ST__SO_SZ_RFind_String( &sOffset, &tgKB, nuiCmp_MaxTest * 2, mbzKA ));
            Test__Expect_EQ(uiRes2, KTgMAX_RSIZE == uiRes2 ? KTgMAX_RSIZE : sOffset.m_nuiCharacters);

            Test__Expect_EQ(KTgMAX_RSIZE == uiRes3 ? KTgE_FAIL : KTgS_OK, tgCM_UT_ST__ST__SO_SZ_RFind_String( &sOffset, &tgKB, nuiCmp_MaxTest * 3, mbzKA ));
            Test__Expect_EQ(uiRes3, KTgMAX_RSIZE == uiRes3 ? KTgMAX_RSIZE : sOffset.m_nuiCharacters);

            tgCM_UT_ST__ST__Free( &tgKA );
            tgCM_UT_ST__ST__Free( &tgKB );
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__SO_SN_RFind_String ------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SO_SN_RFind_String )
{
    for (TgRSIZE uiSrc = 0; uiSrc < TgARRAY_COUNT(s_ambzTest); ++uiSrc)
    {
        TgRSIZE_C                           nbySrc_MaxTest = s_asTest_Length[uiSrc].m_nbyCharacters;

        for (TgRSIZE uiCmp = 0; uiCmp < TgARRAY_COUNT(s_ambzTest); ++uiCmp)
        {
            TgRSIZE_C                           nuiCmp_MaxTest = s_asTest_Length[uiCmp].m_nuiCharacters;
            TgRSIZE_C       uiRes0 = (uiSrc == uiCmp) ? nuiCmp_MaxTest * 3 : nuiCmp_MaxTest * 2;
            TgRSIZE_C       uiRes1 = (uiSrc == uiCmp) ? nuiCmp_MaxTest * 2 : nuiCmp_MaxTest * 2;
            TgRSIZE_C       uiRes2 = (uiSrc == uiCmp) ? nuiCmp_MaxTest * 1 : KTgMAX_RSIZE;
            TgRSIZE_C       uiRes3 = (uiSrc == uiCmp) ? nuiCmp_MaxTest * 0 : KTgMAX_RSIZE;

            STg2_UT_ST__ST                      tgKA, tgKB;
            TgCHAR_U8_CP                        mbzKA;
            STg1_Text_Length                    sOffset;

            tgCM_UT_ST__ST__SZ_Init( &tgKA, s_ambzTest[uiSrc] );
            mbzKA = tgCM_UT_ST__ST__Query_String( &tgKA );

            tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[uiCmp] );
            tgCM_UT_ST__ST__SZ_Append( &tgKB, s_ambzTest[uiCmp] );
            tgCM_UT_ST__ST__SZ_Append( &tgKB, s_ambzTest[uiSrc] );
            tgCM_UT_ST__ST__SZ_Append( &tgKB, s_ambzTest[uiCmp] );

            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SO_SN_RFind_String( &sOffset, &tgKB, nuiCmp_MaxTest * 0, mbzKA, nbySrc_MaxTest ));
            Test__Expect_EQ(uiRes0, sOffset.m_nuiCharacters);

            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SO_SN_RFind_String( &sOffset, &tgKB, nuiCmp_MaxTest * 1, mbzKA, nbySrc_MaxTest ));
            Test__Expect_EQ(uiRes1, sOffset.m_nuiCharacters);

            Test__Expect_EQ(KTgMAX_RSIZE == uiRes2 ? KTgE_FAIL : KTgS_OK, tgCM_UT_ST__ST__SO_SN_RFind_String( &sOffset, &tgKB, nuiCmp_MaxTest * 2, mbzKA, nbySrc_MaxTest ));
            Test__Expect_EQ(uiRes2, KTgMAX_RSIZE == uiRes2 ? KTgMAX_RSIZE : sOffset.m_nuiCharacters);

            Test__Expect_EQ(KTgMAX_RSIZE == uiRes3 ? KTgE_FAIL : KTgS_OK, tgCM_UT_ST__ST__SO_SN_RFind_String( &sOffset, &tgKB, nuiCmp_MaxTest * 3, mbzKA, nbySrc_MaxTest ));
            Test__Expect_EQ(uiRes3, KTgMAX_RSIZE == uiRes3 ? KTgMAX_RSIZE : sOffset.m_nuiCharacters);

            tgCM_UT_ST__ST__Free( &tgKA );
            tgCM_UT_ST__ST__Free( &tgKB );
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__SO_ST_RFind_String ------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SO_ST_RFind_String )
{
    for (TgRSIZE uiSrc = 0; uiSrc < TgARRAY_COUNT(s_ambzTest); ++uiSrc)
    {
        for (TgRSIZE uiCmp = 0; uiCmp < TgARRAY_COUNT(s_ambzTest); ++uiCmp)
        {
            TgRSIZE_C                           nuiCmp_MaxTest = s_asTest_Length[uiCmp].m_nuiCharacters;
            TgRSIZE_C       uiRes0 = (uiSrc == uiCmp) ? nuiCmp_MaxTest * 3 : nuiCmp_MaxTest * 2;
            TgRSIZE_C       uiRes1 = (uiSrc == uiCmp) ? nuiCmp_MaxTest * 2 : nuiCmp_MaxTest * 2;
            TgRSIZE_C       uiRes2 = (uiSrc == uiCmp) ? nuiCmp_MaxTest * 1 : KTgMAX_RSIZE;
            TgRSIZE_C       uiRes3 = (uiSrc == uiCmp) ? nuiCmp_MaxTest * 0 : KTgMAX_RSIZE;

            STg2_UT_ST__ST                      tgKA, tgKB;
            TgCHAR_U8_CP                        mbzKA;
            STg1_Text_Length                    sOffset;

            tgCM_UT_ST__ST__SZ_Init( &tgKA, s_ambzTest[uiSrc] );
            mbzKA = tgCM_UT_ST__ST__Query_String( &tgKA );

            tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[uiCmp] );
            tgCM_UT_ST__ST__SZ_Append( &tgKB, s_ambzTest[uiCmp] );
            tgCM_UT_ST__ST__SZ_Append( &tgKB, s_ambzTest[uiSrc] );
            tgCM_UT_ST__ST__SZ_Append( &tgKB, s_ambzTest[uiCmp] );

            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SO_ST_RFind_String( &sOffset, &tgKB, nuiCmp_MaxTest * 0, &tgKA ));
            Test__Expect_EQ(uiRes0, sOffset.m_nuiCharacters);

            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SO_ST_RFind_String( &sOffset, &tgKB, nuiCmp_MaxTest * 1, &tgKA ));
            Test__Expect_EQ(uiRes1, sOffset.m_nuiCharacters);

            Test__Expect_EQ(KTgMAX_RSIZE == uiRes2 ? KTgE_FAIL : KTgS_OK, tgCM_UT_ST__ST__SO_ST_RFind_String( &sOffset, &tgKB, nuiCmp_MaxTest * 2, &tgKA ));
            Test__Expect_EQ(uiRes2, KTgMAX_RSIZE == uiRes2 ? KTgMAX_RSIZE : sOffset.m_nuiCharacters);

            Test__Expect_EQ(KTgMAX_RSIZE == uiRes3 ? KTgE_FAIL : KTgS_OK, tgCM_UT_ST__ST__SO_ST_RFind_String( &sOffset, &tgKB, nuiCmp_MaxTest * 3, &tgKA ));
            Test__Expect_EQ(uiRes3, KTgMAX_RSIZE == uiRes3 ? KTgMAX_RSIZE : sOffset.m_nuiCharacters);

            tgCM_UT_ST__ST__Free( &tgKA );
            tgCM_UT_ST__ST__Free( &tgKB );
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__SO_SF_RFind_String ------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SO_SF_RFind_String )
{
    for (TgRSIZE uiSrc = 0; uiSrc < TgARRAY_COUNT(s_ambzTest); ++uiSrc)
    {
        TgRSIZE_C                           nuiSrc_MaxTest = s_asTest_Length[uiSrc].m_nuiCharacters;

        for (TgRSIZE uiCmp = 0; uiCmp < TgARRAY_COUNT(s_ambzTest); ++uiCmp)
        {
            TgRSIZE_C                           nuiCmp_MaxTest = s_asTest_Length[uiCmp].m_nuiCharacters;
            TgRSIZE_C       uiRes0 = (uiSrc == uiCmp) ? nuiCmp_MaxTest * 3 : nuiCmp_MaxTest * 2;
            TgRSIZE_C       uiRes1 = (uiSrc == uiCmp) ? nuiCmp_MaxTest * 2 : nuiCmp_MaxTest * 2;
            TgRSIZE_C       uiRes2 = (uiSrc == uiCmp) ? nuiCmp_MaxTest * 1 : KTgMAX_RSIZE;
            TgRSIZE_C       uiRes3 = (uiSrc == uiCmp) ? nuiCmp_MaxTest * 0 : KTgMAX_RSIZE;

            STg2_UT_ST__ST                      tgKA, tgKB, tgKC;
            STg1_Text_Length                    sOffset;

            tgCM_UT_ST__ST__SZ_Init( &tgKA, s_ambzTest[uiSrc] );

            tgCM_UT_ST__ST__SZ_Init( &tgKB, s_ambzTest[uiCmp] );
            tgCM_UT_ST__ST__SZ_Append( &tgKB, s_ambzTest[uiCmp] );
            tgCM_UT_ST__ST__SZ_Append( &tgKB, s_ambzTest[uiSrc] );
            tgCM_UT_ST__ST__SZ_Append( &tgKB, s_ambzTest[uiCmp] );

            tgCM_UT_ST__ST__SZ_Init( &tgKC, s_ambzTest[uiSrc] );
            tgCM_UT_ST__ST__SZ_Append( &tgKC, s_ambzTest[uiSrc] );

            
            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SO_SF_RFind_String( &sOffset, &tgKB, nuiCmp_MaxTest * 0, &tgKA, 0, nuiSrc_MaxTest  ));
            Test__Expect_EQ(uiRes0, sOffset.m_nuiCharacters);

            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SO_SF_RFind_String( &sOffset, &tgKB, nuiCmp_MaxTest * 1, &tgKA, 0, nuiSrc_MaxTest  ));
            Test__Expect_EQ(uiRes1, sOffset.m_nuiCharacters);

            Test__Expect_EQ(KTgMAX_RSIZE == uiRes2 ? KTgE_FAIL : KTgS_OK, tgCM_UT_ST__ST__SO_SF_RFind_String( &sOffset, &tgKB, nuiCmp_MaxTest * 2, &tgKA, 0, nuiSrc_MaxTest  ));
            Test__Expect_EQ(uiRes2, KTgMAX_RSIZE == uiRes2 ? KTgMAX_RSIZE : sOffset.m_nuiCharacters);

            Test__Expect_EQ(KTgMAX_RSIZE == uiRes3 ? KTgE_FAIL : KTgS_OK, tgCM_UT_ST__ST__SO_SF_RFind_String( &sOffset, &tgKB, nuiCmp_MaxTest * 3, &tgKA, 0, nuiSrc_MaxTest  ));
            Test__Expect_EQ(uiRes3, KTgMAX_RSIZE == uiRes3 ? KTgMAX_RSIZE : sOffset.m_nuiCharacters);

            
            
            if (uiSrc != uiCmp)
            {
                Test__Expect_NE(KTgS_OK, tgCM_UT_ST__ST__SO_SF_RFind_String( &sOffset, &tgKB, nuiCmp_MaxTest * 1, &tgKC, 0, nuiSrc_MaxTest*2 ));

                Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SO_SF_RFind_String( &sOffset, &tgKB, nuiCmp_MaxTest * 1, &tgKC, nuiSrc_MaxTest, nuiSrc_MaxTest ));
                Test__Expect_EQ(uiRes1, sOffset.m_nuiCharacters);
                
                Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SO_SF_RFind_String( &sOffset, &tgKB, nuiCmp_MaxTest * 1, &tgKC, 0, nuiSrc_MaxTest ));
                Test__Expect_EQ(uiRes1, sOffset.m_nuiCharacters);
            };


            tgCM_UT_ST__ST__Free( &tgKA );
            tgCM_UT_ST__ST__Free( &tgKB );
            tgCM_UT_ST__ST__Free( &tgKC );
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__SO_SZ_RFind_Set --------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SO_SZ_RFind_Set )
{
    TgCHAR_U8_C                         mbzTest_0[] = KTgU8_LIT_TEST__BURMESE;
    TgCHAR_U8_C                         mbzTest_1[] = u8"AbCdEfGhIjKlMnOpQrStUvWxYz";

    STg2_UT_ST__ST                      tgKA, tgKB;
    STg1_Text_Length                    sOffset;

    tgCM_UT_ST__ST__SZ_Init( &tgKA, u8"" );
    Test__Expect_NE(KTgS_OK, tgCM_UT_ST__ST__SO_SZ_RFind_Set( &sOffset, &tgKA, 0, u8"" ));
    tgCM_UT_ST__ST__Free( &tgKA );



    tgCM_UT_ST__ST__SZ_Init( &tgKB, mbzTest_0 );

    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SO_SZ_RFind_Set( &sOffset, &tgKB, 0, u8"\U0000102f" ));
    Test__Expect_EQ((TgRSIZE)9, sOffset.m_nuiCharacters);

    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SO_SZ_RFind_Set( &sOffset, &tgKB, 0, u8"\U0000103e" ));
    Test__Expect_EQ((TgRSIZE)8, sOffset.m_nuiCharacters);

    Test__Expect_NE(KTgS_OK, tgCM_UT_ST__ST__SO_SZ_RFind_Set( &sOffset, &tgKB, 0, u8"" ));

    tgCM_UT_ST__ST__Free( &tgKB );



    tgCM_UT_ST__ST__SZ_Init( &tgKB, mbzTest_1 );

    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SO_SZ_RFind_Set( &sOffset, &tgKB, 0, u8"xUQ" ));
    Test__Expect_EQ((TgRSIZE)23, sOffset.m_nuiCharacters);

    tgCM_UT_ST__ST__Free( &tgKB );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__SO_SN_RFind_Set --------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SO_SN_RFind_Set )
{
    TgCHAR_U8_C                         mbzTest_0[] = KTgU8_LIT_TEST__BURMESE;
    TgCHAR_U8_C                         mbzTest_A[] = u8"\U0000102f";
    TgCHAR_U8_C                         mbzTest_1[] = u8"AbCdEfGhIjKlMnOpQrStUvWxYz";
    TgCHAR_U8_C                         mbzTest_B[] = u8"UQx";

    STg2_UT_ST__ST                      tgKA, tgKB;
    TgCHAR_U8_CP                        mbzKA;
    STg1_Text_Length                    sOffset;

    tgCM_UT_ST__ST__SZ_Init( &tgKA, mbzTest_A );
    mbzKA = tgCM_UT_ST__ST__Query_String( &tgKA );
    tgCM_UT_ST__ST__SZ_Init( &tgKB, mbzTest_0 );

    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SO_SN_RFind_Set( &sOffset, &tgKB, 0, mbzKA, 3 ));
    Test__Expect_EQ((TgRSIZE)9, sOffset.m_nuiCharacters);

    Test__Expect_NE(KTgS_OK, tgCM_UT_ST__ST__SO_SN_RFind_Set( &sOffset, &tgKB, 0, u8"", 0 ));

    tgCM_UT_ST__ST__Free( &tgKA );
    tgCM_UT_ST__ST__Free( &tgKB );



    tgCM_UT_ST__ST__SZ_Init( &tgKA, mbzTest_B );
    mbzKA = tgCM_UT_ST__ST__Query_String( &tgKA );
    tgCM_UT_ST__ST__SZ_Init( &tgKB, mbzTest_1 );

    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SO_SN_RFind_Set( &sOffset, &tgKB, 0, mbzKA, 3 ));
    Test__Expect_EQ((TgRSIZE)23, sOffset.m_nuiCharacters);

    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SO_SN_RFind_Set( &sOffset, &tgKB, 0, mbzKA, 2 ));
    Test__Expect_EQ((TgRSIZE)20, sOffset.m_nuiCharacters);

    tgCM_UT_ST__ST__Free( &tgKA );
    tgCM_UT_ST__ST__Free( &tgKB );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__SO_ST_RFind_Set --------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SO_ST_RFind_Set )
{
    TgCHAR_U8_C                         mbzTest_0[] = KTgU8_LIT_TEST__BURMESE;
    TgCHAR_U8_C                         mbzTest_A[] = u8"\U0000102f";
    TgCHAR_U8_C                         mbzTest_1[] = u8"AbCdEfGhIjKlMnOpQrStUvWxYz";
    TgCHAR_U8_C                         mbzTest_B[] = u8"xUQ";

    STg2_UT_ST__ST                      tgKA, tgKB;
    TgCHAR_U8_CP                        mbzKA;
    STg1_Text_Length                    sOffset;

    tgCM_UT_ST__ST__SZ_Init( &tgKA, mbzTest_A );
    mbzKA = tgCM_UT_ST__ST__Query_String( &tgKA );
    tgCM_UT_ST__ST__SZ_Init( &tgKB, mbzTest_0 );

    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SO_ST_RFind_Set( &sOffset, &tgKB, 0, &tgKA ));
    Test__Expect_EQ((TgRSIZE)9, sOffset.m_nuiCharacters);

    tgCM_UT_ST__ST__Free( &tgKA );
    tgCM_UT_ST__ST__Free( &tgKB );



    tgCM_UT_ST__ST__SZ_Init( &tgKA, mbzTest_B );
    mbzKA = tgCM_UT_ST__ST__Query_String( &tgKA );
    tgCM_UT_ST__ST__SZ_Init( &tgKB, mbzTest_1 );

    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SO_ST_RFind_Set( &sOffset, &tgKB, 0, &tgKA ));
    Test__Expect_EQ((TgRSIZE)23, sOffset.m_nuiCharacters);

    tgCM_UT_ST__ST__Free( &tgKA );
    tgCM_UT_ST__ST__Free( &tgKB );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__SO_SZ_RFind_Not_Set ----------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SO_SZ_RFind_Not_Set )
{
    TgCHAR_U8_C                         mbzTest_0[] = KTgU8_LIT_TEST__BURMESE;
    TgCHAR_U8_C                         mbzTest_1[] = u8"AbCdEfGhIjKlMnOpQrStUvWxYz";

    STg2_UT_ST__ST                      tgKB;
    STg1_Text_Length                    sOffset;

    tgCM_UT_ST__ST__SZ_Init( &tgKB, mbzTest_0 );

    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SO_SZ_RFind_Not_Set( &sOffset, &tgKB, 0, u8"\U0000103e\U0000102f" ));
    Test__Expect_EQ((TgRSIZE)7, sOffset.m_nuiCharacters);

    tgCM_UT_ST__ST__Free( &tgKB );



    tgCM_UT_ST__ST__SZ_Init( &tgKB, mbzTest_1 );

    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SO_SZ_RFind_Not_Set( &sOffset, &tgKB, 0, u8"zYxW" ));
    Test__Expect_EQ((TgRSIZE)21, sOffset.m_nuiCharacters);

    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SO_SZ_RFind_Not_Set( &sOffset, &tgKB, 0, u8"" ));
    Test__Expect_EQ((TgRSIZE)25, sOffset.m_nuiCharacters);

    tgCM_UT_ST__ST__Free( &tgKB );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__SO_SN_RFind_Not_Set ----------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SO_SN_RFind_Not_Set )
{
    TgCHAR_U8_C                         mbzTest_0[] = KTgU8_LIT_TEST__BURMESE;
    TgCHAR_U8_C                         mbzTest_A[] = u8"\U0000103e\U0000102f";
    TgCHAR_U8_C                         mbzTest_1[] = u8"AbCdEfGhIjKlMnOpQrStUvWxYz";
    TgCHAR_U8_C                         mbzTest_B[] = u8"zYxW";

    STg2_UT_ST__ST                      tgKA, tgKB;
    TgCHAR_U8_CP                        mbzKA;
    STg1_Text_Length                    sOffset;

    tgCM_UT_ST__ST__SZ_Init( &tgKA, mbzTest_A );
    mbzKA = tgCM_UT_ST__ST__Query_String( &tgKA );
    tgCM_UT_ST__ST__SZ_Init( &tgKB, mbzTest_0 );

    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SO_SN_RFind_Not_Set( &sOffset, &tgKB, 0, mbzKA, 6 ));
    Test__Expect_EQ((TgRSIZE)7, sOffset.m_nuiCharacters);

    tgCM_UT_ST__ST__Free( &tgKA );
    tgCM_UT_ST__ST__Free( &tgKB );



    tgCM_UT_ST__ST__SZ_Init( &tgKA, mbzTest_B );
    mbzKA = tgCM_UT_ST__ST__Query_String( &tgKA );
    tgCM_UT_ST__ST__SZ_Init( &tgKB, mbzTest_1 );

    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SO_SN_RFind_Not_Set( &sOffset, &tgKB, 0, mbzKA, 4 ));
    Test__Expect_EQ((TgRSIZE)21, sOffset.m_nuiCharacters);

    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SO_SN_RFind_Not_Set( &sOffset, &tgKB, 0, mbzKA, 3 ));
    Test__Expect_EQ((TgRSIZE)22, sOffset.m_nuiCharacters);

    tgCM_UT_ST__ST__Free( &tgKA );
    tgCM_UT_ST__ST__Free( &tgKB );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__SO_ST_RFind_Not_Set ----------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__SO_ST_RFind_Not_Set )
{
    TgCHAR_U8_C                         mbzTest_0[] = KTgU8_LIT_TEST__BURMESE;
    TgCHAR_U8_C                         mbzTest_A[] = u8"\U0000103e\U0000102f";
    TgCHAR_U8_C                         mbzTest_1[] = u8"AbCdEfGhIjKlMnOpQrStUvWxYz";
    TgCHAR_U8_C                         mbzTest_B[] = u8"zYxW";

    STg2_UT_ST__ST                      tgKA, tgKB;
    TgCHAR_U8_CP                        mbzKA;
    STg1_Text_Length                    sOffset;

    tgCM_UT_ST__ST__SZ_Init( &tgKA, mbzTest_A );
    mbzKA = tgCM_UT_ST__ST__Query_String( &tgKA );
    tgCM_UT_ST__ST__SZ_Init( &tgKB, mbzTest_0 );

    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SO_ST_RFind_Not_Set( &sOffset, &tgKB, 0, &tgKA ));
    Test__Expect_EQ((TgRSIZE)7, sOffset.m_nuiCharacters);

    tgCM_UT_ST__ST__Free( &tgKA );
    tgCM_UT_ST__ST__Free( &tgKB );



    tgCM_UT_ST__ST__SZ_Init( &tgKA, mbzTest_B );
    mbzKA = tgCM_UT_ST__ST__Query_String( &tgKA );
    tgCM_UT_ST__ST__SZ_Init( &tgKB, mbzTest_1 );

    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__ST__SO_ST_RFind_Not_Set( &sOffset, &tgKB, 0, &tgKA ));
    Test__Expect_EQ((TgRSIZE)21, sOffset.m_nuiCharacters);

    tgCM_UT_ST__ST__Free( &tgKA );
    tgCM_UT_ST__ST__Free( &tgKB );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__Trim_Start_Set ---------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__Trim_Start_Set )
{
    TgRSIZE                             uiIndex2, uiSize, uiCheck;/*, uiIndex, nbyTest, uiSrc_Start, uiSrc_End; */
    STg2_UT_ST__ST                      tgKB;
    TgCHAR_U8_CP                        mbzKB;
    TgCHAR_U8_C                         aszStart[] = u8"DCE";
    TgCHAR_U8_C                         aszEnd[] = u8"DE";

    for (uiIndex2 = 0; uiIndex2 < 2 * KTgSTRING_STATIC_BUFFER_SIZE; uiIndex2 += KTgSTRING_STATIC_BUFFER_SIZE / 2)
    {
        TgCHAR_U8_P                         mbzInit_String_0;

        mbzInit_String_0 = (TgCHAR_U8_P)TgMALLOC_TEMP( uiIndex2 + 1 );
        tgMM_Set_U08(mbzInit_String_0, uiIndex2, (TgUINT_E08)(aszStart[1]) );
        mbzInit_String_0[uiIndex2] = 0;

        for (uiSize = 0; uiSize < 2 * KTgSTRING_STATIC_BUFFER_SIZE; uiSize += KTgSTRING_STATIC_BUFFER_SIZE / 2)
        {
            TgCHAR_U8_P                         mbzInit_String_1, mbzInit_String_2;

            mbzInit_String_1 = (TgCHAR_U8_P)TgMALLOC_TEMP( uiSize + 1 );
            tgMM_Set_U08(mbzInit_String_1, uiSize, (TgUINT_E08)(aszStart[0]) );
            mbzInit_String_1[uiSize] = 0;

            mbzInit_String_2 = (TgCHAR_U8_P)TgMALLOC_TEMP( uiSize + 1 );
            tgMM_Set_U08(mbzInit_String_2, uiSize, (TgUINT_E08)(aszStart[2]) );
            mbzInit_String_2[uiSize] = 0;

            tgCM_UT_ST__ST__SZ_Init( &tgKB, mbzInit_String_0 );
            tgCM_UT_ST__ST__SZ_Append( &tgKB, mbzInit_String_1 );
            tgCM_UT_ST__ST__SZ_Append( &tgKB, mbzInit_String_2 );

            tgCM_UT_ST__ST__Trim_Start_Set( &tgKB, aszStart, 2 );

            mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );

            for (uiCheck = 0; uiCheck < uiSize; ++uiCheck)
            {
                Test__Expect_EQ('E', mbzKB[uiCheck]);
            };

            Test__Expect_EQ('\0', mbzKB[uiCheck]);
            Test__Expect_EQ(uiCheck, tgCM_UT_ST__ST__Length_U08( &tgKB ));
            Test__Expect_EQ(uiCheck, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

            tgCM_UT_ST__ST__Free( &tgKB );

            if (uiIndex2 > 0)
            {
                tgCM_UT_ST__ST__SZ_Init( &tgKB, mbzInit_String_0 );
                tgCM_UT_ST__ST__SZ_Append( &tgKB, mbzInit_String_1 );
                tgCM_UT_ST__ST__SZ_Append( &tgKB, mbzInit_String_2 );

                tgCM_UT_ST__ST__Trim_Start_Set( &tgKB, aszEnd, 2 );

                mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );

                for (uiCheck = 0; uiCheck < uiIndex2; ++uiCheck)
                {
                    Test__Expect_EQ('C', mbzKB[uiCheck]);
                };

                for (; uiCheck < uiIndex2 + uiSize; ++uiCheck)
                {
                    Test__Expect_EQ('D', mbzKB[uiCheck]);
                };

                for (; uiCheck < uiIndex2 + uiSize + uiSize; ++uiCheck)
                {
                    Test__Expect_EQ('E', mbzKB[uiCheck]);
                };

                Test__Expect_EQ('\0', mbzKB[uiCheck]);
                Test__Expect_EQ(uiCheck, tgCM_UT_ST__ST__Length_U08( &tgKB ));
                Test__Expect_EQ(uiCheck, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

                tgCM_UT_ST__ST__Free( &tgKB );
            };

            TgFREE_TEMP( mbzInit_String_2 );
            TgFREE_TEMP( mbzInit_String_1 );
        };

        TgFREE_TEMP( mbzInit_String_0 );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__ST__Trim_End_Set ------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__ST__Trim_End_Set )
{
    TgRSIZE                             uiIndex2, uiSize, uiCheck;/*, uiIndex, nbyTest, uiSrc_Start, uiSrc_End; */
    STg2_UT_ST__ST                      tgKB;
    TgCHAR_U8_CP                        mbzKB;
    TgCHAR_U8_C                         aszStart[] = { 'D', 'C', 'E' };
    TgCHAR_U8_C                         aszEnd[] = { 'C', 'E', 'D' };

    for (uiIndex2 = 0; uiIndex2 < 2 * KTgSTRING_STATIC_BUFFER_SIZE; uiIndex2 += KTgSTRING_STATIC_BUFFER_SIZE / 2)
    {
        TgCHAR_U8_P                         mbzInit_String_0;

        mbzInit_String_0 = (TgCHAR_U8_P)TgMALLOC_TEMP( uiIndex2 + 1 );
        tgMM_Set_U08(mbzInit_String_0, uiIndex2, (TgUINT_E08)(aszStart[0]) );
        mbzInit_String_0[uiIndex2] = 0;

        for (uiSize = 0; uiSize < 2 * KTgSTRING_STATIC_BUFFER_SIZE; uiSize += KTgSTRING_STATIC_BUFFER_SIZE / 2)
        {
            TgCHAR_U8_P                         mbzInit_String_1, mbzInit_String_2;

            mbzInit_String_1 = (TgCHAR_U8_P)TgMALLOC_TEMP( uiSize + 1 );
            tgMM_Set_U08(mbzInit_String_1, uiSize, (TgUINT_E08)(aszStart[1]) );
            mbzInit_String_1[uiSize] = 0;

            mbzInit_String_2 = (TgCHAR_U8_P)TgMALLOC_TEMP( uiSize + 1 );
            tgMM_Set_U08(mbzInit_String_2, uiSize, (TgUINT_E08)(aszStart[2]) );
            mbzInit_String_2[uiSize] = 0;

            tgCM_UT_ST__ST__SZ_Init( &tgKB, mbzInit_String_0 );
            tgCM_UT_ST__ST__SZ_Append( &tgKB, mbzInit_String_1 );
            tgCM_UT_ST__ST__SZ_Append( &tgKB, mbzInit_String_2 );

            tgCM_UT_ST__ST__Trim_End_Set( &tgKB, aszEnd, 2 );

            mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );

            for (uiCheck = 0; uiCheck < uiIndex2; ++uiCheck)
            {
                Test__Expect_EQ((TgUINT_E08)(aszStart[0]), mbzKB[uiCheck]);
            };

            Test__Expect_EQ('\0', mbzKB[uiCheck]);
            Test__Expect_EQ(uiCheck, tgCM_UT_ST__ST__Length_U08( &tgKB ));
            Test__Expect_EQ(uiCheck, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

            tgCM_UT_ST__ST__Free( &tgKB );



            tgCM_UT_ST__ST__SZ_Init( &tgKB, mbzInit_String_0 );
            tgCM_UT_ST__ST__SZ_Append( &tgKB, mbzInit_String_1 );
            tgCM_UT_ST__ST__SZ_Append( &tgKB, mbzInit_String_2 );

            tgCM_UT_ST__ST__Trim_End_Set( &tgKB, aszEnd, 1 );

            mbzKB = tgCM_UT_ST__ST__Query_String( &tgKB );

            for (uiCheck = 0; uiCheck < uiIndex2; ++uiCheck)
            {
                Test__Expect_EQ((TgUINT_E08)(aszStart[0]), mbzKB[uiCheck]);
            };

            for (; uiCheck < uiIndex2 + uiSize; ++uiCheck)
            {
                Test__Expect_EQ((TgUINT_E08)(aszStart[1]), mbzKB[uiCheck]);
            };

            for (; uiCheck < uiIndex2 + uiSize + uiSize; ++uiCheck)
            {
                Test__Expect_EQ((TgUINT_E08)(aszStart[2]), mbzKB[uiCheck]);
            };

            Test__Expect_EQ('\0', mbzKB[uiCheck]);
            Test__Expect_EQ(uiCheck, tgCM_UT_ST__ST__Length_U08( &tgKB ));
            Test__Expect_EQ(uiCheck, tgUSZ_Length_U08( mbzKB, KTgMAX_RSIZE ));

            tgCM_UT_ST__ST__Free( &tgKB );

            TgFREE_TEMP( mbzInit_String_2 );
            TgFREE_TEMP( mbzInit_String_1 );
        };

        TgFREE_TEMP( mbzInit_String_0 );
    };

    TEST_END_METHOD( KTgS_OK );
}
