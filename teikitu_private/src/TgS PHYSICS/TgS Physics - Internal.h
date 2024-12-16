/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Physics - Internal.h
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.21 | »GUID« AEEC8393-9780-4ECA-918D-E3E11F7E2744 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_PHYSICS_INTERNAL_H)
#if !defined (ENABLE_RELOAD_GUARD)

#include "TgS Common.h"
#include "TgS Collision.h"
#include "TgS Partition.h"
#include "TgS Kernel.h"
#include "TgS Kernel [GPU].h"
#include "TgS Physics.h"

#include "TgS Physics - Internal - Constants.h"
#include "TgS Physics - Internal - Type.h"
#include "TgS Physics - Internal - Data.h"

#include "TgS Physics - Internal - Macro.h"

#include "TgS COMMON/TgS Common.inl"




/* == Physics ==================================================================================================================================================================== */

/* NOTE: Many of the internal functions will ASSUME specific read/write rights. */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/** @brief Used doing Module Initialization and responsbile for the setup of the Job. */
TgEXTN TgVOID
tgPH_Update_World__Init_Jobs( TgVOID );


/* -- Mass ----------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/** @addtogroup TGS_PHYSICS_MASS */
/** @{ */

/** @brief Update the mass structure based on moving the centre of mass. @return Result Code.
    @param [in,out] INOUT0 Pointer to a mass data structure that is updated.
    @param [in] ARG1 Scalar value.
    @param [in] ARG2 Scalar value.
    @param [in] ARG3 Scalar value.*/
TgINLINE TgRESULT
tgPH_Mass_Move_Elem(
    STg2_PH_Mass_PC TgANALYSIS_NO_NULL INOUT0, TgFLOAT32_C ARG1, TgFLOAT32_C ARG2, TgFLOAT32_C ARG3 );

/** @brief Update the mass structure based on moving the centre of mass. @return Result Code.
    @param [in,out] INOUT0 Pointer to a mass data structure that is updated.
    @param [in] ARG1 Vector value. */
TgEXTN TgRESULT
tgPH_Mass_Move(
    STg2_PH_Mass_PC TgANALYSIS_NO_NULL INOUT0, TgVEC_F32_04_1_C ARG1 );

/** @brief Update the mass structure based on a rotation (euler angles). @return Result Code.
    @param [in,out] INOUT0 Pointer to a mass data structure that is updated.
    @param [in] ARG1 Scalar value.
    @param [in] ARG2 Scalar value.
    @param [in] ARG3 Scalar value. */
TgINLINE TgRESULT
tgPH_Mass_Rotate_Eul_Elem(
    STg2_PH_Mass_PC TgANALYSIS_NO_NULL INOUT0, TgFLOAT32_C ARG1, TgFLOAT32_C ARG2, TgFLOAT32_C ARG3 );

/** @brief Update the mass structure based on a rotation (euler angles). @return Result Code.
    @param [in,out] INOUT0 Pointer to a mass data structure that is updated.
    @param [in] ARG1 Vector value. */
TgINLINE TgRESULT
tgPH_Mass_Rotate_Eul( 
    STg2_PH_Mass_PC TgANALYSIS_NO_NULL INOUT0, TgVEC_F32_04_1_C ARG1 );

/** @brief Update the mass structure based on a rotation (quaternion). @return Result Code.
    @param [in,out] INOUT0 Pointer to a mass data structure that is updated.
    @param [in] ARG1 Vector value. */
TgINLINE TgRESULT
tgPH_Mass_Rotate_Quat(
    STg2_PH_Mass_PC TgANALYSIS_NO_NULL INOUT0, TgVEC_F32_04_1_C ARG1 );

/** @brief Update the mass structure based on a rotation (matrix). @return Result Code.
    @param [in,out] INOUT0 Pointer to a mass data structure that is updated.
    @param [in] ARG1 Pointer to an array of vectors (matrix). */
TgEXTN TgRESULT
tgPH_Mass_Rotate_Mat(
    STg2_PH_Mass_PC TgANALYSIS_NO_NULL INOUT0, TgVEC_F32_04_3_CPCU ARG1 );

