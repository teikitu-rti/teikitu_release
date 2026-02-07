/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Kernel [GPU] - Internal.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.20 | »GUID« DE461472-5528-4A5B-A7F4-09CCAD73387B */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_KERNEL_GPU_INTERNAL_H) && defined(TgBUILD_FEATURE__GRAPHICS)
#if !defined (ENABLE_RELOAD_GUARD)

#include "TgS Common.h"

#include "TgS Ring 0 - Type.h"
#include "TgS Ring 2 - Type.h"

#include "TgS Kernel.h"

#include "TgS Kernel [GPU].h"
#include "TgS Kernel [GPU] - Internal - Constants.h"
#include "TgS Kernel [GPU] - Internal - Type.h"
#include "TgS Kernel [GPU] - Internal - Data.h"
#include "TgS Kernel [GPU] - Internal [EXT].h"

#include "TgS COMMON/TgS Common.inl"


/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal OS and API Module Lifecycle Functions                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/** @brief Standard Module function: First part of initialization process. Set the state of the module.
    @return Result Code. */
TgEXTN TgRESULT
tgKN_OS_GPU_Module_Init( TgVOID );

/** @brief Standard Module function: Last part of initialization process. Used for setup and other necessary tasks prior to the use of the module.
    @return Result Code. */
TgEXTN TgRESULT
tgKN_OS_GPU_Module_Boot( TgVOID );

/** @brief Standard Module function: Used for close the module as part of the shutdown process. Module is not to be used after this is executed. */
TgEXTN TgVOID
tgKN_OS_GPU_Module_Stop( TgVOID );

/** @brief Standard Module function: Final part of shutdown process. Release any remaining allocated memory, and reset the state of the module. */
TgEXTN TgVOID
tgKN_OS_GPU_Module_Free( TgVOID );

/** @brief Standard Module function: First part of initialization process. Set the state of the module.
    @return Result Code. */
TgEXTN TgRESULT
tgKN_OS_GPU_API_Module_Init( TgVOID );

/** @brief Standard Module function: Last part of initialization process. Used for setup and other necessary tasks prior to the use of the module.
    @return Result Code. */
TgEXTN TgRESULT
tgKN_OS_GPU_API_Module_Boot( TgVOID );

/** @brief Standard Module function: Used for close the module as part of the shutdown process. Module is not to be used after this is executed. */
TgEXTN TgVOID
tgKN_OS_GPU_API_Module_Stop( TgVOID );

/** @brief Standard Module function: Final part of shutdown process. Release any remaining allocated memory, and reset the state of the module. */
TgEXTN TgVOID
tgKN_OS_GPU_API_Module_Free( TgVOID );

#if TgS_STAT__KERNEL || TgS_DEBUG__KERNEL
TgEXTN TgVOID
tgSTAT_KN_OS_GPU_Physical_Device_Output( TgVOID );
/*# TgS_STAT__KERNEL || TgS_DEBUG__KERNEL */
#endif




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- GPU - Contexts ----------------------------------------------------------------------------------------------------------------------------------------------------------- */

/** @brief Initialize the single host and host external data contexts.
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU__Host__Init( TgVOID );

/** @brief Free all associated memory with the single host and host external data contexts, and clear and invalidate all values. */
TgEXTN TgVOID
tgKN_GPU__Host__Free( TgVOID );


/** @brief Initialize a new context (if one is available). [Single-Threaded]
    @param [out] OUT0 Pointer to result data structure that is filled in with the resulting UID(s) of the allocated contexts.
    @param [in] ARG1 Pointer to a selection data structure.
    @param [in] ARG2 Integer index of the device context to be created.
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU__Device__Init(
    STg2_KN_GPU_Init_Result_PCU OUT0, STg2_KN_GPU_Select_CPCU ARG1, TgRSIZE_C ARG2 );

/** @brief Free the context and all associated resource, returning it to a free pool.
    @param [in] ARG0 UID of the device context. */
TgEXTN TgVOID
tgKN_GPU__Device__Free(
    TgKN_GPU_CXT_DEVC_ID_C ARG0 );

