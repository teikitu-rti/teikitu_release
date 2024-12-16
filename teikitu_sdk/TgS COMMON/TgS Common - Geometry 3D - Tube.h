/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Geometry 3D - Tube.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_GEOMETRY_3D_TUBE_H)

#if !defined (TEMPLATE_TYPE_EXPANSION__RELOAD)
    #error Must be included as part of a type expansion include chain
#endif


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @addtogroup TGS_COMMON_GEOMETRY_TB */
/** @{ */

/** @brief Invalidate the geometry object (tube)
    @param [out] OUT Pointer to the geometry object (tube) */
TgINLINE TgVOID
FCN_VO(tgGM_TB_Reset)(
    VEC_OBJ_T(TgTUBE,PCU) TgANALYSIS_NO_NULL OUT );

/** @brief Validate the integrity of the geometry object (tube)
    @param [in] ARG Pointer to a geometry object (tube)
    @return True if the geometry object (tube) is valid and false otherwise */
TgINLINE TgBOOL
FCN_VO(tgGM_TB_Is_Valid)(
    VEC_OBJ_T(TgTUBE,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Transform the geometry object (tube) at ARG0 by the matrix at ARG1
    @param [in,out] ARG0 Pointer to a geometry object (tube)
    @param [in] ARG1 Column-Major matrix (3x4) containing rotation and translation */
TgINLINE TgVOID
FCN_VO(tgGM_TB_TX)(
    VEC_OBJ_T(TgTUBE,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(3,CPCU) TgANALYSIS_NO_NULL ARG1 );

/** @brief Transform the geometry object (tube) at ARG1 by the matrix at ARG2 and store it in ARG0
    @param [out] ARG0 Pointer to a geometry object (tube)
    @param [in] ARG1 Pointer to a geometry object (tube)
    @param [in] ARG2 Column-Major matrix (3x4) containing rotation and translation */
TgINLINE TgVOID
FCN_VO(tgGM_TB_Copy_TX)(
    VEC_OBJ_T(TgTUBE,PCU) TgANALYSIS_NO_NULL ARG0, VEC_OBJ_T(TgTUBE,CPCU) TgANALYSIS_NO_NULL ARG1, VEC_T(3,CPCU) TgANALYSIS_NO_NULL ARG2 );


/** @brief Initialize a new geometry object (tube) with the function arguments
    @param [out] ARG0 Pointer to a geometry object (tube)
    @param [in] ARG1 Column-Major matrix (3x4) containing rotation (basis vectors) and origin
    @param [in] ARG2 Vector holding the new extent of the axis from origin to the end of the axis, broadcast across all lanes
    @param [in] ARG3 Vector holding the new radius, broadcast across all lanes */
TgINLINE TgVOID
FCN_VO(tgGM_TB_Init)(
    VEC_OBJ_T(TgTUBE,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(3,CPCU) TgANALYSIS_NO_NULL ARG1, VEC_T(1,C) ARG2, VEC_T(1,C) ARG3 );

/** @brief Copy the one geometry object (tube) to another of the same type
    @param [out] ARG0 Pointer to a geometry object (tube)
    @param [in] ARG1 Pointer to a geometry object (tube) */
TgINLINE TgVOID
FCN_VO(tgGM_TB_Copy)(
    VEC_OBJ_T(TgTUBE,PCU) TgANALYSIS_NO_NULL ARG0, VEC_OBJ_T(TgTUBE,CPCU) TgANALYSIS_NO_NULL ARG1 );


/** @brief Set all three of the basis vectors and the origin
    @note Orthogonality of the basis vectors is the responsibility of the caller
    @param [in,out] ARG0 Pointer to a geometry object (tube)
    @param [in] ARG1 Column-Major matrix (3x4) containing rotation (basis vectors) and origin */
TgINLINE TgVOID
FCN_VO(tgGM_TB_Set_Reference_Frame)(
    VEC_OBJ_T(TgTUBE,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(3,CPCU) TgANALYSIS_NO_NULL ARG1 );

/** @brief Set the origin
    @param [in,out] ARG0 Pointer to a geometry object (tube)
    @param [in] ARG1 Position vector */
TgINLINE TgVOID
FCN_VO(tgGM_TB_Set_Origin)(
    VEC_OBJ_T(TgTUBE,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Set the extent (magnitude of the half axis)
    @param [in,out] ARG0 Pointer to a geometry object (tube)
    @param [in] ARG1 Vector holding the new extent, broadcast across all lanes */
TgINLINE TgVOID
FCN_VO(tgGM_TB_Set_Extent)(
    VEC_OBJ_T(TgTUBE,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Set the radius
    @param [in,out] ARG0 Pointer to a geometry object (tube)
    @param [in] ARG1 Vector holding the new radius, broadcast across all lanes */
TgINLINE TgVOID
FCN_VO(tgGM_TB_Set_Radius)(
    VEC_OBJ_T(TgTUBE,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1 );


/** @brief Return the origin
    @param [in] ARG Pointer to a geometry object (tube)
    @return The origin */
TgINLINE VEC_T(1)
FCN_VO(tgGM_TB_Query_Origin)(
    VEC_OBJ_T(TgTUBE,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Return the segment from an end of the tube to the mid point of the axis
    @param [in] ARG Pointer to a geometry object (tube)
    @return The segment from an end of the tube to the mid point of the axis */
TgINLINE VEC_T(1)
FCN_VO(tgGM_TB_Query_Half_Axis)(
    VEC_OBJ_T(TgTUBE,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Return the segment that is the tube axis
    @param [in] ARG Pointer to a geometry object (tube)
    @return The segment that is the tube axis */
TgINLINE VEC_OBJ_T(TgSEGMENT,CP)
FCN_VO(tgGM_TB_Query_Segment)(
    VEC_OBJ_T(TgTUBE,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Return the a normalized direction of the tube's axis
    @param [in] ARG Pointer to a geometry object (tube)
    @return The normalized direction of the tube's axis */
TgINLINE VEC_T(1)
FCN_VO(tgGM_TB_Query_Axis_Unit)(
    VEC_OBJ_T(TgTUBE,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Return the first basis vector orthogonal to the tube axis
    @param [in] ARG Pointer to a geometry object (tube)
    @return The first basis vector orthogonal to the tube axis */
TgINLINE VEC_T(1)
FCN_VO(tgGM_TB_Query_Basis_Unit_0)(
    VEC_OBJ_T(TgTUBE,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Return the second basis vector orthogonal to the tube axis
    @param [in] ARG Pointer to a geometry object (tube)
    @return The second basis vector orthogonal to the tube axis */
TgINLINE VEC_T(1)
FCN_VO(tgGM_TB_Query_Basis_Unit_1)(
    VEC_OBJ_T(TgTUBE,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Return the extent (magnitude of the half axis)
    @param [in,out] ARG0 Pointer to a geometry object (tube)
    @return The extent (magnitude of the half axis) */
TgINLINE VEC_T(1)
FCN_VO(tgGM_TB_Query_Extent)(
    VEC_OBJ_T(TgTUBE,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Return the radius
    @param [in] ARG Pointer to a geometry object (tube)
    @return The radius */
TgINLINE VEC_T(1)
FCN_VO(tgGM_TB_Query_Radius)(
    VEC_OBJ_T(TgTUBE,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Return the radius squared
    @param [in] ARG Pointer to a geometry object (tube)
    @return The radius squared */
TgINLINE VEC_T(1)
FCN_VO(tgGM_TB_Query_Radius_Sq)(
    VEC_OBJ_T(TgTUBE,CPCU) TgANALYSIS_NO_NULL ARG );


/** @} TGS_COMMON_GEOMETRY_TB */

/* =============================================================================================================================================================================== */
#endif
