/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Kernel [GPU] - Internal.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.20 | »GUID« DE461472-5528-4A5B-A7F4-09CCAD73387B */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_KERNEL_INTERNAL_GPU_H) && defined(TgBUILD_FEATURE__GRAPHICS)
#if !defined (ENABLE_RELOAD_GUARD)

#include "TgS Common.h"

#include "TgS Ring 0 - Type.h"
#include "TgS Ring 2 - Type.h"

#include "TgS Kernel.h"

#include "TgS Kernel [GPU].h"
#include "TgS Kernel [GPU] - Internal - Type.h"
#include "TgS Kernel [GPU] - Internal - Data.h"
#include "TgS Kernel [GPU] - Internal [EXT].h"

#include "TgS COMMON/TgS Common.inl"


/* == Kernel ===================================================================================================================================================================== */

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

/** @brief Initialize render debug output resources.
    @param [in] ARG0 UID of the execution context.
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU__Execute__Init_Debug(
    TgKN_GPU_CXT_EXEC_ID_C ARG0 );

/** @brief Initialize render debug output resources.
    @param [in] ARG0 UID of the execution context.
    @return Result Code. */
TgEXTN TgVOID
tgKN_GPU__Execute__Free_Debug(
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

#if TgCOMPILE__RENDER_DEBUG_OUTPUT

/** @brief Initialize render debug output resources.
    @param [in] ARG0 Union of a pointer to the command list data structure returned by tgKN_GPU_EXT__Execute__Command_List_Acquire.
    @param [in] ARG1 UID of the context. */
TgEXTN TgVOID
tgKN_GPU__SwapChain__Present_Print_Debug_Stats(
    UTg2_KN_GPU_CMD_C ARG0, TgKN_GPU_CXT_SWAP_ID_C ARG1 );

/*# TgCOMPILE__RENDER_DEBUG_OUTPUT */
#endif


/* ---- GPU - Resource - Texture ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* Resource instances are bound to a specific render resource context. A single copy of the raw resource is stored in global memory. Depending on the platform, instances of the 
   resource may have context specific copies or it may be shared. */

/** @brief Create a off-screen render target. 
    @param [in] ARG0 Union of a pointer to the command list data structure returned by tgKN_GPU_EXT__Execute__Command_List_Acquire.
    @param [in] ARG1 Enumeration of the memory allocation method used for the resource.
    @param [in] ARG2 Pointer to a texture image descriptor.
    @return UID for the initialized resource instance, or the INVALID ID otherwise. 
*/
TgEXTN TgKN_GPU_TX_IMG_INST_ID
tgKN_GPU_RT_IMG__Create(
    UTg2_KN_GPU_CMD_C ARG0, ETgKN_GPU_ALLOCATOR_C ARG1, STg2_KN_GPU_TX_IMG_DESC_CPCU ARG2 );

#if TgCOMPILE__RENDER_DEBUG_OUTPUT

/** @brief Create a resource instance of a texture filled with a constant colour.
    @param [in] ARG0 Union of a pointer to the command list data structure returned by tgKN_GPU_EXT__Execute__Command_List_Acquire.
    @param [in] ARG1 Pointer to a font data structure.
    @return UID for the initialized resource instance, or the INVALID ID otherwise. */
TgEXTN TgKN_GPU_TX_IMG_INST_ID
tgKN_GPU_TX_IMG_Inst__Font_ROM(
    UTg2_KN_GPU_CMD_C ARG0, STg2_KN_GPU_FONT_PC ARG1 );

/*# TgCOMPILE__RENDER_DEBUG_OUTPUT */
#endif

#if TgS_DEBUG__KERNEL || TgS_DEBUG__RENDER

/** @brief Create a resource instance of a texture filled with a constant colour.
    @param [in] ARG0 Union of a pointer to the command list data structure returned by tgKN_GPU_EXT__Execute__Command_List_Acquire.
    @param [in] ARG1 Integer width of the texture to be created.
    @param [in] ARG2 Integer height of the texture to be created.
    @param [in] ARG3 Pointer to a UTF8 string to name the resource.
    @return UID for the initialized resource instance, or the INVALID ID otherwise. */
TgEXTN TgKN_GPU_TX_IMG_INST_ID
tgKN_GPU_TX_IMG_Inst__Init_MIP(
    UTg2_KN_GPU_CMD_C ARG0, TgUINT_E32 ARG1, TgUINT_E32 ARG2, TgCHAR_U8_CPCU ARG3 );

/** @brief Create a resource instance of a texture filled with a constant colour.
    @param [in] ARG0 Union of a pointer to the command list data structure returned by tgKN_GPU_EXT__Execute__Command_List_Acquire.
    @param [in] ARG1 Integer width of the texture to be created.
    @param [in] ARG2 Integer height of the texture to be created.
    @param [in] ARG3 Pointer to a UTF8 string to name the resource.
    @return UID for the initialized resource instance, or the INVALID ID otherwise. */
TgEXTN TgKN_GPU_TX_IMG_INST_ID
tgKN_GPU_TX_IMG_Inst__Init_Gamma_Test(
    UTg2_KN_GPU_CMD_C ARG0, TgUINT_E32 ARG1, TgUINT_E32 ARG2, TgCHAR_U8_CPCU ARG3 );

/** @brief Create a resource instance of a texture filled with a constant colour.
    @param [in] ARG0 Union of a pointer to the command list data structure returned by tgKN_GPU_EXT__Execute__Command_List_Acquire.
    @param [in] ARG1 Integer width of the texture to be created.
    @param [in] ARG2 Integer height of the texture to be created.
    @param [in] ARG3 Structure of a 32bit colour used for the 1st colour of the checker pattern.
    @param [in] ARG4 Structure of a 32bit colour used for the 2nd colour of the checker pattern.
    @param [in] ARG4 Pointer to a UTF8 string to name the resource.
    @return UID for the initialized resource instance, or the INVALID ID otherwise. */
TgEXTN TgKN_GPU_TX_IMG_INST_ID
tgKN_GPU_TX_IMG_Inst__Init_Checker_Pattern(
    UTg2_KN_GPU_CMD_C ARG0, TgUINT_E32 ARG1, TgUINT_E32 ARG2, TgCOLOUR32_C ARG3, TgCOLOUR32_C ARG4, TgCHAR_U8_CPCU ARG5 );

/*# TgS_DEBUG__KERNEL || TgS_DEBUG__RENDER */
#endif


/* ---- GPU - Debug -------------------------------------------------------------------------------------------------------------------------------------------------------------- */

#if TgCOMPILE__RENDER_DEBUG_OUTPUT

TgEXTN TgVOID
tgKN_GPU_DBG_Init_Mesh_Sphere(
    TgKN_GPU_DBG_PM_Generate_PC ARG0 );

TgEXTN TgVOID
tgKN_GPU_DBG_Init_Mesh_Capsule(
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

/*# TgCOMPILE__RENDER_DEBUG_OUTPUT */
#endif

TgEXTN TgCHAR_U8_CP
tgKN_GPU_Format_To_String(
    ETgKN_GPU_EXT_FORMAT_C enFormat );


/* ---- GPU - Resource ----------------------------------------------------------------------------------------------------------------------------------------------------------- */

#define __PARENT_FILE__ "TgS Kernel [GPU] - Internal.h"
#define ENABLE_RELOAD_GUARD
#include "TgS KERNEL/TgS Kernel [GPU] - Resource [INC].h"
#undef ENABLE_RELOAD_GUARD
#undef __PARENT_FILE__

#define TGS_KERNEL_INTERNAL_GPU_H


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
    TgKN_FILE_ID_C ARG0, TgRSIZE_C ARG1, T(STg2_KN_GPU_,_DESC_CPC) ARG2, ETgKN_GPU_ALLOCATOR_C ARG3, T(TgKN_GPU_,_ID_C) ARG4 );

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
