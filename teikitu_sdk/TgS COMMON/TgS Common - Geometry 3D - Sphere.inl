/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Geometry 3D - Sphere.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_GEOMETRY_3D_SPHERE_INL)

#if !defined (TEMPLATE_TYPE_EXPANSION__RELOAD)
    #error Must be included as part of a type expansion include chain
#endif


/* == Common ===================================================================================================================================================================== */

/* ---- FCN_VO(tgGM_SP_Reset) ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_SP_Reset)( VEC_OBJ_T(TgSPHERE,PCU) psSP0 )
{
    psSP0->m_vOrigin = FCN_V(tgMH_Init_Point)( FCN_V(tgMH_SET1)( TYPE_K(0) ) );
    psSP0->m_vRadius = FCN_V(tgMH_SET1)( TYPE_K(0) );
    psSP0->m_vRadiusSq = FCN_V(tgMH_SET1)( TYPE_K(0) );
}


/* ---- FCN_VO(tgGM_SP_Is_Valid) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_VO(tgGM_SP_Is_Valid)( VEC_OBJ_T(TgSPHERE,CPCU) psSP0 )
{
    if (!FCN_V(tgMH_Is_Valid_Point)( psSP0->m_vOrigin ))
    {
        return (false);
    };

    if (!FCN_V(tgMH_Is_Valid)( psSP0->m_vRadius ) || !FCN_V(tgMH_Is_Valid)( psSP0->m_vRadiusSq ))
    {
        return (false);
    };

    if (FCN_V(tgMH_Is_PRX_CMP_EQ)( psSP0->m_vRadius, FCN_V(tgMH_SET1)( TYPE_K(0) ) ))
    {
        return (false);
    };

    if (!FCN_V(tgMH_Is_PRX_CMP_EQ)( psSP0->m_vRadiusSq, FCN_V(tgMH_MUL)( psSP0->m_vRadius, psSP0->m_vRadius ) ))
    {
        return (false);
    };

    return (true);
}


/* ---- FCN_VO(tgGM_SP_Support_Point) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_SP_Support_Point)( VEC_OBJ_T(TgSPHERE,CPCU) psSP0, VEC_T(1,C) vDN )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_SP_Is_Valid)( psSP0 ) && FCN_V(tgMH_Is_Valid_Unit_Vector)( vDN ));

    return (FCN_V(tgMH_MAD)( psSP0->m_vRadius, vDN, psSP0->m_vOrigin) );
}


/* ---- FCN_VO(tgGM_SP_Volume) --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_SP_Volume)( VEC_OBJ_T(TgSPHERE,CPCU) psSP0 )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_SP_Is_Valid)( psSP0 ));

    {
        VEC_T(1,C)                          vX0 = FCN_V(tgMH_SET1)( TYPE_K(2)*VAR_K(KTgTWO_PI) / TYPE_K(3) );
        VEC_T(1,C)                          vX1 = FCN_V(tgMH_MUL)( psSP0->m_vRadius, vX0 );
        VEC_T(1,C)                          vX2 = FCN_V(tgMH_MUL)( psSP0->m_vRadius, psSP0->m_vRadius );
        VEC_T(1,C)                          vRet = FCN_V(tgMH_MUL)( vX1, vX2 );

        return (vRet);
    }
}


/* ---- FCN_VO(tgGM_SP_Area) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_SP_Area)( VEC_OBJ_T(TgSPHERE,CPCU) psSP0 )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_SP_Is_Valid)( psSP0 ));

    {
        VEC_T(1,C)                          vX0 = FCN_V(tgMH_SET1)( TYPE_K(2)*VAR_K(KTgTWO_PI) );
        VEC_T(1,C)                          vRet = FCN_V(tgMH_MUL)( vX0, psSP0->m_vRadiusSq );

        return (vRet);
    }
}


/* ---- FCN_VO(tgGM_SP_BA) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_SP_BA)( VEC_OBJ_T(TgBOXAA,PCU) psBA0, VEC_OBJ_T(TgSPHERE,CPCU) psSP0 )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_SP_Is_Valid)( psSP0 ));

    FCN_VO(tgGM_BA_Init_SP)( psBA0, psSP0->m_vOrigin, psSP0->m_vRadius );
}


/* ---- FCN_VO(tgGM_SP_Sweep_BA) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_SP_Sweep_BA)( VEC_OBJ_T(TgBOXAA,PCU) psBA0, VEC_OBJ_T(TgSPHERE,CPCU) psSP1, VEC_T(1,C) vDT )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Vector)( vDT ));

    FCN_VO(tgGM_SP_BA)( psBA0, psSP1 );
    FCN_VO(tgGM_BA_Sweep)( psBA0, vDT );
}


/* ---- FCN_VO(tgGM_SP_Project) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_SP_Project)( VEC_T(1,PCU) pvMin, VEC_T(1,PCU) pvMax, VEC_OBJ_T(TgSPHERE,CPCU) psSP0, VEC_T(1,C) vDN )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_SP_Is_Valid)( psSP0 ) && FCN_V(tgMH_Is_Valid_Unit_Vector)( vDN ));

    {
        VEC_T(1,C)                          vC0_DN = FCN_V(tgMH_DOT)(psSP0->m_vOrigin,vDN);

        *pvMin = FCN_V(tgMH_SUB)(vC0_DN,FCN_V(tgMH_Init_Vector)(psSP0->m_vRadius));
        *pvMax = FCN_V(tgMH_ADD)(vC0_DN,FCN_V(tgMH_Init_Vector)(psSP0->m_vRadius));
    }
}


/* ---- FCN_VO(tgGM_SP_Is_Contained) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_VO(tgGM_SP_Is_Contained)( VEC_OBJ_T(TgSPHERE,CPCU) psSP0, VEC_T(1,C) vS0 )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_SP_Is_Valid)( psSP0 ));
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Point)( vS0 ));

    {
        VEC_T(1,C)                          vX0 = FCN_V(tgMH_SUB)( vS0, psSP0->m_vOrigin );
        VEC_T(1,C)                          vX1 = FCN_V(tgMH_LSQ)( vX0 );
        VEC_T(1,C)                          vX2 = FCN_V(tgMH_CMP_LE)( vX1, FCN_V(tgMH_Init_Vector)( psSP0->m_vRadiusSq ) );

        return (FCN_V(tgMH_CMP_ALL_TO_BOOL)( vX2 ));
    }
}


/* ---- FCN_VO(tgGM_SP_TX) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_SP_TX)( VEC_OBJ_T(TgSPHERE,PCU) psSP0, VEC_T(3,CPCU) pmM0 )
{
    TgGEOM_ASSERT_PARAM(!FCN_V(tgMH_NAN,3)( pmM0 ));

    psSP0->m_vOrigin = FCN_V(tgMH_TX_P,3)( psSP0->m_vOrigin, pmM0 );
}


/* ---- FCN_VO(tgGM_SP_Copy_TX) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_SP_Copy_TX)( VEC_OBJ_T(TgSPHERE,PCU) psSP0, VEC_OBJ_T(TgSPHERE,CPCU) psSP1, VEC_T(3,CPCU) pmM0 )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_SP_Is_Valid)( psSP1 ) && !FCN_V(tgMH_NAN,3)( pmM0 ));

    psSP0->m_vOrigin = FCN_V(tgMH_TX_P,3)( psSP1->m_vOrigin, pmM0 );
    psSP0->m_vRadius = psSP1->m_vRadius;
    psSP0->m_vRadiusSq = psSP1->m_vRadiusSq;
}


/* ---- FCN_VO(tgGM_SP_Init) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_SP_Init)( VEC_OBJ_T(TgSPHERE,PCU) psSP0, VEC_T(1,C) vS0, VEC_T(1,C) vRad )
{
    FCN_VO(tgGM_SP_Set_Origin)( psSP0, vS0 );
    FCN_VO(tgGM_SP_Set_Radius)( psSP0, vRad );
}


/* ---- FCN_VO(tgGM_SP_Copy) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_SP_Copy)( VEC_OBJ_T(TgSPHERE,PCU) psSP0, VEC_OBJ_T(TgSPHERE,CPCU) psSP1 )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_SP_Is_Valid)( psSP1 ));

    psSP0->m_vOrigin = psSP1->m_vOrigin;
    psSP0->m_vRadius = psSP1->m_vRadius;
    psSP0->m_vRadiusSq = psSP1->m_vRadiusSq;
}


/* ---- FCN_VO(tgGM_SP_Set_Origin) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_SP_Set_Origin)( VEC_OBJ_T(TgSPHERE,PCU) psSP0, VEC_T(1,C) vS0 )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Point)( vS0 ));

    psSP0->m_vOrigin = vS0;
}


/* ---- FCN_VO(tgGM_SP_Set_Radius) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_SP_Set_Radius)( VEC_OBJ_T(TgSPHERE,PCU) psSP0, VEC_T(1,C) vRad )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Broadcast_Positive_Scalar)( vRad ));

    psSP0->m_vRadius = vRad;
    psSP0->m_vRadiusSq = FCN_V(tgMH_MUL)( vRad, vRad );
}


/* ---- FCN_VO(tgGM_SP_Query_Origin) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_SP_Query_Origin)( VEC_OBJ_T(TgSPHERE,CPCU) psSP1 )
{
    return (psSP1->m_vOrigin);
}

/* ---- FCN_VO(tgGM_SP_Query_Radius) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_SP_Query_Radius)( VEC_OBJ_T(TgSPHERE,CPCU) psSP0 )
{
    return (psSP0->m_vRadius);
}


/* ---- FCN_VO(tgGM_SP_Query_Radius_Sq) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_SP_Query_Radius_Sq)( VEC_OBJ_T(TgSPHERE,CPCU) psSP0 )
{
    return (psSP0->m_vRadiusSq);
}


/* =============================================================================================================================================================================== */
#endif
