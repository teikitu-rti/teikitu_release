/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Capsule-Point.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
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

/* ---- FCN_VO(tgCO_PT_Penetrate_CP) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN_VO(tgCO_PT_Penetrate_CP)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_T(1,C) vS0, VEC_OBJ_T(TgTUBE,CPC) psCP0 )
{
    TgPARAM_CHECK( FCN_VO(tgGM_TB_Is_Valid)( psCP0 ) && FCN_V(tgMH_Is_Valid_Point)( vS0 ) );

    if (0 == psPacket->m_nuiMaxContact || nullptr == psPacket->m_psContact)
    {
        return (KTgE_FAIL);
    }
    else
    {
        VEC_UN_T(1)                         uUAX;
        VEC_T(1)                            vCP0, vNormal, vMag_NM;
        VEC_OBJ_T(STg2_CO_Contact,P)        psContact;
        VEC_T(1,C)                          vDistSq = FCN_VO(tgCO_SG_ClosestSq_PT)( &vCP0, &psCP0->m_sAX, vS0 );

        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vDistSq, psCP0->m_vRadiusSq ) ))
        {
            return (KTgE_NO_INTERSECT);
        };

        if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
        {
            return (KTgE_FAIL);
        };

        if (FCN_V(tgMH_Is_NR0)( vDistSq ))
        {
            VEC_UN_1_MEMBER(uUAX) = FCN_V(tgMH_Query_Axis_1,3)( &psCP0->m_mReference_Frame );
            if (FCN_V(tgMH_Is_NR0)( FCN_V(tgMH_SPZ)( VEC_UN_1_MEMBER(uUAX) ) ))
            {
                vNormal = FCN_V(tgMH_Init_Vector_ELEM)(-VEC_S_UN_1_MEMBER(uUAX).y, VEC_S_UN_1_MEMBER(uUAX).x, TYPE_K(0));
            }
            else
            {
                vNormal = FCN_V(tgMH_Init_Vector_ELEM)(TYPE_K(0), VEC_S_UN_1_MEMBER(uUAX).z, -VEC_S_UN_1_MEMBER(uUAX).y);
            };

            vNormal = FCN_V(tgMH_NORM)( vNormal );
            vMag_NM = FCN_V(tgMH_SET1)( TYPE_K(0) );
        }
        else
        {
            vNormal = FCN_V(tgMH_NORM_LEN)( &vMag_NM, FCN_V(tgMH_SUB)( vCP0, vS0 ) );
        };

        psContact = psPacket->m_psContact + psPacket->m_nuiContact;

        psContact->m_vS0 = FCN_V(tgMH_SUB)( vCP0, FCN_V(tgMH_MUL)( psCP0->m_vRadius, vNormal ) );
        psContact->m_vN0 = vNormal;
        psContact->m_vT0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
        psContact->m_vDepth = FCN_V(tgMH_SUB)( psCP0->m_vRadius, vMag_NM );

        ++psPacket->m_nuiContact;

        return (KTgS_OK);
    };
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
