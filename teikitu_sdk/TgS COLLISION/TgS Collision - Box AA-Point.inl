/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Box AA-Point.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.18 | »GUID« 5BB31923-DAF4-437F-8513-C1B5BEEA163A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_BOXAA_POINT_INL)
#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* == Collision ================================================================================================================================================================== */

/* ---- FCN_VO(tgCO_BA_DistSq_PT) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_BA_DistSq_PT)( VEC_OBJ_T(TgBOXAA,CPC) psBA0, VEC_T(1,C) vS0 )
{
    VEC_T(1)                            vBA0;

    return (FCN_VO(tgCO_BA_ClosestSq_PT)( &vBA0, psBA0, vS0 ));
}


/* ---- FCN_VO(tgCO_BA_Dist_PT) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_BA_Dist_PT)( VEC_OBJ_T(TgBOXAA,CPC) psBA0, VEC_T(1,C) vS0 )
{
    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_BA_DistSq_PT)( psBA0, vS0 ) ));
}


/* ---- FCN_VO(tgCO_BA_ClosestSq_PT) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_BA_ClosestSq_PT)( VEC_T(1,PC) pvBA0, VEC_OBJ_T(TgBOXAA,CPC) psBA0, VEC_T(1,C) vS0 )
{
    VEC_T(1,C)                          vBA0_Min = FCN_VO(tgGM_BA_Query_Min)( psBA0 );
    VEC_T(1,C)                          vBA0_Max = FCN_VO(tgGM_BA_Query_Max)( psBA0 );

    VEC_T(1,C)                          vP1 = FCN_V(tgMH_CLP)( vS0, vBA0_Min, vBA0_Max );
    VEC_T(1,C)                          vX0 = FCN_V(tgMH_SUB)( vP1, vS0 );
    VEC_T(1,C)                          vRet = FCN_V(tgMH_LSQ)( vX0 );

    *pvBA0 = vP1;
    return (vRet);
}


/* ---- FCN_VO(tgCO_BA_Closest_PT) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_BA_Closest_PT)( VEC_T(1,PC) pvBA0, VEC_OBJ_T(TgBOXAA,CPC) psBA0, VEC_T(1,C) vS0 )
{
    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_BA_ClosestSq_PT)( pvBA0, psBA0, vS0 ) ));
}


/* ---- FCN_VO(tgCO_BA_Test_PT) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_VO(tgCO_BA_Test_PT)( VEC_OBJ_T(TgBOXAA,CPC) psBA0, VEC_T(1,C) vS0 )
{
    return (FCN_V(tgMH_Is_Contained_In_Interval)( FCN_V(tgMH_Init_Vector)( vS0 ), psBA0->m_vMin, psBA0->m_vMax ));
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

    #define TGS_COLLISION_BOXAA_POINT_INL

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COLLISION_BOXAA_POINT_INL) */
#endif
