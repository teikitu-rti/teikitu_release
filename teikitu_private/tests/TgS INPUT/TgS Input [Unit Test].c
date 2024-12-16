/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Input [Unit Test].c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   4.51 | »GUID« A9981407-3EC9-42AF-8B6F-8BE6DD919615                                                                                                                 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Input ====================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Data                                                                                                                                                                */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

static Test_Set                                             s_sSET__INPUT;

static Test_Case                                            s_sTEST__Module;
static Test_Case                                            s_sTEST__GUI_Keyboard;
static Test_Case                                            s_sTEST__Keyboard;
static Test_Case                                            s_sTEST__GUI_Mouse;
static Test_Case                                            s_sTEST__Mouse;
static Test_Case                                            s_sTEST__GamePad;
static Test_Case                                            s_sTEST__Stat;




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Main Execution                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgCLANG_WARN_SUPPRESS(missing-prototypes)
TgVOID tgCM_Unit_Test_Register( TgVOID )
{
    /* Initialize the unit test structures */

    Unit_Test__Set_Init( &s_sSET__INPUT );

    Unit_Test__Case_Init( &s_sTEST__Module );
    Unit_Test__Case_Init( &s_sTEST__GUI_Keyboard );
    Unit_Test__Case_Init( &s_sTEST__Keyboard );
    Unit_Test__Case_Init( &s_sTEST__GUI_Mouse );
    Unit_Test__Case_Init( &s_sTEST__Mouse );
    Unit_Test__Case_Init( &s_sTEST__GamePad );
    Unit_Test__Case_Init( &s_sTEST__Stat );



    /* Configure the test set */

    s_sSET__INPUT.m_szSet = u8"Input";



    /* Configure the test cases */

    s_sTEST__Module.m_pszSet = s_sSET__INPUT.m_szSet;
    s_sTEST__Module.m_pszCase = u8"Module";
    s_sTEST__Module.m_pfnTest[0] = TEST__Input_Module;

    s_sTEST__GUI_Keyboard.m_pszSet = s_sSET__INPUT.m_szSet;
    s_sTEST__GUI_Keyboard.m_pszCase = u8"GUI Keyboard";
    s_sTEST__GUI_Keyboard.m_pfnTest[0] = TEST__Input_GUI_Keyboard;

    s_sTEST__Keyboard.m_pszSet = s_sSET__INPUT.m_szSet;
    s_sTEST__Keyboard.m_pszCase = u8"Keyboard";
    s_sTEST__Keyboard.m_pfnTest[0] = TEST__Input_Keyboard;

    s_sTEST__GUI_Mouse.m_pszSet = s_sSET__INPUT.m_szSet;
    s_sTEST__GUI_Mouse.m_pszCase = u8"GUI Mouse";
    s_sTEST__GUI_Mouse.m_pfnTest[0] = TEST__Input_GUI_Mouse;

    s_sTEST__Mouse.m_pszSet = s_sSET__INPUT.m_szSet;
    s_sTEST__Mouse.m_pszCase = u8"Mouse";
    s_sTEST__Mouse.m_pfnTest[0] = TEST__Input_Mouse;

    s_sTEST__GamePad.m_pszSet = s_sSET__INPUT.m_szSet;
    s_sTEST__GamePad.m_pszCase = u8"Game Pad";
    s_sTEST__GamePad.m_pfnTest[0] = TEST__Input_GamePad;

    s_sTEST__Stat.m_pszSet = s_sSET__INPUT.m_szSet;
    s_sTEST__Stat.m_pszCase = u8"Stat";
    s_sTEST__Stat.m_pfnTest[0] = TEST__Input_Stat;



    /* Register all of the test cases with the test set */

    Unit_Test__Set_Register_Case( &s_sSET__INPUT, &s_sTEST__Module );
    Unit_Test__Set_Register_Case( &s_sSET__INPUT, &s_sTEST__GUI_Keyboard );
    Unit_Test__Set_Register_Case( &s_sSET__INPUT, &s_sTEST__Keyboard );
    Unit_Test__Set_Register_Case( &s_sSET__INPUT, &s_sTEST__GUI_Mouse );
    Unit_Test__Set_Register_Case( &s_sSET__INPUT, &s_sTEST__Mouse );
    Unit_Test__Set_Register_Case( &s_sSET__INPUT, &s_sTEST__GamePad );
    Unit_Test__Set_Register_Case( &s_sSET__INPUT, &s_sTEST__Stat );



    /* Register the test set with the unit test system */

    Unit_Test__Register( &s_sSET__INPUT );
}
