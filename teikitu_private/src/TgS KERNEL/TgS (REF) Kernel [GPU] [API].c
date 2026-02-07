/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (REF) Kernel [GPU] [API].c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Kernel ===================================================================================================================================================================== */
#if !defined (ENABLE_RELOAD_GUARD)

TgCLANG_WARN_DISABLE_PUSH(unused-parameter)


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  TgS Kernel - [GPU].h                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- GPU - Contexts - Extension ----------------------------------------------------------------------------------------------------------------------------------------------- */

TgVOID tgKN_GPU_EXT__Execute__Cmd_Buffer_Flush( TgKN_GPU_CXT_EXEC_ID_C ARG0, ETgKN_GPU_EXT_COMMAND_C ARG1 )
{
}

TgVOID tgKN_GPU_EXT__Execute__Flush( TgKN_GPU_CXT_EXEC_ID_C ARG0 )
{
}

TgKN_GPU_RENDER_TARGET_ID tgKN_GPU_EXT__Execute__Create_Render_Target( TgKN_GPU_CXT_EXEC_ID_C ARG0, STg2_KN_GPU_Render_Target_DESC_CPC ARG1 )
{
    return (KTgKN_GPU_RENDER_TARGET_ID__INVALID);
}
    
TgKN_GPU_CXT_WORK_ID tgKN_GPU_EXT__Execute__Frame_Start( TgKN_GPU_CXT_EXEC_ID_C ARG0 )
{
    return (KTgKN_GPU_CXT_WORK_ID__INVALID);
}

TgRESULT tgKN_GPU_EXT__SwapChain__Acquire_Present_Buffer( TgKN_GPU_CXT_SWAP_ID_C ARG0, TgKN_GPU_CXT_WORK_ID_C ARG1 )
{
    return (KTgS_OK);
}

TgRESULT tgKN_GPU_EXT__SwapChain__Query_Render_Target_DESC( STg2_KN_GPU_Render_Target_DESC_PC OUT0, TgKN_GPU_CXT_SWAP_ID_C ARG1 )
{
    return (KTgS_OK);
}

TgRESULT tgKN_GPU_EXT__SwapChain__Query_Output_DESC( STg2_KN_GPU_Output_DESC_PC OUT0, TgKN_GPU_CXT_SWAP_ID_C ARG1 )
{
    return (KTgS_OK);
}

TgVOID tgKN_GPU_EXT__WORK__Frame_End( TgKN_GPU_CXT_WORK_ID_C ARG0 )
{
}

STg2_KN_GPU_CMD_P tgKN_GPU_EXT__WORK__Acquire_Command( TgKN_GPU_CXT_WORK_ID_C ARG0, ETgKN_GPU_EXT_COMMAND_C ARG1, TgCHAR_U8_CPC ARG2 )
{
    return (nullptr);
}

TgRESULT tgKN_GPU_EXT__WORK__Present( TgKN_GPU_CXT_WORK_ID_C ARG0, TgKN_GPU_CXT_SWAP_ID_C ARG1, ETgKN_GPU_EXT_COMMAND ARG2, TgUINT_E64 ARG3 )
{
    return (KTgS_OK);
}

TgRESULT tgKN_GPU_EXT__WORK__Submit_GPU_Timestamp( TgRSIZE_PC TgANALYSIS_NO_NULL OUT0, TgKN_GPU_CXT_WORK_ID_C ARG1 )
{
    return (KTgS_OK);
}

TgFLOAT32 tgKN_GPU_EXT__WORK__Query_GPU_Timestamp( TgKN_GPU_CXT_WORK_ID_C ARG0, TgRSIZE ARG1, TgRSIZE ARG2 )
{
    return (-1.0f);
}

TgVOID tgKN_GPU_EXT__CMD__Command_Buffer_Close_And_Submit_With_Wait( TgUINT_E64_P OUT0, STg2_KN_GPU_CMD_PC TgANALYSIS_NO_NULL ARG1, ETgKN_GPU_EXT_COMMAND_C ARG2, TgUINT_E64_C ARG3 )
{
}

TgRESULT tgKN_GPU_EXT__CMD__Begin_Rendering( STg2_KN_GPU_CMD_PC TgANALYSIS_NO_NULL ARG0, TgKN_GPU_RENDER_TARGET_ID_C ARG1, TgKN_GPU_CXT_SWAP_ID_C ARG2, STg2_KN_GPU_Clear_Target_CPC TgANALYSIS_OK_NULL ARG3, STg2_KN_GPU_Camera_CPC TgANALYSIS_OK_NULL ARG4, STg2_KN_GPU_DBG_Render_DESC_CPC TgANALYSIS_OK_NULL ARG5 )
{
    return (KTgS_OK);
}

