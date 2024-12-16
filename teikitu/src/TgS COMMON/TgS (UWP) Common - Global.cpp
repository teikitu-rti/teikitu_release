/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (UWP) Common - Global.cpp
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.12 | »GUID« 964CB1A6-814D-4E19-8E67-A83FCA98BF05 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Common ===================================================================================================================================================================== */

#include "TgS COMMON/TgS (WIN) Common - Base - LoadDLL.h"


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

#if defined(TgBUILD_UNIVERSAL__UWP)

#include <synchapi.h>
#include <processthreadsapi.h>
#include <handleapi.h>
#include <errhandlingapi.h>
#include <debugapi.h>
#include <profileapi.h>
#include <heapapi.h>
#include <memoryapi.h>
#include <libloaderapi.h>
#include <processenv.h>
#include <winbase.h>

TgEXTN TgVOID GB_Init__Implicit_DLL( TgVOID );
TgVOID GB_Init__Implicit_DLL( TgVOID )
{
    // API Set: api-ms-win-core-synch-l1-2-0
    g_pfnCreateEventEx = CreateEventEx;
    g_pfnSetEvent = SetEvent;
    g_pfnResetEvent = ResetEvent;
    g_pfnCreateSemaphoreEx = CreateSemaphoreEx;
    g_pfnReleaseSemaphore = ReleaseSemaphore;
    g_pfnCreateMutexEx = CreateMutexEx;
    g_pfnReleaseMutex = ReleaseMutex;
    g_pfnInitializeCriticalSectionEx = InitializeCriticalSectionEx;
    g_pfnEnterCriticalSection = EnterCriticalSection;
    g_pfnLeaveCriticalSection = LeaveCriticalSection;
    g_pfnTryEnterCriticalSection = TryEnterCriticalSection;
    g_pfnDeleteCriticalSection = DeleteCriticalSection;
    g_pfnWaitForSingleObjectEx = WaitForSingleObjectEx;
    g_pfnSleep = Sleep;

    // API Set: api-ms-win-core-processthreads-l1-1-2
    g_pfnGetCurrentProcess = GetCurrentProcess;
    g_pfnGetCurrentProcessId = GetCurrentProcessId;
    g_pfnGetCurrentThread = GetCurrentThread;
    g_pfnGetCurrentThreadId = GetCurrentThreadId;
    g_pfnGetThreadId = GetThreadId;
    g_pfnSuspendThread = SuspendThread;
    g_pfnResumeThread = ResumeThread;
    g_pfnSetThreadPriority = SetThreadPriority;
    g_pfnSwitchToThread = SwitchToThread;
    g_pfnIsProcessorFeaturePresent = IsProcessorFeaturePresent;

    // API Set: api-ms-win-core-handle-l1-1-0
    g_pfnCloseHandle = CloseHandle;
    g_pfnDuplicateHandle = DuplicateHandle;

    // API Set: api-ms-win-core-debug-l1-1-1
    g_pfnOutputDebugString = OutputDebugString;
    g_pfnIsDebuggerPresent = IsDebuggerPresent;

    // API Set: api-ms-win-core-com-l1-1-1
    //g_pfnCoInitializeEx = CoInitializeEx;
    //g_pfnCoUninitialize = CoUninitialize;

    // API Set: api-ms-win-core-sysinfo-l1-2-1
    g_pfnGetSystemInfo = GetNativeSystemInfo;
    g_pfnGetTickCount64 = GetTickCount64;

    // API Set: api-ms-win-core-processenvironment-l1-2-0
    g_pfnGetCurrentDirectory = GetCurrentDirectory;
    g_pfnGetCommandLine = GetCommandLine;

    // API Set: api-ms-win-core-profile-l1-1-0
    g_pfnQueryPerformanceFrequency = QueryPerformanceFrequency;
    g_pfnQueryPerformanceCounter = QueryPerformanceCounter;

    // API Set: api-ms-win-core-file-l1-2-1
    g_pfnGetFileAttributesEx = GetFileAttributesEx;
    g_pfnCreateFile2 = CreateFile2;
    g_pfnSetFilePointerEx = SetFilePointerEx;
    g_pfnReadFile = ReadFile;
    g_pfnWriteFile = WriteFile;
    g_pfnFlushFileBuffers = FlushFileBuffers;
    g_pfnCreateDirectory = CreateDirectory;
    g_pfnRemoveDirectory = RemoveDirectory;

    // API Set: api-ms-win-core-file-l2-1-1
    g_pfnCopyFile2 = CopyFile2;
    g_pfnGetFileInformationByHandleEx = GetFileInformationByHandleEx;
    g_pfnMoveFileEx = MoveFileEx;

    // API Set: api-ms-win-core-libraryloader-l1-2-0
    g_pfnGetModuleFileName = GetModuleFileName;

    // API Set: api-ms-win-core-localization-l1-2-1
    g_pfnFormatMessage = FormatMessage;

    // API Set: api-ms-win-core-heap-l1-2-0
    g_pfnGetProcessHeap = GetProcessHeap;
    g_pfnHeapFree = HeapFree;

    // API Set: api-ms-win-core-memory-l1-1-2
    g_pfnVirtualFree = VirtualFree;

    // API Set: api-ms-win-core-memory-l1-1-3
    g_pfnVirtualAllocFromApp = VirtualAllocFromApp;
}
#endif // !defined(TgBUILD_UNIVERSAL__UWP)
