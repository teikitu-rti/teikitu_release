/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Partition - Prune and Sweep.c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.12 | »GUID« 964CB1A6-814D-4E19-8E67-A83FCA98BF05 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Partition ================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

static TgRESULT
tgPA_Graph_PNS_Insert_Object_Internal(
    STg2_PA_Graph__Prune_And_Sweep_PC ARG0, TgUINT_E32 ARG1, TgBOXAA_F32_04_CPCU ARG5 );

static TgRESULT
tgPA_Graph_PNS_Remove_Object_Internal(
    STg2_PA_Graph__Prune_And_Sweep_PC ARG0, TgPARTITION_OBJECT_ID_C ARG1 );

static TgVOID
tgPA_Graph_PNS_Object_Update_Interval(
    STg2_PA_Graph__Prune_And_Sweep_PCU TgANALYSIS_NO_NULL ARG0, STg2_PA_Graph__PNS__Point_End_PCU TgANALYSIS_NO_NULL ARG1, TgFLOAT32_C ARG2, TgFLOAT32_C ARG3, 
    TgFLOAT32_C ARG4, TgFLOAT32_C ARG5, TgPARTITION_OBJECT_ID_C ARG6 );

static TgVOID
tgPA_Graph_PNS_Interval_Push(
    STg2_PA_Graph__PNS__Point_End_PCU TgANALYSIS_NO_NULL ARG0, TgFLOAT32_C ARG2, TgFLOAT32_C ARG3, TgRSIZE_C ARG4 );

static TgVOID
tgPA_Graph_PNS_Interval_Update(
    STg2_PA_Graph__PNS__Point_End_PCU TgANALYSIS_NO_NULL ARG0, TgUINT_E16_C ARG2, TgUINT_E16_C ARG3 );

static TgBOOL
tgPA_Graph_PNS_Pair_Push(
    STg2_PA_Graph__Prune_And_Sweep_PCU TgANALYSIS_NO_NULL ARG0, TgRSIZE_C ARG2, TgRSIZE_C ARG3 );

static TgBOOL
tgPA_Graph_PNS_Remove_Contact_Pair(
    STg2_PA_Graph__Prune_And_Sweep_PCU TgANALYSIS_NO_NULL ARG0, TgRSIZE_C ARG2, TgRSIZE_C ARG3 );

static TgVOID
tgPA_Graph_PNS_Remove_Object_Contact_List(
    STg2_PA_Graph__Prune_And_Sweep_PCU TgANALYSIS_NO_NULL ARG0, TgRSIZE_C ARG2 );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Prune and Sweep - Public Functions                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgPA_Graph_PNS_Init ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgPARTITION_GRAPH_ID tgPA_Graph_PNS_Init( TgVOID )
{
    TgSINT_E32                          iIndex;
    STg2_PA_Graph__Prune_And_Sweep_P    psPA_PNS;

    tgPM_MT_MX_Wait_Block( &g_sModule_Lock );

    /* Allocate memory for into the graph array */

    if (nullptr == g_aapsPA_Graph)
    {
        /* This is the first Graph to be allocated - allocate the modules Graph array. */
        g_iPA_Graph_End = 1;
        g_aapsPA_Graph = (STg2_PA_Graph_PP)TgMALLOC_POOL( (TgRSIZE)g_iPA_Graph_End * sizeof(STg2_PA_Graph_P) );
        g_aapsPA_Graph[g_iPA_Graph_End - 1] = nullptr;
    }
    else if (g_niPA_Graph == g_iPA_Graph_End)
    {
        /* Graph pointers can not be moved in the array, and so it is possibel for us to have holes in the array. We only need to expand the array in the case that we do not have
           room for a new Graph, and there are no holes in the array. */
        ++g_iPA_Graph_End;
        g_aapsPA_Graph = (STg2_PA_Graph_PP)TgREALLOC_POOL( g_aapsPA_Graph, (TgRSIZE)g_iPA_Graph_End * sizeof(STg2_PA_Graph_P) );
        g_aapsPA_Graph[g_iPA_Graph_End - 1] = nullptr;
    }

    /* Search the Graph array for a spot and allocate memory for a Prune and Sweep Graph. */

    for (iIndex = g_iPA_Graph_End - 1; iIndex >= 0; --iIndex) /* We go backgrounds based on the assumption that the realloc case is the most likely. */
    {
        if (nullptr == g_aapsPA_Graph[iIndex])
        {
            break;
        }
    };

    TgDIAG(iIndex >= 0); /* Function is in a MX and there is no logical way for the above code to fail (i.e. no fallback is implemented). */

    g_aapsPA_Graph[iIndex] = (STg2_PA_Graph_P)TgMALLOC_POOL( sizeof(STg2_PA_Graph__Prune_And_Sweep) );
    tgMM_Set_U08_0x00( g_aapsPA_Graph[iIndex], sizeof(STg2_PA_Graph__Prune_And_Sweep) );

    tgPARTITION_GRAPH_ID_Init( &g_aapsPA_Graph[iIndex]->m_tiGraph_Singleton, (TgUINT_E32)iIndex );
    g_aapsPA_Graph[iIndex]->m_uiSize = sizeof(STg2_PA_Graph__Prune_And_Sweep);
    g_aapsPA_Graph[iIndex]->m_enPA_Graph = ETgPA_GRAPH_TYPE__PRUNE_SWEEP;

    psPA_PNS = (STg2_PA_Graph__Prune_And_Sweep_P)g_aapsPA_Graph[iIndex];

    tgPM_MT_MX_Release( &g_sModule_Lock );

    /* Initialize the new Graph. */

    psPA_PNS->m_asX0[KTgPA_PNS_MAX_INTERVAL].m_uiNext = KTgPA_PNS_MAX_INTERVAL;
    psPA_PNS->m_asX0[KTgPA_PNS_MAX_INTERVAL].m_uiPrev = KTgPA_PNS_MAX_INTERVAL;
    psPA_PNS->m_asX1[KTgPA_PNS_MAX_INTERVAL].m_uiNext = KTgPA_PNS_MAX_INTERVAL;
    psPA_PNS->m_asX1[KTgPA_PNS_MAX_INTERVAL].m_uiPrev = KTgPA_PNS_MAX_INTERVAL;
    psPA_PNS->m_asX2[KTgPA_PNS_MAX_INTERVAL].m_uiNext = KTgPA_PNS_MAX_INTERVAL;
    psPA_PNS->m_asX2[KTgPA_PNS_MAX_INTERVAL].m_uiPrev = KTgPA_PNS_MAX_INTERVAL;

    for (TgRSIZE uiIndex = 0; uiIndex < KTgPA_PNS_MAX_OBJECTS; ++uiIndex)
    {
        psPA_PNS->m_asObject[uiIndex].m_uiContact_Linked_List_Head = KTgPA_PNS_MAX_CONTACT_PAIR;
    };

    for (TgRSIZE uiIndex = 0; uiIndex < KTgPA_PNS_MAX_CONTACT_PAIR; ++uiIndex)
    {
        psPA_PNS->m_asContact_Pair[uiIndex].m_uiContact_Next = uiIndex + 1;
    };

    psPA_PNS->m_nuiObjects = 0;
    psPA_PNS->m_uiEmpty = 0;

    /* Create the Critical Section if MP-Safe requested */
    tgPM_MT_MX_Init( &psPA_PNS->m_sSystem_Lock, nullptr );
    ++g_niPA_Graph;
    return (tgPARTITION_GRAPH_ID_Query_Unsafe( &g_aapsPA_Graph[iIndex]->m_tiGraph_Singleton ));
}


