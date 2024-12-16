/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Parallelogram.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_PARALLELOGRAM_H)
#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* == Collision ================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions - Scalar Functions                                                                                                                                            */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @addtogroup TGS_COLLISION_PE */
/** @{ */

TgEXTN TgRESULT
FCN_VO(tgCO_Clip_PE)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC), VEC_OBJ_T(TgPARALLELOGRAM,CPC) );


/* Parallelogram - Point                                                                                                                                                           */

/** @brief Calculate the minimal distance squared between a parallelogram and a point.
    @param [in] ARG0 Pointer to a parallelogram object.
    @param [in] ARG1 Vector holding a position (point).
    @return Minimal distance squared between the parallelogram and point, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_PE_DistSq_PT)(
    VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG0, VEC_T(1,C) ARG1 );

/** @brief Calculate the minimal distance between a parallelogram and a point.
    @param [in] ARG0 Pointer to a parallelogram object.
    @param [in] ARG1 Vector holding a position (point).
    @return Minimal distance between the parallelogram and point, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_PE_Dist_PT)(
    VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG0, VEC_T(1,C) ARG1 );

/** @brief Calculate the minimal distance squared between a parallelogram and a point, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG2 on ARG1.
    @param [in] ARG1 Pointer to a parallelogram object.
    @param [in] ARG2 Vector holding a position (point).
    @return Minimal distance squared between the parallelogram and point, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_PE_ClosestSq_PT)(
    VEC_T(1,PC) OUT0, VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG1, VEC_T(1,C) ARG2 );

/** @brief Calculate the minimal distance between a parallelogram and a point, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG2 on ARG1.
    @param [in] ARG1 Pointer to a parallelogram object.
    @param [in] ARG2 Vector holding a position (point).
    @return Minimal distance between the parallelogram and point, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_PE_Closest_PT)(
    VEC_T(1,PC) OUT0, VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG1, VEC_T(1,C) ARG2 );

/** @brief Calculate the minimal distance squared between a parallelogram and a line, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the 1st edge scalar of ARG2.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the 2nd edge scalar of ARG2.
    @param [in] ARG2 Pointer to a parallelogram object.
    @param [in] ARG3 Vector holding a position (point).
    @return Minimal distance squared between the parallelogram and line, or zero otherwise, broadcast across all vector lanes. */
TgEXTN VEC_T(1)
FCN_VO(tgCO_PE_ClosestSq_PM_PT)(
    VEC_T(1,PC) OUT0 , VEC_T(1,PC) OUT1, VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG2, VEC_T(1,C) ARG3 );

/** @brief Calculate the minimal distance between a parallelogram and a line, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the 1st edge scalar of ARG2.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the 2nd edge scalar of ARG2.
    @param [in] ARG2 Pointer to a parallelogram object.
    @param [in] ARG3 Vector holding a position (point).
    @return Minimal distance between the parallelogram and line, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_PE_Closest_PM_PT)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG2, VEC_T(1,C) ARG3 );


/* Parallelogram - Line                                                                                                                                                            */

