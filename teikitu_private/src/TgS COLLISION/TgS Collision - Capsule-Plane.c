/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Capsule-Plane.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

/* Α α, Β β, Γ γ, Δ δ, Ε ε, Ζ ζ, Η η, Θ θ, Ι ι, Κ κ, Λ λ, Μ μ, Ν ν, Ξ ξ, Ο ο, Π π, Ρ ρ, Σ σ/ς, Τ τ, Υ υ, Φ φ, Χ χ, Ψ ψ, Ω ω. */
/* α β γ δ ζ η θ ι κ λ μ ξ ο π ρ σ τ υ φ χ  | ν • ψ ε ∀ ∃ ∄ ∅ ∓ ∴ ≤ ≥ × て */
/* Latin for scalars, and Greek for vectors, and prefix ν for points */

/* ==== Capsule - Plane ========================================================================================================================================================== */
/**
    Capsule Definition: [νP0,νP1] are the two terminal points of a line segment representing the primary axis of the capsule. R0 is the capsule radius such that R0 > 0.
        Shell: Defined as all points that have a minimal distance to the capsule axis (P0->P1) that is R0 (capsule radius) .
        Solid: Defined as all points that have a minimal distance to the capsule axis (P0->P1) that is equal to or less than R0 (capsule radius) .
    Plane Definition: νP2 is a point on the plane, and η is a unit vector normal to plane. For half-spaces, the vector points out of the half space.

        Let υ be the normalized direction vector from νP0->νP1
            σ be the vector formed from νP0->νP1 == νP1-νP0
            D0 be the length of σ such that D0 > 0 (we ignore the degenerate case of a zero length capsule axis as it is the same as a sphere)

    Penetration
        Let V0 = [νP0-νP2]•η, V1 = [νP1-νP2]•η
          Whichever is higher is the point furthest from the plane (out of the half-space) and the other point is the one that is furthest into the half-space.

        WOLOG let νP0 be the point that is furthest into the half-space resulting in V0 ≤ V1

        Assume νP0 is the centre of a sphere of radius R0, the resulting point of greatest penetration would be νP0 - R0•η

        ∴ [νP0-νP2]•η ≤ [νP1-νP2]•η
           νP0•η-νP2•η ≤ νP1•η-νP2•η
           νP0•η ≤ νP1•η
           0 ≤ (νP1-νP0)•η
           0 ≤ σ•η
           0 ≤ (D0×υ)•η
           0 ≤ υ•η

        For this point to be on the hemi-sphere end of the capsule
         0 ≥ ((νP0-R0×η)-νP0)•υ
         0 ≥? -R0×η•υ
         0 ≤? υ•η
         0 ≤ υ•η, which was previously shown to be true

        The point of deepest penetration is νP3=νP0-R0×η and that it lies on the hemi-sphere end of the capsule.

        Generating a second point of penetration (νP4) is done for νP1. However, for similar reasons to above, we know that the point of deepest penetration is *outside* of the
          hemi-sphere end of the capsule. 



*/



#include "TgS COLLISION/TgS Collision - Plane-Linear.inl"
#include "TgS COLLISION/TgS Collision - Plane-Point.inl"
#include "TgS COLLISION/TgS Collision - Plane-Segment.inl"

#if !defined (TEMPLATE_TYPE_EXPANSION__RELOAD)
    #define TEMPLATE_TYPE_EXPANSION__RELOAD

    #if TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE
        #define TEMPLATE__VECTOR_DIM 4
        #define TEMPLATE__TYPE_SIZE 64
        #include __FILE__
    #endif

    #define TEMPLATE__VECTOR_DIM 4
    #define TEMPLATE__TYPE_SIZE 32

    #undef TEMPLATE_TYPE_EXPANSION__RELOAD
#endif

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"


/* == Collision ================================================================================================================================================================== */

