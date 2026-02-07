/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (WINDOWS) Kernel - Module.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "TgS COMMON/TgS (WINDOWS) Common - SysInfo.h"


/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Macros                                                                                                                                                              */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

#define TFCN_TOQUOTE(FCN) #FCN
#if defined(TgCOMPILE_OS_TEXT__UTF8)
#define TFCN(FCN) TFCN_TOQUOTE(FCN##A)
#elif defined (TgCOMPILE_OS_TEXT__WIDE)
#define TFCN(FCN) TFCN_TOQUOTE(FCN##W)
#else
#endif




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

static TgVOID
tgKN_OS_Clean_Up_Window_Threads( TgVOID );

static HINSTANCE                            s_hDLL_Core_COM = nullptr;
static HINSTANCE                            s_hDLL_Core_Error = nullptr;
static HINSTANCE                            s_hDLL_Shell32 = nullptr;
static HINSTANCE                            s_hDLL_User32 = nullptr;
static HINSTANCE                            s_hDLL_ext_ms_win_ntuser_sysparams_ext_l1_1_1 = nullptr;
static HINSTANCE                            s_hDLL_ext_ms_win_ntuser_windowclass_l1_1_0 = nullptr;
static HINSTANCE                            s_hDLL_ext_ext_ms_win_ntuser_window_l1_1_0 = nullptr;
static HINSTANCE                            s_hDLL_ext_ms_win_ntuser_window_l1_1_2 = nullptr;
static HINSTANCE                            s_hDLL_ext_ms_win_ntuser_window_l1_1_3 = nullptr;
static HINSTANCE                            s_hDLL_ext_ms_win_ntuser_draw_l1_1_0 = nullptr;
static HINSTANCE                            s_hDLL_ext_ms_win_ntuser_message_l1_1_0 = nullptr;




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Unit Test Functions                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

static TgVOID
tgTST_KN_Device_Change_Check(
    HWND ARG0, STg2_KN_OS_Window_Configuration_PC ARG1 );

static TgVOID
tgTST_KN_Query_Monitor_Min_Resolution(
    TgUINT_E32_P OUT0, TgUINT_E32_P OUT1, HMONITOR ARG2 );

static TgVOID
tgTST_KN_Query_Monitor_Max_Resolution(
    TgUINT_E32_P OUT0, TgUINT_E32_P OUT1, HMONITOR ARG2 );

static TgVOID
tgTST_KN_Query_Swap_Context_Mode_Width_and_Height(
    TgUINT_E32_P OUT0, TgUINT_E32_P OUT1, HWND ARG2 );

