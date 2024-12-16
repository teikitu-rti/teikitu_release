/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Geometry 3D - Segment.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_GEOMETRY_3D_SEGMENT_INL)

#if !defined (TEMPLATE_TYPE_EXPANSION__RELOAD)
    #error Must be included as part of a type expansion include chain
#endif


/* == Common ===================================================================================================================================================================== */

/* ---- FCN_VO(tgGM_SG_Reset) ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_SG_Reset)( VEC_OBJ_T(TgSEGMENT,PCU) psSG0 )
{
    psSG0->m_vOrigin = FCN_V(tgMH_Init_Point)( FCN_V(tgMH_SET1)( TYPE_K(0) ) );
    psSG0->m_vDirN = FCN_V(tgMH_Init_Vector)( FCN_V(tgMH_SET1)( TYPE_K(0) ) );
}


/* ---- FCN_VO(tgGM_SG_Is_Valid) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_VO(tgGM_SG_Is_Valid)( VEC_OBJ_T(TgSEGMENT,CPCU) psSG0 )
{
    if (!FCN_V(tgMH_Is_Valid_Point)( psSG0->m_vOrigin ))
    {
        return (false);
    };

    if (!FCN_V(tgMH_Is_Valid_Vector)( psSG0->m_vDirN ) || FCN_V(tgMH_Is_PRX_CMP_EQ)( psSG0->m_vDirN, FCN_V(tgMH_SET1)( TYPE_K(0) ) ))
    {
        return (false);
    };

    return (true);
}


/* ---- FCN_VO(tgGM_SG_BA) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_SG_BA)( VEC_OBJ_T(TgBOXAA,PCU) psBA0, VEC_OBJ_T(TgSEGMENT,CPCU) psSG1 )
{
    FCN_VO(tgGM_BA_Init_PT)( psBA0, psSG1->m_vOrigin );
    FCN_VO(tgGM_BA_Sweep)( psBA0, psSG1->m_vDirN );
}


/* ---- FCN_VO(tgGM_SG_Sweep_BA) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_SG_Sweep_BA)( VEC_OBJ_T(TgBOXAA,PCU) psBA0, VEC_OBJ_T(TgSEGMENT,CPCU) psSG1, VEC_T(1,C) vDT )
{
    FCN_VO(tgGM_SG_BA)( psBA0, psSG1 );
    FCN_VO(tgGM_BA_Sweep)( psBA0, vDT );
}


/* ---- FCN_VO(tgGM_SG_Project) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_SG_Project)( VEC_T(1,PCU) pvMin, VEC_T(1,PCU) pvMax, VEC_OBJ_T(TgSEGMENT,CPCU) psSG0, VEC_T(1,C) vDN )
{
    TgGEOM_ASSERT_PARAM(nullptr != pvMin && nullptr != pvMax && FCN_VO(tgGM_SG_Is_Valid)( psSG0 ) && FCN_V(tgMH_Is_Valid_Unit_Vector)( vDN ));

    {
        VEC_T(1,C)                          vS0_DN = FCN_V(tgMH_DOT)( psSG0->m_vOrigin, vDN );
        VEC_T(1,C)                          vS1_DN = FCN_V(tgMH_DOT)( FCN_V(tgMH_ADD)( psSG0->m_vOrigin, psSG0->m_vDirN ), vDN );

        *pvMin = FCN_V(tgMH_MIN)( vS0_DN, vS1_DN );
        *pvMax = FCN_V(tgMH_MAX)( vS0_DN, vS1_DN );
    }
}


/* ---- FCN_VO(tgGM_SG_Is_Contained) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_VO(tgGM_SG_Is_Contained)( VEC_OBJ_T(TgSEGMENT,CPCU) psSG0, VEC_T(1,C) vS0 )
{
    VEC_T(1,C)                          vDS = FCN_V(tgMH_SUB)( vS0, psSG0->m_vOrigin );
    VEC_T(1,C)                          vX0 = FCN_V(tgMH_DOT)( vDS, psSG0->m_vDirN );
    VEC_T(1,C)                          vX1 = FCN_V(tgMH_LSQ)( psSG0->m_vDirN );
    VEC_T(1,C)                          vX2 = FCN_V(tgMH_CLP)( vX0, FCN_V(tgMH_SET1)( TYPE_K(0) ), vX1 );
    VEC_T(1,C)                          vX3 = FCN_V(tgMH_DIV)( vX2, vX1 );
    VEC_T(1,C)                          vX4 = FCN_V(tgMH_MUL)( vX3, psSG0->m_vDirN );
    VEC_T(1,C)                          vX5 = FCN_V(tgMH_SUB)( vDS, vX4 );

    return (FCN_V(tgMH_Is_PRX_CMP_EQ)( vX5, FCN_V(tgMH_SET1)( TYPE_K(0) ) ));
}


/* ---- FCN_VO(tgGM_SG_TX) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_SG_TX)( VEC_OBJ_T(TgSEGMENT,PCU) psSG0, VEC_T(3,CPCU) pmM0 )
{
    TgGEOM_ASSERT_PARAM(!FCN_V(tgMH_NAN,3)( pmM0 ));

    psSG0->m_vOrigin = FCN_V(tgMH_TX_P,3)( psSG0->m_vOrigin, pmM0 );
    psSG0->m_vDirN = FCN_V(tgMH_TX_V,3)( psSG0->m_vDirN, pmM0 );
}


/* ---- FCN_VO(tgGM_SG_Copy_TX) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_SG_Copy_TX)( VEC_OBJ_T(TgSEGMENT,PCU) psSG0, VEC_OBJ_T(TgSEGMENT,CPCU) psSG1, VEC_T(3,CPCU) pmM0 )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_SG_Is_Valid)( psSG1 ) && !FCN_V(tgMH_NAN,3)( pmM0 ));

    psSG0->m_vOrigin = FCN_V(tgMH_TX_P,3)( psSG1->m_vOrigin, pmM0 );
    psSG0->m_vDirN = FCN_V(tgMH_TX_V,3)( psSG1->m_vDirN, pmM0 );
}


/* ---- FCN_VO(tgGM_SG_Init) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_SG_Init)( VEC_OBJ_T(TgSEGMENT,PCU) psSG0, VEC_T(1,C) vS0, VEC_T(1,C) vDN )
{
    psSG0->m_vOrigin = vS0;
    psSG0->m_vDirN = vDN;

    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_SG_Is_Valid)( psSG0 ));
}


/* ---- FCN_VO(tgGM_SG_Copy) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_SG_Copy)( VEC_OBJ_T(TgSEGMENT,PCU) psSG0, VEC_OBJ_T(TgSEGMENT,CPCU) psSG1 )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_SG_Is_Valid)( psSG1 ));

    psSG0->m_vOrigin = psSG1->m_vOrigin;
    psSG0->m_vDirN = psSG1->m_vDirN;
}


/* ---- FCN_VO(tgGM_SG_Set_Origin) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_SG_Set_Origin)( VEC_OBJ_T(TgSEGMENT,PCU) psSG0, VEC_T(1,C) vS0 )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Point)( vS0 ));

    psSG0->m_vOrigin = vS0;
}


/* ---- FCN_VO(tgGM_SG_Set_DirN) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_SG_Set_DirN)( VEC_OBJ_T(TgSEGMENT,PCU) psSG0, VEC_T(1,C) vDN )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Vector)( vDN ));

    psSG0->m_vDirN = vDN;
}


/* ---- FCN_VO(tgGM_SG_Query_Origin) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_SG_Query_Origin)( VEC_OBJ_T(TgSEGMENT,CPCU) psSG1 )
{
    return (psSG1->m_vOrigin);
}


/* ---- FCN_VO(tgGM_SG_Query_DirN) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_SG_Query_DirN)( VEC_OBJ_T(TgSEGMENT,CPCU) psSG1 )
{
    return (psSG1->m_vDirN);
}


/* =============================================================================================================================================================================== */
#endif
