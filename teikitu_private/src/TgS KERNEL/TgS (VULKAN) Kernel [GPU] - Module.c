/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (VULKAN) Kernel [GPU] - Module.c
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
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

static TgRESULT
tgKN_GPU_EXT_Create_Instance( TgVOID );

static TgVOID
tgKN_GPU_EXT_Destroy_Instance( TgVOID );

#if defined(TgS_DEBUG__KERNEL_GPU) && TgS_DEBUG__KERNEL_GPU
static VkBool32 VKAPI_PTR
tgKN_GPU_EXT_Debug_Callback( 
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageTypes, VkDebugUtilsMessengerCallbackDataEXT_CP pCallbackData,
    TgVOID_P pUserData);
/*# defined(TgS_DEBUG__KERNEL_GPU) && TgS_DEBUG__KERNEL_GPU */
#endif

// static TgVOID_P VKAPI_CALL
// tgKN_GPU_VLKN_Custom_Allocation(
//     TgVOID_P pUserData, size_t uiSize, size_t uiAlignment, VkSystemAllocationScope enVLKN_Allocation_Scope );

// static TgVOID_P VKAPI_CALL
// tgKN_GPU_VLKN_Custom_Reallocation(
//     TgVOID_P pUserData, TgVOID_P pOriginal, size_t uiSize, size_t uiAlignment, VkSystemAllocationScope enVLKN_Allocation_Scope );

// static void VKAPI_CALL
// tgKN_GPU_VLKN_Custom_Free(
//     TgVOID_P pUserData, TgVOID_P pMemory );

// static void VKAPI_CALL
// tgKN_GPU_VLKN_Internal_Allocation_Notification(
//     TgVOID_P pUserData, size_t uiSize, VkInternalAllocationType enVLKN_Allocation_Type, VkSystemAllocationScope enVLKN_Allocation_Scope );

// static void VKAPI_CALL
// tgKN_GPU_VLKN_Internal_Free_Notification(
//     TgVOID_P pUserData, size_t uiSize, VkInternalAllocationType enVLKN_Allocation_Type, VkSystemAllocationScope enVLKN_Allocation_Scope );

                                    /* Using the current memory functions is too slow */
static VkAllocationCallbacks_C      s_sKN_GPU_VLKN_Allocator = {
                                        .pUserData = nullptr,
                                        .pfnAllocation = nullptr /* tgKN_GPU_VLKN_Custom_Allocation */,
                                        .pfnReallocation = nullptr /* tgKN_GPU_VLKN_Custom_Reallocation */,
                                        .pfnFree = nullptr /* tgKN_GPU_VLKN_Custom_Free */,
                                        .pfnInternalAllocation = nullptr /* tgKN_GPU_VLKN_Internal_Allocation_Notification */,
                                        .pfnInternalFree = nullptr /* tgKN_GPU_VLKN_Internal_Free_Notification */
                                    };




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Data                                                                                                                                                                    */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

