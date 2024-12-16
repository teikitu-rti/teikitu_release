/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Tube-Linear.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#if !defined (ENABLE_RELOAD_GUARD_LINEAR)
    #define ENABLE_RELOAD_GUARD_LINEAR

    TgMSVC_WARN_DISABLE_PUSH(4702) /* unreachable code. */

    #define TEMPLATE__PRIM_0_CAP_0 0
    #define TEMPLATE__PRIM_0_CAP_1 0
    #define TEMPLATE__PRIM_0 TB
    #define TEMPLATE__PRIM_1_CAP_0 0
    #define TEMPLATE__PRIM_1_CAP_1 0
    #define TEMPLATE__PRIM_1 LR
        #include __FILE__

    #define TEMPLATE__PRIM_0_CAP_0 0
    #define TEMPLATE__PRIM_0_CAP_1 0
    #define TEMPLATE__PRIM_0 TB
    #define TEMPLATE__PRIM_1_CAP_0 1
    #define TEMPLATE__PRIM_1_CAP_1 0
    #define TEMPLATE__PRIM_1 LR
        #include __FILE__

    #define TEMPLATE__PRIM_0_CAP_0 0
    #define TEMPLATE__PRIM_0_CAP_1 0
    #define TEMPLATE__PRIM_0 TB
    #define TEMPLATE__PRIM_1_CAP_0 1
    #define TEMPLATE__PRIM_1_CAP_1 1
    #define TEMPLATE__PRIM_1 LR
        #include __FILE__

    #define TEMPLATE__PRIM_0_CAP_0 1
    #define TEMPLATE__PRIM_0_CAP_1 0
    #define TEMPLATE__PRIM_0 TB
    #define TEMPLATE__PRIM_1_CAP_0 0
    #define TEMPLATE__PRIM_1_CAP_1 0
    #define TEMPLATE__PRIM_1 LR
        #include __FILE__

    #define TEMPLATE__PRIM_0_CAP_0 1
    #define TEMPLATE__PRIM_0_CAP_1 0
    #define TEMPLATE__PRIM_0 TB
    #define TEMPLATE__PRIM_1_CAP_0 1
    #define TEMPLATE__PRIM_1_CAP_1 0
    #define TEMPLATE__PRIM_1 LR
        #include __FILE__

    #define TEMPLATE__PRIM_0_CAP_0 1
    #define TEMPLATE__PRIM_0_CAP_1 0
    #define TEMPLATE__PRIM_0 TB
    #define TEMPLATE__PRIM_1_CAP_0 1
    #define TEMPLATE__PRIM_1_CAP_1 1
    #define TEMPLATE__PRIM_1 LR
        #include __FILE__

    #define TEMPLATE__PRIM_0_CAP_0 1
    #define TEMPLATE__PRIM_0_CAP_1 1
    #define TEMPLATE__PRIM_0 TB
    #define TEMPLATE__PRIM_1_CAP_0 0
    #define TEMPLATE__PRIM_1_CAP_1 0
    #define TEMPLATE__PRIM_1 LR
        #include __FILE__

    #define TEMPLATE__PRIM_0_CAP_0 1
    #define TEMPLATE__PRIM_0_CAP_1 1
    #define TEMPLATE__PRIM_0 TB
    #define TEMPLATE__PRIM_1_CAP_0 1
    #define TEMPLATE__PRIM_1_CAP_1 0
    #define TEMPLATE__PRIM_1 LR
        #include __FILE__

    #define TEMPLATE__PRIM_0_CAP_0 1
    #define TEMPLATE__PRIM_0_CAP_1 1
    #define TEMPLATE__PRIM_0 TB
    #define TEMPLATE__PRIM_1_CAP_0 1
    #define TEMPLATE__PRIM_1_CAP_1 1
    #define TEMPLATE__PRIM_1 LR
        #include __FILE__

    TgMSVC_WARN_DISABLE_POP(4702)

    #undef ENABLE_RELOAD_GUARD_LINEAR

/*# !defined (ENABLE_RELOAD_GUARD_LINEAR) */
#else

