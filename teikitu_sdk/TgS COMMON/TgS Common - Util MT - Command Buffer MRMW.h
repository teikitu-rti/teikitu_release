/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Util MT - Command Buffer MRMW.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.21 | »GUID« AEEC8393-9780-4ECA-918D-E3E11F7E2744 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_UTIL_MT_COMMAND_BUFFER_MRMW_H)
#define TGS_COMMON_UTIL_MT_COMMAND_BUFFER_MRMW_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  DOXYGEN                                                                                                                                                                        */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @defgroup TGS_COMMON_UTIL_MT_COMMAND_BUFFER_MRMW Command Buffer of a Function Pointer and arbitrary sized 16 byte aligned data, Multiple Readers and Multiple Writers
    @ingroup TGS_COMMON_UTILITY_MT
*/


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Types                                                                                                                                                                   */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TgTYPE_UNION(STg2_UT__CMD_BUF__INDEX,)
{
    TgUINT_E64                                  m_uiREQ_NBY;
    struct
    {
        TgUINT_E32                                  m_nuiRequested; /**< Number of commands that have started the queuing process. */
        TgUINT_E32                                  m_nbyUsed; /**< Number of bytes that are used for the buffer with the memory manager. */
    };
};

typedef TgVOID (*TgFCN_CMD_FUNCTION)( TgVOID_CPC, TgRSIZE_C );
TgTYPE_STRUCT(STg2_UT__CMD_BUF__CMD, )
{
    TgALIGN(16) TgFCN_CMD_FUNCTION              m_pfnCommand;
    TgRSIZE                                     m_nbyParam;
};

TgTYPE_STRUCT(STg2_UT__CMD_BUF,) /**< Command Buffer */
{
    TgVOID_P                                    m_pBuffer; /**< Pointer to the buffer. */
    TgUINT_E64_A                                m_uiREQ_NBY; /**< Aggregate of number of requests and number of bytes used. */
    TgUINT_E32_A                                m_nuiCompleted; /**< Number of queue requests that have been completed. */
    TgUINT_E32                                  m_nbyMax; /**< Number of bytes that are allocated for the buffer with the memory manager. */
};
TgCOMPILER_ASSERT(0 == sizeof(STg2_UT__CMD_BUF__CMD) % 16,0);




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/** @addtogroup TGS_COMMON_UTIL_MT_COMMAND_BUFFER_MRMW */
/** @{ */

/** @brief Initialize a management object with ARG1 number of reserved bytes. @return Result Code.
    @param [out] OUT0 Pointer to a management object for the command buffer.
    @param [in] ARG1 Number of bytes to reserve for the command buffer. */
TgINLINE TgRESULT
tgCM_UT__CMD_BUF__Init(
    STg2_UT__CMD_BUF_PCU TgANALYSIS_NO_NULL OUT0, TgUINT_E32_C ARG1 );

/** @brief Return the number of elements being used. @return Result Code.
    @param [in,out] ARG Pointer to a management object for the command buffer. */
TgINLINE TgRESULT
tgCM_UT__CMD_BUF__Free(
    STg2_UT__CMD_BUF_PCU TgANALYSIS_NO_NULL ARG );

/** @brief Return the number of elements being used
    @param [in,out] ARG Pointer to a management object for the command buffer.
    @return The number of bytes that are committed for the command buffer. */
TgINLINE TgRSIZE
tgCM_UT__CMD_BUF__Query_Used_Size(
    STg2_UT__CMD_BUF_PCU TgANALYSIS_NO_NULL ARG );

/** @brief Return the number of free elements remaining for the ring buffer
    @param [in,out] ARG Pointer to a management object for the command buffer.
    @return The number of committed bytes not used by the command buffer. */
TgINLINE TgRSIZE
tgCM_UT__CMD_BUF__Query_Free_Size(
    STg2_UT__CMD_BUF_PCU TgANALYSIS_NO_NULL ARG );

/** @brief Return the number of elements being managed*/
/** @param [in,out] ARG Pointer to a management object for the command buffer.
    @return The number of bytes reserved for the command buffer. */
TgINLINE TgSIZE_ALL
tgCM_UT__CMD_BUF__Query_Max_Size(
    STg2_UT__CMD_BUF_PCU TgANALYSIS_NO_NULL ARG );

/** @brief Acquire the next index for the producer (writer)
    @param [in,out] ARG0 Pointer to a management object for the command buffer.
    @param [in] ARG1 Function pointer to be called.
    @param [in] ARG2 Integer size of the data structure to be copied and passed to the function (Arg1).
    @param [in] ARG3 Pointer to the data to be copied (function parameters).
    @return The next index for an element to be written */
TgINLINE TgRESULT
tgCM_UT__CMD_BUF__Queue_Command(
    STg2_UT__CMD_BUF_PCU TgANALYSIS_NO_NULL ARG0, TgFCN_CMD_FUNCTION TgANALYSIS_NO_NULL ARG1, TgRSIZE_C ARG2, TgVOID_CPC TgANALYSIS_NO_NULL ARG3 );

/** @brief Execute all of the functions added to the command buffer. NOTE: ASSUMES that the caller prevents additional requests during this period. Will reset at end of execution.
    @param [in,out] ARG Pointer to a management object for the command buffer */
TgINLINE TgVOID
tgCM_UT__CMD_BUF__Execute(
    STg2_UT__CMD_BUF_PCU TgANALYSIS_NO_NULL ARG );

/** @} TGS_COMMON_UTIL_MT_COMMAND_BUFFER_MRMW */


/* =============================================================================================================================================================================== */
#endif
