/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common [Unit Test] [Test] - Math [Matrix] [S] [F] [44].c_inc
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

/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- FCN_M_UT(tgMH_CAT_34_44_S) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_CAT_34_44_S) )
{
    VEC_S_T(4)                          mM1, mMX;
    VEC_S_T(3)                          mM0;

    for (TgRSIZE uiIndex = 0; uiIndex < 3; ++uiIndex)
    {
        mM0.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
        mM1.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
    };
    mM1.m_avCol[3] = FCN_V(tgMH_RAND_S)();

    FCN_M(tgMH_CAT_34_44_S)( &mMX, &mM0, &mM1 );

    for (TgRSIZE uiIndex = 0; uiIndex < 16; ++uiIndex)
    {
        VAR_T()                             tTotal;

        tTotal = TYPE_K(0);

        for (TgRSIZE uiCheck = 0; uiCheck < 3; ++uiCheck)
        {
            tTotal += mM0.m_aColRow[uiCheck][uiIndex % 4] * mM1.m_aColRow[uiIndex / 4][uiCheck];
        };

        if (3 == (uiIndex % 4))
        {
            tTotal += mM1.m_aColRow[uiIndex / 4][3];
        };

        Test__Expect_EQ(true, FCN_F(tgCM_NR0)( tTotal - mMX.m_aColRow[uiIndex / 4][uiIndex % 4] ));
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_CAT_44_34_S) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_CAT_44_34_S) )
{
    VEC_S_T(4)                          mM0, mMX;
    VEC_S_T(3)                          mM1;

    for (TgRSIZE uiIndex = 0; uiIndex < 3; ++uiIndex)
    {
        mM0.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
        mM1.m_avCol[uiIndex] = FCN_V(tgMH_RAND_S)();
    };
    mM0.m_avCol[3] = FCN_V(tgMH_RAND_S)();

    FCN_M(tgMH_CAT_44_34_S)( &mMX, &mM0, &mM1 );

    for (TgRSIZE uiIndex = 0; uiIndex < 12; ++uiIndex)
    {
        VAR_T()                             tTotal;

        tTotal = TYPE_K(0);

        for (TgRSIZE uiCheck = 0; uiCheck < 4; ++uiCheck)
        {
            tTotal += mM0.m_aColRow[uiCheck][uiIndex % 4] * mM1.m_aColRow[uiIndex / 4][uiCheck];
        };

        Test__Expect_EQ(true, FCN_F(tgCM_NR0)( tTotal - mMX.m_aColRow[uiIndex / 4][uiIndex % 4] ));
    };

    for (TgRSIZE uiIndex = 12; uiIndex < 16; ++uiIndex)
    {
        Test__Expect_EQ(true, FCN_F(tgCM_NR0)( mM0.m_aColRow[uiIndex / 4][uiIndex % 4] - mMX.m_aColRow[uiIndex / 4][uiIndex % 4] ));
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_TR_S) -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_TR_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       xM0, xM1;

    for (TgRSIZE iIndex = 0; iIndex < TEMPLATE__VECTOR_COL * TEMPLATE__VECTOR_DIM; ++iIndex)
    {
        while (0 == (xM1.m_aElement[iIndex] = FCN_F(tgCM_RAND)()));
    };

    FCN_M(tgMH_TR_S)( &xM0, &xM1 );

    for (TgRSIZE iRow = 0; iRow < 4; ++iRow)
    {
        for (TgRSIZE iCol = 0; iCol < 4; ++iCol)
        {
            Test__Expect_EQ( xM0.m_aColRow[iCol][iRow], xM1.m_aColRow[iRow][iCol] );
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_Look_S) ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_Look_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       xM0;
    VEC_S_T(1)                          vFrom, vTo, vUp, vT;

    for (TgRSIZE iIndex = 0; iIndex < 3; ++iIndex)
    {
        while (0 == (vUp.m_aData[iIndex] = FCN_F(tgCM_RAND)()));
        while (0 == (vFrom.m_aData[iIndex] = FCN_F(tgCM_RAND)()));
        while (0 == (vTo.m_aData[iIndex] = FCN_F(tgCM_RAND)()));
    };
    vFrom.w = TYPE_K(1);
    vTo.w = TYPE_K(1);
    vUp.w = TYPE_K(0);

    vT = FCN_V(tgMH_SET1_S)( TYPE_K(0) );
    vT.x = vUp.x;
    vT.y = vUp.y;
    vT.z = vUp.z;
    FCN_V(tgMH_NORM_S)( vT );

    FCN_M(tgMH_Look_S)( &xM0, vFrom, vTo, vT );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_LookLH_S) ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_LookLH_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       xM0;
    VEC_S_T(1)                          vFrom, vTo, vUp, vT;

    for (TgRSIZE iIndex = 0; iIndex < 3; ++iIndex)
    {
        while (0 == (vUp.m_aData[iIndex] = FCN_F(tgCM_RAND)()));
        while (0 == (vFrom.m_aData[iIndex] = FCN_F(tgCM_RAND)()));
        while (0 == (vTo.m_aData[iIndex] = FCN_F(tgCM_RAND)()));
    };
    vFrom.w = TYPE_K(1);
    vTo.w = TYPE_K(1);
    vUp.w = TYPE_K(0);

    vT = FCN_V(tgMH_SET1_S)( TYPE_K(0) );
    vT.x = vUp.x;
    vT.y = vUp.y;
    vT.z = vUp.z;
    FCN_V(tgMH_NORM_S)( vT );

    /* #UNITTEST */
    FCN_M(tgMH_LookLH_S)(&xM0, vFrom, vTo, vT );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_LookRH_S) ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_LookRH_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       xM0;
    VEC_S_T(1)                          vFrom, vTo, vUp, vT;

    for (TgRSIZE iIndex = 0; iIndex < 3; ++iIndex)
    {
        while (0 == (vUp.m_aData[iIndex] = FCN_F(tgCM_RAND)()));
        while (0 == (vFrom.m_aData[iIndex] = FCN_F(tgCM_RAND)()));
        while (0 == (vTo.m_aData[iIndex] = FCN_F(tgCM_RAND)()));
    };
    vFrom.w = TYPE_K(1);
    vTo.w = TYPE_K(1);
    vUp.w = TYPE_K(0);

    vT = FCN_V(tgMH_SET1_S)( TYPE_K(0) );
    vT.x = vUp.x;
    vT.y = vUp.y;
    vT.z = vUp.z;
    FCN_V(tgMH_NORM_S)( vT );

    FCN_M(tgMH_LookRH_S)( &xM0, vFrom, vTo, vT );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_PProjLH_S) --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_PProjLH_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       xM0;

    FCN_M(tgMH_PProjLH_S)( &xM0, TYPE_K(1), TYPE_K(2,0), TYPE_K(3,0), TYPE_K(4,0) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_PProjRH_S) --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_PProjRH_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       xM0;

    FCN_M(tgMH_PProjRH_S)( &xM0, TYPE_K(1), TYPE_K(2,0), TYPE_K(3,0), TYPE_K(4,0) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_PProj_S) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_PProj_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       xM0;

    FCN_M(tgMH_PProj_S)( &xM0, TYPE_K(1), TYPE_K(2,0), TYPE_K(3,0), TYPE_K(4,0) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_PProj_OffsetLH_S) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_PProj_OffsetLH_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       xM0;

    FCN_M(tgMH_PProj_OffsetLH_S)( &xM0, TYPE_K(1), TYPE_K(2,0), TYPE_K(3,0), TYPE_K(4,0), TYPE_K(5,0), TYPE_K(6,0) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_PProj_OffsetRH_S) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_PProj_OffsetRH_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       xM0;

    FCN_M(tgMH_PProj_OffsetRH_S)( &xM0, TYPE_K(1), TYPE_K(2,0), TYPE_K(3,0), TYPE_K(4,0), TYPE_K(5,0), TYPE_K(6,0) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_PProj_Offset_S) ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_PProj_Offset_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       xM0;

    FCN_M(tgMH_PProj_Offset_S)( &xM0, TYPE_K(1), TYPE_K(2,0), TYPE_K(3,0), TYPE_K(4,0), TYPE_K(5,0), TYPE_K(6,0) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_PProj_FoV_S) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_PProj_FoV_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       xM0;

    FCN_M(tgMH_PProj_FoVLH_S)( &xM0, TYPE_K(1), TYPE_K(2,0), TYPE_K(3,0), TYPE_K(4,0) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_PProj_FoVLH_S) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_PProj_FoVLH_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       xM0;

    FCN_M(tgMH_PProj_FoVRH_S)( &xM0, TYPE_K(1), TYPE_K(2,0), TYPE_K(3,0), TYPE_K(4,0) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_PProj_FoVRH_S) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_PProj_FoVRH_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       xM0;

    FCN_M(tgMH_PProj_FoV_S)( &xM0, TYPE_K(1), TYPE_K(2,0), TYPE_K(3,0), TYPE_K(4,0) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_OrthoLH_S) --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_OrthoLH_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       xM0;

    FCN_M(tgMH_OrthoLH_S)(&xM0, TYPE_K(1), TYPE_K(2,0), TYPE_K(3,0), TYPE_K(4,0) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_OrthoRH_S) --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_OrthoRH_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       xM0;

    FCN_M(tgMH_OrthoRH_S)( &xM0, TYPE_K(1), TYPE_K(2,0), TYPE_K(3,0), TYPE_K(4,0) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_Ortho_S) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_Ortho_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       xM0;

    FCN_M(tgMH_Ortho_S)( &xM0, TYPE_K(1), TYPE_K(2,0), TYPE_K(3,0), TYPE_K(4,0) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_Ortho_OffsetLH_S) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_Ortho_OffsetLH_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       xM0;

    FCN_M(tgMH_Ortho_OffsetLH_S)( &xM0, TYPE_K(1), TYPE_K(2,0), TYPE_K(3,0), TYPE_K(4,0), TYPE_K(5,0), TYPE_K(6,0) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_Ortho_OffsetRH_S) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_Ortho_OffsetRH_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       xM0;

    FCN_M(tgMH_Ortho_OffsetRH_S)( &xM0, TYPE_K(1), TYPE_K(2,0), TYPE_K(3,0), TYPE_K(4,0), TYPE_K(5,0), TYPE_K(6,0) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_M_UT(tgMH_Ortho_Offset_S) ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_M_UT(tgMH_Ortho_Offset_S) )
{
    VEC_S_T(TEMPLATE__VECTOR_COL)       xM0;

    FCN_M(tgMH_Ortho_Offset_S)( &xM0, TYPE_K(1), TYPE_K(2,0), TYPE_K(3,0), TYPE_K(4,0), TYPE_K(5,0), TYPE_K(6,0) );

    TEST_END_METHOD( KTgS_OK );
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

#undef FCN_M_UT
#undef FCN_UT_1
#undef FCN_UT_2
