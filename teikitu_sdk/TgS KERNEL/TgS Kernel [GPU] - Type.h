/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Kernel - Type [GPU].h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.20 | »GUID« DE461472-5528-4A5B-A7F4-09CCAD73387B */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_KERNEL_TYPE_GPU_H) && defined(TgBUILD_FEATURE__GRAPHICS)
#if !defined (ENABLE_RELOAD_GUARD)
/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Types                                                                                                                                                                   */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgTYPE_FORWARD_STRUCT( STg2_KN_GPU_CMD );
TgTYPE_FORWARD_STRUCT( STg2_KN_GPU_EXT_CMD );
TgTYPE_UNION( UTg2_KN_GPU_CMD, )
{
    STg2_KN_GPU_CMD_P TgANALYSIS_NO_NULL                    ps;
    STg2_KN_GPU_EXT_CMD_P TgANALYSIS_NO_NULL                psEXT;
};


/* ---- GPU Resource ID ---------------------------------------------------------------------------------------------------------------------------------------------------------- */

#define __PARENT_FILE__ "TgS Kernel [GPU] - Type.h"
#define ENABLE_RELOAD_GUARD
#include "TgS KERNEL/TgS Kernel [GPU] - Resource [INC].h"
#undef ENABLE_RELOAD_GUARD
#undef __PARENT_FILE__

#define TGS_KERNEL_TYPE_GPU_H


/* ---- GPU - Resource - Shader - Descriptors ------------------------------------------------------------------------------------------------------------------------------------ */

TgTYPE_STRUCT(STg2_KN_GPU_CS_DESC,)
{
    TgUINT_E08_CP                               m_puiData; /**< Shader byte code. */
    TgRSIZE                                     m_nuiData; /**< Size in \b >bytes< of the shader byte code. */
    TgCHAR_U8_CP                                m_uszName;
};

TgTYPE_STRUCT(STg2_KN_GPU_DS_DESC,)
{
    TgUINT_E08_CP                               m_puiData; /**< Shader byte code. */
    TgRSIZE                                     m_nuiData; /**< Size in \b >bytes< of the shader byte code. */
    TgCHAR_U8_CP                                m_uszName;
};

TgTYPE_STRUCT(STg2_KN_GPU_GS_DESC,)
{
    TgUINT_E08_CP                               m_puiData; /**< Shader byte code. */
    TgRSIZE                                     m_nuiData; /**< Size in \b >bytes< of the shader byte code. */
    TgCHAR_U8_CP                                m_uszName;
};

TgTYPE_STRUCT(STg2_KN_GPU_HS_DESC,)
{
    TgUINT_E08_CP                               m_puiData; /**< Shader byte code. */
    TgRSIZE                                     m_nuiData; /**< Size in \b >bytes< of the shader byte code. */
    TgCHAR_U8_CP                                m_uszName;
};

TgTYPE_STRUCT(STg2_KN_GPU_PS_DESC,)
{
    TgUINT_E08_CP                               m_puiData; /**< Shader byte code. */
    TgRSIZE                                     m_nuiData; /**< Size in \b >bytes< of the shader byte code. */
    TgCHAR_U8_CP                                m_uszName;
};

TgTYPE_STRUCT(STg2_KN_GPU_VS_DESC,)
{
    TgUINT_E08_CP                               m_puiData; /**< Shader byte code. */
    TgRSIZE                                     m_nuiData; /**< Size in \b >bytes< of the shader byte code. */
    TgCHAR_U8_CP                                m_uszName;
};


