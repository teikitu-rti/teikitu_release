/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (DX12) Kernel - System [GPU] [Context] [SWAP].c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */

#include "TgS KERNEL/TgS (DX12) Kernel [GPU] - Debug.inl"


/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

static TgBOOL
tgKN_GPU_EXT_CXT_SWAP_Find_Mode(
    STg2_KN_GPU_CXT_SWAP_CPC ARG0, DXGI_MODE_DESC1_P ARG1 );

TgINLINE TgVOID
tgKN_GPU_EXT_CXT_SWAP_Free_For_Resize(
    TgKN_GPU_CXT_SWAP_ID_C ARG0
);

static TgRESULT
tgKN_GPU_EXT_CXT_SWAP_Set_HDR_Metadata(
    TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_GPU_EXT__SwapChain__Init ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* NOTE: This is the only context init function that is re-entrant. This is so it can be reused after a windows has been resized on the windows platform. Specifically, the 
         existence of a swap chain pointer is used to validate if the structure has been initialized.                                                                              */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_EXT__SwapChain__Init( TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP, TgBOOL_C bResize )
{
    STg2_KN_GPU_EXT_CXT_SWAP_PC         psEXT_CXT_SWAP = g_asKN_GPU_EXT_CXT_SWAP + tiCXT_SWAP.m_uiI;
    STg2_KN_GPU_CXT_SWAP_PC             psCXT_SWAP = g_asKN_GPU_CXT_SWAP + tiCXT_SWAP.m_uiI;
    TgBOOL_C                            bFirst_Time_Init = nullptr == psEXT_CXT_SWAP->m_psDXGI_Swap_Chain;
    union { HWND hWnd; TgUINT_PTR uiPTR; } const sHWND = { .uiPTR = psCXT_SWAP->m_uiOS_ID };

    STg2_KN_GPU_EXT_CXT_EXEC_P          psEXT_CXT_EXEC;
    ID3D12Device10_P                    psDX12_Device;
    HRESULT                             iRet;

    /* Local pointer aliases to global data structures. */
    TgPARAM_CHECK_INDEX(tiCXT_SWAP.m_uiI, g_asKN_GPU_EXT_CXT_SWAP);

    TgERROR(nullptr != g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Adapter[psCXT_SWAP->m_uiAdapter_Index].m_psDXGI_Adapter);
    TgERROR(nullptr != g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Adapter[psCXT_SWAP->m_uiAdapter_Index].m_psDX12_Device);
    psDX12_Device = g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Adapter[psCXT_SWAP->m_uiAdapter_Index].m_psDX12_Device;

    TgPARAM_CHECK_INDEX(psCXT_SWAP->m_tiCXT_EXEC.m_uiI, g_asKN_GPU_EXT_CXT_EXEC);
    psEXT_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + psCXT_SWAP->m_tiCXT_EXEC.m_uiI;


    /// Update the swap context with the most recent data from the output device that is displaying the majority of the render surface area (assuming a window).

    tgKN_OS_GPU_EXT_Update_Swap_Output( tiCXT_SWAP, psCXT_SWAP->m_uiOS_ID, true );


    /// Check to see if the swap chain already exists, which occurs in the case that we are resizing the output buffers.

    if (!bFirst_Time_Init)
    {
        if (bResize)
        {
            tgKN_GPU_EXT__Execute__Flush( psCXT_SWAP->m_tiCXT_EXEC );
            tgPM_MT_MX_Wait_Block( &psEXT_CXT_SWAP->m_sSwap_And_View_Lock );

            tgKN_GPU_EXT_CXT_SWAP_Free_For_Resize( tiCXT_SWAP );

            iRet = IDXGISwapChain4_ResizeBuffers(  psEXT_CXT_SWAP->m_psDXGI_Swap_Chain,
                                                   psCXT_SWAP->m_nuiSwap_Buffers,
                                                   psEXT_CXT_SWAP->m_sDXGI_Mode.Width,
                                                   psEXT_CXT_SWAP->m_sDXGI_Mode.Height,
                                                   psEXT_CXT_SWAP->m_sDXGI_Mode.Format,
                                                   DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH | DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING );

            if (iRet == DXGI_ERROR_DEVICE_REMOVED || iRet == DXGI_ERROR_DEVICE_RESET)
            {
                g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Adapter[psCXT_SWAP->m_uiAdapter_Index].m_uiIsReset = 1;
                tgPM_MT_MX_Release( &psEXT_CXT_SWAP->m_sSwap_And_View_Lock );
                tgKN_GPU_EXT__SwapChain__Free( tiCXT_SWAP );
                TgDEBUG_BREAK_AND_RETURN( KTgE_FAIL );
            };
            TgVERIFY(SUCCEEDED(iRet));

            TgERROR( psEXT_CXT_SWAP->m_sDXGI_Mode.Width == psCXT_SWAP->m_sMode.m_sBuffer.m_uiWidth );
            TgERROR( psEXT_CXT_SWAP->m_sDXGI_Mode.Height == psCXT_SWAP->m_sMode.m_sBuffer.m_uiHeight );

            psCXT_SWAP->m_sViewport.m_iPosX = 0;
            psCXT_SWAP->m_sViewport.m_iPosY = 0;
            psCXT_SWAP->m_sViewport.m_iWidth = (TgSINT_E32)psEXT_CXT_SWAP->m_sDXGI_Mode.Width;
            psCXT_SWAP->m_sViewport.m_iHeight = (TgSINT_E32)psEXT_CXT_SWAP->m_sDXGI_Mode.Height;

            psCXT_SWAP->m_sScissor_Rect.m_iLeft = 0;
            psCXT_SWAP->m_sScissor_Rect.m_iTop = 0;
            psCXT_SWAP->m_sScissor_Rect.m_iRight = psCXT_SWAP->m_sScissor_Rect.m_iLeft + psCXT_SWAP->m_sViewport.m_iWidth;
            psCXT_SWAP->m_sScissor_Rect.m_iBottom = psCXT_SWAP->m_sScissor_Rect.m_iLeft + psCXT_SWAP->m_sViewport.m_iHeight;
        }
    }
    else
    {
        D3D12_DESCRIPTOR_HEAP_DESC          sDX12_Heap;
        DXGI_SWAP_CHAIN_DESC1               sDXGI_Swap_Chain_1;
        DXGI_SWAP_CHAIN_FULLSCREEN_DESC     sDXGI_Swap_Chain_FS;
        IUnknown_P                          psUnknown;
        IDXGISwapChain1_P                   psDXGI_Swap_Chain_1;
        TgUINT_E32                          uiIndex;

        if (KTgMAX_U32 == psCXT_SWAP->m_uiScanout_Adapter_Enumeration_Index || KTgMAX_U32 == psCXT_SWAP->m_uiScanout_Output_Enumeration_Index)
        {
            /* This can happen if the attached window is off-screen. */
            psEXT_CXT_SWAP->m_sDXGI_Mode.Width = psCXT_SWAP->m_sMode.m_sBuffer.m_uiWidth;
            psEXT_CXT_SWAP->m_sDXGI_Mode.Height = psCXT_SWAP->m_sMode.m_sBuffer.m_uiHeight;
            psEXT_CXT_SWAP->m_sDXGI_Mode.RefreshRate.Numerator = psCXT_SWAP->m_sMode.m_uiRefresh_Rate__Numerator;
            psEXT_CXT_SWAP->m_sDXGI_Mode.RefreshRate.Denominator = psCXT_SWAP->m_sMode.m_uiRefresh_Rate__Denominator;
            psEXT_CXT_SWAP->m_sDXGI_Mode.Format = (DXGI_FORMAT)psCXT_SWAP->m_sMode.m_sBuffer.m_enFormat;
            psEXT_CXT_SWAP->m_sDXGI_Mode.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
            psEXT_CXT_SWAP->m_sDXGI_Mode.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
            psEXT_CXT_SWAP->m_sDXGI_Mode.Stereo = 0;
        }
        else
        {
            if(!tgKN_GPU_EXT_CXT_SWAP_Find_Mode( psCXT_SWAP, &psEXT_CXT_SWAP->m_sDXGI_Mode ))
            {
                TgDEBUG_BREAK_AND_RETURN( KTgE_FAIL );
            };
        };

        psEXT_CXT_SWAP->m_enDXGI_Format_DS = (DXGI_FORMAT)psCXT_SWAP->m_enFormat_DS;
        psEXT_CXT_SWAP->m_enDXGI_Format_RT = (DXGI_FORMAT)psCXT_SWAP->m_enFormat_RT;
        tgPM_MT_MX_Init( &psEXT_CXT_SWAP->m_sSwap_And_View_Lock, TgOS_TEXT("DX12 Swap Chain") );
        tgPM_MT_MX_Wait_Block( &psEXT_CXT_SWAP->m_sSwap_And_View_Lock );

        /* First time initialization - this is where we initialize all of the non re-entrant resources. */


        /// Create descriptor heaps. 

        tgMM_Set_U08_0x00( &sDX12_Heap, sizeof( sDX12_Heap ) );
        sDX12_Heap.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
        sDX12_Heap.NodeMask = psEXT_CXT_EXEC->m_uiNodeMask;
        sDX12_Heap.NumDescriptors = 1;
        sDX12_Heap.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;

        if (FAILED( ID3D12Device10_CreateDescriptorHeap( psDX12_Device, &sDX12_Heap, MS_REF IID_ID3D12DescriptorHeap, (TgVOID_PP)&psEXT_CXT_SWAP->m_sDSV.m_psDX12_Heap ) ))
        {
            tgPM_MT_MX_Release( &psEXT_CXT_SWAP->m_sSwap_And_View_Lock );
            tgKN_GPU_EXT__SwapChain__Free( tiCXT_SWAP );
            TgDEBUG_BREAK_AND_RETURN( KTgE_FAIL );
        };
        TgMACRO_KN_GPU_EXT_SET_NAME( psEXT_CXT_SWAP->m_sDSV.m_psDX12_Heap, u8"tgKN_GPU_EXT__SwapChain__Init: DSV" );
        psEXT_CXT_SWAP->m_sDSV.m_uiDescriptor_Size = ID3D12Device10_GetDescriptorHandleIncrementSize( psDX12_Device, sDX12_Heap.Type );
        ID3D12DescriptorHeap_GetCPUDescriptorHandleForHeapStart( psEXT_CXT_SWAP->m_sDSV.m_psDX12_Heap, &psEXT_CXT_SWAP->m_sDSV.m_sDX12_CPU_Handle );
        psEXT_CXT_SWAP->m_sDSV.m_nuiMax = 1;
        psEXT_CXT_SWAP->m_sDSV.m_uiMax  = psEXT_CXT_SWAP->m_sDSV.m_sDX12_CPU_Handle.ptr;
        psEXT_CXT_SWAP->m_sDSV.m_uiMax += psEXT_CXT_SWAP->m_sDSV.m_uiDescriptor_Size * psEXT_CXT_SWAP->m_sDSV.m_nuiMax;

        tgMM_Set_U08_0x00( &sDXGI_Swap_Chain_1, sizeof( sDXGI_Swap_Chain_1 ) );
        sDXGI_Swap_Chain_1.Width = psEXT_CXT_SWAP->m_sDXGI_Mode.Width;
        sDXGI_Swap_Chain_1.Height = psEXT_CXT_SWAP->m_sDXGI_Mode.Height;
        sDXGI_Swap_Chain_1.Format = psEXT_CXT_SWAP->m_sDXGI_Mode.Format;
        sDXGI_Swap_Chain_1.Stereo = psEXT_CXT_SWAP->m_sDXGI_Mode.Stereo;
        sDXGI_Swap_Chain_1.SampleDesc.Quality = 0;
        sDXGI_Swap_Chain_1.SampleDesc.Count = psCXT_SWAP->m_uiMSAA_Sample;
        sDXGI_Swap_Chain_1.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sDXGI_Swap_Chain_1.BufferCount = psCXT_SWAP->m_nuiSwap_Buffers;
        sDXGI_Swap_Chain_1.Scaling = DXGI_SCALING_NONE;
        sDXGI_Swap_Chain_1.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
        sDXGI_Swap_Chain_1.AlphaMode = DXGI_ALPHA_MODE_IGNORE;
        sDXGI_Swap_Chain_1.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH | DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING;

        sDXGI_Swap_Chain_FS.RefreshRate = psEXT_CXT_SWAP->m_sDXGI_Mode.RefreshRate;
        sDXGI_Swap_Chain_FS.ScanlineOrdering = psEXT_CXT_SWAP->m_sDXGI_Mode.ScanlineOrdering;
        sDXGI_Swap_Chain_FS.Scaling = DXGI_MODE_SCALING_CENTERED;
        sDXGI_Swap_Chain_FS.Windowed = TRUE;

        ID3D12CommandQueue_QueryInterface( psEXT_CXT_EXEC->m_sCmd_Queue[D3D12_COMMAND_LIST_TYPE_DIRECT].m_psDX12_Cmd_Queue, MS_REF IID_IUnknown, (TgVOID_PP)&psUnknown );

    #if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
        iRet = IDXGIFactory7_CreateSwapChainForHwnd( g_pDXGIFactory, psUnknown, sHWND.hWnd, &sDXGI_Swap_Chain_1, &sDXGI_Swap_Chain_FS, nullptr, &psDXGI_Swap_Chain_1 );
    #else
        iRet = IDXGIFactory7_CreateSwapChainForCoreWindow( g_pDXGIFactory, pUnknown, (IUnknown*)[CoreWindow Crap], &sDXGI_Swap_Chain_1, nullptr, &psDXGI_Swap_Chain_1 );
    #endif

        IUnknown_Release( psUnknown );
        psUnknown = nullptr;

        if (FAILED( iRet ))
        {
            tgPM_MT_MX_Release( &psEXT_CXT_SWAP->m_sSwap_And_View_Lock );
            tgKN_GPU_EXT__SwapChain__Free( tiCXT_SWAP );
            TgDEBUG_BREAK_AND_RETURN( KTgE_FAIL );
        };
        iRet = IDXGISwapChain1_QueryInterface( psDXGI_Swap_Chain_1, MS_REF IID_IDXGISwapChain4, (TgVOID_PP)&psEXT_CXT_SWAP->m_psDXGI_Swap_Chain );
        if (FAILED( iRet ))
        {
            TgERROR_MSG(false, u8"tgKN_GPU_EXT_CXT_SWAP__Init: Failed to create swap chain");
            psEXT_CXT_SWAP->m_psDXGI_Swap_Chain = nullptr;
            TgVERIFY(0 == IDXGISwapChain1_Release( psDXGI_Swap_Chain_1 ));
            tgPM_MT_MX_Release( &psEXT_CXT_SWAP->m_sSwap_And_View_Lock );
            tgKN_GPU_EXT__SwapChain__Free( tiCXT_SWAP );
            TgDEBUG_BREAK_AND_RETURN( KTgE_FAIL );
        };
        TgVERIFY(1 == IDXGISwapChain1_Release( psDXGI_Swap_Chain_1 ));
        TgVERIFY(SUCCEEDED(IDXGIFactory7_MakeWindowAssociation( g_pDXGIFactory, sHWND.hWnd, DXGI_MWA_NO_ALT_ENTER )));


        /// Create synchronization objects.

        TgVERIFY(nullptr == psEXT_CXT_SWAP->m_psDX12_Fence && nullptr == psEXT_CXT_SWAP->m_psFence_Event);
        TgVERIFY(SUCCEEDED(ID3D12Device10_CreateFence( psDX12_Device, atomic_load( &psEXT_CXT_SWAP->m_xuiFence_Value ), D3D12_FENCE_FLAG_NONE, MS_REF IID_ID3D12Fence,
                                                       (TgVOID_PP) &psEXT_CXT_SWAP->m_psDX12_Fence ) ) );
        atomic_fetch_add( &psEXT_CXT_SWAP->m_xuiFence_Value, 1 );
        psEXT_CXT_SWAP->m_psFence_Event = g_pfnCreateEvent( nullptr, FALSE, FALSE, nullptr );
        TgMACRO_KN_GPU_EXT_SET_NAME(psEXT_CXT_SWAP->m_psDX12_Fence, u8"tgKN_GPU_EXT__SwapChain__Init: Fence: Direct SWAP");


        /// Create the reserved command resources.

        tgMM_Set_U08_0x00( &sDX12_Heap, sizeof( D3D12_DESCRIPTOR_HEAP_DESC ) );
        sDX12_Heap.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
        sDX12_Heap.NodeMask = psEXT_CXT_EXEC->m_uiNodeMask;
        sDX12_Heap.NumDescriptors = 1;
        sDX12_Heap.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;

        for (uiIndex = 0; uiIndex < psCXT_SWAP->m_nuiSwap_Buffers; ++uiIndex)
        {
            STg2_KN_GPU_EXT_Output_Sync_PC     psEXT_Sync = psEXT_CXT_SWAP->m_sCmd + uiIndex;

            if (FAILED( ID3D12Device10_CreateCommandAllocator( psDX12_Device, D3D12_COMMAND_LIST_TYPE_DIRECT, MS_REF IID_ID3D12CommandAllocator,
                                                               (TgVOID_PP)(&psEXT_Sync->m_psDX12_Cmd_Allocator_Reserved) ) ))
            {
                tgPM_MT_MX_Release( &psEXT_CXT_SWAP->m_sSwap_And_View_Lock );
                tgKN_GPU_EXT__SwapChain__Free( tiCXT_SWAP );
                TgDEBUG_BREAK_AND_RETURN( KTgE_FAIL );
            };

            if (FAILED( ID3D12Device10_CreateCommandList1( psDX12_Device, psEXT_CXT_EXEC->m_uiNodeMask, D3D12_COMMAND_LIST_TYPE_DIRECT, D3D12_COMMAND_LIST_FLAG_NONE,
                                                           MS_REF IID_ID3D12GraphicsCommandList8, (TgVOID_PP)&psEXT_Sync->m_psDX12_Cmd_List + 0 ) ))
            {
                tgPM_MT_MX_Release( &psEXT_CXT_SWAP->m_sSwap_And_View_Lock );
                tgKN_GPU_EXT__SwapChain__Free( tiCXT_SWAP );
                TgDEBUG_BREAK_AND_RETURN( KTgE_FAIL );
            };

            if (FAILED( ID3D12Device10_CreateCommandList1( psDX12_Device, psEXT_CXT_EXEC->m_uiNodeMask, D3D12_COMMAND_LIST_TYPE_DIRECT, D3D12_COMMAND_LIST_FLAG_NONE,
                                                           MS_REF IID_ID3D12GraphicsCommandList8, (TgVOID_PP)&psEXT_Sync->m_psDX12_Cmd_List + 1 ) ))
            {
                tgPM_MT_MX_Release( &psEXT_CXT_SWAP->m_sSwap_And_View_Lock );
                tgKN_GPU_EXT__SwapChain__Free( tiCXT_SWAP );
                TgDEBUG_BREAK_AND_RETURN( KTgE_FAIL );
            };

            if (FAILED( ID3D12Device10_CreateDescriptorHeap( psDX12_Device, &sDX12_Heap, MS_REF IID_ID3D12DescriptorHeap, (TgVOID_PP)&psEXT_Sync->m_sRTV.m_psDX12_Heap ) ))
            {
                tgPM_MT_MX_Release( &psEXT_CXT_SWAP->m_sSwap_And_View_Lock );
                tgKN_GPU_EXT__SwapChain__Free( tiCXT_SWAP );
                TgDEBUG_BREAK_AND_RETURN( KTgE_FAIL );
            };
            psEXT_Sync->m_sRTV.m_uiDescriptor_Size = ID3D12Device10_GetDescriptorHandleIncrementSize( psDX12_Device, sDX12_Heap.Type );
            ID3D12DescriptorHeap_GetCPUDescriptorHandleForHeapStart( psEXT_Sync->m_sRTV.m_psDX12_Heap, &psEXT_Sync->m_sRTV.m_sDX12_CPU_Handle );
            psEXT_Sync->m_sRTV.m_nuiMax = 1;
            psEXT_Sync->m_sRTV.m_uiMax  = psEXT_Sync->m_sRTV.m_sDX12_CPU_Handle.ptr;
            psEXT_Sync->m_sRTV.m_uiMax += psEXT_Sync->m_sRTV.m_uiDescriptor_Size * psEXT_Sync->m_sRTV.m_nuiMax;

            TgMACRO_KN_GPU_EXT_SET_NAME( psEXT_Sync->m_psDX12_Cmd_Allocator_Reserved, u8"tgKN_GPU_EXT__SwapChain__Init: SYNC: Allocator" );
            TgMACRO_KN_GPU_EXT_SET_NAME( psEXT_Sync->m_psDX12_Cmd_List[0], u8"tgKN_GPU_EXT__SwapChain__Init: SYNC: CMD List 0" );
            TgMACRO_KN_GPU_EXT_SET_NAME( psEXT_Sync->m_psDX12_Cmd_List[1], u8"tgKN_GPU_EXT__SwapChain__Init: SYNC: CMD List 1" );
            TgMACRO_KN_GPU_EXT_SET_NAME( psEXT_Sync->m_sRTV.m_psDX12_Heap, u8"tgKN_GPU_EXT__SwapChain__Init: SYNC: Heap RTV" );
        };
    };

    TgVERIFY(nullptr != psEXT_CXT_SWAP->m_psDX12_Fence && nullptr != psEXT_CXT_SWAP->m_psFence_Event);


    /// Attempt to set the colour space.

    psEXT_CXT_SWAP->m_enDXGI_Colour_Space = DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P709;
    psCXT_SWAP->m_enColour_Space = ETgKN_GPU_HLSL_COLOR_SPACE_G22_NONE_P709;
    psCXT_SWAP->m_bHDR_Enabled = false;

    if (ETgKN_GPU_EXT_FORMAT_R16G16B16A16_FLOAT == psCXT_SWAP->m_sMode.m_sBuffer.m_enFormat)
    {
        psEXT_CXT_SWAP->m_enDXGI_Colour_Space = DXGI_COLOR_SPACE_RGB_FULL_G10_NONE_P709;
        psCXT_SWAP->m_enColour_Space = ETgKN_GPU_HLSL_COLOR_SPACE_G10_NONE_P709;
    }

    if (psCXT_SWAP->m_bHDR_Supported && psCXT_SWAP->m_bHDR_Request && ETgKN_GPU_EXT_FORMAT_R10G10B10A2_UNORM == psCXT_SWAP->m_sMode.m_sBuffer.m_enFormat)
    {
        psEXT_CXT_SWAP->m_enDXGI_Colour_Space = DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020;
        psCXT_SWAP->m_enColour_Space = ETgKN_GPU_HLSL_COLOR_SPACE_G2084_NONE_P2020;
    }

    iRet = IDXGISwapChain4_SetColorSpace1( psEXT_CXT_SWAP->m_psDXGI_Swap_Chain, psEXT_CXT_SWAP->m_enDXGI_Colour_Space );

    if (SUCCEEDED( iRet ) && psCXT_SWAP->m_bHDR_Supported && psCXT_SWAP->m_bHDR_Request)
    {
        iRet = tgKN_GPU_EXT_CXT_SWAP_Set_HDR_Metadata( tiCXT_SWAP );
        psCXT_SWAP->m_bHDR_Enabled = true;
    };

    if (FAILED( iRet ))
    {
        tgPM_MT_MX_Release( &psEXT_CXT_SWAP->m_sSwap_And_View_Lock );
        tgKN_GPU_EXT__SwapChain__Free( tiCXT_SWAP );
        TgDEBUG_BREAK_AND_RETURN( KTgE_FAIL );
    };


    /// Create the default depth stencil resource and view.

    if (ETgKN_GPU_EXT_FORMAT_UNKNOWN != psCXT_SWAP->m_enFormat_DS && nullptr == psEXT_CXT_SWAP->m_psDX12_Depth_Stencil)
    {
        D3D12_HEAP_PROPERTIES               sDX12_Heap_Properties;
        D3D12_RESOURCE_DESC                 sDX12_Resource;
        D3D12_CLEAR_VALUE                   sDX12_Clear_Value;
        D3D12_DEPTH_STENCIL_VIEW_DESC       sDX12_DSV_Desc;
        D3D12_CPU_DESCRIPTOR_HANDLE         sDX12_CPU_Heap_DSV;

        tgMM_Set_U08_0x00( &sDX12_Heap_Properties, sizeof(sDX12_Heap_Properties) );
        sDX12_Heap_Properties.Type = D3D12_HEAP_TYPE_DEFAULT;
        sDX12_Heap_Properties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
        sDX12_Heap_Properties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
        sDX12_Heap_Properties.CreationNodeMask = psEXT_CXT_EXEC->m_uiNodeMask;
        sDX12_Heap_Properties.VisibleNodeMask = psEXT_CXT_EXEC->m_uiNodeMask;

        tgMM_Set_U08_0x00( &sDX12_Resource, sizeof(sDX12_Resource) );
        sDX12_Resource.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
        sDX12_Resource.Alignment = 0;
        sDX12_Resource.Width = psEXT_CXT_SWAP->m_sDXGI_Mode.Width;
        sDX12_Resource.Height = psEXT_CXT_SWAP->m_sDXGI_Mode.Height;
        sDX12_Resource.DepthOrArraySize = 1;
        sDX12_Resource.MipLevels = 1;
        sDX12_Resource.Format = psEXT_CXT_SWAP->m_enDXGI_Format_DS;
        sDX12_Resource.SampleDesc.Count = 1;
        sDX12_Resource.SampleDesc.Quality = 0;
        sDX12_Resource.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
        sDX12_Resource.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

        tgMM_Set_U08_0x00( &sDX12_Clear_Value, sizeof(sDX12_Clear_Value) );
        sDX12_Clear_Value.Format = psEXT_CXT_SWAP->m_enDXGI_Format_DS;
        sDX12_Clear_Value.DepthStencil.Depth = 1.0F;
        sDX12_Clear_Value.DepthStencil.Stencil = 0;

        iRet = ID3D12Device10_CreateCommittedResource1( psDX12_Device, &sDX12_Heap_Properties, D3D12_HEAP_FLAG_NONE, &sDX12_Resource, D3D12_RESOURCE_STATE_DEPTH_WRITE,
                                                        &sDX12_Clear_Value, nullptr, MS_REF IID_ID3D12Resource, (TgVOID_PP)&psEXT_CXT_SWAP->m_psDX12_Depth_Stencil );

        if (FAILED(iRet))
        {
            TgERROR_MSG(false, u8"tgKN_GPU_EXT_CXT_SWAP__Init: Failed to create depth stencil buffer");
            tgPM_MT_MX_Release( &psEXT_CXT_SWAP->m_sSwap_And_View_Lock );
            tgKN_GPU_EXT__SwapChain__Free( tiCXT_SWAP );
            TgDEBUG_BREAK_AND_RETURN( KTgE_FAIL );
        };

        TgMACRO_KN_GPU_EXT_SET_NAME( psEXT_CXT_SWAP->m_psDX12_Depth_Stencil, u8"tgKN_GPU_EXT__SwapChain__Init: Depth Stencil Buffer" );
        tgMM_Set_U08_0x00( &sDX12_DSV_Desc, sizeof( sDX12_DSV_Desc ) );
        sDX12_DSV_Desc.Format = psEXT_CXT_SWAP->m_enDXGI_Format_DS;
        sDX12_DSV_Desc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
        sDX12_DSV_Desc.Flags = D3D12_DSV_FLAG_NONE;

        ID3D12DescriptorHeap_GetCPUDescriptorHandleForHeapStart( psEXT_CXT_SWAP->m_sDSV.m_psDX12_Heap, &sDX12_CPU_Heap_DSV );
        ID3D12Device10_CreateDepthStencilView( psDX12_Device, psEXT_CXT_SWAP->m_psDX12_Depth_Stencil, &sDX12_DSV_Desc, sDX12_CPU_Heap_DSV );
    };


    /// Create render target resource views.

    if (bFirst_Time_Init || bResize)
    {
        TgUINT_E32                          uiIndex;
        TgUINT_E64                          uiFence_Value;

        uiFence_Value = atomic_fetch_add( &psEXT_CXT_SWAP->m_xuiFence_Value, 1 );
        TgVERIFY( SUCCEEDED( ID3D12CommandQueue_Signal( psEXT_CXT_EXEC->m_sCmd_Queue[D3D12_COMMAND_LIST_TYPE_DIRECT].m_psDX12_Cmd_Queue,
                                                        psEXT_CXT_SWAP->m_psDX12_Fence, uiFence_Value ) ) );

        for (uiIndex = 0; uiIndex < psCXT_SWAP->m_nuiSwap_Buffers; ++uiIndex)
        {
            STg2_KN_GPU_EXT_Output_Sync_PC      psEXT_Sync = psEXT_CXT_SWAP->m_sCmd + uiIndex;

            D3D12_CPU_DESCRIPTOR_HANDLE         sDX12_CPU_Heap_RTV;

            TgVERIFY( nullptr != psEXT_Sync->m_sRTV.m_psDX12_Heap );
            TgVERIFY( nullptr == psEXT_Sync->m_psDX12_Render_Target_View );

            ID3D12DescriptorHeap_GetCPUDescriptorHandleForHeapStart( psEXT_Sync->m_sRTV.m_psDX12_Heap, &sDX12_CPU_Heap_RTV );
            IDXGISwapChain4_GetBuffer( psEXT_CXT_SWAP->m_psDXGI_Swap_Chain, uiIndex, MS_REF IID_ID3D12Resource, (TgVOID_PP)(&psEXT_Sync->m_psDX12_Render_Target_View) );
            ID3D12Device10_CreateRenderTargetView( psDX12_Device, psEXT_Sync->m_psDX12_Render_Target_View, nullptr, sDX12_CPU_Heap_RTV );
            psEXT_Sync->m_uiFence_Value_Present = uiFence_Value;

        #if defined(TgCOMPILE__GPU_OBJECT_NAME) && TgCOMPILE__GPU_OBJECT_NAME
            {
                TgCHAR_U8                           uszDebugName[128];

                tgUSZ_PrintF( uszDebugName, sizeof(uszDebugName), u8"Swap Chain Buffer (%d) (%d)", psCXT_SWAP->m_tiCXT_EXEC.m_uiI, tiCXT_SWAP.m_uiI );
                TgMACRO_KN_GPU_EXT_SET_NAME_WTH_VAR( psEXT_Sync->m_psDX12_Render_Target_View, uszDebugName );
            };
        /*# defined(TgCOMPILE__GPU_OBJECT_NAME) && TgCOMPILE__GPU_OBJECT_NAME */
        #endif
        };
    }

    tgPM_MT_MX_Release( &psEXT_CXT_SWAP->m_sSwap_And_View_Lock );
    return (KTgS_OK);

}


/* ---- tgKN_GPU_EXT__SwapChain__Free ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_EXT__SwapChain__Free( TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP )
{
    STg2_KN_GPU_EXT_CXT_SWAP_PC         psEXT_CXT_SWAP = g_asKN_GPU_EXT_CXT_SWAP + tiCXT_SWAP.m_uiI;

    TgRSIZE                             uiIndex;

    TgPARAM_CHECK_INDEX(tiCXT_SWAP.m_uiI, g_asKN_GPU_EXT_CXT_SWAP);
    TgERROR(nullptr != psEXT_CXT_SWAP);

    tgKN_GPU_EXT__Execute__Flush( g_asKN_GPU_CXT_SWAP[tiCXT_SWAP.m_uiI].m_tiCXT_EXEC );
    tgKN_GPU_EXT_CXT_SWAP_Free_For_Resize( tiCXT_SWAP );

    for (uiIndex = 0; uiIndex < KTgKN_GPU_MAX_BUFFER_IN_FLIP_CHAIN; ++uiIndex)
    {
        if (nullptr != psEXT_CXT_SWAP->m_sCmd[uiIndex].m_sRTV.m_psDX12_Heap)
            TgVERIFY( 0 == ID3D12DescriptorHeap_Release( psEXT_CXT_SWAP->m_sCmd[uiIndex].m_sRTV.m_psDX12_Heap ) );
        if (nullptr != psEXT_CXT_SWAP->m_sCmd[uiIndex].m_psDX12_Cmd_List[1])
            TgVERIFY( 0 == ID3D12GraphicsCommandList8_Release( psEXT_CXT_SWAP->m_sCmd[uiIndex].m_psDX12_Cmd_List[1] ) );
        if (nullptr != psEXT_CXT_SWAP->m_sCmd[uiIndex].m_psDX12_Cmd_List[0])
            TgVERIFY( 0 == ID3D12GraphicsCommandList8_Release( psEXT_CXT_SWAP->m_sCmd[uiIndex].m_psDX12_Cmd_List[0] ) );
        if (nullptr != psEXT_CXT_SWAP->m_sCmd[uiIndex].m_psDX12_Cmd_Allocator_Reserved)
            TgVERIFY( 0 == ID3D12CommandAllocator_Release( psEXT_CXT_SWAP->m_sCmd[uiIndex].m_psDX12_Cmd_Allocator_Reserved ) );
    };

    if (nullptr != psEXT_CXT_SWAP->m_psDX12_Fence)
    {
        TgVERIFY( 0 == ID3D12Fence_Release( psEXT_CXT_SWAP->m_psDX12_Fence ) );
        psEXT_CXT_SWAP->m_psDX12_Fence= nullptr;
    };

    if (nullptr != psEXT_CXT_SWAP->m_psFence_Event)
    {
        g_pfnCloseHandle( psEXT_CXT_SWAP->m_psFence_Event );
        psEXT_CXT_SWAP->m_psFence_Event = nullptr;
    };

    if (nullptr != psEXT_CXT_SWAP->m_psDXGI_Swap_Chain)
    {
        TgVERIFY( 0 == IDXGISwapChain4_Release( psEXT_CXT_SWAP->m_psDXGI_Swap_Chain ) );
        psEXT_CXT_SWAP->m_psDXGI_Swap_Chain = nullptr;
    };

    if (nullptr != psEXT_CXT_SWAP->m_sDSV.m_psDX12_Heap)
    {
        TgVERIFY( 0 == ID3D12DescriptorHeap_Release( psEXT_CXT_SWAP->m_sDSV.m_psDX12_Heap ) );
    }

    tgPM_MT_MX_Free( &psEXT_CXT_SWAP->m_sSwap_And_View_Lock );
    tgMM_Set_U08_0x00( psEXT_CXT_SWAP, sizeof( STg2_KN_GPU_EXT_CXT_SWAP ) );
    psEXT_CXT_SWAP->m_tiID = KTgKN_GPU_CXT_SWAP_ID__INVALID;
}


/* ---- tgKN_GPU_EXT__SwapChain__Get_Back_Buffer --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_EXT__SwapChain__Get_Back_Buffer( D3D12_CPU_DESCRIPTOR_HANDLE_P psHeap_RTV, D3D12_CPU_DESCRIPTOR_HANDLE_P psHeap_DSV,
                                                   STg2_KN_GPU_HLSL_Output_DESC_PC psOutput_DESC, TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP )
{
    TgPARAM_CHECK_INDEX( tiCXT_SWAP.m_uiI, g_asKN_GPU_CXT_SWAP );
    TgPARAM_CHECK( tgKN_GPU_CXT_SWAP_ID_Is_Equal( &(g_asKN_GPU_CXT_SWAP[tiCXT_SWAP.m_uiI].m_tiCXT_SWAP_S), tiCXT_SWAP ) );
    TgPARAM_CHECK_INDEX( g_asKN_GPU_CXT_SWAP[tiCXT_SWAP.m_uiI].m_tiCXT_EXEC.m_uiI, g_asKN_GPU_CXT_EXEC );
    TgPARAM_CHECK( tgKN_GPU_CXT_EXEC_ID_Is_Equal( &(g_asKN_GPU_CXT_EXEC[g_asKN_GPU_CXT_SWAP[tiCXT_SWAP.m_uiI].m_tiCXT_EXEC.m_uiI].m_tiCXT_EXEC_S),
                   g_asKN_GPU_CXT_SWAP[tiCXT_SWAP.m_uiI].m_tiCXT_EXEC ) );
    {
        STg2_KN_GPU_EXT_CXT_SWAP_PC         psEXT_CXT_SWAP = g_asKN_GPU_EXT_CXT_SWAP + tiCXT_SWAP.m_uiI;
        STg2_KN_GPU_CXT_SWAP_PC             psCXT_SWAP = g_asKN_GPU_CXT_SWAP + tiCXT_SWAP.m_uiI;
        STg2_KN_GPU_EXT_CMD_Queue_PC        psEXT_CMD_Queue = g_asKN_GPU_EXT_CXT_EXEC[psCXT_SWAP->m_tiCXT_EXEC.m_uiI].m_sCmd_Queue + D3D12_COMMAND_LIST_TYPE_DIRECT;

        TgSINT_E32                          iSwap_Index;
        TgUINT_E64                          uiFence_Value;
        STg2_KN_GPU_EXT_Output_Sync_P       psEXT_Output_Sync;
        D3D12_RESOURCE_BARRIER              sDX12_Barrier;

        tgPM_MT_MX_Wait_Block( &psEXT_CXT_SWAP->m_sSwap_And_View_Lock );

        iSwap_Index = (TgSINT_E32)IDXGISwapChain4_GetCurrentBackBufferIndex( psEXT_CXT_SWAP->m_psDXGI_Swap_Chain );

        /* Check to make sure that swap command for this buffer has completed (fence), and reset the swap resources. */

        uiFence_Value = psEXT_CXT_SWAP->m_sCmd[iSwap_Index].m_uiFence_Value_Present;
        while (ID3D12Fence_GetCompletedValue( psEXT_CXT_SWAP->m_psDX12_Fence ) < uiFence_Value)
        {
            TgVERIFY( SUCCEEDED( ID3D12Fence_SetEventOnCompletion( psEXT_CXT_SWAP->m_psDX12_Fence, uiFence_Value, psEXT_CXT_SWAP->m_psFence_Event ) ) );
            g_pfnWaitForSingleObjectEx( psEXT_CXT_SWAP->m_psFence_Event, 1, FALSE );
        };

        /* Reset the resources used by the swap routines for this index. */

        psEXT_Output_Sync = psEXT_CXT_SWAP->m_sCmd + iSwap_Index;
        TgVERIFY( SUCCEEDED( ID3D12CommandAllocator_Reset( psEXT_Output_Sync->m_psDX12_Cmd_Allocator_Reserved ) ) );
        TgVERIFY( SUCCEEDED( ID3D12GraphicsCommandList8_Reset( psEXT_Output_Sync->m_psDX12_Cmd_List[0], psEXT_Output_Sync->m_psDX12_Cmd_Allocator_Reserved, nullptr ) ) );

        /* Transition the back buffer from presentation to render target. */
        tgMM_Set_U08_0x00( &sDX12_Barrier, sizeof( D3D12_RESOURCE_BARRIER ) );
        sDX12_Barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
        sDX12_Barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
        sDX12_Barrier.Transition.pResource = psEXT_CXT_SWAP->m_sCmd[iSwap_Index].m_psDX12_Render_Target_View;
        sDX12_Barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
        sDX12_Barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
        sDX12_Barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

        ID3D12GraphicsCommandList8_ResourceBarrier( psEXT_CXT_SWAP->m_sCmd[iSwap_Index].m_psDX12_Cmd_List[0], 1, &sDX12_Barrier );

        TgVERIFY( SUCCEEDED( ID3D12GraphicsCommandList8_Close( psEXT_CXT_SWAP->m_sCmd[iSwap_Index].m_psDX12_Cmd_List[0] ) ) );
        ID3D12CommandQueue_ExecuteCommandLists( psEXT_CMD_Queue->m_psDX12_Cmd_Queue, 1, (ID3D12CommandList_PP)(psEXT_CXT_SWAP->m_sCmd[iSwap_Index].m_psDX12_Cmd_List + 0) );

        ID3D12DescriptorHeap_GetCPUDescriptorHandleForHeapStart( psEXT_CXT_SWAP->m_sCmd[iSwap_Index].m_sRTV.m_psDX12_Heap, psHeap_RTV );
        ID3D12DescriptorHeap_GetCPUDescriptorHandleForHeapStart( psEXT_CXT_SWAP->m_sDSV.m_psDX12_Heap, psHeap_DSV );

        tgKN_OS_GPU_EXT_Update_Swap_Output( tiCXT_SWAP, psCXT_SWAP->m_uiOS_ID, false );

        psOutput_DESC->m_fPerceptual_Exponent = 2.2F;
        psOutput_DESC->m_fSDR_In_HDR_Nits_Level = psCXT_SWAP->m_fSDR_In_HDR_Nits_Level;
        psOutput_DESC->m_enColour_Space = psCXT_SWAP->m_enColour_Space;
        psOutput_DESC->m_bHDR_Enabled = psCXT_SWAP->m_bHDR_Enabled;
        psOutput_DESC->m_fMin_Luminance = psCXT_SWAP->m_fMin_Luminance;
        psOutput_DESC->m_fMax_Luminance = psCXT_SWAP->m_fMax_Luminance;
        psOutput_DESC->m_fMax_Full_Frame_Luminance = psCXT_SWAP->m_fMax_Full_Frame_Luminance;

        return (KTgS_OK);
    };
}


