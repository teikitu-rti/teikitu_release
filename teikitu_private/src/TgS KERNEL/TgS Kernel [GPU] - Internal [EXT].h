/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Kernel [GPU] - Internal [EXT].h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.20 | »GUID« DE461472-5528-4A5B-A7F4-09CCAD73387B */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_KERNEL_GPU_INTERNAL_EXT_H) && defined(TgBUILD_FEATURE__GRAPHICS)
#if !defined (ENABLE_RELOAD_GUARD)

#include "TgS Common.h"

#include "TgS Ring 0 - Type.h"
#include "TgS Ring 2 - Type.h"

#include "TgS Kernel.h"

#include "TgS Kernel [GPU].h"
#include "TgS Kernel [GPU] - Internal - Type.h"
#include "TgS Kernel [GPU] - Internal - Data.h"

#include "TgS COMMON/TgS Common.inl"


/* == Kernel ===================================================================================================================================================================== */

/*
    Types, Data, and Functions use the EXT (Extension) prefix whenever it is meant to be part of the generic API extension Kernel Extension. API specific prefix should only be
    used for strictly internal API implementation.
*/

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgEXTN TgRESULT
tgKN_GPU_EXT_Module_Init( TgVOID );

TgEXTN TgRESULT
tgKN_GPU_EXT_Module_Boot( TgVOID );

TgEXTN TgVOID
tgKN_GPU_EXT_Module_Stop( TgVOID );

TgEXTN TgVOID
tgKN_GPU_EXT_Module_Free( TgVOID );

TgEXTN TgRESULT
tgKN_GPU_EXT_Module_Update(
    TgFLOAT32_C );

TgEXTN TgRSIZE
tgKN_GPU_EXT_Query_Fixed_Memory( TgVOID );


/* ---- GPU - Enumeration - Extension -------------------------------------------------------------------------------------------------------------------------------------------- */

TgEXTN TgRESULT
tgKN_GPU_EXT_Enumerate( TgVOID );

/** @brief Free all the resources associated with a physical device at the given index in the HOST contexts.
    @param [in] ARG0 Index of the physical device to free. */
TgEXTN TgVOID
tgKN_GPU_EXT_Physical_Device_Free(
    TgRSIZE_C ARG0 );

/** @brief Free all the resources associated with a display output at the given index in the HOST contexts.
    @param [in] ARG0 Index of the display output to free. */
TgEXTN TgVOID
tgKN_GPU_EXT_Display_Output_Free(
    TgRSIZE_C ARG0 );


/* ---- GPU - Contexts - Extension ----------------------------------------------------------------------------------------------------------------------------------------------- */

TgEXTN TgRESULT
tgKN_GPU_EXT__Host__Init( TgVOID );

/** @brief Free all associated memory with the single host and host external data contexts, and clear and invalidate all values. */
TgEXTN TgVOID
tgKN_GPU_EXT__Host__Free( TgVOID );

/** @brief Initialize the extended data for a new device context.
    @param [in] ARG0 UID of the device context.
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_EXT__Device__Init(
    TgKN_GPU_CXT_DEVC_ID_C ARG0 );

/** @brief Free the context and all associated resource, returning it to a free pool. Called as part of the non-extension version of the same call.
    @param [in] ARG0 UID of the device context. */
TgEXTN TgVOID
tgKN_GPU_EXT__Device__Free(
    TgKN_GPU_CXT_DEVC_ID_C ARG0 );

/** @brief Initialize the extended data for a new execution context.
    @param [in] ARG0 UID of the execution context.
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_EXT__Execute__Init(
    TgKN_GPU_CXT_EXEC_ID_C ARG0 );

/** @brief Create default pipeline resources. Between Pass 0 and Pass 1 
    @param [in] ARG0 Pointer to the Vulkan command structure
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_EXT__Execute__Init__Create_Default_Resources__Pass_0(
    STg2_KN_GPU_CMD_PC TgANALYSIS_NO_NULL ARG0 );

/** @brief Create default pipeline resources
    @param [in] ARG0 Pointer to the Vulkan command structure
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_EXT__Execute__Init__Create_Default_Resources__Pass_1(
    STg2_KN_GPU_CMD_PC TgANALYSIS_NO_NULL ARG0 );

/** @brief Free the context and all associated resource, returning it to a free pool. Called as part of the non-extension version of the same call.
    @param [in] ARG0 UID of the context. */
