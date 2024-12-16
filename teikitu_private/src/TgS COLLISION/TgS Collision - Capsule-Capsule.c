/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Capsule-Capsule.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "TgS COLLISION/TgS Collision - Segment.inl"

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

/* ---- FCN_VO(tgCO_CP_Penetrate_CP) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN_VO(tgCO_CP_Penetrate_CP)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_OBJ_T(TgTUBE,CPC) psCP0, VEC_OBJ_T(TgTUBE,CPC) psCP1 )
{
    TgPARAM_CHECK( FCN_VO(tgGM_TB_Is_Valid)( psCP0 ) && FCN_VO(tgGM_TB_Is_Valid)( psCP1 ) );

    if (0 == psPacket->m_nuiMaxContact || psPacket->m_nuiContact >= psPacket->m_nuiMaxContact || nullptr == psPacket->m_psContact)
    {
        return (KTgE_FAIL);
    }
    else
    {
        VEC_T(1,C)                          vUAX_0 = FCN_VO(tgGM_TB_Query_Axis_Unit)( psCP0 );
        VEC_T(1,C)                          vUAX_1 = FCN_VO(tgGM_TB_Query_Axis_Unit)( psCP1 );
        VEC_T(1,C)                          vNxN = FCN_V(tgMH_UCX)( vUAX_0, vUAX_1 );
        VEC_T(1,C)                          vX0 = FCN_V(tgMH_LSQ)( vNxN );

        if (FCN_V(tgMH_Is_NR0)( vX0 ))
        {
            /* Since the capsules are near parallel, contact points will be created at the extreme points of the overlap space of both of the primary axes. */

            VEC_T(1,C)                          vC0 = FCN_VO(tgGM_TB_Query_Origin)( psCP0 );
            VEC_T(1,C)                          vC1 = FCN_VO(tgGM_TB_Query_Origin)( psCP1 );
            VEC_T(1,C)                          vAX1_C0 = FCN_V(tgMH_DOT)( vUAX_1, vC0 );
            VEC_T(1,C)                          vAX1_C1 = FCN_V(tgMH_DOT)( vUAX_1, vC1 );
            VEC_T(1,C)                          vX1 = FCN_V(tgMH_SUB)( vAX1_C1, vAX1_C0 );
            VEC_T(1,C)                          vX2 = FCN_V(tgMH_ABS)( vX1 );
            VEC_T(1,C)                          vSumExt = FCN_V(tgMH_ADD)( psCP0->m_vExtent, psCP1->m_vExtent );
            VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_LT)( vX2, vSumExt );

            if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_0 ))
            {
                return (FCN_VO(tgCO_Penetrate_Parallel)( psPacket, psCP0, psCP1, vAX1_C0, vAX1_C1 ));
            };

            /* Axes did not overlap - use the standard non-parallel algorithm */
        };

        return (FCN_VO(tgCO_Penetrate_NonParallel)( psPacket, psCP0, psCP1, vNxN ));
    };
}


