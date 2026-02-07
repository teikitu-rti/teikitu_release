/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Math [Vector].h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_MATH_VECTOR_H)

#if !defined (TEMPLATE_TYPE_EXPANSION__RELOAD)
    #error Must be included as part of a type expansion include chain
#endif


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @addtogroup TGS_COMMON_MATH_VECTOR_LOAD
    @brief Return a vector with the data at the unaligned location at ARG
    @param [in] ARG Pointer to a possibly unaligned region of memory holding enough data to completely initialize a new vector
    @return A vector initialized from the data at ARG*/
TgINLINE VEC_T(1)
FCN_V(tgMH_SETU)(
    VAR_T(CPC) TgANALYSIS_NO_NULL ARG );

/** @addtogroup TGS_COMMON_MATH_VECTOR_LOAD
    @brief Return a vector with the data at the aligned location at ARG
    @param [in] ARG Pointer to an aligned region of memory holding enough data to completely initialize a new vector
    @return A vector initialized from the data at ARG*/
TgINLINE VEC_T(1)
FCN_V(tgMH_SETA)(
    VAR_T(CPC) TgANALYSIS_NO_NULL ARG );

/** @addtogroup TGS_COMMON_MATH_VECTOR_LOAD
    @brief Return a vector where each element is assigned the same value as ARG
    @param [in] ARG Scalar value
    @return A vector where each element is assigned the same value as ARG */
TgINLINE VEC_T(1)
FCN_V(tgMH_SET1)(
    VAR_T(C) ARG );

/** @addtogroup TGS_COMMON_MATH_VECTOR_LOAD
    @brief Return a vector where each element is assigned a random value
    @return A vector where each element is assigned a random value */
TgINLINE VEC_T(1)
FCN_V(tgMH_RAND)( TgVOID );




/** @addtogroup TGS_COMMON_MATH_VECTOR_ART
    @brief Return a vector that is assigned the per-element operation ARG0 + ARG1, wrapping on overflow
    @param [in] ARG0 Vector
    @param [in] ARG1 Vector
    @return A vector where each element is the corresponding sum from the arguments, wrapping on overflow */
