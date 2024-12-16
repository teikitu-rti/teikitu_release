/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (DX12) Kernel - System [GPU] [Enumeration].c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */

TgCLANG_WARN_DISABLE_PUSH(everything)
TgMSVC_PRAGMA(warning(push, 0))
#include <stdlib.h> /**< qsort */
#define NORASTEROPS
#define NOMETAFILE
#define NOTEXTMETRIC
//#include <wingdi.h>
#undef NOTEXTMETRIC
#undef NOMETAFILE
#undef NORASTEROPS
TgMSVC_PRAGMA(warning(pop))
TgCLANG_WARN_DISABLE_POP(everything)


/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgEXTN TgBOOL
tgSI_APP_Is_Remote_Session( TgVOID );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

static STg2_KN_GPU_EXT_Adapter_P
tgKN_GPU_EXT_Enumerate__Process_Adapter(
    IDXGIAdapter_P, TgBOOL_C );

static TgRESULT
tgKN_GPU_EXT_Enumerate__Adapter_Output(
    STg2_KN_GPU_EXT_Adapter_PCU );

static TgVOID
tgKN_GPU_EXT_Enumerate__Adapter_Mode(
    STg2_KN_GPU_EXT_Adapter_PCU, STg2_KN_GPU_EXT_Output_PCU );

static TgVOID
tgKN_GPU_EXT_Enumerate__Populate_Module( TgVOID );

/** @brief Free all the resources associated with an adapter at the given index in the HOST contexts.
    @param [in] ARG0 Index of the Adapter to free. */
static TgVOID
tgKN_GPU_EXT_Adapter_Free(
    TgRSIZE_C ARG0 );

static TgVOID
tgKN_GPU_EXT_Output_Free(
    STg2_KN_GPU_EXT_Output_P );

static TgSINT_E32 CDECL
tgKN_GPU_EXT_Quick_Sort__DXGI_MODE_DESC(
    TgVOID_CPC, TgVOID_CPC ) TgATTRIBUTE_NO_EXCEPT;

static TgVOID
tgKN_GPU_EXT_Debug_Layer_Configuration(
    STg2_KN_GPU_EXT_Adapter_P
);

#if defined(TgBUILD_ENABLE_D3D_DEBUG) && TgBUILD_ENABLE_D3D_DEBUG
static TgVOID CDECL
tgKN_GPU_EXT_Message_Function(
    D3D12_MESSAGE_CATEGORY Category, D3D12_MESSAGE_SEVERITY Severity, D3D12_MESSAGE_ID ID, LPCSTR pDescription, TgVOID_P pContext ) TgATTRIBUTE_NO_EXCEPT;
/*# defined(TgBUILD_ENABLE_D3D_DEBUG) && TgBUILD_ENABLE_D3D_DEBUG */
#endif




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_GPU_EXT_Enumerate --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_EXT_Enumerate( TgVOID )
{
    TgUINT_E32                          uiAdapter;
    IDXGIAdapter_P                      psDXGI_IAdapter;
    STg2_KN_GPU_EXT_Adapter_P           psEXT_Adapter;

    TgCRITICAL(nullptr != g_pDXGIFactory);
    TgERROR(tgKN_Query_Boot());

    g_sKN_GPU_CXT_HOST.m_nuiAdapter = 0;

    for (uiAdapter = 0; g_sKN_GPU_CXT_HOST.m_nuiAdapter < KTgKN_GPU_MAX_ADAPTER; ++uiAdapter)
    {
        if (FAILED(IDXGIFactory7_EnumAdapters( g_pDXGIFactory, uiAdapter, &psDXGI_IAdapter )))
        {
            break;
        };

        /* Note: This function is responsible for releasing the adapter interface. */
        psEXT_Adapter = tgKN_GPU_EXT_Enumerate__Process_Adapter( psDXGI_IAdapter, false );
        if (nullptr == psEXT_Adapter)
        {
            continue;
        };

        psEXT_Adapter->m_uiDXGI_Adapter_Ordinal = uiAdapter;
    };

    tgKN_GPU_EXT_Enumerate__Populate_Module();

    return (0 != g_sKN_GPU_CXT_HOST.m_nuiAdapter ? KTgS_OK : KTgE_FAIL);
}


