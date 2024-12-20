/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (POSIX) Common - Base - Type [MT].h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_POSIX_COMMON_BASE_TYPE_MT_H)
#define TGS_POSIX_COMMON_BASE_TYPE_MT_H
#pragma once


/* == Common ===================================================================================================================================================================== */
/* MARK: No Unit Test Required                                                                                                                                                     */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Types                                                                                                                                                                   */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- STg1_MT_MX --------------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_STRUCT(STg1_MT_MX,)
{
    pthread_mutex_t                             m_hMutex;
};

#if defined(TgBUILD_HOST_SYSTEM__HMAC) && TgBUILD_HOST_SYSTEM__HMAC
#define SIZE_STg1_MT_MX 64
#else
#define SIZE_STg1_MT_MX 40
#endif

TgCOMPILER_ASSERT( SIZE_STg1_MT_MX == sizeof( STg1_MT_MX ), 0 );


/* ---- STg1_MT_SM --------------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_STRUCT(STg1_MT_SM,)
{
    sem_t                                       *m_hSemaphore;
    TgCHAR_U8                                   m_mbzName[KTgMAX_SEMAPHORE_NAME];
};
#define SIZE_STg1_MT_SM 24
TgCOMPILER_ASSERT( SIZE_STg1_MT_SM == sizeof( STg1_MT_SM ), 0 );


/* =============================================================================================================================================================================== */
#endif

