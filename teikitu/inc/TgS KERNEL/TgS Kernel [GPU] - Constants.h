/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Kernel - Constants [GPU].h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.20 | »GUID« DE461472-5528-4A5B-A7F4-09CCAD73387B */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_KERNEL_CONSTANTS_GPU_H) && defined(TgBUILD_FEATURE__GRAPHICS)
#define TGS_KERNEL_CONSTANTS_GPU_H
#pragma once

#include "TgS KERNEL/TgS Kernel [GPU] - Resource [HLSL] [Constants].h"
#include TgHEADER_GRAPHCIS(TgS KERNEL/TgS,Kernel [GPU] - Constants.h)


/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Configuration                                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

enum { KTgKN_GPU_MAX_HOST_CONTEXT                   =     1,    /**< Maximum number of Host/CPU resource contexts (one per host/cpu memory controller). */
       KTgKN_GPU_MAX_DEVC_CONTEXT                   =     4,    /**< Maximum number of GPU devices allowed. */
       KTgKN_GPU_MAX_EXEC_CONTEXT                   =     4,    /**< Maximum number of GPU execute contexts allowed (one per node). */
       KTgKN_GPU_MAX_SWAP_CONTEXT                   =     9,    /**< Maximum number of GPU output (scan-out) devices. */

       KTgKN_GPU_MAX_ADAPTER                        =     8,    /**< Maximum number of GPU adapters that can be enumerated. */
       KTgKN_GPU_MAX_ADAPTER_NODE                   =     2,    /**< Maximum number of GPU nodes per adapter that can be enumerated. */
       KTgKN_GPU_MAX_ADAPTER_NAME                   =   128,    /**< Maximum length of adapter name | description. */
       KTgKN_GPU_MAX_OUTPUT                         =    64,    /**< Maximum number of GPU output (scan-out) devices per adapter than can be enumerated. */
       KTgKN_GPU_MAX_OUTPUT_NAME                    =    32,    /**< Maximum name stored for each output device. */

       KTgKN_GPU_MAX_BUFFER_IN_FLIP_CHAIN           =     3,    /**< Maximum latency of the system. For embedded devices this should match the exact desired configuration */
       KTgKN_GPU_MAX_EXEC_CONTEXT_COMMAND           =     3,

       KTgKN_GPU_MAX__SIMULTANEOUS_TARGET_COUNT     =     8,

       KTgKN_GPU_MAX_VS                             =    32,    /**< Maximum number of vertex shaders. */
       KTgKN_GPU_MAX_DS                             =    32,    /**< Maximum number of domain shaders. */
       KTgKN_GPU_MAX_GS                             =    32,    /**< Maximum number of geometry shaders. */
       KTgKN_GPU_MAX_HS                             =    32,    /**< Maximum number of hull shaders. */
       KTgKN_GPU_MAX_PS                             =    64,    /**< Maximum number of pixel shaders. */
       KTgKN_GPU_MAX_CS                             =    64,    /**< Maximum number of compute shaders. */

       KTgKN_GPU_MAX_TX_CBE                         =    64,    /**< Maximum number of cube textures. */
       KTgKN_GPU_MAX_TX_IMG                         =  4096,    /**< Maximum number of 2D textures. */
       KTgKN_GPU_MAX_TX_VOL                         =    64,    /**< Maximum number of volume textures. */

       KTgKN_GPU_MAX_TX_CBE_INST                    = KTgKN_GPU_MAX_TX_CBE,
       KTgKN_GPU_MAX_TX_IMG_INST                    = KTgKN_GPU_MAX_TX_IMG,
       KTgKN_GPU_MAX_TX_VOL_INST                    = KTgKN_GPU_MAX_TX_VOL,

       KTgKN_GPU_MAX_RELEASE_RESOURCE               =    64,

#if TgCOMPILE__RENDER_DEBUG_OUTPUT
       KTgKN_GPU_MAX_DEBUG_TEXT_LINE_LENGTH        = KTgMACRO_KN_GPU_HLSL_DEBUG_MAX_TEXT_GLYPH,
       KTgKN_GPU_MAX_DEBUG_LINE_VERTEX_COUNT       =   1024,
       KTgKN_GPU_MAX_DEBUG_TEXT                    = TgCOMPILE__CONSOLE ? 64 : KTgCN_OSLOG_MAX_LINE + 32,
       KTgKN_GPU_MAX_DEBUG_UI                      =     32,
       KTgKN_GPU_MAX_DEBUG_LINE                    =     32,
       KTgKN_GPU_MAX_DEBUG_GEOM                    =    128,
/*# TgCOMPILE__RENDER_DEBUG_OUTPUT */
#endif