/** @brief Calculate the minimal distance squared between a parallelogram and a line.
    @param [in] ARG0 Pointer to a parallelogram object.
    @param [in] ARG1 Pointer to a line object.
    @return Minimal distance squared between a parallelogram and a line, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_PE_DistSq_LN)(
    VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG0, VEC_OBJ_T(TgLINE,CPC) ARG1 );

/** @brief Calculate the minimal distance between a parallelogram and a line.
    @param [in] ARG0 Pointer to a parallelogram object.
    @param [in] ARG1 Pointer to a line object.
    @return Minimal distance between a parallelogram and a line, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_PE_Dist_LN)(
    VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG0, VEC_OBJ_T(TgLINE,CPC) ARG1 );

/** @brief Calculate the minimal distance squared between a parallelogram and a line, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a parallelogram object.
    @param [in] ARG3 Pointer to a line object.
    @return Minimal distance squared between the parallelogram and line, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_PE_ClosestSq_LN)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG2, VEC_OBJ_T(TgLINE,CPC) ARG3 );

/** @brief Calculate the minimal distance between a parallelogram and a line, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a parallelogram object.
    @param [in] ARG3 Pointer to a line object.
    @return Minimal distance between the parallelogram and line, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_PE_Closest_LN)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG2, VEC_OBJ_T(TgLINE,CPC) ARG3 );

/** @brief Calculate the minimal distance squared between a parallelogram and a line, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the 1st edge scalar of ARG3.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the 2nd edge scalar of ARG3.
    @param [out] OUT2 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG3 on ARG4.
    @param [in] ARG3 Pointer to a parallelogram object.
    @param [in] ARG4 Pointer to a line object.
    @return Minimal distance squared between the parallelogram and line, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_PE_ClosestSq_PM_LN)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) ARG2, VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG3, VEC_OBJ_T(TgLINE,CPC) ARG4 );

/** @brief Calculate the minimal distance between a parallelogram and a line, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the 1st edge scalar of ARG3.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the 2nd edge scalar of ARG3.
    @param [out] OUT2 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG3 on ARG4.
    @param [in] ARG3 Pointer to a parallelogram object.
    @param [in] ARG4 Pointer to a line object.
    @return Minimal distance between the parallelogram and line, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_PE_Closest_PM_LN)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG3, VEC_OBJ_T(TgLINE,CPC) ARG4 );

/** @brief Calculate the minimal distance squared between a parallelogram and a line, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the 1st edge scalar of ARG3.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the 2nd edge scalar of ARG3.
    @param [out] OUT2 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG3 on {ARG4,ARG5}.
    @param [in] ARG3 Pointer to a parallelogram object.
    @param [in] ARG4 Vector holding the Line Origin.
    @param [in] ARG5 Vector holding the Line Direction.
    @return Minimal distance squared between the parallelogram and line, or zero otherwise, broadcast across all vector lanes. */
TgEXTN VEC_T(1)
FCN_VO(tgCO_PE_ClosestSq_PM_LR00)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG3, VEC_T(1,C) ARG4, VEC_T(1,C) ARG5 );

/** @brief Calculate the minimal distance between a parallelogram and a line, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the 1st edge scalar of ARG3.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the 2nd edge scalar of ARG3.
    @param [out] OUT2 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG3 on {ARG4,ARG5}.
    @param [in] ARG3 Pointer to a parallelogram object.
    @param [in] ARG4 Vector holding the Line Origin.
    @param [in] ARG5 Vector holding the Line Direction.
    @return Minimal distance between the parallelogram and line, or zero otherwise, broadcast across all vector lanes. */
TgEXTN VEC_T(1)
FCN_VO(tgCO_PE_Closest_PM_LR00)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG3, VEC_T(1,C) ARG4, VEC_T(1,C) ARG5 );


/** @brief Determine if the two primitives are intersecting.
    @param [in] ARG0 Pointer to a parallelogram object.
    @param [in] ARG1 Pointer to a line object.
    @return True if the two primitives are intersecting, and false otherwise. */
TgINLINE TgBOOL
FCN_VO(tgCO_PE_Test_LN)(
    VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG0, VEC_OBJ_T(TgLINE,CPC) ARG1 );

/** @brief Determine if the two primitives are intersecting.
    @param [in] ARG0 Pointer to a parallelogram object.
    @param [in] ARG1 Vector holding the Line Origin.
    @param [in] ARG2 Vector holding the Line Direction.
    @return True if the two primitives are intersecting, and false otherwise. */
TgINLINE TgBOOL
FCN_VO(tgCO_PE_Test_LR00)(
    VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG0, VEC_T(1,C) ARG1, VEC_T(1,C) ARG2 );


