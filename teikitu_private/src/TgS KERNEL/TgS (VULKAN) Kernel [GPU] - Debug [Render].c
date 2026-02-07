/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (VULKAN) Kernel [GPU] - Debug [Geom-Text-UI].c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.22 | »GUID« 7ECEAB43-40E4-4161-8F94-87AF31F5BA9A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    Models:     Claude 3.7, Claude 4.0
    ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
#if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)

#include "TgS KERNEL/TgS (VULKAN) Kernel [GPU] - Debug.inl"

TgDISABLE_ALL_WARNNGS_PUSH

/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/** @brief Upload (Copy) the data contents into a storage buffer.
   @param INOUT0 [out] Offset into the SBO where the data starts.
   @param INOUT1 [in,out] Number of elements to copy.
   @param INOUT2 [in,out] Pointer to the current atomic offset (in elements) into the storage buffer (updated on return).
   @param ARG3 [in] Pointer to the command context.
   @param ARG4 [in] Pointer to the data to be copied.
   @param ARG5 [in] Size of each element to copy.
   @param ARG6 [in] Maximum number of elements that can be stored in the storage buffer.
   @param ARG7 [in] Pointer to the storage buffer descriptor.
   @return Result Code. */
static TgRESULT
tgKN_GPU_EXT__CMD__Update_SBO(
    TgUINT_E32_P OUT0, TgRSIZE_P INOUT1, TgRSIZE_A *INOUT2, STg2_KN_GPU_CMD_PC ARG3, TgVOID_CPCU ARG4, TgRSIZE ARG5, TgRSIZE_C ARG6, STg2_KN_GPU_SBO_DESC_PC ARG7 );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_GPU_EXT__CMD__Register_Debug_Geometry ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_EXT__CMD__Register_Debug_Geometry( STg2_KN_GPU_CMD_PC psCMD, ETgKN_GPU_DEBUG_PM enPM, TgKN_GPU_DBG_PM_Generate_CPCU psGenerate )
{
    UTg2_KN_GPU_CMD_C                           uCMD = { .ps = psCMD };
    TgRSIZE                             uiEXEC = (uCMD.psVLKN->m_sBase.m_tiCXT_WORK.m_uiI >> 16) & 0xFFFF;
    STg2_KN_GPU_DBG_VLKN_CXT_EXEC_PC    psDBG_VLKN_CXT_EXEC = g_asKN_GPU_DBG_EXT_CXT_EXEC + uiEXEC;
    STg2_KN_GPU_VLKN_CXT_EXEC_PC        psVLKN_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + uiEXEC;

    TgUINT_E64                          uiResource_Descriptor_Local;
    TgCHAR_U8                           szObject_Name[128];

    TgPARAM_CHECK_KN_GPU_CMD( psCMD );

    uiResource_Descriptor_Local  = ETgKN_GPU_RESOURCE_DESCRIPTOR__MEMORY_LOCAL;

    if (enPM < ETgKN_GPU_DEBUG_PM_3D_START || enPM >= ETgKN_GPU_DEBUG_PM_3D_END)
    {
        return;
    }
    enPM = (ETgKN_GPU_DEBUG_PM)((TgSINT_E32)enPM - ETgKN_GPU_DEBUG_PM_3D_START);

    if (psDBG_VLKN_CXT_EXEC->m_ahVLKN_VBO_Buffer__Geom[enPM])
    {
        tgKN_GPU_VLKN__CMD__Register_Resource_For_Release( psCMD, psDBG_VLKN_CXT_EXEC->m_ahVLKN_VBO_Buffer__Geom[enPM],
                                                           psDBG_VLKN_CXT_EXEC->m_ahVLKN_VBO_Memory__Geom[enPM] );
        psDBG_VLKN_CXT_EXEC->m_ahVLKN_VBO_Buffer__Geom[enPM] = nullptr;
    }

    if (psDBG_VLKN_CXT_EXEC->m_ahVLKN_IBO_Buffer__Geom[enPM])
    {
        tgKN_GPU_VLKN__CMD__Register_Resource_For_Release( psCMD, psDBG_VLKN_CXT_EXEC->m_ahVLKN_IBO_Buffer__Geom[enPM],
                                                           psDBG_VLKN_CXT_EXEC->m_ahVLKN_IBO_Memory__Geom[enPM] );
        psDBG_VLKN_CXT_EXEC->m_ahVLKN_IBO_Buffer__Geom[enPM] = nullptr;
    }

    psDBG_VLKN_CXT_EXEC->m_nbyVLKN_IBO__Geom[enPM] = psGenerate->m_nuiIndex * sizeof(TgUINT_E16);
    tgKN_GPU_VLKN__CMD__Create_Buffer_With_Data( psDBG_VLKN_CXT_EXEC->m_ahVLKN_VBO_Buffer__Geom + enPM, psDBG_VLKN_CXT_EXEC->m_ahVLKN_VBO_Memory__Geom + enPM,
                                                 uCMD.psVLKN, ETgKN_GPU_RESOURCE_DESCRIPTOR__VERTEX_BUFFER | uiResource_Descriptor_Local, psGenerate->m_psVertex,
                                                 psGenerate->m_nuiVertex * sizeof(STg2_KN_GPU_Vertex_Geom_02) );

    tgKN_GPU_VLKN__CMD__Create_Buffer_With_Data( psDBG_VLKN_CXT_EXEC->m_ahVLKN_IBO_Buffer__Geom + enPM, psDBG_VLKN_CXT_EXEC->m_ahVLKN_IBO_Memory__Geom + enPM,
                                                 uCMD.psVLKN, ETgKN_GPU_RESOURCE_DESCRIPTOR__INDEX_BUFFER | uiResource_Descriptor_Local, psGenerate->m_puiIndex,
                                                 psDBG_VLKN_CXT_EXEC->m_nbyVLKN_IBO__Geom[enPM] );

    tgUSZ_PrintF( szObject_Name, sizeof( szObject_Name ), u8"EXEC CXT Resource: VB Debug %s", tgGM_Primitive_To_USZ( (ETgPRIMITIVE)enPM ) );
    TgMACRO_KN_GPU_VLKN_SET_NAME(uCMD.psVLKN->m_hVLKN_Device, VK_OBJECT_TYPE_BUFFER, psDBG_VLKN_CXT_EXEC->m_ahVLKN_VBO_Buffer__Geom[enPM], szObject_Name);
    tgUSZ_PrintF( szObject_Name, sizeof( szObject_Name ), u8"EXEC CXT Resource: IB Debug %s", tgGM_Primitive_To_USZ( (ETgPRIMITIVE)enPM ) );
    TgMACRO_KN_GPU_VLKN_SET_NAME(uCMD.psVLKN->m_hVLKN_Device, VK_OBJECT_TYPE_BUFFER, psDBG_VLKN_CXT_EXEC->m_ahVLKN_IBO_Buffer__Geom[enPM], szObject_Name);
}


