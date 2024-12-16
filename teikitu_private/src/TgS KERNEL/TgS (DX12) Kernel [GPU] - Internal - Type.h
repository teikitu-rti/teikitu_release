/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (DX12) Kernel - Internal - Type [GPU].h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
#if !defined(TGS_DX12_KERNEL_INTERNAL_TYPE_GPU_H)
#define TGS_DX12_KERNEL_INTERNAL_TYPE_GPU_H
#pragma once


/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal DirectX Type Aliases                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* Ancient Base Object Interfaces */

TgTYPE_MODIFIER_ALL(IUnknown);


/* DXGI Interfaces */

TgTYPE_MODIFIER_ALL(IDXGIAdapter);
TgTYPE_MODIFIER_ALL(IDXGIAdapter4);
TgTYPE_MODIFIER_ALL(IDXGIOutput);
TgTYPE_MODIFIER_ALL(IDXGIOutput6);
TgTYPE_MODIFIER_ALL(IDXGISwapChain1);
TgTYPE_MODIFIER_ALL(IDXGISwapChain4);

TgTYPE_MODIFIER_ALL(DXGI_MODE_DESC1);


/* D3D 12 Interfaces - Found in DirectX-Headers */

TgTYPE_MODIFIER_ALL(ID3D12DebugDevice2);
TgTYPE_MODIFIER_ALL(ID3D12InfoQueue1);

TgTYPE_DECLARE(D3D12_VERSIONED_ROOT_SIGNATURE_DESC, D3D12_VER_ROOT_SIG_DESC);
TgTYPE_DECLARE(D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS, D3D12_FD_MSQL);




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Types                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- GPU Configuration -------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_STRUCT(STg2_KN_GPU_EXT_Output,)
{
    /* DirectX */
    IDXGIOutput6_P                              m_psDXGI_Output;
    DXGI_OUTPUT_DESC1                           m_sDXGI_Output;
    TgRSIZE                                     m_uiDXGI_Output_Ordinal;
    TgUINT_E32                                  m_uiWidth;
    TgUINT_E32                                  m_uiHeight;

    DXGI_HDR_METADATA_HDR10                     m_sHDR10;
    TgUINT_E32                                  m_bHDR_Supported : 1; /* Indicates of the device is in HDR. */
    TgUINT_E32                                  m_bReSize : 1;

    /* Enumeration */
    DXGI_MODE_DESC1_P                           m_psDXGI_Mode;
    TgRSIZE                                     m_nuiDXGI_Mode;
    TgRSIZE                                     m_nuiMode_ScanOut[KTgKN_GPU_EXT_FORMAT_RT_SCANOUT_MAX];
};

TgTYPE_STRUCT(STg2_KN_GPU_EXT_Adapter,) /* GPU Adapter - provides scan out to output devices, and one or more GPU nodes */
{
    /* DXGI */
    TgRSIZE                                     m_uiDXGI_Adapter_Ordinal;
    IDXGIAdapter4_P                             m_psDXGI_Adapter;
    DXGI_ADAPTER_DESC3                          m_sDXGI_Adapter;

    /* DirectX */
    ID3D12Device10_P                            m_psDX12_Device;
    D3D12_FEATURE_DATA_SHADER_MODEL             m_sDX12_Shader_Model;
    D3D_FEATURE_LEVEL                           m_enD3D_Feature_Level;
    TgUINT_E32                                  m_uiIsReset : 1;
    TgUINT_E32                                  m_uiIsWARP : 1;
    TgUINT_E32                                  m_uiPad : 30;
    DWORD                                       m_dwCookie;

    /* Enumeration */
    TgUINT_E32                                  m_auiMS[KTgKN_GPU_EXT_FORMAT_RT_SCANOUT_MAX][KTgKN_GPU_MS__MAX];
    STg2_KN_GPU_EXT_Output                      m_asEXT_Output[KTgKN_GPU_MAX_OUTPUT];
    TgRSIZE                                     m_nuiEXT_Output;

    /* Debug / Troubleshooting */
    TgKN_GPU_CXT_DEVC_ID                        m_tiID_DEVC;
};


