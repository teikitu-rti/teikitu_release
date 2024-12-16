/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (DX12) Kernel - Internal - Constants [GPU].h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
#if !defined(TGS_DX12_KERNEL_INTERNAL_CONSTANTS_GPU_H)
#define TGS_DX12_KERNEL_INTERNAL_CONSTANTS_GPU_H
#pragma once


/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Configuration                                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* MSFT: A given allocator can be associated with no more than one currently recording command list at a time, though one command allocator can be used to create any number of
         GraphicsCommandList objects. (For calling Reset) The app must make sure that the GPU is no longer executing any command lists which are associated with the allocator;
         otherwise, the call will fail. Unlike ID3D12CommandAllocator::Reset, you can call Reset while the command list is still being executed. Note that only one command list
         associated with each command allocator may be in a recording state at one time. */

/* PLAN: NOTE: Allocators are created by the device, but no node mask is associated with it. For simplicity of implementation, we want to have enough allocators to cover the
         number of lists that can be concurrently recording, multiplied by the number of frames that can be queued on the GPU node (execution context). Assuming we are using the 
         integrated job system, that would be the number of job threads (+1 for the main thread), multiplied by the maximum buffers in flip chain constant (for graphic lists).
         This assumes that a job will always acquire and close its own graphic list. Allocators are assumed to be in use in conjunction with the sequencing of the flip chain. For
         non-graphic lists, we will make the same assumption for compute lists as we did for the graphic lists. The remaining list types we will use a limit of four until we
         develop an usage pattern that violates the limit. */

/* The above plan will result in the follow math for the derived constants:
   Allocators = Number of lists (of a single type) that can be actively recording (for each list type).
     # active recording graphic/compute lists: KTgKN_MAX_JOB_THREAD + 1 (main thread) + 15 (pad for lists that are not closed prior at the end of job execution)
     # active recording other lists: 4
   Lists = Number of lists needed within a frame. */

enum {  KTgKN_GPU_EXT_MAX_HIGH_USE_ALLOC       = KTgKN_MAX_JOB_THREAD + 16, /**< Number of allocators available concurrently for recording of high use list types. */
        KTgKN_GPU_EXT_MAX_LOW_USE_ALLOC        = 4 }; /**< Number of allocators available concurrently for recording of low use list types. */

enum {  KTgKN_GPU_EXT_MAX_GRAPHICS_LIST        = 16384,    /**< Number of graphic lists available in a frame for recording. */
        KTgKN_GPU_EXT_MAX_BUNDLE_LIST          =  4096,    /**< Number of bundle lists available in a frame for recording. */
        KTgKN_GPU_EXT_MAX_COMPUTE_LIST         =  4096,    /**< Number of compute lists available in a frame for recording. */
        KTgKN_GPU_EXT_MAX_COPY_LIST            =  1024,    /**< Number of copy lists available in a frame for recording. */
        KTgKN_GPU_EXT_MAX_LOW_USE_LIST         =    64 };  /**< Number of lists available in a frame for recording of low use list types. */

enum {  KTgKN_GPU_EXT_MAX_COMMAND_LIST         = KTgKN_GPU_EXT_MAX_GRAPHICS_LIST
                                               + KTgKN_GPU_EXT_MAX_BUNDLE_LIST
                                               + KTgKN_GPU_EXT_MAX_COMPUTE_LIST
                                               + KTgKN_GPU_EXT_MAX_COPY_LIST
                                               + KTgKN_GPU_EXT_MAX_LOW_USE_LIST * 3 };

enum {  KTgKN_GPU_EXT_MAX_ROOT_SIGNATURE       =    16,
        KTgKN_GPU_EXT_MAX_PSO_RN               =   256,
        KTgKN_GPU_EXT_MAX_PSO_CM               =    64,
        KTgKN_GPU_EXT_MAX_DEFAULT_SRV_CBE      = KTgMACRO_KN_GPU_EXT_MAX_DEFAULT_SRV_CBE,
        KTgKN_GPU_EXT_MAX_DEFAULT_SRV_VOL      = KTgMACRO_KN_GPU_EXT_MAX_DEFAULT_SRV_VOL,
        KTgKN_GPU_EXT_MAX_DEFAULT_SRV_IMG      = KTgMACRO_KN_GPU_EXT_MAX_DEFAULT_SRV_IMG,
        KTgKN_GPU_EXT_MAX_DEFAULT_SRV          = KTgKN_GPU_EXT_MAX_DEFAULT_SRV_CBE + KTgKN_GPU_EXT_MAX_DEFAULT_SRV_VOL + KTgKN_GPU_EXT_MAX_DEFAULT_SRV_IMG,
};




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Validation                                                                                                                                                                     */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgCOMPILER_ASSERT(D3D12_SIMULTANEOUS_RENDER_TARGET_COUNT <= 8,0);




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Constants                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Code Macros                                                                                                                                                                    */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */


#if defined(TgCOMPILE__GPU_OBJECT_NAME) && TgCOMPILE__GPU_OBJECT_NAME
    #define TgMACRO_KN_GPU_EXT_SET_NAME_WTH_VAR(OBJ,VAR)                                                                                                                            \
    {                                                                                                                                                                               \
        ID3D12Object_SetPrivateData( OBJ, MS_REF WKPDID_D3DDebugObjectName, sizeof( VAR ), VAR );                                                                                   \
    }
    #define TgMACRO_KN_GPU_EXT_SET_NAME(OBJ,MSG)                                                                                                                                               \
    {                                                                                                                                                                               \
        TgCHAR_U8_C                         uszDebugName[] = MSG;                                                                                                                   \
                                                                                                                                                                                    \
        ID3D12Object_SetPrivateData( OBJ, MS_REF WKPDID_D3DDebugObjectName, sizeof( uszDebugName ), uszDebugName );                                                                 \
    }
#else
    #define TgMACRO_KN_GPU_EXT_SET_NAME(OBJ,MSG)
/*# defined(TgCOMPILE__GPU_OBJECT_NAME) && TgCOMPILE__GPU_OBJECT_NAME */
#endif

/* =============================================================================================================================================================================== */
#endif