/* ---- tgKN_GPU_EXT__CMD__Render_Debug_Text ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_EXT__CMD__Render_Debug_Text( STg2_KN_GPU_CMD_PC psCMD, STg2_KN_GPU_DBG_Text_CPC psText, TgVEC_S_F32_04_1_CPC asText_Offsets, TgRSIZE nuiOffsets )
{
    UTg2_KN_GPU_CMD_C                           uCMD = { .ps = psCMD };
    TgRSIZE                             uiEXEC = (uCMD.psVLKN->m_sBase.m_tiCXT_WORK.m_uiI >> 16) & 0xFFFF;
    TgRSIZE                             uiWORK = (uCMD.psVLKN->m_sBase.m_tiCXT_WORK.m_uiI & 0xFFFF) % KTgKN_GPU_MAX_EXEC_CONTEXT_COMMAND;
    STg2_KN_GPU_VLKN_CXT_EXEC_PC        psVLKN_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + uiEXEC;
    STg2_KN_GPU_DBG_VLKN_CXT_EXEC_PC    psDBG_VLKN_CXT_EXEC = g_asKN_GPU_DBG_EXT_CXT_EXEC + uiEXEC;

    STg2_KN_GPU_DBG_VLKN_CMD_P          psCMD_DBG_VLKN;
    TgSINT_PTR                          iCmd_Index;
    STg2_KN_GPU_DBG_VLKN_CXT_CMD_P      psVLKN_DBG_CXT_CMD;
    VkPipeline                          hVLKN_Pipeline;
    VkDescriptorSet                     ahVLKN_Descriptor_Sets[2];
    VkDeviceSize                        uiBuffer_Offset;
    TgRESULT                            iRet;
    STg2_KN_GPU_DBG_Text_Push           sDBG_Text_Push;

    TgPARAM_CHECK_KN_GPU_CMD( psCMD );

    if (0 == nuiOffsets || nullptr == asText_Offsets || nullptr == psText)
    {
        TgERROR_MSGF(false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Invalid parameters to tgKN_GPU_EXT__CMD__Render_Debug_Text.");
        return;
    }

    TgPARAM_CHECK(VK_NULL_HANDLE != psDBG_VLKN_CXT_EXEC->m_hVLKN_VBO_Buffer__Text);
    TgPARAM_CHECK(nullptr != psDBG_VLKN_CXT_EXEC->m_sSBO__Text.m_uSBO_Mapped.m_pVoid);

    psVLKN_DBG_CXT_CMD = psDBG_VLKN_CXT_EXEC->m_asContext_Command_DBG + uiWORK;
    ahVLKN_Descriptor_Sets[0] = psDBG_VLKN_CXT_EXEC->m_hVLKN_Descriptor_Set_Render_DESC;
    ahVLKN_Descriptor_Sets[1] = psDBG_VLKN_CXT_EXEC->m_hVLKN_DBG_Descriptor_Set__Text;

    iCmd_Index = uCMD.psVLKN - psVLKN_CXT_EXEC->m_asCommand;
    psCMD_DBG_VLKN = psDBG_VLKN_CXT_EXEC->m_asComand_DBG + iCmd_Index;
    hVLKN_Pipeline = psCMD_DBG_VLKN->m_ahVLKN_Pipeline_Graphics[ETgKN_GPU_DBG_GRAPHICS_PIPELINE_TEXT];
    TgPARAM_CHECK(VK_NULL_HANDLE != hVLKN_Pipeline);
    vkCmdBindPipeline( uCMD.psVLKN->m_hVLKN_Command_Buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, hVLKN_Pipeline );

    tgMM_Copy( &sDBG_Text_Push, sizeof(sDBG_Text_Push), psText, sizeof(STg2_KN_GPU_DBG_Text) );
    iRet = tgKN_GPU_EXT__CMD__Update_SBO( &sDBG_Text_Push.m_uiText_SBO_Offset, &nuiOffsets, &psVLKN_DBG_CXT_CMD->m_xuiSBO__Text_Offset, psCMD, asText_Offsets,
                                          sizeof(TgVEC_F32_04_1), psVLKN_DBG_CXT_CMD->m_uiSBO__Text_End, &psDBG_VLKN_CXT_EXEC->m_sSBO__Text );
    if (TgFAILED(iRet))
    {
        TgERROR_MSGF(false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to copy text instance data.");
        return;
    }

    vkCmdSetPrimitiveTopology( uCMD.psVLKN->m_hVLKN_Command_Buffer, VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP );
    uiBuffer_Offset = 0;
    vkCmdBindVertexBuffers( uCMD.psVLKN->m_hVLKN_Command_Buffer, 0, 1, &psDBG_VLKN_CXT_EXEC->m_hVLKN_VBO_Buffer__Text, &uiBuffer_Offset );

    vkCmdBindDescriptorSets( uCMD.psVLKN->m_hVLKN_Command_Buffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
                             psDBG_VLKN_CXT_EXEC->m_ahVLKN_Pipeline_Layout[ETgKN_GPU_DBG_PIPELINE_LAYOUT__SBO], 0,
                             2u, ahVLKN_Descriptor_Sets, 1u, &uCMD.psVLKN->m_uiUBO_Render_DESC_Offset );

    vkCmdPushConstants( uCMD.psVLKN->m_hVLKN_Command_Buffer, psDBG_VLKN_CXT_EXEC->m_ahVLKN_Pipeline_Layout[ETgKN_GPU_DBG_PIPELINE_LAYOUT__SBO],
                        VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 0, sizeof(STg2_KN_GPU_DBG_Text_Push), &sDBG_Text_Push );

    vkCmdDraw( uCMD.psVLKN->m_hVLKN_Command_Buffer, 4u, (TgUINT_E32)nuiOffsets, 0, 0 );
}


/* ---- tgKN_GPU_EXT__CMD__Render_Debug_Quad ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_EXT__CMD__Render_Debug_Quad( STg2_KN_GPU_CMD_PC psCMD, STg2_KN_GPU_DBG_Quad_CPC psQuad_UBO )
{
    UTg2_KN_GPU_CMD_C                           uCMD = { .ps = psCMD };
    TgRSIZE                             uiEXEC = (uCMD.psVLKN->m_sBase.m_tiCXT_WORK.m_uiI >> 16) & 0xFFFF;
    TgRSIZE                             uiWORK = (uCMD.psVLKN->m_sBase.m_tiCXT_WORK.m_uiI & 0xFFFF) % KTgKN_GPU_MAX_EXEC_CONTEXT_COMMAND;
    STg2_KN_GPU_VLKN_CXT_EXEC_PC        psVLKN_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + uiEXEC;
    STg2_KN_GPU_DBG_VLKN_CXT_EXEC_PC    psDBG_VLKN_CXT_EXEC = g_asKN_GPU_DBG_EXT_CXT_EXEC + uiEXEC;

    STg2_KN_GPU_DBG_VLKN_CMD_P          psCMD_DBG_VLKN;
    TgSINT_PTR                          iCmd_Index;
    VkPipeline                          hVLKN_Pipeline;
    VkDeviceSize                        uiVertex_Offset;

    TgPARAM_CHECK_KN_GPU_CMD( psCMD );

    iCmd_Index = uCMD.psVLKN - psVLKN_CXT_EXEC->m_asCommand;
    psCMD_DBG_VLKN = psDBG_VLKN_CXT_EXEC->m_asComand_DBG + iCmd_Index;

    hVLKN_Pipeline = psCMD_DBG_VLKN->m_ahVLKN_Pipeline_Graphics[ETgKN_GPU_DBG_GRAPHICS_PIPELINE_UI];
    TgPARAM_CHECK(VK_NULL_HANDLE != hVLKN_Pipeline);

    vkCmdBindPipeline(uCMD.psVLKN->m_hVLKN_Command_Buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, hVLKN_Pipeline);

    vkCmdBindDescriptorSets( uCMD.psVLKN->m_hVLKN_Command_Buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, 
                             psDBG_VLKN_CXT_EXEC->m_ahVLKN_Pipeline_Layout[ETgKN_GPU_DBG_PIPELINE_LAYOUT__NONE], 0, 1u, &psDBG_VLKN_CXT_EXEC->m_hVLKN_Descriptor_Set_Render_DESC,
                             1u, &uCMD.psVLKN->m_uiUBO_Render_DESC_Offset);

    vkCmdPushConstants( uCMD.psVLKN->m_hVLKN_Command_Buffer, psDBG_VLKN_CXT_EXEC->m_ahVLKN_Pipeline_Layout[ETgKN_GPU_DBG_PIPELINE_LAYOUT__NONE],
                        VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 0, sizeof(STg2_KN_GPU_DBG_Quad), psQuad_UBO );

    /* Draw the UI quad as triangle strip (4 vertices) */
    vkCmdSetPrimitiveTopology( uCMD.psVLKN->m_hVLKN_Command_Buffer, VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP );
    uiVertex_Offset = 0;
    vkCmdBindVertexBuffers(uCMD.psVLKN->m_hVLKN_Command_Buffer, 0, 1, &psDBG_VLKN_CXT_EXEC->m_hVLKN_VBO_Buffer__Quad, &uiVertex_Offset);
    vkCmdDraw(uCMD.psVLKN->m_hVLKN_Command_Buffer, 4, 1, 0, 0);
}


