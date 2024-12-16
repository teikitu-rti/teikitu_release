/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Kernel - Debug [GPU] [Console].c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/* == Kernel ===================================================================================================================================================================== */
#if TgCOMPILE__RENDER_DEBUG_OUTPUT && TgCOMPILE__CONSOLE

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_GPU_DXGI_Output__Adapter -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_Set_CN_Render_Text( KTgCN_CHANEL_SEVERITY_C enCN_Channel, TgCHAR_U8_PP ppuszLine, TgRSIZE nuiLine, TgRSIZE nuiLineMax )
{
    TgCHAR_U8_P                         uszText_Render_Buffer;
    TgRSIZE                             nbyText_Render_Buffer;
    TgRSIZE                             uiLine;

    /* We only support rendering of the on-screen log and the debug console. */
    if (KTgCN_CHANEL_LOG_SCREEN == enCN_Channel)
    {
        uszText_Render_Buffer = g_uszKN_GPU_LOG_Render_Buffer;
        nbyText_Render_Buffer = sizeof( g_uszKN_GPU_LOG_Render_Buffer );
        g_nuiKN_GPU_LOG_Line = nuiLineMax;
    }
    else if (KTgCN_CHANEL_CONSOLE == enCN_Channel)
    {
        uszText_Render_Buffer = g_uszKN_GPU_CON_Render_Buffer;
        nbyText_Render_Buffer = sizeof( g_uszKN_GPU_CON_Render_Buffer );
        g_nuiKN_GPU_CON_Line = nuiLineMax;
    }
    else
    {
        return;
    }

    uszText_Render_Buffer[0] = 0;
    for (uiLine = 0; uiLine < nuiLine; ++uiLine)
    {
        tgUSZ_AppendF( uszText_Render_Buffer, nbyText_Render_Buffer, u8"%s\n", ppuszLine[uiLine], KTgMAX_RSIZE );
    }
}