/* ---- GPU - Resource - Texture - Descriptors ----------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_STRUCT(STg2_KN_GPU_TX_CBE_DESC,)
{
    TgUINT_E32                                  m_nuiMIP;
    ETgKN_GPU_EXT_FORMAT                        m_enFormat;
    TgUINT_E32                                  m_uiFlags;
    TgUINT_E32                                  m_uiEdge;
    TgCHAR_U8_CP                                m_uszName;
};

TgTYPE_STRUCT(STg2_KN_GPU_TX_IMG_DESC,)
{
    TgUINT_E32                                  m_nuiMIP;
    ETgKN_GPU_EXT_FORMAT                        m_enFormat;
    TgUINT_E32                                  m_uiFlags;
    TgUINT_E32                                  m_uiWidth, m_uiHeight;
    TgUINT_E32                                  m_uiPad0;
    TgCHAR_U8_CP                                m_uszName;
};

TgTYPE_STRUCT(STg2_KN_GPU_TX_VOL_DESC,)
{
    TgUINT_E32                                  m_nuiMIP;
    ETgKN_GPU_EXT_FORMAT                        m_enFormat;
    TgUINT_E32                                  m_uiFlags;
    TgUINT_E32                                  m_uiWidth, m_uiHeight, m_uiDepth;
    TgCHAR_U8_CP                                m_uszName;
};


/* ---- GPU - Resource - Descriptors --------------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_STRUCT(STg2_KN_GPU_RT_DESC,)
{
    TgRSIZE                                     m_uiWidth, m_uiHeight;
    TgUINT_E32                                  m_uiPad;
    ETgKN_GPU_EXT_FORMAT                        m_enFormat_DS;
    ETgKN_GPU_EXT_FORMAT                        m_enFormat_RT[8];
};


/* ---- GPU - Configuration ------------------------------------------------------------------------------------------------------------------------------------------------------ */

TgTYPE_STRUCT(STg2_KN_GPU_Output,)
{
    TgCHAR_U8                                   m_szName[KTgKN_GPU_MAX_OUTPUT_NAME];
    TgUINT_E64                                  m_uiScanOut;
};

TgTYPE_STRUCT(STg2_KN_GPU_Adapter,)
{
    TgCHAR_U8                                   m_szAdapter[KTgKN_GPU_MAX_ADAPTER_NAME];
    STg2_KN_GPU_Output                          m_asOutput[KTgKN_GPU_MAX_OUTPUT];
    TgUINT_E32                                  m_nuiNode;
    TgUINT_E32                                  m_nuiOutput;
    TgUINT_E32                                  m_uiHost_Adapter_Index;
    TgUINT_E32                                  m_uiSupport_Flags;
};

TgTYPE_STRUCT(STg2_KN_GPU_Render_Buffer,)
{
    TgUINT_E32                                  m_uiWidth, m_uiHeight;
    ETgKN_GPU_EXT_FORMAT                        m_enFormat;
};

TgTYPE_STRUCT(STg2_KN_GPU_Mode,)
{
    STg2_KN_GPU_Render_Buffer                   m_sBuffer;
    TgUINT_E32                                  m_uiRefresh_Rate__Numerator, m_uiRefresh_Rate__Denominator;
};

TgTYPE_STRUCT(STg2_KN_GPU_Viewport,)
{
    TgSINT_E32                                  m_iPosX, m_iPosY, m_iWidth, m_iHeight;
    TgFLOAT32                                   m_fMinZ, m_fMaxZ;
};

