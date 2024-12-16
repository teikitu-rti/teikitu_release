/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Effect - Internal.h
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.12 | »GUID« 964CB1A6-814D-4E19-8E67-A83FCA98BF05 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_EFFECT_INTERNAL_H)
#if !defined (ENABLE_RELOAD_GUARD)

#include "TgS Common.h"
#include "TgS Collision.h"
#include "TgS Kernel.h"
#include "TgS Kernel [GPU].h"
#include "TgS Utility.h"
#include "TgS Render [Stub].h"
#include "TgS Script [Stub].h"
#include "TgS Sound [Stub].h"
#include "TgS Object [Stub].h"
#include "TgS Set [Stub].h"

#include "TgS Effect.h"

#include "TgS Effect - Internal - Type.h"
#include "TgS Effect - Internal - Data.h"

#include "TgS COMMON/TgS Common.inl"
#include "TgS COLLISION/TgS Collision.inl"


/* == Effects ==================================================================================================================================================================== */

/* The effect system has three lanes of execution ownership.  The client thread owns creation and termination of effect instances.  The render thread owns the other */
/* two lanes - updating and rendering.  Communication between the client and render threads is done by message passing within the effect system.  Each effect instance */
/* has a client thread id and a render thread id.  The process for creation requires that the client thread create a generic effect instance, and then pass the creation */
/* message to the render thread.  As long as the render thread instance is active the entire effect instance is owned by the render thread.  Once the render */
/* instance is done it will send back a message to the client thread for termination.  Early termination requires the client thread to send a termination message to */
/* the render thread.  The client thread instance cannot be terminated until the render thread sends its termination request. */

