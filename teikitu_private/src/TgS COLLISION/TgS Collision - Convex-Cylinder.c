/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Convex-Cylinder.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "TgS COLLISION/TgS Collision - Box AA-Box AA.inl"

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

/* ---- FCN_VO(tgCO_CY_Penetrate_CX) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* Input:  tgPacket: The current series of contact points for this query-series, and contact generation parameters.                                                                */
/* Input:  psCY0: Cylinder primitive                                                                                                                                               */
/* Input:  tgMH0: Mesh(Convex) primitive - contact points are generated on this primitive                                                                                          */
/* Output: tgPacket: Points of penetration between the two primitives are added to it                                                                                              */
/* Return: Result Code                                                                                                                                                             */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN_VO(tgCO_CY_Penetrate_CX)(
    VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_OBJ_T(TgTUBE,CPC) psCY0, VEC_OBJ_T(TgSTRI,CPC) apsST, VEC_OBJ_T(TgBOXAA,CPC) apsBA, TgRSIZE_C nuiTri )
{
    TgRSIZE_C                           nuiContact = psPacket->m_nuiContact;
    VEC_OBJ_T(STg2_CO_Packet)           sTriPacket;
    VEC_OBJ_T(STg2_CO_Contact)          asContact[8];
    TgRSIZE                             uiIndex;
    VEC_OBJ_T(TgBOXAA)                  sBA_CY0;
    VEC_OBJ_T(STg2_CO_Contact,P)        psContact;
    TgRSIZE                             uiTriIndex;

    TgPARAM_CHECK( nullptr != psPacket );
    TgPARAM_CHECK( nullptr != psCY0 );
    TgPARAM_CHECK( nullptr != apsST && nullptr != apsBA && 0 < nuiTri );

    sTriPacket.m_psContact = asContact;
    sTriPacket.m_vSweepTol = FCN_V(tgMH_SET1)( TYPE_K(0) );
    sTriPacket.m_vSnapTol = FCN_V(tgMH_SET1)( VAR_K(KTgEPS) );
    sTriPacket.m_nuiContact = 0;
    sTriPacket.m_nuiMaxContact = 8;

    FCN_VO(tgGM_CY_BA)( &sBA_CY0, psCY0 );

    for (uiIndex = 0; uiIndex < nuiTri; ++uiIndex)
    {
        if (!FCN_VO(tgCO_BA_Test_BA)( apsBA + uiIndex, &sBA_CY0 ))
        {
            continue;
        };

        if (FCN_VO(tgCO_ST_Penetrate_CY)( &sTriPacket, apsST + uiIndex, psCY0 ) < 0)
        {
            continue;
        };

        for (uiTriIndex = 0; uiTriIndex < sTriPacket.m_nuiContact; ++uiTriIndex)
        {
            if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
            {
                return (KTgE_MAX_CONTACTS);
            };

            psContact = psPacket->m_psContact + psPacket->m_nuiContact;

            psContact->m_vS0 = FCN_V(tgMH_MAD)( asContact[uiTriIndex].m_vDepth, asContact[uiTriIndex].m_vN0, asContact[uiTriIndex].m_vS0 );
            psContact->m_vN0 = FCN_V(tgMH_NEG)( asContact[uiTriIndex].m_vN0 );
            psContact->m_vT0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
            psContact->m_vDepth = asContact[uiTriIndex].m_vDepth;

            ++psPacket->m_nuiContact;
        };
    };

    return (nuiContact != psPacket->m_nuiContact ? KTgS_OK : KTgE_NO_INTERSECT);
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
