/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Parallelogram-Linear.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

/*  Let E0 and E1 be the two defining edges for the parallelogram                                                                                                                  */
/*                                                                                                                                                                                 */
/*  The normal N = E0 x E1                                                                                                                                                         */
/*  It follows that,                                                                                                                                                               */
/*      E1_(N × E0,DIM) = N_(E0 × E1,DIM) = N•N = |N|^2 ≥ 0                                                                                                                        */
/*           - The second edge always has a non-negative projection onto the first edge's clip plane.                                                                              */
/*      E0_(E1 × N,DIM) = -E0_(N × E1,DIM) = -N_(E1 × E0,DIM) = N_(E0 × E1,DIM) = N•N = |N|^2 ≥ 0                                                                                  */
/*           - The first edge always has a non-negative projection onto the second edge's clip plane.                                                                              */


#if !defined (ENABLE_RELOAD_GUARD_LINEAR)
    #define ENABLE_RELOAD_GUARD_LINEAR

    TgMSVC_WARN_DISABLE_PUSH(6235) /* Analysis - (<non-zero constant> || <expression>) is always a non-zero constant. */
    TgMSVC_WARN_DISABLE_PUSH(6240) /* Analysis - (<expression> && <non-zero constant>) always evaluates to the result of <expression>. */

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

    TgMSVC_WARN_DISABLE_POP(6235)
    TgMSVC_WARN_DISABLE_POP(6240)

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

