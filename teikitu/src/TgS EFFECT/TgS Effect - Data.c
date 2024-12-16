/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Effect - Data.c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.12 | »GUID« 964CB1A6-814D-4E19-8E67-A83FCA98BF05 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined (ENABLE_RELOAD_GUARD)


/* == Effects ==================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Type Validation                                                                                                                                                                */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

//CLANG_WARN_DISABLE_PUSH(extended-offsetof)
TgCOMPILER_ASSERT( sizeof( TgUINT_F32  ) == sizeof( ETgFX_COMMAND ), 0 );
TgCOMPILER_ASSERT( sizeof( TgUINT_F64  ) == sizeof( TgFX_DATA_INST_ID ), 0 );
TgCOMPILER_ASSERT( sizeof( TgUINT_F64  ) == sizeof( TgFX_CLIENT_INST_ID ), 0 );
TgCOMPILER_ASSERT( ETgFX_COMMAND__MAX < 0xFF, 0 );
TgCOMPILER_ASSERT( offsetof( STg2_FX_Command__Update__NoParam, m_sDest.m_tiData ) == offsetof( STg2_FX_Command__Update__1_S32, m_sDest.m_tiData ), 0 );
TgCOMPILER_ASSERT( offsetof( STg2_FX_Command__Update__NoParam, m_sDest.m_tiData ) == offsetof( STg2_FX_Command__Update__1_F32, m_sDest.m_tiData ), 0 );
TgCOMPILER_ASSERT( offsetof( STg2_FX_Command__Update__NoParam, m_sDest.m_tiData ) == offsetof( STg2_FX_Command__Update__1_F32_04, m_sDest.m_tiData ), 0 );
TgCOMPILER_ASSERT( offsetof( STg2_FX_Command__Update__NoParam, m_sDest.m_tiData ) == offsetof( STg2_FX_Command__Update__2_F32_04, m_sDest.m_tiData ), 0 );
TgCOMPILER_ASSERT( offsetof( STg2_FX_Command__Update__NoParam, m_sDest.m_tiData ) == offsetof( STg2_FX_Command__Update__1_UXX, m_sDest.m_tiData ), 0 );
TgCOMPILER_ASSERT( offsetof( STg2_FX_Command__Update__NoParam, m_sDest.m_tiData ) == offsetof( STg2_FX_Command__Update__2_UXX, m_sDest.m_tiData ), 0 );
//CLANG_WARN_DISABLE_POP(extended-offsetof)




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  System ID                                                                                                                                                                      */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgKI_DEFINE( FX_CLIENT_INST_ID );
TgKI_DEFINE( FX_DATA_INST_ID );
TgKI_DEFINE( FX_EFFECT_ID );
TgKI_DEFINE( FX_CACHE_ID );
TgFX_CLIENT_INST_ID_C KTgFX_CLIENT_INST_ID__GROUP_DELAYED_SPAWN = { ~0LL + 1LL };




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Profile Markers                                                                                                                                                                */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

PROFILE_DEFINE( FX_COMMANDS__CLIENT );
PROFILE_ARRAY_DEFINE( ETgFX_UPDATE__MAX + 1, FX_UPDATE__UPDATE );
PROFILE_DEFINE( FX_RENDER_PATCH_CONTEXT );
PROFILE_DEFINE( FX_RENDER_PROCESS_COMMANDS );
PROFILE_DEFINE( FX_RENDER_GENERATE );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Data                                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgFLOAT32                                   g_fFX_Quality_Setting;
TgCN_VAR_ID                                 g_tiFX_CN__Quality_Setting;
TgFLOAT32                                   g_fFX_Alpha_Threshold;
TgCN_VAR_ID                                 g_tiFX_CN__Alpha_Threshold;
TgRSIZE                                     g_uiFX_Decal_Memory_Max;
TgCN_VAR_ID                                 g_tiFX_CN__Decal_Memory_Max;
TgFLOAT32                                   g_fFX_Decal_Normal_Threshold;
TgCN_VAR_ID                                 g_tiFX_CN__Decal_Normal_Threshold;
TgRSIZE                                     g_uiFX_Emitter_Memory_Max;
TgCN_VAR_ID                                 g_tiFX_CN__Emitter_Memory_Max;

