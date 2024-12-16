/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Effect - Beam - Update.c
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

/* ---- tgFX__File__Beam_Patch_File_Data ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgFX__File__Beam_Patch_File_Data( STg2_FX_Beam__File_Data_P psData )
{
    TgUINT_PTR                          uiData_Top;

    uiData_Top = (TgUINT_PTR)psData;

    TgVERIFY(psData->m_nuiPoints> 1);

    psData->m_sShape.m_sData_Offset.m_uiShape_Colour += uiData_Top;
    psData->m_sShape.m_sData_Offset.m_uiShape_Offset += uiData_Top;
    psData->m_sShape.m_sData_Offset.m_uiShape_Width += uiData_Top;
    psData->m_sShape.m_sData_Offset.m_uiShape_Fraction += uiData_Top;
    psData->m_sShape.m_sData_Offset.m_uiShape_Normalized_T += uiData_Top;

    psData->m_sAnim.m_sData_Offset.m_uiEnd_Position += uiData_Top;
    psData->m_sAnim.m_sData_Offset.m_uiSG0_SG1 += uiData_Top;
}


/* ---- tgFX__Update__Beam_Create_Command ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgFX__Update__Beam_Create_Command( STg2_FX_Instance_CP UNUSED_PARAM psInst, TgFX_DATA_INST_ID_C tiData, TgVOID_CP UNUSED_PARAM pData1 )
{
    STg2_FX__Beam_P                     psBeam;
    STg2_FX_Beam__File_Data_CP          psFile_Data;
    TgUN_V128                           uAnim;

    psBeam = g_asFX__Beam + tiData.m_uiI;
    psFile_Data = psBeam->m_psFile_Data;

#if defined(TgBUILD_FEATURE__GRAPHICS_VFX)
    tgFX__Update__Set_Render_Data_From_Material_Hash( nullptr, &psBeam->m_tiMaterial, &psBeam->m_enVertex, psFile_Data->m_uiHash_Material );

    if (KTgID__INVALID_VALUE == psBeam->m_tiMaterial.m_uiKI)
    {
        return (false);
    };

    tgRN_Calc_UV_Animation_F32_04_1( &psBeam->m_sExtend.m_vUV_01_Constant, &psBeam->m_sExtend.m_vUV_01_Scale, psBeam->m_tiMaterial, KTgZERO_V128.m_vF32_04_1, KTgZERO_V128.m_vF32_04_1 );
/*# defined(TgBUILD_FEATURE__GRAPHICS_VFX) */
#endif

    psBeam->m_sExtend.m_vEnd_Variance = tgMH_MAD_F32_04_1( tgMH_SET1_F32_04_1( tgCM_RAND_ONE_F32() ), psFile_Data->m_vEnd_Position_RNG, psFile_Data->m_vEnd_Position_MID );
    psBeam->m_sExtend.m_vEnd_Variance = tgMH_Init_Vector_F32_04_1( psBeam->m_sExtend.m_vEnd_Variance );

    tgFX_Evaluate_AnimData_F32_04_1( &psBeam->m_sExtend.m_vEnd_Position, psFile_Data->m_sAnim.m_sParameter.m_psEnd_Position, tgMH_SET1_F32_04_1( 0.0F ) );
    psBeam->m_sExtend.m_vEnd_Position = tgMH_Init_Vector_F32_04_1( psBeam->m_sExtend.m_vEnd_Position );
    tgFX_Evaluate_AnimData_F32_04_1( &uAnim.m_vF32_04_1, psFile_Data->m_sAnim.m_sParameter.m_psSG0_SG1, tgMH_SET1_F32_04_1( 0.0F ) );
    psBeam->m_sExtend.m_fShape_Start_Fraction = tgCM_MAX_F32( 0.0F, uAnim.m_vS_F32_04_1.x );
    psBeam->m_sExtend.m_fShape_End_Fraction = tgCM_MAX_F32( 0.0F, uAnim.m_vS_F32_04_1.y );

    if (psBeam->m_sTime.m_fTime_End__Start < 0.0F)
        g_aenFX__Beam__Shared__State[tiData.m_uiI] = ETgFX_EFFECT_STATE__UPDATE__ACTIVE_INFINITE;
    else
        g_aenFX__Beam__Shared__State[tiData.m_uiI] = ETgFX_EFFECT_STATE__UPDATE__ACTIVE_FIRST;

    return (true);
}


/* ---- tgFX__Update__Beam_Update ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgFX__Update__Beam_Update( TgVEC_F32_04_1 vdT, TgFLOAT32_C fDT, ETgFX_UPDATE_C enUpdate )
{
    TgFX_DATA_INST_ID                   tiActive;
    STg2_FX__Beam_PU                    psBeam;
    STg2_FX_Beam__File_Data_CP          psFile_Data;
    TgUN_V128                           uAnim;
    TgVEC_F32_04_1                      vT;

    tiActive = g_atiFX__Beam__Update__Head[enUpdate];

    while (KTgID__INVALID_VALUE != tiActive.m_uiKI)
    {
        tgFX__Update__Beam_Diag_Check_Effect( tiActive );

        psBeam = g_asFX__Beam + tiActive.m_uiI;
        psFile_Data = psBeam->m_psFile_Data;

        if (!tgFX__Update__Beam_Update_Life_Time( tiActive.m_uiI, fDT, vdT ))
        {
            tiActive = psBeam->m_tiNext[ETgFX_NEXT__UPDATE];
            continue;
        };

        vT = tgMH_DIV_F32_04_1( psBeam->m_vLive_Time, tgMH_SET1_F32_04_1( psBeam->m_sTime.m_fTime_Total ) );
        tgFX_Evaluate_AnimData_F32_04_1( &psBeam->m_sExtend.m_vEnd_Position, psFile_Data->m_sAnim.m_sParameter.m_psEnd_Position, vT );
        psBeam->m_sExtend.m_vEnd_Position = tgMH_Init_Vector_F32_04_1( psBeam->m_sExtend.m_vEnd_Position );
        tgFX_Evaluate_AnimData_F32_04_1( &uAnim.m_vF32_04_1, psFile_Data->m_sAnim.m_sParameter.m_psSG0_SG1, vT );
        psBeam->m_sExtend.m_fShape_Start_Fraction = uAnim.m_vS_F32_04_1.x;
        psBeam->m_sExtend.m_fShape_End_Fraction = uAnim.m_vS_F32_04_1.y;

        tiActive = psBeam->m_tiNext[ETgFX_NEXT__UPDATE];
    };
}


/* ---- tgFX__Update__Beam_Process_Update_Command -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgFX__Update__Beam_Process_Update_Command( ETgFX_COMMAND_C enCommand, TgVOID_CP pData, TgFX_DATA_INST_ID_C tiData )
{
    tgFX__Update__Beam_Process_Update_Command_Default( enCommand, pData, tiData );
}
