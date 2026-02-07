/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common [Unit Test] [Test] - Math [Vector] [FXX_04].c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#if !defined (ENABLE_RELOAD_GUARD2)
    #define ENABLE_RELOAD_GUARD2

    TEST_LOCAL TgFLOAT32 tgMH_ERR_S_F32_04_1( TgVEC_S_F32_04_1_C v0 ) { return (tgCM_MAX_F32( 10.0F*tgMH_LEN_S_F32_04_1( v0 ), 1.0F )); }
    TEST_LOCAL TgFLOAT64 tgMH_ERR_S_F64_04_1( TgVEC_S_F64_04_1_C v0 ) { return (tgCM_MAX_F64(  10.0*tgMH_LEN_S_F64_04_1( v0 ), 1.0 )); }

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

#define FCN_V_UT(...)                       MULTI_MACRO(FCN_V_UT, __VA_ARGS__)
#define FCN_V_UT_1(F)                       TgMACRO_CONCAT5( UNIT_TEST__TEST__##F, _, GENERATE__VEC_DESC, _, 1 )
#define FCN_V_UT_2(F, COL)                  TgMACRO_CONCAT5( UNIT_TEST__TEST__##F, _, GENERATE__VEC_DESC, _, COL )

#if (!VEC_IS_NATIVE && TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE) || VEC_IS_NATIVE /* MACRO_COMPILE_NATIVE_MATRIX_GUARD */

