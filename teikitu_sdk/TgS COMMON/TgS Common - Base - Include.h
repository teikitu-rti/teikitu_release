/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Base - Include.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_BASE_INCLUDE_H)
#define TGS_COMMON_BASE_INCLUDE_H
#pragma once

#include TgHEADER_HARDWARE(TgS COMMON/TgS,Common - Base - Include.h)


/* == Common ===================================================================================================================================================================== */
/* MARK: No Unit Test Required                                                                                                                                                     */

#if !defined(TgCOMPILE__NO_SYSTEM_HEADERS) || defined(TgCOMPILE__DOXYGEN_BUILD)

TgMSVC_PRAGMA(warning( push, 3 ))
TgMSVC_WARN_DISABLE_PUSH(4117)
TgCLANG_WARN_DISABLE_PUSH(everything)

#define _STD_ATOMIC_ALWAYS_USE_CMPXCHG16B 1
#define _CRT_DECLARE_NONSTDC_NAMES 0
#define _CRT_SECURE_NO_WARNINGS

#define __STDC_WANT_LIB_EXT1__      1
#define __STDC_WANT_SECURE_LIB__    1
#define _XOPEN_SOURCE 700
#define _DEFAULT_SOURCE
#define _ISOC11_SOURCE

#if defined(TgBUILD_COMPILER_FRONTEND__APPLE) && !defined(__GNUC__)
#define __GNUC__ 4
#endif


#if defined(TgCOMPILE_FILE__CXX)
#include <cstdint>                  /* intXX_t, int_leastXX_t, INT_C, MIN, MAX */
#include <cstddef>                  /* ptrdiff_t, size_t, rsize_t, wchar_t */
#include <cstdarg>                  /* va_XXX - variable argument support */
#include <cfloat>                   /* [FLT,DBL,LDBL] MIN, MAX, DIG, EPSILON - Floating point constants */
#include <cuchar>
#include <atomic>

#define NULL 0
#undef NAN                          /* corecrt_math.h */

#else
#include <stdint.h>                 /* intXX_t, int_leastXX_t, INT_C, MIN, MAX */
#include <stddef.h>                 /* ptrdiff_t, size_t, rsize_t, wchar_t */
#include <stdbool.h>                /* true, false */
#include <stdarg.h>                 /* va_XXX - variable argument support */
#include <float.h>                  /* [FLT,DBL,LDBL] MIN, MAX, DIG, EPSILON - Floating point constants */
#include <stdatomic.h>              /* TgSTD_ATOMIC(XXX) - C11 atomic type and functions */
#undef NULL                         /* stddef.h */
#endif

#if defined(TgBUILD_OS__WINDOWS)
#include <malloc.h>                 /* alloca */
#endif

#include <limits.h>

TgCLANG_WARN_DISABLE_POP(everything)
TgMSVC_WARN_DISABLE_POP(4117)
TgMSVC_PRAGMA(warning(pop))

#if !defined(TgCOMPILE_FILE__CXX)
    #define nullptr 0
#endif

// #if defined(NULL)
//    #error NULL is still defined
// #endif

#if defined(NAN)
    #undef NAN
#endif

/*# !defined(TgCOMPILE__NO_SYSTEM_HEADERS) || defined(TgCOMPILE__DOXYGEN_BUILD) */
#endif


/* =============================================================================================================================================================================== */
#endif
