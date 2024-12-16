/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Box.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_BOX_H)
#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* == Collision ================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @addtogroup TGS_COLLISION_BX */
/** @{ */

/* Box - Point                                                                                                                                                                     */

/** @brief Calculate the minimal distance squared between a box and a point.
    @param [in] ARG0 Pointer to a box object.
    @param [in] ARG1 Vector holding a position (point).
    @return Minimal distance squared between the box and point, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_BX_DistSq_PT)(
    VEC_OBJ_T(TgBOX,CPC) ARG0, VEC_T(1,C) ARG1 );

/** @brief Calculate the minimal distance between a box and a point.
    @param [in] ARG0 Pointer to a box object.
    @param [in] ARG1 Vector holding a position (point).
    @return Minimal distance between the box and point, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_BX_Dist_PT)(
    VEC_OBJ_T(TgBOX,CPC) NONULLARG0, VEC_T(1,C) ARG1 );

/** @brief Calculate the minimal distance squared between a box and a point, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG2 on ARG1.
    @param [in] ARG1 Pointer to a box object.
    @param [in] ARG2 Vector holding a position (point).
    @return Minimal distance squared between the box and point, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_BX_ClosestSq_PT)(
    VEC_T(1,PC) OUT0, VEC_OBJ_T(TgBOX,CPC) ARG1, VEC_T(1,C) ARG2 );

/** @brief Calculate the minimal distance between a box and a point, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG2 on ARG1.
    @param [in] ARG1 Pointer to a box object.
    @param [in] ARG2 Vector holding a position (point).
    @return Minimal distance between the box and point, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_BX_Closest_PT)(
    VEC_T(1,PC) OUT0, VEC_OBJ_T(TgBOX,CPC) ARG1, VEC_T(1,C) ARG2 );


/** @brief Calculate the minimal distance squared between a box and a point, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG4 along the 1st axis of ARG3.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG4 along the 2nd axis of ARG3.
    @param [out] OUT2 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG4 along the 3rd axis of ARG3.
    @param [in] ARG3 Pointer to a box object.
    @param [in] ARG4 Vector holding a position (point).
    @return Minimal distance squared between the box and point, or zero otherwise, broadcast across all vector lanes. */
TgEXTN VEC_T(1)
FCN_VO(tgCO_BX_ClosestSq_PM_PT)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_OBJ_T(TgBOX,CPC) ARG3, VEC_T(1,C) ARG4 );

/** @brief Calculate the minimal distance between a box and a point, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG4 along the 1st axis of ARG3.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG4 along the 2nd axis of ARG3.
    @param [out] OUT2 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG4 along the 3rd axis of ARG3.
    @param [in] ARG3 Pointer to a box object.
    @param [in] ARG4 Vector holding a position (point).
    @return Minimal distance between the box and point, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_BX_Closest_PM_PT)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_OBJ_T(TgBOX,CPC) ARG3, VEC_T(1,C) ARG4 );



/* Box - Line                                                                                                                                                                      */

/** @brief Calculate the minimal distance squared between a box and a line.
    @param [in] ARG0 Pointer to a box object.
    @param [in] ARG1 Pointer to a line object.
    @return Minimal distance squared between a box and a line, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_BX_DistSq_LN)(
    VEC_OBJ_T(TgBOX,CPC) ARG0, VEC_OBJ_T(TgLINE,CPC) ARG1 );

/** @brief Calculate the minimal distance between a box and a line.
    @param [in] ARG0 Pointer to a box object.
    @param [in] ARG1 Pointer to a line object.
    @return Minimal distance between a box and a line, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_BX_Dist_LN)(
    VEC_OBJ_T(TgBOX,CPC) ARG0, VEC_OBJ_T(TgLINE,CPC) ARG1 );

/** @brief Calculate the minimal distance squared between a box and a line, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a box object.
    @param [in] ARG3 Pointer to a line object.
    @return Minimal distance squared between the box and line, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_BX_ClosestSq_LN)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgBOX,CPC) ARG2, VEC_OBJ_T(TgLINE,CPC) ARG3 );

/** @brief Calculate the minimal distance between a box and a line, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a box object.
    @param [in] ARG3 Pointer to a line object.
    @return Minimal distance between the box and line, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_BX_Closest_LN)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgBOX,CPC) ARG2, VEC_OBJ_T(TgLINE,CPC) ARG3 );


/** @brief Calculate the minimal distance squared between a box and a line, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG5 along the 1st axis of ARG4.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG5 along the 2nd axis of ARG4.
    @param [out] OUT2 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG5 along the 3rd axis of ARG4.
    @param [out] OUT3 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG4 along ARG5.
    @param [in] ARG4 Pointer to a box object.
    @param [in] ARG5 Pointer to a line object.
    @return Minimal distance squared between the box and line, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_BX_ClosestSq_PM_LN)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_T(1,PC) OUT3, VEC_OBJ_T(TgBOX,CPC) ARG4, VEC_OBJ_T(TgLINE,CPC) ARG5 );

/** @brief Calculate the minimal distance between a box and a line, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG5 along the 1st axis of ARG4.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG5 along the 2nd axis of ARG4.
    @param [out] OUT2 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG5 along the 3rd axis of ARG4.
    @param [out] OUT3 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG4 along ARG5.
    @param [in] ARG4 Pointer to a box object.
    @param [in] ARG5 Pointer to a line object.
    @return Minimal distance between the box and line, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_BX_Closest_PM_LN)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_T(1,PC) OUT3, VEC_OBJ_T(TgBOX,CPC) ARG4, VEC_OBJ_T(TgLINE,CPC) ARG5 );

/** @brief Calculate the minimal distance between a box and a line, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the parametric value for the closest point to {ARG5,ARG6} along the 1st axis of ARG4.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the parametric value for the closest point to {ARG5,ARG6} along the 2nd axis of ARG4.
    @param [out] OUT2 Pointer to a vector with a full broadcast of the parametric value for the closest point to {ARG5,ARG6} along the 3rd axis of ARG4.
    @param [out] OUT3 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG4 along {ARG5,ARG6}.
    @param [in] ARG4 Pointer to a box object.
    @param [in] ARG5 Vector holding the Line Origin.
    @param [in] ARG6 Vector holding the Line Direction.
    @return Minimal distance between the box and line, or zero otherwise, broadcast across all vector lanes. */
