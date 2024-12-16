/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (WINDOWS) Kernel - System.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

static TgVOID
tgKN_OS_Set_Window_Title_Internal(
    TgSINT_PTR_C iWindow_Index, STg2_KN_OS_Window_Configuration_CPC psConfig, TgOSCHAR_CPC oszText, TgRSIZE_C nuiText );

static TgUINT_E32
tgKN_OS_Create_Window_Thread(
    TgUINT_PTR_C ) TgATTRIBUTE_NO_EXCEPT;




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_OS_Create_Window ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgSINT_PTR tgKN_OS_Create_Window( STg2_KN_OS_Window_Configuration_CPC psKN_OS_Window_Configuration )
{
    TgSINT_E32_C                        iMultiple_Instance = tgGB_CMD_Query_Argument_Index( u8"-multiple_instance" );

    union
    {
        STg2_KN_OS_HWND_P                   ps;
        STg2_UT_ST__ST_Node_P               pNode;
    }                                   sHWND;
    TgSINT_PTR                          iWindow;
    HMONITOR                            hMonitor;
    RECT                                sRect;

    if (g_bKN_Close_Windows || nullptr == psKN_OS_Window_Configuration)
    {
        return (-1);
    };

    /* Check to see if multiple instances of this application are allowed */

    tgPM_MT_SM_Wait_Block( &g_sKN_Window_Instance_Search_Lock );

    if (0 > iMultiple_Instance)
    {
        HWND                                hWnd;

        if (0 == psKN_OS_Window_Configuration->m_szClass_Name[0])
        {
            hWnd = g_pfnFindWindow( g_szKN_Default_Class_Name, nullptr );
        }
        else
        {
            hWnd = g_pfnFindWindow( psKN_OS_Window_Configuration->m_szClass_Name, nullptr );
        };

        if (hWnd)
        {
            if (g_pfnIsIconic( hWnd ))
            {
                g_pfnShowWindow( hWnd, 9 );
            };

            g_pfnSetForegroundWindow( hWnd );

            tgPM_MT_SM_Signal( &g_sKN_Window_Instance_Search_Lock, 1 );
            return (-1);
        };
    };

    /* Acquire the data structure that holds all of the creation criteria for the new window */
    TgSTD_ATOMIC(fetch_add)( &g_xuiKN_Wnd_Request, 1 );
    sHWND.pNode = tgCM_UT_LF__ST__Pop( &g_sKN_GPU_OS_HWND__Free_Stack.m_sStack );
    if (nullptr == sHWND.pNode)
    {
        TgSTD_ATOMIC(fetch_add)( &g_xuiKN_Wnd_Served, 1 );
        TgSTD_ATOMIC(fetch_add)( &g_xuiKN_Wnd_Closed, 1 );
        tgPM_MT_SM_Signal( &g_sKN_Window_Instance_Search_Lock, 1 );
        return (-1);
    };

    TgVERIFY(nullptr ==sHWND.ps->m_hWnd);

    iWindow = (TgSINT_PTR)(sHWND.ps - g_asKN_Wnd);
    sHWND.ps->m_enState = ETgMODULE_STATE__INITIALIZING;
    tgMM_Copy( &sHWND.ps->m_sConfig, sizeof(sHWND.ps->m_sConfig), psKN_OS_Window_Configuration, sizeof(STg2_KN_OS_Window_Configuration) );

    /* Create defaults for any uninitialized values required by Windows OS */

    if (0 == psKN_OS_Window_Configuration->m_szDefault_Title[0])
    {
        TgOS_TEXT_FCN(PrintF)( sHWND.ps->m_sConfig.m_szDefault_Title, sizeof(sHWND.ps->m_sConfig.m_szDefault_Title), TgOS_TEXT("%s [%d]"), g_szKN_Default_Window_Title, iWindow );
    };

    if (0 == psKN_OS_Window_Configuration->m_szTitle[0])
    {
        TgOS_TEXT_FCN(PrintF)( sHWND.ps->m_sConfig.m_szTitle, sizeof(sHWND.ps->m_sConfig.m_szTitle), TgOS_TEXT("%s"), sHWND.ps->m_sConfig.m_szDefault_Title );
    };

    if (0 == psKN_OS_Window_Configuration->m_szClass_Name[0])
    {
        TgOS_TEXT_FCN(PrintF)( sHWND.ps->m_sConfig.m_szClass_Name, sizeof(sHWND.ps->m_sConfig.m_szClass_Name), TgOS_TEXT("%s_%d"), g_szKN_Default_Class_Name, iWindow );
    };

    if (0 == psKN_OS_Window_Configuration->m_uiWindow_Style)
    {
        sHWND.ps->m_sConfig.m_uiWindow_Style = g_uiKN_Default_Window_Style;
    };

    if (nullptr == psKN_OS_Window_Configuration->m_pfnWndProc)
    {
        sHWND.ps->m_sConfig.m_pfnWndProc = g_pfnKN_Default_WndProc;
    };

    /* Find the monitor that contains the majority of the window. */
    sRect.left = sHWND.ps->m_sConfig.m_iWindow_X0;
    sRect.top = sHWND.ps->m_sConfig.m_iWindow_Y0;
    sRect.right = sRect.left + (LONG)sHWND.ps->m_sConfig.m_uiRender_Target_W;
    sRect.bottom = sRect.top + (LONG)sHWND.ps->m_sConfig.m_uiRender_Target_H;
    hMonitor = g_pfnMonitorFromRect( &sRect, MONITOR_DEFAULTTONULL );

    /* Make sure to create the window with at least a minimal size for rendering. */
    if (g_pfnQuery_Monitor_Min_Resolution && (0 == sHWND.ps->m_sConfig.m_uiRender_Target_W || 0 == sHWND.ps->m_sConfig.m_uiRender_Target_H))
    {
        HMONITOR                            hMonitor_Test;

        g_pfnQuery_Monitor_Min_Resolution( &sHWND.ps->m_sConfig.m_uiRender_Target_W, &sHWND.ps->m_sConfig.m_uiRender_Target_H, hMonitor );
        sRect.right = sRect.left + (LONG)sHWND.ps->m_sConfig.m_uiRender_Target_W;
        sRect.bottom = sRect.top + (LONG)sHWND.ps->m_sConfig.m_uiRender_Target_H;
        hMonitor_Test = g_pfnMonitorFromRect( &sRect, MONITOR_DEFAULTTONULL );

        /* It is possible that based on the configuration of monitors that we could ping-pong between two monitors. However, we will retry once.*/
        if (hMonitor_Test != hMonitor)
        {
            g_pfnQuery_Monitor_Min_Resolution( &sHWND.ps->m_sConfig.m_uiRender_Target_W, &sHWND.ps->m_sConfig.m_uiRender_Target_H, hMonitor );
            sRect.right = sRect.left + (LONG)sHWND.ps->m_sConfig.m_uiRender_Target_W;
            sRect.bottom = sRect.top + (LONG)sHWND.ps->m_sConfig.m_uiRender_Target_H;
        };
    };

    /* Check to see if we should centre the window on the monitor. */

    if (sHWND.ps->m_sConfig.m_bCenterOnMonitor)
    {
        MONITORINFO                         sMonitor_Info;
        TgSINT_E32                          iMonitor_W, iMonitor_H;

        /* Use the monitor handle to cache the dimensions of it. */
        sMonitor_Info.cbSize = sizeof(sMonitor_Info);
        if (g_pfnGetMonitorInfo && g_pfnGetMonitorInfo( hMonitor, &sMonitor_Info ))
        {
            iMonitor_W = sMonitor_Info.rcWork.right - sMonitor_Info.rcWork.left;
            iMonitor_H = sMonitor_Info.rcWork.bottom - sMonitor_Info.rcWork.top;
        }
        else
        {
            iMonitor_W = iMonitor_H = 0;
        };

        sHWND.ps->m_sConfig.m_iWindow_X0 = (iMonitor_W >> 1) - (((TgSINT_E32)sHWND.ps->m_sConfig.m_uiRender_Target_W + g_iKN_Window_PadX) >> 1);
        sHWND.ps->m_sConfig.m_iWindow_Y0 = (iMonitor_H >> 1) - (((TgSINT_E32)sHWND.ps->m_sConfig.m_uiRender_Target_H + g_iKN_Window_PadY) >> 1);
    };

    /* Create a thread to run the window and windows message processing. */

    tgPM_MT_SM_Wait_Block( &g_sKN_Window_Creation_Lock );

    sHWND.ps->m_enState = ETgMODULE_STATE__INITIALIZED;
    TgSTD_ATOMIC(thread_fence)( TgSTD_MEMORY_ORDER(seq_cst) );
    sHWND.ps->m_tiThread = tgTR_Create( tgKN_OS_Create_Window_Thread, (TgUINT_PTR)(sHWND.ps - g_asKN_Wnd), 0, ETgTHREAD_PRIORITY__HIGHEST, u8"KN Update Windows" );

    if (sHWND.ps->m_tiThread.m_uiKI == KTgTHREAD_ID__INVALID.m_uiKI)
    {
        TgSTD_ATOMIC(fetch_add)( &g_xuiKN_Wnd_Served, 1 );
        TgSTD_ATOMIC(fetch_add)( &g_xuiKN_Wnd_Closed, 1 );
        tgCM_UT_LF__ST__Push( &g_sKN_GPU_OS_HWND__Free_Stack.m_sStack, sHWND.pNode );
        tgPM_MT_SM_Signal( &g_sKN_Window_Creation_Lock, 1 );
        tgPM_MT_SM_Signal( &g_sKN_Window_Instance_Search_Lock, 1 );
        return (-1);
    };

    /* So ... there is a high chance of a race condition here, so we are going to pause here to make sure that the HWND has been assigned into structure. */
    tgPM_MT_SM_Wait_Block( &g_sKN_Window_Creation_Lock );
    tgPM_MT_SM_Signal( &g_sKN_Window_Creation_Lock, 1 );

    return ((TgSINT_PTR)(sHWND.ps - g_asKN_Wnd));
}


