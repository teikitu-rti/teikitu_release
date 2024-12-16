/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Effect - Internal - Data.h
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.20 | »GUID« DE461472-5528-4A5B-A7F4-09CCAD73387B */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_EFFECT_INTERNAL_DATA_H)
#if !defined (ENABLE_RELOAD_GUARD)


/* == Effects ==================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Data                                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

                                            /* Configuration Values */
TgEXTN TgFLOAT32                            g_fFX_Quality_Setting;
TgEXTN TgCN_VAR_ID                          g_tiFX_CN__Quality_Setting;
TgEXTN TgFLOAT32                            g_fFX_Alpha_Threshold;
TgEXTN TgCN_VAR_ID                          g_tiFX_CN__Alpha_Threshold;
TgEXTN TgRSIZE                              g_uiFX_Decal_Memory_Max;
TgEXTN TgCN_VAR_ID                          g_tiFX_CN__Decal_Memory_Max;
TgEXTN TgFLOAT32                            g_fFX_Decal_Normal_Threshold;
TgEXTN TgCN_VAR_ID                          g_tiFX_CN__Decal_Normal_Threshold;
TgEXTN TgRSIZE                              g_uiFX_Emitter_Memory_Max;
TgEXTN TgCN_VAR_ID                          g_tiFX_CN__Emitter_Memory_Max;

                                            /* Synchronization Fences */
TgEXTN TgRSIZE_A                            g_xuiFX_Fence__TO_CLIENT__COMMAND_QUEUE_FULL;
TgEXTN TgRSIZE_A                            g_xuiFX_Fence__CLIENT_TO_UPDATE__COMMAND_QUEUE_FULL;
TgEXTN TgRSIZE_A                            g_xuiFX_FENCE__UPDATE;
TgEXTN TgRSIZE_A                            g_xuiFX_FENCE__UPDATE__UPDATE;
TgEXTN TgRSIZE_A                            g_xuiFX_FENCE__UPDATE__FINISH;
TgEXTN TgRSIZE_A                            g_xuiFX_FENCE__SCENE;
TgEXTN TgRSIZE_A                            g_xuiFX_FENCE__SCENE__REFRESH_BA;
TgEXTN TgRSIZE_A                            g_xuiFX_FENCE__SCENE__CULL;
TgEXTN TgRSIZE_A                            g_xuiFX_FENCE__SCENE__FINISH;
TgEXTN TgRSIZE_A                            g_xuiFX_FENCE__RENDER;
TgEXTN TgRSIZE_A                            g_xuiFX_FENCE__RENDER__PROCESS_HEADERS;
TgEXTN TgRSIZE_A                            g_xuiFX_FENCE__RENDER__ALLOCATE;
TgEXTN TgRSIZE_A                            g_xuiFX_FENCE__RENDER__GENERATE;

                                            /* Effect System Constants */
TgEXTN STg2_FX_Descriptor_P                 g_apsFX_Descriptor[ETgFX__EFFECT_MAX];
TgEXTN TgUINT_E32_C                         g_uiFX_Command_Size[ETgFX_COMMAND__MAX + 1];

#if defined(TgBUILD_FEATURE__GRAPHICS_VFX)
                                            /* Render */
TgEXTN STg2_RN_Particle_Header              g_asParticle_Header[(TgSINT_E32)KTgFX_MAX_RENDER_INSTANCE * (TgSINT_E32)ETgFX_MAX_HEADER_INDEX];
TgEXTN TgUINT_E32                           g_uiParticle_Header_Index;
TgEXTN STg2_Job                             g_sFX__Job__Render__Allocate_Render_Buffers;
/*# defined(TgBUILD_FEATURE__GRAPHICS_VFX) */
#endif

                                            /* Shared Effect Object / State */
