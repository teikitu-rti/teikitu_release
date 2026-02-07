/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Sphere-Triangle.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "TgS COLLISION/TgS Collision - Plane-Point.inl"
#include "TgS COLLISION/TgS Collision - Sphere-Triangle.inl"

#if !defined (TEMPLATE_TYPE_EXPANSION__RELOAD)
    #define TEMPLATE_TYPE_EXPANSION__RELOAD

    #if TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE
        #define TEMPLATE__VECTOR_DIM 4
        #define TEMPLATE__TYPE_SIZE 64
        #include __FILE__
    #endif

    #define TEMPLATE__VECTOR_DIM 4
    #define TEMPLATE__TYPE_SIZE 32

    #undef TEMPLATE_TYPE_EXPANSION__RELOAD
#endif

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"


/* == Collision ================================================================================================================================================================== */

/* ---- FCN_VO(tgCO_SP_Sweep_ST) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN_VO(tgCO_SP_Sweep_ST)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_T(1,P) pvPM, VEC_OBJ_T(TgSPHERE,CPC) psSP0, VEC_OBJ_T(TgSTRI,CPC) psST0, VEC_OBJ_T(TgDELTA,CPC) psDT )
{
    TgPARAM_CHECK( FCN_VO(tgGM_SP_Is_Valid)(psSP0) && FCN_VO(tgGM_ST_Is_Valid)(psST0) );

    if (0 == psPacket->m_nuiMaxContact || psPacket->m_nuiContact >= psPacket->m_nuiMaxContact || nullptr == psPacket->m_psContact)
    {
        return (KTgE_FAIL);
    }
    else
    {
        /*TgDEBUG_COLLISION_TRIANGLE_CREATEID( iDBG_TriID, psST0, etgDEBUG_COLLISION_ENTERFCN ); */

        TgRESULT                            iResult;

        TgBOOL_C                            bPenetrate = psPacket->m_bReport_Penetration;
        TgRSIZE_C                           nuiContact = psPacket->m_nuiContact;

        VEC_T(1,C)                          vX0 = FCN_V(tgMH_SUB)( psSP0->m_vOrigin, psST0->m_sCT.m_sET.m_sPT.m_avPoint[0] );
        VEC_T(1,C)                          vX0_N = FCN_V(tgMH_DOT)( vX0, psST0->m_sCT.m_sET.m_sPT.m_vNormal );
        VEC_T(1,C)                          vDT_N = FCN_V(tgMH_DOT)( psDT->m_vDT, psST0->m_sCT.m_sET.m_sPT.m_vNormal );
        VEC_T(1,C)                          vX1 = FCN_V(tgMH_SUB)( psSP0->m_vRadius, vX0_N );
        VEC_T(1,C)                          vT = FCN_V(tgMH_DIV)( vX1, vDT_N );

        /* Check the displacement vector - if it is directed away from the triangle intersection is not possible. */

        VEC_T(1,C)                          vABS_X0_N = FCN_V(tgMH_ABS)( vX0_N );
        VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_GT)( vABS_X0_N, psSP0->m_vRadius );
        TgBOOL_C                            bCMP_0 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_0 );
        VEC_T(1,C)                          vABS_DT_N = FCN_V(tgMH_ABS)( vDT_N );
        VEC_T(1,C)                          vCMP_1 = FCN_V(tgMH_CMP_GT)( vABS_DT_N, FCN_V(tgMH_SET1)( VAR_K(KTgROOT_EPS) ) );
        TgBOOL_C                            bCMP_1 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_1 );
        VEC_T(1,C)                          vX2 = FCN_V(tgMH_MUL)( vX0_N, vDT_N );
        VEC_T(1,C)                          vCMP_2 = FCN_V(tgMH_CMP_GT)( vX2, FCN_V(tgMH_SET1)( TYPE_K(0) ) );
        TgBOOL_C                            bCMP_2 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_2 );

        /* Calculate the extrapolation required to translate the distance from the origin to the triangle plane. */

        VEC_T(1,C)                          vX3 = FCN_V(tgMH_ADD)( *pvPM, psPacket->m_vSweepTol );
        VEC_T(1,C)                          vCMP_3 = FCN_V(tgMH_CMP_GT)( vT, vX3 );
        TgBOOL_C                            bCMP_3 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_3 );
        VEC_T(1,C)                          vCMP_4 = FCN_V(tgMH_CMP_GT)( vT, FCN_V(tgMH_SET1)( TYPE_K(1) ) );
        TgBOOL_C                            bCMP_4 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_4 );
    
        if ( bCMP_0 && bCMP_1 && bCMP_2 )
        {
            return (KTgE_NO_INTERSECT);
        };

        if (bCMP_3 || bCMP_4)
        {
            if (!psPacket->m_bReport_Penetration)
            {
                return (KTgE_NO_INTERSECT);
            };
        }
        else
        {
            /* Examine the resulting point on the plane to see if it is contained by the triangle. */

            VEC_T(1,C)                          vCMP_5 = FCN_V(tgMH_CMP_GE)( vT, FCN_V(tgMH_SET1)( TYPE_K(0) ) );
            TgBOOL_C                            bCMP_5 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_5 );

            if (bCMP_5)
            {
                VEC_OBJ_T(STg2_CO_Contact,P)        psContact;
                TgBOOL                              bOUTSIDE_TRIANGLE;

                VEC_T(1,C)                          vK0 = FCN_V(tgMH_MUL)( vT, psDT->m_vDT );
                VEC_T(1,C)                          vK1 = FCN_V(tgMH_ADD)( psSP0->m_vOrigin, vK0 );
                VEC_T(1,C)                          vK2 = FCN_V(tgMH_MUL)( psSP0->m_vRadius, psST0->m_sCT.m_sET.m_sPT.m_vNormal );
                VEC_T(1,C)                          vK3 = FCN_V(tgMH_SET1)( VAR_K(KTgEPS) );

                bOUTSIDE_TRIANGLE = false;

                for (TgRSIZE uiEdge = 0; uiEdge < 3; ++uiEdge)
                {
                    VEC_T(1,C)                          vK4 = FCN_V(tgMH_LEN)( psST0->m_sCT.m_sET.m_avEdge[uiEdge] );
                    VEC_T(1,C)                          vLimit = FCN_V(tgMH_MUL)( vK3, vK4 );
                    VEC_T(1,C)                          vDist = FCN_VO(tgCO_PN_Dist_PT)( psST0->m_avPlane + uiEdge, vK1 );
                    VEC_T(1,C)                          vK5 = FCN_V(tgMH_NEG)( vLimit );
                    VEC_T(1,C)                          vCMP_6 = FCN_V(tgMH_CMP_LT)( vDist, vK5 );
                    TgBOOL_C                            bCMP_6 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_6 );
                    VEC_T(1,C)                          vCMP_7 = FCN_V(tgMH_CMP_LE)( vDist, vLimit );
                    TgBOOL_C                            bCMP_7 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_7 );

                    if (bCMP_6)
                    {
                        VEC_T(1,C)                          vEN_DT = FCN_V(tgMH_DOT)( psST0->m_avPlane[uiEdge].m_vNormal, psDT->m_vDT );
                        VEC_T(1,C)                          vCMP_8 = FCN_V(tgMH_CMP_LT)( vEN_DT, FCN_V(tgMH_SET1)( TYPE_K(0) ) );
                        TgBOOL_C                            bCMP_8 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_8 );

                        /* The sphere origin is behind the triangle plane.  Check to see if the delta moves away from the plane. */

                        if (!FCN_VO(tgGM_ST_Test_Edge)( psST0, uiEdge ) && bCMP_8)
                        {
                            return (KTgE_NO_INTERSECT);
                        };

                        /* The sphere does not intersect the triangle plane - check the edge/vertices for intersection. */
                        bOUTSIDE_TRIANGLE = true;
                        break;
                    }
                    else if (bCMP_7)
                    {
                        /* The contact point is within tolerance of a specific triangle's edge.  Check to see if its been marked invalid. */

                        if (!FCN_VO(tgGM_ST_Test_Edge)( psST0, uiEdge ) && FCN_VO(tgGM_ET_Is_Tri_Edge_Ignored_Code)( &psST0->m_sCT.m_sET, uiEdge ))
                        {
                            return (KTgE_NO_INTERSECT);
                        };
                    };
                };

                /* Valid point of contact. */
                if (!bOUTSIDE_TRIANGLE)
                {
                    VEC_T(1,C)                          vK4 = FCN_V(tgMH_SUB)( *pvPM, psPacket->m_vSweepTol );
                    VEC_T(1,C)                          vCMP_6 = FCN_V(tgMH_CMP_LT)( vT, vK4 );
                    TgBOOL_C                            bCMP_6 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_6 );

                    if (bCMP_6)
                    {
                        psPacket->m_nuiContact = 0;
                        *pvPM = vT;
                    };

                    psContact = psPacket->m_psContact + psPacket->m_nuiContact;

                    psContact->m_vS0 = FCN_V(tgMH_SUB)( vK1, vK2 );
                    psContact->m_vN0 = psST0->m_sCT.m_sET.m_sPT.m_vNormal;
                    psContact->m_vT0 = vT;
                    psContact->m_vDepth = FCN_V(tgMH_SET1)( TYPE_K(0) );

                    ++psPacket->m_nuiContact;

                    /*TgDEBUG_COLLISION_TRIANGLE( iDBG_TriID, etgDEBUG_COLLISION_CODE1 ); */

                    return (KTgS_OK);
                }
                else
                {
                    /* State Block for Edge Tests - Required because of the goto statement used for the penetration check */

                    TgBOOL                              bHit = false;

                    VEC_T(1,C)                          vK4 = FCN_V(tgMH_SUB)( psDT->m_vDT, psST0->m_sCT.m_sET.m_sPT.m_avPoint[0] );
                    VEC_T(1,C)                          vK5 = FCN_V(tgMH_ADD)( psSP0->m_vOrigin, vK4 );

                    /* Check for collisions against the three edges */
                    for (TgRSIZE uiEdge = 0; uiEdge < 3; ++uiEdge)
                    {
                        if (!FCN_VO(tgGM_ST_Test_Edge)( psST0, uiEdge ) && FCN_VO(tgGM_ET_Is_Tri_Edge_Ignored_Code)( &psST0->m_sCT.m_sET, uiEdge ))
                        {
                            continue;
                        }
                        else
                        {
                            VEC_T(1,C)                          vNeg_Rad = FCN_V(tgMH_NEG)( psSP0->m_vRadius );
                            VEC_T(1,C)                          vK6 = FCN_V(tgMH_LEN)( psST0->m_sCT.m_sET.m_avEdge[uiEdge] );
                            VEC_T(1,C)                          vLimit = FCN_V(tgMH_MUL)( vNeg_Rad, vK6 );

                            VEC_T(1,C)                          vT0 = FCN_V(tgMH_DOT)( psST0->m_avPlane[uiEdge].m_vNormal, vX0 );
                            VEC_T(1,C)                          vT1 = FCN_V(tgMH_DOT)( psST0->m_avPlane[uiEdge].m_vNormal, vK5 );
                            VEC_T(1,C)                          vCMP_7 = FCN_V(tgMH_CMP_LT)( vT0, FCN_V(tgMH_SET1)( VAR_K(KTgROOT_EPS) ) );
                            TgBOOL_C                            bCMP_7 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_7 );
                            VEC_T(1,C)                          vCMP_8 = FCN_V(tgMH_CMP_LT)( vT1, FCN_V(tgMH_SET1)( VAR_K(KTgROOT_EPS) ) );
                            TgBOOL_C                            bCMP_8 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_8 );

                            VEC_T(1,C)                          vCMP_9 = FCN_V(tgMH_CMP_LT)( vT0, vLimit );
                            TgBOOL_C                            bCMP_9 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_9 );
                            VEC_T(1,C)                          vCMP_A = FCN_V(tgMH_CMP_LT)( vT1, vLimit );
                            TgBOOL_C                            bCMP_A = FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_A );

                            if (bCMP_9 && bCMP_A)
                            {
                                return (KTgE_NO_INTERSECT);
                            };

                            if (bCMP_7 || bCMP_8)
                            {
                                bHit |= 0 <= FCN_VO(tgCO_SP_Sweep_LR11)( psPacket, pvPM, nullptr,
                                                                         psSP0, psST0->m_sCT.m_sET.m_sPT.m_avPoint[uiEdge], psST0->m_sCT.m_sET.m_avEdge[uiEdge], psDT );
                            };
                        };
                    };

                    /* Check for collisions against the three vertices */

                    for (TgRSIZE uiPoint = 0; uiPoint < 3; ++uiPoint)
                    {
                        if (FCN_VO(tgGM_ST_Test_Point)(psST0, uiPoint))
                        {
                            bHit |= TgSUCCEEDED( FCN_VO(tgCO_PT_Sweep_SP)( psPacket, pvPM, nullptr, psST0->m_sCT.m_sET.m_sPT.m_avPoint[uiPoint], psSP0, psDT ) );
                        };
                    };

                    /*TgDEBUG_COLLISION_TRIANGLE( iDBG_TriID, etgDEBUG_COLLISION_CODE2 ); */

                    if (bHit)
                    {
                        return (KTgS_OK);
                    };
                };

                /* If pre-penetration information is not requested or the sphere's origin is behind the triangle report a non-intersection. */

                if (!bPenetrate)
                {
                    return (KTgE_NO_INTERSECT);
                };
            };
        };


        /*TgDEBUG_COLLISION_TRIANGLE( iDBG_TriID, etgDEBUG_COLLISION_PREPENETRATION ); */

        /* Record the current number of contacts before potentially clearing the list in case pre-penetration is not found. */

        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( *pvPM, psPacket->m_vSweepTol ) ))
        {
            psPacket->m_nuiContact = 0;
        };

        iResult = FCN_VO(tgCO_ST_Penetrate_SP)(psPacket, psST0, psSP0);

        /* Restore the original number of contacts if pre-penetration was not found. */

        if (TgFAILED( iResult ))
        {
            psPacket->m_nuiContact = nuiContact;
            return (iResult);
        };

        /* Set the time parameter and return back the appropriate result code. */

        *pvPM = FCN_V(tgMH_SET1)( TYPE_K(0) );

        return (KTgE_MAX_CONTACTS == iResult ? KTgE_MAX_CONTACTS : (KTgS_OK == iResult ? KTgE_PREPENETRATION : iResult));
    };
}