static TgVOID
tgTST_KN_Query_Swap_Context_Closest_Mode_Rounded_Down(
    TgUINT_E32_P OUT0, TgUINT_E32_P OUT1, HWND ARG2 );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_OS_Module_Init ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_OS_Module_Init( TgVOID )
{
    /* Clear the platform specific data */
    tgMM_Set_U08_0x00( g_asKN_Wnd, sizeof(g_asKN_Wnd) );
    tgCM_UT_LF__ST__Init_PreLoad( &g_sKN_GPU_OS_HWND__Free_Stack.m_sStack, g_asKN_Wnd, sizeof( STg2_KN_OS_HWND ), KTgKN_MAX_WINDOWS );
    tgCM_UT_LF__ST__Init( &g_sKN_GPU_OS_HWND__Term_Stack.m_sStack );
    TgSTD_ATOMIC(store)( &g_xuiKN_Wnd_Request, 0 );
    TgSTD_ATOMIC(store)( &g_xuiKN_Wnd_Served, 0 );
    TgSTD_ATOMIC(store)( &g_xuiKN_Wnd_Closed, 0 );
    tgPM_MT_SM_Init( &g_sKN_Window_Instance_Search_Lock, u8"TgKN_GPU_OS: Window_Instance_Search", 1, 1 );
    tgPM_MT_SM_Init( &g_sKN_Window_Creation_Lock, u8"TgKN_GPU_OS: Window_Creation", 1, 1 );
    g_bKN_Close_Windows = true;

    tgMM_Set_U08_0x00( g_szKN_Default_Class_Name, sizeof( g_szKN_Default_Class_Name ) );
    tgMM_Set_U08_0x00( g_szKN_Default_Window_Title, sizeof( g_szKN_Default_Window_Title ) );
    g_uiKN_Default_Window_Style = 0;
    g_pfnKN_Default_WndProc = tgKN_OS_Base_Window_Update;

    g_iKN_Window_PadX = 0;
    g_iKN_Window_PadY = 0;

    g_pfnKN_GUI_Keyboard_Handler = nullptr;
    g_pfnKN_GUI_Mouse_Handler = nullptr;

    g_pfnDevice_Change_Check = nullptr;
    g_pfnQuery_Monitor_Min_Resolution = nullptr;
    g_pfnQuery_Monitor_Max_Resolution = nullptr;
    g_pfnQuery_CXT_SWAP_Query_Mode = nullptr;
    g_pfnQuery_CXT_SWAP_Query_Mode_Rounded_Down = nullptr;

#if !defined(TgBUILD_UNIVERSAL__UWP)
    /* API Set: api-ms-win-core-com-l1-1-1 */
    if (!tgGB_Load_Lib( &s_hDLL_Core_COM, TgOS_TEXT("api-ms-win-core-com-l1-1-1") ))
    {
        TgCRITICAL_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to load API set api-ms-win-core-com-l1-1-1" );
        tgKN_OS_Module_Free();
        return (KTgE_FAIL);
    };

    if (
           !tgGB_Get_Func_Address( (FARPROC*)&g_pfnCoInitializeEx, s_hDLL_Core_COM, ("CoInitializeEx") )
        || !tgGB_Get_Func_Address( (FARPROC*)&g_pfnCoUninitialize, s_hDLL_Core_COM, ("CoUninitialize") )
        || !tgGB_Get_Func_Address( (FARPROC*)&g_pfnCoTaskMemFree, s_hDLL_Core_COM, ("CoTaskMemFree") )
    )
    {
        TgCRITICAL_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to find function in api-ms-win-core-com-l1-1-1" );
        tgKN_OS_Module_Free();
        return (KTgE_FAIL);
    };

    /* API Set: api-ms-win-core-errorhandling-l1-1-0 */
    if (!tgGB_Load_Lib( &s_hDLL_Core_Error, TgOS_TEXT("api-ms-win-core-errorhandling-l1-1-0") ))
    {
        TgCRITICAL_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to load api-ms-win-core-errorhandling-l1-1-0" );
        tgKN_OS_Module_Free();
        return (KTgE_FAIL);
    };

    if (
           !tgGB_Get_Func_Address( (FARPROC*)&g_pfnRaiseException, s_hDLL_Core_Error, ("RaiseException") )
        || !tgGB_Get_Func_Address( (FARPROC*)&g_pfnGetLastError, s_hDLL_Core_Error, ("GetLastError") )
        )
    {
        TgCRITICAL_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to find function in api-ms-win-core-errorhandling-l1-1-0" );
        tgKN_OS_Module_Free();
        return (KTgE_FAIL);
    };

    /* Load the Shell functions from the DLL */
    if (!tgGB_Load_Lib( &s_hDLL_Shell32, TgOS_TEXT("shell32.dll") ))
    {
        TgCRITICAL_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to load Shell32 DLL." );
        tgKN_OS_Module_Free();
        return (KTgE_FAIL);
    };

    if (
           !tgGB_Get_Func_Address( (FARPROC*)&g_pfnSHGetKnownFolderPath, s_hDLL_Shell32, ("SHGetKnownFolderPath") )
        )
    {
        TgCRITICAL_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to find function in Shell32 DLL" );
        tgKN_OS_Module_Free();
        return (KTgE_FAIL);
    };

    /* Load the user functions from the DLL */
    if (!tgGB_Load_Lib( &s_hDLL_User32, TgOS_TEXT("user32.dll") ))
    {
        TgCRITICAL_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to load User32 DLL." );
        tgKN_OS_Module_Free();
        return (KTgE_FAIL);
    };

    if (
           !tgGB_Get_Func_Address( (FARPROC*)&g_pfnSetCursor, s_hDLL_User32, ("SetCursor") )
        )
    {
        TgCRITICAL_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to find function in User32 DLL" );
        tgKN_OS_Module_Free();
        return (KTgE_FAIL);
    };

    /* API Set: ext-ms-win-ntuser-sysparams-ext-l1-1-1 */
    if (!tgGB_Load_Lib( &s_hDLL_ext_ms_win_ntuser_sysparams_ext_l1_1_1, TgOS_TEXT("ext-ms-win-ntuser-sysparams-ext-l1-1-1") ))
    {
        TgCRITICAL_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to load ext-ms-win-ntuser-sysparams-ext-l1-1-1" );
        tgKN_OS_Module_Free();
        return (KTgE_FAIL);
    };

    if (
           !tgGB_Get_Func_Address( (FARPROC *)&g_pfnMonitorFromWindow, s_hDLL_ext_ms_win_ntuser_sysparams_ext_l1_1_1, "MonitorFromWindow" )
        || !tgGB_Get_Func_Address( (FARPROC *)&g_pfnGetMonitorInfo, s_hDLL_ext_ms_win_ntuser_sysparams_ext_l1_1_1, TFCN( GetMonitorInfo ) )
        || !tgGB_Get_Func_Address( (FARPROC *)&g_pfnMonitorFromRect, s_hDLL_ext_ms_win_ntuser_sysparams_ext_l1_1_1, ("MonitorFromRect") )
        || !tgGB_Get_Func_Address( (FARPROC *)&g_pfnEnumDisplayMonitors, s_hDLL_ext_ms_win_ntuser_sysparams_ext_l1_1_1, ("EnumDisplayMonitors") )
        )
    {
        TgCRITICAL_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to find function in ext-ms-win-ntuser-sysparams-ext-l1-1-1" );
        tgKN_OS_Module_Free();
        return (KTgE_FAIL);
    };

    /* API Set: ext-ms-win-ntuser-windowclass-l1-1-0 */
    if (!tgGB_Load_Lib( &s_hDLL_ext_ms_win_ntuser_windowclass_l1_1_0, TgOS_TEXT("ext-ms-win-ntuser-windowclass-l1-1-0") ))
    {
        TgCRITICAL_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to load ext-ms-win-ntuser-windowclass-l1-1-0" );
        tgKN_OS_Module_Free();
        return (KTgE_FAIL);
    };

    if (
           !tgGB_Get_Func_Address( (FARPROC *)&g_pfnRegisterClassEx, s_hDLL_ext_ms_win_ntuser_windowclass_l1_1_0, TFCN( RegisterClassEx ) )
        || !tgGB_Get_Func_Address( (FARPROC *)&g_pfnUnregisterClass, s_hDLL_ext_ms_win_ntuser_windowclass_l1_1_0, TFCN( UnregisterClass ) )
        || !tgGB_Get_Func_Address( (FARPROC *)&g_pfnGetWindowLongPtr, s_hDLL_ext_ms_win_ntuser_windowclass_l1_1_0, TFCN( GetWindowLongPtr ) )
        || !tgGB_Get_Func_Address( (FARPROC *)&g_pfnSetWindowLongPtr, s_hDLL_ext_ms_win_ntuser_windowclass_l1_1_0, TFCN( SetWindowLongPtr ) )
        )
    {
        TgCRITICAL_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to find function in ext-ms-win-ntuser-windowclass-l1-1-0" );
        tgKN_OS_Module_Free();
        return (KTgE_FAIL);
    };

    /* API Set: ext-ms-win-ntuser-window-l1-1-0 */
    if (!tgGB_Load_Lib( &s_hDLL_ext_ext_ms_win_ntuser_window_l1_1_0, TgOS_TEXT("ext-ms-win-ntuser-window-l1-1-0") ))
    {
        TgCRITICAL_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to load ext-ms-win-ntuser-window-l1-1-0" );
        tgKN_OS_Module_Free();
        return (KTgE_FAIL);
    };

    if (
           !tgGB_Get_Func_Address( (FARPROC *)&g_pfnCreateWindowEx, s_hDLL_ext_ext_ms_win_ntuser_window_l1_1_0, TFCN( CreateWindowEx ) )
        || !tgGB_Get_Func_Address( (FARPROC *)&g_pfnDestroyWindow, s_hDLL_ext_ext_ms_win_ntuser_window_l1_1_0, "DestroyWindow" )
        || !tgGB_Get_Func_Address( (FARPROC *)&g_pfnShowWindow, s_hDLL_ext_ext_ms_win_ntuser_window_l1_1_0, "ShowWindow" )
        || !tgGB_Get_Func_Address( (FARPROC *)&g_pfnGetWindowRect, s_hDLL_ext_ext_ms_win_ntuser_window_l1_1_0, "GetWindowRect" )
        || !tgGB_Get_Func_Address( (FARPROC *)&g_pfnGetClientRect, s_hDLL_ext_ext_ms_win_ntuser_window_l1_1_0, "GetClientRect" )
        || !tgGB_Get_Func_Address( (FARPROC *)&g_pfnFindWindow, s_hDLL_ext_ext_ms_win_ntuser_window_l1_1_0, TFCN( FindWindow ) )
        || !tgGB_Get_Func_Address( (FARPROC *)&g_pfnIsIconic, s_hDLL_ext_ext_ms_win_ntuser_window_l1_1_0, "IsIconic" )
        || !tgGB_Get_Func_Address( (FARPROC *)&g_pfnSetForegroundWindow, s_hDLL_ext_ext_ms_win_ntuser_window_l1_1_0, "SetForegroundWindow" )
        || !tgGB_Get_Func_Address( (FARPROC *)&g_pfnDefWindowProc, s_hDLL_ext_ext_ms_win_ntuser_window_l1_1_0, TFCN( DefWindowProc ) )
        || !tgGB_Get_Func_Address( (FARPROC *)&g_pfnSetWindowPos, s_hDLL_ext_ext_ms_win_ntuser_window_l1_1_0, "SetWindowPos" )
        )
    {
        TgCRITICAL_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to find function in ext-ms-win-ntuser-window-l1-1-0" );
        tgKN_OS_Module_Free();
        return (KTgE_FAIL);
    };

    /* API Set: ext-ms-win-ntuser-window-l1-1-2 */
    if (!tgGB_Load_Lib( &s_hDLL_ext_ms_win_ntuser_window_l1_1_2, TgOS_TEXT("ext-ms-win-ntuser-window-l1-1-2") ))
    {
        TgCRITICAL_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to load ext-ms-win-ntuser-window-l1-1-2" );
        tgKN_OS_Module_Free();
        return (KTgE_FAIL);
    };

    if (
           !tgGB_Get_Func_Address( (FARPROC *)&g_pfnScreenToClient, s_hDLL_ext_ms_win_ntuser_window_l1_1_2, "ScreenToClient" )
        )
    {
        TgCRITICAL_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to find function in ext-ms-win-ntuser-window-l1-1-2" );
        tgKN_OS_Module_Free();
        return (KTgE_FAIL);
    };

    /* API Set: ext-ms-win-ntuser-window-l1-1-3 */
    if (!tgGB_Load_Lib( &s_hDLL_ext_ms_win_ntuser_window_l1_1_3, TgOS_TEXT("ext-ms-win-ntuser-window-l1-1-3") ))
    {
        TgCRITICAL_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to load ext-ms-win-ntuser-window-l1-1-3" );
        tgKN_OS_Module_Free();
        return (KTgE_FAIL);
    };

    if (
           !tgGB_Get_Func_Address( (FARPROC *)&g_pfnSetWindowText, s_hDLL_ext_ms_win_ntuser_window_l1_1_3, TFCN( SetWindowText ) )
        )
    {
        TgCRITICAL_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to find function in ext-ms-win-ntuser-window-l1-1-3" );
        tgKN_OS_Module_Free();
        return (KTgE_FAIL);
    };

    /* API Set: ext-ms-win-ntuser-draw-l1-1-0 */
    if (!tgGB_Load_Lib( &s_hDLL_ext_ms_win_ntuser_draw_l1_1_0, TgOS_TEXT("ext-ms-win-ntuser-draw-l1-1-0") ))
    {
        TgCRITICAL_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to load ext-ms-win-ntuser-draw-l1-1-0" );
        tgKN_OS_Module_Free();
        return (KTgE_FAIL);
    };

    if (
           !tgGB_Get_Func_Address( (FARPROC *)&g_pfnUpdateWindow, s_hDLL_ext_ms_win_ntuser_draw_l1_1_0, "UpdateWindow" )
        )
    {
        TgCRITICAL_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to find function in ext-ms-win-ntuser-draw-l1-1-0" );
        tgKN_OS_Module_Free();
        return (KTgE_FAIL);
    };

    /* API Set: ext-ms-win-ntuser-message-l1-1-0 */
    if (!tgGB_Load_Lib( &s_hDLL_ext_ms_win_ntuser_message_l1_1_0, TgOS_TEXT("ext-ms-win-ntuser-message-l1-1-0") ))
    {
        TgCRITICAL_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to load ext-ms-win-ntuser-message-l1-1-0" );
        tgKN_OS_Module_Free();
        return (KTgE_FAIL);
    };

    if (
           !tgGB_Get_Func_Address( (FARPROC *)&g_pfnPeekMessage, s_hDLL_ext_ms_win_ntuser_message_l1_1_0, TFCN( PeekMessage ) )
        || !tgGB_Get_Func_Address( (FARPROC *)&g_pfnGetMessage, s_hDLL_ext_ms_win_ntuser_message_l1_1_0, TFCN( GetMessage ) )
        || !tgGB_Get_Func_Address( (FARPROC *)&g_pfnTranslateMessage, s_hDLL_ext_ms_win_ntuser_message_l1_1_0, "TranslateMessage" )
        || !tgGB_Get_Func_Address( (FARPROC *)&g_pfnPostQuitMessage, s_hDLL_ext_ms_win_ntuser_message_l1_1_0, "PostQuitMessage" )
        || !tgGB_Get_Func_Address( (FARPROC *)&g_pfnDispatchMessage, s_hDLL_ext_ms_win_ntuser_message_l1_1_0, TFCN( DispatchMessage ) )
        || !tgGB_Get_Func_Address( (FARPROC *)&g_pfnSendMessage, s_hDLL_ext_ms_win_ntuser_message_l1_1_0, TFCN( SendMessage ) )
        || !tgGB_Get_Func_Address( (FARPROC *)&g_pfnPostMessage, s_hDLL_ext_ms_win_ntuser_message_l1_1_0, TFCN( PostMessage ) )
        )
    {
        TgCRITICAL_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to find function in ext-ms-win-ntuser-message-l1-1-0" );
        tgKN_OS_Module_Free();
        return (KTgE_FAIL);
    };
    
#else
#error
/*# !defined(TgBUILD_UNIVERSAL__UWP) */
#endif

    return (KTgS_OK);
}