/* --------|--------------------------------------|---------------------------------------|--------------------------------------|--------------------------------------| */
/* Thread  | Client                               | Update (Jobs)                         | Scene (Jobs)                         | Render Thread and Jobs               | */
/* --------|--------------------------------------|---------------------------------------|--------------------------------------|--------------------------------------| */
/* Goal    |                                      | Update All Effects                    | Add all visible effects to the scene | Render all Effects in Scene          | */
/* --------|--------------------------------------|---------------------------------------|--------------------------------------|--------------------------------------| */
/* Pre     | [Previous Render Jobs in Flight]     |                                       |                                      |                                      | */
/*         | [No Update Jobs]                     |                                       |                                      |                                      | */
/*         | [No Scene Jobs]                      |                                       |                                      |                                      | */
/*         | OWN: Client Effect Data              |                                       |                                      |                                      | */
/* --------|--------------------------------------|---------------------------------------|--------------------------------------|--------------------------------------| */
/* Execute | SINGLE UPDATE: Default Update List   |                                       |                                      |                                      | */
/*         | SINGLE UPDATE: External Update List  |                                       |                                      |                                      | */
/*         | FLUSH: New Update List               |                                       |                                      |                                      | */
/*         | EXECUTE: ToClient Commands           |                                       |                                      |                                      | */
/*         |                                      |                                       |                                      |                                      | */
/*         | Execute all ToClient Commands        |                                       |                                      |                                      | */
/*         | Remove all deleted effects from lists|                                       |                                      |                                      | */
/*         | Add all new effects to update lists  |                                       |                                      |                                      | */
/*         |                                      |                                       |                                      |                                      | */
/*         | Submit Update Jobs                   |                                       |                                      |                                      | */
/*         |  - Update Default List               |                                       |                                      |                                      | */
/* --------|--------------------------------------|---------------------------------------|--------------------------------------|--------------------------------------| */
/* Pre     |                                      | [No Trigger - Start on Submit]        |                                      |                                      | */
/*         |                                      | OWN: System Effect Data               |                                      |                                      | */
/* --------|--------------------------------------|---------------------------------------|--------------------------------------|--------------------------------------| */
/* Execute |                                      | Update the Default Update List        |                                      |                                      | */
/* --------|--------------------------------------|---------------------------------------|--------------------------------------|--------------------------------------| */
/* Pre     | [Scene Camera Set]                   |                                       |                                      |                                      | */
/*         | [Buffer Toggle]                      |                                       |                                      |                                      | */
/* --------|--------------------------------------|---------------------------------------|--------------------------------------|--------------------------------------| */
/* Execute | Submit Scene Cull Jobs               |                                       |                                      |                                      | */
/*         |  - Update Default List               |                                       |                                      |                                      | */
/*         |  - Update External List              |                                       |                                      |                                      | */
/* --------|--------------------------------------|---------------------------------------|--------------------------------------|--------------------------------------| */
/* Pre     |                                      |                                       | [Scene Camera Set]                   |                                      | */
/*         |                                      |                                       |  - Known from Submit                 |                                      | */
/*         |                                      |                                       | RENDER NEXT?                         |                                      | */
/*         |                                      |                                       | TRIGGER: Update Complete             |                                      | */
/*         |                                      |                                       | OWN: Bounding Box                    |                                      | */
/* --------|--------------------------------------|---------------------------------------|--------------------------------------|--------------------------------------| */
/* Execute |                                      |                                       | Cull the Default Update List         |                                      | */
/*         |                                      |                                       | Cull the External Update List        |                                      | */
/*         |                                      |                                       | Culling Pass                         |                                      | */
/*         |                                      |                                       | - If visible to camera               |                                      | */
/*         |                                      |                                       |   - Add to render list               |                                      | */
/*         |                                      |                                       |   - Reserve a Context Index          |                                      | */
/*         |                                      |                                       | - Else                               |                                      | */
/*         |                                      |                                       |   - Clear the Context Index          |                                      | */
/* --------|--------------------------------------|---------------------------------------|--------------------------------------|--------------------------------------| */
/* Pre     | [Attachment Update Complete]         |                                       |                                      |                                      | */
/* --------|--------------------------------------|---------------------------------------|--------------------------------------|--------------------------------------| */
/* Execute | Submit Update Jobs                   |                                       |                                      |                                      | */
/*         |  - Update External List              |                                       |                                      |                                      | */
/* --------|--------------------------------------|---------------------------------------|--------------------------------------|--------------------------------------| */
/* Pre     |                                      | [Attachment Update Complete]          |                                      |                                      | */
/*         |                                      |  - Known from Submit                  |                                      |                                      | */
/* --------|--------------------------------------|---------------------------------------|--------------------------------------|--------------------------------------| */
/* Execute |                                      | Update the External Update List       |                                      |                                      | */
/*         |                                      |                                       |                                      |                                      | */
/* --------|--------------------------------------|---------------------------------------|--------------------------------------|--------------------------------------| */
/* Pre     | [Client Update Complete]             |                                       |                                      |                                      | */
/* --------|--------------------------------------|---------------------------------------|--------------------------------------|--------------------------------------| */
/* Execute | Submit all Jobs for ToUpdate Commands|                                       |                                      |                                      | */
/* --------|--------------------------------------|---------------------------------------|--------------------------------------|--------------------------------------| */
/* Pre     |                                      | [Default Update Complete]             |                                      |                                      | */
/*         |                                      | [External Update Complete]            |                                      |                                      | */
/*         |                                      | [Client Update Complete]              |                                      |                                      | */
/*         |                                      |  - Known from Submit                  |                                      |                                      | */
/* --------|--------------------------------------|---------------------------------------|--------------------------------------|--------------------------------------| */
/* Execute |                                      | Execute all ToUpdate Commands         |                                      |                                      | */
/*         |                                      |  - Creates effects (added to new list)|                                      |                                      | */
/*         |                                      |  - Notify Messages                    |                                      |                                      | */
/*         |                                      |  - Delete Effect (mark for removal)   |                                      |                                      | */
/*         |                                      |                                       |                                      |                                      | */
/*         |                                      |  - Update New Effects                 |                                      |                                      | */
/*         |                                      |  - Cull New Effects                   |                                      |                                      | */
/*         |                                      |                                       |                                      |                                      | */
/*         |                                      |  - Submit Bounding Box Update         |                                      |                                      | */
/* --------|--------------------------------------|---------------------------------------|--------------------------------------|--------------------------------------| */
/* Post    |                                      | UPDATE DONE: All Effects Updated      |                                      |                                      | */
/* --------|--------------------------------------|---------------------------------------|--------------------------------------|--------------------------------------| */
/* Pre     | [All Scene Cull Jobs Complete]       |                                       | [All Scene Cull Jobs Complete]       |                                      | */
/*         | [ToUpdate Commands Complete]         |                                       | [ToUpdate Commands Complete]         |                                      | */
/* --------|--------------------------------------|---------------------------------------|--------------------------------------|--------------------------------------| */
/* Execute | Scene Processing                     |                                       | Update Bounding Boxes not in Render  |                                      | */
/* --------|--------------------------------------|---------------------------------------|--------------------------------------|--------------------------------------| */
/* Post    |                                      |                                       | CULL DONE: Effects culled in scene   |                                      | */
/*         |                                      |                                       | SCENE DONE                           |                                      | */
/* --------|--------------------------------------|---------------------------------------|--------------------------------------|--------------------------------------| */
/* Pre     | [Scene Submitted for Rendering]      |                                       |                                      |                                      | */
/* --------|--------------------------------------|---------------------------------------|--------------------------------------|--------------------------------------| */
/* Execute | Submit all Jobs for Rendering        |                                       |                                      |                                      | */
/* --------|--------------------------------------|---------------------------------------|--------------------------------------|--------------------------------------| */
/* Pre     |                                      |                                       |                                      | [Scene Submitted for Rendering]      | */
/*         |                                      |                                       |                                      |  - Known from Submit                 | */
/* --------|--------------------------------------|---------------------------------------|--------------------------------------|--------------------------------------| */
/* Execute |                                      |                                       |                                      | Request Particle Headers from System | */
/*         |                                      |                                       |                                      |  - Patch Context Buffer              | */
/*         |                                      |                                       |                                      |  - Map Context to Particle Buffer    | */
/* --------|--------------------------------------|---------------------------------------|--------------------------------------|--------------------------------------| */
/* Pre     |                                      |                                       |                                      | [All Process Headers Complete]       | */
/* --------|--------------------------------------|---------------------------------------|--------------------------------------|--------------------------------------| */
/* Execute |                                      |                                       |                                      | Allocate Memory for CPU Rendering    | */
/*         |                                      |                                       |                                      |  - Degrade VFX rendered as necessary | */
/*         |                                      |                                       |                                      |  - Clamp at Max Memory for Effects   | */
/*         |                                      |                                       |                                      | Assign memory into each Header       | */
/*         |                                      |                                       |                                      |                                      | */
/*         |                                      |                                       |                                      | Submit all job for Render Generation | */
/* --------|--------------------------------------|---------------------------------------|--------------------------------------|--------------------------------------| */
/* Pre     |                                      |                                       |                                      | [Allocations Complete]               | */
/*         |                                      |                                       |                                      |  - Known from Submit                 | */
/* --------|--------------------------------------|---------------------------------------|--------------------------------------|--------------------------------------| */
/* Execute |                                      |                                       |                                      | Render Geometry                      | */
/* --------|--------------------------------------|---------------------------------------|--------------------------------------|--------------------------------------| */
/* Post    |                                      |                                       |                                      | RENDER DONE                          | */
/* --------|--------------------------------------|---------------------------------------|--------------------------------------|--------------------------------------| */


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- System Functions - Effects ----------------------------------------------------------------------------------------------------------------------------------------------- */