TgTYPE_STRUCT(STg2_KN_GPU_Select,)
{
    /* Device Context */
    TgRSIZE                                     m_uiEnumeration_Adapter_Index[KTgKN_GPU_MAX_DEVC_CONTEXT]; /**< Index into the enumeration results of the adapter. */
    TgRSIZE                                     m_nuiAdapter;

    /* Execution Context - Each node is assumed to be a separate GPU w/ independent memory controller. */
    struct
    {
        TgRSIZE                                     m_uiAdapter_Index; /**< Adapter index in this structure for the GPU node. */
        TgUINT_E32                                  m_uiAdapter_Node_Mask;
        TgUINT_E32                                  m_nuiRender_Target_Max;
        TgUINT_E32                                  m_nuiDepth_Stencil_Max;
        TgUINT_E32                                  m_nuiData_Buffers_Max;
    }                                           m_sNode[KTgKN_GPU_MAX_EXEC_CONTEXT];
    TgRSIZE                                     m_nuiNode;

    /* Output Context */
    struct
    {
        /* Content Configuration */
        TgFLOAT32                                   m_fMax_Mastering_Nits;
        TgFLOAT32                                   m_fMin_Mastering_Nits;
        TgFLOAT32                                   m_fMax_Content_Light_Level;
        TgFLOAT32                                   m_fMax_Frame_Average_Light_Level;

        TgRSIZE                                     m_uiNode_Index; /**< Node index in this structure for the swap chain. */
        TgUINT_PTR                                  m_uiOS_ID; /**< Application and Window Identifier. */
        STg2_KN_GPU_Mode                            m_sMode;
        TgUINT_E32                                  m_uiMSAA_Sample;
        ETgKN_GPU_EXT_FORMAT                        m_enFormat_DS;
        struct {
            TgUINT_E32                                  m_nuiSwap_Buffers : 8;
            TgUINT_E32                                  m_uiStereo : 1;
            TgUINT_E32                                  m_uiVSync : 2;
            TgUINT_E32                                  m_bHDR_Request : 1;
            TgUINT_E32                                  m_bFullscreen : 1;
            TgUINT_E32                                  m_uiPad : 19;
        }                                           m_uiOutput_Config;
    }                                           m_sOutput[KTgKN_GPU_MAX_SWAP_CONTEXT];
    TgRSIZE                                     m_nuiOutput;
};

TgTYPE_STRUCT(STg2_KN_GPU_Init_Result,)
{
    struct
    {
        TgRSIZE                                     m_uiEnumeration_Adapter_Index; /**< Index into the enumeration results of the adapter. */
        TgKN_GPU_CXT_EXEC_ID                        m_tiCXT_EXEC;
        TgUINT_E32                                  m_uiNodeMask;
        TgUINT_E32                                  m_uiPad;
    }                                           m_sEXEC[KTgKN_GPU_MAX_EXEC_CONTEXT];
    TgRSIZE                                     m_nuiEXEC;

    struct
    {
        TgKN_GPU_CXT_EXEC_ID                        m_tiCXT_EXEC;
        TgUINT_E32                                  m_uiNodeMask;
        TgUINT_E32                                  m_uiPad;
        TgKN_GPU_CXT_SWAP_ID                        m_tiCXT_SWAP;
        TgUINT_PTR                                  m_uiOS_ID;
    }                                           m_sSWAP[KTgKN_GPU_MAX_SWAP_CONTEXT];
    TgRSIZE                                     m_nuiSWAP;
};


/* ---- GPU - Resource - Texture ------------------------------------------------------------------------------------------------------------------------------------------------- */

typedef TgBOOL(*TgKN_GPU_FCN_TX_CBE_LOADER)( TgKN_GPU_TX_CBE_ID_C, TgKN_FILE_ID_C, TgRSIZE_C );
TgTYPE_MODIFIER_DEFAULT(TgKN_GPU_FCN_TX_CBE_LOADER);

typedef TgBOOL(*TgKN_GPU_FCN_TX_IMG_LOADER)( TgKN_GPU_TX_IMG_ID_C, TgKN_FILE_ID_C, TgRSIZE_C );
TgTYPE_MODIFIER_DEFAULT(TgKN_GPU_FCN_TX_IMG_LOADER);

typedef TgBOOL(*TgKN_GPU_FCN_TX_VOL_LOADER)( TgKN_GPU_TX_VOL_ID_C, TgKN_FILE_ID_C, TgRSIZE_C );
TgTYPE_MODIFIER_DEFAULT(TgKN_GPU_FCN_TX_VOL_LOADER);


