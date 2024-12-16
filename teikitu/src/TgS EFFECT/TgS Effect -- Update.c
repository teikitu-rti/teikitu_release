/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Effect - Effect - Update.c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.20 | »GUID« DE461472-5528-4A5B-A7F4-09CCAD73387B */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined (ENABLE_RELOAD_GUARD)

    #include "TgS Effect - Internal.inl"

    #define __PARENT_FILE__ "TgS Effect -- Update.c"
    #define ENABLE_RELOAD_GUARD
    #include "TgS EFFECT/TgS Effect - Effect [INC].h"
    #undef ENABLE_RELOAD_GUARD
    #undef __PARENT_FILE__

#else
/* == Effects ==================================================================================================================================================================== */
#if T_EFFECT_UPDATE

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgFX__Client__,_Init_Update ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID T_NAME(tgFX__Client__,_Init_Update)( TgVOID )
{
    TgRSIZE                             uiIndex;

    PROFILE_ARRAY_INIT( 0, DEFAULT, T_TYPE(FX_,_UPDATE__UPDATE) );
    PROFILE_ARRAY_INIT( 1, EXTERNAL, T_TYPE(FX_,_UPDATE__UPDATE) );
    PROFILE_ARRAY_INIT( 2, NEW, T_TYPE(FX_,_UPDATE__UPDATE) );
    PROFILE_ARRAY_INIT( 3, FINISH, T_TYPE(FX_,_UPDATE__UPDATE) );
    PROFILE_INIT( T_TYPE(FX_,_UPDATE__DATA) );
    PROFILE_INIT( T_TYPE(FX_,_UPDATE_EXTERNAL__DATA) );

    /* Fence Controls */
    atomic_store( &T_TYPE(g_xuiFX_FENCE__UPDATE__UPDATE__,), 0 );
    for (uiIndex = 0; uiIndex < ETgFX_UPDATE__MAX; ++uiIndex)
    {
        atomic_store( T_TYPE(g_axuiFX_FENCE__UPDATE__UPDATE__,) + uiIndex, 0 );
    };
    atomic_store( &T_TYPE(g_xuiFX_FENCE__UPDATE__FINISH__,), 0 );

    /* Effect Lists */

    tgMM_Set_U08_0x00( T_NAME(g_atiFX__,__Update__Head), sizeof( T_NAME(g_atiFX__,__Update__Head) ) );
    T_NAME(g_niFX__,__Update__Active) = 0;

    /* Jobs */

    tgMM_Set_U08_0x00( T_NAME(g_sFX__Job__,__Update), sizeof( T_NAME(g_sFX__Job__,__Update) ) );
    tgMM_Set_U08_0x00( &T_NAME(g_sFX__Job__,__Update__Update_Finish), sizeof( T_NAME(g_sFX__Job__,__Update__Update_Finish) ) );
    tgMM_Set_U08_0x00( &T_NAME(g_sFX__Job__,__Update__Process_ClientToUpdate), sizeof( T_NAME(g_sFX__Job__,__Update__Process_ClientToUpdate) ) );
    atomic_store( &T_NAME(g_xuiFX_Command__,__Update_Command_Offset), 0 );
    atomic_store( &T_NAME(g_xuiFX_Command__,__ClientToUpdate_Offset), 0 );
}


/* ---- tgFX__Client__,_Boot_Update ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID T_NAME(tgFX__Client__,_Boot_Update)( TgVOID )
{
    T_NAME(g_sFX__Job__,__Update)[ETgFX_UPDATE__DEFAULT].m_pfnExecute = T_NAME(tgFX__Update__Job__,_Update);
    T_NAME(g_sFX__Job__,__Update)[ETgFX_UPDATE__DEFAULT].m_pxuiFinish = &T_TYPE(g_xuiFX_FENCE__UPDATE__UPDATE__,);

    T_NAME(g_sFX__Job__,__Update)[ETgFX_UPDATE__EXTERNAL].m_pfnExecute = T_NAME(tgFX__Update__Job__,_Update);
    T_NAME(g_sFX__Job__,__Update)[ETgFX_UPDATE__EXTERNAL].m_pxuiFinish = &T_TYPE(g_xuiFX_FENCE__UPDATE__UPDATE__,);

    T_NAME(g_sFX__Job__,__Update__Update_Finish).m_pfnExecute = T_NAME(tgFX__Update__Job__,_Update_Finish);
    T_NAME(g_sFX__Job__,__Update__Update_Finish).m_pxuiTrigger = &T_TYPE(g_xuiFX_FENCE__UPDATE__UPDATE__,);
    T_NAME(g_sFX__Job__,__Update__Update_Finish).m_pxuiFinish = &T_TYPE(g_xuiFX_FENCE__UPDATE__FINISH__,);
}


/* ---- tgFX__Client__,_Update_Command ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL T_NAME(tgFX__Client__,_Update_Command)( ETgFX_COMMAND_C enCommand, TgVOID_CP pData )
{
    TgUINT_F08_P                        puiCommand_Stream;

    if (g_uiFX_Command_Size[enCommand] <= 0)
        return (false);

    puiCommand_Stream = T_NAME(tgFX_,__Reserve_Update_Command)( enCommand );
    if (nullptr == puiCommand_Stream)
        return (false);

    tgMM_Copy( puiCommand_Stream, g_uiFX_Command_Size[enCommand], pData, g_uiFX_Command_Size[enCommand] );
    return (true);
}


/* ---- tgFX__Client__Submit_Job__,_Update --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID T_NAME(tgFX__Client__Submit_Job__,_Update)( TgVEC_F32_04_1 vDT, TgFLOAT32_C fDT, ETgFX_UPDATE_C enUpdate )
{
    union
    {
        TgUINT_F08_P                        pui;
        STg2_FX_Job__Update_Data_P          psJob_Data;
    }                                   sUnion;

    TgERROR((TgRSIZE)enUpdate >= atomic_load( &T_TYPE(g_xuiFX_FENCE__UPDATE__UPDATE__,) ));
    TgERROR(nullptr != T_NAME(g_sFX__Job__,__Update)[enUpdate].m_pfnExecute);

    sUnion.pui = T_NAME(g_sFX__Job__,__Update)[enUpdate].m_auiData;
    sUnion.psJob_Data->m_vDT = vDT;
    sUnion.psJob_Data->m_fDT = fDT;
    sUnion.psJob_Data->m_enUpdate = enUpdate;

    /* #PERF: Come up with a better load balancer than a single submission */
    atomic_fetch_add( &g_xuiFX_FENCE__UPDATE, 1 );
    atomic_fetch_add( &g_xuiFX_FENCE__UPDATE__UPDATE, 1 );
    atomic_fetch_add( &T_TYPE(g_xuiFX_FENCE__UPDATE__UPDATE__,), 1 );
    atomic_fetch_add( T_TYPE(g_axuiFX_FENCE__UPDATE__UPDATE__,) + enUpdate, 1 );

    if (TgFAILED(tgJM_Queue_Job( g_sJob_Queue__Client_Normal, T_NAME(g_sFX__Job__,__Update) + enUpdate )))
    {
        TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to submit job." );
        atomic_fetch_sub( &g_xuiFX_FENCE__UPDATE, 1 );
        atomic_fetch_sub( &g_xuiFX_FENCE__UPDATE__UPDATE, 1 );
        atomic_fetch_sub( &T_TYPE(g_xuiFX_FENCE__UPDATE__UPDATE__,), 1 );
        atomic_fetch_sub( T_TYPE(g_axuiFX_FENCE__UPDATE__UPDATE__,) + enUpdate, 1 );
    };
}


