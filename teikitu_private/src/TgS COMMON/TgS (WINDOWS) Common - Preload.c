/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (WINDOWS) Common - Preload.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.21 | »GUID« AEEC8393-9780-4ECA-918D-E3E11F7E2744 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if defined (MK_BUILD__SHARED_LIBRARY)

/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Data                                                                                                                                                                    */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/*  API Set: api-ms-win-core-sysinfo-l1-1-0 */
TgEXTN TgVOID                               (__stdcall *g_pfnGetSystemInfo)( LPSYSTEM_INFO );
TgVOID                                      (__stdcall *g_pfnGetSystemInfo)( LPSYSTEM_INFO ) = nullptr;

typedef TgVOID (__stdcall *PGetSystemInfo)( LPSYSTEM_INFO );

/* API Set: api-ms-win-core-memory-l1-1-2 */
TgEXTN TgVOID_P                             (__stdcall *g_pfnVirtualAlloc)( TgVOID_P, TgUINT_E64, DWORD, DWORD );
TgEXTN TgSINT_E32                           (__stdcall *g_pfnVirtualFree)( TgVOID_P, TgUINT_E64, DWORD );
TgVOID_P                                    (__stdcall *g_pfnVirtualAlloc)( TgVOID_P, TgUINT_E64 , DWORD, DWORD ) = nullptr;
TgSINT_E32                                  (__stdcall *g_pfnVirtualFree)( TgVOID_P, TgUINT_E64 , DWORD ) = nullptr;

/* API Set: api-ms-win-core-synch-l1-2-0 */
TgVOID_P                                    (__stdcall *g_pfnCreateSemaphoreEx)( LPSECURITY_ATTRIBUTES, LONG, LONG, TgOSCHAR_CP, DWORD, DWORD )=nullptr;
TgSINT_E32                                  (__stdcall *g_pfnReleaseSemaphore)( TgVOID_P, LONG, LPLONG ) = nullptr;
TgVOID                                      (__stdcall *g_pfnSleep)( DWORD ) = nullptr;

/* API Set: api-ms-win-core-processthreads-l1-1-2 */
TgSINT_E32                                  (__stdcall *g_pfnSwitchToThread)( TgVOID ) = nullptr;

TgUINT_PTR_A                                g_xuiProcess_Init = 0;




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Types                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

typedef PVOID (__stdcall *PVirtualAlloc)( TgVOID_P, TgUINT_E64 , DWORD, DWORD );
typedef TgSINT_E32 (__stdcall *PVirtualFree)( TgVOID_P, TgUINT_E64 , DWORD );

typedef TgVOID_P (__stdcall *PCreateSemaphoreEx)( LPSECURITY_ATTRIBUTES, LONG, LONG, TgOSCHAR_CP, DWORD, DWORD );
typedef TgSINT_E32 (__stdcall *PReleaseSemaphore)( TgVOID_P, LONG, LPLONG );
typedef TgVOID (__stdcall *PSleep)( DWORD );

typedef TgSINT_E32 (__stdcall *PSwitchToThread)( TgVOID );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

static TgRESULT
tgMM_OS__Preload_Process_Load( TgVOID );

static TgBOOL                               s_bOS_MM_Preloading = true; // true until this module is initialized
static TgBOOL                               s_bOS_MM_Process_Initialized = false;




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Redirection Handoff                                                                                                                                                            */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

// Communicate with the redirection module on Windows
#if defined(TgBUILD_FEATURE__MIMALLOC_ALLOCATOR)
TgCLANG_WARN_DISABLE_PUSH(reserved-identifier)

TgEXTN TgDLL_EXPORT TgBOOL _mi_is_redirected(void);
TgBOOL _mi_is_redirected(void) {
    return g_bOS_MM_Redirected;
}

