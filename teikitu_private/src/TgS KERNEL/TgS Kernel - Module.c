/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Kernel - Module.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Data                                                                                                                                                                */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

static ETgMODULE_STATE                      s_enKernel_State = ETgMODULE_STATE__FREED;




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_Module_Init --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_Module_Init( TgVOID )
{
    STg2_KN_File_System_DESC            sFS_DESC;

    /* Verify the state of the system */
    TgERROR( ETgMODULE_STATE__FREED == s_enKernel_State );
    s_enKernel_State = ETgMODULE_STATE__INITIALIZING;

    /* Job Manager Execution Queues */
    g_sJob_Stack__JiT = KTgJOB_QUEUE_ID__INVALID;
    g_sJob_Queue__Render_High = KTgJOB_QUEUE_ID__INVALID;
    g_sJob_Queue__Render_Normal = KTgJOB_QUEUE_ID__INVALID;
    g_sJob_Queue__GPU = KTgJOB_QUEUE_ID__INVALID;
    g_sJob_Queue__Client_High = KTgJOB_QUEUE_ID__INVALID;
    g_sJob_Queue__Client_Normal = KTgJOB_QUEUE_ID__INVALID;
    g_sJob_Queue__Client_Low = KTgJOB_QUEUE_ID__INVALID;

    tgMM_Set_U08_0x00( g_atiJob_Thread, sizeof( g_atiJob_Thread ) );

    /* Initialize the Notification system */
    for (TgUINT_E32 uiIndex = 0; uiIndex + 1 < KTgKN_MAX_NOTIFY_ENTRIES; ++uiIndex)
    {
        g_auiKN_Notify_Next[uiIndex] = uiIndex + 1;
    };
    g_auiKN_Notify_Next[KTgKN_MAX_NOTIFY_ENTRIES - 1] = KTgMAX_U32;
    tgMM_Set_U08_0xFF( g_auiKN_Notify_Index, sizeof( g_auiKN_Notify_Index ) );
    tgCM_UT_LF__SN__Init( &g_sKN_Notfiy_Lock.m_sLock );
    g_uiKN_Notfiy_Free_Index = 0;

    /* File System */
    TgSTD_ATOMIC(store)( &g_xnuiKN_FS, 0 );
    tgCM_UT_LF__ST__Init_PreLoad( &g_sKN_FS_Mount__Free_Stack.m_sStack, g_asKN_FS_Mount, sizeof( STg2_KN_FS_Mount ), KTgKN_MAX_FILE_SYSTEM_MOUNT );
    tgCM_UT_LF__ST__Init_PreLoad( &g_sKN_File_Info__Free_Stack.m_sStack, g_asKN_File_Info, sizeof( STg2_KN_File_Info ), KTgKN_MAX_FILE_OPEN );
    tgCM_UT_LF__ST__Init_PreLoad( &g_sKN_File_Job__Free_Stack.m_sStack, g_asKN_File_Job, sizeof( STg2_KN_File_Job ), KTgKN_MAX_FILE_JOB );

    /* Register the FS-HD */
    sFS_DESC.m_niMax_Execute = KTgKN_FS_MAX_OS_COMMAND_PER_DEVICE;
    sFS_DESC.m_pfnFree_Space = tgKN_FS_HDD__Free_Space;
    sFS_DESC.m_pfnMount = tgKN_FS_HDD__Mount;
    sFS_DESC.m_pfnExecute_Job = tgKN_FS_HDD__Execute_Job;
    sFS_DESC.m_pfnMount_Free = tgKN_FS_HDD__Mount_Free;
    g_tiKN_FS_HDD = tgKN_File_System__Register( &sFS_DESC );

    if(TgFAILED(tgKN_OS_Module_Init()))
    {
        goto KN_Init_Fail;
    };

    s_enKernel_State = ETgMODULE_STATE__INITIALIZED;

    return (KTgS_OK);

KN_Init_Fail:
    tgKN_Module_Free();
    return (KTgE_FAIL);
}


/* ---- tgKN_Module_Boot --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_Module_Boot( TgVOID )
{
    /* Verify the state of the system */
    TgERROR( ETgMODULE_STATE__INITIALIZED == s_enKernel_State );
    s_enKernel_State = ETgMODULE_STATE__BOOTING;

    g_sJob_Stack__JiT = tgJM_Init_Job_Queue();
    g_sJob_Queue__Render_High = tgJM_Init_Job_Queue();
    g_sJob_Queue__Render_Normal = tgJM_Init_Job_Queue();
    g_sJob_Queue__GPU = tgJM_Init_Job_Queue();
    g_sJob_Queue__Client_High = tgJM_Init_Job_Queue();
    g_sJob_Queue__Client_Normal = tgJM_Init_Job_Queue();
    g_sJob_Queue__Client_Low = tgJM_Init_Job_Queue();

    /* Note the standard set of job threads are created in tgKN_OS_Module_Boot. */
    if (TgFAILED( tgKN_OS_Module_Boot() ))
    {
        goto KN_Boot_Fail;
    };

    s_enKernel_State = ETgMODULE_STATE__BOOTED;

    LOG_STD_MSG_USZ_FMTU64( KTgCN_CHANEL_INITIALIZE_MEMORY, u8"Static Memory Size", tgKN_Query_Fixed_Memory() )

    return (KTgS_OK);

