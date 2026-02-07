/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (WINDOWS) Kernel [GPU] - System [Select].c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
#if defined(TgBUILD_FEATURE__GRAPHICS)

#include "TgS Kernel [GPU] - Internal.h"

#include "TgS (DXGI) Kernel [GPU] - Internal.h"


/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/** @brief Select the minimum mode for a given display output.
    @param [out] OUT0 Pointer to the selected mode.
    @param [in] ARG1 Pointer to the requested mode.
    @param [in] ARG2 Index of the display output.
    @return Result Code. */
static TgRESULT
tgKN_OS_GPU_Select_Min_Mode_Local(
    STg2_KN_OS_GPU_Mode_PC OUT0, STg2_KN_OS_GPU_Mode_CPC ARG1, TgRSIZE_C ARG2 );

static ETgKN_OS_GPU_FORMAT
tgKN_OS_GPU_Convert_To_OS_Format(
    ETgKN_GPU_EXT_FORMAT_C ARG0);




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_OS_GPU_Query_Mode_List ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRSIZE tgKN_OS_GPU_Query_Mode_List( STg2_KN_OS_GPU_Mode_P psMode, TgRSIZE_C nuiMode, TgRSIZE_C uiOS_DXGI_Output_Index, ETgKN_OS_GPU_FORMAT_C enFormat )
{
    DXGI_FORMAT                         enDXGI_Format;
    TgRSIZE                             nuiRet;
    TgRSIZE                             uiMode;

    TgPARAM_CHECK_INDEX( uiOS_DXGI_Output_Index, g_asDXGI_Output );

    enDXGI_Format = (DXGI_FORMAT)enFormat;
    nuiRet = 0;

    if (nullptr == psMode)
    {
        for (uiMode = 0; uiMode < g_asDXGI_Output[uiOS_DXGI_Output_Index].m_nuiDXGI_Mode; ++uiMode)
        {
            if (g_asDXGI_Output[uiOS_DXGI_Output_Index].m_psDXGI_Mode[uiMode].Format != enDXGI_Format)
                continue;
            ++nuiRet;
        };
    }
    else
    {
        for (uiMode = 0; uiMode < g_asDXGI_Output[uiOS_DXGI_Output_Index].m_nuiDXGI_Mode; ++uiMode)
        {
            if (g_asDXGI_Output[uiOS_DXGI_Output_Index].m_psDXGI_Mode[uiMode].Format != enDXGI_Format)
                continue;
            if (nuiRet < nuiMode)
            {
                psMode[nuiRet].m_uiWidth = g_asDXGI_Output[uiOS_DXGI_Output_Index].m_psDXGI_Mode[uiMode].Width;
                psMode[nuiRet].m_uiHeight = g_asDXGI_Output[uiOS_DXGI_Output_Index].m_psDXGI_Mode[uiMode].Height;
                psMode[nuiRet].m_uiRefresh_Rate__Numerator = g_asDXGI_Output[uiOS_DXGI_Output_Index].m_psDXGI_Mode[uiMode].RefreshRate.Numerator;
                psMode[nuiRet].m_uiRefresh_Rate__Denominator = g_asDXGI_Output[uiOS_DXGI_Output_Index].m_psDXGI_Mode[uiMode].RefreshRate.Denominator;
                psMode[nuiRet].m_enFormat  = enFormat;
            };
            ++nuiRet;
        };
    };

    return (nuiRet);
}


