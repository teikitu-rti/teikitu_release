/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Event MGR [Time Event].c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "TgS Common - Event MGR - Internal.h"
#include "TgS Common - Event MGR.inl"


/* == Common ===================================================================================================================================================================== */

/** ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    @ingroup TGS_COMMON_EVENT_MGR
    @details <b>Life Time Sequence</b>

    \b Birth: Check to see if there are available allocations in a pool.  The free list of pools should contain a sorted linked list with priority given to entries with the
    most used allocations.  We want to encourage as much density as possible during the update.  Once a pool has been acquired (created or locked from the free list) the first
    available item from the pools free list will be used for the new entity.  Once it has been initialized and set, the object is added to the new stack for insertion to the
    processing lists on the next update.
    [Free -> New Stack]

    \b  Life: Access is always controlled through the 1:1 matching lock lists to the data.  There is a spin lock and associated identity value for each item.  The ids are a
    combination pool | index pair and a generated key value to prevent issues with stale ids being passed into the system.  The spin lock needs to be acquired and the ids match
    before gaining access to the data.  Keep in mind that this is probably a 2000+ cycle operation (memory miss on both the spin lock and id value).
    [New Stack -> Waiting -> Processing]

    \b  Death: The lock for the entity is invalidated and the object marked to be removed.  Since the entity is contained within lists that are access isolated, the removal
    from the list has to be done on the update.  Once a list of all the deleted entities is generated during the update, they will be added in index priority to the free list.
    Keep in mind once marked for deletion, since the id key is invalidated, no further use of the object will be possible.
    [Processing -> Free]

   ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- Time Event - Frame ------------------------------------------------------------------------------------------------------------------------------------------------------- */

/* ---- tgEM_TE_FRM_NEW ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgEM_TE_FRM_ID tgEM_TE_FRM_NEW( TgFCN_EM_CALLBACK pfnCallback, TgUINT_PTR_C uiParam, TgSINT_F32_C iStart, TgSINT_F32_C iEnd )
{
    TgSINT_F32                          iPool, iIndex;
    STg2_EM_TE_Pool_P                   psPool;
    TgEM_TE_FRM_ID_SINGLETON            xtiTE_Singleton;

    if (nullptr == pfnCallback || iStart < 0 || iEnd < 0)
    {
        return (KTgEM_TE_FRM_ID__INVALID);
    };

    tgCM_UT_LF__SN__Lock_Spin( &g_sEM_TE_FRM_Lock.m_sLock );

    /* Check to see if we need to allocate a new pool into the pool list */
    if (nullptr == g_psEM_TE_FRM_Free_List)
    {
        /* Find an available pool slot */
        for (iPool = 0; iPool < KTgEM_MAX_TE_FRM_POOL && nullptr != g_apsEM_TE_FRM[iPool]; ++iPool) {};
        TgCRITICAL( iPool < KTgEM_MAX_TE_FRM_POOL );

        /* Allocate and initialize a new pool */
        psPool = (STg2_EM_TE_Pool_P)TgMALLOC_POOL( sizeof( STg2_EM_TE_Pool ) );
        tgEM_TP_Init( psPool );
        psPool->m_iPool = iPool;
        psPool->m_niUsed = 1;

        tgCM_UT_LF__SN__Lock_Spin( &g_asEM_TE_FRM_NewDel_Lock[iPool].m_sLock );

        /* Assign the new pool into the array list, and as the free pool */
        g_psEM_TE_FRM_Free_List = psPool;
        g_apsEM_TE_FRM[iPool] = psPool;
    }
    else
    {
        psPool = (STg2_EM_TE_Pool_P)g_psEM_TE_FRM_Free_List;
        iPool = g_psEM_TE_FRM_Free_List->m_iPool;

        tgCM_UT_LF__SN__Lock_Spin( &g_asEM_TE_FRM_NewDel_Lock[iPool].m_sLock );

        TgERROR(psPool == g_apsEM_TE_FRM[iPool]);
        ++g_psEM_TE_FRM_Free_List->m_niUsed;

        /* Check to see if we have filled this pool (to remove from the free list */
        if (g_psEM_TE_FRM_Free_List->m_niUsed >= KTgEM_NUM_TE_IN_POOL)
        {
            g_psEM_TE_FRM_Free_List = g_psEM_TE_FRM_Free_List->m_psFree_Next;
            g_psEM_TE_FRM_Free_List->m_psFree_Next = nullptr;
        };
    };

    tgCM_UT_LF__SN__Signal( &g_sEM_TE_FRM_Lock.m_sLock );

    /* Remove the head of the free list for the allocation */
    iIndex = (TgSINT_F32 )(psPool->m_psFree - psPool->m_asTB);
    psPool->m_psFree = psPool->m_psFree->m_psHead_Next;
    tgCM_UT_LF__SN__Signal( &g_asEM_TE_FRM_NewDel_Lock[iPool].m_sLock );

    psPool->m_atiEM_TE_FRM_NoSingleton[iIndex] = tgEM_TE_FRM_ID_Init( &xtiTE_Singleton, (TgUINT_F32)((iPool << 16) | iIndex) );

    /* Initialize and acquire the look */
    psPool->m_asTB[iIndex].m_psHead_Next = nullptr;
    psPool->m_asTB[iIndex].m_fStart = -1.0F;
    psPool->m_asTB[iIndex].m_fEnd = -1.0F;
    psPool->m_asTB[iIndex].m_iStart = iStart;
    psPool->m_asTB[iIndex].m_iEnd = iEnd;
    psPool->m_asTB[iIndex].m_uiLocal_Index = psPool->m_atiEM_TE_FRM_NoSingleton[iIndex].m_uiI;
    psPool->m_asTB[iIndex].m_bfFlags = 0;

    psPool->m_asTE[iIndex].m_pfnCallback = pfnCallback;
    psPool->m_asTE[iIndex].m_uiParam = uiParam;

    atomic_thread_fence( cxx__memory_order_seq_cst );

    tgCM_UT_LF__ST__Push( &psPool->m_sNew, &psPool->m_asTB[iIndex].m_sHead_Next );

    return (psPool->m_atiEM_TE_FRM_NoSingleton[iIndex]);
}


