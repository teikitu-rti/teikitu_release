/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (VULKAN) Kernel [GPU] - Internal - Data.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.22 | »GUID« 7ECEAB43-40E4-4161-8F94-87AF31F5BA9A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    Models:     Claude 3.7, Claude 4.0
    ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_VULKAN_KERNEL_GPU_INTERNAL_DATA_H)
#define TGS_VULKAN_KERNEL_GPU_INTERNAL_DATA_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif


/* == Kernel ===================================================================================================================================================================== */

/* ══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════
* DEPTH-ONLY RENDERING OPTIMIZED DESCRIPTOR SET LAYOUT DESIGN
* ═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════
* 
* Specialized for depth-only rendering passes with extreme performance focus:
* 
* DEPTH-ONLY SPECIFIC OPTIMIZATIONS:
* • Minimal Memory Bandwidth: Only essential transform and culling data
* • GPU-Driven Rendering: Indirect draws with GPU culling for massive object counts
* • Early Z Optimization: Layout optimized for maximum early-Z rejection
* • Instanced Rendering: Massive instancing support with minimal per-instance data
* • Alpha Testing Support: Minimal texture binding for alpha-tested geometry
* 
* PERFORMANCE CHARACTERISTICS:
* • Zero Fragment Shading: No color/material data, only depth writes
* • Maximum Throughput: Optimized for rendering millions of objects
* • GPU Culling Integration: Frustum, occlusion, and distance culling
* • Minimal CPU Overhead: Push constants and storage buffers only
* • Memory Bandwidth Minimal: Only transform matrices and alpha textures
* 
* USE CASES:
* • Shadow Map Generation (directional, spot, point lights)
* • Z-Prepass for complex scenes
* • Occlusion Queries
* • Depth-based GPU culling
* • Hi-Z buffer generation
* ════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════ */

/* ══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════
* PERFORMANCE-OPTIMIZED DESCRIPTOR SET LAYOUT DESIGN
* ═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════
* 
* This layout is designed for maximum CPU and GPU performance using modern Vulkan techniques:
* 
* CPU PERFORMANCE OPTIMIZATIONS:
* • Bindless Rendering: Large texture arrays eliminate per-draw descriptor set updates
* • Push Descriptors: Set 1 uses VK_KHR_push_descriptor for zero-allocation per-draw updates
* • Push Constants: Ultra-fast 128 bytes for material indices and transform data
* • Immutable Samplers: Zero CPU overhead for sampler binding
* • Minimal Descriptor Sets: Only 3 sets total, updated at different frequencies
* 
* GPU PERFORMANCE OPTIMIZATIONS:
* • Cache-Friendly Layout: Related data grouped together for optimal GPU cache usage
* • Storage Buffers: Large data sets use storage buffers for GPU-friendly access patterns
* • GPU-Driven Rendering: Indirect drawing and GPU culling reduce CPU-GPU sync
* • Compute Integration: Set 2 optimized for async compute workloads
* • Texture Array Bindless: Eliminates texture binding overhead and increases batch sizes
* 
* MEMORY LAYOUT:
* Set 0 (Global): Updated once per frame - immutable samplers, global textures, materials
* Set 1 (Draw):   Updated per draw call - transform buffers, indirect commands, culling
* Set 2 (Compute): Async compute resources - animation, particles, culling results
* Push Constants: Per-draw material ID, texture indices, transform (128 bytes)
* ════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════ */

/* ══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════
* POST-PROCESSING OPTIMIZED DESCRIPTOR SET LAYOUT DESIGN
* ═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════
* 
* Optimized for post-processing workloads with different performance characteristics than general rendering:
* 
* POST-PROCESSING SPECIFIC OPTIMIZATIONS:
* • Screen-Space Focus: All effects work on full-screen quads, no vertex data complexity
* • Sequential Processing: Effects are applied in sequence, optimized for GPU pipeline efficiency
* • Temporal Effects: Support for frame history and temporal accumulation
* • Compute Integration: Many effects benefit from compute shaders for parallelism
* • Memory Bandwidth Optimization: Careful grouping to minimize memory traffic
* 
* PERFORMANCE BENEFITS:
* • Zero CPU Overhead: Push descriptors for per-effect parameters
* • GPU Cache Optimized: Input/output textures grouped for optimal cache usage
* • Minimal State Changes: Shared descriptor sets across effect chains
* • Async Compute: Compute effects run parallel to subsequent graphics work
* • Memory Coalescing: Structured for optimal memory access patterns
* ════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════ */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Data Constants and Configuration                                                                                                                                      */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgEXTN TgCHAR_NC_CPC                        g_apszKN_GPU_EXT_Validation_Layers[];
TgEXTN TgRSIZE_C                            g_nuiKN_GPU_EXT_Validation_Layers;
TgEXTN TgCHAR_NC_CPC                        g_apszKN_GPU_EXT_Instance_Extensions[];
TgEXTN TgRSIZE_C                            g_nuiKN_GPU_EXT_Instance_Extensions;
TgEXTN TgCHAR_NC_CPC                        g_apszKN_GPU_EXT_Device_Extensions[];
TgEXTN TgRSIZE_C                            g_nuiKN_GPU_EXT_Device_Extensions;

TgEXTN VkSamplerCI_C                        g_asKN_GPU_VLKN_Default_Sampler_Create_Info[ETgKN_GPU_DEFAULT_SAMPLER_COUNT];
TgEXTN VkPipelineRasterizationStateCI_C     g_asKN_GPU_VLKN_Default_Rasterizer_CI[ETgKN_GPU_RASTERIZER_STATE_COUNT];
TgEXTN VkPipelineDepthStencilStateCI_C      g_asKN_GPU_VLKN_Default_Depth_Stencil_CI[ETgKN_GPU_DEPTH_STENCIL_STATE_COUNT];
TgEXTN VkPipelineColorBlendAttachmentState_C g_asKN_GPU_VLKN_Default_Blend_Attachment[ETgKN_GPU_BLEND_STATE_COUNT];
TgEXTN VkPipelineVertexInputStateCI_C       g_asKN_GPU_VLKN_Vertex_Input_State[ETgKN_GPU_INPUT_LAYOUT_COUNT];

TgEXTN VkAllocationCallbacks_CPC            g_psKN_GPU_VLKN_Allocator;




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Data                                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- GPU - Contexts ----------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgEXTN STg2_KN_GPU_VLKN_CXT_HOST            g_sKN_GPU_EXT_CXT_HOST;

TgEXTN STg2_KN_GPU_VLKN_CXT_DEVC            g_asKN_GPU_EXT_CXT_DEVC[KTgKN_GPU_MAX_DEVC_CONTEXT];
TgEXTN STg2_KN_GPU_VLKN_CXT_EXEC            g_asKN_GPU_EXT_CXT_EXEC[KTgKN_GPU_MAX_EXEC_CONTEXT];
TgEXTN STg2_KN_GPU_VLKN_CXT_SWAP            g_asKN_GPU_EXT_CXT_SWAP[KTgKN_GPU_MAX_SWAP_CONTEXT];

#if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)
TgEXTN STg2_KN_GPU_DBG_VLKN_CXT_EXEC        g_asKN_GPU_DBG_EXT_CXT_EXEC[KTgKN_GPU_MAX_EXEC_CONTEXT];
TgEXTN STg2_KN_GPU_DBG_VLKN_CXT_SWAP        g_asKN_GPU_DBG_EXT_CXT_SWAP[KTgKN_GPU_MAX_SWAP_CONTEXT];
/*# defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
#endif




/* =============================================================================================================================================================================== */
#endif 