TgEXTN TgVOID
tgKN_GPU_EXT__Execute__Free(
    TgKN_GPU_CXT_EXEC_ID_C ARG0 );

/** @brief Initialize swap chain.
    @param [in] ARG0 UID of the swap chain context.
    @param [in] ARG1 Flag indicating if the swap chain should be resized. Used when the compositor needs to notify of a size change.
    @param [in] ARG2 Flag indicating if the swap chain should be created. Used when the device loses the swap chain.
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_EXT__SwapChain__Init(
    TgKN_GPU_CXT_SWAP_ID_C ARG0, TgBOOL_C ARG1, TgBOOL_C ARG2);

/** @brief Free the context and all associated resource, returning it to a free pool. Called as part of the non-extension version of the same call.
    @param [in] ARG0 UID of the context. */
TgEXTN TgVOID
tgKN_GPU_EXT__SwapChain__Free(
    TgKN_GPU_CXT_SWAP_ID_C ARG0 );


/* ---- GPU - Resource ----------------------------------------------------------------------------------------------------------------------------------------------------------- */

#define __PARENT_FILE__ "TgS Kernel [GPU] - Internal [EXT].h"
#define ENABLE_RELOAD_GUARD
#include "TgS KERNEL/TgS Kernel [GPU] - Resource [INC].h"
#undef ENABLE_RELOAD_GUARD
#undef __PARENT_FILE__

#define TGS_KERNEL_GPU_INTERNAL_EXT_H


/* ---- GPU - Debug -------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)

/** @brief Initialize the extended data (debug) for a new host context.
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_EXT__Host__Init_Debug( TgVOID );

/** @brief Free/Destroy the extended data (debug) for a new host context. */
TgEXTN TgVOID
tgKN_GPU_EXT__Host__Free_Debug( TgVOID );

/** @brief Initialize the extended data (debug) for a new execution context.
    @param [in] ARG0 UID of the execution context.
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_EXT__Execute__Init_Debug(
    TgKN_GPU_CXT_EXEC_ID_C ARG0 );

/** @brief Initialize render debug output resources.
    @param [in] ARG0 ARG0 Pointer to the command structure returned by tgKN_GPU_EXT__WORK__Acquire_Command.
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_EXT__Execute__Init_Debug__Create_Resources(
    STg2_KN_GPU_CMD_PC ARG0 );

/** @brief Free/Destroy render debug output resources.
    @param [in] ARG0 ARG0 Pointer to the command structure returned by tgKN_GPU_EXT__WORK__Acquire_Command. */
TgEXTN TgVOID
tgKN_GPU_EXT__Execute__Free_Debug__Destroy_Resources(
    STg2_KN_GPU_CMD_PC ARG0 );

/** @brief Free/Destroy the extended data (debug) for a new execution context.
    @param [in] ARG0 UID of the execution context. */
TgEXTN TgVOID
tgKN_GPU_EXT__Execute__Free_Debug(
    TgKN_GPU_CXT_EXEC_ID_C ARG0 );

/** @brief Initialize the extended data (debug) for a new execution context.
    @param [in] ARG0 UID of the swap context.
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_EXT__Swap__Init_Debug(
    TgKN_GPU_CXT_SWAP_ID_C ARG0 );

/** @brief Free/Destroy the extended data (debug) for a new execution context.
    @param [in] ARG0 UID of the swap context. */
TgEXTN TgVOID
tgKN_GPU_EXT__Swap__Free_Debug(
    TgKN_GPU_CXT_SWAP_ID_C ARG0 );

