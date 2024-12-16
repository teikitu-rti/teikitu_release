/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common [Unit Test] - Geometry 3D - Triangle [Edge].c
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

TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Calc_Normal) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Calc_Point) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Reset) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Is_Valid) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Support_Point) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Area) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_BA) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Sweep_BA) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Project) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Is_Contained) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_TX) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Copy_TX) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Init_PN) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Init_P) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Init_EN) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Init_E) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PT_ET_Init) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Copy) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Set_Origin) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Set_Point_0) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Set_Point_1) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Set_Point_2) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Set_Edge_0) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Set_Edge_1) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Set_Edge_2) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Query_Origin) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Query_Normal) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Query_Point_0) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Query_Point_1) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Query_Point_2) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Query_Point) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Query_Edge_0) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Query_Edge_1) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Query_Edge_2) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Query_Edge) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Query_PT) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Is_Tri_Edge_Ignored) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Is_Tri_Edge_Ignored_Code) );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TgEXTN TgVOID
FCN_V(UNIT_TEST__SETUP__PT)(
    VEC_OBJ_T(TgPTRI,PCU) );

TgEXTN TgVOID
FCN_V(UNIT_TEST__SETUP__ET)(
    VEC_OBJ_T(TgETRI,PCU) );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- FCN_V(UNIT_TEST__TEST__GEOM_ET) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V(UNIT_TEST__TEST__GEOM_ET) )
{
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_ET_Calc_Normal)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_ET_Calc_Point)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_ET_Reset)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_ET_Is_Valid)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_ET_Support_Point)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_ET_Area)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_ET_BA)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_ET_Sweep_BA)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_ET_Project)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_ET_Is_Contained)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_ET_TX)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_ET_Copy_TX)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_ET_Init_PN)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_ET_Init_P)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_ET_Init_EN)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_ET_Init_E)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_PT_ET_Init)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_ET_Copy)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_ET_Set_Origin)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_ET_Set_Point_0)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_ET_Set_Point_1)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_ET_Set_Point_2)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_ET_Set_Edge_0)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_ET_Set_Edge_1)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_ET_Set_Edge_2)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_ET_Query_Origin)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_ET_Query_Normal)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_ET_Query_Point_0)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_ET_Query_Point_1)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_ET_Query_Point_2)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_ET_Query_Point)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_ET_Query_Edge_0)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_ET_Query_Edge_1)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_ET_Query_Edge_2)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_ET_Query_Edge)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_ET_Query_PT)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_ET_Is_Tri_Edge_Ignored)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_ET_Is_Tri_Edge_Ignored_Code)());

    TEST_END_METHOD( KTgS_OK );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- FCN_V(UNIT_TEST__TEST__GM_ET_Calc_Normal) -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Calc_Normal) )
{
    VEC_OBJ_T(TgETRI)                   sET0;

    FCN_V(UNIT_TEST__SETUP__ET)( &sET0 );
    FCN_VO(tgGM_ET_Calc_Normal)( &sET0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_ET_Calc_Point) --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Calc_Point) )
{
    VEC_OBJ_T(TgETRI)                   sET0;

    FCN_V(UNIT_TEST__SETUP__ET)( &sET0 );
    FCN_VO(tgGM_ET_Calc_Point)( &sET0, FCN_V(tgMH_SET1)( TYPE_K(1) ), FCN_V(tgMH_SET1)( TYPE_K(1) ) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_ET_Reset) -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Reset) )
{
    VEC_OBJ_T(TgETRI)                   sET0;

    FCN_V(UNIT_TEST__SETUP__ET)( &sET0 );
    FCN_VO(tgGM_ET_Reset)( &sET0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_ET_Is_Valid) ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Is_Valid) )
{
    VEC_OBJ_T(TgETRI)                   sET0;

    FCN_V(UNIT_TEST__SETUP__ET)( &sET0 );
    Test__Expect_EQ( true, FCN_VO(tgGM_ET_Is_Valid)( &sET0 ));
    FCN_VO(tgGM_ET_Reset)( &sET0 );
    Test__Expect_EQ(false, FCN_VO(tgGM_ET_Is_Valid)( &sET0 ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_ET_Support_Point) ------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Support_Point) )
{
    VEC_OBJ_T(TgETRI)                   sET0;
    VEC_T(1)                            vV0;

    vV0 = FCN_V(tgMH_Init_Vector_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vV0 = FCN_V(tgMH_NORM)( vV0 );
    FCN_V(UNIT_TEST__SETUP__ET)( &sET0 );
    FCN_VO(tgGM_ET_Support_Point)( &sET0, vV0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_ET_Area) --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Area) )
{
    VEC_OBJ_T(TgETRI)                   sET0;

    FCN_V(UNIT_TEST__SETUP__ET)( &sET0 );
    FCN_VO(tgGM_ET_Area)( &sET0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_ET_BA) ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_BA) )
{
    VEC_OBJ_T(TgETRI)                   sET0;
    VEC_OBJ_T(TgBOXAA)                  sBA0;

    FCN_V(UNIT_TEST__SETUP__ET)( &sET0 );
    FCN_VO(tgGM_ET_BA)( &sBA0, &sET0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_ET_Sweep_BA) ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Sweep_BA) )
{
    VEC_OBJ_T(TgETRI)                   sET0;
    VEC_OBJ_T(TgBOXAA)                  sBA0;
    VEC_T(1)                            vV0;

    vV0 = FCN_V(tgMH_Init_Vector_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vV0 = FCN_V(tgMH_NORM)( vV0 );
    FCN_V(UNIT_TEST__SETUP__ET)( &sET0 );
    FCN_VO(tgGM_ET_Sweep_BA)( &sBA0, &sET0, vV0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_ET_Project) ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Project) )
{
    VEC_OBJ_T(TgETRI)                   sET0;
    VEC_T(1)                            vV0, vVal;

    vV0 = FCN_V(tgMH_Init_Vector_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vV0 = FCN_V(tgMH_NORM)( vV0 );
    FCN_V(UNIT_TEST__SETUP__ET)( &sET0 );
    FCN_VO(tgGM_ET_Project)( &vVal, &vVal, &sET0, vV0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_ET_Is_Contained) ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Is_Contained) )
{
    VEC_OBJ_T(TgETRI)                   sET0;
    VEC_T(1)                            vS0;

    vS0 = FCN_V(tgMH_Init_Point_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    FCN_V(UNIT_TEST__SETUP__ET)( &sET0 );
    FCN_VO(tgGM_ET_Is_Contained)( &sET0, vS0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_ET_TX) ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_TX) )
{
    VEC_OBJ_T(TgETRI)                   sET0;
    VEC_T(3)                            xM0;

    FCN_V(tgMH_CLI,3)( &xM0 );
    FCN_V(UNIT_TEST__SETUP__ET)( &sET0 );
    FCN_VO(tgGM_ET_TX)( &sET0, &xM0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_ET_Copy_TX) ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Copy_TX) )
{
    VEC_OBJ_T(TgETRI)                   sET0;
    VEC_T(3)                            xM0;

    FCN_V(tgMH_CLI,3)( &xM0 );
    FCN_V(UNIT_TEST__SETUP__ET)( &sET0 );
    FCN_VO(tgGM_ET_Copy_TX)( &sET0, &sET0, &xM0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_ET_Init_PN) ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Init_PN) )
{
    VEC_OBJ_T(TgETRI)                   sET0;
    VEC_T(1)                            vS0, vS1, vS2, vE0, vE1, vNM;

    vS0 = FCN_V(tgMH_Init_Point_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vS1 = FCN_V(tgMH_Init_Point_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vS2 = FCN_V(tgMH_Init_Point_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );

    vE0 = FCN_V(tgMH_SUB)( vS1, vS0 );
    vE1 = FCN_V(tgMH_SUB)( vS2, vS0 );
    vNM = FCN_V(tgMH_UCX)( vE0, vE1 );

    FCN_VO(tgGM_ET_Init_PN)( &sET0, vS0, vS1, vS2, vNM );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_ET_Init_P) ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Init_P) )
{
    VEC_OBJ_T(TgETRI)                   sET0;
    VEC_T(1)                            vS0, vS1, vS2;

    vS0 = FCN_V(tgMH_Init_Point_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vS1 = FCN_V(tgMH_Init_Point_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vS2 = FCN_V(tgMH_Init_Point_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    FCN_VO(tgGM_ET_Init_P)( &sET0, vS0, vS1, vS2 );
    Test__Expect_EQ(true, FCN_VO(tgGM_ET_Is_Valid)( &sET0 ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_ET_Init_EN) ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Init_EN) )
{
    VEC_OBJ_T(TgETRI)                   sET0;
    VEC_T(1)                            vS0, vV0, vV1, vNM;

    vS0 = FCN_V(tgMH_Init_Point_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vV0 = FCN_V(tgMH_Init_Vector_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vV0 = FCN_V(tgMH_NORM)( vV0 );
    vV1 = FCN_V(tgMH_Init_Vector_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vV1 = FCN_V(tgMH_NORM)( vV1 );
    vNM = FCN_V(tgMH_UCX)( vV0, vV1 );

    FCN_VO(tgGM_ET_Init_EN)( &sET0, vS0, vV0, vV1, vNM );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_ET_Init_E) ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Init_E) )
{
    VEC_OBJ_T(TgETRI)                   sET0;
    VEC_T(1)                            vS0, vV0, vV1;

    vS0 = FCN_V(tgMH_Init_Point_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vV0 = FCN_V(tgMH_Init_Vector_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vV0 = FCN_V(tgMH_NORM)( vV0 );
    vV1 = FCN_V(tgMH_Init_Vector_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vV1 = FCN_V(tgMH_NORM)( vV1 );

    FCN_VO(tgGM_ET_Init_E)( &sET0, vS0, vV0, vV1 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_PT_ET_Init) ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PT_ET_Init) )
{
    VEC_OBJ_T(TgETRI)                   sET0;
    VEC_OBJ_T(TgPTRI)                   sPT0;

    FCN_V(UNIT_TEST__SETUP__PT)( &sPT0 );
    FCN_VO(tgGM_ET_Init_PT)( &sET0, &sPT0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_ET_Copy) --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Copy) )
{
    VEC_OBJ_T(TgETRI)                   sET0;

    FCN_V(UNIT_TEST__SETUP__ET)( &sET0 );
    FCN_VO(tgGM_ET_Copy)( &sET0, &sET0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_ET_Set_Origin) --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Set_Origin) )
{
    VEC_OBJ_T(TgETRI)                   sET0;
    VEC_T(1)                            vS0;

    vS0 = FCN_V(tgMH_Init_Point_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    FCN_V(UNIT_TEST__SETUP__ET)( &sET0 );
    FCN_VO(tgGM_ET_Set_Origin)( &sET0, vS0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_ET_Set_Point_0) -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Set_Point_0) )
{
    VEC_OBJ_T(TgETRI)                   sET0;
    VEC_T(1)                            vS0;

    vS0 = FCN_V(tgMH_Init_Point_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    FCN_V(UNIT_TEST__SETUP__ET)( &sET0 );
    FCN_VO(tgGM_ET_Set_Point_0)( &sET0, vS0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_ET_Set_Point_1) -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Set_Point_1) )
{
    VEC_OBJ_T(TgETRI)                   sET0;
    VEC_T(1)                            vS0;

    vS0 = FCN_V(tgMH_Init_Point_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    FCN_V(UNIT_TEST__SETUP__ET)( &sET0 );
    FCN_VO(tgGM_ET_Set_Point_1)( &sET0, vS0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_ET_Set_Point_2) -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Set_Point_2) )
{
    VEC_OBJ_T(TgETRI)                   sET0;
    VEC_T(1)                            vS0;

    vS0 = FCN_V(tgMH_Init_Point_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    FCN_V(UNIT_TEST__SETUP__ET)( &sET0 );
    FCN_VO(tgGM_ET_Set_Point_2)( &sET0, vS0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_ET_Set_Edge_0) --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Set_Edge_0) )
{
    VEC_OBJ_T(TgETRI)                   sET0;

    FCN_V(UNIT_TEST__SETUP__ET)( &sET0 );
    FCN_VO(tgGM_ET_Set_Edge_0)( &sET0, sET0.m_avEdge[0] ); /**< Point 0 to Point 1; */

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_ET_Set_Edge_1) --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Set_Edge_1) )
{
    VEC_OBJ_T(TgETRI)                   sET0;

    FCN_V(UNIT_TEST__SETUP__ET)( &sET0 );
    FCN_VO(tgGM_ET_Set_Edge_1)( &sET0, sET0.m_avEdge[1] ); /**< Point 1 to Point 2; */

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_ET_Set_Edge_2) --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Set_Edge_2) )
{
    VEC_OBJ_T(TgETRI)                   sET0;

    FCN_V(UNIT_TEST__SETUP__ET)( &sET0 );
    FCN_VO(tgGM_ET_Set_Edge_2)( &sET0, sET0.m_avEdge[2] ); /**< Point 2 to Point 0; */

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_ET_Query_Origin) ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Query_Origin) )
{
    VEC_OBJ_T(TgETRI)                   sET0;

    FCN_V(UNIT_TEST__SETUP__ET)( &sET0 );
    FCN_VO(tgGM_ET_Query_Origin)( &sET0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_ET_Query_Normal) ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Query_Normal) )
{
    VEC_OBJ_T(TgETRI)                   sET0;

    FCN_V(UNIT_TEST__SETUP__ET)( &sET0 );
    FCN_VO(tgGM_ET_Query_Normal)( &sET0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_ET_Query_Point_0) ------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Query_Point_0) )
{
    VEC_OBJ_T(TgETRI)                   sET0;

    FCN_V(UNIT_TEST__SETUP__ET)( &sET0 );
    FCN_VO(tgGM_ET_Query_Point_0)( &sET0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_ET_Query_Point_1) ------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Query_Point_1) )
{
    VEC_OBJ_T(TgETRI)                   sET0;

    FCN_V(UNIT_TEST__SETUP__ET)( &sET0 );
    FCN_VO(tgGM_ET_Query_Point_1)( &sET0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_ET_Query_Point_2) ------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Query_Point_2) )
{
    VEC_OBJ_T(TgETRI)                   sET0;

    FCN_V(UNIT_TEST__SETUP__ET)( &sET0 );
    FCN_VO(tgGM_ET_Query_Point_2)( &sET0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_ET_Query_Point) -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Query_Point) )
{
    VEC_OBJ_T(TgETRI)                   sET0;

    FCN_V(UNIT_TEST__SETUP__ET)( &sET0 );
    FCN_VO(tgGM_ET_Query_Point)( &sET0, 0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_ET_Query_Edge_0) ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Query_Edge_0) )
{
    VEC_OBJ_T(TgETRI)                   sET0;

    FCN_V(UNIT_TEST__SETUP__ET)( &sET0 );
    FCN_VO(tgGM_ET_Query_Edge_0)( &sET0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_ET_Query_Edge_1) ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Query_Edge_1) )
{
    VEC_OBJ_T(TgETRI)                   sET0;

    FCN_V(UNIT_TEST__SETUP__ET)( &sET0 );
    FCN_VO(tgGM_ET_Query_Edge_1)( &sET0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_ET_Query_Edge_2) ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Query_Edge_2) )
{
    VEC_OBJ_T(TgETRI)                   sET0;

    FCN_V(UNIT_TEST__SETUP__ET)( &sET0 );
    FCN_VO(tgGM_ET_Query_Edge_2)( &sET0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_ET_Query_Edge) --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Query_Edge) )
{
    VEC_OBJ_T(TgETRI)                   sET0;

    FCN_V(UNIT_TEST__SETUP__ET)( &sET0 );
    FCN_VO(tgGM_ET_Query_Edge)( &sET0, 0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_ET_Query_PT) ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Query_PT) )
{
    VEC_OBJ_T(TgETRI)                   sET0;

    FCN_V(UNIT_TEST__SETUP__ET)( &sET0 );
    FCN_VO(tgGM_ET_Query_PT)( &sET0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_ET_Is_Tri_Edge_Ignored) ------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Is_Tri_Edge_Ignored) )
{
    VEC_OBJ_T(TgETRI)                   sET0;

    FCN_V(UNIT_TEST__SETUP__ET)( &sET0 );
    FCN_VO(tgGM_ET_Is_Tri_Edge_Ignored)( &sET0, FCN_V(tgMH_SET1)( TYPE_K(0) ), FCN_V(tgMH_SET1)( TYPE_K(1) ) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_ET_Is_Tri_Edge_Ignored_Code) ------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_ET_Is_Tri_Edge_Ignored_Code) )
{
    VEC_OBJ_T(TgETRI)                   sET0;

    FCN_V(UNIT_TEST__SETUP__ET)( &sET0 );
    FCN_VO(tgGM_ET_Is_Tri_Edge_Ignored_Code)( &sET0, 0 );

    TEST_END_METHOD( KTgS_OK );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TgVOID FCN_V(UNIT_TEST__SETUP__ET)( VEC_OBJ_T(TgETRI,PCU) psET )
{
    VEC_T(1)                            vS0, vS1, vS2, vE0, vE1, vNM;

    vS0 = FCN_V(tgMH_Init_Point_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vS1 = FCN_V(tgMH_Init_Point_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vS2 = FCN_V(tgMH_Init_Point_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );

    vE0 = FCN_V(tgMH_SUB)( vS1, vS0 );
    vE1 = FCN_V(tgMH_SUB)( vS2, vS0 );
    vNM = FCN_V(tgMH_UCX)( vE0, vE1 );

    FCN_VO(tgGM_ET_Init_PN)( psET, vS0, vS1, vS2, vNM );
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