TgEXTN TgDLL_EXPORT TgVOID _mi_redirect_entry(unsigned long uiReason);
TgVOID _mi_redirect_entry(unsigned long uiReason)
{
    // called on redirection; careful as this may be called before DllMain
    if (uiReason == 1)
    {
        g_bOS_MM_Redirected = true;
    }
    else if (uiReason == 0)
    {
        g_bOS_MM_Redirected = false;
    }
    else if (uiReason == 3)
    {
        tgMM_Free_Thread_Local();
    }
}
TgCLANG_WARN_DISABLE_POP()

TgEXTN TgDLL_IMPORT TgBOOL CDECL mi_allocator_init(const char** message);
TgEXTN TgDLL_IMPORT TgVOID CDECL mi_allocator_done(void);

/*# defined(TgBUILD_FEATURE__MIMALLOC_ALLOCATOR) */
#endif




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- DLL Main / Preload Init -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* Based on: https://github.com/microsoft/mimalloc/blob/master/src/init.c */

TgEXTN TgDLL_EXPORT int __stdcall DllMain( TgATTRIBUTE_UNUSED void* hinstDLL, unsigned long fdwReason, void* lpvReserved );
int __stdcall DllMain(
    TgATTRIBUTE_UNUSED void* hinstDLL, // handle to DLL module
    unsigned long fdwReason, // reason for calling function
    void* lpvReserved ) // reserved
{
    // Perform actions based on the reason for calling.
    switch( fdwReason ) 
    { 
        case 1: /* DLL_PROCESS_ATTACH Initialize once for each new process. Return FALSE to fail DLL load. */
            if (TgFAILED(tgMM_OS__Preload_Process_Load()))
            {
                return false;
            }
            break;

        case 2: /* DLL_THREAD_ATTACH Do thread-specific initialization. */
            break;

        case 3: /* DLL_THREAD_DETACH Do thread-specific cleanup. */
            if (!tgMM_OS__Preload_Malloc_Redirected())
            {
                tgMM_Free_Thread_Local();
            }
            break;

        case 0: /* DLL_PROCESS_DETACH */
        
            if (lpvReserved != nullptr)
            {
                break; // do not do cleanup if process termination scenario
            }
            
            tgMM_OS__Preload_Process_Done();

            // Perform any necessary cleanup.
            break;
    }
    return true;  // Successful DLL_PROCESS_ATTACH.
}


