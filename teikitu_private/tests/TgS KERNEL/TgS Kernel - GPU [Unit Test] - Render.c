/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Kernel - GPU [Unit Test] - Render.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
#if defined(TgBUILD_FEATURE__GRAPHICS)

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  External Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/** @brief Clear the screen using the clear screen API. Colour correction will need to be done on the CPU. */
TgEXTN TgRESULT
tgUnit_Test__KN_GPU__Render_0(
    TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC, TgKN_GPU_CXT_WORK_ID_C tiCXT_WORK, TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP, TgKN_GPU_RENDER_TARGET_ID_C tiRender_Target);

/** @brief Clear the screen using a fullscreen quad, matching the previous clear colours. This will invoke the pixel shader for colour correction instead of CPU correction. */
TgEXTN TgRESULT
tgUnit_Test__KN_GPU__Render_1(
    TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC, TgKN_GPU_CXT_WORK_ID_C tiCXT_WORK, TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP, TgKN_GPU_RENDER_TARGET_ID_C tiRender_Target);

/** @brief Clear the screen using a fullscreen quad. This will use the colour reference image. */
TgEXTN TgRESULT
tgUnit_Test__KN_GPU__Render_2(
    TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC, TgKN_GPU_CXT_WORK_ID_C tiCXT_WORK, TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP, TgKN_GPU_RENDER_TARGET_ID_C tiRender_Target);

/** @brief Render using the shared render function (quad clear with reference image, gradients, 3D debug geometry). */
TgEXTN TgRESULT
tgUnit_Test__KN_GPU__Render_3(
    TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC, TgKN_GPU_CXT_WORK_ID_C tiCXT_WORK, TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP, TgKN_GPU_RENDER_TARGET_ID_C tiRender_Target);

/** @brief Render using the shared render function and line drawing. */
TgEXTN TgRESULT
tgUnit_Test__KN_GPU__Render_4(
    TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC, TgKN_GPU_CXT_WORK_ID_C tiCXT_WORK, TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP, TgKN_GPU_RENDER_TARGET_ID_C tiRender_Target);

/** @brief Render using the shared render function and . */
TgEXTN TgRESULT
 tgUnit_Test__KN_GPU__Render_5(
     TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC, TgKN_GPU_CXT_WORK_ID_C tiCXT_WORK, TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP, TgKN_GPU_RENDER_TARGET_ID_C tiRender_Target);




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Local File Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

static TgRESULT
tgUnit_Test__KN_GPU__Render_Shared(
    STg2_KN_GPU_Camera_Shared_PC OUT0, STg2_KN_GPU_CMD_PP OUT1, TgKN_GPU_CXT_EXEC_ID_C ARG2, TgKN_GPU_CXT_WORK_ID ARG3, TgKN_GPU_CXT_SWAP_ID_C ARG4, TgKN_GPU_RENDER_TARGET_ID_C ARG5);

#if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)

static TgVOID
tgUnit_Test__Generate_Perceptual_Grid_Colors(
    TgVEC_F32_04_1_P OUT0, TgBOOL_C ARG1 );

/*# defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
#endif

enum { g_nuiPoints_Per_Edge = 11 };




/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgUnit_Test__KN_GPU__Render_0 -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgUnit_Test__KN_GPU__Render_0(
    TgATTRIBUTE_UNUSED TgKN_GPU_CXT_EXEC_ID_C   tiCXT_EXEC,
    TgKN_GPU_CXT_WORK_ID_C                      tiCXT_WORK,
    TgKN_GPU_CXT_SWAP_ID_C                      tiCXT_SWAP,
    TgKN_GPU_RENDER_TARGET_ID_C                 tiRender_Target )
{
    STg2_KN_GPU_CMD_P                           psCMD;
    STg2_KN_GPU_Output_DESC                     sOutput_DESC;
    STg2_KN_GPU_Clear_Target                    sClear_Target;
    TgUINT_E64                                  uiTimeline_Value;

    (void)tiRender_Target;
    /* Phase Zero Test: Clear the render and depth buffer. */

    /* Query the output description for the swap chain, used to set the clear colour taking into account the back buffer colour space. (i.e. CPU colour correction) */
    if (TgFAILED(tgKN_GPU_EXT__SwapChain__Query_Output_DESC( &sOutput_DESC, tiCXT_SWAP )))
    {
        goto tgUnit_Test__KN_GPU__Render_0_FAILED_0;
    }

    /* Acquire the next available back buffer for a render target. */
    if (TgFAILED(tgKN_GPU_EXT__SwapChain__Acquire_Present_Buffer(tiCXT_SWAP, tiCXT_WORK)))
    {
        goto tgUnit_Test__KN_GPU__Render_0_FAILED_0;
    }

    /* Get an opaque pointer (handle) used for issuing GPU commands. Note: this has the side effect of potenially generating required pipelines. */
    psCMD = tgKN_GPU_EXT__WORK__Acquire_Command(tiCXT_WORK, ETgKN_GPU_EXT_COMMAND_GRAPHICS, u8"CMD BUF: Unit Test Render 0");
    if (nullptr == psCMD)
    {
        goto tgUnit_Test__KN_GPU__Render_0_FAILED_0;
    }

    /* Initialize the clear structure used with render start. */
    tgMM_Set_U08_0x00( &sClear_Target, sizeof(STg2_KN_GPU_Clear_Target) );
    sClear_Target.m_uiColour_Clear = 1;
    sClear_Target.m_bDepth_Clear = true;
    sClear_Target.m_avColour_Clear[0].r = 0.5F * tgPM_SIN_F32(KTgPI_F32 * tgTM_Query_Time() * 0.0005F) + 0.5F;
    sClear_Target.m_avColour_Clear[0].g = 0.5F * tgPM_SIN_F32((2.F / 3.F) * KTgPI_F32 + KTgPI_F32 * tgTM_Query_Time() * 0.0005F) + 0.5F;
    sClear_Target.m_avColour_Clear[0].b = 0.5F * tgPM_SIN_F32((4.F / 3.F) * KTgPI_F32 + KTgPI_F32 * tgTM_Query_Time() * 0.0005F) + 0.5F;
    sClear_Target.m_avColour_Clear[0].a = 1.0F;
    sClear_Target.m_avColour_Clear[0] = tgKN_GPU_Colour_Grading_CPU(sClear_Target.m_avColour_Clear[0], &sOutput_DESC);

    /* Begin rendering with the clear data from above, no camera, and no degbug configuration. */
    if (TgFAILED(tgKN_GPU_EXT__CMD__Begin_Rendering( psCMD, KTgKN_GPU_RENDER_TARGET_ID__INVALID, tiCXT_SWAP, &sClear_Target, nullptr, nullptr )))
    {
        goto tgUnit_Test__KN_GPU__Render_0_FAILED_1;
    }

    tgKN_GPU_EXT__CMD__Set_Viewport_and_Scissor( psCMD, tiCXT_SWAP );
    tgKN_GPU_EXT__CMD__End_Rendering( psCMD );

    tgKN_GPU_EXT__CMD__Command_Buffer_Close_And_Submit_With_Wait(&uiTimeline_Value, psCMD, ETgKN_GPU_EXT_COMMAND_NONE, 0);

    /* Present the acquired back buffer. This is required once it has been acquired. */
    tgKN_GPU_EXT__WORK__Present(tiCXT_WORK, tiCXT_SWAP, ETgKN_GPU_EXT_COMMAND_GRAPHICS, uiTimeline_Value);
    return (KTgS_OK);

