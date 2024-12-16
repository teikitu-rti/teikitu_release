/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Sphere-Linear.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

/**    Sphere Definition: |S(v) - C0| < R0
       Line Definition: L1(α) = P1 + α•D1 | α ε [ 0, 1]

   Derivation: Let C0 be the centre of sphere S0 with radius R0
               Let L1 = P1 + α•D1 | α ε [ 0, 1]
               Let Q1 = P1 + γ•D1 by the closest point of contact
               Let V = C0 - Q1, the vector connecting the closest points of contact ( the minimal distance vector )

   Minimal distance vector, by definition must be perpendicular to the line.
   Therefore, D1•v=0, DS=C0-P1, v=DS-γ•D1

        0 = D1•(DS-γ•D1)
        0 = DS•D1-γ•D1•D1
        γ = DS•D1 / D1•D1

   However, we know that γ ε [ 0, 1], generating three cases:

   [1] γ ε (-∞, 0) || γ = 0
      Distance: The distance between P1 and C0
         = (C0-P1)•(C0-P1)
         = DS•DS

   [2] γ ε [ 0, 1] || γ = (DS•D1) / (D1•D1)
      Distance: The distance value would be || v ||.
         = || v || = v•v = (DS-γ•D1)•(DS-γ•D1)
         = DS•DS + γ•γ•D1•D1 - 2•γ•DS•D1
         = DS•DS + γ•(γ•D1•D1 - 2•DS•D1)
         = DS•DS + γ•((DS•D1 / D1•D1)•D1•D1 - 2•DS•D1)
         = DS•DS + γ•(DS•D1 - 2•DS•D1)
         = DS•DS - γ•(DS•D1)

   [3] γ ε ( 1, ∞) || γ = 1
      Distance: The distance between P1+D1 and C0
         = (C0-P1-D1)•(C0-P1-D1)
         = (DS-D1)•(DS-D1)
         = DS•DS - 2•DS•D1 + D1•D1

      Form a right-sided triangle.
        (a) The hypotenuse is the sphere radius.
        (b) The known edge is the segment from the centre of the sphere to the closest point on the line.
        (c) The length of the remaining side (along L1) is the distance from the point of closest proximity and the
            points of contact between the sphere and the line.

                                .(C0)                                                      .(C0)
                               /|\                                                        /|\
                              / | \                                                      / | \
                             /  |  \                                                    /  |  \
                            /   |   \                                                  /   |   \
                           /    |    \                                                /    |    \
                          /(R0) |     \(R0)                                 (R0)     /     |     \      (R0)
                                |                                       .----.------/------.------\------.----> (D1)
                                |                                      (P1) (Q2)   /      (Q1)     \    (Q3)
             .------------.-----.--------------> (D1)                             /        |        \
            (P1)         (Q2)  (Q1)                                              /(R0)     |         \(R0)

     Contact can not occur under the following conditions:
      Given that the point on the line closest to the sphere centre is at γ = DS•D1 / D1•D1
      The squared distance of Q1-C0 is φ = DS•DS - γ•γ•D1•D1 = DS•DS - γ•(DS•D1)
      Thus, if DS•DS - γ•(DS•D1) > R0•R0, intersection can not occur.
     Otherwise: Intersection has definitely occurred.
       By definition (sphere) it is known that
           R0•R0 = ||C0 - P1 - β•D1||, for β ε (-∞, ∞)
                 = ||DS - β•D1||
               0 = β•β•D1•D1 - β•2•DS•D1 + DS•DS - R0•R0
           Solving using the quadratic formula
               β = (2•(DS•D1) ± √(4•(DS•D1)•(DS•D1) - 4•(D1•D1)(DS•DS - R0•R0))) / (2•(D1•D1))
               β = ((DS•D1) ± √((DS•D1)•(DS•D1) - (D1•D1)(DS•DS - R0•R0))) / (D1•D1)
           If the discriminant ((DS•D1)•(DS•D1) - (D1•D1)(DS•DS - R0•R0)) is zero, there is only one point of intersection
*/

#include "TgS COLLISION/TgS Collision - Line.inl"
#include "TgS COLLISION/TgS Collision - Ray.inl"
#include "TgS COLLISION/TgS Collision - Segment.inl"

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

    #if TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE
        #define ENABLE_RELOAD_GUARD
        #define TEMPLATE__TYPE_SIZE 64
        #include __FILE__
        #undef TEMPLATE__TYPE_SIZE
        #undef ENABLE_RELOAD_GUARD
    #endif

    #define TEMPLATE__TYPE_SIZE 32
