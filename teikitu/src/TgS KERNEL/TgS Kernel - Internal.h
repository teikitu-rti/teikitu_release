/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Kernel - Internal.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_KERNEL_INTERNAL_H)
#define TGS_KERNEL_INTERNAL_H

#include "TgS Common.h"
#include "TgS Kernel.h"
#include "TgS Kernel - Internal - Type.h"
#include "TgS Kernel - Internal - Data.h"

#include "TgS COMMON/TgS Common.inl"


/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/** @brief Standard Module function: First part of initialization process. Set the state of the module.
    @return Result Code. */
TgEXTN TgRESULT
tgKN_OS_Module_Init( TgVOID );

/** @brief Standard Module function: Last part of initialization process. Used for setup and other necessary tasks prior to the use of the module.
    @return Result Code. */
TgEXTN TgRESULT
tgKN_OS_Module_Boot( TgVOID );

/** @brief Standard Module function: Used for close the module as part of the shutdown process. Module is not to be used after this is executed. */
TgEXTN TgRESULT
tgKN_OS_Module_Stop( TgVOID );

/** @brief Standard Module function: Final part of shutdown process. Release any remaining allocated memory, and reset the state of the module. */
TgEXTN TgRESULT
tgKN_OS_Module_Free( TgVOID );

/** @brief Standard Module function: Update the module, usually called on a per-frame basis, where the parameter is the forward time step amount.
    @param[in] ARG0 Amount of time to step forward the module in milliseconds.
    @return Result Code. */
TgEXTN TgRESULT
tgKN_OS_Module_Update(
    TgFLOAT32_C ARG0 );

/** @brief Standard Module function: Recall the amount of global (static) memory used by the module.
    @return Amount of global (static) memory used by the module. This is hard coded and thus, not explicitly correct. */
TgEXTN TgRSIZE
tgKN_OS_Query_Fixed_Memory( TgVOID );


/* ---- File Serialization ------------------------------------------------------------------------------------------------------------------------------------------------------- */

/** @brief Register a file system. There is no process to unregister a file system.
    @param[in] ARG0 Pointer to a command structure for the operation.
    @return UID to identify the file system on success, and the INVALID ID otherwise. */
TgEXTN TgKN_FILE_SYSTEM_ID
tgKN_File_System__Register(
    STg2_KN_File_System_DESC_PC ARG0 );

/** @brief Free all memory associated with the registered file systems, and invalidate all references. Used as part of the Kernel Free process. */
TgEXTN TgVOID
tgKN_File_System__Free_All( TgVOID );


/** @brief Initialize an open command structure, and assign a file UID.
    @param[in] OUT0 Pointer to a command structure for the operation.
    @return UID to identify the proposed file on success, and the INVALID ID otherwise. */
TgEXTN TgKN_FILE_ID
tgKN_File__Info_Init(
    STg2_KN_File_Open_Command_CPCU OUT0 );

/** @brief Frees all allocated memory associated with an open file (for example, system memory cache) and invalidates the associated UID.
    @param[in] ARG0 UID that identifies the file (returned from tgKN_FS_BL_Open). */
TgEXTN TgVOID
tgKN_File__Info_Free(
    TgKN_FILE_ID_C ARG0 );


/** @brief Last action for a job in the pipeline, responsible for executing call backs and placing it back into the queue to be re-used.
    @param[in] OUT0 Pointer to a file job. */
TgEXTN TgVOID
tgKN_FS_Job_Complete(
    STg2_KN_File_Job_PCU OUT0 );


/** @brief Initialize a generic input structure to be used for file read-only operations.
    @param[in] OUT0 Pointer to a file input structure.
    @param[in] ARG1 UID for the mount location to be used.
    @param[in] ARG2 Integer hash for the path.
    @param[in] ARG3 Integer hash for the file.
    @return Result Code. */
