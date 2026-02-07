/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Kernel [GPU] - Debug [Geom-Text-UI].c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/* == Kernel ===================================================================================================================================================================== */
#if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Types and Functions                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgTYPE_STRUCT( TgKN_GPU_DBG_Geom_For_Tessellation, )
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
    TgFLOAT32_C ARG0, TgFLOAT32_C ARG1, TgVEC_S_F32_04_1_P ARG2, TgVEC_S_F32_04_1_P ARG3 );

static TgVOID
tgKN_GPU_DBG_Tessellate(
    TgKN_GPU_DBG_PM_Generate_PCU ARG0 );

static TgVOID
tgKN_GPU_DBG_Tessellate_Capsule(
    TgRSIZE_PCU OUT0, TgKN_GPU_DBG_PM_Generate_PCU ARG1 );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_GPU__CMD__Init_DBG_Render_DESC -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU__CMD__Init_DBG_Render_DESC( STg2_KN_GPU_DBG_Render_DESC_P psDBG_Render_DESC, STg2_KN_GPU_CMD_PC psCMD, STg2_KN_GPU_Camera_CPC psCamera )
{
    TgFLOAT32                           fWidth, fHeight;

    TgPARAM_CHECK( nullptr != psCMD );
    TgPARAM_CHECK( nullptr != psDBG_Render_DESC );

    fWidth = (TgFLOAT32)psCMD->m_uiRender_Target_Width;
    fHeight = (TgFLOAT32)psCMD->m_uiRender_Target_Height;

    psDBG_Render_DESC->m_vLight_Ambient = tgMH_Init_ELEM_F32_04_1( 0.01F, 0.01F, 0.01F, 1.0F );

    /* Key Light */
    psDBG_Render_DESC->m_avLight_Direction_Colour[0] = tgMH_Init_ELEM_F32_04_1( 1.0F, 0.95F, 0.8F, 1.0F );
    psDBG_Render_DESC->m_avLight_Direction[0] = tgMH_Init_ELEM_F32_04_1(-0.5F, -0.5F, -0.7F, 0.0F );
    psDBG_Render_DESC->m_avLight_Direction[0] = tgMH_NORM_F32_04_1( psDBG_Render_DESC->m_avLight_Direction[0] );

    /* Fill Light */
    psDBG_Render_DESC->m_avLight_Direction_Colour[1] = tgMH_Init_ELEM_F32_04_1( 0.28F, 0.32F, 0.4F, 1.0F );
    psDBG_Render_DESC->m_avLight_Direction[1] = tgMH_Init_ELEM_F32_04_1( 0.3F, -0.8F, -0.3F, 0.0F );
    psDBG_Render_DESC->m_avLight_Direction[1] = tgMH_NORM_F32_04_1( psDBG_Render_DESC->m_avLight_Direction[1] );

    /* Back Light */
    psDBG_Render_DESC->m_avLight_Direction_Colour[2] = tgMH_Init_ELEM_F32_04_1( 0.6F, 0.6F, 0.54F, 1.0F );
    psDBG_Render_DESC->m_avLight_Direction[2] = tgMH_Init_ELEM_F32_04_1( 0.2F, 0.8F, -0.5F, 0.0F );
    psDBG_Render_DESC->m_avLight_Direction[2] = tgMH_NORM_F32_04_1( psDBG_Render_DESC->m_avLight_Direction[2] );

    psDBG_Render_DESC->m_fMin_Line_Length = 1.0f / tgCM_MAX_F32(fWidth, fHeight);
    psDBG_Render_DESC->m_fMax_Distance = psCamera ? psCamera->m_sConfiguration.m_fFar : 1000.0F;
    psDBG_Render_DESC->m_fGlobal_Line_Width = 1.0f;
}