/* ---- GPU - Resource - Shader -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ---- GPU - Resource - Texture ------------------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_STRUCT(STg2_KN_GPU_EXT_TX_CBE_INST_DATA,)
{
    ID3D12Resource_P                            m_psDX12_Resource;
    TgKN_GPU_TX_CBE_ID                          m_sID;
    TgUINT_E32                                  m_uiNodeMask, m_uiPad;
};

TgTYPE_STRUCT(STg2_KN_GPU_EXT_TX_IMG_INST_DATA,)
{
    ID3D12Resource_P                            m_psDX12_Resource;
    TgKN_GPU_TX_IMG_ID                          m_sID;
    TgUINT_E32                                  m_uiNodeMask, m_uiPad;
};

TgTYPE_STRUCT(STg2_KN_GPU_EXT_TX_VOL_INST_DATA,)
{
    ID3D12Resource_P                            m_psDX12_Resource;
    TgKN_GPU_TX_VOL_ID                          m_sID;
    TgUINT_E32                                  m_uiNodeMask, m_uiPad;
};


/* ---- GPU - Resource - Render Pass Defaults ------------------------------------------------------------------------------------------------------------------------------------ */

TgTYPE_STRUCT(STg2_KN_GPU_EXT_Root_Signature,)
{
    D3D12_DESCRIPTOR_RANGE1                     m_asDX12_Descriptor_Range[4];
    TgRSIZE                                     m_nuiDX12_Descriptor_Range;
    D3D12_ROOT_PARAMETER1                       m_asDX12_Root_Parameter[6];
    TgRSIZE                                     m_nuiDX12_Root_Parameter;
    D3D12_VERSIONED_ROOT_SIGNATURE_DESC         m_sDX12_Root_Signature;
    ID3D12RootSignature_P                       m_psDX12_Root_Signature;
};

TgTYPE_STRUCT(STg2_KN_GPU_PSO_DESC,)
{
    ETgKN_GPU_DEFAULT_ROOT_SIGNATURE            m_enRoot_Signature;
    ETgKN_GPU_DEFAULT_INPUT_LAYOUT              m_enInput_Layout;
    ETgKN_GPU_EXT_TOPOLOGY_TYPE                 m_enTopology_Type;
    ETgKN_GPU_DEFAULT_RASTERIZER_STATE          m_enRasterizer_State;
    ETgKN_GPU_DEFAULT_BLEND_STATE               m_enBlend_State;
    ETgKN_GPU_DEFAULT_DEPTH_STENCIL_STATE       m_enDepth_State;
    TgCHAR_U8                                   m_uszName[KTgKN_RESOURCE_NAME_MAX];
};


/* ---- GPU - Contexts - Execution Containers ------------------------------------------------------------------------------------------------------------------------------------ */

TgTYPE_STRUCT(STg2_KN_GPU_EXT_CMD_Queue,) /* A single GPU task, for a single GPU node */
{
    ID3D12CommandQueue_P                        m_psDX12_Cmd_Queue;
    TgUINT_E64_A                                m_xuiFence_Value;
    ID3D12Fence_P                               m_psDX12_Fence;
    TgVOID_P                                    m_psFence_Event;
};

TgTYPE_STRUCT(STg2_KN_GPU_EXT_ST_Node_Cmd_Allocator,)
{
    STg2_UT_ST__ST_Node                         m_sNext;
    ID3D12CommandAllocator_P                    m_psDX12;
};

TgTYPE_STRUCT(STg2_KN_GPU_EXT_ST_Node_G_Cmd_List,)
{
    STg2_UT_ST__ST_Node                         m_sNext;
    ID3D12GraphicsCommandList8_P                m_psDX12;
};

