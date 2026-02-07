/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (VULKAN) Kernel [GPU] - Data.c
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
/*  Internal Data Constants and Configuration                                                                                                                                      */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* Vulkan Validation Layers */
TgCHAR_NC_CPC                               g_apszKN_GPU_EXT_Validation_Layers[] = {
                                            #if defined(TgS_DEBUG__KERNEL_GPU)
                                                "VK_LAYER_KHRONOS_validation",
                                            #endif
                                                "VK_LAYER_LUNARG_crash_diagnostic"
                                            };
TgRSIZE_C                                   g_nuiKN_GPU_EXT_Validation_Layers = TgARRAY_COUNT(g_apszKN_GPU_EXT_Validation_Layers);

/* Vulkan Instance Extensions */
TgCHAR_NC_CPC                               g_apszKN_GPU_EXT_Instance_Extensions[] = {
                                                VK_KHR_DISPLAY_EXTENSION_NAME,
                                                VK_KHR_GET_DISPLAY_PROPERTIES_2_EXTENSION_NAME,
                                                VK_KHR_GET_SURFACE_CAPABILITIES_2_EXTENSION_NAME,
                                                VK_KHR_SURFACE_EXTENSION_NAME,
                                            #if defined(TgBUILD_OS__WINDOWS)
                                                VK_KHR_WIN32_SURFACE_EXTENSION_NAME,
                                            #elif defined(MK_BUILD_OS__POSIX)
                                                VK_KHR_XLIB_SURFACE_EXTENSION_NAME,
                                                VK_KHR_XCB_SURFACE_EXTENSION_NAME,
                                            #elif defined(MK_BUILD_OS__ANDROID)
                                                VK_KHR_ANDROID_SURFACE_EXTENSION_NAME,
                                            #endif
                                            #if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)
                                                VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
                                            #endif
                                                VK_EXT_SWAPCHAIN_COLOR_SPACE_EXTENSION_NAME,
                                            };
TgRSIZE_C                                   g_nuiKN_GPU_EXT_Instance_Extensions = TgARRAY_COUNT(g_apszKN_GPU_EXT_Instance_Extensions);

/* Vulkan Device Extensions */
TgCHAR_NC_CPC                               g_apszKN_GPU_EXT_Device_Extensions[] = {

                                                // Essential
                                                VK_KHR_SWAPCHAIN_EXTENSION_NAME,
                                                VK_KHR_SYNCHRONIZATION_2_EXTENSION_NAME,

                                                // High Performance
                                                VK_KHR_DYNAMIC_RENDERING_EXTENSION_NAME,
                                                VK_EXT_MESH_SHADER_EXTENSION_NAME,
                                                VK_EXT_SHADER_OBJECT_EXTENSION_NAME,
                                                VK_KHR_PUSH_DESCRIPTOR_EXTENSION_NAME,

                                                // Memory Management
                                                VK_EXT_MEMORY_BUDGET_EXTENSION_NAME,
                                                VK_EXT_DESCRIPTOR_INDEXING_EXTENSION_NAME,
                                                VK_KHR_BUFFER_DEVICE_ADDRESS_EXTENSION_NAME,

                                                // Modern Rendering
                                                VK_EXT_EXTENDED_DYNAMIC_STATE_EXTENSION_NAME,
                                                VK_EXT_EXTENDED_DYNAMIC_STATE_2_EXTENSION_NAME,
                                                VK_EXT_HDR_METADATA_EXTENSION_NAME,

                                                // Ray Tracing (if needed)
                                                VK_KHR_DEFERRED_HOST_OPERATIONS_EXTENSION_NAME,
                                                VK_KHR_ACCELERATION_STRUCTURE_EXTENSION_NAME,
                                                VK_KHR_RAY_TRACING_PIPELINE_EXTENSION_NAME,
                                                VK_KHR_RAY_QUERY_EXTENSION_NAME
                                            };
TgRSIZE_C                                   g_nuiKN_GPU_EXT_Device_Extensions = TgARRAY_COUNT(g_apszKN_GPU_EXT_Device_Extensions);


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Data                                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- GPU - Contexts ----------------------------------------------------------------------------------------------------------------------------------------------------------- */

STg2_KN_GPU_VLKN_CXT_HOST                   g_sKN_GPU_EXT_CXT_HOST;
STg2_KN_GPU_VLKN_CXT_DEVC                   g_asKN_GPU_EXT_CXT_DEVC[KTgKN_GPU_MAX_DEVC_CONTEXT];
STg2_KN_GPU_VLKN_CXT_EXEC                   g_asKN_GPU_EXT_CXT_EXEC[KTgKN_GPU_MAX_EXEC_CONTEXT];
STg2_KN_GPU_VLKN_CXT_SWAP                   g_asKN_GPU_EXT_CXT_SWAP[KTgKN_GPU_MAX_SWAP_CONTEXT];

#if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)
STg2_KN_GPU_DBG_VLKN_CXT_EXEC               g_asKN_GPU_DBG_EXT_CXT_EXEC[KTgKN_GPU_MAX_EXEC_CONTEXT];
STg2_KN_GPU_DBG_VLKN_CXT_SWAP               g_asKN_GPU_DBG_EXT_CXT_SWAP[KTgKN_GPU_MAX_SWAP_CONTEXT];
/*# defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
#endif


/* ---- GPU - Resource - Defaults ------------------------------------------------------------------------------------------------------------------------------------------------ */

                                            /* ---- Samplers --------------------------------------------------------------------------------------------------------------------- */

                                            /* Default samplers that will be used as immutable samplers. */
