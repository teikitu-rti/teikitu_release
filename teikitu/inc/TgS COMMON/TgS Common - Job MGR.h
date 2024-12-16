/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Job MGR.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_JOB_MGR_H)
#define TGS_COMMON_JOB_MGR_H
#pragma once


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  DOXYGEN                                                                                                                                                                        */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @defgroup TGS_COMMON_JOB_MGR Job Manager
    @ingroup TGS_COMMON_COMMON
*/

    /** @defgroup TGS_COMMON_JOB_MGR_MODULE Module Functions
        @ingroup TGS_COMMON_JOB_MGR
    */


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Constants                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

enum { KTgMAX_NUM_THREAD                   = TgPLATFORM__THREAD_MAX >> 1 };
enum { KTgMAX_NUM_QUEUE                    = 1024 };
enum { KTgMAX_NUM_JOB                      = 4096 };
TgCOMPILER_ASSERT( KTgMAX_NUM_THREAD >= 16, 0 );

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Data                                                                                                                                                                    */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TgEXTN TgJOB_QUEUE_ID                       g_tiJob_Queue__OS;


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Console Variables - Job MGR                                                                                                                                                    */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TgEXTN TgCN_VAR_ID                          g_tiCVAR_Job_MGR_Enabled;


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions - Job MGR                                                                                                                                                     */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @addtogroup TGS_COMMON_JOB_MGR_MODULE */
/** @{ */

/** @brief Standard Module function: First part of initialization process. Set the state of the module.
    @return Result Code. */
TgEXTN TgRESULT
tgJM_Init_MGR( TgVOID );

/** @brief Standard Module function: Last part of initialization process. Used for setup and other necessary tasks prior to the use of the module.
    @return Result Code. */
TgEXTN TgRESULT
tgJM_Boot_MGR( TgVOID );

/** @brief Standard Module function: Used for close the module as part of the shutdown process. Module is not to be used after this is executed.
    @return Result Code. */
TgEXTN TgRESULT
tgJM_Stop_MGR( TgVOID );

/** @brief Standard Module function: Final part of shutdown process. Release any remaining allocated memory, and reset the state of the module.
    @return Result Code. */
TgEXTN TgRESULT
tgJM_Free_MGR( TgVOID );

/** @brief Standard Module function: State query to determine if the module is in the initialized or booted state
    @return True if the module has been initialized, and false otherwise. */
TgEXTN TgBOOL
tgJM_Query_Init( TgVOID );

/** @brief Standard Module function: State query to determine if the module has been booted state
    @return True if the module has been initialized and booted, and false otherwise. */
TgEXTN TgBOOL
tgJM_Query_Boot( TgVOID );

/** @brief Standard Module function: Recall the amount of global (static) memory used by the module
    @return Amount of global (static) memory used by the module. This is hard coded and thus, not explicitly correct. */
TgEXTN TgRSIZE
tgJM_Query_Fixed_Memory( TgVOID );


/** @} TGS_COMMON_JOB_MGR_MODULE */


/** @addtogroup TGS_COMMON_JOB_MGR */
/** @{ */

/** @brief Initialize a new job queue
    @return An identifier for the new job queue */
TgEXTN TgJOB_QUEUE_ID
tgJM_Init_Job_Queue( TgVOID );

/** @brief Stop the queue from processing any further jobs, with an option to abort jobs in flight
    @param [in] ARG0 Job Queue Identifier
    @param [in] ARG1 Abort flag - true to abort in flight jobs, and false otherwise */
TgEXTN TgVOID
tgJM_Stop_Job_Queue(
    TgJOB_QUEUE_ID ARG0, TgBOOL_C ARG1 );

/** @brief Free all resources used for the job queue
    @param [in] ARG Job Queue Identifier */
TgEXTN TgVOID
tgJM_Free_Job_Queue(
    TgJOB_QUEUE_ID ARG );


/** @brief Queue a job onto a job queue
    @param [in] ARG0 Job Queue Identifier
    @param [in] ARG1 Pointer to a job object */
TgEXTN TgRESULT
tgJM_Queue_Job(
    TgJOB_QUEUE_ID ARG0, STg2_Job_P ARG1 );


/** @brief Spawn a new thread to be used for job processing
    @param [in] ARG0 Pointer to a list of job queues that the thread will process
    @param [in] ARG1 Number of queues in ARG0
    @param [in] ARG2 Thread priority
    @param [in] ARG3 Thread name
    @return An identifier for the job thread */
TgEXTN TgJOB_THREAD_ID
tgJM_Spawn_Job_Thread(
    TgJOB_QUEUE_ID_CPC ARG0, TgUINT_F32 ARG1, ETgTHREAD_PRIORITY_C ARG2, TgCHAR_U8_CPC ARG3 );

/** @brief Stop the thread from processing any further jobs, join the thread and terminate it
    @param [in] ARG Job Thread Identifier */
TgEXTN TgVOID
tgJM_Stop_Job_Thread( 
    TgJOB_THREAD_ID ARG );

/** @brief Return the thread identifier used for the job thread
    @param [in] ARG Job Thread Identifier */
TgEXTN TgTHREAD_ID
tgJM_Query_Thread_Id(
    TgJOB_THREAD_ID ARG );

/** @} TGS_COMMON_JOB_MGR */


/* =============================================================================================================================================================================== */
#endif
