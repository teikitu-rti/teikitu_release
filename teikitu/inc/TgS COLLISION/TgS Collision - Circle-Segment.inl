/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Circle-Segment.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.18 | »GUID« 5BB31923-DAF4-437F-8513-C1B5BEEA163A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_CIRCLE_SEGMENT_INL)
#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* == Collision ================================================================================================================================================================== */

/* ---- FCN_VO(tgCO_CI_DistSq_SG) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_CI_DistSq_SG)( VEC_OBJ_T(TgCIRCLE,CPC) psCI0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    VEC_T(1)                            vCI0, vSG0;

    return (FCN_VO(tgCO_CI_ClosestSq_PM_LR11)( &vCI0, &vSG0, psCI0, psSG0->m_vOrigin, psSG0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_CI_Dist_SG) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_CI_Dist_SG)( VEC_OBJ_T(TgCIRCLE,CPC) psCI0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_CI_DistSq_SG)( psCI0, psSG0 ) ));
}


/* ---- FCN_VO(tgCO_CI_ClosestSq_SG) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_CI_ClosestSq_SG)( VEC_T(1,PC) pvCI0, VEC_T(1,PC) pvSG0, VEC_OBJ_T(TgCIRCLE,CPC) psCI0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    VEC_T(1)                            vSG0;

    VEC_T(1,C)                          vDistSq = FCN_VO(tgCO_CI_ClosestSq_PM_LR11)( pvCI0, &vSG0, psCI0, psSG0->m_vOrigin, psSG0->m_vDirN );

    *pvSG0 = FCN_V(tgMH_MAD)( vSG0, psSG0->m_vDirN, psSG0->m_vOrigin );

    return (vDistSq);
}


/* ---- FCN_VO(tgCO_CI_Closest_SG) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_CI_Closest_SG)( VEC_T(1,PC) pvCI0, VEC_T(1,PC) pvSG0, VEC_OBJ_T(TgCIRCLE,CPC) psCI0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_CI_ClosestSq_SG)( pvCI0, pvSG0, psCI0, psSG0 ) ));
}


/* ---- FCN_VO(tgCO_CI_ClosestSq_PM_SG) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_CI_ClosestSq_PM_SG)( VEC_T(1,PC) pvCI0, VEC_T(1,PC) pvSG0, VEC_OBJ_T(TgCIRCLE,CPC) psCI0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    return (FCN_VO(tgCO_CI_ClosestSq_PM_LR11)( pvCI0, pvSG0, psCI0, psSG0->m_vOrigin, psSG0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_CI_Closest_PM_SG) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_CI_Closest_PM_SG)( VEC_T(1,PC) pvCI0, VEC_T(1,PC) pvSG0, VEC_OBJ_T(TgCIRCLE,CPC) psCI0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_CI_ClosestSq_PM_LR11)( pvCI0, pvSG0, psCI0, psSG0->m_vOrigin, psSG0->m_vDirN ) ));
}


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

    #define TGS_COLLISION_CIRCLE_SEGMENT_INL

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COLLISION_CIRCLE_SEGMENT_INL) */
#endif
