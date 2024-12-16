/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Triangle-Triangle.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

/** Triangle Definition: T0(α,β) = P0 + α•E0 + β•E1 | α ε [ 0, 1], β ε [ 0, 1], (α + β) ε [0, 1]

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
  
      These regions define the closest feature of the triangle when contained in their area.  The point is projected onto the triangle plane, and the region that contains the
    point is determined.  It is then a simple matter to calculate the resulting distance to the triangle for the point.
*/

#include "TgS COLLISION/TgS Collision - Triangle [Util].inl"
#include "TgS COLLISION/TgS Collision - Plane-Point.inl"
#include "TgS COLLISION/TgS Collision - Triangle-Triangle.inl"

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

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

static TgRESULT                             FCN_VO(tgCO_ST_Internal_CoP_ST)( VEC_OBJ_T(STg2_CO_Packet,PC), VEC_OBJ_T(STg2_CO_Clip_List,PC), VEC_T(1,C), VEC_T(1,C) );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- FCN_VO(tgCO_ST_ClosestSq_PM_ST) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
VEC_T(1) FCN_VO(tgCO_ST_ClosestSq_PM_ST)( VEC_T(1,P) pvST00, VEC_T(1,P) pvST01, VEC_T(1,P) pvST10, VEC_T(1,P) pvST11, VEC_OBJ_T(TgSTRI,CPC) psST0, VEC_OBJ_T(TgSTRI,CPC) psST1 )
{
    VEC_T(1)                            vDistSq, vET00, vET01, vET10, vET11, vTestSq, vT0, vT1, vG1;

    /* == Test Triangle 0 Edges against Triangle 1 == */

    vDistSq = FCN_VO(tgCO_ST_ClosestSq_PM_LR11)( &vET00, &vET01, &vET10, psST0, psST1->m_sCT.m_sET.m_sPT.m_avPoint[0], psST1->m_sCT.m_sET.m_avEdge[0] );
    vET11 = FCN_V(tgMH_SET1)( TYPE_K(0) );

    vTestSq = FCN_VO(tgCO_ST_ClosestSq_PM_LR11)( &vT0, &vT1, &vG1, psST0, psST1->m_sCT.m_sET.m_sPT.m_avPoint[1], psST1->m_sCT.m_sET.m_avEdge[1] );
    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTestSq, vDistSq ) ))
    {
        vDistSq = vTestSq;
        vET00 = vT0;
        vET01 = vT1;
        vET10 = FCN_V(tgMH_SUB)( FCN_V(tgMH_SET1)( TYPE_K(1) ), vG1 );
        vET11 = vG1;
    };

    vTestSq = FCN_VO(tgCO_ST_ClosestSq_PM_LR11)( &vT0, &vT1, &vG1, psST0, psST1->m_sCT.m_sET.m_sPT.m_avPoint[2], psST1->m_sCT.m_sET.m_avEdge[2] );
    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTestSq, vDistSq ) ))
    {
        vDistSq = vTestSq;
        vET00 = vT0;
        vET01 = vT1;
        vET10 = FCN_V(tgMH_SET1)( TYPE_K(0) );
        vET11 = FCN_V(tgMH_SUB)( FCN_V(tgMH_SET1)( TYPE_K(1) ), vG1 );
    };

    /* == Test Triangle 1 Edges against Triangle 0 == */

    vTestSq = FCN_VO(tgCO_ST_ClosestSq_PM_LR11)( &vT0, &vT1, &vG1, psST1, psST0->m_sCT.m_sET.m_sPT.m_avPoint[0], psST0->m_sCT.m_sET.m_avEdge[0] );
    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTestSq, vDistSq ) ))
    {
        vDistSq = vTestSq;
        vET00 = vG1;
        vET01 = FCN_V(tgMH_SET1)( TYPE_K(0) );
        vET10 = vT0;
        vET11 = vT1;
    };

    vTestSq = FCN_VO(tgCO_ST_ClosestSq_PM_LR11)( &vT0, &vT1, &vG1, psST1, psST0->m_sCT.m_sET.m_sPT.m_avPoint[1], psST0->m_sCT.m_sET.m_avEdge[1] );
    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTestSq, vDistSq ) ))
    {
        vDistSq = vTestSq;
        vET00 = FCN_V(tgMH_SUB)( FCN_V(tgMH_SET1)( TYPE_K(1) ), vG1 );
        vET01 = vG1;
        vET10 = vT0;
        vET11 = vT1;
    };

    vTestSq = FCN_VO(tgCO_ST_ClosestSq_PM_LR11)( &vT0, &vT1, &vG1, psST1, psST0->m_sCT.m_sET.m_sPT.m_avPoint[2], psST0->m_sCT.m_sET.m_avEdge[2] );
    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTestSq, vDistSq ) ))
    {
        vDistSq = vTestSq;
        vET00 = FCN_V(tgMH_SET1)( TYPE_K(0) );
        vET01 = FCN_V(tgMH_SUB)( FCN_V(tgMH_SET1)( TYPE_K(1) ), vG1 );
        vET10 = vT0;
        vET11 = vT1;
    };

    /* == Return Values == */

    *pvST00 = vET00;
    *pvST01 = vET01;
    *pvST10 = vET10;
    *pvST11 = vET11;

    return (vDistSq);
}


