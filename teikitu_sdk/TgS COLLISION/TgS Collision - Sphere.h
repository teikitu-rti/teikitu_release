/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Sphere.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_SPHERE_H)
#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* == Collision ================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @addtogroup TGS_COLLISION_SP */
/** @{ */

/* ---- Sphere - Point ----------------------------------------------------------------------------------------------------------------------------------------------------------- */

/** @brief Calculate the minimal distance squared between a sphere and a point.
    @param [in] ARG0 Pointer to a sphere object.
    @param [in] ARG1 Vector holding a position (point).
    @return Minimal distance squared between the sphere and point, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_SP_DistSq_PT)(
    VEC_OBJ_T(TgSPHERE,CPC) ARG0, VEC_T(1,C) ARG1 );

/** @brief Calculate the minimal distance between a sphere and a point.
    @param [in] ARG0 Pointer to a sphere object.
    @param [in] ARG1 Vector holding a position (point).
    @return Minimal distance between the sphere and point, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_SP_Dist_PT)(
    VEC_OBJ_T(TgSPHERE,CPC) ARG0, VEC_T(1,C) ARG1 );

/** @brief Calculate the minimal distance squared between a sphere and a point, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG2 on ARG1.
    @param [in] ARG1 Pointer to a sphere object.
    @param [in] ARG2 Vector holding a position (point).
    @return Minimal distance squared between the sphere and point, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_SP_ClosestSq_PT)(
    VEC_T(1,PC) OUT0, VEC_OBJ_T(TgSPHERE,CPC) ARG1, VEC_T(1,C) ARG2 );

/** @brief Calculate the minimal distance between a sphere and a point, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG2 on ARG1.
    @param [in] ARG1 Pointer to a sphere object.
    @param [in] ARG2 Vector holding a position (point).
    @return Minimal distance between the sphere and point, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_SP_Closest_PT)(
    VEC_T(1,PC) OUT0, VEC_OBJ_T(TgSPHERE,CPC) ARG1, VEC_T(1,C) ARG2 );

/** @brief Determine if the two primitives are intersecting.
    @param [in] ARG0 Pointer to a sphere object.
    @param [in] ARG1 Vector holding a position (point).
    @return True if the two primitives are intersecting, and false otherwise. */
TgINLINE TgBOOL
FCN_VO(tgCO_SP_Test_PT)(
    VEC_OBJ_T(TgSPHERE,CPC) ARG0, VEC_T(1,C) ARG1 );

/** @brief Calculate the minimal distance squared between a sphere and a point, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG1.
    @param [in] ARG1 Pointer to a sphere object.
    @param [in] ARG2 Vector holding a full broadcast of the distance between the sphere origin and the point.
    @param [in] ARG3 Vector holding a position (point).
    @return Minimal distance squared between the sphere and point, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_SP_Util__ClosestSq_PT_Dist)(
    VEC_T(1,PC) OUT0, VEC_OBJ_T(TgSPHERE,CPC) ARG1, VEC_T(1,C) ARG2, VEC_T(1,C) ARG3 );

/** @brief Calculate the minimal distance between a sphere and a point, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG1.
    @param [in] ARG1 Pointer to a sphere object.
    @param [in] ARG2 Vector holding a full broadcast of the distance between the sphere origin and the point.
    @param [in] ARG3 Vector holding a position (point).
    @return Minimal distance between the sphere and point, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_SP_Util__Closest_PT_Dist)(
    VEC_T(1,PC) OUT0, VEC_OBJ_T(TgSPHERE,CPC) ARG1, VEC_T(1,C) ARG2, VEC_T(1,C) ARG3 );


/** @brief Update the collision packet with point(s) of penetration between the point and the sphere.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG2.
                         Contact normals are the direction for the object at ARG2 to move to achieve separation.
                         Depth values are measured from the surface of the object at ARG1 to the contact point.
    @param [in] ARG1 Pointer to a sphere object.
    @param [in] ARG2 Vector holding a position (point).
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_SP_Penetrate_PT)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgSPHERE,CPC) ARG1, VEC_T(1,C) ARG2 );

/** @brief Update the collision packet with the result of sweeping a point versus a sphere.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG3.
                         Contact normal is the surface normal at the contact point on ARG3.
    @param [in,out] OUT1 Pointer to a vector with a full broadcast of the normalized time of contact (percentage of time step).
    @param [in,out] OUT2 Pointer to an integer holding the starting index for the contact points generated in this call.
    @param [in] ARG3 Pointer to a sphere object. The test is done inside of this object's reference frame.
    @param [in] ARG4 Vector holding a position (point).
    @param [in] ARG5 Pointer to an object holding displacement values of ARG4.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_SP_Sweep_PT)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_T(1,PC) OUT1, TgRSIZE_P TgANALYSIS_OK_NULL OUT2, VEC_OBJ_T(TgSPHERE,CPC) ARG3, VEC_T(1,C) ARG4, VEC_OBJ_T(TgDELTA,CPC) ARG5 );

/** @brief Update the collision packet with the result of sweeping a sphere versus a point.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG3.
                         Contact normal is the surface normal at the contact point on ARG3.
    @param [in,out] OUT1 Pointer to a vector with a full broadcast of the normalized time of contact (percentage of time step).
    @param [in,out] OUT2 Pointer to an integer holding the starting index for the contact points generated in this call.
    @param [in] ARG3 Vector holding a position (point). The test is done inside of this object's reference frame.
    @param [in] ARG4 Pointer to a sphere object.
    @param [in] ARG5 Pointer to an object holding displacement values of ARG4.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_PT_Sweep_SP)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_T(1,PC) OUT1, TgRSIZE_P TgANALYSIS_OK_NULL OUT2, VEC_T(1,C) ARG3, VEC_OBJ_T(TgSPHERE,CPC) ARG4, VEC_OBJ_T(TgDELTA,CPC) ARG5 );


/* ---- Sphere - Linear ---------------------------------------------------------------------------------------------------------------------------------------------------------- */

