/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (WINDOWS) Kernel - Internal - Data.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
#if !defined(TGS_WINDOWS_KERNEL_INTERNAL_DATA_H)
#define TGS_WINDOWS_KERNEL_INTERNAL_DATA_H
#pragma once


/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Data                                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgEXTN HINSTANCE                            g_hInstance; /**< Imported from Common - Global; Needs to be initialized by the main routine of the executable */

TgEXTN STg2_KN_OS_HWND                      g_asKN_Wnd[KTgKN_MAX_WINDOWS];
TgEXTN STg2_UT_LF_ISO__ST                   g_sKN_GPU_OS_HWND__Free_Stack;
TgEXTN STg2_UT_LF_ISO__ST                   g_sKN_GPU_OS_HWND__Term_Stack;
TgEXTN TgUINT_E64_A                         g_xuiKN_Wnd_Request;
TgEXTN TgUINT_E64_A                         g_xuiKN_Wnd_Served;
TgEXTN TgUINT_E64_A                         g_xuiKN_Wnd_Closed;
TgEXTN STg1_MT_SM                           g_sKN_Window_Instance_Search_Lock;
TgEXTN STg1_MT_SM                           g_sKN_Window_Creation_Lock;
TgEXTN TgBOOL                               g_bKN_Close_Windows;

TgEXTN TgOSCHAR                             g_szKN_Default_Class_Name[KTgKN_MAX_TITLE];
TgEXTN TgOSCHAR                             g_szKN_Default_Window_Title[KTgKN_MAX_TITLE];
TgEXTN TgUINT_E32                           g_uiKN_Default_Window_Style;
TgEXTN WNDPROC                              g_pfnKN_Default_WndProc;

TgEXTN TgSINT_E32                           g_iKN_Window_PadX;
TgEXTN TgSINT_E32                           g_iKN_Window_PadY;

TgEXTN WNDPROC                              g_pfnKN_GUI_Keyboard_Handler;
TgEXTN WNDPROC                              g_pfnKN_GUI_Mouse_Handler;

TgEXTN TgVOID                               (*g_pfnDevice_Change_Check)(HWND,STg2_KN_OS_Window_Configuration_PC);
TgEXTN TgVOID                               (*g_pfnQuery_Monitor_Min_Resolution)(TgUINT_E32_P, TgUINT_E32_P, HMONITOR);
TgEXTN TgVOID                               (*g_pfnQuery_Monitor_Max_Resolution)(TgUINT_E32_P, TgUINT_E32_P, HMONITOR);
TgEXTN TgVOID                               (*g_pfnQuery_Swap_Context_Mode_Width_and_Height)(TgUINT_E32_P, TgUINT_E32_P, HWND, HMONITOR);
TgEXTN TgVOID                               (*g_pfnQuery_Swap_Context_Closest_Mode_Rounded_Down)(TgUINT_E32_P, TgUINT_E32_P, HWND, HMONITOR);

/* ---- WIN OS DLL Function Pointers  -------------------------------------------------------------------------------------------------------------------------------------------- */

/*  API Set: api-ms-win-core-com-l1-1-0 */
TgEXTN HRESULT                              (__stdcall *g_pfnCoInitializeEx)(TgVOID_P, DWORD);
TgEXTN TgVOID                               (__stdcall *g_pfnCoUninitialize)(TgVOID);
TgEXTN TgVOID                               (__stdcall *g_pfnCoTaskMemFree)(TgVOID_P);

/*  API Set: api-ms-win-core-errorhandling-l1-1-0 */
TgEXTN TgVOID                               (__stdcall *g_pfnRaiseException)(DWORD, DWORD, DWORD, TgUINT_E64_CP);
TgEXTN DWORD                                (__stdcall *g_pfnGetLastError)(TgVOID);

/*  API Set: ext-ms-win-ntuser-sysparams-ext-l1-1-1 */
TgEXTN HMONITOR                             (__stdcall *g_pfnMonitorFromWindow)(HWND, DWORD);
TgEXTN BOOL                                 (__stdcall *g_pfnGetMonitorInfo)(HMONITOR, LPMONITORINFO);
TgEXTN HMONITOR                             (__stdcall *g_pfnMonitorFromRect)(LPCRECT, DWORD);
TgEXTN BOOL                                 (__stdcall *g_pfnEnumDisplayMonitors)(HDC, LPCRECT, MONITORENUMPROC, TgSINT_E64);

