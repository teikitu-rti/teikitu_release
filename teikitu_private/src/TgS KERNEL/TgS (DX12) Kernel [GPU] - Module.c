/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (DX12) Kernel - Module [GPU].c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

#if TgCOMPILE__CONSOLE
static TgVOID
tgKN_GPU_EXT_STAT_Print_Adapters(
    TgUINT_E32_C nuiArg, TgCHAR_U8_CP pArgV[KTgMAX_CMD_LINE_COUNT] ) TgATTRIBUTE_NO_EXCEPT;

static const TgCHAR_U8                      s_szSTAT_Print_Adapters[] = u8"STAT_Print_Adapters";
/*# TgCOMPILE__CONSOLE */
#endif




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_GPU_EXT_Module_Init ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_EXT_Module_Init( TgVOID )
{
    TgRSIZE                             uiIndex;

    TgERROR( nullptr == g_pfnDXGICreateDXGIFactory );

    TgERROR( nullptr == g_pfnDXGIGetDebugInterface1 );

    TgERROR( nullptr == g_pfnD3D12SerializeVersionedRootSignature );
    TgERROR( nullptr == g_pfnD3D12CreateVersionedRootSignatureDeserializer );
    TgERROR( nullptr == g_pfnD3D12CreateDevice );
    TgERROR( nullptr == g_pfnD3D12GetDebugInterface );

    TgERROR( nullptr == g_pDXGIFactory );

    TgERROR( nullptr != g_pfnCreateEventEx );
    TgERROR( nullptr != g_pfnCreateEvent );
    TgERROR( nullptr != g_pfnCloseHandle );

    if (TgFAILED(tgKN_OS_GPU_API_Module_Init()))
    {
        return (KTgE_FAIL);
    };

    TgERROR( nullptr != g_pfnDXGICreateDXGIFactory );

    TgERROR( nullptr != g_pfnDXGIGetDebugInterface1 );

    TgERROR( nullptr != g_pfnD3D12SerializeVersionedRootSignature );
    TgERROR( nullptr != g_pfnD3D12CreateVersionedRootSignatureDeserializer );
    TgERROR( nullptr != g_pfnD3D12CreateDevice );
    TgERROR( nullptr != g_pfnD3D12GetDebugInterface );

    tgMM_Set_U08_0x00(  &g_sKN_GPU_EXT_CXT_HOST, sizeof( STg2_KN_GPU_EXT_CXT_HOST ) );
    tgMM_Set_U08_0x00( &g_asKN_GPU_EXT_CXT_DEVC, sizeof( g_asKN_GPU_EXT_CXT_DEVC ) );
    tgMM_Set_U08_0x00( &g_asKN_GPU_EXT_CXT_EXEC, sizeof( g_asKN_GPU_EXT_CXT_EXEC ) );
    tgMM_Set_U08_0x00( &g_asKN_GPU_EXT_CXT_SWAP, sizeof( g_asKN_GPU_EXT_CXT_SWAP ) );

    for (uiIndex = 0; uiIndex < KTgKN_GPU_MAX_ADAPTER; ++uiIndex)
    {
        g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Adapter[uiIndex].m_tiID_DEVC = KTgKN_GPU_CXT_DEVC_ID__INVALID;
    };

    for (uiIndex = 0; uiIndex < KTgKN_GPU_MAX_DEVC_CONTEXT; ++uiIndex)
    {
        g_asKN_GPU_EXT_CXT_DEVC[uiIndex].m_tiID = KTgKN_GPU_CXT_DEVC_ID__INVALID;
    };

    for (uiIndex = 0; uiIndex < KTgKN_GPU_MAX_EXEC_CONTEXT; ++uiIndex)
    {
        g_asKN_GPU_EXT_CXT_EXEC[uiIndex].m_tiID = KTgKN_GPU_CXT_EXEC_ID__INVALID;
    };

    for (uiIndex = 0; uiIndex < KTgKN_GPU_MAX_SWAP_CONTEXT; ++uiIndex)
    {
        g_asKN_GPU_EXT_CXT_SWAP[uiIndex].m_tiID = KTgKN_GPU_CXT_SWAP_ID__INVALID;
    };

    return (KTgS_OK);
}


/* ---- tgKN_GPU_EXT_Module_Boot ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_EXT_Module_Boot( TgVOID )
{
    TgERROR( nullptr == g_pDXGIFactory );

    if (TgFAILED(tgKN_OS_GPU_API_Module_Boot()))
    {
        return (KTgE_FAIL);
    };

    tgCN_Insert_Command_Function( s_szSTAT_Print_Adapters, tgUSZ_Length_U08( s_szSTAT_Print_Adapters, KTgMAX_RSIZE ), tgKN_GPU_EXT_STAT_Print_Adapters, u8"", 1 );
    TgERROR( nullptr != g_pDXGIFactory );

    return (KTgS_OK);
}


/* ---- tgKN_GPU_EXT_Module_Stop ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_EXT_Module_Stop( TgVOID )
{
    tgCN_Remove_Command_Function( s_szSTAT_Print_Adapters, tgUSZ_Length_U08( s_szSTAT_Print_Adapters, KTgMAX_RSIZE ) );

    tgKN_OS_GPU_API_Module_Stop();

    TgERROR( nullptr == g_pDXGIFactory );
}


/* ---- tgKN_GPU_EXT_Module_Free ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_EXT_Module_Free( TgVOID )
{
    tgKN_OS_GPU_API_Module_Free();

    TgERROR( nullptr == g_pfnDXGICreateDXGIFactory );

    TgERROR( nullptr == g_pfnDXGIGetDebugInterface1 );

    TgERROR( nullptr == g_pfnD3D12SerializeVersionedRootSignature );
    TgERROR( nullptr == g_pfnD3D12CreateVersionedRootSignatureDeserializer );
    TgERROR( nullptr == g_pfnD3D12CreateDevice );
    TgERROR( nullptr == g_pfnD3D12GetDebugInterface );
}


/* ---- tgKN_GPU_EXT_Module_Update ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_EXT_Module_Update( TgATTRIBUTE_UNUSED TgFLOAT32_C fdT )
{
    return (KTgS_OK);
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

#if TgCOMPILE__CONSOLE
static TgVOID tgKN_GPU_EXT_STAT_Print_Adapters(
    TgATTRIBUTE_UNUSED TgUINT_E32_C nuiArg, TgATTRIBUTE_UNUSED TgCHAR_U8_CP pArgV[KTgMAX_CMD_LINE_COUNT] ) TgATTRIBUTE_NO_EXCEPT
{
    TgRSIZE                             uiAdapter;

    for (uiAdapter = 0; uiAdapter < KTgKN_GPU_MAX_ADAPTER; ++uiAdapter)
    {
        tgSTAT_KN_GPU_EXT_Adapter_Output( g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Adapter + uiAdapter );
    };
}
/*# TgCOMPILE__CONSOLE */
#endif