/* ---- tgKN_OS_GPU_Query_Monitor_Min_Resolution --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_OS_GPU_Query_Monitor_Min_Resolution( TgUINT_E32_P puiW, TgUINT_E32_P puiH, HMONITOR hMonitor )
{
    TgRSIZE                             uiDisplay_Output;
    DXGI_MODE_DESC1_P                   psDXGI_Mode;

    if (hMonitor == nullptr || nullptr == puiW || nullptr == puiH)
        return;

    *puiW = 640;
    *puiH = 480;

    for (uiDisplay_Output = 0; uiDisplay_Output < g_nuiDXGI_Output; ++uiDisplay_Output)
    {
        if (hMonitor != g_asDXGI_Output[uiDisplay_Output].m_sDXGI_Output_DESC.Monitor)
            continue;
        psDXGI_Mode = g_asDXGI_Output[uiDisplay_Output].m_psDXGI_Mode;
        *puiW = psDXGI_Mode[0].Width;
        *puiH = psDXGI_Mode[0].Height;
        return;
    };
}


/* ---- tgKN_OS_GPU_Query_Monitor_Max_Resolution --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_OS_GPU_Query_Monitor_Max_Resolution( TgUINT_E32_P puiW, TgUINT_E32_P puiH, HMONITOR hMonitor )
{
    TgRSIZE                             uiDisplay_Output;
    DXGI_MODE_DESC1_P                   psDXGI_Mode;

    if (hMonitor == nullptr || nullptr == puiW || nullptr == puiH)
        return;

    *puiW = 640;
    *puiH = 480;

    for (uiDisplay_Output = 0; uiDisplay_Output < g_nuiDXGI_Output; ++uiDisplay_Output)
    {
        if (hMonitor != g_asDXGI_Output[uiDisplay_Output].m_sDXGI_Output_DESC.Monitor)
            continue;
        psDXGI_Mode = g_asDXGI_Output[uiDisplay_Output].m_psDXGI_Mode;
        *puiW = psDXGI_Mode[g_asDXGI_Output[uiDisplay_Output].m_nuiDXGI_Mode - 1].Width;
        *puiH = psDXGI_Mode[g_asDXGI_Output[uiDisplay_Output].m_nuiDXGI_Mode - 1].Height;
        return;
    };
}


/* ---- tgKN_OS_GPU_Select_Min_Mode ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_OS_GPU_Select_Min_Mode( STg2_KN_OS_GPU_Mode_PC psSelect, STg2_KN_OS_GPU_Mode_CPC psRequest, HMONITOR hMonitor )
{
    TgRSIZE                             uiDisplay_Output;

    TgPARAM_CHECK(nullptr != psSelect);
    TgPARAM_CHECK(nullptr != psRequest);

    for (uiDisplay_Output = 0; uiDisplay_Output < g_nuiDXGI_Output; ++uiDisplay_Output)
    {
        if (hMonitor == g_asDXGI_Output[uiDisplay_Output].m_sDXGI_Output_DESC.Monitor)
        {
            break;
        };
    };

    return (tgKN_OS_GPU_Select_Min_Mode_Local(psSelect, psRequest, uiDisplay_Output));

}


/* ---- tgKN_OS_GPU_Select_Max_Mode ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* These generic GPU functions need to be defined in the API layer as we do not copy all of the modes to the generic layer.                                                        */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_OS_GPU_Select_Max_Mode( STg2_KN_OS_GPU_Mode_PC psSelect, STg2_KN_OS_GPU_Mode_CPC psRequest, HMONITOR hMonitor )
{
    TgUINT_E32                          uiWidth = psRequest->m_uiWidth;
    TgUINT_E32                          uiHeight = psRequest->m_uiHeight;
    DXGI_FORMAT const                   enDXGI_Format = (DXGI_FORMAT)psRequest->m_enFormat;

    TgRSIZE                             uiDisplay_Output;
    DXGI_MODE_DESC1_P                   psDXGI_Mode;
    TgRSIZE                             nuiModes;
    TgUINT_E32                          uiIndex;

    TgPARAM_CHECK(nullptr != psSelect);
    TgPARAM_CHECK(nullptr != psRequest);

    for (uiDisplay_Output = 0; uiDisplay_Output < g_nuiDXGI_Output; ++uiDisplay_Output)
    {
        if (hMonitor == g_asDXGI_Output[uiDisplay_Output].m_sDXGI_Output_DESC.Monitor)
        {
            break;
        };
    };

    if (uiDisplay_Output >= g_nuiDXGI_Output || (nullptr == g_asDXGI_Output[uiDisplay_Output].m_psDXGI_Mode))
    {
        return (KTgE_FAIL);
    };

    nuiModes = g_asDXGI_Output[uiDisplay_Output].m_nuiDXGI_Mode;
    psDXGI_Mode = g_asDXGI_Output[uiDisplay_Output].m_psDXGI_Mode;
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

    psSelect->m_uiWidth = psDXGI_Mode[uiIndex].Width;
    psSelect->m_uiHeight = psDXGI_Mode[uiIndex].Height;
    psSelect->m_uiRefresh_Rate__Numerator = psDXGI_Mode[uiIndex].RefreshRate.Numerator;
    psSelect->m_uiRefresh_Rate__Denominator = psDXGI_Mode[uiIndex].RefreshRate.Denominator;
    psSelect->m_enFormat = psRequest->m_enFormat;

    return (KTgS_OK);
}


