///* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
///*  »Project«   Teikitu Gaming System (TgS) (∂)
//    »File«      TgS Collision - Box-Triangle.c
//    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
//    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
///*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
///*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
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
//static TgBOOL
//FCN_VO(tgCO_ST_Penetrate_Axis_Seperation_BX)(
//    VEC_OBJ_T(STg2_CO_Axis_Result,PC), VEC_OBJ_T(TgSTRI,CPC), VEC_OBJ_T(TgBOX,CPC) );
//
//static TgRESULT
//FCN_VO(tgCO_ST_Sweep_Axis_Seperation_BX)(
//    VEC_OBJ_T(STg2_CO_Axis_Info,PC), VAR_T(C), VEC_OBJ_T(TgSTRI,CPC), VEC_OBJ_T(TgBOX,CPC), VEC_OBJ_T(TgDELTA,CPC) );
//
//
//
//
///* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
///*  Public Functions                                                                                                                                                               */
///* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
//
///* ---- FCN_VO(tgCO_ST_Penetrate_BX) --------------------------------------------------------------------------------------------------------------------------------------------- */
///* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
//TgRESULT FCN_VO(tgCO_ST_Penetrate_BX)(VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_OBJ_T(TgSTRI,CPC) psST0, VEC_OBJ_T(TgBOX,CPC) psBX0)
//{
//    VEC_OBJ_T(STg2_CO_Contact,P)        psContact;
//    VEC_OBJ_T(STg2_CO_Axis_Result)      sAxS;
//    TgRESULT                            iResult;
//    VEC_T(1)                            vAX_NM;
//
//    TgRSIZE_C                           nuiContact = psPacket->m_nuiContact;
//    VEC_T(1,C)                          vDS = FCN_V(tgMH_SUB)( psBX0->m_vOrigin, psST0->m_sCT.m_sET.m_sPT.m_avPoint[0] );
//
//    TgPARAM_CHECK( FCN_VO(tgGM_ST_Is_Valid)(psST0) && FCN_VO(tgGM_BX_Is_Valid)(psBX0) );
//
//    if (0 == psPacket->m_nuiMaxContact || psPacket->m_nuiContact >= psPacket->m_nuiMaxContact || nullptr == psPacket->m_psContact)
//    {
//        return (KTgE_FAIL);
//    };
//
//    /*  Quick out logic - for the contact generation routines to be accurate then the box origin is assumed to be outside of the infinite negative projection of the */
//    /* triangle space.  (ie. that it is on the positive half-space of the plane defined by the triangle. */
//
//    if (FCN_V(tgMH_DOT)( psST0->m_sCT.m_sET.m_sPT.m_vNormal, vDS ) < TYPE_K(0))
//    {
//        return (KTgE_NO_INTERSECT);
//    };
//
//    /* Find the minimal axis of separation, or return if the primitives are not in contact. */
//
//    if (!FCN_VO(tgCO_ST_Penetrate_Axis_Seperation_BX)( sAxS, psST0, psBX0))
//    {
//        return (KTgE_NO_INTERSECT);
//    };
//
//    TgERROR( FCN_F(tgCM_NR1)(FCN_V(tgMH_LSQ)( sAxS.m_vNormal)) && sAxS.m_fDepth >= TYPE_K(0) );
//
//    /* == Contact Generation == */
//
//    if (sAxS.m_iAxis == 1 || sAxS.m_iAxis >= 21)
//    {
//        /* -- Triangle Normal or Edge Plane Intersection -- */
//        /*  The minimal separation axis is triangle normal or one of the edge planes. */
//
//        TgSINT_E32_C    iIdx = sAxS.m_iAxis == 1 ? 0 : sAxS.m_iAxis - 21;
//
//        /*  Analyze the valid triangle vertices to see if they are contact points - this is done since contained points are not found by the following algorithm */
//        /* (box edge clipping). */
//
//        VEC_T(1,C)                          vK0 = FCN_V(tgMH_NEG)( (psST0->m_avPlane[iIdx].m_vNormal));
//        VEC_T(1,C)                          vNormal = sAxS.m_iAxis == 1 ? psST0->m_sCT.m_sET.m_sPT.m_vNormal : vK0;
//
//        TgSINT_E32                          iFlag, iAxis;
//
//        for (TgRSIZE uiVert = 0; uiVert < 3; ++uiVert)
//        {
//            VEC_T(1,C)                          vVert = psST0->m_sCT.m_sET.m_sPT.m_avPoint[uiVert];
//            VEC_T(1)                            vT0, vT1, vT, vK1, vK2;
//
//            if (!FCN_VO(tgGM_ST_Test_Point)(psST0, uiVert)) /* Skip reduced features/vertices. */
//            {
//                continue;
//            };
//
//            if (!FCN_VO(tgGM_BX_Is_Contained)(psBX0, vVert )) /* Skip exterior points - edge crossings are handled differently. */
//            {
//                continue;
//            };
//
//            if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
//            {
//                return (KTgE_MAX_CONTACTS);
//            };
//
//            psContact = psPacket->m_psContact + psPacket->m_nuiContact;
//
//            /* Find the point on the box along the negative normal direction. */
//            vK1 = FCN_V(tgMH_NEG)( vNormal );
//            iResult = FCN_VO(tgCO_BX_Clip_PM_LR10)( &vT0, &vT1, psBX0, vVert, vK1 );
//            TgERROR( FCN_F(tgPM_ABS)(fT0) <= VAR_K(KTgEPS) );
//
//            fT = (TgFAILED( iResult ) || fT1 < TYPE_K(0)) ? TYPE_K(0) : fT1;
//
//            vK2 = FCN_V(tgMH_MUL)( vT, vNormal );
//            psContact->m_vS0 = FCN_V(tgMH_SUB)( vVert, vK2 );
//            psContact->m_vN0 = vNormal;
//            psContact->m_vT0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
//            psContact->m_vDepth = vT;
//
//            ++psPacket->m_nuiContact;
//            /*TgDEBUG_COLLISION_TRIANGLE( iDBG_TriID, ETgFEBUG_COLLISION_COLLIDED ); */
//        };
//
//        /*  F_Clip the edges of the box against the triangle space. */
//
//        for (iFlag = 0; iFlag < 8; ++iFlag)
//        {
//            VEC_T(1,C)                          vE0 = 0 != (iFlag & 1) ? psBX0->m_vExtent.x : -psBX0->m_vExtent.x;
//            VEC_T(1,C)                          vE1 = 0 != (iFlag & 2) ? psBX0->m_vExtent.y : -psBX0->m_vExtent.y;
//            VEC_T(1,C)                          vE2 = 0 != (iFlag & 4) ? psBX0->m_vExtent.z : -psBX0->m_vExtent.z;
//            VEC_T(1,C)                          vCS = FCN_VO(tgGM_BX_Calc_Point)(psBX0, fE0, fE1, fE2);
//            VEC_T(1,C)                          vK3 = FCN_V(tgMH_SUB)( vCS, psST0->m_sCT.m_sET.m_sPT.m_avPoint);
//            VEC_T(1,C)                          vDistN = FCN_V(tgMH_DOT)( vK3, &psST0->m_sCT.m_sET.m_sPT.m_vNormal);
//            VAR_T()                             fDist[3];
//
//            if (fDistN >= TYPE_K(0))
//            {
//                /* The point/vertex is above the triangle plane - ignore and continue processing. */
//
//                continue;
//            };
//
//            fDist[0] = FCN_VO(tgCO_PN_Dist_PT)(psST0->m_avPlane + 0, vCS );
//            fDist[1] = FCN_VO(tgCO_PN_Dist_PT)(psST0->m_avPlane + 1, vCS );
//            fDist[2] = FCN_VO(tgCO_PN_Dist_PT)(psST0->m_avPlane + 2, vCS );
//
//            if (fDist[0] >= -VAR_K(KTgEPS) && fDist[1] >= -VAR_K(KTgEPS) && fDist[2] >= -VAR_K(KTgEPS))
//            {
//                /* The vertex is contained inside the negative triangle space - add it as a contact and test next vertex. */
//
//                if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
//                {
//                    return (KTgE_MAX_CONTACTS);
//                };
//
//                psContact = psPacket->m_psContact + psPacket->m_nuiContact;
//
//                psContact->m_vS0 = vCS;
//                psContact->m_vT0 = TYPE_K(0);
//
//                if (sAxS.m_iAxis >= 21)
//                {
//                    VAR_T()                             fT0, fT1;
//                    TgSINT_E32                          iCode = 0;
//
//                    iResult = FCN_VO(tgCO_ST_Clip_PM_F_LR10)( fT0, &fT1, &iCode, psST0, &vCS, vNormal );
//                    TgERROR( FCN_F(tgPM_ABS)(fT0) <= VAR_K(KTgEPS) );
//
//                    psContact->m_vDepth = (TgFAILED( iResult ) || 3 != (iCode & 3) || fT1 < TYPE_K(0)) ? TYPE_K(0) : fT1;
//                }
//                else
//                {
//                    psContact->m_vDepth = -fDistN;
//                };
//
//                psContact->m_vN0 = vNormal;
//                ++psPacket->m_nuiContact;
//                /*TgDEBUG_COLLISION_TRIANGLE( iDBG_TriID, ETgFEBUG_COLLISION_COLLIDED ); */
//
//                continue;
//            };
//
//            /*  The vertex is under the triangle plane but not inside the triangle itself.  Attempt to create contact points where the triangle would clip the box edges. */
//
//            for (iAxis = 0; iAxis < 3; ++iAxis)
//            {
//                VEC_T(1,C)                          vK6 = psST0->m_avPlane[0].m_vNormal;
//                VEC_T(1,C)                          vK1 = psST0->m_avPlane[1].m_vNormal;
//                VEC_T(1,C)                          vK2 = psST0->m_avPlane[2].m_vNormal;
//
//                VEC_T(1,C)                          vBX_EN0 = FCN_V(tgMH_DOT)( vK6, psBX0->m_avAxis + iAxis);
//                VEC_T(1,C)                          vBX_EN1 = FCN_V(tgMH_DOT)( vK1, psBX0->m_avAxis + iAxis);
//                VEC_T(1,C)                          vBX_EN2 = FCN_V(tgMH_DOT)( vK2, psBX0->m_avAxis + iAxis);
//
//                VAR_T()                             fBX_EN[3];
//                VEC_T(1,C)        vS2;
//
//                fBX_EN[0] = 0 == (iFlag & (1 << iAxis)) ? fBX_EN0 : -fBX_EN0;
//                fBX_EN[1] = 0 == (iFlag & (1 << iAxis)) ? fBX_EN1 : -fBX_EN1;
//                fBX_EN[2] = 0 == (iFlag & (1 << iAxis)) ? fBX_EN2 : -fBX_EN2;
//
//                for (TgRSIZE uiEdge = 0; uiEdge < 3; ++uiEdge)
//                {
//                    VAR_T(C)        fInt = -fDist[uiEdge] / fBX_EN[uiEdge];
//                    VEC_T(1,C)                          vK0 = 0 == (iFlag & (1 << iAxis)) ? fInt : -fInt;
//                    VEC_T(1,C)                          vK5 = FCN_V(tgMH_MUL_VS)(psBX0->m_avAxis + iAxis, fK0);
//                    VEC_T(1,C)                          vK4 = FCN_V(tgMH_ADD)( vCS, vK5 );
//                    VEC_T(1,C)                          vK7 = FCN_V(tgMH_SUB)( vS2, psST0->m_sCT.m_sET.m_sPT.m_avPoint);
//                    VEC_T(1,C)                          vDepth = -FCN_V(tgMH_DOT)( vK7, &psST0->m_sCT.m_sET.m_sPT.m_vNormal);
//
//                    if (!FCN_VO(tgGM_ST_Test_Edge)(psST0, uiEdge) || (FCN_F(tgCM_NR0)(FCN_F(tgPM_ABS)(fBX_EN[uiEdge]))))
//                    {
//                        /* Ignore edge planes where the axis is near-parallel, or has been marked as non-valid. */
//                        continue;
//                    };
//
//                    if (fInt < TYPE_K(0) || fInt > TYPE_K(2,0)*psBX0->m_vExtent.m_aData[iAxis])
//                    {
//                        /* The resulting clipping point is outside of legal space. */
//                        continue;
//                    };
//
//                    /* If the resulting point is not contained inside of the negative triangle space - ignore it. */
//
//                    if (fDepth < -VAR_K(KTgEPS))
//                    {
//                        continue;
//                    };
//
//                    vS2 = vK4;
//
//                    if (
//                        (FCN_VO(tgCO_PN_Dist_PT)(psST0->m_avPlane + ((uiEdge + 1) % 3), vS2 )) < -VAR_K(KTgEPS) ||
//                        (FCN_VO(tgCO_PN_Dist_PT)(psST0->m_avPlane + ((uiEdge + 2) % 3), vS2 )) < -VAR_K(KTgEPS)
//                    )
//                    {
//                        continue;
//                    };
//
//                    if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
//                    {
//                        return (KTgE_MAX_CONTACTS);
//                    };
//
//                    psContact = psPacket->m_psContact + psPacket->m_nuiContact;
//
//                    psContact->m_vS0 = vS2;
//                    psContact->m_vN0 = vNormal;
//                    psContact->m_vT0 = TYPE_K(0);
//
//                    if (iIdx >= 0)
//                    {
//                        if ((TgRSIZE)iIdx != uiEdge)
//                        {
//                            VAR_T()                             fT0, fT1;
//                            TgSINT_E32                          iCode = 0;
//
//                            iResult = FCN_VO(tgCO_ST_Clip_PM_F_LR10)( fT0, &fT1, &iCode, psST0, &vS2, vNormal );
//                            TgERROR( FCN_F(tgPM_ABS)(fT0) <= VAR_K(KTgEPS) );
//
//                            psContact->m_vDepth = (TgFAILED( iResult ) || 3 != (iCode & 3) || fT1 < TYPE_K(0)) ? TYPE_K(0) : fT1;
//                        }
//                        else
//                        {
//                            psContact->m_vDepth = TYPE_K(0);
//                        };
//                    }
//                    else
//                    {
//                        psContact->m_vDepth = fDepth < TYPE_K(0) ? TYPE_K(0) : fDepth;
//                    };
//
//                    ++psPacket->m_nuiContact;
//                    /*TgDEBUG_COLLISION_TRIANGLE( iDBG_TriID, ETgFEBUG_COLLISION_COLLIDED ); */
//                };
//            };
//        };
//
//        return (niContact == psPacket->m_nuiContact ? KTgE_NO_INTERSECT : KTgS_OK);
//    };
//
//    if (sAxS.m_iAxis >= 8)
//    {
//        /* -- Edge/Edge Intersection -- */
//        /*   The minimal separation axis is the result of the cross product of both a triangle and box axis. */
//
//        /* Construct the line segments representing the colliding edges. */
//
//        TgSINT_E32_C    iTriIdx = (sAxS.m_iAxis - 8) / 3;
//        TgSINT_E32_C    iBoxIdx0 = (sAxS.m_iAxis - 8) % 3;
//        VEC_T(1,C)        vK6;
//
//        /*  The support point function works in this case because the axis separation routine is known NOT to return back a axis (normal) that is orthogonal to an */
//        /* existing box axis. This ensures the resulting vector is on a box edge. */
//
//        TgSINT_E32_C    iIdx1 = (iBoxIdx0 + 1) % 3;
//        TgSINT_E32_C    iIdx2 = (iBoxIdx0 + 2) % 3;
//        VAR_T(C)        fBX1_N = FCN_V(tgMH_DOT)(psBX0->m_avAxis + iIdx1, &sAxS.m_vNormal);
//        VAR_T(C)        fBX2_N = FCN_V(tgMH_DOT)(psBX0->m_avAxis + iIdx2, &sAxS.m_vNormal);
//
//        VEC_T(1,C)                          vK0 = fBX1_N > TYPE_K(0) ? psBX0->m_vExtent.m_aData[iIdx1] : -psBX0->m_vExtent.m_aData[iIdx1];
//        VEC_T(1,C)                          vK1 = fBX2_N > TYPE_K(0) ? psBX0->m_vExtent.m_aData[iIdx2] : -psBX0->m_vExtent.m_aData[iIdx2];
//        VEC_T(1,C)                          vK2 = TYPE_K(2,0)*psBX0->m_vExtent.m_aData[iBoxIdx0];
//        VEC_T(1,C)                          vK0 = FCN_V(tgMH_MUL)( vK0, psBX0->m_avAxis + iIdx1);
//        VEC_T(1,C)                          vK1 = FCN_V(tgMH_MUL)( vK1, psBX0->m_avAxis + iIdx2);
//        VEC_T(1,C)                          vK2 = FCN_V(tgMH_MUL)( psBX0->m_vExtent.m_aData[iBoxIdx0], psBX0->m_avAxis + iBoxIdx0);
//        VEC_T(1,C)                          vK3 = FCN_V(tgMH_ADD)( vK0, vK1 );
//        VEC_T(1,C)                          vK4 = FCN_V(tgMH_SUB)( psBX0->m_vOrigin, vK2 );
//        VEC_T(1,C)                          vK5 = FCN_V(tgMH_MUL)( vK2, psBX0->m_avAxis + iBoxIdx0);
//
//        VEC_T(1)                            vP0;
//        VAR_T()                             vDistSq, vT0, vT1;
//
//        vP0 = FCN_V(tgMH_ADD)( vK3, vK4 );
//
//        /* Calculate the contact point based on the points of closest proximity between the two edges. */
//        fDistSq = FCN_VO(tgCO_LR11_ClosestSq_PM_LR11)(
//            &fT0, &fT1, &vP0, &vK5, psST0->m_sCT.m_sET.m_sPT.m_avPoint + iTriIdx, psST0->m_sCT.m_sET.m_avEdge + iTriIdx);
//
//        vK6 = FCN_V(tgMH_MUL_SV)(fT0, vK5 );
//
//        psContact = psPacket->m_psContact + psPacket->m_nuiContact;
//
//        psContact->m_vS0 = FCN_V(tgMH_ADD)( vP0, vK6 );
//        psContact->m_vN0 = sAxS.m_vNormal;
//        psContact->m_vT0 = TYPE_K(0);
//        psContact->m_vDepth = FCN_F(tgPM_SQRT)(fDistSq);
//
//        TgERROR( FCN_F(tgCM_NR0)(fDistSq - sAxS.m_fDepth*sAxS.m_fDepth) );
//
//        ++psPacket->m_nuiContact;
//        /*TgDEBUG_COLLISION_TRIANGLE( iDBG_TriID, ETgFEBUG_COLLISION_COLLIDED ); */
//
//        return (KTgS_OK);
//    }
//
//    TgERROR( sAxS.m_iAxis > 1 );
//
//    /* -- Box Axis Intersection */
//    /*  The minimal separation axis is one of the box axes. */
//
//    fAX_NM = FCN_V(tgMH_DOT)( sAxS.m_vNormal, &psST0->m_sCT.m_sET.m_sPT.m_vNormal);
//
//    if (!FCN_F(tgCM_NR0)(fAX_NM))
//    {
//        /*  Analyze the box vertices to see if they are contact points - this is done since contained points are not found by the following algorithm (edge clipping).  */
//        /* Take each box vertex, project it down along the contact normal to see if it intersects the triangle making a contact. */
//
//        TgSINT_E32                          iFlag;
//
//        for (iFlag = 0; iFlag < 8; ++iFlag)
//        {
//            VEC_T(1,C)                          vE0 = 0 != (iFlag & 1) ? psBX0->m_vExtent.x : -psBX0->m_vExtent.x;
//            VEC_T(1,C)                          vE1 = 0 != (iFlag & 2) ? psBX0->m_vExtent.y : -psBX0->m_vExtent.y;
//            VEC_T(1,C)                          vE2 = 0 != (iFlag & 4) ? psBX0->m_vExtent.z : -psBX0->m_vExtent.z;
//            VEC_T(1,C)                          vCS = FCN_VO(tgGM_BX_Calc_Point)(psBX0, fE0, fE1, fE2);
//            VEC_T(1,C)                          vK0 = FCN_V(tgMH_SUB)( vCS, psST0->m_sCT.m_sET.m_sPT.m_avPoint);
//            VEC_T(1,C)                          vDistN = FCN_V(tgMH_DOT)( vK0, &psST0->m_sCT.m_sET.m_sPT.m_vNormal);
//            VEC_T(1,C)                          vDepth = FCN_F(tgPM_ABS)(fDistN / fAX_NM);
//            VEC_T(1,C)                          vK1 = FCN_V(tgMH_MUL_SV)(FCN_F(tgPM_FSEL)(fAX_NM, fDepth, -fDepth), &sAxS.m_vNormal);
//            VEC_T(1,C)                          vP0 = FCN_V(tgMH_ADD)( vCS, vK1 );
//
//            if (fDistN >= TYPE_K(0)) /* The point/vertex is above the triangle plane - ignore and continue processing. */
//            {
//                continue;
//            };
//
//            if (!FCN_VO(tgGM_ST_Is_Contained)(psST0, vP0 ))
//            {
//                continue;
//            };
//
//            if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
//            {
//                return (KTgE_MAX_CONTACTS);
//            };
//
//            psContact = psPacket->m_psContact + psPacket->m_nuiContact;
//
//            psContact->m_vS0 = vCS;
//            psContact->m_vN0 = sAxS.m_vNormal;
//            psContact->m_vT0 = TYPE_K(0);
//            psContact->m_vDepth = fDepth;
//
//            ++psPacket->m_nuiContact;
//            /*TgDEBUG_COLLISION_TRIANGLE( iDBG_TriID, ETgFEBUG_COLLISION_COLLIDED ); */
//        };
//    };
//
//    TgERROR( !FCN_F(tgCM_NR1)(FCN_V(tgMH_DOT)( sAxS.m_vNormal, &psST0->m_sCT.m_sET.m_sPT.m_vNormal)) );
//
//    {
//        /*  Need to use the special version of the clip function so that the cutting face opposite of the resultant contact surface can be disabled so that the correct */
//        /* points on the triangle can be found. */
//
//        VEC_OBJ_T(STg2_CO_Clip_List,PU)     psCL;
//        TgSINT_E32_C    iFlag = ~(1 << (sAxS.m_iAxis - 2));
//        VAR_T(C)        fExtent = psBX0->m_vExtent.m_aData[(sAxS.m_iAxis - 2) % 3];
//        VAR_T()                             fRadSq;
//
//        psCL = TgMALLOC_POOL( sizeof( VEC_OBJ_T(STg2_CO_Clip_List) ) + 8 * sizeof( VEC_T(1) ) );
//        psCL->m_nuiPoint = 0;
//        psCL->m_nuiMax = 8;
//
//        iResult = FCN_VO(tgCO_BXF_Clip_PT)(psCL, psBX0, iFlag, &psST0->m_sCT.m_sET.m_sPT);
//        TgERROR( TgSUCCEEDED( iResult ) );
//
//        fRadSq = psBX0->m_vExtent.x*psBX0->m_vExtent.x;
//        fRadSq += psBX0->m_vExtent.y*psBX0->m_vExtent.y;
//        fRadSq += psBX0->m_vExtent.z*psBX0->m_vExtent.z;
//
//        for (iResult = 0; iResult < psCL->m_nuiPoint; ++iResult)
//        {
//            /*  If the contact point is on an invalid edge and is not a box vertex then cull the point. */
//
//            VEC_T(1,C)                          vRelPoint = FCN_V(tgMH_SUB)( psCL->m_avPoint[iResult], &psBX0->m_vOrigin);
//
//            /* Box vertices are not eligible for culling. */
//
//            if (!FCN_F(tgCM_NR0)(FCN_V(tgMH_LSQ)( vRelPoint ) - fRadSq))
//            {
//                if (!FCN_VO(tgGM_ST_Test_Edge_0)(psST0))
//                {
//                    if (FCN_VO(tgCO_PN_Dist_PT)(psST0->m_avPlane + 0, psCL->m_avPoint + iResult) < psPacket->m_fSnapTol)
//                    {
//                        continue;
//                    };
//                };
//
//                if (!FCN_VO(tgGM_ST_Test_Edge_1)(psST0))
//                {
//                    if (FCN_VO(tgCO_PN_Dist_PT)(psST0->m_avPlane + 1, psCL->m_avPoint + iResult) < psPacket->m_fSnapTol)
//                    {
//                        continue;
//                    };
//                };
//
//                if (!FCN_VO(tgGM_ST_Test_Edge_2)(psST0))
//                {
//                    if (FCN_VO(tgCO_PN_Dist_PT)(psST0->m_avPlane + 2, psCL->m_avPoint + iResult) < psPacket->m_fSnapTol)
//                    {
//                        continue;
//                    };
//                };
//            };
//
//            psContact = psPacket->m_psContact + psPacket->m_nuiContact;
//
//            if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
//            {
//                TgFREE_POOL( psCL );
//                return (KTgE_MAX_CONTACTS);
//            }
//            else
//            {
//                VEC_T(1,C)                          vDepth = fExtent + FCN_V(tgMH_DOT)( vRelPoint, &sAxS.m_vNormal);
//                VEC_T(1,C)                          vK2 = FCN_V(tgMH_MUL_SV)(fDepth, &sAxS.m_vNormal);
//
//                psContact->m_vS0 = FCN_V(tgMH_SUB)(psCL->m_avPoint + iResult, vK2 );
//                psContact->m_vN0 = sAxS.m_vNormal;
//                psContact->m_vT0 = TYPE_K(0);
//                psContact->m_vDepth = fDepth < TYPE_K(0) ? TYPE_K(0) : fDepth;
//
//                ++psPacket->m_nuiContact;
//                /*TgDEBUG_COLLISION_TRIANGLE( iDBG_TriID, ETgFEBUG_COLLISION_COLLIDED ); */
//            };
//        };
//
//        TgFREE_POOL( psCL );
//    };
//
//    return (niContact == psPacket->m_nuiContact ? KTgE_NO_INTERSECT : KTgS_OK);
//}
//
//
///* ---- FCN_VO(tgCO_ST_Sweep_BX) ------------------------------------------------------------------------------------------------------------------------------------------------- */
///* Input:  tgPacket: The current series of contact points for this query-series, and contact generation parameters.                                                                */
///* Input:  fPM: Current normalized time of first contact.                                                                                                                          */
///* Input:  bPenetrate: If the swept primitives are in penetration, if true the function will return points of penetration.                                                         */
///* Input:  psST0: Space Triangle primitive                                                                                                                                         */
///* Input:  psBX0: Box primitive                                                                                                                                                    */
///* Input:  sDT: A structure holding the swept primitive displacement for the entire duration of the test period                                                                    */
///* Output: tgPacket: Contact points are added or replace the current set depending on the time comparison and given parameters                                                     */
///* Output: fPM: New normalized time of first contact                                                                                                                               */
///* Return: Result Code                                                                                                                                                             */
///* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
//TgRESULT FCN_VO(tgCO_ST_Sweep_BX)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VAR_T(P) pfPM, VEC_OBJ_T(TgSTRI,CPC) psST0, VEC_OBJ_T(TgBOX,CPC) psBX0, VEC_OBJ_T(TgDELTA,CPC) psDT )
//{
//    VEC_OBJ_T(STg2_CO_Contact,P)        psContact;;
//    VEC_OBJ_T(STg2_CO_Axis_Project)     sP0, sP1;
//    VEC_OBJ_T(STg2_CO_Axis_Info)        sNFO;
//    TgRESULT                            iResult;
//
//    TgERROR( FCN_VO(tgGM_ST_Is_Valid)(psST0) && FCN_VO(tgGM_BX_Is_Valid)(psBX0) );
//
//    if (0 == psPacket->m_nuiMaxContact || psPacket->m_nuiContact >= psPacket->m_nuiMaxContact || nullptr == psPacket->m_psContact)
//    {
//        return (KTgE_FAIL);
//    };
//
//    /*TgDEBUG_COLLISION_TRIANGLE_CREATEID(iDBG_TriID, tgST1, ETgFEBUG_COLLISION_ENTERFCN); */
//
//    sNFO.m_enSide = ETgCO_AXIS_CONTACT_DIRECTION__UNKNOWN;
//    sNFO.m_fMinT = VAR_K(KTgMAX);
//
//    iResult = FCN_VO(tgCO_ST_Sweep_Axis_Seperation_BX)( sNFO, *pfPM + psPacket->m_fSweepTol, psST0, psBX0, psDT);
//
//    if (TgFAILED( iResult ))
//    {
//        TgERROR( KTgE_NO_INTERSECT == iResult );
//        return (iResult);
//    };
//
//    /* == Contact Generation == */
//
//    TgERROR( (sNFO.m_enSide != ETgCO_AXIS_CONTACT_DIRECTION__UNKNOWN) );
//
//    if (sNFO.m_enSide == ETgCO_AXIS_CONTACT_DIRECTION__PENETRATED || sNFO.m_fMinT < TYPE_K(0))
//    {
//        /* Pre-Penetration. */
//        if (*pfPM > psPacket->m_fSweepTol)
//        {
//            psPacket->m_nuiContact = 0;
//        };
//
//        *pfPM = TYPE_K(0);
//
//        if ((psPacket->m_bReport_Penetration) && (KTgE_MAX_CONTACTS == FCN_VO(tgCO_ST_Penetrate_BX)(psPacket, psST0, psBX0)))
//        {
//            return (KTgE_MAX_CONTACTS);
//        };
//
//        return (KTgE_PREPENETRATION);
//    };
//
//    /* Make sure this contact has not occurred more than tolerance later than the current sweep time. */
//
//    if (sNFO.m_fMinT > *pfPM + psPacket->m_fSweepTol)
//    {
//        return (KTgE_NO_INTERSECT);
//    };
//
//    /* Generate the axis projection information using the returned axis vector - and then choose the pertinent values. */
//
//    FCN_VO(tgCO_PT_Axis_ProjInfo)( &sP0, &sNFO.m_vNormal, &psST0->m_sCT.m_sET.m_sPT );
//    FCN_VO(tgCO_BX_Axis_ProjInfo)( &sP1, &sNFO.m_vNormal, psBX0 );
//
//    {
//        TgBOOL_C        bSide = sNFO.m_enSide == ETgCO_AXIS_CONTACT_DIRECTION__NEGATIVE;
//        VEC_T(1,PC)                       avVert0 = bSide ? sP0.m_avMinVert : sP0.m_avMaxVert;
//        VEC_T(1,PC)                       avVert1 = bSide ? sP1.m_avMaxVert : sP1.m_avMinVert;
//        TgSINT_E32_C    niVertD0 = bSide ? sP0.m_iMinID : sP0.m_iMaxID;
//        TgSINT_E32_C    niVertD1 = bSide ? sP1.m_iMaxID : sP1.m_iMinID;
//        TgSINT_E32_C    iFeatureID = bSide ? sP0.m_iMinID : sP0.m_iMaxID;
//        VEC_T(1,C)                          vK0 = FCN_V(tgMH_NEG)( sNFO.m_vNormal);
//        VEC_T(1,C)                          vNormal = bSide ? vK0 : sNFO.m_vNormal;
//        VEC_T(1,C)                          vOffset = FCN_V(tgMH_MUL_SV)(sNFO.m_fMinT, &psDT->m_vDT);
//
//        /* Based on the axis projection information - generate the appropriate contact for this axis. */
//        if (1 == niVertD0) /* Triangle Vertex in contact with the box. */
//        {
//            /* Check feature reduction on the triangle to make sure the vertex is valid. */
//
//            if (((iFeatureID >= 0) & (iFeatureID <= 2)) && !FCN_VO(tgGM_ST_Test_Point)(psST0, (TgRSIZE)iFeatureID))
//            {
//                return (KTgE_NO_INTERSECT);
//            };
//
//            /* Check to see if result values need to be reset because of the change in intersection time. */
//
//            if (sNFO.m_fMinT < *pfPM - psPacket->m_fSweepTol)
//            {
//                psPacket->m_nuiContact = 0;
//                *pfPM = sNFO.m_fMinT;
//            };
//
//            psContact = psPacket->m_psContact + psPacket->m_nuiContact;
//
//            psContact->m_vS0 = avVert0[0];
//            psContact->m_vN0 = vNormal;
//            psContact->m_vT0 = sNFO.m_fMinT;
//            psContact->m_vDepth = TYPE_K(0);
//
//            ++psPacket->m_nuiContact;
//
//            /*TgDEBUG_COLLISION_TRIANGLE(iDBG_TriID, ETgFEBUG_COLLISION_COLLIDED); */
//            return (KTgS_OK);
//        };
//
//        if (niVertD1 == 1)
//        {
//            /* Box Vertex in contact with the triangle. */
//            if (sNFO.m_fMinT < *pfPM - psPacket->m_fSweepTol)
//            {
//                psPacket->m_nuiContact = 0;
//                *pfPM = sNFO.m_fMinT;
//            };
//
//            psContact = psPacket->m_psContact + psPacket->m_nuiContact;
//
//            psContact->m_vS0 = FCN_V(tgMH_ADD)( vOffset, &avVert1[0]);
//            psContact->m_vN0 = vNormal;
//            psContact->m_vT0 = sNFO.m_fMinT;
//            psContact->m_vDepth = TYPE_K(0);
//
//            ++psPacket->m_nuiContact;
//
//            /*TgDEBUG_COLLISION_TRIANGLE(iDBG_TriID, ETgFEBUG_COLLISION_COLLIDED); */
//            return (KTgS_OK);
//        };
//
//        if (niVertD0 == 2 || niVertD1 == 2) /* Box or Tri Edge Contact */
//        {
//            /* Check feature reduction on the triangle to make sure the edge is valid. */
//
//            VEC_T(1,C)        vRN0 = VEC_K(KTgZERO);
//            VEC_T(1,C)        vRN1 = VEC_K(KTgZERO);
//            VEC_OBJ_T(TgSEGMENT)                sTriE;
//            VAR_T()                             fT0, fT1;
//            VEC_T(1,C)                          vK9 = FCN_V(tgMH_SUB)(avVert0 + 1, avVert0);
//
//            iResult = -1;
//
//            if (((0 != (iFeatureID & 4)) & (niVertD0 == 2)) && !FCN_VO(tgGM_ST_Test_Edge)(psST0, (TgRSIZE)(iFeatureID - 4)))
//            {
//                return (KTgE_NO_INTERSECT);
//            };
//
//            FCN_VO(tgGM_SG_Init)( sTriE, avVert0, vK9 );
//
//            if (niVertD1 == 4) /* Triangle Edge in contact with a Box Face */
//            {
//                VEC_T(1,C)                          vK1 = FCN_V(tgMH_ADD)(avVert1 + 0, vOffset );
//                VEC_T(1,C)                          vK2 = FCN_V(tgMH_SUB)(avVert1 + 1, avVert1);
//                VEC_T(1,C)                          vK3 = FCN_V(tgMH_SUB)(avVert1 + 2, avVert1);
//                VEC_OBJ_T(TgRECTANGLE)              sBoxFace;
//
//                FCN_VO(tgGM_RT_Init_SE)( sBoxFace, &vK1, &vK2, vK3 );
//
//                if (TgSUCCEEDED( FCN_VO(tgCO_RT_Clip_PM_SG)( fT0, &fT1, &sBoxFace, sTriE ) ))
//                {
//                    VEC_T(1,C)                          vK4 = FCN_V(tgMH_MUL_SV)(fT0, &sTriE.m_vDirN);
//                    VEC_T(1,C)                          vK5 = FCN_V(tgMH_MUL_SV)(fT1, &sTriE.m_vDirN);
//                    VEC_T(1,C)                          vK6 = FCN_V(tgMH_ADD)( sTriE.m_vOrigin, vK4 );
//                    VEC_T(1,C)                          vK7 = FCN_V(tgMH_ADD)( sTriE.m_vOrigin, vK5 );
//                    VEC_T(1,C)                          vK8 = FCN_V(tgMH_SUB)( vRN0, vRN1 );
//
//                    vRN0 = vK6;
//                    vRN1 = vK7;
//                    iResult = FCN_V(tgMH_LSQ)( vK8 ) > VAR_K(KTgROOT_EPS) ? 2 : 1;
//                };
//            }
//            else
//            {
//                VEC_T(1,C)                          vK1 = FCN_V(tgMH_SUB)(avVert1 + 1, avVert1);
//                VEC_T(1,C)                          vK2 = FCN_V(tgMH_ADD)( vOffset, avVert1);
//                VEC_OBJ_T(TgSEGMENT)                sBoxE;
//
//                FCN_VO(tgGM_SG_Init)( sBoxE, &vK2, vK1 );
//
//                if (niVertD0 == 2) /* Triangle Edge in contact with a Box Edge */
//                {
//                    iResult = FCN_VO(tgCO_LN_Internal_Intersect_LN)(
//                        &vRN0, &vRN1, &sTriE.m_vOrigin, &sTriE.m_vDirN, &sBoxE.m_vOrigin, &sBoxE.m_vDirN);
//                }
//                else /* Triangle Face in contact with a Box Edge */
//                {
//                    TgSINT_E32                          iCode;
//
//                    iResult = FCN_VO(tgCO_ST_Clip_PM_F_SG)( fT0, &fT1, &iCode, psST0, sBoxE );
//                    TgERROR( TgSUCCEEDED( iResult ) );
//
//                    if (0 == (iCode & 12)) /* Check to see if both points are either invalid or reduced. */
//                    {
//                        return (KTgE_NO_INTERSECT);
//                    }
//                    else
//                    {
//                        VAR_T(C)        fK0 = (0 != (iCode & 4)) ? fT0 : fT1;
//                        VEC_T(1,C)                          vK3 = FCN_V(tgMH_MUL_SV)(fK0, &sBoxE.m_vDirN);
//                        VEC_T(1,C)                          vK4 = FCN_V(tgMH_MUL_SV)(fT1, &sBoxE.m_vDirN);
//                        VEC_T(1,C)                          vK5 = FCN_V(tgMH_ADD)( sBoxE.m_vOrigin, vK3 );
//                        VEC_T(1,C)                          vK6 = FCN_V(tgMH_ADD)( sBoxE.m_vOrigin, vK4 );
//                        VEC_T(1,C)                          vK7 = FCN_V(tgMH_SUB)( vK5, vK6 );
//
//                        vRN0 = vK5;
//                        vRN1 = vK6;
//
//                        iResult = (12 == (iCode & 12)) && FCN_V(tgMH_LSQ)( vK7 ) > VAR_K(KTgROOT_EPS) ? 2 : 1;
//                    };
//                };
//            };
//
//            if (sNFO.m_fMinT < *pfPM - psPacket->m_fSweepTol)
//            {
//                psPacket->m_nuiContact = 0;
//                *pfPM = sNFO.m_fMinT;
//            };
//
//            switch (iResult)
//            {
//                case 2:
//                    psContact = psPacket->m_psContact + psPacket->m_nuiContact;
//
//                    psContact->m_vS0 = vRN1;
//                    psContact->m_vN0 = vNormal;
//                    psContact->m_vT0 = sNFO.m_fMinT;
//                    psContact->m_vDepth = TYPE_K(0);
//
//                    ++psPacket->m_nuiContact;
//
//                case 1:
//                    if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
//                    {
//                        return (KTgE_MAX_CONTACTS);
//                    };
//
//                    psContact = psPacket->m_psContact + psPacket->m_nuiContact;
//
//                    psContact->m_vS0 = vRN0;
//                    psContact->m_vN0 = vNormal;
//                    psContact->m_vT0 = sNFO.m_fMinT;
//                    psContact->m_vDepth = TYPE_K(0);
//
//                    ++psPacket->m_nuiContact;
//                    /*TgDEBUG_COLLISION_TRIANGLE(iDBG_TriID, ETgFEBUG_COLLISION_COLLIDED); */
//
//                    break;
//
//                default:
//                    TgERROR(false);
//            };
//
//            return (iResult > 0 ? KTgS_OK : KTgE_NO_INTERSECT);
//        }
//        else
//        {
//            /* Triangle Face in contact with a Box Face */
//            /* Construct a centroid orientated rectangle definition */
//
//            VEC_T(1,C)                          vE0 = FCN_V(tgMH_SUB)(avVert1 + 1, avVert1 + 0);
//            VEC_T(1,C)                          vE1 = FCN_V(tgMH_SUB)(avVert1 + 2, avVert1 + 0);
//            VAR_T(C)        fE0_E0 = FCN_V(tgMH_LSQ)( vE0 );
//            VAR_T(C)        fE1_E1 = FCN_V(tgMH_LSQ)( vE1 );
//            VEC_T(1,C)                          vS0 = FCN_V(tgMH_ADD)(avVert1 + 0, vOffset );
//
//            TgSINT_E32                          iIdx, iCode, niPoint = 0;
//            VEC_T(1,C)        avContact[12];
//            VAR_T()                             fT0, fT1;
//
//            /*  Analyze the valid triangle vertices to see if they are contact points - this is done since contained points are not found by the following algorithm */
//            /* (box edge clipping). */
//
//            for (TgRSIZE uiVert = 0; uiVert < 3; ++uiVert)
//            {
//                /* Check to see if the triangle point is contained in the box face. */
//
//                VEC_T(1,C)                          vDS = FCN_V(tgMH_SUB)(psST0->m_sCT.m_sET.m_sPT.m_avPoint + uiVert, vS0 );
//                VAR_T(C)        fDS_E0 = FCN_V(tgMH_DOT)( vDS, vE0 );
//                VAR_T(C)        fDS_E1 = FCN_V(tgMH_DOT)( vDS, vE1 );
//
//                if (!FCN_VO(tgGM_ST_Test_Point)(psST0, uiVert))
//                {
//                    if (fDS_E0 < TYPE_K(0) || fDS_E1 < TYPE_K(0) || fDS_E0 > fE0_E0 || fDS_E1 > fE1_E1)
//                    {
//                        continue;
//                    };
//                };
//
//                avContact[niPoint++] = psST0->m_sCT.m_sET.m_sPT.m_avPoint[uiVert];
//            };
//
//            FCN_VO(tgCO_ST_Clip_PM_F_LR11)( fT0, &fT1, &iCode, psST0, &vS0, vE0 );
//            if (0 != (iCode & 4))
//            {
//                VEC_T(1,C)                          vK1 = FCN_V(tgMH_MUL_SV)(fT0, vE0 );
//
//                avContact[niPoint++] = FCN_V(tgMH_ADD)( vS0, vK1 );
//            };
//
//            if (0 != (iCode & 8))
//            {
//                VEC_T(1,C)                          vK1 = FCN_V(tgMH_MUL_SV)(fT1, vE0 );
//
//                avContact[niPoint++] = FCN_V(tgMH_ADD)( vS0, vK1 );
//            };
//
//            FCN_VO(tgCO_ST_Clip_PM_F_LR11)( fT0, &fT1, &iCode, psST0, &vS0, vE1 );
//            if (0 != (iCode & 4))
//            {
//                VEC_T(1,C)                          vK1 = FCN_V(tgMH_MUL_SV)(fT0, vE1 );
//
//                avContact[niPoint++] = FCN_V(tgMH_ADD)( vS0, vK1 );
//            };
//
//            if (0 != (iCode & 8))
//            {
//                VEC_T(1,C)                          vK1 = FCN_V(tgMH_MUL_SV)(fT1, vE1 );
//
//                avContact[niPoint++] = FCN_V(tgMH_ADD)( vS0, vK1 );
//            };
//
//            {
//                VEC_T(1,C)                          vK3 = FCN_V(tgMH_ADD)( vS0, vE1 );
//
//                FCN_VO(tgCO_ST_Clip_PM_F_LR11)( fT0, &fT1, &iCode, psST0, &vK3, vE0 );
//                if (0 != (iCode & 4))
//                {
//                    VEC_T(1,C)                          vK1 = FCN_V(tgMH_MUL_SV)(fT0, vE0 );
//                    VEC_T(1,C)                          vK2 = FCN_V(tgMH_ADD)( vS0, vE1 );
//
//                    avContact[niPoint++] = FCN_V(tgMH_ADD)( vK2, vK1 );
//                };
//
//                if (0 != (iCode & 8))
//                {
//                    VEC_T(1,C)                          vK1 = FCN_V(tgMH_MUL_SV)(fT1, vE0 );
//                    VEC_T(1,C)                          vK2 = FCN_V(tgMH_ADD)( vS0, vE1 );
//
//                    avContact[niPoint++] = FCN_V(tgMH_ADD)( vK2, vK1 );
//                };
//            };
//
//            {
//                VEC_T(1,C)                          vK3 = FCN_V(tgMH_ADD)( vS0, vE0 );
//
//                FCN_VO(tgCO_ST_Clip_PM_F_LR11)( fT0, &fT1, &iCode, psST0, &vK3, vE1 );
//                if (0 != (iCode & 4))
//                {
//                    VEC_T(1,C)                          vK1 = FCN_V(tgMH_MUL_SV)(fT0, vE1 );
//                    VEC_T(1,C)                          vK2 = FCN_V(tgMH_ADD)( vS0, vE0 );
//
//                    avContact[niPoint++] = FCN_V(tgMH_ADD)( vK2, vK1 );
//                };
//
//                if (0 != (iCode & 8))
//                {
//                    VEC_T(1,C)                          vK1 = FCN_V(tgMH_MUL_SV)(fT1, vE1 );
//                    VEC_T(1,C)                          vK2 = FCN_V(tgMH_ADD)( vS0, vE0 );
//
//                    avContact[niPoint++] = FCN_V(tgMH_ADD)( vK2, vK1 );
//                };
//            };
//
//            TgERROR( niPoint > 0 );
//
//            if (sNFO.m_fMinT < *pfPM - psPacket->m_fSweepTol)
//            {
//                psPacket->m_nuiContact = 0;
//                *pfPM = sNFO.m_fMinT;
//            };
//
//            for (iIdx = 0; iIdx < niPoint; ++iIdx)
//            {
//                TgSINT_E32                          iTest;
//
//                for (iTest = 0; iTest < iIdx; ++iTest)
//                {
//                    VEC_T(1,C)                          vK4 = FCN_V(tgMH_SUB)(avContact + iTest, avContact + iIdx);
//
//                    if (!FCN_F(tgCM_NR0)(FCN_V(tgMH_LSQ)( vK4 )))
//                    {
//                        break;
//                    };
//                }
//
//                if (iTest != iIdx)
//                {
//                    continue;
//                };
//
//                if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
//                {
//                    return (KTgE_MAX_CONTACTS);
//                };
//
//                psContact = psPacket->m_psContact + psPacket->m_nuiContact;
//                psContact->m_vS0 = avContact[iIdx];
//                psContact->m_vN0 = vNormal;
//                psContact->m_vT0 = sNFO.m_fMinT;
//                psContact->m_vDepth = TYPE_K(0);
//
//                ++psPacket->m_nuiContact;
//            };
//        };
//    };
//
//    /*TgDEBUG_COLLISION_TRIANGLE(iDBG_TriID, ETgFEBUG_COLLISION_COLLIDED); */
//    return (KTgS_OK);
//}
//
//
//
//
///* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
///*  File Local Functions                                                                                                                                                           */
///* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
//
///* ---- FCN_VO(tgCO_ST_Penetrate_Axis_Seperation_BX) ----------------------------------------------------------------------------------------------------------------------------- */
///* Input:  psST0: Space Triangle primitive                                                                                                                                         */
///* Input:  psBX0: Box primitive                                                                                                                                                    */
///* Output: sAxS: Structure holds the resulting axis separation information necessary to create a contact set.                                                                      */
///* Return: False if a separating axis exists, true otherwise                                                                                                                       */
///* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
//static TgBOOL FCN_VO(tgCO_ST_Penetrate_Axis_Seperation_BX)(VEC_OBJ_T(STg2_CO_Axis_Result,PC) psAxS, VEC_OBJ_T(TgSTRI,CPC) psST0, VEC_OBJ_T(TgBOX,CPC) psBX0)
//{
//    VAR_T()                             fMinBox, fMaxBox, fMinTri, fMaxTri;
//    TgBOOL                              bTriIsCoPlanarToFace = false;
//
//    /* -- Axis: Triangle Normal -- */
//
//    fMinTri = FCN_V(tgMH_DOT)(psST0->m_sCT.m_sET.m_sPT.m_avPoint, &psST0->m_sCT.m_sET.m_sPT.m_vNormal);
//    FCN_VO(tgGM_BX_Project)( fMinBox, &fMaxBox, psBX0, &psST0->m_sCT.m_sET.m_sPT.m_vNormal);
//
//    if (fMaxBox < fMinTri || fMinBox > fMinTri) /* Separation test. */
//    {
//        return (false);
//    };
//
//    psAxS->m_vNormal = psST0->m_sCT.m_sET.m_sPT.m_vNormal;
//    psAxS->m_fDepth = fMinTri - fMinBox;
//    psAxS->m_iAxis = 1;
//
//    /* -- Axis: Box Face/Plane Normals -- */
//
//    for (TgRSIZE uiIndex = 0; uiIndex < 3; ++uiIndex)
//    {
//        VEC_T(1,C)                          vAxis = psBX0->m_avAxis[uiIndex];
//
//        /* Weight the function towards the triangle normal.  In this case ignore any box axis that is "close". */
//
//        if (FCN_F(tgCM_NR1)(FCN_V(tgMH_DOT)( psST0->m_sCT.m_sET.m_sPT.m_vNormal, vAxis )))
//        {
//            /*  Optimization step: Since a box axis is identical to the triangle normal, the remaining two box axes would be coplanar with the triangle.  Thus, the cross */
//            /* product values would all return vectors equivalent to the triangle normal.  The remaining cross-product values would be the edge-plane normals. */
//            bTriIsCoPlanarToFace = true;
//            continue;
//        }
//        else
//        {
//            /* Determine the extents of the primitives along the chosen axis. */
//
//            VAR_T(C)        fBO_AU = FCN_V(tgMH_DOT)( psBX0->m_vOrigin, vAxis );
//
//            FCN_VO(tgGM_ST_Project)( fMinTri, &fMaxTri, psST0, vAxis );
//
//            fMinBox = fBO_AU - psBX0->m_vExtent.m_aData[uiIndex];
//            fMaxBox = fBO_AU + psBX0->m_vExtent.m_aData[uiIndex];
//
//            /* Separation Test. */
//
//            if (fMaxBox < fMinTri || fMinBox > fMaxTri)
//            {
//                return (false);
//            }
//            else
//            {
//                /* Selection of the best (minimal depth) axis. */
//
//                VAR_T(C)        fMinDepth = fMaxBox - fMinTri;
//                VAR_T(C)        fMaxDepth = fMaxTri - fMinBox;
//                TgBOOL_C        bNegAxis = fMinDepth > fMaxDepth;
//
//                if ((bNegAxis ? fMaxDepth : fMinDepth) < psAxS->m_fDepth)
//                {
//                    psAxS->m_vNormal = (bNegAxis) ? vAxis : FCN_V(tgMH_NEG)( &vAxis );
//                    psAxS->m_fDepth = (bNegAxis) ? fMaxDepth : fMinDepth;
//                    psAxS->m_iAxis = (TgSINT_E32 )uiIndex + (bNegAxis ? 5 : 2);
//                };
//            };
//        };
//    };
//
//    /* -- Axis: Axis-Box Cross Product */
//
//    if (!bTriIsCoPlanarToFace)
//    {
//        for (TgRSIZE uiTriIndex = 0; uiTriIndex < 3; ++uiTriIndex)
//        {
//            /* Disregard edges that are indicated as invalid.  This is usually due to feature reduction removing this element. */
//            for (TgRSIZE uiBoxIndex = 0; uiBoxIndex < 3; ++uiBoxIndex)
//            {
//                VAR_T()                             fAxisLen;
//                VEC_T(1,C)        vAxis;
//
//                /* Axis is created by taking the cross product of the triangle edge and a box axis. */
//
//                vAxis = FCN_V(tgMH_UCX_LEN)( fAxisLen, psBX0->m_avAxis + uiBoxIndex, psST0->m_sCT.m_sET.m_avEdge + uiTriIndex);
//
//                if (FCN_F(tgCM_NR0)(fAxisLen)) /* Sanif/Parallel check for the resulting vector. */
//                {
//                    continue;
//                };
//
//                /*  Check to see if the resultant normal is approximately the same as that of the triangle normal. If this is the case skip this axis.  This check is */
//                /* primarily to aid in contact generation, since a resultant in this context implies an edge-edge contact (1-2 point) instead of the more stable cases */
//                /* (3-4 points). */
//
//                if (
//                    FCN_F(tgCM_NR1)(FCN_V(tgMH_DOT)(psBX0->m_avAxis + 0, vAxis )) ||
//                    FCN_F(tgCM_NR1)(FCN_V(tgMH_DOT)(psBX0->m_avAxis + 1, vAxis )) ||
//                    FCN_F(tgCM_NR1)(FCN_V(tgMH_DOT)(psBX0->m_avAxis + 2, vAxis )) ||
//                    FCN_F(tgCM_NR1)(FCN_V(tgMH_DOT)( psST0->m_sCT.m_sET.m_sPT.m_vNormal, vAxis ))
//                )
//                {
//                    continue;
//                };
//
//                /* Determine the extents of the primitives along the chosen axis. */
//
//                FCN_VO(tgGM_ST_Project)( fMinTri, &fMaxTri, psST0, vAxis );
//                FCN_VO(tgGM_BX_Project)( fMinBox, &fMaxBox, psBX0, vAxis );
//
//                /* Separation Test. */
//
//                if (fMaxBox < fMinTri || fMinBox < fMaxTri)
//                {
//                    return (false);
//                };
//
//                if (!FCN_VO(tgGM_ST_Test_Edge)(psST0, uiTriIndex)) /* Feature reduction test - ignore axes associated with reduced edges. */
//                {
//                    continue;
//                }
//                else
//                {
//                    /* Selection of the best (minimal depth) axis. */
//
//                    VAR_T(C)        fMinDepth = fMaxBox - fMinTri;
//                    VAR_T(C)        fMaxDepth = fMaxTri - fMinBox;
//                    TgBOOL_C        bNegAxis = fMinDepth > fMaxDepth;
//
//                    if ((bNegAxis ? fMaxDepth : fMinDepth) < psAxS->m_fDepth)
//                    {
//                        psAxS->m_vNormal = bNegAxis ? vAxis : FCN_V(tgMH_NEG)( vAxis );
//                        psAxS->m_fDepth = bNegAxis ? fMaxDepth : fMinDepth;
//                        psAxS->m_iAxis = (TgSINT_E32)(uiTriIndex * 3 + uiBoxIndex + 8);
//                    };
//                };
//            };
//        };
//    }
//    else
//    {
//        for (TgRSIZE uiTriIndex = 0; uiTriIndex < 3; ++uiTriIndex)
//        {
//            VEC_T(1,C)                          vAxis = psST0->m_avPlane[uiTriIndex].m_vNormal;
//
//            /* Check to see if the resultant normal is approximately the same as that of the triangle normal. If this is the case skip this axis.  This check is primarily*/
//            /* to aid in contact generation, since a resultant in this context implies an edge-edge contact (1-2 point) instead of the more stable cases (3-4 points). */
//
//            if (
//                FCN_F(tgCM_NR1)(FCN_V(tgMH_DOT)(psBX0->m_avAxis + 0, vAxis )) ||
//                FCN_F(tgCM_NR1)(FCN_V(tgMH_DOT)(psBX0->m_avAxis + 1, vAxis )) ||
//                FCN_F(tgCM_NR1)(FCN_V(tgMH_DOT)(psBX0->m_avAxis + 2, vAxis ))
//            )
//            {
//                continue;
//            };
//
//            /* Determine the extents of the primitives along the chosen axis. */
//
//            FCN_VO(tgGM_ST_Project)( fMinTri, &fMaxTri, psST0, vAxis );
//            FCN_VO(tgGM_BX_Project)( fMinBox, &fMaxBox, psBX0, vAxis );
//
//            /* Separation Test. */
//
//            if (fMaxBox < fMinTri || fMinBox < fMaxTri)
//            {
//                return (false);
//            };
//
//            if (!FCN_VO(tgGM_ST_Test_Edge)(psST0, uiTriIndex)) /* Feature reduction test - ignore axes associated with reduced edges. */
//            {
//                continue;
//            }
//            else
//            {
//                /* Selection of the best (minimal depth) axis. */
//
//                VAR_T(C)        fMinDepth = fMaxBox - fMinTri;
//                VAR_T(C)        fMaxDepth = fMaxTri - fMinBox;
//                TgBOOL_C        bNegAxis = fMinDepth > fMaxDepth;
//
//                if ((bNegAxis ? fMaxDepth : fMinDepth) < psAxS->m_fDepth)
//                {
//                    psAxS->m_vNormal = bNegAxis ? vAxis : FCN_V(tgMH_NEG)( vAxis );
//                    psAxS->m_fDepth = bNegAxis ? fMaxDepth : fMinDepth;
//                    psAxS->m_iAxis = (TgSINT_E32)(uiTriIndex + 21);
//                };
//            };
//        };
//    };
//
//    return (true);
//}
//
//
///* ---- FCN_VO(tgCO_ST_Sweep_Axis_Seperation_BX) --------------------------------------------------------------------------------------------------------------------------------- */
///*  Feature reduction removal of reduced edges and their associated directions implemented.                                                                                        */
///* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
//TgRESULT FCN_VO(tgCO_ST_Sweep_Axis_Seperation_BX)( VEC_OBJ_T(STg2_CO_Axis_Info,PC) psNFO, VAR_T(C) fLimitT, VEC_OBJ_T(TgSTRI,CPC) psST0, VEC_OBJ_T(TgBOX,CPC) psBX0, VEC_OBJ_T(TgDELTA,CPC) psDT )
//{
//    VEC_OBJ_T(STg2_CO_Axis_Test)        sAxTest; /* Parameter data output variable */
//    TgSINT_E32                          iResult;
//    VEC_T(1,C)        vAxis;
//
//    VAR_T()                             fSkipT = -VAR_K(KTgMAX); /* T-value for axes associated with reduced features. */
//    TgBOOL                              bTriIsCoPlanarToFace = false;
//
//    VAR_T(C) fS0_NM = FCN_V(tgMH_DOT)(psST0->m_sCT.m_sET.m_sPT.m_avPoint, &psST0->m_sCT.m_sET.m_sPT.m_vNormal);
//
//    sAxTest.m_fLimitT = fLimitT; /* The maximum t-value by which a contact must happen resulting in non-contact. */
//    sAxTest.m_fMinT = -VAR_K(KTgMAX);
//    sAxTest.m_fMaxT = VAR_K(KTgMAX);
//
//    /* -- Axis: Triangle Normal -- */
//
//    sAxTest.m_fMin0 = fS0_NM;
//    sAxTest.m_fMax0 = fS0_NM;
//    FCN_VO(tgGM_BX_Project)( sAxTest.m_fMin1, &sAxTest.m_fMax1, psBX0, &psST0->m_sCT.m_sET.m_sPT.m_vNormal);
//    sAxTest.m_fSpeed = FCN_V(tgMH_DOT)( psDT->m_vDT, &psST0->m_sCT.m_sET.m_sPT.m_vNormal);
//
//    iResult = FCN_VO(tgCO_Test_Seperating_Axis)( sAxTest );
//    switch (iResult)
//    {
//        case 1: /* Update has occurred */
//            psNFO->m_enSide = (sAxTest.m_fMax1 < sAxTest.m_fMin0) ?
//                ETgCO_AXIS_CONTACT_DIRECTION__NEGATIVE : ETgCO_AXIS_CONTACT_DIRECTION__POSITIVE;
//            psNFO->m_vNormal = psST0->m_sCT.m_sET.m_sPT.m_vNormal;
//            psNFO->m_fMinT = sAxTest.m_fMinT;
//        case 0: /* Contact occurred in valid interval, but earlier contact already recorded. */
//            break;
//        case -1: /* No contact occurred during valid interval, thus primitives are separated on this axis. */
//            return (KTgE_NO_INTERSECT);
//    };
//
//    TgERROR( (psNFO->m_enSide != ETgCO_AXIS_CONTACT_DIRECTION__NEGATIVE) ); /* Sanity Check: Box can not contact the triangle back side.; */
//
//    /* -- Axis: Box Face/Plane Normals -- */
//
//    for (TgRSIZE uiIndex = 0; uiIndex < 3; ++uiIndex)
//    {
//        VEC_T(1,C)                          vAxis1 = psBX0->m_avAxis[uiIndex];
//
//        /* Weight the function towards the triangle normal.  In this case ignore any box axis that is "close". */
//
//        if (FCN_F(tgCM_NR1)(FCN_V(tgMH_DOT)( psST0->m_sCT.m_sET.m_sPT.m_vNormal, vAxis1 )))
//        {
//            /*  Optimization step: Since a box axis is identical to the triangle normal, the remaining two box axes would be coplanar with the triangle.  Thus, the cross */
//            /* product values would all return vectors equivalent to the triangle normal.  The remaining cross-product values would be the edge-plane normals. */
//
//            bTriIsCoPlanarToFace = true;
//            continue;
//        }
//        else
//        {
//            VAR_T(C)        fBO_AU = FCN_V(tgMH_DOT)( psBX0->m_vOrigin, vAxis1 );
//
//            FCN_VO(tgGM_ST_Project)( sAxTest.m_fMin0, &sAxTest.m_fMax0, psST0, vAxis1 );
//            sAxTest.m_fMin1 = fBO_AU - psBX0->m_vExtent.m_aData[uiIndex];
//            sAxTest.m_fMax1 = fBO_AU + psBX0->m_vExtent.m_aData[uiIndex];
//            sAxTest.m_fSpeed = FCN_V(tgMH_DOT)( vAxis1, &psDT->m_vDT);
//
//            iResult = FCN_VO(tgCO_Test_Seperating_Axis)( sAxTest );
//            switch (iResult)
//            {
//                case 1: /* Update has occurred */
//                    psNFO->m_enSide = (sAxTest.m_fMax1 < sAxTest.m_fMin0) ? ETgCO_AXIS_CONTACT_DIRECTION__NEGATIVE : ETgCO_AXIS_CONTACT_DIRECTION__POSITIVE;
//                    psNFO->m_vNormal = vAxis1;
//                    psNFO->m_fMinT = sAxTest.m_fMinT;
//                case 0: /* Contact occurred in valid interval, but earlier contact already recorded. */
//                    break;
//                case -1: /* No contact occurred during valid interval, thus primitives are separated on this axis. */
//                    return (KTgE_NO_INTERSECT);
//            };
//        };
//    };
//
//    if (!bTriIsCoPlanarToFace)
//    {
//        for (TgRSIZE uiTriIndex = 0; uiTriIndex < 3; ++uiTriIndex)
//        {
//            /* Disregard edges that are indicated as invalid.  This is usually due to feature reduction removing this element. */
//
//            for (TgRSIZE uiBoxIndex = 0; uiBoxIndex < 3; ++uiBoxIndex)
//            {
//                VAR_T()                             fAxisLen;
//
//                /* Axis is created by taking the cross product of the triangle edge and a box axis. */
//
//                vAxis = FCN_V(tgMH_UCX_LEN)( fAxisLen, psBX0->m_avAxis + uiBoxIndex, psST0->m_sCT.m_sET.m_avEdge + uiTriIndex);
//
//                if (FCN_F(tgCM_NR0)(fAxisLen))
//                {
//                    continue;
//                };
//
//                /* Check to see if the resultant normal is approximately the same as that of the triangle normal. If this is the case skip this axis.  This check is */
//                /* primarily to aid in contact generation, since a resultant in this context implies an edge-edge contact (1-2 point) instead of the more stable cases */
//                /* (3-4 points). */
//
//                if (
//                    FCN_F(tgCM_NR1)(FCN_V(tgMH_DOT)(psBX0->m_avAxis + 0, vAxis )) ||
//                    FCN_F(tgCM_NR1)(FCN_V(tgMH_DOT)(psBX0->m_avAxis + 1, vAxis )) ||
//                    FCN_F(tgCM_NR1)(FCN_V(tgMH_DOT)(psBX0->m_avAxis + 2, vAxis )) ||
//                    FCN_F(tgCM_NR1)(FCN_V(tgMH_DOT)( psST0->m_sCT.m_sET.m_sPT.m_vNormal, vAxis ))
//                )
//                {
//                    continue;
//                };
//
//                /* Perform the separation test. */
//
//                FCN_VO(tgGM_ST_Project)( sAxTest.m_fMin0, &sAxTest.m_fMax0, psST0, vAxis );
//                FCN_VO(tgGM_BX_Project)( sAxTest.m_fMin1, &sAxTest.m_fMax1, psBX0, vAxis );
//                sAxTest.m_fSpeed = FCN_V(tgMH_DOT)( vAxis, &psDT->m_vDT);
//
//                iResult = FCN_VO(tgCO_Test_Seperating_Axis)( sAxTest );
//                switch (iResult)
//                {
//                    case 1: /* Update has occurred */
//                        if (!FCN_VO(tgGM_ST_Test_Edge)(psST0, (TgRSIZE)uiTriIndex))
//                        {
//                            fSkipT = fSkipT > sAxTest.m_fMinT ? fSkipT : sAxTest.m_fMinT;
//                            break;
//                        };
//
//                        psNFO->m_enSide = (sAxTest.m_fMax1 < sAxTest.m_fMin0) ? ETgCO_AXIS_CONTACT_DIRECTION__NEGATIVE : ETgCO_AXIS_CONTACT_DIRECTION__POSITIVE;
//                        psNFO->m_vNormal = vAxis;
//                        psNFO->m_fMinT = sAxTest.m_fMinT;
//
//                    case 0: /* Contact occurred in valid interval, but earlier contact already recorded. */
//                        break;
//                    case -1: /* No contact occurred during valid interval, thus primitives are separated on this axis. */
//                        return (KTgE_NO_INTERSECT);
//                };
//            };
//        };
//    }
//    else
//    {
//        for (TgRSIZE uiTriIndex = 0; uiTriIndex < 3; ++uiTriIndex)
//        {
//            vAxis = psST0->m_avPlane[uiTriIndex].m_vNormal;
//
//            /* Check to see if the resultant normal is approximately the same as that of the triangle normal. If this is the case skip this axis.  This check is primarily*/
//            /* to aid in contact generation, since a resultant in this context implies an edge-edge contact (1-2 point) instead of the more stable cases (3-4 points). */
//
//            if (
//                FCN_F(tgCM_NR1)(FCN_V(tgMH_DOT)(psBX0->m_avAxis + 0, vAxis )) ||
//                FCN_F(tgCM_NR1)(FCN_V(tgMH_DOT)(psBX0->m_avAxis + 1, vAxis )) ||
//                FCN_F(tgCM_NR1)(FCN_V(tgMH_DOT)(psBX0->m_avAxis + 2, vAxis ))
//            )
//            {
//                continue;
//            };
//
//            FCN_VO(tgGM_ST_Project)( sAxTest.m_fMin0, &sAxTest.m_fMax0, psST0, vAxis );
//            FCN_VO(tgGM_BX_Project)( sAxTest.m_fMin1, &sAxTest.m_fMax1, psBX0, vAxis );
//            sAxTest.m_fSpeed = FCN_V(tgMH_DOT)( vAxis, &psDT->m_vDT);
//
//            iResult = FCN_VO(tgCO_Test_Seperating_Axis)( sAxTest );
//            switch (iResult)
//            {
//                case 1: /* Update has occurred */
//                    if (!FCN_VO(tgGM_ST_Test_Edge)(psST0, uiTriIndex))
//                    {
//                        fSkipT = fSkipT > sAxTest.m_fMinT ? fSkipT : sAxTest.m_fMinT;
//                        break;
//                    };
//
//                    psNFO->m_enSide = (sAxTest.m_fMax1 < sAxTest.m_fMin0) ? ETgCO_AXIS_CONTACT_DIRECTION__NEGATIVE : ETgCO_AXIS_CONTACT_DIRECTION__POSITIVE;
//                    psNFO->m_vNormal = vAxis;
//                    psNFO->m_fMinT = sAxTest.m_fMinT;
//                case 0: /* Contact occurred in valid interval, but earlier contact already recorded. */
//                    break;
//                case -1: /* No contact occurred during valid interval, thus primitives are separated on this axis. */
//                    return (KTgE_NO_INTERSECT);
//            };
//        };
//    };
//
//    for (TgRSIZE uiBoxIndex = 0; uiBoxIndex < 3; ++uiBoxIndex)
//    {
//        VAR_T()                             fAxisLen;
//
//        /* Axis is created by taking the cross product of the triangle edge and a box axis. */
//
//        vAxis = FCN_V(tgMH_UCX_LEN)( fAxisLen, &psDT->m_vDT, psBX0->m_avAxis + uiBoxIndex);
//
//        if (FCN_F(tgCM_NR0)(fAxisLen))
//        {
//            continue;
//        };
//
//        /* Check to see if the resultant normal is approximately the same as that of the triangle normal. If this is the case skip this axis.  This check is primarily to */
//        /* aid in contact generation, since a resultant in this context implies an edge-edge contact (1-2 point) instead of the more stable cases (3-4 points). */
//
//        if (
//            FCN_F(tgCM_NR1)(FCN_V(tgMH_DOT)(psBX0->m_avAxis + 0, vAxis )) ||
//            FCN_F(tgCM_NR1)(FCN_V(tgMH_DOT)(psBX0->m_avAxis + 1, vAxis )) ||
//            FCN_F(tgCM_NR1)(FCN_V(tgMH_DOT)(psBX0->m_avAxis + 2, vAxis )) ||
//            FCN_F(tgCM_NR1)(FCN_V(tgMH_DOT)( psST0->m_sCT.m_sET.m_sPT.m_vNormal, vAxis ))
//        )
//        {
//            continue;
//        };
//
//        /* Perform the separation test. */
//
//        FCN_VO(tgGM_ST_Project)( sAxTest.m_fMin0, &sAxTest.m_fMax0, psST0, vAxis );
//        FCN_VO(tgGM_BX_Project)( sAxTest.m_fMin1, &sAxTest.m_fMax1, psBX0, vAxis );
//        sAxTest.m_fSpeed = FCN_V(tgMH_DOT)( vAxis, &psDT->m_vDT);
//
//        iResult = FCN_VO(tgCO_Test_Seperating_Axis)( sAxTest );
//        switch (iResult)
//        {
//            case 1: /* Update has occurred */
//                psNFO->m_enSide = (sAxTest.m_fMax1 < sAxTest.m_fMin0) ? ETgCO_AXIS_CONTACT_DIRECTION__NEGATIVE : ETgCO_AXIS_CONTACT_DIRECTION__POSITIVE;
//                psNFO->m_vNormal = vAxis;
//                psNFO->m_fMinT = sAxTest.m_fMinT;
//            case 0: /* Contact occurred in valid interval, but earlier contact already recorded. */
//                break;
//            case -1: /* No contact occurred during valid interval, thus primitives are separated on this axis. */
//                return (KTgE_NO_INTERSECT);
//        };
//    };
//
//    /*  In certain cases, because of feature reduction, the time of contact for an axis is not updated into the return data structure.  If this axis happens to be the */
//    /* determining direction for the separation, then contact does not occur.  Specifically, since the return data structure has an earlier time stamp for the contact */
//    /* between the triangle and the box, its known that the missing axis represents a separation between the triangle and the box. */
//
//    if (fSkipT >= sAxTest.m_fMinT)
//    {
//        return (KTgE_NO_INTERSECT);
//    };
//
//    return (KTgS_OK);
//}
//
//
///* =============================================================================================================================================================================== */
//
//#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
