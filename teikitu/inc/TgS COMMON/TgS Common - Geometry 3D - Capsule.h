/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Geometry 3D - Capsule.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_GEOMETRY_3D_CAPSULE_H)

#if !defined (TEMPLATE_TYPE_EXPANSION__RELOAD)
    #error Must be included as part of a type expansion include chain
#endif


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @addtogroup TGS_COMMON_GEOMETRY_CP */
/** @{ */

/** @brief Determine the point on the geometry object (capsule) that is furthest along the direction of ARG1
    @param [in] ARG0 Pointer to a geometry object (capsule)
    @param [in] ARG1 Direction vector
    @return The point on the geometry object (capsule) that is furthest along the direction of ARG1 */
TgINLINE VEC_T(1)
FCN_VO(tgGM_CP_Support_Point)(
    VEC_OBJ_T(TgTUBE,CPCU) NONULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Calculate the volume of the geometry object (capsule)
    @param [in] ARG Pointer to a geometry object (capsule)
    @return The volume of the geometry object (capsule) */
TgINLINE VEC_T(1)
FCN_VO(tgGM_CP_Volume)(
    VEC_OBJ_T(TgTUBE,CPCU) NONULL ARG );

/** @brief Calculate the surface area of the geometry object (capsule)
    @param [in] ARG Pointer to a geometry object (capsule)
    @return The surface area of the geometry object (capsule) */
TgINLINE VEC_T(1)
FCN_VO(tgGM_CP_Area)(
    VEC_OBJ_T(TgTUBE,CPCU) NONULL ARG );

/** @brief Calculate the minimum necessary Axis-Aligned Bounding Box to contain the geometry object (capsule)
    @param [out] ARG0 Pointer to an axis-aligned bounding box object
    @param [in] ARG1 Pointer to a geometry object (capsule) */
TgINLINE TgVOID
FCN_VO(tgGM_CP_BA)(
    VEC_OBJ_T(TgBOXAA,PCU) NONULL ARG0, VEC_OBJ_T(TgTUBE,CPCU) NONULL ARG1 );

/** @brief Calculate the minimum necessary Axis-Aligned Bounding Box to contain the swept geometry object (capsule)
    @param [out] ARG0 Pointer to an axis-aligned bounding box object
    @param [in] ARG1 Pointer to a geometry object (capsule)
    @param [in] ARG2 Pointer to a vector describing the swept direction and magnitude */
TgINLINE TgVOID
FCN_VO(tgGM_CP_Sweep_BA)(
    VEC_OBJ_T(TgBOXAA,PCU) NONULL ARG0, VEC_OBJ_T(TgTUBE,CPCU) NONULL ARG1, VEC_T(1,C) ARG2 );

/** @brief Project the geometry object (capsule) along the direction vector
    @param [out] OUT0 Pointer to a scalar value to hold the lower bound of the projection
    @param [out] OUT1 Pointer to a scalar value to hold the upper bound of the projection
    @param [in] ARG2 Pointer to a geometry object (capsule)
    @param [in] ARG3 Direction vector */
TgINLINE TgVOID
FCN_VO(tgGM_CP_Project)(
    VEC_T(1,PCU) NONULL ARG0, VEC_T(1,PCU) NONULL ARG1, VEC_OBJ_T(TgTUBE,CPCU) NONULL ARG2, VEC_T(1,C) ARG3 );

/** @brief Test to see if a point is either on or in the geometry object (capsule)
    @param [in] ARG0 Pointer to a geometry object (capsule)
    @param [in] ARG1 Position vector
    @return True if the position is either on or in the geometry object (capsule) and false otherwise */
TgINLINE TgBOOL
FCN_VO(tgGM_CP_Is_Contained)(
    VEC_OBJ_T(TgTUBE,CPCU) NONULL ARG0, VEC_T(1,C) ARG1 );


/** @} TGS_COMMON_GEOMETRY_CP */

/* =============================================================================================================================================================================== */
#endif
