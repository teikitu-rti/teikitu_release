/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (DX12) Kernel - Debug [GPU] [Text].c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/* == Kernel ===================================================================================================================================================================== */
#if TgCOMPILE__RENDER_DEBUG_OUTPUT

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Types and Functions                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgTYPE_STRUCT( TgKN_GPU_DBG_Geom_For_Tessellation )
{
    TgKN_GPU_DBG_PM_Generate_P                  m_psGenerate;

    /* Used during the tessellation process and then cleared out prior to returning to the calling function. */

    TgRSIZE                                     m_nuiEdge;
    TgRSIZE                                     m_nuiMax_Edge;
    TgUINT_E16_P                                m_puiStart;
    TgUINT_E16_P                                m_puiEnd;
    TgUINT_E16_P                                m_puiMid;
    TgUINT_E16_P                                m_puiIndex_Orig;
    TgRSIZE                                     m_nuiIndex_Orig;
};


static TgVOID
tgKN_GPU__CMD__Render_Debug_Text_Box_Right_Align(
    STg2_KN_GPU_HLSL_CB_Debug_Text_PC psText_Constant_Buffer, TgRSIZE_C uiBuffer_Index, TgFLOAT32_C fText_Start_Z );

/** @brief Render a debug line in 3D. This will buffer up the render calls until either a new render target is set (which will flush the buffer), or it is filled.
    @param [in] ARG0 Pointer to the a Command List data structure (acquired from the Work Context).
    @param [in] ARG1 Vector starting point.
    @param [in] ARG2 Vector starting point colour in G10 P709.
    @param [in] ARG3 Vector terminal point.
    @param [in] ARG4 Vector terminal point colour in G10 P709. */
static TgVOID
tgKN_GPU__CMD__Render_Debug_Line_Internal(
    UTg2_KN_GPU_CMD_C ARG0, TgVEC_F32_04_1_C ARG1, TgVEC_F32_04_1_C ARG2, TgVEC_F32_04_1_C ARG3, TgVEC_F32_04_1_C ARG4, STg2_KN_GPU_HLSL_CB_Debug_Line_CPC psDBG );

static TgVOID
tgKN_GPU_DBG_Tessellate(
    TgKN_GPU_DBG_PM_Generate_PCU ARG0 );

static TgVOID
tgKN_GPU_DBG_Tessellate_Capsule(
    TgRSIZE_PCU OUT0, TgKN_GPU_DBG_PM_Generate_PCU ARG1 );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_GPU__CMD__Render_Debug_Text_Box ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU__CMD__Render_Debug_Text_Box( UTg2_KN_GPU_CMD_C uCMD, STg2_KN_GPU_OUTPUT_DEBUG_STRING_CPC psDBG )
{
    STg2_KN_GPU_FONT_TX                 sFont_TX;
    STg2_KN_GPU_HLSL_CB_Debug_Text      sText_Constant_Buffer;
    TgRSIZE                             uiLine_Index;
    TgRSIZE                             uiText_Index;
    TgRSIZE                             uiBuffer_Index;
    TgRSIZE                             uiTextX,uiTextY;
    TgBOOL                              bEnd_Process;
    TgFLOAT32                           fText_Start_X;
    TgFLOAT32                           fText_Start_Y, fLimitT;
    TgFLOAT32                           fText_Start_Z;
    TgFLOAT32                           fText_Start_W, fLimitB;

    TgPARAM_CHECK( nullptr != uCMD.ps );
    TgPARAM_CHECK( nullptr != psDBG );

    tgKN_GPU_Query_DOS_Font_ROM_TX( &sFont_TX, psDBG->m_enFont );

    sText_Constant_Buffer.m_sDESC = psDBG->m_sOutput_DESC;
    sText_Constant_Buffer.m_uiSelect_Default_Texture_Index = 11u + (TgUINT_E32)psDBG->m_enFont;
    sText_Constant_Buffer.m_vStart_Position_V.x = psDBG->m_vText_Box_V.x;
    sText_Constant_Buffer.m_vStart_Position_V.y = psDBG->m_vText_Box_V.y;
    sText_Constant_Buffer.m_vFont_Glyph_Scale_S.x = sFont_TX.m_fFntX * 2.0F / (float)psDBG->m_sRTBuffer.m_uiWidth;
    sText_Constant_Buffer.m_vFont_Glyph_Scale_S.y = sFont_TX.m_fFntY * 2.0F / (float)psDBG->m_sRTBuffer.m_uiHeight;
    sText_Constant_Buffer.m_vFont_Glyph_Scale_S.z = (float)psDBG->m_sRTBuffer.m_uiWidth;
    sText_Constant_Buffer.m_vFont_Glyph_Scale_S.w = (float)psDBG->m_sRTBuffer.m_uiHeight;
    sText_Constant_Buffer.m_vFont_Glyph_Scale_UV.x = sFont_TX.m_fFntX / sFont_TX.m_fTX_X;
    sText_Constant_Buffer.m_vFont_Glyph_Scale_UV.y = sFont_TX.m_fFntY / sFont_TX.m_fTX_Y;
    sText_Constant_Buffer.m_vFont_Glyph_Scale_UV.z = sFont_TX.m_fTX_Cell_X / sFont_TX.m_fTX_X;
    sText_Constant_Buffer.m_vFont_Glyph_Scale_UV.w = sFont_TX.m_fTX_Cell_Y / sFont_TX.m_fTX_Y;
    sText_Constant_Buffer.m_vText_Colour = psDBG->m_vText_Colour;

    /* Validate that the box can contain at least one character */
    if (psDBG->m_vText_Box_V.z - psDBG->m_vText_Box_V.x <= sText_Constant_Buffer.m_vFont_Glyph_Scale_S.x)
    {
        return;
    }

    /* Validate that the box can contain at least one line */
    if (psDBG->m_vText_Box_V.y - psDBG->m_vText_Box_V.w <= sText_Constant_Buffer.m_vFont_Glyph_Scale_S.y)
    {
        return;
    }

    /* Test to see if the text would automatically render off screen. */
    if (psDBG->m_vText_Box_V.z <= -1.0F || psDBG->m_vText_Box_V.x >= 1.0F || psDBG->m_vText_Box_V.y <= -1.0F || psDBG->m_vText_Box_V.w >= 1.0F)
    {
        return;
    }

    /* Start converting the text stream into positions and UVs for rendering. The system attempts to do basic formatting like word wrapping (if indicated), and new lines. */

    uiBuffer_Index = 0;
    uiText_Index = 0;
    uiTextX = 0;
    uiTextY = 0;
    bEnd_Process = false;

    fText_Start_X = psDBG->m_vText_Box_V.x + 2.0F / (float)psDBG->m_sRTBuffer.m_uiWidth;
    fText_Start_Y = psDBG->m_vText_Box_V.y - 2.0F / (float)psDBG->m_sRTBuffer.m_uiHeight;
    fText_Start_Z = psDBG->m_vText_Box_V.z - 2.0F / (float)psDBG->m_sRTBuffer.m_uiWidth;
    fText_Start_W = psDBG->m_vText_Box_V.w + 2.0F / (float)psDBG->m_sRTBuffer.m_uiHeight;
    fLimitT = tgCM_MIN_F32( fText_Start_Y,  1.0F );
    fLimitB = tgCM_MAX_F32( fText_Start_W, -1.0F );

    if (psDBG->m_bDraw_Background || psDBG->m_bDraw_First_Line)
    {
        tgKN_GPU_EXT__CMD__Set_State_From_Default( uCMD, ETgKN_GPU_DEFAULT_PSO_DEBUG_UI, psDBG->m_sRTBuffer.m_enFormat, psDBG->m_sDSBuffer.m_enFormat );
    }

    if (psDBG->m_bDraw_Background)
    {
        STg2_KN_GPU_HLSL_CB_Debug_UI        sUI_Constant_Buffer;

        sUI_Constant_Buffer.m_sDESC = psDBG->m_sOutput_DESC;
        sUI_Constant_Buffer.m_vRect_UI.x = psDBG->m_vText_Box_V.x;
        sUI_Constant_Buffer.m_vRect_UI.y = psDBG->m_vText_Box_V.y;
        sUI_Constant_Buffer.m_vRect_UI.z = psDBG->m_vText_Box_V.z;
        sUI_Constant_Buffer.m_vRect_UI.w = psDBG->m_vText_Box_V.w;
        sUI_Constant_Buffer.m_vUI_Colour = psDBG->m_vBackground_Colour;
        sUI_Constant_Buffer.m_uiSelect_Default_Texture_Index = 1;

        tgKN_GPU_EXT__CMD__Render_Debug_UI( uCMD, &sUI_Constant_Buffer );
    }

    if (psDBG->m_bDraw_First_Line)
    {
        STg2_KN_GPU_HLSL_CB_Debug_UI        sUI_Constant_Buffer;

        sUI_Constant_Buffer.m_sDESC = psDBG->m_sOutput_DESC;
        sUI_Constant_Buffer.m_vRect_UI.x = psDBG->m_vText_Box_V.x;
        sUI_Constant_Buffer.m_vRect_UI.y = psDBG->m_vText_Box_V.w + sText_Constant_Buffer.m_vFont_Glyph_Scale_S.y + 4.0F / sText_Constant_Buffer.m_vFont_Glyph_Scale_S.w;
        sUI_Constant_Buffer.m_vRect_UI.z = psDBG->m_vText_Box_V.z;
        sUI_Constant_Buffer.m_vRect_UI.w = psDBG->m_vText_Box_V.w;
        sUI_Constant_Buffer.m_vUI_Colour = psDBG->m_vBackground_First_Line;
        sUI_Constant_Buffer.m_uiSelect_Default_Texture_Index = 1;

        tgKN_GPU_EXT__CMD__Render_Debug_UI( uCMD, &sUI_Constant_Buffer );
    }


    tgKN_GPU_EXT__CMD__Set_State_From_Default( uCMD, ETgKN_GPU_DEFAULT_PSO_DEBUG_TEXT, psDBG->m_sRTBuffer.m_enFormat, psDBG->m_sDSBuffer.m_enFormat );

    /* For every line in the array of pointers in the parameter data structure. */
    for (uiLine_Index = 0; !bEnd_Process && uiLine_Index < TgARRAY_COUNT(psDBG->m_auszText) && uiLine_Index < psDBG->m_nuiText; ++uiLine_Index)
    {
        TgCHAR_U8_CPC                       uszText = psDBG->m_auszText[uiLine_Index];

        if (nullptr == uszText || 0 == uszText[0])
            break;

        do
        {
            /* For every letter in the line that we are processing */
            for (; !bEnd_Process && uiBuffer_Index < TgARRAY_COUNT(sText_Constant_Buffer.m_vText_Offset) && uszText[uiText_Index]; ++uiBuffer_Index, ++uiText_Index)
            {
                if (128 <= uszText[uiText_Index])
                    continue;

                /* Treat (Windows) CRLF and (Unix) LF correctly (start a new line). */

                if ('\n' == uszText[uiText_Index])
                {
                    uiTextX = 0;
                    ++uiTextY;
                    if (psDBG->m_bRight_Aligned && uiBuffer_Index > 0) {
                        tgKN_GPU__CMD__Render_Debug_Text_Box_Right_Align( &sText_Constant_Buffer, uiBuffer_Index, fText_Start_Z );
                    }
                    continue;
                };

                if ('\r' == uszText[uiText_Index] && '\n' == uszText[uiText_Index+1])
                {
                    uiTextX = 0;
                    ++uiTextY;
                    ++uiText_Index;
                    if (psDBG->m_bRight_Aligned && uiBuffer_Index > 0) {
                        tgKN_GPU__CMD__Render_Debug_Text_Box_Right_Align( &sText_Constant_Buffer, uiBuffer_Index, fText_Start_Z );
                    }
                    continue;
                };

                sText_Constant_Buffer.m_vText_Offset[uiBuffer_Index].x = fText_Start_X + (float)uiTextX * sText_Constant_Buffer.m_vFont_Glyph_Scale_S.x;
                ++uiTextX;

                /* Wrap the string (or consume the character, but do not render) if we are now at the right boundary of the text box. */

                if (psDBG->m_bWord_Wrap && (sText_Constant_Buffer.m_vText_Offset[uiBuffer_Index].x + sText_Constant_Buffer.m_vFont_Glyph_Scale_S.x >= fText_Start_Z))
                {
                    sText_Constant_Buffer.m_vText_Offset[uiBuffer_Index].x = fText_Start_X;
                    uiTextX = 0;
                    ++uiTextY;
                }

                /* Consume the character but do not create a render instance since it will be off-screen. */

                if (sText_Constant_Buffer.m_vText_Offset[uiBuffer_Index].x <= -1.0F)
                {
                    continue;
                }

                if (sText_Constant_Buffer.m_vText_Offset[uiBuffer_Index].x >= 1.0F)
                {
                    continue;
                }

                /* Determine the y position of the line (allowing for strings to be go down or up the page) and check to see if we now exceed the box or viewport. */
                if (psDBG->m_bLine_Change_Is_Positive)
                {
                    sText_Constant_Buffer.m_vText_Offset[uiBuffer_Index].y  = fText_Start_W;
                    sText_Constant_Buffer.m_vText_Offset[uiBuffer_Index].y += (float)(uiTextY) * sText_Constant_Buffer.m_vFont_Glyph_Scale_S.y;

                    /* Stop processing the string(s) if there is no longer any room for further lines in the text box. */
                    if (sText_Constant_Buffer.m_vText_Offset[uiBuffer_Index].y + sText_Constant_Buffer.m_vFont_Glyph_Scale_S.y >= fLimitT)
                    {
                        bEnd_Process = true;
                        break;
                    }
                }
                else
                {
                    sText_Constant_Buffer.m_vText_Offset[uiBuffer_Index].y = fText_Start_Y - (float)uiTextY * sText_Constant_Buffer.m_vFont_Glyph_Scale_S.y;

                    /* Stop processing the string(s) if there is no longer any room for further lines in the text box. */
                    if (sText_Constant_Buffer.m_vText_Offset[uiBuffer_Index].y - sText_Constant_Buffer.m_vFont_Glyph_Scale_S.y <= fLimitB)
                    {
                        bEnd_Process = true;
                        break;
                    }
                }

                /* Compute the UV values. */
                sText_Constant_Buffer.m_vText_Offset[uiBuffer_Index].z = (float)(uszText[uiText_Index] % (TgUINT_E32)(sFont_TX.m_fTX_X / sFont_TX.m_fTX_Cell_X));
                sText_Constant_Buffer.m_vText_Offset[uiBuffer_Index].w = (float)(uszText[uiText_Index] / (TgUINT_E32)(sFont_TX.m_fTX_X / sFont_TX.m_fTX_Cell_X));
            };

            if (uiBuffer_Index >= TgARRAY_COUNT(sText_Constant_Buffer.m_vText_Offset))
            {
                tgKN_GPU_EXT__CMD__Render_Debug_Text( uCMD, uiBuffer_Index, &sText_Constant_Buffer );
                uiBuffer_Index = 0;
            };

        } while (!bEnd_Process && psDBG->m_auszText[uiLine_Index][uiText_Index]);

        uiTextX = 0;
        ++uiTextY;
        if (psDBG->m_bRight_Aligned && uiBuffer_Index > 0) {
            tgKN_GPU__CMD__Render_Debug_Text_Box_Right_Align( &sText_Constant_Buffer, uiBuffer_Index, fText_Start_Z );
        }
    };

    if (!bEnd_Process && uiBuffer_Index > 0)
    {
        tgKN_GPU_EXT__CMD__Render_Debug_Text( uCMD, uiBuffer_Index, &sText_Constant_Buffer );
        uiBuffer_Index = 0;
    };
}


