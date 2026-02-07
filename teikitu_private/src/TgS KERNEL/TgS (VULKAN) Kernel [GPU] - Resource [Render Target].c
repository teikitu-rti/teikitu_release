/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (VULKAN) Kernel [GPU] - Resource [Render Target].c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.22 | »GUID« 7ECEAB43-40E4-4161-8F94-87AF31F5BA9A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    Models:     Claude 3.7, Claude 4.0
    ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/** @brief Create graphics pipelines for a render target
    @param [in] ARG0 Pointer to the render target
    @param [in] ARG1 Device handle */
static TgRESULT
tgKN_GPU_VLKN__Render_Target__Create_Pipelines(
    STg2_KN_GPU_VLKN_Render_Target_PC ARG0, VkDevice_C ARG1, STg2_KN_GPU_VLKN_CXT_EXEC_PC ARG2 );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public GPU Functions - Command                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_GPU_VLKN__CMD__Image_Barrier__Graphics_Write_To_Compute_Read ----------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_VLKN__CMD__Image_Barrier__Graphics_Write_To_Compute_Read(
    STg2_KN_GPU_CMD_PC                          psCMD_Graphics,
    STg2_KN_GPU_CMD_PC                          psCMD_Compute,
    STg2_KN_GPU_VLKN_Render_Target_P            psRender_Target )
{
    UTg2_KN_GPU_CMD_C                           uCMD_Graphics = { .ps = psCMD_Graphics };
    UTg2_KN_GPU_CMD_C                           uCMD_Compute = { .ps = psCMD_Compute };
    TgRSIZE_C                                   uiEXEC = (uCMD_Compute.psVLKN->m_sBase.m_tiCXT_WORK.m_uiI >> 16) & 0xFFFF;
    STg2_KN_GPU_VLKN_CXT_EXEC_PC                psVLKN_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + uiEXEC;

    VkImageMemoryBarrier2                       sVLKN_Graphics_Release;
    VkImageMemoryBarrier2                       sVLKN_Compute_Acquire;

    /* Validate parameters */
    TgPARAM_CHECK_KN_GPU_CMD(psCMD_Graphics);
    TgPARAM_CHECK_KN_GPU_CMD(psCMD_Compute);
    TgPARAM_CHECK(psRender_Target);
    TgPARAM_CHECK(uiEXEC == ((uCMD_Graphics.psVLKN->m_sBase.m_tiCXT_WORK.m_uiI >> 16) & 0xFFFF));

    /* RELEASE ON GRAPHICS QUEUE */
    tgMM_Set_U08_0x00(&sVLKN_Graphics_Release, sizeof(sVLKN_Graphics_Release));
    sVLKN_Graphics_Release.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2;
    sVLKN_Graphics_Release.pNext = nullptr;
    sVLKN_Graphics_Release.srcStageMask  = VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT;
    sVLKN_Graphics_Release.srcAccessMask = VK_ACCESS_2_COLOR_ATTACHMENT_WRITE_BIT;
    sVLKN_Graphics_Release.dstStageMask  = 0;
    sVLKN_Graphics_Release.dstAccessMask = 0;
    sVLKN_Graphics_Release.oldLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    sVLKN_Graphics_Release.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    sVLKN_Graphics_Release.srcQueueFamilyIndex = (TgUINT_E32)psVLKN_CXT_EXEC->m_auiVLKN_Queue_Family_Index[ETgKN_GPU_EXT_COMMAND_GRAPHICS];
    sVLKN_Graphics_Release.dstQueueFamilyIndex = (TgUINT_E32)psVLKN_CXT_EXEC->m_auiVLKN_Queue_Family_Index[ETgKN_GPU_EXT_COMMAND_COMPUTE];
    sVLKN_Graphics_Release.image = psRender_Target->m_ahVLKN_Colour_Image[0];
    sVLKN_Graphics_Release.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    sVLKN_Graphics_Release.subresourceRange.baseMipLevel = 0;
    sVLKN_Graphics_Release.subresourceRange.levelCount = 1;
    sVLKN_Graphics_Release.subresourceRange.baseArrayLayer = 0;
    sVLKN_Graphics_Release.subresourceRange.layerCount = 1;

    /* Release Queue Family Ownership of the Images */
    {
        VkDependencyInfo                            sVLKN_Dependency_Info = { 
                                                        .sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO,
                                                        .imageMemoryBarrierCount = 1,
                                                        .pImageMemoryBarriers = &sVLKN_Graphics_Release,
                                                    };

        vkCmdPipelineBarrier2( uCMD_Graphics.psVLKN->m_hVLKN_Command_Buffer, &sVLKN_Dependency_Info );
    }

    /* ACQUIRE ON COMPUTE QUEUE */
    tgMM_Set_U08_0x00(&sVLKN_Compute_Acquire, sizeof(sVLKN_Compute_Acquire));
    sVLKN_Compute_Acquire.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2;
    sVLKN_Compute_Acquire.pNext = nullptr;
    sVLKN_Compute_Acquire.srcStageMask  = 0;
    sVLKN_Compute_Acquire.srcAccessMask = 0;
    sVLKN_Compute_Acquire.dstStageMask  = VK_PIPELINE_STAGE_2_COMPUTE_SHADER_BIT;
    sVLKN_Compute_Acquire.dstAccessMask = VK_ACCESS_2_SHADER_READ_BIT;
    sVLKN_Compute_Acquire.oldLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    sVLKN_Compute_Acquire.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    sVLKN_Compute_Acquire.srcQueueFamilyIndex = (TgUINT_E32)psVLKN_CXT_EXEC->m_auiVLKN_Queue_Family_Index[ETgKN_GPU_EXT_COMMAND_GRAPHICS];
    sVLKN_Compute_Acquire.dstQueueFamilyIndex = (TgUINT_E32)psVLKN_CXT_EXEC->m_auiVLKN_Queue_Family_Index[ETgKN_GPU_EXT_COMMAND_COMPUTE];
    sVLKN_Compute_Acquire.image = psRender_Target->m_ahVLKN_Colour_Image[0];
    sVLKN_Compute_Acquire.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    sVLKN_Compute_Acquire.subresourceRange.baseMipLevel = 0;
    sVLKN_Compute_Acquire.subresourceRange.levelCount = 1;
    sVLKN_Compute_Acquire.subresourceRange.baseArrayLayer = 0;
    sVLKN_Compute_Acquire.subresourceRange.layerCount = 1;

    /* Transition source and destination to compute-appropriate layouts */
    {
        VkDependencyInfo                            sVLKN_Dependency_Info = { 
                                                        .sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO,
                                                        .imageMemoryBarrierCount = 1,
                                                        .pImageMemoryBarriers = &sVLKN_Compute_Acquire,
                                                    };
        vkCmdPipelineBarrier2( uCMD_Compute.psVLKN->m_hVLKN_Command_Buffer, &sVLKN_Dependency_Info );
    }

    return (KTgS_OK);
}


