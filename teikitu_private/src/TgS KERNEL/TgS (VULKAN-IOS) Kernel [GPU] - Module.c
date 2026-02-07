/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (VULKAN-POSIX) Kernel [GPU] - Module.c
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

#include <xcb/xcb.h>
#include <vulkan/vulkan_xcb.h>


/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Extertnal Function                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

static TgRESULT
tgKN_OS_GPU_API_Create_Surface_Internal(
    VkSurfaceKHR* OUT0, xcb_window_t ARG1);

static TgRESULT
tgKN_OS_GPU_API_Create_Headless_Surface( TgVOID );

static TgVOID
tgKN_OS_GPU_API_Destroy_Headless_Surface( TgVOID );

TgEXTN TgRESULT
tgKN_OS_GPU_API_Create_Surface(
     TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Data and Exports                                                                                                                                                    */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

static xcb_connection_t*                    g_pXCB_Connection;
static xcb_screen_t*                        g_pXCB_Screen;

/* Static variables for temporary headless window */
static xcb_window_t                         g_hTemp_Window = 0;




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
    if (TgFAILED(tgKN_OS_GPU_API_Create_Headless_Surface()))
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
    tgKN_OS_GPU_API_Destroy_Headless_Surface();

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
    union { xcb_window_t hWindow; TgUINT_PTR uiPTR; } const sWindow = { .uiPTR = psCXT_SWAP->m_uiOS_ID };

    TgPARAM_CHECK_INDEX(tiCXT_SWAP.m_uiI, g_asKN_GPU_EXT_CXT_SWAP);
    TgVERIFY(VK_NULL_HANDLE == psVLKN_CXT_SWAP->m_hVLKN_Surface);

    return (tgKN_OS_GPU_API_Create_Surface_Internal(&psVLKN_CXT_SWAP->m_hVLKN_Surface, sWindow.hWindow));
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_OS_GPU_API_Create_Surface ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT tgKN_OS_GPU_API_Create_Surface_Internal(VkSurfaceKHR* hVLKN_Surface, xcb_window_t hWindow)
{
    VkXcbSurfaceCreateInfoKHR           sSurface_CI;
    VkResult                            eResult;

    tgMM_Set_U08_0x00(&sSurface_CI, sizeof(sSurface_CI));
    sSurface_CI.sType = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR;
    sSurface_CI.connection = g_pXCB_Connection;
    sSurface_CI.window = hWindow;

    eResult = vkCreateXcbSurfaceKHR(g_sKN_GPU_EXT_CXT_HOST.m_hVLKN_Instance, &sSurface_CI, g_psKN_GPU_VLKN_Allocator, hVLKN_Surface);
    if (eResult != VK_SUCCESS)
    {
        TgERROR_MSGF(0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create Vulkan surface: ", eResult);
        return (KTgE_FAIL);
    }

    return (KTgS_OK);
}


/* ---- tgKN_OS_GPU_API_Create_Headless_Surface ---------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT tgKN_OS_GPU_API_Create_Headless_Surface( TgVOID )
{
    TgRESULT                            iResult;
    uint32_t                            value_mask;
    uint32_t                            value_list[32];

    if (!g_pXCB_Connection || !g_pXCB_Screen)
    {
        TgERROR_MSGF(0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"XCB Connection or Screen not initialized.");
        return (KTgE_FAIL);
    }

    g_hTemp_Window = xcb_generate_id(g_pXCB_Connection);

    value_mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
    value_list[0] = g_pXCB_Screen->black_pixel;
    value_list[1] = 0;

    xcb_create_window(g_pXCB_Connection,
        XCB_COPY_FROM_PARENT,
        g_hTemp_Window,
        g_pXCB_Screen->root,
        0, 0, 1, 1,
        0,
        XCB_WINDOW_CLASS_INPUT_OUTPUT,
        g_pXCB_Screen->root_visual,
        value_mask, value_list);

    /* Create the Vulkan surface using the temporary window */
    iResult = tgKN_OS_GPU_API_Create_Surface_Internal(&g_sKN_GPU_EXT_CXT_HOST.m_hVLKN_Temp_Surface, g_hTemp_Window);
    if (TgFAILED(iResult))
    {
        xcb_destroy_window(g_pXCB_Connection, g_hTemp_Window);
        g_hTemp_Window = 0;
        return (iResult);
    }

    return (KTgS_OK);
}


/* ---- tgKN_OS_GPU_API_Destroy_Headless_Surface --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgKN_OS_GPU_API_Destroy_Headless_Surface( TgVOID )
{
    /* Destroy the Vulkan surface */
    if (g_sKN_GPU_EXT_CXT_HOST.m_hVLKN_Temp_Surface != VK_NULL_HANDLE)
    {
        vkDestroySurfaceKHR(g_sKN_GPU_EXT_CXT_HOST.m_hVLKN_Instance, g_sKN_GPU_EXT_CXT_HOST.m_hVLKN_Temp_Surface, g_psKN_GPU_VLKN_Allocator);
        g_sKN_GPU_EXT_CXT_HOST.m_hVLKN_Temp_Surface = VK_NULL_HANDLE;
    }

    /* Destroy the temporary window */
    if (g_hTemp_Window)
    {
        xcb_destroy_window(g_pXCB_Connection, g_hTemp_Window);
        g_hTemp_Window = 0;
    }
}
