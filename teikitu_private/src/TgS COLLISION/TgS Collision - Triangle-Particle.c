/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Triangle-Particle.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

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

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

static TgRESULT
FCN_VO(tgCO_PC_Internal_Sweep_ET)(
    VEC_OBJ_T(STg2_CO_Contact,PC), VEC_OBJ_T(TgPARTICLE,CPC), VEC_T(1,C), VEC_OBJ_T(TgETRI,CPC) );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- FCN_VO(tgCO_PC_Sweep_ET) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN_VO(tgCO_PC_Sweep_ET)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_T(1,P) pvPM, VEC_OBJ_T(TgPARTICLE,CPC) psPC0, VEC_OBJ_T(TgETRI,CPC) psET0,
                                   VEC_OBJ_T(TgDELTA,CPC) psDT )
{
    VEC_OBJ_T(STg2_CO_Contact)          sContact;
    VEC_OBJ_T(STg2_CO_Contact,P)        psContact;
    TgRESULT                            iResult;

    VEC_T(1,C)      vK0 = FCN_V(tgMH_SUB)( psPC0->m_vVel, psDT->m_vDT );

    TgPARAM_CHECK( FCN_VO(tgGM_ET_Is_Valid)(psET0) && FCN_VO(tgGM_PC_Is_Valid)(psPC0) );

    if (0 == psPacket->m_nuiMaxContact || psPacket->m_nuiContact >= psPacket->m_nuiMaxContact || nullptr == psPacket->m_psContact)
    {
        return (KTgE_FAIL);
    };

    iResult = FCN_VO(tgCO_PC_Internal_Sweep_ET)( &sContact, psPC0, vK0, psET0 );

    if (TgFAILED( iResult ))
    {
        return (iResult);
    }
    else
    {
        VEC_T(1,C)                          vPM_NTol = FCN_V(tgMH_SUB)( *pvPM, psPacket->m_vSweepTol );
        VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_LT)( sContact.m_vT0, vPM_NTol );
        VEC_T(1,C)                          vPM_PTol = FCN_V(tgMH_ADD)( *pvPM, psPacket->m_vSweepTol );
        VEC_T(1,C)                          vCMP_1 = FCN_V(tgMH_CMP_GT)( sContact.m_vT0, vPM_PTol );

        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_1 ) || !FCN_VO(tgGM_ET_Is_Contained)( psET0, sContact.m_vS0 ))
        {
            return (KTgE_NO_INTERSECT);
        };

        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_0 ))
        {
            psPacket->m_nuiContact = 0;
            *pvPM = sContact.m_vT0;
        };

        psContact = psPacket->m_psContact + psPacket->m_nuiContact;

        psContact->m_vS0 = sContact.m_vS0;
        psContact->m_vN0 = sContact.m_vN0;
        psContact->m_vT0 = sContact.m_vT0;
        psContact->m_vDepth = sContact.m_vDepth;

        ++psPacket->m_nuiContact;

        return (KTgS_OK);
    };
}


