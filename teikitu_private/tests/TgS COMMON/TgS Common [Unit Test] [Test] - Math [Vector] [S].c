/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common [Unit Test] [Test] - Math [Vector] [S].c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#if !defined (ENABLE_RELOAD_GUARD2)
    #define ENABLE_RELOAD_GUARD2

    #define TEMPLATE__ENABLE_INTEGER

    #define TEMPLATE__TEST_AND_UNLOAD_TEMPLATE_MACROS
    #define TEMPLATE__TYPE_SIZE 8
    #define TEMPLATE__VECTOR_DIM 16
    #include __FILE__

    #define TEMPLATE__TYPE_SIZE 16
    #define TEMPLATE__VECTOR_DIM 8
    #include __FILE__

    #define TEMPLATE__TYPE_SIZE 32
    #define TEMPLATE__VECTOR_DIM 4
    #include __FILE__

    #define TEMPLATE__TYPE_SIZE 8
    #define TEMPLATE__VECTOR_DIM 4
    #include __FILE__

    #define TEMPLATE__TYPE_SIZE 16
    #define TEMPLATE__VECTOR_DIM 2
    #include __FILE__

    #define TEMPLATE__TYPE_SIZE 64
    #define TEMPLATE__VECTOR_DIM 4
    #include __FILE__

    #undef TEMPLATE__ENABLE_INTEGER

    #define TEMPLATE__VECTOR_DIM 2
    #include __FILE__

    #define TEMPLATE__VECTOR_DIM 3
    #include __FILE__

    #define TEMPLATE__VECTOR_DIM 4
#endif

#if defined(TEMPLATE__ENABLE_INTEGER)

    #if !defined (ENABLE_RELOAD_GUARD)
        #define ENABLE_RELOAD_GUARD
        #define TEMPLATE__ENABLE_UNSIGNED
        #include __FILE__
        #undef TEMPLATE__ENABLE_UNSIGNED
        #undef ENABLE_RELOAD_GUARD
    #endif

#else

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

#endif

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

#define FCN_V_UT(...)                       MULTI_MACRO(FCN_V_UT, __VA_ARGS__)
#define FCN_V_UT_1(F)                       TgMACRO_CONCAT5( UNIT_TEST__TEST__##F, _, GENERATE__VEC_DESC, _, 1 )
#define FCN_V_UT_2(F, COL)                  TgMACRO_CONCAT5( UNIT_TEST__TEST__##F, _, GENERATE__VEC_DESC, _, COL )

/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_SETU_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_SETA_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_SET1_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_PERM_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_SEL_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_AND_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_OR_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_XOR_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_MAX_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_MIN_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_CMP_EQ_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_CMP_NE_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_CMP_GE_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_CMP_GT_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_CMP_LE_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_CMP_LT_S) );
#if (!VEC_IS_NATIVE && TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE) || VEC_IS_NATIVE /* MACRO_COMPILE_NATIVE_VECTOR_GUARD */
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_SETU) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_SETA) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_SET1) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_SEL) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_AND) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_OR) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_XOR) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_MAX) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_MIN) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_CMP_EQ) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_CMP_NE) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_CMP_GE) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_CMP_GT) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_CMP_LE) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_CMP_LT) );
/*# ((128 == TEMPLATE__TYPE_SIZE * TEMPLATE__VECTOR_DIM) && (32 >= TEMPLATE__TYPE_SIZE)) */
#endif
#if defined(TEMPLATE__ENABLE_INTEGER)
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_ADD_CLP_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_ADD_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_SUB_CLP_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_SUB_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_AVG_S) );
#if (!VEC_IS_NATIVE && TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE) || VEC_IS_NATIVE /* MACRO_COMPILE_NATIVE_VECTOR_GUARD */
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_ADD_CLP) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_ADD) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_SUB_CLP) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_SUB) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_AVG) );
/*# ((128 == TEMPLATE__TYPE_SIZE * TEMPLATE__VECTOR_DIM) && (32 >= TEMPLATE__TYPE_SIZE)) */
#endif
/*# defined(TEMPLATE__ENABLE_INTEGER) */
#else
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_ADD_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_MAD_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_NMS_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_DOT_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_MUL_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_DIV_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_SUB_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_LSQ_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_LEN_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_NEG_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_SQRT_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_RSQRT_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_NORM_LEN_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_NORM_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_FLR_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_CEL_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_CLP_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_SAT_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_NAN_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_BND_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_MAD_SVV_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_MAD_VSV_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_NMS_SVV_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_NMS_VSV_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_MUL_SV_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_MUL_VS_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_DIV_SV_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_DIV_VS_S) );
#if (4 == TEMPLATE__VECTOR_DIM)
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_Init_ELEM_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_Init_Point_ELEM_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_Init_Vector_ELEM_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_Init_Point_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_Init_Vector_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_RAND_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_Init_Ortho_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_Init_Basis_From_Vector_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_Is_Valid_Point_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_Is_Valid_Vector_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_DOT3_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_CX_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_UCX_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_UCX_LEN_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_NORM3_LEN_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_NORM3_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_PRX3_CMP_EQ_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_Is_PRX_CMP_EQ_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_QT_Init_Axis_Angle_ELEM_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_QT_Init_Axis_Angle_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_QT_Init_Euler_ELEM_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_QT_Init_Euler_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_QT_Init_Euler_X_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_QT_Init_Euler_Y_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_QT_Init_Euler_Z_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_Quat_To_Euler_ELEM_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_Quat_To_Euler_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_QT_INV_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_QT_MUL_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_QT_Slerp_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_QT_Vector_To_Vector_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_QT_TX_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_QT_INV_TX_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_Rotate_Vector_Euler_X_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_Rotate_Vector_Euler_Y_S) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_Rotate_Vector_Euler_Z_S) );
#endif
#if (!VEC_IS_NATIVE && TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE) || VEC_IS_NATIVE /* MACRO_COMPILE_NATIVE_VECTOR_GUARD */
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_ADD) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_MAD) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_NMS) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_DOT) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_MUL) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_DIV) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_SUB) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_LSQ) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_LEN) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_NEG) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_SQRT) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_RSQRT) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_NORM) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_NORM_LEN) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_FLR) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_CEL) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_CLP) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_SAT) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_NAN) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_BND) );
#if (4 == TEMPLATE__VECTOR_DIM)
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_Init_ELEM) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_Init_Point_ELEM) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_Init_Vector_ELEM) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_Init_Point) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_Init_Vector) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_RAND) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_SPX) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_SPY) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_SPZ) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_SPW) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_DOT3) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_CX) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_UCX) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_UCX_LEN) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_PRX3_CMP_EQ) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_Is_PRX_CMP_EQ) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_QT_INV) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_QT_MUL) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_QT_Slerp) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_QT_Vector_To_Vector) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_QT_TX) );
EXTN_METHOD_DECLARE(FCN_V_UT(tgMH_QT_INV_TX) );
#endif
#endif
/*# defined(TEMPLATE__ENABLE_INTEGER) */
#endif