/* ---- tgKN_GPU_EXT__SwapChain__Present ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_EXT__SwapChain__Present( TgKN_GPU_CXT_WORK_ID_C tiCXT_WORK, TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP )
{
    TgPARAM_CHECK_INDEX( tiCXT_SWAP.m_uiI, g_asKN_GPU_CXT_SWAP );
    TgPARAM_CHECK( tgKN_GPU_CXT_SWAP_ID_Is_Equal( &(g_asKN_GPU_CXT_SWAP[tiCXT_SWAP.m_uiI].m_tiCXT_SWAP_S), tiCXT_SWAP ) );
    TgPARAM_CHECK_INDEX( g_asKN_GPU_CXT_SWAP[tiCXT_SWAP.m_uiI].m_tiCXT_EXEC.m_uiI, g_asKN_GPU_CXT_EXEC );
    TgPARAM_CHECK( tgKN_GPU_CXT_EXEC_ID_Is_Equal( &(g_asKN_GPU_CXT_EXEC[g_asKN_GPU_CXT_SWAP[tiCXT_SWAP.m_uiI].m_tiCXT_EXEC.m_uiI].m_tiCXT_EXEC_S),
                   g_asKN_GPU_CXT_SWAP[tiCXT_SWAP.m_uiI].m_tiCXT_EXEC ) );
    {
        STg2_KN_GPU_EXT_CXT_SWAP_PC         psEXT_CXT_SWAP = g_asKN_GPU_EXT_CXT_SWAP + tiCXT_SWAP.m_uiI;
        STg2_KN_GPU_CXT_SWAP_PC             psCXT_SWAP = g_asKN_GPU_CXT_SWAP + tiCXT_SWAP.m_uiI;
        STg2_KN_GPU_EXT_CXT_EXEC_PC         psEXT_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + psCXT_SWAP->m_tiCXT_EXEC.m_uiI;
        STg2_KN_GPU_EXT_CMD_Queue_PC        psEXT_CMD_Queue = psEXT_CXT_EXEC->m_sCmd_Queue + D3D12_COMMAND_LIST_TYPE_DIRECT;

        TgSINT_E32                          iSwap_Index;
        TgUINT_E64                          uiFence_Value;
        STg2_KN_GPU_EXT_Output_Sync_P       psEXT_Output_Sync;
        D3D12_RESOURCE_BARRIER              sDX12_Barrier;
        HRESULT                             iRet;

        iSwap_Index = (TgSINT_E32)IDXGISwapChain4_GetCurrentBackBufferIndex( psEXT_CXT_SWAP->m_psDXGI_Swap_Chain );

    #if TgCOMPILE__RENDER_DEBUG_OUTPUT
        /* Draw some text. */
        if (tiCXT_WORK.m_uiKI)
        {
            UTg2_KN_GPU_CMD                     uCMD;
            D3D12_CPU_DESCRIPTOR_HANDLE         shHeap_RTV;
            D3D12_CPU_DESCRIPTOR_HANDLE         shHeap_DSV;

            uCMD = tgKN_GPU_EXT__Execute__Command_List_Acquire( tiCXT_WORK, D3D12_COMMAND_LIST_TYPE_DIRECT );
            PIXBeginEvent_ThatWorksInC_ID3D12GraphicsCommandList( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 0, "SWAP: Draw Debug Text" );
            tgKN_GPU_EXT__CMD__Set_Graphics_Root_Signature_From_Default( uCMD, ETgKN_GPU_DEFAULT_ROOT_SIGNATURE_DEBUG );
            ID3D12DescriptorHeap_GetCPUDescriptorHandleForHeapStart( psEXT_CXT_SWAP->m_sCmd[iSwap_Index].m_sRTV.m_psDX12_Heap, &shHeap_RTV );
            ID3D12DescriptorHeap_GetCPUDescriptorHandleForHeapStart( psEXT_CXT_SWAP->m_sDSV.m_psDX12_Heap, &shHeap_DSV );
            ID3D12GraphicsCommandList8_OMSetRenderTargets( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 1, &shHeap_RTV, FALSE, &shHeap_DSV );
            tgKN_GPU_EXT__SwapChain__Set_Viewport_and_Scissor( tiCXT_SWAP, uCMD );
            tgKN_GPU__SwapChain__Present_Print_Debug_Stats( uCMD, tiCXT_SWAP );
            PIXEndEvent_ThatWorksInC_ID3D12GraphicsCommandList( uCMD.psEXT->m_psDX12_Graphics_Cmd_List );
            tgKN_GPU_EXT__CMD__Command_List_Close( uCMD );
        }
    /*# TgCOMPILE__RENDER_DEBUG_OUTPUT */
    #endif

        psEXT_Output_Sync = psEXT_CXT_SWAP->m_sCmd + iSwap_Index;
        TgVERIFY( SUCCEEDED( ID3D12GraphicsCommandList8_Reset( psEXT_Output_Sync->m_psDX12_Cmd_List[1], psEXT_Output_Sync->m_psDX12_Cmd_Allocator_Reserved, nullptr ) ) );

        /* Transition the state of the completed back buffer from render target to ready for presentation (front buffer). */
        tgMM_Set_U08_0x00( &sDX12_Barrier, sizeof( D3D12_RESOURCE_BARRIER ) );
        sDX12_Barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
        sDX12_Barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
        sDX12_Barrier.Transition.pResource = psEXT_Output_Sync->m_psDX12_Render_Target_View;
        sDX12_Barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
        sDX12_Barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
        sDX12_Barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

        ID3D12GraphicsCommandList8_ResourceBarrier( psEXT_Output_Sync->m_psDX12_Cmd_List[1], 1, &sDX12_Barrier );

        TgVERIFY( SUCCEEDED( ID3D12GraphicsCommandList8_Close( psEXT_Output_Sync->m_psDX12_Cmd_List[1] ) ) );
        ID3D12CommandQueue_ExecuteCommandLists( psEXT_CMD_Queue->m_psDX12_Cmd_Queue, 1, (ID3D12CommandList_PP)(psEXT_Output_Sync->m_psDX12_Cmd_List + 1) );

        /* Present the transitioned back buffer. */
        iRet = IDXGISwapChain4_Present( psEXT_CXT_SWAP->m_psDXGI_Swap_Chain, psCXT_SWAP->m_uiVSync, 0 == psCXT_SWAP->m_uiVSync ? DXGI_PRESENT_ALLOW_TEARING : 0 );
        if ((DXGI_ERROR_DEVICE_REMOVED == iRet) || (DXGI_ERROR_DEVICE_RESET == iRet))
        {
            g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Adapter[psCXT_SWAP->m_uiAdapter_Index].m_uiIsReset = 1;
            tgPM_MT_MX_Release( &psEXT_CXT_SWAP->m_sSwap_And_View_Lock );
            TgDEBUG_BREAK_AND_RETURN( KTgE_FAIL );
        };

        /* Schedule a Signal command in the queue to verify when the transition to front buffer is completed. */
        uiFence_Value = atomic_fetch_add( &psEXT_CXT_SWAP->m_xuiFence_Value, 1 );
        TgVERIFY( SUCCEEDED( ID3D12CommandQueue_Signal( psEXT_CMD_Queue->m_psDX12_Cmd_Queue, psEXT_CXT_SWAP->m_psDX12_Fence, uiFence_Value ) ) );
        psEXT_Output_Sync->m_uiFence_Value_Present = uiFence_Value;

        tgPM_MT_MX_Release( &psEXT_CXT_SWAP->m_sSwap_And_View_Lock );
        return (KTgS_OK);
    }
}


