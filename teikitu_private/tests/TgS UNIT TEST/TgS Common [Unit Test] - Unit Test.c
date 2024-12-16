/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common [Unit Test] - Unit Test.c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "../TgS UNIT TEST/TgS Common [Unit Test] - Unit Test.h"


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Unit Test Data                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

static STg2_Profile_Record g_sPROFILE_UNIT_TEST__TEST_SET__EXECUTE;
static Test_Set *g_psTest_Set_Start = 0;




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- Unit_Test__Sleep --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID Unit_Test__Sleep( TgUINT_E32_C uiNanoseconds )
{
#if TgCOMPILE__THREAD
    tgTR_Sleep( uiNanoseconds );
#else
    TgFLOAT32                               fStart;

    fStart = tgTM_Query_Time();
    while (tgTM_Query_Time() - fStart < (TgFLOAT32)uiMilliseconds)
    {
    }
#endif
}


/* ---- Unit_Test__Case_Init ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID Unit_Test__Case_Init( Test_Case_PCU psTest_Case )
{
    tgMM_Set_U08_0x00( psTest_Case, sizeof( Test_Case ) );
}


/* ---- Unit_Test__Case_Execute -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT Unit_Test__Case_Execute( Test_Context_PCU psTest_Context, Test_Case_PCU psCase_Default )
{
    TgBOOL_C            bValid_Case = nullptr != psTest_Context->m_psRestart_Case;
    Test_Case_P                             psCase = bValid_Case ? psTest_Context->m_psRestart_Case : psCase_Default;
    TgRESULT                                tgRet = KTgS_OK;
    TgUINT_E32                              uiTest_Index = psTest_Context->m_psRestart_Case_Test;

    psTest_Context->m_psRestart_Case_Test = 0;
    psTest_Context->m_psRestart_Case = nullptr;

    for (; 0 != psCase && KTgS_OK == tgRet; psCase = psCase->m_psNext)
    {
        for (; uiTest_Index < KTgNUM_TEST_PER_CASE && KTgS_OK == tgRet; ++uiTest_Index)
        {
            if (nullptr == psCase->m_pfnTest[uiTest_Index])
            {
                continue;
            };

            if (nullptr != psCase->m_pfnInit)
            {
                if (TgFAILED( psCase->m_pfnInit() ))
                {
                    psTest_Context->m_psRestart_Case = psCase->m_psNext;
                    tgRet = KTgE_FAIL;

                    if (psCase->m_pfnReport_Case_Failed)
                    {
                        psCase->m_pfnReport_Case_Failed( psTest_Context, psCase, u8"INIT" );
                    }
                    else if (psTest_Context->m_pfnReport_Case_Failed)
                    {
                        psTest_Context->m_pfnReport_Case_Failed( psTest_Context, psCase, u8"INIT" );
                    };

                    break;
                }
                else
                {
                    if (psCase->m_pfnReport_Case_Passed)
                    {
                        psCase->m_pfnReport_Case_Passed( psTest_Context, psCase, u8"INIT" );
                    }
                    else if (psTest_Context->m_pfnReport_Case_Passed)
                    {
                        psTest_Context->m_pfnReport_Case_Passed( psTest_Context, psCase, u8"INIT" );
                    };
                };
            };

            if (TgFAILED( psCase->m_pfnTest[uiTest_Index]() ))
            {
                if (0 != psTest_Context->m_pfnReport_Case_Report_Failed)
                {
                    psTest_Context->m_pfnReport_Case_Report_Failed( psTest_Context, psCase, uiTest_Index );
                }
                else if (0 != psCase->m_pfnReport_Case_Report_Failed)
                {
                    psCase->m_pfnReport_Case_Report_Failed( psTest_Context, psCase, uiTest_Index );
                };

                if (uiTest_Index + 1 >= KTgNUM_TEST_PER_CASE)
                {
                    psTest_Context->m_psRestart_Case = psCase->m_psNext;
                }
                else
                {
                    psTest_Context->m_psRestart_Case = psCase;
                    psTest_Context->m_psRestart_Case_Test = uiTest_Index + 1;
                }
                tgRet = KTgE_FAIL;

                ++psTest_Context->m_nuiCase_Failed;
            }
            else
            {
                if (0 != psTest_Context->m_pfnReport_Case_Report_Passed)
                {
                    psTest_Context->m_pfnReport_Case_Report_Passed( psTest_Context, psCase, uiTest_Index );
                }
                else if (0 != psCase->m_pfnReport_Case_Report_Passed)
                {
                    psCase->m_pfnReport_Case_Report_Passed( psTest_Context, psCase, uiTest_Index );
                };

                ++psTest_Context->m_nuiCase_Passed;
            };

            if (nullptr != psCase->m_pfnFree)
            {
                if (TgFAILED( psCase->m_pfnFree() ))
                {
                    psTest_Context->m_psRestart_Case = psCase->m_psNext;
                    tgRet = KTgE_FAIL;

                    if (psCase->m_pfnReport_Case_Failed)
                    {
                        psCase->m_pfnReport_Case_Failed( psTest_Context, psCase, u8"FREE" );
                    }
                    else if (psTest_Context->m_pfnReport_Case_Failed)
                    {
                        psTest_Context->m_pfnReport_Case_Failed( psTest_Context, psCase, u8"FREE" );
                    };

                    break;
                }
                else
                {
                    if (psCase->m_pfnReport_Case_Passed)
                    {
                        psCase->m_pfnReport_Case_Passed( psTest_Context, psCase, u8"FREE" );
                    }
                    else if (psTest_Context->m_pfnReport_Case_Passed)
                    {
                        psTest_Context->m_pfnReport_Case_Passed( psTest_Context, psCase, u8"FREE" );
                    };
                };
            };

            ++psTest_Context->m_nuiCase_Total;
        };

        uiTest_Index = 0;
    };

    return (tgRet);
}


/* ---- Unit_Test__Set_Register_Case --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID Unit_Test__Set_Register_Case( Test_Set_PC psSet, Test_Case_PC psTest_Case )
{
    if (0 == psSet->m_psFirst_Case)
    {
        psSet->m_psFirst_Case = psTest_Case;
    }
    else
    {
        Test_Case *psTest = psSet->m_psFirst_Case;
        for (; 0 != psTest->m_psNext; psTest = psTest->m_psNext);
        psTest->m_psNext = psTest_Case;
        psTest_Case->m_psPrev = psTest;
    };
}


/* ---- Unit_Test__Set_Init ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID Unit_Test__Set_Init( Test_Set_PC psSet )
{
    tgMM_Set_U08_0x00( psSet, sizeof( Test_Set ) );
}


/* ---- Unit_Test__Set_Execute --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT Unit_Test__Set_Execute( Test_Context_PCU psTest_Context, Test_Set_PCU psSet_Start )
{
    TgBOOL_C            bOutput_Message = nullptr == psTest_Context->m_psRestart_Set;
    Test_Set_P                              psSet = psSet_Start;
    TgRESULT                                iResult;
    TgRESULT                                tgRet = KTgS_OK;

    psTest_Context->m_psRestart_Set = nullptr;

    for (; 0 != psSet && KTgS_OK == tgRet; psSet = psSet->m_psNext)
    {
        if (nullptr != psSet->m_pfnInit)
        {
            if (TgFAILED( psSet->m_pfnInit() ))
            {
                psTest_Context->m_psRestart_Set = psSet->m_psNext;
                tgRet = KTgE_FAIL;

                if (psSet->m_pfnReport_Set_Failed)
                {
                    psSet->m_pfnReport_Set_Failed( psTest_Context, psSet, u8"INIT" );
                }
                else if (psTest_Context->m_pfnReport_Set_Failed)
                {
                    psTest_Context->m_pfnReport_Set_Failed( psTest_Context, psSet, u8"INIT" );
                };

                break;
            }
            else
            {
                if (psSet->m_pfnReport_Set_Passed)
                {
                    psSet->m_pfnReport_Set_Passed( psTest_Context, psSet, u8"INIT" );
                }
                else if (psTest_Context->m_pfnReport_Set_Passed)
                {
                    psTest_Context->m_pfnReport_Set_Passed( psTest_Context, psSet, u8"INIT" );
                };
            }
        };

        if (psSet != psSet_Start || bOutput_Message)
        {
            psSet->m_bPassed = true;

            if (psSet->m_pfnReport_Set_Header)
            {
                psSet->m_pfnReport_Set_Header( psTest_Context, psSet );
            }
            else if (psTest_Context->m_pfnReport_Set_Header)
            {
                psTest_Context->m_pfnReport_Set_Header( psTest_Context, psSet );
            };
        }

        tgProfile_Sample_Start( &g_sPROFILE_UNIT_TEST__TEST_SET__EXECUTE );
        iResult = Unit_Test__Case_Execute( psTest_Context, psSet->m_psFirst_Case );
        tgProfile_Sample_Stop( &g_sPROFILE_UNIT_TEST__TEST_SET__EXECUTE );

        if (TgFAILED(iResult))
        {
            psSet->m_bPassed = false;
            tgRet = KTgE_FAIL;

            /* Test to see if there are any further tests in the set to re-enter */
            if (nullptr == psTest_Context->m_psRestart_Case)
            {
                psTest_Context->m_psRestart_Set = psSet->m_psNext;

                /* Wrap up the end of this test set */
                ++psTest_Context->m_nuiSet_Failed;

                if (psSet->m_pfnReport_Set_Footer)
                {
                    psSet->m_pfnReport_Set_Footer( psTest_Context, psSet );
                }
                else if (psTest_Context->m_pfnReport_Set_Footer)
                {
                    psTest_Context->m_pfnReport_Set_Footer( psTest_Context, psSet );
                };
            }
            else
            {
                /* The set will be re-entrant */
                psTest_Context->m_psRestart_Set = psSet;
            };
        }
        else
        {
            if (psSet->m_bPassed)
            {
                ++psTest_Context->m_nuiSet_Passed;
            }
            else
            {
                ++psTest_Context->m_nuiSet_Failed;
            };

            if (psSet->m_pfnReport_Set_Footer)
            {
                psSet->m_pfnReport_Set_Footer( psTest_Context, psSet );
            }
            else if (psTest_Context->m_pfnReport_Set_Footer)
            {
                psTest_Context->m_pfnReport_Set_Footer( psTest_Context, psSet );
            };
        };

        ++psTest_Context->m_nuiSet_Total;

        if (nullptr != psSet->m_pfnFree)
        {
            if (TgFAILED( psSet->m_pfnFree() ))
            {
                psTest_Context->m_psRestart_Set = psSet->m_psNext;
                tgRet = KTgE_FAIL;

                if (psSet->m_pfnReport_Set_Failed)
                {
                    psSet->m_pfnReport_Set_Failed( psTest_Context, psSet, u8"FREE" );
                }
                else if (psTest_Context->m_pfnReport_Set_Failed)
                {
                    psTest_Context->m_pfnReport_Set_Failed( psTest_Context, psSet, u8"FREE" );
                };
            }
            else
            {
                if (psSet->m_pfnReport_Set_Passed)
                {
                    psSet->m_pfnReport_Set_Passed( psTest_Context, psSet, u8"FREE" );
                }
                else if (psTest_Context->m_pfnReport_Set_Passed)
                {
                    psTest_Context->m_pfnReport_Set_Passed( psTest_Context, psSet, u8"FREE" );
                };
            };
        };
    };

    return (tgRet);
}