/* ---- FCN_VO(tgCO_ET_Sweep_PC) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN_VO(tgCO_ET_Sweep_PC)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_T(1,P) pvPM, VEC_OBJ_T(TgETRI,CPC) psET0, VEC_OBJ_T(TgPARTICLE,CPC) psPC0,
                                   TgATTRIBUTE_UNUSED VEC_OBJ_T(TgDELTA,CPC) psDT )
{
    VEC_OBJ_T(STg2_CO_Contact)          sContact;
    VEC_OBJ_T(STg2_CO_Contact,P)        psContact;
    TgRESULT                            iResult;

    TgPARAM_CHECK( FCN_VO(tgGM_ET_Is_Valid)(psET0) && FCN_VO(tgGM_PC_Is_Valid)(psPC0) );

    if (0 == psPacket->m_nuiMaxContact || psPacket->m_nuiContact >= psPacket->m_nuiMaxContact || nullptr == psPacket->m_psContact)
    {
        return (KTgE_FAIL);
    };

    iResult = FCN_VO(tgCO_PC_Internal_Sweep_ET)( &sContact, psPC0, psPC0->m_vVel, psET0 );

    if (TgFAILED( iResult ))
    {
        return (iResult);
    }
    else
    {
        VEC_T(1,C)                          vPM_NTol = FCN_V(tgMH_SUB)( *pvPM, psPacket->m_vSweepTol );
        VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_LT)( sContact.m_vT0, vPM_NTol );
        VEC_T(1,C)                          vPM_PTol = FCN_V(tgMH_ADD)( *pvPM, psPacket->m_vSweepTol );
        VEC_T(1,C)                          vCMP_1 = FCN_V(tgMH_CMP_GT)( sContact.m_vT0, vPM_PTol );

        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_1 ) || !FCN_VO(tgGM_ET_Is_Contained)( psET0, sContact.m_vS0 ))
        {
            return (KTgE_NO_INTERSECT);
        };

        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_0 ))
        {
            psPacket->m_nuiContact = 0;
            *pvPM = sContact.m_vT0;
        };

        psContact = psPacket->m_psContact + psPacket->m_nuiContact;

        psContact->m_vS0 = sContact.m_vS0;
        psContact->m_vN0 = sContact.m_vN0;
        psContact->m_vT0 = sContact.m_vT0;
        psContact->m_vDepth = sContact.m_vDepth;

        ++psPacket->m_nuiContact;

        return (KTgS_OK);
    };
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- FCN_VO(tgCO_PC_Internal_Sweep_ET) ---------------------------------------------------------------------------------------------------------------------------------------- */
/*                                                                                                                                                                                 */
/*   The culling situation for a particle is complicated by its parabolic path of motion.  Back face culling is done on a point by                                                 */
/*  point basis.  Thus, it is possible for a particle to ignore a triangle as it comes up through the back face and then collide                                                   */
/*  with it as it descends through the front face.                                                                                                                                 */
/*                                                                                                                                                                                 */
/* Input:  psET0: Edge triangle primitive - also undergoing a linear translation                                                                                                   */
/* Input:  psPC0: Particle - this primitive is undergoing the sweep/translation.                                                                                                   */
/* Input:  vRV:  Relative velocity of the particle                                                                                                                                 */
/* Output: sContact: Contact point if one is registered for the time period.                                                                                                       */
/* Return: Result Code                                                                                                                                                             */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT FCN_VO(tgCO_PC_Internal_Sweep_ET)( VEC_OBJ_T(STg2_CO_Contact,PC) psContact, VEC_OBJ_T(TgPARTICLE,CPC) psPC0, VEC_T(1,C) vRV, VEC_OBJ_T(TgETRI,CPC) psET0 )
{
    VEC_T(1)                            vT0;

    VEC_T(1,C)                          vK0 = FCN_V(tgMH_SUB)( psPC0->m_vPos, psET0->m_sPT.m_avPoint[0] );
    VEC_T(1,C)                          vDist = FCN_V(tgMH_DOT)( psET0->m_sPT.m_vNormal, vK0 );
    VEC_T(1,C)                          vA_N = FCN_V(tgMH_DOT)( psET0->m_sPT.m_vNormal, psPC0->m_vAccel );
    VEC_T(1,C)                          vRV_N = FCN_V(tgMH_DOT)( psET0->m_sPT.m_vNormal, vRV );
    VEC_T(1,C)                          vZR = FCN_V(tgMH_SET1)( TYPE_K(0) );

    /* Check to see if the particle is moving away from the triangle plane. */

    if (   FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vDist, vZR ) )
        && FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GE)( vRV_N, vZR ) )
        && FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GE)( vA_N, vZR ) ))
    {
        return (KTgE_NO_INTERSECT);
    };

    if (   FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vDist, vZR ) )
        && FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( vRV_N, vZR ) )
        && FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( vA_N, vZR ) ))
    {
        return (KTgE_NO_INTERSECT);
    };

    if (FCN_V(tgMH_Is_NR0)( vA_N ))
    {
        /*  The particle's acceleration is completely parallel to the triangle plane.  In this case, intersection can only exist if there is a velocity component towards
           the triangle. In that case, the equation is only first order (linear). If the velocity's projection onto the triangle normal is positive then the particle can
           only intersect with the back face of the triangle - a case which is ignored. */

        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GE)( vRV_N, vZR ) ) || FCN_V(tgMH_Is_NR0)( vRV_N ))
        {
            return (KTgE_NO_INTERSECT);
        };

        vT0 = FCN_V(tgMH_DIV)( FCN_V(tgMH_NEG)( vDist ), vRV_N );

        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vT0, vZR ) ))
        {
            /* Sanity check - this can occur because floating point error and epsilon testing. */

            return (KTgE_NO_INTERSECT);
        };
    }
    else
    {
        /*  The particle has an acceleration component towards the triangle plane.  The equation of motion is a quadratic and thus, will have two solutions.  The desired
           answer will be the first positive root. */

        VEC_T(1,C)                          vX0 = FCN_V(tgMH_SET1)( -TYPE_K(2) );
        VEC_T(1,C)                          vX1 = FCN_V(tgMH_MUL)( vRV_N, vRV_N );
        VEC_T(1,C)                          vX2 = FCN_V(tgMH_MUL)( vA_N, vDist );
        VEC_T(1,C)                          vDSC = FCN_V(tgMH_MAD)( vX0, vX2, vX1 );

        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vDSC, vZR ) ))
        {
            /* There is no real result for the given discriminant. This should never occur given the other logic before this point. Register an error and return a
               non-intersection. */

            TgWARN_CO(u8"[PA][ET] Unexpected invalid discriminant in calculation.\n");
            return (KTgE_NO_INTERSECT);
        }
        else
        {
            /*   The math dictates that only one solution can possibly satisfy the constraints on the solution.  Specifically, the requirement that the velocity of the particle at
                the time of intersection have a negative projection on the triangle's normal eliminates the second root of the solution set.

                N•(r + t•a) < 0.0, t = (-(r•N) ± β) / (a•N)
                N•r + t•(N•a) < 0.0
                N•r + ((-(r•N) ± β) / (a•N))•(N•a) < 0.0
                N•r + (-(r•N) ± β) < 0.0
                ± β < 0.0

                 β is known to always be positive since the solution space is restricted to the real plane.  The root constructed with the positive square root value can never 
                satisfy the velocity requirement, and thus, can always be ignored. */

            VEC_T(1,C)                          vSQRT_DSC = FCN_V(tgMH_SQRT)( vDSC );
            VEC_T(1,C)                          vNEG_RV_N = FCN_V(tgMH_NEG)( vRV_N );

            TgBOOL_C                            bCMP_0 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vA_N, vZR ));
            TgBOOL_C                            bCMP_1 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vNEG_RV_N, vSQRT_DSC ));
            TgBOOL_C                            bCMP_2 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vA_N, vZR ));
            TgBOOL_C                            bCMP_3 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vNEG_RV_N, vSQRT_DSC ));

            /* Check to see if the derived value for T0 would be negative, and if so, return with no intersection. */

            if ((bCMP_0 && bCMP_1) || (bCMP_2 && bCMP_3))
            {
                return (KTgE_NO_INTERSECT);
            };

            vT0 = FCN_V(tgMH_DIV)( FCN_V(tgMH_NEG)( FCN_V(tgMH_ADD)( vRV_N, vSQRT_DSC ) ), vA_N );
        };
    };

    /* Compute the point on the triangle plane and then test to see if its contained within the triangle itself. */
    {
        VEC_T(1,C)                          vK2 = FCN_V(tgMH_MUL)( vRV, vT0 );
        VEC_T(1,C)                          vK1 = FCN_V(tgMH_ADD)( psPC0->m_vPos, vK2 );
        VEC_T(1,C)                          vK4 = FCN_V(tgMH_MUL)( vT0, vT0 );
        VEC_T(1,C)                          vK3 = FCN_V(tgMH_MUL)( psPC0->m_vAccel, vK4 );

        psContact->m_vS0 = FCN_V(tgMH_ADD)( vK1, vK3 );
        psContact->m_vN0 = psET0->m_sPT.m_vNormal;
        psContact->m_vT0 = vT0;
        psContact->m_vDepth = FCN_V(tgMH_SET1)( TYPE_K(0) );

        return (KTgS_OK);
    };
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
