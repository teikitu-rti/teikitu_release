/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common [Unit Test] - Geometry 2D - Rectangle.c
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

TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_Is_Valid_RT2D) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_TX_RT2D) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_Copy_TX_RT2D) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_Init_RT2D) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_Set_X0_RT2D) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_Set_Y0_RT2D) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_Set_X1_RT2D) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_Set_Y1_RT2D) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_Copy_RT2D) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_Query_X0_RT2D) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_Query_X1_RT2D) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_Query_Y0_RT2D) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_Query_Y1_RT2D) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_Query_Width_RT2D) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_Query_Height_RT2D) );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

static TgVOID                               FCN_V(UNIT_TEST__SETUP__RT2D)( VEC_OBJ_T(TgRECT2D,PCU) );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- FCN_V(UNIT_TEST__TEST__GEOM_RT2D) ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V(UNIT_TEST__TEST__GEOM_RT2D) )
{
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_Is_Valid_RT2D)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_TX_RT2D)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_Copy_TX_RT2D)());

    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_Init_RT2D)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_Set_X0_RT2D)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_Set_Y0_RT2D)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_Set_X1_RT2D)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_Set_Y1_RT2D)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_Copy_RT2D)());

    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_Query_X0_RT2D)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_Query_X1_RT2D)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_Query_Y0_RT2D)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_Query_Y1_RT2D)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_Query_Width_RT2D)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_Query_Height_RT2D)());

    TEST_END_METHOD( KTgS_OK );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- FCN_V(UNIT_TEST__TEST__GM_Is_Valid_RT2D) --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_Is_Valid_RT2D) )
{
    VEC_OBJ_T(TgRECT2D)                 sRT2_0;

    FCN_V(UNIT_TEST__SETUP__RT2D)( &sRT2_0 );
    FCN_VO(tgGM_Is_Valid_RT2D)( &sRT2_0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_TX_RT2D) --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_TX_RT2D) )
{
    VEC_OBJ_T(TgRECT2D)                 sRT2_0;

    FCN_V(UNIT_TEST__SETUP__RT2D)( &sRT2_0 );
    FCN_VO(tgGM_TX_RT2D)( &sRT2_0, TYPE_K(1), TYPE_K(1) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_Copy_TX_RT2D) ---------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_Copy_TX_RT2D) )
{
    VEC_OBJ_T(TgRECT2D)                 sRT2_0;

    FCN_V(UNIT_TEST__SETUP__RT2D)( &sRT2_0 );
    FCN_VO(tgGM_Copy_TX_RT2D)( &sRT2_0, &sRT2_0, TYPE_K(1), TYPE_K(1) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_Init_RT2D) ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_Init_RT2D) )
{
    VEC_OBJ_T(TgRECT2D)                 sRT2_0;

    FCN_V(UNIT_TEST__SETUP__RT2D)( &sRT2_0 );
    FCN_VO(tgGM_Init_RT2D)( &sRT2_0, TYPE_K(1), TYPE_K(1), TYPE_K(1), TYPE_K(1) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_Set_X0_RT2D) ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_Set_X0_RT2D) )
{
    VEC_OBJ_T(TgRECT2D)                 sRT2_0;

    FCN_V(UNIT_TEST__SETUP__RT2D)( &sRT2_0 );
    FCN_VO(tgGM_Init_X0_RT2D)( &sRT2_0, TYPE_K(1) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_Set_Y0_RT2D) ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_Set_Y0_RT2D) )
{
    VEC_OBJ_T(TgRECT2D)                 sRT2_0;

    FCN_V(UNIT_TEST__SETUP__RT2D)( &sRT2_0 );
    FCN_VO(tgGM_Init_Y0_RT2D)( &sRT2_0, TYPE_K(1) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_Set_X1_RT2D) ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_Set_X1_RT2D) )
{
    VEC_OBJ_T(TgRECT2D)                 sRT2_0;

    FCN_V(UNIT_TEST__SETUP__RT2D)( &sRT2_0 );
    FCN_VO(tgGM_Init_X1_RT2D)( &sRT2_0, TYPE_K(1) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_Set_Y1_RT2D) ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_Set_Y1_RT2D) )
{
    VEC_OBJ_T(TgRECT2D)                 sRT2_0;

    FCN_V(UNIT_TEST__SETUP__RT2D)( &sRT2_0 );
    FCN_VO(tgGM_Init_Y1_RT2D)( &sRT2_0, TYPE_K(1) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_Copy_RT2D) ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_Copy_RT2D) )
{
    VEC_OBJ_T(TgRECT2D)                 sRT2_0;

    FCN_V(UNIT_TEST__SETUP__RT2D)( &sRT2_0 );
    FCN_VO(tgGM_Copy_RT2D)( &sRT2_0, &sRT2_0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_Query_X0_RT2D) --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_Query_X0_RT2D) )
{
    VEC_OBJ_T(TgRECT2D)                 sRT2_0;

    FCN_V(UNIT_TEST__SETUP__RT2D)( &sRT2_0 );
    FCN_VO(tgGM_Query_X0_RT2D)( &sRT2_0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_Query_X1_RT2D) --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_Query_X1_RT2D) )
{
    VEC_OBJ_T(TgRECT2D)                 sRT2_0;

    FCN_V(UNIT_TEST__SETUP__RT2D)( &sRT2_0 );
    FCN_VO(tgGM_Query_X1_RT2D)( &sRT2_0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_Query_Y0_RT2D) --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_Query_Y0_RT2D) )
{
    VEC_OBJ_T(TgRECT2D)                 sRT2_0;

    FCN_V(UNIT_TEST__SETUP__RT2D)( &sRT2_0 );
    FCN_VO(tgGM_Query_Y0_RT2D)( &sRT2_0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_Query_Y1_RT2D) --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_Query_Y1_RT2D) )
{
    VEC_OBJ_T(TgRECT2D)                 sRT2_0;

    FCN_V(UNIT_TEST__SETUP__RT2D)( &sRT2_0 );
    FCN_VO(tgGM_Query_Y1_RT2D)( &sRT2_0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_Query_Width_RT2D) ------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_Query_Width_RT2D) )
{
    VEC_OBJ_T(TgRECT2D)                 sRT2_0;

    FCN_V(UNIT_TEST__SETUP__RT2D)( &sRT2_0 );
    FCN_VO(tgGM_Query_Width_RT2D)( &sRT2_0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_Query_Height_RT2D) ----------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_Query_Height_RT2D) )
{
    VEC_OBJ_T(TgRECT2D)                 sRT2_0;

    FCN_V(UNIT_TEST__SETUP__RT2D)( &sRT2_0 );
    FCN_VO(tgGM_Query_Height_RT2D)( &sRT2_0 );

    TEST_END_METHOD( KTgS_OK );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

static TgVOID FCN_V(UNIT_TEST__SETUP__RT2D)( VEC_OBJ_T(TgRECT2D,PCU) psRT2D )
{
    tgMM_Set_U08_0x00( psRT2D, sizeof( VEC_OBJ_T(TgRECT2D) ) );

    FCN_VO(tgGM_Init_RT2D)( psRT2D, -TYPE_K(1), -TYPE_K(1), TYPE_K(1), TYPE_K(1) );
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
