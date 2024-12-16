/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (POSIX) Common - Base - API [Thread].c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "TgS COMMON/TgS Common -- BASE.h"
#include "TgS COMMON/TgS Common -- UTIL.h"
#include "TgS COMMON/TgS Common -- UTIL.inl"


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#if TgCOMPILE__THREAD
static TgVOID_P                             tgTR_Thread_Start(TgVOID_P);

pthread_t                                   g_aTR_Thread[KTgMAX_THREAD_ENTRIES];

/*# TgCOMPILE__THREAD */
#endif




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#if TgCOMPILE__THREAD

/* ---- tgTR_Register_Main_Thread ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgTHREAD_ID tgTR_Register_Main_Thread( TgCHAR_U8_CPC szName )
{
    TgRSIZE                             uiIndex;
    TgTHREAD_ID                         tiThread;

    tgCM_UT_LF__SN__Lock_Spin( &g_sTR_Lock.m_sLock );
    for (uiIndex = 0; uiIndex < KTgMAX_THREAD_ENTRIES; ++uiIndex)
    {
        if (tgTHREAD_ID_Fetch_And_Is_Valid( nullptr, g_atiTR_Thread_Singleton + uiIndex ))
        {
            continue;
        };

        atomic_store( &g_auiTR_Thread_Stack[uiIndex], tgTR_Stack_Size() );
        g_afnTR_Thread_Function[uiIndex] = nullptr;
        g_auiTR_Thread_Param[uiIndex] = 0;
        g_aenTR_Thread_Priority[uiIndex] = ETgTHREAD_PRIORITY__NORMAL;
        g_aTR_Thread[uiIndex] = pthread_self();

    #if TgCOMPILE__THREAD_INFO
        g_aszTR_Name[uiIndex] = szName;
    #endif

        tiThread = tgTHREAD_ID_Init( g_atiTR_Thread_Singleton + uiIndex, (TgUINT_F32)uiIndex );
        tls_tiThread_Local = tiThread;

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
    TgSINT_F32                          iRet;
    pthread_attr_t                      sAttrib;
    TgRSIZE                             uiCurrentStack;
    TgTHREAD_ID                         tiThread;
    TgUN_SCALAR                         sParam;

    if (0 == pfnThread)
    {
        return (KTgTHREAD_ID__INVALID);
    }

    tgCM_UT_LF__SN__Lock_Spin( &g_sTR_Lock.m_sLock ); /* NOTE: This is done under a lock */
    for (uiIndex = 0; uiIndex < KTgMAX_THREAD_ENTRIES; ++uiIndex)
    {
        if (tgTHREAD_ID_Fetch_And_Is_Valid( nullptr, g_atiTR_Thread_Singleton + uiIndex ))
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

        tiThread = tgTHREAD_ID_Init( g_atiTR_Thread_Singleton + uiIndex, (TgUINT_F32)uiIndex );

        iRet = pthread_attr_init( &sAttrib );
        TgCRITICAL(0 <= iRet);
        iRet = pthread_attr_getstacksize( &sAttrib, &uiCurrentStack );
        TgCRITICAL(0 <= iRet);
        if (uiCurrentStack < uiStack)
        {
            TgVERIFY(0 <= pthread_attr_setstacksize( &sAttrib, uiStack ));
        }
        sParam.m_uiPTR = uiIndex;
        iRet = pthread_create( g_aTR_Thread + uiIndex, nullptr, tgTR_Thread_Start, sParam.m_pPTR );
        TgCRITICAL(0 <= iRet);
        iRet = pthread_attr_destroy( &sAttrib );
        TgCRITICAL(0 <= iRet);

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
#if !defined(TGS_FINAL) || !TgCOMPILE__THREAD_LOCAL
    pthread_t                           sThread;
    TgRSIZE                             uiIndex;

    tgCM_UT_LF__SN__Lock_Spin( &g_sTR_Lock.m_sLock );

    sThread = pthread_self();
    for (uiIndex = 0; uiIndex < KTgMAX_THREAD_ENTRIES; ++uiIndex)
    {
        if (sThread == g_aTR_Thread[uiIndex])
        {
            tgCM_UT_LF__SN__Signal( &g_sTR_Lock.m_sLock );
            TgERROR(tls_tiThread_Local.m_uiI == uiIndex);
            return (tgTHREAD_ID_Query_Unsafe(g_atiTR_Thread_Singleton + uiIndex));
        };
    };

    tgCM_UT_LF__SN__Signal( &g_sTR_Lock.m_sLock );
    TgCRITICAL_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Thread not found in thread pool!" );
    return (KTgTHREAD_ID__INVALID);
/*# !defined(TGS_FINAL) ||  !TgCOMPILE__THREAD_LOCAL */
#else
    return (tgTHREAD_ID_Query_Unsafe(g_atiTR_Thread_Singleton + tls_tiThread_Local.m_uiI));
/*# !defined(TGS_FINAL) ||  !TgCOMPILE__THREAD_LOCAL */
#endif
}


