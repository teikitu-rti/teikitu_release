/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (WINDOWS) Input - GUI Mouse.c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.12 | »GUID« 964CB1A6-814D-4E19-8E67-A83FCA98BF05 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "TgS COMMON/TgS Common - Util MT - LA Ring Buffer SRSW.inl"


/* == Input ====================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

static TgUINT_E32                           s_aiGUI_Mouse[ETgPROP_GUI_MOUSE_MAX];

static TgSINT_PTR __stdcall
tgIN_PM_Update_GUI_Mouse_Callback(
    HWND, TgUINT_E32 , TgUINT_PTR, TgSINT_PTR ) TgATTRIBUTE_NO_EXCEPT;




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgIN_PM_Init_GUI_Mouse --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgIN_PM_Init_GUI_Mouse( TgVOID )
{
    return (KTgS_OK);
}


/* ---- tgIN_PM_Boot_GUI_Mouse --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgIN_PM_Boot_GUI_Mouse( TgVOID )
{
    tgKN_OS_Set_GUI_Mouse_Callback( tgIN_PM_Update_GUI_Mouse_Callback );
    tgCM_UT_LF__LA_RB_SRSW__Init( &g_asController_Active[ETgCONTROLLER_GUI_MOUSE].m_sLA_RB_SRSW, KTgCONTROLLER_MAX_EVENT );
    return (KTgS_OK);
}


/* ---- tgIN_PM_Stop_GUI_Mouse --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgIN_PM_Stop_GUI_Mouse( TgVOID )
{
    tgKN_OS_Set_GUI_Mouse_Callback( nullptr );
    return (KTgS_OK);
}


/* ---- tgIN_PM_Free_GUI_Mouse --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgIN_PM_Free_GUI_Mouse( TgVOID )
{
    return (KTgS_OK);
}


/* ---- tgIN_PM_Update_GUI_Mouse ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgIN_PM_Update_GUI_Mouse( TgATTRIBUTE_UNUSED ETgCONTROLLER_C enController )
{

}


/* ---- tgIN_PM_Query_Fixed_Memory_GUI_Mouse ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRSIZE tgIN_PM_Query_Fixed_Memory_GUI_Mouse( TgVOID )
{
    return (sizeof( s_aiGUI_Mouse ));
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgIN_PM_Update_GUI_Mouse_Callback ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgSINT_PTR __stdcall tgIN_PM_Update_GUI_Mouse_Callback( HWND hWnd, TgUINT_E32 uiMsg, TgUINT_PTR wParam, TgSINT_PTR lParam ) TgATTRIBUTE_NO_EXCEPT
{
#if !defined(TgBUILD_UNIVERSAL__UWP)
    TgUINT_E32_C                        uiMouseButtonState = wParam & 0xFFFF;
    TgUINT_E32                          aiGUI_Mouse[ETgPROP_GUI_MOUSE_MAX];
    TgSINT_E32                          iIndex;
    TgUINT_E32                          uiEvent;

    if (WM_MOUSEWHEEL == uiMsg)
    {
        /* WM_MOUSEWHEEL passes screen mouse coords so convert them to client coords */
        POINT                               pt;

        pt.x = lParam & 0xFFFF;
        pt.y = (lParam >> 16) & 0xFFFF;

        g_pfnScreenToClient( hWnd, &pt );

        aiGUI_Mouse[ETgPROP_GUI_MOUSE_AXIX_DX] = (TgUINT_E32)pt.x;
        aiGUI_Mouse[ETgPROP_GUI_MOUSE_AXIX_DY] = (TgUINT_E32)pt.y;
        aiGUI_Mouse[ETgPROP_GUI_MOUSE_AXIX_DZ] = WM_MOUSEWHEEL == uiMsg ? (wParam >> 16) & 0xFFFF : 0;
    }
    else
    {
        aiGUI_Mouse[ETgPROP_GUI_MOUSE_AXIX_DX] = (TgUINT_E32)(lParam & 0xFFFF);
        aiGUI_Mouse[ETgPROP_GUI_MOUSE_AXIX_DY] = (TgUINT_E32)((lParam >> 16) & 0xFFFF);
        aiGUI_Mouse[ETgPROP_GUI_MOUSE_AXIX_DZ] = WM_MOUSEWHEEL == uiMsg ? (wParam >> 16) & 0xFFFF : 0;
    }

    aiGUI_Mouse[ETgPROP_GUI_MOUSE_BUTTON0] = ((uiMouseButtonState & MK_LBUTTON) != 0);
    aiGUI_Mouse[ETgPROP_GUI_MOUSE_BUTTON1] = ((uiMouseButtonState & MK_MBUTTON) != 0);
    aiGUI_Mouse[ETgPROP_GUI_MOUSE_BUTTON2] = ((uiMouseButtonState & MK_RBUTTON) != 0);
    aiGUI_Mouse[ETgPROP_GUI_MOUSE_BUTTON3] = ((uiMouseButtonState & MK_XBUTTON1) != 0);
    aiGUI_Mouse[ETgPROP_GUI_MOUSE_BUTTON4] = ((uiMouseButtonState & MK_XBUTTON2) != 0);

    if (nullptr == g_asController_Active[ETgCONTROLLER_GUI_MOUSE].m_psConsumer)
    {
        tgMM_Copy( s_aiGUI_Mouse, sizeof( s_aiGUI_Mouse ), aiGUI_Mouse, sizeof( aiGUI_Mouse ) );
        return (0);
    };

    /* Generate events based on the change between this state and the previous state. */
    for (iIndex = 0; iIndex < ETgPROP_GUI_MOUSE_MAX; ++iIndex)
    {
        if (s_aiGUI_Mouse[iIndex] == aiGUI_Mouse[iIndex])
        {
            continue;
        }

        while (0 == tgCM_UT_LF__LA_RB_SRSW__Query_Free_Size( &g_asController_Active[ETgCONTROLLER_GUI_MOUSE].m_sLA_RB_SRSW ))
        {
            tgTR_Yield();
        };

        uiEvent = (TgUINT_E32)tgCM_UT_LF__LA_RB_SRSW__Push_Next_Index( &g_asController_Active[ETgCONTROLLER_GUI_MOUSE].m_sLA_RB_SRSW );

        g_asController_Active[ETgCONTROLLER_GUI_MOUSE].m_asEvent[uiEvent].m_enController = ETgCONTROLLER_GUI_MOUSE;
        g_asController_Active[ETgCONTROLLER_GUI_MOUSE].m_asEvent[uiEvent].m_uiState.GUI_Mouse = 0;
        g_asController_Active[ETgCONTROLLER_GUI_MOUSE].m_asEvent[uiEvent].m_enProp.GUI_Mouse = (ETgPROP_GUI_MOUSE)iIndex;
        g_asController_Active[ETgCONTROLLER_GUI_MOUSE].m_asEvent[uiEvent].m_uiUTF32 = aiGUI_Mouse[iIndex];
        g_asController_Active[ETgCONTROLLER_GUI_MOUSE].m_asEvent[uiEvent].m_fValue = 0.0F;
        g_asController_Active[ETgCONTROLLER_GUI_MOUSE].m_asEvent[uiEvent].m_fDiff = 0.0F;

        tgCM_UT_LF__LA_RB_SRSW__Push_Commit( &g_asController_Active[ETgCONTROLLER_GUI_MOUSE].m_sLA_RB_SRSW );
    };

    tgMM_Copy( s_aiGUI_Mouse, sizeof( s_aiGUI_Mouse ), aiGUI_Mouse, sizeof( aiGUI_Mouse ) );
    return (0);
/*# !defined(TgBUILD_UNIVERSAL__UWP) */
#endif
}
