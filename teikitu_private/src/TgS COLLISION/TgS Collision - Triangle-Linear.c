/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Triangle-Linear.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

/** Triangle Definition: T0(α,β) = P0 + α•E0 + β•E1 | α ε [ 0, 1], β ε [ 0, 1], (α + β) ε [0, 1]
    Segment Definition:   G1(γ) = P3 + γ•D1 | γ ε [ 0, 1]

    Derivation:

           .    .              .    .
            . G .               . G .   NOTE: Keep in mind that in regions C, E and G, an obtuse angle can lead to having significant projections along the other edge.
             .  .                .  .
              . .                 . .      E0
               ..                  ..     .
                .2                  .  F .
                |\                  |\  .
                | \                 | \.
            B   |  \   F         B  | /.  E
                | A \               |/  .
           .....|____\..... E0      .O   .
               O.     .1           ..     .
                .      .          . .  D   .
            C   .   D   .   E    .  .
                .        .      . C .
                .                   .
               E1                  E1


    Let P0,P1,P2 be the three defining vertices of a triangle with E0 = P1 - P0 and E1 = P2 - P0.
    Let P3, D1 by the origin and the vector of a line segment respectively.

    Let DS = P3 - P0

    Let TG1, TE0, TE1 represent the co-ordinates in their respective reference frames of the extrapolated point of contact between the line(segment) and the plane(triangle).

        [D1•D1  D1•E0  D1•E1] [TG1]     [DS•D1]
        [D1•E0  E0•E0  E0•E1] [TE0]  =  [DS•E0]
        [D1•E1  E0•E1  E1•E1] [TE1]     [DS•E1]

        Let C(ij) be the cofactor matrix of row i and column j We know that the determinant can be computed by adding: det = (D1•E0)•C01 + (E0•E0)•C11 + (E0•E1)•C12

        Let K = 1.0 / det

        [TG1]     [C00  C01  C02] [K_(DS•D1,DIM)]
        [TE0]  =  [C01  C11  C12] [K_(DS•E0,DIM)]
        [TE1]     [C02  C12  C22] [K_(DS•E1,DIM)]

    However, it is known that TG1 ε [ 0, 1], TE0 ε [ 0, 1], TE1 ε [ 0, 1], and (TE0 + TE1) ε [ 0, 1]
    These limitations present us with these possible cases.

    [1] TG1 ε (-∞, 0)
        If the given condition is met, then the line segment is tested against the specified triangle edge.
            Triangle Edge 2 • (TE0 + TE1) ε ( 1, ∞)
            Triangle Edge 0 • TE0 ε (-∞, 0)
            Triangle Edge 1 • TE1 ε (-∞, 0)
    [2] TG1 ε [ 0, 1]
       [A] (TE0 + TE1) ε (-∞, 1]
            Triangle Edge 0 • TE0 ε (-∞, 0)
            Triangle Edge 1 • TE1 ε (-∞, 0)
            Intersection • TE0 ε [ 0, 1], TE1 ε [ 0, 1]
       [B] (TE0 + TE1) ε ( 1, ∞)
            Triangle Edge 2
            Triangle Edge 0 • TE0 ε (-∞, 0)
            Triangle Edge 1 • TE1 ε (-∞, 0)
    [3] TG1 ε ( 1, ∞)
        If the given condition is met, then the line segment is tested against the specified triangle edge.
            Triangle Edge 2 • (TE0 + TE1) ε ( 1, ∞)
            Triangle Edge 0 • TE0 ε (-∞, 0)
            Triangle Edge 1 • TE1 ε (-∞, 0)

    If the triangle and the segment happen to be parallel then,
      The distance between the line segment and the triangle can be found by checking the distance of the segment against the three triangle edges (line segments) and the triangle
      against the two end points of the line segment.  The resulting minimal value (with any corresponding extra information) will be the desired result.
*/

#include "TgS COLLISION/TgS Collision - Plane-Point.inl"