/* ---- tgKN_GPU_EXT_Enumerate_Free_Resources ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_EXT_Enumerate_Free_Resources( TgVOID )
{
    TgRSIZE                             uiAdapter;

    for (uiAdapter = 0; uiAdapter < KTgKN_GPU_MAX_ADAPTER; ++uiAdapter)
    {
        tgKN_GPU_EXT_Adapter_Free( uiAdapter );
    };
    g_sKN_GPU_CXT_HOST.m_nuiAdapter = 0;
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_GPU_EXT_Enumerate__Process_Adapter ---------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
STg2_KN_GPU_EXT_Adapter_P tgKN_GPU_EXT_Enumerate__Process_Adapter( IDXGIAdapter_P psDXGI_IAdapter, TgBOOL_C bSoftware )
{
    STg2_KN_GPU_EXT_Adapter_P           psGPU_EXT_Adapter;
    HRESULT                             iRet;
    TgSINT_E32                          iFormat;
    D3D12_FEATURE_DATA_ROOT_SIGNATURE   sDX12_Feature_Data;
    IUnknown_P                          psUnknown;

    psGPU_EXT_Adapter = g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Adapter + g_sKN_GPU_CXT_HOST.m_nuiAdapter;
    TgCRITICAL(0 != psGPU_EXT_Adapter);
    psGPU_EXT_Adapter->m_tiID_DEVC = KTgKN_GPU_CXT_DEVC_ID__INVALID;

    /* Upgrade the adapter interface, and get the most recent version of the adapter description. */
    if (FAILED(IDXGIAdapter_QueryInterface( psDXGI_IAdapter, MS_REF IID_IDXGIAdapter4, (TgVOID_PP)&psGPU_EXT_Adapter->m_psDXGI_Adapter )))
    {
        TgVERIFY(0 == IDXGIAdapter_Release( psDXGI_IAdapter ));
        return (nullptr);
    };
    TgVERIFY(1 == IDXGIAdapter_Release( psDXGI_IAdapter ));
    psDXGI_IAdapter = nullptr;

    TgVERIFY(SUCCEEDED(IDXGIAdapter4_GetDesc3( psGPU_EXT_Adapter->m_psDXGI_Adapter, &psGPU_EXT_Adapter->m_sDXGI_Adapter )));

    if ((!bSoftware) && (psGPU_EXT_Adapter->m_sDXGI_Adapter.Flags & DXGI_ADAPTER_FLAG3_SOFTWARE))
    {
        tgKN_GPU_EXT_Adapter_Free( g_sKN_GPU_CXT_HOST.m_nuiAdapter );
        return (nullptr);
    };

    /* Attempt to acquire a 12.x feature level first (if not installed we get an INVALIDARG fail immediately) */
    psGPU_EXT_Adapter->m_enD3D_Feature_Level = D3D_FEATURE_LEVEL_12_2;
    IDXGIAdapter4_QueryInterface( psGPU_EXT_Adapter->m_psDXGI_Adapter, MS_REF IID_IUnknown, (TgVOID_PP)&psUnknown );
    iRet = g_pfnD3D12CreateDevice( psUnknown, D3D_FEATURE_LEVEL_12_2, MS_REF IID_ID3D12Device10, (TgVOID_PP)&psGPU_EXT_Adapter->m_psDX12_Device );

    if (FAILED( iRet ))
    {
        psGPU_EXT_Adapter->m_enD3D_Feature_Level = D3D_FEATURE_LEVEL_12_1;
        iRet = g_pfnD3D12CreateDevice( psUnknown, D3D_FEATURE_LEVEL_12_1, MS_REF IID_ID3D12Device10, (TgVOID_PP)&psGPU_EXT_Adapter->m_psDX12_Device );
    };

    if (FAILED( iRet ))
    {
        psGPU_EXT_Adapter->m_enD3D_Feature_Level = D3D_FEATURE_LEVEL_12_0;
        iRet = g_pfnD3D12CreateDevice( psUnknown, D3D_FEATURE_LEVEL_12_0, MS_REF IID_ID3D12Device10, (TgVOID_PP)&psGPU_EXT_Adapter->m_psDX12_Device );
    };

    IUnknown_Release( psUnknown );
    psUnknown = nullptr;

    if (FAILED( iRet ))
    {
        tgKN_GPU_EXT_Adapter_Free( g_sKN_GPU_CXT_HOST.m_nuiAdapter );
        return (nullptr);
    };

    psGPU_EXT_Adapter->m_uiIsWARP = (psGPU_EXT_Adapter->m_sDXGI_Adapter.Flags & DXGI_ADAPTER_FLAG3_SOFTWARE) ? 1u : 0;


    tgKN_GPU_EXT_Debug_Layer_Configuration( psGPU_EXT_Adapter );


    /* Check that we support root signature v1.1 */
    sDX12_Feature_Data.HighestVersion = D3D_ROOT_SIGNATURE_VERSION_1_1;
    if (FAILED( ID3D12Device10_CheckFeatureSupport( psGPU_EXT_Adapter->m_psDX12_Device, D3D12_FEATURE_ROOT_SIGNATURE, &sDX12_Feature_Data, sizeof( sDX12_Feature_Data ) ) ))
    {
        tgKN_GPU_EXT_Adapter_Free( g_sKN_GPU_CXT_HOST.m_nuiAdapter );
        return (nullptr);
    }


    /* Check Shader Model Support */
    psGPU_EXT_Adapter->m_sDX12_Shader_Model.HighestShaderModel = D3D_SHADER_MODEL_6_6;
    iRet = ID3D12Device10_CheckFeatureSupport( psGPU_EXT_Adapter->m_psDX12_Device, D3D12_FEATURE_SHADER_MODEL, &psGPU_EXT_Adapter->m_sDX12_Shader_Model,
                                               sizeof(psGPU_EXT_Adapter->m_sDX12_Shader_Model));
    while (iRet == E_INVALIDARG && psGPU_EXT_Adapter->m_sDX12_Shader_Model.HighestShaderModel > D3D_SHADER_MODEL_6_0)
    {
        psGPU_EXT_Adapter->m_sDX12_Shader_Model.HighestShaderModel = (D3D_SHADER_MODEL)(psGPU_EXT_Adapter->m_sDX12_Shader_Model.HighestShaderModel - 1);
        iRet = ID3D12Device10_CheckFeatureSupport( psGPU_EXT_Adapter->m_psDX12_Device, D3D12_FEATURE_SHADER_MODEL, &psGPU_EXT_Adapter->m_sDX12_Shader_Model,
                                                   sizeof(psGPU_EXT_Adapter->m_sDX12_Shader_Model));
    }

    if (FAILED( iRet ))
    {
        psGPU_EXT_Adapter->m_sDX12_Shader_Model.HighestShaderModel = D3D_SHADER_MODEL_5_1;
        iRet = ID3D12Device10_CheckFeatureSupport( psGPU_EXT_Adapter->m_psDX12_Device, D3D12_FEATURE_SHADER_MODEL, &psGPU_EXT_Adapter->m_sDX12_Shader_Model,
                                                   sizeof(psGPU_EXT_Adapter->m_sDX12_Shader_Model));
        if (FAILED( iRet ))
        {
            tgKN_GPU_EXT_Adapter_Free( g_sKN_GPU_CXT_HOST.m_nuiAdapter );
            return (nullptr);
        };
    };


    /* Check for multi-sample support */
    for (iFormat = 0; iFormat < KTgKN_GPU_EXT_FORMAT_RT_SCANOUT_MAX; ++iFormat)
    {
        TgSINT_E32                          iMS;
        D3D12_FD_MSQL                       sMS;

        sMS.Format = (DXGI_FORMAT)KTgKN_GPU_EXT_FORMAT_RT_SCANOUT[iFormat];
        sMS.Flags = D3D12_MULTISAMPLE_QUALITY_LEVELS_FLAG_NONE;

        for (iMS = 0; iMS < KTgKN_GPU_MS__MAX && iMS < D3D12_MAX_MULTISAMPLE_SAMPLE_COUNT; ++iMS)
        {
            sMS.SampleCount = (UINT)(iMS + 1);
            sMS.NumQualityLevels = 0;

            if (FAILED( ID3D12Device10_CheckFeatureSupport( psGPU_EXT_Adapter->m_psDX12_Device, D3D12_FEATURE_MULTISAMPLE_QUALITY_LEVELS, &sMS, sizeof( D3D12_FD_MSQL ) ) ))
            {
                continue;
            };

            if (sMS.NumQualityLevels > 0)
            {
                psGPU_EXT_Adapter->m_auiMS[iFormat][iMS] = sMS.NumQualityLevels;
            };
        };
    };

    psGPU_EXT_Adapter->m_nuiEXT_Output = 0;

    tgKN_GPU_EXT_Enumerate__Adapter_Output( psGPU_EXT_Adapter );

    TgERROR(KTgKN_GPU_CXT_DEVC_ID__INVALID.m_uiKI == psGPU_EXT_Adapter->m_tiID_DEVC.m_uiKI);
    ++g_sKN_GPU_CXT_HOST.m_nuiAdapter;

    return (psGPU_EXT_Adapter);
}