VkAllocationCallbacks_CPC           g_psKN_GPU_VLKN_Allocator = nullptr; // &s_sKN_GPU_VLKN_Allocator;




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_GPU_EXT_Module_Init ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_EXT_Module_Init( TgVOID )
{
    TgRSIZE                             uiIndex;

    (void)s_sKN_GPU_VLKN_Allocator;

    if (TgFAILED(tgKN_OS_GPU_API_Module_Init()))
    {
        return (KTgE_FAIL);
    };

    tgMM_Set_U08_0x00( &g_sKN_GPU_EXT_CXT_HOST, sizeof( g_sKN_GPU_EXT_CXT_HOST ) );
    tgMM_Set_U08_0x00( &g_asKN_GPU_EXT_CXT_DEVC, sizeof( g_asKN_GPU_EXT_CXT_DEVC ) );
    tgMM_Set_U08_0x00( &g_asKN_GPU_EXT_CXT_EXEC, sizeof( g_asKN_GPU_EXT_CXT_EXEC ) );
    tgMM_Set_U08_0x00( &g_asKN_GPU_EXT_CXT_SWAP, sizeof( g_asKN_GPU_EXT_CXT_SWAP ) );

    for (uiIndex = 0; uiIndex < KTgKN_GPU_MAX_PHYSICAL_DEVICE; ++uiIndex)
    {
        g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Physical_Device[uiIndex].m_tiID_DEVC = KTgKN_GPU_CXT_DEVC_ID__INVALID;
    };

    for (uiIndex = 0; uiIndex < KTgKN_GPU_MAX_DEVC_CONTEXT; ++uiIndex)
    {
        g_asKN_GPU_EXT_CXT_DEVC[uiIndex].m_tiID = KTgKN_GPU_CXT_DEVC_ID__INVALID;
    };

    for (uiIndex = 0; uiIndex < KTgKN_GPU_MAX_EXEC_CONTEXT; ++uiIndex)
    {
        g_asKN_GPU_EXT_CXT_EXEC[uiIndex].m_tiCXT_EXEC = KTgKN_GPU_CXT_EXEC_ID__INVALID;
    };

    for (uiIndex = 0; uiIndex < KTgKN_GPU_MAX_SWAP_CONTEXT; ++uiIndex)
    {
        g_asKN_GPU_EXT_CXT_SWAP[uiIndex].m_tiID = KTgKN_GPU_CXT_SWAP_ID__INVALID;
    };

    if (TgFAILED(tgKN_GPU_EXT_Create_Instance()))
    {
        return (KTgE_FAIL);
    }

    /* Load instance-specific function pointers using volk */
    volkLoadInstance(g_sKN_GPU_EXT_CXT_HOST.m_hVLKN_Instance);

    /* Create persistent debug messenger for runtime validation messages */
#if defined(TgS_DEBUG__KERNEL_GPU) && TgS_DEBUG__KERNEL_GPU
    if (g_sKN_GPU_EXT_CXT_HOST.m_bDebug_Enabled)
    {
        VkDebugUtilsMessengerCreateInfoEXT sDebugCreateInfo;
        tgMM_Set_U08_0x00(&sDebugCreateInfo, sizeof(sDebugCreateInfo));
        sDebugCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;

        sDebugCreateInfo.messageSeverity  = VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        sDebugCreateInfo.messageSeverity |= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT;
        sDebugCreateInfo.messageSeverity |= VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT;
        //sDebugCreateInfo.messageSeverity |= VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT;

        sDebugCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | 
                                       VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | 
                                       VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;

        sDebugCreateInfo.pfnUserCallback = tgKN_GPU_EXT_Debug_Callback;
        sDebugCreateInfo.pUserData = nullptr;

        VkResult eResult = vkCreateDebugUtilsMessengerEXT(
            g_sKN_GPU_EXT_CXT_HOST.m_hVLKN_Instance,
            &sDebugCreateInfo,
            g_psKN_GPU_VLKN_Allocator,
            &g_sKN_GPU_EXT_CXT_HOST.m_sVLKN_Debug_Messenger);

        if (VK_SUCCESS != eResult)
        {
            TgWARNING_MSGF(0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create debug messenger: ", eResult);
        }
    }
/*# defined(TgS_DEBUG__KERNEL_GPU) && TgS_DEBUG__KERNEL_GPU */
#endif

    return (KTgS_OK);
}


/* ---- tgKN_GPU_EXT_Module_Boot ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_EXT_Module_Boot( TgVOID )
{
    if (TgFAILED(tgKN_OS_GPU_API_Module_Boot()))
    {
        return (KTgE_FAIL);
    };

    return (KTgS_OK);
}


/* ---- tgKN_GPU_EXT_Module_Stop ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_EXT_Module_Stop( TgVOID )
{
    tgKN_OS_GPU_API_Module_Stop();
}


/* ---- tgKN_GPU_EXT_Module_Free ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_EXT_Module_Free( TgVOID )
{
    if (g_sKN_GPU_EXT_CXT_HOST.m_sVLKN_Debug_Messenger != VK_NULL_HANDLE && vkDestroyDebugUtilsMessengerEXT)
    {
        vkDestroyDebugUtilsMessengerEXT(g_sKN_GPU_EXT_CXT_HOST.m_hVLKN_Instance, g_sKN_GPU_EXT_CXT_HOST.m_sVLKN_Debug_Messenger, g_psKN_GPU_VLKN_Allocator);
        g_sKN_GPU_EXT_CXT_HOST.m_sVLKN_Debug_Messenger = VK_NULL_HANDLE;
    }

    /* Destroy Vulkan instance */
    tgKN_GPU_EXT_Destroy_Instance();

    /* Free Vulkan resources */
    tgKN_OS_GPU_API_Module_Free();
}