/* ---- tgKN_GPU__CMD__Render_Console_Text --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU__CMD__Render_Console_Text( UTg2_KN_GPU_CMD_C uCMD, STg2_KN_GPU_HLSL_Output_DESC_CPC psOutput_DESC, STg2_KN_GPU_Render_Buffer sRTBuffer,
                                           STg2_KN_GPU_Render_Buffer sDSBuffer )
{
    STg2_KN_GPU_OUTPUT_DEBUG_STRING     sOutput_CN_OnScreen_Log;
    STg2_KN_GPU_OUTPUT_DEBUG_STRING     sOutput_CN_Debug_Console;
    STg2_KN_GPU_FONT_TX                 sFont_TX;

    tgKN_GPU_Query_DOS_Font_ROM_TX( &sFont_TX, ETgKN_GPU_DOS_FONT_ROM_MARCIO );

    tgMM_Set_U08_0x00( &sOutput_CN_OnScreen_Log, sizeof( sOutput_CN_OnScreen_Log ) );

    sOutput_CN_OnScreen_Log.m_sOutput_DESC = *psOutput_DESC;
    sOutput_CN_OnScreen_Log.m_sRTBuffer = sRTBuffer;
    sOutput_CN_OnScreen_Log.m_sDSBuffer = sDSBuffer;
    sOutput_CN_OnScreen_Log.m_enFont = ETgKN_GPU_DOS_FONT_ROM_MARCIO;
    sOutput_CN_OnScreen_Log.m_auszText[0] = g_uszKN_GPU_LOG_Render_Buffer;
    sOutput_CN_OnScreen_Log.m_nuiText = 1;
    sOutput_CN_OnScreen_Log.m_vText_Box_V.x =-1.0F + (sFont_TX.m_fTX_Cell_X / (float)sRTBuffer.m_uiWidth);
    sOutput_CN_OnScreen_Log.m_vText_Box_V.y = 1.0F - ((sFont_TX.m_fTX_Cell_Y*16.0F) / (float)sRTBuffer.m_uiHeight);
    sOutput_CN_OnScreen_Log.m_vText_Box_V.z = 1.0F - (sFont_TX.m_fTX_Cell_X / (float)sRTBuffer.m_uiWidth);
    if (0 == g_uszKN_GPU_CON_Render_Buffer[0])
    {
        sOutput_CN_OnScreen_Log.m_vText_Box_V.w =-1.0F + (sFont_TX.m_fTX_Cell_Y / (float)sRTBuffer.m_uiHeight);
    }
    else
    {
        sOutput_CN_OnScreen_Log.m_vText_Box_V.w = -1.0F + ((2.0F * (TgFLOAT32)g_nuiKN_GPU_CON_Line * sFont_TX.m_fTX_Cell_Y)/ (float)sRTBuffer.m_uiHeight);
    }
    sOutput_CN_OnScreen_Log.m_vText_Colour.r = 1.0F;
    sOutput_CN_OnScreen_Log.m_vText_Colour.g = 0.0F;
    sOutput_CN_OnScreen_Log.m_vText_Colour.b = 0.0F;
    sOutput_CN_OnScreen_Log.m_vText_Colour.a = 1.0F;

    tgKN_GPU__CMD__Render_Debug_Text_Box( uCMD, &sOutput_CN_OnScreen_Log );

    tgMM_Set_U08_0x00( &sOutput_CN_Debug_Console, sizeof( sOutput_CN_Debug_Console ) );

    sOutput_CN_Debug_Console.m_sOutput_DESC = *psOutput_DESC;
    sOutput_CN_Debug_Console.m_sRTBuffer = sRTBuffer;
    sOutput_CN_Debug_Console.m_sDSBuffer = sDSBuffer;
    sOutput_CN_Debug_Console.m_enFont = ETgKN_GPU_DOS_FONT_ROM_MARCIO;
    sOutput_CN_Debug_Console.m_bLine_Change_Is_Positive = true;
    sOutput_CN_Debug_Console.m_bDraw_Background = true;
    sOutput_CN_Debug_Console.m_bDraw_First_Line = true;
    sOutput_CN_Debug_Console.m_auszText[0] = g_uszKN_GPU_CON_Render_Buffer;
    sOutput_CN_Debug_Console.m_nuiText = 1;
    sOutput_CN_Debug_Console.m_vText_Box_V.x = -1.0F + (sFont_TX.m_fTX_Cell_X / (float)sRTBuffer.m_uiWidth);
    sOutput_CN_Debug_Console.m_vText_Box_V.y = -1.0F + (((TgFLOAT32)(g_nuiKN_GPU_CON_Line*2) * sFont_TX.m_fTX_Cell_Y)/ (float)sRTBuffer.m_uiHeight);
    sOutput_CN_Debug_Console.m_vText_Box_V.z =  1.0F - (sFont_TX.m_fTX_Cell_X / (float)sRTBuffer.m_uiWidth);
    sOutput_CN_Debug_Console.m_vText_Box_V.w = -1.0F + (sFont_TX.m_fTX_Cell_Y / (float)sRTBuffer.m_uiHeight);
    sOutput_CN_Debug_Console.m_vText_Colour.r = 0.0F;
    sOutput_CN_Debug_Console.m_vText_Colour.g = 0.0F;
    sOutput_CN_Debug_Console.m_vText_Colour.b = 0.0F;
    sOutput_CN_Debug_Console.m_vText_Colour.a = 1.0F;
    sOutput_CN_Debug_Console.m_vBackground_Colour.r = 1.0F;
    sOutput_CN_Debug_Console.m_vBackground_Colour.g = 1.0F;
    sOutput_CN_Debug_Console.m_vBackground_Colour.b = 1.0F;
    sOutput_CN_Debug_Console.m_vBackground_Colour.a = 0.7F;
    sOutput_CN_Debug_Console.m_vBackground_First_Line.r = 1.0F;
    sOutput_CN_Debug_Console.m_vBackground_First_Line.g = 1.0F;
    sOutput_CN_Debug_Console.m_vBackground_First_Line.b = 1.0F;
    sOutput_CN_Debug_Console.m_vBackground_First_Line.a = 1.0F;

    tgKN_GPU__CMD__Render_Debug_Text_Box( uCMD, &sOutput_CN_Debug_Console );
}

/*# TgCOMPILE__RENDER_DEBUG_OUTPUT && TgCOMPILE__CONSOLE */
#endif
