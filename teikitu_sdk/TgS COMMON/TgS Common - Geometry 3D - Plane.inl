/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Geometry 3D - Plane.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_GEOMETRY_3D_PLANE_INL)

#if !defined (TEMPLATE_TYPE_EXPANSION__RELOAD)
    #error Must be included as part of a type expansion include chain
#endif


/* == Common ===================================================================================================================================================================== */

/* ---- FCN_VO(tgGM_PN_Negate) --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_PN_Negate)( VEC_OBJ_T(TgPLANE,PCU) psPN0 )
{
    psPN0->m_vPlnEqN = FCN_V(tgMH_NEG)( psPN0->m_vPlnEqN );
    psPN0->m_vNormal = FCN_V(tgMH_NEG)( psPN0->m_vNormal );
    psPN0->m_vD = FCN_V(tgMH_NEG)( psPN0->m_vD );
}


/* ---- FCN_VO(tgGM_PN_Reset) ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_PN_Reset)( VEC_OBJ_T(TgPLANE,PCU) psPN0 )
{
    psPN0->m_vPlnEqN = FCN_V(tgMH_SET1)( TYPE_K(0) );
    psPN0->m_vNormal = FCN_V(tgMH_SET1)( TYPE_K(0) );
    psPN0->m_vD = FCN_V(tgMH_SET1)( TYPE_K(0) );
}


/* ---- FCN_VO(tgGM_PN_Is_Valid) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_VO(tgGM_PN_Is_Valid)( VEC_OBJ_T(TgPLANE,CPCU) psPN0 )
{
    if (!FCN_V(tgMH_Is_Valid_Broadcast_Scalar)( psPN0->m_vD ))
    {
        return (false);
    };

    if (!FCN_V(tgMH_Is_Valid_Unit_Vector)( psPN0->m_vNormal ))
    {
        return (false);
    };

    return (true);
}


/* ---- FCN_VO(tgGM_PN_Is_Contained) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_VO(tgGM_PN_Is_Contained)( VEC_OBJ_T(TgPLANE,CPCU) psPN0, VEC_T(1,C) vS0 )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_PN_Is_Valid)( psPN0 ) && FCN_V(tgMH_Is_Valid_Point)( vS0 ));

    {
        VEC_T(1,C)                          vX0 = FCN_V(tgMH_DOT3)( vS0, psPN0->m_vNormal );

        return (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( vX0, psPN0->m_vD ) ));
    }
}


/* ---- FCN_VO(tgGM_PN_TX) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_PN_TX)( VEC_OBJ_T(TgPLANE,PCU) psPN0, VEC_T(3,CPCU) pmM0 )
{
    TgGEOM_ASSERT_PARAM(!FCN_V(tgMH_NAN,3)( pmM0 ));

    {
        VEC_T(1,C)                          vS0 = FCN_V(tgMH_MUL)( psPN0->m_vNormal, FCN_V(tgMH_NEG)( psPN0->m_vD ) );
        VEC_T(1,C)                          vS1 = FCN_V(tgMH_TX_P,3)( vS0, pmM0 );
        VEC_UN_T(1,C)                       uN1 = { VEC_UN_1_MEMBER() = FCN_V(tgMH_TX_V,3)( psPN0->m_vNormal, pmM0 ) };
        VEC_UN_T(1,C)                       uD1 = { VEC_UN_1_MEMBER() = FCN_V(tgMH_NEG)( FCN_V(tgMH_DOT)( VEC_UN_1_MEMBER(uN1), vS1 ) ) };

        psPN0->m_vPlnEqN = FCN_V(tgMH_Init_ELEM)( VEC_S_UN_1_MEMBER(uN1).x, VEC_S_UN_1_MEMBER(uN1).y, VEC_S_UN_1_MEMBER(uN1).z, VEC_S_UN_1_MEMBER(uD1).x );
        psPN0->m_vNormal = VEC_UN_1_MEMBER(uN1);
        psPN0->m_vD = VEC_UN_1_MEMBER(uD1);
    }
}


/* ---- FCN_VO(tgGM_PN_Copy_TX) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_PN_Copy_TX)( VEC_OBJ_T(TgPLANE,PCU) psPN0, VEC_OBJ_T(TgPLANE,CPCU) psPN1, VEC_T(3,CPCU) pmM0 )
{
    TgGEOM_ASSERT_PARAM(!FCN_V(tgMH_NAN,3)( pmM0 ));

    {
        VEC_T(1,C)                          vS0 = FCN_V(tgMH_MUL)( psPN1->m_vNormal, FCN_V(tgMH_NEG)( psPN1->m_vD ) );
        VEC_T(1,C)                          vS1 = FCN_V(tgMH_TX_P,3)( vS0, pmM0 );
        VEC_UN_T(1,C)                       uN1 = { VEC_UN_1_MEMBER() = FCN_V(tgMH_TX_V,3)( psPN1->m_vNormal, pmM0 ) };
        VEC_UN_T(1,C)                       uD1 = { VEC_UN_1_MEMBER() = FCN_V(tgMH_NEG)( FCN_V(tgMH_DOT)( VEC_UN_1_MEMBER(uN1), vS1 ) ) };

        psPN0->m_vPlnEqN = FCN_V(tgMH_Init_ELEM)( VEC_S_UN_1_MEMBER(uN1).x, VEC_S_UN_1_MEMBER(uN1).y, VEC_S_UN_1_MEMBER(uN1).z, VEC_S_UN_1_MEMBER(uD1).x );
        psPN0->m_vNormal = VEC_UN_1_MEMBER(uN1);
        psPN0->m_vD = VEC_UN_1_MEMBER(uD1);
    }
}


/* ---- FCN_VO(tgGM_PN_Init_ND) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_PN_Init_ND)( VEC_OBJ_T(TgPLANE,PCU) psPN0, VEC_T(1,C) vN0, VEC_T(1,C) vK )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Unit_Vector)( vN0 ));
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Broadcast_Scalar)( vK ));

    {
        VEC_UN_T(1)                         uX0 = { VEC_UN_1_MEMBER() = vN0 };
        VEC_UN_T(1,C)                       uX1 = { VEC_UN_1_MEMBER() = vK };

        VEC_S_UN_1_MEMBER(uX0).w = VEC_S_UN_1_MEMBER(uX1).w;

        psPN0->m_vPlnEqN = VEC_UN_1_MEMBER(uX0);
        psPN0->m_vNormal = vN0;
        psPN0->m_vD = vK;
    }
}


/* ---- FCN_VO(tgGM_PN_Init_NP) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_PN_Init_NP)( VEC_OBJ_T(TgPLANE,PCU) psPN0, VEC_T(1,C) vN0, VEC_T(1,C) vS0 )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Unit_Vector)( vN0 ));
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Point)( vS0 ));

    {
        VEC_UN_T(1)                         uX0 = { VEC_UN_1_MEMBER() = vN0 };
        VEC_UN_T(1,C)                       uX1 = { VEC_UN_1_MEMBER() = FCN_V(tgMH_NEG)( FCN_V(tgMH_DOT)( vN0, vS0 ) ) };

        VEC_S_UN_1_MEMBER(uX0).w = VEC_S_UN_1_MEMBER(uX1).w;

        psPN0->m_vPlnEqN = VEC_UN_1_MEMBER(uX0);
        psPN0->m_vNormal = vN0;
        psPN0->m_vD = VEC_UN_1_MEMBER(uX1);
    }
}


/* ---- FCN_VO(tgGM_PN_Copy) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_PN_Copy)( VEC_OBJ_T(TgPLANE,PCU) psPN0, VEC_OBJ_T(TgPLANE,CPCU) psPN1 )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_PN_Is_Valid)( psPN1 ));

    psPN0->m_vPlnEqN = psPN1->m_vPlnEqN;
    psPN0->m_vNormal = psPN1->m_vNormal;
    psPN0->m_vD = psPN1->m_vD;
}


/* ---- FCN_VO(tgGM_PN_Set_PlnEqN) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_PN_Set_PlnEqN)( VEC_OBJ_T(TgPLANE,PCU) psPN0, VEC_T(1,C) vPlnEqN )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid)( vPlnEqN ));

    psPN0->m_vPlnEqN = vPlnEqN;
    psPN0->m_vNormal = FCN_V(tgMH_Init_Vector)( vPlnEqN );
    psPN0->m_vD = FCN_V(tgMH_SPW)( vPlnEqN );
}


/* ---- FCN_VO(tgGM_PN_Set_Normal) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_PN_Set_Normal)( VEC_OBJ_T(TgPLANE,PCU) psPN0, VEC_T(1,C) vN0 )
{
    VEC_UN_T(1)                         uX0, uX1;

    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Unit_Vector)( vN0 ));

    psPN0->m_vD = FCN_V(tgMH_DOT)( vN0, FCN_V(tgMH_MUL)( psPN0->m_vNormal, psPN0->m_vD ) );
    psPN0->m_vNormal = vN0;

    VEC_UN_1_MEMBER(uX0) = psPN0->m_vPlnEqN;
    VEC_UN_1_MEMBER(uX1) = psPN0->m_vD;
    VEC_S_UN_1_MEMBER(uX0).w = VEC_S_UN_1_MEMBER(uX1).w;

    psPN0->m_vPlnEqN = VEC_UN_1_MEMBER(uX0);
}


/* ---- FCN_VO(tgGM_PN_Set_Origin) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_PN_Set_Origin)( VEC_OBJ_T(TgPLANE,PCU) psPN0, VEC_T(1,C) vS )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Point)( vS ));

    {
        VEC_UN_T(1,C)                       uX0 = { VEC_UN_1_MEMBER() = FCN_V(tgMH_NEG)( FCN_V(tgMH_DOT)( psPN0->m_vNormal, vS ) ) };
        VEC_UN_T(1)                         uX1 = { VEC_UN_1_MEMBER() = psPN0->m_vPlnEqN };

        VEC_S_UN_1_MEMBER(uX1).w = VEC_S_UN_1_MEMBER(uX0).w;

        psPN0->m_vPlnEqN = VEC_UN_1_MEMBER(uX1);
        psPN0->m_vD = VEC_UN_1_MEMBER(uX0);
    }
}


/* ---- FCN_VO(tgGM_PN_Set_Constant) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_PN_Set_Constant)( VEC_OBJ_T(TgPLANE,PCU) psPN0, VEC_T(1,C) vK )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Broadcast_Scalar)( vK ));

    {
        VEC_UN_T(1)                         uX0 = { VEC_UN_1_MEMBER() = psPN0->m_vPlnEqN };
        VEC_UN_T(1,C)                       uK = { VEC_UN_1_MEMBER() = vK };

        VEC_S_UN_1_MEMBER(uX0).w = VEC_S_UN_1_MEMBER(uK).w;

        psPN0->m_vPlnEqN = VEC_UN_1_MEMBER(uX0);
        psPN0->m_vD = vK;
    }
}


/* ---- FCN_VO(tgGM_PN_Query_PlnEqN) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_PN_Query_PlnEqN)( VEC_OBJ_T(TgPLANE,CPCU) psPN0 )
{
    return (psPN0->m_vPlnEqN);
}


/* ---- FCN_VO(tgGM_PN_Query_Normal) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_PN_Query_Normal)( VEC_OBJ_T(TgPLANE,CPCU) psPN0 )
{
    return (psPN0->m_vNormal);
}


/* ---- FCN_VO(tgGM_PN_Query_Constant) ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_PN_Query_Constant)( VEC_OBJ_T(TgPLANE,CPCU) psPN0 )
{
    return (psPN0->m_vD);
}




/* ---- FCN_VO(tgGM_DistSq_PN_PT) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_DistSq_PN_PT)( VEC_OBJ_T(TgPLANE,CPCU) psPN0, VEC_T(1,C) vS0 )
{
    VEC_T(1,C)                          vDS = FCN_V(tgMH_DOT)( psPN0->m_vPlnEqN, vS0 );
    VEC_T(1,C)                          vX0 = FCN_V(tgMH_MUL)( vDS, vDS );
    VEC_T(1,C)                          vX1 = FCN_V(tgMH_SEL)( vX0, FCN_V(tgMH_SET1)( -VAR_K(KTgMAX) ), FCN_V(tgMH_CMP_LT)( vDS, FCN_V(tgMH_SET1)( TYPE_K(0) )) );

    return (vX1);
}


/* ---- FCN_VO(tgGM_Dist_PN_PT) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_Dist_PN_PT)( VEC_OBJ_T(TgPLANE,CPCU) psPN0, VEC_T(1,C) vS0 )
{
    VEC_T(1,C)                          vDS = FCN_V(tgMH_DOT)( psPN0->m_vPlnEqN, vS0 );
    VEC_T(1,C)                          vX0 = FCN_V(tgMH_SEL)( vDS, FCN_V(tgMH_SET1)( -VAR_K(KTgMAX) ), FCN_V(tgMH_CMP_LT)( vDS, FCN_V(tgMH_SET1)( TYPE_K(0) )) );

    return (vX0);
}


/* ---- FCN_VO(tgGM_Sign_Dist_PN_PT) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_Sign_Dist_PN_PT)( VEC_OBJ_T(TgPLANE,CPCU) psPN0, VEC_T(1,C) vS0 )
{
    return (FCN_V(tgMH_DOT)( psPN0->m_vPlnEqN, vS0 ));
}


/* ---- FCN_VO(tgGM_Sign_Closest_PN_PT) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_Sign_Closest_PN_PT)( VEC_T(1,PCU) pvS0, VEC_OBJ_T(TgPLANE,CPCU) psPN0, VEC_T(1,C) vS1 )
{
    VEC_T(1,C)                          vDS = FCN_V(tgMH_DOT)( psPN0->m_vPlnEqN, vS1 );

    *pvS0 = FCN_V(tgMH_NMS)( vDS, psPN0->m_vNormal, vS1 );
    return (vDS);
}


/* =============================================================================================================================================================================== */
#endif