/* ---- FCN_VO(tgCO_ST_Test_ST) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL FCN_VO(tgCO_ST_Test_ST)( VEC_OBJ_T(TgSTRI,CPC) psST0, VEC_OBJ_T(TgSTRI,CPC) psST1 )
{
    VEC_T(1)                            vMin, vMax;

    VEC_T(1,C)                          vTriD0 = FCN_V(tgMH_DOT)( psST0->m_sCT.m_sET.m_sPT.m_vNormal, psST0->m_sCT.m_sET.m_sPT.m_avPoint[0] );
    VEC_T(1,C)                          vTriD1 = FCN_V(tgMH_DOT)( psST1->m_sCT.m_sET.m_sPT.m_vNormal, psST1->m_sCT.m_sET.m_sPT.m_avPoint[0] );
    VEC_T(1,C)                          vK0 = FCN_V(tgMH_CX)( psST0->m_sCT.m_sET.m_sPT.m_vNormal, psST1->m_sCT.m_sET.m_sPT.m_vNormal );
    VEC_T(1,C)                          vZR = FCN_V(tgMH_SET1)( TYPE_K(0) );

    /* == Triangle Normal == */

    FCN_VO(tgGM_ST_Project)( &vMin, &vMax, psST1, psST0->m_sCT.m_sET.m_sPT.m_vNormal );
    
    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vMin, vTriD0 ) ) || FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vMax, vTriD0 ) ))
    {
        return (false);
    };

    FCN_VO(tgGM_ST_Project)( &vMin, &vMax, psST0, psST1->m_sCT.m_sET.m_sPT.m_vNormal );

    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vMin, vTriD1 ) ) || FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vMax, vTriD1 ) ))
    {
        return (false);
    };

    /* == Cross-Product Normal == */

    if (!FCN_V(tgMH_Is_NR0)( FCN_V(tgMH_LSQ)( vK0 ) ))
    {
        VEC_T(1)                            vNormal;

        for (TgRSIZE iE0 = 0; iE0 < 9; ++iE0)
        {
            vNormal = FCN_V(tgMH_CX)( psST0->m_sCT.m_sET.m_avEdge[(iE0 & 3)], psST1->m_sCT.m_sET.m_avEdge[(iE0 >> 3)] );

            if (FCN_VO(tgCO_PT_Is_Seperating_Axis_PT)( vNormal, &psST0->m_sCT.m_sET.m_sPT, &psST1->m_sCT.m_sET.m_sPT ))
            {
                return (false);
            };
        };
    }
    else
    {
        /* Normal extruded space of triangle 0 */

        VEC_T(1,C)                          vDist_00 =  FCN_VO(tgCO_PN_Sign_Dist_PT)(psST0->m_avPlane + 0, psST1->m_sCT.m_sET.m_sPT.m_avPoint[0]);
        VEC_T(1,C)                          vDist_01 =  FCN_VO(tgCO_PN_Sign_Dist_PT)(psST0->m_avPlane + 0, psST1->m_sCT.m_sET.m_sPT.m_avPoint[1]);
        VEC_T(1,C)                          vDist_02 =  FCN_VO(tgCO_PN_Sign_Dist_PT)(psST0->m_avPlane + 0, psST1->m_sCT.m_sET.m_sPT.m_avPoint[2]);

        TgBOOL_C                            bCMP_00 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vDist_00, vZR ) );
        TgBOOL_C                            bCMP_01 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vDist_01, vZR ) );
        TgBOOL_C                            bCMP_02 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vDist_02, vZR ) );

        if (bCMP_00 && bCMP_01 && bCMP_02)
        {
            return (false);
        }
        else
        {
            VEC_T(1,C)                          vDist_10 = FCN_VO(tgCO_PN_Sign_Dist_PT)( psST0->m_avPlane + 1, psST1->m_sCT.m_sET.m_sPT.m_avPoint[0] );
            VEC_T(1,C)                          vDist_11 = FCN_VO(tgCO_PN_Sign_Dist_PT)( psST0->m_avPlane + 1, psST1->m_sCT.m_sET.m_sPT.m_avPoint[1] );
            VEC_T(1,C)                          vDist_12 = FCN_VO(tgCO_PN_Sign_Dist_PT)( psST0->m_avPlane + 1, psST1->m_sCT.m_sET.m_sPT.m_avPoint[2] );

            TgBOOL_C                            bCMP_10 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vDist_10, vZR ) );
            TgBOOL_C                            bCMP_11 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vDist_11, vZR ) );
            TgBOOL_C                            bCMP_12 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vDist_12, vZR ) );

            if (bCMP_10 && bCMP_11 && bCMP_12)
            {
                return (false);
            }
            else
            {
                VEC_T(1,C)                          vDist_20 = FCN_VO(tgCO_PN_Sign_Dist_PT)( psST0->m_avPlane + 2, psST1->m_sCT.m_sET.m_sPT.m_avPoint[0] );
                VEC_T(1,C)                          vDist_21 = FCN_VO(tgCO_PN_Sign_Dist_PT)( psST0->m_avPlane + 2, psST1->m_sCT.m_sET.m_sPT.m_avPoint[1] );
                VEC_T(1,C)                          vDist_22 = FCN_VO(tgCO_PN_Sign_Dist_PT)( psST0->m_avPlane + 2, psST1->m_sCT.m_sET.m_sPT.m_avPoint[2] );

                TgBOOL_C                            bCMP_20 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vDist_20, vZR ) );
                TgBOOL_C                            bCMP_21 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vDist_21, vZR ) );
                TgBOOL_C                            bCMP_22 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vDist_22, vZR ) );

                if (bCMP_20 && bCMP_21 && bCMP_22)
                {
                    return (false);
                }
                else
                {
                    /* Normal extruded space of triangle 1 */

                    VEC_T(1,C)                          vDist_30 = FCN_VO(tgCO_PN_Sign_Dist_PT)( psST1->m_avPlane + 0, psST0->m_sCT.m_sET.m_sPT.m_avPoint[0] );
                    VEC_T(1,C)                          vDist_31 = FCN_VO(tgCO_PN_Sign_Dist_PT)( psST1->m_avPlane + 0, psST0->m_sCT.m_sET.m_sPT.m_avPoint[1] );
                    VEC_T(1,C)                          vDist_32 = FCN_VO(tgCO_PN_Sign_Dist_PT)( psST1->m_avPlane + 0, psST0->m_sCT.m_sET.m_sPT.m_avPoint[2] );

                    TgBOOL_C                            bCMP_30 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vDist_30, vZR ) );
                    TgBOOL_C                            bCMP_31 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vDist_31, vZR ) );
                    TgBOOL_C                            bCMP_32 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vDist_32, vZR ) );

                    if (bCMP_30 && bCMP_31 && bCMP_32)
                    {
                        return (false);
                    }
                    else
                    {
                        VEC_T(1,C)                          vDist_40 = FCN_VO(tgCO_PN_Sign_Dist_PT)( psST1->m_avPlane + 1, psST0->m_sCT.m_sET.m_sPT.m_avPoint[0] );
                        VEC_T(1,C)                          vDist_41 = FCN_VO(tgCO_PN_Sign_Dist_PT)( psST1->m_avPlane + 1, psST0->m_sCT.m_sET.m_sPT.m_avPoint[1] );
                        VEC_T(1,C)                          vDist_42 = FCN_VO(tgCO_PN_Sign_Dist_PT)( psST1->m_avPlane + 1, psST0->m_sCT.m_sET.m_sPT.m_avPoint[2] );

                        TgBOOL_C                            bCMP_40 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vDist_40, vZR ) );
                        TgBOOL_C                            bCMP_41 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vDist_41, vZR ) );
                        TgBOOL_C                            bCMP_42 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vDist_42, vZR ) );

                        if (bCMP_40 && bCMP_41 && bCMP_42)
                        {
                            return (false);
                        }
                        else
                        {
                            VEC_T(1,C)                          vDist_50 = FCN_VO(tgCO_PN_Sign_Dist_PT)( psST1->m_avPlane + 2, psST0->m_sCT.m_sET.m_sPT.m_avPoint[0] );
                            VEC_T(1,C)                          vDist_51 = FCN_VO(tgCO_PN_Sign_Dist_PT)( psST1->m_avPlane + 2, psST0->m_sCT.m_sET.m_sPT.m_avPoint[1] );
                            VEC_T(1,C)                          vDist_52 = FCN_VO(tgCO_PN_Sign_Dist_PT)( psST1->m_avPlane + 2, psST0->m_sCT.m_sET.m_sPT.m_avPoint[2] );

                            TgBOOL_C                            bCMP_50 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vDist_50, vZR ) );
                            TgBOOL_C                            bCMP_51 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vDist_51, vZR ) );
                            TgBOOL_C                            bCMP_52 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vDist_52, vZR ) );

                            if (bCMP_50 && bCMP_51 && bCMP_52)
                            {
                                return (false);
                            };
                        };
                    };
                };
            };
        };
    };

    return (true);
}