#if !defined (ENABLE_RELOAD_GUARD)
    #define TEMPLATE__VECTOR_DIM 4

    #if TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE
        #define ENABLE_RELOAD_GUARD
        #define TEMPLATE__TYPE_SIZE 64
        #include __FILE__
        #undef TEMPLATE__TYPE_SIZE
        #undef ENABLE_RELOAD_GUARD
    #endif

    #define TEMPLATE__TYPE_SIZE 32
#endif

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"


/* Validation check */
#if (!TEMPLATE__PRIM_0_CAP_0 && TEMPLATE__PRIM_0_CAP_1) || (!TEMPLATE__PRIM_1_CAP_0 && TEMPLATE__PRIM_1_CAP_1)
    #error Invalid Configuration
#endif


/* == Collision ================================================================================================================================================================== */

/* ---- FCNI_VO(tgCO,Param) ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCNI_VO(tgCO,Param)( VEC_T(1,PC) pvLN0, VEC_T(1,PC) pvLN1, VEC_T(1,PC) pvN0, VEC_T(1,PC) pvN1, VEC_T(1,C) vPad, VEC_OBJ_T(TgTUBE,CPC) psTB0, VEC_T(1,C) vS0,
                                 VEC_T(1,C) vD0 )
{
    VEC_T(1)                            vTB0_UX[3], vTB0_OG;
    TgBOOL                              bValid_0, bValid_1;

    TgERROR( FCN_VO(tgGM_TB_Is_Valid)( psTB0 ) && FCN_V(tgMH_Is_Valid_Point)( vS0 ) && FCN_V(tgMH_Is_Valid_Vector)( vD0 ) );

    /* Project the linear onto the tube's cross-sectional plane (the plane defined by using the primary axis as a normal). Solve for when the lines crosses the circle of the tube
       on the plane. Take into account the case where the line direction is parallel to the normal. */

    /* R² = (DS_U0 + ζ•D0_U0)² + (DS_U1 + ζ•D0_U1)²
       R² = DS_U0•DS_U0 + 2•ζ•DS_U0•D0_U0 + ζ•ζ•D0_U0•D0_U0 + DS_U1•DS_U1 + 2•ζ•DS_U1•D0_U1 + ζ•ζ•D0_U1•D0_U1
       0  = ζ•ζ•(D0_U0•D0_U0 + D0_U1•D0_U1) + ζ•(2•DS_U0•D0_U0 + 2•DS_U1•D0_U1) + DS_U0•DS_U0 + DS_U1•DS_U1 - R²

       Let α = D0_U0•D0_U0 + D0_U1•D0_U1, β = DS_U0•D0_U0 + DS_U1•D0_U1, γ = DS_U0•DS_U0 + DS_U1•DS_U1 - R²
       Then, 0 = ζ•ζ•α + ζ•2•β + γ and it follows that
       ζ = (-(2•β) ± √((2•β)² - 4•α•γ)) / 2•α
       ζ = (-β ± √(β² - α•γ)) / α
    */

    FCN_V(tgMH_Query_Reference_Frame,3)( vTB0_UX + 0, vTB0_UX + 1, vTB0_UX + 2, &vTB0_OG, &psTB0->m_mReference_Frame );

    {
        /* Linear direction inside of the tube's reference frame. */

        VEC_T(1,C)                          vD0_U0 = FCN_V(tgMH_DOT)( vD0, vTB0_UX[0] );
        VEC_T(1,C)                          vD0_U1 = FCN_V(tgMH_DOT)( vD0, vTB0_UX[2] );
        VEC_T(1,C)                          vD0_UA = FCN_V(tgMH_DOT)( vD0, vTB0_UX[1] );

        /* Linear origin inside of the tube's reference frame. */

        VEC_T(1,C)                          vDS = FCN_V(tgMH_SUB)( vS0, vTB0_OG );

        VEC_T(1,C)                          vDS_U0 = FCN_V(tgMH_DOT)( vDS, vTB0_UX[0] );
        VEC_T(1,C)                          vDS_U1 = FCN_V(tgMH_DOT)( vDS, vTB0_UX[2] );
        VEC_T(1,C)                          vDS_UA = FCN_V(tgMH_DOT)( vDS, vTB0_UX[1] );

        /* Calculate the quadratic equation coefficients. */

        VEC_T(1,C)                          vRad = FCN_V(tgMH_ADD)( psTB0->m_vRadius, vPad );
        VEC_T(1,C)                          vRadSq = FCN_V(tgMH_MUL)( vRad, vRad );

        VEC_T(1,C)                          vX0 = FCN_V(tgMH_MUL)( vD0_U1, vD0_U1 );
        VEC_T(1,C)                          vA = FCN_V(tgMH_MAD)( vD0_U0, vD0_U0, vX0 );
        VEC_T(1,C)                          vX1 = FCN_V(tgMH_MUL)( vDS_U1, vD0_U1 );
        VEC_T(1,C)                          vB = FCN_V(tgMH_MAD)( vDS_U0, vD0_U0, vX1 );
        VEC_T(1,C)                          vX2 = FCN_V(tgMH_MUL)( vDS_U1, vDS_U1 );
        VEC_T(1,C)                          vX3 = FCN_V(tgMH_MAD)( vDS_U0, vDS_U0, vX2 );
        VEC_T(1,C)                          vNeg_C = FCN_V(tgMH_SUB)( vRadSq, vX3  );
    
        /* Check to see if the linear is parallel to the tube's primary axis */
        if (FCN_V(tgMH_Is_NR0)( vA ))
        {
            if (!FCN_V(tgMH_Is_NR0)( vNeg_C ))
            {
                return (KTgE_NO_INTERSECT);
            }
            else
            {
                /* There are a total of 9 possible permutations to examine. The overlap test can be restricted to a 1 dimensional test between the two linear objects. */
        
                /* 5/9 of the possible cases: 1: (-∞,∞), (-∞,∞), 2: (-∞,∞), (0,∞), 3: (-∞,∞), (0,1), 4: (0,∞), (-∞,∞), 5: (0,1), (-∞,∞) */
            #if (!TEMPLATE__PRIM_0_CAP_0 && !TEMPLATE__PRIM_0_CAP_1) || (!TEMPLATE__PRIM_1_CAP_0 && !TEMPLATE__PRIM_1_CAP_1)
                return (KTgE_TANGENT);
            #endif

            #if (TEMPLATE__PRIM_0_CAP_0 && !TEMPLATE__PRIM_0_CAP_1)
                #if (TEMPLATE__PRIM_1_CAP_0 && !TEMPLATE__PRIM_1_CAP_1)
                /* Case 6: (0,∞), (0,∞) -> DS_UA >= -Extent || D0_UA > 0 */
                VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_GE)( vDS_UA, FCN_V(tgMH_NEG)( psTB0->m_vExtent ) );
                VEC_T(1,C)                          vCMP_1 = FCN_V(tgMH_CMP_GT)( vD0_UA, FCN_V(tgMH_SET1)( TYPE_K(0) ) );

                return (FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_0 ) || FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_1 ));
                #endif
                #if (TEMPLATE__PRIM_1_CAP_0 &&  TEMPLATE__PRIM_1_CAP_1)
                /* Case 7: (0,∞), (0,1) -> DS_UA > -Extent || DS_UA + D0_UA > -Extent */
                VEC_T(1,C)                          vNegExtent = FCN_V(tgMH_NEG)( psTB0->m_vExtent );
                VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_GE)( vDS_UA, vNegExtent );
                VEC_T(1,C)                          vG1_UA = FCN_V(tgMH_ADD)( vDS_UA, vD0_UA );
                VEC_T(1,C)                          vCMP_1 = FCN_V(tgMH_CMP_GE)( vG1_UA, vNegExtent );

                return (FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_0 ) || FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_1 ));
                #endif
            #endif

            #if (TEMPLATE__PRIM_0_CAP_0 &&  TEMPLATE__PRIM_0_CAP_1)
                #if (TEMPLATE__PRIM_1_CAP_0 && !TEMPLATE__PRIM_1_CAP_1)
                /* Case 8: (0,1), (0,∞) -> (DS_UA >= -Extent || D0_UA > 0) && (DS_UA <= Extent || D0_UA < 0) */
                VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_GE)( vDS_UA, FCN_V(tgMH_NEG)( psTB0->m_vExtent ) );
                VEC_T(1,C)                          vCMP_1 = FCN_V(tgMH_CMP_GT)( vD0_UA, FCN_V(tgMH_SET1)( TYPE_K(0) ) );
                VEC_T(1,C)                          vCMP_2 = FCN_V(tgMH_CMP_LE)( vDS_UA, psTB0->m_vExtent );
                TgBOOL_C        bCMP_1 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_1 );

                return ((FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_0 ) || bCMP_1) && (FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_2 ) || !bCMP_1));
                #endif
                #if (TEMPLATE__PRIM_1_CAP_0 &&  TEMPLATE__PRIM_1_CAP_1)
                /* Case 9: (0,1), (0,1) -> DS_UA + D0_UA >= -Extent && DS_UA <= Extent */
                VEC_T(1,C)                          vG1_UA = FCN_V(tgMH_ADD)( vDS_UA, vD0_UA );
                VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_GE)( vG1_UA, FCN_V(tgMH_NEG)( psTB0->m_vExtent ) );
                VEC_T(1,C)                          vCMP_1 = FCN_V(tgMH_CMP_LE)( vDS_UA, psTB0->m_vExtent );

                return (FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_0 ) && FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_1 ));
                #endif
            #endif

                return (KTgE_NO_INTERSECT);
            };
        }
        else
        {
            VEC_T(1,C)                          vDSC = FCN_V(tgMH_MAD)( vA, vNeg_C, FCN_V(tgMH_MUL)( vX3, vX3 ) );
            VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_LT)( vDSC, FCN_V(tgMH_SET1)( -VAR_K(KTgROOT_EPS) ) );

            /* Imaginary roots - there is no intersection between the linear object and the tube */

            if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_0 ))
            {
                return (KTgE_NO_INTERSECT);
            }
            else
            {
                /* Calculate the two roots to the equation */

                VEC_T(1,C)                          vDSC_Sqrt = FCN_V(tgMH_SQRT)( vDSC );
                VEC_T(1,C)                          vF0 = FCN_V(tgMH_NEG)( vB );
                VEC_T(1,C)                          vF1 = FCN_V(tgMH_SUB)( vF0, vDSC_Sqrt );
                VEC_T(1,C)                          vF2 = FCN_V(tgMH_DIV)( vF1, vA );
                VEC_T(1,C)                          vF3 = FCN_V(tgMH_ADD)( vF0, vDSC_Sqrt );
                VEC_T(1,C)                          vF4 = FCN_V(tgMH_DIV)( vF3, vA );

                /* Generate the two points of intersection */
    
                VEC_T(1,C)                          vG0_U0 = FCN_V(tgMH_MAD)( vF2, vD0_U0, vDS_U0 );
                VEC_T(1,C)                          vG0_U1 = FCN_V(tgMH_MAD)( vF2, vD0_U1, vDS_U1 );
                VEC_T(1,C)                          vG0 = FCN_V(tgMH_ADD)( vG0_U0, vG0_U1 );

                VEC_T(1,C)                          vG1_U0 = FCN_V(tgMH_MAD)( vF4, vD0_U0, vDS_U0 );
                VEC_T(1,C)                          vG1_U1 = FCN_V(tgMH_MAD)( vF4, vD0_U1, vDS_U1 );
                VEC_T(1,C)                          vG1 = FCN_V(tgMH_ADD)( vG1_U0, vG1_U1 );

                VEC_T(1,C)                          vG0_UA = FCN_V(tgMH_MAD)( vF2, vD0_UA, vDS_UA );
                VEC_T(1,C)                          vG1_UA = FCN_V(tgMH_MAD)( vF4, vD0_UA, vDS_UA );

                bValid_0 = true;
                bValid_1 = true;

                /* Check to see if it is within the extents of the tube */
                bValid_0 &= !(TEMPLATE__PRIM_0_CAP_1 && FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GE)( vG0_UA, psTB0->m_vExtent ) ));
                bValid_0 &= !(TEMPLATE__PRIM_0_CAP_0 && FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( vG0_UA, FCN_V(tgMH_NEG)( psTB0->m_vExtent ) ) ));
                bValid_1 &= !(TEMPLATE__PRIM_0_CAP_1 && FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GE)( vG1_UA, psTB0->m_vExtent ) ));
                bValid_1 &= !(TEMPLATE__PRIM_0_CAP_0 && FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( vG1_UA, FCN_V(tgMH_NEG)( psTB0->m_vExtent ) ) ));

                /* Check to see if it is within the extents of the tube */
                bValid_0 &= !(TEMPLATE__PRIM_1_CAP_1 && FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GE)( vF2, FCN_V(tgMH_SET1)( TYPE_K(1) ) ) ));
                bValid_0 &= !(TEMPLATE__PRIM_1_CAP_0 && FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( vF2, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ));
                bValid_1 &= !(TEMPLATE__PRIM_1_CAP_1 && FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GE)( vF4, FCN_V(tgMH_SET1)( TYPE_K(1) ) ) ));
                bValid_1 &= !(TEMPLATE__PRIM_1_CAP_0 && FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( vF4, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ));

                if (bValid_0 && bValid_1)
                {
                    *pvLN0 = vF2;
                    *pvN0 = FCN_V(tgMH_NORM)( vG0 );
                    *pvLN1 = vF4;
                    *pvN1 = FCN_V(tgMH_NORM)( vG1 );

                    return (KTgS_OK);
                }

                if (bValid_0)
                {
                    *pvLN0 = *pvLN1 = vF2;
                    *pvN0 = *pvN1 = FCN_V(tgMH_NORM)( vG0 );

                    return (KTgS_OK);
                }

                if (bValid_1)
                {
                    *pvLN0 = *pvLN1 = vF4;
                    *pvN0 = *pvN1 = FCN_V(tgMH_NORM)( vG1 );

                    return (KTgS_OK);
                }

                return (KTgE_NO_INTERSECT);
            };
        };
    };
}


