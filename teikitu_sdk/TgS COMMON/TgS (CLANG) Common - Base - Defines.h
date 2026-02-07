/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (CLANG) Common - Base - Defines.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_CLANG_COMMON_BASE_DEFINES_H)
#define TGS_CLANG_COMMON_BASE_DEFINES_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#if !defined(TgBUILD_COMPILER__CLANG) && !defined(TgBUILD_COMPILER__APPLE)
    #error Build arguments do not indicate this compiler
#endif


/* == Common ===================================================================================================================================================================== */
/* MARK: No Unit Test Required                                                                                                                                                     */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Warnings and Messages                                                                                                                                                          */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#pragma clang diagnostic ignored "-Wreserved-macro-identifier"
#pragma clang diagnostic ignored "-Wmicrosoft-fixed-enum"                   /* Allows for specifying the underlying type for an enumeration */
#pragma clang diagnostic ignored "-W#pragma-messages"                       /* Build and Compiler (and Data, Time) are injected as part of the compile */
#pragma clang diagnostic ignored "-Wextra-semi-stmt"                        /* Disable warnings about extra semi-colons */
#pragma clang diagnostic ignored "-Wnullability-extension"                  /* Allows for marking pointers (normally function parameters) as being non null to help static analysis */
#pragma clang diagnostic ignored "-Wnullability-completeness"               /* Prevents warning on incomplete labeling of pointers */
#pragma clang diagnostic ignored "-Wgnu-zero-variadic-macro-arguments"      /* Triggers because of VAR_T() being empty */
#pragma clang diagnostic ignored "-Wdeclaration-after-statement"            /* Error: mixing declarations and code is incompatible with standards before C99 */
#pragma clang diagnostic ignored "-Wunsafe-buffer-usage"                    /* Disable the dumb-ass warning */
#pragma clang diagnostic ignored "-Wswitch-default"                         /* Triggering even in the case of fully covered switch statements */
#pragma clang diagnostic ignored "-Wanon-enum-enum-conversion"              /* Result Code return */
#pragma clang diagnostic ignored "-Wpre-c23-compat"                         /* Disable warning regarding nullptr */
#if !defined(TgBUILD_OS__ANDROID) || !defined(TgBUILD_HOST_SYSTEM__HLNX)
#pragma clang diagnostic ignored "-Wpre-c11-compat"                         /* Disable warning regarding static assert and atomic */
#endif
#if defined(TgBUILD_OS__ANDROID)
#pragma clang diagnostic ignored "-Watomic-alignment"                       /* Temporay disable: warning that lock free is 8 and most of our atomic values are 16 */
#endif
//#pragma clang diagnostic ignored "-Wunknown-warning-option"                 /* */

#if defined(TgCOMPILE_FILE__CXX)
#pragma clang diagnostic ignored "-Wgnu-anonymous-struct"                   /* Anonymous structures (like VEC_S_T) */
#pragma clang diagnostic ignored "-Wreserved-identifier"                    /* Macros with with two underscores */
#pragma clang diagnostic ignored "-Wold-style-cast"                         /* C-style casts */
#pragma clang diagnostic ignored "-Wc99-extensions"                         /* Flexible array members */
#pragma clang diagnostic ignored "-Wnested-anon-types"                      /* Nesting anon structures, as found in STg2_String_Table_Entry_Id. */
#pragma clang diagnostic ignored "-Wc++98-compat-pedantic"                  /* Variadic macros are incompatible with C++98 */
#pragma clang diagnostic ignored "-Wc++98-compat"                           /* Unicode literals */
#else
#pragma clang diagnostic ignored "-Wc++-keyword"                            /* identifier '' conflicts with a C++ keyword - e.g. wchar_t on Windows */
#pragma clang diagnostic ignored "-Wc99-compat"                             /* Unicode literals */
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

/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* Compiler Warning Settings */

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

/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* Compiler Hints */

#define TgANALYSIS_ASSUME(...)

#if defined(TgCOMPILE_FILE__CXX) && ((defined(_MSVC_LANG) && _MSVC_LANG >= 201103L) || (defined(__cplusplus) && (__cplusplus >= 201103L)))
    #define TgATTRIBUTE_FALLTHROUGH             [[fallthrough]];
    #define TgATTRIBUTE_NO_DISCARD              [[nodiscard]]
    #define TgATTRIBUTE_UNUSED                  [[maybe_unused]]
    #define TgATTRIBUTE_UNUSED_PARAM_CHECK      [[maybe_unused]]
    #define TgATTRIBUTE_LIKELY                  [[likely]]
    #define TgATTRIBUTE_UNLIKELY                [[unlikely]]
#else
    #define TgATTRIBUTE_FALLTHROUGH             __attribute__((fallthrough));
    #define TgATTRIBUTE_NO_DISCARD              __attribute__((warn_unused_result))
    #define TgATTRIBUTE_UNUSED                  __attribute__((unused))
    #if TgCOMPILE_ASSERT && TgCOMPILE_ASSERT__PARAM_CHECK
        #define TgATTRIBUTE_UNUSED_PARAM_CHECK
    #else
        #define TgATTRIBUTE_UNUSED_PARAM_CHECK      __attribute__((unused))
    #endif
    #define TgATTRIBUTE_LIKELY
    #define TgATTRIBUTE_UNLIKELY
