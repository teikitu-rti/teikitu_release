/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Tube.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_TUBE_H)
#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* == Collision ================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions - Scalar Functions                                                                                                                                            */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @addtogroup TGS_COLLISION_TB */
/** @{ */

/* Tube - Line                                                                                                                                                                     */

/** @brief Update the collision packet with point(s) of intersection between a tube and a line
    @param [in,out] OUT0 Pointer to an object holding parameters and existing intersection points
    @param [in] ARG1 Pointer to a tube object
    @param [in] ARG2 Pointer to a line object
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_TB_Intersect_LN)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgTUBE,CPC) ARG1, VEC_OBJ_T(TgLINE,CPC) ARG2 );

/** @brief Output the two points formed by clipping a line to the interior of the tube (or report a fail result)
    @param [out] OUT0 Pointer to a vector holding the parametric value for the 1st point of intersection, broadcast across all lanes
    @param [out] OUT1 Pointer to a vector holding the parametric value for the 2nd point of intersection, broadcast across all lanes
    @param [in] ARG2 Pointer to a tube object
    @param [in] ARG3 Pointer to a line object
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_TB_Clip_PM_LN)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgTUBE,CPC) ARG2, VEC_OBJ_T(TgLINE,CPC) ARG3 );

/** @brief Fill a clip list by clipping the line to the interior of the tube
    @param [out] OUT0 Pointer to a clip list object
    @param [in] ARG1 Pointer to a tube object
    @param [in] ARG2 Pointer to a line object
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_TB_Clip_LN)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, VEC_OBJ_T(TgTUBE,CPC) ARG1, VEC_OBJ_T(TgLINE,CPC) ARG2 );

/** @brief Output the two points formed by clipping a line to the interior of the tube (or report a fail result)
    @param [out] OUT0 Pointer to a vector holding the parametric value for the 1st point of intersection, broadcast across all lanes
    @param [out] OUT1 Pointer to a vector holding the parametric value for the 2nd point of intersection, broadcast across all lanes
    @param [in] ARG2 Pointer to a tube object
    @param [in] ARG3 Vector holding the Line Origin
    @param [in] ARG4 Vector holding the Line Direction
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_TB_Clip_PM_LR00)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgTUBE,CPC) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4 );

/** @brief Output the two points formed by clipping a line to the interior of the tube (or report a fail result)
    @param [out] OUT0 Pointer to a clip list object
    @param [in] ARG1 Pointer to a tube object
    @param [in] ARG2 Vector holding the Line Origin
    @param [in] ARG3 Vector holding the Line Direction
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_TB_Clip_LR00)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, VEC_OBJ_T(TgTUBE,CPC) ARG1, VEC_T(1,C) ARG2, VEC_T(1,C) ARG3 );

/** @brief Update the collision packet with point(s) of intersection between a tube (infinite in both directions) and a line
    @param [in,out] OUT0 Pointer to an object holding parameters and existing intersection points
    @param [in] ARG1 Vector holding the radius to be used for the line, broadcast across all lanes 
    @param [in] ARG2 Pointer to a tube object
    @param [in] ARG3 Vector holding the Line Origin
    @param [in] ARG4 Vector holding the Line Direction
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_TB00_Intersect_LR00)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_T(1,C) ARG1, VEC_OBJ_T(TgTUBE,CPC) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4 );

/** @brief Update the collision packet with point(s) of intersection between a tube (infinite in direction of the axis) and a line
    @param [in,out] OUT0 Pointer to an object holding parameters and existing intersection points
    @param [in] ARG1 Vector holding the radius to be used for the line, broadcast across all lanes 
    @param [in] ARG2 Pointer to a tube object
    @param [in] ARG3 Vector holding the Line Origin
    @param [in] ARG4 Vector holding the Line Direction
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_TB10_Intersect_LR00)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_T(1,C) ARG1, VEC_OBJ_T(TgTUBE,CPC) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4 );

/** @brief Update the collision packet with point(s) of intersection between a tube (finite in both directions) and a line
    @param [in,out] OUT0 Pointer to an object holding parameters and existing intersection points
    @param [in] ARG1 Vector holding the radius to be used for the line, broadcast across all lanes 
    @param [in] ARG2 Pointer to a tube object
    @param [in] ARG3 Vector holding the Line Origin
    @param [in] ARG4 Vector holding the Line Direction
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_TB11_Intersect_LR00)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_T(1,C) ARG1, VEC_OBJ_T(TgTUBE,CPC) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4 );

/** @brief Update the collision packet with point(s) of intersection between a tube (infinite in both directions) and a line
    @param [out] OUT0 Pointer to a vector holding the parametric value for the 1st point of intersection, broadcast across all lanes
    @param [out] OUT1 Pointer to a vector holding the parametric value for the 2nd point of intersection, broadcast across all lanes
    @param [out] OUT2 Pointer to a vector for 1st normal at point of intersection on the tube surface
    @param [out] OUT3 Pointer to a vector for 2nd normal at point of intersection on the tube surface
    @param [in] ARG4 Vector holding the radius to be used for the line, broadcast across all lanes 
    @param [in] ARG5 Pointer to a tube object
    @param [in] ARG6 Vector holding the Line Origin
    @param [in] ARG7 Vector holding the Line Direction
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_TB00_Param_LR00)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_T(1,PC) OUT3, VEC_T(1,C) ARG4, VEC_OBJ_T(TgTUBE,CPC) ARG5, VEC_T(1,C) ARG6, VEC_T(1,C) ARG7 );

/** @brief Update the collision packet with point(s) of intersection between a tube (finite in both directions) and a line
    @param [out] OUT0 Pointer to a vector holding the parametric value for the 1st point of intersection, broadcast across all lanes
    @param [out] OUT1 Pointer to a vector holding the parametric value for the 2nd point of intersection, broadcast across all lanes
    @param [out] OUT2 Pointer to a vector for 1st normal at point of intersection on the tube surface
    @param [out] OUT3 Pointer to a vector for 2nd normal at point of intersection on the tube surface
    @param [in] ARG4 Vector holding the radius to be used for the line, broadcast across all lanes 
    @param [in] ARG5 Pointer to a tube object
    @param [in] ARG6 Vector holding the Line Origin
    @param [in] ARG7 Vector holding the Line Direction
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_TB10_Param_LR00)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_T(1,PC) OUT3, VEC_T(1,C) ARG4, VEC_OBJ_T(TgTUBE,CPC) ARG5, VEC_T(1,C) ARG6, VEC_T(1,C) ARG7 );

/** @brief Update the collision packet with point(s) of intersection between a tube (finite in both directions) and a line
    @param [out] OUT0 Pointer to a vector holding the parametric value for the 1st point of intersection, broadcast across all lanes
    @param [out] OUT1 Pointer to a vector holding the parametric value for the 2nd point of intersection, broadcast across all lanes
    @param [out] OUT2 Pointer to a vector for 1st normal at point of intersection on the tube surface
    @param [out] OUT3 Pointer to a vector for 2nd normal at point of intersection on the tube surface
    @param [in] ARG4 Vector holding the radius to be used for the line, broadcast across all lanes 
    @param [in] ARG5 Pointer to a tube object
    @param [in] ARG6 Vector holding the Line Origin
    @param [in] ARG7 Vector holding the Line Direction
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_TB11_Param_LR00)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_T(1,PC) OUT3, VEC_T(1,C) ARG4, VEC_OBJ_T(TgTUBE,CPC) ARG5, VEC_T(1,C) ARG6, VEC_T(1,C) ARG7 );


/* Tube - Ray                                                                                                                                                                      */