/* ---- FCN_VO(tgCO_ST_Test_Sweep_ST) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL FCN_VO(tgCO_ST_Test_Sweep_ST)( VEC_OBJ_T(TgSTRI,CPC) psST0, VEC_OBJ_T(TgSTRI,CPC) psST1, VEC_OBJ_T(TgDELTA,CPC) psDT )
{
    VEC_OBJ_T(STg2_CO_Axis_Test)        sAxTest; /* Parameter data output variable */

    VEC_T(1,C)                          vS0_NM = FCN_V(tgMH_DOT)( psST0->m_sCT.m_sET.m_sPT.m_avPoint[0], psST0->m_sCT.m_sET.m_sPT.m_vNormal );

    sAxTest.m_vLimitT = FCN_V(tgMH_SET1)( TYPE_K(1) ); /* The maximum t-value by which a contact must happen resulting in non-contact. */
    sAxTest.m_vMinT = FCN_V(tgMH_SET1)( -VAR_K(KTgMAX) );
    sAxTest.m_vMaxT = FCN_V(tgMH_SET1)( VAR_K(KTgMAX) );

    /* -- Axis: Triangle 0 Normal -- */

    sAxTest.m_vMin0 = vS0_NM;
    sAxTest.m_vMax0 = vS0_NM;
    FCN_VO(tgGM_ST_Project)( &sAxTest.m_vMin1, &sAxTest.m_vMax1, psST1, psST0->m_sCT.m_sET.m_sPT.m_vNormal );
    sAxTest.m_vSpeed = FCN_V(tgMH_DOT)( psDT->m_vDT, psST0->m_sCT.m_sET.m_sPT.m_vNormal );

    if (0 >= FCN_VO(tgCO_Test_Seperating_Axis)( &sAxTest ))
    {
        return (false);
    }
    else
    {
        /* Check to see if the triangle's are parallel. */
        VEC_T(1,C)                          vK0 = FCN_V(tgMH_CX)( psST0->m_sCT.m_sET.m_sPT.m_vNormal, psST1->m_sCT.m_sET.m_sPT.m_vNormal );

        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( FCN_V(tgMH_LSQ)( vK0 ), FCN_V(tgMH_SET1)( VAR_K(KTgEPS) ) ) ))
        {
            /* -- Axis: Triangle 1 Normal -- */

            VEC_T(1,C)                          vS1_NM = FCN_V(tgMH_DOT)( psST1->m_sCT.m_sET.m_sPT.m_avPoint[0], psST1->m_sCT.m_sET.m_sPT.m_vNormal );

            FCN_VO(tgGM_ST_Project)( &sAxTest.m_vMin0, &sAxTest.m_vMax0, psST0, psST1->m_sCT.m_sET.m_sPT.m_vNormal );
            sAxTest.m_vMin1 = vS1_NM;
            sAxTest.m_vMax1 = vS1_NM;
            sAxTest.m_vSpeed = FCN_V(tgMH_DOT)( psDT->m_vDT, psST1->m_sCT.m_sET.m_sPT.m_vNormal);

            if (0 >= FCN_VO(tgCO_Test_Seperating_Axis)( &sAxTest ))
            {
                return (false);
            };

            /* == Triangle Cross-Product == */

            for (TgRSIZE iE0 = 0; iE0 < 9; ++iE0)
            {
                VEC_T(1,C)                          vK1 = FCN_V(tgMH_CX)( psST0->m_sCT.m_sET.m_avEdge[(iE0 & 3)], psST1->m_sCT.m_sET.m_avEdge[(iE0 >> 3)] );

                FCN_VO(tgGM_ST_Project)( &sAxTest.m_vMin0, &sAxTest.m_vMax0, psST0, vK1 );
                FCN_VO(tgGM_ST_Project)( &sAxTest.m_vMin1, &sAxTest.m_vMax1, psST1, vK1 );
                sAxTest.m_vSpeed = FCN_V(tgMH_DOT)( psDT->m_vDT, vK1 );

                if (0 >= FCN_VO(tgCO_Test_Seperating_Axis)( &sAxTest ))
                {
                    return (false);
                };
            };
        }
        else
        {
            /* == Triangle 0 Space == */

            for (TgRSIZE iE0 = 0; iE0 < 3; ++iE0)
            {
                VEC_T(1,C)                          vK1 = FCN_V(tgMH_CX)( psST0->m_sCT.m_sET.m_sPT.m_vNormal, psST0->m_sCT.m_sET.m_avEdge[iE0] );

                FCN_VO(tgGM_ST_Project)( &sAxTest.m_vMin0, &sAxTest.m_vMax0, psST0, vK1 );
                FCN_VO(tgGM_ST_Project)( &sAxTest.m_vMin1, &sAxTest.m_vMax1, psST1, vK1 );
                sAxTest.m_vSpeed = FCN_V(tgMH_DOT)( psDT->m_vDT, vK1 );

                if (0 >= FCN_VO(tgCO_Test_Seperating_Axis)( &sAxTest ))
                {
                    return (false);
                };
            };

            /* == Triangle 1 Space == */

            for (TgRSIZE iE0 = 0; iE0 < 3; ++iE0)
            {
                VEC_T(1,C)                          vK1 = FCN_V(tgMH_CX)( psST1->m_sCT.m_sET.m_sPT.m_vNormal, psST1->m_sCT.m_sET.m_avEdge[iE0] );

                FCN_VO(tgGM_ST_Project)( &sAxTest.m_vMin0, &sAxTest.m_vMax0, psST0, vK1 );
                FCN_VO(tgGM_ST_Project)( &sAxTest.m_vMin1, &sAxTest.m_vMax1, psST1, vK1 );
                sAxTest.m_vSpeed = FCN_V(tgMH_DOT)( psDT->m_vDT, vK1 );

                if (0 >= FCN_VO(tgCO_Test_Seperating_Axis)( &sAxTest ))
                {
                    return (false);
                };
            };
        };

        return (true);
    }
}