/* ---- tgKN_GPU__CMD__Render_Debug_Text_Box ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU__CMD__Render_Debug_Text_Box( STg2_KN_GPU_CMD_PC psCMD, STg2_KN_GPU_DBG_Text_CI_CPC psText_CI )
{
    TgRSIZE                             uiEXEC = (psCMD->m_tiCXT_WORK.m_uiI >> 16) & 0xFFFF;
    STg2_KN_GPU_CXT_EXEC_PC             psCXT_EXEC = g_asKN_GPU_CXT_EXEC + uiEXEC;

    TgFLOAT32_C                         fRT_Width = (float)psCMD->m_uiRender_Target_Width;
    TgFLOAT32_C                         fRT_Height = (float)psCMD->m_uiRender_Target_Height;

    STg2_KN_GPU_FONT_TX                 sFont_TX;
    STg2_KN_GPU_DBG_Text                sText;
    TgVEC_S_F32_04_1_P                  pvText_Offsets;
    TgRSIZE                             nuiText_Offsets;
    TgRSIZE                             uiLine_Index;
    TgRSIZE                             uiText_Index;
    TgRSIZE                             uiBuffer_Index;
    TgRSIZE                             uiTextX,uiTextY;
    TgBOOL                              bEnd_Process;
    TgFLOAT32                           fScale_Sx;
    TgFLOAT32                           fText_Start_X;
    TgFLOAT32                           fText_Start_Y, fLimitT;
    TgFLOAT32                           fText_Start_Z;
    TgFLOAT32                           fText_Start_W, fLimitB;

    TgPARAM_CHECK(nullptr != psCMD);
    TgPARAM_CHECK_INDEX(uiEXEC, g_asKN_GPU_CXT_EXEC);

    TgPARAM_CHECK( nullptr != psCMD );
    TgPARAM_CHECK( nullptr != psText_CI );

    tgKN_GPU_Query_DOS_Font_ROM_TX( &sFont_TX, psText_CI->m_enFont );
    fScale_Sx = (sFont_TX.m_fFntX * 2.0F) / fRT_Width;

    sText.m_uiSelect_Default_Texture_Index = (uint32_t)psCXT_EXEC->m_uiDOS_Font_Texture_Index[psText_CI->m_enFont];
    sText.m_vFont_Glyph_Scale_S.x = fScale_Sx;  // Verts are 0->1, NDC is -1->1
    sText.m_vFont_Glyph_Scale_S.y = (sFont_TX.m_fFntY * 2.0F) / fRT_Height; // Verts are 0->1, NDC is -1->1
    sText.m_vFont_Glyph_Scale_S.z = fRT_Width;
    sText.m_vFont_Glyph_Scale_S.w = fRT_Height;
    sText.m_vFont_Glyph_Scale_UV.x = sFont_TX.m_fFntX; // Vulkan pixel centre is at (0.5,0.5)
    sText.m_vFont_Glyph_Scale_UV.y = sFont_TX.m_fFntY; // Vulkan pixel centre is at (0.5,0.5)
    sText.m_vFont_Glyph_Scale_UV.z = sFont_TX.m_fTX_Cell_X;
    sText.m_vFont_Glyph_Scale_UV.w = sFont_TX.m_fTX_Cell_Y;
    sText.m_vText_Colour = psText_CI->m_vText_Colour;

    /* Validate that the box can contain at least one character */
    if (psText_CI->m_vText_Box_V.z - psText_CI->m_vText_Box_V.x <= sText.m_vFont_Glyph_Scale_S.x)
    {
        return;
    }

    /* Validate that the box can contain at least one line */
    if (psText_CI->m_vText_Box_V.w - psText_CI->m_vText_Box_V.y <= sText.m_vFont_Glyph_Scale_S.y)
    {
        return;
    }

    /* Test to see if the text would automatically render off screen. */
    if (psText_CI->m_vText_Box_V.z <= -1.0F || psText_CI->m_vText_Box_V.x >= 1.0F || psText_CI->m_vText_Box_V.w <= -1.0F || psText_CI->m_vText_Box_V.y >= 1.0F)
    {
        return;
    }

    /* No lines provided to the function. */
    if (nullptr == psText_CI->m_puszText)
    {
        return;
    }

    for (uiLine_Index = 0, nuiText_Offsets = 0; uiLine_Index < psText_CI->m_nuiText; ++uiLine_Index )
    {
        if (nullptr == psText_CI->m_puszText[uiLine_Index])
        {
            return;
        }

        if (TgFAILED(tgUSZ_Length_Count(&nuiText_Offsets, psText_CI->m_puszText[uiLine_Index], KTgMAX_RSIZE)))
        {
            return;
        }
    }

    /* No text in the lines provided to the function. */
    if (0 == nuiText_Offsets)
    {
        return;
    }

    pvText_Offsets = (TgVEC_S_F32_04_1_P)TgMALLOC_POOL( sizeof( TgVEC_S_F32_04_1 ) * nuiText_Offsets + 16 );
    if (nullptr == pvText_Offsets)
    {
        TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to allocate memory for text rendering." );
        return;
    }

    /* Start converting the text stream into positions and UVs for rendering. The system attempts to do basic formatting like word wrapping (if indicated), and new lines. */

    uiBuffer_Index = 0;
    uiText_Index = 0;
    uiTextX = 0;
    uiTextY = 0;
    bEnd_Process = false;

    fText_Start_X = psText_CI->m_vText_Box_V.x + 2.0F / fRT_Width;
    fText_Start_Y = psText_CI->m_vText_Box_V.y + 2.0F / fRT_Height;
    fText_Start_Z = psText_CI->m_vText_Box_V.z - 2.0F / fRT_Width;
    fText_Start_W = psText_CI->m_vText_Box_V.w - 2.0F / fRT_Height;
    fLimitT = tgCM_MAX_F32( fText_Start_Y, -1.0F );
    fLimitB = tgCM_MIN_F32( fText_Start_W - sText.m_vFont_Glyph_Scale_S.y*2, 1.0F );

    if (psText_CI->m_bDraw_Background)
    {
        STg2_KN_GPU_DBG_Quad            sUI_Constant_Buffer;

        tgMM_Set_U08_0x00( &sUI_Constant_Buffer, sizeof( sUI_Constant_Buffer ) );
        sUI_Constant_Buffer.m_vRect_UI.x = psText_CI->m_vText_Box_V.x;
        sUI_Constant_Buffer.m_vRect_UI.y = psText_CI->m_vText_Box_V.y;
        sUI_Constant_Buffer.m_vRect_UI.z = psText_CI->m_vText_Box_V.z;
        sUI_Constant_Buffer.m_vRect_UI.w = psText_CI->m_vText_Box_V.w;
        sUI_Constant_Buffer.m_vUI_Colour = psText_CI->m_vBackground_Colour;
        sUI_Constant_Buffer.m_uiSelect_Default_Texture_Index = 1;

        tgKN_GPU_EXT__CMD__Render_Debug_Quad( psCMD, &sUI_Constant_Buffer );
    }

    if (psText_CI->m_bDraw_First_Line)
    {
        STg2_KN_GPU_DBG_Quad            sUI_Constant_Buffer;

        tgMM_Set_U08_0x00( &sUI_Constant_Buffer, sizeof( sUI_Constant_Buffer ) );
        sUI_Constant_Buffer.m_vRect_UI.x = psText_CI->m_vText_Box_V.x;
        sUI_Constant_Buffer.m_vRect_UI.y = psText_CI->m_vText_Box_V.w - sText.m_vFont_Glyph_Scale_S.y - 4.0F / sText.m_vFont_Glyph_Scale_S.w;
        sUI_Constant_Buffer.m_vRect_UI.z = psText_CI->m_vText_Box_V.z;
        sUI_Constant_Buffer.m_vRect_UI.w = psText_CI->m_vText_Box_V.w;
        sUI_Constant_Buffer.m_vUI_Colour = psText_CI->m_vBackground_First_Line;
        sUI_Constant_Buffer.m_uiSelect_Default_Texture_Index = 1;

        tgKN_GPU_EXT__CMD__Render_Debug_Quad( psCMD, &sUI_Constant_Buffer );
    }

    /* For every line in the array of pointers in the parameter data structure. */
    for (uiLine_Index = 0; !bEnd_Process && uiLine_Index < psText_CI->m_nuiText; ++uiLine_Index)
    {
        TgCHAR_U8_CPC                       uszText = psText_CI->m_puszText[uiLine_Index];

        if (nullptr == uszText || 0 == uszText[0])
            break;

        do
        {
            /* For every letter in the line that we are processing */
            for (; !bEnd_Process && uiBuffer_Index < nuiText_Offsets && uszText[uiText_Index]; ++uiBuffer_Index, ++uiText_Index)
            {
                if (128 <= uszText[uiText_Index])
                    continue;

                /* Treat (Windows) CRLF and (Unix) LF correctly (start a new line). */

                if ('\n' == uszText[uiText_Index])
                {
                    uiTextX = 0;
                    ++uiTextY;
                    --uiBuffer_Index;
                    if (psText_CI->m_bRight_Aligned && uiBuffer_Index > 0) {
                        tgKN_GPU__CMD__Render_Debug_Text_Box_Right_Align( fScale_Sx, fText_Start_Z, pvText_Offsets + uiBuffer_Index - 1, pvText_Offsets );
                    }
                    continue;
                };

                if ('\r' == uszText[uiText_Index] && '\n' == uszText[uiText_Index+1])
                {
                    uiTextX = 0;
                    ++uiTextY;
                    ++uiText_Index;
                    --uiBuffer_Index;
                    if (psText_CI->m_bRight_Aligned && uiBuffer_Index > 0) {
                        tgKN_GPU__CMD__Render_Debug_Text_Box_Right_Align( fScale_Sx, fText_Start_Z, pvText_Offsets + uiBuffer_Index - 1, pvText_Offsets );
                    }
                    continue;
                };

                pvText_Offsets[uiBuffer_Index].x = fText_Start_X + (float)uiTextX * sText.m_vFont_Glyph_Scale_S.x;
                ++uiTextX;

                /* Wrap the string (or consume the character, but do not render) if we are now at the right boundary of the text box. */

                if (psText_CI->m_bWord_Wrap && (pvText_Offsets[uiBuffer_Index].x + sText.m_vFont_Glyph_Scale_S.x >= fText_Start_Z))
                {
                    pvText_Offsets[uiBuffer_Index].x = fText_Start_X;
                    uiTextX = 0;
                    ++uiTextY;
                }

                /* Consume the character but do not create a render instance since it will be off-screen. */

                if (pvText_Offsets[uiBuffer_Index].x <= -1.0F)
                {
                    continue;
                }

                if (pvText_Offsets[uiBuffer_Index].x >= 1.0F)
                {
                    continue;
                }

                /* Determine the y position of the line (allowing for strings to be go down or up the page) and check to see if we now exceed the box or viewport. */
                if (psText_CI->m_bLine_Change_Is_Positive)
                {
                    pvText_Offsets[uiBuffer_Index].y  = fText_Start_W;
                    pvText_Offsets[uiBuffer_Index].y -= (float)(uiTextY + 1) * sText.m_vFont_Glyph_Scale_S.y;

                    if (uiTextY > 0 && psText_CI->m_bDraw_First_Line) {
                        pvText_Offsets[uiBuffer_Index].y -= 8.0F / sText.m_vFont_Glyph_Scale_S.w;
                    }

                    /* Stop processing the string(s) if there is no longer any room for further lines in the text box. */
                    if (pvText_Offsets[uiBuffer_Index].y <= fLimitT)
                    {
                        bEnd_Process = true;
                        break;
                    }
                }
                else
                {
                    pvText_Offsets[uiBuffer_Index].y = fText_Start_Y + (float)(uiTextY) * sText.m_vFont_Glyph_Scale_S.y;

                    if (uiTextY > 0 && psText_CI->m_bDraw_First_Line) {
                        pvText_Offsets[uiBuffer_Index].y += 8.0F / sText.m_vFont_Glyph_Scale_S.w;
                    }

                    /* Stop processing the string(s) if there is no longer any room for further lines in the text box. */
                    if (pvText_Offsets[uiBuffer_Index].y + sText.m_vFont_Glyph_Scale_S.y >= fLimitB)
                    {
                        bEnd_Process = true;
                        break;
                    }
                }

                /* Compute the UV values. */
                pvText_Offsets[uiBuffer_Index].z = (float)(uszText[uiText_Index] % (TgUINT_E32)(sFont_TX.m_fTX_X / sFont_TX.m_fTX_Cell_X));
                pvText_Offsets[uiBuffer_Index].w = (float)(uszText[uiText_Index] / (TgUINT_E32)(sFont_TX.m_fTX_X / sFont_TX.m_fTX_Cell_X));
            };

            if ((bEnd_Process && uiBuffer_Index > 0) || (uiBuffer_Index >= nuiText_Offsets))
            {
                if (psText_CI->m_bRight_Aligned && uiBuffer_Index > 0) {
                    tgKN_GPU__CMD__Render_Debug_Text_Box_Right_Align(fScale_Sx, fText_Start_Z, pvText_Offsets + uiBuffer_Index - 1, pvText_Offsets);
                }
                tgKN_GPU_EXT__CMD__Render_Debug_Text( psCMD, &sText, pvText_Offsets, uiBuffer_Index );
                uiBuffer_Index = 0;
            };

        } while (!bEnd_Process && psText_CI->m_puszText[uiLine_Index][uiText_Index]);

        uiTextX = 0;
        ++uiTextY;
        if (psText_CI->m_bRight_Aligned && uiBuffer_Index > 0) {
            tgKN_GPU__CMD__Render_Debug_Text_Box_Right_Align( fScale_Sx, fText_Start_Z, pvText_Offsets + uiBuffer_Index - 1, pvText_Offsets );
        }
    };

    if (!bEnd_Process && uiBuffer_Index > 0)
    {
        if (psText_CI->m_bRight_Aligned && uiBuffer_Index > 0) {
            tgKN_GPU__CMD__Render_Debug_Text_Box_Right_Align(fScale_Sx, fText_Start_Z, pvText_Offsets + uiBuffer_Index - 1, pvText_Offsets);
        }
        tgKN_GPU_EXT__CMD__Render_Debug_Text( psCMD, &sText, pvText_Offsets, uiBuffer_Index);
        uiBuffer_Index = 0;
    };

    TgFREE_POOL( pvText_Offsets );
}


/* ---- tgKN_GPU__CMD__Add_Debug_Line -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU__CMD__Add_Debug_Line( STg2_KN_GPU_CMD_PC psCMD, TgVEC_F32_04_1_C vS0, TgVEC_F32_04_1_C vCL0, TgVEC_F32_04_1_C vS1, TgVEC_F32_04_1_C vCL1, TgVEC_F32_04_1_C vW )
{
    STg2_KN_GPU_CMD_DBG_P               psCMD_DBG;
    TgRSIZE                             uiLine_Index, nuiLine_Page;

    if (TgFAILED(tgKN_GPU_EXT__CMD__Command_Debug(&psCMD_DBG, psCMD)))
    {
        return (KTgE_FAIL);
    }

    uiLine_Index = TgSTD_ATOMIC(fetch_add)( &psCMD_DBG->m_xnuiLine, 1u );
    nuiLine_Page = tgCM_CEL_ALGN_PW2_UMAX( (uiLine_Index + 1u) * sizeof( STg2_KN_GPU_DBG_Line ), tgMM_Page_Size() ) / tgMM_Page_Size();

    if (uiLine_Index >= KTgKN_GPU_MAX_DBG_STORAGE_LINE)
    {
        TgWARNING_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Debug line buffer full. Dropping line." );
        return (KTgE_FAIL);
    }

    if (nuiLine_Page > psCMD_DBG->m_nuiLine_Page)
    {
        /* I don't want to lock every time we call, however, this leaves it open to a race condition where the array is flushed between the increment and the commit. */
        tgCM_UT_LF__SN__Lock_Spin(&psCMD_DBG->m_sLine_Lock);
        psCMD_DBG->m_psLine = (STg2_KN_GPU_DBG_Line_P)TgCOMMIT_VIRTUAL( psCMD_DBG->m_psLine, 0, nuiLine_Page * tgMM_Page_Size());
        if (nullptr == psCMD_DBG->m_psLine)
        {
            TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to allocate memory for debug line rendering." );
            tgCM_UT_LF__SN__Signal(&psCMD_DBG->m_sLine_Lock);
            return (KTgE_FAIL);
        }
        psCMD_DBG->m_nuiLine_Page = nuiLine_Page;
        tgCM_UT_LF__SN__Signal(&psCMD_DBG->m_sLine_Lock);
    }

    psCMD_DBG->m_psLine[uiLine_Index].m_vStart_Width = tgMH_SEL_F32_04_1( vS0, vW, KTg000F_V128.m_vF32_04_1 );
    psCMD_DBG->m_psLine[uiLine_Index].m_vStart_Colour = vCL0;
    psCMD_DBG->m_psLine[uiLine_Index].m_vEnd_Width = tgMH_SEL_F32_04_1( vS1, vW, KTg000F_V128.m_vF32_04_1 );
    psCMD_DBG->m_psLine[uiLine_Index].m_vEnd_Colour = vCL1;
    return (KTgS_OK);
}


