/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (WINDOWS) Common - Console.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.21 | »GUID« AEEC8393-9780-4ECA-918D-E3E11F7E2744 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "TgS Common - Console - Internal.h"


/* == Common ===================================================================================================================================================================== */
#if TgCOMPILE__CONSOLE

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgCN_OS_Process_Input ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* This can only be called by a single thread (the input system).  It is not globally multi-thread safe */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgCN_OS_Process_Input( TgUINT_E64 wParam, TgBOOL bCtrl )
{
    /* Enforce the string length limits of the buffer. */
    if (g_uiOS_Console_Cmd_Index + 4 > KTgCN_OSCON_LINE_LENGTH)
    {
        return;
    };

    tgPM_MT_MX_Wait_Block( &g_sCN_OS_Lock );

    switch (wParam)
    {
        case VK_BACK: /**< Backspace */
            g_uiOS_Console_Cmd_Index = tgCM_MAX_UMAX( tgCM_MAX_UMAX( g_uiOS_Console_Cmd_Index, 1u ) - 1, 2 );
            g_szOS_Console_Buffer[g_uiOS_Console_Buffer_Index][g_uiOS_Console_Cmd_Index] = 0;
            break;

        case VK_TAB: /**< Tab */
            g_szOS_Console_Buffer[g_uiOS_Console_Buffer_Index][g_uiOS_Console_Cmd_Index++] = ' ';
            g_szOS_Console_Buffer[g_uiOS_Console_Buffer_Index][g_uiOS_Console_Cmd_Index++] = ' ';
            g_szOS_Console_Buffer[g_uiOS_Console_Buffer_Index][g_uiOS_Console_Cmd_Index++] = ' ';
            g_szOS_Console_Buffer[g_uiOS_Console_Buffer_Index][g_uiOS_Console_Cmd_Index++] = ' ';
            g_szOS_Console_Buffer[g_uiOS_Console_Buffer_Index][g_uiOS_Console_Cmd_Index] = 0;
            break;

        case VK_RETURN: /**< Enter */
            if (0 != g_szOS_Console_Buffer[g_uiOS_Console_Buffer_Index][2])
            {
                tgCN_Execute_Command( g_szOS_Console_Buffer[g_uiOS_Console_Buffer_Index] + 2, KTgMAX_RSIZE );
                g_uiOS_Console_Display_Index = g_uiOS_Console_Buffer_Index;
                g_uiOS_Console_Buffer_Index = (g_uiOS_Console_Buffer_Index + 1) % KTgCN_OSCON_MAX_LINE;
                g_szOS_Console_Buffer[g_uiOS_Console_Buffer_Index][0] = '>';
                g_szOS_Console_Buffer[g_uiOS_Console_Buffer_Index][1] = ' ';
                g_szOS_Console_Buffer[g_uiOS_Console_Buffer_Index][2] = 0;
                g_uiOS_Console_Cmd_Index = 2;
                g_uiOS_Console_Cmd_History_Index = 0;
            }
            break;

        case 0xC0:
            g_bOS_Console_Render = !g_bOS_Console_Render;
            break;

        case 0x21:
            tgCN_Scroll_Display( 0, -1 );
            break;

        case 0x22:
            tgCN_Scroll_Display( 0, 1 );
            break;

        case 0x23:
            g_uiOS_Console_Display_Index = (KTgCN_OSCON_MAX_LINE + g_uiOS_Console_Buffer_Index - 1) % KTgCN_OSCON_MAX_LINE;
            break;

        case 0x24:
            tgCN_Scroll_Display( 0, KTgMIN_S32 );
            break;

        case VK_LEFT: /**< Left */
            break;

        case VK_UP:
            if (bCtrl)
            {
                tgCN_Scroll_Display( -1, 0 );
            }
            else if (g_uiOS_Console_Cmd_History_Index < KTgCN_OSCON_MAX_LINE - 1)
            {
                TgRSIZE                             uiIndex;

                uiIndex = (KTgCN_OSCON_MAX_LINE + g_uiOS_Console_Buffer_Index - g_uiOS_Console_Cmd_History_Index - 1) % KTgCN_OSCON_MAX_LINE;
                if (0 != g_szOS_Console_Buffer[uiIndex][0])
                {
                    ++g_uiOS_Console_Cmd_History_Index;
                    tgUSZ_Copy( g_szOS_Console_Buffer[g_uiOS_Console_Buffer_Index], KTgCN_OSCON_LINE_LENGTH, g_szOS_Console_Buffer[uiIndex], KTgCN_OSCON_LINE_LENGTH );
                    g_uiOS_Console_Cmd_Index = tgUSZ_Length_U08( g_szOS_Console_Buffer[g_uiOS_Console_Buffer_Index], KTgCN_OSCON_LINE_LENGTH );
                }
            };
            break;

        case VK_RIGHT: /**< Right */
            break;

        case VK_DOWN:
            if (bCtrl)
            {
                tgCN_Scroll_Display( 1, 0 );
            }
            else if (g_uiOS_Console_Cmd_History_Index > 0)
            {
                --g_uiOS_Console_Cmd_History_Index;

                if (0 == g_uiOS_Console_Cmd_History_Index)
                {
                    g_szOS_Console_Buffer[g_uiOS_Console_Buffer_Index][0] = '>';
                    g_szOS_Console_Buffer[g_uiOS_Console_Buffer_Index][1] = ' ';
                    g_szOS_Console_Buffer[g_uiOS_Console_Buffer_Index][2] = 0;
                    g_uiOS_Console_Cmd_Index = 2;
                }
                else
                {
                    TgRSIZE                             uiIndex;

                    uiIndex = (KTgCN_OSCON_MAX_LINE + g_uiOS_Console_Buffer_Index - g_uiOS_Console_Cmd_History_Index) % KTgCN_OSCON_MAX_LINE;
                    tgUSZ_Copy( g_szOS_Console_Buffer[g_uiOS_Console_Buffer_Index], KTgCN_OSCON_LINE_LENGTH, g_szOS_Console_Buffer[uiIndex], KTgCN_OSCON_LINE_LENGTH );
                    g_uiOS_Console_Cmd_Index = tgUSZ_Length_U08( g_szOS_Console_Buffer[g_uiOS_Console_Buffer_Index],KTgCN_OSCON_LINE_LENGTH );
                };
            };
            break;

        default:
            if (wParam >= 0x20)
            {
                /* FIXME: Need to rethink this for MB */
                g_szOS_Console_Buffer[g_uiOS_Console_Buffer_Index][g_uiOS_Console_Cmd_Index++] = (TgCHAR_U8)(wParam & 0xFF);
                g_szOS_Console_Buffer[g_uiOS_Console_Buffer_Index][g_uiOS_Console_Cmd_Index] = 0;
            };
            break;
    };

    tgPM_MT_MX_Release( &g_sCN_OS_Lock );
}


/* =============================================================================================================================================================================== */
/*# TgCOMPILE__CONSOLE */
#endif
