/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Geometry 3D - Torus.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_GEOMETRY_3D_TORUS_H)

#if !defined (TEMPLATE_TYPE_EXPANSION__RELOAD)
    #error Must be included as part of a type expansion include chain
#endif


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @addtogroup TGS_COMMON_GEOMETRY_TS */
/** @{ */

/** @brief Invalidate the geometry object (torus)
    @param [out] OUT Pointer to the geometry object (torus) */
TgINLINE TgVOID
FCN_VO(tgGM_TS_Reset)(
    VEC_OBJ_T(TgTORUS,PCU) TgANALYSIS_NO_NULL OUT );

/** @brief Validate the integrity of the geometry object (torus)
    @param [in] ARG Pointer to a geometry object (torus)
    @return True if the geometry object (torus) is valid and false otherwise */
TgEXTN TgBOOL
FCN_VO(tgGM_TS_Is_Valid)(
    VEC_OBJ_T(TgTORUS,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Determine the point on the geometry object (torus) that is furthest along the direction of ARG1
    @param [in] ARG0 Pointer to a geometry object (torus)
    @param [in] ARG1 Direction vector
    @return The point on the geometry object (torus) that is furthest along the direction of ARG1 */
TgEXTN VEC_T(1)
FCN_VO(tgGM_TS_Support_Point)(
    VEC_OBJ_T(TgTORUS,CPCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Calculate the volume of the geometry object (torus)
    @param [in] ARG Pointer to a geometry object (torus)
    @return The volume of the geometry object (torus) */
TgINLINE VEC_T(1)
FCN_VO(tgGM_TS_Volume)(
    VEC_OBJ_T(TgTORUS,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Calculate the surface area of the geometry object (torus)
    @param [in] ARG Pointer to a geometry object (torus)
    @return The surface area of the geometry object (torus) */
TgINLINE VEC_T(1)
FCN_VO(tgGM_TS_Area)(
    VEC_OBJ_T(TgTORUS,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Calculate the minimum necessary Axis-Aligned Bounding Box to contain the geometry object (torus)
    @param [out] ARG0 Pointer to an axis-aligned bounding box object
    @param [in] ARG1 Pointer to a geometry object (torus) */
TgEXTN TgVOID
FCN_VO(tgGM_TS_BA)(
    VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL ARG0, VEC_OBJ_T(TgTORUS,CPCU) TgANALYSIS_NO_NULL ARG1 );

/** @brief Calculate the minimum necessary Axis-Aligned Bounding Box to contain the swept geometry object (torus)
    @param [out] ARG0 Pointer to an axis-aligned bounding box object
    @param [in] ARG1 Pointer to a geometry object (torus)
    @param [in] ARG2 Pointer to a vector describing the swept direction and magnitude */
TgINLINE TgVOID
FCN_VO(tgGM_TS_Sweep_BA)(
    VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL ARG0, VEC_OBJ_T(TgTORUS,CPCU) TgANALYSIS_NO_NULL ARG1, VEC_T(1,C) ARG2 );

/** @brief Project the geometry object (torus) along the direction vector
    @param [out] OUT0 Pointer to a scalar value to hold the lower bound of the projection
    @param [out] OUT1 Pointer to a scalar value to hold the upper bound of the projection
    @param [in] ARG2 Pointer to a geometry object (torus)
    @param [in] ARG3 Direction vector */
TgEXTN TgVOID
FCN_VO(tgGM_TS_Project)(
    VEC_T(1,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,PCU) TgANALYSIS_NO_NULL ARG1, VEC_OBJ_T(TgTORUS,CPCU) TgANALYSIS_NO_NULL ARG2, VEC_T(1,C) ARG3 );

/** @brief Test to see if a point is either on or in the geometry object (torus)
    @param [in] ARG0 Pointer to a geometry object (torus)
    @param [in] ARG1 Position vector
    @return True if the position is either on or in the geometry object (torus) and false otherwise */
TgEXTN TgBOOL
FCN_VO(tgGM_TS_Is_Contained)(
    VEC_OBJ_T(TgTORUS,CPCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Transform the geometry object (torus) at ARG0 by the matrix at ARG1
    @param [in,out] ARG0 Pointer to a geometry object (torus)
    @param [in] ARG1 Column-Major matrix (3x4) containing rotation and translation */
TgINLINE TgVOID
FCN_VO(tgGM_TS_TX)(
    VEC_OBJ_T(TgTORUS,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(3,CPCU) TgANALYSIS_NO_NULL ARG1 );

/** @brief Transform the geometry object (torus) at ARG1 by the matrix at ARG2 and store it in ARG0
    @param [out] ARG0 Pointer to a geometry object (torus)
    @param [in] ARG1 Pointer to a geometry object (torus)
    @param [in] ARG2 Column-Major matrix (3x4) containing rotation and translation */
TgINLINE TgVOID
FCN_VO(tgGM_TS_Copy_TX)(
    VEC_OBJ_T(TgTORUS,PCU) TgANALYSIS_NO_NULL ARG0, VEC_OBJ_T(TgTORUS,CPCU) TgANALYSIS_NO_NULL ARG1, VEC_T(3,CPCU) TgANALYSIS_NO_NULL ARG2 );


/** @brief Initialize a new geometry object (torus) with the function arguments
    @param [out] ARG0 Pointer to a geometry object (torus)
    @param [in] ARG1 Column-Major matrix (3x4) containing rotation (basis vectors) and origin
    @param [in] ARG2 Vector holding the new inner radius (radius of the torus-tube), broadcast across all lanes
    @param [in] ARG3 Vector holding the new outer radius, broadcast across all lanes */
TgINLINE TgVOID
FCN_VO(tgGM_TS_Init)(
    VEC_OBJ_T(TgTORUS,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(3,CPCU) TgANALYSIS_NO_NULL ARG1, VEC_T(1,C) ARG2, VEC_T(1,C) ARG3 );

/** @brief Copy the one geometry object (torus) to another of the same type
    @param [out] ARG0 Pointer to a geometry object (torus)
    @param [in] ARG1 Pointer to a geometry object (torus) */
TgINLINE TgVOID
FCN_VO(tgGM_TS_Copy)(
    VEC_OBJ_T(TgTORUS,PCU) TgANALYSIS_NO_NULL ARG0, VEC_OBJ_T(TgTORUS,CPCU) TgANALYSIS_NO_NULL ARG1 );


/** @brief Set the normal of the plane
    @param [in,out] ARG0 Pointer to a geometry object (torus)
    @param [in] ARG1 Column-Major matrix (3x4) containing rotation (basis vectors) and origin */
TgINLINE TgVOID
FCN_VO(tgGM_TS_Set_Reference_Frame)(
    VEC_OBJ_T(TgTORUS,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(3,CPCU) TgANALYSIS_NO_NULL ARG1 );

/** @brief Set the origin
    @param [in,out] ARG0 Pointer to a geometry object (torus)
    @param [in] ARG1 Position vector */
TgINLINE TgVOID
FCN_VO(tgGM_TS_Set_Origin)(
    VEC_OBJ_T(TgTORUS,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Set the inner radius
    @param [in,out] ARG0 Pointer to a geometry object (torus)
    @param [in] ARG1 Vector holding the new radius, broadcast across all lanes */
TgINLINE TgVOID
FCN_VO(tgGM_TS_Set_Inner_Radius)(
    VEC_OBJ_T(TgTORUS,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Set the outer radius
    @param [in,out] ARG0 Pointer to a geometry object (torus)
    @param [in] ARG1 Vector holding the new radius, broadcast across all lanes */
TgINLINE TgVOID
FCN_VO(tgGM_TS_Set_Outer_Radius)(
    VEC_OBJ_T(TgTORUS,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1 );


/** @brief Return the origin
    @param [in] ARG Pointer to a geometry object (torus)
    @return The origin */
TgINLINE VEC_T(1)
FCN_VO(tgGM_TS_Query_Origin)(
    VEC_OBJ_T(TgTORUS,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Return the normal of the plane
    @param [in] ARG Pointer to a geometry object (torus)
    @return The normal of the plane */
TgINLINE VEC_T(1)
FCN_VO(tgGM_TS_Query_Normal)(
    VEC_OBJ_T(TgTORUS,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Return the inner radius
    @param [in] ARG Pointer to a geometry object (torus)
    @return The inner radius */
TgINLINE VEC_T(1)
FCN_VO(tgGM_TS_Query_Inner_Radius)(
    VEC_OBJ_T(TgTORUS,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Return the outer radius
    @param [in] ARG Pointer to a geometry object (torus)
    @return The outer radius */
TgINLINE VEC_T(1)
FCN_VO(tgGM_TS_Query_Outer_Radius)(
    VEC_OBJ_T(TgTORUS,CPCU) TgANALYSIS_NO_NULL ARG );


/** @} TGS_COMMON_GEOMETRY_TS */

/* =============================================================================================================================================================================== */
#endif
