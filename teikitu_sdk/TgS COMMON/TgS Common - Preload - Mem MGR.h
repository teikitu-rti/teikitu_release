/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Preload - Mem MGR.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.21 | »GUID« AEEC8393-9780-4ECA-918D-E3E11F7E2744 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_PRELOAD_MEM_MGR_H)
#define TGS_COMMON_PRELOAD_MEM_MGR_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif


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
/*  API                                                                                                                                                                            */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#if defined(MK_BUILD__SHARED_LIBRARY)
    #if defined(_Ring_0___TgS_COMMON__OS_PRELOAD)
        #define PREMM_API TgDLL_EXPORT
    #else
        #define PREMM_API TgDLL_IMPORT
    #endif
#else
    #define PREMM_API
#endif


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Constants                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @brief Enumeration used by the memory manager to allow for the use of multiple allocators. Allocators should be thought of as low level asscessors to acquire and release memory
           through a specific memory controller. The usage pattern of the acquired memory (e.g. stack vs single object) is left to the caller. The two default allocators is a pass
           through to the standard operation system allocator and the second is a pool allocator for small allocations. An example of user allocators that could be created
           depending on the needs of the underlying hardware platform: GPU memory, sound memory, a global shared memory pool, and high-speed local memory. */

typedef enum TgATTRIBUTE_ENUM
{
    ETgMM_ALLOCATOR_BEGIN = 0,
    ETgMM_ALLOCATOR_OS = ETgMM_ALLOCATOR_BEGIN,
    ETgMM_ALLOCATOR_POOL,
    ETgMM_ALLOCATOR_MIMALLOC,
    ETgMM_ALLOCATOR_USER_0,
    ETgMM_ALLOCATOR_USER_1,
    ETgMM_ALLOCATOR_USER_2,
    ETgMM_ALLOCATOR_USER_3,
    ETgMM_ALLOCATOR_END,
    ETgMM_ALLOCATOR_COUNT = ETgMM_ALLOCATOR_END - ETgMM_ALLOCATOR_BEGIN
} ETgMM_ALLOCATOR;
TgTYPE_MODIFIER_DEFAULT(ETgMM_ALLOCATOR);



/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Types                                                                                                                                                                   */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @brief Output data structure to hold the results of a memory allocator call. */
#define MEM_INFO_HEADER__ALLOCATOR_BITS 3
#pragma pack(push,1)
TgTYPE_STRUCT(TgMEM_INFO_HEADER,)
{
    TgUINT_E32                                  m_uiSize;                                   /*  4 Bytes */
    union
    {
        TgUINT_E16                                  m_uiFlags;                                  /*  2 Bytes */
        struct
        {
            TgUINT_E16                                  m_bReserved : 1;
            TgUINT_E16                                  m_enAllocator : MEM_INFO_HEADER__ALLOCATOR_BITS;
            TgUINT_E16                                  m_bPad : 15 - MEM_INFO_HEADER__ALLOCATOR_BITS;
        };
    };
};
#pragma pack(pop)
TgCOMPILER_ASSERT(ETgMM_ALLOCATOR_COUNT < (1 << MEM_INFO_HEADER__ALLOCATOR_BITS),0);

