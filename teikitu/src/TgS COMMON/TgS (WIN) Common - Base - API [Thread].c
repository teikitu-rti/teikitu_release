/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (WIN) Common - Base - API [Thread].c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

MSVC_WARN_DISABLE_PUSH( 4770 )
#if TgCOMPILE__THREAD

CLANG_WARN_DISABLE_PUSH(nonportable-system-include-path)
MSVC_PRAGMA(warning(push,0))
MSVC_PRAGMA(warning(disable: 4820 4668 5039))
#include <tlhelp32.h>
#include <excpt.h>
#include <processthreadsapi.h>
MSVC_PRAGMA(warning(pop))
CLANG_WARN_DISABLE_POP(nonportable-system-include-path)
CLANG_WARN_SUPPRESS(atomic-implicit-seq-cst)


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Forward Declarations                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

#if !defined(TgBUILD_UNIVERSAL__UWP)

/** @brief MSFT WIN OS function to load a dynamic library (DLL).
    @param [in] ARG0 Pointer to a string (wide) holding the filename of the library.
    @return Handle to the library loaded at ARG0. */
__declspec( dllimport ) HINSTANCE __stdcall
LoadLibraryW(
    TgCHAR_WC_CP ARG0 );

/** @brief MSFT WIN OS function to load a dynamic library (DLL).
    @param [in] ARG0 Pointer to a string (narrow) holding the filename of the library.
    @return Handle to the library loaded at ARG0. */
__declspec(dllimport) HINSTANCE __stdcall
LoadLibraryA(
    TgCHAR_NC_CP ARG0 );

/*# !defined(TgBUILD_UNIVERSAL__UWP) */
#else

/** @brief MSFT WIN OS function to load a dynamic library (DLL) in a UWP package.
    @param [in] ARG0 Pointer to a string (wide) holding the filename of the library.
    @param [in] ARG1 Integer for a reserved value.
    @return Handle to the library loaded at ARG0. */
__declspec(dllimport) HINSTANCE __stdcall
LoadPackagedLibrary(
    TgCHAR_WC_CP ARG0, TgUINT_F32 ARG1 );

/*# !defined(TgBUILD_UNIVERSAL__UWP) */
#endif

/** @brief MSFT WIN OS function to release (free) a dynamic library (DLL).
    @param [in] ARG0 Handle to a loaded dynamic library (DLL)
    @return True if the library was succesfully unloaded, and false otherwise. */
__declspec(dllimport) TgSINT_F32 __stdcall
FreeLibrary(
    HINSTANCE ARG0 );

/** @brief MSFT WIN OS function to fetch address for the function in a library .
    @param [in] ARG0 Pointer to a string holding the filename of the library.
    @param [in] ARG1 Pointer to a string (narrow) holding the function name.
    @return Handle to the library loaded at ARG0. */
__declspec(dllimport) FARPROC __stdcall
GetProcAddress(
    HINSTANCE ARG0, TgCHAR_NC_CP ARG1 );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/** @brief Set the name of the thread which can be viewed in VS IDE Debugger
    @param [IN] ARG0 Integer index into the global thread data structures. */
static TgVOID
tgTR_Thread_Set_Name(
    TgRSIZE_C ARG0 );

/** @brief This function is called by the OS on thread start, and after any needed configuration calls the intended primary function.
    @param [IN] ARG0 Pointer which is recast as an integer index in the global thread data structures.
    @return Integer as the thread exit code. */
static unsigned long __stdcall
tgTR_Thread_Start(
    void *ARG0 );

static DWORD                                s_auiTR_Thread_OS_Id[KTgMAX_THREAD_ENTRIES];

#if !TgCOMPILE__THREAD_INFO
TgEXTN TgVOID_P                             g_aTR_Thread[KTgMAX_THREAD_ENTRIES];
/*# !TgCOMPILE__THREAD_INFO */
#endif
TgVOID_P                                    g_aTR_Thread[KTgMAX_THREAD_ENTRIES];



