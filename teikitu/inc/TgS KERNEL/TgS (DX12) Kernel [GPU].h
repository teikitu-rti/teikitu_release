/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (DX12) Kernel [GPU].h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
#if !defined(TGS_DX12_KERNEL_GPU_H)
#define TGS_DX12_KERNEL_GPU_H
#pragma once

#include "TgS Kernel [GPU].h"

#include TgHEADER_OPERATING_SYSTEM(TgS COMMON/TgS,Common - Base - Include.h)

CLANG_WARN_DISABLE_PUSH(everything)
MSVC_PRAGMA(warning(push, 0))
#define D3DX12_NO_CHECK_FEATURE_SUPPORT_CLASS
#define D3DX12_NO_STATE_OBJECT_HELPERS
#include <DirectX/include/minwindefine.h>
#include <DirectX/include/directx/dxcore.h> /**< Needs to be a local copy due to author's prejudice against C. Fixed issues with dxcore_interface.h */
#include <DirectX/include/directx/d3d12.h>
MSVC_PRAGMA(warning(pop))
CLANG_WARN_DISABLE_POP(everything)

#include "TgS KERNEL/TgS (DX12) Kernel [GPU] - Constants.h"
#include "TgS KERNEL/TgS (DX12) Kernel [GPU] - Type.h"
#include "TgS KERNEL/TgS (DX12) Kernel [GPU] - Debug.h"




/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- GPU - Contexts ----------------------------------------------------------------------------------------------------------------------------------------------------------- */

/*  @param [in] ARG0 Union of a pointer to the command list data structure returned by tgKN_GPU_EXT__Execute__Command_List_Acquire. */
TgEXTN TgVOID
tgKN_GPU_EXT__Execute__Register_Resource_For_Release(
    UTg2_KN_GPU_CMD_C ARG0, ID3D12Resource_P ARG1 );

TgEXTN ID3D12Device10_P
tgKN_GPU_EXT__Execute__Get_DX12_Device(
    TgKN_GPU_CXT_EXEC_ID_C ARG0 );

TgEXTN TgRESULT
tgKN_GPU_EXT__SwapChain__Get_Back_Buffer(
    D3D12_CPU_DESCRIPTOR_HANDLE_PC OUT0, D3D12_CPU_DESCRIPTOR_HANDLE_PC OUT1, STg2_KN_GPU_HLSL_Output_DESC_PC OUT2, TgKN_GPU_CXT_SWAP_ID_C ARG3 );

TgEXTN TgRESULT
tgKN_GPU_EXT__SwapChain__Set_Back_Buffer_As_Render_Target(
    STg2_KN_GPU_HLSL_Output_DESC_PC OUT0, TgKN_GPU_CXT_SWAP_ID_C ARG1 );


/* ---- GPU - Resource - Default ------------------------------------------------------------------------------------------------------------------------------------------------- */

/*  @param [in] ARG0 Union of a pointer to the command list data structure returned by tgKN_GPU_EXT__Execute__Command_List_Acquire. */
TgEXTN TgRESULT
tgKN_GPU_EXT__CMD__Set_Graphics_Root_Signature_From_Default(
    UTg2_KN_GPU_CMD_C ARG0, ETgKN_GPU_DEFAULT_ROOT_SIGNATURE_C ARG1 );


/* =============================================================================================================================================================================== */
#endif
