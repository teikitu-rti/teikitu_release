/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (VULKAN) Kernel [GPU] - Internal - Type.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.22 | »GUID« 7ECEAB43-40E4-4161-8F94-87AF31F5BA9A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    Models:     Claude 3.7, Claude 4.0
    ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_VULKAN_KERNEL_GPU_INTERNAL_TYPE_H)
#define TGS_VULKAN_KERNEL_GPU_INTERNAL_TYPE_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif


/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Vulkan Type Aliases                                                                                                                                                   */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgTYPE_MODIFIER_ALL(VkInstance);

TgTYPE_MODIFIER_ALL(VkDisplayPropertiesKHR);
TgTYPE_MODIFIER_ALL(VkDisplayModePropertiesKHR);
TgTYPE_MODIFIER_ALL(VkDisplayModeParametersKHR);

TgTYPE_MODIFIER_ALL(VkPhysicalDevice);
TgTYPE_MODIFIER_ALL(VkPhysicalDeviceProperties);
TgTYPE_MODIFIER_ALL(VkPhysicalDeviceFeatures);
TgTYPE_MODIFIER_ALL(VkPhysicalDeviceMemoryProperties);
TgTYPE_MODIFIER_ALL(VkQueueFamilyProperties);
TgTYPE_MODIFIER_ALL(VkSurfaceFormatKHR);
TgTYPE_MODIFIER_ALL(VkDeviceMemory);
TgTYPE_MODIFIER_ALL(VkDeviceSize);
TgTYPE_MODIFIER_ALL(VkMemoryPropertyFlags);

TgTYPE_MODIFIER_ALL(VkPipeline);
TgTYPE_MODIFIER_ALL(VkDevice);
TgTYPE_MODIFIER_ALL(VkPhysicalDeviceMemoryProperties2);
TgTYPE_MODIFIER_ALL(VkCommandPool);
TgTYPE_MODIFIER_ALL(VkCommandBuffer);
TgTYPE_MODIFIER_ALL(VkDescriptorPool);
TgTYPE_MODIFIER_ALL(VkRenderingInfo);
TgTYPE_MODIFIER_ALL(VkRenderingAttachmentInfo);
TgTYPE_MODIFIER_ALL(VkBuffer);

/* Synchronization */
TgTYPE_MODIFIER_ALL(VkFence);
TgTYPE_MODIFIER_ALL(VkSemaphoreType);
TgTYPE_MODIFIER_ALL(VkSemaphore);
TgTYPE_MODIFIER_ALL(VkTimelineSemaphoreSubmitInfo);
TgTYPE_MODIFIER_ALL(VkSemaphoreWaitInfo);
TgTYPE_MODIFIER_ALL(VkSubmitInfo2);
TgTYPE_MODIFIER_ALL(VkImageMemoryBarrier2);

/* Create Info */
TgTYPE_DECLARE(VkPipelineLayoutCreateInfo, VkPipelineLayoutCI);
TgTYPE_DECLARE(VkPipelineShaderStageCreateInfo, VkPipelineShaderStageCI);
TgTYPE_DECLARE(VkPipelineVertexInputStateCreateInfo, VkPipelineVertexInputStateCI);
TgTYPE_DECLARE(VkPipelineInputAssemblyStateCreateInfo, VkPipelineInputAssemblyStateCI);
TgTYPE_DECLARE(VkPipelineViewportStateCreateInfo, VkPipelineViewportStateCI);
TgTYPE_DECLARE(VkPipelineRasterizationStateCreateInfo, VkPipelineRasterizationStateCI);
TgTYPE_DECLARE(VkPipelineMultisampleStateCreateInfo, VkPipelineMultisampleStateCI);
TgTYPE_DECLARE(VkPipelineDepthStencilStateCreateInfo, VkPipelineDepthStencilStateCI);
TgTYPE_DECLARE(VkPipelineColorBlendStateCreateInfo, VkPipelineColorBlendStateCI);
TgTYPE_DECLARE(VkPipelineDynamicStateCreateInfo, VkPipelineDynamicStateCI);
TgTYPE_DECLARE(VkGraphicsPipelineCreateInfo, VkGraphicsPipelineCI);
TgTYPE_DECLARE(VkBufferViewCreateInfo, VkBufferViewCI);
TgTYPE_DECLARE(VkDescriptorSetLayoutCreateInfo, VkDescriptorSetLayoutCI);
TgTYPE_DECLARE(VkDescriptorPoolCreateInfo, VkDescriptorPoolCI);
TgTYPE_DECLARE(VkSamplerCreateInfo, VkSamplerCI);
TgTYPE_DECLARE(VkRenderPassCreateInfo, VkRenderPassCI);
TgTYPE_DECLARE(VkShaderModuleCreateInfo, VkShaderModuleCI);
TgTYPE_DECLARE(VkDescriptorSetLayoutBindingFlagsCreateInfo, VkDescriptorSetLayoutBindingFlagsCI);
TgTYPE_DECLARE(VkPipelineRenderingCreateInfo, VkPipelineRenderingCI);

/* Descriptor Set */
TgTYPE_MODIFIER_ALL(VkDescriptorSetAllocateInfo);
TgTYPE_MODIFIER_ALL(VkDescriptorSetLayoutBinding);
TgTYPE_MODIFIER_ALL(VkDescriptorImageInfo);
TgTYPE_MODIFIER_ALL(VkDescriptorBufferInfo);
TgTYPE_MODIFIER_ALL(VkWriteDescriptorSet);
TgTYPE_MODIFIER_ALL(VkDescriptorSetLayout);
TgTYPE_MODIFIER_ALL(VkDescriptorSet);
TgTYPE_MODIFIER_ALL(VkDescriptorPoolSize);
TgTYPE_MODIFIER_ALL(VkPushConstantRange);
TgTYPE_MODIFIER_ALL(VkDescriptorBindingFlags);

