/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Capsule-Line.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.18 | »GUID« 5BB31923-DAF4-437F-8513-C1B5BEEA163A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_CAPSULE_LINE_INL)
#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* == Collision ================================================================================================================================================================== */

/* ---- FCN_VO(tgCO_CP_DistSq_LN) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_CP_DistSq_LN)( VEC_OBJ_T(TgTUBE,CPC) psCP0, VEC_OBJ_T(TgLINE,CPC) psLN0 )
{
    VEC_T(1,C)                          vX0 = FCN_VO(tgCO_CP_Dist_LN)( psCP0, psLN0 );

    return (FCN_V(tgMH_MUL)( vX0, vX0 ));
}


/* ---- FCN_VO(tgCO_CP_Dist_LN) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_CP_Dist_LN)( VEC_OBJ_T(TgTUBE,CPC) psCP0, VEC_OBJ_T(TgLINE,CPC) psLN0 )
{
    VEC_T(1,C)                          vX0 = FCN_VO(tgCO_SG_Dist_LN)( &psCP0->m_sAX, psLN0 );
    VEC_T(1,C)                          vX1 =  FCN_V(tgMH_SUB)( vX0, psCP0->m_vRadius );
    VEC_T(1,C)                          vRet = FCN_V(tgMH_MAX)( vX1, FCN_V(tgMH_SET1)( TYPE_K(0) ) );

    return (vRet);
}


/* ---- FCN_VO(tgCO_CP_ClosestSq_LN) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_CP_ClosestSq_LN)( VEC_T(1,PC) pvCP0, VEC_T(1,PC) pvLN0, VEC_OBJ_T(TgTUBE,CPC) psCP0, VEC_OBJ_T(TgLINE,CPC) psLN0 )
{
    VEC_T(1,C)                          vX0 = FCN_VO(tgCO_CP_Closest_LN)( pvCP0, pvLN0, psCP0, psLN0 );

    return (FCN_V(tgMH_MUL)( vX0, vX0 ));
}


/* ---- FCN_VO(tgCO_CP_Closest_LN) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_CP_Closest_LN)( VEC_T(1,PC) pvCP0, VEC_T(1,PC) pvLN0, VEC_OBJ_T(TgTUBE,CPC) psCP0, VEC_OBJ_T(TgLINE,CPC) psLN0 )
{
    VEC_T(1)                            vSG0;

    VEC_T(1,C)                          vDist_PT = FCN_VO(tgCO_SG_Closest_LN)( &vSG0, pvLN0, &psCP0->m_sAX, psLN0 );
    VEC_T(1,C)                          vRet = FCN_VO(tgCO_CP_Internal_Dist_SG_PT)( pvCP0, vDist_PT, psCP0->m_vRadius, vSG0, *pvLN0 );

    return (vRet);
}


/* ---- FCN_VO(tgCO_CP_ClosestSq_PM_LN) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_CP_ClosestSq_PM_LN)( VEC_T(1,PC) pvCP0, VEC_T(1,PC) pvLN_T0, VEC_OBJ_T(TgTUBE,CPC) psCP0, VEC_OBJ_T(TgLINE,CPC) psLN0 )
{
    VEC_T(1,C)                          vX0 = FCN_VO(tgCO_CP_Closest_PM_LN)( pvCP0, pvLN_T0, psCP0, psLN0 );

    return (FCN_V(tgMH_MUL)( vX0, vX0 ));
}


/* ---- FCN_VO(tgCO_CP_Closest_PM_LN) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_CP_Closest_PM_LN)( VEC_T(1,PC) pvCP0, VEC_T(1,PC) pvLN_T0, VEC_OBJ_T(TgTUBE,CPC) psCP0, VEC_OBJ_T(TgLINE,CPC) psLN0 )
{
    VEC_T(1)                            vCP_T0;

    VEC_T(1,C)                          vDist_PT = FCN_VO(tgCO_SG_Closest_PM_LN)( &vCP_T0, pvLN_T0, &psCP0->m_sAX, psLN0 );
    VEC_T(1,C)                          vSG0 = FCN_V(tgMH_MAD)( vCP_T0, psCP0->m_sAX.m_vDirN, psCP0->m_sAX.m_vOrigin );
    VEC_T(1,C)                          vLN0 = FCN_V(tgMH_MAD)( *pvLN_T0, psLN0->m_vDirN, psLN0->m_vOrigin );
    VEC_T(1,C)                          vRet = FCN_VO(tgCO_CP_Internal_Dist_SG_PT)( pvCP0, vDist_PT, psCP0->m_vRadius, vSG0, vLN0 );

    return (vRet);
}


/* ---- FCN_VO(tgCO_CP_Test_LN) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_VO(tgCO_CP_Test_LN)( VEC_OBJ_T(TgTUBE,CPC) psCP0, VEC_OBJ_T(TgLINE,CPC) psLN0 )
{
    VEC_T(1,C)                          vDist_PT = FCN_VO(tgCO_SG_Dist_LN)( &psCP0->m_sAX, psLN0 );
    VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_LE)( vDist_PT, psCP0->m_vRadius  );

    return (FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_0 ));
}


/* ---- FCN_VO(tgCO_CP_Intersect_LN) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_CP_Intersect_LN)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_OBJ_T(TgTUBE,CPC) psCP0, VEC_OBJ_T(TgLINE,CPC) psLN0 )
{
    return (FCN_VO(tgCO_CP_Intersect_LR00)( psPacket, psCP0, psLN0->m_vOrigin, psLN0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_LN_Penetrate_CP) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_LN_Penetrate_CP)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_OBJ_T(TgLINE,CPC) psLN0, VEC_OBJ_T(TgTUBE,CPC) psCP0 )
{
    VEC_T(1)                            vSG0, vLN0;

    TgPARAM_CHECK( FCN_VO(tgGM_TB_Is_Valid)( psCP0 ) && FCN_VO(tgGM_LN_Is_Valid)( psLN0 ) );

    if (0 == psPacket->m_nuiMaxContact || nullptr == psPacket->m_psContact)
    {
        return (KTgE_FAIL);
    };

    VEC_T(1,C)                          vDistSq_PT = FCN_VO(tgCO_SG_ClosestSq_LN)( &vSG0, &vLN0, &psCP0->m_sAX, psLN0 );
    VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_GT)( vDistSq_PT, psCP0->m_vRadiusSq  );

    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_0 ))
    {
        return (KTgE_NO_INTERSECT);
    };

    return (FCN_VO(tgCO_CP_Penetrate_LR00)( psPacket, vLN0, psCP0, vSG0, vDistSq_PT ));
}


/* ---- FCN_VO(tgCO_CP_Clip_PM_LN) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_CP_Clip_PM_LN)( VEC_T(1,PC) pvLN0, VEC_T(1,PC) pvLN1, VEC_OBJ_T(TgTUBE,CPC) psCP0, VEC_OBJ_T(TgLINE,CPC) psLN0 )
{
    return (FCN_VO(tgCO_CP_Clip_PM_LR00)( pvLN0, pvLN1, psCP0, psLN0->m_vOrigin, psLN0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_CP_Clip_LN) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_CP_Clip_LN)( VEC_OBJ_T(STg2_CO_Clip_List,PC) psCL, VEC_OBJ_T(TgTUBE,CPC) psCP0, VEC_OBJ_T(TgLINE,CPC) psLN0 )
{
    return (FCN_VO(tgCO_CP_Clip_LR00)( psCL, psCP0, psLN0->m_vOrigin, psLN0->m_vDirN ));
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

    #define TGS_COLLISION_CAPSULE_LINE_INL

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COLLISION_CAPSULE_LINE_INL) */
#endif
