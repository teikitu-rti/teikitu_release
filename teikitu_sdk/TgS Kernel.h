/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Kernel.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_KERNEL_H)
#define TGS_KERNEL_H
#pragma once

#include "TgS KERNEL/TgS Kernel - Constants.h"
#include "TgS KERNEL/TgS Kernel - Type.h"
#include "TgS KERNEL/TgS Kernel - Data.h"


/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Module Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/** @brief Standard Module functions: Used during the unit test process. */
TgEXTN TgVOID
tgKN_Unit_Test_External( TgVOID ); /* Do not ever execute */


/** @brief Standard Module function: First part of initialization process. Set the state of the module.
    @return Result Code. */
TgEXTN TgRESULT
tgKN_Module_Init( TgVOID );

/** @brief Standard Module function: Last part of initialization process. Used for setup and other necessary tasks prior to the use of the module.
    @return Result Code. */
TgEXTN TgRESULT
tgKN_Module_Boot( TgVOID );

/** @brief Standard Module function: Used for close the module as part of the shutdown process. Module is not to be used after this is executed. */
TgEXTN TgVOID
tgKN_Module_Stop( TgVOID );

/** @brief Standard Module function: Final part of shutdown process. Release any remaining allocated memory, and reset the state of the module. */
TgEXTN TgVOID
tgKN_Module_Free( TgVOID );

/** @brief Standard Module function: Update the module, usually called on a per-frame basis, where the parameter is the forward time step amount.
    @param[in] ARG0 Amount of time to step forward the module in milliseconds.
    @return Result Code. */
TgEXTN TgRESULT
tgKN_Module_Update(
    TgFLOAT32_C ARG0 );


/** @brief Standard Module functions: Set the current configuration of the module. */
TgEXTN TgRESULT
tgKN_Load_Config( TgVOID );

/** @brief Standard Module function: Save the current configuration of the module. */
TgEXTN TgRESULT
tgKN_Save_Config( TgVOID );


/** @brief Standard Module function: State query to determine if the module is in the initialized or booted state.
    @return True if the module has been initialized, and false otherwise. */
TgEXTN TgBOOL
tgKN_Query_Init( TgVOID );

/** @brief Standard Module function: State query to determine if the module has been booted state.
    @return True if the module has been initialized and booted, and false otherwise. */
TgEXTN TgBOOL
tgKN_Query_Boot( TgVOID );

/** @brief Standard Module function: Recall the amount of global (static) memory used by the module.
    @return Amount of global (static) memory used by the module. This is hard coded and thus, not explicitly correct. */
TgEXTN TgRSIZE
tgKN_Query_Fixed_Memory( TgVOID );


#if TgS_STAT__KERNEL
/** @brief Standard Module function: Output relevant stats for the module.
    @param [in,out] OUT0 Pointer to an output object. */
TgEXTN TgVOID
tgKN_Stats(
    STg2_Output_P OUT0 );
#endif


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Kernel Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- Message System ----------------------------------------------------------------------------------------------------------------------------------------------------------- */

/** @brief Register a function to be called when a given message UID is called.
    @param[in] ARG0 Pointer to a function.
    @param[in] ARG1 Integer value that is passed to the function at ARG0 when called.
    @param[in] ARG2 Integer value that is the message UID.
    @return UID to identify this notification registration on success, and the INVALID ID otherwise. */
TgEXTN TgKN_NOTIFY_ID
tgKN_Notify_Start(
    TgKN_FCN_NOTIFY_CALLBACK ARG0, TgUINT_PTR_C ARG1, TgUINT_E64_C ARG2 );

/** @brief Unregister (terminate) the notification for the given notification registration UID.
    @param[in] ARG0 UID that identifies the notification registration (returned from tgKN_Notify_Start).
    @return Result Code. */
TgEXTN TgRESULT
tgKN_Notify_End(
    TgKN_NOTIFY_ID_C ARG0 );

/** @brief Message broadcast system for system and user defined messages
    @param[in] ARG0 Integer that is the message UID.
    @param[in] ARG1 Integer that is the 1st generic parameter.
    @param[in] ARG2 Integer that is the 2nd generic parameter.
    @return Result Code. */
TgEXTN TgRESULT
tgKN_Notify_MSG(
    TgUINT_E64_C ARG0, TgUINT_E64_C ARG1, TgUINT_E64_C ARG2 );


/* ---- File Functions ----------------------------------------------------------------------------------------------------------------------------------------------------------- */

/** @brief Mount a given location with a specified level of access on the provided file system.
    @param[in] ARG0 UID for the file system to be used for the operation.
    @param[in] ARG1 Bitfield indicating the level (type) of access to the files to be mounted at the given location.
    @param[in] ARG2 String indicating the location to be mounted.
    @return UID to identify this file system mount on success, and the INVALID ID otherwise. */
TgEXTN TgKN_FS_MOUNT_ID
tgKN_File_System_Mount(
    TgKN_FILE_SYSTEM_ID_C ARG0, TgUINT_E32_C ARG1, TgCHAR_U8_CPCU ARG2 );

/** @brief Return the amount of free space available at the given file system mount location.
    @param[in] ARG0 UID that identifies the file system mount (returned from tgKN_File_System_Mount). 
    @return Integer of the remaining free space for the given file system mount location on success, or zero otherwise. */
TgEXTN TgRSIZE
tgKN_FS_Query_Free_Space(
    TgKN_FS_MOUNT_ID_C ARG0 ); /* #IMPLEMENT */

