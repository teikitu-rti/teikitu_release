/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Geometry 3D - Triangle [Point].inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_GEOMETRY_3D_TRIANGLE_POINT_INL)

#if !defined (TEMPLATE_TYPE_EXPANSION__RELOAD)
    #error Must be included as part of a type expansion include chain
#endif


/* == Common ===================================================================================================================================================================== */

/* ---- FCN_VO(tgGM_PT_Calc_Normal) ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_PT_Calc_Normal)( VEC_OBJ_T(TgPTRI,PCU) psPT0 )
{
    VEC_T(1,C)                          vX0 = FCN_V(tgMH_SUB)( psPT0->m_avPoint[1], psPT0->m_avPoint[0] );
    VEC_T(1,C)                          vX1 = FCN_V(tgMH_SUB)( psPT0->m_avPoint[2], psPT0->m_avPoint[0] );

    psPT0->m_vNormal = FCN_V(tgMH_UCX)( vX0, vX1 );
}


/* ---- FCN_VO(tgGM_PT_Reset) ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_PT_Reset)( VEC_OBJ_T(TgPTRI,PCU) psPT0 )
{
    psPT0->m_avPoint[0] = FCN_V(tgMH_Init_Point)( FCN_V(tgMH_SET1)( TYPE_K(0) ) );
    psPT0->m_avPoint[1] = FCN_V(tgMH_Init_Point)( FCN_V(tgMH_SET1)( TYPE_K(0) ) );
    psPT0->m_avPoint[2] = FCN_V(tgMH_Init_Point)( FCN_V(tgMH_SET1)( TYPE_K(0) ) );
    psPT0->m_vNormal = FCN_V(tgMH_Init_Vector)( FCN_V(tgMH_SET1)( TYPE_K(0) ) );
}


/* ---- FCN_VO(tgGM_PT_Area) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_PT_Area)( VEC_OBJ_T(TgPTRI,CPCU) psPT1 )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_PT_Is_Valid)( psPT1 ));

    {
        VEC_T(1,C)                          vX0 = FCN_V(tgMH_SUB)( psPT1->m_avPoint[1], psPT1->m_avPoint[0] );
        VEC_T(1,C)                          vX1 = FCN_V(tgMH_SUB)( psPT1->m_avPoint[2], psPT1->m_avPoint[0] );
        VEC_T(1,C)                          vX2 = FCN_V(tgMH_CX)( vX0, vX1 );
        VEC_T(1,C)                          vX3 = FCN_V(tgMH_LEN)( vX2 );
        VEC_T(1,C)                          vX4 = FCN_V(tgMH_SET1)( TYPE_K(0,5) );

        return (FCN_V(tgMH_MUL)( vX4, vX3 ));
    }
}


/* ---- FCN_VO(tgGM_PT_BA) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_PT_BA)( VEC_OBJ_T(TgBOXAA,PCU) psBA0, VEC_OBJ_T(TgPTRI,CPCU) psPT1 )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_PT_Is_Valid)( psPT1 ));

    FCN_VO(tgGM_BA_Init_PT)( psBA0, psPT1->m_avPoint[0] );
    FCN_VO(tgGM_BA_Union_PT)( psBA0, psPT1->m_avPoint[1] );
    FCN_VO(tgGM_BA_Union_PT)( psBA0, psPT1->m_avPoint[2] );
}


/* ---- FCN_VO(tgGM_PT_Sweep_BA) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_PT_Sweep_BA)( VEC_OBJ_T(TgBOXAA,PCU) psBA0, VEC_OBJ_T(TgPTRI,CPCU) psPT1, VEC_T(1,C) vDT )
{
    FCN_VO(tgGM_PT_BA)( psBA0, psPT1 );
    FCN_VO(tgGM_BA_Sweep)( psBA0, vDT );
}


/* ---- FCN_VO(tgGM_PT_Project) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_PT_Project)( VEC_T(1,PCU) pvMin, VEC_T(1,PCU) pvMax, VEC_OBJ_T(TgPTRI,CPCU) psPT1, VEC_T(1,C) vDN )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_PT_Is_Valid)( psPT1 ) && FCN_V(tgMH_Is_Valid_Unit_Vector)( vDN ));

    {
        VEC_T(1,C)                          vP0_DN = FCN_V(tgMH_DOT)( vDN, psPT1->m_avPoint[0] );
        VEC_T(1,C)                          vP1_DN = FCN_V(tgMH_DOT)( vDN, psPT1->m_avPoint[1] );
        VEC_T(1,C)                          vP2_DN = FCN_V(tgMH_DOT)( vDN, psPT1->m_avPoint[2] );

        *pvMin = FCN_V(tgMH_MIN)( FCN_V(tgMH_MIN)( vP0_DN, vP1_DN ), vP2_DN );
        *pvMax = FCN_V(tgMH_MAX)( FCN_V(tgMH_MAX)( vP0_DN, vP1_DN ), vP2_DN );
    }
}


/* ---- FCN_VO(tgGM_PT_Is_Contained) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_VO(tgGM_PT_Is_Contained)( VEC_OBJ_T(TgPTRI,CPCU) psPT1, VEC_T(1,C) vS0 )
{
    /* Note: For both the point and edge triangles a bary-centric approach is used to compute containment. This is, of course, very susceptible to floating point errors, made more
       prominent as the aspect ratio of the triangle becomes extended. Thus, if even a reasonable amount of accuracy is required for a general case triangle - create a space tri
       so that the space variation will be used (plane containment). */

    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_PT_Is_Valid)( psPT1 ) && FCN_V(tgMH_Is_Valid_Point)( vS0 ));

    {
        VEC_T(1,C)                          vS0P0 = FCN_V(tgMH_SUB)( psPT1->m_avPoint[0], vS0 );
        VEC_T(1,C)                          vS0P1 = FCN_V(tgMH_SUB)( psPT1->m_avPoint[1], vS0 );
        VEC_T(1,C)                          vS0P2 = FCN_V(tgMH_SUB)( psPT1->m_avPoint[2], vS0 );

        VEC_T(1,C)                          vX0 = FCN_V(tgMH_DOT)( vS0P0, vS0P1 );
        VEC_T(1,C)                          vX1 = FCN_V(tgMH_DOT)( vS0P0, vS0P2 );
        VEC_T(1,C)                          vX2 = FCN_V(tgMH_DOT)( vS0P1, vS0P2 );
    
        VEC_T(1,C)                          vX3 = FCN_V(tgMH_MUL)( vX2, vX1 );
        VEC_T(1,C)                          vX4 = FCN_V(tgMH_MUL)( vX0, FCN_V(tgMH_LSQ)( vS0P2 ) );
        VEC_T(1,C)                          vX5 = FCN_V(tgMH_MUL)( vX0, vX2 );
        VEC_T(1,C)                          vX6 = FCN_V(tgMH_MUL)( vX1, FCN_V(tgMH_LSQ)( vS0P1 ) );

        return (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GE)( vX3, vX4 ) ) && FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GE)( vX5, vX6 ) ));
    }
}