/* Buffers */
TgTYPE_MODIFIER_ALL(VkBufferImageCopy);
TgTYPE_MODIFIER_ALL(VkBufferUsageFlags);
TgTYPE_MODIFIER_ALL(VkBufferView);
TgTYPE_MODIFIER_ALL(VkBufferViewCreateFlags);

/* Images */
TgTYPE_MODIFIER_ALL(VkImageViewType);
TgTYPE_MODIFIER_ALL(VkImageUsageFlags);
TgTYPE_MODIFIER_ALL(VkImage);
TgTYPE_MODIFIER_ALL(VkImageView);
TgTYPE_MODIFIER_ALL(VkImageMemoryBarrier);


TgTYPE_MODIFIER_ALL(VkFramebuffer);
TgTYPE_MODIFIER_ALL(VkPresentModeKHR);
TgTYPE_MODIFIER_ALL(VkPipelineStageFlags);
TgTYPE_MODIFIER_ALL(VkShaderModule);

TgTYPE_MODIFIER_ALL(VkLayerProperties);
TgTYPE_MODIFIER_ALL(VkExtensionProperties);
TgTYPE_MODIFIER_ALL(VkDebugUtilsMessengerCallbackDataEXT);
TgTYPE_MODIFIER_ALL(VkQueueFlags);

TgTYPE_MODIFIER_ALL(VkQueryPool);
TgTYPE_MODIFIER_ALL(VkQueryPoolCreateInfo);

TgTYPE_MODIFIER_ALL(VkSwapchainKHR);
TgTYPE_MODIFIER_ALL(VkSubmitInfo);
TgTYPE_MODIFIER_ALL(VkSemaphoreSubmitInfo);
TgTYPE_MODIFIER_ALL(VkPresentInfoKHR);
TgTYPE_MODIFIER_ALL(VkCommandBufferBeginInfo);
TgTYPE_MODIFIER_ALL(VkImageCopy);
TgTYPE_MODIFIER_ALL(VkPipelineColorBlendAttachmentState);
TgTYPE_MODIFIER_ALL(VkRenderPass);
TgTYPE_MODIFIER_ALL(VkFormat);
TgTYPE_MODIFIER_ALL(VkSubpassDescription);
TgTYPE_MODIFIER_ALL(VkSubpassDependency);
TgTYPE_MODIFIER_ALL(VkPipelineLayout);

TgTYPE_MODIFIER_ALL(VkAllocationCallbacks);

TgCOMPILER_ASSERT(sizeof(STg2_KN_GPU_Render_DESC) > 128,0);




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Types                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- Helper Structures -------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_STRUCT(STg2_KN_GPU_SBO_DESC, )
{
    TgRSIZE                                     m_uiAligned_SBO_Alignment;
    TgRSIZE                                     m_uiAligned_SBO_Size_Element;
    TgRSIZE                                     m_uiSBO_Elements_Per_Frame;
    TgRSIZE                                     m_uiAligned_SBO_Total_Range;
    VkBuffer                                    m_hVLKN_SBO_Buffer;
    VkDeviceMemory                              m_hVLKN_SBO_Memory;
    TgUN_POINTER                                m_uSBO_Mapped;
};

TgTYPE_STRUCT(STg2_KN_GPU_VLKN_Release_Resource,)
{
    ETgKN_GPU_EXT_COMMAND                       m_enCmd_Queue;
    TgUINT_E32                                  m_uiPad;
    TgRSIZE                                     m_uiFence_Value;
    VkBuffer                                    m_hVLKN_Buffer;
    VkDeviceMemory                              m_hVLKN_Memory;
};

TgTYPE_FORWARD_STRUCT(STg2_KN_GPU_VLKN_CXT_EXEC);

TgTYPE_STRUCT (STg2_KN_GPU_VLKN_Graphics_Pipeline_CI,)
{
    /* Input */
    STg2_KN_GPU_Graphics_Pipeline_CP            m_psPipeline_DESC;
    TgRSIZE                                     m_nuiPipeline_DESC;

    /* Host list of preloaded shaders */
    TgKN_GPU_VS_ID_CP                           m_ptiVS;
    TgRSIZE                                     m_nuiVS;
    TgKN_GPU_TCS_ID_CP                          m_ptiTCS;
    TgRSIZE                                     m_nuiTCS;
    TgKN_GPU_TES_ID_CP                          m_ptiTES;
    TgRSIZE                                     m_nuiTES;
    TgKN_GPU_GS_ID_CP                           m_ptiGS;
    TgRSIZE                                     m_nuiGS;
    TgKN_GPU_TS_ID_CP                           m_ptiTS;
    TgRSIZE                                     m_nuiTS;
    TgKN_GPU_MS_ID_CP                           m_ptiMS;
    TgRSIZE                                     m_nuiMS;
    TgKN_GPU_FS_ID_CP                           m_ptiFS;
    TgRSIZE                                     m_nuiFS;

    /* Shader modules */
    VkShaderModule_CP                           m_phVLKN_VS;
    VkShaderModule_CP                           m_phVLKN_TCS;
    VkShaderModule_CP                           m_phVLKN_TES;
    VkShaderModule_CP                           m_phVLKN_GS;
    VkShaderModule_CP                           m_phVLKN_TS;
    VkShaderModule_CP                           m_phVLKN_MS;
    VkShaderModule_CP                           m_phVLKN_FS;

    VkPipelineRenderingCI                       m_sVLKN_Pipeline_Rendering_CI;
    VkPipelineLayout_P                          m_phVLKN_Pipeline_Layout;
    VkDevice                                    m_hVLKN_Device;
    STg2_KN_GPU_VLKN_CXT_EXEC_P                 m_psVLKN_CXT_EXEC;
    ETgKN_GPU_HLSL_COLOUR_SPACE                 m_enColour_Space;
    TgUINT_E08                                  m_uiPad[4];
};

