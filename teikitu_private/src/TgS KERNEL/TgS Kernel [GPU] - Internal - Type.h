/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Kernel [GPU] - Internal - Type.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_KERNEL_INTERNAL_TYPE_GPU_H) && defined(TgBUILD_FEATURE__GRAPHICS)


/* == Kernel ===================================================================================================================================================================== */
#if defined (ENABLE_RELOAD_GUARD)

#if defined(MACRO_BUILD_TEXTURE)
TgTYPE_STRUCT(T(STg2_KN_GPU_,_INST_LIB_DESC),)
{
    T(TgKN_GPU_,_INST_ID_AP)                    m_pxsID_Inst_Ref_Singleton; /**< Atomic UID and Ref associated with a resource instance. */
    T(TgKN_GPU_,_ID_P)                          m_psRS; /**< UID of the resource associated with a resource instance. */
    TgRSIZE                                     m_nuiRSI; /**< Maximum number of has values (aka resource instances) that can be managed. */

    TgUINT_E64                                  m_uiCXT : KTgKN_GPU_RSI_BIT__MAX_CONTEXT;
    TgUINT_E64                                  m_uiPad_Bit : 62;
    TgUINT_E64_A                                m_xnuiInit;

    TgKN_GPU_CXT_EXEC_ID                        m_tiCXT_EXEC;

    STg2_UT_LF__ST_P                            m_psList; /**< Pointer to an atomic lock-less stack that holds the collection of available resource instances. */
    TgUINT_E08_P                                m_puiData; /**< Pointer to the region of memory that holds the entire set of resource instances managed by this library. */
    TgRSIZE                                     m_uiStride; /**< Integer stride (size) of a single resource instance. */

    TgRSIZE                                     m_uiSize; /**< Total amount of memory managed by the library. */
};
/*# defined(MACRO_BUILD_TEXTURE) */
#endif

/*# defined (ENABLE_RELOAD_GUARD) */
#else

    #define __PARENT_FILE__ "TgS Kernel [GPU] - Internal - Type.h"
    #define ENABLE_RELOAD_GUARD
    #include "TgS KERNEL/TgS Kernel [GPU] - Resource [INC].h"
    #undef ENABLE_RELOAD_GUARD
    #undef __PARENT_FILE__

    #define TGS_KERNEL_INTERNAL_TYPE_GPU_H

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Types                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgTYPE_FORWARD_STRUCT( STg2_KN_GPU_EXT_CMD );


/* ---- GPU - Resource - Shader -------------------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_ENUM_FLAG(ETgKN_GPU_SHADER_FLAGS, TgUINT_E32,
    ETgKN_GPU_SHADER_FLAGS_START = 0,

    ETgKN_GPU_SHADER_FLAGS_FREE_MEMORY_ON_RELEASE = ETgKN_GPU_SHADER_FLAGS_START,

    ETgKN_GPU_SHADER_FLAGS_END,
    ETgKN_GPU_SHADER_FLAGS_MAX = ETgKN_GPU_SHADER_FLAGS_END,
    ETgKN_GPU_SHADER_FLAGS_COUNT = ETgKN_GPU_SHADER_FLAGS_END - ETgKN_GPU_SHADER_FLAGS_START,
);

TgTYPE_STRUCT(STg2_KN_GPU_SH_DATA,)
{
    union
    {
        TgUINT_E08_CP                               m_puiConstData; /**< Shader byte code. */
        TgUINT_E08_P                                m_puiData; /**< Shader byte code. */
    };
    TgRSIZE                                     m_nuiData; /**< Size in \b >bytes< of the shader byte code. */
    TgUINT_E64                                  m_uiFlags;
    TgRSIZE                                     m_uiPad;
};

TgTYPE_STRUCT(STg2_KN_GPU_CS_DATA,)
{
    STg2_KN_GPU_SH_DATA                         m_sSH;
};

TgTYPE_STRUCT(STg2_KN_GPU_DS_DATA,)
{
    STg2_KN_GPU_SH_DATA                         m_sSH;
};

TgTYPE_STRUCT(STg2_KN_GPU_GS_DATA,)
{
    STg2_KN_GPU_SH_DATA                         m_sSH;
};