/* ---- tgKN_GPU_EXT_Module_Update ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_EXT_Module_Update( TgATTRIBUTE_UNUSED TgFLOAT32_C fdT )
{
    return (KTgS_OK);
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_GPU_EXT_Create_Instance --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT tgKN_GPU_EXT_Create_Instance( TgVOID )
{
    VkResult                            eResult;
    TgSINT_E08                          iRet;

    TgUINT_E32                          nuiExtensionSupported = 0;
    VkExtensionProperties_P             psExtensions;
    TgUINT_E32                          uiExtensionSupported, uiExtensionRequested;

    VkApplicationInfo                   sAppInfo;
    VkInstanceCreateInfo                sCreateInfo;

#if defined(TgS_DEBUG__KERNEL_GPU) && TgS_DEBUG__KERNEL_GPU
    VkDebugUtilsMessengerCreateInfoEXT  sDebugCreateInfo;
/*# defined(TgS_DEBUG__KERNEL_GPU) && TgS_DEBUG__KERNEL_GPU */
#endif

    /* Check if all layer / validations are supported --------------------------------------------------------------------------------------------------------------------         */

    g_sKN_GPU_EXT_CXT_HOST.m_bValidation_Requested = true;
    g_sKN_GPU_EXT_CXT_HOST.m_bValidation_Enabled = false;

    do
    {
        TgUINT_E32                          nuiLayer;
        VkLayerProperties_P                 psAvailableLayers;
        TgRSIZE                             uiIndex, uiLayer;

        if (!g_sKN_GPU_EXT_CXT_HOST.m_bValidation_Requested)
        {
            break;
        };

        eResult = vkEnumerateInstanceLayerProperties(&nuiLayer, nullptr);
        if ((VK_SUCCESS != eResult) || (0 == nuiLayer))
        {
            TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to enumerate instance layer properties" );
            break;
        };

        psAvailableLayers = (VkLayerProperties*)TgMALLOC_TEMP(nuiLayer * sizeof(VkLayerProperties));
        if (nullptr == psAvailableLayers)
        {
            TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to allocate memory for layer properties" );
            break;
        };

        eResult = vkEnumerateInstanceLayerProperties(&nuiLayer, psAvailableLayers);
        if (VK_SUCCESS != eResult)
        {
            TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to enumerate instance layer properties" );
            TgFREE_TEMP(psAvailableLayers);
            break;
        };

        for (uiIndex = 0; uiIndex < g_nuiKN_GPU_EXT_Validation_Layers; ++uiIndex)
        {
            TgCHAR_NC_CPC                       pszLayerNameRequested = g_apszKN_GPU_EXT_Validation_Layers[uiIndex];

            for (uiLayer = 0; uiLayer < nuiLayer; ++uiLayer)
            {
                if (TgSUCCEEDED(tgNSZ_Compare(&iRet, psAvailableLayers[uiLayer].layerName, KTgMAX_RSIZE, 0, pszLayerNameRequested, KTgMAX_RSIZE, 0)) && (0 == iRet))
                {
                    break;
                };
            };

            if (nuiLayer == uiLayer)
            {
                TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Validation layer not supported: ", pszLayerNameRequested );
                break;
            };
        };

        TgFREE_TEMP(psAvailableLayers);
        g_sKN_GPU_EXT_CXT_HOST.m_bValidation_Enabled = uiIndex == g_nuiKN_GPU_EXT_Validation_Layers;
    } while (0);


    /* Check if all requested extensions are supported -------------------------------------------------------------------------------------------------------------------         */

    eResult = vkEnumerateInstanceExtensionProperties(nullptr, &nuiExtensionSupported, nullptr);
    if (VK_SUCCESS != eResult)
    {
        TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to enumerate instance extension properties" );
        return (KTgE_FAIL);
    };

    psExtensions = (VkExtensionProperties*)TgMALLOC_TEMP(nuiExtensionSupported * sizeof(VkExtensionProperties));
    if (nullptr == psExtensions)
    {
        TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to allocate memory for extension properties" );
        return (KTgE_FAIL);
    };

    eResult = vkEnumerateInstanceExtensionProperties(nullptr, &nuiExtensionSupported, psExtensions);
    if (VK_SUCCESS != eResult)
    {
        TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to enumerate instance extension properties" );
        TgFREE_TEMP(psExtensions);
        return (KTgE_FAIL);
    };

    for (uiExtensionRequested = 0; uiExtensionRequested < g_nuiKN_GPU_EXT_Instance_Extensions; ++uiExtensionRequested)
    {
        TgCHAR_NC_CPC                       pszExtensionNameRequested = g_apszKN_GPU_EXT_Instance_Extensions[uiExtensionRequested];

        for (uiExtensionSupported = 0; uiExtensionSupported < nuiExtensionSupported; ++uiExtensionSupported)
        {
            TgCHAR_NC_CPC                       pszExtensionNameSupported = psExtensions[uiExtensionSupported].extensionName;

            if (TgSUCCEEDED(tgNSZ_Compare(&iRet, pszExtensionNameSupported, KTgMAX_RSIZE, 0, pszExtensionNameRequested, KTgMAX_RSIZE, 0)) && (0 == iRet))
            {
                /* Check if debug utils extension is supported */
                if (TgSUCCEEDED(tgNSZ_Compare(&iRet, pszExtensionNameSupported, KTgMAX_RSIZE, 0, VK_EXT_DEBUG_UTILS_EXTENSION_NAME, KTgMAX_RSIZE, 0)) && (0 == iRet))
                {
                    g_sKN_GPU_EXT_CXT_HOST.m_bDebug_Enabled = g_sKN_GPU_EXT_CXT_HOST.m_bValidation_Enabled;
                }
                break;
            };
        };

        if (uiExtensionSupported == nuiExtensionSupported)
        {
            TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Extension not supported: ", pszExtensionNameRequested );
            TgFREE_TEMP(psExtensions); /* Free the memory allocated for the extension properties */
            return (KTgE_FAIL);
        };
    };

    TgFREE_TEMP(psExtensions); /* Free the memory allocated for the extension properties */
    psExtensions = nullptr;

    /* Application info */
    tgMM_Set_U08_0x00(&sAppInfo, sizeof(sAppInfo));
    sAppInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    sAppInfo.pApplicationName = KTgKN_GPU_APPLICATION_NAME;
    sAppInfo.applicationVersion = KTgKN_GPU_VLKN_APPLICATION_VERSION;
    sAppInfo.pEngineName = KTgKN_GPU_ENGINE_NAME;
    sAppInfo.engineVersion = KTgKN_GPU_VLKN_ENGINE_VERSION;
    sAppInfo.apiVersion = KTgKN_GPU_VLKN_API_VERSION;

    /* Instance create info */
    tgMM_Set_U08_0x00(&sCreateInfo, sizeof(sCreateInfo));
    sCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    sCreateInfo.pApplicationInfo = &sAppInfo;
    sCreateInfo.enabledExtensionCount = (TgUINT_E32)g_nuiKN_GPU_EXT_Instance_Extensions;
    sCreateInfo.ppEnabledExtensionNames = (const char* const*)g_apszKN_GPU_EXT_Instance_Extensions;

