/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (VULKAN) Kernel [GPU] - Internal.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.22 | »GUID« 7ECEAB43-40E4-4161-8F94-87AF31F5BA9A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    Models:     Claude 3.7, Claude 4.0
    ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_VULKAN_KERNEL_GPU_INTERNAL_H)
#define TGS_VULKAN_KERNEL_GPU_INTERNAL_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* TODO: WIP Comment for VULKAN (API) GPU management
   Other modules that need to use the GPU should have the capacity to write their code using the API semantics directly. Otherwise, we would have to create wrapper functions to
   mimic the graphic APIs and try to create a singular representation across all of them. Instead, think of the users of the GPU module as plug-ins that will be run by the 
   the GPU kernel. The aim will be to provide base functionality to ease the use of the API (similar to the CPU work), taking on some of the burden of memory and resource
   management. */

/* TODO: VULKAN (API) GPU management
   - Create a surface for the GPU to render to.
   - Create a swap chain for the GPU to render to.
   - Create a command pool for the GPU to use.
   - Create a command buffer for the GPU to use.
   - Create a fence for the GPU to use.
   - Create a semaphore for the GPU to use.
   */

/* WARNING: The following functions may require the need to send a windows message and need to be called from the main message processing thread.
    vkCreateSwapchainKHR
    vkDestroySwapchainKHR
    vkAcquireNextImageKHR and vkAcquireNextImage2KHR
    vkQueuePresentKHR
    vkReleaseSwapchainImagesKHR
    vkAcquireFullScreenExclusiveModeEXT
    vkReleaseFullScreenExclusiveModeEXT
    vkSetHdrMetadataEXT */



#include "TgS Kernel [GPU] - Internal.h"

#include "TgS KERNEL/TgS (VULKAN) Kernel [GPU].h"

#include "TgS (VULKAN) Kernel [GPU] - Internal - Constants.h"
#include "TgS (VULKAN) Kernel [GPU] - Internal - Type.h"
#include "TgS (VULKAN) Kernel [GPU] - Internal - Data.h"




/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/** @brief Select a supported mode that matches the request or is the closest by rounding down.
    @param [out] OUT0 Pointer to a mode data structure that holds the results of the search.
    @param [in] ARG1 Pointer to the output device being queried.
    @param [in] ARG2 Pointer to a mode data structure that is the basis of the search.
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_EXT_Select_Min_Mode(
    STg2_KN_GPU_Mode_PC TgANALYSIS_NO_NULL OUT0, STg2_KN_GPU_VLKN_Display_Output_PCU ARG1, STg2_KN_GPU_Mode_CPC ARG2 );

/** @brief Select a supported mode that matches the request or is the closest by rounding up.
    @param [out] OUT0 Pointer to a mode data structure that holds the results of the search.
    @param [in] ARG1 Pointer to the output device being queried.
    @param [in] ARG2 Pointer to a mode data structure that is the basis of the search.
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_EXT_Select_Max_Mode(
    STg2_KN_GPU_Mode_PC TgANALYSIS_NO_NULL OUT0, STg2_KN_GPU_VLKN_Display_Output_PCU ARG1, STg2_KN_GPU_Mode_CPC ARG2 );


/* ---- GPU - Helper Functions --------------------------------------------------------------------------------------------------------------------------------------------------- */