/* ---- tgPA_Graph_PNS_Free ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPA_Graph_PNS_Free( TgPARTITION_GRAPH_ID_C tiPA )
{
    STg2_PA_Graph_PC                    psPA_Graph = g_aapsPA_Graph[tiPA.m_uiI];
    STg2_PA_Graph__Prune_And_Sweep_PC   psPA_PNS = (STg2_PA_Graph__Prune_And_Sweep_P)psPA_Graph;

    TgPARAM_CHECK(nullptr != g_aapsPA_Graph);
    TgPARAM_CHECK(tiPA.m_uiI < (TgUINT_E64)g_iPA_Graph_End);
    TgPARAM_CHECK(nullptr != g_aapsPA_Graph[tiPA.m_uiI]);

    if (tiPA.m_uiKI != tgPARTITION_GRAPH_ID_Query_Unsafe( &psPA_Graph->m_tiGraph_Singleton ).m_uiKI)
        return;

    tgPM_MT_MX_Wait_Block( &g_sModule_Lock );

    tgPM_MT_MX_Wait_Block( &psPA_PNS->m_sSystem_Lock );
    g_aapsPA_Graph[tiPA.m_uiI] = nullptr;
    --g_niPA_Graph;
    tgPM_MT_MX_Release( &psPA_PNS->m_sSystem_Lock );
    TgFREE_POOL(psPA_PNS);

    tgPM_MT_MX_Release( &g_sModule_Lock );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Prune and Sweep - Internal Functions                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgPA_Graph_PNS_Insert_Object --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgPA_Graph_PNS_Insert_Object( TgPARTITION_OBJECT_ID_PC ptiResult, STg2_PA_Graph_PC psPA_Graph, TgUINT_PTR_C uiCallbackID, TgUINT_E64_C uiCategory_0, 
                                       TgUINT_E64_C uiCollide_0, TgBOXAA_F32_04_CPCU psBA )
{
    STg2_PA_Graph__Prune_And_Sweep_PC   psPA_PNS = (STg2_PA_Graph__Prune_And_Sweep_P)psPA_Graph;

    TgUINT_E32                          uiIndex_Object;

    /* Data consistency check - mask values must have valid (one) 62th and 63st bits */

    if ((0 != (uiCategory_0 & (3ULL << 62))) || !tgGM_BA_Is_Valid_F32_04( psBA ) || tgGM_BA_Is_Empty_F32_04( psBA ))
    {
        *ptiResult = KTgPARTITION_OBJECT_ID__INVALID;
        return (KTgE_FAIL);
    }

    TgPARAM_CHECK(nullptr != psPA_Graph);
    TgPARAM_CHECK(sizeof(STg2_PA_Graph__Prune_And_Sweep) == psPA_Graph->m_uiSize);

    tgPM_MT_MX_Wait_Block( &psPA_PNS->m_sSystem_Lock );

    #pragma region Retrieve an open array element and initialize it
    for (uiIndex_Object = 0; uiIndex_Object < KTgPA_PNS_MAX_OBJECTS && (0 != (psPA_PNS->m_asObject[uiIndex_Object].m_uiCategory & (3ULL << 62))); ++uiIndex_Object);

    if (uiIndex_Object >= KTgPA_PNS_MAX_OBJECTS)
    {
        tgPM_MT_MX_Release( &psPA_PNS->m_sSystem_Lock );
        *ptiResult = KTgPARTITION_OBJECT_ID__INVALID;
        return (KTgE_FAIL);
    };

    psPA_PNS->m_asObject[uiIndex_Object].m_uiCallbackID = uiCallbackID;
    psPA_PNS->m_asObject[uiIndex_Object].m_uiCategory = (uiCategory_0 | (3ULL << 62));
    psPA_PNS->m_asObject[uiIndex_Object].m_uiCollide = uiCollide_0;
    tgGM_BA_Copy_F32_04( &psPA_PNS->m_asObject[uiIndex_Object].m_sBA, psBA ); /* Set the AABB data values */
    tgPARTITION_OBJECT_ID_Init( &psPA_PNS->m_asObject[uiIndex_Object].m_tiObject_Singleton, uiIndex_Object );
    TgDIAG(KTgPA_PNS_MAX_CONTACT_PAIR == psPA_PNS->m_asObject[uiIndex_Object].m_uiContact_Linked_List_Head);

    ++psPA_PNS->m_nuiObjects;
    #pragma endregion

    TgVERIFY(TgSUCCEEDED(tgPA_Graph_PNS_Insert_Object_Internal( psPA_PNS, uiIndex_Object, psBA )));

    /*  Store the mask value, which is also used to indicate the ID is now in use.  This must be done after the AABB loop so that */
    /* the trivial case of self intersection can be trivially ignored. */

    *ptiResult = tgPARTITION_OBJECT_ID_Query_Unsafe( &psPA_PNS->m_asObject[uiIndex_Object].m_tiObject_Singleton );
    tgPM_MT_MX_Release( &psPA_PNS->m_sSystem_Lock );
    return (KTgS_OK);
}