TgRSIZE_A                                   g_xuiFX_Fence__TO_CLIENT__COMMAND_QUEUE_FULL;
TgRSIZE_A                                   g_xuiFX_Fence__CLIENT_TO_UPDATE__COMMAND_QUEUE_FULL;
TgRSIZE_A                                   g_xuiFX_FENCE__UPDATE;
TgRSIZE_A                                   g_xuiFX_FENCE__UPDATE__UPDATE;
TgRSIZE_A                                   g_xuiFX_FENCE__UPDATE__FINISH;
TgRSIZE_A                                   g_xuiFX_FENCE__SCENE;
TgRSIZE_A                                   g_xuiFX_FENCE__SCENE__REFRESH_BA;
TgRSIZE_A                                   g_xuiFX_FENCE__SCENE__CULL;
TgRSIZE_A                                   g_xuiFX_FENCE__SCENE__FINISH;
TgRSIZE_A                                   g_xuiFX_FENCE__RENDER;
TgRSIZE_A                                   g_xuiFX_FENCE__RENDER__PROCESS_HEADERS;
TgRSIZE_A                                   g_xuiFX_FENCE__RENDER__ALLOCATE;
TgRSIZE_A                                   g_xuiFX_FENCE__RENDER__GENERATE;

STg2_FX_Descriptor_P                        g_apsFX_Descriptor[ETgFX__EFFECT_MAX];
TgUINT_F32_C                                g_uiFX_Command_Size[ETgFX_COMMAND__MAX + 1] =
                                            {
                                                sizeof( STg2_FX_Command__Notify ),            /* ETgFX_COMMAND__CLIENT_TO_UPDATE__NOTIFY */
                                                sizeof( STg2_FX_Command__Update__Create ),    /* ETgFX_COMMAND__CLIENT_TO_UPDATE__CREATE */
                                                sizeof( STg2_FX_Command__Update__NoParam ),   /* ETgFX_COMMAND__CLIENT_TO_UPDATE__KILL */
                                                sizeof( STg2_FX_Command__Update__NoParam ),   /* ETgFX_COMMAND__CLIENT_TO_UPDATE__STOP */
                                                sizeof( STg2_FX_Command__Update__1_F32_04 ),  /* ETgFX_COMMAND__CLIENT_TO_UPDATE__POSITION_SET */
                                                sizeof( STg2_FX_Command__Update__1_F32_04 ),  /* ETgFX_COMMAND__CLIENT_TO_UPDATE__POSITION_UPDATE_FROM_PARENT */
                                                sizeof( STg2_FX_Command__Update__1_F32_04 ),  /* ETgFX_COMMAND__CLIENT_TO_UPDATE__ROTATION_SET */
                                                sizeof( STg2_FX_Command__Update__1_F32_04 ),  /* ETgFX_COMMAND__CLIENT_TO_UPDATE__ROTATION_UPDATE_FROM_PARENT */
                                                sizeof( STg2_FX_Command__Update__1_F32 ),     /* ETgFX_COMMAND__CLIENT_TO_UPDATE__SPIN */
                                                sizeof( STg2_FX_Command__Update__1_UXX ),     /* ETgFX_COMMAND__CLIENT_TO_UPDATE__VISIBLE */
                                                sizeof( STg2_FX_Command__Update__1_S32 ),     /* ETgFX_COMMAND__SCENE_TO_RENDER__PATCH_CONTEXT */
                                                sizeof( STg2_FX_Command__Client__Create ),    /* ETgFX_COMMAND__UPDATE_TO_CLIENT__CREATE */
                                                sizeof( STg2_FX_Command__Client__Free ),      /* ETgFX_COMMAND__UPDATE_TO_CLIENT__FREE */
                                                sizeof( STg2_FX_Command__Notify ),            /* ETgFX_COMMAND__UPDATE_TO_CLIENT__NOTIFY */
                                                KTgMAX_U32
                                            };

