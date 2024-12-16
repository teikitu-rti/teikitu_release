/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Geometry 3D - Plane.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_GEOMETRY_3D_PLANE_H)

#if !defined (TEMPLATE_TYPE_EXPANSION__RELOAD)
    #error Must be included as part of a type expansion include chain
#endif


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @addtogroup TGS_COMMON_GEOMETRY_PN */
/** @{ */

/** @brief Negate the normal of the plane (flip the plane)
    @param [in,out] ARG Pointer to the geometry object (plane) */
TgINLINE TgVOID
FCN_VO(tgGM_PN_Negate)(
    VEC_OBJ_T(TgPLANE,PCU) TgANALYSIS_NO_NULL ARG );

/** @brief Invalidate the geometry object (plane)
    @param [out] OUT Pointer to the geometry object (plane) */
TgINLINE TgVOID
FCN_VO(tgGM_PN_Reset)(
    VEC_OBJ_T(TgPLANE,PCU) TgANALYSIS_NO_NULL OUT );

/** @brief Validate the integrity of the geometry object (plane)
    @param [in] ARG Pointer to a geometry object (plane)
    @return True if the geometry object (plane) is valid and false otherwise */
TgINLINE TgBOOL
FCN_VO(tgGM_PN_Is_Valid)(
    VEC_OBJ_T(TgPLANE,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Test to see if a point is either on or in the geometry object (plane)
    @param [in] ARG0 Pointer to a geometry object (plane)
    @param [in] ARG1 Position vector
    @return True if the position is either on or in the geometry object (plane) and false otherwise */
TgINLINE TgBOOL
FCN_VO(tgGM_PN_Is_Contained)(
    VEC_OBJ_T(TgPLANE,CPCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Transform the geometry object (plane) at ARG0 by the matrix at ARG1
    @param [in,out] ARG0 Pointer to a geometry object (plane)
    @param [in] ARG1 Column-Major matrix (3x4) containing rotation and translation */
TgINLINE TgVOID
FCN_VO(tgGM_PN_TX)(
    VEC_OBJ_T(TgPLANE,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(3,CPCU) TgANALYSIS_NO_NULL ARG1 );

/** @brief Transform the geometry object (plane) at ARG1 by the matrix at ARG2 and store it in ARG0
    @param [out] ARG0 Pointer to a geometry object (plane)
    @param [in] ARG1 Pointer to a geometry object (plane)
    @param [in] ARG2 Column-Major matrix (3x4) containing rotation and translation */
TgINLINE TgVOID
FCN_VO(tgGM_PN_Copy_TX)(
    VEC_OBJ_T(TgPLANE,PCU) TgANALYSIS_NO_NULL ARG0, VEC_OBJ_T(TgPLANE,CPCU) TgANALYSIS_NO_NULL ARG1, VEC_T(3,CPCU) TgANALYSIS_NO_NULL ARG2 );


/** @brief Initialize a new geometry object (plane) with the function arguments
    @param [out] ARG0 Pointer to a geometry object (plane)
    @param [in] ARG1 Direction vector - normal
    @param [in] ARG2 Vector holding the new plane constant, broadcast across all lanes */
TgINLINE TgVOID
FCN_VO(tgGM_PN_Init_ND)(
    VEC_OBJ_T(TgPLANE,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1, VEC_T(1,C) ARG2 );

/** @brief Initialize a new geometry object (plane) with the function arguments
    @param [out] ARG0 Pointer to a geometry object (plane)
    @param [in] ARG1 Direction vector - normal
    @param [in] ARG2 Position vector - point on the plane */
TgINLINE TgVOID
FCN_VO(tgGM_PN_Init_NP)(
    VEC_OBJ_T(TgPLANE,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1, VEC_T(1,C) ARG2 );

/** @brief Copy the one geometry object (plane) to another of the same type
    @param [out] ARG0 Pointer to a geometry object (plane)
    @param [in] ARG1 Pointer to a geometry object (plane) */
TgINLINE TgVOID
FCN_VO(tgGM_PN_Copy)(
    VEC_OBJ_T(TgPLANE,PCU) TgANALYSIS_NO_NULL ARG0, VEC_OBJ_T(TgPLANE,CPCU) TgANALYSIS_NO_NULL ARG1 );


/** @brief Set the equation of the plane
    @param [in,out] ARG0 Pointer to a geometry object (plane)
    @param [in] ARG1 Normal and plane constant as a vector */
TgINLINE TgVOID
FCN_VO(tgGM_PN_Set_PlnEqN)(
    VEC_OBJ_T(TgPLANE,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Set the normal
    @param [in,out] ARG0 Pointer to a geometry object (plane)
    @param [in] ARG1 Pointer to a normal vector */
TgINLINE TgVOID
FCN_VO(tgGM_PN_Set_Normal)(
    VEC_OBJ_T(TgPLANE,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Set the origin
    @param [in,out] ARG0 Pointer to a geometry object (plane)
    @param [in] ARG1 Position vector */
TgINLINE TgVOID
FCN_VO(tgGM_PN_Set_Origin)(
    VEC_OBJ_T(TgPLANE,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Set the plane constant
    @param [in,out] ARG0 Pointer to a geometry object (plane)
    @param [in] ARG1 Vector holding the new plane constant, broadcast across all lanes */
TgINLINE TgVOID
FCN_VO(tgGM_PN_Set_Constant)(
    VEC_OBJ_T(TgPLANE,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1 );


/** @brief Return the equation of the plane
    @param [in] ARG Pointer to a geometry object (plane)
    @return The equation of the plane */
TgINLINE VEC_T(1)
FCN_VO(tgGM_PN_Query_PlnEqN)(
    VEC_OBJ_T(TgPLANE,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Return the normal
    @param [in] ARG Pointer to a geometry object (plane)
    @return The normal */
TgINLINE VEC_T(1)
FCN_VO(tgGM_PN_Query_Normal)(
    VEC_OBJ_T(TgPLANE,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Return the plane constant
    @param [in] ARG Pointer to a geometry object (plane)
    @return The plane constant */
TgINLINE VEC_T(1)
FCN_VO(tgGM_PN_Query_Constant)(
    VEC_OBJ_T(TgPLANE,CPCU) TgANALYSIS_NO_NULL ARG );


/** @brief Return the minimum distance squared from the geometry object (plane) to the point
    @param [in] ARG0 Pointer to a geometry object (plane)
    @param [in] ARG1 Position vector
    @return Minimum distance squared from the geometry object (plane) to the point if above the plane, and negative max otherwise */
TgINLINE VEC_T(1)
FCN_VO(tgGM_DistSq_PN_PT)(
    VEC_OBJ_T(TgPLANE,CPCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Return the minimum distance from the geometry object (plane) to the point
    @param [in] ARG0 Pointer to a geometry object (plane)
    @param [in] ARG1 Position vector
    @return Minimum distance from the geometry object (plane) to the point if above the plane, and negative max otherwise */
TgINLINE VEC_T(1)
FCN_VO(tgGM_Dist_PN_PT)(
    VEC_OBJ_T(TgPLANE,CPCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Return the minimum distance from the geometry object (plane) to the point
    @param [in] ARG0 Pointer to a geometry object (plane)
    @param [in] ARG1 Position vector
    @return Minimum distance from the geometry object (plane) to the point (positive for above the plane, negative otherwise) */
TgINLINE VEC_T(1)
FCN_VO(tgGM_Sign_Dist_PN_PT)(
    VEC_OBJ_T(TgPLANE,CPCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Return the closest point on the geometry object (plane) and the minimum distance from it to the point
    @param [out] OUT0 Pointer to a vector holding the closest point on the geometry object (plane)
    @param [in] ARG1 Pointer to a geometry object (plane)
    @param [in] ARG2 Position vector
    @return Minimum distance from the geometry object (plane) to the point (positive for above the plane, negative otherwise) */
TgINLINE VEC_T(1)
FCN_VO(tgGM_Sign_Closest_PN_PT)(
    VEC_T(1,PCU) TgANALYSIS_NO_NULL ARG0, VEC_OBJ_T(TgPLANE,CPCU) TgANALYSIS_NO_NULL ARG1, VEC_T(1,C) ARG2 );


/** @} TGS_COMMON_GEOMETRY_PN */

/* =============================================================================================================================================================================== */
#endif