#if defined(TgS_DEBUG__KERNEL_GPU) && TgS_DEBUG__KERNEL_GPU
    if (g_sKN_GPU_EXT_CXT_HOST.m_bValidation_Enabled)
    {
        sCreateInfo.enabledLayerCount = (TgUINT_E32)g_nuiKN_GPU_EXT_Validation_Layers;
        sCreateInfo.ppEnabledLayerNames = (const char* const*)g_apszKN_GPU_EXT_Validation_Layers;
    }
    else
    {
        sCreateInfo.enabledLayerCount = 0;
        sCreateInfo.ppEnabledLayerNames = nullptr;
    };

    if (g_sKN_GPU_EXT_CXT_HOST.m_bDebug_Enabled)
    {
        /* Debug messenger for instance creation/destruction */
        tgMM_Set_U08_0x00(&sDebugCreateInfo, sizeof(sDebugCreateInfo));
        sDebugCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;

        sDebugCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        sDebugCreateInfo.messageSeverity |= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT;
        sDebugCreateInfo.messageSeverity |= VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT;
        //sDebugCreateInfo.messageSeverity |= VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT;

        sDebugCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | 
                                       VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | 
                                       VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;

        sDebugCreateInfo.pfnUserCallback = tgKN_GPU_EXT_Debug_Callback;
        sCreateInfo.pNext = &sDebugCreateInfo;
    };
