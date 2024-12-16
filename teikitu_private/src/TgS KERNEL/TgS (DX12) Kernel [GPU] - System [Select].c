/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (DX12) Kernel - System [GPU] [Select].c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_GPU_Select_Min_Mode ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* These generic GPU functions need to be defined in the API layer as we do not copy all of the modes to the generic layer.                                                        */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_Select_Min_Mode( STg2_KN_GPU_Mode_PC psSelect, TgUINT_E32_C uiAdapter_Index, TgUINT_E32_C uiOutput_Index, STg2_KN_GPU_Mode_CPC psRequest )
{
    TgUINT_E32                          uiWidth = psRequest->m_sBuffer.m_uiWidth;
    TgUINT_E32                          uiHeight = psRequest->m_sBuffer.m_uiHeight;
    DXGI_FORMAT const                   enDXGI_Format = (DXGI_FORMAT)psRequest->m_sBuffer.m_enFormat;

    TgRSIZE                             nuiModes;
    DXGI_MODE_DESC1_P                   psDXGI_Mode;
    TgUINT_E32                          uiIndex;

    TgPARAM_CHECK(nullptr != psSelect);
    TgPARAM_CHECK(nullptr != psRequest);

    nuiModes = g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Adapter[uiAdapter_Index].m_asEXT_Output[uiOutput_Index].m_nuiDXGI_Mode;
    psDXGI_Mode = g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Adapter[uiAdapter_Index].m_asEXT_Output[uiOutput_Index].m_psDXGI_Mode;
    uiIndex = 0;
    if (psDXGI_Mode[uiIndex].Width < uiWidth)
    {
        for (++uiIndex; uiIndex < nuiModes; ++uiIndex)
        {
            if (psDXGI_Mode[uiIndex].Width > uiWidth)
            {
                break;
            };
        };
        --uiIndex;
    };

    uiWidth = psDXGI_Mode[uiIndex].Width;
    if (0 == uiIndex)
    {
        for (++uiIndex; uiIndex < nuiModes; ++uiIndex)
        {
            if (psDXGI_Mode[uiIndex].Width > uiWidth)
            {
                break;
            };
        };
        --uiIndex;
    };

    if (psDXGI_Mode[uiIndex].Height > uiHeight)
    {
        for (; uiIndex > 0; --uiIndex)
        {
            if (psDXGI_Mode[uiIndex].Height < uiHeight || psDXGI_Mode[uiIndex-1].Width != uiWidth)
            {
                break;
            };
        };
    };

    uiHeight = psDXGI_Mode[uiIndex].Height;
    if (0 == uiIndex || psDXGI_Mode[uiIndex-1].Width != uiWidth)
    {
        for (++uiIndex; uiIndex < nuiModes && psDXGI_Mode[uiIndex].Width == uiWidth && psDXGI_Mode[uiIndex].Height == uiHeight; ++uiIndex);
        --uiIndex;
    };

    if (psDXGI_Mode[uiIndex].Format != enDXGI_Format)
    {
        for (; uiIndex > 0; --uiIndex)
        {
            if (psDXGI_Mode[uiIndex].Format == enDXGI_Format)
            {
                break;
            };

            if (psDXGI_Mode[uiIndex-1].Width != uiWidth || psDXGI_Mode[uiIndex-1].Height != uiHeight)
            {
                break;
            };
        };
    };

    if (psDXGI_Mode[uiIndex].Format != enDXGI_Format)
    {
        return (KTgE_FAIL);
    };

    if (psRequest->m_uiRefresh_Rate__Denominator*psDXGI_Mode[uiIndex].RefreshRate.Numerator < psRequest->m_uiRefresh_Rate__Numerator*psDXGI_Mode[uiIndex].RefreshRate.Denominator)
    {
        for (; uiIndex > 0; --uiIndex)
        {
            if(
                psDXGI_Mode[uiIndex-1].Format != enDXGI_Format ||
                psDXGI_Mode[uiIndex-1].Width != uiWidth ||
                psDXGI_Mode[uiIndex-1].Height != uiHeight )
            {
                break;
            };

            if (  psRequest->m_uiRefresh_Rate__Denominator*psDXGI_Mode[uiIndex].RefreshRate.Numerator
                > psRequest->m_uiRefresh_Rate__Numerator*psDXGI_Mode[uiIndex].RefreshRate.Denominator)
            {
                break;
            };
        };
    };

    psSelect->m_sBuffer.m_uiWidth = psDXGI_Mode[uiIndex].Width;
    psSelect->m_sBuffer.m_uiHeight = psDXGI_Mode[uiIndex].Height;
    psSelect->m_uiRefresh_Rate__Numerator = psDXGI_Mode[uiIndex].RefreshRate.Numerator;
    psSelect->m_uiRefresh_Rate__Denominator = psDXGI_Mode[uiIndex].RefreshRate.Denominator;
    psSelect->m_sBuffer.m_enFormat = psRequest->m_sBuffer.m_enFormat;

    return (KTgS_OK);
}