#if !defined (ENABLE_RELOAD_GUARD_LINEAR)
    #define ENABLE_RELOAD_GUARD_LINEAR

    #define TEMPLATE__PRIM_0_CAP_0 0
    #define TEMPLATE__PRIM_0_CAP_1 0
    #define TEMPLATE__PRIM_0 LR
        #include __FILE__

    #define TEMPLATE__PRIM_0_CAP_0 1
    #define TEMPLATE__PRIM_0_CAP_1 0
    #define TEMPLATE__PRIM_0 LR
        #include __FILE__

    #define TEMPLATE__PRIM_0_CAP_0 1
    #define TEMPLATE__PRIM_0_CAP_1 1
    #define TEMPLATE__PRIM_0 LR
        #include __FILE__

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

/* ---- FCNI_VO(tgCO_ST_ClosestSq_PM) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
VEC_T(1) FCNI_VO(tgCO_ST_ClosestSq_PM)( VEC_T(1,PC) pvET0, VEC_T(1,PC) pvET1, VEC_T(1,PC) pvLN0_T0, VEC_OBJ_T(TgSTRI,CPC) psST0, VEC_T(1,C) vS0, VEC_T(1,C) vD0 )
{
    TgSINT_E32                          iTest = 0;

    TgERROR( FCN_VO(tgGM_ST_Is_Valid)( psST0 ) && FCN_V(tgMH_Is_Valid_Point)( vS0 ) && FCN_V(tgMH_Is_Valid_Vector)( vD0 ) );

    /* == Perform the requested primitive-primitive data function. == */

    /* If the linear is not parallel to the triangle, check to see if the two geometries intersect each other. */

    if (!FCN_V(tgMH_Is_NR0)( FCN_V(tgMH_DOT)( vD0, psST0->m_sCT.m_sET.m_sPT.m_vNormal ) ))
    {
        TgRESULT_C iResult = FCNI_VO(tgCO_ET_Intersect_PM)( pvET0, pvET1, pvLN0_T0, &psST0->m_sCT.m_sET, vS0, vD0 );

        if (TgSUCCEEDED(iResult) || (TgFAILED(iResult) && KTgE_NO_INTERSECT != iResult))
        {
            /* Some property of the triangle was illegal - return back an error state. */
            /* The linear may have intersected the triangle. */

            return (FCN_V(tgMH_SET1)( -VAR_K(KTgMAX) ));
        };
    }

    iTest = 0;

    {
        /* Determine which feature tests need to be executed given the linear parameters. */

    #if 1 == TEMPLATE__PRIM_0_CAP_0
        VEC_T(1,C)                          vNEG_EPS = FCN_V(tgMH_SET1)( -VAR_K(KTgROOT_EPS) );
        VEC_T(1,C)                          vEPS = FCN_V(tgMH_SET1)( VAR_K(KTgROOT_EPS) );

        VEC_T(1,C)                          vK00 = FCN_VO(tgCO_PN_Dist_PT)( psST0->m_avPlane + 0, vS0 );
        VEC_T(1,C)                          vK01 = FCN_VO(tgCO_PN_Dist_PT)( psST0->m_avPlane + 1, vS0 );
        VEC_T(1,C)                          vK02 = FCN_VO(tgCO_PN_Dist_PT)( psST0->m_avPlane + 2, vS0 );

        VEC_T(1,C)                          vCMP_00 = FCN_V(tgMH_CMP_LT)( vK00, vEPS );
        TgBOOL_C                            bCMP_00 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_00 );
        VEC_T(1,C)                          vCMP_01 = FCN_V(tgMH_CMP_LT)( vK01, vEPS );
        TgBOOL_C                            bCMP_01 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_01 );
        VEC_T(1,C)                          vCMP_02 = FCN_V(tgMH_CMP_LT)( vK02, vEPS );
        TgBOOL_C                            bCMP_02 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_02 );

        VEC_T(1,C)                          vCMP_03 = FCN_V(tgMH_CMP_GT)( vK00, vNEG_EPS );
        TgBOOL_C                            bCMP_03 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_03 );
        VEC_T(1,C)                          vCMP_04 = FCN_V(tgMH_CMP_GT)( vK01, vNEG_EPS );
        TgBOOL_C                            bCMP_04 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_04 );
        VEC_T(1,C)                          vCMP_05 = FCN_V(tgMH_CMP_GT)( vK02, vNEG_EPS );
        TgBOOL_C                            bCMP_05 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_05 );

    #if 1 == TEMPLATE__PRIM_0_CAP_1
        VEC_T(1,C)                          vS2 = FCN_V(tgMH_ADD)( vS0, vD0 );
        VEC_T(1,C)                          vK10 = FCN_VO(tgCO_PN_Dist_PT)( psST0->m_avPlane + 0, vS2 );
        VEC_T(1,C)                          vK11 = FCN_VO(tgCO_PN_Dist_PT)( psST0->m_avPlane + 1, vS2 );
        VEC_T(1,C)                          vK12 = FCN_VO(tgCO_PN_Dist_PT)( psST0->m_avPlane + 2, vS2 );

        VEC_T(1,C)                          vCMP_10 = FCN_V(tgMH_CMP_LT)( vK10, vEPS );
        TgBOOL_C                            bCMP_10 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_10 );
        VEC_T(1,C)                          vCMP_11 = FCN_V(tgMH_CMP_LT)( vK11, vEPS );
        TgBOOL_C                            bCMP_11 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_11 );
        VEC_T(1,C)                          vCMP_12 = FCN_V(tgMH_CMP_LT)( vK12, vEPS );
        TgBOOL_C                            bCMP_12 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_12 );

        VEC_T(1,C)                          vCMP_13 = FCN_V(tgMH_CMP_GT)( vK10, vNEG_EPS );
        TgBOOL_C                            bCMP_13 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_13 );
        VEC_T(1,C)                          vCMP_14 = FCN_V(tgMH_CMP_GT)( vK11, vNEG_EPS );
        TgBOOL_C                            bCMP_14 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_14 );
        VEC_T(1,C)                          vCMP_15 = FCN_V(tgMH_CMP_GT)( vK12, vNEG_EPS );
        TgBOOL_C                            bCMP_15 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_15 );

        iTest |= (bCMP_13 && bCMP_14 && bCMP_15) ? (1 << 4) : 0;

        iTest |= bCMP_10 ? (1 << 0) : 0;
        iTest |= bCMP_11 ? (1 << 1) : 0;
        iTest |= bCMP_12 ? (1 << 2) : 0;
    #else
        VEC_T(1,C)                          vK10 = FCN_V(tgMH_DOT)( psST0->m_avPlane[0].m_vNormal, vD0 );
        VEC_T(1,C)                          vK11 = FCN_V(tgMH_DOT)( psST0->m_avPlane[1].m_vNormal, vD0 );
        VEC_T(1,C)                          vK12 = FCN_V(tgMH_DOT)( psST0->m_avPlane[2].m_vNormal, vD0 );

        VEC_T(1,C)                          vCMP_10 = FCN_V(tgMH_CMP_LT)( vK10, vNEG_EPS );
        TgBOOL_C                            bCMP_10 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_10 );
        VEC_T(1,C)                          vCMP_11 = FCN_V(tgMH_CMP_LT)( vK11, vNEG_EPS );
        TgBOOL_C                            bCMP_11 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_11 );
        VEC_T(1,C)                          vCMP_12 = FCN_V(tgMH_CMP_LT)( vK12, vNEG_EPS );
        TgBOOL_C                            bCMP_12 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_12 );

        iTest |= bCMP_10 ? (1 << 0) : 0;
        iTest |= bCMP_11 ? (1 << 1) : 0;
        iTest |= bCMP_12 ? (1 << 2) : 0;
    #endif

        iTest |= (bCMP_03 && bCMP_04 && bCMP_05) ? (1 << 3) : 0;

        iTest |= bCMP_00 ? (1 << 0) : 0;
        iTest |= bCMP_01 ? (1 << 1) : 0;
        iTest |= bCMP_02 ? (1 << 2) : 0;

    #else
        VEC_T(1,C)                          vK0 = FCN_V(tgMH_DOT)( psST0->m_avPlane[0].m_vNormal, vD0 );
        VEC_T(1,C)                          vK1 = FCN_V(tgMH_DOT)( psST0->m_avPlane[1].m_vNormal, vD0 );
        VEC_T(1,C)                          vK2 = FCN_V(tgMH_DOT)( psST0->m_avPlane[2].m_vNormal, vD0 );

        iTest |= !FCN_V(tgMH_Is_NR0)( FCN_V(tgMH_ABS)( vK0 ) ) ? (1 << 0) : 0;
        iTest |= !FCN_V(tgMH_Is_NR0)( FCN_V(tgMH_ABS)( vK1 ) ) ? (1 << 1) : 0;
        iTest |= !FCN_V(tgMH_Is_NR0)( FCN_V(tgMH_ABS)( vK2 ) ) ? (1 << 2) : 0;
    #endif
    }
    {
        VEC_T(1)                            vET0, vET1, vLN0_T0, vT0, vT1, vDistSq;

        /* Test the first capped point if it is contained within the triangle space. */

        vET0    = FCN_V(tgMH_SET1)(VAR_K(KTgMAX));
        vET1    = FCN_V(tgMH_SET1)(VAR_K(KTgMAX));
        vLN0_T0 = FCN_V(tgMH_SET1)(VAR_K(KTgMAX));
        vDistSq = FCN_V(tgMH_SET1)(VAR_K(KTgMAX));

        if (0 != (iTest & (1 << 3)))
        {
            VEC_T(1,C)                          vTest = FCN_VO(tgCO_ET_ClosestSq_PM_PT)( &vT0, &vT1, &psST0->m_sCT.m_sET, vS0 );
            VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_LT)( vTest, vDistSq );

            if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_0 ))
            {
                vDistSq = vTest;
                vLN0_T0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
                vET0 = vT0;
                vET1 = vT1;
            };
        };

        /* Test the second capped point if it is contained within the triangle space. */

        if (0 != (iTest & (1 << 4)))
        {
            VEC_T(1,C)                          vS2 = FCN_V(tgMH_ADD)( vS0, vD0 );
            VEC_T(1,C)                          vTest = FCN_VO(tgCO_ET_ClosestSq_PM_PT)( &vT0, &vT1, &psST0->m_sCT.m_sET, vS2 );
            VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_LT)( vTest, vDistSq );

            if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_0 ))
            {
                vDistSq = vTest;
                vLN0_T0 = FCN_V(tgMH_SET1)( TYPE_K(1) );
                vET0 = vT0;
                vET1 = vT1;
            };
        };

        if (0 != (iTest & (3 << 3)))
        {
            return (vDistSq);
        };

        TgERROR( 0 != iTest );

        /* Check minimal distance between linear and edge 0, if any part crosses into the negative space of the edge plane. */

        if (0 != (iTest & (1 << 0)))
        {
            VEC_T(1,C)                          vK0 = psST0->m_sCT.m_sET.m_sPT.m_avPoint[0];
            VEC_T(1,C)                          vK1 = psST0->m_sCT.m_sET.m_avEdge[0];
            VEC_T(1,C)                          vTest = FCNI_VO(tgCO_LR11_ClosestSq_PM)( &vT0, &vT1, vK0, vK1, vS0, vD0 );
            VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_LT)( vTest, vDistSq );

            if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_0 ))
            {
                vDistSq = vTest;
                vLN0_T0 = vT1;
                vET0 = vT0;
                vET1 = FCN_V(tgMH_SET1)( TYPE_K(0) );
            };
        };

        /* Check minimal distance between linear and edge 1, if any part crosses into the negative space of the edge plane. */

        if (0 != (iTest & (1 << 1)))
        {
            VEC_T(1,C)                          vK0 = psST0->m_sCT.m_sET.m_sPT.m_avPoint[1];
            VEC_T(1,C)                          vK1 = psST0->m_sCT.m_sET.m_avEdge[1];
            VEC_T(1,C)                          vTest = FCNI_VO(tgCO_LR11_ClosestSq_PM)( &vT0, &vT1, vK0, vK1, vS0, vD0 );
            VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_LT)( vTest, vDistSq );

            if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_0 ))
            {
                vDistSq = vTest;
                vLN0_T0 = vT1;
                vET0 = FCN_V(tgMH_SUB)( FCN_V(tgMH_SET1)( TYPE_K(1) ), vT0 );
                vET1 = vT0;
            };
        };

        /* Check minimal distance between linear and edge 2, if any part crosses into the negative space of the edge plane. */

        if (0 != (iTest & (1 << 2)))
        {
            VEC_T(1,C)                          vK0 = psST0->m_sCT.m_sET.m_sPT.m_avPoint[2];
            VEC_T(1,C)                          vK1 = psST0->m_sCT.m_sET.m_avEdge[2];
            VEC_T(1,C)                          vTest = FCNI_VO(tgCO_LR11_ClosestSq_PM)( &vT0, &vT1, vK0, vK1, vS0, vD0 );
            VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_LT)( vTest, vDistSq );

            if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_0 ))
            {
                vDistSq = vTest;
                vLN0_T0 = vT1;
                vET0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
                vET1 = FCN_V(tgMH_SUB)( FCN_V(tgMH_SET1)( TYPE_K(1) ), vT0 );
            };
        };

        *pvET0 = vET0;
        *pvET1 = vET1;
        *pvLN0_T0 = vLN0_T0;

        return (vDistSq);
    };
}


