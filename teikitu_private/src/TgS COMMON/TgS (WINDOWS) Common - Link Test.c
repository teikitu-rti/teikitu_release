/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (WINDOWS) Common - Link Test.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

TgDISABLE_ALL_WARNNGS_PUSH
#include <windows.h>
#include <TlHelp32.h>
TgDISABLE_ALL_WARNNGS_POP

TgCOMPILER_ASSERT( sizeof( TgOSCHAR ) == sizeof( TCHAR ), 0 );


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
 /*   Link Test */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
TgEXTN TgVOID Function_Type_Test(TgVOID);

TgVOID Function_Type_Test( TgVOID )
{
#if !defined(TgBUILD_UNIVERSAL__UWP)
    WNDPROC pfnWndProcB = DefWindowProc;
    (void)pfnWndProcB;
/*# !defined(TgBUILD_UNIVERSAL__UWP) */
#endif

     /*  API Set: api-ms-win-core-synch-l1-2-0 */
    g_pfnCreateEventEx = CreateEventEx;
    g_pfnCreateEvent = CreateEvent;
    g_pfnCreateSemaphoreEx = CreateSemaphoreEx;
    g_pfnReleaseSemaphore = ReleaseSemaphore;
    g_pfnCreateMutexEx = CreateMutexEx;
    g_pfnReleaseMutex = ReleaseMutex;
    g_pfnWaitForSingleObjectEx = WaitForSingleObjectEx;
    g_pfnSleep = Sleep;

     /*  API Set: api-ms-win-core-processthreads-l1-1-2 */
    g_pfnGetCurrentProcess = GetCurrentProcess;
    g_pfnGetCurrentProcessId = GetCurrentProcessId;
    g_pfnCreateThread = CreateThread;
    g_pfnGetCurrentThread = GetCurrentThread;
    g_pfnGetCurrentThreadId = GetCurrentThreadId;
    g_pfnExitThread = ExitThread;
    g_pfnSetThreadPriority = SetThreadPriority;
    g_pfnSwitchToThread = SwitchToThread;
    g_pfnIsProcessorFeaturePresent = IsProcessorFeaturePresent;

     /*  API Set: api-ms-win-core-handle-l1-1-0 */
    g_pfnCloseHandle = CloseHandle;
    g_pfnDuplicateHandle = DuplicateHandle;

     /*  API Set: api-ms-win-core-sysinfo-l1-2-1 */
    g_pfnGetSystemInfo = GetNativeSystemInfo;
    g_pfnGetTickCount64 = GetTickCount64;
#if !defined(TgBUILD_UNIVERSAL__UWP)
    g_pfnGetComputerNameEx = GetComputerNameEx;
    g_pfnGetSystemDirectory = GetSystemDirectory;
    g_pfnGetWindowsDirectory = GetWindowsDirectory;
    g_pfnGlobalMemoryStatusEx = GlobalMemoryStatusEx;
/*# !defined(TgBUILD_UNIVERSAL__UWP) */
#endif

     /*  API Set: api-ms-win-core-processenvironment-l1-2-0 */
    g_pfnGetCurrentDirectory = GetCurrentDirectory;
    g_pfnGetCommandLine = GetCommandLine;

     /*  API Set: api-ms-win-core-profile-l1-1-0 */
    g_pfnQueryPerformanceFrequency = QueryPerformanceFrequency;
    g_pfnQueryPerformanceCounter = QueryPerformanceCounter;

     /*  API Set: api-ms-win-core-file-l1-2-1 */
    g_pfnFindFirstFile = FindFirstFile;
    g_pfnFindNextFile = FindNextFile;
    g_pfnFindClose = FindClose;

     /*  API Set: api-ms-win-core-libraryloader-l1-2-0 */
    g_pfnGetModuleFileName = GetModuleFileName;

     /*  API Set: api-ms-win-core-memory-l1-1-2 */
    g_pfnVirtualAlloc = VirtualAlloc;
    g_pfnVirtualFree = VirtualFree;

#if defined(TgBUILD_UNIVERSAL__UWP)
     /*  API Set: api-ms-win-core-memory-l1-1-3 */
    g_pfnVirtualAllocFromApp = VirtualAllocFromApp;
#endif

#if !defined(TgBUILD_UNIVERSAL__UWP)
     /*  API Set: api-ms-win-core-realtime-l1-1-0 */
    g_pfnQueryProcessCycleTime = QueryProcessCycleTime;
    g_pfnQueryThreadCycleTime = QueryThreadCycleTime;
#endif


#if !defined(TgBUILD_UNIVERSAL__UWP)
     /*  kernel32 */
    g_pfnCreateToolhelp32Snapshot = CreateToolhelp32Snapshot;
    g_pfnThread32First = Thread32First;
    g_pfnThread32Next = Thread32Next;
    g_pfnGetACP = GetACP;

     /* user32 */
    g_pfnGetSystemMetrics = GetSystemMetrics;
    g_pfnSystemParametersInfo = SystemParametersInfo;

     /* Advapi32 */
    g_pfnGetUserName = GetUserName;
    g_pfnGetCurrentHwProfile = GetCurrentHwProfile;

     /* Psapi */
     /* g_pfnEnumProcessModulesEx = EnumProcessModulesEx; */
     /* g_pfnGetModuleFileNameEx = GetModuleFileNameEx; */
/*# !defined(TgBUILD_UNIVERSAL__UWP) */
#endif

}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
 /*   Validation */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

#if !defined(TgBUILD_UNIVERSAL__UWP)
TgCOMPILER_ASSERT( FORMAT_MESSAGE_ALLOCATE_BUFFER == 0x00000100, 0 );
#endif

