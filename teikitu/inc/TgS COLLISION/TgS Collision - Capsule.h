/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Capsule.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_CAPSULE_H)
#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* == Collision ================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @addtogroup TGS_COLLISION_CP */
/** @{ */

/* Capsule - Point                                                                                                                                                                 */

/** @brief Calculate the minimal distance squared between a capsule and a point.
    @param [in] ARG0 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG1 Vector holding a position (point).
    @return Minimal distance squared between a capsule and a point, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CP_DistSq_PT)(
    VEC_OBJ_T(TgTUBE,CPC) ARG0, VEC_T(1,C) ARG1 );

/** @brief Calculate the minimal distance between a capsule and a point.
    @param [in] ARG0 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG1 Vector holding a position (point).
    @return Minimal distance between a capsule and a point, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CP_Dist_PT)(
    VEC_OBJ_T(TgTUBE,CPC) ARG0, VEC_T(1,C) ARG1 );

/** @brief Calculate the minimal distance squared between a capsule and a point, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG2 on ARG1.
    @param [in] ARG1 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG2 Vector holding a position (point).
    @return Minimal distance squared between a capsule and a point, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CP_ClosestSq_PT)(
    VEC_T(1,PC), VEC_OBJ_T(TgTUBE,CPC) ARG1, VEC_T(1,C) ARG2 );

/** @brief Calculate the minimal distance between a capsule and a point, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG2 on ARG1.
    @param [in] ARG1 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG2 Vector holding a position (point).
    @return Minimal distance between a capsule and a point, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CP_Closest_PT)(
    VEC_T(1,PC), VEC_OBJ_T(TgTUBE,CPC) ARG1, VEC_T(1,C) ARG2 );


/** @brief Determine if the two primitives are intersecting.
    @param [in] ARG0 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG1 Vector holding a position (point).
    @return True if the two primitives are intersecting, and false otherwise. */
TgINLINE TgBOOL
FCN_VO(tgCO_CP_Test_PT)(
    VEC_OBJ_T(TgTUBE,CPC) ARG0, VEC_T(1,C) ARG1 );


/** @brief Update the collision packet with point(s) of penetration between a capsule and a point.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG2.
                         Contact normals are the direction for the object at ARG2 to move to achieve separation.
                         Depth values are measured from the surface of the object at ARG1 to the contact point.
    @param [in] ARG1 Vector holding a position (point).
    @param [in] ARG2 Pointer to tube object, interpreted as a capsule.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_PT_Penetrate_CP)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_T(1,C) ARG1, VEC_OBJ_T(TgTUBE,CPC) ARG2 );


/** @brief Calculate the minimal distance between a capsule and a point, and store the location on the capsule closest to the point.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG2 on the capsule.
    @param [in] ARG1 Vector holding a full broadcast of the minimal distance between the capsule and the point.
    @param [in] ARG2 Vector holding a full broadcast of the capsule radius.
    @param [in] ARG3 Vector holding the closest point to ARG4 on the capsule axis (line segment).
    @param [in] ARG4 Vector holding a position (point).
    @return Minimal distance between a capsule and a point, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CP_Internal_Dist_SG_PT)(
    VEC_T(1,PC) OUT0, VEC_T(1,C) ARG1, VEC_T(1,C) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4 );


/* Capsule - Line                                                                                                                                                                  */

/** @brief Calculate the minimal distance squared between a capsule and a line.
    @param [in] ARG0 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG1 Pointer to a line object.
    @return Minimal distance squared between a capsule and a line, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CP_DistSq_LN)(
    VEC_OBJ_T(TgTUBE,CPC) ARG0, VEC_OBJ_T(TgLINE,CPC) ARG1 );

/** @brief Calculate the minimal distance between a capsule and a line.
    @param [in] ARG0 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG1 Pointer to a line object.
    @return Minimal distance between a capsule and a line, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CP_Dist_LN)(
    VEC_OBJ_T(TgTUBE,CPC) ARG0, VEC_OBJ_T(TgLINE,CPC) ARG1 );

/** @brief Calculate the minimal distance squared between a capsule and a line, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG3 Pointer to a line object.
    @return Minimal distance squared between the capsule and line, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CP_ClosestSq_LN)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgTUBE,CPC) ARG2, VEC_OBJ_T(TgLINE,CPC) ARG3 );

/** @brief Calculate the minimal distance between a capsule and a line, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG3 Pointer to a line object.
    @return Minimal distance between the capsule and line, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CP_Closest_LN)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgTUBE,CPC) ARG2, VEC_OBJ_T(TgLINE,CPC) ARG3 );


/** @brief Calculate the minimal distance squared between a capsule and a line, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG3 Pointer to a line object.
    @return Minimal distance squared between the capsule and line, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CP_ClosestSq_PM_LN)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgTUBE,CPC) ARG2, VEC_OBJ_T(TgLINE,CPC) ARG3 );

/** @brief Calculate the minimal distance between a capsule and a line, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG3 Pointer to a line object.
    @return Minimal distance between the capsule and line, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CP_Closest_PM_LN)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OTU1, VEC_OBJ_T(TgTUBE,CPC) ARG2, VEC_OBJ_T(TgLINE,CPC) ARG3 );


/** @brief Determine if the two primitives are intersecting.
    @param [in] ARG0 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG1 Pointer to a line object.
    @return True if the two primitives are intersecting, and false otherwise. */