#if defined(TgBUILD_FEATURE__GRAPHICS_VFX)
STg2_RN_Particle_Header                     g_asParticle_Header[(TgSINT_E32)KTgFX_MAX_RENDER_INSTANCE * (TgSINT_E32)ETgFX_MAX_HEADER_INDEX];
TgUINT_F32                                  g_uiParticle_Header_Index;
STg2_Job                                    g_sFX__Job__Render__Allocate_Render_Buffers;
/*# defined(TgBUILD_FEATURE__GRAPHICS_VFX) */
#endif

TgSINT_F32                                  g_aiFX__Client__Shared_State[KTgFX_MAX_EFFECT_INSTANCE];
STg2_UT_LF_ISO__ST                          g_sFX_Effect__Client__Effect;
STg2_FX__Client                             g_asFX_Effect[KTgFX_MAX_EFFECT_INSTANCE];

TgFX_CLIENT_INST_ID                         g_atiFX__Client__Update__Head[ETgFX_UPDATE__MAX];
TgSINT_F32                                  g_niFX__Client__Update__Active;

TgFX_EFFECT_ID                              g_tiFX_File_Default;
TgFX_EFFECT_ID                              g_tiFX_File_Error;

TgUINT_MAX                                  g_auiFX_KN_File__Effect_Hash[ETgFX_DATA__EFFECT_MAX];
STg2_FX_Data__Effect                        g_asFX_KN_File__Effect[ETgFX_DATA__EFFECT_MAX];
STg2_FX_Data__Data                          g_asFX_Cache__Effect[ETgFX_DATA__EFFECT_MAX];

TgRSIZE_A                                   g_xuiFX__Decal__Memory_Current;
TgRSIZE_A                                   g_xuiFX__Emitter__Memory_Current;

#if TgS_DEBUG__EFFECT
TgCN_VAR_ID                                 g_tiFX_Debug__OSD__Profile_Enable;
TgCN_VAR_ID                                 g_tiFX_Debug__OSD__Profile_Sort;

TgCN_VAR_ID                                 g_tiFX_Debug__Draw_BA;
TgCN_VAR_ID                                 g_tiFX_Debug__Draw_Emitter;
TgCN_VAR_ID                                 g_tiFX_Debug__Emitter__Draw_Debug_Colour;

TgCN_VAR_ID                                 g_tiFX_Debug__Disable_Module;
TgCN_VAR_ID                                 g_tiFX_Debug__Disable_Update;
TgCN_VAR_ID                                 g_tiFX_Debug__Disable_Render;
TgCN_VAR_ID                                 g_tiFX_Debug__Disable_Render_Buffer;

TgCN_VAR_ID                                 g_tiFX_Debug__Disable_Cull_On_Spawn;
TgCN_VAR_ID                                 g_tiFX_Debug__Disable_Cull_On_Render;

TgCHAR_U8                                   g_aszFX_Cache__EFfect_Name[ETgFX_DATA__EFFECT_MAX][32];
/*# TgS_DEBUG__EFFECT */
#endif


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Generic Data                                                                                                                                                                   */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

