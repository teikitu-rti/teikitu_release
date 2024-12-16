/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Box-Plane.c
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

/* ---- FCN_VO(tgCO_BX_Closest_PM_PN) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* Input:  tgBX0: Box primitive                                                                                                                                                    */
/* Input:  psPN0: Plane primitive                                                                                                                                                  */
/* Output: tyB0,tyB1,tyB2: Parametric parameters to generate the point of closest proximity on the box (one for each axis)                                                         */
/* Output: vPN0: Point of closest proximity on the plane                                                                                                                           */
/* Return: Minimal distance between the two primitives or negative type max if they intersect or are invalid.                                                                      */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
VEC_T(1) FCN_VO(tgCO_BX_Closest_PM_PN)( VEC_T(1,PC) pvBX0, VEC_T(1,PC) pvBX1, VEC_T(1,PC) pvBX2, VEC_T(1,PC) pvPN0, VEC_OBJ_T(TgBOX,CPC) psBX0, VEC_OBJ_T(TgPLANE,CPC) psPN0 )
{
    VEC_T(1)                            vBX0_UX[3], vBX0_OG, vTest, vX0, vX1, vX2, vX3, vDist, vX4, vP0;
    VEC_UN_T(1)                         uUX0_N, uUX1_N, uUX2_N;

    TgPARAM_CHECK(FCN_VO(tgGM_BX_Is_Valid)( psBX0 ) && FCN_VO(tgGM_PN_Is_Valid)( psPN0 ));

    FCN_V(tgMH_Query_Reference_Frame,3)( vBX0_UX + 0, vBX0_UX + 1, vBX0_UX + 2, &vBX0_OG, &psBX0->m_mReference_Frame );

    vTest = FCN_VO(tgCO_PN_Dist_PT)(psPN0, vBX0_OG );

    VEC_UN_1_MEMBER(uUX0_N) = FCN_V(tgMH_DOT)( vBX0_UX[0], psPN0->m_vNormal );
    VEC_UN_1_MEMBER(uUX1_N) = FCN_V(tgMH_DOT)( vBX0_UX[1], psPN0->m_vNormal );
    VEC_UN_1_MEMBER(uUX2_N) = FCN_V(tgMH_DOT)( vBX0_UX[2], psPN0->m_vNormal );

    vX0 = FCN_V(tgMH_Init_Vector_ELEM)( VEC_S_UN_1_MEMBER(uUX0_N).x, VEC_S_UN_1_MEMBER(uUX1_N).x, VEC_S_UN_1_MEMBER(uUX2_N).x );
    vX1 = FCN_V(tgMH_PRX_SGN)( vX0 );
    vX2 = FCN_V(tgMH_MUL)( vX1, psBX0->m_vExtent );
    vX3 = FCN_V(tgMH_DOT)( vX0, vX2 );
    vDist = FCN_V(tgMH_ADD)( vTest, vX3 );

    vX4 = FCN_V(tgMH_MUL)( vDist, psPN0->m_vNormal );
    vP0 = FCN_V(tgMH_SUB)( vX2, vX4 );

    *pvBX0 = FCN_V(tgMH_SPX)( vX2 );
    *pvBX1 = FCN_V(tgMH_SPY)( vX2 );
    *pvBX2 = FCN_V(tgMH_SPZ)( vX2 );
    *pvPN0 = FCN_V(tgMH_Init_Point)( vP0 );

    return (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( vDist, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ) ? FCN_V(tgMH_SET1)( -VAR_K(KTgMAX) ) : vDist);
}


