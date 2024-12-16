/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (CLANG) Common - Base - Defines.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_CLANG_COMMON_BASE_DEFINES_H)
#define TGS_CLANG_COMMON_BASE_DEFINES_H
#pragma once

#if !defined(TgBUILD_COMPILER__CLANG)
    #error Build arguments do not indicate this compiler
#endif


/* == Common ===================================================================================================================================================================== */
/* MARK: No Unit Test Required                                                                                                                                                     */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Warnings and Messages                                                                                                                                                          */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#pragma clang diagnostic ignored "-W#pragma-messages"                       /* Build and Compiler (and Data, Time) are injected as part of the compile */
#pragma clang diagnostic ignored "-Wextra-semi-stmt"                        /* Disable warnings about extra semi-colons */
#pragma clang diagnostic ignored "-Wnullability-extension"                  /* Allows for marking pointers (normally function parameters) as being non null to help static analysis */
#pragma clang diagnostic ignored "-Wnullability-completeness"               /* Prevents warning on incomplete labeling of pointers */
#pragma clang diagnostic ignored "-Wgnu-zero-variadic-macro-arguments"      /* Triggers because of VAR_T() being empty */

#if defined(TgCOMPILE_FILE__CXX)
#pragma clang diagnostic ignored "-Wc++98-compat-pedantic"                  /* Triggers because of variadic macros */
#pragma clang diagnostic ignored "-Wc++98-compat"                           /* Triggers because of unicode literals */
#pragma clang diagnostic ignored "-Wgnu-anonymous-struct"                   /* Triggers because of anonymous structures (like VEC_S_T) */
#pragma clang diagnostic ignored "-Wreserved-identifier"                    /* Triggers because of macros with with two underscores */
#pragma clang diagnostic ignored "-Wold-style-cast"                         /* Triggers because of C-style casts */
#pragma clang diagnostic ignored "-Wc99-extensions"                         /* Triggers because of flexible array members */
#pragma clang diagnostic ignored "-Wnested-anon-types"                      /* Triggers because of nesting anon structures, as found in STg2_String_Table_Entry_Id. */
#else
#pragma clang diagnostic ignored "-Wc99-compat"                             /* Triggers because of unicode literals */
#pragma clang diagnostic ignored "-Wpre-c++20-compat"                       /* Triggers because of unicode literals */
#endif


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Validations                                                                                                                                                                    */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#if defined(TgCOMPILE_FILE__CXX) && !__has_feature(cxx_unicode_literals)
#error Require unicode literals for multibyte support (default for the platform)
#endif


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Configuration                                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#define _CRT_SECURE_NO_WARNINGS

#define TgCOMPILE__BOUNDS_CHECKING_FCNS     0
#define TgCOMPILE__THREAD                   1

#if __has_feature(c_thread_local)
    #define TgCOMPILE__THREAD_LOCAL             1
#else
    #define TgCOMPILE__THREAD_LOCAL             0
#endif


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Macros                                                                                                                                                                         */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#define DISABLE_ALL_WARNNGS_PUSH __pragma(warning(push,0))
#define DISABLE_ALL_WARNNGS_POP __pragma(warning(pop))

#define DIAG_STR(s) #s
#define DIAG_JOINSTR(x,y) DIAG_STR(x ## y)
#define DIAG_DO_PRAGMA(x) _Pragma (#x)
#define DIAG_PRAGMA(x) DIAG_DO_PRAGMA(clang diagnostic x)

#define CLANG_ATTRIBUTE(...) __attribute__((__VA_ARGS__))
#define CLANG_COMMAND(...) __VA_ARGS__
#define CLANG_PRAGMA(x) DIAG_DO_PRAGMA(clang x)

#define UNUSED_PARAM __attribute__((unused))
#define UNUSED_FUNC __attribute__((unused))
#define UNUSED_TYPE __attribute__((unused))

#define MSVC_ATTRIBUTE(...)
#define MSVC_PRAGMA(...)

#define MSVC_WARN_SUPPRESS(msvc_unused)
#define MSVC_WARN_DISABLE_PUSH(msvc_unused)
#define MSVC_WARN_DISABLE_POP(msvc_unused)

#define CLANG_WARN_SUPPRESS(clang_option) DIAG_PRAGMA(ignored DIAG_JOINSTR(-W,clang_option))
#define CLANG_WARN_DISABLE_PUSH(clang_option) DIAG_PRAGMA(push) DIAG_PRAGMA(ignored DIAG_JOINSTR(-W,clang_option))
#define CLANG_WARN_DISABLE_POP(...) DIAG_PRAGMA(pop)

