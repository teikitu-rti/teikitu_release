/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (WINDOWS) Kernel - Link Test.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/* == Kernel ===================================================================================================================================================================== */

#if defined(_INC_WINDOWS)
#error windows.h has been found in the include chain
#endif


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Link Test                                                                                                                                                                      */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

#if defined(TGS_DEBUG)
TgEXTN TgVOID Function_Type_Test( TgVOID );
TgVOID Function_Type_Test( TgVOID )
{
    //g_pfnCoInitializeEx = CoInitializeEx;
    //g_pfnCoUninitialize = CoUninitialize;
    //g_pfnEnumDisplaySettings = EnumDisplaySettings;

    g_pfnRaiseException = RaiseException;
    g_pfnGetLastError = GetLastError;

    g_pfnMonitorFromWindow = MonitorFromWindow;
    g_pfnGetMonitorInfo = GetMonitorInfo;
    g_pfnMonitorFromRect = MonitorFromRect;
    g_pfnEnumDisplayMonitors = EnumDisplayMonitors;

    g_pfnRegisterClassEx = RegisterClassEx;
    g_pfnUnregisterClass = UnregisterClass;
    g_pfnGetWindowLongPtr = GetWindowLongPtr;
    g_pfnSetWindowLongPtr = SetWindowLongPtr;

    g_pfnCreateWindowEx = CreateWindowEx;
    g_pfnDestroyWindow = DestroyWindow;
    g_pfnShowWindow = ShowWindow;
    g_pfnGetWindowRect = GetWindowRect;
    g_pfnGetClientRect = GetClientRect;
    g_pfnFindWindow = FindWindow;
    g_pfnIsIconic = IsIconic;
    g_pfnSetForegroundWindow = SetForegroundWindow;
    g_pfnDefWindowProc = DefWindowProc;
    g_pfnSetWindowPos = SetWindowPos;

    g_pfnScreenToClient = ScreenToClient;

    g_pfnSetWindowText = SetWindowText;

    g_pfnUpdateWindow = UpdateWindow;

    g_pfnPeekMessage = PeekMessage;
    g_pfnGetMessage = GetMessage;
    g_pfnTranslateMessage = TranslateMessage;
    g_pfnPostQuitMessage = PostQuitMessage;
    g_pfnDispatchMessage = DispatchMessage;
    g_pfnSendMessage = SendMessage;
    g_pfnPostMessage = PostMessage;
}
#endif
