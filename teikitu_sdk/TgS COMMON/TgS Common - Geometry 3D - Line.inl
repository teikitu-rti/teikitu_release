/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Geometry 3D - Line.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_GEOMETRY_3D_LINE_INL)

#if !defined (TEMPLATE_TYPE_EXPANSION__RELOAD)
    #error Must be included as part of a type expansion include chain
#endif


/* == Common ===================================================================================================================================================================== */

/* ---- FCN_VO(tgGM_LN_Reset) ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_LN_Reset)( VEC_OBJ_T(TgLINE,PCU) psLN0 )
{
    psLN0->m_vOrigin = FCN_V(tgMH_Init_Point)( FCN_V(tgMH_SET1)( TYPE_K(0) ) );
    psLN0->m_vDirN = FCN_V(tgMH_Init_Vector)( FCN_V(tgMH_SET1)( TYPE_K(0) ) );
}


/* ---- FCN_VO(tgGM_LN_Is_Valid) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_VO(tgGM_LN_Is_Valid)( VEC_OBJ_T(TgLINE,CPCU) psLN0 )
{
    if (!FCN_V(tgMH_Is_Valid_Point)( psLN0->m_vOrigin ))
    {
        return (false);
    };

    if (!FCN_V(tgMH_Is_Valid_Vector)( psLN0->m_vDirN ) || FCN_V(tgMH_Is_PRX_CMP_EQ)( psLN0->m_vDirN, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) )
    {
        return (false);
    };

    return (true);
}


/* ---- FCN_VO(tgGM_LN_BA) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_LN_BA)( VEC_OBJ_T(TgBOXAA,PCU) psBA0, TgATTRIBUTE_UNUSED VEC_OBJ_T(TgLINE,CPCU) psLN )
{
    FCN_VO(tgGM_BA_Set_Invalid)( psBA0 );
}


/* ---- FCN_VO(tgGM_LN_Sweep_BA) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_LN_Sweep_BA)( VEC_OBJ_T(TgBOXAA,PCU) psBA0, TgATTRIBUTE_UNUSED VEC_OBJ_T(TgLINE,CPCU) psLN, TgATTRIBUTE_UNUSED VEC_T(1,C) vDT )
{
    FCN_VO(tgGM_BA_Set_Invalid)( psBA0 );
}


/* ---- FCN_VO(tgGM_LN_Project) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_LN_Project)( VEC_T(1,PCU) pvMin, VEC_T(1,PCU) pvMax, TgATTRIBUTE_UNUSED_GEOM_PARAM_CHECK VEC_OBJ_T(TgLINE,CPCU) psLN1,
                                         TgATTRIBUTE_UNUSED_GEOM_PARAM_CHECK VEC_T(1,C) vDN )
{
    TgGEOM_ASSERT_PARAM(nullptr != pvMin && nullptr != pvMax && FCN_VO(tgGM_LN_Is_Valid)( psLN1 ) && FCN_V(tgMH_Is_Valid_Vector)( vDN ));

    *pvMin = FCN_V(tgMH_SET1)( -VAR_K(KTgMAX) );
    *pvMax = FCN_V(tgMH_SET1)( VAR_K(KTgMAX) );
}


/* ---- FCN_VO(tgGM_LN_Is_Contained) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_VO(tgGM_LN_Is_Contained)( VEC_OBJ_T(TgLINE,CPCU) psLN1, VEC_T(1,C) vS0 )
{
    VEC_T(1,C)                          vDS = FCN_V(tgMH_SUB)( vS0, psLN1->m_vOrigin );
    VEC_T(1,C)                          vDS_DN = FCN_V(tgMH_DOT)( vDS, psLN1->m_vDirN );
    VEC_T(1,C)                          vX0 = FCN_V(tgMH_MUL)( vDS_DN, psLN1->m_vDirN );
    VEC_T(1,C)                          vX1 = FCN_V(tgMH_SUB)( vDS, vX0 );

    return (FCN_V(tgMH_Is_PRX_CMP_EQ)( vX1, FCN_V(tgMH_SET1)( TYPE_K(0) ) ));
}


/* ---- FCN_VO(tgGM_LN_TX) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_LN_TX)( VEC_OBJ_T(TgLINE,PCU) psLN0, VEC_T(3,CPCU) pmM0 )
{
    TgGEOM_ASSERT_PARAM(!FCN_V(tgMH_NAN,3)( pmM0 ));

    psLN0->m_vOrigin = FCN_V(tgMH_TX_P,3)( psLN0->m_vOrigin, pmM0 );
    psLN0->m_vDirN = FCN_V(tgMH_TX_V,3)( psLN0->m_vDirN, pmM0 );
}


/* ---- FCN_VO(tgGM_LN_Copy_TX) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_LN_Copy_TX)( VEC_OBJ_T(TgLINE,PCU) psLN0, VEC_OBJ_T(TgLINE,CPCU) psLN1, VEC_T(3,CPCU) pmM0 )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_LN_Is_Valid)( psLN1 ) && !FCN_V(tgMH_NAN,3)( pmM0 ));

    psLN0->m_vOrigin = FCN_V(tgMH_TX_P,3)( psLN1->m_vOrigin, pmM0 );
    psLN0->m_vDirN = FCN_V(tgMH_TX_V,3)( psLN1->m_vDirN, pmM0 );
}


/* ---- FCN_VO(tgGM_LN_Init) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_LN_Init)( VEC_OBJ_T(TgLINE,PCU) psLN0, VEC_T(1,C) vS0, VEC_T(1,C) vDN )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Point)( vS0 ) && FCN_V(tgMH_Is_Valid_Vector)( vDN ));

    psLN0->m_vOrigin = vS0;
    psLN0->m_vDirN = vDN;
}


/* ---- FCN_VO(tgGM_LN_Copy) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_LN_Copy)( VEC_OBJ_T(TgLINE,PCU) psLN0, VEC_OBJ_T(TgLINE,CPCU) psLN1 )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_LN_Is_Valid)( psLN1 ));

    psLN0->m_vOrigin = psLN1->m_vOrigin;
    psLN0->m_vDirN = psLN1->m_vDirN;
}


/* ---- FCN_VO(tgGM_LN_Set_Origin) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_LN_Set_Origin)( VEC_OBJ_T(TgLINE,PCU) psLN0, VEC_T(1,C) vS0 )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Point)( vS0 ));
    psLN0->m_vOrigin = vS0;
}


/* ---- FCN_VO(tgGM_LN_Set_DirN) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_LN_Set_DirN)( VEC_OBJ_T(TgLINE,PCU) psLN0, VEC_T(1,C) vDN )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Vector)( vDN ));
    psLN0->m_vDirN = vDN;
}


/* ---- FCN_VO(tgGM_LN_Query_Origin) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_LN_Query_Origin)( VEC_OBJ_T(TgLINE,CPCU) psLN1 )
{
    return (psLN1->m_vOrigin);
}


/* ---- FCN_VO(tgGM_LN_Query_DirN) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_LN_Query_DirN)( VEC_OBJ_T(TgLINE,CPCU) psLN1 )
{
    return (psLN1->m_vDirN);
}


/* =============================================================================================================================================================================== */
#endif
