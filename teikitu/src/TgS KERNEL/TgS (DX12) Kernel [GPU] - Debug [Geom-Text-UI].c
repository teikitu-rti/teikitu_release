/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (DX12) Kernel [GPU] - Debug [Geom-Text-UI].c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.20 | »GUID« DE461472-5528-4A5B-A7F4-09CCAD73387B */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
#if TgCOMPILE__RENDER_DEBUG_OUTPUT

#include "TgS KERNEL/TgS (DX12) Kernel [GPU] - Debug.inl"


/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_GPU_EXT__CMD__Render_Debug_Text ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_EXT__CMD__Render_Debug_Text( UTg2_KN_GPU_CMD_C uCMD, TgRSIZE nuiGlyph, STg2_KN_GPU_HLSL_CB_Debug_Text_CPC psText_Constant_Buffer )
{
    TgRSIZE                             uiEXEC = (uCMD.psEXT->m_tiCXT_WORK.m_uiI >> 16) & 0xFFFF;
    TgRSIZE                             uiWORK = (uCMD.psEXT->m_tiCXT_WORK.m_uiI & 0xFFFF) % KTgKN_GPU_MAX_EXEC_CONTEXT_COMMAND;
    STg2_KN_GPU_EXT_CXT_EXEC_PC         psEXT_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + uiEXEC;

    STg2_KN_GPU_EXT_CXT_CMD_P           psEXT_CXT_CMD;
    TgRSIZE                             uiDX12_CB_Text;
    D3D12_RANGE                         sDX12_Range;
    TgUINT_E08_P                        puiMappedConstantBuffer;
    D3D12_VERTEX_BUFFER_VIEW            sVertex_Buffer_View;
    D3D12_GPU_DESCRIPTOR_HANDLE         shDX12_GPU;
    D3D12_GPU_VIRTUAL_ADDRESS           uiKB_GPU_Address;

    TgPARAM_VAR(STg2_KN_GPU_CXT_EXEC_PC psCXT_EXEC = g_asKN_GPU_CXT_EXEC + uiEXEC;)
    TgPARAM_CHECK_INDEX( uiEXEC, g_asKN_GPU_EXT_CXT_EXEC );
    TgPARAM_CHECK_INDEX( uiWORK, g_asKN_GPU_EXT_CXT_EXEC[uiEXEC].m_sContext_Command );
    TgPARAM_CHECK( tgKN_GPU_CXT_WORK_ID_Is_Equal( &psEXT_CXT_EXEC->m_sContext_Command[uiWORK].m_tiCXT_WORK_S, uCMD.psEXT->m_tiCXT_WORK ) );
    TgPARAM_CHECK( tgKN_GPU_CXT_EXEC_ID_Is_Equal( &psCXT_EXEC->m_tiCXT_EXEC_S, psEXT_CXT_EXEC->m_sContext_Command[uiWORK].m_tiCXT_EXEC ) );
    TgPARAM_CHECK( uCMD.psEXT->m_enCmd == D3D12_COMMAND_LIST_TYPE_DIRECT );

    psEXT_CXT_CMD = psEXT_CXT_EXEC->m_sContext_Command + uiWORK;
    uiDX12_CB_Text = atomic_fetch_add( &psEXT_CXT_CMD->m_xuiDX12_CB_Text, 1 );
    if (uiDX12_CB_Text >= KTgKN_GPU_MAX_DEBUG_TEXT || nullptr == psEXT_CXT_CMD->m_psDX12_CB_Text[uiDX12_CB_Text])
        return;

    tgMM_Set_U08_0x00( &sDX12_Range, sizeof( sDX12_Range ) );

    TgVERIFY(SUCCEEDED(ID3D12Resource_Map( psEXT_CXT_CMD->m_psDX12_CB_Text[uiDX12_CB_Text], 0, &sDX12_Range, (TgVOID_PP)&puiMappedConstantBuffer )));
    tgMM_Copy( puiMappedConstantBuffer, g_uiAligned_Debug_Text_Constant_Buffer_Size, psText_Constant_Buffer, sizeof( STg2_KN_GPU_HLSL_CB_Debug_Text ) );
    ID3D12Resource_Unmap( psEXT_CXT_CMD->m_psDX12_CB_Text[uiDX12_CB_Text], 0, &sDX12_Range );

    sVertex_Buffer_View.BufferLocation = ID3D12Resource_GetGPUVirtualAddress( psEXT_CXT_EXEC->m_psDX12_Vertex_Buffer__Text );
    sVertex_Buffer_View.StrideInBytes = sizeof( STg2_KN_GPU_Vertex_UI_Text );
    sVertex_Buffer_View.SizeInBytes = sizeof( g_sVertex_Text );

    ID3D12GraphicsCommandList8_IASetVertexBuffers( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 0, 1, &sVertex_Buffer_View );
    ID3D12GraphicsCommandList8_IASetIndexBuffer( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, nullptr );
    ID3D12GraphicsCommandList8_IASetPrimitiveTopology( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );
    ID3D12DescriptorHeap_GetGPUDescriptorHandleForHeapStart( uCMD.psEXT->m_sEXT_Heap_CBV_SRV_UAV.m_psDX12_Heap, &shDX12_GPU );
    ID3D12GraphicsCommandList8_SetGraphicsRootDescriptorTable( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 1, shDX12_GPU );

    uiKB_GPU_Address = ID3D12Resource_GetGPUVirtualAddress( psEXT_CXT_CMD->m_psDX12_CB_Text[uiDX12_CB_Text] );
    ID3D12GraphicsCommandList8_SetGraphicsRootConstantBufferView( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 0, uiKB_GPU_Address );
    ID3D12GraphicsCommandList8_DrawInstanced( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 4, (UINT)nuiGlyph, 0, 0 );
}


