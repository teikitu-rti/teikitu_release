/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common [Unit Test] [Test] - Event MGR.c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TEST_METHOD( UNIT_TEST__TEST__EM_Init_MGR );
TEST_METHOD( UNIT_TEST__TEST__EM_Boot_MGR );
TEST_METHOD( UNIT_TEST__TEST__EM_Stop_MGR );
TEST_METHOD( UNIT_TEST__TEST__EM_Free_MGR );
TEST_METHOD( UNIT_TEST__TEST__EM_Update_MGR );
TEST_METHOD( UNIT_TEST__TEST__EM_Update_MGR_Is_Complete );
TEST_METHOD( UNIT_TEST__TEST__EM_Query_Init );
TEST_METHOD( UNIT_TEST__TEST__EM_Query_Boot );
TEST_METHOD( UNIT_TEST__TEST__EM_Query_Fixed_Memory );
TEST_METHOD( UNIT_TEST__TEST__EM_Set_Pause );
TEST_METHOD( UNIT_TEST__TEST__EM_Query_Pause );
TEST_METHOD( UNIT_TEST__TEST__EM_Stats );
TEST_METHOD( UNIT_TEST__TEST__EM_TE_FRM_NEW );
TEST_METHOD( UNIT_TEST__TEST__EM_TE_FRM_DEL );
TEST_METHOD( UNIT_TEST__TEST__EM_TE_FRM_Set_Pause );
TEST_METHOD( UNIT_TEST__TEST__EM_TE_FRM_Set_Start_Frame );
TEST_METHOD( UNIT_TEST__TEST__EM_TE_FRM_Set_End_Frame );
TEST_METHOD( UNIT_TEST__TEST__EM_TE_FRM_Set_Frame_To_Live );
TEST_METHOD( UNIT_TEST__TEST__EM_TE_FRM_Query_Valid );
TEST_METHOD( UNIT_TEST__TEST__EM_TE_FRM_Query_Paused );
TEST_METHOD( UNIT_TEST__TEST__EM_TE_FRM_Query_Start_Frame );
TEST_METHOD( UNIT_TEST__TEST__EM_TE_FRM_Query_End_Frame );
TEST_METHOD( UNIT_TEST__TEST__EM_TE_FRM_Query_Frame_To_Live );
TEST_METHOD( UNIT_TEST__TEST__EM_TE_SEC_NEW );
TEST_METHOD( UNIT_TEST__TEST__EM_TE_SEC_DEL );
TEST_METHOD( UNIT_TEST__TEST__EM_TE_SEC_Set_Pause );
TEST_METHOD( UNIT_TEST__TEST__EM_TE_SEC_Set_Start_Time );
TEST_METHOD( UNIT_TEST__TEST__EM_TE_SEC_Set_End_Time );
TEST_METHOD( UNIT_TEST__TEST__EM_TE_SEC_Set_Time_To_Live );
TEST_METHOD( UNIT_TEST__TEST__EM_TE_SEC_Query_Valid );
TEST_METHOD( UNIT_TEST__TEST__EM_TE_SEC_Query_Paused );
TEST_METHOD( UNIT_TEST__TEST__EM_TE_SEC_Query_Start_Time );
TEST_METHOD( UNIT_TEST__TEST__EM_TE_SEC_Query_End_Time );
TEST_METHOD( UNIT_TEST__TEST__EM_TE_SEC_Query_Time_To_Live );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

static TgNOTHROW TgVOID
EM_TE_FRM_Unit_Test(
    TgUINT_PTR_C );

static TgNOTHROW TgVOID
EM_TE_SEC_Unit_Test(
    TgUINT_PTR_C );

static TgSINT_F32 s_iEvent_MGR_Test;




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- UNIT_TEST__TEST__COMMON_Event_MGR ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( UNIT_TEST__TEST__COMMON_Event_MGR )
{
#if TgCOMPILE__THREAD
    TgJOB_THREAD_ID                     tiJob_Thread[3];
    TgJOB_QUEUE_ID                      atiQueueList[4];
/*# TgCOMPILE__THREAD */
#endif

    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__EM_Init_MGR());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__EM_Boot_MGR());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__EM_Stop_MGR());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__EM_Free_MGR());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__EM_Update_MGR());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__EM_Update_MGR_Is_Complete());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__EM_Query_Init());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__EM_Query_Boot());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__EM_Query_Fixed_Memory());

    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__EM_Set_Pause());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__EM_Query_Pause());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__EM_Stats());

    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__EM_TE_FRM_NEW());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__EM_TE_FRM_DEL());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__EM_TE_FRM_Set_Pause());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__EM_TE_FRM_Set_Start_Frame());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__EM_TE_FRM_Set_End_Frame());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__EM_TE_FRM_Set_Frame_To_Live());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__EM_TE_FRM_Query_Valid());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__EM_TE_FRM_Query_Paused());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__EM_TE_FRM_Query_Start_Frame());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__EM_TE_FRM_Query_End_Frame());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__EM_TE_FRM_Query_Frame_To_Live());

    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__EM_TE_SEC_NEW());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__EM_TE_SEC_DEL());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__EM_TE_SEC_Set_Pause());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__EM_TE_SEC_Set_Start_Time());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__EM_TE_SEC_Set_End_Time());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__EM_TE_SEC_Set_Time_To_Live());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__EM_TE_SEC_Query_Valid());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__EM_TE_SEC_Query_Paused());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__EM_TE_SEC_Query_Start_Time());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__EM_TE_SEC_Query_End_Time());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__EM_TE_SEC_Query_Time_To_Live());