/* ---- tgPA_Graph_PNS_Remove_Object --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgPA_Graph_PNS_Remove_Object( STg2_PA_Graph_PC psPA_Graph, TgPARTITION_OBJECT_ID_C tiObject )
{
    STg2_PA_Graph__Prune_And_Sweep_PC   psPA_PNS = (STg2_PA_Graph__Prune_And_Sweep_P)psPA_Graph;

    TgPARAM_CHECK(nullptr != psPA_Graph);
    TgPARAM_CHECK(sizeof(STg2_PA_Graph__Prune_And_Sweep) == psPA_Graph->m_uiSize);

    tgPM_MT_MX_Wait_Block( &psPA_PNS->m_sSystem_Lock );
    tgPA_Graph_PNS_Remove_Object_Internal( psPA_PNS, tiObject );

    psPA_PNS->m_asObject[tiObject.m_uiI].m_uiCallbackID = KTgMAX_UMAX;
    psPA_PNS->m_asObject[tiObject.m_uiI].m_uiCategory = 0;
    psPA_PNS->m_asObject[tiObject.m_uiI].m_uiCollide = 0;
    tgGM_BA_Reset_F32_04( &psPA_PNS->m_asObject[tiObject.m_uiI].m_sBA );
    tgPARTITION_OBJECT_ID_Invalidate( &psPA_PNS->m_asObject[tiObject.m_uiI].m_tiObject_Singleton );
    psPA_PNS->m_asObject[tiObject.m_uiI].m_uiContact_Linked_List_Head = KTgPA_PNS_MAX_CONTACT_PAIR;

    --psPA_PNS->m_nuiObjects;

    tgPM_MT_MX_Release( &psPA_PNS->m_sSystem_Lock );

    return (KTgS_OK);
}


/* ---- tgPA_Graph_PNS_Test_AABB ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgPA_Graph_PNS_Test_AABB( TgBOOL_PC pbResult, STg2_PA_Graph_PC psPA_Graph, TgUINT_E64_C uiCategory_0, TgUINT_E64_C uiCollide_0, TgBOXAA_F32_04_CPCU psBA )
{
    STg2_PA_Graph__Prune_And_Sweep_PC   psPA_PNS = (STg2_PA_Graph__Prune_And_Sweep_P)psPA_Graph;

    TgPARAM_CHECK(nullptr != pbResult);
    TgPARAM_CHECK(nullptr != psPA_Graph);
    TgPARAM_CHECK(sizeof(STg2_PA_Graph__Prune_And_Sweep) == psPA_Graph->m_uiSize);

    /* Check this object against all current objects, adding all existing pair-wise potential contact sets */

    for (TgRSIZE uiIndex = 0, nuiObjects = 0; uiIndex < KTgPA_PNS_MAX_OBJECTS && nuiObjects < psPA_PNS->m_nuiObjects; ++uiIndex)
    {
        if (0 == (psPA_PNS->m_asObject[uiIndex].m_uiCategory & (3ULL << 62)))
        {
            continue;
        }
        else
        {
            TgUINT_E64_C                        uiCategory_1 = psPA_PNS->m_asObject[uiIndex].m_uiCategory;
            TgUINT_E64_C                        uiCollide_1 = psPA_PNS->m_asObject[uiIndex].m_uiCollide;

            ++nuiObjects;

            if (   0 != ((uiCategory_0 & uiCollide_1) & KTgPA_CATEGORY_BIT_MASK__AND_TEST)
                && 0 != ((uiCategory_1 & uiCollide_0) & KTgPA_CATEGORY_BIT_MASK__AND_TEST)
                && 0 != (((uiCategory_0 & uiCollide_1) | (uiCategory_1 & uiCollide_0)) & KTgPA_CATEGORY_BIT_MASK__OR_TEST)
                && tgCO_BA_Test_BA_F32_04( psBA, &psPA_PNS->m_asObject[uiIndex].m_sBA ))
            {
                *pbResult = true;
                return KTgS_OK;
            };
        };
    };

    *pbResult = false;
    return KTgS_OK;
}


/* ---- tgPA_Graph_PNS_Object_Update --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgPA_Graph_PNS_Object_Update( STg2_PA_Graph_PC psPA_Graph, TgPARTITION_OBJECT_ID_C tiObject, TgBOXAA_F32_04_CPCU psBA, TgUINT_E64_C uiCategory_0, TgUINT_E64_C uiCollide_0 )
{
    STg2_PA_Graph__Prune_And_Sweep_PC   psPA_PNS = (STg2_PA_Graph__Prune_And_Sweep_P)psPA_Graph;

    TgUN_V128                           vOldMin, vOldMax, vNewMin, vNewMax;

    TgERROR( tiObject.m_uiI < KTgPA_PNS_MAX_OBJECTS );

    tgPM_MT_MX_Wait_Block( &psPA_PNS->m_sSystem_Lock );

    /* Check to see if the category or collide bitfields have changed. */

    if (((uiCategory_0 | (3ULL << 62)) != psPA_PNS->m_asObject[tiObject.m_uiI].m_uiCategory) || (uiCollide_0 != psPA_PNS->m_asObject[tiObject.m_uiI].m_uiCollide))
    {
        tgPA_Graph_PNS_Remove_Object_Internal( psPA_PNS, tiObject );

        psPA_PNS->m_asObject[tiObject.m_uiI].m_uiCategory = (uiCategory_0 | (3ULL << 62));
        psPA_PNS->m_asObject[tiObject.m_uiI].m_uiCollide = uiCollide_0;
        tgGM_BA_Copy_F32_04( &psPA_PNS->m_asObject[tiObject.m_uiI].m_sBA, psBA ); /* Set the AABB data values */
        tgPARTITION_OBJECT_ID_Is_Equal( &psPA_PNS->m_asObject[tiObject.m_uiI].m_tiObject_Singleton, tiObject );
        TgDIAG(KTgPA_PNS_MAX_CONTACT_PAIR == psPA_PNS->m_asObject[tiObject.m_uiI].m_uiContact_Linked_List_Head);

        tgPA_Graph_PNS_Insert_Object_Internal( psPA_PNS, tiObject.m_uiI, psBA );
    }
    else
    {
        /* Update respective projections of bounding box on each axis. */

        vOldMin.m_vF32_04_1 = tgGM_BA_Query_Min_F32_04( &psPA_PNS->m_asObject[tiObject.m_uiI].m_sBA );
        vOldMax.m_vF32_04_1 = tgGM_BA_Query_Max_F32_04( &psPA_PNS->m_asObject[tiObject.m_uiI].m_sBA );
        vNewMin.m_vF32_04_1 = tgGM_BA_Query_Min_F32_04( psBA );
        vNewMax.m_vF32_04_1 = tgGM_BA_Query_Max_F32_04( psBA );

        tgPA_Graph_PNS_Object_Update_Interval( psPA_PNS, psPA_PNS->m_asX0, vOldMin.m_vS_F32_04_1.x, vOldMax.m_vS_F32_04_1.x, vNewMin.m_vS_F32_04_1.x, vNewMax.m_vS_F32_04_1.x, tiObject );
        tgPA_Graph_PNS_Object_Update_Interval( psPA_PNS, psPA_PNS->m_asX1, vOldMin.m_vS_F32_04_1.y, vOldMax.m_vS_F32_04_1.y, vNewMin.m_vS_F32_04_1.y, vNewMax.m_vS_F32_04_1.y, tiObject );
        tgPA_Graph_PNS_Object_Update_Interval( psPA_PNS, psPA_PNS->m_asX2, vOldMin.m_vS_F32_04_1.z, vOldMax.m_vS_F32_04_1.z, vNewMin.m_vS_F32_04_1.z, vNewMax.m_vS_F32_04_1.z, tiObject );

        tgGM_BA_Copy_F32_04( &psPA_PNS->m_asObject[tiObject.m_uiI].m_sBA, psBA );
    };

    tgPM_MT_MX_Release( &psPA_PNS->m_sSystem_Lock );

    return (KTgS_OK);
}


