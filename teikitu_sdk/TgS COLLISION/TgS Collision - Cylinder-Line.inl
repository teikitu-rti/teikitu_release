/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Cylinder-Line.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.18 | »GUID« 5BB31923-DAF4-437F-8513-C1B5BEEA163A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_CYLINDER_LINE_INL)
#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* == Collision ================================================================================================================================================================== */

/* ---- FCN_VO(tgCO_CY_Closest_PM_LN) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_CY_Closest_PM_LN)( VEC_T(1,PC) pvCY0, VEC_T(1,PC) pvLN0, VEC_OBJ_T(TgTUBE,CPC) psCY0, VEC_OBJ_T(TgLINE,CPC) psLN0 )
{
    return (FCN_VO(tgCO_CY_Closest_PM_LR00)( pvCY0, pvLN0, psCY0, psLN0->m_vOrigin, psLN0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_CY_Intersect_LN) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_CY_Intersect_LN)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_OBJ_T(TgTUBE,CPC) psCY0, VEC_OBJ_T(TgLINE,CPC) psLN0 )
{
    return (FCN_VO(tgCO_CY_Intersect_LR00)( psPacket, psCY0, psLN0->m_vOrigin, psLN0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_CY_Clip_PM_LN) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_CY_Clip_PM_LN)( VEC_T(1,PC) pvLN0, VEC_T(1,PC) pvLN1, VEC_OBJ_T(TgTUBE,CPC) psCY0, VEC_OBJ_T(TgLINE,CPC) psLN0 )
{
    return (FCN_VO(tgCO_CY_Clip_PM_LR00)( pvLN0, pvLN1, psCY0, psLN0->m_vOrigin, psLN0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_CY_Clip_LN) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_CY_Clip_LN)( VEC_OBJ_T(STg2_CO_Clip_List,PC) psCL, VEC_OBJ_T(TgTUBE,CPC) psCY0, VEC_OBJ_T(TgLINE,CPC) psLN0 )
{
    return (FCN_VO(tgCO_CY_Clip_LR00)( psCL, psCY0, psLN0->m_vOrigin, psLN0->m_vDirN ));
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

    #define TGS_COLLISION_CYLINDER_LINE_INL

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COLLISION_CYLINDER_LINE_INL) */
#endif
