/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (WIN) Common - Global.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Data                                                                                                                                                                    */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

HINSTANCE                                   g_hInstance = nullptr;


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Data                                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* API Set: api-ms-win-core-synch-l1-2-0 */
TgVOID_P                                    (__stdcall *g_pfnCreateEventEx)( LPSECURITY_ATTRIBUTES, TgOSCHAR_CP, DWORD, DWORD ) = nullptr;
TgVOID_P                                    (__stdcall *g_pfnCreateEvent)( LPSECURITY_ATTRIBUTES, BOOL, BOOL, TgOSCHAR_CP ) = nullptr;
TgVOID_P                                    (__stdcall *g_pfnCreateSemaphoreEx)( LPSECURITY_ATTRIBUTES, LONG, LONG, TgOSCHAR_CP, DWORD, DWORD )=nullptr;
TgSINT_F32                                  (__stdcall *g_pfnReleaseSemaphore)( TgVOID_P, LONG, LPLONG ) = nullptr;
TgVOID_P                                    (__stdcall *g_pfnCreateMutexEx)( LPSECURITY_ATTRIBUTES, TgOSCHAR_CP, DWORD, DWORD ) = nullptr;
TgSINT_F32                                  (__stdcall *g_pfnReleaseMutex)( TgVOID_P ) = nullptr;
DWORD                                       (__stdcall *g_pfnWaitForSingleObjectEx)( TgVOID_P, DWORD, BOOL ) = nullptr;
TgVOID                                      (__stdcall *g_pfnSleep)( DWORD ) = nullptr;

/* API Set: api-ms-win-core-processthreads-l1-1-2 */
TgVOID_P                                    (__stdcall *g_pfnGetCurrentProcess)( TgVOID ) = nullptr;
DWORD                                       (__stdcall *g_pfnGetCurrentProcessId)( TgVOID ) = nullptr;
TgVOID_P                                    (__stdcall *g_pfnCreateThread)( LPSECURITY_ATTRIBUTES, TgRSIZE, LPTHREAD_START_ROUTINE, TgVOID_P, DWORD, LPDWORD ) = nullptr;
TgVOID_P                                    (__stdcall *g_pfnGetCurrentThread)( TgVOID ) = nullptr;
DWORD                                       (__stdcall *g_pfnGetCurrentThreadId)( TgVOID ) = nullptr;
TgVOID                                      (__stdcall *g_pfnExitThread)( DWORD ) = nullptr;
BOOL                                        (__stdcall *g_pfnSetThreadPriority)( TgVOID_P, TgSINT_F32  ) = nullptr;
TgSINT_F32                                  (__stdcall *g_pfnSwitchToThread)( TgVOID ) = nullptr;
TgSINT_F32                                  (__stdcall *g_pfnIsProcessorFeaturePresent)( DWORD ) = nullptr;

/* API Set: api-ms-win-core-handle-l1-1-0 */
TgSINT_F32                                  (__stdcall *g_pfnCloseHandle)( TgVOID_P ) = nullptr;
TgSINT_F32                                  (__stdcall *g_pfnDuplicateHandle )(TgVOID_P, TgVOID_P, TgVOID_P, TgVOID_PP, DWORD, BOOL, DWORD) = nullptr;

/* API Set: api-ms-win-core-debug-l1-1-1 */
TgVOID                                      (__stdcall *g_pfnOutputDebugString)( TgOSCHAR_CP ) = nullptr;
BOOL                                        (__stdcall *g_pfnIsDebuggerPresent)( TgVOID ) = nullptr;

/* API Set: api-ms-win-core-sysinfo-l1-2-1 */
TgVOID                                      (__stdcall *g_pfnGetSystemInfo)( LPSYSTEM_INFO ) = nullptr;
TgUINT_F64                                  (__stdcall *g_pfnGetTickCount64)( TgVOID ) = nullptr;
#if !defined(TgBUILD_UNIVERSAL__UWP)
BOOL                                        (__stdcall *g_pfnGetComputerNameEx)( COMPUTER_NAME_FORMAT , TgOSCHAR_P, LPDWORD ) = nullptr;
TgUINT_F32                                  (__stdcall *g_pfnGetSystemDirectory)( TgOSCHAR_P, TgUINT_F32  ) = nullptr;
TgUINT_F32                                  (__stdcall *g_pfnGetWindowsDirectory)( TgOSCHAR_P, TgUINT_F32  ) = nullptr;
BOOL                                        (__stdcall *g_pfnGlobalMemoryStatusEx)( LPMEMORYSTATUSEX ) = nullptr;
/*# !defined(TgBUILD_UNIVERSAL__UWP) */
#endif

/* API Set: api-ms-win-core-processenvironment-l1-2-0 */
DWORD                                       (__stdcall *g_pfnGetCurrentDirectory)( DWORD, TgOSCHAR_P ) = nullptr;
TgOSCHAR_P                                  (__stdcall *g_pfnGetCommandLine)( TgVOID ) = nullptr;