/* ---- tgPA_Graph_PNS_Execute_Function ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgPA_Graph_PNS_Execute_Function( STg2_PA_Graph_PC psPA_Graph, TgFCN_PA_CALLBACK pfnExec )
{
    STg2_PA_Graph__Prune_And_Sweep_PC   psPA_PNS = (STg2_PA_Graph__Prune_And_Sweep_P)psPA_Graph;
    TgRSIZE                             uiIndex, nuiObjects, uiContact_Index;

    if (nullptr == pfnExec)
    {
        return (KTgE_FAIL);
    };

    TgPARAM_CHECK(nullptr != psPA_Graph);
    TgPARAM_CHECK(nullptr != psPA_PNS);
    TgPARAM_CHECK(sizeof(STg2_PA_Graph__Prune_And_Sweep) == psPA_Graph->m_uiSize);

    tgPM_MT_MX_Wait_Block( &psPA_PNS->m_sSystem_Lock );

    for (uiIndex = 0, nuiObjects = 0; uiIndex < KTgPA_PNS_MAX_OBJECTS && nuiObjects < psPA_PNS->m_nuiObjects; ++uiIndex)
    {
        if (0 == ((3ULL << 62) & psPA_PNS->m_asObject[uiIndex].m_uiCategory))
        {
            continue;
        };

        ++nuiObjects;

        for (uiContact_Index = psPA_PNS->m_asObject[uiIndex].m_uiContact_Linked_List_Head; uiContact_Index < KTgPA_PNS_MAX_CONTACT_PAIR; )
        {
            if (psPA_PNS->m_asContact_Pair[uiContact_Index].m_bPaired_Contact)
            {
                uiContact_Index = psPA_PNS->m_asContact_Pair[uiContact_Index].m_uiContact_Next;
                continue;
            }
            else
            {
                TgUINT_MAX                          uiCallbackID_0 = psPA_PNS->m_asContact_Pair[uiContact_Index].m_uiCallbackID_0;
                TgUINT_MAX                          uiCallbackID_1 = psPA_PNS->m_asContact_Pair[uiContact_Index].m_uiCallbackID_1;

                pfnExec( uiCallbackID_0, uiCallbackID_1 );
                uiContact_Index = psPA_PNS->m_asContact_Pair[uiContact_Index].m_uiContact_Next;
            };
        };
    };

    tgPM_MT_MX_Release( &psPA_PNS->m_sSystem_Lock );

    return (KTgS_OK);
}


/* ---- tgPA_Graph_PNS_Object_Execute_Function ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgPA_Graph_PNS_Object_Execute_Function( STg2_PA_Graph_PC psPA_Graph, TgFCN_PA_CALLBACK pfnExec, TgPARTITION_OBJECT_ID_C tiObject )
{
    STg2_PA_Graph__Prune_And_Sweep_PC   psPA_PNS = (STg2_PA_Graph__Prune_And_Sweep_P)psPA_Graph;
    TgRSIZE                             uiContact_Index;

    TgPARAM_CHECK(nullptr != psPA_Graph);
    TgPARAM_CHECK(nullptr != psPA_PNS);
    TgPARAM_CHECK(sizeof(STg2_PA_Graph__Prune_And_Sweep) == psPA_Graph->m_uiSize);

    if (tiObject.m_uiI > KTgPA_PNS_MAX_OBJECTS || nullptr == pfnExec)
    {
        return (KTgE_FAIL);
    };

    tgPM_MT_MX_Wait_Block( &psPA_PNS->m_sSystem_Lock );

    for (uiContact_Index = psPA_PNS->m_asObject[tiObject.m_uiI].m_uiContact_Linked_List_Head; uiContact_Index < KTgPA_PNS_MAX_CONTACT_PAIR; )
    {
        if (psPA_PNS->m_asContact_Pair[uiContact_Index].m_bPaired_Contact)
        {
            uiContact_Index = psPA_PNS->m_asContact_Pair[uiContact_Index].m_uiContact_Next;
            continue;
        }
        else
        {
            TgUINT_MAX                          uiCallbackID_0 = psPA_PNS->m_asContact_Pair[uiContact_Index].m_uiCallbackID_0;
            TgUINT_MAX                          uiCallbackID_1 = psPA_PNS->m_asContact_Pair[uiContact_Index].m_uiCallbackID_1;

            pfnExec( uiCallbackID_0, uiCallbackID_1 );
            uiContact_Index = psPA_PNS->m_asContact_Pair[uiContact_Index].m_uiContact_Next;
        };
    };

    tgPM_MT_MX_Release( &psPA_PNS->m_sSystem_Lock );
    return (KTgS_OK);
}


/* ---- tgPA_Graph_PNS_Object_List_Execute_Function ------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgPA_Graph_PNS_Object_List_Execute_Function( STg2_PA_Graph_PC psPA_Graph, TgFCN_PA_CALLBACK pfnExec, TgUINT_E64_CPC puiFM_List, TgRSIZE nuiFM )
{
    STg2_PA_Graph__Prune_And_Sweep_PC   psPA_PNS = (STg2_PA_Graph__Prune_And_Sweep_P)psPA_Graph;
    TgRSIZE                             uiIndex, uiContact_Index;

    if (nullptr == pfnExec)
    {
        return (KTgE_FAIL);
    };

    TgPARAM_CHECK(nullptr != psPA_Graph);
    TgPARAM_CHECK(nullptr != psPA_PNS);
    TgPARAM_CHECK(sizeof(STg2_PA_Graph__Prune_And_Sweep) == psPA_Graph->m_uiSize);

    tgPM_MT_MX_Wait_Block( &psPA_PNS->m_sSystem_Lock );

    for (uiIndex = 0; uiIndex < nuiFM; ++uiIndex)
    {
        TgPARTITION_OBJECT_ID_C             tiObject = { .m_uiKI = puiFM_List[uiIndex] };

        if (0 == ((3ULL << 62) & psPA_PNS->m_asObject[tiObject.m_uiI].m_uiCategory))
        {
            continue;
        };

        for (uiContact_Index = psPA_PNS->m_asObject[tiObject.m_uiI].m_uiContact_Linked_List_Head; uiContact_Index < KTgPA_PNS_MAX_CONTACT_PAIR; )
        {
            if (psPA_PNS->m_asContact_Pair[uiContact_Index].m_bPaired_Contact)
            {
                uiContact_Index = psPA_PNS->m_asContact_Pair[uiContact_Index].m_uiContact_Next;
                continue;
            }
            else
            {
                TgUINT_MAX                          uiCallbackID_0 = psPA_PNS->m_asContact_Pair[uiContact_Index].m_uiCallbackID_0;
                TgUINT_MAX                          uiCallbackID_1 = psPA_PNS->m_asContact_Pair[uiContact_Index].m_uiCallbackID_1;

                pfnExec( uiCallbackID_0, uiCallbackID_1 );
                uiContact_Index = psPA_PNS->m_asContact_Pair[uiContact_Index].m_uiContact_Next;
            };
        };
    };

    tgPM_MT_MX_Release( &psPA_PNS->m_sSystem_Lock );

    return (KTgS_OK);
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgPA_Graph_PNS_Insert_Object_Internal ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT tgPA_Graph_PNS_Insert_Object_Internal( STg2_PA_Graph__Prune_And_Sweep_PC psPA_PNS, TgUINT_E32 uiIndex_Object, TgBOXAA_F32_04_CPCU psBA )
{
    TgUINT_E64_C                        uiCategory_0 = psPA_PNS->m_asObject[uiIndex_Object].m_uiCategory;
    TgUINT_E64_C                        uiCollide_0 = psPA_PNS->m_asObject[uiIndex_Object].m_uiCollide;
    TgUN_V128                           vMin, vMax;

    #pragma region Add the aligned bounding box to the Manager.
    vMin.m_vF32_04_1 = tgGM_BA_Query_Min_F32_04( psBA );
    vMax.m_vF32_04_1 = tgGM_BA_Query_Max_F32_04( psBA );

    tgPA_Graph_PNS_Interval_Push( psPA_PNS->m_asX0, vMin.m_vS_F32_04_1.x, vMax.m_vS_F32_04_1.x, uiIndex_Object );
    tgPA_Graph_PNS_Interval_Push( psPA_PNS->m_asX1, vMin.m_vS_F32_04_1.y, vMax.m_vS_F32_04_1.y, uiIndex_Object );
    tgPA_Graph_PNS_Interval_Push( psPA_PNS->m_asX2, vMin.m_vS_F32_04_1.z, vMax.m_vS_F32_04_1.z, uiIndex_Object );

    /* Check this object against all current objects, adding all existing pair-wise potential contact sets */

    for (TgRSIZE uiTest_Object = 0, nuiObjects = 0; uiTest_Object < KTgPA_PNS_MAX_OBJECTS && nuiObjects < psPA_PNS->m_nuiObjects; ++uiTest_Object)
    {
        if ((0 == (psPA_PNS->m_asObject[uiTest_Object].m_uiCategory & (3ULL << 62))) || (uiIndex_Object == uiTest_Object))
        {
            continue;
        }
        else
        {
            TgUINT_E64_C                        uiCategory_1 = psPA_PNS->m_asObject[uiTest_Object].m_uiCategory;
            TgUINT_E64_C                        uiCollide_1 = psPA_PNS->m_asObject[uiTest_Object].m_uiCollide;

            ++nuiObjects;

            if (   0 != ((uiCategory_0 & uiCollide_1) & KTgPA_CATEGORY_BIT_MASK__AND_TEST)
                && 0 != ((uiCategory_1 & uiCollide_0) & KTgPA_CATEGORY_BIT_MASK__AND_TEST)
                && 0 != (((uiCategory_0 & uiCollide_1) | (uiCategory_1 & uiCollide_0)) & KTgPA_CATEGORY_BIT_MASK__OR_TEST)
                && tgCO_BA_Test_BA_F32_04( psBA, &psPA_PNS->m_asObject[uiTest_Object].m_sBA ))
            {
                tgPA_Graph_PNS_Pair_Push( psPA_PNS, uiIndex_Object, uiTest_Object );
            };
        };
    };
    #pragma endregion

    return (KTgS_OK);
}


