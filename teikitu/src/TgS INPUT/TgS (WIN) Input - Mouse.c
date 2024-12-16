/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (WIN) Input - Mouse.c
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
/*  Internal Types                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgTYPE_STRUCT(TgIN_MOUSE_DATA,)
{
    TgSINT_F32                                  m_iX, m_iY, m_iZ;
    TgUINT_F08                                  m_uiButtons[8];
};




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Constants                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

static const GUID                           MS_GUID_XAxis = { 0xA36D02E0, 0xC9F3, 0x11CF, { 0xBF, 0xC7, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00 } };
static const GUID                           MS_GUID_YAxis = { 0xA36D02E1, 0xC9F3, 0x11CF, { 0xBF, 0xC7, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00 } };
static const GUID                           MS_GUID_ZAxis = { 0xA36D02E2, 0xC9F3, 0x11CF, { 0xBF, 0xC7, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00 } };

static DIOBJECTDATAFORMAT s_asMouse_Layout[] = {
    { &MS_GUID_XAxis, (TgUINT_F32)offsetof( TgIN_MOUSE_DATA, m_iX ), DIDFT_AXIS | DIDFT_ANYINSTANCE, 0, },
    { &MS_GUID_YAxis, (TgUINT_F32)offsetof( TgIN_MOUSE_DATA, m_iY ), DIDFT_AXIS | DIDFT_ANYINSTANCE, 0, },
    { &MS_GUID_ZAxis, (TgUINT_F32)offsetof( TgIN_MOUSE_DATA, m_iZ ), DIDFT_AXIS | DIDFT_ANYINSTANCE | 0x80000000, 0, },
    { 0, (TgUINT_F32)offsetof( TgIN_MOUSE_DATA, m_uiButtons[0] ), DIDFT_BUTTON | DIDFT_ANYINSTANCE, 0, },
    { 0, (TgUINT_F32)offsetof( TgIN_MOUSE_DATA, m_uiButtons[1] ), DIDFT_BUTTON | DIDFT_ANYINSTANCE, 0, },
    { 0, (TgUINT_F32)offsetof( TgIN_MOUSE_DATA, m_uiButtons[2] ), DIDFT_BUTTON | DIDFT_ANYINSTANCE | 0x80000000, 0, },
    { 0, (TgUINT_F32)offsetof( TgIN_MOUSE_DATA, m_uiButtons[3] ), DIDFT_BUTTON | DIDFT_ANYINSTANCE | 0x80000000, 0, },
    { 0, (TgUINT_F32)offsetof( TgIN_MOUSE_DATA, m_uiButtons[4] ), DIDFT_BUTTON | DIDFT_ANYINSTANCE | 0x80000000, 0, },
    { 0, (TgUINT_F32)offsetof( TgIN_MOUSE_DATA, m_uiButtons[5] ), DIDFT_BUTTON | DIDFT_ANYINSTANCE | 0x80000000, 0, },
    { 0, (TgUINT_F32)offsetof( TgIN_MOUSE_DATA, m_uiButtons[6] ), DIDFT_BUTTON | DIDFT_ANYINSTANCE | 0x80000000, 0, },
    { 0, (TgUINT_F32)offsetof( TgIN_MOUSE_DATA, m_uiButtons[7] ), DIDFT_BUTTON | DIDFT_ANYINSTANCE | 0x80000000, 0, },
};

static const DIDATAFORMAT s_sMouse_Format =
{
    sizeof(DIDATAFORMAT),                                   /* Size of this structure  */
    sizeof(DIOBJECTDATAFORMAT),                             /* Size of object data format  */
    DIDF_RELAXIS,                                           /* Relative axis coordinates  */
    sizeof(TgIN_MOUSE_DATA ),                               /* Size of device data  */
    sizeof(s_asMouse_Layout) / sizeof(s_asMouse_Layout[0]), /* Number of objects  */
    s_asMouse_Layout,                                       /* And here they are  */
};




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

static struct STg2_IN_Mouse
{
    TgFLOAT32                                   m_afData[2][ETgPROP_MOUSE_MAX];
    TgUINT_F32                                  m_uiState;
    TgUINT_F32                                  m_uiBuffer;
    TgBOOL                                      m_bValid;
    TgUINT_E08                                  m_uiPad[3];
}                                           s_asMouse[KTgCONTROLLER_MOUSE_MAX];
static LPDIRECTINPUTDEVICE8                 s_pdxMouse = nullptr;