TgEXTN TgUINT_F32
tgFX__Client__Get_Client_Index(
    TgFX_CLIENT_INST_ID_C );

TgEXTN TgVOID
tgFX__Client__Free_Internal(
    TgUINT_F32_C );


TgEXTN TgVOID
tgFX__Client__Set_Position_From_External_Update(
    TgFX_CLIENT_INST_ID_C, TgVEC_F32_04_1 );

TgEXTN TgVOID
tgFX__Client__Set_Rotation_From_External_Update(
    TgFX_CLIENT_INST_ID_C, TgVEC_F32_04_1 );

TgEXTN TgVOID
tgFX__Client__Update_Position_From_Parent(
    TgFX_CLIENT_INST_ID_C, TgVEC_F32_04_1 );

TgEXTN TgVOID
tgFX__Client__Update_Rotation_From_Parent(
    TgFX_CLIENT_INST_ID_C, TgVEC_F32_04_1 );


TgEXTN TgVOID
tgFX__Client__Group_Add_Child(
    TgFX_DATA_INST_ID_C, TgUINT_F32_C , TgFX_CLIENT_INST_ID_C );

TgEXTN TgVOID
tgFX__Client__Group_On_Kill(
    TgFX_CLIENT_INST_ID_C, TgFX_DATA_INST_ID_C, TgFX_DATA_INST_ID_C );


