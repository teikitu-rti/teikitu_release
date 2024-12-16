/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Primitive.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_PRIMITIVE_H)
#if defined(TEMPLATE_TYPE_EXPANSION__RELOAD)

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* == Collision ================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @brief Determine the minimum distance squared between the two primitives and the corresponding two points of closest proximity. @return Result Code.
    @param [out] OUT0 Pointer to an output vector of distance squared, broadcast across all lanes.
    @param [out] OUT1 Pointer to an output vector for the point of closest proximity to PM1 on PM0.
    @param [out] OUT2 Pointer to an output vector for the point of closest proximity to PM0 on PM1.
    @param [in] ARG3 Enumeration selecting the type of primitive object in ARG4.
    @param [in] ARG4 Pointer to a collision primitive data union. The test is done inside of this object's reference frame.
    @param [in] ARG5 Enumeration selecting the type of primitive object in ARG6.
    @param [in] ARG6 Pointer to a collision primitive data union.  */
TgEXTN TgRESULT FCN_VO(tgCO_PM_ClosestSq_PM)(
    VEC_T(1,PC) TgANALYSIS_NO_NULL OUT0, VEC_T(1,PC) TgANALYSIS_NO_NULL OUT1, VEC_T(1,PC) TgANALYSIS_NO_NULL OUT2,
    ETgPM_SHORT_C ARG3, VEC_OBJ_T(UTg2_CO_Primitive,CPC) TgANALYSIS_NO_NULL ARG4,
    ETgPM_SHORT_C ARG5, VEC_OBJ_T(UTg2_CO_Primitive,CPC) TgANALYSIS_NO_NULL ARG6);

/** @brief Determine the minimum distance between the two primitives and the corresponding two points of closest proximity. @return Result Code.
    @param [out] OUT0 Pointer to an output vector of distance squared, broadcast across all lanes.
    @param [out] OUT1 Pointer to an output vector for the point of closest proximity to PM1 on PM0.
    @param [out] OUT2 Pointer to an output vector for the point of closest proximity to PM0 on PM1.
    @param [in] ARG3 Enumeration selecting the type of primitive object in ARG4.
    @param [in] ARG4 Pointer to a collision primitive data union. The test is done inside of this object's reference frame.
    @param [in] ARG5 Enumeration selecting the type of primitive object in ARG6.
    @param [in] ARG6 Pointer to a collision primitive data union.  */
TgEXTN TgRESULT FCN_VO(tgCO_PM_Closest_PM)(
    VEC_T(1,PC) TgANALYSIS_NO_NULL OUT0, VEC_T(1,PC) TgANALYSIS_NO_NULL OUT1, VEC_T(1,PC) TgANALYSIS_NO_NULL OUT2,
    ETgPM_SHORT_C ARG3, VEC_OBJ_T(UTg2_CO_Primitive,CPC) TgANALYSIS_NO_NULL ARG4,
    ETgPM_SHORT_C ARG5, VEC_OBJ_T(UTg2_CO_Primitive,CPC) TgANALYSIS_NO_NULL ARG6);

/** @brief Determine the minimum distance squared between the two primitives. @return Result Code.
    @param [out] OUT0 Pointer to an output vector of distance squared, broadcast across all lanes.
    @param [in] ARG1 Enumeration selecting the type of primitive object in ARG4.
    @param [in] ARG2 Pointer to a collision primitive data union. The test is done inside of this object's reference frame.
    @param [in] ARG3 Enumeration selecting the type of primitive object in ARG6.
    @param [in] ARG4 Pointer to a collision primitive data union.  */
TgEXTN TgRESULT FCN_VO(tgCO_PM_DistSq_PM)(
    VEC_T(1,PC) TgANALYSIS_NO_NULL OUT0,
    ETgPM_SHORT_C ARG1, VEC_OBJ_T(UTg2_CO_Primitive,CPC) TgANALYSIS_NO_NULL ARG2,
    ETgPM_SHORT_C ARG3, VEC_OBJ_T(UTg2_CO_Primitive,CPC) TgANALYSIS_NO_NULL ARG4);

