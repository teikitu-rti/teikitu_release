/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (UWP) Common [Unit Test].cpp
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.12 | »GUID« 964CB1A6-814D-4E19-8E67-A83FCA98BF05 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include <collection.h>
#include <ppltasks.h>
#include "TgS COMMON/TgS (UWP) Common - Unit Test.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Unit Test Data                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TgEXTN STg2_Output                          g_sErrOut, g_sStdOut;




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TgEXTN TgRESULT                             Test_Context__Init( TgVOID );
TgEXTN TgRESULT                             Test_Context__Boot( TgVOID );
TgEXTN TgRESULT                             Test_Context__Stop( TgVOID );
TgEXTN TgRESULT                             Test_Context__Free( TgVOID );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

namespace Unit_Test___Ring_0___TgS_COMMON
{
    TEST_MODULE_INITIALIZE( ModuleInitialize )
    {
        Logger::WriteMessage( "In Module Initialize" );

    #if defined(TgCOMPILE_PLATFORM_W64)
        // Additional heap checking.
        _CrtSetDbgFlag( _crtDbgFlag | _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF | _CRTDBG_CHECK_CRT_DF );
        _CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_DEBUG );
    #endif // #if defined(TgCOMPILE_PLATFORM_W64)

        g_sErrOut.m_pfnSeek = tgCM_DBG_ERR_Seek;
        g_sErrOut.m_pfnWrite = tgCM_DBG_ERR_Write;
        g_sErrOut.m_pfnClose = nullptr;

        g_sStdOut.m_pfnSeek = tgCM_DBG_OUT_Seek;
        g_sStdOut.m_pfnWrite = tgCM_DBG_OUT_Write;
        g_sStdOut.m_pfnClose = nullptr;
    }


    TEST_MODULE_CLEANUP( ModuleCleanup )
    {
        Logger::WriteMessage( "In Module Cleanup" );
    }


    TEST_CLASS( UnitTest_BASE )
    {
    public:
        BASE_TEST_CLASS_IMPL( UnitTest_BASE )
        #include "TgS Common [Unit Test] - Base.c_inc"
    };
    STg2_UTM_SN UnitTest_BASE::s_sUT_MP_SN_0;
    STg2_UTM_SN UnitTest_BASE::s_sUT_MP_SN_1;

    TEST_CLASS( UnitTest_COMMON )
    {
    public:
        BASE_TEST_CLASS_IMPL( UnitTest_COMMON )
        #include "TgS Common [Unit Test] - Common.c_inc"
    };
    TgATOMIC_INT32 UnitTest_COMMON::g_iTestValue;
    TgPROFILE_ID UnitTest_COMMON::s_tiProfile;

    TEST_CLASS( UnitTest_MATH )
    {
    public:
        BASE_TEST_CLASS_IMPL( UnitTest_MATH )
        #include "TgS Common [Unit Test] - Math.c_inc"
        #include "TgS Common [Unit Test] - Math API [Vector].c_inc"
    };

    TEST_CLASS( UnitTest_GEOM )
    {
    public:
        BASE_TEST_CLASS_IMPL( UnitTest_GEOM )
        #include "TgS Common [Unit Test] - Geometry.c_inc"
    };

    TEST_CLASS( UnitTest_UTILITY )
    {
    public:
        BASE_TEST_CLASS_IMPL( UnitTest_UTILITY )
        #include "TgS Common [Unit Test] - Util MP - Hash Table.c_inc"
        #include "TgS Common [Unit Test] - Util MP - LA Array [Free List].c_inc"
        #include "TgS Common [Unit Test] - Util MP - LA Ring Buffer SRSW.c_inc"
        #include "TgS Common [Unit Test] - Util MP - List.c_inc"
        #include "TgS Common [Unit Test] - Util MP - Queue.c_inc"
        #include "TgS Common [Unit Test] - Util MP - Reader Writer Lock.c_inc"
        #include "TgS Common [Unit Test] - Util MP - Spin Lock.c_inc"
        #include "TgS Common [Unit Test] - Util MP - Stack.c_inc"
        #include "TgS Common [Unit Test] - Util SP - LA Array [Free List].c_inc"
        #include "TgS Common [Unit Test] - Util SP - String.c_inc"
    };
    STg1_MT_SM UnitTest_UTILITY::s_sTest_Count;
    STg2_UTM_AM_RW UnitTest_UTILITY::s_sAM_RW;
    STg2_UTM_SN_RW UnitTest_UTILITY::s_sSN_RW;
    STg2_UTM_RW UnitTest_UTILITY::s_sRW;
    TgSINT_E32 UnitTest_UTILITY::s_iCommand_Expected_Results[ETgRWLOCK_COMMAND_SIZE];
    TgUINT_E08 UnitTest_UTILITY::s_uiCommand_List[ETgRWLOCK_COMMAND_SIZE];
    TgSINT_E32 UnitTest_UTILITY::s_iCommand_Results[ETgRWLOCK_COMMAND_SIZE];
    TgATOMIC_INT32 UnitTest_UTILITY::s_niCommand_Read;
    TgATOMIC_INT32 UnitTest_UTILITY::s_niCommand_Execute;
    TgATOMIC_INT32 UnitTest_UTILITY::s_niCommand_Write;
    TgCHAR_U8 UnitTest_UTILITY::s_szTest_63[63] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    TgCHAR_U8 UnitTest_UTILITY::s_szTest_27[27] = "AbCdEfGhIjKlMnOpQrStUvWxYz";
    TgCHAR_U8 UnitTest_UTILITY::s_szTest_04[4] = "Za4";
    TgCHAR_U8 UnitTest_UTILITY::s_szTest_01[2] = "~";
    TgCHAR_U8 UnitTest_UTILITY::s_szTest_Not_04[60] = "012356789bcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXY";
    TgCHAR_U8_CP UnitTest_UTILITY::s_pszTest[ETgSTRING_UNIT_TEST__MAX_TEST] = { 0, s_szTest_01, s_szTest_04, s_szTest_27, s_szTest_63 };
    TgRSIZE UnitTest_UTILITY::s_uiTest[ETgSTRING_UNIT_TEST__MAX_TEST + 1] = { 0, 1, 3, 26, 62, 75 };
}