/** @brief Output the sequence of points created by clipping the line to the interior of the parallelogram.
    @param [out] OUT0 Pointer to a clip list object, where the resulting points are stored.
    @param [in] ARG1 Pointer to a parallelogram object.
    @param [in] ARG2 Pointer to a line object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_PE_Clip_LN)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG1, VEC_OBJ_T(TgLINE,CPC) ARG2 );

/** @brief Output the sequence of points created by clipping the line to the interior of the parallelogram.
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point from clipping the line.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the 2nd point from clipping the line.
    @param [in] ARG2 Pointer to a parallelogram object.
    @param [in] ARG3 Pointer to a line object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_PE_Clip_PM_LN)(
    VEC_T(1,PC) OUT0 , VEC_T(1,PC) OUT1, VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG2, VEC_OBJ_T(TgLINE,CPC) ARG3 );

/** @brief Output the sequence of points created by clipping the line to the interior of the parallelogram.
    @param [out] OUT0 Pointer to a clip list object, where the resulting points are stored.
    @param [in] ARG1 Pointer to a parallelogram object.
    @param [in] ARG2 Vector holding the Line Origin.
    @param [in] ARG3 Vector holding the Line Direction.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_PE_Clip_LR00)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG1, VEC_T(1,C) ARG2, VEC_T(1,C) ARG3 );

/** @brief Output the sequence of points created by clipping the line to the interior of the parallelogram.
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point from clipping the line.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the 2nd point from clipping the line.
    @param [in] ARG2 Pointer to a parallelogram object.
    @param [in] ARG3 Vector holding the Line Origin.
    @param [in] ARG4 Vector holding the Line Direction.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_PE_Clip_PM_LR00)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4 );


/* Parallelogram - Ray                                                                                                                                                             */

/** @brief Calculate the minimal distance squared between a parallelogram and a ray.
    @param [in] ARG0 Pointer to a parallelogram object.
    @param [in] ARG1 Pointer to a ray object.
    @return Minimal distance squared between a parallelogram and a ray, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_PE_DistSq_RY)(
    VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG0, VEC_OBJ_T(TgRAY,CPC) ARG1 );

/** @brief Calculate the minimal distance between a parallelogram and a ray.
    @param [in] ARG0 Pointer to a parallelogram object.
    @param [in] ARG1 Pointer to a ray object.
    @return Minimal distance between a parallelogram and a ray, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_PE_Dist_RY)(
    VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG0, VEC_OBJ_T(TgRAY,CPC) ARG1 );

/** @brief Calculate the minimal distance squared between a parallelogram and a ray, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a parallelogram object.
    @param [in] ARG3 Pointer to a ray object.
    @return Minimal distance squared between the parallelogram and ray, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_PE_ClosestSq_RY)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG2, VEC_OBJ_T(TgRAY,CPC) ARG3 );

/** @brief Calculate the minimal distance between a parallelogram and a ray, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a parallelogram object.
    @param [in] ARG3 Pointer to a ray object.
    @return Minimal distance between the parallelogram and ray, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_PE_Closest_RY)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG2, VEC_OBJ_T(TgRAY,CPC) ARG3 );

/** @brief Calculate the minimal distance squared between a parallelogram and a ray, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the 1st edge scalar of ARG3.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the 2nd edge scalar of ARG3.
    @param [out] OUT2 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG3 on ARG4.
    @param [in] ARG3 Pointer to a parallelogram object.
    @param [in] ARG4 Pointer to a ray object.
    @return Minimal distance squared between the parallelogram and ray, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_PE_ClosestSq_PM_RY)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG2, VEC_OBJ_T(TgRAY,CPC) ARG3 );

/** @brief Calculate the minimal distance between a parallelogram and a ray, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the 1st edge scalar of ARG3.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the 2nd edge scalar of ARG3.
    @param [out] OUT2 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG3 on ARG4.
    @param [in] ARG3 Pointer to a parallelogram object.
    @param [in] ARG4 Pointer to a ray object.
    @return Minimal distance between the parallelogram and ray, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_PE_Closest_PM_RY)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG3, VEC_OBJ_T(TgRAY,CPC) ARG4 );

/** @brief Calculate the minimal distance squared between a parallelogram and a ray, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the 1st edge scalar of ARG3.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the 2nd edge scalar of ARG3.
    @param [out] OUT2 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG3 on {ARG4,ARG5}.
    @param [in] ARG3 Pointer to a parallelogram object.
    @param [in] ARG4 Vector holding the Ray Origin.
    @param [in] ARG5 Vector holding the Ray Direction.
    @return Minimal distance squared between the parallelogram and ray, or zero otherwise, broadcast across all vector lanes. */
TgEXTN VEC_T(1)
FCN_VO(tgCO_PE_ClosestSq_PM_LR10)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG3, VEC_T(1,C) ARG4, VEC_T(1,C) ARG5 );