#if TgCOMPILE__THREAD
    atiQueueList[0] = g_tiJob_Queue__OS;
    atiQueueList[1] = KTgJOB_QUEUE_ID__INVALID;

    tiJob_Thread[0] = tgJM_Spawn_Job_Thread( atiQueueList, 4, ETgTHREAD_PRIORITY__NORMAL, u8"Event_MGR_Unit_Test" );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiJob_Thread[0].m_uiKI);
    tiJob_Thread[1] = tgJM_Spawn_Job_Thread( atiQueueList, 4, ETgTHREAD_PRIORITY__NORMAL, u8"Event_MGR_Unit_Test" );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiJob_Thread[1].m_uiKI);
    tiJob_Thread[2] = tgJM_Spawn_Job_Thread( atiQueueList, 4, ETgTHREAD_PRIORITY__NORMAL, u8"Event_MGR_Unit_Test" );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiJob_Thread[2].m_uiKI);

    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__EM_TE_FRM_NEW());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__EM_TE_FRM_DEL());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__EM_TE_FRM_Set_Pause());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__EM_TE_FRM_Set_Start_Frame());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__EM_TE_FRM_Set_End_Frame());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__EM_TE_FRM_Set_Frame_To_Live());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__EM_TE_FRM_Query_Valid());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__EM_TE_FRM_Query_Paused());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__EM_TE_FRM_Query_Start_Frame());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__EM_TE_FRM_Query_End_Frame());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__EM_TE_FRM_Query_Frame_To_Live());

    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__EM_TE_SEC_NEW());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__EM_TE_SEC_DEL());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__EM_TE_SEC_Set_Pause());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__EM_TE_SEC_Set_Start_Time());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__EM_TE_SEC_Set_End_Time());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__EM_TE_SEC_Set_Time_To_Live());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__EM_TE_SEC_Query_Valid());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__EM_TE_SEC_Query_Paused());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__EM_TE_SEC_Query_Start_Time());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__EM_TE_SEC_Query_End_Time());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__EM_TE_SEC_Query_Time_To_Live());

    while (!tgEM_Update_MGR_Is_Complete());

    tgJM_Stop_Job_Thread( tiJob_Thread[0] );
    tgJM_Stop_Job_Thread( tiJob_Thread[1] );
    tgJM_Stop_Job_Thread( tiJob_Thread[2] );
