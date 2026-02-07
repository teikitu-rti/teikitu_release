/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common [Unit Test] [Test] - Base - Type [IO].c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Common ===================================================================================================================================================================== */
/* MARK: Unit Test Complete 00D008E0-5616-4AAF-8989-24865B450F52                                                                                                                   */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TEST_METHOD( UNIT_TEST__TEST__IO_IM_Open );
TEST_METHOD( UNIT_TEST__TEST__IO_IM_Close );
TEST_METHOD( UNIT_TEST__TEST__IO_IM_Size );
TEST_METHOD( UNIT_TEST__TEST__IO_IM_Read );
TEST_METHOD( UNIT_TEST__TEST__IO_IM_End_Of_File );
TEST_METHOD( UNIT_TEST__TEST__IO_OM_Open );
TEST_METHOD( UNIT_TEST__TEST__IO_OM_Close );
TEST_METHOD( UNIT_TEST__TEST__IO_OM_Query_Data );
TEST_METHOD( UNIT_TEST__TEST__IO_OM_Write );
TEST_METHOD( UNIT_TEST__TEST__IO_Read_Line_NSZ );
TEST_METHOD( UNIT_TEST__TEST__IO_Read_Line_WSZ );
TEST_METHOD( UNIT_TEST__TEST__IO_Read_Line );
TEST_METHOD( UNIT_TEST__TEST__IO_Print_NSZ );
TEST_METHOD( UNIT_TEST__TEST__IO_Print_WSZ );
TEST_METHOD( UNIT_TEST__TEST__IO_Print );
TEST_METHOD( UNIT_TEST__TEST__IO_PrintF_NSZ );
TEST_METHOD( UNIT_TEST__TEST__IO_PrintF_WSZ );
TEST_METHOD( UNIT_TEST__TEST__IO_PrintF );
TEST_METHOD( UNIT_TEST__TEST__CM_DBG_ERR_Write_Byte );
TEST_METHOD( UNIT_TEST__TEST__CM_DBG_ERR_Write );
TEST_METHOD( UNIT_TEST__TEST__CM_DBG_OUT_Write_Byte );
TEST_METHOD( UNIT_TEST__TEST__CM_DBG_OUT_Write );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- UNIT_TEST__TEST__Base_Type_IO -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( UNIT_TEST__TEST__Base_Type_IO )
{
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__IO_IM_Open());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__IO_IM_Close());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__IO_IM_Size());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__IO_IM_Read());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__IO_IM_End_Of_File());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__IO_OM_Open());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__IO_OM_Close());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__IO_OM_Query_Data());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__IO_OM_Write());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__IO_Read_Line_NSZ());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__IO_Read_Line_WSZ());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__IO_Read_Line());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__IO_Print_NSZ());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__IO_Print_WSZ());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__IO_Print());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__IO_PrintF_NSZ());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__IO_PrintF_WSZ());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__IO_PrintF());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_DBG_ERR_Write_Byte());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_DBG_ERR_Write());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_DBG_OUT_Write_Byte());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_DBG_OUT_Write());

    TEST_END_METHOD( KTgS_OK );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- UNIT_TEST__TEST__IO_IM_Open ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgCLANG_WARN_DISABLE_PUSH(nonnull)