/* ---- tgEM_TE_FRM_DEL ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgEM_TE_FRM_DEL( TgEM_TE_FRM_ID tiTE )
{
    TgUINT_F32                        uiIndex, uiPool;

    uiIndex = tiTE.m_uiI & 0xFFFF;
    uiPool = tiTE.m_uiI >> 16;

    if (TgFAILED( tgEM_TE_FRM_Lock( tiTE, uiPool, uiIndex ) ))
    {
        return (KTgE_FAIL);
    };

    TgPARAM_CHECK_INDEX( uiIndex, g_apsEM_TE_FRM[uiPool]->m_atiEM_TE_FRM_NoSingleton );

    /* Invalidate the item from further acquires (may have to add a data cache flush) */
    g_apsEM_TE_FRM[uiPool]->m_atiEM_TE_FRM_NoSingleton[uiIndex].m_uiKI = KTgID__INVALID_VALUE;

    /* Mark it for removal list by the next update */
    g_apsEM_TE_FRM[uiPool]->m_asTB[uiIndex].m_iStart = 0;
    g_apsEM_TE_FRM[uiPool]->m_asTB[uiIndex].m_iEnd = 0;
    tgEM_TB_Set_Paused( g_apsEM_TE_FRM[uiPool]->m_asTB + uiIndex, false );

    tgCM_UT_LF__SN__Signal( &g_asEM_TE_FRM_Data_Lock[uiPool].m_sLock );
    return (KTgS_OK);
}


