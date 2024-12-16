/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common [Unit Test] [Test] - Util MT - Hash Table.c
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

TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__HT_RW__Init_Virtual );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__HT_RW__Init_Fixed );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__HT_RW__Free );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__HT_RW__Clear );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__HT_RW__Find_Yield );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__HT_RW__Find_Spin );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__HT_RW__Find );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__HT_RW__Insert_Yield );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__HT_RW__Insert_Spin );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__HT_RW__Insert );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__HT_RW__Update_Yield );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__HT_RW__Update_Spin );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__HT_RW__Update );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__HT_RW__Remove_Yield );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__HT_RW__Remove_Spin );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__HT_RW__Remove );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- UNIT_TEST__TEST__UTIL_MT_Hash_Table -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( UNIT_TEST__TEST__UTIL_MT_Hash_Table )
{
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__HT_RW__Init_Virtual());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__HT_RW__Init_Fixed());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__HT_RW__Free());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__HT_RW__Clear());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__HT_RW__Find_Yield());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__HT_RW__Find_Spin());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__HT_RW__Find());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__HT_RW__Insert_Yield());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__HT_RW__Insert_Spin());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__HT_RW__Insert());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__HT_RW__Update_Yield());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__HT_RW__Update_Spin());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__HT_RW__Update());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__HT_RW__Remove_Yield());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__HT_RW__Remove_Spin());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_LF__HT_RW__Remove());

    TEST_END_METHOD( KTgS_OK );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- UNIT_TEST__TEST__CM_UT_LF__HT_RW__Init_Virtual --------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__HT_RW__Init_Virtual )
{
    TgUINT_F32                          uiNode_Per_Page;
    TgRSIZE                             nuiNode;
    STg2_UT_LF__HT_RW                   sAMHT;
    TgUINT_E32                          uiData;

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Init_Virtual( &sAMHT, 4, 3, 7 ));

    uiData = 11;
    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Insert( &sAMHT, 1, &uiData ));
    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Insert( &sAMHT, 1, &uiData ));
    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Insert( &sAMHT, 1, &uiData ));
    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Insert( &sAMHT, 1, &uiData ));
    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Insert( &sAMHT, 1, &uiData ));
    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Insert( &sAMHT, 1, &uiData ));
    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Insert( &sAMHT, 1, &uiData ));
    Test__Expect_NE(KTgS_OK, tgCM_UT_LF__HT_RW__Insert( &sAMHT, 1, &uiData ));

    tgCM_UT_LF__HT_RW__Free( &sAMHT );

    uiNode_Per_Page = tgMM_Page_Size() / (sizeof( STg2_UT_ST__HT_Node ) + 6);

    nuiNode = uiNode_Per_Page - 1;
    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Init_Virtual( &sAMHT, 6, 37, nuiNode ));
    for (TgRSIZE uiIndex = 0; uiIndex < nuiNode; ++uiIndex)
    {
        uiData = tgCM_RAND_MT_U32();
        Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Insert( &sAMHT, tgCM_RAND_MT_U32(), &uiData ));
    };
    uiData = tgCM_RAND_MT_U32();
    Test__Expect_NE(KTgS_OK, tgCM_UT_LF__HT_RW__Insert( &sAMHT, tgCM_RAND_MT_U32(), &uiData ));
    tgCM_UT_LF__HT_RW__Free( &sAMHT );

    nuiNode = uiNode_Per_Page;
    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Init_Virtual( &sAMHT, 6, 37, nuiNode ));
    for (TgRSIZE uiIndex = 0; uiIndex < nuiNode; ++uiIndex)
    {
        uiData = tgCM_RAND_MT_U32();
        Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Insert( &sAMHT, tgCM_RAND_MT_U32(), &uiData ));
    };
    uiData = tgCM_RAND_MT_U32();
    Test__Expect_NE(KTgS_OK, tgCM_UT_LF__HT_RW__Insert( &sAMHT, tgCM_RAND_MT_U32(), &uiData ));
    tgCM_UT_LF__HT_RW__Free( &sAMHT );

    nuiNode = uiNode_Per_Page + 1;
    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Init_Virtual( &sAMHT, 6, 37, nuiNode ));
    for (TgRSIZE uiIndex = 0; uiIndex < nuiNode; ++uiIndex)
    {
        uiData = tgCM_RAND_MT_U32();
        Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Insert( &sAMHT, tgCM_RAND_MT_U32(), &uiData ));
    };
    uiData = tgCM_RAND_MT_U32();
    Test__Expect_NE(KTgS_OK, tgCM_UT_LF__HT_RW__Insert( &sAMHT, tgCM_RAND_MT_U32(), &uiData ));
    tgCM_UT_LF__HT_RW__Free( &sAMHT );

    nuiNode = uiNode_Per_Page * 2;
    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Init_Virtual( &sAMHT, 6, 37, nuiNode ));
    for (TgRSIZE uiIndex = 0; uiIndex < nuiNode; ++uiIndex)
    {
        uiData = tgCM_RAND_MT_U32();
        Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Insert( &sAMHT, tgCM_RAND_MT_U32(), &uiData ));
    };
    uiData = tgCM_RAND_MT_U32();
    Test__Expect_NE(KTgS_OK, tgCM_UT_LF__HT_RW__Insert( &sAMHT, tgCM_RAND_MT_U32(), &uiData ));
    tgCM_UT_LF__HT_RW__Free( &sAMHT );



    nuiNode = uiNode_Per_Page * 2;
    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Init_Virtual( &sAMHT, tgMM_Page_Size(), 37, nuiNode ));
    for (TgRSIZE uiIndex = 0; uiIndex < nuiNode; ++uiIndex)
    {
        uiData = tgCM_RAND_MT_U32();
        Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Insert( &sAMHT, tgCM_RAND_MT_U32(), nullptr ));
    };
    uiData = tgCM_RAND_MT_U32();
    Test__Expect_NE(KTgS_OK, tgCM_UT_LF__HT_RW__Insert( &sAMHT, tgCM_RAND_MT_U32(), nullptr ));
    tgCM_UT_LF__HT_RW__Free( &sAMHT );



    nuiNode = uiNode_Per_Page * 2;
    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Init_Virtual( &sAMHT, tgMM_Page_Size() * 2, 37, nuiNode ));
    for (TgRSIZE uiIndex = 0; uiIndex < nuiNode; ++uiIndex)
    {
        uiData = tgCM_RAND_MT_U32();
        Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Insert( &sAMHT, tgCM_RAND_MT_U32(), nullptr ));
    };
    uiData = tgCM_RAND_MT_U32();
    Test__Expect_NE(KTgS_OK, tgCM_UT_LF__HT_RW__Insert( &sAMHT, tgCM_RAND_MT_U32(), nullptr ));
    tgCM_UT_LF__HT_RW__Free( &sAMHT );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_LF__HT_RW__Init_Fixed ----------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__HT_RW__Init_Fixed )
{
    STg2_UT_LF__HT_RW                   sAMHT;
    TgUINT_E08                          uiBuffer[7*sizeof(STg2_UT_ST__HT_Node)];

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Init_Fixed( &sAMHT, sizeof(TgUINT_E08), 3, sizeof uiBuffer, uiBuffer ));
    tgCM_UT_LF__HT_RW__Free( &sAMHT );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_LF__HT_RW__Free ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__HT_RW__Free )
{
    STg2_UT_LF__HT_RW                   sAMHT;

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Init_Virtual( &sAMHT, sizeof(TgUINT_E08), 3, 7 ));
    tgCM_UT_LF__HT_RW__Free( &sAMHT );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_LF__HT_RW__Clear ---------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__HT_RW__Clear )
{
    STg2_UT_LF__HT_RW                   sAMHT;
    TgUINT_PTR                          uiData;

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Init_Virtual( &sAMHT, sizeof(TgUINT_E08), 3, 7 ));
    uiData = 33;
    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Insert( &sAMHT, 3, &uiData ));
    uiData = 0;
    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Find( &uiData, &sAMHT, 3 ));
    Test__Expect_EQ(true, 33 == uiData);

    tgCM_UT_LF__HT_RW__Clear( &sAMHT );

    Test__Expect_NE(KTgS_OK, tgCM_UT_LF__HT_RW__Find( &uiData, &sAMHT, 3 ));
    tgCM_UT_LF__HT_RW__Free( &sAMHT );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_LF__HT_RW__Find_Yield ----------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__HT_RW__Find_Yield )
{
    STg2_UT_LF__HT_RW                   sAMHT;
    TgUINT_PTR                          uiData;

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Init_Virtual( &sAMHT, sizeof(TgUINT_E08), 3, 7 ));
    uiData = 33;
    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Insert( &sAMHT, 3, &uiData ));
    uiData = 0;

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Find_Yield( &uiData, &sAMHT, 3 ));
    Test__Expect_EQ(true, 33 == uiData);

    tgCM_UT_LF__HT_RW__Free( &sAMHT );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_LF__HT_RW__Find_Spin ------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__HT_RW__Find_Spin )
{
    STg2_UT_LF__HT_RW                   sAMHT;
    TgUINT_PTR                          uiData;

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Init_Virtual( &sAMHT, sizeof(TgUINT_E08), 3, 7 ));
    uiData = 33;
    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Insert( &sAMHT, 3, &uiData ));
    uiData = 0;

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Find_Spin( &uiData, &sAMHT, 3 ));
    Test__Expect_EQ(true, 33 == uiData);

    tgCM_UT_LF__HT_RW__Free( &sAMHT );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_LF__HT_RW__Find ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__HT_RW__Find )
{
    STg2_UT_LF__HT_RW                   sAMHT;
    TgUINT_PTR                          uiData;

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Init_Virtual( &sAMHT, sizeof(TgUINT_E08), 3, 7 ));
    uiData = 33;
    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Insert( &sAMHT, 3, &uiData ));
    uiData = 0;

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Find( &uiData, &sAMHT, 3 ));
    Test__Expect_EQ(true, 33 == uiData);

    tgCM_UT_LF__HT_RW__Free( &sAMHT );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_LF__HT_RW__Insert_Yield --------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__HT_RW__Insert_Yield )
{
    STg2_UT_LF__HT_RW                   sAMHT;
    TgUINT_PTR                          uiData;

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Init_Virtual( &sAMHT, sizeof(TgUINT_E08), 3, 7 ));
    
    uiData = 33;
    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Insert_Yield( &sAMHT, 3, &uiData ));
    uiData = 0;

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Find( &uiData, &sAMHT, 3 ));
    Test__Expect_EQ(true, 33 == uiData);
    tgCM_UT_LF__HT_RW__Free( &sAMHT );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_LF__HT_RW__Insert_Spin ---------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__HT_RW__Insert_Spin )
{
    STg2_UT_LF__HT_RW                   sAMHT;
    TgUINT_PTR                          uiData;

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Init_Virtual( &sAMHT, sizeof(TgUINT_E08), 3, 7 ));
    
    uiData = 33;
    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Insert_Spin( &sAMHT, 3, &uiData ));
    uiData = 0;

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Find( &uiData, &sAMHT, 3 ));
    Test__Expect_EQ(true, 33 == uiData);
    tgCM_UT_LF__HT_RW__Free( &sAMHT );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_LF__HT_RW__Insert --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__HT_RW__Insert )
{
    STg2_UT_LF__HT_RW                   sAMHT;
    TgUINT_PTR                          uiData;

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Init_Virtual( &sAMHT, sizeof(TgUINT_E08), 3, 7 ));

    uiData = 33;
    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Insert( &sAMHT, 3, &uiData ));
    uiData = 0;

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Find( &uiData, &sAMHT, 3 ));
    Test__Expect_EQ(true, 33 == uiData);
    tgCM_UT_LF__HT_RW__Free( &sAMHT );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_LF__HT_RW__Update_Yield --------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__HT_RW__Update_Yield )
{
    STg2_UT_LF__HT_RW                   sAMHT;
    TgUINT_PTR                          uiData;

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Init_Virtual( &sAMHT, sizeof(TgUINT_E08), 3, 7 ));
    uiData = 33;
    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Insert( &sAMHT, 3, &uiData ));
    uiData = 0;
    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Find( &uiData, &sAMHT, 3 ));
    Test__Expect_EQ(true, 33 == uiData);

    uiData = 66;
    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Update_Yield( &sAMHT, 3, &uiData ));
    uiData = 0;

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Find( &uiData, &sAMHT, 3 ));
    Test__Expect_EQ(true, 66 == uiData);
    tgCM_UT_LF__HT_RW__Free( &sAMHT );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_LF__HT_RW__Update_Spin ---------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__HT_RW__Update_Spin )
{
    STg2_UT_LF__HT_RW                   sAMHT;
    TgUINT_PTR                          uiData;

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Init_Virtual( &sAMHT, sizeof(TgUINT_E08), 3, 7 ));
    uiData = 33;
    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Insert( &sAMHT, 3, &uiData ));
    uiData = 0;
    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Find( &uiData, &sAMHT, 3 ));
    Test__Expect_EQ(true, 33 == uiData);

    uiData = 66;
    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Update_Spin( &sAMHT, 3, &uiData ));
    uiData = 0;

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Find( &uiData, &sAMHT, 3 ));
    Test__Expect_EQ(true, 66 == uiData);
    tgCM_UT_LF__HT_RW__Free( &sAMHT );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_LF__HT_RW__Update --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__HT_RW__Update )
{
    STg2_UT_LF__HT_RW                   sAMHT;
    TgUINT_PTR                          uiData;

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Init_Virtual( &sAMHT, sizeof(TgUINT_E08), 3, 7 ));
    uiData = 33;
    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Insert( &sAMHT, 3, &uiData ));
    uiData = 0;
    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Find( &uiData, &sAMHT, 3 ));
    Test__Expect_EQ(true, 33 == uiData);

    uiData = 66;
    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Update( &sAMHT, 3, &uiData ));
    uiData = 0;

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Find( &uiData, &sAMHT, 3 ));
    Test__Expect_EQ(true, 66 == uiData);
    tgCM_UT_LF__HT_RW__Free( &sAMHT );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_LF__HT_RW__Remove_Yield --------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__HT_RW__Remove_Yield )
{
    STg2_UT_LF__HT_RW                   sAMHT;
    TgUINT_PTR                          uiData;

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Init_Virtual( &sAMHT, sizeof(TgUINT_E08), 3, 7 ));
    uiData = 33;
    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Insert( &sAMHT, 3, &uiData ));
    uiData = 0;
    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Find( &uiData, &sAMHT, 3 ));
    Test__Expect_EQ(true, 33 == uiData);

    tgCM_UT_LF__HT_RW__Remove_Yield( &sAMHT, 3 );

    Test__Expect_NE(KTgS_OK, tgCM_UT_LF__HT_RW__Find( &uiData, &sAMHT, 3 ));
    tgCM_UT_LF__HT_RW__Free( &sAMHT );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_LF__HT_RW__Remove_Spin ---------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__HT_RW__Remove_Spin )
{
    STg2_UT_LF__HT_RW                   sAMHT;
    TgUINT_PTR                          uiData;

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Init_Virtual( &sAMHT, sizeof(TgUINT_E08), 3, 7 ));
    uiData = 33;
    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Insert( &sAMHT, 3, &uiData ));
    uiData = 0;
    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Find( &uiData, &sAMHT, 3 ));
    Test__Expect_EQ(true, 33 == uiData);

    tgCM_UT_LF__HT_RW__Remove_Spin( &sAMHT, 3 );

    Test__Expect_NE(KTgS_OK, tgCM_UT_LF__HT_RW__Find( &uiData, &sAMHT, 3 ));
    tgCM_UT_LF__HT_RW__Free( &sAMHT );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_LF__HT_RW__Remove --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_LF__HT_RW__Remove )
{
    STg2_UT_LF__HT_RW                   sAMHT;
    TgUINT_PTR                          uiData;

    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Init_Virtual( &sAMHT, sizeof(TgUINT_E08), 3, 7 ));
    uiData = 33;
    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Insert( &sAMHT, 3, &uiData ));
    uiData = 0;
    Test__Expect_EQ(KTgS_OK, tgCM_UT_LF__HT_RW__Find( &uiData, &sAMHT, 3 ));
    Test__Expect_EQ(true, 33 == uiData);

    tgCM_UT_LF__HT_RW__Remove( &sAMHT, 3 );

    Test__Expect_NE(KTgS_OK, tgCM_UT_LF__HT_RW__Find( &uiData, &sAMHT, 3 ));
    tgCM_UT_LF__HT_RW__Free( &sAMHT );

    TEST_END_METHOD( KTgS_OK );
}