/* ---- tgKN_OS_GPU_CXT_SWAP_Query_Mode ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_OS_GPU_CXT_SWAP_Query_Mode( TgUINT_E32_P puiW, TgUINT_E32_P puiH, HWND hWnd )
{
    TgUINT_E32                          uiSwap;
    union
    {
        HWND                                hWnd;
        TgUINT_PTR                          uiPTR;
    }                                   sHWND;

    if (hWnd == nullptr || nullptr == puiW || nullptr == puiH)
        return;

    sHWND.hWnd = hWnd;
    for (uiSwap = 0; uiSwap < KTgKN_GPU_MAX_SWAP_CONTEXT; ++uiSwap)
    {
        STg2_KN_GPU_CXT_SWAP_CPC            psCXT_SWAP = g_asKN_GPU_CXT_SWAP + uiSwap;

        if (sHWND.uiPTR != g_asKN_GPU_CXT_SWAP[uiSwap].m_uiOS_ID)
            continue;

        *puiW =  psCXT_SWAP->m_sMode.m_sBuffer.m_uiWidth;
        *puiH =  psCXT_SWAP->m_sMode.m_sBuffer.m_uiHeight;
        return;
    };
}


/* ---- tgKN_OS_GPU_CXT_SWAP_Query_Mode_Rounded_Down ----------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_OS_GPU_CXT_SWAP_Query_Mode_Rounded_Down( TgUINT_E32_P puiW, TgUINT_E32_P puiH, HWND hWnd )
{
    TgUINT_E32                          uiSwap;
    STg2_KN_OS_GPU_Mode                 sMode, sMode_Request;
    union
    {
        HWND                                hWnd;
        TgUINT_PTR                          uiPTR;
    }                                   sHWND;

    if (hWnd == nullptr || nullptr == puiW || nullptr == puiH)
        return;

    sHWND.hWnd = hWnd;
    for (uiSwap = 0; uiSwap < KTgKN_GPU_MAX_SWAP_CONTEXT; ++uiSwap)
    {
        STg2_KN_GPU_CXT_SWAP_CPC            psCXT_SWAP = g_asKN_GPU_CXT_SWAP + uiSwap;

        if (sHWND.uiPTR != g_asKN_GPU_CXT_SWAP[uiSwap].m_uiOS_ID)
            continue;

        sMode_Request.m_uiWidth = psCXT_SWAP->m_sMode.m_sBuffer.m_uiWidth;
        sMode_Request.m_uiHeight = psCXT_SWAP->m_sMode.m_sBuffer.m_uiHeight;
        sMode_Request.m_enFormat = tgKN_OS_GPU_Convert_To_OS_Format(psCXT_SWAP->m_sMode.m_sBuffer.m_enFormat);
        sMode_Request.m_uiRefresh_Rate__Numerator = psCXT_SWAP->m_sMode.m_uiRefresh_Rate__Numerator;
        sMode_Request.m_uiRefresh_Rate__Denominator = psCXT_SWAP->m_sMode.m_uiRefresh_Rate__Denominator;

        if (TgSUCCEEDED(tgKN_OS_GPU_Select_Min_Mode_Local(&sMode, &sMode_Request, g_asOS_EXT_Swap_Context_Output[uiSwap].m_uiBest_Output)))
        {
            *puiW = sMode.m_uiWidth;
            *puiH = sMode.m_uiHeight;
        }
        return;
    };
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgSTAT_KN_OS_GPU_Physical_Device_Output ----------------------------------------------------------------------------------------------------------------------------------s */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if TgS_STAT__KERNEL || TgS_DEBUG__KERNEL
TgVOID tgSTAT_KN_OS_GPU_Physical_Device_Output( TgVOID )
{
    TgUINT_E32_C                        uiChannel_Mask = KTgCN_CHANEL_INITIALIZE | KTgCN_SEVERITY_9;

    TgRSIZE                             uiDisplay_Output;
    TgCHAR_U8                           szData[128];

    tgUSZ_Convert_WSZ( szData, TgARRAY_COUNT( szData ), g_asDXGI_Output[0].m_sDXGI_Output_DESC.DeviceName, TgARRAY_COUNT( g_asDXGI_Output[0].m_sDXGI_Output_DESC.DeviceName ) );
    tgCN_PrintF( uiChannel_Mask, u8"%-16.16s(%-48.48s):     - Physical_Device[ %s ]\n", u8"Kernel", u8"tgKN_GPU_PM_Output__Physical_Device", szData );

    for (uiDisplay_Output=0; uiDisplay_Output < g_nuiDXGI_Output; ++uiDisplay_Output)
    {
        TgRSIZE                             uiMode;

        tgUSZ_Convert_WSZ( szData, TgARRAY_COUNT( szData ), g_asDXGI_Output[uiDisplay_Output].m_sDXGI_Output_DESC.DeviceName, TgARRAY_COUNT( g_asDXGI_Output[uiDisplay_Output].m_sDXGI_Output_DESC.DeviceName ) );
        tgCN_PrintF( uiChannel_Mask, u8"%-16.16s(%-48.48s):     - Output[ %s ]\n", u8"Kernel", u8"tgKN_GPU_PM_Output__Physical_Device", szData );

        for (uiMode = 0; uiMode < g_asDXGI_Output[uiDisplay_Output].m_nuiDXGI_Mode; ++uiMode)
        {
            tgCN_PrintF( uiChannel_Mask, u8"%-16.16s(%-48.48s):     - Mode[% 4d]: W[% 5d] H[% 5d] R[% 3d] F[%s]\n", u8"Kernel", u8"tgKN_GPU_PM_Output__Physical_Device",
                         uiMode, g_asDXGI_Output[uiDisplay_Output].m_psDXGI_Mode[uiMode].Width, g_asDXGI_Output[uiDisplay_Output].m_psDXGI_Mode[uiMode].Height,
                         g_asDXGI_Output[uiDisplay_Output].m_psDXGI_Mode[uiMode].RefreshRate.Numerator / g_asDXGI_Output[uiDisplay_Output].m_psDXGI_Mode[uiMode].RefreshRate.Denominator,
                         tgKN_GPU_FMT_To_USZ( (ETgKN_GPU_EXT_FORMAT)g_asDXGI_Output[uiDisplay_Output].m_psDXGI_Mode[uiMode].Format ) );
        };
        tgCN_PrintF( uiChannel_Mask, u8"%-16.16s(%-48.48s):   - Mode Count: %d\n", u8"Kernel", u8"tgKN_GPU_PM_Output__Physical_Device", g_asDXGI_Output[uiDisplay_Output].m_nuiDXGI_Mode );
    };
}
/*# TgS_STAT__KERNEL || TgS_DEBUG__KERNEL */
#endif




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_OS_GPU_Select_Min_Mode_Local ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT tgKN_OS_GPU_Select_Min_Mode_Local( STg2_KN_OS_GPU_Mode_PC psSelect, STg2_KN_OS_GPU_Mode_CPC psRequest, TgRSIZE_C uiDisplay_Output )
{
    TgUINT_E32                          uiWidth = psRequest->m_uiWidth;
    TgUINT_E32                          uiHeight = psRequest->m_uiHeight;
    DXGI_FORMAT const                   enDXGI_Format = (DXGI_FORMAT)psRequest->m_enFormat;

    DXGI_MODE_DESC1_P                   psDXGI_Mode;
    TgRSIZE                             nuiModes;
    TgUINT_E32                          uiIndex;

    TgPARAM_CHECK(nullptr != psSelect);
    TgPARAM_CHECK(nullptr != psRequest);

    if (uiDisplay_Output >= g_nuiDXGI_Output || (nullptr == g_asDXGI_Output[uiDisplay_Output].m_psDXGI_Mode))
    {
        return (KTgE_FAIL);
    };

    nuiModes = g_asDXGI_Output[uiDisplay_Output].m_nuiDXGI_Mode;
    psDXGI_Mode = g_asDXGI_Output[uiDisplay_Output].m_psDXGI_Mode;
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

    psSelect->m_uiWidth = psDXGI_Mode[uiIndex].Width;
    psSelect->m_uiHeight = psDXGI_Mode[uiIndex].Height;
    psSelect->m_uiRefresh_Rate__Numerator = psDXGI_Mode[uiIndex].RefreshRate.Numerator;
    psSelect->m_uiRefresh_Rate__Denominator = psDXGI_Mode[uiIndex].RefreshRate.Denominator;
    psSelect->m_enFormat = psRequest->m_enFormat;

    return (KTgS_OK);
}