tgUnit_Test__KN_GPU__Render_0_FAILED_1:
    tgKN_GPU_EXT__CMD__Command_Buffer_Close_And_Submit_With_Wait(nullptr, psCMD, ETgKN_GPU_EXT_COMMAND_NONE, 0);
tgUnit_Test__KN_GPU__Render_0_FAILED_0:
    return (KTgE_FAIL);
}


/* ---- tgUnit_Test__KN_GPU__Render_1 -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgUnit_Test__KN_GPU__Render_1(
    TgATTRIBUTE_UNUSED TgKN_GPU_CXT_EXEC_ID_C   tiCXT_EXEC,
    TgKN_GPU_CXT_WORK_ID_C                      tiCXT_WORK,
    TgKN_GPU_CXT_SWAP_ID_C                      tiCXT_SWAP,
    TgKN_GPU_RENDER_TARGET_ID_C                 tiRender_Target )
{
    STg2_KN_GPU_CMD_P                           psCMD;
    STg2_KN_GPU_Clear_Target                    sClear_Target;

    /* Get an opaque pointer (handle) used for issuing GPU commands. Note: this has the side effect of potenially generating required pipelines. */
    psCMD = tgKN_GPU_EXT__WORK__Acquire_Command(tiCXT_WORK, ETgKN_GPU_EXT_COMMAND_GRAPHICS, u8"CMD BUF: Unit Test Render 1");
    if (nullptr == psCMD)
    {
        return (KTgE_FAIL);
    }

    tgMM_Set_U08_0x00( &sClear_Target, sizeof(STg2_KN_GPU_Clear_Target) );
    sClear_Target.m_bDepth_Clear = true;

    /* Begin rendering with the clear data from above, no camera, and no degbug configuration. */
    if (TgFAILED(tgKN_GPU_EXT__CMD__Begin_Rendering( psCMD, tiRender_Target, tiCXT_SWAP, &sClear_Target, nullptr, nullptr )))
    {
        tgKN_GPU_EXT__CMD__Command_Buffer_Close_And_Submit_With_Wait(nullptr, psCMD, ETgKN_GPU_EXT_COMMAND_NONE, 0);
        return (KTgE_FAIL);
    }

    tgKN_GPU_EXT__CMD__Set_Viewport_and_Scissor( psCMD, tiCXT_SWAP );

    /* Clear the render target using a full screen quad. The quad will use a texture lookup for a white texture which will be multiplied by the specified colour.
       NOTE: Since the clear is done through a draw, it will be colour corrected for the buffer/colour space on the GPU. */
#if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)
    {
        STg2_KN_GPU_DBG_Quad sUI_UBO;
        tgKN_GPU_EXT__DBG__Begin_Event(psCMD, u8"UNIT TEST: Draw UI - Clear Viewport", KTgMAX_RSIZE, nullptr);
        sUI_UBO.m_vRect_UI.x = -1.0F;
        sUI_UBO.m_vRect_UI.y = -1.0F;
        sUI_UBO.m_vRect_UI.z =  1.0F;
        sUI_UBO.m_vRect_UI.w =  1.0F;
        sUI_UBO.m_vUI_Colour.r = 0.5F * tgPM_SIN_F32(KTgPI_F32 * tgTM_Query_Time() * 0.0005F) + 0.5F;
        sUI_UBO.m_vUI_Colour.g = 0.5F * tgPM_SIN_F32((2.F / 3.F) * KTgPI_F32 + KTgPI_F32 * tgTM_Query_Time() * 0.0005F) + 0.5F;
        sUI_UBO.m_vUI_Colour.b = 0.5F * tgPM_SIN_F32((4.F / 3.F) * KTgPI_F32 + KTgPI_F32 * tgTM_Query_Time() * 0.0005F) + 0.5F;
        sUI_UBO.m_vUI_Colour.a = 1.0F;
        sUI_UBO.m_uiSelect_Default_Texture_Index = 1;
        tgKN_GPU_EXT__CMD__Render_Debug_Quad(psCMD, &sUI_UBO);
        tgKN_GPU_EXT__DBG__End_Event(psCMD);

        /* This will draw two quads with a 0->1 and 0->1 gradients. Used to help validate proper colour handling in SDR, HDR (and different HDR buffers) */
        tgKN_GPU_EXT__CMD__Render_Debug_Gradient(psCMD);
    }
/*# defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
#endif

    tgKN_GPU_EXT__CMD__End_Rendering(psCMD);

    return (tgKN_GPU_EXT__CMD__Render_Target_To_Present_With_Colour_Correction( psCMD, ETgKN_GPU_EXT_COMMAND_NONE, 0, tiCXT_WORK, tiCXT_SWAP, tiRender_Target ));
}

/* ---- tgUnit_Test__KN_GPU__Render_2 -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgUnit_Test__KN_GPU__Render_2(
    TgATTRIBUTE_UNUSED TgKN_GPU_CXT_EXEC_ID_C   tiCXT_EXEC,
    TgKN_GPU_CXT_WORK_ID_C                      tiCXT_WORK,
    TgKN_GPU_CXT_SWAP_ID_C                      tiCXT_SWAP,
    TgKN_GPU_RENDER_TARGET_ID_C                 tiRender_Target )
{
    STg2_KN_GPU_CMD_P                   psCMD;
    STg2_KN_GPU_Clear_Target            sClear_Target;

    /* Get an opaque pointer (handle) used for issuing GPU commands. Note: this has the side effect of potenially generating required pipelines. */
    psCMD = tgKN_GPU_EXT__WORK__Acquire_Command(tiCXT_WORK, ETgKN_GPU_EXT_COMMAND_GRAPHICS, u8"CMD BUF: Unit Test Render 2");
    if (nullptr == psCMD)
    {
        return (KTgE_FAIL);
    }

    tgMM_Set_U08_0x00( &sClear_Target, sizeof(STg2_KN_GPU_Clear_Target) );
    sClear_Target.m_bDepth_Clear = true;

    /* Begin rendering with the clear data from above, no camera, and no degbug configuration. */
    if (TgFAILED(tgKN_GPU_EXT__CMD__Begin_Rendering( psCMD, tiRender_Target, tiCXT_SWAP, &sClear_Target, nullptr, nullptr )))
    {
        tgKN_GPU_EXT__CMD__Command_Buffer_Close_And_Submit_With_Wait(nullptr, psCMD, ETgKN_GPU_EXT_COMMAND_NONE, 0);
        return (KTgE_FAIL);
    }

    tgKN_GPU_EXT__CMD__Set_Viewport_and_Scissor( psCMD, tiCXT_SWAP );

    /* Clear the render target using a full screen quad. The quad will use a referencce image (texture lookup) for the render.
       NOTE: Since the clear is done through a draw, it will be colour corrected for the buffer/colour space on the GPU. */
#if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)
    {
        STg2_KN_GPU_DBG_Quad sUI_UBO;
        tgKN_GPU_EXT__DBG__Begin_Event(psCMD, u8"UNIT TEST: Draw UI - Clear Viewport", KTgMAX_RSIZE, nullptr);
        sUI_UBO.m_vRect_UI.x = -1.0F;
        sUI_UBO.m_vRect_UI.y = -1.0F;
        sUI_UBO.m_vRect_UI.z =  1.0F;
        sUI_UBO.m_vRect_UI.w =  1.0F;
        sUI_UBO.m_vUI_Colour.r = 1.0F;
        sUI_UBO.m_vUI_Colour.g = 1.0F;
        sUI_UBO.m_vUI_Colour.b = 1.0F;
        sUI_UBO.m_vUI_Colour.a = 1.0F;
        sUI_UBO.m_uiSelect_Default_Texture_Index = 15;
        tgKN_GPU_EXT__CMD__Render_Debug_Quad(psCMD, &sUI_UBO);
        tgKN_GPU_EXT__DBG__End_Event(psCMD);

        /* This will draw two quads with a 0->1 and 0->1 gradients. Used to help validate proper colour handling in SDR, HDR (and different HDR buffers) */
        tgKN_GPU_EXT__CMD__Render_Debug_Gradient(psCMD);
    }