/* ---- FCN_VO(tgCO_Penetrate_Parallel) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN_VO(tgCO_Penetrate_Parallel)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_OBJ_T(TgTUBE,CPC) psCP0, VEC_OBJ_T(TgTUBE,CPC) psCP1, VEC_T(1,C) vX1_O0, VEC_T(1,C) vX1_O1 )
{
    /* Calculate the normal of penetration. */

    VEC_T(1)                            vCP0_UX[3], vCP0_OG, vCP1_UX[3], vCP1_OG, vMag_NM, vRS, vNM;

    FCN_V(tgMH_Query_Reference_Frame,3)( vCP0_UX + 0, vCP0_UX + 1, vCP0_UX + 2, &vCP0_OG, &psCP0->m_mReference_Frame );
    FCN_V(tgMH_Query_Reference_Frame,3)( vCP1_UX + 0, vCP1_UX + 1, vCP1_UX + 2, &vCP1_OG, &psCP1->m_mReference_Frame );

    {
        VEC_T(1,C)                          vDS = FCN_V(tgMH_SUB)( vCP1_OG, vCP0_OG );
        VEC_T(1,C)                          vN0 = FCN_V(tgMH_DOT)( vDS, vCP1_UX[0] );
        VEC_T(1,C)                          vN1 = FCN_V(tgMH_DOT)( vDS, vCP1_UX[2] );
        VEC_T(1,C)                          vK0 = FCN_V(tgMH_MUL)( vN0, vCP1_UX[0] );
        VEC_T(1,C)                          vK1 = FCN_V(tgMH_MUL)( vN1, vCP1_UX[2] );
        VEC_T(1,C)                          vK2 = FCN_V(tgMH_ADD)( vK0, vK1 );

        vRS = FCN_V(tgMH_ADD)( psCP1->m_vRadius, psCP0->m_vRadius );
        vNM = FCN_V(tgMH_NORM_LEN)( &vMag_NM, vK2 );
    }

    {
        /* Check to make sure the two capsules are within range of each other on their mutually defined cross-sectional plane. */

        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vMag_NM, vRS ) ))
        {
            return (KTgE_NO_INTERSECT);
        }
        else
        {
            /* Find the overlap range of the two capsule axes. */

            VEC_OBJ_T(STg2_CO_Contact,P)        psContact;

            VEC_T(1,C)                          vMin = FCN_V(tgMH_MAX)( FCN_V(tgMH_SUB)( vX1_O1, psCP1->m_vExtent ), FCN_V(tgMH_SUB)( vX1_O0, psCP0->m_vExtent ) );
            VEC_T(1,C)                          vMax = FCN_V(tgMH_MIN)( FCN_V(tgMH_ADD)( vX1_O1, psCP1->m_vExtent ), FCN_V(tgMH_ADD)( vX1_O0, psCP0->m_vExtent ) );

            /* Determine the first (possibly only) point of contact.  If the difference between the minimum and the maximum on the range of overlap is smaller than the */
            /* minimal radii, create only one point.  This is the prevent creating two points within too close of a range of each other.  In this case, create the point at */
            /* the median of the range. */

            VEC_T(1,C)                          vRad = FCN_V(tgMH_MIN)( psCP1->m_vRadius, psCP0->m_vRadius );
            VEC_T(1,C)                          v1P_A = FCN_V(tgMH_SUB)( vMax, vMin );
            VEC_T(1,C)                          v1P_B = FCN_V(tgMH_MUL)( FCN_V(tgMH_SET1)( TYPE_K(2) ), vRad );
            TgBOOL_C                            bOnePoint = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( v1P_A, v1P_B ) );
            VEC_T(1,C)                          vK0_A = FCN_V(tgMH_DIV)( FCN_V(tgMH_ADD)( vMax, vMin ), FCN_V(tgMH_SET1)( TYPE_K(2) ) );
            VEC_T(1,C)                          vK0 = FCN_V(tgMH_SUB)( bOnePoint ? vK0_A : vMin, vX1_O1 );
            VEC_T(1,C)                          vK3 = FCN_V(tgMH_MUL)( vNM, psCP1->m_vRadius );
            VEC_T(1,C)                          vK4 = FCN_V(tgMH_SUB)( vCP1_OG, vK3 );
            VEC_T(1,C)                          vK5 = FCN_V(tgMH_MUL)( vK0, psCP1->m_vHAX );

            psContact = psPacket->m_psContact + psPacket->m_nuiContact;

            psContact->m_vS0 = FCN_V(tgMH_ADD)( vK4, vK5 );
            psContact->m_vN0 = vNM;
            psContact->m_vT0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
            psContact->m_vDepth = FCN_V(tgMH_SUB)( vRS, vNM );

            ++psPacket->m_nuiContact;

            if (!bOnePoint)
            {
                /* Create the second point at the maximal location on the overlap range. */

                VEC_T(1,C)                          vK6 = FCN_V(tgMH_MUL)( FCN_V(tgMH_SUB)( vMax, vX1_O1), psCP1->m_vHAX );

                if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
                {
                    return (KTgE_MAX_CONTACTS);
                };

                psContact = psPacket->m_psContact + psPacket->m_nuiContact;

                psContact->m_vS0 = FCN_V(tgMH_ADD)( vK4, vK6 );
                psContact->m_vN0 = vNM;
                psContact->m_vT0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
                psContact->m_vDepth = FCN_V(tgMH_SUB)( vRS, vNM );

                ++psPacket->m_nuiContact;
            };

            return (KTgS_OK);
        };
    };
}