TgEXTN TgVOID
tgFX__Update__Emitter_Add_Particle(
    STg2_FX__Emitter_P, TgRSIZE  );

TgEXTN TgVOID
tgFX__Update__Emitter_Update_Particle(
    STg2_FX__Emitter_P, TgFLOAT32_C, TgVEC_F32_04_1 );

TgEXTN TgVOID
tgFX__File__Particle_Patch_File_Data( 
    STg2_FX_Particle__File_Data_P );


/* ---- System Functions --------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgEXTN TgVOID
tgFX__Client__Update_From_External_Module_Data(
    TgFLOAT32_C );

TgEXTN TgVOID
tgFX__Client__Collect_Collision_Results(
    TgBOOL_C );

TgEXTN TgBOOL
tgFX__Client__Queue_Update_Command(
    ETgFX__EFFECT_C, ETgFX_COMMAND_C, TgVOID_CP );

TgEXTN TgVOID
tgFX__Client__Process_ToClient_Command_Buffer( TgVOID );

#if defined(TgBUILD_FEATURE__GRAPHICS_VFX)

TgEXTN TgRESULT
tgFX__Render__Job__Allocate_Render_Buffers(
    STg2_Job_PC );

TgEXTN TgVOID
tgFX__Render__Submit_Job__Allocate_Render_Buffers(
    STg2_FX_Rnd_Output_PC NONULL ARG0 );

/*# defined(STg2_JobTgBUILD_FEATURE__GRAPHICS_VFX) */
#endif


/* ---- Effect File Data and PreLoad --------------------------------------------------------------------------------------------------------------------------------------------- */

TgINLINE TgVOID
tgFX__Update__Set_Render_Data_From_Material_Hash(
    TgRN_MESH_SET_ID_P, TgRN_MATERIAL_ID_P, ETgKN_GPU_DEFAULT_INPUT_LAYOUT_P, TgUINT_MAX_C );


TgEXTN TgVOID
tgFX_Effect__Increment_Reference(
    TgFX_EFFECT_ID_C );

TgEXTN TgVOID
tgFX_Effect__Decrement_Reference(
    TgFX_EFFECT_ID_C );


TgEXTN TgUINT_F64
tgFX__File__Bind_Effect(
    TgKN_FILE_ID_C, STg2_Input_MEM_PC );

TgEXTN TgVOID
tgFX__File__UnBind_Effect(
    TgSINT_F64_C, TgKN_FILE_ID_C );

TgEXTN TgRESULT
tgFX__Client__UnBind_Effect(
    TgFX_EFFECT_ID_C, TgKN_FILE_ID_C );



/* ---- Utility ------------------------------------------------------------------------------------------------------------------------------------------------------------------ */

/** @brief Using the provided FX animation data, integrate along the function to return the result.
    @param [out] OUT0 Pointer to a location to store the output of the function.
    @param [in] ARG1 Pointer to an FX animation data structure.
    @param [in] ARG2 Floating-point time value to evaluate the provided animation data.
    @param [in] ARG3 Floating-point time step value that was taken to arrive at ARG2.
    @return Result Code. */
TgEXTN TgRESULT
tgFX_Integrate_AnimData_F32_04_1(
    TgVEC_F32_04_1_P NONULL OUT0, STg2_FX_AnimData_P NONULL ARG1, TgVEC_F32_04_1_C ARG2, TgVEC_F32_04_1_C ARG3 );

/** @brief Using the provided FX animation data, evaluate the function at the given time value.
    @param [out] OUT0 Pointer to a location to store the output of the function.
    @param [in] ARG1 Pointer to an FX animation data structure.
    @param [in] ARG2 Floating-point time value to evaluate the provided animation data.
    @return Result Code. */