/* ---- tgFX__Client__Submit_Job__,_Update_Finish -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID T_NAME(tgFX__Client__Submit_Job__,_Update_Finish)( TgVOID )
{
    TgERROR( 0 == T_TYPE(g_xuiFX_FENCE__UPDATE__FINISH__,) );

    atomic_fetch_add( &g_xuiFX_FENCE__UPDATE, 1 );
    atomic_fetch_add( &g_xuiFX_FENCE__UPDATE__FINISH, 1 );
    atomic_fetch_add( &T_TYPE(g_xuiFX_FENCE__UPDATE__FINISH__,), 1 );

    if (TgFAILED(tgJM_Queue_Job( g_sJob_Queue__Client_Normal, & T_NAME(g_sFX__Job__,__Update__Update_Finish) )))
    {
        TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to submit job." );
        atomic_fetch_sub( &g_xuiFX_FENCE__UPDATE, 1 );
        atomic_fetch_sub( &g_xuiFX_FENCE__UPDATE__FINISH, 1 );
        atomic_fetch_sub( &T_TYPE(g_xuiFX_FENCE__UPDATE__FINISH__,), 1 );
    };
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgFX__,_Query_Effect_Update_Head ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgFX_DATA_INST_ID T_NAME(tgFX__,_Query_Effect_Update_Head)( ETgFX_UPDATE_C enUpdate )
{
    return (T_NAME(g_atiFX__,__Update__Head)[enUpdate]);
}


/* ---- tgFX__Update__,_Process_Update_Command_Buffer ---------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* This is the only place where effect data can be created and deleted */
TgRSIZE T_NAME(tgFX__Update__,_Process_Update_Command_Buffer)( TgUINT_F08_CP puiCommand_Stream, TgRSIZE uiIndex )
{
    ETgFX_COMMAND                       enCommand;

    puiCommand_Stream = puiCommand_Stream + uiIndex;
    {
        union
        {
            TgUINT_F08_CP                       pui;
            ETgFX_COMMAND_P                     penCommand;
        }                                   sUnion;

        sUnion.pui = puiCommand_Stream;
        enCommand = *sUnion.penCommand;
    }
    uiIndex += g_uiFX_Command_Size[enCommand];

#if T_EFFECT_NOTIFY
    if (ETgFX_COMMAND__CLIENT_TO_UPDATE__NOTIFY == enCommand)
    {
        union
        {
            TgUINT_F08_CP                       pui;
            STg2_FX_Command__Notify_CP          psNotify;
        }                                   sUnion;

        sUnion.pui = puiCommand_Stream;
        if (enCommand == (ETgFX_COMMAND)sUnion.psNotify->m_uiMessage)
        {
            T_NAME(tgFX__Update__Command__,_Notify)( sUnion.psNotify );
            return (uiIndex);
        };
    }
/*# T_EFFECT_NOTIFY */
#else
    TgERROR(ETgFX_COMMAND__CLIENT_TO_UPDATE__NOTIFY != enCommand);
/*# T_EFFECT_NOTIFY */
#endif

    /* Create commands are a special case of the regular commands - they have a different function signature (responsible for binding tiClient and tiData) */
    if (ETgFX_COMMAND__CLIENT_TO_UPDATE__CREATE == enCommand)
    {
        union
        {
            TgUINT_F08_CP                       pui;
            STg2_FX_Command__Update__Create_P   ps;
        }                                   sCreate;
        T_NAME(STg2_FX__,_P)                psEffect;

        sCreate.pui = puiCommand_Stream;

        TgERROR( tgFX_Debug__Is_Valid( sCreate.ps->m_tiClient, sCreate.ps->m_tiData ) );
        TgERROR( sCreate.ps->m_tiClient.m_uiI < KTgFX_MAX_EFFECT_INSTANCE );
        TgERROR( ETgFX_EFFECT_STATE__CLIENT__RESERVED == T_NAME(g_aenFX__,__Shared__State)[sCreate.ps->m_tiData.m_uiI] );
        TgERROR( ETgFX_EFFECT_STATE__CLIENT__ACTIVE == g_aiFX__Client__Shared_State[sCreate.ps->m_tiClient.m_uiI] );
        TgERROR( sCreate.ps->m_tiData.m_uiI < T_TYPE(KTgFX_MAX_,) );

        psEffect = T_NAME(g_asFX__,) + sCreate.ps->m_tiData.m_uiI;

    #if T_EFFECT_RENDER
        psEffect->m_tiNext[ETgFX_NEXT__RENDER] = KTgFX_DATA_INST_ID__INVALID;
    /*# T_EFFECT_RENDER */
    #endif
    #if T_EFFECT_SCENE
        psEffect->m_tiNext[ETgFX_NEXT__SCENE] = KTgFX_DATA_INST_ID__INVALID;
    /*# T_EFFECT_SCENE */
    #endif
        psEffect->m_tiNext[ETgFX_NEXT__UPDATE] = KTgFX_DATA_INST_ID__INVALID;

        psEffect->m_psFile_Data = (T_NAME(STg2_FX_,__File_Data_CP))sCreate.ps->m_psFile_Data_0;
        psEffect->m_tiClient = sCreate.ps->m_tiClient;
        psEffect->m_tiData = sCreate.ps->m_tiData;

    #if T_EFFECT_TIME
        /* [0, Start Duration] is the start period, then we have the standard run time, then [End Start, End Start + Duration] where we closed the effect. */
        psEffect->m_sTime.m_fTime_Total = tgCM_MAX_F32( 0.0F, tgCM_RAND_ONE_F32()*psEffect->m_psFile_Data->m_fTime_Total_RNG + psEffect->m_psFile_Data->m_fTime_Total_MID );
        psEffect->m_sTime.m_fTime_Start__End = tgCM_MAX_F32( 0.0F, tgCM_RAND_ONE_F32()*psEffect->m_psFile_Data->m_fTime_Start_End_RNG + psEffect->m_psFile_Data->m_fTime_Start_End_MID );
        psEffect->m_sTime.m_fTime_End__Start = tgCM_RAND_ONE_F32()*psEffect->m_psFile_Data->m_fTime_End_Start_RNG + psEffect->m_psFile_Data->m_fTime_End_Start_MID;

        /* Correct for the case where end start ends up randomly (or through configuration) to be earlier than the end of the start phrase. */
        if (psEffect->m_sTime.m_fTime_End__Start > 0.0F)
        {
            psEffect->m_sTime.m_fTime_End__Start = tgCM_CLP_F32( psEffect->m_sTime.m_fTime_End__Start, 0.0F, psEffect->m_sTime.m_fTime_Total );
            psEffect->m_sTime.m_fTime_Start__End = tgCM_MIN_F32( psEffect->m_sTime.m_fTime_Start__End, psEffect->m_sTime.m_fTime_End__Start );
            psEffect->m_fTime_End__Duration = tgCM_MAX_F32( 0.0F, psEffect->m_sTime.m_fTime_Total - psEffect->m_sTime.m_fTime_End__Start );
        }
        else
        {
            psEffect->m_fTime_End__Duration = psEffect->m_sTime.m_fTime_End__Start;
        }

        /* Run time values. */
        psEffect->m_fLife_Time = psEffect->m_sTime.m_fTime_Total; /* Counts down. */
        psEffect->m_sTime.m_fLive_Time = 0.0F; /* Counts up. */
        psEffect->m_vLive_Time = tgMH_SET1_F32_04_1( 0.0F );
    /*# T_EFFECT_TIME */
    #endif

    #if T_EFFECT_FRAME
        psEffect->m_qRot_N2M = KTgUNIT_W_F32_04_1;
        psEffect->m_qRot_M2W = sCreate.ps->m_sInstance.m_qRot_N2W;
        psEffect->m_qRot_N2W = tgMH_QT_MUL_F32_04_1( psEffect->m_qRot_N2M, psEffect->m_qRot_M2W );
        psEffect->m_vPos_N2M = tgMH_SET1_F32_04_1( 0.0F );
        psEffect->m_vPos_M2W = sCreate.ps->m_sInstance.m_vPos_N2W;
        psEffect->m_vPos_N2W = tgMH_ADD_F32_04_1( psEffect->m_vPos_M2W, tgMH_QT_TX_F32_04_1( psEffect->m_vPos_N2M, psEffect->m_qRot_M2W ) );
        psEffect->m_vScale = sCreate.ps->m_sInstance.m_vScale;
    /*# T_EFFECT_FRAME */
    #endif

    #if T_EFFECT_RENDER
        psEffect->m_enVertex = ETgKN_GPU_DEFAULT_INPUT_LAYOUT_MAX;
        psEffect->m_tiMesh_Set = KTgRN_MESH_SET_ID__INVALID;
        psEffect->m_tiMaterial = KTgRN_MATERIAL_ID__INVALID;
        psEffect->m_uiRender__NotVisible = 0;
        psEffect->m_uiIndex_In_SE_Context = KTgMAX_RSIZE;
        psEffect->m_vBA_Max_W = tgMH_SET1_F32_04_1( -KTgMAX_F32 );
        psEffect->m_vBA_Min_W = tgMH_SET1_F32_04_1( KTgMAX_F32 );
    /*# T_EFFECT_RENDER */
    #endif

        if (T_NAME(tgFX__Update__,_Create_Command)( &sCreate.ps->m_sInstance, sCreate.ps->m_tiData, sCreate.ps->m_psFile_Data_1 ))
        {
            TgUINT_F32                          uiUpdate;

            uiUpdate = (TgUINT_E32)((sCreate.ps->m_sInstance.m_uiInternal >> 8) & 0xFF);
            TgERROR_INDEX( uiUpdate, T_NAME(g_atiFX__,__Update__Head) );
            psEffect->m_tiNext[ETgFX_NEXT__UPDATE] = T_NAME(g_atiFX__,__Update__Head)[uiUpdate];
            T_NAME(g_atiFX__,__Update__Head)[uiUpdate] = psEffect->m_tiData;

            ++T_NAME(g_niFX__,__Update__Active);
        }
        else
        {
        #if T_EFFECT_RENDER
            psEffect->m_tiNext[ETgFX_NEXT__RENDER] = KTgFX_DATA_INST_ID__INVALID;
        /*# T_EFFECT_RENDER */
        #endif
        #if T_EFFECT_SCENE
            psEffect->m_tiNext[ETgFX_NEXT__SCENE] = KTgFX_DATA_INST_ID__INVALID;
        /*# T_EFFECT_SCENE */
        #endif
            psEffect->m_tiNext[ETgFX_NEXT__UPDATE] = KTgFX_DATA_INST_ID__INVALID;

            psEffect->m_psFile_Data = nullptr;
            psEffect->m_tiClient = KTgFX_CLIENT_INST_ID__INVALID;
            psEffect->m_tiData = KTgFX_DATA_INST_ID__INVALID;

            T_NAME(g_aenFX__,__Shared__State)[sCreate.ps->m_tiData.m_uiI] = ETgFX_EFFECT_STATE__CLIENT__FREE;

            atomic_thread_fence( cxx__memory_order_seq_cst );
            tgCM_UT_LF__ST__Push( &T_NAME(g_sFX__,__Client__Stack).m_sStack, (STg2_UT_ST__ST_Node_P)(psEffect) );

            T_NAME(tgFX__Update__Command__,_Free)( sCreate.ps->m_tiClient, sCreate.ps->m_tiData );
        };

        return (uiIndex);
    };

    {
        union
        {
            TgUINT_F08_CP                       pui;
            STg2_FX_Command__Update__NoParam_P psCommand;
        }                                   sUnion;

        sUnion.pui = puiCommand_Stream;

        /* Ignore stale messages to effects that have been freed on the update thread */
        if (sUnion.psCommand->m_sDest.m_tiData.m_uiKI != T_NAME(g_asFX__,)[sUnion.psCommand->m_sDest.m_tiData.m_uiI].m_tiData.m_uiKI)
        {
            return (uiIndex);
        }
        TgERROR( T_NAME(g_aenFX__,__Shared__State)[sUnion.psCommand->m_sDest.m_tiData.m_uiI] > ETgFX_EFFECT_STATE__CLIENT__FREE );

        /* Process non-create commands to active effects */
        TgERROR( T_NAME(g_aenFX__,__Shared__State)[sUnion.psCommand->m_sDest.m_tiData.m_uiI] >= ETgFX_EFFECT_STATE__UPDATE__ACTIVE );
    #if T_EFFECT_PROCESS_COMMMAND
        T_NAME(tgFX__Update__,_Process_Update_Command)( enCommand, puiCommand_Stream, sUnion.psCommand->m_sDest.m_tiData );
    #endif

        if (ETgFX_COMMAND__CLIENT_TO_UPDATE__KILL == enCommand)
        {
        #if T_EFFECT_GROUP
            T_NAME(tgFX__Update__Command__,_Free)(
                T_NAME(g_asFX__,)[sUnion.psCommand->m_sDest.m_tiData.m_uiI].m_tiClient, T_NAME(g_asFX__,)[sUnion.psCommand->m_sDest.m_tiData.m_uiI].m_tiData );
        /*# T_EFFECT_GROUP */
        #else
            T_NAME(tgFX__Update__,_Kill)( sUnion.psCommand->m_sDest.m_tiData.m_uiI );
        /*# T_EFFECT_GROUP */
        #endif
        }
        else if (ETgFX_COMMAND__CLIENT_TO_UPDATE__STOP == enCommand)
        {
            T_NAME(g_aenFX__,__Shared__State)[sUnion.psCommand->m_sDest.m_tiData.m_uiI] = ETgFX_EFFECT_STATE__UPDATE__ACTIVE_WAITING_TO_DIE;
        };
    };

    return (uiIndex);
}