TgEXTN VEC_T(1)
FCN_VO(tgCO_BX_ClosestSq_PM_LR00)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_T(1,PC) OUT3, VEC_OBJ_T(TgBOX,CPC) ARG4, VEC_T(1,C) ARG5, VEC_T(1,C) ARG6 );

/** @brief Calculate the minimal distance between a box and a line, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the parametric value for the closest point to {ARG5,ARG6} along the 1st axis of ARG4.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the parametric value for the closest point to {ARG5,ARG6} along the 2nd axis of ARG4.
    @param [out] OUT2 Pointer to a vector with a full broadcast of the parametric value for the closest point to {ARG5,ARG6} along the 3rd axis of ARG4.
    @param [out] OUT3 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG4 along {ARG5,ARG6}.
    @param [in] ARG4 Pointer to a box object.
    @param [in] ARG5 Vector holding the Line Origin.
    @param [in] ARG6 Vector holding the Line Direction.
    @return Minimal distance between the box and line, or zero otherwise, broadcast across all vector lanes. */
TgEXTN VEC_T(1)
FCN_VO(tgCO_BX_Closest_PM_LR00)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_T(1,PC) OUT3, VEC_OBJ_T(TgBOX,CPC) ARG4, VEC_T(1,C) ARG5, VEC_T(1,C) ARG6 );


/** @brief Output the sequence of points created by clipping the line to the indexed face (assuming an infinite projection along the face normal).
    @param [out] OUT0 Pointer to a clip list object, where the resulting points are stored.
    @param [in] ARG1 Pointer to a box object.
    @param [in] ARG2 Integer index to select which face (assuming an infinite projection along the face normal) to use for the clipping operation.
    @param [in] ARG3 Pointer to a line object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_BXF_Clip_LN)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, VEC_OBJ_T(TgBOX,CPC) ARG1, TgSINT_E32_C ARG2, VEC_OBJ_T(TgLINE,CPC) ARG3 );

/** @brief Output the sequence of points created by clipping the line to the interior of the box.
    @param [out] OUT0 Pointer to a clip list object, where the resulting points are stored.
    @param [in] ARG1 Pointer to a box object.
    @param [in] ARG2 Pointer to a line object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_BX_Clip_LN)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, VEC_OBJ_T(TgBOX,CPC) ARG1, VEC_OBJ_T(TgLINE,CPC) ARG2 );

/** @brief Output the sequence of points created by clipping the line to the indexed face (assuming an infinite projection along the face normal).
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point from clipping the line.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the 2nd point from clipping the line.
    @param [in] ARG2 Pointer to a box object.
    @param [in] ARG3 Integer index to select which face (assuming an infinite projection along the face normal) to use for the clipping operation.
    @param [in] ARG4 Pointer to a line object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_BXF_Clip_PM_LN)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgBOX,CPC) ARG2, TgSINT_E32_C ARG3, VEC_OBJ_T(TgLINE,CPC) ARG4 );

/** @brief Output the sequence of points created by clipping the line to the interior of the box.
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point from clipping the line.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the 2nd point from clipping the line.
    @param [in] ARG2 Pointer to a box object.
    @param [in] ARG3 Pointer to a line object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_BX_Clip_PM_LN)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgBOX,CPC) ARG2, VEC_OBJ_T(TgLINE,CPC) ARG3 );


/** @brief Output the sequence of points created by clipping the line to the indexed face (assuming an infinite projection along the face normal).
    @param [out] OUT0 Pointer to a clip list object, where the resulting points are stored.
    @param [in] ARG1 Pointer to a box object.
    @param [in] ARG2 Integer index to select which face (assuming an infinite projection along the face normal) to use for the clipping operation.
    @param [in] ARG3 Vector holding the Line Origin.
    @param [in] ARG4 Vector holding the Line Direction.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_BXF_Clip_LR00)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, VEC_OBJ_T(TgBOX,CPC) ARG1, TgSINT_E32_C ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4 );

/** @brief Output the sequence of points created by clipping the line to the interior of the box.
    @param [out] OUT0 Pointer to a clip list object, where the resulting points are stored.
    @param [in] ARG1 Pointer to a box object.
    @param [in] ARG2 Vector holding the Line Origin.
    @param [in] ARG3 Vector holding the Line Direction.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_BX_Clip_LR00)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, VEC_OBJ_T(TgBOX,CPC) ARG1, VEC_T(1,C) ARG2, VEC_T(1,C) ARG3 );

/** @brief Output the sequence of points created by clipping the line to the indexed face (assuming an infinite projection along the face normal).
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point from clipping the line.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the 2nd point from clipping the line.
    @param [in] ARG2 Pointer to a box object.
    @param [in] ARG3 Integer index to select which face (assuming an infinite projection along the face normal) to use for the clipping operation.
    @param [in] ARG4 Vector holding the Line Origin.
    @param [in] ARG5 Vector holding the Line Direction.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_BXF_Clip_PM_LR00)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgBOX,CPC) ARG2, TgSINT_E32_C ARG3, VEC_T(1,C) ARG4, VEC_T(1,C) ARG5 );

/** @brief Output the sequence of points created by clipping the line to the interior of the box.
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point from clipping the line.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the 2nd point from clipping the line.
    @param [in] ARG2 Pointer to a box object.
    @param [in] ARG3 Vector holding the Line Origin.
    @param [in] ARG4 Vector holding the Line Direction.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_BX_Clip_PM_LR00)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgBOX,CPC) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4 );



/* Box - Ray                                                                                                                                                                       */

