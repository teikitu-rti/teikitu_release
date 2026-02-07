/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Kernel [GPU] [EXT].h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.20 | »GUID« DE461472-5528-4A5B-A7F4-09CCAD73387B */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_KERNEL_GPU_EXT_H) && defined(TgBUILD_FEATURE__GRAPHICS)
#define TGS_KERNEL_GPU_EXT_H
/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Extension (API) Functions                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- GPU - Contexts - Extension ----------------------------------------------------------------------------------------------------------------------------------------------- */

/** @brief Insert a fence into the given command list type queue, and wait for the GPU to pass it.
    @param [in] ARG0 UID for the Execution Context (GPU node).
    @param [in] ARG1 Enumeration selecting the command list type to be flushed. */
TgEXTN TgVOID 
tgKN_GPU_EXT__Execute__Cmd_Buffer_Flush(
    TgKN_GPU_CXT_EXEC_ID_C ARG0, ETgKN_GPU_EXT_COMMAND_C ARG1 );

/** @brief Insert a fence into every command queue, and wait for the GPU to pass them.
    @param [in] ARG0 UID for the Execution Context (GPU node). */
TgEXTN TgVOID
tgKN_GPU_EXT__Execute__Flush(
    TgKN_GPU_CXT_EXEC_ID_C ARG0 );

/** @brief Create a render target resource.
    @param [in] ARG0 UID for the execution context (GPU node).
    @param [in] ARG1 Pointer to the render target description structure.
    @return UID for the created render target. */
TgEXTN TgKN_GPU_RENDER_TARGET_ID
tgKN_GPU_EXT__Execute__Create_Render_Target(
    TgKN_GPU_CXT_EXEC_ID_C ARG0, STg2_KN_GPU_Render_Target_DESC_CPC ARG1 );

/** @brief Return a UID for a Work Context, which is the data structure used for issuing render commands.
    @param [in] ARG0 UID for the execution context (GPU node).
    @return UID for the Work Context to be used for render commands. */
TgEXTN TgKN_GPU_CXT_WORK_ID
tgKN_GPU_EXT__Execute__Frame_Start(
    TgKN_GPU_CXT_EXEC_ID_C ARG0 );

/** @brief Acquire the next available present buffer from the swap chain.
    @param [in] ARG0 UID for the Swap Context (swapchain).
    @param [in] ARG1 UID for the per Frame Work Context returned by tgKN_GPU_EXT__Execute__Frame_Start.
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_EXT__SwapChain__Acquire_Present_Buffer(
    TgKN_GPU_CXT_SWAP_ID_C ARG0, TgKN_GPU_CXT_WORK_ID_C ARG1 );

/** @brief Query the render target description for the current back buffer of the swap chain.
    @param [out] OUT0 Pointer to the render target description structure to be filled in.
    @param [in] ARG1 UID for the Swap Context (swapchain).
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_EXT__SwapChain__Query_Render_Target_DESC(
    STg2_KN_GPU_Render_Target_DESC_PC OUT0, TgKN_GPU_CXT_SWAP_ID_C ARG1 );

/** @brief Query the output description for the swap chain.
    @param [out] OUT0 Pointer to the output description structure to be filled in.
    @param [in] ARG1 UID for the Swap Context (swapchain).
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_EXT__SwapChain__Query_Output_DESC(
    STg2_KN_GPU_Output_DESC_PC OUT0, TgKN_GPU_CXT_SWAP_ID_C ARG1 );


/* ---- GPU - Contexts - Extension - WORK ---------------------------------------------------------------------------------------------------------------------------------------- */
/* Context Execute -> Context Command (Returned from a Frame Start) -> Command (Returned from an Acquire, one per thread/job) */

/** @brief Close the Work Context.
    @param [in] ARG0 UID for the per Frame Work Context returned by tgKN_GPU_EXT__Execute__Frame_Start.. */
TgEXTN TgVOID
tgKN_GPU_EXT__WORK__Frame_End(
    TgKN_GPU_CXT_WORK_ID_C ARG0 );

/** @brief Function returns the set of resources necessary for issuing commands to a command list.
    @details Currently using a DX12 style interface (will review when implementing Metal/Vulkan).
    @param [in] ARG0 UID for the per Frame Work Context returned by tgKN_GPU_EXT__Execute__Frame_Start.
    @param [in] ARG1 Enumeration selecting the command list type to return.
    @param [in] ARG2 Optional debug name to assign to the command list and associated resources.
    @return Pointer to a data structure holding a pointer to a command list of the given type, and associated resources necessary for its use. */
