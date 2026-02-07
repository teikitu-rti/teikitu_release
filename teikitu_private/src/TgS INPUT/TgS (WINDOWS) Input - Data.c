/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (WINDOWS) Input - Data.c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.12 | »GUID« 964CB1A6-814D-4E19-8E67-A83FCA98BF05 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Input ====================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Data                                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

HINSTANCE                                   g_hDLL_DInput8 = nullptr;
HINSTANCE                                   g_hDLL_xInput = nullptr;

LPDIRECTINPUT8                              g_pdxDI = nullptr;

unsigned long                               (__stdcall *g_pfnDIN8_Release)( LPDIRECTINPUT8 ) = nullptr;
HRESULT                                     (__stdcall *g_pfnDIN8_CreateDevice)( LPDIRECTINPUT8, REFGUID, LPDIRECTINPUTDEVICE8*, LPUNKNOWN ) = nullptr;
HRESULT                                     (__stdcall *g_pfnDIN8_RunControlPanel)( LPDIRECTINPUT8, HWND, unsigned long ) = nullptr;

unsigned long                               (__stdcall *g_pfnDID8_Release)( LPDIRECTINPUTDEVICE8 ) = nullptr;
HRESULT                                     (__stdcall *g_pfnDID8_Acquire)( LPDIRECTINPUTDEVICE8 ) = nullptr;
HRESULT                                     (__stdcall *g_pfnDID8_Unacquire)( LPDIRECTINPUTDEVICE8 ) = nullptr;
HRESULT                                     (__stdcall *g_pfnDID8_GetDeviceState)( LPDIRECTINPUTDEVICE8, unsigned long, TgVOID_P ) = nullptr;
HRESULT                                     (__stdcall *g_pfnDID8_SetDataFormat)( LPDIRECTINPUTDEVICE8, LPCDIDATAFORMAT ) = nullptr;
HRESULT                                     (__stdcall *g_pfnDID8_SetCooperativeLevel)( LPDIRECTINPUTDEVICE8, HWND, unsigned long ) = nullptr;

HRESULT                                     (__stdcall *g_pfnDirectInput8Create)( HINSTANCE, TgUINT_E32 , TgVOID_CP, TgVOID_PP, TgVOID_P ) = nullptr;

TgUINT_E32                                  (__stdcall *g_pfnXInputSetState)( TgUINT_E32 , TgVOID_P ) = nullptr;
TgUINT_E32                                  (__stdcall *g_pfnXInputGetState)( TgUINT_E32 , TgVOID_P ) = nullptr;
TgUINT_E32                                  (__stdcall *g_pfnXInputGetCapabilities)( TgUINT_E32 , TgUINT_E32 , TgVOID_P ) = nullptr;




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgIN_PM_Query_Fixed_Memory ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRSIZE tgIN_PM_Query_Fixed_Memory( TgVOID )
{
    return (
        +sizeof( g_pdxDI )
        + sizeof( g_pfnDIN8_Release )
        + sizeof( g_pfnDIN8_CreateDevice )
        + sizeof( g_pfnDIN8_RunControlPanel )
        + sizeof( g_pfnDID8_Release )
        + sizeof( g_pfnDID8_Acquire )
        + sizeof( g_pfnDID8_Unacquire )
        + sizeof( g_pfnDID8_GetDeviceState )
        + sizeof( g_pfnDID8_SetDataFormat )
        + sizeof( g_pfnDID8_SetCooperativeLevel )
        + sizeof( g_pfnDirectInput8Create )
        + sizeof( g_pfnXInputSetState )
        + sizeof( g_pfnXInputGetState )
        + sizeof( g_pfnXInputGetCapabilities )
        + tgIN_PM_Query_Fixed_Memory_GUI_Keyboard()
        + tgIN_PM_Query_Fixed_Memory_Keyboard()
        + tgIN_PM_Query_Fixed_Memory_GUI_Mouse()
        + tgIN_PM_Query_Fixed_Memory_Mouse()
        + tgIN_PM_Query_Fixed_Memory_GamePad()
    );
}