/** @brief Update the collision packet with point(s) of penetration between a linear and a sphere.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG2.
                         Contact normals are the direction for the object at ARG2 to move to achieve separation.
                         Depth values are measured from the surface of the object at ARG1 to the contact point.
    @param [in] ARG1 Pointer to a sphere object.
    @param [in] ARG2 Vector holding the closest point to ARG1 on {ARG2,ARG4}.
    @param [in] ARG3 Vector holding a full broadcast of the distance squared between ARG2 and the sphere origin.
    @param [in] ARG4 Vector holding the Line Direction.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_SP_Util__Penetrate_Closest_PT_Dist)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgSPHERE,CPC) ARG1, VEC_T(1,C) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4 );


/* ---- Sphere - Line ------------------------------------------------------------------------------------------------------------------------------------------------------------ */

/** @brief Calculate the minimal distance squared between a sphere and a line.
    @param [in] ARG0 Pointer to a sphere object.
    @param [in] ARG1 Pointer to a line object.
    @return Minimal distance squared between the sphere and line, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_SP_DistSq_LN)(
    VEC_OBJ_T(TgSPHERE,CPC) ARG0, VEC_OBJ_T(TgLINE,CPC) ARG1 );

/** @brief Calculate the minimal distance between a sphere and a line.
    @param [in] ARG0 Pointer to a sphere object.
    @param [in] ARG1 Pointer to a line object.
    @return Minimal distance between the sphere and line, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_SP_Dist_LN)(
    VEC_OBJ_T(TgSPHERE,CPC) ARG0, VEC_OBJ_T(TgLINE,CPC) ARG1 );

/** @brief Calculate the minimal distance squared between a sphere and a line, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a sphere object.
    @param [in] ARG3 Pointer to a line object.
    @return Minimal distance squared between the sphere and line, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_SP_ClosestSq_LN)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgSPHERE,CPC) ARG2, VEC_OBJ_T(TgLINE,CPC) ARG3 );

/** @brief Calculate the minimal distance between a sphere and a line, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a sphere object.
    @param [in] ARG3 Pointer to a line object.
    @return Minimal distance between the sphere and line, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_SP_Closest_LN)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgSPHERE,CPC) ARG2, VEC_OBJ_T(TgLINE,CPC) ARG3 );

/** @brief Calculate the minimal distance squared between a sphere and a line, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a sphere object.
    @param [in] ARG3 Pointer to a line object.
    @return Minimal distance squared between the sphere and line, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_SP_ClosestSq_PM_LN)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgSPHERE,CPC) ARG2, VEC_OBJ_T(TgLINE,CPC) ARG3 );

/** @brief Calculate the minimal distance between a sphere and a line, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a sphere object.
    @param [in] ARG3 Pointer to a line object.
    @return Minimal distance between the sphere and line, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_SP_Closest_PM_LN)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgSPHERE,CPC) ARG2, VEC_OBJ_T(TgLINE,CPC) ARG3 );

/** @brief Determine if the two primitives are intersecting.
    @param [in] ARG0 Pointer to a sphere object.
    @param [in] ARG1 Pointer to a line object.
    @return True if the two primitives are intersecting, and false otherwise. */
TgINLINE TgBOOL
FCN_VO(tgCO_SP_Test_LN)(
    VEC_OBJ_T(TgSPHERE,CPC) ARG0, VEC_OBJ_T(TgLINE,CPC) ARG1 );