/** @brief Update the mass structure as union of itself and the argument. @return Result Code.
    @param [in,out] INOUT0 Pointer to a mass data structure that is updated.
    @param [in] ARG1 Pointer a mass data structure. */
TgINLINE TgRESULT
tgPH_Mass_Union_Mat(
    STg2_PH_Mass_PC TgANALYSIS_NO_NULL INOUT0, STg2_PH_Mass_CPC TgANALYSIS_NO_NULL ARG1 );

/** @} TGS_PHYSICS_MASS */




/* -- Material ------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

/** @brief Used in the module boot (tgPH_Module_Boot) to create standard materials. */
TgEXTN TgVOID
tgPH_Module_Material_Boot( TgVOID );

/** @brief Calculate the restitution factor based on the two body's information (primarily the material for simplicity).
    @param [in] ARG0 Pointer to a Form.
    @param [in] ARG1 Vector of the translation of ARG0.
    @param [in] ARG2 Pointer to a Form.
    @param [in] ARG3 Vector of the translation of ARG2.
    @return Vector of the Factor of Resitution broadcast across all lanes. */
TgINLINE TgVEC_F32_04_1
tgPH_Material_Calc_Restitution_Factor(
    STg2_PH_Form_CPC TgANALYSIS_NO_NULL ARG0, TgVEC_F32_04_1_C ARG1, STg2_PH_Form_CPC TgANALYSIS_NO_NULL ARG2, TgVEC_F32_04_1_C ARG3 );


/* -- Mass ----------------------------------------------------------------------------------------------------------------------------------------------------------------------- */


/* -- Form ----------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

/** @brief Used to update when there is has been a local change to the Form.
    @note WRITE access is required.
    @param [in,out] INOUT0 Pointer to a Form to update.
    @param [in] ARG1 Pointer to the owning Body.
    @param [in] ARG2 Boolean flag for Last Position that on true uses the updated Position and on false the current (previous) Position. */
TgINLINE TgVOID
tgPH_Form_Update__WRITE(
     STg2_PH_Form_PC TgANALYSIS_NO_NULL INOUT0, STg2_PH_Body_PC TgANALYSIS_NO_NULL ARG1, TgBOOL_C ARG2 );

/** @brief Used to update when there is has been a local change to the Form.
    @note WRITE access is required.
    @param [in] ARG0 UID for the Form object to be updated. */
TgEXTN TgVOID
tgPH_Form_Reset_IMM(
     TgPH_FORM_ID_C ARG0 );

/** @brief Immediate mode to set the collision primitive, function table, and primitive data.
    @note WRITE access is required.
    @param [in,out] INOUT0 Pointer to a Form to update.
    @param [in] ARG1 Enumeration selecting the type of primitive.
    @param [in] ARG2 Pointer to the primitive data. */
TgEXTN TgVOID
tgPH_Form_Set_Collision_Primitive_IMM(
    STg2_PH_Form_PC INOUT0, ETgPM_SHORT_C ARG1, UTg2_CO_Primitive_F32_04_CPC ARG2 );



/* -- Body ----------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

/** @brief Used to update the local state of the Body and cascade updates to its children.
    @note WRITE access is required.
    @param [in,out] INOUT0 Pointer to a Body to update.
    @param [in] ARG1 Boolean flag for Last Position that on true uses the updated Position and on false the current (previous) Position. */
TgINLINE TgVOID
tgPH_Body_Update__WRITE(
     STg2_PH_Body_PC TgANALYSIS_NO_NULL INOUT0, TgBOOL_C ARG1 );

/** @brief Removes the Form from the Body's linked list of associated Forms.
    @note WRITE access is required.
    @param [in] ARG0 UID for the Body object.
    @param [in] ARG1 UID for the Form object to add.
    @param [in] ARG2 Pointer to a Mass structure. */
TgEXTN TgVOID
tgPH_Body_Add_Form_IMM(
    TgPH_BODY_ID_C ARG0, TgPH_FORM_ID_C ARG1, STg2_PH_Mass_CPC ARG2 );

/** @brief Removes the Form from the Body's linked list of associated Forms.
    @note WRITE access is required.
    @param [in] ARG0 UID for the Form object to be removed. */