/* ---- tgKN_GPU_VLKN__CMD__Image_Barrier__Graphics_Swap_To_Compute_Write ----------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_VLKN__CMD__Image_Barrier__Graphics_Swap_To_Compute_Write(
    STg2_KN_GPU_CMD_PC                          psCMD_Graphics,
    STg2_KN_GPU_CMD_PC                          psCMD_Compute,
    STg2_KN_GPU_VLKN_Render_Target_P            psRender_Target )
{
    UTg2_KN_GPU_CMD_C                           uCMD_Graphics = { .ps = psCMD_Graphics };
    UTg2_KN_GPU_CMD_C                           uCMD_Compute = { .ps = psCMD_Compute };
    TgRSIZE_C                                   uiEXEC = (uCMD_Compute.psVLKN->m_sBase.m_tiCXT_WORK.m_uiI >> 16) & 0xFFFF;
    STg2_KN_GPU_VLKN_CXT_EXEC_PC                psVLKN_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + uiEXEC;

    VkImageMemoryBarrier2                       sVLKN_Graphics_Release;
    VkImageMemoryBarrier2                       sVLKN_Compute_Acquire;

    /* Validate parameters */
    TgPARAM_CHECK_KN_GPU_CMD(psCMD_Graphics);
    TgPARAM_CHECK_KN_GPU_CMD(psCMD_Compute);
    TgPARAM_CHECK(psRender_Target);
    TgPARAM_CHECK(uiEXEC == ((uCMD_Graphics.psVLKN->m_sBase.m_tiCXT_WORK.m_uiI >> 16) & 0xFFFF));

    /* RELEASE ON GRAPHICS QUEUE */
    tgMM_Set_U08_0x00(&sVLKN_Graphics_Release, sizeof(sVLKN_Graphics_Release));
    sVLKN_Graphics_Release.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2;
    sVLKN_Graphics_Release.pNext = nullptr;
    sVLKN_Graphics_Release.srcStageMask  = VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT;
    sVLKN_Graphics_Release.srcAccessMask = VK_ACCESS_2_COLOR_ATTACHMENT_WRITE_BIT;
    sVLKN_Graphics_Release.dstStageMask  = 0;
    sVLKN_Graphics_Release.dstAccessMask = 0;
    sVLKN_Graphics_Release.oldLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    sVLKN_Graphics_Release.newLayout = VK_IMAGE_LAYOUT_GENERAL;
    sVLKN_Graphics_Release.srcQueueFamilyIndex = (TgUINT_E32)psVLKN_CXT_EXEC->m_auiVLKN_Queue_Family_Index[ETgKN_GPU_EXT_COMMAND_GRAPHICS];
    sVLKN_Graphics_Release.dstQueueFamilyIndex = (TgUINT_E32)psVLKN_CXT_EXEC->m_auiVLKN_Queue_Family_Index[ETgKN_GPU_EXT_COMMAND_COMPUTE];
    sVLKN_Graphics_Release.image = psRender_Target->m_ahVLKN_Colour_Image[0];
    sVLKN_Graphics_Release.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    sVLKN_Graphics_Release.subresourceRange.baseMipLevel = 0;
    sVLKN_Graphics_Release.subresourceRange.levelCount = 1;
    sVLKN_Graphics_Release.subresourceRange.baseArrayLayer = 0;
    sVLKN_Graphics_Release.subresourceRange.layerCount = 1;

    /* Release Queue Family Ownership of the Images */
    {
        VkDependencyInfo                            sVLKN_Dependency_Info = { 
                                                        .sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO,
                                                        .imageMemoryBarrierCount = 1,
                                                        .pImageMemoryBarriers = &sVLKN_Graphics_Release,
                                                    };

        vkCmdPipelineBarrier2( uCMD_Graphics.psVLKN->m_hVLKN_Command_Buffer, &sVLKN_Dependency_Info );
    }

    /* ACQUIRE ON COMPUTE QUEUE */
    tgMM_Set_U08_0x00(&sVLKN_Compute_Acquire, sizeof(sVLKN_Compute_Acquire));
    sVLKN_Compute_Acquire.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2;
    sVLKN_Compute_Acquire.pNext = nullptr;
    sVLKN_Compute_Acquire.srcStageMask  = 0;
    sVLKN_Compute_Acquire.srcAccessMask = 0;
    sVLKN_Compute_Acquire.dstStageMask  = VK_PIPELINE_STAGE_2_COMPUTE_SHADER_BIT;
    sVLKN_Compute_Acquire.dstAccessMask = VK_ACCESS_2_SHADER_STORAGE_WRITE_BIT;
    sVLKN_Compute_Acquire.oldLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    sVLKN_Compute_Acquire.newLayout = VK_IMAGE_LAYOUT_GENERAL;
    sVLKN_Compute_Acquire.srcQueueFamilyIndex = (TgUINT_E32)psVLKN_CXT_EXEC->m_auiVLKN_Queue_Family_Index[ETgKN_GPU_EXT_COMMAND_GRAPHICS];
    sVLKN_Compute_Acquire.dstQueueFamilyIndex = (TgUINT_E32)psVLKN_CXT_EXEC->m_auiVLKN_Queue_Family_Index[ETgKN_GPU_EXT_COMMAND_COMPUTE];
    sVLKN_Compute_Acquire.image = psRender_Target->m_ahVLKN_Colour_Image[0];
    sVLKN_Compute_Acquire.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    sVLKN_Compute_Acquire.subresourceRange.baseMipLevel = 0;
    sVLKN_Compute_Acquire.subresourceRange.levelCount = 1;
    sVLKN_Compute_Acquire.subresourceRange.baseArrayLayer = 0;
    sVLKN_Compute_Acquire.subresourceRange.layerCount = 1;

    /* Transition source and destination to compute-appropriate layouts */
    {
        VkDependencyInfo                            sVLKN_Dependency_Info = { 
                                                        .sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO,
                                                        .imageMemoryBarrierCount = 1,
                                                        .pImageMemoryBarriers = &sVLKN_Compute_Acquire,
                                                    };
        vkCmdPipelineBarrier2( uCMD_Compute.psVLKN->m_hVLKN_Command_Buffer, &sVLKN_Dependency_Info );
    }

    return (KTgS_OK);
}


/* ---- tgKN_GPU_VLKN__CMD__Image_Barrier__Compute_Read_To_Graphics_Write ----------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_VLKN__CMD__Image_Barrier__Compute_Read_To_Graphics_Write(
    STg2_KN_GPU_CMD_PC                          psCMD_Compute,
    STg2_KN_GPU_CMD_PC                          psCMD_Graphics,
    STg2_KN_GPU_VLKN_Render_Target_P            psRender_Target )
{
    UTg2_KN_GPU_CMD_C                           uCMD_Graphics = { .ps = psCMD_Graphics };
    UTg2_KN_GPU_CMD_C                           uCMD_Compute = { .ps = psCMD_Compute };
    TgRSIZE_C                                   uiEXEC = (uCMD_Compute.psVLKN->m_sBase.m_tiCXT_WORK.m_uiI >> 16) & 0xFFFF;
    STg2_KN_GPU_VLKN_CXT_EXEC_PC                psVLKN_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + uiEXEC;

    VkImageMemoryBarrier2                       sVLKN_Compute_Release;
    VkImageMemoryBarrier2                       sVLKN_Graphics_Acquire;

    /* Validate parameters */
    TgPARAM_CHECK_KN_GPU_CMD(psCMD_Graphics);
    TgPARAM_CHECK_KN_GPU_CMD(psCMD_Compute);
    TgPARAM_CHECK(psRender_Target);
    TgPARAM_CHECK(uiEXEC == ((uCMD_Graphics.psVLKN->m_sBase.m_tiCXT_WORK.m_uiI >> 16) & 0xFFFF));

    /* RELEASE ON GRAPHICS QUEUE */
    tgMM_Set_U08_0x00(&sVLKN_Compute_Release, sizeof(sVLKN_Compute_Release));
    sVLKN_Compute_Release.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2;
    sVLKN_Compute_Release.pNext = nullptr;
    sVLKN_Compute_Release.srcStageMask  = VK_PIPELINE_STAGE_2_COMPUTE_SHADER_BIT;
    sVLKN_Compute_Release.srcAccessMask = VK_ACCESS_2_SHADER_READ_BIT;
    sVLKN_Compute_Release.dstStageMask  = 0;
    sVLKN_Compute_Release.dstAccessMask = 0;
    sVLKN_Compute_Release.oldLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    sVLKN_Compute_Release.newLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    sVLKN_Compute_Release.srcQueueFamilyIndex = (TgUINT_E32)psVLKN_CXT_EXEC->m_auiVLKN_Queue_Family_Index[ETgKN_GPU_EXT_COMMAND_COMPUTE];
    sVLKN_Compute_Release.dstQueueFamilyIndex = (TgUINT_E32)psVLKN_CXT_EXEC->m_auiVLKN_Queue_Family_Index[ETgKN_GPU_EXT_COMMAND_GRAPHICS];
    sVLKN_Compute_Release.image = psRender_Target->m_ahVLKN_Colour_Image[0];
    sVLKN_Compute_Release.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    sVLKN_Compute_Release.subresourceRange.baseMipLevel = 0;
    sVLKN_Compute_Release.subresourceRange.levelCount = 1;
    sVLKN_Compute_Release.subresourceRange.baseArrayLayer = 0;
    sVLKN_Compute_Release.subresourceRange.layerCount = 1;

    /* Release Queue Family Ownership of the Images */
    {
        VkDependencyInfo                            sVLKN_Dependency_Info = { 
                                                        .sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO,
                                                        .imageMemoryBarrierCount = 1,
                                                        .pImageMemoryBarriers = &sVLKN_Compute_Release,
                                                    };

        vkCmdPipelineBarrier2( uCMD_Compute.psVLKN->m_hVLKN_Command_Buffer, &sVLKN_Dependency_Info );
    }

    /* ACQUIRE ON COMPUTE QUEUE */
    tgMM_Set_U08_0x00(&sVLKN_Graphics_Acquire, sizeof(sVLKN_Graphics_Acquire));
    sVLKN_Graphics_Acquire.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2;
    sVLKN_Graphics_Acquire.pNext = nullptr;
    sVLKN_Graphics_Acquire.srcStageMask  = 0;
    sVLKN_Graphics_Acquire.srcAccessMask = 0;
    sVLKN_Graphics_Acquire.dstStageMask  = VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT;
    sVLKN_Graphics_Acquire.dstAccessMask = VK_ACCESS_2_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_2_COLOR_ATTACHMENT_READ_BIT;
    sVLKN_Graphics_Acquire.oldLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    sVLKN_Graphics_Acquire.newLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    sVLKN_Graphics_Acquire.srcQueueFamilyIndex = (TgUINT_E32)psVLKN_CXT_EXEC->m_auiVLKN_Queue_Family_Index[ETgKN_GPU_EXT_COMMAND_COMPUTE];
    sVLKN_Graphics_Acquire.dstQueueFamilyIndex = (TgUINT_E32)psVLKN_CXT_EXEC->m_auiVLKN_Queue_Family_Index[ETgKN_GPU_EXT_COMMAND_GRAPHICS];
    sVLKN_Graphics_Acquire.image = psRender_Target->m_ahVLKN_Colour_Image[0];
    sVLKN_Graphics_Acquire.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    sVLKN_Graphics_Acquire.subresourceRange.baseMipLevel = 0;
    sVLKN_Graphics_Acquire.subresourceRange.levelCount = 1;
    sVLKN_Graphics_Acquire.subresourceRange.baseArrayLayer = 0;
    sVLKN_Graphics_Acquire.subresourceRange.layerCount = 1;

    /* Transition source and destination to compute-appropriate layouts */
    {
        VkDependencyInfo                            sVLKN_Dependency_Info = { 
                                                        .sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO,
                                                        .imageMemoryBarrierCount = 1,
                                                        .pImageMemoryBarriers = &sVLKN_Graphics_Acquire,
                                                    };
        vkCmdPipelineBarrier2( uCMD_Graphics.psVLKN->m_hVLKN_Command_Buffer, &sVLKN_Dependency_Info );
    }

    return (KTgS_OK);
}


