/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Kernel - System [GPU] [Context] [SWAP].c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.20 | »GUID« DE461472-5528-4A5B-A7F4-09CCAD73387B */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgKN_GPU__SwapChain__Get_Target_Buffers ---------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU__SwapChain__Get_Target_Buffers( STg2_KN_GPU_Render_Buffer_PC psRTBuffer, STg2_KN_GPU_Render_Buffer_PC psDSBuffer, TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP )
{
    STg2_KN_GPU_CXT_SWAP_P              psCXT_SWAP = g_asKN_GPU_CXT_SWAP + tiCXT_SWAP.m_uiI;

    TgPARAM_CHECK_INDEX( tiCXT_SWAP.m_uiI, g_asKN_GPU_CXT_SWAP );
    TgERROR(tgKN_GPU_CXT_SWAP_ID_Is_Equal( &psCXT_SWAP->m_tiCXT_SWAP_S, tiCXT_SWAP ));

    if (nullptr != psRTBuffer)
    {
        *psRTBuffer = psCXT_SWAP->m_sMode.m_sBuffer;
    };

    if (nullptr != psDSBuffer)
    {
        psDSBuffer->m_uiWidth = psCXT_SWAP->m_sMode.m_sBuffer.m_uiWidth;
        psDSBuffer->m_uiHeight = psCXT_SWAP->m_sMode.m_sBuffer.m_uiHeight;
        psDSBuffer->m_enFormat = psCXT_SWAP->m_enFormat_DS;
    };
}




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
    sCXT_SWAP.ps->m_uiAdapter_Index = psCXT_EXEC->m_uiAdapter_Index;

    /* Content Configuration */

    sCXT_SWAP.ps->m_fMax_Mastering_Nits = psSelect->m_sOutput[uiOutput_Index].m_fMax_Mastering_Nits;
    sCXT_SWAP.ps->m_fMin_Mastering_Nits = psSelect->m_sOutput[uiOutput_Index].m_fMin_Mastering_Nits;
    sCXT_SWAP.ps->m_fMax_Content_Light_Level = psSelect->m_sOutput[uiOutput_Index].m_fMax_Content_Light_Level;
    sCXT_SWAP.ps->m_fMax_Frame_Average_Light_Level = psSelect->m_sOutput[uiOutput_Index].m_fMax_Frame_Average_Light_Level;

    /* Scanout Configuration */

    sCXT_SWAP.ps->m_fSDR_In_HDR_Nits_Level = 80.0F;

    /* Configuration */

    sCXT_SWAP.ps->m_uiScanout_Adapter_Enumeration_Index = KTgMAX_U32;
    sCXT_SWAP.ps->m_uiScanout_Output_Enumeration_Index = KTgMAX_U32;
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

    if (TgFAILED(tgKN_GPU_EXT__SwapChain__Init( tiCXT_SWAP, false )))
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
TgVOID tgKN_GPU__SwapChain__Present_Print_Debug_Stats( UTg2_KN_GPU_CMD_C uCMD, TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP )
{
    STg2_KN_GPU_CXT_SWAP_PC             psCXT_SWAP = g_asKN_GPU_CXT_SWAP + tiCXT_SWAP.m_uiI;
    STg2_KN_GPU_CXT_EXEC_PC             psCXT_EXEC = g_asKN_GPU_CXT_EXEC + psCXT_SWAP->m_tiCXT_EXEC.m_uiI;

    STg2_KN_GPU_HLSL_Output_DESC        sOutput_DESC;
    STg2_KN_GPU_Render_Buffer           sRTBuffer;
    STg2_KN_GPU_Render_Buffer           sDSBuffer;
    TgCHAR_U8                           uszBuffer[256];
    STg2_KN_GPU_OUTPUT_DEBUG_STRING     sOutput_Debug_String_0;

    sOutput_DESC.m_fPerceptual_Exponent = 2.2F;
    sOutput_DESC.m_fSDR_In_HDR_Nits_Level = psCXT_SWAP->m_fSDR_In_HDR_Nits_Level;
    sOutput_DESC.m_enColour_Space = psCXT_SWAP->m_enColour_Space;
    sOutput_DESC.m_bHDR_Enabled = psCXT_SWAP->m_bHDR_Enabled;
    sOutput_DESC.m_fMin_Luminance = psCXT_SWAP->m_fMin_Luminance;
    sOutput_DESC.m_fMax_Luminance = psCXT_SWAP->m_fMax_Luminance;
    sOutput_DESC.m_fMax_Full_Frame_Luminance = psCXT_SWAP->m_fMax_Full_Frame_Luminance;

    sRTBuffer.m_uiWidth = psCXT_SWAP->m_sMode.m_sBuffer.m_uiWidth;
    sRTBuffer.m_uiHeight = psCXT_SWAP->m_sMode.m_sBuffer.m_uiHeight;
    sRTBuffer.m_enFormat = psCXT_SWAP->m_sMode.m_sBuffer.m_enFormat;

    sDSBuffer.m_uiWidth = psCXT_SWAP->m_sMode.m_sBuffer.m_uiWidth;
    sDSBuffer.m_uiHeight = psCXT_SWAP->m_sMode.m_sBuffer.m_uiHeight;
    sDSBuffer.m_enFormat = psCXT_SWAP->m_enFormat_DS;

    if (sOutput_DESC.m_bHDR_Enabled)
    {
        tgUSZ_Copy( uszBuffer, 256, u8"HDR", KTgMAX_RSIZE );
    }
    else
    {
        tgUSZ_Copy( uszBuffer, 256, u8"SDR", KTgMAX_RSIZE );
    };

    TgWARN_DISABLE_PUSH(4061 4062,switch-enum)
    switch (sRTBuffer.m_enFormat) {
    case ETgKN_GPU_EXT_FORMAT_R8G8B8A8_UNORM: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_R8G8B8A8_UNORM_SRGB: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_B8G8R8A8_UNORM: TgATTRIBUTE_FALLTHROUGH
    case ETgKN_GPU_EXT_FORMAT_B8G8R8A8_UNORM_SRGB:
        tgUSZ_Append( uszBuffer, 256, u8"/8", KTgMAX_RSIZE );
        break;
    case ETgKN_GPU_EXT_FORMAT_R10G10B10A2_UNORM:
        tgUSZ_Append( uszBuffer, 256, u8"/10", KTgMAX_RSIZE );
        break;
    case ETgKN_GPU_EXT_FORMAT_R16G16B16A16_FLOAT:
        tgUSZ_Append( uszBuffer, 256, u8"/16", KTgMAX_RSIZE );
        break;
    default:
        break;
    };
    TgWARN_DISABLE_POP()

    tgMM_Set_U08_0x00( &sOutput_Debug_String_0, sizeof( sOutput_Debug_String_0 ) );

    sOutput_Debug_String_0.m_sOutput_DESC = sOutput_DESC;
    sOutput_Debug_String_0.m_sRTBuffer = sRTBuffer;
    sOutput_Debug_String_0.m_sDSBuffer = sDSBuffer;
    sOutput_Debug_String_0.m_enFont = ETgKN_GPU_DOS_FONT_ROM_MARCIO;
    sOutput_Debug_String_0.m_auszText[0] = uszBuffer;
    sOutput_Debug_String_0.m_nuiText = 1;
    sOutput_Debug_String_0.m_vText_Box_V.x = -1.0F + (10.0F / (float)sRTBuffer.m_uiWidth);
    sOutput_Debug_String_0.m_vText_Box_V.y = 1.0F - (10.0F / (float)sRTBuffer.m_uiHeight);
    sOutput_Debug_String_0.m_vText_Box_V.z = 1.0F - (10.0F / (float)sRTBuffer.m_uiWidth);
    sOutput_Debug_String_0.m_vText_Box_V.w =-1.0F + (10.0F / (float)sRTBuffer.m_uiHeight);
    sOutput_Debug_String_0.m_vText_Colour.r = 0.0F;
    sOutput_Debug_String_0.m_vText_Colour.g = 1.0F;
    sOutput_Debug_String_0.m_vText_Colour.b = 0.0F;
    sOutput_Debug_String_0.m_vText_Colour.a = 1.0F;
    sOutput_Debug_String_0.m_bRight_Aligned = true;

    tgUSZ_AppendF( uszBuffer, 256, u8", GPU Adapter %d, Node %d", psCXT_EXEC->m_uiAdapter_Index, psCXT_EXEC->m_uiNodeMask );
    tgUSZ_AppendF( uszBuffer, 256, u8"\nGPU Scanout Adapter %d, Scanout Output %d", psCXT_SWAP->m_uiScanout_Adapter_Enumeration_Index,
                   psCXT_SWAP->m_uiScanout_Output_Enumeration_Index );

    tgKN_GPU__CMD__Render_Debug_Text_Box( uCMD, &sOutput_Debug_String_0 );

    //tgUSZ_AppendF( uszBuffer, 256, u8", GPU Adapter %d, Node %d\nFrame # %5d\nTotal Frame Time: % 9.2fms\nFrame Time: % 4.2fms\nFrame Time for All Windows: % 5.2fms",
    //               uJob_Data.ps->m_tiCXT_EXEC.m_uiI, iEnumeration_Adapter_Node, s_uiFrame_Counter, (double)uJob_Data.ps->m_fElapsed_Time,
    //               (double)s_shWnd[uJob_Data.ps->m_uiWindow].m_fFrame_Elapsed_Time, (double)s_fTotal_Elapse_Frame_Time );

    //fFrame_Start_Time = tgTM_Query_Time();
    //s_shWnd[uJob_Data.ps->m_uiWindow].m_fFrame_Elapsed_Time = tgTM_Query_Time() - fFrame_Start_Time;


    tgKN_GPU__CMD__Render_Console_Text( uCMD, &sOutput_DESC, sRTBuffer, sDSBuffer );
}
/*# defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
#endif
