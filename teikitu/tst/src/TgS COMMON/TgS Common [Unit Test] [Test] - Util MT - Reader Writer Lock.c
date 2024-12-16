/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common [Unit Test] [Test] - Util MT - Reader Writer Lock.c
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

TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__RW__Init );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__RW__Free );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__RW__Enter_Read_Wait_Yield );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__RW__Enter_Read_Wait_Spin );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__RW__Enter_Read );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__RW__Exit_Read );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__RW__Enter_Write_Wait_Yield );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__RW__Enter_Write_Wait_Spin );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__RW__Enter_Write );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__RW__Exit_Write );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_MT__RW__SLOW_THREAD );

#if TgCOMPILE__THREAD
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__RW_SN__Init );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__RW_SN__Free );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__RW_SN__Enter_Read_Yield_Block );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__RW_SN__Enter_Read_Spin_Block );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__RW_SN__Enter_Read_Yield );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__RW_SN__Enter_Read_Spin );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__RW_SN__Exit_Read_Yield );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__RW_SN__Exit_Read_Spin );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__RW_SN__Enter_Write_Yield_Block );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__RW_SN__Enter_Write_Spin_Block );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__RW_SN__Enter_Write_Yield );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__RW_SN__Enter_Write_Spin );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__RW_SN__Exit_Write_Yield );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__RW_SN__Exit_Write_Spin );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__RW_SN__SLOW_THREAD );

TEST_METHOD( UNIT_TEST__TEST__CM_UT_MT__RW_MX__Init );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_MT__RW_MX__Free );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_MT__RW_MX__Enter_Read_Block );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_MT__RW_MX__Enter_Read );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_MT__RW_MX__Exit_Read );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_MT__RW_MX__Enter_Write_Block );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_MT__RW_MX__Enter_Write );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_MT__RW_MX__Exit_Write );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_MT__RW_MX__SLOW_THREAD );

/*# TgCOMPILE__THREAD */
#endif




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
#if TgCOMPILE__THREAD

TEST_LOCAL TgNOTHROW TgUINT_F32
Thread_AM_RW_Read_Unit_Test(
    TgUINT_PTR_C );

TEST_LOCAL TgNOTHROW TgUINT_F32
Thread_AM_RW_Write_Unit_Test(
    TgUINT_PTR_C );

TEST_LOCAL TgNOTHROW TgUINT_F32
Thread_AM_RW_Command_Unit_Test(
    TgUINT_PTR_C );

TEST_LOCAL TgNOTHROW TgUINT_F32
Thread_SN_RW_Read_Unit_Test(
    TgUINT_PTR_C );

TEST_LOCAL TgNOTHROW TgUINT_F32
Thread_SN_RW_Write_Unit_Test(
    TgUINT_PTR_C );

TEST_LOCAL TgNOTHROW TgUINT_F32
Thread_SN_RW_Command_Unit_Test( 
    TgUINT_PTR_C );

TEST_LOCAL TgNOTHROW TgUINT_F32
Thread_RW_Read_Unit_Test(
    TgUINT_PTR_C );

TEST_LOCAL TgNOTHROW TgUINT_F32
Thread_RW_Write_Unit_Test(
    TgUINT_PTR_C );

TEST_LOCAL TgNOTHROW TgUINT_F32
Thread_RW_Command_Unit_Test(
    TgUINT_PTR_C );

enum { KTgRWLOCK_NUM_COMMANDS_PER_THREAD    = 128,
       KTgRWLOCK_NUM_THREADS                = 16,
       KTgRWLOCK_COMMAND_SIZE               = KTgRWLOCK_NUM_THREADS*KTgRWLOCK_NUM_COMMANDS_PER_THREAD };

static STg1_MT_SM                           s_sTest_Count;
static STg2_UT_LF__RW                       s_sAM_RW;
static STg2_UT_LF_ISO__RW_SN                s_sRW_SN;
static STg2_UT_MT__RW_MX                    s_sRW;
static TgSINT_F32                           s_iCommand_Expected_Results[KTgRWLOCK_COMMAND_SIZE];
static TgUINT_F08                           s_uiCommand_List[KTgRWLOCK_COMMAND_SIZE];
static TgSINT_F32                           s_iCommand_Results[KTgRWLOCK_COMMAND_SIZE];
static TgSINT_F32_A                         s_niCommand_Read, s_niCommand_Execute;
static TgSINT_F32_A                         s_niCommand_Write;

/*# TgCOMPILE__THREAD */
#endif




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- UNIT_TEST__TEST__UTIL_MT_Reader_Writer_Lock ------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( UNIT_TEST__TEST__UTIL_MT_Reader_Writer_Lock )
{
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__RW__Init());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__RW__Free());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__RW__Enter_Read_Wait_Yield());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__RW__Enter_Read_Wait_Spin());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__RW__Enter_Read());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__RW__Exit_Read());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__RW__Enter_Write_Wait_Yield());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__RW__Enter_Write_Wait_Spin());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__RW__Enter_Write());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__RW__Exit_Write());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_MT__RW__SLOW_THREAD());

    #if TgCOMPILE__THREAD
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__RW_SN__Init());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__RW_SN__Free());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__RW_SN__Enter_Read_Yield_Block());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__RW_SN__Enter_Read_Spin_Block());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__RW_SN__Enter_Read_Yield());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__RW_SN__Enter_Read_Spin());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__RW_SN__Exit_Read_Yield());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__RW_SN__Exit_Read_Spin());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__RW_SN__Enter_Write_Yield_Block());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__RW_SN__Enter_Write_Spin_Block());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__RW_SN__Enter_Write_Yield());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__RW_SN__Enter_Write_Spin());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__RW_SN__Exit_Write_Yield());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__RW_SN__Exit_Write_Spin());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__RW_SN__SLOW_THREAD());

    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_MT__RW_MX__Init());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_MT__RW_MX__Free());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_MT__RW_MX__Enter_Read_Block());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_MT__RW_MX__Enter_Read());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_MT__RW_MX__Exit_Read());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_MT__RW_MX__Enter_Write_Block());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_MT__RW_MX__Enter_Write());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_MT__RW_MX__Exit_Write());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_MT__RW_MX__SLOW_THREAD());

    /*# TgCOMPILE__THREAD */
    #endif

    TEST_END_METHOD( KTgS_OK );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/* File Local Functions                                                                                                                                                            */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */


/* ---- UNIT_TEST__TEST__CM_UT_LF__RW__Init -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__RW__Init )
{
    STg2_UT_LF__RW                      sAM_RW;

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__RW__Init( &sAM_RW ));
    tgCM_UT_LF__RW__Free( &sAM_RW );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_LF__RW__Free -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__RW__Free )
{
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__RW__Init());
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_LF__RW__Enter_Read_Wait_Yield --------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__RW__Enter_Read_Wait_Yield )
{
    STg2_UT_LF__RW                      sAM_RW;

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__RW__Init( &sAM_RW ));

    tgCM_UT_LF__RW__Enter_Read_Wait_Yield( &sAM_RW );

    tgCM_UT_LF__RW__Exit_Read( &sAM_RW );
    tgCM_UT_LF__RW__Free( &sAM_RW );
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_LF__RW__Enter_Read_Wait_Spin ---------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__RW__Enter_Read_Wait_Spin )
{
    STg2_UT_LF__RW                      sAM_RW;

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__RW__Init( &sAM_RW ));

    tgCM_UT_LF__RW__Enter_Read_Wait_Spin( &sAM_RW );

    tgCM_UT_LF__RW__Exit_Read( &sAM_RW );
    tgCM_UT_LF__RW__Free( &sAM_RW );
    TEST_END_METHOD( KTgS_OK );

}


/* ---- UNIT_TEST__TEST__CM_UT_LF__RW__Enter_Read -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__RW__Enter_Read )
{
    STg2_UT_LF__RW                      sAM_RW;

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__RW__Init( &sAM_RW ));

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__RW__Enter_Read( &sAM_RW ));

    tgCM_UT_LF__RW__Exit_Read( &sAM_RW );
    tgCM_UT_LF__RW__Free( &sAM_RW );
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_LF__RW__Exit_Read --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__RW__Exit_Read )
{
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__RW__Enter_Read_Wait_Spin());
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_LF__RW__Enter_Write_Wait_Yield -------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__RW__Enter_Write_Wait_Yield )
{
    STg2_UT_LF__RW                      sAM_RW;

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__RW__Init( &sAM_RW ));

    tgCM_UT_LF__RW__Enter_Write_Wait_Yield( &sAM_RW );

    Test__Expect_NE(KTgS_OK, tgCM_UT_LF__RW__Enter_Read( &sAM_RW ));
    tgCM_UT_LF__RW__Exit_Write( &sAM_RW );
    tgCM_UT_LF__RW__Free( &sAM_RW );
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_LF__RW__Enter_Write_Wait_Spin --------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__RW__Enter_Write_Wait_Spin )
{
    STg2_UT_LF__RW                      sAM_RW;

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__RW__Init( &sAM_RW ));

    tgCM_UT_LF__RW__Enter_Write_Wait_Spin( &sAM_RW );

    Test__Expect_NE(KTgS_OK, tgCM_UT_LF__RW__Enter_Read( &sAM_RW ));
    tgCM_UT_LF__RW__Exit_Write( &sAM_RW );
    tgCM_UT_LF__RW__Free( &sAM_RW );
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_LF__RW__Enter_Write ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__RW__Enter_Write )
{
    STg2_UT_LF__RW                      sAM_RW;

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__RW__Init( &sAM_RW ));

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__RW__Enter_Write( &sAM_RW ));

    Test__Expect_NE(KTgS_OK, tgCM_UT_LF__RW__Enter_Read( &sAM_RW ));
    tgCM_UT_LF__RW__Exit_Write( &sAM_RW );
    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__RW__Enter_Read( &sAM_RW ));
    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__RW__Enter_Read( &sAM_RW ));

    Test__Expect_NE(KTgS_OK, tgCM_UT_LF__RW__Enter_Write( &sAM_RW ));

    tgCM_UT_LF__RW__Exit_Read( &sAM_RW );
    tgCM_UT_LF__RW__Exit_Read( &sAM_RW );

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__RW__Enter_Write( &sAM_RW ));

    tgCM_UT_LF__RW__Exit_Write( &sAM_RW );

    tgCM_UT_LF__RW__Free( &sAM_RW );
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_LF__RW__Exit_Write -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__RW__Exit_Write )
{
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__RW__Enter_Write_Wait_Spin());
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_MT__RW__SLOW_THREAD ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_MT__RW__SLOW_THREAD )
{
#if TgCOMPILE__THREAD
    TgTHREAD_ID                         tiThread[KTgRWLOCK_NUM_THREADS];
    TgSINT_F32                          iIndex;
    TgSINT_F32                          niCommand_Expected_Results;

    tgPM_MT_SM_Init( &s_sTest_Count, nullptr, 0, KTgRWLOCK_NUM_THREADS );
    niCommand_Expected_Results = 0;
    for (iIndex = 0; iIndex < KTgRWLOCK_COMMAND_SIZE; ++iIndex)
    {
        s_uiCommand_List[iIndex] = tgCM_RAND_U08() % 2u;
        if (0 == s_uiCommand_List[iIndex])
        {
            s_iCommand_Expected_Results[niCommand_Expected_Results] = iIndex;
            ++niCommand_Expected_Results;
        }
    }

    if (tgGB_CMD_Query_Argument_Index( u8"-slow" ) >= 0 || TgCOMPILE__SLOW_UNIT_TEST)
    {
        Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__RW__Init( &s_sAM_RW ));
        for (iIndex = 0; iIndex < (KTgRWLOCK_NUM_THREADS >> 1); ++iIndex)
        {
            tiThread[iIndex] = tgTR_Create( Thread_AM_RW_Read_Unit_Test, 0, 0, ETgTHREAD_PRIORITY__NORMAL, u8"Thread_AM_RW_Read_Unit_Test" );
            Test__Expect_NE(KTgID__INVALID_VALUE, tiThread[iIndex].m_uiKI);
        }
        for (; iIndex < KTgRWLOCK_NUM_THREADS; ++iIndex)
        {
            tiThread[iIndex] = tgTR_Create( Thread_AM_RW_Write_Unit_Test, 0, 0, ETgTHREAD_PRIORITY__NORMAL, u8"Thread_AM_RW_Write_Unit_Test" );
            Test__Expect_NE(KTgID__INVALID_VALUE, tiThread[iIndex].m_uiKI);
        }
        tgPM_MT_SM_Signal( &s_sTest_Count, KTgRWLOCK_NUM_THREADS );
        for (iIndex = 0; iIndex < KTgRWLOCK_NUM_THREADS; ++iIndex)
        {
            tgTR_Close( tiThread[iIndex] );
        }
        tgCM_UT_LF__RW__Free( &s_sAM_RW );

        Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__RW__Init( &s_sAM_RW ));
        atomic_store( &s_niCommand_Execute, 0 );
        atomic_store( &s_niCommand_Read, 0 );
        atomic_store( &s_niCommand_Write, 0 );
        for (iIndex = 0; iIndex < KTgRWLOCK_NUM_THREADS; ++iIndex)
        {
            tiThread[iIndex] = tgTR_Create( Thread_AM_RW_Command_Unit_Test, 0, 0, ETgTHREAD_PRIORITY__NORMAL, u8"Thread_AM_RW_Command_Unit_Test" );
            Test__Expect_NE(KTgID__INVALID_VALUE, tiThread[iIndex].m_uiKI);
        }
        tgPM_MT_SM_Signal( &s_sTest_Count, KTgRWLOCK_NUM_THREADS );
        for (iIndex = 0; iIndex < KTgRWLOCK_NUM_THREADS; ++iIndex)
        {
            tgTR_Close( tiThread[iIndex] );
        }
        tgCM_UT_LF__RW__Free( &s_sAM_RW );
        Test__Expect_EQ(true, niCommand_Expected_Results == atomic_load( &s_niCommand_Write ));
        for (iIndex = 0; iIndex < niCommand_Expected_Results; ++iIndex)
        {
            Test__Expect_EQ(true, s_iCommand_Results[iIndex] == s_iCommand_Expected_Results[iIndex]);
        }
    }

    tgPM_MT_SM_Free( &s_sTest_Count );
/*# TgCOMPILE__THREAD */
#endif

    TEST_END_METHOD( KTgS_OK );
}


