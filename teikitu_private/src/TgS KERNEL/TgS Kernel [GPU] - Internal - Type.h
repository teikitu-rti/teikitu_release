/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Kernel [GPU] - Internal - Type.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_KERNEL_GPU_INTERNAL_TYPE_H) && defined(TgBUILD_FEATURE__GRAPHICS)


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

        STg2_UT_LF__ST_Unaligned_P                  m_psList; /**< Pointer to an atomic lock-less stack that holds the collection of available resource instances. */
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

    #define TGS_KERNEL_GPU_INTERNAL_TYPE_H


    /* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
    /*  Internal Types                                                                                                                                                             */
    /* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

    TgTYPE_FORWARD_STRUCT( STg2_KN_GPU_EXT_CMD );


    /* ---- GPU - Resource - Shader ---------------------------------------------------------------------------------------------------------------------------------------------- */

    typedef enum TgATTRIBUTE_ENUM_FLAG
    {
        ETgKN_GPU_SHADER_FLAGS_START = 0,

        ETgKN_GPU_SHADER_FLAGS_FREE_MEMORY_ON_RELEASE = ETgKN_GPU_SHADER_FLAGS_START,

        ETgKN_GPU_SHADER_FLAGS_END,
        ETgKN_GPU_SHADER_FLAGS_MAX = ETgKN_GPU_SHADER_FLAGS_END,
        ETgKN_GPU_SHADER_FLAGS_COUNT = ETgKN_GPU_SHADER_FLAGS_END - ETgKN_GPU_SHADER_FLAGS_START,
    } ETgKN_GPU_SHADER_FLAGS;
    TgTYPE_MODIFIER_DEFAULT(ETgKN_GPU_SHADER_FLAGS);

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

    TgTYPE_STRUCT(STg2_KN_GPU_VS_DATA,)
    {
        STg2_UT_ST__ST_Node                         m_sNode_Stack;
        struct
        {
            STg2_KN_GPU_SH_DATA                         m_sSH;
        #if 0 != (32 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE)
            TgUINT_E08                                  m_uiPad[32 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE];
        #endif
        };
    };

    TgTYPE_STRUCT(STg2_KN_GPU_TCS_DATA,)
    {
        STg2_UT_ST__ST_Node                         m_sNode_Stack;
        struct
        {
            STg2_KN_GPU_SH_DATA                         m_sSH;
        #if 0 != (32 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE)
            TgUINT_E08                                  m_uiPad[32 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE];
        #endif
        };
    };

    TgTYPE_STRUCT(STg2_KN_GPU_TES_DATA,)
    {
        STg2_UT_ST__ST_Node                         m_sNode_Stack;
        struct
        {
            STg2_KN_GPU_SH_DATA                         m_sSH;
        #if 0 != (32 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE)
            TgUINT_E08                                  m_uiPad[32 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE];
        #endif
        };
    };

    TgTYPE_STRUCT(STg2_KN_GPU_GS_DATA,)
    {
        STg2_UT_ST__ST_Node                         m_sNode_Stack;
        struct
        {
            STg2_KN_GPU_SH_DATA                         m_sSH;
        #if 0 != (32 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE)
            TgUINT_E08                                  m_uiPad[32 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE];
        #endif
        };
    };

    TgTYPE_STRUCT(STg2_KN_GPU_FS_DATA,)
    {
        STg2_UT_ST__ST_Node                         m_sNode_Stack;
        struct
        {
            STg2_KN_GPU_SH_DATA                         m_sSH;
        #if 0 != (32 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE)
            TgUINT_E08                                  m_uiPad[32 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE];
        #endif
        };
    };

    TgTYPE_STRUCT(STg2_KN_GPU_TS_DATA,)
    {
        STg2_UT_ST__ST_Node                         m_sNode_Stack;
        struct
        {
            STg2_KN_GPU_SH_DATA                         m_sSH;
        #if 0 != (32 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE)
            TgUINT_E08                                  m_uiPad[32 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE];
        #endif
        };
    };

    TgTYPE_STRUCT(STg2_KN_GPU_MS_DATA,)
    {
        STg2_UT_ST__ST_Node                         m_sNode_Stack;
        struct
        {
            STg2_KN_GPU_SH_DATA                         m_sSH;
        #if 0 != (32 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE)
            TgUINT_E08                                  m_uiPad[32 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE];
        #endif
        };
    };

    TgTYPE_STRUCT(STg2_KN_GPU_CS_DATA,)
    {
        STg2_UT_ST__ST_Node                         m_sNode_Stack;
        struct
        {
            STg2_KN_GPU_SH_DATA                         m_sSH;
        #if 0 != (32 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE)
            TgUINT_E08                                  m_uiPad[32 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE];
        #endif
        };
    };


    /* ---- GPU - GPU - Sampler -------------------------------------------------------------------------------------------------------------------------------------------------- */

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


    /* ---- GPU - Resource - Texture --------------------------------------------------------------------------------------------------------------------------------------------- */

    /* Base structure for all the texture types */
    TgTYPE_STRUCT(STg2_KN_TX,)
    {
        /* Note: The first eight bytes are used by the resource tracker for invalid resources */

                                                    /* General definition */
        TgUINT_E32                                  m_nuiMIP;
        ETgKN_GPU_EXT_FORMAT                        m_enFormat;

                                                    /* Resource streaming definition. */
        TgUINT_E64                                  m_uiResource_Descriptor;
        TgUINT_E32                                  n_uiPad;
        TgUINT_E32                                  m_uiFlags;
        TgUINT_E32                                  m_uiLast_Touch;
        TgUINT_E32                                  m_uiPriority;
    };

    /** @internal Represents a texture cube data from a backing store like main memory or storage. */
    TgTYPE_STRUCT(STg2_KN_GPU_TX_CBE_DATA,)
    {
        STg2_UT_ST__ST_Node                         m_sNode_Stack;
        struct
        {
            STg2_KN_TX                                  m_sTX;
            TgUINT_E32                                  m_uiEdge;
        #if 0 != (28 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE)
            TgUINT_E08                                  m_uiPad[28 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE];
        #endif
        };
    };

    TgTYPE_STRUCT(STg2_KN_GPU_TX_IMG_DATA,)
    {
        STg2_UT_ST__ST_Node                         m_sNode_Stack;
        struct
        {
            STg2_KN_TX                                  m_sTX;
            TgUINT_E32                                  m_uiWidth, m_uiHeight;
        #if 0 != (24 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE)
            TgUINT_E08                                  m_uiPad[24 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE];
        #endif
        };
    };

    TgTYPE_STRUCT(STg2_KN_GPU_TX_VOL_DATA,)
    {
        STg2_UT_ST__ST_Node                         m_sNode_Stack;
        struct
        {
            STg2_KN_TX                                  m_sTX;
            TgUINT_E32                                  m_uiWidth, m_uiHeight, m_uiDepth;
        #if 0 != (20 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE)
            TgUINT_E08                                  m_uiPad[20 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE];
        #endif
        };
    };

    TgTYPE_STRUCT(STg2_KN_GPU_TX_LOCK,)
    {
        struct {
            TgRSIZE                                     m_nuiRow; /**< Number of rows in this surface/slice. */
            TgRSIZE                                     m_nbyRow; /**< Number of bytes per row. */
            TgRSIZE                                     m_nbyRow_Pitch; /**< Total number of bytes per row. */
        }                                           m_asLayout[KTgKN_GPU_MAX_MIP_LEVELS];

        TgRSIZE                                     m_nuiMip_Levels_Locked; /**< Number of mip levels that are locked. */
        TgRSIZE                                     m_nbyTotal; /**< Total number of \b >bytes< in surface. */
        TgUINT_E08_P                                m_puiData; /**< Pointer to the locked surface layer in main memory. */
        TgUINT_E08                                  m_auiTMP_Upload_Data[64]; /**< API specific data for the upload. */
    };


    /* ---- GPU - Resource - Render Pipeline ------------------------------------------------------------------------------------------------------------------------------------- */

    TgTYPE_STRUCT(STg2_KN_GPU_Graphics_Pipeline,)
    {
        TgUINT_E32                                  m_uiPipeline_Layout;
        ETgKN_GPU_INPUT_LAYOUT                      m_enInput_Layout;
        ETgKN_GPU_EXT_TOPOLOGY                      m_enTopology;
        ETgKN_GPU_RASTERIZER_STATE                  m_enRasterizer_State;
        ETgKN_GPU_BLEND_STATE                       m_enBlend_State;
        ETgKN_GPU_DEPTH_STENCIL_STATE               m_enDepth_State;
        TgUINT_E08                                  m_uiVS;
        TgUINT_E08                                  m_uiTCS;
        TgUINT_E08                                  m_uiTES;
        TgUINT_E08                                  m_uiGS;
        TgUINT_E08                                  m_uiTS;
        TgUINT_E08                                  m_uiMS;
        TgUINT_E08                                  m_uiFS;
        TgUINT_E08                                  m_bUnlit : 1; /* No lighting calculations, just texture fetches */
        TgUINT_E08                                  m_uiPad0 : 7;
        TgCHAR_U8                                   m_uszName[KTgKN_RESOURCE_NAME_MAX];
    };

    TgTYPE_STRUCT(STg2_KN_GPU_Compute_Pipeline,)
    {
        TgUINT_E32                                  m_uiPipeline_Layout;
        TgUINT_E08                                  m_uiCS;
        TgUINT_E08                                  m_uiPad0[3];
        TgCHAR_U8                                   m_uszName[KTgKN_RESOURCE_NAME_MAX];
    };


    /* ---- GPU - Command -------------------------------------------------------------------------------------------------------------------------------------------------------- */

    TgTYPE_STRUCT(STg2_KN_GPU_CMD,) /* A single GPU task (single thread), for a single GPU node */
    {
        STg2_UT_ST__ST_Node_Unaligned               m_sNext;
        TgKN_GPU_CXT_WORK_ID                        m_tiCXT_WORK;

        /* Cached values to simplify working with this command structure for rendering. */

        TgUINT_E32                                  m_uiRender_Target_Width, m_uiRender_Target_Height;
    };


    /* ---- GPU - Contexts ------------------------------------------------------------------------------------------------------------------------------------------------------- */

    /** @internal Represents the physical machine that hosts the GPU hardware, and data managed by its memory controller. In the case of hardware that supports an Unified Memory
                 Architecture then the specific API layer will avoid the memory copy into "video" memory. However, there is still a need to create an instance as this region of 
                memory for the GPU has to be addressed using the configuration of the GPU memory controller and not the CPU memory controller configuration. */
    TgTYPE_STRUCT(STg2_KN_GPU_CXT_HOST,)
    {
        STg2_UT_LF_ISO__RW                          m_sLock; /**< Read-Writer lock for the host context. */
        TgKN_GPU_CXT_HOST_ID_SINGLETON              m_tiCXT_HOST_S; /**< UID Singleton for the host context. */

        STg2_KN_GPU_Physical_Device                 m_asPhysical_Device[KTgKN_GPU_MAX_PHYSICAL_DEVICE]; /**< Physical devices managed by the host context. */
        TgRSIZE                                     m_nuiPhysical_Device; /**< Number of physical devices managed by the host context. */
        STg2_KN_GPU_Display_Output                  m_asDisplay_Output[KTgKN_GPU_MAX_OUTPUT]; /**< Outputs managed by the host context. */
        TgRSIZE                                     m_nuiDisplay_Output; /**< Number of outputs managed by the host context. */

        TgKN_GPU_VS_ID                              m_atiVS[KTgKN_GPU_MAX_VS]; /**< Vertex Shaders managed by the host context. */
        TgRSIZE                                     m_nuiVS; /**< Number of vertex shaders managed by the host context. */
        TgKN_GPU_TCS_ID                             m_atiTCS[KTgKN_GPU_MAX_TCS]; /**< Tesselation control shaders managed by the host context. */
        TgRSIZE                                     m_nuiTCS; /**< Number of tesselation control shaders managed by the host context. */
        TgKN_GPU_TES_ID                             m_atiTES[KTgKN_GPU_MAX_TES]; /**< Tesselation evaluation shaders managed by the host context. */
        TgRSIZE                                     m_nuiTES; /**< Number of tesselation evaluation shaders managed by the host context. */
        TgKN_GPU_GS_ID                              m_atiGS[KTgKN_GPU_MAX_GS]; /**< Geometry shaders managed by the host context. */
        TgRSIZE                                     m_nuiGS; /**< Number of geometry shaders managed by the host context. */
        TgKN_GPU_TS_ID                              m_atiTS[KTgKN_GPU_MAX_TS]; /**< Task Shaders managed by the host context. */
        TgRSIZE                                     m_nuiTS; /**< Number of task shaders managed by the host context. */
        TgKN_GPU_MS_ID                              m_atiMS[KTgKN_GPU_MAX_MS]; /**< Mesh Shaders managed by the host context. */
        TgRSIZE                                     m_nuiMS; /**< Number of mesh shaders managed by the host context. */
        TgKN_GPU_FS_ID                              m_atiFS[KTgKN_GPU_MAX_FS]; /**< Fragment shaders managed by the host context. */
        TgRSIZE                                     m_nuiFS; /**< Number of fragment shaders managed by the host context. */
        TgKN_GPU_CS_ID                              m_atiCS[KTgKN_GPU_MAX_CS]; /**< Compute Shaders managed by the host context. */
        TgRSIZE                                     m_nuiCS; /**< Number of compute shaders managed by the host context. */

        TgKN_GPU_CXT_DEVC_ID                        m_atiCXT_DEVC[KTgKN_GPU_MAX_DEVC_CONTEXT]; /**< Device contexts managed by the host context. */
        TgKN_GPU_CXT_EXEC_ID                        m_atiCXT_EXEC[KTgKN_GPU_MAX_EXEC_CONTEXT]; /**< Execution contexts managed by the host context. */
        TgKN_GPU_CXT_SWAP_ID                        m_atiCXT_SWAP[KTgKN_GPU_MAX_SWAP_CONTEXT]; /**< Swap contexts managed by the host context. */

    #if 0 != (96 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE)
        TgUINT_E08                                  m_uiPad[96 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE];
    #endif
    };
    TgCOMPILER_ASSERT((TgRSIZE)KTgKN_GPU_MAX_VS >= (TgRSIZE)ETgKN_GPU_INPUT_LAYOUT_COUNT,0);
    TgCOMPILER_ASSERT((TgRSIZE)KTgKN_GPU_MAX_FS >= (TgRSIZE)ETgKN_GPU_GRAPHICS_PIPELINE_COUNT,0);

    /** @internal Represents a logical device provisioned by a physical device on the host system. */
    TgTYPE_STRUCT(STg2_KN_GPU_CXT_DEVC,)
    {
        STg2_UT_ST__ST_Node                         m_sNode_Stack;
        struct
        {
            TgKN_GPU_CXT_DEVC_ID_SINGLETON              m_tiCXT_DEVC_S; /**< UID Singleton for the context. */

            TgRSIZE                                     m_idxCXT_HOST_Physical_Device;  /**< Integer index into the array list of the selected adapter. */
        #if 0 != (48 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE)
            TgUINT_E08                                  m_uiPad[48 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE];
        #endif
        };
        TgCXX_CONSTRUCTOR(STg2_KN_GPU_CXT_DEVC() : m_tiCXT_DEVC_S() {})
    };

    /** @internal Represents an execution context on the logical device. This is the context that is used to execute the GPU commands and manage the resources. */
    TgTYPE_STRUCT(STg2_KN_GPU_CXT_EXEC,)
    {
        STg2_UT_ST__ST_Node                         m_sNode_Stack;
        struct
        {
            TgKN_GPU_CXT_EXEC_ID_SINGLETON              m_tiCXT_EXEC_S; /**< UID Singleton for the context. */
            TgKN_GPU_CXT_DEVC_ID                        m_tiCXT_DEVC;
            TgRSIZE                                     m_idxCXT_HOST_Physical_Device;  /**< Integer index into the array list of the selected adapter. */

            TgUINT_E32                                  m_uiNodeMask;
            TgUINT_E32                                  m_nuiMax_Render_Target_View;
            TgUINT_E32                                  m_nuiMax_Depth_Stencil_View;
            TgUINT_E32                                  m_nuiMax_Shader_Resource_View;

            STg2_KN_GPU_TX_IMG_INST_LIB_DESC            m_sTX_IMG_Inst_LIB_DESC;
            STg2_KN_GPU_TX_CBE_INST_LIB_DESC            m_sTX_CBE_Inst_LIB_DESC;
            STg2_KN_GPU_TX_VOL_INST_LIB_DESC            m_sTX_VOL_Inst_LIB_DESC;
            //TgUINT_E08                                  m_auiPad0[8];

        #if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)
            TgRSIZE                                     m_uiDOS_Font_Texture_Index[ETgKN_GPU_DOS_FONT_ROM_COUNT];
        /*# defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
        #endif
        #if 0 != (40 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE)
            TgUINT_E08                                  m_uiPad[40 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE];
        #endif
        };
        TgCXX_CONSTRUCTOR(STg2_KN_GPU_CXT_EXEC() : m_tiCXT_EXEC_S() {})
    };

    /** @internal Represents a swap chain for an execution contexton the logical device. It is used to manage the swap chain and the render targets. */
    TgTYPE_STRUCT(STg2_KN_GPU_CXT_SWAP, )
    {
        STg2_UT_ST__ST_Node                         m_sNode_Stack;
        struct
        {
            TgKN_GPU_CXT_SWAP_ID_SINGLETON              m_tiCXT_SWAP_S; /**< UID Singleton for the context. */
            TgKN_GPU_CXT_EXEC_ID                        m_tiCXT_EXEC;
            TgUINT_PTR                                  m_uiOS_ID;
            TgRSIZE                                     m_idxCXT_HOST_Physical_Device;  /**< Integer index into the array list of the selected adapter. */
            TgRSIZE                                     m_uiCXT_HOST_Output_Index;  /**< Integer index into the array list of the selected output. */

            /* Content Configuration */
            TgFLOAT32                                   m_fMax_Mastering_Nits;
            TgFLOAT32                                   m_fMin_Mastering_Nits;
            TgFLOAT32                                   m_fMax_Content_Light_Level;
            TgFLOAT32                                   m_fMax_Frame_Average_Light_Level;
            TgUINT_E08                                  m_auiPad0[8];

            /* OS Scanout Configuration */
            TgALIGN(16) STg2_KN_GPU_Output_DESC         m_sOutput_DESC;
            TgBOOL                                      m_bOS_Scanout_Valid;
            TgUINT_E08                                  m_auiPad1[3];

            /* Configuration */
            STg2_KN_GPU_Mode                            m_sMode; /**< Selected output mode for the swap chain. */
            TgUINT_E32                                  m_uiMSAA_Sample; /**< Number of MSAA samples to take for the swap chain. */
            ETgKN_GPU_EXT_FORMAT                        m_enFormat_RT; /**< Render target format for the swap chain. */
            ETgKN_GPU_EXT_FORMAT                        m_enFormat_DS; /**< Depth Stencil format for the swap chain. */
            ETgKN_GPU_HLSL_COLOUR_SPACE                 m_enColour_Space; /**< Colour space for the swap chain. */

            TgUINT_E64                                  m_bInit : 1; /**< Have we initialized?. */
            TgUINT_E64                                  m_nuiSwap_Buffers : 8; /**< Number of buffers in the swap chain. */
            TgUINT_E64                                  m_uiStereo : 1; /**< Stereo mode enabled. */
            TgUINT_E64                                  m_uiVSync : 2; /**< VSync method to be used. */
            TgUINT_E64                                  m_bHDR_Request : 1; /**< Use HDR if the output device supports it. */
            TgUINT_E64                                  m_bHDR_Supported : 1; /**< Indicates if the majority of the render surface is on an output device that supports HDR. */
            TgUINT_E64                                  m_bHDR_Enabled : 1; /**< Current swap chain is in HDR. */
            TgUINT_E64                                  m_bFullscreen_Request : 1; /**< Swap chain should be fullscreen (use the entire output device display area). */
            TgUINT_E64                                  m_bFullscreen_Enabled : 1; /**< Current swap chain is in fullscreen. */
            TgUINT_E64                                  m_uiPad_Bit : 47;

            /* Runtime Configuration */
            STg2_KN_GPU_Viewport                        m_sViewport; /**< Viewport for the swap chain. */
            struct {
                TgSINT_E32                                  m_iLeft, m_iTop, m_iRight, m_iBottom;
            }                                           m_sScissor_Rect; /**< Scissor rectangle for the swap chain. */
        #if 0 != (40 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE)
            TgUINT_E08                                  m_uiPad[40 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE];
        #endif
        };
        TgCXX_CONSTRUCTOR(STg2_KN_GPU_CXT_SWAP() : m_tiCXT_SWAP_S() {})
    };


    /* ---- GPU - Resource - Defaults -------------------------------------------------------------------------------------------------------------------------------------------- */




    /* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
    /*  Internal Types for Debug                                                                                                                                                   */
    /* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ____ TgCOMPILE__RENDER_DEBUG_OUTPUT ___________________________________________________________________________________________________________________________________________ */
#if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)

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

    TgTYPE_STRUCT(STg2_KN_GPU_CMD_DBG,)
    {
        STg2_UT_LF__SN                              m_sLine_Lock; /* Lock for access to the debug line rendering system */
        STg2_KN_GPU_DBG_Line_P                      m_psLine;
        TgRSIZE                                     m_nuiLine_Page;
        TgRSIZE_A                                   m_xnuiLine;
    };

    TgTYPE_STRUCT(STg2_KN_GPU_CXT_HOST_DBG,)
    {
        TgKN_GPU_VS_ID                              m_atiVS[ETgKN_GPU_DBG_SHADER_VS_COUNT]; /**< Vertex Shaders managed by the host debug context. */
        TgRSIZE                                     m_nuiVS; /**< Number of vertex shaders managed by the host debug context. */
        TgKN_GPU_TS_ID                              m_atiTS[ETgKN_GPU_DBG_SHADER_TS_COUNT]; /**< Task Shaders managed by the host debug context. */
        TgRSIZE                                     m_nuiTS; /**< Number of task shaders managed by the host debug context. */
        TgKN_GPU_MS_ID                              m_atiMS[ETgKN_GPU_DBG_SHADER_MS_COUNT]; /**< Mesh Shaders managed by the host debug context. */
        TgRSIZE                                     m_nuiMS; /**< Number of mesh shaders managed by the host debug context. */
        TgKN_GPU_FS_ID                              m_atiFS[ETgKN_GPU_DBG_SHADER_FS_COUNT]; /**< Fragment shaders managed by the host debug context. */
        TgRSIZE                                     m_nuiFS; /**< Number of fragment shaders managed by the host debug context. */

        //TgUINT_E08                                  m_auiPad0[32];
    };

/*# defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
#endif
/* ____ TgCOMPILE__RENDER_DEBUG_OUTPUT ___________________________________________________________________________________________________________________________________________ */


/* =============================================================================================================================================================================== */

/*# defined (ENABLE_RELOAD_GUARD) */
#endif

/*# !defined(TGS_KERNEL_INTERNAL_TYPE_GPU_H) && defined(TgBUILD_FEATURE__GRAPHICS) */
#endif
