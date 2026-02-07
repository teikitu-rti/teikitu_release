/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Rectangle-Linear.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.18 | »GUID« 5BB31923-DAF4-437F-8513-C1B5BEEA163A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_RECTANGLE_LINEAR_INL)
#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* == Collision ================================================================================================================================================================== */

/* ---- FCNI_VO(tgCO_RT_Clip) ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCNI_VO(tgCO_RT_Clip)( VEC_OBJ_T(STg2_CO_Clip_List,PC) psCL, VEC_OBJ_T(TgRECTANGLE,CPC) psRT0, VEC_T(1,C) vS0, VEC_T(1,C) vD0 )
{
    VEC_T(1)                            vT0, vT1;

    if (psCL->m_nuiMax < 2)
    {
        return (KTgE_FAIL);
    };

    if (TgFAILED(FCNI_VO(tgCO_RT_Clip_PM)( &vT0, &vT1, psRT0, vS0, vD0 )))
    {
        psCL->m_nuiPoint = 0;
        return (KTgE_NO_INTERSECT);
    };

    if (TEMPLATE__PRIM_0_CAP_0)
    {
        VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_LT)( vT0, FCN_V(tgMH_SET1)( TYPE_K(0) ) );
        VEC_T(1,C)                          vCMP_1 = FCN_V(tgMH_CMP_LE)( vT1, FCN_V(tgMH_SET1)( TYPE_K(0) ) );

        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_0 ) && FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_1 ))
        {
            psCL->m_nuiPoint = 0;
            return (KTgE_NO_INTERSECT);
        };
    };

    if (TEMPLATE__PRIM_0_CAP_1)
    {
        VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_GE)( vT0, FCN_V(tgMH_SET1)( TYPE_K(1) ) );
        VEC_T(1,C)                          vCMP_1 = FCN_V(tgMH_CMP_GT)( vT1, FCN_V(tgMH_SET1)( TYPE_K(1) ) );

        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_0 ) && FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_1 ))
        {
            psCL->m_nuiPoint = 0;
            return (KTgE_NO_INTERSECT);
        };
    };

    psCL->m_avPoint[0] = FCN_V(tgMH_MAD)( vT0, vD0, vS0 );
    psCL->m_avPoint[1] = FCN_V(tgMH_MAD)( vT1, vD0, vS0 );

    psCL->m_nuiPoint = 2;
    return (KTgS_OK);
}


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"


/* =============================================================================================================================================================================== */

/*# !defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#else

    #define TEMPLATE_TYPE_EXPANSION__RELOAD

    #if TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE
        #define TEMPLATE__PRIM_0_CAP_0 0
        #define TEMPLATE__PRIM_0_CAP_1 0
        #define TEMPLATE__PRIM_0 LR
        #define TEMPLATE__VECTOR_DIM 4
        #define TEMPLATE__TYPE_SIZE 64
        #include __FILE__
    #endif

    #define TEMPLATE__PRIM_0_CAP_0 0
    #define TEMPLATE__PRIM_0_CAP_1 0
    #define TEMPLATE__PRIM_0 LR
    #define TEMPLATE__VECTOR_DIM 4
    #define TEMPLATE__TYPE_SIZE 32
    #include __FILE__

    #if TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE
        #define TEMPLATE__PRIM_0_CAP_0 1
        #define TEMPLATE__PRIM_0_CAP_1 0
        #define TEMPLATE__PRIM_0 LR
        #define TEMPLATE__VECTOR_DIM 4
        #define TEMPLATE__TYPE_SIZE 64
        #include __FILE__
    #endif

    #define TEMPLATE__PRIM_0_CAP_0 1
    #define TEMPLATE__PRIM_0_CAP_1 0
    #define TEMPLATE__PRIM_0 LR
    #define TEMPLATE__VECTOR_DIM 4
    #define TEMPLATE__TYPE_SIZE 32
    #include __FILE__

    #if TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE
        #define TEMPLATE__PRIM_0_CAP_0 1
        #define TEMPLATE__PRIM_0_CAP_1 1
        #define TEMPLATE__PRIM_0 LR
        #define TEMPLATE__VECTOR_DIM 4
        #define TEMPLATE__TYPE_SIZE 64
        #include __FILE__
    #endif

    #define TEMPLATE__PRIM_0_CAP_0 1
    #define TEMPLATE__PRIM_0_CAP_1 1
    #define TEMPLATE__PRIM_0 LR
    #define TEMPLATE__VECTOR_DIM 4
    #define TEMPLATE__TYPE_SIZE 32
    #include __FILE__

    #undef TEMPLATE_TYPE_EXPANSION__RELOAD

    #define TGS_COLLISION_BOX_LINEAR_INL


/*# !defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COLLISION_RECTANGLE_LINEAR_INL) */
#endif
