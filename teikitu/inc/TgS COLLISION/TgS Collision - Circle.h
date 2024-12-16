/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Circle.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_CIRCLE_H)
#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* == Collision ================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions - Scalar Functions                                                                                                                                            */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @addtogroup TGS_COLLISION_CI */
/** @{ */

/* Circle - Point                                                                                                                                                                  */

/** @brief Calculate the minimal distance squared between a circle and a point.
    @param [in] ARG0 Pointer to a circle object.
    @param [in] ARG1 Vector holding a position (point).
    @return Minimal distance squared between a circle and a point, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CI_DistSq_PT)(
    VEC_OBJ_T(TgCIRCLE,CPC) ARG0, VEC_T(1,C) ARG1 );

/** @brief Calculate the minimal distance between a circle and a point.
    @param [in] ARG0 Pointer to a circle object.
    @param [in] ARG1 Vector holding a position (point).
    @return Minimal distance between a circle and a point, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CI_Dist_PT)(
    VEC_OBJ_T(TgCIRCLE,CPC) ARG0, VEC_T(1,C) ARG1 );

/** @brief Calculate the minimal distance squared between a circle and a point, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG2 on ARG1.
    @param [in] ARG1 Pointer to a circle object.
    @param [in] ARG2 Vector holding a position (point).
    @return Minimal distance squared between a circle and a point, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CI_ClosestSq_PT)(
    VEC_T(1,PC) OUT0, VEC_OBJ_T(TgCIRCLE,CPC) ARG1, VEC_T(1,C) ARG2 );

/** @brief Calculate the minimal distance between a circle and a point, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG2 on ARG1.
    @param [in] ARG1 Pointer to a circle object.
    @param [in] ARG2 Vector holding a position (point).
    @return Minimal distance between a circle and a point, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CI_Closest_PT)(
    VEC_T(1,PC) OUT0, VEC_OBJ_T(TgCIRCLE,CPC) ARG1, VEC_T(1,C) ARG2 );


/** @brief Calculate the minimal distance squared between a circle and a point.
    @param [in] ARG0 Vector holding the origin of the circle.
    @param [in] ARG1 Vector holding the normal of the plane containing the circle.
    @param [in] ARG2 Vector holding a full broadcast of the radius of the circle.
    @param [in] ARG3 Vector holding a position (point).
    @return Minimal distance squared between a circle and a point, or zero otherwise, broadcast across all vector lanes. */
TgEXTN VEC_T(1)
FCN_VO(tgCO_CI_ELEM_DistSq_PT)(
    VEC_T(1,C) ARG0, VEC_T(1,C) ARG1, VEC_T(1,C) ARG2, VEC_T(1,C) ARG3 );

/** @brief Calculate the minimal distance squared between a circle and a point.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG4 on the circle.
    @param [in] ARG1 Vector holding the origin of the circle.
    @param [in] ARG2 Vector holding the normal of the plane containing the circle.
    @param [in] ARG3 Vector holding a full broadcast of the radius of the circle.
    @param [in] ARG4 Vector holding a position (point).
    @return Minimal distance squared between a circle and a point, or zero otherwise, broadcast across all vector lanes. */
TgEXTN VEC_T(1)
FCN_VO(tgCO_CI_ELEM_ClosestSq_PT)(
    VEC_T(1,PC) OUT0, VEC_T(1,C) ARG1, VEC_T(1,C) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4 );


/* Circle - Line                                                                                                                                                                   */

