/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Kernel [GPU] [EXT].h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.20 | »GUID« DE461472-5528-4A5B-A7F4-09CCAD73387B */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
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
tgKN_GPU_EXT__Execute__Cmd_List_Flush(
    TgKN_GPU_CXT_EXEC_ID_C ARG0, ETgKN_GPU_EXT_COMMAND_C ARG1 );


/** @brief Insert a fence into every command queue, and wait for the GPU to pass them.
    @param [in] ARG0 UID for the Execution Context (GPU node). */
TgEXTN TgVOID
tgKN_GPU_EXT__Execute__Flush(
    TgKN_GPU_CXT_EXEC_ID_C ARG0 );

/** @brief Return a UID for a Work Context, which is the data structure used for issuing render commands.
    @param [in] ARG0 UID for the execution context (GPU node).
    @return UID for the Work Context to be used for render commands. */
TgEXTN TgKN_GPU_CXT_WORK_ID
tgKN_GPU_EXT__Execute__Frame_Start(
    TgKN_GPU_CXT_EXEC_ID_C ARG0 );

/** @brief Close the Work Context.
    @param [in] ARG0 UID for the Work Context. */
TgEXTN TgVOID
tgKN_GPU_EXT__Execute__Frame_End(
    TgKN_GPU_CXT_WORK_ID_C ARG0 );

/** @brief Function returns the set of resources necessary for issuing commands to a command list.
    @detail Currently using a DX12 style interface (will review when implementing Metal/Vulkan). 
    @param [in] ARG0 UID for the Work Context. 
    @param [in] ARG0 Enumeration selecting the command list type to return. 
    @return Pointer to a data structure holding a pointer to a command list of the given type, and associated resources necessary for its use. */
TgEXTN UTg2_KN_GPU_CMD
tgKN_GPU_EXT__Execute__Command_List_Acquire(
    TgKN_GPU_CXT_WORK_ID_C ARG0, ETgKN_GPU_EXT_COMMAND_C ARG1 );

/** @brief Function used to close a command list acquired through (tgKN_GPU_EXT__Execute__Command_List_Acquire).
    @param [in] ARG0 Union of a pointer to the command list data structure returned by tgKN_GPU_EXT__Execute__Command_List_Acquire. */
TgEXTN TgVOID
tgKN_GPU_EXT__CMD__Command_List_Close(
    UTg2_KN_GPU_CMD_C ARG0 );

/** @brief Function to set the state of the command list. In DX12 this is done by setting using a Pipeline State Object.
    @param [in] ARG0 Union of a pointer to the command list data structure returned by tgKN_GPU_EXT__Execute__Command_List_Acquire.
    @param [in] ARG1 Enumeration selecting the command state.
    @param [in] ARG2 Enumeration indicating the format of the render buffer.
    @param [in] ARG3 Enumeration indicating the format of the depth-stencil buffer. */
TgEXTN TgRESULT
tgKN_GPU_EXT__CMD__Set_State_From_Default(
    UTg2_KN_GPU_CMD_C ARG0, ETgKN_GPU_DEFAULT_PSO_C ARG1, ETgKN_GPU_EXT_FORMAT_C ARG2, ETgKN_GPU_EXT_FORMAT_C ARG3 );

#if TgCOMPILE__RENDER_DEBUG_OUTPUT

/** @brief Render text (using the default DOS fonts), in view space. This will keep the text within the limits of the provided rectangle.
    @param [in] ARG0 Union of a pointer to the command list data structure returned by tgKN_GPU_EXT__Execute__Command_List_Acquire.
    @param [in] ARG1 Integer count of the number of glyphs to render (number of quad instances).
    @param [in] ARG2 Pointer to the constant buffer contents to use in the call (non-persistent). */
TgEXTN TgVOID
tgKN_GPU_EXT__CMD__Render_Debug_Text(
    UTg2_KN_GPU_CMD_C ARG0, TgRSIZE ARG1, STg2_KN_GPU_HLSL_CB_Debug_Text_CPC NONULL ARG2 );

/** @brief Render a quad, in view space.
    @param [in] ARG0 Union of a pointer to the command list data structure returned by tgKN_GPU_EXT__Execute__Command_List_Acquire.
    @param [in] ARG1 Pointer to the constant buffer contents to use in the call (non-persistent). */
TgEXTN TgVOID
tgKN_GPU_EXT__CMD__Render_Debug_UI(
    UTg2_KN_GPU_CMD_C ARG0, STg2_KN_GPU_HLSL_CB_Debug_UI_CPC NONULL ARG1 );

/** @brief Render debug geometry.
    @param [in] ARG0 Union of a pointer to the command list data structure returned by tgKN_GPU_EXT__Execute__Command_List_Acquire.
    @param [in] ARG1 Pointer to the constant buffer contents to use in the call (non-persistent). */
