/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (DX12) Effect [Unit Test].c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */

#include "TgS KERNEL/TgS (DX12) Kernel [GPU].h"
#include "TgS KERNEL/TgS (DX12) Kernel [GPU] - Debug.inl"


/* ---- GPU - Unit Test ---------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgEXTN TgVOID
tgUnit_Test__FX__Create_Resources(
    TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC, TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP, TgUINT_E32 uiNodeMask );

TgEXTN TgRESULT
tgUnit_Test__FX__Render(
    TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC, TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP, TgKN_GPU_CXT_WORK_ID_C tiCXT_WORK, TgRSIZE_C uiTest_Level );

TgEXTN TgRESULT
tgUnit_Test__FX__Release_Resources(
    TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC, TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP );

TgEXTN TgVOID
tgUnit_Test__FX__Setup_Scene_Constant_Buffer(
    STg2_KN_GPU_Render_Buffer_CPCU psRTBuffer );




/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Types                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

#if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)
static STg2_KN_GPU_DBG_Quad s_sUIConstantBuffer;
#endif

static STg2_KN_GPU_DBG_Geom s_sModelConstantBuffer;
static const UINT c_alignedModelConstantBufferSize = (sizeof( STg2_KN_GPU_DBG_Geom ) + 255) & ~255ULL;

TgTYPE_STRUCT(STg2_UT_KN_GPU_Exec_Resources,)
{
    ID3D12Resource_P                    m_apsDX12_Vertex_Buffer__FX[2];
    ID3D12Resource_P                    m_apsDX12_Vertex_Buffer_Upload__FX[2];

    TgRSIZE                             m_uiRefCount;
};

TgTYPE_STRUCT(STg2_UT_KN_GPU_Swap_Resources,)
{
    ID3D12Resource_P                    m_psDX12_CBV_Model;
    TgRSIZE                             m_uiRefCount;
};




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/** @brief Clear the screen using the clear screen API. Colour correction will need to be done on the CPU. */
static TgRESULT
tgUnit_Test__FX__Render_0(
    TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC, TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP, TgKN_GPU_CXT_WORK_ID tiCXT_WORK );

