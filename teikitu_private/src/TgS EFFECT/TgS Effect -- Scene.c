/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Effect - Effect - Scene.c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.12 | »GUID« 964CB1A6-814D-4E19-8E67-A83FCA98BF05 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined (ENABLE_RELOAD_GUARD)

    #define __PARENT_FILE__ "TgS Effect -- Scene.c"
    #define ENABLE_RELOAD_GUARD
    #include "TgS EFFECT/TgS Effect - Effect [INC].h"
    #undef ENABLE_RELOAD_GUARD
    #undef __PARENT_FILE__

#else
/* == Effects ==================================================================================================================================================================== */
#if T_EFFECT_SCENE

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#if T_EFFECT_RENDER
static TgVOID
T_NAME(tgFX__Client__,_Init_Scene_Cull)( TgVOID );

static TgBOOL
T_NAME(tgFX__Scene__,_Cull_Test)(
    STg2_SE_Context_PC, T_NAME(STg2_FX__,_P) );

static TgVOID
T_NAME(tgFX__Scene__,_Cull)( 
    STg2_SE_Context_PC, TgRSIZE_C, ETgFX_UPDATE_C );

static TgRESULT
T_NAME(tgFX__Scene__Job__,_Cull)(
    STg2_Job_CPC );

static TgVOID
T_NAME(tgFX__Scene__,_Finish)(
    STg2_SE_Context_PC, TgRSIZE_C );

static TgRESULT
T_NAME(tgFX__Scene__Job__,_Finish)(
    STg2_Job_CPC );

/*# T_EFFECT_RENDER */
#endif

static TgVOID
T_NAME(tgFX__Scene__,_Refresh_BA)(
    ETgFX_UPDATE_C );

static TgRESULT
T_NAME(tgFX__Scene__Job__,_Refresh_BA)(
    STg2_Job_CPC );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgFX__Client__Submit_Job__,_Scene_Cull ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if T_EFFECT_RENDER
TgVOID T_NAME(tgFX__Client__Submit_Job__,_Scene_Cull)( STg2_SE_Context_PC psSE_Context, TgRSIZE_C uiView_Index )
{
    union
    {
        STg2_FX_Job__Scene__Cull_Data_P     psJob;
        TgUINT_E08_P                        pui;
    }                                   psData;

    T_NAME(tgFX__Client__,_Init_Scene_Cull)();

    TgSTD_ATOMIC(fetch_add)( &T_TYPE(g_xuiFX_FENCE__SCENE__CULL__,), 1 );
    TgSTD_ATOMIC(fetch_add)( &g_xuiFX_FENCE__SCENE, 1 );
    TgSTD_ATOMIC(fetch_add)( &g_xuiFX_FENCE__SCENE__CULL, 1 );
    TgSTD_ATOMIC(fetch_add)( T_TYPE(g_axuiFX_FENCE__SCENE__CULL__,) + ETgFX_UPDATE__DEFAULT, 1 );

    psData.pui = T_NAME(g_asFX__Scene__Job__,_Cull)[ETgFX_UPDATE__DEFAULT].m_auiData;
    psData.psJob->m_enUpdate = ETgFX_UPDATE__DEFAULT;
    psData.psJob->m_uiView_Index = uiView_Index;
    psData.psJob->m_psScene_Context = psSE_Context;
    if (TgFAILED(tgJM_Queue_Job( g_sJob_Queue__Render_Normal, T_NAME(g_asFX__Scene__Job__,_Cull) + ETgFX_UPDATE__DEFAULT )))
    {
        TgWARNING_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to submit job." );
        T_NAME(tgFX__Scene__Job__,_Cull)( T_NAME(g_asFX__Scene__Job__,_Cull) + ETgFX_UPDATE__DEFAULT );
        TgSTD_ATOMIC(fetch_sub)( &T_TYPE(g_xuiFX_FENCE__SCENE__CULL__,), 1 );
    };

    TgSTD_ATOMIC(fetch_add)( &T_TYPE(g_xuiFX_FENCE__SCENE__CULL__,), 1 );
    TgSTD_ATOMIC(fetch_add)( &g_xuiFX_FENCE__SCENE, 1 );
    TgSTD_ATOMIC(fetch_add)( &g_xuiFX_FENCE__SCENE__CULL, 1 );
    TgSTD_ATOMIC(fetch_add)( T_TYPE(g_axuiFX_FENCE__SCENE__CULL__,) + ETgFX_UPDATE__EXTERNAL, 1 );

    psData.pui = T_NAME(g_asFX__Scene__Job__,_Cull)[ETgFX_UPDATE__EXTERNAL].m_auiData;
    psData.psJob->m_enUpdate = ETgFX_UPDATE__EXTERNAL;
    psData.psJob->m_uiView_Index = uiView_Index;
    psData.psJob->m_psScene_Context = psSE_Context;
    if (TgFAILED(tgJM_Queue_Job( g_sJob_Queue__Render_Normal, T_NAME(g_asFX__Scene__Job__,_Cull) + ETgFX_UPDATE__EXTERNAL )))
    {
        TgWARNING_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to submit job." );
        T_NAME(tgFX__Scene__Job__,_Cull)( T_NAME(g_asFX__Scene__Job__,_Cull) + ETgFX_UPDATE__EXTERNAL );
        TgSTD_ATOMIC(fetch_sub)( &T_TYPE(g_xuiFX_FENCE__SCENE__CULL__,), 1 );
    };
}
/*# T_EFFECT_RENDER */
#endif


