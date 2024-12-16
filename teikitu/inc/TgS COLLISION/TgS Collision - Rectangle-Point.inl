/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Rectangle-Point.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.18 | »GUID« 5BB31923-DAF4-437F-8513-C1B5BEEA163A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_RECTANGLE_POINT_INL)
#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* == Collision ================================================================================================================================================================== */

/* ---- FCN_VO(tgCO_RT_DistSq_PT) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_RT_DistSq_PT)( VEC_OBJ_T(TgRECTANGLE,CPC) psRT0, VEC_T(1,C) vS0 )
{
    VEC_T(1)                            vT0, vT1;

    return (FCN_VO(tgCO_RT_ClosestSq_PM_PT)( &vT0, &vT1, psRT0, vS0 ));
}


/* ---- FCN_VO(tgCO_RT_Dist_PT) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_RT_Dist_PT)( VEC_OBJ_T(TgRECTANGLE,CPC) psRT0, VEC_T(1,C) vS0 )
{
    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_RT_DistSq_PT)( psRT0, vS0 ) ));
}


/* ---- FCN_VO(tgCO_RT_ClosestSq_PT) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_RT_ClosestSq_PT)( VEC_T(1,PC) pvRT0, VEC_OBJ_T(TgRECTANGLE,CPC) psRT0, VEC_T(1,C) vS0 )
{
    VEC_T(1)                            vT0, vT1;

    VEC_T(1,C)                          vDistSq = FCN_VO(tgCO_RT_ClosestSq_PM_PT)( &vT0, &vT1, psRT0, vS0 );

    VEC_T(1,C)                          vX0 = FCN_V(tgMH_MAD)( vT0, psRT0->m_avEdge[0], psRT0->m_vOrigin );

    *pvRT0 = FCN_V(tgMH_MAD)( vT1, psRT0->m_avEdge[1], vX0 );

    return (vDistSq);
}


/* ---- FCN_VO(tgCO_RT_Closest_PT) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_RT_Closest_PT)( VEC_T(1,PC) pvRT0, VEC_OBJ_T(TgRECTANGLE,CPC) psRT0, VEC_T(1,C) vS0 )
{
    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_RT_ClosestSq_PT)( pvRT0, psRT0, vS0 ) ));
}


/* ---- FCN_VO(tgCO_RT_Closest_PM_PT) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_RT_Closest_PM_PT)( VEC_T(1,PC) pvRT0, VEC_T(1,PC) pvRT1, VEC_OBJ_T(TgRECTANGLE,CPC) psRT0, VEC_T(1,C) vS0 )
{
    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_RT_ClosestSq_PM_PT)( pvRT0, pvRT1, psRT0, vS0 ) ));
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

    #define TGS_COLLISION_RECTANGLE_POINT_INL

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COLLISION_RECTANGLE_POINT_INL) */
#endif