/* ---- tgFX_,__ClientToUpdate__Reserve_Command ---------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgUINT_F08_P T_NAME(tgFX_,__Reserve_Update_Command)( ETgFX_COMMAND_C enCommand )
{
    TgRSIZE                             uiCommand_Size;
    TgRSIZE                             uiCommand_Offset;

    TgPARAM_CHECK( ETgFX_COMMAND__CLIENT_TO_UPDATE__BEGIN <= enCommand && ETgFX_COMMAND__CLIENT_TO_UPDATE__END >= enCommand );
    uiCommand_Size = g_uiFX_Command_Size[enCommand];
    uiCommand_Offset = atomic_load( &T_NAME(g_xuiFX_Command__,__Update_Command_Offset) );
    while (1)
    {
        if ((uiCommand_Offset + uiCommand_Size) >= ETgFX_COMMAND__CLIENT_TO_UPDATE__BYTE_MAX)
        {
            return (nullptr);
        };

        if (atomic_compare_exchange_strong( &T_NAME(g_xuiFX_Command__,__Update_Command_Offset), &uiCommand_Offset, uiCommand_Offset + uiCommand_Size ))
        {
            return (T_NAME(g_asFX_Command__,__Update_Command_Buffer) + uiCommand_Offset);
        };
    };
}


/* ---- tgFX__Update__,_Process_Update_Command_Default --------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if T_EFFECT_PROCESS_COMMMAND_DEFAULT
TgVOID T_NAME(tgFX__Update__,_Process_Update_Command_Default)( ETgFX_COMMAND_C enCommand, TgVOID_CP pData, TgFX_DATA_INST_ID_C tiData )
{
    T_NAME(STg2_FX__,_P)                psEffect;
    union
    {
        STg2_FX_Command__Update__1_F32_04_CP psCommand_1_F32_04;
        STg2_FX_Command__Update__1_UXX_CP   psCommand_1_UXX;
        TgVOID_CP                           pVoid;
    }                                   sUnion;

    TgPARAM_CHECK_INDEX( tiData.m_uiI, T_NAME(g_aenFX__,__Shared__State) );

    sUnion.pVoid = pData;
    psEffect = T_NAME(g_asFX__,) + tiData.m_uiI;
    switch (enCommand)
    {
        case ETgFX_COMMAND__CLIENT_TO_UPDATE__NOTIFY: /**< Fall Through - Invalid */
        case ETgFX_COMMAND__CLIENT_TO_UPDATE__CREATE: /**< Fall Through - Invalid */
        case ETgFX_COMMAND__CLIENT_TO_UPDATE__SPIN: /**< Fall Through - Invalid */
        case ETgFX_COMMAND__SCENE_TO_RENDER__BEGIN: /**< Fall Through - Invalid */
        case ETgFX_COMMAND__UPDATE_TO_CLIENT__BEGIN: /**< Fall Through - Invalid */
        case ETgFX_COMMAND__UPDATE_TO_CLIENT__NOTIFY: /**< Fall Through - Invalid */
        case ETgFX_COMMAND__UPDATE_TO_CLIENT__FREE: /**< Fall Through - Invalid */
        case ETgFX_COMMAND__MAX: /**< Fall Through - Invalid */
        default: TgS_NO_DEFAULT( break );

        case ETgFX_COMMAND__CLIENT_TO_UPDATE__KILL: /**< Fall Through - Intentionally Blank */
        case ETgFX_COMMAND__CLIENT_TO_UPDATE__STOP: /**< Fall Through - Intentionally Blank */
            break;

        case ETgFX_COMMAND__CLIENT_TO_UPDATE__POSITION_SET:
            psEffect->m_vPos_M2W = sUnion.psCommand_1_F32_04->m_vF32_04;
            psEffect->m_vPos_N2W = tgMH_ADD_F32_04_1( psEffect->m_vPos_M2W, tgMH_QT_TX_F32_04_1( psEffect->m_vPos_N2M, psEffect->m_qRot_M2W ) );
            break;
        case ETgFX_COMMAND__CLIENT_TO_UPDATE__POSITION_UPDATE_FROM_PARENT:
            psEffect->m_vPos_M2W = tgMH_ADD_F32_04_1( psEffect->m_vPos_M2W, sUnion.psCommand_1_F32_04->m_vF32_04 );
            psEffect->m_vPos_N2W = tgMH_ADD_F32_04_1( psEffect->m_vPos_M2W, tgMH_QT_TX_F32_04_1( psEffect->m_vPos_N2M, psEffect->m_qRot_M2W ) );
            break;
        case ETgFX_COMMAND__CLIENT_TO_UPDATE__ROTATION_SET:
            psEffect->m_qRot_M2W = sUnion.psCommand_1_F32_04->m_vF32_04;
            psEffect->m_qRot_N2W = tgMH_QT_MUL_F32_04_1( psEffect->m_qRot_N2M, psEffect->m_qRot_M2W );
            psEffect->m_vPos_N2W = tgMH_ADD_F32_04_1( psEffect->m_vPos_M2W, tgMH_QT_TX_F32_04_1( psEffect->m_vPos_N2M, psEffect->m_qRot_M2W ) );
            break;
        case ETgFX_COMMAND__CLIENT_TO_UPDATE__ROTATION_UPDATE_FROM_PARENT:
            psEffect->m_qRot_M2W = tgMH_QT_MUL_F32_04_1( sUnion.psCommand_1_F32_04->m_vF32_04, psEffect->m_qRot_M2W );
            psEffect->m_qRot_N2W = tgMH_QT_MUL_F32_04_1( psEffect->m_qRot_N2M, psEffect->m_qRot_M2W );
            psEffect->m_vPos_N2W = tgMH_ADD_F32_04_1( psEffect->m_vPos_M2W, tgMH_QT_TX_F32_04_1( psEffect->m_vPos_N2M, psEffect->m_qRot_M2W ) );
            break;
        case ETgFX_COMMAND__CLIENT_TO_UPDATE__VISIBLE:
            psEffect->m_uiRender__NotVisible = 0 != sUnion.psCommand_1_UXX->m_uiVal ? 0u : 1u;
            break;
    };
}
/*# T_EFFECT_PROCESS_COMMMAND_DEFAULT */
#endif


