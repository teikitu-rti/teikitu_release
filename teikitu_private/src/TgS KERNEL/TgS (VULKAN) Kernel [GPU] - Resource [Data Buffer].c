/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (VULKAN) Kernel [GPU] - Resource [Buffer].c
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

/* ---- tgKN_GPU_VLKN__CMD__Create_Buffer ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_VLKN__CMD__Create_Buffer(
    VkBuffer_PC                                 phBuffer,
    VkDeviceMemory_PC                           phBuffer_Memory,
    STg2_KN_GPU_VLKN_CMD_PC                     psVLKN_CMD,
    TgUINT_E64_C                                uiResource_Descriptor,
    TgRSIZE_C                                   uiSize,
    TgUINT_E32_CPC                              auiQueue_Family_Index,
    TgRSIZE_C                                   nuiCMD_Concurrent )
{
    VkDevice_C                                  hVLKN_Device = psVLKN_CMD->m_hVLKN_Device;
    VkPhysicalDeviceMemoryProperties_C          sMemory_Properties = psVLKN_CMD->m_sVLKN_Memory_Properties.memoryProperties;
    VkMemoryPropertyFlags_C                     uiMemory_Property_Flags = tgKN_GPU_VLKN_Convert_Memory_Properties(uiResource_Descriptor);

    VkBufferCreateInfo                          sBufferInfo;
    VkMemoryRequirements                        sMemRequirements;
    VkMemoryAllocateInfo                        sAllocInfo;
    VkResult                                    eResult;
    TgUINT_E32                                  uiMemory_Type_Index;

    TgPARAM_CHECK_KN_GPU_VLKN_CMD( psVLKN_CMD );
    TgPARAM_CHECK( nullptr != phBuffer );
    TgPARAM_CHECK( nullptr != phBuffer_Memory );

    /* Create buffer */
    tgMM_Set_U08_0x00( &sBufferInfo, sizeof( sBufferInfo ) );
    sBufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    sBufferInfo.size = uiSize;
    sBufferInfo.usage = tgKN_GPU_VLKN_Convert_Buffer_Usage(uiResource_Descriptor);
    sBufferInfo.sharingMode = (nuiCMD_Concurrent > 0) ? VK_SHARING_MODE_CONCURRENT : VK_SHARING_MODE_EXCLUSIVE;
    sBufferInfo.queueFamilyIndexCount = (TgUINT_E32)nuiCMD_Concurrent;
    sBufferInfo.pQueueFamilyIndices = (nuiCMD_Concurrent > 0) ? auiQueue_Family_Index : nullptr;

    eResult = vkCreateBuffer(hVLKN_Device, &sBufferInfo, g_psKN_GPU_VLKN_Allocator, phBuffer);
    if (eResult != VK_SUCCESS)
    {
        TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create buffer" );
        return (KTgE_FAIL);
    }

    /* Get memory requirements */
    vkGetBufferMemoryRequirements(hVLKN_Device, *phBuffer, &sMemRequirements);

    for (uiMemory_Type_Index = 0; uiMemory_Type_Index < sMemory_Properties.memoryTypeCount; ++uiMemory_Type_Index)
    {
        if (sMemRequirements.memoryTypeBits & (1 << uiMemory_Type_Index))
        {
            if ((sMemory_Properties.memoryTypes[uiMemory_Type_Index].propertyFlags & uiMemory_Property_Flags) == uiMemory_Property_Flags)
            {
                break;
            };
        };
    }

    if (uiMemory_Type_Index == sMemory_Properties.memoryTypeCount)
    {
        TgERROR_MSG( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to find suitable memory type" );
        vkDestroyBuffer(hVLKN_Device, *phBuffer, g_psKN_GPU_VLKN_Allocator);
        return (KTgE_FAIL);
    }

    /* Allocate memory */
    tgMM_Set_U08_0x00( &sAllocInfo, sizeof( sAllocInfo ) );
    sAllocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    sAllocInfo.allocationSize = sMemRequirements.size;
    sAllocInfo.memoryTypeIndex = uiMemory_Type_Index;

    eResult = vkAllocateMemory(hVLKN_Device, &sAllocInfo, g_psKN_GPU_VLKN_Allocator, phBuffer_Memory);
    if (eResult != VK_SUCCESS)
    {
        TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to allocate buffer memory" );
        vkDestroyBuffer(hVLKN_Device, *phBuffer, g_psKN_GPU_VLKN_Allocator);
        return (KTgE_FAIL);
    }

    /* Bind memory to buffer */
    vkBindBufferMemory(hVLKN_Device, *phBuffer, *phBuffer_Memory, 0);

    return (KTgS_OK);
}


