/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Box-Segment.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.18 | »GUID« 5BB31923-DAF4-437F-8513-C1B5BEEA163A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_BOX_SEGMENT_INL)
#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* == Collision ================================================================================================================================================================== */

/* ---- FCN_VO(tgCO_BX_DistSq_SG) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_BX_DistSq_SG)( VEC_OBJ_T(TgBOX,CPC) psBX0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    VEC_T(1)                            vBX0, vBX1, vBX2, vSG0;

    return (FCN_VO(tgCO_BX_ClosestSq_PM_LR11)( &vBX0, &vBX1, &vBX2, &vSG0, psBX0, psSG0->m_vOrigin, psSG0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_BX_Dist_SG) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_BX_Dist_SG)( VEC_OBJ_T(TgBOX,CPC) psBX0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_BX_DistSq_SG)( psBX0, psSG0 ) ));
}


/* ---- FCN_VO(tgCO_BX_ClosestSq_SG) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_BX_ClosestSq_SG)( VEC_T(1,PC) pvBX0, VEC_T(1,PC) pvSG0, VEC_OBJ_T(TgBOX,CPC) psBX0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    VEC_T(1)                            vBX0, vBX1, vBX2, vSG0;

    VEC_T(1,C)                          vDistSq = FCN_VO(tgCO_BX_ClosestSq_PM_LR11)( &vBX0, &vBX1, &vBX2, &vSG0, psBX0, psSG0->m_vOrigin, psSG0->m_vDirN );

    *pvBX0 = FCN_VO(tgGM_BX_Calc_Point)( psBX0, vBX0, vBX1, vBX2 );
    *pvSG0 = FCN_V(tgMH_MAD)( vSG0, psSG0->m_vDirN, psSG0->m_vOrigin );

    return (vDistSq);
}


/* ---- FCN_VO(tgCO_BX_Closest_SG) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_BX_Closest_SG)( VEC_T(1,PC) pvBX0, VEC_T(1,PC) pvSG0, VEC_OBJ_T(TgBOX,CPC) psBX0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_BX_ClosestSq_SG)( pvBX0, pvSG0, psBX0, psSG0 ) ));
}


/* ---- FCN_VO(tgCO_BX_ClosestSq_PM_SG) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_BX_ClosestSq_PM_SG)( VEC_T(1,PC) pvBX_T0, VEC_T(1,PC) pvBX_T1, VEC_T(1,PC) pvBX_T2, VEC_T(1,PC) pvSG_T0, VEC_OBJ_T(TgBOX,CPC) psBX0,
                                                   VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    return (FCN_VO(tgCO_BX_ClosestSq_PM_LR11)( pvBX_T0, pvBX_T1, pvBX_T2, pvSG_T0, psBX0, psSG0->m_vOrigin, psSG0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_BX_Closest_PM_SG) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_BX_Closest_PM_SG)( VEC_T(1,PC) pvBX_T0, VEC_T(1,PC) pvBX_T1, VEC_T(1,PC) pvBX_T2, VEC_T(1,PC) pvSG_T0, VEC_OBJ_T(TgBOX,CPC) psBX0,
                                                 VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_BX_ClosestSq_PM_SG)( pvBX_T0, pvBX_T1, pvBX_T2, pvSG_T0, psBX0, psSG0 ) ));
}


/* ---- FCN_VO(tgCO_BX_Clip_PM_SG) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_BX_Clip_PM_SG)( VEC_T(1,PC) pvSG0, VEC_T(1,PC) pvSG1, VEC_OBJ_T(TgBOX,CPC) psBX0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    return (FCN_VO(tgCO_BX_Clip_PM_LR11)( pvSG0, pvSG1, psBX0, psSG0->m_vOrigin, psSG0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_BXF_Clip_PM_SG) ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_BXF_Clip_PM_SG)( VEC_T(1,PC) pvSG0, VEC_T(1,PC) pvSG1, VEC_OBJ_T(TgBOX,CPC) psBX0, TgSINT_F32_C i0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    return (FCN_VO(tgCO_BXF_Clip_PM_LR11)( pvSG0, pvSG1, psBX0, i0, psSG0->m_vOrigin, psSG0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_BX_Clip_SG) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_BX_Clip_SG)( VEC_OBJ_T(STg2_CO_Clip_List,PC) psCL, VEC_OBJ_T(TgBOX,CPC) psBX0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    return (FCN_VO(tgCO_BX_Clip_LR11)( psCL, psBX0, psSG0->m_vOrigin, psSG0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_BXF_Clip_SG) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_BXF_Clip_SG)( VEC_OBJ_T(STg2_CO_Clip_List,PC) psCL, VEC_OBJ_T(TgBOX,CPC) psBX0, TgSINT_F32_C i0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    VEC_OBJ_T(TgRECTANGLE)              sFace;

    return (FCN_VO(tgCO_RT_Clip_SG)( psCL, FCN_VO(tgCO_BXF_Init_Face)( &sFace, psBX0, i0 ), psSG0 ));
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

    #define TGS_COLLISION_BOX_SEGMENT_INL

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COLLISION_BOX_SEGMENT_INL) */
#endif