/** @brief Calculate the minimal distance squared between a box and a ray.
    @param [in] ARG0 Pointer to a box object.
    @param [in] ARG1 Pointer to a ray object.
    @return Minimal distance squared between a box and a ray, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_BX_DistSq_RY)(
    VEC_OBJ_T(TgBOX,CPC) ARG0, VEC_OBJ_T(TgRAY,CPC) ARG1 );

/** @brief Calculate the minimal distance between a box and a ray.
    @param [in] ARG0 Pointer to a box object.
    @param [in] ARG1 Pointer to a ray object.
    @return Minimal distance between a box and a ray, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_BX_Dist_RY)(
    VEC_OBJ_T(TgBOX,CPC) ARG0, VEC_OBJ_T(TgRAY,CPC) ARG1 );

/** @brief Calculate the minimal distance squared between a box and a ray, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a box object.
    @param [in] ARG3 Pointer to a ray object.
    @return Minimal distance squared between the box and ray, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_BX_ClosestSq_RY)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgBOX,CPC) ARG2, VEC_OBJ_T(TgRAY,CPC) ARG3 );

/** @brief Calculate the minimal distance between a box and a ray, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a box object.
    @param [in] ARG3 Pointer to a ray object.
    @return Minimal distance between the box and ray, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_BX_Closest_RY)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgBOX,CPC) ARG2, VEC_OBJ_T(TgRAY,CPC) ARG3 );


/** @brief Calculate the minimal distance squared between a box and a ray, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG5 along the 1st axis of ARG4.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG5 along the 2nd axis of ARG4.
    @param [out] OUT2 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG5 along the 3rd axis of ARG4.
    @param [out] OUT3 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG4 along ARG5.
    @param [in] ARG4 Pointer to a box object.
    @param [in] ARG5 Pointer to a ray object.
    @return Minimal distance squared between the box and ray, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_BX_ClosestSq_PM_RY)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_T(1,PC) OUT3, VEC_OBJ_T(TgBOX,CPC) ARG4, VEC_OBJ_T(TgRAY,CPC) ARG5 );

/** @brief Calculate the minimal distance between a box and a ray, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG5 along the 1st axis of ARG4.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG5 along the 2nd axis of ARG4.
    @param [out] OUT2 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG5 along the 3rd axis of ARG4.
    @param [out] OUT3 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG4 along ARG5.
    @param [in] ARG4 Pointer to a box object.
    @param [in] ARG5 Pointer to a ray object.
    @return Minimal distance between the box and ray, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_BX_Closest_PM_RY)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_T(1,PC) OUT3, VEC_OBJ_T(TgBOX,CPC) ARG4, VEC_OBJ_T(TgRAY,CPC) ARG5 );

/** @brief Calculate the minimal distance between a box and a line, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the parametric value for the closest point to {ARG5,ARG6} along the 1st axis of ARG4.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the parametric value for the closest point to {ARG5,ARG6} along the 2nd axis of ARG4.
    @param [out] OUT2 Pointer to a vector with a full broadcast of the parametric value for the closest point to {ARG5,ARG6} along the 3rd axis of ARG4.
    @param [out] OUT3 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG4 along {ARG5,ARG6}.
    @param [in] ARG4 Pointer to a box object.
    @param [in] ARG5 Vector holding the Ray Origin.
    @param [in] ARG6 Vector holding the Ray Direction.
    @return Minimal distance between the box and line, or zero otherwise, broadcast across all vector lanes. */
TgEXTN VEC_T(1)
FCN_VO(tgCO_BX_ClosestSq_PM_LR10)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_T(1,PC) OUT3, VEC_OBJ_T(TgBOX,CPC) ARG4, VEC_T(1,C) ARG5, VEC_T(1,C) ARG6 );