/* ---- tgFX__Update__,_Update_Life_Time ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if T_EFFECT_TIME_DEFAULT
TgBOOL T_NAME(tgFX__Update__,_Update_Life_Time)( TgRSIZE_C uiIndex, TgFLOAT32_C fDT, TgVEC_F32_04_1 vdT )
{
    TgDIAG( ETgFX_EFFECT_STATE__UPDATE__ACTIVE_WAITING_TO_DIE >= T_NAME(g_aenFX__,__Shared__State)[uiIndex] );
    TgDIAG( ETgFX_EFFECT_STATE__UPDATE__ACTIVE <= T_NAME(g_aenFX__,__Shared__State)[uiIndex] );
    if (ETgFX_EFFECT_STATE__UPDATE__ACTIVE == T_NAME(g_aenFX__,__Shared__State)[uiIndex])
    {
        T_NAME(g_asFX__,)[uiIndex].m_fLife_Time -= fDT;
        if (T_NAME(g_asFX__,)[uiIndex].m_fLife_Time <= T_NAME(g_asFX__,)[uiIndex].m_fTime_End__Duration)
        {
            T_NAME(g_aenFX__,__Shared__State)[uiIndex] = ETgFX_EFFECT_STATE__UPDATE__ACTIVE_WAITING_TO_DIE;
            if (T_NAME(g_asFX__,)[uiIndex].m_fLife_Time <= 0.0F)
            {
                T_NAME(tgFX__Update__Command__,_Kill_Self)( T_NAME(g_asFX__,)[uiIndex].m_tiData);
                T_NAME(g_asFX__,)[uiIndex].m_fLife_Time = 0.0F;
                return (false);
            };
        };
    }
    else if (ETgFX_EFFECT_STATE__UPDATE__ACTIVE_INFINITE == T_NAME(g_aenFX__,__Shared__State)[uiIndex])
    {
        /* Intentionally left blank */
    }
    else if (ETgFX_EFFECT_STATE__UPDATE__ACTIVE_FIRST == T_NAME(g_aenFX__,__Shared__State)[uiIndex])
    {
        T_NAME(g_aenFX__,__Shared__State)[uiIndex] = ETgFX_EFFECT_STATE__UPDATE__ACTIVE;
    }
    else if (ETgFX_EFFECT_STATE__UPDATE__ACTIVE_WAITING_TO_DIE == T_NAME(g_aenFX__,__Shared__State)[uiIndex])
    {
        if (T_NAME(g_asFX__,)[uiIndex].m_fLife_Time <= fDT)
        {
            T_NAME(tgFX__Update__Command__,_Kill_Self)( T_NAME(g_asFX__,)[uiIndex].m_tiData);
            T_NAME(g_asFX__,)[uiIndex].m_fLife_Time = 0.0F;
            return (false);
        };
        T_NAME(g_asFX__,)[uiIndex].m_fLife_Time -= fDT;
    }
    else
    {
        T_NAME(tgFX__Update__Command__,_Kill_Self)( T_NAME(g_asFX__,)[uiIndex].m_tiData);
        TgERROR_MSGF( 0, u8"%-16.16s(%-32.32s): Invalid Effect State.\n", u8"Effect", u8"tgFX__ __Update_Life_Time" );
        return (false);
    };

    T_NAME(g_asFX__,)[uiIndex].m_vLive_Time = tgMH_ADD_F32_04_1( T_NAME(g_asFX__,)[uiIndex].m_vLive_Time, vdT );
    return (true);
}
/*# T_EFFECT_TIME_DEFAULT */
#endif