TgEXTN TgVOID
tgPH_Body_Remove_Form_IMM(
    TgPH_FORM_ID_C ARG0 );

/** @brief Sets the enabled state for the body, and cascades this change down to all of the associated Forms.
    @note WRITE access is required.
    @param [in] ARG0 Pointer to a Body data structure.
    @param [in] ARG1 Boolean flag to indicating new state. */
TgEXTN TgVOID
tgPH_Body_Set_Update_IMM(
    STg2_PH_Body_PC ARG0, TgBOOL_C ARG1 );

TgEXTN TgVOID
tgPH_Body_Contact_Default(
    TgPH_BODY_ID_C ARG0, TgFLOAT32_C ARG1 );


/* -- Motor ---------------------------------------------------------------------------------------------------------------------------------------------------------------------- */



/* -- Constraint ----------------------------------------------------------------------------------------------------------------------------------------------------------------- */

/** @brief Helper function that will immediately acquire a new constraint and add it to most of the relevant queues. @return Result Code
    @param [out] OUT0 Pointer to a pointer for a constraint.
    @param [in] ARG1 Enumeration selecting the type of constraint for its registration.
    @param [in] ARG2 UID for the first body associated with the constraint (may be invalid but not both).
    @param [in] ARG3 UID for the second body associated with the constraint (may be invalid but not both). */
TgEXTN TgRESULT
tgPH_Constraint__Init_IMM(
    STg2_PH_Constraint_PP TgANALYSIS_NO_NULL OUT0, ETgPH_CONSTRAINT_C ARG1, TgPH_BODY_ID_C ARG2, TgPH_BODY_ID_C ARG3 );

/** @brief Helper function to immediately free and return a constraint to the free queue.
    @param [in] ARG0 UID for the World. */
TgEXTN TgVOID
tgPH_Constraint__Bind_IMM(
    TgPH_WORLD_ID_C ARG0 );

/** @brief Helper function to immediately free and return a constraint to the free queue.
    @param [in] ARG0 Pointer to a Constraint. */
TgEXTN TgVOID
tgPH_Constraint__Free_IMM(
    STg2_PH_Constraint_PC TgANALYSIS_NO_NULL ARG0 );

/** @brief This will immediately acquire a new constraint and set it up as a contact constraint. @return UID for the Constraint.
    @param [in] ARG0 Pointer to the 1st Form used in Contact.
    @param [in] ARG1 Pointer to the 2nd Form used in Contact.
    @param [in] ARG2 Vector of the Restitution Factor broadcast across all lanes for the Collision Response.
    @param [in] ARG3 Pointer to a contact point (surface) between the two bodies (may be penetrated). */
TgEXTN TgPH_CONSTRAINT_ID
tgPH_Constraint_Contact__Init_IMM(
    STg2_PH_Form_CPC TgANALYSIS_NO_NULL ARG0, STg2_PH_Form_CPC TgANALYSIS_NO_NULL ARG1, TgVEC_F32_04_1_C ARG2, STg2_CO_Contact_F32_04_CPC TgANALYSIS_NO_NULL ARG3 );

/** @brief Immediately free and return the constraint to the free queue.
    @param [in] ARG0 Pointer to a Constraint. */
TgEXTN TgVOID
tgPH_Constraint_Contact__Free_IMM(
    STg2_PH_Constraint_PC TgANALYSIS_NO_NULL ARG0 );

/*  @brief Free all contacts. This is used at the end of the world step as we generate contacts on a per frame basis.
    @param [in,out] ARG0 Pointer to a solver data structure that include the problem set, supporting solver data, and the resulting solution outcomes. */
TgEXTN TgVOID
tgPH_Constraint_Contact__Free_All_IMM(
    STg2_PH_Solver__Set_PC TgANALYSIS_NO_NULL ARG0 );

/*  @brief Iterate through all of the contact constraints in this problem set and fill in the required data for the solver.
    @param [in] ARG0 UID for the World to be processed.
    @parma [in,out] ARG1 Pointer to a solver data structure that include the problem set, supporting solver data, and the resulting solution outcomes. */
