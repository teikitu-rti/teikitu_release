/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (WINDOWS) Kernel - Data.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Data                                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

STg2_KN_OS_HWND                             g_asKN_Wnd[KTgKN_MAX_WINDOWS];
STg2_UT_LF_ISO__ST                          g_sKN_GPU_OS_HWND__Free_Stack;
STg2_UT_LF_ISO__ST                          g_sKN_GPU_OS_HWND__Term_Stack;
TgUINT_E64_A                                g_xuiKN_Wnd_Request;
TgUINT_E64_A                                g_xuiKN_Wnd_Served;
TgUINT_E64_A                                g_xuiKN_Wnd_Closed;
STg1_MT_SM                                  g_sKN_Window_Instance_Search_Lock;
STg1_MT_SM                                  g_sKN_Window_Creation_Lock;
TgBOOL                                      g_bKN_Close_Windows;

TgOSCHAR                                    g_szKN_Default_Class_Name[KTgKN_MAX_TITLE];
TgOSCHAR                                    g_szKN_Default_Window_Title[KTgKN_MAX_TITLE];
TgUINT_E32                                  g_uiKN_Default_Window_Style;
WNDPROC                                     g_pfnKN_Default_WndProc;

TgSINT_E32                                  g_iKN_Window_PadX;
TgSINT_E32                                  g_iKN_Window_PadY;

WNDPROC                                     g_pfnKN_GUI_Keyboard_Handler = nullptr;
WNDPROC                                     g_pfnKN_GUI_Mouse_Handler = nullptr;

TgVOID                                      (*g_pfnDevice_Change_Check)(HWND,STg2_KN_OS_Window_Configuration_PC) = nullptr;
TgVOID                                      (*g_pfnQuery_Monitor_Min_Resolution)(TgUINT_E32_P, TgUINT_E32_P, HMONITOR) = nullptr;
TgVOID                                      (*g_pfnQuery_Monitor_Max_Resolution)(TgUINT_E32_P, TgUINT_E32_P, HMONITOR) = nullptr;
TgVOID                                      (*g_pfnQuery_Swap_Context_Mode_Width_and_Height)(TgUINT_E32_P, TgUINT_E32_P, HWND, HMONITOR) = nullptr;
TgVOID                                      (*g_pfnQuery_Swap_Context_Closest_Mode_Rounded_Down)(TgUINT_E32_P, TgUINT_E32_P, HWND, HMONITOR) = nullptr;

/*  API Set: api-ms-win-core-com-l1-1-0 */
HRESULT                                     (__stdcall *g_pfnCoInitializeEx)( TgVOID_P, DWORD ) = nullptr;
TgVOID                                      (__stdcall *g_pfnCoUninitialize)( TgVOID ) = nullptr;
TgVOID                                      (__stdcall *g_pfnCoTaskMemFree)( TgVOID_P ) = nullptr;

/*  API Set: api-ms-win-core-errorhandling-l1-1-0 */
TgVOID                                      (__stdcall *g_pfnRaiseException)( DWORD, DWORD, DWORD, TgUINT_E64_CP  ) = nullptr;
DWORD                                       (__stdcall *g_pfnGetLastError)( TgVOID ) = nullptr;

/*  API Set: ext-ms-win-ntuser-sysparams-ext-l1-1-1 */
HMONITOR                                    (__stdcall *g_pfnMonitorFromWindow)( HWND, DWORD ) = nullptr;
BOOL                                        (__stdcall *g_pfnGetMonitorInfo)( HMONITOR, LPMONITORINFO ) = nullptr;
HMONITOR                                    (__stdcall *g_pfnMonitorFromRect)( LPCRECT, DWORD ) = nullptr;
BOOL                                        (__stdcall *g_pfnEnumDisplayMonitors)( HDC, LPCRECT, MONITORENUMPROC, TgSINT_E64  ) = nullptr;

