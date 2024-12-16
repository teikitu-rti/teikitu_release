/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Triangle.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_TRIANGLE_H)
#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* == Collision ================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions - Scalar Functions                                                                                                                                            */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @addtogroup TGS_COLLISION_TRIANGLE */
/** @{ */

/* Triangle - Point                                                                                                                                                                */

/** @brief Calculate the minimal distance squared between a triangle and a point.
    @param [in] ARG0 Pointer to a triangle (edge) object.
    @param [in] ARG1 Vector holding a position (point).
    @return Minimal distance squared between the triangle and point, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_ET_DistSq_PT)(
    VEC_OBJ_T(TgETRI,CPC) ARG0, VEC_T(1,C) ARG1 );

/** @brief Calculate the minimal distance between a triangle and a point.
    @param [in] ARG0 Pointer to a triangle (edge) object.
    @param [in] ARG1 Vector holding a position (point).
    @return Minimal distance between the triangle and point, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_ET_Dist_PT)(
    VEC_OBJ_T(TgETRI,CPC) ARG0, VEC_T(1,C) ARG1 );

/** @brief Calculate the minimal distance squared between a triangle and a point, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG2 on ARG1.
    @param [in] ARG1 Pointer to a triangle (edge) object.
    @param [in] ARG2 Vector holding a position (point).
    @return Minimal distance squared between the triangle and point, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_ET_ClosestSq_PT)(
    VEC_T(1,PC) OUT0, VEC_OBJ_T(TgETRI,CPC) ARG1, VEC_T(1,C) ARG2 );

/** @brief Calculate the minimal distance between a triangle and a point, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG2 on ARG1.
    @param [in] ARG1 Pointer to a triangle (edge) object.
    @param [in] ARG2 Vector holding a position (point).
    @return Minimal distance between the triangle and point, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_ET_Closest_PT)(
    VEC_T(1,PC) OUT0, VEC_OBJ_T(TgETRI,CPC) ARG1, VEC_T(1,C) ARG2 );

/** @brief Calculate the minimal distance squared between a triangle and a point, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the 1st barycentric coordinate of the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the 2nd barycentric coordinate of the closest point to ARG3 on ARG2.
    @param [in] ARG2 Pointer to a triangle (edge) object.
    @param [in] ARG3 Vector holding a position (point).
    @return Minimal distance squared between a triangle and a point, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_ET_Closest_PM_PT)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgETRI,CPC) ARG2, VEC_T(1,C) ARG3 );

/** @brief Calculate the minimal distance between a triangle and a point, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the 1st barycentric coordinate of the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the 2nd barycentric coordinate of the closest point to ARG3 on ARG2.
    @param [in] ARG2 Pointer to a triangle (edge) object.
    @param [in] ARG3 Vector holding a position (point).
    @return Minimal distance between a triangle and a point, or zero otherwise, broadcast across all vector lanes. */
TgEXTN VEC_T(1)
FCN_VO(tgCO_ET_ClosestSq_PM_PT)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgETRI,CPC) ARG2, VEC_T(1,C) ARG3 );

/* Triangle - Line                                                                                                                                                                 */

/** @brief Calculate the minimal distance squared between a triangle and a line.
    @param [in] ARG0 Pointer to a triangle (space) object.
    @param [in] ARG1 Pointer to a line object.
    @return Minimal distance squared between a triangle and a line, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_ST_DistSq_LN) (
    VEC_OBJ_T(TgSTRI,CPC) ARG0, VEC_OBJ_T(TgLINE,CPC) ARG1 );

/** @brief Calculate the minimal distance between a triangle and a line.
    @param [in] ARG0 Pointer to a triangle (space) object.
    @param [in] ARG1 Pointer to a line object.
    @return Minimal distance between a triangle and a line, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_ST_Dist_LN)(
    VEC_OBJ_T(TgSTRI,CPC) ARG0, VEC_OBJ_T(TgLINE,CPC) ARG1 );

/** @brief Calculate the minimal distance squared between a triangle and a line, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a triangle (space) object.
    @param [in] ARG3 Pointer to a line object.
    @return Minimal distance squared between the triangle and line, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_ST_ClosestSq_LN)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgSTRI,CPC) ARG2, VEC_OBJ_T(TgLINE,CPC) ARG3 );

/** @brief Calculate the minimal distance between a triangle and a line, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a triangle (space) object.
    @param [in] ARG3 Pointer to a line object.
    @return Minimal distance between the triangle and line, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_ST_Closest_LN)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgSTRI,CPC) ARG2, VEC_OBJ_T(TgLINE,CPC) ARG3 );

/** @brief Calculate the minimal distance squared between a triangle and a line, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the 1st barycentric coordinate of the closest point to ARG4 on ARG3.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the 2nd barycentric coordinate of the closest point to ARG4 on ARG3.
    @param [out] OUT2 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG3 on ARG4.
    @param [in] ARG3 Pointer to a triangle (space) object.
    @param [in] ARG4 Pointer to a line object.
    @return Minimal distance squared between the triangle and line, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_ST_ClosestSq_PM_LN)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_OBJ_T(TgSTRI,CPC) ARG3, VEC_OBJ_T(TgLINE,CPC) ARG4 );

/** @brief Calculate the minimal distance between a triangle and a line, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the 1st barycentric coordinate of the closest point to ARG4 on ARG3.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the 2nd barycentric coordinate of the closest point to ARG4 on ARG3.
    @param [out] OUT2 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG3 on ARG4.
    @param [in] ARG3 Pointer to a triangle (space) object.
    @param [in] ARG4 Pointer to a line object.
    @return Minimal distance between the triangle and line, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_ST_Closest_PM_LN)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_OBJ_T(TgSTRI,CPC) ARG3, VEC_OBJ_T(TgLINE,CPC) ARG4 );

/** @brief Calculate the minimal distance between a triangle and a line, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the 1st barycentric coordinate of the closest point to {ARG4,ARG5} on ARG3.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the 2nd barycentric coordinate of the closest point to {ARG4,ARG5} on ARG3.
    @param [out] OUT2 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG3 on {ARG4,ARG5}.
    @param [in] ARG3 Pointer to a triangle (space) object.
    @param [in] ARG4 Vector holding the Line Origin.
    @param [in] ARG5 Vector holding the Line Direction.
    @return Minimal distance between the triangle and line, or zero otherwise, broadcast across all vector lanes. */
