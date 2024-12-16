/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Plane.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_PLANE_H)
#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* == Collision ================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions - Scalar Functions                                                                                                                                            */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @addtogroup TGS_COLLISION_PN */
/** @{ */

/* Plane - Point                                                                                                                                                                   */

/** @brief Calculate the minimal distance squared between a plane and a point.
    @param [in] ARG0 Pointer to a plane object.
    @param [in] ARG1 Vector holding a position (point).
    @return Minimal distance squared between the plane and point when the point is above the plane, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_PN_DistSq_PT)(
    VEC_OBJ_T(TgPLANE,CPC) ARG0, VEC_T(1,C) ARG1 );

/** @brief Calculate the minimal distance between a plane and a point.
    @param [in] ARG0 Pointer to a plane object.
    @param [in] ARG1 Vector holding a position (point).
    @return Minimal distance between the plane and point when the point is above the plane, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_PN_Dist_PT)(
    VEC_OBJ_T(TgPLANE,CPC) ARG0, VEC_T(1,C) ARG1 );

/** @brief Calculate the minimal distance squared between a plane and a point, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG2 on ARG1.
    @param [in] ARG1 Pointer to a plane object.
    @param [in] ARG2 Vector holding a position (point).
    @return Minimal distance squared between the plane and point when the point is above the plane, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_PN_ClosestSq_PT)(
    VEC_T(1,PC) OUT0, VEC_OBJ_T(TgPLANE,CPC) ARG1, VEC_T(1,C) ARG2 );

/** @brief Calculate the minimal distance between a plane and a point, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG2 on ARG1.
    @param [in] ARG1 Pointer to a plane object.
    @param [in] ARG2 Vector holding a position (point).
    @return Minimal distance between the plane and point when the point is above the plane, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_PN_Closest_PT)(
    VEC_T(1,PC) OUT0, VEC_OBJ_T(TgPLANE,CPC) ARG1, VEC_T(1,C) ARG2 );

/** @brief Calculate the minimal distance between a plane and a point.
    @param [in] ARG0 Pointer to a plane object.
    @param [in] ARG1 Vector holding a position (point).
    @return Minimal distance between the plane and point, positive for above the plane and negative for below the plane, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_PN_Sign_Dist_PT)(
    VEC_OBJ_T(TgPLANE,CPC) ARG0, VEC_T(1,C) ARG1 );

/** @brief Calculate the minimal distance between a plane and a point, and store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG2 on ARG1.
    @param [in] ARG1 Pointer to a plane object.
    @param [in] ARG2 Vector holding a position (point).
    @return Minimal distance between the plane and point, positive for above the plane and negative for below the plane, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_PN_Sign_Closest_PT)(
    VEC_T(1,PC) OUT0, VEC_OBJ_T(TgPLANE,CPC) ARG1, VEC_T(1,C) ARG2 );

/** @brief Determine if the point is completely above the plane.
    @param [in] ARG0 Pointer to a plane object.
    @param [in] ARG1 Vector holding a position (point).
    @return True if the point is completely above the plane, and false otherwise. */
TgINLINE TgBOOL
FCN_VO(tgCO_PN_Test_PT)(
    VEC_OBJ_T(TgPLANE,CPC) ARG0, VEC_T(1,C) ARG1 );


/* Plane - Line                                                                                                                                                                    */

