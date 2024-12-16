/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Effect - Beam - Scene.c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.20 | »GUID« DE461472-5528-4A5B-A7F4-09CCAD73387B */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Effect ===================================================================================================================================================================== */
#if defined(TgBUILD_FEATURE__GRAPHICS_VFX)

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Parent File Local Functions                                                                                                                                                    */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgFX_Beam__Update_BA ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgFX_Beam__Update_BA( TgFX_DATA_INST_ID tiData )
{
    STg2_FX__Beam_PC                    psBeam = g_asFX__Beam + tiData.m_uiI;
    STg2_FX_Beam__File_Data_CPC         psFile_Data = psBeam->m_psFile_Data;
    STg2_FX__Beam__Extend_Data_CPC      psExtend = &psBeam->m_sExtend;
    TgFLOAT32_CPC                       pfShape_Width = psFile_Data->m_sShape.m_sData.m_pfShape_Width;
    TgFLOAT32_CPC                       pfShape_Normalized_T = psFile_Data->m_sShape.m_sData.m_pfShape_Normalized_T;

    TgUINT_F32                          uiStart_Frame, uiEnd_Frame, uiFrame;

    /* In the shape key-frame lists, skip until the start of the beam is within the range of a set of key frames. */
    for (uiStart_Frame = 0; uiStart_Frame + 1 < psFile_Data->m_nuiPoints && pfShape_Normalized_T[uiStart_Frame + 1] <= psExtend->m_fShape_Start_Fraction; ++uiStart_Frame) {};
    for (uiEnd_Frame = uiStart_Frame; uiEnd_Frame + 1 < psFile_Data->m_nuiPoints && pfShape_Normalized_T[uiEnd_Frame + 1] <= psExtend->m_fShape_End_Fraction; ++uiEnd_Frame) {};

    /* Validate that we are within the key frames for the shape data. */
    psBeam->m_vBA_Max_W = psBeam->m_vBA_Max_W;
    psBeam->m_vBA_Min_W = psBeam->m_vBA_Max_W;
    if (pfShape_Normalized_T[uiStart_Frame] > psExtend->m_fShape_Start_Fraction)
    {
        return;
    };

    if (pfShape_Normalized_T[uiEnd_Frame] > psExtend->m_fShape_End_Fraction)
    {
        return;
    };

    /* Generate all the quads between the first two vertices and the last two vertices. */
    for (uiFrame = uiStart_Frame; uiFrame <= uiEnd_Frame; ++uiFrame)
    {
        TgVEC_F32_04_1_C                    vMax_Width = tgMH_SET1_F32_04_1( pfShape_Width[uiFrame] );
        TgVEC_F32_04_1_C                    vS0 = tgMH_ADD_F32_04_1( psBeam->m_vPos_N2W, vMax_Width );

        psBeam->m_vBA_Max_W = tgMH_MAX_F32_04_1( psBeam->m_vBA_Max_W, tgMH_ADD_F32_04_1( vS0, vMax_Width ) );
        psBeam->m_vBA_Min_W = tgMH_MIN_F32_04_1( psBeam->m_vBA_Min_W, tgMH_SUB_F32_04_1( vS0, vMax_Width ) );
    };
}


/* ---- tgFX__Scene__Beam_Cull__Insert_Frame_Mesh -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgFX__Scene__Beam_Cull__Insert_Frame_Mesh( STg2_SE_Context_PC UNUSED_PARAM psSE_Context, TgRSIZE_C UNUSED_PARAM uiView_Index, TgFX_DATA_INST_ID UNUSED_PARAM tiActive )
{
    /* Blank on purpose - Not needed */
}


/* == Effect ===================================================================================================================================================================== */

/*# defined(TgBUILD_FEATURE__GRAPHICS_VFX) */
#endif