/** @brief Calculate the minimal distance squared between a circle and a line.
    @param [in] ARG0 Pointer to a circle object.
    @param [in] ARG1 Pointer to a line object.
    @return Minimal distance squared between a circle and a line, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CI_DistSq_LN)(
    VEC_OBJ_T(TgCIRCLE,CPC) ARG0, VEC_OBJ_T(TgLINE,CPC) ARG1 );

/** @brief Calculate the minimal distance between a circle and a line.
    @param [in] ARG0 Pointer to a circle object.
    @param [in] ARG1 Pointer to a line object.
    @return Minimal distance between a circle and a line, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CI_Dist_LN)(
    VEC_OBJ_T(TgCIRCLE,CPC) ARG0, VEC_OBJ_T(TgLINE,CPC) ARG1 );

/** @brief Calculate the minimal distance squared between a circle and a line, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a circle object.
    @param [in] ARG3 Pointer to a line object.
    @return Minimal distance squared between the circle and line, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CI_ClosestSq_LN)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgCIRCLE,CPC) ARG2, VEC_OBJ_T(TgLINE,CPC) ARG3 );

/** @brief Calculate the minimal distance between a circle and a line, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a circle object.
    @param [in] ARG3 Pointer to a line object.
    @return Minimal distance between the circle and line, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CI_Closest_LN)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgCIRCLE,CPC) ARG2, VEC_OBJ_T(TgLINE,CPC) ARG3 );


/** @brief Calculate the minimal distance squared between a circle and a line, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a circle object.
    @param [in] ARG3 Pointer to a line object.
    @return Minimal distance squared between the circle and line, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CI_ClosestSq_PM_LN)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgCIRCLE,CPC) ARG2, VEC_OBJ_T(TgLINE,CPC) ARG3 );

/** @brief Calculate the minimal distance between a circle and a line, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a circle object.
    @param [in] ARG3 Pointer to a line object.
    @return Minimal distance between the circle and line, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CI_Closest_PM_LN)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgCIRCLE,CPC) ARG2, VEC_OBJ_T(TgLINE,CPC) ARG3 );


/** @brief Calculate the minimal distance squared between a circle and a line, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG2 on {ARG3,ARG4}.
    @param [in] ARG2 Pointer to a circle object.
    @param [in] ARG3 Vector holding the Line Origin.
    @param [in] ARG4 Vector holding the Line Direction.
    @return Minimal distance squared between the circle and line, or zero otherwise, broadcast across all vector lanes. */
TgEXTN VEC_T(1)
FCN_VO(tgCO_CI_ClosestSq_PM_LR00)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgCIRCLE,CPC) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4 );

/** @brief Calculate the minimal distance between a circle and a line, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG2 on {ARG3,ARG4}.
    @param [in] ARG2 Pointer to a circle object.
    @param [in] ARG3 Vector holding the Line Origin.
    @param [in] ARG4 Vector holding the Line Direction.
    @return Minimal distance between the circle and line, or zero otherwise, broadcast across all vector lanes. */
TgEXTN VEC_T(1)
FCN_VO(tgCO_CI_Closest_PM_LR00)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgCIRCLE,CPC) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4 );


/* Circle - Ray                                                                                                                                                                    */

/** @brief Calculate the minimal distance squared between a circle and a ray.
    @param [in] ARG0 Pointer to a circle object.
    @param [in] ARG1 Pointer to a ray object.
    @return Minimal distance squared between a circle and a ray, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CI_DistSq_RY)(
    VEC_OBJ_T(TgCIRCLE,CPC) ARG0, VEC_OBJ_T(TgRAY,CPC) ARG1 );

/** @brief Calculate the minimal distance between a circle and a ray.
    @param [in] ARG0 Pointer to a circle object.
    @param [in] ARG1 Pointer to a ray object.
    @return Minimal distance between a circle and a ray, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CI_Dist_RY)(
    VEC_OBJ_T(TgCIRCLE,CPC) ARG0, VEC_OBJ_T(TgRAY,CPC) ARG1 );

/** @brief Calculate the minimal distance squared between a circle and a ray, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a circle object.
    @param [in] ARG3 Pointer to a ray object.
    @return Minimal distance squared between the circle and ray, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CI_ClosestSq_RY)( 
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgCIRCLE,CPC) ARG2, VEC_OBJ_T(TgRAY,CPC) ARG3 );

/** @brief Calculate the minimal distance between a circle and a ray, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a circle object.
    @param [in] ARG3 Pointer to a ray object.
    @return Minimal distance between the circle and ray, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CI_Closest_RY)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgCIRCLE,CPC) ARG2, VEC_OBJ_T(TgRAY,CPC) ARG3 );


/** @brief Calculate the minimal distance squared between a circle and a ray, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a circle object.
    @param [in] ARG3 Pointer to a ray object.
    @return Minimal distance squared between the circle and ray, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CI_ClosestSq_PM_RY)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgCIRCLE,CPC) ARG2, VEC_OBJ_T(TgRAY,CPC) ARG3 );

/** @brief Calculate the minimal distance between a circle and a ray, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a circle object.
    @param [in] ARG3 Pointer to a ray object.
    @return Minimal distance between the circle and ray, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CI_Closest_PM_RY)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgCIRCLE,CPC) ARG2, VEC_OBJ_T(TgRAY,CPC) ARG3 );


/** @brief Calculate the minimal distance squared between a circle and a ray, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG2 on {ARG3,ARG4}.
    @param [in] ARG2 Pointer to a circle object.
    @param [in] ARG3 Vector holding the Ray Origin.
    @param [in] ARG4 Vector holding the Ray Direction.
    @return Minimal distance squared between the circle and ray, or zero otherwise, broadcast across all vector lanes. */