/* ---- FCN_V_UT(tgMH_SETU_S) ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_SETU_S) )
{
    VAR_T()                             at1[TEMPLATE__VECTOR_DIM*2];
    VEC_S_T(1)                          vV1;
    TgRSIZE                             uiStart, uiIndex;

    for (uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM*2; ++uiIndex)
    {
        at1[uiIndex] = (VAR_T())(uiIndex + 1);
    };

    uiStart = uiIndex = (0 == ((TgUINT_PTR)at1 % 16)) ? 1u : 0u;
    vV1 = FCN_V(tgMH_SETU_S)( at1 + uiIndex );

    for (; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_EQ((VAR_T())(uiIndex + 1), vV1.m_aData[uiIndex - uiStart]);
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_SETA_S) ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_SETA_S) )
{
    TgALIGN(16) VAR_T()                 at1[TEMPLATE__VECTOR_DIM];
    VEC_S_T(1)                          vV1;
    TgRSIZE                             uiIndex;

    for (uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        at1[uiIndex] = (VAR_T())(uiIndex + 1);
    };

    vV1 = FCN_V(tgMH_SETA_S)( at1 );

    for (uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_EQ((VAR_T())(uiIndex + 1), vV1.m_aData[uiIndex]);
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_SET1_S) ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_SET1_S) )
{
    VEC_S_T(1)                          vV3;

    vV3 = FCN_V(tgMH_SET1_S)( 3 );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_EQ((VAR_T())3, vV3.m_aData[uiIndex]);
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_PERM_S) ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_PERM_S) )
{
    VEC_S_T(1)                          vV0 = {{0}}, vV1 = {{0}}, vV2 = {{0}}, vV3 = {{0}};
    UVAR_T()                            uiPerm, uiI2;

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        ((UVAR_T(P))(&vV0))[uiIndex] = (UVAR_T())tgCM_RAND_U64();
        ((UVAR_T(P))(&vV1))[uiIndex] = (UVAR_T())tgCM_RAND_U64();
        uiPerm = (UVAR_T())tgCM_RAND_U64();
        ((UVAR_T(P))(&vV2))[uiIndex] = (UVAR_T())((uiPerm & KTgPERM_PARAM_SELECT_BIT) + (uiPerm % TEMPLATE__VECTOR_DIM));
    };

    vV3 = FCN_V(tgMH_PERM_S)( vV0, vV1, (UVAR_T(P))( &vV2 ) );
    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        uiI2 = ((UVAR_T(P))(&vV2))[uiIndex];
        uiPerm = (UVAR_T())(uiI2 & (KTgPERM_PARAM_SELECT_BIT - 1));
        TgERROR( uiPerm < TEMPLATE__VECTOR_DIM );

        if (uiI2 >= KTgPERM_PARAM_SELECT_BIT)
        {
            Test__Expect_EQ( ((UVAR_T(P))(&vV1))[uiPerm], ((UVAR_T(P))(&vV3))[uiIndex] );
        }
        else
        {
            Test__Expect_EQ( ((UVAR_T(P))(&vV0))[uiPerm], ((UVAR_T(P))(&vV3))[uiIndex] );
        };
    };


    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_SEL_S) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_SEL_S) )
{
    VEC_S_T(1)                          vV0 = {{0}}, vV1 = {{0}}, vV2 = {{0}}, vV3 = {{0}};
    TgUINT_E32                          ui0;
    TgUINT_E08                          ui08_0;

    for (ui0 = 0; ui0 < TEMPLATE__VECTOR_DIM*sizeof( VAR_T() ); ++ui0)
    {
        ((TgUINT_E08_P)(&vV0))[ui0] = tgCM_RAND_U08();
        ((TgUINT_E08_P)(&vV1))[ui0] = tgCM_RAND_U08();
        ui08_0 = tgCM_RAND_U08();
        ((TgUINT_E08_P)(&vV2))[ui0] = (TgUINT_E08)((ui08_0 & KTgPERM_PARAM_SELECT_BIT) + (ui08_0 % TEMPLATE__VECTOR_DIM));
    };

    vV3 = FCN_V(tgMH_SEL_S)( vV0, vV1, (UVAR_T(P))( &vV2 ) );
    for (ui0 = 0; ui0 < TEMPLATE__VECTOR_DIM * sizeof( VAR_T() ); ++ui0)
    {
        ui08_0  = (TgUINT_E08)(((TgUINT_E08_P)(&vV0))[ui0] & ~((TgUINT_E08_P)(&vV2))[ui0]);
        ui08_0 |= ((TgUINT_E08_P)(&vV1))[ui0] &  ((TgUINT_E08_P)(&vV2))[ui0];
        Test__Expect_EQ(((TgUINT_E08_P)(&vV3))[ui0], ui08_0);
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_AND_S) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_AND_S) )
{
    VEC_S_T(1)                          vV0 = {{0}}, vV1 = {{0}}, vV2 = {{0}};
    TgUINT_E32                          ui0;

    for (ui0 = 0; ui0 < TEMPLATE__VECTOR_DIM*sizeof( VAR_T() ); ++ui0)
    {
        ((TgUINT_E08_P)(&vV1))[ui0] = tgCM_RAND_U08();
        ((TgUINT_E08_P)(&vV2))[ui0] = tgCM_RAND_U08();
    };

    vV0 = FCN_V(tgMH_AND_S)( vV1, vV2 );
    for (ui0 = 0; ui0 < TEMPLATE__VECTOR_DIM*sizeof( VAR_T() ); ++ui0)
    {
        Test__Expect_EQ(((TgUINT_E08_P)(&vV0))[ui0], (TgUINT_E08)(((TgUINT_E08_P)(&vV1))[ui0] & ((TgUINT_E08_P)(&vV2))[ui0]));
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_OR_S) ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_OR_S) )
{
    VEC_S_T(1)                          vV0 = {{0}}, vV1 = {{0}}, vV2 = {{0}};
    TgUINT_E32                          ui0;

    for (ui0 = 0; ui0 < TEMPLATE__VECTOR_DIM*sizeof( VAR_T() ); ++ui0)
    {
        ((TgUINT_E08_P)(&vV1))[ui0] = tgCM_RAND_U08();
        ((TgUINT_E08_P)(&vV2))[ui0] = tgCM_RAND_U08();
    };

    vV0 = FCN_V(tgMH_OR_S)( vV1, vV2 );
    for (ui0 = 0; ui0 < TEMPLATE__VECTOR_DIM*sizeof( VAR_T() ); ++ui0)
    {
        Test__Expect_EQ(((TgUINT_E08_P)(&vV0))[ui0], (TgUINT_E08)(((TgUINT_E08_P)(&vV1))[ui0] | ((TgUINT_E08_P)(&vV2))[ui0]));
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_XOR_S) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_XOR_S) )
{
    VEC_S_T(1)                          vV0 = {{0}}, vV1 = {{0}}, vV2 = {{0}};
    TgUINT_E32                          ui0;

    for (ui0 = 0; ui0 < TEMPLATE__VECTOR_DIM*sizeof( VAR_T() ); ++ui0)
    {
        ((TgUINT_E08_P)(&vV1))[ui0] = tgCM_RAND_U08();
        ((TgUINT_E08_P)(&vV2))[ui0] = tgCM_RAND_U08();
    };

    vV0 = FCN_V(tgMH_XOR_S)( vV1, vV2 );
    for (ui0 = 0; ui0 < TEMPLATE__VECTOR_DIM*sizeof( VAR_T() ); ++ui0)
    {
        Test__Expect_EQ(((TgUINT_E08_P)(&vV0))[ui0], (TgUINT_E08)(((TgUINT_E08_P)(&vV1))[ui0] ^ ((TgUINT_E08_P)(&vV2))[ui0]));
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_MAX_S) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_MAX_S) )
{
    VEC_S_T(1,C)                        vV0 = FCN_V(tgMH_SET1_S)(0);
    VEC_S_T(1,C)                        vV1 = FCN_V(tgMH_SET1_S)(1);
    VEC_S_T(1,C)                        vV2 = FCN_V(tgMH_SET1_S)(2);
    VEC_S_T(1)                          vV3 = {{0}}, vV4 = {{0}};
    TgSINT_E32                          uiIndex, ui0;

    for (ui0 = 0; ui0 < TEMPLATE__VECTOR_DIM; ++ui0)
    {
        while (0 == (vV3.m_aData[ui0] = FCN_F(tgCM_RAND)()));
        while (0 == (vV4.m_aData[ui0] = FCN_F(tgCM_RAND)()));
    };

    {
        VEC_S_T(1,C)                        v5 = FCN_V(tgMH_MAX_S)( vV1, vV0 );
        VEC_S_T(1,C)                        v6 = FCN_V(tgMH_MAX_S)( vV1, vV1 );
        VEC_S_T(1,C)                        v7 = FCN_V(tgMH_MAX_S)( vV1, vV2 );

        Test__Expect_EQ(0, memcmp( &vV1, &v5, sizeof( VEC_S_T(1) ) ));
        Test__Expect_EQ(0, memcmp( &vV1, &v6, sizeof( VEC_S_T(1) ) ));
        Test__Expect_EQ(0, memcmp( &vV2, &v7, sizeof( VEC_S_T(1) ) ));
    };

    for (uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        VEC_S_T(1)                          v5 = FCN_V(tgMH_SET1_S)(1);

        v5.m_aData[uiIndex] = 0;
        {
            VEC_S_T(1,C)                        v6 = FCN_V(tgMH_MAX_S)( vV1, v5 );

            Test__Expect_EQ(0, memcmp( &vV1, &v6, sizeof( VEC_S_T(1) ) ));
        };

        v5.m_aData[uiIndex] = 2;
        {
            VEC_S_T(1,C)                        v7 = FCN_V(tgMH_MAX_S)( vV1, v5 );

            Test__Expect_EQ(0, memcmp( &v5, &v7, sizeof( VEC_S_T(1) ) ));
        };
    };

    {
        VEC_S_T(1,C)                        v5 = FCN_V(tgMH_MAX_S)( vV3, vV4 );

        for (ui0 = 0; ui0 < TEMPLATE__VECTOR_DIM; ++ui0)
        {
            Test__Expect_EQ(v5.m_aData[ui0], FCN_F(tgCM_MAX)(vV3.m_aData[ui0], vV4.m_aData[ui0]));
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_MIN_S) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_MIN_S) )
{
    VEC_S_T(1,C)                        vV0 = FCN_V(tgMH_SET1_S)(0);
    VEC_S_T(1,C)                        vV1 = FCN_V(tgMH_SET1_S)(1);
    VEC_S_T(1,C)                        vV2 = FCN_V(tgMH_SET1_S)(2);

    /* Basic comparison, but all lanes have the same value */
    {
        VEC_S_T(1,C)                        v8 = FCN_V(tgMH_MIN_S)( vV1, vV0 );
        VEC_S_T(1,C)                        v9 = FCN_V(tgMH_MIN_S)( vV1, vV1 );
        VEC_S_T(1,C)                        vA = FCN_V(tgMH_MIN_S)( vV1, vV2 );

        Test__Expect_EQ(0, memcmp( &vV0, &v8, sizeof( VEC_S_T(1) ) ));
        Test__Expect_EQ(0, memcmp( &vV1, &v9, sizeof( VEC_S_T(1) ) ));
        Test__Expect_EQ(0, memcmp( &vV1, &vA, sizeof( VEC_S_T(1) ) ));
    };

    /* Per-Lane check */
    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        VEC_S_T(1)                          v5 = FCN_V(tgMH_SET1_S)(1);

        v5.m_aData[uiIndex] = 0;
        {
            VEC_S_T(1,C)                        v7 = FCN_V(tgMH_MIN_S)( vV1, v5 );

            Test__Expect_EQ(0, memcmp( &v5, &v7, sizeof( VEC_S_T(1) ) ));
        };

        v5.m_aData[uiIndex] = 2;
        {
            VEC_S_T(1,C)                        v6 = FCN_V(tgMH_MIN_S)( vV1, v5 );

            Test__Expect_EQ(0, memcmp( &vV1, &v6, sizeof( VEC_S_T(1) ) ));
        };
    };

    /* Per-Lane Random Check */
    {
        VEC_S_T(1)                          vV3, vV4, vV6;

        vV3 = FCN_V(tgMH_RAND_S)();
        vV4 = FCN_V(tgMH_RAND_S)();
        vV6 = FCN_V(tgMH_MIN_S)( vV3, vV4 );

        for (TgRSIZE ui0 = 0; ui0 < TEMPLATE__VECTOR_DIM; ++ui0)
        {
            Test__Expect_EQ(vV6.m_aData[ui0], FCN_F(tgCM_MIN)(vV3.m_aData[ui0], vV4.m_aData[ui0]));
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_CMP_EQ_S) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_CMP_EQ_S) )
{
    VEC_S_T(1,C)                        vV0 = FCN_V(tgMH_SET1_S)(0);
    VEC_S_T(1,C)                        vV1 = FCN_V(tgMH_SET1_S)(1);
    VEC_S_T(1,C)                        vV2 = FCN_V(tgMH_SET1_S)(2);
    VEC_S_T(1)                          vV3, vT, vF;
    TgUN_SCALAR                         test = { (TgUINT_E64)-1 };

    (void)test;

    tgMM_Set_U08_0xFF( &vT, sizeof( VEC_S_T(1) ) );
    tgMM_Set_U08_0x00( &vF, sizeof( VEC_S_T(1) ) );

    vV3 = FCN_V(tgMH_CMP_EQ_S)( vV0, vV0 ); Test__Expect_EQ(0, memcmp( &vT, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_EQ_S)( vV0, vV1 ); Test__Expect_EQ(0, memcmp( &vF, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_EQ_S)( vV0, vV2 ); Test__Expect_EQ(0, memcmp( &vF, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_EQ_S)( vV1, vV0 ); Test__Expect_EQ(0, memcmp( &vF, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_EQ_S)( vV1, vV1 ); Test__Expect_EQ(0, memcmp( &vT, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_EQ_S)( vV1, vV2 ); Test__Expect_EQ(0, memcmp( &vF, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_EQ_S)( vV2, vV0 ); Test__Expect_EQ(0, memcmp( &vF, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_EQ_S)( vV2, vV1 ); Test__Expect_EQ(0, memcmp( &vF, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_EQ_S)( vV2, vV2 ); Test__Expect_EQ(0, memcmp( &vT, &vV3, sizeof( VEC_S_T(1) ) ));

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        vV3 = FCN_V(tgMH_SET1_S)(1);

        Test__Expect_EQ(true, FCN_V(tgMH_CMP_ALL_TO_BOOL_S)( FCN_V(tgMH_CMP_EQ_S)( vV1, vV3 ) ));
        vV3.m_aData[uiIndex] = 0;
        Test__Expect_EQ(false, FCN_V(tgMH_CMP_ALL_TO_BOOL_S)( FCN_V(tgMH_CMP_EQ_S)( vV1, vV3 ) ));

        {
            VEC_S_T(1,C)                        vV4 = FCN_V(tgMH_CMP_EQ_S)( vV1, vV3 );

            for (TgRSIZE uiCheck = 0; uiCheck < TEMPLATE__VECTOR_DIM; ++uiCheck)
            {
                if (uiCheck != uiIndex)
                {
                    Test__Expect_EQ(0, memcmp( &vT, vV4.m_aData + uiCheck, sizeof( VAR_T() ) ));
                }
                else
                {
                    Test__Expect_EQ(0, memcmp( &vF, vV4.m_aData + uiCheck, sizeof( VAR_T() ) ));
                };
            };
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_CMP_NE_S) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_CMP_NE_S) )
{
    VEC_S_T(1,C)                        vV0 = FCN_V(tgMH_SET1_S)(0);
    VEC_S_T(1,C)                        vV1 = FCN_V(tgMH_SET1_S)(1);
    VEC_S_T(1,C)                        vV2 = FCN_V(tgMH_SET1_S)(2);
    VEC_S_T(1)                          vV3, vT, vF;

    tgMM_Set_U08_0xFF( &vT, sizeof( VEC_S_T(1) ) );
    tgMM_Set_U08_0x00( &vF, sizeof( VEC_S_T(1) ) );

    vV3 = FCN_V(tgMH_CMP_NE_S)( vV0, vV0 ); Test__Expect_EQ(0, memcmp( &vF, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_NE_S)( vV0, vV1 ); Test__Expect_EQ(0, memcmp( &vT, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_NE_S)( vV0, vV2 ); Test__Expect_EQ(0, memcmp( &vT, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_NE_S)( vV1, vV0 ); Test__Expect_EQ(0, memcmp( &vT, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_NE_S)( vV1, vV1 ); Test__Expect_EQ(0, memcmp( &vF, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_NE_S)( vV1, vV2 ); Test__Expect_EQ(0, memcmp( &vT, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_NE_S)( vV2, vV0 ); Test__Expect_EQ(0, memcmp( &vT, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_NE_S)( vV2, vV1 ); Test__Expect_EQ(0, memcmp( &vT, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_NE_S)( vV2, vV2 ); Test__Expect_EQ(0, memcmp( &vF, &vV3, sizeof( VEC_S_T(1) ) ));

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        vV3 = FCN_V(tgMH_SET1_S)(1);

        Test__Expect_EQ(false, FCN_V(tgMH_CMP_ALL_TO_BOOL_S)( FCN_V(tgMH_CMP_NE_S)( vV1, vV3 ) ));
        vV3.m_aData[uiIndex] = 0;
        Test__Expect_EQ(false, FCN_V(tgMH_CMP_ALL_TO_BOOL_S)( FCN_V(tgMH_CMP_NE_S)( vV1, vV3 ) ));

        {
            VEC_S_T(1,C)                        vV4 = FCN_V(tgMH_CMP_NE_S)( vV1, vV3 );

            for (TgRSIZE uiCheck = 0; uiCheck < TEMPLATE__VECTOR_DIM; ++uiCheck)
            {
                if (uiCheck == uiIndex)
                {
                    Test__Expect_EQ(0, memcmp( &vT, vV4.m_aData + uiCheck, sizeof( VAR_T() ) ));
                }
                else
                {
                    Test__Expect_EQ(0, memcmp( &vF, vV4.m_aData + uiCheck, sizeof( VAR_T() ) ));
                };
            };
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_CMP_GE_S) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_CMP_GE_S) )
{
    VEC_S_T(1,C)                        vV0 = FCN_V(tgMH_SET1_S)(0);
    VEC_S_T(1,C)                        vV1 = FCN_V(tgMH_SET1_S)(1);
    VEC_S_T(1,C)                        vV2 = FCN_V(tgMH_SET1_S)(2);
    VEC_S_T(1)                          vV3, vT, vF;

    tgMM_Set_U08_0xFF( &vT, sizeof( VEC_S_T(1) ) );
    tgMM_Set_U08_0x00( &vF, sizeof( VEC_S_T(1) ) );

    vV3 = FCN_V(tgMH_CMP_GE_S)( vV0, vV0 ); Test__Expect_EQ(0, memcmp( &vT, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_GE_S)( vV0, vV1 ); Test__Expect_EQ(0, memcmp( &vF, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_GE_S)( vV0, vV2 ); Test__Expect_EQ(0, memcmp( &vF, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_GE_S)( vV1, vV0 ); Test__Expect_EQ(0, memcmp( &vT, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_GE_S)( vV1, vV1 ); Test__Expect_EQ(0, memcmp( &vT, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_GE_S)( vV1, vV2 ); Test__Expect_EQ(0, memcmp( &vF, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_GE_S)( vV2, vV0 ); Test__Expect_EQ(0, memcmp( &vT, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_GE_S)( vV2, vV1 ); Test__Expect_EQ(0, memcmp( &vT, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_GE_S)( vV2, vV2 ); Test__Expect_EQ(0, memcmp( &vT, &vV3, sizeof( VEC_S_T(1) ) ));

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        vV3 = FCN_V(tgMH_SET1_S)(1);

        Test__Expect_EQ(true, FCN_V(tgMH_CMP_ALL_TO_BOOL_S)( FCN_V(tgMH_CMP_GE_S)( vV1, vV3 ) ));
        vV3.m_aData[uiIndex] = 0;
        Test__Expect_EQ(true, FCN_V(tgMH_CMP_ALL_TO_BOOL_S)( FCN_V(tgMH_CMP_GE_S)( vV1, vV3 ) ));

        {
            VEC_S_T(1,C)                        vV4 = FCN_V(tgMH_CMP_GE_S)( vV1, vV3 );

            for (TgRSIZE uiCheck = 0; uiCheck < TEMPLATE__VECTOR_DIM; ++uiCheck)
            {
                Test__Expect_EQ(0, memcmp( &vT, vV4.m_aData + uiCheck, sizeof( VAR_T() ) ));
            };
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_CMP_GT_S) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_CMP_GT_S) )
{
    VEC_S_T(1,C)                        vV0 = FCN_V(tgMH_SET1_S)(0);
    VEC_S_T(1,C)                        vV1 = FCN_V(tgMH_SET1_S)(1);
    VEC_S_T(1,C)                        vV2 = FCN_V(tgMH_SET1_S)(2);
    VEC_S_T(1)                          vV3, vT, vF;

    tgMM_Set_U08_0xFF( &vT, sizeof( VEC_S_T(1) ) );
    tgMM_Set_U08_0x00( &vF, sizeof( VEC_S_T(1) ) );

    vV3 = FCN_V(tgMH_CMP_GT_S)( vV0, vV0 ); Test__Expect_EQ(0, memcmp( &vF, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_GT_S)( vV0, vV1 ); Test__Expect_EQ(0, memcmp( &vF, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_GT_S)( vV0, vV2 ); Test__Expect_EQ(0, memcmp( &vF, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_GT_S)( vV1, vV0 ); Test__Expect_EQ(0, memcmp( &vT, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_GT_S)( vV1, vV1 ); Test__Expect_EQ(0, memcmp( &vF, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_GT_S)( vV1, vV2 ); Test__Expect_EQ(0, memcmp( &vF, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_GT_S)( vV2, vV0 ); Test__Expect_EQ(0, memcmp( &vT, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_GT_S)( vV2, vV1 ); Test__Expect_EQ(0, memcmp( &vT, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_GT_S)( vV2, vV2 ); Test__Expect_EQ(0, memcmp( &vF, &vV3, sizeof( VEC_S_T(1) ) ));

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        vV3 = FCN_V(tgMH_SET1_S)(1);

        Test__Expect_EQ(false, FCN_V(tgMH_CMP_ALL_TO_BOOL_S)( FCN_V(tgMH_CMP_GT_S)( vV1, vV3 ) ));
        vV3.m_aData[uiIndex] = 0;
        Test__Expect_EQ(false, FCN_V(tgMH_CMP_ALL_TO_BOOL_S)( FCN_V(tgMH_CMP_GT_S)( vV1, vV3 ) ));

        {
            VEC_S_T(1,C)                        vV4 = FCN_V(tgMH_CMP_GT_S)( vV1, vV3 );

            for (TgRSIZE uiCheck = 0; uiCheck < TEMPLATE__VECTOR_DIM; ++uiCheck)
            {
                if (uiCheck == uiIndex)
                {
                    Test__Expect_EQ(0, memcmp( &vT, vV4.m_aData + uiCheck, sizeof( VAR_T() ) ));
                }
                else
                {
                    Test__Expect_EQ(0, memcmp( &vF, vV4.m_aData + uiCheck, sizeof( VAR_T() ) ));
                };
            };
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_CMP_LE_S) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_CMP_LE_S) )
{
    VEC_S_T(1,C)                        vV0 = FCN_V(tgMH_SET1_S)(0);
    VEC_S_T(1,C)                        vV1 = FCN_V(tgMH_SET1_S)(1);
    VEC_S_T(1,C)                        vV2 = FCN_V(tgMH_SET1_S)(2);
    VEC_S_T(1)                          vV3, vT, vF;

    tgMM_Set_U08_0xFF( &vT, sizeof( VEC_S_T(1) ) );
    tgMM_Set_U08_0x00( &vF, sizeof( VEC_S_T(1) ) );

    vV3 = FCN_V(tgMH_CMP_LE_S)( vV0, vV0 ); Test__Expect_EQ(0, memcmp( &vT, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_LE_S)( vV0, vV1 ); Test__Expect_EQ(0, memcmp( &vT, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_LE_S)( vV0, vV2 ); Test__Expect_EQ(0, memcmp( &vT, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_LE_S)( vV1, vV0 ); Test__Expect_EQ(0, memcmp( &vF, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_LE_S)( vV1, vV1 ); Test__Expect_EQ(0, memcmp( &vT, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_LE_S)( vV1, vV2 ); Test__Expect_EQ(0, memcmp( &vT, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_LE_S)( vV2, vV0 ); Test__Expect_EQ(0, memcmp( &vF, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_LE_S)( vV2, vV1 ); Test__Expect_EQ(0, memcmp( &vF, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_LE_S)( vV2, vV2 ); Test__Expect_EQ(0, memcmp( &vT, &vV3, sizeof( VEC_S_T(1) ) ));

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        vV3 = FCN_V(tgMH_SET1_S)(1);

        Test__Expect_EQ(true, FCN_V(tgMH_CMP_ALL_TO_BOOL_S)( FCN_V(tgMH_CMP_LE_S)( vV1, vV3 ) ));
        vV3.m_aData[uiIndex] = 0;
        Test__Expect_EQ(false, FCN_V(tgMH_CMP_ALL_TO_BOOL_S)( FCN_V(tgMH_CMP_LE_S)( vV1, vV3 ) ));

        {
            VEC_S_T(1,C)                        vV4 = FCN_V(tgMH_CMP_LE_S)( vV1, vV3 );

            for (TgRSIZE uiCheck = 0; uiCheck < TEMPLATE__VECTOR_DIM; ++uiCheck)
            {
                if (uiCheck != uiIndex)
                {
                    Test__Expect_EQ(0, memcmp( &vT, vV4.m_aData + uiCheck, sizeof( VAR_T() ) ));
                }
                else
                {
                    Test__Expect_EQ(0, memcmp( &vF, vV4.m_aData + uiCheck, sizeof( VAR_T() ) ));
                };
            };
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_CMP_LT_S) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_CMP_LT_S) )
{
    VEC_S_T(1,C)                        vV0 = FCN_V(tgMH_SET1_S)(0);
    VEC_S_T(1,C)                        vV1 = FCN_V(tgMH_SET1_S)(1);
    VEC_S_T(1,C)                        vV2 = FCN_V(tgMH_SET1_S)(2);
    VEC_S_T(1)                          vV3, vT, vF;

    tgMM_Set_U08_0xFF( &vT, sizeof( VEC_S_T(1) ) );
    tgMM_Set_U08_0x00( &vF, sizeof( VEC_S_T(1) ) );

    vV3 = FCN_V(tgMH_CMP_LT_S)( vV0, vV0 ); Test__Expect_EQ(0, memcmp( &vF, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_LT_S)( vV0, vV1 ); Test__Expect_EQ(0, memcmp( &vT, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_LT_S)( vV0, vV2 ); Test__Expect_EQ(0, memcmp( &vT, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_LT_S)( vV1, vV0 ); Test__Expect_EQ(0, memcmp( &vF, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_LT_S)( vV1, vV1 ); Test__Expect_EQ(0, memcmp( &vF, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_LT_S)( vV1, vV2 ); Test__Expect_EQ(0, memcmp( &vT, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_LT_S)( vV2, vV0 ); Test__Expect_EQ(0, memcmp( &vF, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_LT_S)( vV2, vV1 ); Test__Expect_EQ(0, memcmp( &vF, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_LT_S)( vV2, vV2 ); Test__Expect_EQ(0, memcmp( &vF, &vV3, sizeof( VEC_S_T(1) ) ));

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        vV3 = FCN_V(tgMH_SET1_S)(1);

        Test__Expect_EQ(false, FCN_V(tgMH_CMP_ALL_TO_BOOL_S)( FCN_V(tgMH_CMP_LT_S)(vV1, vV3) ));
        vV3.m_aData[uiIndex] = 0;
        Test__Expect_EQ(false, FCN_V(tgMH_CMP_ALL_TO_BOOL_S)( FCN_V(tgMH_CMP_LT_S)(vV1, vV3) ));

        {
            VEC_S_T(1,C)                        vV4 = FCN_V(tgMH_CMP_LT_S)(vV1, vV3);

            for (TgRSIZE uiCheck = 0; uiCheck < TEMPLATE__VECTOR_DIM; ++uiCheck)
            {
                Test__Expect_EQ((VAR_T())0, vV4.m_aData[uiCheck]);
            };
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(MATH_VECTOR) ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(MATH_VECTOR) )
{
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_SETU_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_SETA_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_SET1_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_PERM_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_SEL_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_AND_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_OR_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_XOR_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_MAX_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_MIN_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_CMP_EQ_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_CMP_NE_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_CMP_GE_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_CMP_GT_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_CMP_LE_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_CMP_LT_S)() );

#if (!VEC_IS_NATIVE && TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE) || VEC_IS_NATIVE /* MACRO_COMPILE_NATIVE_VECTOR_GUARD */
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_SETU)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_SETA)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_SET1)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_SEL)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_AND)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_OR)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_XOR)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_MAX)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_MIN)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_CMP_EQ)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_CMP_NE)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_CMP_GE)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_CMP_GT)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_CMP_LE)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_CMP_LT)() );

/*# ((128 == TEMPLATE__TYPE_SIZE * TEMPLATE__VECTOR_DIM) && (32 >= TEMPLATE__TYPE_SIZE)) */
#endif

#if defined(TEMPLATE__ENABLE_INTEGER)
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_ADD_CLP_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_ADD_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_SUB_CLP_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_SUB_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_AVG_S)() );

#if (!VEC_IS_NATIVE && TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE) || VEC_IS_NATIVE /* MACRO_COMPILE_NATIVE_VECTOR_GUARD */
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_ADD_CLP)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_ADD)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_SUB_CLP)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_SUB)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_AVG)() );

/*# ((128 == TEMPLATE__TYPE_SIZE * TEMPLATE__VECTOR_DIM) && (32 >= TEMPLATE__TYPE_SIZE)) */
#endif

/*# defined(TEMPLATE__ENABLE_INTEGER) */
#else
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_ADD_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_MAD_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_NMS_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_DOT_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_MUL_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_DIV_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_SUB_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_LSQ_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_LEN_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_NEG_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_SQRT_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_RSQRT_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_NORM_LEN_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_NORM_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_FLR_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_CEL_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_CLP_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_SAT_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_NAN_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_BND_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_MAD_SVV_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_MAD_VSV_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_NMS_SVV_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_NMS_VSV_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_MUL_SV_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_MUL_VS_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_DIV_SV_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_DIV_VS_S)() );

#if (4 == TEMPLATE__VECTOR_DIM)
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_Init_ELEM_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_Init_Point_ELEM_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_Init_Vector_ELEM_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_Init_Point_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_Init_Vector_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_RAND_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_Init_Ortho_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_Init_Basis_From_Vector_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_Is_Valid_Point_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_Is_Valid_Vector_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_DOT3_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_CX_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_UCX_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_UCX_LEN_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_NORM3_LEN_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_NORM3_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_PRX3_CMP_EQ_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_Is_PRX_CMP_EQ_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_QT_Init_Axis_Angle_ELEM_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_QT_Init_Axis_Angle_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_QT_Init_Euler_ELEM_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_QT_Init_Euler_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_QT_Init_Euler_X_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_QT_Init_Euler_Y_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_QT_Init_Euler_Z_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_Quat_To_Euler_ELEM_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_Quat_To_Euler_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_QT_INV_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_QT_MUL_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_QT_Slerp_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_QT_Vector_To_Vector_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_QT_TX_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_QT_INV_TX_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_Rotate_Vector_Euler_X_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_Rotate_Vector_Euler_Y_S)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_Rotate_Vector_Euler_Z_S)() );

#endif
#if (!VEC_IS_NATIVE && TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE) || VEC_IS_NATIVE /* MACRO_COMPILE_NATIVE_VECTOR_GUARD */
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_ADD)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_MAD)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_NMS)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_DOT)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_MUL)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_DIV)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_SUB)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_LSQ)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_LEN)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_NEG)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_SQRT)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_RSQRT)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_NORM)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_NORM_LEN)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_FLR)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_CEL)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_CLP)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_SAT)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_NAN)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_BND)() );

#if (4 == TEMPLATE__VECTOR_DIM)
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_Init_ELEM)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_Init_Point_ELEM)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_Init_Vector_ELEM)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_Init_Point)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_Init_Vector)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_RAND)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_SPX)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_SPY)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_SPZ)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_SPW)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_DOT3)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_CX)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_UCX)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_UCX_LEN)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_PRX3_CMP_EQ)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_Is_PRX_CMP_EQ)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_QT_INV)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_QT_MUL)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_QT_Slerp)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_QT_Vector_To_Vector)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_QT_TX)() );
    Test__Expect_EQ( KTgS_OK, FCN_V_UT(tgMH_QT_INV_TX)() );

#endif
#endif


/*# defined(TEMPLATE__ENABLE_INTEGER) */
#endif

    TEST_END_METHOD( KTgS_OK );
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

#undef FCN_V_UT
#undef FCN_V_UT_1
#undef FCN_V_UT_2
