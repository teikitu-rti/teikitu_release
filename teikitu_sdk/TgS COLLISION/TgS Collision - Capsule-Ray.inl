/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Capsule-Ray.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.18 | »GUID« 5BB31923-DAF4-437F-8513-C1B5BEEA163A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_CAPSULE_RAY_INL)
#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* == Collision ================================================================================================================================================================== */

/* ---- FCN_VO(tgCO_CP_DistSq_RY) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_CP_DistSq_RY)( VEC_OBJ_T(TgTUBE,CPC) psCP0, VEC_OBJ_T(TgRAY,CPC) psRY0 )
{
    VEC_T(1,C)                          vX0 = FCN_VO(tgCO_CP_Dist_RY)( psCP0, psRY0 );

    return (FCN_V(tgMH_MUL)( vX0, vX0 ));
}


/* ---- FCN_VO(tgCO_CP_Dist_RY) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_CP_Dist_RY)( VEC_OBJ_T(TgTUBE,CPC) psCP0, VEC_OBJ_T(TgRAY,CPC) psRY0 )
{
    VEC_T(1,C)                          vX0 = FCN_VO(tgCO_SG_Dist_RY)( &psCP0->m_sAX, psRY0 );
    VEC_T(1,C)                          vX1 = FCN_V(tgMH_SUB)( vX0, psCP0->m_vRadius );
    VEC_T(1,C)                          vRet = FCN_V(tgMH_MAX)( vX1, FCN_V(tgMH_SET1)( TYPE_K(0) ) );

    return (vRet);
}


/* ---- FCN_VO(tgCO_CP_ClosestSq_RY) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_CP_ClosestSq_RY)( VEC_T(1,PC) pvCP0, VEC_T(1,PC) pvRY0, VEC_OBJ_T(TgTUBE,CPC) psCP0, VEC_OBJ_T(TgRAY,CPC) psRY0 )
{
    VEC_T(1,C)                          vX0 = FCN_VO(tgCO_CP_Closest_RY)( pvCP0, pvRY0, psCP0, psRY0 );

    return (FCN_V(tgMH_MUL)( vX0, vX0 ));
}


/* ---- FCN_VO(tgCO_CP_Closest_RY) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_CP_Closest_RY)( VEC_T(1,PC) pvCP0, VEC_T(1,PC) pvRY0, VEC_OBJ_T(TgTUBE,CPC) psCP0, VEC_OBJ_T(TgRAY,CPC) psRY0 )
{
    VEC_T(1)                            vSG0;

    VEC_T(1,C)                          vDist_PT = FCN_VO(tgCO_SG_Closest_RY)( &vSG0, pvRY0, &psCP0->m_sAX, psRY0 );
    VEC_T(1,C)                          vRet = FCN_VO(tgCO_CP_Internal_Dist_SG_PT)( pvCP0, vDist_PT, psCP0->m_vRadius, vSG0, *pvRY0 );

    return (vRet);
}


/* ---- FCN_VO(tgCO_CP_ClosestSq_PM_RY) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_CP_ClosestSq_PM_RY)( VEC_T(1,PC) pvCP0, VEC_T(1,PC) pvRY_T0, VEC_OBJ_T(TgTUBE,CPC) psCP0, VEC_OBJ_T(TgRAY,CPC) psRY0 )
{
    VEC_T(1,C)                          vX0 = FCN_VO(tgCO_CP_Closest_PM_RY)( pvCP0, pvRY_T0, psCP0, psRY0 );

    return (FCN_V(tgMH_MUL)( vX0, vX0 ));
}


/* ---- FCN_VO(tgCO_CP_Closest_PM_RY) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_CP_Closest_PM_RY)( VEC_T(1,PC) pvCP0, VEC_T(1,PC) pvRY_T0, VEC_OBJ_T(TgTUBE,CPC) psCP0, VEC_OBJ_T(TgRAY,CPC) psRY0 )
{
    VEC_T(1)                            vSG_T0;

    VEC_T(1,C)                          vDist_PT = FCN_VO(tgCO_SG_Closest_PM_RY)( &vSG_T0, pvRY_T0, &psCP0->m_sAX, psRY0 );
    VEC_T(1,C)                          vSG0 = FCN_V(tgMH_MAD)( vSG_T0, psCP0->m_sAX.m_vDirN, psCP0->m_sAX.m_vOrigin );
    VEC_T(1,C)                          vRY0 = FCN_V(tgMH_MAD)( *pvRY_T0, psRY0->m_vDirN, psRY0->m_vOrigin );
    VEC_T(1,C)                          vRet = FCN_VO(tgCO_CP_Internal_Dist_SG_PT)( pvCP0, vDist_PT, psCP0->m_vRadius, vSG0, vRY0 );

    return (vRet);
}


/* ---- FCN_VO(tgCO_CP_Test_RY) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_VO(tgCO_CP_Test_RY)( VEC_OBJ_T(TgTUBE,CPC) psCP0, VEC_OBJ_T(TgRAY,CPC) psRY0 )
{
    VEC_T(1,C)                          vDist_PT = FCN_VO(tgCO_SG_Dist_RY)( &psCP0->m_sAX, psRY0 );
    VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_LE)( vDist_PT, psCP0->m_vRadius  );

    return (FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_0 ));
}


/* ---- FCN_VO(tgCO_CP_Intersect_RY) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_CP_Intersect_RY)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_OBJ_T(TgTUBE,CPC) psCP0, VEC_OBJ_T(TgRAY,CPC) psRY0 )
{
    return (FCN_VO(tgCO_CP_Intersect_LR10)( psPacket, psCP0, psRY0->m_vOrigin, psRY0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_RY_Penetrate_CP) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_RY_Penetrate_CP)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_OBJ_T(TgRAY,CPC) psRY0, VEC_OBJ_T(TgTUBE,CPC) psCP0 )
{
    VEC_T(1)                            vSG0, vRY0, vDistSq_PT, vCMP_0;

    TgPARAM_CHECK( FCN_VO(tgGM_TB_Is_Valid)( psCP0 ) && FCN_VO(tgGM_RY_Is_Valid)( psRY0 ) );

    if (0 == psPacket->m_nuiMaxContact || psPacket->m_nuiContact >= psPacket->m_nuiMaxContact || nullptr == psPacket->m_psContact)
    {
        return (KTgE_FAIL);
    };

    vDistSq_PT = FCN_VO(tgCO_SG_ClosestSq_RY)( &vSG0, &vRY0, &psCP0->m_sAX, psRY0 );
    vCMP_0 = FCN_V(tgMH_CMP_GT)( vDistSq_PT, psCP0->m_vRadiusSq  );

    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_0 ))
    {
        return (KTgE_NO_INTERSECT);
    };

    return (FCN_VO(tgCO_CP_Penetrate_LR10)( psPacket, vRY0, psCP0, vSG0, vDistSq_PT ));
}


/* ---- FCN_VO(tgCO_CP_Clip_PM_RY) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_CP_Clip_PM_RY)( VEC_T(1,PC) pvRY0, VEC_T(1,PC) pvRY1, VEC_OBJ_T(TgTUBE,CPC) psCP0, VEC_OBJ_T(TgRAY,CPC) psRY0 )
{
    return (FCN_VO(tgCO_CP_Clip_PM_LR10)( pvRY0, pvRY1, psCP0, psRY0->m_vOrigin, psRY0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_CP_Clip_RY) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_CP_Clip_RY)( VEC_OBJ_T(STg2_CO_Clip_List,PC) psCL, VEC_OBJ_T(TgTUBE,CPC) psCP0, VEC_OBJ_T(TgRAY,CPC) psRY0 )
{
    return (FCN_VO(tgCO_CP_Clip_LR10)( psCL, psCP0, psRY0->m_vOrigin, psRY0->m_vDirN ));
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

    #define TGS_COLLISION_CAPSULE_RAY_INL

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COLLISION_CAPSULE_RAY_INL) */
#endif
