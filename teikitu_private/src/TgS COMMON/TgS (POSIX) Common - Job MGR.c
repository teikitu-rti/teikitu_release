/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (POSIX) Common - Job MGR.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.21 | »GUID« AEEC8393-9780-4ECA-918D-E3E11F7E2744 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "TgS Common - Job MGR - Internal.h"


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Type */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TgTYPE_STRUCT(STg2_PM_Job_Thread,)
{
    TgJOB_THREAD_ID TgALIGN(16)                 m_tiJob_Thread;
    TgVOID_P                                    m_apEvent[KTgMAX_NUM_QUEUE];
    TgRSIZE                                     m_nuiEvent;
};


TgTYPE_STRUCT(STg2_PM_Job_Queue,)
{
    TgJOB_QUEUE_ID                              m_tiQueue;
    TgVOID_P                                    m_pEvent;
};




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Data                                                                                                                                                                */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

static STg2_PM_Job_Queue                    s_asJob_Queue[KTgMAX_NUM_QUEUE];

#if TgCOMPILE__THREAD
static STg2_PM_Job_Thread                   s_asJob_Thread[KTgMAX_NUM_THREAD];
/*# TgCOMPILE__THREAD */
#endif




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Private Functions                                                                                                                                                              */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgVOID tgJM_PM_Init_MGR( TgVOID )
{
    tgMM_Set_U08_0x00( s_asJob_Queue, sizeof(s_asJob_Queue) );
#if TgCOMPILE__THREAD
    tgMM_Set_U08_0x00( s_asJob_Thread, sizeof(s_asJob_Thread) );
/*# TgCOMPILE__THREAD */
#endif
}


TgVOID tgJM_PM_Free_MGR( TgVOID )
{
}


TgVOID tgJM_PM_Init_Job_Queue( TgJOB_QUEUE_ID_C tiQueue )
{
    s_asJob_Queue[tiQueue.m_uiI].m_tiQueue = tiQueue;
    //s_asJob_Queue[tiQueue.m_uiI].m_pEvent = g_pfnCreateEvent( nullptr, FALSE, FALSE, nullptr );
}


TgVOID tgJM_PM_Free_Job_Queue( TgJOB_QUEUE_ID_C tiQueue )
{
    s_asJob_Queue[tiQueue.m_uiI].m_tiQueue.m_uiKI = KTgID__INVALID_VALUE;
    //g_pfnCloseHandle( s_asJob_Queue[tiQueue.m_uiI].m_pEvent );
}


TgVOID tgJM_PM_Queue_Job( TgATTRIBUTE_UNUSED TgJOB_QUEUE_ID_C tiQueue )
{
    //g_pfnSetEvent( s_asJob_Queue[tiQueue.m_uiI].m_pEvent );
}


#if TgCOMPILE__THREAD
TgVOID tgJM_PM_Spawn_Job_Thread( TgJOB_THREAD_ID_C tiJob_Thread, TgJOB_QUEUE_ID_CPC atiQueueList, TgUINT_E32 nuiQueue, ETgTHREAD_PRIORITY_C enPriority, TgCHAR_U8_CPC szName )
{
    TgUINT_E32                          uiIndex;

    (void)enPriority;
    (void)szName;

    tgMM_Set_U08_0x00( s_asJob_Thread + tiJob_Thread.m_uiI, sizeof(s_asJob_Thread[0]) );

    s_asJob_Thread[tiJob_Thread.m_uiI].m_tiJob_Thread = tiJob_Thread;
    s_asJob_Thread[tiJob_Thread.m_uiI].m_nuiEvent = nuiQueue;

    for (uiIndex = 0; uiIndex <nuiQueue; ++uiIndex )
    {
        if (KTgJOB_QUEUE_ID__INVALID.m_uiKI == atiQueueList[uiIndex].m_uiKI)
            break;

        /* Check that the queue is still valid (i.e. the UIDs match). */
        if (s_asJob_Queue[atiQueueList[uiIndex].m_uiI].m_tiQueue.m_uiKI != atiQueueList[uiIndex].m_uiKI)
            continue;
        /* Assign the event handler into the thread list. */
        s_asJob_Thread[tiJob_Thread.m_uiI].m_apEvent[uiIndex] = s_asJob_Queue[atiQueueList[uiIndex].m_uiI].m_pEvent;
    };
}
/*# TgCOMPILE__THREAD */
#endif


#if TgCOMPILE__THREAD
TgVOID tgJM_PM_Stop_Job_Thread( TgJOB_THREAD_ID_C tiJob_Thread )
{
    if (s_asJob_Thread[tiJob_Thread.m_uiI].m_tiJob_Thread.m_uiKI != tiJob_Thread.m_uiKI)
        return;
    s_asJob_Thread[tiJob_Thread.m_uiI].m_tiJob_Thread.m_uiKI = KTgID__INVALID_VALUE;
    s_asJob_Thread[tiJob_Thread.m_uiI].m_nuiEvent = 0;
}
/*# TgCOMPILE__THREAD */
#endif


#if TgCOMPILE__THREAD
TgVOID tgJM_PM_Job_Thread__Wait_For_Job( TgJOB_THREAD_ID_C tiJob_Thread )
{
    if (s_asJob_Thread[tiJob_Thread.m_uiI].m_tiJob_Thread.m_uiKI != tiJob_Thread.m_uiKI)
        return;
    //g_pfnWaitForMultipleObjectsEx( (DWORD)s_asJob_Thread[tiJob_Thread.m_uiI].m_nuiEvent, s_asJob_Thread[tiJob_Thread.m_uiI].m_apEvent, 0, INFINITE, 0 );
}
/*# TgCOMPILE__THREAD */
#endif
