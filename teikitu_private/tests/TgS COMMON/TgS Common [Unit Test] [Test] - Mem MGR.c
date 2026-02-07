/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common [Unit Test] [Test] - Mem MGR.c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TEST_METHOD( UNIT_TEST__TEST__MM_Init_MGR );
TEST_METHOD( UNIT_TEST__TEST__MM_Boot_MGR );
TEST_METHOD( UNIT_TEST__TEST__MM_Stop_MGR );
TEST_METHOD( UNIT_TEST__TEST__MM_Free_MGR );
TEST_METHOD( UNIT_TEST__TEST__MM_Update_MGR );
TEST_METHOD( UNIT_TEST__TEST__MM_Query_Fixed_Memory );
TEST_METHOD( UNIT_TEST__TEST__MM_Query_Init );

TEST_METHOD( UNIT_TEST__TEST__MM_Page_Size );
TEST_METHOD( UNIT_TEST__TEST__MM_Register_Allocator );
TEST_METHOD( UNIT_TEST__TEST__MM_Stats );

TEST_METHOD( UNIT_TEST__TEST__MM_Size );
TEST_METHOD( UNIT_TEST__TEST__MM_Malloc );
TEST_METHOD( UNIT_TEST__TEST__MM_Reserve );
TEST_METHOD( UNIT_TEST__TEST__MM_Commit );
TEST_METHOD( UNIT_TEST__TEST__MM_Free );
TEST_METHOD( UNIT_TEST__TEST__MM_Realloc );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- UNIT_TEST__TEST__COMMON_Mem_MGR ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( UNIT_TEST__TEST__COMMON_Mem_MGR )
{
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__MM_Init_MGR());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__MM_Boot_MGR());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__MM_Stop_MGR());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__MM_Free_MGR());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__MM_Update_MGR());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__MM_Query_Fixed_Memory());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__MM_Query_Init());

    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__MM_Page_Size());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__MM_Register_Allocator());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__MM_Stats());

    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__MM_Size());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__MM_Malloc());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__MM_Reserve());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__MM_Commit());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__MM_Free());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__MM_Realloc());

    TEST_END_METHOD( KTgS_OK );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- UNIT_TEST__TEST__MM_Init_MGR --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__MM_Init_MGR )
{
    /* Due to their nature, module management functions can not be unit tested */

#if defined(TgBUILD_FEATURE__MALLOC_OVERRIDE)
    Test__Expect_EQ(true, tgMM_OS__Preload_Malloc_Redirected());
#endif

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__MM_Boot_MGR --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__MM_Boot_MGR )
{
    /* Due to their nature, module management functions can not be unit tested */

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__MM_Stop_MGR --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__MM_Stop_MGR )
{
    /* Due to their nature, module management functions can not be unit tested */

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__MM_Free_MGR --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__MM_Free_MGR )
{
    /* Due to their nature, module management functions can not be unit tested */

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__MM_Update_MGR ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__MM_Update_MGR )
{
    /* Due to their nature, module management functions can not be unit tested */

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__MM_Query_Fixed_Memory ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__MM_Query_Fixed_Memory )
{
    tgMM_Query_Fixed_Memory();

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__MM_Query_Init ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__MM_Query_Init )
{
    Test__Expect_EQ(true, tgMM_Query_Init());

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__MM_Page_Size -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__MM_Page_Size )
{
    Test__Expect_NE(0, tgMM_Page_Size());

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__MM_Register_Allocator ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__MM_Register_Allocator )
{
    /* Due to their nature, module management functions can not be unit tested */
    /* Since the base two allocators use this function in Init_MGR it is tested as a regular part of the manager */
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__MM_Stats ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__MM_Stats )
{
#if TgS_STAT__COMMON
    TgCHAR_U8                           mbzBuffer[256];
    STg2_Output_MEM                     sOutput;
    TgUN_POINTER                        sBuffer;

    sBuffer.m_mbz = mbzBuffer;

    /* Create a memory base output object to be used when testing the console output systems */
    tgIO_OM__Open( &sOutput, sBuffer.m_puiE08, sizeof( mbzBuffer ), nullptr );
    mbzBuffer[0] = 0;

    tgMM_Stats( &sOutput.m_sOutput );

/*# TgS_STAT__COMMON */
#endif

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__MM_Size ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__MM_Size )
{
    TgRSIZE                             uiPage_Size;

    uiPage_Size = tgMM_Page_Size();

    for (ETgMM_ALLOCATOR enAllocator = ETgMM_ALLOCATOR_BEGIN; enAllocator < ETgMM_ALLOCATOR_USER_0; enAllocator = (ETgMM_ALLOCATOR)((TgSINT_E32)enAllocator + 1))
    {
        TgUN_PTR                            uMem;

        if (!tgMM_Is_Allocator_Registered(enAllocator))
        {
            continue;
        };

        Test__Expect_EQ(0, tgMM_Size( enAllocator, nullptr ));

        uMem.m_pVoid = tgMM_Malloc( enAllocator, 1, 16 );
        Test__Expect_NE(nullptr, uMem.m_pVoid);
        Test__Expect_EQ(true, tgMM_Size( enAllocator, uMem.m_pVoid ) >= 1);
        tgMM_Free( enAllocator, uMem.m_pVoid );

        for (TgRSIZE nuiTest = 0; nuiTest < 1000; ++nuiTest)
        {
            TgRSIZE                             uiSize;

            uiSize = tgCM_RAND_MT_U32() % (10 * uiPage_Size);

            uMem.m_pVoid = tgMM_Malloc( enAllocator, uiSize + 1, 16 );
            Test__Expect_NE(nullptr, uMem.m_pVoid);
            Test__Expect_EQ(true, tgMM_Size( enAllocator, uMem.m_pVoid ) >= uiSize + 1);
            tgMM_Free( enAllocator, uMem.m_pVoid );
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__MM_Malloc ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__MM_Malloc )
{
    TgRSIZE                             uiPage_Size;

    uiPage_Size = tgMM_Page_Size();

    for (ETgMM_ALLOCATOR enAllocator = ETgMM_ALLOCATOR_BEGIN; enAllocator < ETgMM_ALLOCATOR_USER_0; enAllocator = (ETgMM_ALLOCATOR)((TgSINT_E32)enAllocator + 1))
    {
        TgUN_PTR                            auMem[2048];
        TgUN_PTR                            uMem;

        if (!tgMM_Is_Allocator_Registered(enAllocator))
        {
            continue;
        };

        Test__Expect_EQ(0, tgMM_Size( enAllocator, nullptr ));

        uMem.m_pVoid = tgMM_Malloc( enAllocator, 1, 16 );
        Test__Expect_NE(nullptr, uMem.m_pVoid);
        tgMM_Free( enAllocator, uMem.m_pVoid );

        for (TgRSIZE nuiTest = 0; nuiTest < 1000; ++nuiTest)
        {
            TgRSIZE                             uiSize;

            uiSize = tgCM_RAND_MT_U32() % (10 * uiPage_Size);

            uMem.m_pVoid = tgMM_Malloc( enAllocator, uiSize, 16 );
            Test__Expect_NE(nullptr, uMem.m_pVoid);
            tgMM_Free( enAllocator, uMem.m_pVoid );
        };

        for (TgRSIZE nuiTest = 0; nuiTest < 10; ++nuiTest)
        {
            for (TgRSIZE nuiTest_Inner = 0; nuiTest_Inner < TgARRAY_COUNT(auMem); ++nuiTest_Inner)
            {
                auMem[nuiTest_Inner].m_pVoid = tgMM_Malloc( enAllocator, 16u, 16 );
                Test__Expect_NE(nullptr, auMem[nuiTest_Inner].m_pVoid);
            };
            for (TgRSIZE nuiTest_Inner = 0; nuiTest_Inner < TgARRAY_COUNT(auMem); ++nuiTest_Inner)
            {
                tgMM_Free( enAllocator, auMem[nuiTest_Inner].m_pVoid );
            };
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__MM_Reserve ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__MM_Reserve )
{
    TgRSIZE                             uiPage_Size;

    uiPage_Size = tgMM_Page_Size();

    for (ETgMM_ALLOCATOR enAllocator = ETgMM_ALLOCATOR_BEGIN; enAllocator < ETgMM_ALLOCATOR_USER_0; enAllocator = (ETgMM_ALLOCATOR)((TgSINT_E32)enAllocator + 1))
    {
        TgUN_PTR                            uReserve;

        if (!tgMM_Is_Allocator_Registered(enAllocator))
        {
            continue;
        };

        uReserve.m_pVoid = tgMM_Reserve( enAllocator, 1 );
        if (nullptr == uReserve.m_pVoid)
        {
            continue;
        };
        tgMM_Free( enAllocator, uReserve.m_pVoid );

        for (TgRSIZE nuiTest = 0; nuiTest < 1000; ++nuiTest)
        {
            TgRSIZE                             uiSize;

            uiSize = 8 * uiPage_Size + tgCM_RAND_MT_U32() % (10 * uiPage_Size);

            /* Virtual Memory - Reserve a range of pages (no good way to test for non-committed pages due to page fault) */
            uReserve.m_pVoid = tgMM_Reserve( enAllocator, uiSize );
            Test__Expect_NE(nullptr, uReserve.m_pVoid);

            /* Virtual Memory - Free all pages associated with this allocation */
            tgMM_Free( enAllocator, uReserve.m_pVoid );
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__MM_Commit ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__MM_Commit )
{
    TgRSIZE                             uiPage_Size;

    uiPage_Size = tgMM_Page_Size();

    for (ETgMM_ALLOCATOR enAllocator = ETgMM_ALLOCATOR_BEGIN; enAllocator < ETgMM_ALLOCATOR_USER_0; enAllocator = (ETgMM_ALLOCATOR)((TgSINT_E32)enAllocator + 1))
    {
        TgUN_PTR                            uCommit;

        if (!tgMM_Is_Allocator_Registered(enAllocator))
        {
            continue;
        };

        uCommit.m_pVoid = tgMM_Commit( enAllocator, nullptr, 0, 1 );
        if (nullptr == uCommit.m_pVoid)
        {
            continue;
        };
        tgMM_Free( enAllocator, uCommit.m_pVoid );

        for (TgRSIZE nuiTest = 0; nuiTest < 1000; ++nuiTest)
        {
            TgRSIZE                             uiSize;
            TgUN_PTR                            uReserve;

            uiSize = 8 * uiPage_Size + tgCM_RAND_MT_U32() % (10 * uiPage_Size);

            /* Virtual Memory - Reserve a range of pages (no good way to test for non-committed pages due to page fault) */
            uReserve.m_pVoid = tgMM_Reserve( enAllocator, uiSize );
            Test__Expect_NE(nullptr, uReserve.m_pVoid);

            /* Virtual Memory - Standard commit */
            Test__Expect_EQ(uReserve.m_pVoid, tgMM_Commit( enAllocator, uReserve.m_pVoid, 0, 2 * uiPage_Size ));

            /* Virtual Memory - Commit pages non-contiguous from reserve start */
            uCommit.m_pVoid = uReserve.m_pVoid;
            uCommit.m_uiPTR += 4 * uiPage_Size;
            Test__Expect_EQ(uCommit.m_pVoid, tgMM_Commit( enAllocator, uCommit.m_pVoid, 0, 4 * uiPage_Size ));

            /* Virtual Memory - Recommitting pages */
            Test__Expect_EQ(uCommit.m_pVoid, tgMM_Commit( enAllocator, uCommit.m_pVoid, 0, 4 * uiPage_Size ));

            /* Virtual Memory - Failure for over commit */
            /* Test__Expect_EQ(nullptr, tgMM_Commit( enAllocator, uCommit.m_uiPTR, 0, 10 * uiPage_Size )); */

            /* Virtual Memory - Free all pages associated with this allocation */
            tgMM_Free( enAllocator, uReserve.m_pVoid );
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__MM_Free ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__MM_Free )
{
    /* Tested as part of the Malloc, Reserve and Commit */
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__MM_Realloc ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__MM_Realloc )
{
    TgRSIZE                             uiPage_Size;
    ETgMM_ALLOCATOR                     enAllocator;

    uiPage_Size = tgMM_Page_Size();

    for (enAllocator = ETgMM_ALLOCATOR_BEGIN; enAllocator < ETgMM_ALLOCATOR_USER_0; enAllocator = (ETgMM_ALLOCATOR)((TgSINT_E32)enAllocator + 1))
    {
        TgUN_PTR                            uMem_0, uMem_1;

        if (!tgMM_Is_Allocator_Registered(enAllocator))
        {
            continue;
        };

        Test__Expect_EQ(0, tgMM_Size( enAllocator, nullptr ));

        uMem_0.m_pVoid = tgMM_Malloc( enAllocator, 1, 16 );
        Test__Expect_NE(nullptr, uMem_0.m_pVoid);
        uMem_1.m_pVoid = tgMM_Realloc( enAllocator, uMem_0.m_pVoid, 1, 16 );
        if (nullptr == uMem_1.m_pVoid)
        {
            tgMM_Free( enAllocator, uMem_0.m_pVoid );
            continue;
        };
        tgMM_Free( enAllocator, uMem_1.m_pVoid );

        for (TgRSIZE nuiTest = 0; nuiTest < 1000; ++nuiTest)
        {
            TgRSIZE                             uiSize;

            uiSize = tgCM_RAND_MT_U32() % (10 * uiPage_Size);
            uMem_0.m_pVoid = tgMM_Malloc( enAllocator, uiSize, 16 );
            Test__Expect_NE(nullptr, uMem_0.m_pVoid);

            uiSize = tgCM_RAND_MT_U32() % (10 * uiPage_Size);
            uMem_1.m_pVoid = tgMM_Realloc( enAllocator, uMem_0.m_pVoid, uiSize, 16 );
            Test__Expect_NE(nullptr, uMem_1.m_pVoid);
            tgMM_Free( enAllocator, uMem_1.m_pVoid );
        };
    };

    TEST_END_METHOD( KTgS_OK );
}
