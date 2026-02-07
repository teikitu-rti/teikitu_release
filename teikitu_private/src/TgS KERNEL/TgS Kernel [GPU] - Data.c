/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Kernel [GPU] - Data.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Kernel ===================================================================================================================================================================== */
#if !defined (ENABLE_RELOAD_GUARD)

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  System ID                                                                                                                                                                      */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgKI_DEFINE(KN_GPU_CXT_HOST_ID);
TgKI_DEFINE(KN_GPU_CXT_HOST_EXTN_ID);
TgKI_DEFINE(KN_GPU_CXT_DEVC_ID);
TgKI_DEFINE(KN_GPU_CXT_EXEC_ID);
TgKI_DEFINE(KN_GPU_CXT_SWAP_ID);
TgKI_DEFINE(KN_GPU_CXT_WORK_ID);
TgKI_DEFINE(KN_GPU_RENDER_TARGET_ID);

TgKN_GPU_VS_ID_C                            KTgKN_GPU_VS_ID__INVALID = { KTgID__INVALID_VALUE };
TgKN_GPU_TCS_ID_C                           KTgKN_GPU_TCS_ID__INVALID = { KTgID__INVALID_VALUE };
TgKN_GPU_TES_ID_C                           KTgKN_GPU_TES_ID__INVALID = { KTgID__INVALID_VALUE };
TgKN_GPU_GS_ID_C                            KTgKN_GPU_GS_ID__INVALID = { KTgID__INVALID_VALUE };
TgKN_GPU_TS_ID_C                            KTgKN_GPU_TS_ID__INVALID = { KTgID__INVALID_VALUE };
TgKN_GPU_MS_ID_C                            KTgKN_GPU_MS_ID__INVALID = { KTgID__INVALID_VALUE };
TgKN_GPU_FS_ID_C                            KTgKN_GPU_FS_ID__INVALID = { KTgID__INVALID_VALUE };
TgKN_GPU_CS_ID_C                            KTgKN_GPU_CS_ID__INVALID = { KTgID__INVALID_VALUE };

TgKN_GPU_TX_CBE_ID_C                        KTgKN_GPU_TX_CBE_ID__INVALID = { KTgID__INVALID_VALUE };
TgKN_GPU_TX_IMG_ID_C                        KTgKN_GPU_TX_IMG_ID__INVALID = { KTgID__INVALID_VALUE };
TgKN_GPU_TX_VOL_ID_C                        KTgKN_GPU_TX_VOL_ID__INVALID = { KTgID__INVALID_VALUE };

TgKN_GPU_TX_CBE_INST_ID_C                   KTgKN_GPU_TX_CBE_INST_ID__INVALID = { KTgID__INVALID_VALUE };
TgKN_GPU_TX_IMG_INST_ID_C                   KTgKN_GPU_TX_IMG_INST_ID__INVALID = { KTgID__INVALID_VALUE };
TgKN_GPU_TX_VOL_INST_ID_C                   KTgKN_GPU_TX_VOL_INST_ID__INVALID = { KTgID__INVALID_VALUE };




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Data                                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/* NOTE: Data definitions for templated resource and resource libraries are declared in the associated source files. */

/* ---- Configuration ------------------------------------------------------------------------------------------------------------------------------------------------------------ */

TgCN_VAR_ID                                 g_tiCVAR_KN_GPU_Physical_Device;
TgCN_VAR_ID                                 g_tiCVAR_KN_GPU_Output;
TgCN_VAR_ID                                 g_tiCVAR_KN_GPU_Width;
TgCN_VAR_ID                                 g_tiCVAR_KN_GPU_Height;
TgCN_VAR_ID                                 g_tiCVAR_KN_GPU_Refresh_Rate;
TgCN_VAR_ID                                 g_tiCVAR_KN_GPU_ScanOut_HDR;

TgCHAR_U8                                   g_szKN_GPU_Physical_Device[128];
TgCHAR_U8                                   g_szKN_GPU_Output[32];
TgUINT_E32                                  g_uiKN_GPU_Width;
TgUINT_E32                                  g_uiKN_GPU_Height;
TgUINT_E32                                  g_uiKN_GPU_Refresh_Rate;
TgBOOL                                      g_bKN_GPU_ScanOut_HDR;


/* ---- GPU - Console ------------------------------------------------------------------------------------------------------------------------------------------------------------- */

#if TgCOMPILE__CONSOLE
TgCHAR_U8                                   g_uszKN_GPU_LOG_Render_Buffer[KTgCN_OSLOG_LINE_LENGTH*KTgCN_OSLOG_MAX_LINE];
TgRSIZE                                     g_nuiKN_GPU_LOG_Line;
TgCHAR_U8                                   g_uszKN_GPU_CON_Render_Buffer[KTgCN_OSCON_MAX_LINE*KTgCN_OSCON_LINE_LENGTH];
TgRSIZE                                     g_nuiKN_GPU_CON_Line;
/*# TgCOMPILE__CONSOLE */
#endif


/* ---- Enumeration and Contexts ------------------------------------------------------------------------------------------------------------------------------------------------- */

STg2_KN_GPU_CXT_HOST_EXTN                   g_sKN_GPU_CXT_HOST_EXTN;
STg2_KN_GPU_CXT_HOST                        g_sKN_GPU_CXT_HOST;

STg2_KN_GPU_CXT_DEVC                        g_asKN_GPU_CXT_DEVC[KTgKN_GPU_MAX_DEVC_CONTEXT];
STg2_UT_LF_ISO__ST                          g_sKN_GPU_CXT_DEVC_Free_Stack;
STg2_KN_GPU_CXT_EXEC_EXTN                   g_asKN_GPU_CXT_EXEC_EXTN[KTgKN_GPU_MAX_EXEC_CONTEXT];
STg2_KN_GPU_CXT_EXEC                        g_asKN_GPU_CXT_EXEC[KTgKN_GPU_MAX_EXEC_CONTEXT];
STg2_UT_LF_ISO__ST                          g_sKN_GPU_CXT_EXEC_Free_Stack;
STg2_KN_GPU_CXT_SWAP                        g_asKN_GPU_CXT_SWAP[KTgKN_GPU_MAX_SWAP_CONTEXT];
STg2_UT_LF_ISO__ST                          g_sKN_GPU_CXT_SWAP_Free_Stack;


/* ---- GPU Resource ------------------------------------------------------------------------------------------------------------------------------------------------------------- */

                                            /* ---- Pipeline Descriptions -------------------------------------------------------------------------------------------------------- */

