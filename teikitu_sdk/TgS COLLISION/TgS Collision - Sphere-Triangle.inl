/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Sphere-Triangle.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.18 | »GUID« 5BB31923-DAF4-437F-8513-C1B5BEEA163A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_SPHERE_TRIANGLE_INL)
#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* == Collision ================================================================================================================================================================== */

/* ---- FCN_VO(tgCO_SP_DistSq_ET) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_SP_DistSq_ET)( VEC_OBJ_T(TgSPHERE,CPC) psSP0, VEC_OBJ_T(TgETRI,CPC) psET0 )
{
    VEC_T(1,C)                          vX0 = FCN_VO(tgCO_SP_Dist_ET)( psSP0, psET0 );

    return (FCN_V(tgMH_MUL)( vX0, vX0 ));
}


/* ---- FCN_VO(tgCO_SP_Dist_ET) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_SP_Dist_ET)( VEC_OBJ_T(TgSPHERE,CPC) psSP0, VEC_OBJ_T(TgETRI,CPC) psET0 )
{
    VEC_T(1,C)                          vX0 = FCN_VO(tgCO_ET_Dist_PT)( psET0, psSP0->m_vOrigin );
    VEC_T(1,C)                          vX1 = FCN_V(tgMH_SUB)( vX0, psSP0->m_vRadius );
    VEC_T(1,C)                          vX2 = FCN_V(tgMH_MAX)( vX1, FCN_V(tgMH_SET1)( TYPE_K(0) ) );

    return (vX2);
}


/* ---- FCN_VO(tgCO_SP_ClosestSq_ET) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_SP_ClosestSq_ET)( VEC_T(1,PC) pvSP0, VEC_T(1,PC) pvET0, VEC_OBJ_T(TgSPHERE,CPC) psSP0, VEC_OBJ_T(TgETRI,CPC) psET0 )
{
    VEC_T(1,C)                          vDist = FCN_VO(tgCO_SP_Closest_ET)( pvSP0, pvET0, psSP0, psET0 );

    return (FCN_V(tgMH_MUL)( vDist, vDist ));
}


/* ---- FCN_VO(tgCO_SP_Closest_ET) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_SP_Closest_ET)( VEC_T(1,PC) pvSP0, VEC_T(1,PC) pvET0, VEC_OBJ_T(TgSPHERE,CPC) psSP0, VEC_OBJ_T(TgETRI,CPC) psET0 )
{
    VEC_T(1,C)                          vDist_PT = FCN_VO(tgCO_ET_Closest_PT)( pvET0, psET0, psSP0->m_vOrigin );
    VEC_T(1,C)                          vRet = FCN_VO(tgCO_SP_Util__Closest_PT_Dist)( pvSP0, psSP0, vDist_PT, *pvET0 );

    return (vRet);
}


/* ---- FCN_VO(tgCO_SP_ClosestSq_PM_ET) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_SP_ClosestSq_PM_ET)( VEC_T(1,PC) pvSP0, VEC_T(1,PC) pvET0, VEC_T(1,PC) pvET1, VEC_OBJ_T(TgSPHERE,CPC) psSP0, VEC_OBJ_T(TgETRI,CPC) psET0 )
{
    VEC_T(1,C)                          vX0 = FCN_VO(tgCO_SP_Closest_PM_ET)( pvSP0, pvET0, pvET1, psSP0, psET0 );

    return (FCN_V(tgMH_MUL)( vX0, vX0 ));
}


/* ---- FCN_VO(tgCO_SP_Closest_PM_ET) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_SP_Closest_PM_ET)( VEC_T(1,PC) pvSP0, VEC_T(1,PC) pvET0, VEC_T(1,PC) pvET1, VEC_OBJ_T(TgSPHERE,CPC) psSP0, VEC_OBJ_T(TgETRI,CPC) psET0 )
{
    VEC_T(1,C)                          vDist_PT = FCN_VO(tgCO_ET_Closest_PM_PT)( pvET0, pvET1, psET0, psSP0->m_vOrigin );
    VEC_T(1,C)                          vET0 = FCN_VO(tgGM_ET_Calc_Point)( psET0, *pvET0, *pvET1 );
    VEC_T(1,C)                          vRet = FCN_VO(tgCO_SP_Util__Closest_PT_Dist)( pvSP0, psSP0, vDist_PT, vET0 );

    return (vRet);
}


/* ---- FCN_VO(tgCO_SP_Test_ET) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_VO(tgCO_SP_Test_ET)( VEC_OBJ_T(TgSPHERE,CPC) psSP0, VEC_OBJ_T(TgETRI,CPC) psET0 )
{
    VEC_T(1,C)                          vDist_PT = FCN_VO(tgCO_ET_Dist_PT)( psET0, psSP0->m_vOrigin );
    VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_LE)( vDist_PT, psSP0->m_vRadius  );

    return (FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_0 ));
}


/* ---- FCN_VO(tgCO_ST_Penetrate_SP) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_ST_Penetrate_SP)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_OBJ_T(TgSTRI,CPC) psST0, VEC_OBJ_T(TgSPHERE,CPC) psSP0 )
{
    VEC_OBJ_T(STg2_CO_Contact,P)        psContact;

    TgRSIZE_C                           nuiContact = psPacket->m_nuiContact;
    TgRESULT_C      iResult = FCN_VO(tgCO_SP_Penetrate_ST)( psPacket, psSP0, psST0 );

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

    #define TGS_COLLISION_SPHERE_TRIANGLE_INL

    #include "TgS COLLISION/TgS Collision - Sphere-Point.inl"
    #include "TgS COLLISION/TgS Collision - Triangle-Point.inl"

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COLLISION_SPHERE_TRIANGLE_INL) */
#endif
