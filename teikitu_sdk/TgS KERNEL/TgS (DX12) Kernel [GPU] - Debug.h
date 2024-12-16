/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (DX12) Kernel - Debug [GPU].h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
#if !defined(TGS_DX12_KERNEL_DEBUG_GPU_H)
#define TGS_DX12_KERNEL_DEBUG_GPU_H
#pragma once

#if !defined(TGS_DX12_KERNEL_TYPE_GPU_H)
#include "TgS KERNEL/TgS (DX12) Kernel [GPU] - Type.h"
#endif


/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Constants                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- PIX for Windows ---------------------------------------------------------------------------------------------------------------------------------------------------------- */

/* MSFT did not bother creating a pix header that worked with C, and so we will have to ignore their implementation.*/

static const UINT                           PIX_EVENT_ANSI_VERSION = 1;

TgEXTN TgVOID                               ( __stdcall *g_pfnPIXBeginEventOnCommandList )( ID3D12GraphicsCommandList_P, UINT64, TgCHAR_NC_CP );
TgEXTN TgVOID                               ( __stdcall *g_pfnPIXEndEventOnCommandList )( ID3D12GraphicsCommandList_P );
TgEXTN TgVOID                               ( __stdcall *g_pfnPIXSetMarkerOnCommandList )( ID3D12GraphicsCommandList_P, UINT64, TgCHAR_NC_CP );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Data                                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- PIX for Windows ---------------------------------------------------------------------------------------------------------------------------------------------------------- */

/* MSFT did not bother creating a pix header that worked with C, and so we will have to ignore their implementation.*/

TgINLINE TgVOID PIXBeginEvent_ThatWorksInC_ID3D12GraphicsCommandList( ID3D12GraphicsCommandList8_P ARG0, TgATTRIBUTE_UNUSED UINT64 ARG1, TgCHAR_NC_CPC ARG2 );
TgINLINE TgVOID PIXEndEvent_ThatWorksInC_ID3D12GraphicsCommandList( ID3D12GraphicsCommandList8_P ARG0 );
TgINLINE TgVOID PIXSetMarker_ThatWorksInC_ID3D12GraphicsCommandList( ID3D12GraphicsCommandList8_P ARG0, TgCHAR_NC_CPC ARG1 );

TgINLINE TgVOID PIXBeginEvent_ThatWorksInC_ID3D12CommandQueue( ID3D12CommandQueue_P ARG0, TgATTRIBUTE_UNUSED UINT64 ARG1, TgCHAR_NC_CPC ARG2 );
TgINLINE TgVOID PIXEndEvent_ThatWorksInC_ID3D12CommandQueue( ID3D12CommandQueue_P ARG0 );




/* =============================================================================================================================================================================== */
#endif
