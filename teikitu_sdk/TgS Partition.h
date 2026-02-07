/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Partition.h
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.12 | »GUID« 964CB1A6-814D-4E19-8E67-A83FCA98BF05 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_PARTITION_H)
#define TGS_PARTITION_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#define TGS_PLATFORM_PARTITION_H

#include "TgS PARTITION/TgS Partition - Constants.h"
#include "TgS PARTITION/TgS Partition - Type.h"
#include "TgS PARTITION/TgS Partition - Data.h"


/* == Partition ================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Module Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/** @addtogroup TGS_PARTITION_MODULE */
/** @{ */

/** @brief Standard Module function: First part of initialization process. Set the state of the module.
    @return Result Code. */
TgEXTN TgRESULT
tgPA_Module_Init( TgVOID );

/** @brief Standard Module function: Last part of initialization process. Used for setup and other necessary tasks prior to the use of the module.
    @return Result Code. */
TgEXTN TgRESULT
tgPA_Module_Boot( TgVOID );

/** @brief Standard Module function: Used for close the module as part of the shutdown process. Module is not to be used after this is executed. */
TgEXTN TgVOID
tgPA_Module_Stop( TgVOID );

/** @brief Standard Module function: Final part of shutdown process. Release any remaining allocated memory, and reset the state of the module. */
TgEXTN TgVOID
tgPA_Module_Free( TgVOID );

/** @brief Standard Module function: Update the module, usually called on a per-frame basis, where the parameter is the forward time step amount. @return Result Code.
    @param[in] ARG0 Amount of time to step forward the module in milliseconds. */
TgEXTN TgRESULT
tgPA_Module_Update(
    TgFLOAT32_C ARG0 );


/** @brief Standard Module functions: Set the current configuration of the module. */
TgEXTN TgVOID
tgPA_Load_Config( TgVOID );

/** @brief Standard Module function: Save the current configuration of the module. */
TgEXTN TgVOID
tgPA_Save_Config( TgVOID );


/** @brief Standard Module function: State query to determine if the module is in the initialized or booted state
    @return True if the module has been initialized, and false otherwise. */
TgEXTN TgBOOL
tgPA_Query_Init( TgVOID );

/** @brief Standard Module function: State query to determine if the module has been booted state
    @return True if the module has been initialized and booted, and false otherwise. */
TgEXTN TgBOOL
tgPA_Query_Boot( TgVOID );

/** @brief Standard Module function: Recall the amount of global (static) memory used by the module
    @return Amount of global (static) memory used by the module. This is hard coded and thus, not explicitly correct. */
TgEXTN TgRSIZE
tgPA_Query_Fixed_Memory( TgVOID );

/** @} TGS_PARTITION_MODULE */


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/** @addtogroup TGS_PARTITION_SYSTEM */
/** @{ */

/** @brief Insert a bounding box into the Partition Graph. @return Result Code.
    @param [out] OUT0 Pointer to a Parition Object ID to hold the result of the function.
    @param [in] ARG1 UID for the Partition Manager to be used.
    @param [in] ARG2 Integer user data field.
    @param [in] ARG3 Integer category field.
    @param [in] ARG4 Integer collide bitmask.
    @param [in] ARG5 Pointer to axis aligned bounding box to be added to the manager. */
TgEXTN TgRESULT
tgPA_Graph_Insert_Object(
    TgPARTITION_OBJECT_ID_PC TgANALYSIS_NO_NULL OUT0, TgPARTITION_GRAPH_ID_C ARG1, TgUINT_PTR_C ARG2, TgUINT_E64_C ARG3, TgUINT_E64_C ARG4,
    TgBOXAA_F32_04_CPC TgANALYSIS_NO_NULL ARG5 );

/** @brief Remove an object from a Partition Graph. @return Result Code.
    @param [in] ARG0 UID for the Partition Manager to be used.
    @param [in] ARG1 Unique identifier for the object. */
TgEXTN TgRESULT
tgPA_Graph_Remove_Object(
    TgPARTITION_GRAPH_ID_C ARG0, TgPARTITION_OBJECT_ID_C ARG1 );

