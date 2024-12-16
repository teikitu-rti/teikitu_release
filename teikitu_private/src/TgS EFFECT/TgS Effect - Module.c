/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Effect - Module.c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.12 | »GUID« 964CB1A6-814D-4E19-8E67-A83FCA98BF05 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Effects ==================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

static TgVOID                               tgFX__Client__Flush_Deleted_Effects( TgVOID );
static TgVOID                               tgFX__Client__Flush_New_Effect_List( TgVOID );

static ETgMODULE_STATE                      s_enEffect_State = ETgMODULE_STATE__FREED;




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgFX_Module_Init --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgFX_Module_Init( TgVOID )
{
    TgUINT_E32                          uiIndex;

    /* Verify the state of the system */
    TgERROR( ETgMODULE_STATE__FREED == s_enEffect_State );
    s_enEffect_State = ETgMODULE_STATE__INITIALIZING;

    PROFILE_INIT( FX_COMMANDS__CLIENT );
    PROFILE_ARRAY_INIT( 0, DEFAULT, FX_UPDATE__UPDATE );
    PROFILE_ARRAY_INIT( 1, EXTERNAL, FX_UPDATE__UPDATE );
    PROFILE_ARRAY_INIT( 2, NEW, FX_UPDATE__UPDATE );
    PROFILE_ARRAY_INIT( 3, FINISH, FX_UPDATE__UPDATE );
    PROFILE_INIT( FX_RENDER_PATCH_CONTEXT );
    PROFILE_INIT( FX_RENDER_PROCESS_COMMANDS );
    PROFILE_INIT( FX_RENDER_GENERATE );
    
    g_fFX_Quality_Setting = 1.0F;
    g_tiFX_CN__Quality_Setting = KTgCN_VAR_ID__INVALID;
    g_fFX_Alpha_Threshold = 0.0F;
    g_tiFX_CN__Alpha_Threshold = KTgCN_VAR_ID__INVALID;
    g_uiFX_Decal_Memory_Max = 1024*1024;
    g_tiFX_CN__Decal_Memory_Max = KTgCN_VAR_ID__INVALID;
    g_fFX_Decal_Normal_Threshold = 0.0F;
    g_tiFX_CN__Decal_Normal_Threshold = KTgCN_VAR_ID__INVALID;
    g_uiFX_Emitter_Memory_Max = 2048*1024;
    g_tiFX_CN__Emitter_Memory_Max = KTgCN_VAR_ID__INVALID;

    TgSTD_ATOMIC(store)( &g_xuiFX_FENCE__UPDATE, 0 );
    TgSTD_ATOMIC(store)( &g_xuiFX_FENCE__UPDATE__UPDATE, 0 );
    TgSTD_ATOMIC(store)( &g_xuiFX_FENCE__UPDATE__FINISH, 0 );
    TgSTD_ATOMIC(store)( &g_xuiFX_FENCE__SCENE, 0 );
    TgSTD_ATOMIC(store)( &g_xuiFX_FENCE__SCENE__REFRESH_BA, 0 );
    TgSTD_ATOMIC(store)( &g_xuiFX_FENCE__RENDER, 0 );
    TgSTD_ATOMIC(store)( &g_xuiFX_FENCE__RENDER__PROCESS_HEADERS, 0 );
    TgSTD_ATOMIC(store)( &g_xuiFX_FENCE__RENDER__ALLOCATE, 0 );
    TgSTD_ATOMIC(store)( &g_xuiFX_FENCE__RENDER__GENERATE, 0 );

    tgMM_Set_U08_0x00( g_apsFX_Descriptor, sizeof( g_apsFX_Descriptor ) );

#if defined(TgBUILD_FEATURE__GRAPHICS_VFX)
    g_uiParticle_Header_Index = 0;
/*# defined(TgBUILD_FEATURE__GRAPHICS_VFX) */
#endif

    for (uiIndex = 0; uiIndex < KTgFX_MAX_EFFECT_INSTANCE; ++uiIndex)
    {
        g_aiFX__Client__Shared_State[uiIndex] = ETgFX_EFFECT_STATE__CLIENT__FREE;
    };
    tgCM_UT_LF__ST__Init( &g_sFX_Effect__Client__Effect.m_sStack );

    for (uiIndex = KTgFX_MAX_EFFECT_INSTANCE - 1; uiIndex != KTgMAX_U32; --uiIndex)
    {
        tgCM_UT_LF__ST__Push( &g_sFX_Effect__Client__Effect.m_sStack, (STg2_UT_ST__ST_Node_P)(g_asFX_Effect + uiIndex) );
    };

    for (uiIndex = 0; uiIndex < ETgFX_UPDATE__MAX; ++uiIndex)
    {
        g_atiFX__Client__Update__Head[uiIndex] = KTgFX_CLIENT_INST_ID__INVALID;
    };
    g_niFX__Client__Update__Active = 0;

    g_tiFX_File_Default = KTgFX_EFFECT_ID__INVALID;
    g_tiFX_File_Error = KTgFX_EFFECT_ID__INVALID;

    tgMM_Set_U08_0x00( g_asFX_KN_File__Effect, sizeof( g_asFX_KN_File__Effect ) );
    for (uiIndex = 0; uiIndex < ETgFX_DATA__EFFECT_MAX; ++uiIndex)
    {
        g_auiFX_KN_File__Effect_Hash[uiIndex] = KTgEMPTY_HASH;
        tgFX_EFFECT_ID_Invalidate( &g_asFX_KN_File__Effect[uiIndex].m_tiEffect_Singleton );
        g_asFX_KN_File__Effect[uiIndex].m_tiFile = KTgKN_FILE_ID__INVALID;
    };

    /* #FIX: Add tgFX_Load_File__Bind_Effect to Kernel, tgFX_Load_File__UnBind_Effect */

    TgSTD_ATOMIC(store)( &g_xuiFX__Decal__Memory_Current, 0 );
    TgSTD_ATOMIC(store)( &g_xuiFX__Emitter__Memory_Current, 0 );

    tgFX__Client__Beam_Init();
    tgFX__Client__Billboard_Init();
    tgFX__Client__Decal_Init();
    tgFX__Client__Emitter_Init();
    tgFX__Client__GIB_Init();
    tgFX__Client__Glass_Init();
    tgFX__Client__Group_Init();
    tgFX__Client__Light_Init();
    tgFX__Client__Liquid_Init();
    tgFX__Client__Post_Init();
    tgFX__Client__Sound_Init();
    tgFX__Client__Trail_Init();

#if TgS_DEBUG__EFFECT
    g_tiFX_Debug__OSD__Profile_Enable = KTgCN_VAR_ID__INVALID;
    g_tiFX_Debug__OSD__Profile_Sort = KTgCN_VAR_ID__INVALID;
    g_tiFX_Debug__Draw_BA = KTgCN_VAR_ID__INVALID;
    g_tiFX_Debug__Draw_Emitter = KTgCN_VAR_ID__INVALID;
    g_tiFX_Debug__Emitter__Draw_Debug_Colour = KTgCN_VAR_ID__INVALID;
    g_tiFX_Debug__Disable_Module = KTgCN_VAR_ID__INVALID;
    g_tiFX_Debug__Disable_Update = KTgCN_VAR_ID__INVALID;
    g_tiFX_Debug__Disable_Render = KTgCN_VAR_ID__INVALID;
    g_tiFX_Debug__Disable_Render_Buffer = KTgCN_VAR_ID__INVALID;
    g_tiFX_Debug__Disable_Cull_On_Spawn = KTgCN_VAR_ID__INVALID;
    g_tiFX_Debug__Disable_Cull_On_Render = KTgCN_VAR_ID__INVALID;
    tgMM_Set_U08_0x00( g_aszFX_Cache__EFfect_Name, sizeof( g_aszFX_Cache__EFfect_Name ) );
/*# TgS_DEBUG__EFFECT */
#endif

    tgFX_Load_Config();

    s_enEffect_State = ETgMODULE_STATE__INITIALIZED;
    return (KTgS_OK);
}