TgTYPE_STRUCT(STg2_KN_GPU_EXT_CXT_CMD,)
{
    /* Memory Management
       MSFT: Separate descriptor heaps for those being rendered on the GPU and for those being recorded by the CPU, would probably be necessary to avoid conflict. */
    STg2_KN_GPU_EXT_Heap                        m_sRTV, m_sCBV_SRV_UAV;

    /* Synchronization */
    TgUINT_E64                                  m_uiFence_Value_End_Of_Frame[D3D12_COMMAND_LIST_TYPE_VIDEO_ENCODE+1];

    /* Command Allocators
       MSFT Summary: When creating a command list, the command list type of the allocator, specified by D3D12_COMMAND_LIST_TYPE, must match the type of command list being created.
       A given allocator can be associated with no more than one currently recording command list at a time. But calling reset to reclaim the memory used by the allocator, the app
       must make sure that the GPU is no longer executing any command lists which are associated with the allocator. Also, note that this API is not free-threaded and therefore
       can't be called on the same allocator at the same time from multiple threads. */

    STg2_KN_GPU_EXT_ST_Node_Cmd_Allocator       m_asCmd_Allocator__Direct[KTgKN_GPU_EXT_MAX_HIGH_USE_ALLOC];
    STg2_KN_GPU_EXT_ST_Node_Cmd_Allocator       m_asCmd_Allocator__Bundle[KTgKN_GPU_EXT_MAX_HIGH_USE_ALLOC];
    STg2_KN_GPU_EXT_ST_Node_Cmd_Allocator       m_asCmd_Allocator__Compute[KTgKN_GPU_EXT_MAX_HIGH_USE_ALLOC];
    STg2_KN_GPU_EXT_ST_Node_Cmd_Allocator       m_asCmd_Allocator__Copy[KTgKN_GPU_EXT_MAX_HIGH_USE_ALLOC];
    STg2_KN_GPU_EXT_ST_Node_Cmd_Allocator       m_asCmd_Allocator__Video_Decode[KTgKN_GPU_EXT_MAX_LOW_USE_ALLOC];
    STg2_KN_GPU_EXT_ST_Node_Cmd_Allocator       m_asCmd_Allocator__Video_Process[KTgKN_GPU_EXT_MAX_LOW_USE_ALLOC];
    STg2_KN_GPU_EXT_ST_Node_Cmd_Allocator       m_asCmd_Allocator__Video_Encode[KTgKN_GPU_EXT_MAX_LOW_USE_ALLOC];

    /* Command List */
    STg2_KN_GPU_EXT_ST_Node_G_Cmd_List          m_asCmd_List__Direct[KTgKN_GPU_EXT_MAX_GRAPHICS_LIST];
    STg2_KN_GPU_EXT_ST_Node_G_Cmd_List          m_asCmd_List__Bundle[KTgKN_GPU_EXT_MAX_BUNDLE_LIST];
    STg2_KN_GPU_EXT_ST_Node_G_Cmd_List          m_asCmd_List__Compute[KTgKN_GPU_EXT_MAX_COMPUTE_LIST];
    STg2_KN_GPU_EXT_ST_Node_G_Cmd_List          m_asCmd_List__Copy[KTgKN_GPU_EXT_MAX_COPY_LIST];
    STg2_KN_GPU_EXT_ST_Node_G_Cmd_List          m_asCmd_List__Video_Decode[KTgKN_GPU_EXT_MAX_LOW_USE_LIST];
    STg2_KN_GPU_EXT_ST_Node_G_Cmd_List          m_asCmd_List__Video_Process[KTgKN_GPU_EXT_MAX_LOW_USE_LIST];
    STg2_KN_GPU_EXT_ST_Node_G_Cmd_List          m_asCmd_List__Video_Encode[KTgKN_GPU_EXT_MAX_LOW_USE_LIST];

#if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)
    /* Default Resources */
    ID3D12Resource_P                            m_psDX12_CB_Text[KTgKN_GPU_MAX_DEBUG_TEXT];
    TgRSIZE_A                                   m_xuiDX12_CB_Text;
    ID3D12Resource_P                            m_psDX12_CB_UI[KTgKN_GPU_MAX_DEBUG_UI];
    TgRSIZE_A                                   m_xuiDX12_CB_UI;
    ID3D12Resource_P                            m_psDX12_CB_GEOM[KTgKN_GPU_MAX_DEBUG_GEOM];
    TgRSIZE_A                                   m_xuiDX12_CB_GEOM;

    ID3D12Resource_P                            m_psDX12_VB_LINE[KTgKN_GPU_MAX_DEBUG_LINE];
    TgRSIZE_A                                   m_xuiDX12_VB_LINE;
#else
    TgUINT_E08                                  m_uiPad[32];
/*# defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
#endif

    /* Semaphore for multithread ownership. */
    STg1_MT_SM                                  m_sLock;
    TgKN_GPU_CXT_EXEC_ID                        m_tiCXT_EXEC;
    TgKN_GPU_CXT_WORK_ID_SINGLETON              m_tiCXT_WORK_S;

    /* Lock Free Stacks */
    STg2_UT_LF_ISO__ST                          m_sCmd_Allocator_Free_Stack[D3D12_COMMAND_LIST_TYPE_VIDEO_ENCODE+1];
    STg2_UT_LF_ISO__ST                          m_sCmd_List_Used_Stack[D3D12_COMMAND_LIST_TYPE_VIDEO_ENCODE+1];
    STg2_UT_LF_ISO__ST                          m_sCmd_List_Free_Stack[D3D12_COMMAND_LIST_TYPE_VIDEO_ENCODE+1];
};