TgEXTN STg2_KN_GPU_CMD_P
tgKN_GPU_EXT__WORK__Acquire_Command(
    TgKN_GPU_CXT_WORK_ID_C ARG0, ETgKN_GPU_EXT_COMMAND_C ARG1, TgCHAR_U8_CPC ARG2 );

/** @brief Finalize this frame, and rotate the swap chain (present the current render buffer from the swap chain).
    @param [in] ARG0 UID for the per Frame Work Context returned by tgKN_GPU_EXT__Execute__Frame_Start. 
    @param [in] ARG1 UID for the Swap Context (swapchain) to be presented (associated with the same execution context as that of the Work Context).
    @param [in] ARG2 Command Queue to wait on using the semaphore timeline value that proceeds.
    @param [in] ARG3 Timeline semaphore value to wait on before executing the present (render complete).
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_EXT__WORK__Present(
    TgKN_GPU_CXT_WORK_ID_C ARG0, TgKN_GPU_CXT_SWAP_ID_C ARG1, ETgKN_GPU_EXT_COMMAND ARG2, TgUINT_E64 ARG3);

/** @brief Submit a GPU timestamp query.
    @param [out] OUT0 Pointer to the variable that will receive the timestamp index.
    @param [in] ARG1 UID for the per Frame Work Context returned by tgKN_GPU_EXT__Execute__Frame_Start.
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_EXT__WORK__Submit_GPU_Timestamp(
    TgRSIZE_PC TgANALYSIS_NO_NULL OUT0, TgKN_GPU_CXT_WORK_ID_C ARG1 );

/** @brief Query a GPU timestamp.
    @param [in] ARG0 UID for the Execution Context (GPU node).
    @param [in] ARG1 The index of the timestamp to query for the start of the range (as returned by tgKN_GPU_EXT__CMD__Submit_GPU_Timestamp).
    @param [in] ARG2 The index of the timestamp to query for the end of the range (as returned by tgKN_GPU_EXT__CMD__Submit_GPU_Timestamp).
    @return The GPU timestamp in milliseconds, or -1.0f if the timestamp is not available. */
TgEXTN TgFLOAT32
tgKN_GPU_EXT__WORK__Query_GPU_Timestamp(
    TgKN_GPU_CXT_WORK_ID_C ARG0, TgRSIZE ARG1, TgRSIZE ARG2 );


/* ---- GPU - Contexts - Extension - Command ------------------------------------------------------------------------------------------------------------------------------------- */

/** @brief Function used to close a command list acquired through (tgKN_GPU_EXT__WORK__Acquire_Command).
    @param [out] OUT0 Pointer to the current timeline semaphore value used when submitting the command buffer.
    @param [in] ARG1 Pointer to the command structure returned by tgKN_GPU_EXT__WORK__Acquire_Command.
    @param [in] ARG2 Command Queue to wait on using the semaphore timeline value that proceeds.
    @param [in] ARG3 Timeline semaphore value to wait on before executing the command buffer. */
TgEXTN TgVOID
tgKN_GPU_EXT__CMD__Command_Buffer_Close_And_Submit_With_Wait(
    TgUINT_E64_P OUT0, STg2_KN_GPU_CMD_PC TgANALYSIS_NO_NULL ARG1, ETgKN_GPU_EXT_COMMAND_C ARG2, TgUINT_E64_C ARG3 );

/** @brief Begin a render pass.
    @param [in] ARG0 Pointer to the command structure returned by tgKN_GPU_EXT__WORK__Acquire_Command.
    @param [in] ARG1 UID for the render target, or invalid value if the swap chain back buffer is to be used.
    @param [in] ARG2 UID for the swap context. Used to expose the display/scanout device characteristics.
    @param [in] ARG3 Pointer to the clear target description to be used when beginning rendering (non-persistent).
    @param [in] ARG4 Pointer to the camera data to be used in the descriptor set (non-persistent).
    @param [in] ARG5 Pointer to the debug render description to be used in the descriptor set (non-persistent).
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_EXT__CMD__Begin_Rendering(
    STg2_KN_GPU_CMD_PC TgANALYSIS_NO_NULL ARG0, TgKN_GPU_RENDER_TARGET_ID_C ARG1, TgKN_GPU_CXT_SWAP_ID_C ARG2, STg2_KN_GPU_Clear_Target_CPC TgANALYSIS_OK_NULL ARG3, 
    STg2_KN_GPU_Camera_CPC TgANALYSIS_OK_NULL ARG4, STg2_KN_GPU_DBG_Render_DESC_CPC TgANALYSIS_OK_NULL ARG5 );

/** @brief End a render pass.
    @param [in] ARG0 Pointer to the command structure returned by tgKN_GPU_EXT__WORK__Acquire_Command. */
