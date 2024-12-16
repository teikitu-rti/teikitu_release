/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (WINDOWS) Kernel - Unit Test.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

static TgSINT_E64 __stdcall
tgKN_OS_UNIT_TEST__UTIL__Window_Update(
    HWND hWnd, TgUINT_E32 uMessage, TgUINT_E64 wParam, TgSINT_E64 lParam );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_OS_UNIT_TEST__UTIL__Init_Windows ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRSIZE tgKN_OS_UNIT_TEST__UTIL__Init_Windows( STg2_KN_OS_UNIT_TEST__UTIL__Window_PC psWnd, TgRSIZE_C nuiWnd, TgBOOL_C bSingle )
{
    STg2_KN_OS_Window_Configuration     sWin_Config;
    TgOSCHAR                            szBuffer[256];
    TgRSIZE_C                           nuiWnd_MAX = tgCM_MIN_UMAX( 9u, tgCM_MIN_UMAX( nuiWnd, KTgKN_MAX_WINDOWS ) );

    if (0 == nuiWnd || (!bSingle && 9 > nuiWnd_MAX))
    {
        return (0);
    }

    tgMM_Set_U08_0x00( &sWin_Config, sizeof(sWin_Config) );

    sWin_Config.m_pfnWndProc = tgKN_OS_UNIT_TEST__UTIL__Window_Update;
    sWin_Config.m_bCenterOnMonitor = 1;
    sWin_Config.m_bTitle_Include_Default = true;
    sWin_Config.m_bTitle_Include_Dimensions = true;

    TgOS_TEXT_FCN(PrintF)( szBuffer, 256, TgOS_TEXT(" No Swap Chain, No Update") );

    psWnd[bSingle ? 0: 4].m_iWnd = tgKN_OS_Create_Window( &sWin_Config );
    if (0 > psWnd[bSingle ? 0: 4].m_iWnd)
    {
        return (0);
    }

    psWnd[bSingle ? 0: 4].m_hWnd = tgKN_OS_Query_Window_Handle( psWnd[bSingle ? 0: 4].m_iWnd );
    psWnd[bSingle ? 0: 4].m_iOutput = -1;

    tgKN_OS_Set_Window_Title(psWnd[bSingle ? 0: 4].m_iWnd, szBuffer, 256 );

    if (bSingle)
    {
        return (1);
    }

    tgKN_OS_Query_Window_Configuration( &sWin_Config, psWnd[bSingle ? 0: 4].m_iWnd );

    sWin_Config.m_szDefault_Title[0] = sWin_Config.m_szTitle[0] = sWin_Config.m_szClass_Name[0] = 0;
    sWin_Config.m_bCenterOnMonitor = 0;

    {
        TgSINT_E32_C                        iWindow_X0 = sWin_Config.m_iWindow_X0 - (TgSINT_E32)sWin_Config.m_uiRender_Target_W - tgKN_Query_Window_PadX() - 25;
        TgSINT_E32_C                        iWindow_Y0 = sWin_Config.m_iWindow_Y0 - (TgSINT_E32)sWin_Config.m_uiRender_Target_H - tgKN_Query_Window_PadY() - 25;
        TgRSIZE                             uiIndex;
            
        for (uiIndex = 0; uiIndex < nuiWnd_MAX; ++uiIndex)
        {
            if (4 == uiIndex)
                continue;

            sWin_Config.m_iWindow_X0 = iWindow_X0 + ((TgSINT_E32)uiIndex % 3)*((TgSINT_E32)sWin_Config.m_uiRender_Target_W + tgKN_Query_Window_PadX() + 25);
            sWin_Config.m_iWindow_Y0 = iWindow_Y0 + ((TgSINT_E32)uiIndex / 3)*((TgSINT_E32)sWin_Config.m_uiRender_Target_H + tgKN_Query_Window_PadY() + 25);
            psWnd[uiIndex].m_iWnd = tgKN_OS_Create_Window( &sWin_Config );
            if (0 > psWnd[uiIndex].m_iWnd)
            {
                continue;
            }
            psWnd[uiIndex].m_hWnd = tgKN_OS_Query_Window_Handle( psWnd[uiIndex].m_iWnd );
            psWnd[uiIndex].m_iOutput = -1;
            tgKN_OS_Set_Window_Title(psWnd[uiIndex].m_iWnd, szBuffer, 256 );
        }
    }

    return (nuiWnd_MAX);
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgUT_KN_GPU_Base_Window_Update ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgSINT_E64 __stdcall tgKN_OS_UNIT_TEST__UTIL__Window_Update( HWND hWnd, TgUINT_E32 uMessage, TgUINT_E64 wParam, TgSINT_E64 lParam )
{
    WNDPROC                             pfnDefault_Function = tgKN_OS_Query_Default_WndProc();

#if TgCOMPILE__CONSOLE
    switch (uMessage)
    {
        case WM_KEYDOWN:
            tgCN_OS_Process_Input( wParam, false );
            break;
        default:
            break;
    };
/*# TgCOMPILE__CONSOLE */
#endif

    if (pfnDefault_Function)
    {
        return (pfnDefault_Function( hWnd, uMessage, wParam, lParam ));
    }
    else
    {
        return (-1);
    };
}