/*# defined(TgS_DEBUG__KERNEL_GPU) && TgS_DEBUG__KERNEL_GPU */
#endif

    /* Create instance */
    eResult = vkCreateInstance(&sCreateInfo, g_psKN_GPU_VLKN_Allocator, &g_sKN_GPU_EXT_CXT_HOST.m_hVLKN_Instance);
    if (VK_SUCCESS != eResult)
    {
        TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create Vulkan instance" );
        return (KTgE_FAIL);
    };

    return (KTgS_OK);
}


/* ---- tgKN_GPU_EXT_Destroy_Instance -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgKN_GPU_EXT_Destroy_Instance( TgVOID )
{
    if (g_sKN_GPU_EXT_CXT_HOST.m_hVLKN_Instance != VK_NULL_HANDLE)
    {
        vkDestroyInstance(g_sKN_GPU_EXT_CXT_HOST.m_hVLKN_Instance, g_psKN_GPU_VLKN_Allocator);
        g_sKN_GPU_EXT_CXT_HOST.m_hVLKN_Instance = VK_NULL_HANDLE;
    }
}


#if defined(TgS_DEBUG__KERNEL_GPU) && TgS_DEBUG__KERNEL_GPU

/* ---- tgKN_GPU_EXT_Debug_Callback ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static VKAPI_ATTR VkBool32 VKAPI_CALL tgKN_GPU_EXT_Debug_Callback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    VkDebugUtilsMessengerCallbackDataEXT_CP pCallbackData,
    TgATTRIBUTE_UNUSED TgVOID_P pUserData)
{
    TgCHAR_U8_CP                        pszSeverity = u8"INFO";
    TgUINT_E32                          uiChannel = KTgCN_CHANEL_LOG | KTgCN_SEVERITY_7;
    TgCHAR_U8                           uszHeader[512];
    TgCHAR_U8                           uszMessage[KTgCN_OSCON_LINE_LENGTH];

    /* Filter informational messages about missing optional extensions by message ID name.
       This is more efficient than full message string comparison. */
    if ((1 == pCallbackData->messageIdNumber) && pCallbackData->pMessageIdName)
    {
        TgSINT_E08                          iRet;
        
        /* Suppress AMD device coherent memory extension warning (optional extension, informational only) */
        if (TgSUCCEEDED(tgNSZ_Compare(&iRet, pCallbackData->pMessageIdName, KTgMAX_RSIZE, 0, "CDL", KTgMAX_RSIZE, 0)) && (0 == iRet))
        {
            TgRSIZE                             uiLoc;

            if (pCallbackData->pMessage && TgSUCCEEDED(tgNSZ_StrStr( &uiLoc, pCallbackData->pMessage, KTgMAX_RSIZE, "VK_AMD_device_coherent_memory", KTgMAX_RSIZE )))
            {
                return VK_FALSE;
            }
        }
    }

    // Handle shader debug printf output
    if (messageType & VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT)
    {
        TgRSIZE                             uiLoc;

        // Check if this is a debug printf message
        if (pCallbackData->pMessage && TgSUCCEEDED(tgNSZ_StrStr( &uiLoc, pCallbackData->pMessage, KTgMAX_RSIZE, "DEBUG-PRINTF", KTgMAX_RSIZE )))
        {
            // Extract and print the shader debug printf message
            tgUSZ_PrintF(uszHeader, sizeof(uszHeader), STD_MSG_PREFIX u8"[SHADER DEBUG] ", STD_MSG_POST);
            tgCN_PrintPrefixF(KTgCN_CHANEL_LOG | KTgCN_SEVERITY_7, uszHeader, u8"%s", pCallbackData->pMessage);
            return VK_FALSE;
        }
    }

    // Handle other validation messages
    TgWARN_DISABLE_PUSH(4061 4062,switch-enum)
    switch (messageSeverity)
    {
        default:
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
            pszSeverity = u8"VERBOSE";
            uiChannel = KTgCN_CHANEL_LOG | KTgCN_SEVERITY_7;
            break;
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
            pszSeverity = u8"INFO";
            uiChannel = KTgCN_CHANEL_LOG | KTgCN_SEVERITY_6;
            break;
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
            pszSeverity = u8"WARNING";
            uiChannel = KTgCN_CHANEL_ERROR | KTgCN_SEVERITY_4;
            break;
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
            pszSeverity = u8"ERROR";
            uiChannel = KTgCN_CHANEL_ERROR | KTgCN_SEVERITY_2;
            break;
    }
    TgWARN_DISABLE_POP()

    tgUSZ_PrintF(uszHeader, sizeof(uszHeader), STD_MSG_PREFIX u8"[VK %s] ", STD_MSG_POST, pszSeverity );
    tgUSZ_PrintF(uszMessage, sizeof(uszMessage), u8"%s\n", pCallbackData->pMessage);
    tgCN_PrintPrefix(uiChannel, uszHeader, uszMessage, KTgMAX_RSIZE);

    return VK_FALSE;
}

