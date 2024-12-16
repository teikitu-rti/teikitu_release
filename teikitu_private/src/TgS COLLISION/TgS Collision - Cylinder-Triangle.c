///* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
///*  »Project«   Teikitu Gaming System (TgS) (∂)
//    »File«      TgS Collision - Cylinder-Triangle.c
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
///* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
///*  File Local Functions                                                                                                                                                           */
///* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
//
//static TgBOOL                               FCN_VO(tgCO_ST_Axis_Seperation_CY)( VEC_OBJ_T(STg2_CO_Axis_Result,PC), VEC_OBJ_T(TgSTRI,CPC), VEC_OBJ_T(TgTUBE,CPC));
//static TgBOOL                               FCN_VO(tgCO_ST_Internal_ClipTriToCyl_CY)( VEC_OBJ_T(STg2_CO_Clip_List,PC), VEC_OBJ_T(TgSTRI,CPC), VEC_OBJ_T(TgTUBE,CPC));
//
//
//
//
///* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
///*  Public Functions                                                                                                                                                               */
///* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
//
///* ---- FCN_VO(tgCO_ST_Penetrate_CY) --------------------------------------------------------------------------------------------------------------------------------------------- */
///* Input:  tgPacket: The current series of contact points for this query-series, and contact generation parameters.                                                                */
///* Input:  psST0: Space Triangle primitive                                                                                                                                         */
///* Input:  psCY0: Cylinder primitive - contact points are generated on this primitive                                                                                              */
///* Output: tgPacket: Points of penetration between the two primitives are added to it                                                                                              */
///* Return: Result Code                                                                                                                                                             */
///* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
//TgRESULT FCN_VO(tgCO_ST_Penetrate_CY)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_OBJ_T(TgSTRI,CPC) psST0, VEC_OBJ_T(TgTUBE,CPC) psCY0)
//{
//    VEC_OBJ_T(STg2_CO_Contact,P)        psContact;;
//    VEC_OBJ_T(STg2_CO_Axis_Result)      sAxS;
//
//    TgSINT_E32_C    niContact = psPacket->m_nuiContact;
//
//    TgERROR(FCN_VO(tgGM_TB_Is_Valid)(psCY0) && FCN_VO(tgGM_ST_Is_Valid)(psST0));
//
//    if (0 == psPacket->m_nuiMaxContact || psPacket->m_nuiContact >= psPacket->m_nuiMaxContact || nullptr == psPacket->m_psContact)
//    {
//        return (KTgE_FAIL);
//    };
//
//    /*TgDEBUG_COLLISION_TRIANGLE_CREATEID( iDBG_TriID, psST0, etgDEBUG_COLLISION_ENTERFCN ); */
//
//    {
//        /* Primitive Culling - Set of criteria required for the primitive to be considered penetrating the triangle. */
//
//        VEC_T(1,C)      vK0 = FCN_V(tgMH_SUB)( psCY0->m_vOrigin, psST0->m_sCT.m_sET.m_sPT.m_avPoint);
//        VAR_T(C)        fDS_N = FCN_V(tgMH_DOT)( psST0->m_sCT.m_sET.m_sPT.m_vNormal, vK0 );
//        VAR_T(C)        fEX_N = FCN_V(tgMH_DOT)( psST0->m_sCT.m_sET.m_sPT.m_vNormal, &psCY0->m_vHAX);
//        VAR_T(C)        fS0_N = fDS_N - fEX_N;
//        VAR_T(C)        fS1_N = fDS_N + fEX_N;
//        VAR_T(C)        fRadius = psCY0->m_fRadius;
//
//        if ((fS0_N > fRadius && fS1_N > fRadius) || (fS0_N < TYPE_K(0) && fS1_N < TYPE_K(0)))
//        {
//            /* Either both of the capsule's end points are below the plane or more than radius above the plane. */
//
//            return (KTgE_NO_INTERSECT);
//        };
//
//        /*TgDEBUG_COLLISION_TRIANGLE( iDBG_TriID, etgDEBUG_COLLISION_PASSED_REJECT ); */
//
//        /* Find the minimal axis of separation, or return if the primitives are not in contact. */
//
//        if (!FCN_VO(tgCO_ST_Axis_Seperation_CY)( sAxS, psST0, psCY0))
//        {
//            return (KTgE_NO_INTERSECT);
//        };
//
//        TgERROR( FCN_F(tgCM_NR1)(FCN_V(tgMH_LSQ)( sAxS.m_vNormal)) && sAxS.m_fDepth >= TYPE_K(0) );
//    }
//
//    /* == Contact Generation == */
//
//    if (sAxS.m_iAxis >= 4)
//    {
//        /* -- Axis: Cap-Surface Component -- */
//
//        VEC_T(1,C)      vK0 = FCN_V(tgMH_MUL_SV)(psCY0->m_fRadius, &sAxS.m_vNormal);
//
//        psContact = psPacket->m_psContact + psPacket->m_nuiContact;
//
//        psContact->m_vS0 = FCN_V(tgMH_SUB)( sAxS.m_vPoint, vK0 );
//        psContact->m_vN0 = sAxS.m_vNormal;
//        psContact->m_vT0 = TYPE_K(0);
//        psContact->m_vDepth = sAxS.m_fDepth;
//
//        ++psPacket->m_nuiContact;
//
//        return (KTgS_OK);
//    };
//
//    if (sAxS.m_iAxis >= 2)
//    {
//        /* -- Axis: Cylinder Primary Axis -- */
//
//        VEC_OBJ_T(STg2_CO_Clip_List,PU)             psCL;
//
//        psCL = TgMALLOC_POOL( sizeof( VEC_OBJ_T(STg2_CO_Clip_List) ) + 8 * sizeof( VEC_T(1) ) );
//        psCL->m_nuiPoint = 0;
//        psCL->m_nuiMax = 8;
//
//        if (FCN_VO(tgCO_ST_Internal_ClipTriToCyl_CY)(psCL, psST0, psCY0) && 0 == psCL->m_nuiPoint)
//        {
//            TgFREE_POOL( psCL );
//            return (KTgE_NO_INTERSECT);
//        }
//        else
//        {
//            TgSINT_E32                          iIdx;
//
//            TgSINT_E32_C niMax = tgCM_MIN_S32( psCL->m_nuiPoint, psPacket->m_nuiMaxContact - psPacket->m_nuiContact );
//            for (iIdx = 0; iIdx < niMax; ++iIdx)
//            {
//                VEC_T(1,C)      vK0 = FCN_V(tgMH_SUB)(psCL->m_avPoint + iIdx, &psCY0->m_vOrigin);
//                VAR_T(C)        fP_AX = FCN_V(tgMH_DOT)( vK0, &psCY0->m_vU_HAX);
//                VAR_T()                             fDepth = psCY0->m_fExtent - FCN_F(tgPM_ABS)(fP_AX);
//                VEC_T(1,C)      vK2 = FCN_V(tgMH_MUL_SV)(fDepth, &sAxS.m_vNormal);
//
//                psContact = psPacket->m_psContact + psPacket->m_nuiContact;
//
//                fDepth = FCN_F(tgPM_FSEL)(fDepth, fDepth, TYPE_K(0));
//
//                psContact->m_vS0 = FCN_V(tgMH_SUB)(psCL->m_avPoint + iIdx, vK2 );
//                psContact->m_vN0 = sAxS.m_vNormal;
//                psContact->m_vT0 = TYPE_K(0);
//                psContact->m_vDepth = fDepth;
//
//                ++psPacket->m_nuiContact;
//            };
//
//            if (0 != psCL->m_nuiPoint)
//            {
//                TgFREE_POOL( psCL );
//                return (niMax == psCL->m_nuiPoint ? KTgS_OK : KTgE_MAX_CONTACTS);
//            };
//        };
//
//        TgFREE_POOL( psCL );
//
//        /* Error catch - default to triangle normal for this error state. */
//    };
//
//
//    /* -- Triangle Normal -- */
//
//    {
//        VAR_T(C)        fAX_N = FCN_V(tgMH_DOT)( psCY0->m_vU_HAX, &psST0->m_sCT.m_sET.m_sPT.m_vNormal);
//        VAR_T(C)        fUseBX = FCN_F(tgPM_ABS)(fAX_N) - (TYPE_K(1) - VAR_K(KTgEPS));
//        VAR_T(C)        fDN = FCN_F(tgPM_FSEL)(fAX_N, -TYPE_K(1), TYPE_K(1));
//        VEC_T(1,C)      vK0 = FCN_V(tgMH_MUL_SV)(fDN, &psCY0->m_vHAX);
//        VEC_T(1,C)      vC0 = FCN_V(tgMH_ADD)( psCY0->m_vOrigin, vK0 );
//        VEC_T(1,C)      vK1 = FCN_V(tgMH_MUL_SV)(fAX_N, &psCY0->m_vU_HAX);
//        VEC_T(1,C)      vT0 = FCN_V(tgMH_SUB)( vK1, &psST0->m_sCT.m_sET.m_sPT.m_vNormal);
//        VAR_T(C)        fK0 = FCN_F(tgPM_FSEL)(fUseBX, psCY0->m_vU_Basis0.x, vT0.x);
//        VAR_T(C)        fK1 = FCN_F(tgPM_FSEL)(fUseBX, psCY0->m_vU_Basis0.y, vT0.y);
//        VAR_T(C)        fK2 = FCN_F(tgPM_FSEL)(fUseBX, psCY0->m_vU_Basis0.z, vT0.z);
//        VEC_T(1,C)      vK2 = FCN_V(tgMH_Init_Vector_ELEM)(fK0, fK1, fK2);
//        VEC_T(1,C)      vX0 = FCN_V(tgMH_NORM)( vK2 );
//
//
//        if (fAX_N > TYPE_K(0,5))
//        {
//            /* Method: Produce three points along symmetrical points along the cylinder rim.  If the cylinder plane is not parallel to the triangle plane then one of */
//            /* these points must be the point of deepest penetration. */
//
//            VAR_T()                             fT0, fT1;
//            TgSINT_E32                          iCode;
//
//            VEC_T(1,C)      vT1 = FCN_V(tgMH_CX)( vX0, &psCY0->m_vU_HAX);
//            VAR_T(C)        fK3 = FCN_F(tgPM_FSEL)(fUseBX, psCY0->m_vU_Basis1.x, vT1.x);
//            VAR_T(C)        fK4 = FCN_F(tgPM_FSEL)(fUseBX, psCY0->m_vU_Basis1.y, vT1.y);
//            VAR_T(C)        fK5 = FCN_F(tgPM_FSEL)(fUseBX, psCY0->m_vU_Basis1.z, vT1.z);
//            VEC_T(1,C)      vK3 = FCN_V(tgMH_Init_Vector_ELEM)(fK3, fK4, fK5);
//            VEC_T(1,C)      vK4 = FCN_V(tgMH_NORM)( vK3 );
//            VEC_T(1,C)      vX1 = FCN_V(tgMH_MUL_VS)( vK4, VAR_K(KTgSQRT3));
//
//            /* Generate the line segment for each of these points from the middle of the cylinder's end cap - and then clip it against the triangle using feature */
//            /* reduction information.  Chose the largest t value returned to create the contact point. */
//
//            VEC_T(1,C)      vT2 = FCN_V(tgMH_MUL_SV)(psCY0->m_fRadius, vX0 );
//            VEC_T(1,C)      vK5 = FCN_V(tgMH_ADD)( vX0, vX1 );
//            VEC_T(1,C)      vT3 = FCN_V(tgMH_MUL_SV)(-TYPE_K(0,5)*psCY0->m_fRadius, vK5 );
//            VEC_T(1,C)      vK6 = FCN_V(tgMH_SUB)( vX0, vX1 );
//            VEC_T(1,C)      vT4 = FCN_V(tgMH_MUL_SV)(-TYPE_K(0,5)*psCY0->m_fRadius, vK6 );
//
//            if (FCN_VO(tgCO_ST_Clip_PM_F_LR11)( fT0, &fT1, &iCode, psST0, &vC0, vT2 ) >= 0 && 0 != (iCode & 12))
//            {
//                VAR_T(C)        fL0 = 0 != (iCode & 4) ? fT0 : -fT1;
//                VAR_T(C)        fL1 = 0 != (iCode & 8) ? fT1 : -fT0;
//                VAR_T(C)        fLN = FCN_F(tgPM_FSEL)(fL1 - fL0, fL1, fL0);
//                VEC_T(1,C)      vK8 = FCN_V(tgMH_MUL_SV)(fLN, vT2 );
//                VEC_T(1,C)      vK7 = FCN_V(tgMH_ADD)( vC0, vK8 );
//                VEC_T(1,C)      vK9 = FCN_V(tgMH_SUB)(psST0->m_sCT.m_sET.m_sPT.m_avPoint, vK7 );
//                VAR_T(C)        fK6 = FCN_V(tgMH_DOT)( vK9, &psST0->m_sCT.m_sET.m_sPT.m_vNormal);
//
//                if (fK6 >= TYPE_K(0))
//                {
//                    if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
//                    {
//                        return (KTgE_MAX_CONTACTS);
//                    };
//
//                    psContact = psPacket->m_psContact + psPacket->m_nuiContact;
//
//                    psContact->m_vS0 = vK7;
//                    psContact->m_vN0 = psST0->m_sCT.m_sET.m_sPT.m_vNormal;
//                    psContact->m_vT0 = TYPE_K(0);
//                    psContact->m_vDepth = fK6;
//
//                    ++psPacket->m_nuiContact;
//                };
//            };
//
//            if (FCN_VO(tgCO_ST_Clip_PM_F_LR11)( fT0, &fT1, &iCode, psST0, &vC0, vT3 ) >= 0 && 0 != (iCode & 12))
//            {
//                VAR_T(C)        fL0 = 0 != (iCode & 4) ? fT0 : -fT1;
//                VAR_T(C)        fL1 = 0 != (iCode & 8) ? fT1 : -fT0;
//                VAR_T(C)        fLN = FCN_F(tgPM_FSEL)(fL1 - fL0, fL1, fL0);
//                VEC_T(1,C)      vK8 = FCN_V(tgMH_MUL_SV)(fLN, vT3 );
//                VEC_T(1,C)      vK7 = FCN_V(tgMH_ADD)( vC0, vK8 );
//                VEC_T(1,C)      vK9 = FCN_V(tgMH_SUB)(psST0->m_sCT.m_sET.m_sPT.m_avPoint, vK7 );
//                VAR_T(C)        fK6 = FCN_V(tgMH_DOT)( vK9, &psST0->m_sCT.m_sET.m_sPT.m_vNormal);
//
//                if (fK6 >= TYPE_K(0))
//                {
//                    if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
//                    {
//                        return (KTgE_MAX_CONTACTS);
//                    };
//
//                    psContact = psPacket->m_psContact + psPacket->m_nuiContact;
//
//                    psContact->m_vS0 = vK7;
//                    psContact->m_vN0 = psST0->m_sCT.m_sET.m_sPT.m_vNormal;
//                    psContact->m_vT0 = TYPE_K(0);
//                    psContact->m_vDepth = fK6;
//
//                    ++psPacket->m_nuiContact;
//                };
//            };
//
//
//            if (FCN_VO(tgCO_ST_Clip_PM_F_LR11)( fT0, &fT1, &iCode, psST0, &vC0, vT4 ) >= 0 && 0 != (iCode & 12))
//            {
//                VAR_T(C)        fL0 = 0 != (iCode & 4) ? fT0 : -fT1;
//                VAR_T(C)        fL1 = 0 != (iCode & 8) ? fT1 : -fT0;
//                VAR_T(C)        fLN = FCN_F(tgPM_FSEL)(fL1 - fL0, fL1, fL0);
//                VEC_T(1,C)      vK8 = FCN_V(tgMH_MUL_SV)(fLN, vT4 );
//                VEC_T(1,C)      vK7 = FCN_V(tgMH_ADD)( vC0, vK8 );
//                VEC_T(1,C)      vK9 = FCN_V(tgMH_SUB)(psST0->m_sCT.m_sET.m_sPT.m_avPoint, vK7 );
//                VAR_T(C)        fK6 = FCN_V(tgMH_DOT)( vK9, &psST0->m_sCT.m_sET.m_sPT.m_vNormal);
//
//                if (fK6 >= TYPE_K(0))
//                {
//                    if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
//                    {
//                        return (KTgE_MAX_CONTACTS);
//                    };
//
//                    psContact = psPacket->m_psContact + psPacket->m_nuiContact;
//
//                    psContact->m_vS0 = vK7;
//                    psContact->m_vN0 = psST0->m_sCT.m_sET.m_sPT.m_vNormal;
//                    psContact->m_vT0 = TYPE_K(0);
//                    psContact->m_vDepth = fK6;
//
//                    ++psPacket->m_nuiContact;
//                };
//            };
//
//            if (niContact != psPacket->m_nuiContact)
//            {
//                return (KTgS_OK);
//            }
//            else
//            {
//                VEC_OBJ_T(STg2_CO_Clip_List,PU)             psCL;
//
//                TgSINT_E32                          iIdx, niMax;
//
//                VAR_T(C)        fK6 = TYPE_K(-2,0)*psCY0->m_fExtent;
//                VEC_T(1,C)      vT5 = FCN_V(tgMH_MUL_SV)(fK6, &psST0->m_sCT.m_sET.m_sPT.m_vNormal);
//
//                psCL = TgMALLOC_POOL( sizeof( VEC_OBJ_T(STg2_CO_Clip_List) ) + 8 * sizeof( VEC_T(1) ) );
//                psCL->m_nuiPoint = 0;
//                psCL->m_nuiMax = 8;
//
//                FCN_VO(tgCO_ST_Internal_ClipTriToCyl_CY)(psCL, psST0, psCY0);
//
//                if (0 == psCL->m_nuiPoint)
//                {
//                    TgFREE_POOL( psCL );
//                    return (KTgE_NO_INTERSECT);
//                }
//
//                niMax = tgCM_MIN_S32( psCL->m_nuiPoint, psPacket->m_nuiMaxContact - psPacket->m_nuiContact );
//
//                for (iIdx = 0; iIdx < niMax; ++iIdx)
//                {
//                    if (FCN_VO(tgCO_CY_Clip_PM_LR11)( fT0, &fT1, psCY0, psCL->m_avPoint + iIdx, vT5 ) < 0)
//                    {
//                        continue;
//                    };
//
//                    if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
//                    {
//                        TgFREE_POOL( psCL );
//                        return (KTgE_MAX_CONTACTS);
//                    }
//                    else
//                    {
//                        VAR_T(C)        fLN = FCN_F(tgPM_FSEL)(fT1 - fT0, fT1, fT0);
//                        VEC_T(1,C)      vK7 = FCN_V(tgMH_MUL_SV)(fLN, vT5 );
//                        VEC_T(1,C)      vK8 = FCN_V(tgMH_ADD)(psCL->m_avPoint + iIdx, vK7 );
//                        VEC_T(1,C)      vK9 = FCN_V(tgMH_SUB)(psST0->m_sCT.m_sET.m_sPT.m_avPoint, vK8 );
//                        VAR_T(C)        fK7 = FCN_V(tgMH_DOT)( vK9, &psST0->m_sCT.m_sET.m_sPT.m_vNormal);
//
//                        psContact = psPacket->m_psContact + psPacket->m_nuiContact;
//
//                        psContact->m_vS0 = vK8;
//                        psContact->m_vN0 = psST0->m_sCT.m_sET.m_sPT.m_vNormal;
//                        psContact->m_vT0 = TYPE_K(0);
//                        psContact->m_vDepth = fK7;
//
//                        ++psPacket->m_nuiContact;
//                    };
//                };
//
//                TgFREE_POOL( psCL );
//                return (niContact != psPacket->m_nuiContact ? KTgS_OK : KTgE_NO_INTERSECT);
//            };
//        }
//        else
//        {
//            VAR_T()                             fT0, fT1;
//            TgSINT_E32                          iCode;
//
//            VEC_T(1,C)      vD0 = FCN_V(tgMH_MUL_SV)(TYPE_K(-2,0)*fDN, &psCY0->m_vHAX);
//            VEC_T(1,C)      vS0 = FCN_V(tgMH_ADD)( vC0, vX0 );
//
//            if (FCN_VO(tgCO_ST_Clip_PM_F_LR11)( fT0, &fT1, &iCode, psST0, &vS0, vD0 ) < 0 || 0 == (iCode & 12))
//            {
//                return (KTgE_NO_INTERSECT);
//            }
//            else
//            {
//                VEC_T(1,C)      vK7 = FCN_V(tgMH_MUL_SV)(fT0, vD0 );
//                VEC_T(1,C)      vK8 = FCN_V(tgMH_ADD)( vS0, vK7 );
//                VEC_T(1,C)      vK9 = FCN_V(tgMH_SUB)(psST0->m_sCT.m_sET.m_sPT.m_avPoint, vK8 );
//                VAR_T(C)        fK8 = FCN_V(tgMH_DOT)( vK9, &psST0->m_sCT.m_sET.m_sPT.m_vNormal);
//
//                VEC_T(1,C)      vKA = FCN_V(tgMH_MUL_SV)(fT1, vD0 );
//                VEC_T(1,C)      vKB = FCN_V(tgMH_ADD)( vS0, vKA );
//                VEC_T(1,C)      vKC = FCN_V(tgMH_SUB)(psST0->m_sCT.m_sET.m_sPT.m_avPoint, vKB );
//                VAR_T(C)        fK7 = FCN_V(tgMH_DOT)( vKC, &psST0->m_sCT.m_sET.m_sPT.m_vNormal);
//
//                if (0 == (iCode & 4) && fK8 >= TYPE_K(0))
//                {
//                    psContact = psPacket->m_psContact + psPacket->m_nuiContact;
//
//                    psContact->m_vS0 = vK8;
//                    psContact->m_vN0 = psST0->m_sCT.m_sET.m_sPT.m_vNormal;
//                    psContact->m_vT0 = TYPE_K(0);
//                    psContact->m_vDepth = fK8;
//
//                    ++psPacket->m_nuiContact;
//                };
//
//                if (0 == (iCode & 8) && fK7 >= TYPE_K(0))
//                {
//                    if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
//                    {
//                        return (KTgE_MAX_CONTACTS);
//                    };
//
//                    psContact = psPacket->m_psContact + psPacket->m_nuiContact;
//
//                    psContact->m_vS0 = vKB;
//                    psContact->m_vN0 = psST0->m_sCT.m_sET.m_sPT.m_vNormal;
//                    psContact->m_vT0 = TYPE_K(0);
//                    psContact->m_vDepth = fK7;
//
//                    ++psPacket->m_nuiContact;
//                };
//            };
//        };
//    };
//
//    return (niContact != psPacket->m_nuiContact ? KTgS_OK : KTgE_NO_INTERSECT);
//}
//
//
//
//
///* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
///*  File Local Functions                                                                                                                                                           */
///* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
//
///* ---- FCN_VO(tgCO_ST_Axis_Seperation_CY) --------------------------------------------------------------------------------------------------------------------------------------- */
///* Input:  psST0: Space Triangle primitive                                                                                                                                         */
///* Input:  psCY0: Cylinder primitive                                                                                                                                               */
///* Output: sAxS: Structure holds the resulting axis separation information necessary to create a contact set.                                                                      */
///* Return: False if a separating axis exists, true otherwise                                                                                                                       */
///* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
//static TgBOOL FCN_VO(tgCO_ST_Axis_Seperation_CY)(VEC_OBJ_T(STg2_CO_Axis_Result,PC) psAxS, VEC_OBJ_T(TgSTRI,CPC) psST0, VEC_OBJ_T(TgTUBE,CPC) psCY0)
//{
//    VAR_T()                             fMinDepth, fMaxDepth, fCyl;
//    VEC_T(1,C)        vProxCyl, vProxTri;
//
//    VAR_T(C)        fTriD = FCN_V(tgMH_DOT)(psST0->m_sCT.m_sET.m_sPT.m_avPoint, &psST0->m_sCT.m_sET.m_sPT.m_vNormal);
//    VAR_T(C)        fNormTest = FCN_V(tgMH_DOT)( psST0->m_sCT.m_sET.m_sPT.m_vNormal, &psCY0->m_vU_HAX);
//
//    {
//        /* -- Axis: Triangle Normal -- */
//
//        VAR_T()                             fMinCyl, fMaxCyl;
//
//        FCN_VO(tgGM_CY_Project)( fMinCyl, &fMaxCyl, psCY0, &psST0->m_sCT.m_sET.m_sPT.m_vNormal);
//
//        TgERROR( FCN_VO(tgGM_TB_Is_Valid)(psCY0) && FCN_VO(tgGM_ST_Is_Valid)(psST0) );
//
//        if (fMaxCyl < fTriD || fMinCyl > fTriD)
//        {
//            return (false);
//        };
//
//        psAxS->m_vNormal = FCN_V(tgMH_NEG)( psST0->m_sCT.m_sET.m_sPT.m_vNormal);
//        psAxS->m_fDepth = fTriD - fMinCyl;
//        psAxS->m_iAxis = 1;
//    };
//
//    {
//        /* -- Axis: Cylinder Primary Axis -- */
//
//        VAR_T()                             fMinCyl, fMaxCyl, fMinTri, fMaxTri;
//
//        if (!FCN_F(tgCM_NR1)(fNormTest))
//        {
//            fMinCyl = FCN_V(tgMH_DOT)( psCY0->m_vOrigin, &psCY0->m_vU_HAX);
//            fMaxCyl = fMinCyl + psCY0->m_fExtent;
//            fMinCyl -= psCY0->m_fExtent;
//
//            FCN_VO(tgGM_ST_Project)( fMinTri, &fMaxTri, psST0, &psCY0->m_vU_HAX);
//
//            if (fMaxCyl < fMinTri || fMinCyl > fMaxTri)
//            {
//                return (false);
//            };
//
//            fMinDepth = fMaxCyl - fMinTri;
//            fMaxDepth = fMaxTri - fMinCyl;
//
//            if (fMinDepth > fMaxDepth)
//            {
//                if (fMaxDepth < psAxS->m_fDepth)
//                {
//                    psAxS->m_vNormal = psCY0->m_vU_HAX;
//                    psAxS->m_fDepth = fMaxDepth;
//                    psAxS->m_iAxis = 2;
//                };
//            }
//            else
//            {
//                if (fMinDepth < psAxS->m_fDepth)
//                {
//                    psAxS->m_vNormal = FCN_V(tgMH_NEG)( psCY0->m_vU_HAX);
//                    psAxS->m_fDepth = fMinDepth;
//                    psAxS->m_iAxis = 3;
//                };
//            };
//        };
//    };
//
//    {
//        /* -- Axis: Radial Cylindrical Sweep -- */
//
//        VAR_T()                             fET0, fET1;
//
//        VAR_T(C) fDistSq = FCN_VO(tgCO_ST_ClosestSq_PM_SG)( fET0, &fET1, &fCyl, psST0, &psCY0->m_sAX);
//
//        if (fDistSq > psCY0->m_fRadiusSq)
//        {
//            return (false);
//        };
//
//        if (FCN_VO(tgGM_ST_Is_Point_Culled)(psST0, fET0, fET1))
//        {
//            return (true);
//        }
//        else
//        {
//            VEC_T(1,C)      vK0 = FCN_V(tgMH_MUL_SV)(fET0, psST0->m_sCT.m_sET.m_avEdge[0]);
//            VEC_T(1,C)      vK1 = FCN_V(tgMH_MUL_SV)(fET1, psST0->m_sCT.m_sET.m_avEdge[2]);
//            VEC_T(1,C)      vK2 = FCN_V(tgMH_MUL_SV)(fCyl, &psCY0->m_sAX.m_vDirN);
//            VEC_T(1,C)      vK3 = FCN_V(tgMH_SUB)( vK0, vK1 );
//
//            vProxCyl = FCN_V(tgMH_ADD)( psCY0->m_sAX.m_vOrigin, vK2 );
//            vProxTri = FCN_V(tgMH_ADD)(psST0->m_sCT.m_sET.m_sPT.m_avPoint, vK3 );
//        };
//    }
//
//    if (FCN_F(tgCM_NR0)(fCyl) || FCN_F(tgCM_NR1)(fCyl))
//    {
//        /* -- Axis: Cap-Surface Component -- */
//
//        VAR_T(C)        fDet = TYPE_K(1) - fNormTest*fNormTest;
//
//        if (fDet <= VAR_K(KTgROOT_EPS))
//        {
//            /* The plane upon which the cylinder cap rests is parallel to that of the triangle.  Return the last best result. */
//
//            return (true);
//        }
//        else
//        {
//            /* Define the line of intersection between the two planar surfaces. */
//
//            VEC_OBJ_T(TgLINE)                   sLN0;
//            VAR_T()                             fG0;
//            VEC_OBJ_T(STg2_CO_Clip_List,PU)             psCL;
//
//            VAR_T(C)        fInvDet = TYPE_K(1) / fDet;
//            VAR_T(C)        fCylD = FCN_V(tgMH_DOT)( psCY0->m_vU_HAX, vProxCyl );
//            VAR_T(C)        fTA = fInvDet*(fCylD - fNormTest*fTriD);
//            VAR_T(C)        fTB = fInvDet*(fTriD - fNormTest*fCylD);
//            VEC_T(1,C)      vK0 = FCN_V(tgMH_MUL_SV)(fTA, &psCY0->m_vU_HAX);
//            VEC_T(1,C)      vK1 = FCN_V(tgMH_MUL_SV)(fTB, &psST0->m_sCT.m_sET.m_sPT.m_vNormal);
//
//            psCL = TgMALLOC_POOL( sizeof( VEC_OBJ_T(STg2_CO_Clip_List) ) + 8 * sizeof( VEC_T(1) ) );
//            psCL->m_nuiPoint = 0;
//            psCL->m_nuiMax = 8;
//
//            sLN0.m_vOrigin = FCN_V(tgMH_ADD)( vK0, vK1 );
//            sLN0.m_vDirN = FCN_V(tgMH_CX)( psCY0->m_vU_HAX, &psST0->m_sCT.m_sET.m_sPT.m_vNormal);
//
//            FCN_VO(tgCO_ST_Clip_LN)(psCL, psST0, sLN0 );
//
//            if (psCL->m_nuiPoint != 2)
//            {
//                /* No intersection can exist between the triangle and cylinder cap.  Error state.  Return the last best result. */
//                TgFREE_POOL( psCL );
//                return (true);
//            }
//            else
//            {
//                /* Find the minimal distance to the cap rim. */
//
//                VEC_T(1,C)      vK2 = FCN_V(tgMH_SUB)(psCL->m_avPoint[1], psCL->m_avPoint);
//                VAR_T(C)        fK0 = FCN_VO(tgCO_LR11_ClosestSq_PM_PT)( fG0, psCL->m_avPoint, &vK2, vProxCyl );
//                VEC_T(1,C)      vK3 = FCN_V(tgMH_MUL_SV)(fG0, vK2 );
//
//                TgFREE_POOL( psCL );
//
//                if (fK0 > psCY0->m_fRadiusSq)
//                {
//                    /* Error state.  Return the last best result. */
//                    return (true);
//                };
//
//                vProxTri = FCN_V(tgMH_ADD)(psCL->m_avPoint, vK3 );
//            };
//        };
//    };
//
//    {
//        VAR_T()                             fTest;
//
//        VEC_T(1,C)      vT0 = FCN_V(tgMH_SUB)( vProxCyl, vProxTri );
//        VEC_T(1,C)      vNormal = FCN_V(tgMH_NORM_LEN)( fTest, vT0 );
//
//        if (FCN_F(tgCM_NR0)(fTest))
//        {
//            return (true); /* Error state.  Return the last best result. */
//        };
//
//        fTest = FCN_F(tgPM_FSEL)(psCY0->m_fRadius - fTest, psCY0->m_fRadius - fTest, TYPE_K(0));
//
//        if (1 == psAxS->m_iAxis && FCN_F(tgCM_NR1)(FCN_V(tgMH_DOT)( psST0->m_sCT.m_sET.m_sPT.m_vNormal, vNormal )))
//        {
//            return (true); /* Bias towards having the contacts created for a triangle contact. */
//        };
//
//        if (fTest < psAxS->m_fDepth)
//        {
//            psAxS->m_vNormal = vNormal;
//            psAxS->m_vPoint = vProxCyl;
//            psAxS->m_fDepth = fTest;
//            psAxS->m_iAxis = 4;
//        };
//    };
//
//    return (true);
//}
//
//
///* ---- FCN_VO(tgCO_ST_Internal_ClipTriToCyl_CY) --------------------------------------------------------------------------------------------------------------------------------- */
///* Input:  psST0: Space Triangle primitive                                                                                                                                         */
///* Input:  psCY0: Cylinder primitive                                                                                                                                               */
///* Output: sCL: The resulting points of the clipping operation                                                                                                                     */
///* Return: Result Code                                                                                                                                                             */
///* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
//static TgBOOL FCN_VO(tgCO_ST_Internal_ClipTriToCyl_CY)(VEC_OBJ_T(STg2_CO_Clip_List,PC) psCL, VEC_OBJ_T(TgSTRI,CPC) psST0, VEC_OBJ_T(TgTUBE,CPC) psCY0)
//{
//    TgBOOL                              bC0, bC1, bTest0, bTest1, bRet = false;
//    VAR_T()                             fT0, fT1;
//
//    /* Triangle Edge 0 */
//
//    bRet |= FCN_VO(tgCO_CY_Clip_PM_LR11)( &fT0, &fT1, psCY0, psST0->m_sCT.m_sET.m_sPT.m_avPoint[0], psST0->m_sCT.m_sET.m_avEdge[0]);
//
//    bC0 = FCN_F(tgCM_NR0)(fT0);
//    bC1 = FCN_F(tgCM_NR1)(fT0);
//    bTest0 = (bC0 && !FCN_VO(tgGM_ST_Test_Point_0)(psST0)) || (bC1 && !FCN_VO(tgGM_ST_Test_Point_1)(psST0)) || (!bC0 && !bC1 && !FCN_VO(tgGM_ST_Test_Edge_0)(psST0));
//
//    bC0 = FCN_F(tgCM_NR0)(fT1);
//    bC1 = FCN_F(tgCM_NR1)(fT1);
//    bTest1 = (bC0 && !FCN_VO(tgGM_ST_Test_Point_0)(psST0)) || (bC1 && !FCN_VO(tgGM_ST_Test_Point_1)(psST0)) || (!bC0 && !bC1 && !FCN_VO(tgGM_ST_Test_Edge_0)(psST0));
//
//    if (!bTest0)
//    {
//        VEC_T(1,C)      vK0 = FCN_V(tgMH_MUL_SV)(fT0, psST0->m_sCT.m_sET.m_avEdge[0]);
//
//        psCL->m_avPoint[psCL->m_nuiPoint++] = FCN_V(tgMH_ADD)(psST0->m_sCT.m_sET.m_sPT.m_avPoint[0], vK0 );
//    };
//
//    if (!bTest1)
//    {
//        VEC_T(1,C)      vK0 = FCN_V(tgMH_MUL_SV)(fT1, psST0->m_sCT.m_sET.m_avEdge[0]);
//
//        psCL->m_avPoint[psCL->m_nuiPoint++] = FCN_V(tgMH_ADD)(psST0->m_sCT.m_sET.m_sPT.m_avPoint[0], vK0 );
//    };
//
//
//    /* Triangle Edge 1 */
//
//    bRet |= FCN_VO(tgCO_CY_Clip_PM_LR11)( &fT0, &fT1, psCY0, psST0->m_sCT.m_sET.m_sPT.m_avPoint[1], psST0->m_sCT.m_sET.m_avEdge[1]);
//
//    bC0 = FCN_F(tgCM_NR0)(fT0);
//    bC1 = FCN_F(tgCM_NR1)(fT0);
//    bTest0 = (bC0 && !FCN_VO(tgGM_ST_Test_Point_1)(psST0)) || (bC1 && !FCN_VO(tgGM_ST_Test_Point_2)(psST0)) || (!bC0 && !bC1 && !FCN_VO(tgGM_ST_Test_Edge_1)(psST0));
//
//    bC0 = FCN_F(tgCM_NR0)(fT1);
//    bC1 = FCN_F(tgCM_NR1)(fT1);
//    bTest1 = (bC0 && !FCN_VO(tgGM_ST_Test_Point_1)(psST0)) || (bC1 && !FCN_VO(tgGM_ST_Test_Point_2)(psST0)) || (!bC0 && !bC1 && !FCN_VO(tgGM_ST_Test_Edge_1)(psST0));
//
//    if (!bTest0)
//    {
//        VEC_T(1,C)      vK0 = FCN_V(tgMH_MUL_SV)(fT0, psST0->m_sCT.m_sET.m_avEdge[1]);
//
//        psCL->m_avPoint[psCL->m_nuiPoint++] = FCN_V(tgMH_ADD)(psST0->m_sCT.m_sET.m_sPT.m_avPoint[1], vK0 );
//    };
//
//    if (!bTest1)
//    {
//        VEC_T(1,C)      vK0 = FCN_V(tgMH_MUL_SV)(fT1, psST0->m_sCT.m_sET.m_avEdge[1]);
//
//        psCL->m_avPoint[psCL->m_nuiPoint++] = FCN_V(tgMH_ADD)(psST0->m_sCT.m_sET.m_sPT.m_avPoint[1], vK0 );
//    };
//
//
//    /* Triangle Edge 2 */
//
//    bRet |= FCN_VO(tgCO_CY_Clip_PM_LR11)( &fT0, &fT1, psCY0, psST0->m_sCT.m_sET.m_sPT.m_avPoint[2], psST0->m_sCT.m_sET.m_avEdge[2] );
//
//    bC0 = FCN_F(tgCM_NR0)(fT0);
//    bC1 = FCN_F(tgCM_NR1)(fT0);
//    bTest0 = (bC0 && !FCN_VO(tgGM_ST_Test_Point_2)(psST0)) || (bC1 && !FCN_VO(tgGM_ST_Test_Point_0)(psST0)) || (!bC0 && !bC1 && !FCN_VO(tgGM_ST_Test_Edge_2)(psST0));
//
//    bC0 = FCN_F(tgCM_NR0)(fT1);
//    bC1 = FCN_F(tgCM_NR1)(fT1);
//    bTest1 = (bC0 && !FCN_VO(tgGM_ST_Test_Point_2)(psST0)) || (bC1 && !FCN_VO(tgGM_ST_Test_Point_0)(psST0)) || (!bC0 && !bC1 && !FCN_VO(tgGM_ST_Test_Edge_2)(psST0));
//
//    if (!bTest0)
//    {
//        VEC_T(1,C)      vK0 = FCN_V(tgMH_MUL_SV)(fT0, psST0->m_sCT.m_sET.m_avEdge[2]);
//
//        psCL->m_avPoint[psCL->m_nuiPoint++] = FCN_V(tgMH_ADD)(psST0->m_sCT.m_sET.m_sPT.m_avPoint[2], vK0 );
//    };
//
//    if (!bTest1)
//    {
//        VEC_T(1,C)      vK0 = FCN_V(tgMH_MUL_SV)(fT1, psST0->m_sCT.m_sET.m_avEdge[2]);
//
//        psCL->m_avPoint[psCL->m_nuiPoint++] = FCN_V(tgMH_ADD)(psST0->m_sCT.m_sET.m_sPT.m_avPoint[2], vK0 );
//    };
//
//
//    return (bRet);
//}
//
//
///* =============================================================================================================================================================================== */
//
//#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
