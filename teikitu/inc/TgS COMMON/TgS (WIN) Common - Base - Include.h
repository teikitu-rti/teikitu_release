/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (WIN) Common - Base - Include.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_WIN_COMMON_BASE_INCLUDE_H)
#define TGS_WIN_COMMON_BASE_INCLUDE_H
#pragma once

#define TgCOMPILE_PLATFORM_INCLUDE_MSFT_WINDOWS_HEADERS
#define WINAPI_FAMILY WINAPI_FAMILY_DESKTOP_APP
#define _CRT_RAND_S
#define WIN32_LEAN_AND_MEAN
#define MICROSOFT_WINDOWS_WINBASE_H_DEFINE_INTERLOCKED_CPLUSPLUS_OVERLOADS 0

#if defined(_M_AMD64)
#define _AMD64_
#define __X64__
#elif defined(_M_IX86)
#define _X86_
#define __X86__
#else
#error Unknown platform
#endif

#if !defined(_WIN32) && !defined(_WIN64)
#error Unsupported Windows Configuration
#endif


#define WINAPI_FAMILY WINAPI_FAMILY_DESKTOP_APP
#define _CRT_RAND_S
#define CINTERFACE
#define COBJMACROS
#define INITGUID
#define COM_NO_WINDOWS_H
#define RPC_NO_WINDOWS_H


CLANG_WARN_DISABLE_PUSH(nonportable-system-include-path)
MSVC_PRAGMA(warning(push, 0))
MSVC_PRAGMA(warning(disable: 4820 4668 5039))
#include <winapifamily.h>
#include <sdkddkver.h>
#include <windef.h>
#include <winbase.h>
#include <winuser.h>
MSVC_PRAGMA(warning(pop))
CLANG_WARN_DISABLE_POP(nonportable-system-include-path)

#if defined(_INC_WINDOWS)
#error windows.h has been found in the include chain
#endif

#undef CDECL
#define CDECL TgCDECL
#undef OUT


/* =============================================================================================================================================================================== */
#endif