static STg2_UT_KN_GPU_Exec_Resources s_saGPU_Exec_Resources[KTgKN_GPU_MAX_EXEC_CONTEXT];
static STg2_UT_KN_GPU_Swap_Resources s_saGPU_Swap_Resources[KTgKN_GPU_MAX_SWAP_CONTEXT];




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgUnit_Test__FX__Create_Resources ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgUnit_Test__FX__Create_Resources( TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC, TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP, TgUINT_E32 uiNodeMask )
{
    ID3D12Device10_PC                   psDX12_Device = tgKN_GPU_EXT__Execute__Get_DX12_Device( tiCXT_EXEC );
    STg2_UT_KN_GPU_Swap_Resources_P     psSwap_Resource = s_saGPU_Swap_Resources + tiCXT_SWAP.m_uiI;
    STg2_UT_KN_GPU_Exec_Resources_P     psExec_Resource = s_saGPU_Exec_Resources + tiCXT_EXEC.m_uiI;

    D3D12_HEAP_PROPERTIES               sDX12_Default_Heap_Properties;
    D3D12_HEAP_PROPERTIES               sDX12_Upload_Heap_Properties;
    D3D12_RESOURCE_DESC                 sDX12_Resource_Desc;
    HRESULT                             iRet;

    /* Initialize the data structures */
    tgMM_Set_U08_0x00( &sDX12_Default_Heap_Properties, sizeof( sDX12_Default_Heap_Properties ) );
    sDX12_Default_Heap_Properties.Type = D3D12_HEAP_TYPE_DEFAULT;
    sDX12_Default_Heap_Properties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
    sDX12_Default_Heap_Properties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
    sDX12_Default_Heap_Properties.CreationNodeMask = uiNodeMask;
    sDX12_Default_Heap_Properties.VisibleNodeMask = uiNodeMask;

    tgMM_Set_U08_0x00( &sDX12_Upload_Heap_Properties, sizeof( sDX12_Upload_Heap_Properties ) );
    sDX12_Upload_Heap_Properties.Type = D3D12_HEAP_TYPE_UPLOAD;
    sDX12_Upload_Heap_Properties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
    sDX12_Upload_Heap_Properties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
    sDX12_Upload_Heap_Properties.CreationNodeMask = uiNodeMask;
    sDX12_Upload_Heap_Properties.VisibleNodeMask = uiNodeMask;

    tgMM_Set_U08_0x00( &sDX12_Resource_Desc, sizeof( sDX12_Resource_Desc ) );
    sDX12_Resource_Desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
    sDX12_Resource_Desc.Alignment = 0;
    sDX12_Resource_Desc.Width = c_alignedModelConstantBufferSize;
    sDX12_Resource_Desc.Height = 1;
    sDX12_Resource_Desc.DepthOrArraySize = 1;
    sDX12_Resource_Desc.MipLevels = 1;
    sDX12_Resource_Desc.Format = DXGI_FORMAT_UNKNOWN;
    sDX12_Resource_Desc.SampleDesc.Count = 1;
    sDX12_Resource_Desc.SampleDesc.Quality = 0;
    sDX12_Resource_Desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
    sDX12_Resource_Desc.Flags = D3D12_RESOURCE_FLAG_NONE;

    /// Constant Buffer
    TgVERIFY(SUCCEEDED(ID3D12Device10_CreateCommittedResource1( psDX12_Device, &sDX12_Upload_Heap_Properties, D3D12_HEAP_FLAG_NONE, &sDX12_Resource_Desc, D3D12_RESOURCE_STATE_GENERIC_READ,
                                                                nullptr, nullptr, MS_REF IID_ID3D12Resource, (TgVOID_PP)&psSwap_Resource->m_psDX12_CBV_Model )));
    ID3D12Object_SetName(psSwap_Resource->m_psDX12_CBV_Model,L"Unit Test Resource: Constant Buffer");


    /// Create a Vertex Buffer

    if (0 != psExec_Resource->m_uiRefCount)
    {
        ++psExec_Resource->m_uiRefCount;
        return;
    };

    ++psExec_Resource->m_uiRefCount;

    /* 1.1 Create the vertex buffers for the rendering test. */
    sDX12_Resource_Desc.Width = KTgRN_MAX_PRTCL_BUFFER_SIZE;
    iRet = ID3D12Device10_CreateCommittedResource1( psDX12_Device, &sDX12_Default_Heap_Properties, D3D12_HEAP_FLAG_NONE, &sDX12_Resource_Desc, D3D12_RESOURCE_STATE_COMMON,
                                                    nullptr, nullptr, MS_REF IID_ID3D12Resource, (TgVOID_PP)psExec_Resource->m_apsDX12_Vertex_Buffer__FX );
    TgVERIFY(SUCCEEDED(iRet));
    ID3D12Object_SetName(psExec_Resource->m_apsDX12_Vertex_Buffer__FX[0],L"Unit Test Resource: Vertex Buffer Cube 00");

    iRet = ID3D12Device10_CreateCommittedResource1( psDX12_Device, &sDX12_Default_Heap_Properties, D3D12_HEAP_FLAG_NONE, &sDX12_Resource_Desc, D3D12_RESOURCE_STATE_COMMON,
                                                    nullptr, nullptr, MS_REF IID_ID3D12Resource, (TgVOID_PP)psExec_Resource->m_apsDX12_Vertex_Buffer__FX + 1 );
    TgVERIFY(SUCCEEDED(iRet));
    ID3D12Object_SetName(psExec_Resource->m_apsDX12_Vertex_Buffer__FX[1],L"Unit Test Resource: Vertex Buffer Cube 00");

    /* 1.3 Create the vertex upload buffers that will be used for uploading/copying the data to the GPU. */
    sDX12_Resource_Desc.Width = KTgRN_MAX_PRTCL_BUFFER_SIZE;
    iRet = ID3D12Device10_CreateCommittedResource1( psDX12_Device, &sDX12_Upload_Heap_Properties, D3D12_HEAP_FLAG_NONE, &sDX12_Resource_Desc, D3D12_RESOURCE_STATE_GENERIC_READ, 
                                                    nullptr, nullptr, MS_REF IID_ID3D12Resource, (TgVOID_PP)psExec_Resource->m_apsDX12_Vertex_Buffer_Upload__FX );
    TgVERIFY(SUCCEEDED(iRet));
    ID3D12Object_SetName(psExec_Resource->m_apsDX12_Vertex_Buffer_Upload__FX[0],L"Unit Test Resource: Vertex Upload Buffer Cube 00");

    iRet = ID3D12Device10_CreateCommittedResource1( psDX12_Device, &sDX12_Upload_Heap_Properties, D3D12_HEAP_FLAG_NONE, &sDX12_Resource_Desc, D3D12_RESOURCE_STATE_GENERIC_READ, 
                                            nullptr, nullptr, MS_REF IID_ID3D12Resource, (TgVOID_PP)psExec_Resource->m_apsDX12_Vertex_Buffer_Upload__FX + 1 );
    TgVERIFY(SUCCEEDED(iRet));
    ID3D12Object_SetName(psExec_Resource->m_apsDX12_Vertex_Buffer_Upload__FX[1],L"Unit Test Resource: Vertex Upload Buffer Cube 00");
}