TgEXTN TgSINT_E32                           g_aiFX__Client__Shared_State[KTgFX_MAX_EFFECT_INSTANCE];
TgEXTN STg2_UT_LF_ISO__ST                   g_sFX_Effect__Client__Effect;
TgEXTN STg2_FX__Client                      g_asFX_Effect[KTgFX_MAX_EFFECT_INSTANCE];

TgEXTN TgFX_CLIENT_INST_ID                  g_atiFX__Client__Update__Head[ETgFX_UPDATE__MAX];
TgEXTN TgSINT_E32                           g_niFX__Client__Update__Active;

                                            /* Default Resources */
TgEXTN TgFX_EFFECT_ID                       g_tiFX_File_Default;
TgEXTN TgFX_EFFECT_ID                       g_tiFX_File_Error;

                                            /* Cache System */
TgEXTN TgUINT_MAX                           g_auiFX_KN_File__Effect_Hash[ETgFX_DATA__EFFECT_MAX];
TgEXTN STg2_FX_Data__Effect                 g_asFX_KN_File__Effect[ETgFX_DATA__EFFECT_MAX];
TgEXTN STg2_FX_Data__Data                   g_asFX_Cache__Effect[ETgFX_DATA__EFFECT_MAX];

                                            /* Decal Memory */
TgEXTN TgRSIZE_A                            g_xuiFX__Decal__Memory_Current;

                                            /* Emitter Memory */
TgEXTN TgRSIZE_A                            g_xuiFX__Emitter__Memory_Current;

                                            /* Group */
TgEXTN TgFX_CLIENT_INST_ID_C                KTgFX_CLIENT_INST_ID__GROUP_DELAYED_SPAWN;

#if defined(TgS_DEBUG__EFFECT) && TgS_DEBUG__EFFECT
                                            /* Visualization */
TgEXTN TgCN_VAR_ID                          g_tiFX_Debug__OSD__Profile_Enable;
TgEXTN TgCN_VAR_ID                          g_tiFX_Debug__OSD__Profile_Sort;

TgEXTN TgCN_VAR_ID                          g_tiFX_Debug__Draw_BA;
TgEXTN TgCN_VAR_ID                          g_tiFX_Debug__Draw_Emitter;

                                            /* Execution Debug / Troubleshooting Update */
TgEXTN TgCN_VAR_ID                          g_tiFX_Debug__Disable_Module;
TgEXTN TgCN_VAR_ID                          g_tiFX_Debug__Disable_Update;
TgEXTN TgCN_VAR_ID                          g_tiFX_Debug__Disable_Render;
TgEXTN TgCN_VAR_ID                          g_tiFX_Debug__Disable_Render_Buffer;

                                            /* Execution Debug / Troubleshooting Rendering */
TgEXTN TgCN_VAR_ID                          g_tiFX_Debug__Disable_Cull_On_Spawn;
TgEXTN TgCN_VAR_ID                          g_tiFX_Debug__Disable_Cull_On_Render;

                                            /* Cache File System */
TgEXTN TgCHAR_U8                            g_aszFX_Cache__EFfect_Name[ETgFX_DATA__EFFECT_MAX][32];

/*# defined(TgS_DEBUG__EFFECT) && TgS_DEBUG__EFFECT */
#endif


#define __PARENT_FILE__ "TgS Effect - Internal - Data.h"
#define ENABLE_RELOAD_GUARD
#include "TgS EFFECT/TgS Effect - Effect [INC].h"
#undef ENABLE_RELOAD_GUARD
#undef __PARENT_FILE__

#define TGS_EFFECT_INTERNAL_DATA_H

/*# defined (ENABLE_RELOAD_GUARD) */
#else

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Generic Data                                                                                                                                                                   */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgEXTN ETgFX_EFFECT_STATE                   T_NAME(g_aenFX__,__Shared__State)[T_TYPE(KTgFX_MAX_,)];
TgEXTN STg2_UT_LF_ISO__ST                   T_NAME(g_sFX__,__Client__Stack);
TgEXTN T_NAME(STg2_FX__,)                   T_NAME(g_asFX__,)[T_TYPE(KTgFX_MAX_,)];
TgEXTN STg2_FX_Descriptor                   T_NAME(g_sFX_Descriptor__,);
TgEXTN TgUINT_E32                           T_NAME(g_uiFX__,__Shared__Notify_State);