/** @brief Calculate the minimal distance squared between a plane and a line.
    @param [in] ARG0 Pointer to a plane object.
    @param [in] ARG1 Pointer to a line object.
    @return Minimal distance squared between a plane and a line when it is above the plane, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_PN_DistSq_LN)(
    VEC_OBJ_T(TgPLANE,CPC) ARG0, VEC_OBJ_T(TgLINE,CPC) ARG1 );

/** @brief Calculate the minimal distance between a plane and a line.
    @param [in] ARG0 Pointer to a plane object.
    @param [in] ARG1 Pointer to a line object.
    @return Minimal distance between a plane and a line when it is above the plane, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_PN_Dist_LN)(
    VEC_OBJ_T(TgPLANE,CPC) ARG0, VEC_OBJ_T(TgLINE,CPC) ARG1 );

/** @brief Calculate the minimal distance squared between a plane and a line, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a plane object.
    @param [in] ARG3 Pointer to a line object.
    @return Minimal distance squared between the plane and line when it is above the plane, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_PN_ClosestSq_LN)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgPLANE,CPC) ARG2, VEC_OBJ_T(TgLINE,CPC) ARG3 );

/** @brief Calculate the minimal distance between a plane and a line, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a plane object.
    @param [in] ARG3 Pointer to a line object.
    @return Minimal distance between the plane and line when the line is above the plane, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_PN_Closest_LN)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgPLANE,CPC) ARG2, VEC_OBJ_T(TgLINE,CPC) ARG3 );

/** @brief Calculate the minimal distance squared between a plane and a line, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a plane object.
    @param [in] ARG3 Pointer to a line object.
    @return Minimal distance squared between the plane and line when it is above the plane, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_PN_ClosestSq_PM_LN)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgPLANE,CPC) ARG2, VEC_OBJ_T(TgLINE,CPC) ARG3 );

/** @brief Calculate the minimal distance between a plane and a line, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a plane object.
    @param [in] ARG3 Pointer to a line object.
    @return Minimal distance between the plane and line when it is above the plane, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_PN_Closest_PM_LN)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgPLANE,CPC) ARG2, VEC_OBJ_T(TgLINE,CPC) ARG3 );


/** @brief Determine if the line is completely above the plane.
    @param [in] ARG0 Pointer to a plane object.
    @param [in] ARG1 Pointer to a line object.
    @return True if the line is completely above the plane, and false otherwise. */
TgINLINE TgBOOL
FCN_VO(tgCO_PN_Test_LN)(
    VEC_OBJ_T(TgPLANE,CPC) ARG0, VEC_OBJ_T(TgLINE,CPC) ARG1 );


/** @brief Update the collision packet with point(s) of intersection between a plane and a line.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new intersection points.
    @param [in] ARG1 Pointer to a plane object.
    @param [in] ARG2 Pointer to a line object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_PN_Intersect_LN)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgPLANE,CPC) ARG1, VEC_OBJ_T(TgLINE,CPC) ARG2 );

/** @brief Update the collision packet with point(s) of intersection between a plane and a line.
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point from clipping the line.
    @param [in] ARG1 Pointer to a plane object.
    @param [in] ARG2 Pointer to a line object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_PN_Intersect_PM_LN)(
    VEC_T(1,PC) OUT0, VEC_OBJ_T(TgPLANE,CPC) ARG1, VEC_OBJ_T(TgLINE,CPC) ARG2 );


/** @brief Output the sequence of points created by clipping the line to the interior of the plane.
    @param [out] OUT0 Pointer to a clip list object, where the resulting points are stored.
    @param [in] ARG1 Pointer to a plane object.
    @param [in] ARG2 Pointer to a line object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_PN_Clip_LN)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, VEC_OBJ_T(TgPLANE,CPC) ARG1, VEC_OBJ_T(TgLINE,CPC) ARG2 );

/** @brief Output the sequence of points created by clipping the line to the interior of the plane.
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point from clipping the line.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the 2nd point from clipping the line.
    @param [in] ARG2 Pointer to a plane object.
    @param [in] ARG3 Pointer to a line object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_PN_Clip_PM_LN)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgPLANE,CPC) ARG2, VEC_OBJ_T(TgLINE,CPC) ARG3 );

/** @brief Output the sequence of points created by clipping the line to the interior of the plane.
    @param [out] OUT0 Pointer to a clip list object, where the resulting points are stored.
    @param [in] ARG1 Pointer to a plane object.
    @param [in] ARG2 Vector holding the Line Origin.
    @param [in] ARG3 Vector holding the Line Direction.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_PN_Clip_LR00)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, VEC_OBJ_T(TgPLANE,CPC) ARG1, VEC_T(1,C) ARG2, VEC_T(1,C) ARG3 );

/** @brief Output the sequence of points created by clipping the line to the interior of the plane.
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point from clipping the line.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the 2nd point from clipping the line.
    @param [in] ARG2 Pointer to a plane object.
    @param [in] ARG3 Vector holding the Line Origin.
    @param [in] ARG4 Vector holding the Line Direction.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_PN_Clip_PM_LR00)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgPLANE,CPC) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4 );


/* Plane - Ray                                                                                                                                                                     */