/* ---- Unit_Test__Context_Init -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID Unit_Test__Context_Init( Test_Context_PCU psContext )
{
    tgMM_Set_U08_0x00( psContext, sizeof( Test_Context ) );

    psContext->m_bReport_Case_Report = true;
    psContext->m_bReport_Set_Report = true;
    psContext->m_bReport_Context_Report = true;

    psContext->m_pfnReport_Case_Report_Passed = Default_Report_Case_Report_Passed;
    psContext->m_pfnReport_Case_Report_Failed = Default_Report_Case_Report_Failed;
    psContext->m_pfnReport_Case_Passed = Default_Report_Case_Passed;
    psContext->m_pfnReport_Case_Failed = Default_Report_Case_Failed;
    psContext->m_pfnReport_Set_Header = Default_Report_Set_Header;
    psContext->m_pfnReport_Set_Footer = Default_Report_Set_Footer;
    psContext->m_pfnReport_Set_Passed = Default_Report_Set_Passed;
    psContext->m_pfnReport_Set_Failed = Default_Report_Set_Failed;
    psContext->m_pfnReport_Context_Header = Default_Report_Context_Header;
    psContext->m_pfnReport_Context_Footer = Default_Report_Context_Footer;
    psContext->m_pfnReport_Context_Passed = Default_Report_Context_Passed;
    psContext->m_pfnReport_Context_Failed = Default_Report_Context_Failed;
}


/* ---- Unit_Test__Register ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID Unit_Test__Register( Test_Set_PC psSet )
{
    if (0 == g_psTest_Set_Start)
    {
        g_psTest_Set_Start = psSet;
    }
    else
    {
        Test_Set_P                              psTest_Set = g_psTest_Set_Start;

        for (; 0 != psTest_Set->m_psNext; psTest_Set = psTest_Set->m_psNext);
        psTest_Set->m_psNext = psSet;
        psSet->m_psPrev = psTest_Set;
    };
}


/* ---- Unit_Test__Execute ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT Unit_Test__Execute( Test_Context_PC psTest_Context )
{
    TgBOOL                                  bExecute_Loop = true;
    TgRESULT                                tgRet = KTgS_OK;

    if (nullptr != psTest_Context->m_pfnReport_Context_Header)
    {
        psTest_Context->m_pfnReport_Context_Header( psTest_Context );
    };

    while (bExecute_Loop)
    {
        /* UNIT TEST - CONTEXT INIT ---------------------------------------------------------------------------------------------------------------------------------------------- */
        if ((nullptr != psTest_Context->m_pfnInit) && TgFAILED( psTest_Context->m_pfnInit() ))
        {
            if (nullptr != psTest_Context->m_pfnReport_Context_Failed)
            {
                psTest_Context->m_pfnReport_Context_Failed( psTest_Context, u8"INIT" );
            };

            return (KTgE_FAIL);
        }
        else
        {
            if (nullptr != psTest_Context->m_pfnReport_Context_Passed)
            {
                psTest_Context->m_pfnReport_Context_Passed( psTest_Context, u8"INIT" );
            };
        }


        /* UNIT TEST - CONTEXT BOOT ---------------------------------------------------------------------------------------------------------------------------------------------- */
        if ((nullptr != psTest_Context->m_pfnBoot) && TgFAILED( psTest_Context->m_pfnBoot() ))
        {
            if (nullptr != psTest_Context->m_pfnReport_Context_Failed)
            {
                psTest_Context->m_pfnReport_Context_Failed( psTest_Context, u8"BOOT" );
            };

            tgRet = KTgE_FAIL;
            bExecute_Loop = false;
        }
        else
        {
            Test_Set_P                              psRestart_Set = psTest_Context->m_psRestart_Set;

            if (nullptr != psTest_Context->m_pfnReport_Context_Passed)
            {
                psTest_Context->m_pfnReport_Context_Passed( psTest_Context, u8"BOOT" );
            };

            if (TgFAILED( Unit_Test__Set_Execute( psTest_Context, 0 != psRestart_Set ? psRestart_Set : g_psTest_Set_Start ) ))
            {
                if (psTest_Context->m_bFail_On_First_Fail || nullptr == psTest_Context->m_psRestart_Set)
                {
                    tgRet = KTgE_FAIL;
                    bExecute_Loop = false;
                };
            }
            else
            {
                bExecute_Loop = false;
            };

            /* UNIT TEST - CONTEXT STOP ------------------------------------------------------------------------------------------------------------------------------------------ */
            if ((nullptr != psTest_Context->m_pfnStop) && TgFAILED( psTest_Context->m_pfnStop() ))
            {
                if (nullptr != psTest_Context->m_pfnReport_Context_Failed)
                {
                    psTest_Context->m_pfnReport_Context_Failed( psTest_Context, u8"STOP" );
                };

                tgRet = KTgE_FAIL;
                bExecute_Loop = false;
            }
            else
            {
                if (nullptr != psTest_Context->m_pfnReport_Context_Passed)
                {
                    psTest_Context->m_pfnReport_Context_Passed( psTest_Context, u8"STOP" );
                };
            };
        }


        /* UNIT TEST - CONTEXT FREE ---------------------------------------------------------------------------------------------------------------------------------------------- */
        if ((nullptr != psTest_Context->m_pfnFree) && TgFAILED( psTest_Context->m_pfnFree() ))
        {
            if (nullptr != psTest_Context->m_pfnReport_Context_Failed)
            {
                psTest_Context->m_pfnReport_Context_Failed( psTest_Context, u8"FREE" );
            };

            return (KTgE_FAIL);
        }
        else
        {
            if (nullptr != psTest_Context->m_pfnReport_Context_Passed)
            {
                psTest_Context->m_pfnReport_Context_Passed( psTest_Context, u8"FREE" );
            };
        };
    };

    if (nullptr != psTest_Context->m_pfnReport_Context_Footer)
    {
        psTest_Context->m_pfnReport_Context_Footer( psTest_Context );
    };

    return (tgRet);
}


