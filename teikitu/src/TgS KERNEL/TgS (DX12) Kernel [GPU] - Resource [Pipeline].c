/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (DX12) Kernel - Resource [GPU] [Pipeline].c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Constants                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#define RENDER_INPUT_LAYOUT_START(A,B)                              static const D3D12_INPUT_ELEMENT_DESC sDX12_Input_Layout_##A[] = {
#define RENDER_INPUT_LAYOUT_PER_VERTEX(A, B, C, D, E, F, G, ...)        { #A, B, (DXGI_FORMAT)C, D, E, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, F },
#define RENDER_INPUT_LAYOUT_PER_VERTEX_APPEND(A, B, C, D, F, G, ...)    { #A, B, (DXGI_FORMAT)C, D, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, F },
#define RENDER_INPUT_LAYOUT_END(A)                                  };
#define RENDER_INPUT_ALIGNMENT_CHECK(A,B)

    #include "TgS KERNEL/TgS Kernel [GPU] - Resource [HLSL] [Vertex].h"

#undef RENDER_INPUT_ALIGNMENT_CHECK
#undef RENDER_INPUT_LAYOUT_END
#undef RENDER_INPUT_LAYOUT_PER_VERTEX_APPEND
#undef RENDER_INPUT_LAYOUT_PER_VERTEX
#undef RENDER_INPUT_LAYOUT_START


#define RENDER_INPUT_LAYOUT_START(A,B)                              static const D3D12_INPUT_ELEMENT_DESC sDX12_Input_Layout_Instance_##A[] = {
#define RENDER_INPUT_LAYOUT_PER_VERTEX(A, B, C, D, E, F, G, ...)        { #A, B, (DXGI_FORMAT)C, D, E, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, F },
#define RENDER_INPUT_LAYOUT_PER_VERTEX_APPEND(A, B, C, D, F, G, ...)    { #A, B, (DXGI_FORMAT)C, D, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, F },
#define RENDER_INPUT_LAYOUT_END(A)                                      { "SV_InstanceID", 0, DXGI_FORMAT_R32_UINT, 1, 0, D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA, 1 }         \
                                                                    };
#define RENDER_INPUT_ALIGNMENT_CHECK(A,B)

    #include "TgS KERNEL/TgS Kernel [GPU] - Resource [HLSL] [Vertex].h"

#undef RENDER_INPUT_ALIGNMENT_CHECK
#undef RENDER_INPUT_LAYOUT_END
#undef RENDER_INPUT_LAYOUT_PER_VERTEX_APPEND
#undef RENDER_INPUT_LAYOUT_PER_VERTEX
#undef RENDER_INPUT_LAYOUT_START

#define RENDER_INPUT_LAYOUT_PER_VERTEX(A, B, C, D, E, F, G, ...)
#define RENDER_INPUT_LAYOUT_PER_VERTEX_APPEND(A, B, C, D, F, G, ...)
#define RENDER_INPUT_LAYOUT_END(A)
#define RENDER_INPUT_ALIGNMENT_CHECK(A,B)

static const D3D12_INPUT_LAYOUT_DESC s_asKN_GPU_EXT_Input_Layout[ETgKN_GPU_DEFAULT_INPUT_LAYOUT_COUNT] = {
    #define RENDER_INPUT_LAYOUT_START(A,B) { .pInputElementDescs = sDX12_Input_Layout_##A, .NumElements = TgARRAY_COUNT(sDX12_Input_Layout_##A) },
    #include "TgS KERNEL/TgS Kernel [GPU] - Resource [HLSL] [Vertex].h"
    #undef RENDER_INPUT_LAYOUT_START
    #define RENDER_INPUT_LAYOUT_START(A,B) { .pInputElementDescs = sDX12_Input_Layout_Instance_##A, .NumElements = TgARRAY_COUNT(sDX12_Input_Layout_Instance_##A) },
    #include "TgS KERNEL/TgS Kernel [GPU] - Resource [HLSL] [Vertex].h"
    #undef RENDER_INPUT_LAYOUT_START
};

#undef RENDER_INPUT_ALIGNMENT_CHECK
#undef RENDER_INPUT_LAYOUT_END
#undef RENDER_INPUT_LAYOUT_PER_VERTEX_APPEND
#undef RENDER_INPUT_LAYOUT_PER_VERTEX




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

static TgVOID
tgKN_GPU_EXT_Initialize_Default_Root_Signature_Description__Debug(
    TgKN_GPU_CXT_EXEC_ID_C ARG0, ETgKN_GPU_DEFAULT_ROOT_SIGNATURE_C ARG1
);

