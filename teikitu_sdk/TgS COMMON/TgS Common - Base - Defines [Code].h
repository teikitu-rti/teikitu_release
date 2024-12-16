/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Base - Defines [Code].h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_BASE_DEFINES_CODE_H)
#define TGS_COMMON_BASE_DEFINES_CODE_H
#pragma once


/* == Common ===================================================================================================================================================================== */
/* MARK: No Unit Test Required                                                                                                                                                     */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Language Flags                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#define __STDC_WANT_LIB_EXT1__              1
#define __DARWIN_C_LEVEL                    __DARWIN_C_FULL


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Code Constants                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#define TgCOMPILE_MEM_MALLOC_PATTERN        0xEB
#define TgCOMPILE_MEM_FREE_PATTERN          0xFA

#define KTgID__INVALID_VALUE                0ULL

#define STD_MSG_PREFIX                      u8"| %-12.12s | %-47.47s | "
#define STD_MSG_LITERAL_0                   u8"| %-12.12s | %-47.47s |\n"
#define STD_MSG_LITERAL_1X                  u8"| %-12.12s | %-47.47s | %s\n"
#define STD_MSG_LITERAL_1                   u8"| %-12.12s | %-47.47s | %-40.40s |\n"
#define STD_MSG_LITERAL_2                   u8"| %-12.12s | %-47.47s | %-40.40s | %-16.16s |\n"
#define STD_MSG_LITERAL_2X                  u8"| %-12.12s | %-47.47s | %-40.40s | %s\n"
#define STD_MSG_LITERAL_2M                  u8"| %-12.12s | %-47.47s | %-40.40s | %-43.43s |\n"
#define STD_MSG_LITERAL_3                   u8"| %-12.12s | %-47.47s | %-40.40s | %-20.20s | %-20.20s |\n"
#define STD_MSG_LITERAL_LOAD_1              u8"| %-12.12s | %-47.47s | %-40.40s | id(% 16d) | % 17d BY |\n"
#define STD_MSG_POST                        TgU8_TEXT_WITH_QUOTE(__MODULE__), __FUNCTION__


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Memory Tracking                                                                                                                                                                */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#if defined(TgCOMPILE__FORCE_C_MEMORY_ALLOCATION) && (TgCOMPILE__FORCE_C_MEMORY_ALLOCATION >= 1)
    #define TgMALLOC_EXACT(A)                   malloc( A )
    #define TgFREE__EXACT(A)                    free( A )
    #define TgMALLOC_POOL(A)                    malloc( A )
    #define TgFREE_POOL(A)                      free( A )
    #define TgREALLOC_POOL(A,B)                 realloc( A, B )
    #define TgMALLOC_TEMP(A)                    malloc( A )
    #define TgFREE_TEMP(A)                      free( A )
    #define TgMALLOC_NOTRACE(A)                 malloc( A )
    #define TgFREE_NOTRACE(A)                   free( A )
    #define TgMALLOC_POOL_COMMENT(A)            malloc( A )

    #define TgRESERVE_VIRTUAL(A)                malloc( A )
    #define TgCOMMIT_VIRTUAL(A,B,C)             (A+B)
    #define TgFREE_VIRTUAL(A)                   free( A )

