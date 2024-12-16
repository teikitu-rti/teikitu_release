/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Effect - System.c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.12 | »GUID« 964CB1A6-814D-4E19-8E67-A83FCA98BF05 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Effects ==================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

static TgVOID
tgFX__Update__Group__Update_Command__Process_Command(
    ETgFX_COMMAND_C, TgVOID_CP );

static TgVOID
tgFX__Client__ToClient__Process_Command_Internal(
    TgUINT_F08_P, TgRSIZE );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgFX__Client__Update_1 --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgFX__Client__Update_1( TgFLOAT32_C fDT )
{
    TgVEC_F32_04_1                    vDT;

#if TgS_DEBUG__EFFECT
    TgBOOL                              bDisable;
    if ((tgCN_Var_Query_Bool( &bDisable, g_tiFX_Debug__Disable_Update )) && (bDisable))
        return;
/*# TgS_DEBUG__EFFECT */
#endif

    TgERROR( 0 == atomic_load( &g_xuiFX_FENCE__UPDATE ) );
    TgERROR( 0 == atomic_load( &g_xuiFX_FENCE__SCENE ) );
    TgERROR( 0 == atomic_load( &g_xuiFX_FENCE__RENDER ) );

    vDT = tgMH_SET1_F32_04_1( fDT );

    tgFX__Client__Collect_Collision_Results( false );

    tgFX__Client__Submit_Job__Beam_Update( vDT, fDT, ETgFX_UPDATE__DEFAULT );
    tgFX__Client__Submit_Job__Billboard_Update( vDT, fDT, ETgFX_UPDATE__DEFAULT );
    tgFX__Client__Submit_Job__Decal_Update( vDT, fDT, ETgFX_UPDATE__DEFAULT );
    tgFX__Client__Submit_Job__Emitter_Update( vDT, fDT, ETgFX_UPDATE__DEFAULT );
    tgFX__Client__Submit_Job__GIB_Update( vDT, fDT, ETgFX_UPDATE__DEFAULT );
    tgFX__Client__Submit_Job__Glass_Update( vDT, fDT, ETgFX_UPDATE__DEFAULT );
    tgFX__Client__Submit_Job__Group_Update( vDT, fDT, ETgFX_UPDATE__DEFAULT );
    tgFX__Client__Submit_Job__Light_Update( vDT, fDT, ETgFX_UPDATE__DEFAULT );
    tgFX__Client__Submit_Job__Liquid_Update( vDT, fDT, ETgFX_UPDATE__DEFAULT );
    tgFX__Client__Submit_Job__Post_Update( vDT, fDT, ETgFX_UPDATE__DEFAULT );
    tgFX__Client__Submit_Job__Sound_Update( vDT, fDT, ETgFX_UPDATE__DEFAULT );
    tgFX__Client__Submit_Job__Trail_Update( vDT, fDT, ETgFX_UPDATE__DEFAULT );
}


/* ---- tgFX__Client__Update_2 --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgFX__Client__Update_2( TgFLOAT32_C fDT )
{
    TgVEC_F32_04_1                    vDT;

    /* In case of overflow - flush the command queue.  Impact to state consistency is unknown. */
    if (0 != g_xuiFX_Fence__CLIENT_TO_UPDATE__COMMAND_QUEUE_FULL)
    {
        tgFX__Client__Process_ToClient_Command_Buffer();
        TgVERIFY( 0 != atomic_exchange( &g_xuiFX_Fence__CLIENT_TO_UPDATE__COMMAND_QUEUE_FULL, 0 ) );
    };

#if TgS_DEBUG__EFFECT
    {
        TgBOOL                              bDisable;
        if ((tgCN_Var_Query_Bool( &bDisable, g_tiFX_Debug__Disable_Update )) && (bDisable))
            return;
    }