TgTYPE_STRUCT (STg2_KN_GPU_VLKN_Compute_Pipeline_CI,)
{
    /* Input */
    STg2_KN_GPU_Compute_Pipeline_CP             m_psPipeline_DESC;
    TgRSIZE                                     m_nuiPipeline_DESC;

    TgKN_GPU_CS_ID_CP                           m_ptiCS;
    TgRSIZE                                     m_nuiCS;

    /* Shader modules */
    VkShaderModule_CP                           m_phVLKN_CS;

    VkPipelineRenderingCI                       m_sVLKN_Pipeline_Rendering_CI;
    VkPipelineLayout_P                          m_phVLKN_Pipeline_Layout;
    VkDevice                                    m_hVLKN_Device;
    STg2_KN_GPU_VLKN_CXT_EXEC_P                 m_psVLKN_CXT_EXEC;
    ETgKN_GPU_HLSL_COLOUR_SPACE                 m_enColour_Space;
    TgUINT_E08                                  m_uiPad[4];
};


/* ---- GPU - Contexts - Render Target Container --------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_STRUCT(STg2_KN_GPU_VLKN_Render_Target,) /* Render target collection including back buffer, depth/stencil, and history buffers */
{
    TgKN_GPU_RENDER_TARGET_ID_SINGLETON         m_tiRender_Target_S;

    /* Render Target Configuration */
    STg2_KN_GPU_Render_Target_DESC              m_sRender_Target_DESC;

    /* Flags */
    TgUINT_E64                                  m_bDepth_ReverseZ : 1; /**< If true, the depth buffer is cleared to 1.0 */
    TgUINT_E64                                  m_bStencil_Valid : 1; /**< If true, there is a stencil buffer. */
    TgUINT_E64                                  m_nuiMSAA_Sample : 7;  /**< The number of MSAA samples in use (1,2,4,8,16,32,64). */
    TgUINT_E64                                  m_uiPad1 : 55;

    /* Generated Vulkan Object */

    /* Vulkan: Depth/Stencil Target */
    VkImage                                     m_hVLKN_Depth_Stencil_Image;
    VkDeviceMemory                              m_hVLKN_Depth_Stencil_Memory;
    VkImageView                                 m_hVLKN_Depth_Stencil_View;
    TgRSIZE                                     m_uiDepth_Stencil_Descriptor_Set_Index;

    /* Vulkan: Colour Render Targets */
    VkImage                                     m_ahVLKN_Colour_Image[KTgKN_GPU_MAX_SIMULTANEOUS_TARGET_COUNT];
    VkDeviceMemory                              m_ahVLKN_Colour_Memory[KTgKN_GPU_MAX_SIMULTANEOUS_TARGET_COUNT];
    VkImageView                                 m_ahVLKN_Colour_Image_View[KTgKN_GPU_MAX_SIMULTANEOUS_TARGET_COUNT];
    TgRSIZE                                     m_auiColour_Descriptor_Set_Index[KTgKN_GPU_MAX_SIMULTANEOUS_TARGET_COUNT];

    /* Vulkan: Pipelines */
    VkPipeline                                  m_ahVLKN_Pipeline_Graphics[ETgKN_GPU_GRAPHICS_PIPELINE_COUNT];
    VkPipeline                                  m_ahVLKN_Pipeline_Compute[ETgKN_GPU_COMPUTE_PIPELINE_FOR_RENDERING_COUNT];
};


/* ---- GPU - Contexts - Output Containers --------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_STRUCT(STg2_KN_GPU_VLKN_Output_Sync,)
{
    /* Acquire Next Back Buffer / Present Command Buffer */
    TgUINT_E64                                  m_uiTimeline_Transition_To_Render_Counter;

    /* Prepare for Present Command Buffer */
    TgUINT_E64                                  m_uiTimeline_Transition_To_Present_Counter;

    /* Binary Semaphores to Control Rendering */
    VkSemaphore                                 m_hVLKN_Semaphore_Binary_Image_Available; /* Signal semaphore when next image in swap chain available. */
    VkSemaphore                                 m_hVLKN_Semaphore_Binary_Transition_To_Present_Complete; /* Signal semaphore when back buffer is transitioned to present. */
};