/* ---- FCNI_VO(tgCO,Intersect) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCNI_VO(tgCO,Intersect)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_T(1,C) vPad, VEC_OBJ_T(TgTUBE,CPC) psTB0, VEC_T(1,C) vS0, VEC_T(1,C) vD0 )
{
    VEC_T(1)                            vLN0, vLN1, vN0, vN1;
    VEC_OBJ_T(STg2_CO_Contact,P)        psContact;
    TgRESULT                            iResult;

    /* Check to make sure that a valid contact, and contact packet exist. */

    if (0 == psPacket->m_nuiMaxContact || nullptr == psPacket->m_psContact)
    {
        return (KTgE_FAIL);
    };

    iResult = FCNI_VO(tgCO,Param)( &vLN0, &vLN1, &vN0, &vN1, vPad, psTB0, vS0, vD0 );

    if (TgFAILED( iResult ))
    {
        return (iResult);
    };

    if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
    {
        return (KTgE_MAX_CONTACTS);
    };

    psContact = psPacket->m_psContact + psPacket->m_nuiContact;

    psContact->m_vS0 = FCN_V(tgMH_MAD)( vLN0, vD0, vS0 );
    psContact->m_vN0 = vN0;
    psContact->m_vT0 = vLN0;
    psContact->m_vDepth = FCN_V(tgMH_SET1)( TYPE_K(0) );

    ++psPacket->m_nuiContact;

    /* Check that the parametric term is within the acceptable range */
    if (!FCN_V(tgMH_Is_PRX_CMP_EQ)( vLN0, vLN1 ))
    {
        psContact = psPacket->m_psContact + psPacket->m_nuiContact;

        if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
        {
            return (KTgE_MAX_CONTACTS);
        };

        psContact->m_vS0 = FCN_V(tgMH_MAD)( vLN1, vD0, vS0 );
        psContact->m_vN0 = vN1;
        psContact->m_vT0 = vLN1;
        psContact->m_vDepth = FCN_V(tgMH_SET1)( TYPE_K(0) );

        ++psPacket->m_nuiContact;
    };

    return (KTgS_OK);
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/*# !defined (ENABLE_RELOAD_GUARD_LINEAR) */
#endif
