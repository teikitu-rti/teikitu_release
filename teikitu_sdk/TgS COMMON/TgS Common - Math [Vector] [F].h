/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Math API [Vector] [F].h_inc
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_MATH_API_VECTOR_F_H)

#if !defined (TEMPLATE_TYPE_EXPANSION__RELOAD)
    #error Must be included as part of a type expansion include chain
#endif


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  DOXYGEN                                                                                                                                                                        */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @defgroup TGS_COMMON_MATH_VECTOR_CALC SIMD - Calculations
    @ingroup TGS_COMMON_MATH_VECTOR_API
*/


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @addtogroup TGS_COMMON_MATH_VECTOR_CALC
    @brief Return true if the argument is a valid vector and false otherwise
    @param [in] ARG Vector*/
/** @return True if the argument is a vector and false otherwise */
TgINLINE TgBOOL
FCN_V(tgMH_Is_Valid)(
    VEC_T(1,C) ARG );

/** @addtogroup TGS_COMMON_MATH_VECTOR_CALC
    @brief Return true if the argument vector has the same non-negative value broadcast across all lanes, and false otherwise
    @param [in] ARG Vector*/
/** @return True if the argument vector has the same non-negative value broadcast across all lanes, and false otherwise */
TgINLINE TgBOOL
FCN_V(tgMH_Is_Valid_Broadcast_Non_Negative_Scalar)(
    VEC_T(1,C) ARG );

/** @addtogroup TGS_COMMON_MATH_VECTOR_CALC
    @brief Return true if the argument vector has the same positive value broadcast across all lanes, and false otherwise
    @param [in] ARG Vector*/
/** @return True if the argument vector has the same positive value broadcast across all lanes, and false otherwise */
TgINLINE TgBOOL
FCN_V(tgMH_Is_Valid_Broadcast_Positive_Scalar)(
    VEC_T(1,C) ARG );

/** @addtogroup TGS_COMMON_MATH_VECTOR_CALC
    @brief Return true if the argument vector has the same value broadcast across all lanes, and false otherwise
    @param [in] ARG Vector*/
/** @return True if the argument vector has the same value broadcast across all lanes, and false otherwise */
TgINLINE TgBOOL
FCN_V(tgMH_Is_Valid_Broadcast_Scalar)(
    VEC_T(1,C) ARG );

/** @addtogroup TGS_COMMON_MATH_VECTOR_BOUNDS
    @brief Return a new vector whose element value is set if the argument element is NAN and zero otherwise
    @param [in] ARG0 Vector
    @param [in] ARG1 Vector for the minimum range
    @param [in] ARG2 Vector for the maximum range
    @return True if the input vector is within the closed interval of [ARG1, ARG2] */