/* ---- tgFX__Client__Submit_Job__,_Refresh_BA ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID T_NAME(tgFX__Client__Submit_Job__,_Refresh_BA)( TgVOID )
{
    union
    {
        STg2_FX_Job__Scene__Bounding_Box_P psJob;
        TgUINT_E08_P                        pui;
    }                                   psData;

    TgSTD_ATOMIC(fetch_add)( &T_TYPE(g_xuiFX_FENCE__SCENE__REFRESH_BA__,), 1 );
    TgSTD_ATOMIC(fetch_add)( &g_xuiFX_FENCE__SCENE, 1 );
    TgSTD_ATOMIC(fetch_add)( &g_xuiFX_FENCE__SCENE__REFRESH_BA, 1 );
    TgSTD_ATOMIC(fetch_add)( T_TYPE(g_axuiFX_FENCE__SCENE__REFRESH_BA__,) + ETgFX_UPDATE__DEFAULT, 1 );

    psData.pui = T_NAME(g_asFX__Scene__Job__,_Refresh_BA)[ETgFX_UPDATE__DEFAULT].m_auiData;
    psData.psJob->m_enUpdate = ETgFX_UPDATE__DEFAULT;
    if (TgFAILED(tgJM_Queue_Job( g_sJob_Queue__Render_Normal, T_NAME(g_asFX__Scene__Job__,_Refresh_BA) + ETgFX_UPDATE__DEFAULT )))
    {
        TgWARNING_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to submit job." );
        T_NAME(tgFX__Scene__Job__,_Refresh_BA)( T_NAME(g_asFX__Scene__Job__,_Refresh_BA) + ETgFX_UPDATE__DEFAULT );
        TgSTD_ATOMIC(fetch_sub)( &T_TYPE(g_xuiFX_FENCE__SCENE__REFRESH_BA__,), 1 );
    };

    TgSTD_ATOMIC(fetch_add)( &T_TYPE(g_xuiFX_FENCE__SCENE__REFRESH_BA__,), 1 );
    TgSTD_ATOMIC(fetch_add)( &g_xuiFX_FENCE__SCENE, 1 );
    TgSTD_ATOMIC(fetch_add)( &g_xuiFX_FENCE__SCENE__REFRESH_BA, 1 );
    TgSTD_ATOMIC(fetch_add)( T_TYPE(g_axuiFX_FENCE__SCENE__REFRESH_BA__,) + ETgFX_UPDATE__EXTERNAL, 1 );

    psData.pui = T_NAME(g_asFX__Scene__Job__,_Refresh_BA)[ETgFX_UPDATE__EXTERNAL].m_auiData;
    psData.psJob->m_enUpdate = ETgFX_UPDATE__EXTERNAL;
    if (TgFAILED(tgJM_Queue_Job( g_sJob_Queue__Render_Normal, T_NAME(g_asFX__Scene__Job__,_Refresh_BA) + ETgFX_UPDATE__EXTERNAL )))
    {
        TgWARNING_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to submit job." );
        T_NAME(tgFX__Scene__Job__,_Refresh_BA)( T_NAME(g_asFX__Scene__Job__,_Refresh_BA) + ETgFX_UPDATE__EXTERNAL );
        TgSTD_ATOMIC(fetch_sub)( &T_TYPE(g_xuiFX_FENCE__SCENE__REFRESH_BA__,), 1 );
    };
}


/* ---- tgFX__Client__Submit_Job__,_Scene_Finish --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if T_EFFECT_RENDER
TgVOID T_NAME(tgFX__Client__Submit_Job__,_Scene_Finish)( STg2_SE_Context_PC psSE_Context, TgRSIZE_C uiView_Index )
{
    union
    {
        STg2_FX_Job__Scene__Finish_P        psJob;
        TgUINT_E08_P                        pui;
    }                                   psData;

    TgSTD_ATOMIC(fetch_add)( &T_TYPE(g_xuiFX_FENCE__SCENE__FINISH__,), 1 );
    TgSTD_ATOMIC(fetch_add)( &g_xuiFX_FENCE__SCENE, 1 );
    TgSTD_ATOMIC(fetch_add)( &g_xuiFX_FENCE__SCENE__FINISH, 1 );

    psData.pui = T_NAME(g_sFX__Scene__Job__,_Finish).m_auiData;
    psData.psJob->m_uiView_Index = uiView_Index;
    psData.psJob->m_psScene_Context = psSE_Context;
    if (TgFAILED(tgJM_Queue_Job( g_sJob_Queue__Render_Normal, &T_NAME(g_sFX__Scene__Job__,_Finish) )))
    {
        TgWARNING_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to submit job." );
        T_NAME(tgFX__Scene__Job__,_Finish)( &T_NAME(g_sFX__Scene__Job__,_Finish) );
        TgSTD_ATOMIC(fetch_sub)( &T_TYPE(g_xuiFX_FENCE__SCENE__FINISH__,), 1 );
    };
}
/*# T_EFFECT_RENDER */
#endif




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgFX__Client__,_Init_Scene ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID T_NAME(tgFX__Client__,_Init_Scene)( TgVOID )
{
    TgRSIZE                             uiIndex;

    PROFILE_ARRAY_INIT( 0, DEFAULT, T_TYPE(FX_,_SCENE__CULL) );
    PROFILE_ARRAY_INIT( 1, EXTERNAL, T_TYPE(FX_,_SCENE__CULL) );
    PROFILE_INIT( T_TYPE(FX_,_SCENE__CULL_TOTAL) );
    PROFILE_ARRAY_INIT( 0, DEFAULT, T_TYPE(FX_,_SCENE__UPDATE_BA) );
    PROFILE_ARRAY_INIT( 1, EXTERNAL, T_TYPE(FX_,_SCENE__UPDATE_BA) );
    PROFILE_INIT( T_TYPE(FX_,_SCENE__UPDATE_BA_TOTAL) );
    PROFILE_INIT( T_TYPE(FX_,_SCENE__FINISH_TOTAL) );

    /* Fence Controls */

    TgSTD_ATOMIC(store)( &T_TYPE(g_xuiFX_FENCE__SCENE__REFRESH_BA__,), 0 );
    for (uiIndex = 0; uiIndex < ETgFX_UPDATE__MAX; ++uiIndex)
    {
        TgSTD_ATOMIC(store)( T_TYPE(g_axuiFX_FENCE__SCENE__REFRESH_BA__,) + uiIndex, 0 );
    };

    /* Jobs */

    tgMM_Set_U08_0x00( T_NAME(g_asFX__Scene__Job__,_Refresh_BA), sizeof(T_NAME(g_asFX__Scene__Job__,_Refresh_BA)) );


#if T_EFFECT_RENDER

    /* Fence Controls */

    TgSTD_ATOMIC(store)( &g_xuiFX_FENCE__SCENE__CULL, 0 );
    TgSTD_ATOMIC(store)( &g_xuiFX_FENCE__SCENE__FINISH, 0 );

    TgSTD_ATOMIC(store)( &T_TYPE(g_xuiFX_FENCE__SCENE__CULL__,), 0 );
    for (uiIndex = 0; uiIndex < ETgFX_UPDATE__MAX; ++uiIndex)
    {
        TgSTD_ATOMIC(store)( T_TYPE(g_axuiFX_FENCE__SCENE__CULL__,) + uiIndex, 0 );
    };
    TgSTD_ATOMIC(store)( &T_TYPE(g_xuiFX_FENCE__SCENE__FINISH__,), 0 );

    /* Jobs */

    tgMM_Set_U08_0x00( T_NAME(g_asFX__Scene__Job__,_Cull), sizeof(T_NAME(g_asFX__Scene__Job__,_Cull)) );
    tgMM_Set_U08_0x00( &T_NAME(g_sFX__Scene__Job__,_Finish), sizeof( STg2_Job ) );

    T_NAME(tgFX__Client__,_Init_Scene_Cull)();

/*# T_EFFECT_RENDER */
#else
    /* Effect Lists */

    tgMM_Set_U08_0x00( T_NAME(g_atiFX__,__Scene__Effect_Head), sizeof(T_NAME(g_atiFX__,__Scene__Effect_Head)) );
    T_NAME(g_niFX__,__Scene__Effect_Active) = 0;

/*# T_EFFECT_RENDER */
#endif
}