/* ---- FCN_VO(tgCO_CP_Closest_PN) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
VEC_T(1) FCN_VO(tgCO_CP_Closest_PN)( VEC_T(1,PC) pfCP0, VEC_T(1,PC) pvPN0, VEC_OBJ_T(TgTUBE,CPC) psCP0, VEC_OBJ_T(TgPLANE,CPC) psPN0 )
{
    VEC_T(1,C)                          vOG = FCN_VO(tgGM_TB_Query_Origin)( psCP0 );
    VEC_T(1,C)                          vTest = FCN_VO(tgCO_PN_Sign_Dist_PT)( psPN0, vOG );

    TgPARAM_CHECK( FCN_VO(tgGM_TB_Is_Valid)(psCP0) && FCN_VO(tgGM_PN_Is_Valid)(psPN0) );

    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTest, psCP0->m_vRadius ) ))
    {
        return (FCN_V(tgMH_SET1)( -VAR_K(KTgMAX) ));
    }
    else
    {
        VEC_T(1,C)                          vUAX = FCN_VO(tgGM_TB_Query_Axis_Unit)( psCP0 );
        VEC_T(1,C)                          vUAX_N = FCN_V(tgMH_DOT)( psPN0->m_vNormal, vUAX );
        VEC_T(1,C)                          vE2 = FCN_V(tgMH_MUL)( psCP0->m_vExtent, FCN_V(tgMH_ABS)( vUAX_N ) );

        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GE)( FCN_V(tgMH_ADD)( vE2, psCP0->m_vRadius ), vTest ) ))
        {
            /* The capsule is penetrating this plane, return back the error state. */
            return (FCN_V(tgMH_SET1)( -VAR_K(KTgMAX) ));
        }
        else
        {
            VEC_T(1,C)                          vAx = FCN_V(tgMH_NEG)( FCN_V(tgMH_PRX_SGN)( vUAX_N ) );
            VEC_T(1,C)                          vK0 = FCN_V(tgMH_MUL)( psCP0->m_vRadius, psPN0->m_vNormal );
            VEC_T(1,C)                          vK1 = FCN_V(tgMH_SUB)( vOG, vK0 );
            VEC_T(1,C)                          vK2 = FCN_V(tgMH_MUL)( vAx, psCP0->m_vHAX );
            VEC_T(1,C)                          vPnt = FCN_V(tgMH_ADD)( vK1, vK2 );
            VEC_T(1,C)                          vDist = FCN_V(tgMH_SUB)( vTest, FCN_V(tgMH_ADD)( vE2, psCP0->m_vRadius ) );
            VEC_T(1,C)                          vK3 = FCN_V(tgMH_MUL)( vDist, psPN0->m_vNormal );

            *pfCP0 = vPnt;
            *pvPN0 = FCN_V(tgMH_SUB)( vPnt, vK3 );

            return (vDist);
        }
    }
}