STg2_KN_GPU_Graphics_Pipeline_C             g_asKN_GPU_Graphics_Pipeline[ETgKN_GPU_GRAPHICS_PIPELINE_COUNT] = {
                                              /*{
                                                    Shader Stages: Vertex is set by the input layout, and the fragment shader is 1:1 with the pipeline enumeration.
                                                }*/

                                                {   /* ETgKN_GPU_GRAPHICS_PIPELINE_UNIT_TEST_SCENE */
                                                    .m_uiPipeline_Layout = ETgKN_GPU_PIPELINE_LAYOUT__UNIT_TEST,
                                                    .m_enInput_Layout = ETgKN_GPU_INPUT_LAYOUT_VERTEX_GEOM_02,
                                                    .m_enTopology = ETgKN_GPU_EXT_TOPOLOGY_TRIANGLE_LIST,
                                                    .m_enRasterizer_State = ETgKN_GPU_RASTERIZER_STATE_DEFAULT_SOLID,
                                                    .m_enBlend_State = ETgKN_GPU_BLEND_STATE_NONE,
                                                    .m_enDepth_State = ETgKN_GPU_DEPTH_STENCIL_STATE_TEST_DEPTH,
                                                    .m_uiVS = ETgKN_GPU_SHADER_VS_TEST_SN_VWNC,
                                                    .m_uiTCS = ETgKN_GPU_SHADER_TCS_END,
                                                    .m_uiTES = ETgKN_GPU_SHADER_TES_END,
                                                    .m_uiGS = ETgKN_GPU_SHADER_GS_END,
                                                    .m_uiTS = ETgKN_GPU_SHADER_TS_END,
                                                    .m_uiMS = ETgKN_GPU_SHADER_MS_END,
                                                    .m_uiFS = ETgKN_GPU_SHADER_FS_TEST_VWNC,
                                                    .m_bUnlit = true,
                                                    .m_uszName = u8"UNIT TEST SCENE",
                                                },

                                                {   /* ETgKN_GPU_GRAPHICS_PIPELINE_PARTICLE_00 */
                                                    .m_uiPipeline_Layout = ETgKN_GPU_PIPELINE_LAYOUT__UNIT_TEST,
                                                    .m_enInput_Layout = ETgKN_GPU_INPUT_LAYOUT_VERTEX_PARTICLE_00,
                                                    .m_enTopology = ETgKN_GPU_EXT_TOPOLOGY_TRIANGLE_LIST,
                                                    .m_enRasterizer_State = ETgKN_GPU_RASTERIZER_STATE_DEFAULT_SOLID,
                                                    .m_enBlend_State = ETgKN_GPU_BLEND_STATE_ALPHA,
                                                    .m_enDepth_State = ETgKN_GPU_DEPTH_STENCIL_STATE_TEST_DEPTH,
                                                    .m_uiVS = ETgKN_GPU_SHADER_VS_PARTICLE_SC_VWC_00,
                                                    .m_uiTCS = ETgKN_GPU_SHADER_TCS_END,
                                                    .m_uiTES = ETgKN_GPU_SHADER_TES_END,
                                                    .m_uiGS = ETgKN_GPU_SHADER_GS_END,
                                                    .m_uiTS = ETgKN_GPU_SHADER_TS_END,
                                                    .m_uiMS = ETgKN_GPU_SHADER_MS_END,
                                                    .m_uiFS = ETgKN_GPU_SHADER_FS_PARTICLE_VWC,
                                                    .m_bUnlit = true,
                                                    .m_uszName = u8"PARTICLE 00",
                                                },

                                                {   /* ETgKN_GPU_GRAPHICS_PIPELINE_PARTICLE_01 */
                                                    .m_uiPipeline_Layout = ETgKN_GPU_PIPELINE_LAYOUT__UNIT_TEST,
                                                    .m_enInput_Layout = ETgKN_GPU_INPUT_LAYOUT_VERTEX_PARTICLE_01,
                                                    .m_enTopology = ETgKN_GPU_EXT_TOPOLOGY_TRIANGLE_LIST,
                                                    .m_enRasterizer_State = ETgKN_GPU_RASTERIZER_STATE_DEFAULT_SOLID,
                                                    .m_enBlend_State = ETgKN_GPU_BLEND_STATE_ALPHA,
                                                    .m_enDepth_State = ETgKN_GPU_DEPTH_STENCIL_STATE_TEST_DEPTH,
                                                    .m_uiVS = ETgKN_GPU_SHADER_VS_PARTICLE_SC_VWC_01,
                                                    .m_uiTCS = ETgKN_GPU_SHADER_TCS_END,
                                                    .m_uiTES = ETgKN_GPU_SHADER_TES_END,
                                                    .m_uiGS = ETgKN_GPU_SHADER_GS_END,
                                                    .m_uiTS = ETgKN_GPU_SHADER_TS_END,
                                                    .m_uiMS = ETgKN_GPU_SHADER_MS_END,
                                                    .m_uiFS = ETgKN_GPU_SHADER_FS_PARTICLE_VWC,
                                                    .m_bUnlit = true,
                                                    .m_uszName = u8"PARTICLE 01",
                                                }
                                            };

STg2_KN_GPU_Compute_Pipeline_C              g_asKN_GPU_Compute_Pipeline_For_Rendering[ETgKN_GPU_COMPUTE_PIPELINE_FOR_RENDERING_COUNT] = {
                                                {   /* ETgKN_GPU_GRAPHICS_PIPELINE_PARTICLE_01 */
                                                    .m_uiPipeline_Layout = ETgKN_GPU_PIPELINE_LAYOUT__POST_PROCESS_COMPUTE,
                                                    .m_uiCS = ETgKN_GPU_SHADER_CS_COLOUR_CORRECTION,
                                                    .m_uszName = u8"COLOLUR CORRECTION",
                                                },

                                                {   /* ETgKN_GPU_GRAPHICS_PIPELINE_PARTICLE_01 */
                                                    .m_uiPipeline_Layout = ETgKN_GPU_PIPELINE_LAYOUT__POST_PROCESS_COMPUTE,
                                                    .m_uiCS = ETgKN_GPU_SHADER_CS_LUMINANCE_HISTOGRAM,
                                                    .m_uszName = u8"LUMINANCE HISTOGRAM",
                                                }
                                            };

