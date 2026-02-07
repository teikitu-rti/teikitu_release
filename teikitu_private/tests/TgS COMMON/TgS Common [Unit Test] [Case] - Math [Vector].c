/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common [Unit Test] [Case] - Math [Vector].c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TgEXTN TgVOID
tgCM_Unit_Test_Register_Math_Vector(
    Test_Set *);




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Tests                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

EXTN_METHOD_DECLARE( UNIT_TEST__TEST__MATH_VECTOR_S08_16_1 );
EXTN_METHOD_DECLARE( UNIT_TEST__TEST__MATH_VECTOR_S16_08_1 );
EXTN_METHOD_DECLARE( UNIT_TEST__TEST__MATH_VECTOR_S32_04_1 );
EXTN_METHOD_DECLARE( UNIT_TEST__TEST__MATH_VECTOR_S08_04_1 );
EXTN_METHOD_DECLARE( UNIT_TEST__TEST__MATH_VECTOR_S16_02_1 );
EXTN_METHOD_DECLARE( UNIT_TEST__TEST__MATH_VECTOR_S64_04_1 );
EXTN_METHOD_DECLARE( UNIT_TEST__TEST__MATH_VECTOR_U08_16_1 );
EXTN_METHOD_DECLARE( UNIT_TEST__TEST__MATH_VECTOR_U16_08_1 );
EXTN_METHOD_DECLARE( UNIT_TEST__TEST__MATH_VECTOR_U32_04_1 );
EXTN_METHOD_DECLARE( UNIT_TEST__TEST__MATH_VECTOR_U08_04_1 );
EXTN_METHOD_DECLARE( UNIT_TEST__TEST__MATH_VECTOR_U16_02_1 );
EXTN_METHOD_DECLARE( UNIT_TEST__TEST__MATH_VECTOR_U64_04_1 );

EXTN_METHOD_DECLARE( UNIT_TEST__TEST__MATH_VECTOR_F32_02_1 );
EXTN_METHOD_DECLARE( UNIT_TEST__TEST__MATH_VECTOR_F32_03_1 );
EXTN_METHOD_DECLARE( UNIT_TEST__TEST__MATH_VECTOR_F32_04_1 );
EXTN_METHOD_DECLARE( UNIT_TEST__TEST__MATH_VECTOR_F64_02_1 );
EXTN_METHOD_DECLARE( UNIT_TEST__TEST__MATH_VECTOR_F64_03_1 );
EXTN_METHOD_DECLARE( UNIT_TEST__TEST__MATH_VECTOR_F64_04_1 );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Macros                                                                                                                                                              */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#define SETUP_VEC_INT_TEST(A, B)                            s_sCASE__VEC.m_apszTest[ uiIndex] = u8"S" #A "_" #B;                                                                    \
                                                            s_sCASE__VEC.m_pfnTest[uiIndex++] = UNIT_TEST__TEST__MATH_VECTOR_S##A##_##B##_1;                                        \
                                                            s_sCASE__VEC.m_apszTest[ uiIndex] = u8"U" #A "_" #B;                                                                    \
                                                            s_sCASE__VEC.m_pfnTest[uiIndex++] = UNIT_TEST__TEST__MATH_VECTOR_U##A##_##B##_1

#define SETUP_VEC_FLT_TEST(A)                               s_sCASE__VEC.m_apszTest[ uiIndex] = u8"F32_" #A;                                                                        \
                                                            s_sCASE__VEC.m_pfnTest[uiIndex++] = UNIT_TEST__TEST__MATH_VECTOR_F32_##A##_1;                                           \
                                                            s_sCASE__VEC.m_apszTest[ uiIndex] = u8"F64_" #A;                                                                        \
                                                            s_sCASE__VEC.m_pfnTest[uiIndex++] = UNIT_TEST__TEST__MATH_VECTOR_F64_##A##_1




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Data                                                                                                                                                                */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

static Test_Case                                            s_sCASE__VEC;




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgCM_Unit_Test_Register_Math_Vector -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgCM_Unit_Test_Register_Math_Vector( Test_Set * psSET__BASE )
{
    TgSINT_E32                          uiIndex;

    /* Initialize the unit test structures */

    Unit_Test__Case_Init( &s_sCASE__VEC );



    /* Configure the test set */

    s_sCASE__VEC.m_pszSet = psSET__BASE->m_szSet;
    s_sCASE__VEC.m_pszCase = u8"Vector";
    uiIndex = 0;

    SETUP_VEC_INT_TEST(08,16);
    SETUP_VEC_INT_TEST(16,08);
    SETUP_VEC_INT_TEST(32,04);
    SETUP_VEC_INT_TEST(08,04);
    SETUP_VEC_INT_TEST(16,02);
    SETUP_VEC_INT_TEST(64,04);

    SETUP_VEC_FLT_TEST(02);
    SETUP_VEC_FLT_TEST(03);
    SETUP_VEC_FLT_TEST(04);

    TgCRITICAL(uiIndex < KTgNUM_TEST_PER_CASE);



    /* Register all of the test cases with the test set */

    Unit_Test__Set_Register_Case( psSET__BASE, &s_sCASE__VEC );
}
