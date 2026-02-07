/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Kernel [GPU].h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.20 | »GUID« DE461472-5528-4A5B-A7F4-09CCAD73387B */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_KERNEL_GPU_H) && defined(TgBUILD_FEATURE__GRAPHICS)
#if !defined (ENABLE_RELOAD_GUARD)

#include "TgS KERNEL/TgS Kernel [GPU] - Constants.h"
#include "TgS KERNEL/TgS Kernel [GPU] - Type.h"
#include "TgS KERNEL/TgS Kernel [GPU] [EXT].h"


/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Kernel GPU Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/** @brief Standard Module function: First part of initialization process. Set the state of the module.
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_Module_Init( TgVOID );

/** @brief Standard Module function: Last part of initialization process. Used for setup and other necessary tasks prior to the use of the module.
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_Module_Boot( TgVOID );

/** @brief Standard Module function: Used for close the module as part of the shutdown process. Module is not to be used after this is executed. */
TgEXTN TgRESULT
tgKN_GPU_Module_Stop( TgVOID );

/** @brief Standard Module function: Final part of shutdown process. Release any remaining allocated memory, and reset the state of the module. */
TgEXTN TgRESULT
tgKN_GPU_Module_Free( TgVOID );

/** @brief Standard Module function: Update the module, usually called on a per-frame basis, where the parameter is the forward time step amount.
    @param [in] ARG0 Amount of time to step forward the module in milliseconds.
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_Module_Update(
    TgFLOAT32_C ARG0 );

/** @brief Standard Module function: Recall the amount of global (static) memory used by the module.
    @return Amount of global (static) memory used by the module. This is hard coded and thus, not explicitly correct. */
TgEXTN TgRSIZE
tgKN_GPU_Query_Fixed_Memory( TgVOID );

#if TgS_STAT__KERNEL
/** @brief Standard Module function: Output relevant stats for the module.
    @param [in,out] OUT0 Pointer to an output object. */
TgEXTN TgVOID
tgKN_GPU_Stats(
    STg2_Output_P OUT0 );
#endif


/* ---- GPU - Enumeration -------------------------------------------------------------------------------------------------------------------------------------------------------- */

/** @brief Have the system enumerate (internally) all available GPU related resources. */
TgEXTN TgRESULT
tgKN_GPU_Enumerate( TgVOID );

/** @brief Free all the resources that were allocated during enumeration. */
TgEXTN TgVOID
tgKN_GPU_Enumerate_Free_Resources( TgVOID );


/* ---- GPU - Contexts ----------------------------------------------------------------------------------------------------------------------------------------------------------- */

/*  Context - Host - Host/CPU resource context (expect one per host/cpu memory controller).
    Context - Device - A virtual or physical GPU construct, which may include one or more physical GPU devices (nodes).
    Context - Execute - An execution context is bound to a single GPU node.
    Context - Output - An output device (TV, monitor) that is associated with the device, and bound to a specific node (execution context).
    Context - Data - Used to manage resource and resource instances associated with a specific memory controller.
    Context - External - Resource IDs available to other modules and customers of the GPU module/system.

    Could extend the model to support multiple GPUs sharing a single memory controller (N Execute to 1 Data).

    Examples (all under a single device, or a separate devices):
    1x 1-GPU video card, 1 output: 1 Device, 1 Execute, 1 Output, 1 Data, 1 External
    1x 1-GPU video card, 2 output: 1 Device, 1 Execute, 2 Output, 1 Data, 1 External
    2x 1-GPU video card, 1 output: 1 Device, 2 Execute, 1 Output, 2 Data, 2 External
    2x 1-GPU video card, 1 output: 2 Device, 2 Execute, 1 Output, 2 Data, 2 External */

