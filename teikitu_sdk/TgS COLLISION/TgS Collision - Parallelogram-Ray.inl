/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Parallelogram-Ray.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_PARALLELOGRAM_RAY_INL)
#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* == Collision ================================================================================================================================================================== */

/* ---- FCN_VO(tgCO_PE_DistSq_RY) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_PE_DistSq_RY)( VEC_OBJ_T(TgPARALLELOGRAM,CPC) psPE0, VEC_OBJ_T(TgRAY,CPC) psRY0 )
{
    VEC_T(1)                            vT0, vT1, vT2;

    return (FCN_VO(tgCO_PE_ClosestSq_PM_RY)( &vT0, &vT1, &vT2, psPE0, psRY0 ));
}


/* ---- FCN_VO(tgCO_PE_Dist_RY) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_PE_Dist_RY)( VEC_OBJ_T(TgPARALLELOGRAM,CPC) psPE0, VEC_OBJ_T(TgRAY,CPC) psRY0 )
{
    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_PE_DistSq_RY)( psPE0, psRY0 ) ));
}


/* ---- FCN_VO(tgCO_PE_ClosestSq_RY) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_PE_ClosestSq_RY)( VEC_T(1,PC) pvPE0, VEC_T(1,PC) pvRY0, VEC_OBJ_T(TgPARALLELOGRAM,CPC) psPE0, VEC_OBJ_T(TgRAY,CPC) psRY0 )
{
    VEC_T(1)                            vT0, vT1, vT2;

    VEC_T(1,C)                          vDistSq = FCN_VO(tgCO_PE_ClosestSq_PM_RY)( &vT0, &vT1, &vT2, psPE0, psRY0 );
    VEC_T(1,C)                          vK0 = FCN_V(tgMH_MUL)( vT0, psPE0->m_avEdge[0] );
    VEC_T(1,C)                          vK1 = FCN_V(tgMH_MUL)( vT1, psPE0->m_avEdge[1] );
    VEC_T(1,C)                          vK2 = FCN_V(tgMH_ADD)( vK0, vK1 );
    VEC_T(1,C)                          vK3 = FCN_V(tgMH_MUL)( vT2, psRY0->m_vDirN );

    *pvPE0 = FCN_V(tgMH_ADD)( psPE0->m_vOrigin, vK2 );
    *pvRY0 = FCN_V(tgMH_ADD)( psRY0->m_vOrigin, vK3 );

    return (vDistSq);
}


/* ---- FCN_VO(tgCO_PE_Closest_RY) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_PE_Closest_RY)( VEC_T(1,PC) pvPE0, VEC_T(1,PC) pvRY0, VEC_OBJ_T(TgPARALLELOGRAM,CPC) psPE0, VEC_OBJ_T(TgRAY,CPC) psRY0 )
{
    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_PE_ClosestSq_RY)( pvPE0, pvRY0, psPE0, psRY0 ) ));
}


/* ---- FCN_VO(tgCO_PE_ClosestSq_PM_RY) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_PE_ClosestSq_PM_RY)( VEC_T(1,PC) pvPE0, VEC_T(1,PC) pvPE1, VEC_T(1,PC) pvRY0, VEC_OBJ_T(TgPARALLELOGRAM,CPC) psPE0, VEC_OBJ_T(TgRAY,CPC) psRY0 )
{
    return (FCN_VO(tgCO_PE_Closest_PM_LR10)( pvPE0, pvPE1, pvRY0, psPE0, psRY0->m_vOrigin, psRY0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_PE_Closest_PM_RY) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_PE_Closest_PM_RY)( VEC_T(1,PC) pvPE0, VEC_T(1,PC) pvPE1, VEC_T(1,PC) pvRY0, VEC_OBJ_T(TgPARALLELOGRAM,CPC) psPE0, VEC_OBJ_T(TgRAY,CPC) psRY0 )
{
    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_PE_ClosestSq_PM_RY)( pvPE0, pvPE1, pvRY0, psPE0, psRY0 ) ));
}


/* ---- FCN_VO(tgCO_PE_Test_RY) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_VO(tgCO_PE_Test_RY)( VEC_OBJ_T(TgPARALLELOGRAM,CPC) psPE0, VEC_OBJ_T(TgRAY,CPC) psRY0 )
{
    return (FCN_VO(tgCO_PE_Test_LR10)( psPE0, psRY0->m_vOrigin, psRY0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_PE_Clip_PM_RY) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_PE_Clip_PM_RY)( VEC_T(1,PC) pvRY0, VEC_T(1,PC) pvRY1, VEC_OBJ_T(TgPARALLELOGRAM,CPC) psPE0, VEC_OBJ_T(TgRAY,CPC) psRY0 )
{
    return (FCN_VO(tgCO_PE_Clip_PM_LR10)( pvRY0, pvRY1, psPE0, psRY0->m_vOrigin, psRY0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_PE_Clip_RY) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_PE_Clip_RY)( VEC_OBJ_T(STg2_CO_Clip_List,PC) psCL, VEC_OBJ_T(TgPARALLELOGRAM,CPC) psPE0, VEC_OBJ_T(TgRAY,CPC) psRY0 )
{
    return (FCN_VO(tgCO_PE_Clip_LR10)( psCL, psPE0, psRY0->m_vOrigin, psRY0->m_vDirN ));
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

    #define TGS_COLLISION_PARALLELOGRAM_RAY_INL

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COLLISION_PARALLELOGRAM_RAY_INL) */
#endif
