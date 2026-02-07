/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (WINDOWS) Kernel - Constants.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
#if !defined(TGS_WINDOWS_KERNEL_CONSTANTS_H)
#define TGS_WINDOWS_KERNEL_CONSTANTS_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#if !defined(TGS_KERNEL_H)
#error Base Kernel include chain should be prior to this file.
#endif


/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Configuration                                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

enum { KTgKN_MAX_JOB_THREAD                 =   128 };  /**< Maximum number of job threads used by the kernel */
enum { KTgKN_MAX_WINDOWS                    =     9 };  /**< Maximum number of windows */
enum { KTgKN_MAX_TITLE                      =   256 };

/* DXGI Formats */
typedef enum TgATTRIBUTE_ENUM
{
    ETgKN_OS_GPU_FORMAT_UNDEFINED = 0,
    ETgKN_OS_GPU_FORMAT_R32G32B32A32_SFLOAT = 2,
    ETgKN_OS_GPU_FORMAT_R32G32B32A32_UINT = 3,
    ETgKN_OS_GPU_FORMAT_R32G32B32A32_SINT = 4,
    ETgKN_OS_GPU_FORMAT_R32G32B32_SFLOAT = 6,
    ETgKN_OS_GPU_FORMAT_R32G32B32_UINT = 7,
    ETgKN_OS_GPU_FORMAT_R32G32B32_SINT = 8,
    ETgKN_OS_GPU_FORMAT_R16G16B16A16_SFLOAT = 10,
    ETgKN_OS_GPU_FORMAT_R16G16B16A16_UNORM = 11,
    ETgKN_OS_GPU_FORMAT_R16G16B16A16_UINT = 12,
    ETgKN_OS_GPU_FORMAT_R16G16B16A16_SNORM = 13,
    ETgKN_OS_GPU_FORMAT_R16G16B16A16_SINT = 14,
    ETgKN_OS_GPU_FORMAT_R32G32_SFLOAT = 16,
    ETgKN_OS_GPU_FORMAT_R32G32_UINT = 17,
    ETgKN_OS_GPU_FORMAT_R32G32_SINT = 18,
    ETgKN_OS_GPU_FORMAT_A2R10G10B10_UNORM_PACK32 = 24,
    ETgKN_OS_GPU_FORMAT_A2R10G10B10_UINT_PACK32 = 25,
    ETgKN_OS_GPU_FORMAT_R11G11B10_SFLOAT = 26,
    ETgKN_OS_GPU_FORMAT_R8G8B8A8_UNORM = 28,
    ETgKN_OS_GPU_FORMAT_R8G8B8A8_SRGB = 29,
    ETgKN_OS_GPU_FORMAT_R8G8B8A8_UINT = 30,
    ETgKN_OS_GPU_FORMAT_R8G8B8A8_SNORM = 31,
    ETgKN_OS_GPU_FORMAT_R8G8B8A8_SINT = 32,
    ETgKN_OS_GPU_FORMAT_R16G16_SFLOAT = 34,
    ETgKN_OS_GPU_FORMAT_R16G16_UNORM = 35,
    ETgKN_OS_GPU_FORMAT_R16G16_UINT = 36,
    ETgKN_OS_GPU_FORMAT_R16G16_SNORM = 37,
    ETgKN_OS_GPU_FORMAT_R16G16_SINT = 38,
    ETgKN_OS_GPU_FORMAT_D32_SFLOAT = 40,
    ETgKN_OS_GPU_FORMAT_R32_SFLOAT = 41,
    ETgKN_OS_GPU_FORMAT_R32_UINT = 42,
    ETgKN_OS_GPU_FORMAT_R32_SINT = 43,
    ETgKN_OS_GPU_FORMAT_D24_UNORM_S8_UINT = 45,
    ETgKN_OS_GPU_FORMAT_R8G8_UNORM = 49,
    ETgKN_OS_GPU_FORMAT_R8G8_UINT = 50,
    ETgKN_OS_GPU_FORMAT_R8G8_SNORM = 51,
    ETgKN_OS_GPU_FORMAT_R8G8_SINT = 52,
    ETgKN_OS_GPU_FORMAT_R16_SFLOAT = 54,
    ETgKN_OS_GPU_FORMAT_D16_UNORM = 55,
    ETgKN_OS_GPU_FORMAT_R16_UNORM = 56,
    ETgKN_OS_GPU_FORMAT_R16_UINT = 57,
    ETgKN_OS_GPU_FORMAT_R16_SNORM = 58,
    ETgKN_OS_GPU_FORMAT_R16_SINT = 59,
    ETgKN_OS_GPU_FORMAT_R8_UNORM = 61,
    ETgKN_OS_GPU_FORMAT_R8_UINT = 62,
    ETgKN_OS_GPU_FORMAT_R8_SNORM = 63,
    ETgKN_OS_GPU_FORMAT_R8_SINT = 64,
    ETgKN_OS_GPU_FORMAT_BC1_UNORM = 71,
    ETgKN_OS_GPU_FORMAT_BC1_UNORM_SRGB = 72,
    ETgKN_OS_GPU_FORMAT_BC2_UNORM = 74,
    ETgKN_OS_GPU_FORMAT_BC2_UNORM_SRGB = 75,
    ETgKN_OS_GPU_FORMAT_BC3_UNORM = 77,
    ETgKN_OS_GPU_FORMAT_BC3_UNORM_SRGB = 78,
    ETgKN_OS_GPU_FORMAT_BC4_UNORM = 80,
    ETgKN_OS_GPU_FORMAT_BC4_SNORM = 81,
    ETgKN_OS_GPU_FORMAT_BC5_UNORM = 83,
    ETgKN_OS_GPU_FORMAT_BC5_SNORM = 84,
    ETgKN_OS_GPU_FORMAT_B5G6R5_UNORM = 85,
    ETgKN_OS_GPU_FORMAT_B5G5R5A1_UNORM = 86,
    ETgKN_OS_GPU_FORMAT_B8G8R8A8_UNORM = 87,
    ETgKN_OS_GPU_FORMAT_B8G8R8A8_SRGB = 91,
    ETgKN_OS_GPU_FORMAT_BC6H_UF16 = 95,
    ETgKN_OS_GPU_FORMAT_BC6H_SF16 = 96,
    ETgKN_OS_GPU_FORMAT_BC7_UNORM = 98,
    ETgKN_OS_GPU_FORMAT_BC7_UNORM_SRGB = 99,
} ETgKN_OS_GPU_FORMAT;
TgTYPE_MODIFIER_DEFAULT(ETgKN_OS_GPU_FORMAT);



/* =============================================================================================================================================================================== */
#endif
