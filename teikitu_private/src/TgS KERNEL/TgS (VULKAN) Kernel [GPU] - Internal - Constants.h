/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (VULKAN) Kernel [GPU] - Internal - Constants.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.22 | »GUID« 7ECEAB43-40E4-4161-8F94-87AF31F5BA9A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    Models:     Claude 3.7, Claude 4.0
    ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_VULKAN_KERNEL_GPU_INTERNAL_CONSTANTS_H)
#define TGS_VULKAN_KERNEL_GPU_INTERNAL_CONSTANTS_H
#pragma once


/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Configuration                                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

#define KTgKN_GPU_VLKN_API_VERSION              VK_API_VERSION_1_4
#define KTgKN_GPU_VLKN_ENGINE_VERSION           VK_MAKE_VERSION(5, 22, 0)
#define KTgKN_GPU_VLKN_APPLICATION_VERSION      VK_MAKE_VERSION(1, 0, 0)

enum { KTgKN_GPU_EXT_MAX_GRAPHICS_BUFFER       = 16384,    /**< Number of graphic command buffers available in a frame for recording. */
       KTgKN_GPU_EXT_MAX_PRESENT_BUFFER        =    32,    /**< Number of present command buffers available in a frame for recording. */
       KTgKN_GPU_EXT_MAX_COMPUTE_BUFFER        =  4096,    /**< Number of compute command buffers available in a frame for recording. */
       KTgKN_GPU_EXT_MAX_TRANSFER_BUFFER       =  1024 };  /**< Number of transfer command buffers available in a frame for recording. */

 enum { KTgKN_GPU_EXT_MAX_COMMAND_BUFFER       = KTgKN_GPU_EXT_MAX_GRAPHICS_BUFFER
                                               + KTgKN_GPU_EXT_MAX_PRESENT_BUFFER
                                               + KTgKN_GPU_EXT_MAX_COMPUTE_BUFFER
                                               + KTgKN_GPU_EXT_MAX_TRANSFER_BUFFER };

/* Max default SRV value would be the most in a single descriptor set. */

enum { KTgKN_GPU_VLKN_MAX_QUEUE_FAMILY         =    12 }; /* Vulkan has 9 different queue bits. */
enum { KTgKN_GPU_VLKN_ALLOC_PER_FRAME          =  1024 }; /* Controls the size of the descriptor pool */
enum { KTgKN_GPU_VLKN_DBG_ALLOC_PER_FRAME      =   256 }; /* Controls the size of the descriptor pool */

enum { KTgKN_GPU_VLKN_DBG_LINE__CULL_WORKGROUP_SIZE         =      64 };    /* Compute shader workgroup size for culling */
enum { KTgKN_GPU_VLKN_DBG_LINE__MESH_LINES_PER_WORKGROUP    =      32 };    /* Lines processed per mesh workgroup */

enum { KTgKN_GPU_VLKN_TIMESTAMP_QUERIES_PER_POOL            =     128 };    /* Must be significantly lower than KTgKN_GPU_EXT_MAX_GRAPHICS_BUFFER */


// enum { KTgKN_GPU_EXT_MAX_DESCRIPTOR_SET_LAYOUT =    16 };
// enum { KTgKN_GPU_VLKN_MAX_DESCRIPTOR_POOLS     =     3 };
// enum { KTgKN_GPU_VLKN_MAX_COMMAND_POOLS        =    16 };
// enum { KTgKN_GPU_VLKN_MAX_DESCRIPTOR_SETS      =  8192 };
// enum { KTgKN_GPU_VLKN_MAX_COMMAND_BUFFERS      =    64 };
// enum { KTgKN_GPU_VLKN_MAX_PIPELINE_LAYOUTS     =    64 };
// enum { KTgKN_GPU_VLKN_MAX_PIPELINES            =   256 };
// enum { KTgKN_GPU_VLKN_MAX_SHADER_MODULES       =   512 };
// enum { KTgKN_GPU_VLKN_MAX_SAMPLERS             =    64 };
// enum { KTgKN_GPU_VLKN_MAX_BUFFER_VIEWS         =  4096 };
// enum { KTgKN_GPU_VLKN_MAX_IMAGE_VIEWS          =  4096 };
// enum { KTgKN_GPU_VLKN_MAX_SEMAPHORES           =   256 };
// enum { KTgKN_GPU_VLKN_MAX_FENCES               =    32 };
// enum { KTgKN_GPU_VLKN_MAX_EVENTS               =    16 };


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Validation                                                                                                                                                                     */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

//TgCOMPILER_ASSERT(D3D12_SIMULTANEOUS_RENDER_TARGET_COUNT <= 8,0);




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Debug Configuration                                                                                                                                                   */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

#define TgCOMPILE__VULKAN_DEBUG

#if defined(TgCOMPILE__VULKAN_DEBUG)
#define TgBUILD_ENABLE_VULKAN_DEBUG 1
#define TgBUILD_ENABLE_VULKAN_DEBUG_WITH_GPU_VALIDATION 0
#else
#define TgBUILD_ENABLE_VULKAN_DEBUG 0
#define TgBUILD_ENABLE_VULKAN_DEBUG_WITH_GPU_VALIDATION 0
#endif




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Constants                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