/** @brief Update the collision packet with point(s) of intersection between the line and the sphere.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG1.
                         Contact normal is the surface normal at the contact point on ARG1.
    @param [in] ARG1 Pointer to a sphere object.
    @param [in] ARG2 Pointer to a line object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_SP_Intersect_LN)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgSPHERE,CPC) ARG1, VEC_OBJ_T(TgLINE,CPC) ARG2 );

/** @brief Update the collision packet with point(s) of penetration between the line and the sphere.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG2.
                         Contact normals are the direction for the object at ARG2 to move to achieve separation.
                         Depth values are measured from the surface of the object at ARG1 to the contact point.
    @param [in] ARG1 Pointer to a sphere object.
    @param [in] ARG2 Pointer to a line object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_SP_Penetrate_LN)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgSPHERE,CPC) ARG1, VEC_OBJ_T(TgLINE,CPC) ARG2 );

/** @brief Update the collision packet with the result of sweeping a line versus a sphere.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG3.
                         Contact normal is the surface normal at the contact point on ARG3.
    @param [in,out] OUT1 Pointer to a vector with a full broadcast of the normalized time of contact (percentage of time step).
    @param [in,out] OUT2 Pointer to an integer holding the starting index for the contact points generated in this call.
    @param [in] ARG3 Pointer to a sphere object. The test is done inside of this object's reference frame.
    @param [in] ARG4 Pointer to a line object.
    @param [in] ARG5 Pointer to an object holding displacement values for ARG4.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_SP_Sweep_LN)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_T(1,PC) OUT1, TgRSIZE_P TgANALYSIS_OK_NULL OUT2, VEC_OBJ_T(TgSPHERE,CPC) ARG3, VEC_OBJ_T(TgLINE,CPC) ARG4, VEC_OBJ_T(TgDELTA,CPC) ARG5 );

/** @brief Update the collision packet with the result of sweeping a sphere versus a line.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG3.
                         Contact normal is the surface normal at the contact point on ARG3.
    @param [in,out] OUT1 Pointer to a vector with a full broadcast of the normalized time of contact (percentage of time step).
    @param [in,out] OUT2 Pointer to an integer holding the starting index for the contact points generated in this call.
    @param [in] ARG3 Pointer to a line object. The test is done inside of this object's reference frame.
    @param [in] ARG4 Pointer to a sphere object.
    @param [in] ARG5 Pointer to an object holding displacement values for ARG4.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_LN_Sweep_SP)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_T(1,PC) OUT1, TgRSIZE_P TgANALYSIS_OK_NULL OUT2, VEC_OBJ_T(TgLINE,CPC) ARG3, VEC_OBJ_T(TgSPHERE,CPC) ARG4, VEC_OBJ_T(TgDELTA,CPC) ARG5 );

/** @brief Clip the line so that it is fully contained by the sphere.
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point from clipping the line.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the 2nd point from clipping the line.
    @param [in] ARG2 Pointer to a sphere object.
    @param [in] ARG3 Pointer to a line object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_SP_Clip_PM_LN)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgSPHERE,CPC) ARG2, VEC_OBJ_T(TgLINE,CPC) ARG3 );

/** @brief Clip the line so that it is fully contained by the sphere.
    @param [out] OUT0 Pointer to a clip list object, where the resulting points are stored.
    @param [in] ARG1 Pointer to a sphere object.
    @param [in] ARG2 Pointer to a line object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_SP_Clip_LN)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, VEC_OBJ_T(TgSPHERE,CPC) ARG1, VEC_OBJ_T(TgLINE,CPC) ARG2 );


/** @brief Store point(s) of intersection between the line and the sphere.
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point of intersection.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the 2nd point of intersection.
    @param [out] OUT2 Pointer to a vector holding the contact normal for the point in OUT0 (directed out of ARG4).
    @param [out] OUT3 Pointer to a vector holding the contact normal for the point in OUT1 (directed out of ARG4).
    @param [in] ARG4 Pointer to a sphere object.
    @param [in] ARG5 Vector holding the Line Origin.
    @param [in] ARG6 Vector holding the Line Direction.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_SP_Intersect_PM_LR00)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_T(1,PC) OUT3, VEC_OBJ_T(TgSPHERE,CPC) ARG4, VEC_T(1,C) ARG5, VEC_T(1,C) ARG6 );

/** @brief Update the collision packet with point(s) of intersection between the line and the sphere.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG1.
                         Contact normal is the surface normal at the contact point on ARG1.
    @param [in] ARG1 Pointer to a sphere object.
    @param [in] ARG2 Vector holding the Line Origin.
    @param [in] ARG3 Vector holding the Line Direction.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_SP_Intersect_LR00)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgSPHERE,CPC) ARG1, VEC_T(1,C) ARG2, VEC_T(1,C) ARG3 );

/** @brief Update the collision packet with the result of sweeping a line versus a sphere.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG3.
                         Contact normal is the surface normal at the contact point on ARG3.
    @param [in,out] OUT1 Pointer to a vector with a full broadcast of the normalized time of contact (percentage of time step).
    @param [in,out] OUT2 Pointer to an integer holding the starting index for the contact points generated in this call.
    @param [in] ARG3 Pointer to a sphere object. The test is done inside of this object's reference frame.
    @param [in] ARG4 Vector holding the Line Origin.
    @param [in] ARG5 Vector holding the Line Direction.
    @param [in] ARG6 Pointer to an object holding displacement values for {ARG4,ARG5}.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_SP_Sweep_LR00)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_T(1,PC) OUT1, TgRSIZE_P TgANALYSIS_OK_NULL OUT2, VEC_OBJ_T(TgSPHERE,CPC) ARG3, VEC_T(1,C) ARG4, VEC_T(1,C) ARG5, VEC_OBJ_T(TgDELTA,CPC) ARG6 );

/** @brief Update the collision packet with the result of sweeping a sphere versus a line.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of {ARG3,ARG4}.
                         Contact normal is the surface normal at the contact point on {ARG3,ARG4}.
    @param [in,out] OUT1 Pointer to a vector with a full broadcast of the normalized time of contact (percentage of time step).
    @param [in,out] OUT2 Pointer to an integer holding the starting index for the contact points generated in this call.
    @param [in] ARG3 Vector holding the Line Origin. The test is done inside of this object's reference frame.
    @param [in] ARG4 Vector holding the Line Direction.
    @param [in] ARG5 Pointer to a sphere object.
    @param [in] ARG6 Pointer to an object holding displacement values for ARG5.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_LR00_Sweep_SP)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_T(1,PC) OUT1, TgRSIZE_P TgANALYSIS_OK_NULL OUT2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4, VEC_OBJ_T(TgSPHERE,CPC) ARG5, VEC_OBJ_T(TgDELTA,CPC) ARG6 );


/* ---- Sphere - Ray ------------------------------------------------------------------------------------------------------------------------------------------------------------- */

/** @brief Calculate the minimal distance squared between a sphere and a ray.
    @param [in] ARG0 Pointer to a sphere object.
    @param [in] ARG1 Pointer to a ray object.
    @return Minimal distance squared between the sphere and ray, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_SP_DistSq_RY)(
    VEC_OBJ_T(TgSPHERE,CPC) ARG0, VEC_OBJ_T(TgRAY,CPC) ARG1 );

/** @brief Calculate the minimal distance between a sphere and a ray.
    @param [in] ARG0 Pointer to a sphere object.
    @param [in] ARG1 Pointer to a ray object.
    @return Minimal distance between the sphere and ray, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_SP_Dist_RY)(
    VEC_OBJ_T(TgSPHERE,CPC) ARG0, VEC_OBJ_T(TgRAY,CPC) ARG1 );

/** @brief Calculate the minimal distance squared between a sphere and a ray, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a sphere object.
    @param [in] ARG3 Pointer to a ray object.
    @return Minimal distance squared between the sphere and ray, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_SP_ClosestSq_RY)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgSPHERE,CPC) ARG2, VEC_OBJ_T(TgRAY,CPC) ARG3 );

/** @brief Calculate the minimal distance between a sphere and a ray, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a sphere object.
    @param [in] ARG3 Pointer to a ray object.
    @return Minimal distance between the sphere and ray, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_SP_Closest_RY)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgSPHERE,CPC) ARG2, VEC_OBJ_T(TgRAY,CPC) ARG3 );

/** @brief Calculate the minimal distance squared between a sphere and a ray, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a sphere object.
    @param [in] ARG3 Pointer to a ray object.
    @return Minimal distance squared between the sphere and ray, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_SP_ClosestSq_PM_RY)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgSPHERE,CPC) ARG2, VEC_OBJ_T(TgRAY,CPC) ARG3 );

/** @brief Calculate the minimal distance between a sphere and a ray, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a sphere object.
    @param [in] ARG3 Pointer to a ray object.
    @return Minimal distance between the sphere and ray, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_SP_Closest_PM_RY)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgSPHERE,CPC) ARG2, VEC_OBJ_T(TgRAY,CPC) ARG3 );

/** @brief Determine if the two primitives are intersecting.
    @param [in] ARG0 Pointer to a sphere object.
    @param [in] ARG1 Pointer to a ray object.
    @return True if the two primitives are intersecting, and false otherwise. */
