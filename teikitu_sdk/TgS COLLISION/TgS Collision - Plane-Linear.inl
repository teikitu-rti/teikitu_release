/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Plane-Linear.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_PLANE_LINEAR_INL)
#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* == Collision ================================================================================================================================================================== */

/* ---- FCNI_VO(tgCO_PN_Clip_PM) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCNI_VO(tgCO_PN_Clip_PM)( VEC_T(1,PC) pvT0, VEC_T(1,PC) pvT1, VEC_OBJ_T(TgPLANE,CPC) psPN0, VEC_T(1,C) vS0, VEC_T(1,C) vD0 )
{
    VEC_T(1,C)                          vZero = FCN_V(tgMH_SET1)( TYPE_K(0) );
    VEC_T(1,C)                          vOne = FCN_V(tgMH_SET1)( TYPE_K(1) );
    VEC_T(1,C)                          vC0 = FCN_VO(tgCO_PN_Dist_PT)( psPN0, vS0 );
    VEC_T(1,C)                          vK0 = FCN_V(tgMH_ADD)( vS0, vD0 );
    VEC_T(1,C)                          vC1 = FCN_VO(tgCO_PN_Dist_PT)( psPN0, vK0 );
    VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_GE)( vC0, vZero );
    VEC_T(1,C)                          vCMP_1 = FCN_V(tgMH_CMP_GE)( vC1, vZero );
    VEC_T(1,C)                          vX0 = FCN_V(tgMH_SUB)( vC1, vC0 );
    VEC_T(1,C)                          vX1 = FCN_V(tgMH_DIV)( vC0, vX0 );
    VEC_T(1,C)                          vX2 = FCN_V(tgMH_DIV)( vC1, vX0 );

    if (TEMPLATE__PRIM_0_CAP_0 && TEMPLATE__PRIM_0_CAP_1)
    {
        *pvT0 = FCN_V(tgMH_SEL)( vX1, vZero, vCMP_0 );
        *pvT1 = FCN_V(tgMH_SEL)( vX2, vOne, vCMP_1 );
    }
    else
    {
        VEC_T(1,C)                          vCMP_2 = FCN_V(tgMH_CMP_GE)( vC0, vC1 );
        VEC_T(1,C)                          vX3 = FCN_V(tgMH_SET1)( VAR_K(KTgMAX) );
        VEC_T(1,C)                          vX4 = FCN_V(tgMH_SEL)( vX3, vX2, vCMP_2 );

        if (TEMPLATE__PRIM_0_CAP_0 && !TEMPLATE__PRIM_0_CAP_1)
        {
            *pvT0 = FCN_V(tgMH_SEL)( vX1, vZero, vCMP_0 );
            *pvT1 = FCN_V(tgMH_SEL)( vX2, vX4, vCMP_1 );
        }
        else
        {
            VEC_T(1,C)                          vX5 = FCN_V(tgMH_SET1)( -VAR_K(KTgMAX) );
            VEC_T(1,C)                          vX6 = FCN_V(tgMH_SEL)( vX1, vX5, vCMP_2 );

            *pvT0 = FCN_V(tgMH_SEL)( vX1, vX6, vCMP_0 );
            *pvT1 = FCN_V(tgMH_SEL)( vX2, vX4, vCMP_1 );
        };
    };

    return (FCN_V(tgMH_CMP_ALL_TO_BOOL)(vCMP_0) || FCN_V(tgMH_CMP_ALL_TO_BOOL)(vCMP_1));
}


/* ---- FCNI_VO(tgCO_PN_Clip) ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCNI_VO(tgCO_PN_Clip)( VEC_OBJ_T(STg2_CO_Clip_List,PC) psCL, VEC_OBJ_T(TgPLANE,CPC) psPN0, VEC_T(1,C) vS0, VEC_T(1,C) vD0 )
{
    VEC_T(1)                            vT0, vT1;

    VEC_T(1,C)                          vZero = FCN_V(tgMH_SET1)( TYPE_K(0) );
    VEC_T(1,C)                          vOne = FCN_V(tgMH_SET1)( TYPE_K(0) );

    if (psCL->m_nuiMax < 2)
    {
        return (KTgE_FAIL);
    };

    if (TgFAILED(FCNI_VO(tgCO_PN_Clip_PM)( &vT0, &vT1, psPN0, vS0, vD0 )))
    {
        psCL->m_nuiPoint = 0;
        return (KTgE_NO_INTERSECT);
    };

    if (TEMPLATE__PRIM_0_CAP_0)
    {
        VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_LT)( vT0, vZero );
        VEC_T(1,C)                          vCMP_1 = FCN_V(tgMH_CMP_LE)( vT1, vZero );
        
        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_0 ) && FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_1 ))
        {
            psCL->m_nuiPoint = 0;
            return (KTgE_NO_INTERSECT);
        };
    };

    if (TEMPLATE__PRIM_0_CAP_1)
    {
        VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_GT)( vT0, vOne );
        VEC_T(1,C)                          vCMP_1 = FCN_V(tgMH_CMP_GE)( vT1, vOne );
        
        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_0 ) && FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_1 ))
        {
            psCL->m_nuiPoint = 0;
            return (KTgE_NO_INTERSECT);
        };
    };

    {
        VEC_T(1,C)                          vK0 = FCN_V(tgMH_MUL)( vT0, vD0 );
        VEC_T(1,C)                          vK1 = FCN_V(tgMH_MUL)( vT1, vD0 );

        psCL->m_avPoint[0] = FCN_V(tgMH_ADD)( vS0, vK0 );
        psCL->m_avPoint[1] = FCN_V(tgMH_ADD)( vS0, vK1 );

        psCL->m_nuiPoint = 2;
        return (KTgS_OK);
    }
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

    #define TGS_COLLISION_PLANE_LINEAR_INL


/*# !defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COLLISION_PLANE_LINEAR_INL) */
#endif