TgEXTN TgVOID
tgKN_GPU_EXT__CMD__Render_Debug_Geom(
    UTg2_KN_GPU_CMD_C ARG0, ETgKN_GPU_DEBUG_PM ARG1, STg2_KN_GPU_HLSL_CB_Debug_Model_CPC NONULL ARG2 );

/** @brief Render debug geometry.
    @param [in] ARG0 Union of a pointer to the command list data structure returned by tgKN_GPU_EXT__Execute__Command_List_Acquire.
    @param [in] ARG1 Pointer to the constant buffer contents to use in the call (non-persistent). */
TgEXTN TgVOID
tgKN_GPU_EXT__CMD__Render_Debug_Geom_Instance(
    UTg2_KN_GPU_CMD_C ARG0, ETgKN_GPU_DEBUG_PM ARG1, TgRSIZE_C ARG2, STg2_KN_GPU_HLSL_CB_Debug_Model_Instance_CPC NONULL ARG3 );

/** @brief Render a debug line in 3D. This will buffer up the render calls until either a new render target is set (which will flush the buffer), or it is filled.
    @param [in] ARG0 Union of a pointer to the command list data structure returned by tgKN_GPU_EXT__Execute__Command_List_Acquire.
    @param [in] ARG1 Pointer to an array of line vertices (position, colour).
    @param [in] ARG2 Integer count of the number of vertices (line list). */
TgEXTN TgVOID
tgKN_GPU_EXT__CMD__Render_Debug_Line(
    UTg2_KN_GPU_CMD_C ARG0, STg2_KN_GPU_Vertex_Geom_01_CPCU ARG1, TgRSIZE_C ARG2, STg2_KN_GPU_HLSL_CB_Debug_Line_CPC NONULL ARG3 );

/*# TgCOMPILE__RENDER_DEBUG_OUTPUT */
#endif

/** @brief Finalize this frame, and rotate the swap chain (present the current render buffer from the swap chain).
    @param [in] ARG0 UID for the most recent active Work Context.
    @param [in] ARG1 UID for the Swap Context (swapchain) to be presented (associated with the same execution context as that of the Work Context).
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_EXT__SwapChain__Present(
    TgKN_GPU_CXT_WORK_ID_C ARG0, TgKN_GPU_CXT_SWAP_ID_C ARG1 );

/** @brief Insert the set of commands required to set the viewport and scissors region on the given command list.
    @param [in] ARG0 UID for the Swap Context (swapchain).
    @param [in] ARG1 Union of a pointer to the command list data structure returned by tgKN_GPU_EXT__Execute__Command_List_Acquire.
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_EXT__SwapChain__Set_Viewport_and_Scissor(
    TgKN_GPU_CXT_SWAP_ID_C ARG0, UTg2_KN_GPU_CMD_C ARG1 );


/* ---- GPU - Resource - Extension ----------------------------------------------------------------------------------------------------------------------------------------------- */

/** @brief Initialize and upload a data buffer using the provided command list. The output parameter is a pointer to a pointer to the resulting API resource.
    @detail Usually used to upload a vertex buffer.
    @param [in,out] OUT0 Pointer to a pointer to an API resource.
    @param [in] ARG1 Union of a pointer to the command list data structure returned by tgKN_GPU_EXT__Execute__Command_List_Acquire.
    @param [in] ARG2 Pointer to the data to be uploaded.
    @param [in] ARG3 Size of the data to be uploaded.
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_EXT__Execute__Init_Data_Buffer_1(
    TgVOID_PP NONULL OUT0, UTg2_KN_GPU_CMD_C ARG1, TgVOID_CP NONULL ARG2, TgRSIZE_C ARG3 );

/** @brief Initialize and upload two data buffers using the provided command list. The output parameters are a pointer to a pointer to the resulting API resource.
    @detail Usually used to upload a vertex and index buffer.
    @param [in,out] OUT0 Pointer to a pointer to an API resource.
    @param [in,out] OUT1 Pointer to a pointer to an API resource.
    @param [in] ARG2 Union of a pointer to the command list data structure returned by tgKN_GPU_EXT__Execute__Command_List_Acquire.
    @param [in] ARG3 Pointer to the first data to be uploaded.
    @param [in] ARG4 Size of the first data to be uploaded.
    @param [in] ARG5 Pointer to second data to be uploaded.
    @param [in] ARG6 Size of second data to be uploaded.
    @return Result Code. */
TgEXTN TgRESULT
tgKN_GPU_EXT__Execute__Init_Data_Buffer_2(
    TgVOID_PP NONULL OUT0, TgVOID_PP NONULL OUT1, UTg2_KN_GPU_CMD_C ARG2, TgVOID_CP NONULL ARG3, TgRSIZE_C ARG4, TgVOID_CP NONULL ARG5, TgRSIZE_C ARG6 );


/*# !defined(TGS_KERNEL_GPU_EXT_H) && defined(TgBUILD_FEATURE__GRAPHICS) */
#endif