/* ---- GPU Configuration -------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_STRUCT(STg2_KN_GPU_VLKN_Display_Output,)
{
    VkDisplayPropertiesKHR                      m_sVLKN_Display_Properties;
    TgRSIZE                                     m_nuiVLKN_Display_Mode;
    VkDisplayModePropertiesKHR_P                m_psVLKN_Display_Mode_Properties;
};

TgTYPE_STRUCT(STg2_KN_GPU_VLKN_Physical_Device,) /* GPU Adapter - provides scan out to output devices, and one or more GPU nodes */
{
    /* DXGI */
    TgRSIZE                                     m_uiPhysical_Device_Ordinal;

    /* Vulkan */
    VkPhysicalDevice                            m_hVLKN_Physical_Device;
    VkPhysicalDeviceProperties                  m_sVLKN_Properties;
    VkPhysicalDeviceVulkan11Features            m_sVLKN_Vulkan11_Features;
    VkPhysicalDeviceVulkan12Features            m_sVLKN_Vulkan12_Features;
    VkPhysicalDeviceVulkan13Features            m_sVLKN_Vulkan13_Features;
    VkPhysicalDeviceVulkan14Features            m_sVLKN_Vulkan14_Features;
    VkPhysicalDeviceFeatures2                   m_sVLKN_Features;
    VkPhysicalDeviceMemoryProperties2           m_sVLKN_Memory_Properties;

    VkSurfaceCapabilitiesKHR                    m_sVLKN_Surface_Capabilities;
    TgUINT_E08                                  m_uiPad1[4];
    VkSurfaceFormatKHR_P                        m_psVLKN_Surface_Format;
    TgRSIZE                                     m_nuiVLKN_Surface_Format;
    VkPresentModeKHR_P                          m_psVLKN_Present_Mode;
    TgRSIZE                                     m_nuiVLKN_Present_Mode;

    VkQueueFamilyProperties                     m_asVLKN_Queue_Family_Properties[KTgKN_GPU_VLKN_MAX_QUEUE_FAMILY];
    TgRSIZE                                     m_nuiVLKN_Queue_Family;

    TgRSIZE                                     m_auiVLKN_Queue_Family_Index[ETgKN_GPU_EXT_COMMAND_MAX];

    VkDevice                                    m_hVLKN_Device;
    TgRSIZE                                     m_auiUnique_Queue_Family_Index[ETgKN_GPU_EXT_COMMAND_MAX];
    TgRSIZE                                     m_nuiUnique_Queue_Family;

    /* Feature Flags*/
    TgUINT_E32                                  m_uiIsReset : 1;
    TgUINT_E32                                  m_uiIsWARP : 1;
    TgUINT_E32                                  m_uiPad : 30;

    /* Enumeration */
    TgUINT_E32                                  m_auiMS[KTgKN_GPU_EXT_FORMAT_RT_SCANOUT_MAX][KTgKN_GPU_MS__MAX];
    TgUINT_E08                                  m_uiPad2[4];
    TgRSIZE                                     m_tiOutput[KTgKN_GPU_MAX_OUTPUT];

    /* Debug / Troubleshooting */
    TgKN_GPU_CXT_DEVC_ID                        m_tiID_DEVC;
};


/* ---- GPU - Resource - Shader -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ---- GPU - Resource - Texture ------------------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_STRUCT(STg2_KN_GPU_VLKN_TX_CBE_INST_DATA,)
{
    VkImage                                     m_hVLKN_Image;
    VkDeviceMemory                              m_hVLKN_Image_Memory;
    VkImageView                                 m_hVLKN_Image_View;
    TgKN_GPU_TX_CBE_ID                          m_sID;
    TgUINT_E64                                  m_bInitialized : 1;
    TgUINT_E64                                  m_uiPad : 63;
};

TgTYPE_STRUCT(STg2_KN_GPU_VLKN_TX_IMG_INST_DATA,)
{
    VkImage                                     m_hVLKN_Image;
    VkDeviceMemory                              m_hVLKN_Image_Memory;
    VkImageView                                 m_hVLKN_Image_View;
    TgKN_GPU_TX_IMG_ID                          m_sID;
    TgUINT_E64                                  m_bInitialized : 1;
    TgUINT_E64                                  m_uiPad : 63;
};

TgTYPE_STRUCT(STg2_KN_GPU_VLKN_TX_VOL_INST_DATA,)
{
    VkImage                                     m_hVLKN_Image;
    VkDeviceMemory                              m_hVLKN_Image_Memory;
    VkImageView                                 m_hVLKN_Image_View;
    TgKN_GPU_TX_VOL_ID                          m_sID;
    TgUINT_E64                                  m_bInitialized : 1;
    TgUINT_E64                                  m_uiPad : 63;
};


/* ---- GPU - Resource - Render Pipeline ----------------------------------------------------------------------------------------------------------------------------------------- */

/* ---- GPU - Contexts - Execution Containers ------------------------------------------------------------------------------------------------------------------------------------ */

/*  @internal Node for lockless stack of command pools.
              Two crucial restrictions in Vulkan for command pool usage are (similar to DX12 heaps):
              - Command buffers allocated from one pool may not be recorded concurrently by multiple threads
              - Command buffers and pools can not be freed or reset while GPU is still executing the associated commands */
TgTYPE_UNION(STg2_KN_GPU_VLKN_Node_Cmd_Pool,)
{
    STg2_UT_ST__ST_Node                         m_sNode_Stack;
    struct
    {
        TgALIGN(TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE)
        STg2_UT_ST__ST_Node_Unaligned               m_sPad;
        VkCommandPool                               m_hVLKN_Command_Pool;
        STg2_UT_ST__QU                              m_sCmd_Buffer_Free_Queue;
        STg2_UT_ST__QU                              m_sCmd_Buffer_Used_Queue;
    #if 0 != (208 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE)
        TgUINT_E08                                  m_uiPad[208 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE];
    #endif
    };
};

TgTYPE_UNION(STg2_KN_GPU_VLKN_Node_Cmd_Buffer,) /* A single GPU task, for a single GPU node */
{
    STg2_UT_ST__ST_Node                         m_sNode_Stack;
    STg2_UT_ST__QU_Node                         m_sNode_Queue;
    struct
    {
        TgALIGN(TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE)
        STg2_UT_ST__ST_Node_Unaligned               m_sPad;
        VkCommandBuffer                             m_hVLKN_Command_Buffer;
    #if 0 != (240 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE)
        TgUINT_E08                                  m_uiPad[240 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE];
    #endif
    };
};

TgTYPE_UNION(STg2_KN_GPU_VLKN_Node_DS_Pool,) /* A single GPU task, for a single GPU node */
{
    STg2_UT_ST__ST_Node                         m_sNode_Stack;
    struct
    {
        TgALIGN(TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE)
        STg2_UT_ST__ST_Node_Unaligned               m_sPad;
        VkDescriptorPool                            m_hVLKN_Descriptor_Pool;
    #if 0 != (240 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE)
        TgUINT_E08                                  m_uiPad[240 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE];
    #endif
    };
};

