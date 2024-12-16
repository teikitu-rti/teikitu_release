/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Geometry 3D - Box.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_GEOMETRY_3D_BOX_INL)

#if !defined (TEMPLATE_TYPE_EXPANSION__RELOAD)
    #error Must be included as part of a type expansion include chain
#endif


/* == Common ===================================================================================================================================================================== */

/* ---- FCN_VO(tgGM_BX_Calc_Point) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_BX_Calc_Point)( VEC_OBJ_T(TgBOX,CPCU) psBX0, VEC_T(1,C) vRET_0, VEC_T(1,C) vRET_1, VEC_T(1,C) vRET_2 )
{
    VEC_T(1)                            vA0, vA1, vA2, vC0;

    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_BND)( vRET_0, FCN_V(tgMH_SET1)( TYPE_K(1) ) ));
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_BND)( vRET_1, FCN_V(tgMH_SET1)( TYPE_K(1) ) ));
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_BND)( vRET_2, FCN_V(tgMH_SET1)( TYPE_K(1) ) ));
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_BX_Is_Valid)( psBX0 ));

    FCN_V(tgMH_Query_Reference_Frame,3)( &vA0, &vA1, &vA2, &vC0, &psBX0->m_mReference_Frame );

    {
        VEC_T(1,C)                          vE0 = FCN_V(tgMH_MAD)( FCN_V(tgMH_MUL)( vRET_0, FCN_V(tgMH_SPX)( psBX0->m_vExtent ) ), vA0, vC0 );
        VEC_T(1,C)                          vE1 = FCN_V(tgMH_MAD)( FCN_V(tgMH_MUL)( vRET_1, FCN_V(tgMH_SPY)( psBX0->m_vExtent ) ), vA1, vE0 );
        VEC_T(1,C)                          vRet = FCN_V(tgMH_MAD)( FCN_V(tgMH_MUL)( vRET_2, FCN_V(tgMH_SPZ)( psBX0->m_vExtent ) ), vA2, vE1 );

        return (vRet);
    }
}


/* ---- FCN_VO(tgGM_BX_Calc_Point_Index) ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_BX_Calc_Point_Index)( VEC_OBJ_T(TgBOX,CPCU) psBX0, TgRSIZE_C uiFlag )
{
    VEC_UN_T(1)                         uSelect;
    VEC_T(1)                            vA0, vA1, vA2, vC0;

    VEC_S_UN_1_MEMBER(uSelect).x = (0 != (uiFlag & 1)) ? TYPE_K(1) : -TYPE_K(1);
    VEC_S_UN_1_MEMBER(uSelect).y = (0 != (uiFlag & 2)) ? TYPE_K(1) : -TYPE_K(1);
    VEC_S_UN_1_MEMBER(uSelect).z = (0 != (uiFlag & 4)) ? TYPE_K(1) : -TYPE_K(1);
    VEC_S_UN_1_MEMBER(uSelect).w = TYPE_K(0);

    FCN_V(tgMH_Query_Reference_Frame,3)( &vA0, &vA1, &vA2, &vC0, &psBX0->m_mReference_Frame );

    {
        VEC_UN_T(1,C)                       uExtent = { VEC_UN_1_MEMBER() = FCN_V(tgMH_MUL)( VEC_UN_1_MEMBER(uSelect), psBX0->m_vExtent ) };

        VEC_T(1,C)                          vE0 = FCN_V(tgMH_MAD)( FCN_V(tgMH_SPX)( VEC_UN_1_MEMBER(uExtent) ), vA0, vC0 );
        VEC_T(1,C)                          vE1 = FCN_V(tgMH_MAD)( FCN_V(tgMH_SPY)( VEC_UN_1_MEMBER(uExtent) ), vA1, vE0 );
        VEC_T(1,C)                          vRet = FCN_V(tgMH_MAD)( FCN_V(tgMH_SPZ)( VEC_UN_1_MEMBER(uExtent) ), vA2, vE1 );

        return (vRet);
    }
}


/* ---- FCN_VO(tgGM_BX_Reset) ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_BX_Reset)( VEC_OBJ_T(TgBOX,PCU) psBX0 )
{
    FCN_V(tgMH_CLI,3)( &psBX0->m_mReference_Frame );
    psBX0->m_vExtent = FCN_V(tgMH_SET1)( TYPE_K(0) );
}


/* ---- FCN_VO(tgGM_BX_Is_Valid) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_VO(tgGM_BX_Is_Valid)( VEC_OBJ_T(TgBOX,CPCU) psBX0 )
{
    if (!FCN_V(tgMH_Is_Valid_Reference_Frame,3)( &psBX0->m_mReference_Frame ))
    {
        return (false);
    };

    if (!FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GE)( psBX0->m_vExtent, FCN_V(tgMH_Init_Vector)( FCN_V(tgMH_SET1)( VAR_K(KTgROOT_EPS) ) ) ) ))
    {
        return (false);
    };

    return (true);
}


/* ---- FCN_VO(tgGM_BX_Support_Point) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_BX_Support_Point)( VEC_OBJ_T(TgBOX,CPCU) psBX0, VEC_T(1,C) vDN )
{
    VEC_T(1)                            vA0, vA1, vA2, vC0;

    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_BX_Is_Valid)( psBX0 ));
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Unit_Vector)( vDN ));

    FCN_V(tgMH_Query_Reference_Frame,3)( &vA0, &vA1, &vA2, &vC0, &psBX0->m_mReference_Frame );

    {
        VEC_T(1,C)                          vE0 = FCN_V(tgMH_CP_SGN)( FCN_V(tgMH_SPX)( psBX0->m_vExtent ), FCN_V(tgMH_DOT)( vDN, vA0 ) );
        VEC_T(1,C)                          vE1 = FCN_V(tgMH_CP_SGN)( FCN_V(tgMH_SPY)( psBX0->m_vExtent ), FCN_V(tgMH_DOT)( vDN, vA1 ) );
        VEC_T(1,C)                          vE2 = FCN_V(tgMH_CP_SGN)( FCN_V(tgMH_SPZ)( psBX0->m_vExtent ), FCN_V(tgMH_DOT)( vDN, vA2 ) );

        VEC_T(1,C)                          vV0 = FCN_V(tgMH_MAD)( vE0, vA0, vC0 );
        VEC_T(1,C)                          vV1 = FCN_V(tgMH_MAD)( vE1, vA1, vV0 );
        VEC_T(1,C)                          vV2 = FCN_V(tgMH_MAD)( vE2, vA2, vV1 );

        return (vV2);
    }
}


/* ---- FCN_VO(tgGM_BX_Volume) --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_BX_Volume)( VEC_OBJ_T(TgBOX,CPCU) psBX0 )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_BX_Is_Valid)( psBX0 ));

    {
        VEC_T(1,C)                          vX0 = FCN_V(tgMH_MUL)( FCN_V(tgMH_SPX)( psBX0->m_vExtent ), FCN_V(tgMH_SET1)( TYPE_K(8) ) );
        VEC_T(1,C)                          vX1 = FCN_V(tgMH_MUL)( FCN_V(tgMH_SPY)( psBX0->m_vExtent ), FCN_V(tgMH_SPZ)( psBX0->m_vExtent ) );

        return (FCN_V(tgMH_MUL)( vX0, vX1 ));
    }
}


/* ---- FCN_VO(tgGM_BX_Area) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_BX_Area)( VEC_OBJ_T(TgBOX,CPCU) psBX0 )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_BX_Is_Valid)( psBX0 ));

    {
        VEC_T(1,C)                          vX0 = FCN_V(tgMH_MUL)( FCN_V(tgMH_SPX)( psBX0->m_vExtent ), FCN_V(tgMH_SPY)( psBX0->m_vExtent ) );
        VEC_T(1,C)                          vX1 = FCN_V(tgMH_MAD)( FCN_V(tgMH_SPX)( psBX0->m_vExtent ), FCN_V(tgMH_SPZ)( psBX0->m_vExtent ), vX0 );
        VEC_T(1,C)                          vX2 = FCN_V(tgMH_MAD)( FCN_V(tgMH_SPY)( psBX0->m_vExtent ), FCN_V(tgMH_SPZ)( psBX0->m_vExtent ), vX1 );

        return (FCN_V(tgMH_MUL)( FCN_V(tgMH_SET1)( TYPE_K(8) ), vX2 ));
    }
}


/* ---- FCN_VO(tgGM_BX_BA) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_BX_BA)( VEC_OBJ_T(TgBOXAA,PCU) psBA0, VEC_OBJ_T(TgBOX,CPCU) psBX0 )
{
    VEC_T(1)                            vA0, vA1, vA2, vC0;

    FCN_V(tgMH_Query_Reference_Frame,3)( &vA0, &vA1, &vA2, &vC0, &psBX0->m_mReference_Frame );

    {
        VEC_T(1,C)                          vE0 = FCN_V(tgMH_ABS)( FCN_V(tgMH_MUL)( vA0, FCN_V(tgMH_SPX)( psBX0->m_vExtent ) ) );
        VEC_T(1,C)                          vE1 = FCN_V(tgMH_ABS)( FCN_V(tgMH_MUL)( vA1, FCN_V(tgMH_SPY)( psBX0->m_vExtent ) ) );
        VEC_T(1,C)                          vE2 = FCN_V(tgMH_ABS)( FCN_V(tgMH_MUL)( vA2, FCN_V(tgMH_SPZ)( psBX0->m_vExtent ) ) );

        VEC_T(1,C)                          vX0 = FCN_V(tgMH_ADD)( vE1, vE2 );
        VEC_T(1,C)                          vX1 = FCN_V(tgMH_ADD)( vE0, vX0 );
    
        FCN_VO(tgGM_BA_Init_PT)( psBA0, vC0 );
        FCN_VO(tgGM_BA_Union_PT)( psBA0, FCN_V(tgMH_ADD)( vC0, vX1 ) );
        FCN_VO(tgGM_BA_Union_PT)( psBA0, FCN_V(tgMH_SUB)( vC0, vX1 ) );
    }
}

    
    /* ---- FCN_VO(tgGM_BX_Sweep_BA) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_BX_Sweep_BA)( VEC_OBJ_T(TgBOXAA,PCU) psBA0, VEC_OBJ_T(TgBOX,CPCU) psBX1, VEC_T(1,C) vDT )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_BX_Is_Valid)( psBX1 ) && FCN_V(tgMH_Is_Valid_Vector)( vDT ));

    {
        FCN_VO(tgGM_BX_BA)(psBA0,psBX1);
        FCN_VO(tgGM_BA_Sweep)(psBA0,vDT);
    }
}


/* ---- FCN_VO(tgGM_BX_Project) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_BX_Project)( VEC_T(1,PCU) pvMin, VEC_T(1,PCU) pvMax, VEC_OBJ_T(TgBOX,CPCU) psBX0, VEC_T(1,C) vDN )
{
    VEC_T(1)                            vA0, vA1, vA2, vC0;

    TgGEOM_ASSERT_PARAM(nullptr != pvMin && nullptr != pvMax && FCN_VO(tgGM_BX_Is_Valid)( psBX0 ) && FCN_V(tgMH_Is_Valid_Vector)( vDN ));

    /* Get the three ortho-normal axis and translation of the reference frame */
    FCN_V(tgMH_Query_Reference_Frame,3)( &vA0, &vA1, &vA2, &vC0, &psBX0->m_mReference_Frame );

    {
        VEC_T(1,C)                          vE0 = FCN_V(tgMH_MUL)( FCN_V(tgMH_DOT)( vDN, vA0 ), FCN_V(tgMH_SPX)( psBX0->m_vExtent ) );
        VEC_T(1,C)                          vE1 = FCN_V(tgMH_MUL)( FCN_V(tgMH_DOT)( vDN, vA1 ), FCN_V(tgMH_SPY)( psBX0->m_vExtent ) );
        VEC_T(1,C)                          vE2 = FCN_V(tgMH_MUL)( FCN_V(tgMH_DOT)( vDN, vA2 ), FCN_V(tgMH_SPZ)( psBX0->m_vExtent ) );

        VEC_T(1,C)                          vV0 = FCN_V(tgMH_MUL)( vE0, vA0 );
        VEC_T(1,C)                          vV1 = FCN_V(tgMH_MUL)( vE1, vA1 );
        VEC_T(1,C)                          vV2 = FCN_V(tgMH_MUL)( vE2, vA2 );
        VEC_T(1,C)                          vV3 = FCN_V(tgMH_ADD)( vV1, vV2 );

        *pvMin = FCN_V(tgMH_SUB)( FCN_V(tgMH_SUB)( vC0, vV0 ), vV3 );
        *pvMax = FCN_V(tgMH_ADD)( FCN_V(tgMH_ADD)( vC0, vV0 ), vV3 );
    }
}