TgVOID tgKN_GPU_EXT__CMD__End_Rendering( STg2_KN_GPU_CMD_PC TgANALYSIS_NO_NULL ARG0 )
{
}

TgRESULT tgKN_GPU_EXT__CMD__Clear_Targets( STg2_KN_GPU_CMD_PC TgANALYSIS_NO_NULL ARG0, TgKN_GPU_CXT_SWAP_ID_C ARG1, STg2_KN_GPU_Clear_Target_CPC TgANALYSIS_NO_NULL ARG2 )
{
    return (KTgS_OK);
}

TgRESULT tgKN_GPU_EXT__CMD__Update_Render_DESC_Descriptor_Set( STg2_KN_GPU_CMD_PC TgANALYSIS_NO_NULL ARG0, STg2_KN_GPU_Camera_CPC TgANALYSIS_OK_NULL ARG1, STg2_KN_GPU_DBG_Render_DESC_CPC TgANALYSIS_OK_NULL ARG2, STg2_KN_GPU_Output_DESC_CPC TgANALYSIS_OK_NULL ARG3 )
{
    return (KTgS_OK);
}

TgRESULT tgKN_GPU_EXT__CMD__Set_Viewport_and_Scissor( STg2_KN_GPU_CMD_PC ARG0, TgKN_GPU_CXT_SWAP_ID_C ARG1 )
{
    return (KTgS_OK);
}

TgRESULT tgKN_GPU_EXT__CMD__Render_Target_To_Present_With_Colour_Correction( STg2_KN_GPU_CMD_P ARG0, ETgKN_GPU_EXT_COMMAND_C ARG1, TgUINT_E64 ARG2, TgKN_GPU_CXT_WORK_ID_C ARG3, TgKN_GPU_CXT_SWAP_ID_C ARG4, TgKN_GPU_RENDER_TARGET_ID_C ARG5 )
{
    return (KTgS_OK);
}

#if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)

TgVOID tgKN_GPU_EXT__CMD__Render_Debug_Text( STg2_KN_GPU_CMD_PC ARG0, STg2_KN_GPU_DBG_Text_CPC ARG1, TgVEC_S_F32_04_1_CPC ARG2, TgRSIZE ARG3 )
{
}

TgVOID tgKN_GPU_EXT__CMD__Render_Debug_Quad( STg2_KN_GPU_CMD_PC ARG0, STg2_KN_GPU_DBG_Quad_CPC ARG2 )
{
}

TgVOID tgKN_GPU_EXT__CMD__Render_Debug_Gradient( STg2_KN_GPU_CMD_PC TgANALYSIS_NO_NULL ARG0 )
{
}

TgVOID tgKN_GPU_EXT__CMD__Render_Debug_Geom( STg2_KN_GPU_CMD_PC ARG0, ETgKN_GPU_DEBUG_PM ARG1, STg2_KN_GPU_DBG_Geom_CPC ARG2, TgBOOL_C bUnLit )
{
}

TgVOID tgKN_GPU_EXT__CMD__Render_Debug_Geom_Instance( STg2_KN_GPU_CMD_PC ARG0, ETgKN_GPU_DEBUG_PM_C ARG1, TgRSIZE_C ARG2, STg2_KN_GPU_DBG_Geom_CPC ARG3, TgBOOL_C bUnLit )
{
}

TgVOID tgKN_GPU_EXT__CMD__Render_Debug_Line( STg2_KN_GPU_CMD_PC ARG0 )
{
}

/*# defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
#endif

#if defined(TgS_DEBUG__RENDER)

TgVOID tgKN_GPU_EXT__DBG__Begin_Event( STg2_KN_GPU_CMD_PC TgANALYSIS_NO_NULL ARG0, TgCHAR_U8_CPCU ARG1, TgRSIZE_C ARG2, TgFLOAT32_CPC ARG3 )
{
}

TgVOID tgKN_GPU_EXT__DBG__End_Event( STg2_KN_GPU_CMD_PC TgANALYSIS_NO_NULL ARG0 )
{
}

TgVOID tgKN_GPU_EXT__DBG__Insert_Marker( STg2_KN_GPU_CMD_PC TgANALYSIS_NO_NULL ARG0, TgCHAR_U8_CPCU ARG1, TgRSIZE_C ARG2, TgFLOAT32_CPC ARG3 )
{
}

/*# TgS_DEBUG__RENDER */
#endif


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  TgS Kernel - Internal [GPU].h                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  TgS Kernel - Internal [GPU] [API].h                                                                                                                                            */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgRESULT tgKN_GPU_EXT_Module_Init( TgVOID )
{
    return (KTgS_OK);
}

