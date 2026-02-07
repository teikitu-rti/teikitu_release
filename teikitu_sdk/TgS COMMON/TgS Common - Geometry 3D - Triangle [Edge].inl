/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Geometry 3D - Triangle [Edge].inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_GEOMETRY_3D_TRIANGLE_EDGE_INL)

#if !defined (TEMPLATE_TYPE_EXPANSION__RELOAD)
    #error Must be included as part of a type expansion include chain
#endif


/* == Common ===================================================================================================================================================================== */

/* ---- FCN_VO(tgGM_ET_Calc_Normal) ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_ET_Calc_Normal)( VEC_OBJ_T(TgETRI,PCU) psET0 )
{
    VEC_T(1,C)                          vX0 = FCN_V(tgMH_NEG)( psET0->m_avEdge[2] );

    psET0->m_sPT.m_vNormal = FCN_V(tgMH_UCX)( psET0->m_avEdge[0], vX0 );
}


/* ---- FCN_VO(tgGM_ET_Calc_Point) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_ET_Calc_Point)( VEC_OBJ_T(TgETRI,CPCU) psET1, VEC_T(1,C) vT0, VEC_T(1,C) vT1 )
{
    //TgGEOM_ASSERT_PARAM((fT0 > TYPE_K(0)) && (fT1 > TYPE_K(0)));
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_ET_Is_Valid)( psET1 ));

    {
        VEC_T(1,C)                          vX0 = FCN_V(tgMH_NMS)( vT1, psET1->m_avEdge[2], psET1->m_sPT.m_avPoint[0] );

        return (FCN_V(tgMH_NMS)( vT0, psET1->m_avEdge[0], vX0 ));
    }
}


/* ---- FCN_VO(tgGM_ET_Reset) ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_ET_Reset)( VEC_OBJ_T(TgETRI,PCU) psET0 )
{
    FCN_VO(tgGM_PT_Reset)( &psET0->m_sPT );

    psET0->m_avEdge[0] = FCN_V(tgMH_Init_Vector)( FCN_V(tgMH_SET1)( TYPE_K(0) ) );
    psET0->m_avEdge[1] = FCN_V(tgMH_Init_Vector)( FCN_V(tgMH_SET1)( TYPE_K(0) ) );
    psET0->m_avEdge[2] = FCN_V(tgMH_Init_Vector)( FCN_V(tgMH_SET1)( TYPE_K(0) ) );
}


/* ---- FCN_VO(tgGM_ET_Area) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_ET_Area)( VEC_OBJ_T(TgETRI,CPCU) psET1 )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_ET_Is_Valid)( psET1 ));

    {
        VEC_T(1,C)                          vX0 = FCN_V(tgMH_CX)( psET1->m_avEdge[0], psET1->m_avEdge[2] );
        VEC_T(1,C)                          vX1 = FCN_V(tgMH_LEN)( vX0 );
        VEC_T(1,C)                          vX2 = FCN_V(tgMH_SET1)( TYPE_K(0,5) );

        return (FCN_V(tgMH_MUL)( vX1, vX2 ));
    }
}


/* ---- FCN_VO(tgGM_ET_BA) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_ET_BA)( VEC_OBJ_T(TgBOXAA,PCU) psBA0, VEC_OBJ_T(TgETRI,CPCU) psET1 )
{
    FCN_VO(tgGM_PT_BA)( psBA0, &psET1->m_sPT );
}


/* ---- FCN_VO(tgGM_ET_Sweep_BA) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_ET_Sweep_BA)( VEC_OBJ_T(TgBOXAA,PCU) psBA0, VEC_OBJ_T(TgETRI,CPCU) psET1, VEC_T(1,C) vDT )
{
    FCN_VO(tgGM_ET_BA)( psBA0, psET1 );
    FCN_VO(tgGM_BA_Sweep)( psBA0, vDT );
}


/* ---- FCN_VO(tgGM_ET_Project) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_ET_Project)( VEC_T(1,PCU) pvMin, VEC_T(1,PCU) pvMax, VEC_OBJ_T(TgETRI,CPCU) psET1, VEC_T(1,C) vDN )
{
    FCN_VO(tgGM_PT_Project)( pvMin, pvMax, &psET1->m_sPT, vDN );
}


/* ---- FCN_VO(tgGM_ET_Is_Contained) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_VO(tgGM_ET_Is_Contained)( VEC_OBJ_T(TgETRI,CPCU) psET1, VEC_T(1,C) vS0 )
{
    VEC_T(1,C)                          vDS = FCN_V(tgMH_SUB)( vS0, psET1->m_sPT.m_avPoint[0] );
    VEC_T(1,C)                          vN0 = FCN_V(tgMH_CX)( psET1->m_sPT.m_vNormal, psET1->m_avEdge[0] );
    VEC_T(1,C)                          vX0 = FCN_V(tgMH_DOT)( vDS, vN0 );

    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vX0, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ))
    {
        return (false);
    }
    else
    {
        VEC_T(1,C)                          vN2 = FCN_V(tgMH_CX)( psET1->m_sPT.m_vNormal, psET1->m_avEdge[2] );
        VEC_T(1,C)                          vX1 = FCN_V(tgMH_DOT)( vDS, vN2 );

        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vX1, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ))
        {
            return (false);
        }
        else
        {
            VEC_T(1,C)                          vN1 = FCN_V(tgMH_CX)( psET1->m_sPT.m_vNormal, psET1->m_avEdge[1] );
            VEC_T(1,C)                          vX2 = FCN_V(tgMH_SUB)( vDS, psET1->m_avEdge[0] );
            VEC_T(1,C)                          vX3 = FCN_V(tgMH_DOT)( vX2, vN1 );

            if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vX3, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ))
            {
                return (false);
            };

            return (true);
        };
    };
}


/* ---- FCN_VO(tgGM_ET_TX) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_ET_TX)( VEC_OBJ_T(TgETRI,PCU) psET0, VEC_T(3,CPCU) pmM0 )
{
    FCN_VO(tgGM_PT_TX)( &psET0->m_sPT, pmM0 );
    psET0->m_avEdge[0] = FCN_V(tgMH_TX_V,3)( psET0->m_avEdge[0], pmM0 );
    psET0->m_avEdge[1] = FCN_V(tgMH_TX_V,3)( psET0->m_avEdge[1], pmM0 );
    psET0->m_avEdge[2] = FCN_V(tgMH_TX_V,3)( psET0->m_avEdge[2], pmM0 );
}


/* ---- FCN_VO(tgGM_ET_Copy_TX) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_ET_Copy_TX)( VEC_OBJ_T(TgETRI,PCU) psET0, VEC_OBJ_T(TgETRI,CPCU) psET1, VEC_T(3,CPCU) pmM0 )
{
    FCN_VO(tgGM_PT_Copy_TX)( &psET0->m_sPT, &psET1->m_sPT, pmM0 );
    psET0->m_avEdge[0] = FCN_V(tgMH_TX_V,3)( psET1->m_avEdge[0], pmM0 );
    psET0->m_avEdge[1] = FCN_V(tgMH_TX_V,3)( psET1->m_avEdge[1], pmM0 );
    psET0->m_avEdge[2] = FCN_V(tgMH_TX_V,3)( psET1->m_avEdge[2], pmM0 );
}


/* ---- FCN_VO(tgGM_ET_Init_PN) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_ET_Init_PN)( VEC_OBJ_T(TgETRI,PCU) psET0, VEC_T(1,C) vS0, VEC_T(1,C) vS1, VEC_T(1,C) vS2, VEC_T(1,C) vN )
{
    FCN_VO(tgGM_PT_Init_PN)( &psET0->m_sPT, vS0, vS1, vS2, vN );
    psET0->m_avEdge[0] = FCN_V(tgMH_SUB)( vS1, vS0 );
    psET0->m_avEdge[1] = FCN_V(tgMH_SUB)( vS2, vS1 );
    psET0->m_avEdge[2] = FCN_V(tgMH_SUB)( vS0, vS2 );
}


/* ---- FCN_VO(tgGM_ET_Init_P) --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_ET_Init_P)( VEC_OBJ_T(TgETRI,PCU) psET0, VEC_T(1,C) vS0, VEC_T(1,C) vS1, VEC_T(1,C) vS2 )
{
    FCN_VO(tgGM_PT_Init_P)( &psET0->m_sPT, vS0, vS1, vS2 );
    psET0->m_avEdge[0] = FCN_V(tgMH_SUB)( vS1, vS0 );
    psET0->m_avEdge[1] = FCN_V(tgMH_SUB)( vS2, vS1 );
    psET0->m_avEdge[2] = FCN_V(tgMH_SUB)( vS0, vS2 );
    FCN_VO(tgGM_ET_Calc_Normal)( psET0 );
}


/* ---- FCN_VO(tgGM_ET_Init_EN) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_ET_Init_EN)(  VEC_OBJ_T(TgETRI,PCU) psET0, VEC_T(1,C) vS0, VEC_T(1,C) vE0, VEC_T(1,C) vE1, VEC_T(1,C) vN )
{
    VEC_T(1,C)                          vX1 = FCN_V(tgMH_ADD)( vS0, vE0 );
    VEC_T(1,C)                          vX2 = FCN_V(tgMH_ADD)( vS0, vE1 );

    FCN_VO(tgGM_PT_Init_PN)( &psET0->m_sPT, vS0, vX1, vX2, vN );
    psET0->m_avEdge[0] = vE0;
    psET0->m_avEdge[1] = FCN_V(tgMH_SUB)( vE1, vE0 );
    psET0->m_avEdge[2] = FCN_V(tgMH_NEG)( vE1 );
}


/* ---- FCN_VO(tgGM_ET_Init_E) --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_ET_Init_E)( VEC_OBJ_T(TgETRI,PCU) psET0, VEC_T(1,C) vS0, VEC_T(1,C) vE0, VEC_T(1,C) vE1 )
{
    VEC_T(1,C)                          vX1 = FCN_V(tgMH_ADD)( vS0, vE0 );
    VEC_T(1,C)                          vX2 = FCN_V(tgMH_ADD)( vS0, vE1 );

    FCN_VO(tgGM_PT_Init_P)( &psET0->m_sPT, vS0, vX1, vX2 );
    psET0->m_avEdge[0] = vE0;
    psET0->m_avEdge[1] = FCN_V(tgMH_SUB)( vE1, vE0 );
    psET0->m_avEdge[2] = FCN_V(tgMH_NEG)( vE1 );
}


/* ---- FCN_VO(tgGM_ET_Init_PT) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_ET_Init_PT)( VEC_OBJ_T(TgETRI,PCU) psET0, VEC_OBJ_T(TgPTRI,CPCU) psPT1 )
{
    FCN_VO(tgGM_ET_Init_PN)( psET0, psPT1->m_avPoint[0], psPT1->m_avPoint[1], psPT1->m_avPoint[2], psPT1->m_vNormal );
}


/* ---- FCN_VO(tgGM_ET_Copy) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_ET_Copy)( VEC_OBJ_T(TgETRI,PCU) psET0, VEC_OBJ_T(TgETRI,CPCU) psET1 )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_ET_Is_Valid)( psET1 ));

    FCN_VO(tgGM_PT_Copy)( &psET0->m_sPT, &psET1->m_sPT );
    psET0->m_avEdge[0] = psET1->m_avEdge[0];
    psET0->m_avEdge[1] = psET1->m_avEdge[1];
    psET0->m_avEdge[2] = psET1->m_avEdge[2];
}


/* ---- FCN_VO(tgGM_ET_Set_Origin) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_ET_Set_Origin)( VEC_OBJ_T(TgETRI,PCU) psET0, VEC_T(1,C) vS0 )
{
    FCN_VO(tgGM_PT_Set_Origin)( &psET0->m_sPT, vS0 );
    psET0->m_avEdge[0] = FCN_V(tgMH_SUB)( psET0->m_sPT.m_avPoint[1], vS0 );
    psET0->m_avEdge[2] = FCN_V(tgMH_SUB)( vS0, psET0->m_sPT.m_avPoint[2] );
}


/* ---- FCN_VO(tgGM_ET_Set_Point_0) ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_ET_Set_Point_0)( VEC_OBJ_T(TgETRI,PCU) psET0, VEC_T(1,C) vS0 )
{
    FCN_VO(tgGM_PT_Set_Point_0)( &psET0->m_sPT, vS0 );
    psET0->m_avEdge[0] = FCN_V(tgMH_SUB)( psET0->m_sPT.m_avPoint[1], vS0 );
    psET0->m_avEdge[2] = FCN_V(tgMH_SUB)( vS0, psET0->m_sPT.m_avPoint[2] );
}


/* ---- FCN_VO(tgGM_ET_Set_Point_1) ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_ET_Set_Point_1)( VEC_OBJ_T(TgETRI,PCU) psET0, VEC_T(1,C) vS1 )
{
    FCN_VO(tgGM_PT_Set_Point_1)( &psET0->m_sPT, vS1 );
    psET0->m_avEdge[0] = FCN_V(tgMH_SUB)( vS1, psET0->m_sPT.m_avPoint[0] );
    psET0->m_avEdge[1] = FCN_V(tgMH_SUB)( psET0->m_sPT.m_avPoint[2], vS1 );
}


/* ---- FCN_VO(tgGM_ET_Set_Point_2) ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_ET_Set_Point_2)( VEC_OBJ_T(TgETRI,PCU) psET0, VEC_T(1,C) vS2 )
{
    FCN_VO(tgGM_PT_Set_Point_2)( &psET0->m_sPT, vS2 );
    psET0->m_avEdge[1] = FCN_V(tgMH_SUB)( vS2, psET0->m_sPT.m_avPoint[1] );
    psET0->m_avEdge[2] = FCN_V(tgMH_SUB)( psET0->m_sPT.m_avPoint[0], vS2 );
}


/* ---- FCN_VO(tgGM_ET_Set_Edge_0) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_ET_Set_Edge_0)( VEC_OBJ_T(TgETRI,PCU) psET0, VEC_T(1,C) vE0 )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Vector)( vE0 ));

    psET0->m_sPT.m_avPoint[1] = FCN_V(tgMH_ADD)( psET0->m_sPT.m_avPoint[0], vE0 );
    psET0->m_avEdge[0] = vE0;
    psET0->m_avEdge[1] = FCN_V(tgMH_SUB)( psET0->m_sPT.m_avPoint[2], psET0->m_sPT.m_avPoint[1] );
    FCN_VO(tgGM_ET_Calc_Normal)( psET0 );
}


/* ---- FCN_VO(tgGM_ET_Set_Edge_1) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_ET_Set_Edge_1)( VEC_OBJ_T(TgETRI,PCU) psET0, VEC_T(1,C) vE1 )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Vector)( vE1 ));

    psET0->m_sPT.m_avPoint[2] = FCN_V(tgMH_ADD)( psET0->m_sPT.m_avPoint[1], vE1 );
    psET0->m_avEdge[1] = vE1;
    psET0->m_avEdge[2] = FCN_V(tgMH_SUB)( psET0->m_sPT.m_avPoint[0], psET0->m_sPT.m_avPoint[2] );
    FCN_VO(tgGM_ET_Calc_Normal)( psET0 );
}


/* ---- FCN_VO(tgGM_ET_Set_Edge_2) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_ET_Set_Edge_2)( VEC_OBJ_T(TgETRI,PCU) psET0, VEC_T(1,C) vE2 )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Vector)( vE2 ));

    psET0->m_sPT.m_avPoint[0] = FCN_V(tgMH_ADD)( psET0->m_sPT.m_avPoint[2], vE2 );
    psET0->m_avEdge[0] = FCN_V(tgMH_SUB)( psET0->m_sPT.m_avPoint[1], psET0->m_sPT.m_avPoint[0] );
    psET0->m_avEdge[2] = vE2;
    FCN_VO(tgGM_ET_Calc_Normal)( psET0 );
}


/* ---- FCN_VO(tgGM_ET_Query_Origin) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_ET_Query_Origin)( VEC_OBJ_T(TgETRI,CPCU) psET1 )
{
    return (psET1->m_sPT.m_avPoint[0]);
}


/* ---- FCN_VO(tgGM_ET_Query_Normal) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_ET_Query_Normal)( VEC_OBJ_T(TgETRI,CPCU) psET1 )
{
    return (psET1->m_sPT.m_vNormal);
}


/* ---- FCN_VO(tgGM_ET_Query_Point_0) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_ET_Query_Point_0)( VEC_OBJ_T(TgETRI,CPCU) psET1 )
{
    return (psET1->m_sPT.m_avPoint[0]);
}


/* ---- FCN_VO(tgGM_ET_Query_Point_1) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_ET_Query_Point_1)( VEC_OBJ_T(TgETRI,CPCU) psET1 )
{
    return (psET1->m_sPT.m_avPoint[1]);
}


/* ---- FCN_VO(tgGM_ET_Query_Point_2) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_ET_Query_Point_2)( VEC_OBJ_T(TgETRI,CPCU) psET1 )
{
    return (psET1->m_sPT.m_avPoint[2]);
}


/* ---- FCN_VO(tgGM_ET_Query_Point) ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_ET_Query_Point)( VEC_OBJ_T(TgETRI,CPCU) psET1, TgRSIZE_C uiIndex )
{
    TgGEOM_ASSERT_PARAM(uiIndex <= 2);
    return (psET1->m_sPT.m_avPoint[uiIndex]);
}


/* ---- FCN_VO(tgGM_ET_Query_Edge_0) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_ET_Query_Edge_0)( VEC_OBJ_T(TgETRI,CPCU) psET1 )
{
    return (psET1->m_avEdge[0]);
}


/* ---- FCN_VO(tgGM_ET_Query_Edge_1) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_ET_Query_Edge_1)( VEC_OBJ_T(TgETRI,CPCU) psET1 )
{
    return (psET1->m_avEdge[1]);
}


/* ---- FCN_VO(tgGM_ET_Query_Edge_2) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_ET_Query_Edge_2)( VEC_OBJ_T(TgETRI,CPCU) psET1 )
{
    return (psET1->m_avEdge[2]);
}


/* ---- FCN_VO(tgGM_ET_Query_Edge) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_ET_Query_Edge)( VEC_OBJ_T(TgETRI,CPCU) psET1, TgRSIZE_C uiIndex )
{
    TgGEOM_ASSERT_PARAM(uiIndex <= 2);
    return (psET1->m_avEdge[uiIndex]);
}


/* ---- FCN_VO(tgGM_PT_ET_Query) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_OBJ_T(TgPTRI,CP) FCN_VO(tgGM_ET_Query_PT)( VEC_OBJ_T(TgETRI,CPCU) psET1 )
{
    return (&psET1->m_sPT);
}


/* =============================================================================================================================================================================== */
#endif
