/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Input [Unit Test] - GamePad.c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   4.51 | »GUID« A9981407-3EC9-42AF-8B6F-8BE6DD919615                                                                                                                 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Input ====================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

static TgBOOL                               TEST__Consumer_GamePad( TgUINT_PTR_C, TgFLOAT32_C, STg2_IN_Event_CPC );

static TgRSIZE_A                            s_xuiTest_Count;




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Unit Test Functions                                                                                                                                                            */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- TEST_METHOD(TEST__Input_GamePad) ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE(TEST__Input_GamePad)
{
    TgIN_CONSUMER_ID                    tiConsumer_Id;

    if (!tgIN_Has_Producer( ETgCONTROLLER_GAMEPAD_0 ))
    {
        return (KTgS_OK);
    };

    tiConsumer_Id = tgIN_Insert_Consumer( ETgCONTROLLER_GAMEPAD_0, 0, TEST__Consumer_GamePad, 0 );
    TgMSGF(0xC, u8"%-16.16s(%-32.32s)\n", u8"Input Test", u8"Game Pad Start");

    TgSTD_ATOMIC(store)( &s_xuiTest_Count, 0 );
    while (TgSTD_ATOMIC(load)( &s_xuiTest_Count ) < 64)
    {
        tgIN_Set_Rumble( ETgCONTROLLER_GAMEPAD_0, tgCM_RAND_F32(), tgCM_RAND_F32() );
        tgIN_Module_Update( 0.1F );
        Unit_Test__Sleep( 30000000 );
    };

    tgIN_Remove_Consumer( tiConsumer_Id );
    tgIN_Module_Update( 0.1F );

    return (KTgS_OK);
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- TEST__Consumer_GamePad --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgBOOL TEST__Consumer_GamePad( TgATTRIBUTE_UNUSED TgUINT_PTR_C uiUnused, TgATTRIBUTE_UNUSED TgFLOAT32_C fDT, STg2_IN_Event_CPC psEvent )
{
    switch (psEvent->m_enProp.GamePad)
    {
        case ETgPROP_GAMEPAD__A:
            TgMSGF(0xC, u8"%-16.16s(%-32.32s): %f %f\n", u8"Input Test", "GamePad A", (TgFLOAT64)psEvent->m_fValue, (TgFLOAT64)psEvent->m_fDiff );
            break;
        case ETgPROP_GAMEPAD__B:
            TgMSGF(0xC, u8"%-16.16s(%-32.32s): %f %f\n", u8"Input Test", u8"GamePad B", (TgFLOAT64)psEvent->m_fValue, (TgFLOAT64)psEvent->m_fDiff );
            break;
        case ETgPROP_GAMEPAD__X:
            TgMSGF(0xC, u8"%-16.16s(%-32.32s): %f %f\n", u8"Input Test", u8"GamePad X", (TgFLOAT64)psEvent->m_fValue, (TgFLOAT64)psEvent->m_fDiff );
            break;
        case ETgPROP_GAMEPAD__Y:
            TgMSGF(0xC, u8"%-16.16s(%-32.32s): %f %f\n", u8"Input Test", u8"GamePad Y", (TgFLOAT64)psEvent->m_fValue, (TgFLOAT64)psEvent->m_fDiff );
            break;
        case ETgPROP_GAMEPAD__DPAD_UP:
            TgMSGF(0xC, u8"%-16.16s(%-32.32s): %f %f\n", u8"Input Test", u8"GamePad DPad Up", (TgFLOAT64)psEvent->m_fValue, (TgFLOAT64)psEvent->m_fDiff );
            break;
        case ETgPROP_GAMEPAD__DPAD_DOWN:
            TgMSGF(0xC, u8"%-16.16s(%-32.32s): %f %f\n", u8"Input Test", u8"GamePad DPad Down", (TgFLOAT64)psEvent->m_fValue, (TgFLOAT64)psEvent->m_fDiff );
            break;
        case ETgPROP_GAMEPAD__DPAD_LEFT:
            TgMSGF(0xC, u8"%-16.16s(%-32.32s): %f %f\n", u8"Input Test", u8"GamePad DPad Left", (TgFLOAT64)psEvent->m_fValue, (TgFLOAT64)psEvent->m_fDiff );
            break;
        case ETgPROP_GAMEPAD__DPAD_RIGHT: 
            TgMSGF(0xC, u8"%-16.16s(%-32.32s): %f %f\n", u8"Input Test", u8"GamePad DPad Right", (TgFLOAT64)psEvent->m_fValue, (TgFLOAT64)psEvent->m_fDiff );
            break;
        case ETgPROP_GAMEPAD__LSHOULDER: 
            TgMSGF(0xC, u8"%-16.16s(%-32.32s): %f %f\n", u8"Input Test", u8"GamePad Left Shoulder", (TgFLOAT64)psEvent->m_fValue, (TgFLOAT64)psEvent->m_fDiff );
            break;
        case ETgPROP_GAMEPAD__RSHOULDER:
            TgMSGF(0xC, u8"%-16.16s(%-32.32s): %f %f\n", u8"Input Test", u8"GamePad Right Shoulder", (TgFLOAT64)psEvent->m_fValue, (TgFLOAT64)psEvent->m_fDiff );
            break;
        case ETgPROP_GAMEPAD__LTHUMB:
            TgMSGF(0xC, u8"%-16.16s(%-32.32s): %f %f\n", u8"Input Test", u8"GamePad Left Thumb", (TgFLOAT64)psEvent->m_fValue, ( TgFLOAT64 )psEvent->m_fDiff );
            break;
        case ETgPROP_GAMEPAD__RTHUMB:
            TgMSGF(0xC, u8"%-16.16s(%-32.32s): %f %f\n", u8"Input Test", u8"GamePad Right Thumb", (TgFLOAT64)psEvent->m_fValue, (TgFLOAT64)psEvent->m_fDiff );
            break;
        case ETgPROP_GAMEPAD__START:
            TgMSGF(0xC, u8"%-16.16s(%-32.32s): %f %f\n", u8"Input Test", u8"GamePad Start", (TgFLOAT64)psEvent->m_fValue, (TgFLOAT64)psEvent->m_fDiff );
            break;
        case ETgPROP_GAMEPAD__BACK:
            TgMSGF(0xC, u8"%-16.16s(%-32.32s): %f %f\n", u8"Input Test", u8"GamePad Back", (TgFLOAT64)psEvent->m_fValue, (TgFLOAT64)psEvent->m_fDiff );
            break;
        case ETgPROP_GAMEPAD__LTRIGGER:
            TgMSGF(0xC, u8"%-16.16s(%-32.32s): %f %f\n", u8"Input Test", u8"GamePad Left Trigger", (TgFLOAT64)psEvent->m_fValue, (TgFLOAT64)psEvent->m_fDiff );
            break;
        case ETgPROP_GAMEPAD__RTRIGGER:
            TgMSGF(0xC, u8"%-16.16s(%-32.32s): %f %f\n", u8"Input Test", u8"GamePad Right Trigger", (TgFLOAT64)psEvent->m_fValue, (TgFLOAT64)psEvent->m_fDiff );
            break;
        case ETgPROP_GAMEPAD__LTHUMB_X:
            TgMSGF(0xC, u8"%-16.16s(%-32.32s): %f %f\n", u8"Input Test", u8"GamePad Left Thumb X", (TgFLOAT64)psEvent->m_fValue, (TgFLOAT64)psEvent->m_fDiff );
            break;
        case ETgPROP_GAMEPAD__LTHUMB_Y:
            TgMSGF(0xC, u8"%-16.16s(%-32.32s): %f %f\n", u8"Input Test", u8"GamePad Left Thumb Y", (TgFLOAT64)psEvent->m_fValue, (TgFLOAT64)psEvent->m_fDiff );
            break;
        case ETgPROP_GAMEPAD__RTHUMB_X:
            TgMSGF(0xC, u8"%-16.16s(%-32.32s): %f %f\n", u8"Input Test", u8"GamePad Right Thumb X", (TgFLOAT64)psEvent->m_fValue, (TgFLOAT64)psEvent->m_fDiff );
            break;
        case ETgPROP_GAMEPAD__RTHUMB_Y:
            TgMSGF(0xC, u8"%-16.16s(%-32.32s): %f %f\n", u8"Input Test", u8"GamePad Right Thumb Y", (TgFLOAT64)psEvent->m_fValue, (TgFLOAT64)psEvent->m_fDiff );
            break;
        case ETgPROP_GAMEPAD__MAX:
            TgMSGF(0xC, u8"%-16.16s(%-32.32s)\n", u8"Input Test", u8"GamePad Activate" );
            break;
        case ETgPROP_GAMEPAD__VALID:
            TgS_NO_DEFAULT(break);
    }

    TgSTD_ATOMIC(fetch_add)( &s_xuiTest_Count, 1 );
    return (true); /* Consume the input event */
}