/* ---- FCN_VO(tgCO_PN_Penetrate_CP) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN_VO(tgCO_PN_Penetrate_CP)(VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_OBJ_T(TgPLANE,CPC) psPN0, VEC_OBJ_T(TgTUBE,CPC) psCP0)
{
    TgPARAM_CHECK( FCN_VO(tgGM_TB_Is_Valid)(psCP0) && FCN_VO(tgGM_PN_Is_Valid)(psPN0) );

    if (0 == psPacket->m_nuiMaxContact || nullptr == psPacket->m_psContact)
    {
        return (KTgE_FAIL);
    }
    else
    {
        /* Project the capsule onto the plane normal and verify that some portion lies below the plane. */
        VEC_OBJ_T(STg2_CO_Contact,P)        psContact;

        VEC_T(1,C)                          vCP_HAX__PN_N = FCN_V(tgMH_DOT)( psPN0->m_vNormal, psCP0->m_vHAX ); /* Projection of the capsule axis onto the plane normal */
        VEC_T(1,C)                          vPRX_Sign = FCN_V(tgMH_PRX_SGN)( vCP_HAX__PN_N );  /* Sign of the projection with error range */
        VEC_T(1,C)                          vCP_OG = FCN_V(tgMH_Query_Axis_3,3)( &psCP0->m_mReference_Frame ); /* Origin for the capsule */

        VEC_T(1,C)                          vα0 = FCN_V(tgMH_NMS)( vPRX_Sign, psCP0->m_vHAX, vCP_OG ); /* Point on axis of deepest penetration */
        VEC_T(1,C)                          vα1 = FCN_V(tgMH_NMS)( psCP0->m_vRadius, psPN0->m_vNormal, vα0 ); /* Point of deepest penetration on the capsule surface */
        VEC_T(1,C)                          vDH0 = FCN_VO(tgCO_PN_Sign_Dist_PT)( psPN0, vα1 ); /* Calculate depth of penetration */

        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vDH0, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ))
        {
            return (KTgE_NO_INTERSECT);
        }
        else if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
        {
            return (KTgE_MAX_CONTACTS);
        }
        else
        {
            VEC_T(1,C)                          vβ0 = FCN_V(tgMH_MAD)( vPRX_Sign, psCP0->m_vHAX, vCP_OG ); /* Second capsule termination point */

            VEC_T(1,C)                          vγ0 = FCN_V(tgMH_SUB)( vβ0, vα0 );
            VEC_T(1,C)                          vγ1 = FCN_V(tgMH_DOT)( vγ0, psPN0->m_vNormal );

            /* Create a contact point based on the point of deepest penetration. */

            psContact = psPacket->m_psContact + psPacket->m_nuiContact;

            psContact->m_vS0 = vα1;
            psContact->m_vN0 = psPN0->m_vNormal;
            psContact->m_vT0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
            psContact->m_vDepth = FCN_V(tgMH_NEG)( vDH0 );

            ++psPacket->m_nuiContact;

            if (FCN_V(tgMH_Is_NR0)( vPRX_Sign ))
            {
                return (KTgS_OK);
            };

            if (FCN_V(tgMH_Is_NR0)( vγ1 ))
            {
                return (KTgS_OK);
            }
            else if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
            {
                return (KTgE_MAX_CONTACTS);
            }
            else
            {
                VEC_T(1,C)                          vγ2 = FCN_V(tgMH_NMS)( vγ1, psPN0->m_vNormal, vγ0 );
                VEC_T(1,C)                          vγ3 = FCN_V(tgMH_LEN)( vγ2 );
                VEC_T(1,C)                          vγ4 = FCN_V(tgMH_DIV)( psCP0->m_vRadius, vγ3 );
                VEC_T(1,C)                          vγ5 = FCN_V(tgMH_LEN)( vγ0 );
                VEC_T(1,C)                          vγ6 = FCN_V(tgMH_MUL)( vγ4, vγ5 );

                VEC_T(1,C)                          vβ1 = FCN_V(tgMH_NMS)( psPN0->m_vNormal, vγ6, vβ0 ); /* Second point of contact/penetration */
                VEC_T(1,C)                          vDH1 = FCN_VO(tgCO_PN_Sign_Dist_PT)( psPN0, vβ1 ); /* Calculate depth of penetration */

                /* We want to record a contact point even if not penetrated so that a constraint is created to limit the rotation. */

                psContact = psPacket->m_psContact + psPacket->m_nuiContact;

                psContact->m_vS0 = vβ1;
                psContact->m_vN0 = psPN0->m_vNormal;
                psContact->m_vT0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
                psContact->m_vDepth = FCN_V(tgMH_NEG)( vDH1 );

                ++psPacket->m_nuiContact;

                return (KTgS_OK);
            };
        };
    };
}


/* ---- FCN_VO(tgCO_CP_Penetrate_PN) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN_VO(tgCO_CP_Penetrate_PN)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_OBJ_T(TgTUBE,CPC) psCP0, VEC_OBJ_T(TgPLANE,CPC) psPN0 )
{
    TgRESULT                            iResult;
    TgRSIZE                             nuiExisting_Contact, uiIndex;

    TgPARAM_CHECK(FCN_VO(tgGM_TB_Is_Valid)( psCP0 ) && FCN_VO(tgGM_PN_Is_Valid)( psPN0 ));

    if (0 == psPacket->m_nuiMaxContact || psPacket->m_nuiContact >= psPacket->m_nuiMaxContact || nullptr == psPacket->m_psContact)
    {
        return (KTgE_FAIL);
    };

    nuiExisting_Contact = psPacket->m_nuiContact;

    iResult = FCN_VO(tgCO_PN_Penetrate_CP)( psPacket, psPN0, psCP0 );
    if (TgFAILED(iResult) && (KTgE_MAX_CONTACTS != iResult))
    {
        return (iResult);
    };

    /* Need to reverse the contacts that were made in the reversed collision call. */
    for (uiIndex = nuiExisting_Contact; uiIndex < psPacket->m_nuiContact; ++uiIndex)
    {
        VEC_OBJ_T(STg2_CO_Contact,PC)       psContact = psPacket->m_psContact + uiIndex;

        psContact->m_vS0 = FCN_V(tgMH_MAD)( psContact->m_vDepth, psContact->m_vN0, psContact->m_vS0 );
        psContact->m_vN0 = FCN_V(tgMH_NEG)( psContact->m_vN0 );
    }
    return (iResult);
}


