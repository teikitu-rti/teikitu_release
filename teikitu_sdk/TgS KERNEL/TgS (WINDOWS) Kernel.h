/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (WINDOWS) Kernel.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
#if !defined(TGS_WINDOWS_KERNEL_H)
#define TGS_WINDOWS_KERNEL_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "TgS (WINDOWS) Kernel - Constants.h"
#include "TgS (WINDOWS) Kernel - Type.h"

#include "TgS Kernel [GPU] - Constants.h"
#include "TgS Kernel [GPU] - Type.h"


/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Kernel Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- Configuration ------------------------------------------------------------------------------------------------------------------------------------------------------------ */

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
    TgOSCHAR_CPC TgANALYSIS_NO_NULL ARG0 );

/** @brief Sets the default title text to be used when creating the window. Routines automatically add a numeric suffic to allow for multiple windows.
    @param [in] ARG0 Pointer to a string. */
TgEXTN TgVOID
tgKN_OS_Set_Default_Window_Title(
    TgOSCHAR_CPC TgANALYSIS_NO_NULL ARG0 );

/** @brief Sets the default windows messaging procedure to be used when a window is created. The internal default is used if set to null.
    @param [in] ARG0 Pointer to the function, or null to clear it. */
TgEXTN TgVOID
tgKN_OS_Set_Default_WndProc(
    WNDPROC TgANALYSIS_NO_NULL ARG0 );

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

TgEXTN TgSINT_E32
tgKN_Query_Window_PadX( TgVOID );

TgEXTN TgSINT_E32
tgKN_Query_Window_PadY( TgVOID );


/* ---- OS Functions ------------------------------------------------------------------------------------------------------------------------------------------------------------- */

/** @brief Create a new operating system window for the application.
    @param [in] ARG0 Pointer to the configuration structure to use for creating the window.
    @return Integer index of the window used to identify it, and a negative value otherwise. */
TgEXTN TgSINT_PTR
tgKN_OS_Create_Window(
    STg2_KN_OS_Window_Configuration_CPC TgANALYSIS_NO_NULL ARG0
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
    STg2_KN_OS_Window_Configuration_PC TgANALYSIS_NO_NULL OUT0, TgSINT_PTR_C ARG1 );

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
    @param [in] ARG1 Pointer to an OS Text string buffer.
    @param [in] ARG2 Integer count of the maximum size of the buffer at ARG1. */
TgEXTN TgVOID
tgKN_OS_Set_Window_Title(
    TgSINT_PTR_C ARG0, TgOSCHAR_CPC ARG1, TgRSIZE_C ARG2 );

/** @brief Return the whitepoint used for SDR content on HDR monitors.
    @return Result Code. */
TgEXTN TgRESULT
tgKN_OS_Query_Monitor_Whitepoint( TgVOID );


/* ---- DXGI GPU Functions ------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if defined(TgBUILD_FEATURE__GRAPHICS)

/** @brief Validate that a selected format is supported on an output and physical device.
    @param [in] ARG0 Integer index selecting the physical device.
    @param [in] ARG1 Enumeration selecting the format.
    @return True when the format is supported on the selected output and physical device, false otherwise. */
TgEXTN TgBOOL
tgKN_OS_GPU_Test_Output_ScanOut_Format_Support(
    TgRSIZE_C ARG0, ETgKN_GPU_EXT_FORMAT_C ARG1 );

/** @brief Return a list of modes that are supported by the physical device and output device.
    @param [out] OUT0 Pointer of an array of strings that will contain the modes for the selected output device, physical device and target format.
    @param [in] ARG1 Integer count of the number of mode strings that can be assigned into OUT0.
    @param [in] ARG2 Integer index selecting the output.
    @param [in] ARG3 Enumeration selecting the format.
    @return Integer count of the number of modes assigned into the array. */
TgEXTN TgRSIZE
tgKN_OS_GPU_Query_Mode_List(
    STg2_KN_OS_GPU_Mode_P TgANALYSIS_OK_NULL OUT0, TgRSIZE_C ARG1, TgRSIZE_C ARG2, ETgKN_OS_GPU_FORMAT_C ARG3 );