#endif

#define TgATTRIBUTE_RESTRICT
#define TgATTRIBUTE_MALLOC                  __attribute__((malloc))

#define TgATTRIBUTE_ALLOC_SIZE1(s)          __attribute__((alloc_size(s)))
#define TgATTRIBUTE_ALLOC_SIZE2(s1,s2)      __attribute__((alloc_size(s1,s2)))
#define TgATTRIBUTE_ALLOC_ALIGN(p)          __attribute__((alloc_align(p)))

/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* Compiler Optimization Hints */

/* Optimization Level Control */
#define TgMSVC_OPT_ENABLE_BASIC
#define TgMSVC_OPT_ENABLE_AGGRESSIVE
#define TgMSVC_OPT_ENABLE_MAXIMUM
#define TgMSVC_OPT_ENABLE_SIZE

/* Optimization Disable/Restore */
#define TgMSVC_OPT_DISABLE_ALL
#define TgMSVC_OPT_RESTORE_DEFAULT

/* Specific Feature Control */
#define TgPRAGMA_OPT_ENABLE_UNROLL          _Pragma("unroll")
#define TgPRAGMA_OPT_DISABLE_UNROLL         _Pragma("nounroll")
#define TgPRAGMA_OPT_ENABLE_VECTOR          _Pragma("clang loop vectorize(enable)")
#define TgPRAGMA_OPT_DISABLE_VECTOR         _Pragma("clang loop vectorize(disable)")

/* Function Attributes */
#if __has_attribute(optimize)
    #define TgATTRIBUTE_FORCE_OPTIMIZE          __attribute__((optimize("O3")))
#else
    #define TgATTRIBUTE_FORCE_OPTIMIZE
#endif
#define TgATTRIBUTE_FORCE_NO_OPTIMIZE       __attribute__((optnone))
#define TgINLINE                            static __inline
#if __has_attribute(noinline)
    #define TgATTRIBUTE_NO_INLINE               __attribute__((noinline)) /* Force code to be inline */
#else
    #define TgATTRIBUTE_NO_INLINE
#endif
#if defined(TgCOMPILE__NO_INLINE)
    #define TgFORCEINLINE                           TgATTRIBUTE_NO_INLINE static
#else
    #if __has_attribute(always_inline)
        #define TgFORCEINLINE                       __attribute__((always_inline)) TgINLINE /* Force code to be inline */
    #else
        #define TgFORCEINLINE                       TgINLINE
    #endif
#endif

/* Path Annotations */
#if __has_attribute(hot)
    #define TgATTRIBUTE_HOT_PATH                __attribute__((hot))
#else
    #define TgATTRIBUTE_HOT_PATH
#endif
#if __has_attribute(cold)
    #define TgATTRIBUTE_COLD_PATH               __attribute__((cold))
#else
    #define TgATTRIBUTE_COLD_PATH
#endif

/* Branch Prediction */
#if __has_builtin(__builtin_expect)
    #define TgEXPECT(A,...)                     __builtin_expect( (__VA_ARGS__), (A) )
#else
    #define TgEXPECT(A,...)                     (__VA_ARGS__)
#endif
#define TgEXPECT_TRUE(...)                  TgEXPECT( 1, (__VA_ARGS__) )
#define TgEXPECT_FALSE(...)                 TgEXPECT( 0, (__VA_ARGS__) )

/* Clang-Specific Additional Options */
#define TgCLANG_VECTORIZE_WIDTH(n)          _Pragma("clang loop vectorize_width(n)")
#define TgCLANG_UNROLL_COUNT(n)             _Pragma("clang loop unroll_count(n)")
#define TgCLANG_DISTRIBUTE_ENABLE           _Pragma("clang loop distribute(enable)")
#define TgCLANG_DISTRIBUTE_DISABLE          _Pragma("clang loop distribute(disable)")
#define TgCLANG_PIPELINE_ENABLE             _Pragma("clang loop pipeline(enable)")
#define TgCLANG_PIPELINE_DISABLE            _Pragma("clang loop pipeline(disable)")
#define TgCLANG_ASSUME_ALIGNED(ptr, n)      __builtin_assume_aligned(ptr, n)
#define TgCLANG_UNREACHABLE                 __builtin_unreachable()

/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* Static Analyzer Hints */

#define TgANALYSIS_NO_NULL                  _Nonnull
#define TgANALYSIS_OK_NULL                  _Nullable


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

#define CDECL                               __attribute__((__cdecl__)) /* Defined in MSVC: Standard C function */
#define STDCALL                             __attribute__((__stdcall__)) /* Defined in MSVC: Standard calling convention */
#define TgALIGN(A)                          alignas(A)
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
