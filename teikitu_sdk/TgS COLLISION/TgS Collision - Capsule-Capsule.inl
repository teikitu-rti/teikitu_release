/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Capsule-Capsule.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.18 | »GUID« 5BB31923-DAF4-437F-8513-C1B5BEEA163A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_CAPSULE_CAPSULE_INL)
#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* == Collision ================================================================================================================================================================== */

/* ---- FCN_VO(tgCO_CP_DistSq_CP) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_CP_DistSq_CP)( VEC_OBJ_T(TgTUBE,CPC) psCP0, VEC_OBJ_T(TgTUBE,CPC) psCP1 )
{
    VEC_T(1,C)                          vX0 = FCN_VO(tgCO_CP_Dist_CP)( psCP0, psCP1 );

    return (FCN_V(tgMH_MUL)( vX0, vX0 ));
}


/* ---- FCN_VO(tgCO_CP_Dist_CP) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_CP_Dist_CP)( VEC_OBJ_T(TgTUBE,CPC) psCP0, VEC_OBJ_T(TgTUBE,CPC) psCP1 )
{
    VEC_T(1,C)                          vX0 = FCN_VO(tgCO_SG_Dist_SG)( &psCP0->m_sAX, &psCP1->m_sAX );
    VEC_T(1,C)                          vSum_Rad = FCN_V(tgMH_ADD)( psCP0->m_vRadius, psCP1->m_vRadius );
    VEC_T(1,C)                          vX1 = FCN_V(tgMH_SUB)( vX0, vSum_Rad );
    VEC_T(1,C)                          vRet = FCN_V(tgMH_MAX)( vX1, FCN_V(tgMH_SET1)( TYPE_K(0) ) );

    return (vRet);
}


/* ---- FCN_VO(tgCO_CP_ClosestSq_CP) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_CP_ClosestSq_CP)( VEC_T(1,PC) pvCP0, VEC_T(1,PC) pvCP1, VEC_OBJ_T(TgTUBE,CPC) psCP0, VEC_OBJ_T(TgTUBE,CPC) psCP1 )
{
    VEC_T(1,C)                          vX0 = FCN_VO(tgCO_CP_Closest_CP)( pvCP0, pvCP1, psCP0, psCP1 );

    return (FCN_V(tgMH_MUL)( vX0, vX0 ));
}


/* ---- FCN_VO(tgCO_CP_Closest_CP) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_CP_Closest_CP)( VEC_T(1,PC) pvCP0, VEC_T(1,PC) pvCP1, VEC_OBJ_T(TgTUBE,CPC) psCP0, VEC_OBJ_T(TgTUBE,CPC) psCP1 )
{
    VEC_T(1)                            vSG0, vSG1;

    VEC_T(1,C)                          vDist_PT = FCN_VO(tgCO_SG_Closest_SG)( &vSG0, &vSG1, &psCP0->m_sAX, &psCP1->m_sAX );
    VEC_T(1,C)                          vRet = FCN_VO(tgCO_CP_Internal_Dist_SG_SP)( pvCP0, pvCP1, vDist_PT, psCP0->m_vRadius, vSG0, psCP0->m_vRadius, vSG1 );

    return (vRet);
}


/* ---- FCN_VO(tgCO_CP_Test_CP) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_VO(tgCO_CP_Test_CP)( VEC_OBJ_T(TgTUBE,CPC) psCP0, VEC_OBJ_T(TgTUBE,CPC) psCP1 )
{
    VEC_T(1,C)                          vX0 = FCN_VO(tgCO_SG_Dist_SG)( &psCP0->m_sAX, &psCP1->m_sAX );
    VEC_T(1,C)                          vSum_Rad = FCN_V(tgMH_ADD)( psCP0->m_vRadius, psCP1->m_vRadius );
    VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_LE)( vX0, vSum_Rad );

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

    #define TGS_COLLISION_CAPSULE_CAPSULE_INL

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COLLISION_CAPSULE_CAPSULE_INL) */
#endif
