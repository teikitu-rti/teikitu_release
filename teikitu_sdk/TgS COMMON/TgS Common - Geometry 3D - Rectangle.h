/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Geometry 3D - Rectangle.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_GEOMETRY_3D_RECTANGLE_H)

#if !defined (TEMPLATE_TYPE_EXPANSION__RELOAD)
    #error Must be included as part of a type expansion include chain
#endif


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @addtogroup TGS_COMMON_GEOMETRY_RT */
/** @{ */

/** @brief Invalidate the geometry object (rectangle)
    @param [out] OUT Pointer to the geometry object (rectangle) */
TgINLINE TgVOID
FCN_VO(tgGM_RT_Reset)(
    VEC_OBJ_T(TgRECTANGLE,PCU) TgANALYSIS_NO_NULL OUT );

/** @brief Validate the integrity of the geometry object (rectangle)
    @param [in] ARG Pointer to a geometry object (rectangle)
    @return True if the geometry object (rectangle) is valid and false otherwise */
TgINLINE TgBOOL
FCN_VO(tgGM_RT_Is_Valid)(
    VEC_OBJ_T(TgRECTANGLE,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Determine the point on the geometry object (rectangle) that is furthest along the direction of ARG1
    @param [in] ARG0 Pointer to a geometry object (rectangle)
    @param [in] ARG1 Direction vector
    @return The point on the geometry object (rectangle) that is furthest along the direction of ARG1 */
TgINLINE VEC_T(1)
FCN_VO(tgGM_RT_Support_Point)(
    VEC_OBJ_T(TgRECTANGLE,CPCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Calculate the surface area of the geometry object (rectangle)
    @param [in] ARG Pointer to a geometry object (rectangle)
    @return The surface area of the geometry object (rectangle) */
TgINLINE VEC_T(1)
FCN_VO(tgGM_RT_Area)(
    VEC_OBJ_T(TgRECTANGLE,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Calculate the minimum necessary Axis-Aligned Bounding Box to contain the geometry object (rectangle)
    @param [out] ARG0 Pointer to an axis-aligned bounding box object
    @param [in] ARG1 Pointer to a geometry object (rectangle) */
TgINLINE TgVOID
FCN_VO(tgGM_RT_BA)(
    VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL ARG0, VEC_OBJ_T(TgRECTANGLE,CPCU) TgANALYSIS_NO_NULL ARG1 );

/** @brief Calculate the minimum necessary Axis-Aligned Bounding Box to contain the swept geometry object (rectangle)
    @param [out] ARG0 Pointer to an axis-aligned bounding box object
    @param [in] ARG1 Pointer to a geometry object (rectangle)
    @param [in] ARG2 Pointer to a vector describing the swept direction and magnitude */
TgINLINE TgVOID
FCN_VO(tgGM_RT_Sweep_BA)(
    VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL ARG0, VEC_OBJ_T(TgRECTANGLE,CPCU) TgANALYSIS_NO_NULL ARG1, VEC_T(1,C) ARG2 );

/** @brief Project the geometry object (rectangle) along the direction vector
    @param [out] OUT0 Pointer to a scalar value to hold the lower bound of the projection
    @param [out] OUT1 Pointer to a scalar value to hold the upper bound of the projection
    @param [in] ARG2 Pointer to a geometry object (rectangle)
    @param [in] ARG3 Direction vector */
TgINLINE TgVOID
FCN_VO(tgGM_RT_Project)(
    VEC_T(1,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,PCU) TgANALYSIS_NO_NULL ARG1, VEC_OBJ_T(TgRECTANGLE,CPCU) TgANALYSIS_NO_NULL ARG2, VEC_T(1,C) ARG3 );

/** @brief Test to see if a point is either on or in the geometry object (rectangle)
    @param [in] ARG0 Pointer to a geometry object (rectangle)
    @param [in] ARG1 Position vector
    @return True if the position is either on or in the geometry object (rectangle) and false otherwise */
TgINLINE TgBOOL
FCN_VO(tgGM_RT_Is_Contained)(
    VEC_OBJ_T(TgRECTANGLE,CPCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Transform the geometry object (rectangle) at ARG0 by the matrix at ARG1
    @param [in,out] ARG0 Pointer to a geometry object (rectangle)
    @param [in] ARG1 Column-Major matrix (3x4) containing rotation and translation */
TgINLINE TgVOID
FCN_VO(tgGM_RT_TX)(
    VEC_OBJ_T(TgRECTANGLE,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(3,CPCU) TgANALYSIS_NO_NULL ARG1 );

/** @brief Transform the geometry object (rectangle) at ARG1 by the matrix at ARG2 and store it in ARG0
    @param [out] ARG0 Pointer to a geometry object (rectangle)
    @param [in] ARG1 Pointer to a geometry object (rectangle)
    @param [in] ARG2 Column-Major matrix (3x4) containing rotation and translation */
TgINLINE TgVOID
FCN_VO(tgGM_RT_Copy_TX)(
    VEC_OBJ_T(TgRECTANGLE,PCU) TgANALYSIS_NO_NULL ARG0, VEC_OBJ_T(TgRECTANGLE,CPCU) TgANALYSIS_NO_NULL ARG1, VEC_T(3,CPCU) TgANALYSIS_NO_NULL ARG2);


/** @brief Initialize a new geometry object (rectangle) with the function arguments
    @note Orthogonality of the edge vectors is the responsibility of the caller
    @param [out] ARG0 Pointer to a geometry object (rectangle)
    @param [in] ARG1 - Position vector - origin
    @param [in] ARG2 - Direction vector - direction and length of the first edge
    @param [in] ARG3 - Direction vector - direction and length of the second edge
    @param [in] ARG3 - Direction vector - normal of the plane of the rectangle */
TgINLINE TgVOID
FCN_VO(tgGM_RT_Init_SEN)(
    VEC_OBJ_T(TgRECTANGLE,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1, VEC_T(1,C) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4 );

/** @brief Initialize a new geometry object (rectangle) with the function arguments
    @note Orthogonality of the edge vectors is the responsibility of the caller
    @param [out] ARG0 Pointer to a geometry object (rectangle)
    @param [in] ARG1 - Position vector - origin
    @param [in] ARG2 - Direction vector - direction and length of the first edge
    @param [in] ARG3 - Direction vector - direction and length of the second edge */
TgINLINE TgVOID
FCN_VO(tgGM_RT_Init_SE)(
    VEC_OBJ_T(TgRECTANGLE,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1, VEC_T(1,C) ARG2, VEC_T(1,C) ARG3 );

/** @brief Copy the one geometry object (rectangle) to another of the same type
    @param [out] ARG0 Pointer to a geometry object (rectangle)
    @param [in] ARG1 Pointer to a geometry object (rectangle) */
TgINLINE TgVOID
FCN_VO(tgGM_RT_Copy)(
    VEC_OBJ_T(TgRECTANGLE,PCU) TgANALYSIS_NO_NULL ARG0, VEC_OBJ_T(TgRECTANGLE,CPCU) TgANALYSIS_NO_NULL ARG1 );


/** @brief Set the origin
    @param [in,out] ARG0 Pointer to a geometry object (rectangle)
    @param [in] ARG1 Position vector */
TgINLINE TgVOID
FCN_VO(tgGM_RT_Set_Origin)(
    VEC_OBJ_T(TgRECTANGLE,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Set the direction and length of the two edge vectors
    @param [in,out] ARG0 Pointer to a geometry object (rectangle)
    @param [in] ARG1 Direction vector - Direction and length of the edge (1/2)
    @param [in] ARG2 Direction vector - Direction and length of the edge (2/2) */
TgINLINE TgVOID
FCN_VO(tgGM_RT_Set_Edge)(
    VEC_OBJ_T(TgRECTANGLE,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1, VEC_T(1,C) ARG2 );

/** @brief Set the direction and length of the edge and normal
    @param [in,out] ARG0 Pointer to a geometry object (rectangle)
    @param [in] ARG1 Direction vector - Direction and length of the edge (1/2)
    @param [in] ARG2 Direction vector - Direction and length of the edge (2/2)
    @param [in] ARG3 Direction vector - Unit normal to the plane defined by the two edge vectors */
TgINLINE TgVOID
FCN_VO(tgGM_RT_Set_Edge_Normal)(
    VEC_OBJ_T(TgRECTANGLE,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1, VEC_T(1,C) ARG2, VEC_T(1,C) ARG3 );


/** @brief Return the origin
    @param [in] ARG Pointer to a geometry object (rectangle)
    @return The origin */
TgINLINE VEC_T(1)
FCN_VO(tgGM_RT_Query_Origin)(
    VEC_OBJ_T(TgRECTANGLE,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Return the direction and length of the first edge
    @param [in] ARG Pointer to a geometry object (rectangle)
    @return The direction and length of the first edge */
TgINLINE VEC_T(1)
FCN_VO(tgGM_RT_Query_Edge_0)(
    VEC_OBJ_T(TgRECTANGLE,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Return the direction and length of the second edge
    @param [in] ARG Pointer to a geometry object (rectangle)
    @return The direction and length of the second edge */
TgINLINE VEC_T(1)
FCN_VO(tgGM_RT_Query_Edge_1)(
    VEC_OBJ_T(TgRECTANGLE,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Return the normal of the plane
    @param [in] ARG Pointer to a geometry object (rectangle)
    @return The normal of the plane */
TgINLINE VEC_T(1)
FCN_VO(tgGM_RT_Query_Normal)(
    VEC_OBJ_T(TgRECTANGLE,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Return the first point of the rectangle
    @param [in] ARG Pointer to a geometry object (rectangle)
    @return The first point of the rectangle */
TgINLINE VEC_T(1)
FCN_VO(tgGM_RT_Query_Point_0)(
    VEC_OBJ_T(TgRECTANGLE,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Return the second point of the rectangle
    @param [in] ARG Pointer to a geometry object (rectangle)
    @return The second point of the rectangle */
TgINLINE VEC_T(1)
FCN_VO(tgGM_RT_Query_Point_1)(
    VEC_OBJ_T(TgRECTANGLE,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Return the third point of the rectangle
    @param [in] ARG Pointer to a geometry object (rectangle)
    @return The third point of the rectangle */
TgINLINE VEC_T(1)
FCN_VO(tgGM_RT_Query_Point_2)(
    VEC_OBJ_T(TgRECTANGLE,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Return the fourth point of the rectangle
    @param [in] ARG Pointer to a geometry object (rectangle)
    @return The fourth point of the rectangle */
TgINLINE VEC_T(1)
FCN_VO(tgGM_RT_Query_Point_3)(
    VEC_OBJ_T(TgRECTANGLE,CPCU) TgANALYSIS_NO_NULL ARG );


/** @} TGS_COMMON_GEOMETRY_RT */

/* =============================================================================================================================================================================== */
#endif
