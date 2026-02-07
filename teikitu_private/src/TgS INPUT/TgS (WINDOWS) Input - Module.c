/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (WINDOWS) Input - Module.c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.12 | »GUID« 964CB1A6-814D-4E19-8E67-A83FCA98BF05 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Input ====================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgIN_PM_Module_Init ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgIN_PM_Module_Init( TgVOID )
{
    g_fDefault_GamePad_Stick_0_X_Dead_Zone = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE / 32767.0F;
    g_fDefault_GamePad_Stick_0_Y_Dead_Zone = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE / 32767.0F;
    g_fDefault_GamePad_Stick_1_X_Dead_Zone = XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE / 32767.0F;
    g_fDefault_GamePad_Stick_1_Y_Dead_Zone = XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE / 32767.0F;

    /* Load the dinput functions from the DLL */
    if (!tgGB_Load_Lib( &g_hDLL_DInput8, TgOS_TEXT("dinput8.dll") ))
    {
        TgCRITICAL_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to load dinput8 DLL." );
        return (KTgE_FAIL);
    };

    if (
           !tgGB_Get_Func_Address( (FARPROC*)&g_pfnDirectInput8Create, g_hDLL_DInput8, "DirectInput8Create" )
    )
    {
        TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to find function in dinput8 DLL." );
        tgIN_PM_Module_Free();
        return (KTgE_FAIL);
    };


    /* Load the xInput functions from the DLL */
    if (!tgGB_Load_Lib( &g_hDLL_xInput, TgOS_TEXT("xinput9_1_0.dll") ))
    {
        TgCRITICAL_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to load xinput DLL." );
        tgIN_PM_Module_Free();
        return (KTgE_FAIL);
    };

    if (
           !tgGB_Get_Func_Address( (FARPROC*)&g_pfnXInputGetState, g_hDLL_xInput, "XInputGetState" )
        || !tgGB_Get_Func_Address( (FARPROC*)&g_pfnXInputGetCapabilities, g_hDLL_xInput, "XInputGetCapabilities" )
        || !tgGB_Get_Func_Address( (FARPROC*)&g_pfnXInputSetState, g_hDLL_xInput, "XInputSetState" )
    )
    {
        TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to find function in xinput DLL." );
        tgIN_PM_Module_Free();
        return (KTgE_FAIL);
    };


    if (TgFAILED( g_pfnDirectInput8Create( g_hInstance, DIRECTINPUT_VERSION, &IID_IDirectInput8, (TgVOID_PP)&g_pdxDI, 0 ) ))
    {
        TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Direct input 8.0 failed." );
        tgIN_PM_Module_Free();
        return (KTgE_FAIL);
    };

    if (TgFAILED( tgIN_PM_Init_Function_Table() ))
    {
        TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to acquire input funcitons." );
        tgIN_PM_Module_Free();
        return (KTgE_FAIL);
    };

    tgIN_PM_Init_Keyboard();
    tgIN_PM_Init_Mouse();
    tgIN_PM_Init_GamePad();
    tgIN_PM_Init_GUI_Mouse();
    tgIN_PM_Init_GUI_Keyboard();

    return (KTgS_OK);
}


/* ---- tgIN_PM_Module_Boot ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgIN_PM_Module_Boot( TgVOID )
{
    if (
           TgFAILED( tgIN_PM_Boot_Keyboard() )
        || TgFAILED( tgIN_PM_Boot_Mouse() )
        || TgFAILED( tgIN_PM_Boot_GamePad() )
        || TgFAILED( tgIN_PM_Boot_GUI_Mouse() )
        || TgFAILED( tgIN_PM_Boot_GUI_Keyboard() )
    )
    {
        tgIN_PM_Stop_GUI_Mouse();
        tgIN_PM_Stop_GamePad();
        tgIN_PM_Stop_Mouse();
        tgIN_PM_Stop_Keyboard();
        return (KTgE_FAIL);
    };

    return (KTgS_OK);
}


/* ---- tgIN_PM_Module_Stop ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgIN_PM_Module_Stop( TgVOID )
{
    /* Stop the controller systems */
    TgVERIFY( KTgS_OK == tgIN_PM_Stop_GUI_Keyboard() );
    TgVERIFY( KTgS_OK == tgIN_PM_Stop_GUI_Mouse() );
    TgVERIFY( KTgS_OK == tgIN_PM_Stop_GamePad() );
    TgVERIFY( KTgS_OK == tgIN_PM_Stop_Mouse() );
    TgVERIFY( KTgS_OK == tgIN_PM_Stop_Keyboard() );

    return (KTgS_OK);
}


/* ---- tgIN_PM_Module_Free ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgIN_PM_Module_Free( TgVOID )
{
    TgVERIFY( KTgS_OK == tgIN_PM_Free_GUI_Keyboard() );
    TgVERIFY( KTgS_OK == tgIN_PM_Free_GUI_Mouse() );
    TgVERIFY( KTgS_OK == tgIN_PM_Free_GamePad() );
    TgVERIFY( KTgS_OK == tgIN_PM_Free_Mouse() );
    TgVERIFY( KTgS_OK == tgIN_PM_Free_Keyboard() );

    if (nullptr != g_pdxDI)
    {
        TgVERIFY( 1 != g_pfnDIN8_Release( g_pdxDI ) );
        g_pdxDI = nullptr;
    };

    if (nullptr != g_hDLL_xInput)
    {
        tgGB_Free_Lib( &g_hDLL_xInput );
    };
    g_pfnXInputGetState = 0;
    g_pfnXInputGetCapabilities = 0;
    g_pfnXInputSetState = 0;

    if (nullptr != g_hDLL_DInput8)
    {
        tgGB_Free_Lib( &g_hDLL_DInput8 );
    };
    g_pfnDirectInput8Create = 0;

    return (KTgS_OK);
}