/* ---- tgKN_OS_Module_Boot ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_OS_Module_Boot( TgVOID )
{
    TgSINT_E32                          iArg;

    if (nullptr == g_pfnCoInitializeEx)
    {
        TgCRITICAL_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to find COM Init function in DLL." );
        return (KTgE_FAIL);
    }
    else
    {
        TgSINT_E32                          iResult;

        iResult = g_pfnCoInitializeEx( nullptr, 0 );
        if (TgFAILED( iResult ))
        {
            TgCRITICAL_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to initialize COM layer." );
            return (KTgE_FAIL);
        };
    };

    /* Create an instance of the FS-HD and create a mount point at the execution root */
    {
        TgCHAR_U8_P                         pszBuffer;

        pszBuffer = (TgCHAR_U8_P)TgMALLOC_TEMP( sizeof(TgCHAR_U8)*KTgMAX_FILE_PATH );
        if (nullptr != pszBuffer)
        {
            tgKN_Path_Query_Application_Data_Folder( pszBuffer, KTgMAX_FILE_PATH );
            if (0 != pszBuffer[0])
            {
                tgUSZ_Append( pszBuffer, sizeof(TgCHAR_U8)*KTgMAX_FILE_PATH, u8"\\Teikitu", KTgMAX_RSIZE );
                g_tiKN_FS_HDD__Mount_APP = tgKN_File_System_Mount( g_tiKN_FS_HDD, ETgFILE_IO_ACCESS__READ | ETgFILE_IO_ACCESS__WRITE | ETgFILE_IO_ACCESS__SHARED, pszBuffer );
            };
            TgFREE_TEMP(pszBuffer);
        }
    }

    /* Create defaults for any uninitialized values required by Windows OS. This gives the application a chance between init and boot to set them. */

    if (0 == g_szKN_Default_Class_Name[0])
    {
        TgOS_TEXT_FCN(Copy)( g_szKN_Default_Class_Name, KTgKN_MAX_TITLE, TgOS_TEXT("Teikitu Class"), KTgMAX_RSIZE );
    };

    if (0 == g_szKN_Default_Window_Title[0])
    {
        TgOS_TEXT_FCN(Copy)( g_szKN_Default_Window_Title, KTgKN_MAX_TITLE, TgOS_TEXT("Teikitu Window"), KTgMAX_RSIZE );
    };

    if (0 == g_uiKN_Default_Window_Style)
    {
        g_uiKN_Default_Window_Style = WS_BORDER | WS_CAPTION | WS_SYSMENU | WS_VISIBLE | WS_THICKFRAME; // 0x0040
    };

    /* Look for Unit Test argument to default the render related functions */

    iArg = tgGB_CMD_Query_Argument_Index( u8"-//test/unit/kernel" );
    if (iArg >= 0)
    {
        TgCRITICAL( nullptr == g_pfnDevice_Change_Check );
        TgCRITICAL( nullptr == g_pfnQuery_Monitor_Min_Resolution );
        TgCRITICAL( nullptr == g_pfnQuery_Monitor_Max_Resolution );
        TgCRITICAL( nullptr == g_pfnQuery_CXT_SWAP_Query_Mode );
        TgCRITICAL( nullptr == g_pfnQuery_CXT_SWAP_Query_Mode_Rounded_Down );

        g_pfnDevice_Change_Check = tgTST_KN_Device_Change_Check;
        g_pfnQuery_Monitor_Min_Resolution = tgTST_KN_Query_Monitor_Min_Resolution;
        g_pfnQuery_Monitor_Max_Resolution = tgTST_KN_Query_Monitor_Max_Resolution;
        g_pfnQuery_CXT_SWAP_Query_Mode = tgTST_KN_Query_Swap_Context_Mode_Width_and_Height;
        g_pfnQuery_CXT_SWAP_Query_Mode_Rounded_Down = tgTST_KN_Query_Swap_Context_Closest_Mode_Rounded_Down;
    };