/* ---- tgFX_Module_Boot --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgFX_Module_Boot( TgVOID )
{
    TgERROR( ETgMODULE_STATE__INITIALIZED == s_enEffect_State );
    s_enEffect_State = ETgMODULE_STATE__BOOTING;

    LOG_STD_MSG_USZ_FMTU64( KTgCN_CHANEL_INITIALIZE_MEMORY, u8"Static Memory Size", tgFX_Query_Fixed_Memory() )

    tgFX__Client__Beam_Boot();
    tgFX__Client__Billboard_Boot();
    tgFX__Client__Decal_Boot();
    tgFX__Client__Emitter_Boot();
    tgFX__Client__GIB_Boot();
    tgFX__Client__Glass_Boot();
    tgFX__Client__Group_Boot();
    tgFX__Client__Light_Boot();
    tgFX__Client__Liquid_Boot();
    tgFX__Client__Post_Boot();
    tgFX__Client__Sound_Boot();
    tgFX__Client__Trail_Boot();

    /* #FIX: g_tiFX_File_Default = tgFX_Load_File( 0, nullptr, 0, nullptr ); */
    /* #FIX: g_tiFX_File_Error = tgFX_Load_File( 0, nullptr, 0, nullptr ); */

    s_enEffect_State = ETgMODULE_STATE__BOOTED;
    return (KTgS_OK);
}