/*# defined(TgS_DEBUG__KERNEL_GPU) && TgS_DEBUG__KERNEL_GPU */
#endif

TgMSVC_OPT_ENABLE_MAXIMUM

// /* ---- tgKN_GPU_VLKN_Custom_Allocation ------------------------------------------------------------------------------------------------------------------------------------------ */
// /* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
// TgATTRIBUTE_FORCE_OPTIMIZE
// static TgVOID_P VKAPI_CALL tgKN_GPU_VLKN_Custom_Allocation(
//     TgVOID_P TgATTRIBUTE_UNUSED pUserData,
//     size_t uiSize,
//     size_t uiAlignment,
//     VkSystemAllocationScope TgATTRIBUTE_UNUSED enVLKN_Allocation_Scope) {

//     TgUN_PTR                            uReturn;

//     uReturn.m_pVoid = TgMALLOC_POOL_ALIGNED(uiSize, uiAlignment);
//     TgVERIFY(0 == (uReturn.m_uiPTR % uiAlignment)); /* Ensure the returned memory meets the alignment requirement */
//     TgVERIFY(nullptr != uReturn.m_pVoid || 0 == uiSize); /* If size is non-zero, the allocation must succeed */
//     return uReturn.m_pVoid;
// }


// /* ---- tgKN_GPU_VLKN_Custom_Reallocation ---------------------------------------------------------------------------------------------------------------------------------------- */
// /* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
// TgATTRIBUTE_FORCE_OPTIMIZE
// static TgVOID_P VKAPI_CALL tgKN_GPU_VLKN_Custom_Reallocation(
//     TgVOID_P TgATTRIBUTE_UNUSED pUserData,
//     TgVOID_P pOriginal,
//     size_t uiSize,
//     size_t uiAlignment,
//     VkSystemAllocationScope TgATTRIBUTE_UNUSED enVLKN_Allocation_Scope) {