/* ---- tgEM_TE_FRM_Set_Pause ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgEM_TE_FRM_Set_Pause( TgEM_TE_FRM_ID tiTE, TgBOOL_C bPause )
{
    TgUINT_F32                        uiIndex, uiPool;

    uiIndex = tiTE.m_uiI & 0xFFFF;
    uiPool = tiTE.m_uiI >> 16;

    if (TgFAILED( tgEM_TE_FRM_Lock( tiTE, uiPool, uiIndex ) ))
    {
        return (KTgE_FAIL);
    };

    tgEM_TB_Set_Paused( g_apsEM_TE_FRM[uiPool]->m_asTB + uiIndex, bPause );
    tgCM_UT_LF__SN__Signal( &g_asEM_TE_FRM_Data_Lock[uiPool].m_sLock );
    return (KTgS_OK);
}


/* ---- tgEM_TE_FRM_Set_Start_Frame ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgEM_TE_FRM_Set_Start_Frame( TgEM_TE_FRM_ID tiTE, TgSINT_F32_C iFrame )
{
    TgUINT_F32                        uiIndex, uiPool;

    uiIndex = tiTE.m_uiI & 0xFFFF;
    uiPool = tiTE.m_uiI >> 16;

    if (TgFAILED( tgEM_TE_FRM_Lock( tiTE, uiPool, uiIndex ) ))
    {
        return (KTgE_FAIL);
    };

    TgPARAM_CHECK_INDEX( uiIndex, g_apsEM_TE_FRM[uiPool]->m_asTB );

    if (tgEM_TB_Is_Active( g_apsEM_TE_FRM[uiPool]->m_asTB + uiIndex ))
    {
        tgCM_UT_LF__SN__Signal( &g_asEM_TE_FRM_Data_Lock[uiPool].m_sLock );
        return (KTgE_FAIL);
    }

    g_apsEM_TE_FRM[uiPool]->m_asTB[uiIndex].m_iStart = iFrame;
    tgCM_UT_LF__SN__Signal( &g_asEM_TE_FRM_Data_Lock[uiPool].m_sLock );
    return (KTgS_OK);
}


/* ---- tgEM_TE_FRM_Set_End_Frame ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgEM_TE_FRM_Set_End_Frame( TgEM_TE_FRM_ID tiTE, TgSINT_F32_C iFrame )
{
    TgUINT_F32                        uiIndex, uiPool;

    uiIndex = tiTE.m_uiI & 0xFFFF;
    uiPool = tiTE.m_uiI >> 16;

    if (TgFAILED( tgEM_TE_FRM_Lock( tiTE, uiPool, uiIndex ) ))
    {
        return (KTgE_FAIL);
    };

    TgPARAM_CHECK_INDEX( uiIndex, g_apsEM_TE_FRM[uiPool]->m_asTB );

    g_apsEM_TE_FRM[uiPool]->m_asTB[uiIndex].m_iEnd = tgCM_MAX_S32( g_apsEM_TE_FRM[uiPool]->m_asTB[uiIndex].m_iStart, iFrame );
    tgCM_UT_LF__SN__Signal( &g_asEM_TE_FRM_Data_Lock[uiPool].m_sLock );
    return (KTgS_OK);
}


/* ---- tgEM_TE_FRM_Set_Frame_To_Live -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgEM_TE_FRM_Set_Frame_To_Live( TgEM_TE_FRM_ID tiTE, TgSINT_F32_C iFrame )
{
    TgUINT_F32                        uiIndex, uiPool;

    uiIndex = tiTE.m_uiI & 0xFFFF;
    uiPool = tiTE.m_uiI >> 16;

    if (TgFAILED( tgEM_TE_FRM_Lock( tiTE, uiPool, uiIndex ) ))
    {
        return (KTgE_FAIL);
    };

    TgPARAM_CHECK_INDEX( uiIndex, g_apsEM_TE_FRM[uiPool]->m_asTB );

    g_apsEM_TE_FRM[uiPool]->m_asTB[uiIndex].m_iEnd = tgGB_Query_Total_Frame() + iFrame;
    tgCM_UT_LF__SN__Signal( &g_asEM_TE_FRM_Data_Lock[uiPool].m_sLock );
    return (KTgS_OK);
}


/* ---- tgEM_TE_FRM_Query_Valid -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgEM_TE_FRM_Query_Valid( TgEM_TE_FRM_ID tiTE )
{
    TgUINT_F32                        uiIndex, uiPool;

    uiIndex = tiTE.m_uiI & 0xFFFF;
    uiPool = tiTE.m_uiI >> 16;

    if (TgFAILED( tgEM_TE_FRM_Lock( tiTE, uiPool, uiIndex ) ))
    {
        return (false);
    };

    tgCM_UT_LF__SN__Signal( &g_asEM_TE_FRM_Data_Lock[uiPool].m_sLock );
    return (true);
}


/* ---- tgEM_TE_FRM_Query_Paused ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgEM_TE_FRM_Query_Paused( TgBOOL_PCU pbPaused, TgEM_TE_FRM_ID tiTE )
{
    TgUINT_F32                        uiIndex, uiPool;

    TgPARAM_CHECK(nullptr != pbPaused);

    uiIndex = tiTE.m_uiI & 0xFFFF;
    uiPool = tiTE.m_uiI >> 16;

    if (TgFAILED( tgEM_TE_FRM_Lock( tiTE, uiPool, uiIndex ) ))
    {
        return (KTgE_FAIL);
    };

    TgPARAM_CHECK_INDEX( uiIndex, g_apsEM_TE_FRM[uiPool]->m_asTB );

    *pbPaused = tgEM_TB_Is_Paused( g_apsEM_TE_FRM[uiPool]->m_asTB + uiIndex );
    tgCM_UT_LF__SN__Signal( &g_asEM_TE_FRM_Data_Lock[uiPool].m_sLock );
    return (KTgS_OK);
}


/* ---- tgEM_TE_FRM_Query_Start_Frame -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgEM_TE_FRM_Query_Start_Frame( TgSINT_F32_PCU piFrame, TgEM_TE_FRM_ID tiTE )
{
    TgUINT_F32                        uiIndex, uiPool;

    TgPARAM_CHECK(nullptr != piFrame);

    uiIndex = tiTE.m_uiI & 0xFFFF;
    uiPool = tiTE.m_uiI >> 16;

    if (TgFAILED( tgEM_TE_FRM_Lock( tiTE, uiPool, uiIndex ) ))
    {
        return (KTgE_FAIL);
    };

    TgPARAM_CHECK_INDEX( uiIndex, g_apsEM_TE_FRM[uiPool]->m_asTB );

    *piFrame = g_apsEM_TE_FRM[uiPool]->m_asTB[uiIndex].m_iStart;
    tgCM_UT_LF__SN__Signal( &g_asEM_TE_FRM_Data_Lock[uiPool].m_sLock );
    return (KTgS_OK);
}


/* ---- tgEM_TE_FRM_Query_End_Frame ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgEM_TE_FRM_Query_End_Frame( TgSINT_F32_PCU piFrame, TgEM_TE_FRM_ID tiTE )
{
    TgUINT_F32                        uiIndex, uiPool;

    TgPARAM_CHECK(nullptr != piFrame);

    uiIndex = tiTE.m_uiI & 0xFFFF;
    uiPool = tiTE.m_uiI >> 16;

    if (TgFAILED( tgEM_TE_FRM_Lock( tiTE, uiPool, uiIndex ) ))
    {
        return (KTgE_FAIL);
    };

    TgPARAM_CHECK_INDEX( uiIndex, g_apsEM_TE_FRM[uiPool]->m_asTB );

    *piFrame = g_apsEM_TE_FRM[uiPool]->m_asTB[uiIndex].m_iEnd;
    tgCM_UT_LF__SN__Signal( &g_asEM_TE_FRM_Data_Lock[uiPool].m_sLock );
    return (KTgS_OK);
}


/* ---- tgEM_TE_FRM_Query_Frame_To_Live ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgEM_TE_FRM_Query_Frame_To_Live( TgSINT_F32_PCU piFrame, TgEM_TE_FRM_ID tiTE )
{
    TgUINT_F32                        uiIndex, uiPool;

    TgPARAM_CHECK(nullptr != piFrame);

    uiIndex = tiTE.m_uiI & 0xFFFF;
    uiPool = tiTE.m_uiI >> 16;

    if (TgFAILED( tgEM_TE_FRM_Lock( tiTE, uiPool, uiIndex ) ))
    {
        return (KTgE_FAIL);
    };

    TgPARAM_CHECK_INDEX( uiIndex, g_apsEM_TE_FRM[uiPool]->m_asTB );

    *piFrame = tgGB_Query_Total_Frame() - g_apsEM_TE_FRM[uiPool]->m_asTB[uiIndex].m_iEnd;
    tgCM_UT_LF__SN__Signal( &g_asEM_TE_FRM_Data_Lock[uiPool].m_sLock );
    return (KTgS_OK);
}




/* ---- Time Event - Time -------------------------------------------------------------------------------------------------------------------------------------------------------- */