/* ---- tgFX_Module_Stop --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgFX_Module_Stop( TgVOID )
{
    TgUINT_E32                          uiIndex;

    if ((ETgMODULE_STATE__FREED == s_enEffect_State) || (ETgMODULE_STATE__INITIALIZED == s_enEffect_State))
    {
        return;
    };

    TgERROR( ETgMODULE_STATE__BOOTED == s_enEffect_State );
    s_enEffect_State = ETgMODULE_STATE__STOPPING;

    for (uiIndex = 0; uiIndex < KTgFX_MAX_EFFECT_INSTANCE; ++uiIndex)
    {
        if (g_aiFX__Client__Shared_State[uiIndex] < ETgFX_EFFECT_STATE__CLIENT__ACTIVE)
        {
            continue;
        };

        tgFX__Client__Free_Internal( uiIndex );
    };

    tgFX__Client__Trail_Stop();
    tgFX__Client__Sound_Stop();
    tgFX__Client__Post_Stop();
    tgFX__Client__Liquid_Stop();
    tgFX__Client__Light_Stop();
    tgFX__Client__Group_Stop();
    tgFX__Client__Glass_Stop();
    tgFX__Client__GIB_Stop();
    tgFX__Client__Emitter_Stop();
    tgFX__Client__Decal_Stop();
    tgFX__Client__Billboard_Stop();
    tgFX__Client__Beam_Stop();

    for (uiIndex = 0; uiIndex < ETgFX_DATA__EFFECT_MAX; ++uiIndex)
    {
        if (KTgEMPTY_HASH == g_auiFX_KN_File__Effect_Hash[uiIndex])
        {
            continue;
        };

        if (0 != g_asFX_KN_File__Effect[uiIndex].m_nuiReference)
        {
            TgWARNING_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"FX Cache Stopping with active instances.\n" );
        };

        g_auiFX_KN_File__Effect_Hash[uiIndex] = KTgEMPTY_HASH;

        //tgKN_File__Decrement_Reference( g_asFX_KN_File__Effect[uiIndex].m_tiFile );
        g_asFX_KN_File__Effect[uiIndex].m_tiFile = KTgKN_FILE_ID__INVALID;
        tgFX_EFFECT_ID_Invalidate( &g_asFX_KN_File__Effect[uiIndex].m_tiEffect_Singleton );
    };

    s_enEffect_State = ETgMODULE_STATE__STOPPED;
}


/* ---- tgFX_Module_Free --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgFX_Module_Free( TgVOID )
{
    if (ETgMODULE_STATE__FREED == s_enEffect_State)
    {
        return;
    };

    TgERROR( ETgMODULE_STATE__STOPPED == s_enEffect_State || ETgMODULE_STATE__INITIALIZED == s_enEffect_State );
    s_enEffect_State = ETgMODULE_STATE__FREEING;

    tgFX__Client__Trail_Free();
    tgFX__Client__Sound_Free();
    tgFX__Client__Post_Free();
    tgFX__Client__Liquid_Free();
    tgFX__Client__Light_Free();
    tgFX__Client__Group_Free();
    tgFX__Client__Glass_Free();
    tgFX__Client__GIB_Free();
    tgFX__Client__Emitter_Free();
    tgFX__Client__Decal_Free();
    tgFX__Client__Billboard_Free();
    tgFX__Client__Beam_Free();

    TgERROR( KTgID__INVALID_VALUE == g_tiFX_File_Error.m_uiKI );
    TgERROR( KTgID__INVALID_VALUE == g_tiFX_File_Default.m_uiKI );

    s_enEffect_State = ETgMODULE_STATE__FREED;
}


/* ---- tgFX_Module_Update ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* NOTE: Execute all ToClient Commands, Remove all deleted effects from lists, Add all new effects to update lists */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgFX_Module_Update( TgATTRIBUTE_UNUSED TgFLOAT32_C fDT )
{
    TgUN_SCALAR                         uVal;

    if ((KTgID__INVALID_VALUE != g_tiFX_CN__Quality_Setting.m_uiKI) && tgCN_Var_Query_F32( &uVal.m_f32, g_tiFX_CN__Quality_Setting ))
    {
        g_fFX_Quality_Setting = uVal.m_f32;
    };

    if ((KTgID__INVALID_VALUE != g_tiFX_CN__Alpha_Threshold.m_uiKI) && tgCN_Var_Query_F32( &uVal.m_f32, g_tiFX_CN__Alpha_Threshold ))
    {
        g_fFX_Alpha_Threshold = uVal.m_f32;
    };

    if ((KTgID__INVALID_VALUE != g_tiFX_CN__Decal_Memory_Max.m_uiKI) && tgCN_Var_Query_U64( &uVal.m_uiE64, g_tiFX_CN__Decal_Memory_Max ))
    {
        g_uiFX_Decal_Memory_Max = uVal.m_uiE64;
    };

    if ((KTgID__INVALID_VALUE != g_tiFX_CN__Emitter_Memory_Max.m_uiKI) && tgCN_Var_Query_U64( &uVal.m_uiE64, g_tiFX_CN__Emitter_Memory_Max ))
    {
        g_uiFX_Emitter_Memory_Max = uVal.m_uiE64;
    };

    if ((KTgID__INVALID_VALUE != g_tiFX_CN__Decal_Normal_Threshold.m_uiKI) && tgCN_Var_Query_F32( &uVal.m_f32, g_tiFX_CN__Decal_Normal_Threshold ))
    {
        g_fFX_Decal_Normal_Threshold = uVal.m_f32;
    };

#if TgS_DEBUG__EFFECT
    {
        TgBOOL                              bDisable;
        if ((tgCN_Var_Query_Bool( &bDisable, g_tiFX_Debug__Disable_Module )) && (bDisable))
            return (KTgS_OK);
    }
/*# TgS_DEBUG__EFFECT */
#endif

    while (0 != TgSTD_ATOMIC(load)( &g_xuiFX_FENCE__RENDER ))
    {
        tgTR_Sleep( 500 );
    }

    TgERROR( 0 == TgSTD_ATOMIC(load)( &g_xuiFX_FENCE__UPDATE ) );
    TgERROR( 0 == TgSTD_ATOMIC(load)( &g_xuiFX_FENCE__SCENE ) );
    TgERROR( 0 == TgSTD_ATOMIC(load)( &g_xuiFX_FENCE__RENDER ) );
    
    {
        PROFILE_START(FX_COMMANDS__CLIENT, tgFX_Module_Update);
        tgFX__Client__Process_ToClient_Command_Buffer();
        tgFX__Client__Flush_Deleted_Effects();
        tgFX__Client__Flush_New_Effect_List(); /* #TODO: Move effects from new to update */
        PROFILE_STOP( FX_COMMANDS__CLIENT, tgFX_Module_Update );
    }

    return (KTgS_OK);
}