TgTYPE_STRUCT(STg2_KN_GPU_HS_DATA,)
{
    STg2_KN_GPU_SH_DATA                         m_sSH;
};

TgTYPE_STRUCT(STg2_KN_GPU_PS_DATA,)
{
    STg2_KN_GPU_SH_DATA                         m_sSH;
};

TgTYPE_STRUCT(STg2_KN_GPU_VS_DATA,)
{
    STg2_KN_GPU_SH_DATA                         m_sSH;
};


/* ---- GPU - Resource - Texture ------------------------------------------------------------------------------------------------------------------------------------------------- */

/* Base structure for all the texture types */
TgTYPE_STRUCT(STg2_KN_TX,)
{
    /* Note: The first eight bytes are used by the resource tracker for invalid resources */

                                                /* General definition */
    TgUINT_E32                                  m_nuiMIP;
    ETgKN_GPU_EXT_FORMAT                        m_enFormat;

                                                /* Resource streaming definition. */
    ETgKN_GPU_ALLOCATOR                         m_enAllocator;
    TgUINT_E32                                  m_uiFlags;
    TgUINT_E32                                  m_uiLastTouch;
    TgUINT_E32                                  m_uiPriority;
};

TgTYPE_STRUCT(STg2_KN_GPU_TX_CBE_DATA,)
{
    STg2_KN_TX                                  m_sTX;
    TgUINT_E32                                  m_uiEdge;
    TgUINT_E32                                  m_iPad0;
};

TgTYPE_STRUCT(STg2_KN_GPU_TX_IMG_DATA,)
{
    STg2_KN_TX                                  m_sTX;
    TgUINT_E32                                  m_uiWidth, m_uiHeight;
};

TgTYPE_STRUCT(STg2_KN_GPU_TX_VOL_DATA,)
{
    STg2_KN_TX                                  m_sTX;
    TgUINT_E32                                  m_uiWidth, m_uiHeight, m_uiDepth;
    TgUINT_E32                                  m_iPad0;
};

TgTYPE_STRUCT(STg2_KN_GPU_TX_Surface,)
{
    TgUINT_E32                                  m_uiMIP; /**< MIP layer to lock. */

    TgUINT_E32                                  m_nuiRow; /**< Number of rows. */
    TgUINT_E64                                  m_uiRowPitch; /**< Number of \b >bytes< per row of the texture. */
    TgUINT_E64                                  m_uiMemPitch; /**< Number of \b >bytes< per row of the memory buffer. */
    TgUINT_E64                                  m_nuiTotal; /**< Total number of \b >bytes< in surface. */
    TgUINT_E08_P                                m_puiData; /**< Pointer to the locked surface layer in main memory. */
    TgVOID_P                                    m_psEXT_Object;
};


/* ---- GPU - GPU - State -------------------------------------------------------------------------------------------------------------------------------------------------------- */

//TgTYPE_STRUCT(STg2_KN_GPU_Sampler_State,)
//{
//    ETgKN_GPU_TX_FILTER                         m_enMin, m_enMax, m_enMip;
//    ETgKN_GPU_TX_ADDRESS                        m_enAddress_U;
//    ETgKN_GPU_TX_ADDRESS                        m_enAddress_V;
//    ETgKN_GPU_TX_ADDRESS                        m_enAddress_W;
//    TgFLOAT32                                   m_fBias_MIP_LOD;
//    TgFLOAT32                                   m_afBorder[4];
//    TgFLOAT32                                   m_fMin_LOD, m_fMax_LOD;
//    TgUINT_E32                                  m_uiMax_Anisotropy;
//};


/* ---- GPU - Contexts - Execution Containers ------------------------------------------------------------------------------------------------------------------------------------ */

TgTYPE_STRUCT(STg2_KN_GPU_CMD,) /* A single GPU task, for a single GPU node */
{
    STg2_UT_ST__ST_Node                         m_sNext;
    TgKN_GPU_CXT_WORK_ID                        m_tiCXT_WORK;
};


/* ---- GPU - Contexts ----------------------------------------------------------------------------------------------------------------------------------------------------------- */

/** @brief Represents the physical machine that hosts the GPU hardware, and data managed by its memory controller. In the case of hardware that supports an Unified Memory
           Architecture then the specific API layer will avoid the memory copy into "video" memory. However, there is still a need to create an instance as this region of 
           memory for the GPU has to be addressed using the configuration of the GPU memory controller and not the CPU memory controller configuration. */

