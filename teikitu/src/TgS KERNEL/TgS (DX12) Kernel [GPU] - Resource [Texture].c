/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (DX12) Kernel - Resource [GPU] [Texture].c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Kernel ===================================================================================================================================================================== */
#if defined (ENABLE_RELOAD_GUARD)

// -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. //
//  Internal Functions
// -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. //

/* ---- Resource - GPU - Texture - API ------------------------------------------------------------------------------------------------------------------------------------------- */

/* ---- T(tgKN_GPU_EXT_,__Execute_Load) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT T(tgKN_GPU_EXT_,__Execute_Load)(
    TgKN_FILE_ID_C UNUSED_PARAM ARG0, TgRSIZE_C UNUSED_PARAM ARG1, T(STg2_KN_GPU_,_DESC_CPC) UNUSED_PARAM ARG2, ETgKN_GPU_ALLOCATOR_C UNUSED_PARAM ARG3, 
    T(TgKN_GPU_,_ID_C) UNUSED_PARAM ARG4 )
{
    return (KTgS_OK);
}


/* ---- T(tgKN_GPU_EXT_,__Execute_Free) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID T(tgKN_GPU_EXT_,__Execute_Free)( T(TgKN_GPU_,_ID_C) UNUSED_PARAM sID )
{

}


/* ---- T(tgKN_GPU_EXT_,_Inst__Init) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT T(tgKN_GPU_EXT_,_Inst__Init)( UTg2_KN_GPU_CMD_C uCMD, T(TgKN_GPU_,_INST_ID_C) sID_Inst, TgCHAR_U8_CPCU uszName )
{
    TgRSIZE                             uiEXEC = (uCMD.psEXT->m_tiCXT_WORK.m_uiI >> 16) & 0xFFFF;
    STg2_KN_GPU_CXT_EXEC_PC             psCXT_EXEC = g_asKN_GPU_CXT_EXEC + uiEXEC;
    STg2_KN_GPU_EXT_CXT_EXEC_PC         psEXT_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + uiEXEC;
    ID3D12Device10_PC                   psDX12_Device = uCMD.psEXT->m_psDX12_Device;

    T(STg2_KN_GPU_EXT_,_INST_DATA_P)    T(psEXT_,_INST);
    D3D12_HEAP_PROPERTIES               sDX12_Heap_Properties;
    D3D12_RESOURCE_DESC                 sDX12_Resource;
    HRESULT                             iRet;

    TgPARAM_VAR( TgRSIZE uiWORK = (uCMD.psEXT->m_tiCXT_WORK.m_uiI & 0xFFFF) % KTgKN_GPU_MAX_EXEC_CONTEXT_COMMAND;)
    TgPARAM_CHECK_INDEX( uiEXEC, g_asKN_GPU_EXT_CXT_EXEC );
    TgPARAM_CHECK_INDEX( uiWORK, g_asKN_GPU_EXT_CXT_EXEC[uiEXEC].m_sContext_Command );
    TgPARAM_CHECK( tgKN_GPU_CXT_WORK_ID_Is_Equal( &psEXT_CXT_EXEC->m_sContext_Command[uiWORK].m_tiCXT_WORK_S, uCMD.psEXT->m_tiCXT_WORK ) );
    TgPARAM_CHECK( tgKN_GPU_CXT_EXEC_ID_Is_Equal( &psCXT_EXEC->m_tiCXT_EXEC_S, psEXT_CXT_EXEC->m_sContext_Command[uiWORK].m_tiCXT_EXEC ) );
    TgVERIFY( sID_Inst.m_uiCXT == uiEXEC );

    T(psEXT_,_INST) = psEXT_CXT_EXEC->T(m_as,_INST) + sID_Inst.m_uiIndex;

    /* Initialize the DX12 instance data. */
    T(psEXT_,_INST)->m_uiNodeMask = psEXT_CXT_EXEC->m_uiNodeMask;
    T(psEXT_,_INST)->m_sID = psCXT_EXEC->T(m_s,_Inst_LIB_DESC).m_psRS[sID_Inst.m_uiIndex];

    /* Heap Properties */
    tgMM_Set_U08_0x00( &sDX12_Heap_Properties, sizeof(sDX12_Heap_Properties) );
    sDX12_Heap_Properties.Type = D3D12_HEAP_TYPE_DEFAULT;
    sDX12_Heap_Properties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
    sDX12_Heap_Properties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
    sDX12_Heap_Properties.CreationNodeMask = T(psEXT_,_INST)->m_uiNodeMask;
    sDX12_Heap_Properties.VisibleNodeMask = T(psEXT_,_INST)->m_uiNodeMask;

    /* Resource Properties */
    tgMM_Set_U08_0x00( &sDX12_Resource, sizeof(sDX12_Resource) );
    sDX12_Resource.Alignment = 0;
    TgMACRO_ASSIGN_TEXTURE_DIM_WIDTH_HEIGHT_DEPTH(sDX12_Resource, T(g_asKN_Lib_,_Data)[T(psEXT_,_INST)->m_sID.m_uiIndex]);
    sDX12_Resource.MipLevels = (UINT16)T(g_asKN_Lib_,_Data)[T(psEXT_,_INST)->m_sID.m_uiIndex].m_sTX.m_nuiMIP;
    sDX12_Resource.Format = (DXGI_FORMAT)T(g_asKN_Lib_,_Data)[T(psEXT_,_INST)->m_sID.m_uiIndex].m_sTX.m_enFormat;
    sDX12_Resource.SampleDesc.Count = 1;
    sDX12_Resource.SampleDesc.Quality = 0;
    sDX12_Resource.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
    sDX12_Resource.Flags = D3D12_RESOURCE_FLAG_NONE;

    iRet = ID3D12Device10_CreateCommittedResource1( psDX12_Device, &sDX12_Heap_Properties, D3D12_HEAP_FLAG_NONE, &sDX12_Resource, D3D12_RESOURCE_STATE_GENERIC_READ,
                                                    nullptr, nullptr, MS_REF IID_ID3D12Resource, (TgVOID_PP)&T(psEXT_,_INST)->m_psDX12_Resource );
    TgVERIFY(SUCCEEDED(iRet));