/* ---- Default_Report_Case_Report_Passed ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID Default_Report_Case_Report_Passed( Test_Context_PC psTest_Context, Test_Case_PC psCase_Test, TgUINT_E32_C uiTest )
{
    if (psTest_Context->m_bReport_Case_Report)
    {
        if (psCase_Test->m_apszTest[uiTest])
        {
            TgMSGF( 0, UNIT_TEST__MSG_LITERAL_2, u8"PASSED:", psCase_Test->m_pszSet, psCase_Test->m_pszCase, psCase_Test->m_apszTest[uiTest] );
        }
        else
        {
            TgMSGF( 0, UNIT_TEST__MSG_LITERAL_1, u8"PASSED:", psCase_Test->m_pszSet, psCase_Test->m_pszCase );
        };
    };
}


/* ---- Default_Report_Case_Report_Failed ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID Default_Report_Case_Report_Failed( Test_Context_PC psTest_Context, Test_Case_PC psCase_Test, TgUINT_E32_C uiTest )
{
    if (psTest_Context->m_bIgnore_On_Fail)
    {
        if (psTest_Context->m_bReport_Case_Report)
        {
            if (psCase_Test->m_apszTest[uiTest])
            {
                TgMSGF( 0x0, UNIT_TEST__MSG_LITERAL_2, u8"FAILED:", u8"Test Set:", psCase_Test->m_pszSet, u8"Test Case:", psCase_Test->m_pszCase, psCase_Test->m_apszTest[uiTest] );
            }
            else
            {
                TgMSGF( 0x0, UNIT_TEST__MSG_LITERAL_1, u8"FAILED:", u8"Test Set:", psCase_Test->m_pszSet, u8"Test Case:", psCase_Test->m_pszCase );
            };
        };
    }
    else
    {
        if (psCase_Test->m_apszTest[uiTest])
        {
            TgMSGF( 0x0, UNIT_TEST__MSG_LITERAL_2, u8"FAILED:", psCase_Test->m_pszSet, psCase_Test->m_pszCase, psCase_Test->m_apszTest[uiTest] );
        }
        else
        {
            TgMSGF( 0x0, UNIT_TEST__MSG_LITERAL_1, u8"FAILED:", psCase_Test->m_pszSet, psCase_Test->m_pszCase );
        };
    };
}


/* ---- Default_Report_Case_Passed ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID Default_Report_Case_Passed( Test_Context_PC psTest_Context, Test_Case_PC psCase_Test, TgCHAR_U8_CPC szMsg )
{
    (void)psCase_Test; // -Wunused-parameter
    (void)szMsg; // -Wunused-parameter
    if (psTest_Context->m_bReport_Case_Result)
    {
        TgMSGF( 0x0, UNIT_TEST__MSG_LITERAL_2, u8"PASSED:", psCase_Test->m_pszSet, psCase_Test->m_pszCase, szMsg );
    };
}


/* ---- Default_Report_Case_Failed ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID Default_Report_Case_Failed( Test_Context_PC psTest_Context, Test_Case_PC psCase_Test, TgCHAR_U8_CPC szMsg )
{
    (void)psCase_Test; // -Wunused-parameter
    (void)szMsg; // -Wunused-parameter
    if (psTest_Context->m_bIgnore_On_Fail)
    {
        if (psTest_Context->m_bReport_Set_Result)
        {
            TgMSGF( 0x0, UNIT_TEST__MSG_LITERAL_2, u8"FAILED:", psCase_Test->m_pszSet, psCase_Test->m_pszCase, szMsg );
        };
    }
    else
    {
        TgMSGF( 0x0, UNIT_TEST__MSG_LITERAL_2, u8"FAILED:", psCase_Test->m_pszSet, psCase_Test->m_pszCase, szMsg );
    };
}


/* ---- Default_Report_Set_Header ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID Default_Report_Set_Header( Test_Context_PC psTest_Context, TgATTRIBUTE_UNUSED Test_Set_PC psSet_Test )
{
    tgProfile_Sample_Reset( &g_sPROFILE_UNIT_TEST__TEST_SET__EXECUTE );
    tgProfile_Sample_Start( &g_sPROFILE_UNIT_TEST__TEST_SET__EXECUTE );

    if (psTest_Context->m_bReport_Set_Report)
    {
        TgMSGF( 0x0, UNIT_TEST__MSG_LITERAL_2, u8"", u8"TEST SET", u8"CASE", u8"TEST" );
    };
    tgProfile_Sample_Stop( &g_sPROFILE_UNIT_TEST__TEST_SET__EXECUTE );
}


/* ---- Default_Report_Set_Footer ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID Default_Report_Set_Footer( Test_Context_PC psTest_Context, Test_Set_PC psSet_Test )
{
    TgFLOAT64                               fExecute;
    TgUINT_E64                              uiExecute;
    TgCHAR_U8                               szExecute[32], szExecuteMSG[32];

    tgProfile_Sample_Report( &g_sPROFILE_UNIT_TEST__TEST_SET__EXECUTE );
    fExecute = (TgFLOAT64)g_sPROFILE_UNIT_TEST__TEST_SET__EXECUTE.m_fReport_Sample;
    uiExecute = (TgUINT_E64)(tgPM_FLOOR_F64( 1000.0 * fExecute ));
    tgUSZ_Formatted_From_U64( szExecute, sizeof( szExecute ), uiExecute );
    tgUSZ_PrintF( szExecuteMSG, sizeof( szExecuteMSG ), u8"%s ns", szExecute );

    tgProfile_Sample_Start( &g_sPROFILE_UNIT_TEST__TEST_SET__EXECUTE );
    if (psSet_Test->m_bPassed)
    {
        if (psTest_Context->m_bReport_Set_Report)
        {
            TgMSGF( 0x0, UNIT_TEST__MSG_LITERAL_2, u8"PASSED:", psSet_Test->m_szSet, u8"", szExecuteMSG );
        };
    }
    else
    {
        if (psTest_Context->m_bIgnore_On_Fail)
        {
            if (psTest_Context->m_bReport_Set_Report)
            {
                TgMSGF( 0x0, UNIT_TEST__MSG_LITERAL_2, u8"FAILED:", psSet_Test->m_szSet, u8"", szExecuteMSG );
            };
        }
        else
        {
            TgMSGF( 0x0, UNIT_TEST__MSG_LITERAL_2, u8"FAILED:", psSet_Test->m_szSet, u8"", szExecuteMSG );
        };
    };
    tgProfile_Sample_Stop( &g_sPROFILE_UNIT_TEST__TEST_SET__EXECUTE );
}


/* ---- Default_Report_Set_Passed ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID Default_Report_Set_Passed( Test_Context_PC psTest_Context, Test_Set_PC psSet_Test, TgCHAR_U8_CPC szMsg )
{
    (void)psSet_Test; // -Wunused-parameter
    (void)szMsg; // -Wunused-parameter
    if (psTest_Context->m_bReport_Set_Result)
    {
        TgMSGF( 0x0, UNIT_TEST__MSG_LITERAL_2, u8"PASSED:", psSet_Test->m_szSet, u8"", szMsg );
    };
}


/* ---- Default_Report_Set_Failed ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID Default_Report_Set_Failed( Test_Context_PC psTest_Context, Test_Set_PC psSet_Test, TgCHAR_U8_CPC szMsg )
{
    (void)psSet_Test; // -Wunused-parameter
    (void)szMsg; // -Wunused-parameter
    if (psTest_Context->m_bIgnore_On_Fail)
    {
        if (psTest_Context->m_bReport_Set_Result)
        {
            TgMSGF( 0x0, UNIT_TEST__MSG_LITERAL_2, u8"FAILED:", psSet_Test->m_szSet, u8"", szMsg );
        };
    }
    else
    {
        TgMSGF( 0x0, UNIT_TEST__MSG_LITERAL_2, u8"FAILED:", psSet_Test->m_szSet, u8"", szMsg );
    };
}


/* ---- Default_Report_Context_Header -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID Default_Report_Context_Header( TgATTRIBUTE_UNUSED Test_Context_PC psTest_Context )
{
}


/* ---- Default_Report_Context_Footer -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID Default_Report_Context_Footer( Test_Context_PC psTest_Context )
{
    if (psTest_Context->m_bReport_Context_Report)
    {
    };
}


/* ---- Default_Report_Context_Passed -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID Default_Report_Context_Passed( Test_Context_PC psTest_Context, TgCHAR_U8_CPC szMsg )
{
    if (psTest_Context->m_bReport_Context_Result)
    {
        TgCHAR_U8                               szBuffer[1024];

        tgUSZ_PrintF( szBuffer, 1024, UNIT_TEST__MSG_LITERAL_2, u8"PASSED:", u8"TEST CONTEXT", u8"", szMsg );
        tgCM_DBG_OUT_Write( 0, KTgMAX_RSIZE, szBuffer, 0 );
    };
}


/* ---- Default_Report_Context_Failed -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID Default_Report_Context_Failed( Test_Context_PC psTest_Context, TgCHAR_U8_CPC szMsg )
{
    if (psTest_Context->m_bIgnore_On_Fail)
    {
        if (psTest_Context->m_bReport_Context_Result)
        {
            TgCHAR_U8                               szBuffer[1024];

            tgUSZ_PrintF( szBuffer, 1024, UNIT_TEST__MSG_LITERAL_2, u8"FAILED:", u8"TEST CONTEXT", u8"", szMsg );
            tgCM_DBG_OUT_Write( 0, KTgMAX_RSIZE, szBuffer, 0 );
        };
    }
    else
    {
        TgCHAR_U8                               szBuffer[1024];

        tgUSZ_PrintF( szBuffer, 1024, UNIT_TEST__MSG_LITERAL_2, u8"FAILED:", u8"TEST CONTEXT", u8"", szMsg );
        tgCM_DBG_OUT_Write( 0, KTgMAX_RSIZE, szBuffer, 0 );

        tgPM_Break();
    };
}