/** @brief Create a binary semaphore
    @param [out] OUT0 Semaphore handle
    @param [in] ARG1 Device handle
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_VLKN_Create_Semaphore_Binary(
    VkSemaphore_P TgANALYSIS_NO_NULL OUT0, VkDevice ARG1);

/** @brief Create a timeline semaphore
    @param [out] OUT0 Semaphore handle
    @param [in] ARG1 Device handle
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_VLKN_Create_Semaphore_Timeline(
    VkSemaphore_P TgANALYSIS_NO_NULL OUT0, VkDevice ARG1 );

/* Wait for a timeline semaphore
    @param [in] ARG0 Device handle
    @param [in] ARG1 Semaphore handle
    @param [in] ARG2 Timeout value
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_VLKN_Wait_Semaphore_Timeline(
    VkDevice ARG0, VkSemaphore ARG1, TgUINT_E64_C ARG2);

/** @brief Submit command buffers to a queue with a timeline semaphore
    @param [out] OUT0 Pointer to the timeline value (optional)
    @param [in] ARG1 Pointer to the command queue
    @param [in] ARG2 Number of command buffers
    @param [in] ARG3 Pointer to command buffer array
    @param [in] ARG4 Pointer to the command queue to wait on using the semaphore timeline value that proceeds.
    @param [in] ARG5 Timeline terminating value to wait, added to the command buffer submission.
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_VLKN_Submit_Semaphore_Timeline_For_Queue_With_Wait(
    TgUINT_E64_P TgANALYSIS_OK_NULL OUT0, STg2_KN_GPU_VLKN_CMD_Queue_PC TgANALYSIS_NO_NULL ARG1, TgRSIZE_C ARG3, VkCommandBuffer_CPC ARG2,
    STg2_KN_GPU_VLKN_CMD_Queue_PC TgANALYSIS_OK_NULL ARG4, TgUINT_E64_C ARG5 );

/** @brief Create a command pool
    @param [out] OUT0 Command pool handle
    @param [in] ARG1 Device handle
    @param [in] ARG2 Queue family index
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_VLKN_Create_Command_Pool(
    VkCommandPool_P TgANALYSIS_NO_NULL OUT0, VkDevice ARG1, TgRSIZE_C ARG2 );

/** @brief Create a command buffer
    @param [out] OUT0 Command buffer handle
    @param [in] ARG1 Device handle
    @param [in] ARG2 Command pool handle
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_VLKN_Create_Command_Buffer(
    VkCommandBuffer_P TgANALYSIS_NO_NULL OUT0, VkDevice ARG1, VkCommandPool ARG2 );

/** @brief Create a shader module
    @param [out] OUT0 Shader module handle
    @param [in] ARG1 Device handle
    @param [in] ARG2 Pointer to shader code
    @param [in] ARG3 Size of shader code
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_VLKN_Create_Shader_Module(
    VkShaderModule_P TgANALYSIS_NO_NULL OUT0, VkDevice ARG1, TgVOID_CPC ARG2, TgRSIZE_C ARG3 );

/** @brief Convert resource descriptor to buffer usage flags
    @param [in] ARG0 Resource descriptor
    @return Vulkan buffer usage flags. */
TgEXTN VkBufferUsageFlags
tgKN_GPU_VLKN_Convert_Buffer_Usage(
    TgUINT_E64_C ARG0 );

/** @brief Convert resource descriptor to image usage flags
    @param [in] ARG0 Resource descriptor
    @return Vulkan image usage flags. */
TgEXTN VkImageUsageFlags
tgKN_GPU_VLKN_Convert_Image_Usage(
    TgUINT_E64_C ARG0 );

/** @brief Convert resource descriptor to memory properties
    @param [in] ARG0 Resource descriptor
    @return Vulkan memory properties. */
TgEXTN VkMemoryPropertyFlags
tgKN_GPU_VLKN_Convert_Memory_Properties(
    TgUINT_E64_C ARG0 );

/** @brief Find memory type index that matches requirements
    @param [out] OUT0 Pointer to memory type index result
    @param [in] ARG1 Vulkan physical device handle
    @param [in] ARG2 Memory type bits requirement
    @param [in] ARG3 Memory property flags requirement
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_VLKN_Find_Memory_Type_Index(
    TgUINT_E32_P TgANALYSIS_NO_NULL OUT0, VkPhysicalDevice ARG1, TgUINT_E32_C ARG2, VkMemoryPropertyFlags_C ARG3 );


/* ---- GPU - EXEC Context - Default Resources ----------------------------------------------------------------------------------------------------------------------------------- */

/** @brief Create default pipeline dependencies
    @param [in] ARG0 Pointer to the command structure returned by tgKN_GPU_EXT__WORK__Acquire_Command.
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_VLKN__Execute__Init__Create_Pipeline_Dependencies(
     STg2_KN_GPU_VLKN_CMD_PC TgANALYSIS_NO_NULL ARG0 );

/** @brief Destroy default pipeline dependencies
    @param [in] ARG0 Execution context ID. */