/* ---- FCN_VO(tgGM_PT_TX) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_PT_TX)( VEC_OBJ_T(TgPTRI,PCU) psPT0, VEC_T(3,CPCU) pmM0 )
{
    TgGEOM_ASSERT_PARAM(!FCN_V(tgMH_NAN,3)( pmM0 ));

    psPT0->m_avPoint[0] = FCN_V(tgMH_TX_P,3)( psPT0->m_avPoint[0], pmM0 );
    psPT0->m_avPoint[1] = FCN_V(tgMH_TX_P,3)( psPT0->m_avPoint[1], pmM0 );
    psPT0->m_avPoint[2] = FCN_V(tgMH_TX_P,3)( psPT0->m_avPoint[2], pmM0 );
    psPT0->m_vNormal = FCN_V(tgMH_TX_V,3)( psPT0->m_vNormal, pmM0 );
}


/* ---- FCN_VO(tgGM_PT_Copy_TX) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_PT_Copy_TX)( VEC_OBJ_T(TgPTRI,PCU) psPT0, VEC_OBJ_T(TgPTRI,CPCU) psPT1, VEC_T(3,CPCU) pmM0 )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_PT_Is_Valid)( psPT1 ) && !FCN_V(tgMH_NAN,3)( pmM0 ));

    psPT0->m_avPoint[0] = FCN_V(tgMH_TX_P,3)( psPT1->m_avPoint[0], pmM0 );
    psPT0->m_avPoint[1] = FCN_V(tgMH_TX_P,3)( psPT1->m_avPoint[1], pmM0 );
    psPT0->m_avPoint[2] = FCN_V(tgMH_TX_P,3)( psPT1->m_avPoint[2], pmM0 );
    psPT0->m_vNormal = FCN_V(tgMH_TX_V,3)( psPT1->m_vNormal, pmM0 );
}


/* ---- FCN_VO(tgGM_PT_Init_PN) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_PT_Init_PN)( VEC_OBJ_T(TgPTRI,PCU) psPT0, VEC_T(1,C) vS0, VEC_T(1,C) vS1, VEC_T(1,C) vS2, VEC_T(1,C) vN )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Point)( vS0 ));
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Point)( vS1 ));
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Point)( vS2 ));
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Unit_Vector)( vN ));

    psPT0->m_avPoint[0] = vS0;
    psPT0->m_avPoint[1] = vS1;
    psPT0->m_avPoint[2] = vS2;
    psPT0->m_vNormal = vN;
}


/* ---- FCN_VO(tgGM_PT_Init_P) --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_PT_Init_P)( VEC_OBJ_T(TgPTRI,PCU) psPT0, VEC_T(1,C) vS0, VEC_T(1,C) vS1, VEC_T(1,C) vS2 )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Point)( vS0 ));
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Point)( vS1 ));
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Point)( vS2 ));

    psPT0->m_avPoint[0] = vS0;
    psPT0->m_avPoint[1] = vS1;
    psPT0->m_avPoint[2] = vS2;
    FCN_VO(tgGM_PT_Calc_Normal)( psPT0 );
}


/* ---- FCN_VO(tgGM_PT_Copy) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_PT_Copy)( VEC_OBJ_T(TgPTRI,PCU) psPT0, VEC_OBJ_T(TgPTRI,CPCU) psPT1 )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_PT_Is_Valid)( psPT1 ));

    psPT0->m_avPoint[0] = psPT1->m_avPoint[0];
    psPT0->m_avPoint[1] = psPT1->m_avPoint[1];
    psPT0->m_avPoint[2] = psPT1->m_avPoint[2];
    psPT0->m_vNormal = psPT1->m_vNormal;
}


/* ---- FCN_VO(tgGM_PT_Set_Origin) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_PT_Set_Origin)( VEC_OBJ_T(TgPTRI,PCU) psPT0, VEC_T(1,C) vS0 )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Point)( vS0 ));

    psPT0->m_avPoint[0] = vS0;
    FCN_VO(tgGM_PT_Calc_Normal)( psPT0 );
}


/* ---- FCN_VO(tgGM_PT_Set_Point_0) ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_PT_Set_Point_0)( VEC_OBJ_T(TgPTRI,PCU) psPT0, VEC_T(1,C) vS0 )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Point)( vS0 ));

    psPT0->m_avPoint[0] = vS0;
    FCN_VO(tgGM_PT_Calc_Normal)( psPT0 );
}


/* ---- FCN_VO(tgGM_PT_Set_Point_1) ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_PT_Set_Point_1)( VEC_OBJ_T(TgPTRI,PCU) psPT0, VEC_T(1,C) vS0 )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Point)( vS0 ));

    psPT0->m_avPoint[1] = vS0;
    FCN_VO(tgGM_PT_Calc_Normal)( psPT0 );
}


/* ---- FCN_VO(tgGM_PT_Set_Point_2) ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_PT_Set_Point_2)( VEC_OBJ_T(TgPTRI,PCU) psPT0, VEC_T(1,C) vS0 )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Point)( vS0 ));

    psPT0->m_avPoint[2] = vS0;
    FCN_VO(tgGM_PT_Calc_Normal)( psPT0 );
}


/* ---- FCN_VO(tgGM_PT_Query_Origin) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_PT_Query_Origin)( VEC_OBJ_T(TgPTRI,CPCU) psPT1 )
{
    return (psPT1->m_avPoint[0]);
}


/* ---- FCN_VO(tgGM_PT_Query_Normal) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_PT_Query_Normal)( VEC_OBJ_T(TgPTRI,CPCU) psPT1 )
{
    return (psPT1->m_vNormal);
}


/* ---- FCN_VO(tgGM_PT_Query_Point_0) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_PT_Query_Point_0)( VEC_OBJ_T(TgPTRI,CPCU) psPT1 )
{
    return (psPT1->m_avPoint[0]);
}


/* ---- FCN_VO(tgGM_PT_Query_Point_1) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_PT_Query_Point_1)( VEC_OBJ_T(TgPTRI,CPCU) psPT1 )
{
    return (psPT1->m_avPoint[1]);
}


/* ---- FCN_VO(tgGM_PT_Query_Point_2) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_PT_Query_Point_2)( VEC_OBJ_T(TgPTRI,CPCU) psPT1 )
{
    return (psPT1->m_avPoint[2]);
}


/* ---- FCN_VO(tgGM_PT_Query_Point) ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_PT_Query_Point)( VEC_OBJ_T(TgPTRI,CPCU) psPT1, TgRSIZE_C uiIndex )
{
    TgGEOM_ASSERT_PARAM(uiIndex <= 2);
    return (psPT1->m_avPoint[uiIndex]);
}


/* =============================================================================================================================================================================== */
#endif
