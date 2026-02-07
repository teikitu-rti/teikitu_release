/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Kernel [GPU] - System [Context] [SWAP].c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.20 | »GUID« DE461472-5528-4A5B-A7F4-09CCAD73387B */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgKN_GPU__SwapChain__Init ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU__SwapChain__Init( STg2_KN_GPU_Init_Result_PCU psResult, STg2_KN_GPU_Select_CPCU psSelect, TgRSIZE_C uiOutput_Index, TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC )
{
    TgRSIZE                             uiOutput_Index_In_Host_Context;
    STg2_KN_GPU_CXT_EXEC_P              psCXT_EXEC;
    TgKN_GPU_CXT_SWAP_ID                tiCXT_SWAP;
    union
    {
        STg2_KN_GPU_CXT_SWAP_P              ps;
        STg2_UT_ST__ST_Node_P               pNode;
    }                                   sCXT_SWAP;

    /* Find an empty slot in the host context for the device. */
    for (uiOutput_Index_In_Host_Context = 0; uiOutput_Index_In_Host_Context < KTgKN_GPU_MAX_SWAP_CONTEXT; ++uiOutput_Index_In_Host_Context)
    {
        if (g_sKN_GPU_CXT_HOST.m_atiCXT_SWAP[uiOutput_Index_In_Host_Context].m_uiKI == KTgKN_GPU_CXT_SWAP_ID__INVALID.m_uiKI)
        {
            break;
        };
    };

    /* Theoretically impossible, however range checking is still good practice. */
    if (uiOutput_Index_In_Host_Context >= KTgKN_GPU_MAX_SWAP_CONTEXT)
    {
        return (KTgE_FAIL);
    };

    /* Take a context from the free list. */
    sCXT_SWAP.pNode = tgCM_UT_LF__ST__Pop( &g_sKN_GPU_CXT_SWAP_Free_Stack.m_sStack );
    if (nullptr == sCXT_SWAP.pNode)
    {
        return (KTgE_FAIL);
    };

    TgPARAM_CHECK_INDEX( tiCXT_EXEC.m_uiI, g_asKN_GPU_CXT_EXEC );
    psCXT_EXEC = g_asKN_GPU_CXT_EXEC + tiCXT_EXEC.m_uiI;
    TgERROR(tgKN_GPU_CXT_EXEC_ID_Is_Equal( &psCXT_EXEC->m_tiCXT_EXEC_S, tiCXT_EXEC ));

    /* Initialize the context. */
    tgMM_Set_U08_0x00( sCXT_SWAP.pNode, sizeof( STg2_KN_GPU_CXT_SWAP ) );
    tgKN_GPU_CXT_SWAP_ID_Init( &sCXT_SWAP.ps->m_tiCXT_SWAP_S, (TgUINT_E32)(sCXT_SWAP.ps - g_asKN_GPU_CXT_SWAP) );
    tgKN_GPU_CXT_SWAP_ID_Load( &tiCXT_SWAP, &sCXT_SWAP.ps->m_tiCXT_SWAP_S );

    sCXT_SWAP.ps->m_tiCXT_EXEC = tiCXT_EXEC;
    sCXT_SWAP.ps->m_uiOS_ID = psSelect->m_sOutput[uiOutput_Index].m_uiOS_ID;
    sCXT_SWAP.ps->m_idxCXT_HOST_Physical_Device = psCXT_EXEC->m_idxCXT_HOST_Physical_Device;

    /* Content Configuration */

    sCXT_SWAP.ps->m_fMax_Mastering_Nits = psSelect->m_sOutput[uiOutput_Index].m_fMax_Mastering_Nits;
    sCXT_SWAP.ps->m_fMin_Mastering_Nits = psSelect->m_sOutput[uiOutput_Index].m_fMin_Mastering_Nits;
    sCXT_SWAP.ps->m_fMax_Content_Light_Level = psSelect->m_sOutput[uiOutput_Index].m_fMax_Content_Light_Level;
    sCXT_SWAP.ps->m_fMax_Frame_Average_Light_Level = psSelect->m_sOutput[uiOutput_Index].m_fMax_Frame_Average_Light_Level;

    /* Configuration */

    sCXT_SWAP.ps->m_sMode = psSelect->m_sOutput[uiOutput_Index].m_sMode;
    sCXT_SWAP.ps->m_uiMSAA_Sample = psSelect->m_sOutput[uiOutput_Index].m_uiMSAA_Sample;
    sCXT_SWAP.ps->m_enFormat_RT = psSelect->m_sOutput[uiOutput_Index].m_sMode.m_sBuffer.m_enFormat;
    sCXT_SWAP.ps->m_enFormat_DS = psSelect->m_sOutput[uiOutput_Index].m_enFormat_DS;
    sCXT_SWAP.ps->m_nuiSwap_Buffers = psSelect->m_sOutput[uiOutput_Index].m_uiOutput_Config.m_nuiSwap_Buffers;
    sCXT_SWAP.ps->m_uiStereo = psSelect->m_sOutput[uiOutput_Index].m_uiOutput_Config.m_uiStereo;
    sCXT_SWAP.ps->m_uiVSync = psSelect->m_sOutput[uiOutput_Index].m_uiOutput_Config.m_uiVSync;
    sCXT_SWAP.ps->m_bHDR_Request = psSelect->m_sOutput[uiOutput_Index].m_uiOutput_Config.m_bHDR_Request;

    /* Run-time Configuration */

    sCXT_SWAP.ps->m_sViewport.m_iPosX = 0;
    sCXT_SWAP.ps->m_sViewport.m_iPosY = 0;
    sCXT_SWAP.ps->m_sViewport.m_iWidth = (TgSINT_E32)tgCM_MIN_U32(sCXT_SWAP.ps->m_sMode.m_sBuffer.m_uiWidth, (TgUINT_E32)KTgMAX_S32);
    sCXT_SWAP.ps->m_sViewport.m_iHeight = (TgSINT_E32)tgCM_MIN_U32(sCXT_SWAP.ps->m_sMode.m_sBuffer.m_uiHeight, (TgUINT_E32)KTgMAX_S32);
    sCXT_SWAP.ps->m_sViewport.m_fMinZ = 0.0F;
    sCXT_SWAP.ps->m_sViewport.m_fMaxZ = 1.0F;

    sCXT_SWAP.ps->m_sScissor_Rect.m_iLeft = 0;
    sCXT_SWAP.ps->m_sScissor_Rect.m_iTop = 0;
    sCXT_SWAP.ps->m_sScissor_Rect.m_iRight = (TgSINT_E32)tgCM_MIN_U32(sCXT_SWAP.ps->m_sMode.m_sBuffer.m_uiWidth, (TgUINT_E32)KTgMAX_S32);
    sCXT_SWAP.ps->m_sScissor_Rect.m_iBottom = (TgSINT_E32)tgCM_MIN_U32(sCXT_SWAP.ps->m_sMode.m_sBuffer.m_uiHeight, (TgUINT_E32)KTgMAX_S32);

    if (TgFAILED(tgKN_GPU_EXT__SwapChain__Init( tiCXT_SWAP, false, false )))
    {
        tgMM_Set_U08_0x00( sCXT_SWAP.pNode, sizeof( STg2_KN_GPU_CXT_SWAP ) );
        tgKN_GPU_CXT_SWAP_ID_Invalidate( &sCXT_SWAP.ps->m_tiCXT_SWAP_S );
        tgCM_UT_LF__ST__Push( &g_sKN_GPU_CXT_SWAP_Free_Stack.m_sStack, sCXT_SWAP.pNode );
        return (KTgE_FAIL);
    };

    g_sKN_GPU_CXT_HOST.m_atiCXT_SWAP[uiOutput_Index_In_Host_Context] = tiCXT_SWAP;

    psResult->m_sSWAP[psResult->m_nuiSWAP].m_tiCXT_SWAP = tiCXT_SWAP;
    psResult->m_sSWAP[psResult->m_nuiSWAP].m_tiCXT_EXEC = tiCXT_EXEC;
    psResult->m_sSWAP[psResult->m_nuiSWAP].m_uiNodeMask = psCXT_EXEC->m_uiNodeMask;
    psResult->m_sSWAP[psResult->m_nuiSWAP].m_uiOS_ID = sCXT_SWAP.ps->m_uiOS_ID;
    ++psResult->m_nuiSWAP;

#if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)
    if (TgFAILED( tgKN_GPU__Swap__Init_Debug( tiCXT_SWAP ) ))
    {
        return (KTgE_FAIL);
    }
/*# defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
#endif

    return (KTgS_OK);
}


/* ---- tgKN_GPU__SwapChain__Free --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU__SwapChain__Free( TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP )
{
    TgRSIZE                             uiIndex;
    union
    {
        STg2_KN_GPU_CXT_SWAP_P              ps;
        STg2_UT_ST__ST_Node_P               pNode;
    }                                   sCXT_SWAP;

    TgPARAM_CHECK_INDEX( tiCXT_SWAP.m_uiI, g_asKN_GPU_CXT_SWAP );
    sCXT_SWAP.ps = g_asKN_GPU_CXT_SWAP + tiCXT_SWAP.m_uiI;
    TgERROR(tgKN_GPU_CXT_SWAP_ID_Is_Equal( &sCXT_SWAP.ps->m_tiCXT_SWAP_S, tiCXT_SWAP ));

#if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)
    tgKN_GPU__Swap__Free_Debug( tiCXT_SWAP );
/*# defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
#endif

    tgKN_GPU_EXT__SwapChain__Free( tiCXT_SWAP );

    tgMM_Set_U08_0x00( sCXT_SWAP.pNode, sizeof( STg2_KN_GPU_CXT_SWAP ) );
    tgKN_GPU_CXT_SWAP_ID_Invalidate( &sCXT_SWAP.ps->m_tiCXT_SWAP_S );
    tgCM_UT_LF__ST__Push( &g_sKN_GPU_CXT_SWAP_Free_Stack.m_sStack, sCXT_SWAP.pNode );

    for (uiIndex = 0; uiIndex < KTgKN_GPU_MAX_SWAP_CONTEXT; ++uiIndex)
    {
        if (g_sKN_GPU_CXT_HOST.m_atiCXT_SWAP[uiIndex].m_uiKI == tiCXT_SWAP.m_uiKI)
        {
            g_sKN_GPU_CXT_HOST.m_atiCXT_SWAP[uiIndex] = KTgKN_GPU_CXT_SWAP_ID__INVALID;
            break;
        };
    };
    TgERROR(uiIndex < KTgKN_GPU_MAX_SWAP_CONTEXT);
}


/* ---- tgKN_GPU__SwapChain__Present_Print_Debug_Stats --------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)
TgVOID tgKN_GPU__SwapChain__Present_Print_Debug_Stats( STg2_KN_GPU_CMD_PC psCMD, TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP )
{
    TgRSIZE                             uiEXEC = (psCMD->m_tiCXT_WORK.m_uiI >> 16) & 0xFFFF;
    STg2_KN_GPU_CXT_EXEC_PC             psCXT_EXEC = g_asKN_GPU_CXT_EXEC + uiEXEC;
    STg2_KN_GPU_CXT_SWAP_PC             psCXT_SWAP = g_asKN_GPU_CXT_SWAP + tiCXT_SWAP.m_uiI;

    TgFLOAT32_C                         fRT_Width = (float)psCMD->m_uiRender_Target_Width;

    TgCHAR_U8                           uszBuffer[256];
    STg2_KN_GPU_DBG_Text_CI             sText_CI;
    TgCHAR_U8_CP                        puszText;

    if (psCXT_SWAP->m_bHDR_Enabled)
    {
        tgUSZ_Copy( uszBuffer, 256, u8"HDR", KTgMAX_RSIZE );
    }
    else
    {
        tgUSZ_Copy( uszBuffer, 256, u8"SDR", KTgMAX_RSIZE );
    };

    TgWARN_DISABLE_PUSH(4061 4062,switch-enum)
    switch (psCXT_SWAP->m_sMode.m_sBuffer.m_enFormat) {
    case ETgKN_GPU_EXT_FORMAT_R8G8B8A8_UNORM: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_R8G8B8A8_SRGB: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_B8G8R8A8_UNORM: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_B8G8R8A8_SRGB:
        tgUSZ_Append( uszBuffer, 256, u8"/8", KTgMAX_RSIZE );
        break;
    case ETgKN_GPU_EXT_FORMAT_A2B10G10R10_UNORM_PACK32:
        tgUSZ_Append( uszBuffer, 256, u8"/10", KTgMAX_RSIZE );
        break;
    case ETgKN_GPU_EXT_FORMAT_R16G16B16A16_SFLOAT:
        tgUSZ_Append( uszBuffer, 256, u8"/16", KTgMAX_RSIZE );
        break;
    default:
        break;
    };
    TgWARN_DISABLE_POP()

    tgMM_Set_U08_0x00( &sText_CI, sizeof( sText_CI ) );
    puszText = uszBuffer;

    sText_CI.m_enFont = ETgKN_GPU_DOS_FONT_ROM_MARCIO;
    sText_CI.m_vText_Box_V.x =-1.0F + (10.0F / fRT_Width);
    sText_CI.m_vText_Box_V.y =-1.0F + (10.0F / fRT_Width);
    sText_CI.m_vText_Box_V.z = 1.0F - (10.0F / fRT_Width);
    sText_CI.m_vText_Box_V.w = 1.0F - (10.0F / fRT_Width);
    sText_CI.m_vText_Colour.r = 0.0F;
    sText_CI.m_vText_Colour.g = 1.0F;
    sText_CI.m_vText_Colour.b = 0.0F;
    sText_CI.m_vText_Colour.a = 1.0F;
    sText_CI.m_bRight_Aligned = true;
    sText_CI.m_puszText = &puszText;
    sText_CI.m_nuiText = 1;

    tgUSZ_AppendF( uszBuffer, 256, u8", GPU Physical_Device %d, Swap %d", psCXT_EXEC->m_idxCXT_HOST_Physical_Device, tiCXT_SWAP.m_uiI);

    tgKN_GPU__CMD__Render_Debug_Text_Box( psCMD, &sText_CI );
}
/*# defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
#endif
