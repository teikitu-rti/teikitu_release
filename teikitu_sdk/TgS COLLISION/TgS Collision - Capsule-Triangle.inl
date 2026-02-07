/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Capsule-Triangle.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.18 | »GUID« 5BB31923-DAF4-437F-8513-C1B5BEEA163A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_CAPSULE_TRIANGLE_INL)
#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* == Collision ================================================================================================================================================================== */

/* ---- FCN_VO(tgCO_CP_DistSq_ST) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_CP_DistSq_ST)( VEC_OBJ_T(TgTUBE,CPC) psCP0, VEC_OBJ_T(TgSTRI,CPC) psST0 )
{
    VEC_T(1,C)                          vX0 = FCN_VO(tgCO_CP_Dist_ST)( psCP0, psST0 );

    return (FCN_V(tgMH_MUL)( vX0, vX0 ));
}


/* ---- FCN_VO(tgCO_CP_Dist_ST) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_CP_Dist_ST)( VEC_OBJ_T(TgTUBE,CPC) psCP0, VEC_OBJ_T(TgSTRI,CPC) psST0 )
{
    VEC_T(1,C)                          vX0 = FCN_VO(tgCO_ST_Dist_SG)( psST0, &psCP0->m_sAX );
    VEC_T(1,C)                          vX1 = FCN_V(tgMH_SUB)( vX0, psCP0->m_vRadius );
    VEC_T(1,C)                          vRet = FCN_V(tgMH_MAX)( vX1, FCN_V(tgMH_SET1)( TYPE_K(0) ) );

    return (vRet);
}


/* ---- FCN_VO(tgCO_CP_ClosestSq_ST) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_CP_ClosestSq_ST)( VEC_T(1,PC) pvCP0, VEC_T(1,PC) pvST0, VEC_OBJ_T(TgTUBE,CPC) psCP0, VEC_OBJ_T(TgSTRI,CPC) psST0 )
{
    VEC_T(1,C)                          vX0 = FCN_VO(tgCO_CP_Closest_ST)( pvCP0, pvST0, psCP0, psST0 );

    return (FCN_V(tgMH_MUL)( vX0, vX0 ));
}


/* ---- FCN_VO(tgCO_CP_Closest_ST) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_CP_Closest_ST)( VEC_T(1,PC) pvCP0, VEC_T(1,PC) pvET0, VEC_OBJ_T(TgTUBE,CPC) psCP0, VEC_OBJ_T(TgSTRI,CPC) psST0 )
{
    VEC_T(1)                            vSG0;

    VEC_T(1,C)                          vDist_PT = FCN_VO(tgCO_ST_Closest_SG)( pvET0, &vSG0, psST0, &psCP0->m_sAX );
    VEC_T(1,C)                          vRet = FCN_VO(tgCO_CP_Internal_Dist_SG_PT)( pvCP0, vDist_PT, psCP0->m_vRadius, vSG0, *pvET0 );

    return (vRet);
}


/* ---- FCN_VO(tgCO_CP_ClosestSq_PM_ST) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_CP_ClosestSq_PM_ST)( VEC_T(1,PC) pvCP0, VEC_T(1,PC) pvST_T0, VEC_T(1,PC) pvST_T1, VEC_OBJ_T(TgTUBE,CPC) psCP0, VEC_OBJ_T(TgSTRI,CPC) psST0 )
{
    VEC_T(1,C)                          vX0 = FCN_VO(tgCO_CP_Closest_PM_ST)( pvCP0, pvST_T0, pvST_T1, psCP0, psST0 );

    return (FCN_V(tgMH_MUL)( vX0, vX0 ));
}


/* ---- FCN_VO(tgCO_CP_Closest_PM_ST) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_CP_Closest_PM_ST)( VEC_T(1,PC) pvCP0, VEC_T(1,PC) pvST_T0, VEC_T(1,PC) pvST_T1, VEC_OBJ_T(TgTUBE,CPC) psCP0, VEC_OBJ_T(TgSTRI,CPC) psST0 )
{
    VEC_T(1)                            vSG_T0;

    VEC_T(1,C)                          vDist_PT = FCN_VO(tgCO_ST_ClosestSq_PM_SG)( pvST_T0, pvST_T1, &vSG_T0, psST0, &psCP0->m_sAX );
    VEC_T(1,C)                          vSG0 = FCN_V(tgMH_MAD)( vSG_T0, psCP0->m_sAX.m_vDirN, psCP0->m_sAX.m_vOrigin );
    VEC_T(1,C)                          vST0 = FCN_VO(tgGM_ST_Calc_Point)( psST0, *pvST_T0, *pvST_T1 );
    VEC_T(1,C)                          vRet = FCN_VO(tgCO_CP_Internal_Dist_SG_PT)( pvCP0, vDist_PT, psCP0->m_vRadius, vSG0, vST0 );

    return (vRet);
}


/* ---- FCN_VO(tgCO_CP_Test_ST) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_VO(tgCO_CP_Test_ST)( VEC_OBJ_T(TgTUBE,CPC) psCP0, VEC_OBJ_T(TgSTRI,CPC) psST0 )
{
    VEC_T(1,C)                          vDist_PT = FCN_VO(tgCO_ST_Dist_SG)( psST0, &psCP0->m_sAX );
    VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_LE)( vDist_PT, psCP0->m_vRadius  );

    return (FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_0 ));
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

    #define TGS_COLLISION_CAPSULE_TRIANGLE_INL

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COLLISION_CAPSULE_TRIANGLE_INL) */
#endif