/* ---- tgKN_GPU__CMD__Render_Debug_Line ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU__CMD__Render_Debug_Line( UTg2_KN_GPU_CMD_C uCMD, TgVEC_F32_04_1 vS0, TgVEC_F32_04_1 vCL0, TgVEC_F32_04_1 vS1, TgVEC_F32_04_1 vCL1,
                                         STg2_KN_GPU_HLSL_CB_Debug_Line_CPC psCB )
{
    TgRSIZE                             uiEXEC = (uCMD.ps->m_tiCXT_WORK.m_uiI >> 16) & 0xFFFF;
    STg2_KN_GPU_CXT_EXEC_PC             psCXT_EXEC = g_asKN_GPU_CXT_EXEC + uiEXEC;

    TgPARAM_CHECK_INDEX( uiEXEC, g_asKN_GPU_CXT_EXEC );

    tgCM_UT_LF__SN__Lock_Spin( &psCXT_EXEC->m_sLINE_Lock.m_sLock );
    tgKN_GPU__CMD__Render_Debug_Line_Internal( uCMD, vS0, vCL0, vS1, vCL1, psCB );
    tgCM_UT_LF__SN__Signal( &psCXT_EXEC->m_sLINE_Lock.m_sLock );
}


/* ---- tgKN_GPU__CMD__Render_Debug_Line_Flush ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU__CMD__Render_Debug_Line_Flush( UTg2_KN_GPU_CMD_C uCMD, STg2_KN_GPU_HLSL_CB_Debug_Line_CPC psCB )
{
    TgRSIZE                             uiEXEC = (uCMD.ps->m_tiCXT_WORK.m_uiI >> 16) & 0xFFFF;
    STg2_KN_GPU_CXT_EXEC_PC             psCXT_EXEC = g_asKN_GPU_CXT_EXEC + uiEXEC;

    TgPARAM_CHECK_INDEX( uiEXEC, g_asKN_GPU_CXT_EXEC );

    tgCM_UT_LF__SN__Lock_Spin( &psCXT_EXEC->m_sLINE_Lock.m_sLock );
    tgKN_GPU_EXT__CMD__Render_Debug_Line( uCMD, psCXT_EXEC->m_asLine_Vertex, psCXT_EXEC->m_nuiLine_Vertex, psCB );
    psCXT_EXEC->m_nuiLine_Vertex = 0;
    tgCM_UT_LF__SN__Signal( &psCXT_EXEC->m_sLINE_Lock.m_sLock );
}


/* ---- tgKN_GPU__CMD__Render_Debug_Parabola ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
//TgVOID tgKN_GPU__CMD__Render_Debug_Parabola( UTg2_KN_GPU_CMD_C uCMD, STg2_Parabola_CPCU, STg2_KN_GPU_HLSL_CB_Debug_Line_CPC psDBG )
//{
//}


/* ---- tgKN_GPU__CMD__Render_Debug_Axes ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU__CMD__Render_Debug_Axes( UTg2_KN_GPU_CMD_C uCMD, TgVEC_F32_04_3_CPCU pxX0, TgVEC_F32_04_1 vScale, STg2_KN_GPU_HLSL_CB_Debug_Line_CPC psCB )
{
    TgRSIZE                             uiEXEC = (uCMD.ps->m_tiCXT_WORK.m_uiI >> 16) & 0xFFFF;
    STg2_KN_GPU_CXT_EXEC_PC             psCXT_EXEC = g_asKN_GPU_CXT_EXEC + uiEXEC;

    TgVEC_F32_04_1_C                    vK0 = tgMH_MUL_F32_04_1( vScale, pxX0->m_avCol[0] );
    TgVEC_F32_04_1_C                    vK1 = tgMH_MUL_F32_04_1( vScale, pxX0->m_avCol[1] );
    TgVEC_F32_04_1_C                    vK2 = tgMH_MUL_F32_04_1( vScale, pxX0->m_avCol[2] );
    TgVEC_F32_04_1_C                    vK3 = tgMH_ADD_F32_04_1( pxX0->m_avCol[0], vK0 );
    TgVEC_F32_04_1_C                    vK4 = tgMH_ADD_F32_04_1( pxX0->m_avCol[1], vK1 );
    TgVEC_F32_04_1_C                    vK5 = tgMH_ADD_F32_04_1( pxX0->m_avCol[2], vK2 );

    TgPARAM_CHECK_INDEX( uiEXEC, g_asKN_GPU_CXT_EXEC );

    tgCM_UT_LF__SN__Lock_Spin( &psCXT_EXEC->m_sLINE_Lock.m_sLock );
    tgKN_GPU__CMD__Render_Debug_Line_Internal( uCMD, pxX0->m_avCol[0], KTg_BLUE_G10_P709_F32_04, vK3, KTg_BLUE_G10_P709_F32_04, psCB );
    tgKN_GPU__CMD__Render_Debug_Line_Internal( uCMD, pxX0->m_avCol[1], KTg_GREEN_G10_P709_F32_04, vK4, KTg_GREEN_G10_P709_F32_04, psCB );
    tgKN_GPU__CMD__Render_Debug_Line_Internal( uCMD, pxX0->m_avCol[2], KTg_RED_G10_P709_F32_04, vK5, KTg_RED_G10_P709_F32_04, psCB );
    tgCM_UT_LF__SN__Signal( &psCXT_EXEC->m_sLINE_Lock.m_sLock );
}


/* ---- tgKN_GPU__CMD__Render_Debug_nGon ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU__CMD__Render_Debug_nGon( UTg2_KN_GPU_CMD_C uCMD, TgVEC_F32_04_1 vCL0, TgVEC_F32_04_3_CPCU pxX0, TgFLOAT32_C fScale, TgSINT_E32_C niSide,
                                         STg2_KN_GPU_HLSL_CB_Debug_Line_CPC psCB )
{
    TgRSIZE                             uiEXEC = (uCMD.ps->m_tiCXT_WORK.m_uiI >> 16) & 0xFFFF;
    STg2_KN_GPU_CXT_EXEC_PC             psCXT_EXEC = g_asKN_GPU_CXT_EXEC + uiEXEC;

    TgPARAM_CHECK_INDEX( uiEXEC, g_asKN_GPU_CXT_EXEC );

    if (niSide <= 2)
    {
        return;
    }
    else
    {
        TgFLOAT32_C                         fCutAngle = KTgTWO_PI_F32 / (TgFLOAT32)(niSide);

        TgUN_V128                           uS0, uS1;
        TgSINT_E32                          iIndex;

        uS0.m_vS_F32_04_1 = tgMH_Init_ELEM_S_F32_04_1( fScale, 0.0F, 0.0F, 1.0F );
        uS0.m_vF32_04_1 = tgMH_TX_P_F32_04_3( uS0.m_vF32_04_1, pxX0 );
        uS1.m_vF32_04_1 = KTgUNIT_W_F32_04_1;

        tgCM_UT_LF__SN__Lock_Spin( &psCXT_EXEC->m_sLINE_Lock.m_sLock );
        for (iIndex = 1; iIndex < niSide; ++iIndex)
        {
            tgPM_SINCOS_F32( &uS1.m_vS_F32_04_1.x, &uS1.m_vS_F32_04_1.z, ((TgFLOAT32)iIndex)*fCutAngle );
            uS1.m_vS_F32_04_1.x *= fScale;
            uS1.m_vS_F32_04_1.z *= fScale;
            uS1.m_vF32_04_1 = tgMH_TX_P_F32_04_3( uS1.m_vF32_04_1, pxX0 );
            tgKN_GPU__CMD__Render_Debug_Line_Internal( uCMD, uS0.m_vF32_04_1, vCL0, uS1.m_vF32_04_1, vCL0, psCB );
            uS0.m_vF32_04_1 = uS1.m_vF32_04_1;
        };

        uS1.m_vS_F32_04_1 = tgMH_Init_ELEM_S_F32_04_1( fScale, 0.0F, 0.0F, 1.0F );
        uS1.m_vF32_04_1 = tgMH_TX_P_F32_04_3( uS1.m_vF32_04_1, pxX0 );

        tgKN_GPU__CMD__Render_Debug_Line_Internal( uCMD, uS0.m_vF32_04_1, vCL0, uS1.m_vF32_04_1, vCL0, psCB );
        tgCM_UT_LF__SN__Signal( &psCXT_EXEC->m_sLINE_Lock.m_sLock );
    }
}


/* ---- tgKN_GPU__CMD__Render_Debug_Frustum -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU__CMD__Render_Debug_Frustum( UTg2_KN_GPU_CMD_C uCMD, TgVEC_F32_04_1 vCL0, TgVEC_F32_04_4_CPCU pxS2C, TgVEC_F32_04_4_CPCU pxC2W,
                                            STg2_KN_GPU_HLSL_CB_Debug_Line_CPC psCB )
{
    TgRSIZE                             uiEXEC = (uCMD.ps->m_tiCXT_WORK.m_uiI >> 16) & 0xFFFF;
    STg2_KN_GPU_CXT_EXEC_PC             psCXT_EXEC = g_asKN_GPU_CXT_EXEC + uiEXEC;

    TgVEC_F32_04_1_C                    vP1 = KTgONE_F32_04_1;
    TgVEC_F32_04_1_C                    vN1 = tgMH_NEG_F32_04_1( KTgONE_F32_04_1 );

    TgVEC_F32_04_1_C                    vA0 = tgMH_SEL_F32_04_1( vP1, vN1, KTg0000_V128.m_vF32_04_1 );
    TgVEC_F32_04_1_C                    vA1 = tgMH_SEL_F32_04_1( vP1, vN1, KTg00F0_V128.m_vF32_04_1 );
    TgVEC_F32_04_1_C                    vA2 = tgMH_SEL_F32_04_1( vP1, vN1, KTg0F00_V128.m_vF32_04_1 );
    TgVEC_F32_04_1_C                    vA3 = tgMH_SEL_F32_04_1( vP1, vN1, KTg0FF0_V128.m_vF32_04_1 );
    TgVEC_F32_04_1_C                    vA4 = tgMH_SEL_F32_04_1( vP1, vN1, KTgF000_V128.m_vF32_04_1 );
    TgVEC_F32_04_1_C                    vA5 = tgMH_SEL_F32_04_1( vP1, vN1, KTgF0F0_V128.m_vF32_04_1 );
    TgVEC_F32_04_1_C                    vA6 = tgMH_SEL_F32_04_1( vP1, vN1, KTgFF00_V128.m_vF32_04_1 );
    TgVEC_F32_04_1_C                    vA7 = tgMH_SEL_F32_04_1( vP1, vN1, KTgFFF0_V128.m_vF32_04_1 );

    TgVEC_F32_04_1_C                    vB0 = tgMH_TX_F32_04_4( vA0, pxS2C );
    TgVEC_F32_04_1_C                    vB1 = tgMH_TX_F32_04_4( vA1, pxS2C );
    TgVEC_F32_04_1_C                    vB2 = tgMH_TX_F32_04_4( vA2, pxS2C );
    TgVEC_F32_04_1_C                    vB3 = tgMH_TX_F32_04_4( vA3, pxS2C );
    TgVEC_F32_04_1_C                    vB4 = tgMH_TX_F32_04_4( vA4, pxS2C );
    TgVEC_F32_04_1_C                    vB5 = tgMH_TX_F32_04_4( vA5, pxS2C );
    TgVEC_F32_04_1_C                    vB6 = tgMH_TX_F32_04_4( vA6, pxS2C );
    TgVEC_F32_04_1_C                    vB7 = tgMH_TX_F32_04_4( vA7, pxS2C );

    TgVEC_F32_04_1_C                    vC0 = tgMH_DIV_F32_04_1( vB0, tgMH_SPW_F32_04_1( vB0 ) );
    TgVEC_F32_04_1_C                    vC1 = tgMH_DIV_F32_04_1( vB1, tgMH_SPW_F32_04_1( vB1 ) );
    TgVEC_F32_04_1_C                    vC2 = tgMH_DIV_F32_04_1( vB2, tgMH_SPW_F32_04_1( vB2 ) );
    TgVEC_F32_04_1_C                    vC3 = tgMH_DIV_F32_04_1( vB3, tgMH_SPW_F32_04_1( vB3 ) );
    TgVEC_F32_04_1_C                    vC4 = tgMH_DIV_F32_04_1( vB4, tgMH_SPW_F32_04_1( vB4 ) );
    TgVEC_F32_04_1_C                    vC5 = tgMH_DIV_F32_04_1( vB5, tgMH_SPW_F32_04_1( vB5 ) );
    TgVEC_F32_04_1_C                    vC6 = tgMH_DIV_F32_04_1( vB6, tgMH_SPW_F32_04_1( vB6 ) );
    TgVEC_F32_04_1_C                    vC7 = tgMH_DIV_F32_04_1( vB7, tgMH_SPW_F32_04_1( vB7 ) );

    TgVEC_F32_04_1_C                    vD0 = tgMH_TX_F32_04_4( vC0, pxC2W );
    TgVEC_F32_04_1_C                    vD1 = tgMH_TX_F32_04_4( vC1, pxC2W );
    TgVEC_F32_04_1_C                    vD2 = tgMH_TX_F32_04_4( vC2, pxC2W );
    TgVEC_F32_04_1_C                    vD3 = tgMH_TX_F32_04_4( vC3, pxC2W );
    TgVEC_F32_04_1_C                    vD4 = tgMH_TX_F32_04_4( vC4, pxC2W );
    TgVEC_F32_04_1_C                    vD5 = tgMH_TX_F32_04_4( vC5, pxC2W );
    TgVEC_F32_04_1_C                    vD6 = tgMH_TX_F32_04_4( vC6, pxC2W );
    TgVEC_F32_04_1_C                    vD7 = tgMH_TX_F32_04_4( vC7, pxC2W );

    TgVEC_F32_04_1_C                    vS0 = tgMH_TX_F32_04_4( KTgUNIT_W_F32_04_1, pxC2W );

    TgPARAM_CHECK_INDEX( uiEXEC, g_asKN_GPU_CXT_EXEC );

    tgCM_UT_LF__SN__Lock_Spin( &psCXT_EXEC->m_sLINE_Lock.m_sLock );

    tgKN_GPU__CMD__Render_Debug_Line_Internal( uCMD, vD0, vCL0, vD1, vCL0, psCB );
    tgKN_GPU__CMD__Render_Debug_Line_Internal( uCMD, vD1, vCL0, vD3, vCL0, psCB );
    tgKN_GPU__CMD__Render_Debug_Line_Internal( uCMD, vD3, vCL0, vD2, vCL0, psCB );
    tgKN_GPU__CMD__Render_Debug_Line_Internal( uCMD, vD2, vCL0, vD0, vCL0, psCB );
    tgKN_GPU__CMD__Render_Debug_Line_Internal( uCMD, vD7, vCL0, vD6, vCL0, psCB );
    tgKN_GPU__CMD__Render_Debug_Line_Internal( uCMD, vD6, vCL0, vD4, vCL0, psCB );
    tgKN_GPU__CMD__Render_Debug_Line_Internal( uCMD, vD4, vCL0, vD5, vCL0, psCB );
    tgKN_GPU__CMD__Render_Debug_Line_Internal( uCMD, vD5, vCL0, vD7, vCL0, psCB );
    tgKN_GPU__CMD__Render_Debug_Line_Internal( uCMD, vD0, vCL0, vD4, vCL0, psCB );
    tgKN_GPU__CMD__Render_Debug_Line_Internal( uCMD, vD1, vCL0, vD5, vCL0, psCB );
    tgKN_GPU__CMD__Render_Debug_Line_Internal( uCMD, vD2, vCL0, vD6, vCL0, psCB );
    tgKN_GPU__CMD__Render_Debug_Line_Internal( uCMD, vD3, vCL0, vD7, vCL0, psCB );

    tgKN_GPU__CMD__Render_Debug_Line_Internal( uCMD, vS0, KTg_MAGENTA_G10_P709_F32_04, vD1, KTg_MAGENTA_G10_P709_F32_04, psCB );
    tgKN_GPU__CMD__Render_Debug_Line_Internal( uCMD, vS0, KTg_MAGENTA_G10_P709_F32_04, vD3, KTg_MAGENTA_G10_P709_F32_04, psCB );
    tgKN_GPU__CMD__Render_Debug_Line_Internal( uCMD, vS0, KTg_MAGENTA_G10_P709_F32_04, vD5, KTg_MAGENTA_G10_P709_F32_04, psCB );
    tgKN_GPU__CMD__Render_Debug_Line_Internal( uCMD, vS0, KTg_MAGENTA_G10_P709_F32_04, vD7, KTg_MAGENTA_G10_P709_F32_04, psCB );

    tgCM_UT_LF__SN__Signal( &psCXT_EXEC->m_sLINE_Lock.m_sLock );
}


/* ---- tgKN_GPU__CMD__Render_Debug_Camera_Frustum ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU__CMD__Render_Debug_Camera_Frustum( UTg2_KN_GPU_CMD_C uCMD, TgVEC_F32_04_1_C vCL0, STg2_KN_GPU_Camera_CPCU psCamera, STg2_KN_GPU_HLSL_CB_Debug_Line_CPC psCB )
{
    tgKN_GPU__CMD__Render_Debug_Frustum( uCMD, vCL0, &psCamera->m_xFrustum_S2C, &psCamera->m_xFrustum_C2W, psCB );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Geometry Generation Functions                                                                                                                                         */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_GPU_DBG_Init_Mesh_Sphere -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_DBG_Init_Mesh_Sphere( TgKN_GPU_DBG_PM_Generate_PC psGeom_Generate )
{
    TgRSIZE                             uiIndex;

    psGeom_Generate->m_nuiVertex = 0;
    psGeom_Generate->m_nuiIndex = 0;

    if (nullptr == psGeom_Generate->m_puiIndex || 0 == psGeom_Generate->m_nuiMax_Index)
    {
        psGeom_Generate->m_nuiMax_Index = TgARRAY_COUNT(KTgGM_ICOSAHEDRON_PN_INDEX)*(TgRSIZE)(tgPM_POW_F32( 4, (TgFLOAT32)psGeom_Generate->m_uiTessellate ));
        return;
    };

    if (psGeom_Generate->m_psVertex)
    {
        if ((2 * psGeom_Generate->m_nuiMax_Vertex) >= TgARRAY_COUNT( KTgGM_ICOSAHEDRON_PN_INDEX_VERTEX ))
        {
            psGeom_Generate->m_nuiVertex = TgARRAY_COUNT(KTgGM_ICOSAHEDRON_PN_INDEX_VERTEX) >> 1;

            for (TgRSIZE uiVert = 0; uiVert < psGeom_Generate->m_nuiVertex; ++uiVert)
            {
                TgVEC_S_F32_04_1_C                  vK2 = tgMH_SET1_S_F32_04_1( 0.5F );
                TgVEC_S_F32_04_1_C                  vKN = tgMH_NORM_S_F32_04_1( KTgGM_ICOSAHEDRON_PN_INDEX_VERTEX[2*uiVert].m_vS_F32_04_1 );
                TgVEC_S_F32_04_1_C                  vKS = tgMH_MUL_S_F32_04_1( vK2, vKN );

                TgCRITICAL(uiVert < psGeom_Generate->m_nuiMax_Vertex);

                psGeom_Generate->m_psVertex[uiVert].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1( vKS.x, vKS.y, vKS.z );
                psGeom_Generate->m_psVertex[uiVert].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1( vKN.x, vKN.y, vKN.z );
            }
        }
        else
        {
            return;
        };
    }
    else
    {
        psGeom_Generate->m_nuiVertex = TgARRAY_COUNT(KTgGM_ICOSAHEDRON_PN_INDEX_VERTEX) >> 1;
    }

    if (psGeom_Generate->m_puiIndex && psGeom_Generate->m_nuiMax_Index >= TgARRAY_COUNT(KTgGM_ICOSAHEDRON_PN_INDEX))
    {
        psGeom_Generate->m_nuiIndex = TgARRAY_COUNT(KTgGM_ICOSAHEDRON_PN_INDEX);
        tgMM_Copy( psGeom_Generate->m_puiIndex, sizeof(KTgGM_ICOSAHEDRON_PN_INDEX), KTgGM_ICOSAHEDRON_PN_INDEX, sizeof(KTgGM_ICOSAHEDRON_PN_INDEX) );
    }
    else
    {
        return;
    }

    for (uiIndex = 0; uiIndex < psGeom_Generate->m_uiTessellate; ++uiIndex)
    {
        tgKN_GPU_DBG_Tessellate( psGeom_Generate );
    };

    if (nullptr == psGeom_Generate->m_psVertex || 0 == psGeom_Generate->m_nuiMax_Vertex)
    {
        psGeom_Generate->m_nuiMax_Vertex = psGeom_Generate->m_nuiVertex;
    };
}


