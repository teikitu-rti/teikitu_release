/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Preload - Internal.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_PRELOAD_INTERNAL_H)
#define TGS_COMMON_PRELOAD_INTERNAL_H

//#include "TgS Common - Internal.h" /**< The global thread variables are shared between the two projects. */

#define TgCOMPILE__GENERATE_LIST_OF_LITERALS
#define ATOMIC_128BIT_SIZE 16
#undef ANDROID

#include "TgS COMMON/TgS Common -- VERSION.h"
#include "TgS COMMON/TgS Common -- BASE.h"

#include "TgS COMMON/TgS Common - Util MT - Spin Lock.h"
#include "TgS COMMON/TgS Common - Util MT - Reader Writer Lock.h"
#include "TgS COMMON/TgS Common - Util MT - Stack.h"
#include "TgS COMMON/TgS Common - Util ST - List.h"

#include "TgS COMMON/TgS Common - Global.h"
#include "TgS COMMON/TgS Common - Console.h"

#include "TgS COMMON/TgS Common - Preload - Mem MGR.h"

#if defined(TgBUILD_FEATURE__MIMALLOC_ALLOCATOR)
    #include "TgS COMMON/TgS Common - Mimalloc.h"
#endif

#include TgHEADER_OPERATING_SYSTEM(TgS,Common - Preload - Internal.h)

// Not all build flavors will include console functions.
#if !defined(tgCN_PrintF)
    #define TgBUILD_PRELOAD__HAS_CONSOLE
    TgEXTN TgVOID (*g_pfnCN_PrintF)( TgUINT_E32_C, TgCHAR_U8_CP NONULL, ... );
    #define tgCN_PrintF(...) if (g_pfnCN_PrintF) { g_pfnCN_PrintF(__VA_ARGS__); }
#endif

#include TgHEADER_COMPILER(TgS COMMON/TgS,Common - Base - API.inl)
#include "TgS COMMON/TgS Common - Base - API [Math].inl"

#include "TgS COMMON/TgS Common - Util MT - Spin Lock.inl"
#include "TgS COMMON/TgS Common - Util MT - Reader Writer Lock.inl"
#include "TgS COMMON/TgS Common - Util MT - Stack.inl"
#include "TgS COMMON/TgS Common - Util ST - List.inl"

TgEXTN TgVOID
tgMM_OS__Preload_Process_Init( TgVOID ) TgATTRIBUTE_NO_EXCEPT;

TgEXTN TgVOID CDECL
tgMM_OS__Preload_Process_Done( TgVOID ) TgATTRIBUTE_NO_EXCEPT;

/** @brief Standard Module function: First part of initialization process. Set the state of the module.
    @return Result Code. */
#if defined(TgBUILD_FEATURE__MALLOC_OVERRIDE)
TgEXTN TgRESULT
tgMM_Init_MGR( TgVOID );
#else
TgEXTN TgRESULT
tgMM_Init_MGR_Preload( TgVOID );
#endif

/** @brief Standard Module function: Final part of shutdown process. Release any remaining allocated memory, and reset the state of the module.
    @return Result Code. */
#if defined(TgBUILD_FEATURE__MALLOC_OVERRIDE)
TgEXTN TgRESULT
tgMM_Free_MGR( TgVOID );
#else
TgEXTN TgRESULT
tgMM_Free_MGR_Preload( TgVOID );
#endif

TgEXTN TgUINT_PTR_A                         g_xuiProcess_Init;
TgEXTN TgBOOL                               g_bOS_MM_Redirected;
TgEXTN TgUINT_E32                           g_uiOS_MM_Page_Size;

TgINLINE TgBOOL tgMM_OS__Preload_Process_Init_Complete( TgVOID )
{
    TgUINT_PTR                          uiInit;

    /* Quick check to make sure that we only run once. */
    if ((uiInit = TgSTD_ATOMIC(load_explicit)( &g_xuiProcess_Init, TgSTD_MEMORY_ORDER(relaxed) )) != 0)
    {
        while (uiInit != 2ULL)
        {
            tgTR_Pause();
            uiInit = TgSTD_ATOMIC(load_explicit)( &g_xuiProcess_Init, TgSTD_MEMORY_ORDER(relaxed) );
        }
        return true;
    };

    return false;
}



/* =============================================================================================================================================================================== */
#endif
