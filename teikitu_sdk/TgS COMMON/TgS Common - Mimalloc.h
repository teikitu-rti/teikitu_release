/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Mimalloc.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.21 | »GUID« AEEC8393-9780-4ECA-918D-E3E11F7E2744 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_MIMALLOC_H)
#define TGS_COMMON_MIMALLOC_H
#pragma once


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  API                                                                                                                                                                            */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#if defined(_Ring_0___TgS_COMMON__MIMALLOC)
    #define TgMIMALLOC_API TgDLL_EXPORT
#else
    #define TgMIMALLOC_API TgDLL_IMPORT
#endif


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* Mimalloc Allocator */

TgEXTN TgMIMALLOC_API TgRESULT
tgMM_MI__Init_MGR( TgVOID );

TgEXTN TgMIMALLOC_API TgRESULT
tgMM_MI__Free_MGR( TgVOID );

TgEXTN TgMIMALLOC_API TgRESULT
tgMM_MI__Size(
    TgUINT_E32_P TgANALYSIS_NO_NULL, TgUINT_E32_P TgANALYSIS_NO_NULL, TgVOID_CPC TgANALYSIS_NO_NULL );

TgEXTN TgMIMALLOC_API TgRESULT
tgMM_MI__Malloc(
    TgMEM_INFO_HEADER_P TgANALYSIS_NO_NULL, TgVOID_PP TgANALYSIS_NO_NULL, TgRSIZE_C, TgRSIZE_C );

TgEXTN TgMIMALLOC_API TgRESULT
tgMM_MI__Free(
    TgMEM_INFO_HEADER_P TgANALYSIS_NO_NULL, TgVOID_PC TgANALYSIS_NO_NULL );

TgEXTN TgMIMALLOC_API TgRESULT
tgMM_MI__Realloc(
    TgMEM_INFO_HEADER_P TgANALYSIS_NO_NULL, TgVOID_PP TgANALYSIS_NO_NULL, TgMEM_INFO_HEADER_P TgANALYSIS_NO_NULL, TgVOID_PC TgANALYSIS_NO_NULL, TgRSIZE_C, TgRSIZE_C );

#if TgS_STAT__COMMON

TgEXTN TgMIMALLOC_API TgVOID
tgMM_MI__Stats(
    TgRSIZE (*)( STg2_Output_PC TgANALYSIS_NO_NULL, TgCHAR_U8_CPC TgANALYSIS_NO_NULL, ... ), STg2_Output_PC TgANALYSIS_NO_NULL );

/*# TgS_STAT__COMMON */
#endif


/* Mimalloc Internal Functions */

TgEXTN TgMIMALLOC_API TgVOID
tgMM_MI__Internal__Process_Load( TgVOID );

TgEXTN TgMIMALLOC_API TgVOID
tgMM_MI__Internal__Process_Init( TgVOID );

TgEXTN TgMIMALLOC_API TgVOID
tgMM_MI__Internal__Thread_Done( TgVOID ) TgATTRIBUTE_NO_EXCEPT;

TgEXTN TgMIMALLOC_API TgVOID CDECL
tgMM_MI__Internal__Process_Done( TgVOID );

/** @brief Set an internal pointer to the console print function. */
TgEXTN TgMIMALLOC_API TgVOID
tgMM_MI_Set_CN_PrintF( TgVOID (*)( TgUINT_E32_C, TgCHAR_U8_CP TgANALYSIS_NO_NULL, ... ) );


/* Mimalloc Windows Specific Supprt Functions */
TgEXTN TgMIMALLOC_API TgRESULT
tgMM_MI__Malloc_Aligned_At(
    TgVOID_PP TgANALYSIS_NO_NULL, TgRSIZE_C, TgRSIZE_C, TgRSIZE_C );


/* =============================================================================================================================================================================== */
#endif
