/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Triangle-Triangle.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.18 | »GUID« 5BB31923-DAF4-437F-8513-C1B5BEEA163A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_TRIANGLE_TRIANGLE_INL)
#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* == Collision ================================================================================================================================================================== */

/* ---- FCN_VO(tgCO_ST_DistSq_ST) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_ST_DistSq_ST)( VEC_OBJ_T(TgSTRI,CPC) psST0, VEC_OBJ_T(TgSTRI,CPC) psST1 )
{
    VEC_T(1)                            vET00, vET01, vET10, vET11;

    return (FCN_VO(tgCO_ST_ClosestSq_PM_ST)( &vET00, &vET01, &vET10, &vET11, psST0, psST1 ));
}


/* ---- FCN_VO(tgCO_ST_Dist_ST) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_ST_Dist_ST)( VEC_OBJ_T(TgSTRI,CPC) psST0, VEC_OBJ_T(TgSTRI,CPC) psST1 )
{
    VEC_T(1)                            vET00, vET01, vET10, vET11;

    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_ST_ClosestSq_PM_ST)( &vET00, &vET01, &vET10, &vET11, psST0, psST1 ) ));
}


/* ---- FCN_VO(tgCO_ST_ClosestSq_ST) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_ST_ClosestSq_ST)( VEC_T(1,PC) pvET0, VEC_T(1,PC) pvET1, VEC_OBJ_T(TgSTRI,CPC) psST0, VEC_OBJ_T(TgSTRI,CPC) psST1 )
{
    VEC_T(1)                            vET00, vET01, vET10, vET11;

    VEC_T(1,C)                          vDistSq = FCN_VO(tgCO_ST_ClosestSq_PM_ST)( &vET00, &vET01, &vET10, &vET11, psST0, psST1 );

    VEC_T(1,C)                          vK1 = FCN_V(tgMH_MUL)( vET01, psST0->m_sCT.m_sET.m_avEdge[2] );
    VEC_T(1,C)                          vK3 = FCN_V(tgMH_MUL)( vET11, psST1->m_sCT.m_sET.m_avEdge[2] );
    VEC_T(1,C)                          vK4 = FCN_V(tgMH_MAD)( vET00, psST0->m_sCT.m_sET.m_avEdge[0], psST0->m_sCT.m_sET.m_sPT.m_avPoint[0] );
    VEC_T(1,C)                          vK5 = FCN_V(tgMH_MAD)( vET10, psST1->m_sCT.m_sET.m_avEdge[0], psST1->m_sCT.m_sET.m_sPT.m_avPoint[0] );

    *pvET0 = FCN_V(tgMH_SUB)( vK4, vK1 );
    *pvET1 = FCN_V(tgMH_SUB)( vK5, vK3 );

    return (vDistSq);
}


/* ---- FCN_VO(tgCO_ST_Closest_ST) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_ST_Closest_ST)( VEC_T(1,PC) pvET0, VEC_T(1,PC) pvET1, VEC_OBJ_T(TgSTRI,CPC) psST0, VEC_OBJ_T(TgSTRI,CPC) psST1 )
{
    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_ST_ClosestSq_ST)( pvET0, pvET1, psST0, psST1 ) ));
}


/* ---- FCN_VO(tgCO_ST_Closest_PM_ST) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_ST_Closest_PM_ST)( VEC_T(1,PC) pvET00, VEC_T(1,PC) pvET01, VEC_T(1,PC) pvET10, VEC_T(1,PC) pvET11, VEC_OBJ_T(TgSTRI,CPC) psST0,
                                                 VEC_OBJ_T(TgSTRI,CPC) psST1 )
{
    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_ST_ClosestSq_PM_ST)( pvET00, pvET01, pvET10, pvET11, psST0, psST1 ) ));
}


/* ---- FCN_VO(tgCO_ST_Clip_PT) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_ST_Clip_PT)( VEC_OBJ_T(STg2_CO_Clip_List,PC) psCL, VEC_OBJ_T(TgSTRI,CPC) psST0, VEC_OBJ_T(TgPTRI,CPC) psPT0 )
{
    if (psCL->m_nuiMax < 6)
    {
        TgERROR(false);
        return (KTgE_FAIL);
    };

    psCL->m_avPoint[0] = FCN_VO(tgGM_PT_Query_Point_0)( psPT0 );
    psCL->m_avPoint[1] = FCN_VO(tgGM_PT_Query_Point_1)( psPT0 );
    psCL->m_avPoint[2] = FCN_VO(tgGM_PT_Query_Point_2)( psPT0 );

    psCL->m_nuiPoint = 3;

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

    #define TGS_COLLISION_TRIANGLE_TRIANGLE_INL

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COLLISION_TRIANGLE_TRIANGLE_INL) */
#endif
