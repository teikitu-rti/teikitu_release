/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Box-Line.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.18 | »GUID« 5BB31923-DAF4-437F-8513-C1B5BEEA163A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_BOX_LINE_INL)
#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* == Collision ================================================================================================================================================================== */

/* ---- FCN_VO(tgCO_BX_DistSq_LN) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_BX_DistSq_LN)( VEC_OBJ_T(TgBOX,CPC) psBX0, VEC_OBJ_T(TgLINE,CPC) psLN0 )
{
    VEC_T(1)                            vBX0, vBX1, vBX2, vLN0;

    return (FCN_VO(tgCO_BX_ClosestSq_PM_LR00)( &vBX0, &vBX1, &vBX2, &vLN0, psBX0, psLN0->m_vOrigin, psLN0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_BX_Dist_LN) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_BX_Dist_LN)( VEC_OBJ_T(TgBOX,CPC) psBX0, VEC_OBJ_T(TgLINE,CPC) psLN0 )
{
    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_BX_DistSq_LN)( psBX0, psLN0 ) ));
}


/* ---- FCN_VO(tgCO_BX_ClosestSq_LN) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_BX_ClosestSq_LN)( VEC_T(1,PC) pvBX0, VEC_T(1,PC) pvLN0, VEC_OBJ_T(TgBOX,CPC) psBX0, VEC_OBJ_T(TgLINE,CPC) psLN0 )
{
    VEC_T(1)                            vBX0, vBX1, vBX2, vLN0;

    VEC_T(1,C)                          vDistSq = FCN_VO(tgCO_BX_ClosestSq_PM_LR00)( &vBX0, &vBX1, &vBX2, &vLN0, psBX0, psLN0->m_vOrigin, psLN0->m_vDirN );

    *pvBX0 = FCN_VO(tgGM_BX_Calc_Point)( psBX0, vBX0, vBX1, vBX2 );
    *pvLN0 = FCN_V(tgMH_MAD)( vLN0, psLN0->m_vDirN, psLN0->m_vOrigin );

    return (vDistSq);
}


/* ---- FCN_VO(tgCO_BX_Closest_LN) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_BX_Closest_LN)( VEC_T(1,PC) pvBX0, VEC_T(1,PC) pvLN0, VEC_OBJ_T(TgBOX,CPC) psBX0, VEC_OBJ_T(TgLINE,CPC) psLN0 )
{
    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_BX_ClosestSq_LN)( pvBX0, pvLN0, psBX0, psLN0 ) ));
}


/* ---- FCN_VO(tgCO_BX_ClosestSq_PM_LN) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_BX_ClosestSq_PM_LN)( VEC_T(1,PC) pvBX_T0, VEC_T(1,PC) pvBX_T1, VEC_T(1,PC) pvBX_T2, VEC_T(1,PC) pvLN_T0, VEC_OBJ_T(TgBOX,CPC) psBX0,
                                                   VEC_OBJ_T(TgLINE,CPC) psLN0 )
{
    return (FCN_VO(tgCO_BX_ClosestSq_PM_LR00)( pvBX_T0, pvBX_T1, pvBX_T2, pvLN_T0, psBX0, psLN0->m_vOrigin, psLN0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_BX_Closest_PM_LN) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_BX_Closest_PM_LN)( VEC_T(1,PC) pvBX_T0, VEC_T(1,PC) pvBX_T1, VEC_T(1,PC) pvBX_T2, VEC_T(1,PC) pvLN_T0, VEC_OBJ_T(TgBOX,CPC) psBX0,
                                                 VEC_OBJ_T(TgLINE,CPC) psLN0 )
{
    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_BX_ClosestSq_PM_LN)( pvBX_T0, pvBX_T1, pvBX_T2, pvLN_T0, psBX0, psLN0 ) ));
}


/* ---- FCN_VO(tgCO_BX_Clip_PM_LN) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_BX_Clip_PM_LN)( VEC_T(1,PC) pvLN0, VEC_T(1,PC) pvLN1, VEC_OBJ_T(TgBOX,CPC) psBX0, VEC_OBJ_T(TgLINE,CPC) psLN0 )
{
    return (FCN_VO(tgCO_BX_Clip_PM_LR00)( pvLN0, pvLN1, psBX0, psLN0->m_vOrigin, psLN0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_BXF_Clip_PM_LN) ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_BXF_Clip_PM_LN)( VEC_T(1,PC) pvLN0, VEC_T(1,PC) pvLN1, VEC_OBJ_T(TgBOX,CPC) psBX0, TgSINT_F32_C i0, VEC_OBJ_T(TgLINE,CPC) psLN0 )
{
    return (FCN_VO(tgCO_BXF_Clip_PM_LR00)( pvLN0, pvLN1, psBX0, i0, psLN0->m_vOrigin, psLN0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_BX_Clip_LN) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_BX_Clip_LN)( VEC_OBJ_T(STg2_CO_Clip_List,PC) psCL, VEC_OBJ_T(TgBOX,CPC) psBX0, VEC_OBJ_T(TgLINE,CPC) psLN0 )
{
    return (FCN_VO(tgCO_BX_Clip_LR00)( psCL, psBX0, psLN0->m_vOrigin, psLN0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_BXF_Clip_LN) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_BXF_Clip_LN)( VEC_OBJ_T(STg2_CO_Clip_List,PC) psCL, VEC_OBJ_T(TgBOX,CPC) psBX0, TgSINT_F32_C i0, VEC_OBJ_T(TgLINE,CPC) psLN0 )
{
    VEC_OBJ_T(TgRECTANGLE)              sFace;

    return (FCN_VO(tgCO_RT_Clip_LN)( psCL, FCN_VO(tgCO_BXF_Init_Face)( &sFace, psBX0, i0 ), psLN0 ));
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

    #define TGS_COLLISION_BOX_LINE_INL

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COLLISION_BOX_LINE_INL) */
#endif
