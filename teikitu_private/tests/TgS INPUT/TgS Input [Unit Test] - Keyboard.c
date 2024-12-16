/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Input [Unit Test] - Keyboard.c
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

static TgBOOL                               TEST__Consumer_Keyboard( TgUINT_PTR_C, TgFLOAT32_C, STg2_IN_Event_CPC );

static TgRSIZE_A                            s_xuiTest_Count;




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Unit Test Functions                                                                                                                                                            */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- TEST_METHOD(TEST__Input_GUI_Keyboard) ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE(TEST__Input_GUI_Keyboard)
{
    TgIN_CONSUMER_ID                    tiConsumer_Id;

    if (!tgIN_Has_Producer( ETgCONTROLLER_GUI_KEYBOARD ))
    {
        return (KTgS_OK);
    };

    tiConsumer_Id = tgIN_Insert_Consumer( ETgCONTROLLER_GUI_KEYBOARD, 0, TEST__Consumer_Keyboard, 0 );

    TgSTD_ATOMIC(store)( &s_xuiTest_Count, 0 );
    while (TgSTD_ATOMIC(load)( &s_xuiTest_Count ) < 20)
    {
        tgIN_Module_Update( 0.1F );
        Unit_Test__Sleep( 30 );
    };

    tgIN_Remove_Consumer( tiConsumer_Id );
    tgIN_Module_Update( 0.1F );

    return (KTgS_OK);
}


/* ---- TEST_METHOD(TEST__Input_Keyboard) ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE(TEST__Input_Keyboard)
{
    TgIN_CONSUMER_ID                    tiConsumer_Id;

    if (!tgIN_Has_Producer( ETgCONTROLLER_KEYBOARD ))
    {
        return (KTgS_OK);
    };

    tiConsumer_Id = tgIN_Insert_Consumer( ETgCONTROLLER_KEYBOARD, 0, TEST__Consumer_Keyboard, 0 );

    TgSTD_ATOMIC(store)( &s_xuiTest_Count, 0 );
    while (TgSTD_ATOMIC(load)( &s_xuiTest_Count ) < 20)
    {
        tgIN_Module_Update( 0.1F );
        Unit_Test__Sleep( 30 );
    };

    tgIN_Remove_Consumer( tiConsumer_Id );
    tgIN_Module_Update( 0.1F );

    return (KTgS_OK);
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- TEST__Consumer_Keyboard -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgBOOL TEST__Consumer_Keyboard( TgATTRIBUTE_UNUSED TgUINT_PTR_C uiUnused, TgATTRIBUTE_UNUSED TgFLOAT32_C fDT, STg2_IN_Event_CPC psEvent )
{
    if (0 != psEvent->m_uiUTF32)
    {
        TgMSGF( 0xC, u8"%-16.16s(%-32.32s): %c\n", u8"Input Test", u8"Keyboard Key", psEvent->m_uiUTF32 );
    }
    else
    {
        TgMSGF( 0xC, u8"%-16.16s(%-32.32s): Property Key\n", u8"Input Test", u8"Keyboard Key", psEvent->m_uiUTF32 );
    };

    TgSTD_ATOMIC(fetch_add)( &s_xuiTest_Count, 1 );
    return (true); /* Consume the input event */
}