TgEXTN VEC_T(1)
FCN_VO(tgCO_ST_ClosestSq_PM_LR00)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_OBJ_T(TgSTRI,CPC) ARG3, VEC_T(1,C) ARG4, VEC_T(1,C) ARG5 );


/** @brief Determine if the two primitives are intersecting.
    @param [in] ARG0 Pointer to a triangle (space) object.
    @param [in] ARG1 Pointer to a line object.
    @return True if the two primitives are intersecting, and false otherwise. */
TgINLINE TgBOOL
FCN_VO(tgCO_ET_Test_LN)(
    VEC_OBJ_T(TgETRI,CPC) ARG0, VEC_OBJ_T(TgLINE,CPC) ARG1 );


/** @brief Update the collision packet with point(s) of intersection between a triangle and a line.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
    @param [in] ARG1 Pointer to triangle (edge) object.
    @param [in] ARG2 Pointer to a line object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_ET_Intersect_LN)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgETRI,CPC) ARG1, VEC_OBJ_T(TgLINE,CPC) ARG2 );

/** @brief Update the collision packet with point(s) of intersection between a triangle and a line.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the 1st barycentric coordinate of the closest point to ARG4 on ARG3.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the 2nd barycentric coordinate of the closest point to ARG4 on ARG3.
    @param [out] OUT2 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG3 on ARG4.
    @param [in] ARG3 Pointer to triangle (edge) object.
    @param [in] ARG4 Pointer to a line object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_ET_Intersect_PM_LN)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_OBJ_T(TgETRI,CPC) ARG3, VEC_OBJ_T(TgLINE,CPC) ARG4 );

/** @brief Update the collision packet with point(s) of intersection between a triangle and a line.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the 1st barycentric coordinate of the closest point to {ARG4,ARG5} on ARG3.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the 2nd barycentric coordinate of the closest point to {ARG4,ARG5} on ARG3.
    @param [out] OUT2 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG3 on {ARG4,ARG5}.
    @param [in] ARG3 Pointer to triangle (edge) object.
    @param [in] ARG4 Vector holding the Line Origin.
    @param [in] ARG5 Vector holding the Line Direction.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_ET_Intersect_PM_LR00)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_OBJ_T(TgETRI,CPC) ARG3, VEC_T(1,C) ARG4, VEC_T(1,C) ARG5 );


/** @brief Output the sequence of points created by clipping the line to the interior of the triangle.
    @param [out] OUT0 Pointer to a clip list object, where the resulting points are stored.
    @param [in] ARG1 Pointer to a triangle (space) object.
    @param [in] ARG2 Pointer to a line object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_ST_Clip_LN)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, VEC_OBJ_T(TgSTRI,CPC) ARG1, VEC_OBJ_T(TgLINE,CPC) ARG2 );

/** @brief Output the sequence of points created by clipping the line to the interior of the triangle.
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point from clipping the line.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the 2nd point from clipping the line.
    @param [in] ARG2 Pointer to a triangle (space) object.
    @param [in] ARG3 Pointer to a line object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_ST_Clip_PM_LN)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgSTRI,CPC) ARG2, VEC_OBJ_T(TgLINE,CPC) ARG3 );

/** @brief Output the sequence of points created by clipping the line to the interior of the triangle.
    @param [out] OUT0 Pointer to a clip list object, where the resulting points are stored.
    @param [in] ARG1 Pointer to a triangle (space) object.
    @param [in] ARG2 Vector holding the Line Origin.
    @param [in] ARG3 Vector holding the Line Direction.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_ST_Clip_LR00)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, VEC_OBJ_T(TgSTRI,CPC) ARG1, VEC_T(1,C) ARG2, VEC_T(1,C) ARG3 );

/** @brief Output the sequence of points created by clipping the line to the interior of the triangle.
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point from clipping the line.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the 2nd point from clipping the line.
    @param [in] ARG2 Pointer to a triangle (space) object.
    @param [in] ARG3 Vector holding the Line Origin.
    @param [in] ARG4 Vector holding the Line Direction.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_ST_Clip_PM_LR00)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgSTRI,CPC) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4 );


/** @brief Output the sequence of points created by clipping the line to the interior of the triangle.
    @param [out] OUT0 Pointer to a clip list object, where the resulting points are stored.
    @param [out] OUT1 Pointer to a bitfield that stores the features responsible for clipping the line.
    @param [in] ARG2 Pointer to a triangle (space) object.
    @param [in] ARG3 Pointer to a line object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_ST_Clip_F_LN)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, TgSINT_E32_PC OUT1, VEC_OBJ_T(TgSTRI,CPC) ARG2, VEC_OBJ_T(TgLINE,CPC) ARG3 );

/** @brief Output the sequence of points created by clipping the line to the interior of the triangle.
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point from clipping the line.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the 2nd point from clipping the line.
    @param [out] OUT1 Pointer to a bitfield that stores the features responsible for clipping the line.
    @param [in] ARG3 Pointer to a triangle (space) object.
    @param [in] ARG4 Pointer to a line object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_ST_Clip_PM_F_LN)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, TgSINT_E32_PC OUT2, VEC_OBJ_T(TgSTRI,CPC) ARG3, VEC_OBJ_T(TgLINE,CPC) ARG4 );

/** @brief Output the sequence of points created by clipping the line to the interior of the triangle.
    @param [out] OUT0 Pointer to a clip list object, where the resulting points are stored.
    @param [out] OUT1 Pointer to a bitfield that stores the features responsible for clipping the line.
    @param [in] ARG2 Pointer to a triangle (space) object.
    @param [in] ARG3 Vector holding the Line Origin.
    @param [in] ARG4 Vector holding the Line Direction.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_ST_Clip_F_LR00)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, TgSINT_E32_PC OUT1, VEC_OBJ_T(TgSTRI,CPC) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4 );

/** @brief Output the sequence of points created by clipping the line to the interior of the triangle.
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point from clipping the line.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the 2nd point from clipping the line.
    @param [out] OUT2 Pointer to a bitfield that stores the features responsible for clipping the line.
    @param [in] ARG3 Pointer to a triangle (space) object.
    @param [in] ARG4 Vector holding the Line Origin.
    @param [in] ARG5 Vector holding the Line Direction.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_ST_Clip_PM_F_LR00)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, TgSINT_E32_PC OUT2, VEC_OBJ_T(TgSTRI,CPC) ARG3, VEC_T(1,C) ARG4, VEC_T(1,C) ARG5 );


/* Triangle - Ray                                                                                                                                                                  */