       KTgKN_GPU_MS__MAX                            =    32,

       KTgKN_GPU_SRV_TX_CBE                         =     0,
       KTgKN_GPU_SRV_TX_VOL                         =     1,
       KTgKN_GPU_SRV_TX_IMG                         =     2,
       KTgKN_GPU_SRV_TYPE_COUNT                     =     3,

       KTgKN_GPU_RS_BIT__MAX_INDEX                  =    22,
       KTgKN_GPU_RS_BIT__SALT                       =    24,
       KTgKN_GPU_RS_BIT__LOAD                       =     1,
       KTgKN_GPU_RS_BIT__FREE                       =     1,
       KTgKN_GPU_RS_BIT__REFERENCE_COUNT            =    16,

       KTgKN_GPU_RSI_BIT__MAX_INDEX                 =    22,
       KTgKN_GPU_RSI_BIT__MAX_CONTEXT               =     2,
       KTgKN_GPU_RSI_BIT__SALT                      =    22,
       KTgKN_GPU_RSI_BIT__LOAD                      =     1,
       KTgKN_GPU_RSI_BIT__FREE                      =     1,
       KTgKN_GPU_RSI_BIT__REFERENCE_COUNT           =    16,
};

/* Maximum number of contexts is 2 bits == 4 */
TgCOMPILER_ASSERT( KTgKN_GPU_MAX_EXEC_CONTEXT <= (1 << KTgKN_GPU_RSI_BIT__MAX_CONTEXT), 0 );

/* Maximum number of instances per library is 22 bits == 4,194,303 */
/* Maximum number of references per resource is 18 bits == 262,143 */


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Constants                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* List of memory locations and cache status */
TgTYPE_ENUM(ETgKN_GPU_ALLOCATOR,TgSINT_F32,

    ETgKN_GPU_ALLOCATOR__VIDEO_MEMORY = (0 << 7) + (0 << 0),
    ETgKN_GPU_ALLOCATOR__VIDEO_MEMORY_WRITEONLY = (0 << 7) + (1 << 0), /**< Standard GPU resource, supports CPU-wo and GPU-rm (worm) */
    ETgKN_GPU_ALLOCATOR__VIDEO_MEMORY_DYNAMIC = (0 << 7) + (2 << 0), /**< Per frame CPU write and GPU read */
    ETgKN_GPU_ALLOCATOR__VIDEO_MEMORY_STAGING = (0 << 7) + (3 << 0), /**< Supports transfer from GPU to CPU */
    ETgKN_GPU_ALLOCATOR__VIDEO_MEMORY_INPLACE = (0 << 7) + (4 << 0), /**< Function should do fixup only (load inplace) */

    ETgKN_GPU_ALLOCATOR__MAIN_MEMORY = (1 << 8) + (0 << 0),
    ETgKN_GPU_ALLOCATOR__MAIN_MEMORY_WRITEONLY = (1 << 8) + (1 << 0),
    ETgKN_GPU_ALLOCATOR__MAIN_MEMORY_DYNAMIC = (1 << 8) + (2 << 0),
    ETgKN_GPU_ALLOCATOR__MAIN_MEMORY_STAGING = (1 << 8) + (3 << 0),
    ETgKN_GPU_ALLOCATOR__MAIN_MEMORY_INPLACE = (0 << 8) + (4 << 0), /**< Function should do fixup only (load inplace) */

    ETgKN_GPU_ALLOCATOR__IGNORE_REF_COUNT = (1 << 9),

    ETgKN_GPU_ALLOCATOR__INVALID = (1 << 10),
);


/* ---- GPU - Resource - Constants ----------------------------------------------------------------------------------------------------------------------------------------------- */

