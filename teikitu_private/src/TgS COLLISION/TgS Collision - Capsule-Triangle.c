/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Capsule-Triangle.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "TgS COLLISION/TgS Collision - Sphere-Triangle.inl"
#include "TgS COLLISION/TgS Collision - Triangle-Segment.inl"
#include "TgS COLLISION/TgS Collision - Parallelogram-Linear.inl"

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

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

static TgRESULT
FCN_VO(tgCO_ST_Penetrate_Parallel_CP)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgSTRI,CPC) ARG1, VEC_OBJ_T(TgTUBE,CPC) ARG2 );

static TgRESULT
FCN_VO(tgCO_ST_Penetrate_Parallel_NoClip_CP)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgSTRI,CPC) ARG1, VEC_OBJ_T(TgTUBE,CPC) ARG2 );

static TgRESULT
FCN_VO(tgCO_ST_Penetrate_Sphere_Cap_CP)(
    VEC_OBJ_T(STg2_CO_Packet,PC) OUT0, VEC_OBJ_T(TgTUBE,CPC) ARG1, VEC_OBJ_T(TgSTRI,CPC) ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4 );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- FCN_VO(tgCO_ST_Penetrate_CP) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN_VO(tgCO_ST_Penetrate_CP)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_OBJ_T(TgSTRI,CPC) psST0, VEC_OBJ_T(TgTUBE,CPC) psCP0 )
{
    VEC_T(1)                            vCP0_UX[3], vCP0_OG;

    TgPARAM_CHECK(FCN_VO(tgGM_TB_Is_Valid)(psCP0) && FCN_VO(tgGM_ST_Is_Valid)(psST0));

    if (0 == psPacket->m_nuiMaxContact || psPacket->m_nuiContact >= psPacket->m_nuiMaxContact || nullptr == psPacket->m_psContact)
    {
        return (KTgE_FAIL);
    };

    FCN_V(tgMH_Query_Reference_Frame,3)( vCP0_UX + 0, vCP0_UX + 1, vCP0_UX + 2, &vCP0_OG, &psCP0->m_mReference_Frame );

    {
        /* Primitive Culling - Set of criteria required for the primitive to be considered penetrating the triangle. */

        VEC_OBJ_T(STg2_CO_Contact,P)        psContact;
        TgBOOL                              bResultCreated = false;
        TgRESULT                            iResult;
        VEC_T(1)                            vDistSq, vPM_CT0, vPM_CT1, vPM_CP0, vDepth;

        VEC_T(1,C)                          vK0 = FCN_V(tgMH_SUB)( vCP0_OG, psST0->m_sCT.m_sET.m_sPT.m_avPoint[0] );
        VEC_T(1,C)                          vDS_N = FCN_V(tgMH_DOT)( psST0->m_sCT.m_sET.m_sPT.m_vNormal, vK0 );
        VEC_T(1,C)                          vEX_N = FCN_V(tgMH_DOT)( psST0->m_sCT.m_sET.m_sPT.m_vNormal, psCP0->m_vHAX );
        VEC_T(1,C)                          vS0_N = FCN_V(tgMH_SUB)( vDS_N, vEX_N );
        VEC_T(1,C)                          vS1_N = FCN_V(tgMH_ADD)( vDS_N, vEX_N );

        /*TgDEBUG_COLLISION_TRIANGLE_CREATEID( iDBG_TriID, psST0, etgDEBUG_COLLISION_ENTERFCN ); */

        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vS0_N, psCP0->m_vRadius ) ))
        {
            if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vS1_N, psCP0->m_vRadius ) ))
            {
                /* Either both of the capsule's end points are below the plane or more than radius above the plane. */
                return (KTgE_NO_INTERSECT);
            };
        };

        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vS0_N, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ))
        {
            if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vS1_N, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ))
            {
                /* Either both of the capsule's end points are below the plane or more than radius above the plane. */
                return (KTgE_NO_INTERSECT);
            };
        };

        /*TgDEBUG_COLLISION_TRIANGLE( iDBG_TriID, etgDEBUG_COLLISION_PASSED_REJECT ); */

        /* Check the projection of the capsule primary axis against the triangle normal. If its near zero (i.e. the two vectors are near perpendicular), the capsule must */
        /* be near-parallel to the triangle. In this case the method of closest proximity will not work, and the axis segment will instead be clipped to triangle space. */

        if (FCN_V(tgMH_Is_NR0)( vEX_N ))
        {
            /* Since the capsule is near-parallel to the triangle itself, in terms of the contact surface, it is no longer different than a regular tube.  Execute that */
            /* primitive's parallel case to generate the contact points. */
            if (TgFAILED( iResult = FCN_VO(tgCO_ST_Penetrate_Parallel_CP)( psPacket, psST0, psCP0 ) ))
            {
                return (iResult);
            };
        };

        /*TgDEBUG_COLLISION_TRIANGLE( iDBG_TriID, etgDEBUG_COLLISION_CODE2 ); */

        /* Find the minimal distance and points of closest proximity for the capsule's axis and the triangle. */

        vDistSq = FCN_VO(tgCO_ST_ClosestSq_PM_SG)( &vPM_CT0, &vPM_CT1, &vPM_CP0, psST0, &psCP0->m_sAX );

        /* Intersection is impossible if the minimal distance is greater than the capsule's radius. */

        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vDistSq, psCP0->m_vRadiusSq ) ))
        {
            return (KTgE_NO_INTERSECT);
        };

        /* If the closest point on the triangle to the capsule's axis is not on a valid edge, then the generated axis is ignored and the system falls back to creating */
        /* contacts for the two spherical caps. */

        if (!FCN_V(tgMH_Is_NR0)( vPM_CP0 ) && !FCN_V(tgMH_Is_NR1)( vPM_CP0 ) && !FCN_VO(tgGM_ST_Is_Point_Culled)( psST0, vPM_CT0, vPM_CT1 ))
        {
            /* Create contacts only for the tube portion of the capsule. */
            /* Create the two points of closest proximity and the corresponding vector difference between the two. */

            VEC_T(1,C)                          vK1 = FCN_V(tgMH_MUL)( vPM_CT0, psST0->m_sCT.m_sET.m_avEdge[0] );
            VEC_T(1,C)                          vK2 = FCN_V(tgMH_MUL)( vPM_CT1, psST0->m_sCT.m_sET.m_avEdge[2] );
            VEC_T(1,C)                          vK4 = FCN_V(tgMH_MUL)( vPM_CP0, psCP0->m_sAX.m_vDirN );
            VEC_T(1,C)                          vK5 = FCN_V(tgMH_SUB)( vK1, vK2 );
            VEC_T(1,C)                          vCP0 = FCN_V(tgMH_ADD)( psCP0->m_sAX.m_vOrigin, vK4 );
            VEC_T(1,C)                          vCT1 = FCN_V(tgMH_ADD)( psST0->m_sCT.m_sET.m_sPT.m_avPoint[0], vK5 );
            VEC_T(1,C)                          vK3 = FCN_V(tgMH_SUB)( vCP0, psST0->m_sCT.m_sET.m_sPT.m_avPoint[0] );
            VEC_T(1,C)                          vTest = FCN_V(tgMH_DOT)( vK3, psST0->m_sCT.m_sET.m_sPT.m_vNormal );
            VEC_T(1,C)                          vK6 = FCN_V(tgMH_SUB)( vCP0, vCT1 );
            VEC_T(1,C)                          vK7 = FCN_V(tgMH_SUB)( vCT1, vCP0 );
            TgBOOL_C                            bTest = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vTest, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) );

            VEC_T(1)                            vNormal = bTest ? vK6 : vK7;

            /* Calculate the resultant penetration depth at this point. */

            VEC_T(1,C)                          vDist = bTest ? FCN_V(tgMH_SQRT)( vDistSq ) : FCN_V(tgMH_NEG)( FCN_V(tgMH_SQRT)( vDistSq ) );
            TgBOOL                              bUseNormal = !FCN_V(tgMH_Is_NR0)( vDistSq );

            vDepth = FCN_V(tgMH_MAX)( FCN_V(tgMH_SUB)( psCP0->m_vRadius, vDist ), FCN_V(tgMH_SET1)( TYPE_K(0) ) );

            /*  Check to see if the normal of intersection should be replaced by the triangle's normal.  This is done to reduce floating point noise in the system where */
            /* near-normal results are returned.  By forcing it to the triangle's normal, extraneous rotations are minimized. The other possibility is that the capsule's */
            /* segment intersects the triangle itself, thus, requiring the selection of the triangle's normal for the intersection. */

            if (bUseNormal)
            {
                vNormal = FCN_V(tgMH_NORM)( vNormal );

                /* Check to see if the resultant normal is near that of the triangle's.  If they are close then use the triangle's normal to help further reduce */
                /* floating point noise. */
                bUseNormal = FCN_V(tgMH_Is_NR1)( FCN_V(tgMH_DOT)( vNormal, psST0->m_sCT.m_sET.m_sPT.m_vNormal ) );
            };

            /* Create contact point. */

            psContact = psPacket->m_psContact + psPacket->m_nuiContact;

            {
                VEC_T(1,C)                          vK8 = bUseNormal ? vNormal : psST0->m_sCT.m_sET.m_sPT.m_vNormal;
                VEC_T(1,C)                          vK9 = FCN_V(tgMH_MUL)( psCP0->m_vRadius, vK8 );

                psContact->m_vS0 = FCN_V(tgMH_SUB)( vCT1, vK9 );
                psContact->m_vN0 = vK8;
                psContact->m_vT0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
                psContact->m_vDepth = vDepth;

                ++psPacket->m_nuiContact;
                bResultCreated = true;
            };
        };

        iResult = FCN_VO(tgCO_ST_Penetrate_Sphere_Cap_CP)( psPacket, psCP0, psST0, vS0_N, FCN_V(tgMH_SUB)( vCP0_OG, psCP0->m_vHAX ) );
        switch (iResult)
        {
            case KTgE_MAX_CONTACTS:
                return (KTgE_MAX_CONTACTS);
            default:
                bResultCreated |= TgSUCCEEDED( iResult );
        };

        iResult = FCN_VO(tgCO_ST_Penetrate_Sphere_Cap_CP)( psPacket, psCP0, psST0, vS1_N, FCN_V(tgMH_ADD)( vCP0_OG, psCP0->m_vHAX ) );
        switch (iResult)
        {
            case KTgE_MAX_CONTACTS:
                return (KTgE_MAX_CONTACTS);
            default:
                bResultCreated |= TgSUCCEEDED( iResult );
        };

        /*TgDEBUG_COLLISION_TRIANGLE( iDBG_TriID, bResultCreated ? etgDEBUG_COLLISION_FINAL : etgDEBUG_COLLISION_CODE4 ); */

        return (bResultCreated ? KTgS_OK : KTgE_NO_INTERSECT);
    };
}


