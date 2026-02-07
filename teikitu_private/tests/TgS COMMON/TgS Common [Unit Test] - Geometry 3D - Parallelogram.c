/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common [Unit Test] - Geometry 3D - Parallelogram.c
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

TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PE_Reset) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PE_Is_Valid) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PE_Support_Point) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PE_Area) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PE_BA) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PE_Sweep_BA) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PE_Project) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PE_Is_Contained) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PE_TX) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PE_Copy_TX) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PE_Init) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PE_Copy) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PE_Set_Origin) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PE_Set_Edge) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PE_Query_Origin) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PE_Query_Edge_0) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PE_Query_Edge_1) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PE_Query_Normal) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PE_Query_Edge_Normal_0) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PE_Query_Edge_Normal_1) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PE_Query_Point_0) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PE_Query_Point_1) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PE_Query_Point_2) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PE_Query_Point_3) );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

static TgVOID                               FCN_V(UNIT_TEST__SETUP__PE)( VEC_OBJ_T(TgPARALLELOGRAM,PCU) );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- FCN_V(UNIT_TEST__TEST__GEOM_PE) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V(UNIT_TEST__TEST__GEOM_PE) )
{
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_PE_Reset)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_PE_Is_Valid)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_PE_Support_Point)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_PE_Area)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_PE_BA)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_PE_Sweep_BA)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_PE_Project)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_PE_Is_Contained)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_PE_TX)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_PE_Copy_TX)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_PE_Init)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_PE_Copy)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_PE_Set_Origin)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_PE_Set_Edge)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_PE_Query_Origin)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_PE_Query_Edge_0)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_PE_Query_Edge_1)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_PE_Query_Normal)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_PE_Query_Edge_Normal_0)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_PE_Query_Edge_Normal_1)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_PE_Query_Point_0)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_PE_Query_Point_1)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_PE_Query_Point_2)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_PE_Query_Point_3)());

    TEST_END_METHOD( KTgS_OK );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- FCN_V(UNIT_TEST__TEST__GM_PE_Reset) -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PE_Reset) )
{
    VEC_OBJ_T(TgPARALLELOGRAM)          sPE0;

    FCN_V(UNIT_TEST__SETUP__PE)( &sPE0 );
    FCN_VO(tgGM_PE_Reset)( &sPE0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_PE_Is_Valid) ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PE_Is_Valid) )
{
    VEC_OBJ_T(TgPARALLELOGRAM)          sPE0;

    FCN_V(UNIT_TEST__SETUP__PE)( &sPE0 );
    Test__Expect_EQ( true, FCN_VO(tgGM_PE_Is_Valid)( &sPE0 ));

    FCN_VO(tgGM_PE_Reset)( &sPE0 );
    Test__Expect_EQ(false, FCN_VO(tgGM_PE_Is_Valid)( &sPE0 ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_PE_Support_Point) ------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PE_Support_Point) )
{
    VEC_OBJ_T(TgPARALLELOGRAM)          sPE0;
    VEC_T(1)                            vV0;

    vV0 = FCN_V(tgMH_Init_Vector_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vV0 = FCN_V(tgMH_NORM)( vV0 );
    FCN_V(UNIT_TEST__SETUP__PE)( &sPE0 );
    FCN_VO(tgGM_PE_Support_Point)( &sPE0, vV0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_PE_Area) --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PE_Area) )
{
    VEC_OBJ_T(TgPARALLELOGRAM)          sPE0;

    FCN_V(UNIT_TEST__SETUP__PE)( &sPE0 );
    FCN_VO(tgGM_PE_Area)( &sPE0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_PE_BA) ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PE_BA) )
{
    VEC_OBJ_T(TgBOXAA)                  sBA0;
    VEC_OBJ_T(TgPARALLELOGRAM)          sPE0;

    FCN_V(UNIT_TEST__SETUP__PE)( &sPE0 );
    FCN_VO(tgGM_PE_BA)( &sBA0, &sPE0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_PE_Sweep_BA) ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PE_Sweep_BA) )
{
    VEC_OBJ_T(TgBOXAA)                  sBA0;
    VEC_OBJ_T(TgPARALLELOGRAM)          sPE0;
    VEC_T(1)                            vV0;

    vV0 = FCN_V(tgMH_Init_Vector_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vV0 = FCN_V(tgMH_NORM)( vV0 );
    FCN_V(UNIT_TEST__SETUP__PE)( &sPE0 );
    FCN_VO(tgGM_PE_Sweep_BA)( &sBA0, &sPE0, vV0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_PE_Project) ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PE_Project) )
{
    VEC_OBJ_T(TgPARALLELOGRAM)          sPE0;
    VEC_T(1)                            vV0, vVal;

    vV0 = FCN_V(tgMH_Init_Vector_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vV0 = FCN_V(tgMH_NORM)( vV0 );
    FCN_V(UNIT_TEST__SETUP__PE)( &sPE0 );
    FCN_VO(tgGM_PE_Project)( &vVal, &vVal, &sPE0, vV0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_PE_Is_Contained) ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PE_Is_Contained) )
{
    VEC_OBJ_T(TgPARALLELOGRAM)          sPE0;
    VEC_T(1)                            vS0;

    vS0 = FCN_V(tgMH_Init_Point_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    FCN_V(UNIT_TEST__SETUP__PE)( &sPE0 );
    FCN_VO(tgGM_PE_Is_Contained)( &sPE0, vS0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_PE_TX) ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PE_TX) )
{
    VEC_OBJ_T(TgPARALLELOGRAM)          sPE0;
    VEC_T(3)                            xM0;

    FCN_V(tgMH_CLI,3)( &xM0 );
    FCN_V(UNIT_TEST__SETUP__PE)( &sPE0 );
    FCN_VO(tgGM_PE_TX)( &sPE0, &xM0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_PE_Copy_TX) ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PE_Copy_TX) )
{
    VEC_OBJ_T(TgPARALLELOGRAM)          sPE0, sPE1;
    VEC_T(3)                            xM0;

    FCN_V(tgMH_CLI,3)( &xM0 );
    FCN_V(UNIT_TEST__SETUP__PE)( &sPE0 );
    FCN_VO(tgGM_PE_Copy_TX)( &sPE1, &sPE0, &xM0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_PE_Init) --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PE_Init) )
{


    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_PE_Copy) --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PE_Copy) )
{
    VEC_OBJ_T(TgPARALLELOGRAM)          sPE0;

    FCN_V(UNIT_TEST__SETUP__PE)( &sPE0 );
    FCN_VO(tgGM_PE_Copy)( &sPE0, &sPE0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_PE_Set_Origin) --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PE_Set_Origin) )
{
    VEC_OBJ_T(TgPARALLELOGRAM)          sPE0;
    VEC_T(1)                            vS0;

    vS0 = FCN_V(tgMH_Init_Point_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    FCN_V(UNIT_TEST__SETUP__PE)( &sPE0 );
    FCN_VO(tgGM_PE_Set_Origin)( &sPE0, vS0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_PE_Set_Edge) ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PE_Set_Edge) )
{
    VEC_OBJ_T(TgPARALLELOGRAM)          sPE0;
    VEC_T(1)                            vV0;

    vV0 = FCN_V(tgMH_Init_Vector_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vV0 = FCN_V(tgMH_NORM)( vV0 );
    FCN_V(UNIT_TEST__SETUP__PE)( &sPE0 );
    FCN_VO(tgGM_PE_Set_Edge)( &sPE0, vV0, vV0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_PE_Query_Origin) ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PE_Query_Origin) )
{
    VEC_OBJ_T(TgPARALLELOGRAM)          sPE0;

    FCN_V(UNIT_TEST__SETUP__PE)( &sPE0 );
    FCN_VO(tgGM_PE_Query_Origin)( &sPE0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_PE_Query_Edge_0) ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PE_Query_Edge_0) )
{
    VEC_OBJ_T(TgPARALLELOGRAM)          sPE0;

    FCN_V(UNIT_TEST__SETUP__PE)( &sPE0 );
    FCN_VO(tgGM_PE_Query_Edge_0)( &sPE0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_PE_Query_Edge_1) ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PE_Query_Edge_1) )
{
    VEC_OBJ_T(TgPARALLELOGRAM)          sPE0;

    FCN_V(UNIT_TEST__SETUP__PE)( &sPE0 );
    FCN_VO(tgGM_PE_Query_Edge_1)( &sPE0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_PE_Query_Normal) ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PE_Query_Normal) )
{
    VEC_OBJ_T(TgPARALLELOGRAM)          sPE0;

    FCN_V(UNIT_TEST__SETUP__PE)( &sPE0 );
    FCN_VO(tgGM_PE_Query_Normal)( &sPE0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_PE_Query_Edge_Normal_0) ------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PE_Query_Edge_Normal_0) )
{
    VEC_OBJ_T(TgPARALLELOGRAM)          sPE0;

    FCN_V(UNIT_TEST__SETUP__PE)( &sPE0 );
    FCN_VO(tgGM_PE_Query_Edge_Normal_0)( &sPE0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_PE_Query_Edge_Normal_1) ------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PE_Query_Edge_Normal_1) )
{
    VEC_OBJ_T(TgPARALLELOGRAM)          sPE0;

    FCN_V(UNIT_TEST__SETUP__PE)( &sPE0 );
    FCN_VO(tgGM_PE_Query_Edge_Normal_1)( &sPE0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_PE_Query_Point_0) ------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PE_Query_Point_0) )
{
    VEC_OBJ_T(TgPARALLELOGRAM)          sPE0;

    FCN_V(UNIT_TEST__SETUP__PE)( &sPE0 );
    FCN_VO(tgGM_PE_Query_Point_0)( &sPE0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_PE_Query_Point_1) ------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PE_Query_Point_1) )
{
    VEC_OBJ_T(TgPARALLELOGRAM)          sPE0;

    FCN_V(UNIT_TEST__SETUP__PE)( &sPE0 );
    FCN_VO(tgGM_PE_Query_Point_1)( &sPE0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_PE_Query_Point_2) ------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PE_Query_Point_2) )
{
    VEC_OBJ_T(TgPARALLELOGRAM)          sPE0;

    FCN_V(UNIT_TEST__SETUP__PE)( &sPE0 );
    FCN_VO(tgGM_PE_Query_Point_2)( &sPE0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_PE_Query_Point_3) ------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PE_Query_Point_3) )
{
    VEC_OBJ_T(TgPARALLELOGRAM)          sPE0;

    FCN_V(UNIT_TEST__SETUP__PE)( &sPE0 );
    FCN_VO(tgGM_PE_Query_Point_3)( &sPE0 );

    TEST_END_METHOD( KTgS_OK );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

static TgVOID FCN_V(UNIT_TEST__SETUP__PE)( VEC_OBJ_T(TgPARALLELOGRAM,PCU) psPE )
{
    VEC_T(1)                            vS0, vV0, vV1, vNM;
    VEC_UN_T(1)                         uU0;

    vS0 = FCN_V(tgMH_Init_Point_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    do
    {
        vV0 = FCN_V(tgMH_Init_Vector_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
        vV0 = FCN_V(tgMH_NORM)( vV0 );
        vV1 = FCN_V(tgMH_Init_Vector_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
        vV1 = FCN_V(tgMH_NORM)( vV1 );
        VEC_UN_1_MEMBER(uU0) = FCN_V(tgMH_DOT)( vV0, vV1 );
    }
    while (VEC_S_UN_1_MEMBER(uU0).x > TYPE_K(0,95));

    vNM = FCN_V(tgMH_UCX)( vV0, vV1 );

    tgMM_Set_U08_0x00( psPE, sizeof( VEC_OBJ_T(TgPARALLELOGRAM) ) );

    FCN_VO(tgGM_PE_Init)( psPE, vS0, vV0, vV1, vNM );
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