/** @brief Initialize render debug output resources.
    @param [in] ARG0 ARG0 Pointer to the command structure returned by tgKN_GPU_EXT__WORK__Acquire_Command.
    @param [in] ARG1 Enumeration selecting the debug primitive.
    @param [in] ARG2 Pointer to a debug geometry generation data structure (data source). */
TgEXTN TgVOID
tgKN_GPU_EXT__CMD__Register_Debug_Geometry(
    STg2_KN_GPU_CMD_PC TgANALYSIS_NO_NULL ARG0, ETgKN_GPU_DEBUG_PM ARG1, TgKN_GPU_DBG_PM_Generate_CPCU TgANALYSIS_NO_NULL ARG2 );

/** @brief Return the debug command structure associated with the given command.
    @param [out] OUT0 Pointer to the debug command structure.
    @param [in] ARG1 ARG0 Pointer to the command structure returned by tgKN_GPU_EXT__WORK__Acquire_Command.
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_EXT__CMD__Command_Debug(
    STg2_KN_GPU_CMD_DBG_PP TgANALYSIS_NO_NULL OUT0, STg2_KN_GPU_CMD_PC TgANALYSIS_NO_NULL ARG1 );

/*# defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
#endif



/*# defined (ENABLE_RELOAD_GUARD) */
#else

/* ---- GPU - Resource ----------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if defined(MACRO_BUILD_TEXTURE)

/** @brief Initialize a resource as part of the loading process.
    @param [in] ARG0 UID of the kernel file object to be used.
    @param [in] ARG1 Integer for the offset into the input object to begin reading.
    @param [in] ARG2 Pointer to a descriptor for the resource type.
    @param [in] ARG3 Enumeration of the memory allocation method used for the resource.
    @param [in] ARG4 UID of the resource to be modified.
    @return Result Code. */
TgEXTN TgRESULT
T(tgKN_GPU_EXT_,__Execute_Load)(
    TgKN_FILE_ID_C ARG0, TgRSIZE_C ARG1, T(STg2_KN_GPU_,_DESC_CPC) ARG2, TgUINT_E64_C ARG3, T(TgKN_GPU_,_ID_C) ARG4 );

/** @brief Free all associated resources with the resource UID.
    @param [in] ARG0 UID of the resource to be modified. */
TgEXTN TgVOID
T(tgKN_GPU_EXT_,__Execute_Free)(
    T(TgKN_GPU_,_ID_C) ARG0 );

/** @brief Create a resource instance, which is the minimum required for use in the GPU pipeline.
    @param [in] ARG0 ARG0 Pointer to the command structure returned by tgKN_GPU_EXT__WORK__Acquire_Command.
    @param [in] ARG1 UID for the resource instance that identifies the texture.
    @param [in] ARG2 String associated with resource for debug purposes.
    @return Result Code. */
TgEXTN TgRESULT
T(tgKN_GPU_EXT__CMD__,_Inst__Init)(
    STg2_KN_GPU_CMD_PC ARG0, T(TgKN_GPU_,_INST_ID_C) ARG1, TgCHAR_U8_CPCU ARG2 );

/** @brief Free all associated resources with the resource instance UID.
    @param [in] ARG0 ARG0 Pointer to the command structure returned by tgKN_GPU_EXT__WORK__Acquire_Command.
    @param [in] ARG1 UID of the resource instance. */
TgEXTN TgVOID
T(tgKN_GPU_EXT__CMD__,_Inst__Free)(
    STg2_KN_GPU_CMD_PC ARG0, T(TgKN_GPU_,_INST_ID_C) ARG1 );

/** @brief Create a Shader Resource View in the Execution Context default heap (which is copied into the Execution Command Context at the start of each frame).
    @param [in] ARG0 ARG0 Pointer to the command structure returned by tgKN_GPU_EXT__WORK__Acquire_Command.
    @param [in] ARG1 UID of the resource instance. */
