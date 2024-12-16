/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Geometry 3D - Triangle [Point].h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_GEOMETRY_3D_TRIANGLE_POINT_H)

#if !defined (TEMPLATE_TYPE_EXPANSION__RELOAD)
    #error Must be included as part of a type expansion include chain
#endif


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @addtogroup TGS_COMMON_GEOMETRY_PT */
/** @{ */

/** @brief Calculate the normal of the triangle
    @param [in,out] ARG Pointer to the geometry object (triangle) */
TgINLINE TgVOID
FCN_VO(tgGM_PT_Calc_Normal)(
    VEC_OBJ_T(TgPTRI,PCU) NONULL ARG );

/** @brief Invalidate the geometry object (triangle)
    @param [out] OUT Pointer to the geometry object (triangle) */
TgINLINE TgVOID
FCN_VO(tgGM_PT_Reset)(
    VEC_OBJ_T(TgPTRI,PCU) NONULL OUT );

/** @brief Validate the integrity of the geometry object (triangle)
    @param [in] ARG Pointer to a geometry object (triangle)
    @return True if the geometry object (triangle) is valid and false otherwise */
TgEXTN TgBOOL
FCN_VO(tgGM_PT_Is_Valid)(
    VEC_OBJ_T(TgPTRI,CPCU) NONULL ARG );

/** @brief Determine the point on the geometry object (triangle) that is furthest along the direction of ARG1
    @param [in] ARG0 Pointer to a geometry object (triangle)
    @param [in] ARG1 Direction vector
    @return The point on the geometry object (triangle) that is furthest along the direction of ARG1 */
