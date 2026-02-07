/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Base - API [Thread].h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_BASE_API_THREAD_H)
#define TGS_COMMON_BASE_API_THREAD_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif


/* == Common ===================================================================================================================================================================== */
/* MARK: Unit Test Complete 00D008E0-5616-4AAF-8989-24865B450F52                                                                                                                   */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  DOXYGEN                                                                                                                                                                        */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @defgroup TGS_COMMON_BASE_API_PLATFORM_THREAD Thread Functions
    @ingroup TGS_COMMON
*/


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- Thread ------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/** @addtogroup TGS_COMMON_BASE_API_PLATFORM_THREAD */
/** @{ */

#if TgCOMPILE__THREAD
/** @brief Used to create and execute the main thread for the system*/
/** @param [in] ARG Name for the thread given to the operating system */
TgEXTN TgTHREAD_ID
tgTR_Register_Main_Thread(
    TgCHAR_U8_CPC ARG );

/** @brief Platform agnostic method to create a new thread
    @param [in] ARG0 Platform specific thread function
    @param [in] ARG1 Thread function parameter
    @param [in] ARG2 Stack Size
    @param [in] ARG3 Thread priority.  By default this should be normal
    @param [in] ARG4 Thread name - used for debugging purposes. */
TgEXTN TgTHREAD_ID
tgTR_Create(
    TgPLATFORM_THREAD_FCN ARG0, TgUINT_PTR_C ARG1, TgUINT_E32_C ARG2, ETgTHREAD_PRIORITY_C ARG3, TgCHAR_U8_CPC ARG4 );

/** @return The unique thread identifier for the current executing thread */
TgEXTN TgTHREAD_ID
tgTR_Query_Id( TgVOID );

/** @brief Joins the thread indicated by ARG and waits for it to terminate
    @param [in] ARG Unique identifier for a specific thread */
TgEXTN TgVOID
tgTR_Close( TgTHREAD_ID ARG );

/** @return The status of the thread
    @param [in] ARG Unique identifier for a specific thread */
TgEXTN ETgTHREAD_STATUS
tgTR_Status(
    TgTHREAD_ID ARG );


/** @return The size of the thread stack. MAX is uninitialized and MAX-1 is used during initialization of the thread */
TgEXTN TgRSIZE
tgTR_Stack_Size( TgVOID );

/** @brief Prints out all threads that have been created through the platform manager
    @param [in] ARG Pointer to an output stream */
TgEXTN TgVOID
tgTR_Print_Threads(
    STg2_Output_P ARG );

/*# TgCOMPILE__THREAD */
#endif
/** @brief Yields the remaining time slice back to the scheduler but does not guarantee that a new thread will execute next. */
TgEXTN TgVOID
tgTR_Yield( TgVOID );

/** @brief Cpu instruction meant to be used for spin loops */
TgEXTN TgVOID
tgTR_Pause( TgVOID );

/** @brief Place the thread to sleep for ARG number of nanoseconds*/
/** @param [in] ARG Nanoseconds */
TgEXTN TgVOID
tgTR_Sleep(
    TgUINT_E32_C ARG );

/** @} TGS_COMMON_BASE_API_PLATFORM_THREAD */


/* =============================================================================================================================================================================== */
#endif