TgEXTN TgRESULT
tgFX_Evaluate_AnimData_F32_04_1( 
    TgVEC_F32_04_1_P NONULL OUT0, STg2_FX_AnimData_P NONULL ARG1, TgVEC_F32_04_1_C ARG2 );

/** @brief Using the provided FX animation data, evaluate the function at the given time value.
    @param [out] OUT0 Pointer to a location to store the output of the function.
    @param [in] ARG1 Pointer to an FX animation data structure.
    @param [in] ARG2 Floating-point time value to evaluate the provided animation data.
    @return Result Code. */
TgEXTN TgRESULT
tgFX_Evaluate_Single_AnimData_UXX(
    TgUINT_MAX_P NONULL OUT0, STg2_FX_AnimData_P NONULL ARG1, TgFLOAT32_C ARG2 );



/* ---- Generic Effect Functions ------------------------------------------------------------------------------------------------------------------------------------------------- */

#define __PARENT_FILE__ "TgS Effect - Internal.h"
#define ENABLE_RELOAD_GUARD
#include "TgS EFFECT/TgS Effect - Effect [INC].h"
#undef ENABLE_RELOAD_GUARD
#undef __PARENT_FILE__


/* ---- Effect Functions --------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgEXTN TgRSIZE
tgFX_Effect__Beam__Render_Quad_Count(
    STg2_FX__Beam_P );

TgEXTN TgRSIZE
tgFX_Effect__Trail__Render_Quad_Count(
    STg2_FX__Trail_P );


/* ---- Debug -------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

#if TgS_DEBUG__EFFECT
TgEXTN TgVOID
tgFX_Debug__Load_Config( TgVOID );

TgEXTN TgBOOL
tgFX_Debug__Is_Valid(
    TgFX_CLIENT_INST_ID_C, TgFX_DATA_INST_ID_C );

/*# TgS_DEBUG__EFFECT */
#else
#define tgFX_Debug__Is_Valid(...)           true
/*# TgS_DEBUG__EFFECT */
#endif

#if TgS_STAT__EFFECT
    #define STAT(...)                       __VA_ARGS__
/*# TgS_STAT__EFFECT */
#else
    #define STAT(...)
/*# TgS_STAT__EFFECT */
#endif

#define TGS_EFFECT_INTERNAL_H

/*# defined (ENABLE_RELOAD_GUARD) */
#else

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Generic Effect Functions                                                                                                                                                       */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgEXTN TgVOID
T_NAME(tgFX__Client__,_Init)( TgVOID );

TgEXTN TgVOID
T_NAME(tgFX__Client__,_Boot)( TgVOID );

TgEXTN TgVOID
T_NAME(tgFX__Client__,_Stop)( TgVOID );

TgEXTN TgVOID
T_NAME(tgFX__Client__,_Free)( TgVOID );

TgEXTN TgRSIZE
T_NAME(tgFX__Client__,_Query_Fixed_Memory)( TgVOID );

#if T_EFFECT_SCENE && T_EFFECT_RENDER
TgEXTN TgFX_DATA_INST_ID
T_NAME(tgFX__,_Reset_Scene_Particle_Head)(
    ETgFX_UPDATE_C );

TgEXTN TgFX_DATA_INST_ID
T_NAME(tgFX__,_Reset_Scene_Mesh_Head)(
    ETgFX_UPDATE_C );

TgEXTN TgRSIZE
T_NAME(tgFX__,_Scene_Active_Count)(
    ETgFX_UPDATE_C );

/*# T_EFFECT_SCENE && T_EFFECT_RENDER */
#else
TgEXTN TgFX_DATA_INST_ID
T_NAME(tgFX__,_Reset_Scene_Effect_Head)(
    ETgFX_UPDATE_C );
/*# T_EFFECT_SCENE && T_EFFECT_RENDER */
#endif

/** @brief Create an FX instance based on the file data from ARG1 and ARG2 (if needed). 
    @param [in] ARG0 UID on the Client for the FX Instance.
    @param [in] ARG1 Pointer to the file data for the effect.
    @param [in] ARG2 Pointer to a supporting file data for the effect.
    @param [in] ARG3 Pointer to an instance data structure (this is copied internally).
    @return UID in the Data Pool for this instance, on success, and Invalid ID otherwise. */
