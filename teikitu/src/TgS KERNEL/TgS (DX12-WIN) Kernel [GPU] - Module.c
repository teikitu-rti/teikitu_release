/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (WIN-DX12) Kernel - Module [GPU].c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */

#include "TgS COMMON/TgS (WIN) Common - Global.h"
#include "TgS KERNEL/TgS (WIN) Kernel - Type.h"

#include "TgS (WIN) Kernel - Internal - Type.h"
#include "TgS (WIN) Kernel - Internal - Data.h"

#define NOTEXTMETRIC
#include <wingdi.h>
#include <winuser.h>


/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Data and Exports                                                                                                                                                    */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* Agility SDK exports to configure the D3D loading path. */
TgEXTN DLL_EXPORT const UINT                D3D12SDKVersion;
       DLL_EXPORT const UINT                D3D12SDKVersion = 606;
TgEXTN DLL_EXPORT const TgCHAR_U8 *         D3D12SDKPath;
       DLL_EXPORT const TgCHAR_U8 *         D3D12SDKPath = u8".\\D3D12\\";

static  TgVOID
tgKN_GPU_EXT_Device_Change_Check(
    HWND hWnd, STg2_KN_OS_Window_Configuration_PC psConfig );

static  TgVOID 
tgKN_GPU_EXT_Query_Monitor_Min_Resolution(
    TgUINT_F32_P puiW, TgUINT_F32_P puiH, HMONITOR hMonitor );

static  TgVOID 
tgKN_GPU_EXT_Query_Monitor_Max_Resolution(
    TgUINT_F32_P puiW, TgUINT_F32_P puiH, HMONITOR hMonitor );

static  TgVOID 
tgKN_GPU_EXT_Query_Swap_Context_Mode_Width_and_Height(
    TgUINT_F32_P puiW, TgUINT_F32_P puiH, HWND hWnd, HMONITOR hMonitor );

static  TgVOID 
tgKN_GPU_EXT_Query_Closest_Output_Mode_Width_and_Height_Rounded_Down(
    TgUINT_F32_P puiW, TgUINT_F32_P puiH, HWND hWnd, HMONITOR hMonitor );

static HINSTANCE                            s_hDLL_DXGI = nullptr;
static HINSTANCE                            s_hDLL_DXGI_DEBUG = nullptr;
static HINSTANCE                            s_hDLL_D3D12 = nullptr;
static HINSTANCE                            s_hDLL_PIX_Event = nullptr;
static HINSTANCE                            s_hDLL_PIX_Capturer = nullptr;
static HINSTANCE                            s_hext_ms_win_ntuser_sysparams_ext_l1_1_1 = nullptr;

static TgUINT_E32                           s_uiCreateFlag = 0;

static ULONG                                (__stdcall *s_pfnGetDisplayConfigBufferSizes)( UINT32, UINT32*, UINT32* );
static ULONG                                (__stdcall *s_pfnQueryDisplayConfig)( UINT32, UINT32*, DISPLAYCONFIG_PATH_INFO*, UINT32*, DISPLAYCONFIG_MODE_INFO*, DISPLAYCONFIG_TOPOLOGY_ID* );
static ULONG                                (__stdcall *s_pfnDisplayConfigGetDeviceInfo)( DISPLAYCONFIG_DEVICE_INFO_HEADER* );

static struct
{
    TgCHAR_WC_CP                                m_wszDevice_Name;
    DISPLAYCONFIG_PATH_INFO                     m_sPath_Info;
    TgUINT_E64                                  m_bInit;
}                                           s_asOS_EXT_Output[KTgKN_GPU_MAX_SWAP_CONTEXT];

TgCOMPILER_ASSERT( (TgSINT_E32)KTgKN_MAX_WINDOWS == (TgSINT_E32)KTgKN_GPU_MAX_SWAP_CONTEXT, 0 );