/* ---- GPU - Contexts ----------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_STRUCT(STg2_KN_GPU_CXT_HOST_EXTN,)
{
    TgKN_GPU_CXT_HOST_EXTN_ID_SINGLETON         m_tiCXT_HOST_EXT_S;

    TgKN_GPU_TX_IMG_ID                          m_sID_TX_IMG_Black_709;
    TgKN_GPU_TX_IMG_ID                          m_sID_TX_IMG_White_709;
    TgKN_GPU_TX_IMG_ID                          m_sID_TX_IMG_Red_709;
    TgKN_GPU_TX_IMG_ID                          m_sID_TX_IMG_Green_709;
    TgKN_GPU_TX_IMG_ID                          m_sID_TX_IMG_Blue_709;
    TgKN_GPU_TX_IMG_ID                          m_sID_TX_IMG_Yellow_709;
    TgKN_GPU_TX_IMG_ID                          m_sID_TX_IMG_Magenta_709;
    TgKN_GPU_TX_IMG_ID                          m_sID_TX_IMG_Cyan_709;

    TgKN_GPU_TX_VOL_ID                          m_sID_TX_VOL_Black_709;
    TgKN_GPU_TX_VOL_ID                          m_sID_TX_VOL_White_709;

    TgKN_GPU_TX_CBE_ID                          m_sID_TX_CBE_Black_709;
    TgKN_GPU_TX_CBE_ID                          m_sID_TX_CBE_White_709;
};

TgTYPE_STRUCT(STg2_KN_GPU_CXT_EXEC_EXTN,)
{
    TgKN_GPU_TX_CBE_INST_ID                     m_sID_TX_CBE_INST_Black_709;
    TgKN_GPU_TX_CBE_INST_ID                     m_sID_TX_CBE_INST_White_709;

    TgKN_GPU_TX_VOL_INST_ID                     m_sID_TX_VOL_INST_Black_709;
    TgKN_GPU_TX_VOL_INST_ID                     m_sID_TX_VOL_INST_White_709;

    TgKN_GPU_TX_IMG_INST_ID                     m_sID_TX_IMG_INST_Black_709;
    TgKN_GPU_TX_IMG_INST_ID                     m_sID_TX_IMG_INST_White_709;
    TgKN_GPU_TX_IMG_INST_ID                     m_sID_TX_IMG_INST_Red_709;
    TgKN_GPU_TX_IMG_INST_ID                     m_sID_TX_IMG_INST_Green_709;
    TgKN_GPU_TX_IMG_INST_ID                     m_sID_TX_IMG_INST_Blue_709;
    TgKN_GPU_TX_IMG_INST_ID                     m_sID_TX_IMG_INST_Yellow_709;
    TgKN_GPU_TX_IMG_INST_ID                     m_sID_TX_IMG_INST_Magenta_709;
    TgKN_GPU_TX_IMG_INST_ID                     m_sID_TX_IMG_INST_Cyan_709;

    TgKN_GPU_TX_IMG_INST_ID                     m_tiTX_IMG_Normal; /**< These is equivalent to a map all in the up direction */
    TgKN_GPU_TX_IMG_INST_ID                     m_tiTX_IMG_Noise;
    TgKN_GPU_TX_IMG_INST_ID                     m_tiTX_IMG_Peturbation;

#if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)
    TgKN_GPU_TX_IMG_INST_ID                     m_sID_Font_ROM__DOS_Font_Default;
    TgKN_GPU_TX_IMG_INST_ID                     m_sID_Font_ROM__DOS_Font_Future;
    TgKN_GPU_TX_IMG_INST_ID                     m_sID_Font_ROM__DOS_Font_Block;
    TgKN_GPU_TX_IMG_INST_ID                     m_sID_Font_ROM__DOS_Font_Marcio;
