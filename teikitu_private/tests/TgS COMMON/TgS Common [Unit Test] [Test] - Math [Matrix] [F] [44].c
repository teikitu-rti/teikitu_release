/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common [Unit Test] [Test] - Math [Matrix] [F] [44].c_inc
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

#if (!VEC_IS_NATIVE && TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE) || VEC_IS_NATIVE /* MACRO_COMPILE_NATIVE_MATRIX_GUARD */

/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- FCN_M_UT(tgMH_CAT_34_44) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_CAT_34_44) )
{
    union
    {
        VEC_T(4)                            m4_V;
        VEC_S_T(4)                          m4_S;
        VEC_T(3)                            m3_V;
        VEC_S_T(3)                          m3_S;
    }                                   uM0, uM1, uMX, uMZ;

    for (TgRSIZE uiIndex = 0; uiIndex < 4; ++uiIndex)
    {
        uM0.m4_S.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
        uM1.m4_S.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
    };

    FCN_M(tgMH_CAT_34_44_S)( &uMZ.m4_S, &uM0.m3_S, &uM1.m4_S );
    FCN_M(tgMH_CAT_34_44)( &uMX.m4_V, &uM0.m3_V, &uM1.m4_V );

    for (TgRSIZE uiIndex = 0; uiIndex < 16; ++uiIndex)
    {
        Test__Expect_EQ( true, FCN_F(tgCM_NR0)( uMX.m4_S.m_aElement[uiIndex] - uMZ.m4_S.m_aElement[uiIndex] ) );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_CAT_44_34) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_CAT_44_34) )
{
    union
    {
        VEC_T(4)                            m4_V;
        VEC_S_T(4)                          m4_S;
        VEC_T(3)                            m3_V;
        VEC_S_T(3)                          m3_S;
    }                                   uM0, uM1, uMX, uMZ;

    for (TgRSIZE uiIndex = 0; uiIndex < 4; ++uiIndex)
    {
        uM0.m4_S.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
        uM1.m4_S.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
    };

    FCN_M(tgMH_CAT_44_34_S)( &uMZ.m4_S, &uM0.m4_S, &uM1.m3_S );
    FCN_M(tgMH_CAT_44_34)( &uMX.m4_V, &uM0.m4_V, &uM1.m3_V );

    for (TgRSIZE uiIndex = 0; uiIndex < 16; ++uiIndex)
    {
        Test__Expect_EQ( true, FCN_F(tgCM_NR0)( uMX.m4_S.m_aElement[uiIndex] - uMZ.m4_S.m_aElement[uiIndex] ) );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_TR) -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_TR) )
{
    union
    {
        VEC_T(4)                            mMV;
        VEC_S_T(4)                          mMS;
    }                                   uM0, uMX, uMZ;

    for (TgRSIZE uiIndex = 0; uiIndex < 4; ++uiIndex)
    {
        uM0.mMS.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
    };

    FCN_M(tgMH_TR_S)( &uMZ.mMS, &uM0.mMS );
    FCN_M(tgMH_TR)( &uMX.mMV, &uM0.mMV );

    for (TgRSIZE uiIndex = 0; uiIndex < 16; ++uiIndex)
    {
        Test__Expect_EQ( true, FCN_F(tgCM_NR0)( uMX.mMS.m_aElement[uiIndex] - uMZ.mMS.m_aElement[uiIndex] ) );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* =============================================================================================================================================================================== */

/*# (!VEC_IS_NATIVE && TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE) || VEC_IS_NATIVE */
#endif

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

#undef FCN_M_UT
#undef FCN_UT_1
#undef FCN_UT_2
