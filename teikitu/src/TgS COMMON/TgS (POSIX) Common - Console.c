/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (POSIX) Common - Console.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Common ===================================================================================================================================================================== */

/* ---- tgCN_OS_Process_Input ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* This can only be called by a single thread (the input system).  It is not globally multi-thread safe */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if TgCOMPILE__CONSOLE
TgVOID tgCN_OS_Process_Input( TgUINT_F64 wParam, TgBOOL bCtrl )
{
    /* Enforce the string length limits of the buffer. */
    if (s_uiOS_Console_Cmd_Index + 4 > KTgCN_OSCON_LINE_LENGTH)
    {
        return;
    };

    tgPM_MT_MX_Wait_Block( &s_sOS_Lock );

    switch (wParam)
    {
        case 0x08: /**< Backspace */
            s_uiOS_Console_Cmd_Index = tgCM_MAX_UMAX( tgCM_MAX_UMAX( s_uiOS_Console_Cmd_Index, 1u ) - 1, 2 );
            s_szOS_Console_Buffer[s_uiOS_Console_Buffer_Index][s_uiOS_Console_Cmd_Index] = 0;
            break;
        case 0x09: /**< Tab */
            s_szOS_Console_Buffer[s_uiOS_Console_Buffer_Index][s_uiOS_Console_Cmd_Index++] = ' ';
            s_szOS_Console_Buffer[s_uiOS_Console_Buffer_Index][s_uiOS_Console_Cmd_Index++] = ' ';
            s_szOS_Console_Buffer[s_uiOS_Console_Buffer_Index][s_uiOS_Console_Cmd_Index++] = ' ';
            s_szOS_Console_Buffer[s_uiOS_Console_Buffer_Index][s_uiOS_Console_Cmd_Index++] = ' ';
            s_szOS_Console_Buffer[s_uiOS_Console_Buffer_Index][s_uiOS_Console_Cmd_Index] = 0;
            break;
        case 0x0D: /**< Enter */
            tgCN_Execute_Command( s_szOS_Console_Buffer[s_uiOS_Console_Buffer_Index] + 2, KTgMAX_RSIZE );
            s_uiOS_Console_Display_Index = s_uiOS_Console_Buffer_Index;
            s_uiOS_Console_Buffer_Index = (s_uiOS_Console_Buffer_Index + 1) % KTgCN_OSCON_MAX_LINE;
            s_szOS_Console_Buffer[s_uiOS_Console_Buffer_Index][0] = '>';
            s_szOS_Console_Buffer[s_uiOS_Console_Buffer_Index][1] = ' ';
            s_szOS_Console_Buffer[s_uiOS_Console_Buffer_Index][2] = 0;
            s_uiOS_Console_Cmd_Index = 2;
            s_uiOS_Console_Cmd_History_Index = 0;
            break;
        case '`':
            s_bOS_Console_Render = !s_bOS_Console_Render;
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
                s_uiOS_Console_Display_Index = s_uiOS_Console_Buffer_Index;
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
            else if (s_uiOS_Console_Cmd_History_Index < KTgCN_OSCON_MAX_LINE - 1)
            {
                TgRSIZE                             uiIndex;

                ++s_uiOS_Console_Cmd_History_Index;
                uiIndex = (KTgCN_OSCON_MAX_LINE + s_uiOS_Console_Buffer_Index - s_uiOS_Console_Cmd_History_Index) % KTgCN_OSCON_MAX_LINE;
                tgUSZ_Copy( s_szOS_Console_Buffer[s_uiOS_Console_Buffer_Index], KTgCN_OSCON_LINE_LENGTH, s_szOS_Console_Buffer[uiIndex], KTgMAX_RSIZE );
            };
            break;
        case 0x27: /**< Right */
            break;
        case 0x28:
            if (bCtrl)
            {
                tgCN_Scroll_Display( 1, 0 );
            }
            else if (s_uiOS_Console_Cmd_History_Index > 0)
            {
                if (0 == --s_uiOS_Console_Cmd_History_Index)
                {
                    s_szOS_Console_Buffer[s_uiOS_Console_Buffer_Index][0] = 0;
                }
                else
                {
                    TgRSIZE                             uiIndex;

                    uiIndex = (KTgCN_OSCON_MAX_LINE + s_uiOS_Console_Buffer_Index - s_uiOS_Console_Cmd_History_Index) % KTgCN_OSCON_MAX_LINE;
                    tgUSZ_Copy( s_szOS_Console_Buffer[s_uiOS_Console_Buffer_Index], KTgCN_OSCON_LINE_LENGTH, s_szOS_Console_Buffer[uiIndex], KTgMAX_RSIZE );
                };
            };
            break;

        default:
            if (wParam >= 0x20)
            {
                /* FIXME: Need to rethink this for MB */
                s_szOS_Console_Buffer[s_uiOS_Console_Buffer_Index][s_uiOS_Console_Cmd_Index++] = (TgCHAR_U8)(wParam * 0xFF);
                s_szOS_Console_Buffer[s_uiOS_Console_Buffer_Index][s_uiOS_Console_Cmd_Index] = 0;
            };
            break;
    };

    tgPM_MT_MX_Release( &s_sOS_Lock );
}
/*# TgCOMPILE__CONSOLE */
#endif
