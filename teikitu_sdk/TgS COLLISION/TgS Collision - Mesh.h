/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Mesh.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_MESH_H)
#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* == Collision ================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions - Scalar Functions                                                                                                                                            */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @addtogroup TGS_COLLISION_MA */
/** @{ */

/** @brief Update the collision packet with point(s) of penetration between a convex mesh and a box.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to the new contact points.
                         Contact points are generated on the surface of ARG2.
                         Contact normals are the direction for the object at ARG2 to move to achieve separation.
                         Depth values are measured from the surface of the object at ARG1 to the contact point.
    @param [in] ARG1 Pointer to a box object.
    @param [in] ARG2 Pointer to an array of triangles (space).
    @param [in] ARG3 Pointer to an array of axis-aligned bounding boxes (1:1 with the triangle array).
    @param [in] ARG4 Integer holding the number of triangles in ARG2 array.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_BX_Penetrate_CX)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgBOX,CPC) ARG1, VEC_OBJ_T(TgSTRI,CPC) ARG2, VEC_OBJ_T(TgBOXAA,CPC) ARG3, TgRSIZE_C ARG4 );

/** @brief Update the collision packet with point(s) of penetration between a convex mesh and a box.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to the new contact points.
                         Contact points are generated on the surface of ARG2.
                         Contact normals are the direction for the object at ARG2 to move to achieve separation.
                         Depth values are measured from the surface of the object at ARG1 to the contact point.
    @param [in] ARG1 Pointer to tube object, interpreted as a cylinder.
    @param [in] ARG2 Pointer to an array of triangles (space).
    @param [in] ARG3 Pointer to an array of axis-aligned bounding boxes (1:1 with the triangle array).
    @param [in] ARG4 Integer holding the number of triangles in ARG2 array.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_CY_Penetrate_CX)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgTUBE,CPC) ARG1, VEC_OBJ_T(TgSTRI,CPC) ARG2, VEC_OBJ_T(TgBOXAA,CPC) ARG3, TgRSIZE_C ARG4 );

/** @brief Update the collision packet with point(s) of penetration between a convex mesh and a box.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to the new contact points.
                         Contact points are generated on the surface of ARG2.
                         Contact normals are the direction for the object at ARG2 to move to achieve separation.
                         Depth values are measured from the surface of the object at ARG1 to the contact point.
    @param [in] ARG1 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG2 Pointer to an array of triangles (space).
    @param [in] ARG3 Pointer to an array of axis-aligned bounding boxes (1:1 with the triangle array).
    @param [in] ARG4 Integer holding the number of triangles in ARG2 array.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_CP_Penetrate_CX)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgTUBE,CPC) ARG1, VEC_OBJ_T(TgSTRI,CPC) ARG2, VEC_OBJ_T(TgBOXAA,CPC) ARG3, TgRSIZE_C ARG4 );

/** @brief Update the collision packet with point(s) of penetration between a convex mesh and a box.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to the new contact points.
                         Contact points are generated on the surface of ARG2.
                         Contact normals are the direction for the object at ARG2 to move to achieve separation.
                         Depth values are measured from the surface of the object at ARG1 to the contact point.
    @param [in] ARG1 Pointer to a sphere object.
    @param [in] ARG2 Pointer to an array of triangles (space).
    @param [in] ARG3 Pointer to an array of axis-aligned bounding boxes (1:1 with the triangle array).
    @param [in] ARG4 Integer holding the number of triangles in ARG2 array.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_SP_Penetrate_CX)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgSPHERE,CPC) ARG1, VEC_OBJ_T(TgSTRI,CPC) ARG2, VEC_OBJ_T(TgBOXAA,CPC) ARG3, TgRSIZE_C ARG4 );

/** @brief Update the collision packet with point(s) of penetration between a convex mesh and a box.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to the new contact points.
                         Contact points are generated on the surface of ARG2.
                         Contact normals are the direction for the object at ARG2 to move to achieve separation.
                         Depth values are measured from the surface of the object at ARG1 to the contact point.
    @param [in] ARG1 Pointer to a plane object.
    @param [in] ARG2 Pointer to an array of triangles (space).
    @param [in] ARG3 Pointer to an array of axis-aligned bounding boxes (1:1 with the triangle array).
    @param [in] ARG4 Integer holding the number of triangles in ARG2 array.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_PN_Penetrate_CX)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgPLANE,CPC) ARG1, VEC_OBJ_T(TgSTRI,CPC) ARG2, VEC_OBJ_T(TgBOXAA,CPC) ARG3, TgRSIZE_C ARG4 );

/** @brief Update the collision packet with point(s) of penetration between a convex mesh and a box.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to the new contact points.
                         Contact points are generated on the surface of ARG2.
                         Contact normals are the direction for the object at ARG2 to move to achieve separation.
                         Depth values are measured from the surface of the object at ARG1 to the contact point.
    @param [in,out] ARG1 Pointer to a vector with a full broadcast of the normalized time of contact (percentage of time step).
    @param [in] ARG2 Pointer to a triangle (space) object.
    @param [in] ARG3 Pointer to an array of triangles (space).
    @param [in] ARG4 Pointer to an array of axis-aligned bounding boxes (1:1 with the triangle array).
    @param [in] ARG5 Integer holding the number of triangles in ARG4 array.
    @param [in] ARG6 Pointer to an object holding displacement values for ARG4.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_ST_Sweep_CX)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_T(1,PC) pvPM, VEC_OBJ_T(TgSTRI,CPC) ARG2, VEC_OBJ_T(TgSTRI,CPC) ARG3, VEC_OBJ_T(TgBOXAA,CPC) ARG4, TgRSIZE_C ARG5,
    VEC_OBJ_T(TgDELTA,CPC) ARG6 );


/** @} TGS_COLLISION_MA */

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

    #define TGS_COLLISION_MESH_H

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COLLISION_MESH_H) */
#endif
