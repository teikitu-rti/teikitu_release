/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common [Unit Test] [Test] - Math [Matrix].c_inc
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#if !defined (ENABLE_RELOAD_GUARD2)
    #define ENABLE_RELOAD_GUARD2
    #define TEMPLATE__TEST_AND_UNLOAD_TEMPLATE_MACROS
    #define TEMPLATE__VECTOR_DIM 4
    #define TEMPLATE__VECTOR_COL 3
    #include __FILE__
    #define TEMPLATE__VECTOR_DIM 4
    #define TEMPLATE__VECTOR_COL 4
#endif

#if !defined (ENABLE_RELOAD_GUARD)
    #define ENABLE_RELOAD_GUARD
    #if !defined(TEMPLATE__TYPE_SIZE)
        #define TEMPLATE__TYPE_SIZE 32
        #include __FILE__
        #undef TEMPLATE__TYPE_SIZE
        #define TEMPLATE__TYPE_SIZE 64
    #endif
    #undef ENABLE_RELOAD_GUARD
#endif

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

#define FCN_M_UT(...)                       MULTI_MACRO(FCN_M_UT, __VA_ARGS__)
#define FCN_M_UT_1(F)                       TgMACRO_CONCAT5( UNIT_TEST__TEST__##F, _, GENERATE__VEC_DESC, _, TEMPLATE__VECTOR_COL )
#define FCN_M_UT_2(F, COL)                  TgMACRO_CONCAT5( UNIT_TEST__TEST__##F, _, GENERATE__VEC_DESC, _, COL )

/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_CLR_S) );
EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_MAX_S) );
EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_MIN_S) );
EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_AND_S) );
EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_OR_S) );
EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_XOR_S) );

#if (!VEC_IS_NATIVE && TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE) || VEC_IS_NATIVE /* MACRO_COMPILE_NATIVE_MATRIX_GUARD */
    EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_CLR) );
    EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_MAX) );
    EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_MIN) );
    EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_AND) );
    EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_OR) );
    EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_XOR) );
#endif

#if defined(TEMPLATE__ENABLE_INTEGER)
    #error Not supported
#else
    EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_ADD_S) );
    EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_MUL_S) );
    EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_MUL_SM_S) );
    EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_MUL_MS_S) );
    EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_DIV_S) );
    EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_DIV_SM_S) );
    EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_DIV_MS_S) );
    EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_SUB_S) );
    EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_NEG_S) );
    EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_Set_Euler_S) );
    EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_Set_Euler_ELEM_S) );
    EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_Set_Euler_X_S) );
    EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_Set_Euler_Y_S) );
    EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_Set_Euler_Z_S) );
    EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_Set_Quat_S) );
    EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_NAN_S) );
    EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_CLI_S) );
    EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_Set_ROT_S) );
    EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_Set_T_S) );
    EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_Set_T_ELEM_S) );
    EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_Init_ROT_S) );
    EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_Init_T_S) );
    EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_Init_T_ELEM_S) );
    EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_Init_Euler_S) );
    EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_Init_Euler_ELEM_S) );
    EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_Init_Euler_X_S) );
    EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_Init_Euler_Y_S) );
    EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_Init_Euler_Z_S) );
    EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_Init_Quat_S) );
    EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_CAT_S) );
    EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_INV_DET_S) );
    EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_INV_S) );
    EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_DET_S) );
    EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_TX_S) );
    EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_TX_P_S) );
    EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_TX_V_S) );
    EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_Query_Row_0_S) );
    EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_Query_Row_1_S) );
    EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_Query_Row_2_S) );
    EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_Query_Row_3_S) );
    EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_Query_Col_0_S) );
    EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_Query_Col_1_S) );
    EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_Query_Col_2_S) );
    EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_Query_Col_3_S) );
    EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_Query_Axis_0_S) );
    EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_Query_Axis_1_S) );
    EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_Query_Axis_2_S) );
    EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_Query_Axis_3_S) );
    EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_Matrix_To_Euler_S_S) );
    EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_Matrix_To_Euler_S) );
    EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_Matrix_To_Quat_S) );
    EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_Init_Reference_Frame_From_Vector_And_Position_S) );
    #if (4 == TEMPLATE__VECTOR_COL)
        EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_CAT_34_44_S) );
        EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_CAT_44_34_S) );
        EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_TR_S) );
        EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_Look_S) );
        EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_LookLH_S) );
        EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_LookRH_S) );
        EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_PProjLH_S) );
        EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_PProjRH_S) );
        EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_PProj_S) );
        EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_PProj_OffsetLH_S) );
        EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_PProj_OffsetRH_S) );
        EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_PProj_Offset_S) );
        EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_PProj_FoV_S) );
        EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_PProj_FoVLH_S) );
        EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_PProj_FoVRH_S) );
        EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_OrthoLH_S) );
        EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_OrthoRH_S) );
        EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_Ortho_S) );
        EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_Ortho_OffsetLH_S) );
        EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_Ortho_OffsetRH_S) );
        EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_Ortho_Offset_S) );
    #elif (3 == TEMPLATE__VECTOR_COL)
        EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_TR_S) );
        EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_LookLH_S) );
        EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_LookRH_S) );
        EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_Look_S) );
    #endif
    #if (!VEC_IS_NATIVE && TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE) || VEC_IS_NATIVE /* MACRO_COMPILE_NATIVE_MATRIX_GUARD */
        EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_Init_T) );
        EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_Init_Quat) );
        EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_CLI) );
        EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_Set_T) );
        EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_ADD) );
        EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_MUL) );
        EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_DIV) );
        EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_SUB) );
        EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_NEG) );
        EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_CAT) );
        EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_INV_DET) );
        EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_INV) );
        EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_DET) );
        EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_TX) );
        EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_TX_P) );
        EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_TX_V) );
        EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_Query_Row_0) );
        EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_Query_Row_1) );
        EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_Query_Row_2) );
        EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_Query_Row_3) );
        EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_Query_Col_0) );
        EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_Query_Col_1) );
        EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_Query_Col_2) );
        EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_Query_Col_3) );
        EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_Query_Axis_0) );
        EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_Query_Axis_1) );
        EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_Query_Axis_2) );
        EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_Query_Axis_3) );
        #if (4 == TEMPLATE__VECTOR_COL)
            EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_CAT_34_44) );
            EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_CAT_44_34) );
            EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_TR) );
        #elif (3 == TEMPLATE__VECTOR_COL)
            EXTN_METHOD_DECLARE( FCN_M_UT(tgMH_TR) );
        #endif
    #endif
