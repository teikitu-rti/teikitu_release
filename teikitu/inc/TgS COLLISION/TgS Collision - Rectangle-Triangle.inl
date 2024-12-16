/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Rectangle-Triangle.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.18 | »GUID« 5BB31923-DAF4-437F-8513-C1B5BEEA163A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_RECTANGLE_TRIANGLE_INL)
#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* == Collision ================================================================================================================================================================== */

/* ---- FCN_VO(tgCO_RT_DistSq_ST) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_RT_DistSq_ST)( VEC_OBJ_T(TgRECTANGLE,CPC) psRT0, VEC_OBJ_T(TgSTRI,CPC) psST0 )
{
    VEC_T(1)                            vT0, vT1, vT2, vT3;

    return (FCN_VO(tgCO_RT_ClosestSq_PM_ST)( &vT0, &vT1, &vT2, &vT3, psRT0, psST0 ));
}


/* ---- FCN_VO(tgCO_RT_Dist_ST) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_RT_Dist_ST)( VEC_OBJ_T(TgRECTANGLE,CPC) psRT0, VEC_OBJ_T(TgSTRI,CPC) psST0 )
{
    VEC_T(1)                            vT0, vT1, vT2, vT3;

    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_RT_ClosestSq_PM_ST)( &vT0, &vT1, &vT2, &vT3, psRT0, psST0 ) ));
}


/* ---- FCN_VO(tgCO_RT_ClosestSq_ST) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_RT_ClosestSq_ST)( VEC_T(1,PC) pvRT0, VEC_T(1,PC) pvST0, VEC_OBJ_T(TgRECTANGLE,CPC) psRT0, VEC_OBJ_T(TgSTRI,CPC) psST0 )
{
    VEC_T(1)                            vRT00, vRT01, vST00, vST01;

    VEC_T(1,C)                          vDistSq = FCN_VO(tgCO_RT_ClosestSq_PM_ST)( &vRT00, &vRT01, &vST00, &vST01, psRT0, psST0 );

    VEC_T(1,C)                          vX0 = FCN_V(tgMH_MAD)( vRT00, psRT0->m_avEdge[0], psRT0->m_vOrigin );
    VEC_T(1,C)                          vX1 = FCN_V(tgMH_MAD)( vST00, psST0->m_sCT.m_sET.m_avEdge[0], psST0->m_sCT.m_sET.m_sPT.m_avPoint[0] );
    VEC_T(1,C)                          vX2 = FCN_V(tgMH_MUL)( vST01, psST0->m_sCT.m_sET.m_avEdge[2] );

    *pvRT0 = FCN_V(tgMH_MAD)( vRT01, psRT0->m_avEdge[1], vX0 );
    *pvST0 = FCN_V(tgMH_SUB)( vX1, vX2 );

    return (vDistSq);
}


/* ---- FCN_VO(tgCO_RT_Closest_ST) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_RT_Closest_ST)( VEC_T(1,PC) pvRT0, VEC_T(1,PC) pvST0, VEC_OBJ_T(TgRECTANGLE,CPC) psRT0, VEC_OBJ_T(TgSTRI,CPC) psST0 )
{
    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_RT_ClosestSq_ST)( pvRT0, pvST0, psRT0, psST0 ) ));
}


/* ---- FCN_VO(tgCO_RT_Closest_PM_ST) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_RT_Closest_PM_ST)( VEC_T(1,PC) pvRT0, VEC_T(1,PC) pvRT1, VEC_T(1,PC) pvST0, VEC_T(1,PC) pvST1, VEC_OBJ_T(TgRECTANGLE,CPC) psRT0,
                                                 VEC_OBJ_T(TgSTRI,CPC) psST0 )
{
    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_RT_ClosestSq_PM_ST)( pvRT0, pvRT1, pvST0, pvST1, psRT0, psST0 ) ));
}


/* ---- FCN_VO(tgCO_RT_Clip_ST) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_RT_Clip_ST)( VEC_OBJ_T(STg2_CO_Clip_List,PC) psCL, VEC_OBJ_T(TgRECTANGLE,CPC) psRT0, VEC_OBJ_T(TgSTRI,CPC) psST0 )
{
    if (psCL->m_nuiMax < 8)
    {
        TgERROR(false);
        return (KTgE_FAIL);
    };

    psCL->m_avPoint[0] = psRT0->m_vOrigin;
    psCL->m_avPoint[1] = FCN_VO(tgGM_RT_Query_Point_1)( psRT0 );
    psCL->m_avPoint[2] = FCN_VO(tgGM_RT_Query_Point_2)( psRT0 );
    psCL->m_avPoint[3] = FCN_VO(tgGM_RT_Query_Point_3)( psRT0 );

    psCL->m_nuiPoint = 4;

    return (FCN_VO(tgCO_ST_Clip)( psCL, psST0 ));
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

    #define TGS_COLLISION_RECTANGLE_TRIANGLE_INL

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COLLISION_RECTANGLE_TRIANGLE_INL) */
#endif
