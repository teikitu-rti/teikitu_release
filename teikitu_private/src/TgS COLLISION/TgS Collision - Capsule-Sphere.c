/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Capsule-Sphere.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
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

/* ---- FCN_VO(tgCO_CP_Penetrate_SP) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN_VO(tgCO_CP_Penetrate_SP)(VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_OBJ_T(TgTUBE,CPC) psCP0, VEC_OBJ_T(TgSPHERE,CPC) psSP0 )
{
    TgPARAM_CHECK( FCN_VO(tgGM_TB_Is_Valid)( psCP0 ) && FCN_VO(tgGM_SP_Is_Valid)( psSP0 ) );

    if (0 == psPacket->m_nuiMaxContact || nullptr == psPacket->m_psContact)
    {
        return (KTgE_FAIL);
    }
    else
    {
        VEC_T(1)                            vCP0, vNormal, vMag_NM;
        VEC_OBJ_T(STg2_CO_Contact,P)        psContact;

        VEC_T(1,C)                          vRS = FCN_V(tgMH_ADD)( psCP0->m_vRadius, psSP0->m_vRadius );
        VEC_T(1,C)                          vRS_RS = FCN_V(tgMH_MUL)( vRS, vRS );
        VEC_T(1,C)                          vDistSq = FCN_VO(tgCO_SG_ClosestSq_PT)( &vCP0, &psCP0->m_sAX, psSP0->m_vOrigin );

        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vDistSq, vRS_RS ) ))
        {
            return (KTgE_NO_INTERSECT);
        };

        if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
        {
            return (KTgE_FAIL);
        };

        if (FCN_V(tgMH_Is_NR0)( vDistSq ))
        {
            vNormal = FCN_VO(tgGM_TB_Query_Basis_Unit_0)( psCP0 );
            vMag_NM = FCN_V(tgMH_SET1)( TYPE_K(0) );
        }
        else
        {
            vNormal = FCN_V(tgMH_NORM_LEN)( &vMag_NM, FCN_V(tgMH_SUB)( vCP0, psSP0->m_vOrigin ) );
        };

        psContact = psPacket->m_psContact + psPacket->m_nuiContact;

        psContact->m_vS0 = FCN_V(tgMH_MAD)( vNormal, psCP0->m_vRadius, psSP0->m_vOrigin );
        psContact->m_vN0 = FCN_V(tgMH_NEG)( vNormal );
        psContact->m_vT0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
        psContact->m_vDepth = FCN_V(tgMH_SUB)( vRS, vMag_NM );

        ++psPacket->m_nuiContact;

        return (KTgS_OK);
    };
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
