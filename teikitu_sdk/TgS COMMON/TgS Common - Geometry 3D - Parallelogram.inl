/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Geometry 3D - Parallelogram.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_GEOMETRY_3D_PARALLELOGRAM_INL)

#if !defined (TEMPLATE_TYPE_EXPANSION__RELOAD)
    #error Must be included as part of a type expansion include chain
#endif


/* == Common ===================================================================================================================================================================== */

/* ---- FCN_VO(tgGM_PE_Reset) ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_PE_Reset)( VEC_OBJ_T(TgPARALLELOGRAM,PCU) psPE0 )
{
    psPE0->m_vOrigin = FCN_V(tgMH_Init_Point)( FCN_V(tgMH_SET1)( TYPE_K(0) ) );
    psPE0->m_avEdge[0] = FCN_V(tgMH_Init_Vector)( FCN_V(tgMH_SET1)( TYPE_K(0) ) );
    psPE0->m_avEdge[1] = FCN_V(tgMH_Init_Vector)( FCN_V(tgMH_SET1)( TYPE_K(0) ) );
    psPE0->m_vNormal = FCN_V(tgMH_Init_Vector)( FCN_V(tgMH_SET1)( TYPE_K(0) ) );
}


/* ---- FCN_VO(tgGM_PE_Is_Valid) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_VO(tgGM_PE_Is_Valid)( VEC_OBJ_T(TgPARALLELOGRAM,CPCU) psPE0 )
{
    if (!FCN_V(tgMH_Is_Valid_Point)( psPE0->m_vOrigin ))
    {
        return (false);
    };

    if (!FCN_V(tgMH_Is_Valid_Vector)( psPE0->m_avEdge[0] ) || FCN_V(tgMH_Is_PRX_CMP_EQ)( psPE0->m_avEdge[0], FCN_V(tgMH_SET1)( TYPE_K(0) ) ))
    {
        return (false);
    };

    if (!FCN_V(tgMH_Is_Valid_Vector)( psPE0->m_avEdge[1] ) || FCN_V(tgMH_Is_PRX_CMP_EQ)( psPE0->m_avEdge[1], FCN_V(tgMH_SET1)( TYPE_K(0) ) ))
    {
        return (false);
    };

    if (!FCN_V(tgMH_Is_Valid_Unit_Vector)( psPE0->m_vNormal ))
    {
        return (false);
    };

    if (!FCN_V(tgMH_Is_Valid_Unit_Vector)( psPE0->m_avEdge_Normal[0] ))
    {
        return (false);
    };

    if (!FCN_V(tgMH_Is_Valid_Unit_Vector)( psPE0->m_avEdge_Normal[1] ))
    {
        return (false);
    };

    if (!FCN_V(tgMH_Is_PRX_CMP_EQ)( FCN_V(tgMH_DOT)( psPE0->m_avEdge[0], psPE0->m_avEdge_Normal[0] ), FCN_V(tgMH_SET1)( TYPE_K(0) ) ))
    {
        return (false);
    };

    if (!FCN_V(tgMH_Is_PRX_CMP_EQ)( FCN_V(tgMH_DOT)( psPE0->m_avEdge[1], psPE0->m_avEdge_Normal[1] ), FCN_V(tgMH_SET1)( TYPE_K(0) ) ))
    {
        return (false);
    };

    if (!FCN_V(tgMH_Is_PRX_CMP_EQ)( FCN_V(tgMH_DOT)( psPE0->m_avEdge[0], psPE0->m_vNormal ), FCN_V(tgMH_SET1)( TYPE_K(0) ) ))
    {
        return (false);
    };

    if (!FCN_V(tgMH_Is_PRX_CMP_EQ)( FCN_V(tgMH_DOT)( psPE0->m_avEdge[1], psPE0->m_vNormal ), FCN_V(tgMH_SET1)( TYPE_K(0) ) ))
    {
        return (false);
    };

    if (!FCN_V(tgMH_Is_PRX_CMP_EQ)( FCN_V(tgMH_DOT)( psPE0->m_avEdge_Normal[0], psPE0->m_vNormal ), FCN_V(tgMH_SET1)( TYPE_K(0) ) ))
    {
        return (false);
    };

    if (!FCN_V(tgMH_Is_PRX_CMP_EQ)( FCN_V(tgMH_DOT)( psPE0->m_avEdge_Normal[1], psPE0->m_vNormal ), FCN_V(tgMH_SET1)( TYPE_K(0) ) ))
    {
        return (false);
    };

    return (true);
}


/* ---- FCN_VO(tgGM_PE_Support_Point) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_PE_Support_Point)( VEC_OBJ_T(TgPARALLELOGRAM,CPCU) psPE1, VEC_T(1,C) vDN )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_PE_Is_Valid)( psPE1 ) && FCN_V(tgMH_Is_Valid_Unit_Vector)( vDN ));

    {
        VEC_T(1,C)                          vSAT_DN_E0 = FCN_V(tgMH_SAT)( FCN_V(tgMH_DOT)( vDN, psPE1->m_avEdge[0] ) );
        VEC_T(1,C)                          vSAT_DN_E1 = FCN_V(tgMH_SAT)( FCN_V(tgMH_DOT)( vDN, psPE1->m_avEdge[1] ) );
        VEC_T(1,C)                          vE0 = FCN_V(tgMH_MUL)( vSAT_DN_E0, psPE1->m_avEdge[0] );
        VEC_T(1,C)                          vE1 = FCN_V(tgMH_MUL)( vSAT_DN_E1, psPE1->m_avEdge[1] );
        VEC_T(1,C)                          vS0 = FCN_V(tgMH_ADD)( vE0, vE1 );

        return (FCN_V(tgMH_ADD)( psPE1->m_vOrigin, vS0 ) );
    }
}


/* ---- FCN_VO(tgGM_PE_Area) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_PE_Area)( VEC_OBJ_T(TgPARALLELOGRAM,CPCU) psPE1 )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_PE_Is_Valid)( psPE1 ));

    {
        VEC_T(1,C)                          vV0 = FCN_V(tgMH_CX)( psPE1->m_avEdge[0], psPE1->m_avEdge[1] );
        VEC_T(1,C)                          vV1 = FCN_V(tgMH_LEN)( vV0 );

        return (vV1);
    }
}


/* ---- FCN_VO(tgGM_PE_BA) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_PE_BA)( VEC_OBJ_T(TgBOXAA,PCU) psBA0, VEC_OBJ_T(TgPARALLELOGRAM,CPCU) psPE1 )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_PE_Is_Valid)( psPE1 ));

    {
        VEC_T(1,C)                          vX0 = FCN_V(tgMH_ADD)( psPE1->m_vOrigin, psPE1->m_avEdge[0] );
        VEC_T(1,C)                          vX1 = FCN_V(tgMH_ADD)( psPE1->m_vOrigin, psPE1->m_avEdge[1] );
        VEC_T(1,C)                          vX2 = FCN_V(tgMH_ADD)( vX0, psPE1->m_avEdge[1] );

        FCN_VO(tgGM_BA_Init_PT)( psBA0, psPE1->m_vOrigin );
        FCN_VO(tgGM_BA_Union_PT)( psBA0, vX0 );
        FCN_VO(tgGM_BA_Union_PT)( psBA0, vX1 );
        FCN_VO(tgGM_BA_Union_PT)( psBA0, vX2 );
    }
}


/* ---- FCN_VO(tgGM_PE_Sweep_BA) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_PE_Sweep_BA)( VEC_OBJ_T(TgBOXAA,PCU) psBA0, VEC_OBJ_T(TgPARALLELOGRAM,CPCU) psPE1, VEC_T(1,C) vDT )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_PE_Is_Valid)( psPE1 ) && FCN_V(tgMH_Is_Valid_Vector)( vDT ));

    FCN_VO(tgGM_PE_BA)( psBA0, psPE1 );
    FCN_VO(tgGM_BA_Sweep)( psBA0, vDT );
}


/* ---- FCN_VO(tgGM_PE_Project) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_PE_Project)( VEC_T(1,PCU) pvMin, VEC_T(1,PCU) pvMax, VEC_OBJ_T(TgPARALLELOGRAM,CPCU) psPE1, VEC_T(1,C) vDN )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_PE_Is_Valid)( psPE1 ) && FCN_V(tgMH_Is_Valid_Unit_Vector)( vDN ));

    {
        VEC_T(1,C)                          vDN_E0 = FCN_V(tgMH_DOT)( vDN, psPE1->m_avEdge[0] );
        VEC_T(1,C)                          vDN_E1 = FCN_V(tgMH_DOT)( vDN, psPE1->m_avEdge[1] );

        VEC_T(1,C)                          vDN_S0 = FCN_V(tgMH_DOT)( vDN, psPE1->m_vOrigin );
        VEC_T(1,C)                          vDN_S1 = FCN_V(tgMH_ADD)( vDN_S0, vDN_E0 );
        VEC_T(1,C)                          vDN_S2 = FCN_V(tgMH_ADD)( vDN_S0, vDN_E1 );
        VEC_T(1,C)                          vDN_S3 = FCN_V(tgMH_ADD)( vDN_S1, vDN_E1 );

        *pvMin = FCN_V(tgMH_MIN)( FCN_V(tgMH_MIN)( vDN_S0, vDN_S1 ), FCN_V(tgMH_MIN)( vDN_S2, vDN_S3 ) );
        *pvMax = FCN_V(tgMH_MAX)( FCN_V(tgMH_MAX)( vDN_S0, vDN_S1 ), FCN_V(tgMH_MAX)( vDN_S2, vDN_S3 ) );
    }
}


/* ---- FCN_VO(tgGM_PE_Is_Contained) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_VO(tgGM_PE_Is_Contained)( VEC_OBJ_T(TgPARALLELOGRAM,CPCU) psPE0, VEC_T(1,C) vS0 )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_PE_Is_Valid)( psPE0 ) && FCN_V(tgMH_Is_Valid_Point)( vS0 ));

    {
        VEC_T(1,C)                          vDS = FCN_V(tgMH_SUB)( vS0, psPE0->m_vOrigin );

        VEC_UN_T(1,C)                       uEN0_DS = { VEC_UN_1_MEMBER() = FCN_V(tgMH_DOT)( psPE0->m_avEdge_Normal[0], vDS ) };
        VEC_UN_T(1,C)                       uEN0_E1 = { VEC_UN_1_MEMBER() = FCN_V(tgMH_DOT)( psPE0->m_avEdge_Normal[0], psPE0->m_avEdge[1] ) };

        if (VEC_S_UN_1_MEMBER(uEN0_DS).x < TYPE_K(0) || VEC_S_UN_1_MEMBER(uEN0_DS).x > VEC_S_UN_1_MEMBER(uEN0_E1).x)
        {
            return (false);
        }
        else
        {
            VEC_UN_T(1,C)                       uEN1_DS = { VEC_UN_1_MEMBER() = FCN_V(tgMH_DOT)( psPE0->m_avEdge_Normal[1], vDS ) };
            VEC_UN_T(1,C)                       uEN1_E0 = { VEC_UN_1_MEMBER() = FCN_V(tgMH_DOT)( psPE0->m_avEdge_Normal[1], psPE0->m_avEdge[0] ) };

            if (VEC_S_UN_1_MEMBER(uEN1_DS).x < TYPE_K(0) || VEC_S_UN_1_MEMBER(uEN1_DS).x > VEC_S_UN_1_MEMBER(uEN1_E0).x)
            {
                return (false);
            };

            return (true);
        };
    };
}


/* ---- FCN_VO(tgGM_PE_TX) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_PE_TX)( VEC_OBJ_T(TgPARALLELOGRAM,PCU) psPE0, VEC_T(3,CPCU) pmM0 )
{
    TgGEOM_ASSERT_PARAM(!FCN_V(tgMH_NAN,3)( pmM0 ));

    psPE0->m_avEdge[0] = FCN_V(tgMH_TX_V,3)( psPE0->m_avEdge[0], pmM0 );
    psPE0->m_avEdge[1] = FCN_V(tgMH_TX_V,3)( psPE0->m_avEdge[1], pmM0 );
    psPE0->m_vNormal = FCN_V(tgMH_TX_V,3)( psPE0->m_vNormal, pmM0 );
    psPE0->m_vOrigin = FCN_V(tgMH_TX_P,3)( psPE0->m_vOrigin, pmM0 );
    psPE0->m_avEdge_Normal[0] = FCN_V(tgMH_TX_V,3)( psPE0->m_avEdge_Normal[0], pmM0 );
    psPE0->m_avEdge_Normal[1] = FCN_V(tgMH_TX_V,3)( psPE0->m_avEdge_Normal[1], pmM0 );
}


/* ---- FCN_VO(tgGM_PE_Copy_TX) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_PE_Copy_TX)( VEC_OBJ_T(TgPARALLELOGRAM,PCU) psPE0, VEC_OBJ_T(TgPARALLELOGRAM,CPCU) psPE1, VEC_T(3,CPCU) pmM0 )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_PE_Is_Valid)( psPE1 ) && !FCN_V(tgMH_NAN,3)( pmM0 ));

    psPE0->m_avEdge[0] = FCN_V(tgMH_TX_V,3)( psPE1->m_avEdge[0], pmM0 );
    psPE0->m_avEdge[1] = FCN_V(tgMH_TX_V,3)( psPE1->m_avEdge[1], pmM0 );
    psPE0->m_vNormal = FCN_V(tgMH_TX_V,3)( psPE1->m_vNormal, pmM0 );
    psPE0->m_vOrigin = FCN_V(tgMH_TX_P,3)( psPE1->m_vOrigin, pmM0 );
    psPE0->m_avEdge_Normal[0] = FCN_V(tgMH_TX_V,3)( psPE1->m_avEdge_Normal[0], pmM0 );
    psPE0->m_avEdge_Normal[1] = FCN_V(tgMH_TX_V,3)( psPE1->m_avEdge_Normal[1], pmM0 );
}


/* ---- FCN_VO(tgGM_PE_Init) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_PE_Init)( VEC_OBJ_T(TgPARALLELOGRAM,PCU) psPE0, VEC_T(1,C) vOrigin, VEC_T(1,C) vEdge0, VEC_T(1,C) vEdge1, VEC_T(1,C) vNormal )
{
    FCN_VO(tgGM_PE_Set_Origin)( psPE0, vOrigin );
    FCN_VO(tgGM_PE_Set_Edge_Normal)( psPE0, vEdge0, vEdge1, vNormal );

    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_PE_Is_Valid)( psPE0 ));
}


/* ---- FCN_VO(tgGM_PE_Copy) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_PE_Copy)( VEC_OBJ_T(TgPARALLELOGRAM,PCU) psPE0, VEC_OBJ_T(TgPARALLELOGRAM,CPCU) psPE1 )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_PE_Is_Valid)( psPE1 ));

    psPE0->m_vOrigin = psPE1->m_vOrigin;
    psPE0->m_avEdge[0] = psPE1->m_avEdge[0];
    psPE0->m_avEdge[1] = psPE1->m_avEdge[1];
    psPE0->m_vNormal = psPE1->m_vNormal;
    psPE0->m_avEdge_Normal[0] = psPE1->m_avEdge_Normal[0];
    psPE0->m_avEdge_Normal[1] = psPE1->m_avEdge_Normal[1];
}


/* ---- FCN_VO(tgGM_PE_Set_Origin) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_PE_Set_Origin)( VEC_OBJ_T(TgPARALLELOGRAM,PCU) psPE0, VEC_T(1,C) vOrigin )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Point)( vOrigin ));
    psPE0->m_vOrigin = vOrigin;
}


/* ---- FCN_VO(tgGM_PE_Set_Edge) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_PE_Set_Edge)( VEC_OBJ_T(TgPARALLELOGRAM,PCU) psPE0, VEC_T(1,C) vEdge0, VEC_T(1,C) vEdge1 )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Vector)( vEdge0 ));

    psPE0->m_avEdge[0] = vEdge0;
    psPE0->m_avEdge[1] = vEdge1;
    psPE0->m_vNormal = FCN_V(tgMH_UCX)( vEdge0, vEdge1 );
    psPE0->m_avEdge_Normal[0] = FCN_V(tgMH_CX)( psPE0->m_vNormal, vEdge0 );
    psPE0->m_avEdge_Normal[1] = FCN_V(tgMH_CX)( vEdge1, psPE0->m_vNormal );
}


/* ---- FCN_VO(tgGM_PE_Set_Edge_Normal) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_PE_Set_Edge_Normal)( VEC_OBJ_T(TgPARALLELOGRAM,PCU) psPE0, VEC_T(1,C) vEdge0, VEC_T(1,C) vEdge1, VEC_T(1,C) vNormal )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Vector)( vEdge0 ));

    psPE0->m_avEdge[0] = vEdge0;
    psPE0->m_avEdge[1] = vEdge1;
    psPE0->m_vNormal = vNormal;
    psPE0->m_avEdge_Normal[0] = FCN_V(tgMH_CX)( vNormal, vEdge0 );
    psPE0->m_avEdge_Normal[1] = FCN_V(tgMH_CX)( vEdge1, vNormal );
}


/* ---- FCN_VO(tgGM_PE_Query_Origin) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_PE_Query_Origin)( VEC_OBJ_T(TgPARALLELOGRAM,CPCU) psPE1 )
{
    return (psPE1->m_vOrigin);
}


/* ---- FCN_VO(tgGM_PE_Query_Edge_0) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_PE_Query_Edge_0)( VEC_OBJ_T(TgPARALLELOGRAM,CPCU) psPE1 )
{
    return (psPE1->m_avEdge[0]);
}


/* ---- FCN_VO(tgGM_PE_Query_Edge_1) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_PE_Query_Edge_1)( VEC_OBJ_T(TgPARALLELOGRAM,CPCU) psPE1 )
{
    return (psPE1->m_avEdge[1]);
}


/* ---- FCN_VO(tgGM_PE_Query_Normal) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_PE_Query_Normal)( VEC_OBJ_T(TgPARALLELOGRAM,CPCU) psPE1 )
{
    return (psPE1->m_vNormal);
}


/* ---- FCN_VO(tgGM_PE_Query_Edge_Normal_0) -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_PE_Query_Edge_Normal_0)( VEC_OBJ_T(TgPARALLELOGRAM,CPCU) psPE1 )
{
    return (psPE1->m_avEdge_Normal[0]);
}


/* ---- FCN_VO(tgGM_PE_Query_Edge_Normal_1) -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_PE_Query_Edge_Normal_1)( VEC_OBJ_T(TgPARALLELOGRAM,CPCU) psPE1 )
{
    return (psPE1->m_avEdge_Normal[1]);
}


/* ---- FCN_VO(tgGM_PE_Query_Point_0) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_PE_Query_Point_0)( VEC_OBJ_T(TgPARALLELOGRAM,CPCU) psPE1 )
{
    return (psPE1->m_vOrigin);
}


/* ---- FCN_VO(tgGM_PE_Query_Point_1) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_PE_Query_Point_1)( VEC_OBJ_T(TgPARALLELOGRAM,CPCU) psPE1 )
{
    return (FCN_V(tgMH_ADD)( psPE1->m_vOrigin, psPE1->m_avEdge[0]) );
}


/* ---- FCN_VO(tgGM_PE_Query_Point_2) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_PE_Query_Point_2)( VEC_OBJ_T(TgPARALLELOGRAM,CPCU) psPE1 )
{
    return (FCN_V(tgMH_ADD)( psPE1->m_vOrigin, psPE1->m_avEdge[1]) );
}


/* ---- FCN_VO(tgGM_PE_Query_Point_3) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_PE_Query_Point_3)( VEC_OBJ_T(TgPARALLELOGRAM,CPCU) psPE1 )
{
    return (FCN_V(tgMH_ADD)( psPE1->m_vOrigin, FCN_V(tgMH_ADD)( psPE1->m_avEdge[0], psPE1->m_avEdge[1] )) );
}


/* =============================================================================================================================================================================== */
#endif