#define __PARENT_FILE__ "TgS Effect - Data.c"
#define ENABLE_RELOAD_GUARD
#include "TgS EFFECT/TgS Effect - Effect [INC].h"
#undef ENABLE_RELOAD_GUARD
#undef __PARENT_FILE__


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgFX_Query_Fixed_Memory -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRSIZE tgFX_Query_Fixed_Memory( TgVOID )
{
    return (0
           + sizeof( g_fFX_Quality_Setting )
           + sizeof( g_tiFX_CN__Quality_Setting )
           + sizeof( g_fFX_Alpha_Threshold )
           + sizeof( g_tiFX_CN__Alpha_Threshold )
           + sizeof( g_uiFX_Decal_Memory_Max )
           + sizeof( g_tiFX_CN__Decal_Memory_Max )
           + sizeof( g_fFX_Decal_Normal_Threshold )
           + sizeof( g_tiFX_CN__Decal_Normal_Threshold )
           + sizeof( g_uiFX_Emitter_Memory_Max )
           + sizeof( g_tiFX_CN__Emitter_Memory_Max )

           + sizeof( g_xuiFX_Fence__TO_CLIENT__COMMAND_QUEUE_FULL )
           + sizeof( g_xuiFX_Fence__CLIENT_TO_UPDATE__COMMAND_QUEUE_FULL )
           + sizeof( g_xuiFX_FENCE__UPDATE )
           + sizeof( g_xuiFX_FENCE__UPDATE__UPDATE )
           + sizeof( g_xuiFX_FENCE__UPDATE__FINISH )
           + sizeof( g_xuiFX_FENCE__SCENE )
           + sizeof( g_xuiFX_FENCE__SCENE__REFRESH_BA )
           + sizeof( g_xuiFX_FENCE__SCENE__CULL )
           + sizeof( g_xuiFX_FENCE__SCENE__FINISH )
           + sizeof( g_xuiFX_FENCE__RENDER )
           + sizeof( g_xuiFX_FENCE__RENDER__PROCESS_HEADERS )
           + sizeof( g_xuiFX_FENCE__RENDER__ALLOCATE )
           + sizeof( g_xuiFX_FENCE__RENDER__GENERATE )
            
           + sizeof( g_apsFX_Descriptor )
           + sizeof( g_uiFX_Command_Size )

        #if defined(TgBUILD_FEATURE__GRAPHICS_VFX)
           + sizeof( g_asParticle_Header )
           + sizeof( g_uiParticle_Header_Index )
        /*# defined(TgBUILD_FEATURE__GRAPHICS_VFX) */
        #endif

           + sizeof( g_aiFX__Client__Shared_State )
           + sizeof( g_sFX_Effect__Client__Effect )
           + sizeof( g_asFX_Effect )

           + sizeof( g_atiFX__Client__Update__Head )
           + sizeof( g_niFX__Client__Update__Active )

           + sizeof( g_tiFX_File_Default )
           + sizeof( g_tiFX_File_Error )

           + sizeof( g_auiFX_KN_File__Effect_Hash )
           + sizeof( g_asFX_KN_File__Effect )
           + sizeof( g_asFX_Cache__Effect )

           + sizeof( g_xuiFX__Decal__Memory_Current )
           + sizeof( g_xuiFX__Emitter__Memory_Current )

           + tgFX__Client__Trail_Query_Fixed_Memory()
           + tgFX__Client__Sound_Query_Fixed_Memory()
           + tgFX__Client__Post_Query_Fixed_Memory()
           + tgFX__Client__Liquid_Query_Fixed_Memory()
           + tgFX__Client__Light_Query_Fixed_Memory()
           + tgFX__Client__Group_Query_Fixed_Memory()
           + tgFX__Client__GIB_Query_Fixed_Memory()
           + tgFX__Client__Glass_Query_Fixed_Memory()
           + tgFX__Client__Emitter_Query_Fixed_Memory()
           + tgFX__Client__Decal_Query_Fixed_Memory()
           + tgFX__Client__Billboard_Query_Fixed_Memory()
           + tgFX__Client__Beam_Query_Fixed_Memory()

         #if TgS_DEBUG__EFFECT
            + sizeof( g_tiFX_Debug__OSD__Profile_Enable )
            + sizeof( g_tiFX_Debug__OSD__Profile_Sort )
            + sizeof( g_tiFX_Debug__Draw_BA )
            + sizeof( g_tiFX_Debug__Draw_Emitter )
            + sizeof( g_tiFX_Debug__Disable_Module )
            + sizeof( g_tiFX_Debug__Disable_Update )
            + sizeof( g_tiFX_Debug__Disable_Render )
            + sizeof( g_tiFX_Debug__Disable_Render_Buffer )
            + sizeof( g_tiFX_Debug__Disable_Cull_On_Spawn )
            + sizeof( g_tiFX_Debug__Disable_Cull_On_Render )
            + sizeof( g_aszFX_Cache__EFfect_Name )
         /*# TgS_DEBUG__EFFECT */
         #endif
    );
}