/* ---- FCN_VO(tgGM_BX_Is_Contained) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_VO(tgGM_BX_Is_Contained)( VEC_OBJ_T(TgBOX,CPCU) psBX0, VEC_T(1,C) vS0 )
{
    VEC_T(1)                            vA0, vA1, vA2, vC0;

    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_BX_Is_Valid)( psBX0 ) && FCN_V(tgMH_Is_Valid_Point)( vS0 ));

    /* Get the three ortho-normal axis and translation of the reference frame */
    FCN_V(tgMH_Query_Reference_Frame,3)( &vA0, &vA1, &vA2, &vC0, &psBX0->m_mReference_Frame );

    {
        VEC_T(1,C)                          vDS = FCN_V(tgMH_SUB)( vS0, vC0 );

        VEC_T(1,C)                          vV0 = FCN_V(tgMH_ABS)( FCN_V(tgMH_DOT)( vDS, vA0 ) );
        VEC_T(1,C)                          vV1 = FCN_V(tgMH_ABS)( FCN_V(tgMH_DOT)( vDS, vA1 ) );
        VEC_T(1,C)                          vV2 = FCN_V(tgMH_ABS)( FCN_V(tgMH_DOT)( vDS, vA2 ) );
    
        return (
            FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( vV0, FCN_V(tgMH_SPX)( psBX0->m_vExtent ) ) ) &&
            FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( vV1, FCN_V(tgMH_SPY)( psBX0->m_vExtent ) ) ) &&
            FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( vV2, FCN_V(tgMH_SPZ)( psBX0->m_vExtent ) ) )
        );
    }
}


