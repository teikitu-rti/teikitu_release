/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Input [Unit Test] - Mouse.c
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

static TgBOOL                               TEST__Consumer_Mouse( TgUINT_PTR_C, TgFLOAT32_C, STg2_IN_Event_CPC );
static TgBOOL                               TEST__Consumer_GUI_Mouse( TgUINT_PTR_C, TgFLOAT32_C, STg2_IN_Event_CPC );

static TgRSIZE_A                            s_xuiTest_Count;




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Unit Test Functions                                                                                                                                                            */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- TEST_METHOD(TEST__Input_GUI_Mouse) --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE(TEST__Input_GUI_Mouse)
{
    TgIN_CONSUMER_ID                    tiConsumer_Id;

    if (!tgIN_Has_Producer( ETgCONTROLLER_GUI_MOUSE ))
    {
        return (KTgS_OK);
    };

    tiConsumer_Id = tgIN_Insert_Consumer( ETgCONTROLLER_GUI_MOUSE, 0, TEST__Consumer_GUI_Mouse, 0 );

    TgSTD_ATOMIC(store)( &s_xuiTest_Count, 0 );
    while (TgSTD_ATOMIC(load)( &s_xuiTest_Count ) < 64)
    {
        tgIN_Module_Update( 0.1F );
        Unit_Test__Sleep( 30000000 );
    };

    tgIN_Remove_Consumer( tiConsumer_Id );
    tgIN_Module_Update( 0.1F );

    return (KTgS_OK);
}


/* ---- TEST_METHOD(TEST__Input_Mouse) ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE(TEST__Input_Mouse)
{
    TgIN_CONSUMER_ID                    tiConsumer_Id;

    if (!tgIN_Has_Producer( ETgCONTROLLER_MOUSE ))
    {
        return (KTgS_OK);
    };

    tiConsumer_Id = tgIN_Insert_Consumer( ETgCONTROLLER_MOUSE, 0, TEST__Consumer_Mouse, 0 );

    TgSTD_ATOMIC(store)( &s_xuiTest_Count, 0 );
    while (TgSTD_ATOMIC(load)( &s_xuiTest_Count ) < 64)
    {
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

/* ---- TEST__Consumer_Mouse ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgBOOL TEST__Consumer_Mouse( TgATTRIBUTE_UNUSED TgUINT_PTR_C uiUnused, TgATTRIBUTE_UNUSED TgFLOAT32_C fDT, STg2_IN_Event_CPC psEvent )
{
    TgCHAR_U8_CP                        szNameList[ETgPROP_MOUSE_MAX] = {
                                            u8"Button 0",   u8"Button 1",   u8"Button 2",   u8"Button 3",
                                            u8"Button 4",   u8"Button 5",   u8"Button 6",   u8"Button 7",
                                            u8"Axis X",     u8"Axis Y",     u8"Axis Z" };

    (void)szNameList; // -Wunused-variable
    (void)psEvent; // -Wunused-parameter

    TgMSGF(0xC, u8"%-16.16s(Mouse - %-24.24s): %f %f\n", "Input Test", szNameList[psEvent->m_enProp.Mouse], (TgFLOAT64)psEvent->m_fValue, (TgFLOAT64)psEvent->m_fDiff);
    TgSTD_ATOMIC(fetch_add)( &s_xuiTest_Count, 1 );
    return (true);
}


/* ---- TEST__Consumer_GUI_Mouse ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgBOOL TEST__Consumer_GUI_Mouse( TgATTRIBUTE_UNUSED TgUINT_PTR_C uiA, TgATTRIBUTE_UNUSED TgFLOAT32_C fA, STg2_IN_Event_CPC psEvent )
{
    TgCHAR_U8_CP                        szNameList[ETgPROP_GUI_MOUSE_MAX] = {
                                            u8"Button 0",   u8"Button 1",   u8"Button 2",   u8"Button 3",
                                            u8"Button 4",   u8"Axis X",     u8"Axis Y",     u8"Axis Z" };

    (void)szNameList; // -Wunused-variable
    (void)psEvent; // -Wunused-parameter

    TgMSGF(0xC, u8"%-16.16s(GUI Mouse - %-20.20s): %d\n", "Input Test", szNameList[psEvent->m_enProp.GUI_Mouse], (TgSINT_E16 )(psEvent->m_uiUTF32 & 0xFFFF));
    TgSTD_ATOMIC(fetch_add)( &s_xuiTest_Count, 1 );
    return (true);
}
