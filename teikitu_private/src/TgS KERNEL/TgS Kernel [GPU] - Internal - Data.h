/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Kernel [GPU] - Internal - Data.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_KERNEL_GPU_INTERNAL_DATA_H) && defined(TgBUILD_FEATURE__GRAPHICS)


/* == Kernel ===================================================================================================================================================================== */
#if !defined (ENABLE_RELOAD_GUARD)

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Data                                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/* NOTE: Data declarations for template resource and resource libraries are declared in the associated header files. */

/* ---- GPU - Configuration ------------------------------------------------------------------------------------------------------------------------------------------------------ */

TgEXTN TgCN_VAR_ID                          g_tiCVAR_KN_GPU_Physical_Device;
TgEXTN TgCN_VAR_ID                          g_tiCVAR_KN_GPU_Output;
TgEXTN TgCN_VAR_ID                          g_tiCVAR_KN_GPU_Width;
TgEXTN TgCN_VAR_ID                          g_tiCVAR_KN_GPU_Height;
TgEXTN TgCN_VAR_ID                          g_tiCVAR_KN_GPU_Refresh_Rate;
TgEXTN TgCN_VAR_ID                          g_tiCVAR_KN_GPU_ScanOut_HDR;

TgEXTN TgCHAR_U8                            g_szKN_GPU_Physical_Device[128];
TgEXTN TgCHAR_U8                            g_szKN_GPU_Output[32];
TgEXTN TgUINT_E32                           g_uiKN_GPU_Width;
TgEXTN TgUINT_E32                           g_uiKN_GPU_Height;
TgEXTN TgUINT_E32                           g_uiKN_GPU_Refresh_Rate;
TgEXTN TgBOOL                               g_bKN_GPU_ScanOut_HDR;


/* ---- GPU - Console ------------------------------------------------------------------------------------------------------------------------------------------------------------- */

#if TgCOMPILE__CONSOLE
TgEXTN TgCHAR_U8                            g_uszKN_GPU_LOG_Render_Buffer[KTgCN_OSLOG_LINE_LENGTH*KTgCN_OSLOG_MAX_LINE];
TgEXTN TgRSIZE                              g_nuiKN_GPU_LOG_Line;
TgEXTN TgCHAR_U8                            g_uszKN_GPU_CON_Render_Buffer[KTgCN_OSCON_MAX_LINE*KTgCN_OSCON_LINE_LENGTH];
TgEXTN TgRSIZE                              g_nuiKN_GPU_CON_Line;
/*# TgCOMPILE__CONSOLE */
#endif


/* ---- GPU - Contexts ------------------------------------------------------------------------------------------------------------------------------------------------------------ */

TgEXTN STg2_KN_GPU_CXT_HOST_EXTN            g_sKN_GPU_CXT_HOST_EXTN;
TgEXTN STg2_KN_GPU_CXT_HOST                 g_sKN_GPU_CXT_HOST;

TgEXTN STg2_KN_GPU_CXT_DEVC                 g_asKN_GPU_CXT_DEVC[KTgKN_GPU_MAX_DEVC_CONTEXT];
TgEXTN STg2_UT_LF_ISO__ST                   g_sKN_GPU_CXT_DEVC_Free_Stack;
TgEXTN STg2_KN_GPU_CXT_EXEC_EXTN            g_asKN_GPU_CXT_EXEC_EXTN[KTgKN_GPU_MAX_EXEC_CONTEXT];
TgEXTN STg2_KN_GPU_CXT_EXEC                 g_asKN_GPU_CXT_EXEC[KTgKN_GPU_MAX_EXEC_CONTEXT];
TgEXTN STg2_UT_LF_ISO__ST                   g_sKN_GPU_CXT_EXEC_Free_Stack;
TgEXTN STg2_KN_GPU_CXT_SWAP                 g_asKN_GPU_CXT_SWAP[KTgKN_GPU_MAX_SWAP_CONTEXT];
TgEXTN STg2_UT_LF_ISO__ST                   g_sKN_GPU_CXT_SWAP_Free_Stack;


/* ---- GPU - Resource ------------------------------------------------------------------------------------------------------------------------------------------------------------ */

TgEXTN STg2_KN_GPU_Graphics_Pipeline_C      g_asKN_GPU_Graphics_Pipeline[ETgKN_GPU_GRAPHICS_PIPELINE_COUNT];
TgEXTN STg2_KN_GPU_Compute_Pipeline_C       g_asKN_GPU_Compute_Pipeline_For_Rendering[ETgKN_GPU_COMPUTE_PIPELINE_FOR_RENDERING_COUNT];
//TgEXTN STg2_KN_GPU_Compute_Pipeline_C       g_asKN_GPU_Compute_Pipeline[ETgKN_GPU_COMPUTE_PIPELINE_COUNT];

TgEXTN TgRSIZE_C                            g_uiAligned_Render_DESC_UBO_Size;

#define __PARENT_FILE__ "TgS Kernel [GPU] - Internal - Data.h"
#define ENABLE_RELOAD_GUARD
#include "TgS KERNEL/TgS Kernel [GPU] - Resource [INC].h"
#undef ENABLE_RELOAD_GUARD
#undef __PARENT_FILE__

#define TGS_KERNEL_GPU_INTERNAL_DATA_H




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Data for Debug                                                                                                                                                        */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

#if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)
TgEXTN STg2_KN_GPU_CXT_HOST_DBG             g_sKN_GPU_DBG_CXT_HOST;

