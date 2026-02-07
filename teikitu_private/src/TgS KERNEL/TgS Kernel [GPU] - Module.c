/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Kernel [GPU] - Module.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Data                                                                                                                                                                */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

static ETgMODULE_STATE                      s_enKernel_GPU_State = ETgMODULE_STATE__FREED;




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_GPU_Module_Init ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_Module_Init( TgVOID )
{
    /* Verify the state of the system */
    TgERROR( ETgMODULE_STATE__FREED == s_enKernel_GPU_State );
    s_enKernel_GPU_State = ETgMODULE_STATE__INITIALIZING;

    g_tiCVAR_KN_GPU_Physical_Device = KTgCN_VAR_ID__INVALID;
    g_tiCVAR_KN_GPU_Output = KTgCN_VAR_ID__INVALID;
    g_tiCVAR_KN_GPU_Width = KTgCN_VAR_ID__INVALID;
    g_tiCVAR_KN_GPU_Height = KTgCN_VAR_ID__INVALID;
    g_tiCVAR_KN_GPU_Refresh_Rate = KTgCN_VAR_ID__INVALID;
    g_tiCVAR_KN_GPU_ScanOut_HDR = KTgCN_VAR_ID__INVALID;

    g_szKN_GPU_Physical_Device[0] = 0;
    g_szKN_GPU_Output[0] = 0;
    g_uiKN_GPU_Width = 0;
    g_uiKN_GPU_Height = 0;
    g_uiKN_GPU_Refresh_Rate = 60;
    g_bKN_GPU_ScanOut_HDR = false;

    tgCM_UT_LF__ST__Init_PreLoad( &g_sKN_GPU_CXT_DEVC_Free_Stack.m_sStack, g_asKN_GPU_CXT_DEVC, sizeof( STg2_KN_GPU_CXT_DEVC ), KTgKN_GPU_MAX_DEVC_CONTEXT );
    tgCM_UT_LF__ST__Init_PreLoad( &g_sKN_GPU_CXT_EXEC_Free_Stack.m_sStack, g_asKN_GPU_CXT_EXEC, sizeof( STg2_KN_GPU_CXT_EXEC ), KTgKN_GPU_MAX_EXEC_CONTEXT );
    tgCM_UT_LF__ST__Init_PreLoad( &g_sKN_GPU_CXT_SWAP_Free_Stack.m_sStack, g_asKN_GPU_CXT_SWAP, sizeof( STg2_KN_GPU_CXT_SWAP ), KTgKN_GPU_MAX_SWAP_CONTEXT );

    tgKN_GPU_CXT_HOST_EXTN_ID_Invalidate( &g_sKN_GPU_CXT_HOST_EXTN.m_tiCXT_HOST_EXT_S );
    tgKN_GPU_CXT_HOST_ID_Invalidate( &g_sKN_GPU_CXT_HOST.m_tiCXT_HOST_S );

    /* Init Stats and Performance Markers */
#if TgS_STAT__KERNEL
    g_uiKN_Stats_Loaded_Mesh_Vertex = 0;
    g_uiKN_Stats_Loaded_Mesh_Face = 0;
    g_uiKN_Stats_Memory_Buffer = 0;
    g_uiKN_Stats_Memory_Mesh = 0;
    g_uiKN_Stats_Memory_Mesh_Collision = 0;
/*# TgS_STAT__KERNEL */
#endif

    if (TgFAILED( tgKN_GPU_EXT_Module_Init() ))
    {
        s_enKernel_GPU_State = ETgMODULE_STATE__FREED;
        return (KTgE_FAIL);
    };

    tgKN_GPU_VS_LIB__Init();
    tgKN_GPU_TCS_LIB__Init();
    tgKN_GPU_TES_LIB__Init();
    tgKN_GPU_GS_LIB__Init();
    tgKN_GPU_TS_LIB__Init();
    tgKN_GPU_MS_LIB__Init();
    tgKN_GPU_FS_LIB__Init();
    tgKN_GPU_CS_LIB__Init();

    tgKN_GPU_TX_IMG_LIB__Init();
    tgKN_GPU_TX_CBE_LIB__Init();
    tgKN_GPU_TX_VOL_LIB__Init();

#if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) && TgCOMPILE__CONSOLE
    tgCN_Register_Render_Callback( tgKN_GPU_Set_CN_Render_Text );
/*# defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) && TgCOMPILE__CONSOLE */
#endif

    s_enKernel_GPU_State = ETgMODULE_STATE__INITIALIZED;
    return (KTgS_OK);
}