/* ---- tgKN_OS_Query_Window_Handle ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
HWND tgKN_OS_Query_Window_Handle( TgSINT_PTR_C iWindow_Index )
{
    TgPARAM_CHECK_INDEX(iWindow_Index,g_asKN_Wnd);
    return (g_asKN_Wnd[iWindow_Index].m_hWnd);
}


/* ---- tgKN_OS_Query_Window_Thread_Status --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
ETgTHREAD_STATUS tgKN_OS_Query_Window_Thread_Status( TgSINT_PTR_C iWindow_Index )
{
    TgPARAM_CHECK_INDEX(iWindow_Index,g_asKN_Wnd);
    if (KTgID__INVALID_VALUE == g_asKN_Wnd[iWindow_Index].m_tiThread.m_uiKI)
        return ETgTHREAD_STATUS__INVALID;
    return (tgTR_Status(g_asKN_Wnd[iWindow_Index].m_tiThread));
}


/* ---- tgKN_OS_Query_Window_Configuration --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_OS_Query_Window_Configuration( STg2_KN_OS_Window_Configuration_PC psOut, TgSINT_PTR_C iWindow_Index )
{
    TgPARAM_CHECK_INDEX(iWindow_Index,g_asKN_Wnd);
    tgMM_Copy( psOut, sizeof(STg2_KN_OS_Window_Configuration), &g_asKN_Wnd[iWindow_Index].m_sConfig, sizeof(STg2_KN_OS_Window_Configuration) );
}


/* ---- tgKN_OS_Window_FullScreen ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_OS_Window_FullScreen( TgSINT_PTR_C iWindow_Index )
{
    DWORD                               uiStyleMask = ~(DWORD)(WS_BORDER | WS_CAPTION | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SYSMENU | WS_THICKFRAME);
    DWORD                               uiExStyleMask = ~(DWORD)(WS_EX_CLIENTEDGE | WS_EX_STATICEDGE | WS_EX_WINDOWEDGE | WS_EX_DLGMODALFRAME);
    TgSINT_E32                          iX, iY, iW, iH;
    RECT                                sRect;
    HMONITOR                            hMonitor;
    MONITORINFO                         sMonitor_Info;

    if (g_asKN_Wnd[iWindow_Index].m_sConfig.m_bFullScreen)
    {
        return;
    };

    /* Store the original window data */
    g_pfnGetWindowRect( g_asKN_Wnd[iWindow_Index].m_hWnd, &sRect );
    g_asKN_Wnd[iWindow_Index].m_iWindow_Saved_X = sRect.left;
    g_asKN_Wnd[iWindow_Index].m_iWindow_Saved_Y = sRect.top;
    g_asKN_Wnd[iWindow_Index].m_iWindow_Saved_W = (TgSINT_E32)g_asKN_Wnd[iWindow_Index].m_sConfig.m_uiRender_Target_W;
    g_asKN_Wnd[iWindow_Index].m_iWindow_Saved_H = (TgSINT_E32)g_asKN_Wnd[iWindow_Index].m_sConfig.m_uiRender_Target_H;

    /* Modify the window's style */
    g_pfnSetWindowLongPtr( g_asKN_Wnd[iWindow_Index].m_hWnd, GWL_STYLE, (long)(g_asKN_Wnd[iWindow_Index].m_sConfig.m_uiWindow_Style & uiStyleMask) );
    g_pfnSetWindowLongPtr( g_asKN_Wnd[iWindow_Index].m_hWnd, GWL_EXSTYLE, (long)(g_asKN_Wnd[iWindow_Index].m_sConfig.m_uiWindow_ExStyle & uiExStyleMask));

    /* Stretch the window to the full size of the screen */
    hMonitor = g_pfnMonitorFromWindow( g_asKN_Wnd[iWindow_Index].m_hWnd, MONITOR_DEFAULTTONULL );
    sMonitor_Info.cbSize = sizeof( sMonitor_Info );

    if (g_pfnGetMonitorInfo && g_pfnGetMonitorInfo( hMonitor, &sMonitor_Info ))
    {
        iX = sMonitor_Info.rcMonitor.left;
        iY = sMonitor_Info.rcMonitor.top;
        iW = sMonitor_Info.rcMonitor.right - sMonitor_Info.rcMonitor.left;
        iH = sMonitor_Info.rcMonitor.bottom - sMonitor_Info.rcMonitor.top;
    }
    else
    {
        iX = 0;
        iY = 0;
        iW = g_pfnGetSystemMetrics( SM_CXSCREEN );
        iH = g_pfnGetSystemMetrics( SM_CYSCREEN );
    };

    g_pfnSetWindowPos( g_asKN_Wnd[iWindow_Index].m_hWnd, HWND_TOPMOST, iX, iY, iW, iH, SWP_FRAMECHANGED | SWP_NOACTIVATE );

    g_pfnShowWindow(g_asKN_Wnd[iWindow_Index].m_hWnd, SW_MAXIMIZE);
    g_asKN_Wnd[iWindow_Index].m_sConfig.m_bFullScreen = true;
    tgKN_ReCalc_Display( iWindow_Index );
    tgKN_OS_Set_Window_Title_Internal( iWindow_Index, &g_asKN_Wnd[iWindow_Index].m_sConfig, nullptr, 0 );
}


