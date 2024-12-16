/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Box AA-Plane.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.18 | »GUID« 5BB31923-DAF4-437F-8513-C1B5BEEA163A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_BOXAA_PLANE_INL)
#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* == Collision ================================================================================================================================================================== */

/* ---- FCN_VO(tgCO_BA_DistSq_PN) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_BA_DistSq_PN)( VEC_OBJ_T(TgBOXAA,CPC) psBA0, VEC_OBJ_T(TgPLANE,CPC) psPN0 )
{
    VEC_T(1,C)                          vDist = FCN_VO(tgCO_BA_Dist_PN)( psBA0, psPN0 );

    return (FCN_V(tgMH_MUL)( vDist, vDist ));
}


/* ---- FCN_VO(tgCO_BA_Dist_PN) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_BA_Dist_PN)( VEC_OBJ_T(TgBOXAA,CPC) psBA0, VEC_OBJ_T(TgPLANE,CPC) psPN0 )
{
    VEC_T(1,C)                          vX0 = FCN_V(tgMH_CMP_GE)( psPN0->m_vNormal, FCN_V(tgMH_SET1)( TYPE_K(0) ) );
    VEC_T(1,C)                          vX1 = FCN_V(tgMH_SEL)( psBA0->m_vMax, psBA0->m_vMin, vX0 );
    VEC_T(1,C)                          vX2 = FCN_V(tgMH_Init_Point)( vX1 );
    VEC_T(1,C)                          vX3 = FCN_V(tgMH_DOT)( vX2, psPN0->m_vPlnEqN );
    VEC_T(1,C)                          vDist = FCN_V(tgMH_MAX)( vX3, FCN_V(tgMH_SET1)( TYPE_K(0) ) );
    
    return (vDist);
}


/* ---- FCN_VO(tgCO_BA_ClosestSq_PN) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_BA_ClosestSq_PN)( VEC_T(1,PC) pvBA0, VEC_T(1,PC) pvPN0, VEC_OBJ_T(TgBOXAA,CPC) psBA0, VEC_OBJ_T(TgPLANE,CPC) psPN0 )
{
    VEC_T(1,C)                          vDist = FCN_VO(tgCO_BA_Closest_PN)( pvBA0, pvPN0, psBA0, psPN0 );

    return (FCN_V(tgMH_MUL)( vDist, vDist ));
}


/* ---- FCN_VO(tgCO_BA_Closest_PN) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_BA_Closest_PN)( VEC_T(1,PC) pvBA0, VEC_T(1,PC) pvPN0, VEC_OBJ_T(TgBOXAA,CPC) psBA0, VEC_OBJ_T(TgPLANE,CPC) psPN0 )
{
    VEC_T(1,C)                          vX0 = FCN_V(tgMH_CMP_GE)( psPN0->m_vNormal, FCN_V(tgMH_SET1)( TYPE_K(0) ) );
    VEC_T(1,C)                          vX1 = FCN_V(tgMH_SEL)( psBA0->m_vMax, psBA0->m_vMin, vX0 );
    VEC_T(1,C)                          vX2 = FCN_V(tgMH_Init_Point)( vX1 );
    VEC_T(1,C)                          vX3 = FCN_V(tgMH_DOT)( vX2, psPN0->m_vPlnEqN );
    VEC_T(1,C)                          vDist = FCN_V(tgMH_MAX)( vX3, FCN_V(tgMH_SET1)( TYPE_K(0) ) );
    VEC_T(1,C)                          vX4 = FCN_V(tgMH_MUL)( vDist, psPN0->m_vNormal );

    *pvBA0 = vX2;
    *pvPN0 = FCN_V(tgMH_SUB)( vX2, vX4 );
    return (vDist);
}


/* ---- FCN_VO(tgCO_BA_Test_PN) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_VO(tgCO_BA_Test_PN)(VEC_OBJ_T(TgBOXAA,CPC) psBA0, VEC_OBJ_T(TgPLANE,CPC) psPN0)
{
    VEC_T(1,C)                          vX0 = FCN_V(tgMH_CMP_GE)( psPN0->m_vNormal, FCN_V(tgMH_SET1)( TYPE_K(0) ) );
    VEC_T(1,C)                          vX1 = FCN_V(tgMH_SEL)( psBA0->m_vMax, psBA0->m_vMin, vX0 );
    VEC_T(1,C)                          vX2 = FCN_V(tgMH_Init_Point)( vX1 );
    VEC_T(1,C)                          vX3 = FCN_V(tgMH_DOT)( vX2, psPN0->m_vPlnEqN );

    return (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vX3, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ));
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

    #define TGS_COLLISION_BOXAA_PLANE_INL

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COLLISION_BOXAA_PLANE_INL) */
#endif
