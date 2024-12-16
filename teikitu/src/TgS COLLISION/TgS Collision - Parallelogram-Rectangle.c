/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Parallelogram-Rectangle.c_inc
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#if !defined (ENABLE_RELOAD_GUARD)
    #define TEMPLATE__VECTOR_DIM 4
    #define ENABLE_RELOAD_GUARD
    #if !defined(TEMPLATE__TYPE_SIZE)
        #if TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE
            #define TEMPLATE__TYPE_SIZE 64
            #include __FILE__
            #undef TEMPLATE__TYPE_SIZE
        #endif
        #define TEMPLATE__TYPE_SIZE 32
    #endif
    #undef ENABLE_RELOAD_GUARD
#endif

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"


/* == Collision ================================================================================================================================================================== */

/* ---- FCN_VO(tgCO_PE_ClosestSq_PM_RT) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
VEC_T(1) FCN_VO(tgCO_PE_ClosestSq_PM_RT)( VEC_T(1,PC) pvPE0, VEC_T(1,PC) pvPE1, VEC_T(1,PC) pvRT0, VEC_T(1,PC) pvRT1, VEC_OBJ_T(TgPARALLELOGRAM,CPC) psPE0,
                                          VEC_OBJ_T(TgRECTANGLE,CPC) psRT0 )
{
    VEC_T(1)                            vT_E0, vT_E1, vT_G1, vTestSq, vDistSq;
    VEC_T(1)                            vPE00, vPE01, vRT10, vRT11;

    TgPARAM_CHECK( FCN_VO(tgGM_PE_Is_Valid)(psPE0) );

    /* Compare the edges of the parallelogram against the parallelogram. */

    vDistSq = FCN_VO(tgCO_PE_ClosestSq_PM_LR11)( &vPE00, &vPE01, &vRT10, psPE0, psRT0->m_vOrigin, psRT0->m_avEdge[0] );
    vRT11 = FCN_V(tgMH_SET1)( TYPE_K(0) );

    {
        VEC_T(1,C)                          vK0 = FCN_VO(tgGM_RT_Query_Point_2)(psRT0);

        vTestSq = FCN_VO(tgCO_PE_ClosestSq_PM_LR11)( &vT_E0, &vT_E1, &vT_G1, psPE0, vK0, psRT0->m_avEdge[0] );
        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTestSq, vDistSq ) ))
        {
            vDistSq = vTestSq;
            vPE00 = vT_E0;
            vPE01 = vT_E1;
            vRT10 = vT_G1;
            vRT11 = FCN_V(tgMH_SET1)( TYPE_K(1) );
        };
    };

    vTestSq = FCN_VO(tgCO_PE_ClosestSq_PM_LR11)( &vT_E0, &vT_E1, &vT_G1, psPE0, psRT0->m_vOrigin, psRT0->m_avEdge[1] );
    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTestSq, vDistSq ) ))
    {
        vDistSq = vTestSq;
        vPE00 = vT_E0;
        vPE01 = vT_E1;
        vRT10 = FCN_V(tgMH_SET1)( TYPE_K(0) );
        vRT11 = vT_G1;
    };

    {
        VEC_T(1,C)                          vK0 = FCN_VO(tgGM_RT_Query_Point_1)(psRT0);

        vTestSq = FCN_VO(tgCO_PE_ClosestSq_PM_LR11)( &vT_E0, &vT_E1, &vT_G1, psPE0, vK0, psRT0->m_avEdge[1] );
        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTestSq, vDistSq ) ))
        {
            vDistSq = vTestSq;
            vPE00 = vT_E0;
            vPE01 = vT_E1;
            vRT10 = FCN_V(tgMH_SET1)( TYPE_K(1) );
            vRT11 = vT_G1;
        };
    };

    /* Compare the edges of the parallelogram to the parallelogram. */

    vTestSq = FCN_VO(tgCO_RT_ClosestSq_PM_LR11)( &vT_E0, &vT_E1, &vT_G1, psRT0, psPE0->m_vOrigin, psPE0->m_avEdge[0] );
    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTestSq, vDistSq ) ))
    {
        vDistSq = vTestSq;
        vPE00 = vT_G1;
        vPE01 = FCN_V(tgMH_SET1)( TYPE_K(0) );
        vRT10 = vT_E0;
        vRT11 = vT_E1;
    };

    {
        VEC_T(1,C)                          vK0 = FCN_VO(tgGM_PE_Query_Point_2)(psPE0);

        vTestSq = FCN_VO(tgCO_RT_ClosestSq_PM_LR11)( &vT_E0, &vT_E1, &vT_G1, psRT0, vK0, psPE0->m_avEdge[0] );
        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTestSq, vDistSq ) ))
        {
            vDistSq = vTestSq;
            vPE00 = vT_G1;
            vPE01 = FCN_V(tgMH_SET1)( TYPE_K(1) );
            vRT10 = vT_E0;
            vRT11 = vT_E1;
        };
    };

    vTestSq = FCN_VO(tgCO_RT_ClosestSq_PM_LR11)( &vT_E0, &vT_E1, &vT_G1, psRT0, psPE0->m_vOrigin, psPE0->m_avEdge[1] );
    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTestSq, vDistSq ) ))
    {
        vDistSq = vTestSq;
        vPE00 = FCN_V(tgMH_SET1)( TYPE_K(0) );
        vPE01 = vT_G1;
        vRT10 = vT_E0;
        vRT11 = vT_E1;
    };

    {
        VEC_T(1,C)                          vK0 = FCN_VO(tgGM_PE_Query_Point_1)(psPE0);

        vTestSq = FCN_VO(tgCO_RT_ClosestSq_PM_LR11)( &vT_E0, &vT_E1, &vT_G1, psRT0, vK0, psPE0->m_avEdge[1] );
        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTestSq, vDistSq ) ))
        {
            vDistSq = vTestSq;
            vPE00 = FCN_V(tgMH_SET1)( TYPE_K(1) );
            vPE01 = vT_G1;
            vRT10 = vT_E0;
            vRT11 = vT_E1;
        };
    };

    *pvPE0 = vPE00;
    *pvPE1 = vPE01;
    *pvRT0 = vRT10;
    *pvRT1 = vRT11;

    return (vDistSq);
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
