/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Math API [Vector] [FXX_04].h_inc
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_MATH_API_VECTOR_S_FXX_04_H)

#if !defined (TEMPLATE_TYPE_EXPANSION__RELOAD)
    #error Must be included as part of a type expansion include chain
#endif


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  DOXYGEN                                                                                                                                                                        */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @defgroup TGS_COMMON_MATH_QUAT Quaternion
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
TgINLINE VEC_S_T(1)
FCN_V(tgMH_Init_ELEM_S)(
    VAR_T(C) ARG0, VAR_T(C) ARG1, VAR_T(C) ARG2, VAR_T(C) ARG3 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_LOAD
    @brief Return a vector from the three arguments and W=1.0 for a homogeneous point vector
    @param [in] ARG0 X (1st) value for the vector
    @param [in] ARG1 Y (2nd) value for the vector
    @param [in] ARG2 Z (3rd) value for the vector
    @return A vector from the three arguments and W=1.0 for a homogeneous point vector */
TgINLINE VEC_S_T(1)
FCN_V(tgMH_Init_Point_ELEM_S)(
    VAR_T(C) ARG0, VAR_T(C) ARG1, VAR_T(C) ARG2 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_LOAD
    @brief Return a vector from the three arguments and W=0.0 for a homogeneous direction vector
    @param [in] ARG0 X (1st) value for the vector
    @param [in] ARG1 Y (2nd) value for the vector
    @param [in] ARG2 Z (3rd) value for the vector
    @return A vector from the three arguments and W=1.0 for a homogeneous direction vector */
TgINLINE VEC_S_T(1)
FCN_V(tgMH_Init_Vector_ELEM_S)(
    VAR_T(C) ARG0, VAR_T(C) ARG1, VAR_T(C) ARG2 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_LOAD
    @brief Return a vector from the argument and W=1.0 for a homogeneous point vector
    @param [in] ARG Vector
    @return A vector from the argument and W=1.0 for a homogeneous point vector */
TgINLINE VEC_S_T(1)
FCN_V(tgMH_Init_Point_S)(
    VEC_S_T(1,C) ARG );

/** @addtogroup TGS_COMMON_MATH_VECTOR_LOAD
    @brief Return a vector from the argument and W=0.0 for a homogeneous direction vector
    @param [in] ARG Vector
    @return A vector from the argument and W=0.0 for a homogeneous direction vector */
TgINLINE VEC_S_T(1)
FCN_V(tgMH_Init_Vector_S)(
    VEC_S_T(1,C) ARG );

/** @addtogroup TGS_COMMON_MATH_VECTOR_LOAD
    @brief Return a vector that is orthogonal to ARG
    @param [in] ARG Vector
    @return A vector that is orthogonal to ARG */
TgINLINE VEC_S_T(1)
FCN_V(tgMH_Init_Ortho_S)(
    VEC_S_T(1,C) ARG );

/** @addtogroup TGS_COMMON_MATH_VECTOR_LOAD
    @brief Store two additional orthogonal vectors to ARG2 (creating a basis)
    @param [out] OUT0 Destination Vector
    @param [out] OUT1 Destination Vector
    @param [in] ARG2 Vector */
TgINLINE TgVOID
FCN_V(tgMH_Init_Basis_From_Vector_S)(
    VEC_S_T(1,PCU) NONULL ARG0, VEC_S_T(1,PCU) NONULL ARG1, VEC_S_T(1,C) ARG2 );




/** @addtogroup TGS_COMMON_MATH_VECTOR_CALC
    @brief Return true if the argument is a valid homogeneous point and false otherwise
    @param [in] ARG Vector*/
/** @return True if the argument is a valid homogeneous point and false otherwise */
TgINLINE TgBOOL
FCN_V(tgMH_Is_Valid_Point_S)(
    VEC_S_T(1,C) ARG );

/** @addtogroup TGS_COMMON_MATH_VECTOR_CALC
    @brief Return true if the argument is a valid homogeneous direction and false otherwise
    @param [in] ARG Vector*/
/** @return True if the argument is a valid homogeneous direction and false otherwise */
TgINLINE TgBOOL
FCN_V(tgMH_Is_Valid_Vector_S)(
    VEC_S_T(1,C) ARG );

/** @addtogroup TGS_COMMON_MATH_VECTOR_CALC
    @brief Return a vector where each element contains the dot product of the first three elements of the arguments
    @param [in] ARG0 Vector
    @param [in] ARG1 Vector
    @return A vector where each element contains the dot product of the first three elements of the arguments */
TgINLINE VAR_T()
FCN_V(tgMH_DOT3_S)(
    VEC_S_T(1,C) ARG0, VEC_S_T(1,C) ARG1 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_CALC
    @brief Return a vector that is the cross product of the two vector arguments
    @param [in] ARG0 Vector
    @param [in] ARG1 Vector
    @return A vector that is the cross product of the two vector arguments */
TgINLINE VEC_S_T(1)
FCN_V(tgMH_CX_S)(
    VEC_S_T(1,C) ARG0, VEC_S_T(1,C) ARG1 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_CALC
    @brief Return a vector that is the normalized cross product of the two vector arguments
    @param [in] ARG0 Vector
    @param [in] ARG1 Vector
    @return A vector that is the normalized cross product of the two vector arguments */
TgINLINE VEC_S_T(1)
FCN_V(tgMH_UCX_S)(
    VEC_S_T(1,C) ARG0, VEC_S_T(1,C) ARG1 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_CALC
    @brief Return a vector that is the normalized cross product of the two vector arguments
    @param [out] OUT0 Destination, to hold the length of the original vector
    @param [in] ARG1 Vector
    @param [in] ARG2 Vector
    @return A vector that is the normalized cross product of the two vector arguments */
TgINLINE VEC_S_T(1)
FCN_V(tgMH_UCX_LEN_S)(
    VAR_T(P) NONULL OUT0, VEC_S_T(1,C) ARG1, VEC_S_T(1,C) ARG2 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_CALC
    @brief Return a vector where the first three elements of ARG1 have been normalized
    @param [out] OUT0 Destination, to hold the length of the original vector
    @param [in] ARG1 Vector
    @return A vector that is the normalized cross product of the two vector arguments */
TgINLINE VEC_S_T(1)
FCN_V(tgMH_NORM3_LEN_S)(
    VAR_T(P) NONULL OUT0, VEC_S_T(1,C) ARG1 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_CALC
    @brief Return a vector where each element contains the dot product of the first three elements of the arguments
    @param [in] ARG0 Vector
    @param [in] ARG1 Vector
    @return A vector that is the normalized cross product of the two vector arguments */
TgINLINE VEC_S_T(1)
FCN_V(tgMH_NORM3_S)(
    VEC_S_T(1,C) ARG );




/** @addtogroup TGS_COMMON_MATH_VECTOR_CMP
    @brief Return true if the first three elements of the two arguments are approximately the same vector, and false otherwise
    @param [in] ARG0 Vector
    @param [in] ARG1 Vector
    @return True if the first three elements of the two arguments are approximately the same vector, and false otherwise */
TgINLINE TgBOOL
FCN_V(tgMH_PRX3_CMP_EQ_S)(
    VEC_S_T(1,C) ARG0, VEC_S_T(1,C) ARG1 );




/** @addtogroup TGS_COMMON_MATH_QUAT
    @brief Return a quaternion that matches a rotation of ARG3 around the vector made from [ARG0, ARG1, ARG2]
    @param [in] ARG0 X Axis Value
    @param [in] ARG1 Y Axis Value
    @param [in] ARG2 Z Axis Value
    @param [in] ARG3 Angle
    @return A quaternion that matches a rotation of ARG3 around the vector made from [ARG0, ARG1, ARG2] */
TgINLINE VEC_S_T(1)
FCN_V(tgMH_QT_Init_Axis_Angle_ELEM_S)(
    VAR_T(C) ARG0, VAR_T(C) ARG1, VAR_T(C) ARG2, VAR_T(C) ARG3 );

/** @addtogroup TGS_COMMON_MATH_QUAT
    @brief Return a quaternion that matches a rotation of W around the vector made from [X, Y, Z]
    @param [in] ARG Axis-Angle
    @return A quaternion that matches a rotation of W around the vector made from [X, Y, Z] */
TgINLINE VEC_S_T(1)
FCN_V(tgMH_QT_Init_Axis_Angle_S)(
    VEC_S_T(1,C) ARG );

/** @addtogroup TGS_COMMON_MATH_QUAT
    @brief Return a quaternion formed by the Euler rotations of the three arguments
    @param [in] ARG0 Euler X
    @param [in] ARG1 Euler Y
    @param [in] ARG2 Euler Z
    @return A quaternion formed by the Euler rotations of the three arguments */
TgINLINE VEC_S_T(1)
FCN_V(tgMH_QT_Init_Euler_ELEM_S)(
    VAR_T(C) ARG0, VAR_T(C) ARG1, VAR_T(C) ARG2 );

/** @addtogroup TGS_COMMON_MATH_QUAT
    @brief Return a quaternion formed by the Euler rotations of the three arguments
    @param [in] ARG Vector with Euler X, Y, Z
    @return A quaternion formed by the Euler rotations of the three arguments */
TgINLINE VEC_S_T(1)
FCN_V(tgMH_QT_Init_Euler_S)(
    VEC_S_T(1,C) ARG );

/** @addtogroup TGS_COMMON_MATH_QUAT
    @brief Return a quaternion matching a rotation of ARG around an Euler X-Axis
    @param [in] ARG Angle
    @return A quaternion matching a rotation of ARG around an Euler X-Axis */
TgINLINE VEC_S_T(1)
FCN_V(tgMH_QT_Init_Euler_X_S)(
    VAR_T(C) ARG );

/** @addtogroup TGS_COMMON_MATH_QUAT
    @brief Return a quaternion matching a rotation of ARG around an Euler Y-Axis
    @param [in] ARG Angle
    @return A quaternion matching a rotation of ARG around an Euler Y-Axis */
TgINLINE VEC_S_T(1)
FCN_V(tgMH_QT_Init_Euler_Y_S)(
    VAR_T(C) ARG );

/** @addtogroup TGS_COMMON_MATH_QUAT
    @brief Return a quaternion matching a rotation of ARG around an Euler Z-Axis
    @param [in] ARG Angle
    @return A quaternion matching a rotation of ARG around an Euler Z-Axis */
TgINLINE VEC_S_T(1)
FCN_V(tgMH_QT_Init_Euler_Z_S)(
    VAR_T(C) ARG );

/** @addtogroup TGS_COMMON_MATH_QUAT
    @brief Return a vector holding the three Euler angles matching the rotation of the argument quaternion
    @param [out] OUT0 Destination pointer to hold Euler X value
    @param [out] OUT1 Destination pointer to hold Euler Y value
    @param [out] OUT2 Destination pointer to hold Euler Z value
    @param [in] ARG3 Quaternion
    @brief A vector holding the three Euler angles matching the rotation of the argument quaternion */
TgINLINE TgVOID
FCN_V(tgMH_Quat_To_Euler_ELEM_S)(
    VAR_T(PCU) NONULL OUT0, VAR_T(PCU) NONULL OUT1, VAR_T(PCU) NONULL OUT2, VEC_S_T(1,C) ARG3 );

/** @addtogroup TGS_COMMON_MATH_QUAT
    @brief Return a vector holding the three Euler angles matching the rotation of the argument quaternion
    @param [in] ARG Quaternion
    @brief A vector holding the three Euler angles matching the rotation of the argument quaternion */
TgINLINE VEC_S_T(1)
FCN_V(tgMH_Quat_To_Euler_S)(
    VEC_S_T(1,C) ARG );

/** @addtogroup TGS_COMMON_MATH_QUAT
    @brief Return the inverse of the quaternion
    @param [in] ARG Quaternion
    @return The inverse of the quaternion */
TgINLINE VEC_S_T(1)
FCN_V(tgMH_QT_INV_S)(
    VEC_S_T(1,C) ARG );

/** @addtogroup TGS_COMMON_MATH_QUAT
    @brief Multiply the two quaternions
    @param [in] ARG0 Quaternion
    @param [in] ARG1 Quaternion
    @return The result of multiplying the two quaternions */
TgINLINE VEC_S_T(1)
FCN_V(tgMH_QT_MUL_S)(
    VEC_S_T(1,C) ARG0, VEC_S_T(1,C) ARG1 );

/** @addtogroup TGS_COMMON_MATH_QUAT
    @brief Return a spherical interpolation of the two quaternions according to the vector argument
    @param [in] ARG0 Spherical interpolation factor
    @param [in] ARG1 Quaternion
    @param [in] ARG2 Quaternion
    @return A spherical interpolation of the two quaternions according to the vector argument */
TgINLINE VEC_S_T(1)
FCN_V(tgMH_QT_Slerp_S)(
    VAR_T(C) ARG0, VEC_S_T(1,C) ARG1, VEC_S_T(1,C) ARG2 );

/** @addtogroup TGS_COMMON_MATH_QUAT
    @brief Return the quaternion necessary to rotation the first vector into the second vector
    @param [in] ARG0 Vector
    @param [in] ARG1 Vector
    @return The quaternion necessary to rotation the first vector into the second  */
TgINLINE VEC_S_T(1)
FCN_V(tgMH_QT_Vector_To_Vector_S)(
    VEC_S_T(1,C) ARG0, VEC_S_T(1,C) ARG1 );

/** @addtogroup TGS_COMMON_MATH_QUAT
    @brief Rotate the vector by the quaternion
    @param [in] ARG0 Vector
    @param [in] ARG1 Quaternion
    @return The result of rotating the vector by the quaternion */
TgINLINE VEC_S_T(1)
FCN_V(tgMH_QT_TX_S)(
    VEC_S_T(1,C) ARG0, VEC_S_T(1,C) ARG1 );

/** @addtogroup TGS_COMMON_MATH_QUAT
    @brief Rotate the vector by the inverse quaternion
    @param [in] ARG0 Vector
    @param [in] ARG1 Quaternion
    @return The result of rotating the vector by the inverse quaternion */
TgINLINE VEC_S_T(1)
FCN_V(tgMH_QT_INV_TX_S)(
    VEC_S_T(1,C) ARG0, VEC_S_T(1,C) ARG1 );

/** @addtogroup TGS_COMMON_MATH_QUAT
    @brief Rotate the vector ARG0 around the X axis by the angle ARG1
    @param [in] ARG0 Vector
    @param [in] ARG1 Angle
    @return The result of the rotation of the vector ARG0 around the X axis by the angle ARG1 */
TgINLINE VEC_S_T(1)
FCN_V(tgMH_Rotate_Vector_Euler_X_S)(
    VEC_S_T(1,C) ARG0, VAR_T(C) ARG1 );

/** @addtogroup TGS_COMMON_MATH_QUAT
    @brief Rotate the vector ARG0 around the Y axis by the angle ARG1
    @param [in] ARG0 Vector
    @param [in] ARG1 Angle
    @return The result of the rotation of the vector ARG0 around the Y axis by the angle ARG1 */
TgINLINE VEC_S_T(1)
FCN_V(tgMH_Rotate_Vector_Euler_Y_S)(
    VEC_S_T(1,C) ARG0, VAR_T(C) ARG1 );

/** @addtogroup TGS_COMMON_MATH_QUAT
    @brief Rotate the vector ARG0 around the Z axis by the angle ARG1
    @param [in] ARG0 Vector
    @param [in] ARG1 Angle
    @return The result of the rotation of the vector ARG0 around the Z axis by the angle ARG1 */
TgINLINE VEC_S_T(1)
FCN_V(tgMH_Rotate_Vector_Euler_Z_S)(
    VEC_S_T(1,C) ARG0, VAR_T(C) ARG1 );


/* =============================================================================================================================================================================== */
#endif