TgINLINE TgBOOL
FCN_VO(tgCO_SP_Test_RY)(
    VEC_OBJ_T(TgSPHERE,CPC) ARG0, VEC_OBJ_T(TgRAY,CPC) ARG1 );

/** @brief Update the collision packet with point(s) of intersection between the ray and the sphere.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG1.
                         Contact normal is the surface normal at the contact point on ARG1.
    @param [in] ARG1 Pointer to a sphere object.
    @param [in] ARG2 Pointer to a ray object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_SP_Intersect_RY)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgSPHERE,CPC) ARG1, VEC_OBJ_T(TgRAY,CPC) ARG2 );

/** @brief Update the collision packet with point(s) of penetration between the ray and the sphere.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG2.
                         Contact normals are the direction for the object at ARG2 to move to achieve separation.
                         Depth values are measured from the surface of the object at ARG1 to the contact point.
    @param [in] ARG1 Pointer to a sphere object.
    @param [in] ARG2 Pointer to a ray object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_SP_Penetrate_RY)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgSPHERE,CPC) ARG1, VEC_OBJ_T(TgRAY,CPC) ARG2 );

/** @brief Update the collision packet with the result of sweeping a ray versus a sphere.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG3.
                         Contact normal is the surface normal at the contact point on ARG3.
    @param [in,out] OUT1 Pointer to a vector with a full broadcast of the normalized time of contact (percentage of time step).
    @param [in,out] OUT2 Pointer to an integer holding the starting index for the contact points generated in this call.
    @param [in] ARG3 Pointer to a sphere object. The test is done inside of this object's reference frame.
    @param [in] ARG4 Pointer to a ray object.
    @param [in] ARG5 Pointer to an object holding displacement values for ARG4.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_SP_Sweep_RY)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_T(1,PC) OUT1, TgRSIZE_P TgANALYSIS_OK_NULL OUT2, VEC_OBJ_T(TgSPHERE,CPC) ARG3, VEC_OBJ_T(TgRAY,CPC) ARG4, VEC_OBJ_T(TgDELTA,CPC) ARG5 );

/** @brief Update the collision packet with the result of sweeping a sphere versus a ray.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG3.
                         Contact normal is the surface normal at the contact point on ARG3.
    @param [in,out] OUT1 Pointer to a vector with a full broadcast of the normalized time of contact (percentage of time step).
    @param [in,out] OUT2 Pointer to an integer holding the starting index for the contact points generated in this call.
    @param [in] ARG3 Pointer to a ray object. The test is done inside of this object's reference frame.
    @param [in] ARG4 Pointer to a sphere object.
    @param [in] ARG5 Pointer to an object holding displacement values for ARG4.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_RY_Sweep_SP)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_T(1,PC) OUT1, TgRSIZE_P TgANALYSIS_OK_NULL OUT2, VEC_OBJ_T(TgRAY,CPC) ARG3, VEC_OBJ_T(TgSPHERE,CPC) ARG4, VEC_OBJ_T(TgDELTA,CPC) ARG5 );

/** @brief Clip the ray so that it is fully contained by the sphere.
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point from clipping the ray.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the 2nd point from clipping the ray.
    @param [in] ARG2 Pointer to a sphere object.
    @param [in] ARG3 Pointer to a ray object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_SP_Clip_PM_RY)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgSPHERE,CPC) ARG2, VEC_OBJ_T(TgRAY,CPC) ARG3 );

/** @brief Clip the ray so that it is fully contained by the sphere.
    @param [out] OUT0 Pointer to a clip list object, where the clipped points of the ray will be added.
    @param [in] ARG1 Pointer to a sphere object.
    @param [in] ARG2 Pointer to a ray object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_SP_Clip_RY)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, VEC_OBJ_T(TgSPHERE,CPC) ARG1, VEC_OBJ_T(TgRAY,CPC) ARG2 );


/** @brief Store point(s) of intersection between the ray and the sphere.
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point of contact.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the 2nd point of contact.
    @param [out] OUT2 Pointer to a vector holding the contact normal for the point in OUT0 (directed out of ARG4).
    @param [out] OUT3 Pointer to a vector holding the contact normal for the point in OUT1 (directed out of ARG4).
    @param [in] ARG4 Pointer to a sphere object.
    @param [in] ARG5 Vector holding the Ray Origin.
    @param [in] ARG6 Vector holding the Ray Direction.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_SP_Intersect_PM_LR10)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_T(1,PC) OUT3, VEC_OBJ_T(TgSPHERE,CPC) ARG4, VEC_T(1,C) ARG5, VEC_T(1,C) ARG6 );

/** @brief Update the collision packet with point(s) of intersection between the ray and the sphere.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG1.
                         Contact normal is the surface normal at the contact point on ARG1.
    @param [in] ARG1 Pointer to a sphere object.
    @param [in] ARG2 Vector holding the Ray Origin.
    @param [in] ARG3 Vector holding the Ray Direction.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_SP_Intersect_LR10)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgSPHERE,CPC) ARG1, VEC_T(1,C) ARG2, VEC_T(1,C) ARG3 );

/** @brief Update the collision packet with the result of sweeping a ray versus a sphere.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG3.
                         Contact normal is the surface normal at the contact point on ARG3.
    @param [in,out] OUT1 Pointer to a vector with a full broadcast of the normalized time of contact (percentage of time step).
    @param [in,out] OUT2 Pointer to an integer holding the starting index for the contact points generated in this call.
    @param [in] ARG3 Pointer to a sphere object. The test is done inside of this object's reference frame.
    @param [in] ARG4 Vector holding the Ray Origin.
    @param [in] ARG5 Vector holding the Ray Direction.
    @param [in] ARG6 Pointer to an object holding displacement values for {ARG4,ARG5}.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_SP_Sweep_LR10)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_T(1,PC) OUT1, TgRSIZE_P TgANALYSIS_OK_NULL OUT2, VEC_OBJ_T(TgSPHERE,CPC) ARG3, VEC_T(1,C) ARG4, VEC_T(1,C) ARG5, VEC_OBJ_T(TgDELTA,CPC) ARG6 );

/** @brief Update the collision packet with the result of sweeping a sphere versus a ray.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of {ARG3,ARG4}.
                         Contact normal is the surface normal at the contact point on {ARG3,ARG4}.
    @param [in,out] OUT1 Pointer to a vector with a full broadcast of the normalized time of contact (percentage of time step).
    @param [in,out] OUT2 Pointer to an integer holding the starting index for the contact points generated in this call.
    @param [in] ARG3 Vector holding the Ray Origin. The test is done inside of this object's reference frame.
    @param [in] ARG4 Vector holding the Ray Direction.
    @param [in] ARG5 Pointer to a sphere object.
    @param [in] ARG6 Pointer to an object holding displacement values for ARG5.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_LR10_Sweep_SP)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_T(1,PC) OUT1, TgRSIZE_P TgANALYSIS_OK_NULL OUT2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4, VEC_OBJ_T(TgSPHERE,CPC) ARG5, VEC_OBJ_T(TgDELTA,CPC) ARG6 );


/* ---- Sphere - Segment --------------------------------------------------------------------------------------------------------------------------------------------------------- */

