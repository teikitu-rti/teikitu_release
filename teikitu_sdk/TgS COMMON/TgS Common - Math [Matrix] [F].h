/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Math [Matrix] [F].h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_MATH_MATRIX_F_H)

#if !defined (TEMPLATE_TYPE_EXPANSION__RELOAD)
    #error Must be included as part of a type expansion include chain
#endif


/* == Common ===================================================================================================================================================================== */

/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/*  Implementation: Matrix Size Specific                                                                                                                                           */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

/* ---- TGS_COMMON_MATH_VECTOR_LOAD ---------------------------------------------------------------------------------------------------------------------------------------------- */

/** @addtogroup TGS_COMMON_MATH_VECTOR_LOAD
    @brief Initialize the rotation of matrix (ARG0) from the matrix at ARG1
    @param [out] OUT0 Matrix
    @param [in] ARG1 Matrix */
TgINLINE TgVOID
FCN_M(tgMH_Init_ROT)(
    MAT_T(PC) TgANALYSIS_NO_NULL OUT0, MAT_T(CPC) TgANALYSIS_NO_NULL ARG1 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_LOAD
    @brief Initialize the translocation of the matrix (ARG0) to the location ARG1
    @param [out] OUT0 Matrix
    @param [in] ARG1 Vector */
TgINLINE TgVOID
FCN_M(tgMH_Init_T)(
    MAT_T(PC) TgANALYSIS_NO_NULL OUT0, VEC_T(1,C) ARG1 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_LOAD
    @brief Initialize the translocation of the matrix (ARG0) to the location ARG1-ARG3
    @param [out] OUT0 Matrix
    @param [in] ARG1 X Location
    @param [in] ARG2 Y Location
    @param [in] ARG3 Z Location */
TgINLINE TgVOID
FCN_M(tgMH_Init_T_ELEM)(
    MAT_T(PC) TgANALYSIS_NO_NULL OUT0, VAR_T(C) ARG1, VAR_T(C) ARG2, VAR_T(C) ARG3 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_LOAD
    @brief Initialize the rotation of the matrix (ARG0) to an Euler rotation from the first three elements of the vector ARG1
    @param [in,out] OUT0 Pointer to output matrix.
    @param [in] ARG1 Vector holding three Euler Angles */
TgINLINE TgVOID
FCN_M(tgMH_Init_Euler)(
    MAT_T(PC) TgANALYSIS_NO_NULL OUT0, VEC_T(1,C) ARG1 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_LOAD
    @brief Initialize the rotation of the matrix (ARG0) to an Euler rotation of ARG1-ARG3
    @param [out] OUT0 Matrix
    @param [in] ARG1 Euler X angle
    @param [in] ARG2 Euler Y angle
    @param [in] ARG3 Euler Z angle */
TgINLINE TgVOID
FCN_M(tgMH_Init_Euler_ELEM)(
    MAT_T(PC) TgANALYSIS_NO_NULL OUT0, VAR_T(C) ARG1, VAR_T(C) ARG2, VAR_T(C) ARG3 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_LOAD
    @brief Initialize a matrix with a matching rotation of ARG1 around the X axis
    @param [out] OUT0 Matrix
    @param [in] ARG1 Angle */
TgINLINE TgVOID
FCN_M(tgMH_Init_Euler_X)(
    MAT_T(PC) TgANALYSIS_NO_NULL OUT0, VAR_T(C) ARG1 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_LOAD
    @brief Initialize a matrix with a matching rotation of ARG1 around the Y axis
    @param [out] OUT0 Matrix
    @param [in] ARG1 Angle */
TgINLINE TgVOID
FCN_M(tgMH_Init_Euler_Y)(
    MAT_T(PC) TgANALYSIS_NO_NULL OUT0, VAR_T(C) ARG1 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_LOAD
    @brief Initialize a matrix with a matching rotation of ARG1 around the Z axis
    @param [out] OUT0 Matrix
    @param [in] ARG1 Angle */
TgINLINE TgVOID
FCN_M(tgMH_Init_Euler_Z)(
    MAT_T(PC) TgANALYSIS_NO_NULL OUT0, VAR_T(C) ARG1 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_LOAD
    @brief Initialize a matrix with a matching rotation to the quaternion at ARG1
    @param [out] OUT0 Matrix
    @param [in] ARG1 Quaternion */
TgINLINE TgVOID
FCN_M(tgMH_Init_Quat)(
    MAT_T(PC) TgANALYSIS_NO_NULL OUT0, VEC_T(1,C) ARG1 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_LOAD
    @brief Calculate a reference frame from using the position/translation and non-parallel other vector (a basis vector).
    @param [out] OUT0 Matrix
    @param [in] ARG1 Vector - Used as the second basis vector
    @param [in] ARG2 Vector - Translation */
TgINLINE TgVOID
FCN_M(tgMH_Init_Reference_Frame_From_Vector_And_Position)(
    MAT_T(PC) TgANALYSIS_NO_NULL OUT0, VEC_T(1,C) ARG1, VEC_T(1,C) ARG2 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_LOAD
    @brief Create a reference frame from the basis vectors and position/translation.
    @param [out] OUT0 Matrix
    @param [in] ARG1 Vector - Ortho-normal basis vector 0 - Coplanar
    @param [in] ARG2 Vector - Ortho-normal basis vector 1 - Normal to the plane
    @param [in] ARG3 Vector - Ortho-normal basis vector 2 - Coplanar
    @param [in] ARG4 Vector position / translation of the matrix */
TgINLINE TgVOID
FCN_M(tgMH_Init_Reference_Frame_From_Basis_Axes_And_Position)(
    MAT_T(PC) TgANALYSIS_NO_NULL OUT0, VEC_T(1,C) ARG1, VEC_T(1,C) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_LOAD
    @brief Create a reference frame from a quaternion rotation and position.
    @param [out] OUT0 Matrix - Column major ortho-normal basis vector matrix.
    @param [in] ARG1 Quternion rotation of the matrix.
    @param [in] ARG2 Vector position / translation of the matrix. */
TgINLINE TgVOID
FCN_M(tgMH_Init_Reference_Frame_From_Quaternion_And_Position)(
    MAT_T(PC) TgANALYSIS_NO_NULL OUT0, VEC_T(1,C) ARG1, VEC_T(1,C) ARG2 );


/* ---- TGS_COMMON_MATH_VECTOR_CALC ---------------------------------------------------------------------------------------------------------------------------------------------- */

/** @addtogroup TGS_COMMON_MATH_VECTOR_CALC
    @brief Determine if the reference frame is valid
    @param [in] ARG Matrix
    @return true if the reference frame is valid and false otherwise */
TgINLINE TgBOOL
FCN_M(tgMH_Is_Valid_Reference_Frame)(
    MAT_T(CPC) TgANALYSIS_NO_NULL ARG );

/** @addtogroup TGS_COMMON_MATH_VECTOR_CALC
    @brief Store the concatenation (multiplication) of the two arguments (ARG1 x ARG2)
    @param [out] OUT0 Pointer to output matrix.
    @param [in] ARG1 Matrix
    @param [in] ARG2 Matrix */
TgINLINE TgVOID
FCN_M(tgMH_CAT)(
    MAT_T(PC) TgANALYSIS_NO_NULL OUT0, MAT_T(CPC) TgANALYSIS_NO_NULL ARG1, MAT_T(CPC) TgANALYSIS_NO_NULL ARG2 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_CALC
    @brief Store the inverse of the matrix at ARG2 in ARG0 and the determinant in ARG1
    @param [out] OUT0 Pointer to output matrix.
    @param [in] ARG1 Determinant of the matrix at ARG2
    @param [in] ARG2 Matrix */
TgINLINE TgVOID
FCN_M(tgMH_INV_DET)(
    VEC_T(4,PC) TgANALYSIS_NO_NULL OUT0, VEC_T(1,C) ARG1, MAT_T(CPC) TgANALYSIS_NO_NULL ARG2 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_CALC
    @brief Store the inverse of the matrix at ARG1 in ARG0
    @param [out] OUT0 Pointer to output matrix.
    @param [in] ARG1 Matrix */
TgINLINE TgVOID
FCN_M(tgMH_INV)(
    VEC_T(4,PC) TgANALYSIS_NO_NULL OUT0, MAT_T(CPC) TgANALYSIS_NO_NULL ARG1 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_CALC
    @brief Return the determinant of the matrix at OUT0
    @param [in] ARG Matrix
    @return The determinant of the matrix at OUT0 */
TgINLINE VEC_T(1)
FCN_M(tgMH_DET)(
    MAT_T(CPC) TgANALYSIS_NO_NULL ARG );

/** @addtogroup TGS_COMMON_MATH_VECTOR_CALC
    @brief Transform the vector at ARG1 by the matrix at ARG0
    @param [in] ARG0 Vector
    @param [in] ARG1 Matrix
    @return The result of the transform of the vector at ARG1 by the matrix at ARG0 */
TgINLINE VEC_T(1)
FCN_M(tgMH_TX)(
    VEC_T(1,C) ARG0, MAT_T(CPC) TgANALYSIS_NO_NULL ARG1 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_CALC
    @brief Transform the vector at ARG1 (and treated as a homogeneous point) by the matrix at ARG0
    @param [in] ARG0 Vector
    @param [in] ARG1 Matrix
    @return The result of the transform of the vector at ARG1 (and treated as a homogeneous point) by the matrix at ARG0 */
TgINLINE VEC_T(1)
FCN_M(tgMH_TX_P)(
    VEC_T(1,C) ARG0, MAT_T(CPC) TgANALYSIS_NO_NULL ARG1 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_CALC
    @brief Transform the vector at ARG1 (and treated as a homogeneous vector) by the matrix at ARG0
    @param [in] ARG0 Vector
    @param [in] ARG1 Matrix
    @return The result of the transform of the vector at ARG1 (and treated as a homogeneous vector) by the matrix at ARG0 */
TgINLINE VEC_T(1)
FCN_M(tgMH_TX_V)(
    VEC_T(1,C) ARG0, MAT_T(CPC) TgANALYSIS_NO_NULL ARG1 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_CALC
    @brief Return the first row from the matrix at ARG
    @param [in] ARG Matrix
    @return The first row from the matrix at ARG */
TgINLINE VEC_T(1)
FCN_M(tgMH_Query_Row_0)(
    MAT_T(CPC) TgANALYSIS_NO_NULL ARG );

/** @addtogroup TGS_COMMON_MATH_VECTOR_CALC
    @brief Return the second row from the matrix at ARG
    @param [in] ARG Matrix
    @return The second row from the matrix at ARG */
TgINLINE VEC_T(1)
FCN_M(tgMH_Query_Row_1)(
    MAT_T(CPC) TgANALYSIS_NO_NULL ARG );

/** @addtogroup TGS_COMMON_MATH_VECTOR_CALC
    @brief Return the third row from the matrix at ARG
    @param [in] ARG Matrix
    @return The third row from the matrix at ARG */
TgINLINE VEC_T(1)
FCN_M(tgMH_Query_Row_2)(
    MAT_T(CPC) TgANALYSIS_NO_NULL ARG );

/** @addtogroup TGS_COMMON_MATH_VECTOR_CALC
    @brief Return the fourth row from the matrix at ARG
    @param [in] ARG Matrix
    @return The fourth row from the matrix at ARG */
TgINLINE VEC_T(1)
FCN_M(tgMH_Query_Row_3)(
    MAT_T(CPC) TgANALYSIS_NO_NULL ARG );

/** @addtogroup TGS_COMMON_MATH_VECTOR_CALC
    @brief Return the first column from the matrix at ARG
    @param [in] ARG Matrix
    @return The first column from the matrix at ARG */
TgINLINE VEC_T(1)
FCN_M(tgMH_Query_Col_0)(
    MAT_T(CPC) TgANALYSIS_NO_NULL ARG );

/** @addtogroup TGS_COMMON_MATH_VECTOR_CALC
    @brief Return the second column from the matrix at ARG
    @param [in] ARG Matrix
    @return The second column from the matrix at ARG */
TgINLINE VEC_T(1)
FCN_M(tgMH_Query_Col_1)(
    MAT_T(CPC) TgANALYSIS_NO_NULL ARG );

/** @addtogroup TGS_COMMON_MATH_VECTOR_CALC
    @brief Return the third column from the matrix at ARG
    @param [in] ARG Matrix
    @return The third column from the matrix at ARG */
TgINLINE VEC_T(1)
FCN_M(tgMH_Query_Col_2)(
    MAT_T(CPC) TgANALYSIS_NO_NULL ARG );

/** @addtogroup TGS_COMMON_MATH_VECTOR_CALC
    @brief Return the fourth column from the matrix at ARG
    @param [in] ARG Matrix
    @return The fourth column from the matrix at ARG */
TgINLINE VEC_T(1)
FCN_M(tgMH_Query_Col_3)(
    MAT_T(CPC) TgANALYSIS_NO_NULL ARG );

/** @addtogroup TGS_COMMON_MATH_VECTOR_CALC
    @brief Return the first row from the matrix at ARG, assuming it is used for homogeneous transformations
    @param [in] ARG Matrix
    @return The first row from the matrix at ARG */
TgINLINE VEC_T(1)
FCN_M(tgMH_Query_Axis_0)(
    MAT_T(CPC) TgANALYSIS_NO_NULL ARG );

/** @addtogroup TGS_COMMON_MATH_VECTOR_CALC
    @brief Return the second row from the matrix at ARG, assuming it is used for homogeneous transformations
    @param [in] ARG Matrix
    @return The second row from the matrix at ARG */
TgINLINE VEC_T(1)
FCN_M(tgMH_Query_Axis_1)(
    MAT_T(CPC) TgANALYSIS_NO_NULL ARG );

/** @addtogroup TGS_COMMON_MATH_VECTOR_CALC
    @brief Return the third row from the matrix at ARG, assuming it is used for homogeneous transformations
    @param [in] ARG Matrix
    @return The third row from the matrix at ARG */
TgINLINE VEC_T(1)
FCN_M(tgMH_Query_Axis_2)(
    MAT_T(CPC) TgANALYSIS_NO_NULL ARG );

/** @addtogroup TGS_COMMON_MATH_VECTOR_CALC
    @brief Return the fourth row from the matrix at ARG, assuming it is used for homogeneous transformations
    @param [in] ARG Matrix
    @return The fourth row from the matrix at ARG */
TgINLINE VEC_T(1)
FCN_M(tgMH_Query_Axis_3)(
    MAT_T(CPC) TgANALYSIS_NO_NULL ARG );

/** @addtogroup TGS_COMMON_MATH_VECTOR_CALC
    @brief Store the basis vectors and translation contained by the reference frame. @return Result Code.
    @param [out] OUT0 Vector - Ortho-normal basis vector 0 - Coplanar.
    @param [out] OUT1 Vector - Ortho-normal basis vector 1 - Normal to the plane.
    @param [out] OUT2 Vector - Ortho-normal basis vector 2 - Coplanar.
    @param [out] OUT3 Vector - Translation.
    @param [in] ARG4 Matrix. */
TgINLINE TgRESULT
FCN_M(tgMH_Query_Reference_Frame)(
    VEC_T(1,PC) TgANALYSIS_NO_NULL OUT0, VEC_T(1,PC) TgANALYSIS_NO_NULL OUT1, VEC_T(1,PC) TgANALYSIS_NO_NULL OUT2, VEC_T(1,PC) TgANALYSIS_NO_NULL OUT3, MAT_T(CPC) TgANALYSIS_NO_NULL ARG4 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_CALC
    @brief Store the three Euler angles that match the rotation of the matrix at ARG3
    @param [out] OUT0 Pointer to a scalar value for the X rotation
    @param [out] OUT1 Pointer to a scalar value for the Y rotation
    @param [out] OUT2 Pointer to a scalar value for the Z rotation
    @param [in] ARG3 Matrix */
TgINLINE TgVOID
FCN_M(tgMH_Matrix_To_Euler_ELEM)(
    VAR_T(P) TgANALYSIS_NO_NULL OUT0, VAR_T(P) TgANALYSIS_NO_NULL OUT1, VAR_T(P) TgANALYSIS_NO_NULL OUT2, MAT_T(CPC) TgANALYSIS_NO_NULL ARG3 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_CALC
    @brief Store the three Euler angles that match the rotation of the matrix at ARG3
    @param [out] OUT0 Pointer to a vector to hold the three Euler angles
    @param [in] ARG1 Matrix */
TgINLINE TgVOID
FCN_M(tgMH_Matrix_To_Euler)(
    VEC_T(1,PC) TgANALYSIS_NO_NULL OUT0, MAT_T(CPC) TgANALYSIS_NO_NULL ARG1 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_CALC
    @brief Store the quaternion that matches the rotation of the matrix at ARG3
    @param [out] OUT0 Quaternion
    @param [in] ARG1 Matrix */
TgINLINE TgVOID
FCN_M(tgMH_Matrix_To_Quat)(
    VEC_T(1,PC) TgANALYSIS_NO_NULL OUT0, MAT_T(CPC) TgANALYSIS_NO_NULL ARG1 );




/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/*  Implementation: Matrix Size Specific                                                                                                                                           */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

/** @addtogroup TGS_COMMON_MATH_VECTOR_LOAD
    @brief Store an identity matrix at the destination
    @param [out] OUT0 Pointer to output matrix. */
TgINLINE TgVOID
FCN_M(tgMH_CLI)(
    MAT_T(PC) TgANALYSIS_NO_NULL OUT0 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_LOAD
    @brief Store an identity matrix at the destination
    @param [out] OUT0 Pointer to output matrix. */
TgINLINE TgVOID
FCN_M(tgMH_DIAG)(
    MAT_T(PC) TgANALYSIS_NO_NULL OUT0, VAR_T(C) ARG1 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_LOAD
    @brief Set the rotation of matrix (ARG0) from the matrix at ARG1
    @param [in,out] OUT0 Pointer to output matrix.
    @param [in] ARG1  */
TgINLINE TgVOID
FCN_M(tgMH_Set_Rot)(
    MAT_T(PC) TgANALYSIS_NO_NULL OUT0, MAT_T(CPC) TgANALYSIS_NO_NULL ARG1 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_LOAD
    @brief Set the translocation of the matrix (ARG0) to the location ARG1
    @param [in,out] OUT0 Pointer to output matrix.
    @param [in] ARG1 Vector */
TgINLINE TgVOID
FCN_M(tgMH_Set_T)(
    MAT_T(PC) TgANALYSIS_NO_NULL OUT0, VEC_T(1,C) ARG1 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_LOAD
    @brief Set the translocation of the matrix (ARG0) to the location ARG1-ARG3
    @param [in,out] OUT0 Pointer to output matrix.
    @param [in] ARG1 X Location
    @param [in] ARG2 Y Location
    @param [in] ARG3 Z Location */
TgINLINE TgVOID
FCN_M(tgMH_Set_T_ELEM)(
    MAT_T(PC) TgANALYSIS_NO_NULL OUT0, VAR_T(C) ARG1, VAR_T(C) ARG2, VAR_T(C) ARG3 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_LOAD
    @brief Set the rotation of the matrix (ARG0) to an Euler rotation from the first three elements of the vector ARG1
    @param [in,out] OUT0 Pointer to output matrix.
    @param [in] ARG1 Vector holding three Euler Angles */
TgINLINE TgVOID
FCN_M(tgMH_Set_Euler)(
    MAT_T(PC) TgANALYSIS_NO_NULL OUT0, VEC_T(1,C) ARG1 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_LOAD
    @brief Set the rotation of the matrix (ARG0) to an Euler rotation of ARG1-ARG3
    @param [in,out] OUT0 Pointer to output matrix.
    @param [in] ARG1 Euler X angle
    @param [in] ARG2 Euler Y angle
    @param [in] ARG3 Euler Z angle */
TgINLINE TgVOID
FCN_M(tgMH_Set_Euler_ELEM)(
    MAT_T(PC) TgANALYSIS_NO_NULL OUT0, VAR_T(C) ARG1, VAR_T(C) ARG2, VAR_T(C) ARG3 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_LOAD
    @brief Set the rotation of the matrix (ARG0) to a matching rotation of ARG1 around the X axis
    @param [in,out] OUT0 Pointer to output matrix.
    @param [in] ARG1 Euler X angle */
TgINLINE TgVOID
FCN_M(tgMH_Set_Euler_X)(
    MAT_T(PC) TgANALYSIS_NO_NULL OUT0, VAR_T(C) ARG1 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_LOAD
    @brief Set the rotation of the matrix (ARG0) to a matching rotation of ARG1 around the Y axis
    @param [in,out] OUT0 Pointer to output matrix.
    @param [in] ARG1 Euler Y angle */
TgINLINE TgVOID
FCN_M(tgMH_Set_Euler_Y)(
    MAT_T(PC) TgANALYSIS_NO_NULL OUT0, VAR_T(C) ARG1 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_LOAD
    @brief Set the rotation of the matrix (ARG0) to a matching rotation of ARG1 around the Z axis
    @param [in,out] OUT0 Pointer to output matrix.
    @param [in] ARG1 Euler Z angle */
TgINLINE TgVOID
FCN_M(tgMH_Set_Euler_Z)(
    MAT_T(PC) TgANALYSIS_NO_NULL OUT0, VAR_T(C) ARG1 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_LOAD
    @brief Set the rotation of the matrix (ARG0) to a matching rotation of the quaternion ARG1
    @param [in,out] OUT0 Pointer to output matrix.
    @param [in] ARG1 Quaternion */
TgINLINE TgVOID
FCN_M(tgMH_Set_Quat)(
    MAT_T(PC) TgANALYSIS_NO_NULL OUT0, VEC_T(1,C) ARG1 );


/* ---- TGS_COMMON_MATH_VECTOR_ART ----------------------------------------------------------------------------------------------------------------------------------------------- */

/** @addtogroup TGS_COMMON_MATH_VECTOR_ART
    @brief Store a matrix that is assigned the per-element operation ARG1 + ARG2
    @param [out] OUT0 Pointer to output matrix.
    @param [in] ARG1 Matrix
    @param [in] ARG2 Matrix */
TgINLINE TgVOID
FCN_M(tgMH_ADD)(
    MAT_T(PC) TgANALYSIS_NO_NULL OUT0, MAT_T(CPC) TgANALYSIS_NO_NULL ARG1, MAT_T(CPC) TgANALYSIS_NO_NULL ARG2 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_ART
    @brief Store a matrix that is assigned the per-element operation ARG1 * ARG2
    @param [out] OUT0 Pointer to output matrix.
    @param [in] ARG1 Matrix
    @param [in] ARG2 Matrix */
TgINLINE TgVOID
FCN_M(tgMH_MUL)(
    MAT_T(PC) TgANALYSIS_NO_NULL OUT0, MAT_T(CPC) TgANALYSIS_NO_NULL ARG1, MAT_T(CPC) TgANALYSIS_NO_NULL ARG2 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_ART
    @brief Store a matrix that is assigned the per-element operation ARG1 / ARG2
    @param [out] OUT0 Pointer to output matrix.
    @param [in] ARG1 Matrix
    @param [in] ARG2 Matrix */
TgINLINE TgVOID
FCN_M(tgMH_DIV)(
    MAT_T(PC) TgANALYSIS_NO_NULL OUT0, MAT_T(CPC) TgANALYSIS_NO_NULL ARG1, MAT_T(CPC) TgANALYSIS_NO_NULL ARG2 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_ART
    @brief Store a matrix that is assigned the per-element operation ARG1 - ARG2
    @param [out] OUT0 Pointer to output matrix.
    @param [in] ARG1 Matrix
    @param [in] ARG2 Matrix */
TgINLINE TgVOID
FCN_M(tgMH_SUB)(
    MAT_T(PC) TgANALYSIS_NO_NULL OUT0, MAT_T(CPC) TgANALYSIS_NO_NULL ARG1, MAT_T(CPC) TgANALYSIS_NO_NULL ARG2 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_ART
    @brief Store a matrix that is assigned the per-element operation -ARG1
    @param [out] OUT0 Pointer to output matrix.
    @param [in] ARG1 Matrix */
TgINLINE TgVOID
FCN_M(tgMH_NEG)(
    MAT_T(PC) TgANALYSIS_NO_NULL OUT0, MAT_T(CPC) TgANALYSIS_NO_NULL ARG1 );


/* ---- TGS_COMMON_MATH_VECTOR_CALC ---------------------------------------------------------------------------------------------------------------------------------------------- */

/** @addtogroup TGS_COMMON_MATH_VECTOR_CALC
    @brief Return true if any element from the matrix at ARG are not a number, or false otherwise
    @param [in] ARG Matrix */
TgINLINE TgBOOL
FCN_M(tgMH_NAN)(
    MAT_T(CPC) TgANALYSIS_NO_NULL ARG );



/* =============================================================================================================================================================================== */
#endif
