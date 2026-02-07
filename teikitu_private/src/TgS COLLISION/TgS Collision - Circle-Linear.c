///* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
///*  »Project«   Teikitu Gaming System (TgS) (∂)
//    »File«      TgS Collision - Circle-Linear.c
//    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
//    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
///*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
///*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
//    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
//    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
///* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
///*  Algorithm taken from paper at: http://jgt.akpeters.com/papers/Vranek02/                                                                                                        */
///* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
//
//#if !defined (ENABLE_RELOAD_GUARD_LINEAR)
//    #define ENABLE_RELOAD_GUARD_LINEAR
//
//    #define LN_CAP_0 0
//    #define LN_CAP_1 0
//        #define VI(A) FCN_VO(A##00)
//        #include __FILE__
//        #undef VI
//    #undef LN_CAP_0
//    #undef LN_CAP_1
//
//    #define LN_CAP_0 1
//    #define LN_CAP_1 0
//        #define VI(A) FCN_VO(A##10)
//        #include __FILE__
//        #undef VI
//    #undef LN_CAP_0
//    #undef LN_CAP_1
//
//    #define LN_CAP_0 1
//    #define LN_CAP_1 1
//        #define VI(A) FCN_VO(A##11)
//        #include __FILE__
//        #undef VI
//    #undef LN_CAP_0
//    #undef LN_CAP_1
//
//    #undef ENABLE_RELOAD_GUARD_LINEAR
//
///*# !defined (ENABLE_RELOAD_GUARD_LINEAR) */
//#else
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
//TgTYPE_STRUCT( VI(STg2_EqN_CI_LR), )
//{
//    VAR_T()                             fCF0, fCF1, fCF2, fCF3, fCF4, fCF5, fCF6;
//};
//
//static TgVOID                               VI(tgCO_CI_Init_EqN_LR)( VI(STg2_EqN_CI_LR) * const, VEC_T(1,C), VAR_T(C), VEC_T(1,C), VEC_T(1,C), VEC_T(1,C) );
//static VAR_T()                              VI(tgCO_CI_Solve_EqN_LR)( TgVOID_PC, VAR_T(C) );
//static VAR_T()                              VI(tgCO_CI_Solve_Diff1_EqN_LR)( TgVOID_PC, VAR_T(C) );
//static VAR_T()                              VI(tgCO_CI_Solve_Diff2_EqN_LR)( TgVOID_PC, VAR_T(C) );
//
//
//
//
///* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
///*  Public Functions                                                                                                                                                               */
///* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
//
///* ---- VI(tgCO_CI_ClosestSq_PM_LR) ------------------------------------------------------------------------------------------------------------------------------------------------ */
///* Input:  vCIS0: Origin of the circle (and the point on the plane).                                                                                                               */
///* Input:  vCIN0: Normal to the plane containing the circle.                                                                                                                       */
///* Input:  fRadius: Radius of the circle                                                                                                                                           */
///* Input:  vS0,vD0: Origin and Direction for the Linear.                                                                                                                           */
///* Output: vCI0: Point of closest proximity on the circle.                                                                                                                         */
///* Output: tyLN0: Parametric parameter to generate point of minimal distance #1 based on the linear.                                                                               */
///* Return: Minimal distance between the two primitives or negative type max if they intersect or are invalid.                                                                      */
///* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
//VAR_T() VI(tgCO_CI_ClosestSq_PM_LR)(VEC_T(1,PC) pvCI0, VAR_T(P) pfLN0, VEC_OBJ_T(TgCIRCLE,CPC) psCI0, VEC_T(1,C) vS0, VEC_T(1,C) vD0)
//{
//    VEC_T(1,C)      vDS = FCN_V(tgMH_SUB)(pvS0, &psCI0->m_vOrigin);
//    VAR_T(C)        fDS_DS = FCN_V(tgMH_LSQ)( vDS );
//    VAR_T(C)        fD0_D0 = FCN_V(tgMH_LSQ)(vD0);
//    VAR_T(C)        fMid = -FCN_V(tgMH_DOT)(vD0, vDS ) / fD0_D0;
//    VAR_T(C)        fMinT = fMid - psCI0->m_fRadius;
//    VAR_T(C)        fMaxT = fMid + psCI0->m_fRadius;
//
//    VI(STg2_EqN_CI_LR)                  sEqN;
//    VAR_T()                             fT0;
//    VAR_T()                             fT1, fT2, fMinDistSq;
//
//    if (TgEXPECT_FALSE( fDS_DS <= VAR_K(KTgEPS) ))
//    {
//        return (fDS_DS); /* Quick Out - the point is within tolerance of circle origin. */
//    };
//
//    VI(tgCO_CI_Init_EqN_LR)( sEqN, &psCI0->m_vNormal, psCI0->m_fRadius, &vDS, pvS0, vD0);
//
//    if (!FCN_F(tgMH_BrentZ)( fT0, &sEqN, VI(tgCO_CI_Solve_Diff1_EqN_LR), fMinT, fMaxT))
//    {
//        return (-VAR_K(KTgMAX));
//    };
//
//    fT0 -= VI(tgCO_CI_Solve_Diff1_EqN_LR)( sEqN, fT0) / VI(tgCO_CI_Solve_Diff2_EqN_LR)( sEqN, fT0);
//
//
//    if (VI(tgCO_CI_Solve_Diff2_EqN_LR)( sEqN, fT0) < TYPE_K(0))
//    {
//        if (
//            (!FCN_F(tgMH_BrentZ)( fT1, &sEqN, VI(tgCO_CI_Solve_Diff1_EqN_LR), fMinT, fT0 - VAR_K(KTgROOT_EPS))) ||
//            (!FCN_F(tgMH_BrentZ)( fT2, &sEqN, VI(tgCO_CI_Solve_Diff1_EqN_LR), fT0 + VAR_K(KTgROOT_EPS), fMaxT))
//        )
//        {
//            return (-VAR_K(KTgMAX));
//        }
//        else
//        {
//            VAR_T(C)        fMin1 = VI(tgCO_CI_Solve_EqN_LR)( sEqN, fT1);
//            VAR_T(C)        fMin2 = VI(tgCO_CI_Solve_EqN_LR)( sEqN, fT2);
//
//            fT0 = FCN_F(tgPM_FSEL)(fMin2 - fMin1, fT1, fT2);
//            fMinDistSq = FCN_F(tgPM_FSEL)(fMin2 - fMin1, fMin1, fMin2);
//        };
//    }
//    else
//    {
//        /* Compute coefficients of a polynomial */
//
//        fMinDistSq = VI(tgCO_CI_Solve_EqN_LR)( sEqN, fT0);
//
//        {
//            VAR_T(C)        fPT3 = TYPE_K(2,0)*sEqN.fCF5*sEqN.fCF6;
//            VAR_T(C)        fPT4 = sEqN.fCF6*sEqN.fCF6;
//
//            /* Return in the case of the coefficient */
//
//            if (FCN_F(tgPM_ABS)(fPT4) > VAR_K(KTgROOT_EPS))
//            {
//                VAR_T(C)        fCF1 = fPT3 + TYPE_K(2,0)*fPT4*fT0;
//                VAR_T(C)        fCF2 = TYPE_K(2,0)*sEqN.fCF6*(sEqN.fCF4 - fMinDistSq)
//                    + TYPE_K(2,0)*fPT3*fT0
//                    + TYPE_K(3,0)*fPT4*fT0*fT0
//                    - sEqN.fCF3*sEqN.fCF3*sEqN.fCF2
//                    + sEqN.fCF5*sEqN.fCF5;
//                VAR_T()                             afRoot[2];
//                TgSINT_E32                          niRoot;
//
//                if (FCN_F(tgMH_Calc_Root_2)(afRoot, &niRoot, fPT4, fCF1, fCF2))
//                {
//                    fT1 = FCN_F(tgPM_FSEL)(afRoot[0] - afRoot[1], afRoot[1], afRoot[0]);
//                    fT2 = FCN_F(tgPM_FSEL)(afRoot[0] - afRoot[1], afRoot[0], afRoot[1]);
//
//                    /* Find the global minimum */
//                    FCN_F(tgMH_BrentZ)( fT0, &sEqN, VI(tgCO_CI_Solve_Diff1_EqN_LR), fT1, fT2);
//                    fMinDistSq = VI(tgCO_CI_Solve_EqN_LR)( sEqN, fT0);
//                };
//            };
//        };
//    };
//
//    if (LN_CAP_1)
//    {
//        VEC_T(1,C)      vK1 = FCN_V(tgMH_ADD)(pvS0, vD0);
//        VAR_T(C)        fDistSq = FCN_VO(tgCO_CI_DistSq_PT)(psCI0, vK1 );
//
//        if (fDistSq < fMinDistSq || fT0 > TYPE_K(1))
//        {
//            fMinDistSq = fDistSq;
//            fT0 = TYPE_K(1);
//        };
//    };
//
//    if (LN_CAP_0)
//    {
//        VAR_T(C)        fDistSq = FCN_VO(tgCO_CI_DistSq_PT)(psCI0, pvS0);
//
//        if (fDistSq < fMinDistSq || fT0 < TYPE_K(0))
//        {
//            fMinDistSq = fDistSq;
//            fT0 = TYPE_K(0);
//        };
//    };
//
//    *pfLN0 = fT0;
//
//    {
//        VEC_T(1,C)      vK1 = FCN_V(tgMH_MUL_SV)(fT0, vD0);
//        VEC_T(1,C)      vT0 = FCN_V(tgMH_ADD)( vDS, vK1 );
//        VEC_T(1,C)      vK0 = FCN_V(tgMH_MUL_SV_S)(FCN_V(tgMH_DOT)( vT0, &psCI0->m_vNormal), &psCI0->m_vNormal);
//        VEC_T(1,C)      vK2 = FCN_V(tgMH_SUB)( vT0, vK0 );
//        VEC_T(1,C)      vD1 = FCN_V(tgMH_NORM)( vK2 );
//        VEC_T(1,C)      vK3 = FCN_V(tgMH_MUL_SV)(psCI0->m_fRadius, vD1 );
//
//        *pvCI0 = FCN_V(tgMH_ADD)( vT0, vK3 );
//
//        return (fMinDistSq);
//    };
//}
//
//
//
//
///* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
///*  File Local Functions                                                                                                                                                           */
///* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
//
///* ---- VI(tgCO_CI_Init_EqN_LR) ----------------------------------------------------------------------------------------------------------------------------------------------- */
///* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
//static TgVOID VI(tgCO_CI_Init_EqN_LR)(
//    VI(STg2_EqN_CI_LR) * const psEQN, VEC_T(1,C) vNormal, VAR_T(C) fRadius, VEC_T(1,C) vDS, VEC_T(1,C) pvS0, VEC_T(1,C) vD0)
//{
//    VAR_T(C)        fN_D0 = FCN_V(tgMH_DOT)(pvNormal, vD0);
//    VAR_T(C)        fN_DS = FCN_V(tgMH_DOT)(pvNormal, pvDS);
//    VAR_T(C)        fDS_DS = FCN_V(tgMH_LSQ)(pvDS);
//    VEC_T(1,C)      vK0 = FCN_V(tgMH_MUL_SV)(fN_D0, pvNormal);
//    VEC_T(1,C)      vK1 = FCN_V(tgMH_MUL_SV)(fN_DS, pvNormal);
//    VEC_T(1,C)      vT0 = FCN_V(tgMH_SUB)(vD0, vK0 );
//    VEC_T(1,C)      vT1 = FCN_V(tgMH_SUB)(pvDS, vK1 );
//
//    psEQN->fCF0 = FCN_V(tgMH_LSQ)( vT1 );
//    psEQN->fCF1 = TYPE_K(2,0)*FCN_V(tgMH_DOT)( vT0, vT1 );
//    psEQN->fCF2 = FCN_V(tgMH_LSQ)( vT0 );
//    psEQN->fCF3 = -TYPE_K(2,0)*fRadius;
//    psEQN->fCF4 = fDS_DS + fRadius*fRadius;
//    psEQN->fCF5 = TYPE_K(2,0)*FCN_V(tgMH_DOT)(pvDS, vD0);
//    psEQN->fCF6 = FCN_V(tgMH_LSQ)(vD0);
//}
//
//
///* ---- VI(tgCO_CI_Solve_EqN_LR) ---------------------------------------------------------------------------------------------------------------------------------------------- */
///* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
//static VAR_T() VI(tgCO_CI_Solve_EqN_LR)(TgVOID_PC psEQN, VAR_T(C) fT0)
//{
//    return (
//        ((VI(STg2_EqN_CI_LR)*)(psEQN))->fCF6*fT0*fT0 +
//        ((VI(STg2_EqN_CI_LR)*)(psEQN))->fCF5*fT0 +
//        ((VI(STg2_EqN_CI_LR)*)(psEQN))->fCF4 +
//        ((VI(STg2_EqN_CI_LR)*)(psEQN))->fCF3*FCN_F(tgPM_SQRT)
//            (
//                ((VI(STg2_EqN_CI_LR)*)(psEQN))->fCF2*fT0*fT0
//                + ((VI(STg2_EqN_CI_LR)*)(psEQN))->fCF1*fT0
//                + ((VI(STg2_EqN_CI_LR)*)(psEQN))->fCF0
//                )
//    );
//}
//
//
///* ---- VI(tgCO_CI_Solve_Diff1_EqN_LR) ---------------------------------------------------------------------------------------------------------------------------------------- */
///* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
//static VAR_T() VI(tgCO_CI_Solve_Diff1_EqN_LR)(TgVOID_PC psEQN, VAR_T(C) fT0)
//{
//    return (
//          ((VI(STg2_EqN_CI_LR)*)(psEQN))->fCF6*fT0*TYPE_K(2,0)
//        + ((VI(STg2_EqN_CI_LR)*)(psEQN))->fCF5
//        +
//        (
//            ((VI(STg2_EqN_CI_LR)*)(psEQN))->fCF3
//            * (((VI(STg2_EqN_CI_LR)*)(psEQN))->fCF2*fT0*TYPE_K(2,0) + ((VI(STg2_EqN_CI_LR)*)(psEQN))->fCF1)
//            )
//        /
//        (
//            TYPE_K(2,0)*FCN_F(tgPM_SQRT)
//            (
//                ((VI(STg2_EqN_CI_LR)*)(psEQN))->fCF2*fT0*fT0
//                + ((VI(STg2_EqN_CI_LR)*)(psEQN))->fCF1*fT0
//                + ((VI(STg2_EqN_CI_LR)*)(psEQN))->fCF0
//                )
//            )
//    );
//}
//
//
///* ---- VI(tgCO_CI_Solve_Diff2_EqN_LR) ---------------------------------------------------------------------------------------------------------------------------------------- */
///* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
//static VAR_T() VI(tgCO_CI_Solve_Diff2_EqN_LR)(TgVOID_PC psEQN, VAR_T(C) fT0)
//{
//    VAR_T(C)        fX4 = ((VI(STg2_EqN_CI_LR)*)(psEQN))->fCF2*fT0*fT0
//                                            + ((VI(STg2_EqN_CI_LR)*)(psEQN))->fCF1*fT0
//                                            + ((VI(STg2_EqN_CI_LR)*)(psEQN))->fCF0;
//    VAR_T(C)        fX5 = FCN_F(tgPM_SQRT)(fX4);
//    VAR_T(C)        fX1 = ((VI(STg2_EqN_CI_LR)*)(psEQN))->fCF2*fT0*TYPE_K(2,0)
//                                            + ((VI(STg2_EqN_CI_LR)*)(psEQN))->fCF1;
//
//    return
//        (
//              ((VI(STg2_EqN_CI_LR)*)(psEQN))->fCF6*TYPE_K(2,0)
//            - ((VI(STg2_EqN_CI_LR)*)(psEQN))->fCF3 / fX5 / fX4*fX1*fX1 / 4
//            + ((VI(STg2_EqN_CI_LR)*)(psEQN))->fCF3 / fX5*((VI(STg2_EqN_CI_LR)*)(psEQN))->fCF2
//        );
//}
//
//
///* =============================================================================================================================================================================== */
//
//#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
//
///*# !defined (ENABLE_RELOAD_GUARD_LINEAR) */
//#endif