/* ---- FCN_VO(tgCO_SP_Penetrate_ST) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN_VO(tgCO_SP_Penetrate_ST)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_OBJ_T(TgSPHERE,CPC) psSP0, VEC_OBJ_T(TgSTRI,CPC) psST0 )
{
    /*TgDEBUG_COLLISION_TRIANGLE_CREATEID( iDBG_TriID, psCT0, etgDEBUG_COLLISION_ENTERFCN ); */

    VEC_T(1)                            vNormal, vCT0_T0, vCT0_T1;

    VEC_T(1,C)                          vDistSq = FCN_VO(tgCO_ET_ClosestSq_PM_PT)( &vCT0_T0, &vCT0_T1, &psST0->m_sCT.m_sET, psSP0->m_vOrigin );
    VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_GT)( vDistSq, psSP0->m_vRadiusSq );

    /* Check to see if the proposed point of contact is on a reduced triangle feature. */

    TgBOOL_C                            bCulled = FCN_VO(tgGM_ST_Is_Point_Culled)( psST0, vCT0_T0, vCT0_T1 );

    /* Check to see if the reduced feature should be included for this case (only important if bCulled is true). */

    TgBOOL_C                            bEdge = FCN_VO(tgGM_ET_Is_Tri_Edge_Ignored)( &psST0->m_sCT.m_sET, vCT0_T0, vCT0_T1 );

    /*  No penetration if the minimal distance between the sphere origin and the triangle is greater than the sphere's radius. Also, if the point is on a reduced */
    /* feature, the contact can be ignored.  The exception is for an edge, specifically for a sphere ( limit of one contact point ) it is necessary to make sure that a */
    /* contact on the edge is not ignored at least once to prevent the system from culling out all contact points between a sphere and a triangle list. */

    TgERROR( !(0 == psPacket->m_nuiMaxContact || psPacket->m_nuiContact >= psPacket->m_nuiMaxContact) );
    TgERROR( !(0 == psPacket->m_psContact) );

    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_0 ) || (bCulled && bEdge))
    {
        return (KTgE_NO_INTERSECT);
    }
    else
    {
        /*TgDEBUG_COLLISION_TRIANGLE( iDBG_TriID, etgDEBUG_COLLISION_PASSED_REJECT ); */

        VEC_T(1,C)                          vCT0 = FCN_VO(tgGM_ST_Calc_Point)( psST0, vCT0_T0, vCT0_T1 );
        VEC_T(1,C)                          vDist = FCN_V(tgMH_SQRT)( vDistSq );
        VEC_T(1,C)                          vX0 = FCN_V(tgMH_SUB)( psSP0->m_vRadius, vDist );
        VEC_T(1,C)                          vDepth = FCN_V(tgMH_MAX)( FCN_V(tgMH_SET1)( TYPE_K(0) ), vX0 );

        /*  Check to see if the normal of intersection should be replaced by the triangle's normal.  This is done to reduce floating point noise in the system where */
        /* near-normal results are returned.  By forcing it to the triangle's normal, extraneous rotations are minimized. The other possibility is that the sphere's */
        /* origin lies on the triangle itself, thus, requiring the selection of the triangle's normal for the intersection. */

        TgBOOL                              bUseNormal = !FCN_V(tgMH_Is_NR0)( vDist );
        VEC_OBJ_T(STg2_CO_Contact,P)        psContact;

        vNormal = FCN_V(tgMH_SUB)(psSP0->m_vOrigin, vCT0);

        if (bUseNormal)
        {
            vNormal = FCN_V(tgMH_NORM)( vNormal );

            /*  Check to see if the resultant normal is near that of the triangle's.  If they are close then use the triangle's normal to help further reduce floating */
            /* point noise. */

            bUseNormal = FCN_V(tgMH_Is_NR1)(FCN_V(tgMH_DOT)( vNormal, psST0->m_sCT.m_sET.m_sPT.m_vNormal ));
        };

        if (bCulled && bUseNormal)
        {
            /* If the point was marked to be culled (even if its on a valid edge), and the contact normal does not match the triangle's normal, ignore this contact.  Its */
            /* assumed that the matching triangle, attached to this one, will create the required contact point.  Prevents duplicate points from being created. */

            return (KTgE_NO_INTERSECT);
        }
        else
        {
            VEC_T(1,C)                          vKN = bUseNormal ? vNormal : psST0->m_sCT.m_sET.m_sPT.m_vNormal;
            VEC_T(1,C)                          vK1 = FCN_V(tgMH_MUL)( psSP0->m_vRadius, vKN );

            /* Create contact point. */

            psContact = psPacket->m_psContact + psPacket->m_nuiContact;

            psContact->m_vN0 = vKN;
            psContact->m_vT0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
            psContact->m_vDepth = vDepth;
            psContact->m_vS0 = FCN_V(tgMH_SUB)( psSP0->m_vOrigin, vK1 );

            ++psPacket->m_nuiContact;

            /*TgDEBUG_COLLISION_TRIANGLE( iDBG_TriID, etgDEBUG_COLLISION_CODE1 ); */

            return (KTgS_OK);
        };
    };
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