TgTYPE_STRUCT(STg2_KN_GPU_EXT_Release_Resource,)
{
    ID3D12Resource_P                            m_psDX12_Resource;
    ETgKN_GPU_EXT_COMMAND                       m_enCmd;
    TgUINT_E32                                  m_uiPad;
    TgUINT_E64                                  m_uiFence_Value;
};

TgCOMPILER_ASSERT( offsetof(STg2_KN_GPU_EXT_CMD,m_uiPad) == offsetof(STg2_KN_GPU_CMD,m_sNext), 0 );
TgCOMPILER_ASSERT( offsetof(STg2_KN_GPU_EXT_CMD,m_tiCXT_WORK) == offsetof(STg2_KN_GPU_CMD,m_tiCXT_WORK), 0 );


/* ---- GPU - Contexts - Output Containers --------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_STRUCT(STg2_KN_GPU_EXT_Output_Sync,)
{
    ID3D12CommandAllocator_P                    m_psDX12_Cmd_Allocator_Reserved;
    ID3D12GraphicsCommandList8_P                m_psDX12_Cmd_List[2];
    TgUINT_E64                                  m_uiFence_Value_Present;
    STg2_KN_GPU_EXT_Heap                        m_sRTV;
    ID3D12Resource_P                            m_psDX12_Render_Target_View;
};


/* ---- GPU - Contexts ----------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_STRUCT(STg2_KN_GPU_EXT_CXT_HOST,)
{
    STg2_KN_GPU_EXT_Adapter                     m_asEXT_Adapter[KTgKN_GPU_MAX_ADAPTER];

    /* Debug / Troubleshooting */
    TgKN_GPU_CXT_HOST_ID                        m_tiID;
};


TgTYPE_STRUCT(STg2_KN_GPU_EXT_CXT_DEVC,)
{
    TgUINT_E32                                  m_uiAdapter_Index;

    /* Debug / Troubleshooting */
    TgUINT_E32                                  m_uiPad;
    TgKN_GPU_CXT_DEVC_ID                        m_tiID;
};

