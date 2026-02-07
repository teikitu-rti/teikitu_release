/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Geometry 3D - Mesh [BA].inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_GEOMETRY_3D_MESH_BA_INL)

#if !defined (TEMPLATE_TYPE_EXPANSION__RELOAD)
    #error Must be included as part of a type expansion include chain
#endif


/* == Common ===================================================================================================================================================================== */

/* ---- FCN_VO(tgGM_MA_Free_Internal) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_MA_Free_Internal)( VEC_OBJ_T(TgMESH_BA,PCU) psMA0 )
{
    if (psMA0->m_pvVert_DT)
    {
        TgFREE_POOL( psMA0->m_pvVert_DT );
        psMA0->m_pvVert_DT = nullptr;
    };
    TgERROR((0 == psMA0->m_sMS.m_nuiVert) || (ETgSWEEP_STATIC == psMA0->m_enSweep));

    if (psMA0->m_psBA)
    {
        TgFREE_POOL( psMA0->m_psBA );
        psMA0->m_psBA = nullptr;
    };
    if (psMA0->m_puiFlags)
    {
        TgFREE_POOL( psMA0->m_puiFlags );
        psMA0->m_puiFlags = nullptr;
    };
    psMA0->m_nuiFace = 0;
    psMA0->m_enSweep = ETgSWEEP_STATIC;
}


/* ---- FCN_VO(tgGM_MA_Reset) ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_MA_Reset)( VEC_OBJ_T(TgMESH_BA,PCU) psMA0 )
{
    FCN_VO(tgGM_MS_Reset)( &psMA0->m_sMS );
    FCN_VO(tgGM_MA_Free_Internal)( psMA0 );

    FCN_VO(tgGM_DT_Reset)( &psMA0->m_sDT );
    psMA0->m_vCG[0] = FCN_V(tgMH_Init_Point)( FCN_V(tgMH_SET1)( TYPE_K(0) ) );
    psMA0->m_vCG[1] = FCN_V(tgMH_Init_Point)( FCN_V(tgMH_SET1)( TYPE_K(0) ) );
}


/* ---- FCN_VO(tgGM_MA_Support_Point) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_MA_Support_Point)( VEC_OBJ_T(TgMESH_BA,CPCU) psMA1, VEC_T(1,C) vDN )
{
    return (FCN_VO(tgGM_MS_Support_Point)( &psMA1->m_sMS, vDN ) );
}


/* ---- FCN_VO(tgGM_MA_Volume) --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_MA_Volume)( VEC_OBJ_T(TgMESH_BA,CPCU) psMA1 )
{
    return (FCN_VO(tgGM_MS_Volume)( &psMA1->m_sMS) );
}


/* ---- FCN_VO(tgGM_MA_Area) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_MA_Area)( VEC_OBJ_T(TgMESH_BA,CPCU) psMA1 )
{
    return (FCN_VO(tgGM_MS_Area)( &psMA1->m_sMS) );
}


/* ---- FCN_VO(tgGM_MA_BA) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_MA_BA)( VEC_OBJ_T(TgBOXAA,PCU) psBA0, VEC_OBJ_T(TgMESH_BA,CPCU) psMA1 )
{
    FCN_VO(tgGM_MS_BA)( psBA0, &psMA1->m_sMS );
}


/* ---- FCN_VO(tgGM_MA_Sweep_BA) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_MA_Sweep_BA)( VEC_OBJ_T(TgBOXAA,PCU) psBA0, VEC_OBJ_T(TgMESH_BA,CPCU) psMA1, VEC_T(1,C) vDT )
{
    FCN_VO(tgGM_MA_BA)( psBA0, psMA1 );
    FCN_VO(tgGM_BA_Sweep)( psBA0, vDT );
}


/* ---- FCN_VO(tgGM_MA_Project) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_MA_Project)( VEC_T(1,PCU) pvMin, VEC_T(1,PCU) pvMax, VEC_OBJ_T(TgMESH_BA,CPCU) psMA1, VEC_T(1,C) vDN )
{
    FCN_VO(tgGM_MS_Project)( pvMin, pvMax, &psMA1->m_sMS, vDN );
}


/* ---- FCN_VO(tgGM_MA_Is_Contained) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_VO(tgGM_MA_Is_Contained)( VEC_OBJ_T(TgMESH_BA,CPCU) psMA1, VEC_T(1,C) vS0 )
{
    return (FCN_VO(tgGM_MS_Is_Contained)( &psMA1->m_sMS, vS0 ));
}


/* ---- FCN_VO(tgGM_MA_Init_MS) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_MA_Init_MS)( VEC_OBJ_T(TgMESH_BA,PCU) psMA0, VEC_OBJ_T(TgMESH_SIMPLE,CPCU) psMS )
{
    TgRSIZE_C                           nuiVert = psMS->m_nuiVert;
    TgRSIZE_C                           nuiIndx = psMS->m_nuiIndx;

    FCN_VO(tgGM_MA_Init)( psMA0, nuiVert, nuiIndx, ETgSWEEP_STATIC );
    FCN_VO(tgGM_MS_Copy)( &psMA0->m_sMS, psMS );
    FCN_VO(tgGM_DT_Reset)( &psMA0->m_sDT );

    FCN_VO(tgGM_MA_Update_Face_CG_BA)( psMA0 );
    tgMM_Set_U08_0xFF( psMA0->m_puiFlags, psMA0->m_nuiFace*sizeof( TgUINT_E32  ) );
    psMA0->m_enSweep = ETgSWEEP_STATIC;
}


/* ---- FCN_VO(tgGM_MA_Init_MS_TX) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_MA_Init_MS_TX)( VEC_OBJ_T(TgMESH_BA,PCU) psMA0, VEC_OBJ_T(TgMESH_SIMPLE,CPCU) psMS, VEC_T(3,CPCU) pmM0 )
{
    TgRSIZE_C                           nuiVert = psMS->m_nuiVert;
    TgRSIZE_C                           nuiIndx = psMS->m_nuiIndx;

    FCN_VO(tgGM_MA_Init)( psMA0, nuiVert, nuiIndx, ETgSWEEP_STATIC );
    FCN_VO(tgGM_MS_Copy_TX)( &psMA0->m_sMS, psMS, pmM0 );
    FCN_VO(tgGM_DT_Reset)( &psMA0->m_sDT );

    FCN_VO(tgGM_MA_Update_Face_CG_BA)( psMA0 );
    tgMM_Set_U08_0xFF( psMA0->m_puiFlags, psMA0->m_nuiFace*sizeof( TgUINT_E32  ) );
    psMA0->m_enSweep = ETgSWEEP_STATIC;
}


/* ---- FCN_VO(tgGM_MA_Init_MS_TX_TL) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_MA_Init_MS_TX_TL)( VEC_OBJ_T(TgMESH_BA,PCU) psMA0, VEC_OBJ_T(TgMESH_SIMPLE,CPCU) psMS, VEC_T(3,CPCU) pmM0, VEC_T(1,C) vDT )
{
    TgRSIZE_C                           nuiVert = psMS->m_nuiVert;
    TgRSIZE_C                           nuiIndx = psMS->m_nuiIndx;

    FCN_VO(tgGM_MA_Init)( psMA0, nuiVert, nuiIndx, ETgSWEEP_LINEAR );
    FCN_VO(tgGM_MS_Copy_TX)( &psMA0->m_sMS, psMS, pmM0 );
    FCN_VO(tgGM_DT_Set)( &psMA0->m_sDT, vDT );

    FCN_VO(tgGM_MA_Update_Face_CG_BA)( psMA0 );
    tgMM_Set_U08_0xFF( psMA0->m_puiFlags, psMA0->m_nuiFace*sizeof( TgUINT_E32  ) );
    psMA0->m_enSweep = ETgSWEEP_LINEAR;
}


/* ---- FCN_VO(tgGM_MA_Init_MS_TX_TX) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_MA_Init_MS_TX_TX)( VEC_OBJ_T(TgMESH_BA,PCU) psMA0, VEC_OBJ_T(TgMESH_SIMPLE,CPCU) psMS, VEC_T(3,CPCU) pmM0, VEC_T(3,CPCU) pmM1 )
{
    TgUINT_E32                          uiIndex;

    TgRSIZE_C                           nuiVert = psMS->m_nuiVert;
    TgRSIZE_C                           nuiIndx = psMS->m_nuiIndx;

    FCN_VO(tgGM_MA_Init)( psMA0, nuiVert, nuiIndx, ETgSWEEP_ROTATIONAL );
    FCN_VO(tgGM_MS_Copy_TX)( &psMA0->m_sMS, psMS, pmM0 );
    FCN_VO(tgGM_DT_Reset)( &psMA0->m_sDT );

    for (uiIndex = 0; uiIndex < psMS->m_nuiVert; ++uiIndex)
    {
        VEC_T(1,C)                          vX0 = FCN_V(tgMH_TX_P,3)( psMS->m_pvVert_List[uiIndex], pmM1 );

        psMA0->m_pvVert_DT[uiIndex] = FCN_V(tgMH_SUB)( vX0, psMA0->m_sMS.m_pvVert_List[uiIndex] );
    };

    FCN_VO(tgGM_MA_Update_Face_CG_BA)( psMA0 );
    tgMM_Set_U08_0xFF( psMA0->m_puiFlags, psMA0->m_nuiFace*sizeof( TgUINT_E32  ) );
    psMA0->m_enSweep = ETgSWEEP_ROTATIONAL;
}


/* ---- FCN_VO(tgGM_MA_Copy) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_MA_Copy)( VEC_OBJ_T(TgMESH_BA,PCU) psMA0, VEC_OBJ_T(TgMESH_BA,CPCU) psMA1 )
{
    TgRSIZE_C                           nuiVert_MA1 = psMA1->m_sMS.m_nuiVert;
    TgRSIZE_C                           nuiIndex_MA1 = psMA1->m_sMS.m_nuiIndx;
    TgRSIZE_C                           nuiFace_MA1 = psMA1->m_nuiFace;

    FCN_VO(tgGM_MA_Init)( psMA0, nuiVert_MA1, nuiIndex_MA1, psMA1->m_enSweep );
    FCN_VO(tgGM_MS_Copy)( &psMA0->m_sMS, &psMA1->m_sMS );
    psMA0->m_enSweep = psMA1->m_enSweep;

    switch (psMA0->m_enSweep)
    {
        case ETgSWEEP_ROTATIONAL:
        {
            TgRSIZE_C       uiVert_DT_Size = sizeof( psMA0->m_pvVert_DT[0] );
            TgRSIZE_C                           nuiVert_MA0 = psMA0->m_sMS.m_nuiVert;

            TgCOMPILER_ASSERT(sizeof( psMA0->m_pvVert_DT[0] ) == sizeof( psMA1->m_pvVert_DT[0] ),);
            tgMM_Copy( psMA0->m_pvVert_DT, nuiVert_MA0*uiVert_DT_Size, psMA1->m_pvVert_DT, nuiVert_MA1*uiVert_DT_Size );
            
            psMA0->m_vCG[1] = psMA1->m_vCG[1];
            
        };
        TgATTRIBUTE_FALLTHROUGH case ETgSWEEP_LINEAR:
            psMA0->m_sDT = psMA1->m_sDT;
        TgATTRIBUTE_FALLTHROUGH case ETgSWEEP_STATIC:
        {
            TgRSIZE_C       uiBA_Size = sizeof( psMA0->m_psBA[0] );
            TgRSIZE_C       uiFlags_Size = sizeof( psMA0->m_puiFlags[0] );
            TgRSIZE_C                           nuiFace_MA0 = psMA0->m_nuiFace;

            TgCOMPILER_ASSERT(sizeof( psMA0->m_psBA[0] ) == sizeof( psMA1->m_psBA[0] ),);
            TgCOMPILER_ASSERT(sizeof( psMA0->m_puiFlags[0] ) == sizeof( psMA1->m_puiFlags[0] ),);

            tgMM_Copy( psMA0->m_psBA, nuiFace_MA0*uiBA_Size, psMA1->m_psBA, nuiFace_MA1*uiBA_Size );
            tgMM_Copy( psMA0->m_puiFlags, nuiFace_MA0*uiFlags_Size, psMA1->m_puiFlags, nuiFace_MA1*uiFlags_Size );
            
            psMA0->m_vCG[0] = psMA1->m_vCG[0];
            break;
        };
    };
}


/* ---- FCN_VO(tgGM_MA_Update_Face_BA) ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_MA_Update_Face_BA)( VEC_OBJ_T(TgMESH_BA,PCU) psMA0 )
{
    if (nullptr == psMA0->m_sMS.m_puiIndx_List)
    {
        FCN_VO(tgGM_MA_Update_Face_BA_VL)( psMA0 );
    }
    else
    {
        FCN_VO(tgGM_MA_Update_Face_BA_IL)( psMA0 );
    };
}


/* ---- FCN_VO(tgGM_MA_Update_Face_CG_BA) ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_MA_Update_Face_CG_BA)( VEC_OBJ_T(TgMESH_BA,PCU) psMA0 )
{
    if (nullptr == psMA0->m_sMS.m_puiIndx_List)
    {
        FCN_VO(tgGM_MA_Update_Face_CG_BA_VL)( psMA0 );
    }
    else
    {
        FCN_VO(tgGM_MA_Update_Face_CG_BA_IL)( psMA0 );
    };
}


/* ---- FCN_VO(tgGM_MA_Query_Indx_List) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgUINT_E16_CP FCN_VO(tgGM_MA_Query_Indx_List)( VEC_OBJ_T(TgMESH_BA,CPCU) psMA0 )
{
    return (FCN_VO(tgGM_MS_Query_Indx_List)( &psMA0->m_sMS) );
}


/* ---- FCN_VO(tgGM_MA_Query_Vert_List) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1,CP) FCN_VO(tgGM_MA_Query_Vert_List)( VEC_OBJ_T(TgMESH_BA,CPCU) psMA0 )
{
    return (FCN_VO(tgGM_MS_Query_Vert_List)( &psMA0->m_sMS) );
}


/* ---- FCN_VO(tgGM_MA_Query_Indx_Count) ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRSIZE FCN_VO(tgGM_MA_Query_Indx_Count)( VEC_OBJ_T(TgMESH_BA,CPCU) psMA0 )
{
    return (FCN_VO(tgGM_MS_Query_Indx_Count)( &psMA0->m_sMS) );
}


/* ---- FCN_VO(tgGM_MA_Query_Vert_Count) ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRSIZE FCN_VO(tgGM_MA_Query_Vert_Count)( VEC_OBJ_T(TgMESH_BA,CPCU) psMA0 )
{
    return (FCN_VO(tgGM_MS_Query_Vert_Count)( &psMA0->m_sMS) );
}


/* ---- FCN_VO(tgGM_MA_Query_CG_0) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1,CP) FCN_VO(tgGM_MA_Query_CG_0)( VEC_OBJ_T(TgMESH_BA,CPCU) psMA0 )
{
    return (psMA0->m_vCG + 0);
}


/* ---- FCN_VO(tgGM_MA_Query_CG_1) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1,CP) FCN_VO(tgGM_MA_Query_CG_1)( VEC_OBJ_T(TgMESH_BA,CPCU) psMA0 )
{
    TgERROR(ETgSWEEP_STATIC != psMA0->m_enSweep);
    return (psMA0->m_vCG + 1);
}


/* ---- FCN_VO(tgGM_MA_Query_DT) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_OBJ_T(TgDELTA,CP) FCN_VO(tgGM_MA_Query_DT)( VEC_OBJ_T(TgMESH_BA,CPCU) psMA0 )
{
    return (&psMA0->m_sDT);
}


/* =============================================================================================================================================================================== */
#endif
