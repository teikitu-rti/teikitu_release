/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Triangle [Util].inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.18 | »GUID« 5BB31923-DAF4-437F-8513-C1B5BEEA163A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_TRIANGLE_UTIL_INL)

#include "TgS COLLISION/TgS Collision - Triangle-Segment.inl"

#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* == Collision ================================================================================================================================================================== */

/* ---- FCN_VO(tgCO_ST_Clip_Points) ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_ST_Clip_Points)( VEC_T(1,PC) pvSG0, VEC_T(1,PC) pvSG1, VEC_OBJ_T(TgSTRI,CPC) psST0, VEC_T(1,C) vS0, VEC_T(1,C) vS1 )
{
    VEC_T(1)                            vD0;

    vD0 = FCN_V(tgMH_SUB)( vS1, vS0 );
    return (FCN_VO(tgCO_ST_Clip_PM_LR11)( pvSG0, pvSG1, psST0, vS0, vD0 ));
}


/* ---- FCN_VO(tgCO_Clip_ST) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_Clip_ST)( VEC_OBJ_T(STg2_CO_Clip_List,PC) psCL, VEC_OBJ_T(TgSTRI,CPC) psST0 )
{
    if (TgFAILED( FCN_VO(tgCO_PN_Clip)( psCL, psST0->m_avPlane + 0 ) ) || 0 != psCL->m_nuiPoint)
    {
        return (KTgE_FAIL);
    };

    if (TgFAILED( FCN_VO(tgCO_PN_Clip)( psCL, psST0->m_avPlane + 1 ) ) || 0 != psCL->m_nuiPoint)
    {
        return (KTgE_FAIL);
    };

    if (TgFAILED( FCN_VO(tgCO_PN_Clip)( psCL, psST0->m_avPlane + 2 ) ) || 0 != psCL->m_nuiPoint)
    {
        return (KTgE_FAIL);
    };

    return (KTgS_OK);
}


/* ---- FCN_VO(tgCO_Clip_ET) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_Clip_ET)( VEC_OBJ_T(STg2_CO_Clip_List,PC) psCL, VEC_OBJ_T(TgETRI,CPC) psET0 )
{
    VEC_OBJ_T(TgPLANE)                  sPN0;
    VEC_T(1)                            vK0;

    vK0 = FCN_V(tgMH_CX)( psET0->m_sPT.m_vNormal, psET0->m_avEdge[0] );
    FCN_VO(tgGM_PN_Init_NP)( &sPN0, vK0, psET0->m_sPT.m_avPoint[0] );
    if (TgFAILED(FCN_VO(tgCO_PN_Clip)( psCL, &sPN0 )))
    {
        return (KTgE_FAIL);
    };
    if (0 == psCL->m_nuiPoint) return (KTgS_OK);

    vK0 = FCN_V(tgMH_CX)( psET0->m_sPT.m_vNormal, psET0->m_avEdge[1] );
    FCN_VO(tgGM_PN_Init_NP)( &sPN0, vK0, psET0->m_sPT.m_avPoint[1] );
    if (TgFAILED(FCN_VO(tgCO_PN_Clip)( psCL, &sPN0 )))
    {
        return (KTgE_FAIL);
    };
    if (0 == psCL->m_nuiPoint) return (KTgS_OK);

    vK0 = FCN_V(tgMH_CX)( psET0->m_sPT.m_vNormal, psET0->m_avEdge[2] );
    FCN_VO(tgGM_PN_Init_NP)( &sPN0, vK0, psET0->m_sPT.m_avPoint[2] );
    if (TgFAILED(FCN_VO(tgCO_PN_Clip)( psCL, &sPN0 )))
    {
        return (KTgE_FAIL);
    };
    return (KTgS_OK);
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

    #define TGS_COLLISION_TRIANGLE_UTIL_INL

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COLLISION_TRIANGLE_UTIL_INL) */
#endif