TgINLINE VEC_T(1)
FCN_V(tgMH_ADD)(
    VEC_T(1,C) ARG0, VEC_T(1,C) ARG1 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_ART
    @brief Return a vector that is assigned the per-element operation ARG0 - ARG1, wrapping on underflow
    @param [in] ARG0 Vector
    @param [in] ARG1 Vector
    @return A vector where each element is the corresponding sum from the arguments, wrapping on underflow */
TgINLINE VEC_T(1)
FCN_V(tgMH_SUB)(
    VEC_T(1,C) ARG0, VEC_T(1,C) ARG1 );

#if !defined(TEMPLATE__ENABLE_INTEGER) || !defined(TEMPLATE__ENABLE_UNSIGNED)

/** @addtogroup TGS_COMMON_MATH_VECTOR_CALC
    @brief Return a vector that is the negative of the argument
    @param [in] ARG0 Vector
    @return A vector that is the negative of the argument */
TgINLINE VEC_T(1)
FCN_V(tgMH_NEG)(
    VEC_T(1,C) ARG );

/*# !defined(TEMPLATE__ENABLE_INTEGER) || !defined(TEMPLATE__ENABLE_UNSIGNED) */
#endif

/** @addtogroup TGS_COMMON_MATH_VECTOR_ART
    @brief Return a vector where each element is the corresponding average of the arguments
    @param [in] ARG0 Vector
    @param [in] ARG1 Vector
    @return A vector where each element is the corresponding average of the arguments */
TgINLINE VEC_T(1)
FCN_V(tgMH_AVG)(
    VEC_T(1,C) ARG0, VEC_T(1,C) ARG1 );




/** @addtogroup TGS_COMMON_MATH_VECTOR_PERM
    @brief Return the result of a bit-wise select where 0 selects the bit from ARG0 and the bit from ARG1 otherwise
    @param [in] ARG0 Vector
    @param [in] ARG1 Vector
    @param [in] ARG1 Vector, Mask
    @return A bit-wise select where 0 selects the bit from ARG0 and the bit from ARG1 otherwise */
TgINLINE VEC_T(1)
FCN_V(tgMH_SEL)(
    VEC_T(1,C) ARG0, VEC_T(1,C) ARG1, VEC_T(1,C) ARG2 );




/** @addtogroup TGS_COMMON_MATH_VECTOR_LOGICAL
    @brief Return the result of a bit-wise and between both arguments
    @param [in] ARG0 Vector
    @param [in] ARG1 Vector
    @return A result of a bit-wise and between both arguments */
TgINLINE VEC_T(1)
FCN_V(tgMH_AND)(
    VEC_T(1,C) ARG0, VEC_T(1,C) ARG1 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_LOGICAL
    @brief Return the result of a bit-wise or between both arguments
    @param [in] ARG0 Vector
    @param [in] ARG1 Vector
    @return A result of a bit-wise or between both arguments */
TgINLINE VEC_T(1)
FCN_V(tgMH_OR)(
    VEC_T(1,C) ARG0, VEC_T(1,C) ARG1 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_LOGICAL
    @brief Return the result of a bit-wise xor between both arguments
    @param [in] ARG0 Vector
    @param [in] ARG1 Vector
    @return A result of a bit-wise xor between both arguments */
TgINLINE VEC_T(1)
FCN_V(tgMH_XOR)(
    VEC_T(1,C) ARG0, VEC_T(1,C) ARG1 );




/** @addtogroup TGS_COMMON_MATH_VECTOR_BOUNDS
    @brief Return a vector where each element is the maximum of the corresponding elements in the argument vectors
    @param [in] ARG0 Vector
    @param [in] ARG1 Vector
    @return A vector where each element is the maximum of the corresponding elements in the argument vectors */
TgINLINE VEC_T(1)
FCN_V(tgMH_MAX)(
    VEC_T(1,C) ARG0, VEC_T(1,C) ARG1 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_BOUNDS
    @brief Return a vector where each element is the maximum of the corresponding elements in the argument vectors
    @param [in] ARG0 Vector
    @return A vector where each element is the maximum of the corresponding elements in the argument vectors */
TgINLINE VAR_T()
FCN_V(tgMH_MAX_ELEM)(
    VEC_T(1,C) ARG0 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_BOUNDS
    @brief Return a vector where each element is the minimum of the corresponding elements in the argument vectors
    @param [in] ARG0 Vector
    @param [in] ARG1 Vector
    @return A vector where each element is the minimum of the corresponding elements in the argument vectors */
TgINLINE VEC_T(1)
FCN_V(tgMH_MIN)(
    VEC_T(1,C) ARG0, VEC_T(1,C) ARG1 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_BOUNDS
    @brief Return a vector where each element is the minimum of the corresponding elements in the argument vectors
    @param [in] ARG0 Vector
    @return A vector where each element is the minimum of the corresponding elements in the argument vectors */
TgINLINE VAR_T()
FCN_V(tgMH_MIN_ELEM)(
    VEC_T(1,C) ARG0 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_BOUNDS
    @brief Return a new vector whose elements are the absolute value of the argument elements
    @param [in] ARG Vector
    @return A new vector whose elements are the absolute value of the argument elements */
TgINLINE VEC_T(1)
FCN_V(tgMH_ABS)(
    VEC_T(1,C) ARG );

/** @addtogroup TGS_COMMON_MATH_VECTOR_BOUNDS
    @brief Return a new vector whose element value are (-1,0,+1) based on the sign of the argument elements
    @param [in] ARG Vector
    @return A new vector whose element value are (-1,0,+1) based on the sign of the argument elements */
TgINLINE VEC_T(1)
FCN_V(tgMH_SGN)(
    VEC_T(1,C) ARG );




/** @addtogroup TGS_COMMON_MATH_VECTOR_CMP
    @brief Return a vector encoding the result of ARG0 equal to ARG1, where a set bit is true, and false otherwise
    @param [in] ARG0 Vector
    @param [in] ARG1 Vector
    @return A vector encoding the result of ARG0 equal to ARG1, where a set bit is true, and false otherwise */
TgINLINE VEC_T(1)
FCN_V(tgMH_CMP_EQ)(
    VEC_T(1,C) ARG0, VEC_T(1,C) ARG1 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_CMP
    @brief Return a vector encoding the result of ARG0 not equal to ARG1, where a set bit is true, and false otherwise
    @param [in] ARG0 Vector
    @param [in] ARG1 Vector
    @return A vector encoding the result of ARG0 not equal to ARG1, where a set bit is true, and false otherwise */
TgINLINE VEC_T(1)
FCN_V(tgMH_CMP_VE)(
    VEC_T(1,C) ARG0, VEC_T(1,C) ARG1 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_CMP
    @brief Return a vector encoding the result of ARG0 greater than or equal to ARG1, where a set bit is true, and false otherwise
    @param [in] ARG0 Vector
    @param [in] ARG1 Vector
    @return A vector encoding the result of ARG0 greater than or equal to ARG1, where a set bit is true, and false otherwise */
TgINLINE VEC_T(1)
FCN_V(tgMH_CMP_GE)(
    VEC_T(1,C) ARG0, VEC_T(1,C) ARG1 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_CMP
    @brief Return a vector encoding the result of ARG0 greater than ARG1, where a set bit is true, and false otherwise
    @param [in] ARG0 Vector
    @param [in] ARG1 Vector
    @return A vector encoding the result of ARG0 greater than ARG1, where a set bit is true, and false otherwise */
TgINLINE VEC_T(1)
FCN_V(tgMH_CMP_GT)(
    VEC_T(1,C) ARG0, VEC_T(1,C) ARG1 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_CMP
    @brief Return a vector encoding the result of ARG0 less than or equal to ARG1, where a set bit is true, and false otherwise
    @param [in] ARG0 Vector
    @param [in] ARG1 Vector
    @return A vector encoding the result of ARG0 less than or equal to ARG1, where a set bit is true, and false otherwise */
TgINLINE VEC_T(1)
FCN_V(tgMH_CMP_LE)(
    VEC_T(1,C) ARG0, VEC_T(1,C) ARG1 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_CMP
    @brief Return a vector encoding the result of ARG0 less than ARG1, where a set bit is true, and false otherwise
    @param [in] ARG0 Vector
    @param [in] ARG1 Vector
    @return A vector encoding the result of ARG0 less than ARG1, where a set bit is true, and false otherwise */
TgINLINE VEC_T(1)
FCN_V(tgMH_CMP_LT)(
    VEC_T(1,C) ARG0, VEC_T(1,C) ARG1 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_CMP
    @brief Return true if all lanes in the vector are set and false otherwise
    @param [in] ARG Vector
    @return A true if all lanes in the vector are set and false otherwise */
TgINLINE TgBOOL
FCN_V(tgMH_CMP_ALL_TO_BOOL)(
    VEC_T(1,C) ARG );

/** @addtogroup TGS_COMMON_MATH_VECTOR_CMP
    @brief Return true if all lanes in the vector are set and false otherwise
    @param [in] ARG Vector
    @return A true if all lanes in the vector are set and false otherwise */
TgINLINE TgBOOL
FCN_V(tgMH_CMP_ANY_TO_BOOL)(
    VEC_T(1,C) ARG );


/* =============================================================================================================================================================================== */
#endif