/** @brief Fill out a GPU context selection data structure based on the current read configuration state. 
    @param [out] OUT0 Pointer to a selection data structure.
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_Select_Context__Init_From_Config(
    STg2_KN_GPU_Select_PCU TgANALYSIS_NO_NULL OUT0 );

/** @brief Fill a selection data structure based on internal data filled out by a call to Enumerate.
    @param [in] ARG0 Pointer to a selection data structure.
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_Select_Context__Init_From_Enumeration(
    STg2_KN_GPU_Select_PCU TgANALYSIS_NO_NULL ARG0 );

/** @brief Validate and update the selection data structure based on internal data, of which most is discovered during an enumeration. 
    @param [in,out] OUT0 Pointer to a selection data structure. 
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_Select_Context__Validate(
    STg2_KN_GPU_Select_CPCU TgANALYSIS_NO_NULL OUT0 );

/** @brief Create a new GPU context based on the selection data structure.
    @param [out] OUT0 Pointer to result data structure that is filled in with the resulting UID(s) of the allocated contexts.
    @param [in] ARG1 Pointer to a selection structure describing the set of initial resources to be created for a new GPU context. 
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_Contexts__Init(
    STg2_KN_GPU_Init_Result_PCU TgANALYSIS_NO_NULL OUT0, STg2_KN_GPU_Select_CPCU TgANALYSIS_NO_NULL ARG1 );

/** @brief Free a GPU context, and all associated resources assuming that they are not shared with other contexts. */
TgEXTN TgVOID
tgKN_GPU_Contexts__Free( TgVOID );

/** @brief Get the array of strings of the accessible GPU devices.
    @param [out] OUT0 Pointer of an array of adapter points that will contain the list of all enumerated GPU adapters.
    @param [in] ARG1 Integer count of the number of strings that can be assigned into OUT0. 
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU__Host__Query_Physical_Device_List(
    STg2_KN_GPU_Physical_Device_CPP TgANALYSIS_NO_NULL OUT0, TgUINT_E32_C ARG1 );


/* ---- GPU Resource ID ---------------------------------------------------------------------------------------------------------------------------------------------------------- */

/* Recall this file for each resource type defined by the module to define the set of Generic Functions. */
#define __PARENT_FILE__ "TgS Kernel [GPU].h"
#define ENABLE_RELOAD_GUARD
#include "TgS KERNEL/TgS Kernel [GPU] - Resource [INC].h"
#undef ENABLE_RELOAD_GUARD
#undef __PARENT_FILE__

#define TGS_KERNEL_GPU_H


/* ---- GPU - Resource - Texture ------------------------------------------------------------------------------------------------------------------------------------------------- */

/** @brief Load a TIFF (using LibTIFF) using a file name and path. Supported only in non-Final builds.
    @param [in] ARG0 ARG0 Pointer to the command context returned by tgKN_GPU_EXT__WORK__Acquire_Command.
    @param [in] ARG1 UID for the mount location for HDD (OS) access.
    @param [in] ARG2 Pointer to a UTF8 string holding the path location (can be NULL).
    @param [in] ARG3 Pointer to a UTF8 string holding the file name (cannot be NULL).
    @param [in] ARG4 Enumeration for the type of allocator to use. */
TgEXTN TgKN_GPU_TX_IMG_INST_ID
tgKN_GPU__CMD__TX_IMG__Load_TIFF_From_OS_File_System(
    STg2_KN_GPU_CMD_PC TgANALYSIS_NO_NULL ARG0, TgKN_FS_MOUNT_ID_C ARG1, TgCHAR_U8_CPC TgANALYSIS_OK_NULL ARG2, TgCHAR_U8_CPC TgANALYSIS_NO_NULL ARG3, TgUINT_E64_C ARG4 );

/** @brief Load a TIFF (using LibTIFF) using a file UID.
    @param [in] ARG0 ARG0 Pointer to the command context returned by tgKN_GPU_EXT__WORK__Acquire_Command.
    @param [in] ARG1 UID for the file.
    @param [in] ARG2 Integer offset into the file to begin the file operation.
    @param [in] ARG3 Enumeration for the type of allocator to use. */