/*# TgS_DEBUG__EFFECT */
#endif

    TgERROR( 0 == atomic_load( &g_xuiFX_FENCE__SCENE ) );
    TgERROR( 0 == atomic_load( &g_xuiFX_FENCE__RENDER ) );

    tgFX__Client__Update_From_External_Module_Data( fDT );

    tgFX__Client__Collect_Collision_Results( false );

    vDT = tgMH_SET1_F32_04_1( fDT );

    tgFX__Client__Submit_Job__Beam_Update( vDT, fDT, ETgFX_UPDATE__EXTERNAL );
    tgFX__Client__Submit_Job__Billboard_Update( vDT, fDT, ETgFX_UPDATE__EXTERNAL );
    tgFX__Client__Submit_Job__Decal_Update( vDT, fDT, ETgFX_UPDATE__EXTERNAL );
    tgFX__Client__Submit_Job__Emitter_Update( vDT, fDT, ETgFX_UPDATE__EXTERNAL );
    tgFX__Client__Submit_Job__GIB_Update( vDT, fDT, ETgFX_UPDATE__EXTERNAL );
    tgFX__Client__Submit_Job__Glass_Update( vDT, fDT, ETgFX_UPDATE__EXTERNAL );
    tgFX__Client__Submit_Job__Group_Update( vDT, fDT, ETgFX_UPDATE__EXTERNAL );
    tgFX__Client__Submit_Job__Light_Update( vDT, fDT, ETgFX_UPDATE__EXTERNAL );
    tgFX__Client__Submit_Job__Liquid_Update( vDT, fDT, ETgFX_UPDATE__EXTERNAL );
    tgFX__Client__Submit_Job__Post_Update( vDT, fDT, ETgFX_UPDATE__EXTERNAL );
    tgFX__Client__Submit_Job__Sound_Update( vDT, fDT, ETgFX_UPDATE__EXTERNAL );
    tgFX__Client__Submit_Job__Trail_Update( vDT, fDT, ETgFX_UPDATE__EXTERNAL );
}


/* ---- tgFX__Client__Update_Finish ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgFX__Client__Update_Finish( TgVOID )
{
    TgERROR( 0 == atomic_load( &g_xuiFX_FENCE__SCENE ) );
    TgERROR( 0 == atomic_load( &g_xuiFX_FENCE__RENDER ) );

    tgFX__Client__Submit_Job__Beam_Update_Finish();
    tgFX__Client__Submit_Job__Billboard_Update_Finish();
    tgFX__Client__Submit_Job__Decal_Update_Finish();
    tgFX__Client__Submit_Job__Emitter_Update_Finish();
    tgFX__Client__Submit_Job__GIB_Update_Finish();
    tgFX__Client__Submit_Job__Glass_Update_Finish();
    tgFX__Client__Submit_Job__Group_Update_Finish();
    tgFX__Client__Submit_Job__Light_Update_Finish();
    tgFX__Client__Submit_Job__Liquid_Update_Finish();
    tgFX__Client__Submit_Job__Post_Update_Finish();
    tgFX__Client__Submit_Job__Sound_Update_Finish();
    tgFX__Client__Submit_Job__Trail_Update_Finish();

    tgFX__Client__Submit_Job__Beam_Refresh_BA();
    tgFX__Client__Submit_Job__Billboard_Refresh_BA();
    tgFX__Client__Submit_Job__Decal_Refresh_BA();
    tgFX__Client__Submit_Job__Emitter_Refresh_BA();
    tgFX__Client__Submit_Job__GIB_Refresh_BA();
    tgFX__Client__Submit_Job__Glass_Refresh_BA();
    tgFX__Client__Submit_Job__Light_Refresh_BA();
    tgFX__Client__Submit_Job__Liquid_Refresh_BA();
    tgFX__Client__Submit_Job__Post_Refresh_BA();
    tgFX__Client__Submit_Job__Trail_Refresh_BA();
}


/* ---- tgFX__Client__Scene_Cull ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if defined(TgBUILD_FEATURE__GRAPHICS_VFX)
TgVOID tgFX__Client__Scene_Cull( STg2_SE_Context_PC psScene_Context, TgRSIZE_C uiView_Index )
{
    TgERROR( 0 == atomic_load( &g_xuiFX_FENCE__RENDER ) );

    /* In case of overflow - flush the command queue.  Impact to state consistency is unknown. */
    if (0 != g_xuiFX_Fence__CLIENT_TO_UPDATE__COMMAND_QUEUE_FULL)
    {
        tgFX__Client__Process_ToClient_Command_Buffer();
        TgVERIFY( 0 != atomic_exchange( &g_xuiFX_Fence__CLIENT_TO_UPDATE__COMMAND_QUEUE_FULL, 0 ) );
    };