/* ---- FCN_VO(tgCO_CP_Test_Sweep_ST) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL FCN_VO(tgCO_CP_Test_Sweep_ST)( VEC_OBJ_T(TgSTRI,CPC) psST0, VEC_OBJ_T(TgTUBE,CPC) psCP0, VEC_OBJ_T(TgDELTA,CPC) psDT )
{
    VEC_OBJ_T(TgPARALLELOGRAM)          sSweptCapsule;
    VEC_T(1)                            vPM_T0, vPM_T1, vPM_T2, vNM, vTestSq;

    VEC_T(1,C)                          vCP0_UAX = FCN_VO(tgGM_TB_Query_Axis_Unit)( psCP0 );
    VEC_T(1,C)                          vUDT_CA = FCN_V(tgMH_DOT)( psDT->m_vUDT, vCP0_UAX );

    TgERROR( FCN_VO(tgGM_TB_Is_Valid)( psCP0 ) && FCN_VO(tgGM_ST_Is_Valid)( psST0 ) );

    if (FCN_V(tgMH_Is_NR1)( vUDT_CA )) /* Delta vector is parallel to the capsule axis. */
    {
        vTestSq = FCN_VO(tgCO_ST_ClosestSq_PM_LR11)( &vPM_T0, &vPM_T1, &vPM_T2, psST0, psCP0->m_sAX.m_vOrigin, FCN_V(tgMH_ADD)( psCP0->m_sAX.m_vDirN, psDT->m_vDT ) );
        return (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTestSq, psCP0->m_vRadiusSq ) ));
    };

    if (FCN_V(tgMH_Is_NR0)( FCN_V(tgMH_ADD)( vUDT_CA, FCN_V(tgMH_SET1)( TYPE_K(1) ) ) )) /* Delta vector is parallel to the capsule axis. */
    {
        VEC_T(1,C)                          vK0 = FCN_V(tgMH_ADD)( psCP0->m_sAX.m_vOrigin, psDT->m_vDT );
        VEC_T(1,C)                          vK1 = FCN_V(tgMH_SUB)( psCP0->m_sAX.m_vDirN, psDT->m_vDT );

        vTestSq = FCN_VO(tgCO_ST_ClosestSq_PM_LR11)( &vPM_T0, &vPM_T1, &vPM_T2, psST0, vK0, vK1 );
        return (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTestSq, psCP0->m_vRadiusSq ) ));
    }
    else
    {
        /* Test to see if the swept capsule (represented by the edges of a parallelogram) comes within range of the triangle. */
        VEC_T(1,C)                          vK3 = FCN_V(tgMH_ADD)( psCP0->m_sAX.m_vOrigin, psDT->m_vDT );
        VEC_T(1,C)                          vK4 = FCN_V(tgMH_ADD)( psCP0->m_sAX.m_vOrigin, psCP0->m_sAX.m_vDirN );

        vTestSq = FCN_VO(tgCO_ST_ClosestSq_PM_LR11)( &vPM_T0, &vPM_T1, &vPM_T2, psST0, psCP0->m_sAX.m_vOrigin, psCP0->m_sAX.m_vDirN );
        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTestSq, psCP0->m_vRadiusSq ) ))
        {
            return (true);
        };

        vTestSq = FCN_VO(tgCO_ST_ClosestSq_PM_LR11)( &vPM_T0, &vPM_T1, &vPM_T2, psST0, psCP0->m_sAX.m_vOrigin, psDT->m_vDT );
        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)(FCN_V(tgMH_CMP_LT)(vTestSq, psCP0->m_vRadiusSq)))
        {
            return (true);
        };

        vTestSq = FCN_VO(tgCO_ST_ClosestSq_PM_LR11)( &vPM_T0, &vPM_T1, &vPM_T2, psST0, vK3, psCP0->m_sAX.m_vDirN );
        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)(FCN_V(tgMH_CMP_LT)(vTestSq, psCP0->m_vRadiusSq)))
        {
            return (true);
        };

        vTestSq = FCN_VO(tgCO_ST_ClosestSq_PM_LR11)( &vPM_T0, &vPM_T1, &vPM_T2, psST0, vK4, psDT->m_vDT );
        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)(FCN_V(tgMH_CMP_LT)(vTestSq, psCP0->m_vRadiusSq)))
        {
            return (true);
        };
    };

    /* Test to see if the triangle ever comes within range of the swept capsule (represented by a parallelogram) */

    vNM = FCN_V(tgMH_UCX)( psCP0->m_sAX.m_vDirN, psDT->m_vDT );
    FCN_VO(tgGM_PE_Init)( &sSweptCapsule, psCP0->m_sAX.m_vOrigin, psCP0->m_sAX.m_vDirN, psDT->m_vDT, vNM );

    if (
        FCN_VO(tgCO_PE_Test_LR11)( &sSweptCapsule, psST0->m_sCT.m_sET.m_sPT.m_avPoint[0], psST0->m_sCT.m_sET.m_avEdge[0] ) ||
        FCN_VO(tgCO_PE_Test_LR11)( &sSweptCapsule, psST0->m_sCT.m_sET.m_sPT.m_avPoint[0], psST0->m_sCT.m_sET.m_avEdge[1] ) ||
        FCN_VO(tgCO_PE_Test_LR11)( &sSweptCapsule, psST0->m_sCT.m_sET.m_sPT.m_avPoint[1], psST0->m_sCT.m_sET.m_avEdge[2] )
    )
    {
        return (true);
    };

    return (false);
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- FCN_VO(tgCO_ST_Penetrate_Parallel_CP) ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT FCN_VO(tgCO_ST_Penetrate_Parallel_CP)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_OBJ_T(TgSTRI,CPC) psST0, VEC_OBJ_T(TgTUBE,CPC) psCP0 )
{
    /* The capsule is, within tolerance, parallel to the triangle plane.  The format of the surface of contact is therefore definitively a longitudinal surface - */
    /* stretching along the capsule.  It is necessary to trap this specific case since the non-parallel case will use a closest point algorithm derivative.  Using that */
    /* system will cause a varying and random selection of one of the capsule extremities - which would then introduce a time varying reaction force resulting in */
    /* an unrealistic rocking motion or could potentially feed existing rotations.  Keep in mind that since the selection process would be at the extremities, an */
    /* unbalanced moment would be added into the simulation which could be very problematic. */

    VEC_T(1)                            vPM_T0, vPM_T1;

    if (TgFAILED( FCN_VO(tgCO_ST_Clip_PM_SG)( &vPM_T0, &vPM_T1, psST0, &psCP0->m_sAX) ))
    {
        /* The capsule axis does not exist anywhere in the triangle's normal extruded space.  A specific contact routine will create the contacts between the triangle */
        /* edge and the capsule. */

        return (FCN_VO(tgCO_ST_Penetrate_Parallel_NoClip_CP)(psPacket, psST0, psCP0));
    }
    else
    {
        VEC_OBJ_T(STg2_CO_Contact,P)        psContact;
        TgRESULT                            iResult;

        VEC_T(1,C)                          vK0 = FCN_V(tgMH_MUL)( vPM_T0, psCP0->m_sAX.m_vDirN );
        VEC_T(1,C)                          vK1 = FCN_V(tgMH_MUL)( vPM_T1, psCP0->m_sAX.m_vDirN );
        VEC_T(1,C)                          vP0 = FCN_V(tgMH_ADD)( psCP0->m_sAX.m_vOrigin, vK0 );
        VEC_T(1,C)                          vP1 = FCN_V(tgMH_ADD)( psCP0->m_sAX.m_vOrigin, vK1 );

        VEC_T(1,C)                          vK2 = FCN_V(tgMH_SUB)( vP0, psST0->m_sCT.m_sET.m_sPT.m_avPoint[0] );
        VEC_T(1,C)                          vK3 = FCN_V(tgMH_SUB)( vP1, psST0->m_sCT.m_sET.m_sPT.m_avPoint[0] );
        VEC_T(1,C)                          vDist0 = FCN_V(tgMH_SUB)( psCP0->m_vRadius, FCN_V(tgMH_DOT)( vK2, psST0->m_sCT.m_sET.m_sPT.m_vNormal ) );
        VEC_T(1,C)                          vDist1 = FCN_V(tgMH_SUB)( psCP0->m_vRadius, FCN_V(tgMH_DOT)( vK3, psST0->m_sCT.m_sET.m_sPT.m_vNormal ) );

        iResult = KTgE_NO_INTERSECT;

        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GE)( vDist0, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ))
        {
            if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
            {
                return (KTgE_MAX_CONTACTS);
            }
            else
            {
                VEC_T(1,C)                          vK4 = FCN_V(tgMH_MUL)( psCP0->m_vRadius, psST0->m_sCT.m_sET.m_sPT.m_vNormal );

                psContact = psPacket->m_psContact + psPacket->m_nuiContact;

                psContact->m_vS0 = FCN_V(tgMH_SUB)( vP0, vK4 );
                psContact->m_vN0 = psST0->m_sCT.m_sET.m_sPT.m_vNormal;
                psContact->m_vT0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
                psContact->m_vDepth = vDist0;

                ++psPacket->m_nuiContact;
            };

            iResult = KTgS_OK;
        };

        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GE)( vDist1, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ))
        {
            if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
            {
                return (KTgE_MAX_CONTACTS);
            }
            else
            {
                VEC_T(1,C)                          vK5 = FCN_V(tgMH_MUL)( psCP0->m_vRadius, psST0->m_sCT.m_sET.m_sPT.m_vNormal );

                psContact = psPacket->m_psContact + psPacket->m_nuiContact;

                psContact->m_vS0 = FCN_V(tgMH_SUB)( vP1, vK5 );
                psContact->m_vN0 = psST0->m_sCT.m_sET.m_sPT.m_vNormal;
                psContact->m_vT0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
                psContact->m_vDepth = vDist1;

                ++psPacket->m_nuiContact;
            };

            iResult = KTgS_OK;
        };

        return (iResult);
    }
}


