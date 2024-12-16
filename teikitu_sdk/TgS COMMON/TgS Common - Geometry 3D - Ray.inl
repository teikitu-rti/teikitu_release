/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Geometry 3D - Ray.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_GEOMETRY_3D_RAY_INL)

#if !defined (TEMPLATE_TYPE_EXPANSION__RELOAD)
    #error Must be included as part of a type expansion include chain
#endif


/* == Common ===================================================================================================================================================================== */

/* ---- FCN_VO(tgGM_RY_Reset) ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_RY_Reset)( VEC_OBJ_T(TgRAY,PCU) psRY0 )
{
    psRY0->m_vOrigin = FCN_V(tgMH_Init_Point)( FCN_V(tgMH_SET1)( TYPE_K(0) ) );
    psRY0->m_vDirN = FCN_V(tgMH_Init_Vector)( FCN_V(tgMH_SET1)( TYPE_K(0) ) );
}


/* ---- FCN_VO(tgGM_RY_Is_Valid) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_VO(tgGM_RY_Is_Valid)( VEC_OBJ_T(TgRAY,CPCU) psRY1 )
{
    if (!FCN_V(tgMH_Is_Valid_Point)( psRY1->m_vOrigin ))
    {
        return (false);
    };

    if (!FCN_V(tgMH_Is_Valid_Unit_Vector)( psRY1->m_vDirN ))
    {
        return (false);
    };

    return (true);
}


/* ---- FCN_VO(tgGM_RY_BA) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_RY_BA)( VEC_OBJ_T(TgBOXAA,PCU) psBA0, TgATTRIBUTE_UNUSED VEC_OBJ_T(TgRAY,CPCU) psRY0 )
{
    FCN_VO(tgGM_BA_Set_Invalid)( psBA0 );
}


/* ---- FCN_VO(tgGM_RY_Sweep_BA) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_RY_Sweep_BA)( VEC_OBJ_T(TgBOXAA,PCU) psBA0, TgATTRIBUTE_UNUSED VEC_OBJ_T(TgRAY,CPCU) psRY0, TgATTRIBUTE_UNUSED VEC_T(1,C) vDT )
{
    FCN_VO(tgGM_BA_Set_Invalid)( psBA0 );
}


/* ---- FCN_VO(tgGM_RY_Project) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_RY_Project)( VEC_T(1,PCU) pvMin, VEC_T(1,PCU) pvMax, VEC_OBJ_T(TgRAY,CPCU) psRY1, VEC_T(1,C) vDN )
{
    TgGEOM_ASSERT_PARAM(nullptr != pvMin && nullptr != pvMax && FCN_VO(tgGM_RY_Is_Valid)( psRY1 ) && FCN_V(tgMH_Is_Valid_Unit_Vector)( vDN ));

    {
        VEC_T(1,C)                          vS0_DN = FCN_V(tgMH_DOT)( psRY1->m_vOrigin, vDN );
        VEC_T(1,C)                          vD0_DN = FCN_V(tgMH_DOT)( psRY1->m_vDirN, vDN );
        VEC_T(1,C)                          vV0 = FCN_V(tgMH_CP_SGN)( FCN_V(tgMH_SET1)( VAR_K(KTgMAX) ), vD0_DN );

        *pvMin = FCN_V(tgMH_MIN)( vS0_DN, vV0 );
        *pvMax = FCN_V(tgMH_MAX)( vS0_DN, vV0 );
    }
}


/* ---- FCN_VO(tgGM_RY_Is_Contained) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_VO(tgGM_RY_Is_Contained)( VEC_OBJ_T(TgRAY,CPCU) psRY1, VEC_T(1,C) vS0 )
{
    VEC_T(1,C)                          vDS = FCN_V(tgMH_SUB)( vS0, psRY1->m_vOrigin );
    VEC_T(1,C)                          vCLP_DS = FCN_V(tgMH_MAX)( FCN_V(tgMH_DOT)( vDS, psRY1->m_vDirN ), FCN_V(tgMH_SET1)( TYPE_K(0) ) );
    VEC_T(1,C)                          vX0 = FCN_V(tgMH_MUL)( vCLP_DS, psRY1->m_vDirN );
    VEC_T(1,C)                          vX1 = FCN_V(tgMH_SUB)( vDS, vX0 );

    return (FCN_V(tgMH_Is_PRX_CMP_EQ)( vX1, FCN_V(tgMH_SET1)( TYPE_K(0) ) ));
}


/* ---- FCN_VO(tgGM_RY_TX) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_RY_TX)( VEC_OBJ_T(TgRAY,PCU) psRY0, VEC_T(3,CPCU) pmM0 )
{
    TgGEOM_ASSERT_PARAM(!FCN_V(tgMH_NAN,3)( pmM0 ));

    psRY0->m_vOrigin = FCN_V(tgMH_TX_P,3)( psRY0->m_vOrigin, pmM0 );
    psRY0->m_vDirN = FCN_V(tgMH_TX_V,3)( psRY0->m_vDirN, pmM0 );
}


/* ---- FCN_VO(tgGM_RY_Copy_TX) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_RY_Copy_TX)( VEC_OBJ_T(TgRAY,PCU) psRY0, VEC_OBJ_T(TgRAY,CPCU) psRY1, VEC_T(3,CPCU) pmM0 )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_RY_Is_Valid)( psRY1 ) && !FCN_V(tgMH_NAN,3)( pmM0 ));

    psRY0->m_vOrigin = FCN_V(tgMH_TX_P,3)( psRY1->m_vOrigin, pmM0 );
    psRY0->m_vDirN = FCN_V(tgMH_TX_V,3)( psRY1->m_vDirN, pmM0 );
}


/* ---- FCN_VO(tgGM_RY_Init) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_RY_Init)( VEC_OBJ_T(TgRAY,PCU) psRY0, VEC_T(1,C) vS0, VEC_T(1,C) vDN )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Point)( vS0 ) && FCN_V(tgMH_Is_Valid_Unit_Vector)( vDN ));

    psRY0->m_vOrigin = vS0;
    psRY0->m_vDirN = vDN;
}


/* ---- FCN_VO(tgGM_RY_Copy) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_RY_Copy)( VEC_OBJ_T(TgRAY,PCU) psRY0, VEC_OBJ_T(TgRAY,CPCU) psRY1 )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_RY_Is_Valid)( psRY1 ));

    psRY0->m_vOrigin = psRY1->m_vOrigin;
    psRY0->m_vDirN = psRY1->m_vDirN;
}


/* ---- FCN_VO(tgGM_RY_Set_Origin) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_RY_Set_Origin)( VEC_OBJ_T(TgRAY,PCU) psRY0, VEC_T(1,C) vS0 )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Point)( vS0 ));
    psRY0->m_vOrigin = vS0;
}


/* ---- FCN_VO(tgGM_RY_Set_DirN) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_RY_Set_DirN)( VEC_OBJ_T(TgRAY,PCU) psRY0, VEC_T(1,C) vDN )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Unit_Vector)( vDN ));
    psRY0->m_vDirN = vDN;
}


/* ---- FCN_VO(tgGM_RY_Query_Origin) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_RY_Query_Origin)( VEC_OBJ_T(TgRAY,CPCU) psRY1 )
{
    return (psRY1->m_vOrigin);
}


/* ---- FCN_VO(tgGM_RY_Query_DirN) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_RY_Query_DirN)( VEC_OBJ_T(TgRAY,CPCU) psRY1 )
{
    return (psRY1->m_vDirN);
}


/* =============================================================================================================================================================================== */
#endif
