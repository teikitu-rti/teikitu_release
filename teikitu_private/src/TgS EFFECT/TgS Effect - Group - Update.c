/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Effect - Group - Update.c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.12 | »GUID« 964CB1A6-814D-4E19-8E67-A83FCA98BF05 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

TgCOMPILER_ASSERT( TgARRAY_COUNT( ((STg2_FX__Group_P)0)->m_sExtend.m_atiChildren ) < 0xFF, 0 );
#include "TgS Effect - Internal.inl"


/* == Effect ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgFORCEINLINE TgBOOL                        tgFX__Update__Group_Is_Valid_Child( TgFX_CLIENT_INST_ID );
static TgVOID                               tgFX__Update__Group__Child_Create( TgFX_DATA_INST_ID );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgFX__File__Group_Patch_File_Data ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgFX__File__Group_Patch_File_Data( TgATTRIBUTE_UNUSED STg2_FX_Group__File_Data_P psData )
{
}


/* ---- tgFX__Client__Group_Add_Child -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgFX__Client__Group_Add_Child( TgFX_DATA_INST_ID_C tiParent_Data, TgUINT_E32_C uiIndex, TgFX_CLIENT_INST_ID_C tiClient )
{
    STg2_FX__Group_P                    psParent;

    psParent = g_asFX__Group + tiParent_Data.m_uiI;

    if (tiParent_Data.m_uiKI != psParent->m_tiData.m_uiKI)
    {
        return;
    };

    if (KTgFX_CLIENT_INST_ID__GROUP_DELAYED_SPAWN.m_uiKI == psParent->m_sExtend.m_atiChildren[uiIndex].m_uiKI)
    {
        TgWARNING_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Attempt to spawn a child that already exists / existed.\n" );
        return;
    };

    psParent->m_sExtend.m_atiChildren[uiIndex] = tiClient;
}


/* ---- tgFX__Client__Group_On_Kill ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgFX__Client__Group_On_Kill( TgFX_CLIENT_INST_ID_C tiClient, TgFX_DATA_INST_ID_C tiData, TgFX_DATA_INST_ID_C tiParent_Data )
{
    do /* Remove "this" from the parent child list */
    {
        STg2_FX__Group_P                    psParent;
        TgSINT_E32                          iChild_Index;

        if (KTgID__INVALID_VALUE == tiParent_Data.m_uiKI)
        {
            break;
        };

        TgPARAM_CHECK_INDEX( tiParent_Data.m_uiI, g_asFX__Group );
        psParent = g_asFX__Group + tiParent_Data.m_uiI;

        if (tiParent_Data.m_uiKI != psParent->m_tiData.m_uiKI)
        {
            break;
        };

        for (iChild_Index = 0; iChild_Index < (TgSINT_E32 )TgARRAY_COUNT( psParent->m_sExtend.m_atiChildren ); ++iChild_Index)
        {
            if (tiClient.m_uiKI != psParent->m_sExtend.m_atiChildren[iChild_Index].m_uiKI)
            {
                continue;
            };
            psParent->m_sExtend.m_atiChildren[iChild_Index] = KTgFX_CLIENT_INST_ID__INVALID;
            TgSTD_ATOMIC(fetch_add)( &psParent->m_sExtend.m_xniChildren, -1 );
            break;
        };
    }
    while (0);

    do /* Kill all child effects */
    {
        STg2_FX__Group_P                    psGroup;
        TgSINT_E32                          iChild_Index;

        if (KTgID__INVALID_VALUE == tiData.m_uiKI)
        {
            break;
        };

        psGroup = g_asFX__Group + tiData.m_uiI;

        if (tiData.m_uiKI != psGroup->m_tiData.m_uiKI)
        {
            break;
        };

        for (iChild_Index = 0; iChild_Index < (TgSINT_E32 )TgARRAY_COUNT( psGroup->m_sExtend.m_atiChildren ); ++iChild_Index)
        {
            if (KTgID__INVALID_VALUE == psGroup->m_sExtend.m_atiChildren[iChild_Index].m_uiKI)
            {
                continue;
            };
            tgFX__Client__Kill( psGroup->m_sExtend.m_atiChildren[iChild_Index] );
        };

        /* Kill the system effect (Deferred from original message) */
        tgFX__Update__Group_Kill( tiData.m_uiI );
    }
    while (0);
}


