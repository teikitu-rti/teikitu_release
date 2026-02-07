/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Kernel [GPU] - Resource [HLSL] [Constants].h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.20 | »GUID« DE461472-5528-4A5B-A7F4-09CCAD73387B */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/* == Kernel ===================================================================================================================================================================== */
#if !defined(TGS_KERNEL_GPU_RESOURCE_HLSL_CONSTANTS_H)
#define TGS_KERNEL_GPU_RESOURCE_HLSL_CONSTANTS_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Macro Constants                                                                                                                                                                */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

#define KTgMACRO_KN_GPU_HLSL_COLOR_SPACE_G22_P709                                       0
#define KTgMACRO_KN_GPU_HLSL_COLOR_SPACE_G2084_P2020                                    1
#define KTgMACRO_KN_GPU_HLSL_COLOR_SPACE_G10_P709                                       2
#define KTgMACRO_KN_GPU_HLSL_COLOR_SPACE_G10_P709_NO_CORRECTION                         3

#define KTgMACRO_KN_GPU_MAX_RENDER_TARGET_IMAGE                                         128
#define KTgMACRO_KN_GPU_MAX_IMAGE                                                       4096
#define KTgMACRO_KN_GPU_MAX_CUBE                                                        64
#define KTgMACRO_KN_GPU_MAX_VOLUME                                                      64

#define KTgMACRO_KN_GPU_VLKN_SAMPLER_COUNT                                              8



#define KTgMACRO_KN_GPU_VLKN_BINDING_IMMUTABLE_SAMPLERS                                 0
#define KTgMACRO_KN_GPU_VLKN_BINDING_RENDER_DESC                                        1

#define KTgMACRO_KN_GPU_VLKN_BINDING_UNIT_TEST_INSTANCE_DATA                            2
#define KTgMACRO_KN_GPU_VLKN_BINDING_UNIT_TEST_SCENE_DATA                               3

#define KTgMACRO_KN_GPU_VLKN_BINDING_LUMINANCE_HISTOGRAM                                2

#define KTgMACRO_KN_GPU_VLKN_BINDING_DBG_UBO                                            2
#define KTgMACRO_KN_GPU_VLKN_BINDING_DBG_SBO                                            3
#define KTgMACRO_KN_GPU_VLKN_BINDING_DBG_LINE_SBO__INPUT_LINES                          2
#define KTgMACRO_KN_GPU_VLKN_BINDING_DBG_LINE_SBO__VISIBLE_LINES                        3

#define KTgMACRO_KN_GPU_VLKN_BINDING_TX_IMG_IMAGE                                       (32 + KTgMACRO_KN_GPU_MAX_RENDER_TARGET_IMAGE)
#define KTgMACRO_KN_GPU_VLKN_BINDING_TX_IMG                                             (KTgMACRO_KN_GPU_VLKN_BINDING_TX_IMG_IMAGE + KTgMACRO_KN_GPU_MAX_IMAGE)
#define KTgMACRO_KN_GPU_VLKN_BINDING_TX_CBE                                             (KTgMACRO_KN_GPU_VLKN_BINDING_TX_IMG + KTgMACRO_KN_GPU_MAX_CUBE)
#define KTgMACRO_KN_GPU_VLKN_BINDING_TX_VOL                                             (KTgMACRO_KN_GPU_VLKN_BINDING_TX_CBE + KTgMACRO_KN_GPU_MAX_VOLUME)



#define KTgKN_GPU_VLKN_DBG_LINE__TASK_WORKGROUP_SIZE                                    64



#define KTgMACRO_KN_GPU_VLKN_CONSTANT_ID_USE_G22_P709                                   0
#define KTgMACRO_KN_GPU_VLKN_CONSTANT_ID_USE_G2084_P2020                                1
#define KTgMACRO_KN_GPU_VLKN_CONSTANT_ID_USE_G10_P709                                   2
#define KTgMACRO_KN_GPU_VLKN_CONSTANT_ID_DBG_USE_LIGHTING                               3


/* =============================================================================================================================================================================== */
#endif
