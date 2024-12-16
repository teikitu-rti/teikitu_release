/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Effect - Decal - Update.c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.12 | »GUID« 964CB1A6-814D-4E19-8E67-A83FCA98BF05 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "TgS Effect - Internal.inl"


/* == Effect ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
#if defined(TgBUILD_FEATURE__GRAPHICS_VFX)

static TgBOOL                               tgFX__Update__Decal_Reserve_Cache_Buffer( STg2_FX__Decal_P );
static TgBOOL                               tgFX__Update__Decal_Commit_Cache_Buffer( STg2_FX__Decal_P, TgRSIZE_C  );
static TgVOID                               tgFX__Update__Decal_Free_Cache_Buffer( STg2_FX__Decal_P );
static TgVOID                               tgFX__Update__Decal_Update__Write_Cache( STg2_FX__Decal_P, STg2_CO_Request_F32_04_CP );

/*# defined(TgBUILD_FEATURE__GRAPHICS_VFX) */
#endif




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgFX__File__Decal_Patch_File_Data ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgFX__File__Decal_Patch_File_Data( STg2_FX_Decal__File_Data_P psData )
{
    TgUINT_PTR                          uiData_Top;

    uiData_Top = (TgUINT_PTR)psData;

    psData->m_sAnim.m_sData_Offset.m_uiColour += uiData_Top;
}


/* ---- tgFX__Update__Decal_Create_Command --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgFX__Update__Decal_Create_Command( STg2_FX_Instance_CP psInst, TgFX_DATA_INST_ID_C tiData, TgVOID_CP UNUSED_PARAM pData1 )
{
    STg2_FX__Decal_P                    psDecal;
    STg2_FX_Decal__File_Data_CP         psFile_Data;

    psDecal = g_asFX__Decal + tiData.m_uiI;
    psFile_Data = psDecal->m_psFile_Data;

#if defined(TgBUILD_FEATURE__GRAPHICS_VFX)
    if (!tgFX__Update__Decal_Reserve_Cache_Buffer( psDecal ))
    {
        return (false);
    };

    tgFX__Update__Set_Render_Data_From_Material_Hash( nullptr, &psDecal->m_tiMaterial, &psDecal->m_enVertex, psFile_Data->m_uiHash_Material );

    if (KTgID__INVALID_VALUE == psDecal->m_tiMaterial.m_uiKI)
    {
        return (false);
    };

    tgRN_Calc_UV_Animation_F32_04_1( &psDecal->m_sExtend.m_vUV_01_Constant, &psDecal->m_sExtend.m_vUV_01_Scale, psDecal->m_tiMaterial, KTgZERO_V128.m_vF32_04_1, KTgZERO_V128.m_vF32_04_1 );
/*# defined(TgBUILD_FEATURE__GRAPHICS_VFX) */
#endif

    psDecal->m_sExtend.m_vSize_Start = tgMH_MAD_F32_04_1( tgMH_SET1_F32_04_1( tgCM_RAND_ONE_F32() ), psFile_Data->m_vSize_RNG[0], psFile_Data->m_vSize_MID[0] );
    psDecal->m_sExtend.m_vSize_Final = tgMH_MAD_F32_04_1( tgMH_SET1_F32_04_1( tgCM_RAND_ONE_F32() ), psFile_Data->m_vSize_RNG[1], psFile_Data->m_vSize_MID[1] );

    psDecal->m_sExtend.m_vPos_N2W = psInst->m_vPos_N2W;
    psDecal->m_sExtend.m_vScale = psInst->m_vScale;
    psDecal->m_sExtend.m_vSpin = tgMH_SET1_F32_04_1( tgCM_RAND_ONE_F32()*psFile_Data->m_fSpin_RNG + psFile_Data->m_fSpin_MID );
    psDecal->m_sExtend.m_vSize = psDecal->m_sExtend.m_vSize_Start;
    tgFX_Evaluate_AnimData_F32_04_1( &psDecal->m_sExtend.m_vColour, psFile_Data->m_sAnim.m_sParameter.m_psColour, tgMH_SET1_F32_04_1( 0.0F ) );

    if (psDecal->m_sTime.m_fTime_End__Start < 0.0F)
        g_aenFX__Decal__Shared__State[tiData.m_uiI] = ETgFX_EFFECT_STATE__UPDATE__ACTIVE_INFINITE;
    else
        g_aenFX__Decal__Shared__State[tiData.m_uiI] = ETgFX_EFFECT_STATE__UPDATE__ACTIVE_FIRST;

    return (true);
}


