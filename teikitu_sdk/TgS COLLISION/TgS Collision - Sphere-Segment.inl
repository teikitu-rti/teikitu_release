/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Sphere-Segment.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.18 | »GUID« 5BB31923-DAF4-437F-8513-C1B5BEEA163A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_SPHERE_SEGMENT_INL)

#include "TgS COLLISION/TgS Collision - Sphere-Linear.inl"
#include "TgS COLLISION/TgS Collision - Sphere-Point.inl"


#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* == Collision ================================================================================================================================================================== */

/* ---- FCN_VO(tgCO_SP_DistSq_SG) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_SP_DistSq_SG)( VEC_OBJ_T(TgSPHERE,CPC) psSP0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    VEC_T(1,C)                          vX0 = FCN_VO(tgCO_SP_Dist_SG)( psSP0, psSG0 );

    return (FCN_V(tgMH_MUL)( vX0, vX0 ));
}


/* ---- FCN_VO(tgCO_SP_Dist_SG) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_SP_Dist_SG)( VEC_OBJ_T(TgSPHERE,CPC) psSP0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    VEC_T(1,C)                          vX0 = FCN_VO(tgCO_SG_Dist_PT)( psSG0, psSP0->m_vOrigin );
    VEC_T(1,C)                          vX1 = FCN_V(tgMH_SUB)( vX0, psSP0->m_vRadius );
    VEC_T(1,C)                          vX2 = FCN_V(tgMH_MAX)( vX1, FCN_V(tgMH_SET1)( TYPE_K(0) ) );

    return (vX2);
}


/* ---- FCN_VO(tgCO_SP_ClosestSq_SG) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_SP_ClosestSq_SG)( VEC_T(1,PC) pvSP0, VEC_T(1,PC) pvSG0, VEC_OBJ_T(TgSPHERE,CPC) psSP0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    VEC_T(1,C)                          vX0 = FCN_VO(tgCO_SP_Closest_SG)( pvSP0, pvSG0, psSP0, psSG0 );

    return (FCN_V(tgMH_MUL)( vX0, vX0 ));
}


/* ---- FCN_VO(tgCO_SP_Closest_SG) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_SP_Closest_SG)( VEC_T(1,PC) pvSP0, VEC_T(1,PC) pvSG0, VEC_OBJ_T(TgSPHERE,CPC) psSP0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    VEC_T(1,C)                          vDist_PT = FCN_VO(tgCO_SG_Closest_PT)( pvSG0, psSG0, psSP0->m_vOrigin );
    VEC_T(1,C)                          vRet = FCN_VO(tgCO_SP_Util__Closest_PT_Dist)( pvSP0, psSP0, vDist_PT, *pvSG0 );

    return (vRet);
}


/* ---- FCN_VO(tgCO_SP_ClosestSq_PM_SG) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_SP_ClosestSq_PM_SG)( VEC_T(1,PC) pvSP0, VEC_T(1,PC) pvT1, VEC_OBJ_T(TgSPHERE,CPC) psSP0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    VEC_T(1,C)                          vX0 = FCN_VO(tgCO_SP_Closest_PM_SG)( pvSP0, pvT1, psSP0, psSG0 );

    return (FCN_V(tgMH_MUL)( vX0, vX0 ));
}


/* ---- FCN_VO(tgCO_SP_Closest_PM_SG) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_SP_Closest_PM_SG)( VEC_T(1,PC) pvSP0, VEC_T(1,PC) pvT1, VEC_OBJ_T(TgSPHERE,CPC) psSP0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    VEC_T(1,C)                          vDist_PT = FCN_VO(tgCO_SG_Closest_PM_PT)( pvT1, psSG0, psSP0->m_vOrigin );
    VEC_T(1,C)                          vSG0 = FCN_V(tgMH_MAD)( *pvT1, psSG0->m_vDirN, psSG0->m_vOrigin );
    VEC_T(1,C)                          vRet = FCN_VO(tgCO_SP_Util__Closest_PT_Dist)( pvSP0, psSP0, vDist_PT, vSG0 );

    return (vRet);
}


/* ---- FCN_VO(tgCO_SP_Test_SG) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_VO(tgCO_SP_Test_SG)( VEC_OBJ_T(TgSPHERE,CPC) psSP0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    VEC_T(1,C)                          vDist_PT = FCN_VO(tgCO_SG_DistSq_PT)( psSG0, psSP0->m_vOrigin );
    VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_LE)( vDist_PT, psSP0->m_vRadiusSq  );

    return (FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_0 ));
}


/* ---- FCN_VO(tgCO_SP_Intersect_SG) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_SP_Intersect_SG)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_OBJ_T(TgSPHERE,CPC) psSP0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    return (FCN_VO(tgCO_SP_Intersect_LR11)( psPacket, psSP0, psSG0->m_vOrigin, psSG0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_SP_Penetrate_SG) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_SP_Penetrate_SG)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_OBJ_T(TgSPHERE,CPC) psSP0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    VEC_T(1)                            vSG0;

    TgPARAM_CHECK( FCN_VO(tgGM_SP_Is_Valid)( psSP0 ) && FCN_VO(tgGM_SG_Is_Valid)( psSG0 ) );

    if (0 == psPacket->m_nuiMaxContact || psPacket->m_nuiContact >= psPacket->m_nuiMaxContact || nullptr == psPacket->m_psContact)
    {
        return (KTgE_FAIL);
    };

    {
        VEC_T(1,C)                          vDistSq_PT = FCN_VO(tgCO_SG_ClosestSq_PT)( &vSG0, psSG0, psSP0->m_vOrigin );
        VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_GT)( vDistSq_PT, psSP0->m_vRadiusSq  );

        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_0 ))
        {
            return (KTgE_NO_INTERSECT);
        };

        return (FCN_VO(tgCO_SP_Util__Penetrate_Closest_PT_Dist)( psPacket, psSP0, vSG0, vDistSq_PT, psSG0->m_vDirN ));
    }
}


/* ---- FCN_VO(tgCO_SP_Sweep_SG) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_SP_Sweep_SG)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_T(1,PC) pvPM, TgRSIZE_P puiStart, VEC_OBJ_T(TgSPHERE,CPC) psSP0,
                                            VEC_OBJ_T(TgSEGMENT,CPC) psSG0, VEC_OBJ_T(TgDELTA,CPC) psDT )
{
    return (FCN_VO(tgCO_SP_Sweep_LR11)( psPacket, pvPM, puiStart, psSP0, psSG0->m_vOrigin, psSG0->m_vDirN, psDT ));
}


/* ---- FCN_VO(tgCO_SP_Clip_PM_SG) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_SP_Clip_PM_SG)( VEC_T(1,PC) pvSG0, VEC_T(1,PC) pvSG1, VEC_OBJ_T(TgSPHERE,CPC) psSP0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    return (FCN_VO(tgCO_SP_Clip_PM_LR11)( pvSG0, pvSG1, psSP0, psSG0->m_vOrigin, psSG0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_SP_Clip_SG) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_SP_Clip_SG)( VEC_OBJ_T(STg2_CO_Clip_List,PC) psCL, VEC_OBJ_T(TgSPHERE,CPC) psSP0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    return (FCN_VO(tgCO_SP_Clip_LR11)( psCL, psSP0, psSG0->m_vOrigin, psSG0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_SP_Clip_Points) ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_SP_Clip_Points)( VEC_T(1,PC) pvSG0, VEC_T(1,PC) pvSG1, VEC_OBJ_T(TgSPHERE,CPC) psSP0, VEC_T(1,C) vS0, VEC_T(1,C) vS1 )
{
    VEC_T(1)                            vD0;

    vD0 = FCN_V(tgMH_SUB)( vS1, vS0 );
    return (FCN_VO(tgCO_SP_Clip_PM_LR11)( pvSG0, pvSG1, psSP0, vS0, vD0 ));
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

    #define TGS_COLLISION_SPHERE_SEGMENT_INL

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COLLISION_SPHERE_SEGMENT_INL) */
#endif
