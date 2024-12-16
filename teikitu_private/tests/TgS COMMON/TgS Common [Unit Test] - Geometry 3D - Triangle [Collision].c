/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common [Unit Test] - Geometry 3D - Triangle [Collision].c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
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

TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Is_Point_Culled) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Reset_Flags) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Calc_Normal) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Calc_Point) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Reset) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Is_Valid) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Support_Point) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Area) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_BA) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Sweep_BA) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Project) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Is_Contained) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_TX) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Copy_TX) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Init_PN) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Init_P) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Init_EN) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Init_E) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Init_PT) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Init_ET) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Copy) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Set_Origin) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Set_Point_0) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Set_Point_1) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Set_Point_2) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Set_Edge_0) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Set_Edge_1) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Set_Edge_2) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Set_Flags) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Query_Origin) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Query_Normal) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Query_Point_0) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Query_Point_1) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Query_Point_2) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Query_Point) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Query_Edge_0) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Query_Edge_1) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Query_Edge_2) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Query_Edge) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Query_PT) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Query_ET) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Query_Flags) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Set_Test_Point) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Set_Test_Point_0) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Set_Test_Point_1) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Set_Test_Point_2) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Set_Test_Edge) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Set_Test_Edge_0) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Set_Test_Edge_1) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Set_Test_Edge_2) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Test_Point) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Test_Point_0) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Test_Point_1) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Test_Point_2) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Test_Edge) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Test_Edge_0) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Test_Edge_1) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Test_Edge_2) );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TgEXTN TgVOID
FCN_V(UNIT_TEST__SETUP__PT)(
    VEC_OBJ_T(TgPTRI,PCU) );

TgEXTN TgVOID
FCN_V(UNIT_TEST__SETUP__ET)(
    VEC_OBJ_T(TgETRI,PCU) );