TgEXTN TgRSIZE
T(tgKN_GPU_EXT__CMD__Register_Default_,_Inst)(
    STg2_KN_GPU_CMD_PC ARG0, T(TgKN_GPU_,_INST_ID_C) ARG1, ETgKN_GPU_DEFAULT_SAMPLER_C ARG2 );

/*# defined(MACRO_BUILD_TEXTURE) */
#endif


/* ---- Resource - GPU - Texture - API ------------------------------------------------------------------------------------------------------------------------------------------- */
#if defined(MACRO_BUILD_TEXTURE)

/** @brief Lock the surface of a texture for modification. This will make it available to be modified by CPU operations. Does not check to see if texture is in use.
    @param [out] OUT0 Pointer to the data structure holding the surface information of the locked texture layer in main memory.
    @param [in] ARG1 ARG0 Pointer to the command structure returned by tgKN_GPU_EXT__WORK__Acquire_Command.
    @param [in] ARG2 Integer indicating the MIP level of the texture to be locked.
    @param [in] ARG3 Integer indicating the depth of the surface to be locked.  */
TgEXTN TgVOID
T(tgKN_GPU_EXT__CMD__,__Fast_Lock)(
    STg2_KN_GPU_TX_LOCK_PCU TgANALYSIS_NO_NULL OUT0, STg2_KN_GPU_CMD_PC ARG1, T(TgKN_GPU_,_INST_ID_C) ARG2 );

/** @brief Lock the surface of a texture for modification. This will make it available to be modified by CPU operations.
    @param [out] OUT0 Pointer to the data structure holding the surface information of the locked texture layer in main memory.
    @param [in] ARG1 ARG0 Pointer to the command structure returned by tgKN_GPU_EXT__WORK__Acquire_Command.
    @param [in] ARG2 Integer indicating the MIP level of the texture to be locked.
    @param [in] ARG3 Integer indicating the depth of the surface to be locked.  */
TgEXTN TgVOID
T(tgKN_GPU_EXT__CMD__,__Lock)(
    STg2_KN_GPU_TX_LOCK_PCU TgANALYSIS_NO_NULL OUT0, STg2_KN_GPU_CMD_PC ARG1, T(TgKN_GPU_,_INST_ID_C) ARG2 );

/** @brief Return the surface to the GPU to be used. Paired function when surface was fast unlocked.
    @param [in] ARG0 ARG0 Pointer to the command structure returned by tgKN_GPU_EXT__WORK__Acquire_Command.
    @param [in] ARG1 Integer indicating the MIP level of the texture to be locked.
    @param [in] ARG2 Integer indicating the depth of the surface to be locked.  */
TgEXTN TgVOID
T(tgKN_GPU_EXT__CMD__,__Fast_Unlock)(
    STg2_KN_GPU_CMD_PC ARG0, STg2_KN_GPU_TX_LOCK_PCU ARG1, T(TgKN_GPU_,_INST_ID_C) ARG2 );

/** @brief Unlocks the resource instance (transitions the resource from CPU writable to GPU readable).
    @param [in] ARG0 ARG0 Pointer to the command structure returned by tgKN_GPU_EXT__WORK__Acquire_Command.
    @param [in] ARG1 Pointer to the surface structure that was filled/returned by the paired lock function.
    @param [in] ARG2 UID for the resource instance that identifies the texture. */
TgEXTN TgVOID
T(tgKN_GPU_EXT__CMD__,__Unlock)(
    STg2_KN_GPU_CMD_PC ARG0, STg2_KN_GPU_TX_LOCK_PCU ARG1, T(TgKN_GPU_,_INST_ID_C) ARG2 );

/*# defined(MACRO_BUILD_TEXTURE) */
#endif


/* =============================================================================================================================================================================== */

/*# defined (ENABLE_RELOAD_GUARD) */
#endif

/*# !defined(TGS_KERNEL_GPU_INTERNAL_EXT_H) && defined(TgBUILD_FEATURE__GRAPHICS) */
#endif
