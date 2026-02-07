/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Geometry 3D - Mesh [Simple].h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_GEOMETRY_3D_MESH_SIMPLE_H)

#if !defined (TEMPLATE_TYPE_EXPANSION__RELOAD)
    #error Must be included as part of a type expansion include chain
#endif


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @addtogroup TGS_COMMON_GEOMETRY_MS */
/** @{ */

/** @brief Invalidate the geometry object (mesh)
    @param [out] OUT Pointer to the geometry object (mesh) */
TgINLINE TgVOID
FCN_VO(tgGM_MS_Reset)(
    VEC_OBJ_T(TgMESH_SIMPLE,PCU) TgANALYSIS_NO_NULL OUT );

/** @brief Validate the integrity of the geometry object (mesh)
    @param [in] ARG Pointer to a geometry object (mesh)
    @return True if the geometry object (mesh) is valid and false otherwise */
TgEXTN TgBOOL
FCN_VO(tgGM_MS_Is_Valid)(
    VEC_OBJ_T(TgMESH_SIMPLE,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Determine the point on the geometry object (mesh) that is furthest along the direction of ARG1
    @param [in] ARG0 Pointer to a geometry object (mesh)
    @param [in] ARG1 Direction vector
    @return The point on the geometry object (mesh) that is furthest along the direction of ARG1 */
TgEXTN VEC_T(1)
FCN_VO(tgGM_MS_Support_Point)(
    VEC_OBJ_T(TgMESH_SIMPLE,CPCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Calculate the volume of the geometry object (mesh)
    @param [in] ARG Pointer to a geometry object (mesh)
    @return The volume of the geometry object (mesh) */
TgINLINE VEC_T(1)
FCN_VO(tgGM_MS_Volume)(
    VEC_OBJ_T(TgMESH_SIMPLE,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Calculate the surface area of the geometry object (mesh)
    @param [in] ARG Pointer to a geometry object (mesh)
    @return The surface area of the geometry object (mesh) */
TgINLINE VEC_T(1)
FCN_VO(tgGM_MS_Area)(
    VEC_OBJ_T(TgMESH_SIMPLE,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Calculate the minimum necessary Axis-Aligned Bounding Box to contain the geometry object (mesh)
    @param [out] ARG0 Pointer to an axis-aligned bounding box object
    @param [in] ARG1 Pointer to a geometry object (mesh) */
TgINLINE TgVOID
FCN_VO(tgGM_MS_BA)(
    VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL ARG0, VEC_OBJ_T(TgMESH_SIMPLE,CPCU) TgANALYSIS_NO_NULL ARG1 );

/** @brief Calculate the minimum necessary Axis-Aligned Bounding Box to contain the swept geometry object (mesh)
    @param [out] ARG0 Pointer to an axis-aligned bounding box object
    @param [in] ARG1 Pointer to a geometry object (mesh)
    @param [in] ARG2 Pointer to a vector describing the swept direction and magnitude */
TgINLINE TgVOID
FCN_VO(tgGM_MS_Sweep_BA)(
    VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL ARG0, VEC_OBJ_T(TgMESH_SIMPLE,CPCU) TgANALYSIS_NO_NULL ARG1, VEC_T(1,C) ARG2 );

/** @brief Project the geometry object (mesh) along the direction vector
    @param [out] OUT0 Pointer to a scalar value to hold the lower bound of the projection
    @param [out] OUT1 Pointer to a scalar value to hold the upper bound of the projection
    @param [in] ARG2 Pointer to a geometry object (mesh)
    @param [in] ARG3 Direction vector */
TgINLINE TgVOID
FCN_VO(tgGM_MS_Project)(
    VEC_T(1,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,PCU) TgANALYSIS_NO_NULL ARG1, VEC_OBJ_T(TgMESH_SIMPLE,CPCU) TgANALYSIS_NO_NULL ARG2, VEC_T(1,C) ARG3 );

/** @brief Test to see if a point is either on or in the geometry object (mesh)
    @param [in] ARG0 Pointer to a geometry object (mesh)
    @param [in] ARG1 Position vector
    @return True if the position is either on or in the geometry object (mesh) and false otherwise */
TgINLINE TgBOOL
FCN_VO(tgGM_MS_Is_Contained)(
    VEC_OBJ_T(TgMESH_SIMPLE,CPCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Transform the geometry object (mesh) at ARG0 by the matrix at ARG1
    @param [in,out] ARG0 Pointer to a geometry object (mesh)
    @param [in] ARG1 Column-Major matrix (3x4) containing rotation and translation */
TgINLINE TgVOID
FCN_VO(tgGM_MS_TX)(
    VEC_OBJ_T(TgMESH_SIMPLE,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(3,CPCU) TgANALYSIS_NO_NULL ARG1 );

/** @brief Transform the geometry object (mesh) at ARG1 by the matrix at ARG2 and store it in ARG0
    @param [out] ARG0 Pointer to a geometry object (mesh)
    @param [in] ARG1 Pointer to a geometry object (mesh)
    @param [in] ARG2 Column-Major matrix (3x4) containing rotation and translation */
TgINLINE TgVOID
FCN_VO(tgGM_MS_Copy_TX)(
    VEC_OBJ_T(TgMESH_SIMPLE,PCU) TgANALYSIS_NO_NULL ARG0, VEC_OBJ_T(TgMESH_SIMPLE,CPCU) TgANALYSIS_NO_NULL ARG1, VEC_T(3,CPCU) TgANALYSIS_NO_NULL ARG2 );


/** @brief Initialize a new geometry object (mesh) with the function arguments
    @param [out] OUT0 Pointer to a geometry object (mesh)
    @param [in] ARG1 Scalar value - number of vertices
    @param [in] ARG2 Scalar value - number of indices  */
TgINLINE TgVOID
FCN_VO(tgGM_MS_Init)(
    VEC_OBJ_T(TgMESH_SIMPLE,PCU) TgANALYSIS_NO_NULL OUT0, TgRSIZE_C ARG1, TgRSIZE_C ARG2 );

/** @brief Copy the one geometry object (mesh) to another of the same type
    @param [out] ARG0 Pointer to a geometry object (mesh)
    @param [in] ARG1 Pointer to a geometry object (mesh) */
TgINLINE TgVOID
FCN_VO(tgGM_MS_Copy)(
    VEC_OBJ_T(TgMESH_SIMPLE,PCU) TgANALYSIS_NO_NULL ARG0, VEC_OBJ_T(TgMESH_SIMPLE,CPCU) TgANALYSIS_NO_NULL ARG1 );


/** @brief Return the internal index array
    @param [in] ARG Pointer to the geometry object (mesh)
    @return The internal index array */
TgINLINE TgUINT_E16_CP
FCN_VO(tgGM_MS_Query_Indx_List)(
    VEC_OBJ_T(TgMESH_SIMPLE,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Return the internal vertex (position) array
    @param [in] ARG Pointer to the geometry object (mesh)
    @return The internal vertex (position) array */
TgINLINE VEC_T(1,CP)
FCN_VO(tgGM_MS_Query_Vert_List)(
    VEC_OBJ_T(TgMESH_SIMPLE,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Return the internal index count
    @param [in] ARG Pointer to the geometry object (mesh)
    @return The internal index count */
TgINLINE TgRSIZE
FCN_VO(tgGM_MS_Query_Indx_Count)(
    VEC_OBJ_T(TgMESH_SIMPLE,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Return the internal vertex count
    @param [in] ARG Pointer to the geometry object (mesh)
    @return The internal vertex count */
TgINLINE TgRSIZE
FCN_VO(tgGM_MS_Query_Vert_Count)(
    VEC_OBJ_T(TgMESH_SIMPLE,CPCU) TgANALYSIS_NO_NULL ARG );


/* Utility Functions for Primitive List Type */

/** @brief Return the contained volume assuming the primitive type is a vertex list
    @param [in] ARG Pointer to the geometry object (mesh)
    @return Volume assuming the primitive type is a vertex list */
TgEXTN VEC_T(1)
FCN_VO(tgGM_Volume_MS_VL)(
    VEC_OBJ_T(TgMESH_SIMPLE,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Return the contained volume assuming the primitive type is an indexed vertex list
    @param [in] ARG Pointer to the geometry object (mesh)
    @return Volume assuming the primitive type is an indexed vertex list */
TgEXTN VEC_T(1)
FCN_VO(tgGM_Volume_MS_IL)(
    VEC_OBJ_T(TgMESH_SIMPLE,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Return the surface area assuming the primitive type is a vertex list
    @param [in] ARG Pointer to the geometry object (mesh)
    @return Surface area assuming the primitive type is a vertex list */
TgEXTN VEC_T(1)
FCN_VO(tgGM_Area_MS_VL)(
    VEC_OBJ_T(TgMESH_SIMPLE,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Return the surface area assuming the primitive type is an indexed vertex list
    @param [in] ARG Pointer to the geometry object (mesh)
    @return Surface area assuming the primitive type is an indexed vertex list */
TgEXTN VEC_T(1)
FCN_VO(tgGM_Area_MS_IL)(
    VEC_OBJ_T(TgMESH_SIMPLE,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Test to see if a point is either on or in the mesh assuming its a vertex list
    @param [in] ARG0 Pointer to the geometry object (mesh)
    @param [in] ARG1 Pointer to the position vector
    @return True if the position is either on or in the geometry object (mesh) and false otherwise */
TgEXTN TgBOOL
FCN_VO(tgGM_Is_Contained_MS_VL)(
    VEC_OBJ_T(TgMESH_SIMPLE,CPCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Test to see if a point is either on or in the mesh assuming its an indexed vertex list
    @param [in] ARG0 Pointer to the geometry object (mesh)
    @param [in] ARG1 Pointer to the position vector
    @return True if the position is either on or in the geometry object (mesh) and false otherwise */
TgEXTN TgBOOL
FCN_VO(tgGM_Is_Contained_MS_IL)(
    VEC_OBJ_T(TgMESH_SIMPLE,CPCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1 );


/* Iterator Functions for Primitive List Type */

TgINLINE TgVOID
FCN_VO(tgGM_Iterator__Init_MS_VL)(
    TgMESH_ITER_PCU TgANALYSIS_NO_NULL ARG0, VEC_OBJ_T(TgMESH_SIMPLE,CPCU) TgANALYSIS_NO_NULL ARG1 );

TgINLINE TgRSIZE
FCN_VO(tgGM_Iterator__Increase_MS_VL)(
    TgMESH_ITER_PCU TgANALYSIS_NO_NULL ARG0, VEC_OBJ_T(TgMESH_SIMPLE,CPCU) TgANALYSIS_NO_NULL ARG1 );

TgINLINE TgVOID
FCN_VO(tgGM_Iterator__Init_MS_IL)(
    TgMESH_ITER_PCU TgANALYSIS_NO_NULL ARG0, VEC_OBJ_T(TgMESH_SIMPLE,CPCU) TgANALYSIS_NO_NULL ARG1 );

TgINLINE TgRSIZE
FCN_VO(tgGM_Iterator__Increase_MS_IL)(
    TgMESH_ITER_PCU TgANALYSIS_NO_NULL ARG0, VEC_OBJ_T(TgMESH_SIMPLE,CPCU) TgANALYSIS_NO_NULL ARG1 );


/** @} TGS_COMMON_GEOMETRY_MS */

/* =============================================================================================================================================================================== */
#endif
