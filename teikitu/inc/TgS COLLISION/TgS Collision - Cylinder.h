/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Cylinder.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_CYLINDER_H)
#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* == Collision ================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions - Scalar Functions                                                                                                                                            */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @addtogroup TGS_COLLISION_CY */
/** @{ */

/* Cylinder - Line                                                                                                                                                                 */

/** @brief Calculate the minimal distance squared between a cylinder and a line, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to tube object, interpreted as a cylinder.
    @param [in] ARG3 Pointer to a line object.
    @return Minimal distance squared between the cylinder and line, or zero otherwise, broadcast across all vector lanes. */
TgINLINE TgRESULT
FCN_VO(tgCO_CY_Closest_PM_LN)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgTUBE,CPC) ARG2, VEC_OBJ_T(TgLINE,CPC) ARG3 );

/** @brief Calculate the minimal distance squared between a cylinder and a line, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to {ARG3,ARG4} on ARG2.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG2 on {ARG3,ARG4}.
    @param [in] ARG2 Pointer to tube object, interpreted as a cylinder.
    @param [in] ARG3 Vector holding the Line Origin.
    @param [in] ARG4 Vector holding the Line Direction.
    @return Minimal distance squared between the cylinder and line, or zero otherwise, broadcast across all vector lanes. */
TgINLINE TgRESULT
FCN_VO(tgCO_CY_Closest_PM_LR00)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgTUBE,CPC) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4 );


/** @brief Update the collision packet with point(s) of intersection between a cylinder and a line.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
    @param [in] ARG1 Pointer to tube object, interpreted as a cylinder.
    @param [in] ARG2 Pointer to a line object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_CY_Intersect_LN)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgTUBE,CPC) ARG1, VEC_OBJ_T(TgLINE,CPC) ARG2 );

/** @brief Update the collision packet with point(s) of intersection between a cylinder and a line.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
    @param [in] ARG1 Pointer to tube object, interpreted as a cylinder.
    @param [in] ARG2 Vector holding the Line Origin.
    @param [in] ARG3 Vector holding the Line Direction.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_CY_Intersect_LR00)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgTUBE,CPC) ARG1, VEC_T(1,C) ARG2, VEC_T(1,C) ARG3 );


/** @brief Output the sequence of points created by clipping the line to the interior of the cylinder.
    @param [out] OUT0 Pointer to a clip list object, where the resulting points are stored.
    @param [in] ARG1 Pointer to tube object, interpreted as a cylinder.
    @param [in] ARG2 Pointer to a line object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_CY_Clip_LN)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, VEC_OBJ_T(TgTUBE,CPC) ARG1, VEC_OBJ_T(TgLINE,CPC) ARG2 );

/** @brief Output the sequence of points created by clipping the line to the interior of the cylinder.
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point from clipping the line.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the 2nd point from clipping the line.
    @param [in] ARG2 Pointer to tube object, interpreted as a cylinder.
    @param [in] ARG3 Pointer to a line object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_CY_Clip_PM_LN)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgTUBE,CPC) ARG2, VEC_OBJ_T(TgLINE,CPC) ARG3 );

/** @brief Output the sequence of points created by clipping the line to the interior of the cylinder.
    @param [out] OUT0 Pointer to a clip list object, where the resulting points are stored.
    @param [in] ARG1 Pointer to tube object, interpreted as a cylinder.
    @param [in] ARG2 Vector holding the Line Origin.
    @param [in] ARG3 Vector holding the Line Direction.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_CY_Clip_LR00)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, VEC_OBJ_T(TgTUBE,CPC) ARG1, VEC_T(1,C) ARG2, VEC_T(1,C) ARG3 );

/** @brief Output the sequence of points created by clipping the line to the interior of the cylinder.
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point from clipping the line.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the 2nd point from clipping the line.
    @param [in] ARG2 Pointer to tube object, interpreted as a cylinder.
    @param [in] ARG3 Vector holding the Line Origin.
    @param [in] ARG4 Vector holding the Line Direction.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_CY_Clip_PM_LR00)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgTUBE,CPC) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4 );


/** @brief Generate the contact points generated from the intersection of the line and cylinder.
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point from clipping the line.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the 2nd point from clipping the line.
    @param [out] OUT2 Pointer to a vector holding the contact normal for the point in OUT0.
    @param [out] OUT3 Pointer to a vector holding the contact normal for the point in OUT1.
    @param [in] ARG4 Pointer to tube object, interpreted as a cylinder.
    @param [in] ARG5 Vector holding the Line Origin.
    @param [in] ARG6 Vector holding the Line Direction.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_CY_Internal_PM_LR00)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_T(1,PC) OUT3, VEC_OBJ_T(TgTUBE,CPC) ARG4, VEC_T(1,C) ARG5, VEC_T(1,C) ARG6 );


/* Cylinder - Ray                                                                                                                                                                  */