/* ---- FCNI_VO(tgCO_ET_Intersect_PM) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCNI_VO(tgCO_ET_Intersect_PM)( VEC_T(1,PC) pvET0, VEC_T(1,PC) pvET1, VEC_T(1,PC) pvLN0_T0, VEC_OBJ_T(TgETRI,CPC) psET0, VEC_T(1,C) vS0, VEC_T(1,C) vD0 )
{
    VEC_T(1,C)                          vDS = FCN_V(tgMH_SUB)( vS0, psET0->m_sPT.m_avPoint[0] );
    VEC_T(1,C)                          vDS_DS = FCN_V(tgMH_LSQ)( vDS );
    VEC_T(1)                            vET0, vET1, vT0, vD1_N;
    VEC_T(1)                            vK0, vK1, vK2, vK3, vK4, vK5, vK6;
    VEC_T(1)                            vCMP_0, vCMP_1, vCMP_2, vCMP_3, vCMP_4, vCMP_5;

    TgERROR( FCN_VO(tgGM_ET_Is_Valid)( psET0 ) && FCN_V(tgMH_Is_Valid_Point)( vS0 ) && FCN_V(tgMH_Is_Valid_Vector)( vD0 ) );

    if (FCN_V(tgMH_Is_NR0)( vDS_DS ))
    {
        /* Quick Out - the segment origin is within tolerance of triangle origin. */

        *pvET0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
        *pvET1 = FCN_V(tgMH_SET1)( TYPE_K(0) );
        *pvLN0_T0 = FCN_V(tgMH_SET1)( TYPE_K(0) );

        return (KTgS_OK);
    };

    vD1_N = FCN_V(tgMH_DOT)( vD0, psET0->m_sPT.m_vNormal );
    vK0 = FCN_V(tgMH_ABS)( vD1_N );

    if (FCN_V(tgMH_Is_NR0)( vK0 ))
    {
        /* Linear is parallel to the plane of the triangle. */
        return (KTgE_NO_INTERSECT);
    };

    vK1 = FCN_V(tgMH_DIV)( FCN_V(tgMH_SET1)( TYPE_K(1) ), vD1_N );
    vK2 = FCN_V(tgMH_DOT)( vDS, psET0->m_sPT.m_vNormal );

    vT0 = FCN_V(tgMH_MUL)( vK1, vK2 );

    vCMP_0 = FCN_V(tgMH_CMP_LT)( vT0, FCN_V(tgMH_SET1)( TYPE_K(0) ) );
    vCMP_1 = FCN_V(tgMH_CMP_GT)( vT0, FCN_V(tgMH_SET1)( TYPE_K(1) ) );

    if ((TEMPLATE__PRIM_0_CAP_0 && FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_0 )) || (TEMPLATE__PRIM_0_CAP_1 && FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_1 )))
    {
        return (KTgE_NO_INTERSECT);
    };

    vK3 = FCN_V(tgMH_CX)( psET0->m_avEdge[1], vDS );
    vK4 = FCN_V(tgMH_DOT)( vD0, vK3 );

    vET0 = FCN_V(tgMH_MUL)( vK1, vK4 );

    vCMP_2 = FCN_V(tgMH_CMP_LT)( vET0, FCN_V(tgMH_SET1)( TYPE_K(0) ) );
    vCMP_3 = FCN_V(tgMH_CMP_GT)( vET0, FCN_V(tgMH_SET1)( TYPE_K(1) ) );

    if ((FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_2 )) || (FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_3 )))
    {
        return (KTgE_NO_INTERSECT);
    };

    vK5 = FCN_V(tgMH_CX)( psET0->m_avEdge[0], vDS );
    vK6 = FCN_V(tgMH_DOT)( vD0, vK5 );

    vET1 = FCN_V(tgMH_MUL)( vK1, vK6 );

    vCMP_4 = FCN_V(tgMH_CMP_LT)( vET1, FCN_V(tgMH_SET1)( TYPE_K(0) ) );
    vCMP_5 = FCN_V(tgMH_CMP_GT)( FCN_V(tgMH_ADD)( vET0, vET1 ), FCN_V(tgMH_SET1)( TYPE_K(1) ) );

    if ((FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_4 )) || (FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_5 )))
    {
        return (KTgE_NO_INTERSECT);
    };

    *pvET0 = vET0;
    *pvET1 = vET1;
    *pvLN0_T0 = vT0;

    return (KTgS_OK);
}