#define __PARENT_FILE__ "TgS Kernel [GPU] - Data.c"
#define ENABLE_RELOAD_GUARD
#include "TgS KERNEL/TgS Kernel [GPU] - Resource [INC].h"
#undef ENABLE_RELOAD_GUARD
#undef __PARENT_FILE__




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Data for Debug                                                                                                                                                        */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
#if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)

STg2_KN_GPU_CXT_HOST_DBG                    g_sKN_GPU_DBG_CXT_HOST;

STg2_KN_GPU_Graphics_Pipeline_C             g_asKN_GPU_DBG_Graphics_Pipeline[ETgKN_GPU_DBG_GRAPHICS_PIPELINE_COUNT] = {
                                                {   /* ETgKN_GPU_DBG_GRAPHICS_PIPELINE_UI */
                                                    .m_uiPipeline_Layout = ETgKN_GPU_DBG_PIPELINE_LAYOUT__NONE,
                                                    .m_enInput_Layout = ETgKN_GPU_INPUT_LAYOUT_VERTEX_UI,
                                                    .m_enTopology = ETgKN_GPU_EXT_TOPOLOGY_TRIANGLE_STRIP,
                                                    .m_enRasterizer_State = ETgKN_GPU_RASTERIZER_STATE_DEFAULT_SOLID,
                                                    .m_enBlend_State = ETgKN_GPU_BLEND_STATE_ALPHA,
                                                    .m_enDepth_State = ETgKN_GPU_DEPTH_STENCIL_STATE_TEST_NONE,
                                                    .m_uiVS = ETgKN_GPU_DBG_SHADER_VS_VERTEX_UI_SUC_UC,
                                                    .m_uiTCS = ETgKN_GPU_DBG_SHADER_TCS_END,
                                                    .m_uiTES = ETgKN_GPU_DBG_SHADER_TES_END,
                                                    .m_uiGS = ETgKN_GPU_DBG_SHADER_GS_END,
                                                    .m_uiTS = ETgKN_GPU_DBG_SHADER_TS_END,
                                                    .m_uiMS = ETgKN_GPU_DBG_SHADER_MS_END,
                                                    .m_uiFS = ETgKN_GPU_DBG_SHADER_FS_UC_00,
                                                    .m_bUnlit = true,
                                                    .m_uszName = u8"DEBUG UI",
                                                },

                                                {   /* ETgKN_GPU_GRAPHICS_PIPELINE_DEBUG_UI_WITH_GAMMA */
                                                    .m_uiPipeline_Layout = ETgKN_GPU_DBG_PIPELINE_LAYOUT__NONE,
                                                    .m_enInput_Layout = ETgKN_GPU_INPUT_LAYOUT_VERTEX_UI,
                                                    .m_enTopology = ETgKN_GPU_EXT_TOPOLOGY_TRIANGLE_STRIP,
                                                    .m_enRasterizer_State = ETgKN_GPU_RASTERIZER_STATE_DEFAULT_SOLID,
                                                    .m_enBlend_State = ETgKN_GPU_BLEND_STATE_ALPHA,
                                                    .m_enDepth_State = ETgKN_GPU_DEPTH_STENCIL_STATE_TEST_NONE,
                                                    .m_uiVS = ETgKN_GPU_DBG_SHADER_VS_VERTEX_UI_SUC_UC,
                                                    .m_uiTCS = ETgKN_GPU_DBG_SHADER_TCS_END,
                                                    .m_uiTES = ETgKN_GPU_DBG_SHADER_TES_END,
                                                    .m_uiGS = ETgKN_GPU_DBG_SHADER_GS_END,
                                                    .m_uiTS = ETgKN_GPU_DBG_SHADER_TS_END,
                                                    .m_uiMS = ETgKN_GPU_DBG_SHADER_MS_END,
                                                    .m_uiFS = ETgKN_GPU_DBG_SHADER_FS_UC_01,
                                                    .m_bUnlit = true,
                                                    .m_uszName = u8"DEBUG UI GAMMA",
                                                },

                                                {   /* ETgKN_GPU_DBG_GRAPHICS_PIPELINE_TEXT */
                                                    .m_uiPipeline_Layout = ETgKN_GPU_DBG_PIPELINE_LAYOUT__SBO,
                                                    .m_enInput_Layout = ETgKN_GPU_INPUT_LAYOUT_INSTANCE_VERTEX_UI_TEXT,
                                                    .m_enTopology = ETgKN_GPU_EXT_TOPOLOGY_TRIANGLE_STRIP,
                                                    .m_enRasterizer_State = ETgKN_GPU_RASTERIZER_STATE_DEFAULT_SOLID,
                                                    .m_enBlend_State = ETgKN_GPU_BLEND_STATE_ALPHA,
                                                    .m_enDepth_State = ETgKN_GPU_DEPTH_STENCIL_STATE_TEST_NONE,
                                                    .m_uiVS = ETgKN_GPU_DBG_SHADER_VS_VERTEX_TEXT_SU_U,
                                                    .m_uiTCS = ETgKN_GPU_DBG_SHADER_TCS_END,
                                                    .m_uiTES = ETgKN_GPU_DBG_SHADER_TES_END,
                                                    .m_uiGS = ETgKN_GPU_DBG_SHADER_GS_END,
                                                    .m_uiTS = ETgKN_GPU_DBG_SHADER_TS_END,
                                                    .m_uiMS = ETgKN_GPU_DBG_SHADER_MS_END,
                                                    .m_uiFS = ETgKN_GPU_DBG_SHADER_FS_TEXT_U,
                                                    .m_bUnlit = true,
                                                    .m_uszName = u8"DEBUG UI TEXT",
                                                },

                                                {   /* ETgKN_GPU_GRAPHICS_PIPELINE_DEBUG_LINE_MESH */
                                                    .m_uiPipeline_Layout = ETgKN_GPU_DBG_PIPELINE_LAYOUT__LINE_TASK_MESH,
                                                    .m_enTopology = ETgKN_GPU_EXT_TOPOLOGY_TRIANGLE_LIST,
                                                    .m_enRasterizer_State = ETgKN_GPU_RASTERIZER_STATE_DEFAULT_SOLID,
                                                    .m_enBlend_State = ETgKN_GPU_BLEND_STATE_ALPHA,
                                                    .m_enDepth_State = ETgKN_GPU_DEPTH_STENCIL_STATE_TEST_DEPTH,
                                                    .m_uiVS = ETgKN_GPU_DBG_SHADER_VS_END,
                                                    .m_uiTCS = ETgKN_GPU_DBG_SHADER_TCS_END,
                                                    .m_uiTES = ETgKN_GPU_DBG_SHADER_TES_END,
                                                    .m_uiGS = ETgKN_GPU_DBG_SHADER_GS_END,
                                                    .m_uiTS = ETgKN_GPU_DBG_SHADER_TS_LINE,
                                                    .m_uiMS = ETgKN_GPU_DBG_SHADER_MS_LINE,
                                                    .m_uiFS = ETgKN_GPU_DBG_SHADER_FS_LINE,
                                                    .m_bUnlit = true,
                                                    .m_uszName = u8"DEBUG LINE",
                                                },

                                                {   /* ETgKN_GPU_DBG_GRAPHICS_PIPELINE_GEOM_00 */
                                                    .m_uiPipeline_Layout = ETgKN_GPU_DBG_PIPELINE_LAYOUT__NONE,
                                                    .m_enInput_Layout = ETgKN_GPU_INPUT_LAYOUT_VERTEX_GEOM_00,
                                                    .m_enTopology = ETgKN_GPU_EXT_TOPOLOGY_TRIANGLE_LIST,
                                                    .m_enRasterizer_State = ETgKN_GPU_RASTERIZER_STATE_DEFAULT_SOLID,
                                                    .m_enBlend_State = ETgKN_GPU_BLEND_STATE_ALPHA,
                                                    .m_enDepth_State = ETgKN_GPU_DEPTH_STENCIL_STATE_TEST_DEPTH,
                                                    .m_uiVS = ETgKN_GPU_DBG_SHADER_VS_VERTEX_GEOM_S_VW,
                                                    .m_uiTCS = ETgKN_GPU_DBG_SHADER_TCS_END,
                                                    .m_uiTES = ETgKN_GPU_DBG_SHADER_TES_END,
                                                    .m_uiGS = ETgKN_GPU_DBG_SHADER_GS_END,
                                                    .m_uiTS = ETgKN_GPU_DBG_SHADER_TS_END,
                                                    .m_uiMS = ETgKN_GPU_DBG_SHADER_MS_END,
                                                    .m_uiFS = ETgKN_GPU_DBG_SHADER_FS_VW,
                                                    .m_bUnlit = true,
                                                    .m_uszName = u8"DEBUG GEOM 00",
                                                },

                                                {   /* ETgKN_GPU_DBG_GRAPHICS_PIPELINE_GEOM_01 */
                                                    .m_uiPipeline_Layout = ETgKN_GPU_DBG_PIPELINE_LAYOUT__NONE,
                                                    .m_enInput_Layout = ETgKN_GPU_INPUT_LAYOUT_VERTEX_GEOM_01,
                                                    .m_enTopology = ETgKN_GPU_EXT_TOPOLOGY_TRIANGLE_LIST,
                                                    .m_enRasterizer_State = ETgKN_GPU_RASTERIZER_STATE_DEFAULT_SOLID,
                                                    .m_enBlend_State = ETgKN_GPU_BLEND_STATE_ALPHA,
                                                    .m_enDepth_State = ETgKN_GPU_DEPTH_STENCIL_STATE_TEST_DEPTH,
                                                    .m_uiVS = ETgKN_GPU_DBG_SHADER_VS_VERTEX_GEOM_SC_VWC,
                                                    .m_uiTCS = ETgKN_GPU_DBG_SHADER_TCS_END,
                                                    .m_uiTES = ETgKN_GPU_DBG_SHADER_TES_END,
                                                    .m_uiGS = ETgKN_GPU_DBG_SHADER_GS_END,
                                                    .m_uiTS = ETgKN_GPU_DBG_SHADER_TS_END,
                                                    .m_uiMS = ETgKN_GPU_DBG_SHADER_MS_END,
                                                    .m_uiFS = ETgKN_GPU_DBG_SHADER_FS_VWC_00,
                                                    .m_bUnlit = true,
                                                    .m_uszName = u8"DEBUG GEOM 01",
                                                },

                                                {   /* ETgKN_GPU_DBG_GRAPHICS_PIPELINE_GEOM_01 WITH GAMMA */
                                                    .m_uiPipeline_Layout = ETgKN_GPU_DBG_PIPELINE_LAYOUT__NONE,
                                                    .m_enInput_Layout = ETgKN_GPU_INPUT_LAYOUT_VERTEX_GEOM_01,
                                                    .m_enTopology = ETgKN_GPU_EXT_TOPOLOGY_TRIANGLE_LIST,
                                                    .m_enRasterizer_State = ETgKN_GPU_RASTERIZER_STATE_DEFAULT_SOLID,
                                                    .m_enBlend_State = ETgKN_GPU_BLEND_STATE_ALPHA,
                                                    .m_enDepth_State = ETgKN_GPU_DEPTH_STENCIL_STATE_TEST_DEPTH,
                                                    .m_uiVS = ETgKN_GPU_DBG_SHADER_VS_VERTEX_GEOM_SC_VWC,
                                                    .m_uiTCS = ETgKN_GPU_DBG_SHADER_TCS_END,
                                                    .m_uiTES = ETgKN_GPU_DBG_SHADER_TES_END,
                                                    .m_uiGS = ETgKN_GPU_DBG_SHADER_GS_END,
                                                    .m_uiTS = ETgKN_GPU_DBG_SHADER_TS_END,
                                                    .m_uiMS = ETgKN_GPU_DBG_SHADER_MS_END,
                                                    .m_uiFS = ETgKN_GPU_DBG_SHADER_FS_VWC_01,
                                                    .m_bUnlit = true,
                                                    .m_uszName = u8"DEBUG GEOM 01 WITH GAMMA",
                                                },

                                                {   /* ETgKN_GPU_DBG_GRAPHICS_PIPELINE_GEOM_02 */
                                                    .m_uiPipeline_Layout = ETgKN_GPU_DBG_PIPELINE_LAYOUT__NONE,
                                                    .m_enInput_Layout = ETgKN_GPU_INPUT_LAYOUT_VERTEX_GEOM_02,
                                                    .m_enTopology = ETgKN_GPU_EXT_TOPOLOGY_TRIANGLE_LIST,
                                                    .m_enRasterizer_State = ETgKN_GPU_RASTERIZER_STATE_DEFAULT_SOLID,
                                                    .m_enBlend_State = ETgKN_GPU_BLEND_STATE_ALPHA,
                                                    .m_enDepth_State = ETgKN_GPU_DEPTH_STENCIL_STATE_TEST_DEPTH,
                                                    .m_uiVS = ETgKN_GPU_DBG_SHADER_VS_VERTEX_GEOM_SN_VWNC,
                                                    .m_uiTCS = ETgKN_GPU_DBG_SHADER_TCS_END,
                                                    .m_uiTES = ETgKN_GPU_DBG_SHADER_TES_END,
                                                    .m_uiGS = ETgKN_GPU_DBG_SHADER_GS_END,
                                                    .m_uiTS = ETgKN_GPU_DBG_SHADER_TS_END,
                                                    .m_uiMS = ETgKN_GPU_DBG_SHADER_MS_END,
                                                    .m_uiFS = ETgKN_GPU_DBG_SHADER_FS_VWNC,
                                                    .m_bUnlit = true,
                                                    .m_uszName = u8"DEBUG GEOM 02",
                                                },

                                                {   /* ETgKN_GPU_DBG_GRAPHICS_PIPELINE_GEOM_02_INSTANCE */
                                                    .m_uiPipeline_Layout = ETgKN_GPU_DBG_PIPELINE_LAYOUT__SBO,
                                                    .m_enInput_Layout = ETgKN_GPU_INPUT_LAYOUT_INSTANCE_VERTEX_GEOM_02,
                                                    .m_enTopology = ETgKN_GPU_EXT_TOPOLOGY_TRIANGLE_LIST,
                                                    .m_enRasterizer_State = ETgKN_GPU_RASTERIZER_STATE_DEFAULT_SOLID,
                                                    .m_enBlend_State = ETgKN_GPU_BLEND_STATE_ALPHA,
                                                    .m_enDepth_State = ETgKN_GPU_DEPTH_STENCIL_STATE_TEST_DEPTH,
                                                    .m_uiVS = ETgKN_GPU_DBG_SHADER_VS_VERTEX_GEOM_SN_VWNC_I,
                                                    .m_uiTCS = ETgKN_GPU_DBG_SHADER_TCS_END,
                                                    .m_uiTES = ETgKN_GPU_DBG_SHADER_TES_END,
                                                    .m_uiGS = ETgKN_GPU_DBG_SHADER_GS_END,
                                                    .m_uiTS = ETgKN_GPU_DBG_SHADER_TS_END,
                                                    .m_uiMS = ETgKN_GPU_DBG_SHADER_MS_END,
                                                    .m_uiFS = ETgKN_GPU_DBG_SHADER_FS_VWNC,
                                                    .m_bUnlit = true,
                                                    .m_uszName = u8"DEBUG GEOM 02 INSTANCE",
                                                },

                                                {   /* ETgKN_GPU_DBG_GRAPHICS_PIPELINE_GEOM_02_LIT */
                                                    .m_uiPipeline_Layout = ETgKN_GPU_DBG_PIPELINE_LAYOUT__NONE,
                                                    .m_enInput_Layout = ETgKN_GPU_INPUT_LAYOUT_VERTEX_GEOM_02,
                                                    .m_enTopology = ETgKN_GPU_EXT_TOPOLOGY_TRIANGLE_LIST,
                                                    .m_enRasterizer_State = ETgKN_GPU_RASTERIZER_STATE_DEFAULT_SOLID,
                                                    .m_enBlend_State = ETgKN_GPU_BLEND_STATE_ALPHA,
                                                    .m_enDepth_State = ETgKN_GPU_DEPTH_STENCIL_STATE_TEST_DEPTH,
                                                    .m_uiVS = ETgKN_GPU_DBG_SHADER_VS_VERTEX_GEOM_SN_VWNC,
                                                    .m_uiTCS = ETgKN_GPU_DBG_SHADER_TCS_END,
                                                    .m_uiTES = ETgKN_GPU_DBG_SHADER_TES_END,
                                                    .m_uiGS = ETgKN_GPU_DBG_SHADER_GS_END,
                                                    .m_uiTS = ETgKN_GPU_DBG_SHADER_TS_END,
                                                    .m_uiMS = ETgKN_GPU_DBG_SHADER_MS_END,
                                                    .m_uiFS = ETgKN_GPU_DBG_SHADER_FS_VWNC,
                                                    .m_bUnlit = false,
                                                    .m_uszName = u8"DEBUG GEOM 02 LIT",
                                                },

                                                {   /* ETgKN_GPU_DBG_GRAPHICS_PIPELINE_GEOM_02_LIT_INSTANCE */
                                                    .m_uiPipeline_Layout = ETgKN_GPU_DBG_PIPELINE_LAYOUT__SBO,
                                                    .m_enInput_Layout = ETgKN_GPU_INPUT_LAYOUT_INSTANCE_VERTEX_GEOM_02,
                                                    .m_enTopology = ETgKN_GPU_EXT_TOPOLOGY_TRIANGLE_LIST,
                                                    .m_enRasterizer_State = ETgKN_GPU_RASTERIZER_STATE_DEFAULT_SOLID,
                                                    .m_enBlend_State = ETgKN_GPU_BLEND_STATE_ALPHA,
                                                    .m_enDepth_State = ETgKN_GPU_DEPTH_STENCIL_STATE_TEST_DEPTH,
                                                    .m_uiVS = ETgKN_GPU_DBG_SHADER_VS_VERTEX_GEOM_SN_VWNC_I,
                                                    .m_uiTCS = ETgKN_GPU_DBG_SHADER_TCS_END,
                                                    .m_uiTES = ETgKN_GPU_DBG_SHADER_TES_END,
                                                    .m_uiGS = ETgKN_GPU_DBG_SHADER_GS_END,
                                                    .m_uiTS = ETgKN_GPU_DBG_SHADER_TS_END,
                                                    .m_uiMS = ETgKN_GPU_DBG_SHADER_MS_END,
                                                    .m_uiFS = ETgKN_GPU_DBG_SHADER_FS_VWNC,
                                                    .m_bUnlit = false,
                                                    .m_uszName = u8"DEBUG GEOM 02 LIT INSTANCE",
                                                },

                                                {   /* ETgKN_GPU_GRAPHICS_PIPELINE_DEBUG_GEOM_03 */
                                                    .m_uiPipeline_Layout = ETgKN_GPU_DBG_PIPELINE_LAYOUT__NONE,
                                                    .m_enInput_Layout = ETgKN_GPU_INPUT_LAYOUT_VERTEX_GEOM_03,
                                                    .m_enTopology = ETgKN_GPU_EXT_TOPOLOGY_TRIANGLE_LIST,
                                                    .m_enRasterizer_State = ETgKN_GPU_RASTERIZER_STATE_DEFAULT_SOLID,
                                                    .m_enBlend_State = ETgKN_GPU_BLEND_STATE_ALPHA,
                                                    .m_enDepth_State = ETgKN_GPU_DEPTH_STENCIL_STATE_TEST_DEPTH,
                                                    .m_uiVS = ETgKN_GPU_DBG_SHADER_VS_VERTEX_GEOM_SNC_VWNC,
                                                    .m_uiTCS = ETgKN_GPU_DBG_SHADER_TCS_END,
                                                    .m_uiTES = ETgKN_GPU_DBG_SHADER_TES_END,
                                                    .m_uiGS = ETgKN_GPU_DBG_SHADER_GS_END,
                                                    .m_uiTS = ETgKN_GPU_DBG_SHADER_TS_END,
                                                    .m_uiMS = ETgKN_GPU_DBG_SHADER_MS_END,
                                                    .m_uiFS = ETgKN_GPU_DBG_SHADER_FS_VWNC,
                                                    .m_bUnlit = true,
                                                    .m_uszName = u8"DEBUG GEOM 03",
                                                },
                                            };