/*  API Set: ext-ms-win-ntuser-windowclass-l1-1-0 */
TgEXTN WORD                                 (__stdcall *g_pfnRegisterClassEx)(const WNDCLASSEX *);
TgEXTN BOOL                                 (__stdcall *g_pfnUnregisterClass)(TgOSCHAR_CP, HINSTANCE);
TgEXTN TgSINT_E64                           (__stdcall *g_pfnGetWindowLongPtr)(HWND, TgSINT_E32);
TgEXTN TgSINT_E64                           (__stdcall *g_pfnSetWindowLongPtr)(HWND, TgSINT_E32, TgSINT_PTR);

/*  API Set: ext-ms-win-ntuser-window-l1-1-0 */
TgEXTN HWND                                 (__stdcall *g_pfnCreateWindowEx)(DWORD, TgOSCHAR_CP, TgOSCHAR_CP, DWORD, TgSINT_E32, TgSINT_E32, TgSINT_E32, TgSINT_E32, HWND, HMENU, 
                                                                             HINSTANCE, TgVOID_P);
TgEXTN BOOL                                 (__stdcall *g_pfnDestroyWindow)(HWND);
TgEXTN BOOL                                 (__stdcall *g_pfnShowWindow )(HWND, TgSINT_E32);
TgEXTN BOOL                                 (__stdcall *g_pfnGetWindowRect)(HWND, LPRECT);
TgEXTN BOOL                                 (__stdcall *g_pfnGetClientRect)(HWND, LPRECT);
TgEXTN HWND                                 (__stdcall *g_pfnFindWindow )(TgOSCHAR_CP, TgOSCHAR_CP);
TgEXTN BOOL                                 (__stdcall *g_pfnIsIconic )(HWND);
TgEXTN BOOL                                 (__stdcall *g_pfnSetForegroundWindow)(HWND);
TgEXTN TgSINT_E64                           (__stdcall *g_pfnDefWindowProc)(HWND, TgUINT_E32, TgUINT_E64, TgSINT_E64);
TgEXTN BOOL                                 (__stdcall *g_pfnSetWindowPos)(HWND, HWND, TgSINT_E32, TgSINT_E32, TgSINT_E32, TgSINT_E32, TgUINT_E32);

/*  API Set: ext-ms-win-ntuser-window-l1-1-2 */
TgEXTN BOOL                                 (__stdcall *g_pfnScreenToClient)(HWND, LPPOINT);

/*  API Set: ext-ms-win-ntuser-window-l1-1-3 */
TgEXTN BOOL                                 (__stdcall *g_pfnSetWindowText)(HWND, TgOSCHAR_CP);

/*  API Set: ext-ms-win-ntuser-draw-l1-1-0 */
TgEXTN BOOL                                 (__stdcall *g_pfnUpdateWindow)(HWND);

/*  API Set: ext-ms-win-ntuser-message-l1-1-0 */
TgEXTN BOOL                                 (__stdcall *g_pfnPeekMessage)(LPMSG, HWND, TgUINT_E32, TgUINT_E32, TgUINT_E32);
TgEXTN BOOL                                 (__stdcall *g_pfnGetMessage)(LPMSG, HWND, TgUINT_E32, TgUINT_E32);
TgEXTN BOOL                                 (__stdcall *g_pfnTranslateMessage)(const MSG *);
TgEXTN TgVOID                               (__stdcall *g_pfnPostQuitMessage)(TgSINT_E32);
TgEXTN TgSINT_E64                           (__stdcall *g_pfnDispatchMessage)(const MSG *);
TgEXTN TgSINT_E64                           (__stdcall *g_pfnSendMessage)(HWND, TgUINT_E32, TgUINT_E64, TgSINT_E64);
TgEXTN BOOL                                 (__stdcall *g_pfnPostMessage)(HWND, TgUINT_E32, TgUINT_E64, TgSINT_E64);

/* shell32 */
TgEXTN HRESULT                              (__stdcall *g_pfnSHGetKnownFolderPath)(const GUID *, DWORD, HANDLE, PWSTR *);

/* user32 */
TgEXTN HRESULT                              (__stdcall *g_pfnSetCursor)(HCURSOR);

/* (WINDOWS) COMMON, API Set: ext-ms-win-ntuser-sysparams-ext-l1-1-0 */
TgEXTN TgSINT_E32                           (__stdcall *g_pfnGetSystemMetrics)(TgSINT_E32);


/* =============================================================================================================================================================================== */
#endif
/* (WINDOWS) KERNEL, DLL: user32 */