#elif defined(TgCOMPILE__MEM_TRACK)
    #define TgMALLOC_EXACT(A)                   tgMM_Malloc_With_Trace( ETgMM_ALLOCATOR_MIMALLOC, A, 16, TgU8_TEXT_WITH_QUOTE(__FILE__), __LINE__ )
    #define TgFREE__EXACT(A)                    tgMM_Free_With_Trace( ETgMM_ALLOCATOR_MIMALLOC, A, TgU8_TEXT_WITH_QUOTE(__FILE__), __LINE__ )
    #define TgMALLOC_POOL(A)                    tgMM_Malloc_With_Trace( ETgMM_ALLOCATOR_MIMALLOC, A, 16, TgU8_TEXT_WITH_QUOTE(__FILE__), __LINE__ )
    #define TgFREE_POOL(A)                      tgMM_Free_With_Trace( ETgMM_ALLOCATOR_MIMALLOC, A, TgU8_TEXT_WITH_QUOTE(__FILE__), __LINE__ )
    #define TgREALLOC_POOL(A,B)                 tgMM_Realloc_With_Trace( ETgMM_ALLOCATOR_MIMALLOC, A, B, 16, TgU8_TEXT_WITH_QUOTE(__FILE__), __LINE__ )
    #define TgMALLOC_TEMP(A)                    tgMM_Malloc_With_Trace( ETgMM_ALLOCATOR_MIMALLOC, A, 16, TgU8_TEXT_WITH_QUOTE(__FILE__), __LINE__ )
    #define TgFREE_TEMP(A)                      tgMM_Free_With_Trace( ETgMM_ALLOCATOR_MIMALLOC, A, TgU8_TEXT_WITH_QUOTE(__FILE__), __LINE__ )
    #define TgMALLOC_NOTRACE(A)                 tgMM_Malloc( ETgMM_ALLOCATOR_MIMALLOC, A, 16 )
    #define TgFREE_NOTRACE(A)                   tgMM_Free( ETgMM_ALLOCATOR_MIMALLOC, A )
    #define TgMALLOC_POOL_COMMENT(A,B)          tgMM_Malloc_With_Trace_Comment( ETgMM_ALLOCATOR_MIMALLOC, A, 16, TgU8_TEXT_WITH_QUOTE(__FILE__), __LINE__, B )

    #define TgRESERVE_VIRTUAL(A)                tgMM_Reserve_With_Trace( ETgMM_ALLOCATOR_OS, A, TgU8_TEXT_WITH_QUOTE(__FILE__), __LINE__ )
    #define TgCOMMIT_VIRTUAL(A,B,C)             tgMM_Commit_With_Trace( ETgMM_ALLOCATOR_OS, A, B, C, TgU8_TEXT_WITH_QUOTE(__FILE__), __LINE__ )
    #define TgFREE_VIRTUAL(A)                   tgMM_Free_With_Trace( ETgMM_ALLOCATOR_OS, A, TgU8_TEXT_WITH_QUOTE(__FILE__), __LINE__ )
#else
    #define TgMALLOC_EXACT(A)                   tgMM_Malloc( ETgMM_ALLOCATOR_MIMALLOC, A, 16 )
    #define TgFREE__EXACT(A)                    tgMM_Free( ETgMM_ALLOCATOR_MIMALLOC, A )
    #define TgMALLOC_POOL(A)                    tgMM_Malloc( ETgMM_ALLOCATOR_MIMALLOC, A, 16 )
    #define TgFREE_POOL(A)                      tgMM_Free( ETgMM_ALLOCATOR_MIMALLOC, A )
    #define TgREALLOC_POOL(A,B)                 tgMM_Realloc( ETgMM_ALLOCATOR_MIMALLOC, A, B, 16 )
    #define TgMALLOC_TEMP(A)                    tgMM_Malloc( ETgMM_ALLOCATOR_MIMALLOC, A, 16 )
    #define TgFREE_TEMP(A)                      tgMM_Free( ETgMM_ALLOCATOR_MIMALLOC, A )
    #define TgMALLOC_NOTRACE(A)                 tgMM_Malloc( ETgMM_ALLOCATOR_MIMALLOC, A, 16 )
    #define TgFREE_NOTRACE(A)                   tgMM_Free( ETgMM_ALLOCATOR_MIMALLOC, A )
    #define TgMALLOC_POOL_COMMENT(A,B)          tgMM_Malloc( ETgMM_ALLOCATOR_MIMALLOC, A, 16 )

    #define TgRESERVE_VIRTUAL(A)                tgMM_Reserve( ETgMM_ALLOCATOR_OS, A )
    #define TgCOMMIT_VIRTUAL(A,B,C)             tgMM_Commit( ETgMM_ALLOCATOR_OS, A, B, C )
    #define TgFREE_VIRTUAL(A)                   tgMM_Free( ETgMM_ALLOCATOR_OS, A )
#endif

#define TgMEMCPY_NOCACHE tgMM_Copy


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Unique Identifiers                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#define TgKI_CUSTOM_DECLARE_AND_INLINE(A) TgKI_CUSTOM_DECLARE_AND_INLINE_2(A)