/* ---- FCN_VO(tgGM_BX_TX) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_BX_TX)( VEC_OBJ_T(TgBOX,PCU) psBX0, VEC_T(3,CPCU) pmM0 )
{
    TgGEOM_ASSERT_PARAM(!FCN_V(tgMH_NAN,3)( pmM0 ));

    FCN_V(tgMH_CAT,3)( &psBX0->m_mReference_Frame, &psBX0->m_mReference_Frame, pmM0 );
}


/* ---- FCN_VO(tgGM_BX_Copy_TX) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_BX_Copy_TX)( VEC_OBJ_T(TgBOX,PCU) psBX0, VEC_OBJ_T(TgBOX,CPCU) psBX1, VEC_T(3,CPCU) pmM0 )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_BX_Is_Valid)( psBX1 ) && !FCN_V(tgMH_NAN,3)( pmM0 ));

    FCN_V(tgMH_CAT,3)( &psBX0->m_mReference_Frame, &psBX1->m_mReference_Frame, pmM0 );
    psBX0->m_vExtent = psBX1->m_vExtent;
}


/* ---- FCN_VO(tgGM_BX_Init) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_BX_Init)( VEC_OBJ_T(TgBOX,PCU) psBX0, VEC_T(3,CPCU) pmTX, VEC_T(1,C) vExtent )
{
    FCN_VO(tgGM_BX_Set_Reference_Frame)( psBX0, pmTX );
    psBX0->m_vExtent = vExtent;
}


/* ---- FCN_VO(tgGM_BX_Copy) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_BX_Copy)( VEC_OBJ_T(TgBOX,PCU) psBX0, VEC_OBJ_T(TgBOX,CPCU) psBX1 )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_BX_Is_Valid)( psBX1 ));

    psBX0->m_mReference_Frame = psBX1->m_mReference_Frame;
    psBX0->m_vExtent = psBX1->m_vExtent;
}


/* ---- FCN_VO(tgGM_BX_Set_Reference_Frame) -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_BX_Set_Reference_Frame)( VEC_OBJ_T(TgBOX,PCU) psBX0, VEC_T(3,CPCU) pmM0 )
{
    TgGEOM_ASSERT_PARAM(!FCN_V(tgMH_NAN,3)( pmM0 ));
    psBX0->m_mReference_Frame = *pmM0;
}


/* ---- FCN_VO(tgGM_BX_Set_Origin) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_BX_Set_Origin)( VEC_OBJ_T(TgBOX,PCU) psBX0, VEC_T(1,C) vOrigin )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Point)( vOrigin ));
    FCN_V(tgMH_Set_T,3)( &psBX0->m_mReference_Frame, vOrigin );
}


/* ---- FCN_VO(tgGM_BX_Set_Extent_List) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_BX_Set_Extent_List)( VEC_OBJ_T(TgBOX,PCU) psBX0, VEC_T(1,C) vExtent )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid)( vExtent ));
    psBX0->m_vExtent = vExtent;
}


/* ---- FCN_VO(tgGM_BX_Set_Extent_Index) ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_BX_Set_Extent_Index)( VEC_OBJ_T(TgBOX,PCU) psBX0, TgRSIZE_C uiIndex, VEC_T(1,C) vExtent )
{
    TgGEOM_ASSERT_PARAM(uiIndex < 3 && FCN_V(tgMH_Is_Valid_Broadcast_Positive_Scalar)( vExtent ));

    {
        VEC_UN_T(1,C)                       uExtent = { VEC_UN_1_MEMBER() = vExtent };
        VEC_UN_T(1)                         uBX0_Extent = { VEC_UN_1_MEMBER() = psBX0->m_vExtent };

        VEC_S_UN_1_MEMBER(uBX0_Extent).m_aData[uiIndex] = VEC_S_UN_1_MEMBER(uExtent).m_aData[uiIndex];
        psBX0->m_vExtent = VEC_UN_1_MEMBER(uBX0_Extent);
    }
}


/* ---- FCN_VO(tgGM_BX_Set_Extent_0) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_BX_Set_Extent_0)( VEC_OBJ_T(TgBOX,PCU) psBX0, VEC_T(1,C) vExtent )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Broadcast_Non_Negative_Scalar)( vExtent ));

    {
        VEC_UN_T(1,C)                       uExtent = { VEC_UN_1_MEMBER() = vExtent };
        VEC_UN_T(1)                         uBX0_Extent = { VEC_UN_1_MEMBER() = psBX0->m_vExtent };

        VEC_S_UN_1_MEMBER(uBX0_Extent).x = VEC_S_UN_1_MEMBER(uExtent).x;
        psBX0->m_vExtent = VEC_UN_1_MEMBER(uBX0_Extent);
    }
}


/* ---- FCN_VO(tgGM_BX_Set_Extent_1) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_BX_Set_Extent_1)( VEC_OBJ_T(TgBOX,PCU) psBX0, VEC_T(1,C) vExtent )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Broadcast_Non_Negative_Scalar)( vExtent ));

    {
        VEC_UN_T(1,C)                       uExtent = { VEC_UN_1_MEMBER() = vExtent };
        VEC_UN_T(1)                         uBX0_Extent = { VEC_UN_1_MEMBER() = psBX0->m_vExtent };

        VEC_S_UN_1_MEMBER(uBX0_Extent).y = VEC_S_UN_1_MEMBER(uExtent).y;
        psBX0->m_vExtent = VEC_UN_1_MEMBER(uBX0_Extent);
    }
}


/* ---- FCN_VO(tgGM_BX_Set_Extent_2) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_BX_Set_Extent_2)( VEC_OBJ_T(TgBOX,PCU) psBX0, VEC_T(1,C) vExtent )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Broadcast_Non_Negative_Scalar)( vExtent ));

    {
        VEC_UN_T(1,C)                       uExtent ={VEC_UN_1_MEMBER() = vExtent};
        VEC_UN_T(1)                         uBX0_Extent ={VEC_UN_1_MEMBER() = psBX0->m_vExtent};

        VEC_S_UN_1_MEMBER(uBX0_Extent).z = VEC_S_UN_1_MEMBER(uExtent).z;
        psBX0->m_vExtent = VEC_UN_1_MEMBER(uBX0_Extent);
    }
}


/* ---- FCN_VO(tgGM_BX_Query_Origin) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_BX_Query_Origin)( VEC_OBJ_T(TgBOX,CPCU) psBX0 )
{
    return (FCN_V(tgMH_Query_Axis_3,3)( &psBX0->m_mReference_Frame ));
}


/* ---- FCN_VO(tgGM_BX_Query_Axis_Unit_0) ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_BX_Query_Axis_Unit_0)( VEC_OBJ_T(TgBOX,CPCU) psBX0 )
{
    return (FCN_V(tgMH_Query_Axis_0,3)( &psBX0->m_mReference_Frame ));
}


/* ---- FCN_VO(tgGM_BX_Query_Axis_Unit_1) ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_BX_Query_Axis_Unit_1)( VEC_OBJ_T(TgBOX,CPCU) psBX0 )
{
    return (FCN_V(tgMH_Query_Axis_1,3)( &psBX0->m_mReference_Frame ));
}


/* ---- FCN_VO(tgGM_BX_Query_Axis_Unit_2) ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_BX_Query_Axis_Unit_2)( VEC_OBJ_T(TgBOX,CPCU) psBX0 )
{
    return (FCN_V(tgMH_Query_Axis_2,3)( &psBX0->m_mReference_Frame ));
}


/* ---- FCN_VO(tgGM_BX_Query_Extent_List) ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_BX_Query_Extent_List)( VEC_OBJ_T(TgBOX,CPCU) psBX0 )
{
    return (psBX0->m_vExtent);
}


/* ---- FCN_VO(tgGM_BX_Query_Extent_Index) --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_BX_Query_Extent_Index)( VEC_OBJ_T(TgBOX,CPCU) psBX0, TgRSIZE_C uiIndex )
{
    VEC_UN_T(1)     uBX0_Extent = { VEC_UN_1_MEMBER() = psBX0->m_vExtent };

    return (FCN_V(tgMH_SET1)( VEC_S_UN_1_MEMBER(uBX0_Extent).m_aData[uiIndex] ));
}


/* ---- FCN_VO(tgGM_BX_Query_Extent_0) ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_BX_Query_Extent_0)( VEC_OBJ_T(TgBOX,CPCU) psBX0 )
{
    return (FCN_V(tgMH_SPX)( psBX0->m_vExtent ));
}


/* ---- FCN_VO(tgGM_BX_Query_Extent_1) ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_BX_Query_Extent_1)( VEC_OBJ_T(TgBOX,CPCU) psBX0 )
{
    return (FCN_V(tgMH_SPY)( psBX0->m_vExtent ));
}


/* ---- FCN_VO(tgGM_BX_Query_Extent_2) ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_BX_Query_Extent_2)( VEC_OBJ_T(TgBOX,CPCU) psBX0 )
{
    return (FCN_V(tgMH_SPZ)( psBX0->m_vExtent ));
}


/* =============================================================================================================================================================================== */
#endif
