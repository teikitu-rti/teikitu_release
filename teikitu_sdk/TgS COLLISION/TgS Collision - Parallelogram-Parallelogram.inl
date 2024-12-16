/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Parallelogram-Parallelogram.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_PARALLELOGRAM_PARALLELOGRAM_INL)
#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* == Collision ================================================================================================================================================================== */

/* ---- FCN_VO(tgCO_PE_DistSq_PE) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_PE_DistSq_PE)( VEC_OBJ_T(TgPARALLELOGRAM,CPC) psPE0, VEC_OBJ_T(TgPARALLELOGRAM,CPC) psPE1 )
{
    VEC_T(1)                            vPE00, vPE01, vPE10, vPE11;

    return (FCN_VO(tgCO_PE_ClosestSq_PM_PE)( &vPE00, &vPE01, &vPE10, &vPE11, psPE0, psPE1 ));
}


/* ---- FCN_VO(tgCO_PE_Dist_PE) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_PE_Dist_PE)( VEC_OBJ_T(TgPARALLELOGRAM,CPC) psPE0, VEC_OBJ_T(TgPARALLELOGRAM,CPC) psPE1 )
{
    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_PE_DistSq_PE)( psPE0, psPE1 ) ));
}


/* ---- FCN_VO(tgCO_PE_ClosestSq_PE) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_PE_ClosestSq_PE)( VEC_T(1,PC) pvPE0, VEC_T(1,PC) pvPE1, VEC_OBJ_T(TgPARALLELOGRAM,CPC) psPE0, VEC_OBJ_T(TgPARALLELOGRAM,CPC) psPE1 )
{
    VEC_T(1)                            vPE00, vPE01, vPE10, vPE11;

    VEC_T(1,C)                          vDistSq = FCN_VO(tgCO_PE_ClosestSq_PM_PE)( &vPE00, &vPE01, &vPE10, &vPE11, psPE0, psPE1 );

    VEC_T(1,C)                          vK0 = FCN_V(tgMH_MUL)( vPE00, psPE0->m_avEdge[0] );
    VEC_T(1,C)                          vK1 = FCN_V(tgMH_MUL)( vPE01, psPE0->m_avEdge[1] );
    VEC_T(1,C)                          vK2 = FCN_V(tgMH_MUL)( vPE10, psPE1->m_avEdge[0] );
    VEC_T(1,C)                          vK3 = FCN_V(tgMH_MUL)( vPE11, psPE1->m_avEdge[1] );
    VEC_T(1,C)                          vK4 = FCN_V(tgMH_ADD)( psPE0->m_vOrigin, vK0 );
    VEC_T(1,C)                          vK5 = FCN_V(tgMH_ADD)( psPE1->m_vOrigin, vK2 );

    *pvPE0 = FCN_V(tgMH_ADD)( vK4, vK1 );
    *pvPE1 = FCN_V(tgMH_ADD)( vK5, vK3 );

    return (vDistSq);
}


/* ---- FCN_VO(tgCO_PE_Closest_PE) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_PE_Closest_PE)( VEC_T(1,PC) pvPE0, VEC_T(1,PC) pvPE1, VEC_OBJ_T(TgPARALLELOGRAM,CPC) psPE0, VEC_OBJ_T(TgPARALLELOGRAM,CPC) psPE1 )
{
    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_PE_ClosestSq_PE)( pvPE0, pvPE1, psPE0, psPE1 ) ));
}


/* ---- FCN_VO(tgCO_PE_Closest_PM_PE) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_PE_Closest_PM_PE)( VEC_T(1,PC) pvPE00, VEC_T(1,PC) pvPE01, VEC_T(1,PC) pvPE10, VEC_T(1,PC) pvPE11, VEC_OBJ_T(TgPARALLELOGRAM,CPC) psPE0,
                                                 VEC_OBJ_T(TgPARALLELOGRAM,CPC) psPE1 )
{
    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_PE_ClosestSq_PM_PE)( pvPE00, pvPE01, pvPE10, pvPE11, psPE0, psPE1 ) ));
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

    #define TGS_COLLISION_PARALLELOGRAM_PARALLELOGRAM_INL

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COLLISION_PARALLELOGRAM_PARALLELOGRAM_INL) */
#endif
