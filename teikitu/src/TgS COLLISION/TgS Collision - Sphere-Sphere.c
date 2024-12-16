/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Sphere-Sphere.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

/** Let S0 and S1 represent two spheres, with radius R0, R1, centers C0,C1 and velocities V0, V1 respectively.
    W.O.L.O.G. Perform the following calculations within S0 frame of reference.
    Assume the frame of reference in non-rotational (only translation).

    SWEEP TEST

    As with all sweep tests, an arbitrary body is chosen as the principal reference frame so that only the relative motion of one of the bodies is relevant.
    The solution is as follows,
     (1) Create a line (RV) using the centre of the second sphere and the vector of relative motion.
     (2) Form a right-sided triangle.
         (a) The hypotenuse is the sum of the sphere radii.
         (b) The known side is the line from the centre of the first sphere to the closest point on line RV.
         (c) The length of the remaining side (along RV) is the distance from the point of closest proximity and the
             point of first contact between the two spheres.

                                 .(C0)
                                /|\
                               / | \
                              /  |  \
                             /   |   \
                            /    |    \
                           /(R0) |     \(R0)
             (R1)/    (R1)/      |
                /        /       |
               /        /        |
              .--------.---------.--------------> (RV)
             (C1)     (P1)      (P0)

    Let RV = V1 - V0, the relative velocity of S1 in the frame of reference of S0
    Let RV_N be the normalized RV vector, and RV_L the length of the original RV vector
    Let DS = C1 - C0, the vector joining the two sphere centers
    Let RS = R0+R1, the sum of the radii of the two spheres

    Test 1: Pre penetration - The spheres are in contact if DS•DS < RS•RS
    Test 2: Movement - RV_L ~= 0, no contact takes place
    Test 3: Parallel - ψ = DS•RV_N
      Contact can not occur under the following conditions:
        [ψ > 0]          - Second sphere is moving away from the first sphere
        [ψ < -(RV_L+RS)] - Motion is insufficient for them to come within proximity
    Test 4: Perpendicular - φ = DS - ψ•RV_N
      Contact can not occur under the following conditions:
        [φ•φ > RS•RS] - The sphere path does not bring them within proximity
    Result: Υ = RS•RS - φ•φ, ζ = ψ + √Υ
      [ζ < RV_L] - The two sphere's contact at (ζ / RV_L) of the complete path of motion.
*/

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