/* ---- FCN_VO(tgCO_ST_Intersect_ST) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN_VO(tgCO_ST_Intersect_ST)(VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_OBJ_T(TgSTRI,CPC) psST0, VEC_OBJ_T(TgSTRI,CPC) psST1)
{
    if (!FCN_VO(tgCO_ST_Test_ST)(psST0, psST1))
    {
        return (KTgE_NO_INTERSECT);
    }
    else
    {
        VEC_OBJ_T(STg2_CO_Clip_List,PU)     psCL;
        VEC_T(1)                            vMag_K0;

        VEC_T(1,C)                          vN0_N1 = FCN_V(tgMH_DOT)( psST0->m_sCT.m_sET.m_sPT.m_vNormal, psST1->m_sCT.m_sET.m_sPT.m_vNormal);
        VEC_T(1,C)                          vK0 = FCN_V(tgMH_CX)( psST0->m_sCT.m_sET.m_sPT.m_vNormal, psST1->m_sCT.m_sET.m_sPT.m_vNormal );
        VEC_T(1,C)                          vN0xN1 = FCN_V(tgMH_NORM_LEN)( &vMag_K0, vK0 );
        VEC_T(1,C)                          vDet = FCN_V(tgMH_SUB)( FCN_V(tgMH_SET1)( TYPE_K(1) ), FCN_V(tgMH_MUL)( vN0_N1, vN0_N1 ) );

        psCL = (VEC_OBJ_T(STg2_CO_Clip_List,PU))TgMALLOC_POOL( sizeof( VEC_OBJ_T(STg2_CO_Clip_List) ) + 8 * sizeof( VEC_T(1) ) );
        psCL->m_nuiPoint = 0;
        psCL->m_nuiMax = 8;

        if (FCN_V(tgMH_Is_NR0)(vK0 ) || FCN_V(tgMH_Is_NR0)( vDet )) /* Co-Planar Triangles */
        {
            FCN_VO(tgCO_ST_Clip_PT)( psCL, psST0, &psST1->m_sCT.m_sET.m_sPT );
            return (FCN_VO(tgCO_ST_Internal_CoP_ST)( psPacket, psCL, FCN_V(tgMH_SET1)( TYPE_K(0) ), psST0->m_sCT.m_sET.m_sPT.m_vNormal ));
        }
        else
        {
            VEC_OBJ_T(STg2_CO_Contact,P)        psContact;

            VEC_T(1,C)                          vD0 = FCN_V(tgMH_DOT)( psST0->m_sCT.m_sET.m_sPT.m_avPoint[0], psST0->m_sCT.m_sET.m_sPT.m_vNormal );
            VEC_T(1,C)                          vD1 = FCN_V(tgMH_DOT)( psST1->m_sCT.m_sET.m_sPT.m_avPoint[0], psST1->m_sCT.m_sET.m_sPT.m_vNormal );
            TgRSIZE_C                           nuiPoint = tgCM_MIN_UMAX( psCL->m_nuiPoint, psPacket->m_nuiMaxContact - psPacket->m_nuiContact );

            VEC_T(1,C)                          vT0 = FCN_V(tgMH_DIV)( FCN_V(tgMH_SUB)( vD0, FCN_V(tgMH_MUL)( vD1, vN0_N1 ) ), vDet );
            VEC_T(1,C)                          vT1 = FCN_V(tgMH_DIV)( FCN_V(tgMH_SUB)( vD1, FCN_V(tgMH_MUL)( vD0, vN0_N1 ) ), vDet );
            VEC_T(1,C)                          vK2 = FCN_V(tgMH_MUL)( vT0, psST0->m_sCT.m_sET.m_sPT.m_vNormal );
            VEC_T(1,C)                          vK1 = FCN_V(tgMH_MUL)( vT1, psST1->m_sCT.m_sET.m_sPT.m_vNormal );
            VEC_T(1,C)                          vS0 = FCN_V(tgMH_ADD)( vK2, vK1 );

            FCN_VO(tgCO_ST_Clip_LR11)( psCL, psST0, vS0, vN0xN1 );

            FCN_VO(tgCO_Clip_ST)( psCL, psST1 );

            switch (nuiPoint)
            {
                case 2:
                    psContact = psPacket->m_psContact + psPacket->m_nuiContact;
                    psContact->m_vS0 = psCL->m_avPoint[1];
                    psContact->m_vN0 = vN0xN1;
                    psContact->m_vT0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
                    psContact->m_vDepth = FCN_V(tgMH_SET1)( TYPE_K(0) );

                    ++psPacket->m_nuiContact;

                SWITCH_FALLTHROUGH case 1:
                    psContact = psPacket->m_psContact + psPacket->m_nuiContact;
                    psContact->m_vS0 = psCL->m_avPoint[0];
                    psContact->m_vN0 = vN0xN1;
                    psContact->m_vT0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
                    psContact->m_vDepth = FCN_V(tgMH_SET1)( TYPE_K(0) );

                    ++psPacket->m_nuiContact;

                SWITCH_FALLTHROUGH case 0:
                    return (nuiPoint < psCL->m_nuiPoint ? KTgE_MAX_CONTACTS : KTgS_OK);

                default:
                    TgS_NO_DEFAULT(return (KTgE_FAIL));
            };
        };
    };
}