/** @brief Test an Axis Aligned Bounding Box for contact in the Partition Graph. @return Result Code.
    @param [out] OUT0 Pointer to boolean value to hold the result of the function.
    @param [in] ARG1 UID for the Partition Manager to be used.
    @param [in] ARG2 Integer category bitfield.
    @param [in] ARG3 Integer collision bitfield.
    @param [in] ARG4 Pointer to an axis aligned bounding box for testing. */
TgEXTN TgRESULT
tgPA_Graph_Test_AABB(
    TgBOOL_PC TgANALYSIS_NO_NULL OUT0, TgPARTITION_GRAPH_ID_C ARG1, TgUINT_E64_C ARG2, TgUINT_E64_C ARG3, TgBOXAA_F32_04_CPCU TgANALYSIS_NO_NULL ARG4 );

/** @brief Update the Axis Aligned Bounding Box for the given object. @return Result Code.
    @param [in] ARG0 UID for the Partition Manager to be used.
    @param [in] ARG1 Unique identifier for the object.
    @param [in] ARG2 Pointer to Axis Aligned Bounding Box to update the manager.
    @param [in] ARG3 Integer category bitfield.
    @param [in] ARG4 Integer collision bitfield. */
TgEXTN TgRESULT
tgPA_Graph_Object_Update(
    TgPARTITION_GRAPH_ID_C ARG0, TgPARTITION_OBJECT_ID_C ARG1, TgBOXAA_F32_04_CPCU TgANALYSIS_NO_NULL ARG2, TgUINT_E64_C ARG3, TgUINT_E64_C ARG4 );

/** @brief Execute a callback function on all potentially colliding pairs. @return Result Code.
    @param [in] ARG0 UID for the Partition Manager to be used.
    @param [in] ARG1 Function pointer to execute on contact/collision between two objects using the user data as the parameter. */
TgEXTN TgRESULT
tgPA_Graph_Execute_Function(
    TgPARTITION_GRAPH_ID_C ARG0, TgFCN_PA_CALLBACK ARG1 );

/** @brief Execute a callback function on all potentially colliding pairs with the object selected in ARG1. @return Result Code.
    @param [in] ARG0 UID for the Partition Manager to be used.
    @param [in] ARG1 Function pointer to execute on contact/collision between two objects using the user data as the parameter.
    @param [in] ARG2 Unique identifier for the object. */
TgEXTN TgRESULT
tgPA_Graph_Object_Execute_Function(
    TgPARTITION_GRAPH_ID_C ARG0, TgFCN_PA_CALLBACK ARG1, TgPARTITION_OBJECT_ID_C ARG2 );

/** @brief Execute a callback function on all potentially colliding pairs with the objects in the list arg ARG2. @return Result Code.
    @param [in,out] ARG0 Pointer to a Prune and Sweep Partition Manager.
    @param [in] ARG1 Function pointer to execute on contact/collision between two objects using the user data as the parameter.
    @param [in] ARG2 Pointer that stores the list of objects to be reprocessed.
    @param [in] ARG3 Integer count of values for ARG2. */
TgEXTN TgRESULT
tgPA_Graph_Object_List_Execute_Function(
    TgPARTITION_GRAPH_ID_C ARG0, TgFCN_PA_CALLBACK ARG1, TgUINT_E64_CPC ARG2, TgRSIZE_C ARG3 );

/** @} TGS_PARTITION_SYSTEM */


/* -- Prune and Sweep ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/** @addtogroup TGS_PARTITION_PRUNE_AND_SWEEP */
/** @{ */

/** @brief Initialize a new Prune and Sweep Partition Manager.
    @return UID for the new object, or the INVALID ID otherwise. */
TgEXTN TgPARTITION_GRAPH_ID
tgPA_Graph_PNS_Init( TgVOID );

/** @brief Free a Prune and Sweep Partition Manager. 
    @param [in] ARG0 UID for the Manager. */
TgEXTN TgVOID
tgPA_Graph_PNS_Free(
    TgPARTITION_GRAPH_ID_C ARG0 );

/** @} TGS_PARTITION_PRUNE_AND_SWEEP */


/* =============================================================================================================================================================================== */
#endif
