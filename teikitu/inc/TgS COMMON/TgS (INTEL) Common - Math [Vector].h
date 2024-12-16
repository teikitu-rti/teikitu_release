/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (INTEL) Common - Math [Vector].h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_INTEL_COMMON_MATH_VECTOR_H)
#define TGS_INTEL_COMMON_MATH_VECTOR_H
#pragma once

#ifdef TGS_COMMON_MATH_VECTOR_SPECIALIZATION
    #error "Previous Math Specialization Already Exists"
#endif

#define TGS_COMMON_MATH_VECTOR_SPECIALIZATION


/* == Common ===================================================================================================================================================================== */
/* MARK: No Unit Test Required                                                                                                                                                     */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Types                                                                                                                                                                   */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#define TgVEC_U08_16_1_C                __m128i const
#define TgVEC_U08_16_1_P                __m128i *
#define TgVEC_U08_16_1_PC               __m128i * const
#define TgVEC_U08_16_1_PCU              __m128i * const __restrict
#define TgVEC_U08_16_1_PU               __m128i * __restrict
#define TgVEC_U08_16_1_CP               __m128i const *
#define TgVEC_U08_16_1_CPU              __m128i const * __restrict
#define TgVEC_U08_16_1_CPC              __m128i const * const
#define TgVEC_U08_16_1_CPCU             __m128i const * const __restrict
#define TgVEC_U08_16_1_PP               __m128i**
#define TgVEC_U08_16_1_PPU              __m128i ** __restrict
#define TgVEC_U08_16_1_CPCPU            __m128i const *const * __restrict
#define TgVEC_U08_16_1_CPPU             __m128i const ** __restrict
#define TgVEC_U08_16_1_PPCU             __m128i ** const __restrict
#define TgVEC_U08_16_1                  __m128i

#define TgVEC_U16_08_1_C                __m128i const
#define TgVEC_U16_08_1_P                __m128i *
#define TgVEC_U16_08_1_PC               __m128i * const
#define TgVEC_U16_08_1_PCU              __m128i * const __restrict
#define TgVEC_U16_08_1_PU               __m128i * __restrict
#define TgVEC_U16_08_1_CP               __m128i const *
#define TgVEC_U16_08_1_CPU              __m128i const * __restrict
#define TgVEC_U16_08_1_CPC              __m128i const * const
#define TgVEC_U16_08_1_CPCU             __m128i const * const __restrict
#define TgVEC_U16_08_1_PP               __m128i**
#define TgVEC_U16_08_1_PPU              __m128i ** __restrict
#define TgVEC_U16_08_1_CPCPU            __m128i const *const * __restrict
#define TgVEC_U16_08_1_CPPU             __m128i const ** __restrict
#define TgVEC_U16_08_1_PPCU             __m128i ** const __restrict
#define TgVEC_U16_08_1                  __m128i

#define TgVEC_U32_04_1_C                __m128i const
#define TgVEC_U32_04_1_P                __m128i *
#define TgVEC_U32_04_1_PC               __m128i * const
#define TgVEC_U32_04_1_PCU              __m128i * const __restrict
#define TgVEC_U32_04_1_PU               __m128i * __restrict
#define TgVEC_U32_04_1_CP               __m128i const *
#define TgVEC_U32_04_1_CPU              __m128i const * __restrict
#define TgVEC_U32_04_1_CPC              __m128i const * const
#define TgVEC_U32_04_1_CPCU             __m128i const * const __restrict
#define TgVEC_U32_04_1_PP               __m128i**
#define TgVEC_U32_04_1_PPU              __m128i ** __restrict
#define TgVEC_U32_04_1_CPCPU            __m128i const *const * __restrict
#define TgVEC_U32_04_1_CPPU             __m128i const ** __restrict
#define TgVEC_U32_04_1_PPCU             __m128i ** const __restrict
#define TgVEC_U32_04_1                  __m128i

