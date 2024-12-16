/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (DX12) Kernel - System [GPU].c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_GPU_EXT_Query_Mode_List --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgUINT_F32 tgKN_GPU_EXT_Query_Mode_List( STg2_KN_GPU_Mode_P psMode, TgUINT_F32_C nuiMode, TgUINT_F32_C uiAdapter, TgUINT_F32_C uiOutput, ETgKN_GPU_EXT_FORMAT_C enFormat )
{
    DXGI_FORMAT                         enDXGI_Format;
    TgUINT_F32                          nuiRet;
    TgUINT_F32                          uiMode;
    STg2_KN_GPU_EXT_Adapter_P           psEXT_Adapter;

    TgPARAM_CHECK_INDEX( uiAdapter, g_sKN_GPU_CXT_HOST.m_asAdapter );

    enDXGI_Format = (DXGI_FORMAT)enFormat;
    nuiRet = 0;
    psEXT_Adapter = g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Adapter + uiAdapter;

    TgPARAM_CHECK_INDEX( uiOutput, g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Adapter[uiAdapter].m_asEXT_Output );

    if (nullptr == psMode)
    {
        for (uiMode = 0; uiMode < psEXT_Adapter->m_asEXT_Output->m_nuiDXGI_Mode; ++uiMode)
        {
            if (psEXT_Adapter->m_asEXT_Output->m_psDXGI_Mode[uiMode].Format != enDXGI_Format)
                continue;
            ++nuiRet;
        };
    }
    else
    {
        for (uiMode = 0; uiMode < psEXT_Adapter->m_asEXT_Output->m_nuiDXGI_Mode; ++uiMode)
        {
            if (psEXT_Adapter->m_asEXT_Output->m_psDXGI_Mode[uiMode].Format != enDXGI_Format)
                continue;
            if (nuiRet < nuiMode)
            {
                psMode[nuiRet].m_sBuffer.m_uiWidth = psEXT_Adapter->m_asEXT_Output->m_psDXGI_Mode[uiMode].Width;
                psMode[nuiRet].m_sBuffer.m_uiHeight = psEXT_Adapter->m_asEXT_Output->m_psDXGI_Mode[uiMode].Height;
                psMode[nuiRet].m_uiRefresh_Rate__Numerator = psEXT_Adapter->m_asEXT_Output->m_psDXGI_Mode[uiMode].RefreshRate.Numerator;
                psMode[nuiRet].m_uiRefresh_Rate__Denominator = psEXT_Adapter->m_asEXT_Output->m_psDXGI_Mode[uiMode].RefreshRate.Denominator;
                psMode[nuiRet].m_sBuffer.m_enFormat  = enFormat;
            };
            ++nuiRet;
        };
    };

    return (nuiRet);
}
