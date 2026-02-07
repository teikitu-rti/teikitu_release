/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (ANDROID) Kernel - Internal.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.21 | »GUID« AEEC8393-9780-4ECA-918D-E3E11F7E2744 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
#if !defined(TGS_ANDROID_KERNEL_INTERNAL_H)
#define TGS_ANDROID_KERNEL_INTERNAL_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "TgS Common.h"
#include "TgS Kernel.h"

#include "TgS COMMON/TgS (ANDROID) Common - Base - Include.h"
#include "TgS COMMON/TgS (ANDROID) Common - Global.h"
#include "TgS KERNEL/TgS (ANDROID) Kernel - Constants.h"
#include "TgS KERNEL/TgS (ANDROID) Kernel.h"

#include "TgS Kernel - Internal.h"
#include "TgS (ANDROID) Kernel - Internal - Type.h"
#include "TgS (ANDROID) Kernel - Internal - Data.h"

#include "TgS COMMON/TgS Common.inl"

#if !defined(TgBUILD_OS__ANDROID)
#error This file should only be included for posix based platforms
#endif

#if !defined(TgCOMPILE__THREAD)
#error Teikitu requires threading supoprt.
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
