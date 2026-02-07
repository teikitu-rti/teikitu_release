/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Kernel [GPU] - Internal - Constants.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_KERNEL_GPU_INTERNAL_CONSTANTS_H)
#define TGS_KERNEL_GPU_INTERNAL_CONSTANTS_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif


/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Configuration                                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

#define KTgKN_GPU_ENGINE_NAME                   "Teikitu Gaming System"
#define KTgKN_GPU_APPLICATION_NAME              "Teikitu Application"

enum { KTgKN_GPU_MAX_HIGH_USE_ALLOC             = KTgKN_MAX_JOB_THREAD + 16, /**< Number of allocators available concurrently for recording of high use list types. */
       KTgKN_GPU_MAX_LOW_USE_ALLOC              = 4 }; /**< Number of allocators available concurrently for recording of low use list types. */




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Macro Code Blocks                                                                                                                                                              */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

#define TgPARAM_CHECK_KN_EXEC_EXEC( A )                                                                                                                                             \
    TgPARAM_CHECK_INDEX( (A).m_uiI, g_asKN_GPU_CXT_EXEC );                                                                                                                          \
    TgPARAM_CHECK( tgKN_GPU_CXT_EXEC_ID_Is_Equal( &(g_asKN_GPU_CXT_EXEC[(A).m_uiI].m_tiCXT_EXEC_S), (A) ) )

#define TgPARAM_CHECK_KN_EXEC_SWAP( A )                                                                                                                                             \
    TgPARAM_CHECK_INDEX( tiCXT_SWAP.m_uiI, g_asKN_GPU_CXT_SWAP );                                                                                                                   \
    TgPARAM_CHECK( tgKN_GPU_CXT_SWAP_ID_Is_Equal( &(g_asKN_GPU_CXT_SWAP[tiCXT_SWAP.m_uiI].m_tiCXT_SWAP_S), tiCXT_SWAP ) );                                                          \
    TgPARAM_CHECK_KN_EXEC_EXEC( g_asKN_GPU_CXT_SWAP[tiCXT_SWAP.m_uiI].m_tiCXT_EXEC )

#define TgPARAM_CHECK_KN_EXEC_WORK( A )                                                                                                                                             \
    TgPARAM_CHECK_INDEX( ((A).m_uiI >> 16) & 0xFFFF, g_asKN_GPU_EXT_CXT_EXEC );                                                                                                     \
    TgPARAM_CHECK_INDEX( ((A).m_uiI & 0xFFFF) % KTgKN_GPU_MAX_EXEC_CONTEXT_COMMAND, g_asKN_GPU_EXT_CXT_EXEC[((A).m_uiI >> 16) & 0xFFFF].m_sContext_Command );                       \
    TgPARAM_CHECK( tgKN_GPU_CXT_WORK_ID_Is_Equal(                                                                                                                                   \
        &g_asKN_GPU_EXT_CXT_EXEC[((A).m_uiI >> 16) & 0xFFFF].m_sContext_Command[((A).m_uiI & 0xFFFF) % KTgKN_GPU_MAX_EXEC_CONTEXT_COMMAND].m_tiCXT_WORK_S, (A) ) );                 \
    TgPARAM_CHECK( tgKN_GPU_CXT_EXEC_ID_Is_Equal(                                                                                                                                   \
        &g_asKN_GPU_CXT_EXEC[((A).m_uiI >> 16) & 0xFFFF].m_tiCXT_EXEC_S,                                                                                                            \
        g_asKN_GPU_EXT_CXT_EXEC[((A).m_uiI >> 16) & 0xFFFF].m_sContext_Command[((A).m_uiI & 0xFFFF) % KTgKN_GPU_MAX_EXEC_CONTEXT_COMMAND].m_tiCXT_EXEC ) )

#define TgPARAM_CHECK_KN_GPU_CMD( A )                                                                                                                                               \
    TgPARAM_CHECK_KN_EXEC_WORK(((STg2_KN_GPU_CMD_P)(A))->m_tiCXT_WORK)


/* =============================================================================================================================================================================== */
#endif
