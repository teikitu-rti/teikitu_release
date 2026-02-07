/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common -- UTIL.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON____UTIL_INL)
#define TGS_COMMON____UTIL_INL

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Make sure the header has been included */
#include "TgS COMMON/TgS Common -- UTIL.h"

/* Multithreaded locks (gates) */
#include "TgS COMMON/TgS Common - Util MT - Spin Lock.inl"
#include "TgS COMMON/TgS Common - Util MT - Reader Writer Lock.inl"

/* Multithreaded containers */
#include "TgS COMMON/TgS Common - Util MT - Hash Table.inl"
#include "TgS COMMON/TgS Common - Util MT - LA Ring Buffer SRSW.inl"
#include "TgS COMMON/TgS Common - Util MT - Stack.inl"

/* Multithreaded types */
#include "TgS COMMON/TgS Common - Util MT - Command Buffer MRMW.inl"
#include "TgS COMMON/TgS Common - Util MT - Profile Sample.inl"

/* Single threaded containers */
#include "TgS COMMON/TgS Common - Util ST - Array.inl"
#include "TgS COMMON/TgS Common - Util ST - Colour.inl"
#include "TgS COMMON/TgS Common - Util ST - List.inl"
#include "TgS COMMON/TgS Common - Util ST - Queue.inl"
#include "TgS COMMON/TgS Common - Util ST - String.inl"

/* Single thread types */
#include "TgS COMMON/TgS Common - Util ST - Colour.h"


/* =============================================================================================================================================================================== */
#endif
