/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (POSIX) Common - Console.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "TgS Common - Console - Internal.h"


/* == Common ===================================================================================================================================================================== */
#if TgCOMPILE__CONSOLE

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

static TgVOID                               tgCN_Scroll_Display( TgSINT_E32_C , TgSINT_E32_C  );




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
        case 0x08: /**< Backspace */
            g_uiOS_Console_Cmd_Index = tgCM_MAX_UMAX( tgCM_MAX_UMAX( g_uiOS_Console_Cmd_Index, 1u ) - 1, 2 );
            g_szOS_Console_Buffer[g_uiOS_Console_Buffer_Index][g_uiOS_Console_Cmd_Index] = 0;
            break;
        case 0x09: /**< Tab */
            g_szOS_Console_Buffer[g_uiOS_Console_Buffer_Index][g_uiOS_Console_Cmd_Index++] = ' ';
            g_szOS_Console_Buffer[g_uiOS_Console_Buffer_Index][g_uiOS_Console_Cmd_Index++] = ' ';
            g_szOS_Console_Buffer[g_uiOS_Console_Buffer_Index][g_uiOS_Console_Cmd_Index++] = ' ';
            g_szOS_Console_Buffer[g_uiOS_Console_Buffer_Index][g_uiOS_Console_Cmd_Index++] = ' ';
            g_szOS_Console_Buffer[g_uiOS_Console_Buffer_Index][g_uiOS_Console_Cmd_Index] = 0;
            break;
        case 0x0D: /**< Enter */
            tgCN_Execute_Command( g_szOS_Console_Buffer[g_uiOS_Console_Buffer_Index] + 2, KTgMAX_RSIZE );
            g_uiOS_Console_Display_Index = g_uiOS_Console_Buffer_Index;
            g_uiOS_Console_Buffer_Index = (g_uiOS_Console_Buffer_Index + 1) % KTgCN_OSCON_MAX_LINE;
            g_szOS_Console_Buffer[g_uiOS_Console_Buffer_Index][0] = '>';
            g_szOS_Console_Buffer[g_uiOS_Console_Buffer_Index][1] = ' ';
            g_szOS_Console_Buffer[g_uiOS_Console_Buffer_Index][2] = 0;
            g_uiOS_Console_Cmd_Index = 2;
            g_uiOS_Console_Cmd_History_Index = 0;
            break;
        case '`':
            g_bOS_Console_Render = !g_bOS_Console_Render;
            break;

        case 0x21:
            if (bCtrl)
            {
                tgCN_Scroll_Display( 0, -1 );
            }
            else
            {
            };
            break;
        case 0x22:
            if (bCtrl)
            {
                tgCN_Scroll_Display( 0, 1 );
            }
            else
            {
            };
            break;
        case 0x23:
            if (bCtrl)
            {
                g_uiOS_Console_Display_Index = g_uiOS_Console_Buffer_Index;
            }
            else
            {
            };
            break;
        case 0x24:
            if (bCtrl)
            {
            }
            else
            {
            };
            break;
        case 0x25: /**< Left */
            break;
        case 0x26:
            if (bCtrl)
            {
                tgCN_Scroll_Display( -1, 0 );
            }
            else if (g_uiOS_Console_Cmd_History_Index < KTgCN_OSCON_MAX_LINE - 1)
            {
                TgRSIZE                             uiIndex;

                ++g_uiOS_Console_Cmd_History_Index;
                uiIndex = (KTgCN_OSCON_MAX_LINE + g_uiOS_Console_Buffer_Index - g_uiOS_Console_Cmd_History_Index) % KTgCN_OSCON_MAX_LINE;
                tgUSZ_Copy( g_szOS_Console_Buffer[g_uiOS_Console_Buffer_Index], KTgCN_OSCON_LINE_LENGTH, g_szOS_Console_Buffer[uiIndex], KTgMAX_RSIZE );
            };
            break;
        case 0x27: /**< Right */
            break;
        case 0x28:
            if (bCtrl)
            {
                tgCN_Scroll_Display( 1, 0 );
            }
            else if (g_uiOS_Console_Cmd_History_Index > 0)
            {
                if (0 == --g_uiOS_Console_Cmd_History_Index)
                {
                    g_szOS_Console_Buffer[g_uiOS_Console_Buffer_Index][0] = 0;
                }
                else
                {
                    TgRSIZE                             uiIndex;

                    uiIndex = (KTgCN_OSCON_MAX_LINE + g_uiOS_Console_Buffer_Index - g_uiOS_Console_Cmd_History_Index) % KTgCN_OSCON_MAX_LINE;
                    tgUSZ_Copy( g_szOS_Console_Buffer[g_uiOS_Console_Buffer_Index], KTgCN_OSCON_LINE_LENGTH, g_szOS_Console_Buffer[uiIndex], KTgMAX_RSIZE );
                };
            };
            break;

        default:
            if (wParam >= 0x20)
            {
                /* FIXME: Need to rethink this for MB */
                g_szOS_Console_Buffer[g_uiOS_Console_Buffer_Index][g_uiOS_Console_Cmd_Index++] = (TgCHAR_U8)(wParam * 0xFF);
                g_szOS_Console_Buffer[g_uiOS_Console_Buffer_Index][g_uiOS_Console_Cmd_Index] = 0;
            };
            break;
    };

    tgPM_MT_MX_Release( &g_sCN_OS_Lock );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgCN_Scroll_Display ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* NOTE: This should only be called by tgCN_OS_Process_Input due to synchronization on internal variables */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgCN_Scroll_Display( TgSINT_E32_C niLN, TgSINT_E32_C niPG )
{
    TgRSIZE                             uiNew_Index, uiTest;
    TgSINT_E32                          iCount, iChange;

    iChange = niLN + niPG*(TgSINT_E32)g_nuiOS_Console_Render_Page_Height;
    uiNew_Index = g_uiOS_Console_Display_Index;

    if (0 == g_szOS_Console_Buffer[g_uiOS_Console_Display_Index][0])
        return;

    if (iChange < 0)
    {
        for (iCount = 0; iCount > iChange; --iCount)
        {
            uiTest = (KTgCN_OSCON_MAX_LINE + uiNew_Index - 1) % KTgCN_OSCON_MAX_LINE;

            if (g_nuiOS_Console_Render_Page_Height >= (KTgCN_OSCON_MAX_LINE + uiTest - g_uiOS_Console_Buffer_Index) % KTgCN_OSCON_MAX_LINE)
                break;
            if (0 == g_szOS_Console_Buffer[uiTest][0])
                break;

            uiNew_Index = uiTest;
        };
    }
    else
    {
        for (iCount = 0; iCount < iChange; ++iCount)
        {
            uiTest = (KTgCN_OSCON_MAX_LINE + uiNew_Index + 1) % KTgCN_OSCON_MAX_LINE;

            if (uiTest == g_uiOS_Console_Buffer_Index)
                break;
            if (0 == g_szOS_Console_Buffer[uiTest][0])
                break;

            uiNew_Index = uiTest;
        };
    }

    g_uiOS_Console_Display_Index = uiNew_Index;
}


/* =============================================================================================================================================================================== */
/*# TgCOMPILE__CONSOLE */
#endif
