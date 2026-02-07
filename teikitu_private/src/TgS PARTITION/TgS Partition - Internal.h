/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Partition - Internal.h
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.12 | »GUID« 964CB1A6-814D-4E19-8E67-A83FCA98BF05 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_PARTITION_INTERNAL_H)
#define TGS_PARTITION_INTERNAL_H

#include "TgS Common.h"
#include "TgS Collision.h"
#include "TgS Partition.h"

#include "TgS Partition - Internal - Constants.h"
#include "TgS Partition - Internal - Type.h"
#include "TgS Partition - Internal - Data.h"

#include "TgS COMMON/TgS Common.inl"
#include "TgS COLLISION/TgS Collision.inl"


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Private Functions                                                                                                                                                              */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Prune and Sweep Private Functions                                                                                                                                              */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @brief Insert a bounding box into the Partition Graph. @return Result Code.
    @param [out] OUT0 Pointer to a Parition Object ID to hold the result of the function.
    @param [in] ARG1 Pointer to a Prune and Sweep Partition Manager.
    @param [in] ARG2 Integer user data field.
    @param [in] ARG3 Integer category field.
    @param [in] ARG4 Integer collide bitmask.
    @param [in] ARG5 Pointer to axis aligned bounding box to be added to the manager. */
TgEXTN TgRESULT
tgPA_Graph_PNS_Insert_Object(
    TgPARTITION_OBJECT_ID_PC TgANALYSIS_NO_NULL OUT0, STg2_PA_Graph_PC TgANALYSIS_NO_NULL ARG1, TgUINT_PTR_C ARG2, TgUINT_E64_C ARG3, TgUINT_E64_C ARG4,
    TgBOXAA_F32_04_CPC TgANALYSIS_NO_NULL ARG5 );

/** @brief Remove an object from a Partition Graph. @return Result Code.
    @param [in,out] ARG0 Pointer to a Prune and Sweep Partition Manager.
    @param [in] ARG1 Unique identifier for the object. */
TgEXTN TgRESULT
tgPA_Graph_PNS_Remove_Object(
    STg2_PA_Graph_PC TgANALYSIS_NO_NULL ARG0, TgPARTITION_OBJECT_ID_C ARG1 );

/** @brief Test an Axis Aligned Bounding Box for contact in the Partition Graph. @return Result Code.
    @param [out] OUT0 Pointer to boolean value to hold the result of the function.
    @param [in,out] ARG1 Pointer to a Prune and Sweep Partition Manager.
    @param [in] ARG2 Integer category bitfield.
    @param [in] ARG3 Integer collision bitfield.
    @param [in] ARG4 Pointer to an axis aligned bounding box for testing. */
TgEXTN TgRESULT
tgPA_Graph_PNS_Test_AABB(
    TgBOOL_PC TgANALYSIS_NO_NULL OUT0, STg2_PA_Graph_PC TgANALYSIS_NO_NULL ARG1, TgUINT_E64_C ARG2, TgUINT_E64_C ARG3, TgBOXAA_F32_04_CPCU TgANALYSIS_NO_NULL ARG4 );

/** @brief Update the Axis Aligned Bounding Box for the given object. @return Result Code.
    @param [in,out] ARG0 Pointer to a Prune and Sweep Partition Manager.
    @param [in] ARG1 Unique identifier for the object.
    @param [in] ARG2 Pointer to Axis Aligned Bounding Box to update the manager.
    @param [in] ARG3 Integer category bitfield.
    @param [in] ARG4 Integer collision bitfield. */
TgEXTN TgRESULT
tgPA_Graph_PNS_Object_Update(
    STg2_PA_Graph_PC TgANALYSIS_NO_NULL ARG0, TgPARTITION_OBJECT_ID_C ARG1, TgBOXAA_F32_04_CPCU TgANALYSIS_NO_NULL ARG2, TgUINT_E64_C ARG3, TgUINT_E64_C ARG4 );

/** @brief Execute a callback function on all potentially colliding pairs. @return Result Code.
    @param [in,out] ARG0 Pointer to a Prune and Sweep Partition Manager.
    @param [in] ARG1 Function pointer to execute on contact/collision between two objects using the user data as the parameter. */
TgEXTN TgRESULT
tgPA_Graph_PNS_Execute_Function(
    STg2_PA_Graph_PC TgANALYSIS_NO_NULL ARG0, TgFCN_PA_CALLBACK ARG1 );

/** @brief Execute a callback function on all potentially colliding pairs with the object selected in ARG1. @return Result Code.
    @param [in,out] ARG0 Pointer to a Prune and Sweep Partition Manager.
    @param [in] ARG1 Function pointer to execute on contact/collision between two objects using the user data as the parameter.
    @param [in] ARG2 Unique identifier for the object. */
TgEXTN TgRESULT
tgPA_Graph_PNS_Object_Execute_Function(
    STg2_PA_Graph_PC TgANALYSIS_NO_NULL ARG0, TgFCN_PA_CALLBACK ARG1, TgPARTITION_OBJECT_ID_C ARG2 );

/** @brief Execute a callback function on all potentially colliding pairs with the objects in the list arg ARG2. @return Result Code.
    @param [in,out] ARG0 Pointer to a Prune and Sweep Partition Manager.
    @param [in] ARG1 Function pointer to execute on contact/collision between two objects using the user data as the parameter.
    @param [in] ARG2 Pointer that stores the list of objects to be reprocessed.
    @param [in] ARG3 Integer count of values for ARG2. */
TgEXTN TgRESULT
tgPA_Graph_PNS_Object_List_Execute_Function(
    STg2_PA_Graph_PC TgANALYSIS_NO_NULL ARG0, TgFCN_PA_CALLBACK ARG1, TgUINT_E64_CPC ARG2, TgRSIZE_C ARG3 );




/* =============================================================================================================================================================================== */
#endif

