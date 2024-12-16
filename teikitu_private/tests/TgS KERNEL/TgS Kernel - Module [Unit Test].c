/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Kernel - Module [Unit Test].c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TEST_METHOD( UNIT_TEST__TEST__KN_Notify );
TEST_METHOD( UNIT_TEST__TEST__KN_File_BL );
TEST_METHOD( UNIT_TEST__TEST__KN_File_JB );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

static TgVOID
tgUnit_Test__KN_Notify_Func(
    TgUINT_PTR_C uiParam, TgUINT_E64_C uiParam0, TgUINT_E64_C uiParam1 ) TgATTRIBUTE_NO_EXCEPT;

static TgVOID
tgUnit_Test__KN_File_Job_Write_Callback(
    STg2_KN_File_Write_Command_PCU ) TgATTRIBUTE_NO_EXCEPT;

static TgVOID
tgUnit_Test__KN_File_Job_Read_Callback(
    STg2_KN_File_Read_Command_PCU ) TgATTRIBUTE_NO_EXCEPT;

static Test_Set                             s_sSET__KERNEL;
static Test_Case                            s_sCASE__Kernel_Base;
static Test_Case                            s_sCASE__Kernel_File;

static TgSINT_E32                           g_iUnit_Test__KN_Notify_Signal;




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgCM_Unit_Test_Register_KERNEL ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgCM_Unit_Test_Register_KERNEL( TgVOID )
{
    /* Initialize the unit test structures */

    Unit_Test__Set_Init( &s_sSET__KERNEL );
    Unit_Test__Case_Init( &s_sCASE__Kernel_Base );
    Unit_Test__Case_Init( &s_sCASE__Kernel_File );



    /* Configure the test set */

    s_sSET__KERNEL.m_szSet = u8"Kernel";



    /* Configure the test cases */

    s_sCASE__Kernel_Base.m_pszSet = s_sSET__KERNEL.m_szSet;
    s_sCASE__Kernel_Base.m_pszCase = u8"Base";
    s_sCASE__Kernel_Base.m_pfnTest[0] = UNIT_TEST__TEST__KN_Notify;
    s_sCASE__Kernel_Base.m_apszTest[0] = u8"Notify";

    s_sCASE__Kernel_File.m_pszSet = s_sSET__KERNEL.m_szSet;
    s_sCASE__Kernel_File.m_pszCase = u8"File";
    s_sCASE__Kernel_File.m_pfnTest[0] = UNIT_TEST__TEST__KN_File_BL;
    s_sCASE__Kernel_File.m_apszTest[0] = u8"File Blocking";
    s_sCASE__Kernel_File.m_pfnTest[1] = UNIT_TEST__TEST__KN_File_JB;
    s_sCASE__Kernel_File.m_apszTest[1] = u8"File Job-Based";



    /* Register all of the test cases with the test set */
    Unit_Test__Set_Register_Case( &s_sSET__KERNEL, &s_sCASE__Kernel_Base );
    Unit_Test__Set_Register_Case( &s_sSET__KERNEL, &s_sCASE__Kernel_File );

    /* Register the test set with the unit test system */

    Unit_Test__Register( &s_sSET__KERNEL );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- UNIT_TEST__TEST__KN_Notify ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__KN_Notify )
{
    TgKN_NOTIFY_ID                      tiNotify;

    g_iUnit_Test__KN_Notify_Signal = 0;
    tiNotify = tgKN_Notify_Start( tgUnit_Test__KN_Notify_Func, 0xbad00c0ffee00000ULL, 0xdeadbeaf );
    Test__Expect_EQ(true, KTgKN_NOTIFY_ID__INVALID.m_uiKI != tiNotify.m_uiKI);
    Test__Expect_EQ( KTgS_OK, tgKN_Notify_MSG( 0xdeadbeaf, 0xbadfece5, 0xc00010ff ) );
    Test__Expect_EQ( 1, g_iUnit_Test__KN_Notify_Signal );
    Test__Expect_EQ( KTgS_OK, tgKN_Notify_End( tiNotify ) );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__KN_File_IO ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__KN_File_BL )
{
    STg2_KN_File_Open_Command           sOpen_Command;
    STg2_KN_File_Cache_Command          sCache_Command;
    STg2_KN_File_Read_Command           sRead_Command;
    STg2_KN_File_Write_Command          sWrite_Command;
    TgCHAR_U8                           szBuffer[] = u8"This is the contents of the file test.";

    sOpen_Command.m_tiFS_Mount = g_tiKN_FS_HDD__Mount_APP;
    sOpen_Command.m_uiPath = KTgEMPTY_HASH;
    sOpen_Command.m_uiFile = KTgEMPTY_HASH;
    sOpen_Command.m_uiMode = ETgFILE_IO_ACCESS__WRITE | ETgFILE_IO_ACCESS__CREATE;
    sOpen_Command.m_iCache = 0;
    sOpen_Command.m_pszFile_Name = u8"UnitTest_File_Test_Blocking.tst";

    tgMM_Set_U08_0x00( &sWrite_Command, sizeof( sWrite_Command ) );
    sWrite_Command.m_tiFile = tgKN_FS_BL_Open( &sOpen_Command );
    Test__Expect_EQ(true, KTgKN_FILE_ID__INVALID.m_uiKI != sWrite_Command.m_tiFile.m_uiKI);
    sWrite_Command.m_pBuffer = szBuffer;
    sWrite_Command.m_nuiBuffer = TgARRAY_COUNT( szBuffer ) * sizeof( TgCHAR_U8 );
    Test__Expect_EQ(KTgS_OK, tgKN_FS_BL_Write( &sWrite_Command ));
    //tgKN_FS_BL_Flush
    Test__Expect_EQ(KTgS_OK, tgKN_FS_BL_Close( sWrite_Command.m_tiFile ));

    /* Validate that the number of bytes written is the same as the number of bytes in the buffer. */
    Test__Expect_EQ( sWrite_Command.m_nuiBuffer, sWrite_Command.m_nuiResult );

    sOpen_Command.m_uiMode = ETgFILE_IO_ACCESS__READ;
    tgUSZ_Hash( &sOpen_Command.m_uiFile, sOpen_Command.m_pszFile_Name, KTgMAX_RSIZE );
    sOpen_Command.m_pszFile_Name = nullptr;

    tgMM_Set_U08_0x00( &sRead_Command, sizeof( sRead_Command ) );
    sRead_Command.m_tiFile = tgKN_FS_BL_Open( &sOpen_Command );
    sRead_Command.m_pfnAllocator = tgKN_FILE_ALLOCATOR__Default_Malloc_Pool;
    Test__Expect_EQ(true, KTgKN_FILE_ID__INVALID.m_uiKI != sRead_Command.m_tiFile.m_uiKI);
    Test__Expect_EQ(KTgS_OK, tgKN_FS_BL_Read( &sRead_Command ));
    Test__Expect_EQ(KTgS_OK, tgKN_FS_BL_Close( sRead_Command.m_tiFile ));

    Test__Expect_EQ(0, memcmp( sRead_Command.m_pBuffer, szBuffer, sWrite_Command.m_nuiBuffer ));
    TgFREE_POOL( sRead_Command.m_pBuffer );

    tgMM_Set_U08_0x00( &sCache_Command, sizeof( sCache_Command ) );
    sRead_Command.m_tiFile = tgKN_FS_BL_Open( &sOpen_Command );
    Test__Expect_EQ(true, KTgKN_FILE_ID__INVALID.m_uiKI != sRead_Command.m_tiFile.m_uiKI);
    //tgKN_FS_BL_Cache
    Test__Expect_EQ(KTgS_OK, tgKN_FS_BL_Close( sRead_Command.m_tiFile ));

#if TgS_STAT__COMMON
#endif

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__KN_File_JB ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__KN_File_JB )
{
    STg2_KN_File_Open_Command           sOpen_Command;
    STg2_KN_File_Cache_Command          sCache_Command;
    STg2_KN_File_Read_Command           sRead_Command;
    STg2_KN_File_Write_Command          sWrite_Command;
    TgCHAR_U8                           szBuffer[] = u8"This is the contents of the file test.";
    TgKN_FILE_JOB_ID                    tiFile_Job;
    union
    {
        STg2_KN_File_Read_Command_P     psRead;
        STg2_KN_File_Write_Command_P    psWrite;
        TgUINT_PTR                      uiPTR;
    }                                   sAlias_PTR;

    //tgKN_FS_JB_Cancel( KTgKN_FILE_JOB_ID__INVALID );

    sOpen_Command.m_tiFS_Mount = g_tiKN_FS_HDD__Mount_APP;
    sOpen_Command.m_uiPath = KTgEMPTY_HASH;
    sOpen_Command.m_uiFile = KTgEMPTY_HASH;
    sOpen_Command.m_uiMode = ETgFILE_IO_ACCESS__WRITE | ETgFILE_IO_ACCESS__CREATE;
    sOpen_Command.m_iCache = 0;
    sOpen_Command.m_pszFile_Name = u8"UnitTest_File_Test_Job.tst";

    /* Initialize a write command. */
    tgMM_Set_U08_0x00( &sWrite_Command, sizeof( sWrite_Command ) );
    sWrite_Command.m_tiFile = tgKN_FS_BL_Open( &sOpen_Command );
    Test__Expect_EQ(true, KTgKN_FILE_ID__INVALID.m_uiKI != sWrite_Command.m_tiFile.m_uiKI);
    sWrite_Command.m_pBuffer = szBuffer;
    sWrite_Command.m_nuiBuffer = TgARRAY_COUNT( szBuffer ) * sizeof( TgCHAR_U8 );
    sWrite_Command.m_pfnFinish = tgUnit_Test__KN_File_Job_Write_Callback;
    sAlias_PTR.psWrite = &sWrite_Command;
    sWrite_Command.m_uiParam = sAlias_PTR.uiPTR;

    /* Write the buffer in the command into the open file. */
    tiFile_Job = tgKN_FS_JB_Write( &sWrite_Command );
    Test__Expect_EQ(true, KTgKN_FILE_JOB_ID__INVALID.m_uiKI != tiFile_Job.m_uiKI);
    while (ETgKN_IO_STATUS__INVALID != tgKN_FS_JB_Status(tiFile_Job))
    {};

    //tgKN_FS_JB_Flush

    /* Close the file. */
    tiFile_Job = tgKN_FS_JB_Close( sWrite_Command.m_tiFile );
    Test__Expect_EQ(true, KTgKN_FILE_JOB_ID__INVALID.m_uiKI != tiFile_Job.m_uiKI);
    while (ETgKN_IO_STATUS__INVALID != tgKN_FS_JB_Status(tiFile_Job))
    {};

    /* Validate that the number of bytes written is the same as the number of bytes in the buffer. */
    Test__Expect_EQ( sWrite_Command.m_nuiBuffer, sWrite_Command.m_nuiResult );

    sOpen_Command.m_uiMode = ETgFILE_IO_ACCESS__READ;
    tgUSZ_Hash( &sOpen_Command.m_uiFile, sOpen_Command.m_pszFile_Name, KTgMAX_RSIZE );
    sOpen_Command.m_pszFile_Name = nullptr;

    /* Initialize a read command. */
    tgMM_Set_U08_0x00( &sRead_Command, sizeof( sRead_Command ) );
    sRead_Command.m_tiFile = tgKN_FS_BL_Open( &sOpen_Command );
    sRead_Command.m_pfnAllocator = tgKN_FILE_ALLOCATOR__Default_Malloc_Pool;
    Test__Expect_EQ(true, KTgKN_FILE_ID__INVALID.m_uiKI != sRead_Command.m_tiFile.m_uiKI);
    sRead_Command.m_pfnFinish = tgUnit_Test__KN_File_Job_Read_Callback;
    sAlias_PTR.psRead = &sRead_Command;
    sRead_Command.m_uiParam = sAlias_PTR.uiPTR;

    /* Read the contents of the file we just wrote. */
    tiFile_Job = tgKN_FS_JB_Read( &sRead_Command );
    Test__Expect_EQ(true, KTgKN_FILE_JOB_ID__INVALID.m_uiKI != tiFile_Job.m_uiKI);
    while (ETgKN_IO_STATUS__INVALID != tgKN_FS_JB_Status(tiFile_Job))
    {};

    /* Close the file. */
    tiFile_Job = tgKN_FS_JB_Close( sRead_Command.m_tiFile );
    Test__Expect_EQ(true, KTgKN_FILE_JOB_ID__INVALID.m_uiKI != tiFile_Job.m_uiKI);
    while (ETgKN_IO_STATUS__INVALID != tgKN_FS_JB_Status(tiFile_Job))
    {};

    /* Compare the contents of what we read to the original buffer that was used to write the file. */
    Test__Expect_EQ(0, memcmp( sRead_Command.m_pBuffer, szBuffer, sWrite_Command.m_nuiBuffer ));
    TgFREE_POOL( sRead_Command.m_pBuffer );

    /* Validate that the cache command works. */
    tgMM_Set_U08_0x00( &sCache_Command, sizeof( sCache_Command ) );
    sRead_Command.m_tiFile = tgKN_FS_BL_Open( &sOpen_Command );
    Test__Expect_EQ(true, KTgKN_FILE_ID__INVALID.m_uiKI != sRead_Command.m_tiFile.m_uiKI);
    //tgKN_FS_JB_Cache
    Test__Expect_EQ(KTgS_OK, tgKN_FS_BL_Close( sRead_Command.m_tiFile ));

#if TgS_STAT__COMMON
#endif

    TEST_END_METHOD( KTgS_OK );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

static TgVOID tgUnit_Test__KN_Notify_Func( TgUINT_PTR_C uiParam, TgUINT_E64_C uiParam0, TgUINT_E64_C uiParam1 ) TgATTRIBUTE_NO_EXCEPT
{
    if (0xbad00c0ffee00000ULL != uiParam)
    {
        g_iUnit_Test__KN_Notify_Signal = -1;
        return;
    };

    if (0xbadfece5 != uiParam0)
    {
        g_iUnit_Test__KN_Notify_Signal = -1;
        return;
    };

    if (0xc00010ff != uiParam1)
    {
        g_iUnit_Test__KN_Notify_Signal = -1;
        return;
    };

    ++g_iUnit_Test__KN_Notify_Signal;
}

static TgVOID tgUnit_Test__KN_File_Job_Write_Callback( STg2_KN_File_Write_Command_PCU psWrite_CMD ) TgATTRIBUTE_NO_EXCEPT
{
    union
    {
        STg2_KN_File_Write_Command_P    psWrite;
        TgUINT_PTR                      uiPTR;
    }                                   sAlias_PTR;

    sAlias_PTR.uiPTR = psWrite_CMD->m_uiParam;
    sAlias_PTR.psWrite->m_pBuffer = psWrite_CMD->m_pBuffer;
    sAlias_PTR.psWrite->m_nuiBuffer = psWrite_CMD->m_nuiBuffer;
    sAlias_PTR.psWrite->m_nuiResult = psWrite_CMD->m_nuiResult;
}

static TgVOID tgUnit_Test__KN_File_Job_Read_Callback( STg2_KN_File_Read_Command_PCU psRead_CMD ) TgATTRIBUTE_NO_EXCEPT
{
    union
    {
        STg2_KN_File_Read_Command_P     psRead;
        TgUINT_PTR                      uiPTR;
    }                                   sAlias_PTR;

    sAlias_PTR.uiPTR = psRead_CMD->m_uiParam;
    sAlias_PTR.psRead->m_pBuffer = psRead_CMD->m_pBuffer;
    sAlias_PTR.psRead->m_nuiBuffer = psRead_CMD->m_nuiBuffer;
    sAlias_PTR.psRead->m_nuiResult = psRead_CMD->m_nuiResult;
}