/** @brief Update the collision packet with point(s) of intersection between a tube and a ray
    @param [in,out] OUT0 Pointer to an object holding parameters and existing intersection points
    @param [in] ARG1 Pointer to a tube object
    @param [in] ARG2 Pointer to a ray object
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_TB_Intersect_RY)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgTUBE,CPC) ARG1, VEC_OBJ_T(TgRAY,CPC) ARG2 );

/** @brief Output the two points formed by clipping a ray to the interior of the tube (or report a fail result)
    @param [out] OUT0 Pointer to a vector holding the parametric value for the 1st point of intersection, broadcast across all lanes
    @param [out] OUT1 Pointer to a vector holding the parametric value for the 2nd point of intersection, broadcast across all lanes
    @param [in] ARG2 Pointer to a tube object
    @param [in] ARG3 Pointer to a ray object
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_TB_Clip_PM_RY)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgTUBE,CPC) ARG2, VEC_OBJ_T(TgRAY,CPC) ARG3 );

/** @brief Fill a clip list by clipping the ray to the interior of the tube
    @param [out] OUT0 Pointer to a clip list object
    @param [in] ARG1 Pointer to a tube object
    @param [in] ARG2 Pointer to a ray object
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_TB_Clip_RY)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, VEC_OBJ_T(TgTUBE,CPC) ARG2, VEC_OBJ_T(TgRAY,CPC) ARG3 );

/** @brief Output the two points formed by clipping a ray to the interior of the tube (or report a fail result)
    @param [out] OUT0 Pointer to a vector holding the parametric value for the 1st point of intersection, broadcast across all lanes
    @param [out] OUT1 Pointer to a vector holding the parametric value for the 2nd point of intersection, broadcast across all lanes
    @param [in] ARG2 Pointer to a tube object
    @param [in] ARG3 Vector holding the Ray Origin
    @param [in] ARG4 Vector holding the Ray Direction
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_TB_Clip_PM_LR10)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgTUBE,CPC) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4 );

/** @brief Output the two points formed by clipping a ray to the interior of the tube (or report a fail result)
    @param [out] OUT0 Pointer to a clip list object
    @param [in] ARG1 Pointer to a tube object
    @param [in] ARG2 Vector holding the Ray Origin
    @param [in] ARG3 Vector holding the Ray Direction
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_TB_Clip_LR10)(
     VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, VEC_OBJ_T(TgTUBE,CPC) ARG1, VEC_T(1,C) ARG2, VEC_T(1,C) ARG3 );

/** @brief Update the collision packet with point(s) of intersection between a tube (infinite in both directions) and a ray
    @param [in,out] OUT0 Pointer to an object holding parameters and existing intersection points
    @param [in] ARG1 Vector holding the radius to be used for the ray, broadcast across all lanes 
    @param [in] ARG2 Pointer to a tube object
    @param [in] ARG3 Vector holding the Ray Origin
    @param [in] ARG4 Vector holding the Ray Direction
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_TB00_Intersect_LR10)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_T(1,C) ARG1, VEC_OBJ_T(TgTUBE,CPC) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4 );

/** @brief Update the collision packet with point(s) of intersection between a tube (infinite in direction of the axis) and a ray
    @param [in,out] OUT0 Pointer to an object holding parameters and existing intersection points
    @param [in] ARG1 Vector holding the radius to be used for the ray, broadcast across all lanes 
    @param [in] ARG2 Pointer to a tube object
    @param [in] ARG3 PVector holding the Ray Origin
    @param [in] ARG4 Vector holding the Ray Direction
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_TB10_Intersect_LR10)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_T(1,C) ARG1, VEC_OBJ_T(TgTUBE,CPC) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4 );

/** @brief Update the collision packet with point(s) of intersection between a tube (finite in both directions) and a ray
    @param [in,out] OUT0 Pointer to an object holding parameters and existing intersection points
    @param [in] ARG1 Vector holding the radius to be used for the ray, broadcast across all lanes 
    @param [in] ARG2 Pointer to a tube object
    @param [in] ARG3 Vector holding the Ray Origin
    @param [in] ARG4 Vector holding the Ray Direction
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_TB11_Intersect_LR10)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_T(1,C) ARG1, VEC_OBJ_T(TgTUBE,CPC) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4 );

/** @brief Update the collision packet with point(s) of intersection between a tube (infinite in both directions) and a ray
    @param [out] OUT0 Pointer to a vector holding the parametric value for the 1st point of intersection, broadcast across all lanes
    @param [out] OUT1 Pointer to a vector holding the parametric value for the 2nd point of intersection, broadcast across all lanes
    @param [out] OUT2 Pointer to a vector for 1st normal at point of intersection on the tube surface
    @param [out] OUT3 Pointer to a vector for 2nd normal at point of intersection on the tube surface
    @param [in] ARG4 Vector holding the radius to be used for the ray, broadcast across all lanes 
    @param [in] ARG5 Pointer to a tube object
    @param [in] ARG6 Vector holding the Ray Origin
    @param [in] ARG7 Vector holding the Ray Direction
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_TB00_Param_LR10)( 
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_T(1,PC) OUT3, VEC_T(1,C) ARG4, VEC_OBJ_T(TgTUBE,CPC) ARG5, VEC_T(1,C) ARG6, VEC_T(1,C) ARG7 );

/** @brief Update the collision packet with point(s) of intersection between a tube (finite in both directions) and a ray
    @param [out] OUT0 Pointer to a vector holding the parametric value for the 1st point of intersection, broadcast across all lanes
    @param [out] OUT1 Pointer to a vector holding the parametric value for the 2nd point of intersection, broadcast across all lanes
    @param [out] OUT2 Pointer to a vector for 1st normal at point of intersection on the tube surface
    @param [out] OUT3 Pointer to a vector for 2nd normal at point of intersection on the tube surface
    @param [in] ARG4 Vector holding the radius to be used for the ray, broadcast across all lanes 
    @param [in] ARG5 Pointer to a tube object
    @param [in] ARG6 Vector holding the Ray Origin
    @param [in] ARG7 Vector holding the Ray Direction
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_TB10_Param_LR10)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_T(1,PC) OUT3, VEC_T(1,C) ARG4, VEC_OBJ_T(TgTUBE,CPC) ARG5, VEC_T(1,C) ARG6, VEC_T(1,C) ARG7 );

/** @brief Update the collision packet with point(s) of intersection between a tube (finite in both directions) and a ray
    @param [out] OUT0 Pointer to a vector holding the parametric value for the 1st point of intersection, broadcast across all lanes
    @param [out] OUT1 Pointer to a vector holding the parametric value for the 2nd point of intersection, broadcast across all lanes
    @param [out] OUT2 Pointer to a vector for 1st normal at point of intersection on the tube surface
    @param [out] OUT3 Pointer to a vector for 2nd normal at point of intersection on the tube surface
    @param [in] ARG4 Vector holding the radius to be used for the ray, broadcast across all lanes 
    @param [in] ARG5 Pointer to a tube object
    @param [in] ARG6 Vector holding the Ray Origin
    @param [in] ARG7 Vector holding the Ray Direction
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_TB11_Param_LR10)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_T(1,PC) OUT3, VEC_T(1,C) ARG4, VEC_OBJ_T(TgTUBE,CPC) ARG5, VEC_T(1,C) ARG6, VEC_T(1,C) ARG7 );


/* Tube - Segment                                                                                                                                                                  */

