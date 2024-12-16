/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Effect - Billboard - Update.c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.12 | »GUID« 964CB1A6-814D-4E19-8E67-A83FCA98BF05 */
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

/* ---- tgFX__File__Billboard_Patch_File_Data ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgFX__File__Billboard_Patch_File_Data( STg2_FX_Billboard__File_Data_P psData )
{
    TgUINT_PTR                          uiData_Top;

    uiData_Top = (TgUINT_PTR)psData;

    psData->m_sAnim.m_sData_Offset.m_uiColour += uiData_Top;
    psData->m_sAnim.m_sData_Offset.m_uiSize += uiData_Top;
}


/* ---- tgFX__Update__Billboard_Create_Command ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgFX__Update__Billboard_Create_Command( TgATTRIBUTE_UNUSED STg2_FX_Instance_CP psInst, TgFX_DATA_INST_ID_C tiData, TgATTRIBUTE_UNUSED TgVOID_CP pData1 )
{
    STg2_FX__Billboard_P                psFX;
    STg2_FX_Billboard__File_Data_CP     psFile_Data;

    psFX = g_asFX__Billboard + tiData.m_uiI;
    psFile_Data = psFX->m_psFile_Data;

#if defined(TgBUILD_FEATURE__GRAPHICS_VFX)
    tgFX__Update__Set_Render_Data_From_Material_Hash( nullptr, &psFX->m_tiMaterial, &psFX->m_enVertex, psFile_Data->m_uiHash_Material );

    if (KTgID__INVALID_VALUE == psFX->m_tiMaterial.m_uiKI)
    {
        return (false);
    }

    tgRN_Calc_UV_Animation_F32_04_1( &psFX->m_sExtend.m_vUV_01_Constant, &psFX->m_sExtend.m_vUV_01_Scale, psFX->m_tiMaterial, KTgZERO_V128.m_vF32_04_1, KTgZERO_V128.m_vF32_04_1 );
/*# defined(TgBUILD_FEATURE__GRAPHICS_VFX) */
#endif

    psFX->m_sExtend.m_vPlnX = tgMH_SET1_F32_04_1( 0.0F );
    psFX->m_sExtend.m_vPlnY = tgMH_SET1_F32_04_1( 0.0F );

    psFX->m_sExtend.m_fSpin = tgCM_RAND_ONE_F32()*psFile_Data->m_fSpin_RNG + psFile_Data->m_fSpin_MID;
    tgFX_Evaluate_AnimData_F32_04_1( &psFX->m_sExtend.m_vColour, psFile_Data->m_sAnim.m_sParameter.m_psColour, tgMH_SET1_F32_04_1( 0.0F ) );
    tgFX_Evaluate_AnimData_F32_04_1( &psFX->m_sExtend.m_vSize, psFile_Data->m_sAnim.m_sParameter.m_psSize, tgMH_SET1_F32_04_1( 0.0F ) );

    if (psFX->m_sTime.m_fTime_End__Start < 0.0F)
        g_aenFX__Billboard__Shared__State[tiData.m_uiI] = ETgFX_EFFECT_STATE__UPDATE__ACTIVE_INFINITE;
    else
        g_aenFX__Billboard__Shared__State[tiData.m_uiI] = ETgFX_EFFECT_STATE__UPDATE__ACTIVE_FIRST;

    return (true);
}


/* ---- tgFX__Update__Billboard_Update ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgFX__Update__Billboard_Update( TgVEC_F32_04_1 vdT, TgFLOAT32_C fDT, ETgFX_UPDATE_C enUpdate )
{
    TgFX_DATA_INST_ID                   tiActive;
    STg2_FX__Billboard_P                psBillboard;
    STg2_FX_Billboard__File_Data_CP     psFile_Data;

    tiActive = g_atiFX__Billboard__Update__Head[enUpdate];

    while (KTgID__INVALID_VALUE != tiActive.m_uiKI)
    {
        tgFX__Update__Billboard_Diag_Check_Effect( tiActive );

        psBillboard = g_asFX__Billboard + tiActive.m_uiI;
        psFile_Data = psBillboard->m_psFile_Data;

        if (!tgFX__Update__Billboard_Update_Life_Time( tiActive.m_uiI, fDT, vdT ))
        {
            tiActive = psBillboard->m_tiNext[ETgFX_NEXT__UPDATE];
            continue;
        };

        tgFX_Evaluate_AnimData_F32_04_1( &psBillboard->m_sExtend.m_vColour, psFile_Data->m_sAnim.m_sParameter.m_psColour, psBillboard->m_vLive_Time );
        tgFX_Evaluate_AnimData_F32_04_1( &psBillboard->m_sExtend.m_vSize, psFile_Data->m_sAnim.m_sParameter.m_psSize, psBillboard->m_vLive_Time );
        psBillboard->m_sExtend.m_fSpin += psFile_Data->m_fSpin_Speed*fDT;

        tiActive = psBillboard->m_tiNext[ETgFX_NEXT__UPDATE];
    };
}


/* ---- tgFX__Update__Billboard_Process_Update_Command --------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgFX__Update__Billboard_Process_Update_Command( ETgFX_COMMAND_C enCommand, TgVOID_CP pData, TgFX_DATA_INST_ID_C tiData )
{
    tgFX__Update__Billboard_Process_Update_Command_Default( enCommand, pData, tiData );
}