STg2_KN_GPU_FONT                            g_sKN_GPU_STD_DOS_Font[ETgKN_GPU_DOS_FONT_ROM_COUNT] = {
                                                {
                                                    .m_uiFntX = 8,
                                                    .m_uiFntY = 8,
                                                    .m_uiBufX = TgARRAY_COUNT(g_uiKN_GPU_STD_DOS_Font_Default_Data),
                                                    .m_nuiGlyph = TgARRAY_COUNT( g_uiKN_GPU_STD_DOS_Font_Default_Data ) * 8 / (8*8),
                                                    .m_puiData = g_uiKN_GPU_STD_DOS_Font_Default_Data,
                                                    .m_uszName = u8"FONT DOS Default"
                                                },
                                                {
                                                    .m_uiFntX = 8,
                                                    .m_uiFntY = 8,
                                                    .m_uiBufX = TgARRAY_COUNT(g_uiKN_GPU_STD_DOS_Font_Future_Data),
                                                    .m_nuiGlyph = TgARRAY_COUNT(g_uiKN_GPU_STD_DOS_Font_Future_Data) * 8 / (8*8),
                                                    .m_puiData = g_uiKN_GPU_STD_DOS_Font_Future_Data,
                                                    .m_uszName = u8"FONT DOS Future"
                                                },
                                                {
                                                    .m_uiFntX = 8,
                                                    .m_uiFntY = 8,
                                                    .m_uiBufX = TgARRAY_COUNT(g_uiKN_GPU_STD_DOS_Font_Block_Data),
                                                    .m_nuiGlyph = TgARRAY_COUNT(g_uiKN_GPU_STD_DOS_Font_Block_Data) * 8 / (8*8),
                                                    .m_puiData = g_uiKN_GPU_STD_DOS_Font_Block_Data,
                                                    .m_uszName = u8"FONT DOS Block"
                                                },
                                                {
                                                    .m_uiFntX = 8,
                                                    .m_uiFntY = 16,
                                                    .m_uiBufX = TgARRAY_COUNT(g_uiKN_GPU_STD_DOS_Font_Marcio_Data),
                                                    .m_nuiGlyph = TgARRAY_COUNT(g_uiKN_GPU_STD_DOS_Font_Marcio_Data) * 8 / (8*16),
                                                    .m_puiData = g_uiKN_GPU_STD_DOS_Font_Marcio_Data,
                                                    .m_uszName = u8"FONT DOS Marcio"
                                                }
                                            };

                                            /* Single Quad used for rendering text, which is based instance rendering, position is used to scale the range of the font rect. */
