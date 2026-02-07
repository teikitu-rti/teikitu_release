/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common [Unit Test] [Case] - Base - API.c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TgEXTN TgVOID
tgCM_Unit_Test_Register_Base_API(
    Test_Set *);




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Tests                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

EXTN_METHOD_DECLARE( UNIT_TEST__TEST__BASE_API_MATH_S08 );
EXTN_METHOD_DECLARE( UNIT_TEST__TEST__BASE_API_MATH_U08 );
EXTN_METHOD_DECLARE( UNIT_TEST__TEST__BASE_API_MATH_S16 );
EXTN_METHOD_DECLARE( UNIT_TEST__TEST__BASE_API_MATH_U16 );
EXTN_METHOD_DECLARE( UNIT_TEST__TEST__BASE_API_MATH_S32 );
EXTN_METHOD_DECLARE( UNIT_TEST__TEST__BASE_API_MATH_U32 );
EXTN_METHOD_DECLARE( UNIT_TEST__TEST__BASE_API_MATH_S64 );
EXTN_METHOD_DECLARE( UNIT_TEST__TEST__BASE_API_MATH_U64 );
EXTN_METHOD_DECLARE( UNIT_TEST__TEST__BASE_API_MATH_SPTR );
EXTN_METHOD_DECLARE( UNIT_TEST__TEST__BASE_API_MATH_UPTR );
EXTN_METHOD_DECLARE( UNIT_TEST__TEST__BASE_API_MATH_SMAX );
EXTN_METHOD_DECLARE( UNIT_TEST__TEST__BASE_API_MATH_UMAX );
EXTN_METHOD_DECLARE( UNIT_TEST__TEST__BASE_API_MATH_F32 );
EXTN_METHOD_DECLARE( UNIT_TEST__TEST__BASE_API_MATH_F64 );

EXTN_METHOD_DECLARE( UNIT_TEST__TEST__Base_API_PM_Thread );

EXTN_METHOD_DECLARE( UNIT_TEST__TEST__Base_API );

EXTN_METHOD_DECLARE( UNIT_TEST__TEST__NSZ_Base_API_String );
EXTN_METHOD_DECLARE( UNIT_TEST__TEST__WSZ_Base_API_String );
EXTN_METHOD_DECLARE( UNIT_TEST__TEST__USZ_Base_API_String );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Data                                                                                                                                                                */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

