/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Render.h
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.12 | »GUID« 964CB1A6-814D-4E19-8E67-A83FCA98BF05 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_RENDER_H)
#define TGS_RENDER_H
#pragma once

#include "TgS RENDER/TgS Render - Constants.h"
#include "TgS RENDER/TgS Render - Type.h"
#include "TgS RENDER/TgS Render - Data.h"


/* == Render ===================================================================================================================================================================== */

/*  The goal of this system is to act as a render state manager, and a resource manager for the platform.  Thus, all resources are created through this interface, and all render
   calls are passed through it. The functionality is meant to be fairly high level since the detail implementation will be very platform specific.  Platform specific detail 
   implementation that is outside of the scope of high level implementation will have to acquire the hardware directly and perform the necessary operations. There is no global
   mutex/critical section for the class, but rather its assumed that either operations have no side effects or that the function can only be called by the primary render thread.
   If render operations are being performed outside of the regular main pipeline then very careful care will have to be taken to avoid concurrent render access and manipulation. */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Module Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/** @brief Standard Module function: First part of initialization process. Set the state of the module.
    @return Result Code. */
TgEXTN TgRESULT
tgRN_Module_Init( TgVOID );

/** @brief Standard Module function: Last part of initialization process. Used for setup and other necessary tasks prior to the use of the module.
    @return Result Code. */
TgEXTN TgRESULT
tgRN_Module_Boot( TgVOID );

/** @brief Standard Module function: Used for close the module as part of the shutdown process. Module is not to be used after this is executed. */
TgEXTN TgVOID
tgRN_Module_Stop( TgVOID );

/** @brief Standard Module function: Final part of shutdown process. Release any remaining allocated memory, and reset the state of the module. */
TgEXTN TgVOID
tgRN_Module_Free( TgVOID );

/** @brief Standard Module function: Update the module, usually called on a per-frame basis, where the parameter is the forward time step amount.
    @param[in] ARG0 Amount of time to step forward the module in milliseconds
    @return Result Code. */
TgEXTN TgRESULT
tgRN_Module_Update(
    TgFLOAT32_C ARG0 );


/** @brief Standard Module functions: Set the current configuration of the module. */
TgEXTN TgRESULT
tgRN_Load_Config( TgVOID );

/** @brief Standard Module function: Save the current configuration of the module. */
TgEXTN TgRESULT
tgRN_Save_Config( TgVOID );


/** @brief Standard Module function: State query to determine if the module is in the initialized or booted state
    @return True if the module has been initialized, and false otherwise. */
TgEXTN TgBOOL
tgRN_Query_Init( TgVOID );

/** @brief Standard Module function: State query to determine if the module has been booted state
    @return True if the module has been initialized and booted, and false otherwise. */
TgEXTN TgBOOL
tgRN_Query_Boot( TgVOID );

/** @brief Standard Module function: Recall the amount of global (static) memory used by the module
    @return Amount of global (static) memory used by the module. This is hard coded and thus, not explicitly correct. */
TgEXTN TgRSIZE
tgRN_Query_Fixed_Memory( TgVOID );



#if defined(TgBUILD_FEATURE__GRAPHICS)

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Render Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* -- Resource - Material -------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgEXTN TgVOID
tgRN_Release_Material(
    TgRN_MATERIAL_ID_C ARG0 );

TgEXTN TgRN_MATERIAL_ID
tgRN_Hash_Instance_Material(
    TgUINT_MAX_C ARG0, ETgKN_GPU_DEFAULT_INPUT_LAYOUT_C ARG1 );

TgEXTN TgVOID
tgRN_Calc_UV_Animation_F32_04_1(
    TgVEC_F32_04_1_PCU OUT0, TgVEC_F32_04_1_PCU OUT1, TgRN_MATERIAL_ID_C ARG2, TgVEC_F32_04_1 ARG3, TgVEC_F32_04_1 ARG4 );

TgEXTN TgBOOL
tgRN_Material__Is_Opaque( 
    TgRN_MATERIAL_ID_C ARG0 );


/* -- Resource - Mesh ------------------------------------------------------------------------------------------------------------------------------------------------------------ */


/* -- Resource - Mesh Set -------------------------------------------------------------------------------------------------------------------------------------------------------- */


/** @brief Decrements the reference count of the mesh by one, and frees the resource when the reference count is zero.
    @param [in] ARG0 UID for the mesh to be released. */
TgEXTN TgVOID
tgRN_Release_Mesh_Set(
    TgRN_MESH_SET_ID_C ARG0 );

TgEXTN TgRN_MESH_SET_ID
tgRN_Hash_Instance_Mesh_Set(
    TgUINT_MAX_C ARG0 );

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Debug Interface                                                                                                                                                                */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
#if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) && defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)

/** @brief Attempt to batch the line render together by line type.
    @param [in] ARG0 Vector position 0 of the line in world space.
    @param [in] ARG1 Vector colour for position 0.
    @param [in] ARG2 Vector position 1 of the line in world space.
    @param [in] ARG3 Vector colour for position 1. */
TgEXTN TgVOID
tgRN_DBG_Line(
    TgVEC_F32_04_1 ARG0, TgCOLOUR32_C ARG1, TgVEC_F32_04_1 ARG2, TgCOLOUR32_C ARG3 );

/** @brief Draw Axes
    @param [in] ARG0 Pointer to an transformation matrix containing three eigenvectors.
    @param [in] ARG1 Floating-point scale value used to draw the axes. */
TgEXTN TgVOID
tgRN_DBG_Axes(
    TgVEC_F32_04_3_CPCU ARG0, TgFLOAT32_C ARG1 );

