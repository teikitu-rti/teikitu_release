/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Event MGR.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_EVENT_MGR_H)
#define TGS_COMMON_EVENT_MGR_H
#pragma once


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  DOXYGEN                                                                                                                                                                        */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @defgroup TGS_COMMON_EVENT_MGR Event Manager
    @ingroup TGS_COMMON_COMMON
*/

    /** @defgroup TGS_COMMON_EVENT_MGR_MODULE Module Functions
        @ingroup TGS_COMMON_EVENT_MGR
    */

    /** @defgroup TGS_COMMON_EVENT_MGR_FRAME Frame Based Events
        @ingroup TGS_COMMON_EVENT_MGR
    */

    /** @defgroup TGS_COMMON_EVENT_MGR_TIME Time Based Events
        @ingroup TGS_COMMON_EVENT_MGR
    */


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Types                                                                                                                                                                   */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

typedef TgVOID( *TgFCN_EM_CALLBACK )(TgUINT_PTR_C);


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @addtogroup TGS_COMMON_EVENT_MGR_MODULE */
/** @{ */

/** @brief Standard Module function: First part of initialization process. Set the state of the module.
    @return Result Code. */
TgEXTN TgRESULT
tgEM_Init_MGR( TgVOID );

/** @brief Standard Module function: Last part of initialization process. Used for setup and other necessary tasks prior to the use of the module.
    @return Result Code. */
TgEXTN TgRESULT
tgEM_Boot_MGR( TgVOID );

/** @brief Standard Module function: Used for close the module as part of the shutdown process. Module is not to be used after this is executed.
    @return Result Code. */
TgEXTN TgRESULT
tgEM_Stop_MGR( TgVOID );

/** @brief Standard Module function: Final part of shutdown process. Release any remaining allocated memory, and reset the state of the module.
    @return Result Code. */
TgEXTN TgRESULT
tgEM_Free_MGR( TgVOID );

/** @brief Standard Module function: Update the module, usually called on a per-frame basis, where the parameter is the forward time step amount.
    @param[in] ARG0 Amount of time to step forward the module in milliseconds
    @return Result Code. */
TgEXTN TgRESULT
tgEM_Update_MGR(
    TgFLOAT32_C ARG0 );

/** @brief Accessor-Get returning the completion status of the event manager. 
    @return True if the manager has completed the update process triggered from the most recent call to tgEM_Update_MGR, and false otherwise. */
TgEXTN TgBOOL
tgEM_Update_MGR_Is_Complete( TgVOID );

/** @brief Standard Module function: State query to determine if the module is in the initialized or booted state
    @return True if the module has been initialized, and false otherwise. */
TgEXTN TgBOOL
tgEM_Query_Init( TgVOID );

/** @brief Standard Module function: State query to determine if the module has been booted state
    @return True if the module has been initialized and booted, and false otherwise. */
TgEXTN TgBOOL
tgEM_Query_Boot( TgVOID );

/** @brief Standard Module function: Recall the amount of global (static) memory used by the module
    @return Amount of global (static) memory used by the module. This is hard coded and thus, not explicitly correct. */
TgEXTN TgRSIZE
tgEM_Query_Fixed_Memory( TgVOID );

#if TgS_STAT__COMMON

/** @brief Standard Module function: Output relevant stats for the module.
    @param [in,out] OUT0 Pointer to an output object */
TgEXTN TgVOID
tgEM_Stats(
    STg2_Output_P OUT0 );

#endif

/** @} TGS_COMMON_EVENT_MGR_MODULE */


/** @addtogroup TGS_COMMON_EVENT_MGR */
/** @{ */

/** @brief Set the pause state for the Event Manager
    @param [in] ARG Boolean Flag */
TgEXTN TgVOID
tgEM_Set_Pause(
    TgBOOL_C ARG );

/** @brief Return the pause state for the Event Manager
    @return True if the Event Manager is currently paused, and false otherwise */
