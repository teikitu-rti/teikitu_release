/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Box AA.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_BOX_AA_H)
#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* == Collision ================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @addtogroup TGS_COLLISION_BA */
/** @{ */

/* ---- Box AA - Point ----------------------------------------------------------------------------------------------------------------------------------------------------------- */

/** @brief Calculate the minimal distance squared between an axis-aligned box and a point.
    @param [in] ARG0 Pointer to an axis-aligned box object.
    @param [in] ARG1 Vector holding a position (point).
    @return Minimal distance squared between an axis-aligned box and a point, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_BA_DistSq_PT)(
    VEC_OBJ_T(TgBOXAA,CPC) ARG0, VEC_T(1,C) ARG1 );

/** @brief Calculate the minimal distance between an axis-aligned box and a point.
    @param [in] ARG0 Pointer to an axis-aligned box object.
    @param [in] ARG1 Vector holding a position (point).
    @return Minimal distance between an axis-aligned box and a point, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_BA_Dist_PT)(
    VEC_OBJ_T(TgBOXAA,CPC) ARG0, VEC_T(1,C) ARG1 );

/** @brief Calculate the minimal distance squared between an axis-aligned box and a point, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG2 on ARG1.
    @param [in] ARG1 Pointer to an axis-aligned box object.
    @param [in] ARG2 Vector holding a position (point).
    @return Minimal distance squared between an axis-aligned box and a point, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_BA_ClosestSq_PT)(
    VEC_T(1,PC) OUT0, VEC_OBJ_T(TgBOXAA,CPC) ARG1, VEC_T(1,C) ARG2 );

/** @brief Calculate the minimal distance between an axis-aligned box and a point, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG2 on ARG1.
    @param [in] ARG1 Pointer to an axis-aligned box object.
    @param [in] ARG2 Vector holding a position (point).
    @return Minimal distance between an axis-aligned box and a point, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_BA_Closest_PT)(
    VEC_T(1,PC) OUT0, VEC_OBJ_T(TgBOXAA,CPC) ARG1, VEC_T(1,C) ARG2 );


/** @brief Determine if the two primitives are intersecting.
    @param [in] ARG0 Pointer to an axis-aligned box object.
    @param [in] ARG1 Vector holding a position (point).
    @return True if the two primitives are intersecting, and false otherwise. */
TgINLINE TgBOOL
FCN_VO(tgCO_BA_Test_PT)(
    VEC_OBJ_T(TgBOXAA,CPC) ARG0, VEC_T(1,C) ARG1 );




/* ---- Box AA - Linear ---------------------------------------------------------------------------------------------------------------------------------------------------------- */

/** @brief Determine if the two primitives are intersecting.
    @param [in] ARG0 Pointer to an axis-aligned box object.
    @param [in] ARG1 Vector holding the Line Origin.
    @param [in] ARG2 Vector holding the Line Direction.
    @return True if the two primitives are intersecting, and false otherwise. */
TgEXTN TgBOOL
FCN_VO(tgCO_BA_Test_LR00)(
    VEC_OBJ_T(TgBOXAA,CPC) ARG0, VEC_T(1,C) ARG1, VEC_T(1,C) ARG2 );

/** @brief Determine if the two primitives are intersecting.
    @param [in] ARG0 Pointer to an axis-aligned box object.
    @param [in] ARG1 Vector holding the Ray Origin.
    @param [in] ARG2 Vector holding the Ray Direction.
    @return True if the two primitives are intersecting, and false otherwise. */
TgEXTN TgBOOL
FCN_VO(tgCO_BA_Test_LR10)(
    VEC_OBJ_T(TgBOXAA,CPC) ARG0, VEC_T(1,C) ARG1, VEC_T(1,C) ARG2 );

/** @brief Determine if the two primitives are intersecting.
    @param [in] ARG0 Pointer to an axis-aligned box object.
    @param [in] ARG1 Vector holding the Segment Origin.
    @param [in] ARG2 Vector holding the position relative to the Segment Origin of the Segment Terminal Point.
    @return True if the two primitives are intersecting, and false otherwise. */
TgEXTN TgBOOL
FCN_VO(tgCO_BA_Test_LR11)(
    VEC_OBJ_T(TgBOXAA,CPC) ARG0, VEC_T(1,C) ARG1, VEC_T(1,C) ARG2 );