/** @brief Data structured used to contain all of the function pointers required to define a memory allocator. */
TgTYPE_STRUCT(STg2_MM_MGR,)
{
    TgRESULT                                    (*m_pfnInit_MGR)( TgVOID );
    TgRESULT                                    (*m_pfnFree_MGR)( TgVOID );

#if TgS_STAT__COMMON
    TgVOID                                      (*m_pfnStats)( TgRSIZE (*ARG0)( STg2_Output_PC TgANALYSIS_NO_NULL ARG0, TgCHAR_U8_CPC TgANALYSIS_NO_NULL ARG1, ... ), STg2_Output_PC ARG1 );
#endif

                                                /** @brief Return the size of the memory region starting at ARG2. @return Result Code.
                                                    @param [out] OUT0 Pointer to hold the amount of reserved memory.
                                                    @param [out] OUT1 Pointer to hold the amount of allocated memory.
                                                    @param [in] ARG2 Pointer to the start of a reserved or allocated region of memory. */
    TgRESULT                                    (*m_pfnSize)( TgUINT_E32_P TgANALYSIS_NO_NULL OUT0, TgUINT_E32_P TgANALYSIS_NO_NULL OUT1, TgVOID_CPC TgANALYSIS_NO_NULL ARG2 );

                                                /** @brief Allocate a region of memory (size ARG2) @return Result Code.
                                                    @param [out] OUT0 Pointer to a memory information header.
                                                    @param [out] OUT1 Returned pointer to the beginning of the requested allocated region of memory.
                                                    @param [in] ARG2 Size of the region to allocate.
                                                    @param [in] ARG3 Required alignement for allocation. */
    TgRESULT                                    (*m_pfnMalloc)( TgMEM_INFO_HEADER_P TgANALYSIS_NO_NULL OUT0, TgVOID_PP TgANALYSIS_NO_NULL OUT1, TgRSIZE_C ARG2, TgRSIZE_C ARG3 );

                                                /** @brief Allocate a region of memory (size ARG2). @return Result Code.
                                                    @param [out] OUT0 Pointer to a memory information header.
                                                    @param [out] OUT1 Returned pointer to the beginning of the requested reserved region of memory.
                                                    @param [in] ARG2 Size of the region to reserve. */
    TgRESULT                                    (*m_pfnReserve)( TgMEM_INFO_HEADER_P TgANALYSIS_NO_NULL OUT0, TgVOID_PP TgANALYSIS_NO_NULL OUT1, TgRSIZE_C ARG2 );

                                                /** @brief Allocate a region of memory (size ARG2). @return Result Code.
                                                    @param [out] OUT0 Pointer to a memory information header.
                                                    @param [in,out] OUT1 Pointer to the start of a reserved region, or null for a new allocation. On success, points to the start
                                                                         of the commit block or is nullptr otherwise.
                                                    @param [in] ARG2 Offset from the pointer base to the start of the region to commit.
                                                    @param [in] ARG3 Size of the region to commit. */
    TgRESULT                                    (*m_pfnCommit)( TgMEM_INFO_HEADER_P TgANALYSIS_NO_NULL OUT0, TgVOID_PP TgANALYSIS_NO_NULL OUT1, TgRSIZE_C ARG2, TgRSIZE_C ARG3 );

                                                /** @brief Allocate a region of memory (size ARG2). @return Result Code.
                                                    @param [out] OUT0 Pointer to a memory information header.
                                                    @param [in] ARG1 Pointer to a region of memory to free (deallocate). */
    TgRESULT                                    (*m_pfnFree)( TgMEM_INFO_HEADER_P TgANALYSIS_NO_NULL OUT0, TgVOID_PC TgANALYSIS_NO_NULL ARG1 );

                                                /** @brief Allocate a region of memory (size ARG2). @return Result Code.
                                                    @param [out] OUT0 Pointer to a memory information header for the new region of memory.
                                                    @param [out] OUT1 Returned pointer to the beginning of the requested allocated region of memory.
                                                    @param [out] OUT2 Pointer to a memory information header for the original region of memory.
                                                    @param [in] ARG3 Pointer to the original region of memory.
                                                    @param [in] ARG4 Size of the region to allocate.
                                                    @param [in] ARG5 Alignment for the allocation. */
    TgRESULT                                    (*m_pfnRealloc)(
                                                     TgMEM_INFO_HEADER_P TgANALYSIS_NO_NULL OUT0, TgVOID_PP OUT1, TgMEM_INFO_HEADER_P OUT2, TgVOID_PC ARG3, TgRSIZE_C ARG4, TgRSIZE_C ARG5 );

    TgVOID                                      (*m_pfnFree_Thread_Local)( TgVOID ) TgATTRIBUTE_NO_EXCEPT;
};