static const ETgKN_GPU_EXT_FORMAT KTgKN_GPU_EXT_FORMAT_RT_SCANOUT[] =  {
    ETgKN_GPU_EXT_FORMAT_R16G16B16A16_FLOAT,
    ETgKN_GPU_EXT_FORMAT_R10G10B10A2_UNORM,
    ETgKN_GPU_EXT_FORMAT_R8G8B8A8_UNORM,
    ETgKN_GPU_EXT_FORMAT_R8G8B8A8_UNORM_SRGB,
    ETgKN_GPU_EXT_FORMAT_B8G8R8A8_UNORM,
    ETgKN_GPU_EXT_FORMAT_B8G8R8A8_UNORM_SRGB,
};
enum { KTgKN_GPU_EXT_FORMAT_RT_SCANOUT_MAX = TgARRAY_COUNT(KTgKN_GPU_EXT_FORMAT_RT_SCANOUT) };

static const ETgKN_GPU_EXT_FORMAT KTgKN_GPU_EXT_FORMAT_DS_SCANOUT[] =  {
    ETgKN_GPU_EXT_FORMAT_D32_FLOAT_S8X24_UINT,
    ETgKN_GPU_EXT_FORMAT_D32_FLOAT,
    ETgKN_GPU_EXT_FORMAT_D24_UNORM_S8_UINT,
};
enum { KTgKN_GPU_EXT_FORMAT_DS_SCANOUT_MAX = TgARRAY_COUNT(KTgKN_GPU_EXT_FORMAT_DS_SCANOUT) };

TgTYPE_ENUM_FLAG(ETgKN_GPU_MS, TgSINT_F32,

    ETgKN_GPU_MS__00,               ETgKN_GPU_MS__02,               ETgKN_GPU_MS__03,               ETgKN_GPU_MS__04,               ETgKN_GPU_MS__05,
    ETgKN_GPU_MS__06,               ETgKN_GPU_MS__07,               ETgKN_GPU_MS__08,               ETgKN_GPU_MS__09,               ETgKN_GPU_MS__10,
    ETgKN_GPU_MS__11,               ETgKN_GPU_MS__12,               ETgKN_GPU_MS__13,               ETgKN_GPU_MS__14,               ETgKN_GPU_MS__15,
    ETgKN_GPU_MS__16,
);

TgTYPE_ENUM_FLAG(ETgKN_GPU_DOS_FONT_ROM, TgSINT_F32,
    ETgKN_GPU_DOS_FONT_ROM_START = 0,

    ETgKN_GPU_DOS_FONT_ROM_DEFAULT = ETgKN_GPU_DOS_FONT_ROM_START,
    ETgKN_GPU_DOS_FONT_ROM_FUTURE,
    ETgKN_GPU_DOS_FONT_ROM_BLOCK,
    ETgKN_GPU_DOS_FONT_ROM_MARCIO,

    ETgKN_GPU_DOS_FONT_ROM_END,
    ETgKN_GPU_DOS_FONT_ROM_MAX = ETgKN_GPU_DOS_FONT_ROM_END,
    ETgKN_GPU_DOS_FONT_ROM_COUNT = ETgKN_GPU_DOS_FONT_ROM_END - ETgKN_GPU_DOS_FONT_ROM_START,
);

