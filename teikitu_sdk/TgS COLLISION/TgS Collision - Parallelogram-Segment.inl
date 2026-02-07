/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Parallelogram-Segment.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_PARALLELOGRAM_SEGMENT_INL)
#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* == Collision ================================================================================================================================================================== */

/* ---- FCN_VO(tgCO_PE_DistSq_SG) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_PE_DistSq_SG)( VEC_OBJ_T(TgPARALLELOGRAM,CPC) psPE0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    VEC_T(1)                            vT0, vT1, vT2;

    return (FCN_VO(tgCO_PE_ClosestSq_PM_SG)( &vT0, &vT1, &vT2, psPE0, psSG0 ));
}


/* ---- FCN_VO(tgCO_PE_Dist_SG) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_PE_Dist_SG)( VEC_OBJ_T(TgPARALLELOGRAM,CPC) psPE0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_PE_DistSq_SG)( psPE0, psSG0 ) ));
}


/* ---- FCN_VO(tgCO_PE_ClosestSq_SG) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_PE_ClosestSq_SG)( VEC_T(1,PC) pvPE0, VEC_T(1,PC) pvSG0, VEC_OBJ_T(TgPARALLELOGRAM,CPC) psPE0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    VEC_T(1)                            vT0, vT1, vT2;

    VEC_T(1,C)                          vDistSq = FCN_VO(tgCO_PE_ClosestSq_PM_SG)( &vT0, &vT1, &vT2, psPE0, psSG0 );
    VEC_T(1,C)                          vK0 = FCN_V(tgMH_MUL)( vT0, psPE0->m_avEdge[0] );
    VEC_T(1,C)                          vK1 = FCN_V(tgMH_MUL)( vT1, psPE0->m_avEdge[1] );
    VEC_T(1,C)                          vK2 = FCN_V(tgMH_ADD)( vK0, vK1 );
    VEC_T(1,C)                          vK3 = FCN_V(tgMH_MUL)( vT2, psSG0->m_vDirN );

    *pvPE0 = FCN_V(tgMH_ADD)( psPE0->m_vOrigin, vK2 );
    *pvSG0 = FCN_V(tgMH_ADD)( psSG0->m_vOrigin, vK3 );

    return (vDistSq);
}


/* ---- FCN_VO(tgCO_PE_Closest_SG) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_PE_Closest_SG)( VEC_T(1,PC) pvPE0, VEC_T(1,PC) pvSG0, VEC_OBJ_T(TgPARALLELOGRAM,CPC) psPE0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_PE_ClosestSq_SG)( pvPE0, pvSG0, psPE0, psSG0 ) ));
}


/* ---- FCN_VO(tgCO_PE_ClosestSq_PM_SG) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_PE_ClosestSq_PM_SG)( VEC_T(1,PC) pvPE0, VEC_T(1,PC) pvPE1, VEC_T(1,PC) pvSG0, VEC_OBJ_T(TgPARALLELOGRAM,CPC) psPE0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    return (FCN_VO(tgCO_PE_ClosestSq_PM_LR11)( pvPE0, pvPE1, pvSG0, psPE0, psSG0->m_vOrigin, psSG0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_PE_Closest_PM_SG) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_PE_Closest_PM_SG)( VEC_T(1,PC) pvPE0, VEC_T(1,PC) pvPE1, VEC_T(1,PC) pvSG0, VEC_OBJ_T(TgPARALLELOGRAM,CPC) psPE0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_PE_ClosestSq_PM_SG)( pvPE0, pvPE1, pvSG0, psPE0, psSG0 ) ));
}


/* ---- FCN_VO(tgCO_PE_Test_SG) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_VO(tgCO_PE_Test_SG)( VEC_OBJ_T(TgPARALLELOGRAM,CPC) psPE0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    return (FCN_VO(tgCO_PE_Test_LR11)( psPE0, psSG0->m_vOrigin, psSG0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_PE_Clip_PM_SG) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_PE_Clip_PM_SG)( VEC_T(1,PC) pvSG0, VEC_T(1,PC) pvSG1, VEC_OBJ_T(TgPARALLELOGRAM,CPC) psPE0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    return (FCN_VO(tgCO_PE_Clip_PM_LR11)( pvSG0, pvSG1, psPE0, psSG0->m_vOrigin, psSG0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_PE_Clip_SG) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_PE_Clip_SG)( VEC_OBJ_T(STg2_CO_Clip_List,PC) psCL, VEC_OBJ_T(TgPARALLELOGRAM,CPC) psPE0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    return (FCN_VO(tgCO_PE_Clip_LR11)( psCL, psPE0, psSG0->m_vOrigin, psSG0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_PE_Clip_Points) ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_PE_Clip_Points)( VEC_T(1,PC) pvSG0, VEC_T(1,PC) pvSG1, VEC_OBJ_T(TgPARALLELOGRAM,CPC) psPE0, VEC_T(1,C) vS0, VEC_T(1,C) vS1 )
{
    VEC_T(1)                            vD0;

    vD0 = FCN_V(tgMH_SUB)( vS1, vS0 );
    return (FCN_VO(tgCO_PE_Clip_PM_LR11)( pvSG0, pvSG1, psPE0, vS0, vD0 ));
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

    #define TGS_COLLISION_PARALLELOGRAM_SEGMENT_INL

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COLLISION_PARALLELOGRAM_SEGMENT_INL) */
#endif
