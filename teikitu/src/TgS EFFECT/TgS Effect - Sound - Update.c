/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Effect - Sound - Update.c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.12 | »GUID« 964CB1A6-814D-4E19-8E67-A83FCA98BF05 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "TgS Effect - Internal.inl"


/* == Effect ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgFX__File__Sound_Patch_File_Data ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgFX__File__Sound_Patch_File_Data( STg2_FX_Sound__File_Data_P UNUSED_PARAM psData )
{
}


/* ---- tgFX__Update__Sound_Create_Command --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgFX__Update__Sound_Create_Command( STg2_FX_Instance_CP UNUSED_PARAM psInst, TgFX_DATA_INST_ID_C tiData, TgVOID_CP UNUSED_PARAM pData1 )
{
    STg2_FX__Sound_P                    psSound;
    STg2_FX_Sound__File_Data_CP         psFile_Data;
    TgSN_INST_ID                        tiSound_Instance;

    psSound = g_asFX__Sound + tiData.m_uiI;
    psFile_Data = psSound->m_psFile_Data;

    tiSound_Instance = tgSN_Sound_Inst__Init( psFile_Data->m_tiSound, nullptr );
    if (KTgID__INVALID_VALUE == tiSound_Instance.m_uiKI)
    {
        TgWARNING_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Sound instance init failed.\n" );
        return (false);
    };

    psSound->m_sExtend.m_vDir_W = tgMH_QT_TX_F32_04_1( psFile_Data->m_vDirection, psSound->m_qRot_N2W );

    psSound->m_sExtend.m_tiSound_Instance = tiSound_Instance;

    tgSN_Sound_Inst__Set_Position( tiSound_Instance, psSound->m_vPos_N2W );
    tgSN_Sound_Inst__Set_Direction( tiSound_Instance, psSound->m_sExtend.m_vDir_W );

    /* Sound lift time is controlled by the audio module */
    g_aenFX__Sound__Shared__State[tiData.m_uiI] = ETgFX_EFFECT_STATE__UPDATE__ACTIVE_INFINITE;

    return (true);
}


/* ---- tgFX__Update__Sound_Update ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgFX__Update__Sound_Update( TgVEC_F32_04_1 UNUSED_PARAM vdT, TgFLOAT32_C UNUSED_PARAM fDT, ETgFX_UPDATE_C enUpdate )
{
    TgFX_DATA_INST_ID                   tiActive;
    STg2_FX__Sound_P                    psSound;

    tiActive = g_atiFX__Sound__Update__Head[enUpdate];

    while (KTgID__INVALID_VALUE != tiActive.m_uiKI)
    {
        tgFX__Update__Sound_Diag_Check_Effect( tiActive );

        psSound = g_asFX__Sound + tiActive.m_uiI;

        if (!tgSN_Sound_Inst__Is_Valid( psSound->m_sExtend.m_tiSound_Instance ))
        {
            psSound->m_sExtend.m_tiSound_Instance = KTgSN_INST_ID__INVALID;
            tgFX__Update__Command__Sound_Kill_Self( psSound->m_tiData );
            continue;
        };

        tiActive = psSound->m_tiNext[ETgFX_NEXT__UPDATE];
    };
}


/* ---- tgFX__Update__Sound_Process_Update_Command ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgFX__Update__Sound_Process_Update_Command( ETgFX_COMMAND_C enCommand, TgVOID_CP pData, TgFX_DATA_INST_ID_C tiData )
{
    STg2_FX__Sound_P                    psSound;

    tgFX__Update__Sound_Process_Update_Command_Default( enCommand, pData, tiData );

    psSound = g_asFX__Sound + tiData.m_uiI;
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

        case ETgFX_COMMAND__CLIENT_TO_UPDATE__KILL:
            if (KTgID__INVALID_VALUE != psSound->m_sExtend.m_tiSound_Instance.m_uiKI)
            {
                tgSN_Sound_Inst__Free( psSound->m_sExtend.m_tiSound_Instance );
                psSound->m_sExtend.m_tiSound_Instance = KTgSN_INST_ID__INVALID;
            };
            break;

        case ETgFX_COMMAND__CLIENT_TO_UPDATE__STOP:
            if (KTgID__INVALID_VALUE != psSound->m_sExtend.m_tiSound_Instance.m_uiKI)
            {
                tgSN_Sound_Inst__Event_Stop( psSound->m_sExtend.m_tiSound_Instance );
            };
            break;

        case ETgFX_COMMAND__CLIENT_TO_UPDATE__POSITION_SET:
        case ETgFX_COMMAND__CLIENT_TO_UPDATE__POSITION_UPDATE_FROM_PARENT:
            tgSN_Sound_Inst__Set_Position( psSound->m_sExtend.m_tiSound_Instance, psSound->m_vPos_N2W );
            break;

        case ETgFX_COMMAND__CLIENT_TO_UPDATE__ROTATION_SET:
        case ETgFX_COMMAND__CLIENT_TO_UPDATE__ROTATION_UPDATE_FROM_PARENT:
            psSound->m_sExtend.m_vDir_W = tgMH_QT_TX_F32_04_1( psSound->m_psFile_Data->m_vDirection, psSound->m_qRot_N2W );
            tgSN_Sound_Inst__Set_Direction( psSound->m_sExtend.m_tiSound_Instance, psSound->m_sExtend.m_vDir_W );
            tgSN_Sound_Inst__Set_Position( psSound->m_sExtend.m_tiSound_Instance, psSound->m_vPos_N2W );
            break;

        case ETgFX_COMMAND__CLIENT_TO_UPDATE__VISIBLE: /**< Fall Through - No implementation */
            break;
    };
}
