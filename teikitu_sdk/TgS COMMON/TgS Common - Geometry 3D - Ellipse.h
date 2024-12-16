/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Geometry 3D - Ellipse.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_GEOMETRY_3D_ELLIPSE_H)

#if !defined (TEMPLATE_TYPE_EXPANSION__RELOAD)
    #error Must be included as part of a type expansion include chain
#endif


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @addtogroup TGS_COMMON_GEOMETRY_EL */
/** @{ */

/** @brief Invalidate the geometry object (ellipse)
    @param [out] OUT Pointer to the geometry object (ellipse) */
TgINLINE TgVOID
FCN_VO(tgGM_EL_Reset)(
    VEC_OBJ_T(TgELLIPSE,PCU) TgANALYSIS_NO_NULL OUT );

/** @brief Validate the integrity of the geometry object (ellipse)
    @param [in] ARG Pointer to a geometry object (ellipse)
    @return True if the geometry object (ellipse) is valid and false otherwise */
TgEXTN TgBOOL
FCN_VO(tgGM_EL_Is_Valid)(
    VEC_OBJ_T(TgELLIPSE,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Determine the point on the geometry object (ellipse) that is furthest along the direction of ARG1
    @param [in] ARG0 Pointer to a geometry object (ellipse)
    @param [in] ARG1 Direction vector
    @return The point on the geometry object (ellipse) that is furthest along the direction of ARG1 */
TgEXTN VEC_T(1)
FCN_VO(tgGM_EL_Support_Point)(
    VEC_OBJ_T(TgELLIPSE,CPCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Calculate the surface area of the geometry object (ellipse)
    @param [in] ARG Pointer to a geometry object (ellipse)
    @return The surface area of the geometry object (ellipse) */
TgINLINE VEC_T(1)
FCN_VO(tgGM_EL_Area)(
    VEC_OBJ_T(TgELLIPSE,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Calculate the minimum necessary Axis-Aligned Bounding Box to contain the geometry object (ellipse)
    @param [out] ARG0 Pointer to an axis-aligned bounding box object
    @param [in] ARG1 Pointer to a geometry object (ellipse) */
TgINLINE TgVOID
FCN_VO(tgGM_EL_BA)(
    VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL ARG0, VEC_OBJ_T(TgELLIPSE,CPCU) TgANALYSIS_NO_NULL ARG1 );

/** @brief Calculate the minimum necessary Axis-Aligned Bounding Box to contain the swept geometry object (ellipse)
    @param [out] ARG0 Pointer to an axis-aligned bounding box object
    @param [in] ARG1 Pointer to a geometry object (ellipse)
    @param [in] ARG2 Pointer to a vector describing the swept direction and magnitude */
TgINLINE TgVOID
FCN_VO(tgGM_EL_Sweep_BA)(
    VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL ARG0, VEC_OBJ_T(TgELLIPSE,CPCU) TgANALYSIS_NO_NULL ARG1, VEC_T(1,C) ARG2 );

/** @brief Project the geometry object (ellipse) along the direction vector
    @param [out] OUT0 Pointer to a scalar value to hold the lower bound of the projection
    @param [out] OUT1 Pointer to a scalar value to hold the upper bound of the projection
    @param [in] ARG2 Pointer to a geometry object (ellipse)
    @param [in] ARG3 Direction vector */
TgINLINE TgVOID
FCN_VO(tgGM_EL_Project)(
    VEC_T(1,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,PCU) TgANALYSIS_NO_NULL ARG1, VEC_OBJ_T(TgELLIPSE,CPCU) TgANALYSIS_NO_NULL ARG2, VEC_T(1,C) ARG3);

/** @brief Test to see if a point is either on or in the geometry object (ellipse)
    @param [in] ARG0 Pointer to a geometry object (ellipse)
    @param [in] ARG1 Position vector
    @return True if the position is either on or in the geometry object (ellipse) and false otherwise */
TgINLINE TgBOOL
FCN_VO(tgGM_EL_Is_Contained)(
    VEC_OBJ_T(TgELLIPSE,CPCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Transform the geometry object (ellipse) at ARG0 by the matrix at ARG1
    @param [in,out] ARG0 Pointer to a geometry object
    @param [in] ARG1 Column-Major matrix (3x4) containing rotation and translation */
TgINLINE TgVOID
FCN_VO(tgGM_EL_TX)(
    VEC_OBJ_T(TgELLIPSE,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(3,CPCU) TgANALYSIS_NO_NULL ARG1 );

/** @brief Transform the geometry object (ellipse) at ARG1 by the matrix at ARG2 and store it in ARG0
    @param [out] ARG0 Pointer to a geometry object (ellipse)
    @param [in] ARG1 Pointer to a geometry object (ellipse)
    @param [in] ARG2 Column-Major matrix (3x4) containing rotation and translation */
TgINLINE TgVOID
FCN_VO(tgGM_EL_Copy_TX)(
    VEC_OBJ_T(TgELLIPSE,PCU) TgANALYSIS_NO_NULL ARG0, VEC_OBJ_T(TgELLIPSE,CPCU) TgANALYSIS_NO_NULL ARG1, VEC_T(3,CPCU) TgANALYSIS_NO_NULL ARG2 );


/** @brief Initialize a new geometry object (ellipse) with the function arguments
    @param [out] ARG0 Pointer to a geometry object (ellipse)
    @param [in] ARG1 Column-Major matrix (3x4) containing rotation (basis vectors) and origin
    @param [in] ARG2 Vector holding the new major radius, broadcast across all lanes
    @param [in] ARG3 Vector holding the new minor radius, broadcast across all lanes */
TgINLINE TgVOID
FCN_VO(tgGM_EL_Init)(
    VEC_OBJ_T(TgELLIPSE,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(3,CPCU) TgANALYSIS_NO_NULL ARG1, VEC_T(1,C) ARG2, VEC_T(1,C) ARG3 );

/** @brief Copy the one geometry object (ellipse) to another of the same type
    @param [out] ARG0 Pointer to a geometry object (ellipse)
    @param [in] ARG1 Pointer to a geometry object (ellipse) */
TgINLINE TgVOID
FCN_VO(tgGM_EL_Copy)(
    VEC_OBJ_T(TgELLIPSE,PCU) TgANALYSIS_NO_NULL ARG0, VEC_OBJ_T(TgELLIPSE,CPCU) TgANALYSIS_NO_NULL ARG1 );


/** @brief Set all three of the basis vectors and the origin
    @note Orthogonality of the basis vectors is the responsibility of the caller
    @param [in,out] ARG0 Pointer to a geometry object (ellipse)
    @param [in] ARG1 Column-Major matrix (3x4) containing rotation (basis vectors) and origin */
TgINLINE TgVOID
FCN_VO(tgGM_EL_Set_Reference_Frame)(
    VEC_OBJ_T(TgELLIPSE,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(3,CPCU) TgANALYSIS_NO_NULL ARG1 );

/** @brief Set the origin
    @param [in,out] ARG0 Pointer to a geometry object (ellipse)
    @param [in] ARG1 Position vector */
TgINLINE TgVOID
FCN_VO(tgGM_EL_Set_Origin)(
    VEC_OBJ_T(TgELLIPSE,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Set the major radius
    @param [in,out] ARG0 Pointer to a geometry object (ellipse)
    @param [in] ARG1 Vector holding the new radius, broadcast across all lanes */
TgINLINE TgVOID
FCN_VO(tgGM_EL_Set_Major_Radius)(
    VEC_OBJ_T(TgELLIPSE,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Set the minor radius
    @param [in,out] ARG0 Pointer to a geometry object (ellipse)
    @param [in] ARG1 Vector holding the new radius, broadcast across all lanes */
TgINLINE TgVOID
FCN_VO(tgGM_EL_Set_Minor_Radius)(
    VEC_OBJ_T(TgELLIPSE,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1 );


/** @brief Return the origin
    @param [in] ARG Pointer to a geometry object (ellipse)
    @return The origin */
TgINLINE VEC_T(1)
FCN_VO(tgGM_EL_Query_Origin)(
    VEC_OBJ_T(TgELLIPSE,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Return the first basis vector (major axis) on the plane
    @param [in] ARG Pointer to a geometry object (ellipse)
    @return The first basis vector (major axis) on the plane */
TgINLINE VEC_T(1)
FCN_VO(tgGM_EL_Query_Major_Unit)(
    VEC_OBJ_T(TgELLIPSE,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Return the normal of the plane
    @param [in] ARG Pointer to a geometry object (ellipse)
    @return The normal of the plane */
TgINLINE VEC_T(1)
FCN_VO(tgGM_EL_Query_Normal)(
    VEC_OBJ_T(TgELLIPSE,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Return the second basis vector (minor axis) on the plane
    @param [in] ARG Pointer to a geometry object (ellipse)
    @return The second basis vector (minor axis) on the plane */
TgINLINE VEC_T(1)
FCN_VO(tgGM_EL_Query_Minor_Unit)(
    VEC_OBJ_T(TgELLIPSE,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Return the major radius
    @param [in] ARG Pointer to a geometry object (ellipse)
    @return The major radius */
TgINLINE VEC_T(1)
FCN_VO(tgGM_EL_Query_Major_Radius)(
    VEC_OBJ_T(TgELLIPSE,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Return the minor radius
    @param [in] ARG Pointer to a geometry object (ellipse)
    @return The minor radius */
TgINLINE VEC_T(1)
FCN_VO(tgGM_EL_Query_Minor_Radius)(
    VEC_OBJ_T(TgELLIPSE,CPCU) TgANALYSIS_NO_NULL ARG );


/** @} TGS_COMMON_GEOMETRY_EL */

/* =============================================================================================================================================================================== */
#endif
