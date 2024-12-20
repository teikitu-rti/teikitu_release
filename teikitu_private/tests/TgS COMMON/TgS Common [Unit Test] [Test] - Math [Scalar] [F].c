/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common [Unit Test] - Math [F].c_inc
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#if !defined (ENABLE_RELOAD_GUARD)
    #define ENABLE_RELOAD_GUARD
    #if !defined(TEMPLATE__TYPE_SIZE)
        #define TEMPLATE__TYPE_SIZE 32
        #include __FILE__
        #undef TEMPLATE__TYPE_SIZE
        #define TEMPLATE__TYPE_SIZE 64
    #endif
    #undef ENABLE_RELOAD_GUARD
#endif

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- FCN_F(Brent_Unit_Test) --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static VAR_T() FCN_F(Brent_Unit_Test)( TgATTRIBUTE_UNUSED TgVOID_PCU pVoid, VAR_T(C) fK ) TgATTRIBUTE_NO_EXCEPT
{
    return (fK);
}


/* ---- FCN_F(UNIT_TEST__TEST__MATH_Vector_F_Algorithm) -------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_F(UNIT_TEST__TEST__MATH_Vector_F_Algorithm) )
{
    VAR_T()                             fK0, fK1, fK2, fK3, fK4, fK5;

    fK0 = fK1 = fK2 = fK3 = fK4 = fK5 = TYPE_K(1);
    FCN_F(tgMH_BrentZ)( &fK0, &fK1, FCN_F(Brent_Unit_Test), fK1, fK2 );
    FCN_F(tgMH_BrentD)( &fK0, &fK1, &fK2, FCN_F(Brent_Unit_Test), FCN_F(Brent_Unit_Test), fK3, fK4, fK5 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_F(UNIT_TEST__TEST__MATH_Vector_F_Polynomial) ------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_F(UNIT_TEST__TEST__MATH_Vector_F_Polynomial) )
{
    VAR_T()                             fK0, fK1, fK2, fK3, fK4;
    TgSINT_E32                          niRoot;
    VAR_T()                             aRoot[4];

    fK0 = fK1 = fK2 = fK3 = fK4 = TYPE_K(1);
    FCN_F(tgMH_Calc_Root_1)( aRoot, &niRoot, fK0, fK1 );
    FCN_F(tgMH_Calc_Root_2)( aRoot, &niRoot, fK0, fK1, fK2 );
    FCN_F(tgMH_Calc_Root_3)( aRoot, &niRoot, fK0, fK1, fK2, fK3 );
    FCN_F(tgMH_Calc_Root_4)( aRoot, &niRoot, fK0, fK1, fK2, fK3, fK4 );

    TEST_END_METHOD( KTgS_OK );
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
