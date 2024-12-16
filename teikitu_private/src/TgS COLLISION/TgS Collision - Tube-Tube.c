/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Tube-Tube.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

/*                                                                                                                                                                                 */
/* ---- F_Internal_Sweep --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/*                                                                                                                                                                                 */
/*  INTERNAL FUNCTION:                                                                                                                                                             */
/*   Used by the cylinder and capsule routines to capture tube-tube contacts. The end-caps are expected to capture most of the contacts, and thus, this routine actively           */
/*  responds with false-negatives when it expects the other routines to have already found the correct contacts.                                                                   */
/*                                                                                                                                                                                 */
/*  Let α,β represent any two arbitrary tubes, and W.O.L.O.G.let β be the tube undergoing linear translation Φ.                                                                    */
/*  Let Sα, Sβ be the origin of the tube axes.                                                                                                                                     */
/*  Let Dα, Dβ be the direction of the tube axes.                                                                                                                                  */
/*                                                                                                                                                                                 */
/*  Let N = Dα x Dβ, and n = N/|N| <-- Invariant under translation.                                                                                                                */
/*                                                                                                                                                                                 */
/*  Let ξ = Sα - Sβ                                                                                                                                                                */
/*  Let γ(t) = ξ - Φ*t | t ε [ 0, 1]                                                                                                                                               */
/*                                                                                                                                                                                 */
/*  Minimal distance between the two lines is |(γ(t)•n)|                                                                                                                           */
/*                                                                                                                                                                                 */
/*  Solve for when distance is equal to the sum of the radii                                                                                                                       */
/*                                                                                                                                                                                 */
/*  Let RS be the some of the radii of the two tubes.                                                                                                                              */
/*                                                                                                                                                                                 */
/*  RS*RS   = (γ(t)•n)*(γ(t)•n)                                                                                                                                                    */
/*          = ((ξ - Φ*t)•n)*((ξ - Φ*t)•n)                                                                                                                                          */
/*          = (ξ•n - Φ•n*t)*(ξ•n - Φ•n*t)                                                                                                                                          */
/*          = (ξ•n)*(ξ•n) - 2*(ξ•n)*(Φ•n)*t + (Φ•n)*(Φ•n)*t*t                                                                                                                      */
/*                                                                                                                                                                                 */
/*  Solve the quadratic equation,                                                                                                                                                  */
/*   (Φ•n)*(Φ•n)*t*t - 2*(ξ•n)*(Φ•n)*t + (ξ•n)*(ξ•n) - RS*RS = 0                                                                                                                   */
/*                                                                                                                                                                                 */
/*  t = (-(-2*(ξ•n)*(Φ•n)) ± √((-2*(ξ•n)*(Φ•n))*(-2*(ξ•n)*(Φ•n)) - 4*(Φ•n)*(Φ•n)*((ξ•n)*(ξ•n) - RS*RS))) / 2*(Φ•n)*(Φ•n)                                                           */
/*    = (2*(ξ•n)*(Φ•n) ± √(4*(ξ•n)*(ξ•n)*(Φ•n)*(Φ•n) - 4*(Φ•n)*(Φ•n)*(ξ•n)*(ξ•n) + 4*(Φ•n)*(Φ•n)*RS*RS)) / 2*(Φ•n)*(Φ•n)                                                           */
/*    = (2*(ξ•n)*(Φ•n) ± 2*(Φ•n)*√((ξ•n)*(ξ•n) - (ξ•n)*(ξ•n) + RS*RS)) / 2*(Φ•n)*(Φ•n)                                                                                             */
/*    = ((ξ•n) ± √(RS*RS))) / (Φ•n)                                                                                                                                                */
/*    = ((ξ•n) ± RS) / (Φ•n)                                                                                                                                                       */
/*                                                                                                                                                                                 */

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

