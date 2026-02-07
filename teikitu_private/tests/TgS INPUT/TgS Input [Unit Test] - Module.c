/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Input [Unit Test] - Module.c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   4.51 | »GUID« A9981407-3EC9-42AF-8B6F-8BE6DD919615                                                                                                                 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Input ====================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
#if TgCOMPILE__THREAD
static TgBOOL                               TEST__Consumer_Module( TgUINT_PTR_C, TgFLOAT32_C, STg2_IN_Event_CPC );
static TgUINT_E32                           tgIN_Module_Test_Thread( TgUINT_PTR_C );
#endif

static TgRSIZE_A                            s_xuiTest_Count;
static TgRSIZE_A                            s_xnuiStat_Insert, s_xnuiStat_Remove;

enum { ETgIN_UNIT_TEST__THREAD_COUNT        = 8 };




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Unit Test Functions                                                                                                                                                            */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- TEST_METHOD(TEST__Input_Module) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE(TEST__Input_Module)
{
#if TgCOMPILE__THREAD
    TgTHREAD_ID                         uiTest_Thread[ETgIN_UNIT_TEST__THREAD_COUNT];
    TgUINT_E32                          uiIndex;
/*# TgCOMPILE__THREAD */
#endif

    TgSTD_ATOMIC(store)( &s_xnuiStat_Insert, 0 );
    TgSTD_ATOMIC(store)( &s_xnuiStat_Remove, 0 );
    TgSTD_ATOMIC(store)( &s_xuiTest_Count, 0 );

#if TgCOMPILE__THREAD
    for (uiIndex = 0; uiIndex < ETgIN_UNIT_TEST__THREAD_COUNT; ++uiIndex)
    {
        uiTest_Thread[uiIndex] = tgTR_Create( tgIN_Module_Test_Thread, 0, 0, ETgTHREAD_PRIORITY__NORMAL, u8"Test Input Module" );
    };

    while (TgSTD_ATOMIC(load)( &s_xuiTest_Count ) < ETgIN_UNIT_TEST__THREAD_COUNT)
    {
        tgIN_Module_Update( 0.1F );
        Unit_Test__Sleep( 30000000 );
    };

    for (uiIndex = 0; uiIndex < ETgIN_UNIT_TEST__THREAD_COUNT; ++uiIndex)
    {
        tgTR_Close( uiTest_Thread[uiIndex] );
    };
/*# TgCOMPILE__THREAD */
#endif

    tgIN_Module_Update( 0.1F );
    tgIN_Module_Update( 0.1F );

#if TgS_STAT__INPUT
    Test__Expect_EQ( TgSTD_ATOMIC(load)( &s_xnuiStat_Insert ), tgIN_Stat_Query_Total_Insert() );
    Test__Expect_EQ( TgSTD_ATOMIC(load)( &s_xnuiStat_Remove ), tgIN_Stat_Query_Total_Remove() );
#endif

    TgMSGF( 0xE, u8"%-16.16s(%-32.32s): %-48.48s % 14d\n", u8"Input", u8"Unit Test", u8"Thread Test Total Insert", TgSTD_ATOMIC(load)( &s_xnuiStat_Insert ) );
    TgMSGF( 0xE, u8"%-16.16s(%-32.32s): %-48.48s % 14d\n", u8"Input", u8"Unit Test", u8"Thread Test Total Remove", TgSTD_ATOMIC(load)( &s_xnuiStat_Remove ) );

    return (KTgS_OK);
}


/* ---- TEST_METHOD(TEST__Input_Stat) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE(TEST__Input_Stat)
{
#if TgS_STAT__INPUT
    tgIN_Stats( nullptr );
#endif
    return (KTgS_OK);
}


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- TEST__Consumer_Module ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if TgCOMPILE__THREAD
static TgBOOL TEST__Consumer_Module( TgATTRIBUTE_UNUSED TgUINT_PTR_C uiUnused, TgATTRIBUTE_UNUSED TgFLOAT32_C fDT, TgATTRIBUTE_UNUSED STg2_IN_Event_CPC psEvent )
{
    return (false);
}
/*# TgCOMPILE__THREAD */
#endif


/* ---- tgIN_Module_Test_Thread -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if TgCOMPILE__THREAD
static TgUINT_E32 tgIN_Module_Test_Thread( TgATTRIBUTE_UNUSED TgUINT_PTR_C uiUnused )
{
    TgIN_CONSUMER_ID                    atiConsumer_Id[64];
    TgUINT_E32                          uiIndex, uiMax;
    TgUINT_E32                          nuiTotal;
    TgFLOAT32                           fStart, fDelta = 0.0F;
    TgUINT_E32                          nuiLocal_Insert, nuiLocal_Remove;

    nuiLocal_Insert = nuiLocal_Remove = nuiTotal = 0;

    fStart = tgTM_Query_Time();

    do
    {
        uiMax = tgCM_RAND_U32() % tgCM_MIN_U32( 64 - nuiTotal, 7 );
        for (uiIndex = 0; uiIndex < uiMax; ++uiIndex)
        {
            TgIN_CONSUMER_ID                    tiConsumer_Id;

            tiConsumer_Id = tgIN_Insert_Consumer( (ETgCONTROLLER)(tgCM_RAND_U32() % ETgCONTROLLER__MAX), tgCM_RAND_U32(), TEST__Consumer_Module, 0 );

            if (KTgID__INVALID_VALUE != tiConsumer_Id.m_uiKI)
            {
                atiConsumer_Id[nuiTotal++] = tiConsumer_Id;
                ++nuiLocal_Insert;
                TgSTD_ATOMIC(fetch_add)( &s_xnuiStat_Insert, 1 );
            }
        };

        Unit_Test__Sleep( tgCM_RAND_U32() % 17000000 );

        if (0 == nuiTotal)
        {
            continue;
        };

        uiMax = tgCM_RAND_U32() % nuiTotal;
        for (uiIndex = 0; uiIndex < uiMax; ++uiIndex)
        {
            tgIN_Remove_Consumer( atiConsumer_Id[--nuiTotal] );
            ++nuiLocal_Remove;
            TgSTD_ATOMIC(fetch_add)( &s_xnuiStat_Remove, 1 );
        };

        Unit_Test__Sleep( tgCM_RAND_U32() % 17000000 );

        fDelta = tgTM_Query_Time() - fStart;
    }
    while (fDelta < 120.0F);

    uiMax = nuiTotal;

    for (uiIndex = 0; uiIndex < uiMax; ++uiIndex)
    {
        tgIN_Remove_Consumer( atiConsumer_Id[--nuiTotal] );
        ++nuiLocal_Remove;
        TgSTD_ATOMIC(fetch_add)( &s_xnuiStat_Remove, 1 );
    };

    Unit_Test__Sleep( tgCM_RAND_U32() % 17000000 );

    TgERROR( nuiLocal_Insert == nuiLocal_Remove );

    TgSTD_ATOMIC(fetch_add)( &s_xuiTest_Count, 1 );
    return (0);
}
/*# TgCOMPILE__THREAD */
#endif


