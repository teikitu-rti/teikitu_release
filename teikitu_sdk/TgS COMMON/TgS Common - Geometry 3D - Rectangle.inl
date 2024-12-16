/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Geometry 3D - Rectangle.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_GEOMETRY_3D_RECTANGLE_INL)

#if !defined (TEMPLATE_TYPE_EXPANSION__RELOAD)
    #error Must be included as part of a type expansion include chain
#endif


/* == Common ===================================================================================================================================================================== */

/* ---- FCN_VO(tgGM_RT_Reset) ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_RT_Reset)( VEC_OBJ_T(TgRECTANGLE,PCU) psRT0 )
{
    psRT0->m_vOrigin = FCN_V(tgMH_Init_Point)( FCN_V(tgMH_SET1)( TYPE_K(0) ) );
    psRT0->m_avEdge[0] = FCN_V(tgMH_Init_Vector)( FCN_V(tgMH_SET1)( TYPE_K(0) ) );
    psRT0->m_avEdge[1] = FCN_V(tgMH_Init_Vector)( FCN_V(tgMH_SET1)( TYPE_K(0) ) );
    psRT0->m_vNormal = FCN_V(tgMH_Init_Vector)( FCN_V(tgMH_SET1)( TYPE_K(0) ) );
}


/* ---- FCN_VO(tgGM_RT_Is_Valid) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_VO(tgGM_RT_Is_Valid)( VEC_OBJ_T(TgRECTANGLE,CPCU) psRT0 )
{
    if (!FCN_V(tgMH_Is_Valid_Point)( psRT0->m_vOrigin ))
    {
        return (false);
    };

    if (!FCN_V(tgMH_Is_Valid_Vector)( psRT0->m_avEdge[0] ) || FCN_V(tgMH_Is_PRX_CMP_EQ)( psRT0->m_avEdge[0], FCN_V(tgMH_SET1)( TYPE_K(0) ) ))
    {
        return (false);
    };

    if (!FCN_V(tgMH_Is_Valid_Vector)( psRT0->m_avEdge[1] ) || FCN_V(tgMH_Is_PRX_CMP_EQ)( psRT0->m_avEdge[1], FCN_V(tgMH_SET1)( TYPE_K(0) ) ))
    {
        return (false);
    };

    if (!FCN_V(tgMH_Is_Valid_Unit_Vector)( psRT0->m_vNormal ))
    {
        return (false);
    };

    if (!FCN_V(tgMH_Is_PRX_CMP_EQ)( FCN_V(tgMH_DOT)( psRT0->m_avEdge[0], psRT0->m_avEdge[1] ), FCN_V(tgMH_SET1)( TYPE_K(0) ) ))
    {
        return (false);
    };

    if (!FCN_V(tgMH_Is_PRX_CMP_EQ)( FCN_V(tgMH_DOT)( psRT0->m_avEdge[0], psRT0->m_vNormal ), FCN_V(tgMH_SET1)( TYPE_K(0) ) ))
    {
        return (false);
    };

    if (!FCN_V(tgMH_Is_PRX_CMP_EQ)( FCN_V(tgMH_DOT)( psRT0->m_avEdge[1], psRT0->m_vNormal ), FCN_V(tgMH_SET1)( TYPE_K(0) ) ))
    {
        return (false);
    };

    return (true);
}


/* ---- FCN_VO(tgGM_RT_Support_Point) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_RT_Support_Point)( VEC_OBJ_T(TgRECTANGLE,CPCU) psRT0, VEC_T(1,C) vDN )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_RT_Is_Valid)( psRT0 ) && FCN_V(tgMH_Is_Valid_Unit_Vector)( vDN ));

    {
        VEC_T(1,C)                          vDN_E0 = FCN_V(tgMH_DOT)( vDN, psRT0->m_avEdge[0] );
        VEC_T(1,C)                          vX0 = FCN_V(tgMH_SGN)( vDN_E0 );
        VEC_T(1,C)                          vX1 = FCN_V(tgMH_MUL)( vX0, psRT0->m_avEdge[0] );
        VEC_T(1,C)                          vX2 = FCN_V(tgMH_MAX)( vX1, FCN_V(tgMH_SET1)( TYPE_K(0) ) );

        VEC_T(1,C)                          vDN_E1 = FCN_V(tgMH_DOT)( vDN, psRT0->m_avEdge[1] );
        VEC_T(1,C)                          vX3 = FCN_V(tgMH_SGN)( vDN_E1 );
        VEC_T(1,C)                          vX4 = FCN_V(tgMH_MUL)( vX3, psRT0->m_avEdge[1] );
        VEC_T(1,C)                          vX5 = FCN_V(tgMH_MAX)( vX4, FCN_V(tgMH_SET1)( TYPE_K(0) ) );

        VEC_T(1,C)                          vX6 = FCN_V(tgMH_ADD)( vX2, vX5 );

        return (FCN_V(tgMH_ADD)( psRT0->m_vOrigin, vX6 ) );
    }
}


/* ---- FCN_VO(tgGM_RT_Area) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_RT_Area)( VEC_OBJ_T(TgRECTANGLE,CPCU) psRT0 )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_RT_Is_Valid)( psRT0 ));

    {
        VEC_T(1,C)                          vX0 = FCN_V(tgMH_CX)( psRT0->m_avEdge[0], psRT0->m_avEdge[1] );

        return (FCN_V(tgMH_LEN)( vX0 ));
    }
}


/* ---- FCN_VO(tgGM_RT_BA) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_RT_BA)( VEC_OBJ_T(TgBOXAA,PCU) psBA0, VEC_OBJ_T(TgRECTANGLE,CPCU) psRT1 )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_RT_Is_Valid)( psRT1 ));

    {
        VEC_T(1,C)                          vX0 = FCN_V(tgMH_ADD)( psRT1->m_vOrigin, psRT1->m_avEdge[0] );
        VEC_T(1,C)                          vX1 = FCN_V(tgMH_ADD)( psRT1->m_vOrigin, psRT1->m_avEdge[1] );
        VEC_T(1,C)                          vX2 = FCN_V(tgMH_ADD)( psRT1->m_avEdge[0], psRT1->m_avEdge[1] );
        VEC_T(1,C)                          vX3 = FCN_V(tgMH_ADD)( psRT1->m_vOrigin, vX2 );

        FCN_VO(tgGM_BA_Init_PT)( psBA0, psRT1->m_vOrigin );
        FCN_VO(tgGM_BA_Union_PT)( psBA0, vX0 );
        FCN_VO(tgGM_BA_Union_PT)( psBA0, vX1 );
        FCN_VO(tgGM_BA_Union_PT)( psBA0, vX3 );
    }
}


/* ---- FCN_VO(tgGM_RT_Sweep_BA) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_RT_Sweep_BA)( VEC_OBJ_T(TgBOXAA,PCU) psBA0, VEC_OBJ_T(TgRECTANGLE,CPCU) psRT0, VEC_T(1,C) vDT )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_RT_Is_Valid)( psRT0 ) && FCN_V(tgMH_Is_Valid_Vector)( vDT ));

    FCN_VO(tgGM_RT_BA)( psBA0, psRT0 );
    FCN_VO(tgGM_BA_Sweep)( psBA0, vDT );
}


/* ---- FCN_VO(tgGM_RT_Project) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_RT_Project)( VEC_T(1,PCU) pvMin, VEC_T(1,PCU) pvMax, VEC_OBJ_T(TgRECTANGLE,CPCU) psRT0, VEC_T(1,C) vDN )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_RT_Is_Valid)( psRT0 ) && FCN_V(tgMH_Is_Valid_Unit_Vector)( vDN ));

    {
        VEC_T(1,C)                          vDN_E0 = FCN_V(tgMH_DOT)( vDN, psRT0->m_avEdge[0] );
        VEC_T(1,C)                          vDN_E1 = FCN_V(tgMH_DOT)( vDN, psRT0->m_avEdge[1] );

        VEC_T(1,C)                          vDN_S0 = FCN_V(tgMH_DOT)( vDN, psRT0->m_vOrigin );
        VEC_T(1,C)                          vDN_S1 = FCN_V(tgMH_ADD)( vDN_S0, vDN_E0 );
        VEC_T(1,C)                          vDN_S2 = FCN_V(tgMH_ADD)( vDN_S0, vDN_E1 );
        VEC_T(1,C)                          vDN_S3 = FCN_V(tgMH_ADD)( vDN_S1, vDN_E1 );

        *pvMin = FCN_V(tgMH_MIN)( FCN_V(tgMH_MIN)( vDN_S0, vDN_S1 ), FCN_V(tgMH_MIN)( vDN_S2, vDN_S3 ) );
        *pvMax = FCN_V(tgMH_MAX)( FCN_V(tgMH_MAX)( vDN_S0, vDN_S1 ), FCN_V(tgMH_MAX)( vDN_S2, vDN_S3 ) );
    }
}


/* ---- FCN_VO(tgGM_RT_Is_Contained) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_VO(tgGM_RT_Is_Contained)( VEC_OBJ_T(TgRECTANGLE,CPCU) psRT0, VEC_T(1,C) vS0 )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_RT_Is_Valid)( psRT0 ) && FCN_V(tgMH_Is_Valid_Point)( vS0 ));

    {
        VEC_T(1,C)                          vDS = FCN_V(tgMH_SUB)( vS0, psRT0->m_vOrigin );

        VEC_UN_T(1,C)                       uDS_E0 = { VEC_UN_1_MEMBER() = FCN_V(tgMH_DOT)( vDS, psRT0->m_avEdge[0] ) };
        VEC_UN_T(1,C)                       uE0_E0 = { VEC_UN_1_MEMBER() = FCN_V(tgMH_LSQ)( psRT0->m_avEdge[0] ) };

        if (VEC_S_UN_1_MEMBER(uDS_E0).x < TYPE_K(0) || VEC_S_UN_1_MEMBER(uDS_E0).x > VEC_S_UN_1_MEMBER(uE0_E0).x)
        {
            return (false);
        }
        else
        {
            VEC_UN_T(1,C)                       uDS_E1 = { VEC_UN_1_MEMBER() = FCN_V(tgMH_DOT)( vDS, psRT0->m_avEdge[1] ) };
            VEC_UN_T(1,C)                       uE1_E1 = { VEC_UN_1_MEMBER() = FCN_V(tgMH_LSQ)( psRT0->m_avEdge[1] ) };

            if (VEC_S_UN_1_MEMBER(uDS_E1).x < TYPE_K(0) || VEC_S_UN_1_MEMBER(uDS_E1).x > VEC_S_UN_1_MEMBER(uE1_E1).x)
            {
                return (false);
            };

            return (true);
        };
    };
}


/* ---- FCN_VO(tgGM_RT_TX) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_RT_TX)( VEC_OBJ_T(TgRECTANGLE,PCU) psRT0, VEC_T(3,CPCU) pmM0 )
{
    TgGEOM_ASSERT_PARAM(!FCN_V(tgMH_NAN,3)( pmM0 ));

    psRT0->m_avEdge[0] = FCN_V(tgMH_TX_V,3)( psRT0->m_avEdge[0], pmM0 );
    psRT0->m_avEdge[1] = FCN_V(tgMH_TX_V,3)( psRT0->m_avEdge[1], pmM0 );
    psRT0->m_vNormal = FCN_V(tgMH_TX_V,3)( psRT0->m_vNormal, pmM0 );
    psRT0->m_vOrigin = FCN_V(tgMH_TX_P,3)( psRT0->m_vOrigin, pmM0 );
}


/* ---- FCN_VO(tgGM_RT_Copy_TX) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_RT_Copy_TX)( VEC_OBJ_T(TgRECTANGLE,PCU) psRT0, VEC_OBJ_T(TgRECTANGLE,CPCU) psRT1, VEC_T(3,CPCU) pmM0 )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_RT_Is_Valid)( psRT1 ) && !FCN_V(tgMH_NAN,3)( pmM0 ));

    psRT0->m_avEdge[0] = FCN_V(tgMH_TX_V,3)( psRT1->m_avEdge[0], pmM0 );
    psRT0->m_avEdge[1] = FCN_V(tgMH_TX_V,3)( psRT1->m_avEdge[1], pmM0 );
    psRT0->m_vNormal = FCN_V(tgMH_TX_V,3)( psRT1->m_vNormal, pmM0 );
    psRT0->m_vOrigin = FCN_V(tgMH_TX_P,3)( psRT1->m_vOrigin, pmM0 );
}


/* ---- FCN_VO(tgGM_RT_Init_SEN) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_RT_Init_SEN)( VEC_OBJ_T(TgRECTANGLE,PCU) psRT0, VEC_T(1,C) vOrigin, VEC_T(1,C) vEdge0, VEC_T(1,C) vEdge1, VEC_T(1,C) vNormal )
{
    FCN_VO(tgGM_RT_Set_Origin)( psRT0, vOrigin );
    FCN_VO(tgGM_RT_Set_Edge_Normal)( psRT0, vEdge0, vEdge1, vNormal );
}


/* ---- FCN_VO(tgGM_RT_Init_SE) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_RT_Init_SE)( VEC_OBJ_T(TgRECTANGLE,PCU) psRT0, VEC_T(1,C) vOrigin, VEC_T(1,C) vEdge0, VEC_T(1,C) vEdge1 )
{
    FCN_VO(tgGM_RT_Set_Origin)( psRT0, vOrigin );
    FCN_VO(tgGM_RT_Set_Edge)( psRT0, vEdge0, vEdge1 );
}


/* ---- FCN_VO(tgGM_RT_Copy) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_RT_Copy)( VEC_OBJ_T(TgRECTANGLE,PCU) psRT0, VEC_OBJ_T(TgRECTANGLE,CPCU) psRT1 )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_RT_Is_Valid)( psRT1 ));
    tgMM_Copy( psRT0, sizeof( VEC_OBJ_T(TgRECTANGLE) ), psRT1, sizeof( VEC_OBJ_T(TgRECTANGLE) ) );
}


/* ---- FCN_VO(tgGM_RT_Set_Origin) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_RT_Set_Origin)( VEC_OBJ_T(TgRECTANGLE,PCU) psRT0, VEC_T(1,C) vOrigin )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Point)( vOrigin ));
    psRT0->m_vOrigin = vOrigin;
}


/* ---- FCN_VO(tgGM_RT_Set_Edge) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_RT_Set_Edge)( VEC_OBJ_T(TgRECTANGLE,PCU) psRT0, VEC_T(1,C) vEdge0, VEC_T(1,C) vEdge1 )
{
    psRT0->m_avEdge[0] = vEdge0;
    psRT0->m_avEdge[1] = vEdge1;
    psRT0->m_vNormal = FCN_V(tgMH_UCX)( vEdge0, vEdge1 );
    
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_RT_Is_Valid)( psRT0 ));
}


/* ---- FCN_VO(tgGM_RT_Set_Edge_Normal) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_RT_Set_Edge_Normal)( VEC_OBJ_T(TgRECTANGLE,PCU) psRT0, VEC_T(1,C) vEdge0, VEC_T(1,C) vEdge1, VEC_T(1,C) vNormal )
{
    psRT0->m_avEdge[0] = vEdge0;
    psRT0->m_avEdge[1] = vEdge1;
    psRT0->m_vNormal = vNormal;

    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_RT_Is_Valid)( psRT0 ));
}


/* ---- FCN_VO(tgGM_RT_Query_Origin) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_RT_Query_Origin)( VEC_OBJ_T(TgRECTANGLE,CPCU) psRT1 )
{
    return (psRT1->m_vOrigin);
}


/* ---- FCN_VO(tgGM_RT_Query_Edge_0) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_RT_Query_Edge_0)( VEC_OBJ_T(TgRECTANGLE,CPCU) psRT1 )
{
    return (psRT1->m_avEdge[0]);
}


/* ---- FCN_VO(tgGM_RT_Query_Edge_1) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_RT_Query_Edge_1)( VEC_OBJ_T(TgRECTANGLE,CPCU) psRT1 )
{
    return (psRT1->m_avEdge[1]);
}


/* ---- FCN_VO(tgGM_RT_Query_Normal) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_RT_Query_Normal)( VEC_OBJ_T(TgRECTANGLE,CPCU) psRT1 )
{
    return (psRT1->m_vNormal);
}


/* ---- FCN_VO(tgGM_RT_Query_Point_0) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_RT_Query_Point_0)( VEC_OBJ_T(TgRECTANGLE,CPCU) psRT1 )
{
    return (psRT1->m_vOrigin);
}


/* ---- FCN_VO(tgGM_RT_Query_Point_1) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_RT_Query_Point_1)( VEC_OBJ_T(TgRECTANGLE,CPCU) psRT1 )
{
    return (FCN_V(tgMH_ADD)( psRT1->m_vOrigin, psRT1->m_avEdge[0]) );
}


/* ---- FCN_VO(tgGM_RT_Query_Point_2) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_RT_Query_Point_2)( VEC_OBJ_T(TgRECTANGLE,CPCU) psRT1 )
{
    return (FCN_V(tgMH_ADD)( psRT1->m_vOrigin, psRT1->m_avEdge[1]) );
}


/* ---- FCN_VO(tgGM_RT_Query_Point_3) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_RT_Query_Point_3)( VEC_OBJ_T(TgRECTANGLE,CPCU) psRT1 )
{
    VEC_T(1,C)                          vX0 = FCN_V(tgMH_ADD)( psRT1->m_avEdge[0], psRT1->m_avEdge[1] );

    return (FCN_V(tgMH_ADD)( psRT1->m_vOrigin, vX0) );
}


/* =============================================================================================================================================================================== */
#endif