/*# defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
#endif

    tgKN_GPU_EXT__CMD__End_Rendering(psCMD);

    return (tgKN_GPU_EXT__CMD__Render_Target_To_Present_With_Colour_Correction( psCMD, ETgKN_GPU_EXT_COMMAND_NONE, 0, tiCXT_WORK, tiCXT_SWAP, tiRender_Target ));
}


/* ---- tgUnit_Test__KN_GPU__Render_3 -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgUnit_Test__KN_GPU__Render_3(
    TgKN_GPU_CXT_EXEC_ID_C                      tiCXT_EXEC,
    TgKN_GPU_CXT_WORK_ID_C                      tiCXT_WORK,
    TgKN_GPU_CXT_SWAP_ID_C                      tiCXT_SWAP,
    TgKN_GPU_RENDER_TARGET_ID_C                 tiRender_Target )
{
    STg2_KN_GPU_CMD_P                   psCMD;

    /* Phase Zero Test: Clear the render and depth buffer. */

    if (TgFAILED(tgUnit_Test__KN_GPU__Render_Shared( nullptr, &psCMD, tiCXT_EXEC, tiCXT_WORK, tiCXT_SWAP, tiRender_Target )))
    {
        return (KTgE_FAIL);
    }

    tgKN_GPU_EXT__CMD__End_Rendering(psCMD);

    return (tgKN_GPU_EXT__CMD__Render_Target_To_Present_With_Colour_Correction( psCMD, ETgKN_GPU_EXT_COMMAND_NONE, 0, tiCXT_WORK, tiCXT_SWAP, tiRender_Target ));
}