/* ---- tgKN_GPU_EXT__CMD__Render_Debug_UI ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_EXT__CMD__Render_Debug_UI( UTg2_KN_GPU_CMD_C uCMD, STg2_KN_GPU_HLSL_CB_Debug_UI_CPC psUI_Constant_Buffer )
{
    TgRSIZE                             uiEXEC = (uCMD.psEXT->m_tiCXT_WORK.m_uiI >> 16) & 0xFFFF;
    TgRSIZE                             uiWORK = (uCMD.psEXT->m_tiCXT_WORK.m_uiI & 0xFFFF) % KTgKN_GPU_MAX_EXEC_CONTEXT_COMMAND;
    STg2_KN_GPU_EXT_CXT_EXEC_PC         psEXT_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + uiEXEC;

    STg2_KN_GPU_EXT_CXT_CMD_P           psEXT_CXT_CMD;
    TgRSIZE                             uiDX12_CB_UI;
    D3D12_RANGE                         sDX12_Range;
    TgUINT_E08_P                        puiMappedConstantBuffer;
    D3D12_VERTEX_BUFFER_VIEW            sVertex_Buffer_View;
    D3D12_GPU_DESCRIPTOR_HANDLE         shDX12_GPU;
    D3D12_GPU_VIRTUAL_ADDRESS           uiKB_GPU_Address;

    TgPARAM_VAR(STg2_KN_GPU_CXT_EXEC_PC psCXT_EXEC = g_asKN_GPU_CXT_EXEC + uiEXEC;)
    TgPARAM_CHECK_INDEX( uiEXEC, g_asKN_GPU_EXT_CXT_EXEC );
    TgPARAM_CHECK_INDEX( uiWORK, g_asKN_GPU_EXT_CXT_EXEC[uiEXEC].m_sContext_Command );
    TgPARAM_CHECK( tgKN_GPU_CXT_WORK_ID_Is_Equal( &psEXT_CXT_EXEC->m_sContext_Command[uiWORK].m_tiCXT_WORK_S, uCMD.psEXT->m_tiCXT_WORK ) );
    TgPARAM_CHECK( tgKN_GPU_CXT_EXEC_ID_Is_Equal( &psCXT_EXEC->m_tiCXT_EXEC_S, psEXT_CXT_EXEC->m_sContext_Command[uiWORK].m_tiCXT_EXEC ) );
    TgPARAM_CHECK( uCMD.psEXT->m_enCmd == D3D12_COMMAND_LIST_TYPE_DIRECT );

    psEXT_CXT_CMD = psEXT_CXT_EXEC->m_sContext_Command + uiWORK;
    uiDX12_CB_UI = atomic_fetch_add( &psEXT_CXT_CMD->m_xuiDX12_CB_UI, 1 );

    if (uiDX12_CB_UI >= KTgKN_GPU_MAX_DEBUG_UI || nullptr == psEXT_CXT_CMD->m_psDX12_CB_UI[uiDX12_CB_UI])
        return;

    tgMM_Set_U08_0x00( &sDX12_Range, sizeof( sDX12_Range ) );

    TgVERIFY(SUCCEEDED(ID3D12Resource_Map( psEXT_CXT_CMD->m_psDX12_CB_UI[uiDX12_CB_UI], 0, &sDX12_Range, (TgVOID_PP)&puiMappedConstantBuffer )));
    tgMM_Copy( puiMappedConstantBuffer, g_uiAligned_Debug_Quad_Constant_Buffer_Size, psUI_Constant_Buffer, sizeof( STg2_KN_GPU_HLSL_CB_Debug_UI ) );
    ID3D12Resource_Unmap( psEXT_CXT_CMD->m_psDX12_CB_UI[uiDX12_CB_UI], 0, &sDX12_Range );

    sVertex_Buffer_View.BufferLocation = ID3D12Resource_GetGPUVirtualAddress( psEXT_CXT_EXEC->m_psDX12_Vertex_Buffer__UI );
    sVertex_Buffer_View.StrideInBytes = sizeof( STg2_KN_GPU_Vertex_UI );
    sVertex_Buffer_View.SizeInBytes = sizeof( g_sVertex_UI );

    ID3D12GraphicsCommandList8_IASetVertexBuffers( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 0, 1, &sVertex_Buffer_View );
    ID3D12GraphicsCommandList8_IASetIndexBuffer( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, nullptr );
    ID3D12GraphicsCommandList8_IASetPrimitiveTopology( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );
    ID3D12DescriptorHeap_GetGPUDescriptorHandleForHeapStart( uCMD.psEXT->m_sEXT_Heap_CBV_SRV_UAV.m_psDX12_Heap, &shDX12_GPU );
    ID3D12GraphicsCommandList8_SetGraphicsRootDescriptorTable( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 1, shDX12_GPU );
    uiKB_GPU_Address = ID3D12Resource_GetGPUVirtualAddress( psEXT_CXT_CMD->m_psDX12_CB_UI[uiDX12_CB_UI] );
    ID3D12GraphicsCommandList8_SetGraphicsRootConstantBufferView( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 0, uiKB_GPU_Address );
    ID3D12GraphicsCommandList8_DrawInstanced( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 4, 1, 0, 0 );
}


/* ---- tgKN_GPU_EXT__CMD__Render_Debug_Geom --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_EXT__CMD__Render_Debug_Geom( UTg2_KN_GPU_CMD_C uCMD, ETgKN_GPU_DEBUG_PM enPM, STg2_KN_GPU_HLSL_CB_Debug_Model_CPC psModel_Constant_Buffer )
{
    TgRSIZE                             uiEXEC = (uCMD.psEXT->m_tiCXT_WORK.m_uiI >> 16) & 0xFFFF;
    TgRSIZE                             uiWORK = (uCMD.psEXT->m_tiCXT_WORK.m_uiI & 0xFFFF) % KTgKN_GPU_MAX_EXEC_CONTEXT_COMMAND;
    STg2_KN_GPU_EXT_CXT_EXEC_PC         psEXT_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + uiEXEC;

    STg2_KN_GPU_EXT_CXT_CMD_P           psEXT_CXT_CMD;
    TgRSIZE                             uiDX12_CB_GEOM, nuiIndex;
    D3D12_RANGE                         sDX12_Range;
    TgUINT_E08_P                        puiMappedConstantBuffer;
    D3D12_VERTEX_BUFFER_VIEW            sVertex_Buffer_View;
    D3D12_INDEX_BUFFER_VIEW             sIndex_Buffer_View;
    D3D12_GPU_DESCRIPTOR_HANDLE         shDX12_GPU;
    D3D12_GPU_VIRTUAL_ADDRESS           uiKB_GPU_Address;

    TgPARAM_VAR(STg2_KN_GPU_CXT_EXEC_PC psCXT_EXEC = g_asKN_GPU_CXT_EXEC + uiEXEC;)
    TgPARAM_CHECK_INDEX( uiEXEC, g_asKN_GPU_EXT_CXT_EXEC );
    TgPARAM_CHECK_INDEX( uiWORK, g_asKN_GPU_EXT_CXT_EXEC[uiEXEC].m_sContext_Command );
    TgPARAM_CHECK( tgKN_GPU_CXT_WORK_ID_Is_Equal( &psEXT_CXT_EXEC->m_sContext_Command[uiWORK].m_tiCXT_WORK_S, uCMD.psEXT->m_tiCXT_WORK ) );
    TgPARAM_CHECK( tgKN_GPU_CXT_EXEC_ID_Is_Equal( &psCXT_EXEC->m_tiCXT_EXEC_S, psEXT_CXT_EXEC->m_sContext_Command[uiWORK].m_tiCXT_EXEC ) );
    TgPARAM_CHECK( uCMD.psEXT->m_enCmd == D3D12_COMMAND_LIST_TYPE_DIRECT );

    if (enPM < ETgKN_GPU_DEBUG_PM_3D_START || enPM >= ETgKN_GPU_DEBUG_PM_3D_END)
    {
        return;
    }
    enPM -= ETgKN_GPU_DEBUG_PM_3D_START;

    if (nullptr == psEXT_CXT_EXEC->m_psDX12_Vertex_Buffer__Geom[enPM])
        return;

    psEXT_CXT_CMD = psEXT_CXT_EXEC->m_sContext_Command + uiWORK;
    uiDX12_CB_GEOM = atomic_fetch_add( &psEXT_CXT_CMD->m_xuiDX12_CB_GEOM, 1 );

    if (uiDX12_CB_GEOM >= KTgKN_GPU_MAX_DEBUG_GEOM || nullptr == psEXT_CXT_CMD->m_psDX12_CB_GEOM[uiDX12_CB_GEOM])
        return;

    tgMM_Set_U08_0x00( &sDX12_Range, sizeof( sDX12_Range ) );

    TgVERIFY(SUCCEEDED(ID3D12Resource_Map( psEXT_CXT_CMD->m_psDX12_CB_GEOM[uiDX12_CB_GEOM], 0, &sDX12_Range, (TgVOID_PP)&puiMappedConstantBuffer )));
    tgMM_Copy( puiMappedConstantBuffer, g_uiAligned_Debug_Model_Constant_Buffer_Size, psModel_Constant_Buffer, sizeof( STg2_KN_GPU_HLSL_CB_Debug_Model ) );
    ID3D12Resource_Unmap( psEXT_CXT_CMD->m_psDX12_CB_GEOM[uiDX12_CB_GEOM], 0, &sDX12_Range );

    sVertex_Buffer_View.BufferLocation = ID3D12Resource_GetGPUVirtualAddress( psEXT_CXT_EXEC->m_psDX12_Vertex_Buffer__Geom[enPM] );
    sVertex_Buffer_View.StrideInBytes = sizeof( STg2_KN_GPU_Vertex_Geom_02 );
    sVertex_Buffer_View.SizeInBytes = (UINT)psEXT_CXT_EXEC->m_nbyDX12_Vertex_Buffer__Geom[enPM];

    sIndex_Buffer_View.BufferLocation = ID3D12Resource_GetGPUVirtualAddress( psEXT_CXT_EXEC->m_psDX12_Index_Buffer__Geom[enPM] );
    sIndex_Buffer_View.SizeInBytes = (UINT)psEXT_CXT_EXEC->m_nbyDX12_Index_Buffer__Geom[enPM];
    sIndex_Buffer_View.Format = DXGI_FORMAT_R16_UINT;

    ID3D12GraphicsCommandList8_IASetVertexBuffers( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 0, 1, &sVertex_Buffer_View );
    ID3D12GraphicsCommandList8_IASetIndexBuffer( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, &sIndex_Buffer_View );
    ID3D12GraphicsCommandList8_IASetPrimitiveTopology( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
    ID3D12DescriptorHeap_GetGPUDescriptorHandleForHeapStart( uCMD.psEXT->m_sEXT_Heap_CBV_SRV_UAV.m_psDX12_Heap, &shDX12_GPU );
    ID3D12GraphicsCommandList8_SetGraphicsRootDescriptorTable( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 1, shDX12_GPU );
    uiKB_GPU_Address = ID3D12Resource_GetGPUVirtualAddress( psEXT_CXT_CMD->m_psDX12_CB_GEOM[uiDX12_CB_GEOM] );
    ID3D12GraphicsCommandList8_SetGraphicsRootConstantBufferView( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 0, uiKB_GPU_Address );
    nuiIndex = psEXT_CXT_EXEC->m_nbyDX12_Index_Buffer__Geom[enPM] / sizeof(TgUINT_E16);
    ID3D12GraphicsCommandList8_DrawIndexedInstanced( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, (UINT)nuiIndex, 1, 0, 0, 0 );
}


/* ---- tgKN_GPU_EXT__CMD__Render_Debug_Geom_Instance ---------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_EXT__CMD__Render_Debug_Geom_Instance( UTg2_KN_GPU_CMD_C uCMD, ETgKN_GPU_DEBUG_PM enPM, TgRSIZE_C nuiInstance,
                                                      STg2_KN_GPU_HLSL_CB_Debug_Model_Instance_CPC psModel_Instance_Constant_Buffer )
{
    TgRSIZE                             uiEXEC = (uCMD.psEXT->m_tiCXT_WORK.m_uiI >> 16) & 0xFFFF;
    TgRSIZE                             uiWORK = (uCMD.psEXT->m_tiCXT_WORK.m_uiI & 0xFFFF) % KTgKN_GPU_MAX_EXEC_CONTEXT_COMMAND;
    STg2_KN_GPU_EXT_CXT_EXEC_PC         psEXT_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + uiEXEC;

    STg2_KN_GPU_EXT_CXT_CMD_P           psEXT_CXT_CMD;
    TgRSIZE                             uiDX12_CB_GEOM;
    TgRSIZE                             nuiIndex;
    D3D12_RANGE                         sDX12_Range;
    TgUINT_E08_P                        puiMappedConstantBuffer;
    D3D12_VERTEX_BUFFER_VIEW            sVertex_Buffer_View;
    D3D12_INDEX_BUFFER_VIEW             sIndex_Buffer_View;
    D3D12_GPU_DESCRIPTOR_HANDLE         shDX12_GPU;
    D3D12_GPU_VIRTUAL_ADDRESS           uiKB_GPU_Address;

    TgPARAM_VAR(STg2_KN_GPU_CXT_EXEC_PC psCXT_EXEC = g_asKN_GPU_CXT_EXEC + uiEXEC;)
    TgPARAM_CHECK_INDEX( uiEXEC, g_asKN_GPU_EXT_CXT_EXEC );
    TgPARAM_CHECK_INDEX( uiWORK, g_asKN_GPU_EXT_CXT_EXEC[uiEXEC].m_sContext_Command );
    TgPARAM_CHECK( tgKN_GPU_CXT_WORK_ID_Is_Equal( &psEXT_CXT_EXEC->m_sContext_Command[uiWORK].m_tiCXT_WORK_S, uCMD.psEXT->m_tiCXT_WORK ) );
    TgPARAM_CHECK( tgKN_GPU_CXT_EXEC_ID_Is_Equal( &psCXT_EXEC->m_tiCXT_EXEC_S, psEXT_CXT_EXEC->m_sContext_Command[uiWORK].m_tiCXT_EXEC ) );
    TgPARAM_CHECK( uCMD.psEXT->m_enCmd == D3D12_COMMAND_LIST_TYPE_DIRECT );

    if (enPM < ETgKN_GPU_DEBUG_PM_3D_START || enPM >= ETgKN_GPU_DEBUG_PM_3D_END)
    {
        return;
    }
    enPM -= ETgKN_GPU_DEBUG_PM_3D_START;

    psEXT_CXT_CMD = psEXT_CXT_EXEC->m_sContext_Command + uiWORK;
    uiDX12_CB_GEOM = atomic_fetch_add( &psEXT_CXT_CMD->m_xuiDX12_CB_GEOM, 1 );

    if (uiDX12_CB_GEOM >= KTgKN_GPU_MAX_DEBUG_GEOM || nullptr == psEXT_CXT_CMD->m_psDX12_CB_GEOM[uiDX12_CB_GEOM])
        return;

    tgMM_Set_U08_0x00( &sDX12_Range, sizeof( sDX12_Range ) );

    TgVERIFY(SUCCEEDED(ID3D12Resource_Map( psEXT_CXT_CMD->m_psDX12_CB_GEOM[uiDX12_CB_GEOM], 0, &sDX12_Range, (TgVOID_PP)&puiMappedConstantBuffer )));
    tgMM_Copy( puiMappedConstantBuffer, g_uiAligned_Debug_Model_Instance_Constant_Buffer_Size, psModel_Instance_Constant_Buffer, sizeof(STg2_KN_GPU_HLSL_CB_Debug_Model_Instance) );
    ID3D12Resource_Unmap( psEXT_CXT_CMD->m_psDX12_CB_GEOM[uiDX12_CB_GEOM], 0, &sDX12_Range );

    sVertex_Buffer_View.BufferLocation = ID3D12Resource_GetGPUVirtualAddress( psEXT_CXT_EXEC->m_psDX12_Vertex_Buffer__Geom[enPM] );
    sVertex_Buffer_View.StrideInBytes = sizeof( STg2_KN_GPU_Vertex_Geom_02 );
    sVertex_Buffer_View.SizeInBytes = (UINT)psEXT_CXT_EXEC->m_nbyDX12_Vertex_Buffer__Geom[enPM];

    sIndex_Buffer_View.BufferLocation = ID3D12Resource_GetGPUVirtualAddress( psEXT_CXT_EXEC->m_psDX12_Index_Buffer__Geom[enPM] );
    sIndex_Buffer_View.SizeInBytes = (UINT)psEXT_CXT_EXEC->m_nbyDX12_Index_Buffer__Geom[enPM];
    sIndex_Buffer_View.Format = DXGI_FORMAT_R16_UINT;

    ID3D12GraphicsCommandList8_IASetVertexBuffers( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 0, 1, &sVertex_Buffer_View );
    ID3D12GraphicsCommandList8_IASetIndexBuffer( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, &sIndex_Buffer_View );
    ID3D12GraphicsCommandList8_IASetPrimitiveTopology( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
    ID3D12DescriptorHeap_GetGPUDescriptorHandleForHeapStart( uCMD.psEXT->m_sEXT_Heap_CBV_SRV_UAV.m_psDX12_Heap, &shDX12_GPU );
    ID3D12GraphicsCommandList8_SetGraphicsRootDescriptorTable( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 1, shDX12_GPU );
    uiKB_GPU_Address = ID3D12Resource_GetGPUVirtualAddress( psEXT_CXT_CMD->m_psDX12_CB_GEOM[uiDX12_CB_GEOM] );
    ID3D12GraphicsCommandList8_SetGraphicsRootConstantBufferView( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 0, uiKB_GPU_Address );
    nuiIndex = psEXT_CXT_EXEC->m_nbyDX12_Index_Buffer__Geom[enPM] / sizeof(TgUINT_E16);
    ID3D12GraphicsCommandList8_DrawIndexedInstanced( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, (UINT)nuiIndex, (UINT)nuiInstance, 0, 0, 0 );
}


/* ---- tgKN_GPU_EXT__CMD__Render_Debug_Line ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_EXT__CMD__Render_Debug_Line( UTg2_KN_GPU_CMD_C uCMD, STg2_KN_GPU_Vertex_Geom_01_CPCU asLine_Vertex, TgRSIZE_C nuiLine_Vertex, 
                                             STg2_KN_GPU_HLSL_CB_Debug_Line_CPC psLine_Constant_Buffer )
{
    TgRSIZE                             uiEXEC = (uCMD.psEXT->m_tiCXT_WORK.m_uiI >> 16) & 0xFFFF;
    TgRSIZE                             uiWORK = (uCMD.psEXT->m_tiCXT_WORK.m_uiI & 0xFFFF) % KTgKN_GPU_MAX_EXEC_CONTEXT_COMMAND;
    STg2_KN_GPU_EXT_CXT_EXEC_PC         psEXT_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + uiEXEC;
    ID3D12Device10_PC                   psDX12_Device = uCMD.psEXT->m_psDX12_Device;
    TgRSIZE_C                           nbyData = nuiLine_Vertex * sizeof(STg2_KN_GPU_Vertex_Geom_01);

    STg2_KN_GPU_EXT_CXT_CMD_P           psEXT_CXT_CMD;
    TgRSIZE                             uiDX12_CB_GEOM;
    TgRSIZE                             uiDX12_VB_LINE;

    D3D12_HEAP_PROPERTIES               sDX12_Upload_Heap_Properties;
    D3D12_RESOURCE_DESC                 sDX12_Resource_Desc;
    D3D12_RESOURCE_BARRIER              sDX12_ResourceBarrier;
    D3D12_RANGE                         sDX12_Range;

    ID3D12Resource_P                    psDX12_VB_Upload;
    D3D12_VERTEX_BUFFER_VIEW            sVertex_Buffer_View;
    D3D12_GPU_DESCRIPTOR_HANDLE         shDX12_GPU;
    D3D12_GPU_VIRTUAL_ADDRESS           uiKB_GPU_Address;

    HRESULT                             iRet;
    TgUINT_E08_P                        puiMapped_Upload;
    TgUINT_E08_P                        puiMappedConstantBuffer;

    TgPARAM_VAR(STg2_KN_GPU_CXT_EXEC_PC psCXT_EXEC = g_asKN_GPU_CXT_EXEC + uiEXEC;)
    TgPARAM_CHECK_INDEX( uiEXEC, g_asKN_GPU_EXT_CXT_EXEC );
    TgPARAM_CHECK_INDEX( uiWORK, g_asKN_GPU_EXT_CXT_EXEC[uiEXEC].m_sContext_Command );
    TgPARAM_CHECK( tgKN_GPU_CXT_WORK_ID_Is_Equal( &psEXT_CXT_EXEC->m_sContext_Command[uiWORK].m_tiCXT_WORK_S, uCMD.psEXT->m_tiCXT_WORK ) );
    TgPARAM_CHECK( tgKN_GPU_CXT_EXEC_ID_Is_Equal( &psCXT_EXEC->m_tiCXT_EXEC_S, psEXT_CXT_EXEC->m_sContext_Command[uiWORK].m_tiCXT_EXEC ) );
    TgPARAM_CHECK( uCMD.psEXT->m_enCmd == D3D12_COMMAND_LIST_TYPE_DIRECT );

    if (0 == nuiLine_Vertex)
        return;

    psEXT_CXT_CMD = psEXT_CXT_EXEC->m_sContext_Command + uiWORK;

    uiDX12_VB_LINE = atomic_fetch_add( &psEXT_CXT_CMD->m_xuiDX12_VB_LINE, 1 );
    if (uiDX12_VB_LINE >= KTgKN_GPU_MAX_DEBUG_LINE || nullptr == psEXT_CXT_CMD->m_psDX12_VB_LINE[uiDX12_VB_LINE])
        return;

    uiDX12_CB_GEOM = atomic_fetch_add( &psEXT_CXT_CMD->m_xuiDX12_CB_GEOM, 1 );
    if (uiDX12_CB_GEOM >= KTgKN_GPU_MAX_DEBUG_GEOM || nullptr == psEXT_CXT_CMD->m_psDX12_CB_GEOM[uiDX12_CB_GEOM])
        return;

    /* Initialize the data structures */
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

    tgMM_Set_U08_0x00( &sDX12_Range, sizeof( sDX12_Range ) );

    sDX12_ResourceBarrier.Transition.StateBefore = D3D12_RESOURCE_STATE_COMMON;
    sDX12_ResourceBarrier.Transition.StateAfter = D3D12_RESOURCE_STATE_COPY_DEST;
    sDX12_ResourceBarrier.Transition.pResource = psEXT_CXT_CMD->m_psDX12_VB_LINE[uiDX12_VB_LINE];
    ID3D12GraphicsCommandList8_ResourceBarrier( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 1, &sDX12_ResourceBarrier );

    sDX12_Resource_Desc.Width = nbyData;
    iRet = ID3D12Device10_CreateCommittedResource1( psDX12_Device, &sDX12_Upload_Heap_Properties, D3D12_HEAP_FLAG_NONE, &sDX12_Resource_Desc, D3D12_RESOURCE_STATE_GENERIC_READ,
                                                    nullptr, nullptr, MS_REF IID_ID3D12Resource, (TgVOID_PP)&psDX12_VB_Upload );
    TgVERIFY(SUCCEEDED(iRet));
    ID3D12Object_SetName(psDX12_VB_Upload,L"Resource: Vertex Upload");
    TgVERIFY(SUCCEEDED(ID3D12Resource_Map( psDX12_VB_Upload, 0, &sDX12_Range, (TgVOID_PP)(&puiMapped_Upload) )));
    tgMM_Copy( puiMapped_Upload, nbyData, asLine_Vertex, nbyData );
    ID3D12Resource_Unmap( psDX12_VB_Upload, 0, &sDX12_Range );
    puiMapped_Upload = nullptr;
    ID3D12GraphicsCommandList8_CopyBufferRegion( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, psEXT_CXT_CMD->m_psDX12_VB_LINE[uiDX12_VB_LINE], 0, psDX12_VB_Upload, 0, nbyData );
    sDX12_ResourceBarrier.Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST;
    sDX12_ResourceBarrier.Transition.StateAfter = D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER;
    sDX12_ResourceBarrier.Transition.pResource = psEXT_CXT_CMD->m_psDX12_VB_LINE[uiDX12_VB_LINE];
    ID3D12GraphicsCommandList8_ResourceBarrier( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 1, &sDX12_ResourceBarrier );

    tgKN_GPU_EXT__Execute__Register_Resource_For_Release( uCMD, psDX12_VB_Upload );

    TgVERIFY(SUCCEEDED(ID3D12Resource_Map( psEXT_CXT_CMD->m_psDX12_CB_GEOM[uiDX12_CB_GEOM], 0, &sDX12_Range, (TgVOID_PP)&puiMappedConstantBuffer )));
    tgMM_Copy( puiMappedConstantBuffer, g_uiAligned_Debug_Line_Constant_Buffer_Size, psLine_Constant_Buffer, sizeof(STg2_KN_GPU_HLSL_CB_Debug_Line) );
    ID3D12Resource_Unmap( psEXT_CXT_CMD->m_psDX12_CB_GEOM[uiDX12_CB_GEOM], 0, &sDX12_Range );

    sVertex_Buffer_View.BufferLocation = ID3D12Resource_GetGPUVirtualAddress( psEXT_CXT_CMD->m_psDX12_VB_LINE[uiDX12_VB_LINE] );
    sVertex_Buffer_View.StrideInBytes = sizeof( STg2_KN_GPU_Vertex_Geom_01 );
    sVertex_Buffer_View.SizeInBytes = (UINT)nbyData;

    ID3D12GraphicsCommandList8_IASetVertexBuffers( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 0, 1, &sVertex_Buffer_View );
    ID3D12GraphicsCommandList8_IASetIndexBuffer( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, nullptr );
    ID3D12GraphicsCommandList8_IASetPrimitiveTopology( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, D3D_PRIMITIVE_TOPOLOGY_LINELIST );
    ID3D12DescriptorHeap_GetGPUDescriptorHandleForHeapStart( uCMD.psEXT->m_sEXT_Heap_CBV_SRV_UAV.m_psDX12_Heap, &shDX12_GPU );
    ID3D12GraphicsCommandList8_SetGraphicsRootDescriptorTable( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 1, shDX12_GPU );
    uiKB_GPU_Address = ID3D12Resource_GetGPUVirtualAddress( psEXT_CXT_CMD->m_psDX12_CB_GEOM[uiDX12_CB_GEOM] );
    ID3D12GraphicsCommandList8_SetGraphicsRootConstantBufferView( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 0, uiKB_GPU_Address );
    ID3D12GraphicsCommandList8_DrawInstanced( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, (UINT)nuiLine_Vertex, 1, 0, 0 );
}


/*# TgCOMPILE__RENDER_DEBUG_OUTPUT */
#endif