TgINLINE TgBOOL
FCN_VO(tgCO_CP_Test_LN)(
    VEC_OBJ_T(TgTUBE,CPC) ARG1, VEC_OBJ_T(TgLINE,CPC) ARG2 );


/** @brief Update the collision packet with point(s) of intersection between a capsule and a line.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
    @param [in] ARG1 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG2 Pointer to a line object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_CP_Intersect_LN)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgTUBE,CPC) ARG1, VEC_OBJ_T(TgLINE,CPC) ARG2 );

/** @brief Update the collision packet with point(s) of intersection between a capsule and a line.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
    @param [in] ARG1 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG2 Vector holding the Line Origin.
    @param [in] ARG3 Vector holding the Line Direction.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_CP_Intersect_LR00)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgTUBE,CPC) ARG1, VEC_T(1,C) ARG2, VEC_T(1,C) ARG3 );


/** @brief Update the collision packet with point(s) of penetration between a capsule and a line.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG2.
                         Contact normals are the direction for the object at ARG2 to move to achieve separation.
                         Depth values are measured from the surface of the object at ARG1 to the contact point.
    @param [in] ARG1 Pointer to a triangle (space) object.
    @param [in] ARG2 Pointer to tube object, interpreted as a capsule.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_LN_Penetrate_CP)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgLINE,CPC) ARG1, VEC_OBJ_T(TgTUBE,CPC) ARG2 );

/** @brief Update the collision packet with point(s) of penetration between a capsule and a line.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG2.
                         Contact normals are the direction for the object at ARG2 to move to achieve separation.
                         Depth values are measured from the surface of the object at ARG1 to the contact point.
    @param [in] ARG1 Vector holding the point of closest proximity on the line to the capsule axis.
    @param [in] ARG2 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG3 Vector holding the point of closest proximity on the capsule axis to the line.
    @param [in] ARG4 Vector holding a full broadcast of the minimal distance squared between the capsule axis and the line.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_CP_Penetrate_LR00)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_T(1,C) ARG1, VEC_OBJ_T(TgTUBE,CPC) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4 );


/** @brief Output the sequence of points created by clipping the line to the interior of the capsule.
    @param [out] OUT0 Pointer to a clip list object, where the resulting points are stored.
    @param [in] ARG1 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG2 Pointer to a line object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_CP_Clip_LN)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, VEC_OBJ_T(TgTUBE,CPC) ARG1, VEC_OBJ_T(TgLINE,CPC) ARG2 );

/** @brief Output the sequence of points created by clipping the line to the interior of the capsule.
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point from clipping the line.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the 2nd point from clipping the line.
    @param [in] ARG2 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG3 Pointer to a line object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_CP_Clip_PM_LN)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgTUBE,CPC) ARG2, VEC_OBJ_T(TgLINE,CPC) ARG3 );

/** @brief Output the sequence of points created by clipping the line to the interior of the capsule.
    @param [out] OUT0 Pointer to a clip list object, where the resulting points are stored.
    @param [in] ARG1 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG2 Vector holding the Line Origin.
    @param [in] ARG3 Vector holding the Line Direction.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_CP_Clip_LR00)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, VEC_OBJ_T(TgTUBE,CPC) ARG1, VEC_T(1,C) ARG2, VEC_T(1,C) ARG3 );

/** @brief Output the sequence of points created by clipping the line to the interior of the capsule.
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point from clipping the line.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the 2nd point from clipping the line.
    @param [in] ARG2 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG3 Vector holding the Line Origin.
    @param [in] ARG4 Vector holding the Line Direction.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_CP_Clip_PM_LR00)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgTUBE,CPC) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4 );


/** @brief Determine the points of contact between the capsule and line. Internal function that does not clip to the linear limits.
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point of contact.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the 2nd point of contact.
    @param [out] OUT2 Pointer to a vector holding the contact normal for the point in OUT0.
    @param [out] OUT3 Pointer to a vector holding the contact normal for the point in OUT1.
    @param [in] ARG4 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG5 Vector holding the Line Origin.
    @param [in] ARG6 Vector holding the Line Direction.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_CP_Contact_LR00)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_T(1,PC) OUT3, VEC_OBJ_T(TgTUBE,CPC) ARG4, VEC_T(1,C) ARG5, VEC_T(1,C) ARG6 );


/* Capsule - Ray                                                                                                                                                                   */