/* ---- tgKN_GPU_EXT_Enumerate__Adapter_Output ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT tgKN_GPU_EXT_Enumerate__Adapter_Output( STg2_KN_GPU_EXT_Adapter_PCU psGPU_EXT_Adapter )
{
    TgUINT_E32                          uiOutput;
    STg2_KN_GPU_EXT_Output_P            psGPU_EXT_Output;

    psGPU_EXT_Adapter->m_nuiEXT_Output = 0;
    for (uiOutput = 0; psGPU_EXT_Adapter->m_nuiEXT_Output < KTgKN_GPU_MAX_OUTPUT; ++uiOutput)
    {
        IDXGIOutput                         *pDXGI_Output = nullptr;

        psGPU_EXT_Output = psGPU_EXT_Adapter->m_asEXT_Output + psGPU_EXT_Adapter->m_nuiEXT_Output;

        if (FAILED(IDXGIAdapter4_EnumOutputs( psGPU_EXT_Adapter->m_psDXGI_Adapter, uiOutput, &pDXGI_Output )))
            break;

        if (FAILED(IDXGIOutput_QueryInterface( pDXGI_Output, MS_REF IID_IDXGIOutput6, (TgVOID_PP)&psGPU_EXT_Output->m_psDXGI_Output ) ))
        {
            TgVERIFY(0 == IDXGIOutput_Release( pDXGI_Output ));
            pDXGI_Output = nullptr;
            continue;
        };

        TgVERIFY(1 == IDXGIOutput_Release( pDXGI_Output ));
        pDXGI_Output = nullptr;

        if (FAILED(IDXGIOutput6_GetDesc1( psGPU_EXT_Output->m_psDXGI_Output, &psGPU_EXT_Output->m_sDXGI_Output )))
        {
            tgKN_GPU_EXT_Output_Free( psGPU_EXT_Output );
            continue;
        }

        psGPU_EXT_Output->m_uiDXGI_Output_Ordinal= uiOutput;

        tgKN_GPU_EXT_Enumerate__Adapter_Mode( psGPU_EXT_Adapter, psGPU_EXT_Output );

        if (0 >= psGPU_EXT_Output->m_nuiDXGI_Mode)
        {
            /* This would be really screwed up since we are not filtering any of the devices or modes but just in case ... */
            tgCN_PrintF( KTgCN_CHANEL_ERROR, u8"%-16.16s(%-48.48s): Failed to find any modes for an adapter output.\n", u8"Kernel", u8"tgKN_GPU_EXT_Enumerate__Adapter_Output" );
            tgKN_GPU_EXT_Output_Free( psGPU_EXT_Output );
            continue;
        };
        TgERROR(0 < psGPU_EXT_Output->m_nuiDXGI_Mode);
        ++psGPU_EXT_Adapter->m_nuiEXT_Output;
    };

    return (0 < psGPU_EXT_Adapter->m_nuiEXT_Output ? KTgS_OK : KTgE_FAIL);
}


