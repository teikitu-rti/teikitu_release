/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Input - System.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "TgS COMMON/TgS Common - Util MT - Stack.inl"


/* == Input ====================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgIN_Has_Producer -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgIN_Has_Producer( ETgCONTROLLER_C enController )
{
    ETgCONTROLLER                       enIndex;

    for (enIndex = 0; enIndex < ETgCONTROLLER_MAX; ++enIndex)
    {
        if (0 != g_asController_Active[enIndex].m_pfnProduce && enController == g_asController_Active[enIndex].m_enController)
        {
            return (true);
        };
    };

    return (false);
}


/* ---- tgIN_Update_Producers ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/*  This function is a wrapper by platform specific implementations to enforce a real time guaranteed execution. */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgIN_Update_Producers( TgVOID )
{
    ETgCONTROLLER                       enIndex;

    for (enIndex = 0; enIndex < ETgCONTROLLER_MAX; ++enIndex)
    {
        if (0 != g_asController_Active[enIndex].m_pfnProduce)
        {
            g_asController_Active[enIndex].m_pfnProduce( enIndex );
        };
    };
}


/* ---- tgIN_Insert_Consumer ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgIN_CONSUMER_ID tgIN_Insert_Consumer( ETgCONTROLLER_C enController, TgUINT_F32_C uiPriority, TgIN_FCN_CONSUMER pfnConsume, TgUINT_PTR_C uiParam )
{
    STg2_Input_Consumer_PU              psNew_Consumer;
    TgIN_CONSUMER_ID_SINGLETON          tiDesired_Singleton;
    TgIN_CONSUMER_ID                    tiDesired;

    if (enController >= ETgCONTROLLER_MAX)
    {
        TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unknown Input Controller as Parameter" );
        return (KTgIN_CONSUMER_ID__INVALID);
    };

    if (nullptr == pfnConsume)
    {
        TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Consume function is null" );
        return (KTgIN_CONSUMER_ID__INVALID);
    };

    tgIN_CONSUMER_ID_Init( &tiDesired_Singleton, KTgMAX_CONSUMER );
    tiDesired = tgIN_CONSUMER_ID_Query_Unsafe( &tiDesired_Singleton );
    psNew_Consumer = nullptr;

    for (TgUINT_F32 uiIndex = 0; uiIndex < KTgMAX_CONSUMER; ++uiIndex)
    {
        TgIN_CONSUMER_ID                    tiExpected;

        tiExpected.m_uiKI = KTgID__INVALID_VALUE;

        if (atomic_compare_exchange_strong( &g_asConsumer[uiIndex].m_tiConsumer_Singleton.m_uiKI, &tiExpected.m_uiKI, tiDesired.m_uiKI ))
        {
            tgMM_Set_U08_0x00( &g_asConsumer[uiIndex].m_sMP_Element, sizeof( g_asConsumer[uiIndex].m_sMP_Element ) );
            tgIN_CONSUMER_ID_Init( &g_asConsumer[uiIndex].m_tiConsumer_Singleton, uiIndex );
            psNew_Consumer = g_asConsumer + uiIndex;
            break;
        };
    };

    if (nullptr == psNew_Consumer)
    {
    #if TgS_DEBUG__INPUT
        TgWARNING_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Exceed total number of alloweable input consumers." );
    #endif
        return (KTgIN_CONSUMER_ID__INVALID);
    };

    psNew_Consumer->m_pfnConsume = pfnConsume;
    psNew_Consumer->m_enController = enController;
    psNew_Consumer->m_uiParam = uiParam;
    psNew_Consumer->m_uiPriority = uiPriority;
    psNew_Consumer->m_bRemove = false;

    tgCM_UT_LF__ST__Push( &g_sConsumer_Insert, &psNew_Consumer->m_sMP_Element );

    return (tgIN_CONSUMER_ID_Query_Unsafe( &psNew_Consumer->m_tiConsumer_Singleton ));
}


/* ---- tgIN_Remove_Consumer ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgIN_Remove_Consumer( TgIN_CONSUMER_ID_C tiConsumer )
{
#if TgS_DEBUG__INPUT
    if (!tgIN_CONSUMER_ID_Is_Equal( &g_asConsumer[tiConsumer.m_uiI].m_tiConsumer_Singleton, tiConsumer ))
    {
        TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Invalid or stale ID." );
    };
#endif

    g_asConsumer[tiConsumer.m_uiI].m_bRemove = true;

    return (KTgS_OK);
}


/* ---- tgIN_Pause_Controller ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgIN_Pause_Controller( ETgCONTROLLER_C enInput, TgBOOL_C bPause )
{
    if (enInput < ETgCONTROLLER_MAX)
    {
        g_abController_Paused[enInput] = bPause;
        return (true);
    };

    TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unknown Input Controller as Parameter" );
    return (false);
}


/* ---- tgIN_Pause_Input --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgIN_Pause_Input( TgBOOL_C bPause )
{
    TgUINT_F32                          uiIndex = 0;

    for (; uiIndex < ETgCONTROLLER_MAX; ++uiIndex)
    {
        TgVERIFY( tgIN_Pause_Controller( (ETgCONTROLLER)uiIndex, bPause ) );
    };
}


/* ---- tgIN_Set_Default_Dead_Zone ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgIN_Set_Default_Dead_Zone( ETgDEAD_ZONE_C enZone, TgFLOAT32_C fValue )
{
    switch (enZone)
    {
        case ETgDEAD_ZONE_MOUSE_X:
            g_fDefault_Mouse_X_Dead_Zone = fValue; break;
        case ETgDEAD_ZONE_MOUSE_Y:
            g_fDefault_Mouse_Y_Dead_Zone = fValue; break;
        case ETgDEAD_ZONE_MOUSE_Z:
            g_fDefault_Mouse_Z_Dead_Zone = fValue; break;

        case ETgDEAD_ZONE_STICK_0_X:
            g_fDefault_GamePad_Stick_0_X_Dead_Zone = fValue; break;
        case ETgDEAD_ZONE_STICK_0_Y:
            g_fDefault_GamePad_Stick_0_Y_Dead_Zone = fValue; break;
        case ETgDEAD_ZONE_STICK_1_X:
            g_fDefault_GamePad_Stick_1_X_Dead_Zone = fValue; break;
        case ETgDEAD_ZONE_STICK_1_Y:
            g_fDefault_GamePad_Stick_1_Y_Dead_Zone = fValue; break;
        
        case ETgDEAD_ZONE_MAX:
            break;

        default:
            TgS_NO_DEFAULT(break);
    };
}


/* ---- tgIN_Set_Dead_Zone ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgIN_Set_Dead_Zone( ETgCONTROLLER_C enController, ETgDEAD_ZONE_C enZone, TgFLOAT32_C fValue )
{
    switch (enController)
    {
        case ETgCONTROLLER_GAMEPAD_0:
        SWITCH_FALLTHROUGH case ETgCONTROLLER_GAMEPAD_1:
        SWITCH_FALLTHROUGH case ETgCONTROLLER_GAMEPAD_2:
        SWITCH_FALLTHROUGH case ETgCONTROLLER_GAMEPAD_3:
            TgPARAM_CHECK( enZone >= ETgDEAD_ZONE_STICK_0_X );
            g_fGamePad_Stick_Dead_Zone[enController - ETgCONTROLLER_GAMEPAD_0][enZone - ETgDEAD_ZONE_STICK_0_X] = fValue; break;

        case ETgCONTROLLER_GUI_MOUSE:
        SWITCH_FALLTHROUGH case ETgCONTROLLER_MOUSE:
            if (enZone >= ETgDEAD_ZONE_MOUSE_X && enZone < ETgDEAD_ZONE_STICK_0_X)
            {
                g_fMouse_Dead_Zone[enController - ETgCONTROLLER_MOUSE][enZone - ETgDEAD_ZONE_MOUSE_X] = fValue;
            };
            break;

        case ETgCONTROLLER_KEYBOARD:
        SWITCH_FALLTHROUGH case ETgCONTROLLER_GUI_KEYBOARD:
        SWITCH_FALLTHROUGH case ETgCONTROLLER_NET_0:
        SWITCH_FALLTHROUGH case ETgCONTROLLER_NET_1:
        SWITCH_FALLTHROUGH case ETgCONTROLLER_NET_2:
        SWITCH_FALLTHROUGH case ETgCONTROLLER_NET_3:
        SWITCH_FALLTHROUGH case ETgCONTROLLER_MAX:
            break;

        default:
            TgS_NO_DEFAULT(break);
    };
}


/* ---- tgIN_Query_Default_Dead_Zone --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgFLOAT32 tgIN_Query_Default_Dead_Zone( ETgDEAD_ZONE_C enZone )
{
    switch (enZone)
    {
        case ETgDEAD_ZONE_MOUSE_X:
            return (g_fDefault_Mouse_X_Dead_Zone);
        case ETgDEAD_ZONE_MOUSE_Y:
            return (g_fDefault_Mouse_Y_Dead_Zone);
        case ETgDEAD_ZONE_MOUSE_Z:
            return (g_fDefault_Mouse_Z_Dead_Zone);

        case ETgDEAD_ZONE_STICK_0_X:
            return (g_fDefault_GamePad_Stick_0_X_Dead_Zone);
        case ETgDEAD_ZONE_STICK_0_Y:
            return (g_fDefault_GamePad_Stick_0_Y_Dead_Zone);
        case ETgDEAD_ZONE_STICK_1_X:
            return (g_fDefault_GamePad_Stick_1_X_Dead_Zone);
        case ETgDEAD_ZONE_STICK_1_Y:
            return (g_fDefault_GamePad_Stick_1_Y_Dead_Zone);

        case ETgDEAD_ZONE_MAX:
            return (0.0F);

        default:
            TgS_NO_DEFAULT( return (0.0F) );
    };
}


/* ---- tgIN_Query_Dead_Zone ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgFLOAT32 tgIN_Query_Dead_Zone( ETgCONTROLLER_C enController, ETgDEAD_ZONE_C enZone )
{
    switch (enController)
    {
        case ETgCONTROLLER_GAMEPAD_0:
        SWITCH_FALLTHROUGH case ETgCONTROLLER_GAMEPAD_1:
        SWITCH_FALLTHROUGH case ETgCONTROLLER_GAMEPAD_2:
        SWITCH_FALLTHROUGH case ETgCONTROLLER_GAMEPAD_3:
            TgPARAM_CHECK( enZone >= ETgDEAD_ZONE_STICK_0_X );
            return (g_fGamePad_Stick_Dead_Zone[enController - ETgCONTROLLER_GAMEPAD_0][enZone - ETgDEAD_ZONE_STICK_0_X]);

        case ETgCONTROLLER_GUI_MOUSE:
        SWITCH_FALLTHROUGH case ETgCONTROLLER_MOUSE:
            if (enZone >= ETgDEAD_ZONE_MOUSE_X && enZone < ETgDEAD_ZONE_STICK_0_X)
            {
                return (g_fMouse_Dead_Zone[enController - ETgCONTROLLER_MOUSE][enZone - ETgDEAD_ZONE_MOUSE_X]);
            };

        SWITCH_FALLTHROUGH case ETgCONTROLLER_KEYBOARD:
        SWITCH_FALLTHROUGH case ETgCONTROLLER_GUI_KEYBOARD:
        SWITCH_FALLTHROUGH case ETgCONTROLLER_NET_0:
        SWITCH_FALLTHROUGH case ETgCONTROLLER_NET_1:
        SWITCH_FALLTHROUGH case ETgCONTROLLER_NET_2:
        SWITCH_FALLTHROUGH case ETgCONTROLLER_NET_3:
        SWITCH_FALLTHROUGH case ETgCONTROLLER_MAX:
            return (0.0F);

        default:
            TgS_NO_DEFAULT( return (0.0F) );
    };
}


/* ---- tgIN_Set_Rumble ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgIN_Set_Rumble( ETgCONTROLLER_C enController, TgFLOAT32_C fLt, TgFLOAT32_C fRt )
{
    if (nullptr == g_asController_Rumble[enController].m_pfnRumble)
    {
        return (KTgE_FAIL);
    };

    g_asController_Rumble[enController].m_fLt = fLt;
    g_asController_Rumble[enController].m_fRt = fRt;

    return (g_asController_Rumble[enController].m_pfnRumble( enController ));
}


/* ---- tgIN_Stat_Query_Total_Insert --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if TgS_STAT__INPUT
TgUINT_F32 tgIN_Stat_Query_Total_Insert( TgVOID )
{
    return (g_nuiStat_Insert[ETgCONTROLLER_MAX]);
}
#endif


/* ---- tgIN_Stat_Query_Total_Remove --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if TgS_STAT__INPUT
TgUINT_F32 tgIN_Stat_Query_Total_Remove( TgVOID )
{
    return (g_nuiStat_Remove[ETgCONTROLLER_MAX]);
}
#endif