/* ---- tgUnit_Test__KN_GPU__Render_4 -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgUnit_Test__KN_GPU__Render_4(
    TgKN_GPU_CXT_EXEC_ID_C                      tiCXT_EXEC,
    TgKN_GPU_CXT_WORK_ID_C                      tiCXT_WORK,
    TgKN_GPU_CXT_SWAP_ID_C                      tiCXT_SWAP,
    TgKN_GPU_RENDER_TARGET_ID_C                 tiRender_Target )
{
    STg2_KN_GPU_CMD_P                   psCMD;
    STg2_KN_GPU_Camera_Shared           sCamera_Shared;

    /* Phase Zero Test: Clear the render and depth buffer. */

    if (TgFAILED(tgUnit_Test__KN_GPU__Render_Shared(&sCamera_Shared, &psCMD, tiCXT_EXEC, tiCXT_WORK, tiCXT_SWAP, tiRender_Target)))
    {
        return (KTgE_FAIL);
    }

    #if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)
    {
        TgVEC_F32_04_1_C                    vWidth = tgMH_SET1_F32_04_1(1.5F);
        TgUINT_E32                          uiPM;
        TgVEC_F32_04_1                      avGraph_Points[5];
        TgVEC_F32_04_1                      avColour_SDR[4];
        TgVEC_F32_04_1                      avColour_HDR[4];
        TgUN_V128                           uS0, uS1;
        TgRSIZE                             uiIndex;
        TgRSIZE_C                           uiMax_Value = 20;

        tgKN_GPU_EXT__DBG__Begin_Event( psCMD, u8"UNIT TEST: Draw Debug Lines", KTgMAX_RSIZE, nullptr );
        uiPM = (TgUINT_E32)(tgPM_FLOOR_F32( tgPM_FMOD_F32( tgTM_Query_Time(), 4.0F*1600.0F ) / 1600.0F ));

        avGraph_Points[0] = tgMH_TX_F32_04_4( tgMH_Init_Point_ELEM_F32_04_1( 0.0F, 0.0F, 0.5F ), &sCamera_Shared.m_avS2C);
        avGraph_Points[0] = tgMH_DIV_F32_04_1( avGraph_Points[0], tgMH_SPW_F32_04_1(avGraph_Points[0]) );
        avGraph_Points[0] = tgMH_TX_F32_04_4( avGraph_Points[0], &sCamera_Shared.m_avC2W );

        avGraph_Points[1] = tgMH_TX_F32_04_4( tgMH_Init_Point_ELEM_F32_04_1( -0.5F, 0.0F, 0.5F ), &sCamera_Shared.m_avS2C);
        avGraph_Points[1] = tgMH_DIV_F32_04_1( avGraph_Points[1], tgMH_SPW_F32_04_1(avGraph_Points[1]) );
        avGraph_Points[1] = tgMH_TX_F32_04_4( avGraph_Points[1], &sCamera_Shared.m_avC2W );

        avGraph_Points[2] = tgMH_TX_F32_04_4( tgMH_Init_Point_ELEM_F32_04_1( 0.5F, 0.0F, 0.5F ), &sCamera_Shared.m_avS2C);
        avGraph_Points[2] = tgMH_DIV_F32_04_1( avGraph_Points[2], tgMH_SPW_F32_04_1(avGraph_Points[2]) );
        avGraph_Points[2] = tgMH_TX_F32_04_4( avGraph_Points[2], &sCamera_Shared.m_avC2W );

        avGraph_Points[3] = tgMH_TX_F32_04_4( tgMH_Init_Point_ELEM_F32_04_1( 0.0F, 0.5F, 0.5F ), &sCamera_Shared.m_avS2C);
        avGraph_Points[3] = tgMH_DIV_F32_04_1( avGraph_Points[3], tgMH_SPW_F32_04_1(avGraph_Points[3]) );
        avGraph_Points[3] = tgMH_TX_F32_04_4( avGraph_Points[3], &sCamera_Shared.m_avC2W );

        avGraph_Points[4] = tgMH_TX_F32_04_4( tgMH_Init_Point_ELEM_F32_04_1( 0.0F,-0.5F, 0.5F ), &sCamera_Shared.m_avS2C);
        avGraph_Points[4] = tgMH_DIV_F32_04_1( avGraph_Points[4], tgMH_SPW_F32_04_1(avGraph_Points[4]) );
        avGraph_Points[4] = tgMH_TX_F32_04_4( avGraph_Points[4], &sCamera_Shared.m_avC2W );

        avColour_SDR[0] = tgMH_Init_ELEM_F32_04_1( 1.0F, 0.0F, 0.0F, 1.0F );
        avColour_SDR[1] = tgMH_Init_ELEM_F32_04_1( 0.0F, 1.0F, 0.0F, 1.0F );
        avColour_SDR[2] = tgMH_Init_ELEM_F32_04_1( 0.0F, 0.0F, 1.0F, 1.0F );
        avColour_SDR[3] = tgMH_Init_ELEM_F32_04_1( 1.0F, 1.0F, 1.0F, 1.0F );

        avColour_HDR[0] = tgMH_Init_ELEM_F32_04_1(10.0F,  0.0F,  0.0F, 1.0F);
        avColour_HDR[1] = tgMH_Init_ELEM_F32_04_1( 0.0F, 10.0F,  0.0F, 1.0F);
        avColour_HDR[2] = tgMH_Init_ELEM_F32_04_1( 0.0F,  0.0F, 10.0F, 1.0F);
        avColour_HDR[3] = tgMH_Init_ELEM_F32_04_1(10.0F, 10.0F, 10.0F, 1.0F);

        for( uiIndex = 0; uiIndex <= uiMax_Value; ++uiIndex )
        {
            uS0.m_vF32_04_1 = tgMH_SUB_F32_04_1(avGraph_Points[1],avGraph_Points[0]);
            uS0.m_vF32_04_1 = tgMH_MUL_F32_04_1(uS0.m_vF32_04_1, tgMH_SET1_F32_04_1( (float)(uiMax_Value - uiIndex) / (float)uiMax_Value ));
            uS0.m_vF32_04_1 = tgMH_ADD_F32_04_1(uS0.m_vF32_04_1,avGraph_Points[0]);

            uS1.m_vF32_04_1 = tgMH_SUB_F32_04_1(avGraph_Points[4],avGraph_Points[0]);
            uS1.m_vF32_04_1 = tgMH_MUL_F32_04_1(uS1.m_vF32_04_1, tgMH_SET1_F32_04_1( (float)(uiIndex) / (float)uiMax_Value ));
            uS1.m_vF32_04_1 = tgMH_ADD_F32_04_1(uS1.m_vF32_04_1,avGraph_Points[0]);

            tgKN_GPU__CMD__Add_Debug_Line( psCMD, uS0.m_vF32_04_1, avColour_SDR[(uiPM+0u) % TgARRAY_COUNT(avColour_SDR)], uS1.m_vF32_04_1,
                                           avColour_SDR[(uiPM+0u) % TgARRAY_COUNT(avColour_SDR)], vWidth );

            uS0.m_vF32_04_1 = tgMH_SUB_F32_04_1(avGraph_Points[2],avGraph_Points[0]);
            uS0.m_vF32_04_1 = tgMH_MUL_F32_04_1(uS0.m_vF32_04_1, tgMH_SET1_F32_04_1( (float)(uiMax_Value - uiIndex) / (float)uiMax_Value ));
            uS0.m_vF32_04_1 = tgMH_ADD_F32_04_1(uS0.m_vF32_04_1,avGraph_Points[0]);

            uS1.m_vF32_04_1 = tgMH_SUB_F32_04_1(avGraph_Points[4],avGraph_Points[0]);
            uS1.m_vF32_04_1 = tgMH_MUL_F32_04_1(uS1.m_vF32_04_1, tgMH_SET1_F32_04_1( (float)(uiIndex) / (float)uiMax_Value ));
            uS1.m_vF32_04_1 = tgMH_ADD_F32_04_1(uS1.m_vF32_04_1,avGraph_Points[0]);

            tgKN_GPU__CMD__Add_Debug_Line( psCMD, uS0.m_vF32_04_1, avColour_SDR[(uiPM+1u) % TgARRAY_COUNT(avColour_HDR)], uS1.m_vF32_04_1,
                                           avColour_SDR[(uiPM+1u) % TgARRAY_COUNT(avColour_HDR)], vWidth );

            uS0.m_vF32_04_1 = tgMH_SUB_F32_04_1(avGraph_Points[2],avGraph_Points[0]);
            uS0.m_vF32_04_1 = tgMH_MUL_F32_04_1(uS0.m_vF32_04_1, tgMH_SET1_F32_04_1( (float)(uiMax_Value - uiIndex) / (float)uiMax_Value ));
            uS0.m_vF32_04_1 = tgMH_ADD_F32_04_1(uS0.m_vF32_04_1,avGraph_Points[0]);

            uS1.m_vF32_04_1 = tgMH_SUB_F32_04_1(avGraph_Points[3],avGraph_Points[0]);
            uS1.m_vF32_04_1 = tgMH_MUL_F32_04_1(uS1.m_vF32_04_1, tgMH_SET1_F32_04_1( (float)(uiIndex) / (float)uiMax_Value ));
            uS1.m_vF32_04_1 = tgMH_ADD_F32_04_1(uS1.m_vF32_04_1,avGraph_Points[0]);

            tgKN_GPU__CMD__Add_Debug_Line( psCMD, uS0.m_vF32_04_1, avColour_SDR[(uiPM+2u) % TgARRAY_COUNT(avColour_SDR)], uS1.m_vF32_04_1,
                                           avColour_SDR[(uiPM+2u) % TgARRAY_COUNT(avColour_SDR)], vWidth );

            uS0.m_vF32_04_1 = tgMH_SUB_F32_04_1(avGraph_Points[1],avGraph_Points[0]);
            uS0.m_vF32_04_1 = tgMH_MUL_F32_04_1(uS0.m_vF32_04_1, tgMH_SET1_F32_04_1( (float)(uiMax_Value - uiIndex) / (float)uiMax_Value ));
            uS0.m_vF32_04_1 = tgMH_ADD_F32_04_1(uS0.m_vF32_04_1,avGraph_Points[0]);

            uS1.m_vF32_04_1 = tgMH_SUB_F32_04_1(avGraph_Points[3],avGraph_Points[0]);
            uS1.m_vF32_04_1 = tgMH_MUL_F32_04_1(uS1.m_vF32_04_1, tgMH_SET1_F32_04_1( (float)(uiIndex) / (float)uiMax_Value ));
            uS1.m_vF32_04_1 = tgMH_ADD_F32_04_1(uS1.m_vF32_04_1,avGraph_Points[0]);

            tgKN_GPU__CMD__Add_Debug_Line( psCMD, uS0.m_vF32_04_1, avColour_SDR[(uiPM+3u) % TgARRAY_COUNT(avColour_HDR)], uS1.m_vF32_04_1,
                                           avColour_SDR[(uiPM+3u) % TgARRAY_COUNT(avColour_HDR)], vWidth );
        }

        avGraph_Points[0] = tgMH_TX_F32_04_4( tgMH_Init_Point_ELEM_F32_04_1( -0.5F, -0.5F, 0.5F ), &sCamera_Shared.m_avS2C);
        avGraph_Points[0] = tgMH_DIV_F32_04_1( avGraph_Points[0], tgMH_SPW_F32_04_1(avGraph_Points[0]) );
        avGraph_Points[0] = tgMH_TX_F32_04_4( avGraph_Points[0], &sCamera_Shared.m_avC2W );

        avGraph_Points[1] = tgMH_TX_F32_04_4( tgMH_Init_Point_ELEM_F32_04_1( 0.5F, -0.5F, 0.5F ), &sCamera_Shared.m_avS2C);
        avGraph_Points[1] = tgMH_DIV_F32_04_1( avGraph_Points[1], tgMH_SPW_F32_04_1(avGraph_Points[1]) );
        avGraph_Points[1] = tgMH_TX_F32_04_4( avGraph_Points[1], &sCamera_Shared.m_avC2W );

        avGraph_Points[2] = tgMH_TX_F32_04_4( tgMH_Init_Point_ELEM_F32_04_1( -0.5F, 0.5F, 0.5F ), &sCamera_Shared.m_avS2C);
        avGraph_Points[2] = tgMH_DIV_F32_04_1( avGraph_Points[2], tgMH_SPW_F32_04_1(avGraph_Points[2]) );
        avGraph_Points[2] = tgMH_TX_F32_04_4( avGraph_Points[2], &sCamera_Shared.m_avC2W );

        avGraph_Points[3] = tgMH_TX_F32_04_4( tgMH_Init_Point_ELEM_F32_04_1( 0.5F, 0.5F, 0.5F ), &sCamera_Shared.m_avS2C);
        avGraph_Points[3] = tgMH_DIV_F32_04_1( avGraph_Points[3], tgMH_SPW_F32_04_1(avGraph_Points[3]) );
        avGraph_Points[3] = tgMH_TX_F32_04_4( avGraph_Points[3], &sCamera_Shared.m_avC2W );

        for( uiIndex = 0; uiIndex <= uiMax_Value; ++uiIndex )
        {
            uS0.m_vF32_04_1 = tgMH_SUB_F32_04_1(avGraph_Points[1],avGraph_Points[0]);
            uS0.m_vF32_04_1 = tgMH_MUL_F32_04_1(uS0.m_vF32_04_1, tgMH_SET1_F32_04_1( 0.5F * (float)(uiMax_Value - uiIndex) / (float)uiMax_Value ));
            uS0.m_vF32_04_1 = tgMH_ADD_F32_04_1(uS0.m_vF32_04_1,avGraph_Points[0]);

            uS1.m_vF32_04_1 = tgMH_SUB_F32_04_1(avGraph_Points[0], avGraph_Points[2]);
            uS1.m_vF32_04_1 = tgMH_MUL_F32_04_1(uS1.m_vF32_04_1, tgMH_SET1_F32_04_1( 0.5F + 0.5F * ((float)(uiMax_Value - uiIndex) / (float)uiMax_Value )));
            uS1.m_vF32_04_1 = tgMH_ADD_F32_04_1(uS1.m_vF32_04_1,avGraph_Points[2]);

            tgKN_GPU__CMD__Add_Debug_Line( psCMD, uS0.m_vF32_04_1, avColour_HDR[(uiPM+0u) % TgARRAY_COUNT(avColour_SDR)], uS1.m_vF32_04_1,
                                           avColour_HDR[(uiPM+0u) % TgARRAY_COUNT(avColour_SDR)], vWidth );

            uS0.m_vF32_04_1 = tgMH_SUB_F32_04_1(avGraph_Points[0],avGraph_Points[1]);
            uS0.m_vF32_04_1 = tgMH_MUL_F32_04_1(uS0.m_vF32_04_1, tgMH_SET1_F32_04_1( 0.5F * (float)(uiMax_Value - uiIndex) / (float)uiMax_Value ));
            uS0.m_vF32_04_1 = tgMH_ADD_F32_04_1(uS0.m_vF32_04_1,avGraph_Points[1]);

            uS1.m_vF32_04_1 = tgMH_SUB_F32_04_1(avGraph_Points[1], avGraph_Points[3]);
            uS1.m_vF32_04_1 = tgMH_MUL_F32_04_1(uS1.m_vF32_04_1, tgMH_SET1_F32_04_1( 0.5F + 0.5F * ((float)(uiMax_Value - uiIndex) / (float)uiMax_Value )));
            uS1.m_vF32_04_1 = tgMH_ADD_F32_04_1(uS1.m_vF32_04_1,avGraph_Points[3]);

            tgKN_GPU__CMD__Add_Debug_Line( psCMD, uS0.m_vF32_04_1, avColour_HDR[(uiPM+1u) % TgARRAY_COUNT(avColour_HDR)], uS1.m_vF32_04_1,
                                           avColour_HDR[(uiPM+1u) % TgARRAY_COUNT(avColour_HDR)], vWidth );

            uS0.m_vF32_04_1 = tgMH_SUB_F32_04_1(avGraph_Points[1],avGraph_Points[3]);
            uS0.m_vF32_04_1 = tgMH_MUL_F32_04_1(uS0.m_vF32_04_1, tgMH_SET1_F32_04_1( 0.5F * (float)(uiMax_Value - uiIndex) / (float)uiMax_Value ));
            uS0.m_vF32_04_1 = tgMH_ADD_F32_04_1(uS0.m_vF32_04_1,avGraph_Points[3]);

            uS1.m_vF32_04_1 = tgMH_SUB_F32_04_1(avGraph_Points[3], avGraph_Points[2]);
            uS1.m_vF32_04_1 = tgMH_MUL_F32_04_1(uS1.m_vF32_04_1, tgMH_SET1_F32_04_1( 0.5F + 0.5F * ((float)(uiMax_Value - uiIndex) / (float)uiMax_Value )));
            uS1.m_vF32_04_1 = tgMH_ADD_F32_04_1(uS1.m_vF32_04_1,avGraph_Points[2]);

            tgKN_GPU__CMD__Add_Debug_Line( psCMD, uS0.m_vF32_04_1, avColour_SDR[(uiPM+2u) % TgARRAY_COUNT(avColour_SDR)], uS1.m_vF32_04_1,
                                           avColour_SDR[(uiPM+2u) % TgARRAY_COUNT(avColour_SDR)], vWidth );

            uS0.m_vF32_04_1 = tgMH_SUB_F32_04_1(avGraph_Points[0],avGraph_Points[2]);
            uS0.m_vF32_04_1 = tgMH_MUL_F32_04_1(uS0.m_vF32_04_1, tgMH_SET1_F32_04_1( 0.5F * (float)(uiMax_Value - uiIndex) / (float)uiMax_Value ));
            uS0.m_vF32_04_1 = tgMH_ADD_F32_04_1(uS0.m_vF32_04_1,avGraph_Points[2]);

            uS1.m_vF32_04_1 = tgMH_SUB_F32_04_1(avGraph_Points[2], avGraph_Points[3]);
            uS1.m_vF32_04_1 = tgMH_MUL_F32_04_1(uS1.m_vF32_04_1, tgMH_SET1_F32_04_1( 0.5F + 0.5F * ((float)(uiMax_Value - uiIndex) / (float)uiMax_Value )));
            uS1.m_vF32_04_1 = tgMH_ADD_F32_04_1(uS1.m_vF32_04_1,avGraph_Points[3]);

            tgKN_GPU__CMD__Add_Debug_Line( psCMD, uS0.m_vF32_04_1, avColour_HDR[(uiPM+3u) % TgARRAY_COUNT(avColour_HDR)], uS1.m_vF32_04_1,
                                           avColour_HDR[(uiPM+3u) % TgARRAY_COUNT(avColour_HDR)], vWidth );
        }

        tgKN_GPU__CMD__Render_Debug_Line( psCMD );
        tgKN_GPU_EXT__DBG__End_Event( psCMD );
    }
    /*# defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
    #endif

    tgKN_GPU_EXT__CMD__End_Rendering(psCMD);

    return (tgKN_GPU_EXT__CMD__Render_Target_To_Present_With_Colour_Correction( psCMD, ETgKN_GPU_EXT_COMMAND_NONE, 0, tiCXT_WORK, tiCXT_SWAP, tiRender_Target ));
}


/* ---- tgUnit_Test__KN_GPU__Render_5 -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgUnit_Test__KN_GPU__Render_5(
    TgKN_GPU_CXT_EXEC_ID_C                      tiCXT_EXEC,
    TgKN_GPU_CXT_WORK_ID_C                      tiCXT_WORK,
    TgKN_GPU_CXT_SWAP_ID_C                      tiCXT_SWAP,
    TgKN_GPU_RENDER_TARGET_ID_C                 tiRender_Target )
{
    STg2_KN_GPU_CMD_P                   psCMD;
    STg2_KN_GPU_Camera_Shared           sCamera_Shared;

    /* Phase Zero Test: Clear the render and depth buffer. */

    if (TgFAILED(tgUnit_Test__KN_GPU__Render_Shared(&sCamera_Shared, &psCMD, tiCXT_EXEC, tiCXT_WORK, tiCXT_SWAP, tiRender_Target)))
    {
        return (KTgE_FAIL);
    }