TgEXTN TgFX_DATA_INST_ID
T_NAME(tgFX__Client__,_Create_Data_Inst)(
    TgFX_CLIENT_INST_ID_C ARG0, TgVOID_CP ARG1, TgVOID_CP ARG2, STg2_FX_Instance_CPCU ARG3 );

TgEXTN TgVOID
T_NAME(tgFX__File__,_Patch_File_Data)(
    T_NAME(STg2_FX_,__File_Data_P) );


TgEXTN TgUINT_F08_P
T_NAME(tgFX_,__Reserve_Update_Command)(
    ETgFX_COMMAND_C );

TgINLINE TgUINT_F08_P
T_NAME(tgFX_,__ToClient__Reserve_Command)(
    ETgFX_COMMAND_C enCommand );


TgINLINE TgBOOL
T_NAME(tgFX__Client__,_ToClient)(
    TgFX_CLIENT_INST_ID_C UNUSED_PARAM tiClient, ETgFX_COMMAND_C enCommand, TgVOID_CP pData );


TgEXTN TgBOOL
T_NAME(tgFX__Update__,_Create_Command)(
    STg2_FX_Instance_CP, TgFX_DATA_INST_ID_C, TgVOID_CP );

TgEXTN TgVOID
T_NAME(tgFX__Update__,_Update)(
    TgVEC_F32_04_1, TgFLOAT32_C, ETgFX_UPDATE_C );


TgINLINE TgVOID
T_NAME(tgFX__Update__Command__,_Create)(
    TgUINT_MAX_C uiHash, STg2_FX_Instance_CP psInstance );

TgINLINE TgVOID
T_NAME(tgFX__Update__Command__,_Free)(
    TgFX_CLIENT_INST_ID_C tiClient, TgFX_DATA_INST_ID_C tiData );

TgINLINE TgVOID
T_NAME(tgFX__Update__Command__,_Notify)(
    STg2_FX_Command__Notify_CP psNotify );


#if T_EFFECT_PROCESS_COMMMAND
TgEXTN TgVOID
T_NAME(tgFX__Update__,_Process_Update_Command)(
    ETgFX_COMMAND_C, TgVOID_CP, TgFX_DATA_INST_ID_C );

#endif

TgEXTN TgRSIZE
T_NAME(tgFX__Update__,_Process_Update_Command_Buffer)(
    TgUINT_F08_CP, TgRSIZE );


TgEXTN TgVOID
T_NAME(tgFX__Update__,_Diag_Check_Effect)(
    TgFX_DATA_INST_ID );


TgEXTN TgVOID
T_NAME(tgFX__Update__,_Kill)(
    TgRSIZE_C  );

TgEXTN TgVOID
T_NAME(tgFX__Update__Command__,_Kill_Self)(
    TgFX_DATA_INST_ID_C );


TgEXTN TgRESULT
T_NAME(tgFX__Update__Job__,_Update)(
    STg2_Job_PC );

TgEXTN TgVOID
T_NAME(tgFX__Update__,_Process_Mark_For_Delete)( TgVOID );

TgEXTN TgVOID
T_NAME(tgFX__Update__,_Process_New_Effects)( TgVOID );

TgEXTN TgVOID
T_NAME(tgFX__Update__,_Update_Finish)( TgVOID );

TgEXTN TgRESULT
T_NAME(tgFX__Update__Job__,_Update_Finish)(
    STg2_Job_PC );



#if T_EFFECT_UPDATE

TgEXTN TgVOID
T_NAME(tgFX__Client__,_Init_Update)( TgVOID );

TgEXTN TgVOID
T_NAME(tgFX__Client__,_Boot_Update)( TgVOID );


TgEXTN TgFX_DATA_INST_ID
T_NAME(tgFX__,_Query_Effect_Update_Head)(
    ETgFX_UPDATE_C );

TgEXTN TgUINT_F08_P
T_NAME(tgFX_,__Reserve_Update_Command)(
    ETgFX_COMMAND_C );


