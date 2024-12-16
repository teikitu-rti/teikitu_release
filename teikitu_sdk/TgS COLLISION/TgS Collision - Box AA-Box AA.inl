/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Box AA-Box AA.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.18 | »GUID« 5BB31923-DAF4-437F-8513-C1B5BEEA163A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_BOXAA_BOXAA_INL)
#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* == Collision ================================================================================================================================================================== */

/* ---- FCN_VO(tgCO_BA_DistSq_BA) ---------------------------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_BA_DistSq_BA)( VEC_OBJ_T(TgBOXAA,CPC) psBA0, VEC_OBJ_T(TgBOXAA,CPC) psBA1 )
{
    VEC_T(1,C)                          vX0 = FCN_V(tgMH_MAX)( psBA0->m_vMin, psBA1->m_vMin );
    VEC_T(1,C)                          vX1 = FCN_V(tgMH_MIN)( psBA0->m_vMax, psBA1->m_vMax );
    VEC_T(1,C)                          vX2 = FCN_V(tgMH_SUB)( vX0, vX1 );
    VEC_T(1,C)                          vX3 = FCN_V(tgMH_MAX)( FCN_V(tgMH_SET1)( TYPE_K(0) ), vX2 );
    VEC_T(1,C)                          vDistSq = FCN_V(tgMH_LSQ)( vX3 );

    return (vDistSq);
}


/* ---- FCN_VO(tgCO_BA_Dist_BA) -----------------------------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_BA_Dist_BA)( VEC_OBJ_T(TgBOXAA,CPC) psBA0, VEC_OBJ_T(TgBOXAA,CPC) psBA1 )
{
    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_BA_DistSq_BA)( psBA0, psBA1 ) ));
}


/* ---- FCN_VO(tgCO_BA_Closest_BA) --------------------------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_BA_Closest_BA)( VEC_T(1,PC) pvBA0, VEC_T(1,PC) pvBA1, VEC_OBJ_T(TgBOXAA,CPC) psBA0, VEC_OBJ_T(TgBOXAA,CPC) psBA1 )
{
    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_BA_ClosestSq_BA)( pvBA0, pvBA1, psBA0, psBA1 ) ));
}


/* ---- FCN_VO(tgCO_BA_Sweep_Test_BA) -----------------------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_VO(tgCO_BA_Sweep_Test_BA)( VEC_OBJ_T(TgBOXAA,CPC) psBA0, VEC_OBJ_T(TgBOXAA,CPC) psBA1, VEC_T(1,C) vUDT, VEC_T(1,C) vMag_DT )
{
    VEC_T(1,C)                          vDT = FCN_V(tgMH_MUL)( vUDT, vMag_DT );
    VEC_T(1,C)                          vX0 = FCN_V(tgMH_ADD)( psBA1->m_vMin, vDT );
    VEC_T(1,C)                          vMin = FCN_V(tgMH_MIN)( vX0, psBA1->m_vMin );
    VEC_T(1,C)                          vX1 = FCN_V(tgMH_ADD)( psBA1->m_vMax, vDT );
    VEC_T(1,C)                          vMax = FCN_V(tgMH_MAX)( vX1, psBA1->m_vMax );

    TgBOOL_C        bFlag_0 = FCN_V(tgMH_Is_Contained_In_Interval)( vMin, psBA0->m_vMin, psBA0->m_vMax );
    TgBOOL_C        bFlag_1 = FCN_V(tgMH_Is_Contained_In_Interval)( vMax, psBA0->m_vMin, psBA0->m_vMax );
    TgBOOL_C        bFlag_2 = FCN_V(tgMH_Is_Contained_In_Interval)( psBA0->m_vMin, vMin, vMax );
    TgBOOL_C        bFlag_3 = FCN_V(tgMH_Is_Contained_In_Interval)( psBA0->m_vMax, vMin, vMax );

    return (bFlag_0 && bFlag_1 && bFlag_2 && bFlag_3);
}


/* ---- FCN_VO(tgCO_BA_Test_BA) -----------------------------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_VO(tgCO_BA_Test_BA)( VEC_OBJ_T(TgBOXAA,CPC) psBA0, VEC_OBJ_T(TgBOXAA,CPC) psBA1 )
{
    return (FCN_VO(tgCO_BA_Test_Elem_BA)( psBA0->m_vMin, psBA0->m_vMax, psBA1->m_vMin, psBA1->m_vMax ));
}


/* ---- FCN_VO(tgCO_BA_Test_Elem_BA) ------------------------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_VO(tgCO_BA_Test_Elem_BA)( VEC_T(1,C) vMin_BA0, VEC_T(1,C) vMax_BA0, VEC_T(1,C) vMin_BA1, VEC_T(1,C) vMax_BA1 )
{
    VEC_T(1,C)                          vX0 = FCN_V(tgMH_MAX)( vMin_BA0, vMin_BA1 );
    VEC_T(1,C)                          vX1 = FCN_V(tgMH_MIN)( vMax_BA0, vMax_BA1 );
    VEC_T(1,C)                          vX2 = FCN_V(tgMH_SUB)( vX0, vX1 );
    VEC_T(1,C)                          vCMP = FCN_V(tgMH_CMP_GT)( vX2, FCN_V(tgMH_SET1)( TYPE_K(0) ) );

    /* Greater than test is used to avoid a false positive due to the w value */
    return (!FCN_V(tgMH_CMP_ANY_TO_BOOL)( vCMP ));
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

    #define TGS_COLLISION_BOXAA_BOXAA_INL

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COLLISION_BOXAA_BOXAA_INL) */
#endif