#if TgS_STAT__COMMON
TgTYPE_STRUCT(STg2_MM_Preload_Stats,)
{
    TgCHAR_U8_CP                                m_ambzStat_Name[ETgMM_ALLOCATOR_COUNT];
    TgRSIZE                                     m_anuiStat_Allocations[ETgMM_ALLOCATOR_COUNT];
    TgRSIZE                                     m_anuiStat_Max_Allocations[ETgMM_ALLOCATOR_COUNT];
    TgRSIZE                                     m_auiStat_Allocated[ETgMM_ALLOCATOR_COUNT];
    TgRSIZE                                     m_auiStat_Max_Allocated[ETgMM_ALLOCATOR_COUNT];
    TgRSIZE                                     m_auiStat_Reserved[ETgMM_ALLOCATOR_COUNT];
    TgRSIZE                                     m_auiStat_Max_Reserved[ETgMM_ALLOCATOR_COUNT];
};
/*# TgS_STAT__COMMON */
#endif


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* #REVIEW: Do we need a way to segment | heap the allocations - maybe include the FAC code with each allocation request? */

/** @addtogroup TGS_COMMON_MEMORY_MGR_MODULE */
/** @{ */

/** @brief Set an internal pointer to the console print function. */
TgEXTN PREMM_API TgVOID
tgMM_Set_CN_PrintF( TgVOID (*)( TgUINT_E32_C, TgCHAR_U8_CP TgANALYSIS_NO_NULL, ... ) );

/** @brief Standard Module function: State query to determine if the module is in the initialized or booted state.
    @return True if the module has been initialized, and false otherwise. */
TgEXTN PREMM_API TgBOOL
tgMM_Query_Init( TgVOID );

/** @brief Standard Module function: Recall the amount of global (static) memory used by the module.
    @return Amount of global (static) memory used by the module. This is hard coded and thus, not explicitly correct. */
TgEXTN PREMM_API TgRSIZE
tgMM_Query_Fixed_Memory_Preload( TgVOID );

#if TgS_STAT__COMMON
/** @brief Support for Standard Module function: Store the current set of memory statistics into the provided data structure.
    @param [out] OUT0 Pointer to a data structure to hold the current value of the allocator specific stats.
    @return success if it was possible to acquire the statistics and fail otherwise. */
TgEXTN PREMM_API TgRESULT
tgMM_Query_Stats( STg2_MM_Preload_Stats_P OUT0 );

/** @brief Support for Standard Module function: Output the allocator specific stats.
    @param [in,out] ARG0 Pointer to a print function.
    @param [in,out] ARG1 Pointer to an output object. */
TgEXTN PREMM_API TgVOID
tgMM_Stats_Allocator( TgRSIZE (*ARG0)( STg2_Output_PC TgANALYSIS_NO_NULL, TgCHAR_U8_CPC TgANALYSIS_NO_NULL, ... ), STg2_Output_PC ARG1 );
/*# TgS_STAT__COMMON */
#endif

/** @brief Standard Module function: Recall the amount of global (static) memory used by the module.
    @return Amount of global (static) memory used by the module. This is hard coded and thus, not explicitly correct. */
TgEXTN TgATTRIBUTE_NO_DISCARD PREMM_API TgBOOL
tgMM_OS__Preload_Malloc_Redirected( TgVOID ) TgATTRIBUTE_NO_EXCEPT;

/** @} TGS_COMMON_MEMORY_MGR_MODULE */

/** @addtogroup TGS_COMMON_MEMORY_MGR */
/** @{ */

/** @brief Return the memory page size used by the manager
    @return The memory page size used by the manager */
TgEXTN PREMM_API TgRSIZE
tgMM_Page_Size( TgVOID );

/** @brief Register an allocator for use through the memory manager
    @param [in] ARG0 The allocator enumeration to be associated with the allocator
    @param [in] ARG1 Definition of a memory allocator */
TgEXTN PREMM_API TgVOID
tgMM_Register_Allocator(
    ETgMM_ALLOCATOR_C ARG0, STg2_MM_MGR_P ARG1 );

/** @brief Register an allocator for use through the memory manager
    @param [in] ARG0 The allocator enumeration to be associated with the allocator */
