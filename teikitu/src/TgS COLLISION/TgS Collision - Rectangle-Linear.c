/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Rectangle-Linear.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#if !defined (ENABLE_RELOAD_GUARD_LINEAR)
    #define ENABLE_RELOAD_GUARD_LINEAR

    MSVC_WARN_DISABLE_PUSH(6235) /* Analysis - (<non-zero constant> || <expression>) is always a non-zero constant. */
    MSVC_WARN_DISABLE_PUSH(6240) /* Analysis - (<expression> && <non-zero constant>) always evaluates to the result of <expression>. */

    #define LN_CAP_0 0
    #define LN_CAP_1 0
        #define VI(A) FCN_VO(A##00)
        #include __FILE__
        #undef VI
    #undef LN_CAP_0
    #undef LN_CAP_1

    #define LN_CAP_0 1
    #define LN_CAP_1 0
        #define VI(A) FCN_VO(A##10)
        #include __FILE__
        #undef VI
    #undef LN_CAP_0
    #undef LN_CAP_1

    #define LN_CAP_0 1
    #define LN_CAP_1 1
        #define VI(A) FCN_VO(A##11)
        #include __FILE__
        #undef VI
    #undef LN_CAP_0
    #undef LN_CAP_1

    MSVC_WARN_DISABLE_POP(6235) /* Analysis - (<non-zero constant> || <expression>) is always a non-zero constant. */
    MSVC_WARN_DISABLE_POP(6240) /* Analysis - (<expression> && <non-zero constant>) always evaluates to the result of <expression>. */

    #undef ENABLE_RELOAD_GUARD_LINEAR

/*# !defined (ENABLE_RELOAD_GUARD_LINEAR) */
#else

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

