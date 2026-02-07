/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Input.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_INPUT_H)
#define TGS_INPUT_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "TgS INPUT/TgS Input - Constants.h"
#include "TgS INPUT/TgS Input - Type.h"


/* == Input ====================================================================================================================================================================== */

/* The Input Module can be best described as a chain of responsibility and a producer-consumer pattern.  Input devices act as producers, while the receiver stack acts collectively
   as the consumer. */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Module Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/** @brief Standard Module function: First part of initialization process. Set the state of the module.
    @return Result Code. */
TgEXTN TgRESULT
tgIN_Module_Init( TgVOID );

/** @brief Standard Module function: Last part of initialization process. Used for setup and other necessary tasks prior to the use of the module.
    @return Result Code. */
TgEXTN TgRESULT
tgIN_Module_Boot( TgVOID );

/** @brief Standard Module function: Used for close the module as part of the shutdown process. Module is not to be used after this is executed. */
TgEXTN TgVOID
tgIN_Module_Stop( TgVOID );

/** @brief Standard Module function: Final part of shutdown process. Release any remaining allocated memory, and reset the state of the module. */
TgEXTN TgVOID
tgIN_Module_Free( TgVOID );

/** @brief Standard Module function: Update the module, usually called on a per-frame basis, where the parameter is the forward time step amount.
    @param[in] ARG0 Amount of time to step forward the module in milliseconds
    @return Result Code. */
TgEXTN TgRESULT
tgIN_Module_Update(
    TgFLOAT32_C ARG0 );


/** @brief Standard Module functions: Set the current configuration of the module. */
TgEXTN TgVOID
tgIN_Load_Config( TgVOID );

/** @brief Standard Module function: Save the current configuration of the module. */
TgEXTN TgVOID
tgIN_Save_Config( TgVOID );


/** @brief Standard Module function: State query to determine if the module is in the initialized or booted state.
    @return True if the module has been initialized, and false otherwise. */
TgEXTN TgBOOL
tgIN_Query_Init( TgVOID );

/** @brief Standard Module function: State query to determine if the module has been booted state.
    @return True if the module has been initialized and booted, and false otherwise. */
TgEXTN TgBOOL
tgIN_Query_Boot( TgVOID );

/** @brief Standard Module function: Recall the amount of global (static) memory used by the module.
    @return Amount of global (static) memory used by the module. This is hard coded and thus, not explicitly correct. */
TgEXTN TgRSIZE
tgIN_Query_Fixed_Memory( TgVOID );


#if TgS_STAT__INPUT
/** @brief Standard Module function: Output relevant stats for the module.
    @param [in,out] OUT0 Pointer to an output object. */
TgEXTN TgVOID
tgIN_Stats(
    STg2_Output_P OUT0 );
#endif


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Input Functions                                                                                                                                                                */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/** @brief Samples the input hardware and updates all consumers.
    @param[in] ARG0 Amount of time to step forward the module in milliseconds. */
TgEXTN TgVOID
tgIN_Update__Client(
    TgFLOAT32_C ARG0 );


/** @brief Add an input consumer (processing function) to the given input controller (device).
    @param[in] ARG0 Enumeration indicating the controller selected.
    @param[in] ARG1 Pointer to a function responsible for input generation (producer).
    @param[in] ARG2 Integer passed to the ARG1 function when called.
    @return Return Code. */
TgEXTN TgRESULT
tgIN_Set_Producer(
    ETgCONTROLLER_C ARG0, TgIN_FCN_PRODUCER ARG1, TgUINT_PTR_C ARG2 );

/** @brief Determine if a given device has a producer bound to it.
    @param[in] ARG0 Enumeration indicating the controller selected.
    @return True when there is a function bound to the controller, and false otherwise. */
TgEXTN TgBOOL
tgIN_Has_Producer(
    ETgCONTROLLER_C ARG0 );

/** @brief Update all the producers.  Normally done asynchronously (e.g. on vblank). The system assumes that only a single thread is responsible for pumping the production queue. */
TgEXTN TgVOID
tgIN_Update_Producers( TgVOID );


/** @brief Add an input consumer (processing function) to the given input controller (device).
    @param[in] ARG0 Enumeration indicating the controller selected.
    @param[in] ARG1 Integer indicating the priority of the processing function.
    @param[in] ARG2 Pointer to a function responsible for input processing (consumer).
    @param[in] ARG3 Integer passed to the ARG2 function when called.
    @return UID for the Consumer function on success, or the Invalid ID otherwise. */
TgEXTN TgIN_CONSUMER_ID
tgIN_Insert_Consumer(
    ETgCONTROLLER_C ARG0, TgUINT_E32_C ARG1, TgIN_FCN_CONSUMER ARG2, TgUINT_PTR_C ARG3 );