/** @brief Calculate the minimal distance between a box and a ray, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the parametric value for the closest point to {ARG5,ARG6} along the 1st axis of ARG4.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the parametric value for the closest point to {ARG5,ARG6} along the 2nd axis of ARG4.
    @param [out] OUT2 Pointer to a vector with a full broadcast of the parametric value for the closest point to {ARG5,ARG6} along the 3rd axis of ARG4.
    @param [out] OUT3 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG4 along {ARG5,ARG6}.
    @param [in] ARG4 Pointer to a box object.
    @param [in] ARG5 Vector holding the Ray Origin.
    @param [in] ARG6 Vector holding the Ray Direction.
    @return Minimal distance between the box and ray, or zero otherwise, broadcast across all vector lanes. */
TgEXTN VEC_T(1)
FCN_VO(tgCO_BX_Closest_PM_LR10)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_T(1,PC) OUT3, VEC_OBJ_T(TgBOX,CPC) ARG4, VEC_T(1,C) ARG5, VEC_T(1,C) ARG6 );


/** @brief Output the sequence of points created by clipping the ray to the indexed face (assuming an infinite projection along the face normal).
    @param [out] OUT0 Pointer to a clip list object, where the resulting points are stored.
    @param [in] ARG1 Pointer to a box object.
    @param [in] ARG2 Integer index to select which face (assuming an infinite projection along the face normal) to use for the clipping operation.
    @param [in] ARG3 Pointer to a ray object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_BXF_Clip_RY)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, VEC_OBJ_T(TgBOX,CPC) ARG1, TgSINT_E32_C ARG2, VEC_OBJ_T(TgRAY,CPC) ARG3 );

/** @brief Output the sequence of points created by clipping the ray to the interior of the box.
    @param [out] OUT0 Pointer to a clip list object, where the resulting points are stored.
    @param [in] ARG1 Pointer to a box object.
    @param [in] ARG2 Pointer to a ray object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_BX_Clip_RY)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, VEC_OBJ_T(TgBOX,CPC) ARG1, VEC_OBJ_T(TgRAY,CPC) ARG2 );

/** @brief Output the sequence of points created by clipping the ray to the indexed face (assuming an infinite projection along the face normal).
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point from clipping the ray.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the 2nd point from clipping the ray.
    @param [in] ARG2 Pointer to a box object.
    @param [in] ARG3 Integer index to select which face (assuming an infinite projection along the face normal) to use for the clipping operation.
    @param [in] ARG4 Pointer to a ray object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_BXF_Clip_PM_RY)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgBOX,CPC) ARG2, TgSINT_E32_C ARG3, VEC_OBJ_T(TgRAY,CPC) ARG4 );

/** @brief Output the sequence of points created by clipping the ray to the interior of the box.
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point from clipping the ray.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the 2nd point from clipping the ray.
    @param [in] ARG2 Pointer to a box object.
    @param [in] ARG3 Pointer to a ray object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_BX_Clip_PM_RY)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgBOX,CPC) ARG2, VEC_OBJ_T(TgRAY,CPC) ARG3 );


/** @brief Output the sequence of points created by clipping the ray to the indexed face (assuming an infinite projection along the face normal).
    @param [out] OUT0 Pointer to a clip list object, where the resulting points are stored.
    @param [in] ARG1 Pointer to a box object.
    @param [in] ARG2 Integer index to select which face (assuming an infinite projection along the face normal) to use for the clipping operation.
    @param [in] ARG3 Vector holding the Ray Origin.
    @param [in] ARG4 Vector holding the Ray Direction.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_BXF_Clip_LR10)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, VEC_OBJ_T(TgBOX,CPC) ARG1, TgSINT_E32_C ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4 );

/** @brief Output the sequence of points created by clipping the ray to the interior of the box.
    @param [out] OUT0 Pointer to a clip list object, where the resulting points are stored.
    @param [in] ARG1 Pointer to a box object.
    @param [in] ARG2 Vector holding the Ray Origin.
    @param [in] ARG3 Vector holding the Ray Direction.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_BX_Clip_LR10)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, VEC_OBJ_T(TgBOX,CPC) ARG1, VEC_T(1,C) ARG2, VEC_T(1,C) ARG3 );

/** @brief Output the sequence of points created by clipping the ray to the indexed face (assuming an infinite projection along the face normal).
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point from clipping the ray.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the 2nd point from clipping the ray.
    @param [in] ARG2 Pointer to a box object.
    @param [in] ARG3 Integer index to select which face (assuming an infinite projection along the face normal) to use for the clipping operation.
    @param [in] ARG4 Vector holding the Ray Origin.
    @param [in] ARG5 Vector holding the Ray Direction.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_BXF_Clip_PM_LR10)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgBOX,CPC) ARG2, TgSINT_E32_C ARG3, VEC_T(1,C) ARG4, VEC_T(1,C) ARG5 );

/** @brief Output the sequence of points created by clipping the ray to the interior of the box.
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point from clipping the ray.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the 2nd point from clipping the ray.
    @param [in] ARG2 Pointer to a box object.
    @param [in] ARG3 Vector holding the Ray Origin.
    @param [in] ARG4 Vector holding the Ray Direction.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_BX_Clip_PM_LR10)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgBOX,CPC) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4 );



/* Box - Segment                                                                                                                                                                   */