STg2_KN_GPU_Vertex_UI_Text_C                g_sVertex_Strip_Text[4] = {
                                                {{{ 0.0F,  0.0F }}, {{ 0.0f, 0.0f }}}, {{{ 1.0F,  0.0F }}, {{ 1.0f, 0.0f }}}, // Top-left, Bottom-left
                                                {{{ 0.0F,  1.0F }}, {{ 0.0f, 1.0f }}}, {{{ 1.0F,  1.0F }}, {{ 1.0f, 1.0f }}}, // Top-right, Bottom-right
                                            };

                                            /* Single quad used for clearing the render target, position is used to scale the range of the input rect. */
STg2_KN_GPU_Vertex_UI_C                     g_sVertex_Strip_Quad[4] = {
                                                {{{ 0.0F,  0.0F }}, {{ 0.0f, 0.0f }}, {{ 1.0f, 1.0f, 1.0f, 1.0f }}}, // Top-left 
                                                {{{ 1.0F,  0.0F }}, {{ 1.0f, 0.0f }}, {{ 1.0f, 1.0f, 1.0f, 1.0f }}}, // Top-right
                                                {{{ 0.0F,  1.0F }}, {{ 0.0f, 1.0f }}, {{ 1.0f, 1.0f, 1.0f, 1.0f }}}, // Bottom-left
                                                {{{ 1.0F,  1.0F }}, {{ 1.0f, 1.0f }}, {{ 1.0f, 1.0f, 1.0f, 1.0f }}}, // Bottom-right
                                            };

                                            /** Single quad used for rendering a grey scale, This data copied from the Microsoft DirectX Graphics Samples (D3D12HDR), under the MIT License. */