#endif

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"


/* == Collision ================================================================================================================================================================== */

/* ---- FCNI_VO(tgCO_SP_Intersect_PM) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCNI_VO(tgCO_SP_Intersect_PM)( VEC_T(1,PC) pvLN0, VEC_T(1,PC) pvLN1, VEC_T(1,PC) pvN0, VEC_T(1,PC) pvN1, VEC_OBJ_T(TgSPHERE,CPC) psSP0, VEC_T(1,C) vS0, VEC_T(1,C) vD0 )
{
    VEC_T(1,C)                          vDS = FCN_V(tgMH_SUB)( psSP0->m_vOrigin, vS0 );
    VEC_T(1,C)                          vD0_D0 = FCN_V(tgMH_LSQ)( vD0 );
    VEC_T(1,C)                          vDS_DS = FCN_V(tgMH_LSQ)( vDS );

    TgERROR( FCN_VO(tgGM_SP_Is_Valid)( psSP0 ) && FCN_V(tgMH_Is_Valid_Point)( vS0 ) && FCN_V(tgMH_Is_Valid_Vector)( vD0 ) );

    /* Check to see if the line is degenerate (a point) */
    if (FCN_V(tgMH_Is_NR0)( vD0_D0 ))
    {
        VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_GT)( vDS_DS, FCN_V(tgMH_SET1)( VAR_K(KTgROOT_EPS) ) );

        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_0 ))
        {
            VEC_T(1,C)                          vVal = FCN_V(tgMH_DIV)( psSP0->m_vRadiusSq, vDS_DS );

            if (FCN_V(tgMH_Is_NR1)( vVal ))
            {
                VEC_T(1,C)                          vK1 = FCN_V(tgMH_SUB)( vS0, psSP0->m_vOrigin );
                VEC_T(1,C)                          vK0 = FCN_V(tgMH_NORM)( vK1 );

                *pvN0  = *pvN1  = vK0;
                *pvLN0 = *pvLN1 = FCN_V(tgMH_SET1)( TYPE_K(0) );

                return (KTgS_OK);
            };
        };
        
        return (KTgE_NO_INTERSECT);
    }
    else
    {
        /* β = ((DS•D0) ± √((DS•D0)•(DS•D0) - (D0•D0)(DS•DS - R0•R0))) / (D0•D0)  */

        VEC_T(1,C)                          vDS_D0 = FCN_V(tgMH_DOT)( vDS, vD0 );
        VEC_T(1,C)                          vX1 = FCN_V(tgMH_SUB)( psSP0->m_vRadiusSq, vDS_DS );
        VEC_T(1,C)                          vX2 = FCN_V(tgMH_MUL)( vD0_D0, vX1 );
        VEC_T(1,C)                          vDSC = FCN_V(tgMH_MAD)( vDS_D0, vDS_D0, vX2 );

        VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_LT)( vDSC, FCN_V(tgMH_SET1)( -VAR_K(KTgROOT_EPS) ) );
        VEC_T(1,C)                          vCMP_1 = FCN_V(tgMH_CMP_GT)( vDSC, FCN_V(tgMH_SET1)(  VAR_K(KTgROOT_EPS) ) );

        VEC_T(1,C)                          vK0 = FCN_V(tgMH_SUB)( vS0, psSP0->m_vOrigin );

        /* Imaginary roots - there is no intersection between the linear object and the sphere */
        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_0 ))
        {
            return (KTgE_NO_INTERSECT);
        };

        /* Check for a single point of intersection (a tangent point) */
        if (!FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_1 ))
        {
            /* Point of Intersection */
            VEC_T(1,C)                          vX3 = FCN_V(tgMH_DIV)( vDS_D0, vD0_D0 );
            VEC_T(1,C)                          vK1 = FCN_V(tgMH_MAD)( vX3, vD0, vK0 );
            TgBOOL_C                            bGE_1_CAP = TEMPLATE__PRIM_0_CAP_1 && FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GE)( vX3, FCN_V(tgMH_SET1)( TYPE_K(1) ) ) );
            TgBOOL_C                            bLE_0_CAP = TEMPLATE__PRIM_0_CAP_0 && FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( vX3, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) );

            if ((!bGE_1_CAP) && (!bLE_0_CAP))
            {
                *pvN0  = *pvN1  = FCN_V(tgMH_NORM)( vK1 );
                *pvLN0 = *pvLN1 = vX3;
                return (KTgS_OK);
            };

            return (KTgE_NO_INTERSECT);
        }
        else
        {
            /* Potentially two points of intersection */

            VEC_T(1,C)                          vX3 = FCN_V(tgMH_SQRT)( vDSC );

            /* First Point of Intersection */
            VEC_T(1,C)                          vX4 = FCN_V(tgMH_SUB)( vDS_D0, vX3 );
            VEC_T(1,C)                          vX6 = FCN_V(tgMH_DIV)( vX4, vD0_D0 );
            TgBOOL_C                            bX6_GE_1_CAP = TEMPLATE__PRIM_0_CAP_1 && FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GE)( vX6, FCN_V(tgMH_SET1)( TYPE_K(1) ) ) );
            TgBOOL_C                            bX6_LE_0_CAP = TEMPLATE__PRIM_0_CAP_0 && FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( vX6, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) );

            /* Second Point of Intersection */
            VEC_T(1,C)                          vX5 = FCN_V(tgMH_ADD)( vDS_D0, vX3 );
            VEC_T(1,C)                          vX7 = FCN_V(tgMH_DIV)( vX5, vD0_D0 );
            TgBOOL_C                            bX7_GE_1_CAP = TEMPLATE__PRIM_0_CAP_1 && FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GE)( vX7, FCN_V(tgMH_SET1)( TYPE_K(1) ) ) );
            TgBOOL_C                            bX7_LE_0_CAP = TEMPLATE__PRIM_0_CAP_0 && FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( vX7, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) );

            if ((!bX6_GE_1_CAP) && (!bX6_LE_0_CAP))
            {
                VEC_T(1,C)                          vK1 = FCN_V(tgMH_MAD)( vX6, vD0, vK0 );

                if ((!bX7_GE_1_CAP) && (!bX7_LE_0_CAP))
                {
                    VEC_T(1,C)                          vK2 = FCN_V(tgMH_MAD)( vX7, vD0, vK0 );

                    *pvN0 = FCN_V(tgMH_NORM)( vK1 );
                    *pvLN0 = vX6;
                    *pvN1 = FCN_V(tgMH_NORM)( vK2 );
                    *pvLN1 = vX7;
                    return (KTgS_OK);
                }
                else
                {
                    *pvN0 = FCN_V(tgMH_NORM)( vK1 );
                    *pvLN0 = vX6;
                    *pvN1 = *pvN0;
                    *pvLN1 = vX6;
                    return (KTgS_OK);
                };
            };

            if ((!bX7_GE_1_CAP) && (!bX7_LE_0_CAP))
            {
                VEC_T(1,C)                          vK2 = FCN_V(tgMH_MAD)( vX7, vD0, vK0 );

                *pvN0  = *pvN1  = vK2;
                *pvLN0 = *pvLN1 = vX7;
                return (KTgS_OK);
            };

            return (KTgE_NO_INTERSECT);
        };
    };
}


