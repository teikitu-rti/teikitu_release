/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Box AA-Plane.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "TgS COLLISION/TgS Collision - Plane-Point.inl"

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

/* ---- FCN_VO(tgCO_PN_Penetrate_BA) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* Input:  tgPacket: The current series of contact points for this query-series, and contact generation parameters.                                                                */
/* Input:  psPN0: Plane Triangle primitive                                                                                                                                         */
/* Input:  tgBA0: Box, Axis-Aligned primitive - contact points are generated on this primitive                                                                                     */
/* Output: tgPacket: Points of penetration between the two primitives are added to it                                                                                              */
/* Return: Result Code                                                                                                                                                             */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN_VO(tgCO_PN_Penetrate_BA)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_OBJ_T(TgPLANE,CPC) psPN0, VEC_OBJ_T(TgBOXAA,CPC) psBA0 )
{
    VEC_T(1)                            vBA0_Min, vBA0_Max, vCMP_0, vBA0, vDist;
    VEC_OBJ_T(STg2_CO_Contact,P)        psContact;

    TgPARAM_CHECK( FCN_VO(tgGM_PN_Is_Valid)(psPN0) && FCN_VO(tgGM_BA_Is_Valid)(psBA0) );

    if (0 == psPacket->m_nuiMaxContact || nullptr == psPacket->m_psContact)
    {
        return (KTgE_FAIL);
    };

    vBA0_Min = FCN_VO(tgGM_BA_Query_Min)( psBA0 );
    vBA0_Max = FCN_VO(tgGM_BA_Query_Max)( psBA0 );
    vCMP_0 = FCN_V(tgMH_CMP_GE)( psPN0->m_vNormal, FCN_V(tgMH_SET1)( TYPE_K(0) ) );
    vBA0 = FCN_V(tgMH_SEL)( vBA0_Min, vBA0_Max, vCMP_0 );

    vDist = FCN_VO(tgCO_PN_Sign_Dist_PT)( psPN0, vBA0 );

    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GE)( vDist, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ))
    {
        return (KTgE_NO_INTERSECT);
    };

    if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
    {
        return (KTgE_FAIL);
    };

    psContact = psPacket->m_psContact + psPacket->m_nuiContact;

    psContact->m_vS0 = vBA0;
    psContact->m_vN0 = psPN0->m_vNormal;
    psContact->m_vT0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
    psContact->m_vDepth = FCN_V(tgMH_NEG)( vDist );

    ++psPacket->m_nuiContact;

    return (KTgS_OK);
}


/* ---- FCN_VO(tgCO_PN_Sweep_BA) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* Input:  tgPacket: The current series of contact points for this query-series, and contact generation parameters.                                                                */
/* Input:  fPM: Current normalized time of first contact.                                                                                                                          */
/* Input:  bPenetrate: If the swept primitives are in penetration, if true the function will return points of penetration.                                                         */
/* Input:  psPN0: Plane primitive                                                                                                                                                  */
/* Input:  tgBA0: Box, Axis-Aligned Primitive                                                                                                                                      */
/* Input:  psDT: A structure holding the swept primitive displacement for the entire duration of the test period                                                                   */
/* Output: tgPacket: Contact points are added or replace the current set depending on the time comparison and given parameters                                                     */
/* Output: fPM: New normalized time of first contact                                                                                                                               */
/* Return: Result Code                                                                                                                                                             */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN_VO(tgCO_PN_Sweep_BA)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_T(1,P) pvPM,
                                   VEC_OBJ_T(TgPLANE,CPC) psPN0, VEC_OBJ_T(TgBOXAA,CPC) psBA0, VEC_OBJ_T(TgDELTA,CPC) psDT )
{
    VEC_T(1)                            vDT_N0, vBA0_Min, vBA0_Max, vX0, vBA0, vDist, vT0, vPM_PTol, vPM_NTol;
    VEC_OBJ_T(STg2_CO_Contact,P)        psContact;

    TgPARAM_CHECK( FCN_VO(tgGM_PN_Is_Valid)(psPN0) && FCN_VO(tgGM_BA_Is_Valid)(psBA0) );

    if (0 == psPacket->m_nuiMaxContact || nullptr == psPacket->m_psContact || FCN_V(tgMH_Is_NR0)( *pvPM ))
    {
        return (KTgE_FAIL);
    };

    vDT_N0 = FCN_V(tgMH_DOT)( psDT->m_vDT, psPN0->m_vNormal );
    vBA0_Min = FCN_VO(tgGM_BA_Query_Min)( psBA0 );
    vBA0_Max = FCN_VO(tgGM_BA_Query_Min)( psBA0 );
    vX0 = FCN_V(tgMH_CMP_GE)( psPN0->m_vNormal, FCN_V(tgMH_SET1)( TYPE_K(0) ) );
    vBA0 = FCN_V(tgMH_SEL)( vBA0_Min, vBA0_Max, vX0 );

    vDist = FCN_VO(tgCO_PN_Sign_Dist_PT)( psPN0, vBA0 );

    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vDist, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ))
    {
        *pvPM = FCN_V(tgMH_SET1)( TYPE_K(0) );
        psPacket->m_nuiContact = 0;

        if (psPacket->m_bReport_Penetration)
        {
            if (KTgE_MAX_CONTACTS == FCN_VO(tgCO_PN_Penetrate_BA)(psPacket, psPN0, psBA0))
            {
                return (KTgE_MAX_CONTACTS);
            };
        };

        return (KTgE_PREPENETRATION);
    };

    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GE)( vDist, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ))
    {
        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GE)( FCN_V(tgMH_ADD)( vDist, vDT_N0 ), FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ))
        {
            return (KTgE_NO_INTERSECT);
        };
    };
    
    vT0 = FCN_V(tgMH_DIV)( vDist, FCN_V(tgMH_NEG)( vDT_N0 ) );
    vPM_PTol = FCN_V(tgMH_ADD)( *pvPM, psPacket->m_vSweepTol );
    vPM_NTol = FCN_V(tgMH_SUB)( *pvPM, psPacket->m_vSweepTol );

    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vT0, vPM_PTol ) ))
    {
        return (KTgE_NO_INTERSECT);
    };

    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vT0, vPM_NTol ) ))
    {
        psPacket->m_nuiContact = 0;
        *pvPM = vT0;
    };

    psContact = psPacket->m_psContact + psPacket->m_nuiContact;

    psContact->m_vS0 = vBA0;
    psContact->m_vN0 = psPN0->m_vNormal;
    psContact->m_vT0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
    psContact->m_vDepth = FCN_V(tgMH_SET1)( TYPE_K(0) );

    ++psPacket->m_nuiContact;

    return (KTgS_OK);
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
