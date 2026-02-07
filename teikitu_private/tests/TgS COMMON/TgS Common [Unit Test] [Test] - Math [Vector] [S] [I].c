/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common [Unit Test] [Test] - Math [Vector] [S] [I].c
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
#endif

#if !defined (ENABLE_RELOAD_GUARD)
    #define ENABLE_RELOAD_GUARD
    #define TEMPLATE__ENABLE_UNSIGNED
    #include __FILE__
    #undef TEMPLATE__ENABLE_UNSIGNED
    #undef ENABLE_RELOAD_GUARD
#endif

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

#define FCN_V_UT(...)                       MULTI_MACRO(FCN_V_UT, __VA_ARGS__)
#define FCN_V_UT_1(F)                       TgMACRO_CONCAT5( UNIT_TEST__TEST__##F, _, GENERATE__VEC_DESC, _, 1 )
#define FCN_V_UT_2(F, COL)                  TgMACRO_CONCAT5( UNIT_TEST__TEST__##F, _, GENERATE__VEC_DESC, _, COL )

#if (!VEC_IS_NATIVE && TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE) || VEC_IS_NATIVE /* MACRO_COMPILE_NATIVE_MATRIX_GUARD */

/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- FCN_V_UT(tgMH_ADD_CLP_S) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_ADD_CLP_S) )
{
    VEC_S_T(1,C)                        vX1 = FCN_V(tgMH_SET1_S)( (VAR_T())0 );
    VEC_S_T(1,C)                        vP4 = FCN_V(tgMH_SET1_S)( (VAR_T())4 );
    VEC_S_T(1,C)                        vP8 = FCN_V(tgMH_SET1_S)( (VAR_T())8 );
    VEC_S_T(1,C)                        vX0 = FCN_V(tgMH_SET1_S)( VAR_K(KTgMAX) );
    VEC_S_T(1,C)                        vX4 = FCN_V(tgMH_SET1_S)( VAR_K(KTgMAX) - 4 );
    VEC_S_T(1)                          vRet;

    vRet = FCN_V(tgMH_ADD_CLP_S)( vP4, vP4 ); Test__Expect_EQ( true, FCN_V(tgMH_CMP_ALL_TO_BOOL_S)( FCN_V(tgMH_CMP_EQ_S)( vP8, vRet ) )); /* P P P */
    vRet = FCN_V(tgMH_ADD_CLP_S)( vP4, vX1 ); Test__Expect_EQ( true, FCN_V(tgMH_CMP_ALL_TO_BOOL_S)( FCN_V(tgMH_CMP_EQ_S)( vP4, vRet ) )); /* P P Z */
    vRet = FCN_V(tgMH_ADD_CLP_S)( vX1, vP4 ); Test__Expect_EQ( true, FCN_V(tgMH_CMP_ALL_TO_BOOL_S)( FCN_V(tgMH_CMP_EQ_S)( vP4, vRet ) )); /* P Z P */
    vRet = FCN_V(tgMH_ADD_CLP_S)( vP8, vX4 ); Test__Expect_EQ( true, FCN_V(tgMH_CMP_ALL_TO_BOOL_S)( FCN_V(tgMH_CMP_EQ_S)( vX0, vRet ) )); /* X P N */
    vRet = FCN_V(tgMH_ADD_CLP_S)( vX4, vP8 ); Test__Expect_EQ( true, FCN_V(tgMH_CMP_ALL_TO_BOOL_S)( FCN_V(tgMH_CMP_EQ_S)( vX0, vRet ) )); /* X N P */

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_ADD_S) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_ADD_S) )
{
    VEC_S_T(1,C)                        vX1 = FCN_V(tgMH_SET1_S)((VAR_T())0);
    VEC_S_T(1,C)                        vP4 = FCN_V(tgMH_SET1_S)((VAR_T())4);
    VEC_S_T(1,C)                        vN4 = FCN_V(tgMH_SET1_S)((VAR_T())-4);
    VEC_S_T(1,C)                        vP8 = FCN_V(tgMH_SET1_S)((VAR_T())8);
    VEC_S_T(1,C)                        vN8 = FCN_V(tgMH_SET1_S)((VAR_T())-8);
    VEC_S_T(1,C)                        vX4 = FCN_V(tgMH_SET1_S)(VAR_K(KTgMAX) - 4);
    VEC_S_T(1,C)                        vY3 = FCN_V(tgMH_SET1_S)(VAR_K(KTgMIN) + 3);

    VEC_S_T(1)                          vRet;

    vRet = FCN_V(tgMH_ADD_S)( vP4, vP4 ); Test__Expect_EQ( true, FCN_V(tgMH_CMP_ALL_TO_BOOL_S)( FCN_V(tgMH_CMP_EQ_S)( vP8, vRet ) )); /* P P P */
    vRet = FCN_V(tgMH_ADD_S)( vP4, vX1 ); Test__Expect_EQ( true, FCN_V(tgMH_CMP_ALL_TO_BOOL_S)( FCN_V(tgMH_CMP_EQ_S)( vP4, vRet ) )); /* P P Z */
    vRet = FCN_V(tgMH_ADD_S)( vP8, vN4 ); Test__Expect_EQ( true, FCN_V(tgMH_CMP_ALL_TO_BOOL_S)( FCN_V(tgMH_CMP_EQ_S)( vP4, vRet ) )); /* P P N */
    vRet = FCN_V(tgMH_ADD_S)( vX1, vP4 ); Test__Expect_EQ( true, FCN_V(tgMH_CMP_ALL_TO_BOOL_S)( FCN_V(tgMH_CMP_EQ_S)( vP4, vRet ) )); /* P Z P */
    vRet = FCN_V(tgMH_ADD_S)( vN4, vP8 ); Test__Expect_EQ( true, FCN_V(tgMH_CMP_ALL_TO_BOOL_S)( FCN_V(tgMH_CMP_EQ_S)( vP4, vRet ) )); /* P N P */
    vRet = FCN_V(tgMH_ADD_S)( vY3, vN8 ); Test__Expect_EQ( true, FCN_V(tgMH_CMP_ALL_TO_BOOL_S)( FCN_V(tgMH_CMP_EQ_S)( vX4, vRet ) )); /* P N N */
    vRet = FCN_V(tgMH_ADD_S)( vP4, vN4 ); Test__Expect_EQ( true, FCN_V(tgMH_CMP_ALL_TO_BOOL_S)( FCN_V(tgMH_CMP_EQ_S)( vX1, vRet ) )); /* Z P N */
    vRet = FCN_V(tgMH_ADD_S)( vX1, vX1 ); Test__Expect_EQ( true, FCN_V(tgMH_CMP_ALL_TO_BOOL_S)( FCN_V(tgMH_CMP_EQ_S)( vX1, vRet ) )); /* Z Z Z */
    vRet = FCN_V(tgMH_ADD_S)( vN4, vP4 ); Test__Expect_EQ( true, FCN_V(tgMH_CMP_ALL_TO_BOOL_S)( FCN_V(tgMH_CMP_EQ_S)( vX1, vRet ) )); /* Z N P */
    vRet = FCN_V(tgMH_ADD_S)( vX4, vP8 ); Test__Expect_EQ( true, FCN_V(tgMH_CMP_ALL_TO_BOOL_S)( FCN_V(tgMH_CMP_EQ_S)( vY3, vRet ) )); /* N P P */
    vRet = FCN_V(tgMH_ADD_S)( vP4, vN8 ); Test__Expect_EQ( true, FCN_V(tgMH_CMP_ALL_TO_BOOL_S)( FCN_V(tgMH_CMP_EQ_S)( vN4, vRet ) )); /* N P N */
    vRet = FCN_V(tgMH_ADD_S)( vX1, vN4 ); Test__Expect_EQ( true, FCN_V(tgMH_CMP_ALL_TO_BOOL_S)( FCN_V(tgMH_CMP_EQ_S)( vN4, vRet ) )); /* N Z N */
    vRet = FCN_V(tgMH_ADD_S)( vN8, vP4 ); Test__Expect_EQ( true, FCN_V(tgMH_CMP_ALL_TO_BOOL_S)( FCN_V(tgMH_CMP_EQ_S)( vN4, vRet ) )); /* N N P */
    vRet = FCN_V(tgMH_ADD_S)( vN4, vX1 ); Test__Expect_EQ( true, FCN_V(tgMH_CMP_ALL_TO_BOOL_S)( FCN_V(tgMH_CMP_EQ_S)( vN4, vRet ) )); /* N N Z */
    vRet = FCN_V(tgMH_ADD_S)( vN4, vN4 ); Test__Expect_EQ( true, FCN_V(tgMH_CMP_ALL_TO_BOOL_S)( FCN_V(tgMH_CMP_EQ_S)( vN8, vRet ) )); /* N N N */

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_SUB_CLP_S) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_SUB_CLP_S) )
{
    VEC_S_T(1,C)                        vX1 = FCN_V(tgMH_SET1_S)((VAR_T())0);
    VEC_S_T(1,C)                        vP4 = FCN_V(tgMH_SET1_S)((VAR_T())4);
    VEC_S_T(1,C)                        vP8 = FCN_V(tgMH_SET1_S)((VAR_T())8);
    VEC_S_T(1,C)                        vY0 = FCN_V(tgMH_SET1_S)(VAR_K(KTgMIN));
    VEC_S_T(1,C)                        vY3 = FCN_V(tgMH_SET1_S)(VAR_K(KTgMIN) + 3);

    VEC_S_T(1)                          vRet;

    vRet = FCN_V(tgMH_SUB_CLP_S)( vP8, vP4 ); Test__Expect_EQ( true, FCN_V(tgMH_CMP_ALL_TO_BOOL_S)( FCN_V(tgMH_CMP_EQ_S)( vP4, vRet ) )); /* P P P */
    vRet = FCN_V(tgMH_SUB_CLP_S)( vP4, vX1 ); Test__Expect_EQ( true, FCN_V(tgMH_CMP_ALL_TO_BOOL_S)( FCN_V(tgMH_CMP_EQ_S)( vP4, vRet ) )); /* P P Z */
    vRet = FCN_V(tgMH_SUB_CLP_S)( vY0, vP4 ); Test__Expect_EQ( true, FCN_V(tgMH_CMP_ALL_TO_BOOL_S)( FCN_V(tgMH_CMP_EQ_S)( vY0, vRet ) )); /* P Z P */
    vRet = FCN_V(tgMH_SUB_CLP_S)( vY3, vP8 ); Test__Expect_EQ( true, FCN_V(tgMH_CMP_ALL_TO_BOOL_S)( FCN_V(tgMH_CMP_EQ_S)( vY0, vRet ) )); /* Z P N */

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_SUB_S) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_SUB_S) )
{
    VEC_S_T(1,C)                        vX1 = FCN_V(tgMH_SET1_S)((VAR_T())0);
    VEC_S_T(1,C)                        vP4 = FCN_V(tgMH_SET1_S)((VAR_T())4);
    VEC_S_T(1,C)                        vN4 = FCN_V(tgMH_SET1_S)((VAR_T())-4);
    VEC_S_T(1,C)                        vP8 = FCN_V(tgMH_SET1_S)((VAR_T())8);
    VEC_S_T(1,C)                        vN8 = FCN_V(tgMH_SET1_S)((VAR_T())-8);
    VEC_S_T(1,C)                        vX4 = FCN_V(tgMH_SET1_S)(VAR_K(KTgMAX) - 4);
    VEC_S_T(1,C)                        vY3 = FCN_V(tgMH_SET1_S)(VAR_K(KTgMIN) + 3);

    VEC_S_T(1)                          vRet;

    vRet = FCN_V(tgMH_SUB_S)( vP8, vP4 ); Test__Expect_EQ( true, FCN_V(tgMH_CMP_ALL_TO_BOOL_S)( FCN_V(tgMH_CMP_EQ_S)( vP4, vRet ) )); /* P P P */
    vRet = FCN_V(tgMH_SUB_S)( vP4, vX1 ); Test__Expect_EQ( true, FCN_V(tgMH_CMP_ALL_TO_BOOL_S)( FCN_V(tgMH_CMP_EQ_S)( vP4, vRet ) )); /* P P Z */
    vRet = FCN_V(tgMH_SUB_S)( vP4, vN4 ); Test__Expect_EQ( true, FCN_V(tgMH_CMP_ALL_TO_BOOL_S)( FCN_V(tgMH_CMP_EQ_S)( vP8, vRet ) )); /* P P N */
    vRet = FCN_V(tgMH_SUB_S)( vX1, vN4 ); Test__Expect_EQ( true, FCN_V(tgMH_CMP_ALL_TO_BOOL_S)( FCN_V(tgMH_CMP_EQ_S)( vP4, vRet ) )); /* P Z N */
    vRet = FCN_V(tgMH_SUB_S)( vY3, vP8 ); Test__Expect_EQ( true, FCN_V(tgMH_CMP_ALL_TO_BOOL_S)( FCN_V(tgMH_CMP_EQ_S)( vX4, vRet ) )); /* P N P */
    vRet = FCN_V(tgMH_SUB_S)( vN4, vN8 ); Test__Expect_EQ( true, FCN_V(tgMH_CMP_ALL_TO_BOOL_S)( FCN_V(tgMH_CMP_EQ_S)( vP4, vRet ) )); /* P N N */
    vRet = FCN_V(tgMH_SUB_S)( vP4, vP4 ); Test__Expect_EQ( true, FCN_V(tgMH_CMP_ALL_TO_BOOL_S)( FCN_V(tgMH_CMP_EQ_S)( vX1, vRet ) )); /* Z P P */
    vRet = FCN_V(tgMH_SUB_S)( vX1, vX1 ); Test__Expect_EQ( true, FCN_V(tgMH_CMP_ALL_TO_BOOL_S)( FCN_V(tgMH_CMP_EQ_S)( vX1, vRet ) )); /* Z Z Z */
    vRet = FCN_V(tgMH_SUB_S)( vN4, vN4 ); Test__Expect_EQ( true, FCN_V(tgMH_CMP_ALL_TO_BOOL_S)( FCN_V(tgMH_CMP_EQ_S)( vX1, vRet ) )); /* Z N N */
    vRet = FCN_V(tgMH_SUB_S)( vP4, vP8 ); Test__Expect_EQ( true, FCN_V(tgMH_CMP_ALL_TO_BOOL_S)( FCN_V(tgMH_CMP_EQ_S)( vN4, vRet ) )); /* N P P */
    vRet = FCN_V(tgMH_SUB_S)( vX4, vN8 ); Test__Expect_EQ( true, FCN_V(tgMH_CMP_ALL_TO_BOOL_S)( FCN_V(tgMH_CMP_EQ_S)( vY3, vRet ) )); /* N P N */
    vRet = FCN_V(tgMH_SUB_S)( vX1, vP4 ); Test__Expect_EQ( true, FCN_V(tgMH_CMP_ALL_TO_BOOL_S)( FCN_V(tgMH_CMP_EQ_S)( vN4, vRet ) )); /* N Z P */
    vRet = FCN_V(tgMH_SUB_S)( vN4, vP4 ); Test__Expect_EQ( true, FCN_V(tgMH_CMP_ALL_TO_BOOL_S)( FCN_V(tgMH_CMP_EQ_S)( vN8, vRet ) )); /* N N P */
    vRet = FCN_V(tgMH_SUB_S)( vN4, vX1 ); Test__Expect_EQ( true, FCN_V(tgMH_CMP_ALL_TO_BOOL_S)( FCN_V(tgMH_CMP_EQ_S)( vN4, vRet ) )); /* N N Z */
    vRet = FCN_V(tgMH_SUB_S)( vN8, vN4 ); Test__Expect_EQ( true, FCN_V(tgMH_CMP_ALL_TO_BOOL_S)( FCN_V(tgMH_CMP_EQ_S)( vN4, vRet ) )); /* N N N */

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_AVG_S) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_AVG_S) )
{
    VEC_S_T(1,C)                        vX1 = FCN_V(tgMH_SET1_S)((VAR_T())0);
    VEC_S_T(1,C)                        vP4 = FCN_V(tgMH_SET1_S)((VAR_T())4);
    VEC_S_T(1,C)                        vP6 = FCN_V(tgMH_SET1_S)((VAR_T())6);
    VEC_S_T(1,C)                        vP8 = FCN_V(tgMH_SET1_S)((VAR_T())8);
    VEC_S_T(1,C)                        vX0 = FCN_V(tgMH_SET1_S)(VAR_K(KTgMAX));
    VEC_S_T(1,C)                        vX4 = FCN_V(tgMH_SET1_S)(VAR_K(KTgMAX) - 4);
    VEC_S_T(1,C)                        vY0 = FCN_V(tgMH_SET1_S)(VAR_K(KTgMIN));
    VEC_S_T(1,C)                        vY3 = FCN_V(tgMH_SET1_S)(VAR_K(KTgMIN) + 3);

    VEC_S_T(1)                          vRet;

    vRet = FCN_V(tgMH_AVG_S)( vX1, vX1 ); Test__Expect_EQ(true, FCN_V(tgMH_CMP_ALL_TO_BOOL_S)( FCN_V(tgMH_CMP_EQ_S)( vX1, vRet ) ));
    vRet = FCN_V(tgMH_AVG_S)( vP8, vX1 ); Test__Expect_EQ(true, FCN_V(tgMH_CMP_ALL_TO_BOOL_S)( FCN_V(tgMH_CMP_EQ_S)( vP4, vRet ) ));
    vRet = FCN_V(tgMH_AVG_S)( vP8, vP4 ); Test__Expect_EQ(true, FCN_V(tgMH_CMP_ALL_TO_BOOL_S)( FCN_V(tgMH_CMP_EQ_S)( vP6, vRet ) ));
    vRet = FCN_V(tgMH_AVG_S)( vX0, vX0 ); Test__Expect_EQ(true, FCN_V(tgMH_CMP_ALL_TO_BOOL_S)( FCN_V(tgMH_CMP_EQ_S)( vX0, vRet ) ));
    vRet = FCN_V(tgMH_AVG_S)( vX4, vX4 ); Test__Expect_EQ(true, FCN_V(tgMH_CMP_ALL_TO_BOOL_S)( FCN_V(tgMH_CMP_EQ_S)( vX4, vRet ) ));
    vRet = FCN_V(tgMH_AVG_S)( vY0, vY0 ); Test__Expect_EQ(true, FCN_V(tgMH_CMP_ALL_TO_BOOL_S)( FCN_V(tgMH_CMP_EQ_S)( vY0, vRet ) ));
    vRet = FCN_V(tgMH_AVG_S)( vY3, vY3 ); Test__Expect_EQ(true, FCN_V(tgMH_CMP_ALL_TO_BOOL_S)( FCN_V(tgMH_CMP_EQ_S)( vY3, vRet ) ));

    TEST_END_METHOD( KTgS_OK );
}


/* =============================================================================================================================================================================== */

/*# (!VEC_IS_NATIVE && TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE) || VEC_IS_NATIVE */
#endif

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

#undef FCN_V_UT
#undef FCN_V_UT_1
#undef FCN_V_UT_2
