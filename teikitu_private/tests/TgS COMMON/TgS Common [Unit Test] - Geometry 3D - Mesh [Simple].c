/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common [Unit Test] - Geometry 3D - Mesh [Simple].c
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

TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MS_Reset) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MS_Is_Valid) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MS_Support_Point) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MS_Volume) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MS_Area) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MS_BA) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MS_Sweep_BA) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MS_Project) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MS_Is_Contained) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MS_TX) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MS_Copy_TX) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MS_Init) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MS_Copy) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MS_Query_Indx_List) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MS_Query_Vert_List) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MS_Query_Indx_Count) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MS_Query_Vert_Count) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_Volume_MS_VL) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_Volume_MS_IL) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_Area_MS_VL) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_Area_MS_IL) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_Is_Contained_MS_VL) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_Is_Contained_MS_IL) );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Setup Functions and Data                                                                                                                                                       */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TgEXTN TgVOID
FCN_V(UNIT_TEST__SETUP__MS_Init_VL)(
    VEC_OBJ_T(TgMESH_SIMPLE,PCU) );

TgEXTN TgVOID
FCN_V(UNIT_TEST__SETUP__MS_Init_IL)(
    VEC_OBJ_T(TgMESH_SIMPLE,PCU) );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- FCN_V(UNIT_TEST__TEST__GEOM_MS) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V(UNIT_TEST__TEST__GEOM_MS) )
{
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MS_Reset)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MS_Is_Valid)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MS_Support_Point)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MS_Volume)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MS_Area)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MS_BA)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MS_Sweep_BA)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MS_Project)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MS_Is_Contained)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MS_TX)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MS_Copy_TX)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MS_Init)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MS_Copy)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MS_Query_Indx_List)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MS_Query_Vert_List)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MS_Query_Indx_Count)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_MS_Query_Vert_Count)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_Volume_MS_VL)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_Volume_MS_IL)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_Area_MS_VL)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_Area_MS_IL)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_Is_Contained_MS_VL)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_Is_Contained_MS_IL)());

    TEST_END_METHOD( KTgS_OK );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- FCN_V(UNIT_TEST__TEST__GM_MS_Reset) -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MS_Reset) )
{
    VEC_OBJ_T(TgMESH_SIMPLE)            sMS0;

    FCN_V(UNIT_TEST__SETUP__MS_Init_IL)( &sMS0 );
    FCN_VO(tgGM_MS_Reset)( &sMS0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_MS_Is_Valid) ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MS_Is_Valid) )
{
    VEC_OBJ_T(TgMESH_SIMPLE)            sMS0;

    FCN_V(UNIT_TEST__SETUP__MS_Init_IL)( &sMS0 );
    FCN_VO(tgGM_MS_Is_Valid)( &sMS0 );
    FCN_VO(tgGM_MS_Reset)( &sMS0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_MS_Support_Point) ------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MS_Support_Point) )
{
    VEC_T(1)                            vV0;
    VEC_OBJ_T(TgMESH_SIMPLE)            sMS0;

    vV0 = FCN_V(tgMH_Init_Vector_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vV0 = FCN_V(tgMH_NORM)( vV0 );
    FCN_V(UNIT_TEST__SETUP__MS_Init_IL)( &sMS0 );
    FCN_VO(tgGM_MS_Support_Point)( &sMS0, vV0 );
    FCN_VO(tgGM_MS_Reset)( &sMS0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_MS_Volume) ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MS_Volume) )
{
    VEC_OBJ_T(TgMESH_SIMPLE)            sMS0;

    FCN_V(UNIT_TEST__SETUP__MS_Init_IL)( &sMS0 );
    FCN_VO(tgGM_MS_Volume)( &sMS0 );
    FCN_VO(tgGM_MS_Reset)( &sMS0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_MS_Area) --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MS_Area) )
{
    VEC_OBJ_T(TgMESH_SIMPLE)            sMS0;

    FCN_V(UNIT_TEST__SETUP__MS_Init_IL)( &sMS0 );
    FCN_VO(tgGM_MS_Area)( &sMS0 );
    FCN_VO(tgGM_MS_Reset)( &sMS0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_MS_BA) ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MS_BA) )
{
    VEC_OBJ_T(TgMESH_SIMPLE)            sMS0;
    VEC_OBJ_T(TgBOXAA)                  sBA0;

    FCN_V(UNIT_TEST__SETUP__MS_Init_IL)( &sMS0 );
    FCN_VO(tgGM_MS_BA)( &sBA0, &sMS0 );
    FCN_VO(tgGM_MS_Reset)( &sMS0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_MS_Sweep_BA) ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MS_Sweep_BA) )
{
    VEC_OBJ_T(TgBOXAA)                  sBA0;
    VEC_OBJ_T(TgMESH_SIMPLE)            sMS0;
    VEC_T(1)                            vV0;

    vV0 = FCN_V(tgMH_Init_Vector_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vV0 = FCN_V(tgMH_NORM)( vV0 );
    FCN_V(UNIT_TEST__SETUP__MS_Init_IL)( &sMS0 );
    FCN_VO(tgGM_MS_Sweep_BA)( &sBA0, &sMS0, vV0 );
    FCN_VO(tgGM_MS_Reset)( &sMS0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_MS_Project) ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MS_Project) )
{
    VEC_OBJ_T(TgMESH_SIMPLE)            sMS0;
    VEC_T(1)                            vV0, vVal;

    vV0 = FCN_V(tgMH_Init_Vector_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vV0 = FCN_V(tgMH_NORM)( vV0 );
    FCN_V(UNIT_TEST__SETUP__MS_Init_IL)( &sMS0 );
    FCN_VO(tgGM_MS_Project)( &vVal, &vVal, &sMS0, vV0 );
    FCN_VO(tgGM_MS_Reset)( &sMS0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_MS_Is_Contained) ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MS_Is_Contained) )
{
    VEC_T(1)                            vS0;
    VEC_OBJ_T(TgMESH_SIMPLE)            sMS0;

    vS0 = FCN_V(tgMH_Init_Point_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    FCN_V(UNIT_TEST__SETUP__MS_Init_IL)( &sMS0 );
    FCN_VO(tgGM_MS_Is_Contained)( &sMS0, vS0 );
    FCN_VO(tgGM_MS_Reset)( &sMS0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_MS_TX) ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MS_TX) )
{
    VEC_OBJ_T(TgMESH_SIMPLE)            sMS0;
    VEC_T(3)                            xM0;

    FCN_V(UNIT_TEST__SETUP__MS_Init_IL)( &sMS0 );
    FCN_V(tgMH_CLI,3)( &xM0 );
    FCN_VO(tgGM_MS_TX)( &sMS0, &xM0 );
    FCN_VO(tgGM_MS_Reset)( &sMS0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_MS_Copy_TX) ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MS_Copy_TX) )
{
    VEC_OBJ_T(TgMESH_SIMPLE)            sMS0, sMS1;
    VEC_T(3)                            xM0;

    FCN_V(UNIT_TEST__SETUP__MS_Init_IL)( &sMS0 );
    FCN_V(tgMH_CLI,3)( &xM0 );
    tgMM_Set_U08_0x00( &sMS1, sizeof( sMS1 ) );
    FCN_VO(tgGM_MS_Copy_TX)( &sMS1, &sMS0, &xM0 );
    FCN_VO(tgGM_MS_Reset)( &sMS0 );
    FCN_VO(tgGM_MS_Reset)( &sMS1 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_MS_Init) --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MS_Init) )
{
    VEC_OBJ_T(TgMESH_SIMPLE)            sMS0;

    FCN_V(UNIT_TEST__SETUP__MS_Init_IL)( &sMS0 );
    FCN_VO(tgGM_MS_Reset)( &sMS0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_MS_Copy) --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MS_Copy) )
{
    VEC_OBJ_T(TgMESH_SIMPLE)            sMS0, sMS1;

    FCN_V(UNIT_TEST__SETUP__MS_Init_IL)( &sMS0 );
    tgMM_Set_U08_0x00( &sMS1, sizeof( sMS1 ) );
    FCN_VO(tgGM_MS_Copy)( &sMS1, &sMS0 );
    FCN_VO(tgGM_MS_Reset)( &sMS0 );
    FCN_VO(tgGM_MS_Reset)( &sMS1 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_MS_Query_Indx_List) ---------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MS_Query_Indx_List) )
{
    VEC_OBJ_T(TgMESH_SIMPLE)            sMS0;

    FCN_V(UNIT_TEST__SETUP__MS_Init_IL)( &sMS0 );
    FCN_VO(tgGM_MS_Query_Indx_List)( &sMS0 );
    FCN_VO(tgGM_MS_Reset)( &sMS0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_MS_Query_Vert_List) ---------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MS_Query_Vert_List) )
{
    VEC_OBJ_T(TgMESH_SIMPLE)            sMS0;

    FCN_V(UNIT_TEST__SETUP__MS_Init_IL)( &sMS0 );
    FCN_VO(tgGM_MS_Query_Vert_List)( &sMS0 );
    FCN_VO(tgGM_MS_Reset)( &sMS0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_MS_Query_Indx_Count) --------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MS_Query_Indx_Count) )
{
    VEC_OBJ_T(TgMESH_SIMPLE)            sMS0;

    FCN_V(UNIT_TEST__SETUP__MS_Init_IL)( &sMS0 );
    Test__Expect_EQ( TgARRAY_COUNT(KTgGM_ICOSAHEDRON_PN_INDEX), FCN_VO(tgGM_MS_Query_Indx_Count)( &sMS0 ) );
    FCN_VO(tgGM_MS_Reset)( &sMS0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_MS_Query_Vert_Count) --------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_MS_Query_Vert_Count) )
{
    VEC_OBJ_T(TgMESH_SIMPLE)            sMS0;

    FCN_V(UNIT_TEST__SETUP__MS_Init_IL)( &sMS0 );
    Test__Expect_EQ( TgARRAY_COUNT(KTgGM_ICOSAHEDRON_PN_INDEX_VERTEX) >> 1, FCN_VO(tgGM_MS_Query_Vert_Count)( &sMS0 ) );
    FCN_VO(tgGM_MS_Reset)( &sMS0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_Volume_MS_VL) ---------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_Volume_MS_VL) )
{
    VEC_OBJ_T(TgMESH_SIMPLE)            sMS0;

    FCN_V(UNIT_TEST__SETUP__MS_Init_VL)( &sMS0 );
    FCN_VO(tgGM_Volume_MS_VL)( &sMS0 );
    FCN_VO(tgGM_MS_Reset)( &sMS0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_Volume_MS_IL) ---------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_Volume_MS_IL) )
{
    VEC_OBJ_T(TgMESH_SIMPLE)            sMS0;

    FCN_V(UNIT_TEST__SETUP__MS_Init_IL)( &sMS0 );
    FCN_VO(tgGM_Volume_MS_IL)( &sMS0 );
    FCN_VO(tgGM_MS_Reset)( &sMS0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_Area_MS_VL) ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_Area_MS_VL) )
{
    VEC_OBJ_T(TgMESH_SIMPLE)            sMS0;

    FCN_V(UNIT_TEST__SETUP__MS_Init_VL)( &sMS0 );
    FCN_VO(tgGM_Area_MS_VL)( &sMS0 );
    FCN_VO(tgGM_MS_Reset)( &sMS0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_Area_MS_IL) ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_Area_MS_IL) )
{
    VEC_OBJ_T(TgMESH_SIMPLE)            sMS0;

    FCN_V(UNIT_TEST__SETUP__MS_Init_IL)( &sMS0 );
    FCN_VO(tgGM_Area_MS_IL)( &sMS0 );
    FCN_VO(tgGM_MS_Reset)( &sMS0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_Is_Contained_MS_VL) ---------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_Is_Contained_MS_VL) )
{
    VEC_OBJ_T(TgMESH_SIMPLE)            sMS0;
    VEC_T(1)                            vS0;

    vS0 = FCN_V(tgMH_Init_Point_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    FCN_V(UNIT_TEST__SETUP__MS_Init_VL)( &sMS0 );
    FCN_VO(tgGM_Is_Contained_MS_VL)( &sMS0, vS0 );
    FCN_VO(tgGM_MS_Reset)( &sMS0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_Is_Contained_MS_IL) ---------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_Is_Contained_MS_IL) )
{
    VEC_OBJ_T(TgMESH_SIMPLE)            sMS0;
    VEC_T(1)                            vS0;

    vS0 = FCN_V(tgMH_Init_Point_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    FCN_V(UNIT_TEST__SETUP__MS_Init_IL)( &sMS0 );
    FCN_VO(tgGM_Is_Contained_MS_IL)( &sMS0, vS0 );
    FCN_VO(tgGM_MS_Reset)( &sMS0 );

    TEST_END_METHOD( KTgS_OK );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- FCN_V(UNIT_TEST__SETUP__MS_Init_VL) -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID FCN_V(UNIT_TEST__SETUP__MS_Init_VL)( VEC_OBJ_T(TgMESH_SIMPLE,PCU) psMS )
{
    tgMM_Set_U08_0x00( psMS, sizeof( VEC_OBJ_T(TgMESH_SIMPLE) ) );

    FCN_VO(tgGM_MS_Init)( psMS, TgARRAY_COUNT(KTgGM_ICOSAHEDRON_PN_INDEX), 0 );

    for (TgRSIZE uiIndx = 0, uiVert; uiIndx < psMS->m_nuiIndx; ++uiIndx)
    {
        uiVert = KTgGM_ICOSAHEDRON_PN_INDEX[uiIndx];
        TgERROR(uiVert < psMS->m_nuiVert);
        psMS->m_pvVert_List[uiVert].m_aData[0] = (VAR_T())KTgGM_ICOSAHEDRON_PN_INDEX_VERTEX[2*uiVert].m_vS_F32_04_1.m_aData[0];
        psMS->m_pvVert_List[uiVert].m_aData[1] = (VAR_T())KTgGM_ICOSAHEDRON_PN_INDEX_VERTEX[2*uiVert].m_vS_F32_04_1.m_aData[1];
        psMS->m_pvVert_List[uiVert].m_aData[2] = (VAR_T())KTgGM_ICOSAHEDRON_PN_INDEX_VERTEX[2*uiVert].m_vS_F32_04_1.m_aData[2];
        psMS->m_pvVert_List[uiVert].m_aData[3] = (VAR_T())KTgGM_ICOSAHEDRON_PN_INDEX_VERTEX[2*uiVert].m_vS_F32_04_1.m_aData[3];
    };
}


/* ---- FCN_V(UNIT_TEST__SETUP__MS_Init_IL) -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID FCN_V(UNIT_TEST__SETUP__MS_Init_IL)( VEC_OBJ_T(TgMESH_SIMPLE,PCU) psMS )
{
    tgMM_Set_U08_0x00( psMS, sizeof( VEC_OBJ_T(TgMESH_SIMPLE) ) );

    FCN_VO(tgGM_MS_Init)( psMS, (TgARRAY_COUNT(KTgGM_ICOSAHEDRON_PN_INDEX_VERTEX) >> 1), TgARRAY_COUNT(KTgGM_ICOSAHEDRON_PN_INDEX) );

    for (TgRSIZE uiVert = 0; uiVert < psMS->m_nuiVert; ++uiVert)
    {
        psMS->m_pvVert_List[uiVert].m_aData[0] = (VAR_T())KTgGM_ICOSAHEDRON_PN_INDEX_VERTEX[2*uiVert].m_vS_F32_04_1.m_aData[0];
        psMS->m_pvVert_List[uiVert].m_aData[1] = (VAR_T())KTgGM_ICOSAHEDRON_PN_INDEX_VERTEX[2*uiVert].m_vS_F32_04_1.m_aData[1];
        psMS->m_pvVert_List[uiVert].m_aData[2] = (VAR_T())KTgGM_ICOSAHEDRON_PN_INDEX_VERTEX[2*uiVert].m_vS_F32_04_1.m_aData[2];
        psMS->m_pvVert_List[uiVert].m_aData[3] = (VAR_T())KTgGM_ICOSAHEDRON_PN_INDEX_VERTEX[2*uiVert].m_vS_F32_04_1.m_aData[3];
    };

    tgMM_Copy( psMS->m_puiIndx_List, psMS->m_nuiIndx*sizeof( psMS->m_puiIndx_List[0] ), KTgGM_ICOSAHEDRON_PN_INDEX, sizeof( KTgGM_ICOSAHEDRON_PN_INDEX ) );
    TgERROR( psMS->m_nuiIndx*sizeof( psMS->m_puiIndx_List[0] ) >= sizeof( KTgGM_ICOSAHEDRON_PN_INDEX ) );
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