#if defined(TgBUILD_FEATURE__GRAPHICS)
    TgCRITICAL( nullptr != g_pfnDevice_Change_Check );
    TgCRITICAL( nullptr != g_pfnQuery_Monitor_Min_Resolution );
    TgCRITICAL( nullptr != g_pfnQuery_Monitor_Max_Resolution );
    TgCRITICAL( nullptr != g_pfnQuery_CXT_SWAP_Query_Mode );
    TgCRITICAL( nullptr != g_pfnQuery_CXT_SWAP_Query_Mode_Rounded_Down );
/*# defined(TgBUILD_FEATURE__GRAPHICS) */
#endif

    /* Set the window padding (AdjustRect is a MS function, and therefore does not work - calculate manually) */

    g_iKN_Window_PadX = g_pfnGetSystemMetrics( 32 ) * 4;
    g_iKN_Window_PadY = g_pfnGetSystemMetrics( 33 ) * 4 + g_pfnGetSystemMetrics( 4 );

    /* Allow windows to be created. */
    g_bKN_Close_Windows = false;

    /* Create the default set of job threads for the job manager. */
#if defined(TgBUILD_DEVICE__DESKTOP)
    {
        TgRSIZE_C                           nuiThread = tgCM_MIN_UMAX( KTgMAX_NUM_THREAD, tgSI_SYSTEM_Number_Of_Processors() );
        TgRSIZE                             uiJobThread;

        /* Create a few common scenarios for the number of processors available (hardware threads). */
        if (nuiThread <= 1)
        {
            /* Intentionally left blank - if there is only one physical hardware thread then run in synchronous mode. */
        }
        else if (nuiThread < 4)
        {
            TgJOB_QUEUE_ID_C                    atiQueueList[] = { g_sJob_Stack__JiT, g_sJob_Queue__GPU, g_sJob_Queue__Render_High, g_sJob_Queue__Client_High,
                                                                   g_sJob_Queue__Render_Normal, g_sJob_Queue__Client_Normal, g_sJob_Queue__Client_Low, g_tiJob_Queue__OS, };

            /* With [2,3] hardware threads, saturate with worker threads, which will imply that the main thread can be switched out. This assumes that the majority of the
               processing will always be done as jobs (part of the planned design). */
            for (uiJobThread = 0; uiJobThread < nuiThread; ++uiJobThread)
            {
                g_atiJob_Thread[uiJobThread] = tgJM_Spawn_Job_Thread( atiQueueList, TgARRAY_COUNT(atiQueueList), ETgTHREAD_PRIORITY__NORMAL, u8"Teikitu: Job Thread" );
                TgVERIFY(KTgID__INVALID_VALUE != g_atiJob_Thread[uiJobThread].m_uiKI);
            };
        }
        else if (nuiThread < 8)
        {
            TgJOB_QUEUE_ID_C                    atiQueueList[] = { g_sJob_Stack__JiT, g_sJob_Queue__GPU, g_sJob_Queue__Render_High, g_sJob_Queue__Client_High,
                                                                   g_sJob_Queue__Render_Normal, g_sJob_Queue__Client_Normal, g_sJob_Queue__Client_Low, g_tiJob_Queue__OS, };

            /* With [4,7] threads, a hardware core is left free for the OS to use without impacting the application. */
            for (uiJobThread = 0; uiJobThread < nuiThread - 1; ++uiJobThread)
            {
                g_atiJob_Thread[uiJobThread] = tgJM_Spawn_Job_Thread( atiQueueList, TgARRAY_COUNT(atiQueueList), ETgTHREAD_PRIORITY__NORMAL, u8"Teikitu: Job Thread" );
                TgVERIFY(KTgID__INVALID_VALUE != g_atiJob_Thread[uiJobThread].m_uiKI);
            };
        }
        else
        {
            TgJOB_QUEUE_ID_C                    atiQueueList0[] = { g_sJob_Stack__JiT, g_tiJob_Queue__OS, g_sJob_Queue__GPU, g_sJob_Queue__Render_High, g_sJob_Queue__Client_High,
                                                                    g_sJob_Queue__Render_Normal, g_sJob_Queue__Client_Normal, g_sJob_Queue__Client_Low };
            TgJOB_QUEUE_ID_C                    atiQueueList1[] = { g_sJob_Queue__Client_High, g_sJob_Queue__Client_Normal, g_sJob_Queue__Client_Low };
            TgJOB_QUEUE_ID_C                    atiQueueList2[] = { g_sJob_Queue__GPU, g_sJob_Queue__Render_High, g_sJob_Queue__Render_Normal };

            /* With [8,inf] threads, a hardware core is left free for the OS to use without impacting the application. The remaining cores are split between general use, 
               rendering, and client thread pools. */
            for (uiJobThread = 0; uiJobThread < nuiThread >> 2; ++uiJobThread)
            {
                g_atiJob_Thread[uiJobThread] = tgJM_Spawn_Job_Thread( atiQueueList2, TgARRAY_COUNT(atiQueueList2), ETgTHREAD_PRIORITY__HIGHEST, u8"Teikitu: Job Thread" );
                TgVERIFY(KTgID__INVALID_VALUE != g_atiJob_Thread[uiJobThread].m_uiKI);
            };
            for (; uiJobThread < nuiThread >> 1; ++uiJobThread)
            {
                g_atiJob_Thread[uiJobThread] = tgJM_Spawn_Job_Thread( atiQueueList1, TgARRAY_COUNT(atiQueueList1), ETgTHREAD_PRIORITY__HIGHEST, u8"Teikitu: Job Thread" );
                TgVERIFY(KTgID__INVALID_VALUE != g_atiJob_Thread[uiJobThread].m_uiKI);
            };
            for (; uiJobThread < nuiThread - 1; ++uiJobThread)
            {
                g_atiJob_Thread[uiJobThread] = tgJM_Spawn_Job_Thread( atiQueueList0, TgARRAY_COUNT(atiQueueList0), ETgTHREAD_PRIORITY__NORMAL, u8"Teikitu: Job Thread" );
                TgVERIFY(KTgID__INVALID_VALUE != g_atiJob_Thread[uiJobThread].m_uiKI);
            };
        };
    };