/* ---- tgFX__Update__,_Diag_Check_Effect ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID T_NAME(tgFX__Update__,_Diag_Check_Effect)( TgFX_DATA_INST_ID tiData )
{
#if TgCOMPILE_ASSERT && TgCOMPILE_ASSERT__DIAG
    TgDIAG( T_NAME(g_asFX__,)[tiData.m_uiI].m_tiData.m_uiKI == tiData.m_uiKI );
    TgDIAG( T_NAME(g_aenFX__,__Shared__State)[tiData.m_uiI] >= ETgFX_EFFECT_STATE__UPDATE__ACTIVE );
    TgDIAG( tgFX_Debug__Is_Valid( T_NAME(g_asFX__,)[tiData.m_uiI].m_tiClient, T_NAME(g_asFX__,)[tiData.m_uiI].m_tiData ) );
/*# TgCOMPILE_ASSERT && TgCOMPILE_ASSERT__DIAG */
#endif
}


/* ---- tgFX__Update__,_Kill ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID T_NAME(tgFX__Update__,_Kill)( TgRSIZE_C uiIndex )
{
    TgFX_CLIENT_INST_ID                 tiClient;
    TgFX_DATA_INST_ID                   tiData;

    tiClient = T_NAME(g_asFX__,)[uiIndex].m_tiClient;
    tiData = T_NAME(g_asFX__,)[uiIndex].m_tiData;

#if T_EFFECT_RENDER
    /* Free render resources */
    if (KTgRN_MESH_SET_ID__PARTICLE.m_uiKI != T_NAME(g_asFX__,)[uiIndex].m_tiMesh_Set.m_uiKI)
    {
        tgRN_Release_Mesh_Set( T_NAME(g_asFX__,)[uiIndex].m_tiMesh_Set );
        T_NAME(g_asFX__,)[uiIndex].m_tiMesh_Set = KTgRN_MESH_SET_ID__INVALID;
    };

    if (KTgID__INVALID_VALUE != T_NAME(g_asFX__,)[uiIndex].m_tiMaterial.m_uiKI)
    {
        tgRN_Release_Material( T_NAME(g_asFX__,)[uiIndex].m_tiMaterial );
        T_NAME(g_asFX__,)[uiIndex].m_tiMaterial = KTgRN_MATERIAL_ID__INVALID;
    };

    T_NAME(g_asFX__,)[uiIndex].m_uiIndex_In_SE_Context = KTgMAX_RSIZE;
