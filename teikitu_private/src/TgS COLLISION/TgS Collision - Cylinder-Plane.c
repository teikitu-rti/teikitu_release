/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Cylinder-Plane.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
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

/* ---- FCN_VO(tgCO_CY_Dist_PN) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
VEC_T(1) FCN_VO(tgCO_CY_Dist_PN)( VEC_OBJ_T(TgTUBE,CPC) psCY0, VEC_OBJ_T(TgPLANE,CPC) psPN0 )
{
    /* Calculate out the projection of the cylinder onto the plane's normal */

    VEC_T(1,C)                          vCY0_OG = FCN_VO(tgGM_TB_Query_Origin)( psCY0 );
    VEC_T(1,C)                          vDist = FCN_VO(tgCO_PN_Sign_Dist_PT)( psPN0, vCY0_OG );

    TgERROR( FCN_VO(tgGM_TB_Is_Valid)(psCY0) && FCN_VO(tgGM_PN_Is_Valid)(psPN0) );

    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vDist, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ))
    {
        return (FCN_V(tgMH_SET1)( -VAR_K(KTgMAX) ));
    }
    else
    {
        VEC_T(1,C)                          vCY0_UAX = FCN_VO(tgGM_TB_Query_Axis_Unit)( psCY0 );
        VEC_T(1,C)                          vUAX_N = FCN_V(tgMH_DOT)( psPN0->m_vNormal, vCY0_UAX );
        VEC_T(1,C)                          vE2 = FCN_V(tgMH_MUL)( psCY0->m_vExtent, FCN_V(tgMH_ABS)( vUAX_N ) );
        VEC_T(1,C)                          vE3 = FCN_V(tgMH_SUB)( FCN_V(tgMH_SET1)( TYPE_K(1) ), FCN_V(tgMH_MUL)( vUAX_N, vUAX_N ) );
        VEC_T(1,C)                          vE4 = FCN_V(tgMH_MUL)( psCY0->m_vRadius, FCN_V(tgMH_SQRT)( FCN_V(tgMH_ABS)( vE3 ) ) );
        VEC_T(1,C)                          vTest = FCN_V(tgMH_SUB)( vDist, FCN_V(tgMH_ADD)( vE2, vE4 ) );

        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( vTest, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ))
        {
            /* The cylinder is penetration this plane, return back the error state. */
            return (FCN_V(tgMH_SET1)( -VAR_K(KTgMAX) ));
        };

        return (vTest);
    };
}


/* ---- FCN_VO(tgCO_CY_Closest_PN) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
VEC_T(1) FCN_VO(tgCO_CY_Closest_PN)( VEC_T(1,PC) pvCY0, VEC_T(1,PC) pvPN0, VEC_OBJ_T(TgTUBE,CPC) psCY0, VEC_OBJ_T(TgPLANE,CPC) psPN0 )
{
    /* Calculate out the projection of the cylinder onto the plane's normal */

    VEC_T(1,C)                          vCY0_OG = FCN_VO(tgGM_TB_Query_Origin)( psCY0 );
    VEC_T(1,C)                          vDist = FCN_VO(tgCO_PN_Sign_Dist_PT)(psPN0, vCY0_OG );

    TgERROR( FCN_VO(tgGM_TB_Is_Valid)(psCY0) && FCN_VO(tgGM_PN_Is_Valid)(psPN0) );

    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vDist, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ))
    {
        return (FCN_V(tgMH_SET1)( -VAR_K(KTgMAX) ));
    }
    else
    {
        VEC_T(1,C)                          vCY0_UAX = FCN_VO(tgGM_TB_Query_Axis_Unit)( psCY0 );
        VEC_T(1,C)                          vUAX_N = FCN_V(tgMH_DOT)( psPN0->m_vNormal, vCY0_UAX );
        VEC_T(1,C)                          vE2 = FCN_V(tgMH_MUL)( psCY0->m_vExtent, FCN_V(tgMH_ABS)( vUAX_N ) );
        VEC_T(1,C)                          vE3 = FCN_V(tgMH_SUB)( FCN_V(tgMH_SET1)( TYPE_K(1) ), FCN_V(tgMH_MUL)( vUAX_N, vUAX_N ) );
        VEC_T(1,C)                          vE4 = FCN_V(tgMH_MUL)( psCY0->m_vRadius, FCN_V(tgMH_SQRT)( FCN_V(tgMH_ABS)( vE3 ) ) );
        VEC_T(1,C)                          vTest = FCN_V(tgMH_SUB)( vDist, FCN_V(tgMH_ADD)( vE2, vE4 ) );

        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( vTest, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ))
        {
            /* The cylinder is penetration this plane, return back the error state. */
            return (FCN_V(tgMH_SET1)( -VAR_K(KTgMAX) ));
        }
        else
        {
            VEC_T(1)                            vMAG;

            VEC_T(1,C)                          vK0 = FCN_V(tgMH_MUL)( vCY0_UAX, vUAX_N );
            VEC_T(1,C)                          vK1 = FCN_V(tgMH_SUB)( vK0, psPN0->m_vNormal );
            VEC_T(1,C)                          vK2 = FCN_V(tgMH_NORM_LEN)( &vMAG, vK1 );
            VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_LE)( vMAG, FCN_V(tgMH_SET1)( VAR_K(KTgEPS) ) );
            VEC_T(1,C)                          vK3 = FCN_V(tgMH_SEL)( psCY0->m_vRadius, FCN_V(tgMH_SET1)( TYPE_K(0) ), vCMP_0 );
            VEC_T(1,C)                          vSGN = FCN_V(tgMH_PRX_SGN)( vUAX_N );
            VEC_T(1,C)                          vK5 = FCN_V(tgMH_NMS)( vSGN, psCY0->m_vHAX, FCN_V(tgMH_MUL)( vK3, vK2 ) );
            VEC_T(1,C)                          vPnt = FCN_V(tgMH_ADD)( vCY0_OG, vK5 );

            *pvCY0 = vPnt;
            *pvPN0 = FCN_V(tgMH_NMS)( vTest, psPN0->m_vNormal, vPnt );

            return (vTest);
        };
    };
}


