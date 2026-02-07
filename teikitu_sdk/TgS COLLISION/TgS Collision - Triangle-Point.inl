/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Triangle-Point.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.18 | »GUID« 5BB31923-DAF4-437F-8513-C1B5BEEA163A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_TRIANGLE_POINT_INL)
#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* == Collision ================================================================================================================================================================== */

/* ---- FCN_VO(tgCO_ET_DistSq_PT) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_ET_DistSq_PT)( VEC_OBJ_T(TgETRI,CPC) psET0, VEC_T(1,C) vS0 )
{
    VEC_T(1)                            vT0, vT1;

    return (FCN_VO(tgCO_ET_ClosestSq_PM_PT)( &vT0, &vT1, psET0, vS0 ));
}


/* ---- FCN_VO(tgCO_ET_Dist_PT) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_ET_Dist_PT)( VEC_OBJ_T(TgETRI,CPC) psET0, VEC_T(1,C) vS0 )
{
    VEC_T(1)                            vT0, vT1;

    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_ET_ClosestSq_PM_PT)( &vT0, &vT1, psET0, vS0 ) ));
}


/* ---- FCN_VO(tgCO_ET_ClosestSq_PT) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_ET_ClosestSq_PT)( VEC_T(1,PC) pvET0, VEC_OBJ_T(TgETRI,CPC) psET0, VEC_T(1,C) vS0 )
{
    VEC_T(1)                            vET0, vET1;

    VEC_T(1,C)                          vDistSq = FCN_VO(tgCO_ET_ClosestSq_PM_PT)( &vET0, &vET1, psET0, vS0 );

    VEC_T(1,C)                          vK1 = FCN_V(tgMH_MUL)( vET1, psET0->m_avEdge[2] );
    VEC_T(1,C)                          vK2 = FCN_V(tgMH_MAD)( vET0, psET0->m_avEdge[0], psET0->m_sPT.m_avPoint[0] );

    *pvET0 = FCN_V(tgMH_SUB)( vK2, vK1 );

    return (vDistSq);
}


/* ---- FCN_VO(tgCO_ET_Closest_PT) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_ET_Closest_PT)( VEC_T(1,PC) pvET0, VEC_OBJ_T(TgETRI,CPC) psET0, VEC_T(1,C) vS0 )
{
    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_ET_ClosestSq_PT)( pvET0, psET0, vS0 ) ));
}


/* ---- FCN_VO(tgCO_ET_Closest_PM_PT) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_ET_Closest_PM_PT)( VEC_T(1,PC) pvET0, VEC_T(1,PC) pvET1, VEC_OBJ_T(TgETRI,CPC) psET0, VEC_T(1,C) vS0 )
{
    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_ET_ClosestSq_PM_PT)( pvET0, pvET1, psET0, vS0 ) ));
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

    #define TGS_COLLISION_TRIANGLE_POINT_INL

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COLLISION_TRIANGLE_POINT_INL) */
#endif
