/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Rectangle-Segment.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.18 | »GUID« 5BB31923-DAF4-437F-8513-C1B5BEEA163A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_RECTANGLE_SEGMENT_INL)
#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* == Collision ================================================================================================================================================================== */

/* ---- FCN_VO(tgCO_RT_DistSq_SG) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_RT_DistSq_SG)( VEC_OBJ_T(TgRECTANGLE,CPC) psRT0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    VEC_T(1)                            vT0, vT1, vT2;

    return (FCN_VO(tgCO_RT_ClosestSq_PM_SG)( &vT0, &vT1, &vT2, psRT0, psSG0 ));
}


/* ---- FCN_VO(tgCO_RT_Dist_SG) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_RT_Dist_SG)( VEC_OBJ_T(TgRECTANGLE,CPC) psRT0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_RT_DistSq_SG)( psRT0, psSG0 ) ));
}


/* ---- FCN_VO(tgCO_RT_ClosestSq_SG) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_RT_ClosestSq_SG)( VEC_T(1,PC) pvRT0, VEC_T(1,PC) pvSG0, VEC_OBJ_T(TgRECTANGLE,CPC) psRT0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    VEC_T(1)                            vT0, vT1, vT2;

    VEC_T(1,C)                          vDistSq = FCN_VO(tgCO_RT_ClosestSq_PM_SG)( &vT0, &vT1, &vT2, psRT0, psSG0 );

    VEC_T(1,C)                          vX0 = FCN_V(tgMH_MAD)( vT0, psRT0->m_avEdge[0], psRT0->m_vOrigin );

    *pvRT0 = FCN_V(tgMH_MAD)( vT1, psRT0->m_avEdge[1], vX0 );
    *pvSG0 = FCN_V(tgMH_MAD)( vT2, psSG0->m_vDirN, psSG0->m_vOrigin );

    return (vDistSq);
}


/* ---- FCN_VO(tgCO_RT_Closest_SG) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_RT_Closest_SG)( VEC_T(1,PC) pvRT0, VEC_T(1,PC) pvSG0, VEC_OBJ_T(TgRECTANGLE,CPC) psRT0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_RT_ClosestSq_SG)( pvRT0, pvSG0, psRT0, psSG0 ) ));
}


/* ---- FCN_VO(tgCO_RT_ClosestSq_PM_SG) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_RT_ClosestSq_PM_SG)( VEC_T(1,PC) pvRT0, VEC_T(1,PC) pvRT1, VEC_T(1,PC) pvSG0, VEC_OBJ_T(TgRECTANGLE,CPC) psRT0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    return (FCN_VO(tgCO_RT_ClosestSq_PM_LR11)( pvRT0, pvRT1, pvSG0, psRT0, psSG0->m_vOrigin, psSG0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_RT_Closest_PM_SG) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_RT_Closest_PM_SG)( VEC_T(1,PC) pvRT0, VEC_T(1,PC) pvRT1, VEC_T(1,PC) pvSG0, VEC_OBJ_T(TgRECTANGLE,CPC) psRT0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_RT_ClosestSq_PM_SG)( pvRT0, pvRT1, pvSG0, psRT0, psSG0 ) ));
}


/* ---- FCN_VO(tgCO_RT_Test_SG) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_VO(tgCO_RT_Test_SG)( VEC_OBJ_T(TgRECTANGLE,CPC) psRT0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    VEC_T(1,C)                          vDistSq = FCN_VO(tgCO_RT_DistSq_SG)( psRT0, psSG0 );

    return (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vDistSq, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ));
}


/* ---- FCN_VO(tgCO_RT_Clip_SG) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_RT_Clip_SG)( VEC_OBJ_T(STg2_CO_Clip_List,PC) psCL, VEC_OBJ_T(TgRECTANGLE,CPC) psRT0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    return (FCN_VO(tgCO_RT_Clip_LR11)( psCL, psRT0, psSG0->m_vOrigin, psSG0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_RT_Clip_PM_SG) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_RT_Clip_PM_SG)( VEC_T(1,PC) pvSG0, VEC_T(1,PC) pvSG1, VEC_OBJ_T(TgRECTANGLE,CPC) psRT0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    return (FCN_VO(tgCO_RT_Clip_PM_LR11)( pvSG0, pvSG1, psRT0, psSG0->m_vOrigin, psSG0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_RT_Clip_Points) ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_RT_Clip_Points)( VEC_T(1,PC) pvSG0, VEC_T(1,PC) pvSG1, VEC_OBJ_T(TgRECTANGLE,CPC) psRT0, VEC_T(1,C) vS0, VEC_T(1,C) vS1 )
{
    VEC_T(1)                            vD0;

    vD0 = FCN_V(tgMH_SUB)( vS1, vS0 );
    return (FCN_VO(tgCO_RT_Clip_PM_LR11)( pvSG0, pvSG1, psRT0, vS0, vD0 ));
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

    #define TGS_COLLISION_RECTANGLE_SEGMENT_INL

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COLLISION_RECTANGLE_SEGMENT_INL) */
#endif