/* ---- tgKN_OS_Window_Window ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_OS_Window_Window( TgSINT_PTR_C iWindow_Index )
{
    if (!g_asKN_Wnd[iWindow_Index].m_sConfig.m_bFullScreen)
    {
        return;
    };

    g_pfnSetWindowLongPtr( g_asKN_Wnd[iWindow_Index].m_hWnd, GWL_STYLE, g_asKN_Wnd[iWindow_Index].m_sConfig.m_uiWindow_Style );
    g_pfnSetWindowLongPtr( g_asKN_Wnd[iWindow_Index].m_hWnd, GWL_EXSTYLE, g_asKN_Wnd[iWindow_Index].m_sConfig.m_uiWindow_ExStyle );
    g_pfnSetWindowPos( g_asKN_Wnd[iWindow_Index].m_hWnd,
                       HWND_NOTOPMOST,
                       g_asKN_Wnd[iWindow_Index].m_iWindow_Saved_X,
                       g_asKN_Wnd[iWindow_Index].m_iWindow_Saved_Y,
                       g_asKN_Wnd[iWindow_Index].m_iWindow_Saved_W + g_iKN_Window_PadX,
                       g_asKN_Wnd[iWindow_Index].m_iWindow_Saved_H + g_iKN_Window_PadY,
                       SWP_FRAMECHANGED | SWP_NOACTIVATE );

    g_pfnShowWindow(g_asKN_Wnd[iWindow_Index].m_hWnd, SW_NORMAL);
    g_asKN_Wnd[iWindow_Index].m_sConfig.m_bFullScreen = false;
    tgKN_ReCalc_Display( iWindow_Index );
    tgKN_OS_Set_Window_Title_Internal( iWindow_Index, &g_asKN_Wnd[iWindow_Index].m_sConfig, nullptr, 0 );
}


/* ---- tgKN_OS_Base_Window_Update ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgSINT_E64 __stdcall tgKN_OS_Base_Window_Update( HWND hWnd, TgUINT_E32 uMessage, TgUINT_E64 wParam, TgSINT_E64 lParam )
{
    TgSINT_PTR                          iWindow_Index;
    HMONITOR                            hMonitor;
    MONITORINFO                         sMonitor_Info;

    iWindow_Index = g_pfnGetWindowLongPtr( hWnd, GWLP_USERDATA );
    if (iWindow_Index < 0 || iWindow_Index >= KTgKN_MAX_WINDOWS || g_asKN_Wnd[iWindow_Index].m_hWnd != hWnd)
    {
        return (g_pfnDefWindowProc( hWnd, uMessage, wParam, lParam ));
    };

    switch (uMessage)
    {
        case WM_SYSKEYDOWN:
            switch (wParam)
            {
                case VK_F10:
                    tgKN_OS_Window_Window( iWindow_Index );
                    break;
                case VK_F11:
                    tgKN_OS_Window_FullScreen( iWindow_Index );
                    break;
            }
        TgATTRIBUTE_FALLTHROUGH case WM_KEYDOWN:
        TgATTRIBUTE_FALLTHROUGH case WM_KEYUP:
        TgATTRIBUTE_FALLTHROUGH case WM_SYSKEYUP:
            if (g_pfnKN_GUI_Keyboard_Handler)
            {
                g_pfnKN_GUI_Keyboard_Handler( hWnd, uMessage, wParam, lParam );
                //return (1);
            };
            break;

        case WM_MOUSEMOVE:
            /* Update Cursor Position */
            /* Fall through for input update */

        TgATTRIBUTE_FALLTHROUGH case WM_LBUTTONDOWN:
        TgATTRIBUTE_FALLTHROUGH case WM_LBUTTONUP:
        TgATTRIBUTE_FALLTHROUGH case WM_LBUTTONDBLCLK:
        TgATTRIBUTE_FALLTHROUGH case WM_MBUTTONDOWN:
        TgATTRIBUTE_FALLTHROUGH case WM_MBUTTONUP:
        TgATTRIBUTE_FALLTHROUGH case WM_MBUTTONDBLCLK:
        TgATTRIBUTE_FALLTHROUGH case WM_RBUTTONDOWN:
        TgATTRIBUTE_FALLTHROUGH case WM_RBUTTONUP:
        TgATTRIBUTE_FALLTHROUGH case WM_RBUTTONDBLCLK:
        TgATTRIBUTE_FALLTHROUGH case WM_XBUTTONDOWN:
        TgATTRIBUTE_FALLTHROUGH case WM_XBUTTONUP:
        TgATTRIBUTE_FALLTHROUGH case WM_XBUTTONDBLCLK:
        TgATTRIBUTE_FALLTHROUGH case WM_MOUSEWHEEL:
            if (g_pfnKN_GUI_Mouse_Handler)
            {
                g_pfnKN_GUI_Mouse_Handler( hWnd, uMessage, wParam, lParam );
                //return (1);
            };
            break;

        case WM_ERASEBKGND:
            break;

        case WM_SIZE:
            if (SIZE_MINIMIZED == wParam)
            {
                g_asKN_Wnd[iWindow_Index].m_sConfig.m_bMinimized = true;
                g_asKN_Wnd[iWindow_Index].m_sConfig.m_bMaximized = false;
            }
            else
            {
                RECT                                wRect;

                g_pfnGetClientRect( g_asKN_Wnd[iWindow_Index].m_hWnd, &wRect );

                if (0 == wRect.top && 0 == wRect.bottom)
                {
                    /* Empty on Purpose */
                }
                else if (SIZE_MAXIMIZED == wParam)
                {
                    g_asKN_Wnd[iWindow_Index].m_sConfig.m_bMinimized = false;
                    g_asKN_Wnd[iWindow_Index].m_sConfig.m_bMaximized = true;

                    tgKN_ReCalc_Display( iWindow_Index );
                    if (nullptr != g_pfnDevice_Change_Check)
                    {
                        g_pfnDevice_Change_Check( hWnd, &g_asKN_Wnd[iWindow_Index].m_sConfig );
                    };
                }
                else if (SIZE_RESTORED == wParam)
                {
                    if (g_asKN_Wnd[iWindow_Index].m_sConfig.m_bMaximized)
                    {
                        g_asKN_Wnd[iWindow_Index].m_sConfig.m_bMaximized = false;

                        tgKN_ReCalc_Display( iWindow_Index );
                        if (nullptr != g_pfnDevice_Change_Check)
                        {
                            g_pfnDevice_Change_Check( hWnd, &g_asKN_Wnd[iWindow_Index].m_sConfig );
                        };
                    }
                    else if (g_asKN_Wnd[iWindow_Index].m_sConfig.m_bMinimized)
                    {
                        g_asKN_Wnd[iWindow_Index].m_sConfig.m_bMinimized = false;

                        tgKN_ReCalc_Display( iWindow_Index );
                        if (nullptr != g_pfnDevice_Change_Check)
                        {
                            g_pfnDevice_Change_Check( hWnd, &g_asKN_Wnd[iWindow_Index].m_sConfig );
                        };
                    }
                    else if (g_asKN_Wnd[iWindow_Index].m_bIn_Size_Move)
                    {

                    }
                    else
                    {
                        tgKN_ReCalc_Display( iWindow_Index );
                        if (nullptr != g_pfnDevice_Change_Check)
                        {
                            g_pfnDevice_Change_Check( hWnd, &g_asKN_Wnd[iWindow_Index].m_sConfig );
                        };
                    };
                };
            };
            break;

        case WM_MOVING:
        {
            LPRECT                              pRect = (LPRECT)lParam;

            hMonitor = g_pfnMonitorFromWindow( g_asKN_Wnd[iWindow_Index].m_hWnd, MONITOR_DEFAULTTONULL );
            tgKN_ReCalc_Display( iWindow_Index );

            tgKN_OS_Set_Window_Title_Internal( iWindow_Index, &g_asKN_Wnd[iWindow_Index].m_sConfig, nullptr, 0 );

            if (g_pfnQuery_Swap_Context_Closest_Mode_Rounded_Down)
                g_pfnQuery_Swap_Context_Closest_Mode_Rounded_Down( &g_asKN_Wnd[iWindow_Index].m_sConfig.m_uiRender_Target_W,
                                                                   &g_asKN_Wnd[iWindow_Index].m_sConfig.m_uiRender_Target_H,
                                                                   g_asKN_Wnd[iWindow_Index].m_hWnd, hMonitor );

            pRect->right = pRect->left + (LONG)g_asKN_Wnd[iWindow_Index].m_sConfig.m_uiRender_Target_W + g_iKN_Window_PadX;
            pRect->bottom = pRect->top + (LONG)g_asKN_Wnd[iWindow_Index].m_sConfig.m_uiRender_Target_H + g_iKN_Window_PadY;

            g_pfnPostMessage( g_asKN_Wnd[iWindow_Index].m_hWnd, WM_ERASEBKGND, 0, 0 );
        };
        break;

        case WM_SIZING:
            if (g_asKN_Wnd[iWindow_Index].m_sConfig.m_bWindowSize_Fixed && g_pfnQuery_Swap_Context_Closest_Mode_Rounded_Down)
            {
                LPRECT                              pRect = (LPRECT)lParam;
                TgUINT_E32                          iW = (TgUINT_E32)(pRect->right - pRect->left - g_iKN_Window_PadX);
                TgUINT_E32                          iH = (TgUINT_E32)(pRect->bottom - pRect->top - g_iKN_Window_PadY);

                hMonitor = g_pfnMonitorFromWindow( g_asKN_Wnd[iWindow_Index].m_hWnd, MONITOR_DEFAULTTONULL );

                /* The way the selector works is width then height - to hack in some sizing on height only swap it to a width change */
                //if (WMSZ_TOP == wParam || WMSZ_BOTTOM == wParam)
                //{
                //    iW = g_asKN_Wnd[iWindow_Index].m_sConfig.m_iRender_Target_W;
                //    iH = -g_asKN_Wnd[iWindow_Index].m_sConfig.m_iRender_Target_H;
                //};

                g_pfnQuery_Swap_Context_Closest_Mode_Rounded_Down( &iW, &iH, g_asKN_Wnd[iWindow_Index].m_hWnd, hMonitor );

                switch (wParam)
                {
                    case WMSZ_BOTTOMLEFT:
                    case WMSZ_LEFT:
                        pRect->left = pRect->right - (LONG)iW - g_iKN_Window_PadX;
                        pRect->bottom = pRect->top + (LONG)iH + g_iKN_Window_PadY;
                        break;
                    case WMSZ_BOTTOMRIGHT:
                    case WMSZ_BOTTOM:
                    case WMSZ_RIGHT:
                        pRect->right = pRect->left + (LONG)iW + g_iKN_Window_PadX;
                        pRect->bottom = pRect->top + (LONG)iH + g_iKN_Window_PadY;
                        break;
                    case WMSZ_TOPLEFT:
                        pRect->left = pRect->right - (LONG)iW - g_iKN_Window_PadX;
                        pRect->top = pRect->bottom - (LONG)iH - g_iKN_Window_PadY;
                        break;
                    case WMSZ_TOPRIGHT:
                    case WMSZ_TOP:
                        pRect->right = pRect->left + (LONG)iW + g_iKN_Window_PadX;
                        pRect->top = pRect->bottom - (LONG)iH - g_iKN_Window_PadY;
                        break;
                    default:
                        TgS_NO_DEFAULT(break);
                };

                tgKN_OS_Set_Window_Title_Internal( iWindow_Index, &g_asKN_Wnd[iWindow_Index].m_sConfig, nullptr, 0 );
            };
            break;

        case WM_GETMINMAXINFO:
            if (g_asKN_Wnd[iWindow_Index].m_sConfig.m_bWindowSize_Lock)
            {
                TgUINT_E32                          iW = 0, iH = 0;

                if (g_pfnQuery_Swap_Context_Mode_Width_and_Height)
                {
                    hMonitor = g_pfnMonitorFromWindow( g_asKN_Wnd[iWindow_Index].m_hWnd, MONITOR_DEFAULTTONULL );
                    g_pfnQuery_Swap_Context_Mode_Width_and_Height( &iW, &iH, g_asKN_Wnd[iWindow_Index].m_hWnd, hMonitor );
                };

                ((MINMAXINFO*)lParam)->ptMinTrackSize.x = (LONG)iW + g_iKN_Window_PadX;
                ((MINMAXINFO*)lParam)->ptMinTrackSize.y = (LONG)iH + g_iKN_Window_PadY;
                ((MINMAXINFO*)lParam)->ptMaxTrackSize.x = (LONG)iW + g_iKN_Window_PadX;
                ((MINMAXINFO*)lParam)->ptMaxTrackSize.y = (LONG)iH + g_iKN_Window_PadY;
            }
            else if (g_asKN_Wnd[iWindow_Index].m_sConfig.m_bWindowSize_Fixed)
            {
                TgUINT_E32                          iW = 0, iH = 0;

                hMonitor = g_pfnMonitorFromWindow( g_asKN_Wnd[iWindow_Index].m_hWnd, MONITOR_DEFAULTTONULL );

                if (g_pfnQuery_Monitor_Min_Resolution)
                {
                    g_pfnQuery_Monitor_Min_Resolution( &iW, &iH, hMonitor );
                }
                else
                {
                    iW = 320;
                    iH = 200;
                };

                ((MINMAXINFO*)lParam)->ptMinTrackSize.x = (LONG)iW + g_iKN_Window_PadX;
                ((MINMAXINFO*)lParam)->ptMinTrackSize.y = (LONG)iH + g_iKN_Window_PadY;

                if (g_pfnQuery_Monitor_Max_Resolution)
                {
                    g_pfnQuery_Monitor_Max_Resolution( &iW, &iH, hMonitor );
                }
                else
                {
                    iW = 320;
                    iH = 200;
                };

                ((MINMAXINFO*)lParam)->ptMaxTrackSize.x = (LONG)iW + g_iKN_Window_PadX;
                ((MINMAXINFO*)lParam)->ptMaxTrackSize.y = (LONG)iH + g_iKN_Window_PadY;
            };

            break;

        case WM_ENTERSIZEMOVE:
            g_asKN_Wnd[iWindow_Index].m_bIn_Size_Move = true;
            break;

        case WM_EXITSIZEMOVE:
            g_asKN_Wnd[iWindow_Index].m_bIn_Size_Move = false;
            tgKN_ReCalc_Display( iWindow_Index );
            hMonitor = g_pfnMonitorFromWindow( g_asKN_Wnd[iWindow_Index].m_hWnd, MONITOR_DEFAULTTONULL );
            if (nullptr != g_pfnDevice_Change_Check)
            {
                g_pfnDevice_Change_Check( hWnd, &g_asKN_Wnd[iWindow_Index].m_sConfig );
            };

            if (g_pfnGetMonitorInfo && g_pfnGetMonitorInfo( hMonitor, &sMonitor_Info ))
            {
                TgSINT_E32                          iMonitor_W, iMonitor_H;

                iMonitor_W = sMonitor_Info.rcWork.right - sMonitor_Info.rcWork.left;
                iMonitor_H = sMonitor_Info.rcWork.bottom - sMonitor_Info.rcWork.top;
                g_asKN_Wnd[iWindow_Index].m_bLandscape = iMonitor_W >= iMonitor_H;
            };
            tgKN_OS_Set_Window_Title_Internal( iWindow_Index, &g_asKN_Wnd[iWindow_Index].m_sConfig, nullptr, 0 );
            break;

        case WM_ACTIVATEAPP:
            /* #TODO: Handle Activate App message from WinOS */
            if (wParam && !g_asKN_Wnd[iWindow_Index].m_bActive)
            {

            }
            else if (!wParam && g_asKN_Wnd[iWindow_Index].m_bActive)
            {

            };
            break;

        case WM_MOUSEACTIVATE:
            //return MA_ACTIVATE;
            break;

        case WM_POWERBROADCAST:
            switch (wParam)
            {
                case PBT_APMQUERYSUSPEND:
                    return 0x424D5144;
                case PBT_APMRESUMESUSPEND:
                    return (true);
            }
            break;

        case WM_SYSCOMMAND:
            switch (wParam & 0xFFF0)
            {
                case SC_NEXTWINDOW:
                case SC_PREVWINDOW:
                case SC_TASKLIST:
                case SC_HOTKEY:
                case SC_MOVE:
                case SC_SIZE:
                case SC_MAXIMIZE:
                case SC_KEYMENU:
                    if (g_asKN_Wnd[iWindow_Index].m_sConfig.m_bFullScreen)
                    {
                        return (0);
                    };
                    break;

                case SC_SCREENSAVE:
                case SC_MONITORPOWER:
                    return (1);
            };
            break;

        case WM_DISPLAYCHANGE:
            /* #TODO: Handle Display Change message from WinOS */
            break;

        case WM_KILLFOCUS:
            /* #TODO: Handle Kill Focus message from WinOS */
            break;

        case WM_SETFOCUS:
            /* #TODO: Handle Set Focus message from WinOS */
            break;

        case WM_PAINT:
            /* #TODO: Handle Paint message from WinOS */
            break;

        case WM_SETCURSOR:
            // Turn off window cursor.
            g_pfnSetCursor( NULL );
            return (1);

        case WM_DESTROY:
        case WM_CLOSE:
            g_pfnPostMessage( g_asKN_Wnd[iWindow_Index].m_hWnd, WM_QUIT, 0, 0 );
            return (0);

        case WM_SETTINGCHANGE:
        case WM_DEVICECHANGE:
            if (nullptr != g_pfnDevice_Change_Check)
            {
                g_pfnDevice_Change_Check( hWnd, &g_asKN_Wnd[iWindow_Index].m_sConfig );
            };
            break;

        default:
            break;
    }

    return (g_pfnDefWindowProc( hWnd, uMessage, wParam, lParam ));
}


