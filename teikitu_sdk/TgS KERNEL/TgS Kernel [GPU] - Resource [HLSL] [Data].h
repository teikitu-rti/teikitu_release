/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Kernel [GPU] - Resource [HLSL] [Data].h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.20 | »GUID« DE461472-5528-4A5B-A7F4-09CCAD73387B */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
#if !defined(TGS_KERNEL_GPU_RESOURCE_HLSL_DATA_H)
#define TGS_KERNEL_GPU_RESOURCE_HLSL_DATA_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "TgS Kernel [GPU] - Resource [HLSL] [Constants].h"


/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Struct Declarations - Shared between GPU and CPU                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
#if defined(KTgMACRO_KN_GPU_VLKN_SHADER_INCLUDE)
    #define HLSL_FRUSTUM_MAX_CONST 6
    #define HLSL_COLOR_SPACE_TYPE TgUINT_E32
#else
    #define HLSL_FRUSTUM_MAX_CONST ETgFRUSTUM_PLANE__MAX
    #define HLSL_COLOR_SPACE_TYPE ETgKN_GPU_HLSL_COLOUR_SPACE
#endif

TgTYPE_HLSL_DECL_STRUCT( Camera_Shared )
{
                                                /* Reference Frame of the Camera */
    TgVEC_F32_04_1                              m_vCam_Right; /**< World space camera right vector */
    TgVEC_F32_04_1                              m_vCam_Up; /**< World space camera up vector */
    TgVEC_F32_04_1                              m_vCam_Forward; /**< World space camera forward vector */

                                                /* Reference Frame Transformations */
    TgVEC_F32_04_4                              m_avW2C; /**< World to Camera (View) */
    TgVEC_F32_04_4                              m_avC2S; /**< Camera to Screen (Projection) */
    TgVEC_F32_04_4                              m_avW2S; /**< World to Screen (View-Projection)*/
    TgVEC_F32_04_4                              m_avC2W; /**< Camera to World (Inverse View) */
    TgVEC_F32_04_4                              m_avS2C; /**< Screen to Camera (Inverse Projection) */
    TgVEC_F32_04_4                              m_avS2W; /**< Screen to World */

                                                /* Frustum bounds */
    TgVEC_F32_04_1                              m_vFrustum_Min_BA, m_vFrustum_Max_BA; /**< Frustum bounds - used for a bounding axis-aligned bounding box. */
    TgVEC_F32_04_1                              m_vFrustum_Centroid; /**< Centre of the frustum - used for a bounding sphere. */
    TgVEC_F32_04_1                              m_vFrustum_Radius_Squared; /**< Centre to bounds - used for bounding sphere. */
    TgVEC_F32_04_1                              m_avFrustum_PN[HLSL_FRUSTUM_MAX_CONST]; /**< Non-Normalized Plane Equations. */
};

TgTYPE_HLSL_DECL_STRUCT( Output_DESC )
{
    TgFLOAT32                                   m_fPerceptual_Exponent;
    TgFLOAT32                                   m_fSDR_In_HDR_Nits_Level;
    TgSINT_E32                                  m_iColour_Space;
    TgSINT_E32                                  m_iBits_Per_Colour;

    TgFLOAT32                                   m_fRed_Primary_0;
    TgFLOAT32                                   m_fRed_Primary_1;
    TgFLOAT32                                   m_fGreen_Primary_0;
    TgFLOAT32                                   m_fGreen_Primary_1;
    TgFLOAT32                                   m_fBlue_Primary_0;
    TgFLOAT32                                   m_fBlue_Primary_1;
    TgFLOAT32                                   m_fWhite_Point_0;
    TgFLOAT32                                   m_fWhite_Point_1;

    TgFLOAT32                                   m_fMin_Luminance;
    TgFLOAT32                                   m_fMax_Luminance;
    TgFLOAT32                                   m_fMax_Full_Frame_Luminance;
    TgFLOAT32                                   m_fPad;
};

