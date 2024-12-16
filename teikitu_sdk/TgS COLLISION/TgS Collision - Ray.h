/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Ray.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_RAY_H)
#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* == Collision ================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions - Scalar Functions                                                                                                                                            */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @addtogroup TGS_COLLISION_RY */
/** @{ */

/* Ray - Point                                                                                                                                                                     */

/** @brief Calculate the minimal distance squared between a ray and a point.
    @param [in] ARG0 Pointer to a ray object.
    @param [in] ARG1 Vector holding a position (point).
    @return Minimal distance squared between the ray and point, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_RY_DistSq_PT)(
    VEC_OBJ_T(TgRAY,CPC) ARG0, VEC_T(1,C) ARG1 );

/** @brief Calculate the minimal distance between a ray and a point.
    @param [in] ARG0 Pointer to a ray object.
    @param [in] ARG1 Vector holding a position (point).
    @return Minimal distance between the ray and point, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_RY_Dist_PT)(
    VEC_OBJ_T(TgRAY,CPC) ARG0, VEC_T(1,C) ARG1 );

/** @brief Calculate the minimal distance squared between a ray and a point, and store the location on the ray closest to the point.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG2 on ARG1.
    @param [in] ARG1 Pointer to a ray object.
    @param [in] ARG2 Vector holding a position (point).
    @return Minimal distance squared between the ray and point, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_RY_ClosestSq_PT)(
    VEC_T(1,PC) OUT0, VEC_OBJ_T(TgRAY,CPC) ARG1, VEC_T(1,C) ARG2 );

/** @brief Calculate the minimal distance between a ray and a point, and store the location on the ray closest to the point.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG2 on ARG1.
    @param [in] ARG1 Pointer to a ray object.
    @param [in] ARG2 Vector holding a position (point).
    @return Minimal distance between the ray and point, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_RY_Closest_PT)(
    VEC_T(1,PC) OUT0, VEC_OBJ_T(TgRAY,CPC) ARG1, VEC_T(1,C) ARG2 );

/** @brief Calculate the minimal distance squared between a ray and a point, and store the location on the ray closest to the point.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on {ARG1,ARG2}.
    @param [in] ARG1 Vector holding the Ray Origin.
    @param [in] ARG2 Vector holding the Ray Direction.
    @param [in] ARG3 Vector holding a position (point).
    @return Minimal distance squared between the ray and point, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_LR10_ClosestSq_PT)(
    VEC_T(1,PC) OUT0, VEC_T(1,C) ARG1, VEC_T(1,C) ARG2, VEC_T(1,C) ARG3 );

/** @brief Calculate the minimal distance squared between a ray and a point, and store the location on the ray closest to the point.
    @param [out] OUT0 Pointer to a vector with a broadcast of the parametric value for closest point to ARG2 on ARG1.
    @param [in] ARG1 Pointer to a ray object.
    @param [in] ARG2 Vector holding a position (point).
    @return Minimal distance squared between the ray and point, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_RY_ClosestSq_PM_PT)(
    VEC_T(1,PC) OUT0, VEC_OBJ_T(TgRAY,CPC) ARG1, VEC_T(1,C) ARG2 );

/** @brief Calculate the minimal distance between a ray and a point, and store the location on the ray closest to the point.
    @param [out] OUT0 Pointer to a vector with a broadcast of the parametric value for closest point to ARG2 on ARG1.
    @param [in] ARG1 Pointer to a ray object.
    @param [in] ARG2 Vector holding a position (point).
    @return Minimal distance between the ray and point, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_RY_Closest_PM_PT)(
    VEC_T(1,PC) OUT0, VEC_OBJ_T(TgRAY,CPC) ARG1, VEC_T(1,C) ARG2 );

/** @brief Calculate the minimal distance squared between a ray and a point, and store the location on the ray closest to the point.
    @param [out] OUT0 Pointer to a vector with a broadcast of the parametric value for closest point to ARG3 on {ARG1,ARG2}.
    @param [in] ARG1 Vector holding the Ray Origin.
    @param [in] ARG2 Vector holding the Ray Direction.
    @param [in] ARG3 Vector holding a position (point).
    @return Minimal distance squared between the ray and point, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_LR10_ClosestSq_PM_PT)(
    VEC_T(1,PC) OUT0, VEC_T(1,C) ARG1, VEC_T(1,C) ARG2, VEC_T(1,C) ARG3 );


/* Ray - Line                                                                                                                                                                      */