/** @brief Calculate the minimal distance squared between a capsule and a ray.
    @param [in] ARG0 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG1 Pointer to a ray object.
    @return Minimal distance squared between a capsule and a ray, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CP_DistSq_RY)(
    VEC_OBJ_T(TgTUBE,CPC) ARG0, VEC_OBJ_T(TgRAY,CPC) ARG1 );

/** @brief Calculate the minimal distance between a capsule and a ray.
    @param [in] ARG0 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG1 Pointer to a ray object.
    @return Minimal distance between a capsule and a ray, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CP_Dist_RY)(
    VEC_OBJ_T(TgTUBE,CPC) ARG0, VEC_OBJ_T(TgRAY,CPC) ARG1 );

/** @brief Calculate the minimal distance squared between a capsule and a ray, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG3 Pointer to a ray object.
    @return Minimal distance squared between the capsule and ray, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CP_ClosestSq_RY)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgTUBE,CPC) ARG2, VEC_OBJ_T(TgRAY,CPC) ARG3 );

/** @brief Calculate the minimal distance between a capsule and a ray, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG3 Pointer to a ray object.
    @return Minimal distance between the capsule and ray, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CP_Closest_RY)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgTUBE,CPC) ARG2, VEC_OBJ_T(TgRAY,CPC) ARG3 );


/** @brief Calculate the minimal distance squared between a capsule and a ray, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG3 Pointer to a ray object.
    @return Minimal distance squared between the capsule and ray, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CP_ClosestSq_PM_RY)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgTUBE,CPC) ARG2, VEC_OBJ_T(TgRAY,CPC) ARG3 );

/** @brief Calculate the minimal distance between a capsule and a ray, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG3 Pointer to a ray object.
    @return Minimal distance between the capsule and ray, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CP_Closest_PM_RY)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgTUBE,CPC) ARG2, VEC_OBJ_T(TgRAY,CPC) ARG3 );


/** @brief Determine if the two primitives are intersecting.
    @param [in] ARG0 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG1 Pointer to a ray object.
    @return True if the two primitives are intersecting, and false otherwise. */
TgINLINE TgBOOL
FCN_VO(tgCO_CP_Test_RY)(
    VEC_OBJ_T(TgTUBE,CPC) ARG0, VEC_OBJ_T(TgRAY,CPC) ARG1 );


/** @brief Update the collision packet with point(s) of intersection between a capsule and a ray.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
    @param [in] ARG1 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG2 Pointer to a ray object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_CP_Intersect_RY)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgTUBE,CPC) ARG1, VEC_OBJ_T(TgRAY,CPC) ARG2 );

/** @brief Update the collision packet with point(s) of intersection between a capsule and a ray.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
    @param [in] ARG1 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG2 Vector holding the Ray Origin.
    @param [in] ARG3 Vector holding the Ray Direction.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_CP_Intersect_LR10)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgTUBE,CPC) ARG1, VEC_T(1,C) ARG2, VEC_T(1,C) ARG3 );


/** @brief Update the collision packet with point(s) of penetration between a capsule and a ray.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG2.
                         Contact normals are the direction for the object at ARG2 to move to achieve separation.
                         Depth values are measured from the surface of the object at ARG1 to the contact point.
    @param [in] ARG1 Pointer to a triangle (space) object.
    @param [in] ARG2 Pointer to tube object, interpreted as a capsule.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_RY_Penetrate_CP)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgRAY,CPC) ARG1, VEC_OBJ_T(TgTUBE,CPC) ARG2 );

/** @brief Update the collision packet with point(s) of penetration between a capsule and a ray.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG2.
                         Contact normals are the direction for the object at ARG2 to move to achieve separation.
                         Depth values are measured from the surface of the object at ARG1 to the contact point.
    @param [in] ARG1 Vector holding the point of closest proximity on the ray to the capsule axis.
    @param [in] ARG2 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG3 Vector holding the point of closest proximity on the capsule axis to the ray.
    @param [in] ARG4 Vector holding a full broadcast of the minimal distance squared between the capsule axis and the ray.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_CP_Penetrate_LR10)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_T(1,C) ARG1, VEC_OBJ_T(TgTUBE,CPC) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4 );


/** @brief Output the sequence of points created by clipping the ray to the interior of the capsule.
    @param [out] OUT0 Pointer to a clip list object, where the resulting points are stored.
    @param [in] ARG1 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG2 Pointer to a ray object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_CP_Clip_RY)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, VEC_OBJ_T(TgTUBE,CPC) ARG1, VEC_OBJ_T(TgRAY,CPC) ARG2 );

/** @brief Output the sequence of points created by clipping the ray to the interior of the capsule.
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point from clipping the ray.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the 2nd point from clipping the ray.
    @param [in] ARG2 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG3 Pointer to a ray object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_CP_Clip_PM_RY)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgTUBE,CPC) ARG2, VEC_OBJ_T(TgRAY,CPC) ARG3 );

/** @brief Output the sequence of points created by clipping the ray to the interior of the capsule.
    @param [out] OUT0 Pointer to a clip list object, where the resulting points are stored.
    @param [in] ARG1 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG2 Vector holding the Ray Origin.
    @param [in] ARG3 Vector holding the Ray Direction.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_CP_Clip_LR10)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, VEC_OBJ_T(TgTUBE,CPC) ARG1, VEC_T(1,C) ARG2, VEC_T(1,C) ARG3 );

/** @brief Output the sequence of points created by clipping the ray to the interior of the capsule.
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point from clipping the ray.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the 2nd point from clipping the ray.
    @param [in] ARG2 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG3 Vector holding the Ray Origin.
    @param [in] ARG4 Vector holding the Ray Direction.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_CP_Clip_PM_LR10)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgTUBE,CPC) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4 );


/** @brief Determine the points of contact between the capsule and ray. Internal function that does not clip to the linear limits.
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point of contact.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the 2nd point of contact.
    @param [out] OUT2 Pointer to a vector holding the contact normal for the point in OUT0 (directed out of ARG4).
    @param [out] OUT3 Pointer to a vector holding the contact normal for the point in OUT1 (directed out of ARG4).
    @param [in] ARG4 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG5 Vector holding the Ray Origin.
    @param [in] ARG6 Vector holding the Ray Direction.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_CP_Contact_LR10)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_T(1,PC) OUT3, VEC_OBJ_T(TgTUBE,CPC) ARG4, VEC_T(1,C) ARG5, VEC_T(1,C) ARG6 );


/* Capsule - Segment                                                                                                                                                               */

