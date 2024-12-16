/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (VULKAN) Kernel - Constants [GPU].h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.22 | »GUID« 7ECEAB43-40E4-4161-8F94-87AF31F5BA9A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_EXT_KERNEL_CONSTANTS_GPU_H) && defined(TgBUILD_FEATURE__GRAPHICS)
#define TGS_EXT_KERNEL_CONSTANTS_GPU_H
#pragma once


/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Constants (Made to match API constant values)                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgTYPE_ENUM(ETgKN_GPU_EXT_FORMAT,TgSINT_F32,

    ETgKN_GPU_EXT_FORMAT__START                                  = 0,
    ETgKN_GPU_EXT_FORMAT_UNKNOWN                                 = ETgKN_GPU_EXT_FORMAT__START,

    ETgKN_GPU_EXT_FORMAT_R16G16B16A16_FLOAT,
    ETgKN_GPU_EXT_FORMAT_R10G10B10A2_UNORM,
    ETgKN_GPU_EXT_FORMAT_R8G8B8A8_UNORM,
    ETgKN_GPU_EXT_FORMAT_R8G8B8A8_UNORM_SRGB,
    ETgKN_GPU_EXT_FORMAT_B8G8R8A8_UNORM,
    ETgKN_GPU_EXT_FORMAT_B8G8R8A8_UNORM_SRGB,

    ETgKN_GPU_EXT_FORMAT_D32_FLOAT_S8X24_UINT,
    ETgKN_GPU_EXT_FORMAT_D32_FLOAT,
    ETgKN_GPU_EXT_FORMAT_D24_UNORM_S8_UINT,

    ETgKN_GPU_EXT_FORMAT_R8G8B8A8_UINT,
    ETgKN_GPU_EXT_FORMAT_R32G32B32A32_FLOAT,
    ETgKN_GPU_EXT_FORMAT_A8_UNORM,
    ETgKN_GPU_EXT_FORMAT_R8_UNORM,
    ETgKN_GPU_EXT_FORMAT_R16G16B16A16_UNORM,

    /* Index Values */
    ETgKN_GPU_EXT_FORMAT__END,
    ETgKN_GPU_EXT_FORMAT__MAX = ETgKN_GPU_EXT_FORMAT__END,
    ETgKN_GPU_EXT_FORMAT__COUNT = ETgKN_GPU_EXT_FORMAT__END - ETgKN_GPU_EXT_FORMAT__START,
);

TgTYPE_ENUM( ETgKN_GPU_EXT_TOPOLOGY_TYPE, TgSINT_F32,

    ETgKN_GPU_EXT_TOPOLOGY_TYPE_START = 0,

    ETgKN_GPU_EXT_TOPOLOGY_TYPE_UNDEFINED = ETgKN_GPU_EXT_TOPOLOGY_TYPE_START,
    ETgKN_GPU_EXT_TOPOLOGY_TYPE_POINT,
    ETgKN_GPU_EXT_TOPOLOGY_TYPE_LINE,
    ETgKN_GPU_EXT_TOPOLOGY_TYPE_TRIANGLE,
    ETgKN_GPU_EXT_TOPOLOGY_TYPE_PATCH,

    ETgKN_GPU_EXT_TOPOLOGY_TYPE_END,
    ETgKN_GPU_EXT_TOPOLOGY_TYPE_MAX = ETgKN_GPU_EXT_TOPOLOGY_TYPE_END,
    ETgKN_GPU_EXT_TOPOLOGY_TYPE_COUNT = ETgKN_GPU_EXT_TOPOLOGY_TYPE_END - ETgKN_GPU_EXT_TOPOLOGY_TYPE_START,
);

//TgTYPE_ENUM( ETgKN_GPU_TOPOLOGY, TgSINT_F32,
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

TgTYPE_ENUM_FLAG(ETgKN_GPU_EXT_COMMAND, TgSINT_F32,

    ETgKN_GPU_EXT_COMMAND_START = 0,

    ETgKN_GPU_EXT_COMMAND_GRAPHICS = ETgKN_GPU_EXT_COMMAND_START,
    ETgKN_GPU_EXT_COMMAND_DIRECT,
    ETgKN_GPU_EXT_COMMAND_COMPUTE,
    ETgKN_GPU_EXT_COMMAND_COPY,

    ETgKN_GPU_EXT_COMMAND_END,
    ETgKN_GPU_EXT_COMMAND_MAX = ETgKN_GPU_EXT_COMMAND_END,
    ETgKN_GPU_EXT_COMMAND_COUNT = ETgKN_GPU_EXT_COMMAND_END - ETgKN_GPU_EXT_COMMAND_START,
);

/* =============================================================================================================================================================================== */
#endif