#if defined(TgCOMPILE__GPU_OBJECT_NAME) && TgCOMPILE__GPU_OBJECT_NAME
    {
        TgCHAR_U8                           uszDebugName[128];

        tgUSZ_PrintF( uszDebugName, sizeof( uszDebugName ), T_USZ(tgKN_GPU_EXT_,_Inst__Init) );
        if (uszName)
        {
            tgUSZ_AppendF( uszDebugName, sizeof( uszDebugName ), u8" (%s)", uszName );
        };
        TgMACRO_KN_GPU_EXT_SET_NAME_WTH_VAR( T(psEXT_,_INST)->m_psDX12_Resource, uszDebugName );
    }
#else
    (void)uszName;
/*# defined(TgCOMPILE__GPU_OBJECT_NAME) && TgCOMPILE__GPU_OBJECT_NAME */
#endif

    return (KTgS_OK);
}


/* ---- T(tgKN_GPU_EXT_,_Inst__Free) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID T(tgKN_GPU_EXT_,_Inst__Free)( T(TgKN_GPU_,_INST_ID_C) sID_Inst, TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC )
{
    STg2_KN_GPU_EXT_CXT_EXEC_PC         psEXT_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + tiCXT_EXEC.m_uiI;
    T(STg2_KN_GPU_EXT_,_INST_DATA_PC)   T(psEXT_,_INST) = psEXT_CXT_EXEC->T(m_as,_INST) + sID_Inst.m_uiIndex;
    TgVERIFY(0 == ID3D12Resource_Release( T(psEXT_,_INST)->m_psDX12_Resource ));
    T(psEXT_,_INST)->m_psDX12_Resource = nullptr;
    T(psEXT_,_INST)->m_sID = T(KTgKN_GPU_,_ID__INVALID);
}


/* ---- T(tgKN_GPU_EXT_,__Fast_Lock) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID T(tgKN_GPU_EXT_,__Fast_Lock)( STg2_KN_GPU_TX_Surface_PCU psOUT, UTg2_KN_GPU_CMD_C uCMD, T(TgKN_GPU_,_INST_ID_C) sID_Inst )
{
    /* Fast functions not supported on PC: meant only to be used on hardware that supports unified memory. */
    T(tgKN_GPU_EXT_,__Lock)( psOUT, uCMD, sID_Inst );
}