/* ---- tgEM_TE_SEC_NEW ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgEM_TE_SEC_ID tgEM_TE_SEC_NEW( TgFCN_EM_CALLBACK pfnCallback, TgUINT_PTR_C uiParam, TgFLOAT32_C fStart, TgFLOAT32_C fEnd )
{
    TgSINT_F32                          iPool, iIndex;
    STg2_EM_TE_Pool_P                   psPool;
    TgEM_TE_SEC_ID_SINGLETON            xtiTE_Singleton;

    if (nullptr == pfnCallback)
    {
        return (KTgEM_TE_SEC_ID__INVALID);
    };

    tgCM_UT_LF__SN__Lock_Spin( &g_sEM_TE_SEC_Lock.m_sLock );

    /* Check to see if we need to allocate a new pool into the pool list */
    if (nullptr == g_psEM_TE_SEC_Free_List)
    {
        /* Find an available pool slot */
        for (iPool = 0; iPool < KTgEM_MAX_TE_SEC_POOL && nullptr != g_apsEM_TE_SEC[iPool]; ++iPool) {};
        TgCRITICAL( iPool < KTgEM_MAX_TE_SEC_POOL );

        /* Allocate and initialize a new pool */
        psPool = (STg2_EM_TE_Pool_P)TgMALLOC_POOL( sizeof( STg2_EM_TE_Pool ) );
        tgEM_TP_Init( psPool );
        psPool->m_iPool = iPool;
        psPool->m_niUsed = 1;

        tgCM_UT_LF__SN__Lock_Spin( &g_asEM_TE_SEC_NewDel_Lock[iPool].m_sLock );

        /* Assign the new pool into the array list, and as the free pool */
        g_psEM_TE_SEC_Free_List = psPool;
        g_apsEM_TE_SEC[iPool] = psPool;
    }
    else
    {
        psPool = (STg2_EM_TE_Pool_P)g_psEM_TE_SEC_Free_List;
        iPool = g_psEM_TE_SEC_Free_List->m_iPool;

        tgCM_UT_LF__SN__Lock_Spin( &g_asEM_TE_SEC_NewDel_Lock[iPool].m_sLock );

        TgERROR(psPool == g_apsEM_TE_SEC[iPool]);
        ++g_psEM_TE_SEC_Free_List->m_niUsed;

        /* Check to see if we have filled this pool (to remove from the free list */
        if (g_psEM_TE_SEC_Free_List->m_niUsed >= KTgEM_NUM_TE_IN_POOL)
        {
            g_psEM_TE_SEC_Free_List = g_psEM_TE_SEC_Free_List->m_psFree_Next;
            g_psEM_TE_SEC_Free_List->m_psFree_Next = nullptr;
        };
    };

    tgCM_UT_LF__SN__Signal( &g_sEM_TE_SEC_Lock.m_sLock );

    /* Remove the head of the free list for the allocation */
    iIndex = (TgSINT_F32 )(psPool->m_psFree - psPool->m_asTB);
    psPool->m_psFree = psPool->m_psFree->m_psHead_Next;
    tgCM_UT_LF__SN__Signal( &g_asEM_TE_SEC_NewDel_Lock[iPool].m_sLock );

    psPool->m_atiEM_TE_SEC_NoSingleton[iIndex] = tgEM_TE_SEC_ID_Init( &xtiTE_Singleton, (TgUINT_F32)((iPool << 16) | iIndex) );

    /* Initialize and acquire the look */
    psPool->m_asTB[iIndex].m_psHead_Next = nullptr;
    psPool->m_asTB[iIndex].m_fStart = fStart;
    psPool->m_asTB[iIndex].m_fEnd = fEnd;
    psPool->m_asTB[iIndex].m_iStart = -1;
    psPool->m_asTB[iIndex].m_iEnd = -1;
    psPool->m_asTB[iIndex].m_uiLocal_Index = psPool->m_atiEM_TE_SEC_NoSingleton[iIndex].m_uiI;
    psPool->m_asTB[iIndex].m_bfFlags = 0;

    psPool->m_asTE[iIndex].m_pfnCallback = pfnCallback;
    psPool->m_asTE[iIndex].m_uiParam = uiParam;

    atomic_thread_fence( cxx__memory_order_seq_cst );

    tgCM_UT_LF__ST__Push( &psPool->m_sNew, &psPool->m_asTB[iIndex].m_sHead_Next );

    return (psPool->m_atiEM_TE_SEC_NoSingleton[iIndex]);
}