TEST_METHOD( UNIT_TEST__TEST__IO_IM_Open )
{
    TgUINT_E32                          uiDefault_Break;
    TgUINT_E32                          uiSeverity;
    STg2_Input_MEM                      tgIN_MEM;
    TgUINT_E08                          uiBuffer[11];

    uiDefault_Break = tgCN_Remove_Default_Break( KTgCN_CHANEL_ERROR );
    uiSeverity = tgCN_Set_Severity_Filter( KTgCN_CHANEL_ERROR, 0 );
    Test__Expect_NE(KTgS_OK, tgIO_IM__Open( &tgIN_MEM, nullptr, 0, nullptr ));
    Test__Expect_NE(KTgS_OK, tgIO_IM__Open( &tgIN_MEM, nullptr, 1, nullptr ));
    Test__Expect_NE(KTgS_OK, tgIO_IM__Open( &tgIN_MEM, nullptr, KTgMAX_RSIZE, nullptr ));
    Test__Expect_NE(KTgS_OK, tgIO_IM__Open( &tgIN_MEM, uiBuffer, KTgMAX_RSIZE, nullptr ));
    tgCN_Set_Severity_Filter( KTgCN_CHANEL_ERROR, uiSeverity );
    if (!uiDefault_Break)
    {
        tgCN_Attach_Default_Break( KTgCN_CHANEL_ERROR );
    };
    Test__Expect_EQ(KTgS_OK, tgIO_IM__Open( &tgIN_MEM, uiBuffer, sizeof uiBuffer, nullptr ));

    TEST_END_METHOD( KTgS_OK );
}
TgCLANG_WARN_DISABLE_POP()