/* ---- tgKN_GPU_DBG_Init_Mesh_Capsule ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_DBG_Init_Mesh_Capsule( TgKN_GPU_DBG_PM_Generate_PC psGeom_Generate )
{
    TgRSIZE                             nuiIndex_Tube;
    TgRSIZE                             uiIndex;

    if (nullptr == psGeom_Generate->m_puiIndex || 0 == psGeom_Generate->m_nuiMax_Index)
    {
        psGeom_Generate->m_nuiMax_Index  = (TgARRAY_COUNT(KTgGM_ICOSAHEDRON_CAPSULE_PN_INDEX) - 36u)*(TgRSIZE)(tgPM_POW_F32( 4, (TgFLOAT32)psGeom_Generate->m_uiTessellate ));
        psGeom_Generate->m_nuiMax_Index += 36u*(TgRSIZE)(tgPM_POW_F32( 2, (TgFLOAT32)psGeom_Generate->m_uiTessellate ));
        return;
    };

    if (psGeom_Generate->m_psVertex)
    {
        if ((2 * psGeom_Generate->m_nuiMax_Vertex) >= TgARRAY_COUNT( KTgGM_ICOSAHEDRON_CAPSULE_PN_INDEX_VERTEX ))
        {
            TgRSIZE                             uiVert;

            psGeom_Generate->m_nuiVertex = TgARRAY_COUNT(KTgGM_ICOSAHEDRON_CAPSULE_PN_INDEX_VERTEX) >> 1;

            for (uiVert= 0; uiVert < psGeom_Generate->m_nuiVertex; ++uiVert)
            {
                TgVEC_S_F32_04_1_C                  vK2 = tgMH_SET1_S_F32_04_1( 0.5F );
                TgVEC_S_F32_04_1_C                  vKN = tgMH_NORM_S_F32_04_1( KTgGM_ICOSAHEDRON_CAPSULE_PN_INDEX_VERTEX[2*uiVert].m_vS_F32_04_1 );
                TgVEC_S_F32_04_1_C                  vKS = tgMH_MUL_S_F32_04_1( vK2, vKN );

                TgCRITICAL(uiVert < psGeom_Generate->m_nuiMax_Vertex);

                psGeom_Generate->m_psVertex[uiVert].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1( vKS.x, vKS.y, vKS.z );
                psGeom_Generate->m_psVertex[uiVert].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1( vKN.x, vKN.y, vKN.z );
            }
        }
        else
        {
            return;
        };
    }
    else
    {
        psGeom_Generate->m_nuiVertex = TgARRAY_COUNT(KTgGM_ICOSAHEDRON_CAPSULE_PN_INDEX_VERTEX) >> 1;
    };

    if (psGeom_Generate->m_puiIndex && psGeom_Generate->m_nuiMax_Index >= TgARRAY_COUNT(KTgGM_ICOSAHEDRON_CAPSULE_PN_INDEX))
    {
        psGeom_Generate->m_nuiIndex = TgARRAY_COUNT(KTgGM_ICOSAHEDRON_CAPSULE_PN_INDEX);
        tgMM_Copy( psGeom_Generate->m_puiIndex, sizeof(KTgGM_ICOSAHEDRON_CAPSULE_PN_INDEX), KTgGM_ICOSAHEDRON_CAPSULE_PN_INDEX, sizeof(KTgGM_ICOSAHEDRON_CAPSULE_PN_INDEX) );
    }
    else
    {
        return;
    }

    nuiIndex_Tube = 36;
    for (uiIndex = 0; uiIndex < psGeom_Generate->m_uiTessellate; ++uiIndex)
    {
        tgKN_GPU_DBG_Tessellate_Capsule( &nuiIndex_Tube, psGeom_Generate );
    };

    if (psGeom_Generate->m_psVertex)
    {
        for (uiIndex = 0; uiIndex < psGeom_Generate->m_nuiVertex >> 1; ++uiIndex)
        {
            psGeom_Generate->m_psVertex[uiIndex].m_vS0 = tgMH_ADD_F32_04_1( psGeom_Generate->m_psVertex[uiIndex].m_vS0, KTgUNIT_Y_F32_04_1 );
        };

        for (; uiIndex < psGeom_Generate->m_nuiVertex; ++uiIndex)
        {
            psGeom_Generate->m_psVertex[uiIndex].m_vS0 = tgMH_SUB_F32_04_1( psGeom_Generate->m_psVertex[uiIndex].m_vS0, KTgUNIT_Y_F32_04_1 );
        };
    };

    if (nullptr == psGeom_Generate->m_psVertex || 0 == psGeom_Generate->m_nuiMax_Vertex)
    {
        psGeom_Generate->m_nuiMax_Vertex = psGeom_Generate->m_nuiVertex;
    };
}


/* ---- tgKN_GPU_DBG_Init_Mesh_Cone ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_DBG_Init_Mesh_Cone( TgKN_GPU_DBG_PM_Generate_PC psGeom_Generate )
{
    TgRSIZE                             nuiRim_Points = 4u * ( psGeom_Generate->m_uiTessellate + 1 );

    if (nullptr == psGeom_Generate->m_psVertex || 0 == psGeom_Generate->m_nuiMax_Vertex || nullptr == psGeom_Generate->m_puiIndex || 0 == psGeom_Generate->m_nuiMax_Index)
    {
        psGeom_Generate->m_nuiMax_Index = 6 * nuiRim_Points;
        psGeom_Generate->m_nuiMax_Vertex = 1 + 3 * nuiRim_Points;
        return;
    }
    else
    {
        TgFLOAT32_C                         fCutAngle = KTgTWO_PI_F32 / (TgFLOAT32)(3 * (nuiRim_Points-1));
        TgUINT_E16_C                        nui16_Rim_Points = (TgUINT_E16)nuiRim_Points;
        TgFLOAT32_C                         fRadius = 0.5F;
        TgUINT_E16                          uiIndex;

        /* Create a vertex  with a cap outward normal and a coincident vertex with a body outward normal. */
        for (psGeom_Generate->m_nuiVertex = 0; psGeom_Generate->m_nuiVertex < 3 * nuiRim_Points; psGeom_Generate->m_nuiVertex += 3)
        {
            TgFLOAT32_C                         fA0 = ((TgFLOAT32)psGeom_Generate->m_nuiVertex)*fCutAngle;
            TgFLOAT32                           fCos0, fSin0;
            TgUN_V128                           uT0, uT1;

            tgPM_SINCOS_F32( &fCos0, &fSin0, fA0 );

            uT0.m_vF32_04_1 = tgMH_Init_Vector_ELEM_F32_04_1( fRadius*fCos0, 1.0F, fRadius*fSin0 );
            uT0.m_vF32_04_1 = tgMH_NORM_F32_04_1( uT0.m_vF32_04_1 );
            uT1.m_vF32_04_1 = tgMH_Init_Vector_ELEM_F32_04_1( fCos0*uT0.m_vS_F32_04_1.y, -fCos0*uT0.m_vS_F32_04_1.x - fSin0*uT0.m_vS_F32_04_1.z, fSin0*uT0.m_vS_F32_04_1.y );
            uT1.m_vF32_04_1 = tgMH_NORM_F32_04_1( uT1.m_vF32_04_1 );

            psGeom_Generate->m_psVertex[psGeom_Generate->m_nuiVertex + 0].m_vS0 = tgMH_Init_Point_F32_04_1( uT0.m_vF32_04_1 );
            psGeom_Generate->m_psVertex[psGeom_Generate->m_nuiVertex + 0].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1( 0.0F, 1.0F, 0.0F );
            psGeom_Generate->m_psVertex[psGeom_Generate->m_nuiVertex + 1].m_vS0 = tgMH_Init_Point_F32_04_1( uT0.m_vF32_04_1 );
            psGeom_Generate->m_psVertex[psGeom_Generate->m_nuiVertex + 1].m_vN0 = uT1.m_vF32_04_1;
            psGeom_Generate->m_psVertex[psGeom_Generate->m_nuiVertex + 2].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1( 0.0F, 0.0F, 0.0F );
            psGeom_Generate->m_psVertex[psGeom_Generate->m_nuiVertex + 2].m_vN0 = uT1.m_vF32_04_1;
        };

        psGeom_Generate->m_psVertex[psGeom_Generate->m_nuiVertex].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1( 0.0F, 1.0F, 0.0F );
        psGeom_Generate->m_psVertex[psGeom_Generate->m_nuiVertex].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1( 0.0F, 1.0F, 0.0F );
        ++psGeom_Generate->m_nuiVertex;

        for (psGeom_Generate->m_nuiIndex = 0, uiIndex = 0; uiIndex < nui16_Rim_Points; ++uiIndex, psGeom_Generate->m_nuiIndex += 6)
        {
            psGeom_Generate->m_puiIndex[6 * uiIndex + 0] = 3u * nui16_Rim_Points;
            psGeom_Generate->m_puiIndex[6 * uiIndex + 1] = 3u * uiIndex + 0u;
            psGeom_Generate->m_puiIndex[6 * uiIndex + 2] = 3u * uiIndex + 3u;

            psGeom_Generate->m_puiIndex[6 * uiIndex + 3] = 3u * uiIndex + 1u;
            psGeom_Generate->m_puiIndex[6 * uiIndex + 4] = 3u * uiIndex + 2u;
            psGeom_Generate->m_puiIndex[6 * uiIndex + 5] = 3u * uiIndex + 3u;
        };
        TgVERIFY( psGeom_Generate->m_nuiMax_Vertex==psGeom_Generate->m_nuiVertex );
        TgVERIFY( psGeom_Generate->m_nuiMax_Index==psGeom_Generate->m_nuiIndex );
    };
}