/* ---- tgFX__Update__Group_Create_Command --------------------------------------------------------------------------------------------------------------------------------------- */
/* Executed on Client Thread                                                                                                                                                       */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgFX__Update__Group_Create_Command( TgATTRIBUTE_UNUSED STg2_FX_Instance_CP psInst, TgFX_DATA_INST_ID_C tiData, TgATTRIBUTE_UNUSED TgVOID_CP pData1 )
{
    STg2_FX_Group__File_Data_CP         psFile_Data;
    STg2_FX__Group_P                    psGroup;
    TgSINT_E32                          iIndex;

    psGroup = g_asFX__Group + tiData.m_uiI;
    psFile_Data = psGroup->m_psFile_Data;

    TgSTD_ATOMIC(store)( &psGroup->m_sExtend.m_xniChildren, 0 );
    psGroup->m_sExtend.m_fLive_Time = 0.0F;

    for (iIndex = 0; iIndex < (TgSINT_E32 )TgARRAY_COUNT( psGroup->m_sExtend.m_atiChildren ); ++iIndex)
    {
        if ((iIndex >= psFile_Data->m_niEffect) || (KTgEMPTY_HASH == psFile_Data->m_asEffect[iIndex].m_uiHash_Effect))
        {
            psGroup->m_sExtend.m_atiChildren[iIndex] = KTgFX_CLIENT_INST_ID__INVALID;
        }
        else
        {
            psGroup->m_sExtend.m_atiChildren[iIndex] = KTgFX_CLIENT_INST_ID__GROUP_DELAYED_SPAWN;
            TgSTD_ATOMIC(fetch_add)( &psGroup->m_sExtend.m_xniChildren, 1 );
        }
    }

    /* Group state is completely dependent on the children */
    g_aenFX__Group__Shared__State[tiData.m_uiI] = ETgFX_EFFECT_STATE__UPDATE__ACTIVE_INFINITE;

    return (true);
}