/* ---- tgKN_GPU_EXT_Enumerate__Adapter_Mode ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgKN_GPU_EXT_Enumerate__Adapter_Mode( TgATTRIBUTE_UNUSED_PARAM_CHECK STg2_KN_GPU_EXT_Adapter_PCU psGPU_EXT_Adapter, STg2_KN_GPU_EXT_Output_PCU psGPU_EXT_Output )
{
    UINT                                nuiModeFormat[KTgKN_GPU_EXT_FORMAT_RT_SCANOUT_MAX];
    TgRSIZE                             nuiMode, nuiModeMax;
    TgRSIZE                             uiIndex, uiFormat;
    HRESULT                             iRet;
    DXGI_MODE_DESC1_P                   psModes;
    TgRSIZE                             uiIndex_Unique;

    TgPARAM_CHECK((nullptr != psGPU_EXT_Adapter) && (nullptr != psGPU_EXT_Output));

    nuiModeMax = 2048;
    nuiMode = 0;
    uiFormat = 0;

    psModes = (DXGI_MODE_DESC1_P)TgMALLOC_TEMP(sizeof(DXGI_MODE_DESC1)*nuiModeMax);
    TgCRITICAL(0 != psModes);

    while (uiFormat < KTgKN_GPU_EXT_FORMAT_RT_SCANOUT_MAX)
    {
        nuiModeFormat[uiFormat] = (UINT)nuiModeMax;
        iRet = IDXGIOutput6_GetDisplayModeList1(
            psGPU_EXT_Output->m_psDXGI_Output, (DXGI_FORMAT)KTgKN_GPU_EXT_FORMAT_RT_SCANOUT[uiFormat], DXGI_ENUM_MODES_SCALING, nuiModeFormat + uiFormat, psModes + nuiMode );

        if (DXGI_ERROR_NOT_FOUND == iRet)
        {
            TgFREE_TEMP( psModes );
            psGPU_EXT_Output->m_psDXGI_Mode = 0;
            psGPU_EXT_Output->m_nuiDXGI_Mode = 0;
            return;
        };

        /* Make a single fake display mode for remote sessions */
        if ((DXGI_ERROR_NOT_CURRENTLY_AVAILABLE == iRet) && (DXGI_FORMAT_R8G8B8A8_UNORM == (DXGI_FORMAT)KTgKN_GPU_EXT_FORMAT_RT_SCANOUT[uiFormat]))
        {
            if (nuiMode == nuiModeMax)
            {
                // Not particularly a clean way to deal with the issue but it will work.
                iRet = DXGI_ERROR_MORE_DATA;
            }
            else
            {
                if (tgSI_APP_Is_Remote_Session())
                {
                    //DEVMODE                             sDevMode;

                    //sDevMode.dmSize = sizeof( DEVMODE );
                    //if (g_pfnEnumDisplaySettings( nullptr, ENUM_CURRENT_SETTINGS, &sDevMode ))
                    //{
                    //    psModes[nuiMode].Width = sDevMode.dmPelsWidth;
                    //    psModes[nuiMode].Height = sDevMode.dmPelsHeight;
                    //    psModes[nuiMode].RefreshRate.Numerator = 60;
                    //    psModes[nuiMode].RefreshRate.Denominator = 1;
                    //    psModes[nuiMode].Format = DXGI_FORMAT_R8G8B8A8_UNORM;
                    //    psModes[nuiMode].ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE;
                    //    psModes[nuiMode].Scaling = DXGI_MODE_SCALING_CENTERED;
                    //    psModes[nuiMode].Stereo = 0;

                    //    nuiModeFormat[uiFormat] = 1;
                    //};
                };
            };
        };

        /* Keep increasing the max pool until we have enough entries. Should only require one attempt. */
        if (DXGI_ERROR_MORE_DATA == iRet)
        {
            DXGI_MODE_DESC1_P                   psModesNew;

            nuiModeMax += 512;

            psModesNew = (DXGI_MODE_DESC1*)TgMALLOC_TEMP(sizeof(DXGI_MODE_DESC1)*nuiModeMax);
            TgCRITICAL(0 != psModesNew);

            if (nuiMode > 0)
            {
                tgMM_Copy( psModesNew, sizeof(DXGI_MODE_DESC1)*nuiModeMax, psModes, sizeof(DXGI_MODE_DESC1)*nuiMode );
            };

            TgFREE_TEMP( psModes );
            psModes = psModesNew;
            continue;
        };

        TgCRITICAL(nuiModeFormat[uiFormat] < (TgUINT_E32)KTgMAX_S32);
        TgCRITICAL(nuiMode < (TgUINT_E32)KTgMAX_S32 - nuiModeFormat[uiFormat]);
        nuiMode += nuiModeFormat[uiFormat];
        ++uiFormat;
    };

    /* Sort the modes for the selection routines and remove duplicates */
    qsort( psModes, nuiMode, sizeof(DXGI_MODE_DESC1), tgKN_GPU_EXT_Quick_Sort__DXGI_MODE_DESC );
    for (uiIndex_Unique = 0, uiIndex = 1; uiIndex < nuiMode; ++uiIndex)
    {
        if (0 != tgKN_GPU_EXT_Quick_Sort__DXGI_MODE_DESC( psModes + uiIndex_Unique, psModes + uiIndex ))
        {
            ++uiIndex_Unique;
            if (uiIndex_Unique != uiIndex)
            {
                psModes[uiIndex_Unique] = psModes[uiIndex];
            };
            continue;
        };
    };
    nuiMode = uiIndex_Unique + 1;

    psGPU_EXT_Output->m_psDXGI_Mode = (DXGI_MODE_DESC1*)TgMALLOC_POOL(sizeof(DXGI_MODE_DESC1)*nuiMode);
    TgCRITICAL_MSGF( nullptr != psGPU_EXT_Output->m_psDXGI_Mode, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to allocate memory." );
    tgMM_Copy( psGPU_EXT_Output->m_psDXGI_Mode, sizeof(DXGI_MODE_DESC1)*nuiMode, psModes, sizeof(DXGI_MODE_DESC1)*nuiMode );
    TgFREE_TEMP( psModes );

    for (uiFormat = 0; uiFormat < TgARRAY_COUNT(KTgKN_GPU_EXT_FORMAT_RT_SCANOUT); ++uiFormat)
    {
        psGPU_EXT_Output->m_nuiMode_ScanOut[uiFormat] = nuiModeFormat[uiFormat];
    };
    psGPU_EXT_Output->m_nuiDXGI_Mode = nuiMode;
}