/** @brief Calculate the minimal distance squared between a box and a segment.
    @param [in] ARG0 Pointer to a box object.
    @param [in] ARG1 Pointer to a segment object.
    @return Minimal distance squared between a box and a segment, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_BX_DistSq_SG)(
    VEC_OBJ_T(TgBOX,CPC) ARG0, VEC_OBJ_T(TgSEGMENT,CPC) ARG1 );

/** @brief Calculate the minimal distance between a box and a segment.
    @param [in] ARG0 Pointer to a box object.
    @param [in] ARG1 Pointer to a segment object.
    @return Minimal distance between a box and a segment, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_BX_Dist_SG)(
    VEC_OBJ_T(TgBOX,CPC) ARG0, VEC_OBJ_T(TgSEGMENT,CPC) ARG1 );

/** @brief Calculate the minimal distance squared between a box and a segment, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a box object.
    @param [in] ARG3 Pointer to a segment object.
    @return Minimal distance squared between the box and segment, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_BX_ClosestSq_SG)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgBOX,CPC) ARG2, VEC_OBJ_T(TgSEGMENT,CPC) ARG3 );

/** @brief Calculate the minimal distance between a box and a segment, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a box object.
    @param [in] ARG3 Pointer to a segment object.
    @return Minimal distance between the box and segment, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_BX_Closest_SG)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgBOX,CPC) ARG2, VEC_OBJ_T(TgSEGMENT,CPC) ARG3 );


/** @brief Calculate the minimal distance squared between a box and a segment, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG5 along the 1st axis of ARG4.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG5 along the 2nd axis of ARG4.
    @param [out] OUT2 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG5 along the 3rd axis of ARG4.
    @param [out] OUT3 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG4 along ARG5.
    @param [in] ARG4 Pointer to a box object.
    @param [in] ARG5 Pointer to a segment object.
    @return Minimal distance squared between the box and segment, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_BX_ClosestSq_PM_SG)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_T(1,PC) OUT3, VEC_OBJ_T(TgBOX,CPC) ARG4, VEC_OBJ_T(TgSEGMENT,CPC) );

/** @brief Calculate the minimal distance between a box and a segment, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG5 along the 1st axis of ARG4.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG5 along the 2nd axis of ARG4.
    @param [out] OUT2 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG5 along the 3rd axis of ARG4.
    @param [out] OUT3 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG4 along ARG5.
    @param [in] ARG4 Pointer to a box object.
    @param [in] ARG5 Pointer to a segment object.
    @return Minimal distance between the box and segment, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_BX_Closest_PM_SG)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_T(1,PC) OUT3, VEC_OBJ_T(TgBOX,CPC) ARG4, VEC_OBJ_T(TgSEGMENT,CPC) );

/** @brief Calculate the minimal distance between a box and a line, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the parametric value for the closest point to {ARG5,ARG6} along the 1st axis of ARG4.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the parametric value for the closest point to {ARG5,ARG6} along the 2nd axis of ARG4.
    @param [out] OUT2 Pointer to a vector with a full broadcast of the parametric value for the closest point to {ARG5,ARG6} along the 3rd axis of ARG4.
    @param [out] OUT3 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG4 along {ARG5,ARG6}.
    @param [in] ARG4 Pointer to a box object.
    @param [in] ARG5 Vector holding the Segment Origin.
    @param [in] ARG6 Vector holding the position relative to the Segment Origin of the Segment Terminal Point.
    @return Minimal distance between the box and line, or zero otherwise, broadcast across all vector lanes. */
TgEXTN VEC_T(1)
FCN_VO(tgCO_BX_ClosestSq_PM_LR11)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_T(1,PC) OUT3, VEC_OBJ_T(TgBOX,CPC) ARG4, VEC_T(1,C) ARG5, VEC_T(1,C) ARG6 );

/** @brief Calculate the minimal distance between a box and a segment, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the parametric value for the closest point to {ARG5,ARG6} along the 1st axis of ARG4.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the parametric value for the closest point to {ARG5,ARG6} along the 2nd axis of ARG4.
    @param [out] OUT2 Pointer to a vector with a full broadcast of the parametric value for the closest point to {ARG5,ARG6} along the 3rd axis of ARG4.
    @param [out] OUT3 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG4 along {ARG5,ARG6}.
    @param [in] ARG4 Pointer to a box object.
    @param [in] ARG5 Vector holding the Segment Origin.
    @param [in] ARG6 Vector holding the position relative to the Segment Origin of the Segment Terminal Point.
    @return Minimal distance between the box and segment, or zero otherwise, broadcast across all vector lanes. */
TgEXTN VEC_T(1)
FCN_VO(tgCO_BX_Closest_PM_LR11)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_T(1,PC) OUT3, VEC_OBJ_T(TgBOX,CPC) ARG4, VEC_T(1,C) ARG5, VEC_T(1,C) ARG6 );


