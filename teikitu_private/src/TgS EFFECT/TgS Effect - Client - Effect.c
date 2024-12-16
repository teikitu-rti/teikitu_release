/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Effect - Client - Effect.c
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

static TgFX_CLIENT_INST_ID                  tgFX__Client__Inst_FX_Internal( ETgFX__EFFECT_C, TgVOID_CP, TgVOID_CP, TgFX_EFFECT_ID_C, STg2_FX_Instance_CPCU );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- Instance Management ------------------------------------------------------------------------------------------------------------------------------------------------------ */

/* ---- tgFX__Client__Inst_FX_RAW ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgFX_CLIENT_INST_ID tgFX__Client__Inst_FX_RAW( ETgFX__EFFECT_C enEffect, TgVOID_CP pData0, TgVOID_CP pData1, STg2_FX_Instance_CPCU psInstance, TgBOOL_C bUseErrorFX )
{
    TgFX_CLIENT_INST_ID                 tiClient;

    TgERROR( nullptr != psInstance );

    if (nullptr != pData0)
    {
        tiClient = tgFX__Client__Inst_FX_Internal( enEffect, pData0, pData1, KTgFX_EFFECT_ID__INVALID, psInstance );
        if (KTgID__INVALID_VALUE != tiClient.m_uiKI)
        {
            return (tiClient);
        };
    };

    if (bUseErrorFX)
    {
        return (tgFX__Client__Inst_FX( g_tiFX_File_Error, psInstance, false ));
    }
    else
    {
        return (KTgFX_CLIENT_INST_ID__INVALID);
    };
}


/* ---- tgFX__Client__Inst_FX_Hash ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgFX_CLIENT_INST_ID tgFX__Client__Inst_FX_Hash( TgUINT_MAX_C uiHash, STg2_FX_Instance_CPCU psInstance, TgBOOL_C bUseErrorFX )
{
    TgERROR( nullptr != psInstance );

    if (KTgEMPTY_HASH != uiHash)
    {
        STg2_FX_Data__Effect_P              psData__Effect;
        TgFX_EFFECT_ID                      tiEffect;
        TgFX_CLIENT_INST_ID                 tiClient;

        /* #PERF: Put the cache list into a unordered set */
        for (TgRSIZE uiIndex = 0; uiIndex < ETgFX_DATA__EFFECT_MAX; ++uiIndex)
        {
            if (uiHash != g_auiFX_KN_File__Effect_Hash[uiIndex])
            {
                continue;
            };

            psData__Effect = g_asFX_KN_File__Effect + uiIndex;
            tiEffect = tgFX_EFFECT_ID_Query_Unsafe( &psData__Effect->m_tiEffect_Singleton );
            tiClient = tgFX__Client__Inst_FX_Internal( psData__Effect->m_enEffect, psData__Effect->m_psFile_Data, nullptr, tiEffect, psInstance );
            if (KTgID__INVALID_VALUE != tiClient.m_uiKI)
            {
                return (tiClient);
            };
            break;
        };
    };

    if (bUseErrorFX)
    {
        return (tgFX__Client__Inst_FX( g_tiFX_File_Error, psInstance, false ));
    }
    else
    {
        return (KTgFX_CLIENT_INST_ID__INVALID);
    };
}