/** @brief Calculate the minimal distance squared between a cylinder and a ray, and store the closest points on each primitive.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to tube object, interpreted as a cylinder.
    @param [in] ARG3 Pointer to a ray object.
    @return Minimal distance squared between the cylinder and ray, or zero otherwise, broadcast across all vector lanes. */
TgINLINE TgRESULT
FCN_VO(tgCO_CY_Closest_PM_RY)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgTUBE,CPC) ARG2, VEC_OBJ_T(TgRAY,CPC) ARG3 );

/** @brief Calculate the minimal distance squared between a cylinder and a ray, and store the closest points on each primitive.
    @param [out] OUT0 Pointer to a vector holding the closest point to {ARG3,ARG4} on ARG2.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG2 on {ARG3,ARG4}.
    @param [in] ARG2 Pointer to tube object, interpreted as a cylinder.
    @param [in] ARG3 Vector holding the Ray Origin.
    @param [in] ARG4 Vector holding the Ray Direction.
    @return Minimal distance squared between the cylinder and ray, or zero otherwise, broadcast across all vector lanes. */
TgINLINE TgRESULT
FCN_VO(tgCO_CY_Closest_PM_LR10)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgTUBE,CPC) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4 );


/** @brief Update the collision packet with point(s) of intersection between a cylinder and a ray.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
    @param [in] ARG1 Pointer to tube object, interpreted as a cylinder.
    @param [in] ARG2 Pointer to a ray object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_CY_Intersect_RY)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgTUBE,CPC) ARG1, VEC_OBJ_T(TgRAY,CPC) ARG2 );

/** @brief Update the collision packet with point(s) of intersection between a cylinder and a ray.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
    @param [in] ARG1 Pointer to tube object, interpreted as a cylinder.
    @param [in] ARG2 Vector holding the Ray Origin.
    @param [in] ARG3 Vector holding the Ray Direction.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_CY_Intersect_LR10)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgTUBE,CPC) ARG1, VEC_T(1,C) ARG2, VEC_T(1,C) ARG3 );


/** @brief Output the sequence of points created by clipping the ray to the interior of the cylinder.
    @param [out] OUT0 Pointer to a clip list object, where the resulting points are stored.
    @param [in] ARG1 Pointer to tube object, interpreted as a cylinder.
    @param [in] ARG2 Pointer to a ray object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_CY_Clip_RY)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, VEC_OBJ_T(TgTUBE,CPC) ARG1, VEC_OBJ_T(TgRAY,CPC) ARG2 );

/** @brief Output the sequence of points created by clipping the ray to the interior of the cylinder.
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point from clipping the ray.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the 2nd point from clipping the ray.
    @param [in] ARG2 Pointer to tube object, interpreted as a cylinder.
    @param [in] ARG3 Pointer to a ray object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_CY_Clip_PM_RY)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgTUBE,CPC) ARG2, VEC_OBJ_T(TgRAY,CPC) ARG3 );

/** @brief Output the sequence of points created by clipping the ray to the interior of the cylinder.
    @param [out] OUT0 Pointer to a clip list object, where the resulting points are stored.
    @param [in] ARG1 Pointer to tube object, interpreted as a cylinder.
    @param [in] ARG2 Vector holding the Ray Origin.
    @param [in] ARG3 Vector holding the Ray Direction.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_CY_Clip_LR10)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, VEC_OBJ_T(TgTUBE,CPC) ARG1, VEC_T(1,C) ARG2, VEC_T(1,C) ARG3 );

/** @brief Output the sequence of points created by clipping the ray to the interior of the cylinder.
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point from clipping the ray.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the 2nd point from clipping the ray.
    @param [in] ARG2 Pointer to tube object, interpreted as a cylinder.
    @param [in] ARG3 Vector holding the Ray Origin.
    @param [in] ARG4 Vector holding the Ray Direction.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_CY_Clip_PM_LR10)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgTUBE,CPC) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4 );


/** @brief Generate the contact points generated from the intersection of the ray and cylinder.
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point from clipping the ray.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the 2nd point from clipping the ray.
    @param [out] OUT2 Pointer to a vector holding the contact normal for the point in OUT0.
    @param [out] OUT3 Pointer to a vector holding the contact normal for the point in OUT1.
    @param [in] ARG4 Pointer to tube object, interpreted as a cylinder.
    @param [in] ARG5 Vector holding the Ray Origin.
    @param [in] ARG6 Vector holding the Ray Direction.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_CY_Internal_PM_LR10)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_T(1,PC) OUT3, VEC_OBJ_T(TgTUBE,CPC) ARG4, VEC_T(1,C) ARG5, VEC_T(1,C) ARG6 );


/* Cylinder - Segment                                                                                                                                                              */

