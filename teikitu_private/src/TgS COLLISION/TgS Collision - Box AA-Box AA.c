/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Box AA-Box AA.c
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

/* ---- FCN_VO(tgCO_BA_ClosestSq_BA) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
VEC_T(1) FCN_VO(tgCO_BA_ClosestSq_BA)( VEC_T(1,PC) pvBA0, VEC_T(1,PC) pvBA1, VEC_OBJ_T(TgBOXAA,CPC) psBA0, VEC_OBJ_T(TgBOXAA,CPC) psBA1 )
{
    VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_LE)( psBA0->m_vMin, psBA1->m_vMin );
    VEC_T(1,C)                          vX1 = FCN_V(tgMH_SEL)( psBA0->m_vMin, psBA1->m_vMin, vCMP_0 );
    VEC_T(1,C)                          vCMP_1 = FCN_V(tgMH_CMP_GE)( psBA0->m_vMax, psBA1->m_vMax );
    VEC_T(1,C)                          vX2 = FCN_V(tgMH_SEL)( psBA0->m_vMax, psBA1->m_vMax, vCMP_1 );
    VEC_T(1,C)                          vX3 = FCN_V(tgMH_SUB)( vX1, vX2 );
    VEC_T(1,C)                          vX4 = FCN_V(tgMH_MAX)( FCN_V(tgMH_SET1)( TYPE_K(0) ), vX3 );
    VEC_T(1,C)                          vDistSq = FCN_V(tgMH_LSQ)( vX4 );

    VEC_T(1,C)                          vK0 = FCN_V(tgMH_AVG)( vX1, vX2 );

    VEC_T(1,C)                          vK1 = FCN_V(tgMH_SEL)( psBA0->m_vMin, vK0, vCMP_0 );
    VEC_T(1,C)                          vK2 = FCN_V(tgMH_SEL)( psBA0->m_vMax, vK1, vCMP_1 );
    VEC_T(1,C)                          vK3 = FCN_V(tgMH_SEL)( vK0, psBA1->m_vMin, vCMP_0 );
    VEC_T(1,C)                          vK4 = FCN_V(tgMH_SEL)( vK3, psBA1->m_vMax, vCMP_1 );

    *pvBA0 = FCN_V(tgMH_Init_Point)( vK2 );
    *pvBA1 = FCN_V(tgMH_Init_Point)( vK4 );

    return (vDistSq);
}


/* ---- FCN_VO(tgCO_BA_Penetrate_BA) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN_VO(tgCO_BA_Penetrate_BA)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_OBJ_T(TgBOXAA,CPC) psBA0, VEC_OBJ_T(TgBOXAA,CPC) psBA1 )
{
    TgPARAM_CHECK( FCN_VO(tgGM_BA_Is_Valid)(psBA1) && FCN_VO(tgGM_BA_Is_Valid)(psBA0) );

    if (0 == psPacket->m_nuiMaxContact || nullptr == psPacket->m_psContact)
    {
        return (KTgE_FAIL);
    }
    else
    {
        VEC_T(1,C)                          vF0 = FCN_V(tgMH_SUB)( psBA0->m_vMin, FCN_V(tgMH_Init_Point)( psBA1->m_vMax ) ); /* Force a -1 for W */
        VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_GE)( vF0, FCN_V(tgMH_SET1)( TYPE_K(0) ) );  /* Axis separation test */
        VEC_T(1,C)                          vG0 = FCN_V(tgMH_SUB)( psBA1->m_vMin, FCN_V(tgMH_Init_Point)( psBA0->m_vMax ) ); /* Force a -1 for W */
        VEC_T(1,C)                          vCMP_1 = FCN_V(tgMH_CMP_GE)( vG0, FCN_V(tgMH_SET1)( TYPE_K(0) ) );  /* Axis separation test */

        VEC_OBJ_T(STg2_CO_Contact,P)        psContact;

        /* Axis separation test */
        if (FCN_V(tgMH_CMP_ANY_TO_BOOL)( vCMP_0 ) || FCN_V(tgMH_CMP_ANY_TO_BOOL)( vCMP_1 ))
        {
            return (KTgE_NO_INTERSECT);
        }
        else
        {
            /* Calculate the overlap region */
            VEC_T(1,C)                          vX0 = FCN_V(tgMH_MAX)( psBA0->m_vMin, psBA1->m_vMin );
            VEC_T(1,C)                          vX1 = FCN_V(tgMH_MIN)( psBA0->m_vMax, psBA1->m_vMax );

            /* Determine the axis of separation */
            VEC_T(1,C)                          vCMP_2 = FCN_V(tgMH_CMP_GT)( vF0, vG0 );
            VEC_T(1,C)                          vX2 = FCN_V(tgMH_SEL)( vG0, vF0, vCMP_2 );

            /* Determine the axis of separation: Find the minimal axis - compare x and y */
            VEC_T(1,C)                          vX3 = FCN_V(tgMH_SPX)( vX2 );
            VEC_T(1,C)                          vX4 = FCN_V(tgMH_SPY)( vX2 );
            VEC_T(1,C)                          vCMP_3 = FCN_V(tgMH_CMP_GT)( vX3, vX4 );
            VEC_T(1,C)                          vX5 = FCN_V(tgMH_SEL)( vX4, vX3, vCMP_3 );

            /* Determine the axis of separation: Find the minimal axis - compare above result to z */
            VEC_T(1,C)                          vX6 = FCN_V(tgMH_SPZ)( vX2 );
            VEC_T(1,C)                          vCMP_4 = FCN_V(tgMH_CMP_GT)( vX6, vX5 );

            /* Generate the contact normal */
            VEC_T(1,C)                          vX7 = FCN_V(tgMH_SEL)( VEC_K(KTgUNIT_Y), VEC_K(KTgUNIT_X), vCMP_3 );
            VEC_T(1,C)                          vX8 = FCN_V(tgMH_SEL)( vX7, VEC_K(KTgUNIT_Z), vCMP_4 );
            VEC_T(1,C)                          vN0 = FCN_V(tgMH_SEL)( FCN_V(tgMH_NEG)( vX8 ), vX8, vCMP_2 );

            /* Calculate Depth */
            VEC_T(1,C)                          vX9 = FCN_V(tgMH_SEL)( vX6, vX5, vCMP_4 );
            VEC_T(1,C)                          vDepth = FCN_V(tgMH_NEG)( vX9 );

            /* Generate the contact positions */
            VEC_T(1,C)                          vK0 = FCN_V(tgMH_SEL)( psBA1->m_vMin, psBA1->m_vMax, vCMP_2 );
            VEC_T(1,C)                          vK1 = FCN_V(tgMH_MUL)( vK0, vX8 ); /* Contact surface position on separating axis */

            VEC_T(1,C)                          vK2 = FCN_V(tgMH_Init_Vector_ELEM)( TYPE_K(1), TYPE_K(1), TYPE_K(1) );
            VEC_T(1,C)                          vK3 = FCN_V(tgMH_SUB)( vK2, vX8 );
            VEC_T(1,C)                          vK4 = FCN_V(tgMH_MUL)( vK3, vX0 ); /* Contact Plane - Point 0 */
            VEC_T(1,C)                          vK5 = FCN_V(tgMH_MUL)( vK3, vX1 ); /* Contact Plane - Point 3 */

            VEC_T(1,C)                          vK6 = FCN_V(tgMH_SEL)( VEC_K(KTgUNIT_X), VEC_K(KTgUNIT_Z), vCMP_3 );
            VEC_T(1,C)                          vK7 = FCN_V(tgMH_SEL)( vK6, VEC_K(KTgUNIT_Y), vCMP_4 );  /* Contact Plane Basis Vector 1 */
            VEC_T(1,C)                          vK8 = FCN_V(tgMH_SUB)( vK3, vK7 ); /* Contact Plane Basis Vector 2 */

            /* Point 1 */

            if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
            {
                return (KTgE_FAIL);
            };

            psContact = psPacket->m_psContact + psPacket->m_nuiContact;

            psContact->m_vS0 = FCN_V(tgMH_ADD)( vK1, vK4 );
            psContact->m_vN0 = vN0;
            psContact->m_vT0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
            psContact->m_vDepth = vDepth;

            ++psPacket->m_nuiContact;

            /* Point 2 */

            if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
            {
                return (KTgE_MAX_CONTACTS);
            };

            psContact = psPacket->m_psContact + psPacket->m_nuiContact;

            psContact->m_vS0 = FCN_V(tgMH_MAD)( vK7, vX0, FCN_V(tgMH_MAD)( vK8, vX1, vK1 ) );
            psContact->m_vN0 = vN0;
            psContact->m_vT0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
            psContact->m_vDepth = vDepth;

            ++psPacket->m_nuiContact;

            /* Point 3 */

            if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
            {
                return (KTgE_MAX_CONTACTS);
            };

            psContact = psPacket->m_psContact + psPacket->m_nuiContact;

            psContact->m_vS0 = FCN_V(tgMH_MAD)( vK8, vX0, FCN_V(tgMH_MAD)( vK7, vX1, vK1 ) );
            psContact->m_vN0 = vN0;
            psContact->m_vT0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
            psContact->m_vDepth = vDepth;

            ++psPacket->m_nuiContact;

            /* Point 4 */

            if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
            {
                return (KTgE_MAX_CONTACTS);
            };

            psContact = psPacket->m_psContact + psPacket->m_nuiContact;

            psContact->m_vS0 = FCN_V(tgMH_ADD)( vK1, vK5 );
            psContact->m_vN0 = vN0;
            psContact->m_vT0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
            psContact->m_vDepth = vDepth;

            ++psPacket->m_nuiContact;

            return (KTgS_OK);
        };
    };
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