/* ---- tgFX__Client__Inst_FX ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgFX_CLIENT_INST_ID tgFX__Client__Inst_FX( TgFX_EFFECT_ID_C tiEffect, STg2_FX_Instance_CPCU psInstance, TgBOOL_C bUseErrorFX )
{
    TgERROR( nullptr != psInstance );

    if ((KTgID__INVALID_VALUE != tiEffect.m_uiKI) && ( g_asFX_Cache__Effect[tiEffect.m_uiI].m_tiEffect.m_uiKI == tiEffect.m_uiKI ))
    {
        STg2_FX_Data__Effect_P              psData__Effect;
        TgFX_CLIENT_INST_ID                 tiClient;

        psData__Effect = g_asFX_KN_File__Effect + tiEffect.m_uiI;
        tiClient = tgFX__Client__Inst_FX_Internal( psData__Effect->m_enEffect, psData__Effect->m_psFile_Data, nullptr, tiEffect, psInstance );
        if (KTgID__INVALID_VALUE != tiClient.m_uiKI)
        {
            return (tiClient);
        };
    };

    if (bUseErrorFX)
    {
        return (tgFX__Client__Inst_FX( g_tiFX_File_Error, psInstance, false ));
    }
    else
    {
        return (KTgFX_CLIENT_INST_ID__INVALID);
    };
}


/* ---- tgFX__Client__Stop ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgFX__Client__Stop( TgFX_CLIENT_INST_ID_C tiClient )
{
    TgUINT_E32                          uiIndex;
    STg2_FX_Command__Update__NoParam    sCommand;

    uiIndex = tgFX__Client__Get_Client_Index( tiClient );
    if (KTgMAX_U32 == uiIndex)
    {
        return;
    };

    sCommand.m_enCommand = ETgFX_COMMAND__CLIENT_TO_UPDATE__STOP;
    sCommand.m_sDest.m_tiData = g_asFX_Effect[uiIndex].m_tiData;
    tgFX__Client__Queue_Update_Command( g_asFX_Effect[uiIndex].m_enEffect, sCommand.m_enCommand, &sCommand );
}


/* ---- tgFX__Client__Kill ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgFX__Client__Kill( TgFX_CLIENT_INST_ID_C tiClient )
{
    TgUINT_E32                          uiIndex;
    STg2_FX_Command__Update__NoParam    sCommand;

    uiIndex = tgFX__Client__Get_Client_Index( tiClient );
    if (KTgMAX_U32 == uiIndex)
    {
        return;
    };

    sCommand.m_enCommand = ETgFX_COMMAND__CLIENT_TO_UPDATE__KILL;
    sCommand.m_sDest.m_tiData = g_asFX_Effect[uiIndex].m_tiData;
    tgFX__Client__Queue_Update_Command( g_asFX_Effect[uiIndex].m_enEffect, sCommand.m_enCommand, &sCommand );
}


/* ---- tgFX__Client__Kill_All --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgFX__Client__Kill_All( TgUINT_E32_P puiNotify_Flag )
{
    TgUINT_E32                          uiIndex;

    for (uiIndex = 0; uiIndex < KTgFX_MAX_EFFECT_INSTANCE; ++uiIndex)
    {
        if (ETgFX_EFFECT_STATE__CLIENT__FREE != g_aiFX__Client__Shared_State[uiIndex])
        {
            tgFX__Client__Kill( tgFX_CLIENT_INST_ID_Query_Unsafe( &g_asFX_Effect[uiIndex].m_tiClient_Singleton ) );
        }
    }

    if (0 != puiNotify_Flag)
    {
        STg2_FX_Command__Notify             sCommand;

        sCommand.m_enCommand = ETgFX_COMMAND__CLIENT_TO_UPDATE__NOTIFY;
        sCommand.m_uiMessage = ETgFX_NOTIFY__FRAME_COMPLETE;
        sCommand.m_pNotify = puiNotify_Flag;
        tgFX__Client__Queue_Update_Command( ETgFX__INVALID, sCommand.m_enCommand, &sCommand );
    }
}

/* ---- Accessors ---------------------------------------------------------------------------------------------------------------------------------------------------------------- */

