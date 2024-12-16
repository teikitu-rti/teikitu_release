/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common [Unit Test] - Geometry 3D - Tube.c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#if !defined (TEMPLATE_TYPE_EXPANSION__RELOAD)
    #define TEMPLATE_TYPE_EXPANSION__RELOAD

    #if TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE
        #define TEMPLATE__VECTOR_DIM 4
        #define TEMPLATE__TYPE_SIZE 64
        #include __FILE__
    #endif

    #define TEMPLATE__VECTOR_DIM 4
    #define TEMPLATE__TYPE_SIZE 32

    #undef TEMPLATE_TYPE_EXPANSION__RELOAD
#endif


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_TB_Reset) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_TB_Is_Valid) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_TB_TX) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_TB_Copy_TX) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_TB_Init) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_TB_Copy) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_TB_Set_Reference_Frame) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_TB_Set_Origin) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_TB_Set_Extent) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_TB_Set_Radius) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_TB_Query_Origin) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_TB_Query_Half_Axis) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_TB_Query_Segment) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_TB_Query_Axis_Unit) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_TB_Query_Basis_Unit_0) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_TB_Query_Basis_Unit_1) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_TB_Query_Extent) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_TB_Query_Radius) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_TB_Query_Radius_Sq) );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

static TgVOID                               FCN_V(UNIT_TEST__SETUP__TB)( VEC_OBJ_T(TgTUBE,PCU) );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- FCN_V(UNIT_TEST__TEST__GEOM_TB) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V(UNIT_TEST__TEST__GEOM_TB) )
{
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_TB_Reset)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_TB_Is_Valid)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_TB_TX)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_TB_Copy_TX)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_TB_Init)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_TB_Copy)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_TB_Set_Reference_Frame)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_TB_Set_Origin)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_TB_Set_Extent)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_TB_Set_Radius)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_TB_Query_Origin)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_TB_Query_Half_Axis)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_TB_Query_Segment)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_TB_Query_Axis_Unit)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_TB_Query_Basis_Unit_0)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_TB_Query_Basis_Unit_1)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_TB_Query_Extent)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_TB_Query_Radius)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_TB_Query_Radius_Sq)());

    TEST_END_METHOD( KTgS_OK );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- FCN_V(UNIT_TEST__TEST__GM_TB_Reset) -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_TB_Reset) )
{
    VEC_OBJ_T(TgTUBE)                   sTB0;

    FCN_V(UNIT_TEST__SETUP__TB)( &sTB0 );
    FCN_VO(tgGM_TB_Reset)( &sTB0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_TB_Is_Valid) ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_TB_Is_Valid) )
{
    VEC_OBJ_T(TgTUBE)                   sTB0;

    FCN_V(UNIT_TEST__SETUP__TB)( &sTB0 );
    Test__Expect_EQ( true, FCN_VO(tgGM_TB_Is_Valid)( &sTB0 ));
    FCN_VO(tgGM_TB_Reset)( &sTB0 );
    Test__Expect_EQ(false, FCN_VO(tgGM_TB_Is_Valid)( &sTB0 ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_TB_TX) ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_TB_TX) )
{
    VEC_OBJ_T(TgTUBE)                   sTB0;
    VEC_T(3)                            mM0;

    FCN_V(tgMH_CLI,3)( &mM0 );
    FCN_V(UNIT_TEST__SETUP__TB)( &sTB0 );
    FCN_VO(tgGM_TB_TX)( &sTB0, &mM0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_TB_Copy_TX) ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_TB_Copy_TX) )
{
    VEC_OBJ_T(TgTUBE)                   sTB0;
    VEC_T(3)                            mM0;

    FCN_V(tgMH_CLI,3)( &mM0 );
    FCN_V(UNIT_TEST__SETUP__TB)( &sTB0 );
    FCN_VO(tgGM_TB_Copy_TX)( &sTB0, &sTB0, &mM0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_TB_Init) --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_TB_Init) )
{
    VEC_OBJ_T(TgTUBE)                   sTB0;
    VEC_T(3)                            mM0;

    FCN_V(tgMH_CLI,3)( &mM0 );
    FCN_VO(tgGM_TB_Init)( &sTB0, &mM0, FCN_V(tgMH_SET1)( TYPE_K(1) ), FCN_V(tgMH_SET1)( TYPE_K(1) ) );
    Test__Expect_EQ(true, FCN_VO(tgGM_TB_Is_Valid)( &sTB0 ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_TB_Copy) --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_TB_Copy) )
{
    VEC_OBJ_T(TgTUBE)                   sTB0;

    FCN_V(UNIT_TEST__SETUP__TB)( &sTB0 );
    FCN_VO(tgGM_TB_Copy)( &sTB0, &sTB0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_TB_Set_Reference_Frame) ------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_TB_Set_Reference_Frame) )
{
    VEC_OBJ_T(TgTUBE)                   sTB0;
    VEC_T(3)                            mM0;

    FCN_V(tgMH_CLI,3)( &mM0 );
    FCN_V(UNIT_TEST__SETUP__TB)( &sTB0 );
    FCN_VO(tgGM_TB_Set_Reference_Frame)( &sTB0, &mM0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_TB_Set_Origin) --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_TB_Set_Origin) )
{
    VEC_OBJ_T(TgTUBE)                   sTB0;
    VEC_T(1)                            vS0;

    vS0 = FCN_V(tgMH_Init_Point_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    FCN_V(UNIT_TEST__SETUP__TB)( &sTB0 );
    FCN_VO(tgGM_TB_Set_Origin)( &sTB0, vS0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_TB_Set_Extent) --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_TB_Set_Extent) )
{
    VEC_OBJ_T(TgTUBE)                   sTB0;

    FCN_V(UNIT_TEST__SETUP__TB)( &sTB0 );
    FCN_VO(tgGM_TB_Set_Extent)( &sTB0, FCN_V(tgMH_SET1)( TYPE_K(1) ) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_TB_Set_Radius) --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_TB_Set_Radius) )
{
    VEC_OBJ_T(TgTUBE)                   sTB0;

    FCN_V(UNIT_TEST__SETUP__TB)( &sTB0 );
    FCN_VO(tgGM_TB_Set_Radius)( &sTB0, FCN_V(tgMH_SET1)( TYPE_K(1) ) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_TB_Query_Origin) ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_TB_Query_Origin) )
{
    VEC_OBJ_T(TgTUBE)                   sTB0;

    FCN_V(UNIT_TEST__SETUP__TB)( &sTB0 );
    FCN_VO(tgGM_TB_Query_Origin)( &sTB0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_TB_Query_Half_Axis) ---------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_TB_Query_Half_Axis) )
{
    VEC_OBJ_T(TgTUBE)                   sTB0;

    FCN_V(UNIT_TEST__SETUP__TB)( &sTB0 );
    FCN_VO(tgGM_TB_Query_Half_Axis)( &sTB0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_TB_Query_Segment) ------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_TB_Query_Segment) )
{
    VEC_OBJ_T(TgTUBE)                   sTB0;

    FCN_V(UNIT_TEST__SETUP__TB)( &sTB0 );
    FCN_VO(tgGM_TB_Query_Segment)( &sTB0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_TB_Query_Axis_Unit) ---------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_TB_Query_Axis_Unit) )
{
    VEC_OBJ_T(TgTUBE)                   sTB0;

    FCN_V(UNIT_TEST__SETUP__TB)( &sTB0 );
    FCN_VO(tgGM_TB_Query_Axis_Unit)( &sTB0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_TB_Query_Basis_Unit_0) ------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_TB_Query_Basis_Unit_0) )
{
    VEC_OBJ_T(TgTUBE)                   sTB0;

    FCN_V(UNIT_TEST__SETUP__TB)( &sTB0 );
    FCN_VO(tgGM_TB_Query_Basis_Unit_0)( &sTB0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_TB_Query_Basis_Unit_1) ------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_TB_Query_Basis_Unit_1) )
{
    VEC_OBJ_T(TgTUBE)                   sTB0;

    FCN_V(UNIT_TEST__SETUP__TB)( &sTB0 );
    FCN_VO(tgGM_TB_Query_Basis_Unit_1)( &sTB0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_TB_Query_Extent) ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_TB_Query_Extent) )
{
    VEC_OBJ_T(TgTUBE)                   sTB0;

    FCN_V(UNIT_TEST__SETUP__TB)( &sTB0 );
    FCN_VO(tgGM_TB_Query_Extent)( &sTB0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_TB_Query_Radius) ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_TB_Query_Radius) )
{
    VEC_OBJ_T(TgTUBE)                   sTB0;

    FCN_V(UNIT_TEST__SETUP__TB)( &sTB0 );
    FCN_VO(tgGM_TB_Query_Radius)( &sTB0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_TB_Query_Radius_Sq) ---------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_TB_Query_Radius_Sq) )
{
    VEC_OBJ_T(TgTUBE)                   sTB0;

    FCN_V(UNIT_TEST__SETUP__TB)( &sTB0 );
    FCN_VO(tgGM_TB_Query_Radius_Sq)( &sTB0 );

    TEST_END_METHOD( KTgS_OK );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

static TgVOID FCN_V(UNIT_TEST__SETUP__TB)( VEC_OBJ_T(TgTUBE,PCU) psTB )
{
    VEC_T(3)                            mM0;

    FCN_V(tgMH_CLI,3)( &mM0 );
    FCN_VO(tgGM_TB_Init)( psTB, &mM0, FCN_V(tgMH_SET1)( TYPE_K(2) ), FCN_V(tgMH_SET1)( TYPE_K(1) ) );
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