/* ---- tgPA_Graph_PNS_Remove_Object_Internal ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT tgPA_Graph_PNS_Remove_Object_Internal( STg2_PA_Graph__Prune_And_Sweep_PC psPA_PNS, TgPARTITION_OBJECT_ID_C tiObject )
{
    TgRSIZE                             uiIndex_Interval_0 = 2 * tiObject.m_uiI + 0;
    TgRSIZE                             uiIndex_Interval_1 = 2 * tiObject.m_uiI + 1;

    TgERROR( (tiObject.m_uiI < KTgPA_PNS_MAX_OBJECTS) && (0 != (psPA_PNS->m_asObject[tiObject.m_uiI].m_uiCategory & (3ULL << 62))) );

    /* Remove the respective min and max projections of the bounding box on each axis. */

    psPA_PNS->m_asX0[psPA_PNS->m_asX0[uiIndex_Interval_0].m_uiPrev].m_uiNext = psPA_PNS->m_asX0[uiIndex_Interval_0].m_uiNext;
    psPA_PNS->m_asX0[psPA_PNS->m_asX0[uiIndex_Interval_0].m_uiNext].m_uiPrev = psPA_PNS->m_asX0[uiIndex_Interval_0].m_uiPrev;
    psPA_PNS->m_asX0[psPA_PNS->m_asX0[uiIndex_Interval_1].m_uiPrev].m_uiNext = psPA_PNS->m_asX0[uiIndex_Interval_1].m_uiNext;
    psPA_PNS->m_asX0[psPA_PNS->m_asX0[uiIndex_Interval_1].m_uiNext].m_uiPrev = psPA_PNS->m_asX0[uiIndex_Interval_1].m_uiPrev;

    psPA_PNS->m_asX1[psPA_PNS->m_asX1[uiIndex_Interval_0].m_uiPrev].m_uiNext = psPA_PNS->m_asX1[uiIndex_Interval_0].m_uiNext;
    psPA_PNS->m_asX1[psPA_PNS->m_asX1[uiIndex_Interval_0].m_uiNext].m_uiPrev = psPA_PNS->m_asX1[uiIndex_Interval_0].m_uiPrev;
    psPA_PNS->m_asX1[psPA_PNS->m_asX1[uiIndex_Interval_1].m_uiPrev].m_uiNext = psPA_PNS->m_asX1[uiIndex_Interval_1].m_uiNext;
    psPA_PNS->m_asX1[psPA_PNS->m_asX1[uiIndex_Interval_1].m_uiNext].m_uiPrev = psPA_PNS->m_asX1[uiIndex_Interval_1].m_uiPrev;

    psPA_PNS->m_asX2[psPA_PNS->m_asX2[uiIndex_Interval_0].m_uiPrev].m_uiNext = psPA_PNS->m_asX2[uiIndex_Interval_0].m_uiNext;
    psPA_PNS->m_asX2[psPA_PNS->m_asX2[uiIndex_Interval_0].m_uiNext].m_uiPrev = psPA_PNS->m_asX2[uiIndex_Interval_0].m_uiPrev;
    psPA_PNS->m_asX2[psPA_PNS->m_asX2[uiIndex_Interval_1].m_uiPrev].m_uiNext = psPA_PNS->m_asX2[uiIndex_Interval_1].m_uiNext;
    psPA_PNS->m_asX2[psPA_PNS->m_asX2[uiIndex_Interval_1].m_uiNext].m_uiPrev = psPA_PNS->m_asX2[uiIndex_Interval_1].m_uiPrev;

    tgPA_Graph_PNS_Remove_Object_Contact_List( psPA_PNS, tiObject.m_uiI ); /**< Remove all pairs that contain this ID */
    TgERROR( KTgPA_PNS_MAX_CONTACT_PAIR == psPA_PNS->m_asObject[tiObject.m_uiI].m_uiContact_Linked_List_Head );

    return (KTgS_OK);
}


