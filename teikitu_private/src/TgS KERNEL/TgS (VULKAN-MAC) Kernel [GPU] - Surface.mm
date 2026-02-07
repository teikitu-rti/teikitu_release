/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (VULKAN-MAC) Kernel [GPU] - Surface.mm
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.22 | »GUID« 7ECEAB43-40E4-4161-8F94-87AF31F5BA9A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    Models:     Claude 3.7-4.5
    ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */

#include "TgS COMMON/TgS (MAC) Common - Global.h"
#include "TgS KERNEL/TgS (MAC) Kernel - Type.h"

#define VK_USE_PLATFORM_METAL_EXT
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_metal.h>

#pragma clang diagnostic ignored "-Wimport-preprocessor-directive-pedantic"
#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>
#import <QuartzCore/QuartzCore.h>

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Data                                                                                                                                                                */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

static NSWindow*                            g_hTemp_Window = nil;

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  External Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
TgEXTN TgRESULT tgKN_OS_GPU_API_Mac_Create_Surface(VkInstance instance, const VkAllocationCallbacks* allocator, VkSurfaceKHR* pSurface, void* hWindow);
TgEXTN TgRESULT tgKN_OS_GPU_API_Mac_Create_Headless_Surface(VkInstance instance, const VkAllocationCallbacks* allocator, VkSurfaceKHR* pSurface);
TgEXTN void tgKN_OS_GPU_API_Mac_Destroy_Headless_Surface(VkInstance instance, const VkAllocationCallbacks* allocator, VkSurfaceKHR surface);

TgRESULT tgKN_OS_GPU_API_Mac_Create_Surface(VkInstance instance, const VkAllocationCallbacks* allocator, VkSurfaceKHR* pSurface, void* hWindow)
{
    VkMetalSurfaceCreateInfoEXT         sSurface_CI;
    VkResult                            eResult;
    NSView*                             pView = (__bridge NSView*)hWindow;
    CAMetalLayer*                       pLayer = nil;

    if ([pView isKindOfClass:[NSWindow class]])
    {
        pView = ((NSWindow*)pView).contentView;
    }

    if ([pView isKindOfClass:[CAMetalLayer class]])
    {
        pLayer = (CAMetalLayer*)pView;
    }
    else
    {
        if (!pView.wantsLayer)
        {
            pView.wantsLayer = YES;
        }
        
        if (!pView.layer)
        {
            pView.layer = [CAMetalLayer layer];
        }
        
        if (![pView.layer isKindOfClass:[CAMetalLayer class]])
        {
             pView.layer = [CAMetalLayer layer];
        }
        pLayer = (CAMetalLayer*)pView.layer;
    }

    tgMM_Set_U08_0x00(&sSurface_CI, sizeof(sSurface_CI));
    sSurface_CI.sType = VK_STRUCTURE_TYPE_METAL_SURFACE_CREATE_INFO_EXT;
    sSurface_CI.pLayer = (__bridge const CAMetalLayer*)pLayer;

    eResult = vkCreateMetalSurfaceEXT(instance, &sSurface_CI, allocator, pSurface);
    if (eResult != VK_SUCCESS)
    {
        TgERROR_MSGF(0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create Vulkan surface: %d", eResult);
        return (KTgE_FAIL);
    }

    return (KTgS_OK);
}

TgRESULT tgKN_OS_GPU_API_Mac_Create_Headless_Surface(VkInstance instance, const VkAllocationCallbacks* allocator, VkSurfaceKHR* pSurface)
{
    TgRESULT                            iResult;

    /* Create a hidden window */
    NSRect frame = NSMakeRect(0, 0, 1, 1);
    g_hTemp_Window = [[NSWindow alloc] initWithContentRect:frame
                                                 styleMask:NSWindowStyleMaskBorderless
                                                   backing:NSBackingStoreBuffered
                                                     defer:NO];
    [g_hTemp_Window setReleasedWhenClosed:NO];
    
    /* Create the Vulkan surface using the temporary window */
    iResult = tgKN_OS_GPU_API_Mac_Create_Surface(instance, allocator, pSurface, (__bridge void*)g_hTemp_Window);
    if (TgFAILED(iResult))
    {
        [g_hTemp_Window close];
        g_hTemp_Window = nil;
        return (iResult);
    }

    return (KTgS_OK);
}

void tgKN_OS_GPU_API_Mac_Destroy_Headless_Surface(VkInstance instance, const VkAllocationCallbacks* allocator, VkSurfaceKHR surface)
{
    /* Destroy the Vulkan surface */
    if (surface != VK_NULL_HANDLE)
    {
        vkDestroySurfaceKHR(instance, surface, allocator);
    }

    /* Destroy the temporary window */
    if (g_hTemp_Window)
    {
        [g_hTemp_Window close];
        g_hTemp_Window = nil;
    }
}

#ifdef __cplusplus
}
#endif
