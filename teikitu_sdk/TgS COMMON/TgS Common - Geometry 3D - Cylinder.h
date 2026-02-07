/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Geometry 3D - Cylinder.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_GEOMETRY_3D_CYLINDER_H)

#if !defined (TEMPLATE_TYPE_EXPANSION__RELOAD)
    #error Must be included as part of a type expansion include chain
#endif


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @addtogroup TGS_COMMON_GEOMETRY_CY */
/** @{ */

/** @brief Determine the point on the geometry object (cylinder) that is furthest along the direction of ARG1
    @param [in] ARG0 Pointer to a geometry object (cylinder)
    @param [in] ARG1 Direction vector
    @return The point on the geometry object (cylinder) that is furthest along the direction of ARG1 */
TgEXTN VEC_T(1)
FCN_VO(tgGM_CY_Support_Point)(
    VEC_OBJ_T(TgTUBE,CPCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Calculate the volume of the geometry object (cylinder)
    @param [in] ARG Pointer to a geometry object (cylinder)
    @return The volume of the geometry object (cylinder) */
TgINLINE VEC_T(1)
FCN_VO(tgGM_CY_Volume)(
    VEC_OBJ_T(TgTUBE,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Calculate the surface area of the geometry object (cylinder)
    @param [in] ARG Pointer to a geometry object (cylinder)
    @return The surface area of the geometry object (cylinder) */
TgINLINE VEC_T(1)
FCN_VO(tgGM_CY_Area)(
    VEC_OBJ_T(TgTUBE,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Calculate the minimum necessary Axis-Aligned Bounding Box to contain the geometry object (cylinder)
    @param [out] ARG0 Pointer to an axis-aligned bounding box object
    @param [in] ARG1 Pointer to a geometry object (cylinder) */
TgINLINE TgVOID
FCN_VO(tgGM_CY_BA)(
    VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL ARG0, VEC_OBJ_T(TgTUBE,CPCU) TgANALYSIS_NO_NULL ARG1 );

/** @brief Calculate the minimum necessary Axis-Aligned Bounding Box to contain the swept geometry object (cylinder)
    @param [out] ARG0 Pointer to an axis-aligned bounding box object
    @param [in] ARG1 Pointer to a geometry object (cylinder)
    @param [in] ARG2 Pointer to a vector describing the swept direction and magnitude */
TgINLINE TgVOID
FCN_VO(tgGM_CY_Sweep_BA)(
    VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL ARG0, VEC_OBJ_T(TgTUBE,CPCU) TgANALYSIS_NO_NULL ARG1, VEC_T(1,C) ARG2 );

/** @brief Project the geometry object (cylinder) along the direction vector
    @param [out] OUT0 Pointer to a scalar value to hold the lower bound of the projection
    @param [out] OUT1 Pointer to a scalar value to hold the upper bound of the projection
    @param [in] ARG2 Pointer to a geometry object (cylinder)
    @param [in] ARG3 Direction vector */
TgINLINE TgVOID
FCN_VO(tgGM_CY_Project)(
    VEC_T(1,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,PCU) TgANALYSIS_NO_NULL ARG1, VEC_OBJ_T(TgTUBE,CPCU) TgANALYSIS_NO_NULL ARG2, VEC_T(1,C) ARG3 );

/** @brief Test to see if a point is either on or in the geometry object (cylinder)
    @param [in] ARG0 Pointer to a geometry object (cylinder)
    @param [in] ARG1 Position vector
    @return True if the position is either on or in the geometry object (cylinder) and false otherwise */
TgINLINE TgBOOL
FCN_VO(tgGM_CY_Is_Contained)(
    VEC_OBJ_T(TgTUBE,CPCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1 );


/** @} TGS_COMMON_GEOMETRY_CY */

/* =============================================================================================================================================================================== */
#endif
