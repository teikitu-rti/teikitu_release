/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Cylinder-Sphere.c
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

/* ---- FCN_VO(tgCO_SP_Penetrate_CY) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* Input:  tgPacket: The current series of contact points for this query-series, and contact generation parameters.                                                                */
/* Input:  psSP0: Sphere primitive                                                                                                                                                 */
/* Input:  psCY0: Cylinder primitive - contact points are generated on this primitive                                                                                              */
/* Output: tgPacket: Points of penetration between the two primitives are added to it                                                                                              */
/* Return: Result Code                                                                                                                                                             */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN_VO(tgCO_SP_Penetrate_CY)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_OBJ_T(TgSPHERE,CPC) psSP0, VEC_OBJ_T(TgTUBE,CPC) psCY0 )
{
    TgPARAM_CHECK( FCN_VO(tgGM_TB_Is_Valid)(psCY0) && FCN_VO(tgGM_SP_Is_Valid)(psSP0) );

    if (0 == psPacket->m_nuiMaxContact || psPacket->m_nuiContact >= psPacket->m_nuiMaxContact || nullptr == psPacket->m_psContact)
    {
        return (KTgE_FAIL);
    };

    {
        VEC_T(1,C)                          vCY0_OG = FCN_VO(tgGM_TB_Query_Origin)( psCY0 );
        VEC_T(1,C)                          vCY0_UAX = FCN_VO(tgGM_TB_Query_Axis_Unit)( psCY0 );
        VEC_T(1,C)                          vDS = FCN_V(tgMH_SUB)( vCY0_OG, psSP0->m_vOrigin );

        /* Separating Axis - Cylindrical Principal Axis. */

        VEC_T(1,C)                          vDS_AX = FCN_V(tgMH_DOT)( vDS, vCY0_UAX );
        VEC_T(1)                            vDepth = FCN_V(tgMH_SUB)( FCN_V(tgMH_ADD)( psCY0->m_vExtent, psSP0->m_vRadius ), FCN_V(tgMH_ABS)( vDS_AX ) );
        VEC_T(1)                            vNormal;

        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vDepth, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ))
        {
            return (KTgE_NO_INTERSECT);
        };

        {
            /* Separating Axis - Cylindrical Radial Axis. */

            VEC_T(1)                            vMAG;
            VEC_T(1,C)                          vK1 = FCN_V(tgMH_SUB)( vDS, FCN_V(tgMH_MUL)( vDS_AX, vCY0_UAX ) );
            VEC_T(1,C)                          vRT = FCN_V(tgMH_NORM_LEN)( &vMAG, vK1 );
            VEC_T(1,C)                          vTest = FCN_V(tgMH_SUB)( FCN_V(tgMH_ADD)( psCY0->m_vRadius, psSP0->m_vRadius), vMAG );

            if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTest, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ))
            {
                return (KTgE_NO_INTERSECT);
            };

            if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTest, vDepth ) ))
            {
                vDepth = vTest;
                vNormal = vRT;
            }
            else
            {
                VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_LT)( vDS_AX, FCN_V(tgMH_SET1)( TYPE_K(0) ) );
                VEC_T(1,C)                          vSGN__DX_AX = FCN_V(tgMH_SEL)( FCN_V(tgMH_SET1)( TYPE_K(1) ), FCN_V(tgMH_SET1)( -TYPE_K(1) ), vCMP_0 );

                vNormal = FCN_V(tgMH_MUL)( vSGN__DX_AX, vCY0_UAX );
            };

            /* Separating Axis - Minimal Axis Connecting Cylindrical Ring and Sphere Centre. */
            /* Dev Note: The origin of the sphere is restricted to being outside of the cylinder.  This biases the contact away from rim collisions, and prevents having */
            /* to do directional analysis to determine the contact depth. */

            if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( FCN_V(tgMH_ABS)( vDS_AX ), psCY0->m_vExtent ) ))
            {
                if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vRT, psCY0->m_vRadius ) ))
                {
                    VEC_T(1,C)                          vK2 = FCN_V(tgMH_NORM)( vDS );
                    VEC_T(1,C)                          vK3 = FCN_V(tgMH_NEG)( vK2 );
                    VEC_T(1,C)                          vK4 = FCN_VO(tgGM_CY_Support_Point)( psCY0, vK3 );
                    VEC_T(1,C)                          vK5 = FCN_V(tgMH_SUB)( vK4, psSP0->m_vOrigin );
                    VEC_T(1,C)                          vRIM = FCN_V(tgMH_NORM_LEN)( &vMAG, vK5 );
                    VEC_T(1,C)                          vTest2 = FCN_V(tgMH_SUB)( psSP0->m_vRadius, vMAG );

                    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTest2, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ))
                    {
                        return (KTgE_NO_INTERSECT);
                    };

                    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTest2, vDepth ) ))
                    {
                        vDepth = vTest2;
                        vNormal = vRIM;
                    };
                };
            };
        };

        {
            VEC_OBJ_T(STg2_CO_Contact, P)        psContact;

            VEC_T(1,C)                          vK2 = FCN_V(tgMH_MUL)( vNormal, FCN_V(tgMH_SUB)( psSP0->m_vRadius, vDepth ) );

            psContact = psPacket->m_psContact + psPacket->m_nuiContact;

            psContact->m_vS0 = FCN_V(tgMH_ADD)( psSP0->m_vOrigin, vK2 );
            psContact->m_vN0 = vNormal;
            psContact->m_vT0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
            psContact->m_vDepth = vDepth;

            ++psPacket->m_nuiContact;

            return (KTgS_OK);
        };
    };
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
