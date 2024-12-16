/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (DX12) Kernel [GPU] - Resource [Data Buffer].c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.20 | »GUID« DE461472-5528-4A5B-A7F4-09CCAD73387B */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_GPU_EXT__Execute__Init_Data_Buffer_1 -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_EXT__Execute__Init_Data_Buffer_1( TgVOID_PP ppsDX12_Resource, UTg2_KN_GPU_CMD_C uCMD, TgVOID_CP pData, TgRSIZE_C nbyData )
{
    TgRSIZE                             uiEXEC = (uCMD.psEXT->m_tiCXT_WORK.m_uiI >> 16) & 0xFFFF;
    STg2_KN_GPU_EXT_CXT_EXEC_PC         psEXT_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + uiEXEC;
    ID3D12Device10_PC                   psDX12_Device = uCMD.psEXT->m_psDX12_Device;

    D3D12_HEAP_PROPERTIES               sDX12_Default_Heap_Properties;
    D3D12_HEAP_PROPERTIES               sDX12_Upload_Heap_Properties;
    D3D12_RESOURCE_DESC                 sDX12_Resource_Desc;
    D3D12_RESOURCE_BARRIER              sDX12_ResourceBarrier;
    D3D12_SUBRESOURCE_DATA              sDX12_SubResource_Data;
    D3D12_RANGE                         sDX12_Range;

    ID3D12Resource_P                    psDX12_Vertex_Buffer_Upload;

    HRESULT                             iRet;
    TgUINT_E08_P                        puiMapped_Upload;

    TgPARAM_VAR( STg2_KN_GPU_CXT_EXEC_PC psCXT_EXEC = g_asKN_GPU_CXT_EXEC + uiEXEC; )
    TgPARAM_VAR( TgRSIZE uiWORK = (uCMD.psEXT->m_tiCXT_WORK.m_uiI & 0xFFFF) % KTgKN_GPU_MAX_EXEC_CONTEXT_COMMAND;)
    TgPARAM_CHECK_INDEX( uiEXEC, g_asKN_GPU_EXT_CXT_EXEC );
    TgPARAM_CHECK_INDEX( uiWORK, g_asKN_GPU_EXT_CXT_EXEC[uiEXEC].m_sContext_Command );
    TgPARAM_CHECK( tgKN_GPU_CXT_WORK_ID_Is_Equal( &psEXT_CXT_EXEC->m_sContext_Command[uiWORK].m_tiCXT_WORK_S, uCMD.psEXT->m_tiCXT_WORK ) );
    TgPARAM_CHECK( tgKN_GPU_CXT_EXEC_ID_Is_Equal( &psCXT_EXEC->m_tiCXT_EXEC_S, psEXT_CXT_EXEC->m_sContext_Command[uiWORK].m_tiCXT_EXEC ) );

    /* Initialize the data structures */
    tgMM_Set_U08_0x00( &sDX12_Default_Heap_Properties, sizeof( sDX12_Default_Heap_Properties ) );
    sDX12_Default_Heap_Properties.Type = D3D12_HEAP_TYPE_DEFAULT;
    sDX12_Default_Heap_Properties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
    sDX12_Default_Heap_Properties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
    sDX12_Default_Heap_Properties.CreationNodeMask = psEXT_CXT_EXEC->m_uiNodeMask;
    sDX12_Default_Heap_Properties.VisibleNodeMask = psEXT_CXT_EXEC->m_uiNodeMask;

    tgMM_Set_U08_0x00( &sDX12_Upload_Heap_Properties, sizeof( sDX12_Upload_Heap_Properties ) );
    sDX12_Upload_Heap_Properties.Type = D3D12_HEAP_TYPE_UPLOAD;
    sDX12_Upload_Heap_Properties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
    sDX12_Upload_Heap_Properties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
    sDX12_Upload_Heap_Properties.CreationNodeMask = psEXT_CXT_EXEC->m_uiNodeMask;
    sDX12_Upload_Heap_Properties.VisibleNodeMask = psEXT_CXT_EXEC->m_uiNodeMask;

    tgMM_Set_U08_0x00( &sDX12_Resource_Desc, sizeof( sDX12_Resource_Desc ) );
    sDX12_Resource_Desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
    sDX12_Resource_Desc.Alignment = 0;
    sDX12_Resource_Desc.Height = 1;
    sDX12_Resource_Desc.DepthOrArraySize = 1;
    sDX12_Resource_Desc.MipLevels = 1;
    sDX12_Resource_Desc.Format = DXGI_FORMAT_UNKNOWN;
    sDX12_Resource_Desc.SampleDesc.Count = 1;
    sDX12_Resource_Desc.SampleDesc.Quality = 0;
    sDX12_Resource_Desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
    sDX12_Resource_Desc.Flags = D3D12_RESOURCE_FLAG_NONE;

    tgMM_Set_U08_0x00( &sDX12_ResourceBarrier, sizeof( D3D12_RESOURCE_BARRIER ) );
    sDX12_ResourceBarrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    sDX12_ResourceBarrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
    sDX12_ResourceBarrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

    tgMM_Set_U08_0x00( &sDX12_SubResource_Data, sizeof( sDX12_SubResource_Data ) );

    tgMM_Set_U08_0x00( &sDX12_Range, sizeof( sDX12_Range ) );

    sDX12_Resource_Desc.Width = nbyData;
    iRet = ID3D12Device10_CreateCommittedResource1( psDX12_Device, &sDX12_Default_Heap_Properties, D3D12_HEAP_FLAG_NONE, &sDX12_Resource_Desc, D3D12_RESOURCE_STATE_COMMON,
                                                    nullptr, nullptr, MS_REF IID_ID3D12Resource, (TgVOID_PP)ppsDX12_Resource );
    TgVERIFY(SUCCEEDED(iRet));
    sDX12_ResourceBarrier.Transition.StateBefore = D3D12_RESOURCE_STATE_COMMON;
    sDX12_ResourceBarrier.Transition.StateAfter = D3D12_RESOURCE_STATE_COPY_DEST;
    sDX12_ResourceBarrier.Transition.pResource = (ID3D12Resource_P)(*ppsDX12_Resource);
    ID3D12GraphicsCommandList8_ResourceBarrier( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 1, &sDX12_ResourceBarrier );
    sDX12_Resource_Desc.Width = nbyData;
    iRet = ID3D12Device10_CreateCommittedResource1( psDX12_Device, &sDX12_Upload_Heap_Properties, D3D12_HEAP_FLAG_NONE, &sDX12_Resource_Desc, D3D12_RESOURCE_STATE_GENERIC_READ,
                                                    nullptr, nullptr, MS_REF IID_ID3D12Resource, (TgVOID_PP)&psDX12_Vertex_Buffer_Upload );
    TgVERIFY(SUCCEEDED(iRet));
    ID3D12Object_SetName(psDX12_Vertex_Buffer_Upload,L"Unit Test Resource: Vertex Upload");
    TgVERIFY(SUCCEEDED(ID3D12Resource_Map( psDX12_Vertex_Buffer_Upload, 0, &sDX12_Range, (TgVOID_PP)(&puiMapped_Upload) )));
    tgMM_Copy( puiMapped_Upload, nbyData, pData, nbyData );
    ID3D12Resource_Unmap( psDX12_Vertex_Buffer_Upload, 0, &sDX12_Range );
    puiMapped_Upload = nullptr;
    ID3D12GraphicsCommandList8_CopyBufferRegion( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, (ID3D12Resource_P)(*ppsDX12_Resource), 0, psDX12_Vertex_Buffer_Upload, 0, nbyData );
    sDX12_ResourceBarrier.Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST;
    sDX12_ResourceBarrier.Transition.StateAfter = D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER;
    sDX12_ResourceBarrier.Transition.pResource = (ID3D12Resource_P)(*ppsDX12_Resource);
    ID3D12GraphicsCommandList8_ResourceBarrier( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 1, &sDX12_ResourceBarrier );

    tgKN_GPU_EXT__Execute__Register_Resource_For_Release( uCMD, psDX12_Vertex_Buffer_Upload );

    return (KTgS_OK);
}


