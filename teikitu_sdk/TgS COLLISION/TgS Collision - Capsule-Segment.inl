/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Capsule-Segment.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.18 | »GUID« 5BB31923-DAF4-437F-8513-C1B5BEEA163A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_CAPSULE_SEGMENT_INL)

#include "TgS COLLISION/TgS Collision - Capsule-Linear.inl"
#include "TgS COLLISION/TgS Collision - Capsule-Point.inl"

#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* == Collision ================================================================================================================================================================== */

/* ---- FCN_VO(tgCO_CP_DistSq_SG) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_CP_DistSq_SG)( VEC_OBJ_T(TgTUBE,CPC) psCP0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    VEC_T(1,C)                          vX0 = FCN_VO(tgCO_CP_Dist_SG)( psCP0, psSG0 );

    return (FCN_V(tgMH_MUL)( vX0, vX0 ));
}


/* ---- FCN_VO(tgCO_CP_Dist_SG) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_CP_Dist_SG)( VEC_OBJ_T(TgTUBE,CPC) psCP0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    VEC_T(1,C)                          vX0 = FCN_VO(tgCO_SG_Dist_SG)( &psCP0->m_sAX, psSG0 );
    VEC_T(1,C)                          vX1 = FCN_V(tgMH_SUB)( vX0, psCP0->m_vRadius );
    VEC_T(1,C)                          vRet = FCN_V(tgMH_MAX)( vX1, FCN_V(tgMH_SET1)( TYPE_K(0) ) );

    return (vRet);
}


/* ---- FCN_VO(tgCO_CP_ClosestSq_SG) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_CP_ClosestSq_SG)( VEC_T(1,PC) pvCP0, VEC_T(1,PC) pvSG0, VEC_OBJ_T(TgTUBE,CPC) psCP0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    VEC_T(1,C)                          vX0 = FCN_VO(tgCO_CP_Closest_SG)( pvCP0, pvSG0, psCP0, psSG0 );

    return (FCN_V(tgMH_MUL)( vX0, vX0 ));
}


/* ---- FCN_VO(tgCO_CP_Closest_SG) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_CP_Closest_SG)( VEC_T(1,PC) pvCP0, VEC_T(1,PC) pvSG0, VEC_OBJ_T(TgTUBE,CPC) psCP0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    VEC_T(1)                            vSG0;

    VEC_T(1,C)                          vDist_PT = FCN_VO(tgCO_SG_Closest_SG)( &vSG0, pvSG0, &psCP0->m_sAX, psSG0 );
    VEC_T(1,C)                          vRet = FCN_VO(tgCO_CP_Internal_Dist_SG_PT)( pvCP0, vDist_PT, psCP0->m_vRadius, vSG0, *pvSG0 );

    return (vRet);
}


/* ---- FCN_VO(tgCO_CP_ClosestSq_PM_SG) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_CP_ClosestSq_PM_SG)( VEC_T(1,PC) pvCP0, VEC_T(1,PC) pvSG_T1, VEC_OBJ_T(TgTUBE,CPC) psCP0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    VEC_T(1,C)                          vX0 = FCN_VO(tgCO_CP_Closest_PM_SG)( pvCP0, pvSG_T1, psCP0, psSG0 );

    return (FCN_V(tgMH_MUL)( vX0, vX0 ));
}


/* ---- FCN_VO(tgCO_CP_Closest_PM_SG) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_CP_Closest_PM_SG)( VEC_T(1,PC) pvCP0, VEC_T(1,PC) pvSG_T1, VEC_OBJ_T(TgTUBE,CPC) psCP0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    VEC_T(1)                            vSG_T0;

    VEC_T(1,C)                          vDist_PT = FCN_VO(tgCO_SG_Closest_PM_SG)( &vSG_T0, pvSG_T1, &psCP0->m_sAX, psSG0 );
    VEC_T(1,C)                          vSG0 = FCN_V(tgMH_MAD)( vSG_T0, psCP0->m_sAX.m_vDirN, psCP0->m_sAX.m_vOrigin );
    VEC_T(1,C)                          vSG1 = FCN_V(tgMH_MAD)( *pvSG_T1, psSG0->m_vDirN, psSG0->m_vOrigin );
    VEC_T(1,C)                          vRet = FCN_VO(tgCO_CP_Internal_Dist_SG_PT)( pvCP0, vDist_PT, psCP0->m_vRadius, vSG0, vSG1 );

    return (vRet);
}


/* ---- FCN_VO(tgCO_CP_Test_SG) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_VO(tgCO_CP_Test_SG)(VEC_OBJ_T(TgTUBE,CPC) psCP0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0)
{
    VEC_T(1,C)                          vDist_PT = FCN_VO(tgCO_SG_Dist_SG)( &psCP0->m_sAX, psSG0 );
    VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_LE)( vDist_PT, psCP0->m_vRadius  );

    return (FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_0 ));
}


/* ---- FCN_VO(tgCO_CP_Intersect_SG) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_CP_Intersect_SG)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_OBJ_T(TgTUBE,CPC) psCP0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    return (FCN_VO(tgCO_CP_Intersect_LR11)( psPacket, psCP0, psSG0->m_vOrigin, psSG0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_SG_Penetrate_CP) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_SG_Penetrate_CP)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_OBJ_T(TgSEGMENT,CPC) psSG0, VEC_OBJ_T(TgTUBE,CPC) psCP0 )
{
    VEC_T(1)                            vSG0, vSG1, vDistSq_PT, vCMP_0;

    TgPARAM_CHECK( FCN_VO(tgGM_TB_Is_Valid)( psCP0 ) && FCN_VO(tgGM_SG_Is_Valid)( psSG0 ) );

    if (0 == psPacket->m_nuiMaxContact || psPacket->m_nuiContact >= psPacket->m_nuiMaxContact || nullptr == psPacket->m_psContact)
    {
        return (KTgE_FAIL);
    };

    vDistSq_PT = FCN_VO(tgCO_SG_ClosestSq_SG)( &vSG0, &vSG1, &psCP0->m_sAX, psSG0 );
    vCMP_0 = FCN_V(tgMH_CMP_GT)( vDistSq_PT, psCP0->m_vRadiusSq );

    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_0 ))
    {
        return (KTgE_NO_INTERSECT);
    };

    return (FCN_VO(tgCO_CP_Penetrate_LR11)( psPacket, vSG0, psCP0, vSG1, vDistSq_PT ));
}


/* ---- FCN_VO(tgCO_CP_Clip_PM_SG) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_CP_Clip_PM_SG)(VEC_T(1,PC) pvSG0, VEC_T(1,PC) pvSG1, VEC_OBJ_T(TgTUBE,CPC) psCP0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0)
{
    return (FCN_VO(tgCO_CP_Clip_PM_LR11)( pvSG0, pvSG1, psCP0, psSG0->m_vOrigin, psSG0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_CP_Clip_SG) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_CP_Clip_SG)(VEC_OBJ_T(STg2_CO_Clip_List,PC) psCL, VEC_OBJ_T(TgTUBE,CPC) psCP0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0)
{
    return (FCN_VO(tgCO_CP_Clip_LR11)( psCL, psCP0, psSG0->m_vOrigin, psSG0->m_vDirN ));
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

    #define TGS_COLLISION_CAPSULE_SEGMENT_INL

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COLLISION_CAPSULE_SEGMENT_INL) */
#endif