VkSamplerCI_C                               g_asKN_GPU_VLKN_Default_Sampler_Create_Info[ETgKN_GPU_DEFAULT_SAMPLER_COUNT] = {
                                                /* ETgKN_GPU_DEFAULT_SAMPLER__NEAREST_REPEAT - Nearest Repeat Sampler - For pixel art and low-res textures */
                                                {
                                                    .sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
                                                    .pNext = nullptr,
                                                    .flags = 0,
                                                    .magFilter = VK_FILTER_NEAREST,
                                                    .minFilter = VK_FILTER_NEAREST,
                                                    .mipmapMode = VK_SAMPLER_MIPMAP_MODE_NEAREST,
                                                    .addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT,
                                                    .addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT,
                                                    .addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT,
                                                    .mipLodBias = 0.0f,
                                                    .anisotropyEnable = VK_FALSE,
                                                    .maxAnisotropy = 1.0f,
                                                    .compareEnable = VK_FALSE,
                                                    .compareOp = VK_COMPARE_OP_ALWAYS,
                                                    .minLod = 0.0f,
                                                    .maxLod = VK_LOD_CLAMP_NONE,
                                                    .borderColor = VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE,
                                                    .unnormalizedCoordinates = VK_FALSE
                                                },
                                                /* ETgKN_GPU_DEFAULT_SAMPLER__NEAREST_CLAMP - Nearest Clamp Sampler - For precise pixel sampling */
                                                {
                                                    .sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
                                                    .pNext = nullptr,
                                                    .flags = 0,
                                                    .magFilter = VK_FILTER_NEAREST,
                                                    .minFilter = VK_FILTER_NEAREST,
                                                    .mipmapMode = VK_SAMPLER_MIPMAP_MODE_NEAREST,
                                                    .addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE,
                                                    .addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE,
                                                    .addressModeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE,
                                                    .mipLodBias = 0.0f,
                                                    .anisotropyEnable = VK_FALSE,
                                                    .maxAnisotropy = 1.0f,
                                                    .compareEnable = VK_FALSE,
                                                    .compareOp = VK_COMPARE_OP_ALWAYS,
                                                    .minLod = 0.0f,
                                                    .maxLod = VK_LOD_CLAMP_NONE,
                                                    .borderColor = VK_BORDER_COLOR_FLOAT_OPAQUE_BLACK,
                                                    .unnormalizedCoordinates = VK_FALSE
                                                },
                                                /* ETgKN_GPU_DEFAULT_SAMPLER__LINEAR_REPEAT - Linear Repeat Sampler - For tiling textures */
                                                {
                                                    .sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
                                                    .pNext = nullptr,
                                                    .flags = 0,
                                                    .magFilter = VK_FILTER_LINEAR,
                                                    .minFilter = VK_FILTER_LINEAR,
                                                    .mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR,
                                                    .addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT,
                                                    .addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT,
                                                    .addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT,
                                                    .mipLodBias = 0.0f,
                                                    .anisotropyEnable = VK_TRUE,
                                                    .maxAnisotropy = 16.0f,
                                                    .compareEnable = VK_FALSE,
                                                    .compareOp = VK_COMPARE_OP_ALWAYS,
                                                    .minLod = 0.0f,
                                                    .maxLod = VK_LOD_CLAMP_NONE,
                                                    .borderColor = VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE,
                                                    .unnormalizedCoordinates = VK_FALSE
                                                },
                                                /* ETgKN_GPU_DEFAULT_SAMPLER__NEAREST_CLAMP - Linear Clamp Sampler - For UI and screen-space textures */
                                                {
                                                    .sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
                                                    .pNext = nullptr,
                                                    .flags = 0,
                                                    .magFilter = VK_FILTER_LINEAR,
                                                    .minFilter = VK_FILTER_LINEAR,
                                                    .mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR,
                                                    .addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE,
                                                    .addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE,
                                                    .addressModeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE,
                                                    .mipLodBias = 0.0f,
                                                    .anisotropyEnable = VK_FALSE,
                                                    .maxAnisotropy = 1.0f,
                                                    .compareEnable = VK_FALSE,
                                                    .compareOp = VK_COMPARE_OP_ALWAYS,
                                                    .minLod = 0.0f,
                                                    .maxLod = VK_LOD_CLAMP_NONE,
                                                    .borderColor = VK_BORDER_COLOR_FLOAT_OPAQUE_BLACK,
                                                    .unnormalizedCoordinates = VK_FALSE
                                                },
                                                /* ETgKN_GPU_DEFAULT_SAMPLER__SHADOW - Shadow Sampler - For depth comparison */
                                                {
                                                    .sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
                                                    .pNext = nullptr,
                                                    .flags = 0,
                                                    .magFilter = VK_FILTER_LINEAR,
                                                    .minFilter = VK_FILTER_LINEAR,
                                                    .mipmapMode = VK_SAMPLER_MIPMAP_MODE_NEAREST,
                                                    .addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER,
                                                    .addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER,
                                                    .addressModeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER,
                                                    .mipLodBias = 0.0f,
                                                    .anisotropyEnable = VK_FALSE,
                                                    .maxAnisotropy = 1.0f,
                                                    .compareEnable = VK_TRUE,
                                                    .compareOp = VK_COMPARE_OP_LESS_OR_EQUAL,
                                                    .minLod = 0.0f,
                                                    .maxLod = 0.0f,
                                                    .borderColor = VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE,
                                                    .unnormalizedCoordinates = VK_FALSE
                                                },
                                                /* ETgKN_GPU_DEFAULT_SAMPLER__CUBEMAP - Cubemap Sampler - For environment mapping */
                                                {
                                                    .sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
                                                    .pNext = nullptr,
                                                    .flags = 0,
                                                    .magFilter = VK_FILTER_LINEAR,
                                                    .minFilter = VK_FILTER_LINEAR,
                                                    .mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR,
                                                    .addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE,
                                                    .addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE,
                                                    .addressModeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE,
                                                    .mipLodBias = 0.0f,
                                                    .anisotropyEnable = VK_FALSE,
                                                    .maxAnisotropy = 1.0f,
                                                    .compareEnable = VK_FALSE,
                                                    .compareOp = VK_COMPARE_OP_ALWAYS,
                                                    .minLod = 0.0f,
                                                    .maxLod = VK_LOD_CLAMP_NONE,
                                                    .borderColor = VK_BORDER_COLOR_FLOAT_OPAQUE_BLACK,
                                                    .unnormalizedCoordinates = VK_FALSE
                                                },
                                                /* ETgKN_GPU_DEFAULT_SAMPLER__MIRROR_REPEAT - Mirror Repeat Sampler - For special effects */
                                                {
                                                    .sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
                                                    .pNext = nullptr,
                                                    .flags = 0,
                                                    .magFilter = VK_FILTER_LINEAR,
                                                    .minFilter = VK_FILTER_LINEAR,
                                                    .mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR,
                                                    .addressModeU = VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT,
                                                    .addressModeV = VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT,
                                                    .addressModeW = VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT,
                                                    .mipLodBias = 0.0f,
                                                    .anisotropyEnable = VK_TRUE,
                                                    .maxAnisotropy = 8.0f,
                                                    .compareEnable = VK_FALSE,
                                                    .compareOp = VK_COMPARE_OP_ALWAYS,
                                                    .minLod = 0.0f,
                                                    .maxLod = VK_LOD_CLAMP_NONE,
                                                    .borderColor = VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE,
                                                    .unnormalizedCoordinates = VK_FALSE
                                                },
                                                /* ETgKN_GPU_DEFAULT_SAMPLER__HIGH_QUALITY_ANISOTROPIC - High Quality Anisotropic Sampler - For detailed textures */
                                                {
                                                    .sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
                                                    .pNext = nullptr,
                                                    .flags = 0,
                                                    .magFilter = VK_FILTER_LINEAR,
                                                    .minFilter = VK_FILTER_LINEAR,
                                                    .mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR,
                                                    .addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT,
                                                    .addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT,
                                                    .addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT,
                                                    .mipLodBias = 0.0f,
                                                    .anisotropyEnable = VK_TRUE,
                                                    .maxAnisotropy = 16.0f,
                                                    .compareEnable = VK_FALSE,
                                                    .compareOp = VK_COMPARE_OP_ALWAYS,
                                                    .minLod = 0.0f,
                                                    .maxLod = VK_LOD_CLAMP_NONE,
                                                    .borderColor = VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE,
                                                    .unnormalizedCoordinates = VK_FALSE
                                                }
                                            };

                                            /* ---- Rasterization State ---------------------------------------------------------------------------------------------------------- */