/* ---- tgMM_OS__Preload_Process_Init -------------------------------------------------------------------------------------------------------------------------------------------- */
/* Initialize the process; called by thread_init or the process loader                                                                                                             */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgMM_OS__Preload_Process_Init( TgVOID ) TgATTRIBUTE_NO_EXCEPT
{
    HINSTANCE                           hDLL_Core_Mem1 = nullptr;
    HINSTANCE                           hDLL_Core_SysInfo = nullptr;
    HINSTANCE                           hDLL_Core_Sync1 = nullptr;
    HINSTANCE                           hDLL_Core_Sync2 = nullptr;
    HINSTANCE                           hDLL_Core_ProcessThread = nullptr;
    union
    {
        PVirtualAlloc                       pAlloc;
        PVirtualFree                        pFree;
        PGetSystemInfo                      pGetSystemInfo;
        PCreateSemaphoreEx                  pfnCreateSemaphoreEx;
        PReleaseSemaphore                   pfnReleaseSemaphore;
        PSleep                              pfnSleep;
        PSwitchToThread                     pfnSwitchToThread;
        FARPROC                             pProc;
    }                                   uCast;
    SYSTEM_INFO                         siSystemInfo;

    TgUINT_PTR                          uiExpected = 0;

    // An explicit and strong compare and exchange to acquire the permission to run.
    if (!TgSTD_ATOMIC(compare_exchange_strong_explicit)( &g_xuiProcess_Init, &uiExpected, (uintptr_t)1, TgSTD_MEMORY_ORDER(acq_rel), TgSTD_MEMORY_ORDER(acquire) ))
    {
        return;
    };

    /* API Set: api-ms-win-core-memory-l1-1-0 */
    hDLL_Core_Mem1 = LoadLibrary( TgOS_TEXT("api-ms-win-core-memory-l1-1-0") );
    if (!hDLL_Core_Mem1)
    {
        return;
    };

    uCast.pProc = GetProcAddress( hDLL_Core_Mem1, ("VirtualAlloc") );
    if (nullptr == uCast.pProc)
    {
        FreeLibrary( hDLL_Core_Mem1 );
        return;
    }
    g_pfnVirtualAlloc = uCast.pAlloc;

    uCast.pProc = GetProcAddress( hDLL_Core_Mem1, ("VirtualFree") );
    if (nullptr == uCast.pProc)
    {
        FreeLibrary( hDLL_Core_Mem1 );
        return;
    }
    g_pfnVirtualFree = uCast.pFree;

    FreeLibrary( hDLL_Core_Mem1 );

    /* API Set: api-ms-win-core-sysinfo-l1-1-0 */
    hDLL_Core_SysInfo = LoadLibrary( TgOS_TEXT("api-ms-win-core-sysinfo-l1-1-0") );
    if (!hDLL_Core_SysInfo)
    {
        return;
    };

    uCast.pProc = GetProcAddress( hDLL_Core_SysInfo, ("GetNativeSystemInfo") );
    if (nullptr == uCast.pProc)
    {
        FreeLibrary( hDLL_Core_SysInfo );
        return;
    }
    g_pfnGetSystemInfo = uCast.pGetSystemInfo;

    FreeLibrary( hDLL_Core_SysInfo );

    g_pfnGetSystemInfo( &siSystemInfo );

    g_uiOS_MM_Page_Size = siSystemInfo.dwPageSize;

#if !defined(TgCOMPILE_WIDE_CHAR)
    /* API Set: api-ms-win-core-synch-l1-2-0 */
    hDLL_Core_Sync1 = LoadLibrary( TgOS_TEXT("api-ms-win-core-synch-ansi-l1-1-0") );
    if (!hDLL_Core_Sync1)
    {
        return;
    };

    uCast.pProc = GetProcAddress( hDLL_Core_Sync1, ("CreateSemaphoreExA") );
    if (nullptr == uCast.pProc)
    {
        FreeLibrary( hDLL_Core_Sync1 );
        return;
    }
    g_pfnCreateSemaphoreEx = uCast.pfnCreateSemaphoreEx;

    FreeLibrary( hDLL_Core_Sync1 );
#else
    (void)hDLL_Core_Sync1;
/*# !defined(TgCOMPILE_WIDE_CHAR) */
#endif

    /* API Set: api-ms-win-core-synch-l1-2-0 */
    hDLL_Core_Sync2 = LoadLibrary( TgOS_TEXT("api-ms-win-core-synch-l1-2-0") );
    if (!hDLL_Core_Sync2)
    {
        return;
    };

    uCast.pProc = GetProcAddress( hDLL_Core_Sync2, ("ReleaseSemaphore") );
    if (nullptr == uCast.pProc)
    {
        FreeLibrary( hDLL_Core_Sync2 );
        return;
    }
    g_pfnReleaseSemaphore = uCast.pfnReleaseSemaphore;

    uCast.pProc = GetProcAddress( hDLL_Core_Sync2, ("Sleep") );
    if (nullptr == uCast.pProc)
    {
        FreeLibrary( hDLL_Core_Sync2 );
        return;
    }
    g_pfnSleep = uCast.pfnSleep;

#if defined(TgCOMPILE_WIDE_CHAR)
    uCast.pProc = GetProcAddress( hDLL_Core_Sync2, TgOS_TEXT("CreateSemaphoreExW") );
    if (nullptr == uCast.pProc)
    {
        FreeLibrary( hDLL_Core_Sync2 );
        return;
    }
    g_pfnCreateSemaphoreEx = uCast.pfnCreateSemaphoreEx;
#endif

    FreeLibrary( hDLL_Core_Sync2 );

    /* API Set: api-ms-win-core-processthreads-l1-1-2 */
    hDLL_Core_ProcessThread = LoadLibrary( TgOS_TEXT("api-ms-win-core-processthreads-l1-1-2") );
    if (!hDLL_Core_ProcessThread)
    {
        return;
    };

    uCast.pProc = GetProcAddress( hDLL_Core_ProcessThread, ("SwitchToThread") );
    if (nullptr == uCast.pProc)
    {
        FreeLibrary( hDLL_Core_ProcessThread );
        return;
    }
    g_pfnSwitchToThread = uCast.pfnSwitchToThread;

    FreeLibrary( hDLL_Core_ProcessThread );

#if defined(TgBUILD_FEATURE__MIMALLOC_ALLOCATOR)
    tgMM_MI__Internal__Process_Init();
/*# defined(TgBUILD_FEATURE__MIMALLOC_ALLOCATOR) */
#endif

    tgMM_Init_MGR();

    s_bOS_MM_Process_Initialized = true;

    TgSTD_ATOMIC(store_explicit)( &g_xuiProcess_Init, (uintptr_t)2, TgSTD_MEMORY_ORDER(seq_cst) );
}