/* ---- tgPA_Graph_PNS_Object_Update_Interval ------------------------------------------------------------------------------------------------------------------------------------ */
/*  Searches for new overlapping pairs as indicated by overlap on a single axis.  The state of overlap on the other axes is  */
/* unknown and can already be in overlap, entering overlap or separated. */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgPA_Graph_PNS_Object_Update_Interval( STg2_PA_Graph__Prune_And_Sweep_PCU psPA_PNS, STg2_PA_Graph__PNS__Point_End_PCU psX, TgFLOAT32_C fOldMin,
                                                     TgFLOAT32_C fOldMax, TgFLOAT32_C fNewMin, TgFLOAT32_C fNewMax, TgPARTITION_OBJECT_ID_C tiObject )
{
    /* Local assignments of the min and max positions along the axis for the initial and final AABBs */

    TgUINT_E16_C                        uiIndex_Interval_0 = 2 * (TgUINT_E16)tiObject.m_uiI + 0u;
    TgUINT_E16_C                        uiIndex_Interval_1 = 2 * (TgUINT_E16)tiObject.m_uiI + 1u;
    TgUINT_E64_C                        uiCategory_0 = psPA_PNS->m_asObject[tiObject.m_uiI].m_uiCategory;
    TgUINT_E64_C                        uiCollide_0 = psPA_PNS->m_asObject[tiObject.m_uiI].m_uiCollide;

    TgUINT_E16                          uiInsert;

    if (fOldMin > fNewMin && uiIndex_Interval_0 != psX[KTgPA_PNS_MAX_INTERVAL].m_uiNext) /**< Moving down the number line (projection) */
    {
        uiInsert = psX[uiIndex_Interval_0].m_uiPrev;

        for (; uiInsert < KTgPA_PNS_MAX_INTERVAL && psX[uiInsert].m_fVal > fNewMin; uiInsert = psX[uiInsert].m_uiPrev)
        {
            TgRSIZE_C       uiTest_Object = (TgRSIZE)(uiInsert >> 1u);

            if (!psX[uiTest_Object].m_bMax)
            {
                continue;
            }
            else
            {
                TgUINT_E64_C                        uiCategory_1 = psPA_PNS->m_asObject[uiTest_Object].m_uiCategory;
                TgUINT_E64_C                        uiCollide_1 = psPA_PNS->m_asObject[uiTest_Object].m_uiCollide;

                TgDIAG(uiTest_Object != tiObject.m_uiI);

                if (   0 != ((uiCategory_0 & uiCollide_1) & KTgPA_CATEGORY_BIT_MASK__AND_TEST)
                    && 0 != ((uiCategory_1 & uiCollide_0) & KTgPA_CATEGORY_BIT_MASK__AND_TEST)
                    && 0 != (((uiCategory_0 & uiCollide_1) | (uiCategory_1 & uiCollide_0)) & KTgPA_CATEGORY_BIT_MASK__OR_TEST)
                    && tgCO_BA_Test_BA_F32_04( &psPA_PNS->m_asObject[uiTest_Object].m_sBA, &psPA_PNS->m_asObject[tiObject.m_uiI].m_sBA ))
                {
                    tgPA_Graph_PNS_Pair_Push( psPA_PNS, tiObject.m_uiI, uiTest_Object );
                };
            };
        };

        tgPA_Graph_PNS_Interval_Update( psX, uiIndex_Interval_0, psX[uiInsert].m_uiNext );
    }
    else if (fOldMin < fNewMin) /**< Moving up the number line (projection) */
    {
        uiInsert = psX[uiIndex_Interval_0].m_uiNext;

        for (; uiInsert < KTgPA_PNS_MAX_INTERVAL && psX[uiInsert].m_fVal < fNewMin; uiInsert = psX[uiInsert].m_uiNext)
        {
            TgRSIZE_C       uiTest_Object = (TgRSIZE)(uiInsert >> 1);

            if (!psX[uiTest_Object].m_bMax || uiTest_Object == tiObject.m_uiI) /* Min point can iterate past the previous Max point. */
            {
                continue;
            }
            else
            {
                TgUINT_E64_C                        uiCategory_1 = psPA_PNS->m_asObject[uiTest_Object].m_uiCategory;
                TgUINT_E64_C                        uiCollide_1 = psPA_PNS->m_asObject[uiTest_Object].m_uiCollide;

                if (   0 != ((uiCategory_0 & uiCollide_1) & KTgPA_CATEGORY_BIT_MASK__AND_TEST)
                    && 0 != ((uiCategory_1 & uiCollide_0) & KTgPA_CATEGORY_BIT_MASK__AND_TEST)
                    && 0 != (((uiCategory_0 & uiCollide_1) | (uiCategory_1 & uiCollide_0)) & KTgPA_CATEGORY_BIT_MASK__OR_TEST)
                    && tgCO_BA_Test_BA_F32_04( &psPA_PNS->m_asObject[uiTest_Object].m_sBA, &psPA_PNS->m_asObject[tiObject.m_uiI].m_sBA ))
                {
                    tgPA_Graph_PNS_Pair_Push( psPA_PNS, tiObject.m_uiI, uiTest_Object );
                };
            };
        };

        tgPA_Graph_PNS_Interval_Update( psX, uiIndex_Interval_0, uiInsert );
    };

    psX[uiIndex_Interval_0].m_fVal = fNewMin; /**< Update the interval value */

    if (fOldMax > fNewMax && uiIndex_Interval_1 != psX[KTgPA_PNS_MAX_INTERVAL].m_uiNext) /**< Moving down the number line (projection) */
    {
        uiInsert = psX[uiIndex_Interval_1].m_uiPrev;

        for (; uiInsert < KTgPA_PNS_MAX_INTERVAL && psX[uiInsert].m_fVal > fNewMax; uiInsert = psX[uiInsert].m_uiPrev)
        {
            TgRSIZE_C       uiTest_Object = (TgRSIZE)(uiInsert >> 1);

            if (psX[uiTest_Object].m_bMax)
            {
                continue;
            }
            else
            {
                TgUINT_E64_C                        uiCategory_1 = psPA_PNS->m_asObject[uiTest_Object].m_uiCategory;
                TgUINT_E64_C                        uiCollide_1 = psPA_PNS->m_asObject[uiTest_Object].m_uiCollide;

                TgDIAG(uiTest_Object != tiObject.m_uiI);

                if (   0 != ((uiCategory_0 & uiCollide_1) & KTgPA_CATEGORY_BIT_MASK__AND_TEST)
                    && 0 != ((uiCategory_1 & uiCollide_0) & KTgPA_CATEGORY_BIT_MASK__AND_TEST)
                    && 0 != (((uiCategory_0 & uiCollide_1) | (uiCategory_1 & uiCollide_0)) & KTgPA_CATEGORY_BIT_MASK__OR_TEST)
                    && tgCO_BA_Test_BA_F32_04( &psPA_PNS->m_asObject[uiTest_Object].m_sBA, &psPA_PNS->m_asObject[tiObject.m_uiI].m_sBA ))
                {
                    tgPA_Graph_PNS_Pair_Push( psPA_PNS, tiObject.m_uiI, uiTest_Object );
                };
            };
        };

        tgPA_Graph_PNS_Interval_Update( psX, uiIndex_Interval_1, psX[uiInsert].m_uiNext );
    }
    else if (fOldMax < fNewMax) /**< Moving up the number line (projection) */
    {
        uiInsert = psX[uiIndex_Interval_1].m_uiNext;

        for (; uiInsert < KTgPA_PNS_MAX_INTERVAL && psX[uiInsert].m_fVal < fNewMax; uiInsert = psX[uiInsert].m_uiNext)
        {
            TgRSIZE_C       uiTest_Object = (TgRSIZE)(uiInsert >> 1);

            if (psX[uiTest_Object].m_bMax || uiTest_Object == tiObject.m_uiI) /* Max point can iterate past the new Min point. */
            {
                continue;
            }
            else
            {
                TgUINT_E64_C                        uiCategory_1 = psPA_PNS->m_asObject[uiTest_Object].m_uiCategory;
                TgUINT_E64_C                        uiCollide_1 = psPA_PNS->m_asObject[uiTest_Object].m_uiCollide;

                if (   0 != ((uiCategory_0 & uiCollide_1) & KTgPA_CATEGORY_BIT_MASK__AND_TEST)
                    && 0 != ((uiCategory_1 & uiCollide_0) & KTgPA_CATEGORY_BIT_MASK__AND_TEST)
                    && 0 != (((uiCategory_0 & uiCollide_1) | (uiCategory_1 & uiCollide_0)) & KTgPA_CATEGORY_BIT_MASK__OR_TEST)
                    && tgCO_BA_Test_BA_F32_04( &psPA_PNS->m_asObject[uiTest_Object].m_sBA, &psPA_PNS->m_asObject[tiObject.m_uiI].m_sBA ))
                {
                    tgPA_Graph_PNS_Pair_Push( psPA_PNS, tiObject.m_uiI, uiTest_Object );
                };
            };
        };

        tgPA_Graph_PNS_Interval_Update( psX, uiIndex_Interval_1, uiInsert );
    };

    psX[uiIndex_Interval_1].m_fVal = fNewMax; /**< Update the interval value */
}


