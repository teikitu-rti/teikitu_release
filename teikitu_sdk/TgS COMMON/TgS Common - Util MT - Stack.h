/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Util MT - Stack.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_UTIL_MP_ST_H)
#define TGS_COMMON_UTIL_MP_ST_H
#pragma once


/* == Common ===================================================================================================================================================================== */
/* MARK: Unit Test Complete 00D008E0-5616-4AAF-8989-24865B450F52                                                                                                                   */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  DOXYGEN                                                                                                                                                                        */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @defgroup TGS_COMMON_UTIL_MT_STACK Stack Container
    @ingroup TGS_COMMON_UTILITY_MT
*/

    /** @defgroup TGS_COMMON_UTIL_MT_STACK_LOCKFREE Stack Container using Lock-free Synchronization
        @ingroup TGS_COMMON_UTIL_MT_STACK
        @note This implementation is not entirely "correct".  It can not guarantee perfect ordering.  Imagine two threads attempting an insert into the stack, with the first
        thread being the earlier arrival.  If the first thread were preempted during its insertion then the second thread would succeed in pushing onto the stack prior to the
        completion of the first thread.
    */

    /** @defgroup TGS_COMMON_UTIL_MT_STACK_MUTEX Stack Container using a Mutex
        @ingroup TGS_COMMON_UTIL_MT_STACK
    */


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Types                                                                                                                                                                   */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- STg2_UT_LF__ST ----------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_STRUCT(STg2_UT_ST__ST_Node,)
{
    TgVOID_P                                    m_pNext_Node;
};

typedef struct
{
    STg2_UT_ST__ST_Node_P                       m_pHead;
    TgRSIZE                                     m_uiTicket; /**< OP Count to avoid ABA issues */
} tagSTg2_UT_ST__PTR_TKT;
TgTYPE_DECLARE( tagSTg2_UT_ST__PTR_TKT, STg2_UT_ST__PTR_TKT );

TgMSVC_WARN_DISABLE_PUSH(4820)

TgTYPE_STRUCT(STg2_UT_LF__ST,)
{
    TgALIGN(16) STg2_UT_ST__PTR_TKT_A           m_sTop;
    TgCXX_CONSTRUCTOR(STg2_UT_LF__ST(): m_sTop() {})
};

TgTYPE_STRUCT(STg2_UT_LF_ISO__ST,)
{
    TgALIGN(TgCCL) STg2_UT_LF__ST               m_sStack;
    TgUINT_E08                                  m_uiPad[TgCCL - (ATOMIC_128BIT_SIZE % TgCCL)];
};

TgMSVC_WARN_DISABLE_POP(4820)

TgCOMPILER_ASSERT( 16 == sizeof( STg2_UT_ST__PTR_TKT ), 0 );
TgCOMPILER_ASSERT( 0 == sizeof( STg2_UT_LF_ISO__ST ) % TgCCL, 0 ) ;


/* ---- STg2_UT_MT__ST_MX -------------------------------------------------------------------------------------------------------------------------------------------------------- */

#define SIZE_STg2_UT_MT__ST_MX (SIZE_STg1_MT_MX + SIZE_STg1_MT_SM + TgBUILD_HARDWARE__POINTER_SIZE)

TgTYPE_STRUCT(STg2_UT_MT__ST_MX,)
{
    STg1_MT_MX                                  m_sLock;
    STg1_MT_SM                                  m_sStack_Count;
    STg2_UT_ST__ST_Node_P                       m_psTop_Node;
};

TgTYPE_STRUCT(STg2_UT_MT_ISO__ST_MX,)
{
    TgALIGN(TgCCL) STg2_UT_MT__ST_MX            m_sStack;
    TgUINT_E08                                  m_uiPad[TgCCL - (SIZE_STg2_UT_MT__ST_MX % TgCCL)];
};

TgCOMPILER_ASSERT( 0 == sizeof( STg2_UT_MT_ISO__ST_MX ) % TgCCL, 0 ) ;


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- Atomic Stack ------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/** @addtogroup TGS_COMMON_UTIL_MT_STACK_LOCKFREE */
/** @{ */

/** @brief Initialize a stack container
@param [out] OUT Pointer to a stack object */
TgINLINE TgVOID
tgCM_UT_LF__ST__Init(
    STg2_UT_LF__ST_PCU OUT );

/** @brief Initialize a stack container filled with the given stack nodes
@param [out] OUT0 Pointer to a stack object
@param [in,out] ARG1 Pointer to the beginning range of elements to place into the stack
@param [in,out] ARG2 Stride of the stack element
@param [in,out] ARG3 Number of elements in the memory range */
TgINLINE TgVOID
tgCM_UT_LF__ST__Init_PreLoad(
    STg2_UT_LF__ST_PCU OUT0, TgVOID_P ARG1, TgRSIZE_C ARG2, TgRSIZE_C ARG3 );

/** @brief Free all resources used by the object and perform some sanity checks
@param [in,out] ARG Pointer to a stack object */
TgINLINE TgVOID
tgCM_UT_LF__ST__Free(
    STg2_UT_LF__ST_PCU ARG );