/* ---- tgEM_TE_SEC_DEL ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgEM_TE_SEC_DEL( TgEM_TE_SEC_ID tiTE )
{
    TgUINT_F32                        uiIndex, uiPool;

    uiIndex = tiTE.m_uiI & 0xFFFF;
    uiPool = tiTE.m_uiI >> 16;

    if (TgFAILED( tgEM_TE_SEC_Lock( tiTE, uiPool, uiIndex ) ))
    {
        return (KTgE_FAIL);
    };

    TgPARAM_CHECK_INDEX( uiIndex, g_apsEM_TE_SEC[uiPool]->m_atiEM_TE_SEC_NoSingleton );

    /* Invalidate the item from further acquires (may have to add a data cache flush) */
    g_apsEM_TE_SEC[uiPool]->m_atiEM_TE_SEC_NoSingleton[uiIndex].m_uiKI = KTgID__INVALID_VALUE;

    /* Mark it for removal list by the next update */
    g_apsEM_TE_SEC[uiPool]->m_asTB[uiIndex].m_fStart = 0.0F;
    g_apsEM_TE_SEC[uiPool]->m_asTB[uiIndex].m_fEnd = 0.0F;
    tgEM_TB_Set_Paused( g_apsEM_TE_SEC[uiPool]->m_asTB + uiIndex, false );

    tgCM_UT_LF__SN__Signal( &g_asEM_TE_SEC_Data_Lock[uiPool].m_sLock );
    return (KTgS_OK);
}


