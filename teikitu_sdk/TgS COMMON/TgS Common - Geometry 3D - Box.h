/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Geometry 3D - Box.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_GEOMETRY_3D_BOX_H)

#if !defined (TEMPLATE_TYPE_EXPANSION__RELOAD)
    #error Must be included as part of a type expansion include chain
#endif


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @addtogroup TGS_COMMON_GEOMETRY_BX */
/** @{ */

/** @brief Calculate a point along the basis vectors of the box
    @param [in] ARG0 Pointer to the geometry object (box)
    @param [in] ARG1 Vector holding the extent along the 1st basis vector, broadcast across all lanes
    @param [in] ARG2 Vector holding the extent along the 2nd basis vector, broadcast across all lanes
    @param [in] ARG3 Vector holding the extent along the 3rd basis vector, broadcast across all lanes
    @return The resulting point from the arguments and the box basis vectors */
TgINLINE VEC_T(1)
FCN_VO(tgGM_BX_Calc_Point)(
    VEC_OBJ_T(TgBOX,CPCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1, VEC_T(1,C) ARG2, VEC_T(1,C) ARG3 );

/** @brief Return one of the box's corner position
    @param [in] ARG0 Pointer to a geometry object (box)
    @param [in] ARG1 Integer value [0-7] to select a box corner
    @return The selected corner position of the box */
TgINLINE VEC_T(1)
FCN_VO(tgGM_BX_Calc_Point_Index)(
    VEC_OBJ_T(TgBOX,CPCU), TgRSIZE_C );

/** @brief Invalidate the geometry object (box)
    @param [out] OUT Pointer to the geometry object (box) */
TgINLINE TgVOID
FCN_VO(tgGM_BX_Reset)(
    VEC_OBJ_T(TgBOX,PCU) TgANALYSIS_NO_NULL OUT );

/** @brief Validate the integrity of the geometry object (box)
    @param [in] ARG Pointer to a geometry object (box)
    @return True if the geometry object (box) is valid and false otherwise */
TgINLINE TgBOOL
FCN_VO(tgGM_BX_Is_Valid)(
    VEC_OBJ_T(TgBOX,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Determine the point on the geometry object (box) that is furthest along the direction of ARG1
    @param [in] ARG0 Pointer to a geometry object (box)
    @param [in] ARG1 Direction vector
    @return The point on the geometry object (box) that is furthest along the direction of ARG1 */
TgINLINE VEC_T(1)
FCN_VO(tgGM_BX_Support_Point)(
    VEC_OBJ_T(TgBOX,CPCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Calculate the volume of the geometry object (box)
    @param [in] ARG Pointer to a geometry object (box)
    @return The volume of the geometry object (box) */
TgINLINE VEC_T(1)
FCN_VO(tgGM_BX_Volume)(
    VEC_OBJ_T(TgBOX,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Calculate the surface area of the geometry object (box)
    @param [in] ARG Pointer to a geometry object (box)
    @return The surface area of the geometry object (box) */
TgINLINE VEC_T(1)
FCN_VO(tgGM_BX_Area)(
    VEC_OBJ_T(TgBOX,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Calculate the minimum necessary Axis-Aligned Bounding Box to contain the geometry object (box)
    @param [out] ARG0 Pointer to an axis-aligned bounding box object
    @param [in] ARG1 Pointer to a geometry object (box) */
TgINLINE TgVOID
FCN_VO(tgGM_BX_BA)(
    VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL ARG0, VEC_OBJ_T(TgBOX,CPCU) TgANALYSIS_NO_NULL ARG1 );

/** @brief Calculate the minimum necessary Axis-Aligned Bounding Box to contain the swept geometry object (box)
    @param [out] ARG0 Pointer to an axis-aligned bounding box object
    @param [in] ARG1 Pointer to a geometry object (box)
    @param [in] ARG2 Pointer to a vector describing the swept direction and magnitude */
TgINLINE TgVOID
FCN_VO(tgGM_BX_Sweep_BA)(
    VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL ARG0, VEC_OBJ_T(TgBOX,CPCU) TgANALYSIS_NO_NULL ARG1, VEC_T(1,C) ARG2 );

/** @brief Project the geometry object (box) along the direction vector
    @param [out] OUT0 Pointer to a scalar value to hold the lower bound of the projection
    @param [out] OUT1 Pointer to a scalar value to hold the upper bound of the projection
    @param [in] ARG2 Pointer to a geometry object (box)
    @param [in] ARG3 Direction vector */
TgINLINE TgVOID
FCN_VO(tgGM_BX_Project)(
    VEC_T(1,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,PCU) TgANALYSIS_NO_NULL ARG1, VEC_OBJ_T(TgBOX,CPCU) TgANALYSIS_NO_NULL ARG2, VEC_T(1,C) ARG3 );

/** @brief Test to see if a point is either on or in the geometry object (box)
    @param [in] ARG0 Pointer to a geometry object (box)
    @param [in] ARG1 Position vector
    @return True if the position is either on or in the geometry object (box) and false otherwise */
TgINLINE TgBOOL
FCN_VO(tgGM_BX_Is_Contained)(
    VEC_OBJ_T(TgBOX,CPCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Transform the geometry object (box) at ARG0 by the matrix at ARG1
    @param [in,out] ARG0 Pointer to a geometry object (box)
    @param [in] ARG1 Column-Major matrix (3x4) containing rotation and translation */
TgINLINE TgVOID
FCN_VO(tgGM_BX_TX)(
    VEC_OBJ_T(TgBOX,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(3,CPCU) TgANALYSIS_NO_NULL ARG1 );

/** @brief Transform the geometry object (box) at ARG1 by the matrix at ARG2 and store it in ARG0
    @param [out] ARG0 Pointer to a geometry object (box)
    @param [in] ARG1 Pointer to a geometry object (box)
    @param [in] ARG2 Column-Major matrix (3x4) containing rotation and translation */
TgINLINE TgVOID
FCN_VO(tgGM_BX_Copy_TX)(
    VEC_OBJ_T(TgBOX,PCU) TgANALYSIS_NO_NULL ARG0, VEC_OBJ_T(TgBOX,CPCU) TgANALYSIS_NO_NULL ARG1, VEC_T(3,CPCU) TgANALYSIS_NO_NULL ARG2 );


/** @brief Initialize a new geometry object (box) with the function arguments
    @param [out] ARG0 Pointer to a geometry object (box)
    @param [in] ARG1 Column-Major matrix (3x4) containing rotation (basis vectors) and origin
    @param [in] ARG2 Vector - holds extent for first, second, and third axis */
TgINLINE TgVOID
FCN_VO(tgGM_BX_Init)(
    VEC_OBJ_T(TgBOX,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(3,CPCU) TgANALYSIS_NO_NULL ARG1, VEC_T(1,C) ARG2 );

/** @brief Copy the one geometry object (box) to another of the same type
    @param [out] ARG0 Pointer to a geometry object (box)
    @param [in] ARG1 Pointer to a geometry object (box) */
TgINLINE TgVOID
FCN_VO(tgGM_BX_Copy)(
    VEC_OBJ_T(TgBOX,PCU) TgANALYSIS_NO_NULL ARG0, VEC_OBJ_T(TgBOX,CPCU) TgANALYSIS_NO_NULL ARG1 );


/** @brief Set all three of the basis vectors and the origin
    @note Orthogonality of the basis vectors is the responsibility of the caller
    @param [in,out] ARG0 Pointer to a geometry object (box)
    @param [in] ARG1 Column-Major matrix (3x4) containing rotation (basis vectors) and origin */
TgINLINE TgVOID
FCN_VO(tgGM_BX_Set_Reference_Frame)(
    VEC_OBJ_T(TgBOX,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(3,CPCU) TgANALYSIS_NO_NULL ARG1 );

/** @brief Set the origin
    @param [in,out] ARG0 Pointer to a geometry object (box) */
TgINLINE TgVOID
FCN_VO(tgGM_BX_Set_Origin)(
    VEC_OBJ_T(TgBOX,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Set the extents along all three of the basis vectors
    @param [in,out] ARG0 Pointer to a geometry object (box)
    @param [in] ARG1 Vector holding the new extents, broadcast across all lanes */
TgINLINE TgVOID
FCN_VO(tgGM_BX_Set_Extent_List)(
    VEC_OBJ_T(TgBOX,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Set the extent along the specific basis vector
    @param [in,out] ARG0 Pointer to a geometry object (box)
    @param [in] ARG1 Basis vector index [0-2]
    @param [in] ARG2 Vector holding the new extent, broadcast across all lanes */
TgINLINE TgVOID
FCN_VO(tgGM_BX_Set_Extent_Index)(
    VEC_OBJ_T(TgBOX,PCU), TgRSIZE_C ARG0, VEC_T(1,C) ARG1 );

/** @brief Set the extent along the first basis vector
    @param [in,out] ARG0 Pointer to a geometry object (box)
    @param [in] ARG1 Vector holding the new extent, broadcast across all lanes */
TgINLINE TgVOID
FCN_VO(tgGM_BX_Set_Extent_0)(
    VEC_OBJ_T(TgBOX,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Set the extent along the second basis vector
    @param [in,out] ARG0 Pointer to a geometry object (box)
    @param [in] ARG1 Vector holding the new extent, broadcast across all lanes */
TgINLINE TgVOID
FCN_VO(tgGM_BX_Set_Extent_1)(
    VEC_OBJ_T(TgBOX,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Set the extent along the third basis vector
    @param [in,out] ARG0 Pointer to a geometry object (box)
    @param [in] ARG1 Vector holding the new extent, broadcast across all lanes */
TgINLINE TgVOID
FCN_VO(tgGM_BX_Set_Extent_2)(
    VEC_OBJ_T(TgBOX,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1 );


/** @brief Return the origin
    @param [in] ARG Pointer to a geometry object (box)
    @return The origin */
TgINLINE VEC_T(1)
FCN_VO(tgGM_BX_Query_Origin)(
    VEC_OBJ_T(TgBOX,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Return the first basis vector
    @param [in] ARG Pointer to a geometry object (box)
    @return The first basis vector */
TgINLINE VEC_T(1)
FCN_VO(tgGM_BX_Query_Axis_Unit_0)(
    VEC_OBJ_T(TgBOX,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Return the second basis vector
    @param [in] ARG Pointer to a geometry object (box)
    @return The second basis vector */
TgINLINE VEC_T(1)
FCN_VO(tgGM_BX_Query_Axis_Unit_1)(
    VEC_OBJ_T(TgBOX,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Return the third basis vector
    @param [in] ARG Pointer to a geometry object (box)
    @return The third basis vector */
TgINLINE VEC_T(1)
FCN_VO(tgGM_BX_Query_Axis_Unit_2)(
    VEC_OBJ_T(TgBOX,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Return a vector of all three extent values
    @param [in] ARG0 Pointer to a geometry object (box)
    @return A vector of all three extent values */
TgINLINE VEC_T(1)
FCN_VO(tgGM_BX_Query_Extent_List)(
    VEC_OBJ_T(TgBOX,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Return the extent along the specified basis vector
    @param [in,out] ARG0 Pointer to a geometry object (box)
    @param [in] ARG1 Basis vector index [0-2]
    @return The extent along the specified basis vector */
TgINLINE VEC_T(1)
FCN_VO(tgGM_BX_Query_Extent_Index)(
    VEC_OBJ_T(TgBOX,CPCU) TgANALYSIS_NO_NULL ARG0, TgRSIZE_C ARG1 );

/** @brief Return the extent along the first basis vector
    @param [in] ARG Pointer to a geometry object (box)
    @return The extent along the first basis vector */
TgINLINE VEC_T(1)
FCN_VO(tgGM_BX_Query_Extent_0)(
    VEC_OBJ_T(TgBOX,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Return the extent along the second basis vector
    @param [in] ARG Pointer to a geometry object (box)
    @return The extent along the second basis vector */
TgINLINE VEC_T(1)
FCN_VO(tgGM_BX_Query_Extent_1)(
    VEC_OBJ_T(TgBOX,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Return the extent along the third basis vector
    @param [in] ARG Pointer to a geometry object (box)
    @return The extent along the third basis vector */
TgINLINE VEC_T(1)
FCN_VO(tgGM_BX_Query_Extent_2)(
    VEC_OBJ_T(TgBOX,CPCU) TgANALYSIS_NO_NULL ARG );


/** @addtogroup TGS_COMMON_GEOMETRY_BX */
/** @{ */

/* =============================================================================================================================================================================== */
#endif