/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgTR_Register_Main_Thread ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgTHREAD_ID tgTR_Register_Main_Thread( TgCHAR_U8_CPC szName )
{
    TgRSIZE                             uiIndex;
    TgTHREAD_ID                         tiThread;

    tgCM_UT_LF__SN__Lock_Spin( &g_sTR_Lock.m_sLock );
    for (uiIndex = 0; uiIndex < KTgMAX_THREAD_ENTRIES; ++uiIndex)
    {
        if (tgTHREAD_ID_Fetch_And_Is_Valid( nullptr, g_axtiTR_Thread_Singleton + uiIndex ))
        {
            continue;
        };

        atomic_store( &g_auiTR_Thread_Stack[uiIndex], tgTR_Stack_Size() );
        g_afnTR_Thread_Function[uiIndex] = nullptr;
        g_auiTR_Thread_Param[uiIndex] = 0;
        g_aenTR_Thread_Priority[uiIndex] = ETgTHREAD_PRIORITY__NORMAL;
        g_pfnDuplicateHandle( g_pfnGetCurrentProcess(), g_pfnGetCurrentThread(), g_pfnGetCurrentProcess(), &(g_aTR_Thread[0]), 0, 0, 0x2 );

    #if TgCOMPILE__THREAD_INFO
        g_aszTR_Name[uiIndex] = szName;
    #endif

        g_aTR_Thread[uiIndex] = nullptr;
        s_auiTR_Thread_OS_Id[uiIndex] = g_pfnGetCurrentThreadId();

        tiThread = tgTHREAD_ID_Init(g_axtiTR_Thread_Singleton + uiIndex, (TgUINT_F32)uiIndex);
        tls_tiThread_Local = tiThread;

        tgTR_Thread_Set_Name( uiIndex );

        tgCM_UT_LF__SN__Signal( &g_sTR_Lock.m_sLock );
        return (tiThread);
    };
    tgCM_UT_LF__SN__Signal( &g_sTR_Lock.m_sLock );
    return (KTgTHREAD_ID__INVALID);
}


/* ---- tgTR_Create -------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgTHREAD_ID tgTR_Create( TgPLATFORM_THREAD_FCN pfnThread, TgUINT_PTR_C uiParam, TgUINT_F32_C uiStack, ETgTHREAD_PRIORITY_C enPriority, TgCHAR_U8_CPC szName )
{
    TgRSIZE                             uiIndex;
    TgTHREAD_ID                         tiThread;

    if (0 == pfnThread)
    {
        return (KTgTHREAD_ID__INVALID);
    }

    tgCM_UT_LF__SN__Lock_Spin( &g_sTR_Lock.m_sLock ); /* NOTE: This is done under a lock */
    for (uiIndex = 0; uiIndex < KTgMAX_THREAD_ENTRIES; ++uiIndex)
    {
        if (tgTHREAD_ID_Fetch_And_Is_Valid( nullptr, g_axtiTR_Thread_Singleton + uiIndex ))
        {
            continue;
        };

        atomic_store( &g_auiTR_Thread_Stack[uiIndex], KTgMAX_RSIZE-1 );
        g_afnTR_Thread_Function[uiIndex] = pfnThread;
        g_auiTR_Thread_Param[uiIndex] = uiParam;
        g_aenTR_Thread_Priority[uiIndex] = enPriority;

    #if TgCOMPILE__THREAD_INFO
        g_aszTR_Name[uiIndex] = szName;
    #endif

        tiThread = tgTHREAD_ID_Init( g_axtiTR_Thread_Singleton + uiIndex, (TgUINT_F32)uiIndex );
        g_aTR_Thread[uiIndex] = (TgVOID_P)g_pfnCreateThread( 0, uiStack, tgTR_Thread_Start, (TgVOID_P)(TgSINT_PTR)uiIndex, 0, s_auiTR_Thread_OS_Id + uiIndex );

        tgCM_UT_LF__SN__Signal( &g_sTR_Lock.m_sLock );
        return (tiThread);
    };
    tgCM_UT_LF__SN__Signal( &g_sTR_Lock.m_sLock );
    return (KTgTHREAD_ID__INVALID);
}