#define TgKI_CUSTOM_DECLARE_AND_INLINE_2(A)                                                                                                                                         \
                                                                                                                                                                                    \
    TgTYPE_STRUCT(Tg##A##_SINGLETON,)                                                                                                                                               \
    {                                                                                                                                                                               \
        TgALIGN(8) TgUINT_E64_A                 m_uiKI;                                                                                                                             \
        TgCXX_CONSTRUCTOR(Tg##A##_SINGLETON(): m_uiKI(KTgMAX_U64) {})                                                                                                               \
    };                                                                                                                                                                              \
                                                                                                                                                                                    \
    TgEXTN Tg##A##_C KTg##A##__INVALID;                                                                                                                                             \
    TgEXTN TgUINT_E32_A tgKI_NUI_##A;                                                                                                                                               \
                                                                                                                                                                                    \
    TgFORCEINLINE TgVOID tg##A##_Store( Tg##A##_SINGLETON_PCU psK0, Tg##A##_C sK1 )                                                                                                 \
    {                                                                                                                                                                               \
        TgSTD_ATOMIC(store)( &(psK0->m_uiKI), sK1.m_uiKI );                                                                                                                         \
    }                                                                                                                                                                               \
                                                                                                                                                                                    \
    TgFORCEINLINE TgVOID tg##A##_Invalidate( Tg##A##_SINGLETON_PCU psK0 )                                                                                                           \
    {                                                                                                                                                                               \
        TgSTD_ATOMIC(store)( &(psK0->m_uiKI), KTgID__INVALID_VALUE );                                                                                                               \
    }                                                                                                                                                                               \
                                                                                                                                                                                    \
    TgFORCEINLINE TgVOID tg##A##_Load( Tg##A##_PCU psK0, Tg##A##_SINGLETON_PCU psK1 )                                                                                               \
    {                                                                                                                                                                               \
        psK0->m_uiKI = TgSTD_ATOMIC(load)( &(psK1->m_uiKI) );                                                                                                                       \
    }                                                                                                                                                                               \
                                                                                                                                                                                    \
    TgFORCEINLINE Tg##A tg##A##_Query_Unsafe( Tg##A##_SINGLETON_CPCU psK1 )                                                                                                         \
    {                                                                                                                                                                               \
        Tg##A                                sInit;                                                                                                                                 \
        sInit.m_uiKI = TgSTD_ATOMIC(load)( &(psK1->m_uiKI) );                                                                                                                       \
        return (sInit);                                                                                                                                                             \
    }                                                                                                                                                                               \
                                                                                                                                                                                    \
    TgFORCEINLINE TgVOID tg##A##_Load_U64( TgUINT_E64_PCU puiKI, Tg##A##_SINGLETON_PCU psK1 )                                                                                       \
    {                                                                                                                                                                               \
        *puiKI = TgSTD_ATOMIC(load)( &(psK1->m_uiKI) );                                                                                                                             \
    }                                                                                                                                                                               \
                                                                                                                                                                                    \
    TgFORCEINLINE TgBOOL tg##A##_Fetch_And_Is_Valid( Tg##A##_P psK1, Tg##A##_SINGLETON_PCU psK0 )                                                                                   \
    {                                                                                                                                                                               \
        Tg##A                                sInit;                                                                                                                                 \
                                                                                                                                                                                    \
        if (nullptr == psK1)                                                                                                                                                        \
        {                                                                                                                                                                           \
            psK1 = &sInit;                                                                                                                                                          \
        };                                                                                                                                                                          \
                                                                                                                                                                                    \
        psK1->m_uiKI = KTg##A##__INVALID.m_uiKI;                                                                                                                                    \
                                                                                                                                                                                    \
        return (TgSTD_ATOMIC(compare_exchange_strong)( &(psK0->m_uiKI), &psK1->m_uiKI, psK1->m_uiKI) ? false : true);                                                               \
    }                                                                                                                                                                               \
                                                                                                                                                                                    \
    TgFORCEINLINE TgBOOL tg##A##_Is_Equal_Test( Tg##A##_SINGLETON_PCU psK0, Tg##A##_SINGLETON_PCU psK1 )                                                                            \
    {                                                                                                                                                                               \
        Tg##A                                sInit;                                                                                                                                 \
        sInit.m_uiKI = TgSTD_ATOMIC(load)( &(psK1->m_uiKI) );                                                                                                                       \
        return (TgSTD_ATOMIC(compare_exchange_strong)( &(psK0->m_uiKI), &sInit.m_uiKI, sInit.m_uiKI));                                                                              \
    }                                                                                                                                                                               \
                                                                                                                                                                                    \
    TgFORCEINLINE TgBOOL tg##A##_Is_Equal_U64( Tg##A##_SINGLETON_PCU psK0, TgUINT_E64 uiKI )                                                                                        \
    {                                                                                                                                                                               \
        return (TgSTD_ATOMIC(compare_exchange_strong)( &(psK0->m_uiKI), &uiKI, uiKI));                                                                                              \
    }                                                                                                                                                                               \
                                                                                                                                                                                    \
    TgFORCEINLINE TgBOOL tg##A##_Is_Equal( Tg##A##_SINGLETON_PCU psK0, Tg##A sK1 )                                                                                                  \
    {                                                                                                                                                                               \
        return (TgSTD_ATOMIC(compare_exchange_strong)( &(psK0->m_uiKI), &sK1.m_uiKI, sK1.m_uiKI));                                                                                  \
    }




#define TgKI_DECLARE(A) TgKI_DECLARE_(A)

#define TgKI_DECLARE_(A)                                                                                                                                                            \
                                                                                                                                                                                    \
    typedef union                                                                                                                                                                   \
    {                                                                                                                                                                               \
        TgALIGN(8) TgUINT_E64                   m_uiKI;                                                                                                                             \
        struct {                                                                                                                                                                    \
            TgUINT_E32                                  m_uiK;                                                                                                                      \
            TgUINT_E32                                  m_uiI;                                                                                                                      \
        };                                                                                                                                                                          \
    } Tg##A;                                                                                                                                                                        \
    TgTYPE_MODIFIER_ALL( Tg##A );                                                                                                                                                   \
                                                                                                                                                                                    \
    TgKI_CUSTOM_DECLARE_AND_INLINE(A)                                                                                                                                               \
                                                                                                                                                                                    \
    TgFORCEINLINE Tg##A tg##A##_Init( Tg##A##_SINGLETON_PCU psKI, TgUINT_E32_C uiI )                                                                                                \
    {                                                                                                                                                                               \
        Tg##A                                sInit;                                                                                                                                 \
        sInit.m_uiK = TgSTD_ATOMIC(fetch_add)( &(tgKI_NUI_##A), 1 );                                                                                                                \
        sInit.m_uiI = uiI;                                                                                                                                                          \
        TgSTD_ATOMIC(store)( &(psKI->m_uiKI), sInit.m_uiKI );                                                                                                                       \
        return (sInit);                                                                                                                                                             \
    }




#define TgKI_DEFINE(A) TgKI_DEFINE_(A)

#define TgKI_DEFINE_(A)                                                                                                                                                             \
    TgUINT_E32_A tgKI_NUI_##A = 1001;                                                                                                                                               \
    Tg##A##_C KTg##A##__INVALID = { KTgID__INVALID_VALUE }




#define LOG_STD_MSG_USZ_FMTU64(CHANNEL,MSG,NUM_BYTE)                                                                                                                                \
    {                                                                                                                                                                               \
        TgRSIZE_C                           nbyByte = NUM_BYTE;                                                                                                                     \
        TgCHAR_U8                           uszBuffer[16];                                                                                                                          \
                                                                                                                                                                                    \
        if (TgSUCCEEDED(tgUSZ_Formatted_From_U64(uszBuffer,sizeof(uszBuffer),nbyByte)))                                                                                             \
        {                                                                                                                                                                           \
            tgCN_PrintF( CHANNEL, STD_MSG_PREFIX u8"%-48.48s % 14s\n", STD_MSG_POST, MSG, uszBuffer );                                                                              \
        }                                                                                                                                                                           \
        else                                                                                                                                                                        \
        {                                                                                                                                                                           \
            tgCN_PrintF( CHANNEL, STD_MSG_PREFIX u8"%-48.48s % 14d\n", STD_MSG_POST, MSG, nbyByte );                                                                                \
        }                                                                                                                                                                           \
    }




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Utility macro to allow for default arguments                                                                                                                                   */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @see <a href="https://stackoverflow.com/questions/3046889/optional-parameters-with-c-macros">Original Source</a> */
#define FUNC_CHOOSER(_f0, _f1, _f2, _f3, _f4, _f5, _f6, _f7, _f8, _f9, _f10, _f11, _f12, _f13, _f14, _f15, _f16, ...) _f16
#define FUNC_RECOMPOSER(argsWithParentheses) FUNC_CHOOSER argsWithParentheses
#define CHOOSE_FROM_ARG_COUNT(F, ...) FUNC_RECOMPOSER((__VA_ARGS__, \
            F##_16, F##_15, F##_14, F##_13, F##_12, F##_11, F##_10, F##_9, F##_8,\
            F##_7, F##_6, F##_5, F##_4, F##_3, F##_2, F##_1, ))
#define NO_ARG_EXPANDER(FUNC) ,,,,,,,,,,,,,,,,FUNC ## _0
#define MACRO_CHOOSER(FUNC, ...) CHOOSE_FROM_ARG_COUNT(FUNC, NO_ARG_EXPANDER __VA_ARGS__ (FUNC))
#define MULTI_MACRO(FUNC, ...) MACRO_CHOOSER(FUNC, __VA_ARGS__)(__VA_ARGS__)

#define DEBUG_TIME_BLOCK(A,...)                                                                                                                                                     \
{                                                                                                                                                                                   \
    TgFLOAT64_C fStart = (TgFLOAT64)tgTM_Query_Time();                                                                                                                              \
    __VA_ARGS__                                                                                                                                                                     \
    TgMSGF(0, A u8": %f\n", (TgFLOAT64)tgTM_Query_Time() - fStart);                                                                                                                 \
}




/* =============================================================================================================================================================================== */
#endif