TgTYPE_STRUCT(STg2_KN_GPU_CXT_HOST,)
{
    TgKN_GPU_CXT_HOST_ID_SINGLETON              m_tiCXT_HOST_S;

    STg2_KN_GPU_Adapter                         m_asAdapter[KTgKN_GPU_MAX_ADAPTER];
    TgRSIZE                                     m_nuiAdapter;

    TgKN_GPU_VS_ID                              m_atiVS[ETgKN_GPU_DEFAULT_INPUT_LAYOUT_COUNT];
    TgKN_GPU_PS_ID                              m_atiPS[ETgKN_GPU_DEFAULT_PSO_COUNT];

    TgKN_GPU_CXT_DEVC_ID                        m_atiCXT_DEVC[KTgKN_GPU_MAX_DEVC_CONTEXT];
    TgKN_GPU_CXT_EXEC_ID                        m_atiCXT_EXEC[KTgKN_GPU_MAX_EXEC_CONTEXT];
    TgKN_GPU_CXT_SWAP_ID                        m_atiCXT_SWAP[KTgKN_GPU_MAX_SWAP_CONTEXT];
};

TgTYPE_STRUCT(STg2_KN_GPU_CXT_DEVC,)
{
    TgKN_GPU_CXT_DEVC_ID_SINGLETON              m_tiCXT_DEVC_S; /**< UID Singleton for the context. */

    TgUINT_E32                                  m_uiAdapter_Index;  /**< Integer index into the array list of the selected adapter. */
    TgUINT_E32                                  m_uiPad;
};

