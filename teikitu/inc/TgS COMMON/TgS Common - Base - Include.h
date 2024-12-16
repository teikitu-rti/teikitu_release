/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Base - Include.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
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

MSVC_PRAGMA(warning( push, 3 ))
MSVC_WARN_DISABLE_PUSH(4117)
CLANG_WARN_DISABLE_PUSH(everything)

#define _STD_ATOMIC_ALWAYS_USE_CMPXCHG16B 1
#define _CRT_DECLARE_NONSTDC_NAMES 0
#define _CRT_SECURE_NO_WARNINGS

#define __STDC_WANT_LIB_EXT1__      1
#define __STDC_WANT_SECURE_LIB__    1
#define __DARWIN_C_LEVEL            __DARWIN_C_FULL

#if defined(TgCOMPILE_FILE__CXX)
#include <cstdint>                  /* intXX_t, int_leastXX_t, INT_C, MIN, MAX */
#include <cstddef>                  /* ptrdiff_t, size_t, rsize_t, wchar_t */
#include <cstdarg>                  /* va_XXX - variable argument support */
#include <cfloat>                   /* [FLT,DBL,LDBL] MIN, MAX, DIG, EPSILON - Floating point constants */
#include "atomic.c++"               /* atomic_XXX - C11 atomic type and functions */

#undef NAN                          /* corecrt_math.h */
#else
#include <stdint.h>                 /* intXX_t, int_leastXX_t, INT_C, MIN, MAX */
#include <stddef.h>                 /* ptrdiff_t, size_t, rsize_t, wchar_t */
#include <stdbool.h>                /* true, false */
#include <stdarg.h>                 /* va_XXX - variable argument support */
#include <float.h>                  /* [FLT,DBL,LDBL] MIN, MAX, DIG, EPSILON - Floating point constants */
#include <stdatomic.h>              /* atomic_XXX - C11 atomic type and functions */
#include <stdlib.h>                 /* qsort */

#undef NULL                         /* stddef.h */
#endif

#include <intrin.h>

CLANG_WARN_DISABLE_POP(everything)
MSVC_WARN_DISABLE_POP(4117)
MSVC_PRAGMA(warning(pop))

#if !defined(TgCOMPILE_FILE__CXX)
    #define nullptr 0
#endif

/*# !defined(TgCOMPILE__NO_SYSTEM_HEADERS) || defined(TgCOMPILE__DOXYGEN_BUILD) */
#endif


/* =============================================================================================================================================================================== */
#endif