/* ---- tgKN_GPU_EXT__Execute__Init_Data_Buffer_2 -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_EXT__Execute__Init_Data_Buffer_2( TgVOID_PP ppsDX12_Resource_0, TgVOID_PP ppsDX12_Resource_1, UTg2_KN_GPU_CMD_C uCMD, TgVOID_CP pData_0, TgRSIZE_C nbyData_0,
                                                    TgVOID_CP pData_1, TgRSIZE_C nbyData_1 )
{
    TgRSIZE                             uiEXEC = (uCMD.psEXT->m_tiCXT_WORK.m_uiI >> 16) & 0xFFFF;
    STg2_KN_GPU_EXT_CXT_EXEC_PC         psEXT_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + uiEXEC;
    ID3D12Device10_PC                   psDX12_Device = uCMD.psEXT->m_psDX12_Device;

    D3D12_HEAP_PROPERTIES               sDX12_Default_Heap_Properties;
    D3D12_HEAP_PROPERTIES               sDX12_Upload_Heap_Properties;
    D3D12_RESOURCE_DESC                 sDX12_Resource_Desc;
    D3D12_RESOURCE_BARRIER              sDX12_ResourceBarrier;
    D3D12_SUBRESOURCE_DATA              sDX12_SubResource_Data;
    D3D12_RANGE                         sDX12_Range;

    ID3D12Resource_P                    psDX12_Buffer_Upload_0;
    ID3D12Resource_P                    psDX12_Buffer_Upload_1;

    HRESULT                             iRet;
    TgUINT_E08_P                        puiMapped_Upload;

    TgPARAM_VAR( STg2_KN_GPU_CXT_EXEC_PC psCXT_EXEC = g_asKN_GPU_CXT_EXEC + uiEXEC; )
    TgPARAM_VAR( TgRSIZE uiWORK = (uCMD.psEXT->m_tiCXT_WORK.m_uiI & 0xFFFF) % KTgKN_GPU_MAX_EXEC_CONTEXT_COMMAND;)
    TgPARAM_CHECK_INDEX( uiEXEC, g_asKN_GPU_EXT_CXT_EXEC );
    TgPARAM_CHECK_INDEX( uiWORK, g_asKN_GPU_EXT_CXT_EXEC[uiEXEC].m_sContext_Command );
    TgPARAM_CHECK( tgKN_GPU_CXT_WORK_ID_Is_Equal( &psEXT_CXT_EXEC->m_sContext_Command[uiWORK].m_tiCXT_WORK_S, uCMD.psEXT->m_tiCXT_WORK ) );
    TgPARAM_CHECK( tgKN_GPU_CXT_EXEC_ID_Is_Equal( &psCXT_EXEC->m_tiCXT_EXEC_S, psEXT_CXT_EXEC->m_sContext_Command[uiWORK].m_tiCXT_EXEC ) );
    TgPARAM_CHECK(0 != nbyData_0);
    TgPARAM_CHECK(0 != nbyData_1);

    /* Initialize the data structures */
    tgMM_Set_U08_0x00( &sDX12_Default_Heap_Properties, sizeof( sDX12_Default_Heap_Properties ) );
    sDX12_Default_Heap_Properties.Type = D3D12_HEAP_TYPE_DEFAULT;
    sDX12_Default_Heap_Properties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
    sDX12_Default_Heap_Properties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
    sDX12_Default_Heap_Properties.CreationNodeMask = psEXT_CXT_EXEC->m_uiNodeMask;
    sDX12_Default_Heap_Properties.VisibleNodeMask = psEXT_CXT_EXEC->m_uiNodeMask;

    tgMM_Set_U08_0x00( &sDX12_Upload_Heap_Properties, sizeof( sDX12_Upload_Heap_Properties ) );
    sDX12_Upload_Heap_Properties.Type = D3D12_HEAP_TYPE_UPLOAD;
    sDX12_Upload_Heap_Properties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
    sDX12_Upload_Heap_Properties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
    sDX12_Upload_Heap_Properties.CreationNodeMask = psEXT_CXT_EXEC->m_uiNodeMask;
    sDX12_Upload_Heap_Properties.VisibleNodeMask = psEXT_CXT_EXEC->m_uiNodeMask;

    tgMM_Set_U08_0x00( &sDX12_Resource_Desc, sizeof( sDX12_Resource_Desc ) );
    sDX12_Resource_Desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
    sDX12_Resource_Desc.Alignment = 0;
    sDX12_Resource_Desc.Height = 1;
    sDX12_Resource_Desc.DepthOrArraySize = 1;
    sDX12_Resource_Desc.MipLevels = 1;
    sDX12_Resource_Desc.Format = DXGI_FORMAT_UNKNOWN;
    sDX12_Resource_Desc.SampleDesc.Count = 1;
    sDX12_Resource_Desc.SampleDesc.Quality = 0;
    sDX12_Resource_Desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
    sDX12_Resource_Desc.Flags = D3D12_RESOURCE_FLAG_NONE;

    tgMM_Set_U08_0x00( &sDX12_ResourceBarrier, sizeof( D3D12_RESOURCE_BARRIER ) );
    sDX12_ResourceBarrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    sDX12_ResourceBarrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
    sDX12_ResourceBarrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

    tgMM_Set_U08_0x00( &sDX12_SubResource_Data, sizeof( sDX12_SubResource_Data ) );

    tgMM_Set_U08_0x00( &sDX12_Range, sizeof( sDX12_Range ) );

    sDX12_Resource_Desc.Width = nbyData_0;
    iRet = ID3D12Device10_CreateCommittedResource1( psDX12_Device, &sDX12_Default_Heap_Properties, D3D12_HEAP_FLAG_NONE, &sDX12_Resource_Desc, D3D12_RESOURCE_STATE_COMMON,
                                                    nullptr, nullptr, MS_REF IID_ID3D12Resource, ppsDX12_Resource_0 );
    TgVERIFY(SUCCEEDED(iRet));
    sDX12_ResourceBarrier.Transition.StateBefore = D3D12_RESOURCE_STATE_COMMON;
    sDX12_ResourceBarrier.Transition.StateAfter = D3D12_RESOURCE_STATE_COPY_DEST;
    sDX12_ResourceBarrier.Transition.pResource = (ID3D12Resource_P)(*ppsDX12_Resource_0);
    ID3D12GraphicsCommandList8_ResourceBarrier( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 1, &sDX12_ResourceBarrier );
    sDX12_Resource_Desc.Width = nbyData_0;
    iRet = ID3D12Device10_CreateCommittedResource1( psDX12_Device, &sDX12_Upload_Heap_Properties, D3D12_HEAP_FLAG_NONE, &sDX12_Resource_Desc, D3D12_RESOURCE_STATE_GENERIC_READ,
                                                    nullptr, nullptr, MS_REF IID_ID3D12Resource, (TgVOID_PP)&psDX12_Buffer_Upload_0 );
    TgVERIFY(SUCCEEDED(iRet));
    ID3D12Object_SetName(psDX12_Buffer_Upload_0,L"Unit Test Resource: Upload 0");
    TgVERIFY(SUCCEEDED(ID3D12Resource_Map( psDX12_Buffer_Upload_0, 0, &sDX12_Range, (TgVOID_PP)(&puiMapped_Upload) )));
    tgMM_Copy( puiMapped_Upload, nbyData_0, pData_0, nbyData_0 );
    ID3D12Resource_Unmap( psDX12_Buffer_Upload_0, 0, &sDX12_Range );
    puiMapped_Upload = nullptr;
    ID3D12GraphicsCommandList8_CopyBufferRegion( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, (ID3D12Resource_P)(*ppsDX12_Resource_0), 0, psDX12_Buffer_Upload_0, 0, nbyData_0 );
    sDX12_ResourceBarrier.Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST;
    sDX12_ResourceBarrier.Transition.StateAfter = D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER;
    sDX12_ResourceBarrier.Transition.pResource = (ID3D12Resource_P)(*ppsDX12_Resource_0);
    ID3D12GraphicsCommandList8_ResourceBarrier( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 1, &sDX12_ResourceBarrier );

    tgKN_GPU_EXT__Execute__Register_Resource_For_Release( uCMD, psDX12_Buffer_Upload_0 );

    sDX12_Resource_Desc.Width = nbyData_1;
    iRet = ID3D12Device10_CreateCommittedResource1( psDX12_Device, &sDX12_Default_Heap_Properties, D3D12_HEAP_FLAG_NONE, &sDX12_Resource_Desc, D3D12_RESOURCE_STATE_COMMON,
                                                    nullptr, nullptr, MS_REF IID_ID3D12Resource, ppsDX12_Resource_1 );
    TgVERIFY(SUCCEEDED(iRet));
    sDX12_ResourceBarrier.Transition.StateBefore = D3D12_RESOURCE_STATE_COMMON;
    sDX12_ResourceBarrier.Transition.StateAfter = D3D12_RESOURCE_STATE_COPY_DEST;
    sDX12_ResourceBarrier.Transition.pResource = (ID3D12Resource_P)(*ppsDX12_Resource_1);
    ID3D12GraphicsCommandList8_ResourceBarrier( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 1, &sDX12_ResourceBarrier );
    sDX12_Resource_Desc.Width = nbyData_1;
    iRet = ID3D12Device10_CreateCommittedResource1( psDX12_Device, &sDX12_Upload_Heap_Properties, D3D12_HEAP_FLAG_NONE, &sDX12_Resource_Desc, D3D12_RESOURCE_STATE_GENERIC_READ,
                                                    nullptr, nullptr, MS_REF IID_ID3D12Resource, (TgVOID_PP)&psDX12_Buffer_Upload_1 );
    TgVERIFY(SUCCEEDED(iRet));
    ID3D12Object_SetName(psDX12_Buffer_Upload_1,L"Unit Test Resource: Upload 1");
    TgVERIFY(SUCCEEDED(ID3D12Resource_Map( psDX12_Buffer_Upload_1, 0, &sDX12_Range, (TgVOID_PP)(&puiMapped_Upload) )));
    tgMM_Copy( puiMapped_Upload, nbyData_1, pData_1, nbyData_1 );
    ID3D12Resource_Unmap( psDX12_Buffer_Upload_1, 0, &sDX12_Range );
    puiMapped_Upload = nullptr;
    ID3D12GraphicsCommandList8_CopyBufferRegion( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, (ID3D12Resource_P)(*ppsDX12_Resource_1), 0, psDX12_Buffer_Upload_1, 0, nbyData_1 );
    sDX12_ResourceBarrier.Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST;
    sDX12_ResourceBarrier.Transition.StateAfter = D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER;
    sDX12_ResourceBarrier.Transition.pResource = (ID3D12Resource_P)(*ppsDX12_Resource_1);
    ID3D12GraphicsCommandList8_ResourceBarrier( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 1, &sDX12_ResourceBarrier );

    tgKN_GPU_EXT__Execute__Register_Resource_For_Release( uCMD, psDX12_Buffer_Upload_1 );

    return (KTgS_OK);
}
