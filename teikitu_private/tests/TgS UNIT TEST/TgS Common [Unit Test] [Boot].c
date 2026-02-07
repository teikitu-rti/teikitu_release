/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common [Unit Test] [Boot].c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "../TgS UNIT TEST/TgS Common [Unit Test] - Unit Test.h"

#include "TgS Common.h"

#if TgS_RING_LEVEL >= 0 || defined(TgS_UNIT_TEST__COLLISION)
#include "TgS Collision.h"
#endif
#if TgS_RING_LEVEL >= 0 || defined(TgS_UNIT_TEST__PARTITION)
#include "TgS Partition.h"
#endif
#if TgS_RING_LEVEL >= 0 || defined(TgS_UNIT_TEST__PATH_AI)
#include "TgS Path-AI.h"
#endif
#if TgS_RING_LEVEL >= 2 || defined(TgS_UNIT_TEST__KERNEL)
#include "TgS Kernel.h"
#include "TgS Utility.h"
#if defined(TgBUILD_FEATURE__GRAPHICS)
#include "TgS Kernel [GPU].h"
#endif
#endif
#if TgS_RING_LEVEL >= 3 || defined(TgS_UNIT_TEST__ANIMATION)
#include "TgS Animation.h"
#endif
#if TgS_RING_LEVEL >= 3 || defined(TgS_UNIT_TEST__INPUT)
#include "TgS Input.h"
#endif
#if TgS_RING_LEVEL >= 3 || defined(TgS_UNIT_TEST__PHYSICS)
#include "TgS Physics.h"
#endif
#if TgS_RING_LEVEL >= 3 || defined(TgS_UNIT_TEST__RENDER)
#include "TgS Render.h"
#endif
#if TgS_RING_LEVEL >= 3 || defined(TgS_UNIT_TEST__SOUND)
#include "TgS Sound.h"
#endif
#if TgS_RING_LEVEL >= 4 || defined(TgS_UNIT_TEST__EFFECT)
#include "TgS Effect.h"
#endif
#if TgS_RING_LEVEL >= 4 || defined(TgS_UNIT_TEST__OBJECT)
#include "TgS Object.h"
#endif
#if TgS_RING_LEVEL >= 4 || defined(TgS_UNIT_TEST__SCRIPT)
#include "TgS Set.h"
#endif
#if TgS_RING_LEVEL >= 4 || defined(TgS_UNIT_TEST__SET)
#include "TgS Script.h"
#endif
#if TgS_RING_LEVEL >= 5 || defined(TgS_UNIT_TEST__EXECUTION)
    if (TgFAILED(tgEX_Module_Init()))
        goto FAIL_Test_Context__Init;
#endif

#if defined(TgBUILD_OS__WINDOWS)
#include "TgS COMMON/TgS (WINDOWS) Common - Base - Include.h"
#include "TgS COMMON/TgS (WINDOWS) Common - Base - Type.h"
#endif
typedef struct HINSTANCE__ *HINSTANCE;

TgMSVC_PRAGMA(warning( push, 0 ))
#if defined(TgBUILD_OS__WINDOWS) && defined(_DEBUG )
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
/*# defined(TgBUILD_OS__WINDOWS) && defined(_DEBUG ) */
#endif
TgMSVC_PRAGMA(warning( pop ))
TgCLANG_WARN_SUPPRESS(missing-prototypes)

#include <stdlib.h>


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Unit Test Data                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

static STg2_Output                          g_sErrOut, g_sStdOut;

#if defined(TgBUILD_OS__WINDOWS) && defined(_DEBUG )
TgEXTN HINSTANCE                            g_hInstance;
static _CrtMemState                         s_sMemState0;
/*# defined(TgBUILD_OS__WINDOWS) && defined(_DEBUG ) */
#endif

/* static PROFILE_DEFINE( PROFILE_UNIT_TEST__EXECUTE ); */




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Local CRT Memory Function                                                                                                                                                      */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

void CDECL Test_End_Process(void) TgATTRIBUTE_NO_EXCEPT
{
#if defined(TgBUILD_OS__WINDOWS) && defined(_DEBUG )
  _CrtMemState                        sMemState1, sMemState2;
    _CrtMemCheckpoint( &sMemState1 );
    if (_CrtMemDifference( &sMemState2, &s_sMemState0, &sMemState1 ))
        _CrtMemDumpStatistics( &sMemState2 );
    _CrtMemDumpAllObjectsSince( &s_sMemState0 );
/*# defined(TgBUILD_OS__WINDOWS) && defined(_DEBUG ) */
#endif
}

