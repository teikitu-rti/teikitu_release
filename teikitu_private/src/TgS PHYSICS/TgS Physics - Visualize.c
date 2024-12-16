/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Physics - Visualize.c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.21 | »GUID« AEEC8393-9780-4ECA-918D-E3E11F7E2744 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "TgS Physics - Internal.inl"


/* == Physics ==================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

#if defined(TgBUILD_DEBUG__PHYSICS) && defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)

typedef struct {
    STg2_KN_GPU_HLSL_CB_Debug_Model_Instance    m_sInstance;
    TgRSIZE                                     m_nuiInstance;
} STg2_PH_Visualize_Form;

/*  @param [out] OUT0 Pointer to a vector union storing the colour of the geometry to render.
    @param [in] ARG1 Pointer to the Form under consideration.
    @param [in] ARG2 Pointer to the Body associated with the Form in ARG1.
    @return true if the form should be rendered, or false otherwise. */
static TgBOOL
tgPH_Form_Visualize_Render__Iteration_Loop_Kinematic(
    TgVEC_UN_F32_04_1_PC OUT0, STg2_PH_Form_CPC ARG1, STg2_PH_Body_CPC ARG2 );

/*  @param [out] OUT0 Pointer to a vector union storing the colour of the geometry to render.
    @param [in] ARG1 Pointer to the Form under consideration.
    @param [in] ARG2 Pointer to the Body associated with the Form in ARG1.
    @return true if the form should be rendered, or false otherwise. */
static TgBOOL
tgPH_Form_Visualize_Render__Iteration_Loop_Dynamic(
    TgVEC_UN_F32_04_1_PC OUT0, STg2_PH_Form_CPC ARG1, STg2_PH_Body_CPC ARG2 );

static TgVOID
tgPH_Form_Visualize_Render_Internal(
    UTg2_KN_GPU_CMD_C ARG0, STg2_PH_Visualize_Form ARG1[ETgKN_GPU_DEBUG_PM_3D_COUNT], TgPH_WORLD_ID_C ARG2, TgBOOL (*ARG3)( TgVEC_UN_F32_04_1_PC, STg2_PH_Form_CPC, STg2_PH_Body_CPC ));

#define TgMACRO_MAX_SMOOTH_FRAMES 120
static TgFLOAT64 s_afSmooth__Simulation_Total[TgMACRO_MAX_SMOOTH_FRAMES];
static TgFLOAT64 s_afSmooth__Collision_Total[TgMACRO_MAX_SMOOTH_FRAMES];
static TgFLOAT64 s_afSmooth__Collision_World_Total[TgMACRO_MAX_SMOOTH_FRAMES];
static TgFLOAT64 s_afSmooth__Collision_Contact_Pair_Generation_Total[TgMACRO_MAX_SMOOTH_FRAMES];
static TgFLOAT64 s_afSmooth__Collision_Contact_Callback_Total[TgMACRO_MAX_SMOOTH_FRAMES];
static TgFLOAT64 s_afSmooth__Build_Sets_Total[TgMACRO_MAX_SMOOTH_FRAMES];
static TgFLOAT64 s_afSmooth__Build_Sets_Inner_Total[TgMACRO_MAX_SMOOTH_FRAMES];
static TgFLOAT64 s_afSmooth__Solve_Sets_Total[TgMACRO_MAX_SMOOTH_FRAMES];
static TgFLOAT64 s_afSmooth__Buffer_Execution_Total[TgMACRO_MAX_SMOOTH_FRAMES];
static TgRSIZE s_nuiStat_Call=0;

/*# defined(TgBUILD_DEBUG__PHYSICS) && defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
#endif




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Debug Functions                                                                                                                                                       */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
#if defined(TgBUILD_DEBUG__PHYSICS) && defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)