/* ---- FCN_VO(tgCO_ST_Sweep_ST) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN_VO(tgCO_ST_Sweep_ST)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_T(1,P) pvPM, VEC_OBJ_T(TgSTRI,CPC) psST0, VEC_OBJ_T(TgSTRI,CPC) psST1, VEC_OBJ_T(TgDELTA,CPC) psDT )
{
    VEC_OBJ_T(STg2_CO_Axis_Project)     sP0, sP1;
    VEC_OBJ_T(STg2_CO_Axis_Info)        sNFO;
    TgRESULT                            iResult;

    TgPARAM_CHECK( FCN_VO(tgGM_ST_Is_Valid)(psST0) && FCN_VO(tgGM_ST_Is_Valid)(psST1) );

    if (0 == psPacket->m_nuiMaxContact || psPacket->m_nuiContact >= psPacket->m_nuiMaxContact || nullptr == psPacket->m_psContact)
    {
        return (KTgE_FAIL);
    }
    else
    {
        VEC_OBJ_T(STg2_CO_Contact,P)        psContact;
        VEC_OBJ_T(STg2_CO_Clip_List,PU)     psCL;
        TgRSIZE                             nuiPoint;

        VEC_T(1,C)                          vPM_PTol = FCN_V(tgMH_ADD)( *pvPM, psPacket->m_vSweepTol );
        VEC_T(1,C)                          vPM_NTol = FCN_V(tgMH_SUB)( *pvPM, psPacket->m_vSweepTol );

        /*TgDEBUG_COLLISION_TRIANGLE_CREATEID(iDBG_TriID, psST1, ETgFEBUG_COLLISION_ENTERFCN); */

        sNFO.m_enSide = ETgCO_AXIS_CONTACT_DIRECTION__UNKNOWN;
        sNFO.m_vMinT = FCN_V(tgMH_SET1)( VAR_K(KTgMAX) );

        iResult = FCN_VO(tgCO_ST_Axis_Seperation_ST)( &sNFO, vPM_PTol, psST0, psST1, psDT );

        if (TgFAILED( iResult ))
        {
            TgERROR( KTgE_NO_INTERSECT == iResult );
            return (iResult);
        };

        /* == Contact Generation == */

        TgERROR( (sNFO.m_enSide != ETgCO_AXIS_CONTACT_DIRECTION__UNKNOWN) );

        if (sNFO.m_enSide == ETgCO_AXIS_CONTACT_DIRECTION__PENETRATED || FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( sNFO.m_vMinT, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ))
        {
            psPacket->m_nuiContact = 0;
            *pvPM = FCN_V(tgMH_SET1)( TYPE_K(0) );
            return (KTgE_PREPENETRATION);
        };

        /* Make sure this contact has not occurred more than tolerance later than the current sweep time. */

        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( sNFO.m_vMinT, vPM_PTol ) ))
        {
            return (KTgE_NO_INTERSECT);
        };

        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( sNFO.m_vMinT, vPM_NTol ) ))
        {
            psPacket->m_nuiContact = 0;
            *pvPM = sNFO.m_vMinT;
        };

        FCN_VO(tgCO_PT_Axis_ProjInfo)( &sP0, sNFO.m_vNormal, &psST0->m_sCT.m_sET.m_sPT );
        FCN_VO(tgCO_PT_Axis_ProjInfo)( &sP1, sNFO.m_vNormal, &psST1->m_sCT.m_sET.m_sPT );

        {
            /* Contact generation - interpolate the position of the triangle's at the given time, and compute the contact points. */

            TgBOOL_C                            bNegSide = sNFO.m_enSide == ETgCO_AXIS_CONTACT_DIRECTION__NEGATIVE;
            VEC_T(1,C)                          vOffset = FCN_V(tgMH_MUL)( sNFO.m_vMinT, psDT->m_vDT );

            /*  The two triangles are situated so that they are just touching each other.  Examine how the triangle vertices were projected onto the axis to determine the geometric
                relation of the contact - and then create the contact points. */

            TgRSIZE_C                           nuiVertD0 = bNegSide ? sP0.m_uiMinID : sP0.m_uiMaxID;
            VEC_T(1,PC)                         avVert0 = bNegSide ? sP0.m_avMinVert : sP0.m_avMaxVert;
            TgRSIZE_C                           nuiVertD1 = bNegSide ? sP1.m_uiMaxID : sP1.m_uiMinID;
            VEC_T(1,PC)                         avVert1 = bNegSide ? sP1.m_avMaxVert : sP1.m_avMinVert;
            VEC_T(1,C)                          vK0 = FCN_V(tgMH_NEG)( sNFO.m_vNormal);
            VEC_T(1,C)                          vNormal = bNegSide ? vK0 : sNFO.m_vNormal;

            psCL = (VEC_OBJ_T(STg2_CO_Clip_List,PU))TgMALLOC_POOL( sizeof( VEC_OBJ_T(STg2_CO_Clip_List) ) + 8 * sizeof( VEC_T(1) ) );
            psCL->m_nuiPoint = 0;
            psCL->m_nuiMax = 8;

            if (1 == nuiVertD0) /* Triangle 0 vertex touching a feature of Triangle 1 */
            {
                psContact = psPacket->m_psContact + psPacket->m_nuiContact;
                psContact->m_vS0 = avVert0[0];
                psContact->m_vN0 = vNormal;
                psContact->m_vT0 = sNFO.m_vMinT;
                psContact->m_vDepth = FCN_V(tgMH_SET1)( TYPE_K(0) );

                ++psPacket->m_nuiContact;

                return (KTgS_OK);
            };

            if (1 == nuiVertD1) /* Triangle 1 vertex touching a feature of Triangle 0 */
            {
                psContact = psPacket->m_psContact + psPacket->m_nuiContact;
                psContact->m_vS0 = FCN_V(tgMH_ADD)( avVert1[0], vOffset );
                psContact->m_vN0 = vNormal;
                psContact->m_vT0 = sNFO.m_vMinT;
                psContact->m_vDepth = FCN_V(tgMH_SET1)( TYPE_K(0) );

                ++psPacket->m_nuiContact;

                return (KTgS_OK);
            };

            if (2 == nuiVertD0 && 2 == nuiVertD1) /* Edge-Edge Contact */
            {
                VEC_T(1)                            vS0, vS1;
                TgRSIZE                             nuiCode;

                VEC_T(1,C)                          vK1 = FCN_V(tgMH_SUB)( avVert0[1], avVert0[0] );
                VEC_T(1,C)                          vK2 = FCN_V(tgMH_ADD)( vOffset, avVert1[0] );
                VEC_T(1,C)                          vK3 = FCN_V(tgMH_SUB)( avVert1[1], avVert1[0] );

                nuiCode = FCN_VO(tgCO_LN_Internal_Intersect_LN)( &vS0, &vS1, avVert0[0], vK1, vK2, vK3 );

                nuiPoint = tgCM_MIN_UMAX( nuiCode, psPacket->m_nuiMaxContact - psPacket->m_nuiContact );

                switch (nuiPoint)
                {
                    case 2:
                        psContact = psPacket->m_psContact + psPacket->m_nuiContact;
                        psContact->m_vS0 = vS1;
                        psContact->m_vN0 = vNormal;
                        psContact->m_vT0 = sNFO.m_vMinT;
                        psContact->m_vDepth = FCN_V(tgMH_SET1)( TYPE_K(0) );

                        ++psPacket->m_nuiContact;

                    SWITCH_FALLTHROUGH case 1:
                        psContact = psPacket->m_psContact + psPacket->m_nuiContact;
                        psContact->m_vS0 = vS0;
                        psContact->m_vN0 = vNormal;
                        psContact->m_vT0 = sNFO.m_vMinT;
                        psContact->m_vDepth = FCN_V(tgMH_SET1)( TYPE_K(0) );

                        ++psPacket->m_nuiContact;

                        return (nuiCode != nuiPoint ? KTgE_MAX_CONTACTS : KTgS_OK);

                    default:
                        return (KTgE_NO_INTERSECT);
                };
            };

            if (2 == nuiVertD0 && 3 == nuiVertD1) /* Edge-Face Contact */
            {
                VEC_T(1,C)                          vK1 = FCN_V(tgMH_SUB)( avVert0[0], vOffset );
                VEC_T(1,C)                          vK2 = FCN_V(tgMH_SUB)( avVert0[1], avVert0[0] );

                FCN_VO(tgCO_ST_Clip_LR11)(psCL, psST1, vK1, vK2 );
                nuiPoint = tgCM_MIN_UMAX( psCL->m_nuiPoint, psPacket->m_nuiMaxContact - psPacket->m_nuiContact );

                switch (nuiPoint)
                {
                    case 2:
                        psContact = psPacket->m_psContact + psPacket->m_nuiContact;
                        psContact->m_vS0 = FCN_V(tgMH_ADD)( psCL->m_avPoint[1], vOffset );
                        psContact->m_vN0 = vNormal;
                        psContact->m_vT0 = sNFO.m_vMinT;
                        psContact->m_vDepth = FCN_V(tgMH_SET1)( TYPE_K(0) );

                        ++psPacket->m_nuiContact;

                    SWITCH_FALLTHROUGH case 1:
                        psContact = psPacket->m_psContact + psPacket->m_nuiContact;
                        psContact->m_vS0 = FCN_V(tgMH_ADD)( psCL->m_avPoint[0], vOffset );
                        psContact->m_vN0 = vNormal;
                        psContact->m_vT0 = sNFO.m_vMinT;
                        psContact->m_vDepth = FCN_V(tgMH_SET1)( TYPE_K(0) );

                        ++psPacket->m_nuiContact;

                        return (psCL->m_nuiPoint != nuiPoint ? KTgE_MAX_CONTACTS : KTgS_OK);

                    default:
                        return (KTgE_NO_INTERSECT);
                };
            };

            if (3 == nuiVertD0 && 2 == nuiVertD1) /* Face-Edge Contact */
            {
                VEC_T(1,C)                          vK1 = FCN_V(tgMH_ADD)( vOffset, avVert1[0] );
                VEC_T(1,C)                          vK2 = FCN_V(tgMH_SUB)( avVert1[1], avVert1[0] );

                FCN_VO(tgCO_ST_Clip_LR11)(psCL, psST0, vK1, vK2 );
                nuiPoint = tgCM_MIN_UMAX( psCL->m_nuiPoint, psPacket->m_nuiMaxContact - psPacket->m_nuiContact );

                switch (nuiPoint)
                {
                    case 2:
                        psContact = psPacket->m_psContact + psPacket->m_nuiContact;
                        psContact->m_vS0 = psCL->m_avPoint[1];
                        psContact->m_vN0 = vNormal;
                        psContact->m_vT0 = sNFO.m_vMinT;
                        psContact->m_vDepth = FCN_V(tgMH_SET1)( TYPE_K(0) );

                        ++psPacket->m_nuiContact;

                    SWITCH_FALLTHROUGH case 1:
                        psContact = psPacket->m_psContact + psPacket->m_nuiContact;
                        psContact->m_vS0 = psCL->m_avPoint[0];
                        psContact->m_vN0 = vNormal;
                        psContact->m_vT0 = sNFO.m_vMinT;
                        psContact->m_vDepth = FCN_V(tgMH_SET1)( TYPE_K(0) );

                        ++psPacket->m_nuiContact;

                        return (psCL->m_nuiPoint != nuiPoint ? KTgE_MAX_CONTACTS : KTgS_OK);

                    default:
                        return (KTgE_NO_INTERSECT);
                };
            };

            TgERROR( 3 == nuiVertD0 && 3 == nuiVertD1 );

            FCN_VO(tgCO_ST_Clip_PT)(psCL, psST0, &psST1->m_sCT.m_sET.m_sPT);

            return (FCN_VO(tgCO_ST_Internal_CoP_ST)( psPacket, psCL, sNFO.m_vMinT, vNormal ));
        };
    };
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- FCN_VO(tgCO_ST_Internal_CoP_ST) ---------------------------------------------------------------------------------------------------------------------------------------------
  Transfer the point generated by a clipping operation to the contact list.
  Input:  tgCL: F_Clip list of points
  Input:  fT0: Time of contact
  Input:  vNormal: The normal of contact
  Output: tgPacket: Contact points are added to it
  Return: Result Code
 --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT FCN_VO(tgCO_ST_Internal_CoP_ST)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_OBJ_T(STg2_CO_Clip_List,PC) psCL, VEC_T(1,C) vT0, VEC_T(1,C) vNormal )
{
    TgRSIZE_C                           nuiPoint = tgCM_MIN_UMAX( psCL->m_nuiPoint, psPacket->m_nuiMaxContact - psPacket->m_nuiContact );
    VEC_OBJ_T(STg2_CO_Contact,P)        psContact;;

    switch (nuiPoint)
    {
        case 6:
            psContact = psPacket->m_psContact + psPacket->m_nuiContact;
            psContact->m_vS0 = psCL->m_avPoint[5];
            psContact->m_vN0 = vNormal;
            psContact->m_vT0 = vT0;
            psContact->m_vDepth = FCN_V(tgMH_SET1)( TYPE_K(0) );

            ++psPacket->m_nuiContact;

        SWITCH_FALLTHROUGH case 5:
            psContact = psPacket->m_psContact + psPacket->m_nuiContact;
            psContact->m_vS0 = psCL->m_avPoint[4];
            psContact->m_vN0 = vNormal;
            psContact->m_vT0 = vT0;
            psContact->m_vDepth = FCN_V(tgMH_SET1)( TYPE_K(0) );

            ++psPacket->m_nuiContact;

        SWITCH_FALLTHROUGH case 4:
            psContact = psPacket->m_psContact + psPacket->m_nuiContact;
            psContact->m_vS0 = psCL->m_avPoint[3];
            psContact->m_vN0 = vNormal;
            psContact->m_vT0 = vT0;
            psContact->m_vDepth = FCN_V(tgMH_SET1)( TYPE_K(0) );

            ++psPacket->m_nuiContact;

        SWITCH_FALLTHROUGH case 3:
            psContact = psPacket->m_psContact + psPacket->m_nuiContact;

            psContact->m_vS0 = psCL->m_avPoint[2];
            psContact->m_vN0 = vNormal;
            psContact->m_vT0 = vT0;
            psContact->m_vDepth = FCN_V(tgMH_SET1)( TYPE_K(0) );

            ++psPacket->m_nuiContact;

        SWITCH_FALLTHROUGH case 2:
            psContact = psPacket->m_psContact + psPacket->m_nuiContact;
            psContact->m_vS0 = psCL->m_avPoint[1];
            psContact->m_vN0 = vNormal;
            psContact->m_vT0 = vT0;
            psContact->m_vDepth = FCN_V(tgMH_SET1)( TYPE_K(0) );

            ++psPacket->m_nuiContact;

        SWITCH_FALLTHROUGH case 1:
            psContact = psPacket->m_psContact + psPacket->m_nuiContact;
            psContact->m_vS0 = psCL->m_avPoint[0];
            psContact->m_vN0 = vNormal;
            psContact->m_vT0 = vT0;
            psContact->m_vDepth = FCN_V(tgMH_SET1)( TYPE_K(0) );

            ++psPacket->m_nuiContact;

        SWITCH_FALLTHROUGH case 0:
            return (nuiPoint < psCL->m_nuiPoint ? KTgE_MAX_CONTACTS : KTgS_OK);

        default:
            TgS_NO_DEFAULT(return (KTgE_FAIL));
    };
}