/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_OS_GPU_API_Module_Init ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_OS_GPU_API_Module_Init( TgVOID )
{
    s_hDLL_DXGI = nullptr;
    s_hDLL_DXGI_DEBUG = nullptr;
    s_hDLL_D3D12 = nullptr;
    s_hDLL_PIX_Event = nullptr;
    s_hDLL_PIX_Capturer = nullptr;
    s_hext_ms_win_ntuser_sysparams_ext_l1_1_1 = nullptr;

    tgMM_Set_U08_0x00( &s_asOS_EXT_Output, sizeof( s_asOS_EXT_Output ) );

    /* Load the necessary functions from the WinPixEventRuntime DLL. */
    //if (!tgGB_Load_Lib( &s_hDLL_PIX_Capturer, TgOS_TEXT("WinPixGpuCapturer.dll") ))
    //{
    //    TgCRITICAL_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to load WinPixGpuCapturer DLL." );
    //    goto tgKN_OS_GPU_API_Module_Init_FAIL;
    //};

    /* Loads the necessary functions from DXGI */
    if (!tgGB_Load_Lib( &s_hDLL_DXGI, TgOS_TEXT("dxgi.dll") ))
    {
        TgCRITICAL_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to load DXGI DLL." );
        goto tgKN_OS_GPU_API_Module_Init_FAIL;
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
        goto tgKN_OS_GPU_API_Module_Init_FAIL;
    };

    /* Load the necessary functions from the D3D12 DLL. */
    if (!tgGB_Load_Lib( &s_hDLL_D3D12, TgOS_TEXT("d3d12.dll") ))
    {
        TgCRITICAL_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to load D312 DLL." );
        goto tgKN_OS_GPU_API_Module_Init_FAIL;
    };

    /* Load the needed functions from the DLL */
    if (
           !tgGB_Get_Func_Address( (FARPROC*)&g_pfnD3D12SerializeVersionedRootSignature, s_hDLL_D3D12, "D3D12SerializeVersionedRootSignature" )
        || !tgGB_Get_Func_Address( (FARPROC*)&g_pfnD3D12CreateVersionedRootSignatureDeserializer, s_hDLL_D3D12, "D3D12CreateVersionedRootSignatureDeserializer" )
        || !tgGB_Get_Func_Address( (FARPROC*)&g_pfnD3D12CreateDevice, s_hDLL_D3D12, "D3D12CreateDevice" )
        || !tgGB_Get_Func_Address( (FARPROC*)&g_pfnD3D12GetDebugInterface, s_hDLL_D3D12, "D3D12GetDebugInterface" )
    )
    {
        TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to find function in D3D12 DLL." );
        goto tgKN_OS_GPU_API_Module_Init_FAIL;
    };

    /* Load the necessary functions from the WinPixEventRuntime DLL. */
    if (!tgGB_Load_Lib( &s_hDLL_PIX_Event, TgOS_TEXT("WinPixEventRuntime.dll") ))
    {
        TgCRITICAL_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to load WinPixEventRuntime DLL." );
        goto tgKN_OS_GPU_API_Module_Init_FAIL;
    };

    /* Load the needed functions from the DLL */
    if (
           !tgGB_Get_Func_Address( (FARPROC*)&g_pfnPIXBeginEventOnCommandList, s_hDLL_PIX_Event, "PIXBeginEventOnCommandList" )
        || !tgGB_Get_Func_Address( (FARPROC*)&g_pfnPIXEndEventOnCommandList, s_hDLL_PIX_Event, "PIXEndEventOnCommandList" )
        || !tgGB_Get_Func_Address( (FARPROC*)&g_pfnPIXSetMarkerOnCommandList, s_hDLL_PIX_Event, "PIXSetMarkerOnCommandList" )
    )
    {
        TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to find function in D3D12 DLL." );
        goto tgKN_OS_GPU_API_Module_Init_FAIL;
    };

    if (!tgGB_Load_Lib( &s_hext_ms_win_ntuser_sysparams_ext_l1_1_1, TgOS_TEXT("ext-ms-win-ntuser-sysparams-ext-l1-1-1.dll") ))
    {
        TgCRITICAL_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to load ext-ms-win-ntuser-sysparams-ext-l1-1-1 DLL." );
        goto tgKN_OS_GPU_API_Module_Init_FAIL;
    };

    if (
           !tgGB_Get_Func_Address( (FARPROC *)&s_pfnGetDisplayConfigBufferSizes, s_hext_ms_win_ntuser_sysparams_ext_l1_1_1, ("GetDisplayConfigBufferSizes") )
        || !tgGB_Get_Func_Address( (FARPROC *)&s_pfnQueryDisplayConfig, s_hext_ms_win_ntuser_sysparams_ext_l1_1_1, ("QueryDisplayConfig") )
        || !tgGB_Get_Func_Address( (FARPROC *)&s_pfnDisplayConfigGetDeviceInfo, s_hext_ms_win_ntuser_sysparams_ext_l1_1_1, ("DisplayConfigGetDeviceInfo") )
        )
    {
        TgCRITICAL_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to find function in ext-ms-win-ntuser-sysparams-ext-l1-1-1 DLL" );
        goto tgKN_OS_GPU_API_Module_Init_FAIL;
    };

    g_pfnDevice_Change_Check = tgKN_GPU_EXT_Device_Change_Check;
    g_pfnQuery_Monitor_Min_Resolution = tgKN_GPU_EXT_Query_Monitor_Min_Resolution;
    g_pfnQuery_Monitor_Max_Resolution = tgKN_GPU_EXT_Query_Monitor_Max_Resolution;
    g_pfnQuery_Swap_Context_Mode_Width_and_Height = tgKN_GPU_EXT_Query_Swap_Context_Mode_Width_and_Height;
    g_pfnQuery_Swap_Context_Closest_Mode_Rounded_Down = tgKN_GPU_EXT_Query_Closest_Output_Mode_Width_and_Height_Rounded_Down;

    return (KTgS_OK);

tgKN_OS_GPU_API_Module_Init_FAIL:
    tgKN_OS_GPU_API_Module_Free();
    return (KTgE_FAIL);
}