/*# TgCOMPILE__THREAD */
#endif

    TEST_END_METHOD( KTgS_OK );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- UNIT_TEST__TEST__EM_Init_MGR --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__EM_Init_MGR )
{
    /* Due to their nature, module management functions can not be unit tested */

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__EM_Boot_MGR --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__EM_Boot_MGR )
{
    /* Due to their nature, module management functions can not be unit tested */

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__EM_Stop_MGR --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__EM_Stop_MGR )
{
    /* Due to their nature, module management functions can not be unit tested */

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__EM_Free_MGR --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__EM_Free_MGR )
{
    /* Due to their nature, module management functions can not be unit tested */

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__EM_Update_MGR ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__EM_Update_MGR )
{
    /* Due to their nature, module management functions can not be unit tested */

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__EM_Update_MGR_Is_Complete ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__EM_Update_MGR_Is_Complete )
{


    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__EM_Query_Init ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__EM_Query_Init )
{
    Test__Expect_EQ(true, tgEM_Query_Init());
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__EM_Query_Boot ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__EM_Query_Boot )
{
    Test__Expect_EQ(true, tgEM_Query_Boot());

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__EM_Query_Fixed_Memory ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__EM_Query_Fixed_Memory )
{
    tgEM_Query_Fixed_Memory();

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__EM_Set_Pause -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__EM_Set_Pause )
{
    tgEM_Set_Pause( false );
    Test__Expect_EQ(false, tgEM_Query_Pause());
    tgEM_Set_Pause( true );
    Test__Expect_EQ(true, tgEM_Query_Pause());
    tgEM_Set_Pause( false );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__EM_Query_Pause ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__EM_Query_Pause )
{
    /* Tested in UNIT_TEST__TEST__EM_Set_Pause */

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__EM_Stats ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__EM_Stats )
{


    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__EM_TE_FRM_NEW ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__EM_TE_FRM_NEW )
{
    TgEM_TE_FRM_ID                      tiEM_TE_FRM_ID;

    /* Test creation of an event one frame in the future and a life time of 2 frames */
    tiEM_TE_FRM_ID = tgEM_TE_FRM_NEW( EM_TE_FRM_Unit_Test, 0, tgGB_Query_Total_Frame() + 1, tgGB_Query_Total_Frame() + 3 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiEM_TE_FRM_ID.m_uiKI);
    Test__Expect_EQ(true, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));

    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(true, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));

    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(true, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));

    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(false, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));


    /* Test creation of an event one frame in the past and a life time of 2 frames */
    tiEM_TE_FRM_ID = tgEM_TE_FRM_NEW( EM_TE_FRM_Unit_Test, 0, tgGB_Query_Total_Frame() - 1, tgGB_Query_Total_Frame() + 1 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiEM_TE_FRM_ID.m_uiKI);
    Test__Expect_EQ(true, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));

    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(false, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));


    /* Test the execution of the an event and having it reach end of life */
    s_iEvent_MGR_Test = 0;

    tiEM_TE_FRM_ID = tgEM_TE_FRM_NEW( EM_TE_FRM_Unit_Test, 0, tgGB_Query_Total_Frame(), tgGB_Query_Total_Frame() + 2 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiEM_TE_FRM_ID.m_uiKI);
    Test__Expect_EQ(true, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));

    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(1, s_iEvent_MGR_Test);
    Test__Expect_EQ(true, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));

    tgGB_Inc_Frame_Time( 2.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(2, s_iEvent_MGR_Test);
    Test__Expect_EQ(false, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));

    tgGB_Inc_Frame_Time( 2.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(2, s_iEvent_MGR_Test);

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__EM_TE_FRM_DEL ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__EM_TE_FRM_DEL )
{
    TgEM_TE_FRM_ID                      tiEM_TE_FRM_ID;

    /* Test deletion of an event in the same frame causes it not to execute */
    s_iEvent_MGR_Test = 0;

    tiEM_TE_FRM_ID = tgEM_TE_FRM_NEW( EM_TE_FRM_Unit_Test, 0, tgGB_Query_Total_Frame(), tgGB_Query_Total_Frame() + 2 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiEM_TE_FRM_ID.m_uiKI);
    Test__Expect_EQ(true, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));

    Test__Expect_EQ(KTgS_OK, tgEM_TE_FRM_DEL( tiEM_TE_FRM_ID ));
    Test__Expect_EQ(false, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));

    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(0, s_iEvent_MGR_Test);


    /* Test the execution of the an event and delete it after an update */
    s_iEvent_MGR_Test = 0;

    tiEM_TE_FRM_ID = tgEM_TE_FRM_NEW( EM_TE_FRM_Unit_Test, 0, tgGB_Query_Total_Frame(), tgGB_Query_Total_Frame() + 2 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiEM_TE_FRM_ID.m_uiKI);
    Test__Expect_EQ(true, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));

    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(1, s_iEvent_MGR_Test);
    Test__Expect_EQ(true, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));
    Test__Expect_EQ(KTgS_OK, tgEM_TE_FRM_DEL( tiEM_TE_FRM_ID ));
    Test__Expect_EQ(false, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));

    tgGB_Inc_Frame_Time( 2.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(1, s_iEvent_MGR_Test);
    

    /* Test the execution of the an event and having it reach end of life, and attempt to delete it */
    s_iEvent_MGR_Test = 0;

    tiEM_TE_FRM_ID = tgEM_TE_FRM_NEW( EM_TE_FRM_Unit_Test, 0, tgGB_Query_Total_Frame(), tgGB_Query_Total_Frame() + 2 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiEM_TE_FRM_ID.m_uiKI);
    Test__Expect_EQ(true, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));

    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(1, s_iEvent_MGR_Test);
    Test__Expect_EQ(true, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));

    tgGB_Inc_Frame_Time( 2.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(2, s_iEvent_MGR_Test);
    Test__Expect_EQ(false, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));
    Test__Expect_NE(KTgS_OK, tgEM_TE_FRM_DEL( tiEM_TE_FRM_ID ));

    tgGB_Inc_Frame_Time( 2.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(2, s_iEvent_MGR_Test);

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__EM_TE_FRM_Set_Pause ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__EM_TE_FRM_Set_Pause )
{
    TgEM_TE_FRM_ID                      tiEM_TE_FRM_ID;

    /* Test pause of an event before it starts */
    s_iEvent_MGR_Test = 0;

    tiEM_TE_FRM_ID = tgEM_TE_FRM_NEW( EM_TE_FRM_Unit_Test, 0, tgGB_Query_Total_Frame() + 1, tgGB_Query_Total_Frame() + 3 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiEM_TE_FRM_ID.m_uiKI);

    Test__Expect_EQ(true, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));
    Test__Expect_EQ(0, s_iEvent_MGR_Test);
    Test__Expect_EQ(KTgS_OK, tgEM_TE_FRM_Set_Pause( tiEM_TE_FRM_ID, true ));
    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(true, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));
    Test__Expect_EQ(0, s_iEvent_MGR_Test);
    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(true, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));
    Test__Expect_EQ(0, s_iEvent_MGR_Test);
    Test__Expect_EQ(KTgS_OK, tgEM_TE_FRM_Set_Pause( tiEM_TE_FRM_ID, false ));
    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(true, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));
    Test__Expect_EQ(1, s_iEvent_MGR_Test);
    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(true, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));
    Test__Expect_EQ(2, s_iEvent_MGR_Test);
    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(false, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));
    Test__Expect_EQ(3, s_iEvent_MGR_Test);


    /* Test pausing of an event in the same frame that it should start */
    s_iEvent_MGR_Test = 0;

    tiEM_TE_FRM_ID = tgEM_TE_FRM_NEW( EM_TE_FRM_Unit_Test, 0, tgGB_Query_Total_Frame(), tgGB_Query_Total_Frame() + 2 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiEM_TE_FRM_ID.m_uiKI);

    Test__Expect_EQ(true, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));
    Test__Expect_EQ(0, s_iEvent_MGR_Test);
    Test__Expect_EQ(KTgS_OK, tgEM_TE_FRM_Set_Pause( tiEM_TE_FRM_ID, true ));
    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(true, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));
    Test__Expect_EQ(0, s_iEvent_MGR_Test);
    Test__Expect_EQ(KTgS_OK, tgEM_TE_FRM_Set_Pause( tiEM_TE_FRM_ID, false ));
    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(true, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));
    Test__Expect_EQ(1, s_iEvent_MGR_Test);
    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(false, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));
    Test__Expect_EQ(2, s_iEvent_MGR_Test);


    /* Test pausing an event during execution */
    s_iEvent_MGR_Test = 0;

    tiEM_TE_FRM_ID = tgEM_TE_FRM_NEW( EM_TE_FRM_Unit_Test, 0, tgGB_Query_Total_Frame(), tgGB_Query_Total_Frame() + 2 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiEM_TE_FRM_ID.m_uiKI);

    Test__Expect_EQ(true, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));
    Test__Expect_EQ(0, s_iEvent_MGR_Test);
    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(true, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));
    Test__Expect_EQ(1, s_iEvent_MGR_Test);
    Test__Expect_EQ(KTgS_OK, tgEM_TE_FRM_Set_Pause( tiEM_TE_FRM_ID, true ));
    tgGB_Inc_Frame_Time( 2.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(true, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));
    Test__Expect_EQ(1, s_iEvent_MGR_Test);
    Test__Expect_EQ(KTgS_OK, tgEM_TE_FRM_Set_Pause( tiEM_TE_FRM_ID, false ));
    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(false, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));
    Test__Expect_EQ(2, s_iEvent_MGR_Test);

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__EM_TE_FRM_Set_Start_Frame ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__EM_TE_FRM_Set_Start_Frame )
{
    TgEM_TE_FRM_ID                      tiEM_TE_FRM_ID;

    /* Test behaviour without setting the start frame */
    s_iEvent_MGR_Test = 0;

    tiEM_TE_FRM_ID = tgEM_TE_FRM_NEW( EM_TE_FRM_Unit_Test, 0, tgGB_Query_Total_Frame() + 10, tgGB_Query_Total_Frame() + 12 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiEM_TE_FRM_ID.m_uiKI);
    Test__Expect_EQ(true, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));

    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(0, s_iEvent_MGR_Test);
    Test__Expect_EQ(true, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));

    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(0, s_iEvent_MGR_Test);
    Test__Expect_EQ(true, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));
    
    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(0, s_iEvent_MGR_Test);
    Test__Expect_EQ(true, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));

    Test__Expect_EQ(KTgS_OK, tgEM_TE_FRM_DEL( tiEM_TE_FRM_ID ));
    Test__Expect_EQ(false, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));



    /* Test behaviour after setting the start frame */
    s_iEvent_MGR_Test = 0;

    tiEM_TE_FRM_ID = tgEM_TE_FRM_NEW( EM_TE_FRM_Unit_Test, 0, tgGB_Query_Total_Frame() + 10, tgGB_Query_Total_Frame() + 12 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiEM_TE_FRM_ID.m_uiKI);
    Test__Expect_EQ(true, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));

    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(0, s_iEvent_MGR_Test);
    Test__Expect_EQ(true, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));

    Test__Expect_EQ(KTgS_OK, tgEM_TE_FRM_Set_Start_Frame( tiEM_TE_FRM_ID, tgGB_Query_Total_Frame() ));

    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(1, s_iEvent_MGR_Test);
    Test__Expect_EQ(true, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));
    
    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(2, s_iEvent_MGR_Test);
    Test__Expect_EQ(true, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));

    Test__Expect_EQ(KTgS_OK, tgEM_TE_FRM_DEL( tiEM_TE_FRM_ID ));
    Test__Expect_EQ(false, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__EM_TE_FRM_Set_End_Frame --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__EM_TE_FRM_Set_End_Frame )
{
    TgEM_TE_FRM_ID                      tiEM_TE_FRM_ID;

    /* Test behaviour without setting the end frame */
    s_iEvent_MGR_Test = 0;

    tiEM_TE_FRM_ID = tgEM_TE_FRM_NEW( EM_TE_FRM_Unit_Test, 0, tgGB_Query_Total_Frame(), tgGB_Query_Total_Frame() + 2 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiEM_TE_FRM_ID.m_uiKI);
    Test__Expect_EQ(true, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));

    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(1, s_iEvent_MGR_Test);
    Test__Expect_EQ(true, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));

    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(2, s_iEvent_MGR_Test);
    Test__Expect_EQ(false, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));
    


    /* Test behaviour after setting the end frame */
    s_iEvent_MGR_Test = 0;

    tiEM_TE_FRM_ID = tgEM_TE_FRM_NEW( EM_TE_FRM_Unit_Test, 0, tgGB_Query_Total_Frame(), tgGB_Query_Total_Frame() + 2 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiEM_TE_FRM_ID.m_uiKI);
    Test__Expect_EQ(true, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));

    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(1, s_iEvent_MGR_Test);
    Test__Expect_EQ(true, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));

    Test__Expect_EQ(KTgS_OK, tgEM_TE_FRM_Set_End_Frame( tiEM_TE_FRM_ID, tgGB_Query_Total_Frame() + 4 ));

    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(2, s_iEvent_MGR_Test);
    Test__Expect_EQ(true, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));
    
    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(3, s_iEvent_MGR_Test);
    Test__Expect_EQ(true, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));

    Test__Expect_EQ(KTgS_OK, tgEM_TE_FRM_DEL( tiEM_TE_FRM_ID ));
    Test__Expect_EQ(false, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__EM_TE_FRM_Set_Frame_To_Live ----------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__EM_TE_FRM_Set_Frame_To_Live )
{
    TgEM_TE_FRM_ID                      tiEM_TE_FRM_ID;

    /* Test behaviour without setting the start frame */
    s_iEvent_MGR_Test = 0;

    tiEM_TE_FRM_ID = tgEM_TE_FRM_NEW( EM_TE_FRM_Unit_Test, 0, tgGB_Query_Total_Frame(), tgGB_Query_Total_Frame() + 2 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiEM_TE_FRM_ID.m_uiKI);
    Test__Expect_EQ(true, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));

    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(1, s_iEvent_MGR_Test);
    Test__Expect_EQ(true, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));

    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(2, s_iEvent_MGR_Test);
    Test__Expect_EQ(false, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));
    


    /* Test behaviour after setting the start frame without setting the start frame */
    s_iEvent_MGR_Test = 0;

    tiEM_TE_FRM_ID = tgEM_TE_FRM_NEW( EM_TE_FRM_Unit_Test, 0, tgGB_Query_Total_Frame(), tgGB_Query_Total_Frame() + 2 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiEM_TE_FRM_ID.m_uiKI);
    Test__Expect_EQ(true, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));

    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(1, s_iEvent_MGR_Test);
    Test__Expect_EQ(true, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));

    Test__Expect_EQ(KTgS_OK, tgEM_TE_FRM_Set_Frame_To_Live( tiEM_TE_FRM_ID, 2 ));

    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(2, s_iEvent_MGR_Test);
    Test__Expect_EQ(true, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));
    
    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(3, s_iEvent_MGR_Test);
    Test__Expect_EQ(false, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__EM_TE_FRM_Query_Valid ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__EM_TE_FRM_Query_Valid )
{
    TgEM_TE_FRM_ID                      tiEM_TE_FRM_ID;

    tiEM_TE_FRM_ID = tgEM_TE_FRM_NEW( EM_TE_FRM_Unit_Test, 0, tgGB_Query_Total_Frame(), tgGB_Query_Total_Frame() + 1 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiEM_TE_FRM_ID.m_uiKI);
    Test__Expect_EQ(true, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));

    Test__Expect_EQ(KTgS_OK, tgEM_TE_FRM_DEL( tiEM_TE_FRM_ID ));
    Test__Expect_EQ(false, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__EM_TE_FRM_Query_Paused ---------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__EM_TE_FRM_Query_Paused )
{
    TgEM_TE_FRM_ID                      tiEM_TE_FRM_ID;
    TgBOOL                              bValue;

    tiEM_TE_FRM_ID = tgEM_TE_FRM_NEW( EM_TE_FRM_Unit_Test, 0, tgGB_Query_Total_Frame(), tgGB_Query_Total_Frame() + 1 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiEM_TE_FRM_ID.m_uiKI);
    Test__Expect_EQ(true, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));
    Test__Expect_EQ(KTgS_OK, tgEM_TE_FRM_Query_Paused( &bValue, tiEM_TE_FRM_ID ));

    Test__Expect_EQ(KTgS_OK, tgEM_TE_FRM_DEL( tiEM_TE_FRM_ID ));
    Test__Expect_EQ(false, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__EM_TE_FRM_Query_Start_Frame ----------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__EM_TE_FRM_Query_Start_Frame )
{
    TgEM_TE_FRM_ID                      tiEM_TE_FRM_ID;
    TgSINT_E32                          iValue;

    tiEM_TE_FRM_ID = tgEM_TE_FRM_NEW( EM_TE_FRM_Unit_Test, 0, tgGB_Query_Total_Frame(), tgGB_Query_Total_Frame() + 1 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiEM_TE_FRM_ID.m_uiKI);
    Test__Expect_EQ(true, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));
    Test__Expect_EQ(KTgS_OK, tgEM_TE_FRM_Query_Start_Frame( &iValue, tiEM_TE_FRM_ID ));

    Test__Expect_EQ(KTgS_OK, tgEM_TE_FRM_DEL( tiEM_TE_FRM_ID ));
    Test__Expect_EQ(false, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__EM_TE_FRM_Query_End_Frame ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__EM_TE_FRM_Query_End_Frame )
{
    TgEM_TE_FRM_ID                      tiEM_TE_FRM_ID;
    TgSINT_E32                          iValue;

    tiEM_TE_FRM_ID = tgEM_TE_FRM_NEW( EM_TE_FRM_Unit_Test, 0, tgGB_Query_Total_Frame(), tgGB_Query_Total_Frame() + 1 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiEM_TE_FRM_ID.m_uiKI);
    Test__Expect_EQ(true, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));
    Test__Expect_EQ(KTgS_OK, tgEM_TE_FRM_Query_End_Frame( &iValue, tiEM_TE_FRM_ID ));

    Test__Expect_EQ(KTgS_OK, tgEM_TE_FRM_DEL( tiEM_TE_FRM_ID ));
    Test__Expect_EQ(false, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__EM_TE_FRM_Query_Frame_To_Live --------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__EM_TE_FRM_Query_Frame_To_Live )
{
    TgEM_TE_FRM_ID                      tiEM_TE_FRM_ID;
    TgSINT_E32                          iValue;

    tiEM_TE_FRM_ID = tgEM_TE_FRM_NEW( EM_TE_FRM_Unit_Test, 0, tgGB_Query_Total_Frame(), tgGB_Query_Total_Frame() + 1 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiEM_TE_FRM_ID.m_uiKI);
    Test__Expect_EQ(true, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));
    Test__Expect_EQ(KTgS_OK, tgEM_TE_FRM_Query_Frame_To_Live( &iValue, tiEM_TE_FRM_ID ));

    Test__Expect_EQ(KTgS_OK, tgEM_TE_FRM_DEL( tiEM_TE_FRM_ID ));
    Test__Expect_EQ(false, tgEM_TE_FRM_Query_Valid( tiEM_TE_FRM_ID ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__EM_TE_SEC_NEW ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__EM_TE_SEC_NEW )
{
    TgEM_TE_SEC_ID                      tiEM_TE_SEC_ID;

    /* Test creation of an event one frame in the future and a life time of 2 frames */
    tiEM_TE_SEC_ID = tgEM_TE_SEC_NEW( EM_TE_SEC_Unit_Test, 0, tgGB_Query_Total_Time() + 1, tgGB_Query_Total_Time() + 3 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiEM_TE_SEC_ID.m_uiKI);
    Test__Expect_EQ(true, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));

    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(true, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));

    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(true, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));

    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(false, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));


    /* Test creation of an event one frame in the past and a life time of 2 frames */
    tiEM_TE_SEC_ID = tgEM_TE_SEC_NEW( EM_TE_SEC_Unit_Test, 0, tgGB_Query_Total_Time() - 1, tgGB_Query_Total_Time() + 1 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiEM_TE_SEC_ID.m_uiKI);
    Test__Expect_EQ(true, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));

    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(false, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));


    /* Test the execution of the an event and having it reach end of life */
    s_iEvent_MGR_Test = 0;

    tiEM_TE_SEC_ID = tgEM_TE_SEC_NEW( EM_TE_SEC_Unit_Test, 0, tgGB_Query_Total_Time(), tgGB_Query_Total_Time() + 2 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiEM_TE_SEC_ID.m_uiKI);
    Test__Expect_EQ(true, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));

    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(1, s_iEvent_MGR_Test);
    Test__Expect_EQ(true, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));

    tgGB_Inc_Frame_Time( 2.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(2, s_iEvent_MGR_Test);
    Test__Expect_EQ(false, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));

    tgGB_Inc_Frame_Time( 2.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(2, s_iEvent_MGR_Test);

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__EM_TE_SEC_DEL ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__EM_TE_SEC_DEL )
{
    TgEM_TE_SEC_ID                      tiEM_TE_SEC_ID;

    /* Test deletion of an event in the same frame causes it not to execute */
    s_iEvent_MGR_Test = 0;

    tiEM_TE_SEC_ID = tgEM_TE_SEC_NEW( EM_TE_SEC_Unit_Test, 0, tgGB_Query_Total_Time(), tgGB_Query_Total_Time() + 2 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiEM_TE_SEC_ID.m_uiKI);
    Test__Expect_EQ(true, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));

    Test__Expect_EQ(KTgS_OK, tgEM_TE_SEC_DEL( tiEM_TE_SEC_ID ));
    Test__Expect_EQ(false, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));

    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(0, s_iEvent_MGR_Test);


    /* Test the execution of the an event and delete it after an update */
    s_iEvent_MGR_Test = 0;

    tiEM_TE_SEC_ID = tgEM_TE_SEC_NEW( EM_TE_SEC_Unit_Test, 0, tgGB_Query_Total_Time(), tgGB_Query_Total_Time() + 2 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiEM_TE_SEC_ID.m_uiKI);
    Test__Expect_EQ(true, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));

    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(1, s_iEvent_MGR_Test);
    Test__Expect_EQ(true, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));
    Test__Expect_EQ(KTgS_OK, tgEM_TE_SEC_DEL( tiEM_TE_SEC_ID ));
    Test__Expect_EQ(false, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));

    tgGB_Inc_Frame_Time( 2.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(1, s_iEvent_MGR_Test);
    

    /* Test the execution of the an event and having it reach end of life, and attempt to delete it */
    s_iEvent_MGR_Test = 0;

    tiEM_TE_SEC_ID = tgEM_TE_SEC_NEW( EM_TE_SEC_Unit_Test, 0, tgGB_Query_Total_Time(), tgGB_Query_Total_Time() + 2 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiEM_TE_SEC_ID.m_uiKI);
    Test__Expect_EQ(true, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));

    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(1, s_iEvent_MGR_Test);
    Test__Expect_EQ(true, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));

    tgGB_Inc_Frame_Time( 2.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(2, s_iEvent_MGR_Test);
    Test__Expect_EQ(false, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));
    Test__Expect_NE(KTgS_OK, tgEM_TE_SEC_DEL( tiEM_TE_SEC_ID ));

    tgGB_Inc_Frame_Time( 2.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(2, s_iEvent_MGR_Test);

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__EM_TE_SEC_Set_Pause ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__EM_TE_SEC_Set_Pause )
{
    TgEM_TE_SEC_ID                      tiEM_TE_SEC_ID;

    /* Test pause of an event before it starts */
    s_iEvent_MGR_Test = 0;

    tiEM_TE_SEC_ID = tgEM_TE_SEC_NEW( EM_TE_SEC_Unit_Test, 0, tgGB_Query_Total_Time() + 1.F, tgGB_Query_Total_Time() + 3.F );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiEM_TE_SEC_ID.m_uiKI);

    Test__Expect_EQ(true, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));
    Test__Expect_EQ(0, s_iEvent_MGR_Test);
    Test__Expect_EQ(KTgS_OK, tgEM_TE_SEC_Set_Pause( tiEM_TE_SEC_ID, true ));
    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(true, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));
    Test__Expect_EQ(0, s_iEvent_MGR_Test);
    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(true, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));
    Test__Expect_EQ(0, s_iEvent_MGR_Test);
    Test__Expect_EQ(KTgS_OK, tgEM_TE_SEC_Set_Pause( tiEM_TE_SEC_ID, false ));
    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(true, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));
    Test__Expect_EQ(1, s_iEvent_MGR_Test);
    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(true, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));
    Test__Expect_EQ(2, s_iEvent_MGR_Test);
    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(false, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));
    Test__Expect_EQ(3, s_iEvent_MGR_Test);


    /* Test pausing of an event in the same frame that it should start */
    s_iEvent_MGR_Test = 0;

    tiEM_TE_SEC_ID = tgEM_TE_SEC_NEW( EM_TE_SEC_Unit_Test, 0, tgGB_Query_Total_Time(), tgGB_Query_Total_Time() + 2 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiEM_TE_SEC_ID.m_uiKI);

    Test__Expect_EQ(true, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));
    Test__Expect_EQ(0, s_iEvent_MGR_Test);
    Test__Expect_EQ(KTgS_OK, tgEM_TE_SEC_Set_Pause( tiEM_TE_SEC_ID, true ));
    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(true, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));
    Test__Expect_EQ(0, s_iEvent_MGR_Test);
    Test__Expect_EQ(KTgS_OK, tgEM_TE_SEC_Set_Pause( tiEM_TE_SEC_ID, false ));
    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(true, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));
    Test__Expect_EQ(1, s_iEvent_MGR_Test);
    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(false, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));
    Test__Expect_EQ(2, s_iEvent_MGR_Test);


    /* Test pausing an event during execution */
    s_iEvent_MGR_Test = 0;

    tiEM_TE_SEC_ID = tgEM_TE_SEC_NEW( EM_TE_SEC_Unit_Test, 0, tgGB_Query_Total_Time(), tgGB_Query_Total_Time() + 2 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiEM_TE_SEC_ID.m_uiKI);

    Test__Expect_EQ(true, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));
    Test__Expect_EQ(0, s_iEvent_MGR_Test);
    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(true, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));
    Test__Expect_EQ(1, s_iEvent_MGR_Test);
    Test__Expect_EQ(KTgS_OK, tgEM_TE_SEC_Set_Pause( tiEM_TE_SEC_ID, true ));
    tgGB_Inc_Frame_Time( 2.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(true, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));
    Test__Expect_EQ(1, s_iEvent_MGR_Test);
    Test__Expect_EQ(KTgS_OK, tgEM_TE_SEC_Set_Pause( tiEM_TE_SEC_ID, false ));
    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(false, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));
    Test__Expect_EQ(2, s_iEvent_MGR_Test);

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__EM_TE_SEC_Set_Start_Time -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__EM_TE_SEC_Set_Start_Time )
{
    TgEM_TE_SEC_ID                      tiEM_TE_SEC_ID;

    /* Test behaviour without setting the start frame */
    s_iEvent_MGR_Test = 0;

    tiEM_TE_SEC_ID = tgEM_TE_SEC_NEW( EM_TE_SEC_Unit_Test, 0, tgGB_Query_Total_Time() + 10, tgGB_Query_Total_Time() + 12 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiEM_TE_SEC_ID.m_uiKI);
    Test__Expect_EQ(true, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));

    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(0, s_iEvent_MGR_Test);
    Test__Expect_EQ(true, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));

    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(0, s_iEvent_MGR_Test);
    Test__Expect_EQ(true, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));
    
    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(0, s_iEvent_MGR_Test);
    Test__Expect_EQ(true, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));

    Test__Expect_EQ(KTgS_OK, tgEM_TE_SEC_DEL( tiEM_TE_SEC_ID ));
    Test__Expect_EQ(false, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));



    /* Test behaviour after setting the start frame */
    s_iEvent_MGR_Test = 0;

    tiEM_TE_SEC_ID = tgEM_TE_SEC_NEW( EM_TE_SEC_Unit_Test, 0, tgGB_Query_Total_Time() + 10, tgGB_Query_Total_Time() + 12 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiEM_TE_SEC_ID.m_uiKI);
    Test__Expect_EQ(true, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));

    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(0, s_iEvent_MGR_Test);
    Test__Expect_EQ(true, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));

    Test__Expect_EQ(KTgS_OK, tgEM_TE_SEC_Set_Start_Time( tiEM_TE_SEC_ID, tgGB_Query_Total_Time() ));

    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(1, s_iEvent_MGR_Test);
    Test__Expect_EQ(true, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));
    
    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(2, s_iEvent_MGR_Test);
    Test__Expect_EQ(true, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));

    Test__Expect_EQ(KTgS_OK, tgEM_TE_SEC_DEL( tiEM_TE_SEC_ID ));
    Test__Expect_EQ(false, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__EM_TE_SEC_Set_End_Time ---------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__EM_TE_SEC_Set_End_Time )
{
    TgEM_TE_SEC_ID                      tiEM_TE_SEC_ID;

    /* Test behaviour without setting the end frame */
    s_iEvent_MGR_Test = 0;

    tiEM_TE_SEC_ID = tgEM_TE_SEC_NEW( EM_TE_SEC_Unit_Test, 0, tgGB_Query_Total_Time(), tgGB_Query_Total_Time() + 2 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiEM_TE_SEC_ID.m_uiKI);
    Test__Expect_EQ(true, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));

    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(1, s_iEvent_MGR_Test);
    Test__Expect_EQ(true, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));

    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(2, s_iEvent_MGR_Test);
    Test__Expect_EQ(false, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));
    


    /* Test behaviour after setting the end frame */
    s_iEvent_MGR_Test = 0;

    tiEM_TE_SEC_ID = tgEM_TE_SEC_NEW( EM_TE_SEC_Unit_Test, 0, tgGB_Query_Total_Time(), tgGB_Query_Total_Time() + 2 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiEM_TE_SEC_ID.m_uiKI);
    Test__Expect_EQ(true, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));

    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(1, s_iEvent_MGR_Test);
    Test__Expect_EQ(true, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));

    Test__Expect_EQ(KTgS_OK, tgEM_TE_SEC_Set_End_Time( tiEM_TE_SEC_ID, tgGB_Query_Total_Time() + 4 ));

    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(2, s_iEvent_MGR_Test);
    Test__Expect_EQ(true, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));
    
    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(3, s_iEvent_MGR_Test);
    Test__Expect_EQ(true, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));

    Test__Expect_EQ(KTgS_OK, tgEM_TE_SEC_DEL( tiEM_TE_SEC_ID ));
    Test__Expect_EQ(false, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__EM_TE_SEC_Set_Time_To_Live ------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__EM_TE_SEC_Set_Time_To_Live )
{
    TgEM_TE_SEC_ID                      tiEM_TE_SEC_ID;

    /* Test behaviour without setting the start frame */
    s_iEvent_MGR_Test = 0;

    tiEM_TE_SEC_ID = tgEM_TE_SEC_NEW( EM_TE_SEC_Unit_Test, 0, tgGB_Query_Total_Time(), tgGB_Query_Total_Time() + 2 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiEM_TE_SEC_ID.m_uiKI);
    Test__Expect_EQ(true, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));

    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(1, s_iEvent_MGR_Test);
    Test__Expect_EQ(true, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));

    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(2, s_iEvent_MGR_Test);
    Test__Expect_EQ(false, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));
    


    /* Test behaviour after setting the start frame without setting the start frame */
    s_iEvent_MGR_Test = 0;

    tiEM_TE_SEC_ID = tgEM_TE_SEC_NEW( EM_TE_SEC_Unit_Test, 0, tgGB_Query_Total_Time(), tgGB_Query_Total_Time() + 2 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiEM_TE_SEC_ID.m_uiKI);
    Test__Expect_EQ(true, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));

    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(1, s_iEvent_MGR_Test);
    Test__Expect_EQ(true, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));

    Test__Expect_EQ(KTgS_OK, tgEM_TE_SEC_Set_Time_To_Live( tiEM_TE_SEC_ID, 2 ));

    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(2, s_iEvent_MGR_Test);
    Test__Expect_EQ(true, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));
    
    tgGB_Inc_Frame_Time( 1.0F );
    tgEM_Update_MGR( tgGB_Query_Frame_Time() );
    while (!tgEM_Update_MGR_Is_Complete())
    {
        tgTR_Yield();
    };

    Test__Expect_EQ(3, s_iEvent_MGR_Test);
    Test__Expect_EQ(false, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__EM_TE_SEC_Query_Valid ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__EM_TE_SEC_Query_Valid )
{
    TgEM_TE_SEC_ID                      tiEM_TE_SEC_ID;

    tiEM_TE_SEC_ID = tgEM_TE_SEC_NEW( EM_TE_SEC_Unit_Test, 0, tgGB_Query_Total_Time(), tgGB_Query_Total_Time() + 1 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiEM_TE_SEC_ID.m_uiKI);
    Test__Expect_EQ(true, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));

    Test__Expect_EQ(KTgS_OK, tgEM_TE_SEC_DEL( tiEM_TE_SEC_ID ));
    Test__Expect_EQ(false, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__EM_TE_SEC_Query_Paused ---------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__EM_TE_SEC_Query_Paused )
{
    TgEM_TE_SEC_ID                      tiEM_TE_SEC_ID;
    TgBOOL                              bValue;

    tiEM_TE_SEC_ID = tgEM_TE_SEC_NEW( EM_TE_SEC_Unit_Test, 0, tgGB_Query_Total_Time(), tgGB_Query_Total_Time() + 1 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiEM_TE_SEC_ID.m_uiKI);
    Test__Expect_EQ(true, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));
    Test__Expect_EQ(KTgS_OK, tgEM_TE_SEC_Query_Paused( &bValue, tiEM_TE_SEC_ID ));

    Test__Expect_EQ(KTgS_OK, tgEM_TE_SEC_DEL( tiEM_TE_SEC_ID ));
    Test__Expect_EQ(false, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__EM_TE_SEC_Query_Start_Time ------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__EM_TE_SEC_Query_Start_Time )
{
    TgEM_TE_SEC_ID                      tiEM_TE_SEC_ID;
    TgFLOAT32                           fValue;

    tiEM_TE_SEC_ID = tgEM_TE_SEC_NEW( EM_TE_SEC_Unit_Test, 0, tgGB_Query_Total_Time(), tgGB_Query_Total_Time() + 1 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiEM_TE_SEC_ID.m_uiKI);
    Test__Expect_EQ(true, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));
    Test__Expect_EQ(KTgS_OK, tgEM_TE_SEC_Query_Start_Time( &fValue, tiEM_TE_SEC_ID ));

    Test__Expect_EQ(KTgS_OK, tgEM_TE_SEC_DEL( tiEM_TE_SEC_ID ));
    Test__Expect_EQ(false, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__EM_TE_SEC_Query_End_Time -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__EM_TE_SEC_Query_End_Time )
{
    TgEM_TE_SEC_ID                      tiEM_TE_SEC_ID;
    TgFLOAT32                           fValue;

    tiEM_TE_SEC_ID = tgEM_TE_SEC_NEW( EM_TE_SEC_Unit_Test, 0, tgGB_Query_Total_Time(), tgGB_Query_Total_Time() + 1 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiEM_TE_SEC_ID.m_uiKI);
    Test__Expect_EQ(true, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));
    Test__Expect_EQ(KTgS_OK, tgEM_TE_SEC_Query_End_Time( &fValue, tiEM_TE_SEC_ID ));

    Test__Expect_EQ(KTgS_OK, tgEM_TE_SEC_DEL( tiEM_TE_SEC_ID ));
    Test__Expect_EQ(false, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__EM_TE_SEC_Query_Time_To_Live ---------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__EM_TE_SEC_Query_Time_To_Live )
{
    TgEM_TE_SEC_ID                      tiEM_TE_SEC_ID;
    TgFLOAT32                           fValue;

    tiEM_TE_SEC_ID = tgEM_TE_SEC_NEW( EM_TE_SEC_Unit_Test, 0, tgGB_Query_Total_Time(), tgGB_Query_Total_Time() + 1 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiEM_TE_SEC_ID.m_uiKI);
    Test__Expect_EQ(true, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));
    Test__Expect_EQ(KTgS_OK, tgEM_TE_SEC_Query_Time_To_Live( &fValue, tiEM_TE_SEC_ID ));

    Test__Expect_EQ(KTgS_OK, tgEM_TE_SEC_DEL( tiEM_TE_SEC_ID ));
    Test__Expect_EQ(false, tgEM_TE_SEC_Query_Valid( tiEM_TE_SEC_ID ));

    TEST_END_METHOD( KTgS_OK );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

static TgNOTHROW TgVOID EM_TE_FRM_Unit_Test( TgUINT_PTR_C UNUSED_PARAM uiParam )
{
    ++s_iEvent_MGR_Test;
}

static TgNOTHROW TgVOID EM_TE_SEC_Unit_Test( TgUINT_PTR_C UNUSED_PARAM uiParam )
{
    ++s_iEvent_MGR_Test;
}