/* ---- tgKN_GPU_EXT__CMD__Render_Debug_Gradient --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_EXT__CMD__Render_Debug_Gradient( STg2_KN_GPU_CMD_PC psCMD )
{
    UTg2_KN_GPU_CMD_C                           uCMD = { .ps = psCMD };
    TgRSIZE                             uiEXEC = (uCMD.psVLKN->m_sBase.m_tiCXT_WORK.m_uiI >> 16) & 0xFFFF;
    TgRSIZE                             uiWORK = (uCMD.psVLKN->m_sBase.m_tiCXT_WORK.m_uiI & 0xFFFF) % KTgKN_GPU_MAX_EXEC_CONTEXT_COMMAND;
    STg2_KN_GPU_VLKN_CXT_EXEC_PC        psVLKN_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + uiEXEC;
    STg2_KN_GPU_DBG_VLKN_CXT_EXEC_PC    psDBG_VLKN_CXT_EXEC = g_asKN_GPU_DBG_EXT_CXT_EXEC + uiEXEC;
    TgRSIZE_C                           uiWidth = psCMD->m_uiRender_Target_Width;
    TgRSIZE_C                           uiHeight = psCMD->m_uiRender_Target_Height;

    STg2_KN_GPU_DBG_VLKN_CMD_P          psCMD_DBG_VLKN;
    TgSINT_PTR                          iCmd_Index;
    STg2_KN_GPU_DBG_Quad                sUI_DBG_Quad;
    VkDeviceSize                        uiVertex_Offset;
    VkPipeline                          hVLKN_Pipeline;

    TgPARAM_CHECK_KN_GPU_CMD( psCMD );

    /* Black background to back drop the gamma bars */
    tgMM_Set_U08( &sUI_DBG_Quad, 0, sizeof(STg2_KN_GPU_DBG_Quad) );
    sUI_DBG_Quad.m_vRect_UI.x = -1.0F + 10.0F / (float)uiWidth;
    sUI_DBG_Quad.m_vRect_UI.y = -1.0F + 50.0F / (float)uiHeight;
    sUI_DBG_Quad.m_vRect_UI.z =  1.0F - 10.0F / (float)uiWidth;
    sUI_DBG_Quad.m_vRect_UI.w = -1.0F +  130.0F / (float)uiHeight;
    sUI_DBG_Quad.m_vUI_Colour.r = 0.0F;
    sUI_DBG_Quad.m_vUI_Colour.g = 0.0F;
    sUI_DBG_Quad.m_vUI_Colour.b = 0.0F;
    sUI_DBG_Quad.m_vUI_Colour.a = 1.0F;
    sUI_DBG_Quad.m_uiSelect_Default_Texture_Index = 1;

    tgKN_GPU_EXT__CMD__Render_Debug_Quad( psCMD, &sUI_DBG_Quad );

    tgMM_Set_U08( &sUI_DBG_Quad, 0, sizeof(STg2_KN_GPU_DBG_Quad) );
    sUI_DBG_Quad.m_vRect_UI.x = -1.0F + 20.0F / (float)uiWidth;
    sUI_DBG_Quad.m_vRect_UI.y = -1.0F + 55.0F / (float)uiHeight;
    sUI_DBG_Quad.m_vRect_UI.z =  1.0F - 20.0F / (float)uiWidth;
    sUI_DBG_Quad.m_vRect_UI.w = -1.0F + 85.0F / (float)uiHeight;
    sUI_DBG_Quad.m_vUI_Colour.r = 1.0F;
    sUI_DBG_Quad.m_vUI_Colour.g = 1.0F;
    sUI_DBG_Quad.m_vUI_Colour.b = 1.0F;
    sUI_DBG_Quad.m_vUI_Colour.a = 1.0F;
    sUI_DBG_Quad.m_uiSelect_Default_Texture_Index = 1;

    /* Bind vertex buffer for UI rendering */
    uiVertex_Offset = 0;
    vkCmdBindVertexBuffers(uCMD.psVLKN->m_hVLKN_Command_Buffer, 0, 1, &psDBG_VLKN_CXT_EXEC->m_hVLKN_VBO_Buffer__Gradient, &uiVertex_Offset);

    vkCmdBindDescriptorSets( uCMD.psVLKN->m_hVLKN_Command_Buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, 
                             psDBG_VLKN_CXT_EXEC->m_ahVLKN_Pipeline_Layout[ETgKN_GPU_DBG_PIPELINE_LAYOUT__NONE], 0, 1u, &psDBG_VLKN_CXT_EXEC->m_hVLKN_Descriptor_Set_Render_DESC,
                             1u, &uCMD.psVLKN->m_uiUBO_Render_DESC_Offset);

    iCmd_Index = uCMD.psVLKN - psVLKN_CXT_EXEC->m_asCommand;
    psCMD_DBG_VLKN = psDBG_VLKN_CXT_EXEC->m_asComand_DBG + iCmd_Index;
    hVLKN_Pipeline = psCMD_DBG_VLKN->m_ahVLKN_Pipeline_Graphics[ETgKN_GPU_DBG_GRAPHICS_PIPELINE_UI];
    TgPARAM_CHECK(VK_NULL_HANDLE != hVLKN_Pipeline);
    vkCmdBindPipeline(uCMD.psVLKN->m_hVLKN_Command_Buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, hVLKN_Pipeline);

    vkCmdSetPrimitiveTopology( uCMD.psVLKN->m_hVLKN_Command_Buffer, VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP );

    vkCmdPushConstants( uCMD.psVLKN->m_hVLKN_Command_Buffer, psDBG_VLKN_CXT_EXEC->m_ahVLKN_Pipeline_Layout[ETgKN_GPU_DBG_PIPELINE_LAYOUT__NONE],
                        VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 0, sizeof(STg2_KN_GPU_DBG_Quad), &sUI_DBG_Quad );

    /* Draw the UI quad as triangle strip (4 vertices) */
    vkCmdDraw(uCMD.psVLKN->m_hVLKN_Command_Buffer, 4, 1, 0, 0);

    sUI_DBG_Quad.m_vRect_UI.x = -1.0F + 20.0F / (float)uiWidth;
    sUI_DBG_Quad.m_vRect_UI.y = -1.0F + 95.0F / (float)uiHeight;
    sUI_DBG_Quad.m_vRect_UI.z =  1.0F - 20.0F / (float)uiWidth;
    sUI_DBG_Quad.m_vRect_UI.w = -1.0F + 125.0F / (float)uiHeight;
    sUI_DBG_Quad.m_vUI_Colour.r = 3.0F;
    sUI_DBG_Quad.m_vUI_Colour.g = 3.0F;
    sUI_DBG_Quad.m_vUI_Colour.b = 3.0F;
    sUI_DBG_Quad.m_vUI_Colour.a = 1.0F;

    vkCmdPushConstants( uCMD.psVLKN->m_hVLKN_Command_Buffer, psDBG_VLKN_CXT_EXEC->m_ahVLKN_Pipeline_Layout[ETgKN_GPU_DBG_PIPELINE_LAYOUT__NONE],
                        VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 0, sizeof(STg2_KN_GPU_DBG_Quad), &sUI_DBG_Quad );

    /* Draw the UI quad as triangle strip (4 vertices) */
    vkCmdDraw(uCMD.psVLKN->m_hVLKN_Command_Buffer, 4, 1, 0, 0);
}


