/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (WINDOWS) Input - Internal - Data.h
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.12 | »GUID« 964CB1A6-814D-4E19-8E67-A83FCA98BF05 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_WINDOWS_INPUT_INTERNAL_DATA_H)
#define TGS_WINDOWS_INPUT_INTERNAL_DATA_H
#pragma once

#include "TgS COMMON/TgS (WINDOWS) Common - Base - Include.h"

TgDISABLE_ALL_WARNNGS_PUSH
#define DIRECTINPUT_VERSION 0x0800
#include <guiddef.h>
#include <xinput.h>
#include <dinput.h>
TgDISABLE_ALL_WARNNGS_POP




/* == Input ====================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Data                                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgEXTN HINSTANCE                            g_hInstance;

TgEXTN HINSTANCE                            g_hDLL_DInput8;
TgEXTN HINSTANCE                            g_hDLL_xInput;

TgEXTN LPDIRECTINPUT8                       g_pdxDI;

TgEXTN HRESULT                              (__stdcall *g_pfnDirectInput8Create)( HINSTANCE, TgUINT_E32, TgVOID_CP, TgVOID_PP, TgVOID_P );

TgEXTN unsigned long                        (__stdcall *g_pfnDIN8_Release)( LPDIRECTINPUT8 );
TgEXTN HRESULT                              (__stdcall *g_pfnDIN8_CreateDevice)( LPDIRECTINPUT8, REFGUID, LPDIRECTINPUTDEVICE8*, LPUNKNOWN );
TgEXTN HRESULT                              (__stdcall *g_pfnDIN8_RunControlPanel)( LPDIRECTINPUT8, HWND, unsigned long );

TgEXTN unsigned long                        (__stdcall *g_pfnDID8_Release)( LPDIRECTINPUTDEVICE8 );
TgEXTN HRESULT                              (__stdcall *g_pfnDID8_Acquire)( LPDIRECTINPUTDEVICE8 );
TgEXTN HRESULT                              (__stdcall *g_pfnDID8_Unacquire)( LPDIRECTINPUTDEVICE8 );
TgEXTN HRESULT                              (__stdcall *g_pfnDID8_GetDeviceState)( LPDIRECTINPUTDEVICE8, unsigned long, TgVOID_P );
TgEXTN HRESULT                              (__stdcall *g_pfnDID8_SetDataFormat)( LPDIRECTINPUTDEVICE8, LPCDIDATAFORMAT );
TgEXTN HRESULT                              (__stdcall *g_pfnDID8_SetCooperativeLevel)( LPDIRECTINPUTDEVICE8, HWND, unsigned long );

TgEXTN TgUINT_E32                           (__stdcall *g_pfnXInputSetState)( TgUINT_E32, TgVOID_P );
TgEXTN TgUINT_E32                           (__stdcall *g_pfnXInputGetState)( TgUINT_E32, TgVOID_P );
TgEXTN TgUINT_E32                           (__stdcall *g_pfnXInputGetCapabilities)( TgUINT_E32, TgUINT_E32, TgVOID_P );

/* (WINDOWS) KERNEL, DLL: user32 */
TgEXTN TgBOOL                               (__stdcall *g_pfnScreenToClient)( HWND,TgVOID_P );

/* (WINDOWS) KERNEL, DLL: api-ms-win-core-localization-l1-2-1 */
#if !defined(TgBUILD_UNIVERSAL__UWP)
TgEXTN TgUINT_E32                           (__stdcall *g_pfnGetACP)( TgVOID );
/*# !defined(TgBUILD_UNIVERSAL__UWP) */
#endif


/* =============================================================================================================================================================================== */
#endif
