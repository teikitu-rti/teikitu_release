/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Convex-Plane.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "TgS COLLISION/TgS Collision - Plane-Point.inl"

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

/* ---- FCN_VO(tgCO_PN_Penetrate_CX) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN_VO(tgCO_PN_Penetrate_CX)(
    VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_OBJ_T(TgPLANE,CPC) psPN0, VEC_OBJ_T(TgSTRI,CPC) apsST, VEC_OBJ_T(TgBOXAA,CPC) apsBA, TgRSIZE_C nuiTri )
{
    TgRSIZE_C                           nuiContact = psPacket->m_nuiContact;
    VEC_OBJ_T(STg2_CO_Contact,P)        psContact;
    TgRSIZE                             uiIndex;

    TgPARAM_CHECK( nullptr != psPacket );
    TgPARAM_CHECK( nullptr != psPN0 );
    TgPARAM_CHECK( nullptr != apsST && nullptr != apsBA && 0 < nuiTri );

    for (uiIndex = 0; uiIndex < nuiTri; ++uiIndex)
    {
        if (FCN_VO(tgGM_ST_Test_Point_0)( apsST + uiIndex ))
        {
            VEC_T(1,C)                          vDist = FCN_VO(tgCO_PN_Sign_Dist_PT)( psPN0, apsST[uiIndex].m_sCT.m_sET.m_sPT.m_avPoint[0] );

            if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vDist, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ))
            {
                if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
                {
                    return (KTgE_MAX_CONTACTS);
                };

                psContact = psPacket->m_psContact + psPacket->m_nuiContact;

                psContact->m_vS0 = apsST[uiIndex].m_sCT.m_sET.m_sPT.m_avPoint[0];
                psContact->m_vN0 = psPN0->m_vNormal;
                psContact->m_vT0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
                psContact->m_vDepth = FCN_V(tgMH_NEG)( vDist );

                ++psPacket->m_nuiContact;
            };
        };

        if (FCN_VO(tgGM_ST_Test_Point_1)(apsST + uiIndex))
        {
            VEC_T(1,C)                          vDist = FCN_VO(tgCO_PN_Sign_Dist_PT)( psPN0, apsST[uiIndex].m_sCT.m_sET.m_sPT.m_avPoint[1] );

            if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vDist, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ))
            {
                if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
                {
                    return (KTgE_MAX_CONTACTS);
                };

                psContact = psPacket->m_psContact + psPacket->m_nuiContact;

                psContact->m_vS0 = apsST[uiIndex].m_sCT.m_sET.m_sPT.m_avPoint[1];
                psContact->m_vN0 = psPN0->m_vNormal;
                psContact->m_vT0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
                psContact->m_vDepth = FCN_V(tgMH_NEG)( vDist );

                ++psPacket->m_nuiContact;
            };
        };

        if (FCN_VO(tgGM_ST_Test_Point_2)(apsST + uiIndex))
        {
            VEC_T(1,C)                          vDist = FCN_VO(tgCO_PN_Sign_Dist_PT)( psPN0, apsST[uiIndex].m_sCT.m_sET.m_sPT.m_avPoint[2] );

            if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vDist, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ))
            {
                if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
                {
                    return (KTgE_MAX_CONTACTS);
                };

                psContact = psPacket->m_psContact + psPacket->m_nuiContact;

                psContact->m_vS0 = apsST[uiIndex].m_sCT.m_sET.m_sPT.m_avPoint[2];
                psContact->m_vN0 = psPN0->m_vNormal;
                psContact->m_vT0 = FCN_V(tgMH_SET1)(TYPE_K(0));
                psContact->m_vDepth = FCN_V(tgMH_NEG)(vDist);

                ++psPacket->m_nuiContact;
            };
        };
    };

    return (nuiContact != psPacket->m_nuiContact ? KTgS_OK : KTgE_NO_INTERSECT);
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
