/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Base - Type [Vector].h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_BASE_TYPE_VECTOR_H)
#define TGS_COMMON_BASE_TYPE_VECTOR_H
#pragma once

#if defined(TgBUILD_UNIVERSAL) && !defined (TGS_COMMON_MATH_VECTOR_SPECIALIZATION)
    #include TgHEADER_UNIVERSAL(TgS COMMON/TgS,Common - Math [Vector].h)
#endif
#if defined(TgBUILD_HARDWARE) && !defined(TgBUILD_HARDWARE__C17_A64) && !defined(TgBUILD_HARDWARE__C17_X64) && !defined (TGS_COMMON_MATH_VECTOR_SPECIALIZATION)
    #include TgHEADER_HARDWARE(TgS COMMON/TgS,Common - Math [Vector].h)
#endif
#if defined(TgBUILD_COMPILER) && defined(TgBUILD_VECTOR__COMPILER) && !defined (TGS_COMMON_MATH_VECTOR_SPECIALIZATION)
    #include TgHEADER_COMPILER(TgS COMMON/TgS,Common - Math [Vector].h)
#endif


/* == Common ===================================================================================================================================================================== */
/* MARK: No Unit Test Required                                                                                                                                                     */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Types                                                                                                                                                                   */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#define TEMPLATE__ENABLE_INTEGER

#define TEMPLATE__TEST_AND_UNLOAD_TEMPLATE_MACROS
#define TEMPLATE__TYPE_SIZE 8
#define TEMPLATE__VECTOR_DIM 16
#include "TgS COMMON/TgS Common - Base - Type [Template] [Vector].h"

#define TEMPLATE__TYPE_SIZE 16
#define TEMPLATE__VECTOR_DIM 8
#include "TgS COMMON/TgS Common - Base - Type [Template] [Vector].h"

#define TEMPLATE__TYPE_SIZE 32
#define TEMPLATE__VECTOR_DIM 4
#include "TgS COMMON/TgS Common - Base - Type [Template] [Vector].h"

#define TEMPLATE__TYPE_SIZE 8
#define TEMPLATE__VECTOR_DIM 4
#include "TgS COMMON/TgS Common - Base - Type [Template] [Vector].h"

#define TEMPLATE__TYPE_SIZE 16
#define TEMPLATE__VECTOR_DIM 2
#include "TgS COMMON/TgS Common - Base - Type [Template] [Vector].h"

#define TEMPLATE__TYPE_SIZE 64
#define TEMPLATE__VECTOR_DIM 4
#include "TgS COMMON/TgS Common - Base - Type [Template] [Vector].h"

#undef TEMPLATE__ENABLE_INTEGER

#define TEMPLATE__VECTOR_DIM 2
#include "TgS COMMON/TgS Common - Base - Type [Template] [Vector].h"

#define TEMPLATE__VECTOR_DIM 3
#include "TgS COMMON/TgS Common - Base - Type [Template] [Vector].h"

#define TEMPLATE__VECTOR_DIM 4
#include "TgS COMMON/TgS Common - Base - Type [Template] [Vector].h"

#define TGS_COMMON_BASE_TYPE_VECTOR_HINC


/* NOTE: From a memory alignment point of view, it is reasonable to cast a native vector down to a scalar vector, but not the other way around. */
TgTYPE_UNION(TgUN_V128,)
{
    TgVEC_F32_04_1                              m_vF32_04_1;
    TgVEC_U32_04_1                              m_vU32_04_1;
    TgVEC_U16_08_1                              m_vU16_08_1;
    TgVEC_U08_16_1                              m_vU08_16_1;
    TgVEC_S32_04_1                              m_vS32_04_1;
    TgVEC_S16_08_1                              m_vS16_08_1;
    TgVEC_S08_16_1                              m_vS08_16_1;

    TgVEC_S_F32_04_1                            m_vS_F32_04_1;
    TgVEC_S_U32_04_1                            m_vS_U32_04_1;
    TgVEC_S_U16_08_1                            m_vS_U16_08_1;
    TgVEC_S_U08_16_1                            m_vS_U08_16_1;
    TgVEC_S_S32_04_1                            m_vS_S32_04_1;
    TgVEC_S_S16_08_1                            m_vS_S16_08_1;
    TgVEC_S_S08_16_1                            m_vS_S08_16_1;
};
TgCOMPILER_ASSERT(16 == sizeof(TgUN_V128),);

TgTYPE_UNION(TgUN_PTR_V128,)
{
    TgVEC_F32_04_1_P                            m_pvF32_04_1;
    TgVEC_U32_04_1_P                            m_pvU32_04_1;
    TgVEC_U16_08_1_P                            m_pvU16_08_1;
    TgVEC_U08_16_1_P                            m_pvU08_16_1;
    TgVEC_S32_04_1_P                            m_pvS32_04_1;
    TgVEC_S16_08_1_P                            m_pvS16_08_1;
    TgVEC_S08_16_1_P                            m_pvS08_16_1;

    TgVEC_F32_04_3_P                            m_pvF32_04_3;
    TgVEC_F32_04_4_P                            m_pvF32_04_4;

    TgVEC_S_F32_04_1_P                          m_pvS_F32_04_1;
    TgVEC_S_U32_04_1_P                          m_pvS_U32_04_1;
    TgVEC_S_U16_08_1_P                          m_pvS_U16_08_1;
    TgVEC_S_U08_16_1_P                          m_pvS_U08_16_1;
    TgVEC_S_S32_04_1_P                          m_pvS_S32_04_1;
    TgVEC_S_S16_08_1_P                          m_pvS_S16_08_1;
    TgVEC_S_S08_16_1_P                          m_pvS_S08_16_1;

    TgVEC_S_F32_04_3_P                          m_pvS_F32_04_3;
    TgVEC_S_F32_04_4_P                          m_pvS_F32_04_4;
};

TgTYPE_UNION(TgUN_CONST_PTR_V128,)
{
    TgVEC_F32_04_1_CP                           m_pvF32_04_1;
    TgVEC_U32_04_1_CP                           m_pvU32_04_1;
    TgVEC_U16_08_1_CP                           m_pvU16_08_1;
    TgVEC_U08_16_1_CP                           m_pvU08_16_1;
    TgVEC_S32_04_1_CP                           m_pvS32_04_1;
    TgVEC_S16_08_1_CP                           m_pvS16_08_1;
    TgVEC_S08_16_1_CP                           m_pvS08_16_1;

    TgVEC_F32_04_3_CP                           m_pvF32_04_3;
    TgVEC_F32_04_4_CP                           m_pvF32_04_4;

    TgVEC_S_F32_04_1_CP                         m_pvS_F32_04_1;
    TgVEC_S_U32_04_1_CP                         m_pvS_U32_04_1;
    TgVEC_S_U16_08_1_CP                         m_pvS_U16_08_1;
    TgVEC_S_U08_16_1_CP                         m_pvS_U08_16_1;
    TgVEC_S_S32_04_1_CP                         m_pvS_S32_04_1;
    TgVEC_S_S16_08_1_CP                         m_pvS_S16_08_1;
    TgVEC_S_S08_16_1_CP                         m_pvS_S08_16_1;

    TgVEC_S_F32_04_3_CP                         m_pvS_F32_04_3;
    TgVEC_S_F32_04_4_CP                         m_pvS_F32_04_4;
};


/* =============================================================================================================================================================================== */
#endif
