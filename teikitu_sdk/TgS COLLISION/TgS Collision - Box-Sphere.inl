/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Box-Sphere.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.18 | »GUID« 5BB31923-DAF4-437F-8513-C1B5BEEA163A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_BOX_SPHERE_INL)
#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* == Collision ================================================================================================================================================================== */

/* ---- FCN_VO(tgCO_BX_DistSq_SP) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_BX_DistSq_SP)( VEC_OBJ_T(TgBOX,CPC) psBX0, VEC_OBJ_T(TgSPHERE,CPC) psSP0 )
{
    VEC_T(1,C)                          vDist = FCN_VO(tgCO_BX_Dist_SP)( psBX0, psSP0 );

    return (FCN_V(tgMH_MUL)( vDist, vDist ));
}


/* ---- FCN_VO(tgCO_BX_Dist_SP) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_BX_Dist_SP)( VEC_OBJ_T(TgBOX,CPC) psBX0, VEC_OBJ_T(TgSPHERE,CPC) psSP0 )
{
    VEC_T(1,C)                          vDistSq = FCN_VO(tgCO_BX_DistSq_PT)( psBX0, psSP0->m_vOrigin );
    VEC_T(1,C)                          vDist = FCN_V(tgMH_SQRT)( vDistSq );
    VEC_T(1,C)                          vX0 = FCN_V(tgMH_SUB)( vDist, psSP0->m_vRadius );
    VEC_T(1,C)                          vRet = FCN_V(tgMH_MAX)( vX0, FCN_V(tgMH_SET1)( TYPE_K(0) ) );

    return (vRet);
}


/* ---- FCN_VO(tgCO_BX_ClosestSq_SP) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_BX_ClosestSq_SP)( VEC_T(1,PC) pvBX0, VEC_T(1,PC) pvSP0, VEC_OBJ_T(TgBOX,CPC) psBX0, VEC_OBJ_T(TgSPHERE,CPC) psSP0 )
{
    VEC_T(1,C)                          vDist = FCN_VO(tgCO_BX_Closest_SP)( pvBX0, pvSP0, psBX0, psSP0 );

    return (FCN_V(tgMH_MUL)( vDist, vDist ));
}


/* ---- FCN_VO(tgCO_BX_Closest_SP) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_BX_Closest_SP)( VEC_T(1,PC) pvBX0, VEC_T(1,PC) pvSP0, VEC_OBJ_T(TgBOX,CPC) psBX0, VEC_OBJ_T(TgSPHERE,CPC) psSP0 )
{
    VEC_T(1,C)                          vDistSq = FCN_VO(tgCO_BX_ClosestSq_PT)( pvBX0, psBX0, psSP0->m_vOrigin );
    VEC_T(1,C)                          vDist = FCN_V(tgMH_SQRT)( vDistSq );
    VEC_T(1,C)                          vX0 = FCN_V(tgMH_SUB)( vDist, psSP0->m_vRadius );
    VEC_T(1,C)                          vRet = FCN_V(tgMH_MAX)( vX0, FCN_V(tgMH_SET1)( TYPE_K(0) ) );

    VEC_T(1,C)                          vX1 = FCN_V(tgMH_SUB)( *pvBX0, psSP0->m_vOrigin );
    VEC_T(1,C)                          vX2 = FCN_V(tgMH_DIV)( psSP0->m_vRadius, vDist );

    *pvSP0 = FCN_V(tgMH_MAD)( vX1, vX2, psSP0->m_vOrigin );

    return (vRet);
}


/* ---- FCN_VO(tgCO_BX_ClosestSq_PM_SP) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_BX_ClosestSq_PM_SP)( VEC_T(1,PC) pvBX0, VEC_T(1,PC) pvBX1, VEC_T(1,PC) pvBX2, VEC_T(1,PC) pvSP0, VEC_OBJ_T(TgBOX,CPC) psBX0, VEC_OBJ_T(TgSPHERE,CPC) psSP0)
{
    VEC_T(1,C)                          vDist = FCN_VO(tgCO_BX_Closest_PM_SP)( pvBX0, pvBX1, pvBX2, pvSP0, psBX0, psSP0 );

    return (FCN_V(tgMH_MUL)( vDist, vDist ));
}


/* ---- FCN_VO(tgCO_BX_Closest_PM_SP) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_BX_Closest_PM_SP)( VEC_T(1,PC) pvBX0, VEC_T(1,PC) pvBX1, VEC_T(1,PC) pvBX2, VEC_T(1,PC) pvSP0, VEC_OBJ_T(TgBOX,CPC) psBX0, VEC_OBJ_T(TgSPHERE,CPC) psSP0)
{
    VEC_T(1,C)                          vDistSq = FCN_VO(tgCO_BX_ClosestSq_PM_PT)( pvBX0, pvBX1, pvBX2, psBX0, psSP0->m_vOrigin );
    VEC_T(1,C)                          vDist = FCN_V(tgMH_SQRT)( vDistSq );
    VEC_T(1,C)                          vX0 = FCN_V(tgMH_SUB)( vDist, psSP0->m_vRadius );
    VEC_T(1,C)                          vRet = FCN_V(tgMH_MAX)( vX0, FCN_V(tgMH_SET1)( TYPE_K(0) ) );

    VEC_T(1,C)                          vX1 = FCN_VO(tgGM_BX_Calc_Point)( psBX0, *pvBX0, *pvBX1, *pvBX2 );
    VEC_T(1,C)                          vX2 = FCN_V(tgMH_SUB)( vX1, psSP0->m_vOrigin );
    VEC_T(1,C)                          vX3 = FCN_V(tgMH_DIV)( psSP0->m_vRadius, vDist );

    *pvSP0 = FCN_V(tgMH_MAD)( vX2, vX3, psSP0->m_vOrigin );

    return (vRet);
}


/* ---- FCN_VO(tgCO_BX_Penetrate_SP) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_BX_Penetrate_SP)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_OBJ_T(TgBOX,CPC) psBX0, VEC_OBJ_T(TgSPHERE,CPC) psSP0 )
{
    VEC_OBJ_T(STg2_CO_Contact,P)        psContact;
    VEC_T(1)                            vK0;

    TgRSIZE_C                           nuiContact = psPacket->m_nuiContact;
    TgRESULT_C      iResult = FCN_VO(tgCO_SP_Penetrate_BX)( psPacket, psSP0, psBX0 );

    if (TgFAILED( iResult ))
    {
        return (iResult);
    };

    for (TgRSIZE uiIdx = nuiContact; uiIdx < psPacket->m_nuiContact; ++uiIdx)
    {
        psContact = psPacket->m_psContact + uiIdx;
        vK0 = FCN_V(tgMH_MUL)( psContact->m_vN0, psContact->m_vDepth );
        psContact->m_vS0 = FCN_V(tgMH_ADD)( psContact->m_vS0, vK0 );
        psContact->m_vN0 = FCN_V(tgMH_NEG)( psContact->m_vN0 );
    };

    return (iResult);
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

    #define TGS_COLLISION_BOX_SPHERE_INL

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COLLISION_BOX_SPHERE_INL) */
#endif