/* API Set: api-ms-win-core-profile-l1-1-0 */
BOOL                                        (__stdcall *g_pfnQueryPerformanceFrequency)( PLARGE_INTEGER ) = nullptr;
BOOL                                        (__stdcall *g_pfnQueryPerformanceCounter)( PLARGE_INTEGER ) = nullptr;

/* API Set: api-ms-win-core-file-l1-2-1 */
TgVOID_P                                    (__stdcall *g_pfnFindFirstFile)( TgOSCHAR_CP, LPWIN32_FIND_DATA ) = nullptr;
BOOL                                        (__stdcall *g_pfnFindNextFile)( TgVOID_P, LPWIN32_FIND_DATA ) = nullptr;
BOOL                                        (__stdcall *g_pfnFindClose)( TgVOID_P ) = nullptr;

/* API Set: api-ms-win-core-libraryloader-l1-2-0 */
DWORD                                       (__stdcall *g_pfnGetModuleFileName)( HMODULE, TgOSCHAR_P, DWORD ) = nullptr;

/* API Set: api-ms-win-core-memory-l1-1-2 */
TgVOID_P                                    (__stdcall *g_pfnVirtualAlloc)( TgVOID_P, TgUINT_F64 , DWORD, DWORD ) = nullptr;
TgSINT_F32                                  (__stdcall *g_pfnVirtualFree)( TgVOID_P, TgUINT_F64 , DWORD ) = nullptr;

#if defined(TgBUILD_UNIVERSAL__UWP)
/* API Set: api-ms-win-core-memory-l1-1-3 */
TgVOID_P                                    (__stdcall *g_pfnVirtualAllocFromApp)( TgVOID_P, TgUINT_F64 , DWORD, DWORD ) = nullptr;
/*# defined(TgBUILD_UNIVERSAL__UWP) */
#endif

#if !defined(TgBUILD_UNIVERSAL__UWP)
/* API Set: api-ms-win-core-realtime-l1-1-0 */
BOOL                                        (__stdcall *g_pfnQueryProcessCycleTime)( TgVOID_P, TgUINT_F64_P  ) = nullptr;
BOOL                                        (__stdcall *g_pfnQueryThreadCycleTime)( TgVOID_P, TgUINT_F64_P  ) = nullptr;

/*  API Set: ext-ms-win-ntuser-sysparams-ext-l1-1-0 */
TgSINT_F32                                  (__stdcall *g_pfnGetSystemMetrics)( TgSINT_F32 ) = nullptr;
TgSINT_F32                                  (__stdcall *g_pfnSystemParametersInfo)( TgUINT_F32 , TgUINT_F32 , TgVOID_P, TgUINT_F32  ) = nullptr;

/* API Set: api-ms-win-core-localization-l1-2-1 */
TgUINT_F32                                  (__stdcall *g_pfnGetACP)( TgVOID );

/* kernel32 */
TgVOID_P                                    (__stdcall *g_pfnCreateToolhelp32Snapshot)( DWORD, DWORD ) = nullptr;
BOOL                                        (__stdcall *g_pfnThread32First)( TgVOID_P, LPTHREADENTRY32 ) = nullptr;
BOOL                                        (__stdcall *g_pfnThread32Next)( TgVOID_P, LPTHREADENTRY32 ) = nullptr;

/* Advapi32 */
BOOL                                        (__stdcall *g_pfnGetUserName)( TgOSCHAR_P, LPDWORD  ) = nullptr;
BOOL                                        (__stdcall *g_pfnGetCurrentHwProfile)( LPHW_PROFILE_INFO ) = nullptr;

/* Psapi */
BOOL                                        (__stdcall *g_pfnEnumProcessModulesEx)( TgVOID_P, HINSTANCE*, DWORD, TgUINT_F32_P, DWORD ) = nullptr;
DWORD                                       (__stdcall *g_pfnGetModuleFileNameEx)( TgVOID_P, TgVOID_P, TgOSCHAR_P, DWORD ) = nullptr;

/*# !defined(TgBUILD_UNIVERSAL__UWP) */
#endif




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Macros                                                                                                                                                              */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

#define TFCN_TOQUOTE(FCN) #FCN
#if defined(TgCOMPILE_OS_TEXT__UTF8)
#define TFCN(FCN) TFCN_TOQUOTE(FCN##A)
#elif defined (TgCOMPILE_OS_TEXT__WIDE)
#define TFCN(FCN) TFCN_TOQUOTE(FCN##W)
#else
#endif


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Data                                                                                                                                                                */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

#if !defined(TgBUILD_UNIVERSAL__UWP)
static HINSTANCE                            s_hDLL_OLE32 = nullptr;
static HINSTANCE                            s_hDLL_SysParams_Ext = nullptr;
static HINSTANCE                            s_hDLL_GDI32 = nullptr;
static HINSTANCE                            s_hDLL_Kernel32 = nullptr;
static HINSTANCE                            s_hDLL_AdvAPI32 = nullptr;
static HINSTANCE                            s_hDLL_PSAPI = nullptr;