#define WARN_SUPPRESS(msvc_unused,clang_option) CLANG_WARN_SUPPRESS(clang_option)
#define WARN_DISABLE_PUSH(msvc_unused,clang_option) CLANG_WARN_DISABLE_PUSH(clang_option)
#define WARN_DISABLE_POP(...) CLANG_WARN_DISABLE_POP()

#define TgANALYSIS_ASSUME(...)

#if defined(TgCOMPILE_FILE__CXX) || defined(TgBUILD_COMPILER__CLANG)
    #define SWITCH_FALLTHROUGH CLANG_ATTRIBUTE(fallthrough);
#else
    #define SWITCH_FALLTHROUGH
#endif


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Visual Studio                                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#ifdef _MSC_VER 
#define strncasecoll _strnicoll
#define strcasecoll _stricoll
#define wcsncasecoll _wcsnicoll
#define strncasecmp _strnicmp
#define strcasecmp _stricmp
#define wcsncasecmp _wcsnicmp
#endif


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Keyword Replacements                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#if __has_declspec_attribute(dllimport)
    #define DLL_IMPORT                          __declspec(dllimport) /* Import function from DLL */
#else
    #define DLL_IMPORT
#endif

#if __has_declspec_attribute(dllexport)
    #define DLL_EXPORT                          __declspec(dllexport) /* Export function to DLL */
#else
    #define DLL_EXPORT
#endif

#define TgCDECL                             __attribute__((__cdecl__)) /* Standard C function */
#define CDECL                               __attribute__((__cdecl__)) /* Standard C function */
#define STDCALL                             __attribute__((__stdcall__)) /* Standard calling convention */
#if __has_attribute(always_inline)
#define TgFORCEINLINE                       static __inline __attribute__((always_inline)) /* Force code to be inline */
#else
#define TgFORCEINLINE                       static __inline
#endif
#define TgINLINE                            static __inline
#if defined(TgCOMPILE_FILE__CXX)
#define TgALIGN(A)                          alignas(A)
#else
#define TgALIGN(A)                          _Alignas(A)
#endif
#define TgTLS                               _Thread_local
#define TgNOTHROW                           
#if __has_builtin(__builtin_expect)
    #define TgEXPECT_TRUE(...)                  __builtin_expect( (__VA_ARGS__), 1 )
    #define TgEXPECT_FALSE(...)                 __builtin_expect( (__VA_ARGS__), 0 )
#else
    #define TgEXPECT_TRUE(...)                  (__VA_ARGS__)
    #define TgEXPECT_FALSE(...)                 (__VA_ARGS__)
#endif
#define TgPASSINREG                         
#define TgALIAS                             __attribute__((__may_alias__))

#if TgCOMPILE_ASSERT
    #define TgS_NO_DEFAULT(...)                 TgCRITICAL(0); __VA_ARGS__
#else
    #if __has_builtin(__builtin_unreachable)
        #define TgS_NO_DEFAULT(...)                 __VA_ARGS__
    #else
        #define TgS_NO_DEFAULT(...)                 __builtin_unreachable(); __VA_ARGS__
    #endif
#endif

#if __has_builtin(__builtin_debugtrap)
    #define TgBREAK_INLINE                      __builtin_debugtrap()
#elif __has_builtin(__builtin_trap)
    #define TgBREAK_INLINE                      __builtin_trap()
#else
    #define TgBREAK_INLINE                      abort()
#endif

#define NONULL                              _Nonnull
#define OKNULL                              _Nullable

//TODO __builtin_assume

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Code Macros                                                                                                                                                                    */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#define TgFREEA( VAR )
#define TgALLOCA( TYPE, COUNT, VAR )                                                                                                                                                \
{                                                                                                                                                                                   \
    VAR =  (TYPE *)__builtin_alloca( (COUNT) * sizeof(TYPE) );                                                                                                                      \
}


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Intrinsics                                                                                                                                                                     */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#define TgCOMPILE__HARDWARE__BSF
#define tgPM__HARDWARE__BSF_U32 __builtin_ctz
#define tgPM__HARDWARE__BSF_U64 __builtin_ctzll


/* =============================================================================================================================================================================== */
#endif
