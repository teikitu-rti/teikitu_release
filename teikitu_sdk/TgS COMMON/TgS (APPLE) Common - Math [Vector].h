/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (APPLE) Common - Math [Vector].h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_APPLE_COMMON_MATH_VECTOR_H)
#define TGS_APPLE_COMMON_MATH_VECTOR_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifdef TGS_COMMON_MATH_VECTOR_SPECIALIZATION
    #error "Previous Math Specialization Already Exists"
#endif

#define TGS_COMMON_MATH_VECTOR_SPECIALIZATION

#ifdef TGS_COMMON_MATH_MATRIX_SPECIALIZATION
    #error "Previous Math Specialization Already Exists"
#endif

#define TGS_COMMON_MATH_MATRIX_SPECIALIZATION

#include <simd/simd.h>
#undef NAN


/* == Common ===================================================================================================================================================================== */
/* MARK: No Unit Test Required                                                                                                                                                     */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Types                                                                                                                                                                   */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#define TgVEC_U08_16_1_C                simd_uchar16 const
#define TgVEC_U08_16_1_P                simd_uchar16 *
#define TgVEC_U08_16_1_PC               simd_uchar16 * const
#define TgVEC_U08_16_1_PCU              simd_uchar16 * const __restrict
#define TgVEC_U08_16_1_PU               simd_uchar16 * __restrict
#define TgVEC_U08_16_1_CP               simd_uchar16 const *
#define TgVEC_U08_16_1_CPU              simd_uchar16 const * __restrict
#define TgVEC_U08_16_1_CPC              simd_uchar16 const * const
#define TgVEC_U08_16_1_CPCU             simd_uchar16 const * const __restrict
#define TgVEC_U08_16_1_PP               simd_uchar16 **
#define TgVEC_U08_16_1_PPU              simd_uchar16 ** __restrict
#define TgVEC_U08_16_1_CPCPU            simd_uchar16 const *const * __restrict
#define TgVEC_U08_16_1_CPPU             simd_uchar16 const ** __restrict
#define TgVEC_U08_16_1_PPCU             simd_uchar16 ** const __restrict
#define TgVEC_U08_16_1                  simd_uchar16

#define TgVEC_U16_08_1_C                simd_ushort8 const
#define TgVEC_U16_08_1_P                simd_ushort8 *
#define TgVEC_U16_08_1_PC               simd_ushort8 * const
#define TgVEC_U16_08_1_PCU              simd_ushort8 * const __restrict
#define TgVEC_U16_08_1_PU               simd_ushort8 * __restrict
#define TgVEC_U16_08_1_CP               simd_ushort8 const *
#define TgVEC_U16_08_1_CPU              simd_ushort8 const * __restrict
#define TgVEC_U16_08_1_CPC              simd_ushort8 const * const
#define TgVEC_U16_08_1_CPCU             simd_ushort8 const * const __restrict
#define TgVEC_U16_08_1_PP               simd_ushort8 **
#define TgVEC_U16_08_1_PPU              simd_ushort8 ** __restrict
#define TgVEC_U16_08_1_CPCPU            simd_ushort8 const *const * __restrict
#define TgVEC_U16_08_1_CPPU             simd_ushort8 const ** __restrict
#define TgVEC_U16_08_1_PPCU             simd_ushort8 ** const __restrict
#define TgVEC_U16_08_1                  simd_ushort8

#define TgVEC_U32_04_1_C                simd_uint4 const
#define TgVEC_U32_04_1_P                simd_uint4 *
#define TgVEC_U32_04_1_PC               simd_uint4 * const
#define TgVEC_U32_04_1_PCU              simd_uint4 * const __restrict
#define TgVEC_U32_04_1_PU               simd_uint4 * __restrict
#define TgVEC_U32_04_1_CP               simd_uint4 const *
#define TgVEC_U32_04_1_CPU              simd_uint4 const * __restrict
#define TgVEC_U32_04_1_CPC              simd_uint4 const * const
#define TgVEC_U32_04_1_CPCU             simd_uint4 const * const __restrict
#define TgVEC_U32_04_1_PP               simd_uint4 **
#define TgVEC_U32_04_1_PPU              simd_uint4 ** __restrict
#define TgVEC_U32_04_1_CPCPU            simd_uint4 const *const * __restrict
#define TgVEC_U32_04_1_CPPU             simd_uint4 const ** __restrict
#define TgVEC_U32_04_1_PPCU             simd_uint4 ** const __restrict
#define TgVEC_U32_04_1                  simd_uint4