/* ---- tgKN_GPU_Select_Max_Mode ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* These generic GPU functions need to be defined in the API layer as we do not copy all of the modes to the generic layer.                                                        */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_Select_Max_Mode( STg2_KN_GPU_Mode_PC psSelect, TgUINT_E32_C uiAdapter_Index, TgUINT_E32_C uiOutput_Index, STg2_KN_GPU_Mode_CPC psRequest )
{
    TgUINT_E32                          uiWidth = psRequest->m_sBuffer.m_uiWidth;
    TgUINT_E32                          uiHeight = psRequest->m_sBuffer.m_uiHeight;
    DXGI_FORMAT const                   enDXGI_Format = (DXGI_FORMAT)psRequest->m_sBuffer.m_enFormat;

    TgRSIZE                             nuiModes;
    DXGI_MODE_DESC1_P                   psDXGI_Mode;
    TgUINT_E32                          uiIndex;

    TgPARAM_CHECK(nullptr != psSelect);
    TgPARAM_CHECK(nullptr != psRequest);

    nuiModes = g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Adapter[uiAdapter_Index].m_asEXT_Output[uiOutput_Index].m_nuiDXGI_Mode;
    psDXGI_Mode = g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Adapter[uiAdapter_Index].m_asEXT_Output[uiOutput_Index].m_psDXGI_Mode;
    uiIndex = 0;
    if (psDXGI_Mode[uiIndex].Width < uiWidth)
    {
        for (; uiIndex < nuiModes; ++uiIndex)
        {
            if (psDXGI_Mode[uiIndex].Width >= uiWidth)
            {
                break;
            };
        };
    };

    if (uiIndex == nuiModes)
    {
        uiWidth = psDXGI_Mode[--uiIndex].Width;
        for (; uiIndex > 0; --uiIndex)
        {
            if (psDXGI_Mode[uiIndex-1].Width != uiWidth)
            {
                break;
            };
        };
    }
    else
    {
        uiWidth = psDXGI_Mode[uiIndex].Width;
    };

    if (psDXGI_Mode[uiIndex].Height < uiHeight)
    {
        for (;; ++uiIndex)
        {
            if (uiIndex == nuiModes || uiWidth != psDXGI_Mode[uiIndex].Width)
            {
                uiHeight = psDXGI_Mode[--uiIndex].Height;
                for (; uiIndex > 0; --uiIndex)
                {
                    if (psDXGI_Mode[uiIndex-1].Height != uiHeight || psDXGI_Mode[uiIndex-1].Width != uiWidth)
                    {
                        break;
                    };
                };
                break;
            };

            if( psDXGI_Mode[uiIndex].Height >= uiHeight )
            {
                break;
            };
        };
    };

    uiHeight = psDXGI_Mode[uiIndex].Height;

    if (psDXGI_Mode[uiIndex].Format != enDXGI_Format)
    {
        for (;; ++uiIndex)
        {
            if (   uiIndex == nuiModes
                || psDXGI_Mode[uiIndex].Width != uiWidth
                || psDXGI_Mode[uiIndex].Height != uiHeight
                || psDXGI_Mode[uiIndex].Format == enDXGI_Format)
            {
                break;
            };
        };
    };

    if (   uiIndex == nuiModes
        || psDXGI_Mode[uiIndex].Width != uiWidth
        || psDXGI_Mode[uiIndex].Height != uiHeight
        || psDXGI_Mode[uiIndex].Format != enDXGI_Format
    ) {
            return (KTgE_FAIL);
    };

    if (psRequest->m_uiRefresh_Rate__Denominator*psDXGI_Mode[uiIndex].RefreshRate.Numerator < psRequest->m_uiRefresh_Rate__Numerator*psDXGI_Mode[uiIndex].RefreshRate.Denominator)
    {
        for( ;; ++uiIndex )
        {
            if (   uiIndex == nuiModes
                || psDXGI_Mode[uiIndex].Width != uiWidth
                || psDXGI_Mode[uiIndex].Height != uiHeight
                || psDXGI_Mode[uiIndex].Format != enDXGI_Format)
            {
                --uiIndex;
                break;
            };

            if (  psRequest->m_uiRefresh_Rate__Denominator*psDXGI_Mode[uiIndex].RefreshRate.Numerator
                > psRequest->m_uiRefresh_Rate__Numerator*psDXGI_Mode[uiIndex].RefreshRate.Denominator)
            {
                break;
            };
        };
    };

    psSelect->m_sBuffer.m_uiWidth = psDXGI_Mode[uiIndex].Width;
    psSelect->m_sBuffer.m_uiHeight = psDXGI_Mode[uiIndex].Height;
    psSelect->m_uiRefresh_Rate__Numerator = psDXGI_Mode[uiIndex].RefreshRate.Numerator;
    psSelect->m_uiRefresh_Rate__Denominator = psDXGI_Mode[uiIndex].RefreshRate.Denominator;
    psSelect->m_sBuffer.m_enFormat = psRequest->m_sBuffer.m_enFormat;

    return (KTgS_OK);
}