/* ---- FCN_VO(tgCO_ST_Penetrate_Parallel_NoClip_CP) ----------------------------------------------------------------------------------------------------------------------------- */
/* Used when the capsule is parallel to the triangle plane, and the axis lies outside of the normal extruded triangle space.                                                       */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT FCN_VO(tgCO_ST_Penetrate_Parallel_NoClip_CP)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_OBJ_T(TgSTRI,CPC) psST0, VEC_OBJ_T(TgTUBE,CPC) psCP0 )
{
    /* It is now known that the capsule axis does not pass through the triangle normal extruded space.  However, contact can still occur because the triangle's edge */
    /* and/or vertices can penetrate the capsule resulting in a non-planar directed normal.  Special care must be taken into account if the resulting penetrating feature */
    /* is parallel to the capsule. */

    /* Method: Find the nearest triangle feature to the capsule.  If the feature is not enabled then its assumed that the resulting adjoined primitives will produce the */
    /* required contacts and the feature can be ignored and the procedure terminated.  No matter the type of feature found the resulting edge or connected edges should */
    /* be tested to see if they are parallel to the capsule axis so that multiple points of contact can be created.  The secondary contact point should also be tested */
    /* for feature reduction. */

    VEC_T(1,C)                          vCP0_OG = FCN_VO(tgGM_TB_Query_Origin)( psCP0 );
    VEC_T(1,C)                          vCP0_UAX = FCN_VO(tgGM_TB_Query_Axis_Unit)( psCP0 );
    VEC_T(1,C)                          vS0 = FCN_V(tgMH_SUB)( vCP0_OG, psCP0->m_vHAX );
    VEC_T(1,C)                          vS1 = FCN_V(tgMH_ADD)( vCP0_OG, psCP0->m_vHAX );
    VEC_T(1,C)                          vAX = psCP0->m_sAX.m_vDirN;
    VEC_T(1,C)                          vAX_AX = FCN_V(tgMH_LSQ)( vAX );

    TgRSIZE_C                           nuiContact = psPacket->m_nuiContact;
    VEC_OBJ_T(STg2_CO_Contact,P)        psContact;

    for (TgRSIZE uiEdge = 0; uiEdge < 3; ++uiEdge)
    {
        /* Test each vertex individually to prevent the creation of duplicate contacts from the edge routines (shared vertices). */
        if (FCN_VO(tgGM_ST_Test_Point)( psST0, uiEdge ))
        {
            FCN_VO(tgCO_PT_Penetrate_CP)( psPacket, psST0->m_sCT.m_sET.m_sPT.m_avPoint[uiEdge], psCP0 );
        };

        if (!FCN_VO(tgGM_ST_Test_Edge)( psST0, uiEdge )) /* Only collide with those edges marked as valid */
        {
            continue;
        }
        else
        {
            /* Contacts are created only for those edges where the capsule exists entirely in the positive half-space and at least minimally exists in the feature space. */

            VEC_T(1,C)                          vEP = psST0->m_sCT.m_sET.m_sPT.m_avPoint[uiEdge];
            VEC_T(1,C)                          vEN = psST0->m_avPlane[uiEdge].m_vNormal;
            VEC_T(1,C)                          vET = psST0->m_sCT.m_sET.m_avEdge[uiEdge];

            VEC_T(1,C)                          vK0 = FCN_V(tgMH_SUB)( vS0, vEP );
            VEC_T(1,C)                          vK1 = FCN_V(tgMH_SUB)( vS1, vEP );
            VEC_T(1,C)                          vK2 = FCN_V(tgMH_SUB)( vS0, vEP );
            VEC_T(1,C)                          vK3 = FCN_V(tgMH_SUB)( vS1, vEP );

            VEC_T(1,C)                          vDist0 = FCN_V(tgMH_DOT)( vK0, vET );
            VEC_T(1,C)                          vDist1 = FCN_V(tgMH_DOT)( vK1, vET );
            VEC_T(1,C)                          vTest0 = FCN_V(tgMH_DOT)( vK2, vEN );
            VEC_T(1,C)                          vTest1 = FCN_V(tgMH_DOT)( vK3, vEN );

            VEC_T(1,C)                          vET_ET = FCN_V(tgMH_LSQ)( vET );

            if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vDist0, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ))
            {
                if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vDist1, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ))
                {
                    continue;
                };
            };

            if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vDist0, vET_ET ) ))
            {
                if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vDist1, vET_ET ) ))
                {
                    continue;
                };
            };

            if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTest0, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ))
            {
                if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTest1, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ))
                {
                    continue;
                };
            };

            /* The capsule is known to be on the positive side of the edge normal half-space and is captured passing through it. */

            if (FCN_V(tgMH_Is_NR0)( FCN_V(tgMH_DOT)( vCP0_UAX, vEN ) ))
            {
                /* The capsule axis is parallel to the edge */

                VEC_T(1)                            vT0, vT1, vT2, vT3;

                VEC_T(1,C)                          vDS = FCN_V(tgMH_SUB)( vEP, vS0 );

                /*                                  Projection Values */
                VEC_T(1,C)                          vAX_ET = FCN_V(tgMH_DOT)( vAX, vET );
                VEC_T(1,C)                          vDS_AX = FCN_V(tgMH_DOT)( vDS, vAX );
                VEC_T(1,C)                          vDS_ET = FCN_V(tgMH_NEG)( FCN_V(tgMH_DOT)( vDS, vET ) );

                VEC_T(1,C)                          vDE_AX = FCN_V(tgMH_ADD)( vDS_AX, vAX_ET ); /* vDE = vEP+vET, fDE_ET = (vEP+vET - vS0)•vAX */
                VEC_T(1,C)                          vDF_ET = FCN_V(tgMH_SUB)( vAX_ET, vDS_ET ); /* vDF = vS0+vAX, fDF_ET = (vS0+vAX - vEP)•vET */

                if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GE)( vAX_ET, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ))
                {
                    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vDE_AX, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ))
                    {
                        continue;
                    };

                    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vDS_AX, FCN_V(tgMH_SET1)( TYPE_K(1) ) ) ))
                    {
                        continue;
                    };
                };

                if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( vAX_ET, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ))
                {
                    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vDS_AX, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ))
                    {
                        continue;
                    };

                    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vDE_AX, FCN_V(tgMH_SET1)( TYPE_K(1) ) ) ))
                    {
                        continue;
                    };
                };

                {
                    TgBOOL                              bTest;

                    VEC_T(1,C)                          vTA = FCN_V(tgMH_DIV)( vDS_AX, vAX_AX );
                    VEC_T(1,C)                          vTC = FCN_V(tgMH_DIV)( vDE_AX, vAX_AX );

                    /* Point 0 of segment 0 if contained in segment 1, otherwise if segments are mutually directed point 0 of segment 1, else point 1 of segment 1. */

                    bTest = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GE)( vDS_ET, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) );
                    bTest = bTest && FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GE)( vET_ET, vDS_ET ) );

                    if (bTest)
                    {
                        vT0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
                        vT1 = FCN_V(tgMH_DIV)( vDS_ET, vET_ET );
                    }
                    else
                    {
                        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GE)( vAX_ET, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ))
                        {
                            vT0 = vTA;
                            vT1 = FCN_V(tgMH_SET1)( TYPE_K(0) );
                        }
                        else
                        {
                            vT0 = vTC;
                            vT1 = FCN_V(tgMH_SET1)( TYPE_K(1) );
                        };
                    };

                    /* Point 1 of segment 0 if contained in segment 1, otherwise if segments are mutually directed point 1 of segment 1, else point 0 of segment 1. */

                    bTest = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GE)( vDF_ET, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) );
                    bTest = bTest && FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GE)( vET_ET, vDF_ET ) );

                    if (bTest)
                    {
                        vT2 = FCN_V(tgMH_SET1)( TYPE_K(1) );
                        vT3 = FCN_V(tgMH_DIV)( vDF_ET, vET_ET );
                    }
                    else
                    {
                        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GE)( vAX_ET, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ))
                        {
                            vT2 = vTC;
                            vT3 = FCN_V(tgMH_SET1)( TYPE_K(1) );
                        }
                        else
                        {
                            vT2 = vTA;
                            vT3 = FCN_V(tgMH_SET1)( TYPE_K(0) );
                        };
                    };

                    TgERROR(FCN_V(tgMH_Is_Contained_In_Interval)( vT0, FCN_V(tgMH_SET1)( TYPE_K(0) ), FCN_V(tgMH_SET1)( TYPE_K(1) ) ));
                    TgERROR(FCN_V(tgMH_Is_Contained_In_Interval)( vT1, FCN_V(tgMH_SET1)( TYPE_K(0) ), FCN_V(tgMH_SET1)( TYPE_K(1) ) ));
                    TgERROR(FCN_V(tgMH_Is_Contained_In_Interval)( vT2, FCN_V(tgMH_SET1)( TYPE_K(0) ), FCN_V(tgMH_SET1)( TYPE_K(1) ) ));
                    TgERROR(FCN_V(tgMH_Is_Contained_In_Interval)( vT3, FCN_V(tgMH_SET1)( TYPE_K(0) ), FCN_V(tgMH_SET1)( TYPE_K(1) ) ));
                };

                {
                    VEC_T(1)                            vNM, vMAG;

                    VEC_T(1,C)                          vK4 = FCN_V(tgMH_MUL)( vT0, vAX );
                    VEC_T(1,C)                          vK5 = FCN_V(tgMH_MUL)( vT1, vET );
                    VEC_T(1,C)                          vK6 = FCN_V(tgMH_MUL)( vT2, vAX );
                    VEC_T(1,C)                          vK7 = FCN_V(tgMH_MUL)( vT3, vET );
                    VEC_T(1,C)                          vP0 = FCN_V(tgMH_ADD)( vS0, vK4 );
                    VEC_T(1,C)                          vP1 = FCN_V(tgMH_ADD)( vEP, vK5 );
                    VEC_T(1,C)                          vK8 = FCN_V(tgMH_SUB)( vP0, vP1 );
                    VEC_T(1,C)                          vP2 = FCN_V(tgMH_ADD)( vS0, vK6 );
                    VEC_T(1,C)                          vP3 = FCN_V(tgMH_ADD)( vEP, vK7 );
                    VEC_T(1,C)                          vK9 = FCN_V(tgMH_SUB)( vP2, vP3 );

                    vNM = FCN_V(tgMH_NORM_LEN)( &vMAG, vK8 );

                    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vMAG, psCP0->m_vRadius ) ) && !FCN_V(tgMH_Is_NR0)( vT1 ) && !FCN_V(tgMH_Is_NR1)( vT1 ))
                    {
                        if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
                        {
                            return (KTgE_MAX_CONTACTS);
                        }
                        else
                        {
                            psContact = psPacket->m_psContact + psPacket->m_nuiContact;

                            psContact->m_vS0 = FCN_V(tgMH_SUB)( vP0, FCN_V(tgMH_MUL)( psCP0->m_vRadius, vNM ) );
                            psContact->m_vN0 = vNM;
                            psContact->m_vT0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
                            psContact->m_vDepth = FCN_V(tgMH_SUB)( psCP0->m_vRadius, vMAG );

                            ++psPacket->m_nuiContact;
                        };
                    };

                    vNM = FCN_V(tgMH_NORM_LEN)( &vMAG, vK9 );

                    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vMAG, psCP0->m_vRadius ) ) && !FCN_V(tgMH_Is_NR0)( vT3 ) && !FCN_V(tgMH_Is_NR1)( vT3 ))
                    {
                        if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
                        {
                            return (KTgE_MAX_CONTACTS);
                        }
                        else
                        {
                            psContact = psPacket->m_psContact + psPacket->m_nuiContact;

                            psContact->m_vS0 = FCN_V(tgMH_SUB)( vP2, FCN_V(tgMH_MUL)( psCP0->m_vRadius, vNM ) );
                            psContact->m_vN0 = vNM;
                            psContact->m_vT0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
                            psContact->m_vDepth = FCN_V(tgMH_SUB)( psCP0->m_vRadius, vMAG );

                            ++psPacket->m_nuiContact;
                        };
                    };
                };
            }
            else
            {
                VEC_T(1,C)                          vK4 = FCN_V(tgMH_SUB)( vS1, vS0 );
                VEC_T(1)                            vT0, vT1;
                VEC_T(1,C)                          vDistSq = FCN_VO(tgCO_LR11_ClosestSq_PM_LR11)( &vT0, &vT1, vS0, vK4, vEP, vET );

                if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vDistSq, psCP0->m_vRadiusSq ) ) && !FCN_V(tgMH_Is_NR0)( vT1 ) && !FCN_V(tgMH_Is_NR1)( vT1 ))
                {
                    /* The closest point on the triangle is not a vertex - and the edge is valid. */

                    if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
                    {
                        return (KTgE_MAX_CONTACTS);
                    }
                    else
                    {
                        VEC_T(1)                            vDist;

                        VEC_T(1,C)                          vKA = FCN_V(tgMH_MUL)( FCN_V(tgMH_SUB)( FCN_V(tgMH_SET1)( TYPE_K(1) ), vT1 ), vS0 );
                        VEC_T(1,C)                          vKE = FCN_V(tgMH_MUL)( vT1, vS1 );
                        VEC_T(1,C)                          vP0 = FCN_V(tgMH_ADD)( vKA, vKE );
                        VEC_T(1,C)                          vKB = FCN_V(tgMH_SUB)( vP0, vEP );
                        VEC_T(1,C)                          vKC = FCN_V(tgMH_MUL)( vT1, vET );
                        VEC_T(1,C)                          vKD = FCN_V(tgMH_ADD)( vKB, vKC );
                        VEC_T(1,C)                          vNM = FCN_V(tgMH_NORM_LEN)( &vDist, vKD );
                        VEC_T(1,C)                          vK5 = FCN_V(tgMH_MUL)( psCP0->m_vRadius, vNM );

                        psContact = psPacket->m_psContact + psPacket->m_nuiContact;

                        psContact->m_vS0 = FCN_V(tgMH_SUB)( vP0, vK5 );
                        psContact->m_vN0 = vNM;
                        psContact->m_vT0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
                        psContact->m_vDepth = FCN_V(tgMH_SUB)( psCP0->m_vRadius, vDist );

                        ++psPacket->m_nuiContact;
                    };
                };
            };
        };
    };

    return (nuiContact == psPacket->m_nuiContact ? KTgE_NO_INTERSECT : KTgS_OK);
}


