/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common [Unit Test] [Test] - Math [Matrix] [S] [F].c
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

/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- FCN_M_UT(tgMH_ADD_S) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_ADD_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       sM0, sM1, sMX;

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        sM0.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
        sM1.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
    };

    FCN_M(tgMH_ADD_S)( &sMX, &sM0, &sM1 );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM * TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        Test__Expect_EQ( true, FCN_F(tgCM_NR0)( sMX.m_aElement[uiIndex] - (sM0.m_aElement[uiIndex] + sM1.m_aElement[uiIndex]) ) );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_MUL_S) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_MUL_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       sM0, sM1, sMX;

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        sM0.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
        sM1.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
    };

    FCN_M(tgMH_MUL_S)( &sMX, &sM0, &sM1 );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM * TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        Test__Expect_EQ( true, FCN_F(tgCM_NR0)( sMX.m_aElement[uiIndex] - (sM0.m_aElement[uiIndex] * sM1.m_aElement[uiIndex]) ) );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_MUL_SM_S) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_MUL_SM_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       sM0, sMX;

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        sM0.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
    };

    FCN_M(tgMH_MUL_SM_S)( &sMX, TYPE_K(2), &sM0 );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM * TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        Test__Expect_EQ( true, FCN_F(tgCM_NR0)( sMX.m_aElement[uiIndex] - (TYPE_K(2) * sM0.m_aElement[uiIndex]) ) );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_MUL_MS_S) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_MUL_MS_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       sM0, sMX;

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        sM0.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
    };

    FCN_M(tgMH_MUL_MS_S)( &sMX, &sM0, TYPE_K(3) );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM * TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        Test__Expect_EQ( true, FCN_F(tgCM_NR0)( sMX.m_aElement[uiIndex] - (TYPE_K(3) * sM0.m_aElement[uiIndex]) ) );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_DIV_S) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_DIV_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       sM0, sM1, sMX;

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        sM0.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
        sM1.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
    };

    FCN_M(tgMH_DIV_S)( &sMX, &sM0, &sM1 );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM * TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        Test__Expect_EQ( true, FCN_F(tgCM_NR0)( sMX.m_aElement[uiIndex] - (sM0.m_aElement[uiIndex] / sM1.m_aElement[uiIndex]) ) );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_DIV_SM_S) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_DIV_SM_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       sM0, sMX;

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        sM0.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
    };

    FCN_M(tgMH_DIV_SM_S)( &sMX, TYPE_K(2,0), &sM0 );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM * TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        Test__Expect_EQ( true, FCN_F(tgCM_NR0)( sMX.m_aElement[uiIndex] - (TYPE_K(2) / sM0.m_aElement[uiIndex]) ) );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_DIV_MS_S) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_DIV_MS_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       sM0, sMX;

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        sM0.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
    };

    FCN_M(tgMH_DIV_MS_S)( &sMX, &sM0, TYPE_K(3,0) );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM * TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        Test__Expect_EQ( true, FCN_F(tgCM_NR0)( sMX.m_aElement[uiIndex] - (sM0.m_aElement[uiIndex] / TYPE_K(3)) ) );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_SUB_S) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_SUB_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       sM0, sM1, sMX;

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        sM0.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
        sM1.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
    };

    FCN_M(tgMH_SUB_S)( &sMX, &sM0, &sM1 );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM * TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        Test__Expect_EQ( true, FCN_F(tgCM_NR0)( sMX.m_aElement[uiIndex] - (sM0.m_aElement[uiIndex] - sM1.m_aElement[uiIndex]) ) );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_NEG_S) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_NEG_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       sM0, sMX;

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        sM0.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
    };

    FCN_M(tgMH_NEG_S)( &sMX, &sM0 );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM * TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        Test__Expect_EQ( true, FCN_F(tgCM_NR0)( sMX.m_aElement[uiIndex] + sM0.m_aElement[uiIndex] ) );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_Set_Euler_S) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_Set_Euler_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       sM0;
    VEC_S_T(1)                          v4_0;

    FCN_M(tgMH_CLI_S)( &sM0 );

    v4_0.x = TYPE_K(0,1) * VAR_K(KTgPI);
    v4_0.y = TYPE_K(0,2) * VAR_K(KTgPI);
    v4_0.z = TYPE_K(0,3) * VAR_K(KTgPI);
    v4_0.w = TYPE_K(0);

    FCN_M(tgMH_Set_Euler_S)( &sM0, v4_0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_Set_Euler_ELEM_S) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_Set_Euler_ELEM_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       mM0;

    FCN_M(tgMH_CLI_S)( &mM0 );

    FCN_M(tgMH_Set_Euler_ELEM_S)( &mM0, TYPE_K(0,1) * VAR_K(KTgPI), TYPE_K(0,2) * VAR_K(KTgPI), TYPE_K(0,3) * VAR_K(KTgPI) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_Set_Euler_X_S) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_Set_Euler_X_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       mM0;

    FCN_M(tgMH_CLI_S)( &mM0 );

    FCN_M(tgMH_Set_Euler_X_S)( &mM0, TYPE_K(0,1) * VAR_K(KTgPI) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_Set_Euler_Y_S) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_Set_Euler_Y_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       mM0;

    FCN_M(tgMH_CLI_S)( &mM0 );

    FCN_M(tgMH_Set_Euler_Y_S)( &mM0, TYPE_K(0,2) * VAR_K(KTgPI) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_Set_Euler_Z_S) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_Set_Euler_Z_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       mM0;

    FCN_M(tgMH_CLI_S)( &mM0 );

    FCN_M(tgMH_Set_Euler_Z_S)( &mM0, TYPE_K(0,3) * VAR_K(KTgPI) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_Set_Quat_S) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_Set_Quat_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       mM0;
    VEC_S_T(1)                          v4_0;

    FCN_M(tgMH_CLI_S)( &mM0 );

    v4_0 = FCN_V(tgMH_NORM_S)( FCN_V(tgMH_RAND_S)() );

    FCN_M(tgMH_Set_Quat_S)( &mM0, v4_0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_NAN_S) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_NAN_S) )
{
    VAR_T()                             tInvalid = 0;
    VEC_S_T(TEMPLATE__VECTOR_COL)       mM0, mM1;
    TgSINT_E32                          iIndex;

    tgMM_Set_U08_0xFF( &tInvalid, sizeof( VAR_T() ) );
    FCN_M(tgMH_CLI_S)( &mM1 );
    for (iIndex = 0; iIndex < TEMPLATE__VECTOR_COL * TEMPLATE__VECTOR_DIM; ++iIndex)
    {
        mM0 = mM1;
        Test__Expect_EQ(false, FCN_M(tgMH_NAN_S)( &mM0 ));
        mM0.m_aElement[iIndex] = tInvalid;
        Test__Expect_NE(false, FCN_M(tgMH_NAN_S)( &mM0 ));
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_CLI_S) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_CLI_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       mM0;

    FCN_M(tgMH_CLI_S)( &mM0 );

    for (TgRSIZE uiCol = 0; uiCol < TEMPLATE__VECTOR_COL; ++uiCol)
    {
        for (TgRSIZE uiRow = 0; uiRow < TEMPLATE__VECTOR_DIM; ++uiRow)
        {
            Test__Expect_EQ( uiRow == uiCol ? TYPE_K(1) : TYPE_K(0), mM0.m_aElement[uiCol*TEMPLATE__VECTOR_DIM + uiRow] );
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_Set_ROT_S) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_Set_ROT_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       mM0, mM1;

    FCN_M(tgMH_CLI_S)( &mM1 );

    FCN_M(tgMH_Set_Rot_S)( &mM0, &mM1 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_Set_T_S) --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_Set_T_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       mM0;
    VEC_S_T(1)                          v4_0;

    FCN_M(tgMH_CLI_S)( &mM0 );

    v4_0.x = TYPE_K(0,1) * VAR_K(KTgPI);
    v4_0.y = TYPE_K(0,2) * VAR_K(KTgPI);
    v4_0.z = TYPE_K(0,3) * VAR_K(KTgPI);
    v4_0.w = TYPE_K(0);

    FCN_M(tgMH_Set_T_S)( &mM0, v4_0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_Set_T_ELEM_S) ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_Set_T_ELEM_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       mM0;
    VEC_S_T(1)                          v4_0;

    FCN_M(tgMH_CLI_S)( &mM0 );

    v4_0.x = TYPE_K(0,1) * VAR_K(KTgPI);
    v4_0.y = TYPE_K(0,2) * VAR_K(KTgPI);
    v4_0.z = TYPE_K(0,3) * VAR_K(KTgPI);
    v4_0.w = TYPE_K(0);

    FCN_M(tgMH_Set_T_ELEM_S)( &mM0, v4_0.x, v4_0.y, v4_0.z );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_Init_ROT_S) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_Init_ROT_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       mM0, mMX;

    tgMM_Set_U08_0xFF( &mM0, sizeof(mM0) );
    FCN_M(tgMH_Init_ROT_S)( &mMX, &mM0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_Init_T_S) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_Init_T_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       mM0;
    VEC_S_T(1)                          v4_0;

    v4_0.x = TYPE_K(0,1);
    v4_0.y = TYPE_K(0,2);
    v4_0.z = TYPE_K(0,3);
    v4_0.w = TYPE_K(0);

    FCN_M(tgMH_Init_T_S)( &mM0, v4_0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_Init_T_ELEM_S) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_Init_T_ELEM_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       mM0;

    FCN_M(tgMH_Init_T_ELEM_S)( &mM0, TYPE_K(0,1), TYPE_K(0,2), TYPE_K(0,3) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_Init_Euler_S) ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_Init_Euler_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       mM0;
    VEC_S_T(1)                          v4_0;

    v4_0.x = TYPE_K(0,1) * VAR_K(KTgPI);
    v4_0.y = TYPE_K(0,2) * VAR_K(KTgPI);
    v4_0.z = TYPE_K(0,3) * VAR_K(KTgPI);
    v4_0.w = TYPE_K(0);

    FCN_M(tgMH_Init_Euler_S)( &mM0, v4_0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_Init_Euler_ELEM_S) ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_Init_Euler_ELEM_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       mM0;

    FCN_M(tgMH_Init_Euler_ELEM_S)( &mM0, TYPE_K(0,1) * VAR_K(KTgPI), TYPE_K(0,2) * VAR_K(KTgPI), TYPE_K(0,3) * VAR_K(KTgPI) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_Init_Euler_X_S) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_Init_Euler_X_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       mM0;

    FCN_M(tgMH_Init_Euler_X_S)( &mM0, TYPE_K(0,1) * VAR_K(KTgPI) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_Init_Euler_Y_S) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_Init_Euler_Y_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       mM0;

    FCN_M(tgMH_Init_Euler_Y_S)( &mM0, TYPE_K(0,2) * VAR_K(KTgPI ) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_Init_Euler_Z_S) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_Init_Euler_Z_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       mM0;

    FCN_M(tgMH_Init_Euler_Z_S)( &mM0, TYPE_K(0,3) * VAR_K(KTgPI) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_Init_Quat_S) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_Init_Quat_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       mM0;
    VEC_S_T(1)                          vQ0;

    vQ0 = FCN_V(tgMH_QT_Init_Euler_S)( FCN_V(tgMH_RAND_S)() );

    FCN_M(tgMH_Init_Quat_S)( &mM0, vQ0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_CAT_S) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_CAT_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       mM0, mM1, mMX;

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        mM0.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
        mM1.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
    };

    FCN_M(tgMH_CAT_S)( &mMX, &mM0, &mM1 );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL*TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        VAR_T()                             tTotal;

        tTotal = TYPE_K(0);

        for (TgRSIZE uiCheck = 0; uiCheck < tgCM_MIN_UMAX( TEMPLATE__VECTOR_COL, TEMPLATE__VECTOR_DIM ); ++uiCheck)
        {
            tTotal += mM0.m_aColRow[uiCheck][uiIndex % TEMPLATE__VECTOR_DIM] * mM1.m_aColRow[uiIndex / TEMPLATE__VECTOR_DIM][uiCheck];
        };

        if ((TEMPLATE__VECTOR_COL < TEMPLATE__VECTOR_DIM) && (TEMPLATE__VECTOR_COL == (uiIndex % TEMPLATE__VECTOR_DIM)))
        {
            tTotal += mM1.m_aColRow[uiIndex / TEMPLATE__VECTOR_DIM][uiIndex % TEMPLATE__VECTOR_DIM];
        };

        Test__Expect_EQ(true, FCN_F(tgCM_NR0)( tTotal - mMX.m_aColRow[uiIndex / TEMPLATE__VECTOR_DIM][uiIndex % TEMPLATE__VECTOR_DIM] ));
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_INV_DET_S) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_INV_DET_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_DIM)       mM2;
    VEC_S_T(TEMPLATE__VECTOR_COL)       mM0;
    VAR_T()                             tDet;

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        mM0.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
    };

    tDet = FCN_M(tgMH_DET_S)( &mM0 );
    FCN_M(tgMH_INV_DET_S)( &mM2, tDet, &mM0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_INV_S) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_INV_S) )
{
    union
    {
        VEC_S_T(TEMPLATE__VECTOR_DIM)       mDIM_S;
        VEC_S_T(TEMPLATE__VECTOR_COL)       mCOL_S;
    }                                   uM0, uMX, uMZ;

    FCN_V(tgMH_CLI_S,TEMPLATE__VECTOR_DIM)( &uM0.mDIM_S );
    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        uM0.mCOL_S.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
    };

    FCN_M(tgMH_INV_S)( &uMX.mDIM_S, &uM0.mCOL_S );
    FCN_V(tgMH_CAT_S,TEMPLATE__VECTOR_DIM)( &uMZ.mDIM_S, &uM0.mDIM_S, &uMX.mDIM_S );

    for (TgRSIZE uiCol = 0; uiCol < TEMPLATE__VECTOR_COL; ++uiCol)
    {
        for (TgRSIZE uiRow = 0; uiRow < TEMPLATE__VECTOR_DIM; ++uiRow)
        {
            VAR_T(C) fVal = uMZ.mDIM_S.m_aElement[uiCol*TEMPLATE__VECTOR_DIM + uiRow];
            Test__Expect_EQ( true, FCN_F(tgCM_NR0)( (uiRow == uiCol ? TYPE_K(1) : TYPE_K(0)) - fVal ) );
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_DET_S) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_DET_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       mM0;
    VAR_T()                             tDet;

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        mM0.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
    };

    tDet = FCN_M(tgMH_DET_S)( &mM0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_TX_S) ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_TX_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       mM0;
    VEC_S_T(1)                          vV0_V4, vV1_V4;

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        mM0.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
    };

    while (TYPE_K(0) == (vV0_V4.x = FCN_F(tgCM_RAND)()));
    while (TYPE_K(0) == (vV0_V4.y = FCN_F(tgCM_RAND)()));
    while (TYPE_K(0) == (vV0_V4.z = FCN_F(tgCM_RAND)()));
    vV0_V4.w = TYPE_K(0);

    vV1_V4 = FCN_M(tgMH_TX_S)( vV0_V4, &mM0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_TX_P_S) ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_TX_P_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       mM0;
    VEC_S_T(1)                          vV0_V4, vV1_V4;

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        mM0.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
    };

    while (TYPE_K(0) == (vV0_V4.x = FCN_F(tgCM_RAND)()));
    while (TYPE_K(0) == (vV0_V4.y = FCN_F(tgCM_RAND)()));
    while (TYPE_K(0) == (vV0_V4.z = FCN_F(tgCM_RAND)()));
    vV0_V4.w = TYPE_K(0);

    vV1_V4 = FCN_M(tgMH_TX_P_S)( vV0_V4, &mM0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_TX_V_S) ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_TX_V_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       mM0;
    VEC_S_T(1)                          vV0_V4, vV1_V4;

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        mM0.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
    };

    while (TYPE_K(0) == (vV0_V4.x = FCN_F(tgCM_RAND)()));
    while (TYPE_K(0) == (vV0_V4.y = FCN_F(tgCM_RAND)()));
    while (TYPE_K(0) == (vV0_V4.z = FCN_F(tgCM_RAND)()));
    vV0_V4.w = TYPE_K(0);

    vV1_V4 = FCN_M(tgMH_TX_V_S)( vV0_V4, &mM0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_Query_Row_0_S) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_Query_Row_0_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       mM0;
    VEC_S_T(1)                          vV0_V4;
    TgRSIZE                             uiIndex;

    for (uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        mM0.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
    };

    vV0_V4 = FCN_M(tgMH_Query_Row_0_S)( &mM0 );

    for (uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        Test__Expect_EQ( true, FCN_F(tgCM_NR0)( vV0_V4.m_aData[uiIndex] - mM0.m_aColRow[uiIndex][0] ) );
    };

    for (; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_EQ( true, FCN_F(tgCM_NR0)( vV0_V4.m_aData[uiIndex] ) );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_Query_Row_1_S) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_Query_Row_1_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       mM0;
    VEC_S_T(1)                          vV0_V4;
    TgRSIZE                             uiIndex;

    for (uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        mM0.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
    };

    vV0_V4 = FCN_M(tgMH_Query_Row_1_S)( &mM0 );

    for (uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        Test__Expect_EQ( true, FCN_F(tgCM_NR0)( vV0_V4.m_aData[uiIndex] - mM0.m_aColRow[uiIndex][1] ) );
    };

    for (; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_EQ( true, FCN_F(tgCM_NR0)( vV0_V4.m_aData[uiIndex] ) );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_Query_Row_2_S) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_Query_Row_2_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       mM0;
    VEC_S_T(1)                          vV0_V4;
    TgRSIZE                             uiIndex;

    for (uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        mM0.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
    };

    vV0_V4 = FCN_M(tgMH_Query_Row_2_S)( &mM0 );

    for (uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        Test__Expect_EQ( true, FCN_F(tgCM_NR0)( vV0_V4.m_aData[uiIndex] - mM0.m_aColRow[uiIndex][2] ) );
    };

    for (; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_EQ( true, FCN_F(tgCM_NR0)( vV0_V4.m_aData[uiIndex] ) );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_Query_Row_3_S) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_Query_Row_3_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       mM0;
    VEC_S_T(1)                          vV0_V4;
    TgRSIZE                             uiIndex;

    for (uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        mM0.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
    };

    vV0_V4 = FCN_M(tgMH_Query_Row_3_S)( &mM0 );

    for (uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        Test__Expect_EQ( true, FCN_F(tgCM_NR0)( vV0_V4.m_aData[uiIndex] - mM0.m_aColRow[uiIndex][3] ) );
    };

    for (; uiIndex + 1 < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_EQ( true, FCN_F(tgCM_NR0)( vV0_V4.m_aData[uiIndex] ) );
    };

    if (TEMPLATE__VECTOR_DIM > TEMPLATE__VECTOR_COL)
    {
        Test__Expect_EQ( true, FCN_F(tgCM_NR1)( vV0_V4.m_aData[3] ) );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_Query_Col_0_S) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_Query_Col_0_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       mM0;
    VEC_S_T(1)                          vV0_V4;

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        mM0.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
    };

    vV0_V4 = FCN_M(tgMH_Query_Col_0_S)( &mM0 );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_EQ( true, FCN_F(tgCM_NR0)( vV0_V4.m_aData[uiIndex] - mM0.m_aColRow[0][uiIndex] ) );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_Query_Col_1_S) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_Query_Col_1_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       mM0;
    VEC_S_T(1)                          vV0_V4;

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        mM0.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
    };

    vV0_V4 = FCN_M(tgMH_Query_Col_1_S)( &mM0 );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_EQ( true, FCN_F(tgCM_NR0)(vV0_V4.m_aData[uiIndex] - mM0.m_aColRow[1][uiIndex]) );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_Query_Col_2_S) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_Query_Col_2_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       mM0;
    VEC_S_T(1)                          vV0_V4;

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        mM0.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
    };

    vV0_V4 = FCN_M(tgMH_Query_Col_2_S)( &mM0 );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_EQ( true, FCN_F(tgCM_NR0)(vV0_V4.m_aData[uiIndex] - mM0.m_aColRow[2][uiIndex]) );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_Query_Col_3_S) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_Query_Col_3_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       mM0;
    VEC_S_T(1)                          vV0_V4;

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        mM0.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
    };

    vV0_V4 = FCN_M(tgMH_Query_Col_3_S)( &mM0 );

