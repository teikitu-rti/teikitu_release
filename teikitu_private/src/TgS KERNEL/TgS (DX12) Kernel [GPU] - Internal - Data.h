/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (DX12) Kernel - Internal - Data [GPU].h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
#if !defined(TGS_DX12_KERNEL_INTERNAL_DATA_GPU_H)
#define TGS_DX12_KERNEL_INTERNAL_DATA_GPU_H
#pragma once


/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Data                                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- GPI - API - External Functions and Objects ------------------------------------------------------------------------------------------------------------------------------- */

TgEXTN HRESULT                              (__stdcall *g_pfnDXGICreateDXGIFactory)( UINT, REFIID, TgVOID_PP );

TgEXTN HRESULT                              (__stdcall *g_pfnDXGIGetDebugInterface1)( UINT, REFIID, TgVOID_PP );

TgEXTN HRESULT                              (__stdcall* g_pfnD3D12SerializeVersionedRootSignature )( D3D12_VER_ROOT_SIG_DESC_CP, ID3DBlob_PP, ID3DBlob_PP );
TgEXTN HRESULT                              (__stdcall* g_pfnD3D12CreateVersionedRootSignatureDeserializer )( TgVOID_CP, TgRSIZE, REFIID, TgVOID_PP );
TgEXTN HRESULT                              (__stdcall* g_pfnD3D12CreateDevice)( IUnknown*, D3D_FEATURE_LEVEL, REFIID, TgVOID_PP );
TgEXTN HRESULT                              (__stdcall* g_pfnD3D12GetDebugInterface)( REFIID, TgVOID_PP );

/* Imported from lower level modules. */
TgEXTN TgVOID_P                             (__stdcall *g_pfnCreateEventEx)( LPSECURITY_ATTRIBUTES, TgOSCHAR_CP, DWORD, DWORD );
TgEXTN TgVOID_P                             (__stdcall *g_pfnCreateEvent)( LPSECURITY_ATTRIBUTES, BOOL, BOOL, TgOSCHAR_CP );
TgEXTN TgSINT_E32                           (__stdcall *g_pfnCloseHandle)( TgVOID_P );
TgEXTN DWORD                                (__stdcall *g_pfnWaitForSingleObjectEx)( TgVOID_P, DWORD, BOOL );

TgEXTN IDXGIFactory7                        *g_pDXGIFactory;


/* ---- GPU - Contexts ----------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgEXTN STg2_KN_GPU_EXT_CXT_HOST             g_sKN_GPU_EXT_CXT_HOST;

TgEXTN STg2_KN_GPU_EXT_CXT_DEVC             g_asKN_GPU_EXT_CXT_DEVC[KTgKN_GPU_MAX_DEVC_CONTEXT];
TgEXTN STg2_KN_GPU_EXT_CXT_EXEC             g_asKN_GPU_EXT_CXT_EXEC[KTgKN_GPU_MAX_EXEC_CONTEXT];
TgEXTN STg2_KN_GPU_EXT_CXT_SWAP             g_asKN_GPU_EXT_CXT_SWAP[KTgKN_GPU_MAX_SWAP_CONTEXT];


/* ---- GPU - Resource - Defaults ------------------------------------------------------------------------------------------------------------------------------------------------ */

TgEXTN D3D12_BLEND_DESC const               g_asKN_GPU_EXT_Default_Blend_State[ETgKN_GPU_DEFAULT_BLEND_STATE_COUNT];
TgEXTN D3D12_RASTERIZER_DESC const          g_asKN_GPU_EXT_Default_Rasterizer_State[ETgKN_GPU_DEFAULT_RASTERIZER_STATE_COUNT];
TgEXTN D3D12_DEPTH_STENCIL_DESC const       g_asKN_GPU_EXT_Default_Depth_Stencil_State[ETgKN_GPU_DEFAULT_DEPTH_STENCIL_STATE_COUNT];

TgEXTN STg2_KN_GPU_PSO_DESC                 g_asKN_GPU_STD_PSO_DESC[ETgKN_GPU_DEFAULT_PSO_COUNT];


/* =============================================================================================================================================================================== */
#endif
