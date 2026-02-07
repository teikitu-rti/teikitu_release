/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (INTEL) Common - Base - Defines.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_INTEL_COMMON_BASE_DEFINES_H)
#define TGS_INTEL_COMMON_BASE_DEFINES_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#if !defined(TgBUILD_COMPILER__INTEL)
    #error Build arguments do not indicate this compiler
#endif


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Warnings and Messages                                                                                                                                                          */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#pragma comment( compiler )

#pragma comment( user, "Compiled on " __DATE__ " at " __TIME__ )
#pragma comment( user, "Copyright (C) 2002-2025 Andrew Aye.  All Rights Reserved." )

/* Disable common Intel compiler warnings */
#pragma warning(disable : 188)   /* Enumerated type mixed with another type */
#pragma warning(disable : 279)   /* Controlling expression is constant */
#pragma warning(disable : 383)   /* Reference to temporary used */
#pragma warning(disable : 444)   /* Destructor for base class is not virtual */
#pragma warning(disable : 810)   /* Conversion from "type" to "type" may lose significant bits */
#pragma warning(disable : 869)   /* Parameter was never referenced */
#pragma warning(disable : 981)   /* Operands are evaluated in unspecified order */
#pragma warning(disable : 1418)  /* External function definition with no prior declaration */
#pragma warning(disable : 1419)  /* External declaration in primary source file */
#pragma warning(disable : 1572)  /* Floating-point equality and inequality comparisons are unreliable */
#pragma warning(disable : 1599)  /* Declaration hides variable */
#pragma warning(disable : 2259)  /* Non-pointer conversion may lose significant bits */
#pragma warning(disable : 11074) /* Inlining inhibited by limit max-size */
#pragma warning(disable : 11075) /* Inlining inhibited by limit max-total-size */
#pragma warning(disable : 11076) /* To get full report use -qopt-report=4 -qopt-report-phase ipo */


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Configuration                                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#define TgCOMPILE_BOUNDS_CHECKING_FCNS       1
#define TgCOMPILE__THREAD                    1
#define TgCOMPILE__THREAD_LOCAL              1


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Macros                                                                                                                                                                         */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#ifndef __has_extension
    #define __has_extension(...) 0
#endif

#ifndef __has_attribute
    #define __has_attribute(...) 0
#endif

#ifndef __has_builtin
    #define __has_builtin(...) 0
#endif

#define TgDISABLE_ALL_WARNNGS_PUSH _Pragma("warning(push)") \
                                   _Pragma("warning(disable: 1 10 47 94 111 128 144 167 177 186 188 193 279 304 383 444 810 869 981 1418 1419 1572 1599 2259 11074 11075 11076)")
#define TgDISABLE_ALL_WARNNGS_POP _Pragma("warning(pop)")

#define TgCLANG_ATTRIBUTE(...)
#define TgCLANG_COMMAND(...)
#define TgCLANG_PRAGMA(...)

#define TgMSVC_ATTRIBUTE(...)
#define TgMSVC_COMMAND(...)
#define TgMSVC_PRAGMA(...)

#define TgMSVC_WARN_SUPPRESS(msvc_unused)
#define TgMSVC_WARN_DISABLE_PUSH(msvc_unused)
#define TgMSVC_WARN_DISABLE_POP(msvc_unused)

#define TgCLANG_WARN_SUPPRESS(clang_option)
#define TgCLANG_WARN_DISABLE_PUSH(clang_option)
#define TgCLANG_WARN_DISABLE_POP(clang_option)

#define TgWARN_SUPPRESS(msvc_unused,clang_option)
#define TgWARN_DISABLE_PUSH(msvc_unused,clang_option)
#define TgWARN_DISABLE_POP(clang_option)

#define TgANALYSIS_ASSUME(...) __assume(__VA_ARGS__)

