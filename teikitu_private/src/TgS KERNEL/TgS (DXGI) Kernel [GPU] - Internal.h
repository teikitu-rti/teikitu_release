/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (DXGI) Kernel [GPU] - Internal.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
#if !defined(TGS_DXGI_KERNEL_INTERNAL_H)
#define TGS_DXGI_KERNEL_INTERNAL_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

TgCLANG_WARN_DISABLE_PUSH(everything)
TgMSVC_PRAGMA(warning(push, 0))
TgMSVC_PRAGMA(warning(disable: 4820 4668 5039))
#include <combaseapi.h>
#include <dxgi1_6.h>
#include <dxgidebug.h>
#define NOTEXTMETRIC
#include <wingdi.h>
TgMSVC_PRAGMA(warning(pop))
TgCLANG_WARN_DISABLE_POP(everything)

#if !defined(TgBUILD_OS__WINDOWS)
#error This file should only be included for windows based platforms
#endif


/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Types                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgTYPE_MODIFIER_ALL(DXGI_MODE_DESC1);
TgTYPE_MODIFIER_ALL(IDXGIOutput6);

TgTYPE_STRUCT(STg2_KN_OS_GPU_DXGI_Output)
{
    DXGI_OUTPUT_DESC1                           m_sDXGI_Output_DESC;
    DXGI_MODE_DESC1_P                           m_psDXGI_Mode;
    TgRSIZE                                     m_nuiDXGI_Mode;
};

TgTYPE_STRUCT(STg2_KN_OS_GPU_DXGI_CXT_SWAP)
{
    TgCHAR_WC                                   m_wszDevice_Name[1024];
    DISPLAYCONFIG_PATH_INFO                     m_sPath_Info;
    TgRSIZE                                     m_uiBest_Output;
    TgUINT_E64                                  m_bInit;
};




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Types                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgEXTN IDXGIFactory7                        *g_pDXGIFactory;

TgEXTN STg2_KN_OS_GPU_DXGI_Output           g_asDXGI_Output[KTgKN_GPU_MAX_OUTPUT];
TgEXTN TgRSIZE                              g_nuiDXGI_Output;
TgEXTN STg2_KN_OS_GPU_DXGI_CXT_SWAP         g_asOS_EXT_Swap_Context_Output[KTgKN_GPU_MAX_SWAP_CONTEXT];




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgEXTN TgVOID
tgKN_OS_GPU_DXGI_Enumerate_Output_Modes(
    DXGI_MODE_DESC1_PP OUT0, TgRSIZE_P OUT1, UINT* OUT2, IDXGIOutput6_P ARG3 );

/** @brief Find the exact mode for a given swap chain.
    @param [out] ARG0 Pointer to a Context Swap/Output.
    @param [in] ARG1 Pointer to the found mode.
    @return True when the mode is found, false otherwise. */
TgEXTN TgBOOL
tgKN_OS_GPU_CXT_SWAP_Find_Mode(
    STg2_KN_GPU_CXT_SWAP_CPC ARG0, DXGI_MODE_DESC1_P ARG1 );




/* =============================================================================================================================================================================== */
#endif