/** @brief Calculate the minimal distance squared between a plane and a ray.
    @param [in] ARG0 Pointer to a plane object.
    @param [in] ARG1 Pointer to a ray object.
    @return Minimal distance squared between a plane and a ray when it is above the plane, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_PN_DistSq_RY)(
    VEC_OBJ_T(TgPLANE,CPC) ARG0, VEC_OBJ_T(TgRAY,CPC) ARG1 );

/** @brief Calculate the minimal distance between a plane and a ray.
    @param [in] ARG0 Pointer to a plane object.
    @param [in] ARG1 Pointer to a ray object.
    @return Minimal distance between a plane and a ray when it is above the plane, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_PN_Dist_RY)(
    VEC_OBJ_T(TgPLANE,CPC) ARG0, VEC_OBJ_T(TgRAY,CPC) ARG1 );

/** @brief Calculate the minimal distance squared between a plane and a ray, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a plane object.
    @param [in] ARG3 Pointer to a ray object.
    @return Minimal distance squared between the plane and ray when it is above the plane, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_PN_ClosestSq_RY)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgPLANE,CPC) ARG2, VEC_OBJ_T(TgRAY,CPC) ARG3 );

/** @brief Calculate the minimal distance between a plane and a ray, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a plane object.
    @param [in] ARG3 Pointer to a ray object.
    @return Minimal distance between the plane and ray when the ray is above the plane, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_PN_Closest_RY)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgPLANE,CPC) ARG2, VEC_OBJ_T(TgRAY,CPC) ARG3 );

/** @brief Calculate the minimal distance squared between a plane and a ray, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a plane object.
    @param [in] ARG3 Pointer to a ray object.
    @return Minimal distance squared between the plane and ray when it is above the plane, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_PN_ClosestSq_PM_RY)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgPLANE,CPC) ARG2, VEC_OBJ_T(TgRAY,CPC) ARG3 );

/** @brief Calculate the minimal distance between a plane and a ray, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a plane object.
    @param [in] ARG3 Pointer to a ray object.
    @return Minimal distance between the plane and ray when it is above the plane, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_PN_Closest_PM_RY)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgPLANE,CPC) ARG2, VEC_OBJ_T(TgRAY,CPC) ARG3 );


/** @brief Determine if ray is completely above the plane.
    @param [in] ARG0 Pointer to a plane object.
    @param [in] ARG1 Pointer to a ray object.
    @return True if the ray is completely above the plane, and false otherwise. */
TgINLINE TgBOOL
FCN_VO(tgCO_PN_Test_RY)(
    VEC_OBJ_T(TgPLANE,CPC) ARG0, VEC_OBJ_T(TgRAY,CPC) ARG1 );