/* ---- FCN_VO(tgCO_ST_Axis_Seperation_ST) ------------------------------------------------------------------------------------------------------------------------------------------
    Input:  psST0, psST1: Space triangle primitive - Triangle #2 (psST1) is being swept.
    Input:  fLimitT: Current normalized time of contact for the contact query set.
    Input:  psDT: A structure holding the swept primitive displacement for the entire duration of the test period.
    Output: sNFO: Structure holds the resulting axis separation information necessary to create a contact set.
    Return: Result Code
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN_VO(tgCO_ST_Axis_Seperation_ST)( VEC_OBJ_T(STg2_CO_Axis_Info,PC) psNFO, VEC_T(1,C) vLimitT, VEC_OBJ_T(TgSTRI,CPC) psST0, VEC_OBJ_T(TgSTRI,CPC) psST1,
                                             VEC_OBJ_T(TgDELTA,CPC) psDT )
{
    VEC_OBJ_T(STg2_CO_Axis_Test)        sAxTest; /* Parameter data output variable */
    TgSINT_F32                          iResult;
    TgSINT_F32                          iE0;
    TgBOOL                              bFlag;

    VEC_T(1,C)      vS0_NM = FCN_V(tgMH_DOT)( psST0->m_sCT.m_sET.m_sPT.m_avPoint[0], psST0->m_sCT.m_sET.m_sPT.m_vNormal );
    VEC_T(1,C)      vK0 = FCN_V(tgMH_CX)( psST0->m_sCT.m_sET.m_sPT.m_vNormal, psST1->m_sCT.m_sET.m_sPT.m_vNormal );

    sAxTest.m_vLimitT = vLimitT; /* The maximum t-value by which a contact must happen resulting in non-contact. */
    sAxTest.m_vMinT = FCN_V(tgMH_SET1)( -VAR_K(KTgMAX) );
    sAxTest.m_vMaxT = FCN_V(tgMH_SET1)( VAR_K(KTgMAX) );

    /* -- Axis: Triangle 0 Normal -- */

    sAxTest.m_vMin0 = vS0_NM;
    sAxTest.m_vMax0 = vS0_NM;
    FCN_VO(tgGM_ST_Project)( &sAxTest.m_vMin1, &sAxTest.m_vMax1, psST1, psST0->m_sCT.m_sET.m_sPT.m_vNormal );
    sAxTest.m_vSpeed = FCN_V(tgMH_DOT)( psDT->m_vDT, psST0->m_sCT.m_sET.m_sPT.m_vNormal );

    iResult = FCN_VO(tgCO_Test_Seperating_Axis)( &sAxTest );

    bFlag = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( sAxTest.m_vMax1, sAxTest.m_vMin0 ) );

    switch (iResult)
    {
        case 1: /* Update has occurred */
            psNFO->m_enSide = bFlag ? ETgCO_AXIS_CONTACT_DIRECTION__NEGATIVE : ETgCO_AXIS_CONTACT_DIRECTION__POSITIVE;
            psNFO->m_vNormal = psST0->m_sCT.m_sET.m_sPT.m_vNormal;
            psNFO->m_vMinT = sAxTest.m_vMinT;
        SWITCH_FALLTHROUGH case 0: /* Contact occurred in valid interval, but earlier contact already recorded. */
            break;
        case -1: /* No contact occurred during valid interval, thus primitives are separated on this axis. */
            return (KTgE_NO_INTERSECT);
    };

    /* Check to see if the triangle's are parallel. */

    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( FCN_V(tgMH_LSQ)( vK0 ), FCN_V(tgMH_SET1)( VAR_K(KTgROOT_EPS) ) ) ))
    {
        /* -- Axis: Triangle 1 Normal -- */

        VEC_T(1,C)                          vS1_NM = FCN_V(tgMH_DOT)( psST1->m_sCT.m_sET.m_sPT.m_avPoint[0], psST1->m_sCT.m_sET.m_sPT.m_vNormal );

        FCN_VO(tgGM_ST_Project)( &sAxTest.m_vMin0, &sAxTest.m_vMax0, psST0, psST1->m_sCT.m_sET.m_sPT.m_vNormal );
        sAxTest.m_vMin1 = vS1_NM;
        sAxTest.m_vMax1 = vS1_NM;
        sAxTest.m_vSpeed = FCN_V(tgMH_DOT)( psDT->m_vDT, psST1->m_sCT.m_sET.m_sPT.m_vNormal );

        iResult = FCN_VO(tgCO_Test_Seperating_Axis)( &sAxTest );

        bFlag = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( sAxTest.m_vMax1, sAxTest.m_vMin0 ) );

        switch (iResult)
        {
            case 1: /* Update has occurred */
                psNFO->m_enSide = bFlag ? ETgCO_AXIS_CONTACT_DIRECTION__NEGATIVE : ETgCO_AXIS_CONTACT_DIRECTION__POSITIVE;
                psNFO->m_vNormal = psST1->m_sCT.m_sET.m_sPT.m_vNormal;
                psNFO->m_vMinT = sAxTest.m_vMinT;
            SWITCH_FALLTHROUGH case 0: /* Contact occurred in valid interval, but earlier contact already recorded. */
                break;
            case -1: /* No contact occurred during valid interval, thus primitives are separated on this axis. */
                return (KTgE_NO_INTERSECT);
        };

        /* == Triangle Cross-Product == */

        for (iE0 = 0; iE0 < 9; ++iE0)
        {
            VEC_T(1,C)                          vK1 = FCN_V(tgMH_CX)( psST0->m_sCT.m_sET.m_avEdge[(iE0 & 3)], psST1->m_sCT.m_sET.m_avEdge[(iE0 >> 3)] );

            FCN_VO(tgGM_ST_Project)( &sAxTest.m_vMin0, &sAxTest.m_vMax0, psST0, vK1 );
            FCN_VO(tgGM_ST_Project)( &sAxTest.m_vMin1, &sAxTest.m_vMax1, psST1, vK1 );
            sAxTest.m_vSpeed = FCN_V(tgMH_DOT)( psDT->m_vDT, vK1 );

            iResult = FCN_VO(tgCO_Test_Seperating_Axis)( &sAxTest );

            bFlag = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( sAxTest.m_vMax1, sAxTest.m_vMin0 ) );

            switch (iResult)
            {
                case 1: /* Update has occurred */
                    psNFO->m_enSide = bFlag ? ETgCO_AXIS_CONTACT_DIRECTION__NEGATIVE : ETgCO_AXIS_CONTACT_DIRECTION__POSITIVE;
                    psNFO->m_vNormal = vK1;
                    psNFO->m_vMinT = sAxTest.m_vMinT;
                SWITCH_FALLTHROUGH case 0: /* Contact occurred in valid interval, but earlier contact already recorded. */
                    break;
                case -1: /* No contact occurred during valid interval, thus primitives are separated on this axis. */
                    return (KTgE_NO_INTERSECT);
            };
        };
    }
    else
    {
        /* == Triangle 0 Space == */

        for (iE0 = 0; iE0 < 3; ++iE0)
        {
            VEC_T(1,C)                          vK1 = FCN_V(tgMH_CX)( psST0->m_sCT.m_sET.m_sPT.m_vNormal, psST0->m_sCT.m_sET.m_avEdge[iE0]);

            FCN_VO(tgGM_ST_Project)( &sAxTest.m_vMin0, &sAxTest.m_vMax0, psST0, vK1 );
            FCN_VO(tgGM_ST_Project)( &sAxTest.m_vMin1, &sAxTest.m_vMax1, psST1, vK1 );
            sAxTest.m_vSpeed = FCN_V(tgMH_DOT)( psDT->m_vDT, vK1 );

            iResult = FCN_VO(tgCO_Test_Seperating_Axis)( &sAxTest );

            bFlag = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( sAxTest.m_vMax1, sAxTest.m_vMin0 ) );

            switch (iResult)
            {
                case 1: /* Update has occurred */
                    psNFO->m_enSide = bFlag ? ETgCO_AXIS_CONTACT_DIRECTION__NEGATIVE : ETgCO_AXIS_CONTACT_DIRECTION__POSITIVE;
                    psNFO->m_vNormal = vK1;
                    psNFO->m_vMinT = sAxTest.m_vMinT;
                SWITCH_FALLTHROUGH case 0: /* Contact occurred in valid interval, but earlier contact already recorded. */
                    break;
                case -1: /* No contact occurred during valid interval, thus primitives are separated on this axis. */
                    return (KTgE_NO_INTERSECT);
            };
        };

        /* == Triangle 1 Space == */

        for (iE0 = 0; iE0 < 3; ++iE0)
        {
            VEC_T(1,C)                          vK1 = FCN_V(tgMH_CX)( psST1->m_sCT.m_sET.m_sPT.m_vNormal, psST1->m_sCT.m_sET.m_avEdge[iE0]);

            FCN_VO(tgGM_ST_Project)( &sAxTest.m_vMin0, &sAxTest.m_vMax0, psST0, vK1 );
            FCN_VO(tgGM_ST_Project)( &sAxTest.m_vMin1, &sAxTest.m_vMax1, psST1, vK1 );
            sAxTest.m_vSpeed = FCN_V(tgMH_DOT)( psDT->m_vDT, vK1 );

            iResult = FCN_VO(tgCO_Test_Seperating_Axis)( &sAxTest );
            
            bFlag = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( sAxTest.m_vMax1, sAxTest.m_vMin0 ) );

            switch (iResult)
            {
                case 1: /* Update has occurred */
                    psNFO->m_enSide = bFlag ? ETgCO_AXIS_CONTACT_DIRECTION__NEGATIVE : ETgCO_AXIS_CONTACT_DIRECTION__POSITIVE;
                    psNFO->m_vNormal = vK1;
                    psNFO->m_vMinT = sAxTest.m_vMinT;
                SWITCH_FALLTHROUGH case 0: /* Contact occurred in valid interval, but earlier contact already recorded. */
                    break;
                case -1: /* No contact occurred during valid interval, thus primitives are separated on this axis. */
                    return (KTgE_NO_INTERSECT);
            };
        };
    };

    return (KTgS_OK);
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