/** @brief Calculate the minimal distance squared between a triangle and a ray.
    @param [in] ARG0 Pointer to a triangle (space) object.
    @param [in] ARG1 Pointer to a ray object.
    @return Minimal distance squared between a triangle and a ray, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_ST_DistSq_RY)(
    VEC_OBJ_T(TgSTRI,CPC) ARG0, VEC_OBJ_T(TgRAY,CPC) ARG1 );

/** @brief Calculate the minimal distance between a triangle and a ray.
    @param [in] ARG0 Pointer to a triangle (space) object.
    @param [in] ARG1 Pointer to a ray object.
    @return Minimal distance between a triangle and a ray, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_ST_Dist_RY)(
    VEC_OBJ_T(TgSTRI,CPC) ARG0, VEC_OBJ_T(TgRAY,CPC) ARG1 );

/** @brief Calculate the minimal distance squared between a triangle and a ray, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a triangle (space) object.
    @param [in] ARG3 Pointer to a ray object.
    @return Minimal distance squared between the triangle and ray, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_ST_ClosestSq_RY)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgSTRI,CPC) ARG2, VEC_OBJ_T(TgRAY,CPC) ARG3 );

/** @brief Calculate the minimal distance between a triangle and a ray, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a triangle (space) object.
    @param [in] ARG3 Pointer to a ray object.
    @return Minimal distance between the triangle and ray, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_ST_Closest_RY)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgSTRI,CPC) ARG2, VEC_OBJ_T(TgRAY,CPC) ARG3 );

/** @brief Calculate the minimal distance squared between a triangle and a ray, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the 1st barycentric coordinate of the closest point to ARG4 on ARG3.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the 2nd barycentric coordinate of the closest point to ARG4 on ARG3.
    @param [out] OUT2 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG3 on ARG4.
    @param [in] ARG3 Pointer to a triangle (space) object.
    @param [in] ARG4 Pointer to a ray object.
    @return Minimal distance squared between the triangle and ray, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_ST_ClosestSq_PM_RY)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_OBJ_T(TgSTRI,CPC) ARG3, VEC_OBJ_T(TgRAY,CPC) ARG4 );

/** @brief Calculate the minimal distance between a triangle and a ray, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the 1st barycentric coordinate of the closest point to ARG4 on ARG3.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the 2nd barycentric coordinate of the closest point to ARG4 on ARG3.
    @param [out] OUT2 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG3 on ARG4.
    @param [in] ARG3 Pointer to a triangle (space) object.
    @param [in] ARG4 Pointer to a ray object.
    @return Minimal distance between the triangle and ray, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_ST_Closest_PM_RY)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_OBJ_T(TgSTRI,CPC) ARG3, VEC_OBJ_T(TgRAY,CPC) ARG4 );

/** @brief Calculate the minimal distance between a triangle and a ray, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the 1st barycentric coordinate of the closest point to {ARG4,ARG5} on ARG3.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the 2nd barycentric coordinate of the closest point to {ARG4,ARG5} on ARG3.
    @param [out] OUT2 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG3 on {ARG4,ARG5}.
    @param [in] ARG3 Pointer to a triangle (space) object.
    @param [in] ARG4 Vector holding the Ray Origin.
    @param [in] ARG5 Vector holding the Ray Direction.
    @return Minimal distance between the triangle and ray, or zero otherwise, broadcast across all vector lanes. */
TgEXTN VEC_T(1)
FCN_VO(tgCO_ST_ClosestSq_PM_LR10)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_OBJ_T(TgSTRI,CPC) ARG3, VEC_T(1,C) ARG4, VEC_T(1,C) ARG5 );


/** @brief Determine if the two primitives are intersecting.
    @param [in] ARG0 Pointer to a triangle (edge) object.
    @param [in] ARG1 Pointer to a ray object.
    @return True if the two primitives are intersecting, and false otherwise. */
TgINLINE TgBOOL
    FCN_VO(tgCO_ET_Test_RY)(
        VEC_OBJ_T(TgETRI,CPC) ARG0, VEC_OBJ_T(TgRAY,CPC) ARG1 );