#if TgCOMPILE__THREAD
/* ---- UNIT_TEST__TEST__CM_UT_LF__RW_SN__Init ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__RW_SN__Init )
{
    STg2_UT_LF_ISO__RW_SN               sRW_SN;

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__RW_SN__Init( &sRW_SN ));
    tgCM_UT_LF__RW_SN__Free( &sRW_SN );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_LF__RW_SN__Free ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__RW_SN__Free )
{
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__RW_SN__Init());
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_LF__RW_SN__Enter_Read_Yield_Block ----------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__RW_SN__Enter_Read_Yield_Block )
{
    STg2_UT_LF_ISO__RW_SN               sRW_SN;

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__RW_SN__Init( &sRW_SN ));

    tgCM_UT_LF__RW_SN__Enter_Read_Yield_Block( &sRW_SN );
    tgCM_UT_LF__RW_SN__Exit_Read_Yield( &sRW_SN );
    tgCM_UT_LF__RW_SN__Enter_Read_Yield_Block( &sRW_SN );
    tgCM_UT_LF__RW_SN__Exit_Read_Spin( &sRW_SN );

    tgCM_UT_LF__RW_SN__Free( &sRW_SN );
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_LF__RW_SN__Enter_Read_Spin_Block ------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__RW_SN__Enter_Read_Spin_Block )
{
    STg2_UT_LF_ISO__RW_SN               sRW_SN;

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__RW_SN__Init( &sRW_SN ));

    tgCM_UT_LF__RW_SN__Enter_Read_Spin_Block( &sRW_SN );
    tgCM_UT_LF__RW_SN__Exit_Read_Yield( &sRW_SN );
    tgCM_UT_LF__RW_SN__Enter_Read_Spin_Block( &sRW_SN );
    tgCM_UT_LF__RW_SN__Exit_Read_Spin( &sRW_SN );

    tgCM_UT_LF__RW_SN__Free( &sRW_SN );
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_LF__RW_SN__Enter_Read_Yield ----------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__RW_SN__Enter_Read_Yield )
{
    STg2_UT_LF_ISO__RW_SN               sRW_SN;

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__RW_SN__Init( &sRW_SN ));

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__RW_SN__Enter_Read_Yield( &sRW_SN ));
    tgCM_UT_LF__RW_SN__Exit_Read_Yield( &sRW_SN );
    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__RW_SN__Enter_Read_Spin( &sRW_SN ));
    tgCM_UT_LF__RW_SN__Exit_Read_Spin( &sRW_SN );

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__RW_SN__Enter_Read_Yield( &sRW_SN ));
    tgCM_UT_LF__RW_SN__Exit_Read_Yield( &sRW_SN );
    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__RW_SN__Enter_Read_Yield( &sRW_SN ));
    tgCM_UT_LF__RW_SN__Exit_Read_Spin( &sRW_SN );

    tgCM_UT_LF__RW_SN__Free( &sRW_SN );
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_LF__RW_SN__Enter_Read_Spin ------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__RW_SN__Enter_Read_Spin )
{
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__RW_SN__Enter_Read_Yield());
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_LF__RW_SN__Exit_Read_Yield ------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__RW_SN__Exit_Read_Yield )
{
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__RW_SN__Enter_Read_Yield_Block());
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_LF__RW_SN__Exit_Read_Spin ------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__RW_SN__Exit_Read_Spin )
{
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__RW_SN__Enter_Read_Spin_Block());
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_LF__RW_SN__Enter_Write_Yield_Block ---------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__RW_SN__Enter_Write_Yield_Block )
{
    STg2_UT_LF_ISO__RW_SN               sRW_SN;

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__RW_SN__Init( &sRW_SN ));

    tgCM_UT_LF__RW_SN__Enter_Write_Yield_Block( &sRW_SN );
    Test__Expect_NE(KTgS_OK, tgCM_UT_LF__RW_SN__Enter_Read_Spin( &sRW_SN ));
    tgCM_UT_LF__RW_SN__Exit_Write_Yield( &sRW_SN );
    tgCM_UT_LF__RW_SN__Enter_Write_Yield_Block( &sRW_SN );
    Test__Expect_NE(KTgS_OK, tgCM_UT_LF__RW_SN__Enter_Read_Spin( &sRW_SN ));
    tgCM_UT_LF__RW_SN__Exit_Write_Spin( &sRW_SN );

    tgCM_UT_LF__RW_SN__Free( &sRW_SN );
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_LF__RW_SN__Enter_Write_Spin_Block ----------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__RW_SN__Enter_Write_Spin_Block )
{
    STg2_UT_LF_ISO__RW_SN               sRW_SN;

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__RW_SN__Init( &sRW_SN ));

    tgCM_UT_LF__RW_SN__Enter_Write_Spin_Block( &sRW_SN );
    tgCM_UT_LF__RW_SN__Exit_Write_Yield( &sRW_SN );
    tgCM_UT_LF__RW_SN__Enter_Write_Spin_Block( &sRW_SN );
    tgCM_UT_LF__RW_SN__Exit_Write_Spin( &sRW_SN );

    tgCM_UT_LF__RW_SN__Free( &sRW_SN );
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_LF__RW_SN__Enter_Write_Yield ---------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__RW_SN__Enter_Write_Yield )
{
    STg2_UT_LF_ISO__RW_SN               sRW_SN;

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__RW_SN__Init( &sRW_SN ));

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__RW_SN__Enter_Write_Yield( &sRW_SN ));
    tgCM_UT_LF__RW_SN__Exit_Write_Yield( &sRW_SN );
    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__RW_SN__Enter_Write_Yield( &sRW_SN ));
    tgCM_UT_LF__RW_SN__Exit_Write_Spin( &sRW_SN );

    tgCM_UT_LF__RW_SN__Enter_Read_Yield_Block( &sRW_SN );
    tgCM_UT_LF__RW_SN__Enter_Read_Yield_Block( &sRW_SN );
    Test__Expect_NE(KTgS_OK, tgCM_UT_LF__RW_SN__Enter_Write_Yield( &sRW_SN ));
    tgCM_UT_LF__RW_SN__Exit_Read_Yield( &sRW_SN );
    tgCM_UT_LF__RW_SN__Exit_Read_Yield( &sRW_SN );
    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__RW_SN__Enter_Write_Yield( &sRW_SN ));
    tgCM_UT_LF__RW_SN__Exit_Write_Yield( &sRW_SN );

    tgCM_UT_LF__RW_SN__Free( &sRW_SN );
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_LF__RW_SN__Enter_Write_Spin ----------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__RW_SN__Enter_Write_Spin )
{
    STg2_UT_LF_ISO__RW_SN               sRW_SN;

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__RW_SN__Init( &sRW_SN ));

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__RW_SN__Enter_Write_Spin( &sRW_SN ));
    tgCM_UT_LF__RW_SN__Exit_Write_Yield( &sRW_SN );
    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__RW_SN__Enter_Write_Spin( &sRW_SN ));
    tgCM_UT_LF__RW_SN__Exit_Write_Spin( &sRW_SN );

    tgCM_UT_LF__RW_SN__Free( &sRW_SN );
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_LF__RW_SN__Exit_Write_Yield ----------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__RW_SN__Exit_Write_Yield )
{
    STg2_UT_LF_ISO__RW_SN               sRW_SN;

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__RW_SN__Init( &sRW_SN ));

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__RW_SN__Enter_Write_Spin( &sRW_SN ));
    Test__Expect_NE(KTgS_OK, tgCM_UT_LF__RW_SN__Enter_Write_Spin( &sRW_SN ));
    tgCM_UT_LF__RW_SN__Exit_Write_Yield( &sRW_SN );

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__RW_SN__Enter_Write_Spin( &sRW_SN ));
    tgCM_UT_LF__RW_SN__Exit_Write_Yield( &sRW_SN );

    tgCM_UT_LF__RW_SN__Free( &sRW_SN );
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_LF__RW_SN__Exit_Write_Spin ------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__RW_SN__Exit_Write_Spin )
{
    STg2_UT_LF_ISO__RW_SN               sRW_SN;

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__RW_SN__Init( &sRW_SN ));

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__RW_SN__Enter_Write_Spin( &sRW_SN ));
    Test__Expect_NE(KTgS_OK, tgCM_UT_LF__RW_SN__Enter_Write_Spin( &sRW_SN ));
    tgCM_UT_LF__RW_SN__Exit_Write_Spin( &sRW_SN );

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__RW_SN__Enter_Write_Spin( &sRW_SN ));
    tgCM_UT_LF__RW_SN__Exit_Write_Spin( &sRW_SN );

    tgCM_UT_LF__RW_SN__Free( &sRW_SN );
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_LF__RW_SN__SLOW_THREAD ---------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__RW_SN__SLOW_THREAD )
{
#if TgCOMPILE__THREAD
    TgTHREAD_ID                         tiThread[KTgRWLOCK_NUM_THREADS];
    TgSINT_F32                          iIndex;
    TgSINT_F32                          niCommand_Expected_Results;

    tgPM_MT_SM_Init( &s_sTest_Count, nullptr, 0, KTgRWLOCK_NUM_THREADS );
    niCommand_Expected_Results = 0;
    for (iIndex = 0; iIndex < KTgRWLOCK_COMMAND_SIZE; ++iIndex)
    {
        s_uiCommand_List[iIndex] = tgCM_RAND_U08() % 2u;
        if (0 == s_uiCommand_List[iIndex])
        {
            s_iCommand_Expected_Results[niCommand_Expected_Results] = iIndex;
            ++niCommand_Expected_Results;
        }
    }

    if (tgGB_CMD_Query_Argument_Index( u8"-slow" ) >= 0 || TgCOMPILE__SLOW_UNIT_TEST)
    {
        Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__RW_SN__Init( &s_sRW_SN ));
        for (iIndex = 0; iIndex < (KTgRWLOCK_NUM_THREADS >> 1); ++iIndex)
        {
            tiThread[iIndex] = tgTR_Create( Thread_SN_RW_Read_Unit_Test, 0, 0, ETgTHREAD_PRIORITY__NORMAL, u8"Thread_SN_RW_Read_Unit_Test" );
            Test__Expect_NE(KTgID__INVALID_VALUE, tiThread[iIndex].m_uiKI);
        }
        for (; iIndex < KTgRWLOCK_NUM_THREADS; ++iIndex)
        {
            tiThread[iIndex] = tgTR_Create( Thread_SN_RW_Write_Unit_Test, 0, 0, ETgTHREAD_PRIORITY__NORMAL, u8"Thread_SN_RW_Write_Unit_Test" );
            Test__Expect_NE(KTgID__INVALID_VALUE, tiThread[iIndex].m_uiKI);
        }
        tgPM_MT_SM_Signal( &s_sTest_Count, KTgRWLOCK_NUM_THREADS );
        for (iIndex = 0; iIndex < KTgRWLOCK_NUM_THREADS; ++iIndex)
        {
            tgTR_Close( tiThread[iIndex] );
        }
        tgCM_UT_LF__RW_SN__Free( &s_sRW_SN );

        Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__RW_SN__Init( &s_sRW_SN ));
        atomic_store( &s_niCommand_Execute, 0 );
        atomic_store( &s_niCommand_Read, 0 );
        atomic_store( &s_niCommand_Write, 0 );
        for (iIndex = 0; iIndex < KTgRWLOCK_NUM_THREADS; ++iIndex)
        {
            tiThread[iIndex] = tgTR_Create( Thread_SN_RW_Command_Unit_Test, 0, 0, ETgTHREAD_PRIORITY__NORMAL, u8"Thread_SN_RW_Command_Unit_Test" );
            Test__Expect_NE(KTgID__INVALID_VALUE, tiThread[iIndex].m_uiKI);
        }
        tgPM_MT_SM_Signal( &s_sTest_Count, KTgRWLOCK_NUM_THREADS );
        for (iIndex = 0; iIndex < KTgRWLOCK_NUM_THREADS; ++iIndex)
        {
            tgTR_Close( tiThread[iIndex] );
        }
        tgCM_UT_LF__RW_SN__Free( &s_sRW_SN );
        Test__Expect_EQ(true, niCommand_Expected_Results == atomic_load( &s_niCommand_Write ));
        for (iIndex = 0; iIndex < niCommand_Expected_Results; ++iIndex)
        {
            Test__Expect_EQ(true, s_iCommand_Results[iIndex] == s_iCommand_Expected_Results[iIndex]);
        }
    }

    tgPM_MT_SM_Free( &s_sTest_Count );
/*# TgCOMPILE__THREAD */
#endif

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_MT__RW_MX__Init ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_MT__RW_MX__Init )
{
    STg2_UT_MT__RW_MX                   sRW;

    Test__Expect_EQ(KTgS_OK, tgCM_UT_MT__RW_MX__Init( &sRW ));
    tgCM_UT_MT__RW_MX__Free( &sRW );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_MT__RW_MX__Free ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_MT__RW_MX__Free )
{
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_MT__RW_MX__Init());
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_MT__RW_MX__Enter_Read_Block ----------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_MT__RW_MX__Enter_Read_Block )
{
    STg2_UT_MT__RW_MX                   sRW;

    Test__Expect_EQ(KTgS_OK, tgCM_UT_MT__RW_MX__Init( &sRW ));

    tgCM_UT_MT__RW_MX__Enter_Read_Block( &sRW );
    tgCM_UT_MT__RW_MX__Exit_Read( &sRW );

    tgCM_UT_MT__RW_MX__Free( &sRW );
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_MT__RW_MX__Enter_Read ----------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_MT__RW_MX__Enter_Read )
{
    STg2_UT_MT__RW_MX                   sRW;

    Test__Expect_EQ(KTgS_OK, tgCM_UT_MT__RW_MX__Init( &sRW ));

    Test__Expect_EQ(KTgS_OK, tgCM_UT_MT__RW_MX__Enter_Read( &sRW ));
    tgCM_UT_MT__RW_MX__Exit_Read( &sRW );

    tgCM_UT_MT__RW_MX__Free( &sRW );
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_MT__RW_MX__Exit_Read ------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_MT__RW_MX__Exit_Read )
{
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_MT__RW_MX__Enter_Read_Block());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_MT__RW_MX__Enter_Read());
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_MT__RW_MX__Enter_Write_Block ---------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_MT__RW_MX__Enter_Write_Block )
{
    STg2_UT_MT__RW_MX                   sRW;

    Test__Expect_EQ(KTgS_OK, tgCM_UT_MT__RW_MX__Init( &sRW ));

    tgCM_UT_MT__RW_MX__Enter_Write_Block( &sRW );
    tgCM_UT_MT__RW_MX__Exit_Write( &sRW );

    tgCM_UT_MT__RW_MX__Free( &sRW );
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_MT__RW_MX__Enter_Write ---------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_MT__RW_MX__Enter_Write )
{
    STg2_UT_MT__RW_MX                   sRW;

    Test__Expect_EQ(KTgS_OK, tgCM_UT_MT__RW_MX__Init( &sRW ));

    Test__Expect_EQ(KTgS_OK, tgCM_UT_MT__RW_MX__Enter_Write( &sRW ));
    tgCM_UT_MT__RW_MX__Exit_Write( &sRW );

    tgCM_UT_MT__RW_MX__Free( &sRW );
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_MT__RW_MX__Exit_Write ----------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_MT__RW_MX__Exit_Write )
{
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_MT__RW_MX__Enter_Write_Block());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_MT__RW_MX__Enter_Write());
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_MT__RW_MX__SLOW_THREAD ---------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_MT__RW_MX__SLOW_THREAD )
{
#if TgCOMPILE__THREAD
    TgTHREAD_ID                         tiThread[KTgRWLOCK_NUM_THREADS];
    TgSINT_F32                          iIndex;
    TgSINT_F32                          niCommand_Expected_Results;

    tgPM_MT_SM_Init( &s_sTest_Count, nullptr, 0, KTgRWLOCK_NUM_THREADS );
    niCommand_Expected_Results = 0;
    for (iIndex = 0; iIndex < KTgRWLOCK_COMMAND_SIZE; ++iIndex)
    {
        s_uiCommand_List[iIndex] = tgCM_RAND_U08() % 2u;
        if (0 == s_uiCommand_List[iIndex])
        {
            s_iCommand_Expected_Results[niCommand_Expected_Results] = iIndex;
            ++niCommand_Expected_Results;
        }
    }

    if (tgGB_CMD_Query_Argument_Index( u8"-slow" ) >= 0 || TgCOMPILE__SLOW_UNIT_TEST)
    {
        Test__Expect_EQ(KTgS_OK, tgCM_UT_MT__RW_MX__Init( &s_sRW ));
        for (iIndex = 0; iIndex < (KTgRWLOCK_NUM_THREADS >> 1); ++iIndex)
        {
            tiThread[iIndex] = tgTR_Create( Thread_RW_Read_Unit_Test, 0, 0, ETgTHREAD_PRIORITY__NORMAL, u8"Thread_RW_Read_Unit_Test" );
            Test__Expect_NE(KTgID__INVALID_VALUE, tiThread[iIndex].m_uiKI);
        }
        for (; iIndex < KTgRWLOCK_NUM_THREADS; ++iIndex)
        {
            tiThread[iIndex] = tgTR_Create( Thread_RW_Write_Unit_Test, 0, 0, ETgTHREAD_PRIORITY__NORMAL, u8"Thread_RW_Write_Unit_Test" );
            Test__Expect_NE(KTgID__INVALID_VALUE, tiThread[iIndex].m_uiKI);
        }
        tgPM_MT_SM_Signal( &s_sTest_Count, KTgRWLOCK_NUM_THREADS );
        for (iIndex = 0; iIndex < KTgRWLOCK_NUM_THREADS; ++iIndex)
        {
            tgTR_Close( tiThread[iIndex] );
        }
        tgCM_UT_MT__RW_MX__Free( &s_sRW );

        Test__Expect_EQ(KTgS_OK, tgCM_UT_MT__RW_MX__Init( &s_sRW ));
        atomic_store( &s_niCommand_Execute, 0 );
        atomic_store( &s_niCommand_Read, 0 );
        atomic_store( &s_niCommand_Write, 0 );
        for (iIndex = 0; iIndex < KTgRWLOCK_NUM_THREADS; ++iIndex)
        {
            tiThread[iIndex] = tgTR_Create( Thread_RW_Command_Unit_Test, 0, 0, ETgTHREAD_PRIORITY__NORMAL, u8"Thread_RW_Command_Unit_Test" );
            Test__Expect_NE(KTgID__INVALID_VALUE, tiThread[iIndex].m_uiKI);
        }
        tgPM_MT_SM_Signal( &s_sTest_Count, KTgRWLOCK_NUM_THREADS );
        for (iIndex = 0; iIndex < KTgRWLOCK_NUM_THREADS; ++iIndex)
        {
            tgTR_Close( tiThread[iIndex] );
        }
        tgCM_UT_MT__RW_MX__Free( &s_sRW );
        Test__Expect_EQ(true, niCommand_Expected_Results == atomic_load( &s_niCommand_Write ));
        for (iIndex = 0; iIndex < niCommand_Expected_Results; ++iIndex)
        {
            Test__Expect_EQ(true, s_iCommand_Results[iIndex] == s_iCommand_Expected_Results[iIndex]);
        }
    }

    tgPM_MT_SM_Free( &s_sTest_Count );
/*# TgCOMPILE__THREAD */
#endif

    TEST_END_METHOD( KTgS_OK );
}