/** @brief Update the collision packet with point(s) of intersection between a cylinder and a segment.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new intersection points.
    @param [in] ARG1 Pointer to a plane object.
    @param [in] ARG2 Pointer to a ray object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_PN_Intersect_RY)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgPLANE,CPC) ARG1, VEC_OBJ_T(TgRAY,CPC) ARG2 );

/** @brief Update the collision packet with point(s) of intersection between a cylinder and a segment.
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point from clipping the ray.
    @param [in] ARG1 Pointer to a plane object.
    @param [in] ARG2 Pointer to a ray object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_PN_Intersect_PM_RY)(
    VEC_T(1,PC) OUT0, VEC_OBJ_T(TgPLANE,CPC) ARG1, VEC_OBJ_T(TgRAY,CPC) ARG2 );


/** @brief Output the sequence of points created by clipping the ray to the interior of the plane.
    @param [out] OUT0 Pointer to a clip list object, where the resulting points are stored.
    @param [in] ARG1 Pointer to a plane object.
    @param [in] ARG2 Pointer to a ray object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_PN_Clip_RY)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, VEC_OBJ_T(TgPLANE,CPC) ARG1, VEC_OBJ_T(TgRAY,CPC) ARG2 );

/** @brief Output the sequence of points created by clipping the ray to the interior of the plane.
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point from clipping the ray.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the 2nd point from clipping the ray.
    @param [in] ARG2 Pointer to a plane object.
    @param [in] ARG3 Pointer to a ray object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_PN_Clip_PM_RY)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgPLANE,CPC) ARG2, VEC_OBJ_T(TgRAY,CPC) ARG3 );

/** @brief Output the sequence of points created by clipping the ray to the interior of the plane.
    @param [out] OUT0 Pointer to a clip list object, where the resulting points are stored.
    @param [in] ARG1 Pointer to a plane object.
    @param [in] ARG2 Vector holding the Ray Origin.
    @param [in] ARG3 Vector holding the Ray Direction.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_PN_Clip_LR10)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, VEC_OBJ_T(TgPLANE,CPC) ARG1, VEC_T(1,C) ARG2, VEC_T(1,C) ARG3 );

/** @brief Output the sequence of points created by clipping the ray to the interior of the plane.
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point from clipping the ray.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the 2nd point from clipping the ray.
    @param [in] ARG2 Pointer to a plane object.
    @param [in] ARG3 Vector holding the Ray Origin.
    @param [in] ARG4 Vector holding the Ray Direction.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_PN_Clip_PM_LR10)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgPLANE,CPC) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4 );


/* Plane - Segment                                                                                                                                                                 */

/** @brief Calculate the minimal distance squared between a plane and a segment.
    @param [in] ARG0 Pointer to a plane object.
    @param [in] ARG1 Pointer to a segment object.
    @return Minimal distance squared between a plane and a segment when it is above the plane, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_PN_DistSq_SG)(
    VEC_OBJ_T(TgPLANE,CPC) ARG0, VEC_OBJ_T(TgSEGMENT,CPC) ARG1 );

/** @brief Calculate the minimal distance between a plane and a segment.
    @param [in] ARG0 Pointer to a plane object.
    @param [in] ARG1 Pointer to a segment object.
    @return Minimal distance between a plane and a segment when it is above the plane, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_PN_Dist_SG)(
    VEC_OBJ_T(TgPLANE,CPC) ARG0, VEC_OBJ_T(TgSEGMENT,CPC) ARG1 );

/** @brief Calculate the minimal distance squared between a plane and a segment, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a plane object.
    @param [in] ARG3 Pointer to a segment object.
    @return Minimal distance squared between the plane and segment when it is above the plane, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_PN_ClosestSq_SG)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgPLANE,CPC) ARG2, VEC_OBJ_T(TgSEGMENT,CPC) ARG3 );

/** @brief Calculate the minimal distance between a plane and a segment, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a plane object.
    @param [in] ARG3 Pointer to a segment object.
    @return Minimal distance between the plane and segment when the segment is above the plane, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_PN_Closest_SG)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgPLANE,CPC) ARG2, VEC_OBJ_T(TgSEGMENT,CPC) ARG3 );

/** @brief Calculate the minimal distance squared between a plane and a segment, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a plane object.
    @param [in] ARG3 Pointer to a segment object.
    @return Minimal distance squared between the plane and segment when it is above the plane, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_PN_ClosestSq_PM_SG)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgPLANE,CPC) ARG2, VEC_OBJ_T(TgSEGMENT,CPC) ARG3 );

/** @brief Calculate the minimal distance between a plane and a segment, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a plane object.
    @param [in] ARG3 Pointer to a segment object.
    @return Minimal distance between the plane and segment when it is above the plane, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_PN_Closest_PM_SG)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgPLANE,CPC) ARG2, VEC_OBJ_T(TgSEGMENT,CPC) ARG3 );


/** @brief Determine if the segment is completely above the plane.
    @param [in] ARG0 Pointer to a plane object.
    @param [in] ARG1 Pointer to a segment object.
    @return True if the segment is completely above the plane, and false otherwise. */
