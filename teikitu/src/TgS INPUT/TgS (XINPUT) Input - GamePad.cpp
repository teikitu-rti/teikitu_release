/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (XInput) Input - GamePad.c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.12 | »GUID« 964CB1A6-814D-4E19-8E67-A83FCA98BF05 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "TgS COMMON/TgS (WIN) Common - Base - Include.h"

CLANG_WARN_DISABLE_PUSH(nonportable-system-include-path)
MSVC_PRAGMA(warning(push,0))
#include <windows.h>
#include <xinput.h>
MSVC_PRAGMA(warning(pop))
CLANG_WARN_DISABLE_POP(nonportable-system-include-path)


/* == Input ====================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

static struct STg2_IN_GamePad
{
    TgFLOAT32                                   m_afData[2][ETgPROP_GAMEPAD__MAX];
    TgUINT_F32                                  m_uiState;
    TgUINT_F32                                  m_uiBuffer;
    TgUINT_F32                                  m_uiPacket;
    TgBOOL                                      m_bValid;
    TgUINT_E08                                  m_uiPad[3];
}                                           s_asGamePad[KTgCONTROLLER_GAMEPAD_MAX];

TgFORCEINLINE TgFLOAT32                     tgIN_Convert_Thumbstick_Value( SHORT, TgFLOAT32_C );
static TgRESULT                             tgIN_PM_Rumble_GamePad( ETgCONTROLLER_C );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgIN_PM_Init_GamePad ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgIN_PM_Init_GamePad( TgVOID )
{
    tgMM_Set_U08_0x00( s_asGamePad, sizeof( s_asGamePad ) );

    return (KTgS_OK);
}


/* ---- tgIN_PM_Boot_GamePad ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgIN_PM_Boot_GamePad( TgVOID )
{
    g_asController_Active[ETgCONTROLLER_GAMEPAD_0].m_pfnProduce = tgIN_PM_Update_GamePad;
    g_asController_Active[ETgCONTROLLER_GAMEPAD_0].m_enController = ETgCONTROLLER_GAMEPAD_0;
    tgCM_UT_LF__LA_RB_SRSW__Init( &g_asController_Active[ETgCONTROLLER_GAMEPAD_0].m_sLA_RB_SRSW, KTgCONTROLLER_MAX_EVENT );
    g_asController_Active[ETgCONTROLLER_GAMEPAD_0].m_psConsumer = nullptr;
    g_asController_Rumble[ETgCONTROLLER_GAMEPAD_0].m_fLt = 0.0F;
    g_asController_Rumble[ETgCONTROLLER_GAMEPAD_0].m_fRt = 0.0F;
    g_asController_Rumble[ETgCONTROLLER_GAMEPAD_0].m_pfnRumble = tgIN_PM_Rumble_GamePad;

    g_asController_Active[ETgCONTROLLER_GAMEPAD_1].m_pfnProduce = tgIN_PM_Update_GamePad;
    g_asController_Active[ETgCONTROLLER_GAMEPAD_1].m_enController = ETgCONTROLLER_GAMEPAD_1;
    tgCM_UT_LF__LA_RB_SRSW__Init( &g_asController_Active[ETgCONTROLLER_GAMEPAD_1].m_sLA_RB_SRSW, KTgCONTROLLER_MAX_EVENT );
    g_asController_Active[ETgCONTROLLER_GAMEPAD_1].m_psConsumer = nullptr;
    g_asController_Rumble[ETgCONTROLLER_GAMEPAD_1].m_fLt = 0.0F;
    g_asController_Rumble[ETgCONTROLLER_GAMEPAD_1].m_fRt = 0.0F;
    g_asController_Rumble[ETgCONTROLLER_GAMEPAD_1].m_pfnRumble = tgIN_PM_Rumble_GamePad;

    g_asController_Active[ETgCONTROLLER_GAMEPAD_2].m_pfnProduce = tgIN_PM_Update_GamePad;
    g_asController_Active[ETgCONTROLLER_GAMEPAD_2].m_enController = ETgCONTROLLER_GAMEPAD_2;
    tgCM_UT_LF__LA_RB_SRSW__Init( &g_asController_Active[ETgCONTROLLER_GAMEPAD_2].m_sLA_RB_SRSW, KTgCONTROLLER_MAX_EVENT );
    g_asController_Active[ETgCONTROLLER_GAMEPAD_2].m_psConsumer = nullptr;
    g_asController_Rumble[ETgCONTROLLER_GAMEPAD_2].m_fLt = 0.0F;
    g_asController_Rumble[ETgCONTROLLER_GAMEPAD_2].m_fRt = 0.0F;
    g_asController_Rumble[ETgCONTROLLER_GAMEPAD_2].m_pfnRumble = tgIN_PM_Rumble_GamePad;

    g_asController_Active[ETgCONTROLLER_GAMEPAD_3].m_pfnProduce = tgIN_PM_Update_GamePad;
    g_asController_Active[ETgCONTROLLER_GAMEPAD_3].m_enController = ETgCONTROLLER_GAMEPAD_3;
    tgCM_UT_LF__LA_RB_SRSW__Init( &g_asController_Active[ETgCONTROLLER_GAMEPAD_3].m_sLA_RB_SRSW, KTgCONTROLLER_MAX_EVENT );
    g_asController_Active[ETgCONTROLLER_GAMEPAD_3].m_psConsumer = nullptr;
    g_asController_Rumble[ETgCONTROLLER_GAMEPAD_3].m_fLt = 0.0F;
    g_asController_Rumble[ETgCONTROLLER_GAMEPAD_3].m_fRt = 0.0F;
    g_asController_Rumble[ETgCONTROLLER_GAMEPAD_3].m_pfnRumble = tgIN_PM_Rumble_GamePad;

    return (KTgS_OK);
}


/* ---- tgIN_PM_Stop_GamePad ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgIN_PM_Stop_GamePad( TgVOID )
{
    g_asController_Rumble[ETgCONTROLLER_GAMEPAD_3].m_pfnRumble = nullptr;
    g_asController_Active[ETgCONTROLLER_GAMEPAD_3].m_pfnProduce = nullptr;
    g_asController_Active[ETgCONTROLLER_GAMEPAD_3].m_enController = ETgCONTROLLER_MAX;
    tgCM_UT_LF__LA_RB_SRSW__Init( &g_asController_Active[ETgCONTROLLER_GAMEPAD_3].m_sLA_RB_SRSW, KTgCONTROLLER_MAX_EVENT );
    g_asController_Active[ETgCONTROLLER_GAMEPAD_3].m_psConsumer = nullptr;

    g_asController_Rumble[ETgCONTROLLER_GAMEPAD_2].m_pfnRumble = nullptr;
    g_asController_Active[ETgCONTROLLER_GAMEPAD_2].m_pfnProduce = nullptr;
    g_asController_Active[ETgCONTROLLER_GAMEPAD_2].m_enController = ETgCONTROLLER_MAX;
    tgCM_UT_LF__LA_RB_SRSW__Init( &g_asController_Active[ETgCONTROLLER_GAMEPAD_2].m_sLA_RB_SRSW, KTgCONTROLLER_MAX_EVENT );
    g_asController_Active[ETgCONTROLLER_GAMEPAD_2].m_psConsumer = nullptr;

    g_asController_Rumble[ETgCONTROLLER_GAMEPAD_1].m_pfnRumble = nullptr;
    g_asController_Active[ETgCONTROLLER_GAMEPAD_1].m_pfnProduce = nullptr;
    g_asController_Active[ETgCONTROLLER_GAMEPAD_1].m_enController = ETgCONTROLLER_MAX;
    tgCM_UT_LF__LA_RB_SRSW__Init( &g_asController_Active[ETgCONTROLLER_GAMEPAD_1].m_sLA_RB_SRSW, KTgCONTROLLER_MAX_EVENT );
    g_asController_Active[ETgCONTROLLER_GAMEPAD_1].m_psConsumer = nullptr;

    g_asController_Rumble[ETgCONTROLLER_GAMEPAD_0].m_pfnRumble = nullptr;
    g_asController_Active[ETgCONTROLLER_GAMEPAD_0].m_pfnProduce = nullptr;
    g_asController_Active[ETgCONTROLLER_GAMEPAD_0].m_enController = ETgCONTROLLER_MAX;
    tgCM_UT_LF__LA_RB_SRSW__Init( &g_asController_Active[ETgCONTROLLER_GAMEPAD_0].m_sLA_RB_SRSW, KTgCONTROLLER_MAX_EVENT );
    g_asController_Active[ETgCONTROLLER_GAMEPAD_0].m_psConsumer = nullptr;

    return (KTgS_OK);
}


/* ---- tgIN_PM_Free_GamePad ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgIN_PM_Free_GamePad( TgVOID )
{
    return (KTgS_OK);
}


/* ---- tgIN_PM_Update_GamePad --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgIN_PM_Update_GamePad( ETgCONTROLLER_C enController )
{
    TgUINT_F32_C                        uiID = static_cast<TgUINT_F32>(enController - ETgCONTROLLER_GAMEPAD_0);
    TgUINT_F32_C                        uiNext = (s_asGamePad[uiID].m_uiBuffer & 1) ^ 1;
    TgUINT_F32_C                        uiPrev = (s_asGamePad[uiID].m_uiBuffer & 1);
    TgUINT_F32                          uiIndex;
    TgUINT_F32                          uiEvent;
    TgUINT_F32                          uiState = ETgSTATE_GAMEPAD_VALID;
    XINPUT_STATE                        xState;
    TgBOOL                              bValid;
    TgUINT_F32                          wButtons;

    TgERROR( uiID < KTgCONTROLLER_GAMEPAD_MAX );
    s_asGamePad[uiID].m_uiBuffer = uiNext; /* Advance the buffer id value (this is the device not the event buffer). */

    /* Check the state of the game pad - this determines if its connected to the machine. */
    bValid = 0L == g_pfnXInputGetState( uiID, &xState );

    if (bValid && bValid != s_asGamePad[uiID].m_bValid)
    {
        XINPUT_CAPABILITIES                 xInput;

        bValid &= (0L == g_pfnXInputGetCapabilities( uiID, XINPUT_FLAG_GAMEPAD, &xInput ));
        if (bValid)
        {
            tgMM_Set_U08_0x00( s_asGamePad[uiID].m_afData[uiPrev], sizeof( s_asGamePad[uiID].m_afData[0] ) );
            s_asGamePad[uiID].m_uiBuffer = 0;
            s_asGamePad[uiID].m_uiPacket = 0;
            g_fGamePad_Stick_Dead_Zone[uiID][0] = g_fDefault_GamePad_Stick_0_X_Dead_Zone;
            g_fGamePad_Stick_Dead_Zone[uiID][1] = g_fDefault_GamePad_Stick_1_X_Dead_Zone;
            g_fGamePad_Stick_Dead_Zone[uiID][2] = g_fDefault_GamePad_Stick_0_Y_Dead_Zone;
            g_fGamePad_Stick_Dead_Zone[uiID][3] = g_fDefault_GamePad_Stick_1_Y_Dead_Zone;
        };
    };

    if (bValid != s_asGamePad[uiID].m_bValid)
    {
        while (0 == tgCM_UT_LF__LA_RB_SRSW__Query_Free_Size( &g_asController_Active[enController].m_sLA_RB_SRSW ))
        {
            tgTR_Yield();
        };

        uiEvent = static_cast<TgUINT_F32>(tgCM_UT_LF__LA_RB_SRSW__Push_Next_Index( &g_asController_Active[enController].m_sLA_RB_SRSW ));

        g_asController_Active[enController].m_asEvent[uiEvent].m_enController = enController;
        g_asController_Active[enController].m_asEvent[uiEvent].m_uiState.GamePad = bValid ? ETgSTATE_GAMEPAD_VALID : 0u;
        g_asController_Active[enController].m_asEvent[uiEvent].m_enProp.GamePad = ETgPROP_GAMEPAD__MAX;
        g_asController_Active[enController].m_asEvent[uiEvent].m_uiUTF32 = 0;
        g_asController_Active[enController].m_asEvent[uiEvent].m_fValue = 0.0F;
        g_asController_Active[enController].m_asEvent[uiEvent].m_fDiff = 0.0F;

        tgCM_UT_LF__LA_RB_SRSW__Push_Commit( &g_asController_Active[enController].m_sLA_RB_SRSW );

        /* Set the new state of the game pad */
        s_asGamePad[uiID].m_bValid = bValid;
    };

    if (!bValid)// || s_asGamePad[uiID].m_uiPacket == xState.dwPacketNumber)
    {
        return;
    };

    wButtons = xState.Gamepad.wButtons;

    s_asGamePad[uiID].m_afData[uiNext][ETgPROP_GAMEPAD__A] = 0 != (wButtons & XINPUT_GAMEPAD_A) ? 1.0F : 0.0F;
    s_asGamePad[uiID].m_afData[uiNext][ETgPROP_GAMEPAD__B] = 0 != (wButtons & XINPUT_GAMEPAD_B) ? 1.0F : 0.0F;
    s_asGamePad[uiID].m_afData[uiNext][ETgPROP_GAMEPAD__X] = 0 != (wButtons & XINPUT_GAMEPAD_X) ? 1.0F : 0.0F;
    s_asGamePad[uiID].m_afData[uiNext][ETgPROP_GAMEPAD__Y] = 0 != (wButtons & XINPUT_GAMEPAD_Y) ? 1.0F : 0.0F;
    s_asGamePad[uiID].m_afData[uiNext][ETgPROP_GAMEPAD__DPAD_UP] = 0 != (wButtons & XINPUT_GAMEPAD_DPAD_UP) ? 1.0F : 0.0F;
    s_asGamePad[uiID].m_afData[uiNext][ETgPROP_GAMEPAD__DPAD_DOWN] = 0 != (wButtons & XINPUT_GAMEPAD_DPAD_DOWN) ? 1.0F : 0.0F;
    s_asGamePad[uiID].m_afData[uiNext][ETgPROP_GAMEPAD__DPAD_LEFT] = 0 != (wButtons & XINPUT_GAMEPAD_DPAD_LEFT) ? 1.0F : 0.0F;
    s_asGamePad[uiID].m_afData[uiNext][ETgPROP_GAMEPAD__DPAD_RIGHT] = 0 != (wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) ? 1.0F : 0.0F;
    s_asGamePad[uiID].m_afData[uiNext][ETgPROP_GAMEPAD__LSHOULDER] = 0 != (wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) ? 1.0F : 0.0F;
    s_asGamePad[uiID].m_afData[uiNext][ETgPROP_GAMEPAD__RSHOULDER] = 0 != (wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) ? 1.0F : 0.0F;
    s_asGamePad[uiID].m_afData[uiNext][ETgPROP_GAMEPAD__LTHUMB] = 0 != (wButtons & XINPUT_GAMEPAD_LEFT_THUMB) ? 1.0F : 0.0F;
    s_asGamePad[uiID].m_afData[uiNext][ETgPROP_GAMEPAD__RTHUMB] = 0 != (wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) ? 1.0F : 0.0F;
    s_asGamePad[uiID].m_afData[uiNext][ETgPROP_GAMEPAD__START] = 0 != (wButtons & XINPUT_GAMEPAD_START) ? 1.0F : 0.0F;
    s_asGamePad[uiID].m_afData[uiNext][ETgPROP_GAMEPAD__BACK] = 0 != (wButtons & XINPUT_GAMEPAD_BACK) ? 1.0F : 0.0F;

    s_asGamePad[uiID].m_afData[uiNext][ETgPROP_GAMEPAD__LTRIGGER] = static_cast<TgFLOAT32>(xState.Gamepad.bLeftTrigger) / static_cast<TgFLOAT32>(KTgMAX_U08);
    s_asGamePad[uiID].m_afData[uiNext][ETgPROP_GAMEPAD__RTRIGGER] = static_cast<TgFLOAT32>(xState.Gamepad.bRightTrigger) / static_cast<TgFLOAT32>(KTgMAX_U08);

    s_asGamePad[uiID].m_afData[uiNext][ETgPROP_GAMEPAD__LTHUMB_X] = tgIN_Convert_Thumbstick_Value( xState.Gamepad.sThumbLX, g_fGamePad_Stick_Dead_Zone[uiID][0] );
    s_asGamePad[uiID].m_afData[uiNext][ETgPROP_GAMEPAD__LTHUMB_Y] = tgIN_Convert_Thumbstick_Value( xState.Gamepad.sThumbLY, g_fGamePad_Stick_Dead_Zone[uiID][1] );
    s_asGamePad[uiID].m_afData[uiNext][ETgPROP_GAMEPAD__RTHUMB_X] = tgIN_Convert_Thumbstick_Value( xState.Gamepad.sThumbRX, g_fGamePad_Stick_Dead_Zone[uiID][2] );
    s_asGamePad[uiID].m_afData[uiNext][ETgPROP_GAMEPAD__RTHUMB_Y] = tgIN_Convert_Thumbstick_Value( xState.Gamepad.sThumbRY, g_fGamePad_Stick_Dead_Zone[uiID][3] );

    s_asGamePad[uiID].m_uiPacket = xState.dwPacketNumber;

    if (nullptr == g_asController_Active[enController].m_psConsumer)
    {
        return;
    };

    /* Generate events based on the change between this state and the previous state. */
    for (uiIndex = 0; uiIndex < ETgPROP_GAMEPAD__MAX; ++uiIndex)
    {
        if ((uiIndex <  ETgPROP_GAMEPAD__LTRIGGER) && tgCM_NR0_F32(s_asGamePad[uiID].m_afData[0][uiIndex] - s_asGamePad[uiID].m_afData[1][uiIndex]))
        {
            continue;
        };

        if ((uiIndex >= ETgPROP_GAMEPAD__LTRIGGER) && (s_asGamePad[uiID].m_afData[uiNext][uiIndex] == 0.0F))
        {
            continue;
        };

        while (0 == tgCM_UT_LF__LA_RB_SRSW__Query_Free_Size( &g_asController_Active[enController].m_sLA_RB_SRSW ))
        {
            tgTR_Yield();
        };

        uiEvent = static_cast<TgUINT_F32>(tgCM_UT_LF__LA_RB_SRSW__Push_Next_Index( &g_asController_Active[enController].m_sLA_RB_SRSW ));

        g_asController_Active[enController].m_asEvent[uiEvent].m_enController = enController;
        g_asController_Active[enController].m_asEvent[uiEvent].m_uiState.GamePad = uiState;
        g_asController_Active[enController].m_asEvent[uiEvent].m_enProp.GamePad = static_cast<ETgPROP_GAMEPAD>(uiIndex);
        g_asController_Active[enController].m_asEvent[uiEvent].m_uiUTF32 = 0;
        g_asController_Active[enController].m_asEvent[uiEvent].m_fValue = s_asGamePad[uiID].m_afData[uiNext][uiIndex];
        g_asController_Active[enController].m_asEvent[uiEvent].m_fDiff = s_asGamePad[uiID].m_afData[uiNext][uiIndex] - s_asGamePad[uiID].m_afData[uiPrev][uiIndex];

        tgCM_UT_LF__LA_RB_SRSW__Push_Commit( &g_asController_Active[enController].m_sLA_RB_SRSW );
    };
}