static HINSTANCE                            s_hDLL_Core_Sync1 = nullptr;
static HINSTANCE                            s_hDLL_Core_Sync2 = nullptr;
static HINSTANCE                            s_hDLL_Core_ProcessThread = nullptr;
static HINSTANCE                            s_hDLL_Core_Handle = nullptr;
static HINSTANCE                            s_hDLL_Core_SysInfo = nullptr;
static HINSTANCE                            s_hDLL_Core_ProcessEnvironment = nullptr;
static HINSTANCE                            s_hDLL_Core_Profile = nullptr;
static HINSTANCE                            s_hDLL_Core_File1 = nullptr;
static HINSTANCE                            s_hDLL_Core_File2 = nullptr;
static HINSTANCE                            s_hDLL_Core_Debugger = nullptr;
static HINSTANCE                            s_hDLL_Core_LibLoad = nullptr;
static HINSTANCE                            s_hDLL_Core_Local = nullptr;
static HINSTANCE                            s_hDLL_Core_Heap = nullptr;
static HINSTANCE                            s_hDLL_Core_Mem1 = nullptr;
static HINSTANCE                            s_hDLL_Core_Mem2 = nullptr;
static HINSTANCE                            s_hDLL_Core_RealTime = nullptr;
/*# !defined(TgBUILD_UNIVERSAL__UWP) */
#endif




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

#if !defined(TgBUILD_UNIVERSAL__UWP)
static TgRESULT                             GB_Init__Validate_CPU_ID( TgVOID );
static TgRESULT                             GB_Init__Delay_Loaded_DLL( TgVOID );
#else
TgVOID                                      GB_Init__Implicit_DLL( TgVOID );
/*# !defined(TgBUILD_UNIVERSAL__UWP) */
#endif




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

#if TgCOMPILE__CONSOLE_IDE_DEBUG_OUTPUT && defined(TgCOMPILE__CONSOLE_IDE_DEBUG_OUTPUT_SUPPORTED)

/* ---- tgIDE_DBG_ERR_Write ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRSIZE tgIDE_DBG_ERR_Write( STg2_Output_PC UNUSED_PARAM psOut, TgRSIZE_C UNUSED_PARAM uiOffset, TgVOID_CP szText, TgRSIZE_C nbyText )
{
    TgOSCHAR                            szBuffer[1024];

    if (nullptr == g_pfnOutputDebugString || nullptr ==szText || 0 == nbyText)
        return (0);

    /* TODO: Iterate through the string */
    TgOS_TEXT_FCN(Convert_USZ)( szBuffer, 1024, (TgCHAR_U8_CP)szText, nbyText );
    g_pfnOutputDebugString( szBuffer );

    return (0);
}


/* ---- tgIDE_DBG_OUT_Write ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRSIZE tgIDE_DBG_OUT_Write( STg2_Output_PC UNUSED_PARAM psOut, TgRSIZE_C UNUSED_PARAM uiOffset, TgVOID_CP szText, TgRSIZE_C nbyText )
{
    TgOSCHAR                            szBuffer[1024];

    if (nullptr == g_pfnOutputDebugString || nullptr ==szText || 0 == nbyText)
        return (0);

    /* TODO: Iterate through the string */
    TgOS_TEXT_FCN(Convert_USZ)( szBuffer, 1024, (TgCHAR_U8_CP)szText, nbyText );
    g_pfnOutputDebugString( szBuffer );

    return (0);
}


/*# TgCOMPILE__CONSOLE_IDE_DEBUG_OUTPUT */
#else

/* ---- tgIDE_DBG_ERR_Write ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRSIZE tgIDE_DBG_ERR_Write( STg2_Output_PC UNUSED_PARAM psOut, TgRSIZE_C UNUSED_PARAM uiOffset, TgVOID_CPC UNUSED_PARAM mbzText, TgRSIZE_C UNUSED_PARAM nbyText )
{
    return 0;
}


/* ---- tgIDE_DBG_OUT_Write ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRSIZE tgIDE_DBG_OUT_Write( STg2_Output_PC UNUSED_PARAM psOut, TgRSIZE_C UNUSED_PARAM uiOffset, TgVOID_CPC UNUSED_PARAM mbzText, TgRSIZE_C UNUSED_PARAM nbyText )
{
    return 0;
}


/*# TgCOMPILE__CONSOLE_IDE_DEBUG_OUTPUT && defined(TgCOMPILE__CONSOLE_IDE_DEBUG_OUTPUT_SUPPORTED) */
#endif




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgGB_Init_OS ------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgGB_Init_OS( TgVOID )
{
    TgOSCHAR_P                          pszCmdLN;

#if TgCOMPILE__THREAD_INFO
    tgMM_Set_U08_0x00(g_aTR_Thread, sizeof(g_aTR_Thread));
/*# TgCOMPILE__THREAD_INFO */
#endif

#if !defined(TgBUILD_UNIVERSAL__UWP)
    /* Validate the CPU info */
    if (TgFAILED( GB_Init__Validate_CPU_ID() ))
    {
        return (KTgE_FAIL);
    };

    /* Load DLL | Modules for function pointers */
    if (TgFAILED( GB_Init__Delay_Loaded_DLL() ))
    {
        tgGB_Free_OS();
        return (KTgE_FAIL);
    };
#else
    GB_Init__Implicit_DLL();
/*# !defined(TgBUILD_UNIVERSAL__UWP) */
#endif

    /* Get the command line from the application execution */
    if (0 != (pszCmdLN = g_pfnGetCommandLine()))
    {
        TgCHAR_U8                           oszCmdLN[4096];

        TgOS_TEXT_CONVERT_FCN(tgUSZ_Convert)( oszCmdLN, sizeof(oszCmdLN), pszCmdLN, KTgMAX_RSIZE );
        tgGB_CMD_Set_Command_Line( oszCmdLN );
    };


    /* Initialize the system information */
    tgSI_Init();

    tgTR_Register_Main_Thread( u8"CM Main Thread" );

    return (KTgS_OK);
}


