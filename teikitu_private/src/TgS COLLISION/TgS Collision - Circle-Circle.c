///* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
///*  »Project«   Teikitu Gaming System (TgS) (∂)
//    »File«      TgS Collision - Circle-Circle.c
//    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
//    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
///*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
///*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
//    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
//    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
///* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
///*  Algorithm taken from paper at: http://jgt.akpeters.com/papers/Vranek02/                                                                                                        */
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
//TgTYPE_STRUCT( VEC_OBJ_T(STg2_EqN_CI_CI), )
//{
//    VAR_T()                                     fCF0, fCF1, fCF2, fCF3, fCF4, fCF5, fCF6, fCF7, fCF8, fCF9;
//    TgBOOL                                      bCoaxial, bSymmetric;
//#if 0 != STRUCT_PAD(2,6)
//    TgUINT_E08                                  m_iPad1[STRUCT_PAD(2,6)];
//#endif
//};
//
//static TgVOID
//FCN_VO(tgCO_CI_Init_EqN_CI)(
//    VEC_OBJ_T(STg2_EqN_CI_CI,PC), VEC_OBJ_T(TgCIRCLE,CPC), VEC_OBJ_T(TgCIRCLE,CPC));
//
//static VAR_T()
//FCN_VO(tgCO_CI_Calc_Angle_EqN_CI)(
//    TgVOID_PC, VAR_T(C), VAR_T(C), VAR_T(C) );
//
//static VAR_T()
//FCN_VO(tgCO_CI_Solve2_EqN_CI)(
//    TgVOID_PC, VAR_T(C), VAR_T(C) );
//
//static VAR_T()
//FCN_VO(tgCO_CI_Solve1_EqN_CI)(
//    TgVOID_PC, VAR_T(C) );
//
//static VAR_T()
//FCN_VO(tgCO_CI_Solve_Diff1_EqN_CI)(
//    TgVOID_PC, VAR_T(C) );
//
//static VAR_T()
//FCN_VO(tgCO_CI_Solve_Diff2_EqN_CI)(
//    TgVOID_PC, VAR_T(C) );
//
//
//
//
///* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
///*  Public Functions                                                                                                                                                               */
///* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
//
///* ---- FCN_VO(tgCO_CI_ClosestSq_PM_CI) ------------------------------------------------------------------------------------------------------------------------------------------ */
///* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
//VEC_T(1) FCN_VO(tgCO_CI_ClosestSq_PM_CI)( VEC_T(1,PC) pvTB, VEC_OBJ_T(TgCIRCLE,CPC) psCI0, VEC_OBJ_T(TgCIRCLE,CPC) psCI1 )
//{
//    VEC_OBJ_T(STg2_EqN_CI_CI)           sEqN;
//    VAR_T()                             fMinDist, fTB = VAR_K(KTgMAX);
//
//    TgERROR( FCN_VO(tgGM_CI_Is_Valid)(psCI0) && FCN_VO(tgGM_CI_Is_Valid)(psCI1) );
//    FCN_VO(tgCO_CI_Init_EqN_CI)( &sEqN, psCI0, psCI1 );
//
//    /* Return if coaxial */
//    if (sEqN.bCoaxial)
//    {
//        *pvTB = FCN_V(tgMH_SET1)( TYPE_K(0) );
//        return (FCN_V(tgMH_SET1)( FCN_VO(tgCO_CI_Solve1_EqN_CI)( &sEqN, TYPE_K(0) ) ));
//    }
//    else
//    {
//        /* Create the bracketing triplet */
//
//        VAR_T()                             fX0 = -VAR_K(KTgTWO_PI)*VAR_K(KTgTHIRD);
//        VAR_T()                             fX1 = sEqN.bSymmetric ? -TYPE_K(0,5) : TYPE_K(0);
//        VAR_T()                             fX2 = sEqN.bSymmetric ? TYPE_K(1) : VAR_K(KTgTWO_PI)*VAR_K(KTgTHIRD);
//
//        VAR_T()                             fF0 = FCN_VO(tgCO_CI_Solve1_EqN_CI)( &sEqN, fX0);
//        VAR_T()                             fF1 = FCN_VO(tgCO_CI_Solve1_EqN_CI)( &sEqN, fX1);
//        VAR_T()                             fF2 = FCN_VO(tgCO_CI_Solve1_EqN_CI)( &sEqN, fX2);
//
//        TgSINT_E32                          i;
//
//        i = (fF0 > fF1) && (fF1 < fF2) ? 0 : ((fF1 > fF2) && (fF2 < fF0) ? 1 : ((fF2 > fF0) && (fF0 < fF1) ? 2 : 3));
//
//        if (i > 2) /* Two or more of the function values must be equivalent - process further. */
//        {
//            VAR_T(C)        fA = FCN_F(tgPM_FSEL)(-FCN_F(tgPM_ABS)(fF0 - fF2), fX1, fX0);
//            VAR_T(C)        fC = FCN_F(tgPM_FSEL)(-FCN_F(tgPM_ABS)(fF0 - fF2), fX2, fX2);
//            VAR_T(C)        fFA = FCN_F(tgPM_FSEL)(-FCN_F(tgPM_ABS)(fF0 - fF2), fF1, fF0);
//            VAR_T(C)        fFB = FCN_F(tgPM_FSEL)(-FCN_F(tgPM_ABS)(fF0 - fF2), fF2, fF2);
//
//            TgSINT_E32_C    N = 10;
//            TgSINT_E32                          j = 0;
//
//            for (; j < N; j++)
//            {
//                VAR_T(C)        fB = -VAR_K(KTgPI) + TYPE_K(2,0)*(j + 1)*VAR_K(KTgPI) / (N + 1);
//                VAR_T(C)        fFC = FCN_VO(tgCO_CI_Solve1_EqN_CI)( &sEqN, fB);
//
//                if ((fFA == fFC) || (fFB == fFC))
//                {
//                    continue;
//                };
//
//                fX0 = FCN_F(tgPM_FSEL)(fA - fB, fB, fA);
//                fX1 = FCN_F(tgPM_FSEL)(fA - fB, fA, FCN_F(tgPM_FSEL)(fB - fC, fC, fB));
//                fX2 = FCN_F(tgPM_FSEL)(fA - fB, fC, FCN_F(tgPM_FSEL)(fB - fC, fB, fC));
//
//                fF0 = FCN_F(tgPM_FSEL)(fA - fB, fFC, fFA);
//                fF1 = FCN_F(tgPM_FSEL)(fA - fB, fFA, FCN_F(tgPM_FSEL)(fB - fC, fFB, fFC));
//                fF2 = FCN_F(tgPM_FSEL)(fA - fB, fFB, FCN_F(tgPM_FSEL)(fB - fC, fFC, fFB));
//
//                i = (fF0 > fF1) && (fF1 < fF2) ? 0 : ((fF1 > fF2) && (fF2 < fF0) ? 1 : ((fF2 > fF0) && (fF0 < fF1) ? 2 : 3));
//
//                break;
//            };
//
//            if (j >= N) /* Failure to create solvable conditions */
//            {
//                TgERROR(false);
//                return (FCN_V(tgMH_SET1)( -VAR_K(KTgMAX) ));
//            };
//        }
//
//        /* Find the first minimum */
//
//        switch (i)
//        {
//            case 0: FCN_F(tgMH_BrentD)( &fTB, &fMinDist, &sEqN, FCN_VO(tgCO_CI_Solve1_EqN_CI), FCN_VO(tgCO_CI_Solve_Diff1_EqN_CI), fX0, fX1, fX2); break;
//            case 1: FCN_F(tgMH_BrentD)( &fTB, &fMinDist, &sEqN, FCN_VO(tgCO_CI_Solve1_EqN_CI), FCN_VO(tgCO_CI_Solve_Diff1_EqN_CI), fX1, fX2, fX0); break;
//            case 2: FCN_F(tgMH_BrentD)( &fTB, &fMinDist, &sEqN, FCN_VO(tgCO_CI_Solve1_EqN_CI), FCN_VO(tgCO_CI_Solve_Diff1_EqN_CI), fX2, fX0, fX1); break;
//            default:
//                TgS_NO_DEFAULT(break);
//        };
//
//        /* Polish up the root */
//
//        fTB -= FCN_VO(tgCO_CI_Solve_Diff1_EqN_CI)( &sEqN, fTB) / FCN_VO(tgCO_CI_Solve_Diff2_EqN_CI)( &sEqN, fTB);
//        fMinDist = FCN_VO(tgCO_CI_Solve1_EqN_CI)( &sEqN, fTB);
//
//        /* In the case of the symmetric distance function the minimum has been already found */
//        /* The circles are in touch and their distance is 0 */
//
//        if (sEqN.bSymmetric || FCN_F(tgPM_ABS)(fMinDist) <= VAR_K(KTgROOT_EPS))
//        {
//            *pvTB = FCN_V(tgMH_SET1)( fTB );
//            return (FCN_V(tgMH_SET1)( fMinDist ));
//        }
//        else
//        {
//            /* Set up coefficients of a polynomial p4 */
//
//            VAR_T(C)                            fA0 = sEqN.fCF7 - fMinDist;
//            VAR_T(C)                            fA1 = sEqN.fCF8*sEqN.fCF8;
//            VAR_T(C)                            fA2 = sEqN.fCF6*sEqN.fCF6;
//
//            VAR_T(C)                            fC1 = TYPE_K(2,0)*fA0*sEqN.fCF8 - fA2*sEqN.fCF2;
//            VAR_T(C)                            fC3 = fA0*fA0 - fA2*sEqN.fCF0 + fA1 - fA2*sEqN.fCF4;
//            VAR_T(C)                            fC4 = TYPE_K(2,0)*fA0*sEqN.fCF9 - fA2*sEqN.fCF3;
//            VAR_T(C)                            fC5 = TYPE_K(2,0)*sEqN.fCF9*sEqN.fCF8 - fA2*sEqN.fCF1;
//            VAR_T(C)                            fC6 = fA2*sEqN.fCF4 - fA1 + sEqN.fCF9*sEqN.fCF9 - fA2*sEqN.fCF5;
//
//            VAR_T(C)                            fP4 = fC6*fC6 + fC5*fC5;
//            VAR_T(C)                            fP3 = TYPE_K(2,0)*fC1*fC5 + TYPE_K(2,0)*fC4*fC6;
//            VAR_T()                             fCos;
//
//            /* Return in the case of the coefficient p4[4] = 0 */
//            if (FCN_F(tgPM_ABS)(fP4) < VAR_K(KTgROOT_EPS))
//            {
//                *pvTB = FCN_V(tgMH_SET1)( fTB );
//                return (FCN_V(tgMH_SET1)( fMinDist ));
//            }
//
//            fTB = FCN_F(tgPM_FSEL)(fTB - VAR_K(KTgPI), fTB - VAR_K(KTgTWO_PI), fTB);
//
//            /* Deflate polynomial p4->p2 */
//            fCos = FCN_F(tgPM_COS)(fTB);
//
//            {
//                VAR_T(C)                            fCF0 = fC1*fC1 - fC5*fC5 + TYPE_K(2,0)*fC3*fC6 + fC4*fC4 + 3 * fP4*fCos*fCos + TYPE_K(2,0)*fP3*fCos;
//                VAR_T(C)                            fCF1 = fP3 + TYPE_K(2,0)*fP4*fCos;
//                VAR_T()                             afRoot[2];
//                TgSINT_E32                          niRoot;
//
//                if (
//                      !FCN_F(tgMH_Calc_Root_2)(afRoot, &niRoot, fCF0, fCF1, fP4)
//                    || FCN_F(tgPM_ABS)(afRoot[0]) > TYPE_K(1)
//                    || FCN_F(tgPM_ABS)(afRoot[1]) > TYPE_K(1))
//                {
//                    *pvTB = FCN_V(tgMH_SET1)( fTB );
//                    return (FCN_V(tgMH_SET1)( fMinDist ));
//                }
//                else
//                {
//                    /* Calculate the new bracketing pair */
//
//                    VAR_T(C)                            fH1 = FCN_VO(tgCO_CI_Calc_Angle_EqN_CI)( &sEqN, afRoot[0], fMinDist, fTB);
//                    VAR_T(C)                            fH2 = FCN_VO(tgCO_CI_Calc_Angle_EqN_CI)( &sEqN, afRoot[1], fMinDist, fTB);
//                    VAR_T(C)                            fC01 = FCN_F(tgPM_FSEL)(fH1 - fH2, fH2, fH1);
//                    VAR_T(C)                            fC02 = FCN_F(tgPM_FSEL)(fH1 - fH2, fH1, fH2);
//                    VAR_T()                             fLT, fLocalMin;
//
//                    /* Return in the case of double root */
//                    if (FCN_F(tgPM_ABS)(fH1 - fH2) <= VAR_K(KTgROOT_EPS))
//                    {
//                        *pvTB = FCN_V(tgMH_SET1)( fTB );
//                        return (FCN_V(tgMH_SET1)( fMinDist ));
//                    };
//
//                    /* Find the global minimum */
//                    if ((fC01 < fTB) && (fTB < fC02))
//                    {
//                        FCN_F(tgMH_BrentZ)( &fLT, &sEqN, FCN_VO(tgCO_CI_Solve_Diff1_EqN_CI), fC02, fC01 + VAR_K(KTgTWO_PI));
//                    }
//                    else
//                    {
//                        FCN_F(tgMH_BrentZ)( &fLT, &sEqN, FCN_VO(tgCO_CI_Solve_Diff1_EqN_CI), fC01, fC02);
//                    };
//
//                    fLT -= FCN_VO(tgCO_CI_Solve_Diff1_EqN_CI)( &sEqN, fLT) / FCN_VO(tgCO_CI_Solve_Diff2_EqN_CI)( &sEqN, fLT);
//
//                    fLocalMin = FCN_VO(tgCO_CI_Solve1_EqN_CI)( &sEqN, fLT);
//
//                    if (fLocalMin < fMinDist)
//                    {
//                        fTB = fLT;
//                        fMinDist = fLocalMin;
//                    }
//
//                    *pvTB = FCN_V(tgMH_SET1)( fTB );
//                    return (FCN_V(tgMH_SET1)( fMinDist ));
//                };
//            };
//        };
//    };
//}
//
//
///* ---- FCN_VO(tgCO_CI_Intersect2D_CI) ------------------------------------------------------------------------------------------------------------------------------------------- */
///* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
//TgRESULT FCN_VO(tgCO_CI_Intersect2D_CI)(VEC_T(1,PC) pvR0, VEC_T(1,PC) pvR1, VEC_OBJ_T(TgCIRCLE,CPC) psCI0, VEC_OBJ_T(TgCIRCLE,CPC) psCI1)
//{
//    /* The intersection routine requires that the circles be in parallel planes and that the normal direction is not important to the calculation.  Specifically it will  */
//    /* return points of intersection between the two circles as if the second circle was projected down onto the plane of the first circle. */
//
//    if (!FCN_F(tgCM_NR1)(FCN_V(tgMH_DOT)( psCI0->m_vNormal, &psCI1->m_vNormal)))
//    {
//        TgWARN_CO("Intersection between circles is only valid if co-planar.\n" );
//        return (KTgE_FAIL);
//    }
//    else
//    {
//        VEC_T(1,C)      vDS = FCN_V(tgMH_SUB)( psCI1->m_vOrigin, &psCI0->m_vOrigin);
//        VAR_T(C)        fDS_N = FCN_V(tgMH_DOT)( vDS, &psCI0->m_vNormal);
//        VEC_T(1,C)      vL0 = FCN_V(tgMH_MUL_SV)(fDS_N, &psCI0->m_vNormal);
//        VEC_T(1,C)        vU = FCN_V(tgMH_SUB)( vDS, vL0 );
//        VAR_T(C)        fU = FCN_V(tgMH_LEN)( vU );
//
//        VAR_T(C)        fABS_RS = FCN_F(tgPM_ABS)(psCI0->m_fRadius + psCI1->m_fRadius);
//        VAR_T(C)        fABS_RD = FCN_F(tgPM_ABS)(psCI0->m_fRadius - psCI1->m_fRadius);
//
//        if (fABS_RD >= fU || fABS_RS <= fU)
//        {
//            return (KTgE_NO_INTERSECT);
//        }
//        else
//        {
//            VAR_T(C)        fU_U0 = FCN_V(tgMH_DOT)( vU, &psCI0->m_vU);
//            VAR_T(C)        fU_V0 = FCN_V(tgMH_DOT)( vU, &psCI0->m_vV);
//            VEC_T(1,C)      vK0 = FCN_V(tgMH_MUL_SV)(fU_V0, &psCI0->m_vU);
//            VEC_T(1,C)      vK1 = FCN_V(tgMH_MUL_SV)(fU_U0, &psCI0->m_vV);
//            VEC_T(1,C)      vV = FCN_V(tgMH_SUB)( vK0, vK1 );
//            VAR_T(C)        fM0 = TYPE_K(1) / (fU*fU);
//            VAR_T(C)        fRSQD = psCI0->m_fRadiusSq - psCI1->m_fRadiusSq;
//            VAR_T(C)        fT0 = TYPE_K(0,5)*(TYPE_K(1) + fRSQD*fM0);
//            VAR_T(C)        fT1 = FCN_F(tgPM_SQRT)(psCI0->m_fRadiusSq*fM0 - fT0*fT0);
//            VEC_T(1,C)      vK4 = FCN_V(tgMH_MUL_SV)(fT1, vV );
//            VEC_T(1,C)      vK5 = FCN_V(tgMH_MUL_SV)(fT1, vV );
//            VEC_T(1,C)      vK6 = FCN_V(tgMH_MUL_SV)(fT0, vU );
//            VEC_T(1,C)      vK7 = FCN_V(tgMH_MUL_SV)(fT0, vU );
//            VEC_T(1,C)      vK2 = FCN_V(tgMH_ADD)( vK6, vK4 );
//            VEC_T(1,C)      vK3 = FCN_V(tgMH_SUB)( vK7, vK5 );
//
//            *pvR0 = FCN_V(tgMH_ADD)( psCI0->m_vOrigin, vK2 );
//            *pvR1 = FCN_V(tgMH_ADD)( psCI0->m_vOrigin, vK3 );
//
//            return (KTgS_OK);
//        };
//    };
//}
//
//
///* ---- FCN_VO(tgCO_CI_ClosestSq_CI) --------------------------------------------------------------------------------------------------------------------------------------------- */
///* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
//TgINLINE VEC_T(1) FCN_VO(tgCO_CI_ClosestSq_CI)( VEC_T(1,PC) pvCI0, VEC_T(1,PC) pvCI1, VEC_OBJ_T(TgCIRCLE,CPC) psCI0, VEC_OBJ_T(TgCIRCLE,CPC) psCI1 )
//{
//    VEC_T(1)                            vA0, vN0, vA2, vC0;
//    VAR_T()                             fCos, fSin;
//    VEC_UN_T(1)                         uU0;
//
//    VEC_T(1,C)      vDistSq = FCN_VO(tgCO_CI_ClosestSq_PM_CI)( &VEC_UN_1_MEMBER(uU0), psCI0, psCI1 );
//
//    FCN_F(tgPM_SINCOS)( &fCos, &fSin, VEC_S_UN_1_MEMBER(uU0).x );
//    FCN_V(tgMH_Query_Reference_Frame,3)( &vA0, &vN0, &vA2, &vC0, &psCI0->m_mReference_Frame );
//
//    VEC_T(1,C)      vX0 = FCN_V(tgMH_MUL)( FCN_V(tgMH_SET1)( fCos ), vA0 );
//    VEC_T(1,C)      vX1 = FCN_V(tgMH_MAD)( FCN_V(tgMH_SET1)( fSin ), vA2, vX0 );
//    VEC_T(1,C)      vP1 = FCN_V(tgMH_MAD)( FCN_V(tgMH_SET1)( psCI1->m_fRadius ), vX1, vC0 );
//
//    VEC_T(1,C)      vDS = FCN_V(tgMH_SUB)( vP1, vC0 );
//    VEC_T(1,C)      vDS_N = FCN_V(tgMH_DOT)( vDS, vN0 );
//    VEC_T(1,C)      vX2 = FCN_V(tgMH_MUL)( vDS_N, vN0 );
//    VEC_T(1,C)      vX3 = FCN_V(tgMH_SUB)( vDS, vX2 );
//    VEC_T(1,C)      vRS = FCN_V(tgMH_NORM)( vX3 );
//
//    VEC_T(1,C)      vCMP_0 = FCN_V(tgMH_CMP_GE)( vDistSq, FCN_V(tgMH_SET1)( TYPE_K(0) ) );
//
//    *pvCI0 = FCN_V(tgMH_MAD)( FCN_V(tgMH_SET1)( psCI1->m_fRadius ), vRS, vC0 );
//    *pvCI1 = vP1;
//
//    return (FCN_V(tgMH_SQRT)( vDistSq ));
//}
//
//
//
//
//
///* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
///*  File Local Functions                                                                                                                                                           */
///* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
//
///* ---- FCN_VO(tgCO_CI_Init_EqN_CI) ---------------------------------------------------------------------------------------------------------------------------------------------- */
///* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
//static TgVOID FCN_VO(tgCO_CI_Init_EqN_CI)(VEC_OBJ_T(STg2_EqN_CI_CI,PC) psEQN, VEC_OBJ_T(TgCIRCLE,CPC) psCI0, VEC_OBJ_T(TgCIRCLE,CPC) psCI1)
//{
//    /* Prepare calculation of coefficients */
//
//    VEC_T(1,C)      vDS = FCN_V(tgMH_SUB)( psCI1->m_vOrigin, &psCI0->m_vOrigin);
//    VAR_T(C)        fDS_DS = FCN_V(tgMH_LSQ)( vDS );
//
//    VAR_T(C)        fI0_U1 = FCN_V(tgMH_DOT)( psCI0->m_vOrigin, &psCI1->m_vU);
//    VAR_T(C)        fI0_V1 = FCN_V(tgMH_DOT)( psCI0->m_vOrigin, &psCI1->m_vV);
//    VAR_T(C)        fI1_U1 = FCN_V(tgMH_DOT)( psCI1->m_vOrigin, &psCI1->m_vU);
//    VAR_T(C)        fI1_V1 = FCN_V(tgMH_DOT)( psCI1->m_vOrigin, &psCI1->m_vV);
//
//    VAR_T(C)        fN0_U1 = FCN_V(tgMH_DOT)( psCI0->m_vNormal, &psCI1->m_vU);
//    VAR_T(C)        fN0_V1 = FCN_V(tgMH_DOT)( psCI0->m_vNormal, &psCI1->m_vV);
//    VAR_T(C)        fN0_I0 = FCN_V(tgMH_DOT)( psCI0->m_vNormal, &psCI0->m_vOrigin);
//    VAR_T(C)        fN0_I1 = FCN_V(tgMH_DOT)( psCI0->m_vNormal, &psCI1->m_vOrigin);
//
//    VAR_T(C)        fDiff = fN0_I1 - fN0_I0;
//
//    /* Calculate coefficients of the trigonometric function */
//
//    psEQN->fCF0 = psCI1->m_fRadiusSq + fDS_DS - fDiff*fDiff;
//    psEQN->fCF1 = -psCI1->m_fRadiusSq*fN0_U1*fN0_V1*TYPE_K(2,0);
//    psEQN->fCF2 = psCI1->m_fRadius*TYPE_K(2,0)*(fI1_V1 - fI0_V1 - fDiff*fN0_V1);
//    psEQN->fCF3 = psCI1->m_fRadius*TYPE_K(2,0)*(fI1_U1 - fI0_U1 - fDiff*fN0_U1);
//    psEQN->fCF4 = -psCI1->m_fRadiusSq*fN0_V1*fN0_V1;
//    psEQN->fCF5 = -psCI1->m_fRadiusSq*fN0_U1*fN0_U1;
//    psEQN->fCF6 = -psCI0->m_fRadius*TYPE_K(2,0);
//    psEQN->fCF7 = psCI1->m_fRadiusSq + psCI0->m_fRadiusSq + fDS_DS;
//    psEQN->fCF8 = psCI1->m_fRadius*TYPE_K(2,0)*(fI1_V1 - fI0_V1);
//    psEQN->fCF9 = psCI1->m_fRadius*TYPE_K(2,0)*(fI1_U1 - fI0_U1);
//
//    /* Eliminate a case of coaxial circles */
//
//    psEQN->bCoaxial = FCN_F(tgCM_NR0)(fI1_U1 - fI0_U1) && FCN_F(tgCM_NR0)(fI1_V1 - fI0_V1) && FCN_F(tgCM_NR0)(fN0_U1) && FCN_F(tgCM_NR0)(fN0_V1);
//
//    /* Eliminate a case of a symmetric distance function */
//
//    psEQN->bSymmetric = FCN_F(tgCM_NR0)(psEQN->fCF8) && FCN_F(tgCM_NR0)(psEQN->fCF4) && FCN_F(tgCM_NR0)(psEQN->fCF1);
//}
//
//
///* ---- FCN_VO(tgCO_CI_Calc_Angle_EqN_CI) ---------------------------------------------------------------------------------------------------------------------------------------- */
///* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
//static VAR_T() FCN_VO(tgCO_CI_Calc_Angle_EqN_CI)(TgVOID_PC psEQN, VAR_T(C) fCos, VAR_T(C) fOffset, VAR_T(C) fAngOrig)
//{
//    VAR_T(C)        fSin = FCN_F(tgPM_SQRT)(TYPE_K(1) - fCos*fCos);
//    VAR_T(C)        fVal1 = FCN_VO(tgCO_CI_Solve2_EqN_CI)(((VEC_OBJ_T(STg2_EqN_CI_CI,PC))(psEQN)), fSin, fCos) - fOffset;
//    VAR_T(C)        fVal2 = FCN_VO(tgCO_CI_Solve2_EqN_CI)(((VEC_OBJ_T(STg2_EqN_CI_CI,PC))(psEQN)), -fSin, fCos) - fOffset;
//    VAR_T(C)        fAng = FCN_F(tgPM_ACOS)(fCos);
//
//    if (TYPE_K(0,01)*FCN_F(tgPM_ABS)(fVal1) < VAR_K(KTgROOT_EPS) && TYPE_K(0,01)*FCN_F(tgPM_ABS)(fVal2) < VAR_K(KTgROOT_EPS))
//    {
//        return (-fAngOrig);
//    };
//
//    return (FCN_F(tgPM_FSEL)(FCN_F(tgPM_ABS)(fVal1) - FCN_F(tgPM_ABS)(fVal2), -fAng, fAng));
//}
//
//
///* ---- FCN_VO(tgCO_CI_Solve2_EqN_CI) -------------------------------------------------------------------------------------------------------------------------------------------- */
///* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
//static VAR_T() FCN_VO(tgCO_CI_Solve2_EqN_CI)(TgVOID_PC psEQN, VAR_T(C) fSin, VAR_T(C) fCos)
//{
//    return (
//          ((VEC_OBJ_T(STg2_EqN_CI_CI,PC))(psEQN))->fCF9*fCos
//        + ((VEC_OBJ_T(STg2_EqN_CI_CI,PC))(psEQN))->fCF8*fSin
//        + ((VEC_OBJ_T(STg2_EqN_CI_CI,PC))(psEQN))->fCF7
//        + ((VEC_OBJ_T(STg2_EqN_CI_CI,PC))(psEQN))->fCF6*FCN_F(tgPM_SQRT)
//            (
//                ((VEC_OBJ_T(STg2_EqN_CI_CI,PC))(psEQN))->fCF5*fCos*fCos
//                + ((VEC_OBJ_T(STg2_EqN_CI_CI,PC))(psEQN))->fCF4*fSin*fSin
//                + ((VEC_OBJ_T(STg2_EqN_CI_CI,PC))(psEQN))->fCF3*fCos
//                + ((VEC_OBJ_T(STg2_EqN_CI_CI,PC))(psEQN))->fCF2*fSin
//                + ((VEC_OBJ_T(STg2_EqN_CI_CI,PC))(psEQN))->fCF1*fSin*fCos
//                + ((VEC_OBJ_T(STg2_EqN_CI_CI,PC))(psEQN))->fCF0
//                )
//    );
//}
//
//
///* ---- FCN_VO(tgCO_CI_Solve1_EqN_CI) -------------------------------------------------------------------------------------------------------------------------------------------- */
///* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
//static VAR_T() FCN_VO(tgCO_CI_Solve1_EqN_CI)(TgVOID_PC psEQN, VAR_T(C) fT0)
//{
//    VAR_T()                             fSin, fCos;
//
//    FCN_F(tgPM_SINCOS)( fSin, &fCos, fT0);
//    return (FCN_VO(tgCO_CI_Solve2_EqN_CI)(((VEC_OBJ_T(STg2_EqN_CI_CI,PC))(psEQN)), fSin, fCos));
//}
//
//
///* ---- FCN_VO(tgCO_CI_Solve_Diff1_EqN_CI) --------------------------------------------------------------------------------------------------------------------------------------- */
///* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
//static VAR_T() FCN_VO(tgCO_CI_Solve_Diff1_EqN_CI)(TgVOID_PC psEQN, VAR_T(C) fT0)
//{
//    VAR_T()                             fSin, fCos;
//
//    FCN_F(tgPM_SINCOS)( fSin, &fCos, fT0);
//
//    return (
//          ((VEC_OBJ_T(STg2_EqN_CI_CI,PC))(psEQN))->fCF8*fCos
//        - ((VEC_OBJ_T(STg2_EqN_CI_CI,PC))(psEQN))->fCF9*fSin
//        + ((VEC_OBJ_T(STg2_EqN_CI_CI,PC))(psEQN))->fCF6
//        / FCN_F(tgPM_SQRT)(
//            ((VEC_OBJ_T(STg2_EqN_CI_CI,PC))(psEQN))->fCF5*fCos*fCos
//            + ((VEC_OBJ_T(STg2_EqN_CI_CI,PC))(psEQN))->fCF3*fCos
//            + ((VEC_OBJ_T(STg2_EqN_CI_CI,PC))(psEQN))->fCF4*fSin*fSin
//            + ((VEC_OBJ_T(STg2_EqN_CI_CI,PC))(psEQN))->fCF2*fSin
//            + ((VEC_OBJ_T(STg2_EqN_CI_CI,PC))(psEQN))->fCF1*fSin*fCos
//            + ((VEC_OBJ_T(STg2_EqN_CI_CI,PC))(psEQN))->fCF0
//            )
//        *
//        (
//            ((VEC_OBJ_T(STg2_EqN_CI_CI,PC))(psEQN))->fCF5*fCos*fSin*TYPE_K(-2,0)
//            - ((VEC_OBJ_T(STg2_EqN_CI_CI,PC))(psEQN))->fCF3*fSin
//            + ((VEC_OBJ_T(STg2_EqN_CI_CI,PC))(psEQN))->fCF4*fSin*fCos*TYPE_K(2,0)
//            + ((VEC_OBJ_T(STg2_EqN_CI_CI,PC))(psEQN))->fCF2*fCos
//            + ((VEC_OBJ_T(STg2_EqN_CI_CI,PC))(psEQN))->fCF1*fCos*fCos
//            - ((VEC_OBJ_T(STg2_EqN_CI_CI,PC))(psEQN))->fCF1*fSin*fSin
//            )
//        / TYPE_K(2,0)
//    );
//}
//
//
///* ---- FCN_VO(tgCO_CI_Solve_Diff2_EqN_CI) --------------------------------------------------------------------------------------------------------------------------------------- */
///* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
//static VAR_T() FCN_VO(tgCO_CI_Solve_Diff2_EqN_CI)(TgVOID_PC psEQN, VAR_T(C) fT0)
//{
//    VAR_T()                             fSin, fCos;
//
//    FCN_F(tgPM_SINCOS)( fSin, &fCos, fT0);
//
//    {
//        VAR_T(C)        t6 = ((VEC_OBJ_T(STg2_EqN_CI_CI,PC))(psEQN))->fCF5*fCos*fCos;
//        VAR_T(C)        t7 = ((VEC_OBJ_T(STg2_EqN_CI_CI,PC))(psEQN))->fCF3*fCos;
//        VAR_T(C)        t9 = ((VEC_OBJ_T(STg2_EqN_CI_CI,PC))(psEQN))->fCF4*fSin*fSin;
//        VAR_T(C)        t10 = ((VEC_OBJ_T(STg2_EqN_CI_CI,PC))(psEQN))->fCF2*fSin;
//        VAR_T(C)        t12 = ((VEC_OBJ_T(STg2_EqN_CI_CI,PC))(psEQN))->fCF1*fSin*fCos;
//        VAR_T(C)        t13 = t6 + t7 + t9 + t10 + t12 + ((VEC_OBJ_T(STg2_EqN_CI_CI,PC))(psEQN))->fCF0;
//        VAR_T(C)        t14 = FCN_F(tgPM_SQRT)(t13);
//        VAR_T(C)        fT15 = -TYPE_K(2,0)*((VEC_OBJ_T(STg2_EqN_CI_CI,PC))(psEQN))->fCF5*fCos*fSin
//                                                 - ((VEC_OBJ_T(STg2_EqN_CI_CI,PC))(psEQN))->fCF3*fSin
//                                                 + TYPE_K(2,0)*((VEC_OBJ_T(STg2_EqN_CI_CI,PC))(psEQN))->fCF4*fSin*fCos
//                                                 + ((VEC_OBJ_T(STg2_EqN_CI_CI,PC))(psEQN))->fCF2*fCos
//                                                 + ((VEC_OBJ_T(STg2_EqN_CI_CI,PC))(psEQN))->fCF1*fCos*fCos
//                                                 - ((VEC_OBJ_T(STg2_EqN_CI_CI,PC))(psEQN))->fCF1*fSin*fSin;
//
//        return (
//            TYPE_K(2,0)*((VEC_OBJ_T(STg2_EqN_CI_CI,PC))(psEQN))->fCF4*fCos*fCos
//            - ((VEC_OBJ_T(STg2_EqN_CI_CI,PC))(psEQN))->fCF9*fCos
//            - ((VEC_OBJ_T(STg2_EqN_CI_CI,PC))(psEQN))->fCF8*fSin
//            - ((VEC_OBJ_T(STg2_EqN_CI_CI,PC))(psEQN))->fCF6 / t14 / t13*fT15*fT15 / TYPE_K(4,0)
//            + ((VEC_OBJ_T(STg2_EqN_CI_CI,PC))(psEQN))->fCF6 / t14*(TYPE_K(2,0)*((VEC_OBJ_T(STg2_EqN_CI_CI,PC))(psEQN))->fCF5*fSin*fSin
//            - TYPE_K(2,0)*t6 - t7 - TYPE_K(2,0)*t9 - t10 - TYPE_K(4,0)*t12) / TYPE_K(2,0)
//        );
//    };
//}
//
//
///* =============================================================================================================================================================================== */
//
//#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