/* ---- tgPH_Debug_Render_Performance_Stats -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Debug_Render_Performance_Stats( UTg2_KN_GPU_CMD_C uCMD, STg2_KN_GPU_HLSL_Output_DESC_CPC psOutput_DESC, STg2_KN_GPU_Render_Buffer_CPC psRTBuffer,
                                            STg2_KN_GPU_Render_Buffer_CPC psDSBuffer )
{
    STg2_KN_GPU_FONT_TX                 sFont_TX;
    STg2_KN_GPU_OUTPUT_DEBUG_STRING     sOutput_Debug_String_0;
    TgCHAR_U8                           uszBuffer[512];
    TgRSIZE                             uiIndex;
    TgFLOAT64                           afSmooth_Total;

    tgKN_GPU_Query_DOS_Font_ROM_TX( &sFont_TX, ETgKN_GPU_DOS_FONT_ROM_MARCIO );

    tgMM_Set_U08_0x00( &sOutput_Debug_String_0, sizeof( sOutput_Debug_String_0 ) );

    sOutput_Debug_String_0.m_sOutput_DESC = *psOutput_DESC;
    sOutput_Debug_String_0.m_sRTBuffer = *psRTBuffer;
    sOutput_Debug_String_0.m_sDSBuffer = *psDSBuffer;
    sOutput_Debug_String_0.m_enFont = ETgKN_GPU_DOS_FONT_ROM_MARCIO;
    sOutput_Debug_String_0.m_auszText[0] = uszBuffer;
    sOutput_Debug_String_0.m_nuiText = 1;
    sOutput_Debug_String_0.m_vText_Box_V.x = -1.0F + (10.0F / (float)psRTBuffer->m_uiWidth);
    sOutput_Debug_String_0.m_vText_Box_V.y = 1.0F - (10.0F / (float)psRTBuffer->m_uiHeight);
    sOutput_Debug_String_0.m_vText_Box_V.z = sOutput_Debug_String_0.m_vText_Box_V.x + ((4.0F + sFont_TX.m_fFntX * 34 * 2) / (float)psRTBuffer->m_uiWidth);
    sOutput_Debug_String_0.m_vText_Box_V.w = sOutput_Debug_String_0.m_vText_Box_V.y - ((sFont_TX.m_fFntY * 10 * 2) / (float)psRTBuffer->m_uiHeight);
    sOutput_Debug_String_0.m_vText_Colour.r = 0.0F;
    sOutput_Debug_String_0.m_vText_Colour.g = 1.0F;
    sOutput_Debug_String_0.m_vText_Colour.b = 0.0F;
    sOutput_Debug_String_0.m_vText_Colour.a = 1.0F;
    sOutput_Debug_String_0.m_bRight_Aligned = false;
    sOutput_Debug_String_0.m_bDraw_Background = true;
    sOutput_Debug_String_0.m_vBackground_Colour.r = 0.0F;
    sOutput_Debug_String_0.m_vBackground_Colour.g = 0.0F;
    sOutput_Debug_String_0.m_vBackground_Colour.b = 0.0F;
    sOutput_Debug_String_0.m_vBackground_Colour.a = 0.15F;

    s_afSmooth__Simulation_Total[s_nuiStat_Call % TgMACRO_MAX_SMOOTH_FRAMES] = PROFILE_TOTAL_TIME_CACHED( PH_SIMULATE_BATCH_TOTAL );
    s_afSmooth__Collision_Contact_Callback_Total[s_nuiStat_Call % TgMACRO_MAX_SMOOTH_FRAMES] = PROFILE_TOTAL_TIME_CACHED( PH_COLLISION_CONTACT_CALLBACK_TOTAL );
    s_afSmooth__Collision_Contact_Pair_Generation_Total[s_nuiStat_Call % TgMACRO_MAX_SMOOTH_FRAMES] = PROFILE_TOTAL_TIME_CACHED( PH_COLLISION_CONTACT_PAIR_GENEARTION_TOTAL ) - PROFILE_TOTAL_TIME_CACHED( PH_COLLISION_CONTACT_CALLBACK_TOTAL );
    s_afSmooth__Collision_World_Total[s_nuiStat_Call % TgMACRO_MAX_SMOOTH_FRAMES] = PROFILE_TOTAL_TIME_CACHED( PH_COLLISION_WORLD_TOTAL );
    s_afSmooth__Collision_Total[s_nuiStat_Call % TgMACRO_MAX_SMOOTH_FRAMES] = PROFILE_TOTAL_TIME_CACHED( PH_COLLISION_CONTACT_PAIR_GENEARTION_TOTAL ) + PROFILE_TOTAL_TIME_CACHED( PH_COLLISION_WORLD_TOTAL );
    s_afSmooth__Build_Sets_Total[s_nuiStat_Call % TgMACRO_MAX_SMOOTH_FRAMES] = PROFILE_TOTAL_TIME_CACHED( PH_BUILD_SETS_TOTAL );
    s_afSmooth__Build_Sets_Inner_Total[s_nuiStat_Call % TgMACRO_MAX_SMOOTH_FRAMES] = PROFILE_TOTAL_TIME_CACHED( PH_BUILD_SETS_INNER_TOTAL );
    s_afSmooth__Solve_Sets_Total[s_nuiStat_Call % TgMACRO_MAX_SMOOTH_FRAMES] = PROFILE_TOTAL_TIME_CACHED( PH_SOLVE_SETS_TOTAL );
    s_afSmooth__Buffer_Execution_Total[s_nuiStat_Call % TgMACRO_MAX_SMOOTH_FRAMES] = PROFILE_TOTAL_TIME_CACHED( PH_CMD_BUFFER_EXECEUTE_TOTAL );
    ++s_nuiStat_Call;

    uszBuffer[0] = 0;
    for (afSmooth_Total = 0.0, uiIndex = 0; uiIndex < TgMACRO_MAX_SMOOTH_FRAMES; ++uiIndex) { afSmooth_Total += s_afSmooth__Simulation_Total[uiIndex] / (TgFLOAT64)TgMACRO_MAX_SMOOTH_FRAMES; }                         tgUSZ_AppendF( uszBuffer, 256, u8"Simulation:               %8.2f\n", afSmooth_Total );
    for (afSmooth_Total = 0.0, uiIndex = 0; uiIndex < TgMACRO_MAX_SMOOTH_FRAMES; ++uiIndex) { afSmooth_Total += s_afSmooth__Collision_Total[uiIndex] / (TgFLOAT64)TgMACRO_MAX_SMOOTH_FRAMES; }                          tgUSZ_AppendF( uszBuffer, 256, u8"Collision:                %8.2f\n", afSmooth_Total );
    for (afSmooth_Total = 0.0, uiIndex = 0; uiIndex < TgMACRO_MAX_SMOOTH_FRAMES; ++uiIndex) { afSmooth_Total += s_afSmooth__Collision_World_Total[uiIndex] / (TgFLOAT64)TgMACRO_MAX_SMOOTH_FRAMES; }                    tgUSZ_AppendF( uszBuffer, 256, u8"+-World:                  %8.2f\n", afSmooth_Total );
    for (afSmooth_Total = 0.0, uiIndex = 0; uiIndex < TgMACRO_MAX_SMOOTH_FRAMES; ++uiIndex) { afSmooth_Total += s_afSmooth__Collision_Contact_Pair_Generation_Total[uiIndex] / (TgFLOAT64)TgMACRO_MAX_SMOOTH_FRAMES; }  tgUSZ_AppendF( uszBuffer, 256, u8"  +-Contact Pair:         %8.2f\n", afSmooth_Total );
    tgKN_GPU__CMD__Render_Debug_Text_Box( uCMD, &sOutput_Debug_String_0 );

    sOutput_Debug_String_0.m_bDraw_Background = false;
    uszBuffer[0] = 0; tgUSZ_AppendF( uszBuffer, 256, u8"\n\n\n\n" );
    for (afSmooth_Total = 0.0, uiIndex = 0; uiIndex < TgMACRO_MAX_SMOOTH_FRAMES; ++uiIndex) { afSmooth_Total += s_afSmooth__Collision_Contact_Callback_Total[uiIndex] / (TgFLOAT64)TgMACRO_MAX_SMOOTH_FRAMES; }         tgUSZ_AppendF( uszBuffer, 256, u8"    +-Contact Callback:   %8.2f\n", afSmooth_Total );
#if defined(TgS_STAT__PHYSICS) && TgS_STAT__PHYSICS
    for (afSmooth_Total = 0.0, uiIndex = 0; uiIndex < TgMACRO_MAX_SMOOTH_FRAMES; ++uiIndex) { afSmooth_Total += s_afSmooth__Collision_Contact_Callback_Total[uiIndex] / (TgFLOAT64)TgMACRO_MAX_SMOOTH_FRAMES; }         tgUSZ_AppendF( uszBuffer, 256, u8"     -Count: %d\n", TgSTD_ATOMIC(load_explicit)( &g_xnuiFM_Callback, TgSTD_MEMORY_ORDER(relaxed) ) );
/*# defined(TgS_STAT__PHYSICS) && TgS_STAT__PHYSICS */
#endif
    tgKN_GPU__CMD__Render_Debug_Text_Box( uCMD, &sOutput_Debug_String_0 );

    sOutput_Debug_String_0.m_bDraw_Background = false;
    uszBuffer[0] = 0; tgUSZ_AppendF( uszBuffer, 256, u8"\n\n\n\n\n\n" );
    for (afSmooth_Total = 0.0, uiIndex = 0; uiIndex < TgMACRO_MAX_SMOOTH_FRAMES; ++uiIndex) { afSmooth_Total += s_afSmooth__Build_Sets_Total[uiIndex] / (TgFLOAT64)TgMACRO_MAX_SMOOTH_FRAMES; }                         tgUSZ_AppendF( uszBuffer, 256, u8"Build Sets:               %8.2f\n", afSmooth_Total );
    for (afSmooth_Total = 0.0, uiIndex = 0; uiIndex < TgMACRO_MAX_SMOOTH_FRAMES; ++uiIndex) { afSmooth_Total += s_afSmooth__Build_Sets_Inner_Total[uiIndex] / (TgFLOAT64)TgMACRO_MAX_SMOOTH_FRAMES; }                   tgUSZ_AppendF( uszBuffer, 256, u8"+-Build:                  %8.2f\n", afSmooth_Total );
    for (afSmooth_Total = 0.0, uiIndex = 0; uiIndex < TgMACRO_MAX_SMOOTH_FRAMES; ++uiIndex) { afSmooth_Total += s_afSmooth__Solve_Sets_Total[uiIndex] / (TgFLOAT64)TgMACRO_MAX_SMOOTH_FRAMES; }                         tgUSZ_AppendF( uszBuffer, 256, u8"Solve Sets:               %8.2f\n", afSmooth_Total );
    for (afSmooth_Total = 0.0, uiIndex = 0; uiIndex < TgMACRO_MAX_SMOOTH_FRAMES; ++uiIndex) { afSmooth_Total += s_afSmooth__Buffer_Execution_Total[uiIndex] / (TgFLOAT64)TgMACRO_MAX_SMOOTH_FRAMES; }                   tgUSZ_AppendF( uszBuffer, 256, u8"CMD Execution:            %8.2f\n", afSmooth_Total );

    tgKN_GPU__CMD__Render_Debug_Text_Box( uCMD, &sOutput_Debug_String_0 );
}


