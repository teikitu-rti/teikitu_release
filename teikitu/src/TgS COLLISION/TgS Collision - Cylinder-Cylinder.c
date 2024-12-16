///* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
///*  »Project«   Teikitu Gaming System (TgS) (∂)
//    »File«      TgS Collision - Cylinder-Cylinder.c
//    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
//    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
///*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
///*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
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
//FCN_VO(tgCO_CY_Axis_Seperation_CY)(
//    VEC_OBJ_T(STg2_CO_Axis_Result,PC) OUT0, VEC_OBJ_T(TgTUBE,CPC) ARG1, VEC_OBJ_T(TgTUBE,CPC) ARG2 );
//
//static TgRESULT
//FCN_VO(tgCO_CY_Internal_CapCap_CY)(
//    VEC_OBJ_T(STg2_CO_Contact,PU) OUT0, TgSINT_F32_PC OUT1, VEC_T(1,C) ARG2, VEC_OBJ_T(TgELLIPSE,CPC) ARG3, VEC_OBJ_T(TgTUBE,CPC) ARG4, VEC_OBJ_T(TgTUBE,CPC) ARG5 );
//
//static TgRESULT
//FCN_VO(tgCO_CY_Internal_CapContained_CY)(
//    VEC_OBJ_T(STg2_CO_Contact,PU) OUT0, TgSINT_F32_PC OUT1, VEC_T(1,C) ARG2, VEC_OBJ_T(TgTUBE,CPC) ARG3, VEC_OBJ_T(TgTUBE,CPC) ARG4 );
//
//static TgRESULT
//FCN_VO(tgCO_CY_Internal_AxisCap_CY)(
//    VEC_OBJ_T(STg2_CO_Contact,PU) OUT0, TgSINT_F32_PC OUT1, VEC_T(1,C) ARG2, VEC_OBJ_T(TgTUBE,CPC) ARG3, VEC_OBJ_T(TgTUBE,CPC) ARG4 );
//
//TgEXTN TgBOOL
//FCN_VO(tgGM_CY_Is_Cap_Contained)(
//    VEC_OBJ_T(TgELLIPSE,PCU) ARG0, VEC_OBJ_T(TgTUBE,CPCU) ARG1, VAR_T(C) ARG2, VEC_OBJ_T(TgTUBE,CPCU) ARG3, VAR_T(C) ARG4 );
//
//
//
//
///* ---- FCN_VO(tgGM_CY_Is_Cap_Contained) --------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
//TgBOOL FCN_VO(tgGM_CY_Is_Cap_Contained)( VEC_OBJ_T(TgELLIPSE,PCU) psEL0, VEC_OBJ_T(TgTUBE,CPCU) psCY0, VAR_T(C) fDS_C0A, VEC_OBJ_T(TgTUBE,CPCU) psCY1, VAR_T(C) fDS_C1A )
//{
// /* Containment Test - the projection of the cap of cylinder 1 onto the cap of cylinder 0 */
//
//    VEC_T(1,C)      vX0 = FCN_V(tgMH_MUL_SV)(psCY0->m_vU_HAX.x, &psCY0->m_vU_HAX);
//    VEC_T(1,C)      vX1 = FCN_V(tgMH_MUL_SV)(psCY0->m_vU_HAX.y, &psCY0->m_vU_HAX);
//    VEC_T(1,C)      vX2 = FCN_V(tgMH_MUL_SV)(psCY0->m_vU_HAX.z, &psCY0->m_vU_HAX);
//    VEC_T(1,C)      vXF0 = FCN_V(tgMH_SUB_S)( (VEC_K(KTgUNIT_X)), vX0 );
//    VEC_T(1,C)      vXF1 = FCN_V(tgMH_SUB_S)( (VEC_K(KTgUNIT_Y)), vX1 );
//    VEC_T(1,C)      vXF2 = FCN_V(tgMH_SUB_S)( (VEC_K(KTgUNIT_Z)), vX2 );
//
//    /* Transform the centre of the caps of closest proximity */
//
//    VEC_T(1,C)      vB0 = FCN_V(tgMH_MUL_SV)(FCN_F(tgPM_FSEL)(fDS_C0A, TYPE_K(1), -TYPE_K(1)), &psCY0->m_vHAX);
//    VEC_T(1,C)      vB1 = FCN_V(tgMH_MUL_SV)(FCN_F(tgPM_FSEL)(fDS_C1A, -TYPE_K(1), TYPE_K(1)), &psCY1->m_vHAX);
//    VEC_T(1,C)      vW0 = FCN_V(tgMH_ADD)( psCY0->m_vOrigin, vB0 );
//    VEC_T(1,C)      vW1 = FCN_V(tgMH_ADD)( psCY1->m_vOrigin, vB1 );
//    VAR_T(C)        fA0 = FCN_V(tgMH_DOT)( vXF0, vW0 );
//    VAR_T(C)        fA1 = FCN_V(tgMH_DOT)( vXF1, vW0 );
//    VAR_T(C)        fA2 = FCN_V(tgMH_DOT)( vXF2, vW0 );
//    VAR_T(C)        fB0 = FCN_V(tgMH_DOT)( vXF0, vW1 );
//    VAR_T(C)        fB1 = FCN_V(tgMH_DOT)( vXF1, vW1 );
//    VAR_T(C)        fB2 = FCN_V(tgMH_DOT)( vXF2, vW1 );
//    VEC_T(1,C)      vW2 = FCN_V(tgMH_Init_Point_ELEM)(fA0, fA1, fA2);
//    VEC_T(1,C)      vW3 = FCN_V(tgMH_Init_Point_ELEM)(fB0, fB1, fB2);
//    VAR_T(C)        fU0 = FCN_V(tgMH_DOT)( vXF0, &psCY1->m_vU_HAX);
//    VAR_T(C)        fU1 = FCN_V(tgMH_DOT)( vXF1, &psCY1->m_vU_HAX);
//    VAR_T(C)        fU2 = FCN_V(tgMH_DOT)( vXF2, &psCY1->m_vU_HAX);
//
//    VEC_T(1,C)        vA0, vA1;
//    VEC_T(1,C)        vAxis;
//    VAR_T()                             fCapRadiusRatio;
//
//    /* Ellipse Axes */
//
//    vAxis = FCN_V(tgMH_Init_Vector_ELEM)(fU0, fU1, fU2);
//
//    if (FCN_V(tgMH_LSQ)( vAxis ) > VAR_K(KTgEPS))
//    {
//        vA0 = FCN_V(tgMH_UCX)( vAxis, &psCY0->m_vU_HAX);
//        vAxis = FCN_V(tgMH_CX)( psCY1->m_vU_HAX, vA0 );
//        vA1 = FCN_V(tgMH_Init_Vector_ELEM_S)(FCN_V(tgMH_DOT)( vXF0, vAxis ), FCN_V(tgMH_DOT)( vXF1, vAxis ), FCN_V(tgMH_DOT)( vXF2, vAxis ));
//    }
//    else
//    {
//        vA0 = psCY0->m_vU_Basis0;
//        vA1 = psCY0->m_vU_Basis1;
//    };
//
//    vA1 = FCN_V(tgMH_NORM_LEN)( fCapRadiusRatio, vA1 );
//
//    {
//        VAR_T(C)        fMajRad = fCapRadiusRatio*psCY1->m_fRadius;
//        VAR_T(C)        fA00 = FCN_V(tgMH_DOT)( vA0, &psCY0->m_vU_Basis0);
//        VAR_T(C)        fA01 = FCN_V(tgMH_DOT)( vA0, &psCY0->m_vU_Basis1);
//        VAR_T(C)        fA10 = FCN_V(tgMH_DOT)( vA1, &psCY0->m_vU_Basis0);
//        VAR_T(C)        fA11 = FCN_V(tgMH_DOT)( vA1, &psCY0->m_vU_Basis1);
//        VAR_T(C)        fR00 = fA00 * psCY1->m_fRadius;
//        VAR_T(C)        fR01 = fA01 * psCY1->m_fRadius;
//        VAR_T(C)        fR10 = fA10 * fMajRad;
//        VAR_T(C)        fR11 = fA11 * fMajRad;
//        VEC_T(1,C)      vW32 = FCN_V(tgMH_SUB)( vW3, vW2 );
//        VAR_T(C)        fWC0 = FCN_V(tgMH_DOT)( vW32, &psCY0->m_vU_Basis0);
//        VAR_T(C)        fWC1 = FCN_V(tgMH_DOT)( vW32, &psCY0->m_vU_Basis1);
//
//        /* Initialize the resulting ellipse formed by the projection */
//
//        FCN_VO(tgGM_EL_Set_Origin)( psEL0, &vW3 );
//        FCN_VO(tgGM_EL_Set_Minor_Unit)( psEL0, &vA0 );
//        FCN_VO(tgGM_EL_Set_Normal)( psEL0, &psCY0->m_vU_HAX );
//        FCN_VO(tgGM_EL_Set_Major_Unit)( psEL0, &vA1 );
//        FCN_VO(tgGM_EL_Set_Minor_Radius)( psEL0, psCY1->m_fRadius );
//        FCN_VO(tgGM_EL_Set_Major_Radius)( psEL0, fMajRad );
//
//        if (
//            (fWC0 + fR00)*(fWC0 + fR00) + (fWC1 + fR01)*(fWC1 + fR01) > psCY0->m_fRadiusSq ||
//            (fWC0 - fR00)*(fWC0 - fR00) + (fWC1 - fR01)*(fWC1 - fR01) > psCY0->m_fRadiusSq ||
//            (fWC0 + fR10)*(fWC0 + fR10) + (fWC1 + fR11)*(fWC1 + fR11) > psCY0->m_fRadiusSq ||
//            (fWC0 - fR10)*(fWC0 - fR10) + (fWC1 - fR11)*(fWC1 - fR11) > psCY0->m_fRadiusSq
//        )
//        {
//            return (false);
//        };
//    };
//
//    return (true);
//}
//
///* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
///*  Public Functions                                                                                                                                                               */
///* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
//
///* ---- FCN_VO(tgCO_CY_Penetrate_CY) --------------------------------------------------------------------------------------------------------------------------------------------- */
///* Input:  tgPacket: The current series of contact points for this query-series, and contact generation parameters.                                                                */
///* Input:  psCY0: Cylinder primitive                                                                                                                                               */
///* Input:  psCY1: Cylinder primitive - contact points are generated on this primitive                                                                                              */
///* Output: tgPacket: Points of penetration between the two primitives are added to it                                                                                              */
///* Return: Result Code                                                                                                                                                             */
///* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
//TgRESULT FCN_VO(tgCO_CY_Penetrate_CY)(VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_OBJ_T(TgTUBE,CPC) psCY0, VEC_OBJ_T(TgTUBE,CPC) psCY1)
//{
//    VEC_OBJ_T(STg2_CO_Contact,P)        psContact;;
//    VEC_OBJ_T(STg2_CO_Axis_Result)      sAxS;
//    VEC_OBJ_T(STg2_CO_Contact)          sContact[4];
//    TgSINT_F32                          niMax, iIdx, niPoint = 0;
//
//    VEC_T(1,C)      vDS = FCN_V(tgMH_SUB)( psCY1->m_vOrigin, &psCY0->m_vOrigin);
//    VAR_T(C)        fDS_A0 = FCN_V(tgMH_DOT)( vDS, &psCY0->m_vU_HAX);
//    VAR_T(C)        fDS_A1 = FCN_V(tgMH_DOT)( vDS, &psCY1->m_vU_HAX);
//
//    TgPARAM_CHECK( FCN_VO(tgGM_TB_Is_Valid)(psCY0) && FCN_VO(tgGM_TB_Is_Valid)(psCY1) );
//
//    if (0 == psPacket->m_nuiMaxContact || psPacket->m_nuiContact >= psPacket->m_nuiMaxContact || nullptr == psPacket->m_psContact)
//    {
//        return (KTgE_FAIL);
//    };
//
//    /* Find the minimal axis of separation, or return if the primitives are not in contact. */
//
//    if (!FCN_VO(tgCO_CY_Axis_Seperation_CY)( sAxS, psCY0, psCY1))
//    {
//        return (KTgE_NO_INTERSECT);
//    };
//
//    TgERROR( FCN_F(tgCM_NR1)(FCN_V(tgMH_LSQ)( sAxS.m_vNormal)) && sAxS.m_fDepth >= TYPE_K(0) );
//
//    /* == Contact Generation == */
//
//    switch (sAxS.m_iAxis)
//    {
//        case 0: /* -- Axis: Cylinder #0 Axis -- */
//        {
//            VEC_OBJ_T(TgELLIPSE)                sEL1;
//
//            if (FCN_VO(tgGM_CY_Is_Cap_Contained)( sEL1, psCY0, fDS_A0, psCY1, fDS_A1))
//            {
//                if (FCN_F(tgPM_ABS)(FCN_V(tgMH_DOT)( psCY0->m_vU_HAX, &psCY1->m_vU_HAX)) < VAR_K(KTgSQRT1_2))
//                {
//                    if (FCN_VO(tgCO_CY_Internal_AxisCap_CY)(sContact, &niPoint, &sAxS.m_vNormal, psCY0, psCY1) >= 0)
//                    {
//                        break;
//                    };
//                }
//                else if (FCN_VO(tgCO_CY_Internal_CapContained_CY)(sContact, &niPoint, &sAxS.m_vNormal, psCY0, psCY1) >= 0)
//                {
//                    break;
//                };
//            }
//            else
//            {
//                /* The contact normal is the primary axis of cylinder zero.  Now we need to determine if the case to be generated has the ends touching or an end and */
//                /* side touching. */
//
//                if (FCN_F(tgPM_ABS)(FCN_V(tgMH_DOT)( psCY0->m_vU_HAX, &psCY1->m_vU_HAX)) < VAR_K(KTgSQRT1_2))
//                {
//                    if (FCN_VO(tgCO_CY_Internal_AxisCap_CY)(sContact, &niPoint, &sAxS.m_vNormal, psCY0, psCY1) >= 0)
//                    {
//                        break;
//                    };
//                }
//                else if (FCN_VO(tgCO_CY_Internal_CapCap_CY)(sContact, &niPoint, &sAxS.m_vNormal, &sEL1, psCY0, psCY1) >= 0)
//                {
//                    break;
//                };
//            };
//
//            return (KTgE_NO_INTERSECT);
//        };
//
//        case 2: /* -- Axis: Cylinder #1 Axis -- */
//        {
//            TgRESULT                            iResult;
//            VEC_OBJ_T(TgELLIPSE)                sEL0;
//            TgSINT_F32                          iIndex;
//
//            if (FCN_VO(tgGM_CY_Is_Cap_Contained)( sEL0, psCY1, -fDS_A1, psCY0, -fDS_A0))
//            {
//                if (FCN_F(tgPM_ABS)(FCN_V(tgMH_DOT)( psCY0->m_vU_HAX, &psCY1->m_vU_HAX)) < VAR_K(KTgSQRT1_2))
//                {
//                    iResult = FCN_VO(tgCO_CY_Internal_AxisCap_CY)(sContact, &niPoint, &sAxS.m_vNormal, psCY1, psCY0);
//
//                    if (iResult >= 0)
//                    {
//                        /* Since we swapped the primitives and normal during the contact generation we now need to take the points and reverse them back out so they are */
//                        /* being generated on the correct geometry in the correct direction. */
//                        for (iIndex = 0; iIndex < niPoint; ++iIndex)
//                        {
//                            VEC_T(1,C)      vK0 = FCN_V(tgMH_MUL_SV)(sContact[iIndex].m_fDepth, &sAxS.m_vNormal);
//
//                            sContact[iIndex].m_vS0 = FCN_V(tgMH_SUB)( sContact[iIndex].m_vS0, vK0 );
//                        };
//                        break;
//                    };
//                }
//                else
//                {
//                    iResult = FCN_VO(tgCO_CY_Internal_CapContained_CY)(sContact, &niPoint, &sAxS.m_vNormal, psCY1, psCY0);
//
//                    if (iResult >= 0)
//                    {
//                        /* Since we swapped the primitives and normal during the contact generation we now need to take the points and reverse them back out so they are */
//                        /* being generated on the correct geometry in the correct direction. */
//                        for (iIndex = 0; iIndex < niPoint; ++iIndex)
//                        {
//                            VEC_T(1,C)      vK0 = FCN_V(tgMH_MUL_SV)(sContact[iIndex].m_fDepth, &sAxS.m_vNormal);
//
//                            sContact[iIndex].m_vS0 = FCN_V(tgMH_ADD)( sContact[iIndex].m_vS0, vK0 );
//                        };
//                        sAxS.m_vNormal = FCN_V(tgMH_NEG)( sAxS.m_vNormal);
//                        break;
//                    };
//                };
//            }
//            else
//            {
//                if (FCN_F(tgPM_ABS)(FCN_V(tgMH_DOT)( psCY0->m_vU_HAX, &psCY1->m_vU_HAX)) < VAR_K(KTgSQRT1_2))
//                {
//                    iResult = FCN_VO(tgCO_CY_Internal_AxisCap_CY)(sContact, &niPoint, &sAxS.m_vNormal, psCY0, psCY1);
//
//                    if (iResult >= 0)
//                    {
//                        /* Since we swapped the primitives and normal during the contact generation we now need to take the points and reverse them back out so they are */
//                        /* being generated on the correct geometry in the correct direction. */
//                        for (iIndex = 0; iIndex < niPoint; ++iIndex)
//                        {
//                            VEC_T(1,C)      vK0 = FCN_V(tgMH_MUL_SV)(sContact[iIndex].m_fDepth, &sAxS.m_vNormal);
//
//                            sContact[iIndex].m_vS0 = FCN_V(tgMH_SUB)( sContact[iIndex].m_vS0, vK0 );
//                        };
//                        break;
//                    };
//                }
//
//                iResult = FCN_VO(tgCO_CY_Internal_CapCap_CY)(sContact, &niPoint, &sAxS.m_vNormal, &sEL0, psCY0, psCY1);
//
//                if (iResult >= 0)
//                {
//                    /* Since we swapped the primitives and normal during the contact generation we now need to take the points and reverse them back out so they are */
//                    /* being generated on the correct geometry in the correct direction. */
//                    for (iIndex = 0; iIndex < niPoint; ++iIndex)
//                    {
//                        VEC_T(1,C)      vK0 = FCN_V(tgMH_MUL_SV)(sContact[iIndex].m_fDepth, &sAxS.m_vNormal);
//
//                        sContact[iIndex].m_vS0 = FCN_V(tgMH_SUB)( sContact[iIndex].m_vS0, vK0 );
//                    };
//                    break;
//                };
//            };
//
//            return (KTgE_NO_INTERSECT);
//        };
//
//        case 4: /* -- Axis: Perpendicular to Common Cylinder Axis -- */
//        {
//            VAR_T(C)        fMinY = FCN_F(tgCM_MAX)(-psCY1->m_fExtent, fDS_A1 - psCY0->m_fExtent);
//            VAR_T(C)        fMaxY = FCN_F(tgCM_MIN)(psCY1->m_fExtent, fDS_A1 + psCY0->m_fExtent);
//            VEC_T(1,C)      vK0 = FCN_V(tgMH_MUL_SV)(fMaxY, &psCY1->m_vU_HAX);
//            VEC_T(1,C)      vK1 = FCN_V(tgMH_MUL_SV)(psCY1->m_fRadius, &sAxS.m_vNormal);
//            VEC_T(1,C)      vK2 = FCN_V(tgMH_ADD)( psCY1->m_vOrigin, vK0 );
//
//            if (!FCN_F(tgCM_NR0)(fMinY - fMaxY))
//            {
//                VEC_T(1,C)      vK3 = FCN_V(tgMH_MUL_SV)(fMinY, &psCY1->m_vU_HAX);
//                VEC_T(1,C)      vK4 = FCN_V(tgMH_MUL_SV)(psCY1->m_fRadius, &sAxS.m_vNormal);
//                VEC_T(1,C)      vK5 = FCN_V(tgMH_ADD)( psCY1->m_vOrigin, vK3 );
//
//                psContact = psPacket->m_psContact + psPacket->m_nuiContact;
//
//                psContact->m_vS0 = FCN_V(tgMH_SUB)( vK5, vK4 );
//                psContact->m_vN0 = sAxS.m_vNormal;
//                psContact->m_vT0 = TYPE_K(0);
//                psContact->m_vDepth = sAxS.m_fDepth;
//
//                ++psPacket->m_nuiContact;
//
//                if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
//                {
//                    return (KTgE_MAX_CONTACTS);
//                };
//            };
//
//            psContact = psPacket->m_psContact + psPacket->m_nuiContact;
//
//            psContact->m_vS0 = FCN_V(tgMH_SUB)( vK2, vK1 );
//            psContact->m_vN0 = sAxS.m_vNormal;
//            psContact->m_vT0 = TYPE_K(0);
//            psContact->m_vDepth = sAxS.m_fDepth;
//
//            ++psPacket->m_nuiContact;
//
//            return (KTgS_OK);
//        };
//
//        case 8: /* -- Axis: Contact Between the Two Cylinder Rims -- */
//        case 5: /* -- Axis: Between Points of Closest Proximity -- */
//        {
//            /* Since this axis is only generated when the points of closest proximity do not lie at the termini of the respective cylinder axes, the resulting direction */
//            /* vector is known to be orthogonal to both axes.  (Proof by Observation: the minimal distance would be along a mutually perpendicular vector, which is known */
//            /* to exist since the lines are also known to be skew.) */
//
//            psContact = psPacket->m_psContact + psPacket->m_nuiContact;
//
//            psContact->m_vS0 = sAxS.m_vPoint;
//            psContact->m_vN0 = sAxS.m_vNormal;
//            psContact->m_vT0 = TYPE_K(0);
//            psContact->m_vDepth = sAxS.m_fDepth;
//
//            ++psPacket->m_nuiContact;
//
//            return (KTgS_OK);
//        };
//
//        case 6: /* -- Axis: Perpendicular to Axis of Cylinder 0 -- */
//        {
//            VEC_T(1,C)      vL0 = FCN_V(tgMH_NEG)( sAxS.m_vNormal);
//
//            psContact = psPacket->m_psContact + psPacket->m_nuiContact;
//
//            psContact->m_vS0 = FCN_VO(tgGM_CY_Support_Point)(psCY1, vL0 );
//            psContact->m_vN0 = sAxS.m_vNormal;
//            psContact->m_vT0 = TYPE_K(0);
//            psContact->m_vDepth = sAxS.m_fDepth;
//
//            ++psPacket->m_nuiContact;
//
//            return (KTgS_OK);
//        };
//
//        case 7: /* -- Axis: Perpendicular to Axis of Cylinder 1 -- */
//        {
//            VEC_T(1,C)      vL0 = FCN_V(tgMH_MUL_SV)(sAxS.m_fDepth, &sAxS.m_vNormal);
//            VEC_T(1,C)      vL1 = FCN_VO(tgGM_CY_Support_Point)(psCY0, &sAxS.m_vNormal);
//
//            psContact = psPacket->m_psContact + psPacket->m_nuiContact;
//
//            psContact->m_vS0 = FCN_V(tgMH_SUB)( vL1, vL0 );
//            psContact->m_vN0 = sAxS.m_vNormal;
//            psContact->m_vT0 = TYPE_K(0);
//            psContact->m_vDepth = sAxS.m_fDepth;
//
//            ++psPacket->m_nuiContact;
//
//            return (KTgS_OK);
//        };
//
//        default:
//            TgS_NO_DEFAULT(break);
//    };
//
//    niMax = tgCM_MIN_S32( niPoint, (psPacket->m_nuiMaxContact - psPacket->m_nuiContact) );
//
//    for (iIdx = 0; iIdx < niMax; ++iIdx)
//    {
//        psContact = psPacket->m_psContact + psPacket->m_nuiContact;
//
//        psContact->m_vS0 = sContact[iIdx].m_vS0;
//        psContact->m_vN0 = sAxS.m_vNormal;
//        psContact->m_vT0 = TYPE_K(0);
//        psContact->m_vDepth = sContact[iIdx].m_fDepth;
//
//        ++psPacket->m_nuiContact;
//    };
//
//    return (niMax != niPoint ? KTgE_MAX_CONTACTS : KTgS_OK);
//}
//
//
//
//
///* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
///*  File Local Functions                                                                                                                                                           */
///* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
//
///* ---- FCN_VO(tgCO_CY_Axis_Seperation_CY) --------------------------------------------------------------------------------------------------------------------------------------- */
///* Input:  psCY0, psCY1: Cylinder primitives                                                                                                                                       */
///* Output: sAxS: Structure holds the resulting axis separation information necessary to create a contact set.                                                                      */
///* Return: False if a separating axis exists, true otherwise                                                                                                                       */
///* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
//static TgBOOL FCN_VO(tgCO_CY_Axis_Seperation_CY)(VEC_OBJ_T(STg2_CO_Axis_Result,PC) psAxS, VEC_OBJ_T(TgTUBE,CPC) psCY0, VEC_OBJ_T(TgTUBE,CPC) psCY1)
//{
//    /*  To figure out all the possible axes of separation, it is necessary only to imagine the infinite set of vectors that are orthogonal to the cylinder surface.  Once */
//    /* conceived, it becomes obvious to separate the cylinder into three conceptual parts.  The body is the main tube section of the cylinder.  The caps are the planar */
//    /* terminal part of the cylinder and the rims are where the planar terminal part of the cylinder and the tube intersect.  The body and the caps have obvious and well */
//    /* defined orthogonal vectors sets.  In the case of the caps, the set has only one member - the normal defining the plane. For the body, the set is infinite, defined */
//    /* as those vectors in the cylinder cross-sectional plane that are directed radially.  The rim set is composed of a locus forming a quarter torus.  Most of these */
//    /* axes are invalid, and its a matter of choosing the right ones - and preferably a finite set in computational amount of time.  The correct axes can be found using */
//    /* the following methods: */
//
//    /* Cap-Rim      All cases should be found by the axial test */
//    /* Cap-Cap      All cases should be found by the axial test */
//    /* Cap-Body     All cases should be found by the axial test, if not the minimal distance vector will catch it. */
//
//    /* Rim-Body     Minimal distance vector, projected onto the cylinder plane, will find all such cases. */
//    /* Rim-Rim      The intersection of the two sets of normal rim vectors should be unique and is the test case. */
//
//    /* Body-Body    Minimal distance vector will find all such cases. */
//
//
//    VAR_T()                             fDistSq, fTest, fCA0, fCA1, fT0, fT1, fT2, fT3;
//
//    /* Construct the difference vector between the two origins and calculate the reference frame projections. */
//
//    VEC_T(1,C)      vDS = FCN_V(tgMH_SUB)( psCY1->m_vOrigin, &psCY0->m_vOrigin);
//    VAR_T(C)        fDS_A0 = FCN_V(tgMH_DOT)( vDS, &psCY0->m_vU_HAX);
//    VAR_T(C)        fDS_A1 = FCN_V(tgMH_DOT)( vDS, &psCY1->m_vU_HAX);
//    VAR_T(C)        fABS_A0_A1 = FCN_F(tgPM_ABS)(FCN_V(tgMH_DOT)( psCY0->m_vU_HAX, &psCY1->m_vU_HAX));
//    VAR_T(C)        fABS_A0xA1 = FCN_F(tgPM_SQRT)(TYPE_K(1) - FCN_F(tgCM_MIN)(TYPE_K(1), fABS_A0_A1*fABS_A0_A1));
//    VAR_T(C)        fRadSum = psCY0->m_fRadius + psCY1->m_fRadius;
//
//    psAxS->m_fDepth = VAR_K(KTgMAX);
//
//    TgERROR( FCN_VO(tgGM_TB_Is_Valid)(psCY0) && FCN_VO(tgGM_TB_Is_Valid)(psCY1) );
//
//    /* == Axis Separation Tests == */
//
//    /* -- Axis: Cylinder #0 Axis -- */
//
//    fTest = (psCY0->m_fExtent + psCY1->m_fRadius*fABS_A0xA1 + psCY1->m_fExtent*fABS_A0_A1) - FCN_F(tgPM_ABS)(fDS_A0);
//
//    if (fTest <= TYPE_K(0))
//    {
//        return (false);
//    };
//
//    if (fTest < psAxS->m_fDepth)
//    {
//        psAxS->m_vNormal = fDS_A0 > TYPE_K(0) ? psCY0->m_vU_HAX : FCN_V(tgMH_NEG)( psCY0->m_vU_HAX);
//        psAxS->m_fDepth = fTest;
//        psAxS->m_iAxis = 0;
//    };
//
//    /* == Cylinder Parallel Test == */
//
//    if (FCN_F(tgCM_NR1)(fABS_A0_A1) || FCN_F(tgCM_NR0)(fABS_A0xA1))
//    {
//        /* -- Axis: Perpendicular to Common Cylinder Axis -- */
//
//        fTest = FCN_V(tgMH_LSQ)( vDS ) - fDS_A0*fDS_A0;
//
//        if (fTest > fRadSum*fRadSum)
//        {
//            return (false);
//        };
//
//        fTest = fRadSum - FCN_F(tgPM_SQRT)(fTest);
//
//        if (fTest < psAxS->m_fDepth)
//        {
//            VEC_T(1,C)      vK0 = FCN_V(tgMH_MUL_SV)(fDS_A0, &psCY0->m_vU_HAX);
//
//            psAxS->m_vNormal = FCN_V(tgMH_SUB)( vDS, vK0 );
//            psAxS->m_fDepth = fTest;
//            psAxS->m_iAxis = 4;
//
//            psAxS->m_vNormal = FCN_V(tgMH_NORM)( psAxS->m_vNormal);
//        };
//
//        return (true);
//    };
//
//    /* -- Axis: Cylinder #1 Axis -- */
//
//    fTest = (psCY1->m_fExtent + psCY0->m_fRadius*fABS_A0xA1 + psCY0->m_fExtent*fABS_A0_A1) - FCN_F(tgPM_ABS)(fDS_A1);
//
//    if (fTest <= TYPE_K(0))
//    {
//        return (false);
//    };
//
//    if (fTest < psAxS->m_fDepth)
//    {
//        psAxS->m_vNormal = fDS_A1 > TYPE_K(0) ? FCN_V(tgMH_NEG)( psCY1->m_vU_HAX) : psCY1->m_vU_HAX;
//        psAxS->m_fDepth = fTest;
//        psAxS->m_iAxis = 2;
//    };
//
//    /* ======================================================================================= */
//
//    fDistSq = FCN_VO(tgCO_SG_ClosestSq_PM_SG)( fCA0, &fCA1, &psCY0->m_sAX, &psCY1->m_sAX);
//
//    if (fDistSq > fRadSum*fRadSum)
//    {
//        return (false);
//    };
//
//    {
//        VEC_T(1,C)        vT0, vT1;
//        VEC_OBJ_T(TgLINE)                   sLN0;
//
//        VEC_T(1,C)      vK0 = FCN_V(tgMH_MUL_SV)(fCA0, &psCY0->m_sAX.m_vDirN);
//        VEC_T(1,C)      vK1 = FCN_V(tgMH_MUL_SV)(fCA1, &psCY1->m_sAX.m_vDirN);
//        VEC_T(1,C)      vMin_CY0 = FCN_V(tgMH_ADD)( psCY0->m_sAX.m_vOrigin, vK0 );
//        VEC_T(1,C)      vMin_CY1 = FCN_V(tgMH_ADD)( psCY1->m_sAX.m_vOrigin, vK1 );
//        VEC_T(1,C)      vMinDist = FCN_V(tgMH_SUB)( vMin_CY1, vMin_CY0 );
//        VEC_T(1,C)      vMinDirN = FCN_V(tgMH_NORM)( vMinDist );
//        TgBOOL_C        bCapContact0 = FCN_F(tgCM_NR1)(fCA0) || FCN_F(tgCM_NR0)(fCA0);
//        TgBOOL_C        bCapContact1 = FCN_F(tgCM_NR1)(fCA1) || FCN_F(tgCM_NR0)(fCA1);
//
//        /* -- Axis: Between Points of Closest Proximity -- */
//
//        if (!bCapContact0 && !bCapContact1)
//        {
//            FCN_VO(tgGM_CY_Project)( fT0, &fT1, psCY0, vMinDirN );
//            FCN_VO(tgGM_CY_Project)( fT2, &fT3, psCY1, vMinDirN );
//
//            if (fT1 - fT2 < TYPE_K(0) || fT3 - fT0 < TYPE_K(0))
//            {
//                return (false);
//            };
//
//            fTest = fT2 - fT1;
//
//            if (fTest < psAxS->m_fDepth)
//            {
//                VEC_T(1,C)      vK2 = FCN_V(tgMH_MUL_SV)(psCY1->m_fRadius, vMinDirN );
//
//                psAxS->m_vPoint = FCN_V(tgMH_SUB)( vMin_CY1, vK2 );
//                psAxS->m_vNormal = vMinDirN;
//                psAxS->m_fDepth = fTest;
//                psAxS->m_iAxis = 5;
//            };
//        };
//
//        if (bCapContact0) /* If at a cylinder termini, a better axis may be the minimal direction projected on the cylinder plane. */
//        {
//            /* -- Axis: Perpendicular to Axis of Cylinder 0 -- */
//            /* Example: Rim to Cylinder contact. */
//
//            VAR_T(C)        fK0 = FCN_V(tgMH_DOT)( vMinDist, &psCY0->m_vU_Basis0);
//            VAR_T(C)        fK1 = FCN_V(tgMH_DOT)( vMinDist, &psCY0->m_vU_Basis1);
//            VEC_T(1,C)      vK2 = FCN_V(tgMH_MUL_SV)(fK0, &psCY0->m_vU_Basis0);
//            VEC_T(1,C)      vK3 = FCN_V(tgMH_MUL_SV)(fK1, &psCY0->m_vU_Basis1);
//            VEC_T(1,C)      vK4 = FCN_V(tgMH_ADD)( vK2, vK3 );
//            VEC_T(1,C)      vX0 = FCN_V(tgMH_NORM)( vK4 );
//            VAR_T(C)        fX0_A11_ABS = FCN_F(tgPM_ABS)(FCN_V(tgMH_DOT)( vX0, &psCY1->m_vU_HAX));
//            VAR_T(C)        fX0_C10 = FCN_V(tgMH_DOT)( vX0, &psCY1->m_vU_Basis0);
//            VAR_T(C)        fX0_C11 = FCN_V(tgMH_DOT)( vX0, &psCY1->m_vU_Basis1);
//            VAR_T(C)        fK2 = FCN_F(tgPM_SQRT)(fX0_C10*fX0_C10 + fX0_C11*fX0_C11);
//            VAR_T(C)        fK3 = psCY0->m_fRadius + fX0_A11_ABS*psCY1->m_fExtent;
//            VAR_T(C)        fK4 = (fK3 + fK2*psCY1->m_fRadius) - FCN_F(tgPM_ABS)(FCN_V(tgMH_DOT)( vX0, vDS ));
//
//            if (fK4 <= TYPE_K(0))
//            {
//                return (false);
//            };
//
//            if (fK4 < psAxS->m_fDepth)
//            {
//                psAxS->m_vNormal = vX0;
//                psAxS->m_fDepth = fK4;
//                psAxS->m_iAxis = 6;
//            };
//        };
//
//        if (bCapContact1) /* If at a cylinder termini, a better axis may be the minimal direction projected on the cylinder plane. */
//        {
//            /* -- Axis: Perpendicular to Axis of Cylinder 1 -- */
//            /* Example: Rim to Cylinder contact. */
//
//            VAR_T(C)        fK0 = FCN_V(tgMH_DOT)( vMinDist, &psCY1->m_vU_Basis0);
//            VAR_T(C)        fK1 = FCN_V(tgMH_DOT)( vMinDist, &psCY1->m_vU_Basis1);
//            VEC_T(1,C)      vK2 = FCN_V(tgMH_MUL_SV)(fK0, &psCY1->m_vU_Basis0);
//            VEC_T(1,C)      vK3 = FCN_V(tgMH_MUL_SV)(fK1, &psCY1->m_vU_Basis1);
//            VEC_T(1,C)      vK4 = FCN_V(tgMH_ADD)( vK2, vK3 );
//            VEC_T(1,C)      vX0 = FCN_V(tgMH_NORM)( vK4 );
//            VAR_T(C)        fX0_A01_ABS = FCN_F(tgPM_ABS)(FCN_V(tgMH_DOT)( vX0, &psCY0->m_vU_HAX));
//            VAR_T(C)        fX0_C00 = FCN_V(tgMH_DOT)( vX0, &psCY0->m_vU_Basis0);
//            VAR_T(C)        fX0_C01 = FCN_V(tgMH_DOT)( vX0, &psCY0->m_vU_Basis1);
//            VAR_T(C)        fK2 = FCN_F(tgPM_SQRT)(fX0_C00*fX0_C00 + fX0_C01*fX0_C01);
//            VAR_T(C)        fK3 = psCY1->m_fRadius + fX0_A01_ABS*psCY0->m_fExtent;
//            VAR_T(C)        fK4 = (fK3 + fK2*psCY1->m_fRadius) - FCN_F(tgPM_ABS)(FCN_V(tgMH_DOT)( vX0, vDS ));
//
//            if (fK4 <= TYPE_K(0))
//            {
//                return (false);
//            };
//
//            if (fK4 < psAxS->m_fDepth)
//            {
//                psAxS->m_vNormal = vX0;
//                psAxS->m_fDepth = fK4;
//                psAxS->m_iAxis = 7;
//            };
//        };
//
//        if (!bCapContact0 || !bCapContact1 || FCN_V(tgMH_LSQ)( vDS ) < VAR_K(KTgROOT_EPS))
//        {
//            return (true);
//        }
//        else
//        {
//            /* Construct the line of intersection between the two cylinder cap planes. */
//
//            VAR_T(C)        fA0_A1 = FCN_V(tgMH_DOT)( psCY0->m_vU_HAX, &psCY1->m_vU_HAX);
//            VAR_T(C)        fA = TYPE_K(1) - fA0_A1*fA0_A1;
//            VAR_T(C)        fInvA = TYPE_K(1) / fA;
//            VAR_T(C)        fD_CY0 = FCN_V(tgMH_DOT)( psCY0->m_vU_HAX, vMin_CY0 );
//            VAR_T(C)        fD_CY1 = FCN_V(tgMH_DOT)( psCY1->m_vU_HAX, vMin_CY1 );
//            VAR_T(C)        fK0 = (fD_CY0 - fD_CY1*fA0_A1) * fInvA;
//            VAR_T(C)        fK1 = (fD_CY1 - fD_CY0*fA0_A1) * fInvA;
//            VEC_T(1,C)      vK2 = FCN_V(tgMH_MUL_SV)(fK1, &psCY1->m_vU_HAX);
//            VEC_T(1,C)      vK3 = FCN_V(tgMH_MUL_SV)(fK0, &psCY0->m_vU_HAX);
//
//            if (fA <= VAR_K(KTgROOT_EPS))
//            {
//                return (true); /* Make sure the two planes are not co-planar. */
//            };
//
//            sLN0.m_vOrigin = FCN_V(tgMH_ADD)( vK3, vK2 );
//            sLN0.m_vDirN = FCN_V(tgMH_CX)( psCY0->m_vU_HAX, &psCY1->m_vU_HAX);
//        };
//
//        /* F_Clip the line to cylinder 0 and find the contact point */
//
//        FCN_VO(tgCO_CY_Clip_PM_LN)( fT0, &fT1, psCY0, sLN0 );
//
//        {
//            VEC_T(1,C)      vK4 = FCN_V(tgMH_MUL_SV)(fT0, &sLN0.m_vDirN);
//            VEC_T(1,C)      vK5 = FCN_V(tgMH_ADD)( sLN0.m_vOrigin, vK4 );
//            VEC_T(1,C)      vK6 = FCN_V(tgMH_SUB)( vK5, vMin_CY1 );
//
//            if (FCN_V(tgMH_LSQ)( vK6 ) >= psCY1->m_fRadiusSq)
//            {
//                VEC_T(1,C)      vK7 = FCN_V(tgMH_MUL_SV)(fT1, &sLN0.m_vDirN);
//                VEC_T(1,C)      vK8 = FCN_V(tgMH_ADD)( sLN0.m_vOrigin, vK7 );
//                VEC_T(1,C)      vK9 = FCN_V(tgMH_SUB)( vK8, vMin_CY1 );
//
//                vT0 = vK8;
//
//                if (FCN_V(tgMH_LSQ)( vK9 ) >= psCY1->m_fRadiusSq)
//                {
//                    TgWARN_CO("Not 100% that this type of thing should happen - record for test case.\n");
//                    return (false);
//                };
//            }
//            else
//            {
//                VEC_T(1,C)      vK7 = FCN_V(tgMH_MUL_SV)(fT1, &sLN0.m_vDirN);
//                VEC_T(1,C)      vK8 = FCN_V(tgMH_ADD)( sLN0.m_vOrigin, vK7 );
//                VEC_T(1,C)      vK9 = FCN_V(tgMH_SUB)( vK8, vMin_CY1 );
//
//                vT0 = vK8;
//
//                if (FCN_V(tgMH_LSQ)( vK9 ) <= psCY1->m_fRadiusSq)
//                {
//                    return (true); /* If the entire segment is contained the best axis will be axial. */
//                };
//            };
//        };
//
//        /* F_Clip the line to cylinder 1 and find the contact point */
//
//        FCN_VO(tgCO_CY_Clip_PM_LN)( fT0, &fT1, psCY1, sLN0 );
//
//        {
//            VEC_T(1,C)      vK4 = FCN_V(tgMH_MUL_SV)(fT0, &sLN0.m_vDirN);
//            VEC_T(1,C)      vK5 = FCN_V(tgMH_ADD)( sLN0.m_vOrigin, vK4 );
//            VEC_T(1,C)      vK6 = FCN_V(tgMH_SUB)( vK5, vMin_CY1 );
//
//            if (FCN_V(tgMH_LSQ)( vK6 ) >= psCY0->m_fRadiusSq)
//            {
//                VEC_T(1,C)      vK7 = FCN_V(tgMH_MUL_SV)(fT1, &sLN0.m_vDirN);
//                VEC_T(1,C)      vK8 = FCN_V(tgMH_ADD)( sLN0.m_vOrigin, vK7 );
//                VEC_T(1,C)      vK9 = FCN_V(tgMH_SUB)( vK8, vMin_CY1 );
//
//                vT1 = vK8;
//
//                if (FCN_V(tgMH_LSQ)( vK9 ) >= psCY0->m_fRadiusSq)
//                {
//                    TgWARN_CO("Not 100% that this type of thing should happen - record for test case.\n");
//                    return (false);
//                };
//            }
//            else
//            {
//                VEC_T(1,C)      vK7 = FCN_V(tgMH_MUL_SV)(fT1, &sLN0.m_vDirN);
//                VEC_T(1,C)      vK8 = FCN_V(tgMH_ADD)( sLN0.m_vOrigin, vK7 );
//                VEC_T(1,C)      vK9 = FCN_V(tgMH_SUB)( vK8, vMin_CY1 );
//
//                vT1 = vK8;
//
//                if (FCN_V(tgMH_LSQ)( vK9 ) <= psCY0->m_fRadiusSq)
//                {
//                    return (true); /* If the entire segment is contained the best axis will be axial. */
//                };
//            };
//        };
//
//        /* Construct the tangent vectors, create a mutual orthogonal vector (cross-product) - this is the separating plane normal. Essentially the construction is */
//        /* finding the (possibly unique) vector that exists in the intersection of the two sets of possible rim normals. */
//
//        {
//            VAR_T()                             fL0, fL1, fL2, fL3, fL4;
//
//            VEC_T(1,C)      vK2 = FCN_V(tgMH_SUB)( vT0, vMin_CY0 );
//            VEC_T(1,C)      vK3 = FCN_V(tgMH_SUB)( vT0, vMin_CY1 );
//            VEC_T(1,C)      vD0 = FCN_V(tgMH_CX)( vK2, &psCY0->m_vU_HAX); /* Tangent vector at rim on Cylinder 0 */
//            VEC_T(1,C)      vD1 = FCN_V(tgMH_CX)( vK3, &psCY1->m_vU_HAX); /* Tangent vector at rim on Cylinder 1 */
//            VEC_T(1,C)      vK4 = FCN_V(tgMH_UCX_LEN)( fL0, &vD0, vD1 );
//
//            if (fL0 > VAR_K(KTgROOT_EPS))
//            {
//                FCN_VO(tgGM_CY_Project)( fL1, &fL2, psCY0, vK4 );
//                FCN_VO(tgGM_CY_Project)( fL3, &fL4, psCY1, vK4 );
//
//                fL2 -= fL3;
//                fL4 -= fL1;
//
//                if (fL2 < TYPE_K(0) || fL4 < TYPE_K(0))
//                {
//                    return (false);
//                };
//
//                fTest = -FCN_F(tgCM_MIN)(fL2, fL4);
//
//                if (fTest < psAxS->m_fDepth)
//                {
//                    psAxS->m_vPoint = vT0;
//                    psAxS->m_vNormal = FCN_V(tgMH_MUL_SV)(FCN_F(tgPM_FSEL)(fL2 - fL4, -TYPE_K(1), TYPE_K(1)), vK4 );
//                    psAxS->m_fDepth = fTest;
//                    psAxS->m_iAxis = 8;
//                };
//            };
//        };
//
//        {
//            VAR_T()                             fL0, fL1, fL2, fL3, fL4;
//
//            VEC_T(1,C)      vK2 = FCN_V(tgMH_SUB)( vT1, vMin_CY0 );
//            VEC_T(1,C)      vK3 = FCN_V(tgMH_SUB)( vT1, vMin_CY1 );
//            VEC_T(1,C)      vD0 = FCN_V(tgMH_CX)( vK2, &psCY0->m_vU_HAX); /* Tangent vector at rim on Cylinder 0 */
//            VEC_T(1,C)      vD1 = FCN_V(tgMH_CX)( vK3, &psCY1->m_vU_HAX); /* Tangent vector at rim on Cylinder 1 */
//            VEC_T(1,C)      vK4 = FCN_V(tgMH_UCX_LEN)( fL0, &vD0, vD1 );
//
//            if (fL0 > VAR_K(KTgROOT_EPS))
//            {
//                FCN_VO(tgGM_CY_Project)( fL1, &fL2, psCY0, vK4 );
//                FCN_VO(tgGM_CY_Project)( fL3, &fL4, psCY1, vK4 );
//
//                fL2 -= fL3;
//                fL4 -= fL1;
//
//                if (fL2 < TYPE_K(0) || fL4 < TYPE_K(0))
//                {
//                    return (false);
//                };
//
//                fTest = -FCN_F(tgCM_MIN)(fL2, fL4);
//
//                if (fTest < psAxS->m_fDepth)
//                {
//                    psAxS->m_vPoint = vT1;
//                    psAxS->m_vNormal = FCN_V(tgMH_MUL_SV)(FCN_F(tgPM_FSEL)(fL2 - fL4, -TYPE_K(1), TYPE_K(1)), vK4 );
//                    psAxS->m_fDepth = fTest;
//                    psAxS->m_iAxis = 8;
//                };
//            };
//        };
//
//        return (true);
//    }
//}
//
//
///* ---- FCN_VO(tgCO_CY_Internal_CapCap_CY) --------------------------------------------------------------------------------------------------------------------------------------- */
///*  -- Internal Function -- (Helper to create contact points between caps of two cylinders)                                                                                        */
///* Input:  vNormal: The axis of contact being used.                                                                                                                                */
///* Input:  tgEL0: The Elliptical projection of the cylinder cap onto the plane defined by the axis of contact                                                                      */
///* Input:  psCY0: Cylinder primitive                                                                                                                                               */
///* Input:  psCY1: Cylinder primitive - contact points are generated on this primitive                                                                                              */
///* Output: sContact: An array of contact points to return for processing that will project cylinder 1 out of cylinder 0.                                                           */
///* Output: niPoint: The number of valid points in the array                                                                                                                        */
///* Return: Result Code                                                                                                                                                             */
///* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
//static TgRESULT FCN_VO(tgCO_CY_Internal_CapCap_CY)(
//    VEC_OBJ_T(STg2_CO_Contact,PU) psContact, TgSINT_F32_PC pniPoint, VEC_T(1,C) vNormal, VEC_OBJ_T(TgELLIPSE,CPC) psEL0, VEC_OBJ_T(TgTUBE,CPC) psCY0, VEC_OBJ_T(TgTUBE,CPC) psCY1 )
//{
//    TgSINT_F32                          niPoint = 0;
//    VAR_T()                             fT0, fT1;
//    VAR_T()                             fTest;
//    TgRESULT                            iResult = KTgE_NO_INTERSECT;
//    VEC_T(1,C)        vT0, vT1;
//
//    VAR_T(C)        fK0 = FCN_F(tgPM_FSEL)(FCN_V(tgMH_DOT)(pvNormal, &psCY0->m_vU_HAX), TYPE_K(1), -TYPE_K(1));
//    VAR_T(C)        fK1 = FCN_F(tgPM_FSEL)(FCN_V(tgMH_DOT)(pvNormal, &psCY1->m_vU_HAX), -TYPE_K(1), TYPE_K(1));
//    VEC_T(1,C)      vK0 = FCN_V(tgMH_MUL_SV)(fK0, &psCY0->m_vHAX);
//    VEC_T(1,C)      vK1 = FCN_V(tgMH_MUL_SV)(fK1, &psCY1->m_vHAX);
//    VEC_T(1,C)      vC0 = FCN_V(tgMH_ADD)( psCY0->m_vOrigin, vK0 );
//    VEC_T(1,C)      vC1 = FCN_V(tgMH_ADD)( psCY1->m_vOrigin, vK1 );
//
//    /* Create a reference frame for cylinder one based on the direction of deepest penetration.  To determine this reference frame the primary axis of the second cylinder */
//    /* is projected down onto the cross-sectional plane of the first cylinder. It is the angle of the second cylinder that will give us the direction of maximum */
//    /* penetration.  Once that has been determined that direction now has to be taken back into the second cylinder's reference frame to determine the result basis. */
//
//    VAR_T(C)        fK2 = -fK1*FCN_V(tgMH_DOT)( psCY0->m_vU_Basis0, &psCY1->m_vU_HAX);
//    VAR_T(C)        fK3 = -fK1*FCN_V(tgMH_DOT)( psCY0->m_vU_Basis1, &psCY1->m_vU_HAX);
//    VEC_T(1,C)      vK2 = FCN_V(tgMH_MUL_SV)(fK2, &psCY0->m_vU_Basis0);
//    VEC_T(1,C)      vK3 = FCN_V(tgMH_MUL_SV)(fK3, &psCY0->m_vU_Basis1);
//    VEC_T(1,C)      vK4 = FCN_V(tgMH_ADD)( vK2, vK3 );
//    VEC_T(1,C)      vK5 = FCN_V(tgMH_NORM_LEN)( fTest, vK4 );
//    VEC_T(1,C)      vK6 = FCN_V(tgMH_UCX)( vK5, &psCY1->m_vU_HAX);
//    VEC_T(1,C)      vK7 = FCN_V(tgMH_UCX)( vK6, &psCY1->m_vU_HAX);
//    VEC_T(1,C)      vX0 = fTest <= VAR_K(KTgEPS) ? psCY1->m_vU_Basis0 : vK7;
//    VEC_T(1,C)      vX1 = fTest <= VAR_K(KTgEPS) ? psCY1->m_vU_Basis1 : vK6;
//
//    /* Use the reference frame of cylinder 1 to create the point of deepest penetration. */
//
//    VEC_T(1,C)      vT2 = FCN_V(tgMH_MUL_SV)(psCY1->m_fRadius, vX0 );
//    VEC_T(1,C)      vK8 = FCN_V(tgMH_SUB)( vC1, vT2 );
//    VEC_T(1,C)      vK9 = FCN_V(tgMH_MUL_SV)(TYPE_K(2,0), vT2 );
//    VAR_T(C)        fABS_A0_A1 = FCN_F(tgPM_ABS)(FCN_V(tgMH_DOT)( psCY0->m_vU_HAX, &psCY1->m_vU_HAX));
//    VAR_T(C)        fFactor = -fK1 / fABS_A0_A1;
//
//    if (FCN_VO(tgCO_CY_Clip_PM_LR11)( fT0, &fT1, psCY0, &vK8, vK9 ) >= 0)
//    {
//        VEC_T(1,C)      vKA = FCN_V(tgMH_MUL_SV)(TYPE_K(2,0)*fT1 - TYPE_K(1), vT2 );
//        VEC_T(1,C)      vT3 = FCN_V(tgMH_ADD)( vC1, vKA );
//        VEC_T(1,C)      vKB = FCN_V(tgMH_SUB)( vC0, vT3 );
//        VAR_T(C)        fK4 = FCN_V(tgMH_DOT)( vKB, pvNormal);
//
//        if (fK4 > TYPE_K(0))
//        {
//            psContact[niPoint++].m_vS0 = vT3;
//            psContact[niPoint].m_fDepth = fK4;
//        };
//    };
//
//    /* At issue is the fact that the elliptical intersection routine requires the solution of a quartic equation which are known to be very unstable.  Specifically, as */
//    /* the ellipse ratios become closer to that of a full circle the intersection routine will quickly become degenerate.  Therefore, a heuristic value to determine when */
//    /* to use the elliptical routine over assuming that both caps are co-planar has to be used. Keep in mind the the math will be distinctly less prone to these problems */
//    /* on the 64bit Power architectures used in the Xbox360 and PS3.  However, the calculations will have to be kept in the floating point unit and not vectorized. */
//
//    if (fABS_A0_A1 >= VAR_K(KTgSQRT1_2))
//    {
//        if (FCN_F(tgCM_NR0)(psEL0->m_fMajor - psEL0->m_fMinor))
//        {
//            /* Use the circle routine */
//
//            VEC_OBJ_T(TgCIRCLE)                 sCI0, sCI1;
//
//            FCN_VO(tgGM_CI_Init)( sCI0, &psCY0->m_vU_Basis0, &psCY0->m_vU_HAX, &psCY0->m_vU_Basis1, &vC0, psCY0->m_fRadius);
//            FCN_VO(tgGM_CI_Init)( sCI1, &psCY1->m_vU_Basis0, &psCY1->m_vU_HAX, &psCY1->m_vU_Basis1, &vC1, psCY1->m_fRadius);
//
//            iResult = FCN_VO(tgCO_CI_Intersect2D_CI)( vT0, &vT1, &sCI0, sCI1 );
//        }
//        else
//        {
//            /* Use the elliptical routine */
//
//            VEC_OBJ_T(TgELLIPSE)                sEL1;
//
//            FCN_VO(tgGM_EL_Init)( &sEL1, &psCY0->m_vU_Basis0, &psCY0->m_vU_HAX, &psCY0->m_vU_Basis1, &vC0, psCY0->m_fRadius, psCY0->m_fRadius);
//
//            iResult = FCN_VO(tgCO_EL_Intersect2D_EL)( vT0, &vT1, &sEL1, psEL0);
//        };
//    };
//
//    if (KTgE_NO_INTERSECT == iResult)
//    {
//        /* Used the reference frame of cylinder 0 to create three symmetrical contacts around the rim/base. */
//        VEC_T(1,C)      vKA = FCN_V(tgMH_MUL_SV)(VAR_K(KTgSQRT3), vX1 );
//        VEC_T(1,C)      vKB = FCN_V(tgMH_ADD)( vX0, vKA );
//        VEC_T(1,C)      vKC = FCN_V(tgMH_MUL_SV)(psCY1->m_fRadius*-TYPE_K(0,5), vKB );
//        VEC_T(1,C)      vKD = FCN_V(tgMH_MUL_SV)(VAR_K(KTgSQRT3), vX1 );
//        VEC_T(1,C)      vKE = FCN_V(tgMH_SUB)( vX0, vKD );
//        VEC_T(1,C)      vKF = FCN_V(tgMH_MUL_SV)(psCY1->m_fRadius*-TYPE_K(0,5), vKE );
//
//        if (FCN_VO(tgCO_CY_Clip_PM_LR11)( fT0, &fT1, psCY0, &vC1, vKC ) >= 0)
//        {
//            VEC_T(1,C)      vKG = FCN_V(tgMH_MUL_SV)(fT1, vKC );
//            VEC_T(1,C)      vKH = FCN_V(tgMH_ADD)( vC1, vKG );
//            VEC_T(1,C)      vKI = FCN_V(tgMH_SUB)( vC0, vKH );
//            VAR_T(C)        fK4 = FCN_V(tgMH_DOT)( vKI, pvNormal);
//
//            if (fK4 > TYPE_K(0))
//            {
//                psContact[niPoint++].m_vS0 = vKH;
//                psContact[niPoint].m_fDepth = fK4;
//            };
//        };
//
//
//        if (FCN_VO(tgCO_CY_Clip_PM_LR11)( fT0, &fT1, psCY0, &vC1, vKF ) >= 0)
//        {
//            VEC_T(1,C)      vKG = FCN_V(tgMH_MUL_SV)(fT1, vKF );
//            VEC_T(1,C)      vKH = FCN_V(tgMH_ADD)( vC1, vKG );
//            VEC_T(1,C)      vKI = FCN_V(tgMH_SUB)( vC0, vKH );
//            VAR_T(C)        fK4 = FCN_V(tgMH_DOT)( vKI, pvNormal);
//
//            if (fK4 > TYPE_K(0))
//            {
//                psContact[niPoint++].m_vS0 = vKH;
//                psContact[niPoint].m_fDepth = fK4;
//            };
//        };
//
//        return (0 != niPoint ? KTgS_OK : KTgE_NO_INTERSECT);
//    }
//
//    if (iResult < 0)
//    {
//        TgERROR_MSG( false, u8"F_Internal_CapCap: No intersection points found between the two caps." );
//        *pniPoint = 0;
//        return (KTgE_FAIL);
//    }
//    else
//    {
//        /* Use vTo,vT1, and bisect them and create points on other side of the intersection space. */
//        VEC_T(1,C)      vKC = FCN_V(tgMH_SUB)( vT0, vC1 );
//        VEC_T(1,C)      vKD = FCN_V(tgMH_SUB)( vT1, vC1 );
//        VEC_T(1,C)      vKE = FCN_V(tgMH_ADD)( vT0, vT1 );
//        VEC_T(1,C)      vKF = FCN_V(tgMH_MUL_SV)(TYPE_K(0,5), vKE );
//        VEC_T(1,C)      vKG = FCN_V(tgMH_SUB)( vKF, vC1 );
//        VEC_T(1,C)      vT3 = FCN_V(tgMH_NORM)( vKG );
//        VEC_T(1,C)      vKH = FCN_V(tgMH_MUL_VS)( vT3, psCY1->m_fRadius);
//        VAR_T(C)        fK4 = fFactor*(FCN_V(tgMH_DOT)( vKC, &psCY1->m_vU_HAX));
//        VAR_T(C)        fK5 = fFactor*(FCN_V(tgMH_DOT)( vKD, &psCY1->m_vU_HAX));
//        VAR_T(C)        fK6 = fFactor*(FCN_V(tgMH_DOT)( vKH, &psCY1->m_vU_HAX));
//
//        if (fK4 > TYPE_K(0))
//        {
//            VEC_T(1,C)      vL2 = FCN_V(tgMH_MUL_SV)(fK0*fK4, &psCY0->m_vU_HAX);
//
//            psContact[niPoint++].m_vS0 = FCN_V(tgMH_SUB)( vT0, vL2 );
//            psContact[niPoint].m_fDepth = fK4;
//        };
//
//        if (fK5 > TYPE_K(0))
//        {
//            VEC_T(1,C)      vL2 = FCN_V(tgMH_MUL_SV)(fK0*fK5, &psCY0->m_vU_HAX);
//
//            psContact[niPoint++].m_vS0 = FCN_V(tgMH_SUB)( vT1, vL2 );
//            psContact[niPoint].m_fDepth = fK5;
//        };
//
//        if (fK6 > TYPE_K(0))
//        {
//            VEC_T(1,C)      vL0 = FCN_V(tgMH_MUL_SV)(fK0*fK6, &psCY0->m_vU_HAX);
//            VEC_T(1,C)      vL1 = FCN_V(tgMH_ADD)( vKH, vC1 );
//
//            psContact[niPoint++].m_vS0 = FCN_V(tgMH_SUB)( vL1, vL0 );
//            psContact[niPoint].m_fDepth = fK6;
//        };
//
//        *pniPoint = niPoint;
//        return (KTgS_OK);
//    };
//}
//
//
///* ---- FCN_VO(tgCO_CY_Internal_CapContained_CY) --------------------------------------------------------------------------------------------------------------------------------- */
///*  -- Internal Function -- (Helper to create contact points between caps of two cylinders, given one is entirely contained)                                                       */
///* Input:  vNormal: The axis of contact being used.                                                                                                                                */
///* Input:  psCY0: Cylinder primitive                                                                                                                                               */
///* Input:  psCY1: Cylinder primitive - contact points are generated on this primitive                                                                                              */
///* Output: sContact: An array of contact points to return for processing                                                                                                           */
///* Output: niPoint: The number of valid points in the array                                                                                                                        */
///* Return: Result Code                                                                                                                                                             */
///* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
//static TgRESULT FCN_VO(tgCO_CY_Internal_CapContained_CY)(
//    VEC_OBJ_T(STg2_CO_Contact,PU) psContact, TgSINT_F32_PC pniPoint, VEC_T(1,C) vNormal, VEC_OBJ_T(TgTUBE,CPC) psCY0, VEC_OBJ_T(TgTUBE,CPC) psCY1 )
//{
//    TgSINT_F32                          niPoint = 0;
//    VAR_T()                             fTest;
//
//    VAR_T(C)        fK0 = FCN_F(tgPM_FSEL)(FCN_V(tgMH_DOT)(pvNormal, &psCY0->m_vU_HAX), TYPE_K(1), -TYPE_K(1));
//    VAR_T(C)        fK1 = FCN_F(tgPM_FSEL)(FCN_V(tgMH_DOT)(pvNormal, &psCY1->m_vU_HAX), -TYPE_K(1), TYPE_K(1));
//    VEC_T(1,C)      vK0 = FCN_V(tgMH_MUL_SV)(fK0, &psCY0->m_vHAX);
//    VEC_T(1,C)      vK1 = FCN_V(tgMH_MUL_SV)(fK1, &psCY1->m_vHAX);
//    VEC_T(1,C)      vC0 = FCN_V(tgMH_ADD)( psCY0->m_vOrigin, vK0 );
//    VEC_T(1,C)      vC1 = FCN_V(tgMH_ADD)( psCY1->m_vOrigin, vK1 );
//
//    /* Create a reference frame for cylinder one based on the direction of deepest penetration.  To determine this reference frame the primary axis of the first cylinder */
//    /* is projected down onto the cross-sectional plane of the second cylinder. */
//
//    VAR_T(C)        fK2 = -fK1*FCN_V(tgMH_DOT)( psCY0->m_vU_Basis0, &psCY1->m_vU_HAX);
//    VAR_T(C)        fK3 = -fK1*FCN_V(tgMH_DOT)( psCY0->m_vU_Basis1, &psCY1->m_vU_HAX);
//    VEC_T(1,C)      vK2 = FCN_V(tgMH_MUL_SV)(fK2, &psCY0->m_vU_Basis0);
//    VEC_T(1,C)      vK3 = FCN_V(tgMH_MUL_SV)(fK3, &psCY0->m_vU_Basis1);
//    VEC_T(1,C)      vK4 = FCN_V(tgMH_ADD)( vK2, vK3 );
//    VEC_T(1,C)      vK5 = FCN_V(tgMH_NORM_LEN)( fTest, vK4 );
//    VEC_T(1,C)      vX0 = fTest <= VAR_K(KTgEPS) ? psCY1->m_vU_Basis0 : vK5;
//    VEC_T(1,C)      vK6 = FCN_V(tgMH_UCX)( vX0, &psCY1->m_vU_HAX);
//    VEC_T(1,C)      vX1 = fTest <= VAR_K(KTgEPS) ? psCY1->m_vU_Basis1 : vK6;
//
//    /* Used the reference frame of cylinder 1 to create three symmetrical contacts around the rim/base. */
//
//    VEC_T(1,C)      vKD = FCN_V(tgMH_MUL_SV)(VAR_K(KTgSQRT3), vX1 );
//    VEC_T(1,C)      vKE = FCN_V(tgMH_ADD)( vX0, vKD );
//    VEC_T(1,C)      vKF = FCN_V(tgMH_SUB)( vX0, vKD );
//    VEC_T(1,C)      vL0 = FCN_V(tgMH_MUL_SV)(psCY1->m_fRadius, vX0 );
//    VEC_T(1,C)      vL1 = FCN_V(tgMH_ADD)( vC1, vL0 );
//    VEC_T(1,C)      vL2 = FCN_V(tgMH_SUB)( vC0, vL1 );
//    VAR_T(C)        fK4 = FCN_V(tgMH_DOT)( vL2, pvNormal);
//    VEC_T(1,C)      vL3 = FCN_V(tgMH_MUL_SV)(psCY1->m_fRadius*-TYPE_K(0,5), vKE );
//    VEC_T(1,C)      vL4 = FCN_V(tgMH_ADD)( vC1, vL3 );
//    VEC_T(1,C)      vL5 = FCN_V(tgMH_SUB)( vC0, vL4 );
//    VAR_T(C)        fK5 = FCN_V(tgMH_DOT)( vL5, pvNormal);
//    VEC_T(1,C)      vL6 = FCN_V(tgMH_MUL_SV)(psCY1->m_fRadius*-TYPE_K(0,5), vKF );
//    VEC_T(1,C)      vL7 = FCN_V(tgMH_ADD)( vC1, vL6 );
//    VEC_T(1,C)      vL8 = FCN_V(tgMH_SUB)( vC0, vL7 );
//    VAR_T(C)        fK6 = FCN_V(tgMH_DOT)( vL8, pvNormal);
//
//    if (fK4 < TYPE_K(0))
//    {
//        TgERROR_MSG( 0, u8"F_Internal_CapContained: Axis determined a fully contained cylinder but found no contacts." );
//        *pniPoint = 0;
//        return (KTgE_FAIL);
//    };
//
//    psContact[0].m_vS0 = vL1;
//    psContact[0].m_fDepth = fK4;
//    niPoint = 1;
//
//    if (fK5 > TYPE_K(0))
//    {
//        psContact[niPoint].m_vS0 = vL4;
//        psContact[niPoint].m_fDepth = fK5;
//        ++niPoint;
//    };
//
//    if (fK6 > TYPE_K(0))
//    {
//        psContact[niPoint].m_vS0 = vL7;
//        psContact[niPoint].m_fDepth = fK6;
//        ++niPoint;
//    };
//
//    *pniPoint = niPoint;
//
//    return (KTgS_OK);
//}
//
//
///* ---- FCN_VO(tgCO_CY_Internal_AxisCap_CY) -------------------------------------------------------------------------------------------------------------------------------------- */
///*  -- Internal Function -- (Helper to create contact points between the tube and cap of two cylinders)                                                                            */
///* Input:  vNormal: The axis of contact being used.                                                                                                                                */
///* Input:  psCY0: Cylinder primitive                                                                                                                                               */
///* Input:  psCY1: Cylinder primitive - contact points are generated on this primitive                                                                                              */
///* Output: sContact: An array of contact points to return for processing                                                                                                           */
///* Output: niPoint: The number of valid points in the array                                                                                                                        */
///* Return: Result Code                                                                                                                                                             */
///* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
//static TgRESULT FCN_VO(tgCO_CY_Internal_AxisCap_CY)( VEC_OBJ_T(STg2_CO_Contact,PU) psContact, TgSINT_F32_PC pniPoint, VEC_T(1,C) vNormal, VEC_OBJ_T(TgTUBE,CPC) psCY0, VEC_OBJ_T(TgTUBE,CPC) psCY1 )
//{
//    VAR_T()                             fT0, fT1;
//
//    VAR_T(C)        fK1 = FCN_F(tgPM_FSEL)(FCN_V(tgMH_DOT)(pvNormal, &psCY1->m_vU_HAX), -TYPE_K(1), TYPE_K(1));
//    VEC_T(1,C)      vK1 = FCN_V(tgMH_MUL_SV)(fK1, &psCY1->m_vHAX);
//    VEC_T(1,C)      vC1 = FCN_V(tgMH_ADD)( psCY1->m_vOrigin, vK1 );
//
//    /* Create a reference frame for cylinder one based on the direction of deepest penetration. */
//
//    VAR_T(C)        fK2 = -fK1*FCN_V(tgMH_DOT)( psCY0->m_vU_Basis0, &psCY1->m_vU_HAX);
//    VAR_T(C)        fK3 = -fK1*FCN_V(tgMH_DOT)( psCY0->m_vU_Basis1, &psCY1->m_vU_HAX);
//    VEC_T(1,C)      vK2 = FCN_V(tgMH_MUL_SV)(fK2, &psCY0->m_vU_Basis0);
//    VEC_T(1,C)      vK3 = FCN_V(tgMH_MUL_SV)(fK3, &psCY0->m_vU_Basis1);
//    VEC_T(1,C)      vK4 = FCN_V(tgMH_ADD)( vK2, vK3 );
//    VEC_T(1,C)      vX0 = FCN_V(tgMH_NORM)( vK4 );
//    VEC_T(1,C)      vK5 = FCN_V(tgMH_MUL_SV)(psCY0->m_fRadius, vX0 );
//    VEC_T(1,C)      vS0 = FCN_V(tgMH_ADD)( psCY0->m_sAX.m_vOrigin, vK5 );
//
//    TgERROR_MSG( FCN_F(tgCM_NR1)(FCN_V(tgMH_LSQ)( vX0 )), u8"F_Internal_AxisCap: Degenerate basis set formed." );
//
//    /* Create a segment along the length of the cylinder, in the direction of deepest penetration. */
//
//    if (FCN_VO(tgCO_TB_Clip_PM_LR11)( fT0, &fT1, psCY1, &vS0, &psCY0->m_sAX.m_vDirN) < 0)
//    {
//        *pniPoint = 0;
//        return (KTgE_NO_INTERSECT);
//    }
//    else
//    {
//        VEC_OBJ_T(TgPLANE)                  sPN0;
//
//        VEC_T(1,C)      vS1 = FCN_V(tgMH_MUL_VS)( vS0, fT0);
//        VEC_T(1,C)      vD1 = FCN_V(tgMH_MUL_VS)( psCY0->m_sAX.m_vDirN, fT1 - fT0);
//
//        FCN_VO(tgGM_PN_Init_NP)( sPN0, pvNormal, vC1 );
//
//        if (FCN_VO(tgCO_PN_Clip_PM_LR11)( fT0, &fT1, &sPN0, &vS1, vD1 ) < 0)
//        {
//            *pniPoint = 0;
//            return (KTgE_NO_INTERSECT);
//        }
//        else
//        {
//            /* Segment was clipped to the cylinder surface.  Thus, the resulting point must be contained inside or on the cylinder. */
//
//            VEC_T(1,C)      vK6 = FCN_V(tgMH_MUL_SV)(fT0, &psCY0->m_sAX.m_vDirN);
//            VEC_T(1,C)      vT0 = FCN_V(tgMH_ADD)( vS0, vK6 );
//            VEC_T(1,C)      vK7 = FCN_V(tgMH_SUB)( vT0, vC1 );
//            VAR_T(C)        fK4 = FCN_V(tgMH_DOT)( vK7, pvNormal);
//            VEC_T(1,C)      vK8 = FCN_V(tgMH_MUL_SV)(fT1, &psCY0->m_sAX.m_vDirN);
//            VEC_T(1,C)      vT1 = FCN_V(tgMH_ADD)( vS0, vK8 );
//            VEC_T(1,C)      vK9 = FCN_V(tgMH_SUB)( vT1, vC1 );
//            VAR_T(C)        fK5 = FCN_V(tgMH_DOT)( vK9, pvNormal);
//
//            psContact[0].m_vS0 = fK4 - fK5 > TYPE_K(0) ? vT0 : vT1;
//            psContact[0].m_fDepth = FCN_F(tgPM_FSEL)(fK4 - fK5, fK4, fK5);
//            psContact[1].m_vS0 = fK4 - fK5 > TYPE_K(0) ? vT1 : vT0;
//            psContact[1].m_fDepth = FCN_F(tgPM_FSEL)(fK4 - fK5, fK5, fK4);
//
//            /* Always create the point of largest penetration but only use the second point if it would generate a counter-moment. */
//
//            *pniPoint = !FCN_F(tgCM_NR0)(fT0 - fT1) && ((fT0 - TYPE_K(0,5) < TYPE_K(0)) ^ (fT1 - TYPE_K(0,5) < TYPE_K(0))) ? 2 : 1;
//
//            return (KTgS_OK);
//        };
//    };
//}
//
//
///* =============================================================================================================================================================================== */
//
//#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
