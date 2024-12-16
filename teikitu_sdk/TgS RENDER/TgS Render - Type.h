/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Render - Type.h
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.12 | »GUID« 964CB1A6-814D-4E19-8E67-A83FCA98BF05 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_RENDER_TYPE_H) && defined(TgBUILD_FEATURE__GRAPHICS)
#define TGS_RENDER_TYPE_H
#pragma once

#include "TgS Ring 3 - Type.h"


/* == Render ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Types                                                                                                                                                                   */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */



/* ---- Context Parameters ------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_STRUCT(STg2_RN_Cxt_Mesh,)
{
    TgRN_MESH_SET_ID                            m_tiMesh_Set;
    TgUINT_E32                                  m_uiLOD_Index;
    TgUINT_E32                                  m_uiFlags;

    TgVEC_F32_04_1                              m_vScale;
    TgVEC_F32_04_3                              m_xTX; /**< Local transform - this will place the object in world space */
    TgVEC_F32_04_1                              m_vLast_Scale;
    TgVEC_F32_04_3                              m_xLast_TX;

    TgVEC_F32_04_1                              m_vBA_Max_W;
    TgVEC_F32_04_1                              m_vBA_Min_W;

    TgVEC_F32_04_1                              m_vAmbient;
    TgVEC_F32_04_1                              m_vLM; /**< Light map rect (texture space) definition. */
    TgKN_GPU_TX_IMG_ID                              m_tiLM; /**< Default is a black texture */
    TgRN_MATERIAL_ID                            m_tiMaterial;
    TgRSIZE                                     m_auiLight[KTgRN_CXT_MAX_LIGHT_PER_INSTANCE];
    TgRSIZE                                     m_nuiLight;

    TgUINT_E32                                  m_uiSkeleton_0; /**< Body skeleton index used by this mesh, default is -1 (rigid) */
    TgUINT_E32                                  m_uiSkeleton_1; /**< Face skeleton index used by this mesh, default is -1 (rigid) */

    TgFLOAT32                                   m_fOpacity; /**< Default is 1.0 - Used to for mesh specific override (alpha fade). */
    TgUINT_E08                                  m_uiPad_0[12];
};


/* ---- System Data -------------------------------------------------------------------------------------------------------------------------------------------------------------- */

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

TgTYPE_STRUCT(STg2_RN_Text_Header,)
{
    TgUINT_E32                                  m_uiDebug_Field;
    TgSINT_E32                                  m_iX, m_iY;
    TgCOLOUR32                                  m_sColour;
    TgSINT_E32                                  m_iStart_X;
};


/* =============================================================================================================================================================================== */
#endif