/** @brief Calculate the minimal distance squared between a cylinder and a segment, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to tube object, interpreted as a cylinder.
    @param [in] ARG3 Pointer to a segment object.
    @return Minimal distance squared between the cylinder and segment, or zero otherwise, broadcast across all vector lanes. */
TgINLINE TgRESULT
FCN_VO(tgCO_CY_Closest_PM_SG)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgTUBE,CPC) ARG2, VEC_OBJ_T(TgSEGMENT,CPC) ARG3 );

/** @brief Calculate the minimal distance squared between a cylinder and a segment, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to {ARG3,ARG4} on ARG2.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG2 on {ARG3,ARG4}.
    @param [in] ARG2 Pointer to tube object, interpreted as a cylinder.
    @param [in] ARG3 Vector holding the Segment Origin.
    @param [in] ARG4 Vector holding the position relative to the Segment Origin of the Segment Terminal Point.
    @return Minimal distance squared between the cylinder and segment, or zero otherwise, broadcast across all vector lanes. */
TgINLINE TgRESULT
FCN_VO(tgCO_CY_Closest_PM_LR11)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgTUBE,CPC) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4 );


/** @brief Update the collision packet with point(s) of intersection between a cylinder and a segment.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
    @param [in] ARG1 Pointer to tube object, interpreted as a cylinder.
    @param [in] ARG2 Pointer to a segment object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_CY_Intersect_SG)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgTUBE,CPC) ARG1, VEC_OBJ_T(TgSEGMENT,CPC) ARG2 );

/** @brief Update the collision packet with point(s) of intersection between a cylinder and a segment.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
    @param [in] ARG1 Pointer to tube object, interpreted as a cylinder.
    @param [in] ARG2 Vector holding the Segment Origin.
    @param [in] ARG3 Vector holding the position relative to the Segment Origin of the Segment Terminal Point.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_CY_Intersect_LR11)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgTUBE,CPC) ARG1, VEC_T(1,C) ARG2, VEC_T(1,C) ARG3 );


/** @brief Output the sequence of points created by clipping the segment to the interior of the cylinder.
    @param [out] OUT0 Pointer to a clip list object, where the resulting points are stored.
    @param [in] ARG1 Pointer to tube object, interpreted as a cylinder.
    @param [in] ARG2 Pointer to a segment object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_CY_Clip_SG)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, VEC_OBJ_T(TgTUBE,CPC) ARG1, VEC_OBJ_T(TgSEGMENT,CPC) ARG2 );

/** @brief Output the sequence of points created by clipping the segment to the interior of the cylinder.
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point from clipping the segment.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the 2nd point from clipping the segment.
    @param [in] ARG2 Pointer to tube object, interpreted as a cylinder.
    @param [in] ARG3 Pointer to a segment object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_CY_Clip_PM_SG)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgTUBE,CPC) ARG2, VEC_OBJ_T(TgSEGMENT,CPC) ARG3 );

/** @brief Output the sequence of points created by clipping the segment to the interior of the cylinder.
    @param [out] OUT0 Pointer to a clip list object, where the resulting points are stored.
    @param [in] ARG1 Pointer to tube object, interpreted as a cylinder.
    @param [in] ARG2 Vector holding the Segment Origin.
    @param [in] ARG3 Vector holding the position relative to the Segment Origin of the Segment Terminal Point.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_CY_Clip_LR11)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, VEC_OBJ_T(TgTUBE,CPC) ARG1, VEC_T(1,C) ARG2, VEC_T(1,C) ARG3 );

/** @brief Output the sequence of points created by clipping the segment to the interior of the cylinder.
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point from clipping the segment.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the 2nd point from clipping the segment.
    @param [in] ARG2 Pointer to tube object, interpreted as a cylinder.
    @param [in] ARG3 Vector holding the Segment Origin.
    @param [in] ARG4 Vector holding the position relative to the Segment Origin of the Segment Terminal Point.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_CY_Clip_PM_LRSG)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgTUBE,CPC) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4 );


/** @brief Generate the contact points generated from the intersection of the segment and cylinder.
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point from clipping the segment.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the 2nd point from clipping the segment.
    @param [out] OUT2 Pointer to a vector holding the contact normal for the point in OUT0.
    @param [out] OUT3 Pointer to a vector holding the contact normal for the point in OUT1.
    @param [in] ARG4 Pointer to tube object, interpreted as a cylinder.
    @param [in] ARG5 Vector holding the Segment Origin.
    @param [in] ARG6 Vector holding the position relative to the Segment Origin of the Segment Terminal Point.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_CY_Internal_PM_LR11)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_T(1,PC) OUT3, VEC_OBJ_T(TgTUBE,CPC) ARG4, VEC_T(1,C) ARG5, VEC_T(1,C) ARG6 );


/* Cylinder - Plane                                                                                                                                                                */

