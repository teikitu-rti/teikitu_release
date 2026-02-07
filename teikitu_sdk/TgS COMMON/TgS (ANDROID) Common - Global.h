/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (ANDROID) Common - Global.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_ANDROID_COMMON_GLOBAL_H)
#define TGS_ANDROID_COMMON_GLOBAL_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "TgS COMMON/TgS (ANDROID) Common - Base - Type.h"


/* == Common ===================================================================================================================================================================== */

/* ---- Debug Output ------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/** @addtogroup TGS_COMMON_BASE_TYPE_IO_DBG Debug Output Functions
    @{ */

/** @brief Default output function used to write text through DebugOutput.
    @param [in,out] OUT0 Pointer to an output object that is used for writing.
    @param [in] ARG1 Integer representing the maximum amount of data to write.
    @param [in] ARG2 Pointer to the start of the memory to be written.
    @param [in] ARG3 Integer representing the length of data (in bytes) to write.
    @return The amount of data that was written. */
TgEXTN TgRSIZE
tgIDE_DBG_ERR_Write(
    STg2_Output_PC OUT0, TgRSIZE_C ARG1, TgVOID_CP ARG2, TgRSIZE_C ARG3 );

/** @brief Default output function used to write text through DebugOutput.
    @param [in,out] OUT0 Pointer to an output object that is used for writing.
    @param [in] ARG1 Integer representing the maximum amount of data to write.
    @param [in] ARG2 Pointer to the start of the memory to be written.
    @param [in] ARG3 Integer representing the length of data (in bytes) to write.
    @return The amount of data that was written. */
TgEXTN TgRSIZE
tgIDE_DBG_OUT_Write(
    STg2_Output_PC OUT0, TgRSIZE_C ARG1, TgVOID_CP ARG2, TgRSIZE_C ARG3 );

/** @} TGS_COMMON_BASE_TYPE_IO_DBG */


/* =============================================================================================================================================================================== */
#endif