TgEXTN TgVOID
tgKN_GPU_EXT__CMD__End_Rendering(
    STg2_KN_GPU_CMD_PC TgANALYSIS_NO_NULL ARG0 );

/** @brief Insert the set of commands required to clear the render target on the given command list when in a render pass.
    @param [in] ARG0 UID for the Swap Context (swapchain).
    @param [in] ARG1 ARG0 Pointer to the command structure returned by tgKN_GPU_EXT__WORK__Acquire_Command.
    @param [in] ARG2 Pointer to the clear target description to be used when clearing the render target (non-persistent).
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_EXT__CMD__Clear_Targets(
    STg2_KN_GPU_CMD_PC TgANALYSIS_NO_NULL ARG0, TgKN_GPU_CXT_SWAP_ID_C ARG1, STg2_KN_GPU_Clear_Target_CPC TgANALYSIS_NO_NULL ARG2 );

/** @brief Create a debug descriptor set
    @param [in] ARG0 Pointer to the command structure returned by tgKN_GPU_EXT__WORK__Acquire_Command.
    @param [in] ARG1 Pointer to the camera data to be used in the descriptor set (non-persistent).
    @param [in] ARG2 Pointer to the debug render description to be used in the descriptor set (non-persistent).
    @param [in] ARG3 Pointer to the output description to be used in the descriptor set (non-persistent).
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_EXT__CMD__Update_Render_DESC_Descriptor_Set(
    STg2_KN_GPU_CMD_PC TgANALYSIS_NO_NULL ARG0, STg2_KN_GPU_Camera_CPC TgANALYSIS_OK_NULL ARG1, STg2_KN_GPU_DBG_Render_DESC_CPC TgANALYSIS_OK_NULL ARG2,
    STg2_KN_GPU_Output_DESC_CPC TgANALYSIS_OK_NULL ARG3 );

/** @brief Insert the set of commands required to set the viewport and scissors region on the given command list.
    @param [in] ARG0 UID for the Swap Context (swapchain).
    @param [in] ARG1 ARG0 Pointer to the command structure returned by tgKN_GPU_EXT__WORK__Acquire_Command.
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_EXT__CMD__Set_Viewport_and_Scissor(
    STg2_KN_GPU_CMD_PC TgANALYSIS_NO_NULL ARG0, TgKN_GPU_CXT_SWAP_ID_C ARG1);

/** @brief Render a render target to the present surface with colour correction.
    @details Barriers are placed on the Graphics Queue for both the source and destination render targets. Then this command buffer is submitted to the Graphics Queue with
               a wait specified by ARG1 (queue) and ARG2 (timeline value).
             Synchronization is done between the compute and graphics queues using timeline semaphores.
             The compute shader reads tone mapping parameters (exposure, gamma, tone map type) from the OutputDESC in Set 0 of the descriptor set.
             Image view handles are passed via push constants to avoid descriptor set updates.
    @param [in] ARG0 Pointer to the command context returned by tgKN_GPU_EXT__WORK__Acquire_Command, assumed to be on the Graphics Queue.
    @param [in] ARG1 Enumeration selecting the semaphore timeline queue to use to wait.
    @param [in] ARG2 Semamphore Timeline value used to wait.
    @param [in] ARG3 Work context ID.
    @param [in] ARG4 Swap context ID.
    @param [in] ARG5 Render target ID to be presented.
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_EXT__CMD__Render_Target_To_Present_With_Colour_Correction(
    STg2_KN_GPU_CMD_P ARG0, ETgKN_GPU_EXT_COMMAND_C ARG1, TgUINT_E64 ARG2, TgKN_GPU_CXT_WORK_ID_C ARG3, TgKN_GPU_CXT_SWAP_ID_C ARG4, TgKN_GPU_RENDER_TARGET_ID_C ARG5 );


/* ---- GPU - Contexts - Extension - Debug --------------------------------------------------------------------------------------------------------------------------------------- */
#if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)

/** @brief Render text (using the default DOS fonts), in view space. This will keep the text within the limits of the provided rectangle.
    @param [in] ARG0 Pointer to the command structure returned by tgKN_GPU_EXT__WORK__Acquire_Command.
    @param [in] ARG1 Pointer to the constant buffer contents to use in the call (non-persistent).
    @param [in] ARG2 Pointer to an array of text offsets (UV0, UV1, UV Width, UV Height) to be used in the render call.
    @param [in] ARG3 Integer count of the number of text offsets. */
