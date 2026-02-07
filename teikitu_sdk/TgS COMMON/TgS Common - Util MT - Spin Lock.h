/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Util MT - Spin Lock.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_UTIL_MT_SPIN_LOCK_H)
#define TGS_COMMON_UTIL_MT_SPIN_LOCK_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif


/* == Common ===================================================================================================================================================================== */
/* MARK: Unit Test Complete 00D008E0-5616-4AAF-8989-24865B450F52                                                                                                                   */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  DOXYGEN                                                                                                                                                                        */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @defgroup TGS_COMMON_UTIL_MT_SPINLOCK_LOCKFREE Standard Spin-lock
    @ingroup TGS_COMMON_UTILITY_MT_LOCK
*/

/** @defgroup TGS_COMMON_UTIL_MT_SPINLOCK_AND_COUNTER Spin-lock with request counter
    @ingroup TGS_COMMON_UTILITY_MT_LOCK
    @details Spin-lock that counts number of access requests while locked
*/

/** @defgroup TGS_COMMON_UTIL_MT_SPINLOCK_WITH_ID Spin-lock combined with an identifier check
    @ingroup TGS_COMMON_UTILITY_MT_LOCK
    @details Operations will only succeed if the identifier also compares to be true
*/


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Types                                                                                                                                                                   */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- STg2_UT_LF__SN ----------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_UNION(STg2_UT_ST__SRV_REQ,)
{
    TgUINT_E64                                  m_uiSRV_REQ;
    struct
    {
        TgUINT_E32                                  m_nuiServed;
        TgUINT_E32                                  m_uiRequest;
    };
};

TgTYPE_UNION(STg2_UT_LF__SN,)
{
    TgUINT_E64_A                                m_uiSRV_REQ;

    TgCXX_CONSTRUCTOR(STg2_UT_LF__SN(): m_uiSRV_REQ(0) {})
};

TgTYPE_STRUCT(STg2_UT_LF_ISO__SN, )
{
    TgALIGN(TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE)
    STg2_UT_LF__SN                              m_sLock;
#if 0 != (248 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE)
    TgUINT_E08                                  m_uiPad[248 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE];
#endif
};

TgCOMPILER_ASSERT( 8 == sizeof( STg2_UT_ST__SRV_REQ ), 0 );
TgCOMPILER_ASSERT( 8 == sizeof( STg2_UT_LF__SN ), 0 );
TgCOMPILER_ASSERT( TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE == sizeof( STg2_UT_LF_ISO__SN ), 0 );


/* ---- STg2_UT_LF__SN_CNT ------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_UNION(STg2_UT_ST__SRV_REQ_CNT,)
{
    TgUINT_E64                                  m_uiSRV_REQ_CNT;
    struct
    {
        TgUINT_E16                                  m_nuiServed;
        TgUINT_E16                                  m_uiRequest;
        TgUINT_E32                                  m_nuiTested;
    };
};

TgTYPE_STRUCT(STg2_UT_LF__SN_CNT,)
{
    TgUINT_E64_A                                m_uiSRV_REQ_CNT;
};

TgTYPE_STRUCT(STg2_UT_LF_ISO__SN_CNT, )
{
    TgALIGN(TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE)
    STg2_UT_LF__SN_CNT                          m_sLock;
#if 0 != (248 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE)
    TgUINT_E08                                  m_uiPad[248 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE];
#endif
};

TgCOMPILER_ASSERT( 8 == sizeof( STg2_UT_ST__SRV_REQ_CNT ), 0 );
TgCOMPILER_ASSERT( 8 == sizeof( STg2_UT_LF__SN_CNT ), 0 );
TgCOMPILER_ASSERT( TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE == sizeof( STg2_UT_LF_ISO__SN_CNT ), 0 );


/* ---- STg2_UT_LF__SN_ID -------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_STRUCT(STg2_UT_ST__SRV_REQ_ID, )
{
    union
    {
        TgUINT_E64                              m_uiSRV_REQ;
        struct
        {
            TgUINT_E32                                  m_nuiServed;
            TgUINT_E32                                  m_uiRequest;
        };
    };
    union
    {
        TgUINT_E64                              m_uiKI;
        struct
        {
            TgUINT_E32                                  m_uiK;
            TgUINT_E32                                  m_uiI;
        };
    };
};
TgTYPE_MODIFIER_ATOMIC(STg2_UT_ST__SRV_REQ_ID);
TgCOMPILER_ASSERT( 16 == sizeof( STg2_UT_ST__SRV_REQ_ID_A ), 0 );

TgMSVC_WARN_DISABLE_PUSH(4820)

TgTYPE_STRUCT(STg2_UT_LF__SN_ID, )
{
    TgALIGN(16) STg2_UT_ST__SRV_REQ_ID_A        m_sSRV_REQ_ID;
};
TgCOMPILER_ASSERT( 16 == sizeof( STg2_UT_LF__SN_ID ), 0 );

TgTYPE_STRUCT(STg2_UT_LF_ISO__SN_ID, )
{
    TgALIGN(TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE)
    STg2_UT_LF__SN_ID                           m_sLock;
#if 0 != (240 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE)
    TgUINT_E08                                  m_uiPad0[240 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE];
#endif
};

TgMSVC_WARN_DISABLE_POP(4820)




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- STg2_UT_LF_SN ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/** @addtogroup TGS_COMMON_UTIL_MT_SPINLOCK_LOCKFREE */
/** @{ */