/** @brief Update the collision packet with point(s) of intersection between a triangle and a ray.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
    @param [in] ARG1 Pointer to triangle (edge) object.
    @param [in] ARG2 Pointer to a ray object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_ET_Intersect_RY)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgETRI,CPC) ARG1, VEC_OBJ_T(TgRAY,CPC) ARG2 );

/** @brief Update the collision packet with point(s) of intersection between a triangle and a ray.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the 1st barycentric coordinate of the closest point to ARG4 on ARG3.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the 2nd barycentric coordinate of the closest point to ARG4 on ARG3.
    @param [out] OUT2 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG3 on ARG4.
    @param [in] ARG3 Pointer to triangle (edge) object.
    @param [in] ARG4 Pointer to a ray object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_ET_Intersect_PM_RY)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_OBJ_T(TgETRI,CPC) ARG3, VEC_OBJ_T(TgRAY,CPC) ARG4 );

/** @brief Update the collision packet with point(s) of intersection between a triangle and a ray.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the 1st barycentric coordinate of the closest point to {ARG4,ARG5} on ARG3.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the 2nd barycentric coordinate of the closest point to {ARG4,ARG5} on ARG3.
    @param [out] OUT2 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG3 on {ARG4,ARG5}.
    @param [in] ARG3 Pointer to triangle (edge) object.
    @param [in] ARG4 Vector holding the Ray Origin.
    @param [in] ARG5 Vector holding the Ray Direction.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_ET_Intersect_PM_LR10)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_OBJ_T(TgETRI,CPC) ARG3, VEC_T(1,C) ARG4, VEC_T(1,C) ARG5 );


/** @brief Output the sequence of points created by clipping the ray to the interior of the triangle.
    @param [out] OUT0 Pointer to a clip list object, where the resulting points are stored.
    @param [in] ARG1 Pointer to a triangle (space) object.
    @param [in] ARG2 Pointer to a ray object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_ST_Clip_RY)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, VEC_OBJ_T(TgSTRI,CPC) ARG1, VEC_OBJ_T(TgRAY,CPC) ARG2 );

/** @brief Output the sequence of points created by clipping the ray to the interior of the triangle.
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point from clipping the ray.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the 2nd point from clipping the ray.
    @param [in] ARG2 Pointer to a triangle (space) object.
    @param [in] ARG3 Pointer to a ray object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_ST_Clip_PM_RY)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgSTRI,CPC) ARG2, VEC_OBJ_T(TgRAY,CPC) ARG3 );

/** @brief Output the sequence of points created by clipping the ray to the interior of the triangle.
    @param [out] OUT0 Pointer to a clip list object, where the resulting points are stored.
    @param [in] ARG1 Pointer to a triangle (space) object.
    @param [in] ARG2 Vector holding the Ray Origin.
    @param [in] ARG3 Vector holding the Ray Direction.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_ST_Clip_LR10)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, VEC_OBJ_T(TgSTRI,CPC) ARG1, VEC_T(1,C) ARG2, VEC_T(1,C) ARG3 );

/** @brief Output the sequence of points created by clipping the ray to the interior of the triangle.
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point from clipping the ray.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the 2nd point from clipping the ray.
    @param [in] ARG2 Pointer to a triangle (space) object.
    @param [in] ARG3 Vector holding the Ray Origin.
    @param [in] ARG4 Vector holding the Ray Direction.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_ST_Clip_PM_LR10)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgSTRI,CPC) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4 );


/** @brief Output the sequence of points created by clipping the ray to the interior of the triangle.
    @param [out] OUT0 Pointer to a clip list object, where the resulting points are stored.
    @param [out] OUT1 Pointer to a bitfield that stores the features responsible for clipping the ray.
    @param [in] ARG2 Pointer to a triangle (space) object.
    @param [in] ARG3 Pointer to a ray object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_ST_Clip_F_RY)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, TgSINT_E32_PC OUT1, VEC_OBJ_T(TgSTRI,CPC) ARG2, VEC_OBJ_T(TgRAY,CPC) ARG3 );

/** @brief Output the sequence of points created by clipping the ray to the interior of the triangle.
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point from clipping the ray.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the 2nd point from clipping the ray.
    @param [out] OUT2 Pointer to a bitfield that stores the features responsible for clipping the ray.
    @param [in] ARG3 Pointer to a triangle (space) object.
    @param [in] ARG4 Pointer to a ray object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_ST_Clip_PM_F_RY)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, TgSINT_E32_PC OUT2, VEC_OBJ_T(TgSTRI,CPC) ARG3, VEC_OBJ_T(TgRAY,CPC) ARG4 );

/** @brief Output the sequence of points created by clipping the ray to the interior of the triangle.
    @param [out] OUT0 Pointer to a clip list object, where the resulting points are stored.
    @param [out] OUT1 Pointer to a bitfield that stores the features responsible for clipping the ray.
    @param [in] ARG2 Pointer to a triangle (space) object.
    @param [in] ARG3 Vector holding the Ray Origin.
    @param [in] ARG4 Vector holding the Ray Direction.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_ST_Clip_F_LR10)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, TgSINT_E32_PC OUT1, VEC_OBJ_T(TgSTRI,CPC) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4 );

/** @brief Output the sequence of points created by clipping the ray to the interior of the triangle.
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point from clipping the ray.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the 2nd point from clipping the ray.
    @param [out] OUT2 Pointer to a bitfield that stores the features responsible for clipping the ray.
    @param [in] ARG3 Pointer to a triangle (space) object.
    @param [in] ARG4 Vector holding the Ray Origin.
    @param [in] ARG5 Vector holding the Ray Direction.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_ST_Clip_PM_F_LR10)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, TgSINT_E32_PC OUT2, VEC_OBJ_T(TgSTRI,CPC) ARG3, VEC_T(1,C) ARG4, VEC_T(1,C) ARG5 );


/* Triangle - Segment                                                                                                                                                              */