/** @brief Update the collision packet with point(s) of intersection between a tube and a segment
    @param [in,out] OUT0 Pointer to an object holding parameters and existing intersection points
    @param [in] ARG1 Pointer to a tube object
    @param [in] ARG2 Pointer to a segment object
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_TB_Intersect_SG)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgTUBE,CPC) ARG1, VEC_OBJ_T(TgSEGMENT,CPC) ARG2 );

/** @brief Output the two points formed by clipping a segment to the interior of the tube (or report a fail result)
    @param [out] OUT0 Pointer to a vector holding the parametric value for the 1st point of intersection, broadcast across all lanes
    @param [out] OUT1 Pointer to a vector holding the parametric value for the 2nd point of intersection, broadcast across all lanes
    @param [in] ARG2 Pointer to a tube object
    @param [in] ARG3 Pointer to a segment object
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_TB_Clip_PM_SG)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgTUBE,CPC) ARG2, VEC_OBJ_T(TgSEGMENT,CPC) ARG3 );

/** @brief Fill a clip list by clipping the segment to the interior of the tube
    @param [out] OUT0 Pointer to a clip list object
    @param [in] ARG1 Pointer to a tube object
    @param [in] ARG2 Pointer to a segment object
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_TB_Clip_SG)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, VEC_OBJ_T(TgTUBE,CPC) ARG1, VEC_OBJ_T(TgSEGMENT,CPC) ARG2 );

/** @brief Output the two points formed by clipping a segment to the interior of the tube (or report a fail result)
    @param [out] OUT0 Pointer to a vector holding the parametric value for the 1st point of intersection, broadcast across all lanes
    @param [out] OUT1 Pointer to a vector holding the parametric value for the 2nd point of intersection, broadcast across all lanes
    @param [in] ARG2 Pointer to a tube object
    @param [in] ARG3 Vector holding the Segment Origin
    @param [in] ARG4 Vector holding the position relative to the Segment Origin of the Segment Terminal Point
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_TB_Clip_PM_LR11)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgTUBE,CPC) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4 );

/** @brief Output the two points formed by clipping a segment to the interior of the tube (or report a fail result)
    @param [out] OUT0 Pointer to a clip list object
    @param [in] ARG1 Pointer to a tube object
    @param [in] ARG2 Vector holding the Segment Origin
    @param [in] ARG3 Vector holding the position relative to the Segment Origin of the Segment Terminal Point
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_TB_Clip_LR11)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC) OUT0, VEC_OBJ_T(TgTUBE,CPC) ARG1, VEC_T(1,C) ARG2, VEC_T(1,C) ARG3 );

/** @brief Update the collision packet with point(s) of intersection between a tube (infinite in direction of the axis) and a segment
    @param [in,out] OUT0 Pointer to an object holding parameters and existing intersection points
    @param [in] ARG1 Vector holding the radius to be used for the segment, broadcast across all lanes 
    @param [in] ARG2 Pointer to a tube object
    @param [in] ARG3 Vector holding the Segment Origin
    @param [in] ARG4 Vector holding the position relative to the Segment Origin of the Segment Terminal Point
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_TB00_Intersect_LR11)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_T(1,C) ARG1, VEC_OBJ_T(TgTUBE,CPC) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4 );

/** @brief Update the collision packet with point(s) of intersection between a tube (infinite in direction of the axis) and a ray
    @param [in,out] OUT0 Pointer to an object holding parameters and existing intersection points
    @param [in] ARG1 Vector holding the radius to be used for the segment, broadcast across all lanes 
    @param [in] ARG2 Pointer to a tube object
    @param [in] ARG3 Vector holding the Segment Origin
    @param [in] ARG4 Vector holding the position relative to the Segment Origin of the Segment Terminal Point
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_TB10_Intersect_LR11)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_T(1,C) ARG1, VEC_OBJ_T(TgTUBE,CPC) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4 );

/** @brief Update the collision packet with point(s) of intersection between a tube (finite in both directions) and a segment
    @param [in,out] OUT0 Pointer to an object holding parameters and existing intersection points
    @param [in] ARG1 Vector holding the radius to be used for the segment, broadcast across all lanes 
    @param [in] ARG2 Pointer to a tube object
    @param [in] ARG3 Vector holding the Segment Origin
    @param [in] ARG4 Vector holding the position relative to the Segment Origin of the Segment Terminal Point
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_TB11_Intersect_LR11)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_T(1,C) ARG1, VEC_OBJ_T(TgTUBE,CPC) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4 );

/** @brief Update the collision packet with point(s) of intersection between a tube (infinite in both directions) and a segment
    @param [out] OUT0 Pointer to a vector holding the parametric value for the 1st point of intersection, broadcast across all lanes
    @param [out] OUT1 Pointer to a vector holding the parametric value for the 2nd point of intersection, broadcast across all lanes
    @param [out] OUT2 Pointer to a vector for 1st normal at point of intersection on the tube surface
    @param [out] OUT3 Pointer to a vector for 2nd normal at point of intersection on the tube surface
    @param [in] ARG4 Vector holding the radius to be used for the segment, broadcast across all lanes 
    @param [in] ARG5 Pointer to a tube object
    @param [in] ARG6 Vector holding the Segment Origin
    @param [in] ARG7 Vector holding the position relative to the Segment Origin of the Segment Terminal Point
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_TB00_Param_LR11)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_T(1,PC) OUT3, VEC_T(1,C) ARG4, VEC_OBJ_T(TgTUBE,CPC) ARG5, VEC_T(1,C) ARG6, VEC_T(1,C) ARG7 );

/** @brief Update the collision packet with point(s) of intersection between a tube (finite in both directions) and a segment
    @param [out] OUT0 Pointer to a vector holding the parametric value for the 1st point of intersection, broadcast across all lanes
    @param [out] OUT1 Pointer to a vector holding the parametric value for the 2nd point of intersection, broadcast across all lanes
    @param [out] OUT2 Pointer to a vector for 1st normal at point of intersection on the tube surface
    @param [out] OUT3 Pointer to a vector for 2nd normal at point of intersection on the tube surface
    @param [in] ARG4 Vector holding the radius to be used for the segment, broadcast across all lanes 
    @param [in] ARG5 Pointer to a tube object
    @param [in] ARG6 Vector holding the Segment Origin
    @param [in] ARG7 Vector holding the position relative to the Segment Origin of the Segment Terminal Point
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_TB10_Param_LR11)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_T(1,PC) OUT3, VEC_T(1,C) ARG4, VEC_OBJ_T(TgTUBE,CPC) ARG5, VEC_T(1,C) ARG6, VEC_T(1,C) ARG7 );

/** @brief Update the collision packet with point(s) of intersection between a tube (finite in both directions) and a segment
    @param [out] OUT0 Pointer to a vector holding the parametric value for the 1st point of intersection, broadcast across all lanes
    @param [out] OUT1 Pointer to a vector holding the parametric value for the 2nd point of intersection, broadcast across all lanes
    @param [out] OUT2 Pointer to a vector for 1st normal at point of intersection on the tube surface
    @param [out] OUT3 Pointer to a vector for 2nd normal at point of intersection on the tube surface
    @param [in] ARG4 Vector holding the radius to be used for the segment, broadcast across all lanes 
    @param [in] ARG5 Pointer to a tube object
    @param [in] ARG6 Vector holding the Segment Origin
    @param [in] ARG7 Vector holding the position relative to the Segment Origin of the Segment Terminal Point
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_TB11_Param_LR11)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,PC) OUT2, VEC_T(1,PC) OUT3, VEC_T(1,C) ARG4, VEC_OBJ_T(TgTUBE,CPC) ARG5, VEC_T(1,C) ARG6, VEC_T(1,C) ARG7 );


/* Tube - Sphere                                                                                                                                                                   */

