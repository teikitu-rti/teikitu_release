/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common [Unit Test] - Geometry 3D - Line.c
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

TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_LN_Reset) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_LN_Is_Valid) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_LN_BA) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_LN_Sweep_BA) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_LN_Project) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_LN_Is_Contained) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_LN_TX) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_LN_Copy_TX) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_LN_Init) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_LN_Copy) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_LN_Set_Origin) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_LN_Set_DirN) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_LN_Query_Origin) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_LN_Query_DirN) );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

static TgVOID                               FCN_V(UNIT_TEST__SETUP__LN)( VEC_OBJ_T(TgLINE,PCU) );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- FCN_V(UNIT_TEST__TEST__GEOM_LN) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V(UNIT_TEST__TEST__GEOM_LN) )
{
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_LN_Reset)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_LN_Is_Valid)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_LN_BA)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_LN_Sweep_BA)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_LN_Project)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_LN_Is_Contained)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_LN_TX)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_LN_Copy_TX)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_LN_Init)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_LN_Copy)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_LN_Set_Origin)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_LN_Set_DirN)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_LN_Query_Origin)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_LN_Query_DirN)());

    TEST_END_METHOD( KTgS_OK );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- FCN_V(UNIT_TEST__TEST__GM_LN_Reset) -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_LN_Reset) )
{
    VEC_OBJ_T(TgLINE)                   sLN0;

    FCN_V(UNIT_TEST__SETUP__LN)( &sLN0 );
    FCN_VO(tgGM_LN_Reset)( &sLN0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_LN_Is_Valid) ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_LN_Is_Valid) )
{
    VEC_OBJ_T(TgLINE)                   sLN0;

    FCN_V(UNIT_TEST__SETUP__LN)( &sLN0 );
    Test__Expect_EQ(true, FCN_VO(tgGM_LN_Is_Valid)( &sLN0 ));
    FCN_VO(tgGM_LN_Reset)( &sLN0 );
    Test__Expect_EQ(false, FCN_VO(tgGM_LN_Is_Valid)( &sLN0 ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_LN_BA) ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_LN_BA) )
{
    VEC_OBJ_T(TgLINE)                   sLN0;
    VEC_OBJ_T(TgBOXAA)                  sBA0;

    FCN_V(UNIT_TEST__SETUP__LN)( &sLN0 );
    FCN_VO(tgGM_LN_BA)( &sBA0, &sLN0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_LN_Sweep_BA) ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_LN_Sweep_BA) )
{
    VEC_OBJ_T(TgLINE)                   sLN0;
    VEC_OBJ_T(TgBOXAA)                  sBA0;
    VEC_T(1)                            vV0;

    vV0 = FCN_V(tgMH_Init_Vector_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vV0 = FCN_V(tgMH_NORM)( vV0 );
    FCN_V(UNIT_TEST__SETUP__LN)( &sLN0 );
    FCN_VO(tgGM_LN_Sweep_BA)( &sBA0, &sLN0, vV0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_LN_Project) ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_LN_Project) )
{
    VEC_OBJ_T(TgLINE)                   sLN0;
    VEC_T(1)                            vV0;
    VEC_T(1)                            fVal;

    vV0 = FCN_V(tgMH_Init_Vector_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vV0 = FCN_V(tgMH_NORM)( vV0 );
    FCN_V(UNIT_TEST__SETUP__LN)( &sLN0 );
    FCN_VO(tgGM_LN_Project)( &fVal, &fVal, &sLN0, vV0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_LN_Is_Contained) ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_LN_Is_Contained) )
{
    VEC_OBJ_T(TgLINE)                   sLN0;
    VEC_T(1)                            vS0, vS1;

    vS1 = FCN_V(tgMH_Init_Point_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    FCN_V(UNIT_TEST__SETUP__LN)( &sLN0 );
    vS0 = sLN0.m_vOrigin;
    Test__Expect_EQ(true, FCN_VO(tgGM_LN_Is_Contained)( &sLN0, vS0 ));
    Test__Expect_EQ(false, FCN_VO(tgGM_LN_Is_Contained)( &sLN0, vS1 ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_LN_TX) ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_LN_TX) )
{
    VEC_OBJ_T(TgLINE)                   sLN0;
    VEC_T(3)                            xM0;

    FCN_V(tgMH_CLI,3)( &xM0 );
    FCN_V(UNIT_TEST__SETUP__LN)( &sLN0 );
    FCN_VO(tgGM_LN_TX)( &sLN0, &xM0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_LN_Copy_TX) ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_LN_Copy_TX) )
{
    VEC_OBJ_T(TgLINE)                   sLN0;
    VEC_T(3)                            xM0;

    FCN_V(tgMH_CLI,3)( &xM0 );
    FCN_V(UNIT_TEST__SETUP__LN)( &sLN0 );
    FCN_VO(tgGM_LN_Copy_TX)( &sLN0, &sLN0, &xM0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_LN_Init) --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_LN_Init) )
{
    VEC_OBJ_T(TgLINE)                   sLN0;
    VEC_T(1)                            vS0;
    VEC_T(1)                            vV0;

    vV0 = FCN_V(tgMH_Init_Vector_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vV0 = FCN_V(tgMH_NORM)( vV0 );
    vS0 = FCN_V(tgMH_Init_Point_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );

    FCN_VO(tgGM_LN_Init)( &sLN0, vS0, vV0 );

    Test__Expect_EQ(true, FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_EQ)( vS0, FCN_VO(tgGM_LN_Query_Origin)( &sLN0 ) ) ));
    Test__Expect_EQ(true, FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_EQ)( vV0, FCN_VO(tgGM_LN_Query_DirN)( &sLN0 ) ) ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_LN_Copy) --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_LN_Copy) )
{
    VEC_OBJ_T(TgLINE)                   sLN0, sLN1;

    FCN_V(UNIT_TEST__SETUP__LN)( &sLN0 );
    FCN_VO(tgGM_LN_Copy)( &sLN1, &sLN0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_LN_Set_Origin) --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_LN_Set_Origin) )
{
    VEC_OBJ_T(TgLINE)                   sLN0;
    VEC_T(1)                            vS0;

    vS0 = FCN_V(tgMH_Init_Point_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    FCN_V(UNIT_TEST__SETUP__LN)( &sLN0 );
    FCN_VO(tgGM_LN_Set_Origin)( &sLN0, vS0 );
    Test__Expect_EQ(true, FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_EQ)( vS0, FCN_VO(tgGM_LN_Query_Origin)( &sLN0 ) ) ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_LN_Set_DirN) ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_LN_Set_DirN) )
{
    VEC_OBJ_T(TgLINE)                   sLN0;
    VEC_T(1)                            vV0;

    vV0 = FCN_V(tgMH_Init_Vector_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vV0 = FCN_V(tgMH_NORM)( vV0 );
    FCN_V(UNIT_TEST__SETUP__LN)( &sLN0 );
    FCN_VO(tgGM_LN_Set_DirN)( &sLN0, vV0 );
    Test__Expect_EQ(true, FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_EQ)( vV0, FCN_VO(tgGM_LN_Query_DirN)( &sLN0 ) ) ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_LN_Query_Origin) ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_LN_Query_Origin) )
{
    VEC_OBJ_T(TgLINE)                   sLN0;

    FCN_V(UNIT_TEST__SETUP__LN)( &sLN0 );
    FCN_VO(tgGM_LN_Query_Origin)( &sLN0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_LN_Query_DirN) --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_LN_Query_DirN) )
{
    VEC_OBJ_T(TgLINE)                   sLN0;

    FCN_V(UNIT_TEST__SETUP__LN)( &sLN0 );
    FCN_VO(tgGM_LN_Query_DirN)( &sLN0 );

    TEST_END_METHOD( KTgS_OK );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

static TgVOID FCN_V(UNIT_TEST__SETUP__LN)( VEC_OBJ_T(TgLINE,PCU) psLN )
{
    VEC_T(1)                            vS0, vV0;

    vV0 = FCN_V(tgMH_Init_Vector_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vV0 = FCN_V(tgMH_NORM)( vV0 );

    vS0 = FCN_V(tgMH_Init_Point_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );

    FCN_VO(tgGM_LN_Init)( psLN, vS0, vV0 );
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