/** @brief Calculate the minimal distance between a parallelogram and a ray, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the 1st edge scalar of ARG3.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the 2nd edge scalar of ARG3.
    @param [out] OUT2 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG3 on {ARG4,ARG5}.
    @param [in] ARG3 Pointer to a parallelogram object.
    @param [in] ARG4 Vector holding the Ray Origin.
    @param [in] ARG5 Vector holding the Ray Direction.
    @return Minimal distance between the parallelogram and ray, or zero otherwise, broadcast across all vector lanes. */
TgEXTN VEC_T(1)
FCN_VO(tgCO_PE_Closest_PM_LR10)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG3, VEC_T(1,C) ARG4, VEC_T(1,C) ARG5 );


/** @brief Determine if the two primitives are intersecting.
    @param [in] ARG0 Pointer to a parallelogram object.
    @param [in] ARG1 Pointer to a ray object.
    @return True if the two primitives are intersecting, and false otherwise. */
TgINLINE TgBOOL
FCN_VO(tgCO_PE_Test_RY)(
    VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG0, VEC_OBJ_T(TgRAY,CPC) ARG1 );

/** @brief Determine if the two primitives are intersecting.
    @param [in] ARG0 Pointer to a parallelogram object.
    @param [in] ARG1 Vector holding the Ray Origin.
    @param [in] ARG2 Vector holding the Ray Direction.
    @return True if the two primitives are intersecting, and false otherwise. */
TgINLINE TgBOOL
FCN_VO(tgCO_PE_Test_LR10)(
    VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG0, VEC_T(1,C) ARG1, VEC_T(1,C) ARG2 );


/** @brief Output the sequence of points created by clipping the ray to the interior of the parallelogram.
    @param [out] OUT0 Pointer to a clip list object, where the resulting points are stored.
    @param [in] ARG1 Pointer to a parallelogram object.
    @param [in] ARG2 Pointer to a ray object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_PE_Clip_RY)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG1, VEC_OBJ_T(TgRAY,CPC) ARG2 );

/** @brief Output the sequence of points created by clipping the ray to the interior of the parallelogram.
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point from clipping the ray.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the 2nd point from clipping the ray.
    @param [in] ARG2 Pointer to a parallelogram object.
    @param [in] ARG3 Pointer to a ray object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_PE_Clip_PM_RY)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG2, VEC_OBJ_T(TgRAY,CPC) ARG3 );

/** @brief Output the sequence of points created by clipping the ray to the interior of the parallelogram.
    @param [out] OUT0 Pointer to a clip list object, where the resulting points are stored.
    @param [in] ARG1 Pointer to a parallelogram object.
    @param [in] ARG2 Vector holding the Ray Origin.
    @param [in] ARG3 Vector holding the Ray Direction.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_PE_Clip_LR10)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG1, VEC_T(1,C) ARG2, VEC_T(1,C) ARG3 );

/** @brief Output the sequence of points created by clipping the ray to the interior of the parallelogram.
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point from clipping the ray.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the 2nd point from clipping the ray.
    @param [in] ARG2 Pointer to a parallelogram object.
    @param [in] ARG3 Vector holding the Ray Origin.
    @param [in] ARG4 Vector holding the Ray Direction.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_PE_Clip_PM_LR10)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4 );


/* Parallelogram - Segment                                                                                                                                                         */

