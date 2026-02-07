/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common [Unit Test] - Geometry 3D - Box - Axis Aligned.c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
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

TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Is_Empty) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Union_PT) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Union_SP) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Union_BA) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Sweep) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Expand) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Scale) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Query_Centre) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Reset) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Zero) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Is_Valid) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Support_Point) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Volume) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Area) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_BA) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Sweep_BA) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Project) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Is_Contained) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_TX) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Copy_TX) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Init) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Init_PT) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Init_SP) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Copy) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Set_Invalid) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Set_Min) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Set_Max) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Set_Min_X) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Set_Min_Y) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Set_Min_Z) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Set_Max_X) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Set_Max_Y) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Set_Max_Z) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Query_Min) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Query_Max) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Query_Min_X) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Query_Min_Y) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Query_Min_Z) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Query_Max_X) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Query_Max_Y) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Query_Max_Z) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Query_Size_X) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Query_Size_Y) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Query_Size_Z) );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

static TgVOID                               FCN_V(UNIT_TEST__SETUP__BA)( VEC_OBJ_T(TgBOXAA,PCU) );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- FCN_V(UNIT_TEST__TEST__GEOM_BA) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V(UNIT_TEST__TEST__GEOM_BA) )
{
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BA_Is_Empty)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BA_Union_PT)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BA_Union_SP)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BA_Union_BA)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BA_Sweep)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BA_Expand)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BA_Scale)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BA_Query_Centre)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BA_Reset)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BA_Zero)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BA_Is_Valid)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BA_Support_Point)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BA_Volume)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BA_Area)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BA_BA)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BA_Sweep_BA)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BA_Project)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BA_Is_Contained)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BA_TX)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BA_Copy_TX)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BA_Init)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BA_Init_PT)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BA_Init_SP)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BA_Copy)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BA_Set_Invalid)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BA_Set_Min)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BA_Set_Max)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BA_Set_Min_X)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BA_Set_Min_Y)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BA_Set_Min_Z)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BA_Set_Max_X)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BA_Set_Max_Y)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BA_Set_Max_Z)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BA_Query_Min)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BA_Query_Max)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BA_Query_Min_X)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BA_Query_Min_Y)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BA_Query_Min_Z)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BA_Query_Max_X)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BA_Query_Max_Y)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BA_Query_Max_Z)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BA_Query_Size_X)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BA_Query_Size_Y)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_BA_Query_Size_Z)());

    TEST_END_METHOD( KTgS_OK );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- FCN_V(UNIT_TEST__TEST__GM_BA_Is_Empty) ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Is_Empty) )
{
    VEC_OBJ_T(TgBOXAA)                  sBA0;
    VEC_T(1)                            vS0;

    FCN_VO(tgGM_BA_Reset)( &sBA0 ); /* Clear to an inverted max box */
    Test__Expect_EQ( true, FCN_VO(tgGM_BA_Is_Empty)( &sBA0 ) ); /* Cleared to an empty box */

    vS0 = FCN_V(tgMH_Init_Point_ELEM)( TYPE_K(0), TYPE_K(0), TYPE_K(0) );
    FCN_VO(tgGM_BA_Union_PT)( &sBA0, vS0 );
    Test__Expect_EQ( true, FCN_VO(tgGM_BA_Is_Empty)( &sBA0 ) ); /* A single point is still considered to be an empty AABB */

    vS0 = FCN_V(tgMH_Init_Point_ELEM)( TYPE_K(1), TYPE_K(1), TYPE_K(1) );
    FCN_VO(tgGM_BA_Union_PT)( &sBA0, vS0 );
    Test__Expect_EQ( false, FCN_VO(tgGM_BA_Is_Empty)( &sBA0 ) ); /* Now contains two points and is non empty */

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BA_Union_PT) ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Union_PT) )
{
    VEC_OBJ_T(TgBOXAA)                  sBA0;
    VEC_UN_T(1)                         uMin, uMax;
    VEC_T(1,C)                          vS0 = FCN_V(tgMH_Init_Point_ELEM)( TYPE_K(0), TYPE_K(0), TYPE_K(0) );
    VEC_T(1,C)                          vS1 = FCN_V(tgMH_Init_Point_ELEM)( TYPE_K(1), TYPE_K(2,0), TYPE_K(3,0) );
    VEC_T(1,C)                          vS2 = FCN_V(tgMH_Init_Point_ELEM)( TYPE_K(-3,0), TYPE_K(-6,0), TYPE_K(-9,0) );

    FCN_VO(tgGM_BA_Reset)( &sBA0 ); /* Clear to an inverted max box */
    FCN_VO(tgGM_BA_Union_PT)( &sBA0, vS0 );

    VEC_UN_1_MEMBER(uMin) = sBA0.m_vMin;
    VEC_UN_1_MEMBER(uMax) = sBA0.m_vMax;

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_EQ(TYPE_K(0), VEC_S_UN_1_MEMBER(uMin).m_aData[uiIndex]);
        Test__Expect_EQ(TYPE_K(0), VEC_S_UN_1_MEMBER(uMax).m_aData[uiIndex]);
    };

    FCN_VO(tgGM_BA_Union_PT)( &sBA0, vS1 );

    VEC_UN_1_MEMBER(uMin) = sBA0.m_vMin;
    VEC_UN_1_MEMBER(uMax) = sBA0.m_vMax;

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_EQ(TYPE_K(0), VEC_S_UN_1_MEMBER(uMin).m_aData[uiIndex]);
        Test__Expect_EQ(uiIndex < 3 ? (VAR_T())(uiIndex+1) : TYPE_K(0), VEC_S_UN_1_MEMBER(uMax).m_aData[uiIndex]);
    };

    FCN_VO(tgGM_BA_Union_PT)( &sBA0, vS2 );

    VEC_UN_1_MEMBER(uMin) = sBA0.m_vMin;
    VEC_UN_1_MEMBER(uMax) = sBA0.m_vMax;

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_EQ(uiIndex < 3 ? TYPE_K(-3)*((VAR_T())(uiIndex+1)) : TYPE_K(0), VEC_S_UN_1_MEMBER(uMin).m_aData[uiIndex]);
        Test__Expect_EQ(uiIndex < 3 ? (VAR_T())(uiIndex+1) : TYPE_K(0), VEC_S_UN_1_MEMBER(uMax).m_aData[uiIndex]);
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BA_Union_SP) ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Union_SP) )
{
    VEC_OBJ_T(TgBOXAA)                  sBA0;
    VEC_T(1)                            vS0;

    vS0 = FCN_V(tgMH_Init_Point_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    FCN_V(UNIT_TEST__SETUP__BA)( &sBA0 );
    FCN_VO(tgGM_BA_Union_SP)( &sBA0, vS0, FCN_V(tgMH_SET1)( TYPE_K(1) ) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BA_Union_BA) ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Union_BA) )
{
    VEC_OBJ_T(TgBOXAA)                  sBA0, sBA1;

    FCN_V(UNIT_TEST__SETUP__BA)( &sBA0 );
    FCN_V(UNIT_TEST__SETUP__BA)( &sBA1 );
    FCN_VO(tgGM_BA_Union_BA)( &sBA1, &sBA0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BA_Sweep) -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Sweep) )
{
    VEC_OBJ_T(TgBOXAA)                  sBA0;
    VEC_T(1)                            vV0;

    vV0 = FCN_V(tgMH_Init_Vector_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vV0 = FCN_V(tgMH_NORM)( vV0 );
    FCN_V(UNIT_TEST__SETUP__BA)( &sBA0 );
    FCN_VO(tgGM_BA_Sweep)( &sBA0, vV0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BA_Expand) ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Expand) )
{
    VEC_OBJ_T(TgBOXAA)                  sBA0;

    FCN_V(UNIT_TEST__SETUP__BA)( &sBA0 );
    FCN_VO(tgGM_BA_Expand)( &sBA0, FCN_V(tgMH_SET1)( TYPE_K(1) ) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BA_Scale) -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Scale) )
{
    VEC_OBJ_T(TgBOXAA)                  sBA0;

    FCN_V(UNIT_TEST__SETUP__BA)( &sBA0 );
    FCN_VO(tgGM_BA_Scale)( &sBA0, FCN_V(tgMH_SET1)( TYPE_K(1) ) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BA_Query_Centre) ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Query_Centre) )
{
    VEC_OBJ_T(TgBOXAA)                  sBA0;

    FCN_V(UNIT_TEST__SETUP__BA)( &sBA0 );
    FCN_VO(tgGM_BA_Query_Centre)( &sBA0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BA_Reset) -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Reset) )
{
    VEC_OBJ_T(TgBOXAA)                  sBA0;

    FCN_V(UNIT_TEST__SETUP__BA)( &sBA0 );
    Test__Expect_EQ( true, FCN_VO(tgGM_BA_Is_Valid)( &sBA0 ));
    FCN_VO(tgGM_BA_Reset)( &sBA0 );
    Test__Expect_EQ( false, FCN_VO(tgGM_BA_Is_Valid)( &sBA0 ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BA_Zero) --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Zero) )
{
    VEC_OBJ_T(TgBOXAA)                  sBA0;

    FCN_V(UNIT_TEST__SETUP__BA)( &sBA0 );
    FCN_VO(tgGM_BA_Zero)( &sBA0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BA_Is_Valid) ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Is_Valid) )
{
    VEC_OBJ_T(TgBOXAA)                  sBA0;

    FCN_V(UNIT_TEST__SETUP__BA)( &sBA0 );
    FCN_VO(tgGM_BA_Is_Valid)( &sBA0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BA_Support_Point) ------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Support_Point) )
{
    VEC_OBJ_T(TgBOXAA)                  sBA0;
    VEC_T(1)                            vV0;

    vV0 = FCN_V(tgMH_Init_Vector_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vV0 = FCN_V(tgMH_NORM)( vV0 );
    FCN_V(UNIT_TEST__SETUP__BA)( &sBA0 );

    FCN_VO(tgGM_BA_Support_Point)( &sBA0, vV0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BA_Volume) ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Volume) )
{
    VEC_OBJ_T(TgBOXAA)                  sBA0;

    FCN_V(UNIT_TEST__SETUP__BA)( &sBA0 );
    FCN_VO(tgGM_BA_Volume)( &sBA0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BA_Area) --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Area) )
{
    VEC_OBJ_T(TgBOXAA)                  sBA0;

    FCN_V(UNIT_TEST__SETUP__BA)( &sBA0 );
    FCN_VO(tgGM_BA_Area)( &sBA0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BA_BA) ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_BA) )
{
    VEC_OBJ_T(TgBOXAA)                  sBA0;

    FCN_V(UNIT_TEST__SETUP__BA)( &sBA0 );
    FCN_VO(tgGM_BA_BA)( &sBA0, &sBA0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BA_Sweep_BA) ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Sweep_BA) )
{
    VEC_OBJ_T(TgBOXAA)                  sBA0;
    VEC_T(1)                            vV0;

    vV0 = FCN_V(tgMH_Init_Vector_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vV0 = FCN_V(tgMH_NORM)( vV0 );
    FCN_V(UNIT_TEST__SETUP__BA)( &sBA0 );
    FCN_VO(tgGM_BA_Sweep_BA)( &sBA0, &sBA0, vV0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BA_Project) ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Project) )
{
    VEC_OBJ_T(TgBOXAA)                  sBA0;
    VEC_T(1)                            vV0;
    VEC_T(1)                            fVal;

    vV0 = FCN_V(tgMH_Init_Vector_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vV0 = FCN_V(tgMH_NORM)( vV0 );
    FCN_V(UNIT_TEST__SETUP__BA)( &sBA0 );
    FCN_VO(tgGM_BA_Project)( &fVal, &fVal, &sBA0, vV0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BA_Is_Contained) ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Is_Contained) )
{
    VEC_OBJ_T(TgBOXAA)                  sBA0;
    VEC_T(1)                            vS0;

    vS0 = FCN_V(tgMH_Init_Point_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    FCN_V(UNIT_TEST__SETUP__BA)( &sBA0 );
    FCN_VO(tgGM_BA_Is_Contained)( &sBA0, vS0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BA_TX) ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_TX) )
{
    VEC_OBJ_T(TgBOXAA)                  sBA0;
    VEC_T(3)                            xM0;

    FCN_V(tgMH_CLI,3)( &xM0 );
    FCN_V(UNIT_TEST__SETUP__BA)( &sBA0 );
    FCN_VO(tgGM_BA_TX)( &sBA0, &xM0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BA_Copy_TX) ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Copy_TX) )
{
    VEC_OBJ_T(TgBOXAA)                  sBA0;
    VEC_T(3)                            xM0;

    FCN_V(tgMH_CLI,3)( &xM0 );
    FCN_V(UNIT_TEST__SETUP__BA)( &sBA0 );
    FCN_VO(tgGM_BA_Copy_TX)( &sBA0, &sBA0, &xM0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BA_Init) --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Init) )
{
    VEC_OBJ_T(TgBOXAA)                  sBA0;
    VEC_T(1)                            vS0;

    vS0 = FCN_V(tgMH_Init_Point_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    FCN_V(UNIT_TEST__SETUP__BA)( &sBA0 );
    FCN_VO(tgGM_BA_Init)( &sBA0, vS0, vS0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BA_Init_PT) ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Init_PT) )
{
    VEC_OBJ_T(TgBOXAA)                  sBA0;
    VEC_T(1)                            vS0;

    vS0 = FCN_V(tgMH_Init_Point_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    FCN_V(UNIT_TEST__SETUP__BA)( &sBA0 );
    FCN_VO(tgGM_BA_Init_PT)( &sBA0, vS0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BA_Init_SP) ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Init_SP) )
{
    VEC_OBJ_T(TgBOXAA)                  sBA0;
    VEC_T(1)                            vS0;

    vS0 = FCN_V(tgMH_Init_Point_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    FCN_V(UNIT_TEST__SETUP__BA)( &sBA0 );
    FCN_VO(tgGM_BA_Init_SP)( &sBA0, vS0, FCN_V(tgMH_SET1)( TYPE_K(1) ) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BA_Copy) --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Copy) )
{
    VEC_OBJ_T(TgBOXAA)                  sBA0;

    FCN_V(UNIT_TEST__SETUP__BA)( &sBA0 );
    FCN_VO(tgGM_BA_Copy)( &sBA0, &sBA0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BA_Set_Invalid) -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Set_Invalid) )
{
    VEC_OBJ_T(TgBOXAA)                  sBA0;

    FCN_V(UNIT_TEST__SETUP__BA)( &sBA0 );
    FCN_VO(tgGM_BA_Set_Invalid)( &sBA0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BA_Set_Min) ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Set_Min) )
{
    VEC_OBJ_T(TgBOXAA)                  sBA0;
    VEC_T(1)                            vS0;

    vS0 = FCN_V(tgMH_Init_Vector_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    FCN_V(UNIT_TEST__SETUP__BA)( &sBA0 );
    FCN_VO(tgGM_BA_Set_Min)( &sBA0, vS0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BA_Set_Max) ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Set_Max) )
{
    VEC_OBJ_T(TgBOXAA)                  sBA0;
    VEC_T(1)                            vS0;

    vS0 = FCN_V(tgMH_Init_Vector_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    FCN_V(UNIT_TEST__SETUP__BA)( &sBA0 );
    FCN_VO(tgGM_BA_Set_Max)( &sBA0, vS0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BA_Set_Min_X) ---------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Set_Min_X) )
{
    VEC_OBJ_T(TgBOXAA)                  sBA0;

    FCN_V(UNIT_TEST__SETUP__BA)( &sBA0 );
    FCN_VO(tgGM_BA_Set_Min_X)( &sBA0, FCN_V(tgMH_SET1)( TYPE_K(1) ) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BA_Set_Min_Y) ---------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Set_Min_Y) )
{
    VEC_OBJ_T(TgBOXAA)                  sBA0;

    FCN_V(UNIT_TEST__SETUP__BA)( &sBA0 );
    FCN_VO(tgGM_BA_Set_Min_Y)( &sBA0, FCN_V(tgMH_SET1)( TYPE_K(1) ) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BA_Set_Min_Z) ---------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Set_Min_Z) )
{
    VEC_OBJ_T(TgBOXAA)                  sBA0;

    FCN_V(UNIT_TEST__SETUP__BA)( &sBA0 );
    FCN_VO(tgGM_BA_Set_Min_Z)( &sBA0, FCN_V(tgMH_SET1)( TYPE_K(1) ) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BA_Set_Max_X) ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Set_Max_X) )
{
    VEC_OBJ_T(TgBOXAA)                  sBA0;

    FCN_V(UNIT_TEST__SETUP__BA)( &sBA0 );
    FCN_VO(tgGM_BA_Set_Max_X)( &sBA0, FCN_V(tgMH_SET1)( TYPE_K(1) ) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BA_Set_Max_Y) ---------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Set_Max_Y) )
{
    VEC_OBJ_T(TgBOXAA)                  sBA0;

    FCN_V(UNIT_TEST__SETUP__BA)( &sBA0 );
    FCN_VO(tgGM_BA_Set_Max_Y)( &sBA0, FCN_V(tgMH_SET1)( TYPE_K(1) ) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BA_Set_Max_Z) ---------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Set_Max_Z) )
{
    VEC_OBJ_T(TgBOXAA)                  sBA0;

    FCN_V(UNIT_TEST__SETUP__BA)( &sBA0 );
    FCN_VO(tgGM_BA_Set_Max_Z)( &sBA0, FCN_V(tgMH_SET1)( TYPE_K(1) ) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BA_Query_Min) ---------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Query_Min) )
{
    VEC_OBJ_T(TgBOXAA)                  sBA0;
    VEC_T(1)                            vVal;

    FCN_V(UNIT_TEST__SETUP__BA)( &sBA0 );

    vVal = sBA0.m_vMin;
    Test__Expect_EQ(0, tgMM_Compare( &vVal, sizeof(vVal), &sBA0.m_vMin, sizeof(sBA0.m_vMin) ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BA_Query_Max) ---------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Query_Max) )
{
    VEC_OBJ_T(TgBOXAA)                  sBA0;
    VEC_T(1)                            vVal;

    FCN_V(UNIT_TEST__SETUP__BA)( &sBA0 );

    vVal = sBA0.m_vMax;
    Test__Expect_EQ(0, tgMM_Compare( &vVal, sizeof(vVal), &sBA0.m_vMax, sizeof(sBA0.m_vMax) ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BA_Query_Min_X) -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Query_Min_X) )
{
    VEC_OBJ_T(TgBOXAA)                  sBA0;

    FCN_V(UNIT_TEST__SETUP__BA)( &sBA0 );
    FCN_VO(tgGM_BA_Query_Min_X)( &sBA0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BA_Query_Min_Y) -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Query_Min_Y) )
{
    VEC_OBJ_T(TgBOXAA)                  sBA0;

    FCN_V(UNIT_TEST__SETUP__BA)( &sBA0 );
    FCN_VO(tgGM_BA_Query_Min_Y)( &sBA0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BA_Query_Min_Z) -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Query_Min_Z) )
{
    VEC_OBJ_T(TgBOXAA)                  sBA0;

    FCN_V(UNIT_TEST__SETUP__BA)( &sBA0 );
    FCN_VO(tgGM_BA_Query_Min_Z)( &sBA0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BA_Query_Max_X) -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Query_Max_X) )
{
    VEC_OBJ_T(TgBOXAA)                  sBA0;

    FCN_V(UNIT_TEST__SETUP__BA)( &sBA0 );
    FCN_VO(tgGM_BA_Query_Max_X)( &sBA0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BA_Query_Max_Y) -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Query_Max_Y) )
{
    VEC_OBJ_T(TgBOXAA)                  sBA0;

    FCN_V(UNIT_TEST__SETUP__BA)( &sBA0 );
    FCN_VO(tgGM_BA_Query_Max_Y)( &sBA0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BA_Query_Max_Z) -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Query_Max_Z) )
{
    VEC_OBJ_T(TgBOXAA)                  sBA0;

    FCN_V(UNIT_TEST__SETUP__BA)( &sBA0 );
    FCN_VO(tgGM_BA_Query_Max_Z)( &sBA0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BA_Query_Size_X) ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Query_Size_X) )
{
    VEC_OBJ_T(TgBOXAA)                  sBA0;

    FCN_V(UNIT_TEST__SETUP__BA)( &sBA0 );
    FCN_VO(tgGM_BA_Query_Size_X)( &sBA0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BA_Query_Size_Y) ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Query_Size_Y) )
{
    VEC_OBJ_T(TgBOXAA)                  sBA0;

    FCN_V(UNIT_TEST__SETUP__BA)( &sBA0 );
    FCN_VO(tgGM_BA_Query_Size_Y)( &sBA0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_BA_Query_Size_Z) ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_BA_Query_Size_Z) )
{
    VEC_OBJ_T(TgBOXAA)                  sBA0;

    FCN_V(UNIT_TEST__SETUP__BA)( &sBA0 );
    FCN_VO(tgGM_BA_Query_Size_Z)( &sBA0 );

    TEST_END_METHOD( KTgS_OK );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

static TgVOID FCN_V(UNIT_TEST__SETUP__BA)( VEC_OBJ_T(TgBOXAA,PCU) psBA )
{
    VEC_T(1)                            vS0;

    vS0 = FCN_V(tgMH_Init_Point_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    tgMM_Set_U08_0x00( psBA, sizeof( VEC_OBJ_T(TgBOXAA) ) );

    FCN_VO(tgGM_BA_Init_SP)( psBA, vS0, FCN_V(tgMH_SET1)( TYPE_K(1) ) );
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
