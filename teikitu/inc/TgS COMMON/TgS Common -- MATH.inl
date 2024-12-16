/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common -- MATH.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_MATH_INL)
#define TGS_COMMON_MATH_INL
#pragma once

#if defined(TGS_COMMON_MATH_VECTOR_SPECIALIZATION)
    #if defined(TgBUILD_UNIVERSAL) && !defined (TGS_COMMON_MATH_API_VECTOR_SPECIALIZATION_INL)
        #include TgHEADER_UNIVERSAL(TgS COMMON/TgS,Common - Math [Vector].inl)
    #endif
    #if defined(TgBUILD_HARDWARE) && !defined(TgBUILD_HARDWARE__C11) && !defined (TGS_COMMON_MATH_API_VECTOR_SPECIALIZATION_INL)
        #include TgHEADER_HARDWARE(TgS COMMON/TgS,Common - Math [Vector].inl)
    #endif
    #if defined(TgBUILD_COMPILER) && !defined (TGS_COMMON_MATH_API_VECTOR_SPECIALIZATION_INL)
        #include TgHEADER_COMPILER(TgS COMMON/TgS,Common - Math [Vector].inl)
    #endif
#endif

#include "TgS COMMON/TgS Common - Math [Vector] [API].inl"


#if defined(TGS_COMMON_MATH_VECTOR_SPECIALIZATION)
    #if defined(TgBUILD_UNIVERSAL) && !defined (TGS_COMMON_MATH_API_MATRIX_SPECIALIZATION_INL)
        #include TgHEADER_UNIVERSAL(TgS COMMON/TgS,Common - Math [Matrix].inl)
    #endif
    #if defined(TgBUILD_HARDWARE) && !defined(TgBUILD_HARDWARE__C11) && !defined (TGS_COMMON_MATH_API_MATRIX_SPECIALIZATION_INL)
        #include TgHEADER_HARDWARE(TgS COMMON/TgS,Common - Math [Matrix].inl)
    #endif
    #if defined(TgBUILD_COMPILER) && !defined (TGS_COMMON_MATH_API_MATRIX_SPECIALIZATION_INL)
        #include TgHEADER_COMPILER(TgS COMMON/TgS,Common - Math [Matrix].inl)
    #endif
#endif

#include "TgS COMMON/TgS Common - Math [Matrix] [API].inl"


/* =============================================================================================================================================================================== */
#endif