/* ---- tgKN_GPU_VLKN__CMD__Copy_Buffer ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_VLKN__CMD__Copy_Buffer( STg2_KN_GPU_VLKN_CMD_PC psVLKN_CMD, VkBuffer_C sDstBuffer, TgRSIZE_C uiDst, VkBuffer_C sSrcBuffer, TgRSIZE_C uiSrc, TgRSIZE_C uiSize )
{
    TgPARAM_CHECK_KN_GPU_VLKN_CMD( psVLKN_CMD );

    if (VK_NULL_HANDLE != sSrcBuffer && VK_NULL_HANDLE != sDstBuffer)
    {
        VkBufferCopy                        sCopyRegion;

        tgMM_Set_U08_0x00( &sCopyRegion, sizeof( sCopyRegion ) );
        sCopyRegion.srcOffset = uiSrc;
        sCopyRegion.dstOffset = uiDst;
        sCopyRegion.size = uiSize;

        vkCmdCopyBuffer(psVLKN_CMD->m_hVLKN_Command_Buffer, sSrcBuffer, sDstBuffer, 1, &sCopyRegion);
    };

    return (KTgS_OK);
}


/* ---- tgKN_GPU_VLKN__CMD__Upload_Buffer ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_VLKN__CMD__Upload_Buffer( STg2_KN_GPU_VLKN_CMD_PC psVLKN_CMD, VkBuffer_C hBuffer, TgVOID_CPC pData, TgRSIZE_C nbyOffset, TgRSIZE_C nbyData )
{
    VkBuffer                            hStaging_Buffer;
    VkDeviceMemory                      hStaging_Memory;
    TgVOID_P                            pMapped;
    TgUINT_E64                          uiResource_Descriptor;
    TgRESULT                            iResult;

    TgPARAM_CHECK_KN_GPU_VLKN_CMD( psVLKN_CMD );
    TgPARAM_CHECK( nullptr != pData );
    TgPARAM_CHECK( VK_NULL_HANDLE != hBuffer );

    /* Create staging buffer */

    uiResource_Descriptor  = ETgKN_GPU_RESOURCE_DESCRIPTOR__UPLOAD_BUFFER;
    uiResource_Descriptor |= ETgKN_GPU_RESOURCE_DESCRIPTOR__MEMORY_HOST_VISIBLE;
    uiResource_Descriptor |= ETgKN_GPU_RESOURCE_DESCRIPTOR__MEMORY_HOST_COHERENT;

    iResult = tgKN_GPU_VLKN__CMD__Create_Buffer(&hStaging_Buffer, &hStaging_Memory, psVLKN_CMD, uiResource_Descriptor, nbyData, nullptr, 0);
    if (TgFAILED(iResult))
    {
        return (iResult);
    }

    /* Map and copy data to staging buffer */
    if (VK_SUCCESS == vkMapMemory(psVLKN_CMD->m_hVLKN_Device, hStaging_Memory, 0, nbyData, 0, &pMapped))
    {
        tgMM_Copy(pMapped, nbyData, (TgUINT_E08_CPC)pData + nbyOffset, nbyData);
        vkUnmapMemory(psVLKN_CMD->m_hVLKN_Device, hStaging_Memory);
    }

    /* Copy from staging to destination */
    tgKN_GPU_VLKN__CMD__Copy_Buffer( psVLKN_CMD, hBuffer, 0, hStaging_Buffer, 0, nbyData );

    /* Clean up staging buffer */
    tgKN_GPU_VLKN__CMD__Register_Resource_For_Release((STg2_KN_GPU_CMD_P)psVLKN_CMD, hStaging_Buffer, hStaging_Memory);

    return (KTgS_OK);
}


/* ---- tgKN_GPU_VLKN__CMD__Create_Buffer_With_Data ------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_VLKN__CMD__Create_Buffer_With_Data( VkBuffer_PC phBuffer, VkDeviceMemory_PC phBuffer_Memory, STg2_KN_GPU_VLKN_CMD_PC psVLKN_CMD,
                                                      TgUINT_E64_C uiResource_Descriptor, TgVOID_CP pData, TgRSIZE_C nbyData )
{
    TgRESULT                            iResult;

    TgPARAM_CHECK_KN_GPU_VLKN_CMD( psVLKN_CMD );

    iResult = tgKN_GPU_VLKN__CMD__Create_Buffer(phBuffer, phBuffer_Memory, psVLKN_CMD, uiResource_Descriptor, nbyData, nullptr, 0);
    if (TgFAILED(iResult))
    {
        return iResult;
    }

    if (nullptr != pData && nbyData > 0)
    {
        iResult = tgKN_GPU_VLKN__CMD__Upload_Buffer(psVLKN_CMD, *phBuffer, pData, 0, nbyData);
        if (TgFAILED(iResult))
        {
            /* Clean up on upload failure */
            vkDestroyBuffer(psVLKN_CMD->m_hVLKN_Device, *phBuffer, g_psKN_GPU_VLKN_Allocator);
            vkFreeMemory(psVLKN_CMD->m_hVLKN_Device, *phBuffer_Memory, g_psKN_GPU_VLKN_Allocator);
            *phBuffer = VK_NULL_HANDLE;
            *phBuffer_Memory = VK_NULL_HANDLE;
            return iResult;
        }
    }

    return (KTgS_OK);
}