/** @brief Calculate the minimal distance squared between a capsule and a segment.
    @param [in] ARG0 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG1 Pointer to a segment object.
    @return Minimal distance squared between a capsule and a segment, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CP_DistSq_SG)(
    VEC_OBJ_T(TgTUBE,CPC) ARG0, VEC_OBJ_T(TgSEGMENT,CPC) ARG1 );

/** @brief Calculate the minimal distance between a capsule and a segment.
    @param [in] ARG0 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG1 Pointer to a segment object.
    @return Minimal distance between a capsule and a segment, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CP_Dist_SG)(
    VEC_OBJ_T(TgTUBE,CPC) ARG0, VEC_OBJ_T(TgSEGMENT,CPC) ARG1 );

/** @brief Calculate the minimal distance squared between a capsule and a segment, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG3 Pointer to a segment object.
    @return Minimal distance squared between the capsule and segment, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CP_ClosestSq_SG)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgTUBE,CPC) ARG2, VEC_OBJ_T(TgSEGMENT,CPC) ARG3 );

/** @brief Calculate the minimal distance between a capsule and a segment, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG3 Pointer to a segment object.
    @return Minimal distance between the capsule and segment, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CP_Closest_SG)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgTUBE,CPC) ARG2, VEC_OBJ_T(TgSEGMENT,CPC) ARG3 );


/** @brief Calculate the minimal distance squared between a capsule and a segment, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG3 Pointer to a segment object.
    @return Minimal distance squared between the capsule and segment, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CP_ClosestSq_PM_SG)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgTUBE,CPC) ARG2, VEC_OBJ_T(TgSEGMENT,CPC) ARG3 );

/** @brief Calculate the minimal distance between a capsule and a segment, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG3 Pointer to a segment object.
    @return Minimal distance between the capsule and segment, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CP_Closest_PM_SG)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgTUBE,CPC) ARG2, VEC_OBJ_T(TgSEGMENT,CPC) ARG3 );


/** @brief Determine if the two primitives are intersecting.
    @param [in] ARG0 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG1 Pointer to a segment object.
    @return True if the two primitives are intersecting, and false otherwise. */
TgINLINE TgBOOL
FCN_VO(tgCO_CP_Test_SG)(
    VEC_OBJ_T(TgTUBE,CPC) ARG0, VEC_OBJ_T(TgSEGMENT,CPC) ARG1 );