//     TgUN_PTR                            uReturn;

//     uReturn.m_pVoid = TgREALLOC_POOL(pOriginal, uiSize);
//     TgVERIFY(0 == (uReturn.m_uiPTR % uiAlignment)); /* Ensure the returned memory meets the alignment requirement */
//     TgVERIFY(nullptr != uReturn.m_pVoid || 0 == uiSize); /* If size is non-zero, the allocation must succeed */
//     return uReturn.m_pVoid;
// }


// /* ---- tgKN_GPU_VLKN_Custom_Free ------------------------------------------------------------------------------------------------------------------------------------------------ */
// /* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
// TgATTRIBUTE_FORCE_OPTIMIZE
// static void VKAPI_CALL tgKN_GPU_VLKN_Custom_Free(TgVOID_P pUserData, TgVOID_P pMemory) {
//     (void)pUserData;
//     if (nullptr == pMemory)
//     {
//         return;
//     }
//     TgFREE_POOL(pMemory);
// }


// /* ---- tgKN_GPU_VLKN_Internal_Allocation_Notification --------------------------------------------------------------------------------------------------------------------------- */
// /* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
// TgATTRIBUTE_FORCE_OPTIMIZE
// static void VKAPI_CALL tgKN_GPU_VLKN_Internal_Allocation_Notification(
//     TgVOID_P pUserData,
//     size_t uiSize,
//     VkInternalAllocationType enVLKN_Allocation_Type,
//     VkSystemAllocationScope enVLKN_Allocation_Scope) {

//     (void)pUserData;
//     tgCN_PrintF( KTgCN_CHANEL_MESSAGE, STD_MSG_PREFIX, STD_MSG_POST);
//     tgCN_PrintF( KTgCN_CHANEL_MESSAGE, u8"[INTERNAL_ALLOC] Size: %zu, Type: %d, Scope: %d\n", uiSize, (int)enVLKN_Allocation_Type, (int)enVLKN_Allocation_Scope );
// }


// /* ---- tgKN_GPU_VLKN_Internal_Free_Notification --------------------------------------------------------------------------------------------------------------------------------- */
// /* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
// TgATTRIBUTE_FORCE_OPTIMIZE
// static void VKAPI_CALL tgKN_GPU_VLKN_Internal_Free_Notification(
//     TgVOID_P pUserData,
//     size_t uiSize,
//     VkInternalAllocationType enVLKN_Allocation_Type,
//     VkSystemAllocationScope enVLKN_Allocation_Scope) {

//     (void)pUserData;
//     tgCN_PrintF( KTgCN_CHANEL_MESSAGE, STD_MSG_PREFIX, STD_MSG_POST);
//     tgCN_PrintF( KTgCN_CHANEL_MESSAGE, u8"[INTERNAL_FREE] Size: %zu, Type: %d, Scope: %d\n", uiSize, (int)enVLKN_Allocation_Type, (int)enVLKN_Allocation_Scope);
// }

TgMSVC_OPT_RESTORE_DEFAULT