TgEXTN STg2_KN_GPU_Graphics_Pipeline_C      g_asKN_GPU_DBG_Graphics_Pipeline[ETgKN_GPU_DBG_GRAPHICS_PIPELINE_COUNT];

TgEXTN TgUINT_E08_C                         g_uiKN_GPU_STD_DOS_Font_Default_Data[1024];
TgEXTN TgUINT_E08_C                         g_uiKN_GPU_STD_DOS_Font_Future_Data[1024];
TgEXTN TgUINT_E08_C                         g_uiKN_GPU_STD_DOS_Font_Block_Data[1024];
TgEXTN TgUINT_E08_C                         g_uiKN_GPU_STD_DOS_Font_Marcio_Data[4096];

TgEXTN STg2_KN_GPU_FONT                     g_sKN_GPU_STD_DOS_Font[ETgKN_GPU_DOS_FONT_ROM_COUNT];

TgEXTN STg2_KN_GPU_Vertex_UI_Text_C         g_sVertex_Strip_Text[4];
TgEXTN STg2_KN_GPU_Vertex_UI_C              g_sVertex_Strip_Quad[4];
TgEXTN STg2_KN_GPU_Vertex_UI_C              g_sVertex_Strip_Gradient[4];
TgEXTN STg2_KN_GPU_Vertex_Geom_02_C         g_sVertex_List_Cube[36];

/*# defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
#endif




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Stats | Debug Data                                                                                                                                                    */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- Stat --------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if TgS_STAT__KERNEL || TgS_DEBUG__KERNEL

TgEXTN TgUINT_E32                           g_uiKN_Stats_Loaded_Mesh_Vertex; /* #IMPLEMENT */
TgEXTN TgUINT_E32                           g_uiKN_Stats_Loaded_Mesh_Face; /* #IMPLEMENT */
TgEXTN TgRSIZE                              g_uiKN_Stats_Memory_Buffer; /* #IMPLEMENT */
TgEXTN TgRSIZE                              g_uiKN_Stats_Memory_Mesh; /* #IMPLEMENT */
TgEXTN TgRSIZE                              g_uiKN_Stats_Memory_Mesh_Collision; /* #IMPLEMENT */

/*# TgS_STAT__KERNEL || TgS_DEBUG__KERNEL */
#endif

/*# defined (ENABLE_RELOAD_GUARD) */
#else

TgEXTN T(TgKN_GPU_,_ID_A)                   T(g_axsKN_Lib_,_Ref_Singleton)[T(KTgKN_GPU_MAX_,)]; /**< Atomic UID and Ref associated with a resource instance. */
TgEXTN T(STg2_KN_GPU_,_DATA)                T(g_asKN_Lib_,_Data)[T(KTgKN_GPU_MAX_,)]; /**< Pointer to the entire set of resources managed by this library. */
TgEXTN STg2_UT_LF_ISO__ST                   T(g_sKN_Lib_,); /**< Pointer to an atomic lock-less stack that holds the collection of available resources. */
TgEXTN STg2_UT_LF_ISO__SN                   T(g_sKN_Lib_,_Lock); /** Spin-lock that is used extremely rarely - specifically during init/free phases. */
TgEXTN TgUINT_E64_A                         T(g_xnuiKN_Lib_,_Init); /** Salt value used as part of the identifier structure. Resolve ABA issues. */

#if defined(MACRO_BUILD_TEXTURE)
TgEXTN T(TgKN_GPU_,_INST_ID_A)              T(g_axsCXT_,_Inst_Ref_Singleton)[KTgKN_GPU_MAX_EXEC_CONTEXT][T(KTgKN_GPU_MAX_,_INST)];
TgEXTN T(TgKN_GPU_,_ID)                     T(g_asCXT_,)[KTgKN_GPU_MAX_EXEC_CONTEXT][T(KTgKN_GPU_MAX_,_INST)];
TgEXTN STg2_UT_LF_ISO__ST_Unaligned         T(g_sCXT_,_Inst)[KTgKN_GPU_MAX_EXEC_CONTEXT];
TgEXTN STg2_UT_LF_ISO__SN                   T(g_sCXT_,_Inst_Lock)[KTgKN_GPU_MAX_EXEC_CONTEXT];
/*# defined(MACRO_BUILD_TEXTURE) */
#endif

#if TgS_STAT__KERNEL || TgS_DEBUG__KERNEL
TgEXTN TgRSIZE                              T(g_uiKN_Size_GPU_,)[T(KTgKN_GPU_MAX_,)]; /**< Amount of memory used for each resource. */
TgEXTN TgRSIZE                              T(g_uiKN_Size_GPU_,_Total); /**< Total amount of memory managed by the library. */
/*# TgS_STAT__KERNEL || TgS_DEBUG__KERNEL */
#endif

#if TgS_DEBUG__KERNEL
TgEXTN TgCHAR_U8                            T(g_szKN_GPU_,)[T(KTgKN_GPU_MAX_,)][KTgMAX_FILE_NAME]; /**< Resource name used for defect fixing. */
/*# TgS_DEBUG__KERNEL */
#endif


/* =============================================================================================================================================================================== */

/*# defined (ENABLE_RELOAD_GUARD) */
#endif

/*# !defined(TGS_KERNEL_INTERNAL_DATA_GPU_H) && defined(TgBUILD_FEATURE__GRAPHICS) */
#endif