TgEXTN TgKN_GPU_TX_IMG_INST_ID
tgKN_GPU__CMD__TX_IMG__Load_TIFF_From_KN_File_System(
    STg2_KN_GPU_CMD_PC TgANALYSIS_NO_NULL ARG0, TgKN_FILE_ID_C ARG1, TgRSIZE_C ARG2, TgUINT_E64_C ARG3 );


/* ---- GPU - Utilities ---------------------------------------------------------------------------------------------------------------------------------------------------------- */

/** @brief Initialize a camera based on a configuration structure.
    @param [out] OUT0 Pointer to a camera to be initialized.
    @param [in] ARG1 Pointer to a camera configuration structure.
    @param [in] ARG2 Vector (F32) holding the world up direction. */
TgEXTN TgVOID
tgKN_GPU_Init_Camera(
     STg2_KN_GPU_Camera_P OUT0, STg2_KN_GPU_Camera_Configuration_CP ARG1, TgVEC_F32_04_1_C ARG2 );

/** @brief Based on the output descriptor, modify the input colour to the result output colour that can be used directly by the GPU without any additional colour correction.
    @details Used specifically during testing to validate colour correctness of different frame buffers using only a clear command.
    @param [in] ARG0 Vector (F32) holding a set of RGBA values.
    @param [in] ARG1 Pointer to a descriptor of the output target.
    @return Vector (F32) holding a set of corrected RGBA values. */
TgEXTN TgVEC_S_F32_04_1
tgKN_GPU_Colour_Grading_CPU(
    TgVEC_S_F32_04_1 ARG0, STg2_KN_GPU_Output_DESC_CPC TgANALYSIS_NO_NULL ARG1 );


/* ---- GPU - Debug -------------------------------------------------------------------------------------------------------------------------------------------------------------- */

#if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)

/** @brief Retrieve the texture information for a DOS Font ROM.
    @param [out] OUT0 Pointer to a data structure to hold the results.
    @param [in] ARG1 Enumeration selecting the DOS Font to use.
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_Query_DOS_Font_ROM_TX(
    STg2_KN_GPU_FONT_TX_PC TgANALYSIS_NO_NULL OUT0, ETgKN_GPU_DOS_FONT_ROM_C ARG1 );

/** @brief Initialize the debug render descriptor. 
    @param [out] OUT0 Pointer to a debug render descriptor to be initialized.
    @param [in] ARG1 Pointer to the command context returned by tgKN_GPU_EXT__WORK__Acquire_Command.
    @param [in] ARG2 Pointer to a camera descriptor. */
TgEXTN TgVOID
tgKN_GPU__CMD__Init_DBG_Render_DESC(
    STg2_KN_GPU_DBG_Render_DESC_P TgANALYSIS_NO_NULL OUT0, STg2_KN_GPU_CMD_PC TgANALYSIS_NO_NULL ARG1, STg2_KN_GPU_Camera_CPC TgANALYSIS_OK_NULL ARG2 );

/** @brief Render text (using the default DOS fonts), in view space, just prior to present. This will keep the text within the limits of the provided rectangle.
    @param [in] ARG0 Pointer to the command context returned by tgKN_GPU_EXT__WORK__Acquire_Command.
    @param [in] ARG1 Pointer to a debug string descriptor. */
TgEXTN TgVOID
tgKN_GPU__CMD__Render_Debug_Text_Box( 
    STg2_KN_GPU_CMD_PC TgANALYSIS_NO_NULL ARG0, STg2_KN_GPU_DBG_Text_CI_CPC TgANALYSIS_NO_NULL ARG1 );

/** @brief Render a debug line. This will buffer up the render calls until either a new render target is set (which will flush the buffer), or it is filled.
    @param [in] ARG0 Pointer to the command context returned by tgKN_GPU_EXT__WORK__Acquire_Command.
    @param [in] ARG1 Vector (F32) holding the start position of the line.
    @param [in] ARG2 Vector (F32) holding the RGBA colour of the line at the start.
    @param [in] ARG3 Vector (F32) holding the end position of the line.
    @param [in] ARG4 Vector (F32) holding the RGBA colour of the line at the end. 
    @param [in] ARG5 Vector (F32) holding the value for the line thickness. */