static TgVOID
tgKN_GPU_EXT_Initialize_Default_Root_Signature_Description__Unit_Test(
    TgKN_GPU_CXT_EXEC_ID_C ARG0, ETgKN_GPU_DEFAULT_ROOT_SIGNATURE_C ARG1
);




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_GPU_EXT__CMD__Set_Graphics_Root_Signature_From_Default -------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_EXT__CMD__Set_Graphics_Root_Signature_From_Default( UTg2_KN_GPU_CMD_C uCMD, ETgKN_GPU_DEFAULT_ROOT_SIGNATURE_C enRoot_Signature )
{
    TgRSIZE                             uiEXEC = (uCMD.psEXT->m_tiCXT_WORK.m_uiI >> 16) & 0xFFFF;
    STg2_KN_GPU_EXT_CXT_EXEC_PC         psEXT_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + uiEXEC;

    TgPARAM_VAR(TgRSIZE uiWORK = (uCMD.psEXT->m_tiCXT_WORK.m_uiI & 0xFFFF) % KTgKN_GPU_MAX_EXEC_CONTEXT_COMMAND;)
    TgPARAM_VAR(STg2_KN_GPU_CXT_EXEC_PC psCXT_EXEC = g_asKN_GPU_CXT_EXEC + uiEXEC;)
    TgPARAM_CHECK_INDEX( uiEXEC, g_asKN_GPU_EXT_CXT_EXEC );
    TgPARAM_CHECK( tgKN_GPU_CXT_EXEC_ID_Is_Equal( &psCXT_EXEC->m_tiCXT_EXEC_S, psEXT_CXT_EXEC->m_sContext_Command[uiWORK].m_tiCXT_EXEC ) );

    ID3D12GraphicsCommandList8_SetGraphicsRootSignature( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, psEXT_CXT_EXEC->m_asRoot_Signature[enRoot_Signature].m_psDX12_Root_Signature );
    ID3D12GraphicsCommandList8_SetDescriptorHeaps( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 1, &uCMD.psEXT->m_sEXT_Heap_CBV_SRV_UAV.m_psDX12_Heap );

    return (KTgS_OK);
}


/* ---- tgKN_GPU_EXT__CMD__Set_State_From_Default -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_EXT__CMD__Set_State_From_Default( UTg2_KN_GPU_CMD_C uCMD, ETgKN_GPU_DEFAULT_PSO_C enPSO, ETgKN_GPU_EXT_FORMAT_C enRT, ETgKN_GPU_EXT_FORMAT_C enDS )
{
    TgRSIZE                             uiEXEC = (uCMD.psEXT->m_tiCXT_WORK.m_uiI >> 16) & 0xFFFF;
    STg2_KN_GPU_EXT_CXT_EXEC_PC         psEXT_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + uiEXEC;
    ID3D12PipelineState_PP              ppsPSO;

    TgPARAM_VAR(TgRSIZE uiWORK = (uCMD.psEXT->m_tiCXT_WORK.m_uiI & 0xFFFF) % KTgKN_GPU_MAX_EXEC_CONTEXT_COMMAND;)
    TgPARAM_VAR(STg2_KN_GPU_CXT_EXEC_PC psCXT_EXEC = g_asKN_GPU_CXT_EXEC + uiEXEC;)
    TgPARAM_CHECK_INDEX( uiEXEC, g_asKN_GPU_EXT_CXT_EXEC );
    TgPARAM_CHECK( tgKN_GPU_CXT_EXEC_ID_Is_Equal( &psCXT_EXEC->m_tiCXT_EXEC_S, psEXT_CXT_EXEC->m_sContext_Command[uiWORK].m_tiCXT_EXEC ) );

    switch (enRT) {
    case ETgKN_GPU_EXT_FORMAT_R16G16B16A16_FLOAT:
        ppsPSO = psEXT_CXT_EXEC->m_psDX12_PSO[enPSO][0];
        break;
    case ETgKN_GPU_EXT_FORMAT_R10G10B10A2_UNORM:
        ppsPSO = psEXT_CXT_EXEC->m_psDX12_PSO[enPSO][1];
        break;
    case ETgKN_GPU_EXT_FORMAT_R8G8B8A8_UNORM:
        ppsPSO = psEXT_CXT_EXEC->m_psDX12_PSO[enPSO][2];
        break;
    case ETgKN_GPU_EXT_FORMAT_R8G8B8A8_UNORM_SRGB:
        ppsPSO = psEXT_CXT_EXEC->m_psDX12_PSO[enPSO][3];
        break;
    case ETgKN_GPU_EXT_FORMAT_B8G8R8A8_UNORM:
        ppsPSO = psEXT_CXT_EXEC->m_psDX12_PSO[enPSO][4];
        break;
    case ETgKN_GPU_EXT_FORMAT_B8G8R8A8_UNORM_SRGB:
        ppsPSO = psEXT_CXT_EXEC->m_psDX12_PSO[enPSO][5];
        break;

    default:
        return (KTgE_FAIL);
    }

    switch (enDS) {
    case ETgKN_GPU_EXT_FORMAT_D32_FLOAT_S8X24_UINT:
        ID3D12GraphicsCommandList8_SetPipelineState( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, ppsPSO[0] );
        return (KTgS_OK);
    case ETgKN_GPU_EXT_FORMAT_D32_FLOAT:
        ID3D12GraphicsCommandList8_SetPipelineState( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, ppsPSO[1] );
        return (KTgS_OK);
    case ETgKN_GPU_EXT_FORMAT_D24_UNORM_S8_UINT:
        ID3D12GraphicsCommandList8_SetPipelineState( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, ppsPSO[2] );
        return (KTgS_OK);

    default:
        return (KTgE_FAIL);
    }
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* Create the default root signature(s).
Root Signature Strategy (Default): We will want to create a root signature per render pass as a default. At the kernel level we have a minimal set of scenarios that we need to test. 
We will want to be able to test a depth prepass (to test rendering using multiple passes, different pass configuration, intermediate render buffers). This will also force us to build
the ability to debug-view the different passes of the render chain. */