/** @brief Calculate the minimal distance squared between a triangle and a segment.
    @param [in] ARG0 Pointer to a triangle (space) object.
    @param [in] ARG1 Pointer to a segment object.
    @return Minimal distance squared between a triangle and a segment, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_ST_DistSq_SG)(
    VEC_OBJ_T(TgSTRI,CPC) ARG0, VEC_OBJ_T(TgSEGMENT,CPC) ARG1 );

/** @brief Calculate the minimal distance between a triangle and a segment.
    @param [in] ARG0 Pointer to a triangle (space) object.
    @param [in] ARG1 Pointer to a segment object.
    @return Minimal distance between a triangle and a segment, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_ST_Dist_SG)(
    VEC_OBJ_T(TgSTRI,CPC) ARG0, VEC_OBJ_T(TgSEGMENT,CPC) ARG1 );

/** @brief Calculate the minimal distance squared between a triangle and a segment, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a triangle (space) object.
    @param [in] ARG3 Pointer to a segment object.
    @return Minimal distance squared between the triangle and segment, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_ST_ClosestSq_SG)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgSTRI,CPC) ARG2, VEC_OBJ_T(TgSEGMENT,CPC) ARG3 );

/** @brief Calculate the minimal distance between a triangle and a segment, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a triangle (space) object.
    @param [in] ARG3 Pointer to a segment object.
    @return Minimal distance between the triangle and segment, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_ST_Closest_SG)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgSTRI,CPC) ARG2, VEC_OBJ_T(TgSEGMENT,CPC) ARG3 );

/** @brief Calculate the minimal distance squared between a triangle and a segment, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the 1st barycentric coordinate of the closest point to ARG4 on ARG3.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the 2nd barycentric coordinate of the closest point to ARG4 on ARG3.
    @param [out] OUT2 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG3 on ARG4.
    @param [in] ARG3 Pointer to a triangle (space) object.
    @param [in] ARG4 Pointer to a segment object.
    @return Minimal distance squared between the triangle and segment, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_ST_ClosestSq_PM_SG)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_OBJ_T(TgSTRI,CPC) ARG3, VEC_OBJ_T(TgSEGMENT,CPC) ARG4 );

/** @brief Calculate the minimal distance between a triangle and a segment, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the 1st barycentric coordinate of the closest point to ARG4 on ARG3.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the 2nd barycentric coordinate of the closest point to ARG4 on ARG3.
    @param [out] OUT2 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG3 on ARG4.
    @param [in] ARG3 Pointer to a triangle (space) object.
    @param [in] ARG4 Pointer to a segment object.
    @return Minimal distance between the triangle and segment, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_ST_Closest_PM_SG)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_OBJ_T(TgSTRI,CPC) ARG3, VEC_OBJ_T(TgSEGMENT,CPC) ARG4 );

/** @brief Calculate the minimal distance between a triangle and a segment, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the 1st barycentric coordinate of the closest point to {ARG4,ARG5} on ARG3.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the 2nd barycentric coordinate of the closest point to {ARG4,ARG5} on ARG3.
    @param [out] OUT2 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG3 on {ARG4,ARG5}.
    @param [in] ARG3 Pointer to a triangle (space) object.
    @param [in] ARG4 Vector holding the Segment Origin.
    @param [in] ARG5 Vector holding the position relative to the Segment Origin of the Segment Terminal Point.
    @return Minimal distance between the triangle and segment, or zero otherwise, broadcast across all vector lanes. */
TgEXTN VEC_T(1)
FCN_VO(tgCO_ST_ClosestSq_PM_LR11)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_OBJ_T(TgSTRI,CPC) ARG3, VEC_T(1,C) ARG4, VEC_T(1,C) ARG5 );


/** @brief Determine if the two primitives are intersecting.
    @param [in] ARG0 Pointer to a triangle (space) object.
    @param [in] ARG1 Pointer to a segment object.
    @return True if the two primitives are intersecting, and false otherwise. */
TgINLINE TgBOOL
FCN_VO(tgCO_ET_Test_SG)(
    VEC_OBJ_T(TgETRI,CPC) ARG0, VEC_OBJ_T(TgSEGMENT,CPC) ARG1 );


