/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Box AA-Sphere.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

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

/* ---- FCN_VO(tgCO_BA_Penetrate_SP) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN_VO(tgCO_BA_Penetrate_SP)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_OBJ_T(TgBOXAA,CPC) psBA0, VEC_OBJ_T(TgSPHERE,CPC) psSP0 )
{
    TgPARAM_CHECK( FCN_VO(tgGM_BA_Is_Valid)( psBA0 ) && FCN_VO(tgGM_SP_Is_Valid)( psSP0 ) );

    if ( 0 == psPacket->m_nuiMaxContact || nullptr == psPacket->m_psContact )
    {
        return (KTgE_FAIL);
    }
    else
{
        /* Find the point of closest proximity on the box to the sphere's origin and create a normalized direction vector of the difference between the two points. */
        /* These are the potential contact points and normal. */

        VEC_T(1)                            vNormal_Length;
        VEC_OBJ_T(STg2_CO_Contact,P)        psContact;

        VEC_T(1,C)                          vSP0_C0 = FCN_VO(tgGM_SP_Query_Origin)( psSP0 );
        VEC_T(1,C)                          vBA0_Min = FCN_VO(tgGM_BA_Query_Min)( psBA0 );
        VEC_T(1,C)                          vBA0_Max = FCN_VO(tgGM_BA_Query_Max)( psBA0 );
        VEC_T(1,C)                          vP1 = FCN_V(tgMH_CLP)( vSP0_C0, vBA0_Min, vBA0_Max );

        VEC_T(1,C)                          vDS = FCN_V(tgMH_SUB)( vP1, vSP0_C0 );
        VEC_T(1,C)                          vNormal = FCN_V(tgMH_NORM_LEN)( &vNormal_Length, vDS );

        VEC_T(1,C)                          vDepth = FCN_V(tgMH_SUB)( FCN_VO(tgGM_SP_Query_Radius)( psSP0 ), FCN_V(tgMH_Init_Vector)( vNormal_Length ) );
        VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_LT)( vDepth, FCN_V(tgMH_SET1)( TYPE_K(0) ) );

        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_0 ))
        {
            return (KTgE_NO_INTERSECT);
        };

        if (0 == psPacket->m_nuiMaxContact || nullptr == psPacket->m_psContact)
        {
            return (KTgE_FAIL);
        };

        psContact = psPacket->m_psContact + psPacket->m_nuiContact;

        if (!FCN_V(tgMH_Is_NR0)( vNormal_Length ))
        {
            /* Sphere origin is not contained inside of the box, and therefore the potential contact values are correct. */

            psContact->m_vS0 = vP1;
            psContact->m_vN0 = vNormal;
            psContact->m_vT0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
            psContact->m_vDepth =  vDepth;

            ++psPacket->m_nuiContact;

            return (KTgS_OK);
        }
        else
        {
            /* Sphere origin is contained within the box itself - find the axis of minimum penetration. */

            /* Select the smallest distance from origin to a box face */
            VEC_T(1,C)                          vX0 = FCN_V(tgMH_SUB)( vSP0_C0, vBA0_Min );
            VEC_T(1,C)                          vX1 = FCN_V(tgMH_SUB)( vBA0_Max, vSP0_C0 );
            VEC_T(1,C)                          vCMP_1 = FCN_V(tgMH_CMP_LT)( vX0, vX1 );
            VEC_T(1,C)                          vX2 = FCN_V(tgMH_SEL)( vX1, vX0, vCMP_1 );

            /* Find the minimal axis - compare x and y */
            VEC_T(1,C)                          vX3 = FCN_V(tgMH_SPX)( vX2 );
            VEC_T(1,C)                          vX4 = FCN_V(tgMH_SPY)( vX2 );
            VEC_T(1,C)                          vCMP_2 = FCN_V(tgMH_CMP_LT)( vX3, vX4 );
            VEC_T(1,C)                          vX5 = FCN_V(tgMH_SEL)( vX4, vX3, vCMP_2 );

            /* Find the minimal axis - compare above result to z */
            VEC_T(1,C)                          vX6 = FCN_V(tgMH_SPZ)( vX2 );
            VEC_T(1,C)                          vCMP_3 = FCN_V(tgMH_CMP_LT)( vX5, vX6 );

            VEC_T(1,C)                          vX7 = FCN_V(tgMH_SEL)( VEC_K(KTgUNIT_Y), VEC_K(KTgUNIT_X), vCMP_2 );
            VEC_T(1,C)                          vX8 = FCN_V(tgMH_SEL)( VEC_K(KTgUNIT_Z), vX7, vCMP_3 );
            VEC_T(1,C)                          vX9 = FCN_V(tgMH_SEL)( vX8, FCN_V(tgMH_NEG)( vX8 ), vCMP_1 ); /* Contact Normal */
            VEC_T(1,C)                          vXA = FCN_V(tgMH_MAD)( vX9, vX2, vSP0_C0 ); /* Contact Position */
            VEC_T(1,C)                          vXB = FCN_V(tgMH_DOT)( vX8, vX2 ); /* Contact Depth of the Origin */

            psContact->m_vS0 = vXA;
            psContact->m_vN0 = vX9;
            psContact->m_vT0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
            psContact->m_vDepth = FCN_V(tgMH_ADD)( vXB, FCN_VO(tgGM_SP_Query_Radius)( psSP0 ) );

            ++psPacket->m_nuiContact;
            return (KTgS_OK);
        };
    };
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