#if defined(TgCOMPILE_FILE__CXX) && ((defined(_MSVC_LANG) && _MSVC_LANG >= 201103L) || (defined(__cplusplus) && (__cplusplus >= 201103L)))
    #define TgATTRIBUTE_FALLTHROUGH [[fallthrough]];
    #define TgATTRIBUTE_UNUSED [[maybe_unused]]
    #define TgATTRIBUTE_UNUSED_PARAM_CHECK [[maybe_unused]]
    #define TgATTRIBUTE_LIKELY [[likely]]
    #define TgATTRIBUTE_UNLIKELY [[unlikely]]
#else
    #define TgATTRIBUTE_FALLTHROUGH
    #define TgATTRIBUTE_UNUSED
    #define TgATTRIBUTE_UNUSED_PARAM_CHECK
    #define TgATTRIBUTE_LIKELY
    #define TgATTRIBUTE_UNLIKELY
#endif

#if defined(TgCOMPILE_FILE__CXX) && ((defined(_MSVC_LANG) && _MSVC_LANG >= 201103L) || (defined(__cplusplus) && (__cplusplus >= 201103L)))
    #define TgATTRIBUTE_NO_DISCARD [[nodiscard]]
#else
    #define TgATTRIBUTE_NO_DISCARD
#endif

#define TgATTRIBUTE_NO_INLINE __attribute__((noinline))

#define TgATTRIBUTE_RESTRICT __restrict
#define TgATTRIBUTE_MALLOC

#define TgATTRIBUTE_ALLOC_SIZE1(s)
#define TgATTRIBUTE_ALLOC_SIZE2(s1,s2)
#define TgATTRIBUTE_ALLOC_ALIGN(p)

/* Optimization Level Control */
#define TgINTEL_OPT_ENABLE_BASIC            _Pragma("optimization_level 1")
#define TgINTEL_OPT_ENABLE_MODERATE         _Pragma("optimization_level 2")
#define TgINTEL_OPT_ENABLE_AGGRESSIVE       _Pragma("optimization_level 3")
#define TgINTEL_OPT_ENABLE_MAXIMUM          _Pragma("optimization_level 3") \
                                            _Pragma("inline_forceinline")
#define TgINTEL_OPT_ENABLE_SIZE             _Pragma("optimize(\"s\", on)")

/* Optimization Disable/Restore */
#define TgINTEL_OPT_DISABLE_ALL             _Pragma("optimize(\"\", off)")
#define TgINTEL_OPT_RESTORE_DEFAULT         _Pragma("optimize(\"\", on)")

/* Specific Feature Control */
#define TgPRAGMA_OPT_ENABLE_UNROLL          _Pragma("unroll")
#define TgPRAGMA_OPT_DISABLE_UNROLL         _Pragma("nounroll")
#define TgPRAGMA_OPT_ENABLE_VECTOR          _Pragma("ivdep")
#define TgPRAGMA_OPT_DISABLE_VECTOR         _Pragma("novector")

/* Function Attributes */
#define TgATTRIBUTE_FORCE_OPTIMIZE          /* Intel uses pragmas around functions */
#define TgATTRIBUTE_FORCE_NO_OPTIMIZE       /* Intel uses pragmas around functions */

/* Path Annotations */
#define TgATTRIBUTE_HOT_PATH                /* Not directly supported */
#define TgATTRIBUTE_COLD_PATH               /* Not directly supported */

/* Branch Prediction */
#define TgEXPECT(A,...)                     (__VA_ARGS__)
#define TgEXPECT_TRUE(...)                  TgEXPECT( 1, (__VA_ARGS__) )
#define TgEXPECT_FALSE(...)                 TgEXPECT( 0, (__VA_ARGS__) )

/* Intel-Specific Additional Options */
#define TgINTEL_VECTORIZE_ALWAYS            _Pragma("vector always")
#define TgINTEL_VECTORIZE_ALIGNED           _Pragma("vector aligned")
#define TgINTEL_VECTORIZE_NONTEMPORAL       _Pragma("vector nontemporal")
#define TgINTEL_SIMD                        _Pragma("simd")
#define TgINTEL_DISTRIBUTE_POINT            _Pragma("distribute point")
#define TgINTEL_LOOP_COUNT(n)               _Pragma("loop_count(n)")
#define TgINTEL_PREFETCH                    _Pragma("prefetch")
#define TgINTEL_INLINE_FORCEINLINE          _Pragma("inline_forceinline")
#define TgINTEL_INLINE_NEVER                _Pragma("inline never")


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