/* @internal Execution Command Context for a single frame. */
TgTYPE_STRUCT(STg2_KN_GPU_VLKN_CXT_CMD,)
{
    /* Lock Free Stacks */
    STg2_UT_LF_ISO__ST                          m_sStack_Cmd_Pool_Free[ETgKN_GPU_EXT_COMMAND_MAX];
    STg2_UT_LF_ISO__ST                          m_sStack_Cmd_Buffer;
    STg2_UT_LF_ISO__ST                          m_sStack_DS_Pool_Free;

    /* Command Pools
       Create one command pool per thread for better performance. Keep a free list of allocated command buffers per thread for reuse. This avoids the overhead of allocating new
       command buffers each frame. But calling reset to reclaim the memory used by the allocator, the app must make sure that the GPU is no longer executing any command buffers
       which are associated with the pool. Also, note that this API is not free-threaded and therefore can't be called on the same pool at the same time from multiple threads. */

    STg2_KN_GPU_VLKN_Node_Cmd_Pool              m_asCmd_Pool__Graphics[KTgKN_GPU_MAX_HIGH_USE_ALLOC];
    STg2_KN_GPU_VLKN_Node_Cmd_Pool              m_asCmd_Pool__Present[KTgKN_GPU_MAX_LOW_USE_ALLOC];
    STg2_KN_GPU_VLKN_Node_Cmd_Pool              m_asCmd_Pool__Compute[KTgKN_GPU_MAX_HIGH_USE_ALLOC];
    STg2_KN_GPU_VLKN_Node_Cmd_Pool              m_asCmd_Pool__Transfer[KTgKN_GPU_MAX_HIGH_USE_ALLOC];
   
    /* Command Buffers - There is a reduced performance cost to reusing a command buffer frame over frame. */
    STg2_KN_GPU_VLKN_Node_Cmd_Buffer            m_asCmd_Buffer[KTgKN_GPU_EXT_MAX_COMMAND_BUFFER];

    /* Descriptor Set Pools */
    STg2_KN_GPU_VLKN_Node_DS_Pool               m_asVLKN_Descriptor_Pool[KTgKN_GPU_MAX_HIGH_USE_ALLOC];

    /* Synchronization */
    TgUINT_E64_A                                m_xuiUsed_Queue_Family_Mask; /* Bitmask tracking which queue families had work this frame */
    VkFence                                     m_ahVLKN_Queue_Fence[KTgKN_GPU_VLKN_MAX_QUEUE_FAMILY];
    VkFence                                     m_ahVLKN_Queue_Fence_End_Of_Frame[KTgKN_GPU_VLKN_MAX_QUEUE_FAMILY];
    TgRSIZE                                     m_nuiQueue_Used_In_Frame;

    /* Timestamp Query Pool for GPU Frame Time Measurement */
    VkQueryPool                                 m_hVLKN_Timestamp_Query_Pool;
    TgRSIZE_A                                   m_xuiVLKN_Timestamp;
    TgUINT_E64                                  m_auiTimestamps[KTgKN_GPU_VLKN_TIMESTAMP_QUERIES_PER_POOL];

    /* Semaphore for multithread ownership. */
    STg1_MT_SM                                  m_sLock;
    TgKN_GPU_CXT_EXEC_ID                        m_tiCXT_EXEC;
    TgKN_GPU_CXT_WORK_ID_SINGLETON              m_tiCXT_WORK_S;

    TgRSIZE_A                                   m_xuiUBO_Render_DESC_Offset;
    TgRSIZE                                     m_uiUBO_Render_DESC_End;

#if 0 != ((232 + 24 - SIZE_STg1_MT_SM) % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE)
    TgUINT_E08                                  m_uiPad[(232 + 24 - SIZE_STg1_MT_SM) % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE];
#endif
};

TgTYPE_UNION(STg2_KN_GPU_VLKN_CMD,) /* A single GPU task, for a single GPU node */
{
    STg2_UT_ST__ST_Node                         m_sNode_Stack;
    struct 
    {
        STg2_KN_GPU_CMD                             m_sBase;
        ETgKN_GPU_EXT_COMMAND                       m_enCmd_Queue;

        TgUINT_E32                                  m_uiUBO_Render_DESC_Offset; /* Valid only after setting a Render Target. */
        VkBuffer                                    m_hVLKN_Buffer__Render_DESC; /* Cache: Valid only after setting a Render Target. */

        VkDevice                                    m_hVLKN_Device; /* The device that this command is being executed on */
        VkPhysicalDeviceMemoryProperties2           m_sVLKN_Memory_Properties;
        VkCommandPool                               m_hVLKN_Command_Pool;
        VkCommandBuffer                             m_hVLKN_Command_Buffer;
        VkDescriptorPool                            m_hVLKN_Descriptor_Pool;

        STg2_KN_GPU_VLKN_Node_Cmd_Pool_P            m_psNode_Command_Pool;
        STg2_KN_GPU_VLKN_Node_Cmd_Buffer_P          m_psNode_Command_Buffer;
        STg2_KN_GPU_VLKN_Node_DS_Pool_P             m_psNode_Descriptor_Pool;

        VkPipeline                                  m_ahVLKN_Pipeline_Graphics[ETgKN_GPU_GRAPHICS_PIPELINE_COUNT];
    #if 0 != (112 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE)
        TgUINT_E08                                  m_uiPad[112 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE];
    #endif
    };
};

TgTYPE_UNION(UTg2_KN_GPU_CMD,)
{
    STg2_KN_GPU_CMD_PC                          ps;
    STg2_KN_GPU_VLKN_CMD_PC                     psVLKN;
    STg2_KN_GPU_EXT_CMD_PC                      psEXT;
};

TgTYPE_UNION(UTg2_KN_GPU_CMD_CONST,)
{
    STg2_KN_GPU_CMD_CPC                         ps;
    STg2_KN_GPU_VLKN_CMD_CPC                    psVLKN;
    STg2_KN_GPU_EXT_CMD_CPC                     psEXT;
};