TgTYPE_STRUCT(STg2_KN_GPU_EXT_CXT_EXEC,)
{
    /* Configuration Information */
    TgUINT_E32                                  m_uiAdapter_Index;
    TgUINT_E32                                  m_uiNodeMask;

    /* Frame Command Queues */
    STg2_KN_GPU_EXT_CMD_Queue                   m_sCmd_Queue[D3D12_COMMAND_LIST_TYPE_VIDEO_ENCODE+1];
    TgUINT_E08                                  m_uiPad0[24];

    /* Frame Data */
    STg2_KN_GPU_EXT_CXT_CMD                     m_sContext_Command[KTgKN_GPU_MAX_EXEC_CONTEXT_COMMAND];
    TgRSIZE_A                                   m_xuiContext_Command_Index;
    STg2_KN_GPU_EXT_CMD                         m_asComand[KTgKN_GPU_EXT_MAX_COMMAND_LIST];

    /* Default Resources */
    STg2_KN_GPU_EXT_Root_Signature              m_asRoot_Signature[ETgKN_GPU_DEFAULT_ROOT_SIGNATURE_COUNT];
    D3D12_GRAPHICS_PSO_DESC                     m_sDX12_PSO_State[ETgKN_GPU_DEFAULT_PSO_COUNT];
    ID3D12PipelineState_P                       m_psDX12_PSO[ETgKN_GPU_DEFAULT_PSO_COUNT][KTgKN_GPU_EXT_FORMAT_RT_SCANOUT_MAX][KTgKN_GPU_EXT_FORMAT_DS_SCANOUT_MAX];
    ID3D12Resource_P                            m_psDX12_Vertex_Buffer__Text;
    ID3D12Resource_P                            m_psDX12_Vertex_Buffer__UI;
    ID3D12Resource_P                            m_psDX12_Vertex_Buffer__Geom[ETgKN_GPU_DEBUG_PM_3D_COUNT];
    TgRSIZE                                     m_nbyDX12_Vertex_Buffer__Geom[ETgKN_GPU_DEBUG_PM_3D_COUNT];
    ID3D12Resource_P                            m_psDX12_Index_Buffer__Geom[ETgKN_GPU_DEBUG_PM_3D_COUNT];
    TgRSIZE                                     m_nbyDX12_Index_Buffer__Geom[ETgKN_GPU_DEBUG_PM_3D_COUNT];

    /* Debug / Troubleshooting */
    TgKN_GPU_CXT_EXEC_ID                        m_tiID;

    /* Resources */
    struct {
        ID3D12DescriptorHeap_P                      m_psDX12_Heap;
        TgRSIZE                                     m_uiDescriptor_Size;
        TgRSIZE                                     m_anuiMax[KTgKN_GPU_SRV_TYPE_COUNT];
        TgRSIZE                                     m_auiMax[KTgKN_GPU_SRV_TYPE_COUNT];
        D3D12_CPU_DESCRIPTOR_HANDLE                 m_asDX12_CPU[KTgKN_GPU_SRV_TYPE_COUNT];
    }                                           m_sSRV;

    STg2_KN_GPU_EXT_TX_CBE_INST_DATA            m_asTX_CBE_INST[KTgKN_GPU_MAX_TX_CBE_INST];
    STg2_KN_GPU_EXT_TX_IMG_INST_DATA            m_asTX_IMG_INST[KTgKN_GPU_MAX_TX_IMG_INST];
    STg2_KN_GPU_EXT_TX_VOL_INST_DATA            m_asTX_VOL_INST[KTgKN_GPU_MAX_TX_VOL_INST];

    STg2_KN_GPU_EXT_Release_Resource            m_asRelease_Resource[KTgKN_GPU_MAX_RELEASE_RESOURCE];
    TgUINT_E64                                  m_uiRelease_Resource_Producer_Index;
    TgUINT_E64                                  m_uiRelease_Resource_Consumer_Index;
    TgUINT_E08                                  m_uiPad[40];
    STg2_UT_LF_ISO__SN                          m_sRelease_Resource_Lock;

    /* Lock Free Stack */
    STg2_UT_LF_ISO__ST                          m_sCommand_Free_Stack;
};

TgTYPE_STRUCT(STg2_KN_GPU_EXT_CXT_SWAP,) /* An output device attached to a device (single or multi-node). */
{
    /* Swap Chain Configuration */
    DXGI_MODE_DESC1                             m_sDXGI_Mode;
    DXGI_FORMAT                                 m_enDXGI_Format_DS;
    DXGI_FORMAT                                 m_enDXGI_Format_RT;
    TgUINT_E32                                  m_uiPad;
    DXGI_COLOR_SPACE_TYPE                       m_enDXGI_Colour_Space;

    /* Fence for frame swap. */
    TgUINT_E64_A                                m_xuiFence_Value;
    ID3D12Fence_P                               m_psDX12_Fence;
    TgVOID_P                                    m_psFence_Event;

    /* Mutex to prevent re-size operations and final swap from coinciding. */
    STg1_MT_MX                                  m_sSwap_And_View_Lock;

    /* Swap Chain */
    IDXGISwapChain4_P                           m_psDXGI_Swap_Chain;
    ID3D12Resource_P                            m_psDX12_Depth_Stencil;
    STg2_KN_GPU_EXT_Heap                        m_sDSV;

    /* Associated DX12 resources */
    STg2_KN_GPU_EXT_Output_Sync                 m_sCmd[KTgKN_GPU_MAX_BUFFER_IN_FLIP_CHAIN];

    /* Debug / Troubleshooting */
    TgKN_GPU_CXT_SWAP_ID                        m_tiID;
};


/* =============================================================================================================================================================================== */
#endif
