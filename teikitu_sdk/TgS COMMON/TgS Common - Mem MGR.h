/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Mem MGR.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_MEMMGR_H)
#define TGS_COMMON_MEMMGR_H
#pragma once

#include "TgS COMMON/TgS Common - Preload - Mem MGR.h"


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  DOXYGEN                                                                                                                                                                        */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @defgroup TGS_COMMON_MEMORY_MGR Memory Manager
    @ingroup TGS_COMMON_COMMON
*/

    /** @defgroup TGS_COMMON_MEMORY_MGR_MODULE Module Functions
        @ingroup TGS_COMMON_MEMORY_MGR
    */


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* #REVIEW: Do we need a way to segment | heap the allocations - maybe include the FAC code with each allocation request? */

/** @addtogroup TGS_COMMON_MEMORY_MGR_MODULE */
/** @{ */

/** @brief Standard Module function: First part of initialization process. Set the state of the module.
    @return Result Code. */
TgEXTN TgRESULT
tgMM_Init_MGR( TgVOID );

/** @brief Standard Module function: Last part of initialization process. Used for setup and other necessary tasks prior to the use of the module.
    @return Result Code. */
TgEXTN TgRESULT
tgMM_Boot_MGR( TgVOID );

/** @brief Standard Module function: Used for close the module as part of the shutdown process. Module is not to be used after this is executed.
    @return Result Code. */
TgEXTN TgRESULT
tgMM_Stop_MGR( TgVOID );

/** @brief Standard Module function: Final part of shutdown process. Release any remaining allocated memory, and reset the state of the module.
    @return Result Code. */
TgEXTN TgRESULT
tgMM_Free_MGR( TgVOID );

/** @brief Standard Module function: Update the module, usually called on a per-frame basis, where the parameter is the forward time step amount.
    @param[in] ARG0 Amount of time to step forward the module in milliseconds
    @return Result Code. */
TgEXTN TgRESULT
tgMM_Update_MGR(
    TgFLOAT32_C ARG0 );

/** @brief Standard Module function: Recall the amount of global (static) memory used by the module
    @return Amount of global (static) memory used by the module. This is hard coded and thus, not explicitly correct. */
TgEXTN TgRSIZE
tgMM_Query_Fixed_Memory( TgVOID );

#if TgS_STAT__COMMON

/** @brief Standard Module function: Output relevant stats for the module.
    @param [in,out] OUT0 Pointer to an output object */
TgEXTN TgVOID
tgMM_Stats(
    STg2_Output_PC OUT0 );

/*# TgS_STAT__COMMON */
#endif

/** @} TGS_COMMON_MEMORY_MGR_MODULE */


/** @addtogroup TGS_COMMON_MEMORY_MGR */
/** @{ */

#if defined(TgCOMPILE__MEM_TRACK)

/** @brief Allocate a region of memory (size ARG1). Used in special cases where some extra information is required for the logs.
    @param [in] ARG0 Memory allocator to be used for the function call.
    @param [in] ARG1 Size of the region to allocate.
    @param [in] ARG2 Alignment for the allocation.
    @param [in] ARG3 Filename of the source file of the caller.
    @param [in] ARG4 Line number in the file of the call.
    @param [in] ARG5 String comment stored with the trace (only 23 bytes).
    @return Pointer to the allocated memory region on success and nullptr otherwise. */
TgEXTN TgVOID_P
tgMM_Malloc_With_Trace_Comment(
    ETgMM_ALLOCATOR_C ARG0, TgRSIZE_C ARG1, TgRSIZE_C ARG2, TgCHAR_U8_CPC ARG3, TgUINT_E32_C ARG4, TgCHAR_U8_CPC ARG5 );

/** @brief Allocate a region of memory (size ARG1).
    @param [in] ARG0 Memory allocator to be used for the function call.
    @param [in] ARG1 Size of the region to allocate.
    @param [in] ARG2 Alignment for the allocation.
    @param [in] ARG3 Filename of the source file of the caller.
    @param [in] ARG4 Line number in the file of the call.
    @return Pointer to the allocated memory region on success and nullptr otherwise. */
TgEXTN TgVOID_P
tgMM_Malloc_With_Trace(
    ETgMM_ALLOCATOR_C ARG0, TgRSIZE_C ARG1, TgRSIZE_C ARG2, TgCHAR_U8_CPC ARG3, TgUINT_E32_C ARG4 );

/** @brief Reserves a memory address range (of size ARG1).
    @param [in] ARG0 Memory allocator to be used for the function call.
    @param [in] ARG1 Size of the region to reserve.
    @param [in] ARG2 Filename of the source file of the caller.
    @param [in] ARG3 Line number in the file of the call.
    @return Pointer to the reserved memory region on success and nullptr otherwise. */
TgEXTN TgVOID_P
tgMM_Reserve_With_Trace(
    ETgMM_ALLOCATOR_C ARG0, TgRSIZE_C ARG1, TgCHAR_U8_CPC ARG2, TgUINT_E32_C ARG3 );

/** @brief Commits ARG2 amount of memory from a reserved range.
    @param [in] ARG0 Memory allocator to be used for the function call.
    @param [in] ARG1 Pointer to the start of the reserved region.
    @param [in] ARG2 Offset to the start of the region to commit.
    @param [in] ARG3 Size of the region to commit.
    @param [in] ARG4 Filename of the source file of the caller.
    @param [in] ARG5 Line number in the file of the call.
    @return Pointer to the start of the region committed and nullptr otherwise. */
TgEXTN TgVOID_P
tgMM_Commit_With_Trace(
    ETgMM_ALLOCATOR_C ARG0, TgVOID_PC OKNULL ARG1, TgRSIZE_C ARG2, TgRSIZE_C ARG3, TgCHAR_U8_CPC ARG4, TgUINT_E32_C ARG5 );

/** @brief Frees all resources used by the allocation starting at ARG1.
    @param [in] ARG0 Memory allocator to be used for the function call.
    @param [in] ARG1 Pointer to the start of a region of memory that was reserved.
    @param [in] ARG2 Filename of the source file of the caller.
    @param [in] ARG3 Line number in the file of the call. */
TgEXTN TgVOID
tgMM_Free_With_Trace(
    ETgMM_ALLOCATOR_C ARG0, TgVOID_PC TgANALYSIS_NO_NULL ARG1, TgCHAR_U8_CPC ARG2, TgUINT_E32_C ARG3 );

/** @brief Reallocate the memory at ARG1 to a size of ARG2.
    @param [in] ARG0 Memory allocator to be used for the function call.
    @param [in] ARG1 Pointer to the start of the original region of memory.
    @param [in] ARG2 Size of the new memory region.
    @param [in] ARG3 Alignment for the new memory region.
    @param [in] ARG4 Filename of the source file of the caller.
    @param [in] ARG5 Line number in the file of the call.
    @return Pointer to the start of the region allocated and nullptr otherwise. */
TgEXTN TgVOID_P
tgMM_Realloc_With_Trace(
    ETgMM_ALLOCATOR_C ARG0, TgVOID_PC OKNULL ARG1, TgRSIZE_C ARG2, TgRSIZE_C ARG3, TgCHAR_U8_CPC ARG4, TgUINT_E32_C ARG5 );

/*# defined(TgCOMPILE__MEM_TRACK) */
#endif

/** @} TGS_COMMON_MEMORY_MGR */


/* =============================================================================================================================================================================== */
#endif