/* ---- tgKN_GPU_EXT__CMD__Render_Debug_Line ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_EXT__CMD__Render_Debug_Line( STg2_KN_GPU_CMD_PC psCMD )
{
    UTg2_KN_GPU_CMD_C                           uCMD = { .ps = psCMD };
    TgRSIZE                             uiEXEC = (uCMD.psVLKN->m_sBase.m_tiCXT_WORK.m_uiI >> 16) & 0xFFFF;
    TgRSIZE                             uiWORK = (uCMD.psVLKN->m_sBase.m_tiCXT_WORK.m_uiI & 0xFFFF) % KTgKN_GPU_MAX_EXEC_CONTEXT_COMMAND;
    STg2_KN_GPU_VLKN_CXT_EXEC_PC        psVLKN_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + uiEXEC;
    STg2_KN_GPU_DBG_VLKN_CXT_EXEC_PC    psDBG_VLKN_CXT_EXEC = g_asKN_GPU_DBG_EXT_CXT_EXEC + uiEXEC;

    STg2_KN_GPU_CMD_DBG_P               psCMD_DBG;
    STg2_KN_GPU_DBG_VLKN_CXT_CMD_P      psVLKN_DBG_CXT_CMD;
    TgRESULT                            iRet;
    TgUINT_E32                          uiTask_Workgroups;
    VkDescriptorSet                     ahVLKN_Descriptor_Sets[2];
    TgSINT_PTR                          iCmd_Index;
    STg2_KN_GPU_DBG_VLKN_CMD_P          psCMD_DBG_VLKN;
    VkPipeline                          hVLKN_Pipeline;
    VkPipelineLayout                    hVLKN_Pipeline_Layout;
    TgRSIZE                             nuiLine;
    STg2_KN_GPU_DBG_Line_Push           sDBG_Line_Push;

    TgPARAM_CHECK_KN_GPU_CMD( psCMD );

    /* Acquire the Debug: Command struct associated with this command. */
    if (TgFAILED(tgKN_GPU_EXT__CMD__Command_Debug(&psCMD_DBG,psCMD)))
    {
        return;
    }

    /* Pointer to the Debug: Context Command */
    psVLKN_DBG_CXT_CMD = psDBG_VLKN_CXT_EXEC->m_asContext_Command_DBG + uiWORK;

    /* Lock the debug line data to prevent new lines from being added until we have completed our copy of the data and reset the line count. */
    tgCM_UT_LF__SN__Lock_Spin(&psCMD_DBG->m_sLine_Lock);

    /* Get the current line count, and exit if their are no lines for us to render. */
    nuiLine = TgSTD_ATOMIC(load)( &psCMD_DBG->m_xnuiLine );
    if (0 == nuiLine)
    {
        tgCM_UT_LF__SN__Signal(&psCMD_DBG->m_sLine_Lock);
        return;
    }

    /* Reserve space for the line data in both the input line and visible line storage buffers. */
    iRet = tgKN_GPU_EXT__CMD__Update_SBO( &sDBG_Line_Push.m_uiInput_Line_SBO_Offset, &nuiLine, &psVLKN_DBG_CXT_CMD->m_xuiSBO__Line__Input_Lines_Offset,
                                          psCMD, psCMD_DBG->m_psLine, sizeof(STg2_KN_GPU_DBG_Line), psVLKN_DBG_CXT_CMD->m_uiSBO__Line__Input_Lines_End,
                                          &psDBG_VLKN_CXT_EXEC->m_sSBO__Line__Input_Lines );
    if (TgFAILED(iRet))
    {
        TgERROR_MSGF(false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to reserve memory in the storage buffer for the debug line data.");
        tgCM_UT_LF__SN__Signal(&psCMD_DBG->m_sLine_Lock);
        return;
    }

    sDBG_Line_Push.m_nuiLine = (TgUINT_E32)nuiLine;

    /* We have copied the data, so reset the counter. */
    TgSTD_ATOMIC(store)(&psCMD_DBG->m_xnuiLine, 0);

    /* Release the lock as we should only hold it for the minimum amount of time. Not that a spin lock is computational wasteful and this is a hard requirement. */
    tgCM_UT_LF__SN__Signal(&psCMD_DBG->m_sLine_Lock);

    ahVLKN_Descriptor_Sets[0] = psDBG_VLKN_CXT_EXEC->m_hVLKN_Descriptor_Set_Render_DESC;
    ahVLKN_Descriptor_Sets[1] = psDBG_VLKN_CXT_EXEC->m_hVLKN_DBG_Descriptor_Set__Line_Task_Mesh;

    /* Task+Mesh shader rendering (inside render pass) */
    iCmd_Index = uCMD.psVLKN - psVLKN_CXT_EXEC->m_asCommand;
    psCMD_DBG_VLKN = psDBG_VLKN_CXT_EXEC->m_asComand_DBG + iCmd_Index;
    hVLKN_Pipeline = psCMD_DBG_VLKN->m_ahVLKN_Pipeline_Graphics[ETgKN_GPU_DBG_GRAPHICS_PIPELINE_LINE_TASK_MESH];
    hVLKN_Pipeline_Layout = psDBG_VLKN_CXT_EXEC->m_ahVLKN_Pipeline_Layout[ETgKN_GPU_DBG_PIPELINE_LAYOUT__LINE_TASK_MESH];

    vkCmdBindPipeline( uCMD.psVLKN->m_hVLKN_Command_Buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, hVLKN_Pipeline);
    vkCmdBindDescriptorSets( uCMD.psVLKN->m_hVLKN_Command_Buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, hVLKN_Pipeline_Layout, 0, 2u, ahVLKN_Descriptor_Sets,
                             1u, &uCMD.psVLKN->m_uiUBO_Render_DESC_Offset );

    /* Push the line count as a constant */
    vkCmdPushConstants( uCMD.psVLKN->m_hVLKN_Command_Buffer, hVLKN_Pipeline_Layout, VK_SHADER_STAGE_TASK_BIT_EXT, 0, sizeof(sDBG_Line_Push), &sDBG_Line_Push );

    /* Calculate task shader dispatch size (64 lines per task workgroup) */
    uiTask_Workgroups = (TgUINT_E32)((sDBG_Line_Push.m_nuiLine + KTgKN_GPU_VLKN_DBG_LINE__TASK_WORKGROUP_SIZE - 1) / KTgKN_GPU_VLKN_DBG_LINE__TASK_WORKGROUP_SIZE);
    vkCmdDrawMeshTasksEXT( uCMD.psVLKN->m_hVLKN_Command_Buffer, uiTask_Workgroups, 1, 1 );
}