/** @brief Initialize a spin lock (non reentrant), starting in a signaled state
    @param [out] OUT Pointer to a spin lock object
    @return Result code, KTgS_OK on success */
TgINLINE TgRESULT
tgCM_UT_LF__SN__Init(
    STg2_UT_LF__SN_PCU OUT );

/** @brief Free all resources used by the object and perform some sanity checks
    @param [in,out] ARG Pointer to a spin lock object */
TgINLINE TgVOID
tgCM_UT_LF__SN__Free_Unsafe(
    STg2_UT_LF__SN_PCU ARG );


/** @brief Continuously attempt to acquire the lock until successful, yielding the thread between each attempt
    @param [in,out] ARG Pointer to a spin lock object */
TgINLINE TgVOID
tgCM_UT_LF__SN__Lock_Yield(
    STg2_UT_LF__SN_PCU ARG );

/** @brief Continuously attempt to acquire the lock until successful, pausing the thread between each attempt
    @param [in,out] ARG Pointer to a spin lock object */
TgINLINE TgVOID
tgCM_UT_LF__SN__Lock_Spin(
    STg2_UT_LF__SN_PCU ARG );

/** @brief Attempt to acquire the lock
    @param [in,out] ARG Pointer to a spin lock object
    @return Result code, KTgS_OK on success */
TgINLINE TgRESULT
tgCM_UT_LF__SN__Lock_Test(
    STg2_UT_LF__SN_PCU ARG );


/** @brief Signal the semaphore
    @param [in,out] ARG Pointer to a spin lock object */
TgINLINE TgVOID
tgCM_UT_LF__SN__Signal(
    STg2_UT_LF__SN_PCU ARG );

/** @} TGS_COMMON_UTIL_MT_SPINLOCK_LOCKFREE */


/* ---- STg2_UT_LF_SN_CNT -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/** @addtogroup TGS_COMMON_UTIL_MT_SPINLOCK_AND_COUNTER */
/** @{ */

/** @brief Initialize a specialized semaphore object used in the kernel used to track multiple producers and a single consumer
    @param [out] OUT Pointer to a spin lock counting object
    @return Result code, KTgS_OK on success */
TgINLINE TgRESULT
tgCM_UT_LF__SN_CNT__Init(
    STg2_UT_LF__SN_CNT_PCU OUT );

/** @brief Free all resources used by the object and perform some sanity checks
    @param [in,out] ARG Pointer to a spin lock counting object */
TgINLINE TgVOID
tgCM_UT_LF__SN_CNT__Free_Unsafe(
    STg2_UT_LF__SN_CNT_PCU ARG );


/** @brief Attempt to acquire the lock, and on failure increment an internal counter
    @param [in,out] ARG Pointer to a spin lock counting object
    @return Result code, KTgS_OK on success */
TgINLINE TgRESULT
tgCM_UT_LF__SN_CNT__Lock_Or_Increment_Count(
    STg2_UT_LF__SN_CNT_PCU ARG );

/** @brief Signal the spin lock if the internal counter is at zero, reset the counter and fail otherwise
    @param [in,out] ARG Pointer to a spin lock counting object
    @return 0 on success or the total count that had been stored  */
TgINLINE TgUINT_E32
tgCM_UT_LF__SN_CNT__Signal_Or_Reset_Count(
    STg2_UT_LF__SN_CNT_PCU ARG );

