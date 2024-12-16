///* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
///*  »Project«   Teikitu Gaming System (TgS) (∂)
//    »File«      TgS Collision - Cylinder-Capsule.c
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
//static TgBOOL                               FCN_VO(tgCO_CP_Axis_Seperation_CY)( VEC_OBJ_T(STg2_CO_Axis_Result,PC), VEC_OBJ_T(TgTUBE,CPC), VEC_OBJ_T(TgTUBE,CPC) );
//static TgRESULT                             FCN_VO(tgCO_CP_Penetrate_CylAxis_CY)( VEC_OBJ_T(STg2_CO_Packet,PC), VEC_OBJ_T(STg2_CO_Axis_Result,CPC), VEC_OBJ_T(TgTUBE,CPC), VEC_OBJ_T(TgTUBE,CPC) );
//
//
//
//
///* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
///*  Public Functions                                                                                                                                                               */
///* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
//
///* ---- FCN_VO(tgCO_CP_Penetrate_CY) --------------------------------------------------------------------------------------------------------------------------------------------- */
///* Input:  tgPacket: The current series of contact points for this query-series, and contact generation parameters.                                                                */
///* Input:  psCP0: Capsule primitive                                                                                                                                                */
///* Input:  psCY0: Cylinder primitive - contact points are generated on this primitive                                                                                              */
///* Output: tgPacket: Points of penetration between the two primitives are added to it                                                                                              */
///* Return: Result Code                                                                                                                                                             */
///* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
//TgRESULT FCN_VO(tgCO_CP_Penetrate_CY)(VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_OBJ_T(TgTUBE,CPC) psCP0, VEC_OBJ_T(TgTUBE,CPC) psCY0)
//{
//    VEC_OBJ_T(STg2_CO_Contact,P)        psContact;;
//    VEC_OBJ_T(STg2_CO_Axis_Result)      sAxS;
//
//    TgPARAM_CHECK( FCN_VO(tgGM_TB_Is_Valid)(psCY0) && FCN_VO(tgGM_TB_Is_Valid)(psCP0) );
//
//    if (0 == psPacket->m_nuiMaxContact || psPacket->m_nuiContact >= psPacket->m_nuiMaxContact || nullptr == psPacket->m_psContact)
//    {
//        return (KTgE_FAIL);
//    }
//
//    /* Find the minimal axis of separation, or return if the primitives are not in contact. */
//
//    if (!FCN_VO(tgCO_CP_Axis_Seperation_CY)( sAxS, psCP0, psCY0))
//    {
//        return (KTgE_NO_INTERSECT);
//    };
//
//    TgERROR( FCN_F(tgCM_NR1)(FCN_V(tgMH_LSQ)( sAxS.m_vNormal)) && sAxS.m_fDepth >= TYPE_K(0) );
//
//    /* == Contact Generation == */
//
//    psContact = psPacket->m_psContact + psPacket->m_nuiContact;
//
//    switch (sAxS.m_iAxis)
//    {
//        case 7: /* -- Axis: Rim -- */
//
//            psContact->m_vS0 = sAxS.m_vPoint;
//            psContact->m_vN0 = sAxS.m_vNormal;
//            psContact->m_vT0 = TYPE_K(0);
//            psContact->m_vDepth = sAxS.m_fDepth;
//
//            ++psPacket->m_nuiContact;
//
//            return (KTgS_OK);
//
//        case 2:
//        { /* -- Axis: Perpendicular to Axis of Cylinder -- */
//
//            VEC_T(1,C)      vK0 = FCN_VO(tgGM_CP_Support_Point)(psCP0, &sAxS.m_vNormal);
//            VEC_T(1,C)      vK1 = FCN_V(tgMH_SUB)( vK0, &psCY0->m_vOrigin);
//            VAR_T(C)        fTest = FCN_V(tgMH_DOT)( vK1, &sAxS.m_vNormal) + psCY0->m_fRadius;
//            VEC_T(1,C)      vK2 = FCN_V(tgMH_MUL_SV)(fTest, &sAxS.m_vNormal);
//
//            if (fTest <= TYPE_K(0))
//            {
//                TgWARN_CO("Separation Axis found with no contacts generated.\n");
//                return (KTgE_NO_INTERSECT);
//            };
//
//            psContact->m_vS0 = FCN_V(tgMH_SUB)( vK0, vK2 );
//            psContact->m_vN0 = sAxS.m_vNormal;
//            psContact->m_vT0 = TYPE_K(0);
//            psContact->m_vDepth = sAxS.m_fDepth;
//
//            ++psPacket->m_nuiContact;
//
//            return (KTgS_OK);
//
//        };
//
//        case 1:
//        { /* -- Axis: Cylinder Axis -- */
//
//            return (FCN_VO(tgCO_CP_Penetrate_CylAxis_CY)(psPacket, &sAxS, psCP0, psCY0));
//
//        };
//
//        default:
//            TgWARN_CO("Should not be able to reach this location.\n");
//            return (KTgE_FAIL);
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
///* ---- FCN_VO(tgCO_CP_Axis_Seperation_CY) --------------------------------------------------------------------------------------------------------------------------------------- */
///* Input:  psCP0: Capsule primitive                                                                                                                                                */
///* Input:  psCY0: Cylinder primitive                                                                                                                                               */
///* Output: sAxS: Structure holds the resulting axis separation information necessary to create a contact set.                                                                      */
///* Return: False if a separating axis exists, true otherwise                                                                                                                       */
///* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
//static TgBOOL FCN_VO(tgCO_CP_Axis_Seperation_CY)(VEC_OBJ_T(STg2_CO_Axis_Result,PC) psAxS, VEC_OBJ_T(TgTUBE,CPC) psCP0, VEC_OBJ_T(TgTUBE,CPC) psCY0)
//{
//    VAR_T()                             fDistSq, fA0, fA1;
//
//    /* Construct the difference vector between the two origins and calculate the reference frame projections. */
//
//    VEC_T(1,C)      vDS = FCN_V(tgMH_SUB)( psCY0->m_vOrigin, &psCP0->m_vOrigin);
//    VAR_T(C)        fDS_A1 = FCN_V(tgMH_DOT)( vDS, &psCY0->m_vU_HAX);
//    VAR_T(C)        fRS = psCP0->m_fRadius + psCY0->m_fRadius;
//    VAR_T(C)        fABS_A0_A1 = FCN_F(tgPM_ABS)(FCN_V(tgMH_DOT)( psCP0->m_vU_HAX, &psCY0->m_vU_HAX));
//    VAR_T(C)        fABS_A0xA1 = FCN_F(tgPM_SQRT)(TYPE_K(1) - FCN_F(tgCM_MIN)(TYPE_K(1), fABS_A0_A1*fABS_A0_A1));
//
//    psAxS->m_fDepth = -VAR_K(KTgMAX);
//
//    /* == Axis Separation Tests == */
//
//    {
//        /* -- Axis: Parallel to Axis of Cylinder -- */
//
//        VAR_T(C) fTest = FCN_F(tgPM_ABS)(fDS_A1) - (psCY0->m_fExtent + psCP0->m_fRadius + psCP0->m_fExtent*fABS_A0_A1);
//
//        TgERROR( FCN_VO(tgGM_TB_Is_Valid)(psCP0) && FCN_VO(tgGM_TB_Is_Valid)(psCY0) );
//
//        if (fTest > TYPE_K(0))
//        {
//            return (false);
//        };
//
//        if (fTest > psAxS->m_fDepth)
//        {
//            psAxS->m_vNormal = fDS_A1 > TYPE_K(0) ? psCY0->m_vU_HAX : FCN_V(tgMH_NEG)( psCY0->m_vU_HAX);
//            psAxS->m_fDepth = fTest;
//            psAxS->m_iAxis = 1;
//        };
//    }
//
//    fDistSq = FCN_VO(tgCO_SG_ClosestSq_PM_SG)( fA0, &fA1, &psCP0->m_sAX, &psCY0->m_sAX);
//
//    if (fDistSq > fRS*fRS)
//    {
//        return (false);
//    }
//
//    {
//        VEC_T(1,C)        vMinDirN;
//
//        VEC_T(1,C)      vK0 = FCN_V(tgMH_MUL_SV)(fA0, &psCP0->m_sAX.m_vDirN);
//        VEC_T(1,C)      vK1 = FCN_V(tgMH_MUL_SV)(fA1, &psCY0->m_sAX.m_vDirN);
//        VEC_T(1,C)      vMin_CP0 = FCN_V(tgMH_ADD)( psCP0->m_sAX.m_vOrigin, vK0 );
//        VEC_T(1,C)      vMin_CY0 = FCN_V(tgMH_ADD)( psCY0->m_sAX.m_vOrigin, vK1 );
//
//        if (fDistSq > VAR_K(KTgEPS))
//        {
//            VAR_T()                             fT0, fT1, fT2, fT3;
//
//            VEC_T(1,C)      vK2 = FCN_V(tgMH_SUB)( vMin_CY0, vMin_CP0 );
//
//            vMinDirN = FCN_V(tgMH_NORM)( vK2 );
//
//            /* -- Axis: Direction Between Points of Closest Proximity -- */
//
//            FCN_VO(tgGM_CP_Project)( fT0, &fT1, psCP0, vK2 );
//            FCN_VO(tgGM_CY_Project)( fT2, &fT3, psCY0, vK2 );
//
//            if (fT1 - fT2 < TYPE_K(0) || fT3 - fT0 < TYPE_K(0))
//            {
//                return (false);
//            }
//            else
//            {
//                VAR_T(C)        fTest = fT2 - fT1;
//
//                if (fTest > psAxS->m_fDepth)
//                {
//                    psAxS->m_vPoint = vMin_CY0;
//                    psAxS->m_vNormal = vMinDirN;
//                    psAxS->m_fDepth = fTest;
//                    psAxS->m_iAxis = 2;
//                };
//            };
//        }
//        else
//        {
//            VAR_T()                             fT0;
//
//            vMinDirN = FCN_V(tgMH_NORM_LEN)( fT0, vDS );
//
//            if (FCN_F(tgCM_NR0)(fT0))
//            {
//                /* That's it - throw in the towel, I give up - these primitives are just too penetrated to care which axis is used. */
//                return (true);
//            };
//        };
//
//        {
//            /* -- Axis: Perpendicular to Axis of Cylinder -- */
//
//            VAR_T(C)        fK2 = FCN_V(tgMH_DOT)( vMinDirN, &psCY0->m_vU_Basis0);
//            VAR_T(C)        fK3 = FCN_V(tgMH_DOT)( vMinDirN, &psCY0->m_vU_Basis1);
//            VEC_T(1,C)      vK2 = FCN_V(tgMH_MUL_SV)(fK2, &psCY0->m_vU_Basis0);
//            VEC_T(1,C)      vK3 = FCN_V(tgMH_MUL_SV)(fK3, &psCY0->m_vU_Basis1);
//            VEC_T(1,C)      vK4 = FCN_V(tgMH_ADD)( vK2, vK3 );
//            VEC_T(1,C)      vK5 = FCN_V(tgMH_NORM)( vK4 );
//            VAR_T(C)        fK4 = FCN_F(tgPM_ABS)(FCN_V(tgMH_DOT)( vK5, &psCP0->m_vU_HAX));
//            VAR_T(C)        fK5 = FCN_F(tgPM_ABS)(FCN_V(tgMH_DOT)( vK5, vDS ));
//
//            VAR_T(C) fTest = fK5 - (psCY0->m_fRadius + fK4*psCP0->m_fExtent + psCP0->m_fRadius);
//
//            if (fTest > TYPE_K(0))
//            {
//                return (false);
//            };
//
//            if (fTest > psAxS->m_fDepth)
//            {
//                psAxS->m_vPoint = vMin_CP0;
//                psAxS->m_vNormal = vK5;
//                psAxS->m_fDepth = fTest;
//                psAxS->m_iAxis = 2;
//            };
//        }
//
//
//        if (!FCN_F(tgCM_NR1)(fABS_A0_A1) && !FCN_F(tgCM_NR0)(fABS_A0xA1))
//        {
//            /* -- Axis: Perpendicular to Axis of Capsule -- */
//
//            VAR_T(C)        fK2 = FCN_V(tgMH_DOT)( vMinDirN, &psCP0->m_vU_Basis0);
//            VAR_T(C)        fK3 = FCN_V(tgMH_DOT)( vMinDirN, &psCP0->m_vU_Basis1);
//            VEC_T(1,C)      vK2 = FCN_V(tgMH_MUL_SV)(fK2, &psCP0->m_vU_Basis0);
//            VEC_T(1,C)      vK3 = FCN_V(tgMH_MUL_SV)(fK3, &psCP0->m_vU_Basis1);
//            VEC_T(1,C)      vK4 = FCN_V(tgMH_ADD)( vK2, vK3 );
//            VEC_T(1,C)      vK5 = FCN_V(tgMH_NORM)( vK4 );
//            VAR_T(C)        fK4 = FCN_F(tgPM_ABS)(FCN_V(tgMH_DOT)( vK5, &psCY0->m_vU_HAX));
//            VAR_T(C)        fAx_C10 = FCN_V(tgMH_DOT)( vK5, &psCY0->m_vU_Basis0);
//            VAR_T(C)        fAx_C11 = FCN_V(tgMH_DOT)( vK5, &psCY0->m_vU_Basis1);
//            VAR_T(C)        fK5 = FCN_F(tgPM_SQRT)(fAx_C10*fAx_C10 + fAx_C11*fAx_C11);
//            VAR_T(C)        fK6 = FCN_F(tgPM_ABS)(FCN_V(tgMH_DOT)( vK5, vDS ));
//
//            VAR_T(C) fTest = fK6 - (psCP0->m_fRadius + fK4*psCY0->m_fExtent + fK5*psCY0->m_fRadius);
//
//            if (fTest > TYPE_K(0))
//            {
//                return (false);
//            };
//
//            if (fTest > psAxS->m_fDepth)
//            {
//                psAxS->m_vPoint = vMin_CY0;
//                psAxS->m_vNormal = vK5;
//                psAxS->m_fDepth = fTest;
//                psAxS->m_iAxis = 2;
//            };
//        };
//
//        /* !! VOODOO MAGIC TIME !! - Red Red Wine, Drink a lot of it before proceeding, I'm telling you man - get snookered. */
//        /* Need to try to test the rim cases - <shot> */
//
//        if (FCN_F(tgCM_NR1)(fA1) || FCN_F(tgCM_NR0)(fA1))
//        {
//            VEC_T(1,C)        vCI0, vSG0;
//            VEC_OBJ_T(TgCIRCLE)                 sCI0;
//
//            FCN_VO(tgGM_CI_Init)(
//                &sCI0, &psCY0->m_vU_Basis0, &psCY0->m_vU_HAX, &psCY0->m_vU_Basis1, &vMin_CY0, psCY0->m_fRadius);
//
//            fDistSq = FCN_VO(tgCO_CI_ClosestSq_SG)( vCI0, &vSG0, &sCI0, &psCP0->m_sAX);
//
//            if (fDistSq < TYPE_K(0))
//            {
//                return (true);
//            }
//            else
//            {
//                VAR_T()                             fT0, fT1, fT2, fT3;
//
//                VEC_T(1,C)      vK2 = FCN_V(tgMH_SUB)( vCI0, vSG0 );
//                VEC_T(1,C)      vK3 = FCN_V(tgMH_NORM)( vK2 );
//
//                FCN_VO(tgGM_CP_Project)( fT0, &fT1, psCP0, vK3 );
//                FCN_VO(tgGM_CY_Project)( fT2, &fT3, psCY0, vK3 );
//
//                if (fT1 - fT2 < TYPE_K(0) || fT3 - fT0 < TYPE_K(0))
//                {
//                    return (false);
//                }
//                else
//                {
//                    VAR_T(C)        fTest = fT2 - fT1;
//
//                    if (fTest > psAxS->m_fDepth)
//                    {
//                        psAxS->m_vPoint = vCI0;
//                        psAxS->m_vNormal = vK3;
//                        psAxS->m_fDepth = fTest;
//                        psAxS->m_iAxis = 3;
//                    };
//                };
//            };
//        };
//    };
//
//    return (true);
//}
//
//
///* ---- FCN_VO(tgCO_CP_Penetrate_CylAxis_CY) ------------------------------------------------------------------------------------------------------------------------------------- */
///* Input:  tgPacket: The current series of contact points for this query-series, and contact generation parameters.                                                                */
///* Input:  sAxS: Structure holding the resulting axis separation information necessary to create a contact set.                                                                    */
///* Input:  psCP0: Capsule primitive                                                                                                                                                */
///* Input:  psCY0: Cylinder primitive - contact points are generated on this primitive                                                                                              */
///* Output: tgPacket: Points of penetration between the two primitives are added to it                                                                                              */
///* Return: Result Code                                                                                                                                                             */
///* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
//static TgRESULT FCN_VO(tgCO_CP_Penetrate_CylAxis_CY)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_OBJ_T(STg2_CO_Axis_Result,CPC) psAxS, VEC_OBJ_T(TgTUBE,CPC) psCP0, VEC_OBJ_T(TgTUBE,CPC) psCY0 )
//{
//    /* (1) Capsule is contained within the infinite projection of the cylinder (tube) */
//    /* (2) Capsule axis termination is contained but also passes through the cylinder (tube). */
//    /* (3) Capsule passes through-and-through the cylinder (tube) */
//    /* (4) Capsule axis is entirely outside of the cylinder - the only intersecting part is the capsule cap. */
//
//    VEC_OBJ_T(STg2_CO_Contact,P)        psContact;;
//    VAR_T()                             fT0, fT1;
//    VEC_OBJ_T(TgSEGMENT)                sSG0;
//
//    TgSINT_E32_C    niContact = psPacket->m_nuiContact;
//
//    VEC_T(1,C)      vK0 = FCN_V(tgMH_MUL_SV)(psCY0->m_fExtent, &psAxS->m_vNormal);
//    VEC_T(1,C)      vK1 = FCN_V(tgMH_SUB)( psCY0->m_vOrigin, vK0 );
//    VAR_T(C)        fAX_N = FCN_V(tgMH_DOT)( psCP0->m_vU_HAX, &psAxS->m_vNormal);
//    VAR_T(C)        fUseBX = FCN_F(tgPM_ABS)(fAX_N) - (TYPE_K(1) - VAR_K(KTgEPS));
//
//    {
//        /* Attempt to create a contact point at the lowest point on the capsule. */
//
//        VEC_T(1,C)      vK2 = FCN_V(tgMH_MUL_SV)(FCN_F(tgPM_FSEL)(fAX_N, TYPE_K(1), -TYPE_K(1)), &psCP0->m_vHAX);
//        VEC_T(1,C)      vK3 = FCN_V(tgMH_ADD)( psCP0->m_vOrigin, vK2 );
//        VEC_T(1,C)      vK4 = FCN_V(tgMH_SUB)( vK3, vK1 );
//
//        VAR_T(C)        fK0 = FCN_V(tgMH_DOT)( vK4, &psAxS->m_vNormal);
//
//        if (fK0 > TYPE_K(0) && FCN_VO(tgGM_CY_Is_Contained)(psCY0, vK3 ))
//        {
//            VEC_T(1,C)      vK5 = FCN_V(tgMH_MUL_SV)(psCP0->m_fRadius, &psAxS->m_vNormal);
//
//            /* Capsule termination is a contact point ([Case: 1,2]) */
//
//            psContact = psPacket->m_psContact + psPacket->m_nuiContact;
//
//            psContact->m_vS0 = FCN_V(tgMH_ADD)( vK3, vK5 );
//            psContact->m_vN0 = psAxS->m_vNormal;
//            psContact->m_vT0 = TYPE_K(0);
//            psContact->m_vDepth = fK0;
//
//            ++psPacket->m_nuiContact;
//        };
//    };
//
//    {
//        /* Construct a capsule axis that is directed for maximum penetration into the cylinder. */
//        VEC_T(1,C)      vK2 = FCN_V(tgMH_MUL_SV)(fAX_N, &psCP0->m_vU_HAX);
//        VEC_T(1,C)      vK3 = FCN_V(tgMH_SUB)( psAxS->m_vNormal, vK2 ); /*vT0 */
//
//        VAR_T(C)        fX = FCN_F(tgPM_FSEL)(fUseBX, psCP0->m_vU_Basis0.x, vK3.x);
//        VAR_T(C)        fY = FCN_F(tgPM_FSEL)(fUseBX, psCP0->m_vU_Basis0.y, vK3.y);
//        VAR_T(C)        fZ = FCN_F(tgPM_FSEL)(fUseBX, psCP0->m_vU_Basis0.z, vK3.z);
//
//        VEC_T(1,C)      vK4 = FCN_V(tgMH_Init_Vector_ELEM)(fX, fY, fZ);
//        VEC_T(1,C)      vK5 = FCN_V(tgMH_NORM)( vK4 ); /*vX0 */
//        VEC_T(1,C)      vK6 = FCN_V(tgMH_MUL_SV)(psCP0->m_fRadius, vK5 );
//        VEC_T(1,C)      vK7 = FCN_V(tgMH_ADD)( psCP0->m_sAX.m_vOrigin, vK6 );
//
//        FCN_VO(tgGM_SG_Set_Origin)( sSG0, vK7 );
//        FCN_VO(tgGM_SG_Set_DirN)( sSG0, &psCP0->m_sAX.m_vDirN);
//    }
//
//    /* Translate the capsule axis to the line of deepest penetration along the capsule, and then clip it to the cylinder. */
//
//    if (FCN_VO(tgCO_CY_Clip_PM_SG)( fT0, &fT1, psCY0, sSG0 ) >= 0)
//    {
//        VEC_T(1,C)      vK2 = FCN_V(tgMH_MUL_SV)(fT0, &psCP0->m_sAX.m_vDirN);
//        VEC_T(1,C)      vK3 = FCN_V(tgMH_ADD)( sSG0.m_vOrigin, vK2 );
//        VEC_T(1,C)      vK4 = FCN_V(tgMH_SUB)( vK3, vK1 );
//        VAR_T(C)        fK0 = FCN_V(tgMH_DOT)( vK4, &psAxS->m_vNormal);
//
//        VEC_T(1,C)      vK5 = FCN_V(tgMH_MUL_SV)(fT1, &psCP0->m_sAX.m_vDirN);
//        VEC_T(1,C)      vK6 = FCN_V(tgMH_ADD)( sSG0.m_vOrigin, vK5 );
//        VEC_T(1,C)      vK7 = FCN_V(tgMH_SUB)( vK6, vK1 );
//        VAR_T(C)        fK1 = FCN_V(tgMH_DOT)( vK7, &psAxS->m_vNormal);
//
//        if (fK0 > TYPE_K(0) && niContact == psPacket->m_nuiContact)
//        {
//            if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
//            {
//                return (KTgE_MAX_CONTACTS);
//            };
//
//            /* Capsule termination is a contact point ([Case: 3]) */
//
//            psContact = psPacket->m_psContact + psPacket->m_nuiContact;
//
//            psContact->m_vS0 = vK3;
//            psContact->m_vN0 = psAxS->m_vNormal;
//            psContact->m_vT0 = TYPE_K(0);
//            psContact->m_vDepth = fK0;
//
//            ++psPacket->m_nuiContact;
//        };
//
//        /* Similar to above, and it must not be sufficiently divergent from the first point (prevent two-point tangents) */
//
//        if (fK1 > TYPE_K(0) && !FCN_F(tgCM_NR0)(fT0 - fT1))
//        {
//            if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
//            {
//                return (KTgE_MAX_CONTACTS);
//            };
//
//            /* Capsule termination is a contact point ([Case: 1,2,3]) */
//
//            psContact = psPacket->m_psContact + psPacket->m_nuiContact;
//
//            psContact->m_vS0 = vK6;
//            psContact->m_vN0 = psAxS->m_vNormal;
//            psContact->m_vT0 = TYPE_K(0);
//            psContact->m_vDepth = fK1;
//
//            ++psPacket->m_nuiContact;
//        };
//
//        return (niContact != psPacket->m_nuiContact ? KTgS_OK : KTgE_NO_INTERSECT);
//    };
//
//    /* The capsule contact line is outside of the cylinder.  Attempt to intersect the cylinder with the capsule. ([Case: 4]) */
//
//    {
//        /* One of the extremes of the cylinder rim must be penetrated into the capsule.  Therefore use math. */
//        VEC_T(1,C)      vK2 = FCN_V(tgMH_MUL_SV)(fAX_N, &psAxS->m_vNormal);
//        VEC_T(1,C)      vK3 = FCN_V(tgMH_SUB)( psCP0->m_vU_HAX, vK2 );
//        VEC_T(1,C)      vK4 = FCN_V(tgMH_MUL_SV)(FCN_F(tgPM_FSEL)(fAX_N, -TYPE_K(1), -TYPE_K(1)), vK3 );
//        VEC_T(1,C)      vK5 = FCN_V(tgMH_NORM)( vK4 );
//        VEC_T(1,C)      vK6 = FCN_V(tgMH_MUL_SV)(psCY0->m_fRadius, vK5 );
//        VEC_T(1,C)      vT0 = FCN_V(tgMH_ADD)( vK3, vK6 );
//        VEC_T(1,C)      vK7 = FCN_V(tgMH_SUB)( vT0, vK3 );
//        VEC_T(1,C)      vK8 = FCN_V(tgMH_NORM_LEN)( fT0, vK7 );
//        VAR_T(C)        fK0 = FCN_V(tgMH_DOT)( vK8, &psAxS->m_vNormal) * (psCP0->m_fRadius - fT0);
//        VEC_T(1,C)      vT1 = FCN_V(tgMH_SUB)( vK3, vK6 );
//        VEC_T(1,C)      vK9 = FCN_V(tgMH_SUB)( vT1, vK3 );
//        VEC_T(1,C)      vKA = FCN_V(tgMH_NORM_LEN)( fT1, vK9 );
//        VAR_T(C)        fK1 = FCN_V(tgMH_DOT)( vKA, &psAxS->m_vNormal) * (psCP0->m_fRadius - fT1);
//
//        if (fK0 > TYPE_K(0))
//        {
//            /* Capsule termination is a contact point ([Case: 3]) */
//
//            psContact = psPacket->m_psContact + psPacket->m_nuiContact;
//
//            psContact->m_vS0 = vT0;
//            psContact->m_vN0 = psAxS->m_vNormal;
//            psContact->m_vT0 = TYPE_K(0);
//            psContact->m_vDepth = fK0;
//
//            ++psPacket->m_nuiContact;
//        };
//
//        if (fK1 > TYPE_K(0))
//        {
//            /* Capsule termination is a contact point ([Case: 3]) */
//
//            psContact = psPacket->m_psContact + psPacket->m_nuiContact;
//
//            psContact->m_vS0 = vT0;
//            psContact->m_vN0 = psAxS->m_vNormal;
//            psContact->m_vT0 = TYPE_K(0);
//            psContact->m_vDepth = fK1;
//
//            ++psPacket->m_nuiContact;
//        };
//
//        return (niContact != psPacket->m_nuiContact ? KTgS_OK : KTgE_NO_INTERSECT);
//    };
//}
//
//
///* =============================================================================================================================================================================== */
//
//#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