TgBOOL g_bUnit_Test__Enabled_ERR_Write = true;
static TgRSIZE tgUnit_Test__DBG_ERR_Write( STg2_Output_PC psOut, TgRSIZE_C uiOffset, TgVOID_CP mbzText, TgRSIZE_C _niText)
{
    if (g_bUnit_Test__Enabled_ERR_Write)
    {
        return (tgCM_DBG_ERR_Write( psOut, uiOffset, mbzText, _niText));
    };
    return (0);
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TgRESULT Test_Context__Init( TgVOID )
{
    if (TgFAILED(tgGB_Init()))
        goto FAIL_Test_Context__Init;

#if TgCOMPILE__CONSOLE
    tgCN_Attach_Output( KTgCN_CHANEL_INITIALIZE, &g_sStdOut );
    tgCN_Attach_Output( KTgCN_CHANEL_LOADING, &g_sStdOut );
    tgCN_Attach_Output( KTgCN_CHANEL_MESSAGE, &g_sStdOut );
    tgCN_Attach_Output( KTgCN_CHANEL_WARNING, &g_sStdOut );
    tgCN_Attach_Output( KTgCN_CHANEL_ERROR, &g_sErrOut );
    tgCN_Attach_Output( KTgCN_CHANEL_CONSOLE, &g_sStdOut );
    tgCN_Attach_Output( KTgCN_CHANEL_LOG, &g_sStdOut );

    tgCN_Attach_Default_Break( KTgCN_CHANEL_ERROR );

    tgCN_Set_Severity_Filter( KTgCN_CHANEL_INITIALIZE, KTgCN_SEVERITY_7 );
    tgCN_Set_Severity_Filter( KTgCN_CHANEL_MESSAGE, KTgCN_SEVERITY_7 );
    tgCN_Set_Severity_Filter( KTgCN_CHANEL_ERROR, KTgCN_SEVERITY_7 );
/*# TgCOMPILE__CONSOLE */
#endif

    tgGB_CMD_Push_Argument( u8"-//stat/boot/info" );
    tgGB_CMD_Push_Argument( u8"-//stat/boot/memory" );
    tgGB_CMD_Push_Argument( u8"-//stat/free/memory" );

#if defined(TgS_UNIT_TEST__COMMON)
    tgGB_CMD_Push_Argument( u8"-//test/unit/common" );
#endif
#if defined(TgS_UNIT_TEST__COLLISION)
    tgGB_CMD_Push_Argument( u8"-//test/unit/collision" );
#endif
#if defined(TgS_UNIT_TEST__KERNEL)
#if defined(TgBUILD_FEATURE__GRAPHICS)
    tgGB_CMD_Push_Argument( u8"-//test/unit/kernel/gpu" );
#else
    tgGB_CMD_Push_Argument( u8"-//test/unit/kernel" );
#endif
#endif
#if defined(TgS_UNIT_TEST__ANIMATION)
    tgGB_CMD_Push_Argument( u8"-//test/unit/animation" );
#endif
#if defined(TgS_UNIT_TEST__INPUT)
    tgGB_CMD_Push_Argument( u8"-//test/unit/input" );
#endif
#if defined(TgS_UNIT_TEST__PHYSICS)
    tgGB_CMD_Push_Argument( u8"-//test/unit/physics" );
#endif
#if defined(TgS_UNIT_TEST__RENDER)
    tgGB_CMD_Push_Argument( u8"-//test/unit/render" );
#endif
#if defined(TgS_UNIT_TEST__SOUND)
    tgGB_CMD_Push_Argument( u8"-//test/unit/sound" );
#endif
#if defined(TgS_UNIT_TEST__EFFECT)
    tgGB_CMD_Push_Argument( u8"-//test/unit/effect" );
#endif
#if defined(TgS_UNIT_TEST__OBJECT)
    tgGB_CMD_Push_Argument( u8"-//test/unit/object" );
#endif
#if defined(TgS_UNIT_TEST__SET)
    tgGB_CMD_Push_Argument( u8"-//test/unit/set" );
#endif
#if defined(TgS_UNIT_TEST__EXECUTION)
    tgGB_CMD_Push_Argument( u8"-//test/unit/execution" );
#endif


#if TgS_RING_LEVEL >= 0 || defined(TgS_UNIT_TEST__PARTITION)
    if (TgFAILED(tgPA_Module_Init()))
        goto FAIL_Test_Context__Init;
#endif
#if TgS_RING_LEVEL >= 0 || defined(TgS_UNIT_TEST__COLLISION)
    if (TgFAILED(tgCO_Module_Init()))
        goto FAIL_Test_Context__Init;
#endif
#if TgS_RING_LEVEL >= 2 || defined(TgS_UNIT_TEST__KERNEL)
    if (TgFAILED(tgKN_Module_Init()))
        goto FAIL_Test_Context__Init;
#if defined(TgBUILD_FEATURE__GRAPHICS)
    if (TgFAILED(tgKN_GPU_Module_Init())) {
        goto FAIL_Test_Context__Init;
    }
#endif
#endif
#if TgS_RING_LEVEL >= 3 || defined(TgS_UNIT_TEST__ANIMATION)
    if (TgFAILED(tgAM_Module_Init()))
        goto FAIL_Test_Context__Init;
#endif
#if TgS_RING_LEVEL >= 3 || defined(TgS_UNIT_TEST__INPUT)
    if (TgFAILED(tgIN_Module_Init()))
        goto FAIL_Test_Context__Init;
#endif
#if TgS_RING_LEVEL >= 3 || defined(TgS_UNIT_TEST__PHYSICS)
    if (TgFAILED(tgPH_Module_Init()))
        goto FAIL_Test_Context__Init;
#endif
#if TgS_RING_LEVEL >= 3 || defined(TgS_UNIT_TEST__RENDER)
    if (TgFAILED(tgRN_Module_Init()))
        goto FAIL_Test_Context__Init;
#endif
#if TgS_RING_LEVEL >= 3 || defined(TgS_UNIT_TEST__SOUND)
    if (TgFAILED(tgSN_Module_Init()))
        goto FAIL_Test_Context__Init;
#endif
#if TgS_RING_LEVEL >= 4 || defined(TgS_UNIT_TEST__EFFECT)
    if (TgFAILED(tgFX_Module_Init()))
        goto FAIL_Test_Context__Init;
#endif
#if TgS_RING_LEVEL >= 4 || defined(TgS_UNIT_TEST__OBJECT)
    if (TgFAILED(tgOB_Module_Init()))
        goto FAIL_Test_Context__Init;
#endif
#if TgS_RING_LEVEL >= 4 || defined(TgS_UNIT_TEST__SET)
    if (TgFAILED(tgSE_Module_Init()))
        goto FAIL_Test_Context__Init;
#endif
#if TgS_RING_LEVEL >= 5 || defined(TgS_UNIT_TEST__EXECUTION)
    if (TgFAILED(tgEX_Module_Init()))
        goto FAIL_Test_Context__Init;
#endif

    return (KTgS_OK);

FAIL_Test_Context__Init:
#if TgS_RING_LEVEL >= 5
    tgSE_Module_Free();
#endif
#if TgS_RING_LEVEL >= 4
    tgOB_Module_Free();
    tgFX_Module_Free();
    tgSN_Module_Free();
#endif
#if TgS_RING_LEVEL >= 3
    tgRN_Module_Free();
    tgPH_Module_Free();
    tgIN_Module_Free();
    tgAM_Module_Free();
    tgKN_Module_Free();
#endif
#if TgS_RING_LEVEL >= 2
    tgCO_Module_Free();
#endif
    tgGB_Free();
    return (KTgE_FAIL);
}


TgRESULT Test_Context__Boot( TgVOID )
{
    if (TgFAILED(tgGB_Boot()))
        goto FAIL_Test_Context__Boot;

#if TgS_RING_LEVEL >= 0 || defined(TgS_UNIT_TEST__COLLISION)
    if (TgFAILED(tgCO_Module_Boot()))
        goto FAIL_Test_Context__Boot;
#endif
#if TgS_RING_LEVEL >= 2 || defined(TgS_UNIT_TEST__KERNEL)
    if (TgFAILED(tgKN_Module_Boot()))
        goto FAIL_Test_Context__Boot;
#if defined(TgBUILD_FEATURE__GRAPHICS)
    if (TgFAILED(tgKN_GPU_Module_Boot())) {
        goto FAIL_Test_Context__Boot;
    }
#endif
#endif
#if TgS_RING_LEVEL >= 3 || defined(TgS_UNIT_TEST__ANIMATION)
    if (TgFAILED(tgAM_Module_Boot()))
        goto FAIL_Test_Context__Boot;
#endif
#if TgS_RING_LEVEL >= 3 || defined(TgS_UNIT_TEST__INPUT)
    if (TgFAILED(tgIN_Module_Boot()))
        goto FAIL_Test_Context__Boot;
#endif
#if TgS_RING_LEVEL >= 3 || defined(TgS_UNIT_TEST__PHYSICS)
    if (TgFAILED(tgPH_Module_Boot()))
        goto FAIL_Test_Context__Boot;
#endif
#if TgS_RING_LEVEL >= 3 || defined(TgS_UNIT_TEST__RENDER)
    if (TgFAILED(tgRN_Module_Boot()))
        goto FAIL_Test_Context__Boot;
#endif
#if TgS_RING_LEVEL >= 3 || defined(TgS_UNIT_TEST__SOUND)
    if (TgFAILED(tgSN_Module_Boot()))
        goto FAIL_Test_Context__Boot;
#endif
#if TgS_RING_LEVEL >= 4 || defined(TgS_UNIT_TEST__EFFECT)
    if (TgFAILED(tgFX_Module_Boot()))
        goto FAIL_Test_Context__Boot;
#endif
#if TgS_RING_LEVEL >= 4 || defined(TgS_UNIT_TEST__OBJECT)
    if (TgFAILED(tgOB_Module_Boot()))
        goto FAIL_Test_Context__Boot;
#endif
#if TgS_RING_LEVEL >= 4 || defined(TgS_UNIT_TEST__SET)
    if (TgFAILED(tgSE_Module_Boot()))
        goto FAIL_Test_Context__Boot;
#endif
#if TgS_RING_LEVEL >= 5 || defined(TgS_UNIT_TEST__EXECUTION)
    if (TgFAILED(tgEX_Module_Boot()))
        goto FAIL_Test_Context__Boot;
#endif

    return (KTgS_OK);

FAIL_Test_Context__Boot:
#if TgS_RING_LEVEL >= 5
    tgSE_Module_Stop();
#endif
#if TgS_RING_LEVEL >= 4
    tgOB_Module_Stop();
    tgFX_Module_Stop();
    tgSN_Module_Stop();
#endif
#if TgS_RING_LEVEL >= 3
    tgRN_Module_Stop();
    tgPH_Module_Stop();
    tgIN_Module_Stop();
    tgAM_Module_Stop();
    tgKN_Module_Stop();
#endif
#if TgS_RING_LEVEL >= 2
    tgCO_Module_Stop();
#endif
    tgGB_Stop();
    return (KTgE_FAIL);
}


TgRESULT Test_Context__Stop( TgVOID )
{
#if TgS_RING_LEVEL >= 5 || defined(TgS_UNIT_TEST__EXECUTION)
    tgEX_Module_Stop();
#endif
#if TgS_RING_LEVEL >= 5 || defined(TgS_UNIT_TEST__SET)
    tgSE_Module_Stop();
#endif
#if TgS_RING_LEVEL >= 4 || defined(TgS_UNIT_TEST__OBJECT)
    tgOB_Module_Stop();
#endif
#if TgS_RING_LEVEL >= 4 || defined(TgS_UNIT_TEST__EFFECT)
    tgFX_Module_Stop();
#endif
#if TgS_RING_LEVEL >= 4 || defined(TgS_UNIT_TEST__SOUND)
    tgSN_Module_Stop();
#endif
#if TgS_RING_LEVEL >= 3 || defined(TgS_UNIT_TEST__RENDER)
    tgRN_Module_Stop();
#endif
#if TgS_RING_LEVEL >= 3 || defined(TgS_UNIT_TEST__PHYSICS)
    tgPH_Module_Stop();
#endif
#if TgS_RING_LEVEL >= 3 || defined(TgS_UNIT_TEST__INPUT)
    tgIN_Module_Stop();
#endif
#if TgS_RING_LEVEL >= 3 || defined(TgS_UNIT_TEST__ANIMATION)
    tgAM_Module_Stop();
#endif
#if TgS_RING_LEVEL >= 2 || defined(TgS_UNIT_TEST__KERNEL)
#if defined(TgBUILD_FEATURE__GRAPHICS)
    tgKN_GPU_Module_Stop();
#endif
    tgKN_Module_Stop();
#endif
#if TgS_RING_LEVEL >= 0 || defined(TgS_UNIT_TEST__COLLISION)
    tgCO_Module_Stop();
#endif
    tgGB_Stop();
    return (KTgS_OK);
}


TgRESULT Test_Context__Free( TgVOID )
{
#if TgS_RING_LEVEL >= 5 || defined(TgS_UNIT_TEST__EXECUTION)
    tgEX_Module_Free();
#endif
#if TgS_RING_LEVEL >= 5 || defined(TgS_UNIT_TEST__SET)
    tgSE_Module_Free();
#endif
#if TgS_RING_LEVEL >= 4 || defined(TgS_UNIT_TEST__OBJECT)
    tgOB_Module_Free();
#endif
#if TgS_RING_LEVEL >= 4 || defined(TgS_UNIT_TEST__EFFECT)
    tgFX_Module_Free();
#endif
#if TgS_RING_LEVEL >= 4 || defined(TgS_UNIT_TEST__SOUND)
    tgSN_Module_Free();
#endif
#if TgS_RING_LEVEL >= 3 || defined(TgS_UNIT_TEST__RENDER)
    tgRN_Module_Free();
#endif
#if TgS_RING_LEVEL >= 3 || defined(TgS_UNIT_TEST__PHYSICS)
    tgPH_Module_Free();
#endif
#if TgS_RING_LEVEL >= 3 || defined(TgS_UNIT_TEST__INPUT)
    tgIN_Module_Free();
#endif
#if TgS_RING_LEVEL >= 3 || defined(TgS_UNIT_TEST__ANIMATION)
    tgAM_Module_Free();
#endif
#if TgS_RING_LEVEL >= 2 || defined(TgS_UNIT_TEST__KERNEL)
#if defined(TgBUILD_FEATURE__GRAPHICS)
    tgKN_GPU_Module_Free();
#endif
    tgKN_Module_Free();
#endif
#if TgS_RING_LEVEL >= 0 || defined(TgS_UNIT_TEST__PARTITION)
    tgPA_Module_Free();
#endif
#if TgS_RING_LEVEL >= 0 || defined(TgS_UNIT_TEST__COLLISION)
    tgCO_Module_Free();
#endif

#if TgCOMPILE__CONSOLE
    tgCN_Remove_Default_Break( KTgCN_CHANEL_ERROR );
    tgCN_Remove_Output( KTgCN_CHANEL_CONSOLE, &g_sStdOut );
    tgCN_Remove_Output( KTgCN_CHANEL_ERROR, &g_sErrOut );
    tgCN_Remove_Output( KTgCN_CHANEL_WARNING, &g_sStdOut );
    tgCN_Remove_Output( KTgCN_CHANEL_MESSAGE, &g_sStdOut );
    tgCN_Remove_Output( KTgCN_CHANEL_LOADING, &g_sStdOut );
    tgCN_Remove_Output( KTgCN_CHANEL_INITIALIZE, &g_sStdOut );
#endif

    tgGB_Free();
    return (KTgS_OK);
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Main Execution                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
#if !defined(TgBUILD_UNIVERSAL__UWP)
TgMAIN_FUNCTION
{
    Test_Context                        tgUnit_Test_Context;
    TgSINT_E64                          iTime_Start, iTime_End, iTime_Elapsed;
    TgFLOAT32                           fTime_Elapsed;
    
#if !defined(TgCOMPILE_PLATFORM__WINDOWS_CON) && defined(TgCOMPILE_PLATFORM__WIN)
    (void)hPrevInstance;
    (void)lpCmdLine;
    (void)nCmdShow;
/*# !defined(TgCOMPILE_PLATFORM__WINDOWS_CON) && defined(TgCOMPILE_PLATFORM__WIN) */
#endif

    atexit( Test_End_Process );

    TgMAIN_PLATFORM_GLOBAL_INIT;

#if defined(TgBUILD_OS__WINDOWS) && defined(_DEBUG )
    _CrtSetDbgFlag( _crtDbgFlag | _CRTDBG_ALLOC_MEM_DF | _CRTDBG_CHECK_ALWAYS_DF );
    _CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_DEBUG );
    _CrtMemCheckpoint( &s_sMemState0 );
/*# defined(TgBUILD_OS__WINDOWS) && defined(_DEBUG ) */
#endif

    iTime_Start = tgTM_Query_Counter_Tick();

    Unit_Test__Context_Init( &tgUnit_Test_Context );

    g_sErrOut.m_pfnWrite = tgUnit_Test__DBG_ERR_Write;
    g_sErrOut.m_pfnClose = nullptr;
    g_sStdOut.m_pfnWrite = tgCM_DBG_OUT_Write;
    g_sStdOut.m_pfnClose = nullptr;

    tgUnit_Test_Context.m_pfnInit = Test_Context__Init;
    tgUnit_Test_Context.m_pfnBoot = Test_Context__Boot;
    tgUnit_Test_Context.m_pfnStop = Test_Context__Stop;
    tgUnit_Test_Context.m_pfnFree = Test_Context__Free;

    tgCM_Unit_Test_Register();

    Unit_Test__Execute( &tgUnit_Test_Context );

    TgMAIN_PLATFORM_GLOBAL_FREE;

    iTime_End = tgTM_Query_Counter_Tick();
    iTime_Elapsed = iTime_End - iTime_Start;
    fTime_Elapsed = tgTM_Counter_Tick_To_MilliSeconds( iTime_Elapsed );

    return (0);
}
/*# !defined(TgBUILD_UNIVERSAL__UWP) */
#endif