/*# T_EFFECT_RENDER */
#endif

    /* Invalidate data instance and put it back into the free pool */
#if T_EFFECT_RENDER
    T_NAME(g_asFX__,)[uiIndex].m_tiNext[ETgFX_NEXT__RENDER] = KTgFX_DATA_INST_ID__INVALID;
/*# T_EFFECT_RENDER */
#endif
#if T_EFFECT_SCENE
    T_NAME(g_asFX__,)[uiIndex].m_tiNext[ETgFX_NEXT__SCENE] = KTgFX_DATA_INST_ID__INVALID;
/*# T_EFFECT_SCENE */
#endif
    T_NAME(g_asFX__,)[uiIndex].m_tiNext[ETgFX_NEXT__UPDATE] = KTgFX_DATA_INST_ID__INVALID;

    T_NAME(g_asFX__,)[uiIndex].m_psFile_Data = nullptr;
    T_NAME(g_asFX__,)[uiIndex].m_tiClient = KTgFX_CLIENT_INST_ID__INVALID;
    T_NAME(g_asFX__,)[uiIndex].m_tiData = KTgFX_DATA_INST_ID__INVALID;

    T_NAME(g_aenFX__,__Shared__State)[uiIndex] = ETgFX_EFFECT_STATE__CLIENT__FREE;

    /* Invalidate effect */
    T_NAME(tgFX__Update__Command__,_Free)( tiClient, tiData );
}


