/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Plane-Ray.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_PLANE_RAY_INL)
#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* == Collision ================================================================================================================================================================== */

/* ---- FCN_VO(tgCO_PN_DistSq_RY) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_PN_DistSq_RY)( VEC_OBJ_T(TgPLANE,CPC) psPN0, VEC_OBJ_T(TgRAY,CPC) psRY0 )
{
    if (FCN_V(tgMH_Is_NR0)( FCN_V(tgMH_DOT)( psPN0->m_vNormal, psRY0->m_vDirN ) ))
    {
        VEC_T(1,C)                          vDist = FCN_VO(tgCO_PN_Sign_Dist_PT)( psPN0, psRY0->m_vOrigin );
        VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_GE)( vDist, FCN_V(tgMH_SET1)( TYPE_K(0) ) );

        return (FCN_V(tgMH_MUL)( vDist, vDist ));
    };

    return (FCN_V(tgMH_SET1)( -VAR_K(KTgMAX) ));
}


/* ---- FCN_VO(tgCO_PN_Dist_RY) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_PN_Dist_RY)( VEC_OBJ_T(TgPLANE,CPC) psPN0, VEC_OBJ_T(TgRAY,CPC) psRY0 )
{
    if (FCN_V(tgMH_Is_NR0)( FCN_V(tgMH_DOT)( psPN0->m_vNormal, psRY0->m_vDirN ) ))
    {
        VEC_T(1,C)                          vDist = FCN_VO(tgCO_PN_Sign_Dist_PT)( psPN0, psRY0->m_vOrigin );
        VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_GE)( vDist, FCN_V(tgMH_SET1)( TYPE_K(0) ) );

        return (vDist);
    };

    return (FCN_V(tgMH_SET1)( -VAR_K(KTgMAX) ));
}


/* ---- FCN_VO(tgCO_PN_ClosestSq_RY) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_PN_ClosestSq_RY)( VEC_T(1,PC) pvPN0, VEC_T(1,PC) pvRY0, VEC_OBJ_T(TgPLANE,CPC) psPN0, VEC_OBJ_T(TgRAY,CPC) psRY0 )
{
    if (!FCN_V(tgMH_Is_NR0)( FCN_V(tgMH_DOT)( psPN0->m_vNormal, psRY0->m_vDirN ) ))
    {
        return (FCN_V(tgMH_SET1)( -VAR_K(KTgMAX) ));
    }
    else
    {
        VEC_T(1,C)                          vDist = FCN_VO(tgCO_PN_Sign_Dist_PT)( psPN0, psRY0->m_vOrigin );
        VEC_T(1,C)                          vK0 = FCN_V(tgMH_MUL)( vDist, psPN0->m_vNormal );
        VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_GE)( vDist, FCN_V(tgMH_SET1)( TYPE_K(0) ) );

        *pvPN0 = FCN_V(tgMH_SUB)( psRY0->m_vOrigin, vK0 );
        *pvRY0 = psRY0->m_vOrigin;

        return (FCN_V(tgMH_MUL)( vDist, vDist ));
    };
}


/* ---- FCN_VO(tgCO_PN_Closest_RY) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_PN_Closest_RY)( VEC_T(1,PC) pvPN0, VEC_T(1,PC) pvRY0, VEC_OBJ_T(TgPLANE,CPC) psPN0, VEC_OBJ_T(TgRAY,CPC) psRY0 )
{
    if (FCN_V(tgMH_Is_NR0)( FCN_V(tgMH_DOT)( psPN0->m_vNormal, psRY0->m_vDirN ) ))
    {
        return (FCN_V(tgMH_SET1)( -VAR_K(KTgMAX) ));
    }
    else
    {
        VEC_T(1,C)                          vDist = FCN_VO(tgCO_PN_Sign_Dist_PT)( psPN0, psRY0->m_vOrigin );
        VEC_T(1,C)                          vK0 = FCN_V(tgMH_MUL)( vDist, psPN0->m_vNormal );
        VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_GE)( vDist, FCN_V(tgMH_SET1)( TYPE_K(0) ) );

        *pvPN0 = FCN_V(tgMH_SUB)( psRY0->m_vOrigin, vK0 );
        *pvRY0 = psRY0->m_vOrigin;

        return (vDist);
    };
}


/* ---- FCN_VO(tgCO_PN_ClosestSq_PM_RY) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_PN_ClosestSq_PM_RY)( VEC_T(1,PC) pvPN0, VEC_T(1,PC) pvRY0, VEC_OBJ_T(TgPLANE,CPC) psPN0, VEC_OBJ_T(TgRAY,CPC) psRY0 )
{
    if (FCN_V(tgMH_Is_NR0)( FCN_V(tgMH_DOT)( psPN0->m_vNormal, psRY0->m_vDirN ) ))
    {
        return (FCN_V(tgMH_SET1)( -VAR_K(KTgMAX) ));
    }
    else
    {
        VEC_T(1,C)                          vDist = FCN_VO(tgCO_PN_Sign_Dist_PT)( psPN0, psRY0->m_vOrigin );
        VEC_T(1,C)                          vK0 = FCN_V(tgMH_MUL)( vDist, psPN0->m_vNormal );
        VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_GE)( vDist, FCN_V(tgMH_SET1)( TYPE_K(0) ) );

        *pvPN0 = FCN_V(tgMH_SUB)( psRY0->m_vOrigin, vK0 );
        *pvRY0 = FCN_V(tgMH_SET1)( TYPE_K(0) );

        return (FCN_V(tgMH_MUL)( vDist, vDist ));
    };
}


/* ---- FCN_VO(tgCO_PN_Closest_PM_RY) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_PN_Closest_PM_RY)( VEC_T(1,PC) pvPN0, VEC_T(1,PC) pvRY0, VEC_OBJ_T(TgPLANE,CPC) psPN0, VEC_OBJ_T(TgRAY,CPC) psRY0 )
{
    if (FCN_V(tgMH_Is_NR0)( FCN_V(tgMH_DOT)( psPN0->m_vNormal, psRY0->m_vDirN ) ))
    {
        return (FCN_V(tgMH_SET1)( -VAR_K(KTgMAX) ));
    }
    else
    {
        VEC_T(1,C)                          vDist = FCN_VO(tgCO_PN_Sign_Dist_PT)( psPN0, psRY0->m_vOrigin );
        VEC_T(1,C)                          vK0 = FCN_V(tgMH_MUL)( vDist, psPN0->m_vNormal );
        VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_GE)( vDist, FCN_V(tgMH_SET1)( TYPE_K(0) ) );

        *pvPN0 = FCN_V(tgMH_SUB)( psRY0->m_vOrigin, vK0 );
        *pvRY0 = FCN_V(tgMH_SET1)( TYPE_K(0) );

        return (vDist);
    };
}


/* ---- FCN_VO(tgCO_PN_Test_RY) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_VO(tgCO_PN_Test_RY)(VEC_OBJ_T(TgPLANE,CPC) psPN0, VEC_OBJ_T(TgRAY,CPC) psRY0)
{
    return (!FCN_V(tgMH_Is_NR0)( FCN_V(tgMH_DOT)( psPN0->m_vNormal, psRY0->m_vDirN ) ));
}


/* ---- FCN_VO(tgCO_PN_Intersect_PM_RY) --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_PN_Intersect_PM_RY)( VEC_T(1,PC) pvRY0, VEC_OBJ_T(TgPLANE,CPC) psPN0, VEC_OBJ_T(TgRAY,CPC) psRY0 )
{
    VEC_T(1,C)                          vD1_N = FCN_V(tgMH_DOT)( psPN0->m_vNormal, psRY0->m_vDirN );

    if (FCN_V(tgMH_Is_NR0)( vD1_N ))
    {
        return (KTgE_NO_INTERSECT);
    }
    else
    {
        VEC_T(1,C)                          vDist = FCN_VO(tgCO_PN_Sign_Dist_PT)( psPN0, psRY0->m_vOrigin );

        *pvRY0 = FCN_V(tgMH_DIV)( FCN_V(tgMH_NEG)( vDist ), vD1_N );

        return (KTgS_OK);
    };
}


/* ---- FCN_VO(tgCO_PN_Intersect_RY) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_PN_Intersect_RY)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_OBJ_T(TgPLANE,CPC) psPN0, VEC_OBJ_T(TgRAY,CPC) psRY0 )
{
    VEC_OBJ_T(STg2_CO_Contact,P)        psContact;

    VEC_T(1,C)                          vD1_N = FCN_V(tgMH_DOT)( psPN0->m_vNormal, psRY0->m_vDirN );

    TgPARAM_CHECK( FCN_VO(tgGM_PN_Is_Valid)( psPN0 ) && FCN_VO(tgGM_RY_Is_Valid)( psRY0 ) );

    if (0 == psPacket->m_nuiMaxContact || psPacket->m_nuiContact >= psPacket->m_nuiMaxContact || nullptr == psPacket->m_psContact)
    {
        return (KTgE_FAIL);
    }
    else if (FCN_V(tgMH_Is_NR0)( vD1_N ))
    {
        return (KTgE_NO_INTERSECT);
    }
    else
    {
        VEC_T(1,C)                          vDist = FCN_VO(tgCO_PN_Sign_Dist_PT)( psPN0, psRY0->m_vOrigin );
        VEC_T(1,C)                          vT0 = FCN_V(tgMH_DIV)( FCN_V(tgMH_NEG)( vDist ), vD1_N );
        VEC_T(1,C)                          vK0 = FCN_V(tgMH_MUL)( vT0, psRY0->m_vDirN );
        VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_GE)( vDist, FCN_V(tgMH_SET1)( TYPE_K(0) ) );
        VEC_T(1,C)                          vX0 = FCN_V(tgMH_SEL)( FCN_V(tgMH_SET1)( -TYPE_K(1) ), FCN_V(tgMH_SET1)( TYPE_K(1) ), vCMP_0 );

        psContact = psPacket->m_psContact + psPacket->m_nuiContact;

        psContact->m_vS0 = FCN_V(tgMH_ADD)( psRY0->m_vOrigin, vK0 );
        psContact->m_vN0 = FCN_V(tgMH_MUL)( vX0, psPN0->m_vNormal );
        psContact->m_vT0 = vT0;
        psContact->m_vDepth = FCN_V(tgMH_SET1)( TYPE_K(0) );

        ++psPacket->m_nuiContact;

        return (KTgS_OK);
    };
}


/* ---- FCN_VO(tgCO_PN_Clip_PM_RY) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_PN_Clip_PM_RY)( VEC_T(1,PC) pvRY0, VEC_T(1,PC) pvRY1, VEC_OBJ_T(TgPLANE,CPC) psPN0, VEC_OBJ_T(TgRAY,CPC) psRY0 )
{
    return (FCN_VO(tgCO_PN_Clip_PM_LR10)( pvRY0, pvRY1, psPN0, psRY0->m_vOrigin, psRY0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_PN_Clip_RY) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_PN_Clip_RY)( VEC_OBJ_T(STg2_CO_Clip_List,PC) psCL, VEC_OBJ_T(TgPLANE,CPC) psPN0, VEC_OBJ_T(TgRAY,CPC) psRY0 )
{
    return (FCN_VO(tgCO_PN_Clip_LR10)( psCL, psPN0, psRY0->m_vOrigin, psRY0->m_vDirN ));
}


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* =============================================================================================================================================================================== */

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#else

    #define TEMPLATE_TYPE_EXPANSION__RELOAD

    #if TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE
        #define TEMPLATE__VECTOR_DIM 4
        #define TEMPLATE__TYPE_SIZE 64
        #include __FILE__
    #endif

    #define TEMPLATE__VECTOR_DIM 4
    #define TEMPLATE__TYPE_SIZE 32
    #include __FILE__

    #undef TEMPLATE_TYPE_EXPANSION__RELOAD

    #define TGS_COLLISION_PLANE_RAY_INL

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COLLISION_PLANE_RAY_INL) */
#endif