TgTYPE_ENUM_FLAG(ETgKN_GPU_DEBUG_PM, TgSINT_E32,
    ETgKN_GPU_DEBUG_PM_START = 0,

    ETgKN_GPU_DEBUG_PM_UNKNOWN = ETgKN_GPU_DEBUG_PM_START,

    ETgKN_GPU_DEBUG_PM_LN_START,
    ETgKN_GPU_DEBUG_PM_LN_LINE = ETgKN_GPU_DEBUG_PM_LN_START,
    ETgKN_GPU_DEBUG_PM_LN_AXES,
    ETgKN_GPU_DEBUG_PM_LN_FRUSTUM,
    ETgKN_GPU_DEBUG_PM_LN_PARABOLA,
    ETgKN_GPU_DEBUG_PM_LN_TETRAHEDRON,
    ETgKN_GPU_DEBUG_PM_LN_END,

    ETgKN_GPU_DEBUG_PM_2D_START = ETgKN_GPU_DEBUG_PM_LN_END,
    ETgKN_GPU_DEBUG_PM_2D_NGON = ETgKN_GPU_DEBUG_PM_2D_START,
    ETgKN_GPU_DEBUG_PM_2D_END,

    ETgKN_GPU_DEBUG_PM_3D_START = ETgKN_GPU_DEBUG_PM_2D_END,
    ETgKN_GPU_DEBUG_PM_3D_PLANE = ETgKN_GPU_DEBUG_PM_3D_START,
    ETgKN_GPU_DEBUG_PM_3D_BOX,
    ETgKN_GPU_DEBUG_PM_3D_SPHERE,
    ETgKN_GPU_DEBUG_PM_3D_CAPSULE,
    ETgKN_GPU_DEBUG_PM_3D_CONE,
    ETgKN_GPU_DEBUG_PM_3D_CYLINDER,
    ETgKN_GPU_DEBUG_PM_3D_TUBE,
    ETgKN_GPU_DEBUG_PM_3D_END,

    ETgKN_GPU_DEBUG_PM_END = ETgKN_GPU_DEBUG_PM_3D_END,
    ETgKN_GPU_DEBUG_PM_MAX = ETgKN_GPU_DEBUG_PM_END,
    ETgKN_GPU_DEBUG_PM_COUNT = ETgKN_GPU_DEBUG_PM_END - ETgKN_GPU_DEBUG_PM_START,
    ETgKN_GPU_DEBUG_PM_LN_COUNT = ETgKN_GPU_DEBUG_PM_LN_END - ETgKN_GPU_DEBUG_PM_LN_START,
    ETgKN_GPU_DEBUG_PM_2D_COUNT = ETgKN_GPU_DEBUG_PM_2D_END - ETgKN_GPU_DEBUG_PM_2D_START,
    ETgKN_GPU_DEBUG_PM_3D_COUNT = ETgKN_GPU_DEBUG_PM_3D_END - ETgKN_GPU_DEBUG_PM_3D_START,
);


/* ---- GPU - Resource - Defaults ------------------------------------------------------------------------------------------------------------------------------------------------ */

TgTYPE_ENUM_FLAG(ETgKN_GPU_DEFAULT_BLEND_STATE, TgSINT_F32,
    ETgKN_GPU_DEFAULT_BLEND_STATE_START = 0,

    ETgKN_GPU_DEFAULT_BLEND_STATE_NONE = ETgKN_GPU_DEFAULT_BLEND_STATE_START,
    ETgKN_GPU_DEFAULT_BLEND_STATE_ALPHA,
    ETgKN_GPU_DEFAULT_BLEND_STATE_ALPHA_PREMULT,

    ETgKN_GPU_DEFAULT_BLEND_STATE_END,
    ETgKN_GPU_DEFAULT_BLEND_STATE_MAX = ETgKN_GPU_DEFAULT_BLEND_STATE_END,
    ETgKN_GPU_DEFAULT_BLEND_STATE_COUNT = ETgKN_GPU_DEFAULT_BLEND_STATE_END - ETgKN_GPU_DEFAULT_BLEND_STATE_START,

);

TgTYPE_ENUM_FLAG(ETgKN_GPU_DEFAULT_RASTERIZER_STATE, TgSINT_F32,
    ETgKN_GPU_DEFAULT_RASTERIZER_STATE_START = 0,

    ETgKN_GPU_DEFAULT_RASTERIZER_STATE_DEFAULT_SOLID = ETgKN_GPU_DEFAULT_RASTERIZER_STATE_START,
    ETgKN_GPU_DEFAULT_RASTERIZER_STATE_DEFAULT_SOLID_LINE_AA,
    ETgKN_GPU_DEFAULT_RASTERIZER_STATE_DEFAULT_WIREFRAME,

    ETgKN_GPU_DEFAULT_RASTERIZER_STATE_END,
    ETgKN_GPU_DEFAULT_RASTERIZER_STATE_MAX = ETgKN_GPU_DEFAULT_RASTERIZER_STATE_END,
    ETgKN_GPU_DEFAULT_RASTERIZER_STATE_COUNT = ETgKN_GPU_DEFAULT_RASTERIZER_STATE_END - ETgKN_GPU_DEFAULT_RASTERIZER_STATE_START,

);