/*# defined (ENABLE_RELOAD_GUARD) */
#else

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Generic Data                                                                                                                                                                   */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

PROFILE_DEFINE( T_TYPE(FX_,_COMMANDS__UPDATE) );

#if T_EFFECT_UPDATE
PROFILE_DEFINE( T_TYPE(FX_,_UPDATE__DATA) );
PROFILE_DEFINE( T_TYPE(FX_,_UPDATE_EXTERNAL__DATA) );
PROFILE_ARRAY_DEFINE( ETgFX_UPDATE__MAX + 1, T_TYPE(FX_, _UPDATE__UPDATE) );
/*# T_EFFECT_UPDATE */
#endif

#if T_EFFECT_SCENE
PROFILE_ARRAY_DEFINE( ETgFX_UPDATE__MAX, T_TYPE(FX_,_SCENE__CULL) );
PROFILE_DEFINE( T_TYPE(FX_,_SCENE__CULL_TOTAL) );
PROFILE_ARRAY_DEFINE( ETgFX_UPDATE__MAX, T_TYPE(FX_,_SCENE__UPDATE_BA) );
PROFILE_DEFINE( T_TYPE(FX_,_SCENE__UPDATE_BA_TOTAL) );
PROFILE_DEFINE( T_TYPE(FX_,_SCENE__FINISH_TOTAL) );
/*# T_EFFECT_SCENE */
#endif

#if T_EFFECT_RENDER
PROFILE_ARRAY_DEFINE( ETgFX_UPDATE__MAX, T_TYPE(FX_,_RENDER__PROCESS_HEADERS) );
PROFILE_DEFINE( T_TYPE(FX_,_RENDER__PROCESS_HEADERS_TOTAL) );
PROFILE_DEFINE( T_TYPE(FX_,_RENDER_PATCH_CONTEXT) );
PROFILE_DEFINE( T_TYPE(FX_,_RENDER_UPDATE) );
PROFILE_DEFINE( T_TYPE(FX_,_RENDER__GENERATE) );
/*# T_EFFECT_RENDER */
#endif

ETgFX_EFFECT_STATE                          T_NAME(g_aenFX__,__Shared__State)[T_TYPE(KTgFX_MAX_,)];
STg2_UT_LF_ISO__ST                          T_NAME(g_sFX__,__Client__Stack);
T_NAME(STg2_FX__,)                          T_NAME(g_asFX__,)[T_TYPE(KTgFX_MAX_,)];
STg2_FX_Descriptor                          T_NAME(g_sFX_Descriptor__,);
TgUINT_F32                                  T_NAME(g_uiFX__,__Shared__Notify_State);

#if TgS_DEBUG__EFFECT
TgCN_VAR_ID                                 T_NAME(g_tiFX_Debug__,__Disable_Create);
TgCN_VAR_ID                                 T_NAME(g_tiFX_Debug__,__Disable_Update);
TgCN_VAR_ID                                 T_NAME(g_tiFX_Debug__,__Disable_Scene_Cull);
TgCN_VAR_ID                                 T_NAME(g_tiFX_Debug__,__Disable_Render);
TgCN_VAR_ID                                 T_NAME(g_tiFX_Debug__,__Draw_BA);
TgCN_VAR_ID                                 T_NAME(g_tiFX_Debug__,__Draw_Debug);
/*# TgS_DEBUG__EFFECT */
#endif

#if T_EFFECT_UPDATE || T_EFFECT_RENDER
TgUINT_F08                                  T_NAME(g_asFX_Command__,__ToClient)[ETgFX_COMMAND__TO_CLIENT__BYTE_MAX];
TgRSIZE_A                                   T_NAME(g_xuiFX_Command__,__ToClient_Offset);
/*# T_EFFECT_UPDATE || T_EFFECT_RENDER */
#endif