/* ---- T(tgKN_GPU_EXT_,__Lock) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID T(tgKN_GPU_EXT_,__Lock)( STg2_KN_GPU_TX_Surface_PCU psOUT, UTg2_KN_GPU_CMD_C uCMD, T(TgKN_GPU_,_INST_ID_C) sID_Inst )
{
    TgRSIZE                             uiEXEC = (uCMD.psEXT->m_tiCXT_WORK.m_uiI >> 16) & 0xFFFF;
    STg2_KN_GPU_EXT_CXT_EXEC_PC         psEXT_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + uiEXEC;
    ID3D12Device10_P                    psDX12_Device = uCMD.psEXT->m_psDX12_Device;

    T(STg2_KN_GPU_EXT_,_INST_DATA_P)    T(psEXT_,_INST);
    D3D12_RESOURCE_DESC                 sDX12_Dest, sDX12_Upload;
    D3D12_PLACED_SUBRESOURCE_FOOTPRINT  sDX12_Layout;
    D3D12_HEAP_PROPERTIES               sDX12_Upload_Heap_Properties;
    HRESULT                             iRet;
    union
    {
        TgVOID_P                            psVoid;
        ID3D12Resource_P                    psDX12_Resource;
    }                                   uEXT_Resource;

    TgPARAM_VAR( TgRSIZE uiWORK = (uCMD.psEXT->m_tiCXT_WORK.m_uiI & 0xFFFF) % KTgKN_GPU_MAX_EXEC_CONTEXT_COMMAND;)
    TgPARAM_VAR(STg2_KN_GPU_CXT_EXEC_PC psCXT_EXEC = g_asKN_GPU_CXT_EXEC + uiEXEC;)
    TgPARAM_CHECK_INDEX( uiEXEC, g_asKN_GPU_EXT_CXT_EXEC );
    TgPARAM_CHECK_INDEX( uiWORK, g_asKN_GPU_EXT_CXT_EXEC[uiEXEC].m_sContext_Command );
    TgPARAM_CHECK( tgKN_GPU_CXT_WORK_ID_Is_Equal( &psEXT_CXT_EXEC->m_sContext_Command[uiWORK].m_tiCXT_WORK_S, uCMD.psEXT->m_tiCXT_WORK ) );
    TgPARAM_CHECK( tgKN_GPU_CXT_EXEC_ID_Is_Equal( &psCXT_EXEC->m_tiCXT_EXEC_S, psEXT_CXT_EXEC->m_sContext_Command[uiWORK].m_tiCXT_EXEC ) );
    TgVERIFY( sID_Inst.m_uiCXT == uiEXEC );

    T(psEXT_,_INST) = psEXT_CXT_EXEC->T(m_as,_INST) + sID_Inst.m_uiIndex;

    ID3D12Resource_GetDesc( T(psEXT_,_INST)->m_psDX12_Resource, &sDX12_Dest );
    ID3D12Device10_GetCopyableFootprints( psDX12_Device, &sDX12_Dest, psOUT->m_uiMIP, 1, 0, &sDX12_Layout, &psOUT->m_nuiRow, &psOUT->m_uiRowPitch, &psOUT->m_nuiTotal );
    psOUT->m_uiMemPitch = sDX12_Layout.Footprint.RowPitch;

    /* 1.2 Create the texture upload buffer that will be used for uploading/copying the data to the GPU. */
    sDX12_Upload.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
    sDX12_Upload.Alignment = 0;
    sDX12_Upload.Width = psOUT->m_nuiTotal;
    sDX12_Upload.Height = 1;
    sDX12_Upload.DepthOrArraySize = 1;
    sDX12_Upload.MipLevels = 1;
    sDX12_Upload.Format = DXGI_FORMAT_UNKNOWN;
    sDX12_Upload.SampleDesc.Count = 1;
    sDX12_Upload.SampleDesc.Quality = 0;
    sDX12_Upload.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
    sDX12_Upload.Flags = D3D12_RESOURCE_FLAG_NONE;

    sDX12_Upload_Heap_Properties.Type = D3D12_HEAP_TYPE_UPLOAD;
    sDX12_Upload_Heap_Properties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
    sDX12_Upload_Heap_Properties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
    sDX12_Upload_Heap_Properties.CreationNodeMask = T(psEXT_,_INST)->m_uiNodeMask;
    sDX12_Upload_Heap_Properties.VisibleNodeMask = T(psEXT_,_INST)->m_uiNodeMask;

    iRet = ID3D12Device10_CreateCommittedResource1( psDX12_Device, &sDX12_Upload_Heap_Properties, D3D12_HEAP_FLAG_NONE, &sDX12_Upload, D3D12_RESOURCE_STATE_GENERIC_READ,
                                                    nullptr, nullptr, MS_REF IID_ID3D12Resource, (TgVOID_PP)&uEXT_Resource.psVoid );
    TgVERIFY(SUCCEEDED(iRet));
    psOUT->m_psEXT_Object = uEXT_Resource.psVoid;

