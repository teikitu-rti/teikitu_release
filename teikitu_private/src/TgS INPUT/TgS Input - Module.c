/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Input - Module.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "TgS COMMON/TgS Common - Util MT - Stack.inl"
#include "TgS COMMON/TgS Common - Util MT - LA Ring Buffer SRSW.inl"


/* == Input ====================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

static ETgMODULE_STATE                      s_enInput_State = ETgMODULE_STATE__FREED;

#if TgCOMPILE__THREAD
static TgUINT_E32                           tgIN_Update_Producers_Thread( TgUINT_PTR_C ) TgATTRIBUTE_NO_EXCEPT;

static TgBOOL                               s_bRun_Producer_Thread;
static TgBOOL                               s_bEnd_Producer_Thread;
static TgTHREAD_ID                          s_uiProducer_Thread;

/*# TgCOMPILE__THREAD */
#endif

#if TgS_STAT__INPUT
static TgCHAR_U8_CPC                        s_aszStat_Controller_Name[] = {
                                                u8"Game Pad 0",
                                                u8"Game Pad 1",
                                                u8"Game Pad 2",
                                                u8"Game Pad 3",
                                                u8"Keyboard",
                                                u8"GUI Keyboard",
                                                u8"Mouse",
                                                u8"GUI Mouse",
                                                u8"Net 0",
                                                u8"Net 1",
                                                u8"Net 2",
                                                u8"Net 3" };
#endif




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgIN_Module_Init --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgIN_Module_Init( TgVOID )
{
    TgUINT_E32                          uiIndex;

    /* Verify the state of the system */
    TgERROR( ETgMODULE_STATE__FREED == s_enInput_State );
    s_enInput_State = ETgMODULE_STATE__INITIALIZING;

    tgMM_Set_U08_0x00( g_asController_Active, sizeof( g_asController_Active ) );
    tgMM_Set_U08_0x00( g_asController_Rumble, sizeof( g_asController_Rumble ) );
    tgMM_Set_U08_0x00( g_abController_Paused, sizeof( g_abController_Paused ) );
    tgMM_Set_U08_0x00( g_asConsumer, sizeof( g_asConsumer ) );
    for (uiIndex = 0; uiIndex < TgARRAY_COUNT( g_asConsumer ); ++uiIndex)
    {
        g_asConsumer[uiIndex].m_enController = ETgCONTROLLER__MAX;
    };

    tgCM_UT_LF__ST__Init( &g_sConsumer_Insert );

    g_fDefault_Mouse_X_Dead_Zone = 0.0F;
    g_fDefault_Mouse_Y_Dead_Zone = 0.0F;
    g_fDefault_Mouse_Z_Dead_Zone = 0.0F;

    g_fDefault_GamePad_Stick_0_X_Dead_Zone = 0.0F;
    g_fDefault_GamePad_Stick_0_Y_Dead_Zone = 0.0F;
    g_fDefault_GamePad_Stick_1_X_Dead_Zone = 0.0F;
    g_fDefault_GamePad_Stick_1_Y_Dead_Zone = 0.0F;

#if TgS_STAT__INPUT
    tgMM_Set_U08_0x00( g_nuiStat_Insert, sizeof( g_nuiStat_Insert ) );
    tgMM_Set_U08_0x00( g_nuiStat_Remove, sizeof( g_nuiStat_Remove ) );
#endif

    tgIN_PM_Module_Init();

    s_enInput_State = ETgMODULE_STATE__INITIALIZED;
    return (KTgS_OK);
}


/* ---- tgIN_Module_Boot --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgIN_Module_Boot( TgVOID )
{
    /* Verify the state of the system */
    TgERROR( ETgMODULE_STATE__INITIALIZED == s_enInput_State );
    s_enInput_State = ETgMODULE_STATE__BOOTING;

    LOG_STD_MSG_USZ_FMTU64( KTgCN_CHANEL_INITIALIZE_MEMORY, u8"Static Memory Size", tgIN_Query_Fixed_Memory() )

    tgIN_PM_Module_Boot();

#if TgCOMPILE__THREAD
    s_bEnd_Producer_Thread = false;
    s_bRun_Producer_Thread = true;
    TgSTD_ATOMIC(thread_fence)( TgSTD_MEMORY_ORDER(seq_cst) );
    s_uiProducer_Thread = tgTR_Create( tgIN_Update_Producers_Thread, 0, 0, ETgTHREAD_PRIORITY__CRITICAL, u8"IN Producer" );
/*# TgCOMPILE__THREAD */
#endif

    s_enInput_State = ETgMODULE_STATE__BOOTED;
    return (KTgS_OK);
}


/* ---- tgIN_Module_Stop --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgIN_Module_Stop( TgVOID )
{
#if TgCOMPILE__THREAD
    ETgCONTROLLER                       enController;
#endif

    if ((ETgMODULE_STATE__FREED == s_enInput_State) || (ETgMODULE_STATE__INITIALIZED == s_enInput_State))
    {
        return;
    };

    /* Verify the state of the system */
    TgERROR( ETgMODULE_STATE__BOOTED == s_enInput_State );
    s_enInput_State = ETgMODULE_STATE__STOPPING;

    TgERROR_MSGF( tgCM_UT_LF__ST__Is_Empty( &g_sConsumer_Insert ), STD_MSG_PREFIX u8"Orphaned Consumer Insertion.\n", STD_MSG_POST );