#define TgVEC_S08_16_1_C                simd_char16 const
#define TgVEC_S08_16_1_P                simd_char16 *
#define TgVEC_S08_16_1_PC               simd_char16 * const
#define TgVEC_S08_16_1_PCU              simd_char16 * const __restrict
#define TgVEC_S08_16_1_PU               simd_char16 * __restrict
#define TgVEC_S08_16_1_CP               simd_char16 const *
#define TgVEC_S08_16_1_CPU              simd_char16 const * __restrict
#define TgVEC_S08_16_1_CPC              simd_char16 const * const
#define TgVEC_S08_16_1_CPCU             simd_char16 const * const __restrict
#define TgVEC_S08_16_1_PP               simd_char16 **
#define TgVEC_S08_16_1_PPU              simd_char16 ** __restrict
#define TgVEC_S08_16_1_CPCPU            simd_char16 const *const * __restrict
#define TgVEC_S08_16_1_CPPU             simd_char16 const ** __restrict
#define TgVEC_S08_16_1_PPCU             simd_char16 ** const __restrict
#define TgVEC_S08_16_1                  simd_char16

#define TgVEC_S16_08_1_C                simd_short8 const
#define TgVEC_S16_08_1_P                simd_short8 *
#define TgVEC_S16_08_1_PC               simd_short8 * const
#define TgVEC_S16_08_1_PCU              simd_short8 * const __restrict
#define TgVEC_S16_08_1_PU               simd_short8 * __restrict
#define TgVEC_S16_08_1_CP               simd_short8 const *
#define TgVEC_S16_08_1_CPU              simd_short8 const * __restrict
#define TgVEC_S16_08_1_CPC              simd_short8 const * const
#define TgVEC_S16_08_1_CPCU             simd_short8 const * const __restrict
#define TgVEC_S16_08_1_PP               simd_short8 **
#define TgVEC_S16_08_1_PPU              simd_short8 ** __restrict
#define TgVEC_S16_08_1_CPCPU            simd_short8 const *const * __restrict
#define TgVEC_S16_08_1_CPPU             simd_short8 const ** __restrict
#define TgVEC_S16_08_1_PPCU             simd_short8 ** const __restrict
#define TgVEC_S16_08_1                  simd_short8

#define TgVEC_S32_04_1_C                simd_int4 const
#define TgVEC_S32_04_1_P                simd_int4 *
#define TgVEC_S32_04_1_PC               simd_int4 * const
#define TgVEC_S32_04_1_PCU              simd_int4 * const __restrict
#define TgVEC_S32_04_1_PU               simd_int4 * __restrict
#define TgVEC_S32_04_1_CP               simd_int4 const *
#define TgVEC_S32_04_1_CPU              simd_int4 const * __restrict
#define TgVEC_S32_04_1_CPC              simd_int4 const * const
#define TgVEC_S32_04_1_CPCU             simd_int4 const * const __restrict
#define TgVEC_S32_04_1_PP               simd_int4 **
#define TgVEC_S32_04_1_PPU              simd_int4 ** __restrict
#define TgVEC_S32_04_1_CPCPU            simd_int4 const *const * __restrict
#define TgVEC_S32_04_1_CPPU             simd_int4 const ** __restrict
#define TgVEC_S32_04_1_PPCU             simd_int4 ** const __restrict
#define TgVEC_S32_04_1                  simd_int4