#if defined(TgCOMPILE__GPU_OBJECT_NAME) && TgCOMPILE__GPU_OBJECT_NAME
    {
        TgCHAR_U8                           uszDebugName[128];
        UINT                                nuiDebugName;

        nuiDebugName = sizeof(uszDebugName);
        ID3D12Object_GetPrivateData( T(psEXT_,_INST)->m_psDX12_Resource, MS_REF WKPDID_D3DDebugObjectName, &nuiDebugName, uszDebugName );
        tgUSZ_Append( uszDebugName, sizeof( uszDebugName ), u8" Locked Surface", KTgMAX_RSIZE );
        TgMACRO_KN_GPU_EXT_SET_NAME_WTH_VAR( uEXT_Resource.psDX12_Resource, uszDebugName );
    }
/*# defined(TgCOMPILE__GPU_OBJECT_NAME) && TgCOMPILE__GPU_OBJECT_NAME */
#endif

    TgVERIFY(SUCCEEDED(ID3D12Resource_Map( uEXT_Resource.psDX12_Resource, 0, nullptr, (TgVOID_PP)(&psOUT->m_puiData) )));
}


/* ---- T(tgKN_GPU_EXT_,__Fast_Unlock) ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID T(tgKN_GPU_EXT_,__Fast_Unlock)( UTg2_KN_GPU_CMD_C uCMD, STg2_KN_GPU_TX_Surface_PCU psSurface, T(TgKN_GPU_,_INST_ID_C) sID_Inst )
{
    /* Fast functions not supported on PC: meant only to be used on hardware that supports unified memory. */
    T(tgKN_GPU_EXT_,__Unlock)( uCMD, psSurface, sID_Inst );
}