/* ---- tgTR_Query_Id ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgTHREAD_ID tgTR_Query_Id( TgVOID )
{
#if !defined(TGS_FINAL) ||  !TgCOMPILE__THREAD_LOCAL
    TgUINT_F32                          uiThread_Id;
    TgRSIZE                             uiIndex;

    tgCM_UT_LF__SN__Lock_Spin( &g_sTR_Lock.m_sLock );

    uiThread_Id = g_pfnGetCurrentThreadId();
    for (uiIndex = 0; uiIndex < KTgMAX_THREAD_ENTRIES; ++uiIndex)
    {
        if (uiThread_Id == s_auiTR_Thread_OS_Id[uiIndex])
        {
            tgCM_UT_LF__SN__Signal( &g_sTR_Lock.m_sLock );
            TgERROR(tls_tiThread_Local.m_uiI == uiIndex);
            return (tgTHREAD_ID_Query_Unsafe(g_axtiTR_Thread_Singleton + uiIndex));
        };
    };

    tgCM_UT_LF__SN__Signal( &g_sTR_Lock.m_sLock );
    TgCRITICAL_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Thread not found in thread pool!" );
    return (KTgTHREAD_ID__INVALID);
/*# !defined(TGS_FINAL) ||  !TgCOMPILE__THREAD_LOCAL */
#else
    return (tgTHREAD_ID_Query_Unsafe(g_axtiTR_Thread_Singleton + tls_tiThread_Local.m_uiI));
/*# !defined(TGS_FINAL) ||  !TgCOMPILE__THREAD_LOCAL */
#endif
}


/* ---- tgTR_Close --------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgTR_Close( TgTHREAD_ID_C tiThread )
{
    TgVOID_P                            hThread;

    TgPARAM_CHECK((tiThread.m_uiKI != KTgID__INVALID_VALUE) && (tiThread.m_uiI < KTgMAX_THREAD_ENTRIES));

    /* Get the os handle */
    tgCM_UT_LF__SN__Lock_Spin( &g_sTR_Lock.m_sLock );
    TgERROR(0 != g_afnTR_Thread_Function[tiThread.m_uiI]);
    hThread = g_aTR_Thread[tiThread.m_uiI];
    tgCM_UT_LF__SN__Signal( &g_sTR_Lock.m_sLock );

    while (0UL != g_pfnWaitForSingleObjectEx( (TgVOID_P)hThread, 0xFFFFFFFF, true )) {}; /* Wait for thread to close */
    TgVERIFY( 0 != g_pfnCloseHandle( (TgVOID_P)hThread ) ); /* Close the handle */

    /* Mark the thread slot as available */
    tgCM_UT_LF__SN__Lock_Spin( &g_sTR_Lock.m_sLock );
    g_afnTR_Thread_Function[tiThread.m_uiI] = 0;
    g_aTR_Thread[tiThread.m_uiI] = 0;
    atomic_store( &g_auiTR_Thread_Stack[tiThread.m_uiI], KTgMAX_RSIZE );
    tgTHREAD_ID_Invalidate( g_axtiTR_Thread_Singleton + tiThread.m_uiI );
    tgCM_UT_LF__SN__Signal( &g_sTR_Lock.m_sLock );
}