TgEXTN TgRESULT
tgKN_GPU__CMD__Add_Debug_Line(
    STg2_KN_GPU_CMD_PC TgANALYSIS_NO_NULL ARG0, TgVEC_F32_04_1_C ARG1, TgVEC_F32_04_1_C ARG2, TgVEC_F32_04_1_C ARG3, TgVEC_F32_04_1_C ARG4, TgVEC_F32_04_1_C ARG5 );

/** @brief Flush the debug line renderer.
    @param [in] ARG0 Pointer to the command context returned by tgKN_GPU_EXT__WORK__Acquire_Command. */
TgEXTN TgVOID
tgKN_GPU__CMD__Render_Debug_Line(
    STg2_KN_GPU_CMD_PC TgANALYSIS_NO_NULL ARG0 );

/** @brief Render a debug set of axes. This will buffer up the render calls until either a new render target is set (which will flush the buffer), or it is filled.
    @param [in] ARG0 Pointer to the command context returned by tgKN_GPU_EXT__WORK__Acquire_Command.
    @param [in] ARG1 Vector (F32) holding the position of the axes.
    @param [in] ARG2 Float value for the scale of the axes. */
TgEXTN TgVOID
tgKN_GPU__CMD__Render_Debug_Axes(
    STg2_KN_GPU_CMD_PC TgANALYSIS_NO_NULL ARG0, TgVEC_F32_04_3_CPCU TgANALYSIS_NO_NULL ARG1, TgVEC_F32_04_1 ARG2 );

/** @brief Render a debug n-gon. This will buffer up the render calls until either a new render target is set (which will flush the buffer), or it is filled.
    @param [in] ARG0 Pointer to the command context returned by tgKN_GPU_EXT__WORK__Acquire_Command.
    @param [in] ARG1 Vector (F32) holding the RGBA colour of the n-gon.
    @param [in] ARG2 Pointer to an array of Vector (F32) holding the position of each vertex of the n-gon.
    @param [in] ARG3 Float value for the scale of the axes.
    @param [in] ARG4 Integer count of the number of vertices in the n-gon (must be >= 3). */
TgEXTN TgVOID
tgKN_GPU__CMD__Render_Debug_nGon(
    STg2_KN_GPU_CMD_PC TgANALYSIS_NO_NULL ARG0, TgVEC_F32_04_1 ARG1, TgVEC_F32_04_3_CPCU TgANALYSIS_NO_NULL ARG2, TgFLOAT32_C ARG3, TgSINT_E32_C ARG4 );

/** @brief Render a debug frustum. This will buffer up the render calls until either a new render target is set (which will flush the buffer), or it is filled.
    @param [in] ARG0 Pointer to the command context returned by tgKN_GPU_EXT__WORK__Acquire_Command.
    @param [in] ARG1 Vector (F32) holding the RGBA colour of the frustum.
    @param [in] ARG2 Pointer to an array of eight Vector (F32) holding the position of each corner of the frustum.
    @param [in] ARG3 Pointer to an array of six Vector (F32) holding the normal of each plane of the frustum. */
TgEXTN TgVOID
tgKN_GPU__CMD__Render_Debug_Frustum(
    STg2_KN_GPU_CMD_PC TgANALYSIS_NO_NULL ARG0, TgVEC_F32_04_1 ARG1, TgVEC_F32_04_4_CPCU TgANALYSIS_NO_NULL ARG2, TgVEC_F32_04_4_CPCU TgANALYSIS_NO_NULL ARG3 );

/** @brief Render a debug camera frustum. This will buffer up the render calls until either a new render target is set (which will flush the buffer), or it is filled.
    @param [in] ARG0 Pointer to the command context returned by tgKN_GPU_EXT__WORK__Acquire_Command.
    @param [in] ARG1 Vector (F32) holding the RGBA colour of the frustum.
    @param [in] ARG2 Pointer to a camera object. */