/* ---- T(tgKN_GPU_EXT_,__Unlock) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID T(tgKN_GPU_EXT_,__Unlock)( UTg2_KN_GPU_CMD_C uCMD, STg2_KN_GPU_TX_Surface_PCU psSurface, T(TgKN_GPU_,_INST_ID_C) sID_Inst )
{
    union { TgVOID_P psVoid; ID3D12Resource_P psDX12_Resource; } const uEXT_Resource = { .psVoid = psSurface->m_psEXT_Object };

    TgRSIZE                             uiEXEC = (uCMD.psEXT->m_tiCXT_WORK.m_uiI >> 16) & 0xFFFF;
    STg2_KN_GPU_EXT_CXT_EXEC_PC         psEXT_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + uiEXEC;
    ID3D12Device10_P                    psDX12_Device = uCMD.psEXT->m_psDX12_Device;
    D3D12_TEXTURE_COPY_LOCATION         sDX12_Dest_Location = { nullptr, D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX, { { 0 } } };
    D3D12_TEXTURE_COPY_LOCATION         sDX12_Src_Location = { uEXT_Resource.psDX12_Resource, D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT, { { 0 } } };

    T(STg2_KN_GPU_EXT_,_INST_DATA_P)    T(psEXT_,_INST);
    D3D12_RESOURCE_DESC                 sDX12_Dest;
    D3D12_RESOURCE_BARRIER              sDX12_ResourceBarrier;

    TgPARAM_VAR( TgRSIZE uiWORK = (uCMD.psEXT->m_tiCXT_WORK.m_uiI & 0xFFFF) % KTgKN_GPU_MAX_EXEC_CONTEXT_COMMAND;)
    TgPARAM_VAR(STg2_KN_GPU_CXT_EXEC_PC psCXT_EXEC = g_asKN_GPU_CXT_EXEC + uiEXEC;)
    TgPARAM_CHECK_INDEX( uiEXEC, g_asKN_GPU_EXT_CXT_EXEC );
    TgPARAM_CHECK_INDEX( uiWORK, g_asKN_GPU_EXT_CXT_EXEC[uiEXEC].m_sContext_Command );
    TgPARAM_CHECK( tgKN_GPU_CXT_WORK_ID_Is_Equal( &psEXT_CXT_EXEC->m_sContext_Command[uiWORK].m_tiCXT_WORK_S, uCMD.psEXT->m_tiCXT_WORK ) );
    TgPARAM_CHECK( tgKN_GPU_CXT_EXEC_ID_Is_Equal( &psCXT_EXEC->m_tiCXT_EXEC_S, psEXT_CXT_EXEC->m_sContext_Command[uiWORK].m_tiCXT_EXEC ) );
    TgVERIFY( sID_Inst.m_uiCXT == uiEXEC );

    ID3D12Resource_Unmap( uEXT_Resource.psDX12_Resource, 0, nullptr );
    psSurface->m_puiData = nullptr;

    T(psEXT_,_INST) = psEXT_CXT_EXEC->T(m_as,_INST) + sID_Inst.m_uiIndex;
    
    sDX12_Dest_Location.pResource = T(psEXT_,_INST)->m_psDX12_Resource;
    sDX12_Dest_Location.SubresourceIndex = psSurface->m_uiMIP;
    
    ID3D12Resource_GetDesc( T(psEXT_,_INST)->m_psDX12_Resource, &sDX12_Dest );
    ID3D12Device10_GetCopyableFootprints( psDX12_Device, &sDX12_Dest, psSurface->m_uiMIP, 1, 0, &sDX12_Src_Location.PlacedFootprint, nullptr, nullptr, nullptr );

    sDX12_ResourceBarrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    sDX12_ResourceBarrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
    sDX12_ResourceBarrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
    sDX12_ResourceBarrier.Transition.StateBefore = D3D12_RESOURCE_STATE_GENERIC_READ;
    sDX12_ResourceBarrier.Transition.StateAfter = D3D12_RESOURCE_STATE_COPY_DEST;
    sDX12_ResourceBarrier.Transition.pResource = T(psEXT_,_INST)->m_psDX12_Resource;
    ID3D12GraphicsCommandList8_ResourceBarrier( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 1, &sDX12_ResourceBarrier );

    ID3D12GraphicsCommandList8_CopyTextureRegion( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, &sDX12_Dest_Location, 0, 0, 0, &sDX12_Src_Location, nullptr );

    sDX12_ResourceBarrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    sDX12_ResourceBarrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
    sDX12_ResourceBarrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
    sDX12_ResourceBarrier.Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST;
    sDX12_ResourceBarrier.Transition.StateAfter = D3D12_RESOURCE_STATE_GENERIC_READ;
    sDX12_ResourceBarrier.Transition.pResource = T(psEXT_,_INST)->m_psDX12_Resource;
    ID3D12GraphicsCommandList8_ResourceBarrier( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 1, &sDX12_ResourceBarrier );

    tgKN_GPU_EXT__Execute__Register_Resource_For_Release( uCMD, uEXT_Resource.psDX12_Resource );
}

#else


// -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. //
//  Internal Functions
// -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. //

/* ---- Resource - GPU - Texture - API ------------------------------------------------------------------------------------------------------------------------------------------- */