/** @brief Calculate the minimal distance squared between a parallelogram and a segment.
    @param [in] ARG0 Pointer to a parallelogram object.
    @param [in] ARG1 Pointer to a segment object.
    @return Minimal distance squared between a parallelogram and a segment, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_PE_DistSq_SG)(
    VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG0, VEC_OBJ_T(TgSEGMENT,CPC) ARG1 );

/** @brief Calculate the minimal distance between a parallelogram and a segment.
    @param [in] ARG0 Pointer to a parallelogram object.
    @param [in] ARG1 Pointer to a segment object.
    @return Minimal distance between a parallelogram and a segment, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_PE_Dist_SG)(
    VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG0, VEC_OBJ_T(TgSEGMENT,CPC) ARG1 );

/** @brief Calculate the minimal distance squared between a parallelogram and a segment, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a parallelogram object.
    @param [in] ARG3 Pointer to a segment object.
    @return Minimal distance squared between the parallelogram and segment, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_PE_ClosestSq_SG)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG2, VEC_OBJ_T(TgSEGMENT,CPC) ARG3 );

/** @brief Calculate the minimal distance between a parallelogram and a segment, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a parallelogram object.
    @param [in] ARG3 Pointer to a segment object.
    @return Minimal distance between the parallelogram and segment, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_PE_Closest_SG)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG2, VEC_OBJ_T(TgSEGMENT,CPC) ARG3 );

/** @brief Calculate the minimal distance squared between a parallelogram and a segment, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the 1st edge scalar of ARG3.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the 2nd edge scalar of ARG3.
    @param [out] OUT2 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG3 on ARG4.
    @param [in] ARG3 Pointer to a parallelogram object.
    @param [in] ARG4 Pointer to a segment object.
    @return Minimal distance squared between the parallelogram and segment, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_PE_ClosestSq_PM_SG)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG3, VEC_OBJ_T(TgSEGMENT,CPC) ARG4 );

/** @brief Calculate the minimal distance between a parallelogram and a segment, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the 1st edge scalar of ARG3.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the 2nd edge scalar of ARG3.
    @param [out] OUT2 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG3 on ARG4.
    @param [in] ARG3 Pointer to a parallelogram object.
    @param [in] ARG4 Pointer to a segment object.
    @return Minimal distance between the parallelogram and segment, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_PE_Closest_PM_SG)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG3, VEC_OBJ_T(TgSEGMENT,CPC) ARG4 );

/** @brief Calculate the minimal distance squared between a parallelogram and a segment, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the 1st edge scalar of ARG3.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the 2nd edge scalar of ARG3.
    @param [out] OUT2 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG3 on {ARG4,ARG5}.
    @param [in] ARG3 Pointer to a parallelogram object.
    @param [in] ARG4 Vector holding the Segment Origin.
    @param [in] ARG5 Vector holding the position relative to the Segment Origin of the Segment Terminal Point.
    @return Minimal distance squared between the parallelogram and segment, or zero otherwise, broadcast across all vector lanes. */
TgEXTN VEC_T(1)
FCN_VO(tgCO_PE_ClosestSq_PM_LR11)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG3, VEC_T(1,C) ARG4, VEC_T(1,C) ARG5 );

/** @brief Calculate the minimal distance between a parallelogram and a segment, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the 1st edge scalar of ARG3.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the 2nd edge scalar of ARG3.
    @param [out] OUT2 Pointer to a vector with a full broadcast of the parametric value for the closest point to ARG3 on {ARG4,ARG5}.
    @param [in] ARG3 Pointer to a parallelogram object.
    @param [in] ARG4 Vector holding the Segment Origin.
    @param [in] ARG5 Vector holding the position relative to the Segment Origin of the Segment Terminal Point.
    @return Minimal distance between the parallelogram and segment, or zero otherwise, broadcast across all vector lanes. */
TgEXTN VEC_T(1)
FCN_VO(tgCO_PE_Closest_PM_LR11)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG3, VEC_T(1,C) ARG4, VEC_T(1,C) ARG5 );


/** @brief Determine if the two primitives are intersecting.
    @param [in] ARG0 Pointer to a parallelogram object.
    @param [in] ARG1 Pointer to a segment object.
    @return True if the two primitives are intersecting, and false otherwise. */
TgINLINE TgBOOL
FCN_VO(tgCO_PE_Test_SG)(
    VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG0, VEC_OBJ_T(TgSEGMENT,CPC) ARG1 );

/** @brief Determine if the two primitives are intersecting.
    @param [in] ARG0 Pointer to a parallelogram object.
    @param [in] ARG1 Vector holding the Segment Origin.
    @param [in] ARG2 Vector holding the position relative to the Segment Origin of the Segment Terminal Point.
    @return True if the two primitives are intersecting, and false otherwise. */
TgINLINE TgBOOL
FCN_VO(tgCO_PE_Test_LR11)(
    VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG0, VEC_T(1,C) ARG1, VEC_T(1,C) ARG2 );