/* ---- tgFX__Client__Set_Callback_Terminate ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgFX__Client__Set_Callback_Terminate( TgFX_CLIENT_INST_ID_C tiClient, TgFCN_CB_ON_TERMINATE pfnTerminate, TgUINT_PTR_C uiTerminate_Parameter )
{
    TgUINT_E32                          uiIndex;

    uiIndex = tgFX__Client__Get_Client_Index( tiClient );
    if (KTgMAX_U32 == uiIndex)
    {
        return;
    };

    g_asFX_Effect[uiIndex].m_pfnTerminate = pfnTerminate;
    g_asFX_Effect[uiIndex].m_uiTerminate_Parameter = uiTerminate_Parameter;
}


/* ---- tgFX__Client__Set_Callback_Contact --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgFX__Client__Set_Callback_Contact( TgFX_CLIENT_INST_ID_C tiClient, TgFCN_CB_ON_CONTACT pfnContact, TgUINT_PTR_C uiContact_Parameter )
{
    TgUINT_E32                          uiIndex;

    uiIndex = tgFX__Client__Get_Client_Index( tiClient );
    if (KTgMAX_U32 == uiIndex)
    {
        return;
    };

    g_asFX_Effect[uiIndex].m_pfnContact = pfnContact;
    g_asFX_Effect[uiIndex].m_uiContact_Parameter = uiContact_Parameter;
}


/* ---- tgFX__Client__Set_Visible ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgFX__Client__Set_Visible( TgFX_CLIENT_INST_ID_C tiClient, TgBOOL_C bVisible )
{
    TgUINT_E32                          uiIndex;
    TgUINT_E32                          uiVisible;
    STg2_FX_Command__Update__1_UXX      sCommand;

    uiIndex = tgFX__Client__Get_Client_Index( tiClient );
    if (KTgMAX_U32 == uiIndex)
    {
        return;
    };

    uiVisible = bVisible ? 1u: 0u;
    if (0 != (g_asFX_Effect[uiIndex].m_uiRender_Visible ^ uiVisible))
    {
        return;
    };

    g_asFX_Effect[uiIndex].m_uiRender_Visible = uiVisible;

    sCommand.m_enCommand = ETgFX_COMMAND__CLIENT_TO_UPDATE__VISIBLE;
    sCommand.m_sDest.m_tiData = g_asFX_Effect[uiIndex].m_tiData;
    sCommand.m_uiVal = bVisible ? 1u : 0u;
    tgFX__Client__Queue_Update_Command( g_asFX_Effect[uiIndex].m_enEffect, sCommand.m_enCommand, &sCommand );
}


/* ---- tgFX__Client__Is_Attached ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgFX__Client__Is_Attached( TgFX_CLIENT_INST_ID_C tiClient )
{
    TgUINT_E32                          uiIndex;

    uiIndex = tgFX__Client__Get_Client_Index( tiClient );
    if (KTgMAX_U32 == uiIndex)
    {
        return (false);
    };

    return (KTgID__INVALID_VALUE != g_asFX_Effect[uiIndex].m_tiAttachment.m_uiKI);
}


/* ---- tgFX__Client__Is_Valid --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgFX__Client__Is_Valid( TgFX_CLIENT_INST_ID_C tiClient )
{
    TgUINT_E32                          uiIndex;

    uiIndex = tgFX__Client__Get_Client_Index( tiClient );
    if (KTgMAX_U32 == uiIndex)
    {
        return (KTgE_FAIL);
    };

    if (KTgID__INVALID_VALUE == g_asFX_Effect[tiClient.m_uiI].m_tiData.m_uiKI)
    {
        return (KTgE_FAIL);
    };

    return (KTgS_OK);
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgFX__Client__Get_Client_Index ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgUINT_E32 tgFX__Client__Get_Client_Index( TgFX_CLIENT_INST_ID_C tiClient )
{
    if (KTgID__INVALID_VALUE == tiClient.m_uiKI)
    {
        return KTgMAX_U32;
    };

    TgERROR_INDEX( tiClient.m_uiI, g_asFX_Effect );

    if (!tgFX_CLIENT_INST_ID_Is_Equal( &g_asFX_Effect[tiClient.m_uiI].m_tiClient_Singleton, tiClient ))
    {
        return KTgMAX_U32;
    };

    TgERROR( g_aiFX__Client__Shared_State[tiClient.m_uiI] >= ETgFX_EFFECT_STATE__CLIENT__ACTIVE );
    return (tiClient.m_uiI);
}


/* ---- tgFX__Client__Free_Internal ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgFX__Client__Free_Internal( TgUINT_E32_C uiIndex )
{
    STg2_FX__Client_P                   psEffect;
    TgFX_EFFECT_ID                 tiEffect;
    STg2_FX__Client_P                   psParent;

    TgPARAM_CHECK( g_aiFX__Client__Shared_State[uiIndex] >= ETgFX_EFFECT_STATE__CLIENT__ACTIVE );
    
    psEffect = g_asFX_Effect + uiIndex;
    tiEffect = psEffect->m_tiEffect;
    psParent = nullptr;

    /* Termination call back is executed first (in case there is any necessary data read back) */
    if (nullptr != psEffect->m_pfnTerminate)
    {
        (*psEffect->m_pfnTerminate)( tgFX_CLIENT_INST_ID_Query_Unsafe( &psEffect->m_tiClient_Singleton ), psEffect->m_uiTerminate_Parameter );
    };

    do
    {
        TgFX_DATA_INST_ID                   tiData;

        if (KTgID__INVALID_VALUE == psEffect->m_tiParent.m_uiKI)
        {
            break;
        };

        if (!tgFX_CLIENT_INST_ID_Is_Equal( &g_asFX_Effect[psEffect->m_tiParent.m_uiI].m_tiClient_Singleton, psEffect->m_tiParent ))
        {
            break;
        };
        psParent = g_asFX_Effect + psEffect->m_tiParent.m_uiI;

        if (ETgFX__GROUP != psParent->m_enEffect)
        {
            psParent = nullptr;
            break;
        }
        tiData = ETgFX__GROUP == psEffect->m_enEffect ? psEffect->m_tiData : KTgFX_DATA_INST_ID__INVALID;
        tgFX__Client__Group_On_Kill( tgFX_CLIENT_INST_ID_Query_Unsafe( &psEffect->m_tiClient_Singleton ), tiData, psParent->m_tiData );
    }
    while(0);

    if ((nullptr == psParent) && (ETgFX__GROUP == psEffect->m_enEffect))
    {
        tgFX__Client__Group_On_Kill( tgFX_CLIENT_INST_ID_Query_Unsafe( &psEffect->m_tiClient_Singleton ), psEffect->m_tiData, KTgFX_DATA_INST_ID__INVALID );
    };

    /* Tear down the effect and mark it for delete (invalidate the client id) */
    tgFX_CLIENT_INST_ID_Invalidate( &psEffect->m_tiClient_Singleton );
    psEffect->m_tiData = KTgFX_DATA_INST_ID__INVALID;
    psEffect->m_tiParent = KTgFX_CLIENT_INST_ID__INVALID;
    if (KTgID__INVALID_VALUE != psEffect->m_tiAttachment.m_uiKI)
    {
        tgAttachment__Decrement_Reference( psEffect->m_tiAttachment );
        psEffect->m_tiAttachment = KTgATTACHMENT_ID__INVALID;
    };
    psEffect->m_tiTarget.m_uiKI = KTgID__INVALID_VALUE;
    psEffect->m_pfnTerminate = nullptr;
    psEffect->m_pfnContact = nullptr;
    psEffect->m_enEffect = ETgFX__INVALID;
    psEffect->m_iPriority = 0;
    psEffect->m_tiEffect = KTgFX_EFFECT_ID__INVALID;
    psEffect->m_uiUpdate = 0;
    psEffect->m_uiRender_Visible = 0;

    g_aiFX__Client__Shared_State[uiIndex] = ETgFX_EFFECT_STATE__CLIENT__FREE;

    tgFX_Effect__Decrement_Reference( tiEffect );
}