/* ---- UNIT_TEST__TEST__IO_IM_Close --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__IO_IM_Close )
{
    STg2_Input_MEM                      tgIN_MEM;
    TgUINT_E08                          uiBuffer[11];

    tgMM_Set_U08_0x00( &tgIN_MEM, sizeof tgIN_MEM );
    Test__Expect_NE(KTgS_OK, tgIO_IM__Close( &tgIN_MEM.m_sInput ));

    Test__Expect_EQ(KTgS_OK, tgIO_IM__Open( &tgIN_MEM, uiBuffer, sizeof uiBuffer, nullptr ));
    Test__Expect_EQ(KTgS_OK, tgIO_IM__Close( &tgIN_MEM.m_sInput ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__IO_IM_Size ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__IO_IM_Size )
{
    STg2_Input_MEM                      tgIN_MEM;
    TgUINT_E08                          uiBuffer[11];

    tgMM_Set_U08_0x00( &tgIN_MEM, sizeof tgIN_MEM );

    Test__Expect_EQ(KTgS_OK, tgIO_IM__Open( &tgIN_MEM, uiBuffer, sizeof uiBuffer, nullptr ));
    Test__Expect_EQ(sizeof uiBuffer, tgIO_IM__Size( &tgIN_MEM ));
    Test__Expect_EQ(KTgS_OK, tgIO_IM__Close( &tgIN_MEM.m_sInput ) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__IO_IM_Read ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__IO_IM_Read )
{
    STg2_Input_MEM                      tgIN_MEM;
    TgUINT_E08                          uiBuffer[11] = { 0,1,2,3,4,5,6,7,8,9,10 };
    TgUINT_E08                          uiTest_0[11], uiTest_1[11];
    TgRSIZE                             uiPos;

    tgMM_Set_U08_0x00( &tgIN_MEM, sizeof tgIN_MEM );

    Test__Expect_EQ(KTgS_OK, tgIO_IM__Open( &tgIN_MEM, uiBuffer, sizeof uiBuffer, nullptr ));
    uiPos = 0;

    /* Test reading one byte */
    tgMM_Set_U08_0xFF( uiTest_0, sizeof uiTest_0 );
    Test__Expect_EQ(1, uiPos += tgIO_IM__Read( uiTest_0, sizeof(uiTest_0), (STg2_Input_P)&tgIN_MEM, uiPos, 1));
    Test__Expect_EQ(0u, uiTest_0[0]);

    /* Test reading nine bytes (after an existing read) */
    tgMM_Set_U08_0xFF( uiTest_1, sizeof uiTest_1 );
    Test__Expect_EQ(10, uiPos += tgIO_IM__Read( uiTest_1, sizeof(uiTest_0), (STg2_Input_P)&tgIN_MEM, uiPos, 9));
    Test__Expect_EQ(0, memcmp( uiTest_1, uiBuffer + 1, 9 ));

    Test__Expect_EQ(KTgS_OK, tgIO_IM__Close( &tgIN_MEM.m_sInput ) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__IO_IM_End_Of_File --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__IO_IM_End_Of_File )
{
    STg2_Input_MEM                      tgIN_MEM;
    TgUINT_E08                          uiBuffer[11] = { 0,1,2,3,4,5,6,7,8,9,10 };
    TgUINT_E08                          uiTest[11];
    TgRSIZE                             uiPos;

    tgMM_Set_U08_0x00( &tgIN_MEM, sizeof tgIN_MEM );

    Test__Expect_EQ(KTgS_OK, tgIO_IM__Open( &tgIN_MEM, uiBuffer, sizeof uiBuffer, nullptr ));
    uiPos = 0;

    /* Test end of file determination */
    Test__Expect_EQ(false, tgIO_IM__End_Of_File( (STg2_Input_P)&tgIN_MEM, uiPos ));
    
    Test__Expect_EQ(5, uiPos += tgIO_IM__Read( uiTest, sizeof(uiTest), (STg2_Input_P)&tgIN_MEM, uiPos, 5 ));
    Test__Expect_EQ(false, tgIO_IM__End_Of_File( (STg2_Input_P)&tgIN_MEM, uiPos ));

    Test__Expect_EQ(11, uiPos += tgIO_IM__Read( uiTest, sizeof(uiTest), (STg2_Input_P)&tgIN_MEM, uiPos, 6 ));
    Test__Expect_NE(false, tgIO_IM__End_Of_File( (STg2_Input_P)&tgIN_MEM, uiPos ));

    /* Test seeking (after EOF) */
    Test__Expect_EQ(11, uiPos += tgIO_IM__Read( uiTest, sizeof(uiTest), (STg2_Input_P)&tgIN_MEM, uiPos, 1 ));
    Test__Expect_NE(false, tgIO_IM__End_Of_File( (STg2_Input_P)&tgIN_MEM, uiPos ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__IO_OM_Open ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgCLANG_WARN_DISABLE_PUSH(nonnull)
TEST_METHOD( UNIT_TEST__TEST__IO_OM_Open )
{
    TgUINT_E32                          uiDefault_Break;
    TgUINT_E32                          uiSeverity;
    STg2_Output_MEM                     tgOUT_MEM;
    TgUINT_E08                          uiBuffer[11];

    uiDefault_Break = tgCN_Remove_Default_Break( KTgCN_CHANEL_ERROR );
    uiSeverity = tgCN_Set_Severity_Filter( KTgCN_CHANEL_ERROR, 0 );
    Test__Expect_NE(KTgS_OK, tgIO_OM__Open( &tgOUT_MEM, nullptr, 0, nullptr ));
    Test__Expect_NE(KTgS_OK, tgIO_OM__Open( &tgOUT_MEM, nullptr, 1, nullptr ));
    Test__Expect_NE(KTgS_OK, tgIO_OM__Open( &tgOUT_MEM, nullptr, KTgMAX_RSIZE, nullptr ));
    Test__Expect_NE(KTgS_OK, tgIO_OM__Open( &tgOUT_MEM, uiBuffer, KTgMAX_RSIZE, nullptr ));
    tgCN_Set_Severity_Filter( KTgCN_CHANEL_ERROR, uiSeverity );
    if (!uiDefault_Break)
    {
        tgCN_Attach_Default_Break( KTgCN_CHANEL_ERROR );
    };
    Test__Expect_EQ(KTgS_OK, tgIO_OM__Open( &tgOUT_MEM, uiBuffer, sizeof uiBuffer, nullptr ));

    TEST_END_METHOD( KTgS_OK );
}
TgCLANG_WARN_DISABLE_POP()


/* ---- UNIT_TEST__TEST__IO_OM_Close --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__IO_OM_Close )
{
    STg2_Output_MEM                     tgOUT_MEM;
    TgUINT_E08                          uiBuffer[11];

    tgMM_Set_U08_0x00( &tgOUT_MEM, sizeof tgOUT_MEM );
    Test__Expect_NE( KTgS_OK, tgIO_OM__Close( &tgOUT_MEM.m_sOutput ) );

    Test__Expect_EQ(KTgS_OK, tgIO_OM__Open( &tgOUT_MEM, uiBuffer, sizeof uiBuffer, nullptr ));
    Test__Expect_EQ(KTgS_OK, tgIO_OM__Close( &tgOUT_MEM.m_sOutput ) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__IO_OM_Query_Data ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__IO_OM_Query_Data )
{
    STg2_Output_MEM                     tgOUT_MEM;
    TgUINT_E08                          uiBuffer[11];

    tgMM_Set_U08_0x00( &tgOUT_MEM, sizeof tgOUT_MEM );

    Test__Expect_EQ(KTgS_OK, tgIO_OM__Open( &tgOUT_MEM, uiBuffer, sizeof uiBuffer, nullptr ));
    Test__Expect_EQ(uiBuffer, tgIO_OM__Query_Data( &tgOUT_MEM ));
    Test__Expect_EQ(KTgS_OK, tgIO_OM__Close( &tgOUT_MEM.m_sOutput ) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__IO_OM_Write --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__IO_OM_Write )
{
    STg2_Output_MEM                     tgOUT_MEM;
    TgUINT_E08                          uiTest[] = { 0,1,2,3,4,5,6,7,8,9,10 };
    TgUINT_E08                          uiBuffer[11];

    tgMM_Set_U08_0x00( &tgOUT_MEM, sizeof tgOUT_MEM );
    tgMM_Set_U08_0x00( uiBuffer, sizeof uiBuffer );

    Test__Expect_EQ(KTgS_OK, tgIO_OM__Open( &tgOUT_MEM, uiBuffer, sizeof uiBuffer, nullptr ));
    Test__Expect_EQ(9, tgIO_OM__Write( (STg2_Output_P)&tgOUT_MEM, 0, uiTest, 9 ));
    Test__Expect_EQ(KTgS_OK, tgIO_OM__Close( &tgOUT_MEM.m_sOutput ) );
    Test__Expect_EQ(0, memcmp( uiTest, uiBuffer, 9 ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__IO_Read_Line_NSZ ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__IO_Read_Line_NSZ )
{
    STg2_Input_MEM                      tgIN_MEM;
    TgCHAR_NC                           nczBuffer[] = "2468\nABCD";
    TgCHAR_NC                           nczTest[16];

    tgMM_Set_U08_0x00( &tgIN_MEM, sizeof tgIN_MEM );

    Test__Expect_EQ(KTgS_OK, tgIO_IM__Open( &tgIN_MEM, nczBuffer, sizeof nczBuffer, nullptr ));

    Test__Expect_EQ(5, tgIO_Read_Line_NSZ( nczTest, sizeof nczTest, (STg2_Input_P)&tgIN_MEM, 0 ));
    Test__Expect_EQ(0, memcmp( nczTest, "2468\n", 6 ));

    Test__Expect_EQ(4, tgIO_Read_Line_NSZ( nczTest, sizeof nczTest, (STg2_Input_P)&tgIN_MEM, 1 ));
    Test__Expect_EQ(0, memcmp( nczTest, "468\n", 5 ));

    Test__Expect_EQ(1, tgIO_Read_Line_NSZ( nczTest, sizeof nczTest, (STg2_Input_P)&tgIN_MEM, 4 ));
    Test__Expect_EQ(0, memcmp( nczTest, "\n", 2 ));

    Test__Expect_EQ(4, tgIO_Read_Line_NSZ( nczTest, sizeof nczTest, (STg2_Input_P)&tgIN_MEM, 5 ));
    Test__Expect_EQ(0, memcmp( nczTest, "ABCD", 5 ));

    Test__Expect_EQ(3, tgIO_Read_Line_NSZ( nczTest, sizeof nczTest, (STg2_Input_P)&tgIN_MEM, 6 ));
    Test__Expect_EQ(0, memcmp( nczTest, "BCD", 4 ));

    Test__Expect_EQ(KTgS_OK, tgIO_IM__Close( &tgIN_MEM.m_sInput ) );
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__IO_Read_Line_WSZ ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__IO_Read_Line_WSZ )
{
    STg2_Input_MEM                      tgIN_MEM;
    TgCHAR_WC                           wczBuffer[] = KTgWC_LIT_TEST__ENGLISH L"\n" KTgWC_LIT_TEST__BURMESE L"\n" KTgWC_LIT_TEST__JAPANESE;
    TgCHAR_WC                           wczResult_0[] = KTgWC_LIT_TEST__ENGLISH L"\n";
    TgCHAR_WC                           wczResult_1[] = KTgWC_LIT_TEST__BURMESE L"\n";
    TgCHAR_WC                           wczResult_2[] = KTgWC_LIT_TEST__JAPANESE;
    TgCHAR_WC                           wczTest[32];
    TgRSIZE                             uiPos;

    tgMM_Set_U08_0x00( &tgIN_MEM, sizeof tgIN_MEM );

    Test__Expect_EQ(KTgS_OK, tgIO_IM__Open( &tgIN_MEM, wczBuffer, sizeof wczBuffer, nullptr ));

    uiPos = 0;
    Test__Expect_EQ(sizeof wczResult_0 - 1*sizeof ( TgCHAR_WC ), tgIO_Read_Line_WSZ( wczTest, sizeof wczTest, (STg2_Input_P)&tgIN_MEM, uiPos ));
    Test__Expect_EQ(0, memcmp( wczTest, wczResult_0, sizeof wczResult_0 ));

    uiPos += 1*sizeof( TgCHAR_WC );
    Test__Expect_EQ(sizeof wczResult_0 - 2*sizeof ( TgCHAR_WC ), tgIO_Read_Line_WSZ( wczTest, sizeof wczTest, (STg2_Input_P)&tgIN_MEM, uiPos ));
    Test__Expect_EQ(0, memcmp( wczTest, wczResult_0 + 1, (sizeof wczResult_0) - 1*sizeof( TgCHAR_WC ) ));

    uiPos += sizeof( wczResult_0 ) - 3*sizeof( TgCHAR_WC );
    Test__Expect_EQ(sizeof ( TgCHAR_WC ), tgIO_Read_Line_WSZ( wczTest, sizeof wczTest, (STg2_Input_P)&tgIN_MEM, uiPos ));
    Test__Expect_EQ(0, memcmp( wczTest, "\n", 2 ));

    uiPos += 1*sizeof( TgCHAR_WC );
    Test__Expect_EQ(sizeof wczResult_1 - 1*sizeof ( TgCHAR_WC ), tgIO_Read_Line_WSZ( wczTest, sizeof wczTest, (STg2_Input_P)&tgIN_MEM, uiPos ));
    Test__Expect_EQ(0, memcmp( wczTest, wczResult_1, sizeof wczResult_1 ));

    uiPos += 1*sizeof( TgCHAR_WC );
    Test__Expect_EQ(sizeof wczResult_1 - 2*sizeof ( TgCHAR_WC ), tgIO_Read_Line_WSZ( wczTest, sizeof wczTest, (STg2_Input_P)&tgIN_MEM, uiPos ));
    Test__Expect_EQ(0, memcmp( wczTest, wczResult_1 + 1, (sizeof wczResult_1)- 1*sizeof ( TgCHAR_WC ) ));

    uiPos += sizeof( wczResult_1 ) - 2*sizeof( TgCHAR_WC );
    Test__Expect_EQ(sizeof wczResult_2 - 1*sizeof ( TgCHAR_WC ), tgIO_Read_Line_WSZ( wczTest, sizeof wczTest, (STg2_Input_P)&tgIN_MEM, uiPos ));
    Test__Expect_EQ(0, memcmp( wczTest, wczResult_2, sizeof wczResult_2 ));

    Test__Expect_EQ(KTgS_OK, tgIO_IM__Close( &tgIN_MEM.m_sInput ) );
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__IO_Read_Line -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__IO_Read_Line )
{
    STg2_Input_MEM                      tgIN_MEM;
    TgCHAR_U8                           mbzBuffer[] = KTgU8_LIT_TEST__ENGLISH u8"\n" KTgU8_LIT_TEST__BURMESE u8"\n" KTgU8_LIT_TEST__JAPANESE;
    TgCHAR_U8                           mbzResult_0[] = KTgU8_LIT_TEST__ENGLISH u8"\n";
    TgCHAR_U8                           mbzResult_1[] = KTgU8_LIT_TEST__BURMESE u8"\n";
    TgCHAR_U8                           mbzResult_2[] = KTgU8_LIT_TEST__JAPANESE;
    TgCHAR_U8                           mbzTest[64];
    TgRSIZE                             uiPos;

    tgMM_Set_U08_0x00( &tgIN_MEM, sizeof tgIN_MEM );

    Test__Expect_EQ(KTgS_OK, tgIO_IM__Open( &tgIN_MEM, mbzBuffer, sizeof mbzBuffer, nullptr ));

    uiPos = 0;
    Test__Expect_EQ(sizeof mbzResult_0 - 1, tgIO_Read_Line( mbzTest, sizeof mbzTest, (STg2_Input_P)&tgIN_MEM, uiPos ));
    Test__Expect_EQ(0, memcmp( mbzTest, mbzResult_0, sizeof mbzResult_0 ));

    uiPos += 1;
    Test__Expect_EQ(sizeof mbzResult_0 - 2, tgIO_Read_Line( mbzTest, sizeof mbzTest, (STg2_Input_P)&tgIN_MEM, uiPos ));
    Test__Expect_EQ(0, memcmp( mbzTest, mbzResult_0 + 1, (sizeof mbzResult_0) - 1*sizeof( TgCHAR_WC ) ));

    uiPos += sizeof( mbzResult_0 ) - 3;
    Test__Expect_EQ(1, tgIO_Read_Line( mbzTest, sizeof mbzTest, (STg2_Input_P)&tgIN_MEM, uiPos ));
    Test__Expect_EQ(0, memcmp( mbzTest, "\n", 2 ));

    uiPos += 1;
    Test__Expect_EQ(sizeof mbzResult_1 - 1, tgIO_Read_Line( mbzTest, sizeof mbzTest, (STg2_Input_P)&tgIN_MEM, uiPos ));
    Test__Expect_EQ(0, memcmp( mbzTest, mbzResult_1, sizeof mbzResult_1 ));

    uiPos += 3;
    Test__Expect_EQ(sizeof mbzResult_1 - 4, tgIO_Read_Line( mbzTest, sizeof mbzTest, (STg2_Input_P)&tgIN_MEM, uiPos ));
    Test__Expect_EQ(0, memcmp( mbzTest, mbzResult_1 + 3, (sizeof mbzResult_1) - 4 ));

    uiPos += sizeof( mbzResult_1 ) - 4;
    Test__Expect_EQ(sizeof mbzResult_2 - 1, tgIO_Read_Line( mbzTest, sizeof mbzTest, (STg2_Input_P)&tgIN_MEM, uiPos ));
    Test__Expect_EQ(0, memcmp( mbzTest, mbzResult_2, sizeof mbzResult_2 ));

    Test__Expect_EQ(KTgS_OK, tgIO_IM__Close( &tgIN_MEM.m_sInput ) );
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__IO_Print_NSZ -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__IO_Print_NSZ )
{
    STg2_Output_MEM                     tgOUT_MEM;
    TgCHAR_NC                           nczBuffer[] = KTgNC_LIT_TEST__ENGLISH "\n";
    TgCHAR_NC                           nczTest[] = KTgNC_LIT_TEST__ENGLISH "\n";

    tgMM_Set_U08_0x00( &tgOUT_MEM, sizeof tgOUT_MEM );
    tgMM_Set_U08_0x00( nczBuffer, sizeof nczBuffer );

    Test__Expect_EQ(KTgS_OK, tgIO_OM__Open( &tgOUT_MEM, nczBuffer, sizeof nczBuffer, nullptr ));

    tgOUT_MEM.m_nbyData_Current = 0;
    Test__Expect_EQ(sizeof nczTest -1 , tgIO_Print_NSZ( (STg2_Output_P)&tgOUT_MEM, nczTest, sizeof nczTest ));
    Test__Expect_EQ(0, memcmp( nczBuffer, nczTest, sizeof nczTest ));

    Test__Expect_EQ(KTgS_OK, tgIO_OM__Close( &tgOUT_MEM.m_sOutput ) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__IO_Print_WSZ -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__IO_Print_WSZ )
{
    STg2_Output_MEM                     tgOUT_MEM;
    TgCHAR_WC                           wczBuffer[] = KTgWC_LIT_TEST__BURMESE L"\n";
    TgCHAR_WC                           wczTest[] = KTgWC_LIT_TEST__BURMESE L"\n";

    tgMM_Set_U08_0x00( &tgOUT_MEM, sizeof tgOUT_MEM );
    tgMM_Set_U08_0x00( wczBuffer, sizeof wczBuffer );

    Test__Expect_EQ(KTgS_OK, tgIO_OM__Open( &tgOUT_MEM, wczBuffer, sizeof wczBuffer, nullptr ));

    tgOUT_MEM.m_nbyData_Current = 0;
    Test__Expect_EQ(sizeof wczTest - sizeof( TgCHAR_WC ), tgIO_Print_WSZ( (STg2_Output_P)&tgOUT_MEM, wczTest, sizeof wczTest ));
    Test__Expect_EQ(0, memcmp( wczBuffer, wczTest, sizeof wczTest ));

    Test__Expect_EQ(KTgS_OK, tgIO_OM__Close( &tgOUT_MEM.m_sOutput ) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__IO_Print ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__IO_Print )
{
    STg2_Output_MEM                     tgOUT_MEM;
    TgCHAR_U8                           mbzBuffer[] = KTgU8_LIT_TEST__JAPANESE u8"\n" KTgU8_LIT_TEST__KOREAN;
    TgCHAR_U8                           mbzTest[] = KTgU8_LIT_TEST__JAPANESE u8"\n" KTgU8_LIT_TEST__KOREAN;

    tgMM_Set_U08_0x00( &tgOUT_MEM, sizeof tgOUT_MEM );
    tgMM_Set_U08_0x00( mbzBuffer, sizeof mbzBuffer );

    Test__Expect_EQ(KTgS_OK, tgIO_OM__Open( &tgOUT_MEM, mbzBuffer, sizeof mbzBuffer, nullptr ));

    tgOUT_MEM.m_nbyData_Current = 0;
    Test__Expect_EQ(sizeof mbzTest - 1, tgIO_Print( (STg2_Output_P)&tgOUT_MEM, mbzTest, sizeof mbzTest ));
    Test__Expect_EQ(0, memcmp( mbzBuffer, mbzTest, sizeof mbzTest ));

    Test__Expect_EQ(KTgS_OK, tgIO_OM__Close( &tgOUT_MEM.m_sOutput ) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__IO_PrintF_NSZ ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__IO_PrintF_NSZ )
{
    STg2_Output_MEM                     tgOUT_MEM;
    TgCHAR_NC                           nczBuffer[] = KTgNC_LIT_TEST__ENGLISH "\n";
    TgCHAR_NC                           nczTest[] = KTgNC_LIT_TEST__ENGLISH "\n";

    tgMM_Set_U08_0x00( &tgOUT_MEM, sizeof tgOUT_MEM );
    tgMM_Set_U08_0x00( nczBuffer, sizeof nczBuffer );

    Test__Expect_EQ(KTgS_OK, tgIO_OM__Open( &tgOUT_MEM, nczBuffer, sizeof nczBuffer, nullptr ));

    tgOUT_MEM.m_nbyData_Current = 0;
    Test__Expect_EQ(sizeof nczTest - 1, tgIO_PrintF_NSZ( (STg2_Output_P)&tgOUT_MEM, "%s", nczTest ));
    Test__Expect_EQ(0, memcmp( nczBuffer, nczTest, sizeof nczTest ));

    Test__Expect_EQ(KTgS_OK, tgIO_OM__Close( &tgOUT_MEM.m_sOutput ) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__IO_PrintF_WSZ ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__IO_PrintF_WSZ )
{
    STg2_Output_MEM                     tgOUT_MEM;
    TgCHAR_WC                           wczBuffer[] = KTgWC_LIT_TEST__BURMESE L"\n";
    TgCHAR_WC                           wczTest[] = KTgWC_LIT_TEST__BURMESE L"\n";

    tgMM_Set_U08_0x00( &tgOUT_MEM, sizeof tgOUT_MEM );
    tgMM_Set_U08_0x00( wczBuffer, sizeof wczBuffer );

    Test__Expect_EQ(KTgS_OK, tgIO_OM__Open( &tgOUT_MEM, wczBuffer, sizeof wczBuffer, nullptr ));

    tgOUT_MEM.m_nbyData_Current = 0;
    Test__Expect_EQ(sizeof wczTest - sizeof( TgCHAR_WC ), tgIO_PrintF_WSZ( (STg2_Output_P)&tgOUT_MEM, L"%ls", wczTest ));
    Test__Expect_EQ(0, memcmp( wczBuffer, wczTest, sizeof wczTest ));

    Test__Expect_EQ(KTgS_OK, tgIO_OM__Close( &tgOUT_MEM.m_sOutput ) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__IO_PrintF ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__IO_PrintF )
{
    STg2_Output_MEM                     tgOUT_MEM;
    TgCHAR_U8                           mbzBuffer[] = KTgU8_LIT_TEST__JAPANESE u8"\n" KTgU8_LIT_TEST__KOREAN;
    TgCHAR_U8                           mbzTest[] = KTgU8_LIT_TEST__JAPANESE u8"\n" KTgU8_LIT_TEST__KOREAN;

    tgMM_Set_U08_0x00( &tgOUT_MEM, sizeof tgOUT_MEM );
    tgMM_Set_U08_0x00( mbzBuffer, sizeof mbzBuffer );

    Test__Expect_EQ(KTgS_OK, tgIO_OM__Open( &tgOUT_MEM, mbzBuffer, sizeof mbzBuffer, nullptr ));

    tgOUT_MEM.m_nbyData_Current = 0;
    Test__Expect_EQ(sizeof mbzTest - 1, tgIO_PrintF( (STg2_Output_P)&tgOUT_MEM, u8"%s", mbzTest ));
    Test__Expect_EQ(0, memcmp( mbzBuffer, mbzTest, sizeof mbzTest ));

    Test__Expect_EQ(KTgS_OK, tgIO_OM__Close( &tgOUT_MEM.m_sOutput ) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_DBG_ERR_Write_Byte ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_DBG_ERR_Write_Byte )
{
    tgCM_DBG_ERR_Write_Byte( nullptr, 0, 0 );
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_DBG_ERR_Write ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_DBG_ERR_Write )
{
    tgCM_DBG_ERR_Write( nullptr, 0, nullptr, 0 );
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_DBG_OUT_Write_Byte ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_DBG_OUT_Write_Byte )
{
    tgCM_DBG_OUT_Write_Byte( nullptr, 0, 0 );
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_DBG_OUT_Write ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_DBG_OUT_Write )
{
    tgCM_DBG_OUT_Write( nullptr, 0, nullptr, 0 );
    TEST_END_METHOD( KTgS_OK );
}