/** @brief Update the collision packet with point(s) of intersection between a capsule and a segment.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
    @param [in] ARG1 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG2 Pointer to a segment object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_CP_Intersect_SG)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgTUBE,CPC) ARG1, VEC_OBJ_T(TgSEGMENT,CPC) ARG2 );

/** @brief Update the collision packet with point(s) of intersection between a capsule and a segment.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
    @param [in] ARG1 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG2 Vector holding the Segment Origin.
    @param [in] ARG3 Vector holding the position relative to the Segment Origin of the Segment Terminal Point.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_CP_Intersect_LR11)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgTUBE,CPC) ARG1, VEC_T(1,C) ARG2, VEC_T(1,C) ARG3 );


/** @brief Update the collision packet with point(s) of penetration between a capsule and a segment.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG2.
                         Contact normals are the direction for the object at ARG2 to move to achieve separation.
                         Depth values are measured from the surface of the object at ARG1 to the contact point.
    @param [in] ARG1 Pointer to a segment object.
    @param [in] ARG2 Pointer to tube object, interpreted as a capsule.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_SG_Penetrate_CP)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgSEGMENT,CPC) ARG1, VEC_OBJ_T(TgTUBE,CPC) ARG2 );

/** @brief Update the collision packet with point(s) of penetration between a capsule and a segment.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG2.
                         Contact normals are the direction for the object at ARG2 to move to achieve separation.
                         Depth values are measured from the surface of the object at ARG1 to the contact point.
    @param [in] ARG1 Vector holding the point of closest proximity on the segment to the capsule axis.
    @param [in] ARG2 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG3 Vector holding the point of closest proximity on the capsule axis to the segment.
    @param [in] ARG4 Vector holding a full broadcast of the minimal distance squared between the capsule axis and the segment.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_CP_Penetrate_LR11)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_T(1,C) ARG1, VEC_OBJ_T(TgTUBE,CPC) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4 );


/** @brief Output the sequence of points created by clipping the segment to the interior of the capsule.
    @param [out] OUT0 Pointer to a clip list object, where the resulting points are stored.
    @param [in] ARG1 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG2 Pointer to a segment object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_CP_Clip_SG)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, VEC_OBJ_T(TgTUBE,CPC) ARG1, VEC_OBJ_T(TgSEGMENT,CPC) ARG2 );

/** @brief Output the sequence of points created by clipping the segment to the interior of the capsule.
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point from clipping the segment.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the 2nd point from clipping the segment.
    @param [in] ARG2 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG3 Pointer to a segment object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_CP_Clip_PM_SG)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgTUBE,CPC) ARG2, VEC_OBJ_T(TgSEGMENT,CPC) ARG3 );

/** @brief Output the sequence of points created by clipping the segment to the interior of the capsule.
    @param [out] OUT0 Pointer to a clip list object, where the resulting points are stored.
    @param [in] ARG1 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG2 Vector holding the Segment Origin.
    @param [in] ARG3 Vector holding the position relative to the Segment Origin of the Segment Terminal Point.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_CP_Clip_LR11)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, VEC_OBJ_T(TgTUBE,CPC) ARG1, VEC_T(1,C) ARG2, VEC_T(1,C) ARG3 );

/** @brief Output the sequence of points created by clipping the segment to the interior of the capsule.
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point from clipping the segment.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the 2nd point from clipping the segment.
    @param [in] ARG2 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG3 Vector holding the Segment Origin.
    @param [in] ARG4 Vector holding the position relative to the Segment Origin of the Segment Terminal Point.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_CP_Clip_PM_LR11)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgTUBE,CPC) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4 );


/** @brief Determine the points of contact between the capsule and segment. Internal function that does not clip to the linear limits.
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point of contact.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the 2nd point of contact.
    @param [out] OUT2 Pointer to a vector holding the contact normal for the point in OUT0 (directed out of ARG4).
    @param [out] OUT3 Pointer to a vector holding the contact normal for the point in OUT1 (directed out of ARG4).
    @param [in] ARG4 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG5 Vector holding the Segment Origin.
    @param [in] ARG6 Vector holding the position relative to the Segment Origin of the Segment Terminal Point.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_CP_Contact_LR11)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_T(1,PC) OUT3, VEC_OBJ_T(TgTUBE,CPC) ARG4, VEC_T(1,C) ARG5, VEC_T(1,C) ARG6 );


/* Capsule - Capsule                                                                                                                                                               */

/** @brief Calculate the minimal distance squared between two capsules.
    @param [in] ARG0 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG1 Pointer to tube object, interpreted as a capsule.
    @return Minimal distance squared between two capsules, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CP_DistSq_CP)(
    VEC_OBJ_T(TgTUBE,CPC) ARG0, VEC_OBJ_T(TgTUBE,CPC) ARG1 );

/** @brief Calculate the minimal distance between two capsules.
    @param [in] ARG0 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG1 Pointer to tube object, interpreted as a capsule.
    @return Minimal distance between two capsules, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CP_Dist_CP)(
    VEC_OBJ_T(TgTUBE,CPC) ARG0, VEC_OBJ_T(TgTUBE,CPC) ARG1 );

/** @brief Calculate the minimal distance squared between two capsules, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG3 Pointer to tube object, interpreted as a capsule.
    @return Minimal distance squared between two capsules, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CP_ClosestSq_CP)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgTUBE,CPC) ARG2, VEC_OBJ_T(TgTUBE,CPC) ARG3 );

/** @brief Calculate the minimal distance between two capsules, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG3 Pointer to tube object, interpreted as a capsule.
    @return Minimal distance between two capsules, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CP_Closest_CP)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgTUBE,CPC) ARG2, VEC_OBJ_T(TgTUBE,CPC) ARG3 );


/** @brief Determine if the two primitives are intersecting.
    @param [in] ARG0 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG1 Pointer to tube object, interpreted as a capsule.
    @return True if the two primitives are intersecting, and false otherwise. */
