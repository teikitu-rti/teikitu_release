/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (DX12) Kernel - Constants [GPU].h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_DX12_KERNEL_CONSTANTS_GPU_H)
#define TGS_DX12_KERNEL_CONSTANTS_GPU_H
#pragma once


/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Constants (Made to match API constant values)                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgTYPE_ENUM(ETgKN_GPU_EXT_FORMAT,TgSINT_E32,

    ETgKN_GPU_EXT_FORMAT__START                                  = 0,
    ETgKN_GPU_EXT_FORMAT_UNKNOWN                                 = ETgKN_GPU_EXT_FORMAT__START,
    ETgKN_GPU_EXT_FORMAT_R32G32B32A32_TYPELESS                   = 1,
    ETgKN_GPU_EXT_FORMAT_R32G32B32A32_FLOAT                      = 2,
    ETgKN_GPU_EXT_FORMAT_R32G32B32A32_UINT                       = 3,
    ETgKN_GPU_EXT_FORMAT_R32G32B32A32_SINT                       = 4,
    ETgKN_GPU_EXT_FORMAT_R32G32B32_TYPELESS                      = 5,
    ETgKN_GPU_EXT_FORMAT_R32G32B32_FLOAT                         = 6,
    ETgKN_GPU_EXT_FORMAT_R32G32B32_UINT                          = 7,
    ETgKN_GPU_EXT_FORMAT_R32G32B32_SINT                          = 8,
    ETgKN_GPU_EXT_FORMAT_R16G16B16A16_TYPELESS                   = 9,
    ETgKN_GPU_EXT_FORMAT_R16G16B16A16_FLOAT                      = 10,
    ETgKN_GPU_EXT_FORMAT_R16G16B16A16_UNORM                      = 11,
    ETgKN_GPU_EXT_FORMAT_R16G16B16A16_UINT                       = 12,
    ETgKN_GPU_EXT_FORMAT_R16G16B16A16_SNORM                      = 13,
    ETgKN_GPU_EXT_FORMAT_R16G16B16A16_SINT                       = 14,
    ETgKN_GPU_EXT_FORMAT_R32G32_TYPELESS                         = 15,
    ETgKN_GPU_EXT_FORMAT_R32G32_FLOAT                            = 16,
    ETgKN_GPU_EXT_FORMAT_R32G32_UINT                             = 17,
    ETgKN_GPU_EXT_FORMAT_R32G32_SINT                             = 18,
    ETgKN_GPU_EXT_FORMAT_R32G8X24_TYPELESS                       = 19,
    ETgKN_GPU_EXT_FORMAT_D32_FLOAT_S8X24_UINT                    = 20,
    ETgKN_GPU_EXT_FORMAT_R32_FLOAT_X8X24_TYPELESS                = 21,
    ETgKN_GPU_EXT_FORMAT_X32_TYPELESS_G8X24_UINT                 = 22,
    ETgKN_GPU_EXT_FORMAT_R10G10B10A2_TYPELESS                    = 23,
    ETgKN_GPU_EXT_FORMAT_R10G10B10A2_UNORM                       = 24,
    ETgKN_GPU_EXT_FORMAT_R10G10B10A2_UINT                        = 25,
    ETgKN_GPU_EXT_FORMAT_R11G11B10_FLOAT                         = 26,
    ETgKN_GPU_EXT_FORMAT_R8G8B8A8_TYPELESS                       = 27,
    ETgKN_GPU_EXT_FORMAT_R8G8B8A8_UNORM                          = 28,
    ETgKN_GPU_EXT_FORMAT_R8G8B8A8_UNORM_SRGB                     = 29,
    ETgKN_GPU_EXT_FORMAT_R8G8B8A8_UINT                           = 30,
    ETgKN_GPU_EXT_FORMAT_R8G8B8A8_SNORM                          = 31,
    ETgKN_GPU_EXT_FORMAT_R8G8B8A8_SINT                           = 32,
    ETgKN_GPU_EXT_FORMAT_R16G16_TYPELESS                         = 33,
    ETgKN_GPU_EXT_FORMAT_R16G16_FLOAT                            = 34,
    ETgKN_GPU_EXT_FORMAT_R16G16_UNORM                            = 35,
    ETgKN_GPU_EXT_FORMAT_R16G16_UINT                             = 36,
    ETgKN_GPU_EXT_FORMAT_R16G16_SNORM                            = 37,
    ETgKN_GPU_EXT_FORMAT_R16G16_SINT                             = 38,
    ETgKN_GPU_EXT_FORMAT_R32_TYPELESS                            = 39,
    ETgKN_GPU_EXT_FORMAT_D32_FLOAT                               = 40,
    ETgKN_GPU_EXT_FORMAT_R32_FLOAT                               = 41,
    ETgKN_GPU_EXT_FORMAT_R32_UINT                                = 42,
    ETgKN_GPU_EXT_FORMAT_R32_SINT                                = 43,
    ETgKN_GPU_EXT_FORMAT_R24G8_TYPELESS                          = 44,
    ETgKN_GPU_EXT_FORMAT_D24_UNORM_S8_UINT                       = 45,
    ETgKN_GPU_EXT_FORMAT_R24_UNORM_X8_TYPELESS                   = 46,
    ETgKN_GPU_EXT_FORMAT_X24_TYPELESS_G8_UINT                    = 47,
    ETgKN_GPU_EXT_FORMAT_R8G8_TYPELESS                           = 48,
    ETgKN_GPU_EXT_FORMAT_R8G8_UNORM                              = 49,
    ETgKN_GPU_EXT_FORMAT_R8G8_UINT                               = 50,
    ETgKN_GPU_EXT_FORMAT_R8G8_SNORM                              = 51,
    ETgKN_GPU_EXT_FORMAT_R8G8_SINT                               = 52,
    ETgKN_GPU_EXT_FORMAT_R16_TYPELESS                            = 53,
    ETgKN_GPU_EXT_FORMAT_R16_FLOAT                               = 54,
    ETgKN_GPU_EXT_FORMAT_D16_UNORM                               = 55,
    ETgKN_GPU_EXT_FORMAT_R16_UNORM                               = 56,
    ETgKN_GPU_EXT_FORMAT_R16_UINT                                = 57,
    ETgKN_GPU_EXT_FORMAT_R16_SNORM                               = 58,
    ETgKN_GPU_EXT_FORMAT_R16_SINT                                = 59,
    ETgKN_GPU_EXT_FORMAT_R8_TYPELESS                             = 60,
    ETgKN_GPU_EXT_FORMAT_R8_UNORM                                = 61,
    ETgKN_GPU_EXT_FORMAT_R8_UINT                                 = 62,
    ETgKN_GPU_EXT_FORMAT_R8_SNORM                                = 63,
    ETgKN_GPU_EXT_FORMAT_R8_SINT                                 = 64,
    ETgKN_GPU_EXT_FORMAT_A8_UNORM                                = 65,
    ETgKN_GPU_EXT_FORMAT_R1_UNORM                                = 66,
    ETgKN_GPU_EXT_FORMAT_R9G9B9E5_SHAREDEXP                      = 67,
    ETgKN_GPU_EXT_FORMAT_R8G8_B8G8_UNORM                         = 68,
    ETgKN_GPU_EXT_FORMAT_G8R8_G8B8_UNORM                         = 69,
    ETgKN_GPU_EXT_FORMAT_BC1_TYPELESS                            = 70,
    ETgKN_GPU_EXT_FORMAT_BC1_UNORM                               = 71,
    ETgKN_GPU_EXT_FORMAT_BC1_UNORM_SRGB                          = 72,
    ETgKN_GPU_EXT_FORMAT_BC2_TYPELESS                            = 73,
    ETgKN_GPU_EXT_FORMAT_BC2_UNORM                               = 74,
    ETgKN_GPU_EXT_FORMAT_BC2_UNORM_SRGB                          = 75,
    ETgKN_GPU_EXT_FORMAT_BC3_TYPELESS                            = 76,
    ETgKN_GPU_EXT_FORMAT_BC3_UNORM                               = 77,
    ETgKN_GPU_EXT_FORMAT_BC3_UNORM_SRGB                          = 78,
    ETgKN_GPU_EXT_FORMAT_BC4_TYPELESS                            = 79,
    ETgKN_GPU_EXT_FORMAT_BC4_UNORM                               = 80,
    ETgKN_GPU_EXT_FORMAT_BC4_SNORM                               = 81,
    ETgKN_GPU_EXT_FORMAT_BC5_TYPELESS                            = 82,
    ETgKN_GPU_EXT_FORMAT_BC5_UNORM                               = 83,
    ETgKN_GPU_EXT_FORMAT_BC5_SNORM                               = 84,
    ETgKN_GPU_EXT_FORMAT_B5G6R5_UNORM                            = 85,
    ETgKN_GPU_EXT_FORMAT_B5G5R5A1_UNORM                          = 86,
    ETgKN_GPU_EXT_FORMAT_B8G8R8A8_UNORM                          = 87,
    ETgKN_GPU_EXT_FORMAT_B8G8R8X8_UNORM                          = 88,
    ETgKN_GPU_EXT_FORMAT_R10G10B10_XR_BIAS_A2_UNORM              = 89,
    ETgKN_GPU_EXT_FORMAT_B8G8R8A8_TYPELESS                       = 90,
    ETgKN_GPU_EXT_FORMAT_B8G8R8A8_UNORM_SRGB                     = 91,
    ETgKN_GPU_EXT_FORMAT_B8G8R8X8_TYPELESS                       = 92,
    ETgKN_GPU_EXT_FORMAT_B8G8R8X8_UNORM_SRGB                     = 93,
    ETgKN_GPU_EXT_FORMAT_BC6H_TYPELESS                           = 94,
    ETgKN_GPU_EXT_FORMAT_BC6H_UF16                               = 95,
    ETgKN_GPU_EXT_FORMAT_BC6H_SF16                               = 96,
    ETgKN_GPU_EXT_FORMAT_BC7_TYPELESS                            = 97,
    ETgKN_GPU_EXT_FORMAT_BC7_UNORM                               = 98,
    ETgKN_GPU_EXT_FORMAT_BC7_UNORM_SRGB                          = 99,
    ETgKN_GPU_EXT_FORMAT_AYUV                                    = 100,
    ETgKN_GPU_EXT_FORMAT_Y410                                    = 101,
    ETgKN_GPU_EXT_FORMAT_Y416                                    = 102,
    ETgKN_GPU_EXT_FORMAT_NV12                                    = 103,
    ETgKN_GPU_EXT_FORMAT_P010                                    = 104,
    ETgKN_GPU_EXT_FORMAT_P016                                    = 105,
    ETgKN_GPU_EXT_FORMAT_420_OPAQUE                              = 106,
    ETgKN_GPU_EXT_FORMAT_YUY2                                    = 107,
    ETgKN_GPU_EXT_FORMAT_Y210                                    = 108,
    ETgKN_GPU_EXT_FORMAT_Y216                                    = 109,
    ETgKN_GPU_EXT_FORMAT_NV11                                    = 110,
    ETgKN_GPU_EXT_FORMAT_AI44                                    = 111,
    ETgKN_GPU_EXT_FORMAT_IA44                                    = 112,
    ETgKN_GPU_EXT_FORMAT_P8                                      = 113,
    ETgKN_GPU_EXT_FORMAT_A8P8                                    = 114,
    ETgKN_GPU_EXT_FORMAT_B4G4R4A4_UNORM                          = 115,

    ETgKN_GPU_EXT_FORMAT_P208                                    = 130,
    ETgKN_GPU_EXT_FORMAT_V208                                    = 131,
    ETgKN_GPU_EXT_FORMAT_V408                                    = 132,

    ETgKN_GPU_EXT_FORMAT_SAMPLER_FEEDBACK_MIN_MIP_OPAQUE         = 189,
    ETgKN_GPU_EXT_FORMAT_SAMPLER_FEEDBACK_MIP_REGION_USED_OPAQUE = 190,

    /* Index Values */
    ETgKN_GPU_EXT_FORMAT__END,
    ETgKN_GPU_EXT_FORMAT__MAX                                    = ETgKN_GPU_EXT_FORMAT__END,
    ETgKN_GPU_EXT_FORMAT__COUNT                                  = ETgKN_GPU_EXT_FORMAT__END - ETgKN_GPU_EXT_FORMAT__START,
);

