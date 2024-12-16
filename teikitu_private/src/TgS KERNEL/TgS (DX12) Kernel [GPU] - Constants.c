/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (DX12) Kernel - Constants [GPU].c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

#if TgS_STAT__KERNEL || TgS_DEBUG__KERNEL
/* ---- tgKN_GPU_EXT_FMT_To_USZ -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgMSVC_WARN_DISABLE_PUSH(4715)
TgCHAR_U8_CP tgKN_GPU_EXT_FMT_To_USZ( ETgKN_GPU_EXT_FORMAT_C enFormat )
{
    switch (enFormat) {
    case ETgKN_GPU_EXT_FORMAT_R32G32B32A32_TYPELESS:
        return (u8"R32G32B32A32_TYPELESS");
    case ETgKN_GPU_EXT_FORMAT_R32G32B32A32_FLOAT:
        return (u8"R32G32B32A32_FLOAT");
    case ETgKN_GPU_EXT_FORMAT_R32G32B32A32_UINT:
        return (u8"R32G32B32A32_UINT");
    case ETgKN_GPU_EXT_FORMAT_R32G32B32A32_SINT:
        return (u8"R32G32B32A32_SINT");
    case ETgKN_GPU_EXT_FORMAT_R32G32B32_TYPELESS:
        return (u8"R32G32B32_TYPELESS");
    case ETgKN_GPU_EXT_FORMAT_R32G32B32_FLOAT:
        return (u8"R32G32B32_FLOAT");
    case ETgKN_GPU_EXT_FORMAT_R32G32B32_UINT:
        return (u8"R32G32B32_UINT");
    case ETgKN_GPU_EXT_FORMAT_R32G32B32_SINT:
        return (u8"R32G32B32_SINT");
    case ETgKN_GPU_EXT_FORMAT_R16G16B16A16_TYPELESS:
        return (u8"R16G16B16A16_TYPELESS");
    case ETgKN_GPU_EXT_FORMAT_R16G16B16A16_FLOAT:
        return (u8"R16G16B16A16_FLOAT");
    case ETgKN_GPU_EXT_FORMAT_R16G16B16A16_UNORM:
        return (u8"R16G16B16A16_UNORM");
    case ETgKN_GPU_EXT_FORMAT_R16G16B16A16_UINT:
        return (u8"R16G16B16A16_UINT");
    case ETgKN_GPU_EXT_FORMAT_R16G16B16A16_SNORM:
        return (u8"R16G16B16A16_SNORM");
    case ETgKN_GPU_EXT_FORMAT_R16G16B16A16_SINT:
        return (u8"R16G16B16A16_SINT");
    case ETgKN_GPU_EXT_FORMAT_R32G32_TYPELESS:
        return (u8"R32G32_TYPELESS");
    case ETgKN_GPU_EXT_FORMAT_R32G32_FLOAT:
        return (u8"R32G32_FLOAT");
    case ETgKN_GPU_EXT_FORMAT_R32G32_UINT:
        return (u8"R32G32_UINT");
    case ETgKN_GPU_EXT_FORMAT_R32G32_SINT:
        return (u8"R32G32_SINT");
    case ETgKN_GPU_EXT_FORMAT_R32G8X24_TYPELESS:
        return (u8"R32G8X24_TYPELESS");
    case ETgKN_GPU_EXT_FORMAT_D32_FLOAT_S8X24_UINT:
        return (u8"D32_FLOAT_S8X24_UINT");
    case ETgKN_GPU_EXT_FORMAT_R32_FLOAT_X8X24_TYPELESS:
        return (u8"R32_FLOAT_X8X24_TYPELESS");
    case ETgKN_GPU_EXT_FORMAT_X32_TYPELESS_G8X24_UINT:
        return (u8"X32_TYPELESS_G8X24_UINT");
    case ETgKN_GPU_EXT_FORMAT_R10G10B10A2_TYPELESS:
        return (u8"R10G10B10A2_TYPELESS");
    case ETgKN_GPU_EXT_FORMAT_R10G10B10A2_UNORM:
        return (u8"R10G10B10A2_UNORM");
    case ETgKN_GPU_EXT_FORMAT_R10G10B10A2_UINT:
        return (u8"R10G10B10A2_UINT");
    case ETgKN_GPU_EXT_FORMAT_R11G11B10_FLOAT:
        return (u8"R11G11B10_FLOAT");
    case ETgKN_GPU_EXT_FORMAT_R8G8B8A8_TYPELESS:
        return (u8"R8G8B8A8_TYPELESS");
    case ETgKN_GPU_EXT_FORMAT_R8G8B8A8_UNORM:
        return (u8"R8G8B8A8_UNORM");
    case ETgKN_GPU_EXT_FORMAT_R8G8B8A8_UNORM_SRGB:
        return (u8"R8G8B8A8_UNORM_SRGB");
    case ETgKN_GPU_EXT_FORMAT_R8G8B8A8_UINT:
        return (u8"R8G8B8A8_UINT");
    case ETgKN_GPU_EXT_FORMAT_R8G8B8A8_SNORM:
        return (u8"R8G8B8A8_SNORM");
    case ETgKN_GPU_EXT_FORMAT_R8G8B8A8_SINT:
        return (u8"R8G8B8A8_SINT");
    case ETgKN_GPU_EXT_FORMAT_R16G16_TYPELESS:
        return (u8"R16G16_TYPELESS");
    case ETgKN_GPU_EXT_FORMAT_R16G16_FLOAT:
        return (u8"R16G16_FLOAT");
    case ETgKN_GPU_EXT_FORMAT_R16G16_UNORM:
        return (u8"R16G16_UNORM");
    case ETgKN_GPU_EXT_FORMAT_R16G16_UINT:
        return (u8"R16G16_UINT");
    case ETgKN_GPU_EXT_FORMAT_R16G16_SNORM:
        return (u8"R16G16_SNORM");
    case ETgKN_GPU_EXT_FORMAT_R16G16_SINT:
        return (u8"R16G16_SINT");
    case ETgKN_GPU_EXT_FORMAT_R32_TYPELESS:
        return (u8"R32_TYPELESS");
    case ETgKN_GPU_EXT_FORMAT_D32_FLOAT:
        return (u8"D32_FLOAT");
    case ETgKN_GPU_EXT_FORMAT_R32_FLOAT:
        return (u8"R32_FLOAT");
    case ETgKN_GPU_EXT_FORMAT_R32_UINT:
        return (u8"R32_UINT");
    case ETgKN_GPU_EXT_FORMAT_R32_SINT:
        return (u8"R32_SINT");
    case ETgKN_GPU_EXT_FORMAT_R24G8_TYPELESS:
        return (u8"R24G8_TYPELESS");
    case ETgKN_GPU_EXT_FORMAT_D24_UNORM_S8_UINT:
        return (u8"D24_UNORM_S8_UINT");
    case ETgKN_GPU_EXT_FORMAT_R24_UNORM_X8_TYPELESS:
        return (u8"R24_UNORM_X8_TYPELESS");
    case ETgKN_GPU_EXT_FORMAT_X24_TYPELESS_G8_UINT:
        return (u8"X24_TYPELESS_G8_UINT");
    case ETgKN_GPU_EXT_FORMAT_R8G8_TYPELESS:
        return (u8"R8G8_TYPELESS");
    case ETgKN_GPU_EXT_FORMAT_R8G8_UNORM:
        return (u8"R8G8_UNORM");
    case ETgKN_GPU_EXT_FORMAT_R8G8_UINT:
        return (u8"R8G8_UINT");
    case ETgKN_GPU_EXT_FORMAT_R8G8_SNORM:
        return (u8"R8G8_SNORM");
    case ETgKN_GPU_EXT_FORMAT_R8G8_SINT:
        return (u8"R8G8_SINT");
    case ETgKN_GPU_EXT_FORMAT_R16_TYPELESS:
        return (u8"R16_TYPELESS");
    case ETgKN_GPU_EXT_FORMAT_R16_FLOAT:
        return (u8"R16_FLOAT");
    case ETgKN_GPU_EXT_FORMAT_D16_UNORM:
        return (u8"D16_UNORM");
    case ETgKN_GPU_EXT_FORMAT_R16_UNORM:
        return (u8"R16_UNORM");
    case ETgKN_GPU_EXT_FORMAT_R16_UINT:
        return (u8"R16_UINT");
    case ETgKN_GPU_EXT_FORMAT_R16_SNORM:
        return (u8"R16_SNORM");
    case ETgKN_GPU_EXT_FORMAT_R16_SINT:
        return (u8"R16_SINT");
    case ETgKN_GPU_EXT_FORMAT_R8_TYPELESS:
        return (u8"R8_TYPELESS");
    case ETgKN_GPU_EXT_FORMAT_R8_UNORM:
        return (u8"R8_UNORM");
    case ETgKN_GPU_EXT_FORMAT_R8_UINT:
        return (u8"R8_UINT");
    case ETgKN_GPU_EXT_FORMAT_R8_SNORM:
        return (u8"R8_SNORM");
    case ETgKN_GPU_EXT_FORMAT_R8_SINT:
        return (u8"R8_SINT");
    case ETgKN_GPU_EXT_FORMAT_A8_UNORM:
        return (u8"A8_UNORM");
    case ETgKN_GPU_EXT_FORMAT_R1_UNORM:
        return (u8"R1_UNORM");
    case ETgKN_GPU_EXT_FORMAT_R9G9B9E5_SHAREDEXP:
        return (u8"R9G9B9E5_SHAREDEXP");
    case ETgKN_GPU_EXT_FORMAT_R8G8_B8G8_UNORM:
        return (u8"R8G8_B8G8_UNORM");
    case ETgKN_GPU_EXT_FORMAT_G8R8_G8B8_UNORM:
        return (u8"G8R8_G8B8_UNORM");
    case ETgKN_GPU_EXT_FORMAT_BC1_TYPELESS:
        return (u8"BC1_TYPELESS");
    case ETgKN_GPU_EXT_FORMAT_BC1_UNORM:
        return (u8"BC1_UNORM");
    case ETgKN_GPU_EXT_FORMAT_BC1_UNORM_SRGB:
        return (u8"BC1_UNORM_SRGB");
    case ETgKN_GPU_EXT_FORMAT_BC2_TYPELESS:
        return (u8"BC2_TYPELESS");
    case ETgKN_GPU_EXT_FORMAT_BC2_UNORM:
        return (u8"BC2_UNORM");
    case ETgKN_GPU_EXT_FORMAT_BC2_UNORM_SRGB:
        return (u8"BC2_UNORM_SRGB");
    case ETgKN_GPU_EXT_FORMAT_BC3_TYPELESS:
        return (u8"BC3_TYPELESS");
    case ETgKN_GPU_EXT_FORMAT_BC3_UNORM:
        return (u8"BC3_UNORM");
    case ETgKN_GPU_EXT_FORMAT_BC3_UNORM_SRGB:
        return (u8"BC3_UNORM_SRGB");
    case ETgKN_GPU_EXT_FORMAT_BC4_TYPELESS:
        return (u8"BC4_TYPELESS");
    case ETgKN_GPU_EXT_FORMAT_BC4_UNORM:
        return (u8"BC4_UNORM");
    case ETgKN_GPU_EXT_FORMAT_BC4_SNORM:
        return (u8"BC4_SNORM");
    case ETgKN_GPU_EXT_FORMAT_BC5_TYPELESS:
        return (u8"BC5_TYPELESS");
    case ETgKN_GPU_EXT_FORMAT_BC5_UNORM:
        return (u8"BC5_UNORM");
    case ETgKN_GPU_EXT_FORMAT_BC5_SNORM:
        return (u8"BC5_SNORM");
    case ETgKN_GPU_EXT_FORMAT_B5G6R5_UNORM:
        return (u8"B5G6R5_UNORM");
    case ETgKN_GPU_EXT_FORMAT_B5G5R5A1_UNORM:
        return (u8"B5G5R5A1_UNORM");
    case ETgKN_GPU_EXT_FORMAT_B8G8R8A8_UNORM:
        return (u8"B8G8R8A8_UNORM");
    case ETgKN_GPU_EXT_FORMAT_B8G8R8A8_UNORM_SRGB:
        return (u8"B8G8R8A8_UNORM_SRGB");
    case ETgKN_GPU_EXT_FORMAT_B8G8R8X8_UNORM: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_R10G10B10_XR_BIAS_A2_UNORM: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_B8G8R8A8_TYPELESS: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_B8G8R8X8_TYPELESS: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_B8G8R8X8_UNORM_SRGB: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_BC6H_TYPELESS: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_BC6H_UF16: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_BC6H_SF16: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_BC7_TYPELESS: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_BC7_UNORM: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_BC7_UNORM_SRGB: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_AYUV: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_Y410: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_Y416: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_NV12: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_P010: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_P016: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_420_OPAQUE: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_YUY2: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_Y210: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_Y216: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_NV11: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_AI44: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_IA44: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_P8: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_A8P8: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_B4G4R4A4_UNORM: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_P208: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_V208: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_V408: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_SAMPLER_FEEDBACK_MIN_MIP_OPAQUE: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_SAMPLER_FEEDBACK_MIP_REGION_USED_OPAQUE: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_UNKNOWN: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT__MAX:
        return (u8"Unknown format");
    };
}
TgMSVC_WARN_DISABLE_POP()


/* ---- tgKN_GPU_EXT_FMT_To_WSZ -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgMSVC_WARN_DISABLE_PUSH(4715)
TgCHAR_WC_CP tgKN_GPU_EXT_FMT_To_WSZ( ETgKN_GPU_EXT_FORMAT_C enFormat )
{
    switch (enFormat) {
    case ETgKN_GPU_EXT_FORMAT_R32G32B32A32_TYPELESS:
        return (L"R32G32B32A32_TYPELESS");
    case ETgKN_GPU_EXT_FORMAT_R32G32B32A32_FLOAT:
        return (L"R32G32B32A32_FLOAT");
    case ETgKN_GPU_EXT_FORMAT_R32G32B32A32_UINT:
        return (L"R32G32B32A32_UINT");
    case ETgKN_GPU_EXT_FORMAT_R32G32B32A32_SINT:
        return (L"R32G32B32A32_SINT");
    case ETgKN_GPU_EXT_FORMAT_R32G32B32_TYPELESS:
        return (L"R32G32B32_TYPELESS");
    case ETgKN_GPU_EXT_FORMAT_R32G32B32_FLOAT:
        return (L"R32G32B32_FLOAT");
    case ETgKN_GPU_EXT_FORMAT_R32G32B32_UINT:
        return (L"R32G32B32_UINT");
    case ETgKN_GPU_EXT_FORMAT_R32G32B32_SINT:
        return (L"R32G32B32_SINT");
    case ETgKN_GPU_EXT_FORMAT_R16G16B16A16_TYPELESS:
        return (L"R16G16B16A16_TYPELESS");
    case ETgKN_GPU_EXT_FORMAT_R16G16B16A16_FLOAT:
        return (L"R16G16B16A16_FLOAT");
    case ETgKN_GPU_EXT_FORMAT_R16G16B16A16_UNORM:
        return (L"R16G16B16A16_UNORM");
    case ETgKN_GPU_EXT_FORMAT_R16G16B16A16_UINT:
        return (L"R16G16B16A16_UINT");
    case ETgKN_GPU_EXT_FORMAT_R16G16B16A16_SNORM:
        return (L"R16G16B16A16_SNORM");
    case ETgKN_GPU_EXT_FORMAT_R16G16B16A16_SINT:
        return (L"R16G16B16A16_SINT");
    case ETgKN_GPU_EXT_FORMAT_R32G32_TYPELESS:
        return (L"R32G32_TYPELESS");
    case ETgKN_GPU_EXT_FORMAT_R32G32_FLOAT:
        return (L"R32G32_FLOAT");
    case ETgKN_GPU_EXT_FORMAT_R32G32_UINT:
        return (L"R32G32_UINT");
    case ETgKN_GPU_EXT_FORMAT_R32G32_SINT:
        return (L"R32G32_SINT");
    case ETgKN_GPU_EXT_FORMAT_R32G8X24_TYPELESS:
        return (L"R32G8X24_TYPELESS");
    case ETgKN_GPU_EXT_FORMAT_D32_FLOAT_S8X24_UINT:
        return (L"D32_FLOAT_S8X24_UINT");
    case ETgKN_GPU_EXT_FORMAT_R32_FLOAT_X8X24_TYPELESS:
        return (L"R32_FLOAT_X8X24_TYPELESS");
    case ETgKN_GPU_EXT_FORMAT_X32_TYPELESS_G8X24_UINT:
        return (L"X32_TYPELESS_G8X24_UINT");
    case ETgKN_GPU_EXT_FORMAT_R10G10B10A2_TYPELESS:
        return (L"R10G10B10A2_TYPELESS");
    case ETgKN_GPU_EXT_FORMAT_R10G10B10A2_UNORM:
        return (L"R10G10B10A2_UNORM");
    case ETgKN_GPU_EXT_FORMAT_R10G10B10A2_UINT:
        return (L"R10G10B10A2_UINT");
    case ETgKN_GPU_EXT_FORMAT_R11G11B10_FLOAT:
        return (L"R11G11B10_FLOAT");
    case ETgKN_GPU_EXT_FORMAT_R8G8B8A8_TYPELESS:
        return (L"R8G8B8A8_TYPELESS");
    case ETgKN_GPU_EXT_FORMAT_R8G8B8A8_UNORM:
        return (L"R8G8B8A8_UNORM");
    case ETgKN_GPU_EXT_FORMAT_R8G8B8A8_UNORM_SRGB:
        return (L"R8G8B8A8_UNORM_SRGB");
    case ETgKN_GPU_EXT_FORMAT_R8G8B8A8_UINT:
        return (L"R8G8B8A8_UINT");
    case ETgKN_GPU_EXT_FORMAT_R8G8B8A8_SNORM:
        return (L"R8G8B8A8_SNORM");
    case ETgKN_GPU_EXT_FORMAT_R8G8B8A8_SINT:
        return (L"R8G8B8A8_SINT");
    case ETgKN_GPU_EXT_FORMAT_R16G16_TYPELESS:
        return (L"R16G16_TYPELESS");
    case ETgKN_GPU_EXT_FORMAT_R16G16_FLOAT:
        return (L"R16G16_FLOAT");
    case ETgKN_GPU_EXT_FORMAT_R16G16_UNORM:
        return (L"R16G16_UNORM");
    case ETgKN_GPU_EXT_FORMAT_R16G16_UINT:
        return (L"R16G16_UINT");
    case ETgKN_GPU_EXT_FORMAT_R16G16_SNORM:
        return (L"R16G16_SNORM");
    case ETgKN_GPU_EXT_FORMAT_R16G16_SINT:
        return (L"R16G16_SINT");
    case ETgKN_GPU_EXT_FORMAT_R32_TYPELESS:
        return (L"R32_TYPELESS");
    case ETgKN_GPU_EXT_FORMAT_D32_FLOAT:
        return (L"D32_FLOAT");
    case ETgKN_GPU_EXT_FORMAT_R32_FLOAT:
        return (L"R32_FLOAT");
    case ETgKN_GPU_EXT_FORMAT_R32_UINT:
        return (L"R32_UINT");
    case ETgKN_GPU_EXT_FORMAT_R32_SINT:
        return (L"R32_SINT");
    case ETgKN_GPU_EXT_FORMAT_R24G8_TYPELESS:
        return (L"R24G8_TYPELESS");
    case ETgKN_GPU_EXT_FORMAT_D24_UNORM_S8_UINT:
        return (L"D24_UNORM_S8_UINT");
    case ETgKN_GPU_EXT_FORMAT_R24_UNORM_X8_TYPELESS:
        return (L"R24_UNORM_X8_TYPELESS");
    case ETgKN_GPU_EXT_FORMAT_X24_TYPELESS_G8_UINT:
        return (L"X24_TYPELESS_G8_UINT");
    case ETgKN_GPU_EXT_FORMAT_R8G8_TYPELESS:
        return (L"R8G8_TYPELESS");
    case ETgKN_GPU_EXT_FORMAT_R8G8_UNORM:
        return (L"R8G8_UNORM");
    case ETgKN_GPU_EXT_FORMAT_R8G8_UINT:
        return (L"R8G8_UINT");
    case ETgKN_GPU_EXT_FORMAT_R8G8_SNORM:
        return (L"R8G8_SNORM");
    case ETgKN_GPU_EXT_FORMAT_R8G8_SINT:
        return (L"R8G8_SINT");
    case ETgKN_GPU_EXT_FORMAT_R16_TYPELESS:
        return (L"R16_TYPELESS");
    case ETgKN_GPU_EXT_FORMAT_R16_FLOAT:
        return (L"R16_FLOAT");
    case ETgKN_GPU_EXT_FORMAT_D16_UNORM:
        return (L"D16_UNORM");
    case ETgKN_GPU_EXT_FORMAT_R16_UNORM:
        return (L"R16_UNORM");
    case ETgKN_GPU_EXT_FORMAT_R16_UINT:
        return (L"R16_UINT");
    case ETgKN_GPU_EXT_FORMAT_R16_SNORM:
        return (L"R16_SNORM");
    case ETgKN_GPU_EXT_FORMAT_R16_SINT:
        return (L"R16_SINT");
    case ETgKN_GPU_EXT_FORMAT_R8_TYPELESS:
        return (L"R8_TYPELESS");
    case ETgKN_GPU_EXT_FORMAT_R8_UNORM:
        return (L"R8_UNORM");
    case ETgKN_GPU_EXT_FORMAT_R8_UINT:
        return (L"R8_UINT");
    case ETgKN_GPU_EXT_FORMAT_R8_SNORM:
        return (L"R8_SNORM");
    case ETgKN_GPU_EXT_FORMAT_R8_SINT:
        return (L"R8_SINT");
    case ETgKN_GPU_EXT_FORMAT_A8_UNORM:
        return (L"A8_UNORM");
    case ETgKN_GPU_EXT_FORMAT_R1_UNORM:
        return (L"R1_UNORM");
    case ETgKN_GPU_EXT_FORMAT_R9G9B9E5_SHAREDEXP:
        return (L"R9G9B9E5_SHAREDEXP");
    case ETgKN_GPU_EXT_FORMAT_R8G8_B8G8_UNORM:
        return (L"R8G8_B8G8_UNORM");
    case ETgKN_GPU_EXT_FORMAT_G8R8_G8B8_UNORM:
        return (L"G8R8_G8B8_UNORM");
    case ETgKN_GPU_EXT_FORMAT_BC1_TYPELESS:
        return (L"BC1_TYPELESS");
    case ETgKN_GPU_EXT_FORMAT_BC1_UNORM:
        return (L"BC1_UNORM");
    case ETgKN_GPU_EXT_FORMAT_BC1_UNORM_SRGB:
        return (L"BC1_UNORM_SRGB");
    case ETgKN_GPU_EXT_FORMAT_BC2_TYPELESS:
        return (L"BC2_TYPELESS");
    case ETgKN_GPU_EXT_FORMAT_BC2_UNORM:
        return (L"BC2_UNORM");
    case ETgKN_GPU_EXT_FORMAT_BC2_UNORM_SRGB:
        return (L"BC2_UNORM_SRGB");
    case ETgKN_GPU_EXT_FORMAT_BC3_TYPELESS:
        return (L"BC3_TYPELESS");
    case ETgKN_GPU_EXT_FORMAT_BC3_UNORM:
        return (L"BC3_UNORM");
    case ETgKN_GPU_EXT_FORMAT_BC3_UNORM_SRGB:
        return (L"BC3_UNORM_SRGB");
    case ETgKN_GPU_EXT_FORMAT_BC4_TYPELESS:
        return (L"BC4_TYPELESS");
    case ETgKN_GPU_EXT_FORMAT_BC4_UNORM:
        return (L"BC4_UNORM");
    case ETgKN_GPU_EXT_FORMAT_BC4_SNORM:
        return (L"BC4_SNORM");
    case ETgKN_GPU_EXT_FORMAT_BC5_TYPELESS:
        return (L"BC5_TYPELESS");
    case ETgKN_GPU_EXT_FORMAT_BC5_UNORM:
        return (L"BC5_UNORM");
    case ETgKN_GPU_EXT_FORMAT_BC5_SNORM:
        return (L"BC5_SNORM");
    case ETgKN_GPU_EXT_FORMAT_B5G6R5_UNORM:
        return (L"B5G6R5_UNORM");
    case ETgKN_GPU_EXT_FORMAT_B5G5R5A1_UNORM:
        return (L"B5G5R5A1_UNORM");
    case ETgKN_GPU_EXT_FORMAT_B8G8R8A8_UNORM:
        return (L"B8G8R8A8_UNORM");
    case ETgKN_GPU_EXT_FORMAT_B8G8R8A8_UNORM_SRGB:
        return (L"B8G8R8A8_UNORM_SRGB");
    case ETgKN_GPU_EXT_FORMAT_B8G8R8X8_UNORM: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_R10G10B10_XR_BIAS_A2_UNORM: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_B8G8R8A8_TYPELESS: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_B8G8R8X8_TYPELESS: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_B8G8R8X8_UNORM_SRGB: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_BC6H_TYPELESS: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_BC6H_UF16: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_BC6H_SF16: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_BC7_TYPELESS: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_BC7_UNORM: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_BC7_UNORM_SRGB: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_AYUV: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_Y410: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_Y416: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_NV12: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_P010: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_P016: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_420_OPAQUE: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_YUY2: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_Y210: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_Y216: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_NV11: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_AI44: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_IA44: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_P8: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_A8P8: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_B4G4R4A4_UNORM: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_P208: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_V208: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_V408: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_SAMPLER_FEEDBACK_MIN_MIP_OPAQUE: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_SAMPLER_FEEDBACK_MIP_REGION_USED_OPAQUE: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_UNKNOWN: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT__MAX:
        return (L"Unknown format");
    };
}
TgMSVC_WARN_DISABLE_POP()


/*# TgS_STAT__KERNEL || TgS_DEBUG__KERNEL */
#endif




