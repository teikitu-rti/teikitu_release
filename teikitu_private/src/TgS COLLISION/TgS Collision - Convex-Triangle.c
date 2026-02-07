/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Convex-Triangle.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

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

/* ---- FCN_VO(tgCO_ST_Sweep_CX) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN_VO(tgCO_ST_Sweep_CX)(
    VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_T(1,PC) pvPM, VEC_OBJ_T(TgSTRI,CPC) psST0, VEC_OBJ_T(TgSTRI,CPC) apsST, TgATTRIBUTE_UNUSED VEC_OBJ_T(TgBOXAA,CPC) apsBA, 
    TgRSIZE_C nuiTri, VEC_OBJ_T(TgDELTA,CPC) psDT )
{
    VEC_OBJ_T(STg2_CO_Packet)           sTriPacket;
    VEC_OBJ_T(STg2_CO_Contact)          asContact[8];
    TgRSIZE                             uiIndex, uiContact;
    VEC_OBJ_T(STg2_CO_Contact,P)        psContact;
    TgBOOL                              bContact = false;

    sTriPacket.m_psContact = asContact;
    sTriPacket.m_vSweepTol = FCN_V(tgMH_SET1)( TYPE_K(0) );
    sTriPacket.m_vSnapTol = FCN_V(tgMH_SET1)( VAR_K(KTgEPS) );
    sTriPacket.m_nuiContact = 0;
    sTriPacket.m_nuiMaxContact = 8;

    for (uiIndex = 0; uiIndex < nuiTri; ++uiIndex)
    {
        VEC_T(1)                            vTriPM = *pvPM;

        if (FCN_VO(tgCO_ST_Sweep_ST)( &sTriPacket, &vTriPM, psST0, apsST + uiIndex, psDT ) < 0)
        {
            continue;
        };

        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vTriPM, FCN_V(tgMH_ADD)( *pvPM, psPacket->m_vSweepTol ) ) ))
        {
            continue;
        };

        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTriPM, FCN_V(tgMH_SUB)( *pvPM, psPacket->m_vSweepTol ) ) ))
        {
            psPacket->m_nuiContact = 0;
            *pvPM = vTriPM;
        };

        for (uiContact = 0; uiContact < sTriPacket.m_nuiContact; ++uiContact)
        {
            if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
            {
                return (KTgE_MAX_CONTACTS);
            };

            psContact = psPacket->m_psContact + psPacket->m_nuiContact;

            psContact->m_vS0 = asContact[uiContact].m_vS0;
            psContact->m_vN0 = FCN_V(tgMH_NEG)( asContact[uiContact].m_vN0 );
            psContact->m_vT0 = asContact[uiContact].m_vT0;
            psContact->m_vDepth = asContact[uiContact].m_vDepth;

            ++psPacket->m_nuiContact;
            bContact |= true;
        };
    };

    return (bContact ? KTgS_OK : KTgE_NO_INTERSECT);
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
