/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Circle-Point.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.18 | »GUID« 5BB31923-DAF4-437F-8513-C1B5BEEA163A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_CIRCLE_POINT_INL)
#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* == Collision ================================================================================================================================================================== */

/* ---- FCN_VO(tgCO_CI_DistSq_PT) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_CI_DistSq_PT)( VEC_OBJ_T(TgCIRCLE,CPC) psCI0, VEC_T(1,C) vS0 )
{
    VEC_T(1,C)                          vC0 = FCN_VO(tgGM_CI_Query_Origin)( psCI0 );
    VEC_T(1,C)                          vN0 = FCN_VO(tgGM_CI_Query_Normal)( psCI0 );

    return (FCN_VO(tgCO_CI_ELEM_DistSq_PT)( vC0, vN0, psCI0->m_vRadius, vS0 ));
}


/* ---- FCN_VO(tgCO_CI_Dist_PT) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_CI_Dist_PT)( VEC_OBJ_T(TgCIRCLE,CPC) psCI0, VEC_T(1,C) vS0 )
{
    VEC_T(1,C)                          vDistSq = FCN_VO(tgCO_CI_DistSq_PT)( psCI0, vS0 );

    return (FCN_V(tgMH_SQRT)( vDistSq ));
}


/* ---- FCN_VO(tgCO_CI_ClosestSq_PT) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_CI_ClosestSq_PT)( VEC_T(1,PC) pvCI0, VEC_OBJ_T(TgCIRCLE,CPC) psCI0, VEC_T(1,C) vS0 )
{
    VEC_T(1,C)                          vC0 = FCN_VO(tgGM_CI_Query_Origin)( psCI0 );
    VEC_T(1,C)                          vN0 = FCN_VO(tgGM_CI_Query_Normal)( psCI0 );

    return (FCN_VO(tgCO_CI_ELEM_ClosestSq_PT)( pvCI0, vC0, vN0, psCI0->m_vRadius, vS0 ));
}


/* ---- FCN_VO(tgCO_CI_Closest_PT) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_CI_Closest_PT)( VEC_T(1,PC) pvCI0, VEC_OBJ_T(TgCIRCLE,CPC) psCI0, VEC_T(1,C) vS0 )
{
    VEC_T(1,C)                          vDistSq = FCN_VO(tgCO_CI_ClosestSq_PT)( pvCI0, psCI0, vS0 );

    return (FCN_V(tgMH_SQRT)( vDistSq ));
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

    #define TGS_COLLISION_CIRCLE_POINT_INL

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COLLISION_CIRCLE_POINT_INL) */
#endif
