/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (VULKAN) Kernel [GPU] - System [Enumeration].c
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

static STg2_KN_GPU_VLKN_Physical_Device_P
tgKN_GPU_EXT_Enumerate__Process_Physical_Device(
    VkPhysicalDevice_C, TgBOOL_C );

static TgRESULT
tgKN_GPU_EXT_Enumerate__Physical_Device_Output(
    STg2_KN_GPU_VLKN_Physical_Device_PCU );

static TgVOID
tgKN_GPU_EXT_Enumerate__Populate_Module( TgVOID );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_GPU_EXT_Enumerate --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_EXT_Enumerate( TgVOID )
{
    VkPhysicalDevice_P                  psPhysical_Devices = nullptr;
    TgUINT_E32                          nuiPhysical_Device = 0;
    TgUINT_E32                          idxCXT_HOST_Physical_Device;

    TgERROR(tgKN_Query_Boot());

    tgCM_UT_LF__RW__Enter_Write_Spin_Block( &g_sKN_GPU_CXT_HOST.m_sLock.m_sLock );

    /* If we don't have an instance, fail. */
    if (VK_NULL_HANDLE == g_sKN_GPU_EXT_CXT_HOST.m_hVLKN_Instance)
    {
        tgCM_UT_LF__RW__Exit_Write( &g_sKN_GPU_CXT_HOST.m_sLock.m_sLock );
        return (KTgE_FAIL);
    };

    /* If we already have physical devices, skip the enumeration. */
    if (g_sKN_GPU_CXT_HOST.m_nuiPhysical_Device > 0)
    {
        tgCM_UT_LF__RW__Exit_Write( &g_sKN_GPU_CXT_HOST.m_sLock.m_sLock );
        return (KTgW_DUPLICATE);
    };

    TgPARAM_CHECK(g_sKN_GPU_CXT_HOST.m_nuiPhysical_Device == 0);
    TgPARAM_CHECK(g_sKN_GPU_CXT_HOST.m_nuiDisplay_Output == 0);

    /* Get available physical devices */
    vkEnumeratePhysicalDevices(g_sKN_GPU_EXT_CXT_HOST.m_hVLKN_Instance, &nuiPhysical_Device, nullptr);
    if (nuiPhysical_Device == 0)
    {
        TgERROR_MSG( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to find GPUs with Vulkan support!" );
        tgCM_UT_LF__RW__Exit_Write( &g_sKN_GPU_CXT_HOST.m_sLock.m_sLock );
        return (KTgE_FAIL);
    }

    psPhysical_Devices = (VkPhysicalDevice_P)TgMALLOC_TEMP(nuiPhysical_Device * sizeof(VkPhysicalDevice));
    if (psPhysical_Devices == nullptr)
    {
        TgERROR_MSG( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to allocate memory for physical devices!" );
        tgCM_UT_LF__RW__Exit_Write( &g_sKN_GPU_CXT_HOST.m_sLock.m_sLock );
        return (KTgE_MEM_ALLOC_FAIL);
    };

    vkEnumeratePhysicalDevices(g_sKN_GPU_EXT_CXT_HOST.m_hVLKN_Instance, &nuiPhysical_Device, psPhysical_Devices);

    /* Store physical device information */
    for (idxCXT_HOST_Physical_Device = 0; idxCXT_HOST_Physical_Device < nuiPhysical_Device; ++idxCXT_HOST_Physical_Device)
    {
        STg2_KN_GPU_VLKN_Physical_Device_P  psEXT_Physical_Device;

        psEXT_Physical_Device = tgKN_GPU_EXT_Enumerate__Process_Physical_Device(psPhysical_Devices[idxCXT_HOST_Physical_Device], false);
        if (!psEXT_Physical_Device)
        {
            continue;
        };

        psEXT_Physical_Device->m_uiPhysical_Device_Ordinal = idxCXT_HOST_Physical_Device;
    };

    TgFREE_TEMP(psPhysical_Devices);
    psPhysical_Devices = nullptr;

    if (g_sKN_GPU_CXT_HOST.m_nuiPhysical_Device == 0)
    {
        TgERROR_MSG( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"No suitable Vulkan devices found!" );
        tgCM_UT_LF__RW__Exit_Write( &g_sKN_GPU_CXT_HOST.m_sLock.m_sLock );
        return (KTgE_FAIL);
    };

    tgKN_GPU_EXT_Enumerate__Populate_Module();

    tgCM_UT_LF__RW__Exit_Write( &g_sKN_GPU_CXT_HOST.m_sLock.m_sLock );
    return (KTgS_OK);
}


/* ---- tgKN_GPU_EXT_Physical_Device_Free ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_EXT_Physical_Device_Free( TgRSIZE_C idxCXT_HOST_Physical_Device )
{
    STg2_KN_GPU_VLKN_Physical_Device_PC psEXT_Physical_Device = g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Physical_Device + idxCXT_HOST_Physical_Device;
    STg2_KN_GPU_Physical_Device_PC      psPhysical_Device = g_sKN_GPU_CXT_HOST.m_asPhysical_Device + idxCXT_HOST_Physical_Device;

    /* Wait for device to be idle before destroying */
    if (psEXT_Physical_Device->m_hVLKN_Device != VK_NULL_HANDLE)
    {
        vkDeviceWaitIdle(psEXT_Physical_Device->m_hVLKN_Device);
        vkDestroyDevice(psEXT_Physical_Device->m_hVLKN_Device, g_psKN_GPU_VLKN_Allocator);
        psEXT_Physical_Device->m_hVLKN_Device = VK_NULL_HANDLE;
    }

    /* Free Vulkan display mode properties if allocated */
    if (nullptr != psEXT_Physical_Device->m_psVLKN_Surface_Format)
    {
        TgFREE_POOL( psEXT_Physical_Device->m_psVLKN_Surface_Format );
        psEXT_Physical_Device->m_psVLKN_Surface_Format = nullptr;
    };

    /* Free Vulkan display mode properties if allocated */
    if (nullptr != psEXT_Physical_Device->m_psVLKN_Present_Mode)
    {
        TgFREE_POOL( psEXT_Physical_Device->m_psVLKN_Present_Mode );
        psEXT_Physical_Device->m_psVLKN_Present_Mode = nullptr;
    };

    TgERROR(KTgKN_GPU_CXT_DEVC_ID__INVALID.m_uiKI == psEXT_Physical_Device->m_tiID_DEVC.m_uiKI);
    tgMM_Set_U08_0x00( psEXT_Physical_Device, sizeof(STg2_KN_GPU_VLKN_Physical_Device) );
    psEXT_Physical_Device->m_tiID_DEVC = KTgKN_GPU_CXT_DEVC_ID__INVALID;
    tgMM_Set_U08_0x00( psPhysical_Device, sizeof(STg2_KN_GPU_Physical_Device) );
}


/* ---- tgKN_GPU_EXT_Display_Output_Free ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_EXT_Display_Output_Free( TgRSIZE_C idxCXT_HOST_Display_Output )
{
    STg2_KN_GPU_VLKN_Display_Output_PC  psGPU_EXT_Display_Output = g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Display_Output + idxCXT_HOST_Display_Output;
    STg2_KN_GPU_Display_Output_PC       psGPU_Display_Output = g_sKN_GPU_CXT_HOST.m_asDisplay_Output + idxCXT_HOST_Display_Output;

    /* Free Vulkan display mode properties if allocated */
    if (nullptr != psGPU_EXT_Display_Output->m_psVLKN_Display_Mode_Properties)
    {
        TgFREE_POOL( psGPU_EXT_Display_Output->m_psVLKN_Display_Mode_Properties );
        psGPU_EXT_Display_Output->m_psVLKN_Display_Mode_Properties = nullptr;
    };

    tgMM_Set_U08_0x00( psGPU_EXT_Display_Output, sizeof(STg2_KN_GPU_VLKN_Display_Output) );
    tgMM_Set_U08_0x00( psGPU_Display_Output, sizeof(STg2_KN_GPU_Display_Output) );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_GPU_EXT_Enumerate__Process_Physical_Device -------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static STg2_KN_GPU_VLKN_Physical_Device_P tgKN_GPU_EXT_Enumerate__Process_Physical_Device( VkPhysicalDevice_C hVLKN_Physical_Device, TgATTRIBUTE_UNUSED TgBOOL_C bSoftware )
{
    VkDeviceSize                        uiTotal_Memory;
    STg2_KN_GPU_VLKN_Physical_Device_P  psGPU_EXT_Physical_Device;
    TgRSIZE                             uiIndex;
    VkResult                            eResult;
    TgUINT_E32                          uiVkUint32;
    TgSINT_F32                          iFormat;
    TgBOOL                              bGraphicsFound, bPresentFound, bComputeFound, bTransferFound, bGraphicsSupportPresent;

    /* For now, we use a FCFS approach to allocate physical devices. */
    if (g_sKN_GPU_CXT_HOST.m_nuiPhysical_Device >= KTgKN_GPU_MAX_PHYSICAL_DEVICE)
    {
        return (nullptr);
    };

    psGPU_EXT_Physical_Device = g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Physical_Device + g_sKN_GPU_CXT_HOST.m_nuiPhysical_Device;
    TgCRITICAL(nullptr != psGPU_EXT_Physical_Device);
    tgMM_Set_U08_0x00(psGPU_EXT_Physical_Device, sizeof(STg2_KN_GPU_VLKN_Physical_Device));
    psGPU_EXT_Physical_Device->m_tiID_DEVC = KTgKN_GPU_CXT_DEVC_ID__INVALID;

    /* Store device information ------------------------------------------------------------------------------------------------------------------------------------------ */
    psGPU_EXT_Physical_Device->m_hVLKN_Physical_Device = hVLKN_Physical_Device;

    vkGetPhysicalDeviceProperties(psGPU_EXT_Physical_Device->m_hVLKN_Physical_Device, &psGPU_EXT_Physical_Device->m_sVLKN_Properties);

    psGPU_EXT_Physical_Device->m_sVLKN_Vulkan14_Features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_4_FEATURES;
    psGPU_EXT_Physical_Device->m_sVLKN_Vulkan14_Features.pNext = &psGPU_EXT_Physical_Device->m_sVLKN_Vulkan13_Features;
    psGPU_EXT_Physical_Device->m_sVLKN_Vulkan13_Features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES;
    psGPU_EXT_Physical_Device->m_sVLKN_Vulkan13_Features.pNext = &psGPU_EXT_Physical_Device->m_sVLKN_Vulkan12_Features;
    psGPU_EXT_Physical_Device->m_sVLKN_Vulkan12_Features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES;
    psGPU_EXT_Physical_Device->m_sVLKN_Vulkan12_Features.pNext = &psGPU_EXT_Physical_Device->m_sVLKN_Vulkan11_Features;
    psGPU_EXT_Physical_Device->m_sVLKN_Vulkan11_Features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_FEATURES;

    psGPU_EXT_Physical_Device->m_sVLKN_Features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
    psGPU_EXT_Physical_Device->m_sVLKN_Features.pNext = &psGPU_EXT_Physical_Device->m_sVLKN_Vulkan14_Features;
    vkGetPhysicalDeviceFeatures2(psGPU_EXT_Physical_Device->m_hVLKN_Physical_Device, &psGPU_EXT_Physical_Device->m_sVLKN_Features);

    /* Require certain indexing features to support bindless rendering approaches */
    if (!psGPU_EXT_Physical_Device->m_sVLKN_Vulkan12_Features.shaderSampledImageArrayNonUniformIndexing ||
        !psGPU_EXT_Physical_Device->m_sVLKN_Vulkan12_Features.shaderUniformBufferArrayNonUniformIndexing ||
        !psGPU_EXT_Physical_Device->m_sVLKN_Vulkan12_Features.shaderStorageBufferArrayNonUniformIndexing ||
        !psGPU_EXT_Physical_Device->m_sVLKN_Vulkan12_Features.descriptorBindingSampledImageUpdateAfterBind ||
        !psGPU_EXT_Physical_Device->m_sVLKN_Vulkan12_Features.descriptorBindingUniformBufferUpdateAfterBind ||
        !psGPU_EXT_Physical_Device->m_sVLKN_Vulkan12_Features.descriptorBindingStorageBufferUpdateAfterBind ||
        !psGPU_EXT_Physical_Device->m_sVLKN_Vulkan12_Features.descriptorBindingPartiallyBound )
    {
        TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to find support for required descriptor indexing features" );
        tgKN_GPU_EXT_Physical_Device_Free( g_sKN_GPU_CXT_HOST.m_nuiPhysical_Device );
        return (nullptr);
    };

    psGPU_EXT_Physical_Device->m_sVLKN_Memory_Properties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_PROPERTIES_2;
    vkGetPhysicalDeviceMemoryProperties2(psGPU_EXT_Physical_Device->m_hVLKN_Physical_Device, &psGPU_EXT_Physical_Device->m_sVLKN_Memory_Properties);

    /* Check available memory -------------------------------------------------------------------------------------------------------------------------------------------- */

    for (uiIndex = 0, uiTotal_Memory = 0; uiIndex < psGPU_EXT_Physical_Device->m_sVLKN_Memory_Properties.memoryProperties.memoryHeapCount; ++uiIndex)
    {
        if (psGPU_EXT_Physical_Device->m_sVLKN_Memory_Properties.memoryProperties.memoryHeaps[uiIndex].flags & VK_MEMORY_HEAP_DEVICE_LOCAL_BIT)
        {
            uiTotal_Memory += psGPU_EXT_Physical_Device->m_sVLKN_Memory_Properties.memoryProperties.memoryHeaps[uiIndex].size;
        };
    }

    /* Require at least 1GB of memory */
    if (uiTotal_Memory < (1024 * 1024 * 1024))
    {
        TgERROR_MSGF( 0, STD_MSG_LITERAL_0, STD_MSG_POST, u8"Failed to find support for at least 1GB of memory" );
        tgKN_GPU_EXT_Physical_Device_Free( g_sKN_GPU_CXT_HOST.m_nuiPhysical_Device );
        return (nullptr);
    }
    
    /* Get queue family properties and test for required queues. --------------------------------------------------------------------------------------------------------- */

    vkGetPhysicalDeviceQueueFamilyProperties(psGPU_EXT_Physical_Device->m_hVLKN_Physical_Device, &uiVkUint32, nullptr);
    if (uiVkUint32 > KTgKN_GPU_VLKN_MAX_QUEUE_FAMILY)
    {
        uiVkUint32 = KTgKN_GPU_VLKN_MAX_QUEUE_FAMILY;
    };
    psGPU_EXT_Physical_Device->m_nuiVLKN_Queue_Family = uiVkUint32;
    vkGetPhysicalDeviceQueueFamilyProperties(psGPU_EXT_Physical_Device->m_hVLKN_Physical_Device, &uiVkUint32, psGPU_EXT_Physical_Device->m_asVLKN_Queue_Family_Properties);
    {
        TgUINT_E32                          uiQueue_Family;

        tgMM_Set_U08_0xFF( &psGPU_EXT_Physical_Device->m_auiVLKN_Queue_Family_Index, sizeof( psGPU_EXT_Physical_Device->m_auiVLKN_Queue_Family_Index ) );

        bGraphicsFound = false;
        bGraphicsSupportPresent = false;
        bPresentFound = false;
        bComputeFound = false;
        bTransferFound = false;

        for (uiQueue_Family = 0; uiQueue_Family < psGPU_EXT_Physical_Device->m_nuiVLKN_Queue_Family; ++uiQueue_Family)
        {
            VkQueueFlags_C                      eQueueFlags = psGPU_EXT_Physical_Device->m_asVLKN_Queue_Family_Properties[uiQueue_Family].queueFlags;
            VkBool32                            bPresentSupport;

            /* Check for compute queue (prefer dedicated ahead of the test for present capability) */
            if (!bComputeFound && (eQueueFlags & VK_QUEUE_COMPUTE_BIT) && !(eQueueFlags & VK_QUEUE_GRAPHICS_BIT))
            {
                psGPU_EXT_Physical_Device->m_auiVLKN_Queue_Family_Index[ETgKN_GPU_EXT_COMMAND_COMPUTE] = uiQueue_Family;
                bComputeFound = true;
                continue;
            };

            /* Check for transfer queue (prefer dedicated ahead of the test for present capability) */
            if (!bTransferFound && (eQueueFlags & VK_QUEUE_TRANSFER_BIT) && !(eQueueFlags & VK_QUEUE_GRAPHICS_BIT) && !(eQueueFlags & VK_QUEUE_COMPUTE_BIT))
            {
                psGPU_EXT_Physical_Device->m_auiVLKN_Queue_Family_Index[ETgKN_GPU_EXT_COMMAND_TRANSFER] = uiQueue_Family;
                bTransferFound = true;
                continue;
            };

            /* Check for present support (prefer dedicated)*/
            bPresentSupport = false;
            eResult = vkGetPhysicalDeviceSurfaceSupportKHR(psGPU_EXT_Physical_Device->m_hVLKN_Physical_Device, uiQueue_Family,
                g_sKN_GPU_EXT_CXT_HOST.m_hVLKN_Temp_Surface, &bPresentSupport);
            if (!bPresentFound && (VK_SUCCESS == eResult) && bPresentSupport && (bGraphicsFound || !(eQueueFlags & VK_QUEUE_GRAPHICS_BIT)))
            {
                psGPU_EXT_Physical_Device->m_auiVLKN_Queue_Family_Index[ETgKN_GPU_EXT_COMMAND_PRESENT] = uiQueue_Family;
                bPresentFound = true;
                continue;
            };

            /* Check for graphics queue */
            if (!bGraphicsFound && (eQueueFlags & VK_QUEUE_GRAPHICS_BIT))
            {
                psGPU_EXT_Physical_Device->m_auiVLKN_Queue_Family_Index[ETgKN_GPU_EXT_COMMAND_GRAPHICS] = uiQueue_Family;
                bGraphicsFound = true;
                if ((VK_SUCCESS == eResult) && bPresentSupport)
                {
                    psGPU_EXT_Physical_Device->m_auiVLKN_Queue_Family_Index[ETgKN_GPU_EXT_COMMAND_PRESENT] = uiQueue_Family;
                    bGraphicsSupportPresent = true;
                };
            };
        };

        /* Fall back to graphics queue for compute if no dedicated compute queue */
        if (!bComputeFound && bGraphicsFound)
        {
            psGPU_EXT_Physical_Device->m_auiVLKN_Queue_Family_Index[ETgKN_GPU_EXT_COMMAND_COMPUTE] = psGPU_EXT_Physical_Device->m_auiVLKN_Queue_Family_Index[ETgKN_GPU_EXT_COMMAND_GRAPHICS];
        };

        /* Fall back to graphics queue for transfer if no dedicated transfer queue */
        if (!bTransferFound && bGraphicsFound)
        {
            psGPU_EXT_Physical_Device->m_auiVLKN_Queue_Family_Index[ETgKN_GPU_EXT_COMMAND_TRANSFER] = psGPU_EXT_Physical_Device->m_auiVLKN_Queue_Family_Index[ETgKN_GPU_EXT_COMMAND_GRAPHICS];
        };

        /* Must have at least a graphics queue and present support */
        if (!bGraphicsFound || (!bPresentFound && !bGraphicsSupportPresent))
        {
            TgERROR_MSGF( 0, STD_MSG_LITERAL_0, STD_MSG_POST, u8"Failed to find support for Graphics and/or Present Queues" );
            tgKN_GPU_EXT_Physical_Device_Free( g_sKN_GPU_CXT_HOST.m_nuiPhysical_Device );
            return (nullptr);
        };
    }

    /* Check for required features --------------------------------------------------------------------------------------------------------------------------------------- */

    /* Discrete GPUs have a significant performance advantage */
    if (VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU != psGPU_EXT_Physical_Device->m_sVLKN_Properties.deviceType)
    {
        TgERROR_MSGF( 0, STD_MSG_LITERAL_0, STD_MSG_POST, u8"Failed to find support for Discrete GPUs" );
        tgKN_GPU_EXT_Physical_Device_Free( g_sKN_GPU_CXT_HOST.m_nuiPhysical_Device );
        return (nullptr);
    };

    /* We require geometry shader support */
    if (!psGPU_EXT_Physical_Device->m_sVLKN_Features.features.geometryShader)
    {
        TgERROR_MSGF( 0, STD_MSG_LITERAL_0, STD_MSG_POST, u8"Failed to find support for Geometry Shaders" );
        tgKN_GPU_EXT_Physical_Device_Free( g_sKN_GPU_CXT_HOST.m_nuiPhysical_Device );
        return (nullptr);
    };

    /* We require Vulkan 1.3 */
    if (psGPU_EXT_Physical_Device->m_sVLKN_Properties.apiVersion < VK_API_VERSION_1_3)
    {
        TgERROR_MSGF( 0, STD_MSG_LITERAL_0, STD_MSG_POST, u8"Failed to find support for Vulkan 1.3 or higher" );
        tgKN_GPU_EXT_Physical_Device_Free( g_sKN_GPU_CXT_HOST.m_nuiPhysical_Device );
        return (nullptr);
    };

    /* Check for required extensions ------------------------------------------------------------------------------------------------------------------------------------- */
    if (g_nuiKN_GPU_EXT_Device_Extensions > 0)
    {
        TgUINT_E32                          nuiFound_Extension;
        VkExtensionProperties_P             psAvailable_Extensions;
        TgRSIZE                             uiVLKN_Device_Extension, uiFound_Extension;

        vkEnumerateDeviceExtensionProperties(psGPU_EXT_Physical_Device->m_hVLKN_Physical_Device, nullptr, &nuiFound_Extension, nullptr);
        if (nuiFound_Extension == 0)
        {
            tgKN_GPU_EXT_Physical_Device_Free( g_sKN_GPU_CXT_HOST.m_nuiPhysical_Device );
            return (nullptr);
        };

        psAvailable_Extensions = (VkExtensionProperties*)TgMALLOC_TEMP(nuiFound_Extension * sizeof(VkExtensionProperties));
        if (nullptr == psAvailable_Extensions)
        {
            tgKN_GPU_EXT_Physical_Device_Free( g_sKN_GPU_CXT_HOST.m_nuiPhysical_Device );
            return (nullptr);
        }
        vkEnumerateDeviceExtensionProperties(psGPU_EXT_Physical_Device->m_hVLKN_Physical_Device, nullptr, &nuiFound_Extension, psAvailable_Extensions);

        for (uiVLKN_Device_Extension = 0; uiVLKN_Device_Extension < g_nuiKN_GPU_EXT_Device_Extensions; ++uiVLKN_Device_Extension)
        {
            /* Check if the extension is available. */
            for (uiFound_Extension = 0; uiFound_Extension < nuiFound_Extension; ++uiFound_Extension)
            {
                TgSINT_E08                          iRet;

                if (TgSUCCEEDED(tgNSZ_Compare(&iRet, psAvailable_Extensions[uiFound_Extension].extensionName, KTgMAX_RSIZE, 0,
                                              g_apszKN_GPU_EXT_Device_Extensions[uiVLKN_Device_Extension], KTgMAX_RSIZE, 0)) && (0 == iRet))
                {
                    break;
                };
            };

            /* If we didn't find the extension, fail. */
            if (uiFound_Extension >= nuiFound_Extension)
            {
                break;
            };
        };

        TgFREE_TEMP(psAvailable_Extensions);

        /* If we didn't find all the extensions, fail. */
        if (uiVLKN_Device_Extension < g_nuiKN_GPU_EXT_Device_Extensions)
        {
            TgERROR_MSGF( 0, STD_MSG_LITERAL_0, STD_MSG_POST, u8"Failed to find support for all required device extensions" );
            tgKN_GPU_EXT_Physical_Device_Free( g_sKN_GPU_CXT_HOST.m_nuiPhysical_Device );
            return (nullptr);
        };
    };

    /* Query supported formats ------------------------------------------------------------------------------------------------------------------------------------------- */
    
    eResult = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(psGPU_EXT_Physical_Device->m_hVLKN_Physical_Device, g_sKN_GPU_EXT_CXT_HOST.m_hVLKN_Temp_Surface,
                                                        &psGPU_EXT_Physical_Device->m_sVLKN_Surface_Capabilities);
    if (VK_SUCCESS != eResult)
    {
        tgKN_GPU_EXT_Physical_Device_Free( g_sKN_GPU_CXT_HOST.m_nuiPhysical_Device );
        TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to get surface capabilities" );
        TgDEBUG_BREAK_AND_RETURN( nullptr );
    };

    /* Get surface formats */

    eResult = vkGetPhysicalDeviceSurfaceFormatsKHR(psGPU_EXT_Physical_Device->m_hVLKN_Physical_Device, g_sKN_GPU_EXT_CXT_HOST.m_hVLKN_Temp_Surface, &uiVkUint32, nullptr);
    if (VK_SUCCESS != eResult)
    {
        tgKN_GPU_EXT_Physical_Device_Free( g_sKN_GPU_CXT_HOST.m_nuiPhysical_Device );
        TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to get surface formats" );
        TgDEBUG_BREAK_AND_RETURN( nullptr );
    };
    psGPU_EXT_Physical_Device->m_nuiVLKN_Surface_Format = uiVkUint32;

    psGPU_EXT_Physical_Device->m_psVLKN_Surface_Format = (VkSurfaceFormatKHR_P)TgMALLOC_POOL(sizeof(VkSurfaceFormatKHR) * uiVkUint32);
    if (nullptr == psGPU_EXT_Physical_Device->m_psVLKN_Surface_Format)
    {
        tgKN_GPU_EXT_Physical_Device_Free( g_sKN_GPU_CXT_HOST.m_nuiPhysical_Device );
        TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to allocate memory for surface formats" );
        return (nullptr);
    };

    eResult = vkGetPhysicalDeviceSurfaceFormatsKHR( psGPU_EXT_Physical_Device->m_hVLKN_Physical_Device, g_sKN_GPU_EXT_CXT_HOST.m_hVLKN_Temp_Surface, &uiVkUint32,
                                                    psGPU_EXT_Physical_Device->m_psVLKN_Surface_Format);
    if (VK_SUCCESS != eResult)
    {
        tgKN_GPU_EXT_Physical_Device_Free( g_sKN_GPU_CXT_HOST.m_nuiPhysical_Device );
        TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to get surface formats" );
        return (nullptr);
    };

    /* Get surface present modes */

    eResult = vkGetPhysicalDeviceSurfacePresentModesKHR(psGPU_EXT_Physical_Device->m_hVLKN_Physical_Device, g_sKN_GPU_EXT_CXT_HOST.m_hVLKN_Temp_Surface, &uiVkUint32, nullptr);
    if (VK_SUCCESS != eResult)
    {
        tgKN_GPU_EXT_Physical_Device_Free( g_sKN_GPU_CXT_HOST.m_nuiPhysical_Device );
        TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to get surface formats" );
        TgDEBUG_BREAK_AND_RETURN( nullptr );
    };
    psGPU_EXT_Physical_Device->m_nuiVLKN_Present_Mode = uiVkUint32;

    psGPU_EXT_Physical_Device->m_psVLKN_Present_Mode = (VkPresentModeKHR_P)TgMALLOC_POOL(sizeof(VkPresentModeKHR) * uiVkUint32);
    if (nullptr == psGPU_EXT_Physical_Device->m_psVLKN_Present_Mode)
    {
        tgKN_GPU_EXT_Physical_Device_Free( g_sKN_GPU_CXT_HOST.m_nuiPhysical_Device );
        TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to allocate memory for surface present modes" );
        return (nullptr);
    };

    eResult = vkGetPhysicalDeviceSurfacePresentModesKHR( psGPU_EXT_Physical_Device->m_hVLKN_Physical_Device, g_sKN_GPU_EXT_CXT_HOST.m_hVLKN_Temp_Surface, &uiVkUint32,
                                                         psGPU_EXT_Physical_Device->m_psVLKN_Present_Mode);
    if (VK_SUCCESS != eResult)
    {
        tgKN_GPU_EXT_Physical_Device_Free( g_sKN_GPU_CXT_HOST.m_nuiPhysical_Device );
        TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to get surface present modes" );
        return (nullptr);
    };

    /* Create device ----------------------------------------------------------------------------------------------------------------------------------------------------- */

    {
        VkDeviceQueueCreateInfo             asQueueCreateInfos[KTgKN_GPU_VLKN_MAX_QUEUE_FAMILY];
        TgUINT_E32                          nuiUniqueQueueFamilies;

        VkPhysicalDeviceMeshShaderFeaturesEXT sMeshShaderFeatures;
        VkPhysicalDeviceRobustness2FeaturesEXT sRobustness2Features;
        VkPhysicalDeviceVulkan14Features    sDevice_Features14;
        VkPhysicalDeviceVulkan13Features    sDevice_Features13;
        VkPhysicalDeviceVulkan12Features    sDevice_Features12;
        VkPhysicalDeviceVulkan11Features    sDevice_Features11;
        VkPhysicalDeviceFeatures2           sDevice_Features;
        VkDeviceCreateInfo                  sCreateInfo;
        TgFLOAT32                           fQueuePriority;

        nuiUniqueQueueFamilies = 0;
        fQueuePriority = 1.0f;

        psGPU_EXT_Physical_Device->m_auiUnique_Queue_Family_Index[nuiUniqueQueueFamilies] = psGPU_EXT_Physical_Device->m_auiVLKN_Queue_Family_Index[ETgKN_GPU_EXT_COMMAND_GRAPHICS];
        ++psGPU_EXT_Physical_Device->m_nuiUnique_Queue_Family;

        asQueueCreateInfos[nuiUniqueQueueFamilies].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        asQueueCreateInfos[nuiUniqueQueueFamilies].pNext = nullptr;
        asQueueCreateInfos[nuiUniqueQueueFamilies].flags = 0;
        asQueueCreateInfos[nuiUniqueQueueFamilies].queueFamilyIndex = (TgUINT_E32)psGPU_EXT_Physical_Device->m_auiVLKN_Queue_Family_Index[ETgKN_GPU_EXT_COMMAND_GRAPHICS];
        asQueueCreateInfos[nuiUniqueQueueFamilies].queueCount = 1;
        asQueueCreateInfos[nuiUniqueQueueFamilies].pQueuePriorities = &fQueuePriority;
        ++nuiUniqueQueueFamilies;

        if (bPresentFound)
        {
            psGPU_EXT_Physical_Device->m_auiUnique_Queue_Family_Index[nuiUniqueQueueFamilies] = psGPU_EXT_Physical_Device->m_auiVLKN_Queue_Family_Index[ETgKN_GPU_EXT_COMMAND_PRESENT];
            ++psGPU_EXT_Physical_Device->m_nuiUnique_Queue_Family;

            asQueueCreateInfos[nuiUniqueQueueFamilies].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            asQueueCreateInfos[nuiUniqueQueueFamilies].pNext = nullptr;
            asQueueCreateInfos[nuiUniqueQueueFamilies].flags = 0;
            asQueueCreateInfos[nuiUniqueQueueFamilies].queueFamilyIndex = (TgUINT_E32)psGPU_EXT_Physical_Device->m_auiVLKN_Queue_Family_Index[ETgKN_GPU_EXT_COMMAND_PRESENT];
            asQueueCreateInfos[nuiUniqueQueueFamilies].queueCount = 1;
            asQueueCreateInfos[nuiUniqueQueueFamilies].pQueuePriorities = &fQueuePriority;
            ++nuiUniqueQueueFamilies;
        };

        if (bComputeFound)
        {
            psGPU_EXT_Physical_Device->m_auiUnique_Queue_Family_Index[nuiUniqueQueueFamilies] = psGPU_EXT_Physical_Device->m_auiVLKN_Queue_Family_Index[ETgKN_GPU_EXT_COMMAND_COMPUTE];
            ++psGPU_EXT_Physical_Device->m_nuiUnique_Queue_Family;

            asQueueCreateInfos[nuiUniqueQueueFamilies].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            asQueueCreateInfos[nuiUniqueQueueFamilies].pNext = nullptr;
            asQueueCreateInfos[nuiUniqueQueueFamilies].flags = 0;
            asQueueCreateInfos[nuiUniqueQueueFamilies].queueFamilyIndex = (TgUINT_E32)psGPU_EXT_Physical_Device->m_auiVLKN_Queue_Family_Index[ETgKN_GPU_EXT_COMMAND_COMPUTE];
            asQueueCreateInfos[nuiUniqueQueueFamilies].queueCount = 1;
            asQueueCreateInfos[nuiUniqueQueueFamilies].pQueuePriorities = &fQueuePriority;
            ++nuiUniqueQueueFamilies;
        };

        if (bTransferFound)
        {
            psGPU_EXT_Physical_Device->m_auiUnique_Queue_Family_Index[nuiUniqueQueueFamilies] = psGPU_EXT_Physical_Device->m_auiVLKN_Queue_Family_Index[ETgKN_GPU_EXT_COMMAND_TRANSFER];
            ++psGPU_EXT_Physical_Device->m_nuiUnique_Queue_Family;

            asQueueCreateInfos[nuiUniqueQueueFamilies].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            asQueueCreateInfos[nuiUniqueQueueFamilies].pNext = nullptr;
            asQueueCreateInfos[nuiUniqueQueueFamilies].flags = 0;
            asQueueCreateInfos[nuiUniqueQueueFamilies].queueFamilyIndex = (TgUINT_E32)psGPU_EXT_Physical_Device->m_auiVLKN_Queue_Family_Index[ETgKN_GPU_EXT_COMMAND_TRANSFER];
            asQueueCreateInfos[nuiUniqueQueueFamilies].queueCount = 1;
            asQueueCreateInfos[nuiUniqueQueueFamilies].pQueuePriorities = &fQueuePriority;
            ++nuiUniqueQueueFamilies;
        };

        /* Enable required features  - This will need to be driven by a configuration or platform code. For HMDs, geometry shader etc. are not required.*/

        // Enable Mesh Shader features
        tgMM_Set_U08_0x00(&sMeshShaderFeatures, sizeof(sMeshShaderFeatures));
        sMeshShaderFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MESH_SHADER_FEATURES_EXT;
        sMeshShaderFeatures.taskShader = VK_TRUE;
        sMeshShaderFeatures.meshShader = VK_TRUE;

        // Enable Robustness2 features
        tgMM_Set_U08_0x00(&sRobustness2Features, sizeof(sRobustness2Features));
        sRobustness2Features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ROBUSTNESS_2_FEATURES_EXT;
        sRobustness2Features.pNext = &sMeshShaderFeatures;  // Chain to mesh shader features
        sRobustness2Features.robustBufferAccess2 = VK_TRUE;
        sRobustness2Features.robustImageAccess2 = VK_TRUE;
        sRobustness2Features.nullDescriptor = VK_TRUE;

        // Enable Vulkan 1.4 features
        tgMM_Set_U08_0x00(&sDevice_Features14, sizeof(sDevice_Features14));
        sDevice_Features14.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_4_FEATURES;
        sDevice_Features14.pNext = &sRobustness2Features;  // Chain to robustness2 features
        sDevice_Features14.pushDescriptor = VK_TRUE;
        sDevice_Features14.dynamicRenderingLocalRead = VK_TRUE;

        // Enable Vulkan 1.3 features
        tgMM_Set_U08_0x00(&sDevice_Features13, sizeof(sDevice_Features13));
        sDevice_Features13.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES;
        sDevice_Features13.pNext = &sDevice_Features14;  // Chain to 1.4 features
        sDevice_Features13.dynamicRendering = VK_TRUE;
        sDevice_Features13.synchronization2 = VK_TRUE;
        sDevice_Features13.maintenance4 = VK_TRUE;
        sDevice_Features13.shaderDemoteToHelperInvocation = VK_TRUE;

        // Enable Vulkan 1.2 features (including timeline semaphores)
        tgMM_Set_U08_0x00(&sDevice_Features12, sizeof(sDevice_Features12));
        sDevice_Features12.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES;
        sDevice_Features12.pNext = &sDevice_Features13;  // Chain to 1.3 features
        sDevice_Features12.timelineSemaphore = VK_TRUE;
        sDevice_Features12.bufferDeviceAddress = VK_TRUE;
        sDevice_Features12.descriptorIndexing = VK_TRUE;
        sDevice_Features12.descriptorBindingPartiallyBound = VK_TRUE;
        sDevice_Features12.runtimeDescriptorArray = VK_TRUE;
        sDevice_Features12.descriptorBindingVariableDescriptorCount = VK_TRUE;
        sDevice_Features12.shaderSampledImageArrayNonUniformIndexing = VK_TRUE;
        sDevice_Features12.shaderUniformBufferArrayNonUniformIndexing = VK_TRUE;
        sDevice_Features12.shaderStorageBufferArrayNonUniformIndexing = VK_TRUE;
        sDevice_Features12.descriptorBindingSampledImageUpdateAfterBind = VK_TRUE;
        sDevice_Features12.descriptorBindingUniformBufferUpdateAfterBind = VK_TRUE;
        sDevice_Features12.descriptorBindingStorageBufferUpdateAfterBind = VK_TRUE;
        sDevice_Features12.descriptorBindingPartiallyBound = VK_TRUE;
        sDevice_Features12.vulkanMemoryModel = VK_TRUE;
        sDevice_Features12.vulkanMemoryModelDeviceScope = VK_TRUE;
        sDevice_Features12.storageBuffer8BitAccess = VK_TRUE;
        sDevice_Features12.hostQueryReset = VK_TRUE;


        // Enable Vulkan 1.1 features
        tgMM_Set_U08_0x00(&sDevice_Features11, sizeof(sDevice_Features11));
        sDevice_Features11.pNext = &sDevice_Features12;  // Chain to 1.2 features
        sDevice_Features11.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_FEATURES;

        tgMM_Set_U08_0x00( &sDevice_Features, sizeof( sDevice_Features ) );
        sDevice_Features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
        sDevice_Features.pNext = &sDevice_Features11;  // Chain to 1.1 features
        sDevice_Features.features.robustBufferAccess = VK_TRUE;
        sDevice_Features.features.geometryShader = VK_TRUE;
        sDevice_Features.features.tessellationShader = VK_TRUE;
        sDevice_Features.features.samplerAnisotropy = VK_TRUE;
        sDevice_Features.features.fillModeNonSolid = VK_TRUE;
        sDevice_Features.features.wideLines = VK_TRUE;
        sDevice_Features.features.shaderClipDistance = VK_TRUE;
        sDevice_Features.features.shaderCullDistance = VK_TRUE;
        sDevice_Features.features.pipelineStatisticsQuery = VK_TRUE;
        sDevice_Features.features.fragmentStoresAndAtomics = VK_TRUE;
        sDevice_Features.features.vertexPipelineStoresAndAtomics = VK_TRUE;
        sDevice_Features.features.shaderInt64 = VK_TRUE;
        sDevice_Features.features.fragmentStoresAndAtomics = VK_TRUE;

        /* Create logical device */

        tgMM_Set_U08_0x00( &sCreateInfo, sizeof( sCreateInfo ) );
        sCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        sCreateInfo.pNext = &sDevice_Features;
        sCreateInfo.queueCreateInfoCount = nuiUniqueQueueFamilies;
        sCreateInfo.pQueueCreateInfos = asQueueCreateInfos;
        sCreateInfo.enabledExtensionCount = (TgUINT_E32)g_nuiKN_GPU_EXT_Device_Extensions;
        sCreateInfo.ppEnabledExtensionNames = (TgCHAR_NC_CPCP)g_apszKN_GPU_EXT_Device_Extensions;
        sCreateInfo.enabledLayerCount = g_sKN_GPU_EXT_CXT_HOST.m_bValidation_Enabled ? (TgUINT_E32)g_nuiKN_GPU_EXT_Validation_Layers : 0;
        sCreateInfo.ppEnabledLayerNames = g_sKN_GPU_EXT_CXT_HOST.m_bValidation_Enabled ? (TgCHAR_NC_CPCP)g_apszKN_GPU_EXT_Validation_Layers : nullptr;

        eResult = vkCreateDevice(psGPU_EXT_Physical_Device->m_hVLKN_Physical_Device, &sCreateInfo, g_psKN_GPU_VLKN_Allocator, &psGPU_EXT_Physical_Device->m_hVLKN_Device);
        if (eResult != VK_SUCCESS)
        {
            TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create logical device" );
            tgKN_GPU_EXT_Physical_Device_Free( g_sKN_GPU_CXT_HOST.m_nuiPhysical_Device );
            return (nullptr);
        }

        /* Load device-specific function pointers using volk */
        volkLoadDevice(psGPU_EXT_Physical_Device->m_hVLKN_Device);
    }

    /* Check for multi-sample support using Vulkan ----------------------------------------------------------------------------------------------------------------------- */

    for (iFormat = 0; iFormat < KTgKN_GPU_EXT_FORMAT_RT_SCANOUT_MAX; ++iFormat)
    {
        TgSINT_E32                          iMS;
        VkImageFormatProperties             sImageFormatProps;
        VkFormat                            eVkFormat;

        /* Convert to Vulkan format */
        eVkFormat = (VkFormat)KTgKN_GPU_EXT_FORMAT_RT_SCANOUT[iFormat];

        for (iMS = 0; iMS < KTgKN_GPU_MS__MAX; ++iMS)
        {
            VkSampleCountFlags                  eSampleCount = (VkSampleCountFlags)(1 << iMS);

            /* Check if this sample count is supported for this format */
            eResult = vkGetPhysicalDeviceImageFormatProperties(
                psGPU_EXT_Physical_Device->m_hVLKN_Physical_Device,
                eVkFormat,
                VK_IMAGE_TYPE_2D,
                VK_IMAGE_TILING_OPTIMAL,
                VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
                0,
                &sImageFormatProps
            );

            if ((VK_SUCCESS == eResult) && (sImageFormatProps.sampleCounts & eSampleCount))
            {
                /* Vulkan doesn't have quality levels like D3D12, so we set to 1 if supported */
                psGPU_EXT_Physical_Device->m_auiMS[iFormat][iMS] = 1;
            }
            else
            {
                psGPU_EXT_Physical_Device->m_auiMS[iFormat][iMS] = 0;
            };
        };
    };

    if (TgFAILED(tgKN_GPU_EXT_Enumerate__Physical_Device_Output( psGPU_EXT_Physical_Device )))
    {
        tgKN_GPU_EXT_Physical_Device_Free( g_sKN_GPU_CXT_HOST.m_nuiPhysical_Device );
        return (nullptr);
    };

    TgERROR(KTgKN_GPU_CXT_DEVC_ID__INVALID.m_uiKI == psGPU_EXT_Physical_Device->m_tiID_DEVC.m_uiKI);
    ++g_sKN_GPU_CXT_HOST.m_nuiPhysical_Device;

    return (psGPU_EXT_Physical_Device);
}


/* ---- tgKN_GPU_EXT_Enumerate__Physical_Device_Output --------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT tgKN_GPU_EXT_Enumerate__Physical_Device_Output( STg2_KN_GPU_VLKN_Physical_Device_PCU psGPU_EXT_Physical_Device )
{
    TgUINT_E32                          nuiDisplay_Output;
    VkResult                            iResult;

    TgPARAM_CHECK(nullptr != psGPU_EXT_Physical_Device);

    iResult = vkGetPhysicalDeviceDisplayPropertiesKHR(psGPU_EXT_Physical_Device->m_hVLKN_Physical_Device, &nuiDisplay_Output, nullptr);
    if (iResult == VK_SUCCESS && nuiDisplay_Output > 0)
    {
        TgUINT_E32                          uiDisplay_Output, nuiDisplay_Mode;
        VkDisplayPropertiesKHR_P            pDisplay_Properties;

        pDisplay_Properties = (VkDisplayPropertiesKHR_P)TgMALLOC_TEMP(nuiDisplay_Output * sizeof(VkDisplayPropertiesKHR));
        if (nullptr == pDisplay_Properties)
        {
            return KTgE_MEM_ALLOC_FAIL;
        };
        vkGetPhysicalDeviceDisplayPropertiesKHR(psGPU_EXT_Physical_Device->m_hVLKN_Physical_Device, &nuiDisplay_Output, pDisplay_Properties);

        for (uiDisplay_Output = 0; uiDisplay_Output < nuiDisplay_Output && g_sKN_GPU_CXT_HOST.m_nuiDisplay_Output < KTgKN_GPU_MAX_OUTPUT; ++uiDisplay_Output)
        {
            STg2_KN_GPU_VLKN_Display_Output_PC  psGPU_EXT_Display_Output = g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Display_Output + g_sKN_GPU_CXT_HOST.m_nuiDisplay_Output;

            TgPARAM_CHECK(nullptr == psGPU_EXT_Display_Output->m_psVLKN_Display_Mode_Properties);
            TgPARAM_CHECK(0 == psGPU_EXT_Display_Output->m_nuiVLKN_Display_Mode);

            // Enumerate display modes
            vkGetDisplayModePropertiesKHR(psGPU_EXT_Physical_Device->m_hVLKN_Physical_Device, pDisplay_Properties[uiDisplay_Output].display, &nuiDisplay_Mode, nullptr);
            if (0 == psGPU_EXT_Display_Output->m_nuiVLKN_Display_Mode)
            {
                continue;
            };

            psGPU_EXT_Display_Output->m_psVLKN_Display_Mode_Properties = (VkDisplayModePropertiesKHR_P)TgMALLOC_POOL(nuiDisplay_Mode * sizeof(VkDisplayModePropertiesKHR));
            if (nullptr == psGPU_EXT_Display_Output->m_psVLKN_Display_Mode_Properties)
            {
                TgFREE_TEMP(pDisplay_Properties);
                tgKN_GPU_EXT_Display_Output_Free( g_sKN_GPU_CXT_HOST.m_nuiDisplay_Output );
                return KTgE_MEM_ALLOC_FAIL;
            };

            psGPU_EXT_Display_Output->m_sVLKN_Display_Properties = pDisplay_Properties[uiDisplay_Output];
            psGPU_EXT_Display_Output->m_nuiVLKN_Display_Mode = nuiDisplay_Mode;

            vkGetDisplayModePropertiesKHR(psGPU_EXT_Physical_Device->m_hVLKN_Physical_Device,
                                        pDisplay_Properties[uiDisplay_Output].display,
                                        &nuiDisplay_Mode,
                                        psGPU_EXT_Display_Output->m_psVLKN_Display_Mode_Properties);
            ++g_sKN_GPU_CXT_HOST.m_nuiDisplay_Output;
        };
        TgFREE_TEMP(pDisplay_Properties);
    };

    return KTgS_OK;
}


/* ---- tgKN_GPU_EXT_Enumerate__Populate_Module ---------------------------------------------------------------------------------------------------------------------------------- */
TgCOMPILER_ASSERT( TgARRAY_COUNT(KTgKN_GPU_EXT_FORMAT_RT_SCANOUT) < KTgMAX_U08, 0 );
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgKN_GPU_EXT_Enumerate__Populate_Module( TgVOID )
{
    TgRSIZE                             uiPhysical_Device, uiRT_Format, uiDisplay_Output;
    TgCHAR_WC                           wszDisplay_Name[1024];

    for (uiPhysical_Device = 0; uiPhysical_Device < g_sKN_GPU_CXT_HOST.m_nuiPhysical_Device; ++uiPhysical_Device)
    {
        tgCN_PrintF( KTgCN_CHANEL_INITIALIZE | KTgCN_SEVERITY_9, u8"%-16.16s(%-48.48s): Physical_Device: %d\n", u8"Kernel", u8"tgKN_GPU_EXT_Enumerate", uiPhysical_Device );

    #if TgS_STAT__KERNEL || TgS_DEBUG__KERNEL
        tgKN_GPU_EXT_Enumerate__Physical_Device_Output( g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Physical_Device + uiPhysical_Device );
    #endif

        tgUSZ_Copy( g_sKN_GPU_CXT_HOST.m_asPhysical_Device[uiPhysical_Device].m_szPhysical_Device,
                    TgARRAY_COUNT( g_sKN_GPU_CXT_HOST.m_asPhysical_Device[uiPhysical_Device].m_szPhysical_Device ),
                    (TgCHAR_U8_CP)g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Physical_Device[uiPhysical_Device].m_sVLKN_Properties.deviceName,
                    TgARRAY_COUNT( g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Physical_Device[uiPhysical_Device].m_sVLKN_Properties.deviceName ) );

        g_sKN_GPU_CXT_HOST.m_asPhysical_Device[uiPhysical_Device].m_idxCXT_HOST_Physical_Device = (TgUINT_E32)uiPhysical_Device;
        g_sKN_GPU_CXT_HOST.m_asPhysical_Device[uiPhysical_Device].m_nuiNode = 1; /* Vulkan physical devices typically represent a single node */

        /* Cache the present formats supported by the physical device */
        for (uiRT_Format = 0; uiRT_Format < KTgKN_GPU_EXT_FORMAT_RT_SCANOUT_MAX; ++uiRT_Format)
        {
            VkFormatProperties                   sVLKN_Format_Properties;
            VkFormat                             enVLKN_Format;

            enVLKN_Format = (VkFormat)KTgKN_GPU_EXT_FORMAT_RT_SCANOUT[uiRT_Format];
            TgDIAG( VK_FORMAT_UNDEFINED != enVLKN_Format );

            vkGetPhysicalDeviceFormatProperties( g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Physical_Device[uiPhysical_Device].m_hVLKN_Physical_Device,
                                                 enVLKN_Format, &sVLKN_Format_Properties );

            /* Check if format supports color attachment (render target) or can be used for presentation */
            if ((sVLKN_Format_Properties.optimalTilingFeatures & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT) ||
                (sVLKN_Format_Properties.linearTilingFeatures & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT))
            {
                tgBF_Set_Flag_U64( &g_sKN_GPU_CXT_HOST.m_asPhysical_Device[uiPhysical_Device].m_uiSupport_Flags, (TgUINT_E08)(uiRT_Format), true );
            };
        };
    };

    for (uiDisplay_Output = 0; uiDisplay_Output < g_sKN_GPU_CXT_HOST.m_nuiDisplay_Output; ++uiDisplay_Output)
    {
        STg2_KN_GPU_VLKN_Display_Output_PC  psEXT_Display_Output = g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Display_Output + uiDisplay_Output;
        STg2_KN_GPU_Display_Output_PC       psDisplay_Output = g_sKN_GPU_CXT_HOST.m_asDisplay_Output + uiDisplay_Output;

        tgUSZ_Copy( psDisplay_Output->m_szName, TgARRAY_COUNT( psDisplay_Output->m_szName ),
                    (TgCHAR_U8_CP)psEXT_Display_Output->m_sVLKN_Display_Properties.displayName, KTgMAX_RSIZE );
        tgWSZ_Convert_USZ( wszDisplay_Name, TgARRAY_COUNT( wszDisplay_Name ), (TgCHAR_U8_CP)psEXT_Display_Output->m_sVLKN_Display_Properties.displayName, KTgMAX_RSIZE );
    };
}