/* ---- tgFX__Client__,_Boot ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID T_NAME(tgFX__Client__,_Boot_Scene)( TgVOID )
{
    T_NAME(g_asFX__Scene__Job__,_Refresh_BA)[ETgFX_UPDATE__DEFAULT].m_pfnExecute = T_NAME(tgFX__Scene__Job__,_Refresh_BA);
    T_NAME(g_asFX__Scene__Job__,_Refresh_BA)[ETgFX_UPDATE__DEFAULT].m_pxuiTrigger = &T_TYPE(g_xuiFX_FENCE__UPDATE__FINISH__,);
    T_NAME(g_asFX__Scene__Job__,_Refresh_BA)[ETgFX_UPDATE__DEFAULT].m_pxuiFinish = &T_TYPE(g_xuiFX_FENCE__SCENE__REFRESH_BA__,);

    T_NAME(g_asFX__Scene__Job__,_Refresh_BA)[ETgFX_UPDATE__EXTERNAL].m_pfnExecute = T_NAME(tgFX__Scene__Job__,_Refresh_BA);
    T_NAME(g_asFX__Scene__Job__,_Refresh_BA)[ETgFX_UPDATE__EXTERNAL].m_pxuiTrigger = &T_TYPE(g_xuiFX_FENCE__UPDATE__FINISH__,);
    T_NAME(g_asFX__Scene__Job__,_Refresh_BA)[ETgFX_UPDATE__EXTERNAL].m_pxuiFinish = &T_TYPE(g_xuiFX_FENCE__SCENE__REFRESH_BA__,);

#if T_EFFECT_RENDER
    T_NAME(g_asFX__Scene__Job__,_Cull)[ETgFX_UPDATE__DEFAULT].m_pfnExecute = T_NAME(tgFX__Scene__Job__,_Cull);
    T_NAME(g_asFX__Scene__Job__,_Cull)[ETgFX_UPDATE__DEFAULT].m_pxuiTrigger = &T_TYPE(g_xuiFX_FENCE__UPDATE__FINISH__,);
    T_NAME(g_asFX__Scene__Job__,_Cull)[ETgFX_UPDATE__DEFAULT].m_pxuiFinish = &T_TYPE(g_xuiFX_FENCE__SCENE__CULL__,);

    T_NAME(g_asFX__Scene__Job__,_Cull)[ETgFX_UPDATE__EXTERNAL].m_pfnExecute = T_NAME(tgFX__Scene__Job__,_Cull);
    T_NAME(g_asFX__Scene__Job__,_Cull)[ETgFX_UPDATE__EXTERNAL].m_pxuiTrigger = &T_TYPE(g_xuiFX_FENCE__UPDATE__FINISH__,);
    T_NAME(g_asFX__Scene__Job__,_Cull)[ETgFX_UPDATE__EXTERNAL].m_pxuiFinish = &T_TYPE(g_xuiFX_FENCE__SCENE__CULL__,);

    T_NAME(g_sFX__Scene__Job__,_Finish).m_pfnExecute = T_NAME(tgFX__Scene__Job__,_Finish);
    T_NAME(g_sFX__Scene__Job__,_Finish).m_pxuiTrigger = &T_TYPE(g_xuiFX_FENCE__SCENE__CULL__,);
    T_NAME(g_sFX__Scene__Job__,_Finish).m_pxuiFinish = &T_TYPE(g_xuiFX_FENCE__SCENE__FINISH__,);
/*# T_EFFECT_RENDER */
#endif
}


