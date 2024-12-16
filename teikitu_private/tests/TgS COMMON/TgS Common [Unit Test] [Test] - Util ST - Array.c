/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common [Unit Test] [Test] - Util ST - Array.c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__AR__Init );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__AR__Free );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__AR__Assign_ElementN );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__AR__Copy );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__AR__Assign_Range );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__AR__Push_Back );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__AR__Insert_Element );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__AR__Insert_ElementN );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__AR__Insert_Copy );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__AR__Insert_Range );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__AR__Pop_Back );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__AR__Erase_Element );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__AR__Erase_Range );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__AR__Clear );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__AR__Get_Data );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__AR__Get_Index );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__AR__Get_Front );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__AR__Get_Back );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__AR__Query_Index );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__AR__Query_Front );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__AR__Query_Back );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__AR__Empty );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__AR__Capacity );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__AR__Count );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__AR__Resize );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__AR__Reserve );
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__AR__Shrink );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- UNIT_TEST__TEST__UTIL_ST_Array ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( UNIT_TEST__TEST__UTIL_ST_Array )
{
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__AR__Init());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__AR__Free());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__AR__Assign_ElementN());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__AR__Copy());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__AR__Assign_Range());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__AR__Push_Back());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__AR__Insert_Element());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__AR__Insert_ElementN());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__AR__Insert_Copy());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__AR__Insert_Range());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__AR__Pop_Back());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__AR__Erase_Element());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__AR__Erase_Range());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__AR__Clear());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__AR__Get_Data());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__AR__Get_Index());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__AR__Get_Front());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__AR__Get_Back());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__AR__Query_Index());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__AR__Query_Front());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__AR__Query_Back());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__AR__Empty());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__AR__Capacity());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__AR__Count());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__AR__Resize());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__AR__Reserve());
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__AR__Shrink());
    TEST_END_METHOD( KTgS_OK );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- UNIT_TEST__TEST__CM_UT_ST__AR__Init -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__AR__Init )
{
    TgUINT_E32                          uiDataB[] = { 2,1,0,4,5,6,3 };
    STg2_UT_ST__AR                      sKB;

    tgCM_UT_ST__AR__Init( &sKB, sizeof( uiDataB[0] ), (TgUINT_E08_P)uiDataB, sizeof uiDataB );

    Test__Expect_EQ(0, tgCM_UT_ST__AR__Count( &sKB ));
    Test__Expect_EQ(7, tgCM_UT_ST__AR__Capacity( &sKB ));

    tgCM_UT_ST__AR__Free( &sKB );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__AR__Free -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__AR__Free )
{
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__AR__Init());
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__AR__Assign_ElementN --------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__AR__Assign_ElementN )
{
    TgUINT_E32                          uiElement5;
    TgUINT_E32                          uiElement7;
    TgUINT_E32                          uiReserve;
    TgUINT_E32                          uiSize;
    TgUINT_E32                          uiLength;
    TgUINT_E32                          uiCheck;

    uiElement5 = 5;
    uiElement7 = 7;

    for (uiReserve = 0; uiReserve <= 28; uiReserve = 4 + (uiReserve * 2))
    {
        for (uiSize = 0; uiSize <= uiReserve; uiSize = 4 + (uiSize * 2))
        {
            for (uiLength = 0; uiLength <= 32; ++uiLength)
            {
                STg2_UT_ST__AR                      sKB;

                tgMM_Set_U08_0x00( &sKB, sizeof( STg2_UT_ST__AR ) );
                sKB.m_bFixed = false;
                sKB.m_uiStride = sizeof( uiElement5 );

                tgCM_UT_ST__AR__Reserve( &sKB, uiReserve );
                Test__Expect_EQ(uiReserve, tgCM_UT_ST__AR__Capacity( &sKB ));
                Test__Expect_EQ(0, tgCM_UT_ST__AR__Count( &sKB ));

                Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Assign_ElementN( &sKB, &uiElement5, uiSize ));
                Test__Expect_EQ(uiSize, tgCM_UT_ST__AR__Count( &sKB ));
                for (uiCheck = 0; uiCheck < uiSize; ++uiCheck)
                {
                    Test__Expect_EQ(uiElement5, *(TgUINT_E32_P)tgCM_UT_ST__AR__Get_Index( &sKB, uiCheck ));
                };
                Test__Expect_EQ(0 == uiSize ? 0u : tgCM_MAX_U32( uiReserve, uiSize ), tgCM_UT_ST__AR__Capacity( &sKB ));

                Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Assign_ElementN( &sKB, &uiElement7, uiLength ));
                Test__Expect_EQ(uiLength, tgCM_UT_ST__AR__Count( &sKB ));
                for (uiCheck = 0; uiCheck < uiLength; ++uiCheck)
                {
                    Test__Expect_EQ(uiElement7, *(TgUINT_E32_P)tgCM_UT_ST__AR__Get_Index( &sKB, uiCheck ));
                };
                uiCheck = 0 == uiSize ? 0u : tgCM_MAX_U32( uiReserve, uiSize );
                Test__Expect_EQ(0 == uiLength ? 0u : tgCM_MAX_U32( uiLength, uiCheck ), tgCM_UT_ST__AR__Capacity( &sKB ));

                tgCM_UT_ST__AR__Free( &sKB  );
            };
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__AR__Copy -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__AR__Copy )
{
    TgUINT_E32                          uiElement5;
    TgUINT_E32                          uiElement7;
    TgUINT_E32                          uiReserve;
    TgUINT_E32                          uiSize;
    TgUINT_E32                          uiCheck;

    uiElement5 = 5;
    uiElement7 = 7;

    for (uiReserve = 0; uiReserve <= 28; uiReserve = 4 + (uiReserve * 2))
    {
        for (uiSize = 0; uiSize <= uiReserve; uiSize = 4 + (uiSize * 2))
        {
            STg2_UT_ST__AR                      sKA;
            STg2_UT_ST__AR                      sKB;

            tgMM_Set_U08_0x00( &sKB, sizeof( STg2_UT_ST__AR ) );
            sKB.m_bFixed = false;
            sKB.m_uiStride = sizeof( uiElement5 );

            tgMM_Set_U08_0x00( &sKA, sizeof( STg2_UT_ST__AR ) );
            sKA.m_bFixed = false;
            sKA.m_uiStride = sizeof( uiElement5 );

            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Copy( &sKB, &sKA ));
            Test__Expect_EQ(0, tgCM_UT_ST__AR__Count( &sKB ));
            Test__Expect_EQ(0, tgCM_UT_ST__AR__Capacity( &sKB ));

            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Reserve( &sKB, uiReserve ));
            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Assign_ElementN( &sKB, &uiElement7, uiSize ));
            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Reserve( &sKA, uiReserve ));
            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Assign_ElementN( &sKA, &uiElement5, uiSize / 2 ));

            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Copy( &sKB, &sKA ));
            Test__Expect_EQ(uiSize / 2, tgCM_UT_ST__AR__Count( &sKB ));
            for (uiCheck = 0; uiCheck < tgCM_UT_ST__AR__Count( &sKB ); ++uiCheck)
            {
                Test__Expect_EQ(uiElement5, *(TgUINT_E32_P)tgCM_UT_ST__AR__Get_Index( &sKB, uiCheck ));
            };
            Test__Expect_EQ(0 == uiSize ? 0u : tgCM_MAX_U32( uiReserve, uiSize ), tgCM_UT_ST__AR__Capacity( &sKB ));

            tgCM_UT_ST__AR__Free( &sKA );

            tgMM_Set_U08_0x00( &sKA, sizeof( STg2_UT_ST__AR ) );
            sKA.m_bFixed = false;
            sKA.m_uiStride = sizeof( uiElement5 );
            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Reserve( &sKA, uiReserve ));
            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Assign_ElementN( &sKA, &uiElement5, uiSize ));

            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Copy( &sKB, &sKA ));
            Test__Expect_EQ(uiSize, tgCM_UT_ST__AR__Count( &sKB ));
            for (uiCheck = 0; uiCheck < tgCM_UT_ST__AR__Count( &sKB ); ++uiCheck)
            {
                Test__Expect_EQ(uiElement5, *(TgUINT_E32_P)tgCM_UT_ST__AR__Get_Index( &sKB, uiCheck ));
            };
            Test__Expect_EQ(0 == uiSize ? 0u : tgCM_MAX_U32( uiReserve, uiSize ), tgCM_UT_ST__AR__Capacity( &sKB ));

            tgCM_UT_ST__AR__Free( &sKA );

            tgMM_Set_U08_0x00( &sKA, sizeof( STg2_UT_ST__AR ) );
            sKA.m_bFixed = false;
            sKA.m_uiStride = sizeof( uiElement5 );
            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Reserve( &sKA, uiReserve ));
            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Assign_ElementN( &sKA, &uiElement5, uiSize * 2 ));

            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Copy( &sKB, &sKA ));
            Test__Expect_EQ(uiSize*2, tgCM_UT_ST__AR__Count( &sKB ));
            for (uiCheck = 0; uiCheck < tgCM_UT_ST__AR__Count( &sKB ); ++uiCheck)
            {
                Test__Expect_EQ(uiElement5, *(TgUINT_E32_P)tgCM_UT_ST__AR__Get_Index( &sKB, uiCheck ));
            };
            Test__Expect_EQ(0 == uiSize ? 0u : tgCM_MAX_U32( uiReserve, uiSize*2 ), tgCM_UT_ST__AR__Capacity( &sKB ));

            tgCM_UT_ST__AR__Free( &sKA );
            tgCM_UT_ST__AR__Free( &sKB );
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__AR__Assign_Range ------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__AR__Assign_Range )
{
    TgUINT_E32                          uiDataB[] = { 2,1,0,4,5,6,3 };
    TgUINT_E32                          uiElement5;
    TgUINT_E32                          uiElement7;
    TgUINT_E32                          uiReserve;
    TgUINT_E32                          uiSize;
    TgUINT_E32                          uiLength;
    TgUINT_E32                          uiCheck;
    TgUINT_E32                          uiBegin;
    TgUINT_E32                          uiEnd;

    uiElement5 = 5;
    uiElement7 = 7;

    for (uiReserve = 0; uiReserve <= 28; uiReserve = 4 + (uiReserve * 2))
    {
        for (uiSize = 0; uiSize <= uiReserve; uiSize = 4 + (uiSize * 2))
        {
            for (uiBegin = 0; uiBegin <= TgARRAY_COUNT( uiDataB ); ++uiBegin)
            {
                for (uiEnd = 0; uiBegin + uiEnd <= TgARRAY_COUNT( uiDataB ); ++uiEnd)
                {
                    STg2_UT_ST__AR                      sKB;

                    tgMM_Set_U08_0x00( &sKB, sizeof( STg2_UT_ST__AR ) );
                    sKB.m_bFixed = false;
                    sKB.m_uiStride = sizeof( uiElement5 );
                    uiLength = 7u - uiBegin - uiEnd;

                    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Reserve( &sKB, uiReserve ));
                    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Assign_ElementN( &sKB, &uiElement7, uiSize ));
                    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Assign_Range( &sKB, uiDataB + uiBegin, uiDataB + 7 - uiEnd ));
                    Test__Expect_EQ(uiLength, tgCM_UT_ST__AR__Count( &sKB ));
                    for (uiCheck = 0; uiCheck < uiLength; ++uiCheck)
                    {
                        Test__Expect_EQ(uiDataB[uiBegin + uiCheck], *(TgUINT_E32_P)tgCM_UT_ST__AR__Get_Index( &sKB, uiCheck ));
                    };
                    uiCheck = 0 == uiSize ? 0u : tgCM_MAX_U32( uiReserve, uiSize );
                    Test__Expect_EQ(0 == uiLength ? 0u : tgCM_MAX_U32( uiLength, uiCheck ), tgCM_UT_ST__AR__Capacity( &sKB ));
                    tgCM_UT_ST__AR__Free( &sKB );

                    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Reserve( &sKB, uiReserve ));
                    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Assign_Range( &sKB, uiDataB, uiDataB + TgARRAY_COUNT( uiDataB ) ));
                    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Assign_Range( &sKB, sKB.m_puiStart + uiBegin*sKB.m_uiStride, sKB.m_puiLast - (uiEnd)*sKB.m_uiStride ));
                    Test__Expect_EQ(uiLength, tgCM_UT_ST__AR__Count( &sKB ));
                    for (uiCheck = 0; uiCheck < uiLength; ++uiCheck)
                    {
                        Test__Expect_EQ(uiDataB[uiBegin + uiCheck], *(TgUINT_E32_P)tgCM_UT_ST__AR__Get_Index( &sKB, uiCheck ));
                    };
                    uiCheck = tgCM_MAX_U32( uiReserve, TgARRAY_COUNT( uiDataB ) );
                    Test__Expect_EQ(0 == uiLength ? 0u : tgCM_MAX_U32( uiLength, uiCheck ), tgCM_UT_ST__AR__Capacity( &sKB ));

                    tgCM_UT_ST__AR__Free( &sKB );
                };
            };
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__AR__Push_Back --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__AR__Push_Back )
{
    TgUINT_E32                          uiElement5;
    TgUINT_E32                          uiElement7;
    TgUINT_E32                          uiReserve;
    TgUINT_E32                          uiSize;
    TgUINT_E32                          uiCheck;

    uiElement5 = 5;
    uiElement7 = 7;

    for (uiReserve = 0; uiReserve <= 28; uiReserve = 4 + (uiReserve * 2))
    {
        for (uiSize = 0; uiSize <= uiReserve; uiSize = 4 + (uiSize * 2))
        {
            STg2_UT_ST__AR                      sKB;

            tgMM_Set_U08_0x00( &sKB, sizeof( STg2_UT_ST__AR ) );
            sKB.m_bFixed = false;
            sKB.m_uiStride = sizeof( uiElement5 );
            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Reserve( &sKB, uiReserve ));
            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Assign_ElementN( &sKB, &uiElement5, uiSize ));

            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Push_Back( &sKB, &uiElement7 ));

            Test__Expect_EQ(uiSize + 1, tgCM_UT_ST__AR__Count( &sKB ));
            for (uiCheck = 0; uiCheck < uiSize; ++uiCheck)
            {
                Test__Expect_EQ(uiElement5, *(TgUINT_E32_P)tgCM_UT_ST__AR__Get_Index( &sKB, uiCheck ));
            };
            Test__Expect_EQ(uiElement7, *(TgUINT_E32_P)tgCM_UT_ST__AR__Get_Index( &sKB, uiSize ));
            Test__Expect_EQ(tgCM_MAX_U32( 0 == uiSize ? 0 : uiReserve, uiSize + 1 ), tgCM_UT_ST__AR__Capacity( &sKB ));
            tgCM_UT_ST__AR__Free( &sKB );
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__AR__Insert_Element ---------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__AR__Insert_Element )
{
    TgUINT_E32                          uiElement5;
    TgUINT_E32                          uiElement7;
    TgUINT_E32                          uiReserve;
    TgUINT_E32                          uiSize;
    TgUINT_E32                          uiCheck;
    TgUINT_E32                          uiIndex;

    uiElement5 = 5;
    uiElement7 = 7;

    for (uiReserve = 0; uiReserve <= 28; uiReserve = 4 + (uiReserve * 2))
    {
        for (uiSize = 0; uiSize <= uiReserve; uiSize = 4 + (uiSize * 2))
        {
            for (uiIndex = 0; uiIndex <= uiSize; ++uiIndex)
            {
                STg2_UT_ST__AR                      sKB;

                tgMM_Set_U08_0x00( &sKB, sizeof( STg2_UT_ST__AR ) );
                sKB.m_bFixed = false;
                sKB.m_uiStride = sizeof( uiElement5 );
                Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Reserve( &sKB, uiReserve ));
                Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Assign_ElementN( &sKB, &uiElement5, uiSize ));

                Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Insert_Element( &sKB, uiIndex, &uiElement7 ));

                Test__Expect_EQ(uiSize + 1, tgCM_UT_ST__AR__Count( &sKB ));
                for (uiCheck = 0; uiCheck < uiSize + 1; ++uiCheck)
                {
                    Test__Expect_EQ(uiCheck == uiIndex ? uiElement7 : uiElement5, *(TgUINT_E32_P)tgCM_UT_ST__AR__Get_Index( &sKB, uiCheck ));
                };
                Test__Expect_EQ(tgCM_MAX_U32( 0 == uiSize ? 0 : uiReserve, uiSize + 1 ), tgCM_UT_ST__AR__Capacity( &sKB ));
                tgCM_UT_ST__AR__Free( &sKB );
            };
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__AR__Insert_ElementN --------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__AR__Insert_ElementN )
{
    TgUINT_E32                          uiElement5;
    TgUINT_E32                          uiElement7;
    TgUINT_E32                          uiReserve;
    TgUINT_E32                          uiSize;
    TgUINT_E32                          uiCheck;
    TgUINT_E32                          uiIndex;

    uiElement5 = 5;
    uiElement7 = 7;

    for (uiReserve = 0; uiReserve <= 28; uiReserve = 4 + (uiReserve * 2))
    {
        for (uiSize = 0; uiSize <= uiReserve; uiSize = 4 + (uiSize * 2))
        {
            for (uiIndex = 0; uiIndex <= uiSize; ++uiIndex)
            {
                STg2_UT_ST__AR                      sKB;

                tgMM_Set_U08_0x00( &sKB, sizeof( STg2_UT_ST__AR ) );
                sKB.m_bFixed = false;
                sKB.m_uiStride = sizeof( uiElement5 );
                Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Reserve( &sKB, uiReserve ));
                Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Assign_ElementN( &sKB, &uiElement5, uiSize ));

                Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Insert_ElementN( &sKB, uiIndex, &uiElement7, 3 ));

                Test__Expect_EQ(uiSize + 3, tgCM_UT_ST__AR__Count( &sKB ));
                uiCheck = 0;
                for (; uiCheck < uiIndex; ++uiCheck)
                {
                    Test__Expect_EQ(uiElement5, *(TgUINT_E32_P)tgCM_UT_ST__AR__Get_Index( &sKB, uiCheck ));
                };
                for (; uiCheck < uiIndex + 3; ++uiCheck)
                {
                    Test__Expect_EQ(uiElement7, *(TgUINT_E32_P)tgCM_UT_ST__AR__Get_Index( &sKB, uiCheck ));
                };
                for (; uiCheck < uiSize + 3; ++uiCheck)
                {
                    Test__Expect_EQ(uiElement5, *(TgUINT_E32_P)tgCM_UT_ST__AR__Get_Index( &sKB, uiCheck ));
                };
                Test__Expect_EQ(tgCM_MAX_U32( 0 == uiSize ? 0 : uiReserve, uiSize + 3 ), tgCM_UT_ST__AR__Capacity( &sKB ));
                tgCM_UT_ST__AR__Free( &sKB );
            };
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__AR__Insert_Copy ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__AR__Insert_Copy )
{
    TgUINT_E32                          uiDataB[] = { 2,1,0,4,5,6,3 };
    TgUINT_E32                          uiElement5;
    TgUINT_E32                          uiElement7;
    TgUINT_E32                          uiReserve;
    TgUINT_E32                          uiSize;
    TgUINT_E32                          uiCheck;
    TgUINT_E32                          uiIndex;

    uiElement5 = 5;
    uiElement7 = 7;

    for (uiReserve = 0; uiReserve <= 28; uiReserve = 4 + (uiReserve * 2))
    {
        for (uiSize = 0; uiSize <= uiReserve; uiSize = 4 + (uiSize * 2))
        {
            for (uiIndex = 0; uiIndex <= uiSize; ++uiIndex)
            {
                STg2_UT_ST__AR                      sKA;
                STg2_UT_ST__AR                      sKB;

                tgMM_Set_U08_0x00( &sKA, sizeof( STg2_UT_ST__AR ) );
                sKA.m_bFixed = false;
                sKA.m_uiStride = sizeof( uiElement5 );
                tgCM_UT_ST__AR__Assign_Range( &sKA, uiDataB, uiDataB + 7 );

                tgMM_Set_U08_0x00( &sKB, sizeof( STg2_UT_ST__AR ) );
                sKB.m_bFixed = false;
                sKB.m_uiStride = sizeof( uiElement5 );
                Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Reserve( &sKB, uiReserve ));
                Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Assign_ElementN( &sKB, &uiElement5, uiSize ));

                Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Insert_Copy( &sKB, uiIndex, &sKA ));

                Test__Expect_EQ(uiSize + 7, tgCM_UT_ST__AR__Count( &sKB ));
                uiCheck = 0;
                for (; uiCheck < uiIndex; ++uiCheck)
                {
                    Test__Expect_EQ(uiElement5, *(TgUINT_E32_P)tgCM_UT_ST__AR__Get_Index( &sKB, uiCheck ));
                };
                for (; uiCheck < uiIndex + 7; ++uiCheck)
                {
                    Test__Expect_EQ(uiDataB[uiCheck - uiIndex], *(TgUINT_E32_P)tgCM_UT_ST__AR__Get_Index( &sKB, uiCheck ));
                };
                for (; uiCheck < uiSize + 7; ++uiCheck)
                {
                    Test__Expect_EQ(uiElement5, *(TgUINT_E32_P)tgCM_UT_ST__AR__Get_Index( &sKB, uiCheck ));
                };
                Test__Expect_EQ(tgCM_MAX_U32( 0 == uiSize ? 0 : uiReserve, uiSize + 7 ), tgCM_UT_ST__AR__Capacity( &sKB ));

                tgCM_UT_ST__AR__Free( &sKB );
                tgCM_UT_ST__AR__Free( &sKA );
            };
        };

        for (uiIndex = 0; uiIndex <= 7; ++uiIndex)
        {
            STg2_UT_ST__AR                      sKB;

            tgMM_Set_U08_0x00( &sKB, sizeof( STg2_UT_ST__AR ) );
            sKB.m_bFixed = false;
            sKB.m_uiStride = sizeof( uiElement5 );
            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Reserve( &sKB, uiReserve ));
            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Assign_Range( &sKB, uiDataB, uiDataB + 7 ));

            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Insert_Copy( &sKB, uiIndex, &sKB ));

            Test__Expect_EQ(14, tgCM_UT_ST__AR__Count( &sKB ));
            uiCheck = 0;
            for (; uiCheck < uiIndex; ++uiCheck)
            {
                Test__Expect_EQ(uiDataB[uiCheck], *(TgUINT_E32_P)tgCM_UT_ST__AR__Get_Index( &sKB, uiCheck ));
            };
            for (; uiCheck < uiIndex + 7; ++uiCheck)
            {
                Test__Expect_EQ(uiDataB[uiCheck - uiIndex], *(TgUINT_E32_P)tgCM_UT_ST__AR__Get_Index( &sKB, uiCheck ));
            };
            for (; uiCheck < 14; ++uiCheck)
            {
                Test__Expect_EQ(uiDataB[uiCheck - 7], *(TgUINT_E32_P)tgCM_UT_ST__AR__Get_Index( &sKB, uiCheck ));
            };
            Test__Expect_EQ(14, tgCM_UT_ST__AR__Capacity( &sKB ));

            tgCM_UT_ST__AR__Free( &sKB );
        };
    };


    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__AR__Insert_Range ------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__AR__Insert_Range )
{
    TgUINT_E32                          uiDataB[] = { 2,1,0,4,5,6,3 };
    TgUINT_E32                          uiElement5;
    TgUINT_E32                          uiElement7;
    TgUINT_E32                          uiReserve;
    TgUINT_E32                          uiSize;
    TgUINT_E32                          uiCheck;
    TgUINT_E32                          uiIndex;
    TgUINT_E32                          uiBegin;
    TgUINT_E32                          uiEnd;

    uiElement5 = 5;
    uiElement7 = 7;

    for (uiReserve = 0; uiReserve <= 28; uiReserve = 4 + (uiReserve * 2))
    {
        for (uiSize = 0; uiSize <= uiReserve; uiSize = 4 + (uiSize * 2))
        {
            for (uiIndex = 0; uiIndex <= uiSize; ++uiIndex)
            {
                for (uiBegin = 0; uiBegin <= 7; ++uiBegin)
                {
                    for (uiEnd = 0; uiBegin + uiEnd <= 7; ++uiEnd)
                    {
                        STg2_UT_ST__AR                      sKB;

                        tgMM_Set_U08_0x00( &sKB, sizeof( STg2_UT_ST__AR ) );
                        sKB.m_bFixed = false;
                        sKB.m_uiStride = sizeof( uiElement5 );
                        Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Reserve( &sKB, uiReserve ));
                        Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Assign_ElementN( &sKB, &uiElement5, uiSize ));

                        Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Insert_Range( &sKB, uiIndex, uiDataB + uiBegin, uiDataB + 7 - uiEnd ));

                        Test__Expect_EQ(uiSize + (7 - (uiBegin + uiEnd)), tgCM_UT_ST__AR__Count( &sKB ));
                        uiCheck = 0;
                        for (; uiCheck < uiIndex; ++uiCheck)
                        {
                            Test__Expect_EQ(uiElement5, *(TgUINT_E32_P)tgCM_UT_ST__AR__Get_Index( &sKB, uiCheck ));
                        };
                        for (; uiCheck < uiIndex + (7 - (uiBegin + uiEnd)); ++uiCheck)
                        {
                            Test__Expect_EQ(uiDataB[uiCheck - uiIndex + uiBegin], *(TgUINT_E32_P)tgCM_UT_ST__AR__Get_Index( &sKB, uiCheck ));
                        };
                        for (; uiCheck < uiSize + (7 - (uiBegin + uiEnd)); ++uiCheck)
                        {
                            Test__Expect_EQ(uiElement5, *(TgUINT_E32_P)tgCM_UT_ST__AR__Get_Index( &sKB, uiCheck ));
                        };
                        Test__Expect_EQ(tgCM_MAX_U32( 0 == uiSize ? 0 : uiReserve, uiSize + (7 - (uiBegin + uiEnd)) ), tgCM_UT_ST__AR__Capacity( &sKB ));

                        tgCM_UT_ST__AR__Free( &sKB );

                        if (uiIndex > 7)
                            continue;

                        Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Reserve( &sKB, uiReserve ));
                        Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Assign_Range( &sKB, uiDataB, uiDataB + 7 ));
                        for (uiCheck = 0; uiCheck < 7; ++uiCheck)
                        {
                            Test__Expect_EQ(uiDataB[uiCheck], *(TgUINT_E32_P)tgCM_UT_ST__AR__Get_Index( &sKB, uiCheck ));
                        };

                        Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Insert_Range( &sKB, uiIndex, sKB.m_puiStart + uiBegin*sKB.m_uiStride, sKB.m_puiLast - uiEnd*sKB.m_uiStride ));

                        Test__Expect_EQ(7 + (7 - (uiBegin + uiEnd)), tgCM_UT_ST__AR__Count( &sKB ));

                        /* Check the range that would match the original assigned elements */
                        for (uiCheck = 0; uiCheck < uiIndex; ++uiCheck)
                        {
                            Test__Expect_EQ(uiDataB[uiCheck], *(TgUINT_E32_P)tgCM_UT_ST__AR__Get_Index( &sKB, uiCheck ));
                        };
                        /* Check the range of the inserted values */
                        for (; uiCheck < uiIndex + (7 - (uiBegin + uiEnd)); ++uiCheck)
                        {
                            Test__Expect_EQ(uiDataB[uiCheck - uiIndex + uiBegin], *(TgUINT_E32_P)tgCM_UT_ST__AR__Get_Index( &sKB, uiCheck ));
                        };
                        /* Check the remaining values from the original assignments*/
                        for (; uiCheck < 7 + (7 - (uiBegin + uiEnd)); ++uiCheck)
                        {
                            Test__Expect_EQ(uiDataB[uiCheck - (7 - (uiBegin + uiEnd))], *(TgUINT_E32_P)tgCM_UT_ST__AR__Get_Index( &sKB, uiCheck ));
                        };
                        Test__Expect_EQ(tgCM_MAX_U32( uiBegin + uiEnd == 7 ? uiReserve : 0, 7 + (7 - (uiBegin + uiEnd)) ), tgCM_UT_ST__AR__Capacity( &sKB ));

                        tgCM_UT_ST__AR__Free( &sKB );
                    };
                };
            };
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__AR__Pop_Back ---------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__AR__Pop_Back )
{
    TgUINT_E32                          uiDataB[] = { 2,1,0,4,5,6,3 };
    TgUINT_E32                          uiCheck;
    STg2_UT_ST__AR                      sKB;

    tgMM_Set_U08_0x00( &sKB, sizeof( STg2_UT_ST__AR ) );
    sKB.m_bFixed = false;
    sKB.m_uiStride = sizeof( uiDataB[0] );
    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Assign_Range( &sKB, uiDataB, uiDataB + 7 ));
    Test__Expect_EQ(7, tgCM_UT_ST__AR__Count( &sKB ));
    Test__Expect_EQ(7, tgCM_UT_ST__AR__Capacity( &sKB ));

    tgCM_UT_ST__AR__Pop_Back( &sKB );

    Test__Expect_EQ(6, tgCM_UT_ST__AR__Count( &sKB ));
    for (uiCheck = 0; uiCheck < 6u; ++uiCheck)
    {
        Test__Expect_EQ(uiDataB[uiCheck], *(TgUINT_E32_P)tgCM_UT_ST__AR__Get_Index( &sKB, uiCheck ));
    };
    Test__Expect_EQ(7, tgCM_UT_ST__AR__Capacity( &sKB ));

    tgCM_UT_ST__AR__Free( &sKB );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__AR__Erase_Element ----------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__AR__Erase_Element )
{
    TgUINT_E32                          uiDataB[] = { 2,1,0,4,5,6,3 };
    TgUINT_E32                          uiIndex;
    TgUINT_E32                          uiCheck;
    STg2_UT_ST__AR                      sKB;

    tgMM_Set_U08_0x00( &sKB, sizeof( STg2_UT_ST__AR ) );
    sKB.m_bFixed = false;
    sKB.m_uiStride = sizeof( uiDataB[0] );

    for (uiIndex = 0; uiIndex < 7; ++uiIndex)
    {
        Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Assign_Range( &sKB, uiDataB, uiDataB + 7 ));
        Test__Expect_EQ(7, tgCM_UT_ST__AR__Count( &sKB ));
        Test__Expect_EQ(7, tgCM_UT_ST__AR__Capacity( &sKB ));

        tgCM_UT_ST__AR__Erase_Element( &sKB, uiIndex );

        Test__Expect_EQ(6, tgCM_UT_ST__AR__Count( &sKB ));
        for (uiCheck = 0; uiCheck < 6; ++uiCheck)
        {
            Test__Expect_EQ(uiDataB[uiCheck + (uiCheck >= uiIndex ? 1 : 0)], *(TgUINT_E32_P)tgCM_UT_ST__AR__Get_Index( &sKB, uiCheck ));
        };
        Test__Expect_EQ(7, tgCM_UT_ST__AR__Capacity( &sKB ));
    }

    tgCM_UT_ST__AR__Free( &sKB );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__AR__Erase_Range ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__AR__Erase_Range )
{
    TgUINT_E32                          uiDataB[] = { 2,1,0,4,5,6,3 };
    TgUINT_E32                          uiIndex;
    TgUINT_E32                          uiCheck;
    TgUINT_E32                          uiBegin;
    TgUINT_E32                          uiEnd;
    STg2_UT_ST__AR                      sKB;

    tgMM_Set_U08_0x00( &sKB, sizeof( STg2_UT_ST__AR ) );
    sKB.m_bFixed = false;
    sKB.m_uiStride = sizeof( uiDataB[0] );

    for (uiBegin = 0; uiBegin <= 7; ++uiBegin)
    {
        for (uiEnd = 0; uiBegin + uiEnd <= 7; ++uiEnd)
        {
            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Assign_Range( &sKB, uiDataB, uiDataB + 7 ));
            Test__Expect_EQ(7, tgCM_UT_ST__AR__Count( &sKB ));
            Test__Expect_EQ(7, tgCM_UT_ST__AR__Capacity( &sKB ));

            tgCM_UT_ST__AR__Erase_Range( &sKB, uiBegin, 7 - uiEnd );

            Test__Expect_EQ(uiBegin + uiEnd, tgCM_UT_ST__AR__Count( &sKB ));
            uiIndex = 0;
            for (uiCheck = 0; uiCheck < uiBegin; ++uiCheck, ++uiIndex)
            {
                Test__Expect_EQ(uiDataB[uiCheck], *(TgUINT_E32_P)tgCM_UT_ST__AR__Get_Index( &sKB, uiIndex ));
            };

            for (uiCheck = 7 - uiEnd; uiCheck < 7u; ++uiCheck, ++uiIndex)
            {
                Test__Expect_EQ(uiDataB[uiCheck], *(TgUINT_E32_P)tgCM_UT_ST__AR__Get_Index( &sKB, uiIndex ));
            };

            Test__Expect_EQ(7, tgCM_UT_ST__AR__Capacity( &sKB ));
        };
    };

    tgCM_UT_ST__AR__Free( &sKB );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__AR__Clear ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__AR__Clear )
{
    TgUINT_E32                          uiDataB[] = { 2,1,0,4,5,6,3 };
    STg2_UT_ST__AR                      sKB;

    tgMM_Set_U08_0x00( &sKB, sizeof( STg2_UT_ST__AR ) );
    sKB.m_bFixed = false;
    sKB.m_uiStride = sizeof( uiDataB[0] );

    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Assign_Range( &sKB, uiDataB, uiDataB + 7 ));
    Test__Expect_EQ(7, tgCM_UT_ST__AR__Count( &sKB ));
    Test__Expect_EQ(7, tgCM_UT_ST__AR__Capacity( &sKB ));
    tgCM_UT_ST__AR__Clear( &sKB );
    Test__Expect_EQ(0, tgCM_UT_ST__AR__Count( &sKB ));
    Test__Expect_EQ(0, tgCM_UT_ST__AR__Capacity( &sKB ));

    tgCM_UT_ST__AR__Free( &sKB );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__AR__Get_Data ---------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__AR__Get_Data )
{
    TgUINT_E32                          uiDataB[] = { 2,1,0,4,5,6,3 };
    STg2_UT_ST__AR                      sKB;

    tgMM_Set_U08_0x00( &sKB, sizeof( STg2_UT_ST__AR ) );
    sKB.m_bFixed = false;
    sKB.m_uiStride = sizeof( uiDataB[0] );

    Test__Expect_EQ(nullptr, tgCM_UT_ST__AR__Get_Data( &sKB ));
    Test__Expect_EQ(0, tgCM_UT_ST__AR__Count( &sKB ));
    Test__Expect_EQ(0, tgCM_UT_ST__AR__Capacity( &sKB ));
    Test__Expect_EQ(true, tgCM_UT_ST__AR__Empty( &sKB ));

    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Assign_Range( &sKB, uiDataB, uiDataB + 7 ));
    Test__Expect_EQ(7, tgCM_UT_ST__AR__Count( &sKB ));
    Test__Expect_EQ(7, tgCM_UT_ST__AR__Capacity( &sKB ));
    Test__Expect_NE(nullptr, tgCM_UT_ST__AR__Get_Data( &sKB ));
    Test__Expect_EQ(false, tgCM_UT_ST__AR__Empty( &sKB ));

    tgCM_UT_ST__AR__Free( &sKB );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__AR__Get_Index --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__AR__Get_Index )
{
    TgUINT_E32                          uiDataB[] = { 2,1,0,4,5,6,3 };
    TgUINT_E32                          uiIndex;
    STg2_UT_ST__AR                      sKB;

    tgMM_Set_U08_0x00( &sKB, sizeof( STg2_UT_ST__AR ) );
    sKB.m_bFixed = false;
    sKB.m_uiStride = sizeof( uiDataB[0] );

    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Assign_Range( &sKB, uiDataB, uiDataB + 7 ));
    Test__Expect_EQ(7, tgCM_UT_ST__AR__Count( &sKB ));
    Test__Expect_EQ(7, tgCM_UT_ST__AR__Capacity( &sKB ));
    Test__Expect_NE(nullptr, tgCM_UT_ST__AR__Get_Data( &sKB ));
    Test__Expect_EQ(false, tgCM_UT_ST__AR__Empty( &sKB ));

    for (uiIndex = 0; uiIndex < 7; ++uiIndex)
    {
        Test__Expect_EQ(uiDataB[uiIndex], *(TgUINT_E32_P)tgCM_UT_ST__AR__Get_Index( &sKB, uiIndex ));
    };

    tgCM_UT_ST__AR__Free( &sKB );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__AR__Get_Front --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__AR__Get_Front )
{
    TgUINT_E32                          uiDataB[] = { 2,1,0,4,5,6,3 };
    STg2_UT_ST__AR                      sKB;

    tgMM_Set_U08_0x00( &sKB, sizeof( STg2_UT_ST__AR ) );
    sKB.m_bFixed = false;
    sKB.m_uiStride = sizeof( uiDataB[0] );

    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Assign_Range( &sKB, uiDataB, uiDataB + 7 ));
    Test__Expect_EQ(7, tgCM_UT_ST__AR__Count( &sKB ));
    Test__Expect_EQ(7, tgCM_UT_ST__AR__Capacity( &sKB ));
    Test__Expect_NE(nullptr, tgCM_UT_ST__AR__Get_Data( &sKB ));
    Test__Expect_EQ(false, tgCM_UT_ST__AR__Empty( &sKB ));

    Test__Expect_EQ(uiDataB[0], *(TgUINT_E32_P)tgCM_UT_ST__AR__Get_Front( &sKB ));

    tgCM_UT_ST__AR__Free( &sKB );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__AR__Get_Back ---------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__AR__Get_Back )
{
    TgUINT_E32                          uiDataB[] = { 2,1,0,4,5,6,3 };
    STg2_UT_ST__AR                      sKB;

    tgMM_Set_U08_0x00( &sKB, sizeof( STg2_UT_ST__AR ) );
    sKB.m_bFixed = false;
    sKB.m_uiStride = sizeof( uiDataB[0] );

    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Assign_Range( &sKB, uiDataB, uiDataB + 7 ));
    Test__Expect_EQ(7, tgCM_UT_ST__AR__Count( &sKB ));
    Test__Expect_EQ(7, tgCM_UT_ST__AR__Capacity( &sKB ));
    Test__Expect_NE(nullptr, tgCM_UT_ST__AR__Get_Data( &sKB ));
    Test__Expect_EQ(false, tgCM_UT_ST__AR__Empty( &sKB ));

    Test__Expect_EQ(uiDataB[6], *(TgUINT_E32_P)tgCM_UT_ST__AR__Get_Back( &sKB ));

    tgCM_UT_ST__AR__Free( &sKB );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__AR__Query_Index ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__AR__Query_Index )
{
    TgUINT_E32                          uiDataB[] = { 2,1,0,4,5,6,3 };
    TgUINT_E32                          uiIndex;
    TgUINT_E32                          uiCheck;
    STg2_UT_ST__AR                      sKB;

    tgMM_Set_U08_0x00( &sKB, sizeof( STg2_UT_ST__AR ) );
    sKB.m_bFixed = false;
    sKB.m_uiStride = sizeof( uiDataB[0] );

    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Assign_Range( &sKB, uiDataB, uiDataB + 7 ));
    Test__Expect_EQ(7, tgCM_UT_ST__AR__Count( &sKB ));
    Test__Expect_EQ(7, tgCM_UT_ST__AR__Capacity( &sKB ));
    Test__Expect_NE(nullptr, tgCM_UT_ST__AR__Get_Data( &sKB ));
    Test__Expect_EQ(false, tgCM_UT_ST__AR__Empty( &sKB ));

    for (uiIndex = 0; uiIndex < 7; ++uiIndex)
    {
        Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Query_Index( &uiCheck, sizeof( uiCheck ), &sKB, uiIndex ));
        Test__Expect_EQ(uiDataB[uiIndex], uiCheck);
    };

    tgCM_UT_ST__AR__Free( &sKB );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__AR__Query_Front ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__AR__Query_Front )
{
    TgUINT_E32                          uiDataB[] = { 2,1,0,4,5,6,3 };
    TgUINT_E32                          uiCheck;
    STg2_UT_ST__AR                      sKB;

    tgMM_Set_U08_0x00( &sKB, sizeof( STg2_UT_ST__AR ) );
    sKB.m_bFixed = false;
    sKB.m_uiStride = sizeof( uiDataB[0] );

    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Assign_Range( &sKB, uiDataB, uiDataB + 7 ));
    Test__Expect_EQ(7, tgCM_UT_ST__AR__Count( &sKB ));
    Test__Expect_EQ(7, tgCM_UT_ST__AR__Capacity( &sKB ));
    Test__Expect_NE(nullptr, tgCM_UT_ST__AR__Get_Data( &sKB ));
    Test__Expect_EQ(false, tgCM_UT_ST__AR__Empty( &sKB ));

    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Query_Front( &uiCheck, sizeof( uiCheck ), &sKB ));
    Test__Expect_EQ(uiDataB[0], uiCheck);

    tgCM_UT_ST__AR__Free( &sKB );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__AR__Query_Back -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__AR__Query_Back )
{
    TgUINT_E32                          uiDataB[] = { 2,1,0,4,5,6,3 };
    TgUINT_E32                          uiCheck;
    STg2_UT_ST__AR                      sKB;

    tgMM_Set_U08_0x00( &sKB, sizeof( STg2_UT_ST__AR ) );
    sKB.m_bFixed = false;
    sKB.m_uiStride = sizeof( uiDataB[0] );

    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Assign_Range( &sKB, uiDataB, uiDataB + 7 ));
    Test__Expect_EQ(7, tgCM_UT_ST__AR__Count( &sKB ));
    Test__Expect_EQ(7, tgCM_UT_ST__AR__Capacity( &sKB ));
    Test__Expect_NE(nullptr, tgCM_UT_ST__AR__Get_Data( &sKB ));
    Test__Expect_EQ(false, tgCM_UT_ST__AR__Empty( &sKB ));

    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Query_Back( &uiCheck, sizeof( uiCheck ), &sKB ));
    Test__Expect_EQ(uiDataB[6], uiCheck);

    tgCM_UT_ST__AR__Free( &sKB );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__AR__Empty ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__AR__Empty )
{
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__AR__Get_Data());
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__AR__Capacity ---------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__AR__Capacity )
{
    TgUINT_E32                          uiDataB[] = { 2,1,0,4,5,6,3 };
    STg2_UT_ST__AR                      sKB;

    tgMM_Set_U08_0x00( &sKB, sizeof( STg2_UT_ST__AR ) );
    sKB.m_bFixed = false;
    sKB.m_uiStride = sizeof( uiDataB[0] );

    Test__Expect_EQ(0, tgCM_UT_ST__AR__Count( &sKB ));
    Test__Expect_EQ(0, tgCM_UT_ST__AR__Capacity( &sKB ));

    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Resize( &sKB, 3, uiDataB ));
    Test__Expect_EQ(3, tgCM_UT_ST__AR__Count( &sKB ));
    Test__Expect_EQ(uiDataB[0], *(TgUINT_E32_P)tgCM_UT_ST__AR__Get_Index( &sKB, 0 ));
    Test__Expect_EQ(uiDataB[0], *(TgUINT_E32_P)tgCM_UT_ST__AR__Get_Index( &sKB, 1 ));
    Test__Expect_EQ(uiDataB[0], *(TgUINT_E32_P)tgCM_UT_ST__AR__Get_Index( &sKB, 2 ));
    Test__Expect_EQ(3, tgCM_UT_ST__AR__Capacity( &sKB ));

    tgCM_UT_ST__AR__Free( &sKB );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__AR__Count ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__AR__Count )
{
    Test__Expect_EQ(KTgS_OK, UNIT_TEST__TEST__CM_UT_ST__AR__Capacity());
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__AR__Resize ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__AR__Resize )
{
    TgUINT_E32                          uiDataB[] = { 2,1,0,4,5,6,3 };
    STg2_UT_ST__AR                      sKB;
    TgUINT_E32                          uiSize;
    TgUINT_E32                          uiCheck;

    tgMM_Set_U08_0x00( &sKB, sizeof( STg2_UT_ST__AR ) );
    sKB.m_bFixed = false;
    sKB.m_uiStride = sizeof( uiDataB[0] );

    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Resize( &sKB, 3, uiDataB ));
    Test__Expect_EQ(3, tgCM_UT_ST__AR__Count( &sKB ));
    Test__Expect_EQ(uiDataB[0], *(TgUINT_E32_P)tgCM_UT_ST__AR__Get_Index( &sKB, 0 ));
    Test__Expect_EQ(uiDataB[0], *(TgUINT_E32_P)tgCM_UT_ST__AR__Get_Index( &sKB, 1 ));
    Test__Expect_EQ(uiDataB[0], *(TgUINT_E32_P)tgCM_UT_ST__AR__Get_Index( &sKB, 2 ));
    Test__Expect_EQ(3, tgCM_UT_ST__AR__Capacity( &sKB ));

    for (uiSize = 0; uiSize <= 9; ++uiSize)
    {
        Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Assign_Range( &sKB, uiDataB, uiDataB + 7 ));

        Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Resize( &sKB, uiSize, uiDataB ));

        Test__Expect_EQ(uiSize, tgCM_UT_ST__AR__Count( &sKB ));
        uiCheck = 0;
        for (; uiCheck < tgCM_MIN_U32( uiSize, 7u ); ++uiCheck)
        {
            Test__Expect_EQ(uiDataB[uiCheck], *(TgUINT_E32_P)tgCM_UT_ST__AR__Get_Index( &sKB, uiCheck ));
        };

        for (; uiCheck < uiSize; ++uiCheck)
        {
            Test__Expect_EQ(uiDataB[0], *(TgUINT_E32_P)tgCM_UT_ST__AR__Get_Index( &sKB, uiCheck ));
        };

        Test__Expect_EQ(tgCM_MAX_U32( uiSize, 7 ), tgCM_UT_ST__AR__Capacity( &sKB ));

        tgCM_UT_ST__AR__Free( &sKB );
    };

    tgCM_UT_ST__AR__Free( &sKB );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__AR__Reserve ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__AR__Reserve )
{
    TgUINT_E32                          uiDataB[] = { 2,1,0,4,5,6,3 };
    STg2_UT_ST__AR                      sKB;
    TgUINT_E32                          uiSize;
    TgUINT_E32                          uiCheck;

    tgMM_Set_U08_0x00( &sKB, sizeof( STg2_UT_ST__AR ) );
    sKB.m_bFixed = false;
    sKB.m_uiStride = sizeof( uiDataB[0] );

    for (uiSize = 0; uiSize <= 9; ++uiSize)
    {
        Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Assign_Range( &sKB, uiDataB, uiDataB + 7 ));

        Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Reserve( &sKB, uiSize ));

        Test__Expect_EQ(7, tgCM_UT_ST__AR__Count( &sKB ));
        for (uiCheck = 0; uiCheck < 7u; ++uiCheck)
        {
            Test__Expect_EQ(uiDataB[uiCheck], *(TgUINT_E32_P)tgCM_UT_ST__AR__Get_Index( &sKB, uiCheck ));
        };
        Test__Expect_EQ(tgCM_MAX_U32( uiSize, 7 ), tgCM_UT_ST__AR__Capacity( &sKB ));

        tgCM_UT_ST__AR__Free( &sKB );
    };

    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Reserve( &sKB, 0 ));
    Test__Expect_EQ(0, tgCM_UT_ST__AR__Count( &sKB ));
    Test__Expect_EQ(0, tgCM_UT_ST__AR__Capacity( &sKB ));

    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Reserve( &sKB, 5 ));
    Test__Expect_EQ(0, tgCM_UT_ST__AR__Count( &sKB ));
    Test__Expect_EQ(5, tgCM_UT_ST__AR__Capacity( &sKB ));

    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Reserve( &sKB, 4 ));
    Test__Expect_EQ(0, tgCM_UT_ST__AR__Count( &sKB ));
    Test__Expect_EQ(5, tgCM_UT_ST__AR__Capacity( &sKB ));

    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Reserve( &sKB, 6 ));
    Test__Expect_EQ(0, tgCM_UT_ST__AR__Count( &sKB ));
    Test__Expect_EQ(6, tgCM_UT_ST__AR__Capacity( &sKB ));

    tgCM_UT_ST__AR__Free( &sKB );

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__CM_UT_ST__AR__Shrink ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__CM_UT_ST__AR__Shrink )
{
    TgUINT_E32                          uiDataB[] = { 2,1,0,4,5,6,3 };
    STg2_UT_ST__AR                      sKB;
    TgUINT_E32                          uiSize;
    TgUINT_E32                          uiCheck;

    tgMM_Set_U08_0x00( &sKB, sizeof( STg2_UT_ST__AR ) );
    sKB.m_bFixed = false;
    sKB.m_uiStride = sizeof( uiDataB[0] );

    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Reserve( &sKB, 6 ));
    Test__Expect_EQ(0, tgCM_UT_ST__AR__Count( &sKB ));
    Test__Expect_EQ(6, tgCM_UT_ST__AR__Capacity( &sKB ));

    for (uiSize = 0; uiSize <= 9; ++uiSize)
    {
        Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Assign_Range( &sKB, uiDataB, uiDataB + 7 ));

        if (uiSize < 7)
        {
            Test__Expect_NE(KTgS_OK, tgCM_UT_ST__AR__Shrink( &sKB, uiSize ));
        }
        else
        {
            Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Shrink( &sKB, uiSize ));
        }

        Test__Expect_EQ(7, tgCM_UT_ST__AR__Count( &sKB ));
        for (uiCheck = 0; uiCheck < 7; ++uiCheck)
        {
            Test__Expect_EQ(uiDataB[uiCheck], *(TgUINT_E32_P)tgCM_UT_ST__AR__Get_Index( &sKB, uiCheck ));
        };
        Test__Expect_EQ(7, tgCM_UT_ST__AR__Capacity( &sKB ));

        tgCM_UT_ST__AR__Free( &sKB );
    };

    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Shrink( &sKB, 0 ));
    Test__Expect_EQ(0, tgCM_UT_ST__AR__Count( &sKB ));
    Test__Expect_EQ(0, tgCM_UT_ST__AR__Capacity( &sKB ));

    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Reserve( &sKB, 7 ));
    Test__Expect_EQ(0, tgCM_UT_ST__AR__Count( &sKB ));
    Test__Expect_EQ(7, tgCM_UT_ST__AR__Capacity( &sKB ));

    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Shrink( &sKB, 5 ));
    Test__Expect_EQ(0, tgCM_UT_ST__AR__Count( &sKB ));
    Test__Expect_EQ(5, tgCM_UT_ST__AR__Capacity( &sKB ));

    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Shrink( &sKB, 4 ));
    Test__Expect_EQ(0, tgCM_UT_ST__AR__Count( &sKB ));
    Test__Expect_EQ(4, tgCM_UT_ST__AR__Capacity( &sKB ));

    Test__Expect_EQ(KTgS_OK, tgCM_UT_ST__AR__Shrink( &sKB, 6 ));
    Test__Expect_EQ(0, tgCM_UT_ST__AR__Count( &sKB ));
    Test__Expect_EQ(4, tgCM_UT_ST__AR__Capacity( &sKB ));

    tgCM_UT_ST__AR__Free( &sKB );

    TEST_END_METHOD( KTgS_OK );
}