KN_Boot_Fail:
    tgKN_Module_Stop();
    s_enKernel_State = ETgMODULE_STATE__INITIALIZED;
    return (KTgE_FAIL);
}


/* ---- tgKN_Module_Stop --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_Module_Stop( TgVOID )
{
    if ((ETgMODULE_STATE__FREED == s_enKernel_State) || (ETgMODULE_STATE__INITIALIZED == s_enKernel_State))
    {
        return;
    };

    /* Verify the state of the system */
    TgERROR( ETgMODULE_STATE__BOOTED == s_enKernel_State || ETgMODULE_STATE__BOOTING == s_enKernel_State );
    s_enKernel_State = ETgMODULE_STATE__STOPPING;

    tgKN_OS_Module_Stop();

    tgJM_Stop_Job_Queue( g_sJob_Queue__Client_Low, true );
    tgJM_Free_Job_Queue( g_sJob_Queue__Client_Low );
    g_sJob_Queue__Client_Low = KTgJOB_QUEUE_ID__INVALID;

    tgJM_Stop_Job_Queue( g_sJob_Queue__Client_Normal, true );
    tgJM_Free_Job_Queue( g_sJob_Queue__Client_Normal );
    g_sJob_Queue__Client_Normal = KTgJOB_QUEUE_ID__INVALID;

    tgJM_Stop_Job_Queue( g_sJob_Queue__Client_High, true );
    tgJM_Free_Job_Queue( g_sJob_Queue__Client_High );
    g_sJob_Queue__Client_High = KTgJOB_QUEUE_ID__INVALID;

    tgJM_Stop_Job_Queue( g_sJob_Queue__GPU, true );
    tgJM_Free_Job_Queue( g_sJob_Queue__GPU );
    g_sJob_Queue__GPU = KTgJOB_QUEUE_ID__INVALID;

    tgJM_Stop_Job_Queue( g_sJob_Queue__Render_Normal, true );
    tgJM_Free_Job_Queue( g_sJob_Queue__Render_Normal );
    g_sJob_Queue__Render_Normal = KTgJOB_QUEUE_ID__INVALID;

    tgJM_Stop_Job_Queue( g_sJob_Queue__Render_High, true );
    tgJM_Free_Job_Queue( g_sJob_Queue__Render_High );
    g_sJob_Queue__Render_High = KTgJOB_QUEUE_ID__INVALID;

    tgJM_Stop_Job_Queue( g_sJob_Stack__JiT, true );
    tgJM_Free_Job_Queue( g_sJob_Stack__JiT );
    g_sJob_Stack__JiT = KTgJOB_QUEUE_ID__INVALID;

    s_enKernel_State = ETgMODULE_STATE__STOPPED;
}


/* ---- tgKN_Module_Free --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_Module_Free( TgVOID )
{
    if (ETgMODULE_STATE__FREED == s_enKernel_State)
    {
        return;
    };

    /* Verify the state of the system */
    TgERROR( ETgMODULE_STATE__STOPPED == s_enKernel_State || ETgMODULE_STATE__INITIALIZED == s_enKernel_State || ETgMODULE_STATE__INITIALIZING == s_enKernel_State );
    s_enKernel_State = ETgMODULE_STATE__FREEING;

    tgKN_File_System__Free_All();

    tgKN_OS_Module_Free();

    tgCM_UT_LF__SN__Free_Unsafe( &g_sKN_Notfiy_Lock.m_sLock );

    s_enKernel_State = ETgMODULE_STATE__FREED;
}


/* ---- tgKN_Module_Update ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_Module_Update( TgFLOAT32_C fDT )
{
    TgRESULT                            tgResult = KTgS_OK;

    (void)fDT;

    tgResult |= tgKN_OS_Module_Update( fDT );

    return (tgResult);
}


/* ---- tgKN_Load_Config --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_Load_Config( TgVOID )
{
    return (KTgE_FAIL);
}


/* ---- tgKN_Save_Config --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_Save_Config( TgVOID )
{
    return (KTgE_FAIL);
}


/* ---- tgKN_Query_Init ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgKN_Query_Init( TgVOID )
{
    return (ETgMODULE_STATE__INITIALIZED <= s_enKernel_State && s_enKernel_State <= ETgMODULE_STATE__STOPPED);
}


/* ---- tgKN_Query_Boot ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgKN_Query_Boot( TgVOID )
{
    return (ETgMODULE_STATE__BOOTED == s_enKernel_State);
}


/* ---- tgKN_Stats --------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if TgS_STAT__KERNEL
TgVOID tgKN_Stats( TgATTRIBUTE_UNUSED STg2_Output_P psOUT )
{
}
/*# TgS_STAT__KERNEL */
#endif




