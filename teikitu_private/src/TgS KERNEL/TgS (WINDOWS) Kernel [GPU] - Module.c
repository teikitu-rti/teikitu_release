/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (WINDOWS) Kernel [GPU] - Module.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
#if defined(TgBUILD_FEATURE__GRAPHICS)

#include "TgS Kernel [GPU] - Internal.h"

#include "TgS (DXGI) Kernel [GPU] - Internal.h"


/* == Kernel ===================================================================================================================================================================== */

IDXGIFactory7                               *g_pDXGIFactory = nullptr;
STg2_KN_OS_GPU_DXGI_Output                  g_asDXGI_Output[KTgKN_GPU_MAX_OUTPUT];
TgRSIZE                                     g_nuiDXGI_Output;
STg2_KN_OS_GPU_DXGI_CXT_SWAP                g_asOS_EXT_Swap_Context_Output[KTgKN_GPU_MAX_SWAP_CONTEXT];

static const DXGI_FORMAT KTgKN_GPU_DXGI_FORMAT_RT_SCANOUT[] = {
    DXGI_FORMAT_R16G16B16A16_FLOAT, // ETgKN_GPU_EXT_FORMAT_R16G16B16A16_FLOAT,
    DXGI_FORMAT_R10G10B10A2_UNORM, // ETgKN_GPU_EXT_FORMAT_R10G10B10A2_UNORM,
    DXGI_FORMAT_R8G8B8A8_UNORM, // ETgKN_GPU_EXT_FORMAT_R8G8B8A8_UNORM,
    DXGI_FORMAT_R8G8B8A8_UNORM_SRGB, // ETgKN_GPU_EXT_FORMAT_R8G8B8A8_UNORM_SRGB,
    DXGI_FORMAT_B8G8R8A8_UNORM, // ETgKN_GPU_EXT_FORMAT_B8G8R8A8_UNORM,
    DXGI_FORMAT_B8G8R8A8_UNORM_SRGB, // ETgKN_GPU_EXT_FORMAT_B8G8R8A8_UNORM_SRGB,
};




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  External Types and Functions                                                                                                                                                   */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgEXTN TgBOOL
tgSI_APP_Is_Remote_Session( TgVOID );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Data and Exports                                                                                                                                                    */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

static TgVOID
tgKN_OS_GPU_Device_Change_Check(
    HWND hWnd, STg2_KN_OS_Window_Configuration_PC psConfig );

static TgSINT_E32 CDECL
tgKN_OS_GPU_DXGI_Quick_Sort__DXGI_MODE_DESC(
    TgVOID_CPC arg1, TgVOID_CPC arg2 ) TgATTRIBUTE_NO_EXCEPT;

static TgVOID
tgKN_OS_GPU_DXGI_Enumerate_Adapters_And_Outputs( TgVOID );

static TgVOID
tgKN_OS_GPU_DXGI_Free_Adapters_And_Outputs( TgVOID );

/** @brief Initialize the output structure.
    @param [in] ARG0 Display 
    @param [in] ARG1 Display name */
static TgVOID
tgKN_OS_GPU_CXT_SWAP_Init(
     TgRSIZE ARG0, TgCHAR_WC_CP ARG1 );

/** @brief Initialize the output structure.
    @param [in] ARG0 Display */
static TgVOID
tgKN_OS_GPU_CXT_SWAP_Free(
     TgRSIZE ARG0 );


#if TgCOMPILE__CONSOLE && (TgS_STAT__KERNEL || TgS_DEBUG__KERNEL)
static TgVOID
tgKN_GPU_EXT_STAT_Print_Physical_Devices(
    TgUINT_E32_C nuiArg, TgCHAR_U8_CP pArgV[KTgMAX_CMD_LINE_COUNT] ) TgATTRIBUTE_NO_EXCEPT;

static const TgCHAR_U8                      s_szSTAT_Print_Physical_Devices[] = u8"STAT_Print_Physical_Devices";
/*# TgCOMPILE__CONSOLE && (TgS_STAT__KERNEL || TgS_DEBUG__KERNEL) */
#endif


static HINSTANCE                            s_hDLL_DXGI = nullptr;
static HINSTANCE                            s_hext_ms_win_ntuser_sysparams_ext_l1_1_1 = nullptr;

static TgUINT_E32                           s_uiCreateFlag = 0;

static ULONG                                (__stdcall *s_pfnGetDisplayConfigBufferSizes)( UINT32, UINT32*, UINT32* );
static ULONG                                (__stdcall *s_pfnQueryDisplayConfig)( UINT32, UINT32*, DISPLAYCONFIG_PATH_INFO*, UINT32*, DISPLAYCONFIG_MODE_INFO*,
                                                                                  DISPLAYCONFIG_TOPOLOGY_ID* );
static ULONG                                (__stdcall *s_pfnDisplayConfigGetDeviceInfo)( DISPLAYCONFIG_DEVICE_INFO_HEADER* );