/** @brief Remove the consumer identified by the UID.
    @param[in] ARG0 UID that was returned when the consumer was added to the system.
    @return Return Code. */
TgEXTN TgRESULT
tgIN_Remove_Consumer(
    TgIN_CONSUMER_ID_C ARG0 );


/** @brief Attempt to set the execution state of the producer bound to a specific controller (device).
    @param[in] ARG0 Enumeration indicating the controller selected.
    @param[in] ARG1 Boolean where true will pause input generation for the controller, and false otherwise.
    @return True if the pause state is correctly set (or did not need to be changed), and false otherwise. */
TgEXTN TgBOOL
tgIN_Pause_Controller(
    ETgCONTROLLER_C ARG0, TgBOOL_C ARG1 );

/** @brief Set the execution state of the module and associated threads.
    @param[in] ARG0 Boolean where true will pause execution of the module, and false otherwise. */
TgEXTN TgVOID
tgIN_Pause_Input(
    TgBOOL_C ARG0 );


/** @brief Set the default for a given Dead Zone.
    @param[in] ARG0 Enumeration indicating the dead zone selected.
    @param[in] ARG1 Float value that is set. */
TgEXTN TgVOID
tgIN_Set_Default_Dead_Zone(
    ETgDEAD_ZONE_C ARG0, TgFLOAT32_C ARG1 );

/** @brief Set Dead Zone for a specific controller.
    @param[in] ARG0 Enumeration indicating the controller selected.
    @param[in] ARG1 Enumeration indicating the dead zone selected.
    @param[in] ARG2 Float value that is set. */
TgEXTN TgVOID
tgIN_Set_Dead_Zone(
    ETgCONTROLLER_C ARG0, ETgDEAD_ZONE_C ARG1, TgFLOAT32_C ARG2 );

/** @brief Query the default for a given Dead Zone.
    @param[in] ARG0 Enumeration indicating the dead zone selected.
    @return Float value for the selected dead zone, and zero otherwise. */
TgEXTN TgFLOAT32
tgIN_Query_Default_Dead_Zone(
    ETgDEAD_ZONE_C ARG0 );

/** @brief Query Dead Zone for a specific controller.
    @param[in] ARG0 Enumeration indicating the controller selected.
    @param[in] ARG1 Enumeration indicating the dead zone selected.
    @return Float value for the selected dead zone, and zero otherwise. */
TgEXTN TgFLOAT32
tgIN_Query_Dead_Zone(
    ETgCONTROLLER_C ARG0, ETgDEAD_ZONE_C ARG1 );


/** @brief Set the rumble values for a given controller.
    @param[in] ARG0 Enumeration indicating the controller selected.
    @param[in] ARG1 Float value indicating rumble strength on the left.
    @param[in] ARG2 Float value indicating rumble strength on the right.
    @return Return Code. */
TgEXTN TgRESULT
tgIN_Set_Rumble(
    ETgCONTROLLER_C ARG0, TgFLOAT32_C ARG1, TgFLOAT32_C ARG2 );

#if TgS_STAT__INPUT
/** @brief Report the total number of insertions executed.
    @return Integer count of the total number of insertions executed. */
TgEXTN TgUINT_E32
tgIN_Stat_Query_Total_Insert( TgVOID );

/** @brief Report the total number of removals executed.
    @return Integer count of the total number of removals executed. */
TgEXTN TgUINT_E32
tgIN_Stat_Query_Total_Remove( TgVOID );
/*# TgS_STAT__INPUT */
#endif 


/* ---- Rumble Manager ----------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgEXTN TgVOID
tgRB_Update( TgVOID ); /* #TODO: IMPLEMENT */

TgEXTN TgVOID
tgRB_Set_Rumble_Timer(
    ETgCONTROLLER_C ARG0, TgFLOAT32_C ARG1 ); /* #TODO: IMPLEMENT */

TgEXTN TgVOID
tgRB_Set_Rumble_Interval(
    ETgCONTROLLER_C ARG0, TgFLOAT32_C ARG1 ); /* #TODO: IMPLEMENT */

TgEXTN TgFLOAT32
tgRB_Query_Rumble_Timer(
    ETgCONTROLLER_C ARG0 ); /* #TODO: IMPLEMENT */

TgEXTN TgFLOAT32
tgRB_Query_Rumble_Interval(
    ETgCONTROLLER_C ARG0 ); /* #TODO: IMPLEMENT */

TgEXTN TgBOOL
tgRB_Is_In_Rumble(
    ETgCONTROLLER_C ARG0 ); /* #TODO: IMPLEMENT */


/* =============================================================================================================================================================================== */
#endif