/* ---- tgKN_GPU_EXT__SwapChain__Set_Viewport_and_Scissor ------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_EXT__SwapChain__Set_Viewport_and_Scissor( TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP, UTg2_KN_GPU_CMD_C uCMD )
{
    STg2_KN_GPU_CXT_SWAP_PC             psCXT_SWAP = g_asKN_GPU_CXT_SWAP + tiCXT_SWAP.m_uiI;

    D3D12_VIEWPORT                      sDX12_Viewport;
    D3D12_RECT                          sDX12_Rect;

    TgPARAM_CHECK_INDEX(tiCXT_SWAP.m_uiI, g_asKN_GPU_CXT_SWAP);
    TgPARAM_CHECK_INDEX(psCXT_SWAP->m_tiCXT_EXEC.m_uiI, g_asKN_GPU_CXT_EXEC);

    sDX12_Viewport.Height = (TgFLOAT32)psCXT_SWAP->m_sViewport.m_iHeight;
    sDX12_Viewport.MaxDepth = psCXT_SWAP->m_sViewport.m_fMaxZ;
    sDX12_Viewport.MinDepth = psCXT_SWAP->m_sViewport.m_fMinZ;
    sDX12_Viewport.TopLeftX = (TgFLOAT32)psCXT_SWAP->m_sViewport.m_iPosX;
    sDX12_Viewport.TopLeftY = (TgFLOAT32)psCXT_SWAP->m_sViewport.m_iPosY;
    sDX12_Viewport.Width = (TgFLOAT32)psCXT_SWAP->m_sViewport.m_iWidth;

    ID3D12GraphicsCommandList8_RSSetViewports( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 1, &sDX12_Viewport );

    sDX12_Rect.bottom = psCXT_SWAP->m_sScissor_Rect.m_iBottom;
    sDX12_Rect.left = psCXT_SWAP->m_sScissor_Rect.m_iLeft;
    sDX12_Rect.right = psCXT_SWAP->m_sScissor_Rect.m_iRight;
    sDX12_Rect.top = psCXT_SWAP->m_sScissor_Rect.m_iTop;

    ID3D12GraphicsCommandList8_RSSetScissorRects( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 1, &sDX12_Rect );

    return (KTgS_OK);
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_GPU_EXT_CXT_SWAP_Free_For_Resize ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgKN_GPU_EXT_CXT_SWAP_Free_For_Resize( TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP )
{
    STg2_KN_GPU_EXT_CXT_SWAP_PC         psEXT_CXT_SWAP = g_asKN_GPU_EXT_CXT_SWAP + tiCXT_SWAP.m_uiI;

    TgSINT_E32                          iIndex;

    TgPARAM_CHECK_INDEX(tiCXT_SWAP.m_uiI, g_asKN_GPU_EXT_CXT_SWAP);

    if (nullptr != psEXT_CXT_SWAP->m_psDX12_Depth_Stencil)
    {
        TgVERIFY( 0 == ID3D12Resource_Release( psEXT_CXT_SWAP->m_psDX12_Depth_Stencil ) );
        psEXT_CXT_SWAP->m_psDX12_Depth_Stencil = nullptr;
    };

    for (iIndex = 0; iIndex < (TgSINT_E32)TgARRAY_COUNT( psEXT_CXT_SWAP->m_sCmd ); ++iIndex)
    {
        if (nullptr != psEXT_CXT_SWAP->m_sCmd[iIndex].m_psDX12_Render_Target_View)
        {
            ID3D12Resource_Release( psEXT_CXT_SWAP->m_sCmd[iIndex].m_psDX12_Render_Target_View );
            psEXT_CXT_SWAP->m_sCmd[iIndex].m_psDX12_Render_Target_View = nullptr;
        };
    };
}


/* ---- tgKN_GPU_EXT_CXT_SWAP_Find_Mode ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgBOOL tgKN_GPU_EXT_CXT_SWAP_Find_Mode( STg2_KN_GPU_CXT_SWAP_CPC psCXT_SWAP, DXGI_MODE_DESC1_P psDXGI_Found_Mode )
{
    TgRSIZE_C                           uiAdapter = psCXT_SWAP->m_uiScanout_Adapter_Enumeration_Index;
    TgRSIZE_C                           uiOutput = psCXT_SWAP->m_uiScanout_Output_Enumeration_Index;
    DXGI_FORMAT                         enDXGI_RT_Format;
    TgSINT_E32                          uiMode, uiModeMax;

    /* Search for the exact DXGI mode match. This needs to be done as the generic GPU mode structure lacks elements found in the DXGI structure. */

    enDXGI_RT_Format = (DXGI_FORMAT)psCXT_SWAP->m_enFormat_RT;

    uiModeMax = (TgSINT_E32)g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Adapter[uiAdapter].m_asEXT_Output[uiOutput].m_nuiDXGI_Mode;

    for (uiMode = 0; uiMode < uiModeMax; ++uiMode)
    {
        DXGI_MODE_DESC1_CPC                 psDXGI_Mode = g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Adapter[uiAdapter].m_asEXT_Output[uiOutput].m_psDXGI_Mode + uiMode;

        if (enDXGI_RT_Format != psDXGI_Mode->Format)
            continue;

        if ((psCXT_SWAP->m_sMode.m_sBuffer.m_uiWidth != psDXGI_Mode->Width) || (psCXT_SWAP->m_sMode.m_sBuffer.m_uiHeight != psDXGI_Mode->Height))
            continue;
        if (psCXT_SWAP->m_sMode.m_uiRefresh_Rate__Numerator != psDXGI_Mode->RefreshRate.Numerator)
            continue;
        if (psCXT_SWAP->m_sMode.m_uiRefresh_Rate__Denominator != psDXGI_Mode->RefreshRate.Denominator)
            continue;

        *psDXGI_Found_Mode = *psDXGI_Mode;
        return (true);
    };

    return (false);
}