TgEXTN TgVOID
tgPH_Constraint_Contact__Problem_Definition(
    TgPH_WORLD_ID ARG0, STg2_PH_Solver__Set_CPC TgANALYSIS_NO_NULL ARG1 );

/** @brief This will immediately acquire a new constraint and set it up as a fixed constraint. @return UID for the Constraint.
    @param [in] ARG0 UID for the first body associated with the constraint (may be invalid but not both).
    @param [in] ARG1 UID for the second body associated with the constraint (may be invalid but not both). */
TgEXTN TgPH_CONSTRAINT_ID
tgPH_Constraint_Fixed__Init_IMM(
    TgPH_BODY_ID_C ARG0, TgPH_BODY_ID_C ARG1 );

/** @brief Immediately free and return the constraint to the free queue.
    @param [in] ARG0 Pointer to a Constraint. */
TgEXTN TgVOID
tgPH_Constraint_Fixed__Free_IMM(
    STg2_PH_Constraint_PC TgANALYSIS_NO_NULL ARG0 );

/*  @brief Iterate through all of the fixed constraints in this problem set and fill in the required data for the solver.
    @param [in] ARG0 UID for the World to be processed.
    @parma [in,out] ARG1 Pointer to a solver data structure that include the problem set, supporting solver data, and the resulting solution outcomes. */
TgEXTN TgVOID
tgPH_Constraint_Fixed__Problem_Definition(
    TgPH_WORLD_ID ARG0, STg2_PH_Solver__Set_CPC TgANALYSIS_NO_NULL ARG1 );


/* -- Ragdoll -------------------------------------------------------------------------------------------------------------------------------------------------------------------- */


/* -- Scene ---------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgEXTN TgVOID
tgPH_Scene_Validate(
    STg2_Output_PC TgANALYSIS_NO_NULL OUT0, TgPH_SCENE_ID_C ARG1 );


/* -- World ---------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

/*                                                                                                                                                                   World Updates */

TgEXTN TgRESULT
tgPH_Update_World(
    TgPH_WORLD_ID_C ARG0 );

TgEXTN TgVOID
tgPH_Update_World__Simulate_Batch_IMM(
    TgPH_WORLD_ID_C ARG1, TgRSIZE_C ARG2, TgRSIZE_C ARG3 );

TgEXTN TgVOID
tgPH_Update_World__Collide__Simple_IMM(
    TgPH_WORLD_ID_C ARG0, TgRSIZE_C ARG1, TgRSIZE_C ARG2 );

TgEXTN TgVOID
tgPH_Update_World__Collide__Partition_Manager_IMM(
    TgPH_WORLD_ID_C ARG0 );

TgEXTN TgRESULT
tgPH_Update_World__Build_Sets(
    TgPH_WORLD_ID_C ARG0 );

TgEXTN TgRESULT
tgPH_Update_World__Job__Solve_Sets(
    STg2_Job_CPC TgANALYSIS_NO_NULL ARG0 );

TgEXTN TgVOID
tgPH_Update_World__Define_Problem_And_Solve(
    TgPH_WORLD_ID_C ARG0, STg2_PH_Solver__Set_PC TgANALYSIS_NO_NULL ARG1 );

TgEXTN TgVOID
tgPH_Update_World__Update_Bodies_IMM(
    TgPH_WORLD_ID_C ARG0, STg2_PH_Solver__Set_PC TgANALYSIS_NO_NULL ARG1 );

TgEXTN TgVOID
tgPH_Update_World__Solver_SOR(
    TgPH_WORLD_ID_C ARG0 );

TgEXTN TgVOID
tgPH_Update_World__Solver_Post(
    TgPH_WORLD_ID_C ARG0 );


/*                                                                                                                                                                         Solvers */

TgEXTN TgVOID
tgPH_SV_SOR_LCP(
    TgPH_WORLD_ID_C ARG0, STg2_PH_Solver__Set_CPC TgANALYSIS_NO_NULL ARG1 );

TgEXTN TgVOID
tgPH_SV_GS_LCP( 
    TgPH_WORLD_ID_C ARG0, STg2_PH_Solver__Set_CPC TgANALYSIS_NO_NULL ARG1 ); //« Gauss-Sidel Solver

