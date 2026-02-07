/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Mimalloc - Internal.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.21 | »GUID« AEEC8393-9780-4ECA-918D-E3E11F7E2744 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_MIMALLOC_INTERNAL_H)
#define TGS_COMMON_MIMALLOC_INTERNAL_H

#define TgCOMPILE__GENERATE_LIST_OF_LITERALS
#define ATOMIC_128BIT_SIZE 16
#undef ANDROID

#include "TgS COMMON/TgS Common -- VERSION.h"
#include "TgS COMMON/TgS Common -- BASE.h"

#include "TgS COMMON/TgS Common - Global.h"
#include "TgS COMMON/TgS Common - Console.h"
#include "TgS COMMON/TgS Common - Preload - Mem MGR.h"
#include "TgS COMMON/TgS Common - Mimalloc.h"

// Not all build flavors will include console functions.
#if !defined(tgCN_PrintF)
    #define TgBUILD_MIMALLOC__HAS_CONSOLE
    TgEXTN TgVOID (*g_pfnCN_PrintF)( TgUINT_E32_C, TgCHAR_U8_CP TgANALYSIS_NO_NULL, ... );
    #define tgCN_PrintF(...) if (g_pfnCN_PrintF) { g_pfnCN_PrintF(__VA_ARGS__); }
#endif

TgCLANG_WARN_DISABLE_PUSH(reserved-identifier)
TgMSVC_WARN_DISABLE_PUSH(4820)
#include <mimalloc.h>
TgMSVC_WARN_DISABLE_POP(4820)
TgCLANG_WARN_DISABLE_POP(reserved-identifier)


/* =============================================================================================================================================================================== */
#endif