/** @brief Initialize a new context (if one is available). [Single-Threaded]
    @param [out] OUT0 Pointer to result data structure that is filled in with the resulting UID(s) of the allocated contexts.
    @param [in] ARG1 Pointer to a selection data structure.
    @param [in] ARG2 Integer index in the selection data structure of the execution context to be created.
    @param [in] ARG3 UID of the parent device context.
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU__Execute__Init(
    STg2_KN_GPU_Init_Result_PCU OUT0, STg2_KN_GPU_Select_CPCU ARG1, TgRSIZE_C ARG2, TgKN_GPU_CXT_DEVC_ID_C ARG3 );

/** @brief Free the context and all associated resource, returning it to a free pool.
    @param [in] ARG0 UID of the context. */
TgEXTN TgVOID
tgKN_GPU__Execute__Free(
    TgKN_GPU_CXT_EXEC_ID_C ARG0 );


/** @brief Initialize a new context (if one is available). [Single-Threaded]
    @param [out] OUT0 Pointer to result data structure that is filled in with the resulting UID(s) of the allocated contexts.
    @param [in] ARG1 Pointer to a selection data structure.
    @param [in] ARG2 Integer index of the output context to be created.
    @param [in] ARG3 UID of the parent device context.
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU__SwapChain__Init(
    STg2_KN_GPU_Init_Result_PCU OUT0, STg2_KN_GPU_Select_CPCU ARG1, TgRSIZE_C ARG2, TgKN_GPU_CXT_EXEC_ID_C ARG3 );

/** @brief Free the context and all associated resource, returning it to a free pool.
    @param [in] ARG0 UID of the context. */
TgEXTN TgVOID
tgKN_GPU__SwapChain__Free(
    TgKN_GPU_CXT_SWAP_ID_C ARG0 );

/** @brief Update the output (monitor) expectations and capabilities for the swap chain
    @param [in] ARG0 UID for the Context.
    @param [in] ARG1 Windows OS window handle encoded as an integer.
    @param [in] ARG2 Boolean, if true will re-validate the output device that the window is predominantly using. */
TgEXTN TgVOID
tgKN_OS_GPU_CXT_SWAP_Update_Output( 
    TgKN_GPU_CXT_SWAP_ID_C ARG0, TgUINT_PTR_C ARG1, TgBOOL_C ARG2 );

#if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)

/** @brief Initialize render debug output resources.
    @param [in] ARG0 ARG0 Pointer to the command structure returned by tgKN_GPU_EXT__WORK__Acquire_Command.
    @param [in] ARG1 UID of the context. */
TgEXTN TgVOID
tgKN_GPU__SwapChain__Present_Print_Debug_Stats(
    STg2_KN_GPU_CMD_PC ARG0, TgKN_GPU_CXT_SWAP_ID_C ARG1 );

/*# defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
#endif


/* ---- GPU - Resource - Texture ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* Resource instances are bound to a specific render resource context. A single copy of the raw resource is stored in global memory. Depending on the platform, instances of the 
   resource may have context specific copies or it may be shared. */

/** @brief Create a off-screen render target. 
    @param [in] ARG0 ARG0 Pointer to the command structure returned by tgKN_GPU_EXT__WORK__Acquire_Command.
    @param [in] ARG1 Enumeration of the memory allocation method used for the resource.
    @param [in] ARG2 Pointer to a texture image descriptor.
    @return UID for the initialized resource instance, or the INVALID ID otherwise. 
*/
TgEXTN TgKN_GPU_TX_IMG_INST_ID
tgKN_GPU__CMD__RT_IMG__Create(
    STg2_KN_GPU_CMD_PC ARG0, TgUINT_E64_C ARG1, STg2_KN_GPU_TX_IMG_DESC_CPCU ARG2 );

#if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)

/** @brief Create a resource instance of a texture filled with a constant colour.
    @param [in] ARG0 ARG0 Pointer to the command structure returned by tgKN_GPU_EXT__WORK__Acquire_Command.
    @param [in] ARG1 Pointer to a font data structure.
    @return UID for the initialized resource instance, or the INVALID ID otherwise. */
TgEXTN TgKN_GPU_TX_IMG_INST_ID
tgKN_GPU__CMD__TX_IMG_Inst__Font_ROM(
    STg2_KN_GPU_CMD_PC ARG0, STg2_KN_GPU_FONT_PC ARG1 );