TgEXTN TgVOID
FCN_V(UNIT_TEST__SETUP__CT)(
    VEC_OBJ_T(TgCTRI,PCU) );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- FCN_V(UNIT_TEST__TEST__GEOM_CT) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V(UNIT_TEST__TEST__GEOM_CT) )
{
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_CT_Is_Point_Culled)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_CT_Reset_Flags)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_CT_Calc_Normal)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_CT_Calc_Point)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_CT_Reset)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_CT_Is_Valid)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_CT_Support_Point)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_CT_Area)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_CT_BA)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_CT_Sweep_BA)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_CT_Project)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_CT_Is_Contained)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_CT_TX)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_CT_Copy_TX)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_CT_Init_PN)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_CT_Init_P)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_CT_Init_EN)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_CT_Init_E)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_CT_Init_PT)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_CT_Init_ET)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_CT_Copy)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_CT_Set_Origin)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_CT_Set_Point_0)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_CT_Set_Point_1)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_CT_Set_Point_2)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_CT_Set_Edge_0)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_CT_Set_Edge_1)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_CT_Set_Edge_2)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_CT_Set_Flags)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_CT_Query_Origin)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_CT_Query_Normal)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_CT_Query_Point_0)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_CT_Query_Point_1)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_CT_Query_Point_2)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_CT_Query_Point)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_CT_Query_Edge_0)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_CT_Query_Edge_1)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_CT_Query_Edge_2)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_CT_Query_Edge)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_CT_Query_PT)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_CT_Query_ET)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_CT_Query_Flags)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_CT_Set_Test_Point)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_CT_Set_Test_Point_0)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_CT_Set_Test_Point_1)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_CT_Set_Test_Point_2)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_CT_Set_Test_Edge)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_CT_Set_Test_Edge_0)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_CT_Set_Test_Edge_1)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_CT_Set_Test_Edge_2)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_CT_Test_Point)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_CT_Test_Point_0)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_CT_Test_Point_1)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_CT_Test_Point_2)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_CT_Test_Edge)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_CT_Test_Edge_0)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_CT_Test_Edge_1)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_CT_Test_Edge_2)());

    TEST_END_METHOD( KTgS_OK );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- FCN_V(UNIT_TEST__TEST__GM_CT_Is_Point_Culled) ---------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Is_Point_Culled) )
{
    VEC_OBJ_T(TgCTRI)                   sCT0;

    FCN_V(UNIT_TEST__SETUP__CT)( &sCT0 );
    FCN_VO(tgGM_CT_Is_Point_Culled)( &sCT0, FCN_V(tgMH_SET1)( TYPE_K(1) ), FCN_V(tgMH_SET1)( TYPE_K(1) ) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_CT_Reset_Flags) -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Reset_Flags) )
{
    VEC_OBJ_T(TgCTRI)                   sCT0;

    FCN_V(UNIT_TEST__SETUP__CT)( &sCT0 );
    FCN_VO(tgGM_CT_Reset_Flags)( &sCT0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_CT_Calc_Normal) -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Calc_Normal) )
{
    VEC_OBJ_T(TgCTRI)                   sCT0;

    FCN_V(UNIT_TEST__SETUP__CT)( &sCT0 );
    FCN_VO(tgGM_CT_Calc_Normal)( &sCT0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_CT_Calc_Point) --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Calc_Point) )
{
    VEC_OBJ_T(TgCTRI)                   sCT0;

    FCN_V(UNIT_TEST__SETUP__CT)( &sCT0 );
    FCN_VO(tgGM_CT_Calc_Point)( &sCT0, FCN_V(tgMH_SET1)( TYPE_K(1) ), FCN_V(tgMH_SET1)( TYPE_K(1) ) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_CT_Reset) -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Reset) )
{
    VEC_OBJ_T(TgCTRI)                   sCT0;

    FCN_V(UNIT_TEST__SETUP__CT)( &sCT0 );
    FCN_VO(tgGM_CT_Reset)( &sCT0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_CT_Is_Valid) ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Is_Valid) )
{
    VEC_OBJ_T(TgCTRI)                   sCT0;

    FCN_V(UNIT_TEST__SETUP__CT)( &sCT0 );
    Test__Expect_EQ( true, FCN_VO(tgGM_CT_Is_Valid)( &sCT0 ));
    FCN_VO(tgGM_CT_Reset)( &sCT0);
    Test__Expect_EQ(false, FCN_VO(tgGM_CT_Is_Valid)( &sCT0 ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_CT_Support_Point) ------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Support_Point) )
{
    VEC_OBJ_T(TgCTRI)                   sCT0;
    VEC_T(1)                            vV0;

    vV0 = FCN_V(tgMH_Init_Vector_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vV0 = FCN_V(tgMH_NORM)( vV0 );
    FCN_V(UNIT_TEST__SETUP__CT)( &sCT0 );
    FCN_VO(tgGM_CT_Support_Point)( &sCT0, vV0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_CT_Area) --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Area) )
{
    VEC_OBJ_T(TgCTRI)                   sCT0;

    FCN_V(UNIT_TEST__SETUP__CT)( &sCT0 );
    FCN_VO(tgGM_CT_Area)( &sCT0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_CT_BA) ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_BA) )
{
    VEC_OBJ_T(TgCTRI)                   sCT0;
    VEC_OBJ_T(TgBOXAA)                  sBA0;

    FCN_V(UNIT_TEST__SETUP__CT)( &sCT0 );
    FCN_VO(tgGM_CT_BA)( &sBA0, &sCT0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_CT_Sweep_BA) ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Sweep_BA) )
{
    VEC_OBJ_T(TgCTRI)                   sCT0;
    VEC_OBJ_T(TgBOXAA)                  sBA0;
    VEC_T(1)                            vV0;

    vV0 = FCN_V(tgMH_Init_Vector_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vV0 = FCN_V(tgMH_NORM)( vV0 );
    FCN_V(UNIT_TEST__SETUP__CT)( &sCT0 );
    FCN_VO(tgGM_CT_Sweep_BA)( &sBA0, &sCT0, vV0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_CT_Project) ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Project) )
{
    VEC_OBJ_T(TgCTRI)                   sCT0;
    VEC_T(1)                            vV0, vVal;

    vV0 = FCN_V(tgMH_Init_Vector_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vV0 = FCN_V(tgMH_NORM)( vV0 );
    FCN_V(UNIT_TEST__SETUP__CT)( &sCT0 );
    FCN_VO(tgGM_CT_Project)( &vVal, &vVal, &sCT0, vV0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_CT_Is_Contained) ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Is_Contained) )
{
    VEC_OBJ_T(TgCTRI)                   sCT0;
    VEC_T(1)                            vS0;

    vS0 = FCN_V(tgMH_Init_Point_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    FCN_V(UNIT_TEST__SETUP__CT)( &sCT0 );
    FCN_VO(tgGM_CT_Is_Contained)( &sCT0, vS0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_CT_TX) ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_TX) )
{
    VEC_OBJ_T(TgCTRI)                   sCT0;
    VEC_T(3)                            xM0;

    FCN_V(tgMH_CLI,3)( &xM0 );
    FCN_V(UNIT_TEST__SETUP__CT)( &sCT0 );
    FCN_VO(tgGM_CT_TX)( &sCT0, &xM0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_CT_Copy_TX) ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Copy_TX) )
{
    VEC_OBJ_T(TgCTRI)                   sCT0;
    VEC_T(3)                            xM0;

    FCN_V(tgMH_CLI,3)( &xM0 );
    FCN_V(UNIT_TEST__SETUP__CT)( &sCT0 );
    FCN_VO(tgGM_CT_Copy_TX)( &sCT0, &sCT0, &xM0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_CT_Init_PN) ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Init_PN) )
{
    VEC_OBJ_T(TgCTRI)                   sCT0;
    VEC_T(1)                            vS0, vS1, vS2, vE0, vE1, vNM;

    vS0 = FCN_V(tgMH_Init_Point_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vS1 = FCN_V(tgMH_Init_Point_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vS2 = FCN_V(tgMH_Init_Point_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );

    vE0 = FCN_V(tgMH_SUB)( vS1, vS0 );
    vE1 = FCN_V(tgMH_SUB)( vS2, vS0 );
    vNM = FCN_V(tgMH_UCX)( vE0, vE1 );

    FCN_VO(tgGM_CT_Init_PN)( &sCT0, vS0, vS1, vS2, vNM );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_CT_Init_P) ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Init_P) )
{
    VEC_OBJ_T(TgCTRI)                   sCT0;
    VEC_T(1)                            vS0, vS1, vS2;

    vS0 = FCN_V(tgMH_Init_Point_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vS1 = FCN_V(tgMH_Init_Point_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vS2 = FCN_V(tgMH_Init_Point_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    FCN_VO(tgGM_CT_Init_P)( &sCT0, vS0, vS1, vS2 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_CT_Init_EN) ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Init_EN) )
{
    VEC_OBJ_T(TgCTRI)                   sCT0;
    VEC_T(1)                            vS0, vV0, vV1, vNM;

    vS0 = FCN_V(tgMH_Init_Point_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vV0 = FCN_V(tgMH_Init_Vector_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vV0 = FCN_V(tgMH_NORM)( vV0 );
    vV1 = FCN_V(tgMH_Init_Vector_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vV1 = FCN_V(tgMH_NORM)( vV1 );
    vNM = FCN_V(tgMH_UCX)( vV0, vV1 );
    FCN_VO(tgGM_CT_Init_EN)( &sCT0, vS0, vV0, vV1, vNM );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_CT_Init_E) ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Init_E) )
{
    VEC_OBJ_T(TgCTRI)                   sCT0;
    VEC_T(1)                            vS0, vV0, vV1;

    vS0 = FCN_V(tgMH_Init_Point_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vV0 = FCN_V(tgMH_Init_Vector_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vV0 = FCN_V(tgMH_NORM)( vV0 );
    vV1 = FCN_V(tgMH_Init_Vector_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vV1 = FCN_V(tgMH_NORM)( vV1 );
    FCN_VO(tgGM_CT_Init_E)( &sCT0, vS0, vV0, vV1 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_CT_Init_PT) ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Init_PT) )
{
    VEC_OBJ_T(TgCTRI)                   sCT0;
    VEC_OBJ_T(TgPTRI)                   sPT0;

    FCN_V(UNIT_TEST__SETUP__PT)( &sPT0 );
    FCN_VO(tgGM_CT_Init_PT)( &sCT0, &sPT0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_CT_Init_ET) ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Init_ET) )
{
    VEC_OBJ_T(TgCTRI)                   sCT0;
    VEC_OBJ_T(TgETRI)                   sET0;

    FCN_V(UNIT_TEST__SETUP__ET)( &sET0 );
    FCN_VO(tgGM_CT_Init_ET)( &sCT0, &sET0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_CT_Copy) --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Copy) )
{
    VEC_OBJ_T(TgCTRI)                   sCT0;

    FCN_V(UNIT_TEST__SETUP__CT)( &sCT0 );
    FCN_VO(tgGM_CT_Copy)( &sCT0, &sCT0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_CT_Set_Origin) --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Set_Origin) )
{
    VEC_OBJ_T(TgCTRI)                   sCT0;
    VEC_T(1)                            vS0;

    vS0 = FCN_V(tgMH_Init_Point_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    FCN_V(UNIT_TEST__SETUP__CT)( &sCT0 );
    FCN_VO(tgGM_CT_Set_Origin)( &sCT0, vS0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_CT_Set_Point_0) -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Set_Point_0) )
{
    VEC_OBJ_T(TgCTRI)                   sCT0;
    VEC_T(1)                            vS0;

    vS0 = FCN_V(tgMH_Init_Point_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    FCN_V(UNIT_TEST__SETUP__CT)( &sCT0 );
    FCN_VO(tgGM_CT_Set_Point_0)( &sCT0, vS0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_CT_Set_Point_1) -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Set_Point_1) )
{
    VEC_OBJ_T(TgCTRI)                   sCT0;
    VEC_T(1)                            vS0;

    vS0 = FCN_V(tgMH_Init_Point_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    FCN_V(UNIT_TEST__SETUP__CT)( &sCT0 );
    FCN_VO(tgGM_CT_Set_Point_1)( &sCT0, vS0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_CT_Set_Point_2) -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Set_Point_2) )
{
    VEC_OBJ_T(TgCTRI)                   sCT0;
    VEC_T(1)                            vS0;

    vS0 = FCN_V(tgMH_Init_Point_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    FCN_V(UNIT_TEST__SETUP__CT)( &sCT0 );
    FCN_VO(tgGM_CT_Set_Point_2)( &sCT0, vS0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_CT_Set_Edge_0) --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Set_Edge_0) )
{
    VEC_OBJ_T(TgCTRI)                   sCT0;

    FCN_V(UNIT_TEST__SETUP__CT)( &sCT0 );
    FCN_VO(tgGM_CT_Set_Edge_0)( &sCT0, sCT0.m_sET.m_avEdge[0] ); /**< Point 0 to Point 1; */

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_CT_Set_Edge_1) --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Set_Edge_1) )
{
    VEC_OBJ_T(TgCTRI)                   sCT0;

    FCN_V(UNIT_TEST__SETUP__CT)( &sCT0 );
    FCN_VO(tgGM_CT_Set_Edge_1)( &sCT0, sCT0.m_sET.m_avEdge[1] ); /**< Point 1 to Point 2; */

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_CT_Set_Edge_2) --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Set_Edge_2) )
{
    VEC_OBJ_T(TgCTRI)                   sCT0;

    FCN_V(UNIT_TEST__SETUP__CT)( &sCT0 );
    FCN_VO(tgGM_CT_Set_Edge_2)( &sCT0, sCT0.m_sET.m_avEdge[2] ); /**< Point 2 to Point 0; */

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_CT_Set_Flags) ---------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Set_Flags) )
{
    VEC_OBJ_T(TgCTRI)                   sCT0;

    FCN_V(UNIT_TEST__SETUP__CT)( &sCT0 );
    FCN_VO(tgGM_CT_Set_Flags)( &sCT0, 0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_CT_Query_Origin) ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Query_Origin) )
{
    VEC_OBJ_T(TgCTRI)                   sCT0;

    FCN_V(UNIT_TEST__SETUP__CT)( &sCT0 );
    FCN_VO(tgGM_CT_Query_Origin)( &sCT0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_CT_Query_Normal) ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Query_Normal) )
{
    VEC_OBJ_T(TgCTRI)                   sCT0;

    FCN_V(UNIT_TEST__SETUP__CT)( &sCT0 );
    FCN_VO(tgGM_CT_Query_Normal)( &sCT0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_CT_Query_Point_0) ------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Query_Point_0) )
{
    VEC_OBJ_T(TgCTRI)                   sCT0;

    FCN_V(UNIT_TEST__SETUP__CT)( &sCT0 );
    FCN_VO(tgGM_CT_Query_Point_0)( &sCT0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_CT_Query_Point_1) ------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Query_Point_1) )
{
    VEC_OBJ_T(TgCTRI)                   sCT0;

    FCN_V(UNIT_TEST__SETUP__CT)( &sCT0 );
    FCN_VO(tgGM_CT_Query_Point_1)( &sCT0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_CT_Query_Point_2) ------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Query_Point_2) )
{
    VEC_OBJ_T(TgCTRI)                   sCT0;

    FCN_V(UNIT_TEST__SETUP__CT)( &sCT0 );
    FCN_VO(tgGM_CT_Query_Point_2)( &sCT0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_CT_Query_Point) -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Query_Point) )
{
    VEC_OBJ_T(TgCTRI)                   sCT0;

    FCN_V(UNIT_TEST__SETUP__CT)( &sCT0 );
    FCN_VO(tgGM_CT_Query_Point)( &sCT0, 0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_CT_Query_Edge_0) ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Query_Edge_0) )
{
    VEC_OBJ_T(TgCTRI)                   sCT0;

    FCN_V(UNIT_TEST__SETUP__CT)( &sCT0 );
    FCN_VO(tgGM_CT_Query_Edge_0)( &sCT0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_CT_Query_Edge_1) ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Query_Edge_1) )
{
    VEC_OBJ_T(TgCTRI)                   sCT0;

    FCN_V(UNIT_TEST__SETUP__CT)( &sCT0 );
    FCN_VO(tgGM_CT_Query_Edge_1)( &sCT0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_CT_Query_Edge_2) ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Query_Edge_2) )
{
    VEC_OBJ_T(TgCTRI)                   sCT0;

    FCN_V(UNIT_TEST__SETUP__CT)( &sCT0 );
    FCN_VO(tgGM_CT_Query_Edge_2)( &sCT0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_CT_Query_Edge) --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Query_Edge) )
{
    VEC_OBJ_T(TgCTRI)                   sCT0;

    FCN_V(UNIT_TEST__SETUP__CT)( &sCT0 );
    FCN_VO(tgGM_CT_Query_Edge)( &sCT0, 0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_CT_Query_PT) ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Query_PT) )
{
    VEC_OBJ_T(TgCTRI)                   sCT0;

    FCN_V(UNIT_TEST__SETUP__CT)( &sCT0 );
    FCN_VO(tgGM_PT_CT_Query)( &sCT0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_CT_Query_ET) ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Query_ET) )
{
    VEC_OBJ_T(TgCTRI)                   sCT0;

    FCN_V(UNIT_TEST__SETUP__CT)( &sCT0 );
    FCN_VO(tgGM_ET_CT_Query)( &sCT0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_CT_Query_Flags) -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Query_Flags) )
{
    VEC_OBJ_T(TgCTRI)                   sCT0;

    FCN_V(UNIT_TEST__SETUP__CT)( &sCT0 );
    FCN_VO(tgGM_CT_Query_Flags)( &sCT0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_CT_Set_Test_Point) ----------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Set_Test_Point) )
{
    VEC_OBJ_T(TgCTRI)                   sCT0;

    FCN_V(UNIT_TEST__SETUP__CT)( &sCT0 );
    FCN_VO(tgGM_CT_Set_Test_Point)( &sCT0, 0, false );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_CT_Set_Test_Point_0) --------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Set_Test_Point_0) )
{
    VEC_OBJ_T(TgCTRI)                   sCT0;

    FCN_V(UNIT_TEST__SETUP__CT)( &sCT0 );
    FCN_VO(tgGM_CT_Set_Test_Point_0)( &sCT0, false );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_CT_Set_Test_Point_1) --------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Set_Test_Point_1) )
{
    VEC_OBJ_T(TgCTRI)                   sCT0;

    FCN_V(UNIT_TEST__SETUP__CT)( &sCT0 );
    FCN_VO(tgGM_CT_Set_Test_Point_1)( &sCT0, false );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_CT_Set_Test_Point_2) --------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Set_Test_Point_2) )
{
    VEC_OBJ_T(TgCTRI)                   sCT0;

    FCN_V(UNIT_TEST__SETUP__CT)( &sCT0 );
    FCN_VO(tgGM_CT_Set_Test_Point_2)( &sCT0, false );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_CT_Set_Test_Edge) ------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Set_Test_Edge) )
{
    VEC_OBJ_T(TgCTRI)                   sCT0;

    FCN_V(UNIT_TEST__SETUP__CT)( &sCT0 );
    FCN_VO(tgGM_CT_Set_Test_Edge)( &sCT0, 0, false );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_CT_Set_Test_Edge_0) ---------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Set_Test_Edge_0) )
{
    VEC_OBJ_T(TgCTRI)                   sCT0;

    FCN_V(UNIT_TEST__SETUP__CT)( &sCT0 );
    FCN_VO(tgGM_CT_Set_Test_Edge_0)( &sCT0, false ); /**< Point 0 to Point 1; */

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_CT_Set_Test_Edge_1) ---------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Set_Test_Edge_1) )
{
    VEC_OBJ_T(TgCTRI)                   sCT0;

    FCN_V(UNIT_TEST__SETUP__CT)( &sCT0 );
    FCN_VO(tgGM_CT_Set_Test_Edge_1)( &sCT0, false ); /**< Point 0 to Point 2; */

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_CT_Set_Test_Edge_2) ---------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Set_Test_Edge_2) )
{
    VEC_OBJ_T(TgCTRI)                   sCT0;

    FCN_V(UNIT_TEST__SETUP__CT)( &sCT0 );
    FCN_VO(tgGM_CT_Set_Test_Edge_2)( &sCT0, false ); /**< Point 1 to Point 2; */

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_CT_Test_Point) --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Test_Point) )
{
    VEC_OBJ_T(TgCTRI)                   sCT0;

    FCN_V(UNIT_TEST__SETUP__CT)( &sCT0 );
    FCN_VO(tgGM_CT_Test_Point)( &sCT0, 0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_CT_Test_Point_0) ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Test_Point_0) )
{
    VEC_OBJ_T(TgCTRI)                   sCT0;

    FCN_V(UNIT_TEST__SETUP__CT)( &sCT0 );
    FCN_VO(tgGM_CT_Test_Point_0)( &sCT0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_CT_Test_Point_1) ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Test_Point_1) )
{
    VEC_OBJ_T(TgCTRI)                   sCT0;

    FCN_V(UNIT_TEST__SETUP__CT)( &sCT0 );
    FCN_VO(tgGM_CT_Test_Point_1)( &sCT0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_CT_Test_Point_2) ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Test_Point_2) )
{
    VEC_OBJ_T(TgCTRI)                   sCT0;

    FCN_V(UNIT_TEST__SETUP__CT)( &sCT0 );
    FCN_VO(tgGM_CT_Test_Point_2)( &sCT0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_CT_Test_Edge) ---------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Test_Edge) )
{
    VEC_OBJ_T(TgCTRI)                   sCT0;

    FCN_V(UNIT_TEST__SETUP__CT)( &sCT0 );
    FCN_VO(tgGM_CT_Test_Edge)( &sCT0, 0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_CT_Test_Edge_0) -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Test_Edge_0) )
{
    VEC_OBJ_T(TgCTRI)                   sCT0;

    FCN_V(UNIT_TEST__SETUP__CT)( &sCT0 );
    FCN_VO(tgGM_CT_Test_Edge_0)( &sCT0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_CT_Test_Edge_1) -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Test_Edge_1) )
{
    VEC_OBJ_T(TgCTRI)                   sCT0;

    FCN_V(UNIT_TEST__SETUP__CT)( &sCT0 );
    FCN_VO(tgGM_CT_Test_Edge_1)( &sCT0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_CT_Test_Edge_2) -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_CT_Test_Edge_2) )
{
    VEC_OBJ_T(TgCTRI)                   sCT0;

    FCN_V(UNIT_TEST__SETUP__CT)( &sCT0 );
    FCN_VO(tgGM_CT_Test_Edge_2)( &sCT0 );

    TEST_END_METHOD( KTgS_OK );
}



/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TgVOID FCN_V(UNIT_TEST__SETUP__CT)( VEC_OBJ_T(TgCTRI,PCU) psCT )
{
    VEC_T(1)                            vS0, vS1, vS2, vE0, vE1, vNM;

    vS0 = FCN_V(tgMH_Init_Point_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vS1 = FCN_V(tgMH_Init_Point_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vS2 = FCN_V(tgMH_Init_Point_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );

    vE0 = FCN_V(tgMH_SUB)( vS1, vS0 );
    vE1 = FCN_V(tgMH_SUB)( vS2, vS0 );
    vNM = FCN_V(tgMH_UCX)( vE0, vE1 );

    FCN_VO(tgGM_CT_Init_PN)( psCT, vS0, vS1, vS2, vNM );
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