TgTYPE_ENUM_FLAG(ETgKN_GPU_DEFAULT_DEPTH_STENCIL_STATE, TgSINT_F32,
    ETgKN_GPU_DEFAULT_DEPTH_STENCIL_STATE_START = 0,

    ETgKN_GPU_DEFAULT_DEPTH_STENCIL_STATE_TEST_NONE = ETgKN_GPU_DEFAULT_DEPTH_STENCIL_STATE_START,
    ETgKN_GPU_DEFAULT_DEPTH_STENCIL_STATE_TEST_DEPTH,
    ETgKN_GPU_DEFAULT_DEPTH_STENCIL_STATE_TEST_DEPTH_STENCIL,
    ETgKN_GPU_DEFAULT_DEPTH_STENCIL_STATE_TEST_DEPTH_TRANSPARENT,

    ETgKN_GPU_DEFAULT_DEPTH_STENCIL_STATE_END,
    ETgKN_GPU_DEFAULT_DEPTH_STENCIL_STATE_MAX = ETgKN_GPU_DEFAULT_DEPTH_STENCIL_STATE_END,
    ETgKN_GPU_DEFAULT_DEPTH_STENCIL_STATE_COUNT = ETgKN_GPU_DEFAULT_DEPTH_STENCIL_STATE_END - ETgKN_GPU_DEFAULT_DEPTH_STENCIL_STATE_START,
);

typedef enum CLANG_ATTRIBUTE(enum_extensibility(closed),flag_enum) {
    ETgKN_GPU_DEFAULT_INPUT_LAYOUT_START = 0,

    #define RENDER_INPUT_LAYOUT_PER_VERTEX(A, B, C, D, E, F, G, ...)
    #define RENDER_INPUT_LAYOUT_PER_VERTEX_APPEND(A, B, C, D, F, G, ...)
    #define RENDER_INPUT_LAYOUT_END(A)
    #define RENDER_INPUT_ALIGNMENT_CHECK(A,B)

    #define RENDER_INPUT_LAYOUT_START_FIRST(A,B) ETgKN_GPU_DEFAULT_INPUT_LAYOUT_##B = ETgKN_GPU_DEFAULT_INPUT_LAYOUT_START,
    #define RENDER_INPUT_LAYOUT_START(A,B) ETgKN_GPU_DEFAULT_INPUT_LAYOUT_##B,
    #include "TgS KERNEL/TgS Kernel [GPU] - Resource [HLSL] [Vertex].h"
    #undef RENDER_INPUT_LAYOUT_START
    #undef RENDER_INPUT_LAYOUT_START_FIRST

    #define RENDER_INPUT_LAYOUT_START(A,B) ETgKN_GPU_DEFAULT_INPUT_LAYOUT_INSTANCE_##B,
    #include "TgS KERNEL/TgS Kernel [GPU] - Resource [HLSL] [Vertex].h"
    #undef RENDER_INPUT_LAYOUT_START

    #undef RENDER_INPUT_ALIGNMENT_CHECK
    #undef RENDER_INPUT_LAYOUT_END
    #undef RENDER_INPUT_LAYOUT_PER_VERTEX_APPEND
    #undef RENDER_INPUT_LAYOUT_PER_VERTEX

    ETgKN_GPU_DEFAULT_INPUT_LAYOUT_END,
    ETgKN_GPU_DEFAULT_INPUT_LAYOUT_MAX = ETgKN_GPU_DEFAULT_INPUT_LAYOUT_END,
    ETgKN_GPU_DEFAULT_INPUT_LAYOUT_COUNT = ETgKN_GPU_DEFAULT_INPUT_LAYOUT_END - ETgKN_GPU_DEFAULT_INPUT_LAYOUT_START,

} ETgKN_GPU_DEFAULT_INPUT_LAYOUT;
TgTYPE_DECLARE( ETgKN_GPU_DEFAULT_INPUT_LAYOUT, ETgKN_GPU_DEFAULT_INPUT_LAYOUT );