#if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)
    {
        TgFLOAT32_C                         fDesiredDepth = 40.0F; // Positive Z distance from camera
        TgRSIZE                             uiModel;
        TgVEC_F32_04_4                      avTranslation, avRotation, avTemp0, avTemp1;
        TgVEC_F32_04_4                      avTranslation_UI_S0, avTranslation_UI_S1;
        TgVEC_UN_F32_04_4                   uScale;
        TgVEC_F32_04_1                      avPerceptual_Colours_SDR[g_nuiPoints_Per_Edge * g_nuiPoints_Per_Edge * g_nuiPoints_Per_Edge];
        TgVEC_F32_04_1                      avPerceptual_Colours_HDR[g_nuiPoints_Per_Edge* g_nuiPoints_Per_Edge* g_nuiPoints_Per_Edge];
        TgUN_V128                           uUI_S0, uUI_S1;
        TgRSIZE                             nuiGeom;
        STg2_KN_GPU_DBG_Geom_P              asGeom;

        uUI_S0.m_vF32_04_1 = tgMH_Init_Point_ELEM_F32_04_1(-0.5F, 0.0F, 0.0F);
        uUI_S0.m_vF32_04_1 = tgMH_TX_F32_04_4(uUI_S0.m_vF32_04_1, &sCamera_Shared.m_avS2C);
        uUI_S0.m_vF32_04_1 = tgMH_DIV_F32_04_1(uUI_S0.m_vF32_04_1, tgMH_SPW_F32_04_1(uUI_S0.m_vF32_04_1));
        uUI_S0.m_vS_F32_04_1.x *= fDesiredDepth / uUI_S0.m_vS_F32_04_1.z;
        uUI_S0.m_vS_F32_04_1.y *= fDesiredDepth / uUI_S0.m_vS_F32_04_1.z;
        uUI_S0.m_vS_F32_04_1.z = fDesiredDepth;
        uUI_S0.m_vS_F32_04_1.w = 1.0F;
        uUI_S0.m_vF32_04_1 = tgMH_TX_F32_04_4(uUI_S0.m_vF32_04_1, &sCamera_Shared.m_avC2W);

        uUI_S1.m_vF32_04_1 = tgMH_Init_Point_ELEM_F32_04_1(0.5F, 0.0F, 0.8F);
        uUI_S1.m_vF32_04_1 = tgMH_TX_F32_04_4(uUI_S1.m_vF32_04_1, &sCamera_Shared.m_avS2C);
        uUI_S1.m_vF32_04_1 = tgMH_DIV_F32_04_1(uUI_S1.m_vF32_04_1, tgMH_SPW_F32_04_1(uUI_S1.m_vF32_04_1));
        uUI_S1.m_vS_F32_04_1.x *= fDesiredDepth / uUI_S1.m_vS_F32_04_1.z;
        uUI_S1.m_vS_F32_04_1.y *= fDesiredDepth / uUI_S1.m_vS_F32_04_1.z;
        uUI_S1.m_vS_F32_04_1.z = fDesiredDepth;
        uUI_S1.m_vS_F32_04_1.w = 1.0F;
        uUI_S1.m_vF32_04_1 = tgMH_TX_F32_04_4(uUI_S1.m_vF32_04_1, &sCamera_Shared.m_avC2W);

        tgMH_CLI_F32_04_4(&uScale.m_mF32_04_4);
        uScale.m_mS_F32_04_4._11 = 0.5F;
        uScale.m_mS_F32_04_4._22 = 0.5F;
        uScale.m_mS_F32_04_4._33 = 0.5F;

        /* Generate perceptually distributed colors for maximum contrast */
        tgUnit_Test__Generate_Perceptual_Grid_Colors(avPerceptual_Colours_SDR,false);
        tgUnit_Test__Generate_Perceptual_Grid_Colors(avPerceptual_Colours_HDR, true);

        tgMH_CLI_F32_04_4( &avTranslation );
        tgMH_CLI_F32_04_4( &avRotation );
        tgMH_CLI_F32_04_4( &avTranslation_UI_S0 );
        tgMH_CLI_F32_04_4( &avTranslation_UI_S1 );

        tgMH_Set_T_F32_04_4(&avTranslation_UI_S0, uUI_S0.m_vF32_04_1);
        tgMH_Set_T_F32_04_4(&avTranslation_UI_S1, uUI_S1.m_vF32_04_1);

        nuiGeom = g_nuiPoints_Per_Edge * g_nuiPoints_Per_Edge * g_nuiPoints_Per_Edge;
        TgVERIFY(nuiGeom * 2 < KTgKN_GPU_MAX_DBG_STORAGE_GEOM_INSTANCE);
        asGeom = (STg2_KN_GPU_DBG_Geom_P)TgMALLOC_TEMP(sizeof(STg2_KN_GPU_DBG_Geom) * nuiGeom * 2);

        for (uiModel= 0; uiModel < nuiGeom; ++uiModel)
        {
            TgFLOAT32_C                         fX = (TgFLOAT32)(uiModel % g_nuiPoints_Per_Edge) - (g_nuiPoints_Per_Edge - 1) / 2.0F;
            TgFLOAT32_C                         fY = (TgFLOAT32)((uiModel / g_nuiPoints_Per_Edge) % g_nuiPoints_Per_Edge) - (g_nuiPoints_Per_Edge - 1) / 2.0F;
            TgFLOAT32_C                         fZ = (TgFLOAT32)(uiModel / (g_nuiPoints_Per_Edge * g_nuiPoints_Per_Edge)) - (g_nuiPoints_Per_Edge - 1) / 2.0F;
            TgVEC_F32_04_1_C                    vT = tgMH_Init_ELEM_F32_04_1(fX, fY, fZ, 1.0F);

            tgMH_Set_T_F32_04_4(&avTranslation, vT);
            tgMH_Set_Euler_ELEM_F32_04_4( &avRotation,
                -45.0f * KTgPI_F32 / 180.0f,
                 45.0f * KTgPI_F32 / 180.0f,
                 45.0f * KTgPI_F32 / 180.0f * tgTM_Query_Time() * 0.0005F );
            tgMH_CAT_F32_04_4(&avTemp0, &avTranslation, &uScale.m_mF32_04_4);
            tgMH_CAT_F32_04_4(&avTemp1, &avTemp0, &avRotation);

            tgMH_CAT_F32_04_4(&asGeom[uiModel].m_avModel_Transform, &avTemp1, &avTranslation_UI_S0);
            asGeom[uiModel].m_vModel_Colour = avPerceptual_Colours_SDR[uiModel];

            tgMH_CAT_F32_04_4(&asGeom[nuiGeom + uiModel].m_avModel_Transform, &avTemp1, &avTranslation_UI_S1);
            asGeom[nuiGeom + uiModel].m_vModel_Colour = avPerceptual_Colours_HDR[uiModel];
        }

        tgKN_GPU_EXT__DBG__Begin_Event(psCMD, u8"UNIT TEST: Draw Cube (Instanced, List)", KTgMAX_RSIZE, nullptr);
        tgKN_GPU_EXT__CMD__Render_Debug_Geom_Instance(psCMD, ETgKN_GPU_DEBUG_PM_3D_BOX, nuiGeom * 2, asGeom, true);
        tgKN_GPU_EXT__DBG__End_Event(psCMD);

        TgFREE_TEMP(asGeom);
    }