/* ---- tgGB_Boot_OS ------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgGB_Boot_OS( TgVOID )
{
    tgSI_Boot();
    return (KTgS_OK);
}


/* ---- tgGB_Stop_OS ------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgGB_Stop_OS( TgVOID )
{
    tgSI_Stop();
}


/* ---- tgGB_Free_OS ------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgGB_Free_OS( TgVOID )
{
    tgSI_Free();

#if !defined(TgBUILD_UNIVERSAL__UWP)
    tgGB_Free_Lib( &s_hDLL_Core_Sync1 );
    tgGB_Free_Lib( &s_hDLL_Core_Sync2 );
    tgGB_Free_Lib( &s_hDLL_Core_ProcessThread );
    tgGB_Free_Lib( &s_hDLL_Core_Handle );
    tgGB_Free_Lib( &s_hDLL_Core_SysInfo );
    tgGB_Free_Lib( &s_hDLL_Core_ProcessEnvironment );
    tgGB_Free_Lib( &s_hDLL_Core_Profile );
    tgGB_Free_Lib( &s_hDLL_Core_File1 );
    tgGB_Free_Lib( &s_hDLL_Core_File2 );
    tgGB_Free_Lib( &s_hDLL_Core_Debugger );
    tgGB_Free_Lib( &s_hDLL_Core_LibLoad );
    tgGB_Free_Lib( &s_hDLL_Core_Local );
    tgGB_Free_Lib( &s_hDLL_Core_Heap );
    tgGB_Free_Lib( &s_hDLL_Core_Mem1 );
    tgGB_Free_Lib( &s_hDLL_Core_Mem2 );
    tgGB_Free_Lib( &s_hDLL_Core_RealTime );

    tgGB_Free_Lib( &s_hDLL_PSAPI );
    tgGB_Free_Lib( &s_hDLL_AdvAPI32 );
    tgGB_Free_Lib( &s_hDLL_Kernel32 );
    tgGB_Free_Lib( &s_hDLL_GDI32 );
    tgGB_Free_Lib( &s_hDLL_SysParams_Ext );
    tgGB_Free_Lib( &s_hDLL_OLE32 );
/*# !defined(TgBUILD_UNIVERSAL__UWP) */
#endif
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Local File Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

#if !defined(TgBUILD_UNIVERSAL__UWP)
/* ---- GB_Init__Validate_CPU_ID ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT GB_Init__Validate_CPU_ID( TgVOID )
{
#if defined(TgBUILD_COMPILER__MSVC)
    TgSINT_F32                            aiCPUInfo[4] = { -1 };

    __cpuid( aiCPUInfo, 1 );
    TgERROR(0 != (aiCPUInfo[2] & (1 << 13)));
#endif

    return (KTgS_OK);
}
/*# !defined(TgBUILD_UNIVERSAL__UWP) */
#endif