/* ---- FCN_VO(tgCO_PN_Penetrate_CY) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN_VO(tgCO_PN_Penetrate_CY)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_OBJ_T(TgPLANE,CPC) psPN0, VEC_OBJ_T(TgTUBE,CPC) psCY0 )
{
    VEC_T(1)                            vCY0_UAX, vCY0_UB0, vCY0_UB1, vCY0_OG;

    TgPARAM_CHECK( FCN_VO(tgGM_TB_Is_Valid)(psCY0) && FCN_VO(tgGM_PN_Is_Valid)(psPN0) );
    TgPARAM_CHECK( !FCN_V(tgMH_Is_NR0)( psCY0->m_vExtent ));

    if (0 == psPacket->m_nuiMaxContact || psPacket->m_nuiContact >= psPacket->m_nuiMaxContact || nullptr == psPacket->m_psContact)
    {
        return (KTgE_FAIL);
    };

    FCN_V(tgMH_Query_Reference_Frame,3)( &vCY0_UB0, &vCY0_UAX, &vCY0_UB1, &vCY0_OG, &psCY0->m_mReference_Frame );

    {
        /* Project the cylinder onto the plane normal and verify that some portion lies below the plane. */
        VEC_T(1,C)                          vUAX_N = FCN_V(tgMH_DOT)( psPN0->m_vNormal, vCY0_UAX );
        VEC_T(1,C)                          vDist = FCN_VO(tgCO_PN_Sign_Dist_PT)( psPN0, vCY0_OG );
        VEC_T(1,C)                          vE2 = FCN_V(tgMH_MUL)( psCY0->m_vExtent, FCN_V(tgMH_ABS)( vUAX_N ) );
        VEC_T(1,C)                          vE3 = FCN_V(tgMH_SUB)( FCN_V(tgMH_SET1)( TYPE_K(1) ), FCN_V(tgMH_MUL)( vUAX_N, vUAX_N ) );
        VEC_T(1,C)                          vE4 = FCN_V(tgMH_MUL)( psCY0->m_vRadius, FCN_V(tgMH_SQRT)( FCN_V(tgMH_ABS)( vE3 ) ) );
        VEC_T(1,C)                          vTest0 = FCN_V(tgMH_SUB)( FCN_V(tgMH_ADD)( vE2, vE4 ), vDist );

        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTest0, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ))
        {
            return (KTgE_NO_INTERSECT);
        }
        else
        {
            VEC_OBJ_T(STg2_CO_Contact,P)        psContact;
            VEC_T(1)                            vMAG;

            VEC_T(1,C)                          vK0 = FCN_V(tgMH_MUL)( vCY0_UAX, vUAX_N );
            VEC_T(1,C)                          vK1 = FCN_V(tgMH_SUB)( vK0, psPN0->m_vNormal );
            VEC_T(1,C)                          vK2 = FCN_V(tgMH_NORM_LEN)( &vMAG, vK1 );
            VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_GE)( vUAX_N, FCN_V(tgMH_SET1)( TYPE_K(0) ) );
            VEC_T(1,C)                          vSGN__UAX_N = FCN_V(tgMH_SEL)( FCN_V(tgMH_SET1)( TYPE_K(1) ), FCN_V(tgMH_SET1)( -TYPE_K(1) ), vCMP_0 );
            VEC_T(1,C)                          vK3 = FCN_V(tgMH_MAD)( vSGN__UAX_N, psCY0->m_vHAX, vCY0_OG );

            /* If the cylinder is at a 45 degree angle or less to the plane, create contact points at both extreme points of the cylinder. */

            if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( FCN_V(tgMH_ABS)( vUAX_N ), FCN_V(tgMH_SET1)( VAR_K(KTgSQRT1_2) ) ) ))
            {
                VEC_T(1,C)                          vK4 = FCN_V(tgMH_MUL)( vK2, psCY0->m_vRadius );
                VEC_T(1,C)                          vTest1 = FCN_V(tgMH_SUB)( vE4, FCN_V(tgMH_ADD)( vE2, vDist ) );

                psContact = psPacket->m_psContact + psPacket->m_nuiContact;

                psContact->m_vS0 = FCN_V(tgMH_ADD)( vK3, vK4 );
                psContact->m_vN0 = psPN0->m_vNormal;
                psContact->m_vT0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
                psContact->m_vDepth = vTest0;

                ++psPacket->m_nuiContact;

                if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTest1, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ))
                {
                    return (KTgS_OK);
                };

                if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
                {
                    return (KTgE_MAX_CONTACTS);
                }
                else
                {
                    VEC_T(1, C)                          vK5 = FCN_V(tgMH_NMS)( vSGN__UAX_N, psCY0->m_vHAX, vCY0_OG );

                    psContact = (VEC_OBJ_T(STg2_CO_Contact,P))(psPacket->m_psContact + psPacket->m_nuiContact);

                    psContact->m_vS0 = FCN_V(tgMH_ADD)( vK5, vK4 );
                    psContact->m_vN0 = psPN0->m_vNormal;
                    psContact->m_vT0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
                    psContact->m_vDepth = vTest1;

                    ++psPacket->m_nuiContact;

                    return (KTgS_OK);
                };
            }
            else
            {
                /* The cylinder is at 45 degrees or more to the plane, create 3 points around the rim of the cylinder for contact points. */
                VEC_T(1,C)                          vCMP_1 = FCN_V(tgMH_CMP_LE)( vMAG, FCN_V(tgMH_SET1)( VAR_K(KTgEPS) ) );
                VEC_T(1,C)                          vK4 = FCN_V(tgMH_SEL)( vK2, vCY0_UB0, vCMP_1 );
                VEC_T(1,C)                          vDepth_A = FCN_V(tgMH_ADD)( vE2, FCN_V(tgMH_MUL)( vE3, FCN_V(tgMH_SET1)( TYPE_K(0,5) ) ) );
                VEC_T(1,C)                          vDepth = FCN_V(tgMH_SUB)( vDepth_A, vDist );

                psContact = psPacket->m_psContact + psPacket->m_nuiContact;

                psContact->m_vS0 = FCN_V(tgMH_MAD)( vK4, psCY0->m_vRadius, vK3 );
                psContact->m_vN0 = psPN0->m_vNormal;
                psContact->m_vT0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
                psContact->m_vDepth = FCN_V(tgMH_SUB)( FCN_V(tgMH_ADD)( vE2, vE3 ), vDist );

                ++psPacket->m_nuiContact;

                if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vDepth, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ))
                {
                    VEC_T(1,C)                          vK5 = FCN_V(tgMH_UCX)( vK2, vUAX_N );
                    VEC_T(1,C)                          vK6 = FCN_V(tgMH_SEL)( vK5, vCY0_UB1, vCMP_1 );
                    VEC_T(1,C)                          vK7 = FCN_V(tgMH_MUL)( FCN_V(tgMH_SET1)( VAR_K(KTgSQRT3) ), vK6 );
                    VEC_T(1,C)                          vK8 = FCN_V(tgMH_ADD)( vK4, vK7 );
                    VEC_T(1,C)                          vK9 = FCN_V(tgMH_MUL)( FCN_V(tgMH_SET1)( TYPE_K(0,5) ), psCY0->m_vRadius );
                    VEC_T(1,C)                          vKB = FCN_V(tgMH_SUB)( vK4, vK7 );

                    if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
                    {
                        return (KTgE_MAX_CONTACTS);
                    };

                    psContact = psPacket->m_psContact + psPacket->m_nuiContact;

                    psContact->m_vS0 = FCN_V(tgMH_NMS)( vK9, vK8, vK3 );
                    psContact->m_vN0 = psPN0->m_vNormal;
                    psContact->m_vT0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
                    psContact->m_vDepth = vDepth;

                    ++psPacket->m_nuiContact;

                    if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
                    {
                        return (KTgE_MAX_CONTACTS);
                    };

                    psContact = psPacket->m_psContact + psPacket->m_nuiContact;

                    psContact->m_vS0 = FCN_V(tgMH_NMS)( vK9, vKB, vK3 );
                    psContact->m_vN0 = psPN0->m_vNormal;
                    psContact->m_vT0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
                    psContact->m_vDepth = vDepth;

                    ++psPacket->m_nuiContact;
                };

                return (KTgS_OK);
            };
        };
    };
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