/* ---- tgKN_GPU_EXT_Create_Default_Root_Signature ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_EXT_Create_Default_Root_Signature( TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC )
{
    STg2_KN_GPU_EXT_CXT_EXEC_PC         psEXT_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + tiCXT_EXEC.m_uiI;
    STg2_KN_GPU_CXT_EXEC_PC             psCXT_EXEC = g_asKN_GPU_CXT_EXEC + tiCXT_EXEC.m_uiI;
    ID3D12Device10_PC                   psDX12_Device = g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Adapter[psCXT_EXEC->m_uiAdapter_Index].m_psDX12_Device;

    D3D12_STATIC_SAMPLER_DESC           sDX12_Sampler;
    STg2_KN_GPU_EXT_Root_Signature_P    psEXT_Root_Signature;
    ID3DBlob_P                          pD3D_Signature;
    ID3DBlob_P                          pD3D_Error;

    tgMM_Set_U08_0x00( &sDX12_Sampler, sizeof(sDX12_Sampler) );
    sDX12_Sampler.Filter = D3D12_FILTER_MIN_MAG_MIP_POINT;
    sDX12_Sampler.AddressU = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
    sDX12_Sampler.AddressV = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
    sDX12_Sampler.AddressW = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
    sDX12_Sampler.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
    sDX12_Sampler.MaxLOD = D3D12_FLOAT32_MAX;
    sDX12_Sampler.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;


    /* Create the Debug Render Pass Root Signature */ {
        tgKN_GPU_EXT_Initialize_Default_Root_Signature_Description__Debug( tiCXT_EXEC, ETgKN_GPU_DEFAULT_ROOT_SIGNATURE_DEBUG );
        psEXT_Root_Signature = psEXT_CXT_EXEC->m_asRoot_Signature + ETgKN_GPU_DEFAULT_ROOT_SIGNATURE_DEBUG;

        psEXT_Root_Signature->m_sDX12_Root_Signature.Desc_1_1.NumStaticSamplers = 1;
        psEXT_Root_Signature->m_sDX12_Root_Signature.Desc_1_1.pStaticSamplers = &sDX12_Sampler;

        if (FAILED(g_pfnD3D12SerializeVersionedRootSignature( &psEXT_Root_Signature->m_sDX12_Root_Signature, &pD3D_Signature, &pD3D_Error )))
        {
            TgWARNING_MSGF( false, STD_MSG_LITERAL_1X, STD_MSG_POST, (TgCHAR_NC_CP)ID3D10Blob_GetBufferPointer( pD3D_Error ) );
            goto tgKN_GPU_EXT_Create_Default_Root_Signature_FAILED_0;
        }
        if (FAILED(ID3D12Device10_CreateRootSignature( psDX12_Device, 0, ID3D10Blob_GetBufferPointer( pD3D_Signature ), ID3D10Blob_GetBufferSize( pD3D_Signature ),
                                                       MS_REF IID_ID3D12RootSignature, (TgVOID_PP)&psEXT_Root_Signature->m_psDX12_Root_Signature )))
        {
            goto tgKN_GPU_EXT_Create_Default_Root_Signature_FAILED_0;
        }
        TgMACRO_KN_GPU_EXT_SET_NAME(psEXT_Root_Signature->m_psDX12_Root_Signature, u8"Default Resource: Root Signature: Debug UI");
        tgCN_PrintF( KTgCN_CHANEL_LOADING|KTgCN_SEVERITY_F, STD_MSG_LITERAL_1, STD_MSG_POST, u8"DX12 Root Signature: Debug UI" );
    }


    /* Create the Unit Test Root Signature */ {
        tgKN_GPU_EXT_Initialize_Default_Root_Signature_Description__Debug( tiCXT_EXEC, ETgKN_GPU_DEFAULT_ROOT_SIGNATURE_UNIT_TEST );
        tgKN_GPU_EXT_Initialize_Default_Root_Signature_Description__Unit_Test( tiCXT_EXEC, ETgKN_GPU_DEFAULT_ROOT_SIGNATURE_UNIT_TEST );
        psEXT_Root_Signature = psEXT_CXT_EXEC->m_asRoot_Signature + ETgKN_GPU_DEFAULT_ROOT_SIGNATURE_UNIT_TEST;

        psEXT_Root_Signature->m_sDX12_Root_Signature.Desc_1_1.NumStaticSamplers = 1;
        psEXT_Root_Signature->m_sDX12_Root_Signature.Desc_1_1.pStaticSamplers = &sDX12_Sampler;

        if (FAILED(g_pfnD3D12SerializeVersionedRootSignature( &psEXT_Root_Signature->m_sDX12_Root_Signature, &pD3D_Signature, &pD3D_Error )))
        {
            TgWARNING_MSGF( false, STD_MSG_LITERAL_1X, STD_MSG_POST, (TgCHAR_NC_CP)ID3D10Blob_GetBufferPointer( pD3D_Error ) );
            goto tgKN_GPU_EXT_Create_Default_Root_Signature_FAILED_1;
        }
        if (FAILED(ID3D12Device10_CreateRootSignature( psDX12_Device, 0, ID3D10Blob_GetBufferPointer( pD3D_Signature ), ID3D10Blob_GetBufferSize( pD3D_Signature ),
                                                       MS_REF IID_ID3D12RootSignature, (TgVOID_PP)&psEXT_Root_Signature->m_psDX12_Root_Signature )))
        {
            goto tgKN_GPU_EXT_Create_Default_Root_Signature_FAILED_1;
        }
        TgMACRO_KN_GPU_EXT_SET_NAME(psEXT_Root_Signature->m_psDX12_Root_Signature,u8"Default Resource: Root Signature: Unit Test");
        tgCN_PrintF( KTgCN_CHANEL_LOADING|KTgCN_SEVERITY_F, STD_MSG_LITERAL_1, STD_MSG_POST, u8"DX12 Root Signature: Unit Test" );
    }


    return (KTgS_OK);

