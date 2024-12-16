/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (WIN) Common - Global.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_WIN_COMMON_GLOBAL_H)
#define TGS_WIN_COMMON_GLOBAL_H
#pragma once

#include "TgS COMMON/TgS (WIN) Common - Base - Type.h"


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


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @brief Load a dynamic library (DLL).
    @param [out] OUT0 Pointer to a handle for the loaded library.
    @param [in] ARG1 Pointer to a string holding the filename for the library.
    @return True if the  library was successfully loaded, FALSE otherwise. */
TgEXTN TgBOOL
tgGB_Load_Lib(
    HINSTANCE *OUT0, TgOSCHAR_CPCU ARG1 );

/** @brief Release and free the library at the given handle.
    @param [out] OUT0 Pointer to a handle for the loaded library. */
TgEXTN TgVOID
tgGB_Free_Lib(
    HINSTANCE *OUT0 );

/** @brief Determine the function address (memory address) for a function in the library at the given handle.
    @param [out] OUT0 Pointer to the function.
    @param [in] ARG1 Handle for the loaded library.
    @param [in] ARG2 Pointer to a string holding the function name.
    @return True if the function was successfully found, FALSE otherwise. */
TgEXTN TgBOOL
tgGB_Get_Func_Address(
    FARPROC *OUT0, HINSTANCE ARG1, TgCHAR_NC_CPCU ARG2 );


/* =============================================================================================================================================================================== */
#endif