#if TgCOMPILE__THREAD
    /* Stop the production thread */
    s_bRun_Producer_Thread = false;
    TgSTD_ATOMIC(thread_fence)( TgSTD_MEMORY_ORDER(seq_cst) );

    while (!s_bEnd_Producer_Thread)
    {
        for (enController = ETgCONTROLLER__BEGIN; enController < ETgCONTROLLER__MAX; enController = (ETgCONTROLLER)((TgSINT_E32)enController + 1))
        {
            while (0 != tgCM_UT_LF__LA_RB_SRSW__Query_Used_Size( &g_asController_Active[enController].m_sLA_RB_SRSW ))
            {
                tgCM_UT_LF__LA_RB_SRSW__Pop_Next_Index( &g_asController_Active[enController].m_sLA_RB_SRSW );
                tgCM_UT_LF__LA_RB_SRSW__Pop_Commit( &g_asController_Active[enController].m_sLA_RB_SRSW );
            };
        };
    };

    tgTR_Close( s_uiProducer_Thread );
    s_uiProducer_Thread = KTgTHREAD_ID__INVALID;
/*# TgCOMPILE__THREAD */
#endif

    tgIN_PM_Module_Stop();

    s_enInput_State = ETgMODULE_STATE__STOPPED;
}


/* ---- tgIN_Module_Free --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgIN_Module_Free( TgVOID )
{
    if (ETgMODULE_STATE__FREED == s_enInput_State)
    {
        return;
    };

    /* Verify the state of the system */
    TgERROR( ETgMODULE_STATE__STOPPED == s_enInput_State || ETgMODULE_STATE__INITIALIZED == s_enInput_State );
    s_enInput_State = ETgMODULE_STATE__FREEING;

    tgIN_PM_Module_Free();

    s_enInput_State = ETgMODULE_STATE__FREED;
}


/* ---- tgIN_Module_Update ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgIN_Module_Update( TgATTRIBUTE_UNUSED TgFLOAT32_C fDT )
{
    return (KTgS_OK);
}


/* ---- tgIN_Load_Config --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgIN_Load_Config( TgVOID )
{

}


/* ---- tgIN_Save_Config --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgIN_Save_Config( TgVOID )
{

}


/* ---- tgIN_Query_Init ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgIN_Query_Init( TgVOID )
{
    return (ETgMODULE_STATE__INITIALIZED <= s_enInput_State && s_enInput_State <= ETgMODULE_STATE__STOPPED);
}


/* ---- tgIN_Query_Boot ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgIN_Query_Boot( TgVOID )
{
    return (ETgMODULE_STATE__BOOTED == s_enInput_State);
}


/* ---- tgIN_Stats --------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if TgS_STAT__INPUT
TgVOID tgIN_Stats( TgATTRIBUTE_UNUSED STg2_Output_P psOUT )
{
    TgUINT_E32                          uiIndex;

    TgMSGF( 0, u8"\n%-16.16s(%-32.32s): %-48.48s % 14d\n", STD_MSG_POST, u8"Total Consumer Insert", g_nuiStat_Insert[ETgCONTROLLER__MAX] );

    for (uiIndex = 0; uiIndex < ETgCONTROLLER__MAX; ++uiIndex)
    {
        TgMSGF( 0xD, STD_MSG_PREFIX u8"   -%-44.44s % 14d\n", STD_MSG_POST, s_aszStat_Controller_Name[uiIndex], g_nuiStat_Insert[uiIndex] );
    };

    TgMSGF( 0x0, u8"\n%-16.16s(%-32.32s): %-48.48s % 14d\n", STD_MSG_POST, u8"Total Consumer Remove", g_nuiStat_Remove[ETgCONTROLLER__MAX] );

    for (uiIndex = 0; uiIndex < ETgCONTROLLER__MAX; ++uiIndex)
    {
        TgMSGF( 0xD, STD_MSG_PREFIX u8"   -%-44.44s % 14d\n", STD_MSG_POST, s_aszStat_Controller_Name[uiIndex], g_nuiStat_Remove[uiIndex] );
    };
}
/*# TgS_STAT__INPUT */
#endif




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgIN_Update_Producers_Thread ----------------------------------------------------------------------------------------------------------------------------------------------*/
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if TgCOMPILE__THREAD
static TgUINT_E32 tgIN_Update_Producers_Thread( TgATTRIBUTE_UNUSED TgUINT_PTR_C uiUnused ) TgATTRIBUTE_NO_EXCEPT
{
    s_bEnd_Producer_Thread = false;
    while (s_bRun_Producer_Thread)
    {
        tgTR_Sleep( 7500 ); /* Needs to be changed to an event call so that vblank can trigger */
        tgIN_Update_Producers();
    };
    s_bEnd_Producer_Thread = true;

    return (0);
}
/*# TgCOMPILE__THREAD */
#endif