/* ---- tgFX__Update__Decal_Update ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgFX__Update__Decal_Update( TgVEC_F32_04_1 vdT, TgFLOAT32_C fDT, ETgFX_UPDATE_C enUpdate )
{
    TgFX_DATA_INST_ID                   tiActive;
    STg2_FX__Decal_P                    psDecal;

    tiActive = g_atiFX__Decal__Update__Head[enUpdate];

    while (KTgID__INVALID_VALUE != tiActive.m_uiKI)
    {
        tgFX__Update__Decal_Diag_Check_Effect( tiActive );

        psDecal = g_asFX__Decal + tiActive.m_uiI;

        if (!tgFX__Update__Decal_Update_Life_Time( tiActive.m_uiI, fDT, vdT ))
        {
            tiActive = psDecal->m_tiNext[ETgFX_NEXT__UPDATE];
            continue;
        };

    #if defined(TgBUILD_FEATURE__GRAPHICS_VFX)

        tgFX_Evaluate_AnimData_F32_04_1( &psDecal->m_sExtend.m_vColour, psDecal->m_psFile_Data->m_sAnim.m_sParameter.m_psColour, psDecal->m_vLive_Time );

        if (ETgFX_EFFECT_STATE__UPDATE__ACTIVE_FIRST == g_aenFX__Decal__Shared__State[tiActive.m_uiI])
        {
            STg2_SE_CO_Request_F32_04           sRequest;
            TgUN_V128                           uSize;

            uSize.m_vF32_04_1 = tgMH_LEN_F32_04_1( psDecal->m_sExtend.m_vSize );

            tgSE_Init_Request( &sRequest );
            tgCO_REQ_Init_Collect_F32_04( &sRequest.m_sCollision_Request, ETgSPHERE, ETgCO_PURPOSE__DECAL );
            tgCO_REQ_Set_Include_Filter_F32_04( &sRequest.m_sCollision_Request, ETgCO_FILTER__RENDER );
            tgGM_SP_Init_F32_04( &sRequest.m_sCollision_Request.m_sPrimitive.m_sSP, psDecal->m_sExtend.m_vPos_N2W, uSize.m_vF32_04_1 );

            if (TgFAILED(tgSE_Collide( &sRequest, ETgSE_CHANNEL__SET )) || 0 == sRequest.m_sCollision_Request.m_nuiCollect_Last)
            {
                return;
            };

            tgFX__Update__Decal_Update__Write_Cache( psDecal, &sRequest.m_sCollision_Request );
        }
    /*# defined(TgBUILD_FEATURE__GRAPHICS_VFX) */
    #endif

        tiActive = psDecal->m_tiNext[ETgFX_NEXT__UPDATE];
    };
}