#if T_EFFECT_UPDATE
TgRSIZE_A                                   T_TYPE(g_xuiFX_FENCE__UPDATE__UPDATE__,);
TgRSIZE_A                                   T_TYPE(g_axuiFX_FENCE__UPDATE__UPDATE__,)[ETgFX_UPDATE__MAX];
TgRSIZE_A                                   T_TYPE(g_xuiFX_FENCE__UPDATE__FINISH__,);
TgFX_DATA_INST_ID                           T_NAME(g_atiFX__,__Update__Head)[ETgFX_UPDATE__MAX];
TgSINT_F32                                  T_NAME(g_niFX__,__Update__Active);
STg2_Job                                    T_NAME(g_sFX__Job__,__Update)[ETgFX_UPDATE__MAX];
STg2_Job                                    T_NAME(g_sFX__Job__,__Update__Update_Finish);
STg2_Job                                    T_NAME(g_sFX__Job__,__Update__Process_ClientToUpdate);
TgRSIZE_A                                   T_NAME(g_xuiFX_Command__,__Update_Command_Offset);
TgRSIZE_A                                   T_NAME(g_xuiFX_Command__,__ClientToUpdate_Offset);
TgUINT_F08                                  T_NAME(g_asFX_Command__,__Update_Command_Buffer)[ETgFX_COMMAND__CLIENT_TO_UPDATE__BYTE_MAX];
TgUINT_F08                                  T_NAME(g_asFX_Command__,__ClientToUpdate)[ETgFX_COMMAND__CLIENT_TO_UPDATE__BYTE_MAX];
/*# T_EFFECT_UPDATE */
#endif

#if T_EFFECT_SCENE
TgRSIZE_A                                   T_TYPE(g_xuiFX_FENCE__SCENE__REFRESH_BA__,);
TgRSIZE_A                                   T_TYPE(g_axuiFX_FENCE__SCENE__REFRESH_BA__,)[ETgFX_UPDATE__MAX];
STg2_Job                                    T_NAME(g_asFX__Scene__Job__,_Refresh_BA)[ETgFX_UPDATE__MAX];
#if T_EFFECT_RENDER
TgRSIZE_A                                   T_TYPE(g_xuiFX_FENCE__SCENE__CULL__,);
TgRSIZE_A                                   T_TYPE(g_axuiFX_FENCE__SCENE__CULL__,)[ETgFX_UPDATE__MAX];
TgRSIZE_A                                   T_TYPE(g_xuiFX_FENCE__SCENE__FINISH__,);
STg2_Job                                    T_NAME(g_asFX__Scene__Job__,_Cull)[ETgFX_UPDATE__MAX];
STg2_Job                                    T_NAME(g_sFX__Scene__Job__,_Finish);
TgRSIZE_A                                   T_NAME(g_nbyFX__,__Scene__Particle_Memory);
TgFX_DATA_INST_ID                           T_NAME(g_atiFX__,__Scene__Particle_Head)[ETgFX_UPDATE__MAX];
TgFX_DATA_INST_ID                           T_NAME(g_atiFX__,__Scene__Mesh_Head)[ETgFX_UPDATE__MAX];
TgRSIZE                                     T_NAME(g_anuiFX__,__Scene__Particle_Active)[ETgFX_UPDATE__MAX];
TgRSIZE                                     T_NAME(g_anuiFX__,__Scene__Mesh_Active)[ETgFX_UPDATE__MAX];
TgFX_DATA_INST_ID                           T_NAME(g_atiFX__,__Scene__Culled_Head)[ETgFX_UPDATE__MAX];
TgSINT_F32                                  T_NAME(g_aniFX__,__Scene__Culled)[ETgFX_UPDATE__MAX];
/*# T_EFFECT_RENDER */
#else
TgFX_DATA_INST_ID                           T_NAME(g_atiFX__,__Scene__Effect_Head)[ETgFX_UPDATE__MAX];
TgSINT_F32                                  T_NAME(g_niFX__,__Scene__Effect_Active);
/*# T_EFFECT_RENDER */
#endif