/* ---- tgKN_GPU_EXT_Enumerate__Populate_Module ---------------------------------------------------------------------------------------------------------------------------------- */
TgCOMPILER_ASSERT( TgARRAY_COUNT(KTgKN_GPU_EXT_FORMAT_RT_SCANOUT) < KTgMAX_U08, 0 );
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_EXT_Enumerate__Populate_Module( TgVOID )
{
    TgRSIZE                             uiAdapter;

    for (uiAdapter = 0; uiAdapter < g_sKN_GPU_CXT_HOST.m_nuiAdapter; ++uiAdapter)
    {
        STg2_KN_GPU_EXT_Output_P            psGPU_EXT_Output;
        STg2_KN_GPU_Output_P                psOutput;
        TgRSIZE                             uiOutput;

        tgCN_PrintF( KTgCN_CHANEL_INITIALIZE | KTgCN_SEVERITY_9, u8"%-16.16s(%-48.48s): Adapter: %d\n", u8"Kernel", u8"tgKN_GPU_EXT_Enumerate", uiAdapter );

    #if TgS_STAT__KERNEL || TgS_DEBUG__KERNEL
        //tgKN_GPU_DXGI_Output__Adapter( g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Adapter + uiAdapter );
    #endif

        /* STg2_KN_GPU_Adapter::m_szAdapter */
        tgUSZ_Convert_WSZ( g_sKN_GPU_CXT_HOST.m_asAdapter[uiAdapter].m_szAdapter,
                           TgARRAY_COUNT( g_sKN_GPU_CXT_HOST.m_asAdapter[uiAdapter].m_szAdapter ),
                           g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Adapter[uiAdapter].m_sDXGI_Adapter.Description,
                           TgARRAY_COUNT( g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Adapter[uiAdapter].m_sDXGI_Adapter.Description ) );

        /* STg2_KN_GPU_Adapter::m_uiHost_Adapter_Index */
        g_sKN_GPU_CXT_HOST.m_asAdapter[uiAdapter].m_uiHost_Adapter_Index = (TgUINT_E32)uiAdapter;

        /* STg2_KN_GPU_Adapter::m_nuiNode */
        g_sKN_GPU_CXT_HOST.m_asAdapter[uiAdapter].m_nuiNode = ID3D12Device10_GetNodeCount( g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Adapter[uiAdapter].m_psDX12_Device );

        /* STg2_KN_GPU_Adapter::m_asOutput, STg2_KN_GPU_Adapter::m_nuiOutput */
        g_sKN_GPU_CXT_HOST.m_asAdapter[uiAdapter].m_nuiOutput = 0;
        psGPU_EXT_Output = g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Adapter[uiAdapter].m_asEXT_Output;
        psOutput = g_sKN_GPU_CXT_HOST.m_asAdapter[uiAdapter].m_asOutput;

        /* STg2_KN_GPU_Adapter::m_uiSupport_Flags */
        for (uiOutput = 0; uiOutput < KTgKN_GPU_EXT_FORMAT_RT_SCANOUT_MAX; ++uiOutput)
        {
            D3D12_FEATURE_DATA_FORMAT_SUPPORT   sDX12_Format_Support;

            sDX12_Format_Support.Format = (DXGI_FORMAT)KTgKN_GPU_EXT_FORMAT_RT_SCANOUT[uiOutput];
            if (SUCCEEDED( ID3D12Device10_CheckFeatureSupport( g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Adapter[uiAdapter].m_psDX12_Device, D3D12_FEATURE_FORMAT_SUPPORT,
                                                               &sDX12_Format_Support, sizeof( sDX12_Format_Support ) ) ))
            {
                if (sDX12_Format_Support.Support1 & D3D12_FORMAT_SUPPORT1_RENDER_TARGET )
                {
                   tgBF_Set_Flag_U32( &g_sKN_GPU_CXT_HOST.m_asAdapter[uiAdapter].m_uiSupport_Flags, (TgUINT_E08)(uiOutput), true );
                }
            }
        };

        for (uiOutput = 0; uiOutput < g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Adapter[uiAdapter].m_nuiEXT_Output; ++uiOutput)
        {
            TgUINT_E08                          uiScanOut;

            /* STg2_KN_GPU_Output::m_szName */
            tgUSZ_Convert_WSZ( psOutput->m_szName, TgARRAY_COUNT( psOutput->m_szName ), psGPU_EXT_Output->m_sDXGI_Output.DeviceName,
                               TgARRAY_COUNT( psGPU_EXT_Output->m_sDXGI_Output.DeviceName ) );

            /* STg2_KN_GPU_Output::m_uiFlags */
            psOutput->m_uiScanOut = 0;
            for (uiScanOut = 0; uiScanOut < KTgKN_GPU_EXT_FORMAT_RT_SCANOUT_MAX; ++uiScanOut)
            {
                tgBF_Set_Flag_U64( &psOutput->m_uiScanOut, (TgUINT_E08)(uiScanOut), 0 != psGPU_EXT_Output->m_nuiMode_ScanOut[uiScanOut] );
            };

            ++psGPU_EXT_Output;
            ++psOutput;
            ++g_sKN_GPU_CXT_HOST.m_asAdapter[uiAdapter].m_nuiOutput;

            tgKN_OS_GPU_EXT_Output__Init( psGPU_EXT_Output->m_uiDXGI_Output_Ordinal, psGPU_EXT_Output );
        };

        TgERROR( g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Adapter[uiAdapter].m_nuiEXT_Output == g_sKN_GPU_CXT_HOST.m_asAdapter[uiAdapter].m_nuiOutput );
    };
}