/* ---- tgFX_Load_Config --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgFX_Load_Config( TgVOID )
{
    g_tiFX_CN__Quality_Setting = tgCN_Var_Init_F32( u8"FX Quality_Setting", KTgMAX_RSIZE, u8"Configuration: 1.0 is Normal", KTgMAX_RSIZE, KTgCN_VAR_DEVELOPMENT,
                                                    g_fFX_Quality_Setting, 0.0F, 1.0F );

    g_tiFX_CN__Alpha_Threshold = tgCN_Var_Init_F32( u8"FX Alpha Threshold", KTgMAX_RSIZE, u8"Below this value the effect will not draw", KTgMAX_RSIZE, KTgCN_VAR_DEVELOPMENT,
                                                    g_fFX_Alpha_Threshold, 0.0F, 1.0F );

    g_tiFX_CN__Decal_Memory_Max = tgCN_Var_Init_U64( u8"FX Decal Memory Max", KTgMAX_RSIZE, u8"Max Amount of Memory that Decals will consume in MB", KTgMAX_RSIZE,
                                                     KTgCN_VAR_DEVELOPMENT, g_uiFX_Decal_Memory_Max, 0, 4096*1024 );

    g_tiFX_CN__Decal_Normal_Threshold = tgCN_Var_Init_F32( u8"FX Decal Normal Threshold", KTgMAX_RSIZE, u8"Below this value the decal face will fade out", KTgMAX_RSIZE,
                                                           KTgCN_VAR_DEVELOPMENT, g_fFX_Decal_Normal_Threshold, 0.0F, 1.0F );

    g_tiFX_CN__Emitter_Memory_Max = tgCN_Var_Init_U64( u8"FX Emitter Memory Max", KTgMAX_RSIZE, u8"Max Amount of Memory that Emitters will consume in MB", KTgMAX_RSIZE,
                                                       KTgCN_VAR_DEVELOPMENT, g_uiFX_Emitter_Memory_Max, 0, 4096*1024 );

#if TgS_DEBUG__EFFECT
    tgFX_Debug__Load_Config();
#endif

    return (KTgS_OK);
}


/* ---- tgFX_Save_Config --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgFX_Save_Config( TgVOID )
{
    TgUN_SCALAR                         uVal;
    TgUINT_MAX                          uiFX;

    tgUSZ_Hash( &uiFX, u8"FX", KTgMAX_RSIZE );
    if ((KTgID__INVALID_VALUE != g_tiFX_CN__Quality_Setting.m_uiKI) && tgCN_Var_Query_F32( &uVal.m_f32, g_tiFX_CN__Quality_Setting ))
    {
        g_fFX_Quality_Setting = uVal.m_f32;
    };

    if ((KTgID__INVALID_VALUE != g_tiFX_CN__Alpha_Threshold.m_uiKI) && tgCN_Var_Query_F32( &uVal.m_f32, g_tiFX_CN__Alpha_Threshold ))
    {
        g_fFX_Alpha_Threshold = uVal.m_f32;
    };

    if ((KTgID__INVALID_VALUE != g_tiFX_CN__Decal_Memory_Max.m_uiKI) && tgCN_Var_Query_U64( &uVal.m_uiE64, g_tiFX_CN__Decal_Memory_Max ))
    {
        g_uiFX_Decal_Memory_Max = uVal.m_uiE64;
    };

    if ((KTgID__INVALID_VALUE != g_tiFX_CN__Emitter_Memory_Max.m_uiKI) && tgCN_Var_Query_U64( &uVal.m_uiE64, g_tiFX_CN__Emitter_Memory_Max ))
    {
        g_uiFX_Emitter_Memory_Max = uVal.m_uiE64;
    };

    if ((KTgID__INVALID_VALUE != g_tiFX_CN__Decal_Normal_Threshold.m_uiKI) && tgCN_Var_Query_F32( &uVal.m_f32, g_tiFX_CN__Decal_Normal_Threshold ))
    {
        g_fFX_Decal_Normal_Threshold = uVal.m_f32;
    };

    return (KTgS_OK);
}


/* ---- tgFX_Query_Init ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgFX_Query_Init( TgVOID )
{
    return (ETgMODULE_STATE__INITIALIZED <= s_enEffect_State && s_enEffect_State <= ETgMODULE_STATE__STOPPED);
}


/* ---- tgFX_Query_Boot ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgFX_Query_Boot( TgVOID )
{
    return (ETgMODULE_STATE__BOOTED == s_enEffect_State);
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgFX__Client__Flush_Deleted_Effect --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgFX__Client__Flush_Deleted_Effects( TgVOID )
{
    TgFX_CLIENT_INST_ID                 tiPrev_Client;
    TgFX_CLIENT_INST_ID                 tiCurrent_Client;
    TgFX_CLIENT_INST_ID                 tiNext_Client;
    TgUINT_E32                          uiIndex;

    for (uiIndex = 0; uiIndex < ETgFX_UPDATE__NEW_CLIENT; ++uiIndex)
    {
        tiPrev_Client = KTgFX_CLIENT_INST_ID__INVALID;
        tiCurrent_Client = g_atiFX__Client__Update__Head[uiIndex];

        while (KTgID__INVALID_VALUE != tiCurrent_Client.m_uiKI)
        {
            tiNext_Client = g_asFX_Effect[tiCurrent_Client.m_uiI].m_tiUpdate_Next;

            /* Clear out all effects that were marked for delete in the last frame */
            if (!tgFX_CLIENT_INST_ID_Is_Equal( &g_asFX_Effect[tiCurrent_Client.m_uiI].m_tiClient_Singleton, tiCurrent_Client ))
            {
                if (KTgID__INVALID_VALUE != tiPrev_Client.m_uiKI)
                {
                    g_asFX_Effect[tiPrev_Client.m_uiI].m_tiUpdate_Next = tiNext_Client;
                }
                else
                {
                    g_atiFX__Client__Update__Head[uiIndex] = tiNext_Client;
                };
                tgCM_UT_LF__ST__Push( &g_sFX_Effect__Client__Effect.m_sStack, (STg2_UT_ST__ST_Node_P)(g_asFX_Effect + tiCurrent_Client.m_uiI) );
            }
            else
            {
                tiPrev_Client = tiCurrent_Client;
            };

            tiCurrent_Client = tiNext_Client;
        };
    };
}


