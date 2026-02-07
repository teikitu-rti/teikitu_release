/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (VULKAN-MAC) Kernel [GPU] - Module.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.22 | »GUID« 7ECEAB43-40E4-4161-8F94-87AF31F5BA9A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    Models:     Claude 3.7, Claude 4.0
    ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */

#include "TgS COMMON/TgS (POSIX) Common - Global.h"
#include "TgS KERNEL/TgS (POSIX) Kernel - Type.h"

#include "TgS (POSIX) Kernel - Internal - Type.h"
#include "TgS (POSIX) Kernel - Internal - Data.h"

/* We need Vulkan headers but NOT the Metal extension headers here as they might pull in Obj-C stuff */
#include <vulkan/vulkan.h>

/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  External Function Declarations (from .mm file)                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgRESULT tgKN_OS_GPU_API_Mac_Create_Surface(VkInstance instance, const VkAllocationCallbacks* allocator, VkSurfaceKHR* pSurface, void* hWindow);
TgRESULT tgKN_OS_GPU_API_Mac_Create_Headless_Surface(VkInstance instance, const VkAllocationCallbacks* allocator, VkSurfaceKHR* pSurface);
void tgKN_OS_GPU_API_Mac_Destroy_Headless_Surface(VkInstance instance, const VkAllocationCallbacks* allocator, VkSurfaceKHR surface);

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Extertnal Function                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgEXTN TgRESULT
tgKN_OS_GPU_API_Create_Surface(
     TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP );

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_OS_GPU_API_Module_Init ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_OS_GPU_API_Module_Init( TgVOID )
{
    VkResult                            iResult;

    /* Initialize volk - this will dynamically load vulkan-1.dll and all Vulkan functions */
    iResult = volkInitialize();
    if (VK_SUCCESS != iResult)
    {
        TgCRITICAL_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to initialize volk (Vulkan loader). Error: %d. Is Vulkan installed?", iResult );
        goto tgKN_OS_GPU_API_Module_Init_FAIL;
    };

    TgMSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Volk initialized successfully - Vulkan loaded dynamically." );

    if (TgFAILED(tgKN_OS_GPU_Module_Init()))
    {
        goto tgKN_OS_GPU_API_Module_Init_FAIL;
    };

    return (KTgS_OK);

tgKN_OS_GPU_API_Module_Init_FAIL:
    tgKN_OS_GPU_API_Module_Free();
    return (KTgE_FAIL);
}


/* ---- tgKN_OS_GPU_API_Module_Boot ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_OS_GPU_API_Module_Boot( TgVOID )
{
    /* Additional initialization that requires the instance to be created */

    if (TgFAILED(tgKN_OS_GPU_Module_Boot()))
    {
        return (KTgE_FAIL);
    };

    /* Create headless surface for enumeration */
    if (TgFAILED(tgKN_OS_GPU_API_Mac_Create_Headless_Surface(g_sKN_GPU_EXT_CXT_HOST.m_hVLKN_Instance, g_psKN_GPU_VLKN_Allocator, &g_sKN_GPU_EXT_CXT_HOST.m_hVLKN_Temp_Surface)))
    {
        return (KTgE_FAIL);
    };

    return (KTgS_OK);
}


/* ---- tgKN_OS_GPU_API_Module_Stop ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_OS_GPU_API_Module_Stop( TgVOID )
{
    /* Stop any ongoing operations */
    
    /* Destroy the headless surface */
    tgKN_OS_GPU_API_Mac_Destroy_Headless_Surface(g_sKN_GPU_EXT_CXT_HOST.m_hVLKN_Instance, g_psKN_GPU_VLKN_Allocator, g_sKN_GPU_EXT_CXT_HOST.m_hVLKN_Temp_Surface);
    g_sKN_GPU_EXT_CXT_HOST.m_hVLKN_Temp_Surface = VK_NULL_HANDLE;

    tgKN_OS_GPU_Module_Stop();
}


/* ---- tgKN_OS_GPU_API_Module_Free ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_OS_GPU_API_Module_Free( TgVOID )
{
    tgKN_OS_GPU_Module_Free();

    /* Volk cleanup is automatic - no need to manually free the DLL */
}


/* ---- tgKN_OS_GPU_API_Create_Surface ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_OS_GPU_API_Create_Surface( TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP )
{
    STg2_KN_GPU_VLKN_CXT_SWAP_PC        psVLKN_CXT_SWAP = g_asKN_GPU_EXT_CXT_SWAP + tiCXT_SWAP.m_uiI;
    STg2_KN_GPU_CXT_SWAP_PC             psCXT_SWAP = g_asKN_GPU_CXT_SWAP + tiCXT_SWAP.m_uiI;
    union { void* hWindow; TgUINT_PTR uiPTR; } const sWindow = { .uiPTR = psCXT_SWAP->m_uiOS_ID };

    TgPARAM_CHECK_INDEX(tiCXT_SWAP.m_uiI, g_asKN_GPU_EXT_CXT_SWAP);
    TgVERIFY(VK_NULL_HANDLE == psVLKN_CXT_SWAP->m_hVLKN_Surface);

    return (tgKN_OS_GPU_API_Mac_Create_Surface(g_sKN_GPU_EXT_CXT_HOST.m_hVLKN_Instance, g_psKN_GPU_VLKN_Allocator, &psVLKN_CXT_SWAP->m_hVLKN_Surface, sWindow.hWindow));
}