//KTgMACRO_KN_GPU_HLSL_DEBUG_MAX_MODEL_INSTANCE
/* ---- tgPH_Form_Visualize_Render ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Form_Visualize_Render( UTg2_KN_GPU_CMD_C uCMD, STg2_KN_GPU_HLSL_CB_Debug_Model_PC psModelConstantBuffer, TgPH_WORLD_ID_C tiWorld, ETgKN_GPU_EXT_FORMAT_C enRT,
                                   ETgKN_GPU_EXT_FORMAT_C enDS )
{
    TgRSIZE                             uiIndex;
    STg2_PH_Visualize_Form              asData[ETgKN_GPU_DEBUG_PM_3D_COUNT];
    TgVEC_UN_F32_04_1                   uColour;
    TgSINT_E32                          iSelect = -1;
    TgRSIZE                             uiFence;

    /* Initialize all of the instance constant buffer data from the input constant buffer. */
    for (uiIndex = 0; uiIndex < TgARRAY_COUNT(asData); ++uiIndex)
    {
        asData[uiIndex].m_nuiInstance = 0;
        tgMM_Copy( &asData[uiIndex].m_sInstance, sizeof(STg2_KN_GPU_HLSL_CB_Debug_Model_Instance), psModelConstantBuffer, sizeof(STg2_KN_GPU_HLSL_CB_Debug_Model) );
    };

    /* Make sure that the physics update loop has finished. */
    uiFence = 0;
    while (!TgSTD_ATOMIC(compare_exchange_strong_explicit)( g_axuiPH_FENCE__UPDATE_WORLD + tiWorld.m_uiI, &uiFence, 1, TgSTD_MEMORY_ORDER(acq_rel), TgSTD_MEMORY_ORDER(acquire) ))
    {
        tgTR_Pause();
        uiFence = 0;
    };

    tgKN_GPU_EXT__CMD__Set_State_From_Default( uCMD, ETgKN_GPU_DEFAULT_PSO_DEBUG_GEOM_02_INSTANCE, enRT, enDS );

    /* Render the Kinematic and then the Dynamic geometry. As the render ignores depth, this will force Kinematic to be drawn first which tends to be the right draw order. */
    tgPH_Form_Visualize_Render_Internal( uCMD, asData, tiWorld, tgPH_Form_Visualize_Render__Iteration_Loop_Kinematic );
    tgPH_Form_Visualize_Render_Internal( uCMD, asData, tiWorld, tgPH_Form_Visualize_Render__Iteration_Loop_Dynamic );

    #pragma region Draw a sphere at every contact point
    iSelect = (TgSINT_E32)ETgKN_GPU_DEBUG_PM_3D_SPHERE - (TgSINT_E32)ETgKN_GPU_DEBUG_PM_3D_START;
    uColour.m_vF32_04_1 = g_vPH_Debug_Colour__Contact;
    for (uiIndex = 0; uiIndex < g_nuiPH_Debug__Contact; ++uiIndex)
    {
        tgMH_Init_T_S_F32_04_4( asData[iSelect].m_sInstance.m_avModel_Transform + asData[iSelect].m_nuiInstance, g_auPH_Debug__Contact[uiIndex].m_vS_F32_04_1 );
        asData[iSelect].m_sInstance.m_avModel_Transform[asData[iSelect].m_nuiInstance]._11 = 0.125F;
        asData[iSelect].m_sInstance.m_avModel_Transform[asData[iSelect].m_nuiInstance]._22 = 0.125F;
        asData[iSelect].m_sInstance.m_avModel_Transform[asData[iSelect].m_nuiInstance]._33 = 0.125F;
        asData[iSelect].m_sInstance.m_avModel_Colour[asData[iSelect].m_nuiInstance] = uColour.m_vS_F32_04_1;

        ++asData[iSelect].m_nuiInstance;
        if (asData[iSelect].m_nuiInstance >= TgARRAY_COUNT(asData[iSelect].m_sInstance.m_avModel_Transform))
        {
            tgKN_GPU_EXT__CMD__Render_Debug_Geom_Instance( uCMD, (ETgKN_GPU_DEBUG_PM)((TgSINT_E32)ETgKN_GPU_DEBUG_PM_3D_START + iSelect), asData[iSelect].m_nuiInstance,
                                                           &asData[iSelect].m_sInstance );
            asData[iSelect].m_nuiInstance = 0;
        };
    };
    if (asData[iSelect].m_nuiInstance > 0)
    {
        tgKN_GPU_EXT__CMD__Render_Debug_Geom_Instance( uCMD, (ETgKN_GPU_DEBUG_PM)((TgSINT_E32)ETgKN_GPU_DEBUG_PM_3D_START + iSelect), asData[iSelect].m_nuiInstance,
                                                       &asData[iSelect].m_sInstance );
        asData[iSelect].m_nuiInstance = 0;
    };
    #pragma endregion

    /* Release the lock on the physics update (prevents physics from updating while we are doing the visualization draw. */
    TgSTD_ATOMIC(fetch_sub_explicit)( g_axuiPH_FENCE__UPDATE_WORLD + tiWorld.m_uiI, 1, TgSTD_MEMORY_ORDER(seq_cst) );
}