/* ---- tgFX__Update__Group_Update ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgFX__Update__Group_Update( TgATTRIBUTE_UNUSED TgVEC_F32_04_1 vDT, TgFLOAT32_C fDT, ETgFX_UPDATE_C enUpdate )
{
    TgFX_DATA_INST_ID                   tiActive;
    STg2_FX__Group_P                    psGroup;

    tiActive = g_atiFX__Group__Update__Head[enUpdate];

    while (KTgID__INVALID_VALUE != tiActive.m_uiKI)
    {
        tgFX__Update__Group_Diag_Check_Effect( tiActive );

        psGroup = g_asFX__Group + tiActive.m_uiI;

        psGroup->m_sExtend.m_fLive_Time += fDT;

        tgFX__Update__Group__Child_Create( tiActive );

        if (0 >= TgSTD_ATOMIC(load)( &psGroup->m_sExtend.m_xniChildren ))
        {
            tgFX__Update__Command__Group_Kill_Self( psGroup->m_tiData );
        };

        tiActive = psGroup->m_tiNext[ETgFX_NEXT__UPDATE];
    };
}


/* ---- tgFX__Update__Group_Process_Update_Command ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgFX__Update__Group_Process_Update_Command( ETgFX_COMMAND_C enCommand, TgVOID_CP pData, TgFX_DATA_INST_ID_C tiData )
{
    STg2_FX__Group_P                    psGroup;
    TgUINT_E32                          iChild;

    psGroup = g_asFX__Group + tiData.m_uiI;
    switch (enCommand)
    {
        case ETgFX_COMMAND__CLIENT_TO_UPDATE__KILL:
            break;

            /* Executed on Client Thread */
        case ETgFX_COMMAND__CLIENT_TO_UPDATE__STOP:
            for (iChild = 0; iChild < TgARRAY_COUNT( psGroup->m_sExtend.m_atiChildren ); ++iChild)
            {
                if (!tgFX__Update__Group_Is_Valid_Child( psGroup->m_sExtend.m_atiChildren[iChild] ))
                {
                    continue;
                };
                tgFX__Client__Stop( psGroup->m_sExtend.m_atiChildren[iChild] );
            };
            break;

            /* Executed on Client Thread */
        case ETgFX_COMMAND__CLIENT_TO_UPDATE__POSITION_SET:
        {
            TgVEC_F32_04_1                    vPos_W;
            TgVEC_F32_04_1                    vDelta;

            vPos_W = tgMH_SETU_F32_04_1( (TgFLOAT32_CP)pData );
            vDelta = tgMH_SUB_F32_04_1( vPos_W, psGroup->m_vPos_N2W );
            psGroup->m_vPos_N2W = vPos_W;

            for (iChild = 0; iChild < TgARRAY_COUNT( psGroup->m_sExtend.m_atiChildren ); ++iChild)
            {
                if (!tgFX__Update__Group_Is_Valid_Child( psGroup->m_sExtend.m_atiChildren[iChild] ))
                {
                    continue;
                };
                tgFX__Client__Update_Position_From_Parent( psGroup->m_sExtend.m_atiChildren[iChild], vDelta );
            };
        };
        break;

        /* Executed on Client Thread */
        case ETgFX_COMMAND__CLIENT_TO_UPDATE__POSITION_UPDATE_FROM_PARENT:
        {
            TgVEC_F32_04_1                    vDelta;

            vDelta = tgMH_SETU_F32_04_1( (TgFLOAT32_CP)pData );
            psGroup->m_vPos_N2W = tgMH_ADD_F32_04_1( vDelta, psGroup->m_vPos_N2W );

            for (iChild = 0; iChild < TgARRAY_COUNT( psGroup->m_sExtend.m_atiChildren ); ++iChild)
            {
                if (!tgFX__Update__Group_Is_Valid_Child( psGroup->m_sExtend.m_atiChildren[iChild] ))
                {
                    continue;
                };
                tgFX__Client__Update_Position_From_Parent( psGroup->m_sExtend.m_atiChildren[iChild], vDelta );
            };
        };
        break;

        /* Executed on Client Thread */
        case ETgFX_COMMAND__CLIENT_TO_UPDATE__ROTATION_SET:
        {
            TgVEC_F32_04_1                    qRot_W;
            TgVEC_F32_04_1                    qRot_Inv_W;
            TgVEC_F32_04_1                    qRot;

            qRot_W = tgMH_SETU_F32_04_1( (TgFLOAT32_CP)pData );
            qRot_Inv_W = tgMH_QT_INV_F32_04_1( psGroup->m_qRot_N2W );
            psGroup->m_qRot_N2W = qRot_W;
            qRot = tgMH_QT_MUL_F32_04_1( psGroup->m_qRot_N2W, qRot_Inv_W );

            for (iChild = 0; iChild < TgARRAY_COUNT( psGroup->m_sExtend.m_atiChildren ); ++iChild)
            {
                if (!tgFX__Update__Group_Is_Valid_Child( psGroup->m_sExtend.m_atiChildren[iChild] ))
                {
                    continue;
                };
                tgFX__Client__Update_Rotation_From_Parent( psGroup->m_sExtend.m_atiChildren[iChild], qRot );
            };
        };
        break;

        /* Executed on Client Thread */
        case ETgFX_COMMAND__CLIENT_TO_UPDATE__ROTATION_UPDATE_FROM_PARENT:
        {
            TgVEC_F32_04_1                    vPos_W;
            TgVEC_F32_04_1                    qRot;
            TgVEC_F32_04_1                    qRot_Inv_W;
            TgVEC_F32_04_1                    vDelta;

            qRot = tgMH_SETU_F32_04_1( (TgFLOAT32_CP)pData );
            qRot_Inv_W = tgMH_QT_INV_F32_04_1( psGroup->m_qRot_N2W );
            vPos_W = psGroup->m_vPos_N2W;
            psGroup->m_vPos_N2W = tgMH_QT_TX_F32_04_1( psGroup->m_vPos_N2W, qRot_Inv_W );
            psGroup->m_qRot_N2W = tgMH_QT_MUL_F32_04_1( qRot, psGroup->m_qRot_N2W );
            psGroup->m_vPos_N2W = tgMH_QT_TX_F32_04_1( psGroup->m_vPos_N2W, psGroup->m_qRot_N2W );
            qRot = tgMH_QT_MUL_F32_04_1( psGroup->m_qRot_N2W, qRot_Inv_W );
            vDelta = tgMH_SUB_F32_04_1( psGroup->m_vPos_N2W, vPos_W );

            for (iChild = 0; iChild < TgARRAY_COUNT( psGroup->m_sExtend.m_atiChildren ); ++iChild)
            {
                if (!tgFX__Update__Group_Is_Valid_Child( psGroup->m_sExtend.m_atiChildren[iChild] ))
                {
                    continue;
                };
                tgFX__Client__Update_Position_From_Parent( psGroup->m_sExtend.m_atiChildren[iChild], vDelta );
                tgFX__Client__Update_Rotation_From_Parent( psGroup->m_sExtend.m_atiChildren[iChild], qRot );
            };
        };
        break;

        /* Executed on Client Thread */
        case ETgFX_COMMAND__CLIENT_TO_UPDATE__VISIBLE:
            for (iChild = 0; iChild < TgARRAY_COUNT( psGroup->m_sExtend.m_atiChildren ); ++iChild)
            {
                if (!tgFX__Update__Group_Is_Valid_Child( psGroup->m_sExtend.m_atiChildren[iChild] ))
                {
                    continue;
                };
                tgFX__Client__Set_Visible( psGroup->m_sExtend.m_atiChildren[iChild], *(TgBOOL_CP)pData );
            };
            break;

            /* Executed on Client Thread */
        case ETgFX_COMMAND__CLIENT_TO_UPDATE__CREATE: TgATTRIBUTE_FALLTHROUGH /**< Fall Through - Invalid */
        case ETgFX_COMMAND__CLIENT_TO_UPDATE__NOTIFY: TgATTRIBUTE_FALLTHROUGH /**< Fall Through - Invalid */
        case ETgFX_COMMAND__CLIENT_TO_UPDATE__SPIN: TgATTRIBUTE_FALLTHROUGH /**< Fall Through - Invalid */
        case ETgFX_COMMAND__SCENE_TO_RENDER__BEGIN: TgATTRIBUTE_FALLTHROUGH /**< Fall Through - Invalid */
        case ETgFX_COMMAND__UPDATE_TO_CLIENT__BEGIN: TgATTRIBUTE_FALLTHROUGH /**< Fall Through - Invalid */
        case ETgFX_COMMAND__UPDATE_TO_CLIENT__NOTIFY: TgATTRIBUTE_FALLTHROUGH /**< Fall Through - Invalid */
        case ETgFX_COMMAND__UPDATE_TO_CLIENT__FREE: TgATTRIBUTE_FALLTHROUGH /**< Fall Through - Invalid */
        case ETgFX_COMMAND__MAX: /**< Fall Through - Invalid */
            TgDIAG(false);
            TgS_NO_DEFAULT( break );
    };
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgFX__Update__Group_Is_Valid_Child --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgFORCEINLINE TgBOOL tgFX__Update__Group_Is_Valid_Child( TgFX_CLIENT_INST_ID tiClient )
{
    if (KTgFX_CLIENT_INST_ID__GROUP_DELAYED_SPAWN.m_uiKI == tiClient.m_uiKI)
        return (false);
    if (KTgID__INVALID_VALUE == tiClient.m_uiKI)
        return (false);
    return (true);
}


