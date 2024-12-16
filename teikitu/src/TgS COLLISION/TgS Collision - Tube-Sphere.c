/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Tube-Sphere.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

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

/* ---- FCN_VO(tgCO_Sweep_TB_SP) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN_VO(tgCO_TB_Sweep_SP)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_T(1,P) pvPM, VEC_OBJ_T(TgTUBE,CPC) psTB0, VEC_OBJ_T(TgSPHERE,CPC) psSP0, VEC_OBJ_T(TgDELTA,CPC) psDT )
{
    VEC_OBJ_T(STg2_CO_Packet)           sPacketSG;
    VEC_OBJ_T(STg2_CO_Contact)          asContactSG[2];
    TgRESULT                            iResult;
    VEC_OBJ_T(STg2_CO_Contact,P)        psContactSG;
    VEC_OBJ_T(STg2_CO_Contact,P)        psContact;
    VEC_T(1)                            vRS, vR0, vX0, vX1, vK0;
    VEC_T(1)                            vCMP_0, vCMP_1;

    TgERROR( FCN_VO(tgGM_SP_Is_Valid)(psSP0) && FCN_VO(tgGM_TB_Is_Valid)(psTB0) );
    TgERROR(!psPacket->m_bReport_Penetration); /* Penetration not implemented for tube-sphere. */

    if (0 == psPacket->m_nuiMaxContact || psPacket->m_nuiContact >= psPacket->m_nuiMaxContact || nullptr == psPacket->m_psContact)
    {
        return (KTgE_FAIL);
    };

    vRS = FCN_V(tgMH_ADD)( psTB0->m_vRadius, psSP0->m_vRadius );
    vR0 = psSP0->m_vRadius;

    if (FCN_V(tgMH_Is_NR0)( vRS ) || FCN_V(tgMH_Is_NR0)( psTB0->m_vExtent ))
    {
        return (KTgE_FAIL);
    };

    sPacketSG.m_psContact = asContactSG;
    sPacketSG.m_vSweepTol = FCN_V(tgMH_SET1)( VAR_K(KTgEPS) );
    sPacketSG.m_nuiContact = 0;
    sPacketSG.m_nuiMaxContact = 2;

    iResult = FCN_VO(tgCO_TB11_Intersect_LR11)( &sPacketSG, vR0, psTB0, psSP0->m_vOrigin, psDT->m_vDT );

    if (TgFAILED( iResult ))
    {
        return (iResult);
    };

    TgERROR( sPacketSG.m_nuiContact >= 1 );

    psContactSG = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( asContactSG[0].m_vT0, asContactSG[(1 % sPacketSG.m_nuiContact)].m_vT0 ) ) ? asContactSG : asContactSG + 1;

    vX0 = FCN_V(tgMH_ADD)( *pvPM, psPacket->m_vSweepTol );
    vCMP_0 = FCN_V(tgMH_CMP_GT)( psContactSG->m_vT0, vX0 );

    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_0 ))
    {
        return (KTgE_NO_INTERSECT);
    };

    vX1 = FCN_V(tgMH_SUB)( *pvPM, psPacket->m_vSweepTol );
    vCMP_1 = FCN_V(tgMH_CMP_LT)( psContactSG->m_vT0, vX1 );

    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_1 ))
    {
        psPacket->m_nuiContact = 0;
        *pvPM = psContactSG->m_vT0;
    };

    psContact = psPacket->m_psContact + psPacket->m_nuiContact;

    vK0 = FCN_V(tgMH_MUL)( psSP0->m_vRadius, psContactSG->m_vN0 );

    psContact->m_vS0 = FCN_V(tgMH_SUB)( psContactSG->m_vS0, vK0 );
    psContact->m_vN0 = psContactSG->m_vN0;
    psContact->m_vT0 = psContactSG->m_vT0;
    psContact->m_vDepth = FCN_V(tgMH_SET1)( TYPE_K(0) );

    ++psPacket->m_nuiContact;

    return (KTgS_OK);
}


/* ---- FCN_VO(tgCO_Sweep_SP_TB) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN_VO(tgCO_SP_Sweep_TB)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_T(1,PC) pvPM, VEC_OBJ_T(TgSPHERE,CPC) psSP0, VEC_OBJ_T(TgTUBE,CPC) psTB0, VEC_OBJ_T(TgDELTA,CPC) psDT )
{
    VEC_OBJ_T(TgDELTA)                  sNegDT;
    TgRESULT                            iResult;
    VEC_OBJ_T(STg2_CO_Contact,P)        psContact;
    TgRSIZE                             uiIdx;
    VEC_T(1)                            vT;

    TgRSIZE_C                           nuiContact = psPacket->m_nuiContact;

    vT = *pvPM;

    sNegDT.m_vUDT = FCN_V(tgMH_NEG)( psDT->m_vUDT );
    sNegDT.m_vDT = FCN_V(tgMH_NEG)( psDT->m_vDT );
    sNegDT.m_vMag_DT = psDT->m_vMag_DT;
    sNegDT.m_vDT_DT = psDT->m_vDT_DT;
    sNegDT.m_vInv_Mag_DT = psDT->m_vInv_Mag_DT;

    iResult = FCN_VO(tgCO_TB_Sweep_SP)( psPacket, pvPM, psTB0, psSP0, &sNegDT );

    if (iResult == KTgE_PREPENETRATION)
    {
        for (uiIdx = nuiContact; uiIdx < psPacket->m_nuiContact; ++uiIdx)
        {
            psContact = psPacket->m_psContact + uiIdx;

            {
                VEC_T(1,C)                          vK0 = FCN_V(tgMH_MUL)( psContact->m_vN0, psContact->m_vDepth );

                psContact->m_vS0 = FCN_V(tgMH_ADD)( psContact->m_vS0, vK0 );
                psContact->m_vN0 = FCN_V(tgMH_NEG)( psContact->m_vN0 );
            };
        };

        return (iResult);
    }

    if (TgFAILED( iResult ))
    {
        return (iResult);
    }
    else
    {
        VEC_T(1,C)                          vK0 = FCN_V(tgMH_SUB)( vT, psPacket->m_vSweepTol );
        VEC_T(1,C)                          vK1 = FCN_V(tgMH_CMP_LT)( *pvPM, vK0 );

        uiIdx = FCN_V(tgMH_CMP_ALL_TO_BOOL)( vK1 ) ? 0 : nuiContact;

        TgERROR( uiIdx < psPacket->m_nuiContact );

        for (; uiIdx < psPacket->m_nuiContact; ++uiIdx)
        {
            psContact = psPacket->m_psContact + uiIdx;

            {
                VEC_T(1,C)                          vK2 = FCN_V(tgMH_MUL)( psDT->m_vDT, psContact->m_vT0 );

                psContact->m_vS0 = FCN_V(tgMH_ADD)( psContact->m_vS0, vK2 );
                psContact->m_vN0 = FCN_V(tgMH_NEG)( psContact->m_vN0);
            };
        };

        return (iResult);
    };
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
