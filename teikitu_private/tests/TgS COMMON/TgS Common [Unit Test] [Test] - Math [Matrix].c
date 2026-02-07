/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common [Unit Test] [Test] - Math [Matrix].c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
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

#if (!VEC_IS_NATIVE && TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE) || VEC_IS_NATIVE /* MACRO_COMPILE_NATIVE_MATRIX_GUARD */

/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- FCN_M_UT(tgMH_CLR) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_CLR) )
{
    union
    {
        VEC_T(TEMPLATE__VECTOR_COL)         mMV;
        VEC_S_T(TEMPLATE__VECTOR_COL)       mMS;
    }                                   uMX, uMZ;

    FCN_M(tgMH_CLR_S)( &uMZ.mMS );
    FCN_M(tgMH_CLR)( &uMX.mMV );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL * TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_EQ( true, FCN_F(tgCM_NR0)( uMX.mMS.m_aElement[uiIndex] - uMZ.mMS.m_aElement[uiIndex] ) );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_MAX) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_MAX) )
{
    union
    {
        VEC_T(TEMPLATE__VECTOR_COL)         mMV;
        VEC_S_T(TEMPLATE__VECTOR_COL)       mMS;
    }                                   uM0, uM1, uMX, uMZ;

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        uM0.mMS.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
        uM1.mMS.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
    };

    FCN_M(tgMH_MAX_S)( &uMZ.mMS, &uM0.mMS, &uM1.mMS );
    FCN_M(tgMH_MAX)( &uMX.mMV, &uM0.mMV, &uM1.mMV );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL * TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_EQ( true, FCN_F(tgCM_NR0)( uMX.mMS.m_aElement[uiIndex] - uMZ.mMS.m_aElement[uiIndex] ) );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_MIN) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_MIN) )
{
    union
    {
        VEC_T(TEMPLATE__VECTOR_COL)         mMV;
        VEC_S_T(TEMPLATE__VECTOR_COL)       mMS;
    }                                   uM0, uM1, uMX, uMZ;

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        uM0.mMS.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
        uM1.mMS.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
    };

    FCN_M(tgMH_MIN_S)( &uMZ.mMS, &uM0.mMS, &uM1.mMS );
    FCN_M(tgMH_MIN)( &uMX.mMV, &uM0.mMV, &uM1.mMV );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL * TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_EQ( true, FCN_F(tgCM_NR0)( uMX.mMS.m_aElement[uiIndex] - uMZ.mMS.m_aElement[uiIndex] ) );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_AND) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_AND) )
{
    union
    {
        VEC_T(TEMPLATE__VECTOR_COL)         mMV;
        VEC_S_T(TEMPLATE__VECTOR_COL)       mMS;
        TgUINT_E08                          auiM0[sizeof(VEC_T(TEMPLATE__VECTOR_COL))];
    }                                   uM0, uM1, uMX, uMZ;

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        uM0.mMS.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
        uM1.mMS.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
    };

    FCN_M(tgMH_AND_S)( &uMZ.mMS, &uM0.mMS, &uM1.mMS );
    FCN_M(tgMH_AND)( &uMX.mMV, &uM0.mMV, &uM1.mMV );

    for (TgRSIZE uiIndex = 0; uiIndex < (TgRSIZE)(sizeof( VEC_S_T(TEMPLATE__VECTOR_COL) )); ++uiIndex)
    {
        Test__Expect_EQ( uMX.auiM0[uiIndex], uMZ.auiM0[uiIndex] );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_OR) -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_OR) )
{
    union
    {
        VEC_T(TEMPLATE__VECTOR_COL)         mMV;
        VEC_S_T(TEMPLATE__VECTOR_COL)       mMS;
        TgUINT_E08                          auiM0[sizeof(VEC_T(TEMPLATE__VECTOR_COL))];
    }                                   uM0, uM1, uMX, uMZ;

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        uM0.mMS.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
        uM1.mMS.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
    };

    FCN_M(tgMH_OR_S)( &uMZ.mMS, &uM0.mMS, &uM1.mMS );
    FCN_M(tgMH_OR)( &uMX.mMV, &uM0.mMV, &uM1.mMV );

    for (TgRSIZE uiIndex = 0; uiIndex < (TgRSIZE)(sizeof( VEC_S_T(TEMPLATE__VECTOR_COL) )); ++uiIndex)
    {
        Test__Expect_EQ( uMX.auiM0[uiIndex], uMZ.auiM0[uiIndex] );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_XOR) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_XOR) )
{
    union
    {
        VEC_T(TEMPLATE__VECTOR_COL)         mMV;
        VEC_S_T(TEMPLATE__VECTOR_COL)       mMS;
        TgUINT_E08                          auiM0[sizeof(VEC_T(TEMPLATE__VECTOR_COL))];
    }                                   uM0, uM1, uMX, uMZ;

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        uM0.mMS.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
        uM1.mMS.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
    };

    FCN_M(tgMH_XOR_S)( &uMZ.mMS, &uM0.mMS, &uM1.mMS );
    FCN_M(tgMH_XOR)( &uMX.mMV, &uM0.mMV, &uM1.mMV );

    for (TgRSIZE uiIndex = 0; uiIndex < (TgRSIZE)(sizeof( VEC_S_T(TEMPLATE__VECTOR_COL) )); ++uiIndex)
    {
        Test__Expect_EQ( uMX.auiM0[uiIndex], uMZ.auiM0[uiIndex] );
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