/* ---- tgKN_OS_GPU_API_Module_Boot ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_OS_GPU_API_Module_Boot( TgVOID )
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

#if defined(TgBUILD_ENABLE_D3D_DEBUG) && TgBUILD_ENABLE_D3D_DEBUG
    {
        ID3D12Debug                         *psDX12_Debug;

        if (SUCCEEDED(g_pfnD3D12GetDebugInterface( MS_REF IID_ID3D12Debug, (TgVOID_PP)&psDX12_Debug )))
        {
            ID3D12Debug1                        *psDX12_Debug_1;

            ID3D12Debug_EnableDebugLayer( psDX12_Debug );

            if (SUCCEEDED(ID3D12Debug_QueryInterface( psDX12_Debug, MS_REF IID_ID3D12Debug1, (TgVOID_PP)&psDX12_Debug_1 )))
            {
            #if defined(TgBUILD_ENABLE_D3D_DEBUG_WITH_GPU_VALIDATION) && TgBUILD_ENABLE_D3D_DEBUG_WITH_GPU_VALIDATION
                ID3D12Debug1_SetEnableGPUBasedValidation( psDX12_Debug_1, true );
            #endif
                ID3D12Debug1_Release( psDX12_Debug_1 );
            }
            ID3D12Debug_Release( psDX12_Debug );
        };
    }
/*# defined(TgBUILD_ENABLE_D3D_DEBUG) && TgBUILD_ENABLE_D3D_DEBUG */
#endif

    /* Creating the DXGI Factory is a side effect of this function. */
    tgKN_OS_GPU_EXT_Update_Swap_Output( KTgKN_GPU_CXT_SWAP_ID__INVALID, 0, false );

    return (KTgS_OK);
}


