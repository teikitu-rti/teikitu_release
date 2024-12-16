/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Kernel [GPU] - Resource [HLSL] [Data].h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.20 | »GUID« DE461472-5528-4A5B-A7F4-09CCAD73387B */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */

#include "TgS Kernel [GPU] - Resource [HLSL] [Constants].h"


/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Constant Buffers                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgTYPE_HLSL_STRUCT( STg2_KN_GPU_HLSL_Output_DESC, )
{
    TgFLOAT32                                   m_fPerceptual_Exponent;
    TgFLOAT32                                   m_fSDR_In_HDR_Nits_Level;
    ETgKN_GPU_HLSL_COLOR_SPACE                  m_enColour_Space;
    TgUINT_E32                                  m_bHDR_Enabled;

    TgFLOAT32                                   m_fPad;
    TgFLOAT32                                   m_fMin_Luminance;
    TgFLOAT32                                   m_fMax_Luminance;
    TgFLOAT32                                   m_fMax_Full_Frame_Luminance;
};

TgTYPE_HLSL_STRUCT( STg2_KN_GPU_HLSL_CB_Debug_Line, )
{
    STg2_KN_GPU_HLSL_Output_DESC                m_sDESC;
    TgVEC_S_F32_04_4                            m_mW2C, m_mC2S;
};

TgTYPE_HLSL_STRUCT( STg2_KN_GPU_HLSL_CB_Debug_UI, )
{
    STg2_KN_GPU_HLSL_Output_DESC                m_sDESC;
    TgVEC_S_F32_04_1                            m_vRect_UI; /* left, top, right, bottom - X: [-1,1] Y:[-1,1], standard Cartesian */
    TgVEC_S_F32_04_1                            m_vUI_Colour;
    TgUINT_E32                                  m_uiSelect_Default_Texture_Index;
};

TgTYPE_HLSL_STRUCT( STg2_KN_GPU_HLSL_CB_Debug_Text, )
{
    STg2_KN_GPU_HLSL_Output_DESC                m_sDESC;
    TgUINT_E32                                  m_uiSelect_Default_Texture_Index;
    TgUINT_E32                                  m_uiPad;
    TgVEC_S_F32_02_1                            m_vStart_Position_V;
    TgVEC_S_F32_04_1                            m_vFont_Glyph_Scale_S;
    TgVEC_S_F32_04_1                            m_vFont_Glyph_Scale_UV;
    TgVEC_S_F32_04_1                            m_vText_Colour;
    TgVEC_S_F32_04_1                            m_vText_Offset[KTgMACRO_KN_GPU_HLSL_DEBUG_MAX_TEXT_GLYPH];
};

TgTYPE_HLSL_STRUCT( STg2_KN_GPU_HLSL_CB_Debug_Model, )
{
    STg2_KN_GPU_HLSL_Output_DESC                m_sDESC;
    TgVEC_S_F32_04_4                            m_mW2C, m_mC2S;
    TgVEC_S_F32_04_1                            m_vLight_Direction_Colour;
    TgVEC_S_F32_04_1                            m_vLight_Direction;
    TgVEC_S_F32_04_1                            m_vLight_Ambient;
    TgVEC_S_F32_04_4                            m_vModel_Transform;
    TgVEC_S_F32_04_1                            m_vModel_Colour;
};

TgTYPE_HLSL_STRUCT( STg2_KN_GPU_HLSL_CB_Debug_Model_Instance, )
{
    STg2_KN_GPU_HLSL_Output_DESC                m_sDESC;
    TgVEC_S_F32_04_4                            m_mW2C, m_mC2S;
    TgVEC_S_F32_04_1                            m_vLight_Direction_Colour;
    TgVEC_S_F32_04_1                            m_vLight_Direction;
    TgVEC_S_F32_04_1                            m_vLight_Ambient;
    TgVEC_S_F32_04_4                            m_vModel_Transform[KTgMACRO_KN_GPU_HLSL_DEBUG_MAX_MODEL_INSTANCE];
    TgVEC_S_F32_04_1                            m_vModel_Colour[KTgMACRO_KN_GPU_HLSL_DEBUG_MAX_MODEL_INSTANCE];
};
