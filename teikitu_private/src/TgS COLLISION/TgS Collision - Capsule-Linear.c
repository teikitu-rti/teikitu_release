/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Capsule-Linear.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#if !defined (ENABLE_RELOAD_GUARD_LINEAR)
    #define ENABLE_RELOAD_GUARD_LINEAR

    TgMSVC_WARN_DISABLE_PUSH(6235) /* Analysis - (<non-zero constant> || <non-zero constant>) is always a non-zero constant. */

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

    TgMSVC_WARN_DISABLE_POP(6235)

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


/* == Collision ================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/*  @internal Determine the points of contact between the capsule and line. Internal function that does not clip to the linear limits.
    @param [out] OUT0 Pointer to a vector holding a full broadcast of the parametric value for the 1st point of contact.
    @param [out] OUT1 Pointer to a vector holding the contact normal for the point in OUT0.
    @param [in] ARG2 Vector holding a positive/negative indicator to select which end of the axis to test.
    @param [in] ARG3 Pointer to tube object, interpreted as a capsule.
    @param [in] ARG4 Vector holding the Line Origin.
    @param [in] ARG5 Vector holding the Line Direction.
    @return Result Code. */
static TgRESULT
VI(tgCO_CP_Internal_LR)(
    VEC_T(1,PC) OUT0, VEC_T(1,PC) OUT1, VEC_T(1,C) ARG2, VEC_OBJ_T(TgTUBE,CPC) ARG3, VEC_T(1,C) ARG4, VEC_T(1,C) ARG5 );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- VI(tgCO_CP_Intersect_LR) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT VI(tgCO_CP_Intersect_LR)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_OBJ_T(TgTUBE,CPC) psCP0, VEC_T(1,C) vS0, VEC_T(1,C) vD0 )
{
    VEC_T(1)                            vLN0, vLN1;
    VEC_T(1)                            vN0, vN1;
    VEC_OBJ_T(STg2_CO_Contact,P)        psContact;
    TgRESULT                            iResult;
    TgBOOL                              bContact = false;

    /* Check to make sure that a valid contact, and contact packet exist. */

    if (0 == psPacket->m_nuiMaxContact || psPacket->m_nuiContact >= psPacket->m_nuiMaxContact || nullptr == psPacket->m_psContact)
    {
        return (KTgE_FAIL);
    };

    iResult = VI(tgCO_CP_Contact_LR)( &vLN0, &vLN1, &vN0, &vN1, psCP0, vS0, vD0 );

    if (TgFAILED( iResult ))
    {
        return (iResult);
    };

    /* Limit the variable to the cap regions */

    if (LN_CAP_0 && FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vLN0, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ))
    {
        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( vLN1, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ))
        {
            return (KTgE_NO_INTERSECT);
        };
    }
    else if (!LN_CAP_1 || FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( vLN1, FCN_V(tgMH_SET1)( TYPE_K(1) ) ) ))
    {
        psContact = psPacket->m_psContact + psPacket->m_nuiContact;

        psContact->m_vS0 = FCN_V(tgMH_ADD)( vS0, FCN_V(tgMH_MUL)( vLN0, vD0 ) );
        psContact->m_vN0 = vN0;
        psContact->m_vT0 = vLN0;
        psContact->m_vDepth = FCN_V(tgMH_SET1)( TYPE_K(0) );

        ++psPacket->m_nuiContact;
        bContact = true;
    };

    if (LN_CAP_1 && FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vLN1, FCN_V(tgMH_SET1)( TYPE_K(1) ) ) ))
    {
        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GE)( vLN0, FCN_V(tgMH_SET1)( TYPE_K(1) ) ) ))
        {
            return (KTgE_NO_INTERSECT);
        };
    }
    else if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( FCN_V(tgMH_ABS)( FCN_V(tgMH_SUB)( vLN0, vLN1 ) ), FCN_V(tgMH_SET1)( VAR_K(KTgEPS) ) ) ))
    {
        if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
        {
            return (KTgE_MAX_CONTACTS);
        }
        else
        {
            psContact = psPacket->m_psContact + psPacket->m_nuiContact;

            psContact->m_vS0 = FCN_V(tgMH_ADD)( vS0, FCN_V(tgMH_MUL)( vLN1, vD0 ) );
            psContact->m_vN0 = vN1;
            psContact->m_vT0 = vLN1;
            psContact->m_vDepth = FCN_V(tgMH_SET1)( TYPE_K(0) );

            ++psPacket->m_nuiContact;
            bContact = true;
        };
    };

    return (bContact ? KTgS_OK : KTgE_NO_INTERSECT);
}