/* ---- tgPA_Graph_PNS_Interval_Push --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgPA_Graph_PNS_Interval_Push( STg2_PA_Graph__PNS__Point_End_PCU psX, TgFLOAT32_C fMin, TgFLOAT32_C fMax, TgRSIZE_C uiIndex_Object )
{
    TgUINT_E16                          uiIndex_Interval_0, uiIndex_Interval_1, uiAxis_Index, uiPrev_Axis_Index;

    TgPARAM_CHECK( uiIndex_Object < (KTgMAX_U16 >> 2) - 2 );

    uiIndex_Interval_0 = 2 * (TgUINT_E16)uiIndex_Object + 0u;
    uiIndex_Interval_1 = 2 * (TgUINT_E16)uiIndex_Object + 1u;
    uiAxis_Index = psX[KTgPA_PNS_MAX_INTERVAL].m_uiNext;

    for (; uiAxis_Index < KTgPA_PNS_MAX_INTERVAL && psX[uiAxis_Index].m_fVal < fMin; uiAxis_Index = psX[uiAxis_Index].m_uiNext);

    uiPrev_Axis_Index = psX[uiAxis_Index].m_uiPrev;

    psX[uiIndex_Interval_0].m_fVal = fMin;
    psX[uiIndex_Interval_0].m_uiPrev = uiPrev_Axis_Index;
    psX[uiIndex_Interval_0].m_uiNext = uiAxis_Index;
    psX[uiIndex_Interval_0].m_bMax = 0;

    psX[uiPrev_Axis_Index].m_uiNext = uiIndex_Interval_0;
    if (KTgPA_PNS_MAX_INTERVAL != uiAxis_Index)
    {
        psX[uiAxis_Index].m_uiPrev = uiIndex_Interval_0;
    };

    for (; uiAxis_Index < KTgPA_PNS_MAX_INTERVAL && psX[uiAxis_Index].m_fVal < fMax; uiAxis_Index = psX[uiAxis_Index].m_uiNext);

    uiPrev_Axis_Index = psX[uiAxis_Index].m_uiPrev;

    psX[uiIndex_Interval_1].m_fVal = fMax;
    psX[uiIndex_Interval_1].m_uiPrev = uiPrev_Axis_Index;
    psX[uiIndex_Interval_1].m_uiNext = uiAxis_Index;
    psX[uiIndex_Interval_1].m_bMax = 1;

    psX[uiPrev_Axis_Index].m_uiNext = uiIndex_Interval_1;
    if (KTgPA_PNS_MAX_INTERVAL != uiAxis_Index)
    {
        psX[uiAxis_Index].m_uiPrev = uiIndex_Interval_1;
    };
}


/* ---- tgPA_Graph_PNS_Interval_Update ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgPA_Graph_PNS_Interval_Update( STg2_PA_Graph__PNS__Point_End_PCU psX, TgUINT_E16_C uiVal, TgUINT_E16_C uiInsert )
{
    TgUINT_E16_C                        uiPrev = psX[uiInsert].m_uiPrev;

    if ((uiVal == uiInsert) || (uiVal == uiPrev))
    {
        return;
    }

    TgERROR( uiVal != uiPrev && uiVal != uiInsert && uiPrev != uiInsert );

    /* Cut the element out of the list */

    psX[psX[uiVal].m_uiPrev].m_uiNext = psX[uiVal].m_uiNext;
    psX[psX[uiVal].m_uiNext].m_uiPrev = psX[uiVal].m_uiPrev;

    /* Stitch the element into its new position */

    psX[uiVal].m_uiPrev = uiPrev;
    psX[uiVal].m_uiNext = uiInsert;
    psX[uiPrev].m_uiNext = uiVal;
    psX[uiInsert].m_uiPrev = uiVal;
}