/* ---- tgKN_GPU_DBG_Init_Mesh_Cylinder ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_DBG_Init_Mesh_Cylinder( TgKN_GPU_DBG_PM_Generate_PC psGeom_Generate )
{
    TgRSIZE                             nuiRim_Points = 4u * ( psGeom_Generate->m_uiTessellate + 1 );

    if (nullptr == psGeom_Generate->m_psVertex || 0 == psGeom_Generate->m_nuiMax_Vertex || nullptr == psGeom_Generate->m_puiIndex || 0 == psGeom_Generate->m_nuiMax_Index)
    {
        psGeom_Generate->m_nuiMax_Index = 12u * nuiRim_Points;
        psGeom_Generate->m_nuiMax_Vertex = 2u + 4u * nuiRim_Points;
        return;
    }
    else
    {
        TgFLOAT32_C                         fCutAngle = KTgTWO_PI_F32 / (TgFLOAT32)(4u * (nuiRim_Points-1u));
        TgUINT_E16_C                        nui16_Rim_Points = (TgUINT_E16)nuiRim_Points;
        TgFLOAT32_C                         fRadius = 0.5F;
        TgUINT_E16                          uiIndex;

        /* Create a vertex  with a cap outward normal and a coincident vertex with a body outward normal at both ends. */
        for (psGeom_Generate->m_nuiVertex = 0; psGeom_Generate->m_nuiVertex < 4 * nuiRim_Points; psGeom_Generate->m_nuiVertex += 4)
        {
            TgFLOAT32_C                         fA0 = ((TgFLOAT32)psGeom_Generate->m_nuiVertex)*fCutAngle;
            TgFLOAT32                           fCos0, fSin0;

            tgPM_SINCOS_F32( &fCos0, &fSin0, fA0 );

            psGeom_Generate->m_psVertex[psGeom_Generate->m_nuiVertex + 0].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1( fRadius*fCos0, 1.0F, fRadius*fSin0 );
            psGeom_Generate->m_psVertex[psGeom_Generate->m_nuiVertex + 0].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1( 0.0F, 1.0F, 0.0F );
            psGeom_Generate->m_psVertex[psGeom_Generate->m_nuiVertex + 1].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1( fRadius*fCos0, 1.0F, fRadius*fSin0 );
            psGeom_Generate->m_psVertex[psGeom_Generate->m_nuiVertex + 1].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1( fCos0, 0.0F, fSin0 );
            psGeom_Generate->m_psVertex[psGeom_Generate->m_nuiVertex + 2].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1( fRadius*fCos0, -1.0F, fRadius*fSin0 );
            psGeom_Generate->m_psVertex[psGeom_Generate->m_nuiVertex + 2].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1( fCos0, 0.0F, fSin0 );
            psGeom_Generate->m_psVertex[psGeom_Generate->m_nuiVertex + 3].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1( fRadius*fCos0, -1.0F, fRadius*fSin0 );
            psGeom_Generate->m_psVertex[psGeom_Generate->m_nuiVertex + 3].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1( 0.0F, -1.0F, 0.0F );
        };

        psGeom_Generate->m_psVertex[psGeom_Generate->m_nuiVertex + 0].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1( 0.0F, 1.0F, 0.0F );
        psGeom_Generate->m_psVertex[psGeom_Generate->m_nuiVertex + 0].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1( 0.0F, 1.0F, 0.0F );
        psGeom_Generate->m_psVertex[psGeom_Generate->m_nuiVertex + 1].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1( 0.0F, -1.0F, 0.0F );
        psGeom_Generate->m_psVertex[psGeom_Generate->m_nuiVertex + 1].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1( 0.0F, -1.0F, 0.0F );
        psGeom_Generate->m_nuiVertex += 2;

        for (psGeom_Generate->m_nuiIndex = 0, uiIndex = 0; uiIndex < nui16_Rim_Points; ++uiIndex, psGeom_Generate->m_nuiIndex += 12)
        {
            psGeom_Generate->m_puiIndex[12 * uiIndex + 0x0] = 4 * nui16_Rim_Points + 0u;
            psGeom_Generate->m_puiIndex[12 * uiIndex + 0x1] = 4 * uiIndex + 0u;
            psGeom_Generate->m_puiIndex[12 * uiIndex + 0x2] = 4 * uiIndex + 4u;

            psGeom_Generate->m_puiIndex[12 * uiIndex + 0x3] = 4 * uiIndex + 1u;
            psGeom_Generate->m_puiIndex[12 * uiIndex + 0x4] = 4 * uiIndex + 2u;
            psGeom_Generate->m_puiIndex[12 * uiIndex + 0x5] = 4 * uiIndex + 5u;

            psGeom_Generate->m_puiIndex[12 * uiIndex + 0x6] = 4 * uiIndex + 5u;
            psGeom_Generate->m_puiIndex[12 * uiIndex + 0x7] = 4 * uiIndex + 2u;
            psGeom_Generate->m_puiIndex[12 * uiIndex + 0x8] = 4 * uiIndex + 6u;

            psGeom_Generate->m_puiIndex[12 * uiIndex + 0x9] = 4 * nui16_Rim_Points + 1u;
            psGeom_Generate->m_puiIndex[12 * uiIndex + 0xA] = 4 * uiIndex + 7u;
            psGeom_Generate->m_puiIndex[12 * uiIndex + 0xB] = 4 * uiIndex + 3u;
        };
    };
}


