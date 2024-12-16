/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Parallelogram-Triangle.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_PARALLELOGRAM_TRIANGLE_INL)
#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* == Collision ================================================================================================================================================================== */

/* ---- FCN_VO(tgCO_PE_DistSq_ST) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_PE_DistSq_ST)( VEC_OBJ_T(TgPARALLELOGRAM,CPC) psPE0, VEC_OBJ_T(TgSTRI,CPC) psST0 )
{
    VEC_T(1)                            vPE00, vPE01, vET10, vET11;

    return (FCN_VO(tgCO_PE_ClosestSq_PM_ST)( &vPE00, &vPE01, &vET10, &vET11, psPE0, psST0 ));
}


/* ---- FCN_VO(tgCO_PE_Dist_ST) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_PE_Dist_ST)( VEC_OBJ_T(TgPARALLELOGRAM,CPC) psPE0, VEC_OBJ_T(TgSTRI,CPC) psST0 )
{
    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_PE_DistSq_ST)( psPE0, psST0 ) ));
}


/* ---- FCN_VO(tgCO_PE_ClosestSq_ST) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_PE_ClosestSq_ST)( VEC_T(1,PC) pvPE0, VEC_T(1,PC) pvST0, VEC_OBJ_T(TgPARALLELOGRAM,CPC) psPE0, VEC_OBJ_T(TgSTRI,CPC) psST0 )
{
    VEC_T(1)                            vPE0, vPE1, vST0, vST1;

    VEC_T(1,C)                          vDistSq = FCN_VO(tgCO_PE_ClosestSq_PM_ST)( &vPE0, &vPE1, &vST0, &vST1, psPE0, psST0 );

    VEC_T(1,C)                          vK0 = FCN_V(tgMH_MUL)( vPE0, psPE0->m_avEdge[0] );
    VEC_T(1,C)                          vK1 = FCN_V(tgMH_MUL)( vPE1, psPE0->m_avEdge[1] );
    VEC_T(1,C)                          vK2 = FCN_V(tgMH_MUL)( vST0, psST0->m_sCT.m_sET.m_avEdge[0] );
    VEC_T(1,C)                          vK3 = FCN_V(tgMH_MUL)( vST1, psST0->m_sCT.m_sET.m_avEdge[2] );
    VEC_T(1,C)                          vK4 = FCN_V(tgMH_ADD)( psPE0->m_vOrigin, vK0 );
    VEC_T(1,C)                          vK5 = FCN_V(tgMH_ADD)( psST0->m_sCT.m_sET.m_sPT.m_avPoint[0], vK2 );

    *pvPE0 = FCN_V(tgMH_ADD)( vK4, vK1 );
    *pvST0 = FCN_V(tgMH_SUB)( vK5, vK3 );

    return (vDistSq);
}


/* ---- FCN_VO(tgCO_PE_Closest_ST) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_PE_Closest_ST)( VEC_T(1,PC) pvPE0, VEC_T(1,PC) pvST0, VEC_OBJ_T(TgPARALLELOGRAM,CPC) psPE0, VEC_OBJ_T(TgSTRI,CPC) psST0 )
{
    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_PE_ClosestSq_ST)( pvPE0, pvST0, psPE0, psST0 ) ));
}


/* ---- FCN_VO(tgCO_PE_Closest_PM_ST) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_PE_Closest_PM_ST)( VEC_T(1,PC) pvPE0, VEC_T(1,PC) pvPE1, VEC_T(1,PC) pvST0, VEC_T(1,PC) pvST1, VEC_OBJ_T(TgPARALLELOGRAM,CPC) psPE0, VEC_OBJ_T(TgSTRI,CPC) psST0 )
{
    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_PE_ClosestSq_PM_ST)( pvPE0, pvPE1, pvST0, pvST1, psPE0, psST0 ) ));
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

    #define TGS_COLLISION_PARALLELOGRAM_TRIANGLE_INL

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COLLISION_PARALLELOGRAM_TRIANGLE_INL) */
#endif