/* ---- tgKN_GPU_VLKN__CMD__Image_Barrier__Compute_Write_To_Graphics_Present ------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_VLKN__CMD__Image_Barrier__Compute_Write_To_Graphics_Present(
    STg2_KN_GPU_CMD_PC                          psCMD_Compute,
    STg2_KN_GPU_CMD_PC                          psCMD_Graphics,
    STg2_KN_GPU_VLKN_Render_Target_P            psRender_Target )
{
    UTg2_KN_GPU_CMD_C                           uCMD_Graphics = { .ps = psCMD_Graphics };
    UTg2_KN_GPU_CMD_C                           uCMD_Compute = { .ps = psCMD_Compute };
    TgRSIZE_C                                   uiEXEC = (uCMD_Compute.psVLKN->m_sBase.m_tiCXT_WORK.m_uiI >> 16) & 0xFFFF;
    STg2_KN_GPU_VLKN_CXT_EXEC_PC                psVLKN_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + uiEXEC;

    VkImageMemoryBarrier2                       sVLKN_Compute_Release;
    VkImageMemoryBarrier2                       sVLKN_Graphics_Acquire;

    /* Validate parameters */
    TgPARAM_CHECK_KN_GPU_CMD(psCMD_Graphics);
    TgPARAM_CHECK_KN_GPU_CMD(psCMD_Compute);
    TgPARAM_CHECK(psRender_Target);
    TgPARAM_CHECK(uiEXEC == ((uCMD_Graphics.psVLKN->m_sBase.m_tiCXT_WORK.m_uiI >> 16) & 0xFFFF));

    /* RELEASE ON GRAPHICS QUEUE */
    tgMM_Set_U08_0x00(&sVLKN_Compute_Release, sizeof(sVLKN_Compute_Release));
    sVLKN_Compute_Release.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2;
    sVLKN_Compute_Release.pNext = nullptr;
    sVLKN_Compute_Release.srcStageMask  = VK_PIPELINE_STAGE_2_COMPUTE_SHADER_BIT;
    sVLKN_Compute_Release.srcAccessMask = VK_ACCESS_2_SHADER_STORAGE_WRITE_BIT;
    sVLKN_Compute_Release.dstStageMask  = 0;
    sVLKN_Compute_Release.dstAccessMask = 0;
    sVLKN_Compute_Release.oldLayout = VK_IMAGE_LAYOUT_GENERAL;
    sVLKN_Compute_Release.newLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
    sVLKN_Compute_Release.srcQueueFamilyIndex = (TgUINT_E32)psVLKN_CXT_EXEC->m_auiVLKN_Queue_Family_Index[ETgKN_GPU_EXT_COMMAND_COMPUTE];
    sVLKN_Compute_Release.dstQueueFamilyIndex = (TgUINT_E32)psVLKN_CXT_EXEC->m_auiVLKN_Queue_Family_Index[ETgKN_GPU_EXT_COMMAND_GRAPHICS];
    sVLKN_Compute_Release.image = psRender_Target->m_ahVLKN_Colour_Image[0];
    sVLKN_Compute_Release.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    sVLKN_Compute_Release.subresourceRange.baseMipLevel = 0;
    sVLKN_Compute_Release.subresourceRange.levelCount = 1;
    sVLKN_Compute_Release.subresourceRange.baseArrayLayer = 0;
    sVLKN_Compute_Release.subresourceRange.layerCount = 1;

    /* Release Queue Family Ownership of the Images */
    {
        VkDependencyInfo                            sVLKN_Dependency_Info = { 
                                                        .sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO,
                                                        .imageMemoryBarrierCount = 1,
                                                        .pImageMemoryBarriers = &sVLKN_Compute_Release,
                                                    };

        vkCmdPipelineBarrier2( uCMD_Compute.psVLKN->m_hVLKN_Command_Buffer, &sVLKN_Dependency_Info );
    }

    /* ACQUIRE ON COMPUTE QUEUE */
    tgMM_Set_U08_0x00(&sVLKN_Graphics_Acquire, sizeof(sVLKN_Graphics_Acquire));
    sVLKN_Graphics_Acquire.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2;
    sVLKN_Graphics_Acquire.pNext = nullptr;
    sVLKN_Graphics_Acquire.srcStageMask  = 0;
    sVLKN_Graphics_Acquire.srcAccessMask = 0;
    sVLKN_Graphics_Acquire.dstStageMask  = VK_PIPELINE_STAGE_2_BOTTOM_OF_PIPE_BIT;
    sVLKN_Graphics_Acquire.dstAccessMask = 0;
    sVLKN_Graphics_Acquire.oldLayout = VK_IMAGE_LAYOUT_GENERAL;
    sVLKN_Graphics_Acquire.newLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
    sVLKN_Graphics_Acquire.srcQueueFamilyIndex = (TgUINT_E32)psVLKN_CXT_EXEC->m_auiVLKN_Queue_Family_Index[ETgKN_GPU_EXT_COMMAND_COMPUTE];
    sVLKN_Graphics_Acquire.dstQueueFamilyIndex = (TgUINT_E32)psVLKN_CXT_EXEC->m_auiVLKN_Queue_Family_Index[ETgKN_GPU_EXT_COMMAND_GRAPHICS];
    sVLKN_Graphics_Acquire.image = psRender_Target->m_ahVLKN_Colour_Image[0];
    sVLKN_Graphics_Acquire.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    sVLKN_Graphics_Acquire.subresourceRange.baseMipLevel = 0;
    sVLKN_Graphics_Acquire.subresourceRange.levelCount = 1;
    sVLKN_Graphics_Acquire.subresourceRange.baseArrayLayer = 0;
    sVLKN_Graphics_Acquire.subresourceRange.layerCount = 1;

    /* Transition source and destination to compute-appropriate layouts */
    {
        VkDependencyInfo                            sVLKN_Dependency_Info = { 
                                                        .sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO,
                                                        .imageMemoryBarrierCount = 1,
                                                        .pImageMemoryBarriers = &sVLKN_Graphics_Acquire,
                                                    };
        vkCmdPipelineBarrier2( uCMD_Graphics.psVLKN->m_hVLKN_Command_Buffer, &sVLKN_Dependency_Info );
    }

    return (KTgS_OK);
}