/** @brief Draw a n-sided polygon (planar)
    @param [in] ARG0 Integer 32bit colour value.
    @param [in] ARG1 Pointer to an transformation matrix defining the reference frame.
    @param [in] ARG2 Integer count of the number of sides of the polygon. */
TgEXTN TgVOID
tgRN_DBG_nGon(
    TgCOLOUR32_C ARG0, TgVEC_F32_04_3_CPCU ARG1, TgFLOAT32_C ARG2, TgSINT_E32_C ARG3 );

/** @brief Draw Frustum
    @param [in] ARG0 Integer 32bit colour value.
    @param [in] ARG1 Pointer to a projection matrix.
    @param [in] ARG2 Pointer to a transformation matrix defining the reference frame (camera view).
    @param [in] ARG3 Pointer to an inverse of the projection matrix.
    @param [in] ARG4 Pointer to an inverse of the transformation matrix used to define the reference frame (camera view). */
TgEXTN TgVOID
tgRN_DBG_Frustum(
    TgCOLOUR32_C ARG0, TgVEC_F32_04_4_CPCU ARG1, TgVEC_F32_04_4_CPCU ARG2, TgVEC_F32_04_4_CPCU ARG3, TgVEC_F32_04_4_CPCU ARG4 );

TgEXTN TgVOID
tgRN_DBG_Frustum_Camera(
    TgCOLOUR32_C, STg2_KN_GPU_Camera_CPCU );

TgEXTN TgVOID
tgRN_DBG_Capsule(
    TgCOLOUR32_C, TgVEC_F32_04_3_CPCU, TgFLOAT32_C, TgFLOAT32_C );

TgEXTN TgVOID
tgRN_DBG_Cone(
    TgCOLOUR32_C, TgVEC_F32_04_3_CPCU, TgFLOAT32_C, TgFLOAT32_C );

TgEXTN TgVOID
tgRN_DBG_Cylinder(
    TgCOLOUR32_C, TgVEC_F32_04_3_CPCU, TgFLOAT32_C, TgFLOAT32_C );

TgEXTN TgVOID
tgRN_DBG_Sphere(
    TgCOLOUR32_C, TgVEC_F32_04_1, TgFLOAT32_C );

TgEXTN TgVOID
tgRN_DBG_Tube(
    TgCOLOUR32_C, TgVEC_F32_04_3_CPCU, TgFLOAT32_C, TgFLOAT32_C );

TgEXTN TgVOID
tgRN_DBG_Box(
    TgCOLOUR32_C, TgVEC_F32_04_3_CPCU, TgVEC_F32_04_1 );

TgEXTN TgVOID
tgRN_DBG_Tetrahedron(
    TgCOLOUR32_C, TgVEC_F32_04_3_CPCU, TgFLOAT32_C );

TgEXTN TgVOID
tgRN_DBG_Wireframe_Box(
    TgCOLOUR32_C, TgVEC_F32_04_3_CPCU, TgVEC_F32_04_1 );

TgEXTN TgVOID
tgRN_DBG_Wireframe_Tetrahedron(
    TgCOLOUR32_C, TgVEC_F32_04_3_CPCU, TgFLOAT32_C );


TgEXTN TgVOID
tgRN_DBG_Geom_Capsule(
    TgCOLOUR32_C, TgTUBE_F32_04_CPCU );

TgEXTN TgVOID
tgRN_DBG_Geom_Cylinder(
    TgCOLOUR32_C, TgTUBE_F32_04_CPCU );

TgEXTN TgVOID
tgRN_DBG_Geom_Sphere(
    TgCOLOUR32_C, TgSPHERE_F32_04_CPCU );

TgEXTN TgVOID
tgRN_DBG_Geom_Tube(
    TgCOLOUR32_C, TgTUBE_F32_04_CPCU );

TgEXTN TgVOID
tgRN_DBG_Geom_Box( 
    TgCOLOUR32_C, TgBOX_F32_04_CPCU );

TgEXTN TgVOID
tgRN_DBG_Geom_BoxAA(
    TgCOLOUR32_C, TgBOXAA_F32_04_CPCU );

TgEXTN TgVOID
tgRN_DBG_Geom_Wireframe_Box(
    TgCOLOUR32_C, TgBOX_F32_04_CPCU );

TgEXTN TgVOID
tgRN_DBG_Geom_Wireframe_BoxAA(
    TgCOLOUR32_C, TgBOXAA_F32_04_CPCU );

TgEXTN TgVOID
tgRN_DBG_BoxAA(
    TgCOLOUR32_C, TgVEC_F32_04_1, TgVEC_F32_04_1 );

TgEXTN TgVOID
tgRN_DBG_Wireframe_BoxAA(
    TgCOLOUR32_C, TgVEC_F32_04_1, TgVEC_F32_04_1 );

TgEXTN TgVOID
tgRN_DBG_Text(
    TgSINT_E32_PCU, TgSINT_E32_PCU, TgCOLOUR32_C, TgCHAR_U8_CPCU );

TgEXTN TgVOID
tgRN_DBG_TextF(
    TgSINT_E32_PCU, TgSINT_E32_PCU, TgCOLOUR32_C, TgCHAR_U8_CPCU, ... );

TgEXTN TgVOID
tgRN_DBG_Text_With_Header(
    STg2_RN_Text_Header_PCU, TgCHAR_U8_CPCU );

TgEXTN TgVOID
tgRN_DBG_TextF_With_Header(
    STg2_RN_Text_Header_PCU, TgCHAR_U8_CPCU, ... );

/*# defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) && defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
#endif

/*# defined(TgBUILD_FEATURE__GRAPHICS) */
#endif

/* =============================================================================================================================================================================== */
#endif