TgINLINE TgBOOL
FCN_V(tgMH_Is_Contained_In_Interval)(
    VEC_T(1,C) ARG0, VEC_T(1,C) ARG1, VEC_T(1,C) ARG2 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_BOUNDS
    @brief Return a new vector whose element value is set if the argument element is NAN and zero otherwise
    @param [in] ARG0 Vector
    @param [in] ARG1 Vector for the range
    @return True if the input vector is within the closed interval of [-ARG1, ARG1] */
TgINLINE TgBOOL
FCN_V(tgMH_Is_BND)(
    VEC_T(1,C) ARG0, VEC_T(1,C) ARG1 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_CMP
    @brief Return true if the two arguments are approximately the same vector, and false otherwise
    @param [in] ARG0 Vector
    @param [in] ARG1 Vector
    @return True if the two arguments are approximately the same vector, and false otherwise */
TgINLINE TgBOOL
FCN_V(tgMH_Is_PRX_CMP_EQ)(
    VEC_T(1,C) ARG0, VEC_T(1,C) ARG1 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_CMP
    @brief Return true if all lanes of the argument are near zero, and false otherwise
    @param [in] ARG0 Vector
    @return True if all lanes of the argument are near zero, and false otherwise */
TgINLINE TgBOOL
FCN_V(tgMH_Is_NR0)(
    VEC_T(1,C) ARG0 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_CMP
    @brief Return true if all lanes of the argument are near one, and false otherwise
    @param [in] ARG0 Vector
    @return True if all lanes of the argument are near one, and false otherwise */
TgINLINE TgBOOL
FCN_V(tgMH_Is_NR1)(
    VEC_T(1,C) ARG0 );




/** @addtogroup TGS_COMMON_MATH_VECTOR_ART
    @brief Return a vector that is assigned the per-element operation ARG0 * ARG1 + ARG2
    @param [in] ARG0 Vector
    @param [in] ARG1 Vector
    @param [in] ARG2 Vector
    @return A vector that is assigned the per-element operation ARG0 * ARG1 + ARG2 */
TgINLINE VEC_T(1)
FCN_V(tgMH_MAD)(
    VEC_T(1,C) ARG0, VEC_T(1,C) ARG1, VEC_T(1,C) ARG2 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_ART
    @brief Return a vector that is assigned the per-element operation ARG2 - (ARG0 * ARG1) == -((ARG0 * ARG1) - ARG2)
    @param [in] ARG0 Vector
    @param [in] ARG1 Vector
    @param [in] ARG2 Vector
    @return A vector that is assigned the per-element operation ARG2 - (ARG0 * ARG1) */
TgINLINE VEC_T(1)
FCN_V(tgMH_NMS)(
    VEC_T(1,C) ARG0, VEC_T(1,C) ARG1, VEC_T(1,C) ARG2 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_ART
    @brief Return a vector where each element contains the result of the dot product between the two vectors
    @param [in] ARG0 Vector
    @param [in] ARG1 Vector
    @return A vector where each element contains the result of the dot product between the two vectors */
TgINLINE VEC_T(1)
FCN_V(tgMH_DOT)(
    VEC_T(1,C) ARG0, VEC_T(1,C) ARG1 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_ART
    @brief Return a vector that is assigned the per-element operation ARG0 * ARG1
    @param [in] ARG0 Vector
    @param [in] ARG1 Vector
    @return A vector that is assigned the per-element operation ARG0 * ARG1 */
TgINLINE VEC_T(1)
FCN_V(tgMH_MUL)(
    VEC_T(1,C) ARG0, VEC_T(1,C) ARG1 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_ART
    @brief Return a vector that is assigned the per-element operation ARG0 / ARG1
    @param [in] ARG0 Vector
    @param [in] ARG1 Vector
    @return A vector that is assigned the per-element operation ARG0 / ARG1 */
TgINLINE VEC_T(1)
FCN_V(tgMH_DIV)(
    VEC_T(1,C) ARG0, VEC_T(1,C) ARG1 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_ART
    @brief Return a vector where each element is the inverse of the argument
    @param [in] ARG0 Vector
    @return A vector where each element is the inverse of the argument */
TgINLINE VEC_T(1)
FCN_V(tgMH_RCP)(
    VEC_T(1,C) ARG );




/** @addtogroup TGS_COMMON_MATH_VECTOR_CALC
    @return Linear interpolation / extrapolation [ARG0 + ARG2*(ARG1 - ARG0)]
    @param [in] ARG0 A value of the function type
    @param [in] ARG1 A value of the function type
    @param [in] ARG2 Interpolant / extrapolant */
TgINLINE VEC_T(1)
FCN_V(tgMH_LRP)(
    VEC_T(1,C) ARG0, VEC_T(1,C) ARG1, VEC_T(1,C) ARG2 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_CALC
    @brief Return a vector where each element contains the the squared-length of the vector
    @param [in] ARG0 Vector
    @return A vector where each element contains the the squared-length of the vector */
TgINLINE VEC_T(1)
FCN_V(tgMH_LSQ)(
    VEC_T(1,C) ARG );

/** @addtogroup TGS_COMMON_MATH_VECTOR_CALC
    @brief Return a vector where each element contains the the length of the vector
    @param [in] ARG0 Vector
    @return A vector where each element contains the the length of the vector */
TgINLINE VEC_T(1)
FCN_V(tgMH_LEN)(
    VEC_T(1,C) ARG );

/** @addtogroup TGS_COMMON_MATH_VECTOR_CALC
    @brief Return a vector that is assigned the per-element operation sqrt(ARG0)
    @param [in] ARG0 Vector
    @return A vector that is assigned the per-element operation sqrt(ARG0) */
TgINLINE VEC_T(1)
FCN_V(tgMH_SQRT)(
    VEC_T(1,C) ARG );

/** @addtogroup TGS_COMMON_MATH_VECTOR_CALC
    @brief Return a vector that is assigned the per-element operation 1.0 / sqrt(ARG0)
    @param [in] ARG0 Vector
    @return A vector that is assigned the per-element operation 1.0 / sqrt(ARG0) */
TgINLINE VEC_T(1)
FCN_V(tgMH_RSQRT)(
    VEC_T(1,C) ARG );

/** @addtogroup TGS_COMMON_MATH_VECTOR_CALC
    @brief Return a vector that is a normalized version of the argument
    @param [in] ARG0 Vector
    @return A vector that is a normalized version of the argument */
TgINLINE VEC_T(1)
FCN_V(tgMH_NORM)(
    VEC_T(1,C) ARG );

/** @addtogroup TGS_COMMON_MATH_VECTOR_CALC
    @brief Return a vector that is a normalized version of the argument and its original length
    @param [out] OUT0 Destination vector to hold the original length of the vector in ARG1
    @param [in] ARG1 Vector
    @return A vector that is a normalized version of the argument and its original length */
TgINLINE VEC_T(1)
FCN_V(tgMH_NORM_LEN)(
    VEC_T(1,PC) TgANALYSIS_NO_NULL OUT0, VEC_T(1,C) ARG1 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_CALC
    @brief Return a new vector with values from ARG0 and the sign in ARG1
    @param [in] ARG0 Vector holding the values of the return values
    @param [in] ARG1 Vector holding the sign of the return values
    @return A new vector with values from ARG0 and the sign in ARG1 */
TgINLINE VEC_T(1)
FCN_V(tgMH_CP_SGN)(
    VEC_T(1,C) ARG0, VEC_T(1,C) ARG1 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_CALC
    @brief Return a new vector whose element value are (-1,0,+1) based on the sign of the argument elements
    @param [in] ARG Vector
    @return A new vector whose element value are (-1,0,+1) based on the sign of the argument elements */
TgINLINE VEC_T(1)
FCN_V(tgMH_PRX_SGN)(
    VEC_T(1,C) ARG );




/** @addtogroup TGS_COMMON_MATH_VECTOR_BOUNDS
    @brief Return a vector that is assigned the per-element operation floor(ARG0)
    @param [in] ARG Vector
    @return A vector that is assigned the per-element operation floor(ARG0) */
TgINLINE VEC_T(1)
FCN_V(tgMH_FLR)(
    VEC_T(1,C) ARG );

/** @addtogroup TGS_COMMON_MATH_VECTOR_BOUNDS
    @brief Return a vector that is assigned the per-element operation ceil(ARG0)
    @param [in] ARG Vector
    @return A vector that is assigned the per-element operation ceil(ARG0) */
TgINLINE VEC_T(1)
FCN_V(tgMH_CEL)(
    VEC_T(1,C) ARG );

/** @addtogroup TGS_COMMON_MATH_VECTOR_BOUNDS
    @brief Return a new vector clamping each element of ARG0 between the range of [ARG1,ARG2]
    @param [in] ARG0 Vector
    @param [in] ARG1 Vector for the minimum range
    @param [in] ARG2 Vector for the maximum range
    @return A new vector clamping each element of ARG0 between the range of [ARG1,ARG2]  */
TgINLINE VEC_T(1)
FCN_V(tgMH_CLP)(
    VEC_T(1,C) ARG0, VEC_T(1,C) ARG1, VEC_T(1,C) ARG2 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_BOUNDS
    @brief Return a new vector that clamps the result to [0,1]
    @param [in] ARG Vector
    @return A new vector that clamps the result to [0,1] */
TgINLINE VEC_T(1)
FCN_V(tgMH_SAT)(
    VEC_T(1,C) ARG );

/** @addtogroup TGS_COMMON_MATH_VECTOR_BOUNDS
    @brief Return true if any lane is not a finite number, and false otherwise
    @param [in] ARG Vector
    @return True if any lane is not a finite number, and false otherwise */
TgINLINE VEC_T(1)
FCN_V(tgMH_NAN)(
    VEC_T(1,C) ARG );

/** @addtogroup TGS_COMMON_MATH_VECTOR_BOUNDS
    @brief Return a new vector whose element value is set if the argument element is in the range of [-ARG1,ARG1]
    @param [in] ARG0 Vector
    @param [in] ARG1 Vector whose elements representing the bounding range
    @return A new vector whose element value is set if the argument element is in the range of [-ARG1,ARG1] */
TgINLINE VEC_T(1)
FCN_V(tgMH_BND)(
    VEC_T(1,C) ARG0, VEC_T(1,C) ARG1 );




/* =============================================================================================================================================================================== */
#endif