/* ---- FCN_VO(tgCO_ST_Penetrate_Sphere_Cap_CP) ------------------------------------------------------------------------------------------------------------------------------- */
/* Input:  psPacket: The current series of contact points for this query-series, and contact generation parameters.                                                                */
/* Input:  psCP0: Capsule primitive - contact points are generated on this primitive                                                                                               */
/* Input:  psST0: Space Triangle primitive                                                                                                                                         */
/* Input:  fDist: The minimal distance between the capsule axis (segment) and the triangle                                                                                         */
/* Input:  vP0: Point of closest proximity on the capsule axis between it and the triangle                                                                                         */
/* Output: psPacket: Points of penetration between the two primitives are added to it                                                                                              */
/* Return: Result Code                                                                                                                                                             */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT FCN_VO(tgCO_ST_Penetrate_Sphere_Cap_CP)(
    VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_OBJ_T(TgTUBE,CPC) psCP0, VEC_OBJ_T(TgSTRI,CPC) psST0, VEC_T(1,C) vDist, VEC_T(1,C) vP0 )
{
    VEC_OBJ_T(STg2_CO_Contact,P)                     psContact;

    /* Check the start cap (origin - axis) for contact generation. */

    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GE)( vDist, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ))
    {
        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GE)( vDist, psCP0->m_vRadius ) ))
        {
            return (KTgE_NO_INTERSECT);
        }
        else
        {
            VEC_OBJ_T(STg2_CO_Packet)           sCap_Packet;
            VEC_OBJ_T(STg2_CO_Contact)          sCap_Contact;
            VEC_OBJ_T(TgSPHERE)                 sCap;
            TgRESULT                            iResult;
            VEC_T(1)                            vK0, vK1;

            VEC_T(1,C)                          vCP0_OG = FCN_VO(tgGM_TB_Query_Origin)( psCP0 );

            /* Capsule cap is penetrating the triangle plane with the origin above the plane. Execute the sphere penetration code to generate the contact point for the */
            /* capsule cap.  However, since the caps are hemi-spherical in reality, it is necessary to examine the resultant contact point and make sure that the point */
            /* was not created on the illegal space of the sphere.  This is done by culling points out based on the their contact normal. */

            /* Create contact points for the two end caps. */
            sCap_Packet.m_psContact = &sCap_Contact;
            sCap_Packet.m_vSweepTol = FCN_V(tgMH_SET1)( TYPE_K(0) );
            sCap_Packet.m_nuiContact = 0;
            sCap_Packet.m_nuiMaxContact = 1;

            FCN_VO(tgGM_SP_Init)( &sCap, vP0, psCP0->m_vRadius );

            iResult = FCN_VO(tgCO_ST_Penetrate_SP)( &sCap_Packet, psST0, &sCap );

            vK0 = FCN_V(tgMH_SUB)( sCap_Contact.m_vS0, vP0 );
            vK1 = FCN_V(tgMH_SUB)( vP0, vCP0_OG );

            if (TgFAILED( iResult ) || FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( FCN_V(tgMH_DOT)( vK0, vK1 ), FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ))
            {
                return (KTgE_NO_INTERSECT);
            };

            if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
            {
                return (KTgE_MAX_CONTACTS);
            };

            psContact = psPacket->m_psContact + psPacket->m_nuiContact;

            psContact->m_vS0 = sCap_Contact.m_vS0;
            psContact->m_vN0 = sCap_Contact.m_vN0;
            psContact->m_vT0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
            psContact->m_vDepth = sCap_Contact.m_vDepth;

            ++psPacket->m_nuiContact;
            return (KTgS_OK);
        };
    }
    else
    {
        /* Capsule cap lies below the plane.  Thus, the sphere penetration code would have ignored it, so for the capsule it is necessary to deal with this separately. */
        /* In this case only generate a contact point if the cap position is contained inside of the normal extruded space of the triangle.  For this case, the contact */
        /* will only have a normal equal to the triangle's normal. */

        if (!FCN_VO(tgGM_ST_Is_Contained)( psST0, vP0 ))
        {
            return (KTgE_NO_INTERSECT);
        };

        if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
        {
            return (KTgE_MAX_CONTACTS);
        }
        else
        {
            VEC_T(1,C)                          vK2 = FCN_V(tgMH_MUL)( psCP0->m_vRadius, psST0->m_sCT.m_sET.m_sPT.m_vNormal );

            psContact = psPacket->m_psContact + psPacket->m_nuiContact;

            psContact->m_vS0 = FCN_V(tgMH_SUB)( vP0, vK2 );
            psContact->m_vN0 = psST0->m_sCT.m_sET.m_sPT.m_vNormal;
            psContact->m_vT0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
            psContact->m_vDepth = FCN_V(tgMH_SUB)( psCP0->m_vRadius, vDist );

            ++psPacket->m_nuiContact;
            return (KTgS_OK);
        };
    };
}



/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
