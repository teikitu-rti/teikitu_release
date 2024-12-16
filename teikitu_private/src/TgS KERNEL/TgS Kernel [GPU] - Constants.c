/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Kernel - Constants [GPU].c
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

/* ---- tgKN_GPU_Format_To_String ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgCHAR_U8_CP tgKN_GPU_Format_To_String( ETgKN_GPU_EXT_FORMAT_C enFormat )
{
    TgWARN_DISABLE_PUSH(4061 4062,switch-enum)
    switch (enFormat) {
    case ETgKN_GPU_EXT_FORMAT_R32G32B32A32_FLOAT: return (u8"R32G32B32A32_FLOAT");
    case ETgKN_GPU_EXT_FORMAT_R16G16B16A16_FLOAT: return (u8"R16G16B16A16_FLOAT");
    case ETgKN_GPU_EXT_FORMAT_R10G10B10A2_UNORM: return (u8"R10G10B10A2_UNORM");
    case ETgKN_GPU_EXT_FORMAT_R8G8B8A8_UNORM: return (u8"R8G8B8A8_UNORM");
    case ETgKN_GPU_EXT_FORMAT_R8G8B8A8_UNORM_SRGB: return (u8"R8G8B8A8_UNORM_SRGB");
    case ETgKN_GPU_EXT_FORMAT_B8G8R8A8_UNORM: return (u8"B8G8R8A8_UNORM");
    case ETgKN_GPU_EXT_FORMAT_B8G8R8A8_UNORM_SRGB: return (u8"B8G8R8A8_UNORM_SRGB");
    case ETgKN_GPU_EXT_FORMAT_D24_UNORM_S8_UINT: return (u8"D24_UNORM_S8_UINT");
    case ETgKN_GPU_EXT_FORMAT_D32_FLOAT: return (u8"D32_FLOAT");

    case ETgKN_GPU_EXT_FORMAT_UNKNOWN:
    case ETgKN_GPU_EXT_FORMAT__MAX:
        return (u8"UNKNOWN");

    default:
        TgS_NO_DEFAULT( return (u8"") );
    };
    TgWARN_DISABLE_POP()
}
