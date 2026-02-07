/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (VULKAN) Kernel [GPU].h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.22 | »GUID« 7ECEAB43-40E4-4161-8F94-87AF31F5BA9A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_VULKAN_KERNEL_GPU_H) && defined(TgBUILD_FEATURE__GRAPHICS)
#define TGS_VULKAN_KERNEL_GPU_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#if !defined(TgBUILD_FEATURE__GRAPHICS) || !defined(TgFEATURE_GRAPHICS__VULKAN)
#error GPU API Extensions should not be included without the proper macro definitions.
#endif

#include "TgS Kernel [GPU].h"

#include TgHEADER_OPERATING_SYSTEM(TgS COMMON/TgS,Common - Base - Include.h)

#if defined(TgBUILD_OS__WINDOWS)
    #define VK_USE_PLATFORM_WIN32_KHR
#elif defined(TgBUILD_OS__ANDROID)
    #define VK_USE_PLATFORM_ANDROID_KHR
#elif defined(TgBUILD_OS__MAC) || defined(TgBUILD_OS__IOS)
    #define VK_USE_PLATFORM_METAL_EXT
#elif defined(TgBUILD_OS__POSIX)
    #define VK_USE_PLATFORM_XCB_KHR
#else
    #error "Unsupported platform for Vulkan"
#endif

#define VK_EXT_debug_utils
#define VK_EXT_hdr_metadata
#define VK_EXT_mesh_shader

#if !defined(no_volk)
TgDISABLE_ALL_WARNNGS_PUSH
#define VK_NO_PROTOTYPES  /* Tell Vulkan headers not to include function prototypes */
#include <volk.h>
TgDISABLE_ALL_WARNNGS_POP
#else
#define VOLK_IMPLEMENTATION
#include <volk.h>
#endif

#include "TgS KERNEL/TgS (VULKAN) Kernel [GPU] - Constants.h"
#include "TgS KERNEL/TgS (VULKAN) Kernel [GPU] - Type.h"
#include "TgS KERNEL/TgS (VULKAN) Kernel [GPU] - Debug.h"




/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/*  @param [in] ARG0 ARG0 Pointer to the command structure returned by tgKN_GPU_EXT__WORK__Acquire_Command. */
TgEXTN TgVOID
tgKN_GPU_VLKN__CMD__Register_Resource_For_Release(
    STg2_KN_GPU_CMD_PC ARG0, VkBuffer ARG1, VkDeviceMemory ARG2 );


/* =============================================================================================================================================================================== */
#endif