/* ---- tgKN_GPU_EXT__CMD__Render_Debug_Geom ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_EXT__CMD__Render_Debug_Geom( STg2_KN_GPU_CMD_PC psCMD, ETgKN_GPU_DEBUG_PM enPM, STg2_KN_GPU_DBG_Geom_CPC psGeom_UBO, TgBOOL_C bUnLit )
{
    UTg2_KN_GPU_CMD_C                           uCMD = { .ps = psCMD };
    TgRSIZE                             uiEXEC = (uCMD.psVLKN->m_sBase.m_tiCXT_WORK.m_uiI >> 16) & 0xFFFF;
    TgRSIZE                             uiWORK = (uCMD.psVLKN->m_sBase.m_tiCXT_WORK.m_uiI & 0xFFFF) % KTgKN_GPU_MAX_EXEC_CONTEXT_COMMAND;
    STg2_KN_GPU_VLKN_CXT_EXEC_PC        psVLKN_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + uiEXEC;
    STg2_KN_GPU_DBG_VLKN_CXT_EXEC_PC    psDBG_VLKN_CXT_EXEC = g_asKN_GPU_DBG_EXT_CXT_EXEC + uiEXEC;

    STg2_KN_GPU_DBG_VLKN_CMD_P          psCMD_DBG_VLKN;
    TgSINT_PTR                          iCmd_Index;
    TgRSIZE                             uiPipeline;
    VkPipeline                          hVLKN_Pipeline;
    VkDeviceSize                        uiBuffer_Offset;
    TgRSIZE                             nuiIndex;

    TgPARAM_CHECK_KN_GPU_CMD( psCMD );

    if (enPM < ETgKN_GPU_DEBUG_PM_3D_START || enPM >= ETgKN_GPU_DEBUG_PM_3D_END)
    {
        return;
    }
    enPM = (ETgKN_GPU_DEBUG_PM)((TgSINT_E32)enPM - ETgKN_GPU_DEBUG_PM_3D_START);

    if (VK_NULL_HANDLE == psDBG_VLKN_CXT_EXEC->m_ahVLKN_VBO_Buffer__Geom[enPM])
    {
        return;
    }

    /* Bind vertex and index buffers for rendering */
    uiBuffer_Offset = 0;
    vkCmdBindVertexBuffers(uCMD.psVLKN->m_hVLKN_Command_Buffer, 0u, 1u, psDBG_VLKN_CXT_EXEC->m_ahVLKN_VBO_Buffer__Geom + enPM, &uiBuffer_Offset);
    vkCmdBindIndexBuffer(uCMD.psVLKN->m_hVLKN_Command_Buffer, psDBG_VLKN_CXT_EXEC->m_ahVLKN_IBO_Buffer__Geom[enPM], uiBuffer_Offset, VK_INDEX_TYPE_UINT16);

    vkCmdBindDescriptorSets( uCMD.psVLKN->m_hVLKN_Command_Buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, 
                             psDBG_VLKN_CXT_EXEC->m_ahVLKN_Pipeline_Layout[ETgKN_GPU_DBG_PIPELINE_LAYOUT__NONE], 0, 1u,
                             &psDBG_VLKN_CXT_EXEC->m_hVLKN_Descriptor_Set_Render_DESC, 1u, &uCMD.psVLKN->m_uiUBO_Render_DESC_Offset);

    iCmd_Index = uCMD.psVLKN - psVLKN_CXT_EXEC->m_asCommand;
    psCMD_DBG_VLKN = psDBG_VLKN_CXT_EXEC->m_asComand_DBG + iCmd_Index;
    uiPipeline = bUnLit ? ETgKN_GPU_DBG_GRAPHICS_PIPELINE_GEOM_02 : ETgKN_GPU_DBG_GRAPHICS_PIPELINE_GEOM_02_LIT;
    hVLKN_Pipeline = psCMD_DBG_VLKN->m_ahVLKN_Pipeline_Graphics[uiPipeline];
    TgPARAM_CHECK(VK_NULL_HANDLE != hVLKN_Pipeline);
    vkCmdBindPipeline(uCMD.psVLKN->m_hVLKN_Command_Buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, hVLKN_Pipeline);

    vkCmdSetPrimitiveTopology( uCMD.psVLKN->m_hVLKN_Command_Buffer, VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST );

    TgCOMPILER_ASSERT(sizeof(STg2_KN_GPU_DBG_Geom) % 4 == 0, 0);
    vkCmdPushConstants( uCMD.psVLKN->m_hVLKN_Command_Buffer, psDBG_VLKN_CXT_EXEC->m_ahVLKN_Pipeline_Layout[ETgKN_GPU_DBG_PIPELINE_LAYOUT__NONE],
                        VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 0, sizeof(STg2_KN_GPU_DBG_Geom), psGeom_UBO );

    nuiIndex = psDBG_VLKN_CXT_EXEC->m_nbyVLKN_IBO__Geom[enPM] / sizeof(TgUINT_E16);
    vkCmdDrawIndexed(uCMD.psVLKN->m_hVLKN_Command_Buffer, nuiIndex, 1, 0, 0, 0);
}