/* ---- FCNI_VO(tgCO_ST_Clip_PM_F) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCNI_VO(tgCO_ST_Clip_PM_F)( VEC_T(1,P) pvLN0, VEC_T(1,P) pvLN1, TgSINT_E32_PC  piCode, VEC_OBJ_T(TgSTRI,CPC) psST0, VEC_T(1,C) vS0, VEC_T(1,C) vD0 )
{
    VEC_T(1)                            vT0, vT1, vSEL_0, vSEL_1;
    TgSINT_E32                          iCode = 0;

    vT0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
    vT1 = FCN_V(tgMH_SET1)( TYPE_K(0) );

    for (TgRSIZE uiEdge = 0; uiEdge < 3; ++uiEdge)
    {
        VEC_T(1,C)                          vDist = FCN_VO(tgCO_PN_Dist_PT)( psST0->m_avPlane + uiEdge, vS0 );
        VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_LT)( vDist, FCN_V(tgMH_SET1)( TYPE_K(0) ) );

        VEC_T(1,C)                          vD1_N = FCN_V(tgMH_DOT)( psST0->m_avPlane[uiEdge].m_vNormal, vD0 );

        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_0 ))
        {
            /*  Check to see if its impossible for this linear to intersect the triangle space by seeing if it rests entirely in the exterior half-space of the */
            /* triangle-edge normal space.  This can occur if the linear is near parallel to the resulting partitioning plane, if the linear is start-capped and directed */
            /* away from the plane and if its end-capped and the end point is also behind the plane. */

            VEC_T(1,C)                          vX0 = FCN_V(tgMH_ABS)( vD1_N );
            VEC_T(1,C)                          vCMP_4 = FCN_V(tgMH_CMP_LT)( vD1_N, FCN_V(tgMH_SET1)( TYPE_K(0) ) );

            VEC_T(1,C)                          vX1 = FCN_V(tgMH_ADD)( vD1_N, vDist );
            VEC_T(1,C)                          vCMP_5 = FCN_V(tgMH_CMP_LT)( vX1, FCN_V(tgMH_SET1)( TYPE_K(0) ) );

            if (FCN_V(tgMH_Is_NR0)( vX0 ) || (TEMPLATE__PRIM_0_CAP_0 && FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_4 )) || (TEMPLATE__PRIM_0_CAP_1 && FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_5 )))
            {
                *piCode = 0;
                return (KTgE_NO_INTERSECT);
            };
        };

        {
            VEC_T(1,C)                          vCMP_1 = FCN_V(tgMH_CMP_GT)( vD1_N, FCN_V(tgMH_SET1)( VAR_K(KTgROOT_EPS) ) );
            TgBOOL_C                            bCMP_1 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_1 );
            VEC_T(1,C)                          vCMP_2 = FCN_V(tgMH_CMP_LT)( vD1_N, FCN_V(tgMH_SET1)( -VAR_K(KTgROOT_EPS) ) );
            TgBOOL_C                            bCMP_2 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_2 );

            if (!bCMP_1 && !bCMP_2)
            {
                continue;
            };

            if (bCMP_1)
            {
                vSEL_0 = FCN_V(tgMH_CMP_GT)( vDist, vD1_N );
                vSEL_1 = FCN_V(tgMH_CMP_LT)( vDist, FCN_V(tgMH_SET1)( TYPE_K(0) ) );
            }
            else
            {
                vSEL_0 = FCN_V(tgMH_CMP_LT)( vDist, vD1_N );
                vSEL_1 = FCN_V(tgMH_CMP_GT)( vDist, FCN_V(tgMH_SET1)( TYPE_K(0) ) );
            };

            {
                VEC_T(1,C)                          vK0 = FCN_V(tgMH_DIV)( vDist, vD1_N );
                TgBOOL_C                            bSEL_0 = TEMPLATE__PRIM_0_CAP_1 && FCN_V(tgMH_CMP_ALL_TO_BOOL)( vSEL_0 );
                VEC_T(1,C)                          vK1 = bSEL_0 ? FCN_V(tgMH_SET1)( TYPE_K(1) ) : vK0;
                TgBOOL_C                            bSEL_1 = TEMPLATE__PRIM_0_CAP_0 && FCN_V(tgMH_CMP_ALL_TO_BOOL)( vSEL_1 );
                VEC_T(1,C)                          vTest = bSEL_1 ? FCN_V(tgMH_SET1)( TYPE_K(0) ) : vK1;

                if (bCMP_1)
                {
                    if (iCode & 1)
                    {
                        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vT0, vTest ) ))
                        {
                            vT0 = vTest;
                            iCode &= FCN_VO(tgGM_ST_Test_Edge)( psST0, uiEdge ) ? ~0 : ~4;
                        };
                    }
                    else
                    {
                        vT0 = vTest;
                        iCode |= FCN_VO(tgGM_ST_Test_Edge)( psST0, uiEdge ) ? (1 + 4) : 1;
                    };
                }
                else
                {
                    if (iCode & 2)
                    {
                        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vT1, vTest ) ))
                        {
                            vT1 = vTest;
                            iCode &= FCN_VO(tgGM_ST_Test_Edge)( psST0, uiEdge ) ? ~0 : ~8;
                        };
                    }
                    else
                    {
                        vT1 = vTest;
                        iCode |= FCN_VO(tgGM_ST_Test_Edge)( psST0, uiEdge ) ? (2 + 8) : 2;
                    };
                };
            };
        };
    };

    TgERROR( iCode == 3 );

    *pvLN0 = vT0;
    *pvLN1 = vT1;
    *piCode = iCode;

    return (KTgS_OK);
}