/*# T_EFFECT_SCENE */
#endif

#if T_EFFECT_RENDER
TgRSIZE_A                                   T_TYPE(g_xuiFX_FENCE__RENDER__PROCESS_HEADERS__,);
TgRSIZE_A                                   T_TYPE(g_axuiFX_FENCE__RENDER__PROCESS_HEADERS__,)[ETgFX_UPDATE__MAX];
TgRSIZE_A                                   T_TYPE(g_xuiFX_FENCE__RENDER__GENERATE__,);
TgFX_DATA_INST_ID                           T_NAME(g_atiFX__,__Render_Header__Head)[ETgFX_UPDATE__MAX];
TgSINT_F32                                  T_NAME(g_niFX__,__Render_Header__Active);
TgFX_DATA_INST_ID                           T_NAME(g_tiFX__,__Render_Generate__Head);
TgSINT_F32                                  T_NAME(g_niFX__,__Render_Generate__Active);
STg2_Job                                    T_NAME(g_asFX__Render__Job__,_Process_Headers)[ETgFX_UPDATE__MAX];
STg2_Job                                    T_NAME(g_sFX__Render__Job__,_Render_Generate);
STg2_Job                                    T_NAME(g_sFX__Job__,__Scene__Cull)[ETgFX_UPDATE__MAX];
STg2_Job                                    T_NAME(g_sFX__Job__,__Render__Process_SceneToRender);
STg2_Job                                    T_NAME(g_sFX__Job__,__Render__Generate);
TgRSIZE_A                                   T_NAME(g_xuiFX_Command__,__SceneToRender_Offset);
TgUINT_F08                                  T_NAME(g_asFX_Command__,__SceneToRender)[ETgFX_COMMAND__SCENE_TO_RENDER__BYTE_MAX];
/*# T_EFFECT_RENDER */
#endif