#else
    //#error Unsupported Device
#endif

    return (KTgS_OK);
}


/* ---- tgKN_OS_Module_Stop ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_OS_Module_Stop( TgVOID )
{
    TgUINT_E64                          uiClosed, uiRequest;

    /* Make sure we stop allowing new windows to be created. */
    g_bKN_Close_Windows = true;

    /* Keep looping to clean up the window threads until they have all been closed. */
    uiRequest = uiClosed = TgSTD_ATOMIC(load)( &g_xuiKN_Wnd_Closed );
    while(!TgSTD_ATOMIC(compare_exchange_weak)( &g_xuiKN_Wnd_Request, &uiRequest, uiClosed ))
    {
        tgKN_OS_Clean_Up_Window_Threads();
        uiRequest = uiClosed = TgSTD_ATOMIC(load)( &g_xuiKN_Wnd_Closed );
    }

#if defined(TgBUILD_DEVICE__DESKTOP)
    {
        TgRSIZE                             uiJobThread;

        for (uiJobThread = 0; uiJobThread < KTgMAX_NUM_THREAD; ++uiJobThread)
        {
            if (KTgID__INVALID_VALUE == g_atiJob_Thread[uiJobThread].m_uiKI)
                continue;
            tgJM_Stop_Job_Thread( g_atiJob_Thread[uiJobThread] );
            g_atiJob_Thread[uiJobThread].m_uiKI = KTgID__INVALID_VALUE;
        };
    };