typedef enum TgATTRIBUTE_ENUM_FLAG
{
    ETgKN_GPU_VLKN_DESCRIPTOR_SET_LAYOUT_START = 0,

    ETgKN_GPU_VLKN_DESCRIPTOR_SET_LAYOUT__BASE_SHARED = ETgKN_GPU_VLKN_DESCRIPTOR_SET_LAYOUT_START,
    ETgKN_GPU_VLKN_DESCRIPTOR_SET_LAYOUT__UNIT_TEST,
    ETgKN_GPU_VLKN_DESCRIPTOR_SET_LAYOUT__POST_PROCESS_COMPUTE,

    ETgKN_GPU_VLKN_DESCRIPTOR_SET_LAYOUT_END,
    ETgKN_GPU_VLKN_DESCRIPTOR_SET_LAYOUT_MAX = ETgKN_GPU_VLKN_DESCRIPTOR_SET_LAYOUT_END,
    ETgKN_GPU_VLKN_DESCRIPTOR_SET_LAYOUT_COUNT = ETgKN_GPU_VLKN_DESCRIPTOR_SET_LAYOUT_END - ETgKN_GPU_VLKN_DESCRIPTOR_SET_LAYOUT_START,
} ETgKN_GPU_VLKN_DESCRIPTOR_SET_LAYOUT;
TgTYPE_MODIFIER_DEFAULT(ETgKN_GPU_VLKN_DESCRIPTOR_SET_LAYOUT);

#if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)

typedef enum TgATTRIBUTE_ENUM_FLAG
{
    ETgKN_GPU_DBG_VLKN_DESCRIPTOR_SET_LAYOUT_START = 0,

    ETgKN_GPU_DBG_VLKN_DESCRIPTOR_SET_LAYOUT__UBO = ETgKN_GPU_DBG_VLKN_DESCRIPTOR_SET_LAYOUT_START,
    ETgKN_GPU_DBG_VLKN_DESCRIPTOR_SET_LAYOUT__SBO,
    ETgKN_GPU_DBG_VLKN_DESCRIPTOR_SET_LAYOUT__LINE_TASK_MESH,

    ETgKN_GPU_DBG_VLKN_DESCRIPTOR_SET_LAYOUT_END,
    ETgKN_GPU_DBG_VLKN_DESCRIPTOR_SET_LAYOUT_MAX = ETgKN_GPU_DBG_VLKN_DESCRIPTOR_SET_LAYOUT_END,
    ETgKN_GPU_DBG_VLKN_DESCRIPTOR_SET_LAYOUT_COUNT = ETgKN_GPU_DBG_VLKN_DESCRIPTOR_SET_LAYOUT_END - ETgKN_GPU_DBG_VLKN_DESCRIPTOR_SET_LAYOUT_START,
} ETgKN_GPU_DBG_VLKN_DESCRIPTOR_SET_LAYOUT;
TgTYPE_MODIFIER_DEFAULT(ETgKN_GPU_DBG_VLKN_DESCRIPTOR_SET_LAYOUT);

/*# defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
#endif




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Code Macros                                                                                                                                                                    */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

#if defined(TgCOMPILE__GPU_OBJECT_NAME) && TgCOMPILE__GPU_OBJECT_NAME
    #define TgMACRO_KN_GPU_VLKN_SET_NAME(DEVICE,TYPE,HANDLE,NAME)                                                                                                                   \
    {                                                                                                                                                                               \
        tgKN_GPU_VLKN_Debug_Set_Object_Name(DEVICE, TYPE, (TgUINT_E64)HANDLE, NAME);                                                                                                \
    }

    #define TgMACRO_KN_GPU_VLKN_SET_NAME_FROM_ENUM(DEVICE,TYPE,HANDLE,ENUM)                                                                                                         \
    if (VK_NULL_HANDLE != (HANDLE))                                                                                                                                                 \
    {                                                                                                                                                                               \
        TgMACRO_KN_GPU_VLKN_SET_NAME(DEVICE,TYPE,HANDLE,u8""#ENUM);                                                                                                                 \
    }
#else
    #define TgMACRO_KN_GPU_VLKN_SET_NAME(DEVICE,TYPE,HANDLE,NAME)
    #define TgMACRO_KN_GPU_VLKN_SET_NAME_FROM_ENUM(DEVICE,TYPE,HANDLE,ENUM)
/*# defined(TgCOMPILE__GPU_OBJECT_NAME) && TgCOMPILE__GPU_OBJECT_NAME */
#endif

#define TgPARAM_CHECK_KN_GPU_VLKN_CMD( A )                                                                                                                                          \
    TgPARAM_CHECK( ((STg2_KN_GPU_VLKN_CMD_P)(A))->m_enCmd_Queue == ETgKN_GPU_EXT_COMMAND_GRAPHICS );                                                                                \
    TgPARAM_CHECK_KN_GPU_CMD( A )



/* =============================================================================================================================================================================== */
#endif 