/* ---- tgKN_GPU_DBG_Init_Mesh_Tube ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_DBG_Init_Mesh_Tube( TgKN_GPU_DBG_PM_Generate_PC psGeom_Generate )
{
    TgRSIZE                             nuiRim_Points = 4u * psGeom_Generate->m_uiTessellate;

    if (nullptr == psGeom_Generate->m_psVertex || 0 == psGeom_Generate->m_nuiMax_Vertex || nullptr == psGeom_Generate->m_puiIndex || 0 == psGeom_Generate->m_nuiMax_Index)
    {
        psGeom_Generate->m_nuiMax_Index = 12u * nuiRim_Points;
        psGeom_Generate->m_nuiMax_Vertex = 2u + 4u * nuiRim_Points;
        return;
    }
    else
    {
        TgFLOAT32_C                         fCutAngle = KTgTWO_PI_F32 / (TgFLOAT32)(4u * (nuiRim_Points-1u));
        TgUINT_E16_C                        nui16_Rim_Points = (TgUINT_E16)nuiRim_Points;
        TgFLOAT32_C                         fRadius = 0.5F;
        TgUINT_E16                          uiIndex;

        /* Create a vertex  with a cap outward normal and a coincident vertex with a body outward normal at both ends. */
        for (psGeom_Generate->m_nuiVertex = 0; psGeom_Generate->m_nuiVertex < 4 * nuiRim_Points; psGeom_Generate->m_nuiVertex += 4)
        {
            TgFLOAT32_C                         fA0 = ((TgFLOAT32)psGeom_Generate->m_nuiVertex)*fCutAngle;
            TgFLOAT32                           fCos0, fSin0;

            tgPM_SINCOS_F32( &fCos0, &fSin0, fA0 );

            psGeom_Generate->m_psVertex[psGeom_Generate->m_nuiVertex + 0].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1( fRadius*fCos0, 1.0F, fRadius*fSin0 );
            psGeom_Generate->m_psVertex[psGeom_Generate->m_nuiVertex + 0].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1( -fCos0, 0.0F, -fSin0 );
            psGeom_Generate->m_psVertex[psGeom_Generate->m_nuiVertex + 1].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1( fRadius*fCos0, 1.0F, fRadius*fSin0 );
            psGeom_Generate->m_psVertex[psGeom_Generate->m_nuiVertex + 1].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1( fCos0, 0.0F, fSin0 );
            psGeom_Generate->m_psVertex[psGeom_Generate->m_nuiVertex + 2].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1( fRadius*fCos0, -1.0F, fRadius*fSin0 );
            psGeom_Generate->m_psVertex[psGeom_Generate->m_nuiVertex + 2].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1( fCos0, 0.0F, fSin0 );
            psGeom_Generate->m_psVertex[psGeom_Generate->m_nuiVertex + 3].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1( fRadius*fCos0, -1.0F, fRadius*fSin0 );
            psGeom_Generate->m_psVertex[psGeom_Generate->m_nuiVertex + 3].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1( -fCos0, 0.0F, -fSin0 );
        };

        for (psGeom_Generate->m_nuiIndex = 0, uiIndex = 0; uiIndex < nui16_Rim_Points; ++uiIndex, psGeom_Generate->m_nuiIndex += 12)
        {
            psGeom_Generate->m_puiIndex[12 * uiIndex + 0x0] = 4 * uiIndex + 0u;
            psGeom_Generate->m_puiIndex[12 * uiIndex + 0x1] = 4 * uiIndex + 4u;
            psGeom_Generate->m_puiIndex[12 * uiIndex + 0x2] = 4 * uiIndex + 3u;

            psGeom_Generate->m_puiIndex[12 * uiIndex + 0x3] = 4 * uiIndex + 1u;
            psGeom_Generate->m_puiIndex[12 * uiIndex + 0x4] = 4 * uiIndex + 2u;
            psGeom_Generate->m_puiIndex[12 * uiIndex + 0x5] = 4 * uiIndex + 5u;

            psGeom_Generate->m_puiIndex[12 * uiIndex + 0x6] = 4 * uiIndex + 5u;
            psGeom_Generate->m_puiIndex[12 * uiIndex + 0x7] = 4 * uiIndex + 2u;
            psGeom_Generate->m_puiIndex[12 * uiIndex + 0x8] = 4 * uiIndex + 6u;

            psGeom_Generate->m_puiIndex[12 * uiIndex + 0x9] = 4 * uiIndex + 3u;
            psGeom_Generate->m_puiIndex[12 * uiIndex + 0xA] = 4 * uiIndex + 4u;
            psGeom_Generate->m_puiIndex[12 * uiIndex + 0xB] = 4 * uiIndex + 7u;
        };
    };
}