/** @brief Return a block of memory using the default file system memory allocator.
    @param[in] ARG0 Integer that is the amount of memory in bytes to allocate.
    @return Pointer to the start of the memory block that was allocated, or nullptr otherwise. */
TgEXTN TgVOID_P
tgKN_FILE_ALLOCATOR__Default_Malloc_Pool(
    TgRSIZE_C ARG0 );


/* These will be executed out of order from the other commands, as a highest order request.  If the desire behavior is to stall until the operations are completed in the job list
   as well, then use a custom call back function in a job operation */

/** @brief Open a file and block until the operation is completed.
    @param[in] ARG0 Pointer to a command structure for the operation.
    @return UID to identify the file on success, and the INVALID ID otherwise. */
TgEXTN TgKN_FILE_ID
tgKN_FS_BL_Open(
    STg2_KN_File_Open_Command_CPCU ARG0 );

/** @brief Read from a file and block until the operation is completed.
    @param[in] ARG0 Pointer to a command structure for the operation.
    @return Result Code. */
TgEXTN TgRESULT
tgKN_FS_BL_Read(
    STg2_KN_File_Read_Command_PCU ARG0 );

/** @brief Read some of the contents of a file into the file system cache and block until the operation is completed.
    @param[in] ARG0 Pointer to a command structure for the operation.
    @return Result Code. */
TgEXTN TgRESULT
tgKN_FS_BL_Cache(
    STg2_KN_File_Cache_Command_CPCU ARG0 );

/** @brief Write data into the file and block until the operation is completed.
    @param[in] ARG0 Pointer to a command structure for the operation.
    @return Result Code. */
TgEXTN TgRESULT
tgKN_FS_BL_Write(
    STg2_KN_File_Write_Command_PCU ARG0 );

/** @brief Flush (commit to the persistent storage) all remaining transient operations (e.g. cached writes).
    @param[in] ARG0 UID that identifies the file (returned from tgKN_FS_BL_Open).
    @return Result Code. */
TgEXTN TgRESULT
tgKN_FS_BL_Flush(
    TgKN_FILE_ID_C ARG0 );

/** @brief Close the given file and prevent further file operations on it from succeeding.
    @param[in] ARG0 UID that identifies the file (returned from tgKN_FS_BL_Open).
    @return Result Code. */
TgEXTN TgRESULT
tgKN_FS_BL_Close(
    TgKN_FILE_ID_C ARG0 );


/* Maintaining sequentiality of operations for a given file UID is the responsibility of the file system implementation. */

/** @brief Request an asynchronous read from an open file.
    @param[in] ARG0 Pointer to a command structure for the operation.
    @return UID to identify the job on success, and the INVALID ID otherwise. */
TgEXTN TgKN_FILE_JOB_ID
tgKN_FS_JB_Read(
    STg2_KN_File_Read_Command_CPCU ARG0 );

/** @brief Request an asynchronous read from an open file, storing the result into the file system cache.
    @param[in] ARG0 Pointer to a command structure for the operation.
    @return UID to identify the job on success, and the INVALID ID otherwise. */
TgEXTN TgKN_FILE_JOB_ID
tgKN_FS_JB_Cache(
    STg2_KN_File_Cache_Command_CPCU ARG0 );

/** @brief Request an asynchronous write to an open file.
    @param[in] ARG0 Pointer to a command structure for the operation.
    @return UID to identify the job on success, and the INVALID ID otherwise. */
TgEXTN TgKN_FILE_JOB_ID
tgKN_FS_JB_Write(
    STg2_KN_File_Write_Command_CPCU ARG0 );

/** @brief Request an asynchronous flush (commit to the persistent storage) of all remaining transient operations (e.g. cached writes).
    @param[in] ARG0 UID that identifies the file (returned from tgKN_FS_BL_Open).
    @return UID to identify the job on success, and the INVALID ID otherwise. */
TgEXTN TgKN_FILE_JOB_ID
tgKN_FS_JB_Flush(
    TgKN_FILE_ID_C ARG0 );

/** @brief Request an asynchronous close of the given file and prevent further file operations on it from succeeding.
    @param[in] ARG0 UID that identifies the file (returned from tgKN_FS_BL_Open).
    @return UID to identify the job on success, and the INVALID ID otherwise. */
TgEXTN TgKN_FILE_JOB_ID
tgKN_FS_JB_Close(
    TgKN_FILE_ID_C ARG0 );


/** @brief Request a job to be cancelled.
    @param[in] ARG0 UID that identifies the job. */
TgEXTN TgVOID
tgKN_FS_JB_Cancel(
    TgKN_FILE_JOB_ID_C ARG0 );

/** @brief Query the current status of a given job.
    @param[in] ARG0 UID that identifies the job.
    @return Status of the identified job on success, or ETgKN_IO_STATUS__ERROR otherwise. */
TgEXTN ETgKN_IO_STATUS
tgKN_FS_JB_Status(
    TgKN_FILE_JOB_ID_C ARG0 );


#if TgS_STAT__COMMON
/** @brief Standard Module function: Output relevant stats for the module.
    @param[in,out] OUT0 Pointer to an output object. */
TgEXTN TgVOID
tgKN_FS_Stats(
    STg2_Output_PC OUT0 );  /* #IMPLEMENT */
#endif


/* =============================================================================================================================================================================== */
#endif