/** @brief Calculate the minimal distance squared between a sphere and a segment.
    @param [in] ARG0 Pointer to a sphere object.
    @param [in] ARG1 Pointer to a segment object.
    @return Minimal distance squared between the sphere and segment, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_SP_DistSq_SG)(
    VEC_OBJ_T(TgSPHERE,CPC) ARG0, VEC_OBJ_T(TgSEGMENT,CPC) ARG1 );

/** @brief Calculate the minimal distance between a sphere and a segment.
    @param [in] ARG0 Pointer to a sphere object.
    @param [in] ARG1 Pointer to a segment object.
    @return Minimal distance between the sphere and segment, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_SP_Dist_SG)(
    VEC_OBJ_T(TgSPHERE,CPC) ARG0, VEC_OBJ_T(TgSEGMENT,CPC) ARG1 );

/** @brief Calculate the minimal distance squared between a sphere and a segment, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a sphere object.
    @param [in] ARG3 Pointer to a segment object.
    @return Minimal distance squared between the sphere and segment, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_SP_ClosestSq_SG)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgSPHERE,CPC) ARG2, VEC_OBJ_T(TgSEGMENT,CPC) ARG3 );

/** @brief Calculate the minimal distance between a sphere and a segment, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a sphere object.
    @param [in] ARG3 Pointer to a segment object.
    @return Minimal distance between the sphere and segment, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_SP_Closest_SG)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgSPHERE,CPC) ARG2, VEC_OBJ_T(TgSEGMENT,CPC) ARG3 );

/** @brief Calculate the minimal distance squared between a sphere and a segment, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a sphere object.
    @param [in] ARG3 Pointer to a segment object.
    @return Minimal distance squared between the sphere and segment, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_SP_ClosestSq_PM_SG)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgSPHERE,CPC) ARG2, VEC_OBJ_T(TgSEGMENT,CPC) ARG3 );

/** @brief Calculate the minimal distance between a sphere and a segment, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a sphere object.
    @param [in] ARG3 Pointer to a segment object.
    @return Minimal distance between the sphere and segment, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_SP_Closest_PM_SG)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgSPHERE,CPC) ARG2, VEC_OBJ_T(TgSEGMENT,CPC) ARG3 );

/** @brief Determine if the two primitives are intersecting.
    @param [in] ARG0 Pointer to a sphere object.
    @param [in] ARG1 Pointer to a segment object.
    @return True if the two primitives are intersecting, and false otherwise. */
TgINLINE TgBOOL
FCN_VO(tgCO_SP_Test_SG)(
    VEC_OBJ_T(TgSPHERE,CPC) ARG0, VEC_OBJ_T(TgSEGMENT,CPC) ARG1 );