/** @brief Output the sequence of points created by clipping the segment to the interior of the parallelogram.
    @param [out] OUT0 Pointer to a clip list object, where the resulting points are stored.
    @param [in] ARG1 Pointer to a parallelogram object.
    @param [in] ARG2 Pointer to a segment object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_PE_Clip_SG)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG1, VEC_OBJ_T(TgSEGMENT,CPC) ARG2 );

/** @brief Output the sequence of points created by clipping the segment to the interior of the parallelogram.
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point from clipping the segment.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the 2nd point from clipping the segment.
    @param [in] ARG2 Pointer to a parallelogram object.
    @param [in] ARG3 Pointer to a segment object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_PE_Clip_PM_SG)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG2, VEC_OBJ_T(TgSEGMENT,CPC) ARG3 );

/** @brief Output the sequence of points created by clipping the segment to the interior of the parallelogram.
    @param [out] OUT0 Pointer to a clip list object, where the resulting points are stored.
    @param [in] ARG1 Pointer to a parallelogram object.
    @param [in] ARG2 Vector holding the Segment Origin.
    @param [in] ARG3 Vector holding the position relative to the Segment Origin of the Segment Terminal Point.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_PE_Clip_LR11)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG1, VEC_T(1,C) ARG2, VEC_T(1,C) ARG3 );

/** @brief Output the sequence of points created by clipping the segment to the interior of the parallelogram.
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point from clipping the segment.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the 2nd point from clipping the segment.
    @param [in] ARG2 Pointer to a parallelogram object.
    @param [in] ARG3 Vector holding the Segment Origin.
    @param [in] ARG4 Vector holding the position relative to the Segment Origin of the Segment Terminal Point.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_PE_Clip_PM_LR11)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4 );


/** @brief Output the sequence of points created by clipping the segment to the interior of the capsule.
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point from clipping the segment.
    @param [out] OUT1 Pointer to a vector holding a full broadcast of the parametric value for the 2nd point from clipping the segment.
    @param [in] ARG2 Pointer to a parallelogram object.
    @param [in] ARG3 Vector holding the Segment Origin.
    @param [in] ARG4 Vector holding the position relative to the Segment Origin of the Segment Terminal Point.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_PE_Clip_Points)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4 );


/* Parallelogram - Triangle                                                                                                                                                        */

/** @brief Calculate the minimal distance squared between a parallelogram and a triangle.
    @param [in] ARG0 Pointer to a parallelogram object.
    @param [in] ARG1 Pointer to a triangle (space) object.
    @return Minimal distance squared between a parallelogram and a triangle , or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_PE_DistSq_ST)(
    VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG0, VEC_OBJ_T(TgSTRI,CPC) ARG1 );

/** @brief Calculate the minimal distance between a parallelogram and a triangle.
    @param [in] ARG0 Pointer to a parallelogram object.
    @param [in] ARG1 Pointer to a triangle (space) object.
    @return Minimal distance between a parallelogram and a triangle, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_PE_Dist_ST)(
    VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG0, VEC_OBJ_T(TgSTRI,CPC) ARG1 );

/** @brief Calculate the minimal distance squared between a parallelogram and a triangle, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a parallelogram object.
    @param [in] ARG3 Pointer to a triangle (space) object.
    @return Minimal distance squared between the parallelogram and triangle, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_PE_ClosestSq_ST)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG2, VEC_OBJ_T(TgSTRI,CPC) ARG3 );

/** @brief Calculate the minimal distance between a parallelogram and a triangle, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a parallelogram object.
    @param [in] ARG3 Pointer to a triangle (space) object.
    @return Minimal distance between the parallelogram and triangle, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_PE_Closest_ST)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG2, VEC_OBJ_T(TgSTRI,CPC) ARG3 );

/** @brief Calculate the minimal distance squared between a parallelogram and a triangle, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the 1st edge scalar of the closest point to ARG5 on ARG4.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the 2nd edge scalar of the closest point to ARG5 on ARG4.
    @param [out] OUT2 Pointer to a vector with a full broadcast of the 1st barycentric coordinate of the closest point to ARG4 on ARG5.
    @param [out] OUT3 Pointer to a vector with a full broadcast of the 2nd barycentric coordinate of the closest point to ARG4 on ARG5.
    @param [in] ARG4 Pointer to a parallelogram object.
    @param [in] ARG5 Pointer to a triangle (space) object.
    @return Minimal distance squared between the parallelogram and triangle, or zero otherwise, broadcast across all vector lanes. */