/*# defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
#endif

#if TgS_DEBUG__KERNEL || TgS_DEBUG__RENDER

/** @brief Create a resource instance of a texture filled with a constant colour.
    @param [in] ARG0 ARG0 Pointer to the command structure returned by tgKN_GPU_EXT__WORK__Acquire_Command.
    @param [in] ARG1 Integer width of the texture to be created.
    @param [in] ARG2 Integer height of the texture to be created.
    @param [in] ARG3 Pointer to a UTF8 string to name the resource.
    @return UID for the initialized resource instance, or the INVALID ID otherwise. */
TgEXTN TgKN_GPU_TX_IMG_INST_ID
tgKN_GPU__CMD__TX_IMG_Inst__Init_MIP(
    STg2_KN_GPU_CMD_PC ARG0, TgUINT_E32 ARG1, TgUINT_E32 ARG2, TgCHAR_U8_CPCU ARG3 );

/** @brief Create a resource instance of a texture filled with a constant colour.
    @param [in] ARG0 ARG0 Pointer to the command structure returned by tgKN_GPU_EXT__WORK__Acquire_Command.
    @param [in] ARG1 Integer width of the texture to be created.
    @param [in] ARG2 Integer height of the texture to be created.
    @param [in] ARG3 Pointer to a UTF8 string to name the resource.
    @return UID for the initialized resource instance, or the INVALID ID otherwise. */
TgEXTN TgKN_GPU_TX_IMG_INST_ID
tgKN_GPU__CMD__TX_IMG_Inst__Init_Gamma_Test(
    STg2_KN_GPU_CMD_PC ARG0, TgUINT_E32 ARG1, TgUINT_E32 ARG2, TgCHAR_U8_CPCU ARG3 );

/** @brief Create a resource instance of a texture filled with a constant colour.
    @param [in] ARG0 ARG0 Pointer to the command structure returned by tgKN_GPU_EXT__WORK__Acquire_Command.
    @param [in] ARG1 Integer width of the texture to be created.
    @param [in] ARG2 Integer height of the texture to be created.
    @param [in] ARG3 Structure of a 32bit colour used for the 1st colour of the checker pattern.
    @param [in] ARG4 Structure of a 32bit colour used for the 2nd colour of the checker pattern.
    @param [in] ARG5 Pointer to a UTF8 string to name the resource.
    @return UID for the initialized resource instance, or the INVALID ID otherwise. */
TgEXTN TgKN_GPU_TX_IMG_INST_ID
tgKN_GPU__CMD__TX_IMG_Inst__Init_Checker_Pattern(
    STg2_KN_GPU_CMD_PC ARG0, TgUINT_E32 ARG1, TgUINT_E32 ARG2, TgCOLOUR32_C ARG3, TgCOLOUR32_C ARG4, TgCHAR_U8_CPCU ARG5 );

/*# TgS_DEBUG__KERNEL || TgS_DEBUG__RENDER */
#endif


/* ---- GPU - Debug -------------------------------------------------------------------------------------------------------------------------------------------------------------- */

#if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)

/** @brief Initialize a new context (if one is available). [Single-Threaded]
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU__Host__Init_Debug( TgVOID );

/** @brief Free the context and all associated resource, returning it to a free pool. */
TgEXTN TgVOID
tgKN_GPU__Host__Free_Debug( TgVOID );

/** @brief Initialize a new context (if one is available). [Single-Threaded]
    @param [in] ARG0 UID of the context.
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU__Execute__Init_Debug(
    TgKN_GPU_CXT_EXEC_ID_C ARG0 );

/** @brief Free the context and all associated resource, returning it to a free pool.
    @param [in] ARG0 UID of the context. */
TgEXTN TgVOID
tgKN_GPU__Execute__Free_Debug(
    TgKN_GPU_CXT_EXEC_ID_C ARG0 );

/** @brief Initialize render debug output resources.
    @param [in] ARG0 Pointer to the command structure returned by tgKN_GPU_EXT__WORK__Acquire_Command.
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU__Execute__Init_Debug__Create_Resources(
    STg2_KN_GPU_CMD_PC TgANALYSIS_NO_NULL ARG0 );

/** @brief Initialize render debug output resources.
    @param [in] ARG0 Pointer to the command structure returned by tgKN_GPU_EXT__WORK__Acquire_Command. */
