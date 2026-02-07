/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Parallelogram-Parallelogram.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
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

/* ---- FCN_VO(tgCO_PE_ClosestSq_PM_PE) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* Input:  psPE0, psPE1: Parallelogram primitives                                                                                                                                  */
/* Output: fPE0, fPE1: Parametric parameters to generate point of minimal distance on parallelogram #1                                                                             */
/* Output: tyPE2, tyPE3: Parametric parameters to generate point of minimal distance on parallelogram #2                                                                           */
/* Return: Minimal distance between the two primitives or negative type max if they intersect or are invalid.                                                                      */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
VEC_T(1) FCN_VO(tgCO_PE_ClosestSq_PM_PE)( VEC_T(1,PC) pvPE00, VEC_T(1,P) pvPE01, VEC_T(1,PC) pvPE10, VEC_T(1,PC) pvPE11, VEC_OBJ_T(TgPARALLELOGRAM,CPC) psPE0,
                                          VEC_OBJ_T(TgPARALLELOGRAM,CPC) psPE1 )
{
    VEC_T(1)                            vT_E0, vT_E1, vT_G1, vTestSq, vDistSq;
    VEC_T(1)                            vPE00, vPE01, vPE10, vPE11;

    TgPARAM_CHECK( FCN_VO(tgGM_PE_Is_Valid)(psPE0) );

    /* Compare the edges of the parallelogram against the parallelogram. */

    vDistSq = FCN_VO(tgCO_PE_ClosestSq_PM_LR11)( &vPE00, &vPE01, &vPE10, psPE0, psPE1->m_vOrigin, psPE1->m_avEdge[0] );
    vPE11 = FCN_V(tgMH_SET1)( TYPE_K(0) );

    {
        VEC_T(1,C)                          vK0 = FCN_VO(tgGM_PE_Query_Point_2)(psPE1);

        vTestSq = FCN_VO(tgCO_PE_ClosestSq_PM_LR11)( &vT_E0, &vT_E1, &vT_G1, psPE0, vK0, psPE1->m_avEdge[0] );
        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTestSq, vDistSq ) ))
        {
            vDistSq = vTestSq;
            vPE00 = vT_E0;
            vPE01 = vT_E1;
            vPE10 = vT_G1;
            vPE11 = FCN_V(tgMH_SET1)( TYPE_K(1) );
        };
    };

    vTestSq = FCN_VO(tgCO_PE_ClosestSq_PM_LR11)( &vT_E0, &vT_E1, &vT_G1, psPE0, psPE1->m_vOrigin, psPE1->m_avEdge[1] );
    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTestSq, vDistSq ) ))
    {
        vDistSq = vTestSq;
        vPE00 = vT_E0;
        vPE01 = vT_E1;
        vPE10 = FCN_V(tgMH_SET1)( TYPE_K(0) );
        vPE11 = vT_G1;
    };

    {
        VEC_T(1,C)                          vK0 = FCN_VO(tgGM_PE_Query_Point_1)(psPE1);

        vTestSq = FCN_VO(tgCO_PE_ClosestSq_PM_LR11)( &vT_E0, &vT_E1, &vT_G1, psPE0, vK0, psPE1->m_avEdge[1] );
        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTestSq, vDistSq ) ))
        {
            vDistSq = vTestSq;
            vPE00 = vT_E0;
            vPE01 = vT_E1;
            vPE10 = FCN_V(tgMH_SET1)( TYPE_K(1) );
            vPE11 = vT_G1;
        };
    };

    /* Compare the edges of the parallelogram to the parallelogram. */

    vTestSq = FCN_VO(tgCO_PE_ClosestSq_PM_LR11)( &vT_E0, &vT_E1, &vT_G1, psPE1, psPE0->m_vOrigin, psPE0->m_avEdge[0] );
    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTestSq, vDistSq ) ))
    {
        vDistSq = vTestSq;
        vPE00 = vT_G1;
        vPE01 = FCN_V(tgMH_SET1)( TYPE_K(0) );
        vPE10 = vT_E0;
        vPE11 = vT_E1;
    };

    {
        VEC_T(1,C)                          vK0 = FCN_VO(tgGM_PE_Query_Point_2)(psPE0);

        vTestSq = FCN_VO(tgCO_PE_ClosestSq_PM_LR11)( &vT_E0, &vT_E1, &vT_G1, psPE1, vK0, psPE0->m_avEdge[0] );
        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTestSq, vDistSq ) ))
        {
            vDistSq = vTestSq;
            vPE00 = vT_G1;
            vPE01 = FCN_V(tgMH_SET1)( TYPE_K(1) );
            vPE10 = vT_E0;
            vPE11 = vT_E1;
        };
    };

    vTestSq = FCN_VO(tgCO_PE_ClosestSq_PM_LR11)( &vT_E0, &vT_E1, &vT_G1, psPE1, psPE0->m_vOrigin, psPE0->m_avEdge[1] );
    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTestSq, vDistSq ) ))
    {
        vDistSq = vTestSq;
        vPE00 = FCN_V(tgMH_SET1)( TYPE_K(0) );
        vPE01 = vT_G1;
        vPE10 = vT_E0;
        vPE11 = vT_E1;
    };

    {
        VEC_T(1,C)                          vK0 = FCN_VO(tgGM_PE_Query_Point_1)(psPE0);

        vTestSq = FCN_VO(tgCO_PE_ClosestSq_PM_LR11)( &vT_E0, &vT_E1, &vT_G1, psPE1, vK0, psPE0->m_avEdge[1] );
        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTestSq, vDistSq ) ))
        {
            vDistSq = vTestSq;
            vPE00 = FCN_V(tgMH_SET1)( TYPE_K(1) );
            vPE01 = vT_G1;
            vPE10 = vT_E0;
            vPE11 = vT_E1;
        };
    };

    *pvPE00 = vPE00;
    *pvPE01 = vPE01;
    *pvPE10 = vPE10;
    *pvPE11 = vPE11;

    return (vDistSq);
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
