/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Util MT - LA Ring Buffer SRSW.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_UTIL_MT_LA_RING_BUFFER_SRSW_H)
#define TGS_COMMON_UTIL_MT_LA_RING_BUFFER_SRSW_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif


/* == Common ===================================================================================================================================================================== */
/* MARK: Unit Test Complete 00D008E0-5616-4AAF-8989-24865B450F52                                                                                                                   */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  DOXYGEN                                                                                                                                                                        */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @defgroup TGS_COMMON_UTIL_MT_LA_RING_BUFFER_SRSW Look Aside Ring Buffer, Single Reader and Single Writer
    @ingroup TGS_COMMON_UTILITY_MT
*/


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Types                                                                                                                                                                   */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TgTYPE_STRUCT(STg2_UT_LF__LA_RB_SRSW, ) /**< Look Aside, Ring Buffer, Single Reader, Single Writer */
{
    TgALIGN(TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE)
    TgRSIZE_A                                   m_nuiPushed;
    TgUINT_E08                                  m_uiPad0[248 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE];
    TgALIGN(TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE)
    TgRSIZE_A                                   m_nuiPopped;
    TgUINT_E08                                  m_uiPad1[248 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE];
    TgALIGN(TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE)
    TgRSIZE                                     m_uiMaxSize; /**< Stored as a bit shift value since buffer must be power of two */
    TgUINT_E08                                  m_uiPad2[248 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE];
};
TgCOMPILER_ASSERT( 4 == sizeof( TgSINT_E32 ), 0 );


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/** @addtogroup TGS_COMMON_UTIL_MT_LA_RING_BUFFER_SRSW */
/** @{ */

/** @brief Initialize a management object with ARG1 number of elements
    @param [out] OUT0 Pointer to a management object for the look aside ring buffer
    @param [in] ARG1 Number of elements in the ring buffer */
TgINLINE TgVOID
tgCM_UT_LF__LA_RB_SRSW__Init(
    STg2_UT_LF__LA_RB_SRSW_PCU OUT0, TgRSIZE_C ARG1 );


/** @brief Return the number of elements being used
    @param [in] ARG Pointer to a management object for the look aside ring buffer
    @return The number of elements being used */
TgINLINE TgRSIZE
tgCM_UT_LF__LA_RB_SRSW__Query_Used_Size(
    STg2_UT_LF__LA_RB_SRSW_PCU ARG );

/** @brief Return the number of free elements remaining for the ring buffer
    @param [in] ARG Pointer to a management object for the look aside ring buffer
    @return The number of free elements remaining in the ring buffer */
TgINLINE TgRSIZE
tgCM_UT_LF__LA_RB_SRSW__Query_Free_Size(
    STg2_UT_LF__LA_RB_SRSW_PCU ARG );

/** @brief Return the number of elements being managed*/
/** @param [in] ARG Pointer to a management object for the look aside ring buffer
    @return The number of elements being managed */
TgINLINE TgRSIZE
tgCM_UT_LF__LA_RB_SRSW__Query_Max_Size(
    STg2_UT_LF__LA_RB_SRSW_PCU ARG );


/** @brief Acquire the next index for the producer (writer)
    @param [in] ARG Pointer to a management object for the look aside ring buffer
    @return The next index for an element to be written */
TgINLINE TgRSIZE
tgCM_UT_LF__LA_RB_SRSW__Push_Next_Index(
    STg2_UT_LF__LA_RB_SRSW_PCU ARG );

/** @brief Increment the write index
    @param [in,out] ARG Pointer to a management object for the look aside ring buffer */
TgINLINE TgVOID
tgCM_UT_LF__LA_RB_SRSW__Push_Commit(
    STg2_UT_LF__LA_RB_SRSW_PCU ARG );

/** @brief Acquire the next index as the consumer (reader)
    @param [in] ARG Pointer to a management object for the look aside ring buffer
    @return The next index for an element to be read */
TgINLINE TgRSIZE
tgCM_UT_LF__LA_RB_SRSW__Pop_Next_Index(
    STg2_UT_LF__LA_RB_SRSW_PCU ARG );

/** @brief Increment the read index
    @param [in,out] ARG Pointer to a management object for the look aside ring buffer */
TgINLINE TgVOID
tgCM_UT_LF__LA_RB_SRSW__Pop_Commit(
    STg2_UT_LF__LA_RB_SRSW_PCU ARG );

/** @} TGS_COMMON_UTIL_MT_LA_RING_BUFFER_SRSW */


/* =============================================================================================================================================================================== */
#endif