/* ---- tgKN_GPU_EXT_Register_Default_TX_CBE_Inst -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_EXT_Register_Default_TX_CBE_Inst( TgKN_GPU_TX_CBE_INST_ID_C sID_Inst )
{
    STg2_KN_GPU_EXT_CXT_EXEC_PC         psEXT_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + sID_Inst.m_uiCXT;
    STg2_KN_GPU_EXT_TX_CBE_INST_DATA_PC psEXT_TX_CBE_INST = psEXT_CXT_EXEC->m_asTX_CBE_INST + sID_Inst.m_uiIndex;
    ID3D12Device10_PC                   psDX12_Device = g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Adapter[psEXT_CXT_EXEC->m_uiAdapter_Index].m_psDX12_Device;

    D3D12_RESOURCE_DESC                 sDX12_Resource;
    D3D12_SHADER_RESOURCE_VIEW_DESC     sDX12_SRV;

    if (psEXT_CXT_EXEC->m_sSRV.m_asDX12_CPU[KTgKN_GPU_SRV_TX_CBE].ptr + psEXT_CXT_EXEC->m_sSRV.m_uiDescriptor_Size > psEXT_CXT_EXEC->m_sSRV.m_auiMax[KTgKN_GPU_SRV_TX_CBE])
    {
        TgERROR_MSGF( false, STD_MSG_LITERAL_1X, STD_MSG_POST, u8"Insufficient Heap space for default resource." );
        return;
    };

    ID3D12Resource_GetDesc( psEXT_TX_CBE_INST->m_psDX12_Resource, &sDX12_Resource );
    tgMM_Set_U08_0x00( &sDX12_SRV, sizeof( sDX12_SRV ) );
    sDX12_SRV.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
    sDX12_SRV.Format = sDX12_Resource.Format;
    sDX12_SRV.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
    sDX12_SRV.TextureCube.MipLevels = sDX12_Resource.MipLevels;

    ID3D12Device10_CreateShaderResourceView( psDX12_Device, psEXT_TX_CBE_INST->m_psDX12_Resource, &sDX12_SRV, psEXT_CXT_EXEC->m_sSRV.m_asDX12_CPU[KTgKN_GPU_SRV_TX_CBE] );
    psEXT_CXT_EXEC->m_sSRV.m_asDX12_CPU[KTgKN_GPU_SRV_TX_CBE].ptr += psEXT_CXT_EXEC->m_sSRV.m_uiDescriptor_Size;
}


/* ---- tgKN_GPU_EXT_Register_Default_TX_IMG_Inst -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_EXT_Register_Default_TX_IMG_Inst( TgKN_GPU_TX_IMG_INST_ID_C sID_Inst )
{
    STg2_KN_GPU_EXT_CXT_EXEC_PC         psEXT_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + sID_Inst.m_uiCXT;
    STg2_KN_GPU_EXT_TX_IMG_INST_DATA_PC psEXT_TX_IMG_INST = psEXT_CXT_EXEC->m_asTX_IMG_INST + sID_Inst.m_uiIndex;
    ID3D12Device10_PC                   psDX12_Device = g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Adapter[psEXT_CXT_EXEC->m_uiAdapter_Index].m_psDX12_Device;

    D3D12_RESOURCE_DESC                 sDX12_Resource;
    D3D12_SHADER_RESOURCE_VIEW_DESC     sDX12_SRV;

    if (psEXT_CXT_EXEC->m_sSRV.m_asDX12_CPU[KTgKN_GPU_SRV_TX_IMG].ptr + psEXT_CXT_EXEC->m_sSRV.m_uiDescriptor_Size > psEXT_CXT_EXEC->m_sSRV.m_auiMax[KTgKN_GPU_SRV_TX_IMG])
    {
        TgERROR_MSGF( false, STD_MSG_LITERAL_1X, STD_MSG_POST, u8"Insufficient Heap space for default resource." );
        return;
    };

    ID3D12Resource_GetDesc( psEXT_TX_IMG_INST->m_psDX12_Resource, &sDX12_Resource );
    tgMM_Set_U08_0x00( &sDX12_SRV, sizeof( sDX12_SRV ) );
    sDX12_SRV.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
    sDX12_SRV.Format = sDX12_Resource.Format;
    sDX12_SRV.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
    sDX12_SRV.TextureCube.MipLevels = sDX12_Resource.MipLevels;

    ID3D12Device10_CreateShaderResourceView( psDX12_Device, psEXT_TX_IMG_INST->m_psDX12_Resource, &sDX12_SRV, psEXT_CXT_EXEC->m_sSRV.m_asDX12_CPU[KTgKN_GPU_SRV_TX_IMG] );
    psEXT_CXT_EXEC->m_sSRV.m_asDX12_CPU[KTgKN_GPU_SRV_TX_IMG].ptr += psEXT_CXT_EXEC->m_sSRV.m_uiDescriptor_Size;
}


/* ---- tgKN_GPU_EXT_Register_Default_TX_VOL_Inst -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_EXT_Register_Default_TX_VOL_Inst( TgKN_GPU_TX_VOL_INST_ID_C sID_Inst )
{
    STg2_KN_GPU_EXT_CXT_EXEC_PC         psEXT_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + sID_Inst.m_uiCXT;
    STg2_KN_GPU_EXT_TX_VOL_INST_DATA_PC psEXT_TX_VOL_INST = psEXT_CXT_EXEC->m_asTX_VOL_INST + sID_Inst.m_uiIndex;
    ID3D12Device10_PC                   psDX12_Device = g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Adapter[psEXT_CXT_EXEC->m_uiAdapter_Index].m_psDX12_Device;

    D3D12_RESOURCE_DESC                 sDX12_Resource;
    D3D12_SHADER_RESOURCE_VIEW_DESC     sDX12_SRV;

    if (psEXT_CXT_EXEC->m_sSRV.m_asDX12_CPU[KTgKN_GPU_SRV_TX_VOL].ptr + psEXT_CXT_EXEC->m_sSRV.m_uiDescriptor_Size > psEXT_CXT_EXEC->m_sSRV.m_auiMax[KTgKN_GPU_SRV_TX_VOL])
    {
        TgERROR_MSGF( false, STD_MSG_LITERAL_1X, STD_MSG_POST, u8"Insufficient Heap space for default resource." );
        return;
    };

    ID3D12Resource_GetDesc( psEXT_TX_VOL_INST->m_psDX12_Resource, &sDX12_Resource );
    tgMM_Set_U08_0x00( &sDX12_SRV, sizeof( sDX12_SRV ) );
    sDX12_SRV.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
    sDX12_SRV.Format = sDX12_Resource.Format;
    sDX12_SRV.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE3D;
    sDX12_SRV.TextureCube.MipLevels = sDX12_Resource.MipLevels;

    ID3D12Device10_CreateShaderResourceView( psDX12_Device, psEXT_TX_VOL_INST->m_psDX12_Resource, &sDX12_SRV, psEXT_CXT_EXEC->m_sSRV.m_asDX12_CPU[KTgKN_GPU_SRV_TX_VOL] );
    psEXT_CXT_EXEC->m_sSRV.m_asDX12_CPU[KTgKN_GPU_SRV_TX_VOL].ptr += psEXT_CXT_EXEC->m_sSRV.m_uiDescriptor_Size;
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Generic Implementations                                                                                                                                                        */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

    #define ENABLE_RELOAD_GUARD
    #define T(A,...) TgMACRO_CONCAT3V(A,TgMACRO_BUILD_RESOURCE_TYPE,__VA_ARGS__)

