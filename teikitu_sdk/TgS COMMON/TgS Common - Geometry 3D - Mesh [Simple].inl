/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Geometry 3D - Mesh [Simple].inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_GEOMETRY_3D_MESH_SIMPLE_INL)

#if !defined (TEMPLATE_TYPE_EXPANSION__RELOAD)
    #error Must be included as part of a type expansion include chain
#endif


/* == Common ===================================================================================================================================================================== */

/* ---- FCN_VO(tgGM_MS_Reset) ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_MS_Reset)( VEC_OBJ_T(TgMESH_SIMPLE,PCU) psMS0 )
{
    if (psMS0->m_pvVert_List)
    {
        TgFREE_POOL( psMS0->m_pvVert_List );
        psMS0->m_pvVert_List = nullptr;
    };
    if (psMS0->m_puiIndx_List)
    {
        TgFREE_POOL( psMS0->m_puiIndx_List );
        psMS0->m_puiIndx_List = nullptr;
    };
    psMS0->m_nuiVert = 0;
    psMS0->m_nuiIndx = 0;
}


/* ---- FCN_VO(tgGM_MS_Volume) --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_MS_Volume)( VEC_OBJ_T(TgMESH_SIMPLE,CPCU) psMS1 )
{
    if (nullptr == psMS1->m_puiIndx_List)
    {
        return (FCN_VO(tgGM_Volume_MS_VL)( psMS1) );
    }
    else
    {
        return (FCN_VO(tgGM_Volume_MS_IL)( psMS1) );
    };
}


/* ---- FCN_VO(tgGM_MS_Area) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_MS_Area)( VEC_OBJ_T(TgMESH_SIMPLE,CPCU) psMS1 )
{
    if (nullptr == psMS1->m_puiIndx_List)
    {
        return (FCN_VO(tgGM_Area_MS_VL)( psMS1) );
    }
    else
    {
        return (FCN_VO(tgGM_Area_MS_IL)( psMS1) );
    };
}


/* ---- FCN_VO(tgGM_MS_BA) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_MS_BA)( VEC_OBJ_T(TgBOXAA,PCU) psBA0, VEC_OBJ_T(TgMESH_SIMPLE,CPCU) psMS1 )
{
    FCN_VO(tgGM_BA_Reset)( psBA0 );

    for (TgRSIZE uiIndex = 0; uiIndex < psMS1->m_nuiVert; ++uiIndex)
    {
        FCN_VO(tgGM_BA_Union_PT)( psBA0, psMS1->m_pvVert_List[uiIndex] );
    };
}


/* ---- FCN_VO(tgGM_MS_Sweep_BA) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_MS_Sweep_BA)( VEC_OBJ_T(TgBOXAA,PCU) psBA0, VEC_OBJ_T(TgMESH_SIMPLE,CPCU) psMS1, VEC_T(1,C) vDT )
{
    FCN_VO(tgGM_MS_BA)( psBA0, psMS1 );
    FCN_VO(tgGM_BA_Sweep)( psBA0, vDT );
}


/* ---- FCN_VO(tgGM_MS_Project) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_MS_Project)( VEC_T(1,PCU) pvMin, VEC_T(1,PCU) pvMax, VEC_OBJ_T(TgMESH_SIMPLE,CPCU) psMS1, VEC_T(1,C) vDN )
{
    VEC_T(1)                            vMin, vMax, vProj;

    vMin = FCN_V(tgMH_SET1)( VAR_K(KTgMAX) );
    vMax = FCN_V(tgMH_SET1)( -VAR_K(KTgMAX) );

    for (TgRSIZE uiIndex = 0; uiIndex < psMS1->m_nuiVert; ++uiIndex)
    {
        vProj = FCN_V(tgMH_DOT3)( psMS1->m_pvVert_List[uiIndex], vDN );

        vMin = FCN_V(tgMH_MIN)( vMin, vProj );
        vMax = FCN_V(tgMH_MAX)( vMax, vProj );
    };

    *pvMin = vMin;
    *pvMax = vMax;
}


/* ---- FCN_VO(tgGM_MS_Is_Contained) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_VO(tgGM_MS_Is_Contained)( VEC_OBJ_T(TgMESH_SIMPLE,CPCU) psMS1, VEC_T(1,C) vS0 )
{
    if (nullptr == psMS1->m_puiIndx_List)
    {
        return (FCN_VO(tgGM_Is_Contained_MS_VL)( psMS1, vS0) );
    }
    else
    {
        return (FCN_VO(tgGM_Is_Contained_MS_IL)( psMS1, vS0) );
    };
}


/* ---- FCN_VO(tgGM_MS_TX) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_MS_TX)( VEC_OBJ_T(TgMESH_SIMPLE,PCU) psMS0, VEC_T(3,CPCU) pmM0 )
{
    for (TgRSIZE uiIndex = 0; uiIndex < psMS0->m_nuiVert; ++uiIndex)
    {
        psMS0->m_pvVert_List[uiIndex] = FCN_V(tgMH_TX_P,3)( psMS0->m_pvVert_List[uiIndex], pmM0 );
    };
}


/* ---- FCN_VO(tgGM_MS_Copy_TX) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_MS_Copy_TX)( VEC_OBJ_T(TgMESH_SIMPLE,PCU) psMS0, VEC_OBJ_T(TgMESH_SIMPLE,CPCU) psMS1, VEC_T(3,CPCU) pmM0 )
{
    TgUINT_E32                          uiIndex;

    TgRSIZE_C                           nuiVert_MA1 = psMS1->m_nuiVert;
    TgRSIZE_C                           nuiIndx_MA1 = psMS1->m_nuiIndx;

    FCN_VO(tgGM_MS_Init)( psMS0, nuiVert_MA1, nuiIndx_MA1 );

    for (uiIndex = 0; uiIndex < nuiVert_MA1; ++uiIndex)
    {
        psMS0->m_pvVert_List[uiIndex] = FCN_V(tgMH_TX_P,3)( psMS1->m_pvVert_List[uiIndex], pmM0 );
    };

    if (nuiIndx_MA1 > 0)
    {
        TgRSIZE_C       uiIndx_Size_MA0 = sizeof( psMS1->m_puiIndx_List[0] );
        TgRSIZE_C       uiIndx_Size_MA1 = sizeof( psMS1->m_puiIndx_List[1] );
        TgRSIZE_C                           nuiIndx_MA0 = psMS0->m_nuiIndx;

        tgMM_Copy( psMS0->m_puiIndx_List, nuiIndx_MA0*uiIndx_Size_MA0, psMS1->m_puiIndx_List, nuiIndx_MA1*uiIndx_Size_MA1 );
    };
}


/* ---- FCN_VO(tgGM_MS_Copy) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_MS_Copy)( VEC_OBJ_T(TgMESH_SIMPLE,PCU) psMS0, VEC_OBJ_T(TgMESH_SIMPLE,CPCU) psMS1 )
{
    TgRSIZE_C                           nuiVert_MA1 = psMS1->m_nuiVert;
    TgRSIZE_C                           nuiIndx_MA1 = psMS1->m_nuiIndx;

    FCN_VO(tgGM_MS_Init)( psMS0, nuiVert_MA1, nuiIndx_MA1 );

    if (nuiVert_MA1 > 0)
    {
        TgRSIZE_C       uiVert_Size_MA0 = sizeof( psMS1->m_pvVert_List[0] );
        TgRSIZE_C       uiVert_Size_MA1 = sizeof( psMS1->m_pvVert_List[1] );
        TgRSIZE_C                           nuiVert_MA0 = psMS0->m_nuiVert;

        tgMM_Copy( psMS0->m_pvVert_List, nuiVert_MA0*uiVert_Size_MA0, psMS1->m_pvVert_List, nuiVert_MA1*uiVert_Size_MA1 );
    };

    if (nuiIndx_MA1 > 0)
    {
        TgRSIZE_C       uiIndx_Size_MA0 = sizeof( psMS1->m_puiIndx_List[0] );
        TgRSIZE_C       uiIndx_Size_MA1 = sizeof( psMS1->m_puiIndx_List[1] );
        TgRSIZE_C                           nuiIndx_MA0 = psMS0->m_nuiIndx;

        tgMM_Copy( psMS0->m_puiIndx_List, nuiIndx_MA0*uiIndx_Size_MA0, psMS1->m_puiIndx_List, nuiIndx_MA1*uiIndx_Size_MA1 );
    };
}


/* ---- FCN_VO(tgGM_MS_Init) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_MS_Init)( VEC_OBJ_T(TgMESH_SIMPLE,PCU) psMS0, TgRSIZE_C nuiVert, TgRSIZE_C nuiIndx )
{
    if (!(nuiVert == psMS0->m_nuiVert))
    {
        if (psMS0->m_pvVert_List)
        {
            TgFREE_POOL( psMS0->m_pvVert_List );
            psMS0->m_pvVert_List = nullptr;
        }
        psMS0->m_nuiVert = nuiVert;
        if (nuiVert > 0)
        {
            psMS0->m_pvVert_List = (VEC_T(1,P))TgMALLOC_POOL( nuiVert*sizeof( VEC_T(1) ) );
        };
    };

    if (!(nuiIndx == psMS0->m_nuiIndx))
    {
        if (psMS0->m_puiIndx_List)
        {
            TgFREE_POOL( psMS0->m_puiIndx_List );
            psMS0->m_puiIndx_List = nullptr;
        };
        psMS0->m_nuiIndx = nuiIndx;
        if (nuiIndx > 0)
        {
            psMS0->m_puiIndx_List = (TgUINT_E16_P)TgMALLOC_POOL( nuiIndx*sizeof( TgUINT_E16 ) );
        };
    };
}


/* ---- FCN_VO(tgGM_MS_Query_Indx_List) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgUINT_E16_CP FCN_VO(tgGM_MS_Query_Indx_List)( VEC_OBJ_T(TgMESH_SIMPLE,CPCU) psMS1 )
{
    return (psMS1->m_puiIndx_List);
}


/* ---- FCN_VO(tgGM_MS_Query_Vert_List) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1,CP) FCN_VO(tgGM_MS_Query_Vert_List)( VEC_OBJ_T(TgMESH_SIMPLE,CPCU) psMS1 )
{
    return (psMS1->m_pvVert_List);
}


/* ---- FCN_VO(tgGM_MS_Query_Indx_Count) ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRSIZE FCN_VO(tgGM_MS_Query_Indx_Count)( VEC_OBJ_T(TgMESH_SIMPLE,CPCU) psMS1 )
{
    return (psMS1->m_nuiIndx);
}


/* ---- FCN_VO(tgGM_MS_Query_Vert_Count) ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRSIZE FCN_VO(tgGM_MS_Query_Vert_Count)( VEC_OBJ_T(TgMESH_SIMPLE,CPCU) psMS1 )
{
    return (psMS1->m_nuiVert);
}


/* =============================================================================================================================================================================== */
#endif