TgRESULT tgKN_GPU_EXT_Module_Boot( TgVOID )
{
    return (KTgS_OK);
}

TgVOID tgKN_GPU_EXT_Module_Stop( TgVOID )
{
}

TgVOID tgKN_GPU_EXT_Module_Free( TgVOID )
{
}

TgRESULT tgKN_GPU_EXT_Module_Update( TgFLOAT32_C ARG0 )
{
    return (KTgS_OK);
}

TgRSIZE tgKN_GPU_EXT_Query_Fixed_Memory( TgVOID )
{
    return (0);
}


/* ---- GPU - Enumeration -------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgRESULT tgKN_GPU_EXT_Enumerate( TgVOID )
{
    return (KTgS_OK);
}

TgVOID tgKN_GPU_EXT_Physical_Device_Free( TgRSIZE_C ARG0 )
{
}

TgVOID tgKN_GPU_EXT_Display_Output_Free( TgRSIZE_C ARG0 )
{
}


/* ---- GPU - Contexts ----------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgRESULT tgKN_GPU_EXT__Host__Init( TgVOID )
{
    return (KTgS_OK);
}

TgVOID tgKN_GPU_EXT__Host__Free( TgVOID )
{
}

TgRESULT tgKN_GPU_EXT__Device__Init( TgKN_GPU_CXT_DEVC_ID_C ARG0 )
{
    return (KTgS_OK);
}

TgVOID tgKN_GPU_EXT__Device__Free( TgKN_GPU_CXT_DEVC_ID_C ARG0 )
{
}

TgRESULT tgKN_GPU_EXT__Execute__Init( TgKN_GPU_CXT_EXEC_ID_C ARG0 )
{
    return (KTgS_OK);
}

TgRESULT tgKN_GPU_EXT__Execute__Init__Create_Default_Resources__Pass_0( STg2_KN_GPU_CMD_PC ARG0 )
{
    return (KTgS_OK);
}

TgRESULT tgKN_GPU_EXT__Execute__Init__Create_Default_Resources__Pass_1( STg2_KN_GPU_CMD_PC ARG0 )
{
    return (KTgS_OK);
}

TgVOID tgKN_GPU_EXT__Execute__Free( TgKN_GPU_CXT_EXEC_ID_C ARG0 )
{
}

TgRESULT tgKN_GPU_EXT__SwapChain__Init( TgKN_GPU_CXT_SWAP_ID_C ARG0, TgBOOL_C ARG1, TgBOOL_C ARG2 )
{
    return (KTgS_OK);
}

TgVOID tgKN_GPU_EXT__SwapChain__Free( TgKN_GPU_CXT_SWAP_ID_C ARG0 )
{
}


/* ---- GPU - Resource ----------------------------------------------------------------------------------------------------------------------------------------------------------- */

#define __PARENT_FILE__ "TgS (REF) Kernel [GPU] [API].c"
#define ENABLE_RELOAD_GUARD
#include "TgS KERNEL/TgS Kernel [GPU] - Resource [INC].h"
#undef ENABLE_RELOAD_GUARD
#undef __PARENT_FILE__