/** @brief Update the collision packet with point(s) of intersection between a triangle and a segment.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
    @param [in] ARG1 Pointer to triangle (edge) object.
    @param [in] ARG2 Pointer to a segment object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_ET_Intersect_SG)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgETRI,CPC) ARG1, VEC_OBJ_T(TgSEGMENT,CPC) ARG2 );

/** @brief Update the collision packet with point(s) of intersection between a triangle and a segment.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the 1st barycentric coordinate of the closest point to ARG4 on ARG3.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the 2nd barycentric coordinate of the closest point to ARG4 on ARG3.
    @param [out] OUT2 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG3 on ARG4.
    @param [in] ARG3 Pointer to triangle (edge) object.
    @param [in] ARG4 Pointer to a segment object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_ET_Intersect_PM_SG)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_OBJ_T(TgETRI,CPC) ARG3, VEC_OBJ_T(TgSEGMENT,CPC) ARG4 );

/** @brief Update the collision packet with point(s) of intersection between a triangle and a segment.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the 1st barycentric coordinate of the closest point to {ARG4,ARG5} on ARG3.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the 2nd barycentric coordinate of the closest point to {ARG4,ARG5} on ARG3.
    @param [out] OUT2 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG3 on {ARG4,ARG5}.
    @param [in] ARG3 Pointer to triangle (edge) object.
    @param [in] ARG4 Vector holding the Segment Origin.
    @param [in] ARG5 Vector holding the position relative to the Segment Origin of the Segment Terminal Point.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_ET_Intersect_PM_LR11)( 
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_OBJ_T(TgETRI,CPC) ARG3, VEC_T(1,C) ARG4, VEC_T(1,C) ARG5 );


/** @brief Output the sequence of points created by clipping the segment to the interior of the triangle.
    @param [out] OUT0 Pointer to a clip list object, where the resulting points are stored.
    @param [in] ARG1 Pointer to a triangle (space) object.
    @param [in] ARG2 Pointer to a segment object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_ST_Clip_SG)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, VEC_OBJ_T(TgSTRI,CPC) ARG1, VEC_OBJ_T(TgSEGMENT,CPC) ARG2 );

/** @brief Output the sequence of points created by clipping the segment to the interior of the triangle.
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point from clipping the segment.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the 2nd point from clipping the segment.
    @param [in] ARG2 Pointer to a triangle (space) object.
    @param [in] ARG3 Pointer to a segment object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_ST_Clip_PM_SG)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgSTRI,CPC) ARG2, VEC_OBJ_T(TgSEGMENT,CPC) ARG3 );

/** @brief Output the sequence of points created by clipping the segment to the interior of the triangle.
    @param [out] OUT0 Pointer to a clip list object, where the resulting points are stored.
    @param [in] ARG1 Pointer to a triangle (space) object.
    @param [in] ARG2 Vector holding the Segment Origin.
    @param [in] ARG3 Vector holding the position relative to the Segment Origin of the Segment Terminal Point.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_ST_Clip_LR11)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, VEC_OBJ_T(TgSTRI,CPC) ARG1, VEC_T(1,C), VEC_T(1,C) ARG2 );

/** @brief Output the sequence of points created by clipping the segment to the interior of the triangle.
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point from clipping the segment.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the 2nd point from clipping the segment.
    @param [in] ARG2 Pointer to a triangle (space) object.
    @param [in] ARG3 Vector holding the Segment Origin.
    @param [in] ARG4 Vector holding the position relative to the Segment Origin of the Segment Terminal Point.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_ST_Clip_PM_LR11)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgSTRI,CPC) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4 );


/** @brief Output the sequence of points created by clipping the segment to the interior of the triangle.
    @param [out] OUT0 Pointer to a clip list object, where the resulting points are stored.
    @param [out] OUT1 Pointer to a bitfield that stores the features responsible for clipping the segment.
    @param [in] ARG2 Pointer to a triangle (space) object.
    @param [in] ARG3 Pointer to a segment object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_ST_Clip_F_SG)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, TgSINT_E32_PC OUT1, VEC_OBJ_T(TgSTRI,CPC) ARG2, VEC_OBJ_T(TgSEGMENT,CPC) ARG3 );

/** @brief Output the sequence of points created by clipping the segment to the interior of the triangle.
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point from clipping the segment.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the 2nd point from clipping the segment.
    @param [out] OUT2 Pointer to a bitfield that stores the features responsible for clipping the segment.
    @param [in] ARG3 Pointer to a triangle (space) object.
    @param [in] ARG4 Pointer to a segment object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_ST_Clip_PM_F_SG)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, TgSINT_E32_PC OUT2, VEC_OBJ_T(TgSTRI,CPC) ARG3, VEC_OBJ_T(TgSEGMENT,CPC) ARG4 );

/** @brief Output the sequence of points created by clipping the segment to the interior of the triangle.
    @param [out] OUT0 Pointer to a clip list object, where the resulting points are stored.
    @param [out] OUT1 Pointer to a bitfield that stores the features responsible for clipping the segment.
    @param [in] ARG2 Pointer to a triangle (space) object.
    @param [in] ARG3 Vector holding the Segment Origin.
    @param [in] ARG4 Vector holding the position relative to the Segment Origin of the Segment Terminal Point.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_ST_Clip_F_LR11)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, TgSINT_E32_PC OUT1, VEC_OBJ_T(TgSTRI,CPC) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4 );

/** @brief Output the sequence of points created by clipping the segment to the interior of the triangle.
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point from clipping the segment.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the 2nd point from clipping the segment.
    @param [out] OUT2 Pointer to a bitfield that stores the features responsible for clipping the segment.
    @param [in] ARG3 Pointer to a triangle (space) object.
    @param [in] ARG4 Vector holding the Segment Origin.
    @param [in] ARG5 Vector holding the position relative to the Segment Origin of the Segment Terminal Point.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_ST_Clip_PM_F_LR11)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, TgSINT_E32_PC OUT2, VEC_OBJ_T(TgSTRI,CPC) ARG3, VEC_T(1,C) ARG4, VEC_T(1,C) ARG5 );


/* Triangle - Triangle                                                                                                                                                             */