/* ---- Box AA - Sphere ---------------------------------------------------------------------------------------------------------------------------------------------------------- */

/** @brief Calculate the minimal distance squared between an axis-aligned box and a sphere.
    @param [in] ARG0 Pointer to an axis-aligned box object.
    @param [in] ARG1 Pointer to a sphere object.
    @return Minimal distance squared between an axis-aligned box and a sphere, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_BA_DistSq_SP)(
    VEC_OBJ_T(TgBOXAA,CPC) ARG0, VEC_OBJ_T(TgSPHERE,CPC) ARG1 );

/** @brief Calculate the minimal distance between an axis-aligned box and a sphere.
    @param [in] ARG0 Pointer to an axis-aligned box object.
    @param [in] ARG1 Pointer to a sphere object.
    @return Minimal distance between an axis-aligned box and a sphere, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_BA_Dist_SP)(
    VEC_OBJ_T(TgBOXAA,CPC) ARG0, VEC_OBJ_T(TgSPHERE,CPC) ARG1 );

/** @brief Calculate the minimal distance squared between an axis-aligned box and a sphere, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG2 on ARG1.
    @param [in] ARG1 Pointer to an axis-aligned box object.
    @param [in] ARG2 Pointer to a sphere object.
    @return Minimal distance squared between an axis-aligned box and a sphere, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_BA_ClosestSq_SP)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgBOXAA,CPC) ARG2, VEC_OBJ_T(TgSPHERE,CPC) ARG3 );

/** @brief Calculate the minimal distance between an axis-aligned box and a sphere, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG2 on ARG1.
    @param [in] ARG1 Pointer to an axis-aligned box object.
    @param [in] ARG2 Pointer to a sphere object.
    @return Minimal distance between an axis-aligned box and a sphere, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_BA_Closest_SP)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgBOXAA,CPC) ARG2, VEC_OBJ_T(TgSPHERE,CPC) ARG3 );


/** @brief Determine if the two primitives are intersecting.
    @param [in] ARG1 Pointer to an axis-aligned box object.
    @param [in] ARG2 Pointer to a sphere object.
    @return True if the two primitives are intersecting, and false otherwise. */
TgINLINE TgBOOL
FCN_VO(tgCO_BA_Test_SP)(
    VEC_OBJ_T(TgBOXAA,CPC) ARG0, VEC_OBJ_T(TgSPHERE,CPC) ARG1 );


/** @brief Update the collision packet with point(s) of penetration between an axis-aligned box and a sphere.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG2.
                         Contact normals are the direction for the object at ARG2 to move to achieve separation.
                         Depth values are measured from the surface of the object at ARG1 to the contact point.
    @param [in] ARG1 Pointer to an axis-aligned box object.
    @param [in] ARG2 Pointer to a sphere object.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_BA_Penetrate_SP)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgBOXAA,CPC) ARG1, VEC_OBJ_T(TgSPHERE,CPC) ARG2 );

/** @brief Update the collision packet with point(s) of penetration between an axis-aligned box and a sphere.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG2.
                         Contact normals are the direction for the object at ARG2 to move to achieve separation.
                         Depth values are measured from the surface of the object at ARG1 to the contact point.
    @param [in] ARG1 Pointer to a sphere object.
    @param [in] ARG2 Pointer to an axis-aligned box object.
    @return Result Code. */
TgINLINE TgRESULT
FCN_VO(tgCO_SP_Penetrate_BA)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgSPHERE,CPC) ARG1, VEC_OBJ_T(TgBOXAA,CPC) ARG2 );




/* ---- Box AA - Box AA ---------------------------------------------------------------------------------------------------------------------------------------------------------- */

