/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (WINDOWS) Common - Base - Defines.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.21 | »GUID« AEEC8393-9780-4ECA-918D-E3E11F7E2744 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_WINDOWS_COMMON_BASE_DEFINES_OS_H)
#define TGS_WINDOWS_COMMON_BASE_DEFINES_OS_H
#pragma once


/* == Common ===================================================================================================================================================================== */
/* MARK: No Unit Test Required                                                                                                                                                     */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Configuration                                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#define TgCOMPILE__SYSTEM_INFORMATION       0

#define TgPLATFORM__BARE_PATH_SEPARATOR     \\

#define TgPLATFORM__NC_PATH_SEPARATOR       '\\'
#define TgPLATFORM__NC_FILE_SEPARATOR       '.'

#define TgPLATFORM__U8_PATH_SEPARATOR       u8"\\"
#define TgPLATFORM__U8_FILE_SEPARATOR       u8"."

#define _WIN32_WINNT                        0x0A000007
#define WINVER                              0x0A000007

#if defined(TgCOMPILE__CONSOLE_IDE_DEBUG_OUTPUT) && defined(TgIDE__MSVC) && defined(TgBUILD_OS__WINDOWS)
#define TgCOMPILE__CONSOLE_IDE_DEBUG_OUTPUT_SUPPORTED
#endif


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Code Macros                                                                                                                                                                    */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#if defined(TgBUILD_TARGET__WINDOWS_CONSOLE)
    #define TgMAIN_FUNCTION                     int CDECL main(TgATTRIBUTE_UNUSED int argc, TgATTRIBUTE_UNUSED char *argv[], TgATTRIBUTE_UNUSED char *envp[])
    #define TgMAIN_PLATFORM_GLOBAL_INIT         
    #define TgMAIN_PLATFORM_GLOBAL_FREE         
#else
    #if defined(TgCOMPILE_OS_TEXT__WIDE)
        #define TgMAIN_FUNCTION                     int STDCALL wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR lpCmdLine, int nCmdShow )
    #else
        #define TgMAIN_FUNCTION                     int STDCALL WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, char* lpCmdLine, int nCmdShow )
    #endif
    #define TgMAIN_PLATFORM_GLOBAL_INIT         (void)hPrevInstance; (void)lpCmdLine; (void)nCmdShow; g_hInstance = hInstance
    #define TgMAIN_PLATFORM_GLOBAL_FREE         g_hInstance = 0
#endif

#if defined(TgCOMPILE_ALL__CXX) || defined(TgCOMPILE_FILE__CXX)
#define MS_REF
#else
#define MS_REF &
#endif


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Validation                                                                                                                                                                     */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#define WINAPI_FAMILY WINAPI_FAMILY_DESKTOP_APP
#define _CRT_RAND_S

#if defined(TgCOMPILE_OS_TEXT__WIDE) && !defined(UNICODE)
#error Character Set does not match compilation configuration
#endif

#if defined(UNICODE) && !defined(TgCOMPILE_OS_TEXT__WIDE)
#error Character Set does not match compilation configuration
#endif

#if defined(TgBUILD_UNIVERSAL__UWP) && (!defined(UNICODE) || !defined(TgCOMPILE_OS_TEXT__WIDE))
#error UWP Platform must compile under Unicode / Wide Character
#endif


/* =============================================================================================================================================================================== */
#endif
