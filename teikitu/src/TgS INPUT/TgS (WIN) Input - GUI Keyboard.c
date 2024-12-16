/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (WIN) Input - GUI Keyboard.c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.12 | »GUID« 964CB1A6-814D-4E19-8E67-A83FCA98BF05 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "TgS COMMON/TgS Common - Util MT - LA Ring Buffer SRSW.inl"
#include "TgS COMMON/TgS Common - Base - API [Math].inl"


/* == Input ====================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

static TgNOTHROW TgSINT_PTR __stdcall
tgIN_PM_Update_GUI_Keyboard_Callback(
    HWND, TgUINT_F32 , TgUINT_PTR, TgSINT_PTR );

static TgUINT_F32
tgIN_PM_Query_Code_Page( TgVOID );

static TgUINT_F32                           s_uiInput_Code_Page = 0;




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgIN_PM_Init_GUI_Keyboard ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgIN_PM_Init_GUI_Keyboard( TgVOID )
{
    return (KTgS_OK);
}


/* ---- tgIN_PM_Boot_GUI_Keyboard ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgIN_PM_Boot_GUI_Keyboard( TgVOID )
{
    tgKN_OS_Set_GUI_Keyboard_Callback( tgIN_PM_Update_GUI_Keyboard_Callback );
    tgCM_UT_LF__LA_RB_SRSW__Init( &g_asController_Active[ETgCONTROLLER_GUI_KEYBOARD].m_sLA_RB_SRSW, KTgCONTROLLER_MAX_EVENT );
    return (KTgS_OK);
}


/* ---- tgIN_PM_Stop_GUI_Keyboard ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgIN_PM_Stop_GUI_Keyboard( TgVOID )
{
    tgKN_OS_Set_GUI_Keyboard_Callback( nullptr );
    return (KTgS_OK);
}


/* ---- tgIN_PM_Free_GUI_Keyboard ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgIN_PM_Free_GUI_Keyboard( TgVOID )
{
    return (KTgS_OK);
}


/* ---- tgIN_PM_Update_GUI_Keyboard ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgIN_PM_Update_GUI_Keyboard( ETgCONTROLLER_C UNUSED_PARAM enController )
{
}


/* ---- tgIN_PM_Query_Fixed_Memory_GUI_Keyboard ---------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRSIZE tgIN_PM_Query_Fixed_Memory_GUI_Keyboard( TgVOID )
{
    return (0
    );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgIN_PM_Query_Code_Page -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgUINT_F32 tgIN_PM_Query_Code_Page( TgVOID )
{
#if !defined(TgBUILD_UNIVERSAL__UWP)
    return (g_pfnGetACP());
#else
    return (0);
#endif
}


/* ---- tgIN_PM_Update_GUI_Keyboard_Callback ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgNOTHROW TgSINT_PTR __stdcall tgIN_PM_Update_GUI_Keyboard_Callback( HWND UNUSED_PARAM hWnd, TgUINT_F32 uiMsg, TgUINT_PTR wParam, TgSINT_PTR UNUSED_PARAM lParam )
{
    static TgBOOL                       bIsInit = false;
    TgUINT_F32                          uiState;
    TgUINT_F32                          uiEvent;

    if ((!bIsInit) || 0 == s_uiInput_Code_Page)
    {
        s_uiInput_Code_Page = tgIN_PM_Query_Code_Page();
        bIsInit = true;
    };

    uiState = ETgSTATE_KEYBOARD_VALID;

    switch (uiMsg)
    {
        case WM_INPUTLANGCHANGE:
            s_uiInput_Code_Page = tgIN_PM_Query_Code_Page();
            break;

        case WM_UNICHAR:
            break;

        case WM_IME_CHAR:
            break;

        case WM_CHAR:
            break;

        case WM_SYSKEYDOWN:
        case WM_KEYDOWN:
        case WM_IME_KEYDOWN:
            break;

        case WM_SYSKEYUP:
        case WM_KEYUP:
        case WM_IME_KEYUP:
            break;
    };

    while (0 == tgCM_UT_LF__LA_RB_SRSW__Query_Free_Size( &g_asController_Active[ETgCONTROLLER_GUI_KEYBOARD].m_sLA_RB_SRSW ))
    {
        tgTR_Yield();
    };

    uiEvent = (TgUINT_F32)tgCM_UT_LF__LA_RB_SRSW__Push_Next_Index( &g_asController_Active[ETgCONTROLLER_GUI_KEYBOARD].m_sLA_RB_SRSW );

    g_asController_Active[ETgCONTROLLER_GUI_KEYBOARD].m_asEvent[uiEvent].m_enController = ETgCONTROLLER_GUI_KEYBOARD;
    g_asController_Active[ETgCONTROLLER_GUI_KEYBOARD].m_asEvent[uiEvent].m_uiState.GUI_Keyboard = uiState;
    g_asController_Active[ETgCONTROLLER_GUI_KEYBOARD].m_asEvent[uiEvent].m_enProp.GUI_Keyboard = ETgPROP_GUI_KEY_MAX;
    g_asController_Active[ETgCONTROLLER_GUI_KEYBOARD].m_asEvent[uiEvent].m_uiUTF32 = (TgUINT_F32)wParam;
    g_asController_Active[ETgCONTROLLER_GUI_KEYBOARD].m_asEvent[uiEvent].m_fValue = 0.0F;
    g_asController_Active[ETgCONTROLLER_GUI_KEYBOARD].m_asEvent[uiEvent].m_fDiff = 0.0F;

    tgCM_UT_LF__LA_RB_SRSW__Push_Commit( &g_asController_Active[ETgCONTROLLER_GUI_KEYBOARD].m_sLA_RB_SRSW );
    return (0);
}