VkPipelineRasterizationStateCI_C            g_asKN_GPU_VLKN_Default_Rasterizer_CI[ETgKN_GPU_RASTERIZER_STATE_COUNT] = {
                                                {   /* ETgKN_GPU_RASTERIZER_STATE_DEFAULT_SOLID */
                                                    .sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
                                                    .pNext = nullptr,
                                                    .flags = 0,
                                                    .depthClampEnable = VK_FALSE,
                                                    .rasterizerDiscardEnable = VK_FALSE,
                                                    .polygonMode = VK_POLYGON_MODE_FILL,
                                                    .cullMode = VK_CULL_MODE_BACK_BIT,
                                                    .frontFace = VK_FRONT_FACE_CLOCKWISE,
                                                    .depthBiasEnable = VK_FALSE,
                                                    .depthBiasConstantFactor = 0.0f,
                                                    .depthBiasClamp = 0.0f,
                                                    .depthBiasSlopeFactor = 0.0f,
                                                    .lineWidth = 1.0f,
                                                },

                                                {   /* ETgKN_GPU_RASTERIZER_STATE_DEFAULT_SOLID_LINE_AA */
                                                    .sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
                                                    .pNext = nullptr,
                                                    .flags = 0,
                                                    .depthClampEnable = VK_FALSE,
                                                    .rasterizerDiscardEnable = VK_FALSE,
                                                    .polygonMode = VK_POLYGON_MODE_FILL,
                                                    .cullMode = VK_CULL_MODE_BACK_BIT,
                                                    .frontFace = VK_FRONT_FACE_CLOCKWISE,
                                                    .depthBiasEnable = VK_FALSE,
                                                    .depthBiasConstantFactor = 0.0f,
                                                    .depthBiasClamp = 0.0f,
                                                    .depthBiasSlopeFactor = 0.0f,
                                                    .lineWidth = 1.0f,
                                                },

                                                {   /* ETgKN_GPU_RASTERIZER_STATE_DEFAULT_WIREFRAME */
                                                    .sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
                                                    .pNext = nullptr,
                                                    .flags = 0,
                                                    .depthClampEnable = VK_FALSE,
                                                    .rasterizerDiscardEnable = VK_FALSE,
                                                    .polygonMode = VK_POLYGON_MODE_LINE,
                                                    .cullMode = VK_CULL_MODE_BACK_BIT,
                                                    .frontFace = VK_FRONT_FACE_CLOCKWISE,
                                                    .depthBiasEnable = VK_FALSE,
                                                    .depthBiasConstantFactor = 0.0f,
                                                    .depthBiasClamp = 0.0f,
                                                    .depthBiasSlopeFactor = 0.0f,
                                                    .lineWidth = 1.0f,
                                                },
                                            };

                                            /* ---- Depth Stencil State ---------------------------------------------------------------------------------------------------------- */