/* ---- VI(tgCO_PE_ClosestSq_PM_LR) ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
VEC_T(1) VI(tgCO_PE_ClosestSq_PM_LR)( VEC_T(1,PC) pvPE0, VEC_T(1,PC) pvPE1, VEC_T(1,PC) pvLN0, VEC_OBJ_T(TgPARALLELOGRAM,CPC) psPE0, VEC_T(1,C) vS0, VEC_T(1,C) vD0 )
{
    VEC_T(1,C)                          vX0 = FCN_V(tgMH_SUB)( vS0, psPE0->m_vOrigin );
    VEC_T(1,C)                          vX0_X0 = FCN_V(tgMH_LSQ)( vX0 );
    VEC_T(1,C)                          vE1_EN0 = FCN_V(tgMH_DOT)( psPE0->m_avEdge_Normal[0], psPE0->m_avEdge[1] );
    VEC_T(1,C)                          vE0_EN1 = FCN_V(tgMH_DOT)( psPE0->m_avEdge_Normal[1], psPE0->m_avEdge[0] );

    TgBOOL_C                            bValid_E1_EN0 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( FCN_V(tgMH_ABS)( vE1_EN0 ), FCN_V(tgMH_SET1)( VAR_K(KTgEPS) ) ) );
    TgBOOL_C                            bValid_E0_EN1 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( FCN_V(tgMH_ABS)(vE0_EN1), FCN_V(tgMH_SET1)( VAR_K(KTgEPS) ) ) );

    TgPARAM_CHECK( FCN_VO(tgGM_PE_Is_Valid)(psPE0) && FCN_V(tgMH_Is_Valid_Point)(vS0) && FCN_V(tgMH_Is_Valid_Vector)(vD0) );

    if (TgEXPECT_FALSE( FCN_V(tgMH_Is_NR0)( vX0_X0 ) || bValid_E1_EN0 || bValid_E0_EN1 ) )
    {
        /* Degenerate parallelogram - One or both of the edges has a near-zero length */
        /* Quick Out - the point is within tolerance of rectangle origin. */
        *pvPE0 =  *pvPE1 = *pvLN0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
        return (FCN_V(tgMH_SET1)( -VAR_K(KTgMAX) ));
    }
    else
    {
        VEC_T(1,C)                          vD1_N = FCN_V(tgMH_DOT)( vD0, psPE0->m_vNormal );
        VEC_T(1,C)                          vX0_N = FCN_V(tgMH_DOT)( vX0, psPE0->m_vNormal );

        if (!FCN_V(tgMH_Is_NR0)( FCN_V(tgMH_ABS)( vD1_N ) ))
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
                VEC_T(1,C)                          vINT_EN0 = FCN_V(tgMH_DOT)( psPE0->m_avEdge_Normal[0], vK0 );
                VEC_T(1,C)                          vINT_EN1 = FCN_V(tgMH_DOT)( psPE0->m_avEdge_Normal[1], vK0 );

                TgBOOL_C                            bK2 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GE)( vINT_EN0, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) );
                TgBOOL_C                            bK3 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( vINT_EN0, vE1_EN0 ) );
                TgBOOL_C                            bK4 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GE)( vINT_EN0, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) );
                TgBOOL_C                            bK5 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( vINT_EN0, vE0_EN1 ) );

                if (bK2 && bK3 && bK4 && bK5)
                {
                    *pvPE0 = FCN_V(tgMH_DIV)( vINT_EN1, vE0_EN1 );
                    *pvPE1 = FCN_V(tgMH_DIV)( vINT_EN0, vE1_EN0 );
                    *pvLN0 = vInt;

                    return (FCN_V(tgMH_SET1)( -VAR_K(KTgMAX) ));
                };
            };
        };

        {
            VEC_T(1,C)                          vK0 = FCN_V(tgMH_SUB)( vS0, psPE0->m_vOrigin );
            VEC_T(1,C)                          vX1 = FCN_V(tgMH_ADD)( vK0, vD0 );

            VEC_T(1,C)                          v00 = FCN_V(tgMH_DOT)( psPE0->m_avEdge_Normal[0], vX0 );
            VEC_T(1,C)                          v01 = FCN_V(tgMH_DOT)( psPE0->m_avEdge_Normal[1], vX0 );
            VEC_T(1,C)                          vPE = FCN_V(tgMH_SET1)(  VAR_K(KTgEPS) );

            #if !LN_CAP_0 || !LN_CAP_1
                VEC_T(1,C)                          vNE = FCN_V(tgMH_SET1)( -VAR_K(KTgEPS) );
            #endif

            #if LN_CAP_1
                VEC_T(1,C)                          v10 = FCN_V(tgMH_DOT)( psPE0->m_avEdge_Normal[0], vX1 );
                VEC_T(1,C)                          v11 = FCN_V(tgMH_DOT)( psPE0->m_avEdge_Normal[1], vX1 );
            #else
                VEC_T(1,C)                          v10 = FCN_V(tgMH_DOT)( psPE0->m_avEdge_Normal[0], vD0 );
                VEC_T(1,C)                          v11 = FCN_V(tgMH_DOT)( psPE0->m_avEdge_Normal[1], vD0 );
            #endif

            #if LN_CAP_0
                VEC_T(1,C)                          vX2 = FCN_V(tgMH_SUB)( vE1_EN0, v00 );
                VEC_T(1,C)                          vX3 = FCN_V(tgMH_SUB)( vE0_EN1, v01 );

                TgBOOL_C                            bF0 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( v00, vPE ) );
                TgBOOL_C                            bF1 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( v01, vPE ) );
                TgBOOL_C                            bF2 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vX2, vPE ) );
                TgBOOL_C                            bF3 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vX3, vPE ) );

                TgBOOL_C                            bK0 = FCN_V(tgMH_CMP_ALL_TO_BOOL)(FCN_V(tgMH_CMP_LE)( v00, vE1_EN0 ));
                TgBOOL_C                            bK1 = FCN_V(tgMH_CMP_ALL_TO_BOOL)(FCN_V(tgMH_CMP_LE)( v01, vE0_EN1 ));
                TgBOOL_C                            bF4 = !bF0 && !bF1 && bK0 && bK1;
            #else
                TgBOOL_C                            bF0 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( v10, vPE ) );
                TgBOOL_C                            bF1 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( v11, vPE ) );
                TgBOOL_C                            bF2 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( v10, vNE ) );
                TgBOOL_C                            bF3 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( v11, vNE ) );
                TgBOOL_C                            bF4 = false;
            #endif

            #if LN_CAP_1
                VEC_T(1,C)                          vX4 = FCN_V(tgMH_SUB)( vE1_EN0, v10 );
                VEC_T(1,C)                          vX5 = FCN_V(tgMH_SUB)( vE0_EN1, v11 );

                TgBOOL_C                            bF5 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( v10, vPE ) );
                TgBOOL_C                            bF6 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( v11, vPE ) );
                TgBOOL_C                            bF7 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vX4, vPE ) );
                TgBOOL_C                            bF8 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vX5, vPE ) );

                TgBOOL_C                            bK2 = FCN_V(tgMH_CMP_ALL_TO_BOOL)(FCN_V(tgMH_CMP_LE)( v10, vE1_EN0 ));
                TgBOOL_C                            bK3 = FCN_V(tgMH_CMP_ALL_TO_BOOL)(FCN_V(tgMH_CMP_LE)( v11, vE0_EN1 ));
                TgBOOL_C                            bF9 = !bF5 && !bF6 && bK2 && bK3;
            #else
                TgBOOL_C                            bF5 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( v10, vNE ) );
                TgBOOL_C                            bF6 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( v11, vNE ) );
                TgBOOL_C                            bF7 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( v10, vPE ) );
                TgBOOL_C                            bF8 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( v11, vPE ) );
                TgBOOL_C                            bF9 = false;
            #endif

            VEC_T(1)                            vPE0, vPE1, vG1, vT0, vT1, vTestSq, vDistSq;
            TgSINT_E32                          iTest = 0;

            vPE0 = vPE1 = vG1 = vT0 = vT1 = vTestSq = FCN_V(tgMH_SET1)( TYPE_K(0) );
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

            /* If the linear is a segment, and both termination points are contained inside of the normal extruded triangle then find the closest point to the plane - */
            /* and terminate processing. */

            if (iTest & (3 << 4))
            {
                VEC_T(1,C)                          vX1_N = FCN_V(tgMH_ABS)(FCN_V(tgMH_DOT)( vX1, psPE0->m_vNormal ));

                if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( FCN_V(tgMH_ABS)( vX0_N ), vX1_N ) ))
                {
                    *pvPE0 = FCN_V(tgMH_DIV)( v01, vE0_EN1 );
                    *pvPE1 = FCN_V(tgMH_DIV)( v00, vE1_EN0 );
                    *pvLN0 = FCN_V(tgMH_SET1)( TYPE_K(0) );

                    return (FCN_V(tgMH_MUL)( vX0_N, vX0_N ));
                }
                else
                {
                    *pvPE0 = FCN_V(tgMH_DIV)( v11, vE0_EN1 );
                    *pvPE1 = FCN_V(tgMH_DIV)( v10, vE1_EN0 );
                    *pvLN0 = FCN_V(tgMH_SET1)( TYPE_K(1) );

                    return (FCN_V(tgMH_MUL)( vX1_N, vX1_N ));
                };
            };

            /* Distance calculation for the linear's origin if its capped and within the parallelogram's normal-extruded space. */

            if (iTest & (1 << 4))
            {
                vPE0 = FCN_V(tgMH_DIV)( v01, vE0_EN1 );
                vPE1 = FCN_V(tgMH_DIV)( v00, vE1_EN0 );
                vG1 = FCN_V(tgMH_SET1)( TYPE_K(0) );
                vDistSq = FCN_V(tgMH_MUL)( vX0_N, vX0_N );
            };

            /* Distance calculation for the linear's termination if its capped and within the parallelogram's normal-extruded space. */

            if (iTest & (1 << 5))
            {
                VEC_T(1,C)                          vX1_N = FCN_V(tgMH_DOT)( vX1, psPE0->m_vNormal );

                vTestSq = FCN_V(tgMH_MUL)( vX1_N, vX1_N );

                if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTestSq, vDistSq ) ))
                {
                    vPE0 = FCN_V(tgMH_DIV)( v11, vE0_EN1 );
                    vPE1 = FCN_V(tgMH_DIV)( v10, vE1_EN0 );
                    vG1 = FCN_V(tgMH_SET1)( TYPE_K(1) );
                    vDistSq = vTestSq;
                };
            };

            /* Compare the segment against the four parallelogram edges. */

            if (iTest & (1 << 0))
            {
                vTestSq = FCN_VO(tgCO_LR11_ClosestSq_PM_LR11)( &vT0, &vT1, psPE0->m_vOrigin, psPE0->m_avEdge[0], vS0, vD0 );

                if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTestSq, vDistSq ) ))
                {
                    vDistSq = vTestSq;
                    vPE0 = vT0;
                    vPE1 = FCN_V(tgMH_SET1)( TYPE_K(0) );
                    vG1 = vT1;
                };
            };

            if (iTest & (1 << 1))
            {
                vTestSq = FCN_VO(tgCO_LR11_ClosestSq_PM_LR11)( &vT0, &vT1, psPE0->m_vOrigin, psPE0->m_avEdge[1], vS0, vD0 );

                if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTestSq, vDistSq ) ))
                {
                    vDistSq = vTestSq;
                    vPE0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
                    vPE1 = vT0;
                    vG1 = vT1;
                };
            };

            if (iTest & (1 << 2))
            {
                VEC_T(1,C)      vK3 = FCN_VO(tgGM_PE_Query_Point_2)(psPE0);

                vTestSq = FCN_VO(tgCO_LR11_ClosestSq_PM_LR11)( &vT0, &vT1, vK3, psPE0->m_avEdge[0], vS0, vD0 );

                if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTestSq, vDistSq ) ))
                {
                    vDistSq = vTestSq;
                    vPE0 = vT0;
                    vPE1 = FCN_V(tgMH_SET1)( TYPE_K(1) );
                    vG1 = vT1;
                };
            };

            if (iTest & (1 << 3))
            {
                VEC_T(1,C)      vK4 = FCN_VO(tgGM_PE_Query_Point_1)(psPE0);

                vTestSq = FCN_VO(tgCO_LR11_ClosestSq_PM_LR11)( &vT0, &vT1, vK4, psPE0->m_avEdge[1], vS0, vD0);

                if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTestSq, vDistSq ) ))
                {
                    vDistSq = vTestSq;
                    vPE0 = FCN_V(tgMH_SET1)( TYPE_K(1) );
                    vPE1 = vT0;
                    vG1 = vT1;
                };
            };

            *pvPE0 = vPE0;
            *pvPE1 = vPE1;
            *pvLN0 = vG1;

            return (vDistSq);
        };
    };
}