/* ---- VI(tgCO_RT_ClosestSq_PM_LR) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
VEC_T(1)  VI(tgCO_RT_ClosestSq_PM_LR)( VEC_T(1,PC) pvRT0, VEC_T(1,PC) pvRT1, VEC_T(1,PC) pvLN0, VEC_OBJ_T(TgRECTANGLE,CPC) psRT0, VEC_T(1,C) vS0, VEC_T(1,C) vD0 )
{
    VEC_T(1,C)                          vX0 = FCN_V(tgMH_SUB)( vS0, psRT0->m_vOrigin );
    VEC_T(1,C)                          vX0_X0 = FCN_V(tgMH_LSQ)( vX0 );

    TgERROR( FCN_VO(tgGM_RT_Is_Valid)(psRT0) && FCN_V(tgMH_Is_Valid_Point)(vS0) && FCN_V(tgMH_Is_Valid_Vector)(vD0) );

    if (FCN_V(tgMH_Is_NR0)( vX0_X0 ))
    {
        /* Quick Out - the point is within tolerance of rectangle origin. */
        *pvRT0 = *pvRT1 = *pvLN0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
        return (FCN_V(tgMH_SET1)( -VAR_K(KTgMAX) ));
    }
    else
    {
        VEC_T(1,C)                          vE0_E0 = FCN_V(tgMH_LSQ)( psRT0->m_avEdge[0] );
        VEC_T(1,C)                          vE1_E1 = FCN_V(tgMH_LSQ)( psRT0->m_avEdge[1] );
        VEC_T(1,C)                          vD1_N = FCN_V(tgMH_DOT)( vD0, psRT0->m_vNormal );
        VEC_T(1,C)                          vX0_N = FCN_V(tgMH_DOT)( vX0, psRT0->m_vNormal );

        if (FCN_V(tgMH_Is_NR0)( vE0_E0 ) || FCN_V(tgMH_Is_NR0)( vE1_E1 ))
        {
            /* Degenerate rectangle - One or both of the edges has a near-zero length */
            return (FCN_V(tgMH_SET1)( -VAR_K(KTgMAX) ));
        }
        else if (!FCN_V(tgMH_Is_NR0)( FCN_V(tgMH_ABS)( vD1_N ) ))
        {
            /* Non-trivial plane normal-component in the linear direction.  Check the intersection of the two primitives. */

            VEC_T(1,C)                          vInt = FCN_V(tgMH_NEG)(FCN_V(tgMH_DIV)( vX0_N, vD1_N ));

            #if LN_CAP_0
                TgBOOL_C                            bK0 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GE)( vInt, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) );
            #else
                TgBOOL_C                            bK0 = true;
            #endif

            #if LN_CAP_1
                TgBOOL_C                            bK1 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( vInt, FCN_V(tgMH_SET1)( TYPE_K(1) ) ) );
            #else
                TgBOOL_C                            bK1 = true;
            #endif

            if (bK0 && bK1)
            {
                VEC_T(1,C)                          vK1 = FCN_V(tgMH_MUL)( vInt, vD0 );
                VEC_T(1,C)                          vK0 = FCN_V(tgMH_ADD)( vX0, vK1 );
                VEC_T(1,C)                          vINT_EN0 = FCN_V(tgMH_DOT)( psRT0->m_avEdge[1], vK0 );
                VEC_T(1,C)                          vINT_EN1 = FCN_V(tgMH_DOT)( psRT0->m_avEdge[0], vK0 );

                TgBOOL_C                            bK2 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GE)( vINT_EN0, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) );
                TgBOOL_C                            bK3 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( vINT_EN0, vE1_E1 ) );
                TgBOOL_C                            bK4 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GE)( vINT_EN0, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) );
                TgBOOL_C                            bK5 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( vINT_EN0, vE0_E0 ) );

                if (bK2 && bK3 && bK4 && bK5)
                {
                    *pvRT0 = FCN_V(tgMH_DIV)( vINT_EN1, vE0_E0 );
                    *pvRT1 = FCN_V(tgMH_DIV)( vINT_EN0, vE1_E1 );
                    *pvLN0 = vInt;

                    return (FCN_V(tgMH_SET1)( -VAR_K(KTgMAX) ));
                };
            };
        };

        {
            VEC_T(1,C)                          vK0 = FCN_V(tgMH_SUB)( vS0, psRT0->m_vOrigin );
            VEC_T(1,C)                          vX1 = FCN_V(tgMH_ADD)( vK0, vD0 );
            VEC_T(1,C)                          v00 = FCN_V(tgMH_DOT)( psRT0->m_avEdge[1], vX0 );
            VEC_T(1,C)                          v01 = FCN_V(tgMH_DOT)( psRT0->m_avEdge[0], vX0 );
            VEC_T(1,C)                          vPE = FCN_V(tgMH_SET1)(  VAR_K(KTgEPS) );

            #if !LN_CAP_0 || !LN_CAP_1
                VEC_T(1,C)                          vNE = FCN_V(tgMH_SET1)( -VAR_K(KTgEPS) );
            #endif

            #if LN_CAP_1
                VEC_T(1,C)                          v10 = FCN_V(tgMH_DOT)( psRT0->m_avEdge[1], vX1 );
                VEC_T(1,C)                          v11 = FCN_V(tgMH_DOT)( psRT0->m_avEdge[0], vX1 );
            #else
                VEC_T(1,C)                          v10 = FCN_V(tgMH_DOT)( psRT0->m_avEdge[1], vD0 );
                VEC_T(1,C)                          v11 = FCN_V(tgMH_DOT)( psRT0->m_avEdge[0], vD0 );
            #endif

            #if LN_CAP_0
                VEC_T(1,C)                          vX2 = FCN_V(tgMH_SUB)( vE1_E1, v00 );
                VEC_T(1,C)                          vX3 = FCN_V(tgMH_SUB)( vE0_E0, v01 );

                TgBOOL_C                            bF0 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( v00, vPE ) );
                TgBOOL_C                            bF1 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( v01, vPE ) );
                TgBOOL_C                            bF2 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vX2, vPE ) );
                TgBOOL_C                            bF3 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vX3, vPE ) );

                TgBOOL_C                            bK0 = FCN_V(tgMH_CMP_ALL_TO_BOOL)(FCN_V(tgMH_CMP_LE)( v00, vE1_E1 ));
                TgBOOL_C                            bK1 = FCN_V(tgMH_CMP_ALL_TO_BOOL)(FCN_V(tgMH_CMP_LE)( v01, vE0_E0 ));
                TgBOOL_C                            bF4 = !bF0 && !bF1 && bK0 && bK1;
            #else
                TgBOOL_C                            bF0 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( v10, vPE ) );
                TgBOOL_C                            bF1 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( v11, vPE ) );
                TgBOOL_C                            bF2 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( v10, vNE ) );
                TgBOOL_C                            bF3 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( v11, vNE ) );
                TgBOOL_C                            bF4 = false;
            #endif

            #if LN_CAP_1
                VEC_T(1, C)                         vX4 = FCN_V(tgMH_SUB)( vE1_E1, v10 );
                VEC_T(1, C)                         vX5 = FCN_V(tgMH_SUB)( vE0_E0, v11 );

                TgBOOL_C                            bF5 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( v10, vPE ) );
                TgBOOL_C                            bF6 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( v11, vPE ) );
                TgBOOL_C                            bF7 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vX4, vPE ) );
                TgBOOL_C                            bF8 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vX5, vPE ) );

                TgBOOL_C                            bK2 = FCN_V(tgMH_CMP_ALL_TO_BOOL)(FCN_V(tgMH_CMP_LE)( v10, vE1_E1 ));
                TgBOOL_C                            bK3 = FCN_V(tgMH_CMP_ALL_TO_BOOL)(FCN_V(tgMH_CMP_LE)( v11, vE0_E0 ));
                TgBOOL_C                            bF9 = !bF5 && !bF6 && bK2 && bK3;
            #else
                TgBOOL_C                            bF5 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( v10, vNE ) );
                TgBOOL_C                            bF6 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( v11, vNE ) );
                TgBOOL_C                            bF7 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( v10, vPE ) );
                TgBOOL_C                            bF8 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( v11, vPE ) );
                TgBOOL_C                            bF9 = false;
            #endif

            VEC_T(1)                            vRT0, vRT1, vG1, vT0, vT1, vTestSq, vDistSq;
            TgSINT_F32                          iTest = 0;

            vRT0 = vRT1 = vG1 = vT0 = vT1 = vTestSq = FCN_V(tgMH_SET1)( TYPE_K(0) );
            vDistSq = FCN_V(tgMH_SET1)( VAR_K(KTgMAX) );

            iTest |= bF0 ? (1 << 0) : 0;
            iTest |= bF1 ? (1 << 1) : 0;
            iTest |= bF2 ? (1 << 2) : 0;
            iTest |= bF3 ? (1 << 3) : 0;
            iTest |= bF4 ? (1 << 4) : 0;

            iTest |= bF5 ? (1 << 0) : 0;
            iTest |= bF6 ? (1 << 1) : 0;
            iTest |= bF7 ? (1 << 2) : 0;
            iTest |= bF8 ? (1 << 3) : 0;
            iTest |= bF9 ? (1 << 5) : 0;

            /* Distance calculation for the linear's origin if its capped and within the rectangle's normal-extruded space. */

            if (iTest & (1 << 4))
            {
                vDistSq = FCN_V(tgMH_MUL)( vX0_N, vX0_N );
                vRT0 = FCN_V(tgMH_DIV)( v01, vE0_E0 );
                vRT1 = FCN_V(tgMH_DIV)( v00, vE1_E1 );
                vG1 = FCN_V(tgMH_SET1)( TYPE_K(0) );
            };

            /* Distance calculation for the linear's termination if its capped and within the rectangle's normal-extruded space. */

            if (iTest & (1 << 5))
            {
                VEC_T(1,C)                          vX1_N = FCN_V(tgMH_DOT)( vX1, psRT0->m_vNormal );

                vTestSq = FCN_V(tgMH_MUL)( vX1_N, vX1_N );

                if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTestSq, vDistSq ) ))
                {
                    vDistSq = vTestSq;
                    vRT0 = FCN_V(tgMH_DIV)( v11, vE0_E0 );
                    vRT1 = FCN_V(tgMH_DIV)( v10, vE1_E1 );
                    vG1 = FCN_V(tgMH_SET1)( TYPE_K(1) );
                };

                /* Check to see if the segment is fully contained within the extruded rectangle space. */
                if (iTest & (1 << 4))
                {
                    *pvRT0 = vRT0;
                    *pvRT1 = vRT1;
                    *pvLN0 = vG1;

                    return (vDistSq);
                };
            };

            /* Compare the segment against the four rectangle edges. */

            if (iTest & (1 << 0))
            {
                vTestSq = FCN_VO(tgCO_LR11_ClosestSq_PM_LR11)( &vT0, &vT1, psRT0->m_vOrigin, psRT0->m_avEdge[0], vS0, vD0 );

                if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTestSq, vDistSq ) ))
                {
                    vDistSq = vTestSq;
                    vRT0 = vT0;
                    vRT1 = FCN_V(tgMH_SET1)( TYPE_K(0) );
                    vG1 = vT1;
                }
            }

            if (iTest & (1 << 1))
            {
                vTestSq = FCN_VO(tgCO_LR11_ClosestSq_PM_LR11)( &vT0, &vT1, psRT0->m_vOrigin, psRT0->m_avEdge[1], vS0, vD0 );

                if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTestSq, vDistSq ) ))
                {
                    vDistSq = vTestSq;
                    vRT0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
                    vRT1 = vT0;
                    vG1 = vT1;
                }
            }

            if (iTest & (1 << 2))
            {
                VEC_T(1,C)                          vK1 = FCN_VO(tgGM_RT_Query_Point_2)(psRT0);

                vTestSq = FCN_VO(tgCO_LR11_ClosestSq_PM_LR11)( &vT0, &vT1, vK1, psRT0->m_avEdge[0], vS0, vD0 );

                if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTestSq, vDistSq ) ))
                {
                    vDistSq = vTestSq;
                    vRT0 = vT0;
                    vRT1 = FCN_V(tgMH_SET1)( TYPE_K(1) );
                    vG1 = vT1;
                }
            }

            if (iTest & (1 << 3))
            {
                VEC_T(1,C)                          vK1 = FCN_VO(tgGM_RT_Query_Point_1)(psRT0);

                vTestSq = FCN_VO(tgCO_LR11_ClosestSq_PM_LR11)( &vT0, &vT1, vK1, psRT0->m_avEdge[1], vS0, vD0 );

                if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTestSq, vDistSq ) ))
                {
                    vDistSq = vTestSq;
                    vRT0 = FCN_V(tgMH_SET1)( TYPE_K(1) );
                    vRT1 = vT0;
                    vG1 = vT1;
                }
            }

            *pvRT0 = vRT0;
            *pvRT1 = vRT1;
            *pvLN0 = vG1;

            return (vDistSq);
        };
    };
}