#if TgS_DEBUG__EFFECT
    {
        TgBOOL                              bDisable;
        if ((tgCN_Var_Query_Bool( &bDisable, g_tiFX_Debug__Disable_Render )) && (bDisable))
            return;
    }
/*# TgS_DEBUG__EFFECT */
#endif

    tgFX__Client__Submit_Job__Beam_Scene_Cull( psScene_Context, uiView_Index );
    tgFX__Client__Submit_Job__Billboard_Scene_Cull( psScene_Context, uiView_Index );
    tgFX__Client__Submit_Job__Decal_Scene_Cull( psScene_Context, uiView_Index );
    tgFX__Client__Submit_Job__Emitter_Scene_Cull( psScene_Context, uiView_Index );
    tgFX__Client__Submit_Job__GIB_Scene_Cull( psScene_Context, uiView_Index );
    tgFX__Client__Submit_Job__Glass_Scene_Cull( psScene_Context, uiView_Index );
    tgFX__Client__Submit_Job__Liquid_Scene_Cull( psScene_Context, uiView_Index );
    tgFX__Client__Submit_Job__Trail_Scene_Cull( psScene_Context, uiView_Index );
}
/*# defined(TgBUILD_FEATURE__GRAPHICS_VFX) */
#endif


/* ---- tgFX__Render__Update ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if defined(TgBUILD_FEATURE__GRAPHICS_VFX)
TgVOID tgFX__Render__Update( STg2_FX_Rnd_Output_PC psRndOut )
{
    TgERROR( 0 == atomic_load( &g_xuiFX_FENCE__RENDER__PROCESS_HEADERS ) );
    TgERROR( 0 == atomic_load( &g_xuiFX_FENCE__RENDER__ALLOCATE ) );
    TgERROR( 0 == atomic_load( &g_xuiFX_FENCE__RENDER__GENERATE ) );

#if TgS_DEBUG__EFFECT
    {
        TgBOOL                              bDisable;
        if ((tgCN_Var_Query_Bool( &bDisable, g_tiFX_Debug__Disable_Render )) && (bDisable))
            return;
    }
/*# TgS_DEBUG__EFFECT */
#endif

    g_uiParticle_Header_Index = (g_uiParticle_Header_Index + KTgFX_MAX_RENDER_INSTANCE) % (TgARRAY_COUNT( g_asParticle_Header ));

    tgFX__Render__Submit_Job__Beam_Process_Headers( psRndOut );
    tgFX__Render__Submit_Job__Billboard_Process_Headers( psRndOut );
    tgFX__Render__Submit_Job__Decal_Process_Headers( psRndOut );
    tgFX__Render__Submit_Job__Emitter_Process_Headers( psRndOut );
    tgFX__Render__Submit_Job__GIB_Process_Headers( psRndOut );
    tgFX__Render__Submit_Job__Glass_Process_Headers( psRndOut );
    tgFX__Render__Submit_Job__Liquid_Process_Headers( psRndOut );
    tgFX__Render__Submit_Job__Trail_Process_Headers( psRndOut );

#if TgS_DEBUG__EFFECT
    {
        TgBOOL                              bDisable;
        if ((tgCN_Var_Query_Bool( &bDisable, g_tiFX_Debug__Disable_Render_Buffer )) && (bDisable))
            return;
    }