#if T_EFFECT_UPDATE || T_EFFECT_RENDER
TgEXTN TgUINT_E08                           T_NAME(g_asFX_Command__,__ToClient)[ETgFX_COMMAND__TO_CLIENT__BYTE_MAX];
TgEXTN TgRSIZE_A                            T_NAME(g_xuiFX_Command__,__ToClient_Offset);
/*# T_EFFECT_UPDATE || T_EFFECT_RENDER */
#endif

#if T_EFFECT_UPDATE
TgEXTN TgRSIZE_A                            T_TYPE(g_xuiFX_FENCE__UPDATE__UPDATE__,);
TgEXTN TgRSIZE_A                            T_TYPE(g_axuiFX_FENCE__UPDATE__UPDATE__,)[ETgFX_UPDATE__MAX];
TgEXTN TgRSIZE_A                            T_TYPE(g_xuiFX_FENCE__UPDATE__FINISH__,);

TgEXTN TgFX_DATA_INST_ID                    T_NAME(g_atiFX__,__Update__Head)[ETgFX_UPDATE__MAX]; /* Array of FX entities to be updated. */
TgEXTN TgSINT_E32                           T_NAME(g_niFX__,__Update__Active);

TgEXTN STg2_Job                             T_NAME(g_sFX__Job__,__Update)[ETgFX_UPDATE__MAX];
TgEXTN STg2_Job                             T_NAME(g_sFX__Job__,__Update__Update_Finish);
TgEXTN STg2_Job                             T_NAME(g_sFX__Job__,__Update__Process_ClientToUpdate);
TgEXTN TgRSIZE_A                            T_NAME(g_xuiFX_Command__,__Update_Command_Offset);
TgEXTN TgRSIZE_A                            T_NAME(g_xuiFX_Command__,__ClientToUpdate_Offset);
TgEXTN TgUINT_E08                           T_NAME(g_asFX_Command__,__Update_Command_Buffer)[ETgFX_COMMAND__CLIENT_TO_UPDATE__BYTE_MAX];
TgEXTN TgUINT_E08                           T_NAME(g_asFX_Command__,__ClientToUpdate)[ETgFX_COMMAND__CLIENT_TO_UPDATE__BYTE_MAX];
/*# T_EFFECT_UPDATE */
#endif

#if T_EFFECT_SCENE

TgEXTN TgRSIZE_A                            T_TYPE(g_xuiFX_FENCE__SCENE__REFRESH_BA__,);
TgEXTN TgRSIZE_A                            T_TYPE(g_axuiFX_FENCE__SCENE__REFRESH_BA__,)[ETgFX_UPDATE__MAX];

TgEXTN STg2_Job                             T_NAME(g_asFX__Scene__Job__,_Refresh_BA)[ETgFX_UPDATE__MAX];

#if T_EFFECT_RENDER
TgEXTN TgRSIZE_A                            T_TYPE(g_xuiFX_FENCE__SCENE__CULL__,);
TgEXTN TgRSIZE_A                            T_TYPE(g_axuiFX_FENCE__SCENE__CULL__,)[ETgFX_UPDATE__MAX];
TgEXTN TgRSIZE_A                            T_TYPE(g_xuiFX_FENCE__SCENE__FINISH__,);

TgEXTN STg2_Job                             T_NAME(g_asFX__Scene__Job__,_Cull)[ETgFX_UPDATE__MAX];
TgEXTN STg2_Job                             T_NAME(g_sFX__Scene__Job__,_Finish);