VkPipelineDepthStencilStateCI_C             g_asKN_GPU_VLKN_Default_Depth_Stencil_CI[ETgKN_GPU_DEPTH_STENCIL_STATE_COUNT] = {
                                                {   /* ETgKN_GPU_DEPTH_STENCIL_STATE_TEST_NONE */
                                                    .sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
                                                    .pNext = nullptr,
                                                    .flags = 0,
                                                    .depthTestEnable = VK_FALSE,                        /* Disable depth testing */
                                                    .depthWriteEnable = VK_FALSE,                       /* Disable depth writing */
                                                    .depthCompareOp = VK_COMPARE_OP_NEVER,              /* No comparison (ignored when disabled) */
                                                    .depthBoundsTestEnable = VK_FALSE,                  /* Disable depth bounds testing */
                                                    .stencilTestEnable = VK_FALSE,                      /* Disable stencil testing */
                                                    .front = {                                          /* Front-facing stencil (ignored when disabled) */
                                                        .failOp = VK_STENCIL_OP_KEEP,
                                                        .passOp = VK_STENCIL_OP_KEEP,
                                                        .depthFailOp = VK_STENCIL_OP_KEEP,
                                                        .compareOp = VK_COMPARE_OP_NEVER,
                                                        .compareMask = 0,
                                                        .writeMask = 0,
                                                        .reference = 0
                                                    },
                                                    .back = {                                           /* Back-facing stencil (ignored when disabled) */
                                                        .failOp = VK_STENCIL_OP_KEEP,
                                                        .passOp = VK_STENCIL_OP_KEEP,
                                                        .depthFailOp = VK_STENCIL_OP_KEEP,
                                                        .compareOp = VK_COMPARE_OP_NEVER,
                                                        .compareMask = 0,
                                                        .writeMask = 0,
                                                        .reference = 0
                                                    },
                                                    .minDepthBounds = 0.0f,                             /* Minimum depth bounds (ignored when disabled) */
                                                    .maxDepthBounds = 1.0f                              /* Maximum depth bounds (ignored when disabled) */
                                                },

                                                {   /* ETgKN_GPU_DEPTH_STENCIL_STATE_TEST_DEPTH */
                                                    .sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
                                                    .pNext = nullptr,
                                                    .flags = 0,
                                                    .depthTestEnable = VK_TRUE,                         /* Enable depth testing */
                                                    .depthWriteEnable = VK_TRUE,                        /* Enable depth writing */
                                                    .depthCompareOp = VK_COMPARE_OP_LESS,               /* Pass if incoming depth < stored depth */
                                                    .depthBoundsTestEnable = VK_FALSE,                  /* Disable depth bounds testing */
                                                    .stencilTestEnable = VK_FALSE,                      /* Disable stencil testing */
                                                    .front = {                                          /* Front-facing stencil (ignored) */
                                                        .failOp = VK_STENCIL_OP_KEEP,
                                                        .passOp = VK_STENCIL_OP_KEEP,
                                                        .depthFailOp = VK_STENCIL_OP_KEEP,
                                                        .compareOp = VK_COMPARE_OP_ALWAYS,
                                                        .compareMask = 0xFF,
                                                        .writeMask = 0xFF,
                                                        .reference = 0
                                                    },
                                                    .back = {                                           /* Back-facing stencil (ignored) */
                                                        .failOp = VK_STENCIL_OP_KEEP,
                                                        .passOp = VK_STENCIL_OP_KEEP,
                                                        .depthFailOp = VK_STENCIL_OP_KEEP,
                                                        .compareOp = VK_COMPARE_OP_ALWAYS,
                                                        .compareMask = 0xFF,
                                                        .writeMask = 0xFF,
                                                        .reference = 0
                                                    },
                                                    .minDepthBounds = 0.0f,
                                                    .maxDepthBounds = 1.0f
                                                },

                                                {   /* ETgKN_GPU_DEPTH_STENCIL_STATE_TEST_DEPTH_STENCIL */
                                                    .sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
                                                    .pNext = nullptr,
                                                    .flags = 0,
                                                    .depthTestEnable = VK_TRUE,                         /* Enable depth testing */
                                                    .depthWriteEnable = VK_TRUE,                        /* Enable depth writing */
                                                    .depthCompareOp = VK_COMPARE_OP_LESS,               /* Pass if incoming depth < stored depth */
                                                    .depthBoundsTestEnable = VK_FALSE,
                                                    .stencilTestEnable = VK_TRUE,                       /* Enable stencil testing */
                                                    .front = {                                          /* Front-facing triangles */
                                                        .failOp = VK_STENCIL_OP_KEEP,                   /* Keep stencil if stencil test fails */
                                                        .passOp = VK_STENCIL_OP_REPLACE,                /* Replace stencil if both tests pass */
                                                        .depthFailOp = VK_STENCIL_OP_KEEP,              /* Keep stencil if depth test fails */
                                                        .compareOp = VK_COMPARE_OP_EQUAL,               /* Pass if stencil values are equal */
                                                        .compareMask = 0xFF,                            /* Use all stencil bits for comparison */
                                                        .writeMask = 0xFF,                              /* Write to all stencil bits */
                                                        .reference = 1                                  /* Reference value for comparison */
                                                    },
                                                    .back = {                                           /* Back-facing triangles (usually same as front) */
                                                        .failOp = VK_STENCIL_OP_KEEP,
                                                        .passOp = VK_STENCIL_OP_REPLACE,
                                                        .depthFailOp = VK_STENCIL_OP_KEEP,
                                                        .compareOp = VK_COMPARE_OP_EQUAL,
                                                        .compareMask = 0xFF,
                                                        .writeMask = 0xFF,
                                                        .reference = 1
                                                    },
                                                    .minDepthBounds = 0.0f,
                                                    .maxDepthBounds = 1.0f
                                                },

                                                {   /* ETgKN_GPU_DEPTH_STENCIL_STATE_TEST_DEPTH_TRANSPARENT */
                                                    .sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
                                                    .pNext = nullptr,
                                                    .flags = 0,
                                                    .depthTestEnable = VK_TRUE,                         /* Enable depth testing */
                                                    .depthWriteEnable = VK_FALSE,                       /* Disable depth writing (for transparency) */
                                                    .depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL,      /* Pass if incoming depth <= stored depth */
                                                    .depthBoundsTestEnable = VK_FALSE,
                                                    .stencilTestEnable = VK_FALSE,
                                                    .front = {
                                                        .failOp = VK_STENCIL_OP_KEEP,
                                                        .passOp = VK_STENCIL_OP_KEEP,
                                                        .depthFailOp = VK_STENCIL_OP_KEEP,
                                                        .compareOp = VK_COMPARE_OP_ALWAYS,
                                                        .compareMask = 0xFF,
                                                        .writeMask = 0xFF,
                                                        .reference = 0
                                                    },
                                                    .back = {
                                                        .failOp = VK_STENCIL_OP_KEEP,
                                                        .passOp = VK_STENCIL_OP_KEEP,
                                                        .depthFailOp = VK_STENCIL_OP_KEEP,
                                                        .compareOp = VK_COMPARE_OP_ALWAYS,
                                                        .compareMask = 0xFF,
                                                        .writeMask = 0xFF,
                                                        .reference = 0
                                                    },
                                                    .minDepthBounds = 0.0f,
                                                    .maxDepthBounds = 1.0f
                                                },

                                                {   /* ETgKN_GPU_DEPTH_STENCIL_STATE_TEST_DEPTH_TRANSPARENT_STENCIL */
                                                    .sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
                                                    .pNext = nullptr,
                                                    .flags = 0,
                                                    .depthTestEnable = VK_TRUE,                         /* Enable depth testing */
                                                    .depthWriteEnable = VK_FALSE,                       /* Disable depth writing (for transparency) */
                                                    .depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL,      /* Pass if incoming depth <= stored depth */
                                                    .depthBoundsTestEnable = VK_FALSE,
                                                    .stencilTestEnable = VK_TRUE,                       /* Enable stencil testing */
                                                    .front = {                                          /* Front-facing triangles */
                                                        .failOp = VK_STENCIL_OP_KEEP,                   /* Keep stencil if stencil test fails */
                                                        .passOp = VK_STENCIL_OP_REPLACE,                /* Replace stencil if both tests pass */
                                                        .depthFailOp = VK_STENCIL_OP_KEEP,              /* Keep stencil if depth test fails */
                                                        .compareOp = VK_COMPARE_OP_EQUAL,               /* Pass if stencil values are equal */
                                                        .compareMask = 0xFF,                            /* Use all stencil bits for comparison */
                                                        .writeMask = 0xFF,                              /* Write to all stencil bits */
                                                        .reference = 1                                  /* Reference value for comparison */
                                                    },
                                                    .back = {                                           /* Back-facing triangles (usually same as front) */
                                                        .failOp = VK_STENCIL_OP_KEEP,
                                                        .passOp = VK_STENCIL_OP_REPLACE,
                                                        .depthFailOp = VK_STENCIL_OP_KEEP,
                                                        .compareOp = VK_COMPARE_OP_EQUAL,
                                                        .compareMask = 0xFF,
                                                        .writeMask = 0xFF,
                                                        .reference = 1
                                                    },
                                                    .minDepthBounds = 0.0f,
                                                    .maxDepthBounds = 1.0f
                                                },

                                                {   /* ETgKN_GPU_DEPTH_STENCIL_STATE_TEST_DEPTH_SHADOW_MAP */
                                                    .sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
                                                    .pNext = nullptr,
                                                    .flags = 0,
                                                    .depthTestEnable = VK_TRUE,                         /* Enable depth testing */
                                                    .depthWriteEnable = VK_TRUE,                        /* Enable depth writing */
                                                    .depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL,      /* Less or equal for shadow bias */
                                                    .depthBoundsTestEnable = VK_FALSE,
                                                    .stencilTestEnable = VK_FALSE,                      /* No stencil for shadow maps */
                                                    .front = {
                                                        .failOp = VK_STENCIL_OP_KEEP,
                                                        .passOp = VK_STENCIL_OP_KEEP,
                                                        .depthFailOp = VK_STENCIL_OP_KEEP,
                                                        .compareOp = VK_COMPARE_OP_ALWAYS,
                                                        .compareMask = 0,
                                                        .writeMask = 0,
                                                        .reference = 0
                                                    },
                                                    .back = {
                                                        .failOp = VK_STENCIL_OP_KEEP,
                                                        .passOp = VK_STENCIL_OP_KEEP,
                                                        .depthFailOp = VK_STENCIL_OP_KEEP,
                                                        .compareOp = VK_COMPARE_OP_ALWAYS,
                                                        .compareMask = 0,
                                                        .writeMask = 0,
                                                        .reference = 0
                                                    },
                                                    .minDepthBounds = 0.0f,
                                                    .maxDepthBounds = 1.0f
                                                },

                                                {   /* ETgKN_GPU_DEPTH_STENCIL_STATE_TEST_STENCIL */
                                                    .sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
                                                    .pNext = nullptr,
                                                    .flags = 0,
                                                    .depthTestEnable = VK_FALSE,                        /* Disable depth for UI elements */
                                                    .depthWriteEnable = VK_FALSE,
                                                    .depthCompareOp = VK_COMPARE_OP_ALWAYS,
                                                    .depthBoundsTestEnable = VK_FALSE,
                                                    .stencilTestEnable = VK_TRUE,                       /* Enable stencil for masking */
                                                    .front = {
                                                        .failOp = VK_STENCIL_OP_ZERO,                   /* Clear stencil on fail */
                                                        .passOp = VK_STENCIL_OP_REPLACE,                /* Set stencil value on pass */
                                                        .depthFailOp = VK_STENCIL_OP_ZERO,              /* Clear stencil on depth fail */
                                                        .compareOp = VK_COMPARE_OP_ALWAYS,              /* Always pass stencil test */
                                                        .compareMask = 0xFF,
                                                        .writeMask = 0xFF,
                                                        .reference = 1                                  /* Set stencil to 1 */
                                                    },
                                                    .back = {
                                                        .failOp = VK_STENCIL_OP_ZERO,
                                                        .passOp = VK_STENCIL_OP_REPLACE,
                                                        .depthFailOp = VK_STENCIL_OP_ZERO,
                                                        .compareOp = VK_COMPARE_OP_ALWAYS,
                                                        .compareMask = 0xFF,
                                                        .writeMask = 0xFF,
                                                        .reference = 1
                                                    },
                                                    .minDepthBounds = 0.0f,
                                                    .maxDepthBounds = 1.0f
                                                },

                                            };

                                            /* ---- Color Blend Attachment States ------------------------------------------------------------------------------------------------ */

