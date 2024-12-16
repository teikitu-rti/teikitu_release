/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Plane-Point.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_PLANE_POINT_INL)
#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* == Collision ================================================================================================================================================================== */

/* ---- FCN_VO(tgCO_PN_DistSq_PT) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_PN_DistSq_PT)( VEC_OBJ_T(TgPLANE,CPC) psPN0, VEC_T(1,C) vS0 )
{
    return (FCN_VO(tgGM_DistSq_PN_PT)( psPN0, vS0 ));
}


/* ---- FCN_VO(tgCO_PN_Dist_PT) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_PN_Dist_PT)( VEC_OBJ_T(TgPLANE,CPC) psPN0, VEC_T(1,C) vS0 )
{
    return (FCN_VO(tgGM_Dist_PN_PT)( psPN0, vS0 ));
}


/* ---- FCN_VO(tgCO_PN_ClosestSq_PT) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_PN_ClosestSq_PT)( VEC_T(1,PC) pvPN0, VEC_OBJ_T(TgPLANE,CPC) psPN0, VEC_T(1,C) vS0 )
{
    VEC_T(1,C)                          vDist = FCN_V(tgMH_DOT)( psPN0->m_vPlnEqN, vS0 );
    VEC_T(1,C)                          vT0 = FCN_V(tgMH_MUL)( vDist, psPN0->m_vNormal );

    *pvPN0 = FCN_V(tgMH_SUB)( vS0, vT0 );

    return (FCN_V(tgMH_SEL)( FCN_V(tgMH_MUL)( vDist, vDist ), FCN_V(tgMH_SET1)( -VAR_K(KTgMAX) ), FCN_V(tgMH_CMP_GE)( vDist, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ));
}


/* ---- FCN_VO(tgCO_PN_Closest_PT) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_PN_Closest_PT)( VEC_T(1,PC) pvPN0, VEC_OBJ_T(TgPLANE,CPC) psPN0, VEC_T(1,C) vS0 )
{
    VEC_T(1,C)                          vDist = FCN_V(tgMH_DOT)( psPN0->m_vPlnEqN, vS0 );
    VEC_T(1,C)                          vT0 = FCN_V(tgMH_MUL)( vDist, psPN0->m_vNormal );

    *pvPN0 = FCN_V(tgMH_SUB)( vS0, vT0 );

    return (FCN_V(tgMH_SEL)( vDist, FCN_V(tgMH_SET1)( -VAR_K(KTgMAX) ), FCN_V(tgMH_CMP_GE)( vDist, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ));
}


/* ---- FCN_VO(tgCO_PN_Sign_Dist_PT) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_PN_Sign_Dist_PT)( VEC_OBJ_T(TgPLANE,CPC) psPN0, VEC_T(1,C) vS0 )
{
    return (FCN_VO(tgGM_Sign_Dist_PN_PT)( psPN0, vS0 ));
}


/* ---- FCN_VO(tgCO_PN_Sign_Closest_PT) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_PN_Sign_Closest_PT)( VEC_T(1,PC) pvPN0, VEC_OBJ_T(TgPLANE,CPC) psPN0, VEC_T(1,C) vS0 )
{
    return (FCN_VO(tgGM_Sign_Closest_PN_PT)( pvPN0, psPN0, vS0 ));
}


/* ---- FCN_VO(tgCO_PN_Test_PT) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_VO(tgCO_PN_Test_PT)( VEC_OBJ_T(TgPLANE,CPC) psPN0, VEC_T(1,C) vS0 )
{
    return (FCN_V(tgMH_Is_PRX_CMP_EQ)( FCN_V(tgMH_DOT)( psPN0->m_vPlnEqN, vS0 ), FCN_V(tgMH_SET1)( TYPE_K(0) ) ));
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

    #define TGS_COLLISION_PLANE_POINT_INL

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COLLISION_PLANE_POINT_INL) */
#endif