STg2_KN_GPU_Vertex_UI_C                     g_sVertex_Strip_Gradient[4] = {
                                                {{{ 0.0F, 0.0F }}, {{ 0.0f, 0.0f }}, {{ 0.0f, 0.0f, 0.0f, 1.0f }}},
                                                {{{ 1.0F, 0.0F }}, {{ 1.0f, 0.0f }}, {{ 1.0f, 1.0f, 1.0f, 1.0f }}},
                                                {{{ 0.0F, 1.0F }}, {{ 0.0f, 1.0f }}, {{ 0.0f, 0.0f, 0.0f, 1.0f }}},
                                                {{{ 1.0F, 1.0F }}, {{ 1.0f, 1.0f }}, {{ 1.0f, 1.0f, 1.0f, 1.0f }}},
                                            };

                                            /* Triangle List Cube, where vertices are not shared, allowing for unique normals for each face. */
STg2_KN_GPU_Vertex_Geom_02_C                g_sVertex_List_Cube[36] = {
                                                {{{-0.5f,-0.5f,-0.5f, 1.f}}, {{-1.0f, 0.0f, 0.0f, 0.f}}},
                                                {{{-0.5f,-0.5f, 0.5f, 1.f}}, {{-1.0f, 0.0f, 0.0f, 0.f}}},
                                                {{{-0.5f, 0.5f, 0.5f, 1.f}}, {{-1.0f, 0.0f, 0.0f, 0.f}}},
                                                {{{-0.5f,-0.5f,-0.5f, 1.f}}, {{-1.0f, 0.0f, 0.0f, 0.f}}},
                                                {{{-0.5f, 0.5f, 0.5f, 1.f}}, {{-1.0f, 0.0f, 0.0f, 0.f}}},
                                                {{{-0.5f, 0.5f,-0.5f, 1.f}}, {{-1.0f, 0.0f, 0.0f, 0.f}}},
                                                {{{ 0.5f,-0.5f, 0.5f, 1.f}}, {{ 0.0f,-1.0f, 0.0f, 0.f}}},
                                                {{{-0.5f,-0.5f,-0.5f, 1.f}}, {{ 0.0f,-1.0f, 0.0f, 0.f}}},
                                                {{{ 0.5f,-0.5f,-0.5f, 1.f}}, {{ 0.0f,-1.0f, 0.0f, 0.f}}},
                                                {{{ 0.5f,-0.5f, 0.5f, 1.f}}, {{ 0.0f,-1.0f, 0.0f, 0.f}}},
                                                {{{-0.5f,-0.5f, 0.5f, 1.f}}, {{ 0.0f,-1.0f, 0.0f, 0.f}}},
                                                {{{-0.5f,-0.5f,-0.5f, 1.f}}, {{ 0.0f,-1.0f, 0.0f, 0.f}}},
                                                {{{ 0.5f, 0.5f,-0.5f, 1.f}}, {{ 0.0f, 0.0f,-1.0f, 0.f}}},
                                                {{{-0.5f,-0.5f,-0.5f, 1.f}}, {{ 0.0f, 0.0f,-1.0f, 0.f}}},
                                                {{{-0.5f, 0.5f,-0.5f, 1.f}}, {{ 0.0f, 0.0f,-1.0f, 0.f}}},
                                                {{{ 0.5f, 0.5f,-0.5f, 1.f}}, {{ 0.0f, 0.0f,-1.0f, 0.f}}},
                                                {{{ 0.5f,-0.5f,-0.5f, 1.f}}, {{ 0.0f, 0.0f,-1.0f, 0.f}}},
                                                {{{-0.5f,-0.5f,-0.5f, 1.f}}, {{ 0.0f, 0.0f,-1.0f, 0.f}}},
                                                {{{ 0.5f, 0.5f, 0.5f, 1.f}}, {{ 1.0f, 0.0f, 0.0f, 0.f}}},
                                                {{{ 0.5f,-0.5f,-0.5f, 1.f}}, {{ 1.0f, 0.0f, 0.0f, 0.f}}},
                                                {{{ 0.5f, 0.5f,-0.5f, 1.f}}, {{ 1.0f, 0.0f, 0.0f, 0.f}}},
                                                {{{ 0.5f,-0.5f,-0.5f, 1.f}}, {{ 1.0f, 0.0f, 0.0f, 0.f}}},
                                                {{{ 0.5f, 0.5f, 0.5f, 1.f}}, {{ 1.0f, 0.0f, 0.0f, 0.f}}},
                                                {{{ 0.5f,-0.5f, 0.5f, 1.f}}, {{ 1.0f, 0.0f, 0.0f, 0.f}}},
                                                {{{ 0.5f, 0.5f, 0.5f, 1.f}}, {{ 0.0f, 1.0f, 0.0f, 0.f}}},
                                                {{{ 0.5f, 0.5f,-0.5f, 1.f}}, {{ 0.0f, 1.0f, 0.0f, 0.f}}},
                                                {{{-0.5f, 0.5f,-0.5f, 1.f}}, {{ 0.0f, 1.0f, 0.0f, 0.f}}},
                                                {{{ 0.5f, 0.5f, 0.5f, 1.f}}, {{ 0.0f, 1.0f, 0.0f, 0.f}}},
                                                {{{-0.5f, 0.5f,-0.5f, 1.f}}, {{ 0.0f, 1.0f, 0.0f, 0.f}}},
                                                {{{-0.5f, 0.5f, 0.5f, 1.f}}, {{ 0.0f, 1.0f, 0.0f, 0.f}}},
                                                {{{-0.5f, 0.5f, 0.5f, 1.f}}, {{ 0.0f, 0.0f, 1.0f, 0.f}}},
                                                {{{-0.5f,-0.5f, 0.5f, 1.f}}, {{ 0.0f, 0.0f, 1.0f, 0.f}}},
                                                {{{ 0.5f,-0.5f, 0.5f, 1.f}}, {{ 0.0f, 0.0f, 1.0f, 0.f}}},
                                                {{{ 0.5f, 0.5f, 0.5f, 1.f}}, {{ 0.0f, 0.0f, 1.0f, 0.f}}},
                                                {{{-0.5f, 0.5f, 0.5f, 1.f}}, {{ 0.0f, 0.0f, 1.0f, 0.f}}},
                                                {{{ 0.5f,-0.5f, 0.5f, 1.f}}, {{ 0.0f, 0.0f, 1.0f, 0.f}}},
                                            };

