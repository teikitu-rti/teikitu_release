/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common [Unit Test] [Test] - Math [Vector] [FXX_04].c_inc
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

TEST_LOCAL VAR_T() FCN_V(tgMH_ERR_S)( VEC_S_T(1,C) v0 ) { return (FCN_F(tgCM_MAX)( TYPE_K(10,0)*FCN_V(tgMH_LEN_S)( v0 ), TYPE_K(1,0) )); }

#define FCN_V_UT(...)                       MULTI_MACRO(FCN_V_UT, __VA_ARGS__)
#define FCN_V_UT_1(F)                       TgMACRO_CONCAT5( UNIT_TEST__TEST__##F, _, GENERATE__VEC_DESC, _, 1 )
#define FCN_V_UT_2(F, COL)                  TgMACRO_CONCAT5( UNIT_TEST__TEST__##F, _, GENERATE__VEC_DESC, _, COL )

/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- FCN_V_UT(tgMH_Init_ELEM_S) --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_Init_ELEM_S) )
{
    VEC_S_T(1)                          v0;

    v0 = FCN_V(tgMH_Init_ELEM_S)( TYPE_K(7,0), TYPE_K(2,0), TYPE_K(3,0), TYPE_K(4,0) );

    Test__Expect_EQ(v0.x, TYPE_K(7,0) );
    Test__Expect_EQ(v0.y, TYPE_K(2,0) );
    Test__Expect_EQ(v0.z, TYPE_K(3,0) );
    Test__Expect_EQ(v0.w, TYPE_K(4,0) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_Init_Point_ELEM_S) -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_Init_Point_ELEM_S) )
{
    VEC_S_T(1)                          v4_0;

    v4_0 = FCN_V(tgMH_Init_Point_ELEM_S)(TYPE_K(7,0), TYPE_K(2,0), TYPE_K(3,0));
    Test__Expect_NE(false, FCN_V(tgMH_Is_Valid_Point_S)(v4_0));

    Test__Expect_EQ(v4_0.x, TYPE_K(7,0) );
    Test__Expect_EQ(v4_0.y, TYPE_K(2,0) );
    Test__Expect_EQ(v4_0.z, TYPE_K(3,0) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_Init_Vector_ELEM_S) -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_Init_Vector_ELEM_S) )
{
    VEC_S_T(1)                          v4_0;
    
    v4_0 = FCN_V(tgMH_Init_Vector_ELEM_S)(TYPE_K(7,0), TYPE_K(2,0), TYPE_K(3,0));
    Test__Expect_NE(false, FCN_V(tgMH_Is_Valid_Vector_S)(v4_0));

    Test__Expect_EQ(v4_0.x, TYPE_K(7,0) );
    Test__Expect_EQ(v4_0.y, TYPE_K(2,0) );
    Test__Expect_EQ(v4_0.z, TYPE_K(3,0) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_Init_Point_S) ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_Init_Point_S) )
{
    VEC_S_T(1)                          v4_0, v4_1;

    v4_0 = FCN_V(tgMH_Init_Point_ELEM_S)(TYPE_K(7,0), TYPE_K(2,0), TYPE_K(3,0));
    v4_1 = FCN_V(tgMH_Init_Point_S)(v4_0);
    Test__Expect_NE(false, FCN_V(tgMH_Is_Valid_Point_S)(v4_1));

    Test__Expect_EQ(v4_1.x, TYPE_K(7,0) );
    Test__Expect_EQ(v4_1.y, TYPE_K(2,0) );
    Test__Expect_EQ(v4_1.z, TYPE_K(3,0) );

    v4_0 = FCN_V(tgMH_Init_Vector_ELEM_S)(TYPE_K(7,0), TYPE_K(2,0), TYPE_K(3,0));
    v4_1 = FCN_V(tgMH_Init_Point_S)(v4_0);
    Test__Expect_NE(false, FCN_V(tgMH_Is_Valid_Point_S)(v4_1));

    Test__Expect_EQ(v4_1.x, TYPE_K(7,0) );
    Test__Expect_EQ(v4_1.y, TYPE_K(2,0) );
    Test__Expect_EQ(v4_1.z, TYPE_K(3,0) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_Init_Vector_S) ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_Init_Vector_S) )
{
    VEC_S_T(1)                          v4_0, v4_1;

    v4_0 = FCN_V(tgMH_Init_Point_ELEM_S)(TYPE_K(7,0), TYPE_K(2,0), TYPE_K(3,0));
    v4_1 = FCN_V(tgMH_Init_Vector_S)(v4_0);
    Test__Expect_NE(false, FCN_V(tgMH_Is_Valid_Vector_S)(v4_1));

    Test__Expect_EQ(v4_1.x, TYPE_K(7,0) );
    Test__Expect_EQ(v4_1.y, TYPE_K(2,0) );
    Test__Expect_EQ(v4_1.z, TYPE_K(3,0) );

    v4_0 = FCN_V(tgMH_Init_Vector_ELEM_S)(TYPE_K(7,0), TYPE_K(2,0), TYPE_K(3,0));
    v4_1 = FCN_V(tgMH_Init_Vector_S)(v4_0);
    Test__Expect_NE(false, FCN_V(tgMH_Is_Valid_Vector_S)(v4_1));

    Test__Expect_EQ(v4_1.x, TYPE_K(7,0) );
    Test__Expect_EQ(v4_1.y, TYPE_K(2,0) );
    Test__Expect_EQ(v4_1.z, TYPE_K(3,0) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_RAND_S) ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_RAND_S) )
{
    FCN_V(tgMH_RAND_S)();

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_Init_Ortho_S) ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_Init_Ortho_S) )
{
    VEC_S_T(1)                          v4_0;

    v4_0 = FCN_V(tgMH_Init_Ortho_S)((VEC_K(KTgUNIT_X_S)));
    Test__Expect_NE(false, FCN_F(tgCM_NR0)(FCN_V(tgMH_DOT_S)((VEC_K(KTgUNIT_X_S)), v4_0)));
    Test__Expect_NE(false, FCN_F(tgCM_NR1)(FCN_V(tgMH_LEN_S)(v4_0)));
    
    v4_0 = FCN_V(tgMH_Init_Ortho_S)((VEC_K(KTgUNIT_Y_S)));
    Test__Expect_NE(false, FCN_F(tgCM_NR0)(FCN_V(tgMH_DOT_S)((VEC_K(KTgUNIT_Y_S)), v4_0)));
    Test__Expect_NE(false, FCN_F(tgCM_NR1)(FCN_V(tgMH_LEN_S)(v4_0)));
    
    v4_0 = FCN_V(tgMH_Init_Ortho_S)((VEC_K(KTgUNIT_Z_S)));
    Test__Expect_NE(false, FCN_F(tgCM_NR0)(FCN_V(tgMH_DOT_S)((VEC_K(KTgUNIT_Z_S)), v4_0)));
    Test__Expect_NE(false, FCN_F(tgCM_NR1)(FCN_V(tgMH_LEN_S)(v4_0)));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_Init_Basis_From_Vector_S) ---------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_Init_Basis_From_Vector_S) )
{
    VEC_S_T(1)                          v4_0, v4_1, v4_2;
    VAR_T()                             fLimit;

    v4_2 = FCN_V(tgMH_NORM_S)( FCN_V(tgMH_Init_Vector_S)( FCN_V(tgMH_RAND_S)() ) );

    FCN_V(tgMH_Init_Basis_From_Vector_S)( &v4_0, &v4_1, v4_2 );
    fLimit = VAR_K(KTgEPS) * FCN_V(tgMH_ERR_S)(v4_0) * FCN_V(tgMH_ERR_S)(v4_1) * FCN_V(tgMH_ERR_S)(v4_2);
    Test__Expect_NE(false, FCN_F(tgPM_ABS)(FCN_V(tgMH_DOT_S)(v4_0, v4_2)) <= fLimit);
    Test__Expect_NE(false, FCN_F(tgPM_ABS)(FCN_V(tgMH_DOT_S)(v4_1, v4_2)) <= fLimit);

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_Is_Valid_Point_S) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_Is_Valid_Point_S) )
{
    VAR_T()                            tInvalid = 0;
    VEC_S_T(1)                         v4_0;

    tgMM_Set_U08_0xFF( &tInvalid, sizeof( VAR_T() ) );

    v4_0 = FCN_V(tgMH_Init_ELEM_S)(TYPE_K(0), tInvalid, TYPE_K(0), TYPE_K(0));
    Test__Expect_EQ(0, FCN_V(tgMH_Is_Valid_Point_S)(v4_0));
    
    v4_0 = FCN_V(tgMH_Init_ELEM_S)(TYPE_K(0), tInvalid, TYPE_K(0), TYPE_K(1));
    Test__Expect_EQ(0, FCN_V(tgMH_Is_Valid_Point_S)(v4_0));
    
    v4_0 = FCN_V(tgMH_Init_ELEM_S)(TYPE_K(7,0), TYPE_K(2,0), TYPE_K(3,0), TYPE_K(0));
    Test__Expect_EQ(0, FCN_V(tgMH_Is_Valid_Point_S)(v4_0));
    
    v4_0 = FCN_V(tgMH_Init_ELEM_S)(TYPE_K(7,0), TYPE_K(2,0), TYPE_K(3,0), TYPE_K(1));
    Test__Expect_NE(false, FCN_V(tgMH_Is_Valid_Point_S)(v4_0));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_Is_Valid_Vector_S) ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_Is_Valid_Vector_S) )
{
    VAR_T()                            tInvalid = 0;
    VEC_S_T(1)                         v4_0;

    tgMM_Set_U08_0xFF( &tInvalid, sizeof( VAR_T() ) );

    v4_0 = FCN_V(tgMH_Init_ELEM_S)(TYPE_K(0), tInvalid, TYPE_K(0), TYPE_K(0));
    Test__Expect_EQ(0, FCN_V(tgMH_Is_Valid_Vector_S)(v4_0));
    
    v4_0 = FCN_V(tgMH_Init_ELEM_S)(TYPE_K(0), tInvalid, TYPE_K(0), TYPE_K(1));
    Test__Expect_EQ(0, FCN_V(tgMH_Is_Valid_Vector_S)(v4_0));
    
    v4_0 = FCN_V(tgMH_Init_ELEM_S)(TYPE_K(7,0), TYPE_K(2,0), TYPE_K(3,0), TYPE_K(0));
    Test__Expect_NE(false, FCN_V(tgMH_Is_Valid_Vector_S)(v4_0));
    
    v4_0 = FCN_V(tgMH_Init_ELEM_S)(TYPE_K(7,0), TYPE_K(2,0), TYPE_K(3,0), TYPE_K(1));
    Test__Expect_EQ(0, FCN_V(tgMH_Is_Valid_Vector_S)(v4_0));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_DOT3_S) ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_DOT3_S) )
{
    VEC_S_T(1)                          v4_0, v4_1, v4_2;
    VAR_T()                             fTest;

    tgMM_Set_U08_0xFF( &v4_0, sizeof( VEC_S_T(1) ) );
    tgMM_Set_U08_0xFF( &v4_1, sizeof( VEC_S_T(1) ) );
    tgMM_Set_U08_0xFF( &v4_2, sizeof( VEC_S_T(1) ) );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        while (TYPE_K(0) == (v4_0.m_aData[uiIndex] = FCN_F(tgCM_RAND)()));
        while (TYPE_K(0) == (v4_1.m_aData[uiIndex] = FCN_F(tgCM_RAND)()));
    };

    v4_0.m_aData[3] = TYPE_K(0);
    v4_1.m_aData[3] = TYPE_K(0);

    fTest = v4_0.m_aData[0] * v4_1.m_aData[0];
    fTest += v4_0.m_aData[1] * v4_1.m_aData[1];
    fTest += v4_0.m_aData[2] * v4_1.m_aData[2];
    Test__Expect_NE(false, FCN_F(tgCM_NR0)(fTest - FCN_V(tgMH_DOT3_S)(v4_0, v4_1)));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_CX_S) -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_CX_S) )
{
    VEC_S_T(1)                          v4_0, v4_1, v4_2;
    VAR_T()                             fLimit;

    tgMM_Set_U08_0xFF( &v4_0, sizeof( VEC_S_T(1) ) );
    tgMM_Set_U08_0xFF( &v4_1, sizeof( VEC_S_T(1) ) );
    tgMM_Set_U08_0xFF( &v4_2, sizeof( VEC_S_T(1) ) );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        while (TYPE_K(0) == (v4_0.m_aData[uiIndex] = FCN_F(tgCM_RAND)()));
        while (TYPE_K(0) == (v4_1.m_aData[uiIndex] = FCN_F(tgCM_RAND)()));
    };

    v4_2 = FCN_V(tgMH_CX_S)((VEC_K(KTgUNIT_X_S)), (VEC_K(KTgUNIT_Y_S)));
    Test__Expect_NE(false, FCN_F(tgCM_NR0)(v4_2.m_aData[0] - VEC_K(KTgUNIT_Z_S).m_aData[0]));
    Test__Expect_NE(false, FCN_F(tgCM_NR0)(v4_2.m_aData[1] - VEC_K(KTgUNIT_Z_S).m_aData[1]));
    Test__Expect_NE(false, FCN_F(tgCM_NR0)(v4_2.m_aData[2] - VEC_K(KTgUNIT_Z_S).m_aData[2]));
    
    v4_2 = FCN_V(tgMH_CX_S)(v4_0, v4_1);
    fLimit = VAR_K(KTgEPS) * FCN_V(tgMH_ERR_S)(v4_0) * FCN_V(tgMH_ERR_S)(v4_1) * FCN_V(tgMH_ERR_S)(v4_2);
    Test__Expect_NE(false, FCN_F(tgPM_ABS)(FCN_V(tgMH_DOT_S)(v4_0, v4_2)) <= fLimit);
    Test__Expect_NE(false, FCN_F(tgPM_ABS)(FCN_V(tgMH_DOT_S)(v4_1, v4_2)) <= fLimit);

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_UCX_S) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_UCX_S) )
{
    VEC_S_T(1)                          v4_0, v4_1, v4_2;
    VAR_T()                             fLimit;

    tgMM_Set_U08_0xFF( &v4_0, sizeof( VEC_S_T(1) ) );
    tgMM_Set_U08_0xFF( &v4_1, sizeof( VEC_S_T(1) ) );
    tgMM_Set_U08_0xFF( &v4_2, sizeof( VEC_S_T(1) ) );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        while (TYPE_K(0) == (v4_0.m_aData[uiIndex] = FCN_F(tgCM_RAND)()));
        while (TYPE_K(0) == (v4_1.m_aData[uiIndex] = FCN_F(tgCM_RAND)()));
    };

    v4_2 = FCN_V(tgMH_UCX_S)((VEC_K(KTgUNIT_X_S)), (VEC_K(KTgUNIT_Y_S)));
    Test__Expect_NE(false, FCN_F(tgCM_NR0)(v4_2.m_aData[0] - VEC_K(KTgUNIT_Z_S).m_aData[0]));
    Test__Expect_NE(false, FCN_F(tgCM_NR0)(v4_2.m_aData[1] - VEC_K(KTgUNIT_Z_S).m_aData[1]));
    Test__Expect_NE(false, FCN_F(tgCM_NR0)(v4_2.m_aData[2] - VEC_K(KTgUNIT_Z_S).m_aData[2]));
    
    v4_2 = FCN_V(tgMH_UCX_S)(v4_0, v4_1);
    fLimit = VAR_K(KTgEPS) * FCN_V(tgMH_ERR_S)(v4_0) * FCN_V(tgMH_ERR_S)(v4_1);
    Test__Expect_NE(false, FCN_F(tgPM_ABS)(FCN_V(tgMH_DOT_S)(v4_0, v4_2)) <= fLimit);
    Test__Expect_NE(false, FCN_F(tgPM_ABS)(FCN_V(tgMH_DOT_S)(v4_1, v4_2)) <= fLimit);
    Test__Expect_NE(false, FCN_F(tgPM_ABS)(FCN_V(tgMH_LEN_S)(v4_2) - TYPE_K(1)) <= fLimit);

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_UCX_LEN_S) --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_UCX_LEN_S) )
{
    VEC_S_T(1)                          v4_0, v4_1, v4_2;
    VAR_T()                             fLimit, fLength, fTest;

    tgMM_Set_U08_0xFF( &v4_0, sizeof( VEC_S_T(1) ) );
    tgMM_Set_U08_0xFF( &v4_1, sizeof( VEC_S_T(1) ) );
    tgMM_Set_U08_0xFF( &v4_2, sizeof( VEC_S_T(1) ) );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        while (TYPE_K(0) == (v4_0.m_aData[uiIndex] = FCN_F(tgCM_RAND)()));
        while (TYPE_K(0) == (v4_1.m_aData[uiIndex] = FCN_F(tgCM_RAND)()));
    };

    v4_2 = FCN_V(tgMH_UCX_LEN_S)( &fTest, (VEC_K(KTgUNIT_X_S)), (VEC_K(KTgUNIT_Y_S)));
    Test__Expect_NE(false, FCN_F(tgCM_NR0)(v4_2.m_aData[0] - VEC_K(KTgUNIT_Z_S).m_aData[0]));
    Test__Expect_NE(false, FCN_F(tgCM_NR0)(v4_2.m_aData[1] - VEC_K(KTgUNIT_Z_S).m_aData[1]));
    Test__Expect_NE(false, FCN_F(tgCM_NR0)(v4_2.m_aData[2] - VEC_K(KTgUNIT_Z_S).m_aData[2]));
    
    v4_2 = FCN_V(tgMH_CX_S)(v4_0, v4_1);
    fLength = FCN_V(tgMH_LEN_S)(v4_2);
    v4_2 = FCN_V(tgMH_UCX_LEN_S)( &fTest, v4_0, v4_1);
    fLimit = VAR_K(KTgEPS) * FCN_V(tgMH_ERR_S)(v4_0) * FCN_V(tgMH_ERR_S)(v4_1);
    Test__Expect_NE(false, FCN_F(tgPM_ABS)(FCN_V(tgMH_DOT_S)(v4_0, v4_2)) <= fLimit);
    Test__Expect_NE(false, FCN_F(tgPM_ABS)(FCN_V(tgMH_DOT_S)(v4_1, v4_2)) <= fLimit);
    Test__Expect_NE(false, FCN_F(tgPM_ABS)(FCN_V(tgMH_LEN_S)(v4_2) - TYPE_K(1)) <= fLimit);
    Test__Expect_NE(false, FCN_F(tgPM_ABS)(fLength - fTest) <= fLimit);

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_NORM3_LEN_S) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_NORM3_LEN_S) )
{
    VEC_S_T(1)                          v4_2;
    VAR_T()                             fLength;

    tgMM_Set_U08_0xFF( &v4_2, sizeof( VEC_S_T(1) ) );

    for (TgRSIZE uiIndex = 0; uiIndex < 4; ++uiIndex)
    {
        while (TYPE_K(0) == (v4_2.m_aData[uiIndex] = FCN_F(tgCM_RAND)()));
    };

    v4_2 = FCN_V(tgMH_NORM3_LEN_S)( &fLength, v4_2);

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_NORM3_S) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_NORM3_S) )
{
    VEC_S_T(1)                          v4_2;

    tgMM_Set_U08_0xFF( &v4_2, sizeof( VEC_S_T(1) ) );

    for (TgRSIZE uiIndex = 0; uiIndex < 4; ++uiIndex)
    {
        while (TYPE_K(0) == (v4_2.m_aData[uiIndex] = FCN_F(tgCM_RAND)()));
    };

    v4_2 = FCN_V(tgMH_NORM3_S)(v4_2);

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_PRX3_CMP_EQ_S) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_PRX3_CMP_EQ_S) )
{
    VEC_S_T(1)                          v4_0, v4_1, v4_2;

    tgMM_Set_U08_0xFF( &v4_0, sizeof( VEC_S_T(1) ) );
    tgMM_Set_U08_0xFF( &v4_1, sizeof( VEC_S_T(1) ) );
    tgMM_Set_U08_0xFF( &v4_2, sizeof( VEC_S_T(1) ) );

    for (TgRSIZE uiIndex = 0; uiIndex < 4; ++uiIndex)
    {
        while (TYPE_K(0) == (v4_0.m_aData[uiIndex] = FCN_F(tgCM_RAND)()));
    };

    v4_1 = v4_0;
    Test__Expect_NE(false, FCN_V(tgMH_PRX3_CMP_EQ_S)( v4_0, v4_1 ));
    v4_1.w = -v4_1.w;
    Test__Expect_NE(false, FCN_V(tgMH_PRX3_CMP_EQ_S)( v4_0, v4_1 ));
    v4_1.w = v4_0.w;
    v4_1.y += VAR_K(KTgROOT_EPS) + VAR_K(KTgROOT_EPS);
    Test__Expect_EQ(false, FCN_V(tgMH_PRX3_CMP_EQ_S)( v4_0, v4_1 ));


    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_Is_PRX_CMP_EQ_S) ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_Is_PRX_CMP_EQ_S) )
{
    VEC_S_T(1)                          v4_0, v4_1, v4_2;

    tgMM_Set_U08_0xFF( &v4_0, sizeof( VEC_S_T(1) ) );
    tgMM_Set_U08_0xFF( &v4_1, sizeof( VEC_S_T(1) ) );
    tgMM_Set_U08_0xFF( &v4_2, sizeof( VEC_S_T(1) ) );

    for (TgRSIZE uiIndex = 0; uiIndex < 4; ++uiIndex)
    {
        while (TYPE_K(0) == (v4_0.m_aData[uiIndex] = FCN_F(tgCM_RAND)()));
    };

    v4_1 = v4_0;
    Test__Expect_NE(false, FCN_V(tgMH_Is_PRX_CMP_EQ_S)( v4_0, v4_1 ));
    v4_1.w = -v4_1.w;
    Test__Expect_EQ(false, FCN_V(tgMH_Is_PRX_CMP_EQ_S)( v4_0, v4_1 ));
    v4_1.w = v4_0.w;
    v4_1.y += VAR_K(KTgROOT_EPS) + VAR_K(KTgROOT_EPS);
    Test__Expect_EQ(false, FCN_V(tgMH_Is_PRX_CMP_EQ_S)( v4_0, v4_1 ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_QT_Init_Axis_Angle_ELEM_S) --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_QT_Init_Axis_Angle_ELEM_S) )
{
    VEC_S_T(1)                          v4_0, v4_1, v4_2;

    tgMM_Set_U08_0xFF( &v4_0, sizeof( VEC_S_T(1) ) );
    tgMM_Set_U08_0xFF( &v4_1, sizeof( VEC_S_T(1) ) );
    tgMM_Set_U08_0xFF( &v4_2, sizeof( VEC_S_T(1) ) );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        while (TYPE_K(0) == (v4_1.m_aData[uiIndex] = FCN_F(tgCM_RAND)()));
    };

    v4_1.m_aData[3] = TYPE_K(0);
    v4_1 = FCN_V(tgMH_NORM_S)( v4_1 );

    FCN_V(tgMH_QT_Init_Axis_Angle_ELEM_S)( v4_1.x, v4_1.y, v4_1.z, TYPE_K(0,25)*VAR_K(KTgPI) );
    FCN_V(tgMH_QT_Init_Axis_Angle_S)( v4_1 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_QT_Init_Axis_Angle_S) ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_QT_Init_Axis_Angle_S) )
{
    VEC_S_T(1)                          v4_0, v4_1, v4_2;

    tgMM_Set_U08_0xFF( &v4_0, sizeof( VEC_S_T(1) ) );
    tgMM_Set_U08_0xFF( &v4_1, sizeof( VEC_S_T(1) ) );
    tgMM_Set_U08_0xFF( &v4_2, sizeof( VEC_S_T(1) ) );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        while (TYPE_K(0) == (v4_1.m_aData[uiIndex] = FCN_F(tgCM_RAND)()));
    };

    v4_1.m_aData[3] = TYPE_K(0);
    v4_1 = FCN_V(tgMH_NORM_S)( v4_1 );

    FCN_V(tgMH_QT_Init_Axis_Angle_S)( v4_1 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_QT_Init_Euler_ELEM_S) ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_QT_Init_Euler_ELEM_S) )
{
    VEC_S_T(1)                          v4_0, v4_1, v4_2;

    tgMM_Set_U08_0xFF( &v4_0, sizeof( VEC_S_T(1) ) );
    tgMM_Set_U08_0xFF( &v4_1, sizeof( VEC_S_T(1) ) );
    tgMM_Set_U08_0xFF( &v4_2, sizeof( VEC_S_T(1) ) );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        while (TYPE_K(0) == (v4_1.m_aData[uiIndex] = FCN_F(tgCM_RAND)()));
    };

    v4_1.m_aData[3] = TYPE_K(0);
    v4_1 = FCN_V(tgMH_NORM_S)( v4_1 );

    FCN_V(tgMH_QT_Init_Euler_ELEM_S)( TYPE_K(0,1)*VAR_K(KTgPI), TYPE_K(0,2)*VAR_K(KTgPI), TYPE_K(0,3)*VAR_K(KTgPI) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_QT_Init_Euler_S) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_QT_Init_Euler_S) )
{
    VEC_S_T(1)                          v4_0, v4_1, v4_2;

    tgMM_Set_U08_0xFF( &v4_0, sizeof( VEC_S_T(1) ) );
    tgMM_Set_U08_0xFF( &v4_1, sizeof( VEC_S_T(1) ) );
    tgMM_Set_U08_0xFF( &v4_2, sizeof( VEC_S_T(1) ) );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        while (TYPE_K(0) == (v4_1.m_aData[uiIndex] = FCN_F(tgCM_RAND)()));
    };

    v4_1.m_aData[3] = TYPE_K(0);
    v4_1 = FCN_V(tgMH_NORM_S)( v4_1 );

    FCN_V(tgMH_QT_Init_Euler_S)( v4_1 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_QT_Init_Euler_X_S) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_QT_Init_Euler_X_S) )
{
    FCN_V(tgMH_QT_Init_Euler_X_S)( TYPE_K(0,25)*VAR_K(KTgPI) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_QT_Init_Euler_Y_S) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_QT_Init_Euler_Y_S) )
{
    FCN_V(tgMH_QT_Init_Euler_Y_S)( TYPE_K(0,25)*VAR_K(KTgPI) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_QT_Init_Euler_Z_S) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_QT_Init_Euler_Z_S) )
{
    FCN_V(tgMH_QT_Init_Euler_Z_S)( TYPE_K(0,25)*VAR_K(KTgPI) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_Quat_To_Euler_ELEM_S) ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_Quat_To_Euler_ELEM_S) )
{
    VEC_S_T(1)                          v4_0, v4_1;

    v4_0 = FCN_V(tgMH_QT_Init_Euler_ELEM_S)( TYPE_K(0,1)*VAR_K(KTgPI), TYPE_K(0,2)*VAR_K(KTgPI), TYPE_K(0,3)*VAR_K(KTgPI) );
    FCN_V(tgMH_Quat_To_Euler_ELEM_S)( &v4_1.x, &v4_1.y, &v4_1.z, v4_0 );
    Test__Expect_EQ(true, FCN_F(tgCM_NR0)( v4_1.x - TYPE_K(0,1)*VAR_K(KTgPI) ));
    Test__Expect_EQ(true, FCN_F(tgCM_NR0)( v4_1.y - TYPE_K(0,2)*VAR_K(KTgPI) ));
    Test__Expect_EQ(true, FCN_F(tgCM_NR0)( v4_1.z - TYPE_K(0,3)*VAR_K(KTgPI) ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_Quat_To_Euler_S) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_Quat_To_Euler_S) )
{
    VAR_T()                             roll = TYPE_K(0,1) * VAR_K(KTgPI);
    VAR_T()                             pitch = TYPE_K(0,2) * VAR_K(KTgPI);
    VAR_T()                             yaw = TYPE_K(0,3) * VAR_K(KTgPI);
    VEC_S_T(1)                          v4_0, v4_2;

    VAR_T()                             cy = FCN_F(tgPM_COS)( yaw * TYPE_K(0,5) );
    VAR_T()                             sy = FCN_F(tgPM_SIN)( yaw * TYPE_K(0,5) );
    VAR_T()                             cp = FCN_F(tgPM_COS)( pitch * TYPE_K(0,5) );
    VAR_T()                             sp = FCN_F(tgPM_SIN)( pitch * TYPE_K(0,5) );
    VAR_T()                             cr = FCN_F(tgPM_COS)( roll * TYPE_K(0,5) );
    VAR_T()                             sr = FCN_F(tgPM_SIN)( roll * TYPE_K(0,5) );

    v4_0.w = cr * cp * cy + sr * sp * sy;
    v4_0.x = sr * cp * cy - cr * sp * sy;
    v4_0.y = cr * sp * cy + sr * cp * sy;
    v4_0.z = cr * cp * sy - sr * sp * cy;

    v4_2 = FCN_V(tgMH_Quat_To_Euler_S)( v4_0 );

    Test__Expect_EQ(true, FCN_F(tgCM_NR0)( v4_2.x - TYPE_K(0,1)*VAR_K(KTgPI) ));
    Test__Expect_EQ(true, FCN_F(tgCM_NR0)( v4_2.y - TYPE_K(0,2)*VAR_K(KTgPI) ));
    Test__Expect_EQ(true, FCN_F(tgCM_NR0)( v4_2.z - TYPE_K(0,3)*VAR_K(KTgPI) ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_QT_INV_S) ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_QT_INV_S) )
{
    VEC_S_T(1)                          v4_0, v4_X;

    v4_0 = FCN_V(tgMH_NORM_S)( FCN_V(tgMH_RAND_S)() );
    v4_X = FCN_V(tgMH_QT_INV_S)( v4_0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_QT_MUL_S) ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_QT_MUL_S) )
{
    VEC_S_T(1)                          v4_0, v4_1, v4_X;

    v4_0 = FCN_V(tgMH_NORM_S)( FCN_V(tgMH_RAND_S)() );
    v4_1 = FCN_V(tgMH_NORM_S)( FCN_V(tgMH_RAND_S)() );
    v4_X = FCN_V(tgMH_QT_MUL_S)( v4_0, v4_1 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_QT_Slerp_S) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_QT_Slerp_S) )
{
    VEC_S_T(1)                          v4_0, v4_1, v4_X;

    v4_0 = FCN_V(tgMH_NORM_S)( FCN_V(tgMH_RAND_S)() );
    v4_1 = FCN_V(tgMH_NORM_S)( FCN_V(tgMH_RAND_S)() );
    v4_X = FCN_V(tgMH_QT_Slerp_S)( TYPE_K(0,1), v4_0, v4_1 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_QT_Vector_To_Vector_S) --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_QT_Vector_To_Vector_S) )
{
    VEC_S_T(1)                          v4_0, v4_1;

    v4_0 = FCN_V(tgMH_NORM_S)( FCN_V(tgMH_RAND_S)() );
    v4_1 = FCN_V(tgMH_NORM_S)( FCN_V(tgMH_RAND_S)() );
    v4_0 = FCN_V(tgMH_QT_Vector_To_Vector_S)( v4_0, v4_1 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_QT_TX_S) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_QT_TX_S) )
{
    VEC_S_T(1)                          vARG_0, vARG_1;
    VEC_S_T(1)                          qR0;

    vARG_0 = FCN_V(tgMH_Init_Vector_S)( FCN_V(tgMH_RAND_S)() );
    qR0 = VEC_K(KTgUNIT_X_S);
    vARG_1 = FCN_V(tgMH_QT_TX_S)( vARG_0, qR0 );

    vARG_0 = VEC_K(KTgUNIT_X_S);
    qR0 = FCN_V(tgMH_Init_ELEM_S)( TYPE_K(0), TYPE_K(1) / FCN_F(tgPM_SQRT)(2), TYPE_K(0), TYPE_K(1) / FCN_F(tgPM_SQRT)(2) );
    vARG_1 = FCN_V(tgMH_QT_TX_S)( vARG_0, qR0 );

    Test__Expect_EQ(true, FCN_F(tgCM_NR0)(  vARG_1.x ));
    Test__Expect_EQ(true, FCN_F(tgCM_NR0)(  vARG_1.y ));
    Test__Expect_EQ(true, FCN_F(tgCM_NR1)( -vARG_1.z ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_QT_INV_TX_S) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_QT_INV_TX_S) )
{
    VEC_S_T(1)                          vARG_0, vARG_1;
    VEC_S_T(1)                          qR0;

    vARG_0 = FCN_V(tgMH_NORM_S)( FCN_V(tgMH_RAND_S)() );
    qR0 = VEC_K(KTgUNIT_X_S);
    vARG_1 = FCN_V(tgMH_QT_INV_TX_S)( vARG_0, qR0 );

    vARG_0 = VEC_K(KTgUNIT_X_S);
    qR0 = FCN_V(tgMH_Init_ELEM_S)( TYPE_K(0), TYPE_K(1) / FCN_F(tgPM_SQRT)(2), TYPE_K(0), TYPE_K(1) / FCN_F(tgPM_SQRT)(2) );
    vARG_1 = FCN_V(tgMH_QT_INV_TX_S)( vARG_0, qR0 );

    Test__Expect_EQ(true, FCN_F(tgCM_NR0)(  vARG_1.x ));
    Test__Expect_EQ(true, FCN_F(tgCM_NR0)(  vARG_1.y ));
    Test__Expect_EQ(true, FCN_F(tgCM_NR1)( -vARG_1.z ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_Rotate_Vector_Euler_X_S) -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_Rotate_Vector_Euler_X_S) )
{
    VEC_S_T(1)                          v4_0, v4_1;

    v4_0 = VEC_K(KTgUNIT_Y_S);
    v4_1 = FCN_V(tgMH_Rotate_Vector_Euler_X_S)( v4_0, TYPE_K(0,1)*VAR_K(KTgPI) );


    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_Rotate_Vector_Euler_Y_S) -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_Rotate_Vector_Euler_Y_S) )
{
    VEC_S_T(1)                          v4_0, v4_1;

    v4_0 = VEC_K(KTgUNIT_X_S);
    v4_1 = FCN_V(tgMH_Rotate_Vector_Euler_Y_S)( v4_0, TYPE_K(0,1)*VAR_K(KTgPI) );


    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_Rotate_Vector_Euler_Z_S) -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_Rotate_Vector_Euler_Z_S) )
{
    VEC_S_T(1)                          v4_0, v4_1;

    v4_0 = VEC_K(KTgUNIT_X_S);
    v4_1 = FCN_V(tgMH_Rotate_Vector_Euler_Z_S)( v4_0, TYPE_K(0,1)*VAR_K(KTgPI) );


    TEST_END_METHOD( KTgS_OK );
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

#undef FCN_V_UT
#undef FCN_V_UT_1
#undef FCN_V_UT_2