#if T_EFFECT_RENDER

/* ---- tgFX__,_Reset_Scene_Particle_Head ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgFX_DATA_INST_ID T_NAME(tgFX__,_Reset_Scene_Particle_Head)( ETgFX_UPDATE_C enUpdate )
{
    TgFX_DATA_INST_ID                   tiActive;

    tiActive = T_NAME(g_atiFX__,__Scene__Particle_Head)[enUpdate];
    T_NAME(g_atiFX__,__Scene__Particle_Head)[enUpdate] = KTgFX_DATA_INST_ID__INVALID;

    return (tiActive);
}


/* ---- tgFX__,_Reset_Scene_Mesh_Head -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgFX_DATA_INST_ID T_NAME(tgFX__,_Reset_Scene_Mesh_Head)( ETgFX_UPDATE_C enUpdate )
{
    TgFX_DATA_INST_ID                   tiActive;

    tiActive = T_NAME(g_atiFX__,__Scene__Mesh_Head)[enUpdate];
    T_NAME(g_atiFX__,__Scene__Mesh_Head)[enUpdate] = KTgFX_DATA_INST_ID__INVALID;

    return (tiActive);
}


/* ---- tgFX__,_Scene_Active_Count ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRSIZE T_NAME(tgFX__,_Scene_Active_Count)( ETgFX_UPDATE_C enUpdate )
{
    return (T_NAME(g_anuiFX__,__Scene__Particle_Active)[enUpdate] + T_NAME(g_anuiFX__,__Scene__Mesh_Active)[enUpdate]);
}

/*# T_EFFECT_RENDER */
#else

/* ---- tgFX__,_Reset_Scene_Effect_Head ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgFX_DATA_INST_ID T_NAME(tgFX__,_Reset_Scene_Effect_Head)( ETgFX_UPDATE_C enUpdate )
{
    TgFX_DATA_INST_ID                   tiActive;

    tiActive = T_NAME(g_atiFX__,__Scene__Effect_Head)[enUpdate];
    T_NAME(g_atiFX__,__Scene__Effect_Head)[enUpdate] = KTgFX_DATA_INST_ID__INVALID;

    return (tiActive);
}

/*# T_EFFECT_RENDER */
#endif




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgFX__Client__,_Init_Scene_Cull ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if T_EFFECT_RENDER
static TgVOID T_NAME(tgFX__Client__,_Init_Scene_Cull)( TgVOID )
{
    tgMM_Set_U08_0x00( T_NAME(g_atiFX__,__Scene__Particle_Head), sizeof(T_NAME(g_atiFX__,__Scene__Particle_Head)) );
    tgMM_Set_U08_0x00( T_NAME(g_atiFX__,__Scene__Mesh_Head), sizeof(T_NAME(g_atiFX__,__Scene__Mesh_Head)) );
    tgMM_Set_U08_0x00( T_NAME(g_anuiFX__,__Scene__Particle_Active), sizeof(T_NAME(g_anuiFX__,__Scene__Particle_Active)) );
    tgMM_Set_U08_0x00( T_NAME(g_anuiFX__,__Scene__Mesh_Active), sizeof(T_NAME(g_anuiFX__,__Scene__Mesh_Active)) );
    tgMM_Set_U08_0x00( T_NAME(g_atiFX__,__Scene__Culled_Head), sizeof(T_NAME(g_atiFX__,__Scene__Culled_Head)) );
    tgMM_Set_U08_0x00( T_NAME(g_aniFX__,__Scene__Culled), sizeof(T_NAME(g_aniFX__,__Scene__Culled)) );
}
/*# T_EFFECT_RENDER */
#endif


/* ---- tgFX__Scene__,_Scene_Cull_Test ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if T_EFFECT_RENDER
static TgBOOL T_NAME(tgFX__Scene__,_Cull_Test)( TgATTRIBUTE_UNUSED STg2_SE_Context_PC psSE_Context, T_NAME(STg2_FX__,_P) psEffect )
{
#if TgS_DEBUG__EFFECT
    TgBOOL                              bDisable;
    if ((tgCN_Var_Query_Bool( &bDisable, T_NAME( g_tiFX_Debug__,__Disable_Scene_Cull ) )) && (bDisable))
        return (true);
/*# TgS_DEBUG__EFFECT */
#endif

    if (0 != psEffect->m_uiRender__NotVisible)
        return (false);

    /* #TODO: Frustum Test */

    /* #TODO: Viz Graph Test */

    /* #TODO: Occlusion Test */
    return (true);
}
/*# T_EFFECT_RENDER */
#endif


