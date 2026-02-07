/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Box AA-Sphere.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.18 | »GUID« 5BB31923-DAF4-437F-8513-C1B5BEEA163A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_BOX_AA_SPHERE_INL)
#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* == Collision ================================================================================================================================================================== */

/* ---- FCN_VO(tgCO_BA_DistSq_SP) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_BA_DistSq_SP)( VEC_OBJ_T(TgBOXAA,CPC) psBA0, VEC_OBJ_T(TgSPHERE,CPC) psSP0 )
{
    VEC_T(1,C)                          vDist = FCN_VO(tgCO_BA_Dist_SP)( psBA0, psSP0 );
    VEC_T(1,C)                          vRet = FCN_V(tgMH_MUL)( vDist, vDist );

    return (vRet);
}


/* ---- FCN_VO(tgCO_BA_Dist_SP) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_BA_Dist_SP)( VEC_OBJ_T(TgBOXAA,CPC) psBA0, VEC_OBJ_T(TgSPHERE,CPC) psSP0 )
{
    VEC_T(1,C)                          vDist = FCN_VO(tgCO_BA_Dist_PT)( psBA0, psSP0->m_vOrigin );
    VEC_T(1,C)                          vX0 = FCN_V(tgMH_SUB)( vDist, psSP0->m_vRadius );
    VEC_T(1,C)                          vRet = FCN_V(tgMH_MAX)( vX0, FCN_V(tgMH_SET1)( TYPE_K(0) ) );

    return (vRet);
}


/* ---- FCN_VO(tgCO_BA_ClosestSq_SP) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_BA_ClosestSq_SP)( VEC_T(1,PC) pvBA0, VEC_T(1,PC) pvSP0, VEC_OBJ_T(TgBOXAA,CPC) psBA0, VEC_OBJ_T(TgSPHERE,CPC) psSP0 )
{
    VEC_T(1,C)                          vDist = FCN_VO(tgCO_BA_Closest_SP)( pvBA0, pvSP0, psBA0, psSP0 );
    VEC_T(1,C)                          vRet = FCN_V(tgMH_MUL)( vDist, vDist );

    return (vRet);
}


/* ---- FCN_VO(tgCO_BA_Closest_SP) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_BA_Closest_SP)( VEC_T(1,PC) pvBA0, VEC_T(1,PC) pvSP0, VEC_OBJ_T(TgBOXAA,CPC) psBA0, VEC_OBJ_T(TgSPHERE,CPC) psSP0 )
{
    VEC_T(1,C)                          vDist = FCN_VO(tgCO_BA_Closest_PT)( pvBA0, psBA0, psSP0->m_vOrigin );
    VEC_T(1,C)                          vX0 = FCN_V(tgMH_SUB)( vDist, psSP0->m_vRadius );
    VEC_T(1,C)                          vRet = FCN_V(tgMH_MAX)( vX0, FCN_V(tgMH_SET1)( TYPE_K(0) ) );

    VEC_T(1,C)                          vX1 = FCN_V(tgMH_SUB)( *pvBA0, psSP0->m_vOrigin );
    VEC_T(1,C)                          vX2 = FCN_V(tgMH_DIV)( psSP0->m_vRadius, vDist );
    VEC_T(1,C)                          vX3 = FCN_V(tgMH_MAD)( vX1, vX2, psSP0->m_vOrigin );

    *pvSP0 = vX3;
    return (vRet);
}


/* ---- FCN_VO(tgCO_BA_Test_SP) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_VO(tgCO_BA_Test_SP)( VEC_OBJ_T(TgBOXAA,CPC) psBA0, VEC_OBJ_T(TgSPHERE,CPC) psSP0 )
{
    VEC_T(1,C)                          vBA0_Min = FCN_VO(tgGM_BA_Query_Min)( psBA0 );
    VEC_T(1,C)                          vBA0_Max = FCN_VO(tgGM_BA_Query_Max)( psBA0 );

    VEC_T(1,C)                          vP1 = FCN_V(tgMH_CLP)( psSP0->m_vOrigin, vBA0_Min, vBA0_Max );
    VEC_T(1,C)                          vX0 = FCN_V(tgMH_SUB)( vP1, psSP0->m_vOrigin );
    VEC_T(1,C)                          vDistSq = FCN_V(tgMH_LSQ)( vX0 );

    return (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( vDistSq, psSP0->m_vRadiusSq )));
}


/* ---- FCN_VO(tgCO_SP_Penetrate_BA) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_SP_Penetrate_BA)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_OBJ_T(TgSPHERE,CPC) psSP0, VEC_OBJ_T(TgBOXAA,CPC) psBA0 )
{
    VEC_OBJ_T(STg2_CO_Contact,P)        psContact;

    TgRSIZE_C                           nuiContact = psPacket->m_nuiContact;
    TgRESULT_C      iResult = FCN_VO(tgCO_BA_Penetrate_SP)( psPacket, psBA0, psSP0 );

    if (TgFAILED( iResult ))
    {
        return (iResult);
    };

    for (TgRSIZE uiIdx = nuiContact; uiIdx < psPacket->m_nuiContact; ++uiIdx)
    {
        psContact = psPacket->m_psContact + uiIdx;

        psContact->m_vS0 = FCN_V(tgMH_MAD)( psContact->m_vN0, psContact->m_vDepth, psContact->m_vS0 );
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

    #define TGS_COLLISION_BOX_AA_SPHERE_INL

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COLLISION_BOXAA_SPHERE_INL) */
#endif