/*# TgS_DEBUG__EFFECT */
#endif

    tgFX__Render__Submit_Job__Allocate_Render_Buffers( psRndOut ); /* Determine the particles that will actually be generated based on memory requirements and priority */

    tgFX__Render__Submit_Job__Beam_Render_Generate( psRndOut );
    tgFX__Render__Submit_Job__Billboard_Render_Generate( psRndOut );
    tgFX__Render__Submit_Job__Decal_Render_Generate( psRndOut );
    tgFX__Render__Submit_Job__Emitter_Render_Generate( psRndOut );
    tgFX__Render__Submit_Job__GIB_Render_Generate( psRndOut );
    tgFX__Render__Submit_Job__Glass_Render_Generate( psRndOut );
    tgFX__Render__Submit_Job__Liquid_Render_Generate( psRndOut );
    tgFX__Render__Submit_Job__Trail_Render_Generate( psRndOut );
}
/*# defined(TgBUILD_FEATURE__GRAPHICS_VFX) */
#endif




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgFX__Client__Process_ToClient_Command_Buffer ---------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgFX__Client__Process_ToClient_Command_Buffer( TgVOID )
{
    tgFX__Client__ToClient__Process_Command_Internal( g_asFX_Command__Beam__ToClient, atomic_load( &g_xuiFX_Command__Beam__ToClient_Offset ) );
    tgFX__Client__ToClient__Process_Command_Internal( g_asFX_Command__Billboard__ToClient, atomic_load( &g_xuiFX_Command__Billboard__ToClient_Offset ) );
    tgFX__Client__ToClient__Process_Command_Internal( g_asFX_Command__Decal__ToClient, atomic_load( &g_xuiFX_Command__Decal__ToClient_Offset ) );
    tgFX__Client__ToClient__Process_Command_Internal( g_asFX_Command__Emitter__ToClient, atomic_load( &g_xuiFX_Command__Emitter__ToClient_Offset ) );
    tgFX__Client__ToClient__Process_Command_Internal( g_asFX_Command__GIB__ToClient, atomic_load( &g_xuiFX_Command__GIB__ToClient_Offset ) );
    tgFX__Client__ToClient__Process_Command_Internal( g_asFX_Command__Glass__ToClient, atomic_load( &g_xuiFX_Command__Glass__ToClient_Offset ) );
    tgFX__Client__ToClient__Process_Command_Internal( g_asFX_Command__Group__ToClient, atomic_load( &g_xuiFX_Command__Group__ToClient_Offset ) );
    tgFX__Client__ToClient__Process_Command_Internal( g_asFX_Command__Liquid__ToClient, atomic_load( &g_xuiFX_Command__Liquid__ToClient_Offset ) );
    tgFX__Client__ToClient__Process_Command_Internal( g_asFX_Command__Light__ToClient, atomic_load( &g_xuiFX_Command__Light__ToClient_Offset ) );
    tgFX__Client__ToClient__Process_Command_Internal( g_asFX_Command__Sound__ToClient, atomic_load( &g_xuiFX_Command__Sound__ToClient_Offset ) );
    tgFX__Client__ToClient__Process_Command_Internal( g_asFX_Command__Post__ToClient, atomic_load( &g_xuiFX_Command__Post__ToClient_Offset ) );
    tgFX__Client__ToClient__Process_Command_Internal( g_asFX_Command__Trail__ToClient, atomic_load( &g_xuiFX_Command__Trail__ToClient_Offset ) );
}


/* ---- tgFX__Client__Update_From_External_Module_Data --------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgFX__Client__Update_From_External_Module_Data( TgFLOAT32_C fClient_Time_Total )
{
    TgFX_CLIENT_INST_ID                 tiCurrent_Client;

    tiCurrent_Client = g_atiFX__Client__Update__Head[ETgFX_UPDATE__EXTERNAL];

    while (KTgID__INVALID_VALUE != tiCurrent_Client.m_uiKI)
    {
        TgVEC_F32_04_1                    vPos_W;
        TgVEC_F32_04_1                    qRot_W;

        /* Pull update from attachment - kill effects with in valid attachments */
        if (TgFAILED( tgAttachment__Query_Attachment_W( &vPos_W, &qRot_W, g_asFX_Effect[tiCurrent_Client.m_uiI].m_tiAttachment, fClient_Time_Total ) ))
        {
            /* #REVIEW: Attachment is no longer valid - do we kill the effect, move it into the default update list, or leave it */
            g_asFX_Effect[tiCurrent_Client.m_uiI].m_tiAttachment = KTgATTACHMENT_ID__INVALID;
            tgFX__Client__Kill( tiCurrent_Client );
        }
        else
        {
            tgFX__Client__Set_Rotation_From_External_Update( tiCurrent_Client, qRot_W );
            tgFX__Client__Set_Position_From_External_Update( tiCurrent_Client, vPos_W );
        };

        tiCurrent_Client = g_asFX_Effect[tiCurrent_Client.m_uiI].m_tiUpdate_Next;
    };
}


