/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Request.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_REQUEST_H)
#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* == Collision ================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Collision - Request Functions                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* Setup - Query Type and Primitive */

/** @brief Initialize the structure to test if any contacts occur for the specified primitive and request purpose.
    @param[out] OUT0 Pointer to the collision request object to be initialized.
    @param[in] ARG1 Enumeration value of the primitive type.
    @param[in] ARG2 Enumeration value of the request purpose. */
TgINLINE TgVOID
FCN_VO(tgCO_REQ_Init_Test)(
    VEC_OBJ_T(STg2_CO_Request,PC) OUT0, ETgPRIMITIVE_C ARG1, ETgCO_PURPOSE_C ARG2 );

/** @brief Initialize the structure to test if any contacts occur for the specified primitive, displaced by the sweep vector, and considering the request purpose.
    @param[out] OUT0 Pointer to the collision request object to be initialized.
    @param[in] ARG1 Enumeration value of the primitive type.
    @param[in] ARG2 Vector of the displacement of ARG1.
    @param[in] ARG3 Enumeration value of the request purpose. */
TgINLINE TgVOID
FCN_VO(tgCO_REQ_Init_Test_Sweep)(
    VEC_OBJ_T(STg2_CO_Request,PC) OUT1, ETgPRIMITIVE_C ARG1, VEC_T(1,C) ARG2, ETgCO_PURPOSE_C ARG3 );

/** @brief Initialize the structure to report any points of intersection for the specified primitive and request purpose.
    @param[out] OUT0 Pointer to the collision request object to be initialized.
    @param[in] ARG1 Enumeration value of the primitive type.
    @param[in] ARG2 Enumeration value of the request purpose. */
TgINLINE TgVOID
FCN_VO(tgCO_REQ_Init_Intersect)(
    VEC_OBJ_T(STg2_CO_Request,PC) OUT0, ETgPRIMITIVE_C ARG1, ETgCO_PURPOSE_C ARG2 );

/** @brief Initialize the structure to report any points of penetration for the specified primitive and request purpose.
    @param[out] OUT0 Pointer to the collision request object to be initialized.
    @param[in] ARG1 Enumeration value of the primitive type.
    @param[in] ARG2 Enumeration value of the request purpose. */
TgINLINE TgVOID
FCN_VO(tgCO_REQ_Init_Penetrate)(
    VEC_OBJ_T(STg2_CO_Request,PC) OUT0, ETgPRIMITIVE_C ARG1, ETgCO_PURPOSE_C ARG2 );

/** @brief Initialize the structure to determine any contacts for the specified primitive, displaced by the sweep vector, and considering the request purpose.
    @param[out] OUT0 Pointer to the collision request object to be initialized.
    @param[in] ARG1 Enumeration value of the primitive type.
    @param[in] ARG2 Vector of the displacement of ARG1.
    @param[in] ARG3 Enumeration value of the request purpose. */
TgINLINE TgVOID
FCN_VO(tgCO_REQ_Init_Sweep)(
    VEC_OBJ_T(STg2_CO_Request,PC) OUT0, ETgPRIMITIVE_C ARG1, VEC_T(1,C) ARG2, ETgCO_PURPOSE_C ARG3 );

/** @brief Initialize the structure to determine any points of penetration for the specified primitive, displaced by the sweep vector, and considering the request purpose.
    @param[out] OUT0 Pointer to the collision request object to be initialized.
    @param[in] ARG1 Enumeration value of the primitive type.
    @param[in] ARG2 Vector of the displacement of ARG1.
    @param[in] ARG3 Enumeration value of the request purpose. */
TgINLINE TgVOID
FCN_VO(tgCO_REQ_Init_Sweep_Penetrate)(
    VEC_OBJ_T(STg2_CO_Request,PC) OUT0, ETgPRIMITIVE_C ARG1, VEC_T(1,C) ARG2, ETgCO_PURPOSE_C ARG3 );

/** @brief Initialize the structure to collect all primitives in contact with the specific primitive given the request purpose.
    @param[out] OUT0 Pointer to the collision request object to be initialized.
    @param[in] ARG1 Enumeration value of the primitive type.
    @param[in] ARG2 Enumeration value of the request purpose. */
TgINLINE TgVOID
FCN_VO(tgCO_REQ_Init_Collect)(
    VEC_OBJ_T(STg2_CO_Request,PC) OUT0, ETgPRIMITIVE_C ARG1, ETgCO_PURPOSE_C ARG2 );


/* == Collision ================================================================================================================================================================== */
/* Setup - Filters (Include and Exclude Filters)
    Every collision primitive is a member of at least one collision category, represented by a bitfield. Collision tests are done if the primitive category and the request include
    flags (boolean and operation) are non-zero, and the primitive category and the ignore flags (boolean and operation) are zero.
*/

/** @brief Set the requests include bitfield.
    @param[in,out] OUT0 Pointer to the collision request object.
    @param[in] ARG1 Integer representing a bitfield for the categories to be included in this collision request. */
TgINLINE TgVOID
FCN_VO(tgCO_REQ_Set_Include_Filter)(
    VEC_OBJ_T(STg2_CO_Request,PC) OUT0, TgUINT_F32_C ARG1 );