/** @brief Calculate the minimal distance squared between a ray and a line.
    @param [in] ARG0 Pointer to a ray object.
    @param [in] ARG1 Pointer to a line object.
    @return Minimal distance squared between a ray and a line, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_RY_DistSq_LN)(
    VEC_OBJ_T(TgRAY,CPC) ARG0, VEC_OBJ_T(TgLINE,CPC) ARG1 );

/** @brief Calculate the minimal distance between a ray and a line.
    @param [in] ARG0 Pointer to a ray object.
    @param [in] ARG1 Pointer to a line object.
    @return Minimal distance between a ray and a line, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_RY_Dist_LN)(
    VEC_OBJ_T(TgRAY,CPC) ARG0, VEC_OBJ_T(TgLINE,CPC) ARG1 );

/** @brief Calculate the minimal distance squared between a ray and a line, and store the closest points on each primitive.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a ray object.
    @param [in] ARG3 Pointer to a line object.
    @return Minimal distance squared between the ray and line, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_RY_ClosestSq_LN)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgRAY,CPC) ARG2, VEC_OBJ_T(TgLINE,CPC) ARG3 );

/** @brief Calculate the minimal distance between a ray and a line, and store the closest points on each primitive.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a ray object.
    @param [in] ARG3 Pointer to a line object.
    @return Minimal distance between the ray and line, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_RY_Closest_LN)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgRAY,CPC) ARG2, VEC_OBJ_T(TgLINE,CPC) ARG3 );

/** @brief Calculate the minimal distance squared between a ray and a line, and store the closest points on each primitive.
    @param [out] OUT0 Pointer to a vector holding the closest point to {ARG4,ARG5} on {ARG2,ARG3}.
    @param [out] OUT1 Pointer to a vector holding the closest point to {ARG2,ARG3} on {ARG4,ARG5}.
    @param [in] ARG2 Vector holding the Ray Origin.
    @param [in] ARG3 Vector holding the Ray Direction.
    @param [in] ARG4 Vector holding the Line Origin.
    @param [in] ARG5 Vector holding the Line Direction.
    @return Minimal distance squared between the ray and line, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_LR10_ClosestSq_LR00)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,C) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4, VEC_T(1,C) ARG5 );

/** @brief Calculate the minimal distance squared between a ray and a line, and store the closest points on each primitive.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG3 and ARG2.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG3 and ARG2.
    @param [in] ARG2 Pointer to a ray object.
    @param [in] ARG3 Pointer to a line object.
    @return Minimal distance squared between the ray and line, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_RY_ClosestSq_PM_LN)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgRAY,CPC) ARG2, VEC_OBJ_T(TgLINE,CPC) ARG3 );

/** @brief Calculate the minimal distance between a ray and a line, and store the closest points on each primitive.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG3 and ARG2.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG3 and ARG2.
    @param [in] ARG2 Pointer to a ray object.
    @param [in] ARG3 Pointer to a line object.
    @return Minimal distance between the ray and line, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_RY_Closest_PM_LN)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgRAY,CPC) ARG2, VEC_OBJ_T(TgLINE,CPC) ARG3 );

/** @brief Calculate the minimal distance squared between a ray and a line, and store the parametric value for the closest points on each primitive.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the parametric value for the closest point to {ARG4,ARG5} on {ARG2,ARG3}.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the parametric value for the closest point to {ARG2,ARG3} on {ARG4,ARG5}.
    @param [in] ARG2 Vector holding the Ray Origin.
    @param [in] ARG3 Vector holding the Ray Direction.
    @param [in] ARG4 Vector holding the Line Origin.
    @param [in] ARG5 Vector holding the Line Direction.
    @return Minimal distance squared between the ray and line, or zero otherwise, broadcast across all vector lanes. */
TgEXTN VEC_T(1)
FCN_VO(tgCO_LR10_ClosestSq_PM_LR00)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,C) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4, VEC_T(1,C) ARG5 );

/** @brief Determine if the ray and line intersect.
    @param [in] ARG0 Pointer to a ray object.
    @param [in] ARG1 Pointer to a line object.
    @return True if the primitives intersect and false otherwise. */
TgINLINE TgBOOL
FCN_VO(tgCO_RY_Test_LN)(
    VEC_OBJ_T(TgRAY,CPC), VEC_OBJ_T(TgLINE,CPC) );


/* Ray - Ray                                                                                                                                                                       */

