/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Job MGR - Internal.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_JOB_MGR_INTERNAL_H)
#define TGS_COMMON_JOB_MGR_INTERNAL_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Private Functions                                                                                                                                                              */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/*  Module Functions                                                                                                                                                               */

/** @brief Standard Module function: First part of initialization process. Set the state of the module. */
TgEXTN TgVOID
tgJM_PM_Init_MGR( TgVOID );

/** @brief Standard Module function: Final part of shutdown process. Release any remaining allocated memory, and reset the state of the module. */
TgEXTN TgVOID
tgJM_PM_Free_MGR( TgVOID );


/*  Job Queue                                                                                                                                                                      */

/** @brief Platform init for a job queue. Creates an event to be associated with the queue.
    @param [in] ARG0 UID of the Job Queue. */
TgEXTN TgVOID
tgJM_PM_Init_Job_Queue(
    TgJOB_QUEUE_ID_C ARG0 );

/** @brief Platform free for a job queue. Releases the event associated with the queue.
    @param [in] ARG0 UID of the Job Queue. */
TgEXTN TgVOID
tgJM_PM_Free_Job_Queue(
    TgJOB_QUEUE_ID_C ARG0 );

/** @brief Signals the event associated with the queue.
    @param [in] ARG0 UID of the Job Queue. */
TgEXTN TgVOID
tgJM_PM_Queue_Job(
    TgJOB_QUEUE_ID_C ARG0 );


/*  Job Thread                                                                                                                                                                     */

#if TgCOMPILE__THREAD
/** @brief Spawn a new thread to be used for job processing
    @param [in] ARG0 UID of the Job Thread.
    @param [in] ARG1 Pointer to a list of job queues that the thread will process.
    @param [in] ARG2 Number of queues in ARG0.
    @param [in] ARG3 Thread priority.
    @param [in] ARG4 Thread name.  */
TgEXTN TgVOID
tgJM_PM_Spawn_Job_Thread(
    TgJOB_THREAD_ID_C ARG0, TgJOB_QUEUE_ID_CPC ARG1, TgUINT_E32 ARG2, ETgTHREAD_PRIORITY_C ARG3, TgCHAR_U8_CPC ARG4 );

/** @brief Platform stop for a job thread. Invalidates the internal data associated with the job thread.
    @param [in] ARG0 UID of the Job Thread. */
TgEXTN TgVOID
tgJM_PM_Stop_Job_Thread(
    TgJOB_THREAD_ID_C ARG0 );

/** @brief Causes the job thread to wait on the events associated with all the queues associated with the thread.
    @param [in] ARG0 UID of the Job Thread. */
TgEXTN TgVOID
tgJM_PM_Job_Thread__Wait_For_Job(
    TgJOB_THREAD_ID_C ARG0 );
/*# TgCOMPILE__THREAD */
#endif


/* =============================================================================================================================================================================== */
#endif
