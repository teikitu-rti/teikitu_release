/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common [Unit Test] [Test] - Util ST - Queue.c
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

TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__QU__Init );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__QU__Free );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__QU__Enqueue );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__QU__Merge );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__QU__Dequeue );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__QU__Is_Empty );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- UNIT_TEST__TEST__UTIL_ST_Queue ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( UNIT_TEST__TEST__UTIL_ST_Queue )
{
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__QU__Init());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__QU__Free());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__QU__Enqueue());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__QU__Merge());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__QU__Dequeue());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__QU__Is_Empty());
    
    TEST_END_METHOD( KTgS_OK );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- UNIT_TEST__TEST__CM_UT_ST__QU__Init -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__QU__Init )
{
    STg2_UT_ST__QU                      sQU;

    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__QU__Init( &sQU ));
    tgCM_UT_ST__QU__Free( &sQU );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__QU__Free -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__QU__Free )
{
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__QU__Init());
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__QU__Enqueue ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__QU__Enqueue )
{
    STg2_UT_ST__QU                      sQU;
    STg2_UT_ST__QU_Node                 sData[4];

    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__QU__Init( &sQU ));

    sData[0].m_pNext_Node = (STg2_UT_ST__QU_Node_P)nullptr;
    tgCM_UT_ST__QU__Enqueue( &sQU, sData );
    Test__Expect_EQ(false, tgCM_UT_ST__QU__Is_Empty( &sQU ));
    Test__Expect_EQ(true, sData == tgCM_UT_ST__QU__Dequeue( &sQU ));
    Test__Expect_EQ(true, tgCM_UT_ST__QU__Is_Empty( &sQU ));
    Test__Expect_EQ(true, nullptr == tgCM_UT_ST__QU__Dequeue( &sQU ));

    sData[1].m_pNext_Node = (STg2_UT_ST__QU_Node_P)nullptr;
    tgCM_UT_ST__QU__Enqueue( &sQU, sData + 1 );
    sData[2].m_pNext_Node = (STg2_UT_ST__QU_Node_P)nullptr;
    tgCM_UT_ST__QU__Enqueue( &sQU, sData + 2 );
    sData[3].m_pNext_Node = (STg2_UT_ST__QU_Node_P)nullptr;
    tgCM_UT_ST__QU__Enqueue( &sQU, sData + 3 );
    Test__Expect_EQ(true, sData + 1 == tgCM_UT_ST__QU__Dequeue( &sQU ));
    Test__Expect_EQ(true, sData + 2 == tgCM_UT_ST__QU__Dequeue( &sQU ));
    Test__Expect_EQ(true, sData + 3 == tgCM_UT_ST__QU__Dequeue( &sQU ));

    sData[1].m_pNext_Node = sData + 2;
    sData[2].m_pNext_Node = sData + 3;
    sData[3].m_pNext_Node = (STg2_UT_ST__QU_Node_P)nullptr;
    tgCM_UT_ST__QU__Enqueue( &sQU, sData + 1 );
    Test__Expect_EQ(true, sData + 1 == tgCM_UT_ST__QU__Dequeue( &sQU ));
    Test__Expect_EQ(true, sData + 2 == tgCM_UT_ST__QU__Dequeue( &sQU ));
    Test__Expect_EQ(true, sData + 3 == tgCM_UT_ST__QU__Dequeue( &sQU ));

    tgCM_UT_ST__QU__Free( &sQU );
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__QU__Merge ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__QU__Merge )
{
    STg2_UT_ST__QU                      sQU0, sQU1;
    STg2_UT_ST__QU_Node                 sData[7];

    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__QU__Init( &sQU0 ));
    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__QU__Init( &sQU1 ));

    sData[0].m_pNext_Node = sData + 1;
    sData[1].m_pNext_Node = sData + 2;
    sData[2].m_pNext_Node = (STg2_UT_ST__QU_Node_P)nullptr;
    tgCM_UT_ST__QU__Enqueue( &sQU0, sData + 0 );

    sData[3].m_pNext_Node = sData + 5;
    sData[4].m_pNext_Node = sData + 6;
    sData[5].m_pNext_Node = sData + 4;
    sData[6].m_pNext_Node = (STg2_UT_ST__QU_Node_P)nullptr;
    tgCM_UT_ST__QU__Enqueue( &sQU1, sData + 3 );
    
    tgCM_UT_ST__QU__Merge( &sQU0, &sQU1 );

    Test__Expect_EQ(true, tgCM_UT_ST__QU__Is_Empty( &sQU1 ));
    Test__Expect_EQ(true, sData + 0 == tgCM_UT_ST__QU__Dequeue( &sQU0 ));
    Test__Expect_EQ(true, sData + 1 == tgCM_UT_ST__QU__Dequeue( &sQU0 ));
    Test__Expect_EQ(true, sData + 2 == tgCM_UT_ST__QU__Dequeue( &sQU0 ));
    Test__Expect_EQ(true, sData + 3 == tgCM_UT_ST__QU__Dequeue( &sQU0 ));
    Test__Expect_EQ(true, sData + 5 == tgCM_UT_ST__QU__Dequeue( &sQU0 ));
    Test__Expect_EQ(true, sData + 4 == tgCM_UT_ST__QU__Dequeue( &sQU0 ));
    Test__Expect_EQ(true, sData + 6 == tgCM_UT_ST__QU__Dequeue( &sQU0 ));
    Test__Expect_EQ(true, tgCM_UT_ST__QU__Is_Empty( &sQU0 ));

    tgCM_UT_ST__QU__Free( &sQU0 );
    tgCM_UT_ST__QU__Free( &sQU1 );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__QU__Dequeue ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__QU__Dequeue )
{
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__QU__Enqueue());
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__QU__Is_Empty ---------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__QU__Is_Empty )
{
    STg2_UT_ST__QU                      sQU;
    STg2_UT_ST__QU_Node                 sData[4];

    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__QU__Init( &sQU ));

    sData[0].m_pNext_Node = (STg2_UT_ST__QU_Node_P)nullptr;
    tgCM_UT_ST__QU__Enqueue( &sQU, sData );
    Test__Expect_EQ(false, tgCM_UT_ST__QU__Is_Empty( &sQU ));
    Test__Expect_EQ(true, sData == tgCM_UT_ST__QU__Dequeue( &sQU ));
    Test__Expect_EQ(true, tgCM_UT_ST__QU__Is_Empty( &sQU ));
    Test__Expect_EQ(true, nullptr == tgCM_UT_ST__QU__Dequeue( &sQU ));

    tgCM_UT_ST__QU__Free( &sQU );
    TEST_END_METHOD( KTgS_OK );
}