TgCOMPILER_ASSERT( (TgSINT_E32)KTgKN_MAX_WINDOWS == (TgSINT_E32)KTgKN_GPU_MAX_SWAP_CONTEXT, 0 );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_OS_GPU_Module_Init -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_OS_GPU_Module_Init( TgVOID )
{
    TgERROR( nullptr == g_pfnDXGICreateDXGIFactory );

    TgERROR( nullptr == g_pfnDXGIGetDebugInterface1 );

    s_hDLL_DXGI = nullptr;
    s_hext_ms_win_ntuser_sysparams_ext_l1_1_1 = nullptr;

    tgMM_Set_U08_0x00( &g_asDXGI_Output, sizeof( g_asDXGI_Output ) );
    g_nuiDXGI_Output = 0;
    tgMM_Set_U08_0x00( &g_asOS_EXT_Swap_Context_Output, sizeof( g_asOS_EXT_Swap_Context_Output ) );

    /* Loads the necessary functions from DXGI */
    if (!tgGB_Load_Lib( &s_hDLL_DXGI, TgOS_TEXT("dxgi.dll") ))
    {
        TgCRITICAL_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to load DXGI DLL." );
        goto tgKN_OS_GPU_Module_Init_FAIL;
    };

    if (
           !tgGB_Get_Func_Address( (FARPROC*)&g_pfnDXGICreateDXGIFactory, s_hDLL_DXGI, "CreateDXGIFactory2" )
#if !defined(TGS_FINAL)
        || !tgGB_Get_Func_Address( (FARPROC*)&g_pfnDXGIGetDebugInterface1, s_hDLL_DXGI, "DXGIGetDebugInterface1" )
/*# !defined(TGS_FINAL) */
#endif
    )
    {
        TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to find function in DXGI DLL." );
        goto tgKN_OS_GPU_Module_Init_FAIL;
    };

    if (!tgGB_Load_Lib( &s_hext_ms_win_ntuser_sysparams_ext_l1_1_1, TgOS_TEXT("ext-ms-win-ntuser-sysparams-ext-l1-1-1.dll") ))
    {
        TgCRITICAL_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to load ext-ms-win-ntuser-sysparams-ext-l1-1-1 DLL." );
        goto tgKN_OS_GPU_Module_Init_FAIL;
    };

    if (
           !tgGB_Get_Func_Address( (FARPROC *)&s_pfnGetDisplayConfigBufferSizes, s_hext_ms_win_ntuser_sysparams_ext_l1_1_1, ("GetDisplayConfigBufferSizes") )
        || !tgGB_Get_Func_Address( (FARPROC *)&s_pfnQueryDisplayConfig, s_hext_ms_win_ntuser_sysparams_ext_l1_1_1, ("QueryDisplayConfig") )
        || !tgGB_Get_Func_Address( (FARPROC *)&s_pfnDisplayConfigGetDeviceInfo, s_hext_ms_win_ntuser_sysparams_ext_l1_1_1, ("DisplayConfigGetDeviceInfo") )
        )
    {
        TgCRITICAL_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to find function in ext-ms-win-ntuser-sysparams-ext-l1-1-1 DLL" );
        goto tgKN_OS_GPU_Module_Init_FAIL;
    };

    g_pfnDevice_Change_Check = tgKN_OS_GPU_Device_Change_Check;
    g_pfnQuery_Monitor_Min_Resolution = tgKN_OS_GPU_Query_Monitor_Min_Resolution;
    g_pfnQuery_Monitor_Max_Resolution = tgKN_OS_GPU_Query_Monitor_Max_Resolution;
    g_pfnQuery_CXT_SWAP_Query_Mode = tgKN_OS_GPU_CXT_SWAP_Query_Mode;
    g_pfnQuery_CXT_SWAP_Query_Mode_Rounded_Down = tgKN_OS_GPU_CXT_SWAP_Query_Mode_Rounded_Down;

    return (KTgS_OK);

tgKN_OS_GPU_Module_Init_FAIL:
    tgKN_OS_GPU_Module_Free();
    return (KTgE_FAIL);
}


/* ---- tgKN_OS_GPU_Module_Boot -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_OS_GPU_Module_Boot( TgVOID )
{
    TgPARAM_CHECK( nullptr != g_pfnDXGICreateDXGIFactory );
    s_uiCreateFlag = 0;

#if defined(TgBUILD_ENABLE_DXGI_DEBUG) && TgBUILD_ENABLE_DXGI_DEBUG
    {
        IDXGIInfoQueue                      *psDXGI_Info_Queue;
        DXGI_INFO_QUEUE_FILTER              sDXGI_Info_Queue_Filter;

        /* ** NOTE: MSFT emits messages from this queue prefixed with D3D12 (during adapter initialization). ** */

        if (g_pfnDXGIGetDebugInterface1 && SUCCEEDED(g_pfnDXGIGetDebugInterface1( 0, MS_REF IID_IDXGIInfoQueue, (TgVOID_PP)&psDXGI_Info_Queue )))
        {
            DXGI_INFO_QUEUE_MESSAGE_SEVERITY Severities[] = {
                DXGI_INFO_QUEUE_MESSAGE_SEVERITY_INFO,
                DXGI_INFO_QUEUE_MESSAGE_SEVERITY_MESSAGE
            };

            tgMM_Set_U08_0x00( &sDXGI_Info_Queue_Filter, sizeof( DXGI_INFO_QUEUE_FILTER ) );

            sDXGI_Info_Queue_Filter.DenyList.pSeverityList = Severities;
            sDXGI_Info_Queue_Filter.DenyList.NumSeverities = TgARRAY_COUNT(Severities);

            TgVERIFY(SUCCEEDED(IDXGIInfoQueue_PushStorageFilter(psDXGI_Info_Queue, DXGI_DEBUG_ALL, &sDXGI_Info_Queue_Filter)));

            TgVERIFY(SUCCEEDED(IDXGIInfoQueue_SetBreakOnSeverity(psDXGI_Info_Queue, DXGI_DEBUG_ALL, DXGI_INFO_QUEUE_MESSAGE_SEVERITY_CORRUPTION, TRUE)));
            TgVERIFY(SUCCEEDED(IDXGIInfoQueue_SetBreakOnSeverity(psDXGI_Info_Queue, DXGI_DEBUG_ALL, DXGI_INFO_QUEUE_MESSAGE_SEVERITY_ERROR, TRUE)));
            TgVERIFY(SUCCEEDED(IDXGIInfoQueue_SetBreakOnSeverity(psDXGI_Info_Queue, DXGI_DEBUG_ALL, DXGI_INFO_QUEUE_MESSAGE_SEVERITY_WARNING, FALSE)));
            TgVERIFY(SUCCEEDED(IDXGIInfoQueue_SetBreakOnSeverity(psDXGI_Info_Queue, DXGI_DEBUG_ALL, DXGI_INFO_QUEUE_MESSAGE_SEVERITY_INFO, FALSE)));
            TgVERIFY(SUCCEEDED(IDXGIInfoQueue_SetBreakOnSeverity(psDXGI_Info_Queue, DXGI_DEBUG_ALL, DXGI_INFO_QUEUE_MESSAGE_SEVERITY_MESSAGE, FALSE)));

            IDXGIInfoQueue_Release( psDXGI_Info_Queue );
            s_uiCreateFlag |= DXGI_CREATE_FACTORY_DEBUG;
        };
    };

    {
        IDXGIDebug1                         *psDXGI_Debug_1;

        if (g_pfnDXGIGetDebugInterface1 && SUCCEEDED(g_pfnDXGIGetDebugInterface1( 0, MS_REF IID_IDXGIDebug1, (TgVOID_PP)&psDXGI_Debug_1 )))
        {
            IDXGIDebug1_EnableLeakTrackingForThread(psDXGI_Debug_1);
            IDXGIDebug1_Release( psDXGI_Debug_1 );
        }
    };
