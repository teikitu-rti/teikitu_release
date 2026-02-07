/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Kernel - File System.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_File_System_Mount --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgKN_FS_MOUNT_ID tgKN_File_System_Mount( TgKN_FILE_SYSTEM_ID_C tiFS, TgUINT_E32_C uiMode, TgCHAR_U8_CPCU mbzPath )
{
    union
    {
        STg2_UT_ST__ST_Node_P               psNode;
        STg2_KN_FS_Mount_P                  ps;
    }                                   sMount;

    TgPARAM_CHECK_INDEX( tiFS.m_uiI, g_asKN_FS );

    if (!tgKN_FILE_SYSTEM_ID_Is_Equal( &g_asKN_FS[tiFS.m_uiI].m_tiFS_Singleton, tiFS ))
    {
        return (KTgKN_FS_MOUNT_ID__INVALID);
    };

    sMount.psNode = tgCM_UT_LF__ST__Pop( &g_sKN_FS_Mount__Free_Stack.m_sStack );
    if (nullptr == sMount.psNode)
    {
        return (KTgKN_FS_MOUNT_ID__INVALID);
    };

    tgKN_FS_MOUNT_ID_Init( &sMount.ps->m_tiFS_Mount_Singleton, (TgUINT_E32)(sMount.ps - g_asKN_FS_Mount) );
    sMount.ps->m_tiFS = tiFS;
    sMount.ps->m_uiMode = uiMode;

    if (nullptr != g_asKN_FS[tiFS.m_uiI].m_pfnMount)
    {
        g_asKN_FS[tiFS.m_uiI].m_pfnMount( tgKN_FS_MOUNT_ID_Query_Unsafe( &sMount.ps->m_tiFS_Mount_Singleton ), mbzPath );
    };

    return (tgKN_FS_MOUNT_ID_Query_Unsafe( &sMount.ps->m_tiFS_Mount_Singleton ));
}


