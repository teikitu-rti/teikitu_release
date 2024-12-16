/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common [Unit Test] - Geometry 3D - Box.c
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

TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BX_Calc_Point) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BX_Calc_Point_Index) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BX_Reset) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BX_Is_Valid) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BX_Support_Point) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BX_Volume) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BX_Area) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BX_BA) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BX_Sweep_BA) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BX_Project) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BX_Is_Contained) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BX_TX) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BX_Copy_TX) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BX_Init) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BX_Copy) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BX_Set_Reference_Frame) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BX_Set_Origin) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BX_Set_Extent_List) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BX_Set_Extent_Index) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BX_Set_Extent_0) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BX_Set_Extent_1) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BX_Set_Extent_2) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BX_Query_Origin) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BX_Query_Axis_Unit_0) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BX_Query_Axis_Unit_1) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BX_Query_Axis_Unit_2) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BX_Query_Extent_List) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BX_Query_Extent_Index) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BX_Query_Extent_0) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BX_Query_Extent_1) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BX_Query_Extent_2) );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

static TgVOID                               FCN_V(UNIT_TEST__SETUP__BX)( VEC_OBJ_T(TgBOX,PCU) );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- FCN_V(UNIT_TEST__TEST__GEOM_BX) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V(UNIT_TEST__TEST__GEOM_BX) )
{
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BX_Calc_Point)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BX_Calc_Point_Index)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BX_Reset)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BX_Is_Valid)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BX_Support_Point)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BX_Volume)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BX_Area)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BX_BA)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BX_Sweep_BA)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BX_Project)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BX_Is_Contained)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BX_TX)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BX_Copy_TX)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BX_Init)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BX_Copy)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BX_Set_Reference_Frame)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BX_Set_Origin)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BX_Set_Extent_List)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BX_Set_Extent_Index)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BX_Set_Extent_0)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BX_Set_Extent_1)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BX_Set_Extent_2)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BX_Query_Origin)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BX_Query_Axis_Unit_0)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BX_Query_Axis_Unit_1)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BX_Query_Axis_Unit_2)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BX_Query_Extent_List)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BX_Query_Extent_Index)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BX_Query_Extent_0)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BX_Query_Extent_1)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BX_Query_Extent_2)());

    TEST_END_METHOD( KTgS_OK );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- FCN_V(UNIT_TEST__TEST__GM_BX_Calc_Point) --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BX_Calc_Point) )
{
    VEC_OBJ_T(TgBOX)                    sBX0;
    VEC_T(1)                            vOne;

    vOne = FCN_V(tgMH_SET1)( TYPE_K(1) );
    FCN_V(UNIT_TEST__SETUP__BX)( &sBX0 );

    FCN_VO(tgGM_BX_Calc_Point)( &sBX0, vOne, vOne, vOne );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BX_Calc_Point_Index) --------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BX_Calc_Point_Index) )
{
    VEC_OBJ_T(TgBOX)                    sBX0;

    FCN_V(UNIT_TEST__SETUP__BX)( &sBX0 );
    FCN_VO(tgGM_BX_Calc_Point_Index)( &sBX0, 0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BX_Reset) -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BX_Reset) )
{
    VEC_OBJ_T(TgBOX)                    sBX0;

    FCN_V(UNIT_TEST__SETUP__BX)( &sBX0 );
    FCN_VO(tgGM_BX_Reset)( &sBX0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BX_Is_Valid) ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BX_Is_Valid) )
{
    VEC_OBJ_T(TgBOX)                    sBX0;

    FCN_V(UNIT_TEST__SETUP__BX)( &sBX0 );
    Test__Expect_EQ( true, FCN_VO(tgGM_BX_Is_Valid)( &sBX0 ));
    FCN_VO(tgGM_BX_Reset)( &sBX0 );
    Test__Expect_EQ(false, FCN_VO(tgGM_BX_Is_Valid)( &sBX0 ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BX_Support_Point) ------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BX_Support_Point) )
{
    VEC_OBJ_T(TgBOX)                    sBX0;
    VEC_T(1)                            vV0;

    FCN_V(UNIT_TEST__SETUP__BX)( &sBX0 );

    vV0 = FCN_V(tgMH_Init_Vector_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vV0 = FCN_V(tgMH_NORM)( vV0 );

    FCN_VO(tgGM_BX_Support_Point)( &sBX0, vV0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BX_Volume) ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BX_Volume) )
{
    VEC_OBJ_T(TgBOX)                    sBX0;

    FCN_V(UNIT_TEST__SETUP__BX)( &sBX0 );
    FCN_VO(tgGM_BX_Volume)( &sBX0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BX_Area) --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BX_Area) )
{
    VEC_OBJ_T(TgBOX)                    sBX0;

    FCN_V(UNIT_TEST__SETUP__BX)( &sBX0 );
    FCN_VO(tgGM_BX_Area)( &sBX0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BX_BA) ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BX_BA) )
{
    VEC_OBJ_T(TgBOX)                    sBX0;
    VEC_OBJ_T(TgBOXAA)                  sBA0;

    FCN_V(UNIT_TEST__SETUP__BX)( &sBX0 );
    FCN_VO(tgGM_BX_BA)( &sBA0, &sBX0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BX_Sweep_BA) ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BX_Sweep_BA) )
{
    VEC_OBJ_T(TgBOX)                    sBX0;
    VEC_OBJ_T(TgBOXAA)                  sBA0;
    VEC_T(1)                            vV0;

    vV0 = FCN_V(tgMH_Init_Vector_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vV0 = FCN_V(tgMH_NORM)( vV0 );
    FCN_V(UNIT_TEST__SETUP__BX)( &sBX0 );
    FCN_VO(tgGM_BX_Sweep_BA)( &sBA0, &sBX0, vV0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BX_Project) ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BX_Project) )
{
    VEC_OBJ_T(TgBOX)                    sBX0;
    VEC_T(1)                            vV0, vVal;

    vV0 = FCN_V(tgMH_Init_Vector_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vV0 = FCN_V(tgMH_NORM)( vV0 );
    FCN_V(UNIT_TEST__SETUP__BX)( &sBX0 );
    FCN_VO(tgGM_BX_Project)( &vVal, &vVal, &sBX0, vV0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BX_Is_Contained) ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BX_Is_Contained) )
{
    VEC_OBJ_T(TgBOX)                    sBX0;
    VEC_T(1)                            vS0;

    vS0 = FCN_V(tgMH_Init_Point_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    FCN_V(UNIT_TEST__SETUP__BX)( &sBX0 );
    FCN_VO(tgGM_BX_Is_Contained)( &sBX0, vS0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BX_TX) ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BX_TX) )
{
    VEC_OBJ_T(TgBOX)                    sBX0;
    VEC_T(3)                            xM0;

    FCN_V(tgMH_CLI,3)( &xM0 );
    FCN_V(UNIT_TEST__SETUP__BX)( &sBX0 );
    FCN_VO(tgGM_BX_TX)( &sBX0, &xM0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BX_Copy_TX) ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BX_Copy_TX) )
{
    VEC_OBJ_T(TgBOX)                    sBX0;
    VEC_T(3)                            xM0;

    FCN_V(tgMH_CLI,3)( &xM0 );
    FCN_V(UNIT_TEST__SETUP__BX)( &sBX0 );
    FCN_VO(tgGM_BX_Copy_TX)( &sBX0, &sBX0, &xM0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BX_Init) --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BX_Init) )
{
    VEC_OBJ_T(TgBOX)                    sBX0;
    VEC_T(3)                            xM0;

    FCN_V(tgMH_CLI,3)( &xM0 );
    FCN_V(UNIT_TEST__SETUP__BX)( &sBX0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BX_Copy) --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BX_Copy) )
{
    VEC_OBJ_T(TgBOX)                    sBX0;

    FCN_V(UNIT_TEST__SETUP__BX)( &sBX0 );
    FCN_VO(tgGM_BX_Copy)( &sBX0, &sBX0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BX_Set_Reference_Frame) ------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BX_Set_Reference_Frame) )
{
    VEC_OBJ_T(TgBOX)                    sBX0;
    VEC_T(3)                            xM0;

    FCN_V(tgMH_CLI,3)( &xM0 );
    FCN_V(UNIT_TEST__SETUP__BX)( &sBX0 );
    FCN_VO(tgGM_BX_Set_Reference_Frame)( &sBX0, &xM0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BX_Set_Origin) --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BX_Set_Origin) )
{
    VEC_OBJ_T(TgBOX)                    sBX0;
    VEC_T(1)                            vS0;

    vS0 = FCN_V(tgMH_Init_Point_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    FCN_V(UNIT_TEST__SETUP__BX)( &sBX0 );
    FCN_VO(tgGM_BX_Set_Origin)( &sBX0, vS0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BX_Set_Extent_List) ---------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BX_Set_Extent_List) )
{
    VEC_OBJ_T(TgBOX)                    sBX0;
    VEC_T(1)                            vV0;

    FCN_V(UNIT_TEST__SETUP__BX)( &sBX0 );

    vV0 = FCN_V(tgMH_Init_Vector_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vV0 = FCN_V(tgMH_NORM)( vV0 );
    vV0 = FCN_V(tgMH_ABS)( vV0 );

    FCN_VO(tgGM_BX_Set_Extent_List)( &sBX0, vV0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BX_Set_Extent_Index) --------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BX_Set_Extent_Index) )
{
    VEC_OBJ_T(TgBOX)                    sBX0;

    FCN_V(UNIT_TEST__SETUP__BX)( &sBX0 );
    FCN_VO(tgGM_BX_Set_Extent_Index)( &sBX0, 0, FCN_V(tgMH_SET1)( TYPE_K(1) ) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BX_Set_Extent_0) ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BX_Set_Extent_0) )
{
    VEC_OBJ_T(TgBOX)                    sBX0;

    FCN_V(UNIT_TEST__SETUP__BX)( &sBX0 );
    FCN_VO(tgGM_BX_Set_Extent_0)( &sBX0, FCN_V(tgMH_SET1)( TYPE_K(1) ) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BX_Set_Extent_1) ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BX_Set_Extent_1) )
{
    VEC_OBJ_T(TgBOX)                    sBX0;

    FCN_V(UNIT_TEST__SETUP__BX)( &sBX0 );
    FCN_VO(tgGM_BX_Set_Extent_1)( &sBX0, FCN_V(tgMH_SET1)( TYPE_K(1) ) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BX_Set_Extent_2) ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BX_Set_Extent_2) )
{
    VEC_OBJ_T(TgBOX)                    sBX0;

    FCN_V(UNIT_TEST__SETUP__BX)( &sBX0 );
    FCN_VO(tgGM_BX_Set_Extent_2)( &sBX0, FCN_V(tgMH_SET1)( TYPE_K(1) ) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BX_Query_Origin) ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BX_Query_Origin) )
{
    VEC_OBJ_T(TgBOX)                    sBX0;

    FCN_V(UNIT_TEST__SETUP__BX)( &sBX0 );
    FCN_VO(tgGM_BX_Query_Origin)( &sBX0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BX_Query_Axis_Unit_0) -------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BX_Query_Axis_Unit_0) )
{
    VEC_OBJ_T(TgBOX)                    sBX0;

    FCN_V(UNIT_TEST__SETUP__BX)( &sBX0 );
    FCN_VO(tgGM_BX_Query_Axis_Unit_0)( &sBX0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BX_Query_Axis_Unit_1) -------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BX_Query_Axis_Unit_1) )
{
    VEC_OBJ_T(TgBOX)                    sBX0;

    FCN_V(UNIT_TEST__SETUP__BX)( &sBX0 );
    FCN_VO(tgGM_BX_Query_Axis_Unit_1)( &sBX0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BX_Query_Axis_Unit_2) -------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BX_Query_Axis_Unit_2) )
{
    VEC_OBJ_T(TgBOX)                    sBX0;

    FCN_V(UNIT_TEST__SETUP__BX)( &sBX0 );
    FCN_VO(tgGM_BX_Query_Axis_Unit_2)( &sBX0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BX_Query_Extent_List) -------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BX_Query_Extent_List) )
{
    VEC_OBJ_T(TgBOX)                    sBX0;

    FCN_V(UNIT_TEST__SETUP__BX)( &sBX0 );
    FCN_VO(tgGM_BX_Query_Extent_List)( &sBX0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BX_Query_Extent_Index) ------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BX_Query_Extent_Index) )
{
    VEC_OBJ_T(TgBOX)                    sBX0;

    FCN_V(UNIT_TEST__SETUP__BX)( &sBX0 );
    FCN_VO(tgGM_BX_Query_Extent_Index)( &sBX0, 0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BX_Query_Extent_0) ----------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BX_Query_Extent_0) )
{
    VEC_OBJ_T(TgBOX)                    sBX0;

    FCN_V(UNIT_TEST__SETUP__BX)( &sBX0 );
    FCN_VO(tgGM_BX_Query_Extent_0)( &sBX0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BX_Query_Extent_1) ----------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BX_Query_Extent_1) )
{
    VEC_OBJ_T(TgBOX)                    sBX0;

    FCN_V(UNIT_TEST__SETUP__BX)( &sBX0 );
    FCN_VO(tgGM_BX_Query_Extent_1)( &sBX0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BX_Query_Extent_2) ----------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BX_Query_Extent_2) )
{
    VEC_OBJ_T(TgBOX)                    sBX0;

    FCN_V(UNIT_TEST__SETUP__BX)( &sBX0 );
    FCN_VO(tgGM_BX_Query_Extent_2)( &sBX0 );

    TEST_END_METHOD( KTgS_OK );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

static TgVOID FCN_V(UNIT_TEST__SETUP__BX)( VEC_OBJ_T(TgBOX,PCU) psBX )
{
    VEC_T(3)                            xM0;

    FCN_V(tgMH_CLI,3)( &xM0 );

    FCN_VO(tgGM_BX_Init)( psBX, &xM0, FCN_V(tgMH_SET1)( TYPE_K(1) ) );
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