/*# defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
#endif




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal State | Debug Data                                                                                                                                                    */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- Stat --------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if TgS_STAT__KERNEL || TgS_DEBUG__KERNEL

TgUINT_E32                                  g_uiKN_Stats_Loaded_Mesh_Vertex; /* #IMPLEMENT */
TgUINT_E32                                  g_uiKN_Stats_Loaded_Mesh_Face; /* #IMPLEMENT */
TgRSIZE                                     g_uiKN_Stats_Memory_Buffer; /* #IMPLEMENT */
TgRSIZE                                     g_uiKN_Stats_Memory_Mesh; /* #IMPLEMENT */
TgRSIZE                                     g_uiKN_Stats_Memory_Mesh_Collision; /* #IMPLEMENT */

/*# TgS_STAT__KERNEL || TgS_DEBUG__KERNEL */
#endif


/* ---- Debug -------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if TgS_DEBUG__KERNEL

/*# TgS_DEBUG__KERNEL */
#endif


/* ---- tgKN_GPU_Query_Fixed_Memory ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRSIZE tgKN_GPU_Query_Fixed_Memory( TgVOID )
{
    return ( 0
             + sizeof( g_tiCVAR_KN_GPU_Physical_Device )
             + sizeof( g_tiCVAR_KN_GPU_Output )
             + sizeof( g_tiCVAR_KN_GPU_Width )
             + sizeof( g_tiCVAR_KN_GPU_Height )
             + sizeof( g_tiCVAR_KN_GPU_Refresh_Rate )
             + sizeof( g_tiCVAR_KN_GPU_ScanOut_HDR )
             + sizeof( g_szKN_GPU_Physical_Device )
             + sizeof( g_szKN_GPU_Output )
             + sizeof( g_uiKN_GPU_Width )
             + sizeof( g_uiKN_GPU_Height )
             + sizeof( g_uiKN_GPU_Refresh_Rate )
             + sizeof( g_bKN_GPU_ScanOut_HDR )

             + sizeof( g_sKN_GPU_CXT_HOST_EXTN )
             + sizeof( g_sKN_GPU_CXT_HOST )
             + sizeof( g_asKN_GPU_CXT_DEVC )
             + sizeof( g_sKN_GPU_CXT_DEVC_Free_Stack )
             + sizeof( g_asKN_GPU_CXT_EXEC )
             + sizeof( g_sKN_GPU_CXT_EXEC_Free_Stack )
             + sizeof( g_asKN_GPU_CXT_SWAP )
             + sizeof( g_sKN_GPU_CXT_SWAP_Free_Stack )

             + tgKN_GPU_VS_Query_Fixed_Memory()
             + tgKN_GPU_TCS_Query_Fixed_Memory()
             + tgKN_GPU_TES_Query_Fixed_Memory()
             + tgKN_GPU_GS_Query_Fixed_Memory()
             + tgKN_GPU_TS_Query_Fixed_Memory()
             + tgKN_GPU_MS_Query_Fixed_Memory()
             + tgKN_GPU_FS_Query_Fixed_Memory()
             + tgKN_GPU_CS_Query_Fixed_Memory()

             + tgKN_GPU_TX_CBE_Query_Fixed_Memory()
             + tgKN_GPU_TX_IMG_Query_Fixed_Memory()
             + tgKN_GPU_TX_VOL_Query_Fixed_Memory()

         #if TgS_STAT__KERNEL || TgS_DEBUG__KERNEL
             +sizeof( g_uiKN_Stats_Loaded_Mesh_Vertex ) /* #IMPLEMENT */
             + sizeof( g_uiKN_Stats_Loaded_Mesh_Face ) /* #IMPLEMENT */
             + sizeof( g_uiKN_Stats_Memory_Buffer ) /* #IMPLEMENT */
             + sizeof( g_uiKN_Stats_Memory_Mesh ) /* #IMPLEMENT */
             + sizeof( g_uiKN_Stats_Memory_Mesh_Collision ) /* #IMPLEMENT */
         /*# TgS_STAT__KERNEL || TgS_DEBUG__KERNEL */
         #endif
    );
}