/* ---- tgKN_OS_GPU_API_Module_Stop ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_OS_GPU_API_Module_Stop( TgVOID )
{
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


/* ---- tgKN_OS_GPU_API_Module_Free ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_OS_GPU_API_Module_Free( TgVOID )
{
    g_pfnPIXSetMarkerOnCommandList = nullptr;
    g_pfnPIXEndEventOnCommandList = nullptr;
    g_pfnPIXBeginEventOnCommandList = nullptr;
    g_pfnD3D12GetDebugInterface = nullptr;
    g_pfnD3D12CreateDevice = nullptr;
    g_pfnD3D12CreateVersionedRootSignatureDeserializer = nullptr;
    g_pfnD3D12SerializeVersionedRootSignature = nullptr;
    g_pfnDXGIGetDebugInterface1 = nullptr;
    g_pfnDXGICreateDXGIFactory = nullptr;

    s_pfnGetDisplayConfigBufferSizes = nullptr;
    s_pfnQueryDisplayConfig = nullptr;
    s_pfnDisplayConfigGetDeviceInfo = nullptr;

    tgGB_Free_Lib( &s_hext_ms_win_ntuser_sysparams_ext_l1_1_1 );
    tgGB_Free_Lib( &s_hDLL_PIX_Capturer );
    tgGB_Free_Lib( &s_hDLL_PIX_Event );
    tgGB_Free_Lib( &s_hDLL_DXGI );
    tgGB_Free_Lib( &s_hDLL_DXGI_DEBUG );
    tgGB_Free_Lib( &s_hDLL_D3D12 );

    s_hext_ms_win_ntuser_sysparams_ext_l1_1_1 = nullptr;
    s_hDLL_PIX_Capturer = nullptr;
    s_hDLL_PIX_Event = nullptr;
    s_hDLL_DXGI = nullptr;
    s_hDLL_DXGI_DEBUG = nullptr;
    s_hDLL_D3D12 = nullptr;
}


/* ---- tgKN_OS_GPU_EXT_Update_Swap_Output --------------------------------------------------------------------------------------------------------------------------------------- */
/* Pre-Condition: Enumeration is complete.                                                                                                                                         */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_OS_GPU_EXT_Update_Swap_Output( TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP, TgUINT_PTR_C uiOS_ID, TgBOOL_C bValidateOutputDevice )
{
    STg2_KN_GPU_CXT_SWAP_PC             psCXT_SWAP = g_asKN_GPU_CXT_SWAP + tiCXT_SWAP.m_uiI;

    union { HWND hWnd; TgUINT_PTR uiPTR; } const sHWND = { .uiPTR = uiOS_ID };

    IDXGIFactory                        *psDXGI_Factory_0;
    STg2_KN_GPU_EXT_Output_P            psEXT_Output;

    TgPARAM_CHECK(s_pfnDisplayConfigGetDeviceInfo);

    /* The DXGI factory has to be recreated if it is null, or if there has been a sufficient change in the graphics layer (e.g. change in OS HDR settings). */
    /* MSFT recommends checking every frame. */

    if (!g_pDXGIFactory || !IDXGIFactory7_IsCurrent( g_pDXGIFactory ))
    {
        g_pfnDXGICreateDXGIFactory( s_uiCreateFlag, MS_REF IID_IDXGIFactory, (TgVOID_PP)&psDXGI_Factory_0 );
        if (nullptr == psDXGI_Factory_0)
        {
            return;
        };

        if (FAILED(IDXGIFactory_QueryInterface( psDXGI_Factory_0, MS_REF(IID_IDXGIFactory7), (TgVOID_PP)&g_pDXGIFactory )))
        {
            TgVERIFY(0 == IDXGIFactory_Release( psDXGI_Factory_0 ));
            psDXGI_Factory_0 = nullptr;
            return;
        };
        TgVERIFY( 1 == IDXGIFactory_Release( psDXGI_Factory_0 ) );
    }

    if (0 == sHWND.uiPTR)
    {
        return;
    };


    if (bValidateOutputDevice)
    {
        RECT                                rcWindow;
        TgRECT2D_F32_04                     sWindow;
        TgUINT_E32                          uiAdapter;
        TgUINT_E32                          uiOutput;
        TgFLOAT32                           fBest_Intersect_Area;
        TgRSIZE                             uiBest_Adapter;
        TgRSIZE                             uiBest_Output;

        /* Get the bounds of the attached window. */

        g_pfnGetWindowRect( sHWND.hWnd, &rcWindow );

        sWindow.m_uRect.m_vS_F32_04_1.x = (TgFLOAT32)rcWindow.left;
        sWindow.m_uRect.m_vS_F32_04_1.y = (TgFLOAT32)rcWindow.top;
        sWindow.m_uRect.m_vS_F32_04_1.z = (TgFLOAT32)rcWindow.right;
        sWindow.m_uRect.m_vS_F32_04_1.w = (TgFLOAT32)rcWindow.bottom;


        /* Search for the output device that has the greatest coverage of the render area. */

        fBest_Intersect_Area = 0.0F;
        uiBest_Adapter = KTgMAX_UMAX;
        uiBest_Output = KTgMAX_UMAX;

        for (uiAdapter = 0; uiAdapter < KTgKN_GPU_MAX_ADAPTER; ++uiAdapter)
        {
            if (nullptr == g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Adapter[uiAdapter].m_psDXGI_Adapter)
                continue;

            for (uiOutput = 0; uiOutput < g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Adapter[uiAdapter].m_nuiEXT_Output; ++uiOutput)
            {
                TgRECT2D_F32_04                     sOutput;
                TgFLOAT32                           fIntersect_Area;

                psEXT_Output = g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Adapter[uiAdapter].m_asEXT_Output + uiOutput;
                IDXGIOutput6_GetDesc1( psEXT_Output->m_psDXGI_Output, &psEXT_Output->m_sDXGI_Output );

                psEXT_Output->m_bHDR_Supported = psEXT_Output->m_sDXGI_Output.ColorSpace == DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020;

                sOutput.m_uRect.m_vS_F32_04_1.x = (TgFLOAT32)psEXT_Output->m_sDXGI_Output.DesktopCoordinates.left;
                sOutput.m_uRect.m_vS_F32_04_1.y = (TgFLOAT32)psEXT_Output->m_sDXGI_Output.DesktopCoordinates.top;
                sOutput.m_uRect.m_vS_F32_04_1.z = (TgFLOAT32)psEXT_Output->m_sDXGI_Output.DesktopCoordinates.right;
                sOutput.m_uRect.m_vS_F32_04_1.w = (TgFLOAT32)psEXT_Output->m_sDXGI_Output.DesktopCoordinates.bottom;

                fIntersect_Area = tgGM_Intersection_Area_RT2D_F32_04( &sWindow, &sOutput );
                if (fIntersect_Area > fBest_Intersect_Area)
                {
                    uiBest_Adapter = uiAdapter;
                    uiBest_Output = uiOutput;
                    fBest_Intersect_Area = fIntersect_Area;
                };
            };
        };

        if (KTgMAX_UMAX == uiBest_Adapter || KTgMAX_UMAX == uiBest_Output)
        {
            /* If we have not found a best fit output device - the window could be off-screen (i.e. it is not an invalid state). However, since there is nothing to see, the
               remaining parts of this function are not required. */
            return;
        };

        if (psCXT_SWAP->m_uiScanout_Adapter_Enumeration_Index == uiBest_Adapter && psCXT_SWAP->m_uiScanout_Output_Enumeration_Index == uiBest_Output)
        {
            /* If we have not found a best fit output device - the window could be off-screen (i.e. it is not an invalid state). However, since there is nothing to see, the
               remaining parts of this function are not required. */
            return;
        };

        /* Now that we have found a best fit output device - record the characteristics of the device. */

        psEXT_Output = g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Adapter[uiBest_Adapter].m_asEXT_Output + uiBest_Output;

        psCXT_SWAP->m_uiScanout_Adapter_Enumeration_Index = (TgUINT_E32)uiBest_Adapter;
        psCXT_SWAP->m_uiScanout_Output_Enumeration_Index = (TgUINT_E32)uiBest_Output;
        psCXT_SWAP->m_bHDR_Supported = psEXT_Output->m_bHDR_Supported;
        psCXT_SWAP->m_uiBits_Per_Colour = psEXT_Output->m_sDXGI_Output.BitsPerColor;
        psCXT_SWAP->m_fRed_Primary[0] = psEXT_Output->m_sDXGI_Output.RedPrimary[0];
        psCXT_SWAP->m_fRed_Primary[1] = psEXT_Output->m_sDXGI_Output.RedPrimary[1];
        psCXT_SWAP->m_fGreen_Primary[0] = psEXT_Output->m_sDXGI_Output.GreenPrimary[0];
        psCXT_SWAP->m_fGreen_Primary[1] = psEXT_Output->m_sDXGI_Output.GreenPrimary[1];
        psCXT_SWAP->m_fBlue_Primary[0] = psEXT_Output->m_sDXGI_Output.BluePrimary[0];
        psCXT_SWAP->m_fBlue_Primary[1] = psEXT_Output->m_sDXGI_Output.BluePrimary[1];
        psCXT_SWAP->m_fWhite_Point[0] = psEXT_Output->m_sDXGI_Output.WhitePoint[0];
        psCXT_SWAP->m_fWhite_Point[1] = psEXT_Output->m_sDXGI_Output.WhitePoint[1];
        psCXT_SWAP->m_fMin_Luminance = psEXT_Output->m_sDXGI_Output.MinLuminance;
        psCXT_SWAP->m_fMax_Luminance = psEXT_Output->m_sDXGI_Output.MaxLuminance;
        psCXT_SWAP->m_fMax_Full_Frame_Luminance = psEXT_Output->m_sDXGI_Output.MaxFullFrameLuminance;

        switch (psEXT_Output->m_sDXGI_Output.ColorSpace) {
        case DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P709:
            psCXT_SWAP->m_enColour_Space = ETgKN_GPU_HLSL_COLOR_SPACE_G22_NONE_P709;
            break;
        case DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020:
            psCXT_SWAP->m_enColour_Space = ETgKN_GPU_HLSL_COLOR_SPACE_G2084_NONE_P2020;
            break;
        case DXGI_COLOR_SPACE_RGB_FULL_G10_NONE_P709:
            psCXT_SWAP->m_enColour_Space = ETgKN_GPU_HLSL_COLOR_SPACE_G10_NONE_P709;
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
            psCXT_SWAP->m_enColour_Space = ETgKN_GPU_HLSL_COLOR_SPACE_UNKNOWN;
            break;
        };

        s_asOS_EXT_Output[tiCXT_SWAP.m_uiI].m_bInit = false;
    }
    else
    {
        psEXT_Output = g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Adapter[psCXT_SWAP->m_uiScanout_Adapter_Enumeration_Index].m_asEXT_Output
                     + psCXT_SWAP->m_uiScanout_Output_Enumeration_Index;
    }

    /* Query the windows OS for current graphics related settings. */

    if (!s_asOS_EXT_Output[tiCXT_SWAP.m_uiI].m_bInit)
    {
        tgKN_OS_GPU_EXT_Output__Init( tiCXT_SWAP.m_uiI, psEXT_Output );
    }

    if (s_asOS_EXT_Output[tiCXT_SWAP.m_uiI].m_bInit)
    {
        DISPLAYCONFIG_SDR_WHITE_LEVEL       sDevice_Info;

        tgMM_Set_U08_0x00( &sDevice_Info, sizeof( sDevice_Info ) );

        sDevice_Info.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_SDR_WHITE_LEVEL;
        sDevice_Info.header.size = sizeof( DISPLAYCONFIG_SDR_WHITE_LEVEL  );
        sDevice_Info.header.adapterId = s_asOS_EXT_Output[tiCXT_SWAP.m_uiI].m_sPath_Info.targetInfo.adapterId;
        sDevice_Info.header.id = s_asOS_EXT_Output[tiCXT_SWAP.m_uiI].m_sPath_Info.targetInfo.id;

        s_pfnDisplayConfigGetDeviceInfo( &sDevice_Info.header );

        psCXT_SWAP->m_fSDR_In_HDR_Nits_Level = ((TgFLOAT32)sDevice_Info.SDRWhiteLevel / 1000.0F) * 80.0F;
    }
}