/* ---- tgKN_GPU_DBG_Init_Mesh_Box ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_DBG_Init_Mesh_Box( TgKN_GPU_DBG_PM_Generate_PC psGeom_Generate )
{
    if (nullptr == psGeom_Generate->m_psVertex || 0 == psGeom_Generate->m_nuiMax_Vertex || nullptr == psGeom_Generate->m_puiIndex || 0 == psGeom_Generate->m_nuiMax_Index)
    {
        psGeom_Generate->m_nuiMax_Index = 36u;
        psGeom_Generate->m_nuiMax_Vertex = 36u;
        return;
    }
    else
    {
        TgUINT_E16                            uiIndex;

        psGeom_Generate->m_psVertex[ 0].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1( 0.5F, -0.5F, -0.5F );
        psGeom_Generate->m_psVertex[ 0].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1( 1.0F, 0.0F, 0.0F );
        psGeom_Generate->m_psVertex[ 1].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1( 0.5F, 0.5F, 0.5F );
        psGeom_Generate->m_psVertex[ 1].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1( 1.0F, 0.0F, 0.0F );
        psGeom_Generate->m_psVertex[ 2].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1( 0.5F, -0.5F, 0.5F );
        psGeom_Generate->m_psVertex[ 2].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1( 1.0F, 0.0F, 0.0F );
        psGeom_Generate->m_psVertex[ 3].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1( 0.5F, -0.5F, -0.5F );
        psGeom_Generate->m_psVertex[ 3].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1( 1.0F, 0.0F, 0.0F );
        psGeom_Generate->m_psVertex[ 4].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1( 0.5F, 0.5F, -0.5F );
        psGeom_Generate->m_psVertex[ 4].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1( 1.0F, 0.0F, 0.0F );
        psGeom_Generate->m_psVertex[ 5].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1( 0.5F, 0.5F, 0.5F );
        psGeom_Generate->m_psVertex[ 5].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1( 1.0F, 0.0F, 0.0F );
        psGeom_Generate->m_psVertex[ 6].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1( -0.5F, 0.5F, -0.5F );
        psGeom_Generate->m_psVertex[ 6].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1( 0.0F, 1.0F, 0.0F );
        psGeom_Generate->m_psVertex[ 7].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1( -0.5F, 0.5F, 0.5F );
        psGeom_Generate->m_psVertex[ 7].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1( 0.0F, 1.0F, 0.0F );
        psGeom_Generate->m_psVertex[ 8].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1( 0.5F, 0.5F, 0.5F );
        psGeom_Generate->m_psVertex[ 8].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1( 0.0F, 1.0F, 0.0F );
        psGeom_Generate->m_psVertex[ 9].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1( -0.5F, 0.5F, -0.5F );
        psGeom_Generate->m_psVertex[ 9].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1( 0.0F, 1.0F, 0.0F );
        psGeom_Generate->m_psVertex[10].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1( 0.5F, 0.5F, 0.5F );
        psGeom_Generate->m_psVertex[10].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1( 0.0F, 1.0F, 0.0F );
        psGeom_Generate->m_psVertex[11].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1( 0.5F, 0.5F, -0.5F );
        psGeom_Generate->m_psVertex[11].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1( 0.0F, 1.0F, 0.0F );
        psGeom_Generate->m_psVertex[12].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1( -0.5F, -0.5F, 0.5F );
        psGeom_Generate->m_psVertex[12].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1( 0.0F, 0.0F, 1.0F );
        psGeom_Generate->m_psVertex[13].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1( 0.5F, 0.5F, 0.5F );
        psGeom_Generate->m_psVertex[13].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1( 0.0F, 0.0F, 1.0F );
        psGeom_Generate->m_psVertex[14].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1( -0.5F, 0.5F, 0.5F );
        psGeom_Generate->m_psVertex[14].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1( 0.0F, 0.0F, 1.0F );
        psGeom_Generate->m_psVertex[15].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1( -0.5F, -0.5F, 0.5F );
        psGeom_Generate->m_psVertex[15].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1( 0.0F, 0.0F, 1.0F );
        psGeom_Generate->m_psVertex[16].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1( 0.5F, -0.5F, 0.5F );
        psGeom_Generate->m_psVertex[16].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1( 0.0F, 0.0F, 1.0F );
        psGeom_Generate->m_psVertex[17].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1( 0.5F, 0.5F, 0.5F );
        psGeom_Generate->m_psVertex[17].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1( 0.0F, 0.0F, 1.0F );
        psGeom_Generate->m_psVertex[18].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1( -0.5F, -0.5F, -0.5F );
        psGeom_Generate->m_psVertex[18].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1( -1.0F, 0.0F, 0.0F );
        psGeom_Generate->m_psVertex[19].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1( -0.5F, -0.5F, 0.5F );
        psGeom_Generate->m_psVertex[19].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1( -1.0F, 0.0F, 0.0F );
        psGeom_Generate->m_psVertex[20].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1( -0.5F, 0.5F, 0.5F );
        psGeom_Generate->m_psVertex[20].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1( -1.0F, 0.0F, 0.0F );
        psGeom_Generate->m_psVertex[21].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1( -0.5F, -0.5F, -0.5F );
        psGeom_Generate->m_psVertex[21].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1( -1.0F, 0.0F, 0.0F );
        psGeom_Generate->m_psVertex[22].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1( -0.5F, 0.5F, 0.5F );
        psGeom_Generate->m_psVertex[22].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1( -1.0F, 0.0F, 0.0F );
        psGeom_Generate->m_psVertex[23].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1( -0.5F, 0.5F, -0.5F );
        psGeom_Generate->m_psVertex[23].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1( -1.0F, 0.0F, 0.0F );
        psGeom_Generate->m_psVertex[24].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1( -0.5F, -0.5F, -0.5F );
        psGeom_Generate->m_psVertex[24].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1( 0.0F, -1.0F, 0.0F );
        psGeom_Generate->m_psVertex[25].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1( 0.5F, -0.5F, 0.5F );
        psGeom_Generate->m_psVertex[25].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1( 0.0F, -1.0F, 0.0F );
        psGeom_Generate->m_psVertex[26].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1( -0.5F, -0.5F, 0.5F );
        psGeom_Generate->m_psVertex[26].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1( 0.0F, -1.0F, 0.0F );
        psGeom_Generate->m_psVertex[27].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1( -0.5F, -0.5F, -0.5F );
        psGeom_Generate->m_psVertex[27].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1( 0.0F, -1.0F, 0.0F );
        psGeom_Generate->m_psVertex[28].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1( 0.5F, -0.5F, -0.5F );
        psGeom_Generate->m_psVertex[28].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1( 0.0F, -1.0F, 0.0F );
        psGeom_Generate->m_psVertex[29].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1( 0.5F, -0.5F, 0.5F );
        psGeom_Generate->m_psVertex[29].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1( 0.0F, -1.0F, 0.0F );
        psGeom_Generate->m_psVertex[30].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1( -0.5F, -0.5F, -0.5F );
        psGeom_Generate->m_psVertex[30].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1( 0.0F, 0.0F, -1.0F );
        psGeom_Generate->m_psVertex[31].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1( -0.5F, 0.5F, -0.5F );
        psGeom_Generate->m_psVertex[31].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1( 0.0F, 0.0F, -1.0F );
        psGeom_Generate->m_psVertex[32].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1( 0.5F, 0.5F, -0.5F );
        psGeom_Generate->m_psVertex[32].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1( 0.0F, 0.0F, -1.0F );
        psGeom_Generate->m_psVertex[33].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1( -0.5F, -0.5F, -0.5F );
        psGeom_Generate->m_psVertex[33].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1( 0.0F, 0.0F, -1.0F );
        psGeom_Generate->m_psVertex[34].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1( 0.5F, 0.5F, -0.5F );
        psGeom_Generate->m_psVertex[34].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1( 0.0F, 0.0F, -1.0F );
        psGeom_Generate->m_psVertex[35].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1( 0.5F, -0.5F, -0.5F );
        psGeom_Generate->m_psVertex[35].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1( 0.0F, 0.0F, -1.0F );

        for (uiIndex = 0; uiIndex < 36; ++uiIndex)
        {
            psGeom_Generate->m_puiIndex[uiIndex] = uiIndex;
        };

        psGeom_Generate->m_nuiIndex = 36u;
        psGeom_Generate->m_nuiVertex = 36u;
    };
}


/* ---- tgKN_GPU_DBG_Init_Mesh_Plane --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_DBG_Init_Mesh_Plane( TgKN_GPU_DBG_PM_Generate_PC psGeom_Generate )
{
    if (nullptr == psGeom_Generate->m_psVertex || 0 == psGeom_Generate->m_nuiMax_Vertex || nullptr == psGeom_Generate->m_puiIndex || 0 == psGeom_Generate->m_nuiMax_Index)
    {
        psGeom_Generate->m_nuiMax_Index = 12u;
        psGeom_Generate->m_nuiMax_Vertex = 4u;
        return;
    }
    else
    {
        psGeom_Generate->m_psVertex[0].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1( -1.0F, 0.0F, -1.0F );
        psGeom_Generate->m_psVertex[0].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1( 0.0F, 1.0F, 0.0F );
        psGeom_Generate->m_psVertex[1].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1( -1.0F, 0.0F, 1.0F );
        psGeom_Generate->m_psVertex[1].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1( 0.0F, 1.0F, 0.0F );
        psGeom_Generate->m_psVertex[2].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1( 1.0F, 0.0F, 1.0F );
        psGeom_Generate->m_psVertex[2].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1( 0.0F, 1.0F, 0.0F );
        psGeom_Generate->m_psVertex[3].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1( 1.0F, 0.0F, -1.0F );
        psGeom_Generate->m_psVertex[3].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1( 0.0F, 1.0F, 0.0F );
        psGeom_Generate->m_nuiVertex = 4u;

        psGeom_Generate->m_puiIndex[0] = 0;
        psGeom_Generate->m_puiIndex[1] = 1;
        psGeom_Generate->m_puiIndex[2] = 2;
        psGeom_Generate->m_puiIndex[3] = 0;
        psGeom_Generate->m_puiIndex[4] = 2;
        psGeom_Generate->m_puiIndex[5] = 3;
        psGeom_Generate->m_puiIndex[6] = 0;
        psGeom_Generate->m_puiIndex[7] = 2;
        psGeom_Generate->m_puiIndex[8] = 1;
        psGeom_Generate->m_puiIndex[9] = 0;
        psGeom_Generate->m_puiIndex[10] = 3;
        psGeom_Generate->m_puiIndex[11] = 2;
        psGeom_Generate->m_nuiIndex = 12u;
    };
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgKN_GPU__CMD__Render_Debug_Text_Box_Right_Align ------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgKN_GPU__CMD__Render_Debug_Text_Box_Right_Align( STg2_KN_GPU_HLSL_CB_Debug_Text_PC psText_Constant_Buffer, TgRSIZE_C uiBuffer_Index, TgFLOAT32_C fText_Start_Z )
{
    TgRSIZE                             uiRight_Align_Index = uiBuffer_Index - 1;
    TgFLOAT32_C                         fCurrentY = psText_Constant_Buffer->m_vText_Offset[uiRight_Align_Index].y;
    TgFLOAT32_C                         fOffsetX = fText_Start_Z - psText_Constant_Buffer->m_vText_Offset[uiRight_Align_Index].x - psText_Constant_Buffer->m_vFont_Glyph_Scale_S.x;

    for (; ; -- uiRight_Align_Index)
    {
        psText_Constant_Buffer->m_vText_Offset[uiRight_Align_Index].x += fOffsetX;
        if (0 == uiRight_Align_Index || psText_Constant_Buffer->m_vText_Offset[uiRight_Align_Index].y != fCurrentY)
            break;
    }
}


/* ---- tgKN_GPU__CMD__Render_Debug_Line_Internal -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU__CMD__Render_Debug_Line_Internal( UTg2_KN_GPU_CMD_C uCMD, TgVEC_F32_04_1_C vS0, TgVEC_F32_04_1_C vC0, TgVEC_F32_04_1_C vS1, TgVEC_F32_04_1_C vC1,
                                                  STg2_KN_GPU_HLSL_CB_Debug_Line_CPC psCB )
{
    TgRSIZE                             uiEXEC = (uCMD.ps->m_tiCXT_WORK.m_uiI >> 16) & 0xFFFF;
    STg2_KN_GPU_CXT_EXEC_PC             psCXT_EXEC = g_asKN_GPU_CXT_EXEC + uiEXEC;

    TgPARAM_CHECK_INDEX( uiEXEC, g_asKN_GPU_CXT_EXEC );

    if (psCXT_EXEC->m_nuiLine_Vertex + 2 >= KTgKN_GPU_MAX_DEBUG_LINE_VERTEX_COUNT)
    {
        tgKN_GPU_EXT__CMD__Render_Debug_Line( uCMD, psCXT_EXEC->m_asLine_Vertex, psCXT_EXEC->m_nuiLine_Vertex, psCB );
        psCXT_EXEC->m_nuiLine_Vertex = 0;
    };

    psCXT_EXEC->m_asLine_Vertex[psCXT_EXEC->m_nuiLine_Vertex].m_vS0 = vS0;
    psCXT_EXEC->m_asLine_Vertex[psCXT_EXEC->m_nuiLine_Vertex].m_vCL = vC0;
    ++psCXT_EXEC->m_nuiLine_Vertex;

    psCXT_EXEC->m_asLine_Vertex[psCXT_EXEC->m_nuiLine_Vertex].m_vS0 = vS1;
    psCXT_EXEC->m_asLine_Vertex[psCXT_EXEC->m_nuiLine_Vertex].m_vCL = vC1;
    ++psCXT_EXEC->m_nuiLine_Vertex;
}


/* ==================================================================================================================================================================================
                                                                                                                                                                                 
                                                                                                                                                                                 
                                                                                                                                                                                 
                                                                                                                                                                                 
                                                                                                                                                                                 
                                                                                                                                                                                 
                                 2                                                       4                                                       8                               
                                 /\                                                      /\                                                      /\                              
                                /  \                                                    /  \                                                   7/__\                             
                               /    \                                                  /    \                                                  /\  /\                            
                              /      \                                               3/______\                                               6/__\/__\                           
                             /        \                                              /\      /\                                              /\  /\  /\                          
                            /          \                                            /  \    /  \                                           5/__\/__\/__\                         
                           /            \                                          /    \  /    \                                          /\  /\  /\  /\                        
                         1/______________\                                       2/______\/______\                                       4/__\/__\/__\/__\                       
                         /\              /\                                      /\      /\      /\                                      /\  /\  /\  /\  /\                      
                        /  \            /  \                                    /  \    /  \    /  \                                   3/__\/__\/__\/__\/__\                     
                       /    \          /    \                                  /    \  /    \  /    \                                  /\  /\  /\  /\  /\  /\                    
                      /      \        /      \                               1/______\/______\/______\                               2/__\/__\/__\/__\/__\/__\                   
                     /        \      /        \                              /\      /\      /\      /\                              /\  /\  /\  /\  /\  /\  /\                  
                    /          \    /          \                            /  \    /  \    /  \    /  \                           1/__\/__\/__\/__\/__\/__\/__\                 
                   /            \  /            \                          /    \  /    \  /    \  /    \                          /\  /\  /\  /\  /\  /\  /\  /\                
                  /______________\/______________\                        /______\/______\/______\/______\                        /__\/__\/__\/__\/__\/__\/__\/__\               
                 0                1               2                      0        1       2       3       4                      0    1   2   3   4   5   6   7   8              
                                                                                                                                                                                 
                 Points      Faces                                       Points      Faces                                         Points      Faces                             
                    6          4                                           15          16                                            45          64                              
                                                                                                                                                                                 
================================================================================================================================================================================== */