/* ---- tgFX__Update__Decal_Process_Update_Command ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgFX__Update__Decal_Process_Update_Command( ETgFX_COMMAND_C enCommand, TgVOID_CP UNUSED_PARAM pData, TgFX_DATA_INST_ID_C tiData )
{
#if defined(TgBUILD_FEATURE__GRAPHICS_VFX)
    if (ETgFX_COMMAND__CLIENT_TO_UPDATE__KILL == enCommand)
    {
        tgFX__Update__Decal_Free_Cache_Buffer( g_asFX__Decal + tiData.m_uiI );
    };
#else
    (void)enCommand;
    (void)tiData;
/*# defined(TgBUILD_FEATURE__GRAPHICS_VFX) */
#endif
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgFX__Update__Decal_Reserve_Cache_Buffer --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if defined(TgBUILD_FEATURE__GRAPHICS_VFX)
static TgBOOL tgFX__Update__Decal_Reserve_Cache_Buffer( STg2_FX__Decal_P psDecal )
{
    TgRSIZE                             uiPageSize;
    TgRSIZE                             uiMemory_Current;
    TgRSIZE                             uiMemory_New;
    TgRSIZE                             uiMax_Commit;

    uiPageSize = tgMM_Page_Size();

    /* Determine if the decal max allocation fits into max memory limit for the module / system */
    uiMax_Commit = 1 + (ETgFX_DECAL__VERTEX_MAX * sizeof( STg2_FX__Decal__Vertex ) / uiPageSize);
    uiMemory_Current = atomic_load( &g_xuiFX__Decal__Memory_Current );
    do
    {
        uiMemory_New = uiMemory_Current + uiMax_Commit * uiPageSize;
        if (uiMemory_New > g_uiFX_Decal_Memory_Max)
        {
            return (false);
        };
    }
    while (!atomic_compare_exchange_weak( &g_xuiFX__Decal__Memory_Current, &uiMemory_Current, uiMemory_New ));

    /* Reserve enough memory for max number of vertices */
    psDecal->m_sExtend.m_psVert = (STg2_FX__Decal__Vertex_P)TgRESERVE_VIRTUAL( (TgRSIZE)(uiMax_Commit * uiPageSize) );
    if (nullptr == psDecal->m_sExtend.m_psVert)
    {
        uiMemory_Current = atomic_load( &g_xuiFX__Decal__Memory_Current );
        do
        {
            uiMemory_New = uiMemory_Current - uiMax_Commit * uiPageSize;
        }
        while (!atomic_compare_exchange_weak( &g_xuiFX__Decal__Memory_Current, &uiMemory_Current, uiMemory_New ));
        return (false);
    };

    /* Initialize the linked list of free particles and record the number of particles on committed memory pages */
    psDecal->m_sExtend.m_nuiVert = 0;
    psDecal->m_sExtend.m_nuiVert_Commit = 0;

    return (true);
}
/*# defined(TgBUILD_FEATURE__GRAPHICS_VFX) */
#endif


/* ---- tgFX__Update__Decal_Commit_Cache_Buffer ---------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if defined(TgBUILD_FEATURE__GRAPHICS_VFX)
static TgBOOL tgFX__Update__Decal_Commit_Cache_Buffer( STg2_FX__Decal_P psDecal, TgRSIZE_C nuiVert )
{
    TgRSIZE                             uiPageSize;
    TgRSIZE                             uiMemory_Current;
    TgRSIZE                             uiMemory_New;
    TgRSIZE                             nuiMin_Vert;
    TgRSIZE                             uiMax_Commit;
    TgRSIZE                             uiMin_Commit;

    uiPageSize = tgMM_Page_Size();

    /* Determine if the emitter max allocation fits into max memory limit for the module / system */
    uiMax_Commit = 1 + (ETgFX_DECAL__VERTEX_MAX * sizeof( STg2_FX__Decal__Vertex ) / uiPageSize);
    nuiMin_Vert = tgCM_MAX_UMAX( 1, tgCM_MIN_UMAX( nuiVert, ETgFX_DECAL__VERTEX_MAX ) );
    uiMin_Commit = 1 + (nuiMin_Vert * sizeof( STg2_FX__Decal__Vertex ) / uiPageSize);

    /* Commit enough memory for one memory page, or one vertex */
    if (nullptr == TgCOMMIT_VIRTUAL( psDecal->m_sExtend.m_psVert, uiMin_Commit ))
    {
        uiMemory_Current = atomic_load( &g_xuiFX__Decal__Memory_Current );
        do
        {
            uiMemory_New = uiMemory_Current - uiMax_Commit * uiPageSize;
        }
        while (!atomic_compare_exchange_weak( &g_xuiFX__Decal__Memory_Current, &uiMemory_Current, uiMemory_New ));
        return (false);
    };

    /* Initialize the linked list of free particles and record the number of particles on committed memory pages */
    psDecal->m_sExtend.m_nuiVert_Commit = uiMin_Commit;

    return (true);
}
/*# defined(TgBUILD_FEATURE__GRAPHICS_VFX) */
#endif


