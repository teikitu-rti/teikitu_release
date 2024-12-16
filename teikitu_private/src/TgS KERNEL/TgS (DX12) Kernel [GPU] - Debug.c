/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (DX12) Kernel - Debug [GPU].c
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

/* ---- tgKN_GPU_EXT__Execute__Init_Debug ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_EXT__Execute__Init_Debug( UTg2_KN_GPU_CMD_C uCMD )
{
#if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)
    TgRSIZE                             uiEXEC = (uCMD.psEXT->m_tiCXT_WORK.m_uiI >> 16) & 0xFFFF;
    TgRSIZE                             uiWORK = (uCMD.psEXT->m_tiCXT_WORK.m_uiI & 0xFFFF) % KTgKN_GPU_MAX_EXEC_CONTEXT_COMMAND;
    STg2_KN_GPU_EXT_CXT_EXEC_PC         psEXT_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + uiEXEC;

    ID3D12Device10_P                    psDX12_Device;

    D3D12_HEAP_PROPERTIES               sDX12_Default_Heap_Properties;
    D3D12_HEAP_PROPERTIES               sDX12_Upload_Heap_Properties;
    D3D12_RESOURCE_DESC                 sDX12_Resource_Desc;

    TgRSIZE                             uiCMD, uiResource;

    HRESULT                             iRet;

    TgPARAM_VAR(STg2_KN_GPU_CXT_EXEC_PC psCXT_EXEC = g_asKN_GPU_CXT_EXEC + uiEXEC;)
    TgPARAM_CHECK_INDEX( uiEXEC, g_asKN_GPU_EXT_CXT_EXEC );
    TgPARAM_CHECK_INDEX( uiWORK, g_asKN_GPU_EXT_CXT_EXEC[uiEXEC].m_sContext_Command );
    TgPARAM_CHECK( tgKN_GPU_CXT_WORK_ID_Is_Equal( &psEXT_CXT_EXEC->m_sContext_Command[uiWORK].m_tiCXT_WORK_S, uCMD.psEXT->m_tiCXT_WORK ) );
    TgPARAM_CHECK( tgKN_GPU_CXT_EXEC_ID_Is_Equal( &psCXT_EXEC->m_tiCXT_EXEC_S, psEXT_CXT_EXEC->m_sContext_Command[uiWORK].m_tiCXT_EXEC ) );
    TgPARAM_CHECK( uCMD.psEXT->m_enCmd == ETgKN_GPU_EXT_COMMAND_DIRECT );

    psDX12_Device = g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Adapter[psEXT_CXT_EXEC->m_uiAdapter_Index].m_psDX12_Device;

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

    /// Per Frame Resources created once per Execution Context Command

    for (uiCMD = 0; uiCMD < KTgKN_GPU_MAX_EXEC_CONTEXT_COMMAND; ++uiCMD)
    {
        STg2_KN_GPU_EXT_CXT_CMD_P           psEXT_CXT_EXEC_CMD = psEXT_CXT_EXEC->m_sContext_Command + uiCMD;

        sDX12_Resource_Desc.Width = g_uiAligned_Debug_Text_Constant_Buffer_Size;
        for (uiResource = 0; uiResource < KTgKN_GPU_MAX_DEBUG_TEXT; ++uiResource)
        {
            iRet = ID3D12Device10_CreateCommittedResource1( psDX12_Device, &sDX12_Upload_Heap_Properties, D3D12_HEAP_FLAG_NONE, &sDX12_Resource_Desc,
                                                            D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, nullptr, MS_REF IID_ID3D12Resource,
                                                            (TgVOID_PP)(psEXT_CXT_EXEC_CMD->m_psDX12_CB_Text + uiResource) );
            TgVERIFY(SUCCEEDED(iRet));
            ID3D12Object_SetName(psEXT_CXT_EXEC_CMD->m_psDX12_CB_Text[uiResource],L"Execution Context Command: Debug Text Constant");
        }

        sDX12_Resource_Desc.Width = g_uiAligned_Debug_Quad_Constant_Buffer_Size;
        for (uiResource = 0; uiResource < KTgKN_GPU_MAX_DEBUG_UI; ++uiResource)
        {
            iRet = ID3D12Device10_CreateCommittedResource1( psDX12_Device, &sDX12_Upload_Heap_Properties, D3D12_HEAP_FLAG_NONE, &sDX12_Resource_Desc,
                                                            D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, nullptr, MS_REF IID_ID3D12Resource,
                                                            (TgVOID_PP)(psEXT_CXT_EXEC_CMD->m_psDX12_CB_UI + uiResource) );
            TgVERIFY(SUCCEEDED(iRet));
            ID3D12Object_SetName(psEXT_CXT_EXEC_CMD->m_psDX12_CB_UI[uiResource],L"Execution Context Command: Debug Quad Constant");
        }

        sDX12_Resource_Desc.Width = g_uiAligned_Debug_Model_Instance_Constant_Buffer_Size;
        for (uiResource = 0; uiResource < KTgKN_GPU_MAX_DEBUG_GEOM; ++uiResource)
        {
            iRet = ID3D12Device10_CreateCommittedResource1( psDX12_Device, &sDX12_Upload_Heap_Properties, D3D12_HEAP_FLAG_NONE, &sDX12_Resource_Desc,
                                                            D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, nullptr, MS_REF IID_ID3D12Resource,
                                                            (TgVOID_PP)(psEXT_CXT_EXEC_CMD->m_psDX12_CB_GEOM + uiResource) );
            TgVERIFY(SUCCEEDED(iRet));
            ID3D12Object_SetName(psEXT_CXT_EXEC_CMD->m_psDX12_CB_GEOM[uiResource],L"Execution Context Command: Debug Geometry Constant");
        }

        sDX12_Resource_Desc.Width = KTgKN_GPU_MAX_DEBUG_LINE_VERTEX_COUNT * sizeof(STg2_KN_GPU_Vertex_Geom_01);
        for (uiResource = 0; uiResource < KTgKN_GPU_MAX_DEBUG_LINE; ++uiResource)
        {
            iRet = ID3D12Device10_CreateCommittedResource1( psDX12_Device, &sDX12_Default_Heap_Properties, D3D12_HEAP_FLAG_NONE, &sDX12_Resource_Desc,
                                                            D3D12_RESOURCE_STATE_COMMON, nullptr, nullptr, MS_REF IID_ID3D12Resource,
                                                            (TgVOID_PP)(psEXT_CXT_EXEC_CMD->m_psDX12_VB_LINE + uiResource) );
            TgVERIFY(SUCCEEDED(iRet));
            ID3D12Object_SetName(psEXT_CXT_EXEC_CMD->m_psDX12_VB_LINE[uiResource],L"Execution Context Command: Debug Line VB");
        }
    }

    /// Static Resources created once per Execution Context

    /* Create a Vertex Buffer, and Copy the contents from an Upload Buffer. */

    /* TEXT, UI QUAD */
    tgKN_GPU_EXT__Execute__Init_Data_Buffer_2( (TgVOID_PP)&psEXT_CXT_EXEC->m_psDX12_Vertex_Buffer__Text,
                                               (TgVOID_PP)&psEXT_CXT_EXEC->m_psDX12_Vertex_Buffer__UI, 
                                               uCMD,
                                               (TgVOID_CP)g_sVertex_Text, sizeof( g_sVertex_Text ),
                                               (TgVOID_CP)g_sVertex_UI, sizeof( g_sVertex_UI ) );
    ID3D12Object_SetName(psEXT_CXT_EXEC->m_psDX12_Vertex_Buffer__Text,L"Execution Context Resource: Vertex Buffer Text");
    ID3D12Object_SetName(psEXT_CXT_EXEC->m_psDX12_Vertex_Buffer__UI,L"Execution Context Resource: Vertex Buffer UI");
