/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Internal.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_INTERNAL_H)

#if !defined(TGS_COLLISION_INTERNAL_ONCE_H)
#define TGS_COLLISION_INTERNAL_ONCE_H

#include "TgS Collision.h"
#include "TgS COLLISION/TgS Collision.inl"


/* == Collision ================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Macros                                                                                                                                                                */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
#if TgCOMPILE__CONSOLE

#define TgERROR_CO( ... ) tgCN_PrintF( KTgCN_CHANEL_ERROR, STD_MSG_PREFIX, STD_MSG_POST );  tgCN_PrintF( KTgCN_CHANEL_ERROR, __VA_ARGS__ )
#define TgWARN_CO( ... ) tgCN_PrintF( KTgCN_CHANEL_WARNING, STD_MSG_PREFIX, STD_MSG_POST );  tgCN_PrintF( KTgCN_CHANEL_WARNING, __VA_ARGS__ )
#define TgLOG_CO( ... ) tgCN_PrintF( KTgCN_CHANEL_LOG, STD_MSG_PREFIX, STD_MSG_POST );  tgCN_PrintF( KTgCN_CHANEL_LOG, __VA_ARGS__ )

/*# TgCOMPILE__CONSOLE */
#else

#define TgERROR_CO( ... )
#define TgWARN_CO( ... )
#define TgLOG_CO(  ... )

/*# TgS_COMPILE_CONSOLE */
#endif


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#include "TgS COMMON/TgS Common.inl"
//#include "TgS COLLISION/TgS Collision.inl"


/*# !defined(TGS_COLLISION_INTERNAL_ONCE_H) */
#endif

#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* =============================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @brief Internal function for sweeping a tube versus a tube.
    @param [in,out] OUT0 Pointer to an object holding parameters, existing contact points and updated due to new contact points.
                        Contact points are generated on the surface of ARG2
                        Contact normal is the surface normal at the contact point on ARG2
    @param [in,out] OUT1 Pointer to a vector with a full broadcast of the normalized time of contact (percentage of time step).
    @param [in] ARG2 Pointer to a tube object. The test is done inside of this object's reference frame
    @param [in] ARG3 Pointer to a tube object
    @param [in] ARG4 Pointer to an object holding displacement values for ARG3
    @return Result Code. */
TgEXTN TgRESULT
FCN_VO(tgCO_TB_Internal_Sweep_TB)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_T(1,PC) OUT1, VEC_OBJ_T(TgTUBE,CPC) ARG2, VEC_OBJ_T(TgTUBE,CPC)ARG3, VEC_OBJ_T(TgDELTA,CPC) ARG4 );

/** @brief Given a collision result, return the next result or NULL otherwise.
    @param [in] ARG0 Pointer to a ray object
    @param [in] ARG1 Vector holding a position
    @param [in] ARG2 Vector holding a position
    @param [in] ARG3 Vector holding a position
    @return Pointer to a collision result (data structure), or NULL if no other results exist. */
TgEXTN VEC_OBJ_T(STg2_CO_Result,P)
FCN_VO(tgCO_REQ_Next_Result)(
    VEC_OBJ_T(STg2_CO_Request,PC) OUT0, VEC_T(1,C) ARG1, VEC_T(1,C) ARG2, VEC_T(1,C) ARG3 );

/** @brief Internal contact generation function for two line segments
    @param [out] OUT0 Pointer to a vector holding the 1st point of contact.
    @param [out] OUT1 Pointer to a vector holding the 2nd point of contact.
    @param [in] ARG2 Vector holding a Segment Origin.
    @param [in] ARG3 Vector holding the position relative to the Segment Origin of the Segment Terminal Point.
    @param [in] ARG4 Vector holding a Segment Origin.
    @param [in] ARG5 Vector holding the position relative to the Segment Origin of the Segment Terminal Point.
    @return The number of contacts between the two segments, where a maximum value represents an error condition. */
TgEXTN TgRSIZE
FCN_VO(tgCO_LN_Internal_Intersect_LN)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,C) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4, VEC_T(1,C) ARG5 );

/** @brief Internal contact generation function for two line segments
    @param [out] OUT0 Pointer to a vector holding the 1st point of contact.
    @param [out] OUT1 Pointer to a vector holding the 2nd point of contact.
    @param [in] ARG2 Vector holding a Segment Origin.
    @param [in] ARG3 Vector holding the position relative to the Segment Origin of the Segment Terminal Point.
    @param [in] ARG4 Vector holding a Segment Origin.
    @param [in] ARG5 Vector holding the position relative to the Segment Origin of the Segment Terminal Point.
    @return The number of contacts between the two segments, where a maximum value represents an error condition. */
TgEXTN TgRSIZE
FCN_VO(tgCO_LN_Internal_Parallel_LN)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,C) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4, VEC_T(1,C) ARG5 );

TgEXTN TgSINT_F32
FCN_VO(tgCO_Test_Seperating_Axis)(
    VEC_OBJ_T(STg2_CO_Axis_Test,PC) );

TgEXTN TgRESULT
FCN_VO(tgCO_ST_Axis_Seperation_ST)(
    VEC_OBJ_T(STg2_CO_Axis_Info,PC), VEC_T(1,C), VEC_OBJ_T(TgSTRI,CPC), VEC_OBJ_T(TgSTRI,CPC), VEC_OBJ_T(TgDELTA,CPC) );



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

    #define TGS_COLLISION_INTERNAL_H

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COLLISION_INTERNAL_H) */
#endif