TgFORCEINLINE TgFLOAT32                     tgIN_Convert_Movement_Value( TgSINT_F32 , TgFLOAT32_C );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgIN_PM_Init_Mouse ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgIN_PM_Init_Mouse( TgVOID )
{
    tgMM_Set_U08_0x00( s_asMouse, sizeof( s_asMouse ) );
    s_pdxMouse = nullptr;

    if (TgFAILED( g_pfnDIN8_CreateDevice( g_pdxDI, MS_REF GUID_SysMouse, &s_pdxMouse, nullptr ) ))
    {
        TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create mouse." );
        return (KTgE_FAIL);
    };

    if (TgFAILED( g_pfnDID8_SetDataFormat( s_pdxMouse, (LPCDIDATAFORMAT)&s_sMouse_Format ) ))
    {
        TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to setup mouse." );
        g_pfnDID8_Release( s_pdxMouse );
        s_pdxMouse = nullptr;
        return (KTgE_FAIL);
    };

    //if (TgFAILED( g_pfnDID8_SetCooperativeLevel( s_pdxMouse, g_hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE ) ))
    //{
    //    TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to setup mouse." );
    //    g_pfnDID8_Release( s_pdxMouse );
    //    s_pdxMouse = nullptr;
    //    return (KTgE_FAIL);
    //};

    return (KTgS_OK);
}