/* ---- tgKN_GPU_EXT__CMD__Render_Debug_Geom_Instance ---------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_EXT__CMD__Render_Debug_Geom_Instance( STg2_KN_GPU_CMD_PC psCMD, ETgKN_GPU_DEBUG_PM enPM, TgRSIZE nuiGeom, STg2_KN_GPU_DBG_Geom_CPC asGeom, TgBOOL_C bUnLit )
{
    UTg2_KN_GPU_CMD_C                           uCMD = { .ps = psCMD };
    TgRSIZE                             uiEXEC = (uCMD.psVLKN->m_sBase.m_tiCXT_WORK.m_uiI >> 16) & 0xFFFF;
    TgRSIZE                             uiWORK = (uCMD.psVLKN->m_sBase.m_tiCXT_WORK.m_uiI & 0xFFFF) % KTgKN_GPU_MAX_EXEC_CONTEXT_COMMAND;
    STg2_KN_GPU_VLKN_CXT_EXEC_PC        psVLKN_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + uiEXEC;
    STg2_KN_GPU_DBG_VLKN_CXT_EXEC_PC    psDBG_VLKN_CXT_EXEC = g_asKN_GPU_DBG_EXT_CXT_EXEC + uiEXEC;

    STg2_KN_GPU_DBG_VLKN_CMD_P          psCMD_DBG_VLKN;
    TgSINT_PTR                          iCmd_Index;
    STg2_KN_GPU_DBG_VLKN_CXT_CMD_P      psVLKN_DBG_CXT_CMD;
    VkDescriptorSet                     ahVLKN_Descriptor_Sets[2];
    TgRSIZE                             uiPipeline;
    VkPipeline                          hVLKN_Pipeline;
    VkDeviceSize                        uiBuffer_Offset;
    TgRESULT                            iRet;
    STg2_KN_GPU_DBG_Geom_Instance_Push  sGeom_Instance_Push;

    TgPARAM_CHECK_KN_GPU_CMD( psCMD );

    if (enPM < ETgKN_GPU_DEBUG_PM_3D_START || enPM >= ETgKN_GPU_DEBUG_PM_3D_END)
    {
        return;
    }
    enPM = (ETgKN_GPU_DEBUG_PM)((TgSINT_E32)enPM - ETgKN_GPU_DEBUG_PM_3D_START);

    TgVERIFY(VK_NULL_HANDLE != psDBG_VLKN_CXT_EXEC->m_ahVLKN_VBO_Buffer__Geom[enPM]);
    TgVERIFY(nullptr != psDBG_VLKN_CXT_EXEC->m_sSBO__Geom.m_uSBO_Mapped.m_pVoid);

    psVLKN_DBG_CXT_CMD = psDBG_VLKN_CXT_EXEC->m_asContext_Command_DBG + uiWORK;
    ahVLKN_Descriptor_Sets[0] = psDBG_VLKN_CXT_EXEC->m_hVLKN_Descriptor_Set_Render_DESC;
    ahVLKN_Descriptor_Sets[1] = psDBG_VLKN_CXT_EXEC->m_hVLKN_DBG_Descriptor_Set__Geom;

    iCmd_Index = uCMD.psVLKN - psVLKN_CXT_EXEC->m_asCommand;
    psCMD_DBG_VLKN = psDBG_VLKN_CXT_EXEC->m_asComand_DBG + iCmd_Index;
    uiPipeline = bUnLit ? ETgKN_GPU_DBG_GRAPHICS_PIPELINE_GEOM_02_INSTANCE : ETgKN_GPU_DBG_GRAPHICS_PIPELINE_GEOM_02_LIT_INSTANCE;
    hVLKN_Pipeline = psCMD_DBG_VLKN->m_ahVLKN_Pipeline_Graphics[uiPipeline];
    TgPARAM_CHECK(VK_NULL_HANDLE != hVLKN_Pipeline);
    vkCmdBindPipeline(uCMD.psVLKN->m_hVLKN_Command_Buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, hVLKN_Pipeline);

    iRet = tgKN_GPU_EXT__CMD__Update_SBO( &sGeom_Instance_Push.m_uiGeom_SBO_Offset, &nuiGeom, &psVLKN_DBG_CXT_CMD->m_xuiSBO__Geom_Offset, psCMD, asGeom,
                                          sizeof(asGeom[0]), psVLKN_DBG_CXT_CMD->m_uiSBO__Geom_End, &psDBG_VLKN_CXT_EXEC->m_sSBO__Geom);
    if (TgFAILED(iRet))
    {
        TgERROR_MSGF(false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to copy geometry instance data.");
        return;
    }

    vkCmdSetPrimitiveTopology( uCMD.psVLKN->m_hVLKN_Command_Buffer, VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST );
    uiBuffer_Offset = 0;
    vkCmdBindVertexBuffers(uCMD.psVLKN->m_hVLKN_Command_Buffer, 0, 1, psDBG_VLKN_CXT_EXEC->m_ahVLKN_VBO_Buffer__Geom + enPM, &uiBuffer_Offset);
    vkCmdBindIndexBuffer(uCMD.psVLKN->m_hVLKN_Command_Buffer, psDBG_VLKN_CXT_EXEC->m_ahVLKN_IBO_Buffer__Geom[enPM], uiBuffer_Offset, VK_INDEX_TYPE_UINT16);

    vkCmdBindDescriptorSets( uCMD.psVLKN->m_hVLKN_Command_Buffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
                             psDBG_VLKN_CXT_EXEC->m_ahVLKN_Pipeline_Layout[ETgKN_GPU_DBG_PIPELINE_LAYOUT__SBO], 0,
                             2u, ahVLKN_Descriptor_Sets, 1u, &uCMD.psVLKN->m_uiUBO_Render_DESC_Offset);

    vkCmdPushConstants( uCMD.psVLKN->m_hVLKN_Command_Buffer, psDBG_VLKN_CXT_EXEC->m_ahVLKN_Pipeline_Layout[ETgKN_GPU_DBG_PIPELINE_LAYOUT__SBO],
                        VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 0, sizeof(sGeom_Instance_Push), &sGeom_Instance_Push);

    vkCmdDrawIndexed(uCMD.psVLKN->m_hVLKN_Command_Buffer, (TgUINT_E32)psDBG_VLKN_CXT_EXEC->m_nbyVLKN_IBO__Geom[enPM] / sizeof(TgUINT_E16), (TgUINT_E32)nuiGeom, 0, 0, 0);
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_GPU_EXT__CMD__Render_From_SBO_Internal ------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT tgKN_GPU_EXT__CMD__Update_SBO( TgUINT_E32_P puiOffset, TgRSIZE_P pnuiInst, TgRSIZE_A *pxuiOffset, STg2_KN_GPU_CMD_PC psCMD, TgVOID_CPCU puiData,
                                               TgRSIZE nbyInst, TgRSIZE_C nbySBO_End, STg2_KN_GPU_SBO_DESC_PC psSBO_DESC )
{
    UTg2_KN_GPU_CMD_C                           uCMD = { .ps = psCMD };
    TgRSIZE                             uiEXEC = (uCMD.psVLKN->m_sBase.m_tiCXT_WORK.m_uiI >> 16) & 0xFFFF;
    TgRSIZE                             uiWORK = (uCMD.psVLKN->m_sBase.m_tiCXT_WORK.m_uiI & 0xFFFF) % KTgKN_GPU_MAX_EXEC_CONTEXT_COMMAND;
    STg2_KN_GPU_DBG_VLKN_CXT_EXEC_PC    psDBG_VLKN_CXT_EXEC = g_asKN_GPU_DBG_EXT_CXT_EXEC + uiEXEC;
    STg2_KN_GPU_DBG_VLKN_CXT_CMD_PC     psVLKN_DBG_CXT_CMD = psDBG_VLKN_CXT_EXEC->m_asContext_Command_DBG + uiWORK;

    TgRSIZE                             nbyTotal_Inst_Data, nbyTotal_Allocated, nbyTotal_Offset;
    TgRSIZE                             nbyOffset_Flush, nbyOffset_Dest;

    TgPARAM_CHECK (!(nullptr == psSBO_DESC || VK_NULL_HANDLE == psSBO_DESC->m_hVLKN_SBO_Buffer || nullptr == psSBO_DESC->m_uSBO_Mapped.m_pVoid));

    /* Calculate the total number of bytes required for all of the data elements */
    nbyTotal_Inst_Data = *pnuiInst * nbyInst;

    /* In the shader, the data needs to be referenced by index (therefore a multiple of the element size), but the upload needs to be nonCoherent aligned. */
    nbyTotal_Allocated = nbyTotal_Inst_Data + 2*psSBO_DESC->m_uiAligned_SBO_Alignment;
    nbyTotal_Allocated =  tgCM_CEL_ALGN_PW2_UMAX( nbyTotal_Allocated, psSBO_DESC->m_uiAligned_SBO_Alignment );

    /* Ensure atomic offset acquisition to prevent race conditions between text calls */
    nbyOffset_Flush = TgSTD_ATOMIC(fetch_add)(pxuiOffset, nbyTotal_Allocated);
    TgVERIFY(nbyOffset_Flush % psSBO_DESC->m_uiAligned_SBO_Alignment == 0);

    /* Align to the start of an element */
    nbyOffset_Dest = nbyOffset_Flush;
    if (0 != nbyOffset_Dest % psSBO_DESC->m_uiAligned_SBO_Size_Element)
    {
        nbyOffset_Dest += psSBO_DESC->m_uiAligned_SBO_Size_Element - (nbyOffset_Dest % psSBO_DESC->m_uiAligned_SBO_Size_Element);
    }
    TgVERIFY(nbyOffset_Dest % psSBO_DESC->m_uiAligned_SBO_Alignment == 0);

    if (nbyOffset_Dest + nbyTotal_Inst_Data >= nbySBO_End)
    {
        TgERROR_GEN_MSGF(false, u8"Buffer pool exhausted: %zu/%zu", nbyOffset_Dest, nbySBO_End);

        *pnuiInst = (nbySBO_End > nbyOffset_Dest) ? (nbySBO_End - nbyOffset_Dest) / nbyInst : 0;
        if (0 == *pnuiInst)
        {
            return KTgE_FAIL;
        }
        nbyTotal_Inst_Data = *pnuiInst * nbyInst;
        nbyTotal_Allocated = nbySBO_End - nbyOffset_Flush;
    }

    if (*pnuiInst <= 0)
    {
        return (KTgE_FAIL);
    }
    else
    {
        VkMappedMemoryRange                 sMapped_Range = {
                                                .sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
                                                .pNext = nullptr,
                                                .memory = psSBO_DESC->m_hVLKN_SBO_Memory,
                                                .offset = nbyOffset_Flush,
                                                .size = nbyTotal_Allocated,
                                            };

        TgUN_POINTER                        uDBG_Mapped;
        VkResult                            eResult;

        uDBG_Mapped = psSBO_DESC->m_uSBO_Mapped;
        uDBG_Mapped.m_pui08 += nbyOffset_Dest;

        /* NO BARRIER NEEDED BEFORE COPY - Host-visible memory can always be written by CPU */
        tgMM_Copy(uDBG_Mapped.m_pVoid, nbySBO_End - nbyOffset_Dest, puiData, nbyTotal_Inst_Data);

        /* FLUSH IS REQUIRED - Ensures CPU writes are visible to GPU (unless memory is coherent) */
        eResult = vkFlushMappedMemoryRanges( uCMD.psVLKN->m_hVLKN_Device, 1, &sMapped_Range );
        if (VK_SUCCESS != eResult)
        {
            TgWARNING_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to flush mapped memory ranges for buffer." );
            return KTgE_FAIL;
        }

        *puiOffset = (TgUINT_E32)(nbyOffset_Dest / nbyInst);
        return KTgS_OK;
    }
}


TgDISABLE_ALL_WARNNGS_POP

/*# defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
#endif
