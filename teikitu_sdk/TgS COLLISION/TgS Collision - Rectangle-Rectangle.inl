/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Rectangle-Rectangle.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.18 | »GUID« 5BB31923-DAF4-437F-8513-C1B5BEEA163A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_RECTANGLE_RECTANGLE_INL)
#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* == Collision ================================================================================================================================================================== */

/* ---- FCN_VO(tgCO_RT_DistSq_RT) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_RT_DistSq_RT)( VEC_OBJ_T(TgRECTANGLE,CPC) psRT0, VEC_OBJ_T(TgRECTANGLE,CPC) psRT1 )
{
    VEC_T(1)                            vRT00, vRT01, vRT10, vRT11;

    return (FCN_VO(tgCO_RT_ClosestSq_PM_RT)( &vRT00, &vRT01, &vRT10, &vRT11, psRT0, psRT1 ));
}


/* ---- FCN_VO(tgCO_RT_Dist_RT) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_RT_Dist_RT)( VEC_OBJ_T(TgRECTANGLE,CPC) psRT0, VEC_OBJ_T(TgRECTANGLE,CPC) psRT1 )
{
    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_RT_DistSq_RT)( psRT0, psRT1 ) ));
}


/* ---- FCN_VO(tgCO_RT_ClosestSq_RT) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_RT_ClosestSq_RT)( VEC_T(1,PC) pvRT0, VEC_T(1,PC) pvRT1, VEC_OBJ_T(TgRECTANGLE,CPC) psRT0, VEC_OBJ_T(TgRECTANGLE,CPC) psRT1 )
{
    VEC_T(1)                            vRT00, vRT01, vRT10, vRT11;

    VEC_T(1,C)                          vDistSq = FCN_VO(tgCO_RT_ClosestSq_PM_RT)( &vRT00, &vRT01, &vRT10, &vRT11, psRT0, psRT1 );

    VEC_T(1,C)                          vX0 = FCN_V(tgMH_MAD)( vRT00, psRT0->m_avEdge[0], psRT0->m_vOrigin );
    VEC_T(1,C)                          vX1 = FCN_V(tgMH_MAD)( vRT10, psRT1->m_avEdge[0], psRT1->m_vOrigin );

    *pvRT0 = FCN_V(tgMH_MAD)( vRT01, psRT0->m_avEdge[1], vX0 );
    *pvRT1 = FCN_V(tgMH_MAD)( vRT11, psRT1->m_avEdge[1], vX1 );

    return (vDistSq);
}


/* ---- FCN_VO(tgCO_RT_Closest_RT) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_RT_Closest_RT)( VEC_T(1,PC) pvRT0, VEC_T(1,PC) pvRT1, VEC_OBJ_T(TgRECTANGLE,CPC) psRT0, VEC_OBJ_T(TgRECTANGLE,CPC) psRT1 )
{
    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_RT_ClosestSq_RT)( pvRT0, pvRT1, psRT0, psRT1 ) ));
}


/* ---- FCN_VO(tgCO_RT_Closest_PM_RT) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_RT_Closest_PM_RT)( VEC_T(1,PC) pvRT00, VEC_T(1,PC) pvRT01, VEC_T(1,PC) pvRT10, VEC_T(1,PC) pvRT11, VEC_OBJ_T(TgRECTANGLE,CPC) psRT0,
                                                 VEC_OBJ_T(TgRECTANGLE,CPC) psRT1 )
{
    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_RT_ClosestSq_PM_RT)( pvRT00, pvRT01, pvRT10, pvRT11, psRT0, psRT1 ) ));
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

    #define TGS_COLLISION_RECTANGLE_RECTANGLE_INL

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COLLISION_RECTANGLE_RECTANGLE_INL) */
#endif