/* ---- tgIN_PM_Boot_Mouse ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgIN_PM_Boot_Mouse( TgVOID )
{
    if (TgFAILED( g_pfnDID8_Acquire( s_pdxMouse ) ))
    {
        TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to acquire mouse." );
        return (KTgE_FAIL);
    };

    g_asController_Active[ETgCONTROLLER_MOUSE].m_pfnProduce = tgIN_PM_Update_Mouse;
    g_asController_Active[ETgCONTROLLER_MOUSE].m_enController = ETgCONTROLLER_MOUSE;
    tgCM_UT_LF__LA_RB_SRSW__Init( &g_asController_Active[ETgCONTROLLER_MOUSE].m_sLA_RB_SRSW, KTgCONTROLLER_MAX_EVENT );
    g_asController_Active[ETgCONTROLLER_MOUSE].m_psConsumer = nullptr;

    return (KTgS_OK);
}


/* ---- tgIN_PM_Stop_Mouse ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgIN_PM_Stop_Mouse( TgVOID )
{
    g_asController_Active[ETgCONTROLLER_MOUSE].m_pfnProduce = nullptr;
    g_asController_Active[ETgCONTROLLER_MOUSE].m_enController = ETgCONTROLLER_MAX;
    tgCM_UT_LF__LA_RB_SRSW__Init( &g_asController_Active[ETgCONTROLLER_MOUSE].m_sLA_RB_SRSW, KTgCONTROLLER_MAX_EVENT );
    g_asController_Active[ETgCONTROLLER_MOUSE].m_psConsumer = nullptr;

    g_pfnDID8_Unacquire( s_pdxMouse );

    return (KTgS_OK);
}


/* ---- tgIN_PM_Free_Mouse ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgIN_PM_Free_Mouse( TgVOID )
{
    if (nullptr != s_pdxMouse)
    {
        g_pfnDID8_Release( s_pdxMouse );
        s_pdxMouse = nullptr;
    };
    return (KTgS_OK);
}


/* ---- tgIN_PM_Update_Mouse ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgIN_PM_Update_Mouse( ETgCONTROLLER_C enController )
{
    TgUINT_F32_C    uiID = (TgUINT_F32)(enController - ETgCONTROLLER_MOUSE);
    TgUINT_F32_C    uiNext = s_asMouse[uiID].m_uiBuffer ^ 1;
    TgUINT_F32_C    uiPrev = s_asMouse[uiID].m_uiBuffer;
    TgUINT_F32                          uiIndex;
    TgUINT_F32                          uiEvent;
    TgUINT_F32                          uiState = ETgSTATE_MOUSE_VALID;
    TgIN_MOUSE_DATA                     diState;

    tgMM_Set_U08_0x00( &diState, sizeof( diState ) );
    TgERROR( uiID < KTgCONTROLLER_MOUSE_MAX );
    s_asMouse[uiID].m_uiBuffer = uiNext; /* Advance the buffer id value (this is the device not the event buffer). */

    /* Read the mouse state */
    if (TgFAILED( g_pfnDID8_GetDeviceState( s_pdxMouse, sizeof( diState ), &diState ) ))
    {
        TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to get mouse data." );
        s_asMouse[uiID].m_bValid = false;

        if (TgFAILED( g_pfnDID8_Acquire( s_pdxMouse ) ))
        {
            TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to acquire mouse." );
        };
        return;
    };

    if (!s_asMouse[uiID].m_bValid)
    {
        tgMM_Set_U08_0x00( &(s_asMouse[uiID].m_afData[uiNext ^ 1]), sizeof( s_asMouse[uiID].m_afData[0] ) );

        s_asMouse[uiID].m_uiState = 0;
        s_asMouse[uiID].m_bValid = true;

        g_fMouse_Dead_Zone[uiID][0] = g_fDefault_Mouse_X_Dead_Zone;
        g_fMouse_Dead_Zone[uiID][1] = g_fDefault_Mouse_Y_Dead_Zone;
        g_fMouse_Dead_Zone[uiID][2] = g_fDefault_Mouse_Z_Dead_Zone;
    };

    s_asMouse[uiID].m_afData[uiNext][ETgPROP_MOUSE_BUTTON0] = 0 != diState.m_uiButtons[0] ? 1.0F : 0.0F;
    s_asMouse[uiID].m_afData[uiNext][ETgPROP_MOUSE_BUTTON1] = 0 != diState.m_uiButtons[1] ? 1.0F : 0.0F;
    s_asMouse[uiID].m_afData[uiNext][ETgPROP_MOUSE_BUTTON2] = 0 != diState.m_uiButtons[2] ? 1.0F : 0.0F;
    s_asMouse[uiID].m_afData[uiNext][ETgPROP_MOUSE_BUTTON3] = 0 != diState.m_uiButtons[3] ? 1.0F : 0.0F;
    s_asMouse[uiID].m_afData[uiNext][ETgPROP_MOUSE_BUTTON4] = 0 != diState.m_uiButtons[4] ? 1.0F : 0.0F;
    s_asMouse[uiID].m_afData[uiNext][ETgPROP_MOUSE_BUTTON5] = 0 != diState.m_uiButtons[5] ? 1.0F : 0.0F;
    s_asMouse[uiID].m_afData[uiNext][ETgPROP_MOUSE_BUTTON6] = 0 != diState.m_uiButtons[6] ? 1.0F : 0.0F;
    s_asMouse[uiID].m_afData[uiNext][ETgPROP_MOUSE_BUTTON7] = 0 != diState.m_uiButtons[7] ? 1.0F : 0.0F;
    s_asMouse[uiID].m_afData[uiNext][ETgPROP_MOUSE_AXIX_DX] = tgIN_Convert_Movement_Value( diState.m_iX, g_fMouse_Dead_Zone[uiID][0] );
    s_asMouse[uiID].m_afData[uiNext][ETgPROP_MOUSE_AXIX_DY] = tgIN_Convert_Movement_Value( diState.m_iY, g_fMouse_Dead_Zone[uiID][1] );
    s_asMouse[uiID].m_afData[uiNext][ETgPROP_MOUSE_AXIX_DZ] = tgIN_Convert_Movement_Value( diState.m_iZ, g_fMouse_Dead_Zone[uiID][2] );

    if (nullptr == g_asController_Active[enController].m_psConsumer)
    {
        return;
    };

    /* Generate events based on the change between this state and the previous state. */
    for (uiIndex = 0; uiIndex < ETgPROP_MOUSE_MAX; ++uiIndex)
    {
        if (
            ((uiIndex < ETgPROP_MOUSE_AXIX_DX) && tgCM_NR0_F32(s_asMouse[uiID].m_afData[0][uiIndex] - s_asMouse[uiID].m_afData[1][uiIndex])) ||
            ((uiIndex >= ETgPROP_MOUSE_AXIX_DX) && (!(s_asMouse[uiID].m_afData[uiNext][uiIndex] > 0.0F)))
            )
        {
            continue;
        };

        while (0 == tgCM_UT_LF__LA_RB_SRSW__Query_Free_Size( &g_asController_Active[enController].m_sLA_RB_SRSW ))
        {
            tgTR_Yield();
        };

        uiEvent = (TgUINT_F32)tgCM_UT_LF__LA_RB_SRSW__Push_Next_Index( &g_asController_Active[enController].m_sLA_RB_SRSW );

        g_asController_Active[enController].m_asEvent[uiEvent].m_enController = enController;
        g_asController_Active[enController].m_asEvent[uiEvent].m_uiState.Mouse = uiState;
        g_asController_Active[enController].m_asEvent[uiEvent].m_enProp.Mouse = (ETgPROP_MOUSE)uiIndex;
        g_asController_Active[enController].m_asEvent[uiEvent].m_uiUTF32 = 0;
        g_asController_Active[enController].m_asEvent[uiEvent].m_fValue =
            s_asMouse[uiID].m_afData[uiNext][uiIndex];
        g_asController_Active[enController].m_asEvent[uiEvent].m_fDiff =
            s_asMouse[uiID].m_afData[uiNext][uiIndex] - s_asMouse[uiID].m_afData[uiPrev][uiIndex];

        tgCM_UT_LF__LA_RB_SRSW__Push_Commit( &g_asController_Active[enController].m_sLA_RB_SRSW );
    };
}


/* ---- tgIN_PM_Query_Fixed_Memory_Mouse ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRSIZE tgIN_PM_Query_Fixed_Memory_Mouse( TgVOID )
{
    return (0
        + sizeof( MS_GUID_XAxis )
        + sizeof( MS_GUID_YAxis )
        + sizeof( MS_GUID_ZAxis )
        + sizeof( s_asMouse_Layout )
        + sizeof( s_sMouse_Format )
        + sizeof( s_asMouse )
        + sizeof( s_pdxMouse )
        );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgIN_Convert_Movement_Value ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgFORCEINLINE TgFLOAT32 tgIN_Convert_Movement_Value( TgSINT_F32 sValue, TgFLOAT32_C fDeadZone )
{
    TgFLOAT32_C fValue = (TgFLOAT32)sValue / (TgFLOAT32)KTgMAX_S16;
    return (tgPM_FSEL_F32( fValue - fDeadZone, fValue, tgPM_FSEL_F32( -(fValue + fDeadZone), fValue, 0.0F ) ));
}