/* ---- FCN_VO(tgCO_PN_Sweep_CP) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN_VO(tgCO_PN_Sweep_CP)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_T(1,PC) pvPM, VEC_OBJ_T(TgPLANE,CPC) psPN0, VEC_OBJ_T(TgTUBE,CPC) psCP0, VEC_OBJ_T(TgDELTA,CPC) psDT )
{
    TgPARAM_CHECK( FCN_VO(tgGM_TB_Is_Valid)(psCP0) && FCN_VO(tgGM_PN_Is_Valid)(psPN0) );

    if (0 == psPacket->m_nuiMaxContact || psPacket->m_nuiContact >= psPacket->m_nuiMaxContact || nullptr == psPacket->m_psContact)
    {
        return (KTgE_FAIL);
    }
    else
    {
        VEC_T(1)                            vCP0, vPN0;
        VEC_T(1,C)                          vDist = FCN_VO(tgCO_PN_Closest_SG)( &vPN0, &vCP0, psPN0, &psCP0->m_sAX );

        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( vDist, psCP0->m_vRadius ) ))
        {
            if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( *pvPM, psPacket->m_vSweepTol ) ))
            {
                psPacket->m_nuiContact = 0;
            };

            *pvPM = FCN_V(tgMH_SET1)( TYPE_K(0) );

            if ((psPacket->m_bReport_Penetration) && (KTgE_MAX_CONTACTS == FCN_VO(tgCO_PN_Penetrate_CP)( psPacket, psPN0, psCP0 )))
            {
                return (KTgE_MAX_CONTACTS);
            };

            return (KTgE_PREPENETRATION);
        }
        else
        {
            VEC_OBJ_T(STg2_CO_Contact,P)        psContact;

            VEC_T(1,C)                          vDT_N = FCN_V(tgMH_NEG)( FCN_V(tgMH_DOT)( psDT->m_vDT, psPN0->m_vNormal ) );
            VEC_T(1,C)                          vT0 = FCN_V(tgMH_DIV)( FCN_V(tgMH_SUB)( vDist, psCP0->m_vRadius ), vDT_N );
            VEC_T(1,C)                          vK2 = FCN_V(tgMH_MUL)( vT0, psDT->m_vDT );
            VEC_T(1,C)                          vK0 = FCN_V(tgMH_ADD)( vCP0, vK2 );
            VEC_T(1,C)                          vK1 = FCN_V(tgMH_MUL)( psCP0->m_vRadius, psPN0->m_vNormal );

            if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( vDT_N, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ))
            {
                return (KTgE_NO_INTERSECT);
            };

            if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vT0, FCN_V(tgMH_ADD)( *pvPM, psPacket->m_vSweepTol ) ) ))
            {
                return (KTgE_NO_INTERSECT);
            };

            if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vT0, FCN_V(tgMH_SUB)( *pvPM, psPacket->m_vSweepTol ) ) ))
            {
                psPacket->m_nuiContact = 0;
                *pvPM = vT0;
            };

            psContact = psPacket->m_psContact + psPacket->m_nuiContact;

            psContact->m_vS0 = FCN_V(tgMH_SUB)( vK0, vK1 );
            psContact->m_vN0 = psPN0->m_vNormal;
            psContact->m_vT0 = vT0;
            psContact->m_vDepth = FCN_V(tgMH_SET1)( TYPE_K(0) );

            ++psPacket->m_nuiContact;

            return (KTgS_OK);
        };
    };
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