/* ---- tgKN_GPU_VLKN__CMD__Apply_Colour_Correction_Compute ----------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_VLKN__CMD__Apply_Colour_Correction_Compute(
    STg2_KN_GPU_CMD_PC                          psCMD,
    STg2_KN_GPU_VLKN_Render_Target_P            psRender_Target_Src,
    STg2_KN_GPU_VLKN_Render_Target_P            psRender_Target_Dest )
{
    UTg2_KN_GPU_CMD_C                           uCMD = { .ps = psCMD };
    TgRSIZE_C                                   uiEXEC = (uCMD.psVLKN->m_sBase.m_tiCXT_WORK.m_uiI >> 16) & 0xFFFF;
    STg2_KN_GPU_VLKN_CXT_EXEC_PC                psVLKN_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + uiEXEC;

    VkPipeline                                  hVLKN_Compute_Pipeline;
    VkPipelineLayout                            hVLKN_Pipeline_Layout;

    TgUINT_E32                                  uiWorkgroup_X;
    TgUINT_E32                                  uiWorkgroup_Y;

    struct STg_Push_Constants_Colour_Correction
    {
        TgUINT_E64                                  uiSource_Image_View;
        TgUINT_E64                                  uiDestination_Image_View;
        TgUINT_E32                                  bHDR_Enabled;
        TgFLOAT32                                   fGamma;
        TgFLOAT32                                   fExposure;
        TgUINT_E32                                  enTone_Map_Type;
    }                                           sPushConstants;

    /* Validate parameters */
    TgPARAM_CHECK_KN_GPU_CMD(psCMD);
    TgPARAM_CHECK(psRender_Target_Src);
    TgPARAM_CHECK(psRender_Target_Dest);

    /* Get the compute shader pipeline and layout */
    hVLKN_Compute_Pipeline = psRender_Target_Dest->m_ahVLKN_Pipeline_Compute[ETgKN_GPU_COMPUTE_PIPELINE_FOR_RENDERING_COLOUR_CORRECTION];
    hVLKN_Pipeline_Layout = psVLKN_CXT_EXEC->m_ahVLKN_Pipeline_Layout[ETgKN_GPU_PIPELINE_LAYOUT__POST_PROCESS_COMPUTE];

    if (VK_NULL_HANDLE == hVLKN_Compute_Pipeline)
    {
        TgERROR_MSGF(0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Colour correction compute pipeline not initialized");
        TgDEBUG_BREAK_AND_RETURN(KTgE_FAIL);
    }


    /* DO THE ACTUAL COMPUTE WORK */

    /* Bind compute pipeline */
    vkCmdBindPipeline(
        uCMD.psVLKN->m_hVLKN_Command_Buffer,
        VK_PIPELINE_BIND_POINT_COMPUTE,
        hVLKN_Compute_Pipeline
    );

    /* Bind the render descriptor set (Set 0 with OutputDESC) */
    TgVERIFY(uCMD.psVLKN->m_uiUBO_Render_DESC_Offset != KTgMAX_U32);

    vkCmdBindDescriptorSets(
        uCMD.psVLKN->m_hVLKN_Command_Buffer,
        VK_PIPELINE_BIND_POINT_COMPUTE,
        hVLKN_Pipeline_Layout,
        0u, /* Starting set index (Set 0) */
        1u, /* Number of descriptor sets to bind (Set 0: OutputDESC, Set 1: bindless image array) */
        &psVLKN_CXT_EXEC->m_hVLKN_Descriptor_Set_Render_DESC,
        1u, &uCMD.psVLKN->m_uiUBO_Render_DESC_Offset
    );

    /* Push image indices as push constants to compute shader for dynamic indexing into bindless image array */
    /* The shader uses these indices to access the image_array[] bindless array */
    sPushConstants.uiSource_Image_View = psRender_Target_Src->m_auiColour_Descriptor_Set_Index[0];
    sPushConstants.uiDestination_Image_View = psRender_Target_Dest->m_auiColour_Descriptor_Set_Index[0];
    sPushConstants.bHDR_Enabled = true;
    sPushConstants.fGamma = 2.2F;
    sPushConstants.fExposure = 1.0F;
    sPushConstants.enTone_Map_Type = 2;

    vkCmdPushConstants(
        uCMD.psVLKN->m_hVLKN_Command_Buffer,
        hVLKN_Pipeline_Layout,
        VK_SHADER_STAGE_COMPUTE_BIT,
        0u, /* Offset */
        sizeof(sPushConstants),
        &sPushConstants
    );

    /* Calculate workgroup dimensions (compute shader uses 16x16 local size) */
    uiWorkgroup_X = ((TgUINT_E32)psRender_Target_Dest->m_sRender_Target_DESC.m_uiWidth + 15) / 16;
    uiWorkgroup_Y = ((TgUINT_E32)psRender_Target_Dest->m_sRender_Target_DESC.m_uiHeight + 15) / 16;

    /* Validation: Ensure workgroup dispatch is within device limits */
    if (uiWorkgroup_X == 0 || uiWorkgroup_Y == 0)
    {
        TgERROR_MSGF(0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Invalid workgroup dimensions: %d x %d", uiWorkgroup_X, uiWorkgroup_Y);
        return (KTgE_FAIL);
    }

    /* Dispatch compute shader */
    vkCmdDispatch(
        uCMD.psVLKN->m_hVLKN_Command_Buffer,
        uiWorkgroup_X,
        uiWorkgroup_Y,
        1
    );

    return (KTgS_OK);
}


/* ---- tgKN_GPU_VLKN__CMD__Render_Target_Barrier -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_VLKN__CMD__Render_Target_Barrier(
    STg2_KN_GPU_VLKN_CMD_PC                     psVLKN_CMD,
    STg2_KN_GPU_VLKN_Render_Target_PC           psRender_Target,
    VkPipelineStageFlags2                       destStageMask,
    VkAccessFlags2                              destAccessMask )
{
    VkImageMemoryBarrier2                       asVLKN_Image_Barrier[KTgKN_GPU_MAX_SIMULTANEOUS_TARGET_COUNT];
    VkDependencyInfo                            sVLKN_Dependency_Info;
    TgRSIZE                                     uiIndex;

    for (uiIndex = 0; uiIndex < psRender_Target->m_sRender_Target_DESC.m_nuiColour_Target; ++uiIndex)
    {
        /* Transition render target to general layout for read/write access */
        tgMM_Set_U08_0x00(&asVLKN_Image_Barrier[uiIndex], sizeof(asVLKN_Image_Barrier[uiIndex]));
        asVLKN_Image_Barrier[uiIndex].sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2;
        asVLKN_Image_Barrier[uiIndex].pNext = nullptr;
        asVLKN_Image_Barrier[uiIndex].srcStageMask  = VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT;
        asVLKN_Image_Barrier[uiIndex].srcAccessMask = 0;
        asVLKN_Image_Barrier[uiIndex].dstStageMask  = destStageMask;
        asVLKN_Image_Barrier[uiIndex].dstAccessMask = destAccessMask;
        asVLKN_Image_Barrier[uiIndex].oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        asVLKN_Image_Barrier[uiIndex].newLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
        asVLKN_Image_Barrier[uiIndex].image = psRender_Target->m_ahVLKN_Colour_Image[uiIndex];
        asVLKN_Image_Barrier[uiIndex].subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        asVLKN_Image_Barrier[uiIndex].subresourceRange.baseMipLevel = 0;
        asVLKN_Image_Barrier[uiIndex].subresourceRange.levelCount = 1;
        asVLKN_Image_Barrier[uiIndex].subresourceRange.baseArrayLayer = 0;
        asVLKN_Image_Barrier[uiIndex].subresourceRange.layerCount = 1;
    }

    tgMM_Set_U08_0x00(&sVLKN_Dependency_Info, sizeof(sVLKN_Dependency_Info));
    sVLKN_Dependency_Info.sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO;
    sVLKN_Dependency_Info.imageMemoryBarrierCount = (TgUINT_E32)psRender_Target->m_sRender_Target_DESC.m_nuiColour_Target;
    sVLKN_Dependency_Info.pImageMemoryBarriers = asVLKN_Image_Barrier;

    vkCmdPipelineBarrier2(psVLKN_CMD->m_hVLKN_Command_Buffer, &sVLKN_Dependency_Info );

    return (KTgS_OK);
}