/*# defined(TgBUILD_ENABLE_DXGI_DEBUG) && TgBUILD_ENABLE_DXGI_DEBUG */
#endif

    /* Creating the DXGI Factory is a side effect of this function. */
    tgKN_OS_GPU_CXT_SWAP_Update_Output( KTgKN_GPU_CXT_SWAP_ID__INVALID, 0, false );

    tgCN_Insert_Command_Function( s_szSTAT_Print_Physical_Devices, tgUSZ_Length_U08( s_szSTAT_Print_Physical_Devices, KTgMAX_RSIZE ),
                                  tgKN_GPU_EXT_STAT_Print_Physical_Devices, u8"", 1 );

    return (KTgS_OK);
}


/* ---- tgKN_OS_GPU_Module_Stop -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_OS_GPU_Module_Stop( TgVOID )
{
    TgRSIZE                             uiIndex;

    tgCN_Remove_Command_Function( s_szSTAT_Print_Physical_Devices, tgUSZ_Length_U08( s_szSTAT_Print_Physical_Devices, KTgMAX_RSIZE ) );

    tgKN_OS_GPU_DXGI_Free_Adapters_And_Outputs();

    for (uiIndex = 0; uiIndex < KTgKN_GPU_MAX_SWAP_CONTEXT; ++uiIndex)
    {
        tgKN_OS_GPU_CXT_SWAP_Free( uiIndex );
    };

    if (nullptr != g_pDXGIFactory)
    {
        TgVERIFY(0 == IDXGIFactory7_Release( g_pDXGIFactory ));
        g_pDXGIFactory = nullptr;
    };

#if defined(TgBUILD_ENABLE_DXGI_DEBUG) && TgBUILD_ENABLE_DXGI_DEBUG
    {
        IDXGIDebug                          *psDXGI_Debug;
        if (g_pfnDXGIGetDebugInterface1 && SUCCEEDED(g_pfnDXGIGetDebugInterface1( 0, MS_REF IID_IDXGIDebug, (TgVOID_PP)&psDXGI_Debug )))
        {
            IDXGIDebug_ReportLiveObjects(psDXGI_Debug, DXGI_DEBUG_ALL, (DXGI_DEBUG_RLO_FLAGS)(DXGI_DEBUG_RLO_ALL) );
            IDXGIDebug_Release( psDXGI_Debug );
        }
    }
/*# defined(TgBUILD_ENABLE_DXGI_DEBUG) && TgBUILD_ENABLE_DXGI_DEBUG */
#endif
}