/** @brief Query the minimum resolution of a monitor
    @param [out] OUT0 Pointer to the minimum width of the monitor
    @param [out] OUT1 Pointer to the minimum height of the monitor
    @param [in] ARG2 Monitor handle */
TgEXTN TgVOID
tgKN_OS_GPU_Query_Monitor_Min_Resolution(
    TgUINT_E32_P OUT0, TgUINT_E32_P OUT1, HMONITOR ARG2 );

/** @brief Query the maximum resolution of a monitor
    @param [out] OUT0 Pointer to the maximum width of the monitor
    @param [out] OUT1 Pointer to the maximum height of the monitor
    @param [in] ARG2 Monitor handle */
TgEXTN TgVOID
tgKN_OS_GPU_Query_Monitor_Max_Resolution(
    TgUINT_E32_P OUT0, TgUINT_E32_P OUT1, HMONITOR ARG2 );

/** @brief Find the closest mode (rounded down) that was enumerated for the selected output device.
    @param [out] OUT0 Pointer to the closest (rounded down) valid mode found to the requested mode.
    @param [in] ARG1 Pointer to the requested mode.
    @param [in] ARG2 Monitor handle.
    @return Result Code. */
TgEXTN TgRESULT
tgKN_OS_GPU_Select_Min_Mode(
    STg2_KN_OS_GPU_Mode_PC TgANALYSIS_NO_NULL OUT0, STg2_KN_OS_GPU_Mode_CPC TgANALYSIS_NO_NULL ARG1, HMONITOR ARG2 );
    
/** @brief Find the closest mode (rounded up) that was enumerated for the selected output device.
    @param [out] OUT0 Pointer to the closest (rounded up) valid mode found to the requested mode.
    @param [in] ARG1 Pointer to the requested mode.
    @param [in] ARG2 Monitor handle.
    @return Result Code. */
TgEXTN TgRESULT
tgKN_OS_GPU_Select_Max_Mode(
    STg2_KN_OS_GPU_Mode_PC TgANALYSIS_NO_NULL OUT0, STg2_KN_OS_GPU_Mode_CPC TgANALYSIS_NO_NULL ARG1, HMONITOR ARG2 );

/** @brief Query the current mode of the swap chain.
    @param [out] OUT0 Pointer to the current width of the swap chain.
    @param [out] OUT1 Pointer to the current height of the swap chain.
    @param [in] ARG2 Handle to the window. */
TgEXTN TgVOID
tgKN_OS_GPU_CXT_SWAP_Query_Mode(
    TgUINT_E32_P OUT0, TgUINT_E32_P OUT1, HWND ARG2 );

/** @brief Query the current mode of the swap chain, rounded down to the nearest valid mode.
    @param [out] OUT0 Pointer to the current width of the swap chain rounded down to the nearest valid mode.
    @param [out] OUT1 Pointer to the current height of the swap chain rounded down to the nearest valid mode.
    @param [in] ARG2 Handle to the window. */
TgEXTN TgVOID
tgKN_OS_GPU_CXT_SWAP_Query_Mode_Rounded_Down(
    TgUINT_E32_P OUT0, TgUINT_E32_P OUT1, HWND ARG2 );

/*# defined(TgBUILD_FEATURE__GRAPHICS) */
#endif


/* ---- Unit Test Functions ------------------------------------------------------------------------------------------------------------------------------------------------------ */

/** @brief Return the whitepoint used for SDR content on HDR monitors.
    @param [out] ARG0 Pointer to an array of data structures to fill.
    @param [in] ARG1 Integer count of the number of elements in the array.
    @param [in] ARG2 Boolean flag to indicate window setup
    @return the number of windows created. */
TgEXTN TgRSIZE
tgKN_OS_UNIT_TEST__UTIL__Init_Windows(
    STg2_KN_OS_UNIT_TEST__UTIL__Window_PC ARG0, TgRSIZE_C ARG1, TgBOOL_C ARG2 );


/* =============================================================================================================================================================================== */
#endif