/* ---- tgFX__Client__Set_Position_From_External_Update -------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgFX__Client__Set_Position_From_External_Update( TgFX_CLIENT_INST_ID_C tiClient, TgVEC_F32_04_1 vPos_W )
{
    TgUINT_E32                          uiIndex;
    STg2_FX_Command__Update__1_F32_04   sCommand;

    uiIndex = tgFX__Client__Get_Client_Index( tiClient );
    if (KTgMAX_U32 == uiIndex)
    {
        return;
    };

    sCommand.m_enCommand = ETgFX_COMMAND__CLIENT_TO_UPDATE__POSITION_SET;
    sCommand.m_sDest.m_tiData = g_asFX_Effect[uiIndex].m_tiData;
    sCommand.m_vF32_04 = vPos_W;
    tgFX__Client__Queue_Update_Command( g_asFX_Effect[uiIndex].m_enEffect, sCommand.m_enCommand, &sCommand );
}


/* ---- tgFX__Client__Set_Rotation_From_External_Update -------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgFX__Client__Set_Rotation_From_External_Update( TgFX_CLIENT_INST_ID_C tiClient, TgVEC_F32_04_1 qRot_W )
{
    TgUINT_E32                          uiIndex;
    STg2_FX_Command__Update__1_F32_04   sCommand;

    uiIndex = tgFX__Client__Get_Client_Index( tiClient );
    if (KTgMAX_U32 == uiIndex)
    {
        return;
    };

    sCommand.m_enCommand = ETgFX_COMMAND__CLIENT_TO_UPDATE__ROTATION_SET;
    sCommand.m_sDest.m_tiData = g_asFX_Effect[uiIndex].m_tiData;
    sCommand.m_vF32_04 = qRot_W;
    tgFX__Client__Queue_Update_Command( g_asFX_Effect[uiIndex].m_enEffect, sCommand.m_enCommand, &sCommand );
}


/* ---- tgFX__Client__Update_Position_From_Parent -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgFX__Client__Update_Position_From_Parent( TgFX_CLIENT_INST_ID_C tiClient, TgVEC_F32_04_1 vPos_W )
{
    TgUINT_E32                          uiIndex;
    STg2_FX_Command__Update__1_F32_04   sCommand;

    uiIndex = tgFX__Client__Get_Client_Index( tiClient );
    if (KTgMAX_U32 == uiIndex)
    {
        return;
    };

    sCommand.m_enCommand = ETgFX_COMMAND__CLIENT_TO_UPDATE__POSITION_UPDATE_FROM_PARENT;
    sCommand.m_sDest.m_tiData = g_asFX_Effect[uiIndex].m_tiData;
    sCommand.m_vF32_04 = vPos_W;
    tgFX__Client__Queue_Update_Command( g_asFX_Effect[uiIndex].m_enEffect, sCommand.m_enCommand, &sCommand );
}


/* ---- tgFX__Client__Update_Rotation_From_Parent -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgFX__Client__Update_Rotation_From_Parent( TgFX_CLIENT_INST_ID_C tiClient, TgVEC_F32_04_1 qRot_W )
{
    TgUINT_E32                          uiIndex;
    STg2_FX_Command__Update__1_F32_04   sCommand;

    uiIndex = tgFX__Client__Get_Client_Index( tiClient );
    if (KTgMAX_U32 == uiIndex)
    {
        return;
    };

    sCommand.m_enCommand = ETgFX_COMMAND__CLIENT_TO_UPDATE__ROTATION_UPDATE_FROM_PARENT;
    sCommand.m_sDest.m_tiData = g_asFX_Effect[uiIndex].m_tiData;
    sCommand.m_vF32_04 = qRot_W;
    tgFX__Client__Queue_Update_Command( g_asFX_Effect[uiIndex].m_enEffect, sCommand.m_enCommand, &sCommand );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgFX__Client__Inst_FX_Internal ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgFX_CLIENT_INST_ID tgFX__Client__Inst_FX_Internal( ETgFX__EFFECT_C enEffect, TgVOID_CP pData0, TgVOID_CP pData1, TgFX_EFFECT_ID_C tiFX, STg2_FX_Instance_CPCU psInstance )
{
    STg2_FX__Client_P                   psEffect;
    TgFX_DATA_INST_ID                   tiParent;
    TgUINT_E32                          uiEffect_Index;
    TgFX_CLIENT_INST_ID                 tiClient;

    /* Check to see if our parent is a group, and so need to ourselves to it as a child */
    tiParent = KTgFX_DATA_INST_ID__INVALID;
    do
    {
        STg2_FX__Client_P                   psParent;

        if (0 == (psInstance->m_uiInternal & 0xFF))
        {
            break;
        };

        if (KTgID__INVALID_VALUE == psInstance->m_tiParent.m_uiKI)
        {
            break;
        };

        if (!tgFX_CLIENT_INST_ID_Is_Equal( &g_asFX_Effect[psInstance->m_tiParent.m_uiI].m_tiClient_Singleton, psInstance->m_tiParent ))
        {
            break;
        };

        psParent = g_asFX_Effect + psInstance->m_tiParent.m_uiI;
        if (ETgFX__GROUP != psParent->m_enEffect)
        {
            break;
        };
        tiParent = psParent->m_tiData;
    }
    while(0);

    psEffect = (STg2_FX__Client_P)tgCM_UT_LF__ST__Pop( &g_sFX_Effect__Client__Effect.m_sStack );
    if (nullptr == psEffect)
    {
        return (KTgFX_CLIENT_INST_ID__INVALID);
    };

    uiEffect_Index = (TgUINT_E32)(psEffect - g_asFX_Effect);
    tgFX_CLIENT_INST_ID_Init( &psEffect->m_tiClient_Singleton, uiEffect_Index );
    g_aiFX__Client__Shared_State[uiEffect_Index] = ETgFX_EFFECT_STATE__CLIENT__RESERVED;

    tiClient = tgFX_CLIENT_INST_ID_Query_Unsafe( &psEffect->m_tiClient_Singleton );

    switch (enEffect)
    {
        case ETgFX__BEAM:      psEffect->m_tiData = tgFX__Client__Beam_Create_Data_Inst( tiClient, pData0, pData1, psInstance ); break;
        case ETgFX__BILLBOARD: psEffect->m_tiData = tgFX__Client__Billboard_Create_Data_Inst( tiClient, pData0, pData1, psInstance ); break;
        case ETgFX__DECAL:     psEffect->m_tiData = tgFX__Client__Decal_Create_Data_Inst( tiClient, pData0, pData1, psInstance ); break;
        case ETgFX__EMITTER:   psEffect->m_tiData = tgFX__Client__Emitter_Create_Data_Inst( tiClient, pData0, pData1, psInstance ); break;
        case ETgFX__GIB:       psEffect->m_tiData = tgFX__Client__GIB_Create_Data_Inst( tiClient, pData0, pData1, psInstance ); break;
        case ETgFX__GLASS:     psEffect->m_tiData = tgFX__Client__Glass_Create_Data_Inst( tiClient, pData0, pData1, psInstance ); break;
        case ETgFX__GROUP:     psEffect->m_tiData = tgFX__Client__Group_Create_Data_Inst( tiClient, pData0, pData1, psInstance ); break;
        case ETgFX__LIGHT:     psEffect->m_tiData = tgFX__Client__Light_Create_Data_Inst( tiClient, pData0, pData1, psInstance ); break;
        case ETgFX__LIQUID:    psEffect->m_tiData = tgFX__Client__Liquid_Create_Data_Inst( tiClient, pData0, pData1, psInstance ); break;
        case ETgFX__POST:      psEffect->m_tiData = tgFX__Client__Post_Create_Data_Inst( tiClient, pData0, pData1, psInstance ); break;
        case ETgFX__SOUND:     psEffect->m_tiData = tgFX__Client__Sound_Create_Data_Inst( tiClient, pData0, pData1, psInstance ); break;
        case ETgFX__TRAIL:     psEffect->m_tiData = tgFX__Client__Trail_Create_Data_Inst( tiClient, pData0, pData1, psInstance ); break;

        case ETgFX__INVALID:
        case ETgFX__EFFECT_MAX:
        default: TgS_NO_DEFAULT(break);
    };

    if (KTgID__INVALID_VALUE == psEffect->m_tiData.m_uiKI)
    {
        tgFX_CLIENT_INST_ID_Invalidate( &psEffect->m_tiClient_Singleton );
        g_aiFX__Client__Shared_State[uiEffect_Index] = ETgFX_EFFECT_STATE__CLIENT__FREE;
        TgSTD_ATOMIC(thread_fence)( TgSTD_MEMORY_ORDER(seq_cst) );

        tgCM_UT_LF__ST__Push( &g_sFX_Effect__Client__Effect.m_sStack, (STg2_UT_ST__ST_Node_P)psEffect );
        return (KTgFX_CLIENT_INST_ID__INVALID);
    };

    if (KTgID__INVALID_VALUE != tiFX.m_uiKI)
    {
        tgFX_Effect__Increment_Reference( tiFX );
    };

    if (KTgID__INVALID_VALUE != psInstance->m_tiParent.m_uiKI)
    {
        TgERROR_INDEX( psInstance->m_tiParent.m_uiI, g_asFX_Effect );
        psEffect->m_tiTarget = g_asFX_Effect[psInstance->m_tiParent.m_uiI].m_tiTarget;
        psEffect->m_uiRender_Visible = g_asFX_Effect[psInstance->m_tiParent.m_uiI].m_uiRender_Visible;
    }
    else
    {
        psEffect->m_tiTarget = psInstance->m_tiTarget;
        psEffect->m_uiRender_Visible = psInstance->m_uiRender_Visible ? 1u : 0u;
    };
    
    /* Check for attachment and add effect into the client update list appropriately */
    psEffect->m_uiUpdate = ETgFX_UPDATE__DEFAULT;
    if (0 != (psInstance->m_uiInternal & (ETgFX_UPDATE__EXTERNAL << 8)) || (KTgID__INVALID_VALUE != psInstance->m_tiAttachment.m_uiKI))
    {
        psEffect->m_uiUpdate = ETgFX_UPDATE__EXTERNAL;
    };
    psEffect->m_tiAttachment = psInstance->m_tiAttachment;

    psEffect->m_tiUpdate_Next = g_atiFX__Client__Update__Head[ETgFX_UPDATE__NEW_CLIENT];
    g_atiFX__Client__Update__Head[ETgFX_UPDATE__NEW_CLIENT] = tiClient;

    psEffect->m_tiParent = psInstance->m_tiParent;
    psEffect->m_pfnTerminate = psInstance->m_pfnTerminate;
    psEffect->m_uiTerminate_Parameter = psInstance->m_uiTerminate_Parameter;
    psEffect->m_pfnContact = psInstance->m_pfnContact;
    psEffect->m_uiContact_Parameter = psInstance->m_uiContact_Parameter;
    psEffect->m_enEffect = enEffect;
    psEffect->m_iPriority = psInstance->m_iPriority;
    psEffect->m_tiEffect = tiFX;

    g_aiFX__Client__Shared_State[uiEffect_Index] = ETgFX_EFFECT_STATE__CLIENT__ACTIVE;

    if (KTgID__INVALID_VALUE != tiParent.m_uiKI)
    {
        tgFX__Client__Group_Add_Child( tiParent, (TgUINT_E32)(psInstance->m_uiInternal & 0xFF), tiClient );
    }

    return (tiClient);
}
