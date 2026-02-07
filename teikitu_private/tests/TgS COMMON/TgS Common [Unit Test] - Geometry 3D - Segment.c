/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common [Unit Test] - Geometry 3D - Segment.c
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

TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_SG_Reset) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_SG_Is_Valid) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_SG_BA) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_SG_Sweep_BA) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_SG_Project) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_SG_Is_Contained) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_SG_TX) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_SG_Copy_TX) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_SG_Init) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_SG_Copy) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_SG_Set_Origin) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_SG_Set_DirN) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_SG_Query_Origin) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_SG_Query_DirN) );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

static TgVOID                               FCN_V(UNIT_TEST__SETUP__SG)( VEC_OBJ_T(TgSEGMENT,PCU) );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- FCN_V(UNIT_TEST__TEST__GEOM_SG) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V(UNIT_TEST__TEST__GEOM_SG) )
{
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_SG_Reset)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_SG_Is_Valid)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_SG_BA)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_SG_Sweep_BA)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_SG_Project)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_SG_Is_Contained)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_SG_TX)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_SG_Copy_TX)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_SG_Init)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_SG_Copy)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_SG_Set_Origin)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_SG_Set_DirN)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_SG_Query_Origin)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_SG_Query_DirN)());

    TEST_END_METHOD( KTgS_OK );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- FCN_V(UNIT_TEST__TEST__GM_SG_Reset) -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_SG_Reset) )
{
    VEC_OBJ_T(TgSEGMENT)                sSG0;

    FCN_V(UNIT_TEST__SETUP__SG)( &sSG0 );
    FCN_VO(tgGM_SG_Reset)( &sSG0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_SG_Is_Valid) ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_SG_Is_Valid) )
{
    VEC_OBJ_T(TgSEGMENT)                sSG0;

    FCN_V(UNIT_TEST__SETUP__SG)( &sSG0 );
    Test__Expect_EQ( true, FCN_VO(tgGM_SG_Is_Valid)( &sSG0 ));
    FCN_VO(tgGM_SG_Reset)( &sSG0 );
    Test__Expect_EQ(false, FCN_VO(tgGM_SG_Is_Valid)( &sSG0 ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_SG_BA) ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_SG_BA) )
{
    VEC_OBJ_T(TgSEGMENT)                sSG0;
    VEC_OBJ_T(TgBOXAA)                  sBA0;

    FCN_V(UNIT_TEST__SETUP__SG)( &sSG0 );
    FCN_VO(tgGM_SG_BA)( &sBA0, &sSG0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_SG_Sweep_BA) ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_SG_Sweep_BA) )
{
    VEC_OBJ_T(TgSEGMENT)                sSG0;
    VEC_OBJ_T(TgBOXAA)                  sBA0;
    VEC_T(1)                            vV0;

    vV0 = FCN_V(tgMH_Init_Vector_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vV0 = FCN_V(tgMH_NORM)( vV0 );
    FCN_V(UNIT_TEST__SETUP__SG)( &sSG0 );
    FCN_VO(tgGM_SG_Sweep_BA)( &sBA0, &sSG0, vV0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_SG_Project) ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_SG_Project) )
{
    VEC_OBJ_T(TgSEGMENT)                sSG0;
    VEC_T(1)                            vV0, vVal;

    vV0 = FCN_V(tgMH_Init_Vector_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vV0 = FCN_V(tgMH_NORM)( vV0 );
    FCN_V(UNIT_TEST__SETUP__SG)( &sSG0 );
    FCN_VO(tgGM_SG_Project)( &vVal, &vVal, &sSG0, vV0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_SG_Is_Contained) ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_SG_Is_Contained) )
{
    VEC_OBJ_T(TgSEGMENT)                sSG0;
    VEC_T(1)                            vS0;

    vS0 = FCN_V(tgMH_Init_Point_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    FCN_V(UNIT_TEST__SETUP__SG)( &sSG0 );
    FCN_VO(tgGM_SG_Is_Contained)( &sSG0, vS0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_SG_TX) ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_SG_TX) )
{
    VEC_OBJ_T(TgSEGMENT)                sSG0;
    VEC_T(3)                            xM0;

    FCN_V(tgMH_CLI,3)( &xM0 );
    FCN_V(UNIT_TEST__SETUP__SG)( &sSG0 );
    FCN_VO(tgGM_SG_TX)( &sSG0, &xM0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_SG_Copy_TX) ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_SG_Copy_TX) )
{
    VEC_OBJ_T(TgSEGMENT)                sSG0;
    VEC_T(3)                            xM0;

    FCN_V(tgMH_CLI,3)( &xM0 );
    FCN_V(UNIT_TEST__SETUP__SG)( &sSG0 );
    FCN_VO(tgGM_SG_Copy_TX)( &sSG0, &sSG0, &xM0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_SG_Init) --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_SG_Init) )
{
    VEC_OBJ_T(TgSEGMENT)                sSG0;
    VEC_T(1)                            vV0;
    VEC_T(1)                            vS0;

    vS0 = FCN_V(tgMH_Init_Point_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vV0 = FCN_V(tgMH_Init_Vector_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vV0 = FCN_V(tgMH_NORM)( vV0 );
    FCN_VO(tgGM_SG_Init)( &sSG0, vS0, vV0 );
    Test__Expect_EQ(true, FCN_VO(tgGM_SG_Is_Valid)( &sSG0 ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_SG_Copy) --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_SG_Copy) )
{
    VEC_OBJ_T(TgSEGMENT)                sSG0;

    FCN_V(UNIT_TEST__SETUP__SG)( &sSG0 );
    FCN_VO(tgGM_SG_Copy)( &sSG0, &sSG0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_SG_Set_Origin) --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_SG_Set_Origin) )
{
    VEC_OBJ_T(TgSEGMENT)                sSG0;
    VEC_T(1)                            vS0;

    vS0 = FCN_V(tgMH_Init_Point_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    FCN_V(UNIT_TEST__SETUP__SG)( &sSG0 );
    FCN_VO(tgGM_SG_Set_Origin)( &sSG0, vS0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_SG_Set_DirN) ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_SG_Set_DirN) )
{
    VEC_OBJ_T(TgSEGMENT)                sSG0;
    VEC_T(1)                            vV0;

    vV0 = FCN_V(tgMH_Init_Vector_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vV0 = FCN_V(tgMH_NORM)( vV0 );
    FCN_V(UNIT_TEST__SETUP__SG)( &sSG0 );
    FCN_VO(tgGM_SG_Set_DirN)( &sSG0, vV0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_SG_Query_Origin) ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_SG_Query_Origin) )
{
    VEC_OBJ_T(TgSEGMENT)                sSG0;

    FCN_V(UNIT_TEST__SETUP__SG)( &sSG0 );
    FCN_VO(tgGM_SG_Query_Origin)( &sSG0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_SG_Query_DirN) --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_SG_Query_DirN) )
{
    VEC_OBJ_T(TgSEGMENT)                sSG0;

    FCN_V(UNIT_TEST__SETUP__SG)( &sSG0 );
    FCN_VO(tgGM_SG_Query_DirN)( &sSG0 );

    TEST_END_METHOD( KTgS_OK );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

static TgVOID FCN_V(UNIT_TEST__SETUP__SG)( VEC_OBJ_T(TgSEGMENT,PCU) psSG )
{
    VEC_T(1)                            vS0, vV0;

    vV0 = FCN_V(tgMH_Init_Vector_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vS0 = FCN_V(tgMH_Init_Point_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );

    FCN_VO(tgGM_SG_Init)( psSG, vS0, vV0 );
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
