/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (CLANG) Common - Math [Vector].h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_CLANG_COMMON_MATH_VECTOR_H)
#define TGS_CLANG_COMMON_MATH_VECTOR_H
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

typedef __attribute__((__ext_vector_type__(16))) uint8_t TgVEC_U08_16_1;
TgTYPE_MODIFIER_ALL(TgVEC_U08_16_1);
typedef __attribute__((__ext_vector_type__(16),__aligned__(1))) uint8_t TgVEC_N1_U08_16_1;
TgTYPE_MODIFIER_ALL(TgVEC_N1_U08_16_1);

typedef __attribute__((__ext_vector_type__(8))) uint16_t TgVEC_U16_08_1;
TgTYPE_MODIFIER_ALL(TgVEC_U16_08_1);
typedef __attribute__((__ext_vector_type__(8),__aligned__(1))) uint16_t TgVEC_N1_U16_08_1;
TgTYPE_MODIFIER_ALL(TgVEC_N1_U16_08_1);

typedef __attribute__((__ext_vector_type__(4))) uint32_t TgVEC_U32_04_1;
TgTYPE_MODIFIER_ALL(TgVEC_U32_04_1);
typedef __attribute__((__ext_vector_type__(4),__aligned__(1))) uint32_t TgVEC_N1_U32_04_1;
TgTYPE_MODIFIER_ALL(TgVEC_N1_U32_04_1);

typedef __attribute__((__ext_vector_type__(16))) int8_t TgVEC_S08_16_1;
TgTYPE_MODIFIER_ALL(TgVEC_S08_16_1);
typedef __attribute__((__ext_vector_type__(16),__aligned__(1))) int8_t TgVEC_N1_S08_16_1;
TgTYPE_MODIFIER_ALL(TgVEC_N1_S08_16_1);

typedef __attribute__((__ext_vector_type__(8))) int16_t TgVEC_S16_08_1;
TgTYPE_MODIFIER_ALL(TgVEC_S16_08_1);
typedef __attribute__((__ext_vector_type__(8),__aligned__(1))) int16_t TgVEC_N1_S16_08_1;
TgTYPE_MODIFIER_ALL(TgVEC_N1_S16_08_1);

typedef __attribute__((__ext_vector_type__(4))) int32_t TgVEC_S32_04_1;
TgTYPE_MODIFIER_ALL(TgVEC_S32_04_1);
typedef __attribute__((__ext_vector_type__(4),__aligned__(1))) int32_t TgVEC_N1_S32_04_1;
TgTYPE_MODIFIER_ALL(TgVEC_N1_S32_04_1);

typedef __attribute__((__ext_vector_type__(4))) float TgVEC_F32_04_1;
TgTYPE_MODIFIER_ALL(TgVEC_F32_04_1);
typedef __attribute__((__ext_vector_type__(4),__aligned__(1))) float TgVEC_N1_F32_04_1;
TgTYPE_MODIFIER_ALL(TgVEC_N1_F32_04_1);


/* =============================================================================================================================================================================== */
#endif