TgINLINE TgBOOL
FCN_VO(tgCO_CP_Test_CP)(
    VEC_OBJ_T(TgTUBE,CPC) ARG0, VEC_OBJ_T(TgTUBE,CPC) ARG1 );

/** @brief Determine if the two primitives intersect over the sweep.
    @param [in] ARG0 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG1 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG2 Pointer to an object holding displacement values for ARG1.
    @return True if the two primitives intersect, and false otherwise. */
TgEXTN TgBOOL
FCN_VO(tgCO_CP_Test_Sweep_CP)(
    VEC_OBJ_T(TgTUBE,CPC) ARG0, VEC_OBJ_T(TgTUBE,CPC) ARG1, VEC_OBJ_T(TgDELTA,CPC) ARG2 );


/** @brief Update the collision packet with point(s) of penetration between a capsule and a segment.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG2.
                         Contact normals are the direction for the object at ARG2 to move to achieve separation.
                         Depth values are measured from the surface of the object at ARG1 to the contact point.
    @param [in] ARG1 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG2 Pointer to tube object, interpreted as a capsule.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_CP_Penetrate_CP)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgTUBE,CPC) ARG1, VEC_OBJ_T(TgTUBE,CPC) ARG2 );

/** @brief Update the collision packet with point(s) of penetration between two capsules when their axes are parallel.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG2.
                         Contact normals are the direction for the object at ARG2 to move to achieve separation.
                         Depth values are measured from the surface of the object at ARG1 to the contact point.
    @param [in] ARG1 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG2 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG3 Vector holding a full broadcast of the projection of the primary axis of ARG2 onto 1st unit basis vector of ARG1.
    @param [in] ARG4 Vector holding a full broadcast of the projection of the primary axis of ARG2 onto 2nd unit basis vector of ARG1.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_Penetrate_Parallel)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgTUBE,CPC) ARG1, VEC_OBJ_T(TgTUBE,CPC) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4 );

/** @brief Update the collision packet with point(s) of penetration between two capsules when their axes are not parallel.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG2.
                         Contact normals are the direction for the object at ARG2 to move to achieve separation.
                         Depth values are measured from the surface of the object at ARG1 to the contact point.
    @param [in] ARG1 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG2 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG3 Vector holding the cross product of the two capsules axes.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_Penetrate_NonParallel)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgTUBE,CPC) ARG1, VEC_OBJ_T(TgTUBE,CPC) ARG2, VEC_T(1,C) ARG3 );


/* Capsule - Triangle                                                                                                                                                              */

/** @brief Calculate the minimal distance squared between a capsule and a triangle.
    @param [in] ARG0 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG1 Pointer to a triangle object (space).
    @return Minimal distance squared between a capsule and a triangle, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CP_DistSq_ST)(
    VEC_OBJ_T(TgTUBE,CPC) ARG0, VEC_OBJ_T(TgSTRI,CPC) ARG1 );

/** @brief Calculate the minimal distance between a capsule and a triangle.
    @param [in] ARG0 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG1 Pointer to a triangle object (space).
    @return Minimal distance between a capsule and a triangle, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CP_Dist_ST)(
    VEC_OBJ_T(TgTUBE,CPC) ARG0, VEC_OBJ_T(TgSTRI,CPC) ARG1 );

/** @brief Calculate the minimal distance squared between a capsule and a triangle, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG3 Pointer to a triangle object (space).
    @return Minimal distance squared between the capsule and triangle, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CP_ClosestSq_ST)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgTUBE,CPC) ARG2, VEC_OBJ_T(TgSTRI,CPC) ARG3 );

/** @brief Calculate the minimal distance between a capsule and a triangle, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG3 Pointer to a triangle object (space).
    @return Minimal distance between the capsule and triangle, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CP_Closest_ST)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgTUBE,CPC) ARG2, VEC_OBJ_T(TgSTRI,CPC) ARG3 );


/** @brief Calculate the minimal distance squared between a capsule and a triangle, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG4 on ARG3.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the 1st barycentric coordinate of the closest point to ARG3 on ARG4.
    @param [out] OUT2 Pointer to a vector with a full broadcast of the 2nd barycentric coordinate of the closest point to ARG3 on ARG4.
    @param [in] ARG3 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG4 Pointer to a triangle object (space).
    @return Minimal distance squared between the capsule and triangle, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CP_ClosestSq_PM_ST)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_OBJ_T(TgTUBE,CPC) ARG3, VEC_OBJ_T(TgSTRI,CPC) ARG4 );

/** @brief Calculate the minimal distance between a capsule and a triangle, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG4 on ARG3.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the 1st barycentric coordinate of the closest point to ARG3 on ARG4.
    @param [out] OUT2 Pointer to a vector with a full broadcast of the 2nd barycentric coordinate of the closest point to ARG3 on ARG4.
    @param [in] ARG3 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG4 Pointer to a triangle object (space).
    @return Minimal distance between the capsule and triangle, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CP_Closest_PM_ST)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_OBJ_T(TgTUBE,CPC) ARG3, VEC_OBJ_T(TgSTRI,CPC) ARG4 );


/** @brief Determine if the two primitives are intersecting.
    @param [in] ARG0 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG1 Pointer to a triangle object (space).
    @return True if the two primitives are intersecting, and false otherwise. */
