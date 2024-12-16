/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Rectangle-Line.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.18 | »GUID« 5BB31923-DAF4-437F-8513-C1B5BEEA163A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_RECTANGLE_LINE_INL)
#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* == Collision ================================================================================================================================================================== */

/* ---- FCN_VO(tgCO_RT_DistSq_LN) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_RT_DistSq_LN)( VEC_OBJ_T(TgRECTANGLE,CPC) psRT0, VEC_OBJ_T(TgLINE,CPC) psLN0 )
{
    VEC_T(1)                            vT0, vT1, vT2;

    return (FCN_VO(tgCO_RT_ClosestSq_PM_LN)( &vT0, &vT1, &vT2, psRT0, psLN0 ));
}


/* ---- FCN_VO(tgCO_RT_Dist_LN) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_RT_Dist_LN)( VEC_OBJ_T(TgRECTANGLE,CPC) psRT0, VEC_OBJ_T(TgLINE,CPC) psLN0 )
{
    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_RT_DistSq_LN)( psRT0, psLN0 ) ));
}


/* ---- FCN_VO(tgCO_RT_ClosestSq_LN) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_RT_ClosestSq_LN)( VEC_T(1,PC) pvRT0, VEC_T(1,PC) pvLN0, VEC_OBJ_T(TgRECTANGLE,CPC) psRT0, VEC_OBJ_T(TgLINE,CPC) psLN0 )
{
    VEC_T(1)                            vT0, vT1, vT2;

    VEC_T(1,C)                          vDistSq = FCN_VO(tgCO_RT_ClosestSq_PM_LN)( &vT0, &vT1, &vT2, psRT0, psLN0 );

    VEC_T(1,C)                          vX0 = FCN_V(tgMH_MAD)( vT0, psRT0->m_avEdge[0], psRT0->m_vOrigin );

    *pvRT0 = FCN_V(tgMH_MAD)( vT1, psRT0->m_avEdge[1], vX0 );
    *pvLN0 = FCN_V(tgMH_MAD)( vT2, psLN0->m_vDirN, psLN0->m_vOrigin );

    return (vDistSq);
}


/* ---- FCN_VO(tgCO_RT_Closest_LN) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_RT_Closest_LN)( VEC_T(1,PC) pvRT0, VEC_T(1,PC) pvLN0, VEC_OBJ_T(TgRECTANGLE,CPC) psRT0, VEC_OBJ_T(TgLINE,CPC) psLN0 )
{
    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_RT_ClosestSq_LN)( pvRT0, pvLN0, psRT0, psLN0 ) ));
}


/* ---- FCN_VO(tgCO_RT_ClosestSq_PM_LN) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_RT_ClosestSq_PM_LN)( VEC_T(1,PC) pvRT0, VEC_T(1,PC) pvRT1, VEC_T(1,PC) pvLN0, VEC_OBJ_T(TgRECTANGLE,CPC) psRT0, VEC_OBJ_T(TgLINE,CPC) psLN0 )
{
    return (FCN_VO(tgCO_RT_ClosestSq_PM_LR00)( pvRT0, pvRT1, pvLN0, psRT0, psLN0->m_vOrigin, psLN0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_RT_Closest_PM_LN) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_RT_Closest_PM_LN)( VEC_T(1,PC) pvRT0, VEC_T(1,PC) pvRT1, VEC_T(1,PC) pvLN0, VEC_OBJ_T(TgRECTANGLE,CPC) psRT0, VEC_OBJ_T(TgLINE,CPC) psLN0 )
{
    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_RT_ClosestSq_PM_LN)( pvRT0, pvRT1, pvLN0, psRT0, psLN0 ) ));
}


/* ---- FCN_VO(tgCO_RT_Test_LN) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_VO(tgCO_RT_Test_LN)( VEC_OBJ_T(TgRECTANGLE,CPC) psRT0, VEC_OBJ_T(TgLINE,CPC) psLN0 )
{
    VEC_T(1,C)                          vDistSq = FCN_VO(tgCO_RT_DistSq_LN)( psRT0, psLN0 );

    return (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vDistSq, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ));
}


/* ---- FCN_VO(tgCO_RT_Clip_LN) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_RT_Clip_LN)( VEC_OBJ_T(STg2_CO_Clip_List,PC) psCL, VEC_OBJ_T(TgRECTANGLE,CPC) psRT0, VEC_OBJ_T(TgLINE,CPC) psLN0 )
{
    return (FCN_VO(tgCO_RT_Clip_LR00)( psCL, psRT0, psLN0->m_vOrigin, psLN0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_RT_Clip_PM_LN) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_RT_Clip_PM_LN)( VEC_T(1,PC) pvLN0, VEC_T(1,PC) pvLN1, VEC_OBJ_T(TgRECTANGLE,CPC) psRT0, VEC_OBJ_T(TgLINE,CPC) psLN0 )
{
    return (FCN_VO(tgCO_RT_Clip_PM_LR00)( pvLN0, pvLN1, psRT0, psLN0->m_vOrigin, psLN0->m_vDirN ));
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

    #define TGS_COLLISION_RECTANGLE_LINE_INL

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COLLISION_RECTANGLE_LINE_INL) */
#endif