/* ---- FCN_VO(tgCO_SP_Penetrate_SP) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN_VO(tgCO_SP_Penetrate_SP)(VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_OBJ_T(TgSPHERE,CPC) psSP0, VEC_OBJ_T(TgSPHERE,CPC) psSP1 )
{
    VEC_T(1)                            vMag_DS;
    VEC_OBJ_T(STg2_CO_Contact,P)        psContact;

    TgPARAM_CHECK( FCN_VO(tgGM_SP_Is_Valid)(psSP1) && FCN_VO(tgGM_SP_Is_Valid)(psSP0) );

    if (0 == psPacket->m_nuiMaxContact || nullptr == psPacket->m_psContact)
    {
        return (KTgE_FAIL);
    }
    else
    {
        VEC_T(1,C)                          vDS = FCN_V(tgMH_SUB)( psSP1->m_vOrigin, psSP0->m_vOrigin );
        VEC_T(1,C)                          vDN = FCN_V(tgMH_NORM_LEN)( &vMag_DS, vDS );
        VEC_T(1,C)                          vSR = FCN_V(tgMH_ADD)( psSP0->m_vRadius, psSP1->m_vRadius );

        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( vMag_DS, vSR ) ))
        {
            return (KTgE_NO_INTERSECT);
        };

        if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
        {
            return (KTgE_FAIL);
        };

        psContact = psPacket->m_psContact + psPacket->m_nuiContact;

        psContact->m_vT0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
        psContact->m_vDepth = FCN_V(tgMH_SUB)( vSR, vMag_DS );

        if (FCN_V(tgMH_Is_NR0)( vMag_DS ))
        {
            VEC_T(1,C)                          vK0 = FCN_V(tgMH_MUL)( VEC_K(KTgUNIT_Y), psSP1->m_vRadius );

            psContact->m_vS0 = FCN_V(tgMH_SUB)( psSP1->m_vOrigin, vK0 );
            psContact->m_vN0 = VEC_K(KTgUNIT_Y);
        }
        else
        {
            VEC_T(1,C)                          vK0 = FCN_V(tgMH_MUL)( vDN, psSP1->m_vRadius );

            psContact->m_vS0 = FCN_V(tgMH_SUB)( psSP1->m_vOrigin, vK0 );

            psContact->m_vN0 = vDN;
        };

        ++psPacket->m_nuiContact;
        return (KTgS_OK);
    };
}


/* ---- FCN_VO(tgCO_SP_Sweep_SP) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN_VO(tgCO_SP_Sweep_SP)(VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_T(1,P) pvPM, VEC_OBJ_T(TgSPHERE,CPC) psSP0, VEC_OBJ_T(TgSPHERE,CPC) psSP1, VEC_OBJ_T(TgDELTA,CPC) psDT)
{
    VEC_OBJ_T(STg2_CO_Contact,P)        psContact;

    TgERROR( FCN_VO(tgGM_SP_Is_Valid)(psSP1) && FCN_VO(tgGM_SP_Is_Valid)(psSP0) );

    if (0 == psPacket->m_nuiMaxContact || nullptr == psPacket->m_psContact || FCN_V(tgMH_Is_NR0)( *pvPM ))
    {
        return (KTgE_FAIL);
    }
    else
    {
        /* Check for pre-penetration. */

        VEC_T(1,C)                          vDS = FCN_V(tgMH_SUB)( psSP0->m_vOrigin, psSP1->m_vOrigin );
        VEC_T(1,C)                          vDS_DS = FCN_V(tgMH_LSQ)( vDS );
        VEC_T(1,C)                          vSR = FCN_V(tgMH_ADD)( psSP1->m_vRadius, psSP0->m_vRadius );
        VEC_T(1,C)                          vSR_SR = FCN_V(tgMH_MUL)( vSR, vSR );

        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vDS_DS, vSR_SR ) ))
        {
            *pvPM = FCN_V(tgMH_SET1)( TYPE_K(0) );
            psPacket->m_nuiContact = 0;

            if (psPacket->m_bReport_Penetration)
            {
                if (KTgE_MAX_CONTACTS == FCN_VO(tgCO_SP_Penetrate_SP)( psPacket, psSP0, psSP1 ))
                {
                    return (KTgE_MAX_CONTACTS);
                };
            };

            return (KTgE_PREPENETRATION);
        }
        else
        {
            VEC_T(1,C)                          vDS_UDT = FCN_V(tgMH_DOT)( vDS, psDT->m_vUDT );
            VEC_T(1,C)                          vX0 = FCN_V(tgMH_MAD)( psDT->m_vUDT, vDS_UDT, psSP1->m_vOrigin );
            VEC_T(1,C)                          vDM = FCN_V(tgMH_SUB)( psSP0->m_vOrigin, vX0 );
            VEC_T(1,C)                          vDM_DM = FCN_V(tgMH_LSQ)( vDM );
            VEC_T(1,C)                          vX1 = FCN_V(tgMH_SUB)( vSR_SR, vDM_DM );
            VEC_T(1,C)                          vX2 = FCN_V(tgMH_SQRT)( vX1 );
            VEC_T(1,C)                          vX3 = FCN_V(tgMH_SUB)( vDS_UDT, vX2 );
            VEC_T(1,C)                          vT0 = FCN_V(tgMH_DIV)( vX3, psDT->m_vMag_DT );
            VEC_T(1,C)                          vX4 = FCN_V(tgMH_MAD)( vT0, psDT->m_vDT, psSP1->m_vOrigin );
            VEC_T(1,C)                          vX5 = FCN_V(tgMH_SUB)( vX4, psSP0->m_vOrigin );
            VEC_T(1,C)                          vNormal = FCN_V(tgMH_NORM)( vX5 );
            VEC_T(1,C)                          vX6 = FCN_V(tgMH_MAD)( vNormal, psSP1->m_vRadius, psSP0->m_vOrigin );

            if ( FCN_V(tgMH_CMP_ALL_TO_BOOL)(FCN_V(tgMH_CMP_LE)(vX1, FCN_V(tgMH_SET1)(TYPE_K(0)))) )
            {
                return (KTgE_NO_INTERSECT);
            };

            if (!FCN_V(tgMH_Is_Contained_In_Interval)( vT0, FCN_V(tgMH_SET1)( TYPE_K(0) ), FCN_V(tgMH_ADD)( *pvPM, psPacket->m_vSweepTol ) ))
            {
                return (KTgE_NO_INTERSECT);
            };

            if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vT0, FCN_V(tgMH_SUB)( *pvPM, psPacket->m_vSweepTol ) ) ))
            {
                psPacket->m_nuiContact = 0;
                *pvPM = vT0;
            };

            if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
            {
                return (KTgE_FAIL);
            };

            psContact = psPacket->m_psContact + psPacket->m_nuiContact;

            psContact->m_vS0 = vX6;
            psContact->m_vN0 = vNormal;
            psContact->m_vT0 = vT0;
            psContact->m_vDepth = FCN_V(tgMH_SET1)( TYPE_K(0) );

            ++psPacket->m_nuiContact;

            return (KTgS_OK);
        };
    };
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