#define TgVEC_F32_04_1_C                simd_float4 const
#define TgVEC_F32_04_1_P                simd_float4 *
#define TgVEC_F32_04_1_PC               simd_float4 * const
#define TgVEC_F32_04_1_PCU              simd_float4 * const __restrict
#define TgVEC_F32_04_1_PU               simd_float4 * __restrict
#define TgVEC_F32_04_1_CP               simd_float4 const *
#define TgVEC_F32_04_1_CPU              simd_float4 const * __restrict
#define TgVEC_F32_04_1_CPC              simd_float4 const * const
#define TgVEC_F32_04_1_CPCU             simd_float4 const * const __restrict
#define TgVEC_F32_04_1_PP               simd_float4 **
#define TgVEC_F32_04_1_PPU              simd_float4 ** __restrict
#define TgVEC_F32_04_1_CPCPU            simd_float4 const *const * __restrict
#define TgVEC_F32_04_1_CPPU             simd_float4 const ** __restrict
#define TgVEC_F32_04_1_PPCU             simd_float4 ** const __restrict
#define TgVEC_F32_04_1                  simd_float4




#define TgVEC1_U08_16_1_C               simd_packed_uchar16 const
#define TgVEC1_U08_16_1_P               simd_packed_uchar16 *
#define TgVEC1_U08_16_1_PC              simd_packed_uchar16 * const
#define TgVEC1_U08_16_1_PCU             simd_packed_uchar16 * const __restrict
#define TgVEC1_U08_16_1_PU              simd_packed_uchar16 * __restrict
#define TgVEC1_U08_16_1_CP              simd_packed_uchar16 const *
#define TgVEC1_U08_16_1_CPU             simd_packed_uchar16 const * __restrict
#define TgVEC1_U08_16_1_CPC             simd_packed_uchar16 const * const
#define TgVEC1_U08_16_1_CPCU            simd_packed_uchar16 const * const __restrict
#define TgVEC1_U08_16_1_PP              simd_packed_uchar16 **
#define TgVEC1_U08_16_1_PPU             simd_packed_uchar16 ** __restrict
#define TgVEC1_U08_16_1_CPCPU           simd_packed_uchar16 const *const * __restrict
#define TgVEC1_U08_16_1_CPPU            simd_packed_uchar16 const ** __restrict
#define TgVEC1_U08_16_1_PPCU            simd_packed_uchar16 ** const __restrict
#define TgVEC1_U08_16_1                 simd_packed_uchar16

#define TgVEC1_U16_08_1_C               simd_packed_ushort8 const
#define TgVEC1_U16_08_1_P               simd_packed_ushort8 *
#define TgVEC1_U16_08_1_PC              simd_packed_ushort8 * const
#define TgVEC1_U16_08_1_PCU             simd_packed_ushort8 * const __restrict
#define TgVEC1_U16_08_1_PU              simd_packed_ushort8 * __restrict
#define TgVEC1_U16_08_1_CP              simd_packed_ushort8 const *
#define TgVEC1_U16_08_1_CPU             simd_packed_ushort8 const * __restrict
#define TgVEC1_U16_08_1_CPC             simd_packed_ushort8 const * const
#define TgVEC1_U16_08_1_CPCU            simd_packed_ushort8 const * const __restrict
#define TgVEC1_U16_08_1_PP              simd_packed_ushort8 **
#define TgVEC1_U16_08_1_PPU             simd_packed_ushort8 ** __restrict
#define TgVEC1_U16_08_1_CPCPU           simd_packed_ushort8 const *const * __restrict
#define TgVEC1_U16_08_1_CPPU            simd_packed_ushort8 const ** __restrict
#define TgVEC1_U16_08_1_PPCU            simd_packed_ushort8 ** const __restrict
#define TgVEC1_U16_08_1                 simd_packed_ushort8