TgEXTN TgVOID
tgKN_GPU__CMD__Render_Debug_Camera_Frustum(
    STg2_KN_GPU_CMD_PC TgANALYSIS_NO_NULL ARG0, TgVEC_F32_04_1_C ARG1, STg2_KN_GPU_Camera_CPCU TgANALYSIS_NO_NULL ARG2 );

/*# defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
#endif

#if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) && TgCOMPILE__CONSOLE

/** @brief Render the debug console (defined in TgS COMMON, in interactive mode), just prior to present, using tgKN_GPU__CMD__Render_Debug_Text_Box.
    @param [in] ARG0 ARG0 Pointer to the command context returned by tgKN_GPU_EXT__WORK__Acquire_Command. */
TgEXTN TgVOID
tgKN_GPU__CMD__Render_Console_Text( 
    STg2_KN_GPU_CMD_PC ARG0 );

/*# defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) && TgCOMPILE__CONSOLE */
#endif


/* ---- GPU - Unit Test Helpers -------------------------------------------------------------------------------------------------------------------------------------------------- */

/** @brief Fully populate a selection structure.
    @param [out] OUT0 Pointer to a data structure to hold the results.
    @param [in] ARG1 Boolean flag set to true to create a single large window in the middle of the monitor, false to make a 3x3 grid.
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_UNIT_TEST__UTIL__Init_Select(
    STg2_KN_GPU_Select_PC OUT0, TgBOOL ARG1 );


/*# defined (ENABLE_RELOAD_GUARD) */
#else

/* ---- Resource - GPU ----------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* Resource instances are bound to a specific render resource context.  A single copy of the raw resource is stored in global memory.  Depending on the platform, instances of the
   resource may have context specific copies or it may be shared. */
/* Defined in TgS Kernel [GPU] - Resource [Common].c */

#if !defined(TGS_FINAL)
/** @brief Load a resource from a named file and path.
    @param [in] ARG0 UID for the kernel mount location to be used.
    @param [in] ARG1 String of the path, relative to the mount location, of the file.
    @param [in] ARG2 String of the file name.
    @param [in] ARG3 Enumeration of the memory allocation method used for the resource.
    @return UID for the loaded resource, or the INVALID ID otherwise. */
TgEXTN T(TgKN_GPU_,_ID)
T(tgKN_GPU_,__Load_From_OS_File_System)(
    TgKN_FS_MOUNT_ID_C ARG0, TgCHAR_U8_CPC TgANALYSIS_NO_NULL ARG1, TgCHAR_U8_CPC TgANALYSIS_NO_NULL ARG2, TgUINT_E64_C ARG3 );
/*# !defined(TGS_FINAL) */
#endif

/** @brief Load a resource from the given backing store.
    @param [in] ARG0 UID of the kernel file object to be used.
    @param [in] ARG1 Integer for the offset into the input object to begin reading.
    @param [in] ARG2 Enumeration of the memory allocation method used for the resource.
    @return UID for the loaded resource, or the INVALID ID otherwise. */
TgEXTN T(TgKN_GPU_,_ID)
T(tgKN_GPU_,__Load_From_KN_File_System)(
    TgKN_FILE_ID_C ARG0, TgRSIZE_C ARG1, TgUINT_E64_C ARG2 );

/** @brief Create a resource from a resource descriptor.
    @param [in] ARG0 Pointer to a descriptor for the resource type.
    @param [in] ARG1 Enumeration of the memory allocation method used for the resource.
    @return UID for the loaded resource, or the INVALID ID otherwise. */
TgEXTN T(TgKN_GPU_,_ID)
T(tgKN_GPU_,__Load_From_Memory)(
    T(STg2_KN_GPU_,_DESC_CPC) ARG0, TgUINT_E64_C ARG1 );