/* ---- tgKN_OS_Set_Window_Title ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_OS_Set_Window_Title( TgSINT_PTR_C iWindow_Index, TgOSCHAR_CPC oszText, TgRSIZE_C nuiText )
{
    tgKN_OS_Set_Window_Title_Internal( iWindow_Index, &g_asKN_Wnd[iWindow_Index].m_sConfig, oszText, nuiText );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

static const GUID FOLDERID_LocalAppData = { 0xF1B32785, 0x6FBA, 0x4FCF, { 0x9D, 0x55, 0x7B, 0x8E, 0x7F, 0x15, 0x70, 0x91 } };


/* ---- tgKN_Path_Query_Application_Data_Folder ---------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_Path_Query_Application_Data_Folder( TgCHAR_U8_P szPath, TgRSIZE_C nuiPath )
{
    PWSTR            pszPath = nullptr;

    g_pfnSHGetKnownFolderPath( &FOLDERID_LocalAppData, 0, NULL, &pszPath );
    tgUSZ_Convert_WSZ( szPath, nuiPath, pszPath, KTgMAX_RSIZE );
    g_pfnCoTaskMemFree( pszPath );
}

/* ---- tgKN_Path_Query_Temporary_Folder ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_Path_Query_Temporary_Folder( TgCHAR_U8_P szPath, TgRSIZE_C nuiPath )
{
    PWSTR            pszPath = nullptr;

    g_pfnSHGetKnownFolderPath( &FOLDERID_LocalAppData, 0, NULL, &pszPath );
    tgUSZ_Convert_WSZ( szPath, nuiPath, pszPath, KTgMAX_RSIZE );
    g_pfnCoTaskMemFree( pszPath );
    tgUSZ_Append( szPath, nuiPath, u8"\\temp", KTgMAX_RSIZE );
}


/* ---- tgKN_ReCalc_Display ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_ReCalc_Display( TgSINT_PTR_C iWindow_Index )
{
    RECT                                sRect;

    /* Get the current window rect */
    g_pfnGetWindowRect( g_asKN_Wnd[iWindow_Index].m_hWnd, &sRect );
    g_asKN_Wnd[iWindow_Index].m_sConfig.m_iWindow_X0 = sRect.left;
    g_asKN_Wnd[iWindow_Index].m_sConfig.m_iWindow_Y0 = sRect.top;

    /* Get the current display (client) rect */
    g_pfnGetClientRect( g_asKN_Wnd[iWindow_Index].m_hWnd, &sRect );
    g_asKN_Wnd[iWindow_Index].m_sConfig.m_uiRender_Target_W = (TgUINT_E32)(sRect.right - sRect.left);
    g_asKN_Wnd[iWindow_Index].m_sConfig.m_uiRender_Target_H = (TgUINT_E32)(sRect.bottom - sRect.top);
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_OS_Set_Window_Title_Internal ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgKN_OS_Set_Window_Title_Internal( TgSINT_PTR_C iWindow_Index, STg2_KN_OS_Window_Configuration_CPC psConfig, TgOSCHAR_CPC oszText, TgRSIZE_C nuiText )
{
    TgRSIZE                             nuiBuffer = sizeof(g_asKN_Wnd[iWindow_Index].m_sConfig.m_szTitle);
    TgOSCHAR                            szUINT[16];
    RECT                                wRect;
    TgSINT_E32                          iW, iH;

    TgPARAM_CHECK(nullptr != psConfig);

    if (psConfig->m_bTitle_Include_Default)
    {
        TgOS_TEXT_FCN( Copy )( g_asKN_Wnd[iWindow_Index].m_sConfig.m_szTitle, nuiBuffer, g_asKN_Wnd[iWindow_Index].m_sConfig.m_szDefault_Title, KTgMAX_RSIZE );
    }

    if (psConfig->m_bTitle_Include_Dimensions)
    {
        g_pfnGetClientRect( g_asKN_Wnd[iWindow_Index].m_hWnd, &wRect );

        iW = wRect.right - wRect.left;
        iH = wRect.bottom - wRect.top;

        TgOS_TEXT_FCN(Append)( g_asKN_Wnd[iWindow_Index].m_sConfig.m_szTitle, nuiBuffer, TgOS_TEXT( " [" ), KTgMAX_RSIZE );
        TgOS_TEXT_FCN(From_S32)( szUINT, sizeof(szUINT), iW );
        TgOS_TEXT_FCN(Append)( g_asKN_Wnd[iWindow_Index].m_sConfig.m_szTitle, nuiBuffer, szUINT, KTgMAX_RSIZE );
        TgOS_TEXT_FCN(Append)( g_asKN_Wnd[iWindow_Index].m_sConfig.m_szTitle, nuiBuffer, TgOS_TEXT( " x " ), KTgMAX_RSIZE );
        TgOS_TEXT_FCN(From_S32)( szUINT, sizeof(szUINT), iH );
        TgOS_TEXT_FCN(Append)( g_asKN_Wnd[iWindow_Index].m_sConfig.m_szTitle, nuiBuffer, szUINT, KTgMAX_RSIZE );
        TgOS_TEXT_FCN(Append)( g_asKN_Wnd[iWindow_Index].m_sConfig.m_szTitle, nuiBuffer, TgOS_TEXT( "]" ), KTgMAX_RSIZE );
    }

    if (nullptr != oszText && 0 != nuiText)
    {
        TgOS_TEXT_FCN(Append)( g_asKN_Wnd[iWindow_Index].m_sConfig.m_szTitle, nuiBuffer, oszText, nuiText );
    }

    g_pfnSetWindowText( g_asKN_Wnd[iWindow_Index].m_hWnd, g_asKN_Wnd[iWindow_Index].m_sConfig.m_szTitle );
}