/*  API Set: ext-ms-win-ntuser-windowclass-l1-1-0 */
WORD                                        (__stdcall *g_pfnRegisterClassEx)( const WNDCLASSEX * ) = nullptr;
BOOL                                        (__stdcall *g_pfnUnregisterClass)( TgOSCHAR_CP, HINSTANCE ) = nullptr;
TgSINT_E64                                  (__stdcall *g_pfnGetWindowLongPtr)( HWND, TgSINT_E32  ) = nullptr;
TgSINT_E64                                  (__stdcall *g_pfnSetWindowLongPtr)( HWND, TgSINT_E32 , TgSINT_PTR  ) = nullptr;

/*  API Set: ext-ms-win-ntuser-window-l1-1-0 */
HWND                                        (__stdcall *g_pfnCreateWindowEx)( DWORD, TgOSCHAR_CP, TgOSCHAR_CP, DWORD, TgSINT_E32 , TgSINT_E32 , TgSINT_E32 , TgSINT_E32 , HWND,
                                                                              HMENU, HINSTANCE, TgVOID_P ) = nullptr;
BOOL                                        (__stdcall *g_pfnDestroyWindow)( HWND ) = nullptr;
BOOL                                        (__stdcall *g_pfnShowWindow)( HWND, TgSINT_E32  ) = nullptr;
BOOL                                        (__stdcall *g_pfnGetWindowRect)( HWND, LPRECT ) = nullptr;
BOOL                                        (__stdcall *g_pfnGetClientRect)( HWND, LPRECT ) = nullptr;
HWND                                        (__stdcall *g_pfnFindWindow)( TgOSCHAR_CP, TgOSCHAR_CP ) = nullptr;
BOOL                                        (__stdcall *g_pfnIsIconic)( HWND ) = nullptr;
BOOL                                        (__stdcall *g_pfnSetForegroundWindow)( HWND ) = nullptr;
TgSINT_E64                                  (__stdcall *g_pfnDefWindowProc)( HWND, TgUINT_E32 , TgUINT_E64 , TgSINT_E64  ) = nullptr;
BOOL                                        (__stdcall *g_pfnSetWindowPos)( HWND, HWND, TgSINT_E32 , TgSINT_E32 , TgSINT_E32 , TgSINT_E32 , TgUINT_E32  ) = nullptr;

/*  API Set: ext-ms-win-ntuser-window-l1-1-2 */
BOOL                                        (__stdcall *g_pfnScreenToClient)( HWND, LPPOINT ) = nullptr;

/*  API Set: ext-ms-win-ntuser-window-l1-1-3 */
BOOL                                        (__stdcall *g_pfnSetWindowText)( HWND, TgOSCHAR_CP ) = nullptr;

/*  API Set: ext-ms-win-ntuser-draw-l1-1-0 */
BOOL                                        (__stdcall *g_pfnUpdateWindow)( HWND ) = nullptr;

/*  API Set: ext-ms-win-ntuser-message-l1-1-0 */
BOOL                                        (__stdcall *g_pfnPeekMessage)( LPMSG, HWND, TgUINT_E32 , TgUINT_E32 , TgUINT_E32  ) = nullptr;
BOOL                                        (__stdcall *g_pfnGetMessage)( LPMSG, HWND, TgUINT_E32 , TgUINT_E32  ) = nullptr;
BOOL                                        (__stdcall *g_pfnTranslateMessage)( const MSG * ) = nullptr;
TgVOID                                      (__stdcall *g_pfnPostQuitMessage)( TgSINT_E32  ) = nullptr;
TgSINT_E64                                  (__stdcall *g_pfnDispatchMessage)( const MSG * ) = nullptr;
TgSINT_E64                                  (__stdcall *g_pfnSendMessage)( HWND, TgUINT_E32 , TgUINT_E64 , TgSINT_E64  ) = nullptr;
BOOL                                        (__stdcall *g_pfnPostMessage)( HWND, TgUINT_E32 , TgUINT_E64 , TgSINT_E64  ) = nullptr;