/* ---- tgTR_Close --------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgTR_Close( TgTHREAD_ID tiThread )
{
    pthread_t                           sThreadOS;
    TgSINT_F32                          iRet;

    TgPARAM_CHECK((tiThread.m_uiKI != KTgID__INVALID_VALUE) && (tiThread.m_uiI < KTgMAX_THREAD_ENTRIES));

    /* Get the os handle */
    tgCM_UT_LF__SN__Lock_Spin( &g_sTR_Lock.m_sLock );

    TgERROR(0 != g_afnTR_Thread_Function[tiThread.m_uiI]);
    sThreadOS = g_aTR_Thread[tiThread.m_uiI];
    tgCM_UT_LF__SN__Signal( &g_sTR_Lock.m_sLock );

    iRet = pthread_join( sThreadOS, nullptr );
    TgVERIFY(0 <= iRet);

    /* Mark the thread slot as available */
    tgCM_UT_LF__SN__Lock_Spin( &g_sTR_Lock.m_sLock );
    g_afnTR_Thread_Function[tiThread.m_uiI] = 0;
    g_aTR_Thread[tiThread.m_uiI] = 0;
    atomic_store( &g_auiTR_Thread_Stack[tiThread.m_uiI], KTgMAX_RSIZE );
    tgTHREAD_ID_Invalidate( g_atiTR_Thread_Singleton + tiThread.m_uiI );
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
        if (!tgTHREAD_ID_Is_Equal( g_atiTR_Thread_Singleton + tiThread.m_uiI, tiThread ))
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
    size_t                              uiStackSize;
    pthread_attr_t                      sAttr;
    
    pthread_attr_getstacksize(&sAttr, &uiStackSize);
    return (uiStackSize);
}


/*# TgCOMPILE__THREAD */
#endif


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
TgVOID tgTR_Sleep(TgUINT_F32_C uiNanoseconds)
{
#if TgCOMPILE__THREAD
    struct timespec tim, tim2;
    tim.tv_sec = 0;
    tim.tv_nsec = uiNanoseconds;

    TgVERIFY(0 == nanosleep(&tim, &tim2));
#endif
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgTR_Thread_Start -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if TgCOMPILE__THREAD
static TgVOID_P tgTR_Thread_Start( TgVOID_P pParam )
{
    TgUN_SCALAR                         sParam;
    TgUINT_F32                          uiRet = 1;
    pthread_attr_t                      sAttrib;
    TgSINT_F32                          iRet;
    TgSIZE_ALL                          uiCurrentStack;
    
    iRet = pthread_attr_getstacksize( &sAttrib, &uiCurrentStack );
    TgCRITICAL(0 <= iRet);

    sParam.m_pPTR = pParam;
    TgERROR(sParam.m_uiPTR <= KTgMAX_S32);
 
#if TgCOMPILE__THREAD_LOCAL
    tls_tiThread_Local = tgTHREAD_ID_Query_Unsafe( g_atiTR_Thread_Singleton + sParam.m_uiPTR );
#endif

    atomic_store( &g_auiTR_Thread_Stack[sParam.m_uiE32], uiCurrentStack );
    atomic_thread_fence( cxx__memory_order_seq_cst );

    uiRet = g_afnTR_Thread_Function[sParam.m_uiPTR]( g_auiTR_Thread_Param[sParam.m_uiPTR] );

    tgMM_Clear_Thread_Local_Cache();

    pthread_exit( (TgVOID_P)(TgUINT_PTR)uiRet );
}

/*# TgCOMPILE__THREAD */
#endif


MSVC_WARN_DISABLE_POP( 4770 )