/* ---- tgPA_Graph_PNS_Pair_Push ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgBOOL tgPA_Graph_PNS_Pair_Push( STg2_PA_Graph__Prune_And_Sweep_PCU psPA_PNS, TgRSIZE_C uiIndex_Object_0, TgRSIZE_C uiIndex_Object_1 )
{
    TgRSIZE                             uiNext_Empty;

    TgPARAM_CHECK( uiIndex_Object_0 < KTgPA_PNS_MAX_OBJECTS );
    TgPARAM_CHECK( uiIndex_Object_1 < KTgPA_PNS_MAX_OBJECTS );
    TgPARAM_CHECK( psPA_PNS->m_uiEmpty < KTgPA_PNS_MAX_CONTACT_PAIR );
    TgPARAM_CHECK( uiIndex_Object_0 != uiIndex_Object_1 );

    if (KTgPA_PNS_MAX_CONTACT_PAIR == psPA_PNS->m_uiEmpty)
    {
        tgCN_PrintF( KTgCN_CHANEL_CRITICAL, u8"%-16.16s(%-32.32s): Out of Memory - Can not store pair.\n", u8"Partition: PnS", u8"Pair_Push" );
        return (false);
    };

    uiNext_Empty = psPA_PNS->m_asContact_Pair[psPA_PNS->m_uiEmpty].m_uiContact_Next;

    /* Push this contact onto the object-pair stack */
    psPA_PNS->m_asContact_Pair[psPA_PNS->m_uiEmpty].m_uiCallbackID_0 = psPA_PNS->m_asObject[uiIndex_Object_0].m_uiCallbackID;
    psPA_PNS->m_asContact_Pair[psPA_PNS->m_uiEmpty].m_uiCallbackID_1 = psPA_PNS->m_asObject[uiIndex_Object_1].m_uiCallbackID;
    psPA_PNS->m_asContact_Pair[psPA_PNS->m_uiEmpty].m_bPaired_Contact = false;
    psPA_PNS->m_asContact_Pair[psPA_PNS->m_uiEmpty].m_uiObject_Index = uiIndex_Object_1;
    TgDIAG(0 != psPA_PNS->m_asContact_Pair[psPA_PNS->m_uiEmpty].m_uiCallbackID_0);
    TgDIAG(0 != psPA_PNS->m_asContact_Pair[psPA_PNS->m_uiEmpty].m_uiCallbackID_1);

    psPA_PNS->m_asContact_Pair[psPA_PNS->m_uiEmpty].m_uiContact_Next = psPA_PNS->m_asObject[uiIndex_Object_0].m_uiContact_Linked_List_Head;
    psPA_PNS->m_asObject[uiIndex_Object_0].m_uiContact_Linked_List_Head = psPA_PNS->m_uiEmpty;
    psPA_PNS->m_uiEmpty = uiNext_Empty; /* Record the next available empty pair-ID */

    if (KTgPA_PNS_MAX_CONTACT_PAIR == psPA_PNS->m_uiEmpty)
    {
        tgCN_PrintF( KTgCN_CHANEL_CRITICAL, u8"%-16.16s(%-32.32s): Out of Memory - Can not store pair.\n", u8"Partition: PnS", u8"Pair_Push" );
        return (false);
    };

    uiNext_Empty = psPA_PNS->m_asContact_Pair[psPA_PNS->m_uiEmpty].m_uiContact_Next;

    /* Push this contact onto the object-pair stack */
    psPA_PNS->m_asContact_Pair[psPA_PNS->m_uiEmpty].m_uiCallbackID_0 = psPA_PNS->m_asObject[uiIndex_Object_1].m_uiCallbackID;
    psPA_PNS->m_asContact_Pair[psPA_PNS->m_uiEmpty].m_uiCallbackID_1 = psPA_PNS->m_asObject[uiIndex_Object_0].m_uiCallbackID;
    psPA_PNS->m_asContact_Pair[psPA_PNS->m_uiEmpty].m_bPaired_Contact = true;
    psPA_PNS->m_asContact_Pair[psPA_PNS->m_uiEmpty].m_uiObject_Index = uiIndex_Object_0;
    TgDIAG(0 != psPA_PNS->m_asContact_Pair[psPA_PNS->m_uiEmpty].m_uiCallbackID_0);
    TgDIAG(0 != psPA_PNS->m_asContact_Pair[psPA_PNS->m_uiEmpty].m_uiCallbackID_1);

    psPA_PNS->m_asContact_Pair[psPA_PNS->m_uiEmpty].m_uiContact_Next = psPA_PNS->m_asObject[uiIndex_Object_1].m_uiContact_Linked_List_Head;
    psPA_PNS->m_asObject[uiIndex_Object_1].m_uiContact_Linked_List_Head = psPA_PNS->m_uiEmpty;
    psPA_PNS->m_uiEmpty = uiNext_Empty; /* Record the next available empty pair-ID */

    return (true);
}


/* ---- tgPA_Graph_PNS_Remove_Contact_Pair --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgBOOL tgPA_Graph_PNS_Remove_Contact_Pair( STg2_PA_Graph__Prune_And_Sweep_PCU psPA_PNS, TgRSIZE_C uiIndex_Object_0, TgRSIZE_C uiIndex_Object_1 )
{
    TgRSIZE                             uiContact_Index, uiPrev_Contact_Index;

    uiContact_Index = psPA_PNS->m_asObject[uiIndex_Object_0].m_uiContact_Linked_List_Head;
    if (KTgPA_PNS_MAX_CONTACT_PAIR == uiContact_Index)
    {
        return (false);
    };

    uiPrev_Contact_Index = KTgPA_PNS_MAX_CONTACT_PAIR;
    for (; KTgPA_PNS_MAX_CONTACT_PAIR != uiContact_Index; uiPrev_Contact_Index = uiContact_Index, uiContact_Index = psPA_PNS->m_asContact_Pair[uiContact_Index].m_uiContact_Next)
    {
        if (uiIndex_Object_1 == psPA_PNS->m_asContact_Pair[uiContact_Index].m_uiObject_Index)
        {
            if (KTgPA_PNS_MAX_CONTACT_PAIR == uiPrev_Contact_Index)
            {
                psPA_PNS->m_asObject[uiIndex_Object_0].m_uiContact_Linked_List_Head = psPA_PNS->m_asContact_Pair[uiContact_Index].m_uiContact_Next;
            }
            else
            {
                psPA_PNS->m_asContact_Pair[uiPrev_Contact_Index].m_uiContact_Next = psPA_PNS->m_asContact_Pair[uiContact_Index].m_uiContact_Next;
            };

            /* Push the object-pair onto the empty stack */
            psPA_PNS->m_asContact_Pair[uiContact_Index].m_uiContact_Next = psPA_PNS->m_uiEmpty;
            psPA_PNS->m_asContact_Pair[uiContact_Index].m_uiCallbackID_0 = 0;
            psPA_PNS->m_asContact_Pair[uiContact_Index].m_uiCallbackID_1 = 0;
            psPA_PNS->m_uiEmpty = uiContact_Index;
            return (true);
        };
    };
    return false;
}


/* ---- tgPA_Graph_PNS_Remove_Object_Contact_List -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgPA_Graph_PNS_Remove_Object_Contact_List( STg2_PA_Graph__Prune_And_Sweep_PCU psPA_PNS, TgRSIZE_C uiIndex_Object )
{
    TgRSIZE                             uiContact_Index;
    TgPARTITION_OBJECT_ID               tiObject;

    uiContact_Index = psPA_PNS->m_asObject[uiIndex_Object].m_uiContact_Linked_List_Head;
    if (KTgPA_PNS_MAX_CONTACT_PAIR == uiContact_Index)
    {
        return; /* No Contact Pairs for this object */
    };

    tiObject = tgPARTITION_OBJECT_ID_Query_Unsafe( &psPA_PNS->m_asObject[uiIndex_Object].m_tiObject_Singleton );
    while (1)
    {
        /* The entire contact pair linked list for this object will be added to the empty list, but need to find all pairs in corresponding objects */

        TgVERIFY(tgPA_Graph_PNS_Remove_Contact_Pair( psPA_PNS, psPA_PNS->m_asContact_Pair[uiContact_Index].m_uiObject_Index, tiObject.m_uiI ));
        psPA_PNS->m_asContact_Pair[uiContact_Index].m_uiCallbackID_0 = 0;
        psPA_PNS->m_asContact_Pair[uiContact_Index].m_uiCallbackID_1 = 0;

        /* Check to see if this is the final node and then add the entire contact list from this object to the free list. */

        if (KTgPA_PNS_MAX_CONTACT_PAIR == psPA_PNS->m_asContact_Pair[uiContact_Index].m_uiContact_Next)
        {
            psPA_PNS->m_asContact_Pair[uiContact_Index].m_uiContact_Next = psPA_PNS->m_uiEmpty;
            psPA_PNS->m_uiEmpty = psPA_PNS->m_asObject[uiIndex_Object].m_uiContact_Linked_List_Head;
            break;
        }
        else
        {
            uiContact_Index = psPA_PNS->m_asContact_Pair[uiContact_Index].m_uiContact_Next;
        };
    };

    psPA_PNS->m_asObject[uiIndex_Object].m_uiContact_Linked_List_Head = KTgPA_PNS_MAX_CONTACT_PAIR; /* Clear the object-pair list */
}
