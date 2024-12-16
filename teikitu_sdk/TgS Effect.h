/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Effect.h
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.20 | »GUID« DE461472-5528-4A5B-A7F4-09CCAD73387B */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_EFFECT_H)
#define TGS_EFFECT_H
#pragma once

#include "TgS EFFECT/TgS Effect - Constants.h"
#include "TgS EFFECT/TgS Effect - Type.h"
#include "TgS EFFECT/TgS Effect - Data.h"


/* == Effect ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Module Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/** @brief Standard Module function: First part of initialization process. Set the state of the module.
    @return Result Code. */
TgEXTN TgRESULT
tgFX_Module_Init( TgVOID );

/** @brief Standard Module function: Last part of initialization process. Used for setup and other necessary tasks prior to the use of the module.
    @return Result Code. */
TgEXTN TgRESULT
tgFX_Module_Boot( TgVOID );

/** @brief Standard Module function: Used for close the module as part of the shutdown process. Module is not to be used after this is executed. */
TgEXTN TgVOID
tgFX_Module_Stop( TgVOID );

/** @brief Standard Module function: Final part of shutdown process. Release any remaining allocated memory, and reset the state of the module. */
TgEXTN TgVOID
tgFX_Module_Free( TgVOID );

/** @brief Standard Module function: Update the module, usually called on a per-frame basis, where the parameter is the forward time step amount.
    @param [in] ARG0 Amount of time to step forward the module in milliseconds
    @return Result Code. */
TgEXTN TgRESULT
tgFX_Module_Update(
    TgFLOAT32_C ARG0 ); /* Client Only */


/** @brief Standard Module functions: Set the current configuration of the module. */
TgEXTN TgRESULT
tgFX_Load_Config( TgVOID );

/** @brief Standard Module function: Save the current configuration of the module. */
TgEXTN TgRESULT
tgFX_Save_Config( TgVOID );


/** @brief Standard Module function: State query to determine if the module is in the initialized or booted state
    @return True if the module has been initialized, and false otherwise. */
TgEXTN TgBOOL
tgFX_Query_Init( TgVOID );

/** @brief Standard Module function: State query to determine if the module has been booted state
    @return True if the module has been initialized and booted, and false otherwise. */
TgEXTN TgBOOL
tgFX_Query_Boot( TgVOID );

/** @brief Standard Module function: Recall the amount of global (static) memory used by the module
    @return Amount of global (static) memory used by the module. This is hard coded and thus, not explicitly correct. */
TgEXTN TgRSIZE
tgFX_Query_Fixed_Memory( TgVOID );


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Effect Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* -- Effect - Management -------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgEXTN TgRESULT
tgFX__Client__Is_Loaded(
    TgFX_EFFECT_ID_C );

TgEXTN TgRESULT
tgFX__Client__PreLoad(
    TgFX_EFFECT_ID_C ); /* Pre-load any external resources needed by the effect */


TgEXTN TgFX_EFFECT_ID
tgFX__Client__Query_Id(
    TgUINT_MAX_C  );


/* -- Effect - Instance Management ----------------------------------------------------------------------------------------------------------------------------------------------- */

/** @brief Create a FX instance using a pointer to a raw data effect blob.
    @param [in] ARG0 Enumeration of the effect type that matches the following data blob.
    @param [in] ARG1 Pointer to a data blob for the required file data.  Pointer data must be valid for lifetime of all instances.
    @param [in] ARG2 Pointer to a data blob for the required file data.  Pointer data must be valid for lifetime of all instances.
    @param [in] ARG3 Pointer to an FX Instance data structure.
    @param [in] ARG4 Boolean to indicate if an error effect should be use on failure, or have the function fail. 
    @return UID for the FX to be used by the client. */
TgEXTN TgFX_CLIENT_INST_ID
tgFX__Client__Inst_FX_RAW(
    ETgFX__EFFECT_C ARG0, TgVOID_CP TgANALYSIS_NO_NULL ARG1, TgVOID_CP OKNULL ARG2, STg2_FX_Instance_CPCU TgANALYSIS_NO_NULL ARG3, TgBOOL_C ARG4 );

/** @brief Create a FX instance using a pointer to a raw data effect blob.
    @param [in] ARG0 Hash of the unique name (key) for this effect.
    @param [in] ARG1 Pointer to an FX Instance data structure.
    @param [in] ARG2 Boolean to indicate if an error effect should be use on failure, or have the function fail. 
    @return UID for the FX to be used by the client. */
TgEXTN TgFX_CLIENT_INST_ID
tgFX__Client__Inst_FX_Hash(
    TgUINT_MAX_C ARG0, STg2_FX_Instance_CPCU TgANALYSIS_NO_NULL ARG1, TgBOOL_C ARG2 );

/** @brief Create a FX instance using a pointer to a raw data effect blob.
    @param [in] ARG0 UID for the FX data to be used for this instance.
    @param [in] ARG1 Pointer to an FX Instance data structure.
    @param [in] ARG2 Boolean to indicate if an error effect should be use on failure, or have the function fail. 
    @return UID for the FX to be used by the client. */
TgEXTN TgFX_CLIENT_INST_ID
tgFX__Client__Inst_FX(
    TgFX_EFFECT_ID_C ARG0, STg2_FX_Instance_CPCU TgANALYSIS_NO_NULL ARG1, TgBOOL_C ARG2 );


/** @brief Issue a command to gracefully stop the effect (fade out etc.). */
TgEXTN TgVOID
tgFX__Client__Stop(
    TgFX_CLIENT_INST_ID_C ARG0 );