TgCOMPILER_ASSERT( ComputerNameDnsFullyQualified == 3, 0 );
TgCOMPILER_ASSERT( CS_CLASSDC == 0x0040, 0 );
TgCOMPILER_ASSERT( FILE_SHARE_READ == 0x00000001L, 0 );
TgCOMPILER_ASSERT( FILE_SHARE_WRITE == 0x00000002L, 0 );
TgCOMPILER_ASSERT( FILE_GENERIC_READ == 0x00120089L, 0 );
TgCOMPILER_ASSERT( FILE_GENERIC_WRITE == 0x00120116L, 0 );
TgCOMPILER_ASSERT( FILE_ATTRIBUTE_NORMAL == 0x00000080L, 0 );
TgCOMPILER_ASSERT( FILE_FLAG_RANDOM_ACCESS == 0x10000000L, 0 );
TgCOMPILER_ASSERT( OPEN_ALWAYS == 4, 0 );
TgCOMPILER_ASSERT( FILE_ATTRIBUTE_DIRECTORY == 0x00000010, 0 );
TgCOMPILER_ASSERT( FILE_BEGIN == 0, 0 );
TgCOMPILER_ASSERT( FILE_CURRENT == 1, 0 );
TgCOMPILER_ASSERT( FILE_END == 2, 0 );
TgCOMPILER_ASSERT( FORMAT_MESSAGE_FROM_SYSTEM == 0x00001000, 0 );
TgCOMPILER_ASSERT( THREAD_PRIORITY_LOWEST == -2, 0 );
TgCOMPILER_ASSERT( THREAD_PRIORITY_BELOW_NORMAL == -1, 0 );
TgCOMPILER_ASSERT( THREAD_PRIORITY_NORMAL == 0, 0 );
TgCOMPILER_ASSERT( THREAD_PRIORITY_ABOVE_NORMAL == 1, 0 );
TgCOMPILER_ASSERT( THREAD_PRIORITY_HIGHEST == 2, 0 );
TgCOMPILER_ASSERT( THREAD_PRIORITY_TIME_CRITICAL == 15, 0 );
TgCOMPILER_ASSERT( WS_THICKFRAME == 0x00040000L, 0 );
TgCOMPILER_ASSERT( SM_CXFRAME == 32, 0 );
TgCOMPILER_ASSERT( SM_CYFRAME == 33, 0 );
TgCOMPILER_ASSERT( SM_CYCAPTION == 4, 0 );
TgCOMPILER_ASSERT( PM_NOREMOVE == 0x0000, 0 );
TgCOMPILER_ASSERT( (FILE_GENERIC_READ | FILE_GENERIC_WRITE) == 0x0012019FL, 0 );
TgCOMPILER_ASSERT( (FILE_SHARE_READ | FILE_SHARE_WRITE) == 3, 0 );
TgCOMPILER_ASSERT( SM_CMONITORS == 80, 0 );
TgCOMPILER_ASSERT( SM_CLEANBOOT == 67, 0 );
TgCOMPILER_ASSERT( SM_NETWORK == 63, 0 );
TgCOMPILER_ASSERT( SM_CXDOUBLECLK == 36, 0 );
TgCOMPILER_ASSERT( SM_CYDOUBLECLK == 37, 0 );
TgCOMPILER_ASSERT( SM_CXDRAG == 68, 0 );
TgCOMPILER_ASSERT( SM_CYDRAG == 69, 0 );
TgCOMPILER_ASSERT( SM_SERVERR2 == 89, 0 );
TgCOMPILER_ASSERT( SM_MOUSEWHEELPRESENT == 75, 0 );
TgCOMPILER_ASSERT( SM_MOUSEPRESENT == 19, 0 );
TgCOMPILER_ASSERT( PROCESSOR_ARCHITECTURE_AMD64 == 9, 0 );
TgCOMPILER_ASSERT( VER_NT_WORKSTATION == 0x0000001, 0 );
TgCOMPILER_ASSERT( VER_SUITE_WH_SERVER == 0x00008000, 0 );
TgCOMPILER_ASSERT( PF_COMPARE_EXCHANGE_DOUBLE == 2, 0 );
TgCOMPILER_ASSERT( PF_MMX_INSTRUCTIONS_AVAILABLE == 3, 0 );
TgCOMPILER_ASSERT( PF_XMMI_INSTRUCTIONS_AVAILABLE == 6, 0 );
TgCOMPILER_ASSERT( PF_3DNOW_INSTRUCTIONS_AVAILABLE == 7, 0 );
TgCOMPILER_ASSERT( PF_RDTSC_INSTRUCTION_AVAILABLE == 8, 0 );
TgCOMPILER_ASSERT( PF_XMMI64_INSTRUCTIONS_AVAILABLE == 10, 0 );
TgCOMPILER_ASSERT( PF_SSE3_INSTRUCTIONS_AVAILABLE == 13, 0 );
TgCOMPILER_ASSERT( PF_COMPARE_EXCHANGE128 == 14, 0 );
TgCOMPILER_ASSERT( PF_COMPARE64_EXCHANGE128 == 15, 0 );
TgCOMPILER_ASSERT( PAGE_READWRITE == 0x04, 0 );
TgCOMPILER_ASSERT( MEM_COMMIT == 0x1000, 0 );
TgCOMPILER_ASSERT( MEM_RESERVE == 0x2000, 0 );
TgCOMPILER_ASSERT( MEM_DECOMMIT == 0x4000, 0 );
TgCOMPILER_ASSERT( MEM_RELEASE == 0x8000, 0 );
TgCOMPILER_ASSERT( MEM_FREE == 0x10000, 0 );
TgCOMPILER_ASSERT( MEM_TOP_DOWN == 0x100000, 0 );
TgCOMPILER_ASSERT( DUPLICATE_SAME_ACCESS == 0x2, 0 );