TgINLINE TgBOOL
FCN_VO(tgCO_CP_Test_ST)(
    VEC_OBJ_T(TgTUBE,CPC) ARG0, VEC_OBJ_T(TgSTRI,CPC) ARG1 );


/** @brief Update the collision packet with point(s) of intersection between a capsule and a triangle.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
    @param [in] ARG1 Pointer to a triangle object (space).
    @param [in] ARG2 Pointer to tube object, interpreted as a capsule.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_ST_Penetrate_CP)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgSTRI,CPC) ARG1, VEC_OBJ_T(TgTUBE,CPC) ARG2 );


/* Capsule - Plane                                                                                                                                                                 */

/** @brief Calculate the minimal distance squared between a capsule and a plane.
    @param [in] ARG0 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG1 Pointer to a plane object.
    @return Minimal distance squared between a capsule and a plane when the capsule is above the plane, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CP_DistSq_PN)(
    VEC_OBJ_T(TgTUBE,CPC) ARG0, VEC_OBJ_T(TgPLANE,CPC) ARG1 );

/** @brief Calculate the minimal distance between a capsule and a plane.
    @param [in] ARG0 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG1 Pointer to a plane object.
    @return Minimal distance between a capsule and a plane when the capsule is above the plane, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CP_Dist_PN)(
    VEC_OBJ_T(TgTUBE,CPC) ARG0, VEC_OBJ_T(TgPLANE,CPC) ARG1 );

/** @brief Calculate the minimal distance squared between a capsule and a plane, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG3 Pointer to a plane object.
    @return Minimal distance squared between the capsule and plane when the capsule is above the plane, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CP_ClosestSq_PN)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgTUBE,CPC) ARG2, VEC_OBJ_T(TgPLANE,CPC) ARG3 );

/** @brief Calculate the minimal distance between a capsule and a plane, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG3 Pointer to a plane object.
    @return Minimal distance between the capsule and plane when the capsule is above the plane, or zero otherwise, broadcast across all vector lanes. */
TgEXTN VEC_T(1)
FCN_VO(tgCO_CP_Closest_PN)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgTUBE,CPC) ARG2, VEC_OBJ_T(TgPLANE,CPC) ARG3 );


/** @brief Determine if the capsule is completely above the plane.
    @param [in] ARG0 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG1 Pointer to a plane object.
    @return True if the capsule is completely above the plane, and false otherwise. */
TgINLINE TgBOOL
FCN_VO(tgCO_CP_Test_PN)(
    VEC_OBJ_T(TgTUBE,CPC) ARG0, VEC_OBJ_T(TgPLANE,CPC) ARG1 );


/** @brief Update the collision packet with point(s) of penetration between a capsule and a plane.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG2.
                         Contact normals are the direction for the object at ARG2 to move to achieve separation.
                         Depth values are measured from the surface of the object at ARG1 to the contact point.
    @param [in] ARG1 Pointer to a plane object.
    @param [in] ARG2 Pointer to tube object, interpreted as a capsule.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_PN_Penetrate_CP)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgPLANE,CPC) ARG1, VEC_OBJ_T(TgTUBE,CPC) ARG2 );


/** @brief Update the collision packet with point(s) of contact between a swept capsule and a plane.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
    @param [in,out] OUT1 Pointer to a vector with a full broadcast of the normalized time of contact (percentage of time step).
    @param [in] ARG2 Pointer to a plane object. The test is done inside of this object's reference frame.
    @param [in] ARG3 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG4 Pointer to an object holding displacement values for ARG3.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_PN_Sweep_CP)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgPLANE,CPC) ARG2, VEC_OBJ_T(TgTUBE,CPC) ARG3, VEC_OBJ_T(TgDELTA,CPC) ARG4 );


/* Capsule - Sphere                                                                                                                                                                */