tgKN_GPU_EXT_Create_Default_Root_Signature_FAILED_1:
    TgVERIFY(0 == ID3D12RootSignature_Release( psEXT_CXT_EXEC->m_asRoot_Signature[ETgKN_GPU_DEFAULT_ROOT_SIGNATURE_DEBUG].m_psDX12_Root_Signature ));
    psEXT_CXT_EXEC->m_asRoot_Signature[ETgKN_GPU_DEFAULT_ROOT_SIGNATURE_DEBUG].m_psDX12_Root_Signature = nullptr;
tgKN_GPU_EXT_Create_Default_Root_Signature_FAILED_0:
    return (KTgE_FAIL);
}


/* ---- tgKN_GPU_EXT_Create_Default_PSO ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_EXT_Create_Default_PSO( TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC )
{
    STg2_KN_GPU_EXT_CXT_EXEC_PC         psEXT_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + tiCXT_EXEC.m_uiI;
    STg2_KN_GPU_CXT_EXEC_PC             psCXT_EXEC = g_asKN_GPU_CXT_EXEC + tiCXT_EXEC.m_uiI;
    ID3D12Device10_PC                   psDX12_Device = g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Adapter[psCXT_EXEC->m_uiAdapter_Index].m_psDX12_Device;

    UINT                                uiPSO;



    /* Initialize a PSO descriptor for each of the enumerated PSO states. */

    for (uiPSO = 0; uiPSO < ETgKN_GPU_DEFAULT_PSO_END; ++uiPSO)
    {
        STg2_KN_GPU_PSO_DESC_CPC            psDefault_PSO_DESC = g_asKN_GPU_STD_PSO_DESC + uiPSO;
        D3D12_GRAPHICS_PSO_DESC_PC          psDX12_PSO_DESC = psEXT_CXT_EXEC->m_sDX12_PSO_State + uiPSO;

        tgMM_Set_U08_0x00( psDX12_PSO_DESC, sizeof( psDX12_PSO_DESC[0] ) );

        psDX12_PSO_DESC->pRootSignature = psEXT_CXT_EXEC->m_asRoot_Signature[psDefault_PSO_DESC->m_enRoot_Signature].m_psDX12_Root_Signature;
        psDX12_PSO_DESC->BlendState = g_asKN_GPU_EXT_Default_Blend_State[psDefault_PSO_DESC->m_enBlend_State];
        psDX12_PSO_DESC->SampleMask = UINT_MAX;
        psDX12_PSO_DESC->RasterizerState = g_asKN_GPU_EXT_Default_Rasterizer_State[psDefault_PSO_DESC->m_enRasterizer_State];
        psDX12_PSO_DESC->DepthStencilState = g_asKN_GPU_EXT_Default_Depth_Stencil_State[psDefault_PSO_DESC->m_enDepth_State];
        psDX12_PSO_DESC->InputLayout = s_asKN_GPU_EXT_Input_Layout[psDefault_PSO_DESC->m_enInput_Layout];
        psDX12_PSO_DESC->PrimitiveTopologyType = (D3D12_PRIMITIVE_TOPOLOGY_TYPE)psDefault_PSO_DESC->m_enTopology_Type;
        psDX12_PSO_DESC->NumRenderTargets = 0;
        psDX12_PSO_DESC->RTVFormats[0] = DXGI_FORMAT_UNKNOWN;
        psDX12_PSO_DESC->RTVFormats[1] = DXGI_FORMAT_UNKNOWN;
        psDX12_PSO_DESC->RTVFormats[2] = DXGI_FORMAT_UNKNOWN;
        psDX12_PSO_DESC->RTVFormats[3] = DXGI_FORMAT_UNKNOWN;
        psDX12_PSO_DESC->RTVFormats[4] = DXGI_FORMAT_UNKNOWN;
        psDX12_PSO_DESC->RTVFormats[5] = DXGI_FORMAT_UNKNOWN;
        psDX12_PSO_DESC->RTVFormats[6] = DXGI_FORMAT_UNKNOWN;
        psDX12_PSO_DESC->RTVFormats[7] = DXGI_FORMAT_UNKNOWN;
        psDX12_PSO_DESC->DSVFormat = DXGI_FORMAT_UNKNOWN;
        psDX12_PSO_DESC->SampleDesc.Count = 1;
        psDX12_PSO_DESC->NodeMask = psEXT_CXT_EXEC->m_uiNodeMask;

        psDX12_PSO_DESC->VS.BytecodeLength = g_asKN_Lib_VS_Data[g_sKN_GPU_CXT_HOST.m_atiVS[psDefault_PSO_DESC->m_enInput_Layout].m_uiIndex].m_sSH.m_nuiData;
        psDX12_PSO_DESC->VS.pShaderBytecode = g_asKN_Lib_VS_Data[g_sKN_GPU_CXT_HOST.m_atiVS[psDefault_PSO_DESC->m_enInput_Layout].m_uiIndex].m_sSH.m_puiConstData;
        psDX12_PSO_DESC->PS.BytecodeLength = g_asKN_Lib_PS_Data[g_sKN_GPU_CXT_HOST.m_atiPS[uiPSO].m_uiIndex].m_sSH.m_nuiData;
        psDX12_PSO_DESC->PS.pShaderBytecode = g_asKN_Lib_PS_Data[g_sKN_GPU_CXT_HOST.m_atiPS[uiPSO].m_uiIndex].m_sSH.m_puiConstData;
    };



    /* Initialize a PSO for each enumerated PSO state, and for each render target format. */

    for (uiPSO = 0; uiPSO < ETgKN_GPU_DEFAULT_PSO_END; ++uiPSO)
    {
        D3D12_GRAPHICS_PSO_DESC             sDX12_PSO_State;
        TgRSIZE                             uiRTScanOut;

        sDX12_PSO_State = psEXT_CXT_EXEC->m_sDX12_PSO_State[uiPSO];

        for (uiRTScanOut = 0; uiRTScanOut < KTgKN_GPU_EXT_FORMAT_RT_SCANOUT_MAX; ++uiRTScanOut)
        {
            TgRSIZE                             uiDSScanOut;

            sDX12_PSO_State.RTVFormats[0] = (DXGI_FORMAT)KTgKN_GPU_EXT_FORMAT_RT_SCANOUT[uiRTScanOut];
            sDX12_PSO_State.NumRenderTargets = 1;

            for (uiDSScanOut = 0; uiDSScanOut < KTgKN_GPU_EXT_FORMAT_DS_SCANOUT_MAX; ++uiDSScanOut)
            {
                ID3D12PipelineState_P               psDX12_PSO;

                if (sDX12_PSO_State.DepthStencilState.DepthEnable)
                {
                    sDX12_PSO_State.DSVFormat = (DXGI_FORMAT)KTgKN_GPU_EXT_FORMAT_DS_SCANOUT[uiDSScanOut];
                }
                else
                {
                    sDX12_PSO_State.DSVFormat = DXGI_FORMAT_UNKNOWN;
                }

                if (TgFAILED(ID3D12Device10_CreateGraphicsPipelineState( psDX12_Device, &sDX12_PSO_State, MS_REF IID_ID3D12PipelineState, (TgVOID_PP)(&psDX12_PSO) )))
                {
                    psEXT_CXT_EXEC->m_psDX12_PSO[uiPSO][uiRTScanOut][uiDSScanOut] = nullptr;
                }
                else
                {
                    psEXT_CXT_EXEC->m_psDX12_PSO[uiPSO][uiRTScanOut][uiDSScanOut] = psDX12_PSO;
                #if defined(TgCOMPILE__GPU_OBJECT_NAME) && TgCOMPILE__GPU_OBJECT_NAME
                    {
                        TgCHAR_U8_CPC                       uszRT = tgKN_GPU_EXT_FMT_To_USZ( (DXGI_FORMAT)KTgKN_GPU_EXT_FORMAT_RT_SCANOUT[uiRTScanOut] );
                        TgCHAR_U8_CPC                       uszDS = tgKN_GPU_EXT_FMT_To_USZ( (DXGI_FORMAT)KTgKN_GPU_EXT_FORMAT_DS_SCANOUT[uiDSScanOut] );
                        TgCHAR_U8                           uszDebugName[KTgKN_RESOURCE_NAME_MAX];
                        TgCHAR_U8                           uszMessage[128];

                        tgUSZ_PrintF( uszDebugName, sizeof( uszDebugName ), u8"%s (%s - %s)", g_asKN_GPU_STD_PSO_DESC[uiPSO].m_uszName, uszRT, uszDS );
                        TgMACRO_KN_GPU_EXT_SET_NAME_WTH_VAR( psDX12_PSO, uszDebugName );

                        tgUSZ_PrintF( uszMessage, sizeof(uszMessage), u8"DX12 PSO: %s", uszDebugName );
                        tgCN_PrintF( KTgCN_CHANEL_LOADING|KTgCN_SEVERITY_F, STD_MSG_LITERAL_2M, STD_MSG_POST, uszMessage, uszRT );
                    };
                /*# defined(TgCOMPILE__GPU_OBJECT_NAME) && TgCOMPILE__GPU_OBJECT_NAME */
                #endif
                };
            };
        };
    };

    return (KTgS_OK);
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_GPU_EXT_Initialize_Default_Root_Signature_Description__Debug -------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgKN_GPU_EXT_Initialize_Default_Root_Signature_Description__Debug( TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC, ETgKN_GPU_DEFAULT_ROOT_SIGNATURE_C enRoot_Signature )
{
    STg2_KN_GPU_EXT_CXT_EXEC_PC         psEXT_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + tiCXT_EXEC.m_uiI;
    STg2_KN_GPU_EXT_Root_Signature_PC   psEXT_Root_Signature = psEXT_CXT_EXEC->m_asRoot_Signature + enRoot_Signature;

    /* Set the range values. */

    /* Default Textures */
    psEXT_Root_Signature->m_asDX12_Descriptor_Range[psEXT_Root_Signature->m_nuiDX12_Descriptor_Range].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
    psEXT_Root_Signature->m_asDX12_Descriptor_Range[psEXT_Root_Signature->m_nuiDX12_Descriptor_Range].NumDescriptors = KTgKN_GPU_EXT_MAX_DEFAULT_SRV_CBE;
    psEXT_Root_Signature->m_asDX12_Descriptor_Range[psEXT_Root_Signature->m_nuiDX12_Descriptor_Range].BaseShaderRegister = 1000;
    psEXT_Root_Signature->m_asDX12_Descriptor_Range[psEXT_Root_Signature->m_nuiDX12_Descriptor_Range].RegisterSpace = 0;
    psEXT_Root_Signature->m_asDX12_Descriptor_Range[psEXT_Root_Signature->m_nuiDX12_Descriptor_Range].Flags = D3D12_DESCRIPTOR_RANGE_FLAG_DATA_STATIC;
    psEXT_Root_Signature->m_asDX12_Descriptor_Range[psEXT_Root_Signature->m_nuiDX12_Descriptor_Range].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
    ++psEXT_Root_Signature->m_nuiDX12_Descriptor_Range;

    psEXT_Root_Signature->m_asDX12_Descriptor_Range[psEXT_Root_Signature->m_nuiDX12_Descriptor_Range].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
    psEXT_Root_Signature->m_asDX12_Descriptor_Range[psEXT_Root_Signature->m_nuiDX12_Descriptor_Range].NumDescriptors = KTgKN_GPU_EXT_MAX_DEFAULT_SRV_VOL;
    psEXT_Root_Signature->m_asDX12_Descriptor_Range[psEXT_Root_Signature->m_nuiDX12_Descriptor_Range].BaseShaderRegister = 1000 + KTgMACRO_KN_GPU_EXT_MAX_DEFAULT_SRV_CBE;
    psEXT_Root_Signature->m_asDX12_Descriptor_Range[psEXT_Root_Signature->m_nuiDX12_Descriptor_Range].RegisterSpace = 0;
    psEXT_Root_Signature->m_asDX12_Descriptor_Range[psEXT_Root_Signature->m_nuiDX12_Descriptor_Range].Flags = D3D12_DESCRIPTOR_RANGE_FLAG_DATA_STATIC;
    psEXT_Root_Signature->m_asDX12_Descriptor_Range[psEXT_Root_Signature->m_nuiDX12_Descriptor_Range].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
    ++psEXT_Root_Signature->m_nuiDX12_Descriptor_Range;

    psEXT_Root_Signature->m_asDX12_Descriptor_Range[psEXT_Root_Signature->m_nuiDX12_Descriptor_Range].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
    psEXT_Root_Signature->m_asDX12_Descriptor_Range[psEXT_Root_Signature->m_nuiDX12_Descriptor_Range].NumDescriptors = KTgKN_GPU_EXT_MAX_DEFAULT_SRV_IMG;
    psEXT_Root_Signature->m_asDX12_Descriptor_Range[psEXT_Root_Signature->m_nuiDX12_Descriptor_Range].BaseShaderRegister = 1000 + KTgMACRO_KN_GPU_EXT_MAX_DEFAULT_SRV_CBE
                                                                                                                                + KTgMACRO_KN_GPU_EXT_MAX_DEFAULT_SRV_VOL;
    psEXT_Root_Signature->m_asDX12_Descriptor_Range[psEXT_Root_Signature->m_nuiDX12_Descriptor_Range].RegisterSpace = 0;
    psEXT_Root_Signature->m_asDX12_Descriptor_Range[psEXT_Root_Signature->m_nuiDX12_Descriptor_Range].Flags = D3D12_DESCRIPTOR_RANGE_FLAG_DATA_STATIC;
    psEXT_Root_Signature->m_asDX12_Descriptor_Range[psEXT_Root_Signature->m_nuiDX12_Descriptor_Range].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
    ++psEXT_Root_Signature->m_nuiDX12_Descriptor_Range;


    /* Set the root parameters */

    /* Constant Buffer: Debug : Per-Draw Call */
    psEXT_Root_Signature->m_asDX12_Root_Parameter[psEXT_Root_Signature->m_nuiDX12_Root_Parameter].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
    psEXT_Root_Signature->m_asDX12_Root_Parameter[psEXT_Root_Signature->m_nuiDX12_Root_Parameter].Descriptor.ShaderRegister = 1000;
    psEXT_Root_Signature->m_asDX12_Root_Parameter[psEXT_Root_Signature->m_nuiDX12_Root_Parameter].Descriptor.RegisterSpace = 0;
    psEXT_Root_Signature->m_asDX12_Root_Parameter[psEXT_Root_Signature->m_nuiDX12_Root_Parameter].Descriptor.Flags = D3D12_ROOT_DESCRIPTOR_FLAG_DATA_STATIC;
    psEXT_Root_Signature->m_asDX12_Root_Parameter[psEXT_Root_Signature->m_nuiDX12_Root_Parameter].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
    ++psEXT_Root_Signature->m_nuiDX12_Root_Parameter;

    /* Table: Debug: Default Textures */
    psEXT_Root_Signature->m_asDX12_Root_Parameter[psEXT_Root_Signature->m_nuiDX12_Root_Parameter].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
    psEXT_Root_Signature->m_asDX12_Root_Parameter[psEXT_Root_Signature->m_nuiDX12_Root_Parameter].DescriptorTable.NumDescriptorRanges = 3;
    psEXT_Root_Signature->m_asDX12_Root_Parameter[psEXT_Root_Signature->m_nuiDX12_Root_Parameter].DescriptorTable.pDescriptorRanges = psEXT_Root_Signature->m_asDX12_Descriptor_Range;
    psEXT_Root_Signature->m_asDX12_Root_Parameter[psEXT_Root_Signature->m_nuiDX12_Root_Parameter].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
    ++psEXT_Root_Signature->m_nuiDX12_Root_Parameter;


    /* Set the root signature */

    psEXT_Root_Signature->m_sDX12_Root_Signature.Version = D3D_ROOT_SIGNATURE_VERSION_1_1;
    psEXT_Root_Signature->m_sDX12_Root_Signature.Desc_1_1.NumParameters = (UINT)psEXT_Root_Signature->m_nuiDX12_Root_Parameter;
    psEXT_Root_Signature->m_sDX12_Root_Signature.Desc_1_1.pParameters = psEXT_Root_Signature->m_asDX12_Root_Parameter;
    psEXT_Root_Signature->m_sDX12_Root_Signature.Desc_1_1.NumStaticSamplers = 0;
    psEXT_Root_Signature->m_sDX12_Root_Signature.Desc_1_1.pStaticSamplers = nullptr;
    psEXT_Root_Signature->m_sDX12_Root_Signature.Desc_1_1.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
}