/*# defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
#endif

    tgKN_GPU_EXT__CMD__End_Rendering(psCMD);

    return (tgKN_GPU_EXT__CMD__Render_Target_To_Present_With_Colour_Correction( psCMD, ETgKN_GPU_EXT_COMMAND_NONE, 0, tiCXT_WORK, tiCXT_SWAP, tiRender_Target ));
}



/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Local File Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgUnit_Test__KN_GPU__Render_Shared --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT tgUnit_Test__KN_GPU__Render_Shared(
    STg2_KN_GPU_Camera_Shared_PC                psCamera_Shared,
    STg2_KN_GPU_CMD_PP                          ppsCMD,
    TgATTRIBUTE_UNUSED TgKN_GPU_CXT_EXEC_ID_C   tiCXT_EXEC,
    TgKN_GPU_CXT_WORK_ID                        tiCXT_WORK,
    TgKN_GPU_CXT_SWAP_ID_C                      tiCXT_SWAP,
    TgKN_GPU_RENDER_TARGET_ID_C                 tiRender_Target )
{
    STg2_KN_GPU_Render_Target_DESC      sRender_Target_DESC;
    STg2_KN_GPU_CMD_P                   psCMD;
    TgFLOAT32                           fWidth, fHeight;
    STg2_KN_GPU_Camera                  sCamera;
    STg2_KN_GPU_Clear_Target            sClear_Target;

    /* Query the render target description for the swap chain. */
    if (TgFAILED(tgKN_GPU_EXT__SwapChain__Query_Render_Target_DESC( &sRender_Target_DESC, tiCXT_SWAP )))
    {
        goto tgUnit_Test__KN_GPU__Render_Background_And_Gradient_FAILED_0;
    }

    /* Get an opaque pointer (handle) used for issuing GPU commands. Note: this has the side effect of potenially generating required pipelines. */
    psCMD = tgKN_GPU_EXT__WORK__Acquire_Command(tiCXT_WORK, ETgKN_GPU_EXT_COMMAND_GRAPHICS, u8"CMD BUF: Unit Test Render Shared");
    if (nullptr == psCMD)
    {
        goto tgUnit_Test__KN_GPU__Render_Background_And_Gradient_FAILED_0;
    }

    fWidth = (TgFLOAT32)sRender_Target_DESC.m_uiWidth;
    fHeight = (TgFLOAT32)sRender_Target_DESC.m_uiHeight;

    /* In preparation of drawing 3D geometry setup a default camera and lighting */
    sCamera.m_sConfiguration.m_uCamera_Position.m_vF32_04_1 = tgMH_Init_Point_ELEM_F32_04_1( 0.0F, 50.0F, 5.0F );
    sCamera.m_sConfiguration.m_uCamera_Target.m_vF32_04_1 = tgMH_Init_Point_ELEM_F32_04_1( 0.0F, 0.0F, 0.0F );
    sCamera.m_sConfiguration.m_fAspect_Ratio = fWidth / fHeight;
    sCamera.m_sConfiguration.m_fFoV = 35.0F * KTgPI_F32 / 180.0f;
    sCamera.m_sConfiguration.m_fNear = 0.01F;
    sCamera.m_sConfiguration.m_fFar = 100.0F;
    tgKN_GPU_Init_Camera(&sCamera, &sCamera.m_sConfiguration, tgMH_Init_Vector_ELEM_F32_04_1( 0.0f, 1.0f, 0.0f ) );

    tgMM_Set_U08_0x00( &sClear_Target, sizeof(STg2_KN_GPU_Clear_Target) );
    sClear_Target.m_bDepth_Clear = true;

    /* Begin rendering can trigger clears as well, depending on the configuration of the render targets data. */
    if (TgFAILED(tgKN_GPU_EXT__CMD__Begin_Rendering( psCMD, tiRender_Target, tiCXT_SWAP, &sClear_Target, &sCamera, nullptr )))
    {
        goto tgUnit_Test__KN_GPU__Render_Background_And_Gradient_FAILED_1;
    }

    tgKN_GPU_EXT__CMD__Set_Viewport_and_Scissor( psCMD, tiCXT_SWAP );

    /* Clear the render target using a full screen quad. */