TgTYPE_UNION(UTg2_KN_GPU_CMD_MUTABLE,)
{
    STg2_KN_GPU_CMD_P                           ps;
    STg2_KN_GPU_VLKN_CMD_P                      psVLKN;
    STg2_KN_GPU_EXT_CMD_P                       psEXT;
};

TgTYPE_STRUCT(STg2_KN_GPU_VLKN_CMD_Queue,) /* A single GPU task, for a single GPU node */
{
    STg2_UT_LF_ISO__SN                          m_sLock;
    TgRSIZE                                     m_uiQueue_Family_Index;
    VkQueue                                     m_hVLKN_Queue;
    VkSemaphore                                 m_hVLKN_Timeline;
    TgUINT_E64_A                                m_xuiTimeline_Signal_Value;
#if 0 != (224 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE)
    TgUINT_E08                                  m_uiPad[224 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE];
#endif
};


/* ---- GPU - Contexts ----------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_STRUCT(STg2_KN_GPU_VLKN_CXT_HOST,)
{
    VkInstance                                  m_hVLKN_Instance;
    VkDebugUtilsMessengerEXT                    m_sVLKN_Debug_Messenger;
    VkSurfaceKHR                                m_hVLKN_Temp_Surface;
    TgBOOL                                      m_bValidation_Requested;
    TgBOOL                                      m_bValidation_Enabled;
    TgBOOL                                      m_bDebug_Enabled;
    TgUINT_E08                                  m_uiPad[5];

    /* Physical Devices */
    STg2_KN_GPU_VLKN_Physical_Device            m_asEXT_Physical_Device[KTgKN_GPU_MAX_PHYSICAL_DEVICE];
    STg2_KN_GPU_VLKN_Display_Output             m_asEXT_Display_Output[KTgKN_GPU_MAX_OUTPUT];

    /* Debug / Troubleshooting */
    TgKN_GPU_CXT_HOST_ID                        m_tiID;
};

TgTYPE_STRUCT(STg2_KN_GPU_VLKN_CXT_DEVC,)
{
    TgUINT_E64                                  m_idxCXT_HOST_Physical_Device;

    /* Debug / Troubleshooting */
    TgKN_GPU_CXT_DEVC_ID                        m_tiID;
};

TgTYPE_STRUCT(STg2_KN_GPU_VLKN_CXT_EXEC, )
{
    /* Frame Data */
    STg2_KN_GPU_VLKN_CXT_CMD                    m_sContext_Command[KTgKN_GPU_MAX_EXEC_CONTEXT_COMMAND]; /**< Used to sychronize per-frame resources. */
    STg2_KN_GPU_VLKN_CMD                        m_asCommand[KTgKN_GPU_MAX_HIGH_USE_ALLOC];

    /* Release Resources */
    STg2_UT_LF_ISO__SN                          m_sRelease_Resource_Lock;

    /* Lock Free Stack */
    STg2_UT_LF_ISO__ST                          m_sCommand_Free_Stack;

    /* Frame Command Queues */
    STg2_KN_GPU_VLKN_CMD_Queue                  m_asCmd_Queue_Family_Indexed[KTgKN_GPU_VLKN_MAX_QUEUE_FAMILY];
    STg2_KN_GPU_VLKN_CMD_Queue_P                m_apsCmd_Queue[ETgKN_GPU_EXT_COMMAND_COUNT];

    /* Frame Data */
    TgRSIZE_A                                   m_xuiContext_Command_Index;

    /* Configuration Information */
    TgRSIZE                                     m_idxCXT_HOST_Physical_Device;
    VkPhysicalDevice                            m_hVLKN_Physical_Device;
    VkDevice                                    m_hVLKN_Device;
    TgRSIZE                                     m_auiVLKN_Queue_Family_Index[ETgKN_GPU_EXT_COMMAND_MAX];

    VkShaderModule                              m_ahVLKN_VS[ETgKN_GPU_SHADER_VS_COUNT];
    VkShaderModule                              m_ahVLKN_FS[ETgKN_GPU_SHADER_FS_COUNT];
    VkShaderModule                              m_ahVLKN_CS[ETgKN_GPU_SHADER_CS_COUNT];
    TgUINT_E08                                  m_uiPad0[8];

    /* Debug / Troubleshooting */
    TgKN_GPU_CXT_EXEC_ID                        m_tiCXT_EXEC;

    /* Release Resources */
    STg2_KN_GPU_VLKN_Release_Resource           m_asRelease_Resource[KTgKN_GPU_MAX_RELEASE_RESOURCE];
    TgRSIZE                                     m_uiRelease_Resource_Producer_Index;
    TgRSIZE                                     m_uiRelease_Resource_Consumer_Index;

    /* Default Resources */
    VkSampler                                   m_ahVLKN_Sampler[ETgKN_GPU_DEFAULT_SAMPLER_COUNT];
    VkDescriptorSetLayout                       m_ahVLKN_Descriptor_Set_Layout[ETgKN_GPU_VLKN_DESCRIPTOR_SET_LAYOUT_COUNT];
    VkPipelineLayout                            m_ahVLKN_Pipeline_Layout[ETgKN_GPU_PIPELINE_LAYOUT_COUNT];

    // #NOTE: Temporary - to be replaced with a mechanism that allows for render targets to be released/destroyed.
    STg2_KN_GPU_VLKN_Render_Target              m_asRender_Target[KTgKN_GPU_MAX_RENDER_TARGET];
    VkDescriptorImageInfo                       m_asVLKN_DS_Info_RT_IMG[KTgKN_GPU_MAX_RENDER_TARGET_IMAGE];
    TgRSIZE_A                                   m_xnuiRT_IMG;

    STg2_KN_GPU_VLKN_TX_IMG_INST_DATA           m_asTX_IMG_INST[KTgKN_GPU_MAX_TX_IMG_INST];
    VkDescriptorImageInfo                       m_asVLKN_DS_Info_TX_IMG[KTgKN_GPU_MAX_TX_IMG_INST];
    TgRSIZE_A                                   m_xnuiTX_IMG_INST;

    STg2_KN_GPU_VLKN_TX_CBE_INST_DATA           m_asTX_CBE_INST[KTgKN_GPU_MAX_TX_CBE_INST];
    VkDescriptorImageInfo                       m_asVLKN_DS_Info_TX_CBE[KTgKN_GPU_MAX_TX_CBE_INST];
    TgRSIZE_A                                   m_xnuiTX_CBE_INST;

    STg2_KN_GPU_VLKN_TX_VOL_INST_DATA           m_asTX_VOL_INST[KTgKN_GPU_MAX_TX_VOL_INST];
    VkDescriptorImageInfo                       m_asVLKN_DS_Info_TX_VOL[KTgKN_GPU_MAX_TX_VOL_INST];
    TgRSIZE_A                                   m_xnuiTX_VOL_INST;

    VkDescriptorPool                            m_hVLKN_Descriptor_Pool;

                                                /* Render Targets UBO is acquired through a ring buffer. */
    TgRSIZE                                     m_uiUBO_Aligned_Render_DESC_Size;
    VkBuffer                                    m_hVLKN_Buffer__Render_DESC;
    VkDeviceMemory                              m_hVLKN_Memory__Render_DESC;
    TgUN_POINTER                                m_uUBO_Mapped_Render_DESC;
    VkDescriptorSet                             m_hVLKN_Descriptor_Set_Render_DESC;

#if 0 != (144 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE)
    TgUINT_E08                                  m_uiPad1[144 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE];
#endif
};

