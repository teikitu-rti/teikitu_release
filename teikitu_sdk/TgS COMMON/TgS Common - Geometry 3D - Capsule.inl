/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Geometry 3D - Capsule.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_GEOMETRY_3D_CAPSULE_INL)

#if !defined (TEMPLATE_TYPE_EXPANSION__RELOAD)
    #error Must be included as part of a type expansion include chain
#endif


/* == Common ===================================================================================================================================================================== */

/* ---- FCN_VO(tgGM_CP_Support_Point) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_CP_Support_Point)( VEC_OBJ_T(TgTUBE,CPCU) psCP0, VEC_T(1,C) vDN )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_TB_Is_Valid)( psCP0 )  && FCN_V(tgMH_Is_Valid_Unit_Vector)( vDN ));

    {
        VEC_T(1,C)                          vV0 = FCN_V(tgMH_SGN)( FCN_V(tgMH_DOT)( vDN, psCP0->m_vHAX ) );
        VEC_T(1,C)                          vV1 = FCN_V(tgMH_MUL)( vV0, psCP0->m_vHAX );
        VEC_T(1,C)                          vV2 = FCN_VO(tgGM_TB_Query_Origin)( psCP0 );
        VEC_T(1,C)                          vV3 = FCN_V(tgMH_ADD)( vV2, vV1 );
        VEC_T(1,C)                          vV4 = FCN_V(tgMH_MUL)( psCP0->m_vRadius, vDN );
        VEC_T(1,C)                          vV5 = FCN_V(tgMH_ADD)( vV4, vV3 );

        return (vV5);
    }
}


/* ---- FCN_VO(tgGM_CP_Volume) --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_CP_Volume)( VEC_OBJ_T(TgTUBE,CPCU) psCP0 )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_TB_Is_Valid)( psCP0 ));

    {
        VEC_T(1,C)                          vX0 = FCN_V(tgMH_MUL)( FCN_V(tgMH_SET1)( VAR_K(KTgTWO_PI) ), psCP0->m_vRadiusSq );
        VEC_T(1,C)                          vX1 = FCN_V(tgMH_SET1)( TYPE_K(2) / TYPE_K(3) );
        VEC_T(1,C)                          vX2 = FCN_V(tgMH_MAD)( vX1, psCP0->m_vRadius, psCP0->m_vExtent );
        VEC_T(1,C)                          vRet = FCN_V(tgMH_MUL)( vX0, vX2 );

        return (vRet);
    }
}


/* ---- FCN_VO(tgGM_CP_Area) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_CP_Area)( VEC_OBJ_T(TgTUBE,CPCU) psCP0 )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_TB_Is_Valid)( psCP0 ));

    {
        VEC_T(1,C)                          vX0 = FCN_V(tgMH_ADD)( psCP0->m_vExtent, psCP0->m_vRadius );
        VEC_T(1,C)                          vX1 = FCN_V(tgMH_MUL)( FCN_V(tgMH_SET1)( VAR_K(KTgTWO_PI) ), psCP0->m_vRadius );
        VEC_T(1,C)                          vRet = FCN_V(tgMH_MAD)( FCN_V(tgMH_SET1)( TYPE_K(2) ), vX0, vX1 );

        return (vRet);
    }
}


/* ---- FCN_VO(tgGM_CP_BA) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_CP_BA)( VEC_OBJ_T(TgBOXAA,PCU) psBA0, VEC_OBJ_T(TgTUBE,CPCU) psCP0 )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_TB_Is_Valid)( psCP0 ));

    {
        VEC_T(1,C)                          vC0 = FCN_VO(tgGM_TB_Query_Origin)( psCP0 );
        VEC_T(1,C)                          vV0 = FCN_V(tgMH_SUB)( vC0, psCP0->m_vHAX );
        VEC_T(1,C)                          vV1 = FCN_V(tgMH_ADD)( vC0, psCP0->m_vHAX );

        FCN_VO(tgGM_BA_Init_PT)( psBA0, vV0 );
        FCN_VO(tgGM_BA_Union_PT)( psBA0, vV1 );
        FCN_VO(tgGM_BA_Expand)( psBA0, psCP0->m_vRadius );
    }
}


/* ---- FCN_VO(tgGM_CP_Sweep_BA) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_CP_Sweep_BA)( VEC_OBJ_T(TgBOXAA,PCU) psBA0, VEC_OBJ_T(TgTUBE,CPCU) psCP0, VEC_T(1,C) vDT )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_TB_Is_Valid)( psCP0 ) && FCN_V(tgMH_Is_Valid_Vector)( vDT ));

    FCN_VO(tgGM_CP_BA)( psBA0, psCP0 );
    FCN_VO(tgGM_BA_Sweep)( psBA0, vDT );
}


/* ---- FCN_VO(tgGM_CP_Project) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_CP_Project)( VEC_T(1,PCU) pvMin, VEC_T(1,PCU) pvMax, VEC_OBJ_T(TgTUBE,CPCU) psCP0, VEC_T(1,C) vDN )
{
    TgGEOM_ASSERT_PARAM(nullptr != pvMin && nullptr != pvMax && FCN_VO(tgGM_TB_Is_Valid)( psCP0 ) && FCN_V(tgMH_Is_Valid_Unit_Vector)( vDN ));

    {
        VEC_T(1,C)                          vC0 = FCN_VO(tgGM_TB_Query_Origin)( psCP0 );
        VEC_T(1,C)                          vV0 = FCN_V(tgMH_DOT)( vDN, vC0 );
        VEC_T(1,C)                          vV1 = FCN_V(tgMH_ABS)( FCN_V(tgMH_DOT)( vDN, psCP0->m_vHAX ) );
        VEC_T(1,C)                          vV2 = FCN_V(tgMH_ADD)( vV1, psCP0->m_vRadius );

        *pvMin = FCN_V(tgMH_SUB)( vV0, vV2 );
        *pvMax = FCN_V(tgMH_ADD)( vV0, vV2 );
    }
}


/* ---- FCN_VO(tgGM_CP_Is_Contained) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_VO(tgGM_CP_Is_Contained)( VEC_OBJ_T(TgTUBE,CPCU) psCP0, VEC_T(1,C) vS0 )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_TB_Is_Valid)( psCP0 ) && FCN_V(tgMH_Is_Valid_Point)( vS0 ));

    {
        VEC_T(1,C)                          vC0 = FCN_VO(tgGM_TB_Query_Origin)( psCP0 );
        VEC_T(1,C)                          vDS = FCN_V(tgMH_SUB)( vS0, vC0 );
        VEC_T(1,C)                          vUAX = FCN_V(tgMH_DIV)( psCP0->m_vHAX, psCP0->m_vExtent );

        VEC_UN_T(1,C)                       uDS_UAX = { VEC_UN_1_MEMBER() = FCN_V(tgMH_DOT)( vDS, vUAX ) };

        VEC_T(1,C)                          vV0 = FCN_V(tgMH_MUL)( FCN_V(tgMH_CLP)( VEC_UN_1_MEMBER(uDS_UAX), FCN_V(tgMH_SET1)( -TYPE_K(1) ), FCN_V(tgMH_SET1)( TYPE_K(1) ) ), vUAX );
        VEC_T(1,C)                          vV1 = FCN_V(tgMH_SUB)( vS0, vV0 );

        VEC_UN_T(1,C)                       uU0 = { VEC_UN_1_MEMBER() = FCN_V(tgMH_LSQ)( vV1 ) };

        TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Unit_Vector)(vUAX));
        return (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( VEC_UN_1_MEMBER(uU0), psCP0->m_vRadiusSq ) ));
    }
}


/* =============================================================================================================================================================================== */
#endif