#if (TEMPLATE__VECTOR_COL > 3)
    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_EQ( true, FCN_F(tgCM_NR0)(vV0_V4.m_aData[uiIndex] - mM0.m_aColRow[3][uiIndex]) );
    };
#else
    Test__Expect_EQ(true, FCN_F(tgCM_NR0)( vV0_V4.m_aData[0] ));
    Test__Expect_EQ(true, FCN_F(tgCM_NR0)( vV0_V4.m_aData[1] ));
    Test__Expect_EQ(true, FCN_F(tgCM_NR0)( vV0_V4.m_aData[2] ));
    Test__Expect_EQ(true, FCN_F(tgCM_NR1)( vV0_V4.m_aData[3] ));
#endif

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_Query_Axis_0_S) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_Query_Axis_0_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       mM0;
    VEC_S_T(1)                          vV0_V4;
    TgRSIZE                             uiIndex;

    for (uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        mM0.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
    };

    vV0_V4 = FCN_M(tgMH_Query_Axis_0_S)( &mM0 );

    for (uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        Test__Expect_EQ( true, FCN_F(tgCM_NR0)( vV0_V4.m_aData[uiIndex] - mM0.m_aColRow[uiIndex][0] ) );
    };

    for (; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_EQ( true, FCN_F(tgCM_NR0)( vV0_V4.m_aData[uiIndex] ) );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_Query_Axis_1_S) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_Query_Axis_1_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       mM0;
    VEC_S_T(1)                          vV0_V4;
    TgRSIZE                             uiIndex;

    for (uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        mM0.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
    };

    vV0_V4 = FCN_M(tgMH_Query_Axis_1_S)( &mM0 );

    for (uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        Test__Expect_EQ( true, FCN_F(tgCM_NR0)( vV0_V4.m_aData[uiIndex] - mM0.m_aColRow[uiIndex][1] ) );
    };

    for (; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_EQ( true, FCN_F(tgCM_NR0)( vV0_V4.m_aData[uiIndex] ) );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_Query_Axis_2_S) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_Query_Axis_2_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       mM0;
    VEC_S_T(1)                          vV0_V4;
    TgRSIZE                             uiIndex;

    for (uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        mM0.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
    };

    vV0_V4 = FCN_M(tgMH_Query_Axis_2_S)( &mM0 );

    for (uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        Test__Expect_EQ( true, FCN_F(tgCM_NR0)( vV0_V4.m_aData[uiIndex] - mM0.m_aColRow[uiIndex][2] ) );
    };

    for (; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_EQ( true, FCN_F(tgCM_NR0)( vV0_V4.m_aData[uiIndex] ) );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_Query_Axis_3_S) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_Query_Axis_3_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       mM0;
    VEC_S_T(1)                          vV0_V4;
    TgRSIZE                             uiIndex;

    for (uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        mM0.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
    };

    vV0_V4 = FCN_M(tgMH_Query_Axis_3_S)( &mM0 );

    for (uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        Test__Expect_EQ( true, FCN_F(tgCM_NR0)( vV0_V4.m_aData[uiIndex] - mM0.m_aColRow[uiIndex][3] ) );
    };

    for (; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_EQ( true, FCN_F(tgCM_NR1)( vV0_V4.m_aData[uiIndex] ) );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_Matrix_To_Euler_S_S) --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_Matrix_To_Euler_S_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       mM1;
    VEC_S_T(1)                          vV0_V4;

    tgMM_Set_U08_0xFF( &mM1, sizeof(mM1) );
    FCN_M(tgMH_Matrix_To_Euler_ELEM_S)( &vV0_V4.x, &vV0_V4.y, &vV0_V4.z, &mM1 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_Matrix_To_Euler_S) ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_Matrix_To_Euler_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       mM1;
    VEC_S_T(1)                          vV0_V4;

    tgMM_Set_U08_0xFF( &mM1, sizeof(mM1) );
    FCN_M(tgMH_Matrix_To_Euler_S)( &vV0_V4, &mM1 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_Matrix_To_Quat_S) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_Matrix_To_Quat_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       mM1;
    VEC_S_T(1)                          vV0_V4;

    tgMM_Set_U08_0xFF( &mM1, sizeof(mM1) );
    FCN_M(tgMH_Matrix_To_Quat_S)( &vV0_V4, &mM1 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_Init_Reference_Frame_From_Vector_And_Position_S) ----------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_Init_Reference_Frame_From_Vector_And_Position_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       mM0;
    VEC_S_T(1)                          v4_0;

    v4_0.x = TYPE_K(0,1) * VAR_K(KTgPI);
    v4_0.y = TYPE_K(0,2) * VAR_K(KTgPI);
    v4_0.z = TYPE_K(0,3) * VAR_K(KTgPI);
    v4_0.w = TYPE_K(0);

    v4_0 = FCN_V(tgMH_NORM_S)( v4_0 );
    FCN_M(tgMH_Init_Reference_Frame_From_Vector_And_Position_S)( &mM0, v4_0, v4_0 );

    TEST_END_METHOD( KTgS_OK );
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

#undef FCN_M_UT
#undef FCN_UT_1
#undef FCN_UT_2