/** @brief Calculate the minimal distance squared between a capsule and a sphere.
    @param [in] ARG0 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG1 Pointer to a sphere object.
    @return Minimal distance squared between a capsule and a sphere, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CP_DistSq_SP)(
    VEC_OBJ_T(TgTUBE,CPC) ARG0, VEC_OBJ_T(TgSPHERE,CPC) ARG1 );

/** @brief Calculate the minimal distance between a capsule and a sphere.
    @param [in] ARG0 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG1 Pointer to a sphere object.
    @return Minimal distance between a capsule and a sphere, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CP_Dist_SP)(
    VEC_OBJ_T(TgTUBE,CPC) ARG0, VEC_OBJ_T(TgSPHERE,CPC) ARG1 );

/** @brief Calculate the minimal distance squared between a capsule and a sphere, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG3 Pointer to a sphere object.
    @return Minimal distance squared between the capsule and sphere, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CP_ClosestSq_SP)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgTUBE,CPC) ARG2, VEC_OBJ_T(TgSPHERE,CPC) ARG3 );

/** @brief Calculate the minimal distance between a capsule and a sphere, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG3 Pointer to a sphere object.
    @return Minimal distance between the capsule and sphere, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CP_Closest_SP)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgTUBE,CPC) ARG2, VEC_OBJ_T(TgSPHERE,CPC) ARG3 );


/** @brief Determine if the two primitives are intersecting.
    @param [in] ARG0 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG1 Pointer to a sphere object.
    @return True if the two primitives are intersecting, and false otherwise. */
TgINLINE TgBOOL
FCN_VO(tgCO_CP_Test_SP)(
    VEC_OBJ_T(TgTUBE,CPC) ARG0, VEC_OBJ_T(TgSPHERE,CPC) ARG1 );

/** @brief Determine if the two primitives are intersecting.
    @param [in] ARG0 Pointer to a triangle object (space).
    @param [in] ARG1 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG2 Pointer to an object holding displacement values for ARG1.
    @return True if the two primitives are intersecting, and false otherwise. */
TgEXTN TgBOOL
FCN_VO(tgCO_CP_Test_Sweep_ST)(
    VEC_OBJ_T(TgSTRI,CPC) ARG0, VEC_OBJ_T(TgTUBE,CPC) ARG1, VEC_OBJ_T(TgDELTA,CPC) ARG2 );


/** @brief Update the collision packet with point(s) of penetration between a capsule and sphere.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG2.
                         Contact normals are the direction for the object at ARG2 to move to achieve separation.
                         Depth values are measured from the surface of the object at ARG1 to the contact point.
    @param [in] ARG1 Pointer to a tube object, interpreted as a capsule.
    @param [in] ARG2 Pointer to a sphere object.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_CP_Penetrate_SP)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgTUBE,CPC) ARG1, VEC_OBJ_T(TgSPHERE,CPC) ARG2 );


/** @brief Calculate the minimal distance between a capsule and a point, and store the location on the capsule closest to the point.
    @param [out] OUT0 Pointer to a vector holding the closest point to the sphere on the capsule.
    @param [out] OUT1 Pointer to a vector holding the closest point to the capsule on the sphere.
    @param [in] ARG2 Vector holding a full broadcast of the minimal distance between the capsule and the point.
    @param [in] ARG3 Vector holding a full broadcast of the capsule radius.
    @param [in] ARG4 Vector holding the closest point to ARG6 on the capsule axis (line segment).
    @param [in] ARG5 Vector holding a full broadcast of the sphere radius.
    @param [in] ARG6 Vector holding the sphere origin.
    @return Minimal distance between a capsule and a point, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CP_Internal_Dist_SG_SP)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,C) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4, VEC_T(1,C) ARG5, VEC_T(1,C) ARG6 );


/* Capsule - Utility                                                                                                                                                               */

/** @brief Clip a line segment to the interior of a capsule.
    @param [out] OUT0 Pointer to a vector holding the updated (clipped) point from ARG3.
    @param [out] OUT1 Pointer to a vector holding the updated (clipped) point from ARG4.
    @param [in] ARG2 Pointer to a tube object, interpreted as a capsule.
    @param [in] ARG3 Vector holding a position (point) representing the 1st (starting) point of a line segment.
    @param [in] ARG4 Vector holding a position (point) representing the 2nd (terminal) point of a line segment.
   @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_CP_Clip_Points)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgTUBE,CPC) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4 );

/** @brief Clip a line strip to the interior of a capsule.
    @param [in,out] OUT0 Pointer to a clip list object (an array of vectors interpreted as a line strip).
    @param [in] ARG1 Pointer to a tube object, interpreted as a capsule.
   @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_CP_Clip)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, VEC_OBJ_T(TgTUBE,CPC) ARG1 );


/** @} TGS_COLLISION_CP */

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

    #define TGS_COLLISION_CAPSULE_H

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COLLISION_CAPSULE_H) */
#endif
