/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (APPLE) Common - Base - Defines.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_APPLE_COMMON_BASE_DEFINES_H)
#define TGS_APPLE_COMMON_BASE_DEFINES_H
#pragma once

#if !defined(TgBUILD_COMPILER__APPLE)
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
#pragma clang diagnostic ignored "-Wdeclaration-after-statement"            /* Error: mixing declarations and code is incompatible with standards before C99 */

#if defined(TgCOMPILE_FILE__CXX)
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

#define TgDIAG_STR(s) #s
#define TgDIAG_JOINSTR(x,y) TgDIAG_STR(x ## y)
#define TgDIAG_DO_PRAGMA(x) _Pragma (#x)
#define TgDIAG_PRAGMA(x) TgDIAG_DO_PRAGMA(clang diagnostic x)

#define TgDISABLE_ALL_WARNNGS_PUSH _Pragma("GCC diagnostic push") \
                                   _Pragma("GCC diagnostic ignored \"-Weverything\"")
#define TgDISABLE_ALL_WARNNGS_POP  _Pragma("GCC diagnostic pop")

#define TgCLANG_ATTRIBUTE(...) __attribute__((__VA_ARGS__))
#define TgCLANG_COMMAND(...) __VA_ARGS__
#define TgCLANG_PRAGMA(x) TgDIAG_DO_PRAGMA(clang x)

#define TgMSVC_ATTRIBUTE(...)
#define TgMSVC_COMMAND(...)
#define TgMSVC_PRAGMA(...)

#define TgMSVC_WARN_SUPPRESS(msvc_unused)
#define TgMSVC_WARN_DISABLE_PUSH(msvc_unused)
#define TgMSVC_WARN_DISABLE_POP(msvc_unused)

#define TgCLANG_WARN_SUPPRESS(clang_option) TgDIAG_PRAGMA(ignored TgDIAG_JOINSTR(-W,clang_option))
#define TgCLANG_WARN_DISABLE_PUSH(clang_option) TgDIAG_PRAGMA(push) TgDIAG_PRAGMA(ignored TgDIAG_JOINSTR(-W,clang_option))
#define TgCLANG_WARN_DISABLE_POP(...) TgDIAG_PRAGMA(pop)

#define TgWARN_SUPPRESS(msvc_unused,clang_option) TgCLANG_WARN_SUPPRESS(clang_option)
#define TgWARN_DISABLE_PUSH(msvc_unused,clang_option) TgCLANG_WARN_DISABLE_PUSH(clang_option)
#define TgWARN_DISABLE_POP(...) TgCLANG_WARN_DISABLE_POP()

#define TgANALYSIS_ASSUME(...)

#if defined(TgCOMPILE_FILE__CXX) && ((defined(_MSVC_LANG) && _MSVC_LANG >= 201103L) || (defined(__cplusplus) && (__cplusplus >= 201103L)))
    #define TgATTRIBUTE_FALLTHROUGH [[fallthrough]];
    #define TgATTRIBUTE_NO_DISCARD [[nodiscard]]
    #define TgATTRIBUTE_UNUSED [[maybe_unused]]
    #define TgATTRIBUTE_LIKELY [[likely]]
    #define TgATTRIBUTE_UNLIKELY [[unlikely]]
#else
    #define TgATTRIBUTE_FALLTHROUGH __attribute__((fallthrough));
    #define TgATTRIBUTE_NO_DISCARD __attribute__((warn_unused_result))
    #define TgATTRIBUTE_UNUSED __attribute__((unused))
    #define TgATTRIBUTE_LIKELY
    #define TgATTRIBUTE_UNLIKELY
#endif

#define TgATTRIBUTE_NO_INLINE __attribute__((noinline))
#define TgATTRIBUTE_RESTRICT
#define TgATTRIBUTE_MALLOC __attribute__((malloc))

#define TgATTRIBUTE_ALLOC_SIZE1(s) __attribute__((alloc_size(s)))
#define TgATTRIBUTE_ALLOC_SIZE2(s1,s2) __attribute__((alloc_size(s1,s2)))
#define TgATTRIBUTE_ALLOC_ALIGN(p) __attribute__((alloc_align(p)))


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
    #define TgDLL_IMPORT                        __declspec(dllimport) /* Import function from DLL */
#else
    #define TgDLL_IMPORT
#endif

#if __has_declspec_attribute(dllexport)
    #define TgDLL_EXPORT                        __declspec(dllexport) /* Export function to DLL */
#else
    #define TgDLL_EXPORT
#endif

#if __has_attribute(always_inline)
    #define TgFORCEINLINE                       static __inline __attribute__((always_inline)) /* Force code to be inline */
#else
    #define TgFORCEINLINE                       static __inline
#endif

#if __has_builtin(__builtin_expect)
    #define TgEXPECT_TRUE(...)                  __builtin_expect( (__VA_ARGS__), 1 )
    #define TgEXPECT_FALSE(...)                 __builtin_expect( (__VA_ARGS__), 0 )
#else
    #define TgEXPECT_TRUE(...)                  (__VA_ARGS__)
    #define TgEXPECT_FALSE(...)                 (__VA_ARGS__)
#endif

#define CDECL                               __attribute__((__cdecl__)) /* Defined in MSVC: Standard C function */
#define STDCALL                             __attribute__((__stdcall__)) /* Defined in MSVC: Standard calling convention */
#define TgINLINE                            static __inline

#if defined(TgCOMPILE_FILE__CXX)
    #define TgALIGN(A)                          alignas(A)
#else
    #define TgALIGN(A)                          _Alignas(A)
#endif

#define TgTLS                               _Thread_local
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

#define TgANALYSIS_NO_NULL                  _Nonnull


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
