/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Geometry 3D - Triangle [Collision].h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_GEOMETRY_3D_TRIANGLE_COLLISION_H)

#if !defined (TEMPLATE_TYPE_EXPANSION__RELOAD)
    #error Must be included as part of a type expansion include chain
#endif


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @addtogroup TGS_COMMON_GEOMETRY_CT */
/** @{ */

/** @brief Determine if the barycentric coordinates is a culled point
    @param [in,out] ARG0 Pointer to the geometry object (triangle w/collision)
    @param [in] ARG1 Vector - broadcast of the 1st barycentric co-ordinate
    @param [in] ARG2 Vector - broadcast of the 2nd barycentric co-ordinate
    @return True if the point has been culled and false otherwise */
TgEXTN TgBOOL
FCN_VO(tgGM_CT_Is_Point_Culled)(
    VEC_OBJ_T(TgCTRI,CPCU) NONULL ARG0, VEC_T(1,C) ARG1, VEC_T(1,C) ARG2 );

/** @brief Calculate the edge planes of the triangle
    @param [in,out] ARG Pointer to the geometry object (triangle w/collision) */
TgINLINE TgVOID
FCN_VO(tgGM_CT_Reset_Flags)(
    VEC_OBJ_T(TgCTRI,PCU) NONULL ARG );

/** @brief Calculate the normal of the triangle
    @param [in,out] ARG Pointer to the geometry object (triangle w/collision) */
TgINLINE TgVOID
FCN_VO(tgGM_CT_Calc_Normal)(
    VEC_OBJ_T(TgCTRI,PCU) NONULL ARG );

/** @brief Project the geometry object (triangle w/collision) along the direction vector
    @param [in] ARG1 Pointer to a geometry object (triangle w/collision)
    @param [in] ARG2 Vector holding the fraction along the edge from point 0 to point 1, broadcast across all lanes
    @param [in] ARG3 Vector holding the fraction along the edge from point 0 to point 2, broadcast across all lanes
    @returnn Position vector - Resulting position based on bary-centric values in the arguments */
TgINLINE VEC_T(1)
FCN_VO(tgGM_CT_Calc_Point)(
    VEC_OBJ_T(TgCTRI,CPCU) NONULL ARG1, VEC_T(1,C) ARG2, VEC_T(1,C) ARG3 );

/** @brief Invalidate the geometry object (triangle w/collision)
    @param [out] OUT Pointer to the geometry object (triangle w/collision) */
TgINLINE TgVOID
FCN_VO(tgGM_CT_Reset)(
    VEC_OBJ_T(TgCTRI,PCU) NONULL OUT );

/** @brief Validate the integrity of the geometry object (triangle w/collision)
    @param [in] ARG Pointer to a geometry object (triangle w/collision)
    @return True if the geometry object (triangle w/collision) is valid and false otherwise */
TgINLINE TgBOOL
FCN_VO(tgGM_CT_Is_Valid)(
    VEC_OBJ_T(TgCTRI,CPCU) NONULL ARG );

/** @brief Determine the point on the geometry object (triangle w/collision) that is furthest along the direction of ARG1
    @param [in] ARG0 Pointer to a geometry object (triangle w/collision)
    @param [in] ARG1 Direction vector
    @return The point on the geometry object (triangle w/collision) that is furthest along the direction of ARG1 */
