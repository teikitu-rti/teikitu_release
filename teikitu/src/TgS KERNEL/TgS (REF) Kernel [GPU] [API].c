/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (REF) Kernel [GPU] [API].c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Kernel ===================================================================================================================================================================== */
#if !defined (ENABLE_RELOAD_GUARD)

CLANG_WARN_DISABLE_PUSH(unused-parameter)


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  TgS Kernel - [GPU].h                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- GPU - Contexts - Extension ----------------------------------------------------------------------------------------------------------------------------------------------- */

TgVOID tgKN_GPU_EXT__Execute__Cmd_List_Flush( TgKN_GPU_CXT_EXEC_ID_C ARG0, ETgKN_GPU_EXT_COMMAND_C ARG1 )
{
}

TgVOID tgKN_GPU_EXT__Execute__Flush( TgKN_GPU_CXT_EXEC_ID_C ARG0 )
{
}

TgKN_GPU_CXT_WORK_ID tgKN_GPU_EXT__Execute__Frame_Start( TgKN_GPU_CXT_EXEC_ID_C ARG0 )
{
    return (KTgKN_GPU_CXT_WORK_ID__INVALID);
}

TgVOID tgKN_GPU_EXT__Execute__Frame_End( TgKN_GPU_CXT_WORK_ID_C ARG0 )
{
}

UTg2_KN_GPU_CMD tgKN_GPU_EXT__Execute__Command_List_Acquire( TgKN_GPU_CXT_WORK_ID_C ARG0, ETgKN_GPU_EXT_COMMAND_C ARG1 )
{
    UTg2_KN_GPU_CMD uRet = { .ps = nullptr };
    return (uRet);
}

TgVOID tgKN_GPU_EXT__CMD__Command_List_Close( UTg2_KN_GPU_CMD_C ARG0 )
{
}

TgRESULT tgKN_GPU_EXT__CMD__Set_State_From_Default( UTg2_KN_GPU_CMD_C ARG0, ETgKN_GPU_DEFAULT_PSO_C ARG1, ETgKN_GPU_EXT_FORMAT_C ARG2, ETgKN_GPU_EXT_FORMAT_C ARG3 )
{
    return (KTgS_OK);
}

#if TgCOMPILE__RENDER_DEBUG_OUTPUT

TgVOID tgKN_GPU_EXT__CMD__Render_Debug_Text( UTg2_KN_GPU_CMD_C ARG0, TgRSIZE ARG1, STg2_KN_GPU_HLSL_CB_Debug_Text_CPC ARG2 )
{
}

TgVOID tgKN_GPU_EXT__CMD__Render_Debug_UI( UTg2_KN_GPU_CMD_C ARG0, STg2_KN_GPU_HLSL_CB_Debug_UI_CPC ARG2 )
{
}

TgVOID tgKN_GPU_EXT__CMD__Render_Debug_Geom( UTg2_KN_GPU_CMD_C ARG0, ETgPRIMITIVE_C ARG1, STg2_KN_GPU_HLSL_CB_Debug_Model_CPC ARG2 )
{
}

TgVOID tgKN_GPU_EXT__CMD__Render_Debug_Geom_Instance( UTg2_KN_GPU_CMD_C ARG0, ETgPRIMITIVE_C ARG1, TgRSIZE_C ARG2, STg2_KN_GPU_HLSL_CB_Debug_Model_Instance_CPC ARG3 )
{
}

TgVOID tgKN_GPU_EXT__CMD__Render_Debug_Line( UTg2_KN_GPU_CMD_C ARG0, STg2_KN_GPU_Vertex_Geom_01_CPCU ARG1, TgRSIZE_C ARG2, STg2_KN_GPU_HLSL_CB_Debug_Line_CPC NONULL ARG3 )
{
}

/*# TgCOMPILE__RENDER_DEBUG_OUTPUT */
#endif

TgRESULT tgKN_GPU_EXT__SwapChain__Present( TgKN_GPU_CXT_WORK_ID_C ARG0, TgKN_GPU_CXT_SWAP_ID_C ARG1 )
{
    return (KTgS_OK);
}

TgRESULT tgKN_GPU_EXT__SwapChain__Set_Viewport_and_Scissor( TgKN_GPU_CXT_SWAP_ID_C ARG0, UTg2_KN_GPU_CMD_C ARG1 )
{
    return (KTgS_OK);
}

TgRESULT tgKN_GPU_EXT__Execute__Init_Data_Buffer_1( TgVOID_PP NONULL OUT0, UTg2_KN_GPU_CMD_C ARG1, TgVOID_CP NONULL ARG2, TgRSIZE_C ARG3 )
{
    return (KTgS_OK);
}

TgRESULT tgKN_GPU_EXT__Execute__Init_Data_Buffer_2( TgVOID_PP NONULL OUT0, TgVOID_PP NONULL OUT1, UTg2_KN_GPU_CMD_C ARG2, TgVOID_CP NONULL ARG3, TgRSIZE_C ARG4, TgVOID_CP NONULL ARG5, TgRSIZE_C ARG6 )
{
    return (KTgS_OK);
}


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

