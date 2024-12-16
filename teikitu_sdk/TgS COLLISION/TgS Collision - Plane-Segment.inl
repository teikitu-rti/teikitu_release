/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Plane-Segment.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_PLANE_SEGMENT_INL)

#include "TgS COLLISION/TgS Collision - Plane-Point.inl"
#include "TgS COLLISION/TgS Collision - Plane-Linear.inl"

#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
/* TODO P0 This is all wrong as it does take into account the segment - like WTF */

/* == Collision ================================================================================================================================================================== */

/* ---- FCN_VO(tgCO_PN_DistSq_SG) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_PN_DistSq_SG)( VEC_OBJ_T(TgPLANE,CPC) psPN0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    if (FCN_V(tgMH_Is_NR0)( FCN_V(tgMH_DOT)( psPN0->m_vNormal, psSG0->m_vDirN ) ))
    {
        VEC_T(1,C)                          vDist = FCN_VO(tgCO_PN_Sign_Dist_PT)( psPN0, psSG0->m_vOrigin );
        VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_GE)( vDist, FCN_V(tgMH_SET1)( TYPE_K(0) ) );

        return (FCN_V(tgMH_SEL)( FCN_V(tgMH_SET1)( -VAR_K(KTgMAX) ), FCN_V(tgMH_MUL)( vDist, vDist ), vCMP_0 ));
    };

    return (FCN_V(tgMH_SET1)( -VAR_K(KTgMAX) ));
}


/* ---- FCN_VO(tgCO_PN_Dist_SG) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_PN_Dist_SG)( VEC_OBJ_T(TgPLANE,CPC) psPN0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    if (FCN_V(tgMH_Is_NR0) (FCN_V(tgMH_DOT)( psPN0->m_vNormal, psSG0->m_vDirN ) ))
    {
        VEC_T(1,C)                          vDist = FCN_VO(tgCO_PN_Sign_Dist_PT)( psPN0, psSG0->m_vOrigin );
        VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_GE)( vDist, FCN_V(tgMH_SET1)( TYPE_K(0) ) );

        return (FCN_V(tgMH_SEL)( FCN_V(tgMH_SET1)( -VAR_K(KTgMAX) ), vDist, vCMP_0 ));
    };

    return (FCN_V(tgMH_SET1)( -VAR_K(KTgMAX) ));
}


/* ---- FCN_VO(tgCO_PN_ClosestSq_SG) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_PN_ClosestSq_SG)( VEC_T(1,PC) pvPN0, VEC_T(1,PC) pvSG0, VEC_OBJ_T(TgPLANE,CPC) psPN0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    if (!FCN_V(tgMH_Is_NR0)( FCN_V(tgMH_DOT)( psPN0->m_vNormal, psSG0->m_vDirN ) ))
    {
        return (FCN_V(tgMH_SET1)( -VAR_K(KTgMAX) ));
    }
    else
    {
        VEC_T(1,C)                          vDist = FCN_VO(tgCO_PN_Sign_Dist_PT)( psPN0, psSG0->m_vOrigin );
        VEC_T(1,C)                          vX0 = FCN_V(tgMH_MUL)( vDist, psPN0->m_vNormal );
        VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_GE)( vDist, FCN_V(tgMH_SET1)( TYPE_K(0) ) );

        *pvPN0 = FCN_V(tgMH_SUB)( psSG0->m_vOrigin, vX0 );
        *pvSG0 = psSG0->m_vOrigin;

        return (FCN_V(tgMH_SEL)( FCN_V(tgMH_SET1)( -VAR_K(KTgMAX) ), FCN_V(tgMH_MUL)( vDist, vDist ), vCMP_0 ));
    };
}


/* ---- FCN_VO(tgCO_PN_Closest_SG) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_PN_Closest_SG)( VEC_T(1,PC) pvPN0, VEC_T(1,PC) pvSG0, VEC_OBJ_T(TgPLANE,CPC) psPN0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    if (FCN_V(tgMH_Is_NR0)( FCN_V(tgMH_DOT)( psPN0->m_vNormal, psSG0->m_vDirN ) ))
    {
        return (FCN_V(tgMH_SET1)( -VAR_K(KTgMAX) ));
    }
    else
    {
        VEC_T(1,C)                          vDist = FCN_VO(tgCO_PN_Sign_Dist_PT)( psPN0, psSG0->m_vOrigin );
        VEC_T(1,C)                          vK0 = FCN_V(tgMH_MUL)( vDist, psPN0->m_vNormal );
        VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_GE)( vDist, FCN_V(tgMH_SET1)( TYPE_K(0) ) );

        *pvPN0 = FCN_V(tgMH_SUB)( psSG0->m_vOrigin, vK0 );
        *pvSG0 = psSG0->m_vOrigin;

        return (FCN_V(tgMH_SEL)( FCN_V(tgMH_SET1)( -VAR_K(KTgMAX) ), vDist, vCMP_0 ));
    };
}


/* ---- FCN_VO(tgCO_PN_ClosestSq_PM_SG) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_PN_ClosestSq_PM_SG)( VEC_T(1,PC) pvPN0, VEC_T(1,PC) pvSG0, VEC_OBJ_T(TgPLANE,CPC) psPN0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    if (FCN_V(tgMH_Is_NR0)( FCN_V(tgMH_DOT)( psPN0->m_vNormal, psSG0->m_vDirN ) ))
    {
        return (FCN_V(tgMH_SET1)( -VAR_K(KTgMAX) ));
    }
    else
    {
        VEC_T(1,C)                          vDist = FCN_VO(tgCO_PN_Sign_Dist_PT)( psPN0, psSG0->m_vOrigin );
        VEC_T(1,C)                          vK0 = FCN_V(tgMH_MUL)( vDist, psPN0->m_vNormal );
        VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_GE)( vDist, FCN_V(tgMH_SET1)( TYPE_K(0) ) );

        *pvPN0 = FCN_V(tgMH_SUB)( psSG0->m_vOrigin, vK0 );
        *pvSG0 = FCN_V(tgMH_SET1)( TYPE_K(0) );

        return (FCN_V(tgMH_SEL)( FCN_V(tgMH_SET1)( -VAR_K(KTgMAX) ), FCN_V(tgMH_MUL)( vDist, vDist ), vCMP_0 ));
    };
}


/* ---- FCN_VO(tgCO_PN_Closest_PM_SG) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_PN_Closest_PM_SG)( VEC_T(1,PC) pvPN0, VEC_T(1,PC) pvSG0, VEC_OBJ_T(TgPLANE,CPC) psPN0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    if (FCN_V(tgMH_Is_NR0)( FCN_V(tgMH_DOT)( psPN0->m_vNormal, psSG0->m_vDirN ) ))
    {
        return (FCN_V(tgMH_SET1)( -VAR_K(KTgMAX) ));
    }
    else
    {
        VEC_T(1,C)                          vDist = FCN_VO(tgCO_PN_Sign_Dist_PT)( psPN0, psSG0->m_vOrigin );
        VEC_T(1,C)                          vK0 = FCN_V(tgMH_MUL)( vDist, psPN0->m_vNormal );
        VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_GE)( vDist, FCN_V(tgMH_SET1)( TYPE_K(0) ) );

        *pvPN0 = FCN_V(tgMH_SUB)( psSG0->m_vOrigin, vK0 );
        *pvSG0 = FCN_V(tgMH_SET1)( TYPE_K(0) );

        return (FCN_V(tgMH_SEL)( FCN_V(tgMH_SET1)( -VAR_K(KTgMAX) ), vDist, vCMP_0 ));
    };
}


/* ---- FCN_VO(tgCO_PN_Test_SG) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_VO(tgCO_PN_Test_SG)(VEC_OBJ_T(TgPLANE,CPC) psPN0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0)
{
    return (!FCN_V(tgMH_Is_NR0)( FCN_V(tgMH_DOT)( psPN0->m_vNormal, psSG0->m_vDirN ) ));
}


/* ---- FCN_VO(tgCO_PN_Intersect_PM_SG) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_PN_Intersect_PM_SG)( VEC_T(1,PC) pvSG0, VEC_OBJ_T(TgPLANE,CPC) psPN0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    VEC_T(1,C)                          vD1_N = FCN_V(tgMH_DOT)( psPN0->m_vNormal, psSG0->m_vDirN );

    if (FCN_V(tgMH_Is_NR0)( vD1_N ))
    {
        return (KTgE_NO_INTERSECT);
    }
    else
    {
        VEC_T(1,C)                          vDist = FCN_VO(tgCO_PN_Sign_Dist_PT)( psPN0, psSG0->m_vOrigin );

        *pvSG0 = FCN_V(tgMH_DIV)( FCN_V(tgMH_NEG)( vDist ), vD1_N );

        return (KTgS_OK);
    };
}


/* ---- FCN_VO(tgCO_PN_Intersect_SG) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_PN_Intersect_SG)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_OBJ_T(TgPLANE,CPC) psPN0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    VEC_OBJ_T(STg2_CO_Contact,P)        psContact;

    VEC_T(1)                            vD1_N = FCN_V(tgMH_DOT)( psPN0->m_vNormal, psSG0->m_vDirN );

    TgPARAM_CHECK( FCN_VO(tgGM_PN_Is_Valid)( psPN0 ) && FCN_VO(tgGM_SG_Is_Valid)( psSG0 ) );

    if (0 == psPacket->m_nuiMaxContact || psPacket->m_nuiContact >= psPacket->m_nuiMaxContact || nullptr == psPacket->m_psContact)
    {
        return (KTgE_FAIL);
    }
    else if (FCN_V(tgMH_Is_NR0)( vD1_N ))
    {
        return (KTgE_NO_INTERSECT); /* We ignore the cast where the segment is tangent to the plane. */
    }
    else
    {
        VEC_T(1,C)                          vDist = FCN_VO(tgCO_PN_Sign_Dist_PT)( psPN0, psSG0->m_vOrigin );
        VEC_T(1,C)                          vT0 = FCN_V(tgMH_DIV)( FCN_V(tgMH_NEG)( vDist ), vD1_N );
        VEC_T(1,C)                          vK0 = FCN_V(tgMH_MUL)( vT0, psSG0->m_vDirN );
        VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_GE)( vDist, FCN_V(tgMH_SET1)( TYPE_K(0) ) );
        VEC_T(1,C)                          vX0 = FCN_V(tgMH_SEL)( FCN_V(tgMH_SET1)( -TYPE_K(1) ), FCN_V(tgMH_SET1)( TYPE_K(1) ), vCMP_0 );

        psContact = psPacket->m_psContact + psPacket->m_nuiContact;

        psContact->m_vS0 = FCN_V(tgMH_ADD)( psSG0->m_vOrigin, vK0 ) ;
        psContact->m_vN0 = FCN_V(tgMH_MUL)( vX0, psPN0->m_vNormal );
        psContact->m_vT0 = vT0;
        psContact->m_vDepth = FCN_V(tgMH_SET1)( TYPE_K(0) );

        ++psPacket->m_nuiContact;

        return (KTgS_OK);
    };
}