/*# defined (ENABLE_RELOAD_GUARD) */
#else

T(TgKN_GPU_,_ID_A)                          T(g_axsKN_Lib_,_Ref_Singleton)[T(KTgKN_GPU_MAX_,)];
T(STg2_KN_GPU_,_DATA)                       T(g_asKN_Lib_,_Data)[T(KTgKN_GPU_MAX_,)];
STg2_UT_LF_ISO__ST                          T(g_sKN_Lib_,);
STg2_UT_LF_ISO__SN                          T(g_sKN_Lib_,_Lock);
TgUINT_E64_A                                T(g_xnuiKN_Lib_,_Init);

#if defined(MACRO_BUILD_TEXTURE)
T(TgKN_GPU_,_INST_ID_A)                     T(g_axsCXT_,_Inst_Ref_Singleton)[KTgKN_GPU_MAX_EXEC_CONTEXT][T(KTgKN_GPU_MAX_,_INST)];
T(TgKN_GPU_,_ID)                            T(g_asCXT_,)[KTgKN_GPU_MAX_EXEC_CONTEXT][T(KTgKN_GPU_MAX_,_INST)];
STg2_UT_LF_ISO__ST_Unaligned                T(g_sCXT_,_Inst)[KTgKN_GPU_MAX_EXEC_CONTEXT];
STg2_UT_LF_ISO__SN                          T(g_sCXT_,_Inst_Lock)[KTgKN_GPU_MAX_EXEC_CONTEXT];
/*# defined(MACRO_BUILD_TEXTURE) */
#endif

#if TgS_STAT__KERNEL || TgS_DEBUG__KERNEL
TgRSIZE                                     T(g_uiKN_Size_GPU_,)[T(KTgKN_GPU_MAX_,)];
TgRSIZE                                     T(g_uiKN_Size_GPU_,_Total);
/*# TgS_STAT__KERNEL || TgS_DEBUG__KERNEL */
#endif

#if TgS_DEBUG__KERNEL
TgCHAR_U8                                   T(g_szKN_GPU_,)[T(KTgKN_GPU_MAX_,)][KTgMAX_FILE_NAME];
/*# TgS_DEBUG__KERNEL */
#endif

/* ---- (tgKN_GPU_,_Query_Fixed_Memory) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRSIZE T(tgKN_GPU_,_Query_Fixed_Memory)( TgVOID )
{
    return ( 0
             + sizeof( T(g_axsKN_Lib_,_Ref_Singleton ) )
             + sizeof( T(g_asKN_Lib_,_Data ) )
             + sizeof( T(g_sKN_Lib_, ) )
             + sizeof( T(g_sKN_Lib_,_Lock ) )
             + sizeof( T(g_xnuiKN_Lib_,_Init ) )

        #if defined(MACRO_BUILD_TEXTURE)
             + sizeof( T(g_axsCXT_,_Inst_Ref_Singleton ) )
             + sizeof( T(g_asCXT_, ) )
             + sizeof( T(g_sCXT_,_Inst ) )
             + sizeof( T(g_sCXT_,_Inst_Lock ) )
        /*# defined(MACRO_BUILD_TEXTURE) */
        #endif

        #if TgS_STAT__KERNEL || TgS_DEBUG__KERNEL
             + sizeof( T(g_uiKN_Size_GPU_,) )
        /*# TgS_STAT__KERNEL || TgS_DEBUG__KERNEL */
        #endif

        #if TgS_DEBUG__KERNEL
             + sizeof( T(g_szKN_GPU_,) )
        /*# TgS_DEBUG__KERNEL */
        #endif
    );
}


/* =============================================================================================================================================================================== */

/*# !defined (ENABLE_RELOAD_GUARD) */
#endif
