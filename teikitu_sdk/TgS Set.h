/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Set.h
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.12 | »GUID« 964CB1A6-814D-4E19-8E67-A83FCA98BF05 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_SET_H)
#define TGS_SET_H
#pragma once

#define TGS_PLATFORM_SET_H

#include "TgS SET/TgS Set - Constants.h"
#include "TgS SET/TgS Set - Type.h"


/* == Set ======================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Module Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @brief Standard Module function: First part of initialization process. Set the state of the module.
    @return Result Code. */
TgEXTN TgRESULT
tgSE_Module_Init( TgVOID );

/** @brief Standard Module function: Last part of initialization process. Used for setup and other necessary tasks prior to the use of the module.
    @return Result Code. */
TgEXTN TgRESULT
tgSE_Module_Boot( TgVOID );

/** @brief Standard Module function: Used for close the module as part of the shutdown process. Module is not to be used after this is executed. */
TgEXTN TgVOID
tgSE_Module_Stop( TgVOID );

/** @brief Standard Module function: Final part of shutdown process. Release any remaining allocated memory, and reset the state of the module. */
TgEXTN TgVOID
tgSE_Module_Free( TgVOID );

/** @brief Standard Module function: Update the module, usually called on a per-frame basis, where the parameter is the forward time step amount.
    @param[in] ARG0 Amount of time to step forward the module in milliseconds
    @return Result Code. */
TgEXTN TgRESULT
tgSE_Module_Update(
    TgFLOAT32_C ARG0 );


/** @brief Standard Module functions: Set the current configuration of the module. */
TgEXTN TgVOID
tgSE_Load_Config( TgVOID );

/** @brief Standard Module function: Save the current configuration of the module. */
TgEXTN TgVOID
tgSE_Save_Config( TgVOID );


/** @brief Standard Module function: State query to determine if the module is in the initialized or booted state
    @return True if the module has been initialized, and false otherwise. */
TgEXTN TgBOOL
tgSE_Query_Init( TgVOID );

/** @brief Standard Module function: State query to determine if the module has been booted state
    @return True if the module has been initialized and booted, and false otherwise. */
TgEXTN TgBOOL
tgSE_Query_Boot( TgVOID );

/** @brief Standard Module function: Recall the amount of global (static) memory used by the module
    @return Amount of global (static) memory used by the module. This is hard coded and thus, not explicitly correct. */
TgEXTN TgRSIZE
tgSE_Query_Fixed_Memory( TgVOID );


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  System Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgEXTN TgVOID
tgSE__Server__Build_Lists( TgVOID );

TgEXTN TgVOID
tgSE__Client__Build_Lists( TgVOID );

/* This call should be done before game processing.  This will create a small lag on the camera but given the decoupled nature of the render and game threads, it should */
/* not be significant.  During the call, the system will query the camera system for the current status of the render and debug cameras.  It will then store these off */
/* internally and will not be updated until the next game frame.  The render system may prefer to interpolate between the last frame and the current frame of the camera */
/* if its running at a higher frequency than the game thread. */

TgEXTN TgVOID
tgSE__Server__Update_Init(
    TgFLOAT32_C ARG0 );

TgEXTN TgVOID
tgSE__Server__Update_Simulation(
    TgFLOAT32_C ARG0 );

TgEXTN TgVOID
tgSE__Server__Update_Movement(
    TgFLOAT32_C ARG0 );



TgEXTN TgVOID
tgSE__Client__Update_Init(
    TgFLOAT32_C ARG0 );

TgEXTN TgVOID
tgSE__Client__Update_Simulation_Pre_Input(
    TgFLOAT32_C ARG0 );

TgEXTN TgVOID
tgSE__Client__Update_Movement_Pre_Input(
    TgFLOAT32_C ARG0 );

TgEXTN TgVOID
tgSE__Client__Update_Simulation_Post_Input(
    TgFLOAT32_C ARG0 );

TgEXTN TgVOID
tgSE__Client__Update_Movement_Post_Input(
    TgFLOAT32_C ARG0 );

/** @brief Called to update all animation information (key frame and rigs). Called once prior to player input, and called a second time after player input. The first call will
           update all objects that are not impacted (do not require) player input.
    @param [in] ARG0 Float-point time value. */
TgEXTN TgVOID
tgSE__Client__Update_Animation(
    TgFLOAT32_C ARG0 );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* This will push a collision query packet through the set.  This is the preferable method normally as it will allow the system to perform scene graph logic to restrict  */
/* the number of actual queries that need to be processed by the packet. The exception would be if the query is meant to be restricted to a small set of actors.  In that */
/* case hand-rolling your own logic to collect and then test just those objects would be faster due to the ability to ignore all rigid geometry, and the likelihood that  */
/* a simple LRU could exploit frame coherence. */

TgEXTN TgVOID                               tgSE_Init_Request( STg2_SE_CO_Request_F32_04_PCU ); /* #IMPLEMENT */
TgEXTN TgRESULT                             tgSE_Collide( STg2_SE_CO_Request_F32_04_PCU, ETgSE_CHANNEL_C ); /* #IMPLEMENT */


/* =============================================================================================================================================================================== */
#endif