VkPipelineColorBlendAttachmentState_C       g_asKN_GPU_VLKN_Default_Blend_Attachment[ETgKN_GPU_BLEND_STATE_COUNT] = {
                                                {   /* ETgKN_GPU_BLEND_STATE_NONE/OPAQUE */
                                                    .blendEnable = VK_FALSE,
                                                    .srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA,
                                                    .dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,
                                                    .colorBlendOp = VK_BLEND_OP_ADD,
                                                    .srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE,
                                                    .dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO,
                                                    .alphaBlendOp = VK_BLEND_OP_ADD,
                                                    .colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT,
                                                },

                                                {   /* ETgKN_GPU_BLEND_STATE_ALPHA */
                                                    .blendEnable = VK_TRUE,
                                                    .srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA,
                                                    .dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,
                                                    .colorBlendOp = VK_BLEND_OP_ADD,
                                                    .srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE,
                                                    .dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO,
                                                    .alphaBlendOp = VK_BLEND_OP_ADD,
                                                    .colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT
                                                },

                                                {   /* ETgKN_GPU_BLEND_STATE_ALPHA_PREMULT */
                                                    .blendEnable = VK_TRUE,
                                                    .srcColorBlendFactor = VK_BLEND_FACTOR_ONE,
                                                    .dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,
                                                    .colorBlendOp = VK_BLEND_OP_ADD,
                                                    .srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE,
                                                    .dstAlphaBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,
                                                    .alphaBlendOp = VK_BLEND_OP_ADD,
                                                    .colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT
                                                },

                                                {   /* ETgKN_GPU_BLEND_STATE_ADDITIVE */
                                                    .blendEnable = VK_TRUE,
                                                    .srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA,
                                                    .dstColorBlendFactor = VK_BLEND_FACTOR_ONE,
                                                    .colorBlendOp = VK_BLEND_OP_ADD,
                                                    .srcAlphaBlendFactor = VK_BLEND_FACTOR_ZERO,
                                                    .dstAlphaBlendFactor = VK_BLEND_FACTOR_ONE,
                                                    .alphaBlendOp = VK_BLEND_OP_ADD,
                                                    .colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT
                                                },
                                            };

#define RENDER_INPUT_LAYOUT_START(A,B)                              static const VkVertexInputAttributeDescription sVLKN_Input_Attribute_##A[] = {
#define RENDER_INPUT_LAYOUT_PER_VERTEX(A, B, C, D, E, F, G, ...)        { .location = B, .binding = 0, .format = (VkFormat)E, .offset = offsetof(STg2_KN_GPU_##A, F) },
#define RENDER_INPUT_LAYOUT_PER_VERTEX_APPEND(A, B, C, D, E, F, G, ...) { .location = B, .binding = 0, .format = (VkFormat)E, .offset = offsetof(STg2_KN_GPU_##A, F) },
#define RENDER_INPUT_LAYOUT_END(A)                                  };
#define RENDER_INPUT_ALIGNMENT_CHECK(A,B)

    #include "TgS KERNEL/TgS Kernel [GPU] - Resource [HLSL] [Vertex] [INC].h"

#undef RENDER_INPUT_LAYOUT_PER_VERTEX_APPEND
#undef RENDER_INPUT_LAYOUT_PER_VERTEX
#undef RENDER_INPUT_LAYOUT_START