/** @brief Calculate the minimal distance squared between a triangle and a triangle.
    @param [in] ARG0 Pointer to a triangle (space) object.
    @param [in] ARG1 Pointer to a triangle (space) object.
    @return Minimal distance squared between a triangle and a triangle, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_ST_DistSq_ST)(
    VEC_OBJ_T(TgSTRI,CPC) ARG0, VEC_OBJ_T(TgSTRI,CPC) ARG1 );

/** @brief Calculate the minimal distance between a triangle and a triangle.
    @param [in] ARG0 Pointer to a triangle (space) object.
    @param [in] ARG1 Pointer to a triangle (space) object.
    @return Minimal distance between a triangle and a triangle, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_ST_Dist_ST)(
    VEC_OBJ_T(TgSTRI,CPC) ARG0, VEC_OBJ_T(TgSTRI,CPC) ARG1 );

/** @brief Calculate the minimal distance squared between a triangle and a triangle, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a triangle (space) object.
    @param [in] ARG3 Pointer to a triangle (space) object.
    @return Minimal distance squared between the triangle and triangle, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_ST_ClosestSq_ST)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgSTRI,CPC) ARG2, VEC_OBJ_T(TgSTRI,CPC) ARG3 );

/** @brief Calculate the minimal distance between a triangle and a triangle, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a triangle (space) object.
    @param [in] ARG3 Pointer to a triangle (space) object.
    @return Minimal distance between the triangle and triangle, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_ST_Closest_ST)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgSTRI,CPC) ARG2, VEC_OBJ_T(TgSTRI,CPC) ARG3 );

/** @brief Calculate the minimal distance squared between a triangle and a triangle, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the 1st barycentric coordinate of the closest point to ARG5 on ARG4.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the 2nd barycentric coordinate of the closest point to ARG5 on ARG4.
    @param [out] OUT2 Pointer to a vector with a full broadcast of the 1st barycentric coordinate of the closest point to ARG4 on ARG5.
    @param [out] OUT3 Pointer to a vector with a full broadcast of the 2nd barycentric coordinate of the closest point to ARG4 on ARG5.
    @param [in] ARG4 Pointer to a triangle (space) object.
    @param [in] ARG5 Pointer to a triangle (space) object.
    @return Minimal distance squared between the triangle and triangle, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_ST_Closest_PM_ST)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_T(1,PC) OUT3, VEC_OBJ_T(TgSTRI,CPC) ARG4, VEC_OBJ_T(TgSTRI,CPC) ARG5 );

/** @brief Calculate the minimal distance between a triangle and a triangle, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the 1st barycentric coordinate of the closest point to ARG5 on ARG4.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the 2nd barycentric coordinate of the closest point to ARG5 on ARG4.
    @param [out] OUT2 Pointer to a vector with a full broadcast of the 1st barycentric coordinate of the closest point to ARG4 on ARG5.
    @param [out] OUT3 Pointer to a vector with a full broadcast of the 2nd barycentric coordinate of the closest point to ARG4 on ARG5.
    @param [in] ARG4 Pointer to a triangle (space) object.
    @param [in] ARG5 Pointer to a triangle (space) object.
    @return Minimal distance between the triangle and triangle, or zero otherwise, broadcast across all vector lanes. */
TgEXTN VEC_T(1)
FCN_VO(tgCO_ST_ClosestSq_PM_ST)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_T(1,PC) OUT3, VEC_OBJ_T(TgSTRI,CPC) ARG4, VEC_OBJ_T(TgSTRI,CPC) ARG5 );


/** @brief Determine if the two primitives are intersecting.
    @param [in] ARG0 Pointer to a triangle (space) object.
    @param [in] ARG1 Pointer to a triangle (space) object.
    @return True if the two primitives are intersecting, and false otherwise. */
TgEXTN TgBOOL
FCN_VO(tgCO_ST_Test_ST)(
    VEC_OBJ_T(TgSTRI,CPC) ARG0, VEC_OBJ_T(TgSTRI,CPC) ARG1 );

/** @brief Determine if the two primitives will touch due to the displacement.
    @param [in] ARG0 Pointer to a triangle (space) object.
    @param [in] ARG1 Pointer to a triangle (space) object.
    @param [in] ARG2 Pointer to an object holding displacement values for ARG1.
    @return True if the two primitives are intersecting, and false otherwise. */
TgEXTN TgBOOL
FCN_VO(tgCO_ST_Test_Sweep_ST)(
    VEC_OBJ_T(TgSTRI,CPC) ARG0, VEC_OBJ_T(TgSTRI,CPC) ARG1, VEC_OBJ_T(TgDELTA,CPC) ARG2 );


/** @brief Update the collision packet with point(s) of intersection between a triangle and a triangle.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new intersection points.
    @param [in] ARG1 Pointer to a triangle (space) object.
    @param [in] ARG2 Pointer to a triangle (space) object.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_ST_Intersect_ST)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgSTRI,CPC) ARG1, VEC_OBJ_T(TgSTRI,CPC) ARG2 );


/** @brief Update the collision packet with the result of sweeping a triangle versus a triangle.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG2.
                         Contact normal is the surface normal at the contact point on ARG2.
    @param [in,out] OUT1 Pointer to a vector with a full broadcast of the normalized time of contact (percentage of time step).
    @param [in] ARG2: Pointer to a triangle (space) object. The test is done inside of this object's reference frame.
    @param [in] ARG3: Pointer to a triangle (space) object.
    @param [in] ARG4 Pointer to an object holding displacement values for ARG3.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_ST_Sweep_ST)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgSTRI,CPC) ARG2, VEC_OBJ_T(TgSTRI,CPC) ARG3, VEC_OBJ_T(TgDELTA,CPC) ARG4);


/** @brief Output the sequence of points created by clipping the triangle to the interior of a triangle.
    @param [out] OUT0 Pointer to a clip list object, where the resulting points are stored.
    @param [in] ARG1 Pointer to a triangle (space) object.
    @param [in] ARG2 Pointer to a triangle (point) object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_ST_Clip_PT)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, VEC_OBJ_T(TgSTRI,CPC) ARG1, VEC_OBJ_T(TgPTRI,CPC) ARG2 );


/** @brief Determine if the two primitives will touch due to the displacement.
    @param [in] ARG0 Vector holding the axis of separation (axis of projection).
    @param [in] ARG1 Pointer to a triangle (point) object.
    @param [in] ARG2 Pointer to a triangle (point) object.
    @return True if the two primitives are intersecting, and false otherwise. */