TgEXTN VEC_T(1)
FCN_VO(tgCO_PE_ClosestSq_PM_ST)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_T(1,PC) OUT3, VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG4, VEC_OBJ_T(TgSTRI,CPC) ARG5 );

/** @brief Calculate the minimal distance between a parallelogram and a triangle, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the 1st edge scalar of the closest point to ARG5 on ARG4.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the 2nd edge scalar of the closest point to ARG5 on ARG4.
    @param [out] OUT2 Pointer to a vector with a full broadcast of the 1st barycentric coordinate of the closest point to ARG4 on ARG5.
    @param [out] OUT3 Pointer to a vector with a full broadcast of the 2nd barycentric coordinate of the closest point to ARG4 on ARG5.
    @param [in] ARG4 Pointer to a parallelogram object.
    @param [in] ARG5 Pointer to a triangle (space) object.
    @return Minimal distance between the parallelogram and triangle, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_PE_Closest_PM_ST)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_T(1,PC) OUT3, VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG4, VEC_OBJ_T(TgSTRI,CPC) ARG5 );


/* Parallelogram - Rectangle                                                                                                                                                       */

/** @brief Calculate the minimal distance squared between a parallelogram and a rectangle.
    @param [in] ARG0 Pointer to a parallelogram object.
    @param [in] ARG1 Pointer to a rectangle object.
    @return Minimal distance squared between a parallelogram and a rectangle, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_PE_DistSq_RT)(
    VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG0, VEC_OBJ_T(TgRECTANGLE,CPC) ARG1 );

/** @brief Calculate the minimal distance between a parallelogram and a rectangle.
    @param [in] ARG0 Pointer to a parallelogram object.
    @param [in] ARG1 Pointer to a rectangle object.
    @return Minimal distance between a parallelogram and a rectangle, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_PE_Dist_RT)(
    VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG0, VEC_OBJ_T(TgRECTANGLE,CPC) ARG1 );

/** @brief Calculate the minimal distance squared between a parallelogram and a rectangle, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a parallelogram object.
    @param [in] ARG3 Pointer to a rectangle object.
    @return Minimal distance squared between the parallelogram and rectangle, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_PE_ClosestSq_RT)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG2, VEC_OBJ_T(TgRECTANGLE,CPC) ARG3 );

/** @brief Calculate the minimal distance between a parallelogram and a rectangle, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a parallelogram object.
    @param [in] ARG3 Pointer to a rectangle object.
    @return Minimal distance between the parallelogram and rectangle, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_PE_Closest_RT)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG2, VEC_OBJ_T(TgRECTANGLE,CPC) ARG3 );

/** @brief Calculate the minimal distance squared between a parallelogram and a rectangle, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the 1st edge scalar of the closest point to ARG5 on ARG4.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the 2nd edge scalar of the closest point to ARG5 on ARG4.
    @param [out] OUT2 Pointer to a vector with a full broadcast of the 1st edge scalar of the closest point to ARG4 on ARG5.
    @param [out] OUT3 Pointer to a vector with a full broadcast of the 2nd edge scalar of the closest point to ARG4 on ARG5.
    @param [in] ARG4 Pointer to a parallelogram object.
    @param [in] ARG5 Pointer to a rectangle object.
    @return Minimal distance squared between the parallelogram and rectangle, or zero otherwise, broadcast across all vector lanes. */
TgEXTN VEC_T(1)
FCN_VO(tgCO_PE_ClosestSq_PM_RT)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_T(1,PC) OUT3, VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG4, VEC_OBJ_T(TgRECTANGLE,CPC) ARG5 );