/* ---- tgKN_GPU_EXT_Adapter_Free ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgKN_GPU_EXT_Adapter_Free( TgRSIZE_C uiAdapter_Index )
{
    STg2_KN_GPU_EXT_Adapter_P           psEXT_Adapter;
    STg2_KN_GPU_Adapter_P               psAdapter;
    TgRSIZE                             uiOutput;

    psEXT_Adapter = g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Adapter + uiAdapter_Index;
    psAdapter = g_sKN_GPU_CXT_HOST.m_asAdapter + uiAdapter_Index;

    for (uiOutput = 0; uiOutput < psEXT_Adapter->m_nuiEXT_Output; ++uiOutput)
    {
        tgKN_GPU_EXT_Output_Free( psEXT_Adapter->m_asEXT_Output + uiOutput );
    };

    if (nullptr != psEXT_Adapter->m_psDX12_Device)
    {
        TgVERIFY(0 == ID3D12Device10_Release( psEXT_Adapter->m_psDX12_Device ));
        psEXT_Adapter->m_psDX12_Device = nullptr;
    };

    if (nullptr != psEXT_Adapter->m_psDXGI_Adapter)
    {
        TgVERIFY(0 == IDXGIAdapter4_Release( psEXT_Adapter->m_psDXGI_Adapter ));
        psEXT_Adapter->m_psDXGI_Adapter = nullptr;
    };

    TgERROR(KTgKN_GPU_CXT_DEVC_ID__INVALID.m_uiKI == psEXT_Adapter->m_tiID_DEVC.m_uiKI);
    tgMM_Set_U08_0x00( psEXT_Adapter, sizeof(STg2_KN_GPU_EXT_Adapter) );
    psEXT_Adapter->m_tiID_DEVC = KTgKN_GPU_CXT_DEVC_ID__INVALID;
    tgMM_Set_U08_0x00( psAdapter, sizeof(STg2_KN_GPU_Adapter) );
}


/* ---- tgKN_GPU_EXT_Output_Free ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgKN_GPU_EXT_Output_Free( STg2_KN_GPU_EXT_Output_P psGPU_EXT_Output )
{
    tgKN_OS_GPU_EXT_Output__Free( psGPU_EXT_Output->m_uiDXGI_Output_Ordinal );

    if (nullptr != psGPU_EXT_Output->m_psDXGI_Output)
    {
        TgVERIFY(0 == IDXGIOutput6_Release( psGPU_EXT_Output->m_psDXGI_Output ));
        psGPU_EXT_Output->m_psDXGI_Output = nullptr;
    };

    TgFREE_POOL( psGPU_EXT_Output->m_psDXGI_Mode );
    tgMM_Set_U08_0x00( psGPU_EXT_Output, sizeof(STg2_KN_GPU_EXT_Output) );
}


/* ---- tgKN_GPU_EXT_Quick_Sort__DXGI_MODE_DESC ---------------------------------------------------------------------------------------------------------------------------------- */
/* NOTE: Mode selection routines depend on this specific ordering of the modes.                                                                                                    */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgSINT_E32 CDECL tgKN_GPU_EXT_Quick_Sort__DXGI_MODE_DESC( TgVOID_CPC arg1, TgVOID_CPC arg2 ) TgATTRIBUTE_NO_EXCEPT
{
    const DXGI_MODE_DESC1               *pdm1 = (const DXGI_MODE_DESC1*)arg1;
    const DXGI_MODE_DESC1               *pdm2 = (const DXGI_MODE_DESC1*)arg2;

    if (pdm1->Width > pdm2->Width) return 1;
    if (pdm1->Width < pdm2->Width) return -1;
    if (pdm1->Height > pdm2->Height) return 1;
    if (pdm1->Height < pdm2->Height) return -1;
    if (pdm1->Format > pdm2->Format) return 1;
    if (pdm1->Format < pdm2->Format) return -1;
    if (pdm1->RefreshRate.Numerator > pdm2->RefreshRate.Numerator) return 1;
    if (pdm1->RefreshRate.Numerator < pdm2->RefreshRate.Numerator) return -1;
    return 0;
}