/* ---- tgTR_Status -------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
ETgTHREAD_STATUS tgTR_Status( TgTHREAD_ID tiThread )
{
    TgPARAM_CHECK((tiThread.m_uiKI != KTgID__INVALID_VALUE) && (tiThread.m_uiI < KTgMAX_THREAD_ENTRIES));

    if (tiThread.m_uiKI == KTgID__INVALID_VALUE || tiThread.m_uiI >= KTgMAX_THREAD_ENTRIES)
    {
        return (ETgTHREAD_STATUS__INVALID);
    }
    else
    {
        if (!tgTHREAD_ID_Is_Equal( g_axtiTR_Thread_Singleton + tiThread.m_uiI, tiThread ))
        {
            return (ETgTHREAD_STATUS__INVALID);
        }
        else
        {
            TgRSIZE                             uiStack;

            uiStack = atomic_load( &g_auiTR_Thread_Stack[tiThread.m_uiI] );
            if (KTgMAX_RSIZE == uiStack)
            {
                TgCRITICAL_MSG( false, u8"THREAD: Invalid state. There is a valid thread id with an invalid stack memory count." );
                return (ETgTHREAD_STATUS__INVALID);
            }
            else if (KTgMAX_RSIZE-1 == uiStack)
            {
                return (ETgTHREAD_STATUS__INIT);
            }
            else
            {
                return (ETgTHREAD_STATUS__EXEC);
            };
        };
    };
}


/* ---- tgTR_Stack_Size ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRSIZE tgTR_Stack_Size( TgVOID )
{
    typedef struct 
    {
        TgVOID_P                            DoNotUse00;
        TgVOID_P                            StackBase;
        TgVOID_P                            StackLimit;
        TgVOID_P                            DoNotUse01;
        TgVOID_P                            DoNotUse02;
        TgVOID_P                            DoNotUse03;
        TgVOID_P                            Self;
    } WinThreadStruct;
    WinThreadStruct                     *pTEB;

    pTEB = (WinThreadStruct*)(TgUINT_PTR)__readgsqword( 48 );

    return ((TgUINT_F32)((TgUINT_E08_P)(pTEB->StackBase) - (TgUINT_E08_P)(pTEB->StackLimit)));
}


/* ---- tgTR_Print_Threads ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgTR_Print_Threads( STg2_Output_P pOutput )
{
#if !defined(TgBUILD_UNIVERSAL__UWP)
    THREADENTRY32                       te32;
    TgVOID_P                            hThreadSnap;
    TgUINT_F32                          uiOwnerPID;
    TgBOOL                              bPrint_Header = true;

    hThreadSnap = (TgVOID_P)~((TgUINT_PTR)0);
    uiOwnerPID = g_pfnGetCurrentProcessId();

    /* Take a snapshot of all running threads */
    hThreadSnap = g_pfnCreateToolhelp32Snapshot( 0x00000004, 0 );
    if (hThreadSnap == (TgVOID_P)~((TgUINT_PTR)0))
        return;

    /* Fill in the size of the structure before using it. */
    te32.dwSize = sizeof( te32 );

    /* Retrieve information about the first thread, and exit if unsuccessful */
    if (!g_pfnThread32First( hThreadSnap, &te32 ))
    {
        g_pfnCloseHandle( hThreadSnap );
        return;
    }

#if TgCOMPILE__THREAD_INFO
    tgCM_UT_LF__SN__Lock_Spin( &g_sTR_Lock.m_sLock );
#endif
    tgIO_PrintF( pOutput, u8"\n" );
    do
    {
        if (te32.th32OwnerProcessID == uiOwnerPID)
        {
#if TgCOMPILE__THREAD_INFO
            TgSINT_F32                          iIndex = 0;

            for (iIndex = 0; iIndex < KTgMAX_THREAD_ENTRIES; ++iIndex)
            {
                if (te32.th32ThreadID == s_auiTR_Thread_OS_Id[iIndex])
                {
                    break;
                };
            };

            if (bPrint_Header)
            {
                tgIO_PrintF( pOutput, u8"| %10.10s | %10.10s | %32.32s\n", u8"Thread Id", u8"Stack", u8"Name" );
                bPrint_Header = false;
            };

            if (iIndex >= KTgMAX_THREAD_ENTRIES)
            {
                tgIO_PrintF( pOutput, u8"| 0x%08X | %10.10s | %32.32s\n", te32.th32ThreadID, u8"", u8"" );
            }
            else
            {
                TgRSIZE                             uiStack;

                uiStack = atomic_load(&g_auiTR_Thread_Stack[iIndex]);
                tgIO_PrintF( pOutput, u8"| 0x%08X | % 10d | %32.32s\n", te32.th32ThreadID, uiStack, g_aszTR_Name[iIndex] );
            };
#else
            if (bPrint_Header)
            {
                tgIO_PrintF( pOutput, u8"\n% 25.25s: %10.10s\n", u8"Thread", u8"ID" );
                bPrint_Header = false;
            };
            tgIO_PrintF( pOutput, u8"% 25.25s: 0x%08X\n", u8"Thread", te32.th32ThreadID );
#endif
        }
    } while (g_pfnThread32Next( hThreadSnap, &te32 ));
    tgIO_PrintF( pOutput, u8"\n" );