/* ---- tgFX__Scene__,_Scene_Cull ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if T_EFFECT_RENDER
static TgVOID T_NAME(tgFX__Scene__,_Cull)( STg2_SE_Context_PC psSE_Context, TgRSIZE_C uiView_Index, ETgFX_UPDATE_C enUpdate )
{
    //TgRN_TARGET_ID_C                    tiRN_Target = psSE_Context->m_asView[uiView_Index].m_tiRN_Target;
    //TgUINT_E32                          uiFlags = KTgRN_DATA_MESH__IN_FRUSTUM | KTgRN_DATA_MESH__NO_LOD | KTgRN_DATA_MESH__NO_LIGHTING;

    TgRSIZE                             uiIndex_In_SE_Context;
    TgFX_DATA_INST_ID                   tiActive;
    TgFX_DATA_INST_ID                   tiNext_Active;
    TgBOOL                              bFirstCull;
    T_NAME(STg2_FX__,_P)                psEffect;
    ETgFX_NEXT                          enFX_Next;
    TgRSIZE                             uiView_Inst_Index;

    PROFILE_ARRAY_START( enUpdate, T_TYPE(FX_, _SCENE__CULL), T_NAME(tgFX__Scene__,_Cull) );
    PROFILE_START( T_TYPE(FX_, _SCENE__CULL_TOTAL), T_NAME(tgFX__Scene__,_Cull) );

    uiIndex_In_SE_Context = 0;
    bFirstCull = true;

#if T_EFFECT_RENDER
    /* If we have already generated one view for the scene context, then we can reuse the frame mesh data - cull against all existing inserted objects */
    tiActive = T_NAME(g_atiFX__,__Scene__Particle_Head)[enUpdate];
    if (KTgID__INVALID_VALUE != tiActive.m_uiKI)
    {
        bFirstCull = false;
        do
        {
            psEffect = T_NAME(g_asFX__,) + tiActive.m_uiI;

            if (T_NAME(tgFX__Scene__,_Cull_Test)( psSE_Context, psEffect ))
            {
                uiView_Inst_Index = TgSTD_ATOMIC(fetch_add)( psSE_Context->m_asView[uiView_Index].m_axnuiFrame_Mesh_Inst + ETgSE_DRAW_TYPE__TRANSPARENT, 1 );
                if (uiView_Inst_Index < psSE_Context->m_asView[uiView_Index].m_anuiFrame_Mesh_Inst_Max[ETgSE_DRAW_TYPE__TRANSPARENT])
                    psSE_Context->m_asView[uiView_Index].m_apuiFrame_Mesh_Inst[ETgSE_DRAW_TYPE__TRANSPARENT][uiView_Inst_Index] = psEffect->m_uiIndex_In_SE_Context;
            }

            /* Completed processing the effect */
            tiActive = psEffect->m_tiNext[ETgFX_NEXT__SCENE];
        }
        while (KTgID__INVALID_VALUE != tiActive.m_uiKI);
    };

    tiActive = T_NAME(g_atiFX__,__Scene__Mesh_Head)[enUpdate];
    if (KTgID__INVALID_VALUE != tiActive.m_uiKI)
    {
        bFirstCull = false;
        do
        {
            psEffect = T_NAME(g_asFX__,) + tiActive.m_uiI;

            if (T_NAME(tgFX__Scene__,_Cull_Test)( psSE_Context, psEffect ))
            {
                if (tgRN_Material__Is_Opaque( psEffect->m_tiMaterial ))
                {
                    uiView_Inst_Index = TgSTD_ATOMIC(fetch_add)( psSE_Context->m_asView[uiView_Index].m_axnuiFrame_Mesh_Inst + ETgSE_DRAW_TYPE__OPAQUE, 1 );
                    if (uiView_Inst_Index < psSE_Context->m_asView[uiView_Index].m_anuiFrame_Mesh_Inst_Max[ETgSE_DRAW_TYPE__OPAQUE])
                        psSE_Context->m_asView[uiView_Index].m_apuiFrame_Mesh_Inst[ETgSE_DRAW_TYPE__OPAQUE][uiView_Inst_Index] = psEffect->m_uiIndex_In_SE_Context;
                }
                else
                {
                    uiView_Inst_Index = TgSTD_ATOMIC(fetch_add)( psSE_Context->m_asView[uiView_Index].m_axnuiFrame_Mesh_Inst + ETgSE_DRAW_TYPE__TRANSPARENT, 1 );
                    if (uiView_Inst_Index < psSE_Context->m_asView[uiView_Index].m_anuiFrame_Mesh_Inst_Max[ETgSE_DRAW_TYPE__TRANSPARENT])
                        psSE_Context->m_asView[uiView_Index].m_apuiFrame_Mesh_Inst[ETgSE_DRAW_TYPE__TRANSPARENT][uiView_Inst_Index] = psEffect->m_uiIndex_In_SE_Context;
                };
            }

            /* Completed processing the effect */
            tiActive = psEffect->m_tiNext[ETgFX_NEXT__SCENE];
        }
        while (KTgID__INVALID_VALUE != tiActive.m_uiKI);
    };

/*# T_EFFECT_RENDER */
#else

    tiActive = T_NAME(g_atiFX__,__Scene__Effect_Head)[enUpdate];
    if (KTgID__INVALID_VALUE != tiActive.m_uiKI)
    {
        bFirstCull = false;
        do
        {
            psEffect = T_NAME(g_asFX__,) + tiActive.m_uiI;

            if (T_NAME(tgFX__Scene__,_Cull_Test)( psSE_Context, psEffect ))
            {
                T_NAME(tgFX__Scene__,_Insert_Into_Scene_Context)();
            }

            /* Completed processing the effect */
            tiActive = psEffect->m_tiNext[ETgFX_NEXT__SCENE];
        }
        while (KTgID__INVALID_VALUE != tiActive.m_uiKI);
    };