/* ---- tgKN_GPU_EXT_CXT_SWAP_Set_HDR_Metadata ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/** This function copied from the Microsoft DirectX Graphics Samples (D3D12HDR), under the MIT License. */
static TgRESULT tgKN_GPU_EXT_CXT_SWAP_Set_HDR_Metadata( TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP )
{
    STg2_KN_GPU_EXT_CXT_SWAP_PC         psEXT_CXT_SWAP = g_asKN_GPU_EXT_CXT_SWAP + tiCXT_SWAP.m_uiI;
    STg2_KN_GPU_CXT_SWAP_PC             psCXT_SWAP = g_asKN_GPU_CXT_SWAP + tiCXT_SWAP.m_uiI;
    STg2_KN_GPU_EXT_Adapter_PC          psEXT_Adapter = g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Adapter + psCXT_SWAP->m_uiScanout_Adapter_Enumeration_Index;
    STg2_KN_GPU_EXT_Output_PC           psEXT_Output = psEXT_Adapter->m_asEXT_Output + psCXT_SWAP->m_uiScanout_Output_Enumeration_Index;
    DXGI_HDR_METADATA_HDR10             sDXGI_HDR10_Metadata;
    TgSINT_E32                          iSelected_Chroma = 0;

    static const float DisplayChromaticityList[][8] =
    {
        { 0.64000f, 0.33000f, 0.30000f, 0.60000f, 0.15000f, 0.06000f, 0.31270f, 0.32900f }, // Display Gamut Rec709 
        { 0.70800f, 0.29200f, 0.17000f, 0.79700f, 0.13100f, 0.04600f, 0.31270f, 0.32900f }, // Display Gamut Rec2020
    };

    // Select the chromaticity based on HDR format of the DWM.
    if (DXGI_COLOR_SPACE_RGB_FULL_G10_NONE_P709 == psEXT_CXT_SWAP->m_enDXGI_Colour_Space)
    {
        iSelected_Chroma = 0;
    }
    else if (DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020 == psEXT_CXT_SWAP->m_enDXGI_Colour_Space)
    {
        iSelected_Chroma = 1;
    }
    else
    {
        // Reset the metadata since this is not a supported HDR format.
        return (IDXGISwapChain4_SetHDRMetaData( psEXT_CXT_SWAP->m_psDXGI_Swap_Chain, DXGI_HDR_METADATA_TYPE_NONE, 0, nullptr ));
    }

    // Set HDR meta data
    tgMM_Set_U08_0x00( &sDXGI_HDR10_Metadata, sizeof( sDXGI_HDR10_Metadata ) );

    sDXGI_HDR10_Metadata.RedPrimary[0] = (UINT16)(DisplayChromaticityList[iSelected_Chroma][0] * 50000.0f);
    sDXGI_HDR10_Metadata.RedPrimary[1] = (UINT16)(DisplayChromaticityList[iSelected_Chroma][1] * 50000.0f);
    sDXGI_HDR10_Metadata.GreenPrimary[0] = (UINT16)(DisplayChromaticityList[iSelected_Chroma][2] * 50000.0f);
    sDXGI_HDR10_Metadata.GreenPrimary[1] = (UINT16)(DisplayChromaticityList[iSelected_Chroma][3] * 50000.0f);
    sDXGI_HDR10_Metadata.BluePrimary[0] = (UINT16)(DisplayChromaticityList[iSelected_Chroma][4] * 50000.0f);
    sDXGI_HDR10_Metadata.BluePrimary[1] = (UINT16)(DisplayChromaticityList[iSelected_Chroma][5] * 50000.0f);
    sDXGI_HDR10_Metadata.WhitePoint[0] = (UINT16)(DisplayChromaticityList[iSelected_Chroma][6] * 50000.0f);
    sDXGI_HDR10_Metadata.WhitePoint[1] = (UINT16)(DisplayChromaticityList[iSelected_Chroma][7] * 50000.0f);
    sDXGI_HDR10_Metadata.MaxMasteringLuminance = (UINT)(psCXT_SWAP->m_fMax_Mastering_Nits * 10000.0f);
    sDXGI_HDR10_Metadata.MinMasteringLuminance = (UINT)(psCXT_SWAP->m_fMin_Mastering_Nits * 10000.0f);
    sDXGI_HDR10_Metadata.MaxContentLightLevel = (UINT16)(psCXT_SWAP->m_fMax_Content_Light_Level);
    sDXGI_HDR10_Metadata.MaxFrameAverageLightLevel = (UINT16)(psCXT_SWAP->m_fMax_Frame_Average_Light_Level);

    if (0 != tgMM_Compare( &psEXT_Output->m_sHDR10, sizeof( psEXT_Output->m_sHDR10 ), &sDXGI_HDR10_Metadata, sizeof( sDXGI_HDR10_Metadata ) ))
    {
        tgMM_Copy( &psEXT_Output->m_sHDR10, sizeof( psEXT_Output->m_sHDR10 ), &sDXGI_HDR10_Metadata, sizeof( sDXGI_HDR10_Metadata ) );

        /* This is per output device (not per swap chain). Avoid calling multiple times for the same output device. */
        return (IDXGISwapChain4_SetHDRMetaData( psEXT_CXT_SWAP->m_psDXGI_Swap_Chain, DXGI_HDR_METADATA_TYPE_HDR10, sizeof( DXGI_HDR_METADATA_HDR10 ), &psEXT_Output->m_sHDR10 ));
    }

    return (KTgS_OK);
}