/** @brief Calculate the minimal distance between a parallelogram and a rectangle, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the 1st edge scalar of the closest point to ARG5 on ARG4.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the 2nd edge scalar of the closest point to ARG5 on ARG4.
    @param [out] OUT2 Pointer to a vector with a full broadcast of the 1st edge scalar of the closest point to ARG4 on ARG5.
    @param [out] OUT3 Pointer to a vector with a full broadcast of the 2nd edge scalar of the closest point to ARG4 on ARG5.
    @param [in] ARG4 Pointer to a parallelogram object.
    @param [in] ARG5 Pointer to a rectangle object.
    @return Minimal distance between the parallelogram and rectangle, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_PE_Closest_PM_RT)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_T(1,PC) OUT3, VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG4, VEC_OBJ_T(TgRECTANGLE,CPC) ARG5 );


/* Parallelogram - Parallelogram                                                                                                                                                   */

/** @brief Calculate the minimal distance squared between a parallelogram and a parallelogram.
    @param [in] ARG0 Pointer to a parallelogram object.
    @param [in] ARG1 Pointer to a parallelogram object.
    @return Minimal distance squared between a parallelogram and a parallelogram, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_PE_DistSq_PE)(
    VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG0, VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG1 );

/** @brief Calculate the minimal distance between a parallelogram and a parallelogram.
    @param [in] ARG0 Pointer to a parallelogram object.
    @param [in] ARG1 Pointer to a parallelogram object.
    @return Minimal distance between a parallelogram and a parallelogram, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_PE_Dist_PE)(
    VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG0, VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG1 );

/** @brief Calculate the minimal distance squared between a parallelogram and a parallelogram, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a parallelogram object.
    @param [in] ARG3 Pointer to a parallelogram object.
    @return Minimal distance squared between the parallelogram and parallelogram, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_PE_ClosestSq_PE)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG2, VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG3 );

/** @brief Calculate the minimal distance between a parallelogram and a parallelogram, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG3 on ARG2.
    @param [out] OUT1 Pointer to a vector holding the closest point to ARG2 on ARG3.
    @param [in] ARG2 Pointer to a parallelogram object.
    @param [in] ARG3 Pointer to a parallelogram object.
    @return Minimal distance between the parallelogram and parallelogram, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_PE_Closest_PE)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG2, VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG3 );


/** @brief Calculate the minimal distance squared between a parallelogram and a parallelogram, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the 1st edge scalar of the closest point to ARG5 on ARG4.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the 2nd edge scalar of the closest point to ARG5 on ARG4.
    @param [out] OUT2 Pointer to a vector with a full broadcast of the 1st edge scalar of the closest point to ARG4 on ARG5.
    @param [out] OUT3 Pointer to a vector with a full broadcast of the 2nd edge scalar of the closest point to ARG4 on ARG5.
    @param [in] ARG4 Pointer to a parallelogram object.
    @param [in] ARG5 Pointer to a parallelogram object.
    @return Minimal distance squared between the parallelogram and parallelogram, or zero otherwise, broadcast across all vector lanes. */
TgEXTN VEC_T(1)
FCN_VO(tgCO_PE_ClosestSq_PM_PE)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_T(1,PC) OUT3, VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG4, VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG5 );

/** @brief Calculate the minimal distance between a parallelogram and a parallelogram, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector with a full broadcast of the 1st edge scalar of the closest point to ARG5 on ARG4.
    @param [out] OUT1 Pointer to a vector with a full broadcast of the 2nd edge scalar of the closest point to ARG5 on ARG4.
    @param [out] OUT2 Pointer to a vector with a full broadcast of the 1st edge scalar of the closest point to ARG4 on ARG5.
    @param [out] OUT3 Pointer to a vector with a full broadcast of the 2nd edge scalar of the closest point to ARG4 on ARG5.
    @param [in] ARG4 Pointer to a parallelogram object.
    @param [in] ARG5 Pointer to a parallelogram object.
    @return Minimal distance between the parallelogram and parallelogram, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_PE_Closest_PM_PE)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_T(1,PC) OUT3, VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG4, VEC_OBJ_T(TgPARALLELOGRAM,CPC) ARG5 );


/** @} TGS_COLLISION_PE */

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

    #define TGS_COLLISION_PARALLELOGRAM_H

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COLLISION_PARALLELOGRAM_H) */
#endif