/** @brief Update the collision packet with point(s) of intersection between the segment and the sphere.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG1.
                         Contact normal is the surface normal at the contact point on ARG1.
    @param [in] ARG1 Pointer to a sphere object.
    @param [in] ARG2 Pointer to a segment object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_SP_Intersect_SG)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgSPHERE,CPC) ARG1, VEC_OBJ_T(TgSEGMENT,CPC) ARG2 );

/** @brief Update the collision packet with point(s) of penetration between the segment and the sphere.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG2.
                         Contact normals are the direction for the object at ARG2 to move to achieve separation.
                         Depth values are measured from the surface of the object at ARG1 to the contact point.
    @param [in] ARG1 Pointer to a sphere object.
    @param [in] ARG2 Pointer to a segment object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_SP_Penetrate_SG)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgSPHERE,CPC) ARG1, VEC_OBJ_T(TgSEGMENT,CPC) ARG2 );

/** @brief Update the collision packet with the result of sweeping a segment versus a sphere.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG3.
                         Contact normal is the surface normal at the contact point on ARG3.
    @param [in,out] OUT1 Pointer to a vector with a full broadcast of the normalized time of contact (percentage of time step).
    @param [in,out] OUT2 Pointer to an integer holding the starting index for the contact points generated in this call.
    @param [in] ARG3 Pointer to a sphere object. The test is done inside of this object's reference frame.
    @param [in] ARG4 Pointer to a segment object.
    @param [in] ARG5 Pointer to an object holding displacement values for ARG4.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_SP_Sweep_SG)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_T(1,PC) OUT1, TgRSIZE_P TgANALYSIS_OK_NULL OUT2, VEC_OBJ_T(TgSPHERE,CPC) ARG3, VEC_OBJ_T(TgSEGMENT,CPC) ARG4, VEC_OBJ_T(TgDELTA,CPC) ARG5 );

/** @brief Update the collision packet with the result of sweeping a sphere versus a segment.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG3.
                         Contact normal is the surface normal at the contact point on ARG3.
    @param [in,out] OUT1 Pointer to a vector with a full broadcast of the normalized time of contact (percentage of time step).
    @param [in,out] OUT2 Pointer to an integer holding the starting index for the contact points generated in this call.
    @param [in] ARG3 Pointer to a segment object. The test is done inside of this object's reference frame.
    @param [in] ARG4 Pointer to a sphere object.
    @param [in] ARG5 Pointer to an object holding displacement values for ARG4.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_SG_Sweep_SP)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_T(1,PC) OUT1, TgRSIZE_P TgANALYSIS_OK_NULL OUT2, VEC_OBJ_T(TgSEGMENT,CPC) ARG3, VEC_OBJ_T(TgSPHERE,CPC) ARG4, VEC_OBJ_T(TgDELTA,CPC) ARG5 );

/** @brief Clip the segment so that it is fully contained by the sphere.
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point from clipping the segment.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the 2nd point from clipping the segment.
    @param [in] ARG2 Pointer to a sphere object.
    @param [in] ARG3 Pointer to a segment object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_SP_Clip_PM_SG)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgSPHERE,CPC) ARG2, VEC_OBJ_T(TgSEGMENT,CPC) ARG3 );

/** @brief Clip the segment so that it is fully contained by the sphere.
    @param [out] OUT0 Pointer to a clip list object, where the clipped points of the segment will be added.
    @param [in] ARG1 Pointer to a sphere object.
    @param [in] ARG2 Pointer to a segment object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_SP_Clip_SG)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, VEC_OBJ_T(TgSPHERE,CPC) ARG1, VEC_OBJ_T(TgSEGMENT,CPC) ARG2 );


/** @brief Store point(s) of intersection between the segment and the sphere.
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point of intersection.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the 2nd point of intersection.
    @param [out] OUT2 Pointer to a vector holding the contact normal for the point in OUT0 (directed out of ARG4).
    @param [out] OUT3 Pointer to a vector holding the contact normal for the point in OUT1 (directed out of ARG4).
    @param [in] ARG4 Pointer to a sphere object.
    @param [in] ARG5 Vector holding the Line Origin.
    @param [in] ARG6 Vector holding the Line Direction.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_SP_Intersect_PM_LR11)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_T(1,PC) OUT3, VEC_OBJ_T(TgSPHERE,CPC) ARG4, VEC_T(1,C) ARG5, VEC_T(1,C) ARG6 );

/** @brief Update the collision packet with point(s) of intersection between the segment and the sphere.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG1.
                         Contact normal is the surface normal at the contact point on ARG1.
    @param [in] ARG1 Pointer to a sphere object.
    @param [in] ARG2 Vector holding the Segment Origin.
    @param [in] ARG3 Vector holding the position relative to the Segment Origin of the Segment Terminal Point.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_SP_Intersect_LR11)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgSPHERE,CPC) ARG1, VEC_T(1,C) ARG2, VEC_T(1,C) ARG3 );

/** @brief Update the collision packet with the result of sweeping a segment versus a sphere.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG3.
                         Contact normal is the surface normal at the contact point on ARG3.
    @param [in,out] OUT1 Pointer to a vector with a full broadcast of the normalized time of contact (percentage of time step).
    @param [in,out] OUT2 Pointer to an integer holding the starting index for the contact points generated in this call.
    @param [in] ARG3 Pointer to a sphere object. The test is done inside of this object's reference frame.
    @param [in] ARG4 Vector holding the Segment Origin.
    @param [in] ARG5 Vector holding the position relative to the Segment Origin of the Segment Terminal Point.
    @param [in] ARG6 Pointer to an object holding displacement values for {ARG4,ARG5}.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_SP_Sweep_LR11)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_T(1,PC) OUT1, TgRSIZE_P TgANALYSIS_OK_NULL OUT2, VEC_OBJ_T(TgSPHERE,CPC) ARG3, VEC_T(1,C) ARG4, VEC_T(1,C) ARG5, VEC_OBJ_T(TgDELTA,CPC) ARG6 );

/** @brief Update the collision packet with the result of sweeping a sphere versus a segment.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of {ARG3,ARG4}.
                         Contact normal is the surface normal at the contact point on {ARG3,ARG4}.
    @param [in,out] OUT1 Pointer to a vector with a full broadcast of the normalized time of contact (percentage of time step).
    @param [in,out] OUT2 Pointer to an integer holding the starting index for the contact points generated in this call.
    @param [in] ARG3 Vector holding the Segment Origin. The test is done inside of this object's reference frame.
    @param [in] ARG4 Vector holding the position relative to the Segment Origin of the Segment Terminal Point.
    @param [in] ARG5 Pointer to a sphere object.
    @param [in] ARG6 Pointer to an object holding displacement values for ARG5.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_LR11_Sweep_SP)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_T(1,PC) OUT1, TgRSIZE_P TgANALYSIS_OK_NULL OUT2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4, VEC_OBJ_T(TgSPHERE,CPC) ARG5, VEC_OBJ_T(TgDELTA,CPC) ARG6 );


/* ---- Sphere - Plane ----------------------------------------------------------------------------------------------------------------------------------------------------------- */

/** @brief Calculate the minimal distance squared between a sphere and a plane.
    @param [in] ARG0 Pointer to a sphere object.
    @param [in] ARG1 Pointer to a plane object.
    @return Minimal distance squared between the sphere and plane, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_SP_DistSq_PN)(
    VEC_OBJ_T(TgSPHERE,CPC) ARG0, VEC_OBJ_T(TgPLANE,CPC) ARG1 );

/** @brief Calculate the minimal distance between a sphere and a plane.
    @param [in] ARG0 Pointer to a sphere object.
    @param [in] ARG1 Pointer to a plane object.
    @return Minimal distance between the sphere and plane, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_SP_Dist_PN)(
    VEC_OBJ_T(TgSPHERE,CPC) ARG0, VEC_OBJ_T(TgPLANE,CPC) ARG1 );

/** @brief Calculate the minimal distance squared between a sphere and a plane, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a sphere object.
    @param [in] ARG3 Pointer to a plane object.
    @return Minimal distance squared between the sphere and plane, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_SP_ClosestSq_PN)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgSPHERE,CPC) ARG2, VEC_OBJ_T(TgPLANE,CPC) ARG3 );

/** @brief Calculate the minimal distance between a sphere and a plane, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a sphere object.
    @param [in] ARG3 Pointer to a plane object.
    @return Minimal distance squared between the sphere and plane, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_SP_Closest_PN)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgSPHERE,CPC) ARG2, VEC_OBJ_T(TgPLANE,CPC) ARG3 );

/** @brief Determine if the sphere is completely above the plane.
    @param [in] ARG0 Pointer to a sphere object.
    @param [in] ARG1 Pointer to a plane object.
    @return True if the sphere is completely above the plane, and false otherwise. */