/** @brief Output the sequence of points created by clipping the segment to the indexed face (assuming an infinite projection along the face normal).
    @param [out] OUT0 Pointer to a clip list object, where the resulting points are stored.
    @param [in] ARG1 Pointer to a box object.
    @param [in] ARG2 Integer index to select which face (assuming an infinite projection along the face normal) to use for the clipping operation.
    @param [in] ARG3 Pointer to a segment object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_BXF_Clip_SG)( 
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, VEC_OBJ_T(TgBOX,CPC) ARG1, TgSINT_E32_C ARG2, VEC_OBJ_T(TgSEGMENT,CPC) ARG3 );

/** @brief Output the sequence of points created by clipping the segment to the interior of the box.
    @param [out] OUT0 Pointer to a clip list object, where the resulting points are stored.
    @param [in] ARG1 Pointer to a box object.
    @param [in] ARG2 Pointer to a segment object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_BX_Clip_SG)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, VEC_OBJ_T(TgBOX,CPC) ARG1, VEC_OBJ_T(TgSEGMENT,CPC) ARG2 );

/** @brief Output the sequence of points created by clipping the segment to the indexed face (assuming an infinite projection along the face normal).
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point from clipping the segment.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the 2nd point from clipping the segment.
    @param [in] ARG2 Pointer to a box object.
    @param [in] ARG3 Integer index to select which face (assuming an infinite projection along the face normal) to use for the clipping operation.
    @param [in] ARG4 Pointer to a segment object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_BXF_Clip_PM_SG)( 
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgBOX,CPC) ARG2, TgSINT_E32_C ARG3, VEC_OBJ_T(TgSEGMENT,CPC) ARG4 );

/** @brief Output the sequence of points created by clipping the segment to the interior of the box.
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point from clipping the segment.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the 2nd point from clipping the segment.
    @param [in] ARG2 Pointer to a box object.
    @param [in] ARG3 Pointer to a segment object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_BX_Clip_PM_SG)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgBOX,CPC) ARG2, VEC_OBJ_T(TgSEGMENT,CPC) ARG3 );


/** @brief Output the sequence of points created by clipping the segment to the indexed face (assuming an infinite projection along the face normal).
    @param [out] OUT0 Pointer to a clip list object, where the resulting points are stored.
    @param [in] ARG1 Pointer to a box object.
    @param [in] ARG2 Integer index to select which face (assuming an infinite projection along the face normal) to use for the clipping operation.
    @param [in] ARG3 Vector holding the Segment Origin.
    @param [in] ARG4 Vector holding the position relative to the Segment Origin of the Segment Terminal Point.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_BXF_Clip_LR11)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, VEC_OBJ_T(TgBOX,CPC) ARG1, TgSINT_E32_C ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4 );

/** @brief Output the sequence of points created by clipping the segment to the interior of the box.
    @param [out] OUT0 Pointer to a clip list object, where the resulting points are stored.
    @param [in] ARG1 Pointer to a box object.
    @param [in] ARG2 Vector holding the Segment Origin.
    @param [in] ARG3 Vector holding the position relative to the Segment Origin of the Segment Terminal Point.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_BX_Clip_LR11)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, VEC_OBJ_T(TgBOX,CPC) ARG1, VEC_T(1,C) ARG2, VEC_T(1,C) ARG3 );

/** @brief Output the sequence of points created by clipping the segment to the indexed face (assuming an infinite projection along the face normal).
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point from clipping the segment.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the 2nd point from clipping the segment.
    @param [in] ARG2 Pointer to a box object.
    @param [in] ARG3 Integer index to select which face (assuming an infinite projection along the face normal) to use for the clipping operation.
    @param [in] ARG4 Vector holding the Segment Origin.
    @param [in] ARG5 Vector holding the position relative to the Segment Origin of the Segment Terminal Point.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_BXF_Clip_PM_LR11)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgBOX,CPC) ARG2, TgSINT_E32_C ARG3, VEC_T(1,C) ARG4, VEC_T(1,C) ARG5 );

/** @brief Output the sequence of points created by clipping the segment to the interior of the box.
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point from clipping the segment.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the 2nd point from clipping the segment.
    @param [in] ARG2 Pointer to a box object.
    @param [in] ARG3 Vector holding the Segment Origin.
    @param [in] ARG4 Vector holding the position relative to the Segment Origin of the Segment Terminal Point.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_BX_Clip_PM_LR11)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgBOX,CPC) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4 );



/* Box - Plane                                                                                                                                                                     */