TgEXTN TgBOOL
FCN_VO(tgCO_PT_Is_Seperating_Axis_PT)(
    VEC_T(1,C) ARG0, VEC_OBJ_T(TgPTRI,CPC) ARG2, VEC_OBJ_T(TgPTRI,CPC) ARG3 );

/** @brief Generate the needed information for a axis of separation test.
    @param [out] OUT0 Pointer to a structure used to inform axis separation evaluations.
    @param [in] ARG1 Vector holding the axis of separation (axis of projection).
    @param [in] ARG2 Pointer to a triangle (point) object.
   @return Result Code. */
TgEXTN TgVOID
FCN_VO(tgCO_PT_Axis_ProjInfo)(
    VEC_OBJ_T(STg2_CO_Axis_Project,PC) OUT0, VEC_T(1,C) ARG1, VEC_OBJ_T(TgPTRI,CPC) ARG2 );


/* Triangle - Box                                                                                                                                                                  */

/** @brief Update the collision packet with the result of sweeping a box versus a triangle.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG2.
                         Contact normal is the surface normal at the contact point on ARG2.
    @param [in,out] OUT1 Pointer to a vector with a full broadcast of the normalized time of contact (percentage of time step).
    @param [in] ARG2: Pointer to a triangle (space) object. The test is done inside of this object's reference frame.
    @param [in] ARG3: Pointer to a box object.
    @param [in] ARG4 Pointer to an object holding displacement values for ARG3.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_ST_Sweep_BX)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgSTRI,CPC) ARG2, VEC_OBJ_T(TgBOX,CPC) ARG3, VEC_OBJ_T(TgDELTA,CPC) ARG4 );


/* Triangle - Particle                                                                                                                                                             */

/** @brief Update the collision packet with the result of sweeping a triangle versus a particle.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG2.
                         Contact normal is the surface normal at the contact point on ARG2.
    @param [in,out] OUT1 Pointer to a vector with a full broadcast of the normalized time of contact (percentage of time step).
    @param [in] ARG2: Pointer to a particle object. The test is done inside of this object's reference frame.
    @param [in] ARG3: Pointer to a triangle (edge) object.
    @param [in] ARG4 Pointer to an object holding displacement values for ARG3.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_PC_Sweep_ET)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgPARTICLE,CPC) ARG2, VEC_OBJ_T(TgETRI,CPC) ARG3, VEC_OBJ_T(TgDELTA,CPC) ARG4 );

/** @brief Update the collision packet with the result of sweeping a particle versus a triangle.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG2.
                         Contact normal is the surface normal at the contact point on ARG2.
    @param [in,out] OUT1 Pointer to a vector with a full broadcast of the normalized time of contact (percentage of time step).
    @param [in] ARG2: Pointer to a triangle (edge) object. The test is done inside of this object's reference frame.
    @param [in] ARG3: Pointer to a particle object.
    @param [in] ARG4 Pointer to an object holding displacement values for ARG3.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_ET_Sweep_PC)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgETRI,CPC) ARG2, VEC_OBJ_T(TgPARTICLE,CPC) ARG3, VEC_OBJ_T(TgDELTA,CPC) ARG4 );

/* Triangle Utility                                                                                                                                                                */

/** @brief Clip a line segment to the interior of a triangle.
    @param [out] OUT0 Pointer to a vector holding the updated (clipped) point from ARG3.
    @param [out] OUT1 Pointer to a vector holding the updated (clipped) point from ARG4.
    @param [in] ARG2 Pointer to a triangle (space) object.
    @param [in] ARG3 Vector holding a position (point) representing the 1st (starting) point of a line segment.
    @param [in] ARG4 Vector holding a position (point) representing the 2nd (terminal) point of a line segment.
   @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_ST_Clip_Points)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgSTRI,CPC) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4 );

/** @brief Clip a line strip to the interior of a triangle.
    @param [in,out] OUT0 Pointer to a clip list object (an array of vectors interpreted as a line strip).
    @param [in] ARG1 Pointer to a triangle (space) object.
   @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_ST_Clip)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, VEC_OBJ_T(TgSTRI,CPC) ARG1 );

/** @brief Clip a clip list to the interior of a triangle.
    @param [in,out] OUT0 Pointer to a clip list object (an array of vectors interpreted as a line strip).
    @param [in] ARG1 Pointer to a triangle (space) object.
   @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_Clip_ST)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0,VEC_OBJ_T(TgSTRI,CPC) ARG1 );

/** @brief Clip a clip list to the interior of a triangle.
    @param [in,out] OUT0 Pointer to a clip list object (an array of vectors interpreted as a line strip).
    @param [in] ARG1 Pointer to a triangle (edge) object.
   @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_Clip_ET)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0,VEC_OBJ_T(TgETRI,CPC) ARG1 );


/** @} TGS_COLLISION_TRIANGLE */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* =============================================================================================================================================================================== */

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#else

    #define TEMPLATE_TYPE_EXPANSION__RELOAD

    #if TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE
        #define TEMPLATE__VECTOR_DIM 4
        #define TEMPLATE__TYPE_SIZE 64
        #include __FILE__
    #endif

    #define TEMPLATE__VECTOR_DIM 4
    #define TEMPLATE__TYPE_SIZE 32
    #include __FILE__

    #undef TEMPLATE_TYPE_EXPANSION__RELOAD

    #define TGS_COLLISION_TRIANGLE_H

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COLLISION_TRIANGLE_H) */
#endif
