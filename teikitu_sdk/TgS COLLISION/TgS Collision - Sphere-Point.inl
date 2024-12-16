/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Sphere-Point.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.18 | »GUID« 5BB31923-DAF4-437F-8513-C1B5BEEA163A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_SPHERE_POINT_INL)
#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* == Collision ================================================================================================================================================================== */

/* ---- FCN_VO(tgCO_SP_DistSq_PT) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_SP_DistSq_PT)( VEC_OBJ_T(TgSPHERE,CPC) psSP0, VEC_T(1,C) vS0 )
{
    VEC_T(1,C)                          vDist = FCN_VO(tgCO_SP_Dist_PT)( psSP0, vS0 );

    return (FCN_V(tgMH_MUL)( vDist, vDist ));
}


/* ---- FCN_VO(tgCO_SP_Dist_PT) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_SP_Dist_PT)( VEC_OBJ_T(TgSPHERE,CPC) psSP0, VEC_T(1,C) vS0 )
{
    VEC_T(1,C)                          vDS = FCN_V(tgMH_SUB)( vS0, psSP0->m_vOrigin );
    VEC_T(1,C)                          vMag_DS = FCN_V(tgMH_LEN)( vDS );
    VEC_T(1,C)                          vX0 = FCN_V(tgMH_SUB)( vMag_DS, psSP0->m_vRadius );
    VEC_T(1,C)                          vRet = FCN_V(tgMH_MAX)( vX0, FCN_V(tgMH_SET1)( TYPE_K(0) ) );

    return (vRet);
}


/* ---- FCN_VO(tgCO_SP_ClosestSq_PT) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_SP_ClosestSq_PT)( VEC_T(1,PC) pvSP0, VEC_OBJ_T(TgSPHERE,CPC) psSP0, VEC_T(1,C) vS0 )
{
    VEC_T(1,C)                          vDist = FCN_VO(tgCO_SP_Closest_PT)( pvSP0, psSP0, vS0 );

    return (FCN_V(tgMH_MUL)( vDist, vDist ));
}


/* ---- FCN_VO(tgCO_SP_Closest_PT) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_SP_Closest_PT)( VEC_T(1,PC) pvSP0, VEC_OBJ_T(TgSPHERE,CPC) psSP0, VEC_T(1,C) vS0 )
{
    VEC_T(1)                            vMag_DS;

    VEC_T(1,C)                          vDS = FCN_V(tgMH_SUB)( vS0, psSP0->m_vOrigin );
    VEC_T(1,C)                          vD0 = FCN_V(tgMH_NORM_LEN)( &vMag_DS, vDS );
    VEC_T(1,C)                          vX0 = FCN_V(tgMH_SUB)( vMag_DS, psSP0->m_vRadius );
    VEC_T(1,C)                          vRet = FCN_V(tgMH_MAX)( vX0, FCN_V(tgMH_SET1)( TYPE_K(0) ) );

    *pvSP0 = FCN_V(tgMH_MAD)( vD0, psSP0->m_vRadius, psSP0->m_vOrigin );
    return (vRet);
}


/* ---- FCN_VO(tgCO_SP_Test_PT) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_VO(tgCO_SP_Test_PT)( VEC_OBJ_T(TgSPHERE,CPC) psSP0, VEC_T(1,C) vS0 )
{
    VEC_T(1,C)                          vX0 = FCN_V(tgMH_SUB)( vS0, psSP0->m_vOrigin );
    VEC_T(1,C)                          vX1 = FCN_V(tgMH_LSQ)( vX0 );
    VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_LE)( vX1, psSP0->m_vRadiusSq );

    return (FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_0 ));
}


/* ---- FCN_VO(tgCO_SP_Util__ClosestSq_PT_Dist) ---------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_SP_Util__ClosestSq_PT_Dist)( VEC_T(1,PC) pvSP0, VEC_OBJ_T(TgSPHERE,CPC) psSP0, VEC_T(1,C) vDist_PT, VEC_T(1,C) vPT0 )
{
    VEC_T(1,C)                          vDist = FCN_VO(tgCO_SP_Util__Closest_PT_Dist)( pvSP0, psSP0, vDist_PT, vPT0 );
    VEC_T(1,C)                          vRet = FCN_V(tgMH_MUL)( vDist, vDist );

    return (vRet);
}


/* ---- FCN_VO(tgCO_SP_Util__Closest_PT_Dist) ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_SP_Util__Closest_PT_Dist)( VEC_T(1,PC) pvSP0, VEC_OBJ_T(TgSPHERE,CPC) psSP0, VEC_T(1,C) vDist_PT, VEC_T(1,C) vPT0 )
{
    VEC_T(1,C)                          vDS = FCN_V(tgMH_SUB)( vPT0, psSP0->m_vOrigin );
    VEC_T(1,C)                          vX0 = FCN_V(tgMH_DIV)( psSP0->m_vRadius, vDist_PT );
    VEC_T(1,C)                          vDist = FCN_V(tgMH_SUB)( vDist_PT, psSP0->m_vRadius );
    VEC_T(1,C)                          vRet = FCN_V(tgMH_MAX)( vDist, FCN_V(tgMH_SET1)( TYPE_K(0) ) );

    VEC_T(1,C)                          vOUT = FCN_V(tgMH_MAD)( vX0, vDS, psSP0->m_vOrigin );

    *pvSP0 = vOUT;
    return (vRet);
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

    #define TGS_COLLISION_SPHERE_POINT_INL

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COLLISION_SPHERE_POINT_INL) */
#endif