/* ---- FCN_VO(tgCO_PN_Clip_PM_SG) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_PN_Clip_PM_SG)( VEC_T(1,PC) pvSG0, VEC_T(1,PC) pvSG1, VEC_OBJ_T(TgPLANE,CPC) psPN0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    return (FCN_VO(tgCO_PN_Clip_PM_LR11)( pvSG0, pvSG1, psPN0, psSG0->m_vOrigin, psSG0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_PN_Clip_SG) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_PN_Clip_SG)( VEC_OBJ_T(STg2_CO_Clip_List,PC) psCL, VEC_OBJ_T(TgPLANE,CPC) psPN0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    return (FCN_VO(tgCO_PN_Clip_LR11)( psCL, psPN0, psSG0->m_vOrigin, psSG0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_PN_Clip_Points) ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_PN_Clip_Points)( VEC_T(1,PC) pvSG0, VEC_T(1,PC) pvSG1, VEC_OBJ_T(TgPLANE,CPC) psPN0, VEC_T(1,C) vS0, VEC_T(1,C) vS1 )
{
    VEC_T(1)                              vD0;

    vD0 = FCN_V(tgMH_SUB)( vS1, vS0 );
    return (FCN_VO(tgCO_PN_Clip_PM_LR11)( pvSG0, pvSG1, psPN0, vS0, vD0 ));
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

    #define TGS_COLLISION_PLANE_SEGMENT_INL

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COLLISION_PLANE_SEGMENT_INL) */
#endif