/* ---- tgKN_GPU_EXT_Debug_Layer_Configuration ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgKN_GPU_EXT_Debug_Layer_Configuration( STg2_KN_GPU_EXT_Adapter_P psGPU_EXT_Adapter )
{
#if defined(TgBUILD_ENABLE_D3D_DEBUG) && TgBUILD_ENABLE_D3D_DEBUG
    ID3D12DebugDevice2_P                psDX12_Debug_Interface;

    if (SUCCEEDED(ID3D12Device10_QueryInterface( psGPU_EXT_Adapter->m_psDX12_Device, MS_REF IID_ID3D12DebugDevice2,(TgVOID_PP)&psDX12_Debug_Interface )))
    {
        ID3D12InfoQueue1_P                  psDX12_Info_Queue;

        /* TODO: None of this works, for no clear reason. */
        if (SUCCEEDED(ID3D12Debug2_QueryInterface( psDX12_Debug_Interface, MS_REF IID_ID3D12InfoQueue1, (TgVOID_PP)&psDX12_Info_Queue )))
        {
            // Suppress messages based on their severity level
            D3D12_MESSAGE_SEVERITY Severities[] =
            {
                D3D12_MESSAGE_SEVERITY_INFO,
                D3D12_MESSAGE_SEVERITY_MESSAGE,
            };

            D3D12_MESSAGE_ID Messages[] =
            {
                // Workarounds for debug layer issues
                D3D12_MESSAGE_ID_RESOURCE_BARRIER_MISMATCHING_COMMAND_LIST_TYPE,
            };

            D3D12_INFO_QUEUE_FILTER sDX12_New_Filter;

            tgMM_Set_U08_0x00( &sDX12_New_Filter, sizeof(sDX12_New_Filter) );

            sDX12_New_Filter.DenyList.NumSeverities = TgARRAY_COUNT(Severities);
            sDX12_New_Filter.DenyList.pSeverityList = Severities;
            sDX12_New_Filter.DenyList.NumIDs = TgARRAY_COUNT(Messages);
            sDX12_New_Filter.DenyList.pIDList = Messages;

            ID3D12InfoQueue1_PushStorageFilter( psDX12_Info_Queue, &sDX12_New_Filter );

            ID3D12InfoQueue1_RegisterMessageCallback( psDX12_Info_Queue, tgKN_GPU_EXT_Message_Function, D3D12_MESSAGE_CALLBACK_FLAG_NONE, nullptr, &psGPU_EXT_Adapter->m_dwCookie );

            TgVERIFY(SUCCEEDED(ID3D12InfoQueue1_SetBreakOnCategory( psDX12_Info_Queue, D3D12_MESSAGE_CATEGORY_STATE_CREATION, false )));

            TgVERIFY(SUCCEEDED(ID3D12InfoQueue1_SetBreakOnSeverity( psDX12_Info_Queue, D3D12_MESSAGE_SEVERITY_CORRUPTION, false )));
            TgVERIFY(SUCCEEDED(ID3D12InfoQueue1_SetBreakOnSeverity( psDX12_Info_Queue, D3D12_MESSAGE_SEVERITY_ERROR, false )));
            TgVERIFY(SUCCEEDED(ID3D12InfoQueue1_SetBreakOnSeverity( psDX12_Info_Queue, D3D12_MESSAGE_SEVERITY_WARNING, false )));
            TgVERIFY(SUCCEEDED(ID3D12InfoQueue1_SetBreakOnSeverity( psDX12_Info_Queue, D3D12_MESSAGE_SEVERITY_INFO, false )));
            TgVERIFY(SUCCEEDED(ID3D12InfoQueue1_SetBreakOnSeverity( psDX12_Info_Queue, D3D12_MESSAGE_SEVERITY_MESSAGE, false )));

            TgVERIFY(SUCCEEDED(ID3D12InfoQueue1_SetBreakOnID( psDX12_Info_Queue, D3D12_MESSAGE_ID_LIVE_COMMANDQUEUE, false )));
            TgVERIFY(SUCCEEDED(ID3D12InfoQueue1_SetBreakOnID( psDX12_Info_Queue, D3D12_MESSAGE_ID_LIVE_COMMANDALLOCATOR, false )));
            TgVERIFY(SUCCEEDED(ID3D12InfoQueue1_SetBreakOnID( psDX12_Info_Queue, D3D12_MESSAGE_ID_LIVE_PIPELINESTATE, false )));
            TgVERIFY(SUCCEEDED(ID3D12InfoQueue1_SetBreakOnID( psDX12_Info_Queue, D3D12_MESSAGE_ID_LIVE_COMMANDLIST12, false )));
            TgVERIFY(SUCCEEDED(ID3D12InfoQueue1_SetBreakOnID( psDX12_Info_Queue, D3D12_MESSAGE_ID_LIVE_RESOURCE, false )));
            TgVERIFY(SUCCEEDED(ID3D12InfoQueue1_SetBreakOnID( psDX12_Info_Queue, D3D12_MESSAGE_ID_LIVE_DESCRIPTORHEAP, false )));
            TgVERIFY(SUCCEEDED(ID3D12InfoQueue1_SetBreakOnID( psDX12_Info_Queue, D3D12_MESSAGE_ID_LIVE_ROOTSIGNATURE, false )));
            TgVERIFY(SUCCEEDED(ID3D12InfoQueue1_SetBreakOnID( psDX12_Info_Queue, D3D12_MESSAGE_ID_LIVE_LIBRARY, false )));
            TgVERIFY(SUCCEEDED(ID3D12InfoQueue1_SetBreakOnID( psDX12_Info_Queue, D3D12_MESSAGE_ID_LIVE_HEAP, false )));
            TgVERIFY(SUCCEEDED(ID3D12InfoQueue1_SetBreakOnID( psDX12_Info_Queue, D3D12_MESSAGE_ID_LIVE_MONITOREDFENCE, false )));
            TgVERIFY(SUCCEEDED(ID3D12InfoQueue1_SetBreakOnID( psDX12_Info_Queue, D3D12_MESSAGE_ID_LIVE_QUERYHEAP, false )));
            TgVERIFY(SUCCEEDED(ID3D12InfoQueue1_SetBreakOnID( psDX12_Info_Queue, D3D12_MESSAGE_ID_LIVE_COMMANDSIGNATURE, false )));

            TgVERIFY(SUCCEEDED(ID3D12InfoQueue1_SetBreakOnID( psDX12_Info_Queue, D3D12_MESSAGE_ID_OBJECT_ACCESSED_WHILE_STILL_IN_USE, false )));

            ID3D12InfoQueue1_Release( psDX12_Info_Queue );
        }
        ID3D12Debug2_Release( psDX12_Debug_Interface );
    }
#else
    (void)psGPU_EXT_Adapter;
/*# defined(TgBUILD_ENABLE_D3D_DEBUG) && TgBUILD_ENABLE_D3D_DEBUG */
#endif
}


/* ---- tgKN_GPU_EXT_Message_Function -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if defined(TgBUILD_ENABLE_D3D_DEBUG) && TgBUILD_ENABLE_D3D_DEBUG
static TgVOID CDECL tgKN_GPU_EXT_Message_Function( TgATTRIBUTE_UNUSED D3D12_MESSAGE_CATEGORY enCat, TgATTRIBUTE_UNUSED D3D12_MESSAGE_SEVERITY enSev,
                                                   TgATTRIBUTE_UNUSED D3D12_MESSAGE_ID enID, TgATTRIBUTE_UNUSED LPCSTR pszDesc,
                                                   TgATTRIBUTE_UNUSED void* pVoid ) TgATTRIBUTE_NO_EXCEPT
{
    return;
}
/*# defined(TgBUILD_ENABLE_D3D_DEBUG) && TgBUILD_ENABLE_D3D_DEBUG */
#endif