/* ---- tgKN_OS_GPU_Module_Free -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_OS_GPU_Module_Free( TgVOID )
{
    g_pfnDXGIGetDebugInterface1 = nullptr;
    g_pfnDXGICreateDXGIFactory = nullptr;

    s_pfnGetDisplayConfigBufferSizes = nullptr;
    s_pfnQueryDisplayConfig = nullptr;
    s_pfnDisplayConfigGetDeviceInfo = nullptr;

    tgGB_Free_Lib( &s_hext_ms_win_ntuser_sysparams_ext_l1_1_1 );
    tgGB_Free_Lib( &s_hDLL_DXGI );

    s_hext_ms_win_ntuser_sysparams_ext_l1_1_1 = nullptr;
    s_hDLL_DXGI = nullptr;
}


/* ---- tgKN_OS_GPU_CXT_SWAP_Update_Output --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_OS_GPU_CXT_SWAP_Update_Output( TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP, TgUINT_PTR_C uiOS_ID, TgBOOL_C bValidateOutputDevice )
{
    STg2_KN_GPU_CXT_SWAP_PC             psCXT_SWAP = g_asKN_GPU_CXT_SWAP + tiCXT_SWAP.m_uiI;

    union { HWND hWnd; TgUINT_PTR uiPTR; } const sHWND = { .uiPTR = uiOS_ID };

    TgRSIZE                             uiBest_Output;

    TgPARAM_CHECK(s_pfnDisplayConfigGetDeviceInfo);

    /* The DXGI factory has to be recreated if it is null, or if there has been a sufficient change in the graphics layer (e.g. change in OS HDR settings). */
    /* MSFT recommends checking every frame. */

    if (!g_pDXGIFactory || !IDXGIFactory7_IsCurrent( g_pDXGIFactory ))
    {
        IDXGIFactory                        *psDXGI_Factory_0;

        g_pfnDXGICreateDXGIFactory( s_uiCreateFlag, MS_REF IID_IDXGIFactory, (TgVOID_PP)&psDXGI_Factory_0 );
        if (nullptr == psDXGI_Factory_0)
        {
            return;
        }

        if (FAILED(IDXGIFactory_QueryInterface( psDXGI_Factory_0, MS_REF(IID_IDXGIFactory7), (TgVOID_PP)&g_pDXGIFactory )))
        {
            TgVERIFY(0 == IDXGIFactory_Release( psDXGI_Factory_0 ));
            psDXGI_Factory_0 = nullptr;
            return;
        }
        TgVERIFY( 1 == IDXGIFactory_Release( psDXGI_Factory_0 ) );

        tgKN_OS_GPU_DXGI_Enumerate_Adapters_And_Outputs();
    }

    if (0 == sHWND.uiPTR)
    {
        return;
    }

    uiBest_Output = KTgMAX_UMAX;

    if (bValidateOutputDevice)
    {
        RECT                                rcWindow;
        TgRECT2D_F32_04                     sWindow;
        TgUINT_E32                          uiOutput;
        TgFLOAT32                           fBest_Intersect_Area;

        /* Get the bounds of the attached window. */

        g_pfnGetWindowRect( sHWND.hWnd, &rcWindow );

        sWindow.m_uRect.m_vS_F32_04_1.x = (TgFLOAT32)rcWindow.left;
        sWindow.m_uRect.m_vS_F32_04_1.y = (TgFLOAT32)rcWindow.top;
        sWindow.m_uRect.m_vS_F32_04_1.z = (TgFLOAT32)rcWindow.right;
        sWindow.m_uRect.m_vS_F32_04_1.w = (TgFLOAT32)rcWindow.bottom;

        /* Search for the output device that has the greatest coverage of the render area. */

        fBest_Intersect_Area = 0.0F;

        for (uiOutput = 0; uiOutput < g_nuiDXGI_Output; ++uiOutput)
        {
            TgRECT2D_F32_04                     sOutput;
            TgFLOAT32                           fIntersect_Area;

            sOutput.m_uRect.m_vS_F32_04_1.x = (TgFLOAT32)g_asDXGI_Output[uiOutput].m_sDXGI_Output_DESC.DesktopCoordinates.left;
            sOutput.m_uRect.m_vS_F32_04_1.y = (TgFLOAT32)g_asDXGI_Output[uiOutput].m_sDXGI_Output_DESC.DesktopCoordinates.top;
            sOutput.m_uRect.m_vS_F32_04_1.z = (TgFLOAT32)g_asDXGI_Output[uiOutput].m_sDXGI_Output_DESC.DesktopCoordinates.right;
            sOutput.m_uRect.m_vS_F32_04_1.w = (TgFLOAT32)g_asDXGI_Output[uiOutput].m_sDXGI_Output_DESC.DesktopCoordinates.bottom;

            fIntersect_Area = tgGM_Intersection_Area_RT2D_F32_04( &sWindow, &sOutput );
            if (fIntersect_Area > fBest_Intersect_Area)
            {
                uiBest_Output = uiOutput;
                fBest_Intersect_Area = fIntersect_Area;
            }
        }

        if (KTgMAX_UMAX == uiBest_Output)
        {
            /* If we have not found a best fit output device - the window could be off-screen (i.e. it is not an invalid state). However, since there is nothing to see, the
               remaining parts of this function are not required. */
            psCXT_SWAP->m_bOS_Scanout_Valid = false;
            return;
        }

        /* Now that we have found a best fit output device - record the characteristics of the device. */

        psCXT_SWAP->m_sOutput_DESC.m_iBits_Per_Colour = (TgSINT_E32)g_asDXGI_Output[uiBest_Output].m_sDXGI_Output_DESC.BitsPerColor;
        psCXT_SWAP->m_sOutput_DESC.m_fRed_Primary_0 = g_asDXGI_Output[uiBest_Output].m_sDXGI_Output_DESC.RedPrimary[0];
        psCXT_SWAP->m_sOutput_DESC.m_fRed_Primary_1 = g_asDXGI_Output[uiBest_Output].m_sDXGI_Output_DESC.RedPrimary[1];
        psCXT_SWAP->m_sOutput_DESC.m_fGreen_Primary_0 = g_asDXGI_Output[uiBest_Output].m_sDXGI_Output_DESC.GreenPrimary[0];
        psCXT_SWAP->m_sOutput_DESC.m_fGreen_Primary_1 = g_asDXGI_Output[uiBest_Output].m_sDXGI_Output_DESC.GreenPrimary[1];
        psCXT_SWAP->m_sOutput_DESC.m_fBlue_Primary_0 = g_asDXGI_Output[uiBest_Output].m_sDXGI_Output_DESC.BluePrimary[0];
        psCXT_SWAP->m_sOutput_DESC.m_fBlue_Primary_1 = g_asDXGI_Output[uiBest_Output].m_sDXGI_Output_DESC.BluePrimary[1];
        psCXT_SWAP->m_sOutput_DESC.m_fWhite_Point_0 = g_asDXGI_Output[uiBest_Output].m_sDXGI_Output_DESC.WhitePoint[0];
        psCXT_SWAP->m_sOutput_DESC.m_fWhite_Point_1 = g_asDXGI_Output[uiBest_Output].m_sDXGI_Output_DESC.WhitePoint[1];
        psCXT_SWAP->m_sOutput_DESC.m_fMin_Luminance = g_asDXGI_Output[uiBest_Output].m_sDXGI_Output_DESC.MinLuminance;
        psCXT_SWAP->m_sOutput_DESC.m_fMax_Luminance = g_asDXGI_Output[uiBest_Output].m_sDXGI_Output_DESC.MaxLuminance;
        psCXT_SWAP->m_sOutput_DESC.m_fMax_Full_Frame_Luminance = g_asDXGI_Output[uiBest_Output].m_sDXGI_Output_DESC.MaxFullFrameLuminance;

        switch (g_asDXGI_Output[uiBest_Output].m_sDXGI_Output_DESC.ColorSpace) {
        case DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P709:
            psCXT_SWAP->m_sOutput_DESC.m_iColour_Space = ETgKN_GPU_HLSL_COLOUR_SPACE_G22_P709;
            break;
        case DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020:
            psCXT_SWAP->m_sOutput_DESC.m_iColour_Space = ETgKN_GPU_HLSL_COLOUR_SPACE_G2084_P2020;
            break;
        case DXGI_COLOR_SPACE_RGB_FULL_G10_NONE_P709:
            psCXT_SWAP->m_sOutput_DESC.m_iColour_Space = ETgKN_GPU_HLSL_COLOUR_SPACE_G10_P709;
            break;
        case DXGI_COLOR_SPACE_RGB_STUDIO_G22_NONE_P709:
        case DXGI_COLOR_SPACE_RGB_STUDIO_G22_NONE_P2020:
        case DXGI_COLOR_SPACE_RESERVED:
        case DXGI_COLOR_SPACE_YCBCR_FULL_G22_NONE_P709_X601:
        case DXGI_COLOR_SPACE_YCBCR_STUDIO_G22_LEFT_P601:
        case DXGI_COLOR_SPACE_YCBCR_FULL_G22_LEFT_P601:
        case DXGI_COLOR_SPACE_YCBCR_STUDIO_G22_LEFT_P709:
        case DXGI_COLOR_SPACE_YCBCR_FULL_G22_LEFT_P709:
        case DXGI_COLOR_SPACE_YCBCR_STUDIO_G22_LEFT_P2020:
        case DXGI_COLOR_SPACE_YCBCR_FULL_G22_LEFT_P2020:
        case DXGI_COLOR_SPACE_YCBCR_STUDIO_G2084_LEFT_P2020:
        case DXGI_COLOR_SPACE_RGB_STUDIO_G2084_NONE_P2020:
        case DXGI_COLOR_SPACE_YCBCR_STUDIO_G22_TOPLEFT_P2020:
        case DXGI_COLOR_SPACE_YCBCR_STUDIO_G2084_TOPLEFT_P2020:
        case DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P2020:
        case DXGI_COLOR_SPACE_YCBCR_STUDIO_GHLG_TOPLEFT_P2020:
        case DXGI_COLOR_SPACE_YCBCR_FULL_GHLG_TOPLEFT_P2020:
        case DXGI_COLOR_SPACE_RGB_STUDIO_G24_NONE_P709:
        case DXGI_COLOR_SPACE_RGB_STUDIO_G24_NONE_P2020:
        case DXGI_COLOR_SPACE_YCBCR_STUDIO_G24_LEFT_P709:
        case DXGI_COLOR_SPACE_YCBCR_STUDIO_G24_LEFT_P2020:
        case DXGI_COLOR_SPACE_YCBCR_STUDIO_G24_TOPLEFT_P2020:
        case DXGI_COLOR_SPACE_CUSTOM:
            psCXT_SWAP->m_sOutput_DESC.m_iColour_Space = ETgKN_GPU_HLSL_COLOUR_SPACE_UNKNOWN;
            break;
        }

        psCXT_SWAP->m_bOS_Scanout_Valid = true;
        psCXT_SWAP->m_bHDR_Supported  = g_asDXGI_Output[uiBest_Output].m_sDXGI_Output_DESC.ColorSpace == DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020;
        psCXT_SWAP->m_bHDR_Supported |= g_asDXGI_Output[uiBest_Output].m_sDXGI_Output_DESC.ColorSpace == DXGI_COLOR_SPACE_RGB_FULL_G10_NONE_P709;

        g_asOS_EXT_Swap_Context_Output[tiCXT_SWAP.m_uiI].m_uiBest_Output = uiBest_Output;
        g_asOS_EXT_Swap_Context_Output[tiCXT_SWAP.m_uiI].m_bInit = false;
    }
    else if (psCXT_SWAP->m_bOS_Scanout_Valid)
    {
        uiBest_Output = g_asOS_EXT_Swap_Context_Output[tiCXT_SWAP.m_uiI].m_uiBest_Output;
    }
    else
    {
        return;
    }

    /* Query the windows OS for current graphics related settings. */

    if (!g_asOS_EXT_Swap_Context_Output[tiCXT_SWAP.m_uiI].m_bInit)
    {
        tgKN_OS_GPU_CXT_SWAP_Init( tiCXT_SWAP.m_uiI, g_asDXGI_Output[uiBest_Output].m_sDXGI_Output_DESC.DeviceName );
    }

    if (g_asOS_EXT_Swap_Context_Output[tiCXT_SWAP.m_uiI].m_bInit)
    {
        DISPLAYCONFIG_SDR_WHITE_LEVEL       sDevice_Info;

        tgMM_Set_U08_0x00( &sDevice_Info, sizeof( sDevice_Info ) );

        sDevice_Info.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_SDR_WHITE_LEVEL;
        sDevice_Info.header.size = sizeof( DISPLAYCONFIG_SDR_WHITE_LEVEL  );
        sDevice_Info.header.adapterId = g_asOS_EXT_Swap_Context_Output[tiCXT_SWAP.m_uiI].m_sPath_Info.targetInfo.adapterId;
        sDevice_Info.header.id = g_asOS_EXT_Swap_Context_Output[tiCXT_SWAP.m_uiI].m_sPath_Info.targetInfo.id;

        s_pfnDisplayConfigGetDeviceInfo( &sDevice_Info.header );

        psCXT_SWAP->m_sOutput_DESC.m_fSDR_In_HDR_Nits_Level = ((TgFLOAT32)sDevice_Info.SDRWhiteLevel / 1000.0F) * 80.0F;
        psCXT_SWAP->m_sOutput_DESC.m_fPerceptual_Exponent = 2.2F;
    }
}