/* ---- VI(tgCO_CP_Penetrate_LR) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT VI(tgCO_CP_Penetrate_LR)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_T(1,C) vL0, VEC_OBJ_T(TgTUBE,CPC) psCP0, VEC_T(1,C) vCP1, VEC_T(1,C) vDistSq )
{
    VEC_T(1)                            vNormal, vMAG_NM;
    VEC_OBJ_T(STg2_CO_Contact,P)        psContact;

    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( vDistSq, FCN_V(tgMH_SET1)( VAR_K(KTgEPS) ) ) ))
    {
        VEC_UN_T(1)                         uUAX;

        VEC_UN_1_MEMBER(uUAX) = FCN_VO(tgGM_TB_Query_Axis_Unit)( psCP0 );
        if (FCN_F(tgCM_NR0)(VEC_S_UN_1_MEMBER(uUAX).z))
        {
            vNormal = FCN_V(tgMH_Init_Vector_ELEM)( -VEC_S_UN_1_MEMBER(uUAX).y, VEC_S_UN_1_MEMBER(uUAX).x, TYPE_K(0) );
        }
        else
        {
            vNormal = FCN_V(tgMH_Init_Vector_ELEM)( TYPE_K(0), VEC_S_UN_1_MEMBER(uUAX).z, -VEC_S_UN_1_MEMBER(uUAX).y );
        };
        vNormal = FCN_V(tgMH_NORM)( vNormal );
        vMAG_NM = FCN_V(tgMH_SET1)( TYPE_K(0) );
    }
    else
    {
        vNormal = FCN_V(tgMH_NORM_LEN)( &vMAG_NM, FCN_V(tgMH_SUB)( vCP1, vL0 ) );
    };

    psContact = psPacket->m_psContact + psPacket->m_nuiContact;

    psContact->m_vS0 = FCN_V(tgMH_SUB)( vCP1, FCN_V(tgMH_MUL)( psCP0->m_vRadius, vNormal ) );
    psContact->m_vN0 = vNormal;
    psContact->m_vT0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
    psContact->m_vDepth = FCN_V(tgMH_SUB)( psCP0->m_vRadius, vMAG_NM );

    ++psPacket->m_nuiContact;

    return (KTgS_OK);
}


/* ---- VI(tgCO_CP_Contact_LR) --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT VI(tgCO_CP_Contact_LR)( VEC_T(1,PC) pvLN0, VEC_T(1,PC) pvLN1, VEC_T(1,PC) pvN0, VEC_T(1,PC) pvN1, VEC_OBJ_T(TgTUBE,CPC) psCP0, VEC_T(1,C) vS0, VEC_T(1,C) vD0 )
{
    /* Linear in the reference frame of the capsule */

    VEC_T(1)                            vCP0_UX[3], vCP0_OG;

    FCN_V(tgMH_Query_Reference_Frame,3)( vCP0_UX + 0, vCP0_UX + 1, vCP0_UX + 2, &vCP0_OG, &psCP0->m_mReference_Frame );

    {
        VEC_T(1,C)                          vD0_U0 = FCN_V(tgMH_DOT)( vD0, vCP0_UX[0] );
        VEC_T(1,C)                          vD0_U1 = FCN_V(tgMH_DOT)( vD0, vCP0_UX[2] );
        VEC_T(1,C)                          vD0_UA = FCN_V(tgMH_DOT)( vD0, vCP0_UX[1] );

        VEC_T(1,C)                          vA = FCN_V(tgMH_ADD)( FCN_V(tgMH_MUL)( vD0_U0, vD0_U0 ), FCN_V(tgMH_MUL)( vD0_U1, vD0_U1 ) );

        /* Relative position of the origin inside of the capsule's reference frame. */

        VEC_T(1,C)                          vDS = FCN_V(tgMH_SUB)( vS0, vCP0_OG );

        VEC_T(1,C)                          vDS_UA = FCN_V(tgMH_DOT)( vDS, vCP0_UX[1] );
        VEC_T(1,C)                          vDS_U0 = FCN_V(tgMH_DOT)( vDS, vCP0_UX[0] );
        VEC_T(1,C)                          vDS_U1 = FCN_V(tgMH_DOT)( vDS, vCP0_UX[2] );

        /* Relative distance of the origin on the cross-sectional plane of the capsule. */

        VEC_T(1,C)                          vRelSq = FCN_V(tgMH_ADD)( FCN_V(tgMH_MUL)( vDS_U0, vDS_U0 ), FCN_V(tgMH_MUL)( vDS_U1, vDS_U1 ) );

        TgPARAM_CHECK( FCN_VO(tgGM_TB_Is_Valid)(psCP0) && FCN_V(tgMH_Is_Valid_Point)(vS0) && FCN_V(tgMH_Is_Valid_Vector)(vD0) );

        if (LN_CAP_0)
        {
            /* If the origin lies outside of the capsule and only moves away - intersection can not take place. */

            VEC_T(1,C)                          vK0 = FCN_V(tgMH_ADD)( psCP0->m_vExtent, psCP0->m_vRadius );
            VEC_T(1,C)                          vK1 = FCN_V(tgMH_ADD)( FCN_V(tgMH_MUL)( vDS_U0, vD0_U0 ), FCN_V(tgMH_MUL)( vDS_U1, vD0_U1 ) );

            TgBOOL_C                            bF0 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vDS_UA, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) );
            TgBOOL_C                            bF1 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vD0_UA, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) );
            TgBOOL_C                            bF2 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( FCN_V(tgMH_ABS)( vDS_UA ), vK0 ) );
            TgBOOL_C                            bF3 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vRelSq, psCP0->m_vRadiusSq ) );
            TgBOOL_C                            bF4 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vK1, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) );

            if (!(bF0 ^ bF1) && bF2)
            {
                return (KTgE_NO_INTERSECT);
            };

            /* If the origin lies outside of the capsule and only moves away - intersection can not take place. In the radial case moving away is determined by projecting */
            /* the direction vector onto the difference vector after both have been projected onto the cross-sectional plane. */

            if (bF3 && bF4)
            {
                return (KTgE_NO_INTERSECT);
            };
        };

        /* R² = (DS_U0 + ζ•D0_U0)² + (DS_U1 + ζ•D0_U1)² */
        /* R² = DS_U0•DS_U0 + 2•ζ•DS_U0•D0_U0 + ζ•ζ•D0_U0•D0_U0 + DS_U1•DS_U1 + 2•ζ•DS_U1•D0_U1 + ζ•ζ•D0_U1•D0_U1 */
        /* 0  = ζ•ζ_(D0_U0•D0_U0 + D0_U1•D0_U1,DIM) + ζ_(2•DS_U0•D0_U0 + 2•DS_U1•D0_U1,DIM) + DS_U0•DS_U0 + DS_U1•DS_U1 - R² */

        {
            VEC_T(1,C)                          vHalfNegB_A = FCN_V(tgMH_ADD)( FCN_V(tgMH_MUL)( vDS_U0, vD0_U0 ), FCN_V(tgMH_MUL)( vDS_U1, vD0_U1 ) );
            VEC_T(1,C)                          vHalfNegB = FCN_V(tgMH_MUL)( FCN_V(tgMH_SET1)( -TYPE_K(1) ), vHalfNegB_A );
            VEC_T(1,C)                          vC = FCN_V(tgMH_SUB)( vRelSq, psCP0->m_vRadiusSq );
            VEC_T(1,C)                          vDet = FCN_V(tgMH_SUB)( FCN_V(tgMH_MUL)( vHalfNegB, vHalfNegB ), FCN_V(tgMH_MUL)( vC, vA ) );
            VEC_T(1,C)                          vInvA = FCN_V(tgMH_DIV)( FCN_V(tgMH_SET1)( TYPE_K(1) ), vA );

            if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vDet, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ))
            {
                return (KTgE_NO_INTERSECT);
            }
            else
            {
                VEC_T(1)                            vMAG_D0;

                VEC_T(1,C)                          vDetSqrt = FCN_V(tgMH_SQRT)( vDet );
                VEC_T(1,C)                          vUD0 = FCN_V(tgMH_NORM_LEN)( &vMAG_D0, vD0 );
                VEC_T(1,C)                          vT0 = FCN_V(tgMH_MUL)( FCN_V(tgMH_SUB)( vHalfNegB, vDetSqrt ), vInvA );
                VEC_T(1,C)                          vT1 = FCN_V(tgMH_MUL)( FCN_V(tgMH_ADD)( vHalfNegB, vDetSqrt ), vInvA );

                if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vD0, FCN_V(tgMH_SET1)( VAR_K(KTgEPS) ) ) ))
                {
                    return (KTgE_NO_INTERSECT);
                }
                else
                {
                    VEC_T(1,C)                          vH0 = FCN_V(tgMH_ADD)( vDS_UA, FCN_V(tgMH_MUL)( vT0, vD0_UA ) );
                    VEC_T(1,C)                          vH1 = FCN_V(tgMH_ADD)( vDS_UA, FCN_V(tgMH_MUL)( vT1, vD0_UA ) );
                    VEC_T(1,C)                          vInvD0 = FCN_V(tgMH_DIV)( FCN_V(tgMH_SET1)( TYPE_K(1) ), vD0 );
                    VEC_T(1,C)                          vUAX_0 = FCN_VO(tgGM_TB_Query_Axis_Unit)( psCP0 );

                    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( FCN_V(tgMH_ABS)( vH0 ), psCP0->m_vExtent ) ))
                    {
                        TgBOOL_C                            bF0 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vH0, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) );

                        if (TgFAILED( VI(tgCO_CP_Internal_LR)( pvLN0, pvN0, FCN_V(tgMH_SET1)( bF0 ? TYPE_K(1) : -TYPE_K(1) ), psCP0, vS0, vUD0 ) ))
                        {
                            TgERROR(FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( FCN_V(tgMH_ABS)( vH1 ), psCP0->m_vExtent ) ));
                            return (KTgE_NO_INTERSECT);
                        };

                        *pvLN0 = FCN_V(tgMH_MUL)( *pvLN0, vInvD0 );
                    }
                    else
                    {
                        VEC_T(1,C)                          vK0 = FCN_V(tgMH_MUL)( vT0, vD0 );
                        VEC_T(1,C)                          vK1 = FCN_V(tgMH_MUL)( vH0, vUAX_0 );
                        VEC_T(1,C)                          vK2 = FCN_V(tgMH_SUB)( vK0, vK1 );
                        VEC_T(1,C)                          vK3 = FCN_V(tgMH_ADD)( vDS, vK2 );

                        *pvLN0 = vT0;
                        *pvN0 = FCN_V(tgMH_NORM)( vK3 );
                    };


                    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( FCN_V(tgMH_ABS)( vH1 ), psCP0->m_vExtent ) ))
                    {
                        TgBOOL_C                            bF0 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vH1, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) );

                        if (TgFAILED( VI(tgCO_CP_Internal_LR)( pvLN1, pvN1, FCN_V(tgMH_SET1)( bF0 ? TYPE_K(1) : -TYPE_K(1) ), psCP0, vS0, vUD0 ) ))
                        {
                            TgERROR(false);
                        };

                        *pvLN1 = FCN_V(tgMH_MUL)( *pvLN1, vInvD0 );
                    }
                    else
                    {
                        VEC_T(1,C)                          vK0 = FCN_V(tgMH_MUL)( vT1, vD0 );
                        VEC_T(1,C)                          vK1 = FCN_V(tgMH_MUL)( vH1, vUAX_0 );
                        VEC_T(1,C)                          vK2 = FCN_V(tgMH_SUB)( vK0, vK1 );
                        VEC_T(1,C)                          vK3 = FCN_V(tgMH_ADD)( vDS, vK2 );

                        *pvLN1 = vT1;
                        *pvN1 = FCN_V(tgMH_NORM)( vK3 );
                    };

                    return (KTgS_OK);
                };
            };
        };
    };
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- VI(tgCO_CP_Internal_LR) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT VI(tgCO_CP_Internal_LR)( VEC_T(1,PC) pvL0, VEC_T(1,PC) pvN0, VEC_T(1,C) vAx, VEC_OBJ_T(TgTUBE,CPC) psCP0, VEC_T(1,C) vS0, VEC_T(1,C) vUD0 )
{
    VEC_T(1,C)                          vCP0_OG = FCN_VO(tgGM_TB_Query_Origin)( psCP0 );
    VEC_T(1,C)                          vD1 = FCN_V(tgMH_MUL)( vAx, psCP0->m_vHAX );
    VEC_T(1,C)                          vS1 = FCN_V(tgMH_ADD)( vCP0_OG, vD1 );
    VEC_T(1,C)                          vDS = FCN_V(tgMH_SUB)( vS1, vS0 );
    VEC_T(1,C)                          vDS_DS = FCN_V(tgMH_LSQ)( vDS );
    VEC_T(1,C)                          vT0 = FCN_V(tgMH_DOT)( vDS, vUD0 );
    VEC_T(1,C)                          vDSC = FCN_V(tgMH_ADD)( FCN_V(tgMH_SUB)( FCN_V(tgMH_MUL)( vT0, vT0 ), vDS_DS ), psCP0->m_vRadiusSq );

    TgPARAM_CHECK( FCN_VO(tgGM_TB_Is_Valid)(psCP0) && FCN_V(tgMH_Is_Valid_Point)(vS0) && FCN_V(tgMH_Is_Valid_Vector)(vUD0) );

    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vDSC, FCN_V(tgMH_SET1)( VAR_K(KTgEPS) ) ) ))
    {
        VEC_T(1)                            vT1, vT2, vK0;

        VEC_T(1,C)                          vRoot = FCN_V(tgMH_SQRT)( vDSC );

        vT1 = FCN_V(tgMH_ADD)( vT0, vRoot );
        vK0 = FCN_V(tgMH_MUL)( vT1, vUD0 );
        vT2 = FCN_V(tgMH_SUB)( vK0, vDS );

        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GE)( FCN_V(tgMH_DOT)( vT2, vD1 ), FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ))
        {
            *pvN0 = FCN_V(tgMH_NORM)( vT2 );
            *pvL0 = vT1;

            return (KTgS_OK);
        };

        vT1 = FCN_V(tgMH_SUB)( vT0, vRoot );
        vK0 = FCN_V(tgMH_MUL)( vT1, vUD0 );
        vT2 = FCN_V(tgMH_SUB)( vK0, vDS );

        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GE)( FCN_V(tgMH_DOT)( vT2, vD1 ), FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ))
        {
            *pvN0 = FCN_V(tgMH_NORM)( vT2 );
            *pvL0 = vT1;

            return (KTgS_OK);
        };
    }
    else if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vDSC, FCN_V(tgMH_SET1)( -VAR_K(KTgEPS) ) ) ))
    {
        VEC_T(1,C)                          vK0 = FCN_V(tgMH_MUL)( vT0, vUD0 );
        VEC_T(1,C)                          vT2 = FCN_V(tgMH_SUB)( vK0, vDS );

        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GE)( FCN_V(tgMH_DOT)( vT2, vD1 ), FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ))
        {
            *pvN0 = FCN_V(tgMH_NORM)( vT2 );
            *pvL0 = vT2;

            return (KTgS_OK);
        };
    };

    return (KTgE_NO_INTERSECT);
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/*# !defined (ENABLE_RELOAD_GUARD_LINEAR) */
#endif