/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- FCN_V_UT(tgMH_Init_ELEM) --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_Init_ELEM) )
{
    union
    {
        VEC_T(1)                            vN;
        VEC_S_T(1)                          vT;
    }                                   sV0;

    sV0.vN = FCN_V(tgMH_Init_ELEM)( TYPE_K(7,0), TYPE_K(2,0), TYPE_K(3,0), TYPE_K(4,0) );

    Test__Expect_EQ(sV0.vT.x, TYPE_K(7,0) );
    Test__Expect_EQ(sV0.vT.y, TYPE_K(2,0) );
    Test__Expect_EQ(sV0.vT.z, TYPE_K(3,0) );
    Test__Expect_EQ(sV0.vT.w, TYPE_K(4,0) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_Init_Point_ELEM) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_Init_Point_ELEM) )
{
    union
    {
        VEC_T(1)                            vN;
        VEC_S_T(1)                          vT;
    }                                   sV0;

    sV0.vN = FCN_V(tgMH_Init_Point_ELEM)( TYPE_K(7,0), TYPE_K(2,0), TYPE_K(3,0) );

    Test__Expect_EQ(sV0.vT.x, TYPE_K(7,0) );
    Test__Expect_EQ(sV0.vT.y, TYPE_K(2,0) );
    Test__Expect_EQ(sV0.vT.z, TYPE_K(3,0) );
    Test__Expect_EQ(sV0.vT.w, TYPE_K(1,0) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_Init_Vector_ELEM) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_Init_Vector_ELEM) )
{
    union
    {
        VEC_T(1)                            vN;
        VEC_S_T(1)                          vT;
    }                                   sV0;

    sV0.vN = FCN_V(tgMH_Init_Vector_ELEM)( TYPE_K(2,0), TYPE_K(1,0), TYPE_K(3,0) );

    Test__Expect_EQ(sV0.vT.x, TYPE_K(2,0) );
    Test__Expect_EQ(sV0.vT.y, TYPE_K(1,0) );
    Test__Expect_EQ(sV0.vT.z, TYPE_K(3,0) );
    Test__Expect_EQ(sV0.vT.w, TYPE_K(0,0) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_Init_Point) ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_Init_Point) )
{
    union
    {
        VEC_T(1)                            vN;
        VEC_S_T(1)                          vT;
    }                                   sV0;

    sV0.vN = FCN_V(tgMH_Init_ELEM)( TYPE_K(7,0), TYPE_K(2,0), TYPE_K(3,0), TYPE_K(5,0) );
    sV0.vN = FCN_V(tgMH_Init_Point)( sV0.vN );
    Test__Expect_EQ(true, FCN_V(tgMH_Is_Valid_Point_S)( sV0.vT ));

    Test__Expect_EQ(sV0.vT.x, TYPE_K(7,0) );
    Test__Expect_EQ(sV0.vT.y, TYPE_K(2,0) );
    Test__Expect_EQ(sV0.vT.z, TYPE_K(3,0) );
    Test__Expect_EQ(sV0.vT.w, TYPE_K(1,0) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_Init_Vector) ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_Init_Vector) )
{
    union
    {
        VEC_T(1)                            vN;
        VEC_S_T(1)                          vT;
    }                                   sV0;

    sV0.vN = FCN_V(tgMH_Init_ELEM)( TYPE_K(7,0), TYPE_K(2,0), TYPE_K(3,0), TYPE_K(5,0) );
    sV0.vN = FCN_V(tgMH_Init_Vector)( sV0.vN );
    Test__Expect_EQ(true, FCN_V(tgMH_Is_Valid_Vector_S)( sV0.vT ));

    Test__Expect_EQ(sV0.vT.x, TYPE_K(7,0) );
    Test__Expect_EQ(sV0.vT.y, TYPE_K(2,0) );
    Test__Expect_EQ(sV0.vT.z, TYPE_K(3,0) );
    Test__Expect_EQ(sV0.vT.w, TYPE_K(0,0) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_RAND) ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_RAND) )
{
    FCN_V(tgMH_RAND)();

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_SPX) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_SPX) )
{
    union
    {
        VEC_T(1)                            vN;
        VEC_S_T(1)                          vT;
    }                                   sV0;

    sV0.vN = FCN_V(tgMH_Init_ELEM)( TYPE_K(2,0), TYPE_K(1,0), TYPE_K(3,0), TYPE_K(5,0) );
    sV0.vN = FCN_V(tgMH_SPX)( sV0.vN );

    Test__Expect_EQ( sV0.vT.x, sV0.vT.x );
    Test__Expect_EQ( sV0.vT.y, sV0.vT.x );
    Test__Expect_EQ( sV0.vT.z, sV0.vT.x );
    Test__Expect_EQ( sV0.vT.w, sV0.vT.x );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_SPY) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_SPY) )
{
    union
    {
        VEC_T(1)                            vN;
        VEC_S_T(1)                          vT;
    }                                   sV0;

    sV0.vN = FCN_V(tgMH_Init_ELEM)( TYPE_K(2), TYPE_K(1), TYPE_K(3), TYPE_K(5) );
    sV0.vN = FCN_V(tgMH_SPY)( sV0.vN );

    Test__Expect_EQ( sV0.vT.x, sV0.vT.y );
    Test__Expect_EQ( sV0.vT.y, sV0.vT.y );
    Test__Expect_EQ( sV0.vT.z, sV0.vT.y );
    Test__Expect_EQ( sV0.vT.w, sV0.vT.y );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_SPZ) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_SPZ) )
{
    union
    {
        VEC_T(1)                            vN;
        VEC_S_T(1)                          vT;
    }                                   sV0;

    sV0.vN = FCN_V(tgMH_Init_ELEM)( TYPE_K(2,0), TYPE_K(1,0), TYPE_K(3,0), TYPE_K(5,0) );
    sV0.vN = FCN_V(tgMH_SPZ)( sV0.vN );

    Test__Expect_EQ( sV0.vT.x, sV0.vT.z );
    Test__Expect_EQ( sV0.vT.y, sV0.vT.z );
    Test__Expect_EQ( sV0.vT.z, sV0.vT.z );
    Test__Expect_EQ( sV0.vT.w, sV0.vT.z );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_SPW) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_SPW) )
{
    union
    {
        VEC_T(1)                            vN;
        VEC_S_T(1)                          vT;
    }                                   sV0;

    sV0.vN = FCN_V(tgMH_Init_ELEM)( TYPE_K(2,0), TYPE_K(1,0), TYPE_K(3,0), TYPE_K(5,0) );
    sV0.vN = FCN_V(tgMH_SPW)( sV0.vN );

    Test__Expect_EQ( sV0.vT.x, sV0.vT.w );
    Test__Expect_EQ( sV0.vT.y, sV0.vT.w );
    Test__Expect_EQ( sV0.vT.z, sV0.vT.w );
    Test__Expect_EQ( sV0.vT.w, sV0.vT.w );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_DOT3) ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_DOT3) )
{
    union
    {
        VEC_T(1)                            vN;
        VEC_S_T(1)                          vT;
    }                                   sV0, sV1, sV2;
    VAR_T()                             fDot;

    sV0.vN = FCN_V(tgMH_RAND)();
    sV1.vN = FCN_V(tgMH_RAND)();

    sV2.vN = FCN_V(tgMH_DOT3)( sV0.vN, sV1.vN );
    fDot = FCN_V(tgMH_DOT3_S)( sV0.vT, sV1.vT );

    Test__Expect_NE(false, FCN_F(tgCM_NR0)( fDot - sV2.vT.x ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_CX) ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_CX) )
{
    union
    {
        VEC_T(1)                            vN;
        VEC_S_T(1)                          vT;
    }                                   sV0, sV1, sV2, sV3;
    VAR_T()                             fLimit;

    sV2.vN = FCN_V(tgMH_CX)( VEC_K(KTgUNIT_X), VEC_K(KTgUNIT_Y) );

    Test__Expect_EQ(true, FCN_F(tgCM_NR0)( sV2.vT.m_aData[0] - VEC_K(KTgUNIT_Z_S).m_aData[0] ));
    Test__Expect_EQ(true, FCN_F(tgCM_NR0)( sV2.vT.m_aData[1] - VEC_K(KTgUNIT_Z_S).m_aData[1] ));
    Test__Expect_EQ(true, FCN_F(tgCM_NR0)( sV2.vT.m_aData[2] - VEC_K(KTgUNIT_Z_S).m_aData[2] ));

    sV0.vN = FCN_V(tgMH_Init_Vector)( FCN_V(tgMH_RAND)() );
    sV1.vN = FCN_V(tgMH_Init_Vector)( FCN_V(tgMH_RAND)() );

    sV2.vN = FCN_V(tgMH_CX)( sV0.vN, sV1.vN );
    sV3.vT = FCN_V(tgMH_CX_S)( sV0.vT, sV1.vT );

    Test__Expect_EQ(true, FCN_F(tgCM_NR0)( sV2.vT.m_aData[0] - sV3.vT.m_aData[0] ));
    Test__Expect_EQ(true, FCN_F(tgCM_NR0)( sV2.vT.m_aData[1] - sV3.vT.m_aData[1] ));
    Test__Expect_EQ(true, FCN_F(tgCM_NR0)( sV2.vT.m_aData[2] - sV3.vT.m_aData[2] ));

    fLimit = VAR_K(KTgEPS) * FCN_V(tgMH_ERR_S)( sV0.vT ) * FCN_V(tgMH_ERR_S)( sV1.vT ) * FCN_V(tgMH_ERR_S)( sV2.vT );
    
    sV3.vN = FCN_V(tgMH_DOT)( sV0.vN, sV2.vN );
    Test__Expect_NE(false, FCN_F(tgPM_ABS)(sV3.vT.x) <= fLimit);
    sV3.vN = FCN_V(tgMH_DOT)( sV1.vN, sV2.vN );
    Test__Expect_NE(false, FCN_F(tgPM_ABS)(sV3.vT.x) <= fLimit);

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_UCX) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_UCX) )
{
    union
    {
        VEC_T(1)                            vN;
        VEC_S_T(1)                          vT;
    }                                   sV0, sV1, sV2, sV3;
    VAR_T()                             fLimit;

    sV2.vN = FCN_V(tgMH_UCX)( VEC_K(KTgUNIT_X), VEC_K(KTgUNIT_Y) );

    Test__Expect_EQ(true, FCN_F(tgCM_NR0)( sV2.vT.m_aData[0] - VEC_K(KTgUNIT_Z_S).m_aData[0] ));
    Test__Expect_EQ(true, FCN_F(tgCM_NR0)( sV2.vT.m_aData[1] - VEC_K(KTgUNIT_Z_S).m_aData[1] ));
    Test__Expect_EQ(true, FCN_F(tgCM_NR0)( sV2.vT.m_aData[2] - VEC_K(KTgUNIT_Z_S).m_aData[2] ));

    sV0.vN = FCN_V(tgMH_Init_Vector)( FCN_V(tgMH_RAND)() );
    sV1.vN = FCN_V(tgMH_Init_Vector)( FCN_V(tgMH_RAND)() );

    sV2.vN = FCN_V(tgMH_UCX)( sV0.vN, sV1.vN );
    sV3.vT = FCN_V(tgMH_UCX_S)( sV0.vT, sV1.vT );

    Test__Expect_EQ(true, FCN_F(tgCM_NR0)( sV2.vT.m_aData[0] - sV3.vT.m_aData[0] ));
    Test__Expect_EQ(true, FCN_F(tgCM_NR0)( sV2.vT.m_aData[1] - sV3.vT.m_aData[1] ));
    Test__Expect_EQ(true, FCN_F(tgCM_NR0)( sV2.vT.m_aData[2] - sV3.vT.m_aData[2] ));

    fLimit = VAR_K(KTgEPS) * FCN_V(tgMH_ERR_S)( sV0.vT ) * FCN_V(tgMH_ERR_S)( sV1.vT ) * FCN_V(tgMH_ERR_S)( sV2.vT );

    sV3.vN = FCN_V(tgMH_DOT)( sV0.vN, sV2.vN );
    Test__Expect_NE(false, FCN_F(tgPM_ABS)(sV3.vT.x) <= fLimit);
    sV3.vN = FCN_V(tgMH_DOT)( sV1.vN, sV2.vN );
    Test__Expect_NE(false, FCN_F(tgPM_ABS)(sV3.vT.x) <= fLimit);

    sV3.vN = FCN_V(tgMH_LEN)( sV2.vN );
    Test__Expect_EQ(true, FCN_F(tgCM_NR1)( sV3.vT.m_aData[0] ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_UCX_LEN) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_UCX_LEN) )
{
    union
    {
        VEC_T(1)                            vN;
        VEC_S_T(1)                          vT;
    }                                   sV0, sV1, sV2, sV3, sV4;
    VAR_T()                             fLimit, fLength;

    sV3.vN = FCN_V(tgMH_UCX_LEN)( &sV2.vN, VEC_K(KTgUNIT_X), VEC_K(KTgUNIT_Y) );

    Test__Expect_EQ(true, FCN_F(tgCM_NR0)( sV3.vT.m_aData[0] - VEC_K(KTgUNIT_Z_S).m_aData[0] ));
    Test__Expect_EQ(true, FCN_F(tgCM_NR0)( sV3.vT.m_aData[1] - VEC_K(KTgUNIT_Z_S).m_aData[1] ));
    Test__Expect_EQ(true, FCN_F(tgCM_NR0)( sV3.vT.m_aData[2] - VEC_K(KTgUNIT_Z_S).m_aData[2] ));

    sV0.vN = FCN_V(tgMH_Init_Vector)( FCN_V(tgMH_RAND)() );
    sV1.vN = FCN_V(tgMH_Init_Vector)( FCN_V(tgMH_RAND)() );

    sV3.vN = FCN_V(tgMH_UCX_LEN)( &sV2.vN, sV0.vN, sV1.vN );
    sV4.vT = FCN_V(tgMH_UCX_LEN_S)( &fLength, sV0.vT, sV1.vT );

    Test__Expect_EQ(true, FCN_F(tgCM_NR0)( sV3.vT.m_aData[0] - sV4.vT.m_aData[0] ));
    Test__Expect_EQ(true, FCN_F(tgCM_NR0)( sV3.vT.m_aData[1] - sV4.vT.m_aData[1] ));
    Test__Expect_EQ(true, FCN_F(tgCM_NR0)( sV3.vT.m_aData[2] - sV4.vT.m_aData[2] ));

    fLimit = VAR_K(KTgEPS) * FCN_V(tgMH_ERR_S)( sV0.vT ) * FCN_V(tgMH_ERR_S)( sV1.vT ) * FCN_V(tgMH_ERR_S)( sV3.vT );
    
    sV4.vN = FCN_V(tgMH_DOT)( sV0.vN, sV3.vN );
    Test__Expect_NE(false, FCN_F(tgPM_ABS)( sV4.vT.x ) <= fLimit);
    sV4.vN = FCN_V(tgMH_DOT)( sV1.vN, sV3.vN );
    Test__Expect_NE(false, FCN_F(tgPM_ABS)( sV4.vT.x ) <= fLimit);
    
    sV4.vN = FCN_V(tgMH_LEN)( sV3.vN );
    Test__Expect_EQ(true, FCN_F(tgCM_NR1)( sV4.vT.m_aData[0] ));
    Test__Expect_EQ(true, FCN_F(tgCM_NR0)( sV2.vT.m_aData[0] - fLength ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_PRX3_CMP_EQ) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_PRX3_CMP_EQ) )
{
    union
    {
        VEC_T(1)                            vN;
        VEC_S_T(1)                          vT;
    }                                   sV0, sV1;

    sV0.vN = FCN_V(tgMH_RAND)();
    sV1.vN = sV0.vN;
    Test__Expect_EQ(true, FCN_V(tgMH_PRX3_CMP_EQ)( sV0.vN, sV1.vN ));

    sV1.vT.w = -sV1.vT.w;
    Test__Expect_NE(false, FCN_V(tgMH_PRX3_CMP_EQ)( sV0.vN, sV1.vN ));

    sV1.vT.w = sV0.vT.w;
    sV1.vT.y += VAR_K(KTgROOT_EPS) + VAR_K(KTgROOT_EPS);
    Test__Expect_EQ(false, FCN_V(tgMH_PRX3_CMP_EQ)( sV0.vN, sV1.vN ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_Is_PRX_CMP_EQ) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_Is_PRX_CMP_EQ) )
{
    union
    {
        VEC_T(1)                            vN;
        VEC_S_T(1)                          vT;
    }                                   sV0, sV1;

    sV0.vN = FCN_V(tgMH_RAND)();
    sV1.vN = sV0.vN;
    Test__Expect_NE(false, FCN_V(tgMH_Is_PRX_CMP_EQ)( sV0.vN, sV1.vN ));

    sV1.vT.w = -sV1.vT.w;
    Test__Expect_EQ(false, FCN_V(tgMH_Is_PRX_CMP_EQ)( sV0.vN, sV1.vN ));

    sV1.vT.w = sV0.vT.w;
    sV1.vT.y += VAR_K(KTgROOT_EPS) + VAR_K(KTgROOT_EPS);
    Test__Expect_EQ(false, FCN_V(tgMH_Is_PRX_CMP_EQ)( sV0.vN, sV1.vN ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_QT_INV) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_QT_INV) )
{
    union
    {
        VEC_T(1)                            vN;
        VEC_S_T(1)                          vS;
    }                                   uQ0, uVX, uVZ;

    uQ0.vS = FCN_V(tgMH_QT_Init_Euler_S)( FCN_V(tgMH_RAND_S)() );

    uVZ.vS = FCN_V(tgMH_QT_INV_S)( uQ0.vS );
    uVX.vN = FCN_V(tgMH_QT_INV)( uQ0.vN );

    Test__Expect_EQ(true, FCN_F(tgCM_NR0)( uVX.vS.m_aData[0] - uVZ.vS.m_aData[0] ));
    Test__Expect_EQ(true, FCN_F(tgCM_NR0)( uVX.vS.m_aData[1] - uVZ.vS.m_aData[1] ));
    Test__Expect_EQ(true, FCN_F(tgCM_NR0)( uVX.vS.m_aData[2] - uVZ.vS.m_aData[2] ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_QT_MUL) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_QT_MUL) )
{
    union
    {
        VEC_T(1)                            vN;
        VEC_S_T(1)                          vS;
    }                                   uQ0, uQ1, uQX, uQZ;

    uQ0.vS = FCN_V(tgMH_QT_Init_Euler_S)( FCN_V(tgMH_RAND_S)() );
    uQ1.vS = FCN_V(tgMH_QT_Init_Euler_S)( FCN_V(tgMH_RAND_S)() );

    uQZ.vS = FCN_V(tgMH_QT_MUL_S)( uQ0.vS, uQ1.vS );
    uQX.vN = FCN_V(tgMH_QT_MUL)( uQ0.vN, uQ1.vN );

    Test__Expect_EQ(true, FCN_F(tgCM_NR0)( uQX.vS.m_aData[0] - uQZ.vS.m_aData[0] ));
    Test__Expect_EQ(true, FCN_F(tgCM_NR0)( uQX.vS.m_aData[1] - uQZ.vS.m_aData[1] ));
    Test__Expect_EQ(true, FCN_F(tgCM_NR0)( uQX.vS.m_aData[2] - uQZ.vS.m_aData[2] ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_QT_Slerp) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_QT_Slerp) )
{
    union
    {
        VEC_T(1)                            vN;
        VEC_S_T(1)                          vS;
    }                                   uQ0, uQ1, uQX, uQZ;

    uQ0.vS = FCN_V(tgMH_QT_Init_Euler_S)( FCN_V(tgMH_RAND_S)() );
    uQ1.vS = FCN_V(tgMH_QT_Init_Euler_S)( FCN_V(tgMH_RAND_S)() );

    uQZ.vS = FCN_V(tgMH_QT_Slerp_S)( TYPE_K(0,1), uQ0.vS, uQ1.vS );
    uQX.vN = FCN_V(tgMH_QT_Slerp)( FCN_V(tgMH_SET1)(TYPE_K(0,1)), uQ0.vN, uQ1.vN );

    Test__Expect_EQ(true, FCN_F(tgCM_NR0)( uQX.vS.m_aData[0] - uQZ.vS.m_aData[0] ));
    Test__Expect_EQ(true, FCN_F(tgCM_NR0)( uQX.vS.m_aData[1] - uQZ.vS.m_aData[1] ));
    Test__Expect_EQ(true, FCN_F(tgCM_NR0)( uQX.vS.m_aData[2] - uQZ.vS.m_aData[2] ));
    Test__Expect_EQ(true, FCN_F(tgCM_NR0)( uQX.vS.m_aData[3] - uQZ.vS.m_aData[3] ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_QT_Vector_To_Vector) ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_QT_Vector_To_Vector) )
{
    union
    {
        VEC_T(1)                            vN;
        VEC_S_T(1)                          vT;
    }                                   sV0, sV1, sV2, sV3;

    sV0.vN = FCN_V(tgMH_Init_Vector)( FCN_V(tgMH_RAND)() );
    sV1.vN = FCN_V(tgMH_Init_Vector)( FCN_V(tgMH_RAND)() );

    sV3.vT = FCN_V(tgMH_QT_Vector_To_Vector_S)( sV0.vT, sV1.vT );
    sV2.vN = FCN_V(tgMH_QT_Vector_To_Vector)( sV0.vN, sV1.vN );

    Test__Expect_EQ(true, FCN_F(tgCM_NR0)( sV3.vT.m_aData[0] - sV2.vT.m_aData[0] ));
    Test__Expect_EQ(true, FCN_F(tgCM_NR0)( sV3.vT.m_aData[1] - sV2.vT.m_aData[1] ));
    Test__Expect_EQ(true, FCN_F(tgCM_NR0)( sV3.vT.m_aData[2] - sV2.vT.m_aData[2] ));
    Test__Expect_EQ(true, FCN_F(tgCM_NR0)( sV3.vT.m_aData[3] - sV2.vT.m_aData[3] ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_QT_TX) --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_QT_TX) )
{
    union
    {
        VEC_T(1)                            vN;
        VEC_S_T(1)                          vS;
    }                                   uV0, uQ0, uVX, uVZ;

    uQ0.vS = FCN_V(tgMH_QT_Init_Euler_S)( FCN_V(tgMH_RAND_S)() );
    uV0.vN = FCN_V(tgMH_Init_Vector)( FCN_V(tgMH_RAND)() );

    uVZ.vS = FCN_V(tgMH_QT_TX_S)( uV0.vS, uQ0.vS );
    uVX.vN = FCN_V(tgMH_QT_TX)( uV0.vN, uQ0.vN );

    Test__Expect_EQ(true, FCN_F(tgCM_NR0)( uVX.vS.m_aData[0] - uVZ.vS.m_aData[0] ));
    Test__Expect_EQ(true, FCN_F(tgCM_NR0)( uVX.vS.m_aData[1] - uVZ.vS.m_aData[1] ));
    Test__Expect_EQ(true, FCN_F(tgCM_NR0)( uVX.vS.m_aData[2] - uVZ.vS.m_aData[2] ));
    Test__Expect_EQ(true, FCN_F(tgCM_NR0)( uVX.vS.m_aData[3] - uVZ.vS.m_aData[3] ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_QT_INV_TX) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_QT_INV_TX) )
{
    union
    {
        VEC_T(1)                            vN;
        VEC_S_T(1)                          vS;
    }                                   uV0, uQ0, uVX, uVZ;

    uQ0.vS = FCN_V(tgMH_QT_Init_Euler_S)( FCN_V(tgMH_RAND_S)() );
    uV0.vN = FCN_V(tgMH_Init_Vector)( FCN_V(tgMH_RAND)() );

    uVZ.vS = FCN_V(tgMH_QT_INV_TX_S)( uV0.vS, uQ0.vS );
    uVX.vN = FCN_V(tgMH_QT_INV_TX)( uV0.vN, uQ0.vN );

    Test__Expect_EQ(true, FCN_F(tgCM_NR0)( uVX.vS.m_aData[0] - uVZ.vS.m_aData[0] ));
    Test__Expect_EQ(true, FCN_F(tgCM_NR0)( uVX.vS.m_aData[1] - uVZ.vS.m_aData[1] ));
    Test__Expect_EQ(true, FCN_F(tgCM_NR0)( uVX.vS.m_aData[2] - uVZ.vS.m_aData[2] ));
    Test__Expect_EQ(true, FCN_F(tgCM_NR0)( uVX.vS.m_aData[3] - uVZ.vS.m_aData[3] ));

    TEST_END_METHOD( KTgS_OK );
}


/* =============================================================================================================================================================================== */

/*# (!VEC_IS_NATIVE && TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE) || VEC_IS_NATIVE */
#endif

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

#undef FCN_V_UT
#undef FCN_V_UT_1
#undef FCN_V_UT_2