TgTYPE_STRUCT(STg2_KN_GPU_VLKN_CXT_SWAP,) /* An output device attached to a device (single or multi-node). */
{
    /* Swap Chain Configuration */

    /* Mutex to prevent re-size operations and final swap from coinciding. */
    STg1_MT_SM                                  m_sSwap_And_View_Lock;

    /* Swap Chain */
    VkSurfaceKHR                                m_hVLKN_Surface;
    TgUINT_E32                                  m_uiCurrent_Image_Index;
    TgUINT_E08                                  m_uiPad0[4];

    TgRSIZE                                     m_nuiVLKN_Surface_Format;
    VkSurfaceFormatKHR_P                        m_psVLKN_Surface_Format;
    TgRSIZE                                     m_nuiVLKN_Present_Mode;
    VkPresentModeKHR_P                          m_penVLKN_Present_Mode;
    TgUINT_E08                                  m_uiPad1[4];

    VkSurfaceFormatKHR                          m_sVLKN_Selected_Surface_Format;
    VkPresentModeKHR                            m_enVLKN_Selected_Present_Mode;
    TgRSIZE                                     m_uiSelected_Image_Count;
    VkExtent2D                                  m_sVLKN_Selected_Extent;

    VkSwapchainKHR                              m_hVLKN_Swapchain;

    VkSurfaceCapabilitiesKHR                    m_sVLKN_Capabilities;
    TgUINT_E08                                  m_uiPad2[4];

    /* Frame Synchronization */
    TgUINT_E64_A                                m_xuiSemaphore_Timeline_Value;
    VkSemaphore                                 m_hVLKN_Semaphore_Timeline;
    STg2_KN_GPU_VLKN_Output_Sync                m_sOutput_Sync[KTgKN_GPU_MAX_BUFFER_IN_FLIP_CHAIN];

    /* Associated resources */
    STg2_KN_GPU_VLKN_Render_Target              m_asBack_Buffer__Render_Target[KTgKN_GPU_MAX_BUFFER_IN_FLIP_CHAIN];
    TgRSIZE                                     m_nuiBack_Buffer_Image;
    VkImage                                     m_ahVLKN_History_Images[KTgKN_GPU_MAX_BUFFER_IN_FLIP_CHAIN];
    VkImageView                                 m_ahVLKN_History_Image_Views[KTgKN_GPU_MAX_BUFFER_IN_FLIP_CHAIN];

    /* Debug / Troubleshooting */
    TgKN_GPU_CXT_SWAP_ID                        m_tiID;
};




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Types for Debug                                                                                                                                                       */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

#if defined(TgS_DEBUG__RENDER)
TgTYPE_STRUCT(STg2_KN_GPU_VLKN_CXT_HOST_DBG,)
{
    VkDebugUtilsMessengerEXT                    m_sVLKN_Debug_Messenger;
};
/*# defined(TgS_DEBUG__RENDER) */
#endif

/* ____ TgCOMPILE__RENDER_DEBUG_OUTPUT ___________________________________________________________________________________________________________________________________________ */
#if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)

TgCOMPILER_ASSERT(sizeof(STg2_KN_GPU_DBG_Quad) <= 128,0);
TgCOMPILER_ASSERT(sizeof(STg2_KN_GPU_DBG_Text) <= 128,0);
TgCOMPILER_ASSERT(sizeof(STg2_KN_GPU_DBG_Geom) <= 128,0);

TgTYPE_STRUCT(STg2_KN_GPU_DBG_VLKN_Render_Target,)
{
    /* Vulkan: Pipelines */
    TgALIGN(16) VkPipeline                      m_ahVLKN_Pipeline_Graphics[ETgKN_GPU_DBG_GRAPHICS_PIPELINE_COUNT];
};

