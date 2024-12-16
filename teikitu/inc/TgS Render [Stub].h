/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Render.h
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.12 | »GUID« 964CB1A6-814D-4E19-8E67-A83FCA98BF05 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_RENDER_H)
#define TGS_RENDER_H
#pragma once


/* == Render ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Types                                                                                                                                                                   */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

#if defined(TgBUILD_FEATURE__GRAPHICS)

TgTYPE_STRUCT(STg2_RN_Particle_Header,)
{
    TgRN_MESH_SET_ID                            m_tiMesh_Set; /**< Mesh ID if the particle is a mesh object */
    TgRN_MATERIAL_ID                            m_tiMaterial;
    TgRSIZE                                     m_uiBuffer_Offset; /**< Offset into the particle buffer */
    TgRSIZE                                     m_nbyVertex; /**< Size of the memory block starting at Offset */
    TgRSIZE                                     m_uiIndex_In_SE_Context; /**< Index of the place holder mesh set in the context */
    TgFLOAT32                                   m_fSE_Quality_Score; /**< Computed quality score of the FX done during Culling. */
    ETgKN_GPU_EXT_TOPOLOGY_TYPE                 m_enPrimitive;
    ETgKN_GPU_DEFAULT_INPUT_LAYOUT              m_enVertex; /**< Vertex type stored in the buffer section */
    TgUINT_E32                                  m_uiGenerated_Vertices;
};

/*# defined(TgBUILD_FEATURE__GRAPHICS) */
#endif



/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Constants                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgEXTN TgRN_MESH_SET_ID_C KTgRN_MESH_SET_ID__PARTICLE;

#if defined(TgBUILD_FEATURE__GRAPHICS)

/* Render System Configuration - Frame Data */
enum { KTgRN_MAX_PRTCL_BUFFER_SIZE          = 64000 }; /**< Number of bytes in the buffer */

enum { KTgRN_DATA_MESH__PARTICLE           = 1 <<  3,
       KTgRN_DATA_MESH__SCREEN_SPACE       = 1 << 22,   /* The mesh should be rendered in screen space */

};

/*# defined(TgBUILD_FEATURE__GRAPHICS) */
#endif




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Module Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/** @brief Standard Module function: First part of initialization process. Set the state of the module.
    @return Result Code. */
TgINLINE TgRESULT
tgRN_Module_Init( TgVOID ) { return KTgS_OK; };

/** @brief Standard Module function: Last part of initialization process. Used for setup and other necessary tasks prior to the use of the module.
    @return Result Code. */
TgINLINE TgRESULT
tgRN_Module_Boot( TgVOID ) { return KTgS_OK; };

/** @brief Standard Module function: Used for close the module as part of the shutdown process. Module is not to be used after this is executed. */
TgINLINE TgVOID
tgRN_Module_Stop( TgVOID ) {};

/** @brief Standard Module function: Final part of shutdown process. Release any remaining allocated memory, and reset the state of the module. */
TgINLINE TgVOID
tgRN_Module_Free( TgVOID ) {};

/** @brief Standard Module function: Update the module, usually called on a per-frame basis, where the parameter is the forward time step amount.
    @param[in] ARG0 Amount of time to step forward the module in milliseconds
    @return Result Code. */
TgINLINE TgRESULT
tgRN_Module_Update(
    TgFLOAT32_C UNUSED_PARAM ARG0 ) { return KTgS_OK; };


/** @brief Standard Module functions: Set the current configuration of the module. */
TgINLINE TgRESULT
tgRN_Load_Config( TgVOID ) { return KTgS_OK; };

/** @brief Standard Module function: Save the current configuration of the module. */
TgINLINE TgRESULT
tgRN_Save_Config( TgVOID ) { return KTgS_OK; };


/** @brief Standard Module function: State query to determine if the module is in the initialized or booted state
    @return True if the module has been initialized, and false otherwise. */
TgINLINE TgBOOL
tgRN_Query_Init( TgVOID ) { return true; };

/** @brief Standard Module function: State query to determine if the module has been booted state
    @return True if the module has been initialized and booted, and false otherwise. */
TgINLINE TgBOOL
tgRN_Query_Boot( TgVOID ) { return true; };

/** @brief Standard Module function: Recall the amount of global (static) memory used by the module
    @return Amount of global (static) memory used by the module. This is hard coded and thus, not explicitly correct. */
TgINLINE TgRSIZE
tgRN_Query_Fixed_Memory( TgVOID ) { return 0u; };



#if defined(TgBUILD_FEATURE__GRAPHICS)

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Render Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */


TgINLINE TgVOID
tgRN_Release_Material(
    TgRN_MATERIAL_ID_C UNUSED_PARAM ARG0 ) {};

TgINLINE TgRN_MATERIAL_ID
tgRN_Hash_Instance_Material(
    TgUINT_MAX_C UNUSED_PARAM ARG0, ETgKN_GPU_DEFAULT_INPUT_LAYOUT_C UNUSED_PARAM ARG1 ) { return KTgRN_MATERIAL_ID__INVALID; };

TgINLINE TgVOID
tgRN_Calc_UV_Animation_F32_04_1(
    TgVEC_F32_04_1_PCU UNUSED_PARAM OUT0, TgVEC_F32_04_1_PCU UNUSED_PARAM OUT1, TgRN_MATERIAL_ID_C UNUSED_PARAM ARG2, TgVEC_F32_04_1 UNUSED_PARAM ARG3, TgVEC_F32_04_1 UNUSED_PARAM ARG4 ) {};

TgINLINE TgBOOL
tgRN_Material__Is_Opaque( 
    TgRN_MATERIAL_ID_C UNUSED_PARAM ARG0 ) { return false; };

TgINLINE TgVOID
tgRN_Release_Mesh_Set(
    TgRN_MESH_SET_ID_C ARG0 ) {};

TgINLINE TgRN_MESH_SET_ID
tgRN_Hash_Instance_Mesh_Set(
    TgUINT_MAX_C ARG0 ) { return KTgRN_MESH_SET_ID__INVALID; };

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Debug Interface                                                                                                                                                                */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
#if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) && TgCOMPILE__RENDER_DEBUG_OUTPUT

TgINLINE TgVOID
tgRN_DBG_Line(
    TgVEC_F32_04_1 UNUSED_PARAM ARG0, TgCOLOUR32_C UNUSED_PARAM ARG1, TgVEC_F32_04_1 UNUSED_PARAM ARG2, TgCOLOUR32_C UNUSED_PARAM ARG3 ) {};

TgINLINE TgVOID
tgRN_DBG_Axes(
    TgVEC_F32_04_3_CPCU UNUSED_PARAM ARG0, TgFLOAT32_C UNUSED_PARAM ARG1 ) {};

TgINLINE TgVOID
tgRN_DBG_Sphere(
    TgCOLOUR32_C UNUSED_PARAM ARG0, TgVEC_F32_04_1 UNUSED_PARAM ARG1, TgFLOAT32_C UNUSED_PARAM ARG2 ) {}

TgINLINE TgVOID
tgRN_DBG_Wireframe_BoxAA(
    TgCOLOUR32_C UNUSED_PARAM ARG0, TgVEC_F32_04_1 UNUSED_PARAM ARG1, TgVEC_F32_04_1 UNUSED_PARAM ARG2 ) {};

/*# defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) && TgCOMPILE__RENDER_DEBUG_OUTPUT */
#endif

/*# defined(TgBUILD_FEATURE__GRAPHICS) */
#endif

/* =============================================================================================================================================================================== */
#endif
