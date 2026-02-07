/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Cylinder-Linear.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#if !defined (ENABLE_RELOAD_GUARD_LINEAR)
    #define ENABLE_RELOAD_GUARD_LINEAR

    #define LN_CAP_0 0
    #define LN_CAP_1 0
        #define VI(A) FCN_VO(A##00)
        #include __FILE__
        #undef VI
    #undef LN_CAP_0
    #undef LN_CAP_1

    #define LN_CAP_0 1
    #define LN_CAP_1 0
        #define VI(A) FCN_VO(A##10)
        #include __FILE__
        #undef VI
    #undef LN_CAP_0
    #undef LN_CAP_1

    #define LN_CAP_0 1
    #define LN_CAP_1 1
        #define VI(A) FCN_VO(A##11)
        #include __FILE__
        #undef VI
    #undef LN_CAP_0
    #undef LN_CAP_1

    #undef ENABLE_RELOAD_GUARD_LINEAR

/*# !defined (ENABLE_RELOAD_GUARD_LINEAR) */
#else

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

/* ---- VI(tgCO_CY_Intersect_LR) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT VI(tgCO_CY_Intersect_LR)( TgATTRIBUTE_UNUSED VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, TgATTRIBUTE_UNUSED VEC_OBJ_T(TgTUBE,CPC) psCY0,
                                   TgATTRIBUTE_UNUSED VEC_T(1,C) vS0, TgATTRIBUTE_UNUSED VEC_T(1,C) vD0 )
{
//    VAR_T()                             fLN0, fLN1;
//    VEC_T(1,C)        vN0, vN1;
//
//    TgRESULT_C iResult = FCN_VO(tgCO_CY_Internal_LR00)( fLN0, &fLN1, &vN0, &vN1, psCY0, pvS0, vD0);
//
//    if (TgFAILED( iResult ))
//    {
//        return (iResult);
//    }
//    else
//    {
//        VEC_OBJ_T(STg2_CO_Contact,P)        psContact;;
//
//        VEC_T(1,C)      vK0 = FCN_V(tgMH_MUL_SV)(fLN0, vD0);
//
//        psContact = psPacket->m_psContact + psPacket->m_nuiContact;
//
//        psContact->m_vS0 = FCN_V(tgMH_ADD)(pvS0, vK0 );
//        psContact->m_vN0 = vN0;
//        psContact->m_vT0 = fLN0;
//        psContact->m_vDepth = TYPE_K(0);
//
//        ++psPacket->m_nuiContact;
//
//        /* Check to see if the solution was tangential.  If not add the second intersection point to the packet. */
//
//        if (FCN_F(tgPM_ABS)(fLN0 - fLN1) > VAR_K(KTgEPS))
//        {
//            VEC_T(1,C)      vK1 = FCN_V(tgMH_MUL_SV)(fLN1, vD0);
//
//            if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
//            {
//                return (KTgE_MAX_CONTACTS);
//            };
//
//            psContact = psPacket->m_psContact + psPacket->m_nuiContact;
//
//            psContact->m_vS0 = FCN_V(tgMH_ADD)(pvS0, vK1 );
//            psContact->m_vN0 = vN1;
//            psContact->m_vT0 = fLN1;
//            psContact->m_vDepth = TYPE_K(0);
//
//            ++psPacket->m_nuiContact;
//        };
//    };
//
#if (defined(LN_CAP_0) && LN_CAP_0) || (defined(LN_CAP_1) && LN_CAP_1)
    return (KTgS_OK);
#else
    return (KTgS_OK);
#endif
}