#endif


/* ---- FCN_M_UT(tgMH_CLR_S) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_CLR_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       sM0;

    FCN_M(tgMH_CLR_S)( &sM0 );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL * TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_EQ( TYPE_K(0), sM0.m_aElement[uiIndex] );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_MAX_S) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_MAX_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       sM0, sM1, sMX;

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        sM0.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
        sM1.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
    };

    FCN_M(tgMH_MAX_S)( &sMX, &sM0, &sM1 );

    for (TgRSIZE uiCol = 0; uiCol < TEMPLATE__VECTOR_COL; ++uiCol)
    {
        for (TgRSIZE uiRow = 0; uiRow < TEMPLATE__VECTOR_DIM; ++uiRow)
        {
            TgRSIZE_C uiIndex = uiCol*TEMPLATE__VECTOR_DIM + uiRow;
            VAR_T(C) tVal0 = FCN_F(tgCM_MAX)( sM0.m_aElement[uiIndex],  sM1.m_aElement[uiIndex] );
            VAR_T(C) tVal1 = FCN_F(tgPM_ABS)( sMX.m_aElement[uiIndex] - tVal0 );
            Test__Expect_EQ( true, tVal1 < VAR_K(KTgEPS) * TYPE_K(10) );
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_MIN_S) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_MIN_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       sM0, sM1, sMX;

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        sM0.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
        sM1.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
    };

    FCN_M(tgMH_MIN_S)( &sMX, &sM0, &sM1 );

    for (TgRSIZE uiCol = 0; uiCol < TEMPLATE__VECTOR_COL; ++uiCol)
    {
        for (TgRSIZE uiRow = 0; uiRow < TEMPLATE__VECTOR_DIM; ++uiRow)
        {
            TgRSIZE_C uiIndex = uiCol*TEMPLATE__VECTOR_DIM + uiRow;
            VAR_T(C) tVal0 = FCN_F(tgCM_MIN)( sM0.m_aElement[uiIndex],  sM1.m_aElement[uiIndex] );
            VAR_T(C) tVal1 = FCN_F(tgPM_ABS)( sMX.m_aElement[uiIndex] - tVal0 );
            Test__Expect_EQ( true, tVal1 < VAR_K(KTgEPS) * TYPE_K(10) );
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_AND_S) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_AND_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       sM0, sM1, sMX;
    TgUINT_E08_P                        puiM0, puiM1, puiMX;

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        sM0.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
        sM1.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
    };

    puiM0 = (TgUINT_E08_P)&sM0;
    puiM1 = (TgUINT_E08_P)&sM1;
    puiMX = (TgUINT_E08_P)&sMX;

    FCN_M(tgMH_AND_S)( &sMX, &sM0, &sM1 );

    for (TgRSIZE uiIndex = 0; uiIndex < (TgRSIZE)(sizeof( VEC_S_T(TEMPLATE__VECTOR_COL) )); ++uiIndex)
    {
        Test__Expect_EQ( puiMX[uiIndex], puiM0[uiIndex] & puiM1[uiIndex] );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_OR_S) ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_OR_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       sM0, sM1, sMX;
    TgUINT_E08_P                        puiM0, puiM1, puiMX;

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        sM0.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
        sM1.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
    };

    puiM0 = (TgUINT_E08_P)&sM0;
    puiM1 = (TgUINT_E08_P)&sM1;
    puiMX = (TgUINT_E08_P)&sMX;

    FCN_M(tgMH_OR_S)( &sMX, &sM0, &sM1 );

    for (TgRSIZE uiIndex = 0; uiIndex < (TgRSIZE)(sizeof( VEC_S_T(TEMPLATE__VECTOR_COL) )); ++uiIndex)
    {
        Test__Expect_EQ( puiMX[uiIndex], puiM0[uiIndex] | puiM1[uiIndex] );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_XOR_S) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_XOR_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       sM0, sM1, sMX;
    TgUINT_E08_P                        puiM0, puiM1, puiMX;

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        sM0.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
        sM1.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
    };

    puiM0 = (TgUINT_E08_P)&sM0;
    puiM1 = (TgUINT_E08_P)&sM1;
    puiMX = (TgUINT_E08_P)&sMX;

    FCN_M(tgMH_XOR_S)( &sMX, &sM0, &sM1 );

    for (TgRSIZE uiIndex = 0; uiIndex < (TgRSIZE)(sizeof( VEC_S_T(TEMPLATE__VECTOR_COL) )); ++uiIndex)
    {
        Test__Expect_EQ( puiMX[uiIndex], puiM0[uiIndex] ^ puiM1[uiIndex] );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(MATH_VECTOR) ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(MATH_VECTOR) )
{
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_CLR_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_MAX_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_MIN_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_AND_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_OR_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_XOR_S)() );

#if (!VEC_IS_NATIVE && TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE) || VEC_IS_NATIVE /* MACRO_COMPILE_NATIVE_MATRIX_GUARD */
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_CLR)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_MAX)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_MIN)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_AND)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_OR)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_XOR)() );

