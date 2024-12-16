/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common [Unit Test] - Common.c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TEST_METHOD_DEFINE( UNIT_TEST__TEST__COMMON_Console );
TEST_METHOD_DEFINE( UNIT_TEST__TEST__COMMON_Event_MGR );
TEST_METHOD_DEFINE( UNIT_TEST__TEST__COMMON_Global );
TEST_METHOD_DEFINE( UNIT_TEST__TEST__COMMON_Job_MGR );
TEST_METHOD_DEFINE( UNIT_TEST__TEST__COMMON_Mem_MGR );
TEST_METHOD_DEFINE( UNIT_TEST__TEST__COMMON_Profile );
TEST_METHOD_DEFINE( UNIT_TEST__TEST__COMMON_String_MGR );
TEST_METHOD_DEFINE( UNIT_TEST__TEST__COMMON_SysInfo );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Unit Test Data                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

static Test_Set                             s_sSET__COMMON;

static Test_Case                            s_sCASE__COMMON;




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TgVOID tgCM_Unit_Test_Register_COMMON( TgVOID )
{
    /* Initialize the unit test structures */

    Unit_Test__Set_Init( &s_sSET__COMMON );
    
    Unit_Test__Case_Init( &s_sCASE__COMMON );



    /* Configure the test set */

    s_sSET__COMMON.m_szSet = u8"Common: Common";



    /* Register all of the test cases with the test set */

    s_sCASE__COMMON.m_pszSet = s_sSET__COMMON.m_szSet;
    s_sCASE__COMMON.m_pszCase = u8"Common";

    s_sCASE__COMMON.m_apszTest[0] = u8"Console";
    s_sCASE__COMMON.m_pfnTest[0] = UNIT_TEST__TEST__COMMON_Console;
    s_sCASE__COMMON.m_apszTest[1] = u8"Event MGR";
    s_sCASE__COMMON.m_pfnTest[1] = UNIT_TEST__TEST__COMMON_Event_MGR;
    s_sCASE__COMMON.m_apszTest[2] = u8"Global";
    s_sCASE__COMMON.m_pfnTest[2] = UNIT_TEST__TEST__COMMON_Global;
    s_sCASE__COMMON.m_apszTest[3] = u8"Job MGR";
    s_sCASE__COMMON.m_pfnTest[3] = UNIT_TEST__TEST__COMMON_Job_MGR;
    s_sCASE__COMMON.m_apszTest[4] = u8"Mem MGR";
    s_sCASE__COMMON.m_pfnTest[4] = UNIT_TEST__TEST__COMMON_Mem_MGR;
    s_sCASE__COMMON.m_apszTest[5] = u8"Profile";
    s_sCASE__COMMON.m_pfnTest[5] = UNIT_TEST__TEST__COMMON_Profile;
    s_sCASE__COMMON.m_apszTest[6] = u8"String MGR";
    s_sCASE__COMMON.m_pfnTest[6] = UNIT_TEST__TEST__COMMON_String_MGR;
    s_sCASE__COMMON.m_apszTest[7] = u8"SysInfo";
    s_sCASE__COMMON.m_pfnTest[7] = UNIT_TEST__TEST__COMMON_SysInfo;




    /* Register all of the test cases with the test set */

    Unit_Test__Set_Register_Case( &s_sSET__COMMON, &s_sCASE__COMMON );

    /* Register the test set with the unit test system */

    Unit_Test__Register( &s_sSET__COMMON );
}