TgEXTN TgVOID
tgKN_GPU__Execute__Free_Debug__Destroy_Resources(
    STg2_KN_GPU_CMD_PC TgANALYSIS_NO_NULL ARG0 );

/** @brief Initialize a new context (if one is available). [Single-Threaded]
    @param [in] ARG0 UID of the context.
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU__Swap__Init_Debug(
    TgKN_GPU_CXT_SWAP_ID_C ARG0 );

/** @brief Free the context and all associated resource, returning it to a free pool.
    @param [in] ARG0 UID of the context. */
TgEXTN TgVOID
tgKN_GPU__Swap__Free_Debug(
    TgKN_GPU_CXT_SWAP_ID_C ARG0 );


TgEXTN TgVOID
tgKN_GPU_DBG_Init_Mesh_Sphere(
    TgKN_GPU_DBG_PM_Generate_PC ARG0 );

TgEXTN TgVOID
tgKN_GPU_DBG_Init_Mesh_Capsule_Cap_0(
    TgKN_GPU_DBG_PM_Generate_PC ARG0 );

TgEXTN TgVOID
tgKN_GPU_DBG_Init_Mesh_Capsule_Cap_1(
    TgKN_GPU_DBG_PM_Generate_PC ARG0 );

TgEXTN TgVOID
tgKN_GPU_DBG_Init_Mesh_Capsule_Tube(
    TgKN_GPU_DBG_PM_Generate_PC ARG0 );

TgEXTN TgVOID
tgKN_GPU_DBG_Init_Mesh_Cone(
    TgKN_GPU_DBG_PM_Generate_PC ARG0 );

TgEXTN TgVOID
tgKN_GPU_DBG_Init_Mesh_Cylinder(
    TgKN_GPU_DBG_PM_Generate_PC ARG0 );

TgEXTN TgVOID
tgKN_GPU_DBG_Init_Mesh_Tube(
    TgKN_GPU_DBG_PM_Generate_PC ARG0 );

TgEXTN TgVOID
tgKN_GPU_DBG_Init_Mesh_Box(
    TgKN_GPU_DBG_PM_Generate_PC ARG0 );

TgEXTN TgVOID
tgKN_GPU_DBG_Init_Mesh_Plane(
    TgKN_GPU_DBG_PM_Generate_PC ARG0 );

#if TgCOMPILE__CONSOLE

TgEXTN TgVOID
tgKN_GPU_Set_CN_Render_Text(
    KTgCN_CHANEL_SEVERITY_C ARG0, TgCHAR_U8_PP ARG1, TgRSIZE ARG2, TgRSIZE ARG3 );

/*# TgCOMPILE__CONSOLE */
#endif

/*# defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
#endif


/* ---- GPU - Utility Functions -------------------------------------------------------------------------------------------------------------------------------------------------- */

/** @brief Convert a GPU format enumeration to UTF-8 string representation.
    @param [in] ARG0 GPU format enumeration value.
    @return Pointer to UTF-8 string representation of the format. */
TgEXTN TgCHAR_U8_CP
tgKN_GPU_FMT_To_USZ(
    ETgKN_GPU_EXT_FORMAT_C ARG0 );

/** @brief Convert a GPU format enumeration to wide character string representation.
    @param [in] ARG0 GPU format enumeration value.
    @return Pointer to wide character string representation of the format. */
TgEXTN TgCHAR_WC_CP
tgKN_GPU_FMT_To_WSZ(
    ETgKN_GPU_EXT_FORMAT_C ARG0 );

/** @brief Get the number of bytes per pixel for a given GPU format enumeration.
    @param [in] ARG0 GPU format enumeration value.
    @return Number of bytes per pixel for the format, or 0 if the format is unknown or compressed. */
TgEXTN TgRSIZE
tgKN_GPU_FMT_Bytes_Per_Pixel(
    ETgKN_GPU_EXT_FORMAT_C ARG0 );


/* ---- GPU - Resource ----------------------------------------------------------------------------------------------------------------------------------------------------------- */

