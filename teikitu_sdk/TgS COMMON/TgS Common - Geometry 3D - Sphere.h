/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Geometry 3D - Sphere.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_GEOMETRY_3D_SPHERE_H)

#if !defined (TEMPLATE_TYPE_EXPANSION__RELOAD)
    #error Must be included as part of a type expansion include chain
#endif


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @addtogroup TGS_COMMON_GEOMETRY_SP */
/** @{ */

/** @brief Invalidate the geometry object (sphere)
    @param [out] OUT Pointer to the geometry object (sphere) */
TgINLINE TgVOID
FCN_VO(tgGM_SP_Reset)(
    VEC_OBJ_T(TgSPHERE,PCU) TgANALYSIS_NO_NULL OUT );

/** @brief Validate the integrity of the geometry object (sphere)
    @param [in] ARG Pointer to a geometry object (sphere)
    @return True if the geometry object (sphere) is valid and false otherwise */
TgINLINE TgBOOL
FCN_VO(tgGM_SP_Is_Valid)(
    VEC_OBJ_T(TgSPHERE,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Determine the point on the geometry object (sphere) that is furthest along the direction of ARG1
    @param [in] ARG0 Pointer to a geometry object (sphere)
    @param [in] ARG1 Direction vector
    @return The point on the geometry object (sphere) that is furthest along the direction of ARG1 */
TgINLINE VEC_T(1)
FCN_VO(tgGM_SP_Support_Point)(
    VEC_OBJ_T(TgSPHERE,CPCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Calculate the volume of the geometry object (sphere)
    @param [in] ARG Pointer to a geometry object (sphere)
    @return The volume of the geometry object (sphere) */
TgINLINE VEC_T(1)
FCN_VO(tgGM_SP_Volume)(
    VEC_OBJ_T(TgSPHERE,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Calculate the surface area of the geometry object (sphere)
    @param [in] ARG Pointer to a geometry object (sphere)
    @return The surface area of the geometry object (sphere) */
TgINLINE VEC_T(1)
FCN_VO(tgGM_SP_Area)(
    VEC_OBJ_T(TgSPHERE,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Calculate the minimum necessary Axis-Aligned Bounding Box to contain the geometry object (sphere)
    @param [out] ARG0 Pointer to an axis-aligned bounding box object
    @param [in] ARG1 Pointer to a geometry object (sphere) */
TgINLINE TgVOID
FCN_VO(tgGM_SP_BA)(
    VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL ARG0, VEC_OBJ_T(TgSPHERE,CPCU) TgANALYSIS_NO_NULL ARG1 );

/** @brief Calculate the minimum necessary Axis-Aligned Bounding Box to contain the swept geometry object (sphere)
    @param [out] ARG0 Pointer to an axis-aligned bounding box object
    @param [in] ARG1 Pointer to a geometry object (sphere)
    @param [in] ARG2 Pointer to a vector describing the swept direction and magnitude */
TgINLINE TgVOID
FCN_VO(tgGM_SP_Sweep_BA)(
    VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL ARG0, VEC_OBJ_T(TgSPHERE,CPCU) TgANALYSIS_NO_NULL ARG1, VEC_T(1,C) ARG2 );

/** @brief Project the geometry object (sphere) along the direction vector
    @param [out] OUT0 Pointer to a scalar value to hold the lower bound of the projection
    @param [out] OUT1 Pointer to a scalar value to hold the upper bound of the projection
    @param [in] ARG2 Pointer to a geometry object (sphere)
    @param [in] ARG3 Direction vector */
TgINLINE TgVOID
FCN_VO(tgGM_SP_Project)(
    VEC_T(1,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,PCU) TgANALYSIS_NO_NULL ARG1, VEC_OBJ_T(TgSPHERE,CPCU) TgANALYSIS_NO_NULL ARG2, VEC_T(1,C) ARG3 );

/** @brief Test to see if a point is either on or in the geometry object (sphere)
    @param [in] ARG0 Pointer to a geometry object (sphere)
    @param [in] ARG1 Position vector
    @return True if the position is either on or in the geometry object (sphere) and false otherwise */
TgINLINE TgBOOL
FCN_VO(tgGM_SP_Is_Contained)(
    VEC_OBJ_T(TgSPHERE,CPCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Transform the geometry object (sphere) at ARG0 by the matrix at ARG1
    @param [in,out] ARG0 Pointer to a geometry object (sphere)
    @param [in] ARG1 Column-Major matrix (3x4) containing rotation and translation */
TgINLINE TgVOID
FCN_VO(tgGM_SP_TX)(
    VEC_OBJ_T(TgSPHERE,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(3,CPCU) TgANALYSIS_NO_NULL ARG1 );

/** @brief Transform the geometry object (sphere) at ARG1 by the matrix at ARG2 and store it in ARG0
    @param [out] ARG0 Pointer to a geometry object (sphere)
    @param [in] ARG1 Pointer to a geometry object (sphere)
    @param [in] ARG2 Column-Major matrix (3x4) containing rotation and translation */
TgINLINE TgVOID
FCN_VO(tgGM_SP_Copy_TX)(
    VEC_OBJ_T(TgSPHERE,PCU) TgANALYSIS_NO_NULL ARG0, VEC_OBJ_T(TgSPHERE,CPCU) TgANALYSIS_NO_NULL ARG1, VEC_T(3,CPCU) TgANALYSIS_NO_NULL ARG2 );


/** @brief Initialize a new geometry object (sphere) with the function arguments
    @param [out] ARG0 Pointer to a geometry object (sphere)
    @param [in] ARG1 Position vector - origin
    @param [in] ARG2 Vector holding the new radius, broadcast across all lanes */
TgINLINE TgVOID
FCN_VO(tgGM_SP_Init)(
    VEC_OBJ_T(TgSPHERE,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1, VEC_T(1,C) ARG2 );

/** @brief Copy the one geometry object (sphere) to another of the same type
    @param [out] ARG0 Pointer to a geometry object (sphere)
    @param [in] ARG1 Pointer to a geometry object (sphere) */
TgINLINE TgVOID
FCN_VO(tgGM_SP_Copy)(
    VEC_OBJ_T(TgSPHERE,PCU) TgANALYSIS_NO_NULL ARG0, VEC_OBJ_T(TgSPHERE,CPCU) TgANALYSIS_NO_NULL ARG1 );


/** @brief Set the origin
    @param [in,out] ARG0 Pointer to a geometry object (sphere)
    @param [in] ARG1 Position vector */
TgINLINE TgVOID
FCN_VO(tgGM_SP_Set_Origin)(
    VEC_OBJ_T(TgSPHERE,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Set the radius
    @param [in,out] ARG0 Pointer to a geometry object (sphere)
    @param [in] ARG1 Vector holding the new radius, broadcast across all lanes */
TgINLINE TgVOID
FCN_VO(tgGM_SP_Set_Radius)(
    VEC_OBJ_T(TgSPHERE,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1 );


/** @brief Return the origin
    @param [in] ARG Pointer to a geometry object (sphere)
    @return The origin */
TgINLINE VEC_T(1)
FCN_VO(tgGM_SP_Query_Origin)(
    VEC_OBJ_T(TgSPHERE,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Return the radius
    @param [in] ARG Pointer to a geometry object (sphere)
    @return The radius */
TgINLINE VEC_T(1)
FCN_VO(tgGM_SP_Query_Radius)(
    VEC_OBJ_T(TgSPHERE,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Return the radius squared
    @param [in] ARG Pointer to a geometry object (sphere)
    @return The radius squared */
TgINLINE VEC_T(1)
FCN_VO(tgGM_SP_Query_Radius_Sq)(
    VEC_OBJ_T(TgSPHERE,CPCU) TgANALYSIS_NO_NULL ARG );


/** @} TGS_COMMON_GEOMETRY_SP */

/* =============================================================================================================================================================================== */
#endif