/*# defined(TgBUILD_DEBUG__PHYSICS) && defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
#endif




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

#if defined(TgBUILD_DEBUG__PHYSICS) && defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)
static TgBOOL tgPH_Form_Visualize_Render__Iteration_Loop_Kinematic( TgVEC_UN_F32_04_1_PC puColour, STg2_PH_Form_CPC psFM, STg2_PH_Body_CPC psBY )
{
    if (nullptr != psBY /* && psFM->m_uiCategory */)
    {
        return false;
    }

    if (psFM->m_uiCollide == 0)
    {
        puColour->m_vF32_04_1 = g_vPH_Debug_Colour__Form_Disabled;
    }
    else
    {
        puColour->m_vF32_04_1 = psFM->m_vDebug_Colour;
    }

    return true;
}
/*# defined(TgBUILD_DEBUG__PHYSICS) && defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
#endif


#if defined(TgBUILD_DEBUG__PHYSICS) && defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)
static TgBOOL tgPH_Form_Visualize_Render__Iteration_Loop_Dynamic( TgVEC_UN_F32_04_1_PC puColour, STg2_PH_Form_CPC psFM, STg2_PH_Body_CPC psBY )
{
    if (nullptr == psBY /* || psFM->m_uiCategory */)
    {
        return false;
    }

    if (psFM->m_uiCollide == 0)
    {
        puColour->m_vF32_04_1 = g_vPH_Debug_Colour__Form_Disabled;
    }
    else if (!psBY->m_bUpdate)
    {
        puColour->m_vF32_04_1 = g_vPH_Debug_Colour__Body_Sleep;
    }
    else
    {
        puColour->m_vF32_04_1 = g_vPH_Debug_Colour__Body_Enabled;
    };

    return true;
}
/*# defined(TgBUILD_DEBUG__PHYSICS) && defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
#endif


#if defined(TgBUILD_DEBUG__PHYSICS) && defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)
static TgVOID tgPH_Form_Visualize_Render_Internal( UTg2_KN_GPU_CMD_C uCMD, STg2_PH_Visualize_Form asData[ETgKN_GPU_DEBUG_PM_3D_COUNT], TgPH_WORLD_ID_C tiWorld,
                                                   TgBOOL (*ARG0)( TgVEC_UN_F32_04_1_PC, STg2_PH_Form_CPC, STg2_PH_Body_CPC ))
{
    TgRSIZE_C                           nuiForm_World = TgSTD_ATOMIC(load_explicit)( g_axnuiPH_Form_Total__Used + tiWorld.m_uiI, TgSTD_MEMORY_ORDER(relaxed) );
    TgRSIZE                             uiIndex;
    TgVEC_UN_F32_04_1                   uColour;
    TgSINT_E32                          iSelect = -1;

    #pragma region Draw all world collision first (based on Category and no Body)
    for (uiIndex = 0; uiIndex < nuiForm_World; ++uiIndex)
    {
        STg2_PH_Form_CPC                    psFM = g_aapsPH_Form_Used[tiWorld.m_uiI][uiIndex];
        STg2_PH_Body_CPC                    psBY = KTgID__INVALID_VALUE == psFM->m_tiBY.m_uiKI ? nullptr : g_aasPH_Body[tiWorld.m_uiI] + psFM->m_tiBY.m_uiI;
        TgVEC_UN_CONST_PTR_F32_04_3         uM0 = { .m_pmF32_04_3 = &psFM->m_mFinal_O2W };

        TgDIAG(uM0.m_pmS_F32_04_3);

        if (!ARG0( &uColour, psFM, psBY ))
        {
            continue;
        }

        TgWARN_DISABLE_PUSH(4061 4062,switch-enum)
        iSelect = -1;
        switch (psFM->m_enPM) {
        case ETgPM_PN:

            iSelect = (TgSINT_E32)ETgKN_GPU_DEBUG_PM_3D_PLANE - (TgSINT_E32)ETgKN_GPU_DEBUG_PM_3D_START;

            tgMM_Copy( asData[iSelect].m_sInstance.m_avModel_Transform + asData[iSelect].m_nuiInstance, sizeof(TgVEC_S_F32_04_4), uM0.m_pmS_F32_04_3, sizeof(TgVEC_UN_F32_04_3) );
            asData[iSelect].m_sInstance.m_avModel_Transform[asData[iSelect].m_nuiInstance].m_vC3 = KTgUNIT_W_S_F32_04_1;
            asData[iSelect].m_sInstance.m_avModel_Colour[asData[iSelect].m_nuiInstance] = uColour.m_vS_F32_04_1;

            ++asData[iSelect].m_nuiInstance;
            break;

        case ETgPM_BX: {
            TgVEC_UN_F32_04_1_C                 uScale = { .m_vF32_04_1 = tgMH_Init_Point_F32_04_1( psFM->m_uPM.m_sBX.m_vExtent ) };
            TgVEC_UN_F32_04_3                   uM3;

            iSelect = (TgSINT_E32)ETgKN_GPU_DEBUG_PM_3D_BOX - (TgSINT_E32)ETgKN_GPU_DEBUG_PM_3D_START;

            tgMH_CAT_F32_04_3( &uM3.m_mF32_04_3, &psFM->m_uPM.m_sBX.m_mReference_Frame, uM0.m_pmF32_04_3 );

            asData[iSelect].m_sInstance.m_avModel_Transform[asData[iSelect].m_nuiInstance].m_vC0 = tgMH_MUL_S_F32_04_1( uScale.m_vS_F32_04_1, uM3.m_mS_F32_04_3.m_vC0 );
            asData[iSelect].m_sInstance.m_avModel_Transform[asData[iSelect].m_nuiInstance].m_vC1 = tgMH_MUL_S_F32_04_1( uScale.m_vS_F32_04_1, uM3.m_mS_F32_04_3.m_vC1 );
            asData[iSelect].m_sInstance.m_avModel_Transform[asData[iSelect].m_nuiInstance].m_vC2 = tgMH_MUL_S_F32_04_1( uScale.m_vS_F32_04_1, uM3.m_mS_F32_04_3.m_vC2 );
            asData[iSelect].m_sInstance.m_avModel_Transform[asData[iSelect].m_nuiInstance].m_vC3 = KTgUNIT_W_S_F32_04_1;
            asData[iSelect].m_sInstance.m_avModel_Colour[asData[iSelect].m_nuiInstance] = uColour.m_vS_F32_04_1;

            ++asData[iSelect].m_nuiInstance;
        } break;

        case ETgPM_SP: {
            TgVEC_UN_F32_04_1_C                 uScale = { .m_vF32_04_1 = tgMH_Init_Point_F32_04_1( psFM->m_uPM.m_sSP.m_vRadius ) };

            iSelect = (TgSINT_E32)ETgKN_GPU_DEBUG_PM_3D_SPHERE - (TgSINT_E32)ETgKN_GPU_DEBUG_PM_3D_START;

            asData[iSelect].m_sInstance.m_avModel_Transform[asData[iSelect].m_nuiInstance].m_vC0 = tgMH_MUL_S_F32_04_1( uScale.m_vS_F32_04_1, uM0.m_pmS_F32_04_3->m_vC0 );
            asData[iSelect].m_sInstance.m_avModel_Transform[asData[iSelect].m_nuiInstance].m_vC1 = tgMH_MUL_S_F32_04_1( uScale.m_vS_F32_04_1, uM0.m_pmS_F32_04_3->m_vC1 );
            asData[iSelect].m_sInstance.m_avModel_Transform[asData[iSelect].m_nuiInstance].m_vC2 = tgMH_MUL_S_F32_04_1( uScale.m_vS_F32_04_1, uM0.m_pmS_F32_04_3->m_vC2 );
            asData[iSelect].m_sInstance.m_avModel_Transform[asData[iSelect].m_nuiInstance].m_vC3 = KTgUNIT_W_S_F32_04_1;
            asData[iSelect].m_sInstance.m_avModel_Colour[asData[iSelect].m_nuiInstance] = uColour.m_vS_F32_04_1;

            ++asData[iSelect].m_nuiInstance;
        } break;

        case ETgPM_CP: {
            TgVEC_F32_04_1                      vScale;
            TgVEC_UN_F32_04_1                   uScale;
            TgVEC_UN_F32_04_3                   uM3;
            TgVEC_UN_F32_04_3                   uM4,uM5;

            tgMH_CAT_F32_04_3( &uM3.m_mF32_04_3, &psFM->m_uPM.m_sTB.m_mReference_Frame, uM0.m_pmF32_04_3 );

            vScale = tgMH_SEL_F32_04_1( psFM->m_uPM.m_sTB.m_vRadius, psFM->m_uPM.m_sTB.m_vExtent, KTg0F00_V128.m_vF32_04_1 );
            uScale.m_vF32_04_1 = tgMH_Init_Point_F32_04_1( vScale );
            iSelect = (TgSINT_E32)ETgKN_GPU_DEBUG_PM_3D_CAPSULE_TUBE - (TgSINT_E32)ETgKN_GPU_DEBUG_PM_3D_START;
            asData[iSelect].m_sInstance.m_avModel_Transform[asData[iSelect].m_nuiInstance].m_vC0 = tgMH_MUL_S_F32_04_1( uScale.m_vS_F32_04_1, uM3.m_mS_F32_04_3.m_vC0 );
            asData[iSelect].m_sInstance.m_avModel_Transform[asData[iSelect].m_nuiInstance].m_vC1 = tgMH_MUL_S_F32_04_1( uScale.m_vS_F32_04_1, uM3.m_mS_F32_04_3.m_vC1 );
            asData[iSelect].m_sInstance.m_avModel_Transform[asData[iSelect].m_nuiInstance].m_vC2 = tgMH_MUL_S_F32_04_1( uScale.m_vS_F32_04_1, uM3.m_mS_F32_04_3.m_vC2 );
            asData[iSelect].m_sInstance.m_avModel_Transform[asData[iSelect].m_nuiInstance].m_vC3 = KTgUNIT_W_S_F32_04_1;
            asData[iSelect].m_sInstance.m_avModel_Colour[asData[iSelect].m_nuiInstance] = uColour.m_vS_F32_04_1;

            ++asData[iSelect].m_nuiInstance;

            tgMH_Init_T_F32_04_3( &uM4.m_mF32_04_3, tgMH_MUL_F32_04_1( psFM->m_uPM.m_sTB.m_vExtent, KTgUNIT_Y_F32_04_1 ) );
            tgMH_CAT_F32_04_3( &uM5.m_mF32_04_3, &uM4.m_mF32_04_3, &uM3.m_mF32_04_3 );

            vScale = tgMH_SEL_F32_04_1( psFM->m_uPM.m_sTB.m_vRadius, KTgONE_F32_04_1, KTg0F00_V128.m_vF32_04_1 );
            uScale.m_vF32_04_1 = tgMH_Init_Point_F32_04_1( vScale );
            iSelect = (TgSINT_E32)ETgKN_GPU_DEBUG_PM_3D_CAPSULE_CAP_0 - (TgSINT_E32)ETgKN_GPU_DEBUG_PM_3D_START;
            asData[iSelect].m_sInstance.m_avModel_Transform[asData[iSelect].m_nuiInstance].m_vC0 = tgMH_MUL_S_F32_04_1( uScale.m_vS_F32_04_1, uM5.m_mS_F32_04_3.m_vC0 );
            asData[iSelect].m_sInstance.m_avModel_Transform[asData[iSelect].m_nuiInstance].m_vC1 = tgMH_MUL_S_F32_04_1( uScale.m_vS_F32_04_1, uM5.m_mS_F32_04_3.m_vC1 );
            asData[iSelect].m_sInstance.m_avModel_Transform[asData[iSelect].m_nuiInstance].m_vC2 = tgMH_MUL_S_F32_04_1( uScale.m_vS_F32_04_1, uM5.m_mS_F32_04_3.m_vC2 );
            asData[iSelect].m_sInstance.m_avModel_Transform[asData[iSelect].m_nuiInstance].m_vC3 = KTgUNIT_W_S_F32_04_1;
            asData[iSelect].m_sInstance.m_avModel_Colour[asData[iSelect].m_nuiInstance] = uColour.m_vS_F32_04_1;

            ++asData[iSelect].m_nuiInstance;

            tgMH_Init_T_F32_04_3( &uM4.m_mF32_04_3, tgMH_NEG_F32_04_1( tgMH_MUL_F32_04_1( psFM->m_uPM.m_sTB.m_vExtent, KTgUNIT_Y_F32_04_1 ) ) );
            tgMH_CAT_F32_04_3( &uM5.m_mF32_04_3, &uM4.m_mF32_04_3, &uM3.m_mF32_04_3 );

            vScale = tgMH_SEL_F32_04_1( psFM->m_uPM.m_sTB.m_vRadius, KTgONE_F32_04_1, KTg0F00_V128.m_vF32_04_1 );
            uScale.m_vF32_04_1 = tgMH_Init_Point_F32_04_1( vScale );
            iSelect = (TgSINT_E32)ETgKN_GPU_DEBUG_PM_3D_CAPSULE_CAP_1 - (TgSINT_E32)ETgKN_GPU_DEBUG_PM_3D_START;
            asData[iSelect].m_sInstance.m_avModel_Transform[asData[iSelect].m_nuiInstance].m_vC0 = tgMH_MUL_S_F32_04_1( uScale.m_vS_F32_04_1, uM5.m_mS_F32_04_3.m_vC0 );
            asData[iSelect].m_sInstance.m_avModel_Transform[asData[iSelect].m_nuiInstance].m_vC1 = tgMH_MUL_S_F32_04_1( uScale.m_vS_F32_04_1, uM5.m_mS_F32_04_3.m_vC1 );
            asData[iSelect].m_sInstance.m_avModel_Transform[asData[iSelect].m_nuiInstance].m_vC2 = tgMH_MUL_S_F32_04_1( uScale.m_vS_F32_04_1, uM5.m_mS_F32_04_3.m_vC2 );
            asData[iSelect].m_sInstance.m_avModel_Transform[asData[iSelect].m_nuiInstance].m_vC3 = KTgUNIT_W_S_F32_04_1;
            asData[iSelect].m_sInstance.m_avModel_Colour[asData[iSelect].m_nuiInstance] = uColour.m_vS_F32_04_1;

            ++asData[iSelect].m_nuiInstance;
        } break;

        case ETgPM_CY: {
            TgVEC_F32_04_1_C                    vScale = tgMH_SEL_F32_04_1( psFM->m_uPM.m_sTB.m_vRadius, psFM->m_uPM.m_sTB.m_vExtent, KTg0F00_V128.m_vF32_04_1 );
            TgVEC_UN_F32_04_1_C                 uScale = { .m_vF32_04_1 = tgMH_Init_Point_F32_04_1( vScale ) };
            TgVEC_UN_F32_04_3                   uM3;

            iSelect = (TgSINT_E32)ETgKN_GPU_DEBUG_PM_3D_CYLINDER - (TgSINT_E32)ETgKN_GPU_DEBUG_PM_3D_START;

            tgMH_CAT_F32_04_3( &uM3.m_mF32_04_3, &psFM->m_uPM.m_sTB.m_mReference_Frame, uM0.m_pmF32_04_3 );

            asData[iSelect].m_sInstance.m_avModel_Transform[asData[iSelect].m_nuiInstance].m_vC0 = tgMH_MUL_S_F32_04_1( uScale.m_vS_F32_04_1, uM3.m_mS_F32_04_3.m_vC0 );
            asData[iSelect].m_sInstance.m_avModel_Transform[asData[iSelect].m_nuiInstance].m_vC1 = tgMH_MUL_S_F32_04_1( uScale.m_vS_F32_04_1, uM3.m_mS_F32_04_3.m_vC1 );
            asData[iSelect].m_sInstance.m_avModel_Transform[asData[iSelect].m_nuiInstance].m_vC2 = tgMH_MUL_S_F32_04_1( uScale.m_vS_F32_04_1, uM3.m_mS_F32_04_3.m_vC2 );
            asData[iSelect].m_sInstance.m_avModel_Transform[asData[iSelect].m_nuiInstance].m_vC3 = KTgUNIT_W_S_F32_04_1;
            asData[iSelect].m_sInstance.m_avModel_Colour[asData[iSelect].m_nuiInstance] = uColour.m_vS_F32_04_1;

            ++asData[iSelect].m_nuiInstance;
        } break;

        case ETgPM_BA: {
            TgVEC_UN_F32_04_1                   uScale;

            iSelect = (TgSINT_E32)ETgKN_GPU_DEBUG_PM_3D_BOX - (TgSINT_E32)ETgKN_GPU_DEBUG_PM_3D_START;

            uScale.m_vF32_04_1 = tgMH_SUB_F32_04_1( tgGM_BA_Query_Max_F32_04( &psFM->m_uPM.m_sBA ), tgGM_BA_Query_Min_F32_04( &psFM->m_uPM.m_sBA ) );

            asData[iSelect].m_sInstance.m_avModel_Transform[asData[iSelect].m_nuiInstance].m_vC0 = tgMH_MUL_S_F32_04_1( uScale.m_vS_F32_04_1, uM0.m_pmS_F32_04_3->m_vC0 );
            asData[iSelect].m_sInstance.m_avModel_Transform[asData[iSelect].m_nuiInstance].m_vC1 = tgMH_MUL_S_F32_04_1( uScale.m_vS_F32_04_1, uM0.m_pmS_F32_04_3->m_vC1 );
            asData[iSelect].m_sInstance.m_avModel_Transform[asData[iSelect].m_nuiInstance].m_vC2 = tgMH_MUL_S_F32_04_1( uScale.m_vS_F32_04_1, uM0.m_pmS_F32_04_3->m_vC2 );
            asData[iSelect].m_sInstance.m_avModel_Transform[asData[iSelect].m_nuiInstance].m_vC3 = KTgUNIT_W_S_F32_04_1;
            asData[iSelect].m_sInstance.m_avModel_Colour[asData[iSelect].m_nuiInstance] = uColour.m_vS_F32_04_1;

            ++asData[iSelect].m_nuiInstance;
        } break;
        default:
            break;
        }
        TgWARN_DISABLE_POP()

        if (iSelect >= 0 && asData[iSelect].m_nuiInstance >= TgARRAY_COUNT(asData[iSelect].m_sInstance.m_avModel_Transform))
        {
            tgKN_GPU_EXT__CMD__Render_Debug_Geom_Instance( uCMD, (ETgKN_GPU_DEBUG_PM)((TgSINT_E32)ETgKN_GPU_DEBUG_PM_3D_START + iSelect), asData[iSelect].m_nuiInstance,
                                                           &asData[iSelect].m_sInstance );
            asData[iSelect].m_nuiInstance = 0;
        };

        #pragma region Draw sphere at each of the vertices of an axis aligned bounding box
        iSelect = (TgSINT_E32)ETgKN_GPU_DEBUG_PM_3D_SPHERE - (TgSINT_E32)ETgKN_GPU_DEBUG_PM_3D_START;
        if (asData[iSelect].m_nuiInstance + 10 >= TgARRAY_COUNT(asData[iSelect].m_sInstance.m_avModel_Transform))
        {
            tgKN_GPU_EXT__CMD__Render_Debug_Geom_Instance( uCMD, (ETgKN_GPU_DEBUG_PM)((TgSINT_E32)ETgKN_GPU_DEBUG_PM_3D_START + iSelect), asData[iSelect].m_nuiInstance,
                                                           &asData[iSelect].m_sInstance );
            asData[iSelect].m_nuiInstance = 0;
        };

        uColour.m_vF32_04_1 = tgMH_Init_ELEM_F32_04_1( 1.0F, 1.0F, 0.0F, 1.0F );
        for (TgRSIZE uiVert = 0; uiVert < 8; ++uiVert)
        {
            TgVEC_UN_F32_04_1                   uVert;

            uVert.m_vF32_04_1 = tgGM_BA_Calc_Point_Index_F32_04( &psFM->m_sBA_W, uiVert );
            tgMH_Init_T_S_F32_04_4( asData[iSelect].m_sInstance.m_avModel_Transform + asData[iSelect].m_nuiInstance, uVert.m_vS_F32_04_1 );
            asData[iSelect].m_sInstance.m_avModel_Transform[asData[iSelect].m_nuiInstance]._11 *= 0.05F;
            asData[iSelect].m_sInstance.m_avModel_Transform[asData[iSelect].m_nuiInstance]._22 *= 0.05F;
            asData[iSelect].m_sInstance.m_avModel_Transform[asData[iSelect].m_nuiInstance]._33 *= 0.05F;
            asData[iSelect].m_sInstance.m_avModel_Colour[asData[iSelect].m_nuiInstance] = uColour.m_vS_F32_04_1;

            ++asData[iSelect].m_nuiInstance;
        };

        if (psBY)
        {
            TgVEC_UN_F32_04_1                   uVert;

            uColour.m_vF32_04_1 = tgMH_Init_ELEM_F32_04_1( 10.0F, 10.0F, 10.0F, 1.0F );
            uVert.m_vF32_04_1 = psBY->m_vPos_O2W;
            tgMH_Init_T_S_F32_04_4( asData[iSelect].m_sInstance.m_avModel_Transform + asData[iSelect].m_nuiInstance, uVert.m_vS_F32_04_1 );
            asData[iSelect].m_sInstance.m_avModel_Transform[asData[iSelect].m_nuiInstance]._11 *= 0.05F;
            asData[iSelect].m_sInstance.m_avModel_Transform[asData[iSelect].m_nuiInstance]._22 *= 0.05F;
            asData[iSelect].m_sInstance.m_avModel_Transform[asData[iSelect].m_nuiInstance]._33 *= 0.05F;
            asData[iSelect].m_sInstance.m_avModel_Colour[asData[iSelect].m_nuiInstance] = uColour.m_vS_F32_04_1;

            ++asData[iSelect].m_nuiInstance;
        }
        #pragma endregion
    }

    #pragma region Flush the queue of all the remaining instances.
    for (uiIndex = 0; uiIndex < ETgKN_GPU_DEBUG_PM_3D_COUNT; ++uiIndex)
    {
        if (asData[uiIndex].m_nuiInstance <= 0)
        {
            continue;
        };
        tgKN_GPU_EXT__CMD__Render_Debug_Geom_Instance( uCMD, (ETgKN_GPU_DEBUG_PM)((TgSINT_E32)ETgKN_GPU_DEBUG_PM_3D_START + uiIndex), asData[uiIndex].m_nuiInstance,
                                                       &asData[uiIndex].m_sInstance );
        asData[uiIndex].m_nuiInstance = 0;
    };
    #pragma endregion
}
/*# defined(TgBUILD_DEBUG__PHYSICS) && defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
#endif
