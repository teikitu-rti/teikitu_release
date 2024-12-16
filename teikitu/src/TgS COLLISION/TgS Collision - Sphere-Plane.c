/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Sphere-Plane.c
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

/* ---- FCN_VO(tgCO_PN_Penetrate_SP) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN_VO(tgCO_PN_Penetrate_SP)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_OBJ_T(TgPLANE,CPC) psPN0, VEC_OBJ_T(TgSPHERE,CPC) psSP0 )
{
    VEC_T(1)                            vDist, vK0;
    VEC_OBJ_T(STg2_CO_Contact,P)        psContact;

    TgPARAM_CHECK( FCN_VO(tgGM_SP_Is_Valid)(psSP0) && FCN_VO(tgGM_PN_Is_Valid)(psPN0) );

    if (0 == psPacket->m_nuiMaxContact || nullptr == psPacket->m_psContact)
    {
        return (KTgE_FAIL);
    };

    vDist = FCN_VO(tgCO_PN_Sign_Dist_PT)( psPN0, psSP0->m_vOrigin );
    vK0 = FCN_V(tgMH_MUL)( psSP0->m_vRadius, psPN0->m_vNormal );

    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vDist, psSP0->m_vRadius ) ))
    {
        return (KTgE_NO_INTERSECT);
    };

    if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
    {
        return (KTgE_FAIL);
    };

    psContact = psPacket->m_psContact + psPacket->m_nuiContact;

    psContact->m_vS0 = FCN_V(tgMH_SUB)( psSP0->m_vOrigin, vK0 );
    psContact->m_vN0 = psPN0->m_vNormal;
    psContact->m_vT0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
    psContact->m_vDepth = FCN_V(tgMH_SUB)( psSP0->m_vRadius, vDist );

    ++psPacket->m_nuiContact;

    return (KTgS_OK);
}


/* ---- FCN_VO(tgCO_SP_Penetrate_PN) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN_VO(tgCO_SP_Penetrate_PN)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_OBJ_T(TgSPHERE,CPC) psSP0, VEC_OBJ_T(TgPLANE,CPC) psPN0 )
{
    VEC_T(1)                            vDist;
    VEC_OBJ_T(STg2_CO_Contact,P)        psContact;

    TgPARAM_CHECK( FCN_VO(tgGM_SP_Is_Valid)(psSP0) && FCN_VO(tgGM_PN_Is_Valid)(psPN0) );

    if (0 == psPacket->m_nuiMaxContact || nullptr == psPacket->m_psContact)
    {
        return (KTgE_FAIL);
    };

    vDist = FCN_VO(tgCO_PN_Sign_Dist_PT)( psPN0, psSP0->m_vOrigin );

    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vDist, psSP0->m_vRadius ) ))
    {
        return (KTgE_NO_INTERSECT);
    };

    if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
    {
        return (KTgE_FAIL);
    };

    psContact = psPacket->m_psContact + psPacket->m_nuiContact;

    psContact->m_vS0 = FCN_V(tgMH_SUB)( psSP0->m_vOrigin, FCN_V(tgMH_MUL)( vDist, psPN0->m_vNormal ) );
    psContact->m_vN0 = FCN_V(tgMH_NEG)( psPN0->m_vNormal );
    psContact->m_vT0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
    psContact->m_vDepth = FCN_V(tgMH_SUB)( psSP0->m_vRadius, vDist );

    ++psPacket->m_nuiContact;

    return (KTgS_OK);
}



/* ---- FCN_VO(tgCO_PN_Sweep_SP) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN_VO(tgCO_PN_Sweep_SP)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_T(1,P) pvPM, VEC_OBJ_T(TgPLANE,CPC) psPN0, VEC_OBJ_T(TgSPHERE,CPC) psSP0, VEC_OBJ_T(TgDELTA,CPC) psDT )
{
    VEC_T(1)                            vDist;
    VEC_OBJ_T(STg2_CO_Contact,P)        psContact;

    TgERROR( FCN_VO(tgGM_SP_Is_Valid)(psSP0) && FCN_VO(tgGM_PN_Is_Valid)(psPN0) );

    if (0 == psPacket->m_nuiMaxContact || nullptr == psPacket->m_psContact || FCN_V(tgMH_Is_NR0)( *pvPM ))
    {
        return (KTgE_FAIL);
    };

    vDist = FCN_VO(tgCO_PN_Sign_Dist_PT)( psPN0, psSP0->m_vOrigin );

    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( vDist, psSP0->m_vRadius ) ))
    {
        *pvPM = FCN_V(tgMH_SET1)( TYPE_K(0) );
        psPacket->m_nuiContact = 0;

        if (psPacket->m_bReport_Penetration)
        {
            if (KTgE_MAX_CONTACTS == FCN_VO(tgCO_PN_Penetrate_SP)( psPacket, psPN0, psSP0 ))
            {
                return (KTgE_MAX_CONTACTS);
            };
        };

        return (KTgE_PREPENETRATION);
    }
    else
    {
        VEC_T(1,C)                          vX0 = FCN_V(tgMH_DOT)( psDT->m_vDT, psPN0->m_vNormal );
        VEC_T(1,C)                          vDT_N = FCN_V(tgMH_NEG)( vX0 );
        VEC_T(1,C)                          vX1 = FCN_V(tgMH_SUB)( vDist, psSP0->m_vRadius );
        VEC_T(1,C)                          vT0 = FCN_V(tgMH_DIV)( vX1, vDT_N );
        VEC_T(1,C)                          vK1 = FCN_V(tgMH_MAD)( vT0, psDT->m_vDT, psSP0->m_vOrigin );
        VEC_T(1,C)                          vK2 = FCN_V(tgMH_MUL)( psSP0->m_vRadius, psPN0->m_vNormal );

        if ( !FCN_V(tgMH_Is_Contained_In_Interval)(vT0, FCN_V(tgMH_SET1)(VAR_K(KTgROOT_EPS)), FCN_V(tgMH_ADD)(*pvPM, psPacket->m_vSweepTol)) )
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

        psContact->m_vS0 = FCN_V(tgMH_SUB)( vK1, vK2 );
        psContact->m_vN0 = psPN0->m_vNormal;
        psContact->m_vT0 = vT0;
        psContact->m_vDepth = FCN_V(tgMH_SET1)( TYPE_K(0) );

        ++psPacket->m_nuiContact;

        return (KTgS_OK);
    };
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