/* ---- FCN_VO(tgCO_Penetrate_NonParallel) --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN_VO(tgCO_Penetrate_NonParallel)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_OBJ_T(TgTUBE,CPC) psCP0, VEC_OBJ_T(TgTUBE,CPC) psCP1, VEC_T(1,C) vNxN )
{
    VEC_T(1)                            vCP0, vCP1;

    VEC_T(1,C)                          vRS = FCN_V(tgMH_ADD)( psCP1->m_vRadius, psCP0->m_vRadius );
    VEC_T(1,C)                          vDistSq = FCN_VO(tgCO_SG_ClosestSq_SG)( &vCP0, &vCP1, &psCP1->m_sAX, &psCP0->m_sAX );

    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vDistSq, FCN_V(tgMH_MUL)( vRS, vRS ) ) ))
    {
        return (KTgE_NO_INTERSECT);
    }
    else
    {
        VEC_OBJ_T(STg2_CO_Contact,P)        psContact;
        VEC_T(1)                            vMag_NM;

        VEC_T(1,C)                          vK0 = FCN_V(tgMH_SUB)( vCP0, vCP1 );
        VEC_T(1,C)                          vNM = FCN_V(tgMH_NORM_LEN)( &vMag_NM, vK0 );
        TgBOOL_C                            bUseNormal = !FCN_V(tgMH_Is_NR0)( vMag_NM );
        VEC_T(1,C)                          vK1 = FCN_V(tgMH_MUL)( bUseNormal ? vNM : vNxN, psCP1->m_vRadius );

        psContact = psPacket->m_psContact + psPacket->m_nuiContact;

        psContact->m_vS0 = FCN_V(tgMH_SUB)( vCP0, vK1 );
        psContact->m_vN0 = bUseNormal ? vNM : vNxN;
        psContact->m_vT0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
        psContact->m_vDepth = FCN_V(tgMH_SUB)( vRS, vMag_NM );

        ++psPacket->m_nuiContact;

        return (KTgS_OK);
    }
}


/* ---- FCN_VO(tgCO_CP_Test_Sweep_CP) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL FCN_VO(tgCO_CP_Test_Sweep_CP)( VEC_OBJ_T(TgTUBE,CPC) psCP0, VEC_OBJ_T(TgTUBE,CPC) psCP1, VEC_OBJ_T(TgDELTA,CPC) psDT )
{
    VEC_T(1,C)                          vC0O = psCP0->m_sAX.m_vOrigin;
    VEC_T(1,C)                          vC0A = psCP0->m_sAX.m_vDirN;
    VEC_T(1,C)                          vC1O = psCP1->m_sAX.m_vOrigin;
    VEC_T(1,C)                          vC1A = psCP1->m_sAX.m_vDirN;

    VEC_T(1,C)                          vRS = FCN_V(tgMH_ADD)( psCP0->m_vRadius, psCP1->m_vRadius );
    VEC_T(1,C)                          vRSSq = FCN_V(tgMH_MUL)( vRS, vRS );
    VEC_T(1,C)                          vUAX_1 = FCN_VO(tgGM_TB_Query_Axis_Unit)( psCP1 );
    VEC_T(1,C)                          vUDT_CA = FCN_V(tgMH_DOT)( psDT->m_vUDT, vUAX_1 );

    TgPARAM_CHECK( FCN_VO(tgGM_TB_Is_Valid)(psCP0) && FCN_VO(tgGM_TB_Is_Valid)(psCP1) );

    /* Delta vector is parallel to the capsule axis. */

    if (FCN_V(tgMH_Is_NR1)( vUDT_CA ))
    {
        VEC_T(1)                            vTestSq, vK0, vK1;

        vTestSq = FCN_VO(tgCO_LR11_ClosestSq_PM_LR11)( &vK0, &vK1, vC0O, vC0A, vC1O, FCN_V(tgMH_ADD)( vC1A, psDT->m_vDT ) );
        return (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vTestSq, vRSSq ) ));
    };

    if (FCN_V(tgMH_Is_NR0)( FCN_V(tgMH_ADD)( vUDT_CA, FCN_V(tgMH_SET1)( TYPE_K(1) ) ) ))
    {
        VEC_T(1)                            vTestSq, vK0, vK1;

        vTestSq = FCN_VO(tgCO_LR11_ClosestSq_PM_LR11)( &vK0, &vK1, vC0O, vC0A, FCN_V(tgMH_ADD)( vC1O, psDT->m_vDT ), FCN_V(tgMH_SUB)( vC1A, psDT->m_vDT ) );
        return (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vTestSq, vRSSq ) ));
    }
    else
    {
        VEC_T(1)                            vTestSq, vT0, vT1, vT2;
        VEC_OBJ_T(TgPARALLELOGRAM)          sSweptCapsule;

        FCN_VO(tgGM_PE_Init)( &sSweptCapsule, vC1O, vC1A, psDT->m_vDT, FCN_V(tgMH_UCX)( vC1A, psDT->m_vDT ) );

        vTestSq = FCN_VO(tgCO_PE_ClosestSq_PM_LR11)( &vT0, &vT1, &vT2, &sSweptCapsule, vC0O, vC0A );
        return (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vTestSq, vRSSq ) ));
    }
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