/* ---- VI(tgCO_RT_Clip_PM_LR) --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* TODO Needs testing - outputs are not written */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT VI(tgCO_RT_Clip_PM_LR)( VEC_T(1,PC) pvLN0, VEC_T(1,PC) pvLN1, VEC_OBJ_T(TgRECTANGLE,CPC) psRT0, VEC_T(1,C) vS0, VEC_T(1,C) vD0 )
{
    VEC_T(1)                            vMin, vMax;

    VEC_T(1,C)                          vZero = FCN_V(tgMH_SET1)( TYPE_K(0) );

    VEC_T(1,C)                          vE0_E0 = FCN_V(tgMH_LSQ)( psRT0->m_avEdge[0] );
    VEC_T(1,C)                          vE1_E1 = FCN_V(tgMH_LSQ)( psRT0->m_avEdge[1] );
    VEC_T(1,C)                          vEdgeMax[2] = { vE0_E0, vE1_E1 };
    VEC_T(1,C)                          vDS = FCN_V(tgMH_SUB)( vS0, psRT0->m_vOrigin );

    if (FCN_V(tgMH_Is_NR0)( vE0_E0 ) || FCN_V(tgMH_Is_NR0)( vE1_E1 ))
    {
        /* Degenerate rectangle - One or both of the edges has a near-zero length */
        return (KTgE_FAIL);
    };

    /* Quick out - Does the linear exist outside of the clip region. */

    vMin = FCN_V(tgMH_SET1)( -VAR_K(KTgMAX) );
    vMax = FCN_V(tgMH_SET1)( VAR_K(KTgMAX) );

    for (TgRSIZE uiIndex = 0; uiIndex < 2; ++uiIndex)
    {
        VEC_T(1,C)                          vDS_EI = FCN_V(tgMH_DOT)( psRT0->m_avEdge[uiIndex], vDS );
        VEC_T(1,C)                          vD0_EI = FCN_V(tgMH_DOT)( psRT0->m_avEdge[uiIndex], vD0 );

    #if LN_CAP_0
        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vDS_EI, vZero ) ))
        {
            TgBOOL_C                            bK0 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vD0_EI, vZero ) );

    #if LN_CAP_1
            if (bK0 || FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( FCN_V(tgMH_ADD)( vDS_EI, vD0_EI ), vZero ) ))
            {
                return (KTgE_NO_INTERSECT);
            };
    #else /* LN_CAP_1 */
            if (bK0)
            {
                return (KTgE_NO_INTERSECT);
            };
    #endif /* LN_CAP_1 */
        }
        else if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vDS_EI, vEdgeMax[uiIndex] ) ))
        {
            TgBOOL_C                            bK0 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vD0_EI, vZero ) );

    #if LN_CAP_1
            if (bK0 || FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( FCN_V(tgMH_ADD)( vDS_EI, vD0_EI ), vEdgeMax[uiIndex] ) ))
            {
                return (KTgE_NO_INTERSECT);
            };
    #else /* LN_CAP_1 */
            if (bK0)
            {
                return (KTgE_NO_INTERSECT);
            };
    #endif /* LN_CAP_1 */
        };
    #endif /* LN_CAP_0 */

        /* Find the non-capped intersections of this linear with the two enclosing planes. */
        {
            if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vD0_EI, FCN_V(tgMH_SET1)( -VAR_K(KTgEPS) ) ) ))
            {
                VEC_T(1,C)                          vK0 = FCN_V(tgMH_MUL)( vD0_EI, vMin );
                VEC_T(1,C)                          vK1 = FCN_V(tgMH_ADD)( vK0, vDS_EI );
                VEC_T(1,C)                          vK2 = FCN_V(tgMH_SUB)( vK1, vEdgeMax[uiIndex] );
                VEC_T(1,C)                          vK3 = FCN_V(tgMH_MUL)( vD0_EI, vMax );
                VEC_T(1,C)                          vK4 = FCN_V(tgMH_ADD)( vDS_EI, vK3 );

                VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_GE)( vK2, vZero );
                VEC_T(1,C)                          vCMP_1 = FCN_V(tgMH_CMP_LT)( vK4, vZero );
                VEC_T(1,C)                          vK5 = FCN_V(tgMH_DIV)( FCN_V(tgMH_SUB)( vEdgeMax[uiIndex], vDS_EI ), vD0_EI );
                VEC_T(1,C)                          vK6 = FCN_V(tgMH_NEG)( FCN_V(tgMH_DIV)( vDS_EI, vD0_EI ) );

                vMin = FCN_V(tgMH_SEL)( vMin, vK5, vCMP_0 );
                vMax = FCN_V(tgMH_SEL)( vMax, vK6, vCMP_1 );
            }
            else if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vD0_EI, FCN_V(tgMH_SET1)( VAR_K(KTgEPS) ) ) ))
            {
                VEC_T(1,C)                          vK0 = FCN_V(tgMH_MUL)( vD0_EI, vMax );
                VEC_T(1,C)                          vK1 = FCN_V(tgMH_ADD)( vK0, vDS_EI );
                VEC_T(1,C)                          vK2 = FCN_V(tgMH_SUB)( vK1, vEdgeMax[uiIndex] );
                VEC_T(1,C)                          vK3 = FCN_V(tgMH_MUL)( vD0_EI, vMin );
                VEC_T(1,C)                          vK4 = FCN_V(tgMH_ADD)( vDS_EI, vK3 );

                VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_LT)( vK4, vZero );
                VEC_T(1,C)                          vCMP_1 = FCN_V(tgMH_CMP_GE)( vK2, vZero );
                VEC_T(1,C)                          vK5 = FCN_V(tgMH_NEG)( FCN_V(tgMH_DIV)( vDS_EI, vD0_EI ) );
                VEC_T(1,C)                          vK6 = FCN_V(tgMH_DIV)( FCN_V(tgMH_SUB)( vEdgeMax[uiIndex], vDS_EI ), vD0_EI );

                vMin = FCN_V(tgMH_SEL)( vMin, vK5, vCMP_0 );
                vMax = FCN_V(tgMH_SEL)( vMax, vK6, vCMP_1 );
            };
        };
    };

    /* Return the results - capped to the linear legal region. */

    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vMin, vMax ) ))
    {
        return (KTgE_FAIL);
    };

    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( vMin, FCN_V(tgMH_SET1)( -VAR_K(KTgMAX) )  ) ))
    {
        return (KTgE_FAIL);
    };

    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GE)( vMax, FCN_V(tgMH_SET1)( VAR_K(KTgMAX) )  ) ))
    {
        return (KTgE_FAIL);
    };

    *pvLN0 = vMin;
    *pvLN1 = vMax;

#if LN_CAP_0
    *pvLN0 = FCN_V(tgMH_MAX)( *pvLN0, vZero );
    *pvLN1 = FCN_V(tgMH_MAX)( *pvLN1, vZero );
#endif

#if LN_CAP_1
    *pvLN0 = FCN_V(tgMH_MIN)( *pvLN0, FCN_V(tgMH_SET1)( TYPE_K(1) ) );
    *pvLN1 = FCN_V(tgMH_MIN)( *pvLN1, FCN_V(tgMH_SET1)( TYPE_K(1) ) );
#endif

    return (KTgS_OK);
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/*# !defined (ENABLE_RELOAD_GUARD_LINEAR) */
#endif