#else
    #error Unsupported Device
#endif

    tgPM_MT_SM_Free( &g_sKN_Window_Creation_Lock );
    tgPM_MT_SM_Free( &g_sKN_Window_Instance_Search_Lock );
    g_pfnCoUninitialize();
    return (KTgS_OK);
}


/* ---- tgKN_OS_Module_Free ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_OS_Module_Free( TgVOID )
{
#if !defined(TgBUILD_UNIVERSAL__UWP)
    if (nullptr != s_hDLL_Core_COM)
    {
        tgGB_Free_Lib( &s_hDLL_Core_COM );
        s_hDLL_Core_COM = nullptr;
    };

    if (nullptr != s_hDLL_Core_Error)
    {
        tgGB_Free_Lib( &s_hDLL_Core_Error );
        s_hDLL_Core_Error = nullptr;
    };

    if (nullptr != s_hDLL_Shell32)
    {
        tgGB_Free_Lib( &s_hDLL_Shell32 );
        s_hDLL_Shell32 = nullptr;
    };

    if (nullptr != s_hDLL_User32)
    {
        tgGB_Free_Lib( &s_hDLL_User32 );
        s_hDLL_User32 = nullptr;
    };

    if (nullptr != s_hDLL_ext_ms_win_ntuser_sysparams_ext_l1_1_1)
    {
        tgGB_Free_Lib( &s_hDLL_ext_ms_win_ntuser_sysparams_ext_l1_1_1 );
        s_hDLL_ext_ms_win_ntuser_sysparams_ext_l1_1_1 = nullptr;
    };

    if (nullptr != s_hDLL_ext_ms_win_ntuser_windowclass_l1_1_0)
    {
        tgGB_Free_Lib( &s_hDLL_ext_ms_win_ntuser_windowclass_l1_1_0 );
        s_hDLL_ext_ms_win_ntuser_windowclass_l1_1_0 = nullptr;
    };

    if (nullptr != s_hDLL_ext_ext_ms_win_ntuser_window_l1_1_0)
    {
        tgGB_Free_Lib( &s_hDLL_ext_ext_ms_win_ntuser_window_l1_1_0 );
        s_hDLL_ext_ext_ms_win_ntuser_window_l1_1_0 = nullptr;
    };

    if (nullptr != s_hDLL_ext_ms_win_ntuser_window_l1_1_2)
    {
        tgGB_Free_Lib( &s_hDLL_ext_ms_win_ntuser_window_l1_1_2 );
        s_hDLL_ext_ms_win_ntuser_window_l1_1_2 = nullptr;
    };

    if (nullptr != s_hDLL_ext_ms_win_ntuser_window_l1_1_3)
    {
        tgGB_Free_Lib( &s_hDLL_ext_ms_win_ntuser_window_l1_1_3 );
        s_hDLL_ext_ms_win_ntuser_window_l1_1_3 = nullptr;
    };

    if (nullptr != s_hDLL_ext_ms_win_ntuser_draw_l1_1_0)
    {
        tgGB_Free_Lib( &s_hDLL_ext_ms_win_ntuser_draw_l1_1_0 );
        s_hDLL_ext_ms_win_ntuser_draw_l1_1_0 = nullptr;
    };

    if (nullptr != s_hDLL_ext_ms_win_ntuser_message_l1_1_0)
    {
        tgGB_Free_Lib( &s_hDLL_ext_ms_win_ntuser_message_l1_1_0 );
        s_hDLL_ext_ms_win_ntuser_message_l1_1_0 = nullptr;
    };

    /*# !defined(TgBUILD_UNIVERSAL__UWP) */