TgEXTN PREMM_API TgBOOL
tgMM_Is_Allocator_Registered(
    ETgMM_ALLOCATOR_C ARG0 );

/** @brief Return all thread local resources back to global management */
TgEXTN PREMM_API TgVOID
tgMM_Free_Thread_Local( TgVOID ) TgATTRIBUTE_NO_EXCEPT;

/** @brief Return the size of the memory region that was allocated beginning at ARG1.
    @param [in] ARG0 Memory allocator to be used for the function call.
    @param [in] ARG1 Pointer to the start of a region of memory that was allocated.
    @return The size of the memory region that was allocated beginning at ARG. */
TgEXTN PREMM_API TgRSIZE
tgMM_Size(
    ETgMM_ALLOCATOR_C ARG0, TgVOID_CPC ARG1 );

/** @brief Allocate a region of memory (size ARG1).
    @param [in] ARG0 Memory allocator to be used for the function call.
    @param [in] ARG1 Size of the region to allocate.
    @param [in] ARG2 Alignment for the allocation.
    @return Pointer to the allocated memory region on success and nullptr otherwise. */
TgEXTN PREMM_API TgVOID_P
tgMM_Malloc(
    ETgMM_ALLOCATOR_C ARG0, TgRSIZE_C ARG1, TgRSIZE_C ARG2 );

/** @brief Retrieve the exact amount of memory to allocate in a call to Reserve given the desired amount of memory in ARG0. @return see brief.
    @param [in] ARG0 Size of the desired usable amount of memory to allocate. */
TgEXTN PREMM_API TgRSIZE
tgMM_Required_Virtual_Size( 
    TgRSIZE_C ARG0 );

/** @brief Reserves a memory address range (of size ARG1). Virtual memory operations are always done aligned to the memory page size and number of pages.
    @param [in] ARG0 Memory allocator to be used for the function call.
    @param [in] ARG1 Size of the region to reserve.
    @return Pointer to the reserved memory region on success and nullptr otherwise. */
TgEXTN PREMM_API TgVOID_P
tgMM_Reserve(
    ETgMM_ALLOCATOR_C ARG0, TgRSIZE_C ARG1 );

/** @brief Commits ARG2 amount of memory from a reserved range.
    @param [in] ARG0 Memory allocator to be used for the function call.
    @param [in] ARG1 Pointer to the start of a reserved region, or null for a new allocation.
    @param [in] ARG2 Offset from the pointer base to the start of the region to commit.
    @param [in] ARG3 Size of the region to commit.
    @return Pointer to the start of the region committed and nullptr otherwise. */
TgEXTN PREMM_API TgVOID_P
tgMM_Commit(
    ETgMM_ALLOCATOR_C ARG0, TgVOID_P TgANALYSIS_OK_NULL ARG1, TgRSIZE_C ARG2, TgRSIZE_C ARG3 );

/** @brief Frees all resources used by the allocation starting at ARG1.
    @param [in] ARG0 Memory allocator to be used for the function call.
    @param [in] ARG1 Pointer to the start of a region of memory that was reserved. */
TgEXTN PREMM_API TgVOID
tgMM_Free(
    ETgMM_ALLOCATOR_C ARG0, TgVOID_PC TgANALYSIS_NO_NULL ARG1 );

/** @brief Reallocate the memory at ARG1 to a size of ARG2.
    @param [in] ARG0 Memory allocator to be used for the function call.
    @param [in] ARG1 Pointer to the start of the original region of memory.
    @param [in] ARG2 Size of the new memory region.
    @param [in] ARG3 Alignment for the new memory region.
    @return Pointer to the start of the region allocated and nullptr otherwise. */
TgEXTN PREMM_API TgVOID_P
tgMM_Realloc(
    ETgMM_ALLOCATOR_C ARG0, TgVOID_PC TgANALYSIS_OK_NULL ARG1, TgRSIZE_C ARG2, TgRSIZE_C ARG3 );

/** @} TGS_COMMON_MEMORY_MGR */


/* =============================================================================================================================================================================== */
#endif