/** @brief Calculate the minimal distance squared between a box and a plane.
    @param [in] ARG0 Pointer to a box object.
    @param [in] ARG1 Pointer to a plane object.
    @return Minimal distance squared between a box and a plane when the box is above the plane, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_BX_DistSq_PN)(
    VEC_OBJ_T(TgBOX,CPC) ARG0, VEC_OBJ_T(TgPLANE,CPC) ARG1 );

/** @brief Calculate the minimal distance between a box and a plane.
    @param [in] ARG0 Pointer to a box object.
    @param [in] ARG1 Pointer to a plane object.
    @return Minimal distance between a box and a plane when the box is above the plane, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_BX_Dist_PN)(
    VEC_OBJ_T(TgBOX,CPC) ARG0, VEC_OBJ_T(TgPLANE,CPC) ARG1 );

/** @brief Calculate the minimal distance squared between a box and a plane, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a box object.
    @param [in] ARG3 Pointer to a plane object.
    @return Minimal distance squared between the box and a plane when the box is above the plane, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_BX_ClosestSq_PN)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgBOX,CPC) ARG2, VEC_OBJ_T(TgPLANE,CPC) ARG3 );

/** @brief Calculate the minimal distance between a box and a plane, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a box object.
    @param [in] ARG3 Pointer to a plane object.
    @return Minimal distance between the box and a plane when the box is above the plane, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_BX_Closest_PN)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgBOX,CPC) ARG2, VEC_OBJ_T(TgPLANE,CPC) ARG3 );

/** @brief Calculate the minimal distance squared between a box and a plane, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG5 along the 1st axis of ARG4.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG5 along the 2nd axis of ARG4.
    @param [out] OUT2 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG5 along the 3rd axis of ARG4.
    @param [out] OUT3 Pointer to a vector holding the closest point to ARG4 on ARG5.
    @param [in] ARG4 Pointer to a box object.
    @param [in] ARG5 Pointer to a plane object.
    @return Minimal distance squared between the box and a plane when the box is above the plane, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_BX_ClosestSq_PM_PN)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_T(1,PC) OUT3, VEC_OBJ_T(TgBOX,CPC) ARG4, VEC_OBJ_T(TgPLANE,CPC) ARG5 );

/** @brief Calculate the minimal distance between a box and a plane, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG5 along the 1st axis of ARG4.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG5 along the 2nd axis of ARG4.
    @param [out] OUT2 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG5 along the 3rd axis of ARG4.
    @param [out] OUT3 Pointer to a vector holding the closest point to ARG4 on ARG5.
    @param [in] ARG4 Pointer to a box object.
    @param [in] ARG5 Pointer to a plane object.
    @return Minimal distance between the box and a plane when the box is above the plane, or zero otherwise, broadcast across all vector lanes. */
TgEXTN VEC_T(1)
FCN_VO(tgCO_BX_Closest_PM_PN)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_T(1,PC) OUT3, VEC_OBJ_T(TgBOX,CPC) ARG4, VEC_OBJ_T(TgPLANE,CPC) ARG5 );

/** @brief Update the collision packet with point(s) of penetration between a box and a sphere.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG2.
                         Contact normals are the direction for the object at ARG2 to move to achieve separation.
                         Depth values are measured from the surface of the object at ARG1 to the contact point.
    @param [in] ARG1 Pointer to a box object.
    @param [in] ARG2 Pointer to a plane object.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_PN_Penetrate_BX)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgPLANE,CPC) ARG1, VEC_OBJ_T(TgBOX,CPC) ARG2 );

/** @brief Update the collision packet with point(s) of penetration between a box and a sphere.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG2.
                         Contact normals are the direction for the object at ARG2 to move to achieve separation.
                         Depth values are measured from the surface of the object at ARG1 to the contact point.
    @param [in] ARG2 Pointer to a plane object.
    @param [in] ARG1 Pointer to a box object.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_BX_Penetrate_PN)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgBOX,CPC) ARG1, VEC_OBJ_T(TgPLANE,CPC) ARG2 );


/* Box - Sphere                                                                                                                                                                    */

/** @brief Calculate the minimal distance squared between a box and a sphere.
    @param [in] ARG0 Pointer to a box object.
    @param [in] ARG1 Pointer to a sphere object.
    @return Minimal distance squared between a box and a sphere, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_BX_DistSq_SP)(
    VEC_OBJ_T(TgBOX,CPC) ARG0, VEC_OBJ_T(TgSPHERE,CPC) ARG1 );

/** @brief Calculate the minimal distance between a box and a sphere.
    @param [in] ARG0 Pointer to a box object.
    @param [in] ARG1 Pointer to a sphere object.
    @return Minimal distance between a box and a sphere, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_BX_Dist_SP)(
    VEC_OBJ_T(TgBOX,CPC) ARG0, VEC_OBJ_T(TgSPHERE,CPC) ARG1 );

/** @brief Calculate the minimal distance squared between a box and a sphere, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a box object.
    @param [in] ARG3 Pointer to a sphere object.
    @return Minimal distance squared between the box and a sphere, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_BX_ClosestSq_SP)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgBOX,CPC) ARG2, VEC_OBJ_T(TgSPHERE,CPC) ARG3 );

/** @brief Calculate the minimal distance between a box and a sphere, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a box object.
    @param [in] ARG3 Pointer to a sphere object.
    @return Minimal distance between the box and a sphere, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_BX_Closest_SP)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgBOX,CPC) ARG2, VEC_OBJ_T(TgSPHERE,CPC) ARG3 );


/** @brief Calculate the minimal distance squared between a box and a sphere, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG5 along the 1st axis of ARG4.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG5 along the 2nd axis of ARG4.
    @param [out] OUT2 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG5 along the 3rd axis of ARG4.
    @param [out] OUT3 Pointer to a vector holding the closest point to ARG4 on ARG5.
    @param [in] ARG4 Pointer to a box object.
    @param [in] ARG5 Pointer to a sphere object.
    @return Minimal distance squared between the box and a sphere, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_BX_ClosestSq_PM_SP)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_T(1,PC) OUT3, VEC_OBJ_T(TgBOX,CPC) ARG4, VEC_OBJ_T(TgSPHERE,CPC) ARG5 );

/** @brief Calculate the minimal distance between a box and a sphere, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG5 along the 1st axis of ARG4.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG5 along the 2nd axis of ARG4.
    @param [out] OUT2 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG5 along the 3rd axis of ARG4.
    @param [out] OUT3 Pointer to a vector holding the closest point to ARG4 on ARG5.
    @param [in] ARG4 Pointer to a box object.
    @param [in] ARG5 Pointer to a sphere object.
    @return Minimal distance between the box and a sphere, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_BX_Closest_PM_SP)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_T(1,PC) OUT3, VEC_OBJ_T(TgBOX,CPC) ARG4, VEC_OBJ_T(TgSPHERE,CPC) ARG5 );


/** @brief Update the collision packet with point(s) of penetration between a box and a sphere.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG2.
                         Contact normals are the direction for the object at ARG2 to move to achieve separation.
                         Depth values are measured from the surface of the object at ARG1 to the contact point.
    @param [in] ARG1 Pointer to a box object.
    @param [in] ARG2 Pointer to a sphere object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_BX_Penetrate_SP)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgBOX,CPC) ARG1, VEC_OBJ_T(TgSPHERE,CPC) ARG2 );

/** @brief Update the collision packet with point(s) of penetration between a sphere and a box.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG2.
                         Contact normals are the direction for the object at ARG2 to move to achieve separation.
                         Depth values are measured from the surface of the object at ARG1 to the contact point.
    @param [in] ARG1 Pointer to a sphere object.
    @param [in] ARG2 Pointer to a box object.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_SP_Penetrate_BX)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgSPHERE,CPC) ARG1, VEC_OBJ_T(TgBOX,CPC) ARG2 );



/* Box - Triangle                                                                                                                                                                  */

