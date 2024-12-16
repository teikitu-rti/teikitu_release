/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (WIN) Common - Global - Data.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_WIN_COMMON_GLOBAL_DATA_H)
#define TGS_WIN_COMMON_GLOBAL_DATA_H
#pragma once

#include "TgS COMMON/TgS (WIN) Common - Base - Include.h"


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Types                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

typedef struct tagTHREADENTRY32             *LPTHREADENTRY32;




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Data                                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/* Updated for 10.0.16299 */

/*  API Set: api-ms-win-core-synch-l1-1-0 */
TgEXTN TgVOID_P                             (__stdcall *g_pfnCreateEventEx)( LPSECURITY_ATTRIBUTES, TgOSCHAR_CP, DWORD, DWORD);
TgEXTN TgVOID_P                             (__stdcall *g_pfnCreateEvent)( LPSECURITY_ATTRIBUTES, BOOL, BOOL, TgOSCHAR_CP );
TgEXTN TgVOID_P                             (__stdcall *g_pfnCreateSemaphoreEx)( LPSECURITY_ATTRIBUTES, LONG, LONG, TgOSCHAR_CP, DWORD, DWORD );
TgEXTN TgSINT_F32                           (__stdcall *g_pfnReleaseSemaphore)( TgVOID_P, LONG, LPLONG );
TgEXTN TgVOID_P                             (__stdcall *g_pfnCreateMutexEx)( LPSECURITY_ATTRIBUTES, TgOSCHAR_CP, DWORD, DWORD );
TgEXTN TgSINT_F32                           (__stdcall *g_pfnReleaseMutex)( TgVOID_P );
TgEXTN DWORD                                (__stdcall *g_pfnWaitForSingleObjectEx)( TgVOID_P, DWORD, BOOL );
TgEXTN TgVOID                               (__stdcall *g_pfnSleep)( DWORD );

/*  API Set: api-ms-win-core-processthreads-l1-1-0 */
TgEXTN TgVOID_P                             (__stdcall *g_pfnGetCurrentProcess)( TgVOID );
TgEXTN DWORD                                (__stdcall *g_pfnGetCurrentProcessId)( TgVOID );
TgEXTN TgVOID_P                             (__stdcall *g_pfnCreateThread)( LPSECURITY_ATTRIBUTES, TgRSIZE, LPTHREAD_START_ROUTINE, TgVOID_P, DWORD, LPDWORD );
TgEXTN TgVOID_P                             (__stdcall *g_pfnGetCurrentThread)( TgVOID ); /* Returns a pseudo-handle */
TgEXTN DWORD                                (__stdcall *g_pfnGetCurrentThreadId)( TgVOID );
TgEXTN TgVOID                               (__stdcall *g_pfnExitThread)( DWORD );
TgEXTN BOOL                                 (__stdcall *g_pfnSetThreadPriority)( TgVOID_P, TgSINT_F32 );
TgEXTN TgSINT_F32                           (__stdcall *g_pfnSwitchToThread)( TgVOID );
TgEXTN TgSINT_F32                           (__stdcall *g_pfnIsProcessorFeaturePresent)( DWORD );

/*  API Set: api-ms-win-core-handle-l1-1-0 */
TgEXTN TgSINT_F32                           (__stdcall *g_pfnCloseHandle)( TgVOID_P );
TgEXTN TgSINT_F32                           (__stdcall *g_pfnDuplicateHandle)( TgVOID_P, TgVOID_P, TgVOID_P, TgVOID_PP, DWORD, BOOL, DWORD );

/*  API Set: api-ms-win-core-debug-l1-1-0 */
TgEXTN TgVOID                               (__stdcall *g_pfnOutputDebugString)( TgOSCHAR_CP );
TgEXTN BOOL                                 (__stdcall *g_pfnIsDebuggerPresent)( TgVOID );

/*  API Set: api-ms-win-core-sysinfo-l1-1-0 */
TgEXTN TgVOID                               (__stdcall *g_pfnGetSystemInfo)( LPSYSTEM_INFO );
TgEXTN TgUINT_F64                           (__stdcall *g_pfnGetTickCount64)( TgVOID );
#if !defined(TgBUILD_UNIVERSAL__UWP)
TgEXTN BOOL                                 (__stdcall *g_pfnGetComputerNameEx)( COMPUTER_NAME_FORMAT, TgOSCHAR_P, LPDWORD );
TgEXTN TgUINT_F32                           (__stdcall *g_pfnGetSystemDirectory)( TgOSCHAR_P, TgUINT_F32 );
TgEXTN TgUINT_F32                           (__stdcall *g_pfnGetWindowsDirectory)( TgOSCHAR_P, TgUINT_F32 );
TgEXTN BOOL                                 (__stdcall *g_pfnGlobalMemoryStatusEx)( LPMEMORYSTATUSEX );
/*# !defined(TgBUILD_UNIVERSAL__UWP) */
#endif