/* ---- GPU - Debug -------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)

TgRESULT tgKN_GPU_EXT__Host__Init_Debug( TgVOID )
{
    return (KTgS_OK);
}

TgVOID tgKN_GPU_EXT__Host__Free_Debug( TgVOID )
{
}

TgRESULT tgKN_GPU_EXT__Execute__Init_Debug( TgKN_GPU_CXT_EXEC_ID_C ARG0 )
{
    return (KTgS_OK);
}

TgRESULT tgKN_GPU_EXT__Execute__Init_Debug__Create_Resources( STg2_KN_GPU_CMD_PC ARG0 )
{
    return (KTgS_OK);
}

TgVOID tgKN_GPU_EXT__Execute__Free_Debug__Destroy_Resources( STg2_KN_GPU_CMD_PC ARG0 )
{
}

TgVOID tgKN_GPU_EXT__Execute__Free_Debug( TgKN_GPU_CXT_EXEC_ID_C ARG0 )
{
}

TgRESULT tgKN_GPU_EXT__Swap__Init_Debug( TgKN_GPU_CXT_SWAP_ID_C ARG0 )
{
    return (KTgS_OK);
}

TgVOID tgKN_GPU_EXT__Swap__Free_Debug( TgKN_GPU_CXT_SWAP_ID_C ARG0 )
{
}

TgVOID tgKN_GPU_EXT__CMD__Register_Debug_Geometry( STg2_KN_GPU_CMD_PC ARG0, ETgKN_GPU_DEBUG_PM ARG1, TgKN_GPU_DBG_PM_Generate_CPCU ARG2 )
{
}

TgRESULT tgKN_GPU_EXT__CMD__Command_Debug( STg2_KN_GPU_CMD_DBG_PP OUT0, STg2_KN_GPU_CMD_PC ARG1 )
{
    *OUT0 = nullptr;
    return (KTgE_FAIL);
}

/*# defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
#endif

TgCLANG_WARN_DISABLE_POP(unused-parameter)

/*# defined (ENABLE_RELOAD_GUARD) */
#else

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  TgS Kernel - Internal [GPU].h                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- GPU - Resource ----------------------------------------------------------------------------------------------------------------------------------------------------------- */

#if defined(MACRO_BUILD_TEXTURE)
TgRESULT T(tgKN_GPU_EXT_,__Execute_Load)( TgKN_FILE_ID_C ARG0, TgRSIZE_C ARG1, T(STg2_KN_GPU_,_DESC_CPC) ARG2, TgUINT_E64_C ARG3, T(TgKN_GPU_,_ID_C) ARG4 )
{
    return (KTgS_OK);
}

TgVOID T(tgKN_GPU_EXT_,__Execute_Free)( T(TgKN_GPU_,_ID_C) ARG0 )
{
}

/*# defined(MACRO_BUILD_TEXTURE) */
#endif

#if defined(MACRO_BUILD_TEXTURE)
TgRESULT T(tgKN_GPU_EXT__CMD__,_Inst__Init)( STg2_KN_GPU_CMD_PC ARG0, T(TgKN_GPU_,_INST_ID_C) ARG1, TgCHAR_U8_CPCU ARG2 )
{
    return (KTgS_OK);
}

TgVOID T(tgKN_GPU_EXT__CMD__,_Inst__Free)( STg2_KN_GPU_CMD_PC ARG0, T(TgKN_GPU_,_INST_ID_C) ARG1 )
{
}

TgRSIZE T(tgKN_GPU_EXT__CMD__Register_Default_,_Inst)( STg2_KN_GPU_CMD_PC ARG0, T(TgKN_GPU_,_INST_ID_C) ARG1, ETgKN_GPU_DEFAULT_SAMPLER_C ARG2 )
{
    return (0);
}

/*# defined(MACRO_BUILD_TEXTURE) */
#endif

/* ---- Resource - GPU - Texture - API ------------------------------------------------------------------------------------------------------------------------------------------- */

#if defined(MACRO_BUILD_TEXTURE)
TgVOID T(tgKN_GPU_EXT__CMD__,__Fast_Lock)( STg2_KN_GPU_TX_LOCK_PCU OUT0, STg2_KN_GPU_CMD_PC ARG1, T(TgKN_GPU_,_INST_ID_C) ARG2 )
{
}

TgVOID T(tgKN_GPU_EXT__CMD__,__Lock)( STg2_KN_GPU_TX_LOCK_PCU OUT0, STg2_KN_GPU_CMD_PC ARG1, T(TgKN_GPU_,_INST_ID_C) ARG2 )
{
}

TgVOID T(tgKN_GPU_EXT__CMD__,__Fast_Unlock)( STg2_KN_GPU_CMD_PC ARG0, STg2_KN_GPU_TX_LOCK_PCU ARG1, T(TgKN_GPU_,_INST_ID_C) ARG2 )
{
}

TgVOID T(tgKN_GPU_EXT__CMD__,__Unlock)( STg2_KN_GPU_CMD_PC ARG0, STg2_KN_GPU_TX_LOCK_PCU ARG1, T(TgKN_GPU_,_INST_ID_C) ARG2 )
{
}

/*# defined(MACRO_BUILD_TEXTURE) */
#endif


/* =============================================================================================================================================================================== */

/*# defined (ENABLE_RELOAD_GUARD) */
#endif