/* ---- tgKN_GPU_Module_Boot ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_Module_Boot( TgVOID )
{
    /* Verify the state of the system */
    TgERROR( ETgMODULE_STATE__INITIALIZED == s_enKernel_GPU_State );
    s_enKernel_GPU_State = ETgMODULE_STATE__BOOTING;

    g_szKN_GPU_Physical_Device[0] = 0;
    g_tiCVAR_KN_GPU_Physical_Device = tgCN_Var_Init_String( u8"KN_GPU_Physical_Device", KTgMAX_RSIZE, u8"", KTgMAX_RSIZE, KTgCN_VAR_INIT, u8"0", KTgMAX_RSIZE,
                                                            g_szKN_GPU_Physical_Device, TgARRAY_COUNT(g_szKN_GPU_Physical_Device) );

    g_szKN_GPU_Output[0] = 0;
    g_tiCVAR_KN_GPU_Physical_Device = tgCN_Var_Init_String( u8"KN_GPU_Output", KTgMAX_RSIZE, u8"", KTgMAX_RSIZE, KTgCN_VAR_INIT, u8"0", KTgMAX_RSIZE,
                                                            g_szKN_GPU_Output, TgARRAY_COUNT(g_szKN_GPU_Output) );

    g_tiCVAR_KN_GPU_Width = tgCN_Var_Init_U32( u8"KN_GPU_Width", KTgMAX_RSIZE, u8"", KTgMAX_RSIZE, KTgCN_VAR_INIT,  320, 320, 99999 );
    g_tiCVAR_KN_GPU_Height = tgCN_Var_Init_U32( u8"KN_GPU_Height", KTgMAX_RSIZE, u8"", KTgMAX_RSIZE, KTgCN_VAR_INIT, 200, 200, 99999 );
    g_tiCVAR_KN_GPU_Refresh_Rate = tgCN_Var_Init_U32( u8"KN_GPU_Refresh_Rate", KTgMAX_RSIZE, u8"", KTgMAX_RSIZE, KTgCN_VAR_INIT, 60, 0, 240 );
    g_tiCVAR_KN_GPU_ScanOut_HDR = tgCN_Var_Init_Bool( u8"KN_GPU_ScanOut_HDR", KTgMAX_RSIZE, u8"", KTgMAX_RSIZE, KTgCN_VAR_INIT, false );

    if (TgFAILED( tgKN_GPU_EXT_Module_Boot() ))
    {
        goto KN_GPU_Module_Boot_FAIL_0;
    };

    if (TgFAILED( tgKN_GPU__Host__Init() ))
    {
        goto KN_GPU_Module_Boot_FAIL_1;
    };

    s_enKernel_GPU_State = ETgMODULE_STATE__BOOTED;
    return (KTgS_OK);

KN_GPU_Module_Boot_FAIL_1:
    tgKN_GPU_EXT_Module_Stop();
KN_GPU_Module_Boot_FAIL_0:
    s_enKernel_GPU_State = ETgMODULE_STATE__INITIALIZED;
    return (KTgE_FAIL);
}


/* ---- tgKN_GPU_Module_Stop ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_Module_Stop( TgVOID )
{
    if ((ETgMODULE_STATE__FREED == s_enKernel_GPU_State) || (ETgMODULE_STATE__INITIALIZED == s_enKernel_GPU_State))
    {
        return (KTgS_IGNORED);
    };

    /* Verify the state of the system */
    TgERROR( ETgMODULE_STATE__BOOTED == s_enKernel_GPU_State );
    s_enKernel_GPU_State = ETgMODULE_STATE__STOPPING;

    tgKN_GPU__Host__Free(); /* Free all the default resources. */

    tgKN_GPU_TX_IMG_LIB__Stop();
    tgKN_GPU_TX_CBE_LIB__Stop();
    tgKN_GPU_TX_VOL_LIB__Stop();

    tgKN_GPU_CS_LIB__Stop();
    tgKN_GPU_FS_LIB__Stop();
    tgKN_GPU_MS_LIB__Stop();
    tgKN_GPU_TS_LIB__Stop();
    tgKN_GPU_GS_LIB__Stop();
    tgKN_GPU_TES_LIB__Stop();
    tgKN_GPU_TCS_LIB__Stop();
    tgKN_GPU_VS_LIB__Stop();

    tgKN_GPU_EXT_Module_Stop();

    s_enKernel_GPU_State = ETgMODULE_STATE__STOPPED;
    return (KTgS_OK);
}


/* ---- tgKN_GPU_Module_Free ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_Module_Free( TgVOID )
{
    if (ETgMODULE_STATE__FREED == s_enKernel_GPU_State)
    {
        return (KTgS_IGNORED);
    };

    /* Verify the state of the system */
    TgERROR( ETgMODULE_STATE__STOPPED == s_enKernel_GPU_State || ETgMODULE_STATE__INITIALIZED == s_enKernel_GPU_State );
    s_enKernel_GPU_State = ETgMODULE_STATE__FREEING;

#if TgCOMPILE__CONSOLE && defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)
    tgCN_Register_Render_Callback( nullptr );
/*# TgCOMPILE__CONSOLE && defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
#endif

    tgKN_GPU_TX_VOL_LIB__Free();
    tgKN_GPU_TX_CBE_LIB__Free();
    tgKN_GPU_TX_IMG_LIB__Free();

    tgKN_GPU_CS_LIB__Free();
    tgKN_GPU_FS_LIB__Free();
    tgKN_GPU_MS_LIB__Free();
    tgKN_GPU_TS_LIB__Free();
    tgKN_GPU_GS_LIB__Free();
    tgKN_GPU_TES_LIB__Free();
    tgKN_GPU_TCS_LIB__Free();
    tgKN_GPU_VS_LIB__Free();

    tgKN_GPU_EXT_Module_Free();

    TgERROR(!tgKN_GPU_CXT_HOST_EXTN_ID_Fetch_And_Is_Valid( nullptr, &g_sKN_GPU_CXT_HOST_EXTN.m_tiCXT_HOST_EXT_S ));
    TgERROR(!tgKN_GPU_CXT_HOST_ID_Fetch_And_Is_Valid( nullptr, &g_sKN_GPU_CXT_HOST.m_tiCXT_HOST_S ));

    s_enKernel_GPU_State = ETgMODULE_STATE__FREED;
    return (KTgS_OK);
}


/* ---- tgKN_GPU_Module_Update --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_Module_Update( TgATTRIBUTE_UNUSED TgFLOAT32_C fDT )
{
    return (KTgS_OK);
}


/* ---- tgKN_GPU_Stats ----------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if TgS_STAT__KERNEL
TgVOID tgKN_GPU_Stats( TgATTRIBUTE_UNUSED STg2_Output_P psOUT )
{
}
/*# TgS_STAT__KERNEL */
#endif