/* ---- FCN_VO(tgCO_PN_Penetrate_BX) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* Input:  tgPacket: The current series of contact points for this query-series, and contact generation parameters.                                                                */
/* Input:  psPN0: Plane primitive                                                                                                                                                  */
/* Input:  tgBX0: Box primitive - contact points are generated on this primitive                                                                                                   */
/* Output: tgPacket: Points of penetration between the two primitives are added to it                                                                                              */
/* Return: Result Code                                                                                                                                                             */
/*                                                                                                                                                                                 */
/*   This routine will create up to four contact points.  Collisions/Physics systems need the best(closest) approximation of the contact surface.  To represent the planananananan */
/* of contact between one box face and the plane, its necessary to use all four points that define the box rectangle (face).                                                       */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN_VO(tgCO_PN_Penetrate_BX)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_OBJ_T(TgPLANE,CPC) psPN0, VEC_OBJ_T(TgBOX,CPC) psBX0 )
{
    VEC_T(1)                            vBX0_UX[3], vBX0_OG;

    TgPARAM_CHECK(FCN_VO(tgGM_BX_Is_Valid)( psBX0 ) && FCN_VO(tgGM_PN_Is_Valid)( psPN0 ));

    if (0 == psPacket->m_nuiMaxContact || psPacket->m_nuiContact >= psPacket->m_nuiMaxContact || nullptr == psPacket->m_psContact)
    {
        return (KTgE_FAIL);
    };

    FCN_V(tgMH_Query_Reference_Frame,3)( vBX0_UX + 0, vBX0_UX + 1, vBX0_UX + 2, &vBX0_OG, &psBX0->m_mReference_Frame );

    {
        //VEC_T(1)                            vTest, vX0, vX1, vX2, vX3, vDist, vX4, vP0;
        //VEC_UN_T(1)                         uUX0_N, uUX1_N, uUX2_N;
        //VEC_T(1)                            vK0;
        VEC_T(1)                            vMin_Extent0, vMin_Extent1, vMin_Extent2;
        VEC_T(1)                            vMin0, vMin1, vMin2, vDepth, vPnt, vTest;
        VEC_OBJ_T(STg2_CO_Contact,P)        psContact;

        VEC_T(1,C)                          vDist  = FCN_VO(tgCO_PN_Dist_PT)( psPN0, vBX0_OG );

        VEC_T(1,C)                          vE0 = FCN_V(tgMH_MUL)( FCN_V(tgMH_SPX)( psBX0->m_vExtent ), vBX0_UX[0] );
        VEC_T(1,C)                          vE1 = FCN_V(tgMH_MUL)( FCN_V(tgMH_SPY)( psBX0->m_vExtent ), vBX0_UX[1] );
        VEC_T(1,C)                          vE2 = FCN_V(tgMH_MUL)( FCN_V(tgMH_SPZ)( psBX0->m_vExtent ), vBX0_UX[2] );

        VEC_T(1,C)                          vE0_N = FCN_V(tgMH_DOT)( vE0, psPN0->m_vNormal );
        VEC_T(1,C)                          vE1_N = FCN_V(tgMH_DOT)( vE1, psPN0->m_vNormal );
        VEC_T(1,C)                          vE2_N = FCN_V(tgMH_DOT)( vE2, psPN0->m_vNormal );

        VEC_T(1,C)                          vABS_E0_N = FCN_V(tgMH_ABS)( vE0_N );
        VEC_T(1,C)                          vABS_E1_N = FCN_V(tgMH_ABS)( vE1_N );
        VEC_T(1,C)                          vABS_E2_N = FCN_V(tgMH_ABS)( vE2_N );

        VEC_T(1,C)                          vPlnN = psPN0->m_vNormal;

        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( vABS_E0_N, vABS_E1_N ) ))
        {
            if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( vABS_E1_N, vABS_E2_N ) ))
            {
                /* fABS_X0_N <= fABS_X1_N <= fABS_X2_N */

                vMin_Extent0 = vABS_E0_N;
                vMin_Extent1 = vABS_E1_N;
                vMin_Extent2 = vABS_E2_N;

                vMin0 = FCN_V(tgMH_CP_SGN)( vE0, vE0_N );
                vMin1 = FCN_V(tgMH_CP_SGN)( vE1, vE1_N );
                vMin2 = FCN_V(tgMH_CP_SGN)( vE2, vE2_N );
            }
            else if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( vABS_E0_N, vABS_E2_N ) ))
            {
                /* fABS_X0_N <= fABS_X2_N < fABS_X1_N */

                vMin_Extent0 = vABS_E0_N;
                vMin_Extent1 = vABS_E2_N;
                vMin_Extent2 = vABS_E1_N;

                vMin0 = FCN_V(tgMH_CP_SGN)( vE0, vE0_N );
                vMin1 = FCN_V(tgMH_CP_SGN)( vE2, vE2_N );
                vMin2 = FCN_V(tgMH_CP_SGN)( vE1, vE1_N );
            }
            else
            {
                /* fABS_X2_N < fABS_X0_N <= fABS_X1_N */

                vMin_Extent0 = vABS_E2_N;
                vMin_Extent1 = vABS_E0_N;
                vMin_Extent2 = vABS_E1_N;

                vMin0 = FCN_V(tgMH_CP_SGN)( vE2, vE2_N );
                vMin1 = FCN_V(tgMH_CP_SGN)( vE0, vE0_N );
                vMin2 = FCN_V(tgMH_CP_SGN)( vE1, vE1_N );
            };
        }
        else
        {
            if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( vABS_E2_N, vABS_E1_N ) ))
            {
                /* fABS_X2_N < = fABS_X1_N < fABS_X0_N */

                vMin_Extent0 = vABS_E2_N;
                vMin_Extent1 = vABS_E1_N;
                vMin_Extent2 = vABS_E0_N;

                vMin0 = FCN_V(tgMH_CP_SGN)( vE2, vE2_N );
                vMin1 = FCN_V(tgMH_CP_SGN)( vE1, vE1_N );
                vMin2 = FCN_V(tgMH_CP_SGN)( vE0, vE0_N );
            }
            else if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( vABS_E2_N, vABS_E0_N ) ))
            {
                /* fABS_X1_N < fABS_X2_N <= fABS_X0_N */

                vMin_Extent0 = vABS_E1_N;
                vMin_Extent1 = vABS_E2_N;
                vMin_Extent2 = vABS_E0_N;

                vMin0 = FCN_V(tgMH_CP_SGN)( vE1, vE1_N );
                vMin1 = FCN_V(tgMH_CP_SGN)( vE2, vE2_N );
                vMin2 = FCN_V(tgMH_CP_SGN)( vE0, vE0_N );
            }
            else
            {
                /* fABS_X1_N < fABS_X0_N < fABS_X2_N */

                vMin_Extent0 = vABS_E1_N;
                vMin_Extent1 = vABS_E0_N;
                vMin_Extent2 = vABS_E2_N;

                vMin0 = FCN_V(tgMH_CP_SGN)( vE1, vE1_N );
                vMin1 = FCN_V(tgMH_CP_SGN)( vE0, vE0_N );
                vMin2 = FCN_V(tgMH_CP_SGN)( vE2, vE2_N );
            };
        };

        vDepth = FCN_V(tgMH_SUB)( vMin_Extent2, vDist );

        /* Point 1 - The point of deepest penetration */

        vTest = FCN_V(tgMH_ADD)( FCN_V(tgMH_ADD)( vDepth, vMin_Extent0 ), vMin_Extent1 );
        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vTest, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ))
        {
            return (KTgE_NO_INTERSECT);
        };

        vPnt = FCN_V(tgMH_SUB)( vBX0_OG, vMin2 );

        psContact = psPacket->m_psContact + psPacket->m_nuiContact;

        psContact->m_vS0 = FCN_V(tgMH_SUB)( FCN_V(tgMH_SUB)( vPnt, vMin0 ), vMin1 );
        psContact->m_vN0 = vPlnN;
        psContact->m_vT0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
        psContact->m_vDepth = vTest;

        ++psPacket->m_nuiContact;

        /* Point 2 - The second point of penetration */

        vTest = FCN_V(tgMH_ADD)( FCN_V(tgMH_SUB)( vDepth, vMin_Extent0 ), vMin_Extent1 );
        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( vTest, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ))
        {
            return (KTgS_OK);
        };

        if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
        {
            return (KTgE_MAX_CONTACTS);
        };

        psContact = psPacket->m_psContact + psPacket->m_nuiContact;

        psContact->m_vS0 = FCN_V(tgMH_SUB)( FCN_V(tgMH_ADD)( vPnt, vMin0 ), vMin1 );
        psContact->m_vN0 = vPlnN;
        psContact->m_vT0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
        psContact->m_vDepth = vTest;

        ++psPacket->m_nuiContact;

        /* Point 3 - Next lowest point of penetration */

        vTest = FCN_V(tgMH_SUB)( FCN_V(tgMH_ADD)( vDepth, vMin_Extent0 ), vMin_Extent1 );
        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( vTest, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ))
        {
            return (KTgS_OK);
        };

        if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
        {
            return (KTgE_MAX_CONTACTS);
        };

        psContact = psPacket->m_psContact + psPacket->m_nuiContact;

        psContact->m_vS0 = FCN_V(tgMH_ADD)( FCN_V(tgMH_SUB)( vPnt, vMin0 ), vMin1 );
        psContact->m_vN0 = vPlnN;
        psContact->m_vT0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
        psContact->m_vDepth = vTest;

        ++psPacket->m_nuiContact;

        /* Point 4 - Point of closure - this completes the rectangle/face of the box of deepest penetration */

        vTest = FCN_V(tgMH_SUB)( FCN_V(tgMH_SUB)( vDepth, vMin_Extent0 ), vMin_Extent1 );
        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( vTest, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ))
        {
            return (KTgS_OK);
        };

        if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
        {
            return (KTgE_MAX_CONTACTS);
        };

        psContact = psPacket->m_psContact + psPacket->m_nuiContact;

        psContact->m_vS0 = FCN_V(tgMH_SUB)( FCN_V(tgMH_SUB)( vPnt, vMin0 ), vMin1 );
        psContact->m_vN0 = vPlnN;
        psContact->m_vT0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
        psContact->m_vDepth = vTest;

        ++psPacket->m_nuiContact;

        return (KTgS_OK);
    };
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
