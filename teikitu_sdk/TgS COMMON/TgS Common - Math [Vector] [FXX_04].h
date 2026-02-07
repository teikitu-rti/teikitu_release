/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Math [Vector] [FXX_04].h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_MATH_VECTOR_FXX_04_H)

#if !defined (TEMPLATE_TYPE_EXPANSION__RELOAD)
    #error Must be included as part of a type expansion include chain
#endif


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  DOXYGEN                                                                                                                                                                        */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @defgroup TGS_COMMON_MATH_QUAT SIMD - Quaternion
    @ingroup TGS_COMMON_MATH_VECTOR_API
*/


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @addtogroup TGS_COMMON_MATH_VECTOR_LOAD
    @brief Return a vector with the four arguments
    @param [in] ARG0 X (1st) value for the vector
    @param [in] ARG1 Y (2nd) value for the vector
    @param [in] ARG2 Z (3rd) value for the vector
    @param [in] ARG3 W (4th) value for the vector
    @return A vector with the four arguments */
TgINLINE VEC_T(1)
FCN_V(tgMH_Init_ELEM)(
    VAR_T(C) ARG0, VAR_T(C) ARG1, VAR_T(C) ARG2, VAR_T(C) ARG3 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_LOAD
    @brief Return a vector from the three arguments and W=1.0 for a homogeneous point vector
    @param [in] ARG0 X (1st) value for the vector
    @param [in] ARG1 Y (2nd) value for the vector
    @param [in] ARG2 Z (3rd) value for the vector
    @return A vector from the three arguments and W=1.0 for a homogeneous point vector */
TgINLINE VEC_T(1)
FCN_V(tgMH_Init_Point_ELEM)(
    VAR_T(C) ARG0, VAR_T(C) ARG1, VAR_T(C) ARG2 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_LOAD
    @brief Return a vector from the three arguments and W=0.0 for a homogeneous direction vector
    @param [in] ARG0 X (1st) value for the vector
    @param [in] ARG1 Y (2nd) value for the vector
    @param [in] ARG2 Z (3rd) value for the vector
    @return A vector from the three arguments and W=1.0 for a homogeneous direction vector */
TgINLINE VEC_T(1)
FCN_V(tgMH_Init_Vector_ELEM)(
    VAR_T(C) ARG0, VAR_T(C) ARG1, VAR_T(C) ARG2 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_LOAD
    @brief Return a vector from the argument and W=1.0 for a homogeneous point vector
    @param [in] ARG Vector*/
/** @return A vector from the argument and W=1.0 for a homogeneous point vector */
TgINLINE VEC_T(1)
FCN_V(tgMH_Init_Point)(
    VEC_T(1,C) ARG );

/** @addtogroup TGS_COMMON_MATH_VECTOR_LOAD
    @brief Return a vector from the argument and W=0.0 for a homogeneous direction vector
    @param [in] ARG Vector*/
/** @return A vector from the argument and W=0.0 for a homogeneous direction vector */
TgINLINE VEC_T(1)
FCN_V(tgMH_Init_Vector)(
    VEC_T(1,C) ARG );

/** @addtogroup TGS_COMMON_MATH_VECTOR_LOAD
    @brief Return a vector that is orthogonal to ARG
    @param [in] ARG Vector
    @return A vector that is orthogonal to ARG */
TgINLINE VEC_T(1)
FCN_V(tgMH_Init_Ortho)(
    VEC_T(1,C) ARG );

/** @addtogroup TGS_COMMON_MATH_VECTOR_LOAD
    @brief Store two additional orthogonal vectors to ARG2 (creating a basis)
    @param [out] OUT0 Destination Vector
    @param [out] OUT1 Destination Vector
    @param [in] ARG2 Vector */
TgINLINE TgVOID
FCN_V(tgMH_Init_Basis_From_Vector)(
    VEC_T(1,PC) TgANALYSIS_NO_NULL ARG0, VEC_T(1,PC) TgANALYSIS_NO_NULL ARG1, VEC_T(1,C) ARG2 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_LOAD
    @brief Return a vector where each element is assigned the X element from the argument
    @param [in] ARG Vector*/
/** @return A vector where each element is assigned the X element from the argument */
TgINLINE VEC_T(1)
FCN_V(tgMH_SPX)(
    VEC_T(1,C) ARG );

/** @addtogroup TGS_COMMON_MATH_VECTOR_LOAD
    @brief Return a vector where each element is assigned the Y element from the argument
    @param [in] ARG Vector*/
/** @return A vector where each element is assigned the Y element from the argument */
TgINLINE VEC_T(1)
FCN_V(tgMH_SPY)(
    VEC_T(1,C) ARG );

/** @addtogroup TGS_COMMON_MATH_VECTOR_LOAD
    @brief Return a vector where each element is assigned the Z element from the argument
    @param [in] ARG Vector*/
/** @return A vector where each element is assigned the Z element from the argument */
TgINLINE VEC_T(1)
FCN_V(tgMH_SPZ)(
    VEC_T(1,C) ARG );

/** @addtogroup TGS_COMMON_MATH_VECTOR_LOAD
    @brief Return a vector where each element is assigned the W element from the argument
    @param [in] ARG Vector*/
/** @return A vector where each element is assigned the W element from the argument */
TgINLINE VEC_T(1)
FCN_V(tgMH_SPW)(
    VEC_T(1,C) ARG );




/** @addtogroup TGS_COMMON_MATH_VECTOR_CALC
    @brief Return true if the argument is a valid homogeneous point and false otherwise
    @param [in] ARG Vector*/
/** @return True if the argument is a valid homogeneous point and false otherwise */
TgINLINE TgBOOL
FCN_V(tgMH_Is_Valid_Point)( 
    VEC_T(1,C) ARG );

/** @addtogroup TGS_COMMON_MATH_VECTOR_CALC
    @brief Return true if the argument is a valid homogeneous direction and false otherwise
    @param [in] ARG Vector*/
/** @return True if the argument is a valid homogeneous direction and false otherwise */
TgINLINE TgBOOL
FCN_V(tgMH_Is_Valid_Vector)(
    VEC_T(1,C) ARG );

/** @addtogroup TGS_COMMON_MATH_VECTOR_CALC
    @brief Return true if the argument is a valid homogeneous direction and false otherwise
    @param [in] ARG Vector*/
/** @return True if the argument is a valid homogeneous direction and false otherwise */
TgINLINE TgBOOL
FCN_V(tgMH_Is_Valid_Unit_Vector)(
    VEC_T(1,C) ARG );

/** @addtogroup TGS_COMMON_MATH_VECTOR_CALC
    @brief Return a vector where each element contains the the dot product of the first three elements of the arguments
    @param [in] ARG0 Vector
    @param [in] ARG1 Vector
    @return A vector where each element contains the the dot product of the first three elements of the arguments */
TgINLINE VEC_T(1)
FCN_V(tgMH_DOT3)(
    VEC_T(1,C) ARG0, VEC_T(1,C) ARG1 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_CALC
    @brief Return a vector that is the cross product of the two vector arguments
    @param [in] ARG0 Vector
    @param [in] ARG1 Vector
    @return A vector that is the cross product of the two vector arguments */
TgINLINE VEC_T(1)
FCN_V(tgMH_CX)(
    VEC_T(1,C) ARG0, VEC_T(1,C) ARG1 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_CALC
    @brief Return a vector that is the normalized cross product of the two vector arguments
    @param [in] ARG0 Vector
    @param [in] ARG1 Vector
    @return A vector that is the normalized cross product of the two vector arguments */
TgINLINE VEC_T(1)
FCN_V(tgMH_UCX)(
    VEC_T(1,C) ARG0, VEC_T(1,C) ARG1 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_CALC
    @brief Return a vector that is the normalized cross product of the two vector arguments
    @param [out] OUT0 Destination, to hold the length of the original vector in each element of the vector
    @param [in] ARG1 Vector
    @param [in] ARG2 Vector
    @return A vector that is the normalized cross product of the two vector arguments */
TgINLINE VEC_T(1)
FCN_V(tgMH_UCX_LEN)(
    VEC_T(1,PC) TgANALYSIS_NO_NULL OUT0, VEC_T(1,C) ARG1, VEC_T(1,C) ARG2 );




/** @addtogroup TGS_COMMON_MATH_VECTOR_CMP
    @brief Return true if the first three elements of the two arguments are approximately the same vector, and false otherwise
    @param [in] ARG0 Vector
    @param [in] ARG1 Vector
    @return True if the first three elements of the two arguments are approximately the same vector, and false otherwise */
TgINLINE TgBOOL
FCN_V(tgMH_PRX3_CMP_EQ)(
    VEC_T(1,C) ARG0, VEC_T(1,C) ARG1 );




/** @addtogroup TGS_COMMON_MATH_QUAT
    @brief Return the inverse of the quaternion
    @param [in] ARG Quaternion
    @return The inverse of the quaternion */
TgINLINE VEC_T(1)
FCN_V(tgMH_QT_INV)(
    VEC_T(1,C) ARG );

/** @addtogroup TGS_COMMON_MATH_QUAT
    @brief Multiply the two quaternions
    @param [in] ARG0 Quaternion
    @param [in] ARG1 Quaternion
    @return The result of multiplying the two quaternions */
TgINLINE VEC_T(1)
FCN_V(tgMH_QT_MUL)(
    VEC_T(1,C) ARG0, VEC_T(1,C) ARG1 );

/** @addtogroup TGS_COMMON_MATH_QUAT
    @brief Return a spherical interpolation of the two quaternions according to the vector argument
    @param [in] ARG0 Spherical interpolation factor
    @param [in] ARG1 Quaternion
    @param [in] ARG2 Quaternion
    @return A spherical interpolation of the two quaternions according to the vector argument */
TgINLINE VEC_T(1)
FCN_V(tgMH_QT_Slerp)(
    VEC_T(1,C) ARG0, VEC_T(1,C) ARG1, VEC_T(1,C) ARG2 );

/** @addtogroup TGS_COMMON_MATH_QUAT
    @brief Return the quaternion necessary to rotation the first vector into the second vector
    @param [in] ARG0 Vector
    @param [in] ARG1 Vector
    @return The quaternion necessary to rotation the first vector into the second  */
TgINLINE VEC_T(1)
FCN_V(tgMH_QT_Vector_To_Vector)(
    VEC_T(1,C) ARG0, VEC_T(1,C) ARG1 );

/** @addtogroup TGS_COMMON_MATH_QUAT
    @brief Rotate the vector by the quaternion
    @param [in] ARG0 Vector
    @param [in] ARG1 Quaternion
    @return The result of rotating the vector by the quaternion */
TgINLINE VEC_T(1)
FCN_V(tgMH_QT_TX)(
    VEC_T(1,C) ARG0, VEC_T(1,C) ARG1 );

/** @addtogroup TGS_COMMON_MATH_QUAT
    @brief Rotate the vector by the inverse quaternion
    @param [in] ARG0 Vector
    @param [in] ARG1 Quaternion
    @return The result of rotating the vector by the inverse quaternion */
TgINLINE VEC_T(1)
FCN_V(tgMH_QT_INV_TX)(
    VEC_T(1,C) ARG0, VEC_T(1,C) ARG1 );


/* =============================================================================================================================================================================== */
#endif