TgTYPE_HLSL_DECL_STRUCT( DBG_Render_DESC )
{
                                                /* Debug Lighting Environment: Default setup for lighting environment is a key, fill and rim light. */
    TgVEC_F32_04_1                              m_vLight_Ambient;
    TgVEC_F32_04_1                              m_avLight_Direction_Colour[3]; /**< Assumed to be in G10_P709 */
    TgVEC_F32_04_1                              m_avLight_Direction[3];

                                                /* Debug Render Configuration */
    TgFLOAT32                                   m_fMin_Line_Length; /**< Minimum screen-space line length */
    TgFLOAT32                                   m_fMax_Distance; /**< Maximum culling distance */
    TgFLOAT32                                   m_fGlobal_Line_Width; /**< Global line width multiplier */
    TgFLOAT32                                   m_fPad1;
};

TgTYPE_HLSL_DECL_STRUCT( DBG_Quad )
{
    TgVEC_S_F32_04_1                            m_vRect_UI; /**< left(-1), top(-1), right(1), bottom(1) */
    TgVEC_S_F32_04_1                            m_vUI_Colour; /**< Assumed to be in G10_P709 */
    TgUINT_E32                                  m_uiSelect_Default_Texture_Index;
};

TgTYPE_HLSL_DECL_STRUCT( DBG_Text )
{
    TgVEC_S_F32_04_1                            m_vFont_Glyph_Scale_S;
    TgVEC_S_F32_04_1                            m_vFont_Glyph_Scale_UV;
    TgVEC_S_F32_04_1                            m_vText_Colour; /**< Assumed to be in G10_P709 */
    TgUINT_E32                                  m_uiSelect_Default_Texture_Index;
};

TgTYPE_HLSL_DECL_STRUCT( DBG_Line )
{
    TgVEC_F32_04_1                              m_vStart_Width;
    TgVEC_F32_04_1                              m_vStart_Colour; /**< Assumed to be in G10_P709 */
    TgVEC_F32_04_1                              m_vEnd_Width;
    TgVEC_F32_04_1                              m_vEnd_Colour; /**< Assumed to be in G10_P709 */
};

TgTYPE_HLSL_DECL_STRUCT( DBG_Geom )
{
    TgVEC_F32_04_4                              m_avModel_Transform;
    TgVEC_F32_04_1                              m_vModel_Colour; /**< Assumed to be in G10_P709 */
};




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Storage and Uniform Buffers                                                                                                                                                    */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

#if defined(KTgMACRO_KN_GPU_VLKN_SHADER_INCLUDE)
layout(set = 0, binding = KTgMACRO_KN_GPU_VLKN_BINDING_RENDER_DESC) uniform _Render_DESC
{
    Camera_Shared                               m_sCamera_Shared;
    TgVEC_F32_04_1                              m_vCamera_Position; /**< Camera Position */
    DBG_Render_DESC                             m_sDBG_Render_DESC;
    Output_DESC                                 m_sOutput_DESC;
} Render_DESC;
#else
TgTYPE_HLSL_DECL_STRUCT( Render_DESC )
{
    STg2_KN_GPU_Camera_Shared                   m_sCamera_Shared;
    TgVEC_F32_04_1                              m_vCamera_Position; /**< Camera Position */
    STg2_KN_GPU_DBG_Render_DESC                 m_sDBG_Render_DESC;
    STg2_KN_GPU_Output_DESC                     m_sOutput_DESC;
};

TgTYPE_HLSL_DECL_STRUCT( DBG_Line_Push )
{
    TgUINT_E32                                  m_uiInput_Line_SBO_Offset;
    TgUINT_E32                                  m_nuiLine;
};

TgTYPE_HLSL_DECL_STRUCT( DBG_Text_Push )
{
    TgVEC_S_F32_04_1                            m_vFont_Glyph_Scale_S;
    TgVEC_S_F32_04_1                            m_vFont_Glyph_Scale_UV;
    TgVEC_S_F32_04_1                            m_vText_Colour; /**< Assumed to be in G10_P709 */
    TgUINT_E32                                  m_uiSelect_Default_Texture_Index;
    TgUINT_E32                                  m_uiText_SBO_Offset;
};

TgTYPE_HLSL_DECL_STRUCT( DBG_Geom_Instance_Push )
{
    TgUINT_E32                                  m_uiGeom_SBO_Offset;
};
#endif




/* =============================================================================================================================================================================== */
#endif