/* ---- tgKN_OS_GPU_DXGI_Enumerate_Output_Modes ---------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_OS_GPU_DXGI_Enumerate_Output_Modes( DXGI_MODE_DESC1_PP ppsModes, TgRSIZE_P pnuiMode, UINT *pnuiMode_ScanOut, IDXGIOutput6_P psDXGI_Output  )
{
    UINT                                nuiModeFormat[KTgKN_GPU_EXT_FORMAT_RT_SCANOUT_MAX];
    TgRSIZE                             nuiMode, nuiModeMax;
    TgRSIZE                             uiIndex, uiFormat;
    HRESULT                             iRet;
    DXGI_MODE_DESC1_P                   psModes;
    TgRSIZE                             uiIndex_Unique;

    TgPARAM_CHECK((nullptr != ppsModes) && (nullptr != pnuiMode) && (nullptr != psDXGI_Output));

    nuiModeMax = 2048;
    nuiMode = 0;
    uiFormat = 0;

    psModes = (DXGI_MODE_DESC1_P)TgMALLOC_TEMP(sizeof(DXGI_MODE_DESC1)*nuiModeMax);
    TgCRITICAL(0 != psModes);

    /* Enumerate all display modes for this output using the render target format list. */
    while (uiFormat < KTgKN_GPU_EXT_FORMAT_RT_SCANOUT_MAX)
    {
        nuiModeFormat[uiFormat] = (UINT)(nuiModeMax - nuiMode);
        iRet = IDXGIOutput6_GetDisplayModeList1(
            psDXGI_Output, (DXGI_FORMAT)KTgKN_GPU_DXGI_FORMAT_RT_SCANOUT[uiFormat], DXGI_ENUM_MODES_SCALING, nuiModeFormat + uiFormat, psModes + nuiMode );

        if (DXGI_ERROR_NOT_FOUND == iRet)
        {
            TgFREE_TEMP( psModes );
            *ppsModes = nullptr;
            *pnuiMode = 0;
            return;
        };

        /* Make a single fake display mode for remote sessions */
        if ((DXGI_ERROR_NOT_CURRENTLY_AVAILABLE == iRet) && (DXGI_FORMAT_R8G8B8A8_UNORM == (DXGI_FORMAT)KTgKN_GPU_DXGI_FORMAT_RT_SCANOUT[uiFormat]))
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

    if (0 == nuiMode)
    {
        *ppsModes = nullptr;
        *pnuiMode = 0;
        return;
    }

    /* Sort the modes for the selection routines and remove duplicates */
    qsort( psModes, nuiMode, sizeof(DXGI_MODE_DESC1), tgKN_OS_GPU_DXGI_Quick_Sort__DXGI_MODE_DESC );
    for (uiIndex_Unique = 0, uiIndex = 1; uiIndex < nuiMode; ++uiIndex)
    {
        if (0 != tgKN_OS_GPU_DXGI_Quick_Sort__DXGI_MODE_DESC( psModes + uiIndex_Unique, psModes + uiIndex ))
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

    *ppsModes = (DXGI_MODE_DESC1*)TgMALLOC_POOL(sizeof(DXGI_MODE_DESC1)*nuiMode);
    *pnuiMode = nuiMode;

    tgMM_Copy( *ppsModes, sizeof(DXGI_MODE_DESC1)*nuiMode, psModes, sizeof(DXGI_MODE_DESC1)*nuiMode );
    TgFREE_TEMP( psModes );

    if (nullptr != pnuiMode_ScanOut)
    {
        for (uiFormat = 0; uiFormat < TgARRAY_COUNT(KTgKN_GPU_EXT_FORMAT_RT_SCANOUT); ++uiFormat)
        {
            pnuiMode_ScanOut[uiFormat] = nuiModeFormat[uiFormat];
        };
    };
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Data and Exports                                                                                                                                                    */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_OS_GPU_Device_Change_Check ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgKN_OS_GPU_Device_Change_Check( HWND hWnd, STg2_KN_OS_Window_Configuration_PC psConfig )
{
    union { HWND hWnd; TgUINT_PTR uiPTR; } const sHWND = { .hWnd = hWnd };

    TgUINT_E32                          uiSwap;

    if (psConfig == nullptr)
        return;

    for (uiSwap = 0; uiSwap < KTgKN_GPU_MAX_SWAP_CONTEXT; ++uiSwap)
    {
        STg2_KN_GPU_CXT_SWAP_PC             psCXT_SWAP = g_asKN_GPU_CXT_SWAP + uiSwap;
        TgBOOL                              bUpdateSwapChain;
        TgBOOL                              bResizeSwapChain;

        if (g_sKN_GPU_CXT_HOST.m_atiCXT_SWAP[uiSwap].m_uiKI == KTgKN_GPU_CXT_SWAP_ID__INVALID.m_uiKI)
            continue;

        if (!tgKN_GPU_CXT_SWAP_ID_Is_Equal( &psCXT_SWAP->m_tiCXT_SWAP_S, g_sKN_GPU_CXT_HOST.m_atiCXT_SWAP[uiSwap] ))
            continue;

        if (psCXT_SWAP->m_uiOS_ID != sHWND.uiPTR)
            continue;

        tgKN_OS_GPU_CXT_SWAP_Update_Output( g_sKN_GPU_CXT_HOST.m_atiCXT_SWAP[uiSwap], sHWND.uiPTR, true );

        bUpdateSwapChain  = psCXT_SWAP->m_bHDR_Request && psCXT_SWAP->m_bHDR_Supported && !psCXT_SWAP->m_bHDR_Enabled;
        bUpdateSwapChain |= psCXT_SWAP->m_bHDR_Request && !psCXT_SWAP->m_bHDR_Supported && psCXT_SWAP->m_bHDR_Enabled;

        bResizeSwapChain  = psConfig->m_uiRender_Target_W !=  psCXT_SWAP->m_sMode.m_sBuffer.m_uiWidth;
        bResizeSwapChain |= psConfig->m_uiRender_Target_H !=  psCXT_SWAP->m_sMode.m_sBuffer.m_uiHeight;

        if (!bUpdateSwapChain && !bResizeSwapChain)
            return;

        g_asKN_GPU_CXT_SWAP[uiSwap].m_sMode.m_sBuffer.m_uiWidth = psConfig->m_uiRender_Target_W;
        g_asKN_GPU_CXT_SWAP[uiSwap].m_sMode.m_sBuffer.m_uiHeight = psConfig->m_uiRender_Target_H;

        tgKN_GPU_EXT__SwapChain__Init( g_sKN_GPU_CXT_HOST.m_atiCXT_SWAP[uiSwap], bResizeSwapChain, false );

        break;
    };
}


/* ---- tgKN_OS_GPU_DXGI_Quick_Sort__DXGI_MODE_DESC ------------------------------------------------------------------------------------------------------------------------------ */
/* NOTE: Mode selection routines depend on this specific ordering of the modes.                                                                                                    */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgSINT_E32 CDECL tgKN_OS_GPU_DXGI_Quick_Sort__DXGI_MODE_DESC( TgVOID_CPC arg1, TgVOID_CPC arg2 ) TgATTRIBUTE_NO_EXCEPT
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


/* ---- tgKN_OS_GPU_DXGI_Enumerate_Adapters_And_Outputs -------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgKN_OS_GPU_DXGI_Enumerate_Adapters_And_Outputs( TgVOID )
{
    IDXGIAdapter4                       *psDXGI_Adapter;
    TgUINT_E32                          uiAdapter_Index;
    DXGI_ADAPTER_DESC3                  sDXGI_Adapter_Desc;

    if (nullptr == g_pDXGIFactory)
    {
        return;
    }

    /* Enumerate all adapters */
    uiAdapter_Index = 0;
    while (SUCCEEDED(IDXGIFactory7_EnumAdapters1(g_pDXGIFactory, uiAdapter_Index, (IDXGIAdapter1**)&psDXGI_Adapter)))
    {
        IDXGIOutput6                        *psDXGI_Output;
        TgUINT_E32                          uiOutput_Index;

        /* Get adapter description */
        if (FAILED(IDXGIAdapter4_GetDesc3(psDXGI_Adapter, &sDXGI_Adapter_Desc)))
        {
            IDXGIAdapter4_Release(psDXGI_Adapter);
            ++uiAdapter_Index;
            continue;
        }

        tgCN_PrintF(KTgCN_CHANEL_INITIALIZE | KTgCN_SEVERITY_9, 
                   u8"%-16.16s(%-48.48s): Adapter[%d]: %S\n", 
                   u8"Kernel", u8"tgKN_OS_GPU_DXGI_Enumerate", 
                   uiAdapter_Index, sDXGI_Adapter_Desc.Description);

        /* Enumerate all outputs for this adapter */
        uiOutput_Index = 0;
        while (SUCCEEDED(IDXGIAdapter4_EnumOutputs(psDXGI_Adapter, uiOutput_Index, (IDXGIOutput**)&psDXGI_Output)))
        {
            /* Get output description */ 
            if (SUCCEEDED(IDXGIOutput6_GetDesc1(psDXGI_Output, &g_asDXGI_Output[g_nuiDXGI_Output].m_sDXGI_Output_DESC)))
            {
                /* Enumerate all display modes for this output */

                tgKN_OS_GPU_DXGI_Enumerate_Output_Modes(
                    &g_asDXGI_Output[g_nuiDXGI_Output].m_psDXGI_Mode, &g_asDXGI_Output[g_nuiDXGI_Output].m_nuiDXGI_Mode, nullptr, psDXGI_Output);

                tgCN_PrintF(KTgCN_CHANEL_INITIALIZE | KTgCN_SEVERITY_9, 
                            u8"%-16.16s(%-48.48s):   Output[%d]: %S\n", 
                            u8"Kernel", u8"tgKN_OS_GPU_DXGI_Enumerate", 
                            uiOutput_Index, g_asDXGI_Output[g_nuiDXGI_Output].m_sDXGI_Output_DESC.DeviceName);

                ++g_nuiDXGI_Output;
                if (g_nuiDXGI_Output >= KTgKN_GPU_MAX_OUTPUT)
                    return;
            }

            IDXGIOutput6_Release(psDXGI_Output);
            ++uiOutput_Index;
        }

        IDXGIAdapter4_Release(psDXGI_Adapter);
        ++uiAdapter_Index;
    }
}


/* ---- tgKN_OS_GPU_DXGI_Free_Adapters_And_Outputs ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgKN_OS_GPU_DXGI_Free_Adapters_And_Outputs( TgVOID )
{
    TgRSIZE                             uiIndex;

    for (uiIndex = 0; uiIndex < TgARRAY_COUNT(g_asDXGI_Output); ++uiIndex)
    {
        if (nullptr == g_asDXGI_Output[uiIndex].m_psDXGI_Mode)
            continue;
        TgFREE_POOL( g_asDXGI_Output[uiIndex].m_psDXGI_Mode );
        tgMM_Set_U08_0x00( g_asDXGI_Output + uiIndex, sizeof( g_asDXGI_Output[0] ) );
    }
}


/* ---- tgKN_OS_GPU_CXT_SWAP_Init ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgKN_OS_GPU_CXT_SWAP_Init( TgRSIZE idxHOST_CXT_SWAP, TgCHAR_WC_CP wszDevice_Name )
{
    HRESULT                             hr = S_OK;
    UINT32                              NumPathArrayElements = 0;
    UINT32                              NumModeInfoArrayElements = 0;
    DISPLAYCONFIG_PATH_INFO*            PathInfoArray = nullptr;
    DISPLAYCONFIG_MODE_INFO*            ModeInfoArray = nullptr;

    TgPARAM_CHECK_INDEX( idxHOST_CXT_SWAP, g_asOS_EXT_Swap_Context_Output );
    TgPARAM_CHECK(s_pfnGetDisplayConfigBufferSizes);
    TgPARAM_CHECK(s_pfnDisplayConfigGetDeviceInfo);

    if (g_asOS_EXT_Swap_Context_Output[idxHOST_CXT_SWAP].m_bInit)
        return;

    /* Window OS enumeration of ... you know, did not bother really looking into it. It's a standard enumeration loop, where the linking element to the DXGI enumeration is the
       device name (in this case the output device name). The id values are assumed to remain consistent for the duration of the executable execution. */

    tgWSZ_Copy(g_asOS_EXT_Swap_Context_Output[idxHOST_CXT_SWAP].m_wszDevice_Name, sizeof( g_asOS_EXT_Swap_Context_Output[idxHOST_CXT_SWAP].m_wszDevice_Name ),
               wszDevice_Name, KTgMAX_RSIZE);

    do
    {
        hr = HRESULT_FROM_WIN32(s_pfnGetDisplayConfigBufferSizes(QDC_ONLY_ACTIVE_PATHS, &NumPathArrayElements, &NumModeInfoArrayElements));
        if (FAILED(hr))
        {
            break;
        }

        PathInfoArray = (DISPLAYCONFIG_PATH_INFO*)TgMALLOC_POOL( sizeof(DISPLAYCONFIG_PATH_INFO) * NumPathArrayElements );
        if (PathInfoArray == nullptr)
        {
            hr = E_OUTOFMEMORY;
            break;
        }
        tgMM_Set_U08_0x00( PathInfoArray, sizeof(DISPLAYCONFIG_PATH_INFO) * NumPathArrayElements );

        ModeInfoArray = (DISPLAYCONFIG_MODE_INFO*)TgMALLOC_POOL( sizeof(DISPLAYCONFIG_MODE_INFO) * NumModeInfoArrayElements );
        if (ModeInfoArray == nullptr)
        {
            TgFREE_POOL(PathInfoArray);
            PathInfoArray = nullptr;
            hr = E_OUTOFMEMORY;
            break;
        }
        tgMM_Set_U08_0x00( ModeInfoArray, sizeof(DISPLAYCONFIG_MODE_INFO) * NumModeInfoArrayElements );

        hr = HRESULT_FROM_WIN32(s_pfnQueryDisplayConfig(QDC_ONLY_ACTIVE_PATHS, &NumPathArrayElements, PathInfoArray, &NumModeInfoArrayElements, ModeInfoArray, nullptr));

        if (SUCCEEDED(hr))
        {
            // Loop through all sources until the one which matches the 'monitor' is found.
            for (INT PathIdx = 0; PathIdx < (INT)NumPathArrayElements; ++PathIdx)
            {
                DISPLAYCONFIG_SOURCE_DEVICE_NAME SourceName;

                tgMM_Set_U08_0x00( &SourceName, sizeof( SourceName ) );
                SourceName.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_SOURCE_NAME;
                SourceName.header.size = sizeof(SourceName);
                SourceName.header.adapterId = PathInfoArray[PathIdx].sourceInfo.adapterId;
                SourceName.header.id = PathInfoArray[PathIdx].sourceInfo.id;

                if (SUCCEEDED(HRESULT_FROM_WIN32(s_pfnDisplayConfigGetDeviceInfo(&SourceName.header))))
                {
                    if (wcscmp(g_asOS_EXT_Swap_Context_Output[idxHOST_CXT_SWAP].m_wszDevice_Name, SourceName.viewGdiDeviceName) == 0)
                    {
                        g_asOS_EXT_Swap_Context_Output[idxHOST_CXT_SWAP].m_sPath_Info = PathInfoArray[PathIdx];
                        g_asOS_EXT_Swap_Context_Output[idxHOST_CXT_SWAP].m_bInit = true;
                    }
                }
            }
        }

        TgFREE_POOL(PathInfoArray);
        PathInfoArray = nullptr;

        TgFREE_POOL(ModeInfoArray);
        ModeInfoArray = nullptr;

    } while (hr == HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER));
}