#define TgVEC1_U32_04_1_C               simd_packed_uint4 const
#define TgVEC1_U32_04_1_P               simd_packed_uint4 *
#define TgVEC1_U32_04_1_PC              simd_packed_uint4 * const
#define TgVEC1_U32_04_1_PCU             simd_packed_uint4 * const __restrict
#define TgVEC1_U32_04_1_PU              simd_packed_uint4 * __restrict
#define TgVEC1_U32_04_1_CP              simd_packed_uint4 const *
#define TgVEC1_U32_04_1_CPU             simd_packed_uint4 const * __restrict
#define TgVEC1_U32_04_1_CPC             simd_packed_uint4 const * const
#define TgVEC1_U32_04_1_CPCU            simd_packed_uint4 const * const __restrict
#define TgVEC1_U32_04_1_PP              simd_packed_uint4 **
#define TgVEC1_U32_04_1_PPU             simd_packed_uint4 ** __restrict
#define TgVEC1_U32_04_1_CPCPU           simd_packed_uint4 const *const * __restrict
#define TgVEC1_U32_04_1_CPPU            simd_packed_uint4 const ** __restrict
#define TgVEC1_U32_04_1_PPCU            simd_packed_uint4 ** const __restrict
#define TgVEC1_U32_04_1                 simd_packed_uint4

#define TgVEC1_S08_16_1_C               simd_packed_char16 const
#define TgVEC1_S08_16_1_P               simd_packed_char16 *
#define TgVEC1_S08_16_1_PC              simd_packed_char16 * const
#define TgVEC1_S08_16_1_PCU             simd_packed_char16 * const __restrict
#define TgVEC1_S08_16_1_PU              simd_packed_char16 * __restrict
#define TgVEC1_S08_16_1_CP              simd_packed_char16 const *
#define TgVEC1_S08_16_1_CPU             simd_packed_char16 const * __restrict
#define TgVEC1_S08_16_1_CPC             simd_packed_char16 const * const
#define TgVEC1_S08_16_1_CPCU            simd_packed_char16 const * const __restrict
#define TgVEC1_S08_16_1_PP              simd_packed_char16 **
#define TgVEC1_S08_16_1_PPU             simd_packed_char16 ** __restrict
#define TgVEC1_S08_16_1_CPCPU           simd_packed_char16 const *const * __restrict
#define TgVEC1_S08_16_1_CPPU            simd_packed_char16 const ** __restrict
#define TgVEC1_S08_16_1_PPCU            simd_packed_char16 ** const __restrict
#define TgVEC1_S08_16_1                 simd_packed_char16

#define TgVEC1_S16_08_1_C               simd_packed_short8 const
#define TgVEC1_S16_08_1_P               simd_packed_short8 *
#define TgVEC1_S16_08_1_PC              simd_packed_short8 * const
#define TgVEC1_S16_08_1_PCU             simd_packed_short8 * const __restrict
#define TgVEC1_S16_08_1_PU              simd_packed_short8 * __restrict
#define TgVEC1_S16_08_1_CP              simd_packed_short8 const *
#define TgVEC1_S16_08_1_CPU             simd_packed_short8 const * __restrict
#define TgVEC1_S16_08_1_CPC             simd_packed_short8 const * const
#define TgVEC1_S16_08_1_CPCU            simd_packed_short8 const * const __restrict
#define TgVEC1_S16_08_1_PP              simd_packed_short8 **
#define TgVEC1_S16_08_1_PPU             simd_packed_short8 ** __restrict
#define TgVEC1_S16_08_1_CPCPU           simd_packed_short8 const *const * __restrict
#define TgVEC1_S16_08_1_CPPU            simd_packed_short8 const ** __restrict
#define TgVEC1_S16_08_1_PPCU            simd_packed_short8 ** const __restrict
#define TgVEC1_S16_08_1                 simd_packed_short8

#define TgVEC1_S32_04_1_C               simd_packed_int4 const
#define TgVEC1_S32_04_1_P               simd_packed_int4 *
#define TgVEC1_S32_04_1_PC              simd_packed_int4 * const
#define TgVEC1_S32_04_1_PCU             simd_packed_int4 * const __restrict
#define TgVEC1_S32_04_1_PU              simd_packed_int4 * __restrict
#define TgVEC1_S32_04_1_CP              simd_packed_int4 const *
#define TgVEC1_S32_04_1_CPU             simd_packed_int4 const * __restrict
#define TgVEC1_S32_04_1_CPC             simd_packed_int4 const * const
#define TgVEC1_S32_04_1_CPCU            simd_packed_int4 const * const __restrict
#define TgVEC1_S32_04_1_PP              simd_packed_int4 **
#define TgVEC1_S32_04_1_PPU             simd_packed_int4 ** __restrict
#define TgVEC1_S32_04_1_CPCPU           simd_packed_int4 const *const * __restrict
#define TgVEC1_S32_04_1_CPPU            simd_packed_int4 const ** __restrict
#define TgVEC1_S32_04_1_PPCU            simd_packed_int4 ** const __restrict
#define TgVEC1_S32_04_1                 simd_packed_int4