/* ---- tgUnit_Test__FX__Render -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgUnit_Test__FX__Render( TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC, TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP, TgKN_GPU_CXT_WORK_ID_C tiCXT_WORK, TgRSIZE_C uiTest_Level )
{
    switch (uiTest_Level) {
    case 0: return (tgUnit_Test__FX__Render_0( tiCXT_EXEC, tiCXT_SWAP, tiCXT_WORK ));
    }

    return (KTgS_OK);
}


/* ---- tgUnit_Test__FX__Release_Resources --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgUnit_Test__FX__Release_Resources( TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC, TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP )
{
    STg2_UT_KN_GPU_Exec_Resources_P     psExec_Resource = s_saGPU_Exec_Resources + tiCXT_EXEC.m_uiI;
    STg2_UT_KN_GPU_Swap_Resources_P     psSwap_Resource = s_saGPU_Swap_Resources + tiCXT_SWAP.m_uiI;

    --psExec_Resource->m_uiRefCount;

    if (0 == psExec_Resource->m_uiRefCount)
    {
        tgKN_GPU_EXT__Execute__Flush( tiCXT_EXEC );

        if (psExec_Resource->m_apsDX12_Vertex_Buffer__FX[0])
        {
            TgVERIFY( 0 == ID3D12Heap_Release( psExec_Resource->m_apsDX12_Vertex_Buffer__FX[0] ) );
        };

        if (psExec_Resource->m_apsDX12_Vertex_Buffer__FX[1])
        {
            TgVERIFY( 0 == ID3D12Resource_Release( psExec_Resource->m_apsDX12_Vertex_Buffer__FX[1] ) );
        };

        if (psExec_Resource->m_apsDX12_Vertex_Buffer_Upload__FX[0])
        {
            TgVERIFY( 0 == ID3D12Resource_Release( psExec_Resource->m_apsDX12_Vertex_Buffer_Upload__FX[0] ) );
        };

        if (psExec_Resource->m_apsDX12_Vertex_Buffer_Upload__FX[1])
        {
            TgVERIFY( 0 == ID3D12Resource_Release( psExec_Resource->m_apsDX12_Vertex_Buffer_Upload__FX[1] ) );
        };
    }

    if (psSwap_Resource->m_psDX12_CBV_Model)
    {
        TgVERIFY( 0 == ID3D12Resource_Release( psSwap_Resource->m_psDX12_CBV_Model ) );
    };

    return (KTgS_OK);
}


TgEXTN STg2_FX_Rnd_Output                  g_sRN_Output;
TgEXTN STg2_KN_GPU_Camera                   g_sCamera;
static TgRSIZE_A                            s_xuiBuffer_Index;

/* ---- tgUnit_Test__FX__Render_0 ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT tgUnit_Test__FX__Render_0( TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC, TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP, TgKN_GPU_CXT_WORK_ID tiCXT_WORK )
{
    TgBOOL                              bEndFrame = false;

    STg2_KN_GPU_CMD                     uCMD;
    STg2_KN_GPU_Render_Buffer           sRTBuffer, sDSBuffer;
    STg2_KN_GPU_Output_DESC             sOutput_DESC;
    D3D12_CPU_DESCRIPTOR_HANDLE         shHeap_RTV;
    D3D12_CPU_DESCRIPTOR_HANDLE         shHeap_DSV;
    TgRSIZE                             nuiFX_Header, uiFX_Header;

    if (KTgKN_GPU_CXT_WORK_ID__INVALID.m_uiKI == tiCXT_WORK.m_uiKI)
    {
        tiCXT_WORK = tgKN_GPU_EXT__Execute__Frame_Start( tiCXT_EXEC );
        bEndFrame = true;
    }
    uCMD = tgKN_GPU_EXT__WORK__Acquire_Command( tiCXT_WORK, (ETgKN_GPU_EXT_COMMAND)D3D12_COMMAND_LIST_TYPE_DIRECT );
    tgKN_GPU_EXT__CMD__Set_Graphics_Root_Signature_From_Default( psCMD, ETgKN_GPU_DEFAULT_PIPELINE_LAYOUT_DEBUG );

    if (TgFAILED(tgKN_GPU_EXT__SwapChain__Acquire_Present_Buffer( &shHeap_RTV, &shHeap_DSV, &sOutput_DESC, tiCXT_SWAP )))
    {
        return (KTgE_FAIL);
    };
    tgKN_GPU__SwapChain__Get_Target_Buffers( &sRTBuffer, &sDSBuffer, tiCXT_SWAP );
    ID3D12GraphicsCommandList8_OMSetRenderTargets( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 1, &shHeap_RTV, FALSE, &shHeap_DSV );
    tgKN_GPU_EXT__CMD__Set_Viewport_and_Scissor( psCMD, tiCXT_SWAP );
    ID3D12GraphicsCommandList8_ClearDepthStencilView( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, shHeap_DSV, D3D12_CLEAR_FLAG_DEPTH, 1.0F, 0, 0, nullptr );

    tgUnit_Test__FX__Setup_Scene_Constant_Buffer( &sRTBuffer );

    /* Clear the render target using a full screen quad. */
    #if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)
    {
        PIXBeginEvent_ThatWorksInC_ID3D12GraphicsCommandList( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 0, "UNIT TEST: Draw UI - Clear Viewport" );
        tgKN_GPU_EXT__CMD__Set_State_From_Default( psCMD, ETgKN_GPU_DBG_GRAPHICS_PIPELINE_UI, sRTBuffer.m_enFormat, sDSBuffer.m_enFormat );
        s_sUIConstantBuffer.m_sDESC = sOutput_DESC;
        s_sUIConstantBuffer.m_vRect_UI.x = -1.0F;
        s_sUIConstantBuffer.m_vRect_UI.y =  1.0F;
        s_sUIConstantBuffer.m_vRect_UI.z =  1.0F;
        s_sUIConstantBuffer.m_vRect_UI.w = -1.0F;
        s_sUIConstantBuffer.m_vUI_Colour.r = 1.0F;
        s_sUIConstantBuffer.m_vUI_Colour.g = 1.0F;
        s_sUIConstantBuffer.m_vUI_Colour.b = 1.0F;
        s_sUIConstantBuffer.m_vUI_Colour.a = 1.0F;
        s_sUIConstantBuffer.m_uiSelect_Default_Texture_Index = 0;
        tgKN_GPU_EXT__CMD__Render_Debug_Quad( psCMD, &s_sUIConstantBuffer );
        PIXEndEvent_ThatWorksInC_ID3D12GraphicsCommandList( uCMD.psEXT->m_psDX12_Graphics_Cmd_List );
    }
    #endif

    #if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)
    {
        PIXBeginEvent_ThatWorksInC_ID3D12GraphicsCommandList( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 0, "UNIT TEST: Draw Debug Geometry" );
        tgKN_GPU_EXT__CMD__Set_State_From_Default( psCMD, ETgKN_GPU_DBG_GRAPHICS_PIPELINE_GEOM_02, sRTBuffer.m_enFormat, sDSBuffer.m_enFormat );
        tgMH_CLI_S_F32_04_4( &s_sModelConstantBuffer.m_avModel_Transform );
        s_sModelConstantBuffer.m_avModel_Transform._11 = 0.25F;
        s_sModelConstantBuffer.m_avModel_Transform._22 = 0.25F;
        s_sModelConstantBuffer.m_avModel_Transform._33 = 0.25F;
        s_sModelConstantBuffer.m_avModel_Transform._41 = g_sCamera.m_sConfiguration.m_uCam_Position.m_vS_F32_04_1.x;
        s_sModelConstantBuffer.m_avModel_Transform._42 = g_sCamera.m_sConfiguration.m_uCam_Position.m_vS_F32_04_1.y;
        s_sModelConstantBuffer.m_avModel_Transform._43 = g_sCamera.m_sConfiguration.m_uCam_Position.m_vS_F32_04_1.z;
        s_sModelConstantBuffer.m_sDESC = sOutput_DESC;
        tgMM_Copy( &s_sModelConstantBuffer.m_avW2C, sizeof(s_sModelConstantBuffer.m_avW2C), &g_sSceneConstantBuffer.m_avW2C, sizeof(g_sSceneConstantBuffer.m_avW2C) );
        tgMM_Copy( &s_sModelConstantBuffer.m_avC2S, sizeof(s_sModelConstantBuffer.m_avC2S), &g_sSceneConstantBuffer.m_avC2S, sizeof(g_sSceneConstantBuffer.m_avC2S) );
        s_sModelConstantBuffer.m_vModel_Colour.m_vS_F32_04_1 = tgMH_Init_ELEM_S_F32_04_1( 1.0F, 1.0F, 1.0F, 1.0F );
        s_sModelConstantBuffer.m_vLight_Ambient = tgMH_Init_ELEM_S_F32_04_1( 0.1F, 0.1F, 0.1F, 1.0F );
        s_sModelConstantBuffer.m_vLight_Direction = tgMH_Init_ELEM_S_F32_04_1( -1.0F/1.73205081F, 1.0F/1.73205081F, -1.0F/1.73205081F, 0.0F );
        s_sModelConstantBuffer.m_vLight_Direction_Colour = tgMH_Init_ELEM_S_F32_04_1( 0.4F, 0.6F, 0.6F, 1.0F );
        tgKN_GPU_EXT__CMD__Render_Debug_Geom( psCMD, ETgKN_GPU_DEBUG_PM_3D_SPHERE, &s_sModelConstantBuffer );
        PIXEndEvent_ThatWorksInC_ID3D12GraphicsCommandList( uCMD.psEXT->m_psDX12_Graphics_Cmd_List );
    }
    #endif

    #if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)
    {
        PIXBeginEvent_ThatWorksInC_ID3D12GraphicsCommandList( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 0, "UNIT TEST: Draw Debug Geometry" );
        tgKN_GPU_EXT__CMD__Set_State_From_Default( psCMD, ETgKN_GPU_DBG_GRAPHICS_PIPELINE_GEOM_02, sRTBuffer.m_enFormat, sDSBuffer.m_enFormat );
        tgMH_CLI_S_F32_04_4( &s_sModelConstantBuffer.m_avModel_Transform );
        tgKN_GPU_EXT__CMD__Render_Debug_Geom( psCMD, ETgKN_GPU_DEBUG_PM_3D_BOX, &s_sModelConstantBuffer );
        s_sModelConstantBuffer.m_avModel_Transform._11 = 0.5F;
        s_sModelConstantBuffer.m_avModel_Transform._22 = 0.5F;
        s_sModelConstantBuffer.m_avModel_Transform._33 = 0.5F;
        s_sModelConstantBuffer.m_avModel_Transform._42 = 10.0F;
        tgKN_GPU_EXT__CMD__Render_Debug_Geom( psCMD, ETgKN_GPU_DEBUG_PM_3D_SPHERE, &s_sModelConstantBuffer );
        tgMH_CLI_S_F32_04_4( &s_sModelConstantBuffer.m_avModel_Transform );
        PIXEndEvent_ThatWorksInC_ID3D12GraphicsCommandList( uCMD.psEXT->m_psDX12_Graphics_Cmd_List );
    }
    #endif

    nuiFX_Header = TgSTD_ATOMIC(load)( &g_sRN_Output.m_xnuiFX_Header );
    {
        STg2_UT_KN_GPU_Swap_Resources_P     psSwap_Resource = s_saGPU_Swap_Resources + tiCXT_SWAP.m_uiI;
        STg2_UT_KN_GPU_Exec_Resources_P     psExec_Resource = s_saGPU_Exec_Resources + tiCXT_EXEC.m_uiI;
        TgRSIZE_C                           nbyFX_Data = g_sRN_Output.m_nbyUsed;
        TgRSIZE_C                           uiBuffer_Index = TgSTD_ATOMIC(fetch_add)( &s_xuiBuffer_Index, 1 ) % TgARRAY_COUNT(psExec_Resource->m_apsDX12_Vertex_Buffer__FX);

        D3D12_RESOURCE_BARRIER              sDX12_ResourceBarrier;
        D3D12_VERTEX_BUFFER_VIEW            sVertex_Buffer_View;
        UINT8*                              puiMapped_Upload;
        D3D12_RANGE                         sDX12_Range;
        D3D12_GPU_DESCRIPTOR_HANDLE         shDX12_GPU;
        UINT                                uiStart_Vertex;

        tgMM_Set_U08_0x00( &sDX12_ResourceBarrier, sizeof( D3D12_RESOURCE_BARRIER ) );
        sDX12_ResourceBarrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
        sDX12_ResourceBarrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
        sDX12_ResourceBarrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

        sVertex_Buffer_View.BufferLocation = ID3D12Resource_GetGPUVirtualAddress( psExec_Resource->m_apsDX12_Vertex_Buffer__FX[uiBuffer_Index] );
        sVertex_Buffer_View.StrideInBytes = sizeof( STg2_KN_GPU_Vertex_Particle_00 );
        sVertex_Buffer_View.SizeInBytes = KTgRN_MAX_PRTCL_BUFFER_SIZE;

        /* 1.2 Transition the vertex buffers from their general state to a copy destination. */
        sDX12_ResourceBarrier.Transition.StateBefore = D3D12_RESOURCE_STATE_COMMON;
        sDX12_ResourceBarrier.Transition.StateAfter = D3D12_RESOURCE_STATE_COPY_DEST;
        sDX12_ResourceBarrier.Transition.pResource = psExec_Resource->m_apsDX12_Vertex_Buffer__FX[uiBuffer_Index];
        ID3D12GraphicsCommandList8_ResourceBarrier( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 1, &sDX12_ResourceBarrier );

        /* 1.4 Copy the data from general CPU memory into the CPU upload buffers. */
        sDX12_Range.Begin = 0; sDX12_Range.End = nbyFX_Data;
        TgVERIFY(SUCCEEDED(ID3D12Resource_Map( psExec_Resource->m_apsDX12_Vertex_Buffer_Upload__FX[uiBuffer_Index], 0, &sDX12_Range, (TgVOID_PP)(&puiMapped_Upload) )));
        memcpy( puiMapped_Upload, g_sRN_Output.m_puiBuffer, nbyFX_Data );
        ID3D12Resource_Unmap( psExec_Resource->m_apsDX12_Vertex_Buffer_Upload__FX[uiBuffer_Index], 0, &sDX12_Range );
        puiMapped_Upload = nullptr;
        ID3D12GraphicsCommandList8_CopyBufferRegion( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, psExec_Resource->m_apsDX12_Vertex_Buffer__FX[uiBuffer_Index], 0,
                                                     psExec_Resource->m_apsDX12_Vertex_Buffer_Upload__FX[uiBuffer_Index], 0, nbyFX_Data );

        /* 1.5 Transition the vertex buffers from copy destination to vertex buffer. */
        sDX12_ResourceBarrier.Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST;
        sDX12_ResourceBarrier.Transition.StateAfter = D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER;
        sDX12_ResourceBarrier.Transition.pResource = psExec_Resource->m_apsDX12_Vertex_Buffer__FX[uiBuffer_Index];
        ID3D12GraphicsCommandList8_ResourceBarrier( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 1, &sDX12_ResourceBarrier );


        /* Set the constant buffer for the camera matrices. */
        tgMM_Set_U08_0x00( &sDX12_Range, sizeof( sDX12_Range ) );
        TgVERIFY(SUCCEEDED(ID3D12Resource_Map( psSwap_Resource->m_psDX12_CBV_Model, 0, &sDX12_Range, (TgVOID_PP)&puiMapped_Upload )));
        tgMM_Copy( puiMapped_Upload, c_alignedModelConstantBufferSize, &s_sModelConstantBuffer, sizeof( s_sModelConstantBuffer ) );
        ID3D12Resource_Unmap( psSwap_Resource->m_psDX12_CBV_Model, 0, &sDX12_Range );



        PIXBeginEvent_ThatWorksInC_ID3D12GraphicsCommandList( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 0, "UNIT TEST: Draw FX" );
        tgKN_GPU_EXT__CMD__Set_State_From_Default( psCMD, ETgKN_GPU_GRAPHICS_PIPELINE_PARTICLE_00, sRTBuffer.m_enFormat, sDSBuffer.m_enFormat );
        ID3D12GraphicsCommandList8_IASetVertexBuffers( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 0, 1, &sVertex_Buffer_View );
        ID3D12GraphicsCommandList8_IASetIndexBuffer( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, nullptr );
        ID3D12GraphicsCommandList8_IASetPrimitiveTopology( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
        ID3D12GraphicsCommandList8_SetGraphicsRootConstantBufferView( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 0,
                                                                      ID3D12Resource_GetGPUVirtualAddress( psSwap_Resource->m_psDX12_CBV_Model ) );
        ID3D12DescriptorHeap_GetGPUDescriptorHandleForHeapStart( uCMD.psEXT->m_sEXT_Heap_CBV_SRV_UAV.m_psDX12_Heap, &shDX12_GPU );
        ID3D12GraphicsCommandList8_SetGraphicsRootDescriptorTable( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 1, shDX12_GPU );

        for (uiFX_Header = 0, uiStart_Vertex = 0; uiFX_Header < nuiFX_Header; ++uiFX_Header)
        {
            TgVERIFY(KTgRN_MAX_PRTCL_BUFFER_SIZE >= g_sRN_Output.m_psFX_Header[uiFX_Header].m_uiGenerated_Vertices * sizeof( STg2_KN_GPU_Vertex_Particle_00 ));
            if (g_sRN_Output.m_psFX_Header[uiFX_Header].m_uiGenerated_Vertices <= 0)
                continue;
            uiStart_Vertex = (UINT)(g_sRN_Output.m_psFX_Header[uiFX_Header].m_uiBuffer_Offset / sizeof( STg2_KN_GPU_Vertex_Particle_00 ));
            ID3D12GraphicsCommandList8_DrawInstanced( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, g_sRN_Output.m_psFX_Header[uiFX_Header].m_uiGenerated_Vertices, 1, uiStart_Vertex, 0 );
        }
        PIXEndEvent_ThatWorksInC_ID3D12GraphicsCommandList( uCMD.psEXT->m_psDX12_Graphics_Cmd_List );
    }

    #if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) && TgCOMPILE__PROFILE
    {
        TgCHAR_U8                           uszBuffer[512];
        STg2_Profile_Entry                  sProfile_Entry;
        TgSINT_E64                          iCall_Avg;
        STg2_KN_GPU_DBG_Text_CI             sText_CI;

        PIXBeginEvent_ThatWorksInC_ID3D12GraphicsCommandList( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 0, "FX Performance Stats" );
        tgMM_Set_U08_0x00( &sText_CI, sizeof( sText_CI ) );

        sText_CI.m_enFont = ETgKN_GPU_DOS_FONT_ROM_MARCIO;
        sText_CI.m_auszText = &uszBuffer;
        sText_CI.m_nuiText = 1;
        sText_CI.m_vText_Box_V.x = -1.0F + (10.0F / (float)sRTBuffer.m_uiWidth);
        sText_CI.m_vText_Box_V.y = 0.5F - (10.0F / (float)sRTBuffer.m_uiHeight);
        sText_CI.m_vText_Box_V.z = 1.0F - (10.0F / (float)sRTBuffer.m_uiWidth);
        sText_CI.m_vText_Box_V.w =-1.0F + (10.0F / (float)sRTBuffer.m_uiHeight);
        sText_CI.m_vText_Colour.r = 0.0F;
        sText_CI.m_vText_Colour.g = 1.0F;
        sText_CI.m_vText_Colour.b = 0.0F;
        sText_CI.m_vText_Colour.a = 1.0F;
        sText_CI.m_bRight_Aligned = false;

        tgUSZ_PrintF( uszBuffer, 256, u8"Update" );
        tgPF_Query_Profile_Entry_Unsafe( &sProfile_Entry, sPF_TAG_FX_BEAM_UPDATE__UPDATE[0] );
        iCall_Avg = sProfile_Entry.m_niCall ? sProfile_Entry.m_iCall_Time_Total / sProfile_Entry.m_niCall : 0;
        tgUSZ_AppendF( uszBuffer, TgARRAY_COUNT(uszBuffer), u8"\n Beam:      %8.2f | %8.2f | %8.2f", (double)tgTM_Counter_Tick_To_MilliSeconds( iCall_Avg ),
                        (double)tgTM_Counter_Tick_To_MilliSeconds( sProfile_Entry.m_iCall_Time_Min ), (double)tgTM_Counter_Tick_To_MilliSeconds( sProfile_Entry.m_iCall_Time_Max ) );
        tgPF_Query_Profile_Entry_Unsafe( &sProfile_Entry, sPF_TAG_FX_BILLBOARD_UPDATE__UPDATE[0] );
        iCall_Avg = sProfile_Entry.m_niCall ? sProfile_Entry.m_iCall_Time_Total / sProfile_Entry.m_niCall : 0;
        tgUSZ_AppendF( uszBuffer, TgARRAY_COUNT(uszBuffer), u8"\n Billboard: %8.2f | %8.2f | %8.2f", (double)tgTM_Counter_Tick_To_MilliSeconds( iCall_Avg ),
                        (double)tgTM_Counter_Tick_To_MilliSeconds( sProfile_Entry.m_iCall_Time_Min ), (double)tgTM_Counter_Tick_To_MilliSeconds( sProfile_Entry.m_iCall_Time_Max ) );
        tgPF_Query_Profile_Entry_Unsafe( &sProfile_Entry, sPF_TAG_FX_EMITTER_UPDATE__UPDATE[0] );
        iCall_Avg = sProfile_Entry.m_niCall ? sProfile_Entry.m_iCall_Time_Total / sProfile_Entry.m_niCall : 0;
        tgUSZ_AppendF( uszBuffer, TgARRAY_COUNT(uszBuffer), u8"\n Emitter:   %8.2f | %8.2f | %8.2f", (double)tgTM_Counter_Tick_To_MilliSeconds( iCall_Avg ),
                        (double)tgTM_Counter_Tick_To_MilliSeconds( sProfile_Entry.m_iCall_Time_Min ), (double)tgTM_Counter_Tick_To_MilliSeconds( sProfile_Entry.m_iCall_Time_Max ) );
        tgPF_Query_Profile_Entry_Unsafe( &sProfile_Entry, sPF_TAG_FX_TRAIL_UPDATE__UPDATE[0] );
        iCall_Avg = sProfile_Entry.m_niCall ? sProfile_Entry.m_iCall_Time_Total / sProfile_Entry.m_niCall : 0;
        tgUSZ_AppendF( uszBuffer, TgARRAY_COUNT(uszBuffer), u8"\n Trail:     %8.2f | %8.2f | %8.2f", (double)tgTM_Counter_Tick_To_MilliSeconds( iCall_Avg ),
                        (double)tgTM_Counter_Tick_To_MilliSeconds( sProfile_Entry.m_iCall_Time_Min ), (double)tgTM_Counter_Tick_To_MilliSeconds( sProfile_Entry.m_iCall_Time_Max ) );

        tgUSZ_AppendF( uszBuffer, TgARRAY_COUNT(uszBuffer), u8"\n\nRender Generate" );
        tgPF_Query_Profile_Entry_Unsafe( &sProfile_Entry, sPF_TAG_FX_BEAM_RENDER__GENERATE );
        iCall_Avg = sProfile_Entry.m_niCall ? sProfile_Entry.m_iCall_Time_Total / sProfile_Entry.m_niCall : 0;
        tgUSZ_AppendF( uszBuffer, TgARRAY_COUNT(uszBuffer), u8"\n Beam:      %8.2f | %8.2f | %8.2f", (double)tgTM_Counter_Tick_To_MilliSeconds( iCall_Avg ),
                        (double)tgTM_Counter_Tick_To_MilliSeconds( sProfile_Entry.m_iCall_Time_Min ), (double)tgTM_Counter_Tick_To_MilliSeconds( sProfile_Entry.m_iCall_Time_Max ) );
        tgPF_Query_Profile_Entry_Unsafe( &sProfile_Entry, sPF_TAG_FX_BILLBOARD_RENDER__GENERATE );
        iCall_Avg = sProfile_Entry.m_niCall ? sProfile_Entry.m_iCall_Time_Total / sProfile_Entry.m_niCall : 0;
        tgUSZ_AppendF( uszBuffer, TgARRAY_COUNT(uszBuffer), u8"\n Billboard: %8.2f | %8.2f | %8.2f", (double)tgTM_Counter_Tick_To_MilliSeconds( iCall_Avg ),
                        (double)tgTM_Counter_Tick_To_MilliSeconds( sProfile_Entry.m_iCall_Time_Min ), (double)tgTM_Counter_Tick_To_MilliSeconds( sProfile_Entry.m_iCall_Time_Max ) );
        tgPF_Query_Profile_Entry_Unsafe( &sProfile_Entry, sPF_TAG_FX_EMITTER_RENDER__GENERATE );
        iCall_Avg = sProfile_Entry.m_niCall ? sProfile_Entry.m_iCall_Time_Total / sProfile_Entry.m_niCall : 0;
        tgUSZ_AppendF( uszBuffer, TgARRAY_COUNT(uszBuffer), u8"\n Emitter:   %8.2f | %8.2f | %8.2f", (double)tgTM_Counter_Tick_To_MilliSeconds( iCall_Avg ),
                        (double)tgTM_Counter_Tick_To_MilliSeconds( sProfile_Entry.m_iCall_Time_Min ), (double)tgTM_Counter_Tick_To_MilliSeconds( sProfile_Entry.m_iCall_Time_Max ) );
        tgPF_Query_Profile_Entry_Unsafe( &sProfile_Entry, sPF_TAG_FX_TRAIL_RENDER__GENERATE );
        iCall_Avg = sProfile_Entry.m_niCall ? sProfile_Entry.m_iCall_Time_Total / sProfile_Entry.m_niCall : 0;
        tgUSZ_AppendF( uszBuffer, TgARRAY_COUNT(uszBuffer), u8"\n Trail:     %8.2f | %8.2f | %8.2f", (double)tgTM_Counter_Tick_To_MilliSeconds( iCall_Avg ),
                        (double)tgTM_Counter_Tick_To_MilliSeconds( sProfile_Entry.m_iCall_Time_Min ), (double)tgTM_Counter_Tick_To_MilliSeconds( sProfile_Entry.m_iCall_Time_Max ) );

        tgKN_GPU__CMD__Render_Debug_Text_Box( psCMD, &sText_CI );
        PIXEndEvent_ThatWorksInC_ID3D12GraphicsCommandList( uCMD.psEXT->m_psDX12_Graphics_Cmd_List );
    }
    #endif


    tgKN_GPU_EXT__CMD__Command_Buffer_Close( uCMD );
    uCMD.ps = nullptr;
    tgKN_GPU_EXT__WORK__Present( tiCXT_WORK, tiCXT_SWAP );
    if (bEndFrame)
    {
        tgKN_GPU_EXT__WORK__Frame_End( tiCXT_WORK );
    }
    return (KTgS_OK);
}