/* ---- tgKN_GPU__CMD__Render_Debug_Line ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU__CMD__Render_Debug_Line( STg2_KN_GPU_CMD_PC psCMD )
{
    tgKN_GPU_EXT__CMD__Render_Debug_Line( psCMD );
}


/* ---- tgKN_GPU__CMD__Render_Debug_Parabola ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
//TgVOID tgKN_GPU__CMD__Render_Debug_Parabola( STg2_KN_GPU_CMD_PC psCMD, STg2_Parabola_CPCU )
//{
//}


/* ---- tgKN_GPU__CMD__Render_Debug_Axes ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU__CMD__Render_Debug_Axes( STg2_KN_GPU_CMD_PC psCMD, TgVEC_F32_04_3_CPCU pxX0, TgVEC_F32_04_1 vScale )
{
    TgVEC_F32_04_1_C                    vK0 = tgMH_MUL_F32_04_1( vScale, pxX0->m_avCol[0] );
    TgVEC_F32_04_1_C                    vK1 = tgMH_MUL_F32_04_1( vScale, pxX0->m_avCol[1] );
    TgVEC_F32_04_1_C                    vK2 = tgMH_MUL_F32_04_1( vScale, pxX0->m_avCol[2] );
    TgVEC_F32_04_1_C                    vK3 = tgMH_ADD_F32_04_1( pxX0->m_avCol[0], vK0 );
    TgVEC_F32_04_1_C                    vK4 = tgMH_ADD_F32_04_1( pxX0->m_avCol[1], vK1 );
    TgVEC_F32_04_1_C                    vK5 = tgMH_ADD_F32_04_1( pxX0->m_avCol[2], vK2 );

    tgKN_GPU__CMD__Add_Debug_Line( psCMD, pxX0->m_avCol[0], KTg_BLUE_G10_P709_F32_04, vK3, KTg_BLUE_G10_P709_F32_04, KTgONE_F32_04_1 );
    tgKN_GPU__CMD__Add_Debug_Line( psCMD, pxX0->m_avCol[1], KTg_GREEN_G10_P709_F32_04, vK4, KTg_GREEN_G10_P709_F32_04, KTgONE_F32_04_1 );
    tgKN_GPU__CMD__Add_Debug_Line( psCMD, pxX0->m_avCol[2], KTg_RED_G10_P709_F32_04, vK5, KTg_RED_G10_P709_F32_04, KTgONE_F32_04_1 );
}


/* ---- tgKN_GPU__CMD__Render_Debug_nGon ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU__CMD__Render_Debug_nGon( STg2_KN_GPU_CMD_PC psCMD, TgVEC_F32_04_1 vCL0, TgVEC_F32_04_3_CPCU pxX0, TgFLOAT32_C fScale, TgSINT_E32_C niSide )
{
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

        for (iIndex = 1; iIndex < niSide; ++iIndex)
        {
            tgPM_SINCOS_F32( &uS1.m_vS_F32_04_1.x, &uS1.m_vS_F32_04_1.z, ((TgFLOAT32)iIndex)*fCutAngle );
            uS1.m_vS_F32_04_1.x *= fScale;
            uS1.m_vS_F32_04_1.z *= fScale;
            uS1.m_vF32_04_1 = tgMH_TX_P_F32_04_3( uS1.m_vF32_04_1, pxX0 );
            tgKN_GPU__CMD__Add_Debug_Line( psCMD, uS0.m_vF32_04_1, vCL0, uS1.m_vF32_04_1, vCL0, KTgONE_F32_04_1 );
            uS0.m_vF32_04_1 = uS1.m_vF32_04_1;
        };

        uS1.m_vS_F32_04_1 = tgMH_Init_ELEM_S_F32_04_1( fScale, 0.0F, 0.0F, 1.0F );
        uS1.m_vF32_04_1 = tgMH_TX_P_F32_04_3( uS1.m_vF32_04_1, pxX0 );

        tgKN_GPU__CMD__Add_Debug_Line( psCMD, uS0.m_vF32_04_1, vCL0, uS1.m_vF32_04_1, vCL0, KTgONE_F32_04_1 );
    }
}


/* ---- tgKN_GPU__CMD__Render_Debug_Frustum -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU__CMD__Render_Debug_Frustum( STg2_KN_GPU_CMD_PC psCMD, TgVEC_F32_04_1 vCL0, TgVEC_F32_04_4_CPCU pxS2C, TgVEC_F32_04_4_CPCU pxC2W )
{
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

    tgKN_GPU__CMD__Add_Debug_Line( psCMD, vD0, vCL0, vD1, vCL0, KTgONE_F32_04_1 );
    tgKN_GPU__CMD__Add_Debug_Line( psCMD, vD1, vCL0, vD3, vCL0, KTgONE_F32_04_1 );
    tgKN_GPU__CMD__Add_Debug_Line( psCMD, vD3, vCL0, vD2, vCL0, KTgONE_F32_04_1 );
    tgKN_GPU__CMD__Add_Debug_Line( psCMD, vD2, vCL0, vD0, vCL0, KTgONE_F32_04_1 );
    tgKN_GPU__CMD__Add_Debug_Line( psCMD, vD7, vCL0, vD6, vCL0, KTgONE_F32_04_1 );
    tgKN_GPU__CMD__Add_Debug_Line( psCMD, vD6, vCL0, vD4, vCL0, KTgONE_F32_04_1 );
    tgKN_GPU__CMD__Add_Debug_Line( psCMD, vD4, vCL0, vD5, vCL0, KTgONE_F32_04_1 );
    tgKN_GPU__CMD__Add_Debug_Line( psCMD, vD5, vCL0, vD7, vCL0, KTgONE_F32_04_1 );
    tgKN_GPU__CMD__Add_Debug_Line( psCMD, vD0, vCL0, vD4, vCL0, KTgONE_F32_04_1 );
    tgKN_GPU__CMD__Add_Debug_Line( psCMD, vD1, vCL0, vD5, vCL0, KTgONE_F32_04_1 );
    tgKN_GPU__CMD__Add_Debug_Line( psCMD, vD2, vCL0, vD6, vCL0, KTgONE_F32_04_1 );
    tgKN_GPU__CMD__Add_Debug_Line( psCMD, vD3, vCL0, vD7, vCL0, KTgONE_F32_04_1 );

    tgKN_GPU__CMD__Add_Debug_Line( psCMD, vS0, KTg_MAGENTA_G10_P709_F32_04, vD1, KTg_MAGENTA_G10_P709_F32_04, KTgONE_F32_04_1 );
    tgKN_GPU__CMD__Add_Debug_Line( psCMD, vS0, KTg_MAGENTA_G10_P709_F32_04, vD3, KTg_MAGENTA_G10_P709_F32_04, KTgONE_F32_04_1 );
    tgKN_GPU__CMD__Add_Debug_Line( psCMD, vS0, KTg_MAGENTA_G10_P709_F32_04, vD5, KTg_MAGENTA_G10_P709_F32_04, KTgONE_F32_04_1 );
    tgKN_GPU__CMD__Add_Debug_Line( psCMD, vS0, KTg_MAGENTA_G10_P709_F32_04, vD7, KTg_MAGENTA_G10_P709_F32_04, KTgONE_F32_04_1 );
}


/* ---- tgKN_GPU__CMD__Render_Debug_Camera_Frustum ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU__CMD__Render_Debug_Camera_Frustum( STg2_KN_GPU_CMD_PC psCMD, TgVEC_F32_04_1_C vCL0, STg2_KN_GPU_Camera_CPCU psCamera )
{
    tgKN_GPU__CMD__Render_Debug_Frustum( psCMD, vCL0, &psCamera->m_sCamera_Shared.m_avS2C, &psCamera->m_sCamera_Shared.m_avC2W );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Geometry Generation Functions                                                                                                                                         */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_GPU_DBG_Init_Mesh_Sphere -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_DBG_Init_Mesh_Sphere( TgKN_GPU_DBG_PM_Generate_PC psGeom_Generate )
{
    TgRSIZE_C                           nuiMax_Index_No_Tessellation = TgARRAY_COUNT(KTgGM_ICOSAHEDRON_PN_INDEX);
    TgRSIZE_C                           nuiBit_Max = (TgRSIZE)tgPM_BSR_UMAX((TgRSIZE)KTgMAX_U16 / nuiMax_Index_No_Tessellation) + 1u;
    TgRSIZE_C                           uiTessellate = tgCM_MIN_UMAX((TgRSIZE)psGeom_Generate->m_uiTessellate, (nuiBit_Max >> 1));

    TgRSIZE                             uiIndex;

    psGeom_Generate->m_nuiVertex = 0;
    psGeom_Generate->m_nuiIndex = 0;

    TgVERIFY(nuiMax_Index_No_Tessellation * (1ULL << (uiTessellate * 2)) <= (TgRSIZE)KTgMAX_U16);

    if (nullptr == psGeom_Generate->m_puiIndex || 0 == psGeom_Generate->m_nuiMax_Index)
    {
        psGeom_Generate->m_nuiMax_Index = TgARRAY_COUNT(KTgGM_ICOSAHEDRON_PN_INDEX)*(1ULL << (uiTessellate * 2));
        return;
    };

    if (psGeom_Generate->m_psVertex)
    {
        if ((2 * psGeom_Generate->m_nuiMax_Vertex) >= TgARRAY_COUNT( KTgGM_ICOSAHEDRON_PN_INDEX_VERTEX ))
        {
            TgRSIZE                             uiVert;

            psGeom_Generate->m_nuiVertex = TgARRAY_COUNT(KTgGM_ICOSAHEDRON_PN_INDEX_VERTEX) >> 1;

            for (uiVert = 0; uiVert < psGeom_Generate->m_nuiVertex; ++uiVert)
            {
                TgCRITICAL(uiVert < psGeom_Generate->m_nuiMax_Vertex);
                psGeom_Generate->m_psVertex[uiVert].m_vS0 = KTgGM_ICOSAHEDRON_PN_INDEX_VERTEX[2*uiVert + 0].m_vF32_04_1;
                psGeom_Generate->m_psVertex[uiVert].m_vN0 = KTgGM_ICOSAHEDRON_PN_INDEX_VERTEX[2*uiVert + 1].m_vF32_04_1;
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

    for (uiIndex = 0; uiIndex < uiTessellate; ++uiIndex)
    {
        tgKN_GPU_DBG_Tessellate( psGeom_Generate );
    };

    if (nullptr == psGeom_Generate->m_psVertex || 0 == psGeom_Generate->m_nuiMax_Vertex)
    {
        psGeom_Generate->m_nuiMax_Vertex = psGeom_Generate->m_nuiVertex;
    };
}


/* ---- tgKN_GPU_DBG_Init_Mesh_Capsule_Cap_0 ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_DBG_Init_Mesh_Capsule_Cap_0( TgKN_GPU_DBG_PM_Generate_PC psGeom_Generate )
{
    TgRSIZE_C                           nuiMax_Index_No_Tessellation = TgARRAY_COUNT(KTgGM_ICOSAHEDRON_CAPSULE_FULL_PN_INDEX) / 3;
    TgRSIZE_C                           nuiBit_Max = (TgRSIZE)tgPM_BSR_UMAX((TgRSIZE)KTgMAX_U16 / nuiMax_Index_No_Tessellation) + 1u;
    TgRSIZE_C                           uiTessellate = tgCM_MIN_UMAX((TgRSIZE)psGeom_Generate->m_uiTessellate, (nuiBit_Max >> 1));

    TgRSIZE                             nuiIndex_Tube;
    TgRSIZE                             uiIndex, nuiMax_Index;
    TgUINT_E16_P                        puiIndex;

    psGeom_Generate->m_nuiVertex = 0;
    psGeom_Generate->m_nuiIndex = 0;

    TgVERIFY(nuiMax_Index_No_Tessellation * (1ULL << (uiTessellate * 2)) <= (TgRSIZE)KTgMAX_U16);

    if (nullptr == psGeom_Generate->m_puiIndex || 0 == psGeom_Generate->m_nuiMax_Index)
    {
        psGeom_Generate->m_nuiMax_Index = nuiMax_Index_No_Tessellation * (1ULL << (uiTessellate*2));
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
                TgCRITICAL(uiVert < psGeom_Generate->m_nuiMax_Vertex);
                psGeom_Generate->m_psVertex[uiVert].m_vS0 = KTgGM_ICOSAHEDRON_CAPSULE_PN_INDEX_VERTEX[2*uiVert + 0].m_vF32_04_1;
                psGeom_Generate->m_psVertex[uiVert].m_vN0 = KTgGM_ICOSAHEDRON_CAPSULE_PN_INDEX_VERTEX[2*uiVert + 1].m_vF32_04_1;
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

    if (!(psGeom_Generate->m_puiIndex && psGeom_Generate->m_nuiMax_Index >= TgARRAY_COUNT(KTgGM_ICOSAHEDRON_CAPSULE_FULL_PN_INDEX) / 3))
    {
        return;
    }

    nuiMax_Index = psGeom_Generate->m_nuiMax_Index;
    puiIndex = psGeom_Generate->m_puiIndex;

    psGeom_Generate->m_nuiMax_Index  = (TgARRAY_COUNT(KTgGM_ICOSAHEDRON_CAPSULE_FULL_PN_INDEX) - 36u)*(1ULL << (uiTessellate*2));
    psGeom_Generate->m_nuiMax_Index += 36u*(1ULL << (uiTessellate));
    psGeom_Generate->m_puiIndex = (TgUINT_E16_P)TgMALLOC_TEMP( psGeom_Generate->m_nuiMax_Index*sizeof(TgUINT_E16) );
    tgMM_Copy( psGeom_Generate->m_puiIndex, psGeom_Generate->m_nuiMax_Index*sizeof(TgUINT_E16), KTgGM_ICOSAHEDRON_CAPSULE_FULL_PN_INDEX, 
               sizeof(KTgGM_ICOSAHEDRON_CAPSULE_FULL_PN_INDEX) );
    psGeom_Generate->m_nuiIndex = TgARRAY_COUNT(KTgGM_ICOSAHEDRON_CAPSULE_FULL_PN_INDEX);

    nuiIndex_Tube = 36;
    for (uiIndex = 0; uiIndex < uiTessellate; ++uiIndex)
    {
        tgKN_GPU_DBG_Tessellate_Capsule( &nuiIndex_Tube, psGeom_Generate );
    };

    TgDIAG(psGeom_Generate->m_nuiIndex == nuiMax_Index * 2 + nuiIndex_Tube);

    tgMM_Copy( puiIndex, nuiMax_Index*sizeof(TgUINT_E16), psGeom_Generate->m_puiIndex, (psGeom_Generate->m_nuiIndex - nuiIndex_Tube)*sizeof(TgUINT_E16) / 2u );
    TgFREE_TEMP(psGeom_Generate->m_puiIndex);
    psGeom_Generate->m_nuiIndex -= nuiIndex_Tube;
    psGeom_Generate->m_nuiIndex /= 2;
    psGeom_Generate->m_puiIndex = puiIndex;
    psGeom_Generate->m_nuiMax_Index = nuiMax_Index;

    if (nullptr == psGeom_Generate->m_psVertex || 0 == psGeom_Generate->m_nuiMax_Vertex)
    {
        psGeom_Generate->m_nuiMax_Vertex = psGeom_Generate->m_nuiVertex;
    };
}


/* ---- tgKN_GPU_DBG_Init_Mesh_Capsule_Cap_1 ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_DBG_Init_Mesh_Capsule_Cap_1( TgKN_GPU_DBG_PM_Generate_PC psGeom_Generate )
{
    TgRSIZE_C                           nuiMax_Index_No_Tessellation = TgARRAY_COUNT(KTgGM_ICOSAHEDRON_CAPSULE_FULL_PN_INDEX) / 3;
    TgRSIZE_C                           nuiBit_Max = (TgRSIZE)tgPM_BSR_UMAX((TgRSIZE)KTgMAX_U16 / nuiMax_Index_No_Tessellation) + 1u;
    TgRSIZE_C                           uiTessellate = tgCM_MIN_UMAX((TgRSIZE)psGeom_Generate->m_uiTessellate, (nuiBit_Max >> 1));

    TgRSIZE                             nuiIndex_Tube;
    TgRSIZE                             uiIndex, nuiMax_Index;
    TgUINT_E16_P                        puiIndex;

    psGeom_Generate->m_nuiVertex = 0;
    psGeom_Generate->m_nuiIndex = 0;

    TgVERIFY(nuiMax_Index_No_Tessellation * (1ULL << (uiTessellate * 2)) <= (TgRSIZE)KTgMAX_U16);

    if (nullptr == psGeom_Generate->m_puiIndex || 0 == psGeom_Generate->m_nuiMax_Index)
    {
        psGeom_Generate->m_nuiMax_Index = nuiMax_Index_No_Tessellation * (1ULL << (uiTessellate * 2));
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
                TgCRITICAL(uiVert < psGeom_Generate->m_nuiMax_Vertex);
                psGeom_Generate->m_psVertex[uiVert].m_vS0 = KTgGM_ICOSAHEDRON_CAPSULE_PN_INDEX_VERTEX[2*uiVert + 0].m_vF32_04_1;
                psGeom_Generate->m_psVertex[uiVert].m_vN0 = KTgGM_ICOSAHEDRON_CAPSULE_PN_INDEX_VERTEX[2*uiVert + 1].m_vF32_04_1;
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

    if (!(psGeom_Generate->m_puiIndex && psGeom_Generate->m_nuiMax_Index >= TgARRAY_COUNT(KTgGM_ICOSAHEDRON_CAPSULE_FULL_PN_INDEX) / 3))
    {
        return;
    }

    nuiMax_Index = psGeom_Generate->m_nuiMax_Index;
    puiIndex = psGeom_Generate->m_puiIndex;

    psGeom_Generate->m_nuiMax_Index  = (TgARRAY_COUNT(KTgGM_ICOSAHEDRON_CAPSULE_FULL_PN_INDEX) - 36u)*(1ULL << (uiTessellate*2));
    psGeom_Generate->m_nuiMax_Index += 36u*(1ULL << (uiTessellate));
    psGeom_Generate->m_puiIndex = (TgUINT_E16_P)TgMALLOC_TEMP( psGeom_Generate->m_nuiMax_Index*sizeof(TgUINT_E16) );
    tgMM_Copy( psGeom_Generate->m_puiIndex, psGeom_Generate->m_nuiMax_Index*sizeof(TgUINT_E16), KTgGM_ICOSAHEDRON_CAPSULE_FULL_PN_INDEX, 
               sizeof(KTgGM_ICOSAHEDRON_CAPSULE_FULL_PN_INDEX) );
    psGeom_Generate->m_nuiIndex = TgARRAY_COUNT(KTgGM_ICOSAHEDRON_CAPSULE_FULL_PN_INDEX);

    nuiIndex_Tube = 36;
    for (uiIndex = 0; uiIndex < uiTessellate; ++uiIndex)
    {
        tgKN_GPU_DBG_Tessellate_Capsule( &nuiIndex_Tube, psGeom_Generate );
    };

    TgDIAG(psGeom_Generate->m_nuiIndex == nuiMax_Index * 2 + nuiIndex_Tube);

    tgMM_Copy( puiIndex, nuiMax_Index*sizeof(TgUINT_E16), psGeom_Generate->m_puiIndex + nuiMax_Index, (psGeom_Generate->m_nuiIndex - nuiIndex_Tube)*sizeof(TgUINT_E16) / 2u );
    TgFREE_TEMP(psGeom_Generate->m_puiIndex);
    psGeom_Generate->m_nuiIndex -= nuiIndex_Tube;
    psGeom_Generate->m_nuiIndex /= 2;
    psGeom_Generate->m_puiIndex = puiIndex;
    psGeom_Generate->m_nuiMax_Index = nuiMax_Index;

    if (nullptr == psGeom_Generate->m_psVertex || 0 == psGeom_Generate->m_nuiMax_Vertex)
    {
        psGeom_Generate->m_nuiMax_Vertex = psGeom_Generate->m_nuiVertex;
    };
}


/* ---- tgKN_GPU_DBG_Init_Mesh_Capsule_Tube -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_DBG_Init_Mesh_Capsule_Tube( TgKN_GPU_DBG_PM_Generate_PC psGeom_Generate )
{
    TgRSIZE_C                           nuiMax_Index_No_Tessellation = TgARRAY_COUNT(KTgGM_ICOSAHEDRON_CAPSULE_FULL_PN_INDEX) / 3;
    TgRSIZE_C                           nuiBit_Max = (TgRSIZE)tgPM_BSR_UMAX((TgRSIZE)KTgMAX_U16 / nuiMax_Index_No_Tessellation) + 1u;
    TgRSIZE_C                           uiTessellate = tgCM_MIN_UMAX((TgRSIZE)psGeom_Generate->m_uiTessellate, (nuiBit_Max >> 1));

    TgRSIZE                             nuiIndex_Tube;
    TgRSIZE                             uiIndex, nuiMax_Index;
    TgUINT_E16_P                        puiIndex;

    psGeom_Generate->m_nuiVertex = 0;
    psGeom_Generate->m_nuiIndex = 0;

    TgVERIFY(nuiMax_Index_No_Tessellation * (1ULL << uiTessellate) <= (TgRSIZE)KTgMAX_U16);

    if (nullptr == psGeom_Generate->m_puiIndex || 0 == psGeom_Generate->m_nuiMax_Index)
    {
        psGeom_Generate->m_nuiMax_Index = nuiMax_Index_No_Tessellation * (1ULL << uiTessellate);
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
                TgCRITICAL(uiVert < psGeom_Generate->m_nuiMax_Vertex);
                psGeom_Generate->m_psVertex[uiVert].m_vS0 = KTgGM_ICOSAHEDRON_CAPSULE_PN_INDEX_VERTEX[2*uiVert + 0].m_vF32_04_1;
                psGeom_Generate->m_psVertex[uiVert].m_vN0 = KTgGM_ICOSAHEDRON_CAPSULE_PN_INDEX_VERTEX[2*uiVert + 1].m_vF32_04_1;
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

    if (!(psGeom_Generate->m_puiIndex && psGeom_Generate->m_nuiMax_Index >= TgARRAY_COUNT(KTgGM_ICOSAHEDRON_CAPSULE_FULL_PN_INDEX) / 3))
    {
        return;
    }

    nuiMax_Index = psGeom_Generate->m_nuiMax_Index;
    puiIndex = psGeom_Generate->m_puiIndex;

    psGeom_Generate->m_nuiMax_Index  = (TgARRAY_COUNT(KTgGM_ICOSAHEDRON_CAPSULE_FULL_PN_INDEX) - 36u)*(1ULL << (uiTessellate*2));
    psGeom_Generate->m_nuiMax_Index += 36u*(1ULL << (uiTessellate));
    psGeom_Generate->m_puiIndex = (TgUINT_E16_P)TgMALLOC_TEMP( psGeom_Generate->m_nuiMax_Index*sizeof(TgUINT_E16) );
    tgMM_Copy( psGeom_Generate->m_puiIndex, psGeom_Generate->m_nuiMax_Index*sizeof(TgUINT_E16), KTgGM_ICOSAHEDRON_CAPSULE_FULL_PN_INDEX, 
               sizeof(KTgGM_ICOSAHEDRON_CAPSULE_FULL_PN_INDEX) );
    psGeom_Generate->m_nuiIndex = TgARRAY_COUNT(KTgGM_ICOSAHEDRON_CAPSULE_FULL_PN_INDEX);

    nuiIndex_Tube = 36;
    for (uiIndex = 0; uiIndex < uiTessellate; ++uiIndex)
    {
        tgKN_GPU_DBG_Tessellate_Capsule( &nuiIndex_Tube, psGeom_Generate );
    };

    TgDIAG(nuiMax_Index == nuiIndex_Tube);

    tgMM_Copy( puiIndex, nuiMax_Index*sizeof(TgUINT_E16), psGeom_Generate->m_puiIndex + psGeom_Generate->m_nuiIndex - nuiIndex_Tube, nuiIndex_Tube*sizeof(TgUINT_E16) );
    TgFREE_TEMP(psGeom_Generate->m_puiIndex);
    psGeom_Generate->m_nuiIndex = nuiIndex_Tube;
    psGeom_Generate->m_puiIndex = puiIndex;
    psGeom_Generate->m_nuiMax_Index = nuiMax_Index;

    if (psGeom_Generate->m_psVertex)
    {
        TgVEC_F32_04_1_C                    vOffset = tgMH_MUL_F32_04_1(KTgUNIT_Y_F32_04_1, tgMH_SET1_F32_04_1(0.5F));

        for (uiIndex = 0; uiIndex < psGeom_Generate->m_nuiVertex >> 1; ++uiIndex)
        {
            psGeom_Generate->m_psVertex[uiIndex].m_vS0 = tgMH_ADD_F32_04_1( psGeom_Generate->m_psVertex[uiIndex].m_vS0, vOffset);
        };

        for (; uiIndex < psGeom_Generate->m_nuiVertex; ++uiIndex)
        {
            psGeom_Generate->m_psVertex[uiIndex].m_vS0 = tgMH_SUB_F32_04_1( psGeom_Generate->m_psVertex[uiIndex].m_vS0, vOffset);
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
    TgRSIZE_C                           nuiMax_Tesselate_Factor = tgCM_PRV_PW2_UMAX(KTgMAX_U16 / (6u * 5u));
    TgUINT_E16_C                        nuiRim_Points = 5u * (TgUINT_E16)tgCM_MIN_UMAX(nuiMax_Tesselate_Factor, (1ULL << psGeom_Generate->m_uiTessellate));

    if (nullptr == psGeom_Generate->m_psVertex || 0 == psGeom_Generate->m_nuiMax_Vertex || nullptr == psGeom_Generate->m_puiIndex || 0 == psGeom_Generate->m_nuiMax_Index)
    {
        psGeom_Generate->m_nuiMax_Index = 6u * nuiRim_Points;
        psGeom_Generate->m_nuiMax_Vertex = 1u + 3u * nuiRim_Points;
        return;
    }
    else
    {
        TgFLOAT32_C                         fCutAngle = KTgTWO_PI_F32 / (TgFLOAT32)(3 * (nuiRim_Points-1));
        TgUINT_E16_C                        nui16_Rim_Points = (TgUINT_E16)nuiRim_Points;
        TgUINT_E16                          uiIndex;

        /* Create a vertex  with a cap outward normal and a coincident vertex with a body outward normal. */
        for (psGeom_Generate->m_nuiVertex = 0; psGeom_Generate->m_nuiVertex < 3u * nuiRim_Points; psGeom_Generate->m_nuiVertex += 3u)
        {
            TgFLOAT32_C                         fA0 = ((TgFLOAT32)psGeom_Generate->m_nuiVertex)*fCutAngle;
            TgFLOAT32                           fCos0, fSin0;
            TgUN_V128                           uT0, uT1;

            tgPM_SINCOS_F32( &fCos0, &fSin0, fA0 );

            uT0.m_vF32_04_1 = tgMH_Init_Vector_ELEM_F32_04_1( fCos0* 0.5F, 0.5F, fSin0* 0.5F );
            uT1.m_vF32_04_1 = tgMH_Init_Vector_ELEM_F32_04_1( fCos0*uT0.m_vS_F32_04_1.y, -fCos0*uT0.m_vS_F32_04_1.x - fSin0*uT0.m_vS_F32_04_1.z, fSin0*uT0.m_vS_F32_04_1.y );
            uT1.m_vF32_04_1 = tgMH_NORM_F32_04_1( uT1.m_vF32_04_1 );

            psGeom_Generate->m_psVertex[psGeom_Generate->m_nuiVertex + 0].m_vS0 = tgMH_Init_Point_F32_04_1( uT0.m_vF32_04_1 );
            psGeom_Generate->m_psVertex[psGeom_Generate->m_nuiVertex + 0].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1( 0.0F, 1.0F, 0.0F );
            psGeom_Generate->m_psVertex[psGeom_Generate->m_nuiVertex + 1].m_vS0 = tgMH_Init_Point_F32_04_1( uT0.m_vF32_04_1 );
            psGeom_Generate->m_psVertex[psGeom_Generate->m_nuiVertex + 1].m_vN0 = uT1.m_vF32_04_1;
            psGeom_Generate->m_psVertex[psGeom_Generate->m_nuiVertex + 2].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1( 0.0F, 0.0F, 0.0F );
            psGeom_Generate->m_psVertex[psGeom_Generate->m_nuiVertex + 2].m_vN0 = uT1.m_vF32_04_1;
        };

        psGeom_Generate->m_psVertex[psGeom_Generate->m_nuiVertex].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1( 0.0F, 0.5F, 0.0F );
        psGeom_Generate->m_psVertex[psGeom_Generate->m_nuiVertex].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1( 0.0F, 1.0F, 0.0F );
        ++psGeom_Generate->m_nuiVertex;

        for (psGeom_Generate->m_nuiIndex = 0, uiIndex = 0; uiIndex < nui16_Rim_Points; ++uiIndex, psGeom_Generate->m_nuiIndex += 6)
        {
            psGeom_Generate->m_puiIndex[6 * uiIndex + 0] = 3u * nui16_Rim_Points;
            psGeom_Generate->m_puiIndex[6 * uiIndex + 1] = 3u * uiIndex + 3u;
            psGeom_Generate->m_puiIndex[6 * uiIndex + 2] = 3u * uiIndex + 0u;

            psGeom_Generate->m_puiIndex[6 * uiIndex + 3] = 3u * uiIndex + 1u;
            psGeom_Generate->m_puiIndex[6 * uiIndex + 4] = 3u * uiIndex + 3u;
            psGeom_Generate->m_puiIndex[6 * uiIndex + 5] = 3u * uiIndex + 2u;
        };
        TgVERIFY( psGeom_Generate->m_nuiMax_Vertex==psGeom_Generate->m_nuiVertex );
        TgVERIFY( psGeom_Generate->m_nuiMax_Index==psGeom_Generate->m_nuiIndex );
    };
}


/* ---- tgKN_GPU_DBG_Init_Mesh_Cylinder ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_DBG_Init_Mesh_Cylinder( TgKN_GPU_DBG_PM_Generate_PC psGeom_Generate )
{
    TgRSIZE_C                           nuiMax_Tesselate_Factor = tgCM_PRV_PW2_UMAX(KTgMAX_U16 / (12u*5u));
    TgUINT_E16_C                        nuiSegments = 5u * (TgUINT_E16)tgCM_MIN_UMAX(nuiMax_Tesselate_Factor,(1ULL << psGeom_Generate->m_uiTessellate));

    TgVERIFY(12ULL * (TgRSIZE)nuiSegments <= (TgRSIZE)KTgMAX_U16); /* Max index is less the max index representation. */

    if (nullptr == psGeom_Generate->m_psVertex || 0 == psGeom_Generate->m_nuiMax_Vertex || nullptr == psGeom_Generate->m_puiIndex || 0 == psGeom_Generate->m_nuiMax_Index)
    {
        /* Vertex layout: 
           - 2 center vertices (top/bottom caps)
           - 4 * nuiSegments rim vertices (top and bottom, caps and sides are not shared due to normals) */
        psGeom_Generate->m_nuiMax_Vertex = 2u + 4u * nuiSegments;
        
        /* Index count:
           - Top cap: 3 * nuiSegments (triangle fan)
           - Bottom cap: 3 * nuiSegments (triangle fan) 
           - Sides: 6 * nuiSegments (2 triangles per segment) */
        psGeom_Generate->m_nuiMax_Index = 12u * nuiSegments;
        return;
    }
    else
    {
        TgFLOAT32_C                         fAngleStep = KTgTWO_PI_F32 / (TgFLOAT32)nuiSegments;
        TgUINT_E16                          uiVertex = 0;
        TgUINT_E16                          uiIndex = 0;
        TgUINT_E16                          uiSeg;

        /* Create center vertices for caps */
        psGeom_Generate->m_psVertex[uiVertex].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1(0.0F, 0.5F, 0.0F);    // Top center
        psGeom_Generate->m_psVertex[uiVertex].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1(0.0F, 1.0F, 0.0F);
        ++uiVertex;

        psGeom_Generate->m_psVertex[uiVertex].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1(0.0F, -0.5F, 0.0F);   // Bottom center
        psGeom_Generate->m_psVertex[uiVertex].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1(0.0F, -1.0F, 0.0F);
        ++uiVertex;

        /* Create rim vertices - top ring first, then bottom ring */
        for (uiSeg = 0; uiSeg < nuiSegments; ++uiSeg)
        {
            TgFLOAT32_C                     fAngle = (TgFLOAT32)uiSeg * fAngleStep;
            TgFLOAT32                       fCos, fSin;
            
            tgPM_SINCOS_F32(&fSin, &fCos, fAngle); // Note: swapped sin/cos for correct winding

            /* Top rim vertex */
            psGeom_Generate->m_psVertex[uiVertex].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1(fCos * 0.5F, 0.5F, fSin * 0.5F);
            psGeom_Generate->m_psVertex[uiVertex].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1(0.0F, 1.0F, 0.0F); // Cap normal
            ++uiVertex;
        }

        for (uiSeg = 0; uiSeg < nuiSegments; ++uiSeg)
        {
            TgFLOAT32_C                     fAngle = (TgFLOAT32)uiSeg * fAngleStep;
            TgFLOAT32                       fCos, fSin;
            
            tgPM_SINCOS_F32(&fSin, &fCos, fAngle);

            /* Bottom rim vertex */
            psGeom_Generate->m_psVertex[uiVertex].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1(fCos * 0.5F, -0.5F, fSin * 0.5F);
            psGeom_Generate->m_psVertex[uiVertex].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1(0.0F, -1.0F, 0.0F); // Cap normal
            ++uiVertex;
        }

        /* Create side vertices with radial normals (reuse positions but different normals) */
        for (uiSeg = 0; uiSeg < nuiSegments; ++uiSeg)
        {
            TgFLOAT32_C                     fAngle = (TgFLOAT32)uiSeg * fAngleStep;
            TgFLOAT32                       fCos, fSin;
            
            tgPM_SINCOS_F32(&fSin, &fCos, fAngle);

            /* Top side vertex (same position as rim, but radial normal) */
            psGeom_Generate->m_psVertex[uiVertex].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1(fCos * 0.5F, 0.5F, fSin * 0.5F);
            psGeom_Generate->m_psVertex[uiVertex].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1(fCos, 0.0F, fSin); // Radial normal
            ++uiVertex;

            /* Bottom side vertex */
            psGeom_Generate->m_psVertex[uiVertex].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1(fCos * 0.5F, -0.5F, fSin * 0.5F);
            psGeom_Generate->m_psVertex[uiVertex].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1(fCos, 0.0F, fSin); // Radial normal
            ++uiVertex;
        }

        /* Generate indices */
        
        /* Top cap (triangle fan from center) */
        for (uiSeg = 0; uiSeg < nuiSegments; ++uiSeg)
        {
            TgUINT_E16_C                    uiNext = (uiSeg + 1u) % nuiSegments;
            
            psGeom_Generate->m_puiIndex[uiIndex++] = 0u;                    // Top center
            psGeom_Generate->m_puiIndex[uiIndex++] = 2u + uiSeg;           // Current top rim
            psGeom_Generate->m_puiIndex[uiIndex++] = 2u + uiNext;          // Next top rim
        }

        /* Bottom cap (triangle fan from center, reversed winding) */
        for (uiSeg = 0; uiSeg < nuiSegments; ++uiSeg)
        {
            TgUINT_E16_C                    uiNext = (uiSeg + 1u) % nuiSegments;
            
            psGeom_Generate->m_puiIndex[uiIndex++] = 1u;                                    // Bottom center
            psGeom_Generate->m_puiIndex[uiIndex++] = 2u + nuiSegments + uiNext;           // Next bottom rim
            psGeom_Generate->m_puiIndex[uiIndex++] = 2u + nuiSegments + uiSeg;            // Current bottom rim
        }

        /* Side faces (quads made of 2 triangles each) */
        TgUINT_E16_C                        uiSideVertexStart = 2u + 2u * nuiSegments; // Start of side vertices
        
        for (uiSeg = 0; uiSeg < nuiSegments; ++uiSeg)
        {
            TgUINT_E16_C                    uiNext = (uiSeg + 1u) % nuiSegments;
            
            /* Current segment vertices */
            TgUINT_E16_C                    uiTopCurr = uiSideVertexStart + 2u * uiSeg;
            TgUINT_E16_C                    uiBotCurr = uiSideVertexStart + 2u * uiSeg + 1;
            
            /* Next segment vertices */
            TgUINT_E16_C                    uiTopNext = uiSideVertexStart + 2u * uiNext;
            TgUINT_E16_C                    uiBotNext = uiSideVertexStart + 2u * uiNext + 1;

            /* First triangle of quad */
            psGeom_Generate->m_puiIndex[uiIndex++] = uiTopCurr;
            psGeom_Generate->m_puiIndex[uiIndex++] = uiBotCurr;
            psGeom_Generate->m_puiIndex[uiIndex++] = uiTopNext;

            /* Second triangle of quad */
            psGeom_Generate->m_puiIndex[uiIndex++] = uiTopNext;
            psGeom_Generate->m_puiIndex[uiIndex++] = uiBotCurr;
            psGeom_Generate->m_puiIndex[uiIndex++] = uiBotNext;
        }

        psGeom_Generate->m_nuiVertex = uiVertex;
        psGeom_Generate->m_nuiIndex = uiIndex;

        TgVERIFY(psGeom_Generate->m_nuiVertex == psGeom_Generate->m_nuiMax_Vertex);
        TgVERIFY(psGeom_Generate->m_nuiIndex == psGeom_Generate->m_nuiMax_Index);
    }
}