TgEXTN TgRESULT
tgKN_IF__Open(
    STg2_Input_File_PCU OUT0, TgKN_FS_MOUNT_ID_C ARG1, TgUINT_F32_C ARG2, TgUINT_F32_C ARG3 );

/** @brief Mark the object as being closed (subsequent commands will fail), and optionally frees the memory region
    @param [in,out] OUT0 Pointer to an input object that is memory backed
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
tgKN_IF__Close(
    STg2_Input_PC OUT0 );

/** @brief Read from the input object at ARG0 and store the data at ARG2
    @param [out] OUT0 Pointer to the region of memory that the data will be written
    @param [in] ARG1 Available size of the region of memory at OUT0
    @param [in] ARG2 Pointer to an input memory object (cast as the parent)
    @param [in] ARG3 Starting offset for the read operation
    @param [in] ARG4 Number of bytes to read
    @return The number of characters read or zero otherwise */
TgEXTN TgRSIZE
tgKN_IF__Read(
    TgVOID_P OUT0, TgRSIZE_C ARG1, STg2_Input_PC ARG2, TgRSIZE_C ARG3, TgRSIZE_C ARG4 );

/** @brief Tests to see if the input object has been completely read
    @param [in] ARG0 Pointer to an input object that is memory backed
    @return True if the at the end of input, and false otherwise */
TgEXTN TgBOOL
tgKN_IF__End_Of_File(
    STg2_Input_PC ARG0, TgRSIZE_C ARG1 );


/** @brief Initialize a generic output structure to be used for file read-write operations.
    @param[in] OUT0 Pointer to a file output structure.
    @param[in] ARG1 UID for the mount location to be used.
    @param[in] ARG2 Integer hash for the path.
    @param[in] ARG3 Integer hash for the file.
    @return Result Code. */
TgEXTN TgRESULT
tgKN_OF__Open(
    STg2_Output_File_PCU OUT0, TgKN_FS_MOUNT_ID_C ARG1, TgUINT_F32_C ARG2, TgUINT_F32_C ARG3 );

/** @brief Mark the object as being closed (subsequent commands will fail), and optionally frees the memory region
    @param [in,out] OUT0 Pointer to an output object that is memory backed
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
tgKN_OF__Close(
    STg2_Output_PC OUT0 );

/** @brief Write the data stream in ARG2 out through object at ARG0
    @param [in,out] OUT0 Pointer to an output object that is memory backed
    @param [in] ARG1 Write offset of the output object
    @param [in] ARG2 Pointer to region of memory to be written
    @param [in] ARG3 Size to be written
    @return The number of characters written or zero otherwise */
TgEXTN TgRSIZE
tgKN_OF__Write(
    STg2_Output_PC OUT0, TgRSIZE_C ARG1, TgVOID_CP ARG2, TgRSIZE_C ARG3 );


/* File System - HDD */

/** @brief Report the amount of free space remaining at the mount location.
    @param[in] ARG0 UID for the mount location.
    @return Amount of free space remaining at the mount location. */
TgEXTN TgRSIZE
tgKN_FS_HDD__Free_Space(
    TgKN_FS_MOUNT_ID_C ARG0 );

/** @brief Initialize a generic output structure to be used for file read-write operations.
    @param[in] ARG0 UID for the mount location.
    @param[in] ARG1 String holding the path to be mounted. */
TgEXTN TgVOID
tgKN_FS_HDD__Mount(
    TgKN_FS_MOUNT_ID_C ARG0, TgCHAR_U8_CPCU ARG1 );

/** @brief Primary job execution engine for the HDD file system.
    @param[in] ARG0 Pointer to a file job. */
TgEXTN TgVOID
tgKN_FS_HDD__Execute_Job(
    STg2_KN_File_Job_P ARG0 );

/** @brief Free the system as part of kernel free.
    @param[in] ARG0 UID for the mount location. */
TgEXTN TgVOID
tgKN_FS_HDD__Mount_Free(
    TgKN_FS_MOUNT_ID_C ARG0 );


/* =============================================================================================================================================================================== */
#endif
