/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Sphere-Ray.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.18 | »GUID« 5BB31923-DAF4-437F-8513-C1B5BEEA163A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_SPHERE_RAY_INL)
#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* == Collision ================================================================================================================================================================== */

/* ---- FCN_VO(tgCO_SP_DistSq_RY) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_SP_DistSq_RY)( VEC_OBJ_T(TgSPHERE,CPC) psSP0, VEC_OBJ_T(TgRAY,CPC) psRY0 )
{
    VEC_T(1,C)                          vX0 = FCN_VO(tgCO_SP_Dist_RY)( psSP0, psRY0 );

    return (FCN_V(tgMH_MUL)( vX0, vX0 ));
}


/* ---- FCN_VO(tgCO_SP_Dist_RY) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_SP_Dist_RY)( VEC_OBJ_T(TgSPHERE,CPC) psSP0, VEC_OBJ_T(TgRAY,CPC) psRY0 )
{
    VEC_T(1,C)                          vX0 = FCN_VO(tgCO_RY_Dist_PT)( psRY0, psSP0->m_vOrigin );
    VEC_T(1,C)                          vX1 = FCN_V(tgMH_SUB)( vX0, psSP0->m_vRadius );
    VEC_T(1,C)                          vX2 = FCN_V(tgMH_MAX)( vX1, FCN_V(tgMH_SET1)( TYPE_K(0) ) );

    return (vX2);
}


/* ---- FCN_VO(tgCO_SP_ClosestSq_RY) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_SP_ClosestSq_RY)( VEC_T(1,PC) pvSP0, VEC_T(1,PC) pvRY0, VEC_OBJ_T(TgSPHERE,CPC) psSP0, VEC_OBJ_T(TgRAY,CPC) psRY0 )
{
    VEC_T(1,C)                          vX0 = FCN_VO(tgCO_SP_Closest_RY)( pvSP0, pvRY0, psSP0, psRY0 );

    return (FCN_V(tgMH_MUL)( vX0, vX0 ));
}


/* ---- FCN_VO(tgCO_SP_Closest_RY) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_SP_Closest_RY)( VEC_T(1,PC) pvSP0, VEC_T(1,PC) pvRY0, VEC_OBJ_T(TgSPHERE,CPC) psSP0, VEC_OBJ_T(TgRAY,CPC) psRY0 )
{
    VEC_T(1,C)                          vDist_PT = FCN_VO(tgCO_RY_Closest_PT)( pvRY0, psRY0, psSP0->m_vOrigin );
    VEC_T(1,C)                          vRet = FCN_VO(tgCO_SP_Util__Closest_PT_Dist)( pvSP0, psSP0, vDist_PT, *pvRY0 );

    return (vRet);
}


/* ---- FCN_VO(tgCO_SP_ClosestSq_PM_RY) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_SP_ClosestSq_PM_RY)( VEC_T(1,PC) pvSP0, VEC_T(1,PC) pvT1, VEC_OBJ_T(TgSPHERE,CPC) psSP0, VEC_OBJ_T(TgRAY,CPC) psRY0 )
{
    VEC_T(1,C)                          vX0 = FCN_VO(tgCO_SP_Closest_PM_RY)( pvSP0, pvT1, psSP0, psRY0 );

    return (FCN_V(tgMH_MUL)( vX0, vX0 ));
}


/* ---- FCN_VO(tgCO_SP_Closest_PM_RY) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_SP_Closest_PM_RY)(VEC_T(1,PC) pvSP0, VEC_T(1,PC) pvT1, VEC_OBJ_T(TgSPHERE,CPC) psSP0, VEC_OBJ_T(TgRAY,CPC) psRY0 )
{
    VEC_T(1,C)                          vDist_PT = FCN_VO(tgCO_RY_Closest_PM_PT)( pvT1, psRY0, psSP0->m_vOrigin );
    VEC_T(1,C)                          vRY0 = FCN_V(tgMH_MAD)( *pvT1, psRY0->m_vDirN, psRY0->m_vOrigin );
    VEC_T(1,C)                          vRet = FCN_VO(tgCO_SP_Util__Closest_PT_Dist)( pvSP0, psSP0, vDist_PT, vRY0 );

    return (vRet);
}


/* ---- FCN_VO(tgCO_SP_Test_RY) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_VO(tgCO_SP_Test_RY)( VEC_OBJ_T(TgSPHERE,CPC) psSP0, VEC_OBJ_T(TgRAY,CPC) psRY0 )
{
    VEC_T(1,C)                          vDist_PT = FCN_VO(tgCO_RY_DistSq_PT)( psRY0, psSP0->m_vOrigin );
    VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_LE)( vDist_PT, psSP0->m_vRadiusSq  );

    return (FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_0 ));
}


/* ---- FCN_VO(tgCO_SP_Intersect_RY) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_SP_Intersect_RY)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_OBJ_T(TgSPHERE,CPC) psSP0, VEC_OBJ_T(TgRAY,CPC) psRY0 )
{
    return (FCN_VO(tgCO_SP_Intersect_LR10)( psPacket, psSP0, psRY0->m_vOrigin, psRY0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_SP_Penetrate_RY) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_SP_Penetrate_RY)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_OBJ_T(TgSPHERE,CPC) psSP0, VEC_OBJ_T(TgRAY,CPC) psRY0 )
{
    VEC_T(1)                            vRY0;

    TgPARAM_CHECK(FCN_VO(tgGM_SP_Is_Valid)( psSP0 ) && FCN_VO(tgGM_RY_Is_Valid)( psRY0 ));

    if (0 == psPacket->m_nuiMaxContact || psPacket->m_nuiContact >= psPacket->m_nuiMaxContact || nullptr == psPacket->m_psContact)
    {
        return (KTgE_FAIL);
    };

    VEC_T(1,C)                          vDistSq_PT = FCN_VO(tgCO_RY_ClosestSq_PT)( &vRY0, psRY0, psSP0->m_vOrigin );
    VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_GT)( vDistSq_PT, psSP0->m_vRadiusSq  );

    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_0 ))
    {
        return (KTgE_NO_INTERSECT);
    };

    return (FCN_VO(tgCO_SP_Util__Penetrate_Closest_PT_Dist)( psPacket, psSP0, vRY0, vDistSq_PT, psRY0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_SP_Sweep_RY) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_SP_Sweep_RY)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_T(1,PC) pvPM, TgRSIZE_P puiStart, VEC_OBJ_T(TgSPHERE,CPC) psSP0, VEC_OBJ_T(TgRAY,CPC) psRY0,
                                            VEC_OBJ_T(TgDELTA,CPC) psDT )
{
    return (FCN_VO(tgCO_SP_Sweep_LR10)( psPacket, pvPM, puiStart, psSP0, psRY0->m_vOrigin, psRY0->m_vDirN, psDT ));
}


/* ---- FCN_VO(tgCO_SP_Clip_PM_RY) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_SP_Clip_PM_RY)( VEC_T(1,PC) pvRY0, VEC_T(1,PC) pvRY1, VEC_OBJ_T(TgSPHERE,CPC) psSP0, VEC_OBJ_T(TgRAY,CPC) psRY0 )
{
    return (FCN_VO(tgCO_SP_Clip_PM_LR10)( pvRY0, pvRY1, psSP0, psRY0->m_vOrigin, psRY0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_SP_Clip_RY) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_SP_Clip_RY)( VEC_OBJ_T(STg2_CO_Clip_List,PC) psCL, VEC_OBJ_T(TgSPHERE,CPC) psSP0, VEC_OBJ_T(TgRAY,CPC) psRY0 )
{
    return (FCN_VO(tgCO_SP_Clip_LR10)( psCL, psSP0, psRY0->m_vOrigin, psRY0->m_vDirN ));
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

    #define TGS_COLLISION_SPHERE_RAY_INL

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COLLISION_SPHERE_RAY_INL) */
#endif