/* ---- tgKN_OS_Create_Window_Thread --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgUINT_E32 tgKN_OS_Create_Window_Thread( TgUINT_PTR_C uiParam ) TgATTRIBUTE_NO_EXCEPT
{
    TgSINT_PTR_C                        iWindow_Index = (TgSINT_PTR)uiParam;

    union
    {
        STg2_KN_OS_HWND_P                   ps;
        STg2_UT_ST__ST_Node_P               pNode;
    }                                   sHWND;
    WNDCLASSEX                          wc;
    MSG                                 msg;

    TgPARAM_CHECK_INDEX( iWindow_Index, g_asKN_Wnd );

    tgMM_Set_U08_0x00( &wc, sizeof( WNDCLASSEX ) );

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = g_asKN_Wnd[iWindow_Index].m_sConfig.m_pfnWndProc;
    wc.hInstance = g_hInstance;
    wc.lpszClassName = g_asKN_Wnd[iWindow_Index].m_sConfig.m_szClass_Name;

    if (0 == g_pfnRegisterClassEx( &wc ))
    {
        const DWORD dwError = g_pfnGetLastError();
        if (dwError != 1410L)
        {
            goto tgKN_OS_Update_Window_FAIL_0;
        };
    };

    /* Create an instance of the window we just registered locate it at the bottom of the screen. */
    g_asKN_Wnd[iWindow_Index].m_hWnd = g_pfnCreateWindowEx(
        g_asKN_Wnd[iWindow_Index].m_sConfig.m_uiWindow_ExStyle,
        g_asKN_Wnd[iWindow_Index].m_sConfig.m_szClass_Name,
        g_asKN_Wnd[iWindow_Index].m_sConfig.m_szTitle,
        g_asKN_Wnd[iWindow_Index].m_sConfig.m_uiWindow_Style,
        g_asKN_Wnd[iWindow_Index].m_sConfig.m_iWindow_X0,
        g_asKN_Wnd[iWindow_Index].m_sConfig.m_iWindow_Y0,
        (LONG)g_asKN_Wnd[iWindow_Index].m_sConfig.m_uiRender_Target_W + g_iKN_Window_PadX,
        (LONG)g_asKN_Wnd[iWindow_Index].m_sConfig.m_uiRender_Target_H + g_iKN_Window_PadY,
        0,
        0,
        g_hInstance,
        0
    );

    if (!g_asKN_Wnd[iWindow_Index].m_hWnd)
    {
        g_pfnUnregisterClass( wc.lpszClassName, g_hInstance );
        goto tgKN_OS_Update_Window_FAIL_0;
    };

    g_pfnSetWindowLongPtr( g_asKN_Wnd[iWindow_Index].m_hWnd, GWLP_USERDATA, (TgSINT_PTR)iWindow_Index );
    tgPM_MT_SM_Signal( &g_sKN_Window_Creation_Lock, 1 );
    tgPM_MT_SM_Signal( &g_sKN_Window_Instance_Search_Lock, 1 );

    /* The original call to the window creation will now be free to continue execution. */

    g_pfnShowWindow( g_asKN_Wnd[iWindow_Index].m_hWnd, 10 );
    g_pfnUpdateWindow( g_asKN_Wnd[iWindow_Index].m_hWnd );

    tgKN_ReCalc_Display( iWindow_Index );
    tgKN_OS_Set_Window_Title_Internal( iWindow_Index, &g_asKN_Wnd[iWindow_Index].m_sConfig, nullptr, 0 );

    TgSTD_ATOMIC(fetch_add)( &g_xuiKN_Wnd_Served, 1 );

    while (!g_bKN_Close_Windows)
    {
        while (0 != g_pfnPeekMessage( &msg, g_asKN_Wnd[iWindow_Index].m_hWnd, 0U, 0U, 0x0001 ) && WM_QUIT != msg.message)
        {
            g_pfnTranslateMessage( &msg );
            g_pfnDispatchMessage( &msg );
        };

        if (WM_QUIT == msg.message) break;

        if (0 != g_asKN_Wnd[iWindow_Index].m_oszUpdate_Title[0])
        {
            tgKN_OS_Set_Window_Title_Internal( iWindow_Index, &g_asKN_Wnd[iWindow_Index].m_sConfig, g_asKN_Wnd[iWindow_Index].m_oszUpdate_Title,
                                               sizeof(g_asKN_Wnd[iWindow_Index].m_oszUpdate_Title) );
            g_asKN_Wnd[iWindow_Index].m_oszUpdate_Title[0] = 0;
        };
        tgTR_Sleep( 15000 );
    };

    g_pfnUnregisterClass( wc.lpszClassName, g_hInstance );

    sHWND.ps = g_asKN_Wnd + iWindow_Index;
    tgCM_UT_LF__ST__Push( &g_sKN_GPU_OS_HWND__Term_Stack.m_sStack, sHWND.pNode );
    return (0);

tgKN_OS_Update_Window_FAIL_0:
    tgPM_MT_SM_Signal( &g_sKN_Window_Creation_Lock, 1 );
    tgPM_MT_SM_Signal( &g_sKN_Window_Instance_Search_Lock, 1 );
    TgSTD_ATOMIC(fetch_add)( &g_xuiKN_Wnd_Served, 1 );
    sHWND.ps = g_asKN_Wnd + iWindow_Index;
    tgCM_UT_LF__ST__Push( &g_sKN_GPU_OS_HWND__Term_Stack.m_sStack, sHWND.pNode );
    return (1);
}