#define RENDER_INPUT_LAYOUT_START(A,B)                              static const VkVertexInputBindingDescription sVLKN_Input_Binding_##A[] = { \
                                                                        { .binding = 0, .stride = sizeof(STg2_KN_GPU_##A), .inputRate = VK_VERTEX_INPUT_RATE_VERTEX },
#define RENDER_INPUT_LAYOUT_PER_VERTEX(A, B, C, D, E, F, G, ...)
#define RENDER_INPUT_LAYOUT_PER_VERTEX_APPEND(A, B, C, D, E, F, G, ...)

    #include "TgS KERNEL/TgS Kernel [GPU] - Resource [HLSL] [Vertex] [INC].h"

/* Note: gl_InstanceIndex is supported in Vulkan, and so we can re-use the same binding for instance data as well. */

#undef RENDER_INPUT_LAYOUT_END
#define RENDER_INPUT_LAYOUT_END(A)

VkPipelineVertexInputStateCI_C              g_asKN_GPU_VLKN_Vertex_Input_State[ETgKN_GPU_INPUT_LAYOUT_COUNT] = {
    #undef RENDER_INPUT_LAYOUT_START
    #define RENDER_INPUT_LAYOUT_START(A,B) { \
        .sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO, \
        .pNext = nullptr, \
        .flags = 0, \
        .vertexBindingDescriptionCount = TgARRAY_COUNT(sVLKN_Input_Binding_##A), \
        .pVertexBindingDescriptions = sVLKN_Input_Binding_##A, \
        .vertexAttributeDescriptionCount = TgARRAY_COUNT(sVLKN_Input_Attribute_##A), \
        .pVertexAttributeDescriptions = sVLKN_Input_Attribute_##A \
    },
    
    #include "TgS KERNEL/TgS Kernel [GPU] - Resource [HLSL] [Vertex] [INC].h"
    
    #undef RENDER_INPUT_LAYOUT_START
    #define RENDER_INPUT_LAYOUT_START(A,B) { \
        .sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO, \
        .pNext = nullptr, \
        .flags = 0, \
        .vertexBindingDescriptionCount = TgARRAY_COUNT(sVLKN_Input_Binding_##A), \
        .pVertexBindingDescriptions = sVLKN_Input_Binding_##A, \
        .vertexAttributeDescriptionCount = TgARRAY_COUNT(sVLKN_Input_Attribute_##A), \
        .pVertexAttributeDescriptions = sVLKN_Input_Attribute_##A \
    },
    
    #include "TgS KERNEL/TgS Kernel [GPU] - Resource [HLSL] [Vertex] [INC].h"
};
#undef RENDER_INPUT_ALIGNMENT_CHECK
#undef RENDER_INPUT_LAYOUT_END
#undef RENDER_INPUT_LAYOUT_PER_VERTEX_APPEND
#undef RENDER_INPUT_LAYOUT_PER_VERTEX
#undef RENDER_INPUT_LAYOUT_START




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Validation                                                                                                                                                                     */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_UNDEFINED == (TgSINT_E32)VK_FORMAT_UNDEFINED, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_UNDEFINED == (TgSINT_E32)VK_FORMAT_UNDEFINED, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R4G4_UNORM_PACK8 == (TgSINT_E32)VK_FORMAT_R4G4_UNORM_PACK8, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R4G4B4A4_UNORM_PACK16 == (TgSINT_E32)VK_FORMAT_R4G4B4A4_UNORM_PACK16, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_B4G4R4A4_UNORM_PACK16 == (TgSINT_E32)VK_FORMAT_B4G4R4A4_UNORM_PACK16, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R5G6B5_UNORM_PACK16 == (TgSINT_E32)VK_FORMAT_R5G6B5_UNORM_PACK16, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_B5G6R5_UNORM_PACK16 == (TgSINT_E32)VK_FORMAT_B5G6R5_UNORM_PACK16, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R5G5B5A1_UNORM_PACK16 == (TgSINT_E32)VK_FORMAT_R5G5B5A1_UNORM_PACK16, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_B5G5R5A1_UNORM_PACK16 == (TgSINT_E32)VK_FORMAT_B5G5R5A1_UNORM_PACK16, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_A1R5G5B5_UNORM_PACK16 == (TgSINT_E32)VK_FORMAT_A1R5G5B5_UNORM_PACK16, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R8_UNORM == (TgSINT_E32)VK_FORMAT_R8_UNORM, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R8_SNORM == (TgSINT_E32)VK_FORMAT_R8_SNORM, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R8_USCALED == (TgSINT_E32)VK_FORMAT_R8_USCALED, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R8_SSCALED == (TgSINT_E32)VK_FORMAT_R8_SSCALED, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R8_UINT == (TgSINT_E32)VK_FORMAT_R8_UINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R8_SINT == (TgSINT_E32)VK_FORMAT_R8_SINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R8_SRGB == (TgSINT_E32)VK_FORMAT_R8_SRGB, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R8G8_UNORM == (TgSINT_E32)VK_FORMAT_R8G8_UNORM, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R8G8_SNORM == (TgSINT_E32)VK_FORMAT_R8G8_SNORM, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R8G8_USCALED == (TgSINT_E32)VK_FORMAT_R8G8_USCALED, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R8G8_SSCALED == (TgSINT_E32)VK_FORMAT_R8G8_SSCALED, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R8G8_UINT == (TgSINT_E32)VK_FORMAT_R8G8_UINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R8G8_SINT == (TgSINT_E32)VK_FORMAT_R8G8_SINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R8G8_SRGB == (TgSINT_E32)VK_FORMAT_R8G8_SRGB, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R8G8B8_UNORM == (TgSINT_E32)VK_FORMAT_R8G8B8_UNORM, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R8G8B8_SNORM == (TgSINT_E32)VK_FORMAT_R8G8B8_SNORM, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R8G8B8_USCALED == (TgSINT_E32)VK_FORMAT_R8G8B8_USCALED, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R8G8B8_SSCALED == (TgSINT_E32)VK_FORMAT_R8G8B8_SSCALED, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R8G8B8_UINT == (TgSINT_E32)VK_FORMAT_R8G8B8_UINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R8G8B8_SINT == (TgSINT_E32)VK_FORMAT_R8G8B8_SINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R8G8B8_SRGB == (TgSINT_E32)VK_FORMAT_R8G8B8_SRGB, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_B8G8R8_UNORM == (TgSINT_E32)VK_FORMAT_B8G8R8_UNORM, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_B8G8R8_SNORM == (TgSINT_E32)VK_FORMAT_B8G8R8_SNORM, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_B8G8R8_USCALED == (TgSINT_E32)VK_FORMAT_B8G8R8_USCALED, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_B8G8R8_SSCALED == (TgSINT_E32)VK_FORMAT_B8G8R8_SSCALED, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_B8G8R8_UINT == (TgSINT_E32)VK_FORMAT_B8G8R8_UINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_B8G8R8_SINT == (TgSINT_E32)VK_FORMAT_B8G8R8_SINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_B8G8R8_SRGB == (TgSINT_E32)VK_FORMAT_B8G8R8_SRGB, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R8G8B8A8_UNORM == (TgSINT_E32)VK_FORMAT_R8G8B8A8_UNORM, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R8G8B8A8_SNORM == (TgSINT_E32)VK_FORMAT_R8G8B8A8_SNORM, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R8G8B8A8_USCALED == (TgSINT_E32)VK_FORMAT_R8G8B8A8_USCALED, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R8G8B8A8_SSCALED == (TgSINT_E32)VK_FORMAT_R8G8B8A8_SSCALED, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R8G8B8A8_UINT == (TgSINT_E32)VK_FORMAT_R8G8B8A8_UINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R8G8B8A8_SINT == (TgSINT_E32)VK_FORMAT_R8G8B8A8_SINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R8G8B8A8_SRGB == (TgSINT_E32)VK_FORMAT_R8G8B8A8_SRGB, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_B8G8R8A8_UNORM == (TgSINT_E32)VK_FORMAT_B8G8R8A8_UNORM, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_B8G8R8A8_SNORM == (TgSINT_E32)VK_FORMAT_B8G8R8A8_SNORM, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_B8G8R8A8_USCALED == (TgSINT_E32)VK_FORMAT_B8G8R8A8_USCALED, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_B8G8R8A8_SSCALED == (TgSINT_E32)VK_FORMAT_B8G8R8A8_SSCALED, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_B8G8R8A8_UINT == (TgSINT_E32)VK_FORMAT_B8G8R8A8_UINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_B8G8R8A8_SINT == (TgSINT_E32)VK_FORMAT_B8G8R8A8_SINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_B8G8R8A8_SRGB == (TgSINT_E32)VK_FORMAT_B8G8R8A8_SRGB, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_A8B8G8R8_UNORM_PACK32 == (TgSINT_E32)VK_FORMAT_A8B8G8R8_UNORM_PACK32, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_A8B8G8R8_SNORM_PACK32 == (TgSINT_E32)VK_FORMAT_A8B8G8R8_SNORM_PACK32, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_A8B8G8R8_USCALED_PACK32 == (TgSINT_E32)VK_FORMAT_A8B8G8R8_USCALED_PACK32, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_A8B8G8R8_SSCALED_PACK32 == (TgSINT_E32)VK_FORMAT_A8B8G8R8_SSCALED_PACK32, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_A8B8G8R8_UINT_PACK32 == (TgSINT_E32)VK_FORMAT_A8B8G8R8_UINT_PACK32, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_A8B8G8R8_SINT_PACK32 == (TgSINT_E32)VK_FORMAT_A8B8G8R8_SINT_PACK32, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_A8B8G8R8_SRGB_PACK32 == (TgSINT_E32)VK_FORMAT_A8B8G8R8_SRGB_PACK32, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_A2R10G10B10_UNORM_PACK32 == (TgSINT_E32)VK_FORMAT_A2R10G10B10_UNORM_PACK32, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_A2R10G10B10_SNORM_PACK32 == (TgSINT_E32)VK_FORMAT_A2R10G10B10_SNORM_PACK32, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_A2R10G10B10_USCALED_PACK32 == (TgSINT_E32)VK_FORMAT_A2R10G10B10_USCALED_PACK32, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_A2R10G10B10_SSCALED_PACK32 == (TgSINT_E32)VK_FORMAT_A2R10G10B10_SSCALED_PACK32, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_A2R10G10B10_UINT_PACK32 == (TgSINT_E32)VK_FORMAT_A2R10G10B10_UINT_PACK32, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_A2R10G10B10_SINT_PACK32 == (TgSINT_E32)VK_FORMAT_A2R10G10B10_SINT_PACK32, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_A2B10G10R10_UNORM_PACK32 == (TgSINT_E32)VK_FORMAT_A2B10G10R10_UNORM_PACK32, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_A2B10G10R10_SNORM_PACK32 == (TgSINT_E32)VK_FORMAT_A2B10G10R10_SNORM_PACK32, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_A2B10G10R10_USCALED_PACK32 == (TgSINT_E32)VK_FORMAT_A2B10G10R10_USCALED_PACK32, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_A2B10G10R10_SSCALED_PACK32 == (TgSINT_E32)VK_FORMAT_A2B10G10R10_SSCALED_PACK32, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_A2B10G10R10_UINT_PACK32 == (TgSINT_E32)VK_FORMAT_A2B10G10R10_UINT_PACK32, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_A2B10G10R10_SINT_PACK32 == (TgSINT_E32)VK_FORMAT_A2B10G10R10_SINT_PACK32, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R16_UNORM == (TgSINT_E32)VK_FORMAT_R16_UNORM, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R16_SNORM == (TgSINT_E32)VK_FORMAT_R16_SNORM, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R16_USCALED == (TgSINT_E32)VK_FORMAT_R16_USCALED, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R16_SSCALED == (TgSINT_E32)VK_FORMAT_R16_SSCALED, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R16_UINT == (TgSINT_E32)VK_FORMAT_R16_UINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R16_SINT == (TgSINT_E32)VK_FORMAT_R16_SINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R16_SFLOAT == (TgSINT_E32)VK_FORMAT_R16_SFLOAT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R16G16_UNORM == (TgSINT_E32)VK_FORMAT_R16G16_UNORM, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R16G16_SNORM == (TgSINT_E32)VK_FORMAT_R16G16_SNORM, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R16G16_USCALED == (TgSINT_E32)VK_FORMAT_R16G16_USCALED, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R16G16_SSCALED == (TgSINT_E32)VK_FORMAT_R16G16_SSCALED, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R16G16_UINT == (TgSINT_E32)VK_FORMAT_R16G16_UINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R16G16_SINT == (TgSINT_E32)VK_FORMAT_R16G16_SINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R16G16_SFLOAT == (TgSINT_E32)VK_FORMAT_R16G16_SFLOAT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R16G16B16_UNORM == (TgSINT_E32)VK_FORMAT_R16G16B16_UNORM, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R16G16B16_SNORM == (TgSINT_E32)VK_FORMAT_R16G16B16_SNORM, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R16G16B16_USCALED == (TgSINT_E32)VK_FORMAT_R16G16B16_USCALED, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R16G16B16_SSCALED == (TgSINT_E32)VK_FORMAT_R16G16B16_SSCALED, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R16G16B16_UINT == (TgSINT_E32)VK_FORMAT_R16G16B16_UINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R16G16B16_SINT == (TgSINT_E32)VK_FORMAT_R16G16B16_SINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R16G16B16_SFLOAT == (TgSINT_E32)VK_FORMAT_R16G16B16_SFLOAT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R16G16B16A16_UNORM == (TgSINT_E32)VK_FORMAT_R16G16B16A16_UNORM, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R16G16B16A16_SNORM == (TgSINT_E32)VK_FORMAT_R16G16B16A16_SNORM, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R16G16B16A16_USCALED == (TgSINT_E32)VK_FORMAT_R16G16B16A16_USCALED, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R16G16B16A16_SSCALED == (TgSINT_E32)VK_FORMAT_R16G16B16A16_SSCALED, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R16G16B16A16_UINT == (TgSINT_E32)VK_FORMAT_R16G16B16A16_UINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R16G16B16A16_SINT == (TgSINT_E32)VK_FORMAT_R16G16B16A16_SINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R16G16B16A16_SFLOAT == (TgSINT_E32)VK_FORMAT_R16G16B16A16_SFLOAT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R32_UINT == (TgSINT_E32)VK_FORMAT_R32_UINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R32_SINT == (TgSINT_E32)VK_FORMAT_R32_SINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R32_SFLOAT == (TgSINT_E32)VK_FORMAT_R32_SFLOAT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R32G32_UINT == (TgSINT_E32)VK_FORMAT_R32G32_UINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R32G32_SINT == (TgSINT_E32)VK_FORMAT_R32G32_SINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R32G32_SFLOAT == (TgSINT_E32)VK_FORMAT_R32G32_SFLOAT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R32G32B32_UINT == (TgSINT_E32)VK_FORMAT_R32G32B32_UINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R32G32B32_SINT == (TgSINT_E32)VK_FORMAT_R32G32B32_SINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R32G32B32_SFLOAT == (TgSINT_E32)VK_FORMAT_R32G32B32_SFLOAT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R32G32B32A32_UINT == (TgSINT_E32)VK_FORMAT_R32G32B32A32_UINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R32G32B32A32_SINT == (TgSINT_E32)VK_FORMAT_R32G32B32A32_SINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R32G32B32A32_SFLOAT == (TgSINT_E32)VK_FORMAT_R32G32B32A32_SFLOAT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R64_UINT == (TgSINT_E32)VK_FORMAT_R64_UINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R64_SINT == (TgSINT_E32)VK_FORMAT_R64_SINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R64_SFLOAT == (TgSINT_E32)VK_FORMAT_R64_SFLOAT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R64G64_UINT == (TgSINT_E32)VK_FORMAT_R64G64_UINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R64G64_SINT == (TgSINT_E32)VK_FORMAT_R64G64_SINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R64G64_SFLOAT == (TgSINT_E32)VK_FORMAT_R64G64_SFLOAT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R64G64B64_UINT == (TgSINT_E32)VK_FORMAT_R64G64B64_UINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R64G64B64_SINT == (TgSINT_E32)VK_FORMAT_R64G64B64_SINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R64G64B64_SFLOAT == (TgSINT_E32)VK_FORMAT_R64G64B64_SFLOAT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R64G64B64A64_UINT == (TgSINT_E32)VK_FORMAT_R64G64B64A64_UINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R64G64B64A64_SINT == (TgSINT_E32)VK_FORMAT_R64G64B64A64_SINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_R64G64B64A64_SFLOAT == (TgSINT_E32)VK_FORMAT_R64G64B64A64_SFLOAT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_B10G11R11_UFLOAT_PACK32 == (TgSINT_E32)VK_FORMAT_B10G11R11_UFLOAT_PACK32, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_E5B9G9R9_UFLOAT_PACK32 == (TgSINT_E32)VK_FORMAT_E5B9G9R9_UFLOAT_PACK32, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_D16_UNORM == (TgSINT_E32)VK_FORMAT_D16_UNORM, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_X8_D24_UNORM_PACK32 == (TgSINT_E32)VK_FORMAT_X8_D24_UNORM_PACK32, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_D32_SFLOAT == (TgSINT_E32)VK_FORMAT_D32_SFLOAT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_S8_UINT == (TgSINT_E32)VK_FORMAT_S8_UINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_D16_UNORM_S8_UINT == (TgSINT_E32)VK_FORMAT_D16_UNORM_S8_UINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_D24_UNORM_S8_UINT == (TgSINT_E32)VK_FORMAT_D24_UNORM_S8_UINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_D32_SFLOAT_S8_UINT == (TgSINT_E32)VK_FORMAT_D32_SFLOAT_S8_UINT, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_BC1_RGB_UNORM_BLOCK == (TgSINT_E32)VK_FORMAT_BC1_RGB_UNORM_BLOCK, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_BC1_RGB_SRGB_BLOCK == (TgSINT_E32)VK_FORMAT_BC1_RGB_SRGB_BLOCK, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_BC1_RGBA_UNORM_BLOCK == (TgSINT_E32)VK_FORMAT_BC1_RGBA_UNORM_BLOCK, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_BC1_RGBA_SRGB_BLOCK == (TgSINT_E32)VK_FORMAT_BC1_RGBA_SRGB_BLOCK, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_BC2_UNORM_BLOCK == (TgSINT_E32)VK_FORMAT_BC2_UNORM_BLOCK, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_BC2_SRGB_BLOCK == (TgSINT_E32)VK_FORMAT_BC2_SRGB_BLOCK, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_BC3_UNORM_BLOCK == (TgSINT_E32)VK_FORMAT_BC3_UNORM_BLOCK, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_BC3_SRGB_BLOCK == (TgSINT_E32)VK_FORMAT_BC3_SRGB_BLOCK, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_BC4_UNORM_BLOCK == (TgSINT_E32)VK_FORMAT_BC4_UNORM_BLOCK, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_BC4_SNORM_BLOCK == (TgSINT_E32)VK_FORMAT_BC4_SNORM_BLOCK, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_BC5_UNORM_BLOCK == (TgSINT_E32)VK_FORMAT_BC5_UNORM_BLOCK, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_BC5_SNORM_BLOCK == (TgSINT_E32)VK_FORMAT_BC5_SNORM_BLOCK, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_BC6H_UFLOAT_BLOCK == (TgSINT_E32)VK_FORMAT_BC6H_UFLOAT_BLOCK, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_BC6H_SFLOAT_BLOCK == (TgSINT_E32)VK_FORMAT_BC6H_SFLOAT_BLOCK, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_BC7_UNORM_BLOCK == (TgSINT_E32)VK_FORMAT_BC7_UNORM_BLOCK, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_BC7_SRGB_BLOCK == (TgSINT_E32)VK_FORMAT_BC7_SRGB_BLOCK, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_ETC2_R8G8B8_UNORM_BLOCK == (TgSINT_E32)VK_FORMAT_ETC2_R8G8B8_UNORM_BLOCK, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_ETC2_R8G8B8_SRGB_BLOCK == (TgSINT_E32)VK_FORMAT_ETC2_R8G8B8_SRGB_BLOCK, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_ETC2_R8G8B8A1_UNORM_BLOCK == (TgSINT_E32)VK_FORMAT_ETC2_R8G8B8A1_UNORM_BLOCK, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_ETC2_R8G8B8A1_SRGB_BLOCK == (TgSINT_E32)VK_FORMAT_ETC2_R8G8B8A1_SRGB_BLOCK, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_ETC2_R8G8B8A8_UNORM_BLOCK == (TgSINT_E32)VK_FORMAT_ETC2_R8G8B8A8_UNORM_BLOCK, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_ETC2_R8G8B8A8_SRGB_BLOCK == (TgSINT_E32)VK_FORMAT_ETC2_R8G8B8A8_SRGB_BLOCK, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_EAC_R11_UNORM_BLOCK == (TgSINT_E32)VK_FORMAT_EAC_R11_UNORM_BLOCK, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_EAC_R11_SNORM_BLOCK == (TgSINT_E32)VK_FORMAT_EAC_R11_SNORM_BLOCK, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_EAC_R11G11_UNORM_BLOCK == (TgSINT_E32)VK_FORMAT_EAC_R11G11_UNORM_BLOCK, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_EAC_R11G11_SNORM_BLOCK == (TgSINT_E32)VK_FORMAT_EAC_R11G11_SNORM_BLOCK, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_ASTC_4x4_UNORM_BLOCK == (TgSINT_E32)VK_FORMAT_ASTC_4x4_UNORM_BLOCK, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_ASTC_4x4_SRGB_BLOCK == (TgSINT_E32)VK_FORMAT_ASTC_4x4_SRGB_BLOCK, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_ASTC_5x4_UNORM_BLOCK == (TgSINT_E32)VK_FORMAT_ASTC_5x4_UNORM_BLOCK, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_ASTC_5x4_SRGB_BLOCK == (TgSINT_E32)VK_FORMAT_ASTC_5x4_SRGB_BLOCK, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_ASTC_5x5_UNORM_BLOCK == (TgSINT_E32)VK_FORMAT_ASTC_5x5_UNORM_BLOCK, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_ASTC_5x5_SRGB_BLOCK == (TgSINT_E32)VK_FORMAT_ASTC_5x5_SRGB_BLOCK, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_ASTC_6x5_UNORM_BLOCK == (TgSINT_E32)VK_FORMAT_ASTC_6x5_UNORM_BLOCK, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_ASTC_6x5_SRGB_BLOCK == (TgSINT_E32)VK_FORMAT_ASTC_6x5_SRGB_BLOCK, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_ASTC_6x6_UNORM_BLOCK == (TgSINT_E32)VK_FORMAT_ASTC_6x6_UNORM_BLOCK, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_ASTC_6x6_SRGB_BLOCK == (TgSINT_E32)VK_FORMAT_ASTC_6x6_SRGB_BLOCK, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_ASTC_8x5_UNORM_BLOCK == (TgSINT_E32)VK_FORMAT_ASTC_8x5_UNORM_BLOCK, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_ASTC_8x5_SRGB_BLOCK == (TgSINT_E32)VK_FORMAT_ASTC_8x5_SRGB_BLOCK, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_ASTC_8x6_UNORM_BLOCK == (TgSINT_E32)VK_FORMAT_ASTC_8x6_UNORM_BLOCK, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_ASTC_8x6_SRGB_BLOCK == (TgSINT_E32)VK_FORMAT_ASTC_8x6_SRGB_BLOCK, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_ASTC_8x8_UNORM_BLOCK == (TgSINT_E32)VK_FORMAT_ASTC_8x8_UNORM_BLOCK, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_ASTC_8x8_SRGB_BLOCK == (TgSINT_E32)VK_FORMAT_ASTC_8x8_SRGB_BLOCK, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_ASTC_10x5_UNORM_BLOCK == (TgSINT_E32)VK_FORMAT_ASTC_10x5_UNORM_BLOCK, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_ASTC_10x5_SRGB_BLOCK == (TgSINT_E32)VK_FORMAT_ASTC_10x5_SRGB_BLOCK, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_ASTC_10x6_UNORM_BLOCK == (TgSINT_E32)VK_FORMAT_ASTC_10x6_UNORM_BLOCK, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_ASTC_10x6_SRGB_BLOCK == (TgSINT_E32)VK_FORMAT_ASTC_10x6_SRGB_BLOCK, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_ASTC_10x8_UNORM_BLOCK == (TgSINT_E32)VK_FORMAT_ASTC_10x8_UNORM_BLOCK, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_ASTC_10x8_SRGB_BLOCK == (TgSINT_E32)VK_FORMAT_ASTC_10x8_SRGB_BLOCK, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_ASTC_10x10_UNORM_BLOCK == (TgSINT_E32)VK_FORMAT_ASTC_10x10_UNORM_BLOCK, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_ASTC_10x10_SRGB_BLOCK == (TgSINT_E32)VK_FORMAT_ASTC_10x10_SRGB_BLOCK, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_ASTC_12x10_UNORM_BLOCK == (TgSINT_E32)VK_FORMAT_ASTC_12x10_UNORM_BLOCK, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_ASTC_12x10_SRGB_BLOCK == (TgSINT_E32)VK_FORMAT_ASTC_12x10_SRGB_BLOCK, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_ASTC_12x12_UNORM_BLOCK == (TgSINT_E32)VK_FORMAT_ASTC_12x12_UNORM_BLOCK, 0 );
TgCOMPILER_ASSERT( (TgSINT_E32)ETgKN_GPU_EXT_FORMAT_ASTC_12x12_SRGB_BLOCK == (TgSINT_E32)VK_FORMAT_ASTC_12x12_SRGB_BLOCK, 0 );