#define TgVEC1_F32_04_1_C               simd_packed_float4 const
#define TgVEC1_F32_04_1_P               simd_packed_float4 *
#define TgVEC1_F32_04_1_PC              simd_packed_float4 * const
#define TgVEC1_F32_04_1_PCU             simd_packed_float4 * const __restrict
#define TgVEC1_F32_04_1_PU              simd_packed_float4 * __restrict
#define TgVEC1_F32_04_1_CP              simd_packed_float4 const *
#define TgVEC1_F32_04_1_CPU             simd_packed_float4 const * __restrict
#define TgVEC1_F32_04_1_CPC             simd_packed_float4 const * const
#define TgVEC1_F32_04_1_CPCU            simd_packed_float4 const * const __restrict
#define TgVEC1_F32_04_1_PP              simd_packed_float4 **
#define TgVEC1_F32_04_1_PPU             simd_packed_float4 ** __restrict
#define TgVEC1_F32_04_1_CPCPU           simd_packed_float4 const *const * __restrict
#define TgVEC1_F32_04_1_CPPU            simd_packed_float4 const ** __restrict
#define TgVEC1_F32_04_1_PPCU            simd_packed_float4 ** const __restrict
#define TgVEC1_F32_04_1                 simd_packed_float4




#define TgVEC_F32_04_3_C                simd_float3x4 const
#define TgVEC_F32_04_3_P                simd_float3x4 *
#define TgVEC_F32_04_3_PC               simd_float3x4 * const
#define TgVEC_F32_04_3_PCU              simd_float3x4 * const __restrict
#define TgVEC_F32_04_3_PU               simd_float3x4 * __restrict
#define TgVEC_F32_04_3_CP               simd_float3x4 const *
#define TgVEC_F32_04_3_CPU              simd_float3x4 const * __restrict
#define TgVEC_F32_04_3_CPC              simd_float3x4 const * const
#define TgVEC_F32_04_3_CPCU             simd_float3x4 const * const __restrict
#define TgVEC_F32_04_3_PP               simd_float3x4 **
#define TgVEC_F32_04_3_PPU              simd_float3x4 ** __restrict
#define TgVEC_F32_04_3_CPCPU            simd_float3x4 const *const * __restrict
#define TgVEC_F32_04_3_CPPU             simd_float3x4 const ** __restrict
#define TgVEC_F32_04_3_PPCU             simd_float3x4 ** const __restrict
#define TgVEC_F32_04_3                  simd_float3x4

#define TgVEC_F32_04_4_C                simd_float4x4 const
#define TgVEC_F32_04_4_P                simd_float4x4 *
#define TgVEC_F32_04_4_PC               simd_float4x4 * const
#define TgVEC_F32_04_4_PCU              simd_float4x4 * const __restrict
#define TgVEC_F32_04_4_PU               simd_float4x4 * __restrict
#define TgVEC_F32_04_4_CP               simd_float4x4 const *
#define TgVEC_F32_04_4_CPU              simd_float4x4 const * __restrict
#define TgVEC_F32_04_4_CPC              simd_float4x4 const * const
#define TgVEC_F32_04_4_CPCU             simd_float4x4 const * const __restrict
#define TgVEC_F32_04_4_PP               simd_float4x4 **
#define TgVEC_F32_04_4_PPU              simd_float4x4 ** __restrict
#define TgVEC_F32_04_4_CPCPU            simd_float4x4 const *const * __restrict
#define TgVEC_F32_04_4_CPPU             simd_float4x4 const ** __restrict
#define TgVEC_F32_04_4_PPCU             simd_float4x4 ** const __restrict
#define TgVEC_F32_04_4                  simd_float4x4

/* =============================================================================================================================================================================== */
#endif