/** @brief Calculate the minimal distance squared between two axis-aligned boxes.
    @param [in] ARG0 Pointer to an axis-aligned box object.
    @param [in] ARG1 Pointer to an axis-aligned box object.
    @return Minimal distance squared between two axis-aligned boxes, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_BA_DistSq_BA)(
    VEC_OBJ_T(TgBOXAA,CPC) ARG0, VEC_OBJ_T(TgBOXAA,CPC) ARG1 );

/** @brief Calculate the minimal distance between two axis-aligned boxes.
    @param [in] ARG0 Pointer to an axis-aligned box object.
    @param [in] ARG1 Pointer to an axis-aligned box object.
    @return Minimal distance between two axis-aligned boxes, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_BA_Dist_BA)(
    VEC_OBJ_T(TgBOXAA,CPC) ARG0, VEC_OBJ_T(TgBOXAA,CPC) ARG1 );

/** @brief Calculate the minimal distance squared between two axis-aligned boxes, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG2 on ARG1.
    @param [in] ARG1 Pointer to an axis-aligned box object.
    @param [in] ARG2 Pointer to an axis-aligned box object.
    @return Minimal distance squared between two axis-aligned boxes, or zero otherwise, broadcast across all vector lanes. */
TgEXTN VEC_T(1)
FCN_VO(tgCO_BA_ClosestSq_BA)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgBOXAA,CPC) ARG2, VEC_OBJ_T(TgBOXAA,CPC) ARG3 );

/** @brief Calculate the minimal distance between two axis-aligned boxes, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG2 on ARG1.
    @param [in] ARG1 Pointer to an axis-aligned box object.
    @param [in] ARG2 Pointer to an axis-aligned box object.
    @return Minimal distance between two axis-aligned boxes, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_BA_Closest_BA)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgBOXAA,CPC) ARG2, VEC_OBJ_T(TgBOXAA,CPC) ARG3 );


/** @brief Determine if the two primitives will touch due to the displacement.
    @param [in] ARG0 Pointer to an axis-aligned box object.
    @param [in] ARG1 Pointer to an axis-aligned box object.
    @param [in] ARG2 Vector holding the normalized direction of displacement.
    @param [in] ARG3 Vector holding a full broadcast of the magnitude of the displacement.
    @return True if the two primitives are intersecting, and false otherwise. */
TgINLINE TgBOOL
FCN_VO(tgCO_BA_Sweep_Test_BA)(
    VEC_OBJ_T(TgBOXAA,CPC) ARG0, VEC_OBJ_T(TgBOXAA,CPC) ARG1, VEC_T(1,C) ARG2, VEC_T(1,C) ARG3 );

/** @brief Determine if the two primitives are intersecting.
    @param [in] ARG1 Pointer to an axis-aligned box object.
    @param [in] ARG2 Pointer to an axis-aligned box object.
    @return True if the two primitives are intersecting, and false otherwise. */
TgINLINE TgBOOL
FCN_VO(tgCO_BA_Test_BA)(
    VEC_OBJ_T(TgBOXAA,CPC) ARG0, VEC_OBJ_T(TgBOXAA,CPC) ARG1 );

/** @brief Determine if the two primitives are intersecting.
    @param [in] ARG0 Pointer to a vector of the minimum of an axis-aligned box object.
    @param [in] ARG1 Pointer to a vector of the maximum of an axis-aligned box object.
    @param [in] ARG2 Pointer to a vector of the minimum of an axis-aligned box object.
    @param [in] ARG3 Pointer to a vector of the maximum of an axis-aligned box object.
    @return True if the two primitives are intersecting, and false otherwise. */
TgINLINE TgBOOL
FCN_VO(tgCO_BA_Test_Elem_BA)(
    VEC_T(1,C) ARG0, VEC_T(1,C) ARG1, VEC_T(1,C) ARG2, VEC_T(1,C) ARG3 );


/** @brief Update the collision packet with point(s) of penetration between two axis-aligned boxes.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG2.
                         Contact normals are the direction for the object at ARG2 to move to achieve separation.
                         Depth values are measured from the surface of the object at ARG1 to the contact point.
    @param [in] ARG1 Pointer to an axis-aligned box object.
    @param [in] ARG2 Pointer to an axis-aligned box object.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_BA_Penetrate_BA)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgBOXAA,CPC) ARG1, VEC_OBJ_T(TgBOXAA,CPC) ARG2 );




/* ---- Box AA - Plane ----------------------------------------------------------------------------------------------------------------------------------------------------------- */