/** @brief Reset (clear) the request's ignore bitfield.
    @param[in,out] OUT0 Pointer to the collision request object. */
TgEXTN TgVOID
FCN_VO(tgCO_REQ_Ignore_Reset)(
    VEC_OBJ_T(STg2_CO_Request,PC) OUT0 );


/** @brief Have the collision request enable/disable the ignoring of all collision categories.
    @param[in,out] OUT0 Pointer to the collision request object.
    @param[in] ARG1 Boolean flag to enable or disable whether the request will ignore all collision categories. */
TgINLINE TgVOID
FCN_VO(tgCO_REQ_Ignore_All)(
    VEC_OBJ_T(STg2_CO_Request,PC) OUT0, TgBOOL_C ARG1 );

/** @brief Have the collision request enable/disable the object pointed to in the connection node.
    @param[in,out] OUT0 Pointer to the collision request object.
    @param[in] ARG1 Pointer to a node in a connection graph.
    @param[in] ARG2 Boolean flag to enable or disable the ignore state.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_REQ_Ignore_Connection)(
    VEC_OBJ_T(STg2_CO_Request,PC) OUT0, STg2_Connection_PC ARG1, TgBOOL_C ARG2 );

/** @brief Have the collision request enable/disable the set of object pointed to in the connection graph starting at ARG1.
    @param[in,out] OUT0 Pointer to the collision request object.
    @param[in] ARG1 Pointer to a node (considered to be the root) in a connection graph.
    @param[in] ARG2 Boolean flag to enable or disable the ignore state.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_REQ_Ignore_Connection_Graph)(
    VEC_OBJ_T(STg2_CO_Request,PC) OUT0, STg2_Connection_PC ARG1, TgBOOL_C ARG2 );

/** @brief Have the collision request enable/disable the object or object type referenced by the ARG1 identifier.
    @param[in,out] OUT0 Pointer to the collision request object.
    @param[in] ARG1 Integer identifier representing an object or object type.
    @param[in] ARG2 Boolean flag to enable or disable the ignore state.
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_REQ_Ignore_Native_String)(
    VEC_OBJ_T(STg2_CO_Request,PC) OUT0, TgSINT_F32_C ARG1, TgBOOL_C ARG2 );


/** @brief Test to see if the request is ignoring all collision categories.
    @param[in] ARG0 Pointer to the collision request object.
    @return True if the ignore all flag is set, FALSE otherwise. */
TgINLINE TgBOOL
FCN_VO(tgCO_REQ_Is_Ignored_All)(
    VEC_OBJ_T(STg2_CO_Request,CPC) ARG0 );

/** @brief Test to see if the object pointed to in the connection node (ARG1) is ignored by this request.
    @param[in] ARG0 Pointer to the collision request object.
    @param[in] ARG1 Pointer to a node in a connection graph.
    @return True if the node is marked to be ignored, FALSE otherwise. */
TgEXTN TgBOOL
FCN_VO(tgCO_REQ_Is_Ignored_Connection)(
    VEC_OBJ_T(STg2_CO_Request,CPC) ARG0, STg2_Connection_CPC ARG1 );

/** @brief Test to see if the object or object type referenced by the ARG1 identifier is ignored by this request.
    @param[in] ARG0 Pointer to the collision request object.
    @param[in] ARG1 Integer identifier representing an object or object type.
    @return True if the object or object type referenced is marked to be ignored, FALSE otherwise. */
TgEXTN TgBOOL
FCN_VO(tgCO_REQ_Is_Ignored_Native_String)(
    VEC_OBJ_T(STg2_CO_Request,CPC) ARG0, TgSINT_F32_C ARG1 );


/* Miscellaneous */

/** @brief Reset (clear) all state and configuration of the collision request object. Assumes the object was previously initialized (i.e. it is currently valid).
    @param[in,out] OUT0 Pointer to the collision request object. */
TgEXTN TgVOID
FCN_VO(tgCO_REQ_Reset)(
    VEC_OBJ_T(STg2_CO_Request,PC) OUT0 );


/* Transform */

/** @brief Transform the reference frame of the request by the matrix in ARG1
    @param[in,out] OUT0 Pointer to the collision request object.
    @param[in] ARG1 Pointer to a matrix for the transformation. */
TgEXTN TgVOID
FCN_VO(tgCO_REQ_F_TX)(
    VEC_OBJ_T(STg2_CO_Request,PC) OUT0, VEC_T(3,CPCU) ARG1 );

/** @brief Transform the reference frame of the request by the matrix in ARG2 and store it in ARG1
    @param[out] OUT0 Pointer to a collision request object that will hold the transformed request.
    @param[in] ARG1 Pointer to a collision request object that is the original source.
    @param[in] ARG2 Pointer to a matrix for the transformation. */
TgEXTN TgVOID
FCN_VO(tgCO_REQ_F_Copy_TX)(
    VEC_OBJ_T(STg2_CO_Request,PC) OUT0, VEC_OBJ_T(STg2_CO_Request,CPC) ARG1, VEC_T(3,CPCU) ARG2 );



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

    #define TGS_COLLISION_REQUEST_H

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COLLISION_REQUEST_H) */
#endif