/* ---- FCNI_VO(tgCO_SP_Intersect) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCNI_VO(tgCO_SP_Intersect)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_OBJ_T(TgSPHERE,CPC) psSP0, VEC_T(1,C) vS0, VEC_T(1,C) vD0 )
{
    VEC_T(1)                            vLN0, vLN1, vN0, vN1;
    VEC_OBJ_T(STg2_CO_Contact,P)        psContact;
    TgRESULT                            iResult;

    /* Check to make sure that a valid contact, and contact packet exist. */

    if (0 == psPacket->m_nuiMaxContact || nullptr == psPacket->m_psContact)
    {
        return (KTgE_FAIL);
    };

    iResult = FCNI_VO(tgCO_SP_Intersect_PM)( &vLN0, &vLN1, &vN0, &vN1, psSP0, vS0, vD0 );

    if (TgFAILED(iResult))
    {
        return (iResult);
    };

    if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
    {
        return (KTgE_MAX_CONTACTS);
    };

    psContact = psPacket->m_psContact + psPacket->m_nuiContact;

    psContact->m_vS0 = FCN_V(tgMH_MAD)( vLN0, vD0, vS0 );
    psContact->m_vN0 = vN0;
    psContact->m_vT0 = vLN0;
    psContact->m_vDepth = FCN_V(tgMH_SET1)( TYPE_K(0) );

    ++psPacket->m_nuiContact;

    /* Check that the parametric term is within the acceptable range */
    if (!FCN_V(tgMH_Is_PRX_CMP_EQ)( vLN0, vLN1 ))
    {
        if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
        {
            return (KTgE_FAIL);
        };

        psContact = psPacket->m_psContact + psPacket->m_nuiContact;

        psContact->m_vS0 = FCN_V(tgMH_MAD)( vLN1, vD0, vS0 );
        psContact->m_vN0 = vN1;
        psContact->m_vT0 = vLN1;
        psContact->m_vDepth = FCN_V(tgMH_SET1)( TYPE_K(0) );

        ++psPacket->m_nuiContact;
    };

    return (KTgS_OK);
}