#endif

#if defined(TEMPLATE__ENABLE_INTEGER)
    #error Not supported

#else
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_ADD_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_MUL_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_MUL_SM_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_MUL_MS_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_DIV_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_DIV_SM_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_DIV_MS_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_SUB_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_NEG_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_Set_Euler_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_Set_Euler_ELEM_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_Set_Euler_X_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_Set_Euler_Y_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_Set_Euler_Z_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_Set_Quat_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_NAN_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_CLI_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_Set_ROT_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_Set_T_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_Set_T_ELEM_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_Init_ROT_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_Init_T_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_Init_T_ELEM_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_Init_Euler_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_Init_Euler_ELEM_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_Init_Euler_X_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_Init_Euler_Y_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_Init_Euler_Z_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_Init_Quat_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_CAT_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_INV_DET_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_INV_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_DET_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_TX_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_TX_P_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_TX_V_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_Query_Row_0_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_Query_Row_1_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_Query_Row_2_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_Query_Row_3_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_Query_Col_0_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_Query_Col_1_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_Query_Col_2_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_Query_Col_3_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_Query_Axis_0_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_Query_Axis_1_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_Query_Axis_2_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_Query_Axis_3_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_Matrix_To_Euler_S_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_Matrix_To_Euler_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_Matrix_To_Quat_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_Init_Reference_Frame_From_Vector_And_Position_S)() );

#if (4 == TEMPLATE__VECTOR_COL)
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_CAT_34_44_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_CAT_44_34_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_TR_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_Look_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_LookLH_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_LookRH_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_PProjLH_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_PProjRH_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_PProj_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_PProj_OffsetLH_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_PProj_OffsetRH_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_PProj_Offset_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_PProj_FoV_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_PProj_FoVLH_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_PProj_FoVRH_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_OrthoLH_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_OrthoRH_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_Ortho_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_Ortho_OffsetLH_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_Ortho_OffsetRH_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_Ortho_Offset_S)() );

#elif (3 == TEMPLATE__VECTOR_COL)
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_TR_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_LookLH_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_LookRH_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_Look_S)() );

#endif
#if (!VEC_IS_NATIVE && TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE) || VEC_IS_NATIVE /* MACRO_COMPILE_NATIVE_MATRIX_GUARD */
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_Init_T)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_Init_Quat)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_CLI)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_Set_T)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_ADD)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_MUL)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_DIV)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_SUB)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_NEG)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_CAT)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_INV_DET)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_INV)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_DET)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_TX)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_TX_P)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_TX_V)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_Query_Row_0)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_Query_Row_1)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_Query_Row_2)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_Query_Row_3)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_Query_Col_0)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_Query_Col_1)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_Query_Col_2)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_Query_Col_3)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_Query_Axis_0)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_Query_Axis_1)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_Query_Axis_2)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_Query_Axis_3)() );

#if (4 == TEMPLATE__VECTOR_COL)
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_CAT_34_44)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_CAT_44_34)() );
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_TR)() );
#elif (3 == TEMPLATE__VECTOR_COL)
    Test__Expect_EQ( KTgS_OK, FCN_M_UT(tgMH_TR)() );
#endif
#endif
#endif
    
    TEST_END_METHOD( KTgS_OK );
}




/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

#undef FCN_M_UT
#undef FCN_UT_1
#undef FCN_UT_2