/* ---- tgFX__Client__, _Query_Fixed_Memory -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRSIZE T_NAME(tgFX__Client__, _Query_Fixed_Memory)( TgVOID )
{
    return ( 0
             + sizeof( T_NAME(g_aenFX__,__Shared__State) )
             + sizeof( T_NAME(g_sFX__,__Client__Stack) )
             + sizeof( T_NAME(g_asFX__,) )
             + sizeof( T_NAME(g_sFX_Descriptor__,) )
             + sizeof( T_NAME(g_uiFX__,__Shared__Notify_State) )
 
        #if TgS_DEBUG__EFFECT
             + sizeof( T_NAME(g_tiFX_Debug__,__Disable_Create) )
             + sizeof( T_NAME(g_tiFX_Debug__,__Disable_Update) )
             + sizeof( T_NAME(g_tiFX_Debug__,__Disable_Scene_Cull) )
             + sizeof( T_NAME(g_tiFX_Debug__,__Disable_Render) )
             + sizeof( T_NAME(g_tiFX_Debug__,__Draw_BA) )
             + sizeof( T_NAME(g_tiFX_Debug__,__Draw_Debug) )
        /*# TgS_DEBUG__EFFECT */
        #endif
 
        #if T_EFFECT_UPDATE || T_EFFECT_RENDER
             + sizeof( T_NAME(g_asFX_Command__,__ToClient) )
             + sizeof( T_NAME(g_xuiFX_Command__,__ToClient_Offset) )
        /*# T_EFFECT_UPDATE || T_EFFECT_RENDER */
        #endif

        #if T_EFFECT_UPDATE
             + sizeof( T_TYPE(g_xuiFX_FENCE__UPDATE__UPDATE__,) )
             + sizeof( T_TYPE(g_axuiFX_FENCE__UPDATE__UPDATE__,) )
             + sizeof( T_TYPE(g_xuiFX_FENCE__UPDATE__FINISH__,) )
             + sizeof( T_NAME(g_atiFX__,__Update__Head) )
             + sizeof( T_NAME(g_niFX__,__Update__Active) )
             + sizeof( T_NAME(g_sFX__Job__,__Update) )
             + sizeof( T_NAME(g_sFX__Job__,__Update__Update_Finish) )
             + sizeof( T_NAME(g_sFX__Job__,__Update__Process_ClientToUpdate) )
             + sizeof( T_NAME(g_xuiFX_Command__,__Update_Command_Offset) )
             + sizeof( T_NAME(g_xuiFX_Command__,__ClientToUpdate_Offset) )
             + sizeof( T_NAME(g_asFX_Command__,__Update_Command_Buffer) )
             + sizeof( T_NAME(g_asFX_Command__,__ClientToUpdate) )
        /*# T_EFFECT_UPDATE */
        #endif

        #if T_EFFECT_SCENE
             + sizeof( T_TYPE(g_xuiFX_FENCE__SCENE__REFRESH_BA__,) )
             + sizeof( T_TYPE(g_axuiFX_FENCE__SCENE__REFRESH_BA__,) )
             + sizeof( T_NAME(g_asFX__Scene__Job__,_Refresh_BA) )
        #if T_EFFECT_RENDER
             + sizeof( T_TYPE(g_xuiFX_FENCE__SCENE__CULL__,) )
             + sizeof( T_TYPE(g_axuiFX_FENCE__SCENE__CULL__,) )
             + sizeof( T_TYPE(g_xuiFX_FENCE__SCENE__FINISH__,) )
             + sizeof( T_NAME(g_asFX__Scene__Job__,_Cull) )
             + sizeof( T_NAME(g_sFX__Scene__Job__,_Finish) )
             + sizeof( T_NAME(g_nbyFX__,__Scene__Particle_Memory) )
             + sizeof( T_NAME(g_atiFX__,__Scene__Particle_Head) )
             + sizeof( T_NAME(g_atiFX__,__Scene__Mesh_Head) )
             + sizeof( T_NAME(g_anuiFX__,__Scene__Particle_Active) )
             + sizeof( T_NAME(g_anuiFX__,__Scene__Mesh_Active) )
             + sizeof( T_NAME(g_atiFX__,__Scene__Culled_Head) )
             + sizeof( T_NAME(g_aniFX__,__Scene__Culled) )
        /*# T_EFFECT_RENDER */
        #else
             + sizeof( T_NAME(g_atiFX__,__Scene__Effect_Head) )
             + sizeof( T_NAME(g_niFX__,__Scene__Effect_Active) )
        /*# T_EFFECT_RENDER */
        #endif

        /*# T_EFFECT_SCENE */
        #endif

        #if T_EFFECT_RENDER
             + sizeof( T_TYPE(g_xuiFX_FENCE__RENDER__PROCESS_HEADERS__,) )
             + sizeof( T_TYPE(g_axuiFX_FENCE__RENDER__PROCESS_HEADERS__,) )
             + sizeof( T_TYPE(g_xuiFX_FENCE__RENDER__GENERATE__,) )
             + sizeof( T_NAME(g_atiFX__,__Render_Header__Head) )
             + sizeof( T_NAME(g_niFX__,__Render_Header__Active) )
             + sizeof( T_NAME(g_tiFX__,__Render_Generate__Head) )
             + sizeof( T_NAME(g_niFX__,__Render_Generate__Active) )
             + sizeof( T_NAME(g_asFX__Render__Job__,_Process_Headers) )
             + sizeof( T_NAME(g_sFX__Render__Job__,_Render_Generate) )
             + sizeof( T_NAME(g_sFX__Job__,__Scene__Cull) )
             + sizeof( T_NAME(g_sFX__Job__,__Render__Process_SceneToRender) )
             + sizeof( T_NAME(g_sFX__Job__,__Render__Generate) )
             + sizeof( T_NAME(g_xuiFX_Command__,__SceneToRender_Offset) )
             + sizeof( T_NAME(g_asFX_Command__,__SceneToRender) )
        /*# T_EFFECT_RENDER */
        #endif
    );
}



/* =============================================================================================================================================================================== */

/*# defined (ENABLE_RELOAD_GUARD) */
#endif