/*  API Set: api-ms-win-core-processenvironment-l1-1-0 */
TgEXTN DWORD                                (__stdcall *g_pfnGetCurrentDirectory)( DWORD, TgOSCHAR_P );
TgEXTN TgOSCHAR_P                           (__stdcall *g_pfnGetCommandLine)( TgVOID );

/*  API Set: api-ms-win-core-profile-l1-1-0 */
TgEXTN BOOL                                 (__stdcall *g_pfnQueryPerformanceFrequency)( PLARGE_INTEGER );
TgEXTN BOOL                                 (__stdcall *g_pfnQueryPerformanceCounter)( PLARGE_INTEGER );

/*  API Set: api-ms-win-core-file-l1-1-0 */
TgEXTN TgVOID_P                             (__stdcall *g_pfnFindFirstFile)( TgOSCHAR_CP, LPWIN32_FIND_DATA );
TgEXTN BOOL                                 (__stdcall *g_pfnFindNextFile)( TgVOID_P, LPWIN32_FIND_DATA );
TgEXTN BOOL                                 (__stdcall *g_pfnFindClose)( TgVOID_P );

 /*  API Set: api-ms-win-core-libraryloader-l1-2-0 */
TgEXTN DWORD                                (__stdcall *g_pfnGetModuleFileName)( HMODULE, TgOSCHAR_P, DWORD );

/*  API Set: api-ms-win-core-memory-l1-1-0 */
TgEXTN TgVOID_P                             (__stdcall *g_pfnVirtualAlloc)( TgVOID_P, TgUINT_F64, DWORD, DWORD );
TgEXTN TgSINT_F32                           (__stdcall *g_pfnVirtualFree)( TgVOID_P, TgUINT_F64, DWORD );

#if defined(TgBUILD_UNIVERSAL__UWP)
 /*  API Set: api-ms-win-core-memory-l1-1-3, api-ms-win-core-memory-l1-1-3 */
TgEXTN TgVOID_P                             (__stdcall *g_pfnVirtualAllocFromApp)( TgVOID_P, TgUINT_F64, DWORD, DWORD );
/*# !defined(TgBUILD_UNIVERSAL__UWP) */
#endif

#if !defined(TgBUILD_UNIVERSAL__UWP)
 /*  API Set: api-ms-win-core-realtime-l1-1-0 */
TgEXTN BOOL                                 (__stdcall *g_pfnQueryProcessCycleTime)( TgVOID_P, TgUINT_F64_P );
TgEXTN BOOL                                 (__stdcall *g_pfnQueryThreadCycleTime)( TgVOID_P, TgUINT_F64_P );

/*  API Set: ext-ms-win-ntuser-sysparams-ext-l1-1-0 */
TgEXTN TgSINT_F32                           (__stdcall *g_pfnGetSystemMetrics)( TgSINT_F32 );
TgEXTN TgSINT_F32                           (__stdcall *g_pfnSystemParametersInfo)( TgUINT_F32, TgUINT_F32, TgVOID_P, TgUINT_F32 );

/* API Set: api-ms-win-core-localization-l1-2-1 */
TgEXTN TgUINT_F32                           (__stdcall *g_pfnGetACP)( TgVOID );

 /*  kernel32 */
TgEXTN TgVOID_P                             (__stdcall *g_pfnCreateToolhelp32Snapshot)( DWORD, DWORD );
TgEXTN BOOL                                 (__stdcall *g_pfnThread32First)( TgVOID_P, LPTHREADENTRY32 );
TgEXTN BOOL                                 (__stdcall *g_pfnThread32Next)( TgVOID_P, LPTHREADENTRY32 );

 /* Advapi32 */
TgEXTN BOOL                                 (__stdcall *g_pfnGetUserName)( TgOSCHAR_P, LPDWORD );
TgEXTN BOOL                                 (__stdcall *g_pfnGetCurrentHwProfile)( LPHW_PROFILE_INFO );

 /* Psapi */
TgEXTN BOOL                                 (__stdcall *g_pfnEnumProcessModulesEx)( TgVOID_P, HINSTANCE*, DWORD, TgUINT_F32_P, DWORD );
TgEXTN DWORD                                (__stdcall *g_pfnGetModuleFileNameEx)( TgVOID_P, TgVOID_P, TgOSCHAR_P, DWORD );

/*# defined(TgBUILD_UNIVERSAL__UWP) */
#endif

/* =============================================================================================================================================================================== */
#endif