/** @brief Calculate the minimal distance squared between a ray and a ray.
    @param [in] ARG0 Pointer to a ray object.
    @param [in] ARG1 Pointer to a ray object.
    @return Minimal distance squared between a ray and a ray, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_RY_DistSq_RY)(
    VEC_OBJ_T(TgRAY,CPC), VEC_OBJ_T(TgRAY,CPC) );

/** @brief Calculate the minimal distance between a ray and a ray.
    @param [in] ARG0 Pointer to a ray object.
    @param [in] ARG1 Pointer to a ray object.
    @return Minimal distance between a ray and a ray, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_RY_Dist_RY)(
    VEC_OBJ_T(TgRAY,CPC), VEC_OBJ_T(TgRAY,CPC) );

/** @brief Calculate the minimal distance squared between a ray and a ray, and store the closest points on each primitive.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a ray object.
    @param [in] ARG3 Pointer to a ray object.
    @return Minimal distance squared between the ray and ray, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_RY_ClosestSq_RY)(
    VEC_T(1,PC), VEC_T(1,PC), VEC_OBJ_T(TgRAY,CPC), VEC_OBJ_T(TgRAY,CPC) );

/** @brief Calculate the minimal distance between a ray and a ray, and store the closest points on each primitive.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a ray object.
    @param [in] ARG3 Pointer to a ray object.
    @return Minimal distance between the ray and ray, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_RY_Closest_RY)(
    VEC_T(1,PC), VEC_T(1,PC), VEC_OBJ_T(TgRAY,CPC), VEC_OBJ_T(TgRAY,CPC) );

/** @brief Calculate the minimal distance squared between a ray and a ray, and store the closest points on each primitive.
    @param [out] OUT0 Pointer to a vector holding the closest point to {ARG4,ARG5} on {ARG2,ARG3}.
    @param [out] OUT1 Pointer to a vector holding the closest point to {ARG2,ARG3} on {ARG4,ARG5}.
    @param [in] ARG2 Vector holding the Ray Origin.
    @param [in] ARG3 Vector holding the Ray Direction.
    @param [in] ARG4 Vector holding the Ray Origin.
    @param [in] ARG5 Vector holding the Ray Direction.
    @return Minimal distance squared between the ray and ray, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_LR10_ClosestSq_LR10)(
    VEC_T(1,PC) , VEC_T(1,PC) , VEC_T(1,C), VEC_T(1,C), VEC_T(1,C), VEC_T(1,C) );

/** @brief Calculate the minimal distance squared between a ray and a ray, and store the closest points on each primitive.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG3 and ARG2.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG3 and ARG2.
    @param [in] ARG2 Pointer to a ray object.
    @param [in] ARG3 Pointer to a ray object.
    @return Minimal distance squared between the ray and ray, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_RY_ClosestSq_PM_RY)(
    VEC_T(1,PC) , VEC_T(1,PC) , VEC_OBJ_T(TgRAY,CPC), VEC_OBJ_T(TgRAY,CPC) );

/** @brief Calculate the minimal distance between a ray and a ray, and store the closest points on each primitive.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG3 and ARG2.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG3 and ARG2.
    @param [in] ARG2 Pointer to a ray object.
    @param [in] ARG3 Pointer to a ray object.
    @return Minimal distance between the ray and ray, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_RY_Closest_PM_RY)(
    VEC_T(1,PC) , VEC_T(1,PC) , VEC_OBJ_T(TgRAY,CPC), VEC_OBJ_T(TgRAY,CPC) );

/** @brief Calculate the minimal distance squared between a ray and a ray, and store the parametric value for the closest points on each primitive.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the parametric value for the closest point to {ARG4,ARG5} on {ARG2,ARG3}.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the parametric value for the closest point to {ARG2,ARG3} on {ARG4,ARG5}.
    @param [in] ARG2 Vector holding the Ray Origin.
    @param [in] ARG3 Vector holding the Ray Direction.
    @param [in] ARG4 Vector holding the Ray Origin.
    @param [in] ARG5 Vector holding the Ray Direction.
    @return Minimal distance squared between the ray and ray, or zero otherwise, broadcast across all vector lanes. */
TgEXTN VEC_T(1)
FCN_VO(tgCO_LR10_ClosestSq_PM_LR10)(
    VEC_T(1,PC) , VEC_T(1,PC) , VEC_T(1,C), VEC_T(1,C), VEC_T(1,C), VEC_T(1,C) );

/** @brief Determine if the ray and ray intersect.
    @param [in] ARG0 Pointer to a ray object.
    @param [in] ARG1 Pointer to a ray object.
    @return True if the primitives intersect and false otherwise. */
TgINLINE TgBOOL
FCN_VO(tgCO_RY_Test_RY)(
    VEC_OBJ_T(TgRAY,CPC), VEC_OBJ_T(TgRAY,CPC) );


/* Ray - Segment                                                                                                                                                                   */