/* ---- tgKN_OS_GPU_CXT_SWAP_Free ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgKN_OS_GPU_CXT_SWAP_Free( TgRSIZE idxHOST_CXT_SWAP )
{
    TgPARAM_CHECK_INDEX( idxHOST_CXT_SWAP, g_asOS_EXT_Swap_Context_Output );
    tgMM_Set_U08_0x00( g_asOS_EXT_Swap_Context_Output + idxHOST_CXT_SWAP, sizeof( g_asOS_EXT_Swap_Context_Output[0] ) );
}


/* ---- tgKN_GPU_EXT_STAT_Print_Physical_Devices --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if TgCOMPILE__CONSOLE && (TgS_STAT__KERNEL || TgS_DEBUG__KERNEL)
static TgVOID tgKN_GPU_EXT_STAT_Print_Physical_Devices(
    TgATTRIBUTE_UNUSED TgUINT_E32_C nuiArg, TgATTRIBUTE_UNUSED TgCHAR_U8_CP pArgV[KTgMAX_CMD_LINE_COUNT] ) TgATTRIBUTE_NO_EXCEPT
{
    // tgSTAT_KN_GPU_EXT_Physical_Device_Output();
}
/*# TgCOMPILE__CONSOLE && (TgS_STAT__KERNEL || TgS_DEBUG__KERNEL) */
#endif


/* =============================================================================================================================================================================== */
/*# defined(TgBUILD_FEATURE__GRAPHICS) */
#endif