/* shell32 */
HRESULT                                     (__stdcall *g_pfnSHGetKnownFolderPath)( const GUID *, DWORD, HANDLE, PWSTR* ) = nullptr;

/* user32 */
HRESULT                                     (__stdcall *g_pfnSetCursor)(HCURSOR) = nullptr;




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_OS_Query_Fixed_Memory ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRSIZE tgKN_OS_Query_Fixed_Memory( TgVOID )
{
    return (0
            + sizeof( g_hInstance )

            + sizeof( g_asKN_Wnd )
            + sizeof( g_sKN_GPU_OS_HWND__Free_Stack )
            + sizeof( g_sKN_GPU_OS_HWND__Term_Stack )
            + sizeof( g_xuiKN_Wnd_Request )
            + sizeof( g_xuiKN_Wnd_Served )
            + sizeof( g_xuiKN_Wnd_Closed )
            + sizeof( g_sKN_Window_Instance_Search_Lock )
            + sizeof( g_sKN_Window_Creation_Lock )
            + sizeof( g_bKN_Close_Windows )

            + sizeof( g_szKN_Default_Class_Name )
            + sizeof( g_szKN_Default_Window_Title )
            + sizeof( g_uiKN_Default_Window_Style )
            + sizeof( g_pfnKN_Default_WndProc )

            + sizeof( g_iKN_Window_PadX )
            + sizeof( g_iKN_Window_PadY )

            + sizeof( g_pfnKN_GUI_Keyboard_Handler )
            + sizeof( g_pfnKN_GUI_Mouse_Handler )

            + sizeof( g_pfnDevice_Change_Check )
            + sizeof( g_pfnQuery_Monitor_Min_Resolution )
            + sizeof( g_pfnQuery_Monitor_Max_Resolution )
            + sizeof( g_pfnQuery_Swap_Context_Mode_Width_and_Height )
            + sizeof( g_pfnQuery_Swap_Context_Closest_Mode_Rounded_Down )

            + sizeof( g_pfnCoInitializeEx )
            + sizeof( g_pfnCoUninitialize )
            + sizeof( g_pfnCoTaskMemFree )

            + sizeof( g_pfnRaiseException )
            + sizeof( g_pfnGetLastError )

            + sizeof( g_pfnMonitorFromWindow )
            + sizeof( g_pfnGetMonitorInfo )
            + sizeof( g_pfnMonitorFromRect )
            + sizeof( g_pfnEnumDisplayMonitors )

            + sizeof( g_pfnRegisterClassEx )
            + sizeof( g_pfnUnregisterClass )
            + sizeof( g_pfnGetWindowLongPtr )
            + sizeof( g_pfnSetWindowLongPtr )

            + sizeof( g_pfnCreateWindowEx )
            + sizeof( g_pfnDestroyWindow )
            + sizeof( g_pfnShowWindow )
            + sizeof( g_pfnGetWindowRect )
            + sizeof( g_pfnGetClientRect )
            + sizeof( g_pfnFindWindow )
            + sizeof( g_pfnIsIconic )
            + sizeof( g_pfnSetForegroundWindow )
            + sizeof( g_pfnDefWindowProc )
            + sizeof( g_pfnSetWindowPos )

            + sizeof( g_pfnScreenToClient )

            + sizeof( g_pfnSetWindowText )

            + sizeof( g_pfnUpdateWindow )

            + sizeof( g_pfnPeekMessage )
            + sizeof( g_pfnGetMessage )
            + sizeof( g_pfnTranslateMessage )
            + sizeof( g_pfnPostQuitMessage )
            + sizeof( g_pfnDispatchMessage )
            + sizeof( g_pfnSendMessage )
            + sizeof( g_pfnPostMessage )

            + sizeof( g_pfnSHGetKnownFolderPath )

            + sizeof( g_pfnSetCursor )
    );
}
