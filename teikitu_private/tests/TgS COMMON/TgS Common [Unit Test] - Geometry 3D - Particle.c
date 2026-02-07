/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common [Unit Test] - Geometry 3D - Particle.c
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

TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PC_Reset) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PC_Is_Valid) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PC_BA) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PC_Project) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PC_TX) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PC_Copy_TX) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PC_Init) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PC_Copy) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PC_Set_Position) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PC_Set_Velocity) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PC_Set_Acceleration) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PC_Query_Position) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PC_Query_Velocity) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PC_Query_Acceleration) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PC_Query_Position_Time) );
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PC_Query_Velocity_Time) );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

static TgVOID                               FCN_V(UNIT_TEST__SETUP__PC)( VEC_OBJ_T(TgPARTICLE,PCU) );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- FCN_V(UNIT_TEST__TEST__GEOM_PC) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V(UNIT_TEST__TEST__GEOM_PC) )
{
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_PC_Reset)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_PC_Is_Valid)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_PC_BA)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_PC_Project)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_PC_TX)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_PC_Copy_TX)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_PC_Init)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_PC_Copy)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_PC_Set_Position)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_PC_Set_Velocity)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_PC_Set_Acceleration)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_PC_Query_Position)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_PC_Query_Velocity)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_PC_Query_Acceleration)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_PC_Query_Position_Time)());
    Test__Expect_EQ(KTgS_OK, FCN_V(UNIT_TEST__TEST__GM_PC_Query_Velocity_Time)());

    TEST_END_METHOD( KTgS_OK );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- FCN_V(UNIT_TEST__TEST__GM_PC_Reset) -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PC_Reset) )
{
    VEC_OBJ_T(TgPARTICLE)               sPC0;

    FCN_V(UNIT_TEST__SETUP__PC)( &sPC0 );
    FCN_VO(tgGM_PC_Reset)( &sPC0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_PC_Is_Valid) ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PC_Is_Valid) )
{
    VEC_OBJ_T(TgPARTICLE)               sPC0;

    FCN_V(UNIT_TEST__SETUP__PC)( &sPC0 );
    Test__Expect_EQ( true, FCN_VO(tgGM_PC_Is_Valid)( &sPC0 ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_PC_BA) ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PC_BA) )
{
    VEC_OBJ_T(TgPARTICLE)               sPC0;
    VEC_OBJ_T(TgBOXAA)                  sBA0;

    FCN_V(UNIT_TEST__SETUP__PC)( &sPC0 );
    FCN_VO(tgGM_PC_BA)( &sBA0, &sPC0, FCN_V(tgMH_SET1)( TYPE_K(1) ) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_PC_Project) ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PC_Project) )
{
    VEC_OBJ_T(TgPARTICLE)               sPC0;
    VEC_T(1)                            vV0, vVal;

    vV0 = FCN_V(tgMH_Init_Vector_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vV0 = FCN_V(tgMH_NORM)( vV0 );
    FCN_V(UNIT_TEST__SETUP__PC)( &sPC0 );
    FCN_VO(tgGM_PC_Project)( &vVal, &vVal, &sPC0, vV0, FCN_V(tgMH_SET1)( TYPE_K(0,95) ) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_PC_TX) ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PC_TX) )
{
    VEC_OBJ_T(TgPARTICLE)               sPC0;
    VEC_T(3)                            xM0;

    FCN_V(tgMH_CLI,3)( &xM0 );
    FCN_V(UNIT_TEST__SETUP__PC)( &sPC0 );
    FCN_VO(tgGM_PC_TX)( &sPC0, &xM0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_PC_Copy_TX) ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PC_Copy_TX) )
{
    VEC_OBJ_T(TgPARTICLE)               sPC0;
    VEC_T(3)                            xM0;

    FCN_V(tgMH_CLI,3)( &xM0 );
    FCN_V(UNIT_TEST__SETUP__PC)( &sPC0 );
    FCN_VO(tgGM_PC_Copy_TX)( &sPC0, &sPC0, &xM0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_PC_Init) --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PC_Init) )
{
    VEC_OBJ_T(TgPARTICLE)               sPC0;

    FCN_V(UNIT_TEST__SETUP__PC)( &sPC0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_PC_Copy) --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PC_Copy) )
{
    VEC_OBJ_T(TgPARTICLE)               sPC0;

    FCN_V(UNIT_TEST__SETUP__PC)( &sPC0 );
    FCN_VO(tgGM_PC_Copy)( &sPC0, &sPC0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_PC_Set_Position) ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PC_Set_Position) )
{
    VEC_OBJ_T(TgPARTICLE)               sPC0;
    VEC_T(1)                            vS0;

    vS0 = FCN_V(tgMH_Init_Point_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    FCN_V(UNIT_TEST__SETUP__PC)( &sPC0 );
    FCN_VO(tgGM_PC_Set_Position)( &sPC0, vS0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_PC_Set_Velocity) ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PC_Set_Velocity) )
{
    VEC_OBJ_T(TgPARTICLE)               sPC0;
    VEC_T(1)                            vV0;

    vV0 = FCN_V(tgMH_Init_Vector_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vV0 = FCN_V(tgMH_NORM)( vV0 );
    FCN_V(UNIT_TEST__SETUP__PC)( &sPC0 );
    FCN_VO(tgGM_PC_Set_Velocity)( &sPC0, vV0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_PC_Set_Acceleration) --------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PC_Set_Acceleration) )
{
    VEC_OBJ_T(TgPARTICLE)               sPC0;
    VEC_T(1)                            vV0;

    vV0 = FCN_V(tgMH_Init_Vector_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vV0 = FCN_V(tgMH_NORM)( vV0 );
    FCN_V(UNIT_TEST__SETUP__PC)( &sPC0 );
    FCN_VO(tgGM_PC_Set_Acceleration)( &sPC0, vV0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_PC_Query_Position) ----------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PC_Query_Position) )
{
    VEC_OBJ_T(TgPARTICLE)               sPC0;

    FCN_V(UNIT_TEST__SETUP__PC)( &sPC0 );
    FCN_VO(tgGM_PC_Query_Position)( &sPC0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_PC_Query_Velocity) ----------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PC_Query_Velocity) )
{
    VEC_OBJ_T(TgPARTICLE)               sPC0;

    FCN_V(UNIT_TEST__SETUP__PC)( &sPC0 );
    FCN_VO(tgGM_PC_Query_Velocity)( &sPC0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_PC_Query_Acceleration) ------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PC_Query_Acceleration) )
{
    VEC_OBJ_T(TgPARTICLE)               sPC0;

    FCN_V(UNIT_TEST__SETUP__PC)( &sPC0 );
    FCN_VO(tgGM_PC_Query_Acceleration)( &sPC0 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_PC_Query_Position_Time) ------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PC_Query_Position_Time) )
{
    VEC_OBJ_T(TgPARTICLE)               sPC0;

    FCN_V(UNIT_TEST__SETUP__PC)( &sPC0 );
    FCN_VO(tgGM_PC_Query_Position_Time)( &sPC0, FCN_V(tgMH_SET1)( TYPE_K(1) ) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V(UNIT_TEST__TEST__GM_PC_Query_Velocity_Time) ------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( FCN_V(UNIT_TEST__TEST__GM_PC_Query_Velocity_Time) )
{
    VEC_OBJ_T(TgPARTICLE)               sPC0;

    FCN_V(UNIT_TEST__SETUP__PC)( &sPC0 );
    FCN_VO(tgGM_PC_Query_Velocity_Time)( &sPC0, FCN_V(tgMH_SET1)( TYPE_K(1) ) );

    TEST_END_METHOD( KTgS_OK );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

static TgVOID FCN_V(UNIT_TEST__SETUP__PC)( VEC_OBJ_T(TgPARTICLE,PCU) psPC )
{
    VEC_T(1)                            vS0, vV0, vV1;

    vS0 = FCN_V(tgMH_Init_Point_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );

    vV0 = FCN_V(tgMH_Init_Vector_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vV0 = FCN_V(tgMH_NORM)( vV0 );

    vV1 = FCN_V(tgMH_Init_Vector_ELEM)( FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)(), FCN_F(tgCM_RAND)() );
    vV1 = FCN_V(tgMH_NORM)( vV0 );

    FCN_VO(tgGM_PC_Init)( psPC, vS0, vV0, vV1 );
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