/* ---- VI(tgCO_CY_Internal_PM_LR) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT VI(tgCO_CY_Internal_PM_LR)( TgATTRIBUTE_UNUSED VEC_T(1,P) pfLN0, TgATTRIBUTE_UNUSED VEC_T(1,P) pfLN1, TgATTRIBUTE_UNUSED VEC_T(1,PC) pvN0,
                                     TgATTRIBUTE_UNUSED VEC_T(1,PC) pvN1, TgATTRIBUTE_UNUSED VEC_OBJ_T(TgTUBE,CPC) psCY0, TgATTRIBUTE_UNUSED VEC_T(1,C) vS0,
                                     TgATTRIBUTE_UNUSED VEC_T(1,C) vD0 )
{
//    /* Segment in the reference frame of the cylinder */
//
//    VAR_T(C)        fD0_U0 = FCN_V(tgMH_DOT)(vD0, &psCY0->m_vU_Basis0);
//    VAR_T(C)        fD0_U1 = FCN_V(tgMH_DOT)(vD0, &psCY0->m_vU_Basis1);
//    VAR_T(C)        fD0_UA = FCN_V(tgMH_DOT)(vD0, &psCY0->m_vU_HAX);
//
//    VAR_T(C)        fA = fD0_U0*fD0_U0 + fD0_U1*fD0_U1;
//
//    /* Relative position of the origin inside of the cylinder's reference frame. */
//
//    VEC_T(1,C)      vDS = FCN_V(tgMH_SUB)(pvS0, &psCY0->m_vOrigin);
//
//    VAR_T(C)        fDS_U0 = FCN_V(tgMH_DOT)( vDS, &psCY0->m_vU_Basis0);
//    VAR_T(C)        fDS_U1 = FCN_V(tgMH_DOT)( vDS, &psCY0->m_vU_Basis1);
//    VAR_T(C)        fDS_UA = FCN_V(tgMH_DOT)( vDS, &psCY0->m_vU_HAX);
//
//    /* Relative distance of the origin on the cross-sectional plane of the cylinder. */
//
//    VAR_T(C)        fRelSq = fDS_U0*fDS_U0 + fDS_U1*fDS_U1;
//
//    if (fA + fD0_UA*fD0_UA <= VAR_K(KTgEPS))
//    {
//        return (KTgE_FAIL);
//    };
//
//    TgERROR( FCN_V(tgMH_Is_Valid_Point)(pvS0) && FCN_V(tgMH_Is_Valid_Vector)(vD0) );
//
//    if (LN_CAP_0)
//    {
//        /* If the origin lies outside of the cylinder and only moves away - intersection can not take place. */
//
//        if (FCN_F(tgPM_ABS)(fDS_UA) > psCY0->m_fExtent && !((fDS_UA > TYPE_K(0)) ^ (fD0_UA >= TYPE_K(0))))
//        {
//            return (KTgE_NO_INTERSECT);
//        };
//
//        /* If the origin lies outside of the cylinder and only moves away - intersection can not take place. */
//        /* In the radial case moving away is determined by projecting the direction onto the difference after both have been projected onto the cross-sectional plane. */
//
//        if (fRelSq > psCY0->m_fRadiusSq && (fDS_U0*fD0_U0 + fDS_U1*fD0_U1) > TYPE_K(0))
//        {
//            return (KTgE_NO_INTERSECT);
//        };
//    };
//
//
//    /* Branch for the case where the segment is perpendicular to the cylinder's cross-sectional plane. */
//
//    if (FCN_F(tgCM_NR0)(fA))
//    {
//        VAR_T(C)        fInvTMP = TYPE_K(1) / fD0_UA;
//        VAR_T(C)        fT0 = (-psCY0->m_fExtent - fDS_UA) * fInvTMP;
//        VAR_T(C)        fT1 = (psCY0->m_fExtent - fDS_UA) * fInvTMP;
//
//        if (fRelSq >= psCY0->m_fRadiusSq)
//        {
//            return (KTgE_NO_INTERSECT);
//        };
//
//        if (fT0 < fT1)
//        {
//            *pfLN0 = fT0;
//            *pfLN1 = fT1;
//            *pvN0 = FCN_V(tgMH_NEG)( psCY0->m_vU_HAX);
//            *pvN1 = psCY0->m_vU_HAX;
//        }
//        else
//        {
//            *pfLN0 = fT1;
//            *pfLN1 = fT0;
//            *pvN0 = psCY0->m_vU_HAX;
//            *pvN1 = FCN_V(tgMH_NEG)( psCY0->m_vU_HAX);
//        };
//
//        return (KTgS_OK);
//    };
//
//
//    /* Branch for the case where the segment is parallel to the cylinder's cross-sectional plane. */
//
//    if (FCN_F(tgCM_NR0)(fD0_UA))
//    {
//        /* The following assumes that D0_UA is exactly zero, instead of just being approximately close to it.  This allows for some fast math, avoiding the entire need */
//        /* to project the segment onto the plane.  The minor error this may cause should be negligible. */
//
//        /* Solve the planar problem. (DS_U0 + ζ•D0_U0)² + (DS_U1 + ζ•D0_U1)² = R² */
//        /* DS_U0•DS_U0 + 2•ζ•DS_U0•D0_U0 + ζ•ζ•D0_U0•D0_U0 + DS_U1•DS_U1 + 2•ζ•DS_U1•D0_U1 + ζ•ζ•D0_U1•D0_U1 = R² */
//        /* ζ•ζ_(D0_U0•D0_U0 + D0_U1•D0_U1,DIM) + ζ_(2•DS_U0•D0_U0 + 2•DS_U1•D0_U1,DIM) + DS_U0•DS_U0 + DS_U1•DS_U1 - R² = 0 */
//
//        VAR_T(C)        fHalfNegB = -TYPE_K(1) * (fDS_U0*fD0_U0 + fDS_U1*fD0_U1);
//        VAR_T(C)        fC = fRelSq - psCY0->m_fRadiusSq;
//        VAR_T(C)        fDet = fHalfNegB*fHalfNegB - fA*fC;
//
//        VAR_T(C)        fDetSqrt = FCN_F(tgPM_SQRT)(fDet);
//        VAR_T(C)        fInvA = TYPE_K(1) / fA;
//        VAR_T(C)        fT0 = (fHalfNegB - fDetSqrt) * fInvA;
//        VAR_T(C)        fT1 = (fHalfNegB + fDetSqrt) * fInvA;
//
//        /* Check to see if the line lies outside of the cylinder's extents. */
//
//        if (FCN_F(tgPM_ABS)(fDS_UA) > psCY0->m_fExtent)
//        {
//            return (KTgE_NO_INTERSECT);
//        };
//
//        if (fDet < TYPE_K(0))
//        {
//            return (KTgE_NO_INTERSECT);
//        }
//
//        if (fT0 < fT1)
//        {
//            VEC_T(1,C)      vK0 = FCN_V(tgMH_MUL_SV)(fDS_U0 + fT0*fD0_U0, &psCY0->m_vU_Basis0);
//            VEC_T(1,C)      vK1 = FCN_V(tgMH_MUL_SV)(fDS_U1 + fT0*fD0_U1, &psCY0->m_vU_Basis1);
//            VEC_T(1,C)      vK2 = FCN_V(tgMH_MUL_SV)(fDS_U0 + fT1*fD0_U0, &psCY0->m_vU_Basis0);
//            VEC_T(1,C)      vK3 = FCN_V(tgMH_MUL_SV)(fDS_U1 + fT1*fD0_U1, &psCY0->m_vU_Basis1);
//            VEC_T(1,C)      vK4 = FCN_V(tgMH_ADD)( vK0, vK1 );
//            VEC_T(1,C)      vK5 = FCN_V(tgMH_ADD)( vK2, vK3 );
//
//            *pfLN0 = fT0;
//            *pfLN1 = fT1;
//            *pvN0 = FCN_V(tgMH_NORM)( vK4 );
//            *pvN1 = FCN_V(tgMH_NORM)( vK5 );
//        }
//        else
//        {
//            VEC_T(1,C)      vK0 = FCN_V(tgMH_MUL_SV)(fDS_U0 + fT1*fD0_U0, &psCY0->m_vU_Basis0);
//            VEC_T(1,C)      vK1 = FCN_V(tgMH_MUL_SV)(fDS_U1 + fT1*fD0_U1, &psCY0->m_vU_Basis1);
//            VEC_T(1,C)      vK2 = FCN_V(tgMH_MUL_SV)(fDS_U0 + fT0*fD0_U0, &psCY0->m_vU_Basis0);
//            VEC_T(1,C)      vK3 = FCN_V(tgMH_MUL_SV)(fDS_U1 + fT0*fD0_U1, &psCY0->m_vU_Basis1);
//            VEC_T(1,C)      vK4 = FCN_V(tgMH_ADD)( vK0, vK1 );
//            VEC_T(1,C)      vK5 = FCN_V(tgMH_ADD)( vK2, vK3 );
//
//            *pfLN0 = fT1;
//            *pfLN1 = fT0;
//            *pvN0 = FCN_V(tgMH_NORM)( vK4 );
//            *pvN1 = FCN_V(tgMH_NORM)( vK5 );
//        };
//
//        return (KTgS_OK);
//    }
//    else
//    {
//        /* For the sake of speed, attempt to clip the line using only the cap planes. */
//
//        VAR_T(C)        fInvTMP = TYPE_K(1) / fD0_UA;
//        TgBOOL                              bCapClip = false;
//
//        VAR_T()                             fT0 = TYPE_K(0);
//
//        VAR_T(C)        fPLN0 = (-psCY0->m_fExtent - fDS_UA) * fInvTMP;
//        VAR_T(C)        fPLN1 = (psCY0->m_fExtent - fDS_UA) * fInvTMP;
//
//        VAR_T(C)        fU0 = fDS_U0 + fPLN0 * fD0_U0;
//        VAR_T(C)        fV0 = fDS_U1 + fPLN0 * fD0_U1;
//        VAR_T(C)        fU1 = fDS_U0 + fPLN1 * fD0_U0;
//        VAR_T(C)        fV1 = fDS_U1 + fPLN1 * fD0_U1;
//
//        if (fU0*fU0 + fV0*fV0 <= psCY0->m_fRadiusSq)
//        {
//            if (fU1*fU1 + fV1*fV1 <= psCY0->m_fRadiusSq)
//            {
//                if (fPLN0 < fPLN1)
//                {
//                    *pfLN0 = fPLN0;
//                    *pfLN1 = fPLN1;
//                    *pvN0 = FCN_V(tgMH_NEG)( psCY0->m_vU_HAX);
//                    *pvN1 = psCY0->m_vU_HAX;
//                }
//                else
//                {
//                    *pfLN0 = fPLN1;
//                    *pfLN1 = fPLN0;
//                    *pvN0 = psCY0->m_vU_HAX;
//                    *pvN1 = FCN_V(tgMH_NEG)( psCY0->m_vU_HAX);
//                };
//
//                return (KTgS_OK);
//            }
//
//            bCapClip = true;
//
//            fT0 = fPLN0;
//            *pvN0 = FCN_V(tgMH_NEG)( psCY0->m_vU_HAX);
//        }
//        else if (fU1*fU1 + fV1*fV1 <= psCY0->m_fRadiusSq)
//        {
//            bCapClip = true;
//
//            fT0 = fPLN1;
//            *pvN0 = psCY0->m_vU_HAX;
//        };
//
//        /* The segment may intersect the cylinder walls */
//
//        /* Solve the planar problem. (DS_U0 + ζ•D0_U0)² + (DS_U1 + ζ•D0_U1)² = R² */
//        /* DS_U0•DS_U0 + 2•ζ•DS_U0•D0_U0 + ζ•ζ•D0_U0•D0_U0 + DS_U1•DS_U1 + 2•ζ•DS_U1•D0_U1 + ζ•ζ•D0_U1•D0_U1 = R² */
//        /* ζ•ζ_(D0_U0•D0_U0 + D0_U1•D0_U1,DIM) + ζ_(2•DS_U0•D0_U0 + 2•DS_U1•D0_U1,DIM) + DS_U0•DS_U0 + DS_U1•DS_U1 - R² = 0 */
//
//        {
//            VAR_T(C)        fHalfNegB = -TYPE_K(1) * (fDS_U0*fD0_U0 + fDS_U1*fD0_U1);
//            VAR_T(C)        fC = fRelSq - psCY0->m_fRadiusSq;
//            VAR_T(C)        fDet = fHalfNegB*fHalfNegB - fC*fA;
//            VAR_T(C)        fInvA = TYPE_K(1) / fA;
//            VAR_T(C)        fDetSqrt = FCN_F(tgPM_SQRT)(fDet);
//            VAR_T(C)        fTA = (fHalfNegB - fDetSqrt) * fInvA;
//            VAR_T(C)        fTB = (fHalfNegB + fDetSqrt) * fInvA;
//
//            if (fDet < TYPE_K(0))
//            {
//                TgERROR(!bCapClip);
//                return (KTgE_NO_INTERSECT);
//            }
//
//            /* Only process the point if the contact is bound by the two cap-planes. */
//
//            if (bCapClip)
//            {
//
//                VAR_T(C)        fT1 = (fPLN0 <= fTA && fTA <= fPLN1) ? fTA : fTB;
//
//                TgERROR( (fPLN0 <= fTA && fTA <= fPLN1) ^ (fPLN0 <= fTB && fTB <= fPLN1) );
//
//                if (fT0 < fT1)
//                {
//                    VEC_T(1,C)      vK0 = FCN_V(tgMH_MUL_SV)(fDS_U0 + fT1*fD0_U0, &psCY0->m_vU_Basis0);
//                    VEC_T(1,C)      vK1 = FCN_V(tgMH_MUL_SV)(fDS_U1 + fT1*fD0_U1, &psCY0->m_vU_Basis1);
//                    VEC_T(1,C)      vK2 = FCN_V(tgMH_ADD)( vK0, vK1 );
//
//                    *pfLN0 = fT0;
//                    *pfLN1 = fT1;
//                    *pvN1 = FCN_V(tgMH_NORM)( vK2 );
//                }
//                else
//                {
//                    VEC_T(1,C)      vK0 = FCN_V(tgMH_MUL_SV)(fDS_U0 + fT1*fD0_U0, &psCY0->m_vU_Basis0);
//                    VEC_T(1,C)      vK1 = FCN_V(tgMH_MUL_SV)(fDS_U1 + fT1*fD0_U1, &psCY0->m_vU_Basis1);
//                    VEC_T(1,C)      vK2 = FCN_V(tgMH_ADD)( vK0, vK1 );
//
//                    *pfLN0 = fT1;
//                    *pfLN1 = fT0;
//                    *pvN1 = *pvN0;
//                    *pvN0 = FCN_V(tgMH_NORM)( vK2 );
//                };
//            }
//            else
//            {
//                if ((fPLN0 > fTB || fTB > fPLN1) && (fPLN0 > fTA || fTA > fPLN1))
//                {
//                    /*return (KTgE_NO_INTERSECT); */
//                };
//
//                /*TgERROR( fPLN0 <= fTA && fTA <= fPLN1 && fPLN0 <= fTB && fTB <= fPLN1 ); */
//
//                if (fTA < fTB)
//                {
//                    VEC_T(1,C)      vK0 = FCN_V(tgMH_MUL_SV)(fDS_U0 + fTA*fD0_U0, &psCY0->m_vU_Basis0);
//                    VEC_T(1,C)      vK1 = FCN_V(tgMH_MUL_SV)(fDS_U1 + fTA*fD0_U1, &psCY0->m_vU_Basis1);
//                    VEC_T(1,C)      vK2 = FCN_V(tgMH_MUL_SV)(fDS_U0 + fTB*fD0_U0, &psCY0->m_vU_Basis0);
//                    VEC_T(1,C)      vK3 = FCN_V(tgMH_MUL_SV)(fDS_U1 + fTB*fD0_U1, &psCY0->m_vU_Basis1);
//                    VEC_T(1,C)      vK4 = FCN_V(tgMH_ADD)( vK0, vK1 );
//                    VEC_T(1,C)      vK5 = FCN_V(tgMH_ADD)( vK2, vK3 );
//
//                    *pfLN0 = fTA;
//                    *pfLN1 = fTB;
//                    *pvN0 = FCN_V(tgMH_NORM)( vK4 );
//                    *pvN1 = FCN_V(tgMH_NORM)( vK5 );
//                }
//                else
//                {
//                    VEC_T(1,C)      vK0 = FCN_V(tgMH_MUL_SV)(fDS_U0 + fTB*fD0_U0, &psCY0->m_vU_Basis0);
//                    VEC_T(1,C)      vK1 = FCN_V(tgMH_MUL_SV)(fDS_U1 + fTB*fD0_U1, &psCY0->m_vU_Basis1);
//                    VEC_T(1,C)      vK2 = FCN_V(tgMH_MUL_SV)(fDS_U0 + fTA*fD0_U0, &psCY0->m_vU_Basis0);
//                    VEC_T(1,C)      vK3 = FCN_V(tgMH_MUL_SV)(fDS_U1 + fTA*fD0_U1, &psCY0->m_vU_Basis1);
//                    VEC_T(1,C)      vK4 = FCN_V(tgMH_ADD)( vK0, vK1 );
//                    VEC_T(1,C)      vK5 = FCN_V(tgMH_ADD)( vK2, vK3 );
//
//                    *pfLN0 = fTB;
//                    *pfLN1 = fTA;
//                    *pvN0 = FCN_V(tgMH_NORM)( vK4 );
//                    *pvN1 = FCN_V(tgMH_NORM)( vK5 );
//                };
//            };
//
            return (KTgS_OK);
//        };
//    };
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/*# !defined (ENABLE_RELOAD_GUARD_LINEAR) */
#endif