TgTYPE_STRUCT(STg2_KN_GPU_DBG_VLKN_CMD,)
{
    STg2_KN_GPU_CMD_DBG                         m_sCMD_DBG;

    VkPipeline                                  m_ahVLKN_Pipeline_Graphics[ETgKN_GPU_DBG_GRAPHICS_PIPELINE_COUNT];  /* Valid only after a Beging Rendering call. */
    TgUINT_E32                                  m_uiUBO_Render_DESC_Offset; /* Valid only after setting a Render Target. */
    TgUINT_E08                                  m_uiPad[4];
};

/* @internal Execution Command Debug Context for a single frame. */
TgTYPE_STRUCT(STg2_KN_GPU_DBG_VLKN_CXT_CMD,)
{
    TgRSIZE_A                                   m_xuiSBO__Text_Offset;
    TgRSIZE                                     m_uiSBO__Text_End;

    TgRSIZE_A                                   m_xuiSBO__Line__Input_Lines_Offset;
    TgRSIZE                                     m_uiSBO__Line__Input_Lines_End;

    TgRSIZE_A                                   m_xuiSBO__Geom_Offset;
    TgRSIZE                                     m_uiSBO__Geom_End;
};

TgTYPE_STRUCT(STg2_KN_GPU_DBG_VLKN_CXT_EXEC, )
{
    STg2_KN_GPU_DBG_VLKN_CXT_CMD                m_asContext_Command_DBG[KTgKN_GPU_MAX_EXEC_CONTEXT_COMMAND]; /**< Used to sychronize per-frame resources. */
    STg2_KN_GPU_DBG_VLKN_CMD                    m_asComand_DBG[KTgKN_GPU_MAX_HIGH_USE_ALLOC];

    STg2_KN_GPU_DBG_VLKN_Render_Target          m_asRender_Target[KTgKN_GPU_MAX_RENDER_TARGET];

    TgRSIZE                                     m_idxCXT_HOST_Physical_Device;
    VkPhysicalDevice                            m_hVLKN_Physical_Device;
    VkDevice                                    m_hVLKN_Device;

    VkShaderModule                              m_ahVLKN_VS[ETgKN_GPU_DBG_SHADER_VS_COUNT];
    VkShaderModule                              m_ahVLKN_TS[ETgKN_GPU_DBG_SHADER_TS_COUNT];
    VkShaderModule                              m_ahVLKN_MS[ETgKN_GPU_DBG_SHADER_MS_COUNT];
    VkShaderModule                              m_ahVLKN_FS[ETgKN_GPU_DBG_SHADER_FS_COUNT];

    VkDescriptorSetLayout                       m_ahVLKN_Descriptor_Set_Layout[ETgKN_GPU_DBG_VLKN_DESCRIPTOR_SET_LAYOUT_COUNT];
    VkPipelineLayout                            m_ahVLKN_Pipeline_Layout[ETgKN_GPU_DBG_PIPELINE_LAYOUT_COUNT];
    VkDescriptorPool                            m_hVLKN_Descriptor_Pool;

    VkDescriptorSet                             m_hVLKN_Descriptor_Set_Render_DESC;

                                                /* Text UBO is acquired through a ring buffer, and the vertex buffer is constant. */
    VkBuffer                                    m_hVLKN_VBO_Buffer__Text;
    VkDeviceMemory                              m_hVLKN_VBO_Memory__Text;
    STg2_KN_GPU_SBO_DESC                        m_sSBO__Text;
    VkDescriptorSet                             m_hVLKN_DBG_Descriptor_Set__Text;

                                                /* Per-Draw Call data is stored as a push buffer on the draw call. */
    VkBuffer                                    m_hVLKN_VBO_Buffer__Quad;
    VkDeviceMemory                              m_hVLKN_VBO_Memory__Quad;

                                                /* Gradient specific quad used in the gradient call. */
    VkBuffer                                    m_hVLKN_VBO_Buffer__Gradient;
    VkDeviceMemory                              m_hVLKN_VBO_Memory__Gradient;

                                                /* Per-Draw Call data is stored as a push buffer on the draw call. */
    STg2_KN_GPU_SBO_DESC                        m_sSBO__Line__Input_Lines;
    VkBuffer                                    m_hVLKN_SBO_Buffer__Visible_Lines;
    VkDeviceMemory                              m_hVLKN_SBO_Memory__Visible_Lines;

    VkDescriptorSet                             m_hVLKN_DBG_Descriptor_Set__Line_Task_Mesh;

                                                /* Geometry Geom UBO (Single and Instance) are acquired from a ring buffer and the vertex, index buffers are constant. */
    VkBuffer                                    m_ahVLKN_VBO_Buffer__Geom[ETgKN_GPU_DEBUG_PM_3D_COUNT];
    VkDeviceMemory                              m_ahVLKN_VBO_Memory__Geom[ETgKN_GPU_DEBUG_PM_3D_COUNT];
    VkBuffer                                    m_ahVLKN_IBO_Buffer__Geom[ETgKN_GPU_DEBUG_PM_3D_COUNT];
    VkDeviceMemory                              m_ahVLKN_IBO_Memory__Geom[ETgKN_GPU_DEBUG_PM_3D_COUNT];
    TgRSIZE                                     m_nbyVLKN_IBO__Geom[ETgKN_GPU_DEBUG_PM_3D_COUNT];
    STg2_KN_GPU_SBO_DESC                        m_sSBO__Geom;
    VkDescriptorSet                             m_hVLKN_DBG_Descriptor_Set__Geom;

    //TgUINT_E08                                  m_uiPad4[8];
};

TgTYPE_STRUCT(STg2_KN_GPU_DBG_VLKN_CXT_SWAP, )
{
    STg2_KN_GPU_DBG_VLKN_Render_Target          m_sDBG_Back_Buffer__Render_Target;
};


/*# defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
#endif
/* ____ TgCOMPILE__RENDER_DEBUG_OUTPUT ___________________________________________________________________________________________________________________________________________ */




/* =============================================================================================================================================================================== */
#endif 