TgEXTN TgVOID
tgPH_SV_LCP(
    TgPH_WORLD_ID_C ARG0, STg2_PH_Solver__Set_CPC TgANALYSIS_NO_NULL ARG1 ); //« A non-iterative LCP solver

TgEXTN TgVOID
tgPH_SV_MT_LCP(
    TgPH_WORLD_ID_C ARG0, STg2_PH_Solver__Set_CPC TgANALYSIS_NO_NULL ARG1 ); //« Multi-threaded solver.


/*                                                                                                                                                                 Run Time Values */

/** @brief . */
TgEXTN TgRESULT
tgPH_World_Query_Body_Count(
    TgRSIZE_P OUT0, TgPH_WORLD_ID_C ARG1 );

/** @brief . */
TgEXTN TgRESULT
tgPH_World_Query_Form_Count(
    TgRSIZE_P OUT0, TgPH_WORLD_ID_C ARG1 );


/*                                                                                                                                                        Job Configuration Values */

/** @brief . */
TgEXTN TgRESULT
tgPH_World_Query_Simulate_Batch_Size(
    TgRSIZE_P OUT0, TgPH_WORLD_ID_C ARG1 );

/** @brief . */
TgEXTN TgRESULT
tgPH_World_Query_Collide_Batch_Size(
    TgRSIZE_P OUT0, TgPH_WORLD_ID_C ARG1 );

/*                                                                                                                                                               Utility Functions */
 TgINLINE TgVOID
 tgPH_Update_World__Free_Solver_Set(
     STg2_PH_Solver__Set_PC TgANALYSIS_NO_NULL ARG1 );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Generic Object Memory Management                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

#define __PARENT_FILE__ "TgS Physics - Internal.h"
#define ENABLE_RELOAD_GUARD
#include "TgS PHYSICS/TgS Physics - Object [INC].h"
#undef ENABLE_RELOAD_GUARD
#undef __PARENT_FILE__

#define TGS_PHYSICS_INTERNAL_H


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Debug Functions                                                                                                                                                                */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
#if defined(TgBUILD_DEBUG__PHYSICS)

/* World */
TgEXTN TgVOID
tgPH_World_Validate(
    STg2_Output_PC TgANALYSIS_NO_NULL OUT0, TgPH_WORLD_ID_C ARG1 );

/*                                                                                                                                                          World - User Functions */

/** @brief Set the user function that is called once a collision contact has been created. @return Result Code.
    @param [out] OUT0 Pointer to a function pointer value that will contain the previously used value.
    @param [in] ARG1 UID for the World to be manipulated.
    @param [in] ARG2 Function pointer to use (or nullptr). */
TgEXTN TgRESULT
tgPH_World_Set_User_FCN__Constraint_Contact_Init_Complete(
    TgPH_FCN_USER_CONTACT_COMPLETE_P OUT0, TgPH_WORLD_ID_C ARG1, TgPH_FCN_USER_CONTACT_COMPLETE ARG2 );

/** @brief Print out the intial state of a newly created contact constraint.
    @param [in] ARG0 Pointer to the constraint. */
TgEXTN TgVOID
tgPH_Constraint_Contact__CNPrintF_IMM(
    STg2_PH_Constraint_CPC ARG0 );

/*# defined(TgBUILD_DEBUG__PHYSICS) */
#endif


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Stat Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
#if defined(TgS_STAT__PHYSICS) && TgS_STAT__PHYSICS

/*# defined(TgS_STAT__PHYSICS) && TgS_STAT__PHYSICS */
#endif


/*# defined (ENABLE_RELOAD_GUARD) */
#else

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Generic Object Memory Management                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/** @brief Initialize all of the data values as part of the Module Init. 
    @internal Defined in Generic Functions. */
TgEXTN TgVOID
T_NAME(tgPH_Module_,_Init)( TgVOID );

/** @brief Free all dynamic allocations owned by the module, and validate that the module is in a cleared (reset) state.
    @internal Defined in Generic Functions. */
TgEXTN TgVOID
T_NAME(tgPH_Module_,_Free)( TgVOID );