#if defined(TgCOMPILE__GPU_OBJECT_NAME) && TgCOMPILE__GPU_OBJECT_NAME
    #define T_USZ(A,...) TgMACRO_CONCAT3V_USZ(A,TgMACRO_BUILD_RESOURCE_TYPE,__VA_ARGS__)
#endif

    #define TgMACRO_ASSIGN_TEXTURE_DIM_WIDTH_HEIGHT_DEPTH(A,B) A.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D; A.Width = B.m_uiEdge; A.Height = B.m_uiEdge; A.DepthOrArraySize = 1
    #define TgMACRO_BUILD_RESOURCE_TYPE TX_CBE
        #include "TgS (DX12) Kernel [GPU] - Resource [Texture].c"
    #undef TgMACRO_BUILD_RESOURCE_TYPE
    #undef TgMACRO_ASSIGN_TEXTURE_DIM_WIDTH_HEIGHT_DEPTH

    #define TgMACRO_ASSIGN_TEXTURE_DIM_WIDTH_HEIGHT_DEPTH(A,B) A.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D; A.Width = B.m_uiWidth; A.Height = B.m_uiHeight; A.DepthOrArraySize = 1
    #define TgMACRO_BUILD_RESOURCE_TYPE TX_IMG
        #include "TgS (DX12) Kernel [GPU] - Resource [Texture].c"
    #undef TgMACRO_BUILD_RESOURCE_TYPE
    #undef TgMACRO_ASSIGN_TEXTURE_DIM_WIDTH_HEIGHT_DEPTH

    #define TgMACRO_ASSIGN_TEXTURE_DIM_WIDTH_HEIGHT_DEPTH(A,B) A.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE3D; A.Width = B.m_uiWidth; A.Height = B.m_uiHeight; A.DepthOrArraySize = (UINT16)B.m_uiDepth
    #define TgMACRO_BUILD_RESOURCE_TYPE TX_VOL
        #include "TgS (DX12) Kernel [GPU] - Resource [Texture].c"
    #undef TgMACRO_BUILD_RESOURCE_TYPE
    #undef TgMACRO_ASSIGN_TEXTURE_DIM_WIDTH_HEIGHT_DEPTH

#if defined(TgCOMPILE__GPU_OBJECT_NAME) && TgCOMPILE__GPU_OBJECT_NAME
    #undef T_USZ
#endif

    #undef T
    #undef ENABLE_RELOAD_GUARD

/*# !defined(ENABLE_RELOAD_GUARD) */
#endif