TgEXTN TgBOOL
tgEM_Query_Pause( TgVOID );

/** @} TGS_COMMON_EVENT_MGR */


/* ---- Time Event - Frame ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/** @addtogroup TGS_COMMON_EVENT_MGR_FRAME */
/** @{ */

/** @brief Create a new event based on frame counts with the given parameters
    @param [in] ARG0 The function to call when event is triggered
    @param [in] ARG1 Function parameter to use when called
    @param [in] ARG2 Start Frame for the Event
    @param [in] ARG3 End Frame for the Event
    @return Event identifier on success, and false otherwise */
TgEXTN TgEM_TE_FRM_ID
tgEM_TE_FRM_NEW(
    TgFCN_EM_CALLBACK ARG0, TgUINT_PTR_C ARG1, TgSINT_E32_C ARG2, TgSINT_E32_C ARG3 );

/** @brief Delete the given Event
    @param [in] ARG Event Identifier */
TgEXTN TgRESULT
tgEM_TE_FRM_DEL(
    TgEM_TE_FRM_ID ARG );

/** @brief Set the pause state for the given event
    @param [in] ARG0 Event Identifier
    @param [in] ARG1 Boolean Flag
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
tgEM_TE_FRM_Set_Pause(
    TgEM_TE_FRM_ID ARG0, TgBOOL_C ARG1 );

/** @brief Set the start frame for the given event
    @param [in] ARG0 Event Identifier
    @param [in] ARG1 Start Frame
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
tgEM_TE_FRM_Set_Start_Frame(
    TgEM_TE_FRM_ID ARG0, TgSINT_E32_C ARG1 );

/** @brief Set the end frame for the given event
    @param [in] ARG0 Event Identifier
    @param [in] ARG1 End Frame
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
tgEM_TE_FRM_Set_End_Frame(
    TgEM_TE_FRM_ID ARG0, TgSINT_E32_C ARG1 );

/** @brief Alternative to setting the end frame for the Event, where it is set to be ARG1 frames from the current total
    @param [in] ARG0 Event Identifier
    @param [in] ARG1 Number of Frames from now before terminating the Event
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
tgEM_TE_FRM_Set_Frame_To_Live(
    TgEM_TE_FRM_ID ARG0, TgSINT_E32_C ARG1 );


/** @brief Return true if the ARG Event Identifier is valid and associated with a valid Event
    @param [in] ARG Event Identifier
    @return True if the identifier and Event are valid, and false otherwise */
TgEXTN TgBOOL
tgEM_TE_FRM_Query_Valid(
    TgEM_TE_FRM_ID ARG );

/** @brief Store the pause state of the Event
    @param [out] OUT0 Destination to hold the pause state of the
    @param [in] ARG1 Event Identifier
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
tgEM_TE_FRM_Query_Paused(
    TgBOOL_PCU OUT0, TgEM_TE_FRM_ID ARG1 );

/** @brief Store the frame number to start the Event
    @param [out] OUT0 Destination to hold the start frame for the Event
    @param [in] ARG1 Event Identifier
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
tgEM_TE_FRM_Query_Start_Frame(
    TgSINT_E32_PCU OUT0, TgEM_TE_FRM_ID ARG1 );

/** @brief Store the frame number to end the Event
    @param [out] OUT0 Destination to hold the end frame of the Event
    @param [in] ARG1 Event Identifier
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
tgEM_TE_FRM_Query_End_Frame(
    TgSINT_E32_PCU OUT0, TgEM_TE_FRM_ID ARG1 );

/** @brief Store the number of frames until the Event ends
    @param [out] OUT0 Destination to hold the number of frames until the Event ends
    @param [in] ARG1 Event Identifier
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
tgEM_TE_FRM_Query_Frame_To_Live(
    TgSINT_E32_PCU OUT0, TgEM_TE_FRM_ID ARG1 );

/** @} TGS_COMMON_EVENT_MGR_FRAME */


