/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common [Unit Test] [Test] - Console.c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

TgCLANG_WARN_SUPPRESS(alloca)
#define NULL nullptr


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TgEXTN TgVOID                       tgCN_Init_Unit_Test( TgVOID_PP, TgRSIZE_P);
TgEXTN TgVOID                       tgCN_Start_Unit_Test( TgVOID );
TgEXTN TgVOID                       tgCN_Stop_Unit_Test( STg2_Output_P );

TEST_METHOD( UNIT_TEST__TEST__CN_Init );
TEST_METHOD( UNIT_TEST__TEST__CN_Boot );
TEST_METHOD( UNIT_TEST__TEST__CN_Stop );
TEST_METHOD( UNIT_TEST__TEST__CN_Free );
TEST_METHOD( UNIT_TEST__TEST__CN_Update );
TEST_METHOD( UNIT_TEST__TEST__CN_Query_Init );
TEST_METHOD( UNIT_TEST__TEST__CN_Query_Boot );
TEST_METHOD( UNIT_TEST__TEST__CN_Query_Fixed_Memory );
TEST_METHOD( UNIT_TEST__TEST__CN_Print_Commands );

#if TgCOMPILE__CONSOLE
TEST_METHOD( UNIT_TEST__TEST__CN_Execute_Command );
TEST_METHOD( UNIT_TEST__TEST__CN_Attach_Output );
TEST_METHOD( UNIT_TEST__TEST__CN_Attach_Default_Break );
TEST_METHOD( UNIT_TEST__TEST__CN_Attach_Default_Abort );
TEST_METHOD( UNIT_TEST__TEST__CN_Remove_Output );
TEST_METHOD( UNIT_TEST__TEST__CN_Remove_Default_Break );
TEST_METHOD( UNIT_TEST__TEST__CN_Remove_Default_Abort );
TEST_METHOD( UNIT_TEST__TEST__CN_Set_Prefix );
TEST_METHOD( UNIT_TEST__TEST__CN_Set_UID_Filter );
TEST_METHOD( UNIT_TEST__TEST__CN_Set_Severity_Filter );
TEST_METHOD( UNIT_TEST__TEST__CN_Print );
TEST_METHOD( UNIT_TEST__TEST__CN_PrintF );
TEST_METHOD( UNIT_TEST__TEST__CN_UID_Print );
TEST_METHOD( UNIT_TEST__TEST__CN_UID_PrintF );
TEST_METHOD( UNIT_TEST__TEST__CN_Process_Input );
TEST_METHOD( UNIT_TEST__TEST__CN_Insert_Command_Function );
TEST_METHOD( UNIT_TEST__TEST__CN_Remove_Command_Function );
TEST_METHOD( UNIT_TEST__TEST__CN_Print_Command_Functions );
#endif

TEST_METHOD( UNIT_TEST__TEST__CN_Var_Load_Config );
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Save_Config );
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Query_Init );
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Query_Boot );
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Query_Fixed_Memory );
TEST_METHOD( UNIT_TEST__TEST__CN_Print_Command_Variables );

TEST_METHOD( UNIT_TEST__TEST__CN_Var_Init_Bool );
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Init_S08 );
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Init_S16 );
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Init_S32 );
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Init_S64 );
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Init_U08 );
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Init_U16 );
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Init_U32 );
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Init_U64 );
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Init_F32 );
TEST_METHOD( UNIT_TEST__TEST__CtgMH_Var_Init_F32_04_1 );
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Init_String );

TEST_METHOD( UNIT_TEST__TEST__CN_Var_Set_Bool );
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Set_S08 );
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Set_S16 );
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Set_S32 );
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Set_S64 );
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Set_U08 );
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Set_U16 );
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Set_U32 );
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Set_U64 );
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Set_F32 );
TEST_METHOD( UNIT_TEST__TEST__CtgMH_Var_Set_F32_04_1 );
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Set_String );

TEST_METHOD( UNIT_TEST__TEST__CN_Var_Query_Bool );
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Query_S08 );
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Query_S16 );
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Query_S32 );
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Query_S64 );
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Query_U08 );
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Query_U16 );
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Query_U32 );
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Query_U64 );
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Query_F32 );
TEST_METHOD( UNIT_TEST__TEST__CtgMH_Var_Query_F32_04_1 );
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Query_String );

TEST_METHOD( UNIT_TEST__TEST__CN_Var_Query_Id );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#if TgCOMPILE__CONSOLE
/* Global communication value use to indicate when the console test function has executed.  Made thread safe for fun. */
static TgSINT_E32_A                         g_xuiTestValue;


static TgVOID TEST__Console_Test_Function( TgATTRIBUTE_UNUSED TgUINT_E32_C nuiArg, TgATTRIBUTE_UNUSED TgCHAR_U8_CP pArgV[KTgMAX_CMD_LINE_COUNT] ) TgATTRIBUTE_NO_EXCEPT
{
    TgSTD_ATOMIC(fetch_add)( &g_xuiTestValue, 1 );
}
static TgVOID TEST__Console_Test_Other_Function(
    TgATTRIBUTE_UNUSED TgUINT_E32_C nuiArg, TgATTRIBUTE_UNUSED TgCHAR_U8_CP pArgV[KTgMAX_CMD_LINE_COUNT] ) TgATTRIBUTE_NO_EXCEPT
{
}
/*# TgCOMPILE__CONSOLE */
#endif




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- UNIT_TEST__TEST__COMMON_Console ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( UNIT_TEST__TEST__COMMON_Console )
{
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_Init());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_Boot());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_Stop());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_Free());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_Update());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_Query_Init());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_Query_Boot());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_Query_Fixed_Memory());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_Print_Commands());

    #if TgCOMPILE__CONSOLE
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_Execute_Command());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_Attach_Output());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_Attach_Default_Break());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_Attach_Default_Abort());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_Remove_Output());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_Remove_Default_Break());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_Remove_Default_Abort());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_Set_Prefix());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_Set_UID_Filter());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_Set_Severity_Filter());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_Print());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_PrintF());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_UID_Print());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_UID_PrintF());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_Process_Input());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_Insert_Command_Function());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_Remove_Command_Function());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_Print_Command_Functions());
    #endif

    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_Var_Load_Config());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_Var_Save_Config());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_Var_Query_Init());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_Var_Query_Boot());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_Var_Query_Fixed_Memory());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_Print_Command_Variables());

    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_Var_Init_Bool());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_Var_Init_S08());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_Var_Init_S16());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_Var_Init_S32());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_Var_Init_S64());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_Var_Init_U08());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_Var_Init_U16());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_Var_Init_U32());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_Var_Init_U64());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_Var_Init_F32());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CtgMH_Var_Init_F32_04_1());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_Var_Init_String());

    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_Var_Set_Bool());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_Var_Set_S08());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_Var_Set_S16());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_Var_Set_S32());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_Var_Set_S64());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_Var_Set_U08());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_Var_Set_U16());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_Var_Set_U32());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_Var_Set_U64());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_Var_Set_F32());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CtgMH_Var_Set_F32_04_1());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_Var_Set_String());

    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_Var_Query_Bool());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_Var_Query_S08());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_Var_Query_S16());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_Var_Query_S32());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_Var_Query_S64());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_Var_Query_U08());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_Var_Query_U16());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_Var_Query_U32());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_Var_Query_U64());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_Var_Query_F32());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CtgMH_Var_Query_F32_04_1());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_Var_Query_String());

    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CN_Var_Query_Id());

    TEST_END_METHOD( KTgS_OK );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- UNIT_TEST__TEST__CN_Init ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_Init )
{
    /* Due to their nature, module management functions can not be unit tested */

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CN_Boot ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_Boot )
{
    /* Due to their nature, module management functions can not be unit tested */

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CN_Stop ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_Stop )
{
    /* Due to their nature, module management functions can not be unit tested */

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CN_Free ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_Free )
{
    /* Due to their nature, module management functions can not be unit tested */

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CN_Update ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_Update )
{
    /* Due to their nature, module management functions can not be unit tested */

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CN_Query_Init ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_Query_Init )
{
    Test__Expect_EQ(true, tgCN_Query_Init());

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CN_Query_Boot ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_Query_Boot )
{
    Test__Expect_EQ(true, tgCN_Query_Boot());

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CN_Query_Fixed_Memory ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_Query_Fixed_Memory )
{
    tgCN_Query_Fixed_Memory();

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CN_Print_Commands --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_Print_Commands )
{
    TgCHAR_U8                           sOutput_Buffer[8192];
    STg2_Output_MEM                     sOutput;

    tgIO_OM__Open( &sOutput, (TgUINT_E08_P)sOutput_Buffer, sizeof( sOutput_Buffer ), nullptr );
    sOutput_Buffer[0] = 0;
    sOutput.m_nbyData_Current = 0;

    tgCN_Print_Commands( &sOutput.m_sOutput );

    tgIO_OM__Close( &sOutput.m_sOutput );

    TEST_END_METHOD( KTgS_OK );
}