TgEXTN TgVOID
tgKN_GPU_VLKN__Execute__Free__Destroy_Pipeline_Dependencies(
     TgKN_GPU_CXT_EXEC_ID_C ARG0 );

/** @brief Create default pipeline dependencies
    @param [in] ARG0 Pointer to the command structure returned by tgKN_GPU_EXT__WORK__Acquire_Command.
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_VLKN__Execute__Init__Create_Compute_Pipelines(
     STg2_KN_GPU_VLKN_CMD_PC TgANALYSIS_NO_NULL ARG0 );

/** @brief Create default descriptor set layouts
    @param [in] ARG0 Device handle
    @param [in] ARG1 Index of the Vulkan Execution Context
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_VLKN__Execute__Init__Update_Default_Descriptor_Sets(
    VkDevice_C ARG0, TgRSIZE_C ARG1);

/** @brief Destroy default pipeline dependencies
    @param [in] ARG0 Execution context ID. */
TgEXTN TgVOID
tgKN_GPU_VLKN__Execute__Free__Destroy_Compute_Pipelines(
     TgKN_GPU_CXT_EXEC_ID_C ARG0 );

/** @brief Create default pipeline resources
    @param [out] OUT0 Pointer to an array of pipeline handles
    @param [in] ARG1 Maximum Number of pipelines that can be created (size of the array).
    @param [in] ARG2 Pointer to a creation information structure for the function.
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_VLKN_Create_Graphic_Pipelines(
    VkPipeline_PC TgANALYSIS_NO_NULL OUT0, TgRSIZE_C ARG1, STg2_KN_GPU_VLKN_Graphics_Pipeline_CI_CPC TgANALYSIS_NO_NULL ARG2 );

/** @brief Create default pipeline resources
    @param [out] OUT0 Pointer to an array of pipeline handles
    @param [in] ARG1 Maximum Number of pipelines that can be created (size of the array).
    @param [in] ARG2 Pointer to a creation information structure for the function.
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_VLKN_Create_Compute_Pipelines(
    VkPipeline_PC TgANALYSIS_NO_NULL OUT0, TgRSIZE_C ARG1, STg2_KN_GPU_VLKN_Compute_Pipeline_CI_CPC TgANALYSIS_NO_NULL ARG2 );

/** @brief Initialize generated/derived resources.
    @note Note that we do not clear the data structure as it is expected to be cleared as a member of a parent
    @param [in] ARG0 Pointer to the render target
    @param [in] ARG1 Device handle
    @param [in] ARG2 Execution context
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_VLKN__Render_Target__Init(
    STg2_KN_GPU_VLKN_Render_Target_PC TgANALYSIS_NO_NULL ARG0, VkDevice_C ARG1, STg2_KN_GPU_VLKN_CXT_EXEC_PC ARG2 );

/** @brief Create render target resources
    @param [in] ARG0 Pointer to the render target
    @param [in] ARG1 Device handle
    @param [in] ARG2 Execution context
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_VLKN__Render_Target__Create_Resources(
    STg2_KN_GPU_VLKN_Render_Target_PC TgANALYSIS_NO_NULL ARG0, VkDevice_C ARG1, STg2_KN_GPU_VLKN_CXT_EXEC_PC ARG2 );

/** @brief Free render target resources
    @param [in] ARG0 Pointer to the render target
    @param [in] ARG1 Device handle */
TgEXTN TgVOID
tgKN_GPU_VLKN__Render_Target__Destroy_Resources(
    STg2_KN_GPU_VLKN_Render_Target_PC TgANALYSIS_NO_NULL ARG0, VkDevice_C ARG1 );

/** @brief Free render target resources and pipeline, invalidate the render target id.
    @param [in] ARG0 Pointer to the render target
    @param [in] ARG1 Device handle */
TgEXTN TgVOID
tgKN_GPU_VLKN__Render_Target__Free(
    STg2_KN_GPU_VLKN_Render_Target_PC TgANALYSIS_NO_NULL ARG0, VkDevice_C ARG1 );