/*# TgCOMPILE__THREAD */
 #endif




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
#if TgCOMPILE__THREAD

/* ---- Thread_AM_RW_Read_Unit_Test ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_LOCAL TgNOTHROW TgUINT_F32 Thread_AM_RW_Read_Unit_Test( TgUINT_PTR_C UNUSED_PARAM uiUnused )
{
    TgSINT_F32                          iIndex;

    tgPM_MT_SM_Wait_Block( &s_sTest_Count );

    for (iIndex = 0; iIndex < 200; ++iIndex)
    {
        tgCM_UT_LF__RW__Enter_Read_Wait_Yield( &s_sAM_RW );
        Unit_Test__Sleep( tgCM_RAND_U64() % 30000 );
        tgCM_UT_LF__RW__Exit_Read( &s_sAM_RW );
        Unit_Test__Sleep( 00000 + (tgCM_RAND_U64() % 20000) );

        tgCM_UT_LF__RW__Enter_Read_Wait_Spin( &s_sAM_RW );
        Unit_Test__Sleep( tgCM_RAND_U64() % 30000 );
        tgCM_UT_LF__RW__Exit_Read( &s_sAM_RW );
        Unit_Test__Sleep( 10000 + (tgCM_RAND_U64() % 20000) );
    }
    return (0);
}


/* ---- Thread_AM_RW_Write_Unit_Test --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_LOCAL TgNOTHROW TgUINT_F32 Thread_AM_RW_Write_Unit_Test( TgUINT_PTR_C UNUSED_PARAM uiUnused )
{
    TgSINT_F32                          iIndex;

    tgPM_MT_SM_Wait_Block( &s_sTest_Count );

    for (iIndex = 0; iIndex < 50; ++iIndex)
    {
        tgCM_UT_LF__RW__Enter_Write_Wait_Yield( &s_sAM_RW );
        Unit_Test__Sleep( 10000 + (tgCM_RAND_U64() % 50000) );
        tgCM_UT_LF__RW__Exit_Write( &s_sAM_RW );
        Unit_Test__Sleep( 10000 + (tgCM_RAND_U64() % 30000) );

        tgCM_UT_LF__RW__Enter_Write_Wait_Spin( &s_sAM_RW );
        Unit_Test__Sleep( 10000 + (tgCM_RAND_U64() % 50000) );
        tgCM_UT_LF__RW__Exit_Write( &s_sAM_RW );
        Unit_Test__Sleep( 10000 + (tgCM_RAND_U64() % 30000) );
    }
    return (0);
}


/* ---- Thread_AM_RW_Command_Unit_Test ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_LOCAL TgNOTHROW TgUINT_F32 Thread_AM_RW_Command_Unit_Test( TgUINT_PTR_C UNUSED_PARAM uiUnused )
{
    TgSINT_F32                          iIndex;
    TgSINT_F32                          niWrite;
    TgSINT_F32                          niCommand;
    TgUINT_F08                          iCommand;

    tgPM_MT_SM_Wait_Block( &s_sTest_Count );

    for (iIndex = 0; iIndex < KTgRWLOCK_NUM_COMMANDS_PER_THREAD; ++iIndex)
    {
        niCommand = atomic_fetch_add( &s_niCommand_Read, 1 );
        iCommand = s_uiCommand_List[niCommand % KTgRWLOCK_COMMAND_SIZE];

        while (atomic_load( &s_niCommand_Execute ) != niCommand)
        {
            tgTR_Pause();
        };

        switch (iCommand % 2)
        {
            case 1:
                tgCM_UT_LF__RW__Enter_Read_Wait_Yield( &s_sAM_RW );
                atomic_fetch_add( &s_niCommand_Execute, 1 );
                Unit_Test__Sleep( tgCM_RAND_U64() % 30000 );
                tgCM_UT_LF__RW__Exit_Read( &s_sAM_RW );
                break;

            case 0:
                tgCM_UT_LF__RW__Enter_Write_Wait_Yield( &s_sAM_RW );
                atomic_fetch_add( &s_niCommand_Execute, 1 );
                niWrite = atomic_fetch_add( &s_niCommand_Write, 1 );
                s_iCommand_Results[niWrite] = niCommand;
                Unit_Test__Sleep( 10000 + (tgCM_RAND_U64() % 50000) );
                tgCM_UT_LF__RW__Exit_Write( &s_sAM_RW );
                break;

            default:
                TgS_NO_DEFAULT( break );
        };
    }
    return (0);
}


/* ---- Thread_SN_RW_Read_Unit_Test ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_LOCAL TgNOTHROW TgUINT_F32 Thread_SN_RW_Read_Unit_Test( TgUINT_PTR_C UNUSED_PARAM uiUnused )
{
    TgSINT_F32                          iIndex;

    tgPM_MT_SM_Wait_Block( &s_sTest_Count );

    for (iIndex = 0; iIndex < 200; ++iIndex)
    {
        tgCM_UT_LF__RW_SN__Enter_Read_Yield_Block( &s_sRW_SN );
        Unit_Test__Sleep( tgCM_RAND_U64() % 30000 );
        tgCM_UT_LF__RW_SN__Exit_Read_Yield( &s_sRW_SN );
        Unit_Test__Sleep( 10000 + (tgCM_RAND_U64() % 20000) );

        tgCM_UT_LF__RW_SN__Enter_Read_Spin_Block( &s_sRW_SN );
        Unit_Test__Sleep( tgCM_RAND_U64() % 30000 );
        tgCM_UT_LF__RW_SN__Exit_Read_Spin( &s_sRW_SN );
        Unit_Test__Sleep( 10000 + (tgCM_RAND_U64() % 20000) );
    }
    return (0);
}


/* ---- Thread_SN_RW_Write_Unit_Test --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_LOCAL TgNOTHROW TgUINT_F32 Thread_SN_RW_Write_Unit_Test( TgUINT_PTR_C UNUSED_PARAM uiUnused )
{
    TgSINT_F32                          iIndex;

    tgPM_MT_SM_Wait_Block( &s_sTest_Count );

    for (iIndex = 0; iIndex < 50; ++iIndex)
    {
        tgCM_UT_LF__RW_SN__Enter_Write_Yield_Block( &s_sRW_SN );
        Unit_Test__Sleep( 10000 + (tgCM_RAND_U64() % 50000) );
        tgCM_UT_LF__RW_SN__Exit_Write_Yield( &s_sRW_SN );
        Unit_Test__Sleep( 10000 + (tgCM_RAND_U64() % 30000) );

        tgCM_UT_LF__RW_SN__Enter_Write_Spin_Block( &s_sRW_SN );
        Unit_Test__Sleep( 10000 + (tgCM_RAND_U64() % 50000) );
        tgCM_UT_LF__RW_SN__Exit_Write_Spin( &s_sRW_SN );
        Unit_Test__Sleep( 10000 + (tgCM_RAND_U64() % 30000) );
    }
    return (0);
}


/* ---- Thread_SN_RW_Command_Unit_Test ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_LOCAL TgNOTHROW TgUINT_F32 Thread_SN_RW_Command_Unit_Test( TgUINT_PTR_C UNUSED_PARAM uiUnused )
{
    TgSINT_F32                          iIndex;
    TgSINT_F32                          niWrite;
    TgSINT_F32                          niCommand;
    TgUINT_F08                          iCommand;

    tgPM_MT_SM_Wait_Block( &s_sTest_Count );

    for (iIndex = 0; iIndex < KTgRWLOCK_NUM_COMMANDS_PER_THREAD; ++iIndex)
    {
        niCommand = atomic_fetch_add( &s_niCommand_Read, 1 );
        iCommand = s_uiCommand_List[niCommand % KTgRWLOCK_COMMAND_SIZE];

        while (atomic_load( &s_niCommand_Execute ) != niCommand)
        {
            tgTR_Pause();
        };

        switch (iCommand % 2)
        {
            case 1:
                tgCM_UT_LF__RW_SN__Enter_Read_Yield_Block( &s_sRW_SN );
                atomic_fetch_add( &s_niCommand_Execute, 1 );
                Unit_Test__Sleep( tgCM_RAND_U64() % 30000 );
                tgCM_UT_LF__RW_SN__Exit_Read_Yield( &s_sRW_SN );
                break;

            case 0:
                tgCM_UT_LF__RW_SN__Enter_Write_Yield_Block( &s_sRW_SN );
                atomic_fetch_add( &s_niCommand_Execute, 1 );
                niWrite = atomic_fetch_add( &s_niCommand_Write, 1 );
                s_iCommand_Results[niWrite] = niCommand;
                if (s_iCommand_Results[niWrite] != s_iCommand_Expected_Results[niWrite])
                    return (1);
                Unit_Test__Sleep( 10000 + (tgCM_RAND_U64() % 50000) );
                tgCM_UT_LF__RW_SN__Exit_Write_Yield( &s_sRW_SN );
                break;

            default:
                TgS_NO_DEFAULT( break );
        };
    }
    return (0);
}


/* ---- Thread_RW_Read_Unit_Test ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_LOCAL TgNOTHROW TgUINT_F32 Thread_RW_Read_Unit_Test( TgUINT_PTR_C UNUSED_PARAM uiUnused )
{
    TgSINT_F32                          iIndex;

    tgPM_MT_SM_Wait_Block( &s_sTest_Count );

    for (iIndex = 0; iIndex < 200; ++iIndex)
    {
        tgCM_UT_MT__RW_MX__Enter_Read_Block( &s_sRW );
        Unit_Test__Sleep( tgCM_RAND_U64() % 30000 );
        tgCM_UT_MT__RW_MX__Exit_Read( &s_sRW );
        Unit_Test__Sleep( 10000 + (tgCM_RAND_U64() % 30000) );
    }
    return (0);
}


/* ---- Thread_RW_Write_Unit_Test ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_LOCAL TgNOTHROW TgUINT_F32 Thread_RW_Write_Unit_Test( TgUINT_PTR_C UNUSED_PARAM uiUnused )
{
    TgSINT_F32                          iIndex;

    tgPM_MT_SM_Wait_Block( &s_sTest_Count );

    for (iIndex = 0; iIndex < 50; ++iIndex)
    {
        tgCM_UT_MT__RW_MX__Enter_Write_Block( &s_sRW );
        Unit_Test__Sleep( 10000 + (tgCM_RAND_U64() % 50000) );
        tgCM_UT_MT__RW_MX__Exit_Write( &s_sRW );
        Unit_Test__Sleep( 10000 + (tgCM_RAND_U64() % 50000) );
    }
    return (0);
}


/* ---- Thread_RW_Command_Unit_Test ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_LOCAL TgNOTHROW TgUINT_F32 Thread_RW_Command_Unit_Test( TgUINT_PTR_C UNUSED_PARAM uiUnused )
{
    TgSINT_F32                          iIndex;
    TgSINT_F32                          niWrite;
    TgSINT_F32                          niCommand;
    TgUINT_F08                          iCommand;

    tgPM_MT_SM_Wait_Block( &s_sTest_Count );

    for (iIndex = 0; iIndex < KTgRWLOCK_NUM_COMMANDS_PER_THREAD; ++iIndex)
    {
        niCommand = atomic_fetch_add( &s_niCommand_Read, 1 );
        iCommand = s_uiCommand_List[niCommand % KTgRWLOCK_COMMAND_SIZE];

        while (atomic_load( &s_niCommand_Execute ) != niCommand)
        {
            tgTR_Pause();
        };

        switch (iCommand % 2)
        {
            case 1:
                tgCM_UT_MT__RW_MX__Enter_Read_Block( &s_sRW );
                atomic_fetch_add( &s_niCommand_Execute, 1 );
                Unit_Test__Sleep( tgCM_RAND_U64() % 30000 );
                tgCM_UT_MT__RW_MX__Exit_Read( &s_sRW );
                break;

            case 0:
                tgCM_UT_MT__RW_MX__Enter_Write_Block( &s_sRW );
                atomic_fetch_add( &s_niCommand_Execute, 1 );
                niWrite = atomic_fetch_add( &s_niCommand_Write, 1 );
                s_iCommand_Results[niWrite] = niCommand;
                if (s_iCommand_Results[niWrite] != s_iCommand_Expected_Results[niWrite])
                    return (1);
                Unit_Test__Sleep( 10000 + (tgCM_RAND_U64() % 50000) );
                tgCM_UT_MT__RW_MX__Exit_Write( &s_sRW );
                break;

            default:
                TgS_NO_DEFAULT( break );
        };
    }
    return (0);
}

/*# TgCOMPILE__THREAD */
#endif