/** @brief Calculate the minimal distance squared between an axis-aligned box and a plane.
    @param [in] ARG0 Pointer to an axis-aligned box object.
    @param [in] ARG1 Pointer to a plane object.
    @return Minimal distance squared between an axis-aligned box and a plane when the box is above the plane, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_BA_DistSq_PN)(
    VEC_OBJ_T(TgBOXAA,CPC) ARG0, VEC_OBJ_T(TgPLANE,CPC) ARG1 );

/** @brief Calculate the minimal distance between an axis-aligned box and a plane.
    @param [in] ARG0 Pointer to an axis-aligned box object.
    @param [in] ARG1 Pointer to a plane object.
    @return Minimal distance between an axis-aligned box and a plane when the box is above the plane, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_BA_Dist_PN)(
    VEC_OBJ_T(TgBOXAA,CPC) ARG0, VEC_OBJ_T(TgPLANE,CPC) ARG1 );

/** @brief Calculate the minimal distance squared between an axis-aligned box and a plane, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG2 on ARG1.
    @param [in] ARG1 Pointer to an axis-aligned box object.
    @param [in] ARG2 Pointer to a plane object.
    @return Minimal distance squared between an axis-aligned box and a plane when the box is above the plane, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_BA_ClosestSq_PN)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgBOXAA,CPC) ARG2, VEC_OBJ_T(TgPLANE,CPC) ARG3 );

/** @brief Calculate the minimal distance between an axis-aligned box and a plane, and on a non-negative distance store the point(s) of closest proximity.
    @param [out] OUT0 Pointer to a vector holding the closest point to ARG2 on ARG1.
    @param [in] ARG1 Pointer to an axis-aligned box object.
    @param [in] ARG2 Pointer to a plane object.
    @return Minimal distance between an axis-aligned box and a plane when the box is above the plane, or zero otherwise, broadcast across all vector lanes. */
TgINLINE VEC_T(1)
FCN_VO(tgCO_BA_Closest_PN)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgBOXAA,CPC) ARG2, VEC_OBJ_T(TgPLANE,CPC) ARG3 );


/** @brief Determine if the axis-aligned box is completely above the plane.
    @param [in] ARG0 Pointer to an axis-aligned box object.
    @param [in] ARG1 Pointer to a plane object.
    @return True axis-aligned box is completely above the plane, and false otherwise. */
TgINLINE TgBOOL
FCN_VO(tgCO_BA_Test_PN)(
    VEC_OBJ_T(TgBOXAA,CPC) ARG0, VEC_OBJ_T(TgPLANE,CPC) ARG1 );


/** @brief Update the collision packet with point(s) of penetration between an axis-aligned box and a plane.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                         Contact points are generated on the surface of ARG2.
                         Contact normals are the direction for the object at ARG2 to move to achieve separation.
                         Depth values are measured from the surface of the object at ARG1 to the contact point.
    @param [in] ARG1 Pointer to a plane object.
    @param [in] ARG2 Pointer to an axis-aligned box object.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_PN_Penetrate_BA)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgPLANE,CPC) ARG1, VEC_OBJ_T(TgBOXAA,CPC) ARG2 );

/** @brief Update the collision packet with point(s) of contact between a swept axis-aligned box and a plane.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
    @param [in,out] OUT1 Pointer to a vector with a full broadcast of the normalized time of contact (percentage of time step).
    @param [in] ARG2: Pointer to a plane object. The test is done inside of this object's reference frame.
    @param [in] ARG3: Pointer to an axis-aligned box object.
    @param [in] ARG4 Pointer to an object holding displacement values for ARG3.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_PN_Sweep_BA)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_T(1,P) OUT1, VEC_OBJ_T(TgPLANE,CPC) ARG2, VEC_OBJ_T(TgBOXAA,CPC) ARG3, VEC_OBJ_T(TgDELTA,CPC) ARG4 );




/* ---- Box AA - Triangle -------------------------------------------------------------------------------------------------------------------------------------------------------- */

/** @brief Determine if the two primitives are intersecting.
    @param [in] ARG0 Pointer to an axis-aligned box object.
    @param [in] ARG1 Pointer to a triangle object.
    @return True if the two primitives are intersecting, and false otherwise. */
TgINLINE TgBOOL
FCN_VO(tgCO_BA_Test_PTRI)(
    VEC_OBJ_T(TgBOXAA,CPC) ARG0, VEC_OBJ_T(TgPTRI,CPC) ARG1 );


/** @} TGS_COLLISION_BA */

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

    #define TGS_COLLISION_BOX_AA_H

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COLLISION_BOX_AA_H) */
#endif