/** @brief Retrieve a render target from a swap chain context
    @param [out] OUT0 Pointer to receive the render target pointer
    @param [in] ARG1 Swap chain context identifier
    @param [in] ARG2 Render target identifier
    @param [in] ARG3 Execution context identifier
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_VLKN__Render_Target__Get_Render_Target(
    STg2_KN_GPU_VLKN_Render_Target_PP TgANALYSIS_NO_NULL OUT0, TgKN_GPU_CXT_SWAP_ID_C ARG1, TgKN_GPU_RENDER_TARGET_ID_C ARG2, TgKN_GPU_CXT_EXEC_ID_C ARG3 );


/* ---- GPU - Command Functions -------------------------------------------------------------------------------------------------------------------------------------------------- */

/** @brief Create a buffer with memory allocation
    @param [out] OUT0 Output buffer handle
    @param [out] OUT1 Output memory handle
    @param [in] ARG2 Pointer to the command structure returned by tgKN_GPU_EXT__WORK__Acquire_Command.
    @param [in] ARG3 Memory descriptor including usage, memory type, and properties.
    @param [in] ARG4 Buffer size
    @param [in] ARG5 Pointer to an array of queue family indices if concurrent, otherwise null
    @param [in] ARG6 Number of queue family indices in the array (ARG5)
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_VLKN__CMD__Create_Buffer(
    TgANALYSIS_NO_NULL VkBuffer_PC OUT0, TgANALYSIS_NO_NULL VkDeviceMemory_PC OUT1, STg2_KN_GPU_VLKN_CMD_PC TgANALYSIS_NO_NULL ARG2, TgUINT_E64_C ARG3, TgRSIZE_C ARG4,
    TgUINT_E32_CPC TgANALYSIS_OK_NULL ARG5, TgRSIZE_C ARG6 );

/** @brief Copy data from one buffer to another
    @param [in] ARG0 ARG0 Pointer to the command structure returned by tgKN_GPU_EXT__WORK__Acquire_Command.
    @param [in] ARG1 Destination buffer
    @param [in] ARG2 Offset into buffer to start copy (dest)
    @param [in] ARG3 Soure buffer
    @param [in] ARG4 Offset into buffer to start copy (source)
    @param [in] ARG5 Size to copy
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_VLKN__CMD__Copy_Buffer(
    STg2_KN_GPU_VLKN_CMD_PC TgANALYSIS_NO_NULL ARG0, VkBuffer_C ARG1, TgRSIZE_C ARG2, VkBuffer_C ARG3, TgRSIZE_C ARG4, TgRSIZE_C ARG5 );

/** @brief Upload data to a buffer
    @param [in] ARG0 ARG0 Pointer to the command structure returned by tgKN_GPU_EXT__WORK__Acquire_Command.
    @param [in] ARG1 Destination buffer handle
    @param [in] ARG2 Pointer to source data
    @param [in] ARG3 Offset into destination buffer
    @param [in] ARG4 Size of data to upload
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_VLKN__CMD__Upload_Buffer(
    STg2_KN_GPU_VLKN_CMD_PC TgANALYSIS_NO_NULL ARG0, VkBuffer_C ARG1, TgVOID_CPC ARG2, TgRSIZE_C ARG3, TgRSIZE_C ARG4 );

/** @brief Initialize and upload a data buffer using the provided command list. The output parameter is a pointer to a pointer to the resulting API resource.
    @details Usually used to upload a vertex buffer.
    @param [out] OUT0 Output buffer handle
    @param [out] OUT1 Output memory handle
    @param [in] ARG2 ARG0 Pointer to the command structure returned by tgKN_GPU_EXT__WORK__Acquire_Command.
    @param [in] ARG3 Memory descriptor including usage, memory type, and properties.
    @param [in] ARG4 Pointer to the data to be uploaded.
    @param [in] ARG5 Size of the data to be uploaded.
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_VLKN__CMD__Create_Buffer_With_Data(
    VkBuffer_PC TgANALYSIS_NO_NULL OUT0, VkDeviceMemory_PC TgANALYSIS_NO_NULL OUT1, STg2_KN_GPU_VLKN_CMD_PC TgANALYSIS_NO_NULL ARG2, TgUINT_E64_C ARG3, 
    TgVOID_CP TgANALYSIS_NO_NULL ARG4, TgRSIZE_C ARG5 );

/** @brief Retrieve a render target from a swap chain context
    @param [in] ARG0 Pointer to the command structure returned by tgKN_GPU_EXT__WORK__Acquire_Command.
    @param [in] ARG1 Pointer to the render target
    @param [in] ARG2 Pipeline stage flags
    @param [in] ARG3 Access flags
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_VLKN__CMD__Render_Target_Barrier(
    STg2_KN_GPU_VLKN_CMD_PC TgANALYSIS_NO_NULL ARG0, STg2_KN_GPU_VLKN_Render_Target_PC TgANALYSIS_NO_NULL ARG1, VkPipelineStageFlags2 ARG2, VkAccessFlags2 ARG3 );

/** @brief Transition image resource access and queue ownership from graphics write to compute read.
    @param [in] ARG0 Pointer to a command structure on the Graphics Queue (required), returned by tgKN_GPU_EXT__WORK__Acquire_Command.
    @param [in] ARG1 Pointer to a command structure on the Compute Queue (required), returned by tgKN_GPU_EXT__WORK__Acquire_Command.
    @param [in] ARG2 Pointer to a render target data structure (required)
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_VLKN__CMD__Image_Barrier__Graphics_Write_To_Compute_Read(
    STg2_KN_GPU_CMD_PC TgANALYSIS_NO_NULL ARG0, STg2_KN_GPU_CMD_PC TgANALYSIS_NO_NULL ARG1, STg2_KN_GPU_VLKN_Render_Target_P TgANALYSIS_NO_NULL ARG2 );

/** @brief Transition image resource access and queue ownership from graphics back buffer available (result of tgKN_GPU_VLKN__SwapChain__Acquire_Present_Buffer) to compute write.
    @param [in] ARG0 Pointer to a command structure on the Graphics Queue (required), returned by tgKN_GPU_EXT__WORK__Acquire_Command.
    @param [in] ARG1 Pointer to a command structure on the Compute Queue (required), returned by tgKN_GPU_EXT__WORK__Acquire_Command.
    @param [in] ARG2 Pointer to a render target data structure (required)
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_VLKN__CMD__Image_Barrier__Graphics_Swap_To_Compute_Write(
    STg2_KN_GPU_CMD_PC TgANALYSIS_NO_NULL ARG0, STg2_KN_GPU_CMD_PC TgANALYSIS_NO_NULL ARG1, STg2_KN_GPU_VLKN_Render_Target_P TgANALYSIS_NO_NULL ARG2 );

/** @brief Transition image resource access and queue ownership from compute read to graphics write.
    @param [in] ARG1 Pointer to a command structure on the Compute Queue (required), returned by tgKN_GPU_EXT__WORK__Acquire_Command.
    @param [in] ARG0 Pointer to a command structure on the Graphics Queue (required), returned by tgKN_GPU_EXT__WORK__Acquire_Command.
    @param [in] ARG2 Pointer to a render target data structure (required)
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_VLKN__CMD__Image_Barrier__Compute_Read_To_Graphics_Write(
    STg2_KN_GPU_CMD_PC TgANALYSIS_NO_NULL ARG0, STg2_KN_GPU_CMD_PC TgANALYSIS_NO_NULL ARG1, STg2_KN_GPU_VLKN_Render_Target_P TgANALYSIS_NO_NULL ARG2 );

/** @brief Transition image resource access and queue ownership from compute write to graphics present.
    @param [in] ARG1 Pointer to a command structure on the Compute Queue (required), returned by tgKN_GPU_EXT__WORK__Acquire_Command.
    @param [in] ARG0 Pointer to a command structure on the Graphics Queue (required), returned by tgKN_GPU_EXT__WORK__Acquire_Command.
    @param [in] ARG2 Pointer to a render target data structure (required)
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_VLKN__CMD__Image_Barrier__Compute_Write_To_Graphics_Present(
    STg2_KN_GPU_CMD_PC TgANALYSIS_NO_NULL ARG0, STg2_KN_GPU_CMD_PC TgANALYSIS_NO_NULL ARG1, STg2_KN_GPU_VLKN_Render_Target_P TgANALYSIS_NO_NULL ARG2 );

/** @brief Apply colour correction from a source render target to a destination render target using a compute shader.
    @details The compute shader reads tone mapping parameters (exposure, gamma, tone map type) from the OutputDESC in Set 0 of the descriptor set.
             Image view handles are passed via push constants to avoid descriptor set updates.
             Timeline synchronization: The compute shader will wait on uiTimeline_Value from the graphics queue before executing.
    @param [in] ARG0 Pointer to a command structure on the Compute Queue (required), returned by tgKN_GPU_EXT__WORK__Acquire_Command.
    @param [in] ARG1 Pointer to the source render target.
    @param [in] ARG2 Pointer to the destination render target.
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_VLKN__CMD__Apply_Colour_Correction_Compute(
    STg2_KN_GPU_CMD_PC TgANALYSIS_NO_NULL ARG0, STg2_KN_GPU_VLKN_Render_Target_P TgANALYSIS_NO_NULL ARG1, STg2_KN_GPU_VLKN_Render_Target_P TgANALYSIS_NO_NULL ARG2 );


/* ---- GPU - Debug Functions ---------------------------------------------------------------------------------------------------------------------------------------------------- */