TgINLINE TgBOOL
FCN_VO(tgCO_SP_Test_PN)(
    VEC_OBJ_T(TgSPHERE,CPC) ARG0, VEC_OBJ_T(TgPLANE,CPC) ARG1 );

/** @brief Update the collision packet with point(s) of penetration between the sphere and a plane.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG2.
                         Contact normals are the direction for the object at ARG2 to move to achieve separation.
                         Depth values are measured from the surface of the object at ARG1 to the contact point.
    @param [in] ARG1 Pointer to a sphere object.
    @param [in] ARG2 Pointer to a plane object.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_SP_Penetrate_PN)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgSPHERE,CPC) ARG1, VEC_OBJ_T(TgPLANE,CPC) ARG2 );

/** @brief Update the collision packet with point(s) of penetration between the plane and a sphere.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG2.
                         Contact normals are the direction for the object at ARG2 to move to achieve separation.
                         Depth values are measured from the surface of the object at ARG1 to the contact point.
    @param [in] ARG1 Pointer to a plane object.
    @param [in] ARG2 Pointer to a sphere object.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_PN_Penetrate_SP)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgPLANE,CPC) ARG1, VEC_OBJ_T(TgSPHERE,CPC) ARG2 );

/** @brief Update the collision packet with the result of sweeping a sphere versus a plane.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG2.
                         Contact normal is the surface normal at the contact point on ARG2.
    @param [in,out] OUT1 Pointer to a vector with a full broadcast of the normalized time of contact (percentage of time step).
    @param [in] ARG2: Pointer to a plane object. The test is done inside of this object's reference frame.
    @param [in] ARG3: Pointer to a sphere object.
    @param [in] ARG4 Pointer to an object holding displacement values for ARG3.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_PN_Sweep_SP)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgPLANE,CPC) ARG2, VEC_OBJ_T(TgSPHERE,CPC) ARG3, VEC_OBJ_T(TgDELTA,CPC) ARG4 );


/* ---- Sphere - Triangle -------------------------------------------------------------------------------------------------------------------------------------------------------- */

/** @brief Calculate the minimal distance squared between a sphere and a triangle.
    @param [in] ARG0 Pointer to a sphere object.
    @param [in] ARG1 Pointer to a triangle (edge) object.
    @return Minimal distance squared between the sphere and triangle, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_SP_DistSq_ET)(
    VEC_OBJ_T(TgSPHERE,CPC) ARG0, VEC_OBJ_T(TgETRI,CPC) ARG1 );

/** @brief Calculate the minimal distance between a sphere and a triangle.
    @param [in] ARG0 Pointer to a sphere object.
    @param [in] ARG1 Pointer to a triangle (edge) object.
    @return Minimal distance between the sphere and triangle, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_SP_Dist_ET)(
    VEC_OBJ_T(TgSPHERE,CPC) ARG0, VEC_OBJ_T(TgETRI,CPC) ARG1 );

/** @brief Calculate the minimal distance squared between a sphere and a triangle, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a sphere object.
    @param [in] ARG3 Pointer to a triangle (edge) object.
    @return Minimal distance squared between the sphere and triangle, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_SP_ClosestSq_ET)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgSPHERE,CPC) ARG2, VEC_OBJ_T(TgETRI,CPC) ARG3 );

/** @brief Calculate the minimal distance squared between a sphere and a triangle, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a sphere object.
    @param [in] ARG3 Pointer to a triangle (edge) object.
    @return Minimal distance squared between the sphere and triangle, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_SP_Closest_ET)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgSPHERE,CPC) ARG2, VEC_OBJ_T(TgETRI,CPC) ARG3 );

/** @brief Calculate the minimal distance squared between a sphere and a triangle, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG4 on ARG3.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the 1st barycentric coordinate of the closest point to ARG3 on ARG4.
    @param [out] OUT2 Pointer to a vector with a full broadcast of the 2nd barycentric coordinate of the closest point to ARG3 on ARG4.
    @param [in] ARG3 Pointer to a sphere object.
    @param [in] ARG4 Pointer to a triangle (edge) object.
    @return Minimal distance squared between the sphere and triangle, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_SP_ClosestSq_PM_ET)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_OBJ_T(TgSPHERE,CPC) ARG3, VEC_OBJ_T(TgETRI,CPC) ARG4 );

/** @brief Calculate the minimal distance squared between a sphere and a triangle, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG4 on ARG3.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the 1st barycentric coordinate of the closest point to ARG3 on ARG4.
    @param [out] OUT2 Pointer to a vector with a full broadcast of the 2nd barycentric coordinate of the closest point to ARG3 on ARG4.
    @param [in] ARG3 Pointer to a sphere object.
    @param [in] ARG4 Pointer to a triangle (edge) object.
    @return Minimal distance squared between the sphere and triangle, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_SP_Closest_PM_ET)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_OBJ_T(TgSPHERE,CPC) ARG3, VEC_OBJ_T(TgETRI,CPC) ARG4 );

/** @brief Determine if the two primitives are intersecting.
    @param [in] ARG0 Pointer to a sphere object.
    @param [in] ARG1 Pointer to a triangle (edge) object.
    @return True if the two primitives are intersecting, and false otherwise. */
TgINLINE TgBOOL
FCN_VO(tgCO_SP_Test_ET)(
    VEC_OBJ_T(TgSPHERE,CPC) ARG0, VEC_OBJ_T(TgETRI,CPC) ARG1 );