#if defined(MACRO_BUILD_TEXTURE)
/** @brief Initialize a resource instance from a given resource.
    @param [in] ARG0 ARG0 Pointer to the command context returned by tgKN_GPU_EXT__WORK__Acquire_Command.
    @param [in] ARG1 UID for the resource to be instanced.
    @param [in] ARG2 Pointer to a string used for debugging purposes.
    @return UID for the initialized resource instance, or the INVALID ID otherwise. */
TgEXTN T(TgKN_GPU_,_INST_ID)
T(tgKN_GPU__CMD__,_Inst__Init)(
    STg2_KN_GPU_CMD_PC TgANALYSIS_NO_NULL ARG0, T(TgKN_GPU_,_ID_C) ARG1, TgCHAR_U8_CPCU TgANALYSIS_NO_NULL ARG2 );

/** @brief Increment the reference count on a resource instance.
    @param [in] ARG0 UID for the resource instance.
    @return UID for the resource instance if it remains valid, or the INVALID ID otherwise. */
TgEXTN T(TgKN_GPU_,_INST_ID)
T(tgKN_GPU_, _Inst__IncRef)(
    T(TgKN_GPU_,_INST_ID_C) tiRSI );

/** @brief Decrements the reference count on a resource instance, and free all associated resources when it reaches zero.
    @param [in] ARG0 ARG0 Pointer to the command context returned by tgKN_GPU_EXT__WORK__Acquire_Command.
    @param [in] ARG1 UID for the resource instance.
    @return UID for the resource instance if it remains valid, or the INVALID ID otherwise. */
TgEXTN T(TgKN_GPU_,_INST_ID)
T(tgKN_GPU__CMD__, _Inst__Release)(
    STg2_KN_GPU_CMD_PC TgANALYSIS_NO_NULL ARG0, T(TgKN_GPU_,_INST_ID_C) ARG1 );
/*# defined(MACRO_BUILD_TEXTURE) */
#endif


/* ---- GPU - Resource - Texture ------------------------------------------------------------------------------------------------------------------------------------------------- */
#if defined(MACRO_BUILD_TEXTURE)
/** @brief Create a resource instance of a texture filled with a constant colour.
    @param [in] ARG0 ARG0 Pointer to the command context returned by tgKN_GPU_EXT__WORK__Acquire_Command.
    @param [in] ARG1 32bit colour value to be used.
    @param [in] ARG2 String containing the name to give the texture (used in debug builds).
    @return UID for the initialized resource instance, or the INVALID ID otherwise. */
TgEXTN T(TgKN_GPU_,_INST_ID)
T(tgKN_GPU__CMD__,_Inst__Init_Colour)(
    STg2_KN_GPU_CMD_PC TgANALYSIS_NO_NULL ARG0, TgCOLOUR32_C ARG1, TgCHAR_U8_CPCU TgANALYSIS_NO_NULL ARG2 );

/** @brief Create a resource instance of a texture with the provided format and dimensions.
    @param [in] ARG0 ARG0 Pointer to the command context returned by tgKN_GPU_EXT__WORK__Acquire_Command.
    @param [in] ARG1 Enumeration for the GPU allocator to be used.
    @param [in] ARG2 Pointer to a descriptor for the texture type to be created.
    @return UID for the created texture instance, or INVALID ID otherwise. */
TgEXTN T(TgKN_GPU_,_INST_ID)
T(tgKN_GPU__CMD__,_Inst__Create)(
    STg2_KN_GPU_CMD_PC TgANALYSIS_NO_NULL ARG0, TgUINT_E64_C ARG1, T(STg2_KN_GPU_,_DESC_CPCU) TgANALYSIS_NO_NULL ARG2 );


/*# defined(MACRO_BUILD_TEXTURE) */
#endif


/* =============================================================================================================================================================================== */

/*# defined (ENABLE_RELOAD_GUARD) */
#endif

/*# !defined(TGS_KERNEL_GPU_H) && defined(TgBUILD_FEATURE__GRAPHICS) */
#endif