/* ---- tgEM_TE_SEC_Set_Pause ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgEM_TE_SEC_Set_Pause( TgEM_TE_SEC_ID tiTE, TgBOOL_C bPause )
{
    TgUINT_F32                        uiIndex, uiPool;

    uiIndex = tiTE.m_uiI & 0xFFFF;
    uiPool = tiTE.m_uiI >> 16;

    if (TgFAILED( tgEM_TE_SEC_Lock( tiTE, uiPool, uiIndex ) ))
    {
        return (KTgE_FAIL);
    };

    TgPARAM_CHECK_INDEX( uiIndex, g_apsEM_TE_SEC[uiPool]->m_asTB );

    tgEM_TB_Set_Paused( g_apsEM_TE_SEC[uiPool]->m_asTB + uiIndex, bPause );
    tgCM_UT_LF__SN__Signal( &g_asEM_TE_SEC_Data_Lock[uiPool].m_sLock );
    return (KTgS_OK);
}


/* ---- tgEM_TE_SEC_Set_Start_Time ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgEM_TE_SEC_Set_Start_Time( TgEM_TE_SEC_ID tiTE, TgFLOAT32_C fTime )
{
    TgUINT_F32                        uiIndex, uiPool;

    uiIndex = tiTE.m_uiI & 0xFFFF;
    uiPool = tiTE.m_uiI >> 16;

    if (TgFAILED( tgEM_TE_SEC_Lock( tiTE, uiPool, uiIndex ) ))
    {
        return (KTgE_FAIL);
    };

    TgPARAM_CHECK_INDEX( uiIndex, g_apsEM_TE_SEC[uiPool]->m_asTB );

    if (tgEM_TB_Is_Active( g_apsEM_TE_SEC[uiPool]->m_asTB + uiIndex ))
    {
        tgCM_UT_LF__SN__Signal( &g_asEM_TE_SEC_Data_Lock[uiPool].m_sLock );
        return (KTgE_FAIL);
    }

    g_apsEM_TE_SEC[uiPool]->m_asTB[uiIndex].m_fStart = fTime;
    tgCM_UT_LF__SN__Signal( &g_asEM_TE_SEC_Data_Lock[uiPool].m_sLock );
    return (KTgS_OK);
}


/* ---- tgEM_TE_SEC_Set_End_Time ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgEM_TE_SEC_Set_End_Time( TgEM_TE_SEC_ID tiTE, TgFLOAT32_C fTime )
{
    TgUINT_F32                        uiIndex, uiPool;

    uiIndex = tiTE.m_uiI & 0xFFFF;
    uiPool = tiTE.m_uiI >> 16;

    if (TgFAILED( tgEM_TE_SEC_Lock( tiTE, uiPool, uiIndex ) ))
    {
        return (KTgE_FAIL);
    };

    TgPARAM_CHECK_INDEX( uiIndex, g_apsEM_TE_SEC[uiPool]->m_asTB );

    g_apsEM_TE_SEC[uiPool]->m_asTB[uiIndex].m_fEnd = tgCM_MAX_F32( g_apsEM_TE_SEC[uiPool]->m_asTB[uiIndex].m_fStart, fTime );
    tgCM_UT_LF__SN__Signal( &g_asEM_TE_SEC_Data_Lock[uiPool].m_sLock );
    return (KTgS_OK);
}


/* ---- tgEM_TE_SEC_Set_Time_To_Live --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgEM_TE_SEC_Set_Time_To_Live( TgEM_TE_SEC_ID tiTE, TgFLOAT32_C fTime )
{
    TgUINT_F32                        uiIndex, uiPool;

    uiIndex = tiTE.m_uiI & 0xFFFF;
    uiPool = tiTE.m_uiI >> 16;

    if (TgFAILED( tgEM_TE_SEC_Lock( tiTE, uiPool, uiIndex ) ))
    {
        return (KTgE_FAIL);
    };

    TgPARAM_CHECK_INDEX( uiIndex, g_apsEM_TE_SEC[uiPool]->m_asTB );

    g_apsEM_TE_SEC[uiPool]->m_asTB[uiIndex].m_fEnd = tgGB_Query_Total_Time() + fTime;
    tgCM_UT_LF__SN__Signal( &g_asEM_TE_SEC_Data_Lock[uiPool].m_sLock );
    return (KTgS_OK);
}


/* ---- tgEM_TE_SEC_Query_Valid -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgEM_TE_SEC_Query_Valid( TgEM_TE_SEC_ID tiTE )
{
    TgUINT_F32                        uiIndex, uiPool;

    uiIndex = tiTE.m_uiI & 0xFFFF;
    uiPool = tiTE.m_uiI >> 16;

    if (TgFAILED( tgEM_TE_SEC_Lock( tiTE, uiPool, uiIndex ) ))
    {
        return (false);
    };

    tgCM_UT_LF__SN__Signal( &g_asEM_TE_SEC_Data_Lock[uiPool].m_sLock );
    return (true);
}


/* ---- tgEM_TE_SEC_Query_Paused ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgEM_TE_SEC_Query_Paused( TgBOOL_PCU pbPaused, TgEM_TE_SEC_ID tiTE )
{
    TgUINT_F32                        uiIndex, uiPool;

    TgPARAM_CHECK(nullptr != pbPaused);

    uiIndex = tiTE.m_uiI & 0xFFFF;
    uiPool = tiTE.m_uiI >> 16;

    if (TgFAILED( tgEM_TE_SEC_Lock( tiTE, uiPool, uiIndex ) ))
    {
        return (KTgE_FAIL);
    };

    TgPARAM_CHECK_INDEX( uiIndex, g_apsEM_TE_SEC[uiPool]->m_asTB );

    *pbPaused = tgEM_TB_Is_Paused( g_apsEM_TE_SEC[uiPool]->m_asTB + uiIndex );
    tgCM_UT_LF__SN__Signal( &g_asEM_TE_SEC_Data_Lock[uiPool].m_sLock );
    return (KTgS_OK);
}


/* ---- tgEM_TE_SEC_Query_Start_Time --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgEM_TE_SEC_Query_Start_Time( TgFLOAT32_PCU piTime, TgEM_TE_SEC_ID tiTE )
{
    TgUINT_F32                        uiIndex, uiPool;

    TgPARAM_CHECK(nullptr != piTime);

    uiIndex = tiTE.m_uiI & 0xFFFF;
    uiPool = tiTE.m_uiI >> 16;

    if (TgFAILED( tgEM_TE_SEC_Lock( tiTE, uiPool, uiIndex ) ))
    {
        return (KTgE_FAIL);
    };

    TgPARAM_CHECK_INDEX( uiIndex, g_apsEM_TE_SEC[uiPool]->m_asTB );

    *piTime = g_apsEM_TE_SEC[uiPool]->m_asTB[uiIndex].m_fStart;
    tgCM_UT_LF__SN__Signal( &g_asEM_TE_SEC_Data_Lock[uiPool].m_sLock );
    return (KTgS_OK);
}


/* ---- tgEM_TE_SEC_Query_End_Time ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgEM_TE_SEC_Query_End_Time( TgFLOAT32_PCU piTime, TgEM_TE_SEC_ID tiTE )
{
    TgUINT_F32                        uiIndex, uiPool;

    TgPARAM_CHECK(nullptr != piTime);

    uiIndex = tiTE.m_uiI & 0xFFFF;
    uiPool = tiTE.m_uiI >> 16;

    if (TgFAILED( tgEM_TE_SEC_Lock( tiTE, uiPool, uiIndex ) ))
    {
        return (KTgE_FAIL);
    };

    TgPARAM_CHECK_INDEX( uiIndex, g_apsEM_TE_SEC[uiPool]->m_asTB );

    *piTime = g_apsEM_TE_SEC[uiPool]->m_asTB[uiIndex].m_fEnd;
    tgCM_UT_LF__SN__Signal( &g_asEM_TE_SEC_Data_Lock[uiPool].m_sLock );
    return (KTgS_OK);
}


/* ---- tgEM_TE_SEC_Query_Time_To_Live ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgEM_TE_SEC_Query_Time_To_Live( TgFLOAT32_PCU piTime, TgEM_TE_SEC_ID tiTE )
{
    TgUINT_F32                        uiIndex, uiPool;

    TgPARAM_CHECK(nullptr != piTime);

    uiIndex = tiTE.m_uiI & 0xFFFF;
    uiPool = tiTE.m_uiI >> 16;

    if (TgFAILED( tgEM_TE_SEC_Lock( tiTE, uiPool, uiIndex ) ))
    {
        return (KTgE_FAIL);
    };

    TgPARAM_CHECK_INDEX( uiIndex, g_apsEM_TE_SEC[uiPool]->m_asTB );

    *piTime = tgGB_Query_Total_Time() - g_apsEM_TE_SEC[uiPool]->m_asTB[uiIndex].m_fEnd;
    tgCM_UT_LF__SN__Signal( &g_asEM_TE_SEC_Data_Lock[uiPool].m_sLock );
    return (KTgS_OK);
}