TgEXTN TgRSIZE_A                            T_NAME(g_nbyFX__,__Scene__Particle_Memory); /* Amount of memory needed for the CPU Particle Buffer */

TgEXTN TgFX_DATA_INST_ID                    T_NAME(g_atiFX__,__Scene__Particle_Head)[ETgFX_UPDATE__MAX]; /* Array of FX entities to be rendered into a CPU particle buffer. */
TgEXTN TgRSIZE                              T_NAME(g_anuiFX__,__Scene__Particle_Active)[ETgFX_UPDATE__MAX];
TgEXTN TgFX_DATA_INST_ID                    T_NAME(g_atiFX__,__Scene__Mesh_Head)[ETgFX_UPDATE__MAX]; /* Array of FX entities that will render a mesh object (GPU vertex buffer). */
TgEXTN TgRSIZE                              T_NAME(g_anuiFX__,__Scene__Mesh_Active)[ETgFX_UPDATE__MAX];
TgEXTN TgFX_DATA_INST_ID                    T_NAME(g_atiFX__,__Scene__Culled_Head)[ETgFX_UPDATE__MAX]; /* Array of FX entities that were culled out from the scene. */
TgEXTN TgSINT_E32                           T_NAME(g_aniFX__,__Scene__Culled)[ETgFX_UPDATE__MAX];
/*# T_EFFECT_RENDER */
#else
TgEXTN TgFX_DATA_INST_ID                    T_NAME(g_atiFX__,__Scene__Effect_Head)[ETgFX_UPDATE__MAX];
TgEXTN TgSINT_E32                           T_NAME(g_niFX__,__Scene__Effect_Active);
/*# T_EFFECT_RENDER */
#endif

/*# T_EFFECT_SCENE */
#endif

#if T_EFFECT_RENDER
TgEXTN TgRSIZE_A                            T_TYPE(g_xuiFX_FENCE__RENDER__PROCESS_HEADERS__,);
TgEXTN TgRSIZE_A                            T_TYPE(g_axuiFX_FENCE__RENDER__PROCESS_HEADERS__,)[ETgFX_UPDATE__MAX];
TgEXTN TgRSIZE_A                            T_TYPE(g_xuiFX_FENCE__RENDER__GENERATE__,);

TgEXTN TgFX_DATA_INST_ID                    T_NAME(g_atiFX__,__Render_Header__Head)[ETgFX_UPDATE__MAX]; /* Array of FX Headers for VFX to be rendered. */
TgEXTN TgSINT_E32                           T_NAME(g_niFX__,__Render_Header__Active);
TgEXTN TgFX_DATA_INST_ID                    T_NAME(g_tiFX__,__Render_Generate__Head);
TgEXTN TgSINT_E32                           T_NAME(g_niFX__,__Render_Generate__Active);

TgEXTN STg2_Job                             T_NAME(g_asFX__Render__Job__,_Process_Headers)[ETgFX_UPDATE__MAX];
TgEXTN STg2_Job                             T_NAME(g_sFX__Render__Job__,_Render_Generate);
TgEXTN STg2_Job                             T_NAME(g_sFX__Job__,__Scene__Cull)[ETgFX_UPDATE__MAX];
TgEXTN STg2_Job                             T_NAME(g_sFX__Job__,__Render__Process_SceneToRender);
TgEXTN STg2_Job                             T_NAME(g_sFX__Job__,__Render__Generate);

TgEXTN TgRSIZE_A                            T_NAME(g_xuiFX_Command__,__SceneToRender_Offset);
TgEXTN TgUINT_E08                           T_NAME(g_asFX_Command__,__SceneToRender)[ETgFX_COMMAND__SCENE_TO_RENDER__BYTE_MAX];
/*# T_EFFECT_RENDER */
#endif


/* =============================================================================================================================================================================== */

/*# defined (ENABLE_RELOAD_GUARD) */
#endif

/*# !defined(TGS_EFFECT_INTERNAL_DATA_H) */
#endif