#endif

    return (KTgS_OK);
}


/* ---- tgKN_OS_Module_Update ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_OS_Module_Update( TgATTRIBUTE_UNUSED TgFLOAT32_C fDT )
{
    tgKN_OS_Clean_Up_Window_Threads();

    return (KTgS_OK);
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_OS_Clean_Up_Window_Threads ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgKN_OS_Clean_Up_Window_Threads( TgVOID )
{
    union
    {
        STg2_KN_OS_HWND_P                   ps;
        STg2_UT_ST__ST_Node_P               pNode;
    }                                   sHWND;

    sHWND.pNode = tgCM_UT_LF__ST__Pop( &g_sKN_GPU_OS_HWND__Term_Stack.m_sStack );
    while (nullptr != sHWND.pNode)
    {
        g_pfnDestroyWindow( sHWND.ps->m_hWnd );
        tgTR_Close( sHWND.ps->m_tiThread );
        sHWND.ps->m_tiThread = KTgTHREAD_ID__INVALID;
        TgSTD_ATOMIC(fetch_add)( &g_xuiKN_Wnd_Closed, 1 );
        sHWND.pNode = tgCM_UT_LF__ST__Pop( &g_sKN_GPU_OS_HWND__Term_Stack.m_sStack );
    };
    TgSTD_ATOMIC(thread_fence)( TgSTD_MEMORY_ORDER(seq_cst) );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Unit Test Functions                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

static TgUINT_E32_C s_iTST_KN__W_List[] = { 320,640,720,720,800,1024,1152,1280,1280,1280,1280,1280,1360,1600,1600,1600,1680,1920,1920 };
static TgUINT_E32_C s_iTST_KN__H_List[] = { 240,480,480,576,600,768,864,720,768,800,960,1024,768,900,1024,1200,1050,1080,1200 };

/* ---- tgTST_KN_Device_Change_Check --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgTST_KN_Device_Change_Check( TgATTRIBUTE_UNUSED HWND hWnd, TgATTRIBUTE_UNUSED STg2_KN_OS_Window_Configuration_PC psConfig )
{

}


/* ---- tgTST_KN_Query_Monitor_Min_Resolution ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgTST_KN_Query_Monitor_Min_Resolution( TgUINT_E32_P puiW, TgUINT_E32_P puiH, TgATTRIBUTE_UNUSED HMONITOR hMonitor )
{
    *puiW = s_iTST_KN__W_List[0];
    *puiH = s_iTST_KN__H_List[0];
}


/* ---- tgTST_KN_Query_Monitor_Max_Resolution ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgTST_KN_Query_Monitor_Max_Resolution( TgUINT_E32_P puiW, TgUINT_E32_P puiH, TgATTRIBUTE_UNUSED HMONITOR hMonitor )
{
    *puiW = s_iTST_KN__W_List[(sizeof( s_iTST_KN__W_List ) / sizeof( s_iTST_KN__W_List[0] )) - 1];
    *puiH = s_iTST_KN__H_List[(sizeof( s_iTST_KN__W_List ) / sizeof( s_iTST_KN__W_List[0] )) - 1];
}


/* ---- tgTST_KN_Query_Swap_Context_Mode_Width_and_Height ------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgTST_KN_Query_Swap_Context_Mode_Width_and_Height( TgUINT_E32_P puiW, TgUINT_E32_P puiH, TgATTRIBUTE_UNUSED HWND hWnd )
{
    *puiW = s_iTST_KN__W_List[0];
    *puiH = s_iTST_KN__H_List[0];
}


/* ---- tgTST_KN_Query_Swap_Context_Closest_Mode_Rounded_Down -------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgTST_KN_Query_Swap_Context_Closest_Mode_Rounded_Down( TgUINT_E32_P puiW, TgUINT_E32_P puiH, TgATTRIBUTE_UNUSED HWND hWnd )
{
    TgSINT_E32_C                        uiMaxModes = sizeof( s_iTST_KN__W_List ) / sizeof( s_iTST_KN__W_List[0] );
    TgSINT_E32                          iIndex = 0;
    TgUINT_E32                          iW = *puiW;
    TgUINT_E32                          iH = *puiH;

    if (s_iTST_KN__W_List[iIndex] < iW)
    {
        for (++iIndex; iIndex < uiMaxModes; ++iIndex)
        {
            if (s_iTST_KN__W_List[iIndex] > iW)
            {
                break;
            };
        };
        --iIndex;
    };

    iW = s_iTST_KN__W_List[iIndex];
    if (0 == iIndex)
    {
        for (++iIndex; iIndex < uiMaxModes; ++iIndex)
        {
            if (s_iTST_KN__W_List[iIndex] > iW)
            {
                break;
            };
        };
        --iIndex;
    };

    if (s_iTST_KN__H_List[iIndex] > iH)
    {
        for (; iIndex > 0; --iIndex)
        {
            if (s_iTST_KN__H_List[iIndex] < iH || s_iTST_KN__W_List[iIndex - 1] != iW)
            {
                break;
            };
        };
    };

    iH = s_iTST_KN__H_List[iIndex];
    if (0 == iIndex || s_iTST_KN__W_List[iIndex - 1] != iW)
    {
        for (++iIndex; iIndex < uiMaxModes && s_iTST_KN__W_List[iIndex] == iW && s_iTST_KN__H_List[iIndex] == iH; ++iIndex);
        --iIndex;
    };

    *puiW = iW;
    *puiH = iH;
}
