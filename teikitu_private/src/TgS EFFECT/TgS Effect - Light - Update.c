/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Effect - Light - Update.c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.20 | »GUID« DE461472-5528-4A5B-A7F4-09CCAD73387B */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "TgS Effect - Internal.inl"


/* == Effect ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgFX__File__Light_Patch_File_Data ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgFX__File__Light_Patch_File_Data( STg2_FX_Light__File_Data_P psData )
{
    TgUINT_PTR                          uiData_Top;

    uiData_Top = (TgUINT_PTR)psData;

    psData->m_sAnim.m_sData_Offset.m_uiPosition += uiData_Top;
    psData->m_sAnim.m_sData_Offset.m_uiDirection += uiData_Top;
    psData->m_sAnim.m_sData_Offset.m_uiDiffuse_G10_P709 += uiData_Top;
    psData->m_sAnim.m_sData_Offset.m_uiSpecular_G10_P709 += uiData_Top;
    psData->m_sAnim.m_sData_Offset.m_uiAmbient_G10_P709 += uiData_Top;
    psData->m_sAnim.m_sData_Offset.m_uiGeom_Light += uiData_Top;
}


/* ---- tgFX__Update__Light_Create_Command --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgFX__Update__Light_Create_Command( TgATTRIBUTE_UNUSED STg2_FX_Instance_CP psInst, TgFX_DATA_INST_ID_C tiData, TgATTRIBUTE_UNUSED TgVOID_CP pData1 )
{
    STg2_FX__Light_P                    psLight;
    STg2_FX_Light__File_Data_CP         psFile_Data;

    psLight = g_asFX__Light + tiData.m_uiI;
    psFile_Data = psLight->m_psFile_Data;

    tgFX_Evaluate_AnimData_F32_04_1( &psLight->m_sExtend.m_vDiffuse_G10_P709, psFile_Data->m_sAnim.m_sParameter.m_psDiffuse_G10_P709, tgMH_SET1_F32_04_1( 0.0F ) );
    tgFX_Evaluate_AnimData_F32_04_1( &psLight->m_sExtend.m_vSpecular_G10_P709, psFile_Data->m_sAnim.m_sParameter.m_psSpecular_G10_P709, tgMH_SET1_F32_04_1( 0.0F ) );
    tgFX_Evaluate_AnimData_F32_04_1( &psLight->m_sExtend.m_vAmbient_G10_P709, psFile_Data->m_sAnim.m_sParameter.m_psAmbient_G10_P709, tgMH_SET1_F32_04_1( 0.0F ) );
    tgFX_Evaluate_AnimData_F32_04_1( &psLight->m_sExtend.m_vGeom_Light, psFile_Data->m_sAnim.m_sParameter.m_psGeom_Light, tgMH_SET1_F32_04_1( 0.0F ) );

    /* #TODO: Add Light and Assign ID */

    g_aenFX__Light__Shared__State[tiData.m_uiI] = ETgFX_EFFECT_STATE__CLIENT__ACTIVE;

    return (true);
}


/* ---- tgFX__Update__Light_Update ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgFX__Update__Light_Update( TgVEC_F32_04_1 vDT, TgFLOAT32_C fDT, ETgFX_UPDATE_C enUpdate )
{
    TgFX_DATA_INST_ID                   tiActive;
    STg2_FX__Light_P                    psLight;
    STg2_FX_Light__File_Data_CP         psFile_Data;

    tiActive = g_atiFX__Light__Update__Head[enUpdate];

    while (KTgID__INVALID_VALUE != tiActive.m_uiKI)
    {
        tgFX__Update__Light_Diag_Check_Effect( tiActive );

        psLight = g_asFX__Light + tiActive.m_uiI;
        psFile_Data = psLight->m_psFile_Data;

        if (!tgFX__Update__Light_Update_Life_Time( tiActive.m_uiI, fDT, vDT ))
        {
            tiActive = psLight->m_tiNext[ETgFX_NEXT__UPDATE];
            continue;
        };

        tgFX_Evaluate_AnimData_F32_04_1( &psLight->m_qRot_N2M, psFile_Data->m_sAnim.m_sParameter.m_psRot_N, psLight->m_vLive_Time );
        psLight->m_qRot_N2W = tgMH_QT_MUL_F32_04_1( psLight->m_qRot_N2M, psLight->m_qRot_M2W );
        tgFX_Evaluate_AnimData_F32_04_1( &psLight->m_vPos_N2M, psFile_Data->m_sAnim.m_sParameter.m_psPos_N, psLight->m_vLive_Time );
        psLight->m_vPos_N2W = tgMH_ADD_F32_04_1( psLight->m_vPos_M2W, tgMH_QT_TX_F32_04_1( psLight->m_vPos_N2M, psLight->m_qRot_M2W ) );

        tgFX_Evaluate_AnimData_F32_04_1( &psLight->m_sExtend.m_vDiffuse_G10_P709, psFile_Data->m_sAnim.m_sParameter.m_psDiffuse_G10_P709, psLight->m_vLive_Time );
        tgFX_Evaluate_AnimData_F32_04_1( &psLight->m_sExtend.m_vSpecular_G10_P709, psFile_Data->m_sAnim.m_sParameter.m_psSpecular_G10_P709, psLight->m_vLive_Time );
        tgFX_Evaluate_AnimData_F32_04_1( &psLight->m_sExtend.m_vAmbient_G10_P709, psFile_Data->m_sAnim.m_sParameter.m_psAmbient_G10_P709, psLight->m_vLive_Time );
        tgFX_Evaluate_AnimData_F32_04_1( &psLight->m_sExtend.m_vGeom_Light, psFile_Data->m_sAnim.m_sParameter.m_psGeom_Light, psLight->m_vLive_Time );

        /* #TODO: Update Light */

        tiActive = psLight->m_tiNext[ETgFX_NEXT__UPDATE];
    };
}


/* ---- tgFX__Update__Light_Process_Update_Command ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgFX__Update__Light_Process_Update_Command( ETgFX_COMMAND_C enCommand, TgVOID_CP pData, TgFX_DATA_INST_ID_C tiData )
{
    tgFX__Update__Light_Process_Update_Command_Default( enCommand, pData, tiData );
}
