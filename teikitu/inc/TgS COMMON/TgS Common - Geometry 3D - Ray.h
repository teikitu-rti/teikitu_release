/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Geometry 3D - Ray.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_GEOMETRY_3D_RAY_H)

#if !defined (TEMPLATE_TYPE_EXPANSION__RELOAD)
    #error Must be included as part of a type expansion include chain
#endif


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @addtogroup TGS_COMMON_GEOMETRY_RY */
/** @{ */

/** @brief Invalidate the geometry object (ray)
    @param [out] OUT Pointer to the geometry object (ray) */
TgINLINE TgVOID
FCN_VO(tgGM_RY_Reset)(
    VEC_OBJ_T(TgRAY,PCU) NONULL OUT );

/** @brief Validate the integrity of the geometry object (ray)
    @param [in] ARG Pointer to a geometry object (ray)
    @return True if the geometry object (ray) is valid and false otherwise */
TgINLINE TgBOOL
FCN_VO(tgGM_RY_Is_Valid)(
    VEC_OBJ_T(TgRAY,CPCU) NONULL ARG );

/** @brief Calculate the minimum necessary Axis-Aligned Bounding Box to contain the geometry object (ray)
    @param [out] ARG0 Pointer to an axis-aligned bounding box object
    @param [in] ARG1 Pointer to a geometry object (ray) */
TgINLINE TgVOID
FCN_VO(tgGM_RY_BA)(
    VEC_OBJ_T(TgBOXAA,PCU) NONULL ARG0, VEC_OBJ_T(TgRAY,CPCU) NONULL ARG1 );

/** @brief Calculate the minimum necessary Axis-Aligned Bounding Box to contain the swept geometry object (ray)
    @param [out] ARG0 Pointer to an axis-aligned bounding box object
    @param [in] ARG1 Pointer to a geometry object (ray)
    @param [in] ARG2 Pointer to a vector describing the swept direction and magnitude */
TgINLINE TgVOID
FCN_VO(tgGM_RY_Sweep_BA)(
    VEC_OBJ_T(TgBOXAA,PCU) NONULL ARG0, VEC_OBJ_T(TgRAY,CPCU) NONULL ARG1, VEC_T(1,C) ARG2 );

/** @brief Project the geometry object (ray) along the direction vector
    @param [out] OUT0 Pointer to a scalar value to hold the lower bound of the projection
    @param [out] OUT1 Pointer to a scalar value to hold the upper bound of the projection
    @param [in] ARG2 Pointer to a geometry object (ray)
    @param [in] ARG3 Direction vector */
TgINLINE TgVOID
FCN_VO(tgGM_RY_Project)(
    VEC_T(1,PCU) NONULL ARG0, VEC_T(1,PCU) NONULL ARG1, VEC_OBJ_T(TgRAY,CPCU) NONULL ARG2, VEC_T(1,C) ARG3 );

/** @brief Test to see if a point is either on or in the geometry object (ray)
    @param [in] ARG0 Pointer to a geometry object (ray)
    @param [in] ARG1 Position vector
    @return True if the position is either on or in the geometry object (ray) and false otherwise */
TgINLINE TgBOOL
FCN_VO(tgGM_RY_Is_Contained)(
    VEC_OBJ_T(TgRAY,CPCU) NONULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Transform the geometry object (ray) at ARG0 by the matrix at ARG1
    @param [in,out] ARG0 Pointer to a geometry object (ray)
    @param [in] ARG1 Column-Major matrix (3x4) containing rotation and translation */
TgINLINE TgVOID
FCN_VO(tgGM_RY_TX)(
    VEC_OBJ_T(TgRAY,PCU) NONULL ARG0, VEC_T(3,CPCU) NONULL ARG1 );

/** @brief Transform the geometry object (ray) at ARG1 by the matrix at ARG2 and store it in ARG0
    @param [out] ARG0 Pointer to a geometry object (ray)
    @param [in] ARG1 Pointer to a geometry object (ray)
    @param [in] ARG2 Column-Major matrix (3x4) containing rotation and translation */
TgINLINE TgVOID
FCN_VO(tgGM_RY_Copy_TX)(
    VEC_OBJ_T(TgRAY,PCU) NONULL ARG0, VEC_OBJ_T(TgRAY,CPCU) NONULL ARG1, VEC_T(3,CPCU) NONULL ARG2 );


/** @brief Initialize a new geometry object (disk) with the function arguments
    @param [out] ARG0 Pointer to a geometry object (disk)
    @param [in] ARG1 Position vector - origin (start) of the ray
    @param [in] ARG2 Direction unit vector - direction of the ray */
TgINLINE TgVOID
FCN_VO(tgGM_RY_Init)(
    VEC_OBJ_T(TgRAY,PCU) NONULL ARG0, VEC_T(1,C) ARG1, VEC_T(1,C) ARG2 );

/** @brief Copy the one geometry object (ray) to another of the same type
    @param [out] ARG0 Pointer to a geometry object (ray)
    @param [in] ARG1 Pointer to a geometry object (ray) */
TgINLINE TgVOID
FCN_VO(tgGM_RY_Copy)(
    VEC_OBJ_T(TgRAY,PCU) NONULL ARG0, VEC_OBJ_T(TgRAY,CPCU) NONULL ARG1 );


/** @brief Set the origin
    @param [in,out] ARG0 Pointer to a geometry object (ray)
    @param [in] ARG1 Position vector - origin (start) of the ray */
TgINLINE TgVOID
FCN_VO(tgGM_RY_Set_Origin)(
    VEC_OBJ_T(TgRAY,PCU) NONULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Set the direction of the ray
    @param [in,out] ARG0 Pointer to a geometry object (ray)
    @param [in] ARG1 Direction unit vector - direction of the ray */
TgINLINE TgVOID
FCN_VO(tgGM_RY_Set_DirN)(
    VEC_OBJ_T(TgRAY,PCU) NONULL ARG0, VEC_T(1,C) ARG1 );


/** @brief Return the origin
    @param [in] ARG Pointer to a geometry object (ray)
    @return The origin */
TgINLINE VEC_T(1)
FCN_VO(tgGM_RY_Query_Origin)(
    VEC_OBJ_T(TgRAY,CPCU) NONULL ARG );

/** @brief Return the direction of the ray
    @param [in] ARG Pointer to a geometry object (ray)
    @return The direction of the ray */
TgINLINE VEC_T(1)
FCN_VO(tgGM_RY_Query_DirN)(
    VEC_OBJ_T(TgRAY,CPCU) NONULL ARG );


/** @} TGS_COMMON_GEOMETRY_RY */

/* =============================================================================================================================================================================== */
#endif
