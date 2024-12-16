/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common [Unit Test] [Set] - Math.c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include <math.h>

#include "TgS Common [Unit Test] [Test] - Math [Constants].c_inc"
#include "TgS Common [Unit Test] [Test] - Math [Scalar] [F].c_inc"


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TgEXTN TgVOID
tgCM_Unit_Test_Register_Math_Vector(
    Test_Set * );

TgEXTN TgVOID
tgCM_Unit_Test_Register_Math_Matrix(
    Test_Set * );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Data                                                                                                                                                                */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

static Test_Set                             s_sSET__MATH;
static Test_Case                            s_sCASE__Math_Constant;
static Test_Case                            s_sCASE__Math;




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgCM_Unit_Test_Register_MATH --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgCM_Unit_Test_Register_MATH( TgVOID )
{
    /* Initialize the unit test structures */

    Unit_Test__Set_Init( &s_sSET__MATH );

    Unit_Test__Case_Init( &s_sCASE__Math_Constant );
    Unit_Test__Case_Init( &s_sCASE__Math );



    /* Configure the test set */

    s_sSET__MATH.m_szSet = u8"Common: Math";



    /* Configure the test cases */

    s_sCASE__Math_Constant.m_pszSet = s_sSET__MATH.m_szSet;
    s_sCASE__Math_Constant.m_pszCase = u8"Math Constant";
    s_sCASE__Math_Constant.m_pfnTest[0] = UNIT_TEST__TEST__Math_Constant;
    s_sCASE__Math_Constant.m_apszTest[0] = u8"UNIT_TEST__TEST__Math_Constant";

    s_sCASE__Math.m_pszSet = s_sSET__MATH.m_szSet;
    s_sCASE__Math.m_pszCase = u8"Math Utility";
    s_sCASE__Math.m_pfnTest[0] = UNIT_TEST__TEST__MATH_Vector_F_Algorithm_F32;
    s_sCASE__Math.m_apszTest[0] = u8"Algorithm 32";
    s_sCASE__Math.m_pfnTest[1] = UNIT_TEST__TEST__MATH_Vector_F_Polynomial_F32;
    s_sCASE__Math.m_apszTest[1] = u8"Polynomial 32";
    s_sCASE__Math.m_pfnTest[3] = UNIT_TEST__TEST__MATH_Vector_F_Algorithm_F64;
    s_sCASE__Math.m_apszTest[3] = u8"Algorithm 64";
    s_sCASE__Math.m_pfnTest[4] = UNIT_TEST__TEST__MATH_Vector_F_Polynomial_F64;
    s_sCASE__Math.m_apszTest[4] = u8"Polynomial 64";



    /* Register all of the test cases with the test set */

    Unit_Test__Set_Register_Case( &s_sSET__MATH, &s_sCASE__Math_Constant );
    Unit_Test__Set_Register_Case( &s_sSET__MATH, &s_sCASE__Math );
    tgCM_Unit_Test_Register_Math_Matrix( &s_sSET__MATH );
    tgCM_Unit_Test_Register_Math_Vector( &s_sSET__MATH );



    /* Register the test set with the unit test system */

    Unit_Test__Register( &s_sSET__MATH );
}