#if !defined(T_STATIC)

/** @brief Override resource(type) configuration values. */
TgEXTN TgVOID
T_NAME(tgPH_Module_,_Init_Internal)( TgVOID );

/** @brief Init the object passed in the command buffer and add it to the used list.
    @param [in] ARG0 Pointer to a command buffer (byte array).
    @param [in] ARG1 Integer value for the maximum length of the command buffer. */
TgEXTN TgVOID
T_NAME(tgPH_,_Init_Do_Command)(
    TgVOID_CPC ARG0, TgRSIZE_C ARG1 );

/** @brief Reset the object passed in the command buffer and add it to the free list.
    @param [in] ARG0 Pointer to a command buffer (byte array).
    @param [in] ARG1 Integer value for the maximum length of the command buffer. */
TgEXTN TgVOID
T_NAME(tgPH_,_Reset_Do_Command)(
    TgVOID_CPC TgANALYSIS_NO_NULL ARG0, TgRSIZE_C ARG1 );

#if defined(T_GLOBAL)

TgEXTN T_NAME(STg2_PH_,_P)
T_NAME(tgPH_,_Grow_Commit_List)( TgVOID );

#else

TgEXTN T_NAME(STg2_PH_,_P)
T_NAME(tgPH_,_Grow_Commit_List)(
    TgPH_WORLD_ID_C ARG0 );

#endif

#else
/*# !defined(T_STATIC) */

/** @brief Init the object passed into the function.
    @param [in,out] INOUT0 Pointer to an object to initialize. 
    @return KTgS_OK on success, and KTgE_FAIL or an error code otherwise. */
TgEXTN TgRESULT
T_NAME(tgPH_,_Init_Internal)(
    T_NAME(STg2_PH_,_P) TgANALYSIS_NO_NULL INOUT0 );

/** @brief Reset the object passed into the function.
    @param [in,out] INOUT0 Pointer to an object to initialize.
    @return KTgS_OK on success, and KTgE_FAIL or an error code otherwise. */
TgEXTN TgRESULT
T_NAME(tgPH_,_Reset_Internal)(
    T_NAME(STg2_PH_,_P) TgANALYSIS_NO_NULL INOUT0 );

/*# !defined(T_STATIC) */
#endif

/** @brief Initialize a resource unique identifier given the required parameters.
    @internal Defined in TgS Physics - Internal.inl.
    @param [out] OUT0 Pointer to the identifier to be initialized.
    @param [in] ARG1 Integer index of the resource.
    @param [in] ARG2 Integer index of the world.
    @param [in] ARG3 Integer index of the scene.
    @return A copy of the identifier stored in the singleton on success or INVALID otherwise. */
TgINLINE T_ID(TgPH_,_ID)
T_ID(tgPH_,_ID_Init)(
    T_ID(TgPH_,_ID_PCU) TgANALYSIS_NO_NULL OUT0, TgUINT_E32_C ARG1, TgUINT_E08_C ARG2, TgUINT_E08_C ARG3 );

/** @brief Return a pointer to the object with the given id value.
    @internal Defined in TgS Physics - Internal.inl.
    @return A pointer to the object with the given id value, or nullptr otherwise. */
TgINLINE T_NAME(STg2_PH_,_P)
T_FCN(tgPH_,_Get_,_From_ID)(
    T_ID(TgPH_,_ID_C) ARG0 );

#if defined(TgBUILD_DEBUG__PHYSICS)
/** @brief Validate an object (resource) and output the results of the validation.
    @param [in] ARG0 Pointer to an object containing the functions pointers to be used when outputing the validation messages.
    @param [in] ARG1 Unique Identifier for the resource to be tested. */
TgEXTN TgVOID
T_NAME(tgPH_,_Validate)(
    STg2_Output_PC TgANALYSIS_NO_NULL ARG0, T_ID(TgPH_,_ID_C) ARG1 );
/*# defined(TgBUILD_DEBUG__PHYSICS) */
#endif

/*# defined (ENABLE_RELOAD_GUARD) */
#endif

/* =============================================================================================================================================================================== */
/*# defined (TGS_PHYSICS_INTERNAL_H) */
#endif
