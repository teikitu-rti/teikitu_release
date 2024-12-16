/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Sphere-Linear.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.18 | »GUID« 5BB31923-DAF4-437F-8513-C1B5BEEA163A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_SPHERE_LINEAR_INL)
#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* == Collision ================================================================================================================================================================== */

/* ---- FCNI_VO(tgCO_SP_Clip) ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCNI_VO(tgCO_SP_Clip)( VEC_OBJ_T(STg2_CO_Clip_List,PC) psCL, VEC_OBJ_T(TgSPHERE,CPC) psSP0, VEC_T(1,C) vS0, VEC_T(1,C) vD0 )
{
    VEC_T(1)                            vN0, vN1;
    VEC_T(1)                            vT0, vT1;
    TgRESULT                            iResult;

    if (psCL->m_nuiMax < 2)
    {
        return (KTgE_FAIL);
    };

    if (TgFAILED(iResult = FCNI_VO(tgCO_SP_Intersect_PM)( &vT0, &vT1, &vN0, &vN1, psSP0, vS0, vD0 )))
    {
        psCL->m_nuiPoint = 0;
        return (iResult);
    };

    /* Limit the variable to the cap regions */

    psCL->m_avPoint[0] = FCN_V(tgMH_MAD)( vT0, vD0, vS0 );
    psCL->m_avPoint[1] = FCN_V(tgMH_MAD)( vT1, vD0, vS0 );

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

    psCL->m_nuiPoint = 2;
    return (KTgS_OK);
}


/* ---- FCNI_VO(tgCO_SP_Clip_PM) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCNI_VO(tgCO_SP_Clip_PM)( VEC_T(1,PC) pvT0, VEC_T(1,PC) pvT1, VEC_OBJ_T(TgSPHERE,CPC) psSP0, VEC_T(1,C) vS0, VEC_T(1,C) vD0 )
{
    VEC_T(1)                            vN0, vN1;
    VEC_T(1)                            vT0, vT1;
    TgRESULT                            iResult;

    if (TgFAILED(iResult = FCNI_VO(tgCO_SP_Intersect_PM)( &vT0, &vT1, &vN0, &vN1, psSP0, vS0, vD0 )))
    {
        return (iResult);
    };

    /* Limit the variable to the cap regions */

    *pvT0 = vT0;
    *pvT1 = vT1;

    if (TEMPLATE__PRIM_0_CAP_0)
    {
        VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_LT)( vT0, FCN_V(tgMH_SET1)( TYPE_K(0) ) );
        VEC_T(1,C)                          vCMP_1 = FCN_V(tgMH_CMP_LE)( vT1, FCN_V(tgMH_SET1)( TYPE_K(0) ) );

        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_0 ) && FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_1 ))
        {
            return (KTgE_NO_INTERSECT);
        };
    };

    if (TEMPLATE__PRIM_0_CAP_1)
    {
        VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_GE)( vT0, FCN_V(tgMH_SET1)( TYPE_K(1) ) );
        VEC_T(1,C)                          vCMP_1 = FCN_V(tgMH_CMP_GT)( vT1, FCN_V(tgMH_SET1)( TYPE_K(1) ) );

        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_0 ) && FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_1 ))
        {
            return (KTgE_NO_INTERSECT);
        };
    };

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

    #define TGS_COLLISION_SPHERE_LINEAR_INL


/*# !defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COLLISION_SPHERE_LINEAR_INL) */
#endif