TgTYPE_ENUM_FLAG( ETgKN_GPU_EXT_TOPOLOGY_TYPE, TgSINT_E32,

    ETgKN_GPU_EXT_TOPOLOGY_TYPE_START = 0,

    ETgKN_GPU_EXT_TOPOLOGY_TYPE_UNDEFINED                        = ETgKN_GPU_EXT_TOPOLOGY_TYPE_START,
    ETgKN_GPU_EXT_TOPOLOGY_TYPE_POINT                            = 1,
    ETgKN_GPU_EXT_TOPOLOGY_TYPE_LINE                             = 2,
    ETgKN_GPU_EXT_TOPOLOGY_TYPE_TRIANGLE                         = 3,
    ETgKN_GPU_EXT_TOPOLOGY_TYPE_PATCH                            = 4,

    ETgKN_GPU_EXT_TOPOLOGY_TYPE_END,
    ETgKN_GPU_EXT_TOPOLOGY_TYPE_MAX                              = ETgKN_GPU_EXT_TOPOLOGY_TYPE_END,
    ETgKN_GPU_EXT_TOPOLOGY_TYPE_COUNT                            = ETgKN_GPU_EXT_TOPOLOGY_TYPE_END - ETgKN_GPU_EXT_TOPOLOGY_TYPE_START,
);

