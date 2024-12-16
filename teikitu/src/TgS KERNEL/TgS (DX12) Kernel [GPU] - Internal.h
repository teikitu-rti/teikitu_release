/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (DX12) Kernel - Internal [GPU].h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
#if !defined(TGS_DX12_KERNEL_INTERNAL_GPU_H)
#define TGS_DX12_KERNEL_INTERNAL_GPU_H
#pragma once

/* TODO: WIP Comment for DX12 (API) GPU management
   Other modules that need to use the GPU should have the capacity to write their code using the API semantics directly. Otherwise, we would have to create wrapper functions to
   mimic the graphic APIs and try to create a singular representation across all of them. Instead, think of the users of the GPU module as plug-ins that will be run by the 
   the GPU kernel. The aim will be to provide base functionality to ease the use of the API (similar to the CPU work), taking on some of the burden of memory and resource
   management. */


/* From MSDN D3D12 Multi-Adapter Programming Guide

- The MSFT documentation on this seems to be a little confusing - for clarification
  - A device can be virtual, and be composed of multiple phyiscal different video cards.
  - Device driver setting will determine if the separate video cards are viewed as separate devices, or aggregated into the virtual device.
  - I imagine that a single video card with more than one GPU will emulate two video cards.
  - Multiple or All node functions are applied at the device level.

- The follow APIS are applied to single nodes (and results should be contained in the execution context)

    Allocators are per frame (buffer), per context, per thread

    CreateCommandQueue : creates a queue from a D3D12_COMMAND_QUEUE_DESC structure.
    CreateCommandList : takes a nodeMask parameter.
    CreateDescriptorHeap : creates a descriptor heap from a D3D12_DESCRIPTOR_HEAP_DESC structure.
    CreateQueryHeap : creates a query heap from a D3D12_QUERY_HEAP_DESC structure.

- The follow APIS are applied to multiple nodes (and results should be contained in the device or execution context)

    CreateGraphicsPipelineState : creates a graphics pipeline state object from a D3D12_GRAPHICS_PIPELINE_STATE_DESC structure.
    CreateComputePipelineState : creates a compute pipeline state object from a D3D12_COMPUTE_PIPELINE_STATE_DESC structure.
    CreateRootSignature: Creates a root signature layout.
    CreateCommandSignature : creates a command signature object from a D3D12_COMMAND_SIGNATURE_DESC structure.

- The follow APIS are applied to all nodes (and results should be contained in the device context)

    CreateFence
    GetDescriptorHandleIncrementSize
    SetStablePowerState
    CheckFeatureSupport
    CreateSampler
    CopyDescriptors
    CopyDescriptorsSimple
    CreateSharedHandle
    OpenSharedHandleByName
    CreateCommandAllocator

    CreateConstantBufferView
    CreateRenderTargetView
    CreateUnorderedAccessView
    CreateDepthStencilView
    CreateShaderResourceView

    */

#include "TgS Kernel [GPU] - Internal.h"

#include "TgS KERNEL/TgS (DX12) Kernel [GPU].h"

CLANG_WARN_DISABLE_PUSH(everything)
MSVC_PRAGMA(warning(push, 0))
MSVC_PRAGMA(warning(disable: 4820 4668 5039))
#include <dxgi1_6.h>
#include <dxgidebug.h>
MSVC_PRAGMA(warning(pop))
CLANG_WARN_DISABLE_POP(everything)

#if defined(_INC_WINDOWS)
#error windows.h has been found in the include chain
#endif

#include "TgS (DX12) Kernel [GPU] - Internal - Constants.h"
#include "TgS (DX12) Kernel [GPU] - Internal - Type.h"
#include "TgS (DX12) Kernel [GPU] - Internal - Data.h"
#include "TgS (DX12) Kernel [GPU] - Internal - Debug.h"

TgEXTN HINSTANCE                       g_hInstance;




/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/** @brief Free all the resources that were allocated during enumeration. */
TgEXTN TgVOID
tgKN_GPU_EXT_Enumerate_Free_Resources( TgVOID );

/** @brief Select a supported mode that matches the request or is the closest by rounding down.
    @param [out] OUT0 Pointer to a mode data structure that holds the results of the search.
    @param [in] ARG1 Pointer to the output device being queried.
    @param [in] ARG2 Pointer to a mode data structure that is the basis of the search.
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_EXT_Select_Min_Mode(
    STg2_KN_GPU_Mode_PC OUT0, STg2_KN_GPU_EXT_Output_PCU ARG1, STg2_KN_GPU_Mode_CPC ARG2 );

/** @brief Select a supported mode that matches the request or is the closest by rounding up.
    @param [out] OUT0 Pointer to a mode data structure that holds the results of the search.
    @param [in] ARG1 Pointer to the output device being queried.
    @param [in] ARG2 Pointer to a mode data structure that is the basis of the search.
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_EXT_Select_Max_Mode(
    STg2_KN_GPU_Mode_PC OUT0, STg2_KN_GPU_EXT_Output_PCU ARG1, STg2_KN_GPU_Mode_CPC ARG2 );

#if TgS_STAT__KERNEL || TgS_DEBUG__KERNEL
TgEXTN TgVOID
tgSTAT_KN_GPU_EXT_Adapter_Output(
    STg2_KN_GPU_EXT_Adapter_CPCU );

TgEXTN TgCHAR_U8_CP
tgKN_GPU_EXT_FMT_To_USZ(
    ETgKN_GPU_EXT_FORMAT_C );

TgEXTN TgCHAR_WC_CP
tgKN_GPU_EXT_FMT_To_WSZ(
    ETgKN_GPU_EXT_FORMAT_C );
/*# TgS_STAT__KERNEL || TgS_DEBUG__KERNEL */
#endif


/* ---- OS Functions ------------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgEXTN TgRESULT
tgKN_GPU_EXT_Create_Default_PSO(
    TgKN_GPU_CXT_EXEC_ID_C ARG0 );

TgEXTN TgRESULT
tgKN_GPU_EXT_Create_Default_Root_Signature(
    TgKN_GPU_CXT_EXEC_ID_C ARG0 );


/* ---- OS Functions ------------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgEXTN TgRESULT
tgKN_OS_GPU_API_Module_Init( TgVOID );

TgEXTN TgRESULT
tgKN_OS_GPU_API_Module_Boot( TgVOID );

TgEXTN TgVOID
tgKN_OS_GPU_API_Module_Stop( TgVOID );

TgEXTN TgVOID
tgKN_OS_GPU_API_Module_Free( TgVOID );

/** @param [in] ARG0 UID for the Context.
    @param [in] ARG1 Windows OS window handle encoded as an integer.
    @param [in] ARG2 Boolean, if true will re-validate the output device that the window is predominantly using. */
TgEXTN TgVOID
tgKN_OS_GPU_EXT_Update_Swap_Output( 
    TgKN_GPU_CXT_SWAP_ID_C ARG0, TgUINT_PTR_C ARG1, TgBOOL_C ARG2 );

TgEXTN TgVOID
tgKN_OS_GPU_EXT_Output__Init(
    TgRSIZE, STg2_KN_GPU_EXT_Output_CPCU );

TgEXTN TgVOID
tgKN_OS_GPU_EXT_Output__Free(
    TgRSIZE );


/* =============================================================================================================================================================================== */
#endif