/** @} TGS_COMMON_UTIL_MT_SPINLOCK_AND_COUNTER */


/* ---- STg2_UT_LF_SN_ID --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/** @addtogroup TGS_COMMON_UTIL_MT_SPINLOCK_WITH_ID */
/** @{ */

/** @brief Initialize a spin lock (non reentrant), starting in a signaled state with an invalid ID
    @param [out] OUT0 Pointer to a spin lock object
    @param [in] ARG1 Initial value for the lock's identifier
    @return Result code, KTgS_OK on success */
TgINLINE TgRESULT
tgCM_UT_LF__SN_ID__Init(
    STg2_UT_LF__SN_ID_PCU OUT0, TgUINT_E64_C ARG1 );

/** @brief Free all resources used by the object and perform some sanity checks
    @param [in,out] ARG Pointer to a spin lock object */
TgINLINE TgVOID
tgCM_UT_LF__SN_ID__Free_Yield(
    STg2_UT_LF__SN_ID_PCU ARG );

/** @brief Free all resources used by the object and perform some sanity checks
    @param [in,out] ARG Pointer to a spin lock object */
TgINLINE TgVOID
tgCM_UT_LF__SN_ID__Free_Spin(
    STg2_UT_LF__SN_ID_PCU ARG );

/** @brief Free all resources used by the object and perform some sanity checks
    @param [in,out] ARG Pointer to a spin lock object */
TgINLINE TgVOID
tgCM_UT_LF__SN_ID__Free_Unsafe(
    STg2_UT_LF__SN_ID_PCU ARG );


/** @brief Acquire the lock, spinning with a yield until complete, and fail if ARG1 at any time fails to match the lock's identifier
    @param [in,out] ARG0 Pointer to a spin lock object
    @param [in] ARG1 Additional value that will need to match the lock's identifier
    @return Result code, KTgS_OK on success */
TgINLINE TgRESULT
tgCM_UT_LF__SN_ID__Lock_Yield(
    STg2_UT_LF__SN_ID_PCU ARG0, TgUINT_E64_C ARG1 );

/** @brief Acquire the lock, spinning with a pause until complete, and fail if ARG1 at any time fails to match the lock's identifier
    @param [in,out] ARG0 Pointer to a spin lock object
    @param [in] ARG1 Additional value that will need to match the lock's identifier
    @return Result code, KTgS_OK on success */
TgINLINE TgRESULT
tgCM_UT_LF__SN_ID__Lock_Spin(
    STg2_UT_LF__SN_ID_PCU ARG0, TgUINT_E64_C ARG1 );

/** @brief Attempt to acquire the lock if ARG1 matches the locks identifier
    @param [in,out] ARG0 Pointer to a spin lock object
    @param [in] ARG1 Additional value that will need to match the lock's identifier
    @return Result code, KTgS_OK on success */
TgINLINE TgRESULT
tgCM_UT_LF__SN_ID__Lock_Test(
    STg2_UT_LF__SN_ID_PCU ARG0, TgUINT_E64_C ARG1 );


/** @brief Signal the semaphore, it is assumed that the identifier will not be invalidated without locking
    @param [in,out] ARG0 Pointer to a spin lock object
    @param [in] ARG1 Additional value that will need to match the lock's identifier
    @return Result code, KTgS_OK on success */
TgINLINE TgRESULT
tgCM_UT_LF__SN_ID__Invalidate_Index_Yield(
    STg2_UT_LF__SN_ID_PCU ARG0, TgUINT_E64_C ARG1 );

/** @brief Signal the semaphore, it is assumed that the identifier will not be invalidated without locking
    @param [in,out] ARG0 Pointer to a spin lock object
    @param [in] ARG1 Additional value that will need to match the lock's identifier
    @return Result code, KTgS_OK on success */
TgINLINE TgRESULT
tgCM_UT_LF__SN_ID__Invalidate_Index_Spin(
    STg2_UT_LF__SN_ID_PCU ARG0, TgUINT_E64_C ARG1 );

/** @brief Signal the semaphore, it is assumed that the identifier will not be invalidated without locking
    @param [in,out] ARG Pointer to a spin lock object */
TgINLINE TgVOID
tgCM_UT_LF__SN_ID__Signal(
    STg2_UT_LF__SN_ID_PCU ARG );

/** @} TGS_COMMON_UTIL_MT_SPINLOCK_WITH_ID */


/* =============================================================================================================================================================================== */
#endif
