/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common [Unit Test] [Test] - Math API [Vector].c_inc
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
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

#if (!VEC_IS_NATIVE && TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE) || VEC_IS_NATIVE /* MACRO_COMPILE_NATIVE_MATRIX_GUARD */

/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- FCN_V_UT(tgMH_SETU) ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_SETU) )
{
    union
    {
        VEC_T(1)                            v;
        VEC_S_T(1)                          vS;
    }                                   uV0;
    VAR_T() TgALIGN(16)                 at1[TEMPLATE__VECTOR_DIM*2];

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM*2; ++uiIndex)
    {
        at1[uiIndex] = (VAR_T())(uiIndex + 1);
    };

    for (TgRSIZE uiStart = 0; uiStart < TEMPLATE__VECTOR_DIM; ++uiStart)
    {
        uV0.v = FCN_V(tgMH_SETU)( at1 + uiStart );

        for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
        {
            Test__Expect_EQ( (VAR_T())(uiStart + uiIndex + 1), uV0.vS.m_aData[uiIndex] );
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_SETA) ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_SETA) )
{
    union
    {
        VEC_T(1)                            v;
        VEC_S_T(1)                          vS;
    }                                   uV0;
    VAR_T() TgALIGN(16)                 at1[TEMPLATE__VECTOR_DIM];
    TgRSIZE                             uiIndex;

    for (uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        at1[uiIndex] = (VAR_T())(uiIndex + 1);
    };

    uV0.v = FCN_V(tgMH_SETA)( at1 );

    for (uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_EQ( (VAR_T())(uiIndex + 1), uV0.vS.m_aData[uiIndex] );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_SET1) -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_SET1) )
{
    union
    {
        VEC_T(1)                            v;
        VEC_S_T(1)                          vS;
    }                                   uV0;
    TgRSIZE                             uiIndex;

    uV0.v = FCN_V(tgMH_SET1)( 3 );

    for (uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_EQ((VAR_T())3, uV0.vS.m_aData[uiIndex]);
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_SEL) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_SEL) )
{
    union
    {
        VEC_T(1)                            v;
        VEC_S_T(1)                          vS;
        TgUINT_E08                          auiM0[sizeof( VEC_T(1) )];
    }                                   uV0, uV1, uV2, uV3;
    TgUINT_E08                          ui08_0;

    for (TgRSIZE ui0 = 0; ui0 < sizeof( VEC_T(1) ); ++ui0)
    {
        uV0.auiM0[ui0] = tgCM_RAND_U08();
        uV1.auiM0[ui0] = tgCM_RAND_U08();
        ui08_0 = tgCM_RAND_U08();
        uV2.auiM0[ui0] = (TgUINT_E08)((ui08_0 & KTgPERM_PARAM_SELECT_BIT) + (ui08_0 % TEMPLATE__VECTOR_DIM));
    };

    uV3.v = FCN_V(tgMH_SEL)( uV0.v, uV1.v, uV2.v );

    for (TgRSIZE ui0 = 0; ui0 < sizeof( VEC_S_T(1) ); ++ui0)
    {
        ui08_0  = (TgUINT_E08)(uV0.auiM0[ui0] & ~uV2.auiM0[ui0]);
        ui08_0 |= uV1.auiM0[ui0] & uV2.auiM0[ui0];
        Test__Expect_EQ( uV3.auiM0[ui0], ui08_0 );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_AND) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_AND) )
{
    union
    {
        VEC_T(1)                            v;
        VEC_S_T(1)                          vS;
        TgUINT_E08                          auiM0[sizeof( VEC_T(1) )];
    }                                   uV0, uV1, uV2;

    for (TgRSIZE ui0 = 0; ui0 < sizeof( VEC_T(1) ); ++ui0)
    {
        uV1.auiM0[ui0] = tgCM_RAND_U08();
        uV2.auiM0[ui0] = tgCM_RAND_U08();
    };

    uV0.v = FCN_V(tgMH_AND)( uV1.v, uV2.v );

    for (TgRSIZE ui0 = 0; ui0 < sizeof( VEC_S_T(1) ); ++ui0)
    {
        Test__Expect_EQ(uV0.auiM0[ui0], uV1.auiM0[ui0] & uV2.auiM0[ui0] );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_OR) ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_OR) )
{
    union
    {
        VEC_T(1)                            v;
        VEC_S_T(1)                          vS;
        TgUINT_E08                          auiM0[sizeof( VEC_T(1) )];
    }                                   uV0, uV1, uV2;

    for (TgRSIZE ui0 = 0; ui0 < sizeof( VEC_T(1) ); ++ui0)
    {
        uV1.auiM0[ui0] = tgCM_RAND_U08();
        uV2.auiM0[ui0] = tgCM_RAND_U08();
    };

    uV0.v = FCN_V(tgMH_OR)( uV1.v, uV2.v );

    for (TgRSIZE ui0 = 0; ui0 < sizeof( VEC_S_T(1) ); ++ui0)
    {
        Test__Expect_EQ(uV0.auiM0[ui0], uV1.auiM0[ui0] | uV2.auiM0[ui0] );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_XOR) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_XOR) )
{
    union
    {
        VEC_T(1)                            v;
        VEC_S_T(1)                          vS;
        TgUINT_E08                          auiM0[sizeof( VEC_T(1) )];
    }                                   uV0, uV1, uV2;

    for (TgRSIZE ui0 = 0; ui0 < sizeof( VEC_T(1) ); ++ui0)
    {
        uV1.auiM0[ui0] = tgCM_RAND_U08();
        uV2.auiM0[ui0] = tgCM_RAND_U08();
    };

    uV0.v = FCN_V(tgMH_XOR)( uV1.v, uV2.v );

    for (TgRSIZE ui0 = 0; ui0 < sizeof( VEC_S_T(1) ); ++ui0)
    {
        Test__Expect_EQ(uV0.auiM0[ui0], uV1.auiM0[ui0] ^ uV2.auiM0[ui0] );
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_MAX) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_MAX) )
{
    union
    {
        VEC_T(1)                            v;
        VEC_S_T(1)                          vS;
    }                                   uV0, uV1, uV2;

    uV0.v = FCN_V(tgMH_SET1)( VAR_K(KTgMIN) );
    uV1.v = FCN_V(tgMH_SET1)( 2 );

    uV2.v = FCN_V(tgMH_MAX)( uV0.v, uV1.v ); /* Test a larger negative number vs a positive value */
    Test__Expect_EQ(0, memcmp( &uV2, &uV1, sizeof( VEC_S_T(1) ) ));

    uV2.v = FCN_V(tgMH_MAX)( uV1.v, uV1.v ); /* Test using the same inputs */
    Test__Expect_EQ(0, memcmp( &uV2, &uV1, sizeof( VEC_S_T(1) ) ));

    uV1.v = FCN_V(tgMH_SET1)( 5 );
    uV2.v = FCN_V(tgMH_MAX)( uV0.v, uV1.v ); /* Re-Test the first case */
    Test__Expect_EQ(0, memcmp( &uV2, &uV1, sizeof( VEC_S_T(1) ) ));

    uV0.v = FCN_V(tgMH_SET1)( 9 );
    uV2.v = FCN_V(tgMH_MAX)( uV0.v, uV1.v ); /* Validate that we are not just returning the second vector */
    Test__Expect_EQ(0, memcmp( &uV2, &uV0, sizeof( VEC_S_T(1) ) ));

    uV0.v = FCN_V(tgMH_SET1)( VAR_K(KTgMIN) + 9 );
    uV1.v = FCN_V(tgMH_SET1)( VAR_K(KTgMIN) + 4 );
    uV2.v = FCN_V(tgMH_MAX)( uV0.v, uV1.v ); /* Test negative values */
    Test__Expect_EQ(0, memcmp( &uV2, &uV0, sizeof( VEC_S_T(1) ) ));

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        uV0.v = FCN_V(tgMH_SET1)(1);
        uV1.v = FCN_V(tgMH_SET1)(1);

        uV1.vS.m_aData[uiIndex] = 0;
        uV2.v = FCN_V(tgMH_MAX)( uV0.v, uV1.v );
        Test__Expect_EQ(0, memcmp( &uV2, &uV0, sizeof( VEC_S_T(1) ) ));

        uV1.vS.m_aData[uiIndex] = 2;
        uV2.v = FCN_V(tgMH_MAX)( uV0.v, uV1.v );
        Test__Expect_EQ(0, memcmp( &uV2, &uV1, sizeof( VEC_S_T(1) ) ));
    };

    uV0.v = FCN_V(tgMH_RAND)();
    uV1.v = FCN_V(tgMH_RAND)();
    uV2.v = FCN_V(tgMH_MAX)( uV0.v, uV1.v ); /* Test random values */

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_EQ( uV2.vS.m_aData[uiIndex], FCN_F(tgCM_MAX)( uV0.vS.m_aData[uiIndex], uV1.vS.m_aData[uiIndex] ));
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_MIN) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_MIN) )
{
    union
    {
        VEC_T(1)                            v;
        VEC_S_T(1)                          vS;
    }                                   uV0, uV1, uV2;

    uV0.v = FCN_V(tgMH_SET1)( VAR_K(KTgMIN) );
    uV1.v = FCN_V(tgMH_SET1)( 2 );

    uV2.v = FCN_V(tgMH_MIN)( uV0.v, uV1.v ); /* Test a larger negative number vs a positive value */
    Test__Expect_EQ(0, memcmp( &uV2, &uV0, sizeof( VEC_S_T(1) ) ));

    uV2.v = FCN_V(tgMH_MIN)( uV1.v, uV1.v ); /* Test using the same inputs */
    Test__Expect_EQ(0, memcmp( &uV2, &uV1, sizeof( VEC_S_T(1) ) ));

    uV1.v = FCN_V(tgMH_SET1)( 5 );
    uV2.v = FCN_V(tgMH_MIN)( uV0.v, uV1.v ); /* Re-Test the first case */
    Test__Expect_EQ(0, memcmp( &uV2, &uV0, sizeof( VEC_S_T(1) ) ));

    uV0.v = FCN_V(tgMH_SET1)( 9 );
    uV2.v = FCN_V(tgMH_MIN)( uV0.v, uV1.v ); /* Validate that we are not just returning the first vector */
    Test__Expect_EQ(0, memcmp( &uV2, &uV1, sizeof( VEC_S_T(1) ) ));

    uV0.v = FCN_V(tgMH_SET1)( VAR_K(KTgMIN) + 9 );
    uV1.v = FCN_V(tgMH_SET1)( VAR_K(KTgMIN) + 4 );
    uV2.v = FCN_V(tgMH_MIN)( uV0.v, uV1.v ); /* Test negative values */
    Test__Expect_EQ(0, memcmp( &uV2, &uV1, sizeof( VEC_S_T(1) ) ));

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        uV0.v = FCN_V(tgMH_SET1)(1);
        uV1.v = FCN_V(tgMH_SET1)(1);

        uV1.vS.m_aData[uiIndex] = 0;
        uV2.v = FCN_V(tgMH_MIN)( uV0.v, uV1.v );
        Test__Expect_EQ(0, memcmp( &uV2, &uV1, sizeof( VEC_S_T(1) ) ));

        uV1.vS.m_aData[uiIndex] = 2;
        uV2.v = FCN_V(tgMH_MIN)( uV0.v, uV1.v );
        Test__Expect_EQ(0, memcmp( &uV2, &uV0, sizeof( VEC_S_T(1) ) ));
    };

    uV0.v = FCN_V(tgMH_RAND)();
    uV1.v = FCN_V(tgMH_RAND)();
    uV2.v = FCN_V(tgMH_MIN)( uV0.v, uV1.v ); /* Test random values */

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_EQ( uV2.vS.m_aData[uiIndex], FCN_F(tgCM_MIN)( uV0.vS.m_aData[uiIndex], uV1.vS.m_aData[uiIndex] ));
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_CMP_EQ) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_CMP_EQ) )
{
    VEC_T(1)                            vV0, vV1, vV2, vV3, vS, vF;

    vV0 = FCN_V(tgMH_SET1)(0);
    vV1 = FCN_V(tgMH_SET1)(1);
    vV2 = FCN_V(tgMH_SET1)(2);

    tgMM_Set_U08_0xFF( &vS, sizeof( VEC_S_T(1) ) );
    tgMM_Set_U08_0x00( &vF, sizeof( VEC_S_T(1) ) );

    vV3 = FCN_V(tgMH_CMP_EQ)( vV0, vV0 ); Test__Expect_EQ(0, memcmp( &vS, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_EQ)( vV0, vV1 ); Test__Expect_EQ(0, memcmp( &vF, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_EQ)( vV0, vV2 ); Test__Expect_EQ(0, memcmp( &vF, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_EQ)( vV1, vV0 ); Test__Expect_EQ(0, memcmp( &vF, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_EQ)( vV1, vV1 ); Test__Expect_EQ(0, memcmp( &vS, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_EQ)( vV1, vV2 ); Test__Expect_EQ(0, memcmp( &vF, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_EQ)( vV2, vV0 ); Test__Expect_EQ(0, memcmp( &vF, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_EQ)( vV2, vV1 ); Test__Expect_EQ(0, memcmp( &vF, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_EQ)( vV2, vV2 ); Test__Expect_EQ(0, memcmp( &vS, &vV3, sizeof( VEC_S_T(1) ) ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_CMP_NE) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_CMP_NE) )
{
    VEC_T(1)                            vV0, vV1, vV2, vV3, vS, vF;

    vV0 = FCN_V(tgMH_SET1)(0);
    vV1 = FCN_V(tgMH_SET1)(1);
    vV2 = FCN_V(tgMH_SET1)(2);

    tgMM_Set_U08_0xFF( &vS, sizeof( VEC_S_T(1) ) );
    tgMM_Set_U08_0x00( &vF, sizeof( VEC_S_T(1) ) );

    vV3 = FCN_V(tgMH_CMP_NE)( vV0, vV0 ); Test__Expect_EQ(0, memcmp( &vF, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_NE)( vV0, vV1 ); Test__Expect_EQ(0, memcmp( &vS, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_NE)( vV0, vV2 ); Test__Expect_EQ(0, memcmp( &vS, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_NE)( vV1, vV0 ); Test__Expect_EQ(0, memcmp( &vS, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_NE)( vV1, vV1 ); Test__Expect_EQ(0, memcmp( &vF, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_NE)( vV1, vV2 ); Test__Expect_EQ(0, memcmp( &vS, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_NE)( vV2, vV0 ); Test__Expect_EQ(0, memcmp( &vS, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_NE)( vV2, vV1 ); Test__Expect_EQ(0, memcmp( &vS, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_NE)( vV2, vV2 ); Test__Expect_EQ(0, memcmp( &vF, &vV3, sizeof( VEC_S_T(1) ) ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_CMP_GE) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_CMP_GE) )
{
    VEC_T(1)                            vV0, vV1, vV2, vV3, vS, vF;

    vV0 = FCN_V(tgMH_SET1)(0);
    vV1 = FCN_V(tgMH_SET1)(1);
    vV2 = FCN_V(tgMH_SET1)(2);

    tgMM_Set_U08_0xFF( &vS, sizeof( VEC_S_T(1) ) );
    tgMM_Set_U08_0x00( &vF, sizeof( VEC_S_T(1) ) );

    vV3 = FCN_V(tgMH_CMP_GE)( vV0, vV0 ); Test__Expect_EQ(0, memcmp( &vS, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_GE)( vV0, vV1 ); Test__Expect_EQ(0, memcmp( &vF, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_GE)( vV0, vV2 ); Test__Expect_EQ(0, memcmp( &vF, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_GE)( vV1, vV0 ); Test__Expect_EQ(0, memcmp( &vS, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_GE)( vV1, vV1 ); Test__Expect_EQ(0, memcmp( &vS, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_GE)( vV1, vV2 ); Test__Expect_EQ(0, memcmp( &vF, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_GE)( vV2, vV0 ); Test__Expect_EQ(0, memcmp( &vS, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_GE)( vV2, vV1 ); Test__Expect_EQ(0, memcmp( &vS, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_GE)( vV2, vV2 ); Test__Expect_EQ(0, memcmp( &vS, &vV3, sizeof( VEC_S_T(1) ) ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_CMP_GT) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_CMP_GT) )
{
    VEC_T(1)                            vV0, vV1, vV2, vV3, vS, vF;

    vV0 = FCN_V(tgMH_SET1)(0);
    vV1 = FCN_V(tgMH_SET1)(1);
    vV2 = FCN_V(tgMH_SET1)(2);

    tgMM_Set_U08_0xFF( &vS, sizeof( VEC_S_T(1) ) );
    tgMM_Set_U08_0x00( &vF, sizeof( VEC_S_T(1) ) );

    vV3 = FCN_V(tgMH_CMP_GT)( vV0, vV0 ); Test__Expect_EQ(0, memcmp( &vF, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_GT)( vV0, vV1 ); Test__Expect_EQ(0, memcmp( &vF, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_GT)( vV0, vV2 ); Test__Expect_EQ(0, memcmp( &vF, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_GT)( vV1, vV0 ); Test__Expect_EQ(0, memcmp( &vS, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_GT)( vV1, vV1 ); Test__Expect_EQ(0, memcmp( &vF, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_GT)( vV1, vV2 ); Test__Expect_EQ(0, memcmp( &vF, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_GT)( vV2, vV0 ); Test__Expect_EQ(0, memcmp( &vS, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_GT)( vV2, vV1 ); Test__Expect_EQ(0, memcmp( &vS, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_GT)( vV2, vV2 ); Test__Expect_EQ(0, memcmp( &vF, &vV3, sizeof( VEC_S_T(1) ) ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_CMP_LE) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_CMP_LE) )
{
    VEC_T(1)                            vV0, vV1, vV2, vV3, vS, vF;

    vV0 = FCN_V(tgMH_SET1)(0);
    vV1 = FCN_V(tgMH_SET1)(1);
    vV2 = FCN_V(tgMH_SET1)(2);

    tgMM_Set_U08_0xFF( &vS, sizeof( VEC_S_T(1) ) );
    tgMM_Set_U08_0x00( &vF, sizeof( VEC_S_T(1) ) );

    vV3 = FCN_V(tgMH_CMP_LE)( vV0, vV0 ); Test__Expect_EQ(0, memcmp( &vS, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_LE)( vV0, vV1 ); Test__Expect_EQ(0, memcmp( &vS, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_LE)( vV0, vV2 ); Test__Expect_EQ(0, memcmp( &vS, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_LE)( vV1, vV0 ); Test__Expect_EQ(0, memcmp( &vF, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_LE)( vV1, vV1 ); Test__Expect_EQ(0, memcmp( &vS, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_LE)( vV1, vV2 ); Test__Expect_EQ(0, memcmp( &vS, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_LE)( vV2, vV0 ); Test__Expect_EQ(0, memcmp( &vF, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_LE)( vV2, vV1 ); Test__Expect_EQ(0, memcmp( &vF, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_LE)( vV2, vV2 ); Test__Expect_EQ(0, memcmp( &vS, &vV3, sizeof( VEC_S_T(1) ) ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_CMP_LT) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_CMP_LT) )
{
    VEC_T(1)                            vV0, vV1, vV2, vV3, vS, vF;

    vV0 = FCN_V(tgMH_SET1)(0);
    vV1 = FCN_V(tgMH_SET1)(1);
    vV2 = FCN_V(tgMH_SET1)(2);

    tgMM_Set_U08_0xFF( &vS, sizeof( VEC_S_T(1) ) );
    tgMM_Set_U08_0x00( &vF, sizeof( VEC_S_T(1) ) );

    vV3 = FCN_V(tgMH_CMP_LT)( vV0, vV0 ); Test__Expect_EQ(0, memcmp( &vF, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_LT)( vV0, vV1 ); Test__Expect_EQ(0, memcmp( &vS, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_LT)( vV0, vV2 ); Test__Expect_EQ(0, memcmp( &vS, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_LT)( vV1, vV0 ); Test__Expect_EQ(0, memcmp( &vF, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_LT)( vV1, vV1 ); Test__Expect_EQ(0, memcmp( &vF, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_LT)( vV1, vV2 ); Test__Expect_EQ(0, memcmp( &vS, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_LT)( vV2, vV0 ); Test__Expect_EQ(0, memcmp( &vF, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_LT)( vV2, vV1 ); Test__Expect_EQ(0, memcmp( &vF, &vV3, sizeof( VEC_S_T(1) ) ));
    vV3 = FCN_V(tgMH_CMP_LT)( vV2, vV2 ); Test__Expect_EQ(0, memcmp( &vF, &vV3, sizeof( VEC_S_T(1) ) ));

    TEST_END_METHOD( KTgS_OK );
}


/* =============================================================================================================================================================================== */

/*# (!VEC_IS_NATIVE && TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE) || VEC_IS_NATIVE */
#endif

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

#undef FCN_M_UT
#undef FCN_UT_1
#undef FCN_UT_2
