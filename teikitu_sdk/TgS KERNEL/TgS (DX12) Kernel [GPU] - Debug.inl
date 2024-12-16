/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (DX12) Kernel - Debug [GPU].inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
#if !defined(TGS_DX12_KERNEL_DEBUG_GPU_INL)
#define TGS_DX12_KERNEL_DEBUG_GPU_INL
#pragma once

#include "TgS (DX12) Kernel [GPU] - Debug.h"


/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- PIX for Windows ---------------------------------------------------------------------------------------------------------------------------------------------------------- */

/* MSFT did not bother creating a pix header that worked with C, and so we will have to ignore their implementation.*/

TgINLINE TgVOID PIXBeginEvent_ThatWorksInC_ID3D12GraphicsCommandList( ID3D12GraphicsCommandList8_P psDX12_Command_List, TgATTRIBUTE_UNUSED UINT64 ARG1, TgCHAR_NC_CPC pszPix_Marker )
{
    if (g_pfnPIXBeginEventOnCommandList)
        g_pfnPIXBeginEventOnCommandList( (ID3D12GraphicsCommandList_P)psDX12_Command_List, 0, pszPix_Marker );
}

TgINLINE TgVOID PIXEndEvent_ThatWorksInC_ID3D12GraphicsCommandList( ID3D12GraphicsCommandList8_P psDX12_Command_List )
{
    if (g_pfnPIXEndEventOnCommandList)
        g_pfnPIXEndEventOnCommandList( (ID3D12GraphicsCommandList_P)psDX12_Command_List );
}

TgINLINE TgVOID PIXSetMarker_ThatWorksInC_ID3D12GraphicsCommandList( ID3D12GraphicsCommandList8_P psDX12_Command_List, TgCHAR_NC_CPC pszPix_Marker )
{
    if (g_pfnPIXSetMarkerOnCommandList)
        g_pfnPIXSetMarkerOnCommandList( (ID3D12GraphicsCommandList_P)psDX12_Command_List, 0, pszPix_Marker );
}

TgINLINE TgVOID PIXBeginEvent_ThatWorksInC_ID3D12CommandQueue( ID3D12CommandQueue_P psDX12_Command_Queue, TgATTRIBUTE_UNUSED UINT64 ARG1, TgCHAR_NC_CPC pszPix_Marker )
{
    ID3D12CommandQueue_BeginEvent( psDX12_Command_Queue, PIX_EVENT_ANSI_VERSION, pszPix_Marker, (UINT)(strlen( pszPix_Marker ) + 1) );
}

TgINLINE TgVOID PIXEndEvent_ThatWorksInC_ID3D12CommandQueue( ID3D12CommandQueue_P psDX12_Command_Queue )
{
    ID3D12CommandQueue_EndEvent( psDX12_Command_Queue );
}




/* =============================================================================================================================================================================== */
#endif