/** @brief Calculate the minimal distance squared between a cylinder and a plane.
    @param [in] ARG0 Pointer to tube object, interpreted as a cylinder.
    @param [in] ARG1 Pointer to a plane object.
    @return Minimal distance squared between a cylinder and a plane when the cylinder is above the plane, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CY_DistSq_PN)(
    VEC_OBJ_T(TgTUBE,CPC) ARG0, VEC_OBJ_T(TgPLANE,CPC) ARG1 );

/** @brief Calculate the minimal distance between a cylinder and a plane.
    @param [in] ARG0 Pointer to tube object, interpreted as a cylinder.
    @param [in] ARG1 Pointer to a plane object.
    @return Minimal distance between a cylinder and a plane when the cylinder is above the plane, or zero otherwise, broadcast across all vector lanes.

TODO Minimal distance between the two primitives or negative type max if they intersect or are invalid.
      For distance functions, planes are not considered to be cutting (ie dividing into two half-spaces).  Thus, cylinders on the negative side of the plane are not 
      ignored/culled. The distance value returned */
TgEXTN VEC_T(1)
FCN_VO(tgCO_CY_Dist_PN)(
    VEC_OBJ_T(TgTUBE,CPC) ARG0, VEC_OBJ_T(TgPLANE,CPC) ARG1 );

/** @brief Calculate the minimal distance squared between a cylinder and a plane, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to tube object, interpreted as a cylinder.
    @param [in] ARG3 Pointer to a plane object.
    @return Minimal distance squared between the cylinder and plane when the cylinder is above the plane, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CY_ClosestSq_PN)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgTUBE,CPC) ARG2, VEC_OBJ_T(TgPLANE,CPC) ARG3 );

/** @brief Calculate the minimal distance between a cylinder and a plane, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to tube object, interpreted as a cylinder.
    @param [in] ARG3 Pointer to a plane object.
    @return Minimal distance between the cylinder and plane when the cylinder is above the plane, or zero otherwise, broadcast across all vector lanes. */
TgEXTN VEC_T(1)
FCN_VO(tgCO_CY_Closest_PN)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgTUBE,CPC) ARG2, VEC_OBJ_T(TgPLANE,CPC) ARG3 );

/** @brief Update the collision packet with point(s) of penetration between a cylinder and a plane.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG2.
                         Contact normals are the direction for the object at ARG2 to move to achieve separation.
                         Depth values are measured from the surface of the object at ARG1 to the contact point.
    @param [in] ARG1 Pointer to a plane object.
    @param [in] ARG2 Pointer to tube object, interpreted as a cylinder.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_PN_Penetrate_CY)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgPLANE,CPC) ARG1, VEC_OBJ_T(TgTUBE,CPC) ARG2 );


/* Cylinder - Box                                                                                                                                                                  */