#define TgVEC_S08_16_1_C                __m128i const
#define TgVEC_S08_16_1_P                __m128i *
#define TgVEC_S08_16_1_PC               __m128i * const
#define TgVEC_S08_16_1_PCU              __m128i * const __restrict
#define TgVEC_S08_16_1_PU               __m128i * __restrict
#define TgVEC_S08_16_1_CP               __m128i const *
#define TgVEC_S08_16_1_CPU              __m128i const * __restrict
#define TgVEC_S08_16_1_CPC              __m128i const * const
#define TgVEC_S08_16_1_CPCU             __m128i const * const __restrict
#define TgVEC_S08_16_1_PP               __m128i**
#define TgVEC_S08_16_1_PPU              __m128i ** __restrict
#define TgVEC_S08_16_1_CPCPU            __m128i const *const * __restrict
#define TgVEC_S08_16_1_CPPU             __m128i const ** __restrict
#define TgVEC_S08_16_1_PPCU             __m128i ** const __restrict
#define TgVEC_S08_16_1                  __m128i

#define TgVEC_S16_08_1_C                __m128i const
#define TgVEC_S16_08_1_P                __m128i *
#define TgVEC_S16_08_1_PC               __m128i * const
#define TgVEC_S16_08_1_PCU              __m128i * const __restrict
#define TgVEC_S16_08_1_PU               __m128i * __restrict
#define TgVEC_S16_08_1_CP               __m128i const *
#define TgVEC_S16_08_1_CPU              __m128i const * __restrict
#define TgVEC_S16_08_1_CPC              __m128i const * const
#define TgVEC_S16_08_1_CPCU             __m128i const * const __restrict
#define TgVEC_S16_08_1_PP               __m128i**
#define TgVEC_S16_08_1_PPU              __m128i ** __restrict
#define TgVEC_S16_08_1_CPCPU            __m128i const *const * __restrict
#define TgVEC_S16_08_1_CPPU             __m128i const ** __restrict
#define TgVEC_S16_08_1_PPCU             __m128i ** const __restrict
#define TgVEC_S16_08_1                  __m128i

#define TgVEC_S32_04_1_C                __m128i const
#define TgVEC_S32_04_1_P                __m128i *
#define TgVEC_S32_04_1_PC               __m128i * const
#define TgVEC_S32_04_1_PCU              __m128i * const __restrict
#define TgVEC_S32_04_1_PU               __m128i * __restrict
#define TgVEC_S32_04_1_CP               __m128i const *
#define TgVEC_S32_04_1_CPU              __m128i const * __restrict
#define TgVEC_S32_04_1_CPC              __m128i const * const
#define TgVEC_S32_04_1_CPCU             __m128i const * const __restrict
#define TgVEC_S32_04_1_PP               __m128i**
#define TgVEC_S32_04_1_PPU              __m128i ** __restrict
#define TgVEC_S32_04_1_CPCPU            __m128i const *const * __restrict
#define TgVEC_S32_04_1_CPPU             __m128i const ** __restrict
#define TgVEC_S32_04_1_PPCU             __m128i ** const __restrict
#define TgVEC_S32_04_1                  __m128i

#define TgVEC_F32_04_1_C                __m128 const
#define TgVEC_F32_04_1_P                __m128 *
#define TgVEC_F32_04_1_PC               __m128 * const
#define TgVEC_F32_04_1_PCU              __m128 * const __restrict
#define TgVEC_F32_04_1_PU               __m128 * __restrict
#define TgVEC_F32_04_1_CP               __m128 const *
#define TgVEC_F32_04_1_CPU              __m128 const * __restrict
#define TgVEC_F32_04_1_CPC              __m128 const * const
#define TgVEC_F32_04_1_CPCU             __m128 const * const __restrict
#define TgVEC_F32_04_1_PP               __m128**
#define TgVEC_F32_04_1_PPU              __m128 ** __restrict
#define TgVEC_F32_04_1_CPCPU            __m128 const *const * __restrict
#define TgVEC_F32_04_1_CPPU             __m128 const ** __restrict
#define TgVEC_F32_04_1_PPCU             __m128 ** const __restrict
#define TgVEC_F32_04_1                  __m128


/* =============================================================================================================================================================================== */
#endif
