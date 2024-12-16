/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (WIN) Kernel - Type.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
#if !defined(TGS_WIN_KERNEL_TYPE_H)
#define TGS_WIN_KERNEL_TYPE_H
#pragma once

#if !defined(TGS_KERNEL_H)
#error Base Kernel include chain should be prior to this file.
#endif


/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Types                                                                                                                                                                   */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgTYPE_STRUCT(STg2_KN_OS_Window_Configuration,)
{
    TgUINT_F32                                  m_uiRender_Target_W; /**< Assumed to be 1:1 for window, and thus equal to the client rect */
    TgUINT_F32                                  m_uiRender_Target_H; /**< Assumed to be 1:1 for window, and thus equal to the client rect */

    TgSINT_F32                                  m_iWindow_X0; /**< Left coordinate of the window, ignored if KTgMIN_S32. */
    TgSINT_F32                                  m_iWindow_Y0; /**< Top coordinate of the window, ignored if KTgMIN_S32. */

    TgOSCHAR                                    m_szDefault_Title[KTgKN_MAX_TITLE]; /**< The base used for the MSFT Window window title. */
    TgOSCHAR                                    m_szTitle[KTgKN_MAX_TITLE]; /**< The MSFT Windows window title to use when creating the window (default is used if empty). */
    TgOSCHAR                                    m_szClass_Name[KTgKN_MAX_TITLE]; /**< The MSFT Windows class name to use when creating the window (default is used if empty). */
    WNDPROC                                     m_pfnWndProc; /* The window message handling function to use, otherwise the default will be used.*/
    DWORD                                       m_uiWindow_Style; /**< The MSFT window style bitfield to use when creating the window. */
    DWORD                                       m_uiWindow_ExStyle; /**< The MSFT window style bitfield to use when creating the window. */

    TgSINT_E32                                  m_iMonitor; /**< MSFT Windows monitor index for where to place the window. Position values are ignored if greater than zero. */

    TgUINT_E32                                  m_bMinimized : 1; /**< Start the window in a minimized state. */
    TgUINT_E32                                  m_bMaximized : 1; /**< Start the window in a maximized state. */
    TgUINT_E32                                  m_bFullScreen : 1;  /**< Start the window in fullscreen mode. */
    TgUINT_E32                                  m_bFullScreen_Lock : 1; /**< True if the user is prevented from changing the full screen state, and false otherwise. */
    TgUINT_E32                                  m_bWindowSize_Fixed : 1; /**< True if window resizing should be done in fixed increments (matching render target resolution). */
    TgUINT_E32                                  m_bWindowSize_Lock : 1; /**< True if the user is prevented from resizing the window, and false otherwise. */
    TgUINT_E32                                  m_bMuteInBackground : 1; /**< True if audio is of when the application is not in the foreground, and false otherwise. */
    TgUINT_E32                                  m_bRunInBackground : 1; /**< True if the application continues to run when not in the foreground, and false otherwise. */
    TgUINT_E32                                  m_bHasGDIMenu : 1; /**< True if the window has a windows based menu, and false otherwise. */
    TgUINT_E32                                  m_bClearDisplay : 1; /**< True if the window should be cleared every frame, and false otherwise.*/
    TgUINT_E32                                  m_bPauseOnSize : 1; /**< True if the application is paused when being resized, and false otherwise. */
    TgUINT_E32                                  m_bCenterOnMonitor : 1; /**< True if the application is starts in the middle of the monitor, and false otherwise. */
    TgUINT_E32                                  m_bIncludeDefaultInTitle : 1; /**< True when the default title is included when rebuilding the window title. */
    TgUINT_E32                                  m_bIncludeDimensionsInTitle : 1; /**< True when the window dimensions are included when rebuilding the window title. */
};


/* =============================================================================================================================================================================== */
#endif