/* ---- tgKN_GPU_DBG_Init_Mesh_Tube ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_DBG_Init_Mesh_Tube(TgKN_GPU_DBG_PM_Generate_PC psGeom_Generate)
{
    TgRSIZE_C                           nuiMax_Tesselate_Factor = tgCM_PRV_PW2_UMAX(KTgMAX_U16 / (6u * 5u));
    TgUINT_E16_C                        nuiSegments = 5u * (TgUINT_E16)tgCM_MIN_UMAX(nuiMax_Tesselate_Factor, (1ULL << psGeom_Generate->m_uiTessellate));

    TgVERIFY(5ULL * (TgRSIZE)nuiSegments <= (TgRSIZE)KTgMAX_U16); /* Max index is less the max index representation. */

    if (nullptr == psGeom_Generate->m_psVertex || 0 == psGeom_Generate->m_nuiMax_Vertex || nullptr == psGeom_Generate->m_puiIndex || 0 == psGeom_Generate->m_nuiMax_Index)
    {
        /* Vertex layout: 2 * nuiSegments rim vertices */
        psGeom_Generate->m_nuiMax_Vertex = 2u * nuiSegments;

        /* Index count: Sides: 6 * nuiSegments (2 triangles per segment) */
        psGeom_Generate->m_nuiMax_Index = 6u * nuiSegments;
        return;
    }
    else
    {
        TgFLOAT32_C                         fAngleStep = KTgTWO_PI_F32 / (TgFLOAT32)nuiSegments;
        TgUINT_E16                          uiVertex = 0;
        TgUINT_E16                          uiIndex = 0;
        TgUINT_E16                          uiSeg;

        /* Create side vertices with radial normals (reuse positions but different normals) */
        for (uiSeg = 0; uiSeg < nuiSegments; ++uiSeg)
        {
            TgFLOAT32_C                     fAngle = (TgFLOAT32)uiSeg * fAngleStep;
            TgFLOAT32                       fCos, fSin;

            tgPM_SINCOS_F32(&fSin, &fCos, fAngle);

            /* Top side vertex (same position as rim, but radial normal) */
            psGeom_Generate->m_psVertex[uiVertex].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1(fCos * 0.5F, 0.5F, fSin * 0.5F);
            psGeom_Generate->m_psVertex[uiVertex].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1(fCos, 0.0F, fSin); // Radial normal
            ++uiVertex;

            /* Bottom side vertex */
            psGeom_Generate->m_psVertex[uiVertex].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1(fCos * 0.5F, -0.5F, fSin * 0.5F);
            psGeom_Generate->m_psVertex[uiVertex].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1(fCos, 0.0F, fSin); // Radial normal
            ++uiVertex;
        }

        /* Generate indices */

        /* Side faces (quads made of 2 triangles each) */
        for (uiSeg = 0; uiSeg < nuiSegments; ++uiSeg)
        {
            TgUINT_E16_C                    uiNext = (uiSeg + 1u) % nuiSegments;

            /* Current segment vertices */
            TgUINT_E16_C                    uiTopCurr = 2u * uiSeg;
            TgUINT_E16_C                    uiBotCurr = 2u * uiSeg + 1;

            /* Next segment vertices */
            TgUINT_E16_C                    uiTopNext = 2u * uiNext;
            TgUINT_E16_C                    uiBotNext = 2u * uiNext + 1;

            /* First triangle of quad */
            psGeom_Generate->m_puiIndex[uiIndex++] = uiTopCurr;
            psGeom_Generate->m_puiIndex[uiIndex++] = uiBotCurr;
            psGeom_Generate->m_puiIndex[uiIndex++] = uiTopNext;

            /* Second triangle of quad */
            psGeom_Generate->m_puiIndex[uiIndex++] = uiTopNext;
            psGeom_Generate->m_puiIndex[uiIndex++] = uiBotCurr;
            psGeom_Generate->m_puiIndex[uiIndex++] = uiBotNext;
        }

        psGeom_Generate->m_nuiVertex = uiVertex;
        psGeom_Generate->m_nuiIndex = uiIndex;

        TgVERIFY(psGeom_Generate->m_nuiVertex == psGeom_Generate->m_nuiMax_Vertex);
        TgVERIFY(psGeom_Generate->m_nuiIndex == psGeom_Generate->m_nuiMax_Index);
    }
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

        psGeom_Generate->m_psVertex[ 0].m_vS0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[0].m_vF32_04_1;
        psGeom_Generate->m_psVertex[ 0].m_vN0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[1].m_vF32_04_1;
        psGeom_Generate->m_psVertex[ 1].m_vS0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[2].m_vF32_04_1;
        psGeom_Generate->m_psVertex[ 1].m_vN0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[3].m_vF32_04_1;
        psGeom_Generate->m_psVertex[ 2].m_vS0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[4].m_vF32_04_1;
        psGeom_Generate->m_psVertex[ 2].m_vN0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[5].m_vF32_04_1;
        psGeom_Generate->m_psVertex[ 3].m_vS0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[6].m_vF32_04_1;
        psGeom_Generate->m_psVertex[ 3].m_vN0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[7].m_vF32_04_1;
        psGeom_Generate->m_psVertex[ 4].m_vS0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[8].m_vF32_04_1;
        psGeom_Generate->m_psVertex[ 4].m_vN0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[9].m_vF32_04_1;
        psGeom_Generate->m_psVertex[ 5].m_vS0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[10].m_vF32_04_1;
        psGeom_Generate->m_psVertex[ 5].m_vN0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[11].m_vF32_04_1;
        psGeom_Generate->m_psVertex[ 6].m_vS0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[12].m_vF32_04_1;
        psGeom_Generate->m_psVertex[ 6].m_vN0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[13].m_vF32_04_1;
        psGeom_Generate->m_psVertex[ 7].m_vS0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[14].m_vF32_04_1;
        psGeom_Generate->m_psVertex[ 7].m_vN0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[15].m_vF32_04_1;
        psGeom_Generate->m_psVertex[ 8].m_vS0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[16].m_vF32_04_1;
        psGeom_Generate->m_psVertex[ 8].m_vN0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[17].m_vF32_04_1;
        psGeom_Generate->m_psVertex[ 9].m_vS0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[18].m_vF32_04_1;
        psGeom_Generate->m_psVertex[ 9].m_vN0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[19].m_vF32_04_1;
        psGeom_Generate->m_psVertex[10].m_vS0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[20].m_vF32_04_1;
        psGeom_Generate->m_psVertex[10].m_vN0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[21].m_vF32_04_1;
        psGeom_Generate->m_psVertex[11].m_vS0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[22].m_vF32_04_1;
        psGeom_Generate->m_psVertex[11].m_vN0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[23].m_vF32_04_1;
        psGeom_Generate->m_psVertex[12].m_vS0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[24].m_vF32_04_1;
        psGeom_Generate->m_psVertex[12].m_vN0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[25].m_vF32_04_1;
        psGeom_Generate->m_psVertex[13].m_vS0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[26].m_vF32_04_1;
        psGeom_Generate->m_psVertex[13].m_vN0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[27].m_vF32_04_1;
        psGeom_Generate->m_psVertex[14].m_vS0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[28].m_vF32_04_1;
        psGeom_Generate->m_psVertex[14].m_vN0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[29].m_vF32_04_1;
        psGeom_Generate->m_psVertex[15].m_vS0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[30].m_vF32_04_1;
        psGeom_Generate->m_psVertex[15].m_vN0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[31].m_vF32_04_1;
        psGeom_Generate->m_psVertex[16].m_vS0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[32].m_vF32_04_1;
        psGeom_Generate->m_psVertex[16].m_vN0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[33].m_vF32_04_1;
        psGeom_Generate->m_psVertex[17].m_vS0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[34].m_vF32_04_1;
        psGeom_Generate->m_psVertex[17].m_vN0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[35].m_vF32_04_1;
        psGeom_Generate->m_psVertex[18].m_vS0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[36].m_vF32_04_1;
        psGeom_Generate->m_psVertex[18].m_vN0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[37].m_vF32_04_1;
        psGeom_Generate->m_psVertex[19].m_vS0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[38].m_vF32_04_1;
        psGeom_Generate->m_psVertex[19].m_vN0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[39].m_vF32_04_1;
        psGeom_Generate->m_psVertex[20].m_vS0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[40].m_vF32_04_1;
        psGeom_Generate->m_psVertex[20].m_vN0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[41].m_vF32_04_1;
        psGeom_Generate->m_psVertex[21].m_vS0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[42].m_vF32_04_1;
        psGeom_Generate->m_psVertex[21].m_vN0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[43].m_vF32_04_1;
        psGeom_Generate->m_psVertex[22].m_vS0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[44].m_vF32_04_1;
        psGeom_Generate->m_psVertex[22].m_vN0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[45].m_vF32_04_1;
        psGeom_Generate->m_psVertex[23].m_vS0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[46].m_vF32_04_1;
        psGeom_Generate->m_psVertex[23].m_vN0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[47].m_vF32_04_1;
        psGeom_Generate->m_psVertex[24].m_vS0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[48].m_vF32_04_1;
        psGeom_Generate->m_psVertex[24].m_vN0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[49].m_vF32_04_1;
        psGeom_Generate->m_psVertex[25].m_vS0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[50].m_vF32_04_1;
        psGeom_Generate->m_psVertex[25].m_vN0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[51].m_vF32_04_1;
        psGeom_Generate->m_psVertex[26].m_vS0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[52].m_vF32_04_1;
        psGeom_Generate->m_psVertex[26].m_vN0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[53].m_vF32_04_1;
        psGeom_Generate->m_psVertex[27].m_vS0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[54].m_vF32_04_1;
        psGeom_Generate->m_psVertex[27].m_vN0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[55].m_vF32_04_1;
        psGeom_Generate->m_psVertex[28].m_vS0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[56].m_vF32_04_1;
        psGeom_Generate->m_psVertex[28].m_vN0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[57].m_vF32_04_1;
        psGeom_Generate->m_psVertex[29].m_vS0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[58].m_vF32_04_1;
        psGeom_Generate->m_psVertex[29].m_vN0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[59].m_vF32_04_1;
        psGeom_Generate->m_psVertex[30].m_vS0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[60].m_vF32_04_1;
        psGeom_Generate->m_psVertex[30].m_vN0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[61].m_vF32_04_1;
        psGeom_Generate->m_psVertex[31].m_vS0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[62].m_vF32_04_1;
        psGeom_Generate->m_psVertex[31].m_vN0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[63].m_vF32_04_1;
        psGeom_Generate->m_psVertex[32].m_vS0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[64].m_vF32_04_1;
        psGeom_Generate->m_psVertex[32].m_vN0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[65].m_vF32_04_1;
        psGeom_Generate->m_psVertex[33].m_vS0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[66].m_vF32_04_1;
        psGeom_Generate->m_psVertex[33].m_vN0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[67].m_vF32_04_1;
        psGeom_Generate->m_psVertex[34].m_vS0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[68].m_vF32_04_1;
        psGeom_Generate->m_psVertex[34].m_vN0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[69].m_vF32_04_1;
        psGeom_Generate->m_psVertex[35].m_vS0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[70].m_vF32_04_1;
        psGeom_Generate->m_psVertex[35].m_vN0 = KTgGM_CUBE_PN_TRI_LIST_VERTEX[71].m_vF32_04_1;

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
        psGeom_Generate->m_psVertex[0].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1( -0.5F, 0.0F, -0.5F );
        psGeom_Generate->m_psVertex[0].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1( 0.0F, 1.0F, 0.0F );
        psGeom_Generate->m_psVertex[1].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1( -0.5F, 0.0F, 0.5F );
        psGeom_Generate->m_psVertex[1].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1( 0.0F, 1.0F, 0.0F );
        psGeom_Generate->m_psVertex[2].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1( 0.5F, 0.0F, 0.5F );
        psGeom_Generate->m_psVertex[2].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1( 0.0F, 1.0F, 0.0F );
        psGeom_Generate->m_psVertex[3].m_vS0 = tgMH_Init_Point_ELEM_F32_04_1( 0.5F, 0.0F, -0.5F );
        psGeom_Generate->m_psVertex[3].m_vN0 = tgMH_Init_Vector_ELEM_F32_04_1( 0.0F, 1.0F, 0.0F );
        psGeom_Generate->m_nuiVertex = 4u;
        psGeom_Generate->m_puiIndex[0] = 0;
        psGeom_Generate->m_puiIndex[1] = 2;
        psGeom_Generate->m_puiIndex[2] = 1;
        psGeom_Generate->m_puiIndex[3] = 0;
        psGeom_Generate->m_puiIndex[4] = 3;
        psGeom_Generate->m_puiIndex[5] = 2;
        psGeom_Generate->m_puiIndex[6] = 0;
        psGeom_Generate->m_puiIndex[7] = 1;
        psGeom_Generate->m_puiIndex[8] = 2;
        psGeom_Generate->m_puiIndex[9] = 0;
        psGeom_Generate->m_puiIndex[10] = 2;
        psGeom_Generate->m_puiIndex[11] = 3;
        psGeom_Generate->m_nuiIndex = 12u;
    };
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgKN_GPU__CMD__Render_Debug_Text_Box_Right_Align ------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
//tgKN_GPU__CMD__Render_Debug_Text_Box_Right_Align( fScale_Sx, fText_Start_Z, pvText_Offsets + uiBuffer_Index - 1, pvText_Offsets );
static TgVOID tgKN_GPU__CMD__Render_Debug_Text_Box_Right_Align( TgFLOAT32_C Sx, TgFLOAT32_C fText_Start_Z, TgVEC_S_F32_04_1_P pvText_Offsets, TgVEC_S_F32_04_1_P pvText_Start )
{
    TgFLOAT32_C                         fCurrentY = pvText_Offsets->y;
    TgFLOAT32_C                         fOffsetX = fText_Start_Z - pvText_Offsets->x - Sx;

    for (; pvText_Offsets >= pvText_Start; -- pvText_Offsets)
    {
        pvText_Offsets->x += fOffsetX;
        if (pvText_Offsets->y != fCurrentY)
            break;
    }
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
/*  Vertices are assumed to be on a sphere and the position is corrected to remain at a constant radius from the origin.                                                           */
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
        TgVEC_F32_04_1_C                    vK0 = tgMH_Init_ELEM_F32_04_1( 0.5F, 0.5F, 0.5F, 0.0F );
        TgVEC_F32_04_1_C                    vK1 = tgMH_LEN_F32_04_1( tgMH_Init_Vector_F32_04_1( psData->m_psGenerate->m_psVertex[uiStart].m_vS0 ) );
        TgVEC_F32_04_1_C                    vK2 = tgMH_ADD_F32_04_1( psData->m_psGenerate->m_psVertex[uiStart].m_vS0, psData->m_psGenerate->m_psVertex[uiEnd].m_vS0 );
        TgVEC_F32_04_1_C                    vK3 = tgMH_MUL_F32_04_1( vK0, vK2 );
        TgVEC_F32_04_1_C                    vKN = tgMH_NORM_F32_04_1( vK3 );
        TgVEC_F32_04_1_C                    vKS = tgMH_MUL_F32_04_1( vK1, vKN );

        TgCRITICAL(psData->m_psGenerate->m_nuiVertex < psData->m_psGenerate->m_nuiMax_Vertex);

        psData->m_psGenerate->m_psVertex[psData->m_psGenerate->m_nuiVertex].m_vS0 = tgMH_Init_Point_F32_04_1( vKS );
        psData->m_psGenerate->m_psVertex[psData->m_psGenerate->m_nuiVertex].m_vN0 = tgMH_Init_Vector_F32_04_1( vKN );
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

    TgCRITICAL_MSGF( nullptr != sTessellation.m_puiStart, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to allocate memory." );
    TgCRITICAL_MSGF( nullptr != sTessellation.m_puiEnd, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to allocate memory." );
    TgCRITICAL_MSGF( nullptr != sTessellation.m_puiMid, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to allocate memory." );
    TgCRITICAL_MSGF( nullptr != sTessellation.m_puiIndex_Orig, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to allocate memory." );

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
    TgRSIZE_C                           nuiIndex_Orig = psGenerate->m_nuiIndex;
    TgRSIZE_C                           nuiIndex_Cap_Orig = psGenerate->m_nuiIndex - *pnuiIndex_Tube;

    TgKN_GPU_DBG_Geom_For_Tessellation  sTessellation;
    STg2_KN_GPU_Vertex_Geom_02_P        psVertex_Orig;
    TgRSIZE                             nuiIndex;
    TgRSIZE                             nuiNewIndex;
    TgUINT_E16                          nuiAdded_Vertex;
    TgRSIZE                             nuiTest_Vertex;

    sTessellation.m_psGenerate = psGenerate;
    sTessellation.m_nuiMax_Edge = psGenerate->m_nuiVertex + 4 * nuiIndex_Cap_Orig;
    sTessellation.m_nuiEdge = 0u;
    sTessellation.m_puiStart = (TgUINT_E16_P)TgMALLOC_POOL( sTessellation.m_nuiMax_Edge * sizeof( TgUINT_E16 ) );
    sTessellation.m_puiEnd = (TgUINT_E16_P)TgMALLOC_POOL( sTessellation.m_nuiMax_Edge * sizeof( TgUINT_E16 ) );
    sTessellation.m_puiMid = (TgUINT_E16_P)TgMALLOC_POOL( sTessellation.m_nuiMax_Edge * sizeof( TgUINT_E16 ) );
    sTessellation.m_puiIndex_Orig = (TgUINT_E16_P)TgMALLOC_POOL( nbyIndex_Orig );
    sTessellation.m_nuiIndex_Orig = nuiIndex_Orig;

    TgCRITICAL_MSGF( nullptr != sTessellation.m_puiStart, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to allocate memory." );
    TgCRITICAL_MSGF( nullptr != sTessellation.m_puiEnd, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to allocate memory." );
    TgCRITICAL_MSGF( nullptr != sTessellation.m_puiMid, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to allocate memory." );
    TgCRITICAL_MSGF( nullptr != sTessellation.m_puiIndex_Orig, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to allocate memory." );

    TgMEMCPY_NOCACHE( sTessellation.m_puiIndex_Orig, nbyIndex_Orig, psGenerate->m_puiIndex, nbyIndex_Orig );

    for (nuiIndex = 0; nuiIndex < nuiIndex_Cap_Orig >> 1; ++nuiIndex)
    {
        TgVERIFY( sTessellation.m_puiIndex_Orig[nuiIndex] < (nuiVertex_Orig >> 1) );
    };
    for (; nuiIndex < nuiIndex_Cap_Orig; ++nuiIndex)
    {
        TgVERIFY( sTessellation.m_puiIndex_Orig[nuiIndex] >= (nuiVertex_Orig >> 1) );
    };

    /* The code overwrites the index buffer in place using the copy of the original buffer. */
    psGenerate->m_nuiIndex = 0;

    psVertex_Orig = (STg2_KN_GPU_Vertex_Geom_02_P)TgMALLOC_POOL( nbyVertex_Orig >> 1 );

    /* General reminder: our capsule is created as two demi-spheres that are then separated from each other and the resulting faces defined to fill out the capsule. Taking
                         advantage of that construction method, we copy off the second half of the vertices at this point since we will overwrite their location for implementation
                         simplicity. We can then copy them back when we tessellate the second half of the capsule. This way the index list continues to be separatable. */

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
        sTessellation.m_puiIndex_Orig[nuiIndex] += nuiAdded_Vertex;
    };

    /* Tessellate the first second of the capsule. */
    tgKN_GPU_DBG_Tessellate_Triangles( nuiIndex_Cap_Orig >> 1, nuiIndex_Cap_Orig, psGenerate->m_nuiIndex, &sTessellation );

    /* Do not tessellate the faces in the tube section - create the additional faces caused by the extra vertices in the caps. */

    for (nuiIndex = nuiIndex_Cap_Orig; nuiIndex < nuiIndex_Orig; ++nuiIndex)
    {
        if (sTessellation.m_puiIndex_Orig[nuiIndex] >= (nuiVertex_Orig >> 1) )
        {
            sTessellation.m_puiIndex_Orig[nuiIndex] += nuiAdded_Vertex;
        };
    };

    nuiTest_Vertex = psGenerate->m_nuiVertex;
    for (nuiIndex = nuiIndex_Cap_Orig, nuiNewIndex = psGenerate->m_nuiIndex; nuiIndex < nuiIndex_Orig && nuiNewIndex < psGenerate->m_nuiMax_Index; nuiIndex += 6, nuiNewIndex += 12)
    {
        TgUINT_E16_C                        uiP0 = sTessellation.m_puiIndex_Orig[nuiIndex + 0];
        TgUINT_E16_C                        uiP1 = sTessellation.m_puiIndex_Orig[nuiIndex + 1];
        TgUINT_E16_C                        uiP2 = sTessellation.m_puiIndex_Orig[nuiIndex + 2];
        TgUINT_E16_C                        uiP4 = sTessellation.m_puiIndex_Orig[nuiIndex + 4];
        TgUINT_E16_C                        uiP5 = sTessellation.m_puiIndex_Orig[nuiIndex + 5];

        TgUINT_E16                          ui01 = tgKN_GPU_DBG_Tessellate_Mid_Point( uiP0, uiP1, &sTessellation );
        TgUINT_E16                          ui45 = tgKN_GPU_DBG_Tessellate_Mid_Point( uiP4, uiP5, &sTessellation );

        TgDIAG(nuiTest_Vertex == psGenerate->m_nuiVertex);

        psGenerate->m_puiIndex[nuiNewIndex + 0] = uiP0;
        psGenerate->m_puiIndex[nuiNewIndex + 1] = ui01;
        psGenerate->m_puiIndex[nuiNewIndex + 2] = uiP2;

        psGenerate->m_puiIndex[nuiNewIndex + 3] = ui01;
        psGenerate->m_puiIndex[nuiNewIndex + 4] = ui45;
        psGenerate->m_puiIndex[nuiNewIndex + 5] = uiP2;

        psGenerate->m_puiIndex[nuiNewIndex + 6] = ui01;
        psGenerate->m_puiIndex[nuiNewIndex + 7] = uiP1;
        psGenerate->m_puiIndex[nuiNewIndex + 8] = ui45;

        psGenerate->m_puiIndex[nuiNewIndex + 9] = uiP1;
        psGenerate->m_puiIndex[nuiNewIndex + 10] = uiP4;
        psGenerate->m_puiIndex[nuiNewIndex + 11] = ui45;
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


/*# defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
#endif