/* ---- tgKN_GPU_DBG_Tessellate_Mid_Point ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgUINT_E16 tgKN_GPU_DBG_Tessellate_Mid_Point( TgUINT_E16_C uiStart, TgUINT_E16_C uiEnd, TgKN_GPU_DBG_Geom_For_Tessellation_PCU psData )
{
    TgRSIZE                             uiIndex;
    TgUINT_E16                          uiRet;

    for (uiIndex = 0; uiIndex < psData->m_nuiEdge; ++uiIndex)
    {
        if ((psData->m_puiStart[uiIndex] == uiStart && psData->m_puiEnd[uiIndex] == uiEnd) || (psData->m_puiStart[uiIndex] == uiEnd && psData->m_puiEnd[uiIndex] == uiStart))
        {
            return (psData->m_puiMid[uiIndex]);
        };
    };

    /* Vertex not in the list, so we add it. */
    psData->m_puiStart[psData->m_nuiEdge] = uiStart;
    psData->m_puiEnd[psData->m_nuiEdge] = uiEnd;
    psData->m_puiMid[psData->m_nuiEdge] = (TgUINT_E16)psData->m_psGenerate->m_nuiVertex;

    /* Create new vertex. */

    if (nullptr != psData->m_psGenerate->m_psVertex)
    {
        TgVEC_F32_04_1_C                    vK2 = tgMH_Init_ELEM_F32_04_1( 0.5F, 0.5F, 0.5F, 0.0F );
        TgVEC_F32_04_1_C                    vK0 = tgMH_ADD_F32_04_1( psData->m_psGenerate->m_psVertex[uiStart].m_vS0, psData->m_psGenerate->m_psVertex[uiEnd].m_vS0 );
        TgVEC_F32_04_1_C                    vK1 = tgMH_MUL_F32_04_1( vK2, vK0 );
        TgUN_V128_C                         uKN = { .m_vF32_04_1 = tgMH_NORM_F32_04_1( vK1 ) };
        TgUN_V128_C                         uKS = { .m_vF32_04_1 = tgMH_MUL_F32_04_1( vK2, uKN.m_vF32_04_1 ) };

        TgCRITICAL(psData->m_psGenerate->m_nuiVertex < psData->m_psGenerate->m_nuiMax_Vertex);

        psData->m_psGenerate->m_psVertex[psData->m_psGenerate->m_nuiVertex].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1( uKS.m_vS_F32_04_1.x, uKS.m_vS_F32_04_1.y, uKS.m_vS_F32_04_1.z );
        psData->m_psGenerate->m_psVertex[psData->m_psGenerate->m_nuiVertex].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1( uKN.m_vS_F32_04_1.x, uKN.m_vS_F32_04_1.y, uKN.m_vS_F32_04_1.z );
    };

    TgCRITICAL( psData->m_nuiEdge + 1 < psData->m_nuiMax_Edge );

    uiRet = psData->m_puiMid[psData->m_nuiEdge];

    ++psData->m_psGenerate->m_nuiVertex;
    ++psData->m_nuiEdge;

    return uiRet;
}