TgEXTN TgBOOL
T_NAME(tgFX__Client__,_Update_Command)(
    ETgFX_COMMAND_C, TgVOID_CP );


TgEXTN TgVOID
T_NAME(tgFX__Client__Submit_Job__,_Update)(
    TgVEC_F32_04_1, TgFLOAT32_C, ETgFX_UPDATE_C );

TgEXTN TgVOID
T_NAME(tgFX__Client__Submit_Job__,_Update_Finish)( TgVOID );

TgEXTN TgRSIZE
T_NAME(tgFX__Update__,_Process_Update_Command_Buffer)(
    TgUINT_F08_CP, TgRSIZE );


#if T_EFFECT_PROCESS_COMMMAND_DEFAULT
TgEXTN TgVOID
T_NAME(tgFX__Update__,_Process_Update_Command_Default)( 
    ETgFX_COMMAND_C, TgVOID_CP, TgFX_DATA_INST_ID_C );

#endif

#if T_EFFECT_TIME_DEFAULT
TgEXTN TgBOOL
T_NAME(tgFX__Update__,_Update_Life_Time)(
    TgRSIZE_C , TgFLOAT32_C, TgVEC_F32_04_1 );

#endif

/*# T_EFFECT_UPDATE */
#endif


#if T_EFFECT_SCENE

TgEXTN TgVOID
T_NAME(tgFX__Client__,_Init_Scene)( TgVOID );

TgEXTN TgVOID
T_NAME(tgFX__Client__,_Boot_Scene)( TgVOID );


TgEXTN TgVOID
T_NAME(tgFX__Client__Submit_Job__,_Refresh_BA)( TgVOID );


#if defined(TgBUILD_FEATURE__GRAPHICS_VFX)
TgEXTN TgVOID
T_NAME(tgFX__Client__Submit_Job__,_Scene_Cull)( 
    STg2_SE_Context_PC, TgRSIZE_C );

TgEXTN TgVOID
T_NAME(tgFX__Client__Submit_Job__,_Scene_Finish)(
    STg2_SE_Context_PC, TgRSIZE_C );

/*# defined(TgBUILD_FEATURE__GRAPHICS_VFX) */
#endif

/*# T_EFFECT_SCENE */
#endif


#if T_EFFECT_RENDER

TgEXTN TgVOID
T_NAME(tgFX__Client__,_Init_Render)( TgVOID );

TgEXTN TgVOID
T_NAME(tgFX__Client__,_Boot_Render)( TgVOID );


TgEXTN TgVOID
T_NAME(tgFX__Render__Submit_Job__,_Process_Headers)(
    STg2_FX_Rnd_Output_PC );

TgEXTN TgVOID
T_NAME(tgFX__Render__Submit_Job__,_Render_Generate)(
    STg2_FX_Rnd_Output_PC );


TgEXTN TgUINT_F32
T_NAME(tgFX__Render__,_Render_Generate_Particle_00)(
    STg2_FX_Rnd_Output_PC, STg2_RN_Particle_Header_PC, T_NAME(STg2_FX__,_P) );

TgEXTN TgUINT_F32
T_NAME(tgFX__Render__,_Render_Generate_Particle_01)(
    STg2_FX_Rnd_Output_PC, STg2_RN_Particle_Header_PC, T_NAME(STg2_FX__,_P) );


/*# T_EFFECT_RENDER */
#endif

#if T_EFFECT_RENDER
TgEXTN TgVOID
T_NAME(tgFX__Scene__,_Cull__Insert_Frame_Mesh)(
    STg2_SE_Context_PC, TgRSIZE_C, TgFX_DATA_INST_ID );

#else
TgEXTN TgVOID
T_NAME(tgFX__Scene__,_Insert_Into_Scene_Context)( TgVOID );
#endif
TgEXTN TgVOID
T_NAME(tgFX_,__Update_BA)(
    TgFX_DATA_INST_ID );


/* =============================================================================================================================================================================== */

/*# defined (ENABLE_RELOAD_GUARD) */
#endif

/*# !defined(TGS_EFFECT_INTERNAL_H) */
#endif
