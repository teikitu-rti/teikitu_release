/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (WIN) Kernel - Internal.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
#if !defined(TGS_PLATFORM_KERNEL_INTERNAL_H)
#define TGS_PLATFORM_KERNEL_INTERNAL_H
#pragma once

#include "TgS Common.h"
#include "TgS Kernel.h"

#include "TgS COMMON/TgS (WIN) Common - Base - Include.h"
#include "TgS COMMON/TgS (WIN) Common - Global.h"
#include "TgS KERNEL/TgS (WIN) Kernel - Constants.h"
#include "TgS KERNEL/TgS (WIN) Kernel.h"

#include "TgS Kernel - Internal.h"
#include "TgS (WIN) Kernel - Internal - Type.h"
#include "TgS (WIN) Kernel - Internal - Data.h"

#include "TgS COMMON/TgS Common.inl"

#if !defined(TgBUILD_OS__WIN)
#error This file should only be included for windows based platforms
#endif

#if !defined(TgCOMPILE__THREAD)
#error Windows platform requires threading supoprt.
#endif


/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/** @brief Report the local application directory for the user.
    @param [in,out] OUT0 Pointer to a string to hold the result of the function.
    @param [in] ARG1 Total capacity of the string in ARG0. */
TgEXTN TgVOID
tgKN_Path_Query_Application_Data_Folder(
    TgCHAR_U8_PC OUT0, TgRSIZE_C ARG1 );

/** @brief Report the directory to be used for temporary files.
    @param [in,out] OUT0 Pointer to a string to hold the result of the function.
    @param [in] ARG1 Total capacity of the string in ARG0. */
TgEXTN TgVOID
tgKN_Path_Query_Temporary_Folder(
    TgCHAR_U8_PC OUT0, TgRSIZE_C ARG1 );

TgEXTN TgVOID
tgKN_ReCalc_Display(
    TgSINT_PTR_C ARG0 );




/* =============================================================================================================================================================================== */
#endif