/*# T_EFFECT_RENDER */
#endif

    /* If this is our first time processing the scene context then parse through all effects from the update list, otherwise they have been added to the scene lists */
    tiActive = T_NAME(g_atiFX__,__Scene__Culled_Head)[enUpdate];
    if (bFirstCull && (KTgID__INVALID_VALUE == tiActive.m_uiKI))
    {
        tiActive = T_NAME(tgFX__,_Query_Effect_Update_Head)( enUpdate );
        enFX_Next = ETgFX_NEXT__UPDATE;
    }
    else
    {
        enFX_Next = ETgFX_NEXT__SCENE;
    };

    while (KTgID__INVALID_VALUE != tiActive.m_uiKI)
    {
    #if T_EFFECT_RENDER && T_EFFECT_FRAME
        TgVEC_F32_04_1                            vPos_W;
        TgVEC_F32_04_1                            qRot_W;
    #endif

        psEffect = T_NAME( g_asFX__, ) + tiActive.m_uiI;

        psEffect->m_uiIndex_In_RN_Context = KTgMAX_RSIZE;
        psEffect->m_uiIndex_In_SE_Context = KTgMAX_RSIZE;
        psEffect->m_fSE_Quality_Score = 0.0F;

        tiNext_Active = psEffect->m_tiNext[enFX_Next];

    #if T_EFFECT_RENDER
        if (!T_NAME(tgFX__Scene__,_Cull_Test)( psSE_Context, psEffect ))
            goto T_NAME(tgFX__Scene__,_Update_BA__Cull_Out);

        /* Effect is within the camera frustum */
        uiIndex_In_SE_Context = TgSTD_ATOMIC(fetch_add)( &psSE_Context->m_xnuiFrame_Mesh, 1 );
        if (uiIndex_In_SE_Context >= psSE_Context->m_nuiFrame_Mesh_Max)
            goto T_NAME(tgFX__Scene__,_Update_BA__Cull_Out);

        psEffect->m_uiIndex_In_SE_Context = uiIndex_In_SE_Context;
        psEffect->m_fSE_Quality_Score = 1.0F;

        psSE_Context->m_asFrame_Mesh[uiIndex_In_SE_Context].m_tiMesh_Set = psEffect->m_tiMesh_Set;
        psSE_Context->m_asFrame_Mesh[uiIndex_In_SE_Context].m_uiLOD_Index = 0;
        psSE_Context->m_asFrame_Mesh[uiIndex_In_SE_Context].m_uiFlags = 0;

    #if T_EFFECT_FRAME
        psSE_Context->m_asFrame_Mesh[uiIndex_In_SE_Context].m_vScale = psEffect->m_vScale;
        vPos_W = psEffect->m_vPos_N2W;
        qRot_W = psEffect->m_qRot_N2W;
        tgMH_Init_Quat_F32_04_3( &psSE_Context->m_asFrame_Mesh[uiIndex_In_SE_Context].m_xTX, qRot_W );
        tgMH_Set_T_F32_04_3( &psSE_Context->m_asFrame_Mesh[uiIndex_In_SE_Context].m_xTX, vPos_W );
    /*# T_EFFECT_FRAME */
    #else
        psSE_Context->m_asFrame_Mesh[uiIndex_In_SE_Context].m_xTX.m_avCol[0] = KTgIDENT_F32_04_3.m_avCol[0];
        psSE_Context->m_asFrame_Mesh[uiIndex_In_SE_Context].m_xTX.m_avCol[1] = KTgIDENT_F32_04_3.m_avCol[1];
        psSE_Context->m_asFrame_Mesh[uiIndex_In_SE_Context].m_xTX.m_avCol[2] = KTgIDENT_F32_04_3.m_avCol[2];
    /*# T_EFFECT_FRAME */
    #endif

        psSE_Context->m_asFrame_Mesh[uiIndex_In_SE_Context].m_vLast_Scale = KTgONE_V128.m_vF32_04_1;
        psSE_Context->m_asFrame_Mesh[uiIndex_In_SE_Context].m_xLast_TX.m_avCol[0] = KTgIDENT_F32_04_3.m_avCol[0];
        psSE_Context->m_asFrame_Mesh[uiIndex_In_SE_Context].m_xLast_TX.m_avCol[1] = KTgIDENT_F32_04_3.m_avCol[1];
        psSE_Context->m_asFrame_Mesh[uiIndex_In_SE_Context].m_xLast_TX.m_avCol[2] = KTgIDENT_F32_04_3.m_avCol[2];

        psSE_Context->m_asFrame_Mesh[uiIndex_In_SE_Context].m_vBA_Max_W = psEffect->m_vBA_Max_W;
        psSE_Context->m_asFrame_Mesh[uiIndex_In_SE_Context].m_vBA_Min_W = psEffect->m_vBA_Min_W;

        psSE_Context->m_asFrame_Mesh[uiIndex_In_SE_Context].m_vAmbient = KTgZERO_V128.m_vF32_04_1;
        psSE_Context->m_asFrame_Mesh[uiIndex_In_SE_Context].m_vLM = KTgZERO_V128.m_vF32_04_1;
        psSE_Context->m_asFrame_Mesh[uiIndex_In_SE_Context].m_tiLM.m_uiKI = KTgID__INVALID_VALUE;
        psSE_Context->m_asFrame_Mesh[uiIndex_In_SE_Context].m_tiMaterial = psEffect->m_tiMaterial;
        psSE_Context->m_asFrame_Mesh[uiIndex_In_SE_Context].m_nuiLight = 0;

        psSE_Context->m_asFrame_Mesh[uiIndex_In_SE_Context].m_uiSkeleton_0 = KTgMAX_U32;
        psSE_Context->m_asFrame_Mesh[uiIndex_In_SE_Context].m_uiSkeleton_1 = KTgMAX_U32;

        psSE_Context->m_asFrame_Mesh[uiIndex_In_SE_Context].m_fOpacity = 1.0F;

        if (KTgID__INVALID_VALUE == psEffect->m_tiMesh_Set.m_uiKI)
        {
            psSE_Context->m_asFrame_Mesh[uiIndex_In_SE_Context].m_uiFlags |= KTgRN_DATA_MESH__PARTICLE;
            psEffect->m_tiNext[ETgFX_NEXT__SCENE] = T_NAME(g_atiFX__,__Scene__Particle_Head)[enUpdate];
            T_NAME(g_atiFX__,__Scene__Particle_Head)[enUpdate] = psEffect->m_tiData;
            T_NAME(g_anuiFX__,__Scene__Particle_Active)[enUpdate] += 1;
        }
        else
        {
            psEffect->m_tiNext[ETgFX_NEXT__SCENE] = T_NAME(g_atiFX__,__Scene__Mesh_Head)[enUpdate];
            T_NAME(g_atiFX__,__Scene__Mesh_Head)[enUpdate] = psEffect->m_tiData;
            T_NAME(g_anuiFX__,__Scene__Mesh_Active)[enUpdate] += 1;
        };

        if (psEffect->m_uiRender__ScreenSpace)
        {
            psSE_Context->m_asFrame_Mesh[uiIndex_In_SE_Context].m_uiFlags |= KTgRN_DATA_MESH__SCREEN_SPACE;
        };

        if (tgRN_Material__Is_Opaque( psEffect->m_tiMaterial ))
        {
            uiView_Inst_Index = TgSTD_ATOMIC(fetch_add)( psSE_Context->m_asView[uiView_Index].m_axnuiFrame_Mesh_Inst + ETgSE_DRAW_TYPE__OPAQUE, 1 );
            if (uiView_Inst_Index < psSE_Context->m_asView[uiView_Index].m_anuiFrame_Mesh_Inst_Max[ETgSE_DRAW_TYPE__OPAQUE])
                psSE_Context->m_asView[uiView_Index].m_apuiFrame_Mesh_Inst[ETgSE_DRAW_TYPE__OPAQUE][uiView_Inst_Index] = uiIndex_In_SE_Context;
        }
        else
        {
            uiView_Inst_Index = TgSTD_ATOMIC(fetch_add)( psSE_Context->m_asView[uiView_Index].m_axnuiFrame_Mesh_Inst + ETgSE_DRAW_TYPE__TRANSPARENT, 1 );
            if (uiView_Inst_Index < psSE_Context->m_asView[uiView_Index].m_anuiFrame_Mesh_Inst_Max[ETgSE_DRAW_TYPE__TRANSPARENT])
                psSE_Context->m_asView[uiView_Index].m_apuiFrame_Mesh_Inst[ETgSE_DRAW_TYPE__TRANSPARENT][uiView_Inst_Index] = uiIndex_In_SE_Context;
        };

        goto T_NAME(tgFX__Scene__,_Update_BA__Cull_Done);

    /*# T_EFFECT_RENDER */
    #else

        if (0 != psEffect->m_uiRender__NotVisible)
            goto T_NAME(tgFX__Scene__,_Update_BA__Cull_Out);

        /* #TODO: RENDER TARGET TEST */

        T_NAME( tgFX__Scene__,_Insert_Into_Scene_Context )();

        psEffect->m_tiNext[ETgFX_NEXT__SCENE] = T_NAME(g_atiFX__,__Scene__Effect_Head )[enUpdate];
        T_NAME(g_atiFX__,__Scene__Effect_Head)[enUpdate] = psEffect->m_tiData;
        T_NAME(g_niFX__,__Scene__Effect_Active) += 1;

        goto T_NAME(tgFX__Scene__,_Update_BA__Cull_Done);
    /*# T_EFFECT_RENDER */
    #endif


        /* Effect is outside the camera frustum */
T_NAME(tgFX__Scene__,_Update_BA__Cull_Out):
        psEffect->m_tiNext[ETgFX_NEXT__SCENE] = T_NAME(g_atiFX__,__Scene__Culled_Head)[enUpdate];
        T_NAME(g_atiFX__,__Scene__Culled_Head)[enUpdate] = psEffect->m_tiData;
        T_NAME(g_aniFX__,__Scene__Culled)[enUpdate] += 1;


        /* Completed processing the effect */
T_NAME(tgFX__Scene__,_Update_BA__Cull_Done):
        tiActive = tiNext_Active;
    };

    if (uiIndex_In_SE_Context >= psSE_Context->m_nuiFrame_Mesh_Max)
    {
        TgWARNING_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Too many frame instances used for camera (%32.32s).\n", psSE_Context->m_asView[uiView_Index].m_psCamera->m_szName );
    };

    PROFILE_STOP( T_TYPE(FX_, _SCENE__CULL_TOTAL), T_NAME(tgFX__Scene__,_Cull) );
    PROFILE_ARRAY_STOP( enUpdate, T_TYPE(FX_, _SCENE__CULL), T_NAME(tgFX__Scene__,_Cull) );
}
/*# T_EFFECT_RENDER */
#endif