/* ---- FCNI_VO(tgCO_ST_Clip_F) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCNI_VO(tgCO_ST_Clip_F)( VEC_OBJ_T(STg2_CO_Clip_List,PC) psCL, TgSINT_E32_PC  piCode, VEC_OBJ_T(TgSTRI,CPC) psST0, VEC_T(1,C) vS0, VEC_T(1,C) vD0 )
{
    VEC_T(1)                            vT0, vT1;
    TgSINT_E32                          iCode;
    TgRESULT                            iResult;

    if (psCL->m_nuiMax < 2)
    {
        return (KTgE_FAIL);
    };

    iResult = FCNI_VO(tgCO_ST_Clip_PM_F)( &vT0, &vT1, &iCode, psST0, vS0, vD0 );

    *piCode = iCode;

    if (TgFAILED( iResult ) || 0 == (iCode & 12))
    {
        psCL->m_nuiPoint = 0;
        return (iResult);
    };

    if (12 != (iCode & 12))
    {
        VEC_T(1,C)                          vX0 = FCN_V(tgMH_SUB)( vT0, vT1 );
        VEC_T(1,C)                          vX1 = FCN_V(tgMH_ABS)( vX0 );

        if (FCN_V(tgMH_Is_NR0)( vX1 ))
        {
            VEC_T(1,C)                          vK0 = FCN_V(tgMH_MUL)( vT0, vD0 );

            psCL->m_avPoint[0] = FCN_V(tgMH_ADD)( vS0, vK0 );
            psCL->m_nuiPoint = 1;
        }
        else
        {
            VEC_T(1,C)                          vK0 = FCN_V(tgMH_MUL)( vT0, vD0 );
            VEC_T(1,C)                          vK1 = FCN_V(tgMH_MUL)( vT1, vD0 );

            psCL->m_avPoint[0] = FCN_V(tgMH_ADD)( vS0, vK0 );
            psCL->m_avPoint[1] = FCN_V(tgMH_ADD)( vS0, vK1 );
            psCL->m_nuiPoint = 2;
        };
    }
    else if (4 != (iCode & 4))
    {
        VEC_T(1,C)                          vK0 = FCN_V(tgMH_MUL)( vT0, vD0 );

        psCL->m_avPoint[0] = FCN_V(tgMH_ADD)( vS0, vK0 );
        psCL->m_nuiPoint = 1;
    }
    else if (8 != (iCode & 8))
    {
        VEC_T(1,C)                          vK0 = FCN_V(tgMH_MUL)( vT1, vD0 );

        psCL->m_avPoint[0] = FCN_V(tgMH_ADD)( vS0, vK0 );
        psCL->m_nuiPoint = 1;
    };

    return (KTgS_OK);
}


/* ---- FCNI_VO(tgCO_ST_Clip) ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCNI_VO(tgCO_ST_Clip)( VEC_OBJ_T(STg2_CO_Clip_List,PC) psCL, VEC_OBJ_T(TgSTRI,CPC) psST0, VEC_T(1,C) vS0, VEC_T(1,C) vD0 )
{
    VEC_T(1)                            vT0, vT1;
    TgSINT_E32                          iCode;
    TgRESULT                            iResult;

    if (psCL->m_nuiMax < 2)
    {
        return (KTgE_FAIL);
    };

    iResult = FCNI_VO(tgCO_ST_Clip_PM_F)( &vT0, &vT1, &iCode, psST0, vS0, vD0 );

    if (TgFAILED( iResult ))
    {
        psCL->m_nuiPoint = 0;
        return (iResult);
    }
    else
    {
        VEC_T(1,C)                          vX0 = FCN_V(tgMH_SUB)( vT0, vT1 );
        VEC_T(1,C)                          vX1 = FCN_V(tgMH_ABS)( vX0 );

        if (FCN_V(tgMH_Is_NR0)( vX1 ))
        {
            VEC_T(1,C)                          vK0 = FCN_V(tgMH_MUL)( vT0, vD0 );

            psCL->m_avPoint[0] = FCN_V(tgMH_ADD)( vS0, vK0 );
            psCL->m_nuiPoint = 1;
        }
        else
        {
            VEC_T(1,C)                          vK0 = FCN_V(tgMH_MUL)( vT0, vD0 );
            VEC_T(1,C)                          vK1 = FCN_V(tgMH_MUL)( vT1, vD0 );

            psCL->m_avPoint[0] = FCN_V(tgMH_ADD)( vS0, vK0 );
            psCL->m_avPoint[1] = FCN_V(tgMH_ADD)( vS0, vK1 );
            psCL->m_nuiPoint = 2;
        };

        return (KTgS_OK);
    };
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/*# !defined (ENABLE_RELOAD_GUARD_LINEAR) */
#endif