#define __PARENT_FILE__ "TgS Kernel [GPU] - Internal.h"
#define ENABLE_RELOAD_GUARD
#include "TgS KERNEL/TgS Kernel [GPU] - Resource [INC].h"
#undef ENABLE_RELOAD_GUARD
#undef __PARENT_FILE__

#define TGS_KERNEL_GPU_INTERNAL_H


/*# defined (ENABLE_RELOAD_GUARD) */
#else

/* ---- GPU - Resource (Data) Libraries ------------------------------------------------------------------------------------------------------------------------------------------ */
/* Defined in TgS Kernel - Resource LIB [GPU] [Common].c */

/** @brief  */
TgEXTN TgVOID
T(tgKN_GPU_,_LIB__Init)( TgVOID );

/** @brief  */
TgEXTN TgVOID
T(tgKN_GPU_,_LIB__Stop)( TgVOID );

/** @brief  */
TgEXTN TgVOID
T(tgKN_GPU_,_LIB__Free)( TgVOID );

/** @brief  */
TgEXTN TgRSIZE
T(tgKN_GPU_,_Query_Fixed_Memory)( TgVOID );


#if defined(MACRO_BUILD_TEXTURE)

/** @brief 
    @param [in] ARG0 Integer index of the context. */
TgEXTN TgVOID
T(tgKN_GPU_,_Inst_LIB__Init)(
    TgKN_GPU_CXT_EXEC_ID_C ARG0 );

/** @brief 
    @param [in] ARG0 Integer index of the context. */
TgEXTN TgVOID
T(tgKN_GPU_,_Inst_LIB__Free)(
    TgKN_GPU_CXT_EXEC_ID_C ARG0 );

/** @internal Fast validation check for a resource instance library. */
TgINLINE TgVOID
T(tgKN_GPU_,_INST_LIB_DESC__Check)(
    T(STg2_KN_GPU_,_INST_LIB_DESC_CPCU) ARG0 );

/*# defined(MACRO_BUILD_TEXTURE) */
#endif


/* ---- GPU - Resource ----------------------------------------------------------------------------------------------------------------------------------------------------------- */

/** @brief Initialize a resource as part of the loading process.
    @param [in] ARG0 UID of the kernel file object to be used.
    @param [in] ARG1 Integer for the offset into the input object to begin reading.
    @param [in] ARG2 Pointer to a descriptor for the resource type.
    @param [in] ARG3 Enumeration of the memory allocation method used for the resource.
    @param [in] ARG4 UID of the resource to be modified.
    @param [in] ARG5 Pointer to the GPU resource library to be used.
    @return Result Code. */
TgEXTN TgRESULT
T(tgKN_GPU_,__Execute_Load)(
    TgKN_FILE_ID_C ARG0, TgRSIZE_C ARG1, T(STg2_KN_GPU_,_DESC_CPC) ARG2, TgUINT_E64_C ARG3, T(TgKN_GPU_,_ID_C) ARG4 );

/** @brief Free all associated resources with the resource UID.
    @param [in] ARG0 UID of the resource to be modified.
    @param [in] ARG1 Pointer to the GPU resource library to be used. */
TgEXTN TgVOID
T(tgKN_GPU_,__Execute_Free)(
    T(TgKN_GPU_,_ID_C) ARG0 );

/** @brief Increment the reference count on the GPU resource.
    @param [in] ARG0 UID of the resource to be modified.
    @param [in] ARG1 Pointer to the GPU resource library to be used.
    @return UID for the loaded resource, or the INVALID ID otherwise. */
TgEXTN T(TgKN_GPU_,_ID)
T(tgKN_GPU_,__IncRef)(
    T(TgKN_GPU_,_ID_C) ARG0 );

/** @brief Decrements the reference count on the GPU resource, and free all associated resources when it reaches zero.
    @param [in] ARG0 UID of the resource to be modified.
    @return UID for the loaded resource, or the INVALID ID otherwise. */
TgEXTN T(TgKN_GPU_,_ID)
T(tgKN_GPU_,__Release)(
    T(TgKN_GPU_,_ID_C) ARG0 );


/* =============================================================================================================================================================================== */

/*# defined (ENABLE_RELOAD_GUARD) */
#endif

/*# !defined(TGS_KERNEL_INTERNAL_GPU_H) && defined(TgBUILD_FEATURE__GRAPHICS) */
#endif