#if TgCOMPILE__THREAD_INFO
    tgCM_UT_LF__SN__Signal( &g_sTR_Lock.m_sLock );
#endif

    /*  Don't forget to clean up the snapshot object. */
    g_pfnCloseHandle( hThreadSnap );

/*# !defined(TgBUILD_UNIVERSAL__UWP) */
#endif
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
TgVOID tgTR_Sleep(TgUINT_F32_C uiNanoseconds)
{
    g_pfnSleep( uiNanoseconds / 1000000 );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgTR_Thread_Set_Name ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgTR_Thread_Set_Name( TgRSIZE_C iIndex )
{
    TgCHAR_WC                       wszNameAnsi[1024];

    g_pfnSleep(10);
    TgERROR((TgUINT_F32)s_auiTR_Thread_OS_Id[iIndex] == g_pfnGetCurrentThreadId()); /* OS race condition for the win - sometimes not flushed */

#if TgCOMPILE__THREAD_INFO
    tgWSZ_Convert_USZ( wszNameAnsi, TgARRAY_COUNT( wszNameAnsi ), g_aszTR_Name[iIndex], tgUSZ_Length_U08( g_aszTR_Name[iIndex], KTgMAX_RSIZE ) + 1 );
/*# TgCOMPILE__THREAD_INFO */
#endif
    SetThreadDescription( GetCurrentThread(), wszNameAnsi );
}


/* ---- tgTR_Thread_Start -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static unsigned long __stdcall tgTR_Thread_Start( void* pParam )
{
    TgUN_SCALAR                         sParam;
    TgVOID_P                            hThread;
    TgUINT_F32                          uiRet = 1;

    sParam.m_pPTR = pParam;
    TgERROR(sParam.m_uiPTR <= KTgMAX_S32);

#if TgCOMPILE__THREAD_LOCAL
    tls_tiThread_Local = tgTHREAD_ID_Query_Unsafe( g_axtiTR_Thread_Singleton + sParam.m_uiPTR );
#endif

    atomic_store( &g_auiTR_Thread_Stack[sParam.m_uiE32], tgTR_Stack_Size() );
    atomic_thread_fence( cxx__memory_order_seq_cst );

    tgTR_Thread_Set_Name( sParam.m_uiPTR );
    hThread = g_pfnGetCurrentThread();

    switch (g_aenTR_Thread_Priority[sParam.m_uiPTR])
    {
        case ETgTHREAD_PRIORITY__CRITICAL:
            TgVERIFY( 0 != g_pfnSetThreadPriority( hThread, 15 ) );
            break;
        case ETgTHREAD_PRIORITY__HIGHEST:
            TgVERIFY( 0 != g_pfnSetThreadPriority( hThread, 2 ) );
            break;
        case ETgTHREAD_PRIORITY__HIGH:
            TgVERIFY( 0 != g_pfnSetThreadPriority( hThread, 1 ) );
            break;
        case ETgTHREAD_PRIORITY__NORMAL:
            TgVERIFY( 0 != g_pfnSetThreadPriority( hThread, 0 ) );
            break;
        case ETgTHREAD_PRIORITY__LOW:
            TgVERIFY( 0 != g_pfnSetThreadPriority( hThread, -1 ) );
            break;
        case ETgTHREAD_PRIORITY__LOWEST:
            TgVERIFY( 0 != g_pfnSetThreadPriority( hThread, -2 ) );
            break;
        case ETgTHREAD_PRIORITY__UNKNOWN:
        default:
            TgS_NO_DEFAULT(break);
    };

    uiRet = g_afnTR_Thread_Function[sParam.m_uiPTR]( g_auiTR_Thread_Param[sParam.m_uiPTR] );

    tgMM_Clear_Thread_Local_Cache();
    tgTHREAD_ID_Invalidate( g_axtiTR_Thread_Singleton + sParam.m_uiPTR );
    g_pfnExitThread( uiRet );
    return (uiRet);
}


/*# TgCOMPILE__THREAD */
#endif

MSVC_WARN_DISABLE_POP( 4770 )