/** @brief Update the collision packet with point(s) of penetration between a cylinder and a box.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG2.
                         Contact normals are the direction for the object at ARG2 to move to achieve separation.
                         Depth values are measured from the surface of the object at ARG1 to the contact point.
    @param [in] ARG1 Pointer to a box object.
    @param [in] ARG2 Pointer to tube object, interpreted as a cylinder.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_BX_Penetrate_CY)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgBOX,CPC) ARG1, VEC_OBJ_T(TgTUBE,CPC) ARG2 );


/* Cylinder - Capsule                                                                                                                                                              */

/** @brief Update the collision packet with point(s) of penetration between a cylinder and a capsule.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG2.
                         Contact normals are the direction for the object at ARG2 to move to achieve separation.
                         Depth values are measured from the surface of the object at ARG1 to the contact point.
    @param [in] ARG1 Pointer to a capsule object.
    @param [in] ARG2 Pointer to tube object, interpreted as a cylinder.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_CP_Penetrate_CY)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgTUBE,CPC) ARG1, VEC_OBJ_T(TgTUBE,CPC) ARG2 );


/* Cylinder - Cylinder                                                                                                                                                             */

/** @brief Update the collision packet with point(s) of penetration between a cylinder and a cylinder.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG2.
                         Contact normals are the direction for the object at ARG2 to move to achieve separation.
                         Depth values are measured from the surface of the object at ARG1 to the contact point.
    @param [in] ARG1 Pointer to a cylinder object.
    @param [in] ARG2 Pointer to tube object, interpreted as a cylinder.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_CY_Penetrate_CY)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgTUBE,CPC) ARG1, VEC_OBJ_T(TgTUBE,CPC) ARG2 );


/* Cylinder - Sphere                                                                                                                                                               */

/** @brief Update the collision packet with point(s) of penetration between a cylinder and a sphere.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG2.
                         Contact normals are the direction for the object at ARG2 to move to achieve separation.
                         Depth values are measured from the surface of the object at ARG1 to the contact point.
    @param [in] ARG1 Pointer to a sphere object.
    @param [in] ARG2 Pointer to tube object, interpreted as a cylinder.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_SP_Penetrate_CY)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgSPHERE,CPC) ARG1, VEC_OBJ_T(TgTUBE,CPC) ARG2 );


/* Cylinder - Triangle                                                                                                                                                             */

/** @brief Update the collision packet with point(s) of penetration between a cylinder and a triangle.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG2.
                         Contact normals are the direction for the object at ARG2 to move to achieve separation.
                         Depth values are measured from the surface of the object at ARG1 to the contact point.
    @param [in] ARG1 Pointer to a triangle (space) object.
    @param [in] ARG2 Pointer to tube object, interpreted as a cylinder.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_ST_Penetrate_CY)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgSTRI,CPC) ARG1, VEC_OBJ_T(TgTUBE,CPC) ARG2 );

/* Cylinder - Utility                                                                                                                                                              */

/** @brief Clip a line segment to the interior of a capsule.
    @param [out] OUT0 Pointer to a vector holding the updated (clipped) point from ARG3.
    @param [out] OUT1 Pointer to a vector holding the updated (clipped) point from ARG4.
    @param [in] ARG2 Pointer to a tube object, interpreted as a cylinder.
    @param [in] ARG3 Vector holding a position (point) representing the 1st (starting) point of a line segment.
    @param [in] ARG4 Vector holding a position (point) representing the 2nd (terminal) point of a line segment.
   @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_CY_Clip_Points)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgTUBE,CPC) ARG1, VEC_T(1,C) ARG2, VEC_T(1,C) ARG3 );

/** @brief Clip a line strip to the interior of a capsule.
    @param [in,out] OUT0 Pointer to a clip list object (an array of vectors interpreted as a line strip).
    @param [in] ARG1 Pointer to tube object, interpreted as a cylinder.
   @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_CY_Clip)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, VEC_OBJ_T(TgTUBE,CPC) ARG1 );


/** @} TGS_COLLISION_CY */

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

    #define TGS_COLLISION_CYLINDER_H

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COLLISION_CYLINDER_H) */
#endif