/* ---- VI(tgCO_PE_Clip_PM_LR) --------------------------------------------------------------------------------------------------------------------------------------------- */
/*  -- Internal Function -- LN_CAP_0, LN_CAP_1 : Indicate the termination condition of the linear {bc0,LN_CAP_1}                                                                   */
/* Input:  psPE0: Parallelogram primitive - F_Clip-space is the region defined by the infinite extrusion along the normal.                                                         */
/* Input:  vS0,vD0: Origin and Direction for the Linear                                                                                                                            */
/* Output: fLN0,fLN1: Parametric parameter to generate the two points of the linear contained inside the clip space.                                                               */
/* Return: Result Code.                                                                                                                                                            */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT VI(tgCO_PE_Clip_PM_LR)( VEC_T(1,PC) pvLN0, VEC_T(1,PC) pvLN1, VEC_OBJ_T(TgPARALLELOGRAM,CPC) psPE0, VEC_T(1,C) vS0, VEC_T(1,C) vD0 )
{
    VEC_T(1)                            vMin, vMax;

    VEC_T(1,C)                          vZero = FCN_V(tgMH_SET1)(TYPE_K(0));

    VEC_T(1,C)                          vE1_EN0 = FCN_V(tgMH_DOT)( psPE0->m_avEdge_Normal[0], psPE0->m_avEdge[1] );
    VEC_T(1,C)                          vE0_EN1 = FCN_V(tgMH_DOT)( psPE0->m_avEdge_Normal[1], psPE0->m_avEdge[0] );
    VEC_T(1,C)                          vEdgeMax[2] = { vE1_EN0, vE0_EN1 };
    VEC_T(1,C)                          vDS = FCN_V(tgMH_SUB)( vS0, psPE0->m_vOrigin );

    TgBOOL_C                            bValid_E1_EN0 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( FCN_V(tgMH_ABS)( vE1_EN0 ), FCN_V(tgMH_SET1)( VAR_K(KTgEPS) ) ) );
    TgBOOL_C                            bValid_E0_EN1 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( FCN_V(tgMH_ABS)(vE0_EN1), FCN_V(tgMH_SET1)( VAR_K(KTgEPS) ) ) );

    if (TgEXPECT_FALSE( bValid_E1_EN0 || bValid_E0_EN1 ) )
    {
        /* Degenerate rectangle - One or both of the edges has a near-zero length */
        return (KTgE_FAIL);
    }

    vMin = FCN_V(tgMH_SET1)( -VAR_K(KTgMAX) );
    vMax = FCN_V(tgMH_SET1)( VAR_K(KTgMAX) );

    /* Quick out - Does the linear exist outside of the clip region. */

    for (TgRSIZE uiIndex = 0; uiIndex < 2; ++uiIndex)
    {
        VEC_T(1,C)                          vDS_ENI = FCN_V(tgMH_DOT)( psPE0->m_avEdge_Normal[uiIndex], vDS );
        VEC_T(1,C)                          vD0_ENI = FCN_V(tgMH_DOT)( psPE0->m_avEdge_Normal[uiIndex], vD0 );

    #if LN_CAP_0
        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vDS_ENI, vZero ) ))
        {
            TgBOOL_C                            bK0 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vD0_ENI, vZero ) );

    #if LN_CAP_1
            if (bK0 || FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( FCN_V(tgMH_ADD)( vDS_ENI, vD0_ENI ), vZero ) ))
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
        else if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vDS_ENI, vEdgeMax[uiIndex] ) ))
        {
            TgBOOL_C                            bK0 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vD0_ENI, vZero ) );

    #if LN_CAP_1
            if (bK0 || FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( FCN_V(tgMH_ADD)( vDS_ENI, vD0_ENI ), vEdgeMax[uiIndex] ) ))
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
            if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vD0_ENI, FCN_V(tgMH_SET1)( -VAR_K(KTgEPS) ) ) ))
            {
                VEC_T(1, C)                          vK0 = FCN_V(tgMH_MUL)(vD0_ENI, vMin);
                VEC_T(1, C)                          vK1 = FCN_V(tgMH_ADD)(vK0, vDS_ENI);
                VEC_T(1, C)                          vK2 = FCN_V(tgMH_SUB)(vK1, vEdgeMax[uiIndex]);
                VEC_T(1, C)                          vK3 = FCN_V(tgMH_MUL)(vD0_ENI, vMax);
                VEC_T(1, C)                          vK4 = FCN_V(tgMH_ADD)(vDS_ENI, vK3);

                if (FCN_V(tgMH_CMP_ALL_TO_BOOL)(FCN_V(tgMH_CMP_GE)( vK2, vZero ) ))
                {
                    vMin = FCN_V(tgMH_DIV)( FCN_V(tgMH_SUB)( vEdgeMax[uiIndex], vDS_ENI ), vD0_ENI );
                };

                if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vK4, vZero ) ))
                {
                    vMax = FCN_V(tgMH_NEG)( FCN_V(tgMH_DIV)( vDS_ENI, vD0_ENI ) );
                };
            }
            else if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vD0_ENI, FCN_V(tgMH_SET1)( VAR_K(KTgEPS) ) ) ))
            {
                VEC_T(1, C)                          vK0 = FCN_V(tgMH_MUL)( vD0_ENI, vMax );
                VEC_T(1, C)                          vK1 = FCN_V(tgMH_ADD)( vK0, vDS_ENI );
                VEC_T(1, C)                          vK2 = FCN_V(tgMH_SUB)( vK1, vEdgeMax[uiIndex] );
                VEC_T(1, C)                          vK3 = FCN_V(tgMH_MUL)( vD0_ENI, vMin );
                VEC_T(1, C)                          vK4 = FCN_V(tgMH_ADD)( vDS_ENI, vK3 );

                if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vK4, vZero ) ))
                {
                    vMin = FCN_V(tgMH_NEG)( FCN_V(tgMH_DIV)( vDS_ENI, vD0_ENI ) );
                };

                if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GE)( vK2, vZero ) ))
                {
                    vMax = FCN_V(tgMH_DIV)( FCN_V(tgMH_SUB)( vEdgeMax[uiIndex], vDS_ENI ), vD0_ENI );
                };
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