/* ---- tgKN_OS_GPU_EXT_Output__Init -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_OS_GPU_EXT_Output__Init( TgRSIZE uiOS_EXT_Output, STg2_KN_GPU_EXT_Output_CPCU psEXT_Output )
{
    HRESULT                             hr = S_OK;
    UINT32                              NumPathArrayElements = 0;
    UINT32                              NumModeInfoArrayElements = 0;
    DISPLAYCONFIG_PATH_INFO*            PathInfoArray = nullptr;
    DISPLAYCONFIG_MODE_INFO*            ModeInfoArray = nullptr;

    TgPARAM_CHECK_INDEX( uiOS_EXT_Output, s_asOS_EXT_Output );
    TgPARAM_CHECK(s_pfnGetDisplayConfigBufferSizes);
    TgPARAM_CHECK(s_pfnDisplayConfigGetDeviceInfo);

    if (s_asOS_EXT_Output[uiOS_EXT_Output].m_bInit)
        return;

    /* Window OS enumeration of ... you know, did not bother really looking into it. It's a standard enumeration loop, where the linking element to the DXGI enumeration is the
       device name (in this case the output device name). The id values are assumed to remain consistent for the duration of the executable execution. */

    s_asOS_EXT_Output[uiOS_EXT_Output].m_wszDevice_Name = psEXT_Output->m_sDXGI_Output.DeviceName;

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
                    if (wcscmp(s_asOS_EXT_Output[uiOS_EXT_Output].m_wszDevice_Name, SourceName.viewGdiDeviceName) == 0)
                    {
                        s_asOS_EXT_Output[uiOS_EXT_Output].m_sPath_Info = PathInfoArray[PathIdx];
                        s_asOS_EXT_Output[uiOS_EXT_Output].m_bInit = true;
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


/* ---- tgKN_OS_GPU_EXT_Output__Free -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_OS_GPU_EXT_Output__Free( TgRSIZE uiOS_EXT_Output )
{
    TgPARAM_CHECK_INDEX( uiOS_EXT_Output, s_asOS_EXT_Output );
    tgMM_Set_U08_0x00( s_asOS_EXT_Output+ uiOS_EXT_Output, sizeof( s_asOS_EXT_Output[0] ) );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Data and Exports                                                                                                                                                    */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_GPU_EXT_Device_Change_Check ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgKN_GPU_EXT_Device_Change_Check( HWND hWnd, STg2_KN_OS_Window_Configuration_PC psConfig )
{
    union { HWND hWnd; TgUINT_PTR uiPTR; } const sHWND = { .hWnd = hWnd };

    TgUINT_E32                          uiSwap;

    if (psConfig == nullptr)
        return;

    for (uiSwap = 0; uiSwap < KTgKN_GPU_MAX_SWAP_CONTEXT; ++uiSwap)
    {
        STg2_KN_GPU_CXT_SWAP_P              psCXT_SWAP = g_asKN_GPU_CXT_SWAP + uiSwap;
        TgBOOL                              bUpdateSwapChain;
        TgBOOL                              bResizeSwapChain;

        if (g_sKN_GPU_CXT_HOST.m_atiCXT_SWAP[uiSwap].m_uiKI == KTgKN_GPU_CXT_SWAP_ID__INVALID.m_uiKI)
            continue;

        if (!tgKN_GPU_CXT_SWAP_ID_Is_Equal( &psCXT_SWAP->m_tiCXT_SWAP_S, g_sKN_GPU_CXT_HOST.m_atiCXT_SWAP[uiSwap] ))
            continue;

        if (psCXT_SWAP->m_uiOS_ID != sHWND.uiPTR)
            continue;

        tgKN_OS_GPU_EXT_Update_Swap_Output( g_sKN_GPU_CXT_HOST.m_atiCXT_SWAP[uiSwap], sHWND.uiPTR, true );

        bUpdateSwapChain  = psCXT_SWAP->m_bHDR_Request && psCXT_SWAP->m_bHDR_Supported && !psCXT_SWAP->m_bHDR_Enabled;
        bUpdateSwapChain |= psCXT_SWAP->m_bHDR_Request && !psCXT_SWAP->m_bHDR_Supported && psCXT_SWAP->m_bHDR_Enabled;

        bResizeSwapChain  = psConfig->m_uiRender_Target_W !=  psCXT_SWAP->m_sMode.m_sBuffer.m_uiWidth;
        bResizeSwapChain |= psConfig->m_uiRender_Target_H !=  psCXT_SWAP->m_sMode.m_sBuffer.m_uiHeight;

        if (!bUpdateSwapChain && !bResizeSwapChain)
            return;

        g_asKN_GPU_CXT_SWAP[uiSwap].m_sMode.m_sBuffer.m_uiWidth = psConfig->m_uiRender_Target_W;
        g_asKN_GPU_CXT_SWAP[uiSwap].m_sMode.m_sBuffer.m_uiHeight = psConfig->m_uiRender_Target_H;
        g_asKN_GPU_EXT_CXT_SWAP[uiSwap].m_sDXGI_Mode.Width = psConfig->m_uiRender_Target_W;
        g_asKN_GPU_EXT_CXT_SWAP[uiSwap].m_sDXGI_Mode.Height = psConfig->m_uiRender_Target_H;

        tgPM_MT_MX_Wait_Block( &g_asKN_GPU_EXT_CXT_SWAP[uiSwap].m_sSwap_And_View_Lock );
        tgKN_GPU_EXT__SwapChain__Init( g_sKN_GPU_CXT_HOST.m_atiCXT_SWAP[uiSwap], bResizeSwapChain );
        tgPM_MT_MX_Release( &g_asKN_GPU_EXT_CXT_SWAP[uiSwap].m_sSwap_And_View_Lock );

        break;
    };
}


/* ---- tgKN_GPU_EXT_Query_Monitor_Min_Resolution -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgKN_GPU_EXT_Query_Monitor_Min_Resolution( TgUINT_F32_P puiW, TgUINT_F32_P puiH, HMONITOR hMonitor )
{
    TgRSIZE                             uiAdapter, uiOutput;
    DXGI_MODE_DESC1_P                   psDXGI_Mode;

    if (hMonitor == nullptr || nullptr == puiW || nullptr == puiH)
        return;

    for (uiAdapter = 0; uiAdapter < KTgKN_GPU_MAX_ADAPTER; ++uiAdapter)
    {
        if (0 == g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Adapter[uiAdapter].m_nuiEXT_Output)
        {
            *puiW = 640;
            *puiH = 480;
        }
        for (uiOutput = 0; uiOutput < KTgKN_GPU_MAX_OUTPUT; ++uiOutput)
        {
            if (hMonitor != g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Adapter[uiAdapter].m_asEXT_Output[uiOutput].m_sDXGI_Output.Monitor)
                continue;
            psDXGI_Mode = g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Adapter[uiAdapter].m_asEXT_Output[uiOutput].m_psDXGI_Mode;
            *puiW = psDXGI_Mode[0].Width;
            *puiH = psDXGI_Mode[0].Height;
            return;
        };
    };
}


/* ---- tgKN_GPU_EXT_Query_Monitor_Max_Resolution -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgKN_GPU_EXT_Query_Monitor_Max_Resolution( TgUINT_F32_P puiW, TgUINT_F32_P puiH, HMONITOR hMonitor )
{
    TgRSIZE                             uiAdapter, uiOutput;
    DXGI_MODE_DESC1_P                   psDXGI_Mode;

    if (hMonitor == nullptr || nullptr == puiW || nullptr == puiH)
        return;

    for (uiAdapter = 0; uiAdapter < KTgKN_GPU_MAX_ADAPTER; ++uiAdapter)
    {
        if (0 == g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Adapter[uiAdapter].m_nuiEXT_Output)
        {
            *puiW = 640;
            *puiH = 480;
        }
        for (uiOutput = 0; uiOutput < KTgKN_GPU_MAX_OUTPUT; ++uiOutput)
        {
            if (hMonitor != g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Adapter[uiAdapter].m_asEXT_Output[uiOutput].m_sDXGI_Output.Monitor)
                continue;
            psDXGI_Mode = g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Adapter[uiAdapter].m_asEXT_Output[uiOutput].m_psDXGI_Mode;
            *puiW = psDXGI_Mode[g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Adapter[uiAdapter].m_asEXT_Output[uiOutput].m_nuiDXGI_Mode - 1].Width;
            *puiH = psDXGI_Mode[g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Adapter[uiAdapter].m_asEXT_Output[uiOutput].m_nuiDXGI_Mode - 1].Height;
            return;
        };
    };
}


/* ---- tgKN_GPU_EXT_Query_Swap_Context_Mode_Width_and_Height -------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgKN_GPU_EXT_Query_Swap_Context_Mode_Width_and_Height( TgUINT_F32_P puiW, TgUINT_F32_P puiH, HWND hWnd, HMONITOR hMonitor )
{
    TgUINT_E32                          uiAdapter, uiOutput, uiSwap;
    union
    {
        HWND                                hWnd;
        TgUINT_PTR                          uiPTR;
    }                                   sHWND;
    STg2_KN_GPU_CXT_SWAP_P              psCXT_SWAP;

    if (hWnd == nullptr || hMonitor == nullptr || nullptr == puiW || nullptr == puiH)
        return;

    sHWND.hWnd = hWnd;
    for (uiAdapter = 0; uiAdapter < KTgKN_GPU_MAX_ADAPTER; ++uiAdapter)
    {
        for (uiOutput = 0; uiOutput < KTgKN_GPU_MAX_OUTPUT; ++uiOutput)
        {
            if (hMonitor != g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Adapter[uiAdapter].m_asEXT_Output[uiOutput].m_sDXGI_Output.Monitor)
                continue;
            for (uiSwap = 0; uiSwap < KTgKN_GPU_MAX_SWAP_CONTEXT; ++uiSwap)
            {
                if (g_sKN_GPU_CXT_HOST.m_atiCXT_SWAP[uiSwap].m_uiKI == KTgKN_GPU_CXT_SWAP_ID__INVALID.m_uiKI)
                    continue;
                psCXT_SWAP = g_asKN_GPU_CXT_SWAP + uiSwap;
                if (!tgKN_GPU_CXT_SWAP_ID_Is_Equal(&psCXT_SWAP->m_tiCXT_SWAP_S, g_sKN_GPU_CXT_HOST.m_atiCXT_SWAP[uiSwap]))
                    continue;
                *puiW =  psCXT_SWAP->m_sMode.m_sBuffer.m_uiWidth;
                *puiH =  psCXT_SWAP->m_sMode.m_sBuffer.m_uiHeight;
                return;
            };
        };
    };
}


/* ---- tgKN_GPU_EXT_Query_Closest_Output_Mode_Width_and_Height_Rounded_Down ----------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgKN_GPU_EXT_Query_Closest_Output_Mode_Width_and_Height_Rounded_Down( TgUINT_F32_P puiW, TgUINT_F32_P puiH, HWND hWnd, HMONITOR hMonitor )
{
    TgUINT_E32                          uiAdapter, uiOutput, uiSwap;
    STg2_KN_GPU_Mode                    sMode, sMode_Request;
    union
    {
        HWND                                hWnd;
        TgUINT_PTR                          uiPTR;
    }                                   sHWND;
    STg2_KN_GPU_CXT_SWAP_P              psCXT_SWAP;

    if (hWnd == nullptr || hMonitor == nullptr || nullptr == puiW || nullptr == puiH)
        return;

    sHWND.hWnd = hWnd;
    for (uiAdapter = 0; uiAdapter < KTgKN_GPU_MAX_ADAPTER; ++uiAdapter)
    {
        if (0 == g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Adapter[uiAdapter].m_nuiEXT_Output)
        {
            return;
        }
        for (uiOutput = 0; uiOutput < KTgKN_GPU_MAX_OUTPUT; ++uiOutput)
        {
            if (hMonitor != g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Adapter[uiAdapter].m_asEXT_Output[uiOutput].m_sDXGI_Output.Monitor)
                continue;
            for (uiSwap = 0; uiSwap < KTgKN_GPU_MAX_SWAP_CONTEXT; ++uiSwap)
            {
                if (g_sKN_GPU_CXT_HOST.m_atiCXT_SWAP[uiSwap].m_uiKI == KTgKN_GPU_CXT_SWAP_ID__INVALID.m_uiKI)
                    continue;
                psCXT_SWAP = g_asKN_GPU_CXT_SWAP + uiSwap;
                if (!tgKN_GPU_CXT_SWAP_ID_Is_Equal(&psCXT_SWAP->m_tiCXT_SWAP_S, g_sKN_GPU_CXT_HOST.m_atiCXT_SWAP[uiSwap]))
                    continue;
                sMode_Request = psCXT_SWAP->m_sMode;
                sMode_Request.m_sBuffer.m_uiWidth = *puiW;
                sMode_Request.m_sBuffer.m_uiHeight = *puiH;
                tgKN_GPU_Select_Min_Mode( &sMode, uiAdapter, uiOutput, &sMode_Request );
                *puiW =  sMode_Request.m_sBuffer.m_uiWidth;
                *puiH =  sMode_Request.m_sBuffer.m_uiHeight;
                return;
            };
        };
    };
}