TgTYPE_ENUM_FLAG(ETgKN_GPU_DEFAULT_PSO, TgSINT_F32,
    ETgKN_GPU_DEFAULT_PSO_START = 0,

    ETgKN_GPU_DEFAULT_PSO_PARTICLE_00 = ETgKN_GPU_DEFAULT_PSO_START,
    ETgKN_GPU_DEFAULT_PSO_PARTICLE_01,

    //ETgKN_GPU_DEFAULT_PSO_MESH_00,
    //ETgKN_GPU_DEFAULT_PSO_MESH_01,
    //ETgKN_GPU_DEFAULT_PSO_MESH_02,

    /* 2D (Screen) Default Debug PSO */
    ETgKN_GPU_DEFAULT_PSO_DEBUG_UI,
    ETgKN_GPU_DEFAULT_PSO_DEBUG_UI_WITH_GAMMA,
    ETgKN_GPU_DEFAULT_PSO_DEBUG_TEXT,

    /* 3D Default Debug PSO */
    ETgKN_GPU_DEFAULT_PSO_DEBUG_LINE,
    ETgKN_GPU_DEFAULT_PSO_DEBUG_GEOM_00,
    ETgKN_GPU_DEFAULT_PSO_DEBUG_GEOM_01,
    ETgKN_GPU_DEFAULT_PSO_DEBUG_GEOM_01_WITH_GAMMA,
    ETgKN_GPU_DEFAULT_PSO_DEBUG_GEOM_02,
    ETgKN_GPU_DEFAULT_PSO_DEBUG_GEOM_02_INSTANCE,
    ETgKN_GPU_DEFAULT_PSO_DEBUG_GEOM_03,

    /* Unit Test */
    ETgKN_GPU_DEFAULT_PSO_UNIT_TEST_SCENE,

    /* 3D Default Render Pass Test */

    ETgKN_GPU_DEFAULT_PSO_END,
    ETgKN_GPU_DEFAULT_PSO_MAX = ETgKN_GPU_DEFAULT_PSO_END,
    ETgKN_GPU_DEFAULT_PSO_COUNT = ETgKN_GPU_DEFAULT_PSO_END - ETgKN_GPU_DEFAULT_PSO_START,

);

TgTYPE_ENUM_FLAG(ETgKN_GPU_DEFAULT_ROOT_SIGNATURE, TgSINT_E32,
    ETgKN_GPU_DEFAULT_ROOT_SIGNATURE_START = 0,

    ETgKN_GPU_DEFAULT_ROOT_SIGNATURE_DEBUG = ETgKN_GPU_DEFAULT_ROOT_SIGNATURE_START,
    ETgKN_GPU_DEFAULT_ROOT_SIGNATURE_UNIT_TEST,

    ETgKN_GPU_DEFAULT_ROOT_SIGNATURE_END,
    ETgKN_GPU_DEFAULT_ROOT_SIGNATURE_MAX = ETgKN_GPU_DEFAULT_ROOT_SIGNATURE_END,
    ETgKN_GPU_DEFAULT_ROOT_SIGNATURE_COUNT = ETgKN_GPU_DEFAULT_ROOT_SIGNATURE_END - ETgKN_GPU_DEFAULT_ROOT_SIGNATURE_START,
);


#include "TgS KERNEL/TgS Kernel [GPU] - Resource [HLSL] [Constants].h"

TgTYPE_ENUM_FLAG(ETgKN_GPU_HLSL_COLOR_SPACE, TgSINT_E32,
    ETgKN_GPU_HLSL_COLOR_SPACE_START = KTgMACRO_KN_GPU_HLSL_COLOR_SPACE_G22_NONE_P709,

    ETgKN_GPU_HLSL_COLOR_SPACE_UNKNOWN = - 1,
    ETgKN_GPU_HLSL_COLOR_SPACE_G22_NONE_P709 = KTgMACRO_KN_GPU_HLSL_COLOR_SPACE_G22_NONE_P709,
    ETgKN_GPU_HLSL_COLOR_SPACE_G2084_NONE_P2020 = KTgMACRO_KN_GPU_HLSL_COLOR_SPACE_G2084_NONE_P2020,
    ETgKN_GPU_HLSL_COLOR_SPACE_G10_NONE_P709 = KTgMACRO_KN_GPU_HLSL_COLOR_SPACE_G10_NONE_P709,

    ETgKN_GPU_HLSL_COLOR_SPACE_END,
    ETgKN_GPU_HLSL_COLOR_SPACE_MAX = ETgKN_GPU_HLSL_COLOR_SPACE_END,
    ETgKN_GPU_HLSL_COLOR_SPACE_COUNT = ETgKN_GPU_HLSL_COLOR_SPACE_END - ETgKN_GPU_HLSL_COLOR_SPACE_START,
);


/* =============================================================================================================================================================================== */
#endif