/* ---- tgFX__Update__Command__,_Kill_Self --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID T_NAME(tgFX__Update__Command__,_Kill_Self)( TgFX_DATA_INST_ID_C tiData )
{
    union
    {
        TgUINT_F08_P                        puiCommand_Stream;
        STg2_FX_Command__Update__NoParam_P psCommand;
    }                                   sUnion;

    sUnion.puiCommand_Stream = T_NAME(tgFX_,__Reserve_Update_Command)( ETgFX_COMMAND__CLIENT_TO_UPDATE__KILL );
    if (nullptr == sUnion.puiCommand_Stream)
        return;

    sUnion.psCommand->m_enCommand = ETgFX_COMMAND__CLIENT_TO_UPDATE__KILL;
    sUnion.psCommand->m_sDest.m_tiData = tiData;
}


/* ---- tgFX__Update__Job__,_Update ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT T_NAME(tgFX__Update__Job__,_Update)( STg2_Job_PC psJob )
{
    union
    {
        TgUINT_F08_P                        pui;
        STg2_FX_Job__Update_Data_P          psUpdate_Data;
    }                                   sUnion = { sUnion.pui = psJob->m_auiData };

    PROFILE_ARRAY_START( sUnion.psUpdate_Data->m_enUpdate, T_TYPE(FX_,_UPDATE__UPDATE), T_NAME(tgFX__Update__Job__,_Update) );
    PROFILE_ARRAY_START( sUnion.psUpdate_Data->m_enUpdate, FX_UPDATE__UPDATE, T_NAME(tgFX__Update__Job__,_Update) );

    T_NAME(tgFX__Update__,_Update)( sUnion.psUpdate_Data->m_vDT, sUnion.psUpdate_Data->m_fDT, sUnion.psUpdate_Data->m_enUpdate  );

    PROFILE_ARRAY_STOP( sUnion.psUpdate_Data->m_enUpdate, FX_UPDATE__UPDATE, T_NAME(tgFX__Update__Job__,_Update) );
    PROFILE_ARRAY_STOP( sUnion.psUpdate_Data->m_enUpdate, T_TYPE(FX_,_UPDATE__UPDATE), T_NAME(tgFX__Update__Job__,_Update) );

    atomic_fetch_sub( &g_xuiFX_FENCE__UPDATE, 1 );
    atomic_fetch_sub( &g_xuiFX_FENCE__UPDATE__UPDATE, 1 );
    atomic_fetch_sub( T_TYPE(g_axuiFX_FENCE__UPDATE__UPDATE__,) + sUnion.psUpdate_Data->m_enUpdate, 1 );

    return (KTgS_OK);
}


/* ---- tgFX__Update__,_Process_Mark_For_Delete ---------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* This is the only place where effect data can be created and deleted */
TgVOID T_NAME(tgFX__Update__,_Process_Mark_For_Delete)( TgVOID )
{
    TgFX_DATA_INST_ID                   tiPrev_Client;
    TgFX_DATA_INST_ID                   tiCurrent_Client;
    TgFX_DATA_INST_ID                   tiNext_Client;
    TgRSIZE                             uiIndex;

    for (uiIndex = 0; uiIndex < TgARRAY_COUNT( T_NAME(g_atiFX__,__Update__Head) ); ++uiIndex)
    {
        tiPrev_Client = KTgFX_DATA_INST_ID__INVALID;
        tiCurrent_Client = T_NAME(g_atiFX__,__Update__Head)[uiIndex];

        while (KTgID__INVALID_VALUE != tiCurrent_Client.m_uiKI)
        {
            tiNext_Client = T_NAME(g_asFX__,)[tiCurrent_Client.m_uiI].m_tiNext[ETgFX_NEXT__UPDATE];

            /* Clear out all effects that were marked for delete in the last frame */
            if (tiCurrent_Client.m_uiKI != T_NAME(g_asFX__,)[tiCurrent_Client.m_uiI].m_tiData.m_uiKI)
            {
                if (KTgID__INVALID_VALUE != tiPrev_Client.m_uiKI)
                {
                    T_NAME(g_asFX__,)[tiPrev_Client.m_uiI].m_tiNext[ETgFX_NEXT__UPDATE] = tiNext_Client;
                }
                else
                {
                    T_NAME(g_atiFX__,__Update__Head)[uiIndex] = tiNext_Client;
                };

                TgVERIFY(ETgFX_EFFECT_STATE__CLIENT__FREE == T_NAME(g_aenFX__,__Shared__State)[tiCurrent_Client.m_uiI]);
                tgCM_UT_LF__ST__Push( &T_NAME(g_sFX__,__Client__Stack).m_sStack, (STg2_UT_ST__ST_Node_P)(T_NAME(g_asFX__,) + tiCurrent_Client.m_uiI) );
                tiCurrent_Client = tiNext_Client;
                --T_NAME(g_niFX__,__Update__Active);
                continue;
            };

            tiPrev_Client = tiCurrent_Client;
            tiCurrent_Client = tiNext_Client;
        };
    };
}