TgEXTN VEC_T(1)
FCN_VO(tgCO_CI_ClosestSq_PM_LR10)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgCIRCLE,CPC) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4 );

/** @brief Calculate the minimal distance between a circle and a ray, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG2 on {ARG3,ARG4}.
    @param [in] ARG2 Pointer to a circle object.
    @param [in] ARG3 Vector holding the Ray Origin.
    @param [in] ARG4 Vector holding the Ray Direction.
    @return Minimal distance between the circle and ray, or zero otherwise, broadcast across all vector lanes. */
TgEXTN VEC_T(1)
FCN_VO(tgCO_CI_Closest_PM_LR10)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgCIRCLE,CPC) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4 );


/* Circle - Segment                                                                                                                                                                */

/** @brief Calculate the minimal distance squared between a circle and a segment.
    @param [in] ARG0 Pointer to a circle object.
    @param [in] ARG1 Pointer to a segment object.
    @return Minimal distance squared between a circle and a segment, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CI_DistSq_SG)(
    VEC_OBJ_T(TgCIRCLE,CPC) ARG0, VEC_OBJ_T(TgSEGMENT,CPC) ARG1 );

/** @brief Calculate the minimal distance between a circle and a segment.
    @param [in] ARG0 Pointer to a circle object.
    @param [in] ARG1 Pointer to a segment object.
    @return Minimal distance between a circle and a segment, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CI_Dist_SG)(
    VEC_OBJ_T(TgCIRCLE,CPC) ARG0, VEC_OBJ_T(TgSEGMENT,CPC) ARG1 );

/** @brief Calculate the minimal distance squared between a circle and a segment, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a circle object.
    @param [in] ARG3 Pointer to a segment object.
    @return Minimal distance squared between the circle and segment, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CI_ClosestSq_SG)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgCIRCLE,CPC) ARG2, VEC_OBJ_T(TgSEGMENT,CPC) ARG3 );

/** @brief Calculate the minimal distance between a circle and a segment, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a circle object.
    @param [in] ARG3 Pointer to a segment object.
    @return Minimal distance between the circle and segment, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CI_Closest_SG)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgCIRCLE,CPC) ARG2, VEC_OBJ_T(TgSEGMENT,CPC) ARG3 );


/** @brief Calculate the minimal distance squared between a circle and a segment, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a circle object.
    @param [in] ARG3 Pointer to a segment object.
    @return Minimal distance squared between the circle and segment, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CI_ClosestSq_PM_SG)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgCIRCLE,CPC) ARG2, VEC_OBJ_T(TgSEGMENT,CPC) ARG3 );

/** @brief Calculate the minimal distance between a circle and a segment, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a circle object.
    @param [in] ARG3 Pointer to a segment object.
    @return Minimal distance between the circle and segment, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CI_Closest_PM_SG)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgCIRCLE,CPC) ARG2, VEC_OBJ_T(TgSEGMENT,CPC) ARG3 );


/** @brief Calculate the minimal distance squared between a circle and a segment, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG2 on {ARG3,ARG4}.
    @param [in] ARG2 Pointer to a circle object.
    @param [in] ARG3 Vector holding the Segment Origin.
    @param [in] ARG4 Vector holding the position relative to the Segment Origin of the Segment Terminal Point.
    @return Minimal distance squared between the circle and segment, or zero otherwise, broadcast across all vector lanes. */
