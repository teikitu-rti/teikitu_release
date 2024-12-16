/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Sphere-Sphere.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.18 | »GUID« 5BB31923-DAF4-437F-8513-C1B5BEEA163A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_SPHERE_SPHERE_INL)
#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* == Collision ================================================================================================================================================================== */

/* ---- FCN_VO(tgCO_SP_DistSq_SP) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_SP_DistSq_SP)( VEC_OBJ_T(TgSPHERE,CPC) psSP0, VEC_OBJ_T(TgSPHERE,CPC) psSP1 )
{
    VEC_T(1,C)                          vX0 = FCN_VO(tgCO_SP_Dist_SP)( psSP0, psSP1 );

    return (FCN_V(tgMH_MUL)( vX0, vX0 ));
}


/* ---- FCN_VO(tgCO_SP_Dist_SP) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_SP_Dist_SP)( VEC_OBJ_T(TgSPHERE,CPC) psSP0, VEC_OBJ_T(TgSPHERE,CPC) psSP1 )
{
    VEC_T(1,C)                          vDist_PT = FCN_V(tgMH_SUB)( psSP1->m_vOrigin, psSP0->m_vOrigin );
    VEC_T(1,C)                          vSum_Rad = FCN_V(tgMH_ADD)( psSP1->m_vRadius, psSP0->m_vRadius );
    VEC_T(1,C)                          vX0 = FCN_V(tgMH_LEN)( vDist_PT );
    VEC_T(1,C)                          vX1 = FCN_V(tgMH_SUB)( vX0, vSum_Rad );
    VEC_T(1,C)                          vX2 = FCN_V(tgMH_MAX)( vX1, FCN_V(tgMH_SET1)( TYPE_K(0) ) );

    return (vX2);
}


/* ---- FCN_VO(tgCO_SP_ClosestSq_SP) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_SP_ClosestSq_SP)( VEC_T(1,PC) pvSP0, VEC_T(1,PC) pvSP1, VEC_OBJ_T(TgSPHERE,CPC) psSP0, VEC_OBJ_T(TgSPHERE,CPC) psSP1 )
{
    VEC_T(1,C)                          vDist = FCN_VO(tgCO_SP_Closest_SP)( pvSP0, pvSP1, psSP0, psSP1 );

    return (FCN_V(tgMH_MUL)( vDist, vDist ));
}


/* ---- FCN_VO(tgCO_SP_Closest_SP) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_SP_Closest_SP)( VEC_T(1,PC) pvSP0, VEC_T(1,PC) pvSP1, VEC_OBJ_T(TgSPHERE,CPC) psSP0, VEC_OBJ_T(TgSPHERE,CPC) psSP1 )
{
    VEC_T(1)                            vMag_DS;

    VEC_T(1,C)                          vDS = FCN_V(tgMH_SUB)( psSP1->m_vOrigin, psSP0->m_vOrigin );
    VEC_T(1,C)                          vSum_Rad = FCN_V(tgMH_ADD)( psSP1->m_vRadius, psSP0->m_vRadius );
    VEC_T(1,C)                          vDN = FCN_V(tgMH_NORM_LEN)( &vMag_DS, vDS );
    VEC_T(1,C)                          vX1 = FCN_V(tgMH_SUB)( vMag_DS, vSum_Rad );
    VEC_T(1,C)                          vX2 = FCN_V(tgMH_MAX)( vX1, FCN_V(tgMH_SET1)( TYPE_K(0) ) );

    *pvSP0 = FCN_V(tgMH_MAD)( psSP0->m_vRadius, vDN, psSP0->m_vOrigin );
    *pvSP1 = FCN_V(tgMH_SUB)( psSP1->m_vOrigin, FCN_V(tgMH_MUL)( psSP1->m_vRadius, vDN ) );

    return (vX2);
}


/* ---- FCN_VO(tgCO_SP_Test_SP) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_VO(tgCO_SP_Test_SP)( VEC_OBJ_T(TgSPHERE,CPC) psSP0, VEC_OBJ_T(TgSPHERE,CPC) psSP1 )
{
    VEC_T(1,C)                          vDist_PT = FCN_V(tgMH_SUB)( psSP1->m_vOrigin, psSP0->m_vOrigin );
    VEC_T(1,C)                          vX0 = FCN_V(tgMH_LEN)( vDist_PT );
    VEC_T(1,C)                          vSum_Rad = FCN_V(tgMH_ADD)( psSP1->m_vRadius, psSP0->m_vRadius );
    VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_LE)( vX0, vSum_Rad );

    TgPARAM_CHECK( FCN_VO(tgGM_SP_Is_Valid)( psSP0 ) && FCN_VO(tgGM_SP_Is_Valid)( psSP1 ) );

    return (FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_0 ));
}


/* ---- FCN_VO(tgCO_SP_Test_Sweep_SP) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_VO(tgCO_SP_Test_Sweep_SP)( VEC_OBJ_T(TgSPHERE,CPC) psSP0, VEC_OBJ_T(TgSPHERE,CPC) psSP1, VEC_OBJ_T(TgDELTA,CPC) psDT )
{
    VEC_OBJ_T(TgSEGMENT)                sSG;

    sSG.m_vOrigin = psSP1->m_vOrigin;
    sSG.m_vDirN = psDT->m_vDT;

    VEC_T(1,C)                          vX0 = FCN_VO(tgCO_SG_DistSq_PT)( &sSG, psSP0->m_vOrigin );
    VEC_T(1,C)                          vSR = FCN_V(tgMH_ADD)( psSP1->m_vRadius, psSP0->m_vRadius );
    VEC_T(1,C)                          vSR_SR = FCN_V(tgMH_MUL)( vSR, vSR );

    return (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vX0, vSR_SR ) ));
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

    #define TGS_COLLISION_SPHERE_SPHERE_INL

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COLLISION_SPHERE_SPHERE_INL) */
#endif