/*# defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
#endif

#if TgS_DEBUG__KERNEL || TgS_DEBUG__RENDER
                                                /* Reference Image */
    TgKN_GPU_TX_IMG_INST_ID                     m_sID_TX_IMG_INST_Reference_G10_P709_00;

                                                /* MIP Debug Textures - For viewing the MIP state in real-time. */
    TgKN_GPU_TX_IMG_INST_ID                     m_sID_TX_IMG_INST_MIP_1024x1024;
    TgKN_GPU_TX_IMG_INST_ID                     m_sID_TX_IMG_INST_MIP_0512x0512;
    TgKN_GPU_TX_IMG_INST_ID                     m_sID_TX_IMG_INST_MIP_0256x0256;
    TgKN_GPU_TX_IMG_INST_ID                     m_sID_TX_IMG_INST_MIP_0128x0128;
    TgKN_GPU_TX_IMG_INST_ID                     m_sID_TX_IMG_INST_MIP_0064x0064;

                                                /* Test and Error Textures */
    TgKN_GPU_TX_IMG_INST_ID                     m_sID_TX_IMG_INST_Gamma_Test;
    TgKN_GPU_TX_IMG_INST_ID                     m_sID_TX_IMG_INST_Target; /**< Used for non-diffuse surfaces (including normal and specular) */
    TgKN_GPU_TX_IMG_INST_ID                     m_sID_TX_IMG_INST_Error; /**< Checkerboard pattern (used primarily for diffuse) */
    TgKN_GPU_TX_CBE_INST_ID                     m_sID_TX_CBE_INST_Error;

                                                /* Colour Standard for colour image balancing during development. */
    TgKN_GPU_TX_IMG_INST_ID                     m_sID_TX_IMG_INST_Standard_1080;
    TgKN_GPU_TX_IMG_INST_ID                     m_sID_TX_IMG_INST_Standard_0720;
    TgKN_GPU_TX_IMG_INST_ID                     m_sID_TX_IMG_INST_Standard_NTSC;
    TgKN_GPU_TX_IMG_INST_ID                     m_sID_TX_IMG_INST_Standard_PAL;
//# TgS_DEBUG__KERNEL || TgS_DEBUG__RENDER
#endif 
};


/* ---- GPU - Resource - Defaults ------------------------------------------------------------------------------------------------------------------------------------------------ */

#define RENDER_INPUT_LAYOUT_START(A,B) TgTYPE_STRUCT(STg2_KN_GPU_##A,) {
#define RENDER_INPUT_LAYOUT_PER_VERTEX(A, B, C, D, E, F, G, ...) G __VA_ARGS__;
#define RENDER_INPUT_LAYOUT_PER_VERTEX_APPEND(A, B, C, D, F, G, ...) G __VA_ARGS__;
#define RENDER_INPUT_LAYOUT_END(A) };
#define RENDER_INPUT_ALIGNMENT_CHECK(A,B) TgCOMPILER_ASSERT(A == sizeof(STg2_KN_GPU_##B), 0 );

#include "TgS KERNEL/TgS Kernel [GPU] - Resource [HLSL] [Vertex].h"

#undef RENDER_INPUT_ALIGNMENT_CHECK
#undef RENDER_INPUT_LAYOUT_END
#undef RENDER_INPUT_LAYOUT_PER_VERTEX_APPEND
#undef RENDER_INPUT_LAYOUT_PER_VERTEX
#undef RENDER_INPUT_LAYOUT_START

#define TgTYPE_HLSL_STRUCT(A, ...) TgTYPE_STRUCT_( A, __VA_ARGS__ )
#include "TgS KERNEL/TgS Kernel [GPU] - Resource [HLSL] [Data].h"
#undef TgTYPE_HLSL_STRUCT
TgTYPE_DECLARE( STg2_KN_GPU_HLSL_CB_Debug_Model_Instance, STg2_KN_GPU_HLSL_CB_DMI);


/* ---- GPU - Resource - Font ---------------------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_STRUCT(STg2_KN_GPU_FONT_TX,)
{
    TgFLOAT32                                   m_fFntX, m_fFntY;
    TgFLOAT32                                   m_fTX_X, m_fTX_Y;
    TgFLOAT32                                   m_fTX_Cell_X, m_fTX_Cell_Y;
};


/* ---- GPU - Resource - Debug --------------------------------------------------------------------------------------------------------------------------------------------------- */
#if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)