/** @brief Calculate the minimal distance squared between a ray and a segment.
    @param [in] ARG0 Pointer to a ray object.
    @param [in] ARG1 Pointer to a segment object.
    @return Minimal distance squared between a ray and a segment, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_RY_DistSq_SG)(
    VEC_OBJ_T(TgRAY,CPC), VEC_OBJ_T(TgSEGMENT,CPC) );

/** @brief Calculate the minimal distance between a ray and a segment.
    @param [in] ARG0 Pointer to a ray object.
    @param [in] ARG1 Pointer to a segment object.
    @return Minimal distance between a ray and a segment, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_RY_Dist_SG)(
    VEC_OBJ_T(TgRAY,CPC), VEC_OBJ_T(TgSEGMENT,CPC) );

/** @brief Calculate the minimal distance squared between a ray and a segment, and store the closest points on each primitive.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a ray object.
    @param [in] ARG3 Pointer to a segment object.
    @return Minimal distance squared between the ray and segment, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_RY_ClosestSq_SG)(
    VEC_T(1,PC), VEC_T(1,PC), VEC_OBJ_T(TgRAY,CPC), VEC_OBJ_T(TgSEGMENT,CPC) );

/** @brief Calculate the minimal distance between a ray and a segment, and store the closest points on each primitive.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a ray object.
    @param [in] ARG3 Pointer to a segment object.
    @return Minimal distance between the ray and segment, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_RY_Closest_SG)(
    VEC_T(1,PC), VEC_T(1,PC), VEC_OBJ_T(TgRAY,CPC), VEC_OBJ_T(TgSEGMENT,CPC) );

/** @brief Calculate the minimal distance squared between a ray and a segment, and store the closest points on each primitive.
    @param [out] OUT0 Pointer to a vector holding the closest point to {ARG4,ARG5} on {ARG2,ARG3}.
    @param [out] OUT1 Pointer to a vector holding the closest point to {ARG2,ARG3} on {ARG4,ARG5}.
    @param [in] ARG2 Vector holding the Ray Origin.
    @param [in] ARG3 Vector holding the Ray Direction.
    @param [in] ARG4 Vector holding the Segment Origin.
    @param [in] ARG5 Vector holding the position relative to the Segment Origin of the Segment Terminal Point.
    @return Minimal distance squared between the ray and segment, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_LR10_ClosestSq_LR11)(
    VEC_T(1,PC) , VEC_T(1,PC) , VEC_T(1,C), VEC_T(1,C), VEC_T(1,C), VEC_T(1,C) );

/** @brief Calculate the minimal distance squared between a ray and a segment, and store the closest points on each primitive.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG3 and ARG2.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG3 and ARG2.
    @param [in] ARG2 Pointer to a ray object.
    @param [in] ARG3 Pointer to a segment object.
    @return Minimal distance squared between the ray and segment, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_RY_ClosestSq_PM_SG)(
    VEC_T(1,PC) , VEC_T(1,PC) , VEC_OBJ_T(TgRAY,CPC), VEC_OBJ_T(TgSEGMENT,CPC) );

/** @brief Calculate the minimal distance between a ray and a segment, and store the closest points on each primitive.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG3 and ARG2.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG3 and ARG2.
    @param [in] ARG2 Pointer to a ray object.
    @param [in] ARG3 Pointer to a segment object.
    @return Minimal distance between the ray and segment, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_RY_Closest_PM_SG)(
    VEC_T(1,PC) , VEC_T(1,PC) , VEC_OBJ_T(TgRAY,CPC), VEC_OBJ_T(TgSEGMENT,CPC) );

/** @brief Calculate the minimal distance squared between a ray and a segment, and store the parametric value for the closest points on each primitive.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the parametric value for the closest point to {ARG4,ARG5} on {ARG2,ARG3}.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the parametric value for the closest point to {ARG2,ARG3} on {ARG4,ARG5}.
    @param [in] ARG2 Vector holding the Ray Origin.
    @param [in] ARG3 Vector holding the Ray Direction.
    @param [in] ARG4 Vector holding the Segment Origin.
    @param [in] ARG5 Vector holding the position relative to the Segment Origin of the Segment Terminal Point.
    @return Minimal distance squared between the ray and segment, or zero otherwise, broadcast across all vector lanes. */
TgEXTN VEC_T(1)
FCN_VO(tgCO_LR10_ClosestSq_PM_LR11)(
    VEC_T(1,PC) , VEC_T(1,PC) , VEC_T(1,C), VEC_T(1,C), VEC_T(1,C), VEC_T(1,C) );

/** @brief Determine if the ray and segment intersect.
    @param [in] ARG0 Pointer to a ray object.
    @param [in] ARG1 Pointer to a segment object.
    @return True if the primitives intersect and false otherwise. */
TgINLINE TgBOOL
FCN_VO(tgCO_RY_Test_SG)(
    VEC_OBJ_T(TgRAY,CPC), VEC_OBJ_T(TgSEGMENT,CPC) );


/** @} TGS_COLLISION_RY */

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

    #define TGS_COLLISION_RAY_H

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COLLISION_RAY_H) */
#endif
