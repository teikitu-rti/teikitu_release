/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Box-Plane.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.18 | »GUID« 5BB31923-DAF4-437F-8513-C1B5BEEA163A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_BOX_PLANE_INL)
#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* == Collision ================================================================================================================================================================== */

/* ---- FCN_VO(tgCO_BX_DistSq_PN) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_BX_DistSq_PN)( VEC_OBJ_T(TgBOX,CPC) psBX0, VEC_OBJ_T(TgPLANE,CPC) psPN0 )
{
    VEC_T(1)                            vT0, vT1, vT2, vT3;

    VEC_T(1,C)                          vDist = FCN_VO(tgCO_BX_Closest_PM_PN)( &vT0, &vT1, &vT2, &vT3, psBX0, psPN0 );

    return (FCN_V(tgMH_MUL)( vDist, vDist ));
}


/* ---- FCN_VO(tgCO_BX_Dist_PN) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_BX_Dist_PN)( VEC_OBJ_T(TgBOX,CPC) psBX0, VEC_OBJ_T(TgPLANE,CPC) psPN0 )
{
    VEC_T(1)                            vT0, vT1, vT2, vT3;

    return (FCN_VO(tgCO_BX_Closest_PM_PN)( &vT0, &vT1, &vT2, &vT3, psBX0, psPN0 ));
}


/* ---- FCN_VO(tgCO_BX_ClosestSq_PN) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_BX_ClosestSq_PN)( VEC_T(1,PC) pvBX0, VEC_T(1,PC) pvPN0, VEC_OBJ_T(TgBOX,CPC) psBX0, VEC_OBJ_T(TgPLANE,CPC) psPN0 )
{
    VEC_T(1)                            vT0, vT1, vT2;

    VEC_T(1,C)                          vDist = FCN_VO(tgCO_BX_Closest_PM_PN)( &vT0, &vT1, &vT2, pvPN0, psBX0, psPN0 );

    *pvBX0 = FCN_VO(tgGM_BX_Calc_Point)( psBX0, vT0, vT1, vT2 );

    return (FCN_V(tgMH_MUL)( vDist, vDist ));
}


/* ---- FCN_VO(tgCO_BX_Closest_PN) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_BX_Closest_PN)( VEC_T(1,PC) pvBX0, VEC_T(1,PC) pvPN0, VEC_OBJ_T(TgBOX,CPC) psBX0, VEC_OBJ_T(TgPLANE,CPC) psPN0 )
{
    VEC_T(1)                            vT0, vT1, vT2;

    VEC_T(1,C)                          vDist = FCN_VO(tgCO_BX_Closest_PM_PN)( &vT0, &vT1, &vT2, pvPN0, psBX0, psPN0 );

    *pvBX0 = FCN_VO(tgGM_BX_Calc_Point)( psBX0, vT0, vT1, vT2 );

    return (vDist);
}


/* ---- FCN_VO(tgCO_BX_ClosestSq_PM_PN) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_BX_ClosestSq_PM_PN)( VEC_T(1,PC) pvBX0, VEC_T(1,PC) pvBX1, VEC_T(1,PC) pvBX2, VEC_T(1,PC) pvPN0, VEC_OBJ_T(TgBOX,CPC) psBX0, VEC_OBJ_T(TgPLANE,CPC) psPN0 )
{
    VEC_T(1,C)                          vDist = FCN_VO(tgCO_BX_Closest_PM_PN)( pvBX0, pvBX1, pvBX2, pvPN0, psBX0, psPN0 );

    return (FCN_V(tgMH_MUL)( vDist, vDist ));
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

    #define TGS_COLLISION_BOX_PLANE_INL

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COLLISION_BOX_PLANE_INL) */
#endif