TgEXTN TgVOID
tgKN_GPU_EXT__CMD__Render_Debug_Text(
    STg2_KN_GPU_CMD_PC TgANALYSIS_NO_NULL ARG0, STg2_KN_GPU_DBG_Text_CPC TgANALYSIS_NO_NULL ARG1, TgVEC_S_F32_04_1_CPC TgANALYSIS_NO_NULL ARG2, TgRSIZE ARG3 );

/** @brief Render a quad, in view space.
    @param [in] ARG0 Pointer to the command structure returned by tgKN_GPU_EXT__WORK__Acquire_Command.
    @param [in] ARG1 Pointer to the constant buffer contents to use in the call (non-persistent). */
TgEXTN TgVOID
tgKN_GPU_EXT__CMD__Render_Debug_Quad(
    STg2_KN_GPU_CMD_PC TgANALYSIS_NO_NULL ARG0, STg2_KN_GPU_DBG_Quad_CPC TgANALYSIS_NO_NULL ARG1 );

/** @brief Render a gradient.
    @param [in] ARG0 Pointer to the command structure returned by tgKN_GPU_EXT__WORK__Acquire_Command. */
TgEXTN TgVOID
tgKN_GPU_EXT__CMD__Render_Debug_Gradient(
    STg2_KN_GPU_CMD_PC TgANALYSIS_NO_NULL ARG0 );

/** @brief Render debug geometry.
    @param [in] ARG0 Pointer to the command structure returned by tgKN_GPU_EXT__WORK__Acquire_Command.
    @param [in] ARG1 Enumeration selecting the primitive type to render.
    @param [in] ARG2 Pointer to the constant buffer contents to use in the call (non-persistent).
    @param [in] ARG3 Boolean flag to if the lit (false) or unlit (true) pipeline should be used. */
TgEXTN TgVOID
tgKN_GPU_EXT__CMD__Render_Debug_Geom(
    STg2_KN_GPU_CMD_PC TgANALYSIS_NO_NULL ARG0, ETgKN_GPU_DEBUG_PM ARG1, STg2_KN_GPU_DBG_Geom_CPC TgANALYSIS_NO_NULL ARG2, TgBOOL_C ARG3 );

/** @brief Render debug geometry.
    @param [in] ARG0 Pointer to the command structure returned by tgKN_GPU_EXT__WORK__Acquire_Command.
    @param [in] ARG1 Enumeration selecting the primitive type to render.
    @param [in] ARG2 Integer count of the number of instances to render. 
    @param [in] ARG3 Pointer to an array of instance data (model transform and colour) to be used in the render call.
    @param [in] ARG4 Boolean flag to if the lit (false) or unlit (true) pipeline should be used. */
TgEXTN TgVOID
tgKN_GPU_EXT__CMD__Render_Debug_Geom_Instance(
    STg2_KN_GPU_CMD_PC TgANALYSIS_NO_NULL ARG0, ETgKN_GPU_DEBUG_PM ARG1, TgRSIZE_C ARG2, STg2_KN_GPU_DBG_Geom_CPC TgANALYSIS_NO_NULL ARG3, TgBOOL_C ARG4 );

/** @brief Render a debug line in 3D. This will buffer up the render calls until either a new render target is set (which will flush the buffer), or it is filled.
    @param [in] ARG0 Pointer to the command structure returned by tgKN_GPU_EXT__WORK__Acquire_Command. */
TgEXTN TgVOID
tgKN_GPU_EXT__CMD__Render_Debug_Line(
    STg2_KN_GPU_CMD_PC TgANALYSIS_NO_NULL ARG0 );

/*# defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
#endif


/* ---- GPU - Debug Functions ---------------------------------------------------------------------------------------------------------------------------------------------------- */

#if defined(TgS_DEBUG__RENDER)

TgEXTN TgVOID
tgKN_GPU_EXT__DBG__Begin_Event(
    STg2_KN_GPU_CMD_PC TgANALYSIS_NO_NULL ARG0, TgCHAR_U8_CPCU ARG1, TgRSIZE_C ARG2, TgFLOAT32_CPC ARG3 );

TgEXTN TgVOID
tgKN_GPU_EXT__DBG__End_Event(
    STg2_KN_GPU_CMD_PC TgANALYSIS_NO_NULL ARG0 );

TgEXTN TgVOID
tgKN_GPU_EXT__DBG__Insert_Marker(
    STg2_KN_GPU_CMD_PC TgANALYSIS_NO_NULL ARG0, TgCHAR_U8_CPCU ARG1, TgRSIZE_C ARG2, TgFLOAT32_CPC ARG3 );

    /*# TgS_DEBUG__RENDER */
#endif

/*# !defined(TGS_KERNEL_GPU_EXT_H) && defined(TgBUILD_FEATURE__GRAPHICS) */
#endif