/* ---- FCN_VO(tgCO_TB_Sweep_TB) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN_VO(tgCO_TB_Sweep_TB)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_T(1,P) pvPM, VEC_OBJ_T(TgTUBE,CPC) psTB0, VEC_OBJ_T(TgTUBE,CPC) psTB1, VEC_OBJ_T(TgDELTA,CPC) psDT )
{
    VEC_T(1,C)                          vTB0_UAX = FCN_VO(tgGM_TB_Query_Axis_Unit)( psTB0 );
    VEC_T(1,C)                          vTB1_UAX = FCN_VO(tgGM_TB_Query_Axis_Unit)( psTB1 );
    VEC_T(1,C)                          vTB0_OG = FCN_VO(tgGM_TB_Query_Origin)( psTB0 );
    VEC_T(1,C)                          vTB1_OG = FCN_VO(tgGM_TB_Query_Origin)( psTB1 );
    VEC_T(1,C)                          vSumRad = FCN_V(tgMH_ADD)( psTB0->m_vRadius, psTB1->m_vRadius );
    VEC_T(1,C)                          vDS = FCN_V(tgMH_SUB)( vTB0_OG, vTB1_OG );

    VEC_T(1)                            vTest, vN0, vK10, vDS_N0;

    TgPARAM_CHECK( FCN_VO(tgGM_TB_Is_Valid)(psTB0) && FCN_VO(tgGM_TB_Is_Valid)(psTB1) );

    if (0 == psPacket->m_nuiMaxContact || psPacket->m_nuiContact >= psPacket->m_nuiMaxContact || nullptr == psPacket->m_psContact)
    {
        return (KTgE_FAIL);
    };

    vK10 = FCN_V(tgMH_CX)( vTB0_UAX, vTB1_UAX );
    vN0 = FCN_V(tgMH_NORM_LEN)( &vTest, vK10 );
    vDS_N0 = FCN_V(tgMH_DOT)( vDS, vN0 );

    if (FCN_V(tgMH_Is_NR0)( vTest ))
    {
        return (KTgE_NO_INTERSECT); /* Lines are near parallel */
    };

    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( FCN_V(tgMH_ABS)( vDS_N0 ), vSumRad ) ))
    {
        VEC_T(1,C)                          vTA = FCN_V(tgMH_CX)( vN0, vDS );
        VEC_T(1,C)                          vS0 = FCN_V(tgMH_DOT)( vTB1_UAX, vTA );
        VEC_T(1,C)                          vS1 = FCN_V(tgMH_DOT)( vTB0_UAX, vTA );
        VEC_T(1,C)                          vCMP0 = FCN_V(tgMH_CMP_GE)( FCN_V(tgMH_ABS)( vS0 ), psTB0->m_vExtent );
        VEC_T(1,C)                          vCMP1 = FCN_V(tgMH_CMP_GE)( FCN_V(tgMH_ABS)( vS1 ), psTB1->m_vExtent );

        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP0 ) || FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP1 ))
        {
            return (KTgE_NO_INTERSECT); /* Proximity point lies outside of the tube's extents. */
        };

        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( *pvPM , psPacket->m_vSweepTol ) ))
        {
            psPacket->m_nuiContact = 0;
        };

        *pvPM = FCN_V(tgMH_SET1)( TYPE_K(0) );

        if (psPacket->m_bReport_Penetration)
        {
            VEC_OBJ_T(STg2_CO_Contact,P)        psContact;
            VEC_T(1)                            vK0, vK1, vK2;

            vN0 = FCN_V(tgMH_MUL)( vN0, FCN_V(tgMH_SGN)( FCN_V(tgMH_NEG)( vDS_N0 ) ) ); /* Direct the normal from TB0 to TB1 */

            if (FCN_V(tgMH_Is_NR0)( vDS_N0 )) /* Arbitrarily choose an orthonormal direction if penetrated distance to axis. */
            {
                vN0 = FCN_V(tgMH_Init_Ortho)( vTB1_UAX );
                vN0 = FCN_V(tgMH_NORM)( vN0 );
            };

            vK0 = FCN_V(tgMH_MUL)( vS1, vTB1_UAX );
            vK1 = FCN_V(tgMH_MUL)( vN0, psTB1->m_vRadius );
            vK2 = FCN_V(tgMH_SUB)( vK0, vK1 );

            psContact = psPacket->m_psContact + psPacket->m_nuiContact;

            psContact->m_vS0 = FCN_V(tgMH_ADD)( vTB1_OG, vK2 );
            psContact->m_vN0 = vN0;
            psContact->m_vT0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
            psContact->m_vDepth = FCN_V(tgMH_SUB)( vSumRad, FCN_V(tgMH_ABS)( vDS_N0 ) );

            ++psPacket->m_nuiContact;
        };

        return (KTgE_PREPENETRATION);
    }
    else
    {
        VEC_T(1,C)                          vDT_N0 = FCN_V(tgMH_DOT)( psDT->m_vDT, vN0 );
        VEC_T(1,C)                          vK7 = FCN_V(tgMH_SUB)( FCN_V(tgMH_ABS)( vDS_N0 ), vSumRad );
        VEC_T(1,C)                          vT0 = FCN_V(tgMH_DIV)( vK7, FCN_V(tgMH_ABS)( vDT_N0 ) );
        VEC_T(1,C)                          vK6 = FCN_V(tgMH_CMP_LE)( vDS_N0, FCN_V(tgMH_SET1)( TYPE_K(0) ) );
        VEC_T(1,C)                          vK5 = FCN_V(tgMH_CMP_LE)( vDT_N0, FCN_V(tgMH_SET1)( TYPE_K(0) ) );
        VEC_T(1,C)                          vK0 = FCN_V(tgMH_MUL)( psDT->m_vDT, vT0 );
        VEC_T(1,C)                          vK1 = FCN_V(tgMH_SUB)( vDS, vK0 );
        VEC_T(1,C)                          vTA = FCN_V(tgMH_CX)( vN0, vK1 );
        VEC_T(1,C)                          vS0 = FCN_V(tgMH_DOT)( vTB1_UAX, vTA );
        VEC_T(1,C)                          vS1 = FCN_V(tgMH_DOT)( vTB0_UAX, vTA );
        VEC_T(1,C)                          vKN = FCN_V(tgMH_MUL)( vN0, FCN_V(tgMH_SGN)( FCN_V(tgMH_NEG)( vDS_N0 ) ) );
        VEC_T(1,C)                          vK2 = FCN_V(tgMH_MUL)( vS1, vTB1_UAX );
        VEC_T(1,C)                          vK3 = FCN_V(tgMH_MUL)( vKN, psTB1->m_vRadius );
        VEC_T(1,C)                          vK4 = FCN_V(tgMH_SUB)( vK2, vK3 );
        VEC_T(1,C)                          vCMP0 = FCN_V(tgMH_CMP_GE)( FCN_V(tgMH_ABS)( vS0 ), psTB0->m_vExtent );
        VEC_T(1,C)                          vCMP1 = FCN_V(tgMH_CMP_GE)( FCN_V(tgMH_ABS)( vS1 ), psTB1->m_vExtent );

        VEC_OBJ_T(STg2_CO_Contact, P)        psContact;

        if (FCN_V(tgMH_Is_NR0)(vDT_N0) || !FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_XOR)( vK5, vK6 ) ))
        {
            return (KTgE_NO_INTERSECT); /* Displacement is either near zero, tangential to or directed along the distance vector. */
        };

        if (!FCN_V(tgMH_Is_Contained_In_Interval)( vT0, FCN_V(tgMH_SET1)( TYPE_K(0) ), FCN_V(tgMH_ADD)( *pvPM, psPacket->m_vSweepTol ) ))
        {
            return (KTgE_NO_INTERSECT); /* Earlier intersection already recorded. */
        };

        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP0 ) || FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP1 ))
        {
            return (KTgE_NO_INTERSECT); /* Proximity point lies outside of the tube's extents. */
        };

        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vT0, FCN_V(tgMH_SUB)( *pvPM, psPacket->m_vSweepTol ) ) ))
        {
            psPacket->m_nuiContact = 0; /* New earliest time of intersection */
            *pvPM = vT0;
        };

        psContact = psPacket->m_psContact + psPacket->m_nuiContact;

        psContact->m_vS0 = FCN_V(tgMH_ADD)( vTB1_OG, vK4 );
        psContact->m_vN0 = vKN;
        psContact->m_vT0 = vT0;
        psContact->m_vDepth = FCN_V(tgMH_SET1)( TYPE_K(0) );

        ++psPacket->m_nuiContact;

        return (KTgS_OK);
    };
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