#if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)
    {
        TgFLOAT32_C                         fDesiredDepth = 10.0F; // Positive Z distance from camera
        STg2_KN_GPU_DBG_Quad                sUI_UBO;
        STg2_KN_GPU_DBG_Geom                sGeom_UBO;
        TgSINT_E32                          iPM;
        TgUN_V128                           uUI_S0;

        tgKN_GPU_EXT__DBG__Begin_Event(psCMD, u8"UNIT TEST: Draw UI - Clear Viewport", KTgMAX_RSIZE, nullptr);
        sUI_UBO.m_vRect_UI.x = -1.0F;
        sUI_UBO.m_vRect_UI.y = -1.0F;
        sUI_UBO.m_vRect_UI.z =  1.0F;
        sUI_UBO.m_vRect_UI.w =  1.0F;
        sUI_UBO.m_vUI_Colour.r = 1.0F;
        sUI_UBO.m_vUI_Colour.g = 1.0F;
        sUI_UBO.m_vUI_Colour.b = 1.0F;
        sUI_UBO.m_vUI_Colour.a = 1.0F;
        sUI_UBO.m_uiSelect_Default_Texture_Index = 15;
        tgKN_GPU_EXT__CMD__Render_Debug_Quad(psCMD, &sUI_UBO);
        tgKN_GPU_EXT__DBG__End_Event(psCMD);

        /* This will draw two quads with a 0->1 and 0->1 gradients. Used to help validate proper colour handling in SDR, HDR (and different HDR buffers) */
        tgKN_GPU_EXT__CMD__Render_Debug_Gradient(psCMD);

        /* Validate debug geometry by cycling through all of the 3D primitives (in the upper left corner of the screen).
        Validate line drawing by rendering a coordinate axis */

        uUI_S0.m_vF32_04_1 = tgMH_Init_Point_ELEM_F32_04_1(-0.8F, -0.5F, 0.0F);                             // Start with desired NDC position (X,Y) and near plane Z
        uUI_S0.m_vF32_04_1 = tgMH_TX_F32_04_4(uUI_S0.m_vF32_04_1, &sCamera.m_sCamera_Shared.m_avS2C);       // Transform NDC to camera space using inverse projection
        uUI_S0.m_vF32_04_1 = tgMH_DIV_F32_04_1(uUI_S0.m_vF32_04_1, tgMH_SPW_F32_04_1(uUI_S0.m_vF32_04_1));  // Apply perspective divide to get actual camera space coordinates
        uUI_S0.m_vS_F32_04_1.x *= fDesiredDepth / uUI_S0.m_vS_F32_04_1.z;                                   // Scale the X,Y coordinates to the desired depth while maintaining the same screen position
        uUI_S0.m_vS_F32_04_1.y *= fDesiredDepth / uUI_S0.m_vS_F32_04_1.z;
        uUI_S0.m_vS_F32_04_1.z = fDesiredDepth;                                                             // Set the desired positive Z depth in camera space
        uUI_S0.m_vS_F32_04_1.w = 1.0F;                                                                      // Ensure proper point transformation
        uUI_S0.m_vF32_04_1 = tgMH_TX_F32_04_4(uUI_S0.m_vF32_04_1, &sCamera.m_sCamera_Shared.m_avC2W);       // Transform from camera space to world space

        tgKN_GPU_EXT__DBG__Begin_Event(psCMD, u8"UNIT TEST: Draw Debug Geometry", KTgMAX_RSIZE, nullptr);

        tgMH_Init_Euler_ELEM_F32_04_4( &sGeom_UBO.m_avModel_Transform, 0.0F, 0.0F, -45.0f * KTgPI_F32 / 180.0f * tgTM_Query_Time() * 0.005F );
        tgMH_Set_T_F32_04_4(&sGeom_UBO.m_avModel_Transform, uUI_S0.m_vF32_04_1);
        sGeom_UBO.m_vModel_Colour = tgMH_Init_ELEM_F32_04_1(1.0F, 1.0F, 1.0F, 1.0F);
        iPM = (TgSINT_E32)(tgPM_FLOOR_F32(tgPM_FMOD_F32(tgTM_Query_Time(), (float)ETgKN_GPU_DEBUG_PM_3D_COUNT * 1600.0F) / 1600.0F));
        tgKN_GPU_EXT__CMD__Render_Debug_Geom(psCMD, (ETgKN_GPU_DEBUG_PM)((TgSINT_E32)ETgKN_GPU_DEBUG_PM_3D_START + iPM), &sGeom_UBO, false );

        tgKN_GPU__CMD__Render_Debug_Axes(psCMD, (TgVEC_F32_04_3_P)&sGeom_UBO.m_avModel_Transform, uUI_S0.m_vF32_04_1);


        uUI_S0.m_vF32_04_1 = tgMH_Init_Point_ELEM_F32_04_1(0.8F, -0.5F, 0.0F);                              // Start with desired NDC position (X,Y) and near plane Z
        uUI_S0.m_vF32_04_1 = tgMH_TX_F32_04_4(uUI_S0.m_vF32_04_1, &sCamera.m_sCamera_Shared.m_avS2C);       // Transform NDC to camera space using inverse projection
        uUI_S0.m_vF32_04_1 = tgMH_DIV_F32_04_1(uUI_S0.m_vF32_04_1, tgMH_SPW_F32_04_1(uUI_S0.m_vF32_04_1));  // Apply perspective divide to get actual camera space coordinates
        uUI_S0.m_vS_F32_04_1.x *= fDesiredDepth / uUI_S0.m_vS_F32_04_1.z;                                   // Scale the X,Y coordinates to the desired depth while maintaining the same screen position
        uUI_S0.m_vS_F32_04_1.y *= fDesiredDepth / uUI_S0.m_vS_F32_04_1.z;
        uUI_S0.m_vS_F32_04_1.z = fDesiredDepth;                                                             // Set the desired positive Z depth in camera space
        uUI_S0.m_vS_F32_04_1.w = 1.0F;                                                                      // Ensure proper point transformation
        uUI_S0.m_vF32_04_1 = tgMH_TX_F32_04_4(uUI_S0.m_vF32_04_1, &sCamera.m_sCamera_Shared.m_avC2W);       // Transform from camera space to world space

        tgKN_GPU_EXT__DBG__Begin_Event(psCMD, u8"UNIT TEST: Draw Debug Geometry", KTgMAX_RSIZE, nullptr);

        tgMH_Init_Euler_ELEM_F32_04_4(&sGeom_UBO.m_avModel_Transform, 0.0F, 0.0F, -45.0f * KTgPI_F32 / 180.0f * tgTM_Query_Time() * 0.005F);
        tgMH_Set_T_F32_04_4(&sGeom_UBO.m_avModel_Transform, uUI_S0.m_vF32_04_1);
        sGeom_UBO.m_vModel_Colour = tgMH_Init_ELEM_F32_04_1(1.0F, 1.0F, 1.0F, 1.0F);
        iPM = (TgSINT_E32)(tgPM_FLOOR_F32(tgPM_FMOD_F32(tgTM_Query_Time(), (float)ETgKN_GPU_DEBUG_PM_3D_COUNT * 1600.0F) / 1600.0F));
        tgKN_GPU_EXT__CMD__Render_Debug_Geom(psCMD, (ETgKN_GPU_DEBUG_PM)((TgSINT_E32)ETgKN_GPU_DEBUG_PM_3D_START + iPM), &sGeom_UBO, true );

        tgKN_GPU__CMD__Render_Debug_Axes(psCMD, (TgVEC_F32_04_3_P)&sGeom_UBO.m_avModel_Transform, uUI_S0.m_vF32_04_1);


        tgKN_GPU_EXT__DBG__End_Event(psCMD);
    }