/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgKN_GPU_RENDER_TARGET_ID tgKN_GPU_EXT__Execute__Create_Render_Target( TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC, STg2_KN_GPU_Render_Target_DESC_CPC psRender_Target_DESC )
{
    STg2_KN_GPU_VLKN_CXT_EXEC_PC        psVLKN_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + tiCXT_EXEC.m_uiI;
    STg2_KN_GPU_VLKN_Render_Target_P    psVLKN_Render_Target;
    TgRESULT                            iResult;
    TgRSIZE                             uiIndex;

    TgPARAM_CHECK(nullptr != psRender_Target_DESC);
    TgPARAM_CHECK(psRender_Target_DESC->m_uiWidth > 0 && psRender_Target_DESC->m_uiHeight > 0);
    TgPARAM_CHECK(psRender_Target_DESC->m_nuiColour_Target <= TgARRAY_COUNT(psRender_Target_DESC->m_aenColour_Format));

    /* Find first available render target slot */
    psVLKN_Render_Target = nullptr;
    for (uiIndex = 0; uiIndex < TgARRAY_COUNT(psVLKN_CXT_EXEC->m_asRender_Target); ++uiIndex)
    {
        TgKN_GPU_RENDER_TARGET_ID           tiRender_Target;

        if (!tgKN_GPU_RENDER_TARGET_ID_Fetch_And_Is_Valid( &tiRender_Target, &psVLKN_CXT_EXEC->m_asRender_Target[uiIndex].m_tiRender_Target_S ))
        {
            psVLKN_Render_Target = &psVLKN_CXT_EXEC->m_asRender_Target[uiIndex];
            break;
        }
    }

    if (nullptr == psVLKN_Render_Target)
    {
        TgERROR_MSG(0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to allocate render target");
        return (KTgKN_GPU_RENDER_TARGET_ID__INVALID);
    }

    tgMM_Set_U08_0x00( psVLKN_Render_Target, sizeof( *psVLKN_Render_Target ) );

    psVLKN_Render_Target->m_sRender_Target_DESC = *psRender_Target_DESC;

    iResult = tgKN_GPU_VLKN__Render_Target__Create_Resources( psVLKN_Render_Target, psVLKN_CXT_EXEC->m_hVLKN_Device, psVLKN_CXT_EXEC );
    if (TgFAILED(iResult))
    {
        TgERROR_MSG(0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create resources for render target (Create Resources)");
        tgKN_GPU_VLKN__Render_Target__Free( psVLKN_Render_Target, psVLKN_CXT_EXEC->m_hVLKN_Device );
        return (KTgKN_GPU_RENDER_TARGET_ID__INVALID);
    }

    iResult = tgKN_GPU_VLKN__Render_Target__Init( psVLKN_Render_Target, psVLKN_CXT_EXEC->m_hVLKN_Device, psVLKN_CXT_EXEC );
    if (TgFAILED(iResult))
    {
        TgERROR_MSG(0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to initialize render target");
        tgKN_GPU_VLKN__Render_Target__Free( psVLKN_Render_Target, psVLKN_CXT_EXEC->m_hVLKN_Device );
        return (KTgKN_GPU_RENDER_TARGET_ID__INVALID);
    }

#if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)
    {
        STg2_KN_GPU_DBG_VLKN_CXT_EXEC_PC    psDBG_VLKN_CXT_EXEC = g_asKN_GPU_DBG_EXT_CXT_EXEC + tiCXT_EXEC.m_uiI;
        STg2_KN_GPU_DBG_VLKN_Render_Target_P psDBG_VLKN_Render_Target;

        TgPARAM_CHECK_INDEX(uiIndex, psDBG_VLKN_CXT_EXEC->m_asRender_Target );

        psDBG_VLKN_Render_Target = psDBG_VLKN_CXT_EXEC->m_asRender_Target + uiIndex;

        TgVERIFY(VK_NULL_HANDLE == psDBG_VLKN_Render_Target->m_ahVLKN_Pipeline_Graphics[0]);

        if (TgFAILED( tgKN_GPU_DBG_VLKN__Render_Target__Init( psDBG_VLKN_Render_Target, psVLKN_Render_Target, psVLKN_CXT_EXEC->m_hVLKN_Device, tiCXT_EXEC.m_uiI ) ))
        {
            TgERROR_MSG(0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to initialize render target (debug)");
            tgKN_GPU_VLKN__Render_Target__Free(psVLKN_Render_Target, psVLKN_CXT_EXEC->m_hVLKN_Device);
            return (KTgKN_GPU_RENDER_TARGET_ID__INVALID);
        }
        TgVERIFY(VK_NULL_HANDLE != psDBG_VLKN_Render_Target->m_ahVLKN_Pipeline_Graphics[0]);
    }
/*# defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
#endif

    return (tgKN_GPU_RENDER_TARGET_ID_Query_Unsafe(&psVLKN_Render_Target->m_tiRender_Target_S));
}


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_GPU_VLKN__Render_Target__Init --------------------------------------------------------------------------------------------------------------------------------------- */
/* #NOTE: Initialize generated/derived data for the render target. Note that we do not clear the data structure as it is expected to be cleared as a member of a parent.           */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_VLKN__Render_Target__Init( STg2_KN_GPU_VLKN_Render_Target_PC psRender_Target, VkDevice_C hVLKN_Device, STg2_KN_GPU_VLKN_CXT_EXEC_PC psVLKN_CXT_EXEC )
{
    TgSINT_PTR_DIFF                    iIndex = psRender_Target - psVLKN_CXT_EXEC->m_asRender_Target;

    TgPARAM_CHECK(nullptr != psRender_Target);

    if (iIndex < 0 || iIndex >= (TgSINT_PTR_DIFF)TgARRAY_COUNT(psVLKN_CXT_EXEC->m_asRender_Target))
    {
        /* We have a special case of a shadow render target in the swap chain context to minimize code duplication. */
        tgKN_GPU_RENDER_TARGET_ID_Init( &psRender_Target->m_tiRender_Target_S, KTgMAX_U32 );
    }
    else
    {
        tgKN_GPU_RENDER_TARGET_ID_Init( &psRender_Target->m_tiRender_Target_S, (TgUINT_E32)(iIndex) );
    }

    /* Create the graphics pipelines for this render target if needed */
    if (TgFAILED(tgKN_GPU_VLKN__Render_Target__Create_Pipelines(psRender_Target, hVLKN_Device, psVLKN_CXT_EXEC)))
    {
        TgERROR_MSG(0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create graphics pipelines for render target");
        return (KTgE_FAIL);
    }

    return (KTgS_OK);
}


/* ---- tgKN_GPU_VLKN__Render_Target__Create_Resources --------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_VLKN__Render_Target__Create_Resources( STg2_KN_GPU_VLKN_Render_Target_PC psRender_Target, VkDevice_C hVLKN_Device, STg2_KN_GPU_VLKN_CXT_EXEC_PC psVLKN_CXT_EXEC )
{
    VkImageCreateInfo                   sVLKN_Image_CI;
    VkMemoryRequirements                sVLKN_Memory_Requirements;
    VkMemoryAllocateInfo                sVLKN_Memory_AI;
    VkImageViewCreateInfo               sVLKN_Image_View_CI;
    TgRSIZE                             uiIndex, uiRT_IMG;
    VkResult                            iVLKN_Result;

    TgPARAM_CHECK(nullptr != psRender_Target);
    TgPARAM_CHECK(VK_NULL_HANDLE != hVLKN_Device);
    TgPARAM_CHECK(nullptr != psVLKN_CXT_EXEC);

    /* Create colour attachments */
    for (uiIndex = 0; uiIndex < psRender_Target->m_sRender_Target_DESC.m_nuiColour_Target; ++uiIndex)
    {
        /* Image and Image Memory are created/allocator through vkCreateSwapchainKHR in the case of the swap chain. */
        if (VK_NULL_HANDLE == psRender_Target->m_ahVLKN_Colour_Image[uiIndex])
        {
            tgMM_Set_U08_0x00( &sVLKN_Image_CI, sizeof(sVLKN_Image_CI) );
            sVLKN_Image_CI.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
            sVLKN_Image_CI.pNext = nullptr;
            sVLKN_Image_CI.flags = 0;
            sVLKN_Image_CI.imageType = VK_IMAGE_TYPE_2D;
            sVLKN_Image_CI.format = (VkFormat)psRender_Target->m_sRender_Target_DESC.m_aenColour_Format[uiIndex];
            sVLKN_Image_CI.extent.width = (TgUINT_E32)psRender_Target->m_sRender_Target_DESC.m_uiWidth;
            sVLKN_Image_CI.extent.height = (TgUINT_E32)psRender_Target->m_sRender_Target_DESC.m_uiHeight;
            sVLKN_Image_CI.extent.depth = 1;
            sVLKN_Image_CI.mipLevels = 1;
            sVLKN_Image_CI.arrayLayers = 1;
            sVLKN_Image_CI.samples = VK_SAMPLE_COUNT_1_BIT;
            sVLKN_Image_CI.tiling = VK_IMAGE_TILING_OPTIMAL;
            sVLKN_Image_CI.usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_STORAGE_BIT;
            sVLKN_Image_CI.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
            sVLKN_Image_CI.queueFamilyIndexCount = 0;
            sVLKN_Image_CI.pQueueFamilyIndices = nullptr;
            sVLKN_Image_CI.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

            iVLKN_Result = vkCreateImage( hVLKN_Device, &sVLKN_Image_CI, g_psKN_GPU_VLKN_Allocator, &psRender_Target->m_ahVLKN_Colour_Image[uiIndex] );
            if (VK_SUCCESS != iVLKN_Result)
            {
                TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create colour image [%d]", uiIndex );
                return (KTgE_FAIL);
            }

            vkGetImageMemoryRequirements( hVLKN_Device, psRender_Target->m_ahVLKN_Colour_Image[uiIndex], &sVLKN_Memory_Requirements );

            tgMM_Set_U08_0x00( &sVLKN_Memory_AI, sizeof(sVLKN_Memory_AI) );
            sVLKN_Memory_AI.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
            sVLKN_Memory_AI.pNext = nullptr;
            sVLKN_Memory_AI.allocationSize = sVLKN_Memory_Requirements.size;

            if (TgFAILED(tgKN_GPU_VLKN_Find_Memory_Type_Index( &sVLKN_Memory_AI.memoryTypeIndex, psVLKN_CXT_EXEC->m_hVLKN_Physical_Device, sVLKN_Memory_Requirements.memoryTypeBits,
                                                            VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT )))
            {
                TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to find memory type index for colour image memory [%d]", uiIndex );
                return (KTgE_FAIL);
            }

            iVLKN_Result = vkAllocateMemory( hVLKN_Device, &sVLKN_Memory_AI, g_psKN_GPU_VLKN_Allocator, &psRender_Target->m_ahVLKN_Colour_Memory[uiIndex] );
            if (VK_SUCCESS != iVLKN_Result)
            {
                TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to allocate colour image memory [%d]", uiIndex );
                return (KTgE_FAIL);
            }

            iVLKN_Result = vkBindImageMemory( hVLKN_Device, psRender_Target->m_ahVLKN_Colour_Image[uiIndex], psRender_Target->m_ahVLKN_Colour_Memory[uiIndex], 0 );
            if (VK_SUCCESS != iVLKN_Result)
            {
                TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to bind colour image memory [%d]", uiIndex );
                return (KTgE_FAIL);
            }
        }

        tgMM_Set_U08_0x00( &sVLKN_Image_View_CI, sizeof(sVLKN_Image_View_CI) );
        sVLKN_Image_View_CI.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        sVLKN_Image_View_CI.pNext = nullptr;
        sVLKN_Image_View_CI.flags = 0;
        sVLKN_Image_View_CI.image = psRender_Target->m_ahVLKN_Colour_Image[uiIndex];
        sVLKN_Image_View_CI.viewType = VK_IMAGE_VIEW_TYPE_2D;
        sVLKN_Image_View_CI.format = (VkFormat)psRender_Target->m_sRender_Target_DESC.m_aenColour_Format[uiIndex];
        sVLKN_Image_View_CI.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        sVLKN_Image_View_CI.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        sVLKN_Image_View_CI.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        sVLKN_Image_View_CI.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
        sVLKN_Image_View_CI.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        sVLKN_Image_View_CI.subresourceRange.baseMipLevel = 0;
        sVLKN_Image_View_CI.subresourceRange.levelCount = 1;
        sVLKN_Image_View_CI.subresourceRange.baseArrayLayer = 0;
        sVLKN_Image_View_CI.subresourceRange.layerCount = 1;

        iVLKN_Result = vkCreateImageView( hVLKN_Device, &sVLKN_Image_View_CI, g_psKN_GPU_VLKN_Allocator, &psRender_Target->m_ahVLKN_Colour_Image_View[uiIndex] );
        if (VK_SUCCESS != iVLKN_Result)
        {
            TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create colour image view [%d]", uiIndex );
            return (KTgE_FAIL);
        }

        uiRT_IMG = TgSTD_ATOMIC(fetch_add)( &psVLKN_CXT_EXEC->m_xnuiRT_IMG, 1u );
        psRender_Target->m_auiColour_Descriptor_Set_Index[uiIndex] = uiRT_IMG;
        psVLKN_CXT_EXEC->m_asVLKN_DS_Info_RT_IMG[uiRT_IMG].sampler = VK_NULL_HANDLE;
        psVLKN_CXT_EXEC->m_asVLKN_DS_Info_RT_IMG[uiRT_IMG].imageView = psRender_Target->m_ahVLKN_Colour_Image_View[uiIndex];
        psVLKN_CXT_EXEC->m_asVLKN_DS_Info_RT_IMG[uiRT_IMG].imageLayout = VK_IMAGE_LAYOUT_GENERAL;
    }

    /* Create depth-stencil attachment if present */
    if ((VK_FORMAT_UNDEFINED != (VkFormat)psRender_Target->m_sRender_Target_DESC.m_enDepth_Stencil_Format) && (VK_NULL_HANDLE == psRender_Target->m_hVLKN_Depth_Stencil_Image))
    {
        tgMM_Set_U08_0x00( &sVLKN_Image_CI, sizeof(sVLKN_Image_CI) );
        sVLKN_Image_CI.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        sVLKN_Image_CI.pNext = nullptr;
        sVLKN_Image_CI.flags = 0;
        sVLKN_Image_CI.imageType = VK_IMAGE_TYPE_2D;
        sVLKN_Image_CI.format = (VkFormat)psRender_Target->m_sRender_Target_DESC.m_enDepth_Stencil_Format;
        sVLKN_Image_CI.extent.width = (TgUINT_E32)psRender_Target->m_sRender_Target_DESC.m_uiWidth;
        sVLKN_Image_CI.extent.height = (TgUINT_E32)psRender_Target->m_sRender_Target_DESC.m_uiHeight;
        sVLKN_Image_CI.extent.depth = 1;
        sVLKN_Image_CI.mipLevels = 1;
        sVLKN_Image_CI.arrayLayers = 1;
        sVLKN_Image_CI.samples = (VkSampleCountFlagBits)(tgCM_MAX_U32(1u,psRender_Target->m_nuiMSAA_Sample));
        sVLKN_Image_CI.tiling = VK_IMAGE_TILING_OPTIMAL;
        sVLKN_Image_CI.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
        sVLKN_Image_CI.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        sVLKN_Image_CI.queueFamilyIndexCount = 0;
        sVLKN_Image_CI.pQueueFamilyIndices = nullptr;
        sVLKN_Image_CI.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

        iVLKN_Result = vkCreateImage( hVLKN_Device, &sVLKN_Image_CI, g_psKN_GPU_VLKN_Allocator, &psRender_Target->m_hVLKN_Depth_Stencil_Image );
        if (VK_SUCCESS != iVLKN_Result)
        {
            TgERROR_MSG( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create depth-stencil image" );
            return (KTgE_FAIL);
        }

        vkGetImageMemoryRequirements( hVLKN_Device, psRender_Target->m_hVLKN_Depth_Stencil_Image, &sVLKN_Memory_Requirements );

        tgMM_Set_U08_0x00( &sVLKN_Memory_AI, sizeof(sVLKN_Memory_AI) );
        sVLKN_Memory_AI.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        sVLKN_Memory_AI.pNext = nullptr;
        sVLKN_Memory_AI.allocationSize = sVLKN_Memory_Requirements.size;

        if (TgFAILED(tgKN_GPU_VLKN_Find_Memory_Type_Index( &sVLKN_Memory_AI.memoryTypeIndex, psVLKN_CXT_EXEC->m_hVLKN_Physical_Device, sVLKN_Memory_Requirements.memoryTypeBits,
                                                           VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT )))
        {
            TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to find memory type index for colour image memory [%d]", uiIndex );
            return (KTgE_FAIL);
        }

        iVLKN_Result = vkAllocateMemory( hVLKN_Device, &sVLKN_Memory_AI, g_psKN_GPU_VLKN_Allocator, &psRender_Target->m_hVLKN_Depth_Stencil_Memory );
        if (VK_SUCCESS != iVLKN_Result)
        {
            TgERROR_MSG( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to allocate depth-stencil image memory" );
            return (KTgE_FAIL);
        }

        iVLKN_Result = vkBindImageMemory( hVLKN_Device, psRender_Target->m_hVLKN_Depth_Stencil_Image, psRender_Target->m_hVLKN_Depth_Stencil_Memory, 0 );
        if (VK_SUCCESS != iVLKN_Result)
        {
            TgERROR_MSG( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to bind depth-stencil image memory" );
            return (KTgE_FAIL);
        }

        tgMM_Set_U08_0x00( &sVLKN_Image_View_CI, sizeof(sVLKN_Image_View_CI) );
        sVLKN_Image_View_CI.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        sVLKN_Image_View_CI.pNext = nullptr;
        sVLKN_Image_View_CI.flags = 0;
        sVLKN_Image_View_CI.image = psRender_Target->m_hVLKN_Depth_Stencil_Image;
        sVLKN_Image_View_CI.viewType = VK_IMAGE_VIEW_TYPE_2D;
        sVLKN_Image_View_CI.format = (VkFormat)psRender_Target->m_sRender_Target_DESC.m_enDepth_Stencil_Format;
        sVLKN_Image_View_CI.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
        if (psRender_Target->m_bStencil_Valid)
        {
            sVLKN_Image_View_CI.subresourceRange.aspectMask |= VK_IMAGE_ASPECT_STENCIL_BIT;
        }
        sVLKN_Image_View_CI.subresourceRange.baseMipLevel = 0;
        sVLKN_Image_View_CI.subresourceRange.levelCount = 1;
        sVLKN_Image_View_CI.subresourceRange.baseArrayLayer = 0;
        sVLKN_Image_View_CI.subresourceRange.layerCount = 1;

        iVLKN_Result = vkCreateImageView( hVLKN_Device, &sVLKN_Image_View_CI, g_psKN_GPU_VLKN_Allocator, &psRender_Target->m_hVLKN_Depth_Stencil_View );
        if (VK_SUCCESS != iVLKN_Result)
        {
            TgERROR_MSG( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create depth-stencil image view" );
            return (KTgE_FAIL);
        }
    }

    tgKN_GPU_VLKN__Execute__Init__Update_Default_Descriptor_Sets( hVLKN_Device, psVLKN_CXT_EXEC->m_tiCXT_EXEC.m_uiI );

    return (KTgS_OK);
}


/* ---- tgKN_GPU_VLKN__Render_Target__Destroy_Resources -------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_VLKN__Render_Target__Destroy_Resources( STg2_KN_GPU_VLKN_Render_Target_PC psRender_Target, VkDevice_C hVLKN_Device )
{
    TgRSIZE                             uiIndex;

    TgVERIFY(VK_NULL_HANDLE != hVLKN_Device);
    TgVERIFY(nullptr != psRender_Target);

    /* Destroy image views */

    for (uiIndex = 0; uiIndex < TgARRAY_COUNT(psRender_Target->m_ahVLKN_Colour_Image_View); ++uiIndex)
    {
        if (VK_NULL_HANDLE != psRender_Target->m_ahVLKN_Colour_Image_View[uiIndex])
        {
            vkDestroyImageView(hVLKN_Device, psRender_Target->m_ahVLKN_Colour_Image_View[uiIndex], g_psKN_GPU_VLKN_Allocator);
            psRender_Target->m_ahVLKN_Colour_Image_View[uiIndex] = VK_NULL_HANDLE;
        }
        if (VK_NULL_HANDLE != psRender_Target->m_ahVLKN_Colour_Memory[uiIndex])
        {
            vkFreeMemory(hVLKN_Device, psRender_Target->m_ahVLKN_Colour_Memory[uiIndex], g_psKN_GPU_VLKN_Allocator);
            psRender_Target->m_ahVLKN_Colour_Memory[uiIndex] = VK_NULL_HANDLE;
        }
        if (VK_NULL_HANDLE != psRender_Target->m_ahVLKN_Colour_Image[uiIndex])
        {
            vkDestroyImage(hVLKN_Device, psRender_Target->m_ahVLKN_Colour_Image[uiIndex], g_psKN_GPU_VLKN_Allocator);
            psRender_Target->m_ahVLKN_Colour_Image[uiIndex] = VK_NULL_HANDLE;
        }
    }

    if (VK_NULL_HANDLE != psRender_Target->m_hVLKN_Depth_Stencil_View)
    {
        vkDestroyImageView(hVLKN_Device, psRender_Target->m_hVLKN_Depth_Stencil_View, g_psKN_GPU_VLKN_Allocator);
        psRender_Target->m_hVLKN_Depth_Stencil_View = VK_NULL_HANDLE;
    }
    if (VK_NULL_HANDLE != psRender_Target->m_hVLKN_Depth_Stencil_Memory)
    {
        vkFreeMemory(hVLKN_Device, psRender_Target->m_hVLKN_Depth_Stencil_Memory, g_psKN_GPU_VLKN_Allocator);
        psRender_Target->m_hVLKN_Depth_Stencil_Memory = VK_NULL_HANDLE;
    }
    if (VK_NULL_HANDLE != psRender_Target->m_hVLKN_Depth_Stencil_Image)
    {
        vkDestroyImage(hVLKN_Device, psRender_Target->m_hVLKN_Depth_Stencil_Image, g_psKN_GPU_VLKN_Allocator);
        psRender_Target->m_hVLKN_Depth_Stencil_Image = VK_NULL_HANDLE;
    }
}


/* ---- tgKN_GPU_VLKN__Render_Target__Free --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_VLKN__Render_Target__Free( STg2_KN_GPU_VLKN_Render_Target_PC psRender_Target, VkDevice_C hVLKN_Device )
{
    TgRSIZE                             uiIndex;

    TgVERIFY(VK_NULL_HANDLE != hVLKN_Device);
    TgVERIFY(nullptr != psRender_Target);

    tgKN_GPU_VLKN__Render_Target__Destroy_Resources( psRender_Target, hVLKN_Device );

    /* With dynamic rendering, no render pass or framebuffer objects to destroy */

    for (uiIndex = 0; uiIndex < TgARRAY_COUNT(psRender_Target->m_ahVLKN_Pipeline_Graphics); ++uiIndex)
    {
        if (VK_NULL_HANDLE == psRender_Target->m_ahVLKN_Pipeline_Graphics[uiIndex])
        {
            continue;
        }
        vkDestroyPipeline(hVLKN_Device, psRender_Target->m_ahVLKN_Pipeline_Graphics[uiIndex], g_psKN_GPU_VLKN_Allocator );
        psRender_Target->m_ahVLKN_Pipeline_Graphics[uiIndex] = VK_NULL_HANDLE;
    }

    for (uiIndex = 0; uiIndex < TgARRAY_COUNT(psRender_Target->m_ahVLKN_Pipeline_Compute); ++uiIndex)
    {
        if (VK_NULL_HANDLE == psRender_Target->m_ahVLKN_Pipeline_Compute[uiIndex])
        {
            continue;
        }
        vkDestroyPipeline(hVLKN_Device, psRender_Target->m_ahVLKN_Pipeline_Compute[uiIndex], g_psKN_GPU_VLKN_Allocator );
        psRender_Target->m_ahVLKN_Pipeline_Compute[uiIndex] = VK_NULL_HANDLE;
    }
}


/* ---- tgKN_GPU_VLKN__Render_Target__Get_Render_Target -------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_VLKN__Render_Target__Get_Render_Target( STg2_KN_GPU_VLKN_Render_Target_PP ppsRender_Target, TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP,
                                                          TgKN_GPU_RENDER_TARGET_ID_C tiRender_Target, TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC )
{
    TgPARAM_CHECK( nullptr != ppsRender_Target );

    /* Validate that the render target is valid/current. */
    if (tiRender_Target.m_uiKI != KTgKN_GPU_RENDER_TARGET_ID__INVALID.m_uiKI)
    {
        STg2_KN_GPU_VLKN_CXT_EXEC_PC        psVLKN_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + tiCXT_EXEC.m_uiI;
        STg2_KN_GPU_VLKN_Render_Target_P    psRender_Target;

        TgPARAM_CHECK_INDEX( tiRender_Target.m_uiI, psVLKN_CXT_EXEC->m_asRender_Target );
        TgPARAM_CHECK_INDEX( tiCXT_EXEC.m_uiI, g_asKN_GPU_CXT_EXEC );
        TgPARAM_CHECK( tgKN_GPU_CXT_EXEC_ID_Is_Equal( &(g_asKN_GPU_CXT_EXEC[tiCXT_EXEC.m_uiI].m_tiCXT_EXEC_S), tiCXT_EXEC ) );

        psRender_Target = psVLKN_CXT_EXEC->m_asRender_Target + tiRender_Target.m_uiI;

        if (!tgKN_GPU_RENDER_TARGET_ID_Is_Equal( &psRender_Target->m_tiRender_Target_S, tiRender_Target ))
        {
            TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Render Target ID invalid" );
            return (KTgE_FAIL);
        }

        *ppsRender_Target = psRender_Target;
        return (KTgS_OK);
    }
    else if (KTgKN_GPU_CXT_SWAP_ID__INVALID.m_uiKI != tiCXT_SWAP.m_uiKI)
    {
        STg2_KN_GPU_VLKN_CXT_SWAP_PC        psVLKN_CXT_SWAP = g_asKN_GPU_EXT_CXT_SWAP + tiCXT_SWAP.m_uiI;

        TgPARAM_CHECK_INDEX( tiCXT_SWAP.m_uiI, g_asKN_GPU_CXT_SWAP );
        TgPARAM_CHECK( tgKN_GPU_CXT_SWAP_ID_Is_Equal( &(g_asKN_GPU_CXT_SWAP[tiCXT_SWAP.m_uiI].m_tiCXT_SWAP_S), tiCXT_SWAP ) );

        /* Use the swap context's render target index */
        if (psVLKN_CXT_SWAP->m_uiCurrent_Image_Index != KTgMAX_U32)
        {
            *ppsRender_Target = psVLKN_CXT_SWAP->m_asBack_Buffer__Render_Target + psVLKN_CXT_SWAP->m_uiCurrent_Image_Index;
            return (KTgS_OK);
        }
        return (KTgE_FAIL);
    }

    return (KTgE_FAIL);
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_GPU_VLKN__Render_Target__Create_Pipelines --------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT tgKN_GPU_VLKN__Render_Target__Create_Pipelines(
    STg2_KN_GPU_VLKN_Render_Target_PC           psRender_Target,
    VkDevice_C                                  hVLKN_Device,
    STg2_KN_GPU_VLKN_CXT_EXEC_PC                psVLKN_CXT_EXEC )
{
    VkFormat_C                                  enVLKN_Depth_Stencil_Format = (VkFormat)psRender_Target->m_sRender_Target_DESC.m_enDepth_Stencil_Format;

    STg2_KN_GPU_VLKN_Graphics_Pipeline_CI       sVLKN_Graphics_Pipeline_CI;
    STg2_KN_GPU_VLKN_Compute_Pipeline_CI        sVLKN_Compute_Pipeline_CI;
    TgRSIZE                                     nuiVLKN_Pipeline;

    tgMM_Set_U08_0x00( &sVLKN_Graphics_Pipeline_CI, sizeof(sVLKN_Graphics_Pipeline_CI) );

    sVLKN_Graphics_Pipeline_CI.m_psPipeline_DESC = (STg2_KN_GPU_Graphics_Pipeline_CP)&g_asKN_GPU_Graphics_Pipeline;
    sVLKN_Graphics_Pipeline_CI.m_nuiPipeline_DESC = TgARRAY_COUNT(g_asKN_GPU_Graphics_Pipeline);

    sVLKN_Graphics_Pipeline_CI.m_ptiVS = g_sKN_GPU_CXT_HOST.m_atiVS;
    sVLKN_Graphics_Pipeline_CI.m_nuiVS = TgARRAY_COUNT(g_sKN_GPU_CXT_HOST.m_atiVS);
    sVLKN_Graphics_Pipeline_CI.m_ptiFS = g_sKN_GPU_CXT_HOST.m_atiFS;
    sVLKN_Graphics_Pipeline_CI.m_nuiFS = TgARRAY_COUNT(g_sKN_GPU_CXT_HOST.m_atiFS);

    sVLKN_Graphics_Pipeline_CI.m_phVLKN_VS = psVLKN_CXT_EXEC->m_ahVLKN_VS;
    sVLKN_Graphics_Pipeline_CI.m_phVLKN_FS = psVLKN_CXT_EXEC->m_ahVLKN_FS;

    sVLKN_Graphics_Pipeline_CI.m_phVLKN_Pipeline_Layout = psVLKN_CXT_EXEC->m_ahVLKN_Pipeline_Layout;
    sVLKN_Graphics_Pipeline_CI.m_hVLKN_Device = hVLKN_Device;
    sVLKN_Graphics_Pipeline_CI.m_psVLKN_CXT_EXEC = psVLKN_CXT_EXEC;
    sVLKN_Graphics_Pipeline_CI.m_enColour_Space = psRender_Target->m_sRender_Target_DESC.m_enColour_Space;

    sVLKN_Graphics_Pipeline_CI.m_sVLKN_Pipeline_Rendering_CI.sType = VK_STRUCTURE_TYPE_PIPELINE_RENDERING_CREATE_INFO_KHR;
    sVLKN_Graphics_Pipeline_CI.m_sVLKN_Pipeline_Rendering_CI.pNext = nullptr;
    sVLKN_Graphics_Pipeline_CI.m_sVLKN_Pipeline_Rendering_CI.colorAttachmentCount = (TgUINT_E32)psRender_Target->m_sRender_Target_DESC.m_nuiColour_Target;
    sVLKN_Graphics_Pipeline_CI.m_sVLKN_Pipeline_Rendering_CI.pColorAttachmentFormats = (VkFormat_P)psRender_Target->m_sRender_Target_DESC.m_aenColour_Format;
    sVLKN_Graphics_Pipeline_CI.m_sVLKN_Pipeline_Rendering_CI.depthAttachmentFormat = enVLKN_Depth_Stencil_Format;
    sVLKN_Graphics_Pipeline_CI.m_sVLKN_Pipeline_Rendering_CI.stencilAttachmentFormat = psRender_Target->m_bStencil_Valid ? enVLKN_Depth_Stencil_Format : VK_FORMAT_UNDEFINED;
    sVLKN_Graphics_Pipeline_CI.m_sVLKN_Pipeline_Rendering_CI.viewMask = 0;

    nuiVLKN_Pipeline = TgARRAY_COUNT(psRender_Target->m_ahVLKN_Pipeline_Graphics);
    if (TgFAILED(tgKN_GPU_VLKN_Create_Graphic_Pipelines( psRender_Target->m_ahVLKN_Pipeline_Graphics, nuiVLKN_Pipeline, &sVLKN_Graphics_Pipeline_CI )))
    {
        TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create graphics pipelines for dynamic rendering" );
        return (KTgE_FAIL);
    }

    tgMM_Set_U08_0x00( &sVLKN_Compute_Pipeline_CI, sizeof(sVLKN_Compute_Pipeline_CI) );

    sVLKN_Compute_Pipeline_CI.m_psPipeline_DESC = (STg2_KN_GPU_Compute_Pipeline_CP)&g_asKN_GPU_Compute_Pipeline_For_Rendering;
    sVLKN_Compute_Pipeline_CI.m_nuiPipeline_DESC = TgARRAY_COUNT(g_asKN_GPU_Compute_Pipeline_For_Rendering);

    sVLKN_Compute_Pipeline_CI.m_ptiCS = g_sKN_GPU_CXT_HOST.m_atiCS;
    sVLKN_Compute_Pipeline_CI.m_nuiCS = TgARRAY_COUNT(g_sKN_GPU_CXT_HOST.m_atiCS);

    sVLKN_Compute_Pipeline_CI.m_phVLKN_CS = psVLKN_CXT_EXEC->m_ahVLKN_CS;

    sVLKN_Compute_Pipeline_CI.m_phVLKN_Pipeline_Layout = psVLKN_CXT_EXEC->m_ahVLKN_Pipeline_Layout;
    sVLKN_Compute_Pipeline_CI.m_hVLKN_Device = hVLKN_Device;
    sVLKN_Compute_Pipeline_CI.m_psVLKN_CXT_EXEC = psVLKN_CXT_EXEC;
    sVLKN_Compute_Pipeline_CI.m_enColour_Space = psRender_Target->m_sRender_Target_DESC.m_enColour_Space;

    sVLKN_Compute_Pipeline_CI.m_sVLKN_Pipeline_Rendering_CI.sType = VK_STRUCTURE_TYPE_PIPELINE_RENDERING_CREATE_INFO_KHR;
    sVLKN_Compute_Pipeline_CI.m_sVLKN_Pipeline_Rendering_CI.pNext = nullptr;
    sVLKN_Compute_Pipeline_CI.m_sVLKN_Pipeline_Rendering_CI.colorAttachmentCount = (TgUINT_E32)psRender_Target->m_sRender_Target_DESC.m_nuiColour_Target;
    sVLKN_Compute_Pipeline_CI.m_sVLKN_Pipeline_Rendering_CI.pColorAttachmentFormats = (VkFormat_P)psRender_Target->m_sRender_Target_DESC.m_aenColour_Format;
    sVLKN_Compute_Pipeline_CI.m_sVLKN_Pipeline_Rendering_CI.depthAttachmentFormat = enVLKN_Depth_Stencil_Format;
    sVLKN_Compute_Pipeline_CI.m_sVLKN_Pipeline_Rendering_CI.stencilAttachmentFormat = psRender_Target->m_bStencil_Valid ? enVLKN_Depth_Stencil_Format : VK_FORMAT_UNDEFINED;
    sVLKN_Compute_Pipeline_CI.m_sVLKN_Pipeline_Rendering_CI.viewMask = 0;

    nuiVLKN_Pipeline = TgARRAY_COUNT(psRender_Target->m_ahVLKN_Pipeline_Compute);
    if (TgFAILED(tgKN_GPU_VLKN_Create_Compute_Pipelines( psRender_Target->m_ahVLKN_Pipeline_Compute, nuiVLKN_Pipeline, &sVLKN_Compute_Pipeline_CI )))
    {
        TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create graphics pipelines for dynamic rendering" );
        return (KTgE_FAIL);
    }

    return (KTgS_OK);
}