/* ---- tgFX__Scene__Job__,_Cull ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if T_EFFECT_RENDER
static TgRESULT T_NAME(tgFX__Scene__Job__,_Cull)( STg2_Job_CPC psJob )
{
    union
    {
        STg2_FX_Job__Scene__Cull_Data_CP    psJob;
        TgUINT_E08_CP                       pui;
    }                                   psData;

    TgERROR(0 == T_TYPE(g_xuiFX_FENCE__UPDATE__FINISH__,));

    psData.pui = psJob->m_auiData;

    if (nullptr != psData.psJob->m_psScene_Context)
    {
        T_NAME(tgFX__Scene__,_Cull)( psData.psJob->m_psScene_Context, psData.psJob->m_uiView_Index, psData.psJob->m_enUpdate );
    }

    TgSTD_ATOMIC(fetch_sub)( &g_xuiFX_FENCE__SCENE, 1 );
    TgSTD_ATOMIC(fetch_sub)( &g_xuiFX_FENCE__SCENE__CULL, 1 );
    TgSTD_ATOMIC(fetch_sub)( T_TYPE(g_axuiFX_FENCE__SCENE__CULL__,) + psData.psJob->m_enUpdate, 1 );

    return (nullptr != psData.psJob->m_psScene_Context ? KTgS_OK : KTgE_FAIL);
}
/*# T_EFFECT_RENDER */
#endif