/* ---- tgFX__Client__Collect_Collision_Results ---------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgFX__Client__Collect_Collision_Results( TgBOOL_C UNUSED_PARAM bWait )
{
    /* #TODO: Complete tgFX__Client__Collect_Collision_Results */
}


/* ---- tgFX__Client__Queue_Update_Command --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgFX__Client__Queue_Update_Command( ETgFX__EFFECT_C enEffect, ETgFX_COMMAND_C enCommand, TgVOID_CP pData )
{
    TgBOOL                              bResult;

    TgPARAM_CHECK( ETgFX_COMMAND__CLIENT_TO_UPDATE__BEGIN <= enCommand && ETgFX_COMMAND__CLIENT_TO_UPDATE__END >= enCommand );

    if (ETgFX__GROUP == enEffect && ETgFX_COMMAND__CLIENT_TO_UPDATE__KILL != enCommand)
    {   
        tgFX__Update__Group__Update_Command__Process_Command( enCommand, pData );
        return (true);
    };

    bResult = false;
    switch (enEffect)
    {
        case ETgFX__INVALID:   bResult = tgFX__Client__Emitter_Update_Command( enCommand, pData ); break;
        case ETgFX__BEAM:      bResult = tgFX__Client__Beam_Update_Command( enCommand, pData ); break;
        case ETgFX__BILLBOARD: bResult = tgFX__Client__Billboard_Update_Command( enCommand, pData ); break;
        case ETgFX__DECAL:     bResult = tgFX__Client__Decal_Update_Command( enCommand, pData ); break;
        case ETgFX__EMITTER:   bResult = tgFX__Client__Emitter_Update_Command( enCommand, pData ); break;
        case ETgFX__GIB:       bResult = tgFX__Client__GIB_Update_Command( enCommand, pData ); break;
        case ETgFX__GLASS:     bResult = tgFX__Client__Glass_Update_Command( enCommand, pData ); break;
        case ETgFX__GROUP:     bResult = tgFX__Client__Group_Update_Command( enCommand, pData ); break;
        case ETgFX__LIGHT:     bResult = tgFX__Client__Light_Update_Command( enCommand, pData ); break;
        case ETgFX__LIQUID:    bResult = tgFX__Client__Liquid_Update_Command( enCommand, pData ); break;
        case ETgFX__POST:      bResult = tgFX__Client__Post_Update_Command( enCommand, pData ); break;
        case ETgFX__SOUND:     bResult = tgFX__Client__Sound_Update_Command( enCommand, pData ); break;
        case ETgFX__TRAIL:     bResult = tgFX__Client__Trail_Update_Command( enCommand, pData ); break;

        case ETgFX__EFFECT_MAX:
        default: TgS_NO_DEFAULT( break );
    };

    return (bResult);
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgFX__Update__Group__Update_Command__Process_Command ------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgFX__Update__Group__Update_Command__Process_Command( ETgFX_COMMAND_C UNUSED_PARAM enCommand, TgVOID_CP UNUSED_PARAM pData )
{
}


/* ---- tgFX__Client__ToClient__Process_Command_Internal ------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgFX__Client__ToClient__Process_Command_Internal( TgUINT_F08_P puiCommand_Stream, TgRSIZE uiOffset )
{
    TgRSIZE                             uiBuffer_Size;
    TgRSIZE                             uiIndex;
    ETgFX_COMMAND                       enCommand;
    TgUINT_F32                          uiEffect_Index;

    PROFILE_START( FX_COMMANDS__CLIENT, tgFX__Client__ToClient__Process_Command_Internal );

    uiBuffer_Size = uiOffset;
    TgERROR( uiBuffer_Size <= ETgFX_COMMAND__TO_CLIENT__BYTE_MAX );
    for (uiIndex = 0; uiIndex < uiBuffer_Size; )
    {
        union
        {
            TgUINT_F08_CP                       pui;
            ETgFX_COMMAND_P                     pen;
        }                                   sCommand;
        
        sCommand.pui = puiCommand_Stream;
        enCommand = *sCommand.pen;
        uiIndex += g_uiFX_Command_Size[enCommand];

        switch (enCommand)
        {
            case ETgFX_COMMAND__UPDATE_TO_CLIENT__CREATE:
            {
                union
                {
                    TgUINT_F08_CP                       pui;
                    STg2_FX_Command__Client__Create_P   ps;
                }                                   sCommand_Payload;
                
                sCommand_Payload.pui = puiCommand_Stream;
                tgFX__Client__Inst_FX_Hash( sCommand_Payload.ps->m_uiHash, &sCommand_Payload.ps->m_sInstance, true );
                break;
            };

            case ETgFX_COMMAND__UPDATE_TO_CLIENT__FREE:
            {
                union
                {
                    TgUINT_F08_CP                       pui;
                    STg2_FX_Command__Client__Free_P     ps;
                }                                   sCommand_Payload;
                
                sCommand_Payload.pui = puiCommand_Stream;
                uiEffect_Index = sCommand_Payload.ps->m_tiClient.m_uiI;
                if (tgFX_CLIENT_INST_ID_Is_Equal( &g_asFX_Effect[uiEffect_Index].m_tiClient_Singleton, sCommand_Payload.ps->m_tiClient ))
                {
                    tgFX__Client__Free_Internal( uiEffect_Index );
                };

                break;
            };

            case ETgFX_COMMAND__UPDATE_TO_CLIENT__NOTIFY:
            {
                union
                {
                    TgUINT_F08_CP                       pui;
                    STg2_FX_Command__Notify_P           ps;
                }                                   sCommand_Payload;
                
                sCommand_Payload.pui = puiCommand_Stream;
                switch (sCommand_Payload.ps->m_uiMessage)
                {
                    case ETgFX_NOTIFY__FRAME_COMPLETE:
                        atomic_fetch_add( (TgUINT_PTR_AP)(sCommand_Payload.ps->m_pNotify), 1 );
                        break;
                    default:
                        TgS_NO_DEFAULT( break );
                };
                break;
            };

            case ETgFX_COMMAND__CLIENT_TO_UPDATE__BEGIN:
            case ETgFX_COMMAND__CLIENT_TO_UPDATE__CREATE:
            case ETgFX_COMMAND__CLIENT_TO_UPDATE__KILL:
            case ETgFX_COMMAND__CLIENT_TO_UPDATE__STOP:
            case ETgFX_COMMAND__CLIENT_TO_UPDATE__POSITION_SET:
            case ETgFX_COMMAND__CLIENT_TO_UPDATE__POSITION_UPDATE_FROM_PARENT:
            case ETgFX_COMMAND__CLIENT_TO_UPDATE__ROTATION_SET:
            case ETgFX_COMMAND__CLIENT_TO_UPDATE__ROTATION_UPDATE_FROM_PARENT:
            case ETgFX_COMMAND__CLIENT_TO_UPDATE__SPIN:
            case ETgFX_COMMAND__CLIENT_TO_UPDATE__VISIBLE:
            case ETgFX_COMMAND__SCENE_TO_RENDER__PATCH_CONTEXT:
            case ETgFX_COMMAND__MAX:
            default:
                TgS_NO_DEFAULT( break );
        };
    };
    PROFILE_STOP( FX_COMMANDS__CLIENT, tgFX__Client__ToClient__Process_Command_Internal );
}
