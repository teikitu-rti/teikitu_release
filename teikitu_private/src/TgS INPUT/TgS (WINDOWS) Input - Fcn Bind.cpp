/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (WINDOWS) Input - Fcn Bind.cpp
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.12 | »GUID« 964CB1A6-814D-4E19-8E67-A83FCA98BF05 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "TgS COMMON/TgS (WINDOWS) Common - Base - Include.h"

TgDISABLE_ALL_WARNNGS_PUSH
#define NOTEXTMETRIC
#include <windows.h>
TgEXTN HINSTANCE                            g_hInstance;
TgDISABLE_ALL_WARNNGS_POP


/* == Input ====================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgIN_PM_Init_Function_Table ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgCLANG_WARN_DISABLE_PUSH(invalid-token-paste)
TgRESULT tgIN_PM_Init_Function_Table( TgVOID )
{
    LPDIRECTINPUTDEVICE8                dxDID;
    LPDIRECTINPUT8                      dxDI;

    /* Map the Direct Input System Functions */

    dxDI = static_cast<LPDIRECTINPUT8>(g_pdxDI);

    g_pfnDIN8_Release = dxDI->lpVtbl->Release;
    g_pfnDIN8_CreateDevice = dxDI->lpVtbl->CreateDevice;
    g_pfnDIN8_RunControlPanel = dxDI->lpVtbl->RunControlPanel;

    /* Map the Direct Input Device Functions */

    if (TgFAILED( g_pfnDIN8_CreateDevice( static_cast<LPDIRECTINPUT8>(g_pdxDI), MS_REF GUID_SysKeyboard, &dxDID, nullptr ) ))
    {
        return (KTgE_FAIL);
    };

    g_pfnDID8_Release = dxDID->lpVtbl->Release;
    g_pfnDID8_Acquire = dxDID->lpVtbl->Acquire;
    g_pfnDID8_Unacquire = dxDID->lpVtbl->Unacquire;
    g_pfnDID8_GetDeviceState = dxDID->lpVtbl->GetDeviceState;
    g_pfnDID8_SetDataFormat = dxDID->lpVtbl->SetDataFormat;
    g_pfnDID8_SetCooperativeLevel = dxDID->lpVtbl->SetCooperativeLevel;

    g_pfnDID8_Release( dxDID );

    /* #HACK: BIND FUNC CORRECT */

    return (KTgS_OK);
}
TgCLANG_WARN_DISABLE_POP(invalid-token-paste)