static Test_Case                            s_sTEST__Base_API_MATH;
static Test_Case                            s_sTEST__Base_API_PLATFORM;
static Test_Case                            s_sTEST__Base_API_STRING;
static Test_Case                            s_sTEST__Base_API;




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgCM_Unit_Test_Register_Base_API ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgCM_Unit_Test_Register_Base_API( Test_Set * psSET__BASE )
{
    /* Initialize the unit test structures */

    Unit_Test__Case_Init( &s_sTEST__Base_API_MATH );
    Unit_Test__Case_Init( &s_sTEST__Base_API_PLATFORM );
    Unit_Test__Case_Init( &s_sTEST__Base_API_STRING );
    Unit_Test__Case_Init( &s_sTEST__Base_API );


    /* Configure the test cases */

    s_sTEST__Base_API_MATH.m_pszSet = psSET__BASE->m_szSet;
    s_sTEST__Base_API_MATH.m_pszCase = u8"Math API";

    s_sTEST__Base_API_MATH.m_apszTest[ 0] = u8"S08";
    s_sTEST__Base_API_MATH.m_pfnTest[  0] = UNIT_TEST__TEST__BASE_API_MATH_S08;
    s_sTEST__Base_API_MATH.m_apszTest[ 1] = u8"U08";
    s_sTEST__Base_API_MATH.m_pfnTest[  1] = UNIT_TEST__TEST__BASE_API_MATH_U08;
    s_sTEST__Base_API_MATH.m_apszTest[ 2] = u8"S16";
    s_sTEST__Base_API_MATH.m_pfnTest[  2] = UNIT_TEST__TEST__BASE_API_MATH_S16;
    s_sTEST__Base_API_MATH.m_apszTest[ 3] = u8"U16";
    s_sTEST__Base_API_MATH.m_pfnTest[  3] = UNIT_TEST__TEST__BASE_API_MATH_U16;
    s_sTEST__Base_API_MATH.m_apszTest[ 4] = u8"S32";
    s_sTEST__Base_API_MATH.m_pfnTest[  4] = UNIT_TEST__TEST__BASE_API_MATH_S32;
    s_sTEST__Base_API_MATH.m_apszTest[ 5] = u8"U32";
    s_sTEST__Base_API_MATH.m_pfnTest[  5] = UNIT_TEST__TEST__BASE_API_MATH_U32;
    s_sTEST__Base_API_MATH.m_apszTest[ 6] = u8"S64";
    s_sTEST__Base_API_MATH.m_pfnTest[  6] = UNIT_TEST__TEST__BASE_API_MATH_S64;
    s_sTEST__Base_API_MATH.m_apszTest[ 7] = u8"U64";
    s_sTEST__Base_API_MATH.m_pfnTest[  7] = UNIT_TEST__TEST__BASE_API_MATH_U64;
    s_sTEST__Base_API_MATH.m_apszTest[ 8] = u8"SPTR";
    s_sTEST__Base_API_MATH.m_pfnTest[  8] = UNIT_TEST__TEST__BASE_API_MATH_SPTR;
    s_sTEST__Base_API_MATH.m_apszTest[ 9] = u8"UPTR";
    s_sTEST__Base_API_MATH.m_pfnTest[  9] = UNIT_TEST__TEST__BASE_API_MATH_UPTR;
    s_sTEST__Base_API_MATH.m_apszTest[10] = u8"SMAX";
    s_sTEST__Base_API_MATH.m_pfnTest[ 10] = UNIT_TEST__TEST__BASE_API_MATH_SMAX;
    s_sTEST__Base_API_MATH.m_apszTest[11] = u8"UMAX";
    s_sTEST__Base_API_MATH.m_pfnTest[ 11] = UNIT_TEST__TEST__BASE_API_MATH_UMAX;
    s_sTEST__Base_API_MATH.m_apszTest[12] = u8"F32";
    s_sTEST__Base_API_MATH.m_pfnTest[ 12] = UNIT_TEST__TEST__BASE_API_MATH_F32;
    s_sTEST__Base_API_MATH.m_apszTest[13] = u8"F64";
    s_sTEST__Base_API_MATH.m_pfnTest[ 13] = UNIT_TEST__TEST__BASE_API_MATH_F64;

    s_sTEST__Base_API_PLATFORM.m_pszSet = psSET__BASE->m_szSet;
    s_sTEST__Base_API_PLATFORM.m_pszCase = u8"API";
    s_sTEST__Base_API_PLATFORM.m_apszTest[0] = u8"Platform: Thread";
    s_sTEST__Base_API_PLATFORM.m_pfnTest[0] = UNIT_TEST__TEST__Base_API_PM_Thread;

    s_sTEST__Base_API_STRING.m_pszSet = psSET__BASE->m_szSet;
    s_sTEST__Base_API_STRING.m_pszCase = u8"API";
    s_sTEST__Base_API_STRING.m_apszTest[0] = u8"Narrow Character Null-Terminated String";
    s_sTEST__Base_API_STRING.m_pfnTest[0] = UNIT_TEST__TEST__NSZ_Base_API_String;
    s_sTEST__Base_API_STRING.m_apszTest[1] = u8"Wide Character Null-Terminated String";
    s_sTEST__Base_API_STRING.m_pfnTest[1] = UNIT_TEST__TEST__WSZ_Base_API_String;
    s_sTEST__Base_API_STRING.m_apszTest[2] = u8"UTF8 Character Null-Terminated String";
    s_sTEST__Base_API_STRING.m_pfnTest[2] = UNIT_TEST__TEST__USZ_Base_API_String;

    s_sTEST__Base_API.m_pszSet = psSET__BASE->m_szSet;
    s_sTEST__Base_API.m_pszCase = u8"API";
    s_sTEST__Base_API.m_apszTest[0] = u8"-";
    s_sTEST__Base_API.m_pfnTest[0] = UNIT_TEST__TEST__Base_API;

    /* Register all of the test cases with the test set */

    Unit_Test__Set_Register_Case( psSET__BASE, &s_sTEST__Base_API_MATH );
    Unit_Test__Set_Register_Case( psSET__BASE, &s_sTEST__Base_API_PLATFORM );
    Unit_Test__Set_Register_Case( psSET__BASE, &s_sTEST__Base_API_STRING );
    Unit_Test__Set_Register_Case( psSET__BASE, &s_sTEST__Base_API );
}