/* ---- tgKN_OS_GPU_Convert_To_OS_Format ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static ETgKN_OS_GPU_FORMAT tgKN_OS_GPU_Convert_To_OS_Format(ETgKN_GPU_EXT_FORMAT_C enFormat)
{
    TgWARN_DISABLE_PUSH(4061 4062,switch-enum)
    switch (enFormat)
    {
        case ETgKN_GPU_EXT_FORMAT_R8G8B8A8_UNORM:           return (ETgKN_OS_GPU_FORMAT_R8G8B8A8_UNORM);
        case ETgKN_GPU_EXT_FORMAT_B8G8R8A8_UNORM:           return (ETgKN_OS_GPU_FORMAT_B8G8R8A8_UNORM);
        case ETgKN_GPU_EXT_FORMAT_A2R10G10B10_UNORM_PACK32: return (ETgKN_OS_GPU_FORMAT_A2R10G10B10_UNORM_PACK32);
        case ETgKN_GPU_EXT_FORMAT_R16G16B16A16_SFLOAT:      return (ETgKN_OS_GPU_FORMAT_R16G16B16A16_SFLOAT);
        case ETgKN_GPU_EXT_FORMAT_R32G32B32A32_SFLOAT:      return (ETgKN_OS_GPU_FORMAT_R32G32B32A32_SFLOAT);
        case ETgKN_GPU_EXT_FORMAT_D32_SFLOAT:               return (ETgKN_OS_GPU_FORMAT_D32_SFLOAT);
        default:                                            return (ETgKN_OS_GPU_FORMAT_UNDEFINED);
    }
    TgWARN_DISABLE_POP()
}


/* =============================================================================================================================================================================== */
/*# defined(TgBUILD_FEATURE__GRAPHICS) */
#endif