/* ---- tgKN_FS_Query_Free_Space ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRSIZE tgKN_FS_Query_Free_Space( TgKN_FS_MOUNT_ID_C tiFS_Mount )
{
    STg2_KN_FS_Mount_P                  psFS_Mount;
    STg2_KN_File_System_P               psFS;

    psFS_Mount = g_asKN_FS_Mount + tiFS_Mount.m_uiI;
    if (!tgKN_FS_MOUNT_ID_Is_Equal( &psFS_Mount->m_tiFS_Mount_Singleton, tiFS_Mount ))
    {
        return (0);
    };

    psFS = g_asKN_FS + psFS_Mount->m_tiFS.m_uiI;
    if (!tgKN_FILE_SYSTEM_ID_Is_Equal( &psFS->m_tiFS_Singleton, psFS_Mount->m_tiFS ))
    {
        return (0);
    };

    return (psFS->m_pfnFree_Space( tiFS_Mount ));
}


/* ---- tgKN_FILE_ALLOCATOR__Default_Malloc_Pool --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID_P tgKN_FILE_ALLOCATOR__Default_Malloc_Pool( TgRSIZE_C uiSize )
{
    return (TgMALLOC_POOL( uiSize ));
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_File_System__Register ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgKN_FILE_SYSTEM_ID tgKN_File_System__Register( STg2_KN_File_System_DESC_PC psFS_DESC )
{
    TgUINT_E32                          uiFS_Index;

    uiFS_Index = (TgUINT_E32)TgSTD_ATOMIC(fetch_add)( &g_xnuiKN_FS, 1 );
    if (uiFS_Index >= KTgKN_MAX_FILE_SYSTEM)
    {
        return (KTgKN_FILE_SYSTEM_ID__INVALID);
    };

    tgMM_Set_U08_0x00( g_asKN_FS + uiFS_Index, sizeof(STg2_KN_File_System) );

    tgCM_UT_LF__SN__Init( &g_asKN_FS[uiFS_Index].m_sAdd_Lock.m_sLock );
    tgCM_UT_LF__SN_CNT__Init( &g_asKN_FS[uiFS_Index].m_sProcess_Lock.m_sLock );
    tgCM_UT_ST__QU__Init( &g_asKN_FS[uiFS_Index].m_sAdd_Queue );
    tgCM_UT_ST__QU__Init( &g_asKN_FS[uiFS_Index].m_sProcess_Queue );
    tgCM_UT_LF__ST__Init( &g_asKN_FS[uiFS_Index].m_sComplete_Job.m_sStack );

    tgKN_FILE_SYSTEM_ID_Init( &g_asKN_FS[uiFS_Index].m_tiFS_Singleton, uiFS_Index );

    g_asKN_FS[uiFS_Index].m_niExecute = 0;
    g_asKN_FS[uiFS_Index].m_niMax_Execute = psFS_DESC->m_niMax_Execute;
    g_asKN_FS[uiFS_Index].m_pfnFree_Space = psFS_DESC->m_pfnFree_Space;
    g_asKN_FS[uiFS_Index].m_pfnMount = psFS_DESC->m_pfnMount;
    g_asKN_FS[uiFS_Index].m_pfnExecute_Job = psFS_DESC->m_pfnExecute_Job;
    g_asKN_FS[uiFS_Index].m_pfnMount_Free = psFS_DESC->m_pfnMount_Free;

    return (tgKN_FILE_SYSTEM_ID_Query_Unsafe( &g_asKN_FS[uiFS_Index].m_tiFS_Singleton ));
}


/* ---- tgKN_File_System__Free_All ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_File_System__Free_All( TgVOID )
{
    TgUINT_E32                          uiFS_Index, uiFS_MAX;
    union
    {
        STg2_UT_ST__ST_Node_P               psNode;
        STg2_KN_FS_Mount_P                  ps;
    }                                   sMount;

    uiFS_MAX = (TgUINT_E32)TgSTD_ATOMIC(load)( &g_xnuiKN_FS );
    TgSTD_ATOMIC(store)( &g_xnuiKN_FS, 0 );

    while (nullptr != (sMount.psNode = tgCM_UT_LF__ST__Pop( &g_sKN_FS_Mount__Free_Stack.m_sStack )))
    {
        tgKN_FS_MOUNT_ID_Invalidate( &sMount.ps->m_tiFS_Mount_Singleton );
    };

    for (uiFS_Index = 0; uiFS_Index < KTgKN_MAX_FILE_SYSTEM_MOUNT; ++uiFS_Index)
    {
        if (!tgKN_FS_MOUNT_ID_Fetch_And_Is_Valid( nullptr, &g_asKN_FS_Mount[uiFS_Index].m_tiFS_Mount_Singleton))
        {
            continue;
        };

        if (!tgKN_FILE_SYSTEM_ID_Is_Equal( &g_asKN_FS[g_asKN_FS_Mount[uiFS_Index].m_tiFS.m_uiI].m_tiFS_Singleton, g_asKN_FS_Mount[uiFS_Index].m_tiFS ))
        {
            continue;
        };
        g_asKN_FS[g_asKN_FS_Mount[uiFS_Index].m_tiFS.m_uiI].m_pfnMount_Free( tgKN_FS_MOUNT_ID_Query_Unsafe( &g_asKN_FS_Mount[uiFS_Index].m_tiFS_Mount_Singleton ) );
    }

    for (uiFS_Index = 0; uiFS_Index < uiFS_MAX; ++uiFS_Index)
    {
        tgCM_UT_LF__SN__Free_Unsafe( &g_asKN_FS[uiFS_Index].m_sAdd_Lock.m_sLock );
        tgCM_UT_LF__SN_CNT__Free_Unsafe( &g_asKN_FS[uiFS_Index].m_sProcess_Lock.m_sLock );
        tgCM_UT_ST__QU__Free( &g_asKN_FS[uiFS_Index].m_sAdd_Queue );
        tgCM_UT_ST__QU__Free( &g_asKN_FS[uiFS_Index].m_sProcess_Queue );
        tgCM_UT_LF__ST__Free( &g_asKN_FS[uiFS_Index].m_sComplete_Job.m_sStack );

        tgKN_FILE_SYSTEM_ID_Invalidate( &g_asKN_FS[uiFS_Index].m_tiFS_Singleton );

        tgMM_Set_U08_0x00( g_asKN_FS + uiFS_Index, sizeof(STg2_KN_File_System) );
    };
}