TgINLINE VEC_T(1)
FCN_VO(tgGM_CT_Support_Point)(
    VEC_OBJ_T(TgCTRI,CPCU) NONULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Calculate the surface area of the geometry object (triangle w/collision)
    @param [in] ARG Pointer to a geometry object (triangle w/collision)
    @return The surface area of the geometry object (triangle w/collision) */
TgINLINE VEC_T(1)
FCN_VO(tgGM_CT_Area)(
    VEC_OBJ_T(TgCTRI,CPCU) NONULL ARG );

/** @brief Calculate the minimum necessary Axis-Aligned Bounding Box to contain the geometry object (triangle w/collision)
    @param [out] ARG0 Pointer to an axis-aligned bounding box object
    @param [in] ARG1 Pointer to a geometry object (triangle w/collision) */
TgINLINE TgVOID
FCN_VO(tgGM_CT_BA)(
    VEC_OBJ_T(TgBOXAA,PCU) NONULL ARG0, VEC_OBJ_T(TgCTRI,CPCU) NONULL ARG1 );

/** @brief Calculate the minimum necessary Axis-Aligned Bounding Box to contain the swept geometry object (triangle w/collision)
    @param [out] ARG0 Pointer to an axis-aligned bounding box object
    @param [in] ARG1 Pointer to a geometry object (triangle w/collision)
    @param [in] ARG2 Pointer to a vector describing the swept direction and magnitude */
TgINLINE TgVOID
FCN_VO(tgGM_CT_Sweep_BA)(
    VEC_OBJ_T(TgBOXAA,PCU) NONULL ARG0, VEC_OBJ_T(TgCTRI,CPCU) NONULL ARG1, VEC_T(1,C) ARG2 );

/** @brief Project the geometry object (triangle w/collision) along the direction vector
    @param [out] OUT0 Pointer to a scalar value to hold the lower bound of the projection
    @param [out] OUT1 Pointer to a scalar value to hold the upper bound of the projection
    @param [in] ARG2 Pointer to a geometry object (triangle w/collision)
    @param [in] ARG3 Direction vector */
TgINLINE TgVOID
FCN_VO(tgGM_CT_Project)(
    VEC_T(1,PCU) NONULL ARG0, VEC_T(1,PCU) NONULL ARG1, VEC_OBJ_T(TgCTRI,CPCU) NONULL ARG2, VEC_T(1,C) ARG3 );

/** @brief Test to see if a point is either on or in the geometry object (triangle w/collision)
    @param [in] ARG0 Pointer to a geometry object (triangle w/collision)
    @param [in] ARG1 Position vector
    @return True if the position is either on or in the geometry object (triangle w/collision) and false otherwise */
TgINLINE TgBOOL
FCN_VO(tgGM_CT_Is_Contained)(
    VEC_OBJ_T(TgCTRI,CPCU) NONULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Transform the geometry object (triangle w/collision) at ARG0 by the matrix at ARG1
    @param [in,out] ARG0 Pointer to a geometry object (triangle w/collision)
    @param [in] ARG1 Column-Major matrix (3x4) containing rotation and translation */
TgINLINE TgVOID
FCN_VO(tgGM_CT_TX)(
    VEC_OBJ_T(TgCTRI,PCU) NONULL ARG0, VEC_T(3,CPCU) NONULL ARG1 );

/** @brief Transform the geometry object (triangle w/collision) at ARG1 by the matrix at ARG2 and store it in ARG0
    @param [out] ARG0 Pointer to a geometry object (triangle w/collision)
    @param [in] ARG1 Pointer to a geometry object (triangle w/collision)
    @param [in] ARG2 Column-Major matrix (3x4) containing rotation and translation */
TgINLINE TgVOID
FCN_VO(tgGM_CT_Copy_TX)(
    VEC_OBJ_T(TgCTRI,PCU) NONULL ARG0, VEC_OBJ_T(TgCTRI,CPCU) NONULL ARG1, VEC_T(3,CPCU) NONULL ARG2 );


/** @brief Initialize a new geometry object (triangle w/collision) with the function arguments
    @note Consistency of the normal with the three points is left to the caller
    @param [out] ARG0 Pointer to a geometry object (triangle w/collision)
    @param [in] ARG1 Position vector - first point
    @param [in] ARG2 Position vector - second point
    @param [in] ARG3 Position vector - third point
    @param [in] ARG4 Direction vector - normal */
TgINLINE TgVOID
FCN_VO(tgGM_CT_Init_PN)(
    VEC_OBJ_T(TgCTRI,PCU) NONULL ARG0, VEC_T(1,C) ARG1, VEC_T(1,C) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4 );

/** @brief Initialize a new geometry object (triangle w/collision) with the function arguments
    @param [out] ARG0 Pointer to a geometry object (triangle w/collision)
    @param [in] ARG1 Position vector - first point
    @param [in] ARG2 Position vector - second point
    @param [in] ARG3 Position vector - third point  */
TgINLINE TgVOID
FCN_VO(tgGM_CT_Init_P)(
    VEC_OBJ_T(TgCTRI,PCU) NONULL ARG0, VEC_T(1,C) ARG1, VEC_T(1,C) ARG2, VEC_T(1,C) ARG3 );

/** @brief Initialize a new geometry object (triangle w/collision) with the function arguments
    @note Consistency of the normal with the two edges is left to the caller
    @param [out] ARG0 Pointer to a geometry object (triangle w/collision)
    @param [in] ARG1 Position vector - origin
    @param [in] ARG2 Direction vector - edge from point 0 to point 1
    @param [in] ARG3 Direction vector - edge from point 0 to point 2
    @param [in] ARG4 Direction vector - normal */
TgINLINE TgVOID
FCN_VO(tgGM_CT_Init_EN)(
    VEC_OBJ_T(TgCTRI,PCU) NONULL ARG0, VEC_T(1,C) ARG1, VEC_T(1,C) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4 );

/** @brief Initialize a new geometry object (triangle w/collision) with the function arguments
    @param [out] ARG0 Pointer to a geometry object (triangle w/collision)
    @param [in] ARG1 Position vector - origin
    @param [in] ARG2 Direction vector - edge from point 0 to point 1
    @param [in] ARG3 Direction vector - edge from point 0 to point 2 */
TgINLINE TgVOID
FCN_VO(tgGM_CT_Init_E)(
    VEC_OBJ_T(TgCTRI,PCU) NONULL ARG0, VEC_T(1,C) ARG1, VEC_T(1,C) ARG2, VEC_T(1,C) ARG3 );

/** @brief Initialize a geometry object (triangle w/collision) from a geometry object (triangle)
    @param [out] ARG0 Pointer to a geometry object (triangle w/collision)
    @param [in] ARG1 Pointer to a geometry object (triangle) */
TgINLINE TgVOID
FCN_VO(tgGM_CT_Init_PT)(
    VEC_OBJ_T(TgCTRI,PCU) NONULL ARG0, VEC_OBJ_T(TgPTRI,CPCU) NONULL ARG1 );

/** @brief Initialize a geometry object (triangle w/collision) from a geometry object (triangle)
    @param [out] ARG0 Pointer to a geometry object (triangle w/collision)
    @param [in] ARG1 Pointer to a geometry object (triangle w/edge) */
TgINLINE TgVOID
FCN_VO(tgGM_CT_Init_ET)(
    VEC_OBJ_T(TgCTRI,PCU) NONULL ARG0, VEC_OBJ_T(TgETRI,CPCU) NONULL ARG1 );

/** @brief Copy the one geometry object (triangle w/collision) to another of the same type
    @param [out] ARG0 Pointer to a geometry object (triangle w/collision)
    @param [in] ARG1 Pointer to a geometry object (triangle w/collision) */
TgINLINE TgVOID
FCN_VO(tgGM_CT_Copy)(
    VEC_OBJ_T(TgCTRI,PCU) NONULL ARG0, VEC_OBJ_T(TgCTRI,CPCU) NONULL ARG1 );


/** @brief Set the origin / first point of the triangle
    @param [in,out] ARG0 Pointer to a geometry object (triangle w/collision)
    @param [in] ARG1 Position vector */
TgINLINE TgVOID
FCN_VO(tgGM_CT_Set_Origin)(
    VEC_OBJ_T(TgCTRI,PCU) NONULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Set the first point of the triangle
    @param [in,out] ARG0 Pointer to a geometry object (triangle w/collision)
    @param [in] ARG1 Position vector */
TgINLINE TgVOID
FCN_VO(tgGM_CT_Set_Point_0)(
    VEC_OBJ_T(TgCTRI,PCU) NONULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Set the second point of the triangle
    @param [in,out] ARG0 Pointer to a geometry object (triangle w/collision)
    @param [in] ARG1 Position vector */
TgINLINE TgVOID
FCN_VO(tgGM_CT_Set_Point_1)(
    VEC_OBJ_T(TgCTRI,PCU) NONULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Set the third point of the triangle
    @param [in,out] ARG0 Pointer to a geometry object (triangle w/collision)
    @param [in] ARG1 Position vector */
TgINLINE TgVOID
FCN_VO(tgGM_CT_Set_Point_2)(
    VEC_OBJ_T(TgCTRI,PCU) NONULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Set the first edge of the triangle between point 0 and point 1
    @param [in,out] ARG0 Pointer to a geometry object (triangle w/collision)
    @param [in] ARG1 Direction vector - edge between point 0 and point 1 */
TgINLINE TgVOID
FCN_VO(tgGM_CT_Set_Edge_0)(
    VEC_OBJ_T(TgCTRI,PCU) NONULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Set the first edge of the triangle between point 1 and point 2
    @param [in,out] ARG0 Pointer to a geometry object (triangle w/collision)
    @param [in] ARG1 Direction vector - edge between point 1 and point 2 */
TgINLINE TgVOID
FCN_VO(tgGM_CT_Set_Edge_1)(
    VEC_OBJ_T(TgCTRI,PCU) NONULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Set the first edge of the triangle between point 2 and point 0
    @param [in,out] ARG0 Pointer to a geometry object (triangle w/collision)
    @param [in] ARG1 Direction vector - edge between point 2 and point 0 */
TgINLINE TgVOID
FCN_VO(tgGM_CT_Set_Edge_2)(
    VEC_OBJ_T(TgCTRI,PCU) NONULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Set the collision flags for the triangle
    @param [in,out] ARG0 Pointer to a geometry object (triangle w/collision)
    @param [in] ARG1 Bitfield (32bit) */
TgINLINE TgVOID
FCN_VO(tgGM_CT_Set_Flags)(
    VEC_OBJ_T(TgCTRI,PCU), TgUINT_F32_C );


/** @brief Return the origin / first point of the triangle
    @param [in] ARG Pointer to a geometry object (triangle w/collision)
    @return The origin / first point of the triangle */
TgINLINE VEC_T(1)
FCN_VO(tgGM_CT_Query_Origin)(
    VEC_OBJ_T(TgCTRI,CPCU) NONULL ARG );

/** @brief Return the normal of the plane
    @param [in] ARG Pointer to a geometry object (triangle w/collision)
    @return The normal of the plane */
TgINLINE VEC_T(1)
FCN_VO(tgGM_CT_Query_Normal)(
    VEC_OBJ_T(TgCTRI,CPCU) NONULL ARG );

/** @brief Return the first point of the triangle
    @param [in] ARG Pointer to a geometry object (triangle w/collision)
    @return The first point of the triangle */
TgINLINE VEC_T(1)
FCN_VO(tgGM_CT_Query_Point_0)(
    VEC_OBJ_T(TgCTRI,CPCU) NONULL ARG );

/** @brief Return the second point of the triangle
    @param [in] ARG Pointer to a geometry object (triangle w/collision)
    @return The second point of the triangle */
TgINLINE VEC_T(1)
FCN_VO(tgGM_CT_Query_Point_1)(
    VEC_OBJ_T(TgCTRI,CPCU) NONULL ARG );

/** @brief Return the third point of the triangle
    @param [in] ARG Pointer to a geometry object (triangle w/collision)
    @return The third point of the triangle */
TgINLINE VEC_T(1)
FCN_VO(tgGM_CT_Query_Point_2)(
    VEC_OBJ_T(TgCTRI,CPCU) NONULL ARG );

/** @brief Return the specified point
    @param [in,out] ARG0 Pointer to a geometry object (triangle w/collision)
    @param [in] ARG1 Point index [0-2]
    @return The specified point */
TgINLINE VEC_T(1)
FCN_VO(tgGM_CT_Query_Point)(
    VEC_OBJ_T(TgCTRI,CPCU) NONULL ARG0, TgRSIZE_C ARG1 );

/** @brief Return the first edge of the triangle (point 0 to point 1)
    @param [in] ARG Pointer to a geometry object (triangle w/collision)
    @return The first edge of the triangle (point 0 to point 1) */
TgINLINE VEC_T(1)
FCN_VO(tgGM_CT_Query_Edge_0)(
    VEC_OBJ_T(TgCTRI,CPCU) NONULL ARG );

/** @brief Return the second edge of the triangle (point 1 to point 2)
    @param [in] ARG Pointer to a geometry object (triangle w/collision)
    @return The second edge of the triangle (point 1 to point 2) */
TgINLINE VEC_T(1)
FCN_VO(tgGM_CT_Query_Edge_1)(
    VEC_OBJ_T(TgCTRI,CPCU) NONULL ARG );

/** @brief Return the third edge of the triangle (point 2 to point 0)
    @param [in] ARG Pointer to a geometry object (triangle w/collision)
    @return The third edge of the triangle (point 2 to point 0) */
TgINLINE VEC_T(1)
FCN_VO(tgGM_CT_Query_Edge_2)(
    VEC_OBJ_T(TgCTRI,CPCU) NONULL ARG );

/** @brief Return the specified edge
    @param [in] ARG0 Pointer to a geometry object (triangle w/collision)
    @param [in] ARG1 Edge index [0-2]
    @return The specified edge */
TgINLINE VEC_T(1)
FCN_VO(tgGM_CT_Query_Edge)(
    VEC_OBJ_T(TgCTRI,CPCU) NONULL ARG0, TgRSIZE_C ARG1 );

/** @brief Return a pointer to a geometry object (triangle)
    @param [in] ARG Pointer to a geometry object (triangle w/collision)
    @return A pointer to a geometry object (triangle) */
TgINLINE VEC_OBJ_T(TgPTRI,CP)
FCN_VO(tgGM_CT_Query_PT)(
    VEC_OBJ_T(TgCTRI,CPCU) NONULL ARG );

/** @brief Return a pointer to a geometry object (triangle w/edge)
    @param [in] ARG Pointer to a geometry object (triangle w/collision)
    @return A pointer to a geometry object (triangle w/edge) */
TgINLINE VEC_OBJ_T(TgETRI,CP)
FCN_VO(tgGM_CT_Query_ET)(
    VEC_OBJ_T(TgCTRI,CPCU) NONULL ARG );

/** @brief Return the entire bitfield of collision flags
    @param [in] ARG Pointer to a geometry object (triangle w/collision)
    @return The entire bitfield of collision flags */
TgINLINE TgUINT_F32
FCN_VO(tgGM_CT_Query_Flags)(
    VEC_OBJ_T(TgCTRI,CPCU) NONULL ARG );


/** @brief Set the collision flag for the specified point
    @param [in,out] ARG0 Pointer to a geometry object (triangle w/collision)
    @param [in] ARG1 Edge index [0-2]
    @param [in] ARG2 Boolean - True to enable the point and false otherwise */
TgINLINE TgVOID
FCN_VO(tgGM_CT_Set_Test_Point)(
    VEC_OBJ_T(TgCTRI,PCU) NONULL ARG0, TgRSIZE_C ARG1, TgBOOL_C ARG2 );

/** @brief Set the collision flag for the first point
    @param [in,out] ARG0 Pointer to a geometry object (triangle w/collision)
    @param [in] ARG1 Boolean - True to enable the point and false otherwise */
TgINLINE TgVOID
FCN_VO(tgGM_CT_Set_Test_Point_0)(
    VEC_OBJ_T(TgCTRI,PCU) NONULL ARG0, TgBOOL_C ARG1 );

/** @brief Set the collision flag for the second point
    @param [in,out] ARG0 Pointer to a geometry object (triangle w/collision)
    @param [in] ARG1 Boolean - True to enable the point and false otherwise */
TgINLINE TgVOID
FCN_VO(tgGM_CT_Set_Test_Point_1)(
    VEC_OBJ_T(TgCTRI,PCU) NONULL ARG0, TgBOOL_C ARG1 );

/** @brief Set the collision flag for the third point
    @param [in,out] ARG0 Pointer to a geometry object (triangle w/collision)
    @param [in] ARG1 Boolean - True to enable the point and false otherwise */
TgINLINE TgVOID
FCN_VO(tgGM_CT_Set_Test_Point_2)(
    VEC_OBJ_T(TgCTRI,PCU) NONULL ARG0, TgBOOL_C ARG1 );

/** @brief Set the collision flag for the specified edge
    @param [in,out] ARG0 Pointer to a geometry object (triangle w/collision)
    @param [in] ARG1 Edge index [0-2]
    @param [in] ARG2 Boolean - True to enable the edge and false otherwise */
TgINLINE TgVOID
FCN_VO(tgGM_CT_Set_Test_Edge)(
    VEC_OBJ_T(TgCTRI,PCU) NONULL ARG0, TgRSIZE_C ARG1, TgBOOL_C ARG2 );

/** @brief Set the collision flag for the first edge (point 0 to point1)
    @param [in,out] ARG0 Pointer to a geometry object (triangle w/collision)
    @param [in] ARG1 Boolean - True to enable the edge and false otherwise */
TgINLINE TgVOID
FCN_VO(tgGM_CT_Set_Test_Edge_0)(
    VEC_OBJ_T(TgCTRI,PCU) NONULL ARG0, TgBOOL_C ARG1 );

/** @brief Set the collision flag for the first edge (point 0 to point2)
    @param [in,out] ARG0 Pointer to a geometry object (triangle w/collision)
    @param [in] ARG1 Boolean - True to enable the edge and false otherwise */
TgINLINE TgVOID
FCN_VO(tgGM_CT_Set_Test_Edge_1)(
    VEC_OBJ_T(TgCTRI,PCU) NONULL ARG0, TgBOOL_C ARG1 );

/** @brief Set the collision flag for the first edge (point 1 to point2)
    @param [in,out] ARG0 Pointer to a geometry object (triangle w/collision)
    @param [in] ARG1 Boolean - True to enable the edge and false otherwise */
TgINLINE TgVOID
FCN_VO(tgGM_CT_Set_Test_Edge_2)(
    VEC_OBJ_T(TgCTRI,PCU) NONULL ARG0, TgBOOL_C ARG1 );


/** @brief Determine if the specified point should be considered during collision testing
    @param [in] ARG0 Pointer to a geometry object (triangle w/collision)
    @param [in] ARG1 Point index [0-2]
    @return True if the specified point should be considered during collision testing and false otherwise */
TgINLINE TgBOOL
FCN_VO(tgGM_CT_Test_Point)(
    VEC_OBJ_T(TgCTRI,CPCU) NONULL ARG0, TgRSIZE_C ARG1 );

/** @brief Determine if the first point should be considered during collision testing
    @param [in] ARG Pointer to a geometry object (triangle w/collision)
    @return True if the first point should be considered during collision testing and false otherwise */
TgINLINE TgBOOL
FCN_VO(tgGM_CT_Test_Point_0)(
    VEC_OBJ_T(TgCTRI,CPCU) NONULL ARG );

/** @brief Determine if the second point should be considered during collision testing
    @param [in] ARG Pointer to a geometry object (triangle w/collision)
    @return True if the second point should be considered during collision testing and false otherwise */
TgINLINE TgBOOL
FCN_VO(tgGM_CT_Test_Point_1)(
    VEC_OBJ_T(TgCTRI,CPCU) NONULL ARG );

/** @brief Determine if the third point should be considered during collision testing
    @param [in] ARG Pointer to a geometry object (triangle w/collision)
    @return True if the third point should be considered during collision testing and false otherwise */
TgINLINE TgBOOL
FCN_VO(tgGM_CT_Test_Point_2)(
    VEC_OBJ_T(TgCTRI,CPCU) NONULL ARG );

/** @brief Determine if the specified point should be considered during collision testing
    @param [in] ARG0 Pointer to a geometry object (triangle w/collision)
    @param [in] ARG1 Point index [0-2]
    @return True if the specified point should be considered during collision testing and false otherwise */
TgINLINE TgBOOL
FCN_VO(tgGM_CT_Test_Edge)(
    VEC_OBJ_T(TgCTRI,CPCU) NONULL ARG0, TgRSIZE_C ARG1 );

/** @brief Determine if the first edge should be considered during collision testing
    @param [in] ARG Pointer to a geometry object (triangle w/collision)
    @return True if the first edge should be considered during collision testing and false otherwise */
TgINLINE TgBOOL
FCN_VO(tgGM_CT_Test_Edge_0)(
    VEC_OBJ_T(TgCTRI,CPCU) NONULL ARG );

/** @brief Determine if the second edge should be considered during collision testing
    @param [in] ARG Pointer to a geometry object (triangle w/collision)
    @return True if the second edge should be considered during collision testing and false otherwise */
TgINLINE TgBOOL
FCN_VO(tgGM_CT_Test_Edge_1)(
    VEC_OBJ_T(TgCTRI,CPCU) NONULL ARG );

/** @brief Determine if the third edge should be considered during collision testing
    @param [in] ARG Pointer to a geometry object (triangle w/collision)
    @return True if the third edge should be considered during collision testing and false otherwise */
TgINLINE TgBOOL
FCN_VO(tgGM_CT_Test_Edge_2)(
    VEC_OBJ_T(TgCTRI,CPCU) NONULL ARG );


/** @} TGS_COMMON_GEOMETRY_CT */

/* =============================================================================================================================================================================== */
#endif