/* ---- tgKN_GPU_DBG_Tessellate_Triangles ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgKN_GPU_DBG_Tessellate_Triangles( TgRSIZE uiIndex_Orig, TgRSIZE_C nuiMax_Index_Orig, TgRSIZE uiIndex, TgKN_GPU_DBG_Geom_For_Tessellation_PCU psData )
{
    for (; uiIndex_Orig < nuiMax_Index_Orig && uiIndex < psData->m_psGenerate->m_nuiMax_Index; uiIndex_Orig += 3, uiIndex += 12)
    {
        TgUINT_E16                          uiP0 = psData->m_puiIndex_Orig[uiIndex_Orig + 0];
        TgUINT_E16                          uiP1 = psData->m_puiIndex_Orig[uiIndex_Orig + 1];
        TgUINT_E16                          uiP2 = psData->m_puiIndex_Orig[uiIndex_Orig + 2];

        TgUINT_E16                          ui01 = tgKN_GPU_DBG_Tessellate_Mid_Point( uiP0, uiP1, psData );
        TgUINT_E16                          ui12 = tgKN_GPU_DBG_Tessellate_Mid_Point( uiP1, uiP2, psData );
        TgUINT_E16                          ui20 = tgKN_GPU_DBG_Tessellate_Mid_Point( uiP2, uiP0, psData );

        psData->m_psGenerate->m_puiIndex[uiIndex + 0u] = (TgUINT_E16)uiP0;
        psData->m_psGenerate->m_puiIndex[uiIndex + 1u] = (TgUINT_E16)ui01;
        psData->m_psGenerate->m_puiIndex[uiIndex + 2u] = (TgUINT_E16)ui20;

        psData->m_psGenerate->m_puiIndex[uiIndex + 3u] = (TgUINT_E16)ui20;
        psData->m_psGenerate->m_puiIndex[uiIndex + 4u] = (TgUINT_E16)ui01;
        psData->m_psGenerate->m_puiIndex[uiIndex + 5u] = (TgUINT_E16)ui12;

        psData->m_psGenerate->m_puiIndex[uiIndex + 6u] = (TgUINT_E16)ui20;
        psData->m_psGenerate->m_puiIndex[uiIndex + 7u] = (TgUINT_E16)ui12;
        psData->m_psGenerate->m_puiIndex[uiIndex + 8u] = (TgUINT_E16)uiP2;

        psData->m_psGenerate->m_puiIndex[uiIndex + 9u] = (TgUINT_E16)ui01;
        psData->m_psGenerate->m_puiIndex[uiIndex + 10u] = (TgUINT_E16)uiP1;
        psData->m_psGenerate->m_puiIndex[uiIndex + 11u] = (TgUINT_E16)ui12;
    };

    TgCRITICAL( uiIndex_Orig == nuiMax_Index_Orig );
    TgCRITICAL( psData->m_psGenerate->m_nuiMax_Index >= uiIndex );

    psData->m_psGenerate->m_nuiIndex = uiIndex;
}


/* ---- tgKN_GPU_DBG_Tessellate -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgKN_GPU_DBG_Tessellate( TgKN_GPU_DBG_PM_Generate_PCU psGenerate )
{
    TgRSIZE_C                           nbyIndex_Orig = psGenerate->m_nuiIndex*sizeof( TgUINT_E16 );
    TgKN_GPU_DBG_Geom_For_Tessellation  sTessellation;

    sTessellation.m_psGenerate = psGenerate;
    sTessellation.m_nuiMax_Edge = 2 * psGenerate->m_nuiVertex + psGenerate->m_nuiIndex;
    sTessellation.m_nuiEdge = 0u;
    sTessellation.m_puiStart = (TgUINT_E16_P)TgMALLOC_POOL( sTessellation.m_nuiMax_Edge * sizeof( TgUINT_E16 ) );
    sTessellation.m_puiEnd = (TgUINT_E16_P)TgMALLOC_POOL( sTessellation.m_nuiMax_Edge * sizeof( TgUINT_E16 ) );
    sTessellation.m_puiMid = (TgUINT_E16_P)TgMALLOC_POOL( sTessellation.m_nuiMax_Edge * sizeof( TgUINT_E16 ) );
    sTessellation.m_puiIndex_Orig = (TgUINT_E16_P)TgMALLOC_POOL( nbyIndex_Orig );
    sTessellation.m_nuiIndex_Orig = psGenerate->m_nuiIndex;

    TgMEMCPY_NOCACHE( sTessellation.m_puiIndex_Orig, nbyIndex_Orig, psGenerate->m_puiIndex, nbyIndex_Orig );

    /* The code overwrites the index buffer in place using the copy of the original buffer. */
    psGenerate->m_nuiIndex = 0u;

    /* Tessellate the sphere. */
    tgKN_GPU_DBG_Tessellate_Triangles( 0, sTessellation.m_nuiIndex_Orig, 0, &sTessellation );

    sTessellation.m_nuiMax_Edge = 0u;
    sTessellation.m_nuiEdge = 0u;

    TgFREE_POOL( sTessellation.m_puiStart );
    sTessellation.m_puiStart = nullptr;
    TgFREE_POOL( sTessellation.m_puiEnd );
    sTessellation.m_puiEnd = nullptr;
    TgFREE_POOL( sTessellation.m_puiMid );
    sTessellation.m_puiMid = nullptr;
    TgFREE_POOL( sTessellation.m_puiIndex_Orig );
    sTessellation.m_puiIndex_Orig = nullptr;
}


/* ---- tgKN_GPU_DBG_Tessellate_Capsule ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgKN_GPU_DBG_Tessellate_Capsule( TgRSIZE_PCU pnuiIndex_Tube, TgKN_GPU_DBG_PM_Generate_PCU psGenerate )
{
    TgRSIZE_C                           nbyIndex_Orig = psGenerate->m_nuiIndex*sizeof( TgUINT_E16 );
    TgRSIZE_C                           nbyVertex_Orig = psGenerate->m_nuiVertex * sizeof( STg2_KN_GPU_Vertex_Geom_02 );
    TgRSIZE_C                           nuiVertex_Orig = psGenerate->m_nuiVertex;
    TgRSIZE_C                           nuiIndex_Cap_Orig = psGenerate->m_nuiIndex - *pnuiIndex_Tube;

    TgKN_GPU_DBG_Geom_For_Tessellation  sTessellation;
    STg2_KN_GPU_Vertex_Geom_02_P        psVertex_Orig;
    TgRSIZE                             nuiIndex;
    TgRSIZE                             nuiNewIndex;
    TgUINT_E16                          nuiAdded_Vertex;

    sTessellation.m_psGenerate = psGenerate;
    sTessellation.m_nuiMax_Edge = psGenerate->m_nuiVertex + 4 * nuiIndex_Cap_Orig;
    sTessellation.m_nuiEdge = 0u;
    sTessellation.m_puiStart = (TgUINT_E16_P)TgMALLOC_POOL( sTessellation.m_nuiMax_Edge * sizeof( TgUINT_E16 ) );
    sTessellation.m_puiEnd = (TgUINT_E16_P)TgMALLOC_POOL( sTessellation.m_nuiMax_Edge * sizeof( TgUINT_E16 ) );
    sTessellation.m_puiMid = (TgUINT_E16_P)TgMALLOC_POOL( sTessellation.m_nuiMax_Edge * sizeof( TgUINT_E16 ) );
    sTessellation.m_puiIndex_Orig = (TgUINT_E16_P)TgMALLOC_POOL( nbyIndex_Orig );
    sTessellation.m_nuiIndex_Orig = psGenerate->m_nuiIndex;

    TgMEMCPY_NOCACHE( sTessellation.m_puiIndex_Orig, nbyIndex_Orig, psGenerate->m_puiIndex, nbyIndex_Orig );

    /* The code overwrites the index buffer in place using the copy of the original buffer. */
    psGenerate->m_nuiIndex = 0u;

    psVertex_Orig = (STg2_KN_GPU_Vertex_Geom_02_P)TgMALLOC_POOL( nbyVertex_Orig >> 1 );

    /* General reminder: our capsule is created as two demi-spheres that are then separated from each other and the resulting faces defined to fill out the capsule. Taking
                         advantage of that construction method, we copy off the second half of the vertices at this point since we will overwrite their location for implementation
                         simplicity. We can then copy them back when we tessellate the second half of the capsule. */

    if (nullptr != psGenerate->m_psVertex)
    {
        TgMEMCPY_NOCACHE( psVertex_Orig, (nbyVertex_Orig >> 1), psGenerate->m_psVertex + (psGenerate->m_nuiVertex >> 1), (nbyVertex_Orig >> 1) );
    }

    /* Start with only one side of the capsule vertices (as mentioned above). */
    psGenerate->m_nuiVertex >>= 1;

    /* Tessellate the first cap of the capsule. */
    tgKN_GPU_DBG_Tessellate_Triangles( 0, nuiIndex_Cap_Orig >> 1, 0, &sTessellation );

    /* Copy the vertices from the second cap into the vertex buffer. */
    if (nullptr != psGenerate->m_psVertex)
    {
        TgMEMCPY_NOCACHE( psGenerate->m_psVertex + psGenerate->m_nuiVertex, (nbyVertex_Orig >> 1), psVertex_Orig, (nbyVertex_Orig >> 1) );
    }

    nuiAdded_Vertex = (TgUINT_E16)(psGenerate->m_nuiVertex - (nuiVertex_Orig >> 1));
    psGenerate->m_nuiVertex += nuiVertex_Orig >> 1;

    /* Re-index the old index data to take into account the separation of all the new vertices. */
    for (nuiIndex = nuiIndex_Cap_Orig >> 1; nuiIndex < nuiIndex_Cap_Orig; ++nuiIndex)
    {
        TgVERIFY( sTessellation.m_puiIndex_Orig[nuiIndex] >= (nuiVertex_Orig >> 1) );
        sTessellation.m_puiIndex_Orig[nuiIndex] += nuiAdded_Vertex;
    };

    for (; nuiIndex < sTessellation.m_nuiIndex_Orig; ++nuiIndex)
    {
        if (sTessellation.m_puiIndex_Orig[nuiIndex] >= (nuiVertex_Orig >> 1) )
        {
            sTessellation.m_puiIndex_Orig[nuiIndex] += nuiAdded_Vertex;
        };
    };

    /* Tessellate the first second of the capsule. */
    tgKN_GPU_DBG_Tessellate_Triangles( nuiIndex_Cap_Orig >> 1, nuiIndex_Cap_Orig, psGenerate->m_nuiIndex, &sTessellation );

    /* Do not tessellate the faces in the tube section - create the additional faces caused by the extra vertices in the caps. */

    for (nuiIndex = nuiIndex_Cap_Orig, nuiNewIndex = psGenerate->m_nuiIndex; nuiIndex < sTessellation.m_nuiIndex_Orig && nuiNewIndex < psGenerate->m_nuiMax_Index; nuiIndex += 6, nuiNewIndex += 12)
    {
        TgUINT_E16_C                        uiP0 = sTessellation.m_puiIndex_Orig[nuiIndex + 0];
        TgUINT_E16_C                        uiP1 = sTessellation.m_puiIndex_Orig[nuiIndex + 1];
        TgUINT_E16_C                        uiP2 = sTessellation.m_puiIndex_Orig[nuiIndex + 2];
        TgUINT_E16_C                        uiP3 = sTessellation.m_puiIndex_Orig[nuiIndex + 5];

        TgUINT_E16                          ui02 = tgKN_GPU_DBG_Tessellate_Mid_Point( uiP2, uiP0, &sTessellation );
        TgUINT_E16                          ui13 = tgKN_GPU_DBG_Tessellate_Mid_Point( uiP1, uiP3, &sTessellation );

        psGenerate->m_puiIndex[nuiNewIndex + 0] = uiP0;
        psGenerate->m_puiIndex[nuiNewIndex + 1] = uiP1;
        psGenerate->m_puiIndex[nuiNewIndex + 2] = ui02;

        psGenerate->m_puiIndex[nuiNewIndex + 3] = ui02;
        psGenerate->m_puiIndex[nuiNewIndex + 4] = uiP1;
        psGenerate->m_puiIndex[nuiNewIndex + 5] = ui13;

        psGenerate->m_puiIndex[nuiNewIndex + 6] = ui02;
        psGenerate->m_puiIndex[nuiNewIndex + 7] = ui13;
        psGenerate->m_puiIndex[nuiNewIndex + 8] = uiP2;

        psGenerate->m_puiIndex[nuiNewIndex + 9] = uiP2;
        psGenerate->m_puiIndex[nuiNewIndex + 10] = ui13;
        psGenerate->m_puiIndex[nuiNewIndex + 11] = uiP3;
    };

    *pnuiIndex_Tube = nuiNewIndex - psGenerate->m_nuiIndex;
    psGenerate->m_nuiIndex = nuiNewIndex;

    TgFREE_POOL( psVertex_Orig );
    psVertex_Orig = nullptr;

    sTessellation.m_nuiMax_Edge = 0u;
    sTessellation.m_nuiEdge = 0u;

    TgFREE_POOL( sTessellation.m_puiStart );
    sTessellation.m_puiStart = nullptr;
    TgFREE_POOL( sTessellation.m_puiEnd );
    sTessellation.m_puiEnd = nullptr;
    TgFREE_POOL( sTessellation.m_puiMid );
    sTessellation.m_puiMid = nullptr;
    TgFREE_POOL( sTessellation.m_puiIndex_Orig );
    sTessellation.m_puiIndex_Orig = nullptr;
}


/*# TgCOMPILE__RENDER_DEBUG_OUTPUT */
#endif