/* ---- tgFX__Update__Decal_Free_Cache_Buffer ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if defined(TgBUILD_FEATURE__GRAPHICS_VFX)
static TgVOID tgFX__Update__Decal_Free_Cache_Buffer( STg2_FX__Decal_P psDecal )
{
    TgRSIZE                             uiPageSize;
    TgRSIZE                             uiMemory_Current;
    TgRSIZE                             uiMemory_New;
    TgRSIZE                             uiMax_Commit;

    uiPageSize = tgMM_Page_Size();

    uiMax_Commit = 1 + (ETgFX_DECAL__VERTEX_MAX * sizeof( STg2_FX__Decal__Vertex ) / uiPageSize);
    if (nullptr == psDecal->m_sExtend.m_psVert)
    {
        uiMemory_Current = atomic_load( &g_xuiFX__Decal__Memory_Current );
        do
        {
            uiMemory_New = uiMemory_Current - uiMax_Commit * uiPageSize;
        }
        while (!atomic_compare_exchange_weak( &g_xuiFX__Decal__Memory_Current, &uiMemory_Current, uiMemory_New ));

        TgFREE_VIRTUAL( psDecal->m_sExtend.m_psVert );
    };

    psDecal->m_sExtend.m_psVert = nullptr;
    psDecal->m_sExtend.m_nuiVert = 0;
    psDecal->m_sExtend.m_nuiVert_Commit = 0;
}
/*# defined(TgBUILD_FEATURE__GRAPHICS_VFX) */
#endif


