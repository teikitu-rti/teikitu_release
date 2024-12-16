/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Geometry 3D - Box - Axis Aligned.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_GEOMETRY_3D_BOX_AA_H)

#if !defined (TEMPLATE_TYPE_EXPANSION__RELOAD)
    #error Must be included as part of a type expansion include chain
#endif


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @addtogroup TGS_COMMON_GEOMETRY_BA */
/** @{ */

/** @brief Return one of the box's corner position
    @param [in] ARG0 Pointer to a geometry object (box)
    @param [in] ARG1 Integer value [0-7] to select a box corner
    @return The selected corner position of the box */
TgINLINE VEC_T(1)
FCN_VO(tgGM_BA_Calc_Point_Index)(
    VEC_OBJ_T(TgBOXAA,CPCU), TgRSIZE_C );

/** @brief Tests for the bounding box having a non-zero size
    @param [in] ARG Pointer to the geometry object (axis aligned box)
    @return True if empty (min and max matching extents) and false otherwise */
TgINLINE TgBOOL
FCN_VO(tgGM_BA_Is_Empty)(
    VEC_OBJ_T(TgBOXAA,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Minimal increase to the extents so that the position vector is contained
    @param [in,out] ARG0 Pointer to a geometry object (axis aligned box)
    @param [in] ARG1 Position vector */
TgINLINE TgVOID
FCN_VO(tgGM_BA_Union_PT)(
    VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Minimal increase to the extents so that the sphere with origin and radius is contained
    @param [in,out] ARG0 Pointer to a geometry object (axis aligned box)
    @param [in] ARG1 Position vector holding the origin of the sphere
    @param [in] ARG2 Vector holding the radius of the sphere, broadcast across all lanes */
TgINLINE TgVOID
FCN_VO(tgGM_BA_Union_SP)(
    VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1, VEC_T(1,C) ARG2 );

/** @brief Minimal increase to the extents so that the other axis aligned box is contained
    @param [in,out] ARG0 Pointer to a geometry object (axis aligned box)
    @param [in] ARG1 Pointer to a geometry object (axis aligned box) */
TgINLINE TgVOID
FCN_VO(tgGM_BA_Union_BA)(
    VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL ARG0, VEC_OBJ_T(TgBOXAA,CPCU) TgANALYSIS_NO_NULL ARG1 );

/** @brief Calculate the minimum necessary Axis-Aligned Bounding Box to contain the swept geometry object (axis aligned box)
    @param [in,out] ARG0 Pointer to an axis-aligned bounding box object
    @param [in] ARG1 Pointer to a vector describing the swept direction and magnitude */
TgINLINE TgVOID
FCN_VO(tgGM_BA_Sweep)(
    VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Extend the extents by the argument scalar value (decrease the min and increase the max extents)
    @param [in,out] ARG0 Pointer to a geometry object (axis aligned box)
    @param [in] ARG1 Vector holding the new value, broadcast across all lanes */
TgINLINE TgVOID
FCN_VO(tgGM_BA_Expand)(
    VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Scale the extents (away from the centre) by the scalar value
    @param [in,out] ARG0 Pointer to a geometry object (axis aligned box)
    @param [in] ARG1 Vector holding the new value, broadcast across all lanes */
TgINLINE TgVOID
FCN_VO(tgGM_BA_Scale)(
    VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Return the centre
    @param [in] ARG Pointer to a geometry object (axis aligned box)
    @return The centre */
TgINLINE VEC_T(1)
FCN_VO(tgGM_BA_Query_Centre)(
    VEC_OBJ_T(TgBOXAA,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Invalidate the geometry object (axis aligned box)
    @param [out] OUT Pointer to the geometry object (axis aligned box) */
TgINLINE TgVOID
FCN_VO(tgGM_BA_Reset)(
    VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL OUT );

/** @brief Zero the geometry object (axis aligned box)
    @param [out] OUT Pointer to the geometry object (axis aligned box) */
TgINLINE TgVOID
FCN_VO(tgGM_BA_Zero)(
    VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL OUT );

/** @brief Validate the integrity of the geometry object (axis aligned box)
    @param [in] ARG Pointer to a geometry object (axis aligned box)
    @return True if the geometry object (axis aligned box) is valid and false otherwise */
TgINLINE TgBOOL
FCN_VO(tgGM_BA_Is_Valid)(
    VEC_OBJ_T(TgBOXAA,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Determine the point on the geometry object (axis aligned box) that is furthest along the direction of ARG1
    @param [in] ARG0 Pointer to a geometry object (axis aligned box)
    @param [in] ARG1 Direction vector
    @return The point on the geometry object (axis aligned box) that is furthest along the direction of ARG1 */
TgINLINE VEC_T(1)
FCN_VO(tgGM_BA_Support_Point)(
    VEC_OBJ_T(TgBOXAA,CPCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Calculate the volume of the geometry object (axis aligned box)
    @param [in] ARG Pointer to a geometry object (axis aligned box)
    @return The volume of the geometry object (axis aligned box) */
TgINLINE VEC_T(1)
FCN_VO(tgGM_BA_Volume)(
    VEC_OBJ_T(TgBOXAA,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Calculate the surface area of the geometry object (axis aligned box)
    @param [in] ARG Pointer to a geometry object (axis aligned box)
    @return The surface area of the geometry object (axis aligned box) */
TgINLINE VEC_T(1)
FCN_VO(tgGM_BA_Area)(
    VEC_OBJ_T(TgBOXAA,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Calculate the minimum necessary Axis-Aligned Bounding Box to contain the geometry object (axis aligned box)
    @param [out] ARG0 Pointer to an axis-aligned bounding box object
    @param [in] ARG1 Pointer to a geometry object (axis aligned box) */
TgINLINE TgVOID
FCN_VO(tgGM_BA_BA)(
    VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL ARG0, VEC_OBJ_T(TgBOXAA,CPCU) TgANALYSIS_NO_NULL ARG1 );

/** @brief Calculate the minimum necessary Axis-Aligned Bounding Box to contain the swept geometry object (axis aligned box)
    @param [out] ARG0 Pointer to an axis-aligned bounding box object
    @param [in] ARG1 Pointer to a geometry object (axis aligned box)
    @param [in] ARG2 Pointer to a vector describing the swept direction and magnitude */
TgINLINE TgVOID
FCN_VO(tgGM_BA_Sweep_BA)(
    VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL ARG0, VEC_OBJ_T(TgBOXAA,CPCU) TgANALYSIS_NO_NULL ARG1, VEC_T(1,C) ARG2 );

/** @brief Project the geometry object (axis aligned box) along the direction vector
    @param [out] OUT0 Pointer to a scalar value to hold the lower bound of the projection
    @param [out] OUT1 Pointer to a scalar value to hold the upper bound of the projection
    @param [in] ARG2 Pointer to a geometry object (axis aligned box)
    @param [in] ARG3 Direction vector */
TgINLINE TgVOID
FCN_VO(tgGM_BA_Project)(
    VEC_T(1,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,PCU) TgANALYSIS_NO_NULL ARG1, VEC_OBJ_T(TgBOXAA,CPCU) TgANALYSIS_NO_NULL ARG2, VEC_T(1,C) ARG3 );

/** @brief Test to see if a point is either on or in the geometry object (axis aligned box)
    @param [in] ARG0 Pointer to a geometry object (axis aligned box)
    @param [in] ARG1 Position vector
    @return True if the position is either on or in the geometry object (axis aligned box) and false otherwise */
TgINLINE TgBOOL
FCN_VO(tgGM_BA_Is_Contained)(
    VEC_OBJ_T(TgBOXAA,CPCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Transform the geometry object (axis aligned box) at ARG0 by the matrix at ARG1
    @param [in,out] ARG0 Pointer to a geometry object (axis aligned box)
    @param [in] ARG1 Column-Major matrix (3x4) containing rotation and translation */
TgINLINE TgVOID
FCN_VO(tgGM_BA_TX)(
    VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(3,CPCU) TgANALYSIS_NO_NULL ARG1 );

/** @brief Transform the geometry object (axis aligned box) at ARG1 by the matrix at ARG2 and store it in ARG0
    @param [out] ARG0 Pointer to a geometry object (axis aligned box)
    @param [in] ARG1 Pointer to a geometry object (axis aligned box)
    @param [in] ARG2 Column-Major matrix (3x4) containing rotation and translation */
TgINLINE TgVOID
FCN_VO(tgGM_BA_Copy_TX)(
    VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL ARG0, VEC_OBJ_T(TgBOXAA,CPCU) TgANALYSIS_NO_NULL ARG1, VEC_T(3,CPCU) TgANALYSIS_NO_NULL ARG2 );


/** @brief Initialize a new geometry object (axis aligned box) with the function arguments
    @param [out] ARG0 Pointer to a geometry object (axis aligned box)
    @param [in] ARG1 Pointer to a vector - minimum extents
    @param [in] ARG2 Pointer to a vector - maximum extents  */
TgINLINE TgVOID
FCN_VO(tgGM_BA_Init)(
    VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1, VEC_T(1,C) ARG2 );

/** @brief Initialize a new geometry object (axis aligned box) with the function arguments
    @param [out] ARG0 Pointer to a geometry object (axis aligned box)
    @param [in] ARG1 Position vector */
TgINLINE TgVOID
FCN_VO(tgGM_BA_Init_PT)(
    VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Initialize a new geometry object (axis aligned box) sufficient to contain a sphere defined by the parameters
    @param [out] ARG0 Pointer to a geometry object (axis aligned box)
    @param [in] ARG1 Position vector holding the origin of the sphere
    @param [in] ARG2 Vector holding the radius of the sphere, broadcast across all lanes */
TgINLINE TgVOID
FCN_VO(tgGM_BA_Init_SP)(
    VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1, VEC_T(1,C) ARG2 ); /**< Single Point and Radius */

/** @brief Copy the one geometry object (axis aligned box) to another of the same type
    @param [out] ARG0 Pointer to a geometry object (axis aligned box)
    @param [in] ARG1 Pointer to a geometry object (axis aligned box) */
TgINLINE TgVOID
FCN_VO(tgGM_BA_Copy)(
    VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL ARG0, VEC_OBJ_T(TgBOXAA,CPCU) TgANALYSIS_NO_NULL ARG1 );


/** @brief Set the minimum extents to be a MAX value, and the maximum extents to be a MIN value
    @param [out] ARG0 Pointer to a geometry object (axis aligned box) */
TgINLINE TgVOID
FCN_VO(tgGM_BA_Set_Invalid)(
    VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL ARG );

/** @brief Set the minimum extents
    @param [in,out] ARG0 Pointer to a geometry object (axis aligned box)
    @param [in] ARG1 Pointer to a vector */
TgINLINE TgVOID
FCN_VO(tgGM_BA_Set_Min)(
    VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Set the maximum extents
    @param [in,out] ARG0 Pointer to a geometry object (axis aligned box)
    @param [in] ARG1 Pointer to a vector */
TgINLINE TgVOID
FCN_VO(tgGM_BA_Set_Max)(
    VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Set the minimum extent along the x-axis
    @param [in,out] ARG0 Pointer to a geometry object (axis aligned box)
    @param [in] ARG1 Vector holding the new value, broadcast across all lanes */
TgINLINE TgVOID
FCN_VO(tgGM_BA_Set_Min_X)(
    VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Set the minimum extent along the y-axis
    @param [in,out] ARG0 Pointer to a geometry object (axis aligned box)
    @param [in] ARG1 Vector holding the new value, broadcast across all lanes */
TgINLINE TgVOID
FCN_VO(tgGM_BA_Set_Min_Y)(
    VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Set the minimum extent along the z-axis
    @param [in,out] ARG0 Pointer to a geometry object (axis aligned box)
    @param [in] ARG1 Vector holding the new value, broadcast across all lanes */
TgINLINE TgVOID
FCN_VO(tgGM_BA_Set_Min_Z)(
    VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Set the maximum extent along the x-axis
    @param [in,out] ARG0 Pointer to a geometry object (axis aligned box)
    @param [in] ARG1 Vector holding the new value, broadcast across all lanes */
TgINLINE TgVOID
FCN_VO(tgGM_BA_Set_Max_X)(
    VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Set the maximum extent along the y-axis
    @param [in,out] ARG0 Pointer to a geometry object (axis aligned box)
    @param [in] ARG1 Vector holding the new value, broadcast across all lanes */
TgINLINE TgVOID
FCN_VO(tgGM_BA_Set_Max_Y)(
    VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Set the maximum extent along the z-axis
    @param [in,out] ARG0 Pointer to a geometry object (axis aligned box)
    @param [in] ARG1 Vector holding the new value, broadcast across all lanes */
TgINLINE TgVOID
FCN_VO(tgGM_BA_Set_Max_Z)(
    VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1 );


/** @brief Return the minimum extents as a vector
    @param [in] ARG Pointer to a geometry object (axis aligned box)
    @return The minimum extents as a vector */
TgINLINE VEC_T(1)
FCN_VO(tgGM_BA_Query_Min)(
    VEC_OBJ_T(TgBOXAA,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Return the maximum extents as a vector
    @param [in] ARG Pointer to a geometry object (axis aligned box)
    @return The maximum extents as a vector */
TgINLINE VEC_T(1)
FCN_VO(tgGM_BA_Query_Max)(
    VEC_OBJ_T(TgBOXAA,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Return the minimum extent along the x-axis
    @param [in] ARG Pointer to a geometry object (axis aligned box)
    @return The minimum extent along the x-axis */
TgINLINE VEC_T(1)
FCN_VO(tgGM_BA_Query_Min_X)(
    VEC_OBJ_T(TgBOXAA,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Return the minimum extent along the y-axis
    @param [in] ARG Pointer to a geometry object (axis aligned box)
    @return The minimum extent along the y-axis */
TgINLINE VEC_T(1)
FCN_VO(tgGM_BA_Query_Min_Y)(
    VEC_OBJ_T(TgBOXAA,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Return the minimum extent along the z-axis
    @param [in] ARG Pointer to a geometry object (axis aligned box)
    @return The minimum extent along the z-axis */
TgINLINE VEC_T(1)
FCN_VO(tgGM_BA_Query_Min_Z)(
    VEC_OBJ_T(TgBOXAA,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Return the maximum extent along the x-axis
    @param [in] ARG Pointer to a geometry object (axis aligned box)
    @return The maximum extent along the x-axis */
TgINLINE VEC_T(1)
FCN_VO(tgGM_BA_Query_Max_X)(
    VEC_OBJ_T(TgBOXAA,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Return the maximum extent along the y-axis
    @param [in] ARG Pointer to a geometry object (axis aligned box)
    @return The maximum extent along the y-axis */
TgINLINE VEC_T(1)
FCN_VO(tgGM_BA_Query_Max_Y)(
    VEC_OBJ_T(TgBOXAA,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Return the maximum extent along the z-axis
    @param [in] ARG Pointer to a geometry object (axis aligned box)
    @return The maximum extent along the z-axis */
TgINLINE VEC_T(1)
FCN_VO(tgGM_BA_Query_Max_Z)(
    VEC_OBJ_T(TgBOXAA,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Return the length along of the x-axis
    @param [in] ARG Pointer to a geometry object (axis aligned box)
    @return The length along of the x-axis */
TgINLINE VEC_T(1)
FCN_VO(tgGM_BA_Query_Size_X)(
    VEC_OBJ_T(TgBOXAA,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Return the length along of the y-axis
    @param [in] ARG Pointer to a geometry object (axis aligned box)
    @return The length along of the y-axis */
TgINLINE VEC_T(1)
FCN_VO(tgGM_BA_Query_Size_Y)(
    VEC_OBJ_T(TgBOXAA,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Return the length along of the z-axis
    @param [in] ARG Pointer to a geometry object (axis aligned box)
    @return The length along of the z-axis */
TgINLINE VEC_T(1)
FCN_VO(tgGM_BA_Query_Size_Z)(
    VEC_OBJ_T(TgBOXAA,CPCU) TgANALYSIS_NO_NULL ARG );


/** @} TGS_COMMON_GEOMETRY_BA */

/* =============================================================================================================================================================================== */
#endif