TgINLINE TgBOOL
FCN_VO(tgCO_PN_Test_SG)(
    VEC_OBJ_T(TgPLANE,CPC) ARG0, VEC_OBJ_T(TgSEGMENT,CPC) ARG1 );


/** @brief Update the collision packet with point(s) of intersection between a plane and a segment.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new intersection points.
    @param [in] ARG1 Pointer to a plane object.
    @param [in] ARG2 Pointer to a segment object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_PN_Intersect_SG)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgPLANE,CPC) ARG1, VEC_OBJ_T(TgSEGMENT,CPC) ARG2 );

/** @brief Update the collision packet with point(s) of intersection between a plane and a segment.
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point from clipping the segment.
    @param [in] ARG1 Pointer to a plane object.
    @param [in] ARG2 Pointer to a segment object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_PN_Intersect_PM_SG)(
    VEC_T(1,PC) OUT0, VEC_OBJ_T(TgPLANE,CPC) ARG1, VEC_OBJ_T(TgSEGMENT,CPC) ARG2 );


/** @brief Output the sequence of points created by clipping the segment to the interior of the plane.
    @param [out] OUT0 Pointer to a clip list object, where the resulting points are stored.
    @param [in] ARG1 Pointer to a plane object.
    @param [in] ARG2 Pointer to a segment object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_PN_Clip_SG)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, VEC_OBJ_T(TgPLANE,CPC) ARG1, VEC_OBJ_T(TgSEGMENT,CPC) ARG2 );

/** @brief Output the sequence of points created by clipping the segment to the interior of the plane.
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point from clipping the segment.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the 2nd point from clipping the segment.
    @param [in] ARG2 Pointer to a plane object.
    @param [in] ARG3 Pointer to a segment object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_PN_Clip_PM_SG)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgPLANE,CPC) ARG2, VEC_OBJ_T(TgSEGMENT,CPC) ARG3 );

/** @brief Output the sequence of points created by clipping the segment to the interior of the plane.
    @param [out] OUT0 Pointer to a clip list object, where the resulting points are stored.
    @param [in] ARG1 Pointer to a plane object.
    @param [in] ARG2 Vector holding the Segment Origin.
    @param [in] ARG3 Vector holding the position relative to the Segment Origin of the Segment Terminal Point.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_PN_Clip_LR11)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, VEC_OBJ_T(TgPLANE,CPC) ARG1, VEC_T(1,C) ARG2, VEC_T(1,C) ARG3 );

/** @brief Output the sequence of points created by clipping the segment to the interior of the plane.
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point from clipping the segment.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the 2nd point from clipping the segment.
    @param [in] ARG2 Pointer to a plane object.
    @param [in] ARG3 Vector holding the Segment Origin.
    @param [in] ARG4 Vector holding the position relative to the Segment Origin of the Segment Terminal Point.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_PN_Clip_PM_LR11)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgPLANE,CPC) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4 );


/* Plane - Utility                                                                                                                                                                 */

/** @brief Output the sequence of points created by clipping the segment to the interior of the plane.
    @param [out] OUT0 Pointer to a vector holding the updated (clipped) point from ARG3.
    @param [out] OUT1 Pointer to a vector holding the updated (clipped) point from ARG4.
    @param [in] ARG2 Pointer to a plane object.
    @param [in] ARG3 Vector holding a position (point) representing the 1st (starting) point of a line segment.
    @param [in] ARG4 Vector holding a position (point) representing the 2nd (terminal) point of a line segment.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_PN_Clip_Points)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgPLANE,CPC) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4 );

/** @brief Clip a line strip to the interior of a plane (half-space).
    @param [in,out] OUT0 Pointer to a clip list object (an array of vectors interpreted as a line strip).
    @param [in] ARG1 Pointer to a plane object.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_PN_Clip)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, VEC_OBJ_T(TgPLANE,CPC) ARG1 );


/** @} TGS_COLLISION_PN */

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

    #define TGS_COLLISION_PLANE_H

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COLLISION_PLANE_H) */
#endif
