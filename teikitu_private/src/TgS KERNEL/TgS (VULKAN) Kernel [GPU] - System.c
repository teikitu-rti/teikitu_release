/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (VULKAN) Kernel [GPU] - System.c
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
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_GPU_VLKN_Create_Semaphore_Binary ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_VLKN_Create_Semaphore_Binary( VkSemaphore_P phSemaphore, VkDevice hVLKN_Device )
{
    VkSemaphoreTypeCreateInfo           sVLKN_Semaphore_Type_CI = {
                                            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO,
                                            .pNext = nullptr,
                                            .semaphoreType = VK_SEMAPHORE_TYPE_BINARY,
                                            .initialValue = VK_FALSE,
                                        };

    VkSemaphoreCreateInfo               sVLKN_Semaphore_CI = {
                                            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
                                            .pNext = &sVLKN_Semaphore_Type_CI,
                                            .flags = 0
                                        };

    VkResult                            eResult;

    eResult = vkCreateSemaphore(hVLKN_Device, &sVLKN_Semaphore_CI, g_psKN_GPU_VLKN_Allocator, phSemaphore);
    if (VK_SUCCESS != eResult)
    {
        *phSemaphore = VK_NULL_HANDLE;
        TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create binary semaphore" );
        return (KTgE_FAIL);
    };
    return (KTgS_OK);
}


