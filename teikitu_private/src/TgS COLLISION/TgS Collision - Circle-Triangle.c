///* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
///*  »Project«   Teikitu Gaming System (TgS) (∂)
//    »File«      TgS Collision - Circle-Triangle.c
//    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
//    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
///*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
///*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
//    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
//    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
///* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
//
//#if !defined (ENABLE_RELOAD_GUARD)
//    #define TEMPLATE__VECTOR_DIM 4
//    #define ENABLE_RELOAD_GUARD
//    #if !defined(TEMPLATE__TYPE_SIZE)
//        #if TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE
//            #define TEMPLATE__TYPE_SIZE 64
//            #include __FILE__
//            #undef TEMPLATE__TYPE_SIZE
//        #endif
//        #define TEMPLATE__TYPE_SIZE 32
//    #endif
//    #undef ENABLE_RELOAD_GUARD
//#endif
//
//#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
//
//
///* == Collision ================================================================================================================================================================== */
//
///* ---- FCN_VO(tgCO_ST_Penetrate_CI) --------------------------------------------------------------------------------------------------------------------------------------------- */
///* Input:  tgPacket: The current series of contact points for this query-series, and contact generation parameters.                                                                */
///* Input:  psST0: Space Triangle.                                                                                                                                                  */
///* Input:  psCI0: Circle - this is the primitive upon which the points of contact are generated.                                                                                   */
///* Output: tgPacket: Points of penetration between the two primitives are added to it                                                                                              */
///* Return: Result code.                                                                                                                                                            */
///* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
//TgRESULT FCN_VO(tgCO_ST_Penetrate_CI)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_OBJ_T(TgSTRI,CPC) psST0, VEC_OBJ_T(TgCIRCLE,CPC) psCI0 )
//{
//    VEC_T(1)                            vA0, vA1, vA2, vC0;
//
//    TgERROR( FCN_VO(tgGM_ST_Is_Valid)(psST0) && FCN_VO(tgGM_CI_Is_Valid)(psCI0) );
//
//    FCN_V(tgMH_Query_Reference_Frame,3)( &vA0, &vA1, &vA2, &vC0, &psCI0->m_mReference_Frame );
//
//    if (0 == psPacket->m_nuiMaxContact || psPacket->m_nuiContact >= psPacket->m_nuiMaxContact || nullptr == psPacket->m_psContact)
//    {
//        return (KTgE_FAIL);
//    }
//    else
//    {
//        /* Find the line of intersection between the two planes (defined by the circle and the triangle) */
//
//        VEC_T(1,C)                          vN1_N2 = FCN_V(tgMH_DOT)( vA1, psST0->m_sCT.m_sET.m_sPT.m_vNormal );
//        VEC_T(1,C)                          vOne = FCN_V(tgMH_SET1)( TYPE_K(1) );
//        VEC_T(1,C)                          vA = FCN_V(tgMH_SUB)( vOne, FCN_V(tgMH_MUL)( vN1_N2, vN1_N2 ) );
//
//        if (vA <= VAR_K(KTgROOT_EPS))
//        {
//            return (KTgE_NO_INTERSECT); /* Make sure the two planes are not co-planar. */
//        }
//        else
//        {
//            VEC_T(1,C)                          vInvA = FCN_V(tgMH_DIV)( vOne, vA );
//            VEC_T(1,C)                          vCID = FCN_V(tgMH_DOT)( vA1, vC0 );
//            VEC_T(1,C)                          vSTD = FCN_V(tgMH_DOT)( psST0->m_sCT.m_sET.m_sPT.m_vNormal, psST0->m_sCT.m_sET.m_sPT.m_avPoint[0] );
//            VEC_T(1,C)                          vL0 = FCN_V(tgMH_NMS)( vInvA, FCN_V(tgMH_MUL)( vSTD, vN1_N2 ), vCID );
//            VEC_T(1,C)                          vL1 = FCN_V(tgMH_NMS)( vInvA, FCN_V(tgMH_MUL)( vCID, vN1_N2 ), vSTD );
//
//            VEC_T(1,C)                          vD0 = FCN_V(tgMH_UCX)( vA1, psST0->m_sCT.m_sET.m_sPT.m_vNormal );
//            VEC_T(1,C)                          vK0 = FCN_V(tgMH_MUL)( vL0, vA1 );
//            VEC_T(1,C)                          vK1 = FCN_V(tgMH_MUL)( vL1, psST0->m_sCT.m_sET.m_sPT.m_vNormal );
//            VEC_T(1,C)                          vS0 = FCN_V(tgMH_ADD)( vK0, vK1 );
//
//            VEC_T(1)                            vT0, vT1, vT2;
//            TgRESULT                            iResult;
//
//            /* F_Clip the common line of intersection to the interior of the triangle */
//            if (TgFAILED( iResult = FCN_VO(tgCO_ST_Clip_PM_LR00)( &vT0, &vT1, psST0, vS0, vD0 ) ))
//            {
//                return (iResult);
//            }
//            else
//            {
//                VEC_T(1,C)                          vK2 = FCN_V(tgMH_MUL)( vT0, vD0 );
//                VEC_T(1,C)                          vK3 = FCN_V(tgMH_MUL)( vT1, vD0 );
//                VEC_T(1,C)                          vK4 = FCN_V(tgMH_ADD)( vS0, vK2 );
//                VEC_T(1,C)                          vK5 = FCN_V(tgMH_ADD)( vS0, vK3 );
//
//                VEC_T(1,C)                          vDistSq = FCN_VO(tgCO_LR11_ClosestSq_PM_PT)( &vT2, vK4, vK5, vC0 );
//
//                if (vDistSq > psCI0->m_vRadiusSq)
//                {
//                    return (KTgE_NO_INTERSECT);
//                }
//                else
//                {
//                    VEC_OBJ_T(STg2_CO_Contact,P)        psContact;
//                    VEC_T(1)                            vKB;
//
//                    VEC_T(1,C)                          vK6 = FCN_V(tgMH_MUL)( vT0 + vT2*vT1 + vT2*vT0, vD0 );
//                    VEC_T(1,C)                          vK7 = FCN_V(tgMH_ADD)( vS0, vK6 );
//                    VEC_T(1,C)                          vK8 = FCN_V(tgMH_SUB)( vC0, vK7 );
//                    VEC_T(1,C)                          vK9 = FCN_V(tgMH_NORM_LEN)( &vKB, vK8 );
//                    VEC_T(1,C)                          vKA = FCN_V(tgMH_MUL)( psCI0->m_vRadius, vK9 );
//
//                    psContact = psPacket->m_psContact + psPacket->m_nuiContact;
//
//                    psContact->m_vN0 = vK9;
//                    psContact->m_vT0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
//                    psContact->m_vDepth = FCN_V(tgMH_SUB)( psCI0->m_vRadius, vKB );
//                    psContact->m_vS0 = FCN_V(tgMH_SUB)( vC0, vKA );
//
//                    ++psPacket->m_nuiContact;
//
//                    return (KTgS_OK);
//                };
//            };
//        };
//    };
//}
//
//
///* =============================================================================================================================================================================== */
//
//#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
