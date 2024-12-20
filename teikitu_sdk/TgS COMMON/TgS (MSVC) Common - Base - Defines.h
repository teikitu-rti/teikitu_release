/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (MSVC) Common - Base - Defines.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_MSVC_COMMON_BASE_DEFINES_H)
#define TGS_MSVC_COMMON_BASE_DEFINES_H
#pragma once

#if !defined(TgBUILD_COMPILER__MSVC)
    #error Build arguments do not indicate this compiler
#endif


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Warnings and Messages                                                                                                                                                          */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

__pragma(comment( compiler ))

__pragma(comment( user, "Compiled on " __DATE__ " at " __TIME__ ))
__pragma(comment( user, "Copyright (C) 2002-2022 Andrew Aye.  All Rights Reserved." ))

__pragma(warning(disable : 4003)) /* Not enough arguments for function-like macro invocation */
__pragma(warning(disable : 4100)) /* Unreferenced formal parameter */
__pragma(warning(disable : 4127)) /* Conditional expression is constant */
__pragma(warning(disable : 4200)) /* Nonstandard extension used: zero-sized array in struct/union */
__pragma(warning(disable : 4201)) /* Nonstandard extension used: nameless struct/union */
__pragma(warning(disable : 4359)) /* Actual alignment (%d) is greater than the value specified in __declspec(align()) */
__pragma(warning(disable : 4447)) /* 'main' signature found without threading model. Consider using 'int main(Platform::Array<Platform::String^>^ args)' */
__pragma(warning(disable : 4464)) /* Relative include path contains '..' */
__pragma(warning(disable : 4514)) /* Unreferenced inline function has been removed */
__pragma(warning(disable : 4577)) /* 'noexcept' used with no exception handling mode specified; termination on exception is not guaranteed. Specify /EHsc */
__pragma(warning(disable : 4710)) /* Function not inline */
__pragma(warning(disable : 4711)) /* Function selected for automatic inline expansion */
__pragma(warning(disable : 4815)) /* Zero-sized array in stack object will have no elements (unless the object is an aggregate that has been aggregate initialized) */
__pragma(warning(disable : 5264)) /* 'variable-name': 'const' variable is not used */
#if defined(TGS_DEBUG)
__pragma(warning(disable : 4505)) /* unreferenced function with internal linkage has been removed */
#endif
#if defined(TGS_FINAL)
__pragma(warning(disable : 4555)) /* result of expression not used */
#endif

/* C++ Warnings */
__pragma(warning(disable : 4164)) /* [FUNCTION]: intrinsic function not declared */
__pragma(warning(disable : 4190)) /* [FUNCTION] has C-linkage specified, but returns UDT '[TYPE]' which is incompatible with C */
__pragma(warning(disable : 4623)) /* [TYPE] default constructor was implicitly defined as deleted */
__pragma(warning(disable : 4625)) /* [TYPE] copy constructor was implicitly defined as deleted */
__pragma(warning(disable : 4626)) /* [TYPE] copy assignment was implicitly defined as deleted */
__pragma(warning(disable : 5026)) /* [TYPE] move constructor was implicitly defined as deleted */
__pragma(warning(disable : 5027)) /* [TYPE] move assignment was implicitly defined as deleted */
__pragma(warning(disable : 5045)) /* Compiler will insert Spectre mitigation for memory load if /Qspectre switch specified */
__pragma(warning(disable : 5220)) /* [TYPE]  non-static data member with a volatile qualified type no longer implies that compiler generated copy/move constructors and copy/move assignment operators are not trivial */

/* Analysis Warnings */
__pragma(warning(disable : 6320)) /* Analysis -Exception filter expression is the constant EXCEPTION_EXECUTE_HANDLER */
__pragma(warning(disable : 28251)) /* Inconsistent annotation for '': this instance has no annotations. */


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Configuration                                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#define TgCOMPILE_BOUNDS_CHECKING_FCNS       1
#define TgCOMPILE__THREAD                    1
#define TgCOMPILE__THREAD_LOCAL              1


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Macros                                                                                                                                                                         */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#define __has_extension(...) 0

#define TgDISABLE_ALL_WARNNGS_PUSH __pragma(warning(push,0)) \
                                   __pragma(warning(disable: 4820))
#define TgDISABLE_ALL_WARNNGS_POP __pragma(warning(pop))

#define TgCLANG_ATTRIBUTE(...)
#define TgCLANG_COMMAND(...)
#define TgCLANG_PRAGMA(...)

#define TgMSVC_ATTRIBUTE(...) __VA_ARGS__
#define TgMSVC_COMMAND(...) __VA_ARGS__
#define TgMSVC_PRAGMA(...) __pragma ( __VA_ARGS__ )

#define TgMSVC_WARN_SUPPRESS(A) __pragma(warning(suppress: A))
#define TgMSVC_WARN_DISABLE_PUSH(...) __pragma(warning(push)) \
                                    __pragma(warning(disable: __VA_ARGS__))
#define TgMSVC_WARN_DISABLE_POP(...) __pragma(warning(pop))

#define TgCLANG_WARN_SUPPRESS(clang_option)
#define TgCLANG_WARN_DISABLE_PUSH(clang_option)
#define TgCLANG_WARN_DISABLE_POP(clang_option)

#define TgWARN_SUPPRESS(msvc_unused,clang_option) TgMSVC_WARN_SUPPRESS(msvc_unused)
#define TgWARN_DISABLE_PUSH(msvc_unused,clang_option) TgMSVC_WARN_DISABLE_PUSH(msvc_unused)
#define TgWARN_DISABLE_POP(clang_option) TgMSVC_WARN_DISABLE_POP()

#define TgANALYSIS_ASSUME(...) __analysis_assume(__VA_ARGS__)

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
#elif defined(_MSC_VER >= 1700)
    #define TgATTRIBUTE_NO_DISCARD _Check_return_
#else
    #define TgATTRIBUTE_NO_DISCARD
#endif

#define TgATTRIBUTE_NO_INLINE __declspec(noinline)

#if (_MSC_VER >= 1900) && !defined(__EDG__)
    #define TgATTRIBUTE_RESTRICT __declspec(allocator) __declspec(restrict)
#else
    #define TgATTRIBUTE_RESTRICT __declspec(restrict)
#endif
#define TgATTRIBUTE_MALLOC

#define TgATTRIBUTE_ALLOC_SIZE1(s)
#define TgATTRIBUTE_ALLOC_SIZE2(s1,s2)
#define TgATTRIBUTE_ALLOC_ALIGN(p)


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
#define TgALIGN(A)                          __declspec(align(A))
#define TgTLS                               __declspec(thread)
#define TgEXPECT_TRUE(...)                  (__VA_ARGS__)
#define TgEXPECT_FALSE(...)                 (__VA_ARGS__)
#define TgPASSINREG                         
#define TgALIAS                             

#if TgCOMPILE_ASSERT
    #define TgS_NO_DEFAULT(...)                 TgCRITICAL(0); __VA_ARGS__
#else
    #define TgS_NO_DEFAULT(...)                 __assume(0)
#endif

#define TgBREAK_INLINE                      __debugbreak()

#define NONULL
#define OKNULL

#define TgANALYSIS_NO_NULL



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
#define tgPM__HARDWARE__BSF_U32 tgMSVC_IMPL__BUILTIN_CTZ
#define tgPM__HARDWARE__BSF_U64 tgMSVC_IMPL__BUILTIN_CTZLL


/* =============================================================================================================================================================================== */
#endif