TgTYPE_STRUCT(STg2_KN_GPU_CXT_EXEC,)
{
    TgKN_GPU_CXT_EXEC_ID_SINGLETON              m_tiCXT_EXEC_S; /**< UID Singleton for the context. */
    TgKN_GPU_CXT_DEVC_ID                        m_tiCXT_DEVC;
    TgUINT_E32                                  m_uiAdapter_Index;  /**< Integer index into the array list of the selected adapter. */
    TgUINT_E32                                  m_uiPad;

    TgUINT_E32                                  m_uiNodeMask;
    TgUINT_E32                                  m_nuiMax_Render_Target_View;
    TgUINT_E32                                  m_nuiMax_Depth_Stencil_View;
    TgUINT_E32                                  m_nuiMax_Shader_Resource_View;

    STg2_KN_GPU_TX_IMG_INST_LIB_DESC            m_sTX_IMG_Inst_LIB_DESC;
    STg2_KN_GPU_TX_CBE_INST_LIB_DESC            m_sTX_CBE_Inst_LIB_DESC;
    STg2_KN_GPU_TX_VOL_INST_LIB_DESC            m_sTX_VOL_Inst_LIB_DESC;
    TgUINT_E08                                  m_auiPad0[8];

#if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)
    STg2_KN_GPU_Vertex_Geom_01                  m_asLine_Vertex[KTgKN_GPU_MAX_DEBUG_LINE_VERTEX_COUNT];
    TgRSIZE                                     m_nuiLine_Vertex;
    TgUINT_E08                                  m_auiPad[24];
    STg2_UT_LF_ISO__SN                          m_sLINE_Lock;
/*# defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
#endif
};

TgTYPE_STRUCT(STg2_KN_GPU_CXT_SWAP,)
{
    TgKN_GPU_CXT_SWAP_ID_SINGLETON              m_tiCXT_SWAP_S; /**< UID Singleton for the context. */
    TgKN_GPU_CXT_EXEC_ID                        m_tiCXT_EXEC;
    TgUINT_PTR                                  m_uiOS_ID;
    TgUINT_E32                                  m_uiAdapter_Index;  /**< Integer index into the array list of the selected adapter. */

    /* Content Configuration */
    TgFLOAT32                                   m_fMax_Mastering_Nits;
    TgFLOAT32                                   m_fMin_Mastering_Nits;
    TgFLOAT32                                   m_fMax_Content_Light_Level;
    TgFLOAT32                                   m_fMax_Frame_Average_Light_Level;

    /* Scanout Configuration */
    TgUINT_E32                                  m_uiBits_Per_Colour;
    ETgKN_GPU_HLSL_COLOR_SPACE                  m_enColour_Space;
    TgFLOAT32                                   m_fRed_Primary[2];
    TgFLOAT32                                   m_fGreen_Primary[2];
    TgFLOAT32                                   m_fBlue_Primary[2];
    TgFLOAT32                                   m_fWhite_Point[2];
    TgFLOAT32                                   m_fMin_Luminance;
    TgFLOAT32                                   m_fMax_Luminance;
    TgFLOAT32                                   m_fMax_Full_Frame_Luminance;
    TgFLOAT32                                   m_fSDR_In_HDR_Nits_Level;
    TgFLOAT32                                   m_fPad;

    /* Configuration */
    TgUINT_E32                                  m_uiScanout_Adapter_Enumeration_Index; /**< Current scanout adapter being used by the majority of the swap chain surface area. */
    TgUINT_E32                                  m_uiScanout_Output_Enumeration_Index; /**< Current scanout output being used by the majority of the swap chain surface area. */
    STg2_KN_GPU_Mode                            m_sMode; /**< Selected output mode for the swap chain. */
    TgUINT_E32                                  m_uiMSAA_Sample; /**< Number of MSAA samples to take for the swap chain. */
    ETgKN_GPU_EXT_FORMAT                        m_enFormat_RT; /**< Render target format for the swap chain. */
    ETgKN_GPU_EXT_FORMAT                        m_enFormat_DS; /**< Depth Stencil format for the swap chain. */

    TgUINT_E64                                  m_nuiSwap_Buffers : 8; /**< Number of buffers in the swap chain. */
    TgUINT_E64                                  m_uiStereo : 1; /**< Stereo mode enabled. */
    TgUINT_E64                                  m_uiVSync : 2; /**< VSync method to be used. */
    TgUINT_E64                                  m_bHDR_Request : 1; /**< Use HDR if the output device supports it. */
    TgUINT_E64                                  m_bHDR_Supported : 1; /**< Indicates if the majority of the render surface is on an output device that supports HDR. */
    TgUINT_E64                                  m_bHDR_Enabled : 1; /**< Current swap chain is in HDR. */
    TgUINT_E64                                  m_bFullscreen_Request : 1; /**< Swap chain should be fullscreen (use the entire output device display area). */
    TgUINT_E64                                  m_bFullscreen_Enabled : 1; /**< Current swap chain is in fullscreen. */
    TgUINT_E64                                  m_uiPad_Bit : 48;

    /* Runtime Configuration */
    STg2_KN_GPU_Viewport                        m_sViewport; /**< Viewport for the swap chain. */
    struct {
        TgSINT_E32                                  m_iLeft, m_iTop, m_iRight, m_iBottom;
    }                                           m_sScissor_Rect; /**< Scissor rectangle for the swap chain. */
};


/* ---- GPU - Resource - Defaults ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ---- GPU - Resource - Debug --------------------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_STRUCT( STg2_KN_GPU_FONT, )
{
    TgUINT_E32_C                                m_uiFntX, m_uiFntY;
    TgRSIZE_C                                   m_uiBufX;
    TgRSIZE_C                                   m_nuiGlyph;
    TgUINT_E08_CPC                              m_puiData;
    TgCHAR_U8_CPC                               m_uszName;
    TgUINT_E32                                  m_uiTX_X, m_uiTX_Y;
    TgUINT_E32                                  m_uiTX_Cell_X, m_uiTX_Cell_Y;
};

TgTYPE_STRUCT( TgKN_GPU_DBG_PM_Generate, )
{
    TgRSIZE                                     m_uiTessellate;
    STg2_KN_GPU_Vertex_Geom_02_P                m_psVertex;
    TgRSIZE                                     m_nuiVertex;
    TgRSIZE                                     m_nuiMax_Vertex;
    TgUINT_E16_P                                m_puiIndex;
    TgRSIZE                                     m_nuiIndex;
    TgRSIZE                                     m_nuiMax_Index;
};


/* =============================================================================================================================================================================== */

/*# defined (ENABLE_RELOAD_GUARD) */
#endif

/*# !defined(TGS_KERNEL_INTERNAL_TYPE_GPU_H) && defined(TgBUILD_FEATURE__GRAPHICS) */
#endif
