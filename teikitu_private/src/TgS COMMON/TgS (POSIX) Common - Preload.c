/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (POSIX) Common - Preload.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.21 | »GUID« AEEC8393-9780-4ECA-918D-E3E11F7E2744 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if defined(TgBUILD_FEATURE__MALLOC_OVERRIDE)

#include <time.h>


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Data                                                                                                                                                                    */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TgUINT_PTR_A                                g_xuiProcess_Init = 0;




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

static TgBOOL                               s_bOS_MM_Preloading = true; // true until this module is initialized
static TgBOOL                               s_bOS_MM_Process_Initialized = false;




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Redirection Handoff                                                                                                                                                            */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgMM_OS__Preload_Process_Init -------------------------------------------------------------------------------------------------------------------------------------------- */
/* Initialize the process; called by thread_init or the process loader                                                                                                             */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgMM_OS__Preload_Process_Init( TgVOID ) TgATTRIBUTE_NO_EXCEPT
{
    TgUINT_PTR                          uiExpected = 0;

    // An explicit and strong compare and exchange to acquire the permission to run.
    if (!TgSTD_ATOMIC(compare_exchange_strong_explicit)( &g_xuiProcess_Init, &uiExpected, (uintptr_t)1, TgSTD_MEMORY_ORDER(acq_rel), TgSTD_MEMORY_ORDER(acquire) ))
    {
        return;
    };

#if defined(TgBUILD_FEATURE__MIMALLOC_ALLOCATOR)
    tgMM_MI__Internal__Process_Init();
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
#endif

    //_mi_verbose_message("process done: 0x%zx\n", _mi_heap_main.thread_id);
    s_bOS_MM_Preloading = true; // don't call the C runtime anymore
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  TgS COMMON Public Function Implementations                                                                                                                                     */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgTR_Yield --------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgTR_Yield(TgVOID)
{
#if TgCOMPILE__THREAD
    sched_yield();
#endif
}


/* ---- tgTR_Pause --------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgTR_Pause(TgVOID)
{
#if TgCOMPILE__THREAD
#if defined(TgCOMPILE__HARDWARE__PAUSE)
    tgPM__HARDWARE__PAUSE();
#else
    sched_yield();
#endif
#endif
}


/* ---- tgTR_Sleep --------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgTR_Sleep(TgUINT_E32_C uiNanoseconds)
{
#if TgCOMPILE__THREAD
    struct timespec tim, tim2;
    tim.tv_sec = 0;
    tim.tv_nsec = uiNanoseconds;

    TgVERIFY(0 == nanosleep(&tim, &tim2));
#endif
}


/* ---- tgPM_MT_SM_Signal -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPM_MT_SM_Signal( STg1_MT_SM_PCU psSM, TgUINT_E32_C nuiSignal )
{
    TgSINT_E32                          iRet;

    for (TgRSIZE uiIndex = 0; uiIndex < nuiSignal; ++uiIndex)
    {
        iRet = sem_post( psSM->m_hSemaphore );
        TgVERIFY(0 == iRet);
    };
}

/*# defined(TgBUILD_FEATURE__MALLOC_OVERRIDE) */
#endif
