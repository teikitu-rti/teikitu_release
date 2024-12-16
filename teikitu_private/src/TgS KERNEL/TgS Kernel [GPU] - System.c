/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Kernel - System [GPU].c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_GPU_Enumerate ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_Enumerate( TgVOID )
{
    TgRESULT                            iRet;

    iRet = tgKN_GPU_EXT_Enumerate();

    /* Print/Output the data from enumeration. */
#if TgCOMPILE__CONSOLE
    if (TgSUCCEEDED(iRet) && tgGB_CMD_Query_Argument_Index( u8"-//test/unit/kernel/gpu/info" ) >= 0)
    {
        TgUINT_E32                          uiPrevious_Severity;

        uiPrevious_Severity = tgCN_Set_Severity_Filter( KTgCN_CHANEL_INITIALIZE, KTgCN_MAX_SEVERITY );
        tgCN_Execute_Command( u8"STAT_Print_Adapters", KTgMAX_RSIZE );
        tgCN_Set_Severity_Filter( KTgCN_CHANEL_INITIALIZE, uiPrevious_Severity );
    };
#endif

    return (iRet);
}


/* ---- tgKN_GPU_Query_Adapter_List ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_Query_Adapter_List( STg2_KN_GPU_Adapter_CPP ppAdapter, TgUINT_E32_C nuiAdapter )
{
    TgRSIZE                             uiAdapter;

    TgPARAM_CHECK( nuiAdapter >= KTgKN_GPU_MAX_ADAPTER );

    for (uiAdapter = 0; uiAdapter < g_sKN_GPU_CXT_HOST.m_nuiAdapter; ++uiAdapter)
    {
        ppAdapter[uiAdapter] = g_sKN_GPU_CXT_HOST.m_asAdapter + uiAdapter;
    };

    for (; uiAdapter < nuiAdapter; ++uiAdapter)
    {
        ppAdapter[uiAdapter] = nullptr;
    };

    return (KTgS_OK);
}


/* ---- tgKN_GPU_Test_Output_ScanOut_Format_Support ------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgKN_GPU_Test_Output_ScanOut_Format_Support( TgRSIZE_C uiAdapter, ETgKN_GPU_EXT_FORMAT_C enFormat )
{
    TgUINT_E08                          uiScanOut;

    TgPARAM_CHECK_INDEX( uiAdapter, g_sKN_GPU_CXT_HOST.m_asAdapter );

    for (uiScanOut = 0; uiScanOut < TgARRAY_COUNT(KTgKN_GPU_EXT_FORMAT_RT_SCANOUT); ++uiScanOut)
    {
        if (enFormat == KTgKN_GPU_EXT_FORMAT_RT_SCANOUT[uiScanOut])
        {
            return (tgBF_Test_Flag_U32( &g_sKN_GPU_CXT_HOST.m_asAdapter[uiAdapter].m_uiSupport_Flags, uiScanOut ));
        }
    }

    return (false);
}


/* ---- tgKN_GPU_Query_Mode_List ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgUINT_E32 tgKN_GPU_Query_Mode_List( STg2_KN_GPU_Mode_P psMode, TgUINT_E32_C niMode, TgUINT_E32_C uiAdapter, TgUINT_E32_C uiOutput, ETgKN_GPU_EXT_FORMAT_C enFormat )
{
    return (tgKN_GPU_EXT_Query_Mode_List( psMode, niMode, uiAdapter, uiOutput, enFormat ));
}


/* ---- tgKN_GPU_Query_DOS_Font_ROM_TX ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_Query_DOS_Font_ROM_TX( STg2_KN_GPU_FONT_TX_PC psOUT, ETgKN_GPU_DOS_FONT_ROM_C enFont )
{
    if (nullptr == psOUT || (TgSINT_E32)enFont < 0 || (TgSINT_E32)enFont >= ETgKN_GPU_DOS_FONT_ROM_COUNT)
        return (KTgE_FAIL);

    psOUT->m_fFntX = (TgFLOAT32)(g_sKN_GPU_STD_DOS_Font[enFont].m_uiFntX);
    psOUT->m_fFntY = (TgFLOAT32)(g_sKN_GPU_STD_DOS_Font[enFont].m_uiFntY);
    psOUT->m_fTX_X = (TgFLOAT32)(g_sKN_GPU_STD_DOS_Font[enFont].m_uiTX_X);
    psOUT->m_fTX_Y = (TgFLOAT32)(g_sKN_GPU_STD_DOS_Font[enFont].m_uiTX_Y);
    psOUT->m_fTX_Cell_X = (TgFLOAT32)(g_sKN_GPU_STD_DOS_Font[enFont].m_uiTX_Cell_X);
    psOUT->m_fTX_Cell_Y = (TgFLOAT32)(g_sKN_GPU_STD_DOS_Font[enFont].m_uiTX_Cell_Y);

    return (KTgS_OK);
}


/* ---- tgKN_GPU_Query_Mode_List ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVEC_S_F32_04_1 tgKN_GPU_Colour_Grading_CPU( TgVEC_S_F32_04_1 vColour, STg2_KN_GPU_HLSL_Output_DESC_CPC psOutput_DESC )
{
    if (nullptr == psOutput_DESC)
        return (vColour);

    if (psOutput_DESC->m_bHDR_Enabled)
    {
        if (ETgKN_GPU_HLSL_COLOR_SPACE_G2084_NONE_P2020 == psOutput_DESC->m_enColour_Space)
        {
            TgVEC_S_F32_04_4_C                  mConversion =
            {
                .m_vC0 = { { 0.627402F, 0.329292F, 0.043306F, 0.0F } },
                .m_vC1 = { { 0.069095F, 0.919544F, 0.011360F, 0.0F } },
                .m_vC2 = { { 0.016394F, 0.088028F, 0.895578F, 0.0F } },
                .m_vC3 = { { 0.0F, 0.0F, 0.0F, 1.0F } }
            };

            TgFLOAT32_C                         m2 = 2523.0F / 4096.0F * 128.0F;
            TgFLOAT32_C                         c3 = 2392.0F / 4096.0F * 32.0F;
            TgVEC_S_F32_04_1                    cp;

            /* Render buffer is 10bit per channel, normalized, or 1 is max brightness. To match the SDR rendering, we need to scale down the brightness of the colour, similar to
               how we scale up the colour value (for similar reasons) for the scRGB F16 clear colour. */

            /* P709 to P2020 */

            vColour = tgMH_TX_S_F32_04_4( vColour, &mConversion );

            /* Adjust for max nits in ST2084 (max nits of 10,000), and SDR content on HDR monitor set to 50% in Windows Settings. */

            vColour.r *= psOutput_DESC->m_fSDR_In_HDR_Nits_Level / 10000.0F;
            vColour.g *= psOutput_DESC->m_fSDR_In_HDR_Nits_Level / 10000.0F;
            vColour.b *= psOutput_DESC->m_fSDR_In_HDR_Nits_Level / 10000.0F;

            /* Transfer to ST2084 */

            cp.r = tgPM_POW_F32( tgPM_ABS_F32( vColour.r ), (2610.0F / 4096.0F / 4.0F) );
            cp.g = tgPM_POW_F32( tgPM_ABS_F32( vColour.g ), (2610.0F / 4096.0F / 4.0F) );
            cp.b = tgPM_POW_F32( tgPM_ABS_F32( vColour.b ), (2610.0F / 4096.0F / 4.0F) );

            vColour.r = tgPM_POW_F32( ((3424.0F / 4096.0F) + (2413.0F / 4096.0F * 32.0F) * cp.r) / (1.0F + c3 * cp.r), m2 );
            vColour.g = tgPM_POW_F32( ((3424.0F / 4096.0F) + (2413.0F / 4096.0F * 32.0F) * cp.g) / (1.0F + c3 * cp.g), m2 );
            vColour.b = tgPM_POW_F32( ((3424.0F / 4096.0F) + (2413.0F / 4096.0F * 32.0F) * cp.b) / (1.0F + c3 * cp.b), m2 );
        }
        else if (ETgKN_GPU_HLSL_COLOR_SPACE_G10_NONE_P709 == psOutput_DESC->m_enColour_Space)
        {
            /* scRGB (1,1,1) is considered to be D65 at 80 nits. Since HDR is scene referred, we can directly scale the RGB values according to the current OS configuration. */
            vColour.r *= psOutput_DESC->m_fSDR_In_HDR_Nits_Level / 80.0F;
            vColour.g *= psOutput_DESC->m_fSDR_In_HDR_Nits_Level / 80.0F;
            vColour.b *= psOutput_DESC->m_fSDR_In_HDR_Nits_Level / 80.0F;
        };
    }
    else
    {
        if (ETgKN_GPU_HLSL_COLOR_SPACE_G10_NONE_P709 != psOutput_DESC->m_enColour_Space)
        {
            /* Transform to G22 as needed for the Colour Spaces in Gamma 2.2 */
            vColour.r = vColour.r < 0.0031308F ? 12.92F * vColour.r : 1.055F * tgPM_POW_F32( tgPM_ABS_F32( vColour.r ), 1.0F / 2.4F ) - 0.055F;
            vColour.g = vColour.g < 0.0031308F ? 12.92F * vColour.g : 1.055F * tgPM_POW_F32( tgPM_ABS_F32( vColour.g ), 1.0F / 2.4F ) - 0.055F;
            vColour.b = vColour.b < 0.0031308F ? 12.92F * vColour.b : 1.055F * tgPM_POW_F32( tgPM_ABS_F32( vColour.b ), 1.0F / 2.4F ) - 0.055F;
        }
    };

    return (vColour);
}
