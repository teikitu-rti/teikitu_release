/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (DX12) Kernel - Type [GPU].h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_DX12_KERNEL_TYPE_GPU_H)
#define TGS_DX12_KERNEL_TYPE_GPU_H


/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal DirectX Type Aliases                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgTYPE_MODIFIER_ALL(ID3DBlob);
TgTYPE_MODIFIER_ALL(ID3D12CommandAllocator);
TgTYPE_MODIFIER_ALL(ID3D12CommandQueue);
TgTYPE_MODIFIER_ALL(ID3D12CommandList);
TgTYPE_MODIFIER_ALL(ID3D12DescriptorHeap);
TgTYPE_MODIFIER_ALL(ID3D12Fence);
TgTYPE_MODIFIER_ALL(ID3D12GraphicsCommandList);
TgTYPE_MODIFIER_ALL(ID3D12GraphicsCommandList8);
TgTYPE_MODIFIER_ALL(ID3D12PipelineState);
TgTYPE_MODIFIER_ALL(ID3D12Resource);
TgTYPE_MODIFIER_ALL(ID3D12Resource1);
TgTYPE_MODIFIER_ALL(ID3D12Resource2);
TgTYPE_MODIFIER_ALL(ID3D12RootSignature);
TgTYPE_MODIFIER_ALL(ID3D12Device10);

TgTYPE_MODIFIER_ALL(D3D12_CPU_DESCRIPTOR_HANDLE);

TgTYPE_DECLARE(D3D12_GRAPHICS_PIPELINE_STATE_DESC, D3D12_GRAPHICS_PSO_DESC);




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Types                                                                                                                                                                   */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- GPU - Context - Miscellaneous -------------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_STRUCT(STg2_KN_GPU_EXT_Heap,)
{
    ID3D12DescriptorHeap_P                      m_psDX12_Heap;
    TgRSIZE                                     m_uiMax;
    TgRSIZE                                     m_nuiMax;
    TgRSIZE                                     m_uiDescriptor_Size;
    D3D12_CPU_DESCRIPTOR_HANDLE                 m_sDX12_CPU_Handle;
};


/* ---- GPU - Contexts - Execution Containers ------------------------------------------------------------------------------------------------------------------------------------ */

TgTYPE_STRUCT(STg2_KN_GPU_EXT_CMD,) /* A single GPU task, for a single GPU node */
{
    TgUINT_E32                                  m_uiPad;
    ETgKN_GPU_EXT_COMMAND                       m_enCmd;
    TgKN_GPU_CXT_WORK_ID                        m_tiCXT_WORK;

    /* TODO: Formulate a heap strategy for memory management. */
    STg2_KN_GPU_EXT_Heap                        m_sEXT_Heap_RTV;
    STg2_KN_GPU_EXT_Heap                        m_sEXT_Heap_CBV_SRV_UAV;

    ID3D12CommandAllocator_P                    m_psDX12_Command_Allocator;
    STg2_UT_ST__ST_Node_P                       m_psNode_Command_Allocator;
    ID3D12GraphicsCommandList8_P                m_psDX12_Graphics_Cmd_List;
    STg2_UT_ST__ST_Node_P                       m_psNode_Graphics_Cmd_List;
    ID3D12Device10_P                            m_psDX12_Device;
};


/*# !defined(TGS_DX12_KERNEL_TYPE_GPU_H) && defined(TgBUILD_FEATURE__GRAPHICS) */
#endif
