/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Parallelogram-Point.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "TgS COLLISION/TgS Collision - Segment.inl"

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

/* ---- FCN_VO(tgCO_PE_ClosestSq_PM_PT) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* Input:  psPE0: Parallelogram primitive                                                                                                                                          */
/* Input:  pvS0: Point                                                                                                                                                             */
/* Output: _tyPE0, _tyPE1: Parametric parameters to generate point of minimal distance on the parallelogram                                                                        */
/* Return: Minimal distance between the two primitives or negative type max if they intersect or are invalid.                                                                      */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
VEC_T(1) FCN_VO(tgCO_PE_ClosestSq_PM_PT)( VEC_T(1,PC) pvPE0, VEC_T(1,PC) pvPE1, VEC_OBJ_T(TgPARALLELOGRAM,CPC) psPE0, VEC_T(1,C) vS0 )
{
    VEC_T(1,C)                          vPOS_EPS = FCN_V(tgMH_SET1)( VAR_K(KTgEPS) );
    VEC_T(1,C)                          vKL_0 = FCN_V(tgMH_SET1)( TYPE_K(0) );

    VEC_T(1,C)                          vDS = FCN_V(tgMH_SUB)( vS0, psPE0->m_vOrigin) ;
    VEC_T(1,C)                          vDS_DS = FCN_V(tgMH_LSQ)( vDS );
    VEC_T(1,C)                          vE1_EN0 = FCN_V(tgMH_DOT)( psPE0->m_avEdge_Normal[0], psPE0->m_avEdge[1] );
    VEC_T(1,C)                          vE0_EN1 = FCN_V(tgMH_DOT)( psPE0->m_avEdge_Normal[1], psPE0->m_avEdge[0] );

    VEC_T(1)                            vDistSq;

    TgPARAM_CHECK( FCN_VO(tgGM_PE_Is_Valid)(psPE0) && FCN_V(tgMH_Is_Valid_Point)(vS0) );

    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( vDS_DS, vPOS_EPS ) ))
    {
        /* Quick Out - the point is within tolerance of rectangle origin. */
        *pvPE0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
        *pvPE1 = FCN_V(tgMH_SET1)( TYPE_K(0) );
        vDistSq = FCN_V(tgMH_SET1)( TYPE_K(0) );
        return (vDistSq);
    };

    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( vE1_EN0, vPOS_EPS ) ) || FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( vE0_EN1, vPOS_EPS ) ))
    {
        /* Degenerate parallelogram - One or both of the edges has a near-zero length */
        vDistSq = FCN_V(tgMH_SET1)( -VAR_K(KTgMAX) );
        return (vDistSq);
    }
    else
    {
        VEC_T(1,C)                          v00 = FCN_V(tgMH_DOT)( vDS, psPE0->m_avEdge_Normal[0] );
        VEC_T(1,C)                          v01 = FCN_V(tgMH_DOT)( vDS, psPE0->m_avEdge_Normal[1] );
        VEC_T(1,C)                          v02 = FCN_V(tgMH_SUB)( vE1_EN0, v00 );
        VEC_T(1,C)                          v03 = FCN_V(tgMH_SUB)( vE0_EN1, v01 );

        VEC_T(1,C)                          vDS_N = FCN_V(tgMH_DOT)( vDS, psPE0->m_vNormal );

        VEC_T(1)                            vPE0, vPE1, vT0, vTestSq;

        vPE0 = vPE1 = vDistSq = FCN_V(tgMH_SET1)( VAR_K(KTgMAX) );

        if (   FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( v00, vKL_0 ) )
            || FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( v01, vKL_0 ) )
            || FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( v02, vKL_0 ) )
            || FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( v03, vKL_0 ) ))
        {
            *pvPE0 = FCN_V(tgMH_DIV)( v01, vE0_EN1 );
            *pvPE1 = FCN_V(tgMH_DIV)( v00, vE1_EN0 );
            vDistSq = FCN_V(tgMH_MUL)( vDS_N, vDS_N );
            return (vDistSq);
        };

        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( v00, vPOS_EPS ) ))
        {
            vTestSq = FCN_VO(tgCO_LR11_ClosestSq_PM_PT)( &vT0, psPE0->m_vOrigin, psPE0->m_avEdge[0], vS0 );

            if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTestSq, vDistSq ) ))
            {
                vDistSq = vTestSq;
                vPE0 = vT0;
                vPE1 = FCN_V(tgMH_SET1)( TYPE_K(0) );
            };
        };

        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( v01, vPOS_EPS ) ))
        {
            vTestSq = FCN_VO(tgCO_LR11_ClosestSq_PM_PT)( &vT0, psPE0->m_vOrigin, psPE0->m_avEdge[1], vS0 );

            if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTestSq, vDistSq ) ))
            {
                vDistSq = vTestSq;
                vPE0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
                vPE1 = vT0;
            };
        };

        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( v02, vPOS_EPS ) ))
        {
            VEC_T(1,C)                          vK0 = FCN_VO(tgGM_PE_Query_Point_2)(psPE0);

            vTestSq = FCN_VO(tgCO_LR11_ClosestSq_PM_PT)( &vT0, vK0, psPE0->m_avEdge[0], vS0 );

            if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTestSq, vDistSq ) ))
            {
                vDistSq = vTestSq;
                vPE0 = vT0;
                vPE1 = FCN_V(tgMH_SET1)( TYPE_K(1) );
            };
        };

        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( v03, vPOS_EPS ) ))
        {
            VEC_T(1,C)                          vK0 = FCN_VO(tgGM_PE_Query_Point_1)(psPE0);

            vTestSq = FCN_VO(tgCO_LR11_ClosestSq_PM_PT)( &vT0, vK0, psPE0->m_avEdge[1], vS0 );

            if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTestSq, vDistSq ) ))
            {
                vDistSq = vTestSq;
                vPE0 = FCN_V(tgMH_SET1)( TYPE_K(1) );
                vPE1 = vT0;
            };
        };

        *pvPE0 = vPE0;
        *pvPE1 = vPE1;

        return (vDistSq);
    };
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