//TgTYPE_ENUM( ETgKN_GPU_TOPOLOGY, TgSINT_E32,
//
//    ETgKN_GPU_TOPOLOGY__START,
//
//    ETgKN_GPU_TOPOLOGY_UNDEFINED = ETgKN_GPU_TOPOLOGY__START,
//    ETgKN_GPU_TOPOLOGY_POINTLIST,
//    ETgKN_GPU_TOPOLOGY_LINELIST,
//    ETgKN_GPU_TOPOLOGY_LINESTRIP,
//    ETgKN_GPU_TOPOLOGY_TRIANGLELIST,
//    ETgKN_GPU_TOPOLOGY_TRIANGLESTRIP,
//
//    ETgKN_GPU_TOPOLOGY__END,
//    ETgKN_GPU_TOPOLOGY__MAX = ETgKN_GPU_TOPOLOGY__END,
//    ETgKN_GPU_TOPOLOGY__COUNT = ETgKN_GPU_TOPOLOGY__END - ETgKN_GPU_TOPOLOGY__START,
//);

TgTYPE_ENUM_FLAG(ETgKN_GPU_EXT_COMMAND, TgSINT_E32,

    ETgKN_GPU_EXT_COMMAND_NONE = -1,
    ETgKN_GPU_EXT_COMMAND_UNKNOWN = ETgKN_GPU_EXT_COMMAND_NONE,

    ETgKN_GPU_EXT_COMMAND_START = 0,

    ETgKN_GPU_EXT_COMMAND_DIRECT = ETgKN_GPU_EXT_COMMAND_START,
    ETgKN_GPU_EXT_COMMAND_BUNDLE,
    ETgKN_GPU_EXT_COMMAND_COMPUTE,
    ETgKN_GPU_EXT_COMMAND_COPY,
    ETgKN_GPU_EXT_COMMAND_VIDEO_DECODE,
    ETgKN_GPU_EXT_COMMAND_VIDEO_PROCESS,
    ETgKN_GPU_EXT_COMMAND_VIDEO_ENCODE,

    ETgKN_GPU_EXT_COMMAND_END,
    ETgKN_GPU_EXT_COMMAND_MAX = ETgKN_GPU_EXT_COMMAND_END,
    ETgKN_GPU_EXT_COMMAND_COUNT = ETgKN_GPU_EXT_COMMAND_END - ETgKN_GPU_EXT_COMMAND_START,
);


/* =============================================================================================================================================================================== */
#endif