/** @brief Update the collision packet with point(s) of penetration between a box and a triangle.
    @detail Let α represent the simulation frequency, β the maximum velocity in the system.
              Thus, β/α is the displacement vector used as the function parameter.
            Let Φ represent the minimal distance between the triangle centre and the nearest edge.
            For the system to retain coherency/validity then β/α < Φ - feature reduction may help to reduce this issue.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG2.
                         Contact normals are the direction for the object at ARG2 to move to achieve separation.
                         Depth values are measured from the surface of the object at ARG1 to the contact point.
    @param [in] ARG1 Pointer to a triangle (space) object.
    @param [in] ARG2 Pointer to a box object.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_ST_Penetrate_BX)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgSTRI,CPC) ARG1, VEC_OBJ_T(TgBOX,CPC) ARG2 );



/* Utility                                                                                                                                                                         */

/** @brief Clip a line segment to the interior of a box.
    @param [out] OUT0 Pointer to a vector holding the updated (clipped) point from ARG3.
    @param [out] OUT1 Pointer to a vector holding the updated (clipped) point from ARG4.
    @param [in] ARG2 Pointer to a box object.
    @param [in] ARG3 Vector holding a position (point) representing the 1st (starting) point of a line segment.
    @param [in] ARG4 Vector holding a position (point) representing the 2nd (terminal) point of a line segment.
   @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_BX_Clip_Points)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgBOX,CPC) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4 );

/** @brief Clip a line strip to the interior of a box.
    @param [in,out] OUT0 Pointer to a clip list object (an array of vectors interpreted as a line strip).
    @param [in] ARG1 Pointer to a box object.
   @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_BX_Clip)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, VEC_OBJ_T(TgBOX,CPC) ARG1 );

/** @brief Clip a line strip to the indexed face of a box (assuming an infinite projection along the face normal).
    @param [in,out] OUT0 Pointer to a clip list object (an array of vectors interpreted as a line strip).
    @param [in] ARG1 Pointer to a box object.
    @param [in] ARG2 Integer index to select which face (assuming an infinite projection along the face normal) to use for the clipping operation.
   @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_BXF_Clip)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, VEC_OBJ_T(TgBOX,CPC) ARG1, TgSINT_E32_C ARG2 );

/** @brief Clip a triangle to the indexed face of a box (assuming an infinite projection along the face normal).
    @param [out] OUT0 Pointer to a clip list object (an array of vectors interpreted as a line strip).
    @param [in] ARG1 Pointer to a box object.
    @param [in] ARG2 Integer index to select which face (assuming an infinite projection along the face normal) to use for the clipping operation.
    @param [in] ARG3 Pointer to a triangle (point) object.
   @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_BXF_Clip_PT)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, VEC_OBJ_T(TgBOX,CPC) ARG1, TgSINT_E32_C ARG2, VEC_OBJ_T(TgPTRI,CPC) ARG3 );

/** @brief Generate the needed information for a axis of separation test.
    @param [out] OUT0 Pointer to a structure used to inform axis separation evaluations.
    @param [in] ARG1 Vector holding the axis of separation (axis of projection).
    @param [in] ARG2 Pointer to a box object.
   @return Result Code. */
TgEXTN TgVOID
FCN_VO(tgCO_BX_Axis_ProjInfo)(
    VEC_OBJ_T(STg2_CO_Axis_Project,PC) OUT0, VEC_T(1,C) ARG1, VEC_OBJ_T(TgBOX,CPC) ARG2 );


/** @} TGS_COLLISION_BX */

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

    #define TGS_COLLISION_BOX_H

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COLLISION_BOX_H) */
#endif