/* ---- tgFX__Client__Flush_New_Effect_List -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgFX__Client__Flush_New_Effect_List( TgVOID )
{
    TgFX_CLIENT_INST_ID                 tiCurrent_Client;
    TgFX_CLIENT_INST_ID                 tiNext_Client;

    tiCurrent_Client = g_atiFX__Client__Update__Head[ETgFX_UPDATE__NEW_CLIENT];

    while (KTgID__INVALID_VALUE != tiCurrent_Client.m_uiKI)
    {
        tiNext_Client = g_asFX_Effect[tiCurrent_Client.m_uiI].m_tiUpdate_Next;

        /* Clear out all effects that were marked for delete in the last frame */
        if (!tgFX_CLIENT_INST_ID_Is_Equal( &g_asFX_Effect[tiCurrent_Client.m_uiI].m_tiClient_Singleton, tiCurrent_Client ))
        {
            tgCM_UT_LF__ST__Push( &g_sFX_Effect__Client__Effect.m_sStack, (STg2_UT_ST__ST_Node_P)(g_asFX_Effect + tiCurrent_Client.m_uiI) );
        }
        else
        {
            TgERROR_INDEX( g_asFX_Effect[tiCurrent_Client.m_uiI].m_uiUpdate, g_atiFX__Client__Update__Head );
            g_asFX_Effect[tiCurrent_Client.m_uiI].m_tiUpdate_Next = g_atiFX__Client__Update__Head[g_asFX_Effect[tiCurrent_Client.m_uiI].m_uiUpdate];
            g_atiFX__Client__Update__Head[g_asFX_Effect[tiCurrent_Client.m_uiI].m_uiUpdate] = tiCurrent_Client;
        };

        tiCurrent_Client = tiNext_Client;
    };

    g_atiFX__Client__Update__Head[ETgFX_UPDATE__NEW_CLIENT] = KTgFX_CLIENT_INST_ID__INVALID;
}
