/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Sphere-Point.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

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

/* ---- FCN_VO(tgCO_SP_Penetrate_PT) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN_VO(tgCO_SP_Penetrate_PT)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_OBJ_T(TgSPHERE,CPC) psSP0, VEC_T(1,C) vS0 )
{
    VEC_T(1)                            vNormal, vMag_NM, vDS, vDS_DS;
    VEC_OBJ_T(STg2_CO_Contact,P)        psContact;

    TgPARAM_CHECK( FCN_VO(tgGM_SP_Is_Valid)( psSP0 ) && FCN_V(tgMH_Is_Valid_Point)( vS0 ) );

    if (0 == psPacket->m_nuiMaxContact || nullptr == psPacket->m_psContact)
    {
        return (KTgE_FAIL);
    };

    vDS = FCN_V(tgMH_SUB)( vS0, psSP0->m_vOrigin );
    vDS_DS = FCN_V(tgMH_LSQ)( vDS );

    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vDS_DS, psSP0->m_vRadiusSq ) ))
    {
        return (KTgE_NO_INTERSECT);
    };

    if (FCN_V(tgMH_Is_NR0)( vDS_DS ))
    {
        vNormal = FCN_V(tgMH_Init_Vector_ELEM)( TYPE_K(0), TYPE_K(1), TYPE_K(0) );
        vMag_NM = FCN_V(tgMH_SET1)( TYPE_K(0) );
    }
    else
    {
        vNormal = FCN_V(tgMH_NORM_LEN)( &vMag_NM, vDS );
    };

    if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
    {
        return (KTgE_FAIL);
    };

    psContact = psPacket->m_psContact + psPacket->m_nuiContact;

    psContact->m_vS0 = vS0;
    psContact->m_vN0 = vNormal;
    psContact->m_vT0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
    psContact->m_vDepth = FCN_V(tgMH_SUB)( psSP0->m_vRadius, vMag_NM );

    ++psPacket->m_nuiContact;

    return (KTgS_OK);
}


/* ---- FCN_VO(tgCO_SP_Util__Penetrate_Closest_PT_Dist) -------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN_VO(tgCO_SP_Util__Penetrate_Closest_PT_Dist)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_OBJ_T(TgSPHERE,CPC) psSP0, VEC_T(1,C) vP1, VEC_T(1,C) vDistSq, VEC_T(1,C) vD0 )
{
    VEC_T(1)                            vX0, vNormal, vNM;
    VEC_OBJ_T(STg2_CO_Contact,P)        psContact;

    if (0 == psPacket->m_nuiMaxContact || nullptr == psPacket->m_psContact)
    {
        return (KTgE_FAIL);
    };

    if (FCN_V(tgMH_Is_NR0)( vDistSq ))
    {
        vX0 = FCN_V(tgMH_Init_Ortho)( vD0 );
        vNormal = FCN_V(tgMH_NORM)( vX0 );
        vNM = FCN_V(tgMH_SET1)( TYPE_K(0) );
    }
    else
    {
        vX0 = FCN_V(tgMH_SUB)( vP1, psSP0->m_vOrigin );
        vNormal = FCN_V(tgMH_NORM_LEN)( &vNM, vX0 );
    };

    if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
    {
        return (KTgE_FAIL);
    };

    psContact = psPacket->m_psContact + psPacket->m_nuiContact;

    psContact->m_vS0 = vP1;
    psContact->m_vN0 = vNormal;
    psContact->m_vT0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
    psContact->m_vDepth = FCN_V(tgMH_SUB)( psSP0->m_vRadius, vNM );

    ++psPacket->m_nuiContact;

    return (KTgS_OK);
}


/* ---- FCN_VO(tgCO_PT_Sweep_SP) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN_VO(tgCO_PT_Sweep_SP)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_T(1,P) pvPM, TgRSIZE_P puiStart, VEC_T(1,C) vS0, VEC_OBJ_T(TgSPHERE,CPC) psSP0,
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

    iResult = FCN_VO(tgCO_SP_Sweep_PT)( psPacket, pvPM, &uiStart, psSP0, vS0, &sNegDT );

    if (TgFAILED(iResult) && (KTgE_PREPENETRATION != iResult))
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

    return (KTgS_OK);
}


/* ---- FCN_VO(tgCO_SP_Sweep_PT) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN_VO(tgCO_SP_Sweep_PT)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_T(1,P) pvPM, TgRSIZE_P puiStart, VEC_OBJ_T(TgSPHERE,CPC) psSP0, VEC_T(1,C) vS0,
                                   VEC_OBJ_T(TgDELTA,CPC) psDT )
{
    VEC_T(1)                            vDS, vDS_DS;
    VEC_OBJ_T(STg2_CO_Contact,P)        psContact;

    if (0 == psPacket->m_nuiMaxContact || nullptr == psPacket->m_psContact || FCN_V(tgMH_Is_NR0)( *pvPM ))
    {
        return (KTgE_FAIL);
    };

    TgPARAM_CHECK( FCN_VO(tgGM_DT_Is_Valid)( psDT ) && FCN_VO(tgGM_SP_Is_Valid)( psSP0 ) && FCN_V(tgMH_Is_Valid_Point)( vS0 ) );

    vDS = FCN_V(tgMH_SUB)( psSP0->m_vOrigin, vS0 );
    vDS_DS = FCN_V(tgMH_LSQ)( vDS );

    /* Check for Pre-Penetration */
    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vDS_DS, psSP0->m_vRadiusSq ) ))
    {
        *pvPM = FCN_V(tgMH_SET1)( TYPE_K(0) );
        psPacket->m_nuiContact = 0;
        if (puiStart)
        {
            *puiStart = 0;
        };


        if (psPacket->m_bReport_Penetration)
        {
            if (KTgE_MAX_CONTACTS == FCN_VO(tgCO_SP_Penetrate_PT)( psPacket, psSP0, vS0 ))
            {
                return (KTgE_MAX_CONTACTS);
            };
        };

        return (KTgE_PREPENETRATION);
    }
    else
    {
        VEC_T(1,C)                          vDS_UDT = FCN_V(tgMH_DOT)( vDS, psDT->m_vUDT );
        VEC_T(1,C)                          vX0 = FCN_V(tgMH_MAD)( psDT->m_vUDT, vDS_UDT, vS0 );
        VEC_T(1,C)                          vDM = FCN_V(tgMH_SUB)( psSP0->m_vOrigin, vX0 );
        VEC_T(1,C)                          vDM_DM = FCN_V(tgMH_LSQ)( vDM );
        VEC_T(1,C)                          vX1 = FCN_V(tgMH_SUB)( psSP0->m_vRadiusSq, vDM_DM );
        VEC_T(1,C)                          vX2 = FCN_V(tgMH_SQRT)( vX1 );
        VEC_T(1,C)                          vX3 = FCN_V(tgMH_SUB)( vDS_UDT, vX2 );
        VEC_T(1,C)                          vT0 = FCN_V(tgMH_DIV)( vX3, psDT->m_vMag_DT );
        VEC_T(1,C)                          vX4 = FCN_V(tgMH_MAD)( vT0, psDT->m_vDT, vS0 );
        VEC_T(1,C)                          vX5 = FCN_V(tgMH_SUB)( vX4 , psSP0->m_vOrigin );
        VEC_T(1,C)                          vNormal = FCN_V(tgMH_NORM)( vX5 );

        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( vX1, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ))
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

        if (puiStart)
        {
            *puiStart = psPacket->m_nuiContact;
        };

        psContact->m_vS0 = vX4;
        psContact->m_vN0 = vNormal;
        psContact->m_vT0 = vT0;
        psContact->m_vDepth = FCN_V(tgMH_SET1)( TYPE_K(0) );

        ++psPacket->m_nuiContact;

        return (KTgS_OK);
    };
}




/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