/* ---- tgFX__Scene__,_Refresh_BA ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID T_NAME(tgFX__Scene__,_Refresh_BA)( ETgFX_UPDATE_C enUpdate )
{
#if T_EFFECT_RENDER
    TgFX_DATA_INST_ID                   tiActive;
    T_NAME(STg2_FX__,_P)                psEffect;

    PROFILE_ARRAY_START( enUpdate, T_TYPE(FX_, _SCENE__UPDATE_BA), T_NAME(tgFX__Scene__,_Refresh_BA) );
    PROFILE_START( T_TYPE(FX_, _SCENE__UPDATE_BA_TOTAL), T_NAME(tgFX__Scene__,_Refresh_BA) );

    tiActive = T_NAME(g_atiFX__,__Scene__Culled_Head)[enUpdate];

    while (KTgID__INVALID_VALUE != tiActive.m_uiKI)
    {
        psEffect = T_NAME(g_asFX__,) + tiActive.m_uiI;
        T_NAME(tgFX_,__Update_BA)( tiActive );
        tiActive = psEffect->m_tiNext[ETgFX_NEXT__SCENE];
    };

    PROFILE_STOP( T_TYPE(FX_, _SCENE__UPDATE_BA_TOTAL), T_NAME(tgFX__Scene__,_Refresh_BA) );
    PROFILE_ARRAY_STOP( enUpdate, T_TYPE(FX_, _SCENE__UPDATE_BA), T_NAME(tgFX__Scene__,_Refresh_BA) );
#else
    (void)enUpdate;
/*# T_EFFECT_RENDER */
#endif
}


/* ---- tgFX__Scene__Job__,_Refresh_BA ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT T_NAME(tgFX__Scene__Job__,_Refresh_BA)( STg2_Job_CPC psJob )
{
    union
    {
        STg2_FX_Job__Scene__Bounding_Box_CP psJob;
        TgUINT_E08_CP                       pui;
    }                                   psData;

    TgERROR(0 == T_TYPE(g_xuiFX_FENCE__UPDATE__FINISH__,));

    psData.pui = psJob->m_auiData;

    T_NAME(tgFX__Scene__,_Refresh_BA)( psData.psJob->m_enUpdate );

    TgSTD_ATOMIC(fetch_sub)( &g_xuiFX_FENCE__SCENE, 1 );
    TgSTD_ATOMIC(fetch_sub)( &g_xuiFX_FENCE__SCENE__REFRESH_BA, 1 );
    TgSTD_ATOMIC(fetch_sub)( T_TYPE(g_axuiFX_FENCE__SCENE__REFRESH_BA__,) + psData.psJob->m_enUpdate, 1 );

    return (KTgS_OK);
}


/* ---- tgFX__Scene__,_Finish ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if T_EFFECT_RENDER
static TgVOID T_NAME(tgFX__Scene__,_Finish)( STg2_SE_Context_PC psSE_Context, TgRSIZE_C uiView_Index )
{
    TgFX_DATA_INST_ID                   tiActive;
    ETgFX_UPDATE                        enUpdate;
    T_NAME(STg2_FX__,_P)                psEffect;

    PROFILE_START( T_TYPE(FX_, _SCENE__FINISH_TOTAL), T_NAME(tgFX__Scene__,_Finish) );

    for (enUpdate = ETgFX_UPDATE__BEGIN; enUpdate < ETgFX_UPDATE__END; enUpdate = (ETgFX_UPDATE)((TgSINT_E32)enUpdate + 1))
    {
        tiActive = T_NAME(g_atiFX__,__Scene__Mesh_Head)[enUpdate];

        while (KTgID__INVALID_VALUE != tiActive.m_uiKI)
        {
            T_NAME(tgFX__Scene__,_Cull__Insert_Frame_Mesh)( psSE_Context, uiView_Index, tiActive );
            psEffect = T_NAME(g_asFX__,) + tiActive.m_uiI;
            tiActive = psEffect->m_tiNext[ETgFX_NEXT__SCENE];
        };
    };

    PROFILE_STOP( T_TYPE(FX_, _SCENE__FINISH_TOTAL), T_NAME(tgFX__Scene__,_Finish) );
}
/*# T_EFFECT_RENDER */
#endif


/* ---- tgFX__Scene__Job__,_Finish ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if T_EFFECT_RENDER
static TgRESULT T_NAME(tgFX__Scene__Job__,_Finish)( STg2_Job_CPC psJob )
{
    union
    {
        STg2_FX_Job__Scene__Finish_CP       psJob;
        TgUINT_E08_CP                       pui;
    }                                   psData;

    TgERROR(0 == T_TYPE(g_xuiFX_FENCE__SCENE__CULL__,));

    psData.pui = psJob->m_auiData;

    T_NAME(tgFX__Scene__,_Finish)( psData.psJob->m_psScene_Context, psData.psJob->m_uiView_Index );

    TgSTD_ATOMIC(fetch_sub)( &g_xuiFX_FENCE__SCENE, 1 );
    TgSTD_ATOMIC(fetch_sub)( &g_xuiFX_FENCE__SCENE__FINISH, 1 );

    return (KTgS_OK);
}
/*# T_EFFECT_RENDER */
#endif

/*# T_EFFECT_SCENE */
#endif

/*# defined (ENABLE_RELOAD_GUARD) */
#endif