/** @brief Issues a command to remove the effect immediately. */
TgEXTN TgVOID
tgFX__Client__Kill(
    TgFX_CLIENT_INST_ID_C ARG0 );

/** @brief Issues a command to remove all effects immediately. */
TgEXTN TgVOID
tgFX__Client__Kill_All(
    TgUINT_E32_P ARG0 );

TgEXTN TgVOID
tgFX__Client__Set_Position_From_External_Update(
    TgFX_CLIENT_INST_ID_C, TgVEC_F32_04_1 );

/* -- Effect Instance - Accessors ------------------------------------------------------------------------------------------------------------------------------------------------ */

TgEXTN TgVOID
tgFX__Client__Set_Callback_Terminate(
    TgFX_CLIENT_INST_ID_C ARG0, TgFCN_CB_ON_TERMINATE OKNULL ARG1, TgUINT_PTR_C ARG2 );

TgEXTN TgVOID
tgFX__Client__Set_Callback_Contact(
    TgFX_CLIENT_INST_ID_C ARG0, TgFCN_CB_ON_CONTACT OKNULL ARG1, TgUINT_PTR_C ARG2 );

TgEXTN TgVOID
tgFX__Client__Set_Visible(
    TgFX_CLIENT_INST_ID_C ARG0, TgBOOL_C ARG1 );


TgEXTN TgBOOL
tgFX__Client__Is_Attached(
    TgFX_CLIENT_INST_ID_C ARG0 );

TgEXTN TgRESULT
tgFX__Client__Is_Valid(
    TgFX_CLIENT_INST_ID_C ARG0 );


/* -- System --------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* For details on this synchronization and memory ownership model, see the internal header file. */

/** @brief First update for the FX system, which updates all independent running FX entities. Though it would produce a less accurate result, it is possible to run this at a lower
           frequency than the frame rate, and have the render generation functions interpolate between frames.
    @param [in] ARG0 Floating-point time step value. */
TgEXTN TgVOID
tgFX__Client__Update_1(
    TgFLOAT32_C ARG0 );

/** @brief Second update for the FX system, which updates all FX entities that are dependent (position) on other objects in the frame. This needs to run at the same frequency as
           the update frequency of the dependent geometry. For example, an effect attached to an animating character needs to update every time after character animation.
    @param [in] ARG0 Floating-point time step value. */
TgEXTN TgVOID
tgFX__Client__Update_2(
    TgFLOAT32_C ARG0 );

/** @brief This is the final step in the update process, and one of the key points of synchronization. At this point, the commands that were sent during client update(s) are
           processed and committed, and new effects are created. When executed as a job, on a per effect-type basis, they will not execute until both updates are completed. */
TgEXTN TgVOID
tgFX__Client__Update_Finish( TgVOID );

/** @brief Wait for all of the update jobs to be completed. */
TgEXTN TgVOID
tgFX__Client__Wait_For_Update_Completion( TgVOID );

#if defined(TgBUILD_FEATURE__GRAPHICS)

/** @brief Based on the view index, select all effects that are in the draw frustum and add them as render frame instances to be drawn during rendering. When executed as a job, on
           a per effect-type basis, it will not execute until update finish is complete. Concurrently and with the same restriction, a job will execute to update the bounding
           boxes stored for access by the client. A third job will be queued to run once all culling is complete on a per-effect type basis that is responsible for adding frame
           mesh entities into the render scene (for the view index) when they are non-particle (i.e. full mesh entities).
    @param [in,out] ARG0 Pointer to a Set scene context for processing.
    @param [in] ARG1 Integer selecting the view index to be processed. */
TgEXTN TgVOID
tgFX__Client__Scene_Cull(
    STg2_SE_Context_PC TgANALYSIS_NO_NULL ARG0, TgRSIZE_C ARG1 );

/** @brief This function is responsible for executing (or queuing) two jobs. The first establishes all of the FX headers that will be used during rendering to the draw the FX
           vertex buffers based on the FX that passed culling. The second job is to generate the data for these vertex buffers. Once completed the FX system has completed its
           work for the render frame and a new update pass can start.
    @param [in,out] ARG0 Pointer to a FX rendering data structure that is used to contain the results of the FX render generation data. */
TgEXTN TgVOID
tgFX__Render__Update(
    STg2_FX_Rnd_Output_PC TgANALYSIS_NO_NULL ARG0 );

/** @brief Wait for all of the render jobs to be completed. */
TgEXTN TgVOID
tgFX__Client__Wait_For_Render_Completion( TgVOID );

/*# defined(TgBUILD_FEATURE__GRAPHICS) */
#endif


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Debug and Tools                                                                                                                                                                */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
#if TgS_DEBUG__EFFECT

TgEXTN TgRESULT
tgFX_Debug__Client__Reload_Effect(
    TgFX_EFFECT_ID_C ARG0, STg2_Input_CPC TgANALYSIS_NO_NULL ARG1, TgUINT_PTR_C ARG2, TgVOID(*)( TgUINT_PTR_C, TgFX_EFFECT_ID_C) );

TgEXTN TgCHAR_U8_CP
tgFX_Debug__Client__Query_FX_Name(
    TgFX_EFFECT_ID_C ARG0 );

TgEXTN TgBOOL
tgFX_Debug__Is_Valid(
    TgFX_CLIENT_INST_ID_C ARG0, TgFX_DATA_INST_ID_C ARG1 );

/*# TgS_DEBUG__EFFECT */
#endif


/* =============================================================================================================================================================================== */
#endif