TgEXTN VEC_T(1)
FCN_VO(tgCO_CI_ClosestSq_PM_LR11)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgCIRCLE,CPC) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4 );

/** @brief Calculate the minimal distance between a circle and a segment, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG2 on {ARG3,ARG4}.
    @param [in] ARG2 Pointer to a circle object.
    @param [in] ARG3 Vector holding the Segment Origin.
    @param [in] ARG4 Vector holding the position relative to the Segment Origin of the Segment Terminal Point.
    @return Minimal distance between the circle and segment, or zero otherwise, broadcast across all vector lanes. */
TgEXTN VEC_T(1)
FCN_VO(tgCO_CI_Closest_PM_LR11)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgCIRCLE,CPC) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4 );


/* Circle - Circle                                                                                                                                                                 */

/** @brief Calculate the minimal distance squared between two circles.
    @param [in] ARG0 Pointer to a circle object.
    @param [in] ARG1 Pointer to a circle object.
    @return Minimal distance squared between a circle and a ray, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CI_DistSq_CI)(
    VEC_OBJ_T(TgCIRCLE,CPC) ARG0, VEC_OBJ_T(TgCIRCLE,CPC) ARG1 );

/** @brief Calculate the minimal distance between a circle and a ray.
    @param [in] ARG0 Pointer to a circle object.
    @param [in] ARG1 Pointer to a circle object.
    @return Minimal distance between a circle and a ray, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CI_Dist_CI)(
    VEC_OBJ_T(TgCIRCLE,CPC) ARG0, VEC_OBJ_T(TgCIRCLE,CPC) ARG1 );

/** @brief Calculate the minimal distance squared between a circle and a ray, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a circle object.
    @param [in] ARG3 Pointer to a circle object.
    @return Minimal distance squared between the circle and ray, or zero otherwise, broadcast across all vector lanes. */
TgEXTN VEC_T(1)
FCN_VO(tgCO_CI_ClosestSq_CI)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgCIRCLE,CPC) ARG2, VEC_OBJ_T(TgCIRCLE,CPC) ARG3 );

/** @brief Calculate the minimal distance between a circle and a ray, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a circle object.
    @param [in] ARG3 Pointer to a circle object.
    @return Minimal distance between the circle and ray, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_CI_Closest_CI)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgCIRCLE,CPC) ARG2, VEC_OBJ_T(TgCIRCLE,CPC) ARG3 );


/** @brief Calculate the minimal distance squared between two circles.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the angle for the closest point to ARG2 on the circle ARG1.
    @param [in] ARG1 Pointer to a circle object.
    @param [in] ARG2 Pointer to a circle object.
    @return Minimal distance squared between a circle and a ray, or zero otherwise, broadcast across all vector lanes. */
TgEXTN VEC_T(1)
FCN_VO(tgCO_CI_ClosestSq_PM_CI)( 
    VEC_T(1,PC) OUT0, VEC_OBJ_T(TgCIRCLE,CPC) ARG1, VEC_OBJ_T(TgCIRCLE,CPC) ARG2 );

/** @brief Calculate the minimal distance squared between two circles (assume they are co-planar).
    @param [out] OUT0 Pointer to a vector holding the 1st point of intersection.
    @param [out] OUT1 Pointer to a vector holding the 2nd point of intersection. 
    @param [in] ARG2 Pointer to a circle object.
    @param [in] ARG3 Pointer to a circle object.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_CI_Intersect2D_CI)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgCIRCLE,CPC) ARG2, VEC_OBJ_T(TgCIRCLE,CPC) ARG3 );


/* Circle - Triangle                                                                                                                                                               */

/** @brief Update the collision packet with point(s) of penetration between a circle and a circle.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG2.
                         Contact normals are the direction for the object at ARG2 to move to achieve separation.
                         Depth values are measured from the surface of the object at ARG1 to the contact point.
    @param [in] ARG1 Pointer to a triangle (space) object.
    @param [in] ARG2 Pointer to a circle object.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_ST_Penetrate_CI)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgSTRI,CPC) ARG1, VEC_OBJ_T(TgCIRCLE,CPC) ARG2 );


/** @} TGS_COLLISION_CI */

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

    #define TGS_COLLISION_CIRCLE_H

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COLLISION_CIRCLE_H) */
#endif