/** @brief Determine the minimum distance between the two primitives. @return Result Code.
    @param [out] OUT0 Pointer to an output vector of distance squared, broadcast across all lanes.
    @param [in] ARG1 Enumeration selecting the type of primitive object in ARG4.
    @param [in] ARG2 Pointer to a collision primitive data union. The test is done inside of this object's reference frame.
    @param [in] ARG3 Enumeration selecting the type of primitive object in ARG6.
    @param [in] ARG4 Pointer to a collision primitive data union.  */
TgEXTN TgRESULT FCN_VO(tgCO_PM_Dist_PM)(
    VEC_T(1,PC) TgANALYSIS_NO_NULL OUT0, 
    ETgPM_SHORT_C ARG1, VEC_OBJ_T(UTg2_CO_Primitive,CPC) TgANALYSIS_NO_NULL ARG2,
    ETgPM_SHORT_C ARG3, VEC_OBJ_T(UTg2_CO_Primitive,CPC) TgANALYSIS_NO_NULL ARG4);

/** @brief Update the collision packet with the result of points on a primitive that are inside (penetrated) another primitive. @return Result Code.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG2.
                         Contact normal is the surface normal at the contact point on ARG2.
    @param [in] ARG1 Enumeration selecting the type of primitive object in ARG2.
    @param [in] ARG2 Pointer to a collision primitive data union. The test is done inside of this object's reference frame.
    @param [in] ARG3 Enumeration selecting the type of primitive object in ARG4.
    @param [in] ARG4 Pointer to a collision primitive data union. */
TgEXTN TgRESULT
FCN_VO(tgCO_PM_Penetrate_PM)(
    VEC_OBJ_T(STg2_CO_Packet,PC) TgANALYSIS_NO_NULL OUT0, ETgPM_SHORT_C ARG1, VEC_OBJ_T(UTg2_CO_Primitive,CPC) TgANALYSIS_NO_NULL ARG2, ETgPM_SHORT_C ARG3,
    VEC_OBJ_T(UTg2_CO_Primitive,CPC) TgANALYSIS_NO_NULL ARG4 );

/** @brief Update the collision packet with the result of sweeping a primitive versus an other primitive.
    @param [in] ARG0 Enumeration selecting the type of primitive object for the 1st object.
    @param [in] ARG1 Enumeration selecting the type of primitive object for the 2nd object.
    @return True if the test is supported and false otherwise. */
TgEXTN TgBOOL
FCN_VO(tgCO_PM_Sweep_PM_Supported)(
    ETgPM_SHORT_C ARG0, ETgPM_SHORT_C ARG1 );

/** @brief Update the collision packet with the result of sweeping a primitive versus an other primitive. @return Result Code.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG3.
                         Contact normal is the surface normal at the contact point on ARG3.
    @param [in,out] OUT1 Pointer to a vector with a full broadcast of the normalized time of contact (percentage of time step).
    @param [in] ARG2 Enumeration selecting the type of primitive object in ARG3.
    @param [in] ARG3 Pointer to a collision primitive data union. The test is done inside of this object's reference frame.
    @param [in] ARG4 Enumeration selecting the type of primitive object in ARG5.
    @param [in] ARG5 Pointer to a collision primitive data union.
    @param [in] ARG6 Pointer to an object holding displacement values for ARG5. */
TgEXTN TgRESULT
FCN_VO(tgCO_PM_Sweep_PM)(
    VEC_OBJ_T(STg2_CO_Packet, PC) TgANALYSIS_NO_NULL OUT0, VEC_T(1,PC) TgANALYSIS_NO_NULL OUT1, ETgPM_SHORT_C ARG2, VEC_OBJ_T(UTg2_CO_Primitive,CPC) TgANALYSIS_NO_NULL ARG3,
    ETgPM_SHORT_C ARG4, VEC_OBJ_T(UTg2_CO_Primitive,CPC) TgANALYSIS_NO_NULL ARG5, VEC_OBJ_T(TgDELTA,CPC) TgANALYSIS_NO_NULL ARG6);

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

#define TGS_COLLISION_PRIMITIVE_H

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif

/* =============================================================================================================================================================================== */

/*# !defined(TGS_COLLISION_PRIMITIVE_H) */
#endif