#define TgDLL_IMPORT                        __declspec(dllimport)       /* Import function from DLL */
#define TgDLL_EXPORT                        __declspec(dllexport)       /* Export function to DLL */
#define CDECL                               __cdecl                     /* Standard C function */
#define TgCDECL                             __cdecl                     /* Standard C function */
#define STDCALL                             __stdcall                   /* Standard calling convention */
#if defined(TgCOMPILE__NO_INLINE)
#define TgFORCEINLINE                       static                      /* Force code to be TgINLINE */
#define TgINLINE                            static
#else
#define TgFORCEINLINE                       static __forceinline        /* Force code to be TgINLINE */
#define TgINLINE                            static __inline
#endif
#define TgALIGN(A)                          alignas(A)
#define TgTLS                               __declspec(thread)
#define TgPASSINREG                         
#define TgALIAS                             

#if TgCOMPILE_ASSERT
    #define TgS_NO_DEFAULT(...)                 TgCRITICAL(0); __VA_ARGS__
#else
    #define TgS_NO_DEFAULT(...)                 __assume(0)
#endif

#define TgBREAK_INLINE                      __debugbreak()

#define TgANALYSIS_NO_NULL
#define TgANALYSIS_OK_NULL



/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Code Macros                                                                                                                                                                    */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#if defined(_DEBUG)
    #define _CRTDBG_MAP_ALLOC
    #define TgFREEA( VAR )                      _freea( VAR );
    #define TgALLOCA( TYPE, COUNT, VAR )                                                                                                                                            \
    {                                                                                                                                                                               \
        union                                                                                                                                                                       \
        {                                                                                                                                                                           \
            TgUINT_E08_P pui08;                                                                                                                                                     \
            TgUINT_E32_P pui32;                                                                                                                                                     \
            TgVOID_P p;                                                                                                                                                             \
        } sMem;                                                                                                                                                                     \
        sMem.p = (TYPE*)_malloca( (COUNT) * sizeof(TYPE) );                                                                                                                         \
        VAR = (TYPE *)sMem.p;                                                                                                                                                       \
        if ( VAR )                                                                                                                                                                  \
        {                                                                                                                                                                           \
            sMem.pui08 -= _ALLOCA_S_MARKER_SIZE;                                                                                                                                    \
            if (*sMem.pui32 == _ALLOCA_S_STACK_MARKER)                                                                                                                              \
            {                                                                                                                                                                       \
                tgCN_PrintF( KTgCN_CHANEL_LOG_MEM | KTgCN_SEVERITY_6, u8"Allocated %d bytes of stack\n",(COUNT) * sizeof(TYPE) );                                                   \
            }                                                                                                                                                                       \
            else                                                                                                                                                                    \
            {                                                                                                                                                                       \
                tgCN_PrintF( KTgCN_CHANEL_LOG_MEM | KTgCN_SEVERITY_6, u8"Allocated %d bytes of heap\n", (COUNT) * sizeof(TYPE) );                                                   \
            }                                                                                                                                                                       \
        }                                                                                                                                                                           \
    }
#else
    #define TgFREEA( VAR )                      _freea( VAR );
    #define TgALLOCA( TYPE, COUNT, VAR )        { VAR =  (TYPE*)_malloca( (COUNT) * sizeof(TYPE) ); }
#endif

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Intrinsics                                                                                                                                                                     */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#define TgCOMPILE__HARDWARE__BSF
#define tgPM__HARDWARE__BSF_U32 _bit_scan_forward
#define tgPM__HARDWARE__BSF_U64 _bit_scan_forward


/* =============================================================================================================================================================================== */
#endif
