/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Geometry 3D - Mesh [BA].h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_GEOMETRY_3D_MESH_BA_H)

#if !defined (TEMPLATE_TYPE_EXPANSION__RELOAD)
    #error Must be included as part of a type expansion include chain
#endif


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @addtogroup TGS_COMMON_GEOMETRY_MA */
/** @{ */

/** @brief Invalidate the geometry object (mesh w/AABB)
    @param [out] OUT Pointer to the geometry object (mesh w/AABB) */
TgINLINE TgVOID
FCN_VO(tgGM_MA_Reset)(
    VEC_OBJ_T(TgMESH_BA,PCU) TgANALYSIS_NO_NULL OUT );

/** @brief Validate the integrity of the geometry object (mesh w/AABB)
    @param [in] ARG Pointer to a geometry object (mesh w/AABB)
    @return True if the geometry object (mesh w/AABB) is valid and false otherwise */
TgEXTN TgBOOL
FCN_VO(tgGM_MA_Is_Valid)(
    VEC_OBJ_T(TgMESH_BA,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Determine the point on the geometry object (mesh w/AABB) that is furthest along the direction of ARG1
    @param [in] ARG0 Pointer to a geometry object (mesh w/AABB)
    @param [in] ARG1 Direction vector
    @return The point on the geometry object (mesh w/AABB) that is furthest along the direction of ARG1 */
TgINLINE VEC_T(1)
FCN_VO(tgGM_MA_Support_Point)(
    VEC_OBJ_T(TgMESH_BA,CPCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Calculate the volume of the geometry object (mesh w/AABB)
    @param [in] ARG Pointer to a geometry object (mesh w/AABB)
    @return The volume of the geometry object (mesh w/AABB) */
TgINLINE VEC_T(1)
FCN_VO(tgGM_MA_Volume)(
    VEC_OBJ_T(TgMESH_BA,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Calculate the surface area of the geometry object (mesh w/AABB)
    @param [in] ARG Pointer to a geometry object (mesh w/AABB)
    @return The surface area of the geometry object (mesh w/AABB) */
TgINLINE VEC_T(1)
FCN_VO(tgGM_MA_Area)(
    VEC_OBJ_T(TgMESH_BA,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Calculate the minimum necessary Axis-Aligned Bounding Box to contain the geometry object (mesh w/AABB)
    @param [out] ARG0 Pointer to an axis-aligned bounding box object
    @param [in] ARG1 Pointer to a geometry object (mesh w/AABB) */
TgINLINE TgVOID
FCN_VO(tgGM_MA_BA)(
    VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL ARG0, VEC_OBJ_T(TgMESH_BA,CPCU) TgANALYSIS_NO_NULL ARG1 );

/** @brief Calculate the minimum necessary Axis-Aligned Bounding Box to contain the swept geometry object (mesh w/AABB)
    @param [out] ARG0 Pointer to an axis-aligned bounding box object
    @param [in] ARG1 Pointer to a geometry object (mesh w/AABB)
    @param [in] ARG2 Pointer to a vector describing the swept direction and magnitude */
TgINLINE TgVOID
FCN_VO(tgGM_MA_Sweep_BA)(
    VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL ARG0, VEC_OBJ_T(TgMESH_BA,CPCU) TgANALYSIS_NO_NULL ARG1, VEC_T(1,C) ARG2 );

/** @brief Project the geometry object (mesh w/AABB) along the direction vector
    @param [out] OUT0 Pointer to a scalar value to hold the lower bound of the projection
    @param [out] OUT1 Pointer to a scalar value to hold the upper bound of the projection
    @param [in] ARG2 Pointer to a geometry object (mesh w/AABB)
    @param [in] ARG3 Direction vector */
TgINLINE TgVOID
FCN_VO(tgGM_MA_Project)(
    VEC_T(1,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,PCU) TgANALYSIS_NO_NULL ARG1, VEC_OBJ_T(TgMESH_BA,CPCU) TgANALYSIS_NO_NULL ARG2, VEC_T(1,C) ARG3);

/** @brief Test to see if a point is either on or in the geometry object (mesh w/AABB)
    @param [in] ARG0 Pointer to a geometry object (mesh w/AABB)
    @param [in] ARG1 Position vector
    @return True if the position is either on or in the geometry object (mesh w/AABB) and false otherwise */
TgINLINE TgBOOL
FCN_VO(tgGM_MA_Is_Contained)(
    VEC_OBJ_T(TgMESH_BA,CPCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Transform the geometry object (mesh w/AABB) at ARG0 by the matrix at ARG1
    @param [in,out] ARG0 Pointer to a geometry object (mesh w/AABB)
    @param [in] ARG1 Column-Major matrix (3x4) containing rotation and translation */
TgEXTN TgVOID
FCN_VO(tgGM_MA_TX)(
    VEC_OBJ_T(TgMESH_BA,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(3,CPCU) TgANALYSIS_NO_NULL ARG1 );

/** @brief Transform the geometry object (mesh w/AABB) at ARG1 by the matrix at ARG2 and store it in ARG0
    @param [out] ARG0 Pointer to a geometry object (mesh w/AABB)
    @param [in] ARG1 Pointer to a geometry object (mesh w/AABB)
    @param [in] ARG2 Column-Major matrix (3x4) containing rotation and translation */
TgEXTN TgVOID
FCN_VO(tgGM_MA_Copy_TX)(
    VEC_OBJ_T(TgMESH_BA,PCU) TgANALYSIS_NO_NULL ARG0, VEC_OBJ_T(TgMESH_BA,CPCU) TgANALYSIS_NO_NULL ARG1, VEC_T(3,CPCU) TgANALYSIS_NO_NULL ARG2 );


/** @brief Initialize a new geometry object (mesh w/AABB) with the function arguments
    @param [out] OUT0 Pointer to a geometry object (mesh w/AABB)
    @param [in] ARG1 Scalar value - number of vertices
    @param [in] ARG2 Scalar value - number of indices
    @param [in] ARG2 Enumeration - type of transformation between t0 and t1 */
TgEXTN TgVOID
FCN_VO(tgGM_MA_Init)(
    VEC_OBJ_T(TgMESH_BA,PCU), TgRSIZE_C, TgRSIZE_C, ETgSWEEP_TYPE_C );

/** @brief Initialize a new geometry object (mesh w/AABB) with the function arguments
    @param [out] ARG0 Pointer to a geometry object (mesh w/AABB)
    @param [in] ARG1 Pointer to a geometry object (mesh) */
TgINLINE TgVOID
FCN_VO(tgGM_MA_Init_MS)(
    VEC_OBJ_T(TgMESH_BA,PCU) TgANALYSIS_NO_NULL ARG0, VEC_OBJ_T(TgMESH_SIMPLE,CPCU) TgANALYSIS_NO_NULL ARG1 );

/** @brief Initialize a new geometry object (mesh w/AABB) with the function arguments
    @param [out] ARG0 Pointer to a geometry object (mesh w/AABB)
    @param [in] ARG1 Pointer to a geometry object (mesh)
    @param [in] ARG2 Column-Major matrix (3x4) containing rotation and translation */
TgINLINE TgVOID
FCN_VO(tgGM_MA_Init_MS_TX)(
    VEC_OBJ_T(TgMESH_BA,PCU) TgANALYSIS_NO_NULL ARG0, VEC_OBJ_T(TgMESH_SIMPLE,CPCU) TgANALYSIS_NO_NULL ARG1,
                            VEC_T(3,CPCU) TgANALYSIS_NO_NULL ARG2 );

/** @brief Initialize a new geometry object (mesh w/AABB) with the function arguments
    @param [out] ARG0 Pointer to a geometry object (mesh w/AABB)
    @param [in] ARG1 Pointer to a geometry object (mesh)
    @param [in] ARG2 Column-Major matrix (3x4) containing rotation and translation
    @param [in] ARG3 Direction vector - direction and magnitude of the displacement between t0 and t1 */
TgINLINE TgVOID
FCN_VO(tgGM_MA_Init_MS_TX_TL)(
    VEC_OBJ_T(TgMESH_BA,PCU) TgANALYSIS_NO_NULL ARG0, VEC_OBJ_T(TgMESH_SIMPLE,CPCU) TgANALYSIS_NO_NULL ARG1, VEC_T(3,CPCU) TgANALYSIS_NO_NULL ARG2, VEC_T(1,C) ARG3 );

/** @brief Initialize a new geometry object (mesh w/AABB) with the function arguments
    @param [out] ARG0 Pointer to a geometry object (mesh w/AABB)
    @param [in] ARG1 Pointer to a geometry object (mesh)
    @param [in] ARG2 Column-Major matrix (3x4) containing rotation and translation at t0
    @param [in] ARG3 Column-Major matrix (3x4) containing rotation and translation at t1 */
TgINLINE TgVOID
FCN_VO(tgGM_MA_Init_MS_TX_TX)(
    VEC_OBJ_T(TgMESH_BA,PCU) TgANALYSIS_NO_NULL ARG0, VEC_OBJ_T(TgMESH_SIMPLE,CPCU) TgANALYSIS_NO_NULL ARG1, VEC_T(3,CPCU) TgANALYSIS_NO_NULL ARG2, VEC_T(3,CPCU) TgANALYSIS_NO_NULL ARG3 );

/** @brief Copy the one geometry object (mesh w/AABB) to another of the same type
    @param [out] ARG0 Pointer to a geometry object (mesh w/AABB)
    @param [in] ARG1 Pointer to a geometry object (mesh w/AABB) */
TgINLINE TgVOID
FCN_VO(tgGM_MA_Copy)(
    VEC_OBJ_T(TgMESH_BA,PCU) TgANALYSIS_NO_NULL ARG0, VEC_OBJ_T(TgMESH_BA,CPCU) TgANALYSIS_NO_NULL ARG1 );


/** @brief Update the internal bounding volume objects
    @param [in,out] ARG Pointer to the geometry object (mesh w/AABB) */
TgINLINE TgVOID
FCN_VO(tgGM_MA_Update_Face_BA)(
    VEC_OBJ_T(TgMESH_BA,PCU) TgANALYSIS_NO_NULL ARG );

/** @brief Update the internal bounding volume objects and centre of gravity
    @param [in,out] ARG Pointer to the geometry object (mesh w/AABB) */
TgINLINE TgVOID
FCN_VO(tgGM_MA_Update_Face_CG_BA)(
    VEC_OBJ_T(TgMESH_BA,PCU) TgANALYSIS_NO_NULL ARG );



/** @brief Return the internal index array
    @param [in] ARG Pointer to the geometry object (mesh w/AABB)
    @return The internal index array */
TgINLINE TgUINT_E16_CP
FCN_VO(tgGM_MA_Query_Indx_List)(
    VEC_OBJ_T(TgMESH_BA,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Return the internal vertex (position) array
    @param [in] ARG Pointer to the geometry object (mesh w/AABB)
    @return The internal vertex (position) array */
TgINLINE VEC_T(1,CP)
FCN_VO(tgGM_MA_Query_Vert_List)(
    VEC_OBJ_T(TgMESH_BA,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Return the internal index count
    @param [in] ARG Pointer to the geometry object (mesh w/AABB)
    @return The internal index count */
TgINLINE TgRSIZE
FCN_VO(tgGM_MA_Query_Indx_Count)(
    VEC_OBJ_T(TgMESH_BA,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Return the internal vertex count
    @param [in] ARG Pointer to the geometry object (mesh w/AABB)
    @return The internal vertex count */
TgINLINE TgRSIZE
FCN_VO(tgGM_MA_Query_Vert_Count)(
    VEC_OBJ_T(TgMESH_BA,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Return the centre of gravity at t0
    @param [in] ARG Pointer to the geometry object (mesh w/AABB)
    @return The centre of gravity at t0 */
TgINLINE VEC_T(1,CP)
FCN_VO(tgGM_MA_Query_CG_0)(
    VEC_OBJ_T(TgMESH_BA,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Return the centre of gravity at t1
    @param [in] ARG Pointer to the geometry object (mesh w/AABB)
    @return The centre of gravity at t1 */
TgINLINE VEC_T(1,CP)
FCN_VO(tgGM_MA_Query_CG_1)(
    VEC_OBJ_T(TgMESH_BA,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Return the delta (translation and rotation) between t0 and t1 for the geometry object (mesh w/AABB)
    @param [in] ARG Pointer to the geometry object (mesh w/AABB)
    @return The internal delta object */
TgINLINE VEC_OBJ_T(TgDELTA,CP)
FCN_VO(tgGM_MA_Query_DT)(
    VEC_OBJ_T(TgMESH_BA,CPCU) TgANALYSIS_NO_NULL ARG );


/* Utility Functions for Primitive List Type */

/** @brief Update the internal bounding volume objects assuming the mesh is a vertex list
    @param [in,out] ARG Pointer to the geometry object (mesh w/AABB) */
TgEXTN TgVOID
FCN_VO(tgGM_MA_Update_Face_BA_VL)(
    VEC_OBJ_T(TgMESH_BA,PCU) TgANALYSIS_NO_NULL ARG );

/** @brief Update the internal bounding volume objects assuming the mesh is an indexed vertex list
    @param [in,out] ARG Pointer to the geometry object (mesh w/AABB) */
TgEXTN TgVOID
FCN_VO(tgGM_MA_Update_Face_BA_IL)(
    VEC_OBJ_T(TgMESH_BA,PCU) TgANALYSIS_NO_NULL ARG );

/** @brief Update the internal bounding volume objects and centre of gravity assuming the mesh is a vertex list
    @param [in,out] ARG Pointer to the geometry object (mesh w/AABB) */
TgEXTN TgVOID
FCN_VO(tgGM_MA_Update_Face_CG_BA_VL)(
    VEC_OBJ_T(TgMESH_BA,PCU) TgANALYSIS_NO_NULL ARG );

/** @brief Update the internal bounding volume objects and centre of gravity assuming the mesh is an indexed vertex list
    @param [in,out] ARG Pointer to the geometry object (mesh w/AABB) */
TgEXTN TgVOID
FCN_VO(tgGM_MA_Update_Face_CG_BA_IL)(
    VEC_OBJ_T(TgMESH_BA,PCU) TgANALYSIS_NO_NULL ARG );


/** @} TGS_COMMON_GEOMETRY_MA */

/* =============================================================================================================================================================================== */
#endif