/* ---- FCNI_VO(tgCO_SP_Sweep) --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCNI_VO(tgCO_SP_Sweep)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_T(1,P) pvPM, TgRSIZE_P puiStart, VEC_OBJ_T(TgSPHERE,CPC) psSP0, VEC_T(1,C) vS0, VEC_T(1,C) vD0,
                                 VEC_OBJ_T(TgDELTA,CPC) psDT )
{
    VEC_OBJ_T(TgDELTA)                  sNegDT;
    TgRSIZE                             uiStart;
    TgRESULT                            iResult;

    if (0 == psPacket->m_nuiMaxContact || nullptr == psPacket->m_psContact || FCN_V(tgMH_Is_NR0)( *pvPM ))
    {
        return (KTgE_FAIL);
    };

    sNegDT.m_vUDT = FCN_V(tgMH_NEG)( psDT->m_vUDT );
    sNegDT.m_vDT = FCN_V(tgMH_NEG)( psDT->m_vDT );
    sNegDT.m_vMag_DT = psDT->m_vMag_DT;
    sNegDT.m_vDT_DT = psDT->m_vDT_DT;
    sNegDT.m_vInv_Mag_DT = psDT->m_vInv_Mag_DT;

    iResult = FCNI_VO(tgCO,Sweep_SP)( psPacket, pvPM, &uiStart, vS0, vD0, psSP0, &sNegDT );

    if (TgFAILED(iResult))
    {
        return (iResult);
    };

    if (puiStart)
    {
        *puiStart = uiStart;
    };

    /* Inverting the normals and points of contact for the swap in primitives of the original call. Take into account contact position may be a point of penetration. */
    for (TgRSIZE uiIndex = uiStart; uiIndex < psPacket->m_nuiContact; ++uiIndex)
    {
        VEC_OBJ_T(STg2_CO_Contact,P)        psContact;

        psContact = psPacket->m_psContact + psPacket->m_nuiContact;

        psContact->m_vS0 = FCN_V(tgMH_MAD)( psContact->m_vN0, psContact->m_vDepth, psContact->m_vS0 );
        psContact->m_vN0 = FCN_V(tgMH_NEG)( psContact->m_vN0 );

        ++psPacket->m_nuiContact;
    };

    return (iResult);
}


