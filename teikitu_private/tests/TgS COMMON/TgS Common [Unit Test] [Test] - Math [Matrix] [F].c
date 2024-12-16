/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common [Unit Test] [Test] - Math [Matrix] [F].c_inc
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

#if (!VEC_IS_NATIVE && TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE) || VEC_IS_NATIVE /* MACRO_COMPILE_NATIVE_MATRIX_GUARD */

/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- FCN_M_UT(tgMH_Init_T) ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_Init_T) )
{
    union
    {
        VEC_T(TEMPLATE__VECTOR_COL)         mMV;
        VEC_S_T(TEMPLATE__VECTOR_COL)       mMS;
    }                                   uMX, uMZ;
    VEC_UN_T(1)                         uS0;

    VEC_S_UN_1_MEMBER(uS0) = FCN_V(tgMH_Init_Vector_S)( FCN_V(tgMH_RAND_S)() );

    FCN_M(tgMH_Init_T_S)( &uMZ.mMS, VEC_S_UN_1_MEMBER(uS0) );
    FCN_M(tgMH_Init_T)( &uMX.mMV, VEC_UN_1_MEMBER(uS0) );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL * TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_EQ( true, FCN_F(tgCM_NR0)( uMX.mMS.m_aElement[uiIndex] - uMZ.mMS.m_aElement[uiIndex] ) );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_Init_Quat) ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_Init_Quat) )
{
    union
    {
        VEC_T(TEMPLATE__VECTOR_COL)         mMV;
        VEC_S_T(TEMPLATE__VECTOR_COL)       mMS;
    }                                   uMX, uMZ;
    VEC_UN_T(1)                         uQ0;

    VEC_S_UN_1_MEMBER(uQ0) = FCN_V(tgMH_QT_Init_Euler_S)( FCN_V(tgMH_RAND_S)() );

    FCN_M(tgMH_Init_Quat_S)( &uMZ.mMS, VEC_S_UN_1_MEMBER(uQ0) );
    FCN_M(tgMH_Init_Quat)( &uMX.mMV, VEC_UN_1_MEMBER(uQ0) );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL * TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_EQ( true, FCN_F(tgCM_NR0)( uMX.mMS.m_aElement[uiIndex] - uMZ.mMS.m_aElement[uiIndex] ) );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_CLI) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_CLI) )
{
    union
    {
        VEC_T(TEMPLATE__VECTOR_COL)         mMV;
        VEC_S_T(TEMPLATE__VECTOR_COL)       mMS;
    }                                   uMX, uMZ;

    FCN_M(tgMH_CLI_S)( &uMZ.mMS );
    FCN_M(tgMH_CLI)( &uMX.mMV );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL * TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_EQ( true, FCN_F(tgCM_NR0)( uMX.mMS.m_aElement[uiIndex] - uMZ.mMS.m_aElement[uiIndex] ) );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_Set_T) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_Set_T) )
{
    union
    {
        VEC_T(TEMPLATE__VECTOR_COL)         mMV;
        VEC_S_T(TEMPLATE__VECTOR_COL)       mMS;
    }                                   uMX, uMZ;
    VEC_UN_T(1)                         uS0;

    VEC_S_UN_1_MEMBER(uS0) = FCN_V(tgMH_Init_Vector_S)( FCN_V(tgMH_RAND_S)() );

    FCN_M(tgMH_CLI_S)( &uMZ.mMS );
    FCN_M(tgMH_Set_T_S)( &uMZ.mMS, VEC_S_UN_1_MEMBER(uS0) );
    FCN_M(tgMH_CLI)( &uMX.mMV );
    FCN_M(tgMH_Set_T)( &uMX.mMV, VEC_UN_1_MEMBER(uS0) );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL * TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_EQ( true, FCN_F(tgCM_NR0)( uMX.mMS.m_aElement[uiIndex] - uMZ.mMS.m_aElement[uiIndex] ) );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_ADD) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_ADD) )
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

    FCN_M(tgMH_ADD_S)( &uMZ.mMS, &uM0.mMS, &uM1.mMS );
    FCN_M(tgMH_ADD)( &uMX.mMV, &uM0.mMV, &uM1.mMV );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL * TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_EQ( true, FCN_F(tgCM_NR0)( uMX.mMS.m_aElement[uiIndex] - uMZ.mMS.m_aElement[uiIndex] ) );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_MUL) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_MUL) )
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

    FCN_M(tgMH_MUL_S)( &uMZ.mMS, &uM0.mMS, &uM1.mMS );
    FCN_M(tgMH_MUL)( &uMX.mMV, &uM0.mMV, &uM1.mMV );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL * TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_EQ( true, FCN_F(tgCM_NR0)( uMX.mMS.m_aElement[uiIndex] - uMZ.mMS.m_aElement[uiIndex] ) );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_DIV) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_DIV) )
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

    FCN_M(tgMH_DIV_S)( &uMZ.mMS, &uM0.mMS, &uM1.mMS );
    FCN_M(tgMH_DIV)( &uMX.mMV, &uM0.mMV, &uM1.mMV );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL * TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_EQ( true, FCN_F(tgCM_NR0)( uMX.mMS.m_aElement[uiIndex] - uMZ.mMS.m_aElement[uiIndex] ) );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_SUB) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_SUB) )
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

    FCN_M(tgMH_SUB_S)( &uMZ.mMS, &uM0.mMS, &uM1.mMS );
    FCN_M(tgMH_SUB)( &uMX.mMV, &uM0.mMV, &uM1.mMV );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL * TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_EQ( true, FCN_F(tgCM_NR0)( uMX.mMS.m_aElement[uiIndex] - uMZ.mMS.m_aElement[uiIndex] ) );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_NEG) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_NEG) )
{
    union
    {
        VEC_T(TEMPLATE__VECTOR_COL)         mMV;
        VEC_S_T(TEMPLATE__VECTOR_COL)       mMS;
    }                                   uM0, uMX, uMZ;

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        uM0.mMS.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
    };

    FCN_M(tgMH_NEG_S)( &uMZ.mMS, &uM0.mMS );
    FCN_M(tgMH_NEG)( &uMX.mMV, &uM0.mMV );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL * TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_EQ( true, FCN_F(tgCM_NR0)( uMX.mMS.m_aElement[uiIndex] - uMZ.mMS.m_aElement[uiIndex] ) );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_CAT) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_CAT) )
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

    FCN_M(tgMH_CAT_S)( &uMZ.mMS, &uM0.mMS, &uM1.mMS );
    FCN_M(tgMH_CAT)( &uMX.mMV, &uM0.mMV, &uM1.mMV );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL * TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_EQ( true, FCN_F(tgCM_NR0)( uMX.mMS.m_aElement[uiIndex] - uMZ.mMS.m_aElement[uiIndex] ) );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_INV_DET) --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_INV_DET) )
{
    union
    {
        VEC_T(TEMPLATE__VECTOR_COL)         mCOL_V;
        VEC_S_T(TEMPLATE__VECTOR_COL)       mCOL_S;
        VEC_T(TEMPLATE__VECTOR_DIM)         mDIM_V;
        VEC_S_T(TEMPLATE__VECTOR_DIM)       mDIM_S;
    }                                   uM0, uMX, uMZ;
    VAR_T()                             fDetZ;
    VEC_UN_T(1)                         uDetX;

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        uM0.mCOL_S.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
    };

    fDetZ = FCN_M(tgMH_DET_S)( &uM0.mCOL_S );
    FCN_M(tgMH_INV_DET_S)( &uMZ.mDIM_S, fDetZ, &uM0.mCOL_S );
    VEC_UN_1_MEMBER(uDetX) = FCN_M(tgMH_DET)( &uM0.mCOL_V );
    FCN_M(tgMH_INV_DET)( &uMX.mDIM_V, VEC_UN_1_MEMBER(uDetX), &uM0.mCOL_V );

    Test__Expect_EQ( true, FCN_F(tgCM_NR0)( fDetZ - VEC_S_UN_1_MEMBER(uDetX).x ) );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL * TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_EQ( true, FCN_F(tgCM_NR0)( uMX.mDIM_S.m_aElement[uiIndex] - uMZ.mDIM_S.m_aElement[uiIndex] ) );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_INV) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_INV) )
{
    union
    {
        VEC_T(TEMPLATE__VECTOR_COL)         mCOL_V;
        VEC_S_T(TEMPLATE__VECTOR_COL)       mCOL_S;
        VEC_T(TEMPLATE__VECTOR_DIM)         mDIM_V;
        VEC_S_T(TEMPLATE__VECTOR_DIM)       mDIM_S;
    }                                   uM0, uMX, uMZ;
    VAR_T()                             fDetX;

    do
    {
        for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL; ++uiIndex)
        {
            uM0.mDIM_S.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
        };

        fDetX = FCN_M(tgMH_DET_S)( &uM0.mCOL_S );
    }
    while (FCN_F(tgPM_NAN)( fDetX ) || FCN_F(tgCM_NR0)( fDetX ));

    FCN_M(tgMH_INV_S)( &uMZ.mDIM_S, &uM0.mCOL_S );
    FCN_M(tgMH_INV)( &uMX.mDIM_V, &uM0.mCOL_V );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM * TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_EQ( true, FCN_F(tgCM_NR0)( uMX.mDIM_S.m_aElement[uiIndex] - uMZ.mDIM_S.m_aElement[uiIndex] ) );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_DET) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_DET) )
{
    union
    {
        VEC_T(TEMPLATE__VECTOR_COL)         mMV;
        VEC_S_T(TEMPLATE__VECTOR_COL)       mMS;
    }                                   uM0;
    VAR_T()                             fDetZ;
    VEC_UN_T(1)                         uDetX;

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        uM0.mMS.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
    };

    fDetZ = FCN_M(tgMH_DET_S)( &uM0.mMS );
    VEC_UN_1_MEMBER(uDetX) = FCN_M(tgMH_DET)( &uM0.mMV );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_EQ( true, FCN_F(tgCM_NR0)( fDetZ - VEC_S_UN_1_MEMBER(uDetX).m_aData[uiIndex] ) );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_TX) -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_TX) )
{
    union
    {
        VEC_T(TEMPLATE__VECTOR_COL)         mMV;
        VEC_S_T(TEMPLATE__VECTOR_COL)       mMS;
    }                                   uM0;
    VEC_UN_T(1)                         uS0, uVX, uVZ;

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        uM0.mMS.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
    };

    VEC_S_UN_1_MEMBER(uS0) = FCN_V(tgMH_Init_Point_S)( FCN_V(tgMH_RAND_S)() );

    VEC_S_UN_1_MEMBER(uVZ) = FCN_M(tgMH_TX_S)( VEC_S_UN_1_MEMBER(uS0), &uM0.mMS );
    VEC_UN_1_MEMBER(uVX) = FCN_M(tgMH_TX)( VEC_UN_1_MEMBER(uS0), &uM0.mMV );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_EQ( true, FCN_F(tgCM_NR0)( VEC_S_UN_1_MEMBER(uVX).m_aData[uiIndex] - VEC_S_UN_1_MEMBER(uVZ).m_aData[uiIndex] ) );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_TX_P) ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_TX_P) )
{
    union
    {
        VEC_T(TEMPLATE__VECTOR_COL)         mMV;
        VEC_S_T(TEMPLATE__VECTOR_COL)       mMS;
    }                                   uM0;
    VEC_UN_T(1)                         uS0, uVX, uVZ;

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        uM0.mMS.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
    };

    VEC_S_UN_1_MEMBER(uS0) = FCN_V(tgMH_Init_Vector_S)( FCN_V(tgMH_RAND_S)() );

    VEC_S_UN_1_MEMBER(uVZ) = FCN_M(tgMH_TX_P_S)( VEC_S_UN_1_MEMBER(uS0), &uM0.mMS );
    VEC_UN_1_MEMBER(uVX) = FCN_M(tgMH_TX_P)( VEC_UN_1_MEMBER(uS0), &uM0.mMV );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_EQ( true, FCN_F(tgCM_NR0)( VEC_S_UN_1_MEMBER(uVX).m_aData[uiIndex] - VEC_S_UN_1_MEMBER(uVZ).m_aData[uiIndex] ) );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_TX_V) ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_TX_V) )
{
    union
    {
        VEC_T(TEMPLATE__VECTOR_COL)         mMV;
        VEC_S_T(TEMPLATE__VECTOR_COL)       mMS;
    }                                   uM0;
    VEC_UN_T(1)                         uS0, uVX, uVZ;

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        uM0.mMS.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
    };

    VEC_S_UN_1_MEMBER(uS0) = FCN_V(tgMH_Init_Point_S)( FCN_V(tgMH_RAND_S)() );

    VEC_S_UN_1_MEMBER(uVZ) = FCN_M(tgMH_TX_V_S)( VEC_S_UN_1_MEMBER(uS0), &uM0.mMS );
    VEC_UN_1_MEMBER(uVX) = FCN_M(tgMH_TX_V)( VEC_UN_1_MEMBER(uS0), &uM0.mMV );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_EQ( true, FCN_F(tgCM_NR0)( VEC_S_UN_1_MEMBER(uVX).m_aData[uiIndex] - VEC_S_UN_1_MEMBER(uVZ).m_aData[uiIndex] ) );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_Query_Row_0) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_Query_Row_0) )
{
    union
    {
        VEC_T(TEMPLATE__VECTOR_COL)         mMV;
        VEC_S_T(TEMPLATE__VECTOR_COL)       mMS;
    }                                   uM0;
    VEC_UN_T(1)                         uVX, uVZ;

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        uM0.mMS.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
    };

    VEC_S_UN_1_MEMBER(uVZ) = FCN_M(tgMH_Query_Row_0_S)( &uM0.mMS );
    VEC_UN_1_MEMBER(uVX) = FCN_M(tgMH_Query_Row_0)( &uM0.mMV );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_EQ( true, FCN_F(tgCM_NR0)( VEC_S_UN_1_MEMBER(uVX).m_aData[uiIndex] -  VEC_S_UN_1_MEMBER(uVZ).m_aData[uiIndex] ) );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_Query_Row_1) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_Query_Row_1) )
{
    union
    {
        VEC_T(TEMPLATE__VECTOR_COL)         mMV;
        VEC_S_T(TEMPLATE__VECTOR_COL)       mMS;
    }                                   uM0;
    VEC_UN_T(1)                         uVX, uVZ;

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        uM0.mMS.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
    };

    VEC_S_UN_1_MEMBER(uVZ) = FCN_M(tgMH_Query_Row_1_S)( &uM0.mMS );
    VEC_UN_1_MEMBER(uVX) = FCN_M(tgMH_Query_Row_1)( &uM0.mMV );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_EQ( true, FCN_F(tgCM_NR0)( VEC_S_UN_1_MEMBER(uVX).m_aData[uiIndex] -  VEC_S_UN_1_MEMBER(uVZ).m_aData[uiIndex] ) );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_Query_Row_2) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_Query_Row_2) )
{
    union
    {
        VEC_T(TEMPLATE__VECTOR_COL)         mMV;
        VEC_S_T(TEMPLATE__VECTOR_COL)       mMS;
    }                                   uM0;
    VEC_UN_T(1)                         uVX, uVZ;

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        uM0.mMS.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
    };

    VEC_S_UN_1_MEMBER(uVZ) = FCN_M(tgMH_Query_Row_2_S)( &uM0.mMS );
    VEC_UN_1_MEMBER(uVX) = FCN_M(tgMH_Query_Row_2)( &uM0.mMV );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_EQ( true, FCN_F(tgCM_NR0)( VEC_S_UN_1_MEMBER(uVX).m_aData[uiIndex] -  VEC_S_UN_1_MEMBER(uVZ).m_aData[uiIndex] ) );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_Query_Row_3) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_Query_Row_3) )
{
    union
    {
        VEC_T(TEMPLATE__VECTOR_COL)         mMV;
        VEC_S_T(TEMPLATE__VECTOR_COL)       mMS;
    }                                   uM0;
    VEC_UN_T(1)                         uVX, uVZ;

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        uM0.mMS.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
    };

    VEC_S_UN_1_MEMBER(uVZ) = FCN_M(tgMH_Query_Row_3_S)( &uM0.mMS );
    VEC_UN_1_MEMBER(uVX) = FCN_M(tgMH_Query_Row_3)( &uM0.mMV );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_EQ( true, FCN_F(tgCM_NR0)( VEC_S_UN_1_MEMBER(uVX).m_aData[uiIndex] -  VEC_S_UN_1_MEMBER(uVZ).m_aData[uiIndex] ) );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_Query_Col_0) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_Query_Col_0) )
{
    union
    {
        VEC_T(TEMPLATE__VECTOR_COL)         mMV;
        VEC_S_T(TEMPLATE__VECTOR_COL)       mMS;
    }                                   uM0;
    VEC_UN_T(1)                         uVX, uVZ;

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        uM0.mMS.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
    };

    VEC_S_UN_1_MEMBER(uVZ) = FCN_M(tgMH_Query_Col_0_S)( &uM0.mMS );
    VEC_UN_1_MEMBER(uVX) = FCN_M(tgMH_Query_Col_0)( &uM0.mMV );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_EQ( true, FCN_F(tgCM_NR0)( VEC_S_UN_1_MEMBER(uVX).m_aData[uiIndex] -  VEC_S_UN_1_MEMBER(uVZ).m_aData[uiIndex] ) );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_Query_Col_1) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_Query_Col_1) )
{
    union
    {
        VEC_T(TEMPLATE__VECTOR_COL)         mMV;
        VEC_S_T(TEMPLATE__VECTOR_COL)       mMS;
    }                                   uM0;
    VEC_UN_T(1)                         uVX, uVZ;

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        uM0.mMS.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
    };

    VEC_S_UN_1_MEMBER(uVZ) = FCN_M(tgMH_Query_Col_1_S)( &uM0.mMS );
    VEC_UN_1_MEMBER(uVX) = FCN_M(tgMH_Query_Col_1)( &uM0.mMV );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_EQ( true, FCN_F(tgCM_NR0)( VEC_S_UN_1_MEMBER(uVX).m_aData[uiIndex] -  VEC_S_UN_1_MEMBER(uVZ).m_aData[uiIndex] ) );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_Query_Col_2) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_Query_Col_2) )
{
    union
    {
        VEC_T(TEMPLATE__VECTOR_COL)         mMV;
        VEC_S_T(TEMPLATE__VECTOR_COL)       mMS;
    }                                   uM0;
    VEC_UN_T(1)                         uVX, uVZ;

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        uM0.mMS.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
    };

    VEC_S_UN_1_MEMBER(uVZ) = FCN_M(tgMH_Query_Col_2_S)( &uM0.mMS );
    VEC_UN_1_MEMBER(uVX) = FCN_M(tgMH_Query_Col_2)( &uM0.mMV );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_EQ( true, FCN_F(tgCM_NR0)( VEC_S_UN_1_MEMBER(uVX).m_aData[uiIndex] -  VEC_S_UN_1_MEMBER(uVZ).m_aData[uiIndex] ) );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_Query_Col_3) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_Query_Col_3) )
{
    union
    {
        VEC_T(TEMPLATE__VECTOR_COL)         mMV;
        VEC_S_T(TEMPLATE__VECTOR_COL)       mMS;
    }                                   uM0;
    VEC_UN_T(1)                         uVX, uVZ;

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        uM0.mMS.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
    };

    VEC_S_UN_1_MEMBER(uVZ) = FCN_M(tgMH_Query_Col_3_S)( &uM0.mMS );
    VEC_UN_1_MEMBER(uVX) = FCN_M(tgMH_Query_Col_3)( &uM0.mMV );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_EQ( true, FCN_F(tgCM_NR0)( VEC_S_UN_1_MEMBER(uVX).m_aData[uiIndex] -  VEC_S_UN_1_MEMBER(uVZ).m_aData[uiIndex] ) );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_Query_Axis_0) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_Query_Axis_0) )
{
    union
    {
        VEC_T(TEMPLATE__VECTOR_COL)         mMV;
        VEC_S_T(TEMPLATE__VECTOR_COL)       mMS;
    }                                   uM0;
    VEC_UN_T(1)                         uVX, uVZ;

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        uM0.mMS.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
    };

    VEC_S_UN_1_MEMBER(uVZ) = FCN_M(tgMH_Query_Axis_0_S)( &uM0.mMS );
    VEC_UN_1_MEMBER(uVX) = FCN_M(tgMH_Query_Axis_0)( &uM0.mMV );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_EQ( true, FCN_F(tgCM_NR0)( VEC_S_UN_1_MEMBER(uVX).m_aData[uiIndex] -  VEC_S_UN_1_MEMBER(uVZ).m_aData[uiIndex] ) );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_Query_Axis_1) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_Query_Axis_1) )
{
    union
    {
        VEC_T(TEMPLATE__VECTOR_COL)         mMV;
        VEC_S_T(TEMPLATE__VECTOR_COL)       mMS;
    }                                   uM0;
    VEC_UN_T(1)                         uVX, uVZ;

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        uM0.mMS.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
    };

    VEC_S_UN_1_MEMBER(uVZ) = FCN_M(tgMH_Query_Axis_1_S)( &uM0.mMS );
    VEC_UN_1_MEMBER(uVX) = FCN_M(tgMH_Query_Axis_1)( &uM0.mMV );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_EQ( true, FCN_F(tgCM_NR0)( VEC_S_UN_1_MEMBER(uVX).m_aData[uiIndex] -  VEC_S_UN_1_MEMBER(uVZ).m_aData[uiIndex] ) );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_Query_Axis_2) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_Query_Axis_2) )
{
    union
    {
        VEC_T(TEMPLATE__VECTOR_COL)         mMV;
        VEC_S_T(TEMPLATE__VECTOR_COL)       mMS;
    }                                   uM0;
    VEC_UN_T(1)                         uVX, uVZ;

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        uM0.mMS.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
    };

    VEC_S_UN_1_MEMBER(uVZ) = FCN_M(tgMH_Query_Axis_2_S)( &uM0.mMS );
    VEC_UN_1_MEMBER(uVX) = FCN_M(tgMH_Query_Axis_2)( &uM0.mMV );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_EQ( true, FCN_F(tgCM_NR0)( VEC_S_UN_1_MEMBER(uVX).m_aData[uiIndex] -  VEC_S_UN_1_MEMBER(uVZ).m_aData[uiIndex] ) );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_Query_Axis_3) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_Query_Axis_3) )
{
    union
    {
        VEC_T(TEMPLATE__VECTOR_COL)         mMV;
        VEC_S_T(TEMPLATE__VECTOR_COL)       mMS;
    }                                   uM0;
    VEC_UN_T(1)                         uVX, uVZ;

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_COL; ++uiIndex)
    {
        uM0.mMS.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
    };

    VEC_S_UN_1_MEMBER(uVZ) = FCN_M(tgMH_Query_Axis_3_S)( &uM0.mMS );
    VEC_UN_1_MEMBER(uVX) = FCN_M(tgMH_Query_Axis_3)( &uM0.mMV );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_EQ( true, FCN_F(tgCM_NR0)( VEC_S_UN_1_MEMBER(uVX).m_aData[uiIndex] -  VEC_S_UN_1_MEMBER(uVZ).m_aData[uiIndex] ) );
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