/** @brief Insert the element at ARG1 at the top of the stack
@param [in,out] ARG0 Pointer to a stack object
@param [in] ARG1 Pointer to a stack element */
TgINLINE TgVOID
tgCM_UT_LF__ST__Push(
    STg2_UT_LF__ST_PCU ARG0, STg2_UT_ST__ST_Node_PCU ARG1 );

/** @brief Remove the top element from the stack, return it, if able to acquire the synchronization lock
@param [in,out] ARG Pointer to a stack object
@return The removed node or nullptr otherwise */
TgINLINE STg2_UT_ST__ST_Node_P
tgCM_UT_LF__ST__Pop(
    STg2_UT_LF__ST_PCU ARG );

/** @brief Remove the top element from the stack, return it, once the synchronization lock is acquired
@param [in,out] ARG Pointer to a stack object
@return The removed node or nullptr otherwise */
TgINLINE STg2_UT_ST__ST_Node_P
tgCM_UT_LF__ST__Pop_Wait_Yield(
    STg2_UT_LF__ST_PCU ARG );

/** @brief Remove the top element from the stack, return it, once the synchronization lock is acquired
@param [in,out] ARG Pointer to a stack object
@return The removed node or nullptr otherwise */
TgINLINE STg2_UT_ST__ST_Node_P
tgCM_UT_LF__ST__Pop_Wait_Spin(
    STg2_UT_LF__ST_PCU ARG );

/** @brief Return if the stack is empty
@param [in,out] ARG Pointer to a stack object
@return True if the stack is empty, and false otherwise */
TgINLINE TgBOOL
tgCM_UT_LF__ST__Is_Empty(
    STg2_UT_LF__ST_PCU ARG );

/** @brief Pop (clear) the entire stack returning the former stack head
@param [in,out] ARG Pointer to a stack object
@return The former head of the stack, and nullptr otherwise */
TgINLINE STg2_UT_ST__ST_Node_P
tgCM_UT_LF__ST__Release(
    STg2_UT_LF__ST_PCU ARG );

/** @brief Push (append) an entire list of notes [ARG1,ARG2) onto the stack
@param [in,out] ARG0 Pointer to a stack object
@param [in] ARG1 Pointer to start of region to merge
@param [in] ARG2 Pointer to end of region to merge */
TgINLINE TgVOID
tgCM_UT_LF__ST__Merge(
    STg2_UT_LF__ST_PCU ARG0, STg2_UT_ST__ST_Node_P ARG1, STg2_UT_ST__ST_Node_P ARG2 );

/** @} TGS_COMMON_UTIL_MT_STACK_LOCKFREE */


/* ---- Critical Section Stack --------------------------------------------------------------------------------------------------------------------------------------------------- */

#if TgCOMPILE__THREAD
/** @addtogroup TGS_COMMON_UTIL_MT_STACK_MUTEX */
/** @{ */

/** @brief Initialize a stack container and mutex for synchronization
@param [out] OUT0 Pointer to a stack object
@param [in] ARG1 Name for the operating system mutex */
TgINLINE TgVOID
tgCM_UT_MT__ST_MX__Init(
    STg2_UT_MT__ST_MX_PCU OUT0, TgCHAR_U8_CPCU ARG1 );

/** @brief Release the mutex and perform any needed validation
@param [in,out] ARG Pointer to a stack object */
TgINLINE TgVOID
tgCM_UT_MT__ST_MX__Free(
    STg2_UT_MT__ST_MX_PCU ARG );

/** @brief Insert the element at ARG1 at the top of the stack 
@param [in,out] ARG0 Pointer to a stack object
@param [in] ARG1 Pointer to a stack node */
TgINLINE TgVOID
tgCM_UT_MT__ST_MX__Push(
    STg2_UT_MT__ST_MX_PCU ARG0, STg2_UT_ST__ST_Node_PCU ARG1 );

/** @brief Remove the top element from the stack, return it, if able to acquire the synchronization lock
@param [in,out] ARG Pointer to a stack object
@return The removed node */
TgINLINE STg2_UT_ST__ST_Node_P
tgCM_UT_MT__ST_MX__Pop(
    STg2_UT_MT__ST_MX_PCU ARG );

/** @brief Remove the top element from the stack, return it, once the synchronization lock is acquired
@param [in,out] ARG Pointer to a stack object
@return The removed node */
TgINLINE STg2_UT_ST__ST_Node_P
tgCM_UT_MT__ST_MX__Pop_Wait_Block(
    STg2_UT_MT__ST_MX_PCU ARG );

/** @brief Return if the stack is empty
@param [in,out] ARG Pointer to a stack object
@return True if the stack is empty, and false otherwise */
TgINLINE TgBOOL
tgCM_UT_MT__ST_MX__Is_Empty(
    STg2_UT_MT__ST_MX_PCU ARG );

/** @} TGS_COMMON_UTIL_MT_STACK_MUTEX */


/*# TgCOMPILE__THREAD */
#endif


/* =============================================================================================================================================================================== */
#endif
