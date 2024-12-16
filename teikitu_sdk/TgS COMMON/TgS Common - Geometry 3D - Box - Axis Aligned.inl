/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Geometry 3D - Box - Axis Aligned.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_GEOMETRY_3D_BOX_AA_INL)

#if !defined (TEMPLATE_TYPE_EXPANSION__RELOAD)
    #error Must be included as part of a type expansion include chain
#endif


/* == Common ===================================================================================================================================================================== */

/* ---- FCN_VO(tgGM_BA_Calc_Point_Index) ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_BA_Calc_Point_Index)( VEC_OBJ_T(TgBOXAA,CPCU) psBA0, TgRSIZE_C uiFlag )
{
    union FCN_V(tgMH_SEL_DATA_ALIAS_OUTPUT_S)
    {
        VEC_T(1)                                    v;
        UVAR_T()                                    ui[sizeof( VEC_S_T(1) ) / sizeof( UVAR_T() )];
    }                                   uSelect;

    uSelect.ui[0] = (0 != (uiFlag & 1)) ? UVAR_K(KTgMAX) : 0;
    uSelect.ui[1] = (0 != (uiFlag & 2)) ? UVAR_K(KTgMAX) : 0;
    uSelect.ui[2] = (0 != (uiFlag & 4)) ? UVAR_K(KTgMAX) : 0;
    uSelect.ui[3] = 0;

    return (FCN_V(tgMH_SEL)( psBA0->m_vMin, psBA0->m_vMax, uSelect.v ));
}


/* ---- FCN_VO(tgGM_BA_Is_Empty) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_VO(tgGM_BA_Is_Empty)( VEC_OBJ_T(TgBOXAA,CPCU) TgANALYSIS_NO_NULL psBA0 )
{
    VEC_T(1_C)                          vCMP = FCN_V(tgMH_Init_Vector)( FCN_V(tgMH_CMP_GE)( psBA0->m_vMin, psBA0->m_vMax ) );

    return (FCN_V(tgMH_CMP_ANY_TO_BOOL)( vCMP ));
}


/* ---- FCN_VO(tgGM_BA_Union_PT) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_BA_Union_PT)( VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL psBA0, VEC_T(1,C) vS0 )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Point)( vS0 ));
    psBA0->m_vMin = FCN_V(tgMH_MIN)( psBA0->m_vMin, FCN_V(tgMH_Init_Vector)( vS0 ) );
    psBA0->m_vMax = FCN_V(tgMH_MAX)( psBA0->m_vMax, FCN_V(tgMH_Init_Vector)( vS0 ) );
}


/* ---- FCN_VO(tgGM_BA_Union_SP) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_BA_Union_SP)( VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL psBA0, VEC_T(1,C) vS0, VEC_T(1,C) vRadius )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Point)( vS0 ) && (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GE)( vRadius, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) )));

    {
        VEC_T(1,C)                          vRad = FCN_V(tgMH_Init_Vector)( vRadius );
        VEC_T(1,C)                          vX0 = FCN_V(tgMH_Init_Vector)( vS0 );

        psBA0->m_vMin = FCN_V(tgMH_MIN)( psBA0->m_vMin, FCN_V(tgMH_SUB)( vX0, vRad ) );
        psBA0->m_vMax = FCN_V(tgMH_MAX)( psBA0->m_vMax, FCN_V(tgMH_ADD)( vX0, vRad ) );
    }
}


/* ---- FCN_VO(tgGM_BA_Union_BA) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_BA_Union_BA)( VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL psBA0, VEC_OBJ_T(TgBOXAA,CPCU) TgANALYSIS_NO_NULL psBA1 )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_BA_Is_Valid)( psBA1 ));

    psBA0->m_vMin = FCN_V(tgMH_MIN)( psBA0->m_vMin, psBA1->m_vMin );
    psBA0->m_vMax = FCN_V(tgMH_MAX)( psBA0->m_vMax, psBA1->m_vMax );
}


/* ---- FCN_VO(tgGM_BA_Sweep) ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_BA_Sweep)( VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL psBA0, VEC_T(1,C) vDT )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Vector)( vDT ));

    psBA0->m_vMin = FCN_V(tgMH_MIN)( psBA0->m_vMin, FCN_V(tgMH_ADD)( psBA0->m_vMin, vDT ) );
    psBA0->m_vMax = FCN_V(tgMH_MAX)( psBA0->m_vMax, FCN_V(tgMH_ADD)( psBA0->m_vMax, vDT ) );
}


/* ---- FCN_VO(tgGM_BA_Expand) --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_BA_Expand)( VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL psBA0, VEC_T(1,C) vExpand )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Broadcast_Non_Negative_Scalar)( vExpand ))

    {
        VEC_T(1,C)                          vX0 = FCN_V(tgMH_Init_Vector)( vExpand );

        psBA0->m_vMin = FCN_V(tgMH_SUB)( psBA0->m_vMin, vX0 );
        psBA0->m_vMax = FCN_V(tgMH_ADD)( psBA0->m_vMax, vX0 );
    }
}


/* ---- FCN_VO(tgGM_BA_Scale) ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_BA_Scale)( VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL psBA0, VEC_T(1,C) vScale )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Broadcast_Non_Negative_Scalar)( vScale ))

    {
        VEC_T(1,C)                          vOrigin = FCN_V(tgMH_Init_Vector)( FCN_VO(tgGM_BA_Query_Centre)( psBA0 ) );

        VEC_T(1,C)                          vX0 = FCN_V(tgMH_SUB)( psBA0->m_vMin, vOrigin );
        VEC_T(1,C)                          vExtent = FCN_V(tgMH_MUL)( vX0, vScale );

        psBA0->m_vMin = FCN_V(tgMH_ADD)( vOrigin, vExtent );
        psBA0->m_vMax = FCN_V(tgMH_SUB)( vOrigin, vExtent );
    };
}


/* ---- FCN_VO(tgGM_BA_Query_Centre) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_BA_Query_Centre)( VEC_OBJ_T(TgBOXAA,CPCU) TgANALYSIS_NO_NULL psBA0 )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_BA_Is_Valid)( psBA0 ));
    return (FCN_V(tgMH_Init_Point)( FCN_V(tgMH_AVG)( psBA0->m_vMin, psBA0->m_vMax ) ));
}


/* ---- FCN_VO(tgGM_BA_Reset) ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_BA_Reset)( VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL psBA0 )
{
    FCN_VO(tgGM_BA_Zero)( psBA0 );
}


/* ---- FCN_VO(tgGM_BA_Zero) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_BA_Zero)( VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL psBA0 )
{
    psBA0->m_vMin = FCN_V(tgMH_Init_Vector_ELEM)(  VAR_K(KTgMAX),  VAR_K(KTgMAX),  VAR_K(KTgMAX) );
    psBA0->m_vMax = FCN_V(tgMH_Init_Vector_ELEM)( -VAR_K(KTgMAX), -VAR_K(KTgMAX), -VAR_K(KTgMAX) );
}


/* ---- FCN_VO(tgGM_BA_Is_Valid) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_VO(tgGM_BA_Is_Valid)( VEC_OBJ_T(TgBOXAA,CPCU) TgANALYSIS_NO_NULL psBA0 )
{
    if (!FCN_V(tgMH_Is_Valid)( psBA0->m_vMin ))
    {
        return (false);
    };

    if (!FCN_V(tgMH_Is_Valid)( psBA0->m_vMax ))
    {
        return (false);
    };

    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GE)( psBA0->m_vMin, psBA0->m_vMax ) ))
    {
        return (false);
    };

    return (true);
}


/* ---- FCN_VO(tgGM_BA_Support_Point) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_BA_Support_Point)( VEC_OBJ_T(TgBOXAA,CPCU) TgANALYSIS_NO_NULL psBA0, VEC_T(1,C) vDN )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_BA_Is_Valid)( psBA0 ));
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Unit_Vector)( vDN ));

    {
        VEC_T(1,C)                          vOrigin = FCN_VO(tgGM_BA_Query_Centre)( psBA0 );
        VEC_T(1,C)                          vExtent = FCN_V(tgMH_ABS)( FCN_V(tgMH_SUB)( psBA0->m_vMin, vOrigin ) );
        VEC_T(1,C)                          vX0 = FCN_V(tgMH_MUL)( FCN_V(tgMH_SGN)( vDN ), vExtent );
        VEC_T(1,C)                          vReturn = FCN_V(tgMH_ADD)( vX0, vOrigin );

        return (vReturn);
    };
}


/* ---- FCN_VO(tgGM_BA_Volume) --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_BA_Volume)( VEC_OBJ_T(TgBOXAA,CPCU) TgANALYSIS_NO_NULL psBA0 )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_BA_Is_Valid)( psBA0 ));

    {
        VEC_T(1,C)                          vExtent = FCN_V(tgMH_SUB)( psBA0->m_vMax, psBA0->m_vMin );
        VEC_T(1,C)                          vX0 = FCN_V(tgMH_MUL)( FCN_V(tgMH_SPX)(vExtent), FCN_V(tgMH_SPY)(vExtent) );
        VEC_T(1,C)                          vRet = FCN_V(tgMH_MUL)( vX0, FCN_V(tgMH_SPZ)(vExtent) );

        return (vRet);
    };
}


/* ---- FCN_VO(tgGM_BA_Area) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_BA_Area)( VEC_OBJ_T(TgBOXAA,CPCU) TgANALYSIS_NO_NULL psBA0 )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_BA_Is_Valid)( psBA0 ));

    {
        VEC_T(1,C)                          vExtent = FCN_V(tgMH_SUB)( psBA0->m_vMax, psBA0->m_vMin );
        VEC_T(1,C)                          vX0 = FCN_V(tgMH_MUL)( FCN_V(tgMH_SPX)(vExtent), FCN_V(tgMH_SPY)(vExtent) );
        VEC_T(1,C)                          vX1 = FCN_V(tgMH_MAD)( FCN_V(tgMH_SPX)(vExtent), FCN_V(tgMH_SPZ)(vExtent), vX0 );
        VEC_T(1,C)                          vX2 = FCN_V(tgMH_MAD)( FCN_V(tgMH_SPY)(vExtent), FCN_V(tgMH_SPZ)(vExtent), vX1 );

        return (FCN_V(tgMH_MUL)( FCN_V(tgMH_SET1)( TYPE_K(2) ), vX2 ));
    };
}


/* ---- FCN_VO(tgGM_BA_BA) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_BA_BA)( VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL psBA0, VEC_OBJ_T(TgBOXAA,CPCU) TgANALYSIS_NO_NULL psBA1 )
{
    FCN_VO(tgGM_BA_Copy)( psBA0, psBA1 );
}


/* ---- FCN_VO(tgGM_BA_Sweep_BA) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_BA_Sweep_BA)( VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL psBA0, VEC_OBJ_T(TgBOXAA,CPCU) TgANALYSIS_NO_NULL psBA1, VEC_T(1,C) vDT )
{
    FCN_VO(tgGM_BA_Copy)( psBA0, psBA1 );
    FCN_VO(tgGM_BA_Sweep)( psBA0, vDT );
}


/* ---- FCN_VO(tgGM_BA_Project) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_BA_Project)( VEC_T(1,PCU) TgANALYSIS_NO_NULL pvMin, VEC_T(1,PCU) TgANALYSIS_NO_NULL pvMax, VEC_OBJ_T(TgBOXAA,CPCU) TgANALYSIS_NO_NULL psBA0, VEC_T(1,C) vDN )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_BA_Is_Valid)( psBA0 ) && FCN_V(tgMH_Is_Valid_Vector)( vDN ));

    {
        VEC_T(1,C)                          vOrigin = FCN_VO(tgGM_BA_Query_Centre)( psBA0 );
        VEC_T(1,C)                          vX0 = FCN_V(tgMH_ABS)( FCN_V(tgMH_SUB)( psBA0->m_vMin, vOrigin ) );
        VEC_T(1,C)                          vExtent = FCN_V(tgMH_MUL)( FCN_V(tgMH_SGN)( vDN ), vX0 );

        VEC_T(1,C)                          vMin_Proj = FCN_V(tgMH_DOT)( vDN, FCN_V(tgMH_SUB)( vOrigin, vExtent ) );
        VEC_T(1,C)                          vMax_Proj = FCN_V(tgMH_DOT)( vDN, FCN_V(tgMH_ADD)( vOrigin, vExtent ) );
    
        *pvMin = vMin_Proj;
        *pvMax = vMax_Proj;
    }
}


/* ---- FCN_VO(tgGM_BA_Is_Contained) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_VO(tgGM_BA_Is_Contained)( VEC_OBJ_T(TgBOXAA,CPCU) TgANALYSIS_NO_NULL psBA0, VEC_T(1,C) vP0 )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_BA_Is_Valid)( psBA0 ) && FCN_V(tgMH_Is_Valid_Point)( vP0 ));

    return (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_AND)( FCN_V(tgMH_CMP_GE)( vP0, psBA0->m_vMin ), FCN_V(tgMH_CMP_LE)( vP0, psBA0->m_vMax ) ) ));
}


/* ---- FCN_VO(tgGM_BA_TX) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_BA_TX)( VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL psBA0, VEC_T(3,CPCU) TgANALYSIS_NO_NULL pmM0 )
{
    VEC_T(1,C)                          vA0 = FCN_V(tgMH_ABS)( FCN_V(tgMH_Query_Axis_0,3)( pmM0 ) );
    VEC_T(1,C)                          vA1 = FCN_V(tgMH_ABS)( FCN_V(tgMH_Query_Axis_1,3)( pmM0 ) );
    VEC_T(1,C)                          vA2 = FCN_V(tgMH_ABS)( FCN_V(tgMH_Query_Axis_2,3)( pmM0 ) );
    VEC_T(1,C)                          vA3 = FCN_V(tgMH_Query_Axis_3,3)( pmM0 );

    VEC_T(1,C)                          vV0 = FCN_V(tgMH_MUL)( FCN_VO(tgGM_BA_Query_Size_X)( psBA0 ), vA0 );
    VEC_T(1,C)                          vV1 = FCN_V(tgMH_MAD)( FCN_VO(tgGM_BA_Query_Size_Y)( psBA0 ), vA1, vV0 );
    VEC_T(1,C)                          vV2 = FCN_V(tgMH_MAD)( FCN_VO(tgGM_BA_Query_Size_Z)( psBA0 ), vA2, vV1 );
    VEC_T(1,C)                          vV3 = FCN_V(tgMH_MUL)( FCN_V(tgMH_SET1)( TYPE_K(0,5) ), vV2 );

    VEC_T(1,C)                          vV4 = FCN_VO(tgGM_BA_Query_Centre)( psBA0 );
    VEC_T(1,C)                          vV5 = FCN_V(tgMH_Init_Vector)( FCN_V(tgMH_ADD)( vV4, vA3 ) );

    psBA0->m_vMin = FCN_V(tgMH_SUB)( vV5, vV3 );
    psBA0->m_vMax = FCN_V(tgMH_ADD)( vV5, vV3 );
}


/* ---- FCN_VO(tgGM_BA_Copy_TX) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_BA_Copy_TX)( VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL psBA_Out, VEC_OBJ_T(TgBOXAA,CPCU) TgANALYSIS_NO_NULL psBA0, VEC_T(3,CPCU) TgANALYSIS_NO_NULL pmM0 )
{
    FCN_VO(tgGM_BA_Copy)( psBA_Out, psBA0 );
    FCN_VO(tgGM_BA_TX)( psBA_Out, pmM0 );
}


/* ---- FCN_VO(tgGM_BA_Init) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_BA_Init)( VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL psBA0, VEC_T(1,C) vMin, VEC_T(1,C) vMax )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid)( vMin ) && FCN_V(tgMH_Is_Valid)( vMax ));

    psBA0->m_vMin = vMin;
    psBA0->m_vMax = vMax;
}


/* ---- FCN_VO(tgGM_BA_Init_PT) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_BA_Init_PT)( VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL psBA0, VEC_T(1,C) vPoint )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Point)( vPoint ));

    psBA0->m_vMin = FCN_V(tgMH_Init_Vector)( vPoint );
    psBA0->m_vMax = FCN_V(tgMH_Init_Vector)( vPoint );
}


/* ---- FCN_VO(tgGM_BA_Init_SP) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_BA_Init_SP)( VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL psBA0, VEC_T(1,C) vS0, VEC_T(1,C) vRadius )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Point)( vS0 ));
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Broadcast_Positive_Scalar)( vRadius ));

    {
        VEC_T(1,C)                          vRad = FCN_V(tgMH_Init_Vector)( vRadius );
        VEC_T(1,C)                          vX0 = FCN_V(tgMH_Init_Vector)( vS0 );

        psBA0->m_vMin = FCN_V(tgMH_SUB)( vX0, vRad );
        psBA0->m_vMax = FCN_V(tgMH_ADD)( vX0, vRad );
    }
}


/* ---- FCN_VO(tgGM_BA_Copy) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_BA_Copy)( VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL psBA0, VEC_OBJ_T(TgBOXAA,CPCU) TgANALYSIS_NO_NULL psBA1 )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_BA_Is_Valid)( psBA1 ));

    psBA0->m_vMin = psBA1->m_vMin;
    psBA0->m_vMax = psBA1->m_vMax;
}


/* ---- FCN_VO(tgGM_BA_Set_Invalid) ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_BA_Set_Invalid)( VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL psBA0 )
{
    psBA0->m_vMin = FCN_V(tgMH_Init_Vector)( FCN_V(tgMH_SET1)(  VAR_K(KTgMAX) ) );
    psBA0->m_vMax = FCN_V(tgMH_Init_Vector)( FCN_V(tgMH_SET1)( -VAR_K(KTgMAX) ) );
}


/* ---- FCN_VO(tgGM_BA_Set_Min) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_BA_Set_Min)( VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL psBA0, VEC_T(1,C) vMin )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Vector)( vMin ));
    psBA0->m_vMin = vMin;
}


/* ---- FCN_VO(tgGM_BA_Set_Max) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_BA_Set_Max)( VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL psBA0, VEC_T(1,C) vMax )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Vector)( vMax ));
    psBA0->m_vMax = vMax;
}


/* ---- FCN_VO(tgGM_BA_Set_Min_X) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_BA_Set_Min_X)( VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL psBA0, VEC_T(1,C) vMinX )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Broadcast_Scalar)( vMinX ));

    {
        VEC_UN_T(1,C)                       uMinX = { VEC_UN_1_MEMBER() = vMinX };
        VEC_UN_T(1)                         uBA0_Min = { VEC_UN_1_MEMBER() = psBA0->m_vMin };

        VEC_S_UN_1_MEMBER(uBA0_Min).x = VEC_S_UN_1_MEMBER(uMinX).x;
        psBA0->m_vMin = VEC_UN_1_MEMBER(uBA0_Min);
    }
}


/* ---- FCN_VO(tgGM_BA_Set_Min_Y) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_BA_Set_Min_Y)( VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL psBA0, VEC_T(1,C) vMinY )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Broadcast_Scalar)( vMinY ));

    {
        VEC_UN_T(1,C)                       uMinY = { VEC_UN_1_MEMBER() = vMinY };
        VEC_UN_T(1)                         uBA0_Min = { VEC_UN_1_MEMBER() = psBA0->m_vMin };

        VEC_S_UN_1_MEMBER(uBA0_Min).y = VEC_S_UN_1_MEMBER(uMinY).x;
        psBA0->m_vMin = VEC_UN_1_MEMBER(uBA0_Min);
    }
}


/* ---- FCN_VO(tgGM_BA_Set_Min_Z) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_BA_Set_Min_Z)( VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL psBA0, VEC_T(1,C) vMinZ )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Broadcast_Scalar)( vMinZ ));

    {
        VEC_UN_T(1,C)                       uMinZ = { VEC_UN_1_MEMBER() = vMinZ };
        VEC_UN_T(1)                         uBA0_Min = { VEC_UN_1_MEMBER() = psBA0->m_vMin };

        VEC_S_UN_1_MEMBER(uBA0_Min).z = VEC_S_UN_1_MEMBER(uMinZ).x;
        psBA0->m_vMin = VEC_UN_1_MEMBER(uBA0_Min);
    }
}


/* ---- FCN_VO(tgGM_BA_Set_Max_X) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_BA_Set_Max_X)( VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL psBA0, VEC_T(1,C) vMaxX )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Broadcast_Scalar)( vMaxX ));

    {
        VEC_UN_T(1,C)                       uMaxX = { VEC_UN_1_MEMBER() = vMaxX };
        VEC_UN_T(1)                         uBA0_Max = { VEC_UN_1_MEMBER() = psBA0->m_vMax };

        VEC_S_UN_1_MEMBER(uBA0_Max).x = VEC_S_UN_1_MEMBER(uMaxX).x;
        psBA0->m_vMax = VEC_UN_1_MEMBER(uBA0_Max);
    }
}


/* ---- FCN_VO(tgGM_BA_Set_Max_Y) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_BA_Set_Max_Y)( VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL psBA0, VEC_T(1,C) vMaxY )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Broadcast_Scalar)( vMaxY ));

    {
        VEC_UN_T(1,C)                       uMaxY = { VEC_UN_1_MEMBER() = vMaxY };
        VEC_UN_T(1)                         uBA0_Max = { VEC_UN_1_MEMBER() = psBA0->m_vMax };

        VEC_S_UN_1_MEMBER(uBA0_Max).y = VEC_S_UN_1_MEMBER(uMaxY).x;
        psBA0->m_vMax = VEC_UN_1_MEMBER(uBA0_Max);
    }
}


/* ---- FCN_VO(tgGM_BA_Set_Max_Z) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_BA_Set_Max_Z)( VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL psBA0, VEC_T(1,C) vMaxZ )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Broadcast_Scalar)( vMaxZ ));

    {
        VEC_UN_T(1,C)                       uMaxZ = { VEC_UN_1_MEMBER() = vMaxZ };
        VEC_UN_T(1)                         uBA0_Max = { VEC_UN_1_MEMBER() = psBA0->m_vMax };

        VEC_S_UN_1_MEMBER(uBA0_Max).z = VEC_S_UN_1_MEMBER(uMaxZ).x;
        psBA0->m_vMax = VEC_UN_1_MEMBER(uBA0_Max);
    }
}


/* ---- FCN_VO(tgGM_BA_Query_Min) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_BA_Query_Min)( VEC_OBJ_T(TgBOXAA,CPCU) TgANALYSIS_NO_NULL psBA0 )
{
    return (psBA0->m_vMin);
}


/* ---- FCN_VO(tgGM_BA_Query_Max) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_BA_Query_Max)( VEC_OBJ_T(TgBOXAA,CPCU) TgANALYSIS_NO_NULL psBA0 )
{
    return (psBA0->m_vMax);
}


/* ---- FCN_VO(tgGM_BA_Query_Min_X) ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_BA_Query_Min_X)( VEC_OBJ_T(TgBOXAA,CPCU) TgANALYSIS_NO_NULL psBA0 )
{
    return (FCN_V(tgMH_SPX)(psBA0->m_vMin));
}


/* ---- FCN_VO(tgGM_BA_Query_Min_Y) ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_BA_Query_Min_Y)( VEC_OBJ_T(TgBOXAA,CPCU) TgANALYSIS_NO_NULL psBA0 )
{
    return (FCN_V(tgMH_SPY)(psBA0->m_vMin));
}


/* ---- FCN_VO(tgGM_BA_Query_Min_Z) ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_BA_Query_Min_Z)( VEC_OBJ_T(TgBOXAA,CPCU) TgANALYSIS_NO_NULL psBA0 )
{
    return (FCN_V(tgMH_SPZ)(psBA0->m_vMin));
}


/* ---- FCN_VO(tgGM_BA_Query_Max_X) ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_BA_Query_Max_X)( VEC_OBJ_T(TgBOXAA,CPCU) TgANALYSIS_NO_NULL psBA0 )
{
    return (FCN_V(tgMH_SPX)(psBA0->m_vMax));
}


/* ---- FCN_VO(tgGM_BA_Query_Max_Y) ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_BA_Query_Max_Y)( VEC_OBJ_T(TgBOXAA,CPCU) TgANALYSIS_NO_NULL psBA0 )
{
    return (FCN_V(tgMH_SPY)(psBA0->m_vMax));
}


/* ---- FCN_VO(tgGM_BA_Query_Max_Z) ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_BA_Query_Max_Z)( VEC_OBJ_T(TgBOXAA,CPCU) TgANALYSIS_NO_NULL psBA0 )
{
    return (FCN_V(tgMH_SPZ)(psBA0->m_vMax));
}


/* ---- FCN_VO(tgGM_BA_Query_Size_X) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_BA_Query_Size_X)( VEC_OBJ_T(TgBOXAA,CPCU) TgANALYSIS_NO_NULL psBA0 )
{
    return (FCN_V(tgMH_SUB)( FCN_V(tgMH_SPX)(psBA0->m_vMax), FCN_V(tgMH_SPX)(psBA0->m_vMin) ));
}


/* ---- FCN_VO(tgGM_BA_Query_Size_Y) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_BA_Query_Size_Y)( VEC_OBJ_T(TgBOXAA,CPCU) TgANALYSIS_NO_NULL psBA0 )
{
    return (FCN_V(tgMH_SUB)( FCN_V(tgMH_SPY)(psBA0->m_vMax), FCN_V(tgMH_SPY)(psBA0->m_vMin) ));
}


/* ---- FCN_VO(tgGM_BA_Query_Size_Z) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_BA_Query_Size_Z)( VEC_OBJ_T(TgBOXAA,CPCU) TgANALYSIS_NO_NULL psBA0 )
{
    return (FCN_V(tgMH_SUB)( FCN_V(tgMH_SPZ)(psBA0->m_vMax), FCN_V(tgMH_SPZ)(psBA0->m_vMin) ));
}


/* =============================================================================================================================================================================== */
#endif