/** @brief Collision of a swept tube versus a static tube.
    @internal This is a highly inaccurate test, meant to be used mainly as a child function for the cylinder, and capsule routines. Problems will rest in its false negative
              responses at values beyond the tube's length.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG2
                         Contact normal is the surface normal at the contact point on ARG2
    @param [in,out] OUT1 Pointer to a vector with a full broadcast of the normalized time of contact (percentage of time step).
    @param [in] ARG2 Pointer to a tube object. The test is done inside of this object's reference frame
    @param [in] ARG3 Pointer to a sphere object
    @param [in] ARG4 Pointer to an object holding displacement values for ARG3
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_TB_Sweep_SP)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgTUBE,CPC) ARG2, VEC_OBJ_T(TgSPHERE,CPC) ARG3, VEC_OBJ_T(TgDELTA,CPC) ARG4 );

/** @brief Collision of a swept tube versus a static tube
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG2
                         Contact normal is the surface normal at the contact point on ARG2
    @param [in,out] OUT1 Pointer to a vector with a full broadcast of the normalized time of contact (percentage of time step).
    @param [in] ARG2 Pointer to a sphere object. The test is done inside of this object's reference frame
    @param [in] ARG3 Pointer to a tube object
    @param [in] ARG4 Pointer to an object holding displacement values for ARG3
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_SP_Sweep_TB)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgSPHERE,CPC) ARG2, VEC_OBJ_T(TgTUBE,CPC) ARG3, VEC_OBJ_T(TgDELTA,CPC) ARG4 );


/* Tube - Tube                                                                                                                                                                     */

/** @brief Collision of a swept tube versus a static tube
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG2
                         Contact normal is the surface normal at the contact point on ARG2
    @param [in,out] OUT1 Pointer to a vector with a full broadcast of the normalized time of contact (percentage of time step).
    @param [in] ARG2 Pointer to a tube object. The test is done inside of this object's reference frame.
    @param [in] ARG3 Pointer to a tube object
    @param [in] ARG4 Pointer to an object holding displacement values for ARG3
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_TB_Sweep_TB)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgTUBE,CPC) ARG2, VEC_OBJ_T(TgTUBE,CPC) ARG3, VEC_OBJ_T(TgDELTA,CPC) ARG4 );


/** @} TGS_COLLISION_TB */

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

    #define TGS_COLLISION_TUBE_H

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COLLISION_TUBE_H) */
#endif