/* ---- Time Event - Time -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/** @addtogroup TGS_COMMON_EVENT_MGR_TIME */
/** @{ */

/** @brief Create a new event based on time with the given parameters
    @param [in] ARG0 The function to call when event is triggered
    @param [in] ARG1 Function parameter to use when called
    @param [in] ARG2 Starting time for the Event
    @param [in] ARG3 End time for the Event
    @return Event identifier on success, and false otherwise */
TgEXTN TgEM_TE_SEC_ID
tgEM_TE_SEC_NEW(
    TgFCN_EM_CALLBACK ARG0, TgUINT_PTR_C ARG1, TgFLOAT32_C ARG2, TgFLOAT32_C ARG3 );

/** @brief Delete the given Event
    @param [in] ARG Event Identifier */
TgEXTN TgRESULT
tgEM_TE_SEC_DEL(
    TgEM_TE_SEC_ID ARG );


/** @brief Set the pause state for the given event
    @param [in] ARG0 Event Identifier
    @param [in] ARG1 Boolean Flag
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
tgEM_TE_SEC_Set_Pause(
    TgEM_TE_SEC_ID ARG0, TgBOOL_C ARG1 );

/** @brief Set the starting time for the given event
    @param [in] ARG0 Event Identifier
    @param [in] ARG1 Start time (time in milliseconds)
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
tgEM_TE_SEC_Set_Start_Time(
    TgEM_TE_SEC_ID ARG0, TgFLOAT32_C ARG1 );

/** @brief Set the end time for the given event
    @param [in] ARG0 Event Identifier
    @param [in] ARG1 End time (time in milliseconds)
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
tgEM_TE_SEC_Set_End_Time(
    TgEM_TE_SEC_ID ARG0, TgFLOAT32_C ARG1 );

/** @brief Alternative to setting the end time for the Event, where it is set to be ARG1 milliseconds from the current time
    @param [in] ARG0 Event Identifier
    @param [in] ARG1 Number of milliseconds from now before ending the Event
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
tgEM_TE_SEC_Set_Time_To_Live(
    TgEM_TE_SEC_ID ARG0, TgFLOAT32_C ARG1 );


/** @brief Return true if the ARG Event Identifier is valid and associated with a valid Event
    @param [in] ARG Event Identifier
    @return True if the identifier and Event are valid, and false otherwise */
TgEXTN TgBOOL
tgEM_TE_SEC_Query_Valid(
    TgEM_TE_SEC_ID ARG );

/** @brief Store the pause state for the Event
    @param [out] OUT0 Destination to hold the pause state for the Event
    @param [in] ARG1 Event Identifier
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
tgEM_TE_SEC_Query_Paused(
    TgBOOL_PCU OUT0, TgEM_TE_SEC_ID ARG1 );

/** @brief Store the start time of the Event
    @param [out] OUT0 Destination to hold the start time of the Event
    @param [in] ARG1 Event Identifier
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
tgEM_TE_SEC_Query_Start_Time(
    TgFLOAT32_PCU OUT0, TgEM_TE_SEC_ID ARG1 );

/** @brief Store the end time of the Event
    @param [out] OUT0 Destination to hold the end time of the Event
    @param [in] ARG1 Event Identifier
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
tgEM_TE_SEC_Query_End_Time(
    TgFLOAT32_PCU OUT0, TgEM_TE_SEC_ID ARG1 );

/** @brief Store the number of milliseconds until the Event ends
    @param [out] OUT0 Destination to hold the number of milliseconds until the Event ends
    @param [in] ARG1 Event Identifier
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
tgEM_TE_SEC_Query_Time_To_Live(
    TgFLOAT32_PCU OUT0, TgEM_TE_SEC_ID ARG1);

/** @} TGS_COMMON_EVENT_MGR_TIME */


/* =============================================================================================================================================================================== */
#endif
