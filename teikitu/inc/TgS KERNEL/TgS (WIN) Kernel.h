/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (WIN) Kernel.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
#if !defined(TGS_WIN_KERNEL_H)
#define TGS_WIN_KERNEL_H
#pragma once

#include "TgS (WIN) Kernel - Constants.h"
#include "TgS (WIN) Kernel - Type.h"


/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Kernel Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* Configuration */

/** @brief Function to set the callback into the input module based on input received through the windows messaging. This is specifically useful for IME. 
    @param [in] ARG0 Pointer to the function, or null to clear it. */
TgEXTN TgVOID
tgKN_OS_Set_GUI_Keyboard_Callback(
    WNDPROC ARG0 );

/** @brief Function to set the callback into the input module based on input received through the windows messaging. This is specifically useful to allow the mouse driver to
           perform acceleration and other smoothing operations.
    @param [in] ARG0 Pointer to the function to be called, or null to clear it. */
TgEXTN TgVOID
tgKN_OS_Set_GUI_Mouse_Callback(
    WNDPROC ARG0 );

/** @brief Sets the default name to be used when creating the window class (wndclass). Routines automatically add a numeric suffic to allow for multiple windows.
    @param [in] ARG0 Pointer to a string. */
TgEXTN TgVOID
tgKN_OS_Set_Default_Class_Name(
    TgOSCHAR_CPC NONULL ARG0 );

/** @brief Sets the default title text to be used when creating the window. Routines automatically add a numeric suffic to allow for multiple windows.
    @param [in] ARG0 Pointer to a string. */
TgEXTN TgVOID
tgKN_OS_Set_Default_Window_Title(
    TgOSCHAR_CPC NONULL ARG0 );

/** @brief Sets the default windows messaging procedure to be used when a window is created. The internal default is used if set to null.
    @param [in] ARG0 Pointer to the function, or null to clear it. */
TgEXTN TgVOID
tgKN_OS_Set_Default_WndProc(
    WNDPROC NONULL ARG0 );

/** @brief Return the default base window class name used for future window creation.
    @return Pointer to a string containing the base default window title. */
TgEXTN TgOSCHAR_CPC
tgKN_OS_Query_Default_Class_Name( TgVOID );

/** @brief Return the default base window title used for future window creation.
    @return Pointer to a string containing the base default window title. */
TgEXTN TgOSCHAR_CPC
tgKN_OS_Query_Default_Window_Title( TgVOID );

/** @brief Return the default window messaging processing function used for future window creation.
    @return Pointer to a function that is the default window messaging processing function used for future window creation. */
TgEXTN WNDPROC
tgKN_OS_Query_Default_WndProc( TgVOID );

TgEXTN TgSINT_F32
tgKN_Query_Window_PadX( TgVOID );

TgEXTN TgSINT_F32
tgKN_Query_Window_PadY( TgVOID );



/* OS Functions */

/** @brief Create a new operating system window for the application.
    @param [in] ARG0 Pointer to the configuration structure to use for creating the window.
    @return Integer index of the window used to indentify it, and a negative value otherwise. */
TgEXTN TgSINT_E32
tgKN_OS_Create_Window(
    STg2_KN_OS_Window_Configuration_CPC NONULL ARG0
);

/** @brief Return the Windows OS handle for the windows at the given index (or null otherwise).
    @param [in] ARG0 Integer index in this module for selected window.
    @return The Windows OS handle for the windows at the given index (or null otherwise). */
TgEXTN HWND
tgKN_OS_Query_Window_Handle(
    TgSINT_PTR_C ARG0 );

/** @brief Return the status of the thread used to process Windows OS messages.
    @param [in] ARG0 Integer index in this module for selected window.
    @return The status of the thread used to process Windows OS messages. */
TgEXTN ETgTHREAD_STATUS
tgKN_OS_Query_Window_Thread_Status(
    TgSINT_PTR_C ARG0 );

/** @brief Retrieve a copy of the current configuration of the selected window.
    @param [out] OUT0 Pointer to a configuration structure to be filled. This is reflective of the current configuration (not the values at creation).
    @param [in] ARG1 Integer index in this module for selected window. */
TgEXTN TgVOID
tgKN_OS_Query_Window_Configuration(
    STg2_KN_OS_Window_Configuration_PC NONULL OUT0, TgSINT_PTR_C ARG1 );

/** @brief Place the indicated window into fullscreen mode.
    @param [in] ARG0 Integer index in this module for selected window. */
TgEXTN TgVOID
tgKN_OS_Window_FullScreen(
    TgSINT_PTR_C ARG0 );

/** @brief Place the indicated window into window mode.
    @param [in] ARG0 Integer index in this module for selected window. */
TgEXTN TgVOID
tgKN_OS_Window_Window(
    TgSINT_PTR_C ARG0 );

/** @brief Gaming system default windows procedure handler. If you use a different handler, it would be beneficial to call this one at the end of your routine. */
TgEXTN TgSINT_PTR __stdcall
tgKN_OS_Base_Window_Update(
    HWND ARG0, TgUINT_E32 ARG1, TgUINT_PTR ARG2, TgSINT_PTR ARG3 );

/** @brief Set the caption (title) of the window
    @param [in] ARG0 Integer index in this module for selected window.
    @param [in] ARG1 Boolean flag that when true will automatically prefix the provided text with the default title.
    @param [in] ARG2 Boolean flag that when true will automatically prefix the provided text with the client (render buffer) dimensions.
    @param [in] ARG3 Pointer to an OS Text string buffer.
    @param [in] ARG4 Integer count of the maximum size of the buffer at ARG2. */
TgEXTN TgVOID
tgKN_OS_Set_Window_Title(
    TgSINT_PTR_C ARG0, TgBOOL_C ARG1, TgBOOL_C ARG2, TgOSCHAR_CPC ARG3, TgRSIZE_C ARG4 );

/** @brief Return the whitepoint used for SDR content on HDR monitors.
    @return Result Code. */
TgEXTN TgRESULT
tgKN_OS_Query_Monitor_Whitepoint( TgVOID );


/* =============================================================================================================================================================================== */
#endif