/*# defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
#endif

    if (nullptr != ppsCMD)
    {
        *ppsCMD = psCMD;
    }

    if (nullptr != psCamera_Shared)
    {
        *psCamera_Shared = sCamera.m_sCamera_Shared;
    }

    return (KTgS_OK);

tgUnit_Test__KN_GPU__Render_Background_And_Gradient_FAILED_1:
    tgKN_GPU_EXT__CMD__Command_Buffer_Close_And_Submit_With_Wait(nullptr, psCMD, ETgKN_GPU_EXT_COMMAND_NONE, 0);
tgUnit_Test__KN_GPU__Render_Background_And_Gradient_FAILED_0:
    return (KTgE_FAIL);
}


#if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)

/* ---- tgUnit_Test__Generate_Perceptual_Grid_Colors ----------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgUnit_Test__Generate_Perceptual_Grid_Colors( TgVEC_F32_04_1_P pavColours, TgBOOL_C bUseHDR )
{
    TgFLOAT32_C                         fV_Max = bUseHDR ? 10.0F : 1.0F;
    TgRSIZE                             uiIndex;
    TgUN_V128                           vCL;

    /* Generate colors that represent P709 color space continuum using HSV interpolation
       RGB cube corners mapped properly: Black(0,0,0) -> Primaries -> White(1,1,1) */
    for (uiIndex = 0; uiIndex < g_nuiPoints_Per_Edge* g_nuiPoints_Per_Edge * g_nuiPoints_Per_Edge; ++uiIndex)
    {
        TgSINT_E32_C                    iX = (TgSINT_E32)(uiIndex % g_nuiPoints_Per_Edge);
        TgSINT_E32_C                    iY = (TgSINT_E32)((uiIndex / g_nuiPoints_Per_Edge) % g_nuiPoints_Per_Edge);
        TgSINT_E32_C                    iZ = (TgSINT_E32)(uiIndex / (g_nuiPoints_Per_Edge* g_nuiPoints_Per_Edge));

        TgFLOAT32_C                     fNormX = (TgFLOAT32)iX / (TgFLOAT32)(g_nuiPoints_Per_Edge - 1);
        TgFLOAT32_C                     fNormY = (TgFLOAT32)iY / (TgFLOAT32)(g_nuiPoints_Per_Edge - 1);
        TgFLOAT32_C                     fNormZ = (TgFLOAT32)iZ / (TgFLOAT32)(g_nuiPoints_Per_Edge - 1);

        TgVEC_F32_04_1_C                vRGB = tgMH_Init_ELEM_F32_04_1(fNormX, fNormY, fNormZ, 1.0F);
        TgUN_V128                       uHSV = { .m_vF32_04_1 = tgCM_CL_F32_Convert_RGB_To_HSV(vRGB) };
        TgFLOAT32_C                     fSigmoidZ = 1.0F / (1.0F + tgPM_EXP_F32(-10.0F * (uHSV.m_vS_F32_04_1.z - 0.5F)));

        uHSV.m_vS_F32_04_1.y = tgCM_CLP_F32(tgPM_SIN_F32(KTgPI_F32*0.5F*uHSV.m_vS_F32_04_1.y), 0.0F, 1.0F);
        uHSV.m_vS_F32_04_1.z = fSigmoidZ * fV_Max;

        /* Convert HSV to RGB - the conversion function handles HDR values correctly */
        vCL.m_vF32_04_1 = tgCM_CL_F32_Convert_HSV_To_RGB(uHSV.m_vF32_04_1);
        pavColours[uiIndex] = vCL.m_vF32_04_1;
    }
}

/*# defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
#endif

/*# defined(TgBUILD_FEATURE__GRAPHICS) */
#endif