TgEXTN VEC_T(1)
FCN_VO(tgGM_PT_Support_Point)(
    VEC_OBJ_T(TgPTRI,CPCU) NONULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Calculate the surface area of the geometry object (triangle)
    @param [in] ARG Pointer to a geometry object (triangle)
    @return The surface area of the geometry object (triangle) */
TgINLINE VEC_T(1)
FCN_VO(tgGM_PT_Area)(
    VEC_OBJ_T(TgPTRI,CPCU) NONULL ARG );

/** @brief Calculate the minimum necessary Axis-Aligned Bounding Box to contain the geometry object (triangle)
    @param [out] ARG0 Pointer to an axis-aligned bounding box object
    @param [in] ARG1 Pointer to a geometry object (triangle) */
TgINLINE TgVOID
FCN_VO(tgGM_PT_BA)(
    VEC_OBJ_T(TgBOXAA,PCU) NONULL ARG0, VEC_OBJ_T(TgPTRI,CPCU) NONULL ARG1 );

/** @brief Calculate the minimum necessary Axis-Aligned Bounding Box to contain the swept geometry object (triangle)
    @param [out] ARG0 Pointer to an axis-aligned bounding box object
    @param [in] ARG1 Pointer to a geometry object (triangle)
    @param [in] ARG2 Pointer to a vector describing the swept direction and magnitude */
TgINLINE TgVOID
FCN_VO(tgGM_PT_Sweep_BA)(
    VEC_OBJ_T(TgBOXAA,PCU) NONULL ARG0, VEC_OBJ_T(TgPTRI,CPCU) NONULL ARG1, VEC_T(1,C) ARG2 );

/** @brief Project the geometry object (triangle) along the direction vector
    @param [out] OUT0 Pointer to a scalar value to hold the lower bound of the projection
    @param [out] OUT1 Pointer to a scalar value to hold the upper bound of the projection
    @param [in] ARG2 Pointer to a geometry object (triangle)
    @param [in] ARG3 Direction vector */
TgINLINE TgVOID
FCN_VO(tgGM_PT_Project)(
    VEC_T(1,PCU) NONULL ARG0, VEC_T(1,PCU) NONULL ARG1, VEC_OBJ_T(TgPTRI,CPCU) NONULL ARG2, VEC_T(1,C) ARG3 );

/** @brief Test to see if a point is either on or in the geometry object (triangle)
    @param [in] ARG0 Pointer to a geometry object (triangle)
    @param [in] ARG1 Position vector
    @return True if the position is either on or in the geometry object (triangle) and false otherwise */
TgINLINE TgBOOL
FCN_VO(tgGM_PT_Is_Contained)(
    VEC_OBJ_T(TgPTRI,CPCU) NONULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Transform the geometry object (triangle) at ARG0 by the matrix at ARG1
    @param [in,out] ARG0 Pointer to a geometry object (triangle)
    @param [in] ARG1 Column-Major matrix (3x4) containing rotation and translation */
TgINLINE TgVOID
FCN_VO(tgGM_PT_TX)(
    VEC_OBJ_T(TgPTRI,PCU) NONULL ARG0, VEC_T(3,CPCU) NONULL ARG1 );

/** @brief Transform the geometry object (triangle) at ARG1 by the matrix at ARG2 and store it in ARG0
    @param [out] ARG0 Pointer to a geometry object (triangle)
    @param [in] ARG1 Pointer to a geometry object (triangle)
    @param [in] ARG2 Column-Major matrix (3x4) containing rotation and translation */
TgINLINE TgVOID
FCN_VO(tgGM_PT_Copy_TX)(
    VEC_OBJ_T(TgPTRI,PCU) NONULL ARG0, VEC_OBJ_T(TgPTRI,CPCU) NONULL ARG1, VEC_T(3,CPCU) NONULL ARG2 );


/** @brief Initialize a new geometry object (triangle) with the function arguments
    @note Consistency of the normal with the three points is left to the caller
    @param [out] ARG0 Pointer to a geometry object (triangle)
    @param [in] ARG1 Position vector - first point
    @param [in] ARG2 Position vector - second point
    @param [in] ARG3 Position vector - third point
    @param [in] ARG4 Direction vector - normal */
TgINLINE TgVOID
FCN_VO(tgGM_PT_Init_PN)(
    VEC_OBJ_T(TgPTRI,PCU) NONULL ARG0, VEC_T(1,C) ARG1, VEC_T(1,C) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4 );

/** @brief Initialize a new geometry object (triangle) with the function arguments
    @note Consistency of the normal with the three points is left to the caller
    @param [out] ARG0 Pointer to a geometry object (triangle)
    @param [in] ARG1 Position vector - first point
    @param [in] ARG2 Position vector - second point
    @param [in] ARG3 Position vector - third point  */
TgINLINE TgVOID
FCN_VO(tgGM_PT_Init_P)(
    VEC_OBJ_T(TgPTRI,PCU) NONULL ARG0, VEC_T(1,C) ARG1, VEC_T(1,C) ARG2, VEC_T(1,C) ARG3 );

/** @brief Copy the one geometry object (triangle) to another of the same type
    @param [out] ARG0 Pointer to a geometry object (triangle)
    @param [in] ARG1 Pointer to a geometry object (triangle) */
TgINLINE TgVOID
FCN_VO(tgGM_PT_Copy)(
    VEC_OBJ_T(TgPTRI,PCU) NONULL ARG0, VEC_OBJ_T(TgPTRI,CPCU) NONULL ARG1 );


/** @brief Set the origin / first point of the triangle
    @param [in,out] ARG0 Pointer to a geometry object (triangle)
    @param [in] ARG1 Position vector */
TgINLINE TgVOID
FCN_VO(tgGM_PT_Set_Origin)(
    VEC_OBJ_T(TgPTRI,PCU) NONULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Set the first point of the triangle
    @param [in,out] ARG0 Pointer to a geometry object (triangle)
    @param [in] ARG1 Position vector */
TgINLINE TgVOID
FCN_VO(tgGM_PT_Set_Point_0)(
    VEC_OBJ_T(TgPTRI,PCU) NONULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Set the second point of the triangle
    @param [in,out] ARG0 Pointer to a geometry object (triangle)
    @param [in] ARG1 Position vector */
TgINLINE TgVOID
FCN_VO(tgGM_PT_Set_Point_1)(
    VEC_OBJ_T(TgPTRI,PCU) NONULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Set the third point of the triangle
    @param [in,out] ARG0 Pointer to a geometry object (triangle)
    @param [in] ARG1 Position vector */
TgINLINE TgVOID
FCN_VO(tgGM_PT_Set_Point_2)(
    VEC_OBJ_T(TgPTRI,PCU) NONULL ARG0, VEC_T(1,C) ARG1 );


/** @brief Return the origin / first point of the triangle
    @param [in] ARG Pointer to a geometry object (triangle)
    @return The origin / first point of the triangle */
TgINLINE VEC_T(1)
FCN_VO(tgGM_PT_Query_Origin)(
    VEC_OBJ_T(TgPTRI,CPCU) NONULL ARG );

/** @brief Return the normal of the plane
    @param [in] ARG Pointer to a geometry object (triangle)
    @return The normal of the plane */
TgINLINE VEC_T(1)
FCN_VO(tgGM_PT_Query_Normal)(
    VEC_OBJ_T(TgPTRI,CPCU) NONULL ARG );

/** @brief Return the first point of the triangle
    @param [in] ARG Pointer to a geometry object (triangle)
    @return The first point of the triangle */
TgINLINE VEC_T(1)
FCN_VO(tgGM_PT_Query_Point_0)(
    VEC_OBJ_T(TgPTRI,CPCU) NONULL ARG );

/** @brief Return the second point of the triangle
    @param [in] ARG Pointer to a geometry object (triangle)
    @return The second point of the triangle */
TgINLINE VEC_T(1)
FCN_VO(tgGM_PT_Query_Point_1)(
    VEC_OBJ_T(TgPTRI,CPCU) NONULL ARG );

/** @brief Return the third point of the triangle
    @param [in] ARG Pointer to a geometry object (triangle)
    @return The third point of the triangle */
TgINLINE VEC_T(1)
FCN_VO(tgGM_PT_Query_Point_2)(
    VEC_OBJ_T(TgPTRI,CPCU) NONULL ARG );

/** @brief Return the specified point
    @param [in,out] ARG0 Pointer to a geometry object (triangle)
    @param [in] ARG1 Point index [0-2]
    @return The specified point */
TgINLINE VEC_T(1)
FCN_VO(tgGM_PT_Query_Point)(
    VEC_OBJ_T(TgPTRI,CPCU) NONULL ARG0, TgRSIZE_C ARG1 );


/** @} TGS_COMMON_GEOMETRY_PT */

/* =============================================================================================================================================================================== */
#endif