/* ---- FCNI_VO(tgCO,Sweep_SP) --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCNI_VO(tgCO,Sweep_SP)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_T(1,PC) pvPM, TgRSIZE_P puiStart, VEC_T(1,C) vS0, VEC_T(1,C) vD0, VEC_OBJ_T(TgSPHERE,CPC) psSP0,
                                 VEC_OBJ_T(TgDELTA,CPC) psDT )
{
    VEC_T(1)                            vDistSq, vCMP_0, vLN1, vCMP_1, vFullExtent;
    VEC_T(3)                            mReference_Frame;
    TgRESULT                            iResult;
    VEC_OBJ_T(STg2_CO_Contact,P)        psContact;

    VEC_OBJ_T(TgTUBE)                   sTB0;
    VEC_OBJ_T(STg2_CO_Packet)           sTMP_Packet;
    VEC_OBJ_T(STg2_CO_Contact)          asTMP_Contact[2];

    TgPARAM_CHECK( FCN_VO(tgGM_DT_Is_Valid)( psDT ) && FCN_VO(tgGM_SP_Is_Valid)( psSP0 ) );
    TgPARAM_CHECK( FCN_V(tgMH_Is_Valid_Point)( vS0 ) && FCN_V(tgMH_Is_Valid_Vector)( vD0 ) );

    if (0 == psPacket->m_nuiMaxContact || nullptr == psPacket->m_psContact || FCN_V(tgMH_Is_NR0)( *pvPM ))
    {
        return (KTgE_FAIL);
    };

    vDistSq = FCNI_VO(tgCO,ClosestSq_PT)( &vLN1, vS0, vD0, psSP0->m_vOrigin );
    vCMP_0 = FCN_V(tgMH_CMP_LE)( vDistSq, psSP0->m_vRadiusSq );

    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_0 ))
    {
        *pvPM = FCN_V(tgMH_SET1)( TYPE_K(0) );
        psPacket->m_nuiContact = 0;

        if (psPacket->m_bReport_Penetration)
        {
            if (KTgE_MAX_CONTACTS == FCN_VO(tgCO_SP_Util__Penetrate_Closest_PT_Dist)( psPacket, psSP0, vLN1, vDistSq, vD0 ))
            {
                return (KTgE_MAX_CONTACTS);
            };
        };

        return (KTgE_PREPENETRATION);
    }
    else
    {
        /* Create a tube that represents the linear object padded by the sphere's radius */
        VEC_T(1)                            vT0, vN0, vK0, vK1;
        VEC_T(1,C)                          vZero = FCN_V(tgMH_SET1)( TYPE_K(0) );
        VEC_T(1,C)                          vUD0 = FCN_V(tgMH_NORM_LEN)( &vFullExtent, vD0 );
        VEC_T(1,C)                          vHalf_Extent = FCN_V(tgMH_MUL)( FCN_V(tgMH_SET1)( TYPE_K(0,5) ), vFullExtent );

        FCN_V(tgMH_Init_Reference_Frame_From_Vector_And_Position,3)( &mReference_Frame, vUD0, vS0 );

        FCN_VO(tgGM_TB_Init)( &sTB0, &mReference_Frame, vHalf_Extent, psSP0->m_vRadius );

        /* Test to see if the line made by the sphere origin and the sweep vector intersect the tube */
    
        sTMP_Packet.m_psContact = asTMP_Contact;
        sTMP_Packet.m_nuiContact = 0;
        sTMP_Packet.m_nuiMaxContact = 2;

        iResult = TgMACRO_CONCAT5( tgCO_TB, TEMPLATE__PRIM_0_CAP_0, TEMPLATE__PRIM_0_CAP_1, _Intersect_LR11_, GENERATE__VEC_DESC )(
                                   &sTMP_Packet, vZero, &sTB0, psSP0->m_vOrigin, psDT->m_vDT );

        if (TgFAILED(iResult))
        {
            return (iResult);
        };

        /* We have at least one contact point (potentially two) */
        TgERROR(0 != sTMP_Packet.m_nuiContact);
        if (2 == sTMP_Packet.m_nuiContact)
        {
            vCMP_1 = FCN_V(tgMH_CMP_GT)( asTMP_Contact[0].m_vT0, asTMP_Contact[1].m_vT0 );
        }
        else
        {
            vCMP_1 = FCN_V(tgMH_SET1)( TYPE_K(0) );
        };

        vT0 = FCN_V(tgMH_SEL)( asTMP_Contact[0].m_vT0, asTMP_Contact[1].m_vT0, vCMP_1 );

        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vT0, FCN_V(tgMH_ADD)( *pvPM, psPacket->m_vSweepTol ) ) ))
        {
            return (KTgE_NO_INTERSECT);
        };

        vN0 = FCN_V(tgMH_SEL)( asTMP_Contact[0].m_vN0, asTMP_Contact[1].m_vN0, vCMP_1 );
        vK0 = FCN_V(tgMH_MUL)( psSP0->m_vRadius, vN0 );

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

        if (puiStart)
        {
            *puiStart = psPacket->m_nuiContact;
        };

        vK1 = FCN_V(tgMH_SEL)( asTMP_Contact[0].m_vS0, asTMP_Contact[1].m_vS0, vCMP_1 );

        psContact->m_vS0 = FCN_V(tgMH_SUB)( vK1, vK0 );
        psContact->m_vN0 = vN0;
        psContact->m_vT0 = vT0;
        psContact->m_vDepth = FCN_V(tgMH_SET1)( TYPE_K(0) );

        ++psPacket->m_nuiContact;

        return (iResult);
    };
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/*# !defined (ENABLE_RELOAD_GUARD_LINEAR) */
#endif