#if !defined(TgBUILD_UNIVERSAL__UWP)
/* ---- GB_Init__Delay_Loaded_DLL ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT GB_Init__Delay_Loaded_DLL( TgVOID )
{
    STg2_Output                         sOutCon;

    sOutCon.m_pfnWrite = tgCM_DBG_ERR_Write;
    sOutCon.m_pfnClose = nullptr;

#if !defined(TgCOMPILE_WIDE_CHAR)
    /* API Set: api-ms-win-core-synch-l1-2-0 */
    if (!tgGB_Load_Lib( &s_hDLL_Core_Sync1, TgOS_TEXT("api-ms-win-core-synch-ansi-l1-1-0") ))
    {
        tgIO_PrintF( &sOutCon, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to load api-ms-win-core-synch-ansi-l1-1-0" );
        return (KTgE_FAIL);
    };

    if (
           !tgGB_Get_Func_Address( (FARPROC*)&g_pfnCreateSemaphoreEx, s_hDLL_Core_Sync1, ("CreateSemaphoreExA") )
        )
    {
        tgIO_PrintF( &sOutCon, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to find function in api-ms-win-core-synch-ansi-l1-1-0" );
        return (KTgE_FAIL);
    };
/*# !defined(TgCOMPILE_WIDE_CHAR) */
#endif

    /* API Set: api-ms-win-core-synch-l1-1-0 */
    if (!tgGB_Load_Lib( &s_hDLL_Core_Sync2, TgOS_TEXT("api-ms-win-core-synch-l1-1-0") ))
    {
        tgIO_PrintF( &sOutCon, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to load api-ms-win-core-synch-l1-2-0" );
        return (KTgE_FAIL);
    };

    if (
           !tgGB_Get_Func_Address( (FARPROC*)&g_pfnCreateEventEx, s_hDLL_Core_Sync2, TFCN( CreateEventEx ) )
        || !tgGB_Get_Func_Address( (FARPROC*)&g_pfnCreateEvent, s_hDLL_Core_Sync2, TFCN( CreateEvent ) )
        || !tgGB_Get_Func_Address( (FARPROC*)&g_pfnReleaseSemaphore, s_hDLL_Core_Sync2, ("ReleaseSemaphore") )
        || !tgGB_Get_Func_Address( (FARPROC*)&g_pfnCreateMutexEx, s_hDLL_Core_Sync2, TFCN( CreateMutexEx ) )
        || !tgGB_Get_Func_Address( (FARPROC*)&g_pfnReleaseMutex, s_hDLL_Core_Sync2, ("ReleaseMutex") )
        || !tgGB_Get_Func_Address( (FARPROC*)&g_pfnWaitForSingleObjectEx, s_hDLL_Core_Sync2, ("WaitForSingleObjectEx") )
        || !tgGB_Get_Func_Address( (FARPROC*)&g_pfnSleep, s_hDLL_Core_Sync2, ("Sleep") )
    #if defined(TgCOMPILE_WIDE_CHAR)
        || !tgGB_Get_Func_Address( (FARPROC*)&g_pfnCreateSemaphoreEx, s_hDLL_Core_Sync2, TgOS_TEXT("CreateSemaphoreExW") )
    #endif
        )
    {
        tgIO_PrintF( &sOutCon, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to find function in api-ms-win-core-synch-l1-2-0" );
        return (KTgE_FAIL);
    };

    /* API Set: api-ms-win-core-processthreads-l1-1-0 */
    if (!tgGB_Load_Lib( &s_hDLL_Core_ProcessThread, TgOS_TEXT("api-ms-win-core-processthreads-l1-1-0") ))
    {
        tgIO_PrintF( &sOutCon, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to load api-ms-win-core-processthreads-l1-1-2" );
        return (KTgE_FAIL);
    };

    if (
           !tgGB_Get_Func_Address( (FARPROC*)&g_pfnGetCurrentProcess, s_hDLL_Core_ProcessThread, ("GetCurrentProcess") )
        || !tgGB_Get_Func_Address( (FARPROC*)&g_pfnGetCurrentProcessId, s_hDLL_Core_ProcessThread, ("GetCurrentProcessId") )
        || !tgGB_Get_Func_Address( (FARPROC*)&g_pfnCreateThread, s_hDLL_Core_ProcessThread, ("CreateThread") )
        || !tgGB_Get_Func_Address( (FARPROC*)&g_pfnGetCurrentThread, s_hDLL_Core_ProcessThread, ("GetCurrentThread") )
        || !tgGB_Get_Func_Address( (FARPROC*)&g_pfnGetCurrentThreadId, s_hDLL_Core_ProcessThread, ("GetCurrentThreadId") )
        || !tgGB_Get_Func_Address( (FARPROC*)&g_pfnExitThread, s_hDLL_Core_ProcessThread, ("ExitThread") )
        || !tgGB_Get_Func_Address( (FARPROC*)&g_pfnSetThreadPriority, s_hDLL_Core_ProcessThread, ("SetThreadPriority") )
        || !tgGB_Get_Func_Address( (FARPROC*)&g_pfnSwitchToThread, s_hDLL_Core_ProcessThread, ("SwitchToThread") )
        || !tgGB_Get_Func_Address( (FARPROC*)&g_pfnIsProcessorFeaturePresent, s_hDLL_Core_ProcessThread, ("IsProcessorFeaturePresent") )
        )
    {
        tgIO_PrintF( &sOutCon, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to find function in api-ms-win-core-processthreads-l1-1-2" );
        return (KTgE_FAIL);
    };

    /* API Set: api-ms-win-core-handle-l1-1-0 */
    if (!tgGB_Load_Lib( &s_hDLL_Core_Handle, TgOS_TEXT("api-ms-win-core-handle-l1-1-0") ))
    {
        tgIO_PrintF( &sOutCon, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to load api-ms-win-core-handle-l1-1-0" );
        return (KTgE_FAIL);
    };

    if (
           !tgGB_Get_Func_Address( (FARPROC*)&g_pfnCloseHandle, s_hDLL_Core_Handle, ("CloseHandle") )
        || !tgGB_Get_Func_Address( (FARPROC*)&g_pfnDuplicateHandle, s_hDLL_Core_Handle, ("DuplicateHandle") )
        )
    {
        tgIO_PrintF( &sOutCon, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to find function in api-ms-win-core-handle-l1-1-0" );
        return (KTgE_FAIL);
    };

    /* API Set: api-ms-win-core-debug-l1-1-0 */
    if (!tgGB_Load_Lib( &s_hDLL_Core_Debugger, TgOS_TEXT("api-ms-win-core-debug-l1-1-0") ))
    {
        tgIO_PrintF( &sOutCon, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to load api-ms-win-core-debug-l1-1-0" );
        return (KTgE_FAIL);
    };

    if (
           !tgGB_Get_Func_Address( (FARPROC*)&g_pfnOutputDebugString, s_hDLL_Core_Debugger, TFCN( OutputDebugString ) )
        || !tgGB_Get_Func_Address( (FARPROC*)&g_pfnIsDebuggerPresent, s_hDLL_Core_Debugger, ("IsDebuggerPresent") )
        )
    {
        tgIO_PrintF( &sOutCon, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to find function in api-ms-win-core-debug-l1-1-0" );
        return (KTgE_FAIL);
    };

    /* API Set: api-ms-win-core-sysinfo-l1-1-0 */
    if (!tgGB_Load_Lib( &s_hDLL_Core_SysInfo, TgOS_TEXT("api-ms-win-core-sysinfo-l1-1-0") ))
    {
        tgIO_PrintF( &sOutCon, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to load api-ms-win-core-sysinfo-l1-2-1" );
        return (KTgE_FAIL);
    };

    if (
           !tgGB_Get_Func_Address( (FARPROC*)&g_pfnGetSystemInfo, s_hDLL_Core_SysInfo, ("GetNativeSystemInfo") )
        || !tgGB_Get_Func_Address( (FARPROC*)&g_pfnGetTickCount64, s_hDLL_Core_SysInfo, ("GetTickCount64") )
        || !tgGB_Get_Func_Address( (FARPROC*)&g_pfnGetComputerNameEx, s_hDLL_Core_SysInfo, TFCN( GetComputerNameEx ) )
        || !tgGB_Get_Func_Address( (FARPROC*)&g_pfnGetSystemDirectory, s_hDLL_Core_SysInfo, TFCN( GetSystemDirectory ) )
        || !tgGB_Get_Func_Address( (FARPROC*)&g_pfnGetWindowsDirectory, s_hDLL_Core_SysInfo, TFCN( GetWindowsDirectory ) )
        || !tgGB_Get_Func_Address( (FARPROC*)&g_pfnGlobalMemoryStatusEx, s_hDLL_Core_SysInfo, ("GlobalMemoryStatusEx") )
        )
    {
        tgIO_PrintF( &sOutCon, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to find function in api-ms-win-core-sysinfo-l1-2-1" );
        return (KTgE_FAIL);
    };

    /* API Set: api-ms-win-core-processenvironment-l1-1-0 */
    if (!tgGB_Load_Lib( &s_hDLL_Core_ProcessEnvironment, TgOS_TEXT("api-ms-win-core-processenvironment-l1-1-0") ))
    {
        tgIO_PrintF( &sOutCon, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to load api-ms-win-core-processenvironment-l1-1-0" );
        return (KTgE_FAIL);
    };

    if (
           !tgGB_Get_Func_Address( (FARPROC*)&g_pfnGetCurrentDirectory, s_hDLL_Core_ProcessEnvironment, TFCN( GetCurrentDirectory ) )
        || !tgGB_Get_Func_Address( (FARPROC*)&g_pfnGetCommandLine, s_hDLL_Core_ProcessEnvironment, TFCN( GetCommandLine ) )
        )
    {
        tgIO_PrintF( &sOutCon, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to find function in api-ms-win-core-processenvironment-l1-2-0" );
        return (KTgE_FAIL);
    };

    /* API Set: api-ms-win-core-profile-l1-1-0 */
    if (!tgGB_Load_Lib( &s_hDLL_Core_Profile, TgOS_TEXT("api-ms-win-core-profile-l1-1-0") ))
    {
        tgIO_PrintF( &sOutCon, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to load api-ms-win-core-profile-l1-1-0" );
        return (KTgE_FAIL);
    };

    if (
           !tgGB_Get_Func_Address( (FARPROC*)&g_pfnQueryPerformanceFrequency, s_hDLL_Core_Profile, ("QueryPerformanceFrequency") )
        || !tgGB_Get_Func_Address( (FARPROC*)&g_pfnQueryPerformanceCounter, s_hDLL_Core_Profile, ("QueryPerformanceCounter") )
        )
    {
        tgIO_PrintF( &sOutCon, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to find function in api-ms-win-core-profile-l1-1-0" );
        return (KTgE_FAIL);
    };

    /* API Set: api-ms-win-core-file-l1-1-0 */
    if (!tgGB_Load_Lib( &s_hDLL_Core_File1, TgOS_TEXT("api-ms-win-core-file-l1-1-0") ))
    {
        tgIO_PrintF( &sOutCon, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to load api-ms-win-core-file-l1-1-0" );
        return (KTgE_FAIL);
    };

    if (
           !tgGB_Get_Func_Address( (FARPROC*)&g_pfnFindFirstFile, s_hDLL_Core_File1, TFCN( FindFirstFile ) )
        || !tgGB_Get_Func_Address( (FARPROC*)&g_pfnFindNextFile, s_hDLL_Core_File1, TFCN( FindNextFile ) )
        || !tgGB_Get_Func_Address( (FARPROC*)&g_pfnFindClose, s_hDLL_Core_File1, "FindClose" )
        )
    {
        tgIO_PrintF( &sOutCon, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to find function in api-ms-win-core-file-l1-1-0" );
        return (KTgE_FAIL);
    };

    /* API Set: api-ms-win-core-libraryloader-l1-2-0 */
    if (!tgGB_Load_Lib( &s_hDLL_Core_LibLoad, TgOS_TEXT("api-ms-win-core-libraryloader-l1-2-0") ))
    {
        tgIO_PrintF( &sOutCon, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to load api-ms-win-core-libraryloader-l1-2-0" );
        return (KTgE_FAIL);
    };

    if (
           !tgGB_Get_Func_Address( (FARPROC*)&g_pfnGetModuleFileName, s_hDLL_Core_LibLoad, TFCN( GetModuleFileName ) )
        )
    {
        tgIO_PrintF( &sOutCon, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to find function in api-ms-win-core-libraryloader-l1-2-0" );
        return (KTgE_FAIL);
    };

    /* API Set: api-ms-win-core-memory-l1-1-0 */
    if (!tgGB_Load_Lib( &s_hDLL_Core_Mem1, TgOS_TEXT("api-ms-win-core-memory-l1-1-0") ))
    {
        tgIO_PrintF( &sOutCon, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to load api-ms-win-core-memory-l1-1-0" );
        return (KTgE_FAIL);
    };

    if (
           !tgGB_Get_Func_Address( (FARPROC*)&g_pfnVirtualFree, s_hDLL_Core_Mem1, ("VirtualFree") )
        || !tgGB_Get_Func_Address( (FARPROC*)&g_pfnVirtualAlloc, s_hDLL_Core_Mem1, ("VirtualAlloc") )
        )
    {
        tgIO_PrintF( &sOutCon, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to find function in api-ms-win-core-memory-l1-1-0" );
        return (KTgE_FAIL);
    };

    /* API Set: api-ms-win-core-realtime-l1-1-0 */
    if (!tgGB_Load_Lib( &s_hDLL_Core_RealTime, TgOS_TEXT("api-ms-win-core-realtime-l1-1-0") ))
    {
        tgIO_PrintF( &sOutCon, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to load api-ms-win-core-realtime-l1-1-0" );
        return (KTgE_FAIL);
    };

    if (
           !tgGB_Get_Func_Address( (FARPROC*)&g_pfnQueryProcessCycleTime, s_hDLL_Core_RealTime, ("QueryProcessCycleTime") )
        || !tgGB_Get_Func_Address( (FARPROC*)&g_pfnQueryThreadCycleTime, s_hDLL_Core_RealTime, ("QueryThreadCycleTime") )
        )
    {
        tgIO_PrintF( &sOutCon, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to find function in api-ms-win-core-realtime-l1-1-0" );
        return (KTgE_FAIL);
    };

    /* Kernel32 */
    if (!tgGB_Load_Lib( &s_hDLL_Kernel32, TgOS_TEXT("kernel32") ))
    {
        tgIO_PrintF( &sOutCon, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to load kernel32" );
        return (KTgE_FAIL);
    };

    if (
           !tgGB_Get_Func_Address( (FARPROC*)&g_pfnCreateToolhelp32Snapshot, s_hDLL_Kernel32, ("CreateToolhelp32Snapshot") )
        || !tgGB_Get_Func_Address( (FARPROC*)&g_pfnThread32First, s_hDLL_Kernel32, ("Thread32First") )
        || !tgGB_Get_Func_Address( (FARPROC*)&g_pfnThread32Next, s_hDLL_Kernel32, ("Thread32Next") )
        || !tgGB_Get_Func_Address( (FARPROC*)&g_pfnQueryProcessCycleTime, s_hDLL_Kernel32, ("QueryProcessCycleTime") )
        || !tgGB_Get_Func_Address( (FARPROC*)&g_pfnQueryThreadCycleTime, s_hDLL_Kernel32, ("QueryThreadCycleTime") )
        || !tgGB_Get_Func_Address( (FARPROC*)&g_pfnVirtualAlloc, s_hDLL_Kernel32, ("VirtualAlloc") )
        || !tgGB_Get_Func_Address( (FARPROC*)&g_pfnGetACP, s_hDLL_Kernel32, ("GetACP") )
        )
    {
        tgIO_PrintF( &sOutCon, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to find function in kernel32" );
        return (KTgE_FAIL);
    };

    /* Load the AdvAPI32 functions from the DLL */
    if (!tgGB_Load_Lib( &s_hDLL_AdvAPI32, TgOS_TEXT("advapi32.dll") ))
    {
        tgIO_PrintF( &sOutCon, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to load AdvAPI32 DLL." );
        return (KTgE_FAIL);
    };

    if (
           !tgGB_Get_Func_Address( (FARPROC*)&g_pfnGetUserName, s_hDLL_AdvAPI32, TFCN( GetUserName ) )
        || !tgGB_Get_Func_Address( (FARPROC*)&g_pfnGetCurrentHwProfile, s_hDLL_AdvAPI32, TFCN( GetCurrentHwProfile ) )
    )
    {
        tgIO_PrintF( &sOutCon, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to find function in AdvAPI32 DLL." );
        return (KTgE_FAIL);
    };

    /* Load the PSAPI functions from the DLL */
    if (!tgGB_Load_Lib( &s_hDLL_PSAPI, TgOS_TEXT("psapi.dll") ))
    {
        TgCRITICAL_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to load PSAPI DLL." );
        return (KTgE_FAIL);
    };

    if (
           !tgGB_Get_Func_Address( (FARPROC*)&g_pfnEnumProcessModulesEx, s_hDLL_PSAPI, ("EnumProcessModulesEx") )
        || !tgGB_Get_Func_Address( (FARPROC*)&g_pfnGetModuleFileNameEx, s_hDLL_PSAPI, TFCN( GetModuleFileNameEx ) )
    )
    {
        tgIO_PrintF( &sOutCon, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to find function in PSAPI DLL." );
        return (KTgE_FAIL);
    };

    /* Load the User functions from the DLL */
    if (!tgGB_Load_Lib( &s_hDLL_SysParams_Ext, TgOS_TEXT("ext-ms-win-ntuser-sysparams-ext-l1-1-0") ))
    {
        tgIO_PrintF( &sOutCon, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to load ext-ms-win-ntuser-sysparams-ext-l1-1-0 DLL." );
        return (KTgE_FAIL);
    };

    if (
           !tgGB_Get_Func_Address( (FARPROC*)&g_pfnGetSystemMetrics, s_hDLL_SysParams_Ext, "GetSystemMetrics" )
        || !tgGB_Get_Func_Address( (FARPROC*)&g_pfnSystemParametersInfo, s_hDLL_SysParams_Ext, TFCN( SystemParametersInfo ) )
        )
    {
        tgIO_PrintF( &sOutCon, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to find function in User32 DLL." );
        return (KTgE_FAIL);
    };

    return (KTgS_OK);
}
/*# !defined(TgBUILD_UNIVERSAL__UWP) */
#endif


// == DLL Functions ============================================================================================================================================================== //

/* ---- tgGB_Load_Lib ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgGB_Load_Lib( HINSTANCE* phLib, TgOSCHAR_CPCU pszFileName )
{
    STg2_Output                         tgOutCon;

    TgPARAM_CHECK( (nullptr != pszFileName) && (0 != pszFileName[0]) );

    tgOutCon.m_pfnWrite = tgCM_DBG_ERR_Write;
    tgOutCon.m_pfnClose = nullptr;

    if (nullptr == (*phLib = LoadLibrary( pszFileName )))
    {
        tgIO_PrintF( &tgOutCon, STD_MSG_LITERAL_2, STD_MSG_POST, u8"Unable to load ", pszFileName );
        return (false);
    };

    return (true);
}


/* ---- tgGB_Free_Lib ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgGB_Free_Lib( HINSTANCE* phLib )
{
    TgPARAM_CHECK( phLib );

    if (nullptr != *phLib)
    {
        FreeLibrary( *phLib );
        *phLib = nullptr;
    };
}


/* ---- tgGB_Get_Func_Address ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgGB_Get_Func_Address( FARPROC* pfnFunc, HINSTANCE hLib, TgCHAR_NC_CPCU pszFuncName )
{
    STg2_Output                         tgOutCon;

    TgPARAM_CHECK( (nullptr != pszFuncName) && (0 != pszFuncName[0]) );

    tgOutCon.m_pfnWrite = tgCM_DBG_ERR_Write;
    tgOutCon.m_pfnClose = nullptr;

    if (nullptr == (*pfnFunc = GetProcAddress( hLib, pszFuncName )))
    {
        tgIO_PrintF( &tgOutCon, STD_MSG_LITERAL_2, STD_MSG_POST, u8"Unable to find function ", pszFuncName );
        return (false);
    };

    return (true);
}