/* ---- tgFX__Update__Decal_Update__Write_Cache ---------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if defined(TgBUILD_FEATURE__GRAPHICS_VFX)
static TgVOID tgFX__Update__Decal_Update__Write_Cache( STg2_FX__Decal_P psDecal, STg2_CO_Request_F32_04_CP psCO_Request )
{
    TgPLANE_F32_04                      asPN[ETgFRUSTUM_PLANE__MAX];
    TgUN_V128                           uAA;
    TgVEC_F32_04_1                      vN0;
    TgVEC_F32_04_1                      vT0;
    TgVEC_F32_04_1                      vB0;
    TgVEC_F32_04_1                      vSize;
    TgVEC_F32_04_1                      vInvSizeX;
    TgVEC_F32_04_1                      vInvSizeY;
    TgVEC_F32_04_1                      vD0;
    TgVEC_F32_04_1                      vD1;
    TgVEC_F32_04_1                      vD2;
    TgUN_V128                           uPlnEqN;
    TgUN_V128                           uqR0;
    TgRSIZE                             uiCollect;
    union
    {
        TgUINT_F08_P                        pui;
        STg2_CO_Clip_List_F32_04_P          ps;
    }                                   sClipList;

    psDecal->m_sExtend.m_nuiVert = 0;

    vN0 = psDecal->m_sExtend.m_vNormal;
    tgMH_Init_Basis_From_Vector_F32_04_1( &vT0, &vB0, vN0 );
    uAA.m_vF32_04_1 = tgMH_SEL_F32_04_1( vN0, psDecal->m_sExtend.m_vSpin, KTgFFF0_V128.m_vF32_04_1 );
    uqR0.m_vS_F32_04_1 = tgMH_QT_Init_Axis_Angle_S_F32_04_1( uAA.m_vS_F32_04_1 );
    vT0 = tgMH_QT_INV_TX_F32_04_1( vT0, uqR0.m_vF32_04_1 );
    vB0 = tgMH_QT_INV_TX_F32_04_1( vB0, uqR0.m_vF32_04_1 );
    vSize = tgMH_LEN_F32_04_1( psDecal->m_sExtend.m_vSize );
    vInvSizeX = tgMH_DIV_F32_04_1( KTgONE_V128.m_vF32_04_1, tgMH_SPX_F32_04_1( vSize ) );
    vInvSizeY = tgMH_DIV_F32_04_1( KTgONE_V128.m_vF32_04_1, tgMH_SPY_F32_04_1( vSize ) );

    /* Create Clip Planes */
    vD0 = tgMH_DOT_F32_04_1( psDecal->m_sExtend.m_vPos_N2W, vN0 );
    uPlnEqN.m_vF32_04_1 = tgMH_SEL_F32_04_1( tgMH_NEG_F32_04_1( vN0 ), tgMH_ADD_F32_04_1( vSize, vD0 ), KTgFFF0_V128.m_vF32_04_1 );
    tgGM_PN_Set_PlnEqN_F32_04( asPN + ETgFRUSTUM_PLANE__NEAR, uPlnEqN.m_vF32_04_1 );
    uPlnEqN.m_vF32_04_1 = tgMH_SEL_F32_04_1( vN0, tgMH_SUB_F32_04_1( vSize, vD0 ), KTgFFF0_V128.m_vF32_04_1 );
    tgGM_PN_Set_PlnEqN_F32_04( asPN + ETgFRUSTUM_PLANE__FAR, uPlnEqN.m_vF32_04_1 );

    vD1 = tgMH_DOT_F32_04_1( psDecal->m_sExtend.m_vPos_N2W, vT0 );
    uPlnEqN.m_vF32_04_1 = tgMH_SEL_F32_04_1( vT0, tgMH_SUB_F32_04_1( vSize, vD1 ), KTgFFF0_V128.m_vF32_04_1 );
    tgGM_PN_Set_PlnEqN_F32_04( asPN + ETgFRUSTUM_PLANE__LEFT, uPlnEqN.m_vF32_04_1 );
    uPlnEqN.m_vF32_04_1 = tgMH_SEL_F32_04_1( tgMH_NEG_F32_04_1( vT0 ), tgMH_ADD_F32_04_1( vSize, vD1 ), KTgFFF0_V128.m_vF32_04_1 );
    tgGM_PN_Set_PlnEqN_F32_04( asPN + ETgFRUSTUM_PLANE__RIGHT, uPlnEqN.m_vF32_04_1 );

    vD2 = tgMH_DOT_F32_04_1( psDecal->m_sExtend.m_vPos_N2W, vB0 );
    uPlnEqN.m_vF32_04_1 = tgMH_SEL_F32_04_1( tgMH_NEG_F32_04_1( vB0 ), tgMH_ADD_F32_04_1( vSize, vD2 ), KTgFFF0_V128.m_vF32_04_1 );
    tgGM_PN_Set_PlnEqN_F32_04( asPN + ETgFRUSTUM_PLANE__TOP, uPlnEqN.m_vF32_04_1 );
    uPlnEqN.m_vF32_04_1 = tgMH_SEL_F32_04_1( vB0, tgMH_SUB_F32_04_1( vSize, vD2 ), KTgFFF0_V128.m_vF32_04_1 );
    tgGM_PN_Set_PlnEqN_F32_04( asPN + ETgFRUSTUM_PLANE__BOTTOM, uPlnEqN.m_vF32_04_1 );

    psDecal->m_vBA_Max_W = tgMH_SET1_F32_04_1( -KTgMAX_F32 );
    psDecal->m_vBA_Min_W = tgMH_SET1_F32_04_1( KTgMAX_F32 );

    sClipList.pui = (TgUINT_F08_P)TgMALLOC_POOL(sizeof( STg2_CO_Clip_List_F32_04 ) + 9 * sizeof( TgVEC_F32_04_1 ));

    for (uiCollect = 0; uiCollect < psCO_Request->m_nuiCollect_Last; ++uiCollect)
    {
        TgVEC_F32_04_1                      vDirTest;
        ETgFRUSTUM_PLANE                    enPlane;
        TgFLOAT32                           fNormal_Theshold;
        TgVEC_F32_04_1                      avUV_A[9];
        TgRSIZE                             nuiStart;
        TgRSIZE                             nuiVert;
        TgRSIZE                             uiVert;

        vDirTest = tgMH_DOT_F32_04_1( psCO_Request->m_psCollect[uiCollect].m_vNormal, vN0 );
        if (tgCM_NR0_F32( ((TgVEC_S_F32_04_1_P)(&vDirTest))->x ))
        {
            continue;
        };

        /* Clip each triangle to the frustum planes */
        if (nullptr == sClipList.ps)
        {
            psDecal->m_sExtend.m_nuiVert = 0;
            break;
        };
        sClipList.ps->m_nuiPoint = 3;
        sClipList.ps->m_nuiMax = 9;
        sClipList.ps->m_avPoint[0] = psCO_Request->m_psCollect[uiCollect].m_avPoint[0];
        sClipList.ps->m_avPoint[1] = psCO_Request->m_psCollect[uiCollect].m_avPoint[1];
        sClipList.ps->m_avPoint[2] = psCO_Request->m_psCollect[uiCollect].m_avPoint[2];

        for (enPlane = ETgFRUSTUM_PLANE__NEAR; enPlane < ETgFRUSTUM_PLANE__MAX; ++enPlane)
        {
            if (TgFAILED(tgCO_PN_Clip_F32_04( sClipList.ps, asPN + enPlane )))
            {
                break;
            };
        };

        if (sClipList.ps->m_nuiPoint < 3)
        {
            continue;
        };

        if (3 * (sClipList.ps->m_nuiPoint - 2) + psDecal->m_sExtend.m_nuiVert >= ETgFX_DECAL__VERTEX_MAX)
        {
            TgWARNING_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Decal exceeded max vertex count.\n" );
            psDecal->m_sExtend.m_nuiVert = 0;
            break;
        };

        if (!tgFX__Update__Decal_Commit_Cache_Buffer( psDecal, 3 * (sClipList.ps->m_nuiPoint - 2) + psDecal->m_sExtend.m_nuiVert ))
        {
            TgWARNING_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to commit decal buffer.\n" );
            psDecal->m_sExtend.m_nuiVert = 0;
            break;
        };

        /* Calculate the UVs for each point and an alpha fade parameter based on normal projection */
        fNormal_Theshold = tgCM_NR0_F32( g_fFX_Decal_Normal_Threshold ) ? 1.0F : 1.0F / g_fFX_Decal_Normal_Threshold;
        for (uiVert = 0; uiVert < sClipList.ps->m_nuiPoint; ++uiVert)
        {
            TgVEC_F32_04_1                      vDiff;
            TgVEC_F32_04_1                      vUV_X;
            TgVEC_F32_04_1                      vUV_Y;
            TgVEC_F32_04_1                      vUV_XY;
            TgFLOAT32                           fA;
            TgUN_V128                           uRet;

            vDiff = tgMH_SUB_F32_04_1( sClipList.ps->m_avPoint[uiVert], psDecal->m_sExtend.m_vPos_N2W );
            vUV_X = tgMH_MUL_F32_04_1( tgMH_DOT_F32_04_1( vDiff, vT0 ), vInvSizeX );
            vUV_Y = tgMH_MUL_F32_04_1( tgMH_DOT_F32_04_1( vDiff, vB0 ), vInvSizeY );
            vUV_XY = tgMH_SEL_F32_04_1( vUV_X, vUV_Y, KTgF000_V128.m_vF32_04_1 );

            uRet.m_vF32_04_1 = tgMH_DOT_F32_04_1( psCO_Request->m_psCollect[uiCollect].m_vNormal, vN0 );
            fA = tgCM_MIN_F32( 1.0F, fNormal_Theshold * tgPM_ABS_F32( uRet.m_vS_F32_04_1.x ) );
            avUV_A[uiVert] = tgMH_SEL_F32_04_1( vUV_XY, tgMH_SET1_F32_04_1( fA ), KTgFF00_V128.m_vF32_04_1 );
        };

        psDecal->m_vBA_Max_W = tgMH_MAX_F32_04_1( psDecal->m_vBA_Max_W, sClipList.ps->m_avPoint[0] );
        psDecal->m_vBA_Min_W = tgMH_MIN_F32_04_1( psDecal->m_vBA_Min_W, sClipList.ps->m_avPoint[0] );
        psDecal->m_vBA_Max_W = tgMH_MAX_F32_04_1( psDecal->m_vBA_Max_W, sClipList.ps->m_avPoint[1] );
        psDecal->m_vBA_Min_W = tgMH_MIN_F32_04_1( psDecal->m_vBA_Min_W, sClipList.ps->m_avPoint[1] );

        /* Output the clipped points as a triangle fan and calculate the basis vectors */
        nuiStart = psDecal->m_sExtend.m_nuiVert;
        nuiVert = psDecal->m_sExtend.m_nuiVert;
        for (uiVert = 1; uiVert + 1 < sClipList.ps->m_nuiPoint; nuiVert += 3, ++uiVert)
        {
            psDecal->m_sExtend.m_psVert[nuiVert + 0].m_vS0_W = sClipList.ps->m_avPoint[0];
            psDecal->m_sExtend.m_psVert[nuiVert + 0].m_vT0 = vT0;
            psDecal->m_sExtend.m_psVert[nuiVert + 0].m_vB0 = vB0;
            psDecal->m_sExtend.m_psVert[nuiVert + 0].m_vUV_A = avUV_A[0];
            psDecal->m_sExtend.m_psVert[nuiVert + 1].m_vS0_W = sClipList.ps->m_avPoint[uiVert + 0];
            psDecal->m_sExtend.m_psVert[nuiVert + 1].m_vT0 = vT0;
            psDecal->m_sExtend.m_psVert[nuiVert + 1].m_vB0 = vB0;
            psDecal->m_sExtend.m_psVert[nuiVert + 1].m_vUV_A = avUV_A[uiVert + 0];
            psDecal->m_sExtend.m_psVert[nuiVert + 2].m_vS0_W = sClipList.ps->m_avPoint[uiVert + 1];
            psDecal->m_sExtend.m_psVert[nuiVert + 2].m_vT0 = vT0;
            psDecal->m_sExtend.m_psVert[nuiVert + 2].m_vB0 = vB0;
            psDecal->m_sExtend.m_psVert[nuiVert + 2].m_vUV_A = avUV_A[uiVert + 1];

            psDecal->m_vBA_Max_W = tgMH_MAX_F32_04_1( psDecal->m_vBA_Max_W, sClipList.ps->m_avPoint[uiVert + 1] );
            psDecal->m_vBA_Min_W = tgMH_MIN_F32_04_1( psDecal->m_vBA_Min_W, sClipList.ps->m_avPoint[uiVert + 1] );
        };
        TgERROR( nuiStart != nuiVert );
        (void)nuiStart;
        psDecal->m_sExtend.m_nuiVert = nuiVert;
    };

    TgFREE_POOL(sClipList.pui);
}
/*# defined(TgBUILD_FEATURE__GRAPHICS_VFX) */
#endif