/* ---- tgKN_GPU_EXT__CMD__Set_State_From_Default --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgKN_GPU_EXT_Initialize_Default_Root_Signature_Description__Unit_Test( TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC, ETgKN_GPU_DEFAULT_ROOT_SIGNATURE_C enRoot_Signature )
{
    STg2_KN_GPU_EXT_CXT_EXEC_PC         psEXT_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + tiCXT_EXEC.m_uiI;
    STg2_KN_GPU_EXT_Root_Signature_PC   psEXT_Root_Signature = psEXT_CXT_EXEC->m_asRoot_Signature + enRoot_Signature;

    /* Set the root parameters */

    /* Constant Buffer: Unit Test : Scene */
    psEXT_Root_Signature->m_asDX12_Root_Parameter[psEXT_Root_Signature->m_nuiDX12_Root_Parameter].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
    psEXT_Root_Signature->m_asDX12_Root_Parameter[psEXT_Root_Signature->m_nuiDX12_Root_Parameter].Descriptor.ShaderRegister = 1001;
    psEXT_Root_Signature->m_asDX12_Root_Parameter[psEXT_Root_Signature->m_nuiDX12_Root_Parameter].Descriptor.RegisterSpace = 0;
    psEXT_Root_Signature->m_asDX12_Root_Parameter[psEXT_Root_Signature->m_nuiDX12_Root_Parameter].Descriptor.Flags = D3D12_ROOT_DESCRIPTOR_FLAG_DATA_STATIC;
    psEXT_Root_Signature->m_asDX12_Root_Parameter[psEXT_Root_Signature->m_nuiDX12_Root_Parameter].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
    ++psEXT_Root_Signature->m_nuiDX12_Root_Parameter;


    /* Set the root signature */

    psEXT_Root_Signature->m_sDX12_Root_Signature.Version = D3D_ROOT_SIGNATURE_VERSION_1_1;
    psEXT_Root_Signature->m_sDX12_Root_Signature.Desc_1_1.NumParameters = (UINT)psEXT_Root_Signature->m_nuiDX12_Root_Parameter;
    psEXT_Root_Signature->m_sDX12_Root_Signature.Desc_1_1.pParameters = psEXT_Root_Signature->m_asDX12_Root_Parameter;
    psEXT_Root_Signature->m_sDX12_Root_Signature.Desc_1_1.NumStaticSamplers = 0;
    psEXT_Root_Signature->m_sDX12_Root_Signature.Desc_1_1.pStaticSamplers = nullptr;
    psEXT_Root_Signature->m_sDX12_Root_Signature.Desc_1_1.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
}