/** @brief Update the collision packet with point(s) of penetration between the sphere and a triangle.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG2.
                         Contact normals are the direction for the object at ARG2 to move to achieve separation.
                         Depth values are measured from the surface of the object at ARG1 to the contact point.
    @param [in] ARG1 Pointer to a sphere object.
    @param [in] ARG2 Pointer to a triangle (space) object.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_SP_Penetrate_ST)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgSPHERE,CPC) ARG1, VEC_OBJ_T(TgSTRI,CPC) ARG2 );

/** @brief Update the collision packet with point(s) of penetration between the triangle and a sphere.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG2.
                         Contact normals are the direction for the object at ARG2 to move to achieve separation.
                         Depth values are measured from the surface of the object at ARG1 to the contact point.
    @param [in] ARG1 Pointer to a triangle (space) object.
    @param [in] ARG2 Pointer to a sphere object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_ST_Penetrate_SP)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgSTRI,CPC) ARG1, VEC_OBJ_T(TgSPHERE,CPC) ARG2 );

/** @brief Update the collision packet with the result of sweeping a triangle versus a sphere.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG2.
                         Contact normal is the surface normal at the contact point on ARG2.
    @param [in,out] OUT1 Pointer to a vector with a full broadcast of the normalized time of contact (percentage of time step).
    @param [in] ARG2: Pointer to a sphere object. The test is done inside of this object's reference frame.
    @param [in] ARG3: Pointer to a triangle (space) object.
    @param [in] ARG4 Pointer to an object holding displacement values for ARG3.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_SP_Sweep_ST)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgSPHERE,CPC) ARG2, VEC_OBJ_T(TgSTRI,CPC) ARG3, VEC_OBJ_T(TgDELTA,CPC) ARG4 );


/* ---- Sphere - Sphere ---------------------------------------------------------------------------------------------------------------------------------------------------------- */

/** @brief Calculate the minimal distance squared between a sphere and a sphere.
    @param [in] ARG0 Pointer to a sphere object.
    @param [in] ARG1 Pointer to a sphere object.
    @return Minimal distance squared between the sphere and sphere, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_SP_DistSq_SP)(
    VEC_OBJ_T(TgSPHERE,CPC) ARG0, VEC_OBJ_T(TgSPHERE,CPC) ARG1 );

/** @brief Calculate the minimal distance between a sphere and a sphere.
    @param [in] ARG0 Pointer to a sphere object.
    @param [in] ARG1 Pointer to a sphere object.
    @return Minimal distance between the sphere and sphere, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_SP_Dist_SP)(
    VEC_OBJ_T(TgSPHERE,CPC) ARG0, VEC_OBJ_T(TgSPHERE,CPC) ARG1 );

/** @brief Calculate the minimal distance squared between a sphere and a plane, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a sphere object.
    @param [in] ARG3 Pointer to a sphere object.
    @return Minimal distance squared between the sphere and plane, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_SP_ClosestSq_SP)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgSPHERE,CPC) ARG2, VEC_OBJ_T(TgSPHERE,CPC) ARG3 );

/** @brief Calculate the minimal distance squared between a sphere and a plane, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a sphere object.
    @param [in] ARG3 Pointer to a sphere object.
    @return Minimal distance squared between the sphere and plane, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_SP_Closest_SP)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgSPHERE,CPC) ARG2, VEC_OBJ_T(TgSPHERE,CPC) ARG3 );

/** @brief Determine if the two primitives are intersecting.
    @param [in] ARG0 Pointer to a sphere object.
    @param [in] ARG1 Pointer to a plane object.
    @return True if the two primitives are intersecting, and false otherwise. */
TgINLINE TgBOOL
FCN_VO(tgCO_SP_Test_SP)(
    VEC_OBJ_T(TgSPHERE,CPC) ARG0, VEC_OBJ_T(TgSPHERE,CPC) ARG1 );

/** @brief Determine if the two primitives will touch due to the displacement.
    @param [in] ARG0 Pointer to a sphere object.
    @param [in] ARG1 Pointer to a sphere object.
    @param [in] ARG2 Pointer to an object holding displacement values for ARG1.
    @return True if the two primitives are intersecting, and false otherwise. */
TgINLINE TgBOOL
FCN_VO(tgCO_SP_Test_Sweep_SP)(
    VEC_OBJ_T(TgSPHERE,CPC) ARG0, VEC_OBJ_T(TgSPHERE,CPC) ARG1, VEC_OBJ_T(TgDELTA,CPC) ARG2 );

/** @brief Update the collision packet with point(s) of penetration between the sphere and the sphere.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG2.
                         Contact normals are the direction for the object at ARG2 to move to achieve separation.
                         Depth values are measured from the surface of the object at ARG1 to the contact point.
    @param [in] ARG1 Pointer to a sphere object.
    @param [in] ARG2 Pointer to a sphere object.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_SP_Penetrate_SP)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgSPHERE,CPC) ARG1, VEC_OBJ_T(TgSPHERE,CPC) ARG2 );

/** @brief Update the collision packet with the result of sweeping a sphere versus a sphere.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG2.
                         Contact normal is the surface normal at the contact point on ARG2.
    @param [in,out] OUT1 Pointer to a vector with a full broadcast of the normalized time of contact (percentage of time step).
    @param [in] ARG2: Pointer to a sphere object. The test is done inside of this object's reference frame.
    @param [in] ARG3: Pointer to a sphere object.
    @param [in] ARG4 Pointer to an object holding displacement values for ARG3.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_SP_Sweep_SP)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgSPHERE,CPC) ARG2, VEC_OBJ_T(TgSPHERE,CPC) ARG3, VEC_OBJ_T(TgDELTA,CPC) ARG4 );


/* ---- Sphere Utility ----------------------------------------------------------------------------------------------------------------------------------------------------------- */

/** @brief Clip the two points (treated as a line segment) against the primitive at ARG2.
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point from clipping the segment.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the 2nd point from clipping the segment.
    @param [in] ARG2 Pointer to a sphere object.
    @param [in] ARG3 Vector holding the Segment Origin.
    @param [in] ARG4 Vector holding the position relative to the Segment Origin of the Segment Terminal Point.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_SP_Clip_Points)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgSPHERE,CPC) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4 );

/** @brief Clip the points (treated as a line strip) in the clip list against the primitive at ARG1.
    @param [in,out] OUT0 Pointer to a clip list object.
    @param [in] ARG1 Pointer to a sphere object.
    @return Result code. */
TgEXTN TgRESULT
FCN_VO(tgCO_SP_Clip)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, VEC_OBJ_T(TgSPHERE,CPC) ARG1 );


/** @} TGS_COLLISION_SP */

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

    #define TGS_COLLISION_SPHERE_H

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COLLISION_SPHERE_H) */
#endif
