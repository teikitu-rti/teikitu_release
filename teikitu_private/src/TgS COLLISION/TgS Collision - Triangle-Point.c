/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Triangle-Point.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
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

/* ---- FCN_VO(tgCO_ET_ClosestSq_PM_PT) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
VEC_T(1) FCN_VO(tgCO_ET_ClosestSq_PM_PT)( VEC_T(1,P) pvET0, VEC_T(1,P) pvET1, VEC_OBJ_T(TgETRI,CPC) psET0, VEC_T(1,C) vS0 )
{
    VEC_T(1,C)      vX0 = FCN_V(tgMH_SUB)( vS0, psET0->m_sPT.m_avPoint[0] );
    VEC_T(1,C)      vX0_X0 = FCN_V(tgMH_LSQ)( vX0 );

    TgERROR( FCN_VO(tgGM_ET_Is_Valid)(psET0) && FCN_V(tgMH_Is_Valid_Point)( vS0 ) );

    if (FCN_V(tgMH_Is_NR0)( vX0_X0 ))
    {
        /* Quick Out - the point is within tolerance of triangle origin. */

        *pvET0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
        *pvET1 = FCN_V(tgMH_SET1)( TYPE_K(0) );

        return (vX0_X0);
    }
    else
    {
        VEC_T(1,C)                          vE0_E0 = FCN_V(tgMH_LSQ)(psET0->m_avEdge[0]);
        VEC_T(1,C)                          vE2_E2 = FCN_V(tgMH_LSQ)(psET0->m_avEdge[2]);
        VEC_T(1,C)                          vX1 = FCN_V(tgMH_DOT)( psET0->m_avEdge[0], psET0->m_avEdge[2] );
        VEC_T(1,C)                          vE0_E2 = FCN_V(tgMH_NEG)( vX1 );
        VEC_T(1,C)                          vX2 = FCN_V(tgMH_MUL)( vE0_E2, vE0_E2 );
        VEC_T(1,C)                          vX3 = FCN_V(tgMH_MUL)( vE0_E0, vE2_E2 );
        VEC_T(1,C)                          vX4 = FCN_V(tgMH_SUB)( vX3, vX2 );
        VEC_T(1,C)                          vDet = FCN_V(tgMH_ABS)( vX4 );

        if (FCN_V(tgMH_Is_NR0)( vE0_E0 ) || FCN_V(tgMH_Is_NR0)( vE2_E2 ))
        {   /* Degenerate triangle - One or both of the edges has a near-zero length */
            return (FCN_V(tgMH_SET1)( -VAR_K(KTgMAX) ));
        };

        if (FCN_V(tgMH_Is_NR0)( vDet ))
        {   /* Degenerate triangle - Edges are co-linear (zero-area triangle) */
            return (FCN_V(tgMH_SET1)( -VAR_K(KTgMAX) ));
        }
        else
        {
            VEC_T(1,C)                          vX0_E0 = FCN_V(tgMH_DOT)( psET0->m_avEdge[0], vX0 );
            VEC_T(1,C)                          vX5 = FCN_V(tgMH_DOT)( psET0->m_avEdge[2], vX0 );
            VEC_T(1,C)                          vX0_E2 = FCN_V(tgMH_NEG)( vX5 );
            VEC_T(1,C)                          vX6 = FCN_V(tgMH_MUL)( vE2_E2, vX0_E0 );
            VEC_T(1,C)                          vX7 = FCN_V(tgMH_MUL)( vE0_E2, vX0_E2 );
            VEC_T(1,C)                          vPM0 = FCN_V(tgMH_SUB)( vX6, vX7 );
            VEC_T(1,C)                          vX8 = FCN_V(tgMH_MUL)( vE0_E0, vX0_E2 );
            VEC_T(1,C)                          vX9 = FCN_V(tgMH_MUL)( vE0_E2, vX0_E0 );
            VEC_T(1,C)                          vPM1 = FCN_V(tgMH_SUB)( vX8, vX9 );

            VEC_T(1)                            vET0, vET1;

            /* Categorize the point according to how its contained by the edges, and the sum of the edges. */

            if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( FCN_V(tgMH_ADD)( vPM0, vPM1 ), vDet ) ))
            {
                VEC_T(1,C)                          vK0 = FCN_V(tgMH_DIV)( vX0_E2, vE2_E2 );
                VEC_T(1,C)                          vK1 = FCN_V(tgMH_SAT)( vK0 );
                VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_GE)( vPM0, FCN_V(tgMH_SET1)( TYPE_K(0) ) );

                if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GE)( vPM1, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ))
                {
                    VEC_T(1,C)                          vK2 = FCN_V(tgMH_DIV)( vPM0, vDet );
                    VEC_T(1,C)                          vK3 = FCN_V(tgMH_DIV)( vPM1, vDet );

                    vET0 = FCN_V(tgMH_SEL)( FCN_V(tgMH_SET1)( TYPE_K(0) ), vK2, vCMP_0 );
                    vET1 = FCN_V(tgMH_SEL)( vK1, vK3, vCMP_0 );
                }
                else
                {
                    VEC_T(1,C)                          vCMP_1 = FCN_V(tgMH_CMP_GT)( vX0_E0, FCN_V(tgMH_SET1)( TYPE_K(0) ) );
                    VEC_T(1,C)                          vCMP_2 = FCN_V(tgMH_OR)( vCMP_0, vCMP_1 );

                    vET0 = FCN_V(tgMH_SAT)( FCN_V(tgMH_DIV)( vX0_E0, vE0_E0 ) );
                    vET1 = FCN_V(tgMH_SEL)( vK1, FCN_V(tgMH_SET1)( TYPE_K(0) ), vCMP_2 );
                };
            }
            else
            {
                VEC_T(1,C)                          vK0 = FCN_V(tgMH_SUB)( vS0, psET0->m_sPT.m_avPoint[1] );
                VEC_T(1,C)                          vK1 = FCN_V(tgMH_SUB)( psET0->m_sPT.m_avPoint[2], vS0 );

                VEC_T(1,C)                          vE1_K0 = FCN_V(tgMH_DOT)( psET0->m_avEdge[1], vK0 );
                VEC_T(1,C)                          vE1_K1 = FCN_V(tgMH_DOT)( psET0->m_avEdge[1], vK1 );
                VEC_T(1,C)                          vE1_E1 = FCN_V(tgMH_LSQ)( psET0->m_avEdge[1] );

                if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GE)( vPM1, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ))
                {
                    VEC_T(1,C)                          vK2 = FCN_V(tgMH_DIV)( vX0_E2, vE2_E2 );
                    VEC_T(1,C)                          vK3 = FCN_V(tgMH_SAT)( vK2 );
                    VEC_T(1,C)                          vK4 = FCN_V(tgMH_DIV)( vE1_K0, vE1_E1 );
                    VEC_T(1,C)                          vK5 = FCN_V(tgMH_SAT)( vK4 );
                    VEC_T(1,C)                          vK6 = FCN_V(tgMH_DIV)( vE1_K1, vE1_E1 );
                    VEC_T(1,C)                          vK7 = FCN_V(tgMH_SAT)( vK6 );
                    VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_LT)( vPM0, FCN_V(tgMH_SET1)( TYPE_K(0) ) );
                    VEC_T(1,C)                          vCMP_1 = FCN_V(tgMH_CMP_LE)( vE1_K1, FCN_V(tgMH_SET1)( TYPE_K(0) ) );
                    VEC_T(1,C)                          vCMP_2 = FCN_V(tgMH_AND)( vCMP_0, vCMP_1 );

                    vET0 = vK7;
                    vET1 = FCN_V(tgMH_SEL)( vK5, vK3,vCMP_2 );
                }
                else
                {
                    VEC_T(1,C)                          vK2 = FCN_V(tgMH_SAT)( FCN_V(tgMH_DIV)( vE1_K1, vE1_E1 ) );
                    VEC_T(1,C)                          vK3 = FCN_V(tgMH_SAT)( FCN_V(tgMH_DIV)( vX0_E0, vE0_E0 ) );
                    VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_LT)( vE1_K0, FCN_V(tgMH_SET1)( TYPE_K(0) ) );

                    vET0 = FCN_V(tgMH_SAT)( FCN_V(tgMH_DIV)( vE1_K0, vE1_E1 ) );
                    vET1 = FCN_V(tgMH_SEL)( vK3, vK2, vCMP_0 );
                };
            };

            *pvET0 = vET0;
            *pvET1 = vET1;

            {
                VEC_T(1,C)                          vG0 = FCN_V(tgMH_MUL)( vET0, psET0->m_avEdge[0] );
                VEC_T(1,C)                          vG1 = FCN_V(tgMH_MUL)( vET1, psET0->m_avEdge[2] );
                VEC_T(1,C)                          vG2 = FCN_V(tgMH_ADD)( psET0->m_sPT.m_avPoint[0], vG0 );
                VEC_T(1,C)                          vG3 = FCN_V(tgMH_SUB)( vG2, vG1 );
                VEC_T(1,C)                          vG4 = FCN_V(tgMH_SUB)( vS0, vG3 );

                return (FCN_V(tgMH_LSQ)( vG4 ));
            }
        };
    };
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