/* ---- tgFX__Update__Group__Child_Create ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgFX__Update__Group__Child_Create( TgFX_DATA_INST_ID tiData )
{
    STg2_FX__Group_P                    psGroup;
    STg2_FX_Instance                    sInstance;
    TgUINT_E32                          uiIndex;

    tgFX__Update__Group_Diag_Check_Effect( tiData );
    psGroup = g_asFX__Group + tiData.m_uiI;

    tgMM_Set_U08_0x00( &sInstance, sizeof( sInstance ) );

    sInstance.m_vScale = psGroup->m_vScale;
    sInstance.m_tiParent = psGroup->m_tiClient;
    sInstance.m_tiTarget.m_uiKI = KTgID__INVALID_VALUE;

    for (uiIndex = 0; uiIndex < TgARRAY_COUNT( psGroup->m_sExtend.m_atiChildren ); ++uiIndex)
    {
        STg2_FX_Group_Effect__File_Data_CP psEffect_Data;

        if (KTgFX_CLIENT_INST_ID__GROUP_DELAYED_SPAWN.m_uiKI != psGroup->m_sExtend.m_atiChildren[uiIndex].m_uiKI)
        {
            continue;
        };

        psEffect_Data = psGroup->m_psFile_Data->m_asEffect + uiIndex;
        if (psEffect_Data->m_fStart > psGroup->m_sExtend.m_fLive_Time)
        {
            continue;
        };

        sInstance.m_vPos_N2W = tgMH_ADD_F32_04_1( tgMH_QT_TX_F32_04_1( psEffect_Data->m_vPosition, psGroup->m_qRot_N2W ), psGroup->m_vPos_N2W );
        sInstance.m_qRot_N2W = tgMH_QT_MUL_F32_04_1( psEffect_Data->m_vRotation, psGroup->m_qRot_N2W );
        sInstance.m_uiInternal = (ETgFX_UPDATE__EXTERNAL << 8) | (uiIndex & 0xFF);

        tgFX__Update__Command__Group_Create( psEffect_Data->m_uiHash_Effect, &sInstance );
    };
}
