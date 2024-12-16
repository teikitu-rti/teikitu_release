/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common -- UTIL.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_UTIL_H)
#define TGS_COMMON_UTIL_H
#pragma once

#define ATOMIC_128BIT_SIZE 16

/* Single threaded containers */
#include "TgS COMMON/TgS Common - Util ST - Array.h"
#include "TgS COMMON/TgS Common - Util ST - List.h"
#include "TgS COMMON/TgS Common - Util ST - Queue.h"
#include "TgS COMMON/TgS Common - Util ST - String.h"

/* Single thread types */
#include "TgS COMMON/TgS Common - Util ST - Colour.h"

/* Multithreaded locks (gates) */
#include "TgS COMMON/TgS Common - Util MT - Spin Lock.h"
#include "TgS COMMON/TgS Common - Util MT - Reader Writer Lock.h"

/* Multithreaded containers */
#include "TgS COMMON/TgS Common - Util MT - Hash Table.h"
#include "TgS COMMON/TgS Common - Util MT - LA Ring Buffer SRSW.h"
#include "TgS COMMON/TgS Common - Util MT - Stack.h"

/* Multithreaded types */
#include "TgS COMMON/TgS Common - Util MT - Profile Sample.h"
#include "TgS COMMON/TgS Common - Util ST - Job.h"


/* == Common ===================================================================================================================================================================== */
/* MARK: No Unit Test Required                                                                                                                                                     */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  DOXYGEN                                                                                                                                                                        */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @defgroup TGS_COMMON_UTILITY Utility Functions
    @ingroup TGS_COMMON
*/

/** @defgroup TGS_COMMON_UTILITY_ST Single-thread Support
    @ingroup TGS_COMMON_UTILITY
*/

/** @defgroup TGS_COMMON_UTILITY_MT Multi-thread Support
    @ingroup TGS_COMMON_UTILITY
*/

/** @defgroup TGS_COMMON_UTILITY_MT_LOCK Synchronization Lock
    @ingroup TGS_COMMON_UTILITY_MT
*/


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TgEXTN TgVOID
tgUTM_Check_C11_Lock_Free_Status( TgVOID );


/* =============================================================================================================================================================================== */
#endif