#if TgCOMPILE__CONSOLE
/* ---- UNIT_TEST__TEST__CN_Execute_Command -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_Execute_Command )
{
    TgCHAR_U8                           szNameList[][8] = { u8"tst", u8"a", u8"aa", u8"aaa", u8"aaaa", u8"z", u8"zz", u8"zzz", u8"zzzz" };

    TgSTD_ATOMIC(store)( &g_xuiTestValue, 0 );

    Test__Expect_EQ(true, tgCN_Insert_Command_Function( szNameList[0], KTgMAX_RSIZE, TEST__Console_Test_Function, nullptr, KTgMAX_RSIZE ));
    Test__Expect_EQ(true, tgCN_Insert_Command_Function( szNameList[1], KTgMAX_RSIZE, TEST__Console_Test_Function, nullptr, KTgMAX_RSIZE ));

    /* Direct execution of the command */
    Test__Expect_EQ(true, tgCN_Execute_Command( szNameList[0], KTgMAX_RSIZE ));
    Test__Expect_EQ(1, TgSTD_ATOMIC(load)( &g_xuiTestValue ));

    Test__Expect_EQ(true, tgCN_Execute_Command( szNameList[1], KTgMAX_RSIZE ));
    Test__Expect_EQ(2, TgSTD_ATOMIC(load)( &g_xuiTestValue ));

    Test__Expect_EQ(true, tgCN_Remove_Command_Function( szNameList[1], KTgMAX_RSIZE ));
    Test__Expect_EQ(true, tgCN_Remove_Command_Function( szNameList[0], KTgMAX_RSIZE ));

    Test__Expect_EQ(false, tgCN_Execute_Command( szNameList[1], KTgMAX_RSIZE ));
    Test__Expect_EQ(2, TgSTD_ATOMIC(load)( &g_xuiTestValue ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CN_Attach_Output ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_Attach_Output )
{
    TgVOID_P                            pSrc;
    TgRSIZE                             uiSize;
    TgVOID_P                            pDest;
    TgCHAR_U8                           sOutput_Buffer[8192];
    STg2_Output_MEM                     sOutput;
    TgSINT_E08                          iRet;

    tgCN_Init_Unit_Test( &pSrc, &uiSize );
    TgALLOCA( TgUINT_E08 , uiSize, pDest );
    TgERROR( nullptr != pDest );
    tgMM_Copy( pDest, uiSize, pSrc, uiSize );
    tgCN_Start_Unit_Test();

    /* Create a memory base output object to be used when testing the console output systems */
    tgIO_OM__Open( &sOutput, (TgUINT_E08_P)sOutput_Buffer, sizeof( sOutput_Buffer ), nullptr );
    sOutput_Buffer[0] = 0;
    sOutput.m_nbyData_Current = 0;

    for (TgRSIZE uiIndex = 0; uiIndex < KTgCN_CHANEL_BITS; ++uiIndex)
    {
        TgUINT_E32_C                        uiChannel = 1u << (uiIndex + KTgCN_SEVERITY_BITS);
        TgRSIZE                             uiPrefix_Length = 0;

        /* We need to skip certain channels since they can be used for higher level testing logic in the unit test framework */
        if (
            KTgCN_CHANEL_MESSAGE == uiChannel ||
            KTgCN_CHANEL_WARNING == uiChannel ||
            KTgCN_CHANEL_ERROR == uiChannel ||
            KTgCN_CHANEL_CRITICAL == uiChannel)
        {
            continue;
        }

        /* Make sure that using console output does not modify the output buffer (possible side effect from previous iteration) */
        tgCN_UID_Print( KTgUID_NONE, uiChannel, u8"This is a test", KTgMAX_RSIZE );
        Test__Expect_EQ((TgCHAR_U8)0, sOutput_Buffer[0]);
        sOutput_Buffer[0] = 0;
        sOutput.m_nbyData_Current = 0;

        tgCN_Print( uiChannel, u8"This is a test", KTgMAX_RSIZE );
        Test__Expect_EQ((TgCHAR_U8)0, sOutput_Buffer[0]);
        sOutput_Buffer[0] = 0;
        sOutput.m_nbyData_Current = 0;

        /* Add the output object to the list and make sure it is used */
        tgCN_Attach_Output( uiChannel, &sOutput.m_sOutput );

        /* Determine the size of the prefix used for this channel */
        tgCN_UID_Print( KTgUID_NONE, uiChannel, u8"", KTgMAX_RSIZE );
        tgUSZ_Length_Count( &uiPrefix_Length, sOutput_Buffer, sizeof( sOutput_Buffer ) );
        sOutput_Buffer[0] = 0;
        sOutput.m_nbyData_Current = 0;

        /* Confirm that the system is outputting the expected text */
        tgCN_UID_Print( KTgUID_NONE, uiChannel, u8"This is a test", KTgMAX_RSIZE );
        Test__Expect_EQ(true, tgUSZ_CompareN( &iRet, sOutput_Buffer + uiPrefix_Length, KTgMAX_RSIZE, 0, u8"This is a test", KTgMAX_RSIZE, 0, 14 ) && (0 == iRet));
        sOutput_Buffer[0] = 0;
        sOutput.m_nbyData_Current = 0;

        tgCN_Print( uiChannel, u8"This is a test", KTgMAX_RSIZE );
        Test__Expect_EQ(true, tgUSZ_CompareN( &iRet, sOutput_Buffer + uiPrefix_Length, KTgMAX_RSIZE, 0, u8"This is a test", KTgMAX_RSIZE, 0, 14 ) && (0 == iRet));
        sOutput_Buffer[0] = 0;
        sOutput.m_nbyData_Current = 0;

        /* Remove the output object from the list and make sure its no longer being used */
        tgCN_Remove_Output( uiChannel, &sOutput.m_sOutput );

        tgCN_UID_Print( KTgUID_NONE, uiChannel, u8"This is a test", KTgMAX_RSIZE );
        Test__Expect_EQ((TgCHAR_U8)0, sOutput_Buffer[0]);
        sOutput_Buffer[0] = 0;
        sOutput.m_nbyData_Current = 0;

        tgCN_Print( uiChannel, u8"This is a test", KTgMAX_RSIZE );
        Test__Expect_EQ((TgCHAR_U8)0, sOutput_Buffer[0]);
        sOutput_Buffer[0] = 0;
        sOutput.m_nbyData_Current = 0;
    }

    tgCN_Remove_Output( KTgCN_CHANEL_USER, &sOutput.m_sOutput );
    tgIO_OM__Close( &sOutput.m_sOutput );

    tgCN_Stop_Unit_Test( (STg2_Output_P)pDest );
    TgFREEA( pDest );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CN_Attach_Default_Break --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_Attach_Default_Break )
{
    TgVOID_P                            pSrc;
    TgRSIZE                             uiSize;
    TgVOID_P                            pDest;

    tgCN_Init_Unit_Test( &pSrc, &uiSize );
    TgALLOCA( TgUINT_E08 , uiSize, pDest );
    TgERROR( nullptr != pDest );
    tgMM_Copy( pDest, uiSize, pSrc, uiSize );
    tgCN_Start_Unit_Test();

    for (TgRSIZE uiIndex = 0; uiIndex < KTgCN_CHANEL_BITS; ++uiIndex)
    {
        TgUINT_E32_C    uiChannel = 1u << (uiIndex + KTgCN_SEVERITY_BITS);

        /* We need to skip certain channels since they can be used for higher level testing logic in the unit test framework */
        if (
            KTgCN_CHANEL_MESSAGE == uiChannel ||
            KTgCN_CHANEL_WARNING == uiChannel ||
            KTgCN_CHANEL_ERROR == uiChannel ||
            KTgCN_CHANEL_CRITICAL == uiChannel)
        {
            continue;
        };

        /* Can't really test these as they would break execution (and we don't use exception handling) */
        tgCN_Attach_Default_Break( uiChannel );
        tgCN_Remove_Default_Break( uiChannel );
    };

    tgCN_Stop_Unit_Test( (STg2_Output_P)pDest );
    TgFREEA( pDest );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CN_Attach_Default_Abort --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_Attach_Default_Abort )
{
    TgVOID_P                            pSrc;
    TgRSIZE                             uiSize;
    TgVOID_P                            pDest;

    tgCN_Init_Unit_Test( &pSrc, &uiSize );
    TgALLOCA( TgUINT_E08 , uiSize, pDest );
    TgERROR( nullptr != pDest );
    tgMM_Copy( pDest, uiSize, pSrc, uiSize );
    tgCN_Start_Unit_Test();

    for (TgRSIZE uiIndex = 0; uiIndex < KTgCN_CHANEL_BITS; ++uiIndex)
    {
        TgUINT_E32_C    uiChannel = 1u << (uiIndex + KTgCN_SEVERITY_BITS);

        /* We need to skip certain channels since they can be used for higher level testing logic in the unit test framework */
        if (
            KTgCN_CHANEL_MESSAGE == uiChannel ||
            KTgCN_CHANEL_WARNING == uiChannel ||
            KTgCN_CHANEL_ERROR == uiChannel ||
            KTgCN_CHANEL_CRITICAL == uiChannel)
        {
            continue;
        };

        /* Can't really test these as they would break execution (and we don't use exception handling) */
        tgCN_Attach_Default_Abort( uiChannel );
        tgCN_Remove_Default_Abort( uiChannel );
    };

    tgCN_Stop_Unit_Test( (STg2_Output_P)pDest );
    TgFREEA( pDest );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CN_Remove_Output ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_Remove_Output )
{
    /* Tested in UNIT_TEST__TEST__CN_Attach_Output */

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CN_Remove_Default_Break --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_Remove_Default_Break )
{
    /* Tested in UNIT_TEST__TEST__CN_Attach_Default_Break */

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CN_Remove_Default_Abort --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_Remove_Default_Abort )
{
    /* Tested in UNIT_TEST__TEST__CN_Attach_Default_Abort */

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CN_Set_Prefix ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_Set_Prefix )
{
    TgCHAR_U8                           szNameList[][8] = { u8"tst", u8"a", u8"aa", u8"aaa", u8"aaaa", u8"z", u8"zz", u8"zzz", u8"zzzz" };
    TgVOID_P                            pSrc;
    TgRSIZE                             uiSize;
    TgVOID_P                            pDest;
    TgCHAR_U8                           sOutput_Buffer[8192];
    STg2_Output_MEM                     sOutput;
    TgSINT_E08                          iRet;

    tgCN_Init_Unit_Test( &pSrc, &uiSize );
    TgALLOCA( TgUINT_E08 , uiSize, pDest );
    TgERROR( nullptr != pDest );
    tgMM_Copy( pDest, uiSize, pSrc, uiSize );
    tgCN_Start_Unit_Test();

    /* Create a memory base output object to be used when testing the console output systems */
    tgIO_OM__Open( &sOutput, (TgUINT_E08_P)sOutput_Buffer, sizeof( sOutput_Buffer ), nullptr );
    tgCN_Attach_Output( KTgCN_CHANEL_USER, &sOutput.m_sOutput );
    sOutput_Buffer[0] = 0;
    sOutput.m_nbyData_Current = 0;

    /* Prefixes are only output after a new line character - flush the system to make sure the next output will have a prefix */
    sOutput_Buffer[0] = sOutput_Buffer[1] = 0x20;
    tgCN_UID_Print( KTgUID_NONE, KTgCN_CHANEL_USER, u8"\n", KTgMAX_RSIZE );
    Test__Expect_EQ((TgCHAR_U8)0x0A, sOutput_Buffer[0]);
    Test__Expect_EQ((TgCHAR_U8)0x20, sOutput_Buffer[1]);
    sOutput.m_nbyData_Current = 0;

    /* Validation check of a nullptr prefix */
    sOutput_Buffer[0] = sOutput_Buffer[1] = 0x20;
    tgCN_Set_Prefix( KTgCN_CHANEL_USER, nullptr, KTgMAX_RSIZE );
    tgCN_UID_Print( KTgUID_NONE, KTgCN_CHANEL_USER, u8"\n", KTgMAX_RSIZE );
    Test__Expect_EQ((TgCHAR_U8)0x0A, sOutput_Buffer[0]);
    Test__Expect_EQ((TgCHAR_U8)0x20, sOutput_Buffer[1]);
    sOutput_Buffer[0] = 0;
    sOutput.m_nbyData_Current = 0;

    /* Validation check of an empty prefix */
    sOutput_Buffer[0] = sOutput_Buffer[1] = 0x20;
    tgCN_Set_Prefix( KTgCN_CHANEL_USER, u8"", KTgMAX_RSIZE );
    tgCN_UID_Print( KTgUID_NONE, KTgCN_CHANEL_USER, u8"\n", KTgMAX_RSIZE );
    Test__Expect_EQ((TgCHAR_U8)0x0A, sOutput_Buffer[0]);
    Test__Expect_EQ((TgCHAR_U8)0x20, sOutput_Buffer[1]);
    sOutput_Buffer[0] = 0;
    sOutput.m_nbyData_Current = 0;

    /* Validation check of an non-trivial prefix */
    tgCN_Set_Prefix( KTgCN_CHANEL_USER, u8"TST", KTgMAX_RSIZE );

    /* Empty text should generate a prefix with no other text */
    tgCN_UID_Print( KTgUID_NONE, KTgCN_CHANEL_USER, u8"", KTgMAX_RSIZE );
    Test__Expect_EQ('\0', *sOutput_Buffer);

    /* Since there was no line feed termination, further output should append text (no prefix, same line) */
    tgCN_UID_Print( KTgUID_NONE, KTgCN_CHANEL_USER, u8"a\n", KTgMAX_RSIZE );
    Test__Expect_EQ(true, tgUSZ_CompareN( &iRet, sOutput_Buffer, KTgMAX_RSIZE, 0, u8"TSTa\n", KTgMAX_RSIZE, 0, 5 ) && (0 == iRet));

    /* Since we ended with a new line, this text should be on a new line, and with a prefix */
    tgCN_UID_Print( KTgUID_NONE, KTgCN_CHANEL_USER, szNameList[1], KTgMAX_RSIZE );
    Test__Expect_EQ(true, tgUSZ_CompareN( &iRet, sOutput_Buffer, KTgMAX_RSIZE, 0, u8"TSTa\nTSTa", KTgMAX_RSIZE, 0, 9 ) && (0 == iRet));

    /* Test concatenation of strings without prefix */
    tgCN_UID_Print( KTgUID_NONE, KTgCN_CHANEL_USER, u8"b", KTgMAX_RSIZE );
    Test__Expect_EQ(true, tgUSZ_CompareN( &iRet, sOutput_Buffer, KTgMAX_RSIZE, 0, u8"TSTa\nTSTab", KTgMAX_RSIZE, 0, 10 ) && (0 == iRet));
    tgCN_UID_Print( KTgUID_NONE, KTgCN_CHANEL_USER, u8"cd\nefg", KTgMAX_RSIZE );
    Test__Expect_EQ(true, tgUSZ_CompareN( &iRet, sOutput_Buffer, KTgMAX_RSIZE, 0, u8"TSTa\nTSTabcd\nTSTefg", KTgMAX_RSIZE, 0, 19 ) && (0 == iRet));

    sOutput_Buffer[0] = 0;
    sOutput.m_nbyData_Current = 0;

    /* Reset to defaults, and validate the reset */
    sOutput_Buffer[0] = sOutput_Buffer[1] = 0x20;
    tgCN_Set_Prefix( KTgCN_CHANEL_USER, nullptr, KTgMAX_RSIZE );
    tgCN_UID_Print( KTgUID_NONE, KTgCN_CHANEL_USER, u8"\n", KTgMAX_RSIZE );
    Test__Expect_EQ((TgCHAR_U8)0x0A, sOutput_Buffer[0]);
    Test__Expect_EQ((TgCHAR_U8)0x20, sOutput_Buffer[1]);
    sOutput_Buffer[0] = 0;
    sOutput.m_nbyData_Current = 0;

    tgCN_Remove_Output( KTgCN_CHANEL_USER, &sOutput.m_sOutput );
    tgIO_OM__Close( &sOutput.m_sOutput );

    tgCN_Stop_Unit_Test( (STg2_Output_P)pDest );
    TgFREEA( pDest );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CN_Set_UID_Filter --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_Set_UID_Filter )
{
    TgVOID_P                            pSrc;
    TgRSIZE                             uiSize;
    TgVOID_P                            pDest;
    TgCHAR_U8                           sOutput_Buffer[8192];
    STg2_Output_MEM                     sOutput;
    TgSINT_E08                          iRet;

    tgCN_Init_Unit_Test( &pSrc, &uiSize );
    TgALLOCA( TgUINT_E08 , uiSize, pDest );
    TgERROR( nullptr != pDest );
    tgMM_Copy( pDest, uiSize, pSrc, uiSize );
    tgCN_Start_Unit_Test();

    /* Create a memory base output object to be used when testing the console output systems */
    tgIO_OM__Open( &sOutput, (TgUINT_E08_P)sOutput_Buffer, sizeof( sOutput_Buffer ), nullptr );
    tgCN_Attach_Output( KTgCN_CHANEL_USER, &sOutput.m_sOutput );
    sOutput_Buffer[0] = 0;
    sOutput.m_nbyData_Current = 0;

    /* By default there is no literal filter, so a literal specific message is emitted */
    tgCN_UID_Print( KTgUID_STg2_Input, KTgCN_CHANEL_USER, u8"This is a test", KTgMAX_RSIZE );
    Test__Expect_EQ(true, tgUSZ_CompareN( &iRet, sOutput_Buffer, KTgMAX_RSIZE, 0, u8"This is a test", KTgMAX_RSIZE, 0, 14 ) && (0 == iRet));
    sOutput_Buffer[0] = 0;
    sOutput.m_nbyData_Current = 0;

    /* Set the literal filter (this is used to target specific systems) */
    tgCN_Set_UID_Filter( KTgCN_CHANEL_USER, KTgUID_STg2_Input );

    /* When the message literal matches the filter, the message is emitted */
    tgCN_UID_Print( KTgUID_STg2_Input, KTgCN_CHANEL_USER, u8"This is a test", KTgMAX_RSIZE );
    Test__Expect_EQ(true, tgUSZ_CompareN( &iRet, sOutput_Buffer, KTgMAX_RSIZE, 0, u8"This is a test", KTgMAX_RSIZE, 0, 14 ) && (0 == iRet));
    sOutput_Buffer[0] = 0;
    sOutput.m_nbyData_Current = 0;

    /* When the message literal does not match the filter, no text should be emitter (no side effects either) */
    tgCN_UID_Print( KTgUID_STg2_Output, KTgCN_CHANEL_USER, u8"This is a test", KTgMAX_RSIZE );
    Test__Expect_EQ((TgCHAR_U8)0, sOutput_Buffer[0]);
    sOutput_Buffer[0] = 0;
    sOutput.m_nbyData_Current = 0;

    /* Reset to defaults */
    tgCN_Set_UID_Filter( KTgCN_CHANEL_USER, KTgUID_NONE );
    sOutput_Buffer[0] = 0;
    sOutput.m_nbyData_Current = 0;

    tgCN_Remove_Output( KTgCN_CHANEL_USER, &sOutput.m_sOutput );
    tgIO_OM__Close( &sOutput.m_sOutput );

    tgCN_Stop_Unit_Test( (STg2_Output_P)pDest );
    TgFREEA( pDest );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CN_Set_Severity_Filter ---------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_Set_Severity_Filter )
{
    TgVOID_P                            pSrc;
    TgRSIZE                             uiSize;
    TgVOID_P                            pDest;
    TgCHAR_U8                           sOutput_Buffer[8192];
    STg2_Output_MEM                     sOutput;
    TgSINT_E08                          iRet;

    tgCN_Init_Unit_Test( &pSrc, &uiSize );
    TgALLOCA( TgUINT_E08 , uiSize, pDest );
    TgERROR( nullptr != pDest );
    tgMM_Copy( pDest, uiSize, pSrc, uiSize );
    tgCN_Start_Unit_Test();

    /* Create a memory base output object to be used when testing the console output systems */
    tgIO_OM__Open( &sOutput, (TgUINT_E08_P)sOutput_Buffer, sizeof( sOutput_Buffer ), nullptr );
    tgCN_Attach_Output( KTgCN_CHANEL_USER, &sOutput.m_sOutput );
    sOutput_Buffer[0] = 0;
    sOutput.m_nbyData_Current = 0;

    /* Only messages with a severity less than the filter are emitted */
    for (TgRSIZE uiIndex = 0; uiIndex < (1u << KTgCN_SEVERITY_BITS); ++uiIndex)
    {
        tgCN_Set_Severity_Filter( KTgCN_CHANEL_USER, (TgUINT_E32)uiIndex );

        for (TgRSIZE uiIndex2 = 0; uiIndex2 < (1u << KTgCN_SEVERITY_BITS); ++uiIndex2)
        {
            tgCN_UID_Print( KTgUID_NONE, (TgUINT_E32)(KTgCN_CHANEL_USER | uiIndex2), u8"This is a test", KTgMAX_RSIZE );
            Test__Expect_EQ(uiIndex > uiIndex2, TgSUCCEEDED(tgUSZ_CompareN( &iRet, sOutput_Buffer, KTgMAX_RSIZE, 0, u8"This is a test", KTgMAX_RSIZE, 0, 14 )) && (0 == iRet));
            Test__Expect_EQ(uiIndex <= uiIndex2, 0 == sOutput_Buffer[0]);
            sOutput_Buffer[0] = 0;
            sOutput.m_nbyData_Current = 0;
        };
    };

    /* Reset to defaults */
    sOutput_Buffer[0] = 0;
    sOutput.m_nbyData_Current = 0;

    tgCN_Remove_Output( KTgCN_CHANEL_USER, &sOutput.m_sOutput );
    tgIO_OM__Close( &sOutput.m_sOutput );

    tgCN_Stop_Unit_Test( (STg2_Output_P)pDest );
    TgFREEA( pDest );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CN_Print ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_Print )
{
    TgVOID_P                            pSrc;
    TgRSIZE                             uiSize;
    TgVOID_P                            pDest;
    TgCHAR_U8                           sOutput_Buffer[8192];
    STg2_Output_MEM                     sOutput;
    TgSINT_E08                          iRet;

    tgCN_Init_Unit_Test( &pSrc, &uiSize );
    TgALLOCA( TgUINT_E08 , uiSize, pDest );
    TgERROR( nullptr != pDest );
    tgMM_Copy( pDest, uiSize, pSrc, uiSize );
    tgCN_Start_Unit_Test();

    /* Create a memory base output object to be used when testing the console output systems */
    tgIO_OM__Open( &sOutput, (TgUINT_E08_P)sOutput_Buffer, sizeof( sOutput_Buffer ), nullptr );
    sOutput_Buffer[0] = 0;
    sOutput.m_nbyData_Current = 0;

    for (TgRSIZE uiIndex = 0; uiIndex < KTgCN_CHANEL_BITS; ++uiIndex)
    {
        TgUINT_E32_C                        uiChannel = 1u << (uiIndex + KTgCN_SEVERITY_BITS);
        TgRSIZE                             uiPrefix_Length = 0;

        /* We need to skip certain channels since they can be used for higher level testing logic in the unit test framework */
        if (
            KTgCN_CHANEL_MESSAGE == uiChannel ||
            KTgCN_CHANEL_WARNING == uiChannel ||
            KTgCN_CHANEL_ERROR == uiChannel ||
            KTgCN_CHANEL_CRITICAL == uiChannel)
        {
            continue;
        }

        /* Make sure that using console output does not modify the output buffer (possible side effect from previous iteration) */
        tgCN_Print( uiChannel, u8"This is a test", KTgMAX_RSIZE );
        Test__Expect_EQ((TgCHAR_U8)0, sOutput_Buffer[0]);
        sOutput_Buffer[0] = 0;
        sOutput.m_nbyData_Current = 0;

        /* Add the output object to the list and make sure it is used */
        tgCN_Attach_Output( uiChannel, &sOutput.m_sOutput );

        /* Confirm that the system is outputting the expected text */
        tgCN_Print( uiChannel, u8"This is a test", KTgMAX_RSIZE );
        Test__Expect_EQ(true, tgUSZ_CompareN( &iRet, sOutput_Buffer + uiPrefix_Length, KTgMAX_RSIZE, 0, u8"This is a test", KTgMAX_RSIZE, 0, 14 ) && (0 == iRet));
        sOutput_Buffer[0] = 0;
        sOutput.m_nbyData_Current = 0;

        /* Remove the output object from the list and make sure its no longer being used */
        tgCN_Remove_Output( uiChannel, &sOutput.m_sOutput );
    }

    tgIO_OM__Close( &sOutput.m_sOutput );

    tgCN_Stop_Unit_Test( (STg2_Output_P)pDest );
    TgFREEA( pDest );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CN_PrintF ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_PrintF )
{
    TgVOID_P                            pSrc;
    TgRSIZE                             uiSize;
    TgVOID_P                            pDest;
    TgCHAR_U8                           sOutput_Buffer[8192];
    STg2_Output_MEM                     sOutput;
    TgSINT_E08                          iRet;

    tgCN_Init_Unit_Test( &pSrc, &uiSize );
    TgALLOCA( TgUINT_E08 , uiSize, pDest );
    TgERROR( nullptr != pDest );
    tgMM_Copy( pDest, uiSize, pSrc, uiSize );
    tgCN_Start_Unit_Test();

    /* Create a memory base output object to be used when testing the console output systems */
    tgIO_OM__Open( &sOutput, (TgUINT_E08_P)sOutput_Buffer, sizeof( sOutput_Buffer ), nullptr );
    sOutput_Buffer[0] = 0;
    sOutput.m_nbyData_Current = 0;

    for (TgRSIZE uiIndex = 0; uiIndex < KTgCN_CHANEL_BITS; ++uiIndex)
    {
        TgUINT_E32_C                        uiChannel = 1u << (uiIndex + KTgCN_SEVERITY_BITS);
        TgRSIZE                             uiPrefix_Length = 0;

        /* We need to skip certain channels since they can be used for higher level testing logic in the unit test framework */
        if (
            KTgCN_CHANEL_MESSAGE == uiChannel ||
            KTgCN_CHANEL_WARNING == uiChannel ||
            KTgCN_CHANEL_ERROR == uiChannel ||
            KTgCN_CHANEL_CRITICAL == uiChannel)
        {
            continue;
        }

        /* Make sure that using console output does not modify the output buffer (possible side effect from previous iteration) */
        tgCN_PrintF( uiChannel, u8"%s", u8"This is a test", KTgMAX_RSIZE );
        Test__Expect_EQ((TgCHAR_U8)0, sOutput_Buffer[0]);
        sOutput_Buffer[0] = 0;
        sOutput.m_nbyData_Current = 0;

        /* Add the output object to the list and make sure it is used */
        tgCN_Attach_Output( uiChannel, &sOutput.m_sOutput );

        /* Confirm that the system is outputting the expected text */
        tgCN_PrintF( uiChannel, u8"%s", u8"This is a test" );
        Test__Expect_EQ(true, tgUSZ_CompareN( &iRet, sOutput_Buffer + uiPrefix_Length, KTgMAX_RSIZE, 0, u8"This is a test", KTgMAX_RSIZE, 0, 14 ) && (0 == iRet));
        sOutput_Buffer[0] = 0;
        sOutput.m_nbyData_Current = 0;

        /* Remove the output object from the list and make sure its no longer being used */
        tgCN_Remove_Output( uiChannel, &sOutput.m_sOutput );
    }

    tgIO_OM__Close( &sOutput.m_sOutput );

    tgCN_Stop_Unit_Test( (STg2_Output_P)pDest );
    TgFREEA( pDest );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CN_UID_Print -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_UID_Print )
{
    TgVOID_P                            pSrc;
    TgRSIZE                             uiSize;
    TgVOID_P                            pDest;
    TgCHAR_U8                           sOutput_Buffer[8192];
    STg2_Output_MEM                     sOutput;
    TgSINT_E08                          iRet;

    tgCN_Init_Unit_Test( &pSrc, &uiSize );
    TgALLOCA( TgUINT_E08 , uiSize, pDest );
    TgERROR( nullptr != pDest );
    tgMM_Copy( pDest, uiSize, pSrc, uiSize );
    tgCN_Start_Unit_Test();

    /* Create a memory base output object to be used when testing the console output systems */
    tgIO_OM__Open( &sOutput, (TgUINT_E08_P)sOutput_Buffer, sizeof( sOutput_Buffer ), nullptr );
    sOutput_Buffer[0] = 0;
    sOutput.m_nbyData_Current = 0;

    for (TgRSIZE uiIndex = 0; uiIndex < KTgCN_CHANEL_BITS; ++uiIndex)
    {
        TgUINT_E32_C                        uiChannel = 1u << (uiIndex + KTgCN_SEVERITY_BITS);
        TgRSIZE                             uiPrefix_Length = 0;

        /* We need to skip certain channels since they can be used for higher level testing logic in the unit test framework */
        if (
            KTgCN_CHANEL_MESSAGE == uiChannel ||
            KTgCN_CHANEL_WARNING == uiChannel ||
            KTgCN_CHANEL_ERROR == uiChannel ||
            KTgCN_CHANEL_CRITICAL == uiChannel)
        {
            continue;
        }

        /* Make sure that using console output does not modify the output buffer (possible side effect from previous iteration) */
        tgCN_UID_Print( KTgUID_NONE, uiChannel, u8"This is a test", KTgMAX_RSIZE );
        Test__Expect_EQ((TgCHAR_U8)0, sOutput_Buffer[0]);
        sOutput_Buffer[0] = 0;
        sOutput.m_nbyData_Current = 0;

        /* Add the output object to the list and make sure it is used */
        tgCN_Attach_Output( uiChannel, &sOutput.m_sOutput );

        /* Determine the size of the prefix used for this channel */
        tgCN_UID_Print( KTgUID_NONE, uiChannel, u8"", KTgMAX_RSIZE );
        tgUSZ_Length_Count( &uiPrefix_Length, sOutput_Buffer, sizeof( sOutput_Buffer ) );
        sOutput_Buffer[0] = 0;
        sOutput.m_nbyData_Current = 0;

        /* Confirm that the system is outputting the expected text */
        tgCN_UID_Print( KTgUID_NONE, uiChannel, u8"This is a test", KTgMAX_RSIZE );
        Test__Expect_EQ(true, tgUSZ_CompareN( &iRet, sOutput_Buffer + uiPrefix_Length, KTgMAX_RSIZE, 0, u8"This is a test", KTgMAX_RSIZE, 0, 14 ) && (0 == iRet));
        sOutput_Buffer[0] = 0;
        sOutput.m_nbyData_Current = 0;


        /* Remove the output object from the list and make sure its no longer being used */
        tgCN_Remove_Output( uiChannel, &sOutput.m_sOutput );
        tgCN_UID_Print( KTgUID_NONE, uiChannel, u8"This is a test", KTgMAX_RSIZE );
        Test__Expect_EQ((TgCHAR_U8)0, sOutput_Buffer[0]);
        sOutput_Buffer[0] = 0;
        sOutput.m_nbyData_Current = 0;

        tgCN_UID_Print( KTgUID_NONE, uiChannel, u8"\n", KTgMAX_RSIZE );
    }

    tgIO_OM__Close( &sOutput.m_sOutput );

    tgCN_Stop_Unit_Test( (STg2_Output_P)pDest );
    TgFREEA( pDest );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CN_UID_PrintF ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_UID_PrintF )
{
    TgVOID_P                            pSrc;
    TgRSIZE                             uiSize;
    TgVOID_P                            pDest;
    TgCHAR_U8                           sOutput_Buffer[8192];
    STg2_Output_MEM                     sOutput;
    TgSINT_E08                          iRet;

    tgCN_Init_Unit_Test( &pSrc, &uiSize );
    TgALLOCA( TgUINT_E08 , uiSize, pDest );
    TgERROR( nullptr != pDest );
    tgMM_Copy( pDest, uiSize, pSrc, uiSize );
    tgCN_Start_Unit_Test();

    /* Create a memory base output object to be used when testing the console output systems */
    tgIO_OM__Open( &sOutput, (TgUINT_E08_P)sOutput_Buffer, sizeof( sOutput_Buffer ), nullptr );
    sOutput_Buffer[0] = 0;
    sOutput.m_nbyData_Current = 0;

    for (TgRSIZE uiIndex = 0; uiIndex < KTgCN_CHANEL_BITS; ++uiIndex)
    {
        TgUINT_E32_C                        uiChannel = 1u << (uiIndex + KTgCN_SEVERITY_BITS);
        TgRSIZE                             uiPrefix_Length = 0;

        /* We need to skip certain channels since they can be used for higher level testing logic in the unit test framework */
        if (
            KTgCN_CHANEL_MESSAGE == uiChannel ||
            KTgCN_CHANEL_WARNING == uiChannel ||
            KTgCN_CHANEL_ERROR == uiChannel ||
            KTgCN_CHANEL_CRITICAL == uiChannel)
        {
            continue;
        }

        /* Make sure that using console output does not modify the output buffer (possible side effect from previous iteration) */
        tgCN_UID_PrintF( KTgUID_NONE, uiChannel, u8"%s", u8"This is a test", KTgMAX_RSIZE );
        Test__Expect_EQ((TgCHAR_U8)0, sOutput_Buffer[0]);
        sOutput_Buffer[0] = 0;
        sOutput.m_nbyData_Current = 0;

        /* Add the output object to the list and make sure it is used */
        tgCN_Attach_Output( uiChannel, &sOutput.m_sOutput );

        /* Confirm that the system is outputting the expected text */
        tgCN_UID_PrintF( KTgUID_NONE, uiChannel, u8"%s", u8"This is a test" );
        Test__Expect_EQ(true, tgUSZ_CompareN( &iRet, sOutput_Buffer + uiPrefix_Length, KTgMAX_RSIZE, 0, u8"This is a test", KTgMAX_RSIZE, 0, 14 ) && (0 == iRet));
        sOutput_Buffer[0] = 0;
        sOutput.m_nbyData_Current = 0;

        /* Remove the output object from the list and make sure its no longer being used */
        tgCN_Remove_Output( uiChannel, &sOutput.m_sOutput );
    }

    tgIO_OM__Close( &sOutput.m_sOutput );

    tgCN_Stop_Unit_Test( (STg2_Output_P)pDest );
    TgFREEA( pDest );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CN_Process_Input ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_Process_Input )
{
    TgCHAR_U8                           szNameList[][8] = { u8"tst", u8"a", u8"aa", u8"aaa", u8"aaaa", u8"z", u8"zz", u8"zzz", u8"zzzz" };

    tgCN_OS_Process_Input( 0x0D, false );

    Test__Expect_EQ(true, tgCN_Insert_Command_Function( szNameList[0], KTgMAX_RSIZE, TEST__Console_Test_Function, nullptr, KTgMAX_RSIZE ));
    TgSTD_ATOMIC(store)( &g_xuiTestValue, 0 );

    /* Commands should be executable through the input system as well as directly */
    tgCN_OS_Process_Input( 't', false );
    tgCN_OS_Process_Input( 's', false );
    tgCN_OS_Process_Input( 't', false );
    tgCN_OS_Process_Input( 0x0D, false );
    Test__Expect_EQ(1, TgSTD_ATOMIC(load)( &g_xuiTestValue ));

    Test__Expect_EQ(true, tgCN_Remove_Command_Function( szNameList[0], KTgMAX_RSIZE ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CN_Insert_Command_Function ------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_Insert_Command_Function )
{
    TgCHAR_U8                           szNameList[][8] = { u8"tst", u8"a", u8"aa", u8"aaa", u8"aaaa", u8"z", u8"zz", u8"zzz", u8"zzzz" };

    /* The first call should succeed, while the second fail due to the unique command text requirement */
    Test__Expect_EQ(true, tgCN_Insert_Command_Function( szNameList[0], KTgMAX_RSIZE, TEST__Console_Test_Function, nullptr, KTgMAX_RSIZE ));
    Test__Expect_EQ(true, tgCN_Insert_Command_Function( szNameList[0], KTgMAX_RSIZE, TEST__Console_Test_Function, nullptr, KTgMAX_RSIZE ));
    Test__Expect_EQ(false, tgCN_Insert_Command_Function( szNameList[0], KTgMAX_RSIZE, TEST__Console_Test_Other_Function, nullptr, KTgMAX_RSIZE ));

    Test__Expect_EQ(true, tgCN_Insert_Command_Function( szNameList[1], KTgMAX_RSIZE, TEST__Console_Test_Function, nullptr, KTgMAX_RSIZE ));

    Test__Expect_EQ(true, tgCN_Remove_Command_Function( szNameList[0], KTgMAX_RSIZE ));
    Test__Expect_EQ(false, tgCN_Remove_Command_Function( szNameList[0], KTgMAX_RSIZE ));
    Test__Expect_EQ(false, tgCN_Execute_Command( szNameList[0], KTgMAX_RSIZE ));

    Test__Expect_EQ(true, tgCN_Remove_Command_Function( szNameList[1], KTgMAX_RSIZE ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CN_Remove_Command_Function ------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_Remove_Command_Function )
{
    /* Tested in UNIT_TEST__TEST__CN_Insert_Command_Function */

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CN_Print_Command_Functions ------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_Print_Command_Functions )
{
    TgCHAR_U8                           sOutput_Buffer[8192];
    STg2_Output_MEM                     sOutput;

    tgIO_OM__Open( &sOutput, (TgUINT_E08_P)sOutput_Buffer, sizeof( sOutput_Buffer ), nullptr );
    tgCN_Attach_Output( KTgCN_CHANEL_USER, &sOutput.m_sOutput );
    sOutput_Buffer[0] = 0;
    sOutput.m_nbyData_Current = 0;

    /* Clear out the output object and close it */
    tgCN_Print_Command_Functions( &sOutput.m_sOutput );
    sOutput.m_nbyData_Current = 0;
    sOutput_Buffer[0] = 0;

    tgIO_OM__Close( &sOutput.m_sOutput );

    TEST_END_METHOD( KTgS_OK );
}

/*# TgCOMPILE__CONSOLE */
#endif

/* ---- UNIT_TEST__TEST__CN_Var_Load_Config -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Load_Config )
{
    TgCHAR_U8                           sOutput_Buffer[8192];
    STg2_Output_MEM                     sOutput;
    STg2_Input_MEM                      sInput;
    TgRSIZE                             uiLength;
    TgCN_VAR_ID                         tiVarTest;
    TgUINT_E08                          uiData[128];

    /* Create a memory base output object to be used when testing the console output systems */
    tgIO_OM__Open( &sOutput, (TgUINT_E08_P)sOutput_Buffer, sizeof( sOutput_Buffer ), nullptr );
    sOutput_Buffer[0] = 0;
    sOutput.m_nbyData_Current = 0;

    sOutput_Buffer[0] = 0;
    uiLength = tgIO_PrintF( &sOutput.m_sOutput, u8"%s %f\n", u8"LoadTest", 7.0 );
    sOutput_Buffer[uiLength] = 0;
    tgIO_IM__Open( &sInput, (TgUINT_E08_P)sOutput_Buffer, uiLength, nullptr );

    tiVarTest = tgCN_Var_Init_F32( u8"LoadTest", KTgMAX_RSIZE, nullptr, KTgMAX_RSIZE, 0, 0, -10, 10 );
    tgCN_Var_Load_Config( &sInput.m_sInput, 0 );

    tgIO_IM__Close( &sInput.m_sInput );
    sOutput.m_nbyData_Current = 0;
    sOutput_Buffer[0] = 0;

    Test__Expect_EQ(true, tgCN_Var_Query_F32( (TgFLOAT32_P)uiData, tiVarTest ));
    Test__Expect_EQ(true, *(TgFLOAT32_P)uiData == 7);

    tgIO_OM__Close( &sOutput.m_sOutput );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CN_Var_Save_Config -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Save_Config )
{
    TgCHAR_U8                           sOutput_Buffer[8192];
    STg2_Output_MEM                     sOutput;

    /* Create a memory base output object to be used when testing the console output systems */
    tgIO_OM__Open( &sOutput, (TgUINT_E08_P)sOutput_Buffer, sizeof( sOutput_Buffer ), nullptr );
    sOutput_Buffer[0] = 0;
    sOutput.m_nbyData_Current = 0;

    tgCN_Var_Save_Config( &sOutput.m_sOutput );

    tgIO_OM__Close( &sOutput.m_sOutput );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CN_Var_Query_Init --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Query_Init )
{
    Test__Expect_EQ(true, tgCN_Var_Query_Init());

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CN_Var_Query_Boot --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Query_Boot )
{
    Test__Expect_EQ(true, tgCN_Var_Query_Boot());

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CN_Var_Query_Fixed_Memory ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Query_Fixed_Memory )
{
    tgCN_Var_Query_Fixed_Memory();

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CN_Print_Command_Variables ------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_Print_Command_Variables )
{
    TgCHAR_U8                           sOutput_Buffer[8192];
    STg2_Output_MEM                     sOutput;

    /* Create a memory base output object to be used when testing the console output systems */
    tgIO_OM__Open( &sOutput, (TgUINT_E08_P)sOutput_Buffer, sizeof( sOutput_Buffer ), nullptr );
    sOutput_Buffer[0] = 0;
    sOutput.m_nbyData_Current = 0;

    tgCN_Print_Command_Variables( &sOutput.m_sOutput );
    sOutput.m_nbyData_Current = 0;
    sOutput_Buffer[0] = 0;

    tgIO_OM__Close( &sOutput.m_sOutput );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CN_Var_Init_Bool ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Init_Bool )
{
    TgCN_VAR_ID                         tiVarTest;
    TgUINT_E08                          uiData[16];

    tiVarTest = tgCN_Var_Init_Bool( u8"Var_Init_Bool", KTgMAX_RSIZE, u8"Desc", KTgMAX_RSIZE, 0, true );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiVarTest.m_uiKI);

    /* Attempt to use an getter/setter function of the wrong type */
    Test__Expect_EQ(false, tgCN_Var_Set_S08( tiVarTest, 2 ));
    Test__Expect_EQ(false, tgCN_Var_Query_S08( (TgSINT_E08_P)uiData, tiVarTest ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CN_Var_Init_S08 ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Init_S08 )
{
    TgCN_VAR_ID                         tiVarTest;
    TgUINT_E08                          uiData[16];

    tiVarTest = tgCN_Var_Init_S08( u8"Var_Init_S08", KTgMAX_RSIZE, u8"Desc", KTgMAX_RSIZE, 0, 0, -10, 10 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiVarTest.m_uiKI);

    /* Attempt to use an getter/setter function of the wrong type */
    Test__Expect_EQ(false, tgCN_Var_Set_Bool( tiVarTest, true ));
    Test__Expect_EQ(false, tgCN_Var_Query_Bool( (TgBOOL_P)uiData, tiVarTest ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CN_Var_Init_S16 ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Init_S16 )
{
    TgCN_VAR_ID                         tiVarTest;
    TgUINT_E08                          uiData[16];

    tiVarTest = tgCN_Var_Init_S16( u8"Var_Init_S16", KTgMAX_RSIZE, u8"Desc", KTgMAX_RSIZE, 0, 0, -10, 10 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiVarTest.m_uiKI);

    /* Attempt to use an getter/setter function of the wrong type */
    Test__Expect_EQ(false, tgCN_Var_Set_Bool( tiVarTest, true ));
    Test__Expect_EQ(false, tgCN_Var_Query_Bool( (TgBOOL_P)uiData, tiVarTest ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CN_Var_Init_S32 ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Init_S32 )
{
    TgCN_VAR_ID                         tiVarTest;
    TgUINT_E08                          uiData[16];

    tiVarTest = tgCN_Var_Init_S32( u8"Var_Init_S32", KTgMAX_RSIZE, u8"Desc", KTgMAX_RSIZE, 0, 0, -10, 10 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiVarTest.m_uiKI);

    /* Attempt to use an getter/setter function of the wrong type */
    Test__Expect_EQ(false, tgCN_Var_Set_Bool( tiVarTest, true ));
    Test__Expect_EQ(false, tgCN_Var_Query_Bool( (TgBOOL_P)uiData, tiVarTest ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CN_Var_Init_S64 ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Init_S64 )
{
    TgCN_VAR_ID                         tiVarTest;
    TgUINT_E08                          uiData[16];

    tiVarTest = tgCN_Var_Init_S64( u8"Var_Init_S64", KTgMAX_RSIZE, u8"Desc", KTgMAX_RSIZE, 0, 0, -10, 10 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiVarTest.m_uiKI);

    /* Attempt to use an getter/setter function of the wrong type */
    Test__Expect_EQ(false, tgCN_Var_Set_Bool( tiVarTest, true ));
    Test__Expect_EQ(false, tgCN_Var_Query_Bool( (TgBOOL_P)uiData, tiVarTest ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CN_Var_Init_U08 ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Init_U08 )
{
    TgCN_VAR_ID                         tiVarTest;
    TgUINT_E08                          uiData[16];

    tiVarTest = tgCN_Var_Init_U08( u8"Var_Init_U08", KTgMAX_RSIZE, u8"Desc", KTgMAX_RSIZE, 0, 0, 2, 10 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiVarTest.m_uiKI);

    /* Attempt to use an getter/setter function of the wrong type */
    Test__Expect_EQ(false, tgCN_Var_Set_Bool( tiVarTest, true ));
    Test__Expect_EQ(false, tgCN_Var_Query_Bool( (TgBOOL_P)uiData, tiVarTest ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CN_Var_Init_U16 ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Init_U16 )
{
    TgCN_VAR_ID                         tiVarTest;
    TgUINT_E08                          uiData[16];

    tiVarTest = tgCN_Var_Init_U16( u8"Var_Init_U16", KTgMAX_RSIZE, nullptr, KTgMAX_RSIZE, 0, 0, 2, 10 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiVarTest.m_uiKI);

    /* Attempt to use an getter/setter function of the wrong type */
    Test__Expect_EQ(false, tgCN_Var_Set_Bool( tiVarTest, true ));
    Test__Expect_EQ(false, tgCN_Var_Query_Bool( (TgBOOL_P)uiData, tiVarTest ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CN_Var_Init_U32 ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Init_U32 )
{
    TgCN_VAR_ID                         tiVarTest;
    TgUINT_E08                          uiData[16];

    tiVarTest = tgCN_Var_Init_U32( u8"Var_Init_U32", KTgMAX_RSIZE, u8"Desc", KTgMAX_RSIZE, 0, 0, 2, 10 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiVarTest.m_uiKI);

    /* Attempt to use an getter/setter function of the wrong type */
    Test__Expect_EQ(false, tgCN_Var_Set_Bool( tiVarTest, true ));
    Test__Expect_EQ(false, tgCN_Var_Query_Bool( (TgBOOL_P)uiData, tiVarTest ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CN_Var_Init_U64 ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Init_U64 )
{
    TgCN_VAR_ID                         tiVarTest;
    TgUINT_E08                          uiData[16];

    tiVarTest = tgCN_Var_Init_U64( u8"Var_Init_U64", KTgMAX_RSIZE, u8"Desc", KTgMAX_RSIZE, 0, 0, 2, 10 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiVarTest.m_uiKI);

    /* Attempt to use an getter/setter function of the wrong type */
    Test__Expect_EQ(false, tgCN_Var_Set_Bool( tiVarTest, true ));
    Test__Expect_EQ(false, tgCN_Var_Query_Bool( (TgBOOL_P)uiData, tiVarTest ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CN_Var_Init_F32 ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Init_F32 )
{
    TgCN_VAR_ID                         tiVarTest;
    TgUINT_E08                          uiData[16];

    tiVarTest = tgCN_Var_Init_F32( u8"Var_Init_F32", KTgMAX_RSIZE, nullptr, KTgMAX_RSIZE, 0, 0, -10, 10 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiVarTest.m_uiKI);

    /* Attempt to use an getter/setter function of the wrong type */
    Test__Expect_EQ(false, tgCN_Var_Set_Bool( tiVarTest, true ));
    Test__Expect_EQ(false, tgCN_Var_Query_Bool( (TgBOOL_P)uiData, tiVarTest ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CtgMH_Var_Init_F32_04_1 ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CtgMH_Var_Init_F32_04_1 )
{
    TgUN_V128                           uMin, uMax, uDefault;
    TgCN_VAR_ID                         tiVarTest;
    TgUINT_E08                          uiData[16];

    uMin.m_vF32_04_1 = tgMH_SET1_F32_04_1( -10.0F );
    uMax.m_vF32_04_1 = tgMH_SET1_F32_04_1(  10.0F );
    uDefault.m_vF32_04_1 = tgMH_SET1_F32_04_1( 0.0F );

    tiVarTest = tgCN_Var_Init_F32_04_1( u8"Var_Init_F32_04_1", KTgMAX_RSIZE, u8"Desc", KTgMAX_RSIZE, 0, uDefault.m_vF32_04_1, uMin.m_vF32_04_1, uMax.m_vF32_04_1 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiVarTest.m_uiKI);

    /* Attempt to use an getter/setter function of the wrong type */
    Test__Expect_EQ(false, tgCN_Var_Set_Bool( tiVarTest, true ));
    Test__Expect_EQ(false, tgCN_Var_Query_Bool( (TgBOOL_P)uiData, tiVarTest ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CN_Var_Init_String -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Init_String )
{
    TgCHAR_U8                           szNameList[][8] = { u8"tst", u8"a", u8"aa", u8"aaa", u8"aaaa", u8"z", u8"zz", u8"zzz", u8"zzzz" };
    TgCN_VAR_ID                         tiVarTest;
    TgUINT_E08                          uiData[16];

    tiVarTest = tgCN_Var_Init_String( u8"Var_Init_String", KTgMAX_RSIZE, u8"Desc", KTgMAX_RSIZE, 0, szNameList[0], KTgMAX_RSIZE, (TgCHAR_U8_P)uiData,
                                      sizeof( uiData ) / sizeof(TgCHAR_U8) );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiVarTest.m_uiKI);

    /* Attempt to use an getter/setter function of the wrong type */
    Test__Expect_EQ(false, tgCN_Var_Set_Bool( tiVarTest, true ));
    Test__Expect_EQ(false, tgCN_Var_Query_Bool( (TgBOOL_P)uiData, tiVarTest ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CN_Var_Set_Bool ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Set_Bool )
{
    TgCN_VAR_ID                         tiVarTest;

    tiVarTest = tgCN_Var_Init_Bool( u8"Var_Set_Bool", KTgMAX_RSIZE, u8"Desc", KTgMAX_RSIZE, 0, true );

    Test__Expect_EQ(true, tgCN_Var_Set_Bool( tiVarTest, true ));
    Test__Expect_EQ(true, tgCN_Var_Set_Bool( tiVarTest, false ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CN_Var_Set_S08 ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Set_S08 )
{
    TgCN_VAR_ID                         tiVarTest;

    tiVarTest = tgCN_Var_Init_S08( u8"Var_Set_S08", KTgMAX_RSIZE, u8"Desc", KTgMAX_RSIZE, 0, 0, -10, 10 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiVarTest.m_uiKI);

    Test__Expect_EQ(true, tgCN_Var_Set_S08( tiVarTest, 3 ));
    Test__Expect_EQ(true, tgCN_Var_Set_S08( tiVarTest, 4 ));
    Test__Expect_EQ(true, tgCN_Var_Set_S08( tiVarTest, -12 ));
    Test__Expect_EQ(true, tgCN_Var_Set_S08( tiVarTest, 12 ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CN_Var_Set_S16 ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Set_S16 )
{
    TgCN_VAR_ID                         tiVarTest;

    tiVarTest = tgCN_Var_Init_S16( u8"Var_Set_S16", KTgMAX_RSIZE, u8"Desc", KTgMAX_RSIZE, 0, 0, -10, 10 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiVarTest.m_uiKI);

    Test__Expect_EQ(true, tgCN_Var_Set_S16( tiVarTest, 3 ));
    Test__Expect_EQ(true, tgCN_Var_Set_S16( tiVarTest, 4 ));
    Test__Expect_EQ(true, tgCN_Var_Set_S16( tiVarTest, -12 ));
    Test__Expect_EQ(true, tgCN_Var_Set_S16( tiVarTest, 12 ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CN_Var_Set_S32 ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Set_S32 )
{
    TgCN_VAR_ID                         tiVarTest;

    tiVarTest = tgCN_Var_Init_S32( u8"Var_Set_S32", KTgMAX_RSIZE, u8"Desc", KTgMAX_RSIZE, 0, 0, -10, 10 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiVarTest.m_uiKI);

    Test__Expect_EQ(true, tgCN_Var_Set_S32( tiVarTest, 3 ));
    Test__Expect_EQ(true, tgCN_Var_Set_S32( tiVarTest, 4 ));
    Test__Expect_EQ(true, tgCN_Var_Set_S32( tiVarTest, -12 ));
    Test__Expect_EQ(true, tgCN_Var_Set_S32( tiVarTest, 12 ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CN_Var_Set_S64 ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Set_S64 )
{
    TgCN_VAR_ID                         tiVarTest;

    tiVarTest = tgCN_Var_Init_S64( u8"Var_Set_S64", KTgMAX_RSIZE, u8"Desc", KTgMAX_RSIZE, 0, 0, -10, 10 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiVarTest.m_uiKI);

    Test__Expect_EQ(true, tgCN_Var_Set_S64( tiVarTest, 3 ));
    Test__Expect_EQ(true, tgCN_Var_Set_S64( tiVarTest, 4 ));
    Test__Expect_EQ(true, tgCN_Var_Set_S64( tiVarTest, -12 ));
    Test__Expect_EQ(true, tgCN_Var_Set_S64( tiVarTest, 12 ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CN_Var_Set_U08 ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Set_U08 )
{
    TgCN_VAR_ID                         tiVarTest;

    tiVarTest = tgCN_Var_Init_U08( u8"Var_Set_U08", KTgMAX_RSIZE, u8"Desc", KTgMAX_RSIZE, 0, 0, 2, 10 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiVarTest.m_uiKI);

    Test__Expect_EQ(true, tgCN_Var_Set_U08( tiVarTest, 3 ));
    Test__Expect_EQ(true, tgCN_Var_Set_U08( tiVarTest, 4 ));
    Test__Expect_EQ(true, tgCN_Var_Set_U08( tiVarTest, 1 ));
    Test__Expect_EQ(true, tgCN_Var_Set_U08( tiVarTest, 12 ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CN_Var_Set_U16 ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Set_U16 )
{
    TgCN_VAR_ID                         tiVarTest;

    tiVarTest = tgCN_Var_Init_U16( u8"Var_Set_U16", KTgMAX_RSIZE, nullptr, KTgMAX_RSIZE, 0, 0, 2, 10 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiVarTest.m_uiKI);

    Test__Expect_EQ(true, tgCN_Var_Set_U16( tiVarTest, 3 ));
    Test__Expect_EQ(true, tgCN_Var_Set_U16( tiVarTest, 4 ));
    Test__Expect_EQ(true, tgCN_Var_Set_U16( tiVarTest, 1 ));
    Test__Expect_EQ(true, tgCN_Var_Set_U16( tiVarTest, 12 ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CN_Var_Set_U32 ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Set_U32 )
{
    TgCN_VAR_ID                         tiVarTest;

    tiVarTest = tgCN_Var_Init_U32( u8"Var_Set_U32", KTgMAX_RSIZE, u8"Desc", KTgMAX_RSIZE, 0, 0, 2, 10 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiVarTest.m_uiKI);

    Test__Expect_EQ(true, tgCN_Var_Set_U32( tiVarTest, 3 ));
    Test__Expect_EQ(true, tgCN_Var_Set_U32( tiVarTest, 4 ));
    Test__Expect_EQ(true, tgCN_Var_Set_U32( tiVarTest, 1 ));
    Test__Expect_EQ(true, tgCN_Var_Set_U32( tiVarTest, 12 ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CN_Var_Set_U64 ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Set_U64 )
{
    TgCN_VAR_ID                         tiVarTest;

    tiVarTest = tgCN_Var_Init_U64( u8"Var_Set_U64", KTgMAX_RSIZE, u8"Desc", KTgMAX_RSIZE, 0, 0, 2, 10 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiVarTest.m_uiKI);

    Test__Expect_EQ(true, tgCN_Var_Set_U64( tiVarTest, 3 ));
    Test__Expect_EQ(true, tgCN_Var_Set_U64( tiVarTest, 4 ));
    Test__Expect_EQ(true, tgCN_Var_Set_U64( tiVarTest, 1 ));
    Test__Expect_EQ(true, tgCN_Var_Set_U64( tiVarTest, 12 ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CN_Var_Set_F32 ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Set_F32 )
{
    TgCN_VAR_ID                         tiVarTest;

    tiVarTest = tgCN_Var_Init_F32( u8"Var_Set_F32", KTgMAX_RSIZE, nullptr, KTgMAX_RSIZE, 0, 0, -10, 10 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiVarTest.m_uiKI);

    Test__Expect_EQ(true, tgCN_Var_Set_F32( tiVarTest, 3 ));
    Test__Expect_EQ(true, tgCN_Var_Set_F32( tiVarTest, 4 ));
    Test__Expect_EQ(true, tgCN_Var_Set_F32( tiVarTest, -12 ));
    Test__Expect_EQ(true, tgCN_Var_Set_F32( tiVarTest, 12 ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CtgMH_Var_Set_F32_04_1 ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CtgMH_Var_Set_F32_04_1 )
{
    TgUN_V128                           uMin, uMax, uDefault, uValue;
    TgCN_VAR_ID                         tiVarTest;

    uMin.m_vF32_04_1 = tgMH_SET1_F32_04_1( -10.0F );
    uMax.m_vF32_04_1 = tgMH_SET1_F32_04_1(  10.0F );
    uDefault.m_vF32_04_1 = tgMH_SET1_F32_04_1( 0.0F );

    tiVarTest = tgCN_Var_Init_F32_04_1( u8"Var_Set_F32_04_1", KTgMAX_RSIZE, u8"Desc", KTgMAX_RSIZE, 0, uDefault.m_vF32_04_1, uMin.m_vF32_04_1, uMax.m_vF32_04_1 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiVarTest.m_uiKI);

    uValue.m_vF32_04_1 = tgMH_Init_ELEM_F32_04_1( -12.0F, 3.0F, 5.0F, 12.0F );
    Test__Expect_EQ(true, tgCN_Var_Set_F32_04_1( tiVarTest, uValue.m_vF32_04_1 ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CN_Var_Set_String --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Set_String )
{
    TgCHAR_U8                           szNameList[][8] = { u8"tst", u8"a", u8"aa", u8"aaa", u8"aaaa", u8"z", u8"zz", u8"zzz", u8"zzzz" };
    TgCN_VAR_ID                         tiVarTest;
    TgUINT_E08                          uiData[16];

    tiVarTest = tgCN_Var_Init_String( u8"Var_Set_String", KTgMAX_RSIZE, u8"Desc", KTgMAX_RSIZE, 0, szNameList[0], KTgMAX_RSIZE, (TgCHAR_U8_P)uiData,
                                      sizeof( uiData ) / sizeof(TgCHAR_U8) );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiVarTest.m_uiKI);

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CN_Var_Query_Bool --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Query_Bool )
{
    TgCN_VAR_ID                         tiVarTest;
    TgUINT_E08                          uiData[16];

    tiVarTest = tgCN_Var_Init_Bool( u8"Var_Query_Bool", KTgMAX_RSIZE, u8"Desc", KTgMAX_RSIZE, 0, true );

    Test__Expect_EQ(true, tgCN_Var_Set_Bool( tiVarTest, true ));
    Test__Expect_EQ(true, tgCN_Var_Query_Bool( (TgBOOL_P)uiData, tiVarTest ));
    Test__Expect_EQ(true, *(TgBOOL_P)uiData == true);

    Test__Expect_EQ(true, tgCN_Var_Set_Bool( tiVarTest, false ));
    Test__Expect_EQ(true, tgCN_Var_Query_Bool( (TgBOOL_P)uiData, tiVarTest ));
    Test__Expect_EQ(true, *(TgBOOL_P)uiData == false);

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CN_Var_Query_S08 ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Query_S08 )
{
    TgCN_VAR_ID                         tiVarTest;
    TgUINT_E08                          uiData[16];

    tiVarTest = tgCN_Var_Init_S08( u8"Var_Query_S08", KTgMAX_RSIZE, u8"Desc", KTgMAX_RSIZE, 0, 0, -10, 10 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiVarTest.m_uiKI);

    Test__Expect_EQ(true, tgCN_Var_Set_S08( tiVarTest, 3 ));
    Test__Expect_EQ(true, tgCN_Var_Query_S08( (TgSINT_E08_P)uiData, tiVarTest ));
    Test__Expect_EQ(true, *(TgSINT_E08_P)uiData == 3);

    Test__Expect_EQ(true, tgCN_Var_Set_S08( tiVarTest, 4 ));
    Test__Expect_EQ(true, tgCN_Var_Query_S08( (TgSINT_E08_P)uiData, tiVarTest ));
    Test__Expect_EQ(true, *(TgSINT_E08_P)uiData == 4);

    /* Attempt to set a value lower than the min range */
    Test__Expect_EQ(true, tgCN_Var_Set_S08( tiVarTest, -12 ));
    Test__Expect_EQ(true, tgCN_Var_Query_S08( (TgSINT_E08_P)uiData, tiVarTest ));
    Test__Expect_EQ(true, *(TgSINT_E08_P)uiData == -10);

    /* Attempt to set a value higher than the max range */
    Test__Expect_EQ(true, tgCN_Var_Set_S08( tiVarTest, 12 ));
    Test__Expect_EQ(true, tgCN_Var_Query_S08( (TgSINT_E08_P)uiData, tiVarTest ));
    Test__Expect_EQ(true, *(TgSINT_E08_P)uiData == 10);

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CN_Var_Query_S16 ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Query_S16 )
{
    TgCN_VAR_ID                         tiVarTest;
    TgUINT_E08                          uiData[16];

    tiVarTest = tgCN_Var_Init_S16( u8"Var_Query_S16", KTgMAX_RSIZE, u8"Desc", KTgMAX_RSIZE, 0, 0, -10, 10 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiVarTest.m_uiKI);

    Test__Expect_EQ(true, tgCN_Var_Set_S16( tiVarTest, 3 ));
    Test__Expect_EQ(true, tgCN_Var_Query_S16( (TgSINT_E16_P)uiData, tiVarTest ));
    Test__Expect_EQ(true, *(TgSINT_E16_P)uiData == 3);
    
    Test__Expect_EQ(true, tgCN_Var_Set_S16( tiVarTest, 4 ));
    Test__Expect_EQ(true, tgCN_Var_Query_S16( (TgSINT_E16_P)uiData, tiVarTest ));
    Test__Expect_EQ(true, *(TgSINT_E16_P)uiData == 4);
    
    Test__Expect_EQ(true, tgCN_Var_Set_S16( tiVarTest, -12 ));
    Test__Expect_EQ(true, tgCN_Var_Query_S16( (TgSINT_E16_P)uiData, tiVarTest ));
    Test__Expect_EQ(true, *(TgSINT_E16_P)uiData == -10);
    
    Test__Expect_EQ(true, tgCN_Var_Set_S16( tiVarTest, 12 ));
    Test__Expect_EQ(true, tgCN_Var_Query_S16( (TgSINT_E16_P)uiData, tiVarTest ));
    Test__Expect_EQ(true, *(TgSINT_E16_P)uiData == 10);

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CN_Var_Query_S32 ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Query_S32 )
{
    TgCN_VAR_ID                         tiVarTest;
    TgUINT_E08                          uiData[16];

    tiVarTest = tgCN_Var_Init_S32( u8"Var_Query_S32", KTgMAX_RSIZE, u8"Desc", KTgMAX_RSIZE, 0, 0, -10, 10 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiVarTest.m_uiKI);

    Test__Expect_EQ(true, tgCN_Var_Set_S32( tiVarTest, 3 ));
    Test__Expect_EQ(true, tgCN_Var_Query_S32( (TgSINT_E32_P)uiData, tiVarTest ));
    Test__Expect_EQ(true, *(TgSINT_E32_P)uiData == 3);

    Test__Expect_EQ(true, tgCN_Var_Set_S32( tiVarTest, 4 ));
    Test__Expect_EQ(true, tgCN_Var_Query_S32( (TgSINT_E32_P)uiData, tiVarTest ));
    Test__Expect_EQ(true, *(TgSINT_E32_P)uiData == 4);

    Test__Expect_EQ(true, tgCN_Var_Set_S32( tiVarTest, -12 ));
    Test__Expect_EQ(true, tgCN_Var_Query_S32( (TgSINT_E32_P)uiData, tiVarTest ));
    Test__Expect_EQ(true, *(TgSINT_E32_P)uiData == -10);

    Test__Expect_EQ(true, tgCN_Var_Set_S32( tiVarTest, 12 ));
    Test__Expect_EQ(true, tgCN_Var_Query_S32( (TgSINT_E32_P)uiData, tiVarTest ));
    Test__Expect_EQ(true, *(TgSINT_E32_P)uiData == 10);

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CN_Var_Query_S64 ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Query_S64 )
{
    TgCN_VAR_ID                         tiVarTest;
    TgUINT_E08                          uiData[16];

    tiVarTest = tgCN_Var_Init_S64( u8"Var_Query_S64", KTgMAX_RSIZE, u8"Desc", KTgMAX_RSIZE, 0, 0, -10, 10 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiVarTest.m_uiKI);

    Test__Expect_EQ(true, tgCN_Var_Set_S64( tiVarTest, 3 ));
    Test__Expect_EQ(true, tgCN_Var_Query_S64( (TgSINT_E64_P)uiData, tiVarTest ));
    Test__Expect_EQ(true, *(TgSINT_E64_P)uiData == 3);

    Test__Expect_EQ(true, tgCN_Var_Set_S64( tiVarTest, 4 ));
    Test__Expect_EQ(true, tgCN_Var_Query_S64( (TgSINT_E64_P)uiData, tiVarTest ));
    Test__Expect_EQ(true, *(TgSINT_E64_P)uiData == 4);

    Test__Expect_EQ(true, tgCN_Var_Set_S64( tiVarTest, -12 ));
    Test__Expect_EQ(true, tgCN_Var_Query_S64( (TgSINT_E64_P)uiData, tiVarTest ));
    Test__Expect_EQ(true, *(TgSINT_E64_P)uiData == -10);

    Test__Expect_EQ(true, tgCN_Var_Set_S64( tiVarTest, 12 ));
    Test__Expect_EQ(true, tgCN_Var_Query_S64( (TgSINT_E64_P)uiData, tiVarTest ));
    Test__Expect_EQ(true, *(TgSINT_E64_P)uiData == 10);

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CN_Var_Query_U08 ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Query_U08 )
{
    TgCN_VAR_ID                         tiVarTest;
    TgUINT_E08                          uiData[16];

    tiVarTest = tgCN_Var_Init_U08( u8"Var_Query_U08", KTgMAX_RSIZE, u8"Desc", KTgMAX_RSIZE, 0, 0, 2, 10 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiVarTest.m_uiKI);

    Test__Expect_EQ(true, tgCN_Var_Set_U08( tiVarTest, 3 ));
    Test__Expect_EQ(true, tgCN_Var_Query_U08( (TgUINT_E08_P)uiData, tiVarTest ));
    Test__Expect_EQ(true, *(TgUINT_E08_P)uiData == 3);

    Test__Expect_EQ(true, tgCN_Var_Set_U08( tiVarTest, 4 ));
    Test__Expect_EQ(true, tgCN_Var_Query_U08( (TgUINT_E08_P)uiData, tiVarTest ));
    Test__Expect_EQ(true, *(TgUINT_E08_P)uiData == 4);

    Test__Expect_EQ(true, tgCN_Var_Set_U08( tiVarTest, 1 ));
    Test__Expect_EQ(true, tgCN_Var_Query_U08( (TgUINT_E08_P)uiData, tiVarTest ));
    Test__Expect_EQ(true, *(TgUINT_E08_P)uiData == 2);

    Test__Expect_EQ(true, tgCN_Var_Set_U08( tiVarTest, 12 ));
    Test__Expect_EQ(true, tgCN_Var_Query_U08( (TgUINT_E08_P)uiData, tiVarTest ));
    Test__Expect_EQ(true, *(TgUINT_E08_P)uiData == 10);

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CN_Var_Query_U16 ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Query_U16 )
{
    TgCN_VAR_ID                         tiVarTest;
    TgUINT_E08                          uiData[16];

    tiVarTest = tgCN_Var_Init_U16( u8"Var_Query_U16", KTgMAX_RSIZE, nullptr, KTgMAX_RSIZE, 0, 0, 2, 10 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiVarTest.m_uiKI);

    Test__Expect_EQ(true, tgCN_Var_Set_U16( tiVarTest, 3 ));
    Test__Expect_EQ(true, tgCN_Var_Query_U16( (TgUINT_E16_P)uiData, tiVarTest ));
    Test__Expect_EQ(true, *(TgUINT_E16_P)uiData == 3);

    Test__Expect_EQ(true, tgCN_Var_Set_U16( tiVarTest, 4 ));
    Test__Expect_EQ(true, tgCN_Var_Query_U16( (TgUINT_E16_P)uiData, tiVarTest ));
    Test__Expect_EQ(true, *(TgUINT_E16_P)uiData == 4);

    Test__Expect_EQ(true, tgCN_Var_Set_U16( tiVarTest, 1 ));
    Test__Expect_EQ(true, tgCN_Var_Query_U16( (TgUINT_E16_P)uiData, tiVarTest ));
    Test__Expect_EQ(true, *(TgUINT_E16_P)uiData == 2);

    Test__Expect_EQ(true, tgCN_Var_Set_U16( tiVarTest, 12 ));
    Test__Expect_EQ(true, tgCN_Var_Query_U16( (TgUINT_E16_P)uiData, tiVarTest ));
    Test__Expect_EQ(true, *(TgUINT_E16_P)uiData == 10);

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CN_Var_Query_U32 ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Query_U32 )
{
    TgCN_VAR_ID                         tiVarTest;
    TgUINT_E08                          uiData[16];

    tiVarTest = tgCN_Var_Init_U32( u8"Var_Query_U32", KTgMAX_RSIZE, u8"Desc", KTgMAX_RSIZE, 0, 0, 2, 10 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiVarTest.m_uiKI);

    Test__Expect_EQ(true, tgCN_Var_Set_U32( tiVarTest, 3 ));
    Test__Expect_EQ(true, tgCN_Var_Query_U32( (TgUINT_E32_P)uiData, tiVarTest ));
    Test__Expect_EQ(true, *(TgUINT_E32_P)uiData == 3);

    Test__Expect_EQ(true, tgCN_Var_Set_U32( tiVarTest, 4 ));
    Test__Expect_EQ(true, tgCN_Var_Query_U32( (TgUINT_E32_P)uiData, tiVarTest ));
    Test__Expect_EQ(true, *(TgUINT_E32_P)uiData == 4);

    Test__Expect_EQ(true, tgCN_Var_Set_U32( tiVarTest, 1 ));
    Test__Expect_EQ(true, tgCN_Var_Query_U32( (TgUINT_E32_P)uiData, tiVarTest ));
    Test__Expect_EQ(true, *(TgUINT_E32_P)uiData == 2);

    Test__Expect_EQ(true, tgCN_Var_Set_U32( tiVarTest, 12 ));
    Test__Expect_EQ(true, tgCN_Var_Query_U32( (TgUINT_E32_P)uiData, tiVarTest ));
    Test__Expect_EQ(true, *(TgUINT_E32_P)uiData == 10);

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CN_Var_Query_U64 ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Query_U64 )
{
    TgCN_VAR_ID                         tiVarTest;
    TgUINT_E08                          uiData[16];

    tiVarTest = tgCN_Var_Init_U64( u8"Var_Query_U64", KTgMAX_RSIZE, u8"Desc", KTgMAX_RSIZE, 0, 0, 2, 10 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiVarTest.m_uiKI);

    Test__Expect_EQ(true, tgCN_Var_Set_U64( tiVarTest, 3 ));
    Test__Expect_EQ(true, tgCN_Var_Query_U64( (TgUINT_E64_P)uiData, tiVarTest ));
    Test__Expect_EQ(true, *(TgUINT_E64_P)uiData == 3);

    Test__Expect_EQ(true, tgCN_Var_Set_U64( tiVarTest, 4 ));
    Test__Expect_EQ(true, tgCN_Var_Query_U64( (TgUINT_E64_P)uiData, tiVarTest ));
    Test__Expect_EQ(true, *(TgUINT_E64_P)uiData == 4);

    Test__Expect_EQ(true, tgCN_Var_Set_U64( tiVarTest, 1 ));
    Test__Expect_EQ(true, tgCN_Var_Query_U64( (TgUINT_E64_P)uiData, tiVarTest ));
    Test__Expect_EQ(true, *(TgUINT_E64_P)uiData == 2);

    Test__Expect_EQ(true, tgCN_Var_Set_U64( tiVarTest, 12 ));
    Test__Expect_EQ(true, tgCN_Var_Query_U64( (TgUINT_E64_P)uiData, tiVarTest ));
    Test__Expect_EQ(true, *(TgUINT_E64_P)uiData == 10);

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CN_Var_Query_F32 ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Query_F32 )
{
    TgCN_VAR_ID                         tiVarTest;
    TgUINT_E08                          uiData[16];

    tiVarTest = tgCN_Var_Init_F32( u8"Var_Query_F32", KTgMAX_RSIZE, nullptr, KTgMAX_RSIZE, 0, 0, -10, 10 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiVarTest.m_uiKI);

    Test__Expect_EQ(true, tgCN_Var_Set_F32( tiVarTest, 3 ));
    Test__Expect_EQ(true, tgCN_Var_Query_F32( (TgFLOAT32_P)uiData, tiVarTest ));
    Test__Expect_EQ(true, *(TgFLOAT32_P)uiData == 3);

    Test__Expect_EQ(true, tgCN_Var_Set_F32( tiVarTest, 4 ));
    Test__Expect_EQ(true, tgCN_Var_Query_F32( (TgFLOAT32_P)uiData, tiVarTest ));
    Test__Expect_EQ(true, *(TgFLOAT32_P)uiData == 4);

    Test__Expect_EQ(true, tgCN_Var_Set_F32( tiVarTest, -12 ));
    Test__Expect_EQ(true, tgCN_Var_Query_F32( (TgFLOAT32_P)uiData, tiVarTest ));
    Test__Expect_EQ(true, *(TgFLOAT32_P)uiData == -10);

    Test__Expect_EQ(true, tgCN_Var_Set_F32( tiVarTest, 12 ));
    Test__Expect_EQ(true, tgCN_Var_Query_F32( (TgFLOAT32_P)uiData, tiVarTest ));
    Test__Expect_EQ(true, *(TgFLOAT32_P)uiData == 10);

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CtgMH_Var_Query_F32_04_1 ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CtgMH_Var_Query_F32_04_1 )
{
    TgUN_V128                           uMin, uMax, uDefault, uValue, uQuery;
    TgCN_VAR_ID                         tiVarTest;

    uDefault.m_vF32_04_1 = tgMH_SET1_F32_04_1( 0.0F );
    uMin.m_vF32_04_1 = tgMH_SET1_F32_04_1( -10.0F );
    uMax.m_vF32_04_1 = tgMH_SET1_F32_04_1(  10.0F );

    tiVarTest = tgCN_Var_Init_F32_04_1( u8"Var_Query_F32_04_1", KTgMAX_RSIZE, u8"Desc", KTgMAX_RSIZE, 0, uDefault.m_vF32_04_1, uMin.m_vF32_04_1, uMax.m_vF32_04_1 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiVarTest.m_uiKI);

    Test__Expect_EQ(true, tgCN_Var_Query_F32_04_1( &uQuery.m_vF32_04_1, tiVarTest ));
    Test__Expect_EQ(true, uQuery.m_vS_F32_04_1.x == 0.0F);
    Test__Expect_EQ(true, uQuery.m_vS_F32_04_1.y == 0.0F);
    Test__Expect_EQ(true, uQuery.m_vS_F32_04_1.z == 0.0F);
    Test__Expect_EQ(true, uQuery.m_vS_F32_04_1.w == 0.0F);

    uValue.m_vF32_04_1 = tgMH_Init_ELEM_F32_04_1( -12.0F, 3.0F, 5.0F, 12.0F );
    Test__Expect_EQ(true, tgCN_Var_Set_F32_04_1( tiVarTest, uValue.m_vF32_04_1 ));
    Test__Expect_EQ(true, tgCN_Var_Query_F32_04_1( &uQuery.m_vF32_04_1, tiVarTest ));
    Test__Expect_EQ(true, uQuery.m_vS_F32_04_1.x == -10.0F);
    Test__Expect_EQ(true, uQuery.m_vS_F32_04_1.y == 3.0F);
    Test__Expect_EQ(true, uQuery.m_vS_F32_04_1.z == 5.0F);
    Test__Expect_EQ(true, uQuery.m_vS_F32_04_1.w == 10.0F);

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CN_Var_Query_String ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Query_String )
{
    TgCHAR_U8                           szNameList[][8] = { u8"tst", u8"a", u8"aa", u8"aaa", u8"aaaa", u8"z", u8"zz", u8"zzz", u8"zzzz" };
    TgCN_VAR_ID                         tiVarTest;
    TgCHAR_U8_CP                        mbzValue;
    TgSINT_E08                          iRet;
    TgCHAR_U8_P                         apszVarList[TgARRAY_COUNT( szNameList )];
    TgUINT_E08                          uiData[16];

    tiVarTest = tgCN_Var_Init_String( u8"Var_Query_String", KTgMAX_RSIZE, u8"Desc", KTgMAX_RSIZE, 0, szNameList[0], KTgMAX_RSIZE, (TgCHAR_U8_P)uiData,
                                      sizeof( uiData ) / sizeof(TgCHAR_U8) );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiVarTest.m_uiKI);

    Test__Expect_EQ(true, tgCN_Var_Set_String( tiVarTest, szNameList[1], KTgMAX_RSIZE ));
    Test__Expect_EQ(true, tgCN_Var_Query_String( &mbzValue, tiVarTest ));
    Test__Expect_EQ(true, tgUSZ_Compare( &iRet, szNameList[1], KTgMAX_RSIZE, 0, mbzValue, KTgMAX_RSIZE, 0 ) && (0 == iRet));
    Test__Expect_EQ(true, tgUSZ_Compare( &iRet, (TgCHAR_U8_P)uiData, KTgMAX_RSIZE, 0, mbzValue, KTgMAX_RSIZE, 0 ) && (0 == iRet));

    for (TgRSIZE iIndex = 0; iIndex < (TgSINT_E32 )TgARRAY_COUNT( szNameList ); ++iIndex)
    {
        apszVarList[iIndex] = szNameList[iIndex];
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CN_Var_Query_Id ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CN_Var_Query_Id )
{
    TgCN_VAR_ID                         tiVarTest_0, tiVarTest_1;
    TgUINT_E08                          uiData[16];

    tiVarTest_0 = tgCN_Var_Init_F32( u8"Var_Query_Query_Id", KTgMAX_RSIZE, nullptr, KTgMAX_RSIZE, 0, 0, -10, 10 );
    Test__Expect_NE(KTgID__INVALID_VALUE, tiVarTest_0.m_uiKI);

    Test__Expect_EQ(true, tgCN_Var_Set_F32( tiVarTest_0, 3 ));
    Test__Expect_EQ(true, tgCN_Var_Query_F32( (TgFLOAT32_P)uiData, tiVarTest_0 ));
    Test__Expect_EQ(true, *(TgFLOAT32_P)uiData == 3);

    Test__Expect_EQ(true, tgCN_Var_Set_F32( tiVarTest_0, 4 ));

    tiVarTest_1 = tgCN_Var_Query_Id( u8"Var_Query_Query_Id", KTgMAX_RSIZE );
    Test__Expect_EQ(true, tgCN_Var_Query_F32( (TgFLOAT32_P)uiData, tiVarTest_1 ));
    Test__Expect_EQ(true, *(TgFLOAT32_P)uiData == 4);

    TEST_END_METHOD( KTgS_OK );
}