/** @brief Query and reset the timestamp pool for the given execution context.
    @param [in] ARG0 UID for the Execution Context (GPU node). */
TgEXTN TgVOID
tgKN_GPU_EXT__WORK__Query_And_Reset_Timestamp_Pool(
    TgKN_GPU_CXT_WORK_ID_C ARG0 );

#if defined(TgS_DEBUG__RENDER)

/** @brief Set debug name for a Vulkan object
    @param[in] pDevice Vulkan device
    @param[in] objectType Vulkan object type
    @param[in] objectHandle Handle to the object
    @param[in] pszName Name to assign */
TgEXTN TgVOID
tgKN_GPU_VLKN_Debug_Set_Object_Name(
    TgVOID_P pDevice,
    TgUINT_E32 objectType,
    TgUINT_E64 objectHandle,
    TgCHAR_U8_CPC pszName );

/*# TgS_DEBUG__RENDER */
#endif

#if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)

/** @brief Initialize debug output at the start of a frame
    @param [in] ARG0 Pointer to the command structure returned by tgKN_GPU_EXT__WORK__Acquire_Command.
    @param [in] ARG1 Context Command index
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_VLKN__CMD__Frame_Start_Debug(
    STg2_KN_GPU_VLKN_CXT_CMD_PC ARG0, TgRSIZE_C ARG1 );

/** @brief Begin rendering for a debug render target
    @param [out] OUT0 Pointer to the debug render target
    @param [in] ARG1 Pointer to the render target
    @param [in] ARG2 Device handle
    @param [in] ARG3 Index to the execution context
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_DBG_VLKN__Render_Target__Init(
    STg2_KN_GPU_DBG_VLKN_Render_Target_PC OUT0, STg2_KN_GPU_VLKN_Render_Target_PC ARG1, VkDevice_C ARG2, TgRSIZE_C ARG3 );

/** @brief Free resources associated with a debug render target
    @param [in] ARG0 Pointer to the debug render target
    @param [in] ARG1 Device handle */
TgEXTN TgVOID
tgKN_GPU_DBG_VLKN__Render_Target__Free(
    STg2_KN_GPU_DBG_VLKN_Render_Target_PC ARG0, VkDevice_C ARG1 );

/*# defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
#endif




/* ---- GPU - Test Functions ----------------------------------------------------------------------------------------------------------------------------------------------------- */

/** @brief Create a test descriptor set
    @param [out] OUT0 Descriptor set handle
    @param [in] ARG1 Command context pointer
    @param [in] ARG2 Uniform buffer handle
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_VLKN_Create_TST_Descriptor_Set(
    VkDescriptorSet_PC OUT0, STg2_KN_GPU_CMD_PC ARG1, VkBuffer ARG2 );


/* =============================================================================================================================================================================== */
#endif