/* ---- tgFX__Update__,_Process_New_Effects -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* This is the only place where effect data can be created and deleted */
TgVOID T_NAME(tgFX__Update__,_Process_New_Effects)( TgVOID )
{
    TgFX_DATA_INST_ID                   tiCurrent;
    TgFX_DATA_INST_ID                   tiNext;

    tiCurrent = T_NAME(g_atiFX__,__Update__Head)[ETgFX_UPDATE__NEW_CLIENT];

    while (KTgID__INVALID_VALUE != tiCurrent.m_uiKI)
    {
        T_NAME(STg2_FX__,_P)                psEffect;

        psEffect = T_NAME(g_asFX__,) + tiCurrent.m_uiI;
        tiNext = psEffect ->m_tiNext[ETgFX_NEXT__UPDATE];

        psEffect->m_tiNext[ETgFX_NEXT__UPDATE] = T_NAME(g_atiFX__,__Update__Head)[psEffect->m_uiUpdate];
        T_NAME(g_atiFX__,__Update__Head)[psEffect->m_uiUpdate] = tiCurrent;

        tiCurrent = tiNext;
    };


    /* #TODO: Need to run update on all new effects */
    /* #TODO: Update Effect */
    /* #TODO: Cull Effect */
}


/* ---- tgFX__Update__,_Update_Finish -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* This is the only place where effect data can be created and deleted */
TgVOID T_NAME(tgFX__Update__,_Update_Finish)( TgVOID )
{
    TgRSIZE                             uiRead_Offset;
    TgRSIZE                             uiIndex;

    PROFILE_ARRAY_START( ETgFX_UPDATE__MAX, T_TYPE(FX_,_UPDATE__UPDATE), T_NAME(tgFX__Update__,_Update_Finish) );
    PROFILE_ARRAY_START( ETgFX_UPDATE__MAX, FX_UPDATE__UPDATE, T_NAME(tgFX__Update__,_Update_Finish) );

    for (uiIndex = 0, uiRead_Offset = 0; !atomic_compare_exchange_strong( &T_NAME(g_xuiFX_Command__,__Update_Command_Offset), &uiRead_Offset, 0 ); )
    {
        uiIndex = T_NAME(tgFX__Update__,_Process_Update_Command_Buffer)( T_NAME(g_asFX_Command__,__Update_Command_Buffer), uiIndex );
        uiRead_Offset = uiIndex;
        TgERROR( uiIndex <= uiRead_Offset );
        TgERROR( uiRead_Offset <= ETgFX_COMMAND__CLIENT_TO_UPDATE__BYTE_MAX );
    };

    atomic_thread_fence( cxx__memory_order_seq_cst );

    T_NAME(tgFX__Update__,_Process_Mark_For_Delete)();
    T_NAME(tgFX__Update__,_Process_New_Effects)();

    PROFILE_ARRAY_STOP( ETgFX_UPDATE__MAX, FX_UPDATE__UPDATE, T_NAME(tgFX__Update__,_Update_Finish)  );
    PROFILE_ARRAY_STOP( ETgFX_UPDATE__MAX, T_TYPE(FX_,_UPDATE__UPDATE), T_NAME(tgFX__Update__,_Update_Finish) );
}


/* ---- tgFX__Update__Job__,_Update_Finish --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT T_NAME(tgFX__Update__Job__,_Update_Finish)( STg2_Job_PC UNUSED_PARAM psJob )
{
    T_NAME(tgFX__Update__,_Update_Finish)();

    atomic_fetch_sub( &g_xuiFX_FENCE__UPDATE, 1 );
    atomic_fetch_sub( &g_xuiFX_FENCE__UPDATE__FINISH, 1 );

    return (KTgS_OK);
}


/*# T_EFFECT_UPDATE */
#endif


/*# defined (ENABLE_RELOAD_GUARD) */
#endif
