/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Box-Ray.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.18 | »GUID« 5BB31923-DAF4-437F-8513-C1B5BEEA163A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_BOX_RAY_INL)
#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* == Collision ================================================================================================================================================================== */

/* ---- FCN_VO(tgCO_BX_DistSq_RY) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_BX_DistSq_RY)( VEC_OBJ_T(TgBOX,CPC) psBX0, VEC_OBJ_T(TgRAY,CPC) psRY0 )
{
    VEC_T(1)                            vBX0, vBX1, vBX2, vRY0;

    return (FCN_VO(tgCO_BX_ClosestSq_PM_LR10)( &vBX0, &vBX1, &vBX2, &vRY0, psBX0, psRY0->m_vOrigin, psRY0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_BX_Dist_RY) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_BX_Dist_RY)( VEC_OBJ_T(TgBOX,CPC) psBX0, VEC_OBJ_T(TgRAY,CPC) psRY0 )
{
    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_BX_DistSq_RY)( psBX0, psRY0 ) ));
}


/* ---- FCN_VO(tgCO_BX_ClosestSq_RY) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_BX_ClosestSq_RY)( VEC_T(1,PC) pvBX0, VEC_T(1,PC) pvRY0, VEC_OBJ_T(TgBOX,CPC) psBX0, VEC_OBJ_T(TgRAY,CPC) psRY0 )
{
    VEC_T(1)                            vBX0, vBX1, vBX2, vRY0;

    VEC_T(1,C)                          vDistSq = FCN_VO(tgCO_BX_ClosestSq_PM_LR10)( &vBX0, &vBX1, &vBX2, &vRY0, psBX0, psRY0->m_vOrigin, psRY0->m_vDirN );

    *pvBX0 = FCN_VO(tgGM_BX_Calc_Point)( psBX0, vBX0, vBX1, vBX2 );
    *pvRY0 = FCN_V(tgMH_MAD)( vRY0, psRY0->m_vDirN, psRY0->m_vOrigin );

    return (vDistSq);
}


/* ---- FCN_VO(tgCO_BX_Closest_RY) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_BX_Closest_RY)( VEC_T(1,PC) pvBX0, VEC_T(1,PC) pvRY0, VEC_OBJ_T(TgBOX,CPC) psBX0, VEC_OBJ_T(TgRAY,CPC) psRY0 )
{
    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_BX_ClosestSq_RY)( pvBX0, pvRY0, psBX0, psRY0 ) ));
}


/* ---- FCN_VO(tgCO_BX_ClosestSq_PM_RY) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_BX_ClosestSq_PM_RY)( VEC_T(1,PC) pvBX_T0, VEC_T(1,PC) pvBX_T1, VEC_T(1,PC) pvBX_T2, VEC_T(1,PC) pvRY_T0, VEC_OBJ_T(TgBOX,CPC) psBX0,
                                                   VEC_OBJ_T(TgRAY,CPC) psRY0)
{
    return (FCN_VO(tgCO_BX_ClosestSq_PM_LR10)( pvBX_T0, pvBX_T1, pvBX_T2, pvRY_T0, psBX0, psRY0->m_vOrigin, psRY0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_BX_Closest_PM_RY) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_BX_Closest_PM_RY)( VEC_T(1,PC) pvBX_T0, VEC_T(1,PC) pvBX_T1, VEC_T(1,PC) pvBX_T2, VEC_T(1,PC) pvRY_T0, VEC_OBJ_T(TgBOX,CPC) psBX0,
                                                 VEC_OBJ_T(TgRAY,CPC) psRY0)
{
    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_BX_ClosestSq_PM_RY)( pvBX_T0, pvBX_T1, pvBX_T2, pvRY_T0, psBX0, psRY0 ) ));
}


/* ---- FCN_VO(tgCO_BX_Clip_PM_RY) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_BX_Clip_PM_RY)(VEC_T(1,PC) pvRY0, VEC_T(1,PC) pvRY1, VEC_OBJ_T(TgBOX,CPC) psBX0, VEC_OBJ_T(TgRAY,CPC) psRY0)
{
    return (FCN_VO(tgCO_BX_Clip_PM_LR10)( pvRY0, pvRY1, psBX0, psRY0->m_vOrigin, psRY0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_BXF_Clip_PM_RY) ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_BXF_Clip_PM_RY)( VEC_T(1,PC) pvRY0, VEC_T(1,PC) pvRY1, VEC_OBJ_T(TgBOX,CPC) psBX0, TgSINT_E32_C i0, VEC_OBJ_T(TgRAY,CPC) psRY0)
{
    return (FCN_VO(tgCO_BXF_Clip_PM_LR10)( pvRY0, pvRY1, psBX0, i0, psRY0->m_vOrigin, psRY0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_BX_Clip_RY) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_BX_Clip_RY)(VEC_OBJ_T(STg2_CO_Clip_List,PC) psCL, VEC_OBJ_T(TgBOX,CPC) psBX0, VEC_OBJ_T(TgRAY,CPC) psRY0)
{
    return (FCN_VO(tgCO_BX_Clip_LR10)( psCL, psBX0, psRY0->m_vOrigin, psRY0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_BXF_Clip_RY) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_BXF_Clip_RY)(VEC_OBJ_T(STg2_CO_Clip_List,PC) psCL, VEC_OBJ_T(TgBOX,CPC) psBX0, TgSINT_E32_C i0, VEC_OBJ_T(TgRAY,CPC) psRY0)
{
    VEC_OBJ_T(TgRECTANGLE)              sFace;

    return (FCN_VO(tgCO_RT_Clip_RY)( psCL, FCN_VO(tgCO_BXF_Init_Face)( &sFace, psBX0, i0 ), psRY0 ));
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

    #define TGS_COLLISION_BOX_RAY_INL

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COLLISION_BOX_RAY_INL) */
#endif
