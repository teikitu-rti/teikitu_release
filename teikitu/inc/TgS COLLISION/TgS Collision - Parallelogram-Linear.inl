/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Parallelogram-Linear.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_PARALLELOGRAM_LINEAR_INL)
#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* == Collision ================================================================================================================================================================== */

/* ---- FCNI_VO(tgCO_PE_Test) ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCNI_VO(tgCO_PE_Test)( VEC_OBJ_T(TgPARALLELOGRAM,CPC) psPE0, VEC_T(1,C) vS0, VEC_T(1,C) vD0 )
{
    VEC_T(1,C)                          vK0 = FCN_V(tgMH_SUB)( vS0, psPE0->m_vOrigin );
    VEC_T(1,C)                          vDist = FCN_V(tgMH_DOT)( psPE0->m_vNormal, vK0 );
    VEC_T(1,C)                          vD1_N = FCN_V(tgMH_DOT)( psPE0->m_vNormal, vD0 );
#if TEMPLATE__PRIM_0_CAP_0
    VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_GT)( vDist, FCN_V(tgMH_SET1)( TYPE_K(0) ) );
    VEC_T(1,C)                          vCMP_1 = FCN_V(tgMH_CMP_GT)( vD1_N, FCN_V(tgMH_SET1)( TYPE_K(0) ) );
    VEC_T(1,C)                          vCMP_2 = FCN_V(tgMH_XOR)( vCMP_0, vCMP_1 );
#endif
#if TEMPLATE__PRIM_0_CAP_1
    VEC_T(1,C)                          vCMP_3 = FCN_V(tgMH_CMP_GT)( FCN_V(tgMH_ABS)( vDist ), FCN_V(tgMH_ABS)( vD1_N ) );
#endif

    TgPARAM_CHECK( FCN_VO(tgGM_PE_Is_Valid)( psPE0 ) && FCN_V(tgMH_Is_Valid_Point)( vS0 ) && FCN_V(tgMH_Is_Valid_Vector)( vD0 ) );

    if (FCN_V(tgMH_Is_NR0)( vD1_N ))
    {
        return (false);
    };

#if TEMPLATE__PRIM_0_CAP_0
    if (TEMPLATE__PRIM_0_CAP_0 && !(FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_2 )))
    {
        return (false);
    };
#endif

#if TEMPLATE__PRIM_0_CAP_1
    if (TEMPLATE__PRIM_0_CAP_1 && !(FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_3 )))
    {
        return (false);
    };
#endif

    {
        VEC_T(1,C)                          vK1 = FCN_V(tgMH_MUL)( FCN_V(tgMH_DIV)( FCN_V(tgMH_NEG)( vDist ), vD1_N ), vD0 );
        VEC_T(1,C)                          vK2 = FCN_V(tgMH_ADD)( vS0, vK1 );

        return (FCN_VO(tgGM_PE_Is_Contained)( psPE0, vK2 ));
    }
}


/* ---- FCNI_VO(tgCO_PE_Clip) ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCNI_VO(tgCO_PE_Clip)( VEC_OBJ_T(STg2_CO_Clip_List,PC) psCL, VEC_OBJ_T(TgPARALLELOGRAM,CPC) psPE0, VEC_T(1,C) vS0, VEC_T(1,C) vD0 )
{
    VEC_T(1)                            vT0, vT1;

    if (psCL->m_nuiMax < 2)
    {
        return (KTgE_FAIL);
    };

    if (TgFAILED(FCNI_VO(tgCO_PE_Clip_PM)( &vT0, &vT1, psPE0, vS0, vD0 )))
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

    #define TGS_COLLISION_PARALLELOGRAM_LINEAR_INL


/*# !defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COLLISION_PARALLELOGRAM_LINEAR_INL) */
#endif