/* ---- tgMM_OS__Preload_Process_Done -------------------------------------------------------------------------------------------------------------------------------------------- */
/* Called when the process is done (through `at_exit`)                                                                                                                             */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
 TgVOID CDECL tgMM_OS__Preload_Process_Done( TgVOID ) TgATTRIBUTE_NO_EXCEPT
{
    // only shutdown if we were initialized
    if (!s_bOS_MM_Process_Initialized) return;

    // ensure we are called once
    static bool process_done = false;
    if (process_done) return;
    process_done = true;

    /* Close the memory manager, free all allocated memory. */
    tgMM_Free_MGR();

#if defined(TgBUILD_FEATURE__MIMALLOC_ALLOCATOR)
    tgMM_MI__Internal__Process_Done();
/*# defined(TgBUILD_FEATURE__MIMALLOC_ALLOCATOR) */
#endif

    //_mi_verbose_message("process done: 0x%zx\n", _mi_heap_main.thread_id);
    s_bOS_MM_Preloading = true; // don't call the C runtime anymore
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgMM_OS__Preload_Process_Load -------------------------------------------------------------------------------------------------------------------------------------------- */
/* Called once by the process loader                                                                                                                                               */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT tgMM_OS__Preload_Process_Load( TgVOID )
{
    s_bOS_MM_Preloading = false;

    tgMM_OS__Preload_Process_Init();

#if defined(TgBUILD_FEATURE__MIMALLOC_ALLOCATOR)
    /* Force the redirector dll into the import module list for the DLL / EXE. */
    const char* msg = nullptr;
    mi_allocator_init(&msg);
    tgMM_MI__Internal__Process_Load();
/*# defined(TgBUILD_FEATURE__MIMALLOC_ALLOCATOR) */
#endif

    return KTgS_OK;
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  TgS COMMON Public Function Implementations                                                                                                                                     */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgSI_SYSTEM_Page_Size ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgUINT_E32 tgSI_SYSTEM_Page_Size( TgVOID )
{
    return (g_uiOS_MM_Page_Size);
}


/* ---- tgTR_Yield --------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgTR_Yield(TgVOID)
{
    g_pfnSwitchToThread();
}


/* ---- tgTR_Pause --------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgTR_Pause(TgVOID)
{
    g_pfnSleep( 0 );
}


/* ---- tgTR_Sleep --------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgTR_Sleep(TgUINT_E32_C uiNanoseconds)
{
    g_pfnSleep( uiNanoseconds / 1000000 );
}


/* ---- tgPM_MT_SM_Signal -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPM_MT_SM_Signal( STg1_MT_SM_PCU psSM, TgUINT_E32_C nuiSignal )
{
    g_pfnReleaseSemaphore( psSM->m_hSemaphore, (LONG)nuiSignal, nullptr );
}


/*# defined (MK_BUILD__SHARED_LIBRARY) */
#endif