/* ---- tgIN_PM_Set_GamePad_Rumble ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgIN_PM_Set_GamePad_Rumble( ETgCONTROLLER_C enController, TgFLOAT32_C fLt, TgFLOAT32_C fRt )
{
    XINPUT_VIBRATION                    dxVibration;

    tgMM_Set_U08_0x00( &dxVibration, sizeof( XINPUT_VIBRATION ) );

    dxVibration.wLeftMotorSpeed = static_cast<WORD>(65535.0F*tgCM_MIN_F32( 1.0F, fLt ));
    dxVibration.wRightMotorSpeed = static_cast<WORD>(65535.0F*tgCM_MIN_F32( 1.0F, fRt ));

    g_pfnXInputSetState( static_cast<TgUINT_F32>(enController - ETgCONTROLLER_GAMEPAD_0), &dxVibration );

    return (KTgS_OK);
}


/* ---- tgIN_PM_Query_Fixed_Memory_GamePad --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRSIZE tgIN_PM_Query_Fixed_Memory_GamePad( TgVOID )
{
    return (0
        + sizeof( s_asGamePad )
    );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgIN_Convert_Thumbstick_Value -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgFORCEINLINE TgFLOAT32 tgIN_Convert_Thumbstick_Value( SHORT sThumbstickValue, TgFLOAT32_C fDeadZone )
{
    TgFLOAT32_C                         fValue = sThumbstickValue / static_cast<TgFLOAT32>(KTgMAX_S16);

    return (tgPM_FSEL_F32( fValue - fDeadZone, fValue, tgPM_FSEL_F32( -(fValue + fDeadZone), fValue, 0.0F ) ));
}


/* ---- tgIN_PM_Rumble_GamePad --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT tgIN_PM_Rumble_GamePad( ETgCONTROLLER_C enController )
{
    TgUINT_F32_C                        uiID = static_cast<TgUINT_F32>(enController - ETgCONTROLLER_GAMEPAD_0);
    XINPUT_VIBRATION                    xRumble;

    xRumble.wLeftMotorSpeed = static_cast<WORD>(g_asController_Rumble[enController].m_fLt * static_cast<TgFLOAT32>(KTgMAX_U16));
    xRumble.wRightMotorSpeed = static_cast<WORD>(g_asController_Rumble[enController].m_fRt * static_cast<TgFLOAT32>(KTgMAX_U16));

    g_pfnXInputSetState( uiID, &xRumble );
    return (KTgS_OK);
}