TgTYPE_STRUCT(STg2_KN_GPU_OUTPUT_DEBUG_STRING,)
{
    STg2_KN_GPU_HLSL_Output_DESC                m_sOutput_DESC;
    STg2_KN_GPU_Render_Buffer                   m_sRTBuffer;
    STg2_KN_GPU_Render_Buffer                   m_sDSBuffer;
    ETgKN_GPU_DOS_FONT_ROM                      m_enFont;
    TgUINT_E32                                  m_bWord_Wrap : 1;
    TgUINT_E32                                  m_bLine_Change_Is_Positive : 1;
    TgUINT_E32                                  m_bDraw_Background : 1;
    TgUINT_E32                                  m_bDraw_First_Line : 1;
    TgUINT_E32                                  m_bRight_Aligned : 1;
    TgUINT_E32                                  m_bText_Right_To_Left : 1;
    TgUINT_E32                                  m_uiPad_Bits : 26;
    TgCHAR_U8_CP                                m_auszText[KTgKN_GPU_MAX_DEBUG_TEXT];
    TgRSIZE                                     m_nuiText;
    TgVEC_S_F32_04_1                            m_vText_Box_V;
    TgVEC_S_F32_04_1                            m_vText_Colour;
    TgVEC_S_F32_04_1                            m_vBackground_Colour;
    TgVEC_S_F32_04_1                            m_vBackground_First_Line;
};

TgTYPE_STRUCT(STg2_KN_GPU_OUTPUT_DEBUG_LINE,)
{
    STg2_KN_GPU_HLSL_Output_DESC                m_sOutput_DESC;
    STg2_KN_GPU_Render_Buffer                   m_sRTBuffer;
    STg2_KN_GPU_Render_Buffer                   m_sDSBuffer;
};

TgTYPE_STRUCT(STg2_KN_GPU_OUTPUT_DEBUG_GEOM,)
{
    STg2_KN_GPU_HLSL_Output_DESC                m_sOutput_DESC;
    STg2_KN_GPU_Render_Buffer                   m_sRTBuffer;
    STg2_KN_GPU_Render_Buffer                   m_sDSBuffer;
    STg2_KN_GPU_HLSL_CB_Debug_Model_CP          m_psCB_DBG_Model;
    STg2_KN_GPU_HLSL_CB_Debug_Model_Instance_CP m_psCB_DBG_Model_Instance;
};

/*# defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
#endif


/* ---- GPU - Render Primitives -------------------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_STRUCT(STg2_KN_GPU_Camera_Configuration,)
{
    TgUN_V128                                   m_uCam_Position; /**< World space position of the camera */
    TgUN_V128                                   m_uCam_Target; /**< World space target of the camera */

                                                /* Parameters used to calculate the projection matrix */
    TgFLOAT32                                   m_fAspect_Ratio;
    TgFLOAT32                                   m_fFoV;
    TgFLOAT32                                   m_fNear, m_fFar;
};

/* Camera Parameter - This is the minimal representation for use by the render module.  It is assumed to be in the current render view as established in the rendering system
   (perspective or orthographic). */