TgUINT_F32 tgKN_GPU_EXT_Query_Mode_List( STg2_KN_GPU_Mode_P ARG0, TgUINT_F32_C ARG1, TgUINT_F32_C ARG2, TgUINT_F32_C ARG3, ETgKN_GPU_EXT_FORMAT_C ARG4 )
{
    return (0);
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

TgVOID tgKN_GPU_EXT__Execute__Free( TgKN_GPU_CXT_EXEC_ID_C ARG0 )
{
}

TgRESULT tgKN_GPU_EXT__SwapChain__Init( TgKN_GPU_CXT_SWAP_ID_C ARG0, TgBOOL_C ARG1 )
{
    return (KTgS_OK);
}

TgVOID tgKN_GPU_EXT__SwapChain__Free( TgKN_GPU_CXT_SWAP_ID_C ARG0 )
{
}

#define __PARENT_FILE__ "TgS (REF) Kernel [GPU] [API].c"
#define ENABLE_RELOAD_GUARD
#include "TgS KERNEL/TgS Kernel [GPU] - Resource [INC].h"
#undef ENABLE_RELOAD_GUARD
#undef __PARENT_FILE__

CLANG_WARN_DISABLE_POP(unused-parameter)

/*# defined (ENABLE_RELOAD_GUARD) */
#else

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  TgS Kernel - Internal [GPU].h                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- GPU - Resource ----------------------------------------------------------------------------------------------------------------------------------------------------------- */

#if defined(MACRO_BUILD_TEXTURE)
TgRESULT T(tgKN_GPU_EXT_,__Execute_Load)( TgKN_FILE_ID_C ARG0, TgRSIZE_C ARG1, T(STg2_KN_GPU_,_DESC_CPC) ARG2, ETgKN_GPU_ALLOCATOR_C ARG3, T(TgKN_GPU_,_ID_C) ARG4 )
{
    return (KTgS_OK);
}

TgVOID T(tgKN_GPU_EXT_,__Execute_Free)( T(TgKN_GPU_,_ID_C) ARG0 )
{
}

/*# defined(MACRO_BUILD_TEXTURE) */
#endif

T(TgKN_GPU_,_ID) T(tgKN_GPU_,__IncRef)( T(TgKN_GPU_,_ID_C) ARG0 )
{
    return (ARG0);
}

T(TgKN_GPU_,_ID) T(tgKN_GPU_,__Release)( T(TgKN_GPU_,_ID_C) ARG0 )
{
    return (ARG0);
}


#if defined(MACRO_BUILD_TEXTURE)
TgRESULT T(tgKN_GPU_EXT_,_Inst__Init)( UTg2_KN_GPU_CMD_C ARG0, T(TgKN_GPU_,_INST_ID_C) ARG1, TgCHAR_U8_CPCU ARG2 )
{
    return (KTgS_OK);
}

TgVOID T(tgKN_GPU_EXT_,_Inst__Free)( T(TgKN_GPU_,_INST_ID_C) ARG0, TgKN_GPU_CXT_EXEC_ID_C ARG1 )
{
}

TgVOID T(tgKN_GPU_EXT_Register_Default_,_Inst)( T(TgKN_GPU_,_INST_ID_C) ARG0 )
{
}

/*# defined(MACRO_BUILD_TEXTURE) */
#endif


/* ---- Resource - GPU - Texture - API ------------------------------------------------------------------------------------------------------------------------------------------- */

#if defined(MACRO_BUILD_TEXTURE)
TgVOID T(tgKN_GPU_EXT_,__Fast_Lock)( STg2_KN_GPU_TX_Surface_PCU NONULL OUT0, UTg2_KN_GPU_CMD_C ARG1, T(TgKN_GPU_,_INST_ID_C) ARG2 )
{
}

TgVOID T(tgKN_GPU_EXT_,__Lock)( STg2_KN_GPU_TX_Surface_PCU NONULL OUT0, UTg2_KN_GPU_CMD_C ARG1, T(TgKN_GPU_,_INST_ID_C) ARG2 )
{
}

TgVOID T(tgKN_GPU_EXT_,__Fast_Unlock)( UTg2_KN_GPU_CMD_C ARG0, STg2_KN_GPU_TX_Surface_PCU ARG1, T(TgKN_GPU_,_INST_ID_C) ARG2 )
{
}

TgVOID T(tgKN_GPU_EXT_,__Unlock)( UTg2_KN_GPU_CMD_C ARG0, STg2_KN_GPU_TX_Surface_PCU ARG1, T(TgKN_GPU_,_INST_ID_C) ARG2 )
{
}

/*# defined(MACRO_BUILD_TEXTURE) */
#endif


/* =============================================================================================================================================================================== */

/*# defined (ENABLE_RELOAD_GUARD) */
#endif