/* ---- tgKN_GPU_VLKN_Create_Semaphore_Timeline ---------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_VLKN_Create_Semaphore_Timeline( VkSemaphore_P phSemaphore, VkDevice hVLKN_Device )
{
    VkSemaphoreTypeCreateInfo           sVLKN_Semaphore_Type_CI = {
                                            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO,
                                            .pNext = nullptr,
                                            .semaphoreType = VK_SEMAPHORE_TYPE_TIMELINE,
                                            .initialValue = 0,
                                        };

    VkSemaphoreCreateInfo               sVLKN_Semaphore_CI = {
                                            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
                                            .pNext = &sVLKN_Semaphore_Type_CI,
                                            .flags = 0
                                        };

    VkResult                            eResult;

    eResult = vkCreateSemaphore(hVLKN_Device, &sVLKN_Semaphore_CI, g_psKN_GPU_VLKN_Allocator, phSemaphore);
    if (VK_SUCCESS != eResult)
    {
        *phSemaphore = VK_NULL_HANDLE;
        TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create timeline semaphore" );
        return (KTgE_FAIL);
    };
    return (KTgS_OK);
}


/* ---- tgKN_GPU_VLKN_Wait_Semaphore_Timeline ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_VLKN_Wait_Semaphore_Timeline( VkDevice hVLKN_Device, VkSemaphore hSemaphore, TgUINT_E64_C uiSemaphore_Timeline_Terminator )
{
    TgUINT_E64                          uiCompleted_Semaphore_Timeline_Value;
    VkResult                            eResult;

    eResult = vkGetSemaphoreCounterValue( hVLKN_Device, hSemaphore, &uiCompleted_Semaphore_Timeline_Value );
    if (VK_SUCCESS != eResult)
    {
        TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to get semaphore counter value" );
        return (KTgE_FAIL);
    }

    if (uiCompleted_Semaphore_Timeline_Value < uiSemaphore_Timeline_Terminator)
    {
        VkSemaphoreWaitInfo_C               sVLKN_Semaphore_Wait_Info = {
                                                .sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
                                                .pNext = nullptr,
                                                .flags = 0,
                                                .semaphoreCount = 1,
                                                .pSemaphores = &hSemaphore,
                                                .pValues = &uiSemaphore_Timeline_Terminator,
                                            };

        eResult = vkWaitSemaphores( hVLKN_Device, &sVLKN_Semaphore_Wait_Info, 1000000000 );
        if (VK_SUCCESS != eResult)
        {
            TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to wait on semaphore" );
            return (KTgE_FAIL);
        }
        // VK_TIMEOUT
    }

    return (KTgS_OK);
}


/* ---- tgKN_GPU_VLKN_Submit_Semaphore_Timeline_For_Queue_With_Wait -------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_VLKN_Submit_Semaphore_Timeline_For_Queue_With_Wait(
    TgUINT_E64_P                                puiCurrent_Timeline_Value,
    STg2_KN_GPU_VLKN_CMD_Queue_PC               psCMD_Queue,
    TgRSIZE                                     nuiCmd_Buffer,
    VkCommandBuffer_CP                          ahCmd_Buffer,
    STg2_KN_GPU_VLKN_CMD_Queue_PC               psWait_CMD_Queue,
    TgUINT_E64_C                                uiTimeline_Terminator_Value )
{
    TgPARAM_CHECK( nullptr != psCMD_Queue);

    for (; nuiCmd_Buffer > 16; nuiCmd_Buffer -= 16, ahCmd_Buffer += 16)
    {
        TgRESULT                                    iRet;

        iRet = tgKN_GPU_VLKN_Submit_Semaphore_Timeline_For_Queue_With_Wait( nullptr, psCMD_Queue, 16, ahCmd_Buffer, psWait_CMD_Queue, uiTimeline_Terminator_Value );
        if (TgFAILED(iRet))
        {
            TgERROR_MSGF(0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to submit all command buffers.");
            return (iRet);
        }
    }

    tgCM_UT_LF__SN__Lock_Spin( &psCMD_Queue->m_sLock.m_sLock );
    {
        TgUINT_E64_C                                uiCurrent_Timeline_Value = TgSTD_ATOMIC(fetch_add)( &psCMD_Queue->m_xuiTimeline_Signal_Value, 1 );
        VkResult                                    eResult;

        VkSemaphoreSubmitInfo_C                     sVLKN_Wait_Semaphore_Info = {
                                                        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
                                                        .pNext = nullptr,
                                                        .semaphore = nullptr != psWait_CMD_Queue ? psWait_CMD_Queue->m_hVLKN_Timeline : VK_NULL_HANDLE,
                                                        .value = uiTimeline_Terminator_Value,
                                                        .stageMask = VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT,
                                                        .deviceIndex = 0,
                                                    };

        VkSemaphoreSubmitInfo_C                     sVLKN_Signal_Semaphore_Info = {
                                                        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
                                                        .pNext = nullptr,
                                                        .semaphore = psCMD_Queue->m_hVLKN_Timeline,
                                                        .value = uiCurrent_Timeline_Value,
                                                        .stageMask = VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT,
                                                        .deviceIndex = 0,
                                                    };

        VkCommandBufferSubmitInfo                   asVLKN_Cmd_Buffer_Info[16];

        VkSubmitInfo2_C                             sVLKN_Submit_Info = {
                                                        .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO_2,
                                                        .pNext = nullptr,
                                                        .flags = 0,
                                                        .waitSemaphoreInfoCount = nullptr != psWait_CMD_Queue ? 1u : 0u,
                                                        .pWaitSemaphoreInfos = nullptr != psWait_CMD_Queue ? &sVLKN_Wait_Semaphore_Info : nullptr,
                                                        .commandBufferInfoCount = (TgUINT_E32)nuiCmd_Buffer,
                                                        .pCommandBufferInfos = asVLKN_Cmd_Buffer_Info,
                                                        .signalSemaphoreInfoCount = 1,
                                                        .pSignalSemaphoreInfos = &sVLKN_Signal_Semaphore_Info,
                                                    };

        TgRSIZE                                     uiIndex;

        for (uiIndex = 0; uiIndex < nuiCmd_Buffer; ++uiIndex)
        {
            asVLKN_Cmd_Buffer_Info[uiIndex].sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_SUBMIT_INFO;
            asVLKN_Cmd_Buffer_Info[uiIndex].pNext = nullptr;
            asVLKN_Cmd_Buffer_Info[uiIndex].commandBuffer = ahCmd_Buffer[uiIndex];
            asVLKN_Cmd_Buffer_Info[uiIndex].deviceMask = 0;
        }

        eResult = vkQueueSubmit2(psCMD_Queue->m_hVLKN_Queue, 1, &sVLKN_Submit_Info, VK_NULL_HANDLE);
        if (VK_SUCCESS != eResult)
        {
            TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to submit command buffer" );
        }

        if (nullptr != puiCurrent_Timeline_Value)
        {
            *puiCurrent_Timeline_Value = uiCurrent_Timeline_Value;
        }
    }
    tgCM_UT_LF__SN__Signal( &psCMD_Queue->m_sLock.m_sLock );

    return (KTgS_OK);
}


/* ---- tgKN_GPU_VLKN_Create_Command_Pool ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_VLKN_Create_Command_Pool( VkCommandPool_P phCmd_Pool, VkDevice hVLKN_Device, TgRSIZE_C uiQueue_Family_Index )
{
    VkCommandPoolCreateInfo             sCmd_Pool_CI;
    VkResult                            eResult;

    tgMM_Set_U08_0x00( &sCmd_Pool_CI, sizeof( sCmd_Pool_CI ) );
    sCmd_Pool_CI.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    sCmd_Pool_CI.pNext = nullptr;
    sCmd_Pool_CI.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    sCmd_Pool_CI.queueFamilyIndex = (TgUINT_E32)uiQueue_Family_Index;

    eResult = vkCreateCommandPool( hVLKN_Device, &sCmd_Pool_CI, g_psKN_GPU_VLKN_Allocator, phCmd_Pool );
    if (VK_SUCCESS != eResult)
    {
        TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create command pool" );
        *phCmd_Pool = VK_NULL_HANDLE;
        return( KTgE_FAIL );
    }

    return (KTgS_OK);
}


/* ---- tgKN_GPU_VLKN_Create_Command_Buffer -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_VLKN_Create_Command_Buffer( VkCommandBuffer_P phCmd_Buffer, VkDevice hVLKN_Device, VkCommandPool hCmd_Pool )
{
    VkCommandBufferAllocateInfo         sAlloc_Info;
    VkResult                            eResult;

    TgPARAM_CHECK( nullptr != phCmd_Buffer );

    tgMM_Set_U08_0x00( &sAlloc_Info, sizeof( sAlloc_Info ) );
    sAlloc_Info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    sAlloc_Info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    sAlloc_Info.commandPool = hCmd_Pool;
    sAlloc_Info.commandBufferCount = 1;

    eResult = vkAllocateCommandBuffers( hVLKN_Device, &sAlloc_Info, phCmd_Buffer );
    if (VK_SUCCESS != eResult)
    {
        TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create command buffer" );
        *phCmd_Buffer = VK_NULL_HANDLE;
        return( KTgE_FAIL );
    };
    TgMACRO_KN_GPU_VLKN_SET_NAME(hVLKN_Device, VK_OBJECT_TYPE_COMMAND_BUFFER, *phCmd_Buffer, u8"Command Buffer");

    return (KTgS_OK);
}


/* ---- tgKN_GPU_VLKN_Create_Shader_Module --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_VLKN_Create_Shader_Module( VkShaderModule_P psShaderModule, VkDevice hVLKN_Device, TgVOID_CPC pCode, TgRSIZE_C nbyCode )
{
    VkShaderModuleCreateInfo            sCreateInfo = {
                                            .sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
                                            .pNext = nullptr,
                                            .flags = 0,
                                            .codeSize = nbyCode,
                                            .pCode = (const uint32_t*)pCode
                                        };

    VkResult                            eResult;

    eResult = vkCreateShaderModule(hVLKN_Device, &sCreateInfo, g_psKN_GPU_VLKN_Allocator, psShaderModule);
    if (eResult != VK_SUCCESS)
    {
        TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create shader module" );
        return (KTgE_FAIL);
    }

    return (KTgS_OK);
}


/* ---- tgKN_GPU_VLKN_Convert_Buffer_Usage ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
VkBufferUsageFlags tgKN_GPU_VLKN_Convert_Buffer_Usage( TgUINT_E64_C uiResource_Descriptor )
{
    VkBufferUsageFlags                  uiVLKN_Buffer_Usage;

    uiVLKN_Buffer_Usage = 0u;

    if (ETgKN_GPU_RESOURCE_DESCRIPTOR__VERTEX_BUFFER & uiResource_Descriptor) {
        uiVLKN_Buffer_Usage |= VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;
    } else if (ETgKN_GPU_RESOURCE_DESCRIPTOR__INDEX_BUFFER & uiResource_Descriptor) {
        uiVLKN_Buffer_Usage |= VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;
    } else if ((ETgKN_GPU_RESOURCE_DESCRIPTOR__UNIFORM_BUFFER & uiResource_Descriptor) || (ETgKN_GPU_RESOURCE_DESCRIPTOR__UNIFORM_BUFFER_DYNAMIC & uiResource_Descriptor)) {
        uiVLKN_Buffer_Usage |= VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
    } else if ((ETgKN_GPU_RESOURCE_DESCRIPTOR__STORAGE_BUFFER & uiResource_Descriptor) || (ETgKN_GPU_RESOURCE_DESCRIPTOR__STORAGE_BUFFER_DYNAMIC & uiResource_Descriptor)){
        uiVLKN_Buffer_Usage |= VK_BUFFER_USAGE_STORAGE_BUFFER_BIT;
    } else if (ETgKN_GPU_RESOURCE_DESCRIPTOR__UPLOAD_BUFFER & uiResource_Descriptor) {
        uiVLKN_Buffer_Usage |= VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
    } else if (ETgKN_GPU_RESOURCE_DESCRIPTOR__READBACK_BUFFER & uiResource_Descriptor) {
        uiVLKN_Buffer_Usage |= VK_BUFFER_USAGE_TRANSFER_DST_BIT;
    }

    if (ETgKN_GPU_RESOURCE_DESCRIPTOR__INDIRECT_BUFFER & uiResource_Descriptor) {
        uiVLKN_Buffer_Usage |= VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT;
    }

    if (ETgKN_GPU_RESOURCE_DESCRIPTOR__TRANSFER_SRC & uiResource_Descriptor) {
        uiVLKN_Buffer_Usage |= VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
    }

    if (ETgKN_GPU_RESOURCE_DESCRIPTOR__TRANSFER_DST & uiResource_Descriptor) {
        uiVLKN_Buffer_Usage |= VK_BUFFER_USAGE_TRANSFER_DST_BIT;
    }

    return (uiVLKN_Buffer_Usage);
}


/* ---- tgKN_GPU_VLKN_Convert_Image_Usage ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
VkImageUsageFlags tgKN_GPU_VLKN_Convert_Image_Usage( TgUINT_E64_C uiResource_Descriptor )
{
    TgUINT_F32_C                        uiImageDescriptor = uiResource_Descriptor & ETgKN_GPU_RESOURCE_DESCRIPTOR__TEXTURE_TYPE_MASK;

    switch (uiImageDescriptor)
    {
        case ETgKN_GPU_RESOURCE_DESCRIPTOR__UPLOAD_TYPE_TEXTURE:
            return VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
        case ETgKN_GPU_RESOURCE_DESCRIPTOR__READBACK_TYPE_TEXTURE:
            return VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_STORAGE_BIT;
        default:
            return VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
    }
}


/* ---- tgKN_GPU_VLKN_Convert_Memory_Properties ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
VkMemoryPropertyFlags tgKN_GPU_VLKN_Convert_Memory_Properties( TgUINT_E64_C uiResource_Descriptor )
{
    VkMemoryPropertyFlags               uiVLKN_Memory_Properties;

    uiVLKN_Memory_Properties = 0u;

    if (0 != (uiResource_Descriptor & ETgKN_GPU_RESOURCE_DESCRIPTOR__MEMORY_LOCAL))
    {
        uiVLKN_Memory_Properties |= VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
    }

    if (0 != (uiResource_Descriptor & ETgKN_GPU_RESOURCE_DESCRIPTOR__MEMORY_HOST_VISIBLE))
    {
        uiVLKN_Memory_Properties |= VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT;
    }

    if (0 != (uiResource_Descriptor & ETgKN_GPU_RESOURCE_DESCRIPTOR__MEMORY_HOST_COHERENT))
    {
        uiVLKN_Memory_Properties |= VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
    }

    return uiVLKN_Memory_Properties;
}


/* ---- tgKN_GPU_VLKN_Find_Memory_Type_Index ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_VLKN_Find_Memory_Type_Index( TgUINT_E32_P puiMemory_Type_Index, VkPhysicalDevice hVLKN_Physical_Device, TgUINT_E32_C uiType_Filter, 
                                               VkMemoryPropertyFlags_C uiVLKN_Memory_Properties )
{
    VkPhysicalDeviceMemoryProperties    sVLKN_Memory_Properties;
    TgUINT_E32                          uiIndex;

    TgPARAM_CHECK( nullptr != puiMemory_Type_Index );

    vkGetPhysicalDeviceMemoryProperties( hVLKN_Physical_Device, &sVLKN_Memory_Properties );

    for (uiIndex = 0; uiIndex < sVLKN_Memory_Properties.memoryTypeCount; ++uiIndex)
    {
        if ((uiType_Filter & (1 << uiIndex)) && 
            ((sVLKN_Memory_Properties.memoryTypes[uiIndex].propertyFlags & uiVLKN_Memory_Properties) == uiVLKN_Memory_Properties))
        {
            *puiMemory_Type_Index = uiIndex;
            return (KTgS_OK);
        }
    }

    TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to find suitable memory type" );
    *puiMemory_Type_Index = 0;
    return (KTgE_FAIL);
}