TgTYPE_STRUCT(STg2_KN_GPU_Camera,)
{
    STg2_KN_GPU_Camera_Configuration            m_sCamera;

                                                /* Reference Frame of the Camera */
    TgVEC_F32_04_1                              m_vCam_Forward; /**< World space camera forward vector */
    TgVEC_F32_04_1                              m_vCam_Up; /**< World space camera up vector */
    TgVEC_F32_04_1                              m_vCam_Right; /**< World space camera right vector */

                                                /* Reference Frame Transformations */
    TgVEC_F32_04_4                              m_xFrustum_W2C; /**< World to Camera (View) */
    TgVEC_F32_04_4                              m_xFrustum_C2S; /**< Camera to Screen (Projection) */
    TgVEC_F32_04_4                              m_xFrustum_W2S; /**< World to Screen */
    TgVEC_F32_04_4                              m_xFrustum_C2W; /**< Camera to World (Inverse View) */
    TgVEC_F32_04_4                              m_xFrustum_S2C; /**< Screen to Camera (Inverse Projection) */
    TgVEC_F32_04_4                              m_xFrustum_S2W; /**< Screen to World */

                                                /* Frustum description */
    TgVEC_F32_04_1                              m_vFrustum_Min_BA, m_vFrustum_Max_BA; /**< Frustum bounds - used for a bounding axis-aligned bounding box. */
    TgVEC_F32_04_1                              m_vFrustum_Centroid; /**< Centre of the frustum - used for a bounding sphere. */
    TgVEC_F32_04_1                              m_avFrustum_PN[ETgFRUSTUM_PLANE__MAX]; /**< Non-Normalized Plane Equations. */
    TgFLOAT32                                   m_fFrustum_Radius_Squared; /**< Centre to bounds - used for bounding sphere. */

    TgCHAR_U8                                   m_szName[44];
};


/*# defined (ENABLE_RELOAD_GUARD) */
#else

/* ---- GPU Resource ID ---------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_UNION(T(TgKN_GPU_,_ID),)
{
    TgALIGN(8) TgUINT_E64                   m_uiKI;
    struct {
        TgUINT_E64                                  m_uiIndex : KTgKN_GPU_RS_BIT__MAX_INDEX; /**< Index identification of object within storage array. */
        TgUINT_E64                                  m_uiK : KTgKN_GPU_RS_BIT__SALT; /**< Salt value to prevent ABA atomic issues. */
        TgUINT_E64                                  m_uiLoad : KTgKN_GPU_RS_BIT__LOAD; /**< Salt value to prevent ABA atomic issues. */
        TgUINT_E64                                  m_uiFree : KTgKN_GPU_RS_BIT__FREE; /**< Salt value to prevent ABA atomic issues. */
        TgUINT_E64                                  m_uiRef : KTgKN_GPU_RS_BIT__REFERENCE_COUNT; /**< Reference count of the object. */
    };
};
TgTYPE_MODIFIER_ALL(T(TgKN_GPU_,_ID));
TgEXTN T(TgKN_GPU_,_ID_C) T(KTgKN_GPU_,_ID__INVALID);

TgTYPE_UNION(T(TgKN_GPU_,_INST_ID),)
{
    TgALIGN(8) TgUINT_E64                   m_uiKI;
    struct {
        TgUINT_E64                                  m_uiIndex : KTgKN_GPU_RSI_BIT__MAX_INDEX; /**< Index identification of object within storage array. */
        TgUINT_E64                                  m_uiCXT : KTgKN_GPU_RSI_BIT__MAX_CONTEXT; /**< Index identification of the backing (resource) library. */
        TgUINT_E64                                  m_uiK : KTgKN_GPU_RSI_BIT__SALT; /**< Salt value to prevent ABA atomic issues. */
        TgUINT_E64                                  m_uiLoad : KTgKN_GPU_RSI_BIT__LOAD; /**< Salt value to prevent ABA atomic issues. */
        TgUINT_E64                                  m_uiFree : KTgKN_GPU_RSI_BIT__FREE; /**< Salt value to prevent ABA atomic issues. */
        TgUINT_E64                                  m_uiRef : KTgKN_GPU_RSI_BIT__REFERENCE_COUNT; /**< Reference count of the object. */
    };
};
TgTYPE_MODIFIER_ALL(T(TgKN_GPU_,_INST_ID));
TgEXTN T(TgKN_GPU_,_INST_ID_C) T(KTgKN_GPU_,_INST_ID__INVALID);


/* =============================================================================================================================================================================== */

/*# defined (ENABLE_RELOAD_GUARD) */
#endif

/*# !defined(TGS_KERNEL_TYPE_GPU_H) && defined(TgBUILD_FEATURE__GRAPHICS) */
#endif
