/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Util ST - Queue.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_UTIL_ST_QUEUE_H)
#define TGS_COMMON_UTIL_ST_QUEUE_H
#pragma once


/* == Common ===================================================================================================================================================================== */
/* MARK: Unit Test Complete 00D008E0-5616-4AAF-8989-24865B450F52                                                                                                                   */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  DOXYGEN                                                                                                                                                                        */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @defgroup TGS_COMMON_UTIL_ST_QUEUE Queue Container
    @ingroup TGS_COMMON_UTILITY_ST
*/


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Types                                                                                                                                                                   */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TgTYPE_STRUCT(STg2_UT_ST__QU_Node,)
{
    STg2_UT_ST__QU_Node_P                       m_pNext_Node;
};

TgTYPE_STRUCT(STg2_UT_ST__QU,)
{
    STg2_UT_ST__QU_Node                         m_sNode;
    STg2_UT_ST__QU_Node_P                       m_psTail_Node;
};

TgCOMPILER_ASSERT( 8 == sizeof( STg2_UT_ST__QU_Node ), 1 );
TgCOMPILER_ASSERT( 16 == sizeof( STg2_UT_ST__QU ), 1 );


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- Queue -------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/** @addtogroup TGS_COMMON_UTIL_ST_QUEUE */
/** @{ */

/** @brief Initialize a queue object
    @param [out] OUT Pointer to a queue object
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgINLINE TgRESULT
tgCM_UT_ST__QU__Init(
    STg2_UT_ST__QU_PC OUT );

/** @brief Free all resources used by the object and perform some sanity checks
    @param [in,out] ARG Pointer to a queue object */
TgINLINE TgVOID
tgCM_UT_ST__QU__Free(
    STg2_UT_ST__QU_PC ARG );


/** @brief Enqueue the node at ARG1 to the queue at ARG0
    @param [in,out] ARG0 Pointer to a queue object
    @param [in] ARG1 Pointer to a queue node */
TgINLINE TgVOID
tgCM_UT_ST__QU__Enqueue(
    STg2_UT_ST__QU_PC ARG0, STg2_UT_ST__QU_Node_PC ARG1 );

/** @brief Merge the queues, where ARG1 is added to ARG0
    @param [in,out] ARG0 Pointer to a queue object
    @param [in] ARG1 Pointer to a queue object */
TgINLINE TgVOID
tgCM_UT_ST__QU__Merge(
    STg2_UT_ST__QU_PC ARG0, STg2_UT_ST__QU_PC ARG1 );

/** @brief Dequeue a node from the queue
    @param [in,out] ARG Pointer to a queue object
    @return Pointer to the node that was dequeued, and nullptr otherwise */
TgINLINE STg2_UT_ST__QU_Node_P
tgCM_UT_ST__QU__Dequeue(
    STg2_UT_ST__QU_PC ARG );


/** @brief Check to see if the queue object is empty
    @param [in] ARG Pointer to a queue object
    @return True if the queue is empty, and false otherwise */
TgINLINE TgBOOL
tgCM_UT_ST__QU__Is_Empty(
    STg2_UT_ST__QU_PC ARG );

/** @} TGS_COMMON_UTIL_ST_QUEUE */


/* =============================================================================================================================================================================== */
#endif