/*# defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
#else
    (void)uCMD; // -Wunused-parameter
/*# defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
#endif

    return (KTgS_OK);
}


/* ---- tgKN_GPU_EXT__Execute__Free_Debug ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_EXT__Execute__Free_Debug( TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC )
{
#if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)
    STg2_KN_GPU_EXT_CXT_EXEC_PC         psEXT_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + tiCXT_EXEC.m_uiI;

    TgRSIZE                             uiCMD, uiResource;

    for (uiCMD = 0; uiCMD < KTgKN_GPU_MAX_EXEC_CONTEXT_COMMAND; ++uiCMD)
    {
        STg2_KN_GPU_EXT_CXT_CMD_P           psEXT_CXT_EXEC_CMD = psEXT_CXT_EXEC->m_sContext_Command + uiCMD;

        for (uiResource = 0; uiResource < KTgKN_GPU_MAX_DEBUG_TEXT; ++uiResource)
        {
            if (psEXT_CXT_EXEC_CMD->m_psDX12_CB_Text[uiResource])
            {
                TgVERIFY( 0 == ID3D12Resource_Release( psEXT_CXT_EXEC_CMD->m_psDX12_CB_Text[uiResource] ) );
            }
        };

        for (uiResource = 0; uiResource < KTgKN_GPU_MAX_DEBUG_UI; ++uiResource)
        {
            if (psEXT_CXT_EXEC_CMD->m_psDX12_CB_UI[uiResource])
            {
                TgVERIFY( 0 == ID3D12Resource_Release( psEXT_CXT_EXEC_CMD->m_psDX12_CB_UI[uiResource] ) );
            }
        };

        for (uiResource = 0; uiResource < KTgKN_GPU_MAX_DEBUG_GEOM; ++uiResource)
        {
            if (psEXT_CXT_EXEC_CMD->m_psDX12_CB_GEOM[uiResource])
            {
                TgVERIFY( 0 == ID3D12Resource_Release( psEXT_CXT_EXEC_CMD->m_psDX12_CB_GEOM[uiResource] ) );
            }
        };

        for (uiResource = 0; uiResource < KTgKN_GPU_MAX_DEBUG_LINE; ++uiResource)
        {
            if (psEXT_CXT_EXEC_CMD->m_psDX12_VB_LINE[uiResource])
            {
                TgVERIFY( 0 == ID3D12Resource_Release( psEXT_CXT_EXEC_CMD->m_psDX12_VB_LINE[uiResource] ) );
            }
        };
    };


    if (psEXT_CXT_EXEC->m_psDX12_Vertex_Buffer__Text)
    {
        TgVERIFY( 0 == ID3D12Resource_Release( psEXT_CXT_EXEC->m_psDX12_Vertex_Buffer__Text ) );
    };

    if (psEXT_CXT_EXEC->m_psDX12_Vertex_Buffer__UI)
    {
        TgVERIFY( 0 == ID3D12Resource_Release( psEXT_CXT_EXEC->m_psDX12_Vertex_Buffer__UI ) );
    };

    for (uiResource = 0; uiResource < ETgKN_GPU_DEBUG_PM_3D_COUNT; ++uiResource)
    {
        if (psEXT_CXT_EXEC->m_psDX12_Vertex_Buffer__Geom[uiResource])
        {
            TgVERIFY( 0 == ID3D12Resource_Release( psEXT_CXT_EXEC->m_psDX12_Vertex_Buffer__Geom[uiResource] ) );
        }
        if (psEXT_CXT_EXEC->m_psDX12_Index_Buffer__Geom[uiResource])
        {
            TgVERIFY( 0 == ID3D12Resource_Release( psEXT_CXT_EXEC->m_psDX12_Index_Buffer__Geom[uiResource] ) );
        }
    };
/*# defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
#else
    (void)tiCXT_EXEC; // -Wunused-parameter
/*# defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
#endif
}


/* ---- tgKN_GPU_EXT__Execute__Register_Debug_Geometry --------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)
TgVOID tgKN_GPU_EXT__Execute__Register_Debug_Geometry( UTg2_KN_GPU_CMD_C uCMD, ETgKN_GPU_DEBUG_PM enPM, TgKN_GPU_DBG_PM_Generate_CPCU psGenerate )
{
    TgRSIZE                             uiEXEC = (uCMD.psEXT->m_tiCXT_WORK.m_uiI >> 16) & 0xFFFF;
    TgRSIZE                             uiWORK = (uCMD.psEXT->m_tiCXT_WORK.m_uiI & 0xFFFF) % KTgKN_GPU_MAX_EXEC_CONTEXT_COMMAND;
    STg2_KN_GPU_EXT_CXT_EXEC_PC         psEXT_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + uiEXEC;
    TgCHAR_WC                           wszObject_Name[128];

    TgPARAM_VAR(STg2_KN_GPU_CXT_EXEC_PC psCXT_EXEC = g_asKN_GPU_CXT_EXEC + uiEXEC;)
    TgPARAM_CHECK_INDEX( uiEXEC, g_asKN_GPU_EXT_CXT_EXEC );
    TgPARAM_CHECK_INDEX( uiWORK, g_asKN_GPU_EXT_CXT_EXEC[uiEXEC].m_sContext_Command );
    TgPARAM_CHECK( tgKN_GPU_CXT_WORK_ID_Is_Equal( &psEXT_CXT_EXEC->m_sContext_Command[uiWORK].m_tiCXT_WORK_S, uCMD.psEXT->m_tiCXT_WORK ) );
    TgPARAM_CHECK( tgKN_GPU_CXT_EXEC_ID_Is_Equal( &psCXT_EXEC->m_tiCXT_EXEC_S, psEXT_CXT_EXEC->m_sContext_Command[uiWORK].m_tiCXT_EXEC ) );
    TgPARAM_CHECK( uCMD.psEXT->m_enCmd <= ETgKN_GPU_EXT_COMMAND_VIDEO_ENCODE );

    if (enPM < ETgKN_GPU_DEBUG_PM_3D_START || enPM >= ETgKN_GPU_DEBUG_PM_3D_END)
    {
        return;
    }
    enPM = (ETgKN_GPU_DEBUG_PM)((TgSINT_E32)enPM - ETgKN_GPU_DEBUG_PM_3D_START);

    if (psEXT_CXT_EXEC->m_psDX12_Vertex_Buffer__Geom[enPM])
    {
        tgKN_GPU_EXT__Execute__Register_Resource_For_Release( uCMD, psEXT_CXT_EXEC->m_psDX12_Vertex_Buffer__Geom[enPM] );
        psEXT_CXT_EXEC->m_psDX12_Vertex_Buffer__Geom[enPM] = nullptr;
    }

    if (psEXT_CXT_EXEC->m_psDX12_Index_Buffer__Geom[enPM])
    {
        tgKN_GPU_EXT__Execute__Register_Resource_For_Release( uCMD, psEXT_CXT_EXEC->m_psDX12_Index_Buffer__Geom[enPM] );
        psEXT_CXT_EXEC->m_psDX12_Index_Buffer__Geom[enPM] = nullptr;
    }

    psEXT_CXT_EXEC->m_nbyDX12_Vertex_Buffer__Geom[enPM] = psGenerate->m_nuiVertex * sizeof(STg2_KN_GPU_Vertex_Geom_02);
    psEXT_CXT_EXEC->m_nbyDX12_Index_Buffer__Geom[enPM] = psGenerate->m_nuiIndex * sizeof(TgUINT_E16);
    tgKN_GPU_EXT__Execute__Init_Data_Buffer_2( (TgVOID_PP)psEXT_CXT_EXEC->m_psDX12_Vertex_Buffer__Geom + enPM,
                                                (TgVOID_PP)psEXT_CXT_EXEC->m_psDX12_Index_Buffer__Geom + enPM,
                                                uCMD,
                                                (TgVOID_P)psGenerate->m_psVertex, psEXT_CXT_EXEC->m_nbyDX12_Vertex_Buffer__Geom[enPM],
                                                (TgVOID_P)psGenerate->m_puiIndex, psEXT_CXT_EXEC->m_nbyDX12_Index_Buffer__Geom[enPM] );

    tgWSZ_PrintF( wszObject_Name, sizeof( wszObject_Name ), L"EXEC CXT Resource: VB Debug %s", tgGM_Primitive_To_WSZ( (ETgPRIMITIVE)enPM ) );
    ID3D12Object_SetName( psEXT_CXT_EXEC->m_psDX12_Vertex_Buffer__Geom[enPM], wszObject_Name );
    tgWSZ_PrintF( wszObject_Name, sizeof( wszObject_Name ), L"EXEC CXT Resource: IB Debug %s", tgGM_Primitive_To_WSZ( (ETgPRIMITIVE)enPM ) );
    ID3D12Object_SetName( psEXT_CXT_EXEC->m_psDX12_Index_Buffer__Geom[enPM], wszObject_Name );
}
/*# defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
#endif


/* ---- tgKN_GPU_DXGI_Output__Adapter -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if TgS_STAT__KERNEL || TgS_DEBUG__KERNEL
TgVOID tgSTAT_KN_GPU_EXT_Adapter_Output( STg2_KN_GPU_EXT_Adapter_CPCU psAdapter )
{
    TgUINT_E32_C                        uiChannel_Mask = KTgCN_CHANEL_INITIALIZE | KTgCN_SEVERITY_9;

    TgUINT_E32                          uiOutput;
    STg2_KN_GPU_EXT_Output_CP           psOutput;
    TgCHAR_U8                           szData[128];

    tgUSZ_Convert_WSZ( szData, TgARRAY_COUNT( szData ), psAdapter->m_sDXGI_Adapter.Description, TgARRAY_COUNT( psAdapter->m_sDXGI_Adapter.Description ) );
    tgCN_PrintF( uiChannel_Mask, u8"%-16.16s(%-48.48s):     - Adapter[ %s ]\n", u8"Kernel", u8"tgKN_GPU_PM_Output__Adapter", szData );

    for (uiOutput=0; uiOutput < psAdapter->m_nuiEXT_Output; ++uiOutput)
    {
        TgRSIZE                             uiMode;

        psOutput = psAdapter->m_asEXT_Output + uiOutput;

        tgUSZ_Convert_WSZ( szData, TgARRAY_COUNT( szData ), psOutput->m_sDXGI_Output.DeviceName, TgARRAY_COUNT( psOutput->m_sDXGI_Output.DeviceName ) );
        tgCN_PrintF( uiChannel_Mask, u8"%-16.16s(%-48.48s):     - Output[ %s ]\n", u8"Kernel", u8"tgKN_GPU_PM_Output__Adapter", szData );

        for (uiMode = 0; uiMode < psOutput->m_nuiDXGI_Mode; ++uiMode)
        {
            tgCN_PrintF( uiChannel_Mask, u8"%-16.16s(%-48.48s):     - Mode[% 4d]: W[% 5d] H[% 5d] R[% 3d] F[%s]\n", u8"Kernel", u8"tgKN_GPU_PM_Output__Adapter",
                         uiMode, psOutput->m_psDXGI_Mode[uiMode].Width, psOutput->m_psDXGI_Mode[uiMode].Height,
                         psOutput->m_psDXGI_Mode[uiMode].RefreshRate.Numerator / psOutput->m_psDXGI_Mode[uiMode].RefreshRate.Denominator,
                         tgKN_GPU_EXT_FMT_To_USZ( (ETgKN_GPU_EXT_FORMAT)psOutput->m_psDXGI_Mode[uiMode].Format ) );
        };
        tgCN_PrintF( uiChannel_Mask, u8"%-16.16s(%-48.48s):   - Mode Count: %d\n", u8"Kernel", u8"tgKN_GPU_PM_Output__Adapter", psOutput->m_nuiDXGI_Mode );

        tgCN_PrintF( uiChannel_Mask, u8"%-16.16s(%-48.48s):     - Device Scan Outs\n", u8"Kernel", u8"tgKN_GPU_PM_Output__Adapter" );
        for (uiMode = 0; uiMode < KTgKN_GPU_EXT_FORMAT_RT_SCANOUT_MAX; ++uiMode)
        {
            if (0 >= psOutput->m_nuiMode_ScanOut[uiMode])
                continue;

            tgCN_PrintF( uiChannel_Mask, u8"%-16.16s(%-48.48s):     - F[%s]\n", u8"Kernel", u8"tgKN_GPU_PM_Output__Adapter", tgKN_GPU_EXT_FMT_To_USZ( (ETgKN_GPU_EXT_FORMAT)uiMode ) );
        };
        tgCN_PrintF( uiChannel_Mask, u8"%-16.16s(%-48.48s):   - Mode Count: %d\n", u8"Kernel", u8"tgKN_GPU_PM_Output__Adapter", psOutput->m_nuiDXGI_Mode );
    };
}
/*# TgS_STAT__KERNEL || TgS_DEBUG__KERNEL */
#endif
