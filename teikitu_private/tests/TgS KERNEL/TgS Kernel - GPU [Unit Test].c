/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Kernel - GPU [Unit Test].c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#if defined(TgBUILD_OS__WINDOWS)
#include "TgS COMMON/TgS (WINDOWS) Common - Base - Include.h"
#include "TgS KERNEL/TgS (WINDOWS) Kernel.h"
/*# defined(TgBUILD_OS__WINDOWS) */
#endif

TgCLANG_WARN_DISABLE_PUSH(unused-variable)

/* ---- GPU - Unit Test ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if defined(TgBUILD_FEATURE__GRAPHICS)

TgEXTN TgVOID
tgUnit_Test__KN_GPU__Create_Resources(
    TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC, TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP, TgUINT_E32 uiNodeMask );

TgEXTN TgRESULT
tgUnit_Test__KN_GPU__Render(
    TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC, TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP, TgKN_GPU_CXT_WORK_ID_C tiCXT_WORK, TgRSIZE_C uiTest_Level );

TgEXTN TgRESULT
tgUnit_Test__KN_GPU__Release_Resources(
    TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC, TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP );

/*# defined(TgBUILD_FEATURE__GRAPHICS) */
#endif




/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** END TO END TEST for GPU Functions

    Up to nine screens are created, or in the case of full-screen or non-window hardware, the ability to rotate through nine different scenarios.
    This scenario validates the following:
        Enumeration and then Initialization of GPU hardware, memory management, resource management, and command buffers.
        Rendering in SDR, HDR, simple and more complex vertices, textures, shaders, constant buffers, 
        Validates multi GPU rendering with final pass over to output adapter (first step for alternate frame rendering).

    Test Grid:
                                    [COL] SDR 8bit (RGB FULL,G22,P709)          [COL] HDR 10bit (RGB_FULL,G2084,P2020)      [COL] HDR 16bit (RGB_FULL,G10,P709)
    Row GPU #1 Simple Rendering:    2D: SDR, HDR Gradients
    Row GPU #1 Complex Rendering    3D: Wireframe, Solid, Textured rotating cubes in a Cornell box
    Row GPU #2 Simple Rendering     2D: SDR, HDR Gradients

    This could be turned into a unit test by doing a frame capture of each scenario and comparing against an accepted ground truth image.
*/

TEST_METHOD( UNIT_TEST__TEST__KN_GPU_Render_Enumeration );
TEST_METHOD( UNIT_TEST__TEST__KN_GPU_Render_Init_Select );
TEST_METHOD( UNIT_TEST__TEST__KN_GPU_Render_Init_Windows );
TEST_METHOD( UNIT_TEST__TEST__KN_GPU_Render_Simple );
TEST_METHOD( UNIT_TEST__TEST__KN_GPU_Render_Free );
TEST_METHOD( UNIT_TEST__TEST__KN_GPU_Compute_Init );
TEST_METHOD( UNIT_TEST__TEST__KN_GPU_Compute );
TEST_METHOD( UNIT_TEST__TEST__KN_GPU_Compute_Free );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Data                                                                                                                                                                */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

static Test_Set                             s_sSET__KERNEL_GPU;
static Test_Case                            s_sCASE__Kernel_GPU_Render_Simple;
static Test_Case                            s_sCASE__Kernel_GPU_Compute;

#if defined(TgBUILD_FEATURE__GRAPHICS)
#if defined(TgBUILD_OS__WINDOWS)
static TgRSIZE                              s_nuiAppWindow = 0; /* Minimum of 1 */
static STg2_KN_OS_UNIT_TEST__UTIL__Window   s_shWnd[KTgKN_MAX_WINDOWS];
#else
static TgRSIZE_C                            s_nuiAppWindow = 1;
/*# defined(TgBUILD_OS__WINDOWS) */
#endif
static STg2_KN_GPU_Select                   s_sSelect;
/*# defined(TgBUILD_FEATURE__GRAPHICS) */
#endif

#if defined(TgBUILD_FEATURE__GRAPHICS)
static TgRESULT
UNIT_TEST__TEST__KN_GPU_Render_Simple_Job(
    STg2_Job_CPC psJob );

static TgUINT_E64                           s_uiFrame_Counter;
static TgUINT_E64_A                         s_xuiRender_Counter;
static TgFLOAT32                            s_fTotal_Elapse_Frame_Time;

static TgBOOL                               s_bTest_Context_CMD_Per_Window = true;
static TgBOOL                               s_bTest_Render_With_Jobs = true;

TgTYPE_STRUCT( UT_KN_GPU_Render_Simple_Job_Data, )
{
    TgKN_GPU_CXT_SWAP_ID                m_tiCXT_SWAP;
    TgKN_GPU_CXT_EXEC_ID                m_tiCXT_EXEC;
    TgKN_GPU_CXT_WORK_ID                m_tiCXT_WORK;
    TgUINT_E32                          m_uiNodeMask;
    TgUINT_E32                          m_uiWindow;
    TgUINT_E32                          m_uiLoopWait;
    TgFLOAT32                           m_fStart_Time;
};
TgCOMPILER_ASSERT( sizeof( UT_KN_GPU_Render_Simple_Job_Data ) <= KTgJOB_DATA_SIZE, 0 );
/*# defined(TgBUILD_FEATURE__GRAPHICS) */
#endif




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TgVOID tgCM_Unit_Test_Register_KERNEL_GPU( TgVOID )
{
    /* Initialize the unit test structures */

    Unit_Test__Set_Init( &s_sSET__KERNEL_GPU );
    Unit_Test__Case_Init( &s_sCASE__Kernel_GPU_Render_Simple );
    Unit_Test__Case_Init( &s_sCASE__Kernel_GPU_Compute );



    /* Configure the test set */

    s_sSET__KERNEL_GPU.m_szSet = u8"Kernel: GPU";



    /* Configure the test cases */

    s_sCASE__Kernel_GPU_Render_Simple.m_pszSet = s_sSET__KERNEL_GPU.m_szSet;
    s_sCASE__Kernel_GPU_Render_Simple.m_pszCase = u8"Render";
    s_sCASE__Kernel_GPU_Render_Simple.m_pfnTest[0] = UNIT_TEST__TEST__KN_GPU_Render_Enumeration;
    s_sCASE__Kernel_GPU_Render_Simple.m_apszTest[0] = u8"Enumeration";
    s_sCASE__Kernel_GPU_Render_Simple.m_pfnTest[1] = UNIT_TEST__TEST__KN_GPU_Render_Init_Windows;
    s_sCASE__Kernel_GPU_Render_Simple.m_apszTest[1] = u8"Init Windows";
    s_sCASE__Kernel_GPU_Render_Simple.m_pfnTest[2] = UNIT_TEST__TEST__KN_GPU_Render_Init_Select;
    s_sCASE__Kernel_GPU_Render_Simple.m_apszTest[2] = u8"Init Select";
    s_sCASE__Kernel_GPU_Render_Simple.m_pfnTest[3] = UNIT_TEST__TEST__KN_GPU_Render_Simple;
    s_sCASE__Kernel_GPU_Render_Simple.m_apszTest[3] = u8"Render";
    s_sCASE__Kernel_GPU_Render_Simple.m_pfnTest[4] = UNIT_TEST__TEST__KN_GPU_Render_Free;
    s_sCASE__Kernel_GPU_Render_Simple.m_apszTest[4] = u8"Free Resources and Context";

    s_sCASE__Kernel_GPU_Compute.m_pszSet = s_sSET__KERNEL_GPU.m_szSet;
    s_sCASE__Kernel_GPU_Compute.m_pszCase = u8"Compute";
    s_sCASE__Kernel_GPU_Compute.m_pfnTest[0] = UNIT_TEST__TEST__KN_GPU_Compute_Init;
    s_sCASE__Kernel_GPU_Compute.m_apszTest[0] = u8"Init";
    s_sCASE__Kernel_GPU_Compute.m_pfnTest[0] = UNIT_TEST__TEST__KN_GPU_Compute;
    s_sCASE__Kernel_GPU_Compute.m_apszTest[0] = u8"Compute";
    s_sCASE__Kernel_GPU_Compute.m_pfnTest[0] = UNIT_TEST__TEST__KN_GPU_Compute_Free;
    s_sCASE__Kernel_GPU_Compute.m_apszTest[0] = u8"Free";



    /* Register all of the test cases with the test set */
    Unit_Test__Set_Register_Case( &s_sSET__KERNEL_GPU, &s_sCASE__Kernel_GPU_Render_Simple );
    Unit_Test__Set_Register_Case( &s_sSET__KERNEL_GPU, &s_sCASE__Kernel_GPU_Compute );

    /* Register the test set with the unit test system */

    Unit_Test__Register( &s_sSET__KERNEL_GPU );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- UNIT_TEST__TEST__KN_GPU_Render_Enumeration ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__KN_GPU_Render_Enumeration )
{
#if defined(TgBUILD_FEATURE__GRAPHICS)

    STg2_KN_GPU_Adapter_CP              apAdapter[KTgKN_GPU_MAX_ADAPTER];

    /* Enumerate all the device and device instantiations (including software (WARP on DX12) adapters). */
    Test__Expect_EQ(KTgS_OK, tgKN_GPU_Enumerate());

    /* Unit Test validation that we pulled back at least one adapter, and the output list is legal (though potential empty). */
    Test__Expect_EQ(KTgS_OK, tgKN_GPU_Query_Adapter_List( apAdapter, KTgKN_GPU_MAX_ADAPTER ));
    Test__Expect_NE(nullptr, apAdapter[0]);

/*# defined(TgBUILD_FEATURE__GRAPHICS) */
#endif
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__KN_GPU_Render_Init__Windows ----------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__KN_GPU_Render_Init_Windows )
{
#if defined(TgBUILD_FEATURE__GRAPHICS) && defined(TgBUILD_OS__WINDOWS)
    Test__Expect_EQ( 9, s_nuiAppWindow = tgKN_OS_UNIT_TEST__UTIL__Init_Windows( s_shWnd, KTgKN_MAX_WINDOWS, false ) );
/*# defined(TgBUILD_FEATURE__GRAPHICS) && defined(TgBUILD_OS__WINDOWS) */
#endif

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__KN_GPU_Render_Init_Select ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__KN_GPU_Render_Init_Select )
{
#if defined(TgBUILD_FEATURE__GRAPHICS)

    /* Test the initialization of the select from Kernel configuration. */
    tgMM_Set_U08_0x00( &s_sSelect, sizeof( s_sSelect ) );
    tgKN_GPU_Select_Context__Init_From_Config( &s_sSelect );

    /* Init the selection structure using a unit test utility for the number of windows created. */
    tgMM_Set_U08_0x00( &s_sSelect, sizeof( s_sSelect ) );
    Test__Expect_EQ(KTgS_OK, tgKN_GPU_UNIT_TEST__UTIL__Init_Select( &s_sSelect, 1 == s_nuiAppWindow ));
    s_sSelect.m_sOutput[0].m_uiOutput_Config.m_bFullscreen = 1;
    Test__Expect_EQ( KTgS_OK, tgKN_GPU_Select_Context__Validate( &s_sSelect ) );
    s_sSelect.m_sOutput[0].m_uiOutput_Config.m_bFullscreen = 0;

    /* Initialize the selection limits. For non-windows platforms, we will assume that we are doing a 1:1:1. */
    s_sSelect.m_nuiAdapter = 1;
    s_sSelect.m_nuiNode = 2;
    s_sSelect.m_nuiOutput = 1;

#if defined(TgBUILD_OS__WINDOWS)
    {
        /* On Windows, pull back the window client size to use as the render target size. */

        TgRSIZE                             uiOutput;

        s_sSelect.m_nuiOutput = tgCM_MIN_UMAX(s_nuiAppWindow,s_sSelect.m_nuiOutput);
        for (uiOutput = 0; uiOutput < s_sSelect.m_nuiOutput; ++uiOutput)
        {
            STg2_KN_OS_Window_Configuration     sWin_Config;

            tgKN_OS_Query_Window_Configuration( &sWin_Config, (TgSINT_PTR)uiOutput );

            s_sSelect.m_sOutput[uiOutput].m_sMode.m_sBuffer.m_uiHeight = 0 == sWin_Config.m_uiRender_Target_H ? 480 : sWin_Config.m_uiRender_Target_H;
            s_sSelect.m_sOutput[uiOutput].m_sMode.m_sBuffer.m_uiWidth = 0 == sWin_Config.m_uiRender_Target_W ? 640: sWin_Config.m_uiRender_Target_W;
            s_sSelect.m_sOutput[uiOutput].m_uiOS_ID = s_shWnd[uiOutput].m_uiOS_ID;
        }
    }

/*# defined(TgBUILD_OS__WINDOWS) */
#endif

    Test__Expect_EQ( KTgS_OK, tgKN_GPU_Select_Context__Validate( &s_sSelect ) );

/*# defined(TgBUILD_FEATURE__GRAPHICS) */
#endif

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__KN_GPU_Render_Simple_Job -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if defined(TgBUILD_FEATURE__GRAPHICS)
static TgRESULT UNIT_TEST__TEST__KN_GPU_Render_Simple_Job( STg2_Job_CPC psJob )
{
    union { TgUINT_E08_CP pui; UT_KN_GPU_Render_Simple_Job_Data_CP ps; } const uJob_Data = { .pui = psJob->m_auiData };

    TgOSCHAR                            szBuffer[256];
    TgFLOAT32                           fFrame_Start_Time;

    fFrame_Start_Time = tgTM_Query_Time();
    if (3 == uJob_Data.ps->m_uiWindow || 4 == uJob_Data.ps->m_uiWindow || 5 == uJob_Data.ps->m_uiWindow)
    {
        tgUnit_Test__KN_GPU__Render( uJob_Data.ps->m_tiCXT_EXEC, uJob_Data.ps->m_tiCXT_SWAP, uJob_Data.ps->m_tiCXT_WORK, 5 );
    }
    else if (0 == uJob_Data.ps->m_uiWindow || 1 == uJob_Data.ps->m_uiWindow|| 2 == uJob_Data.ps->m_uiWindow)
    {
        tgUnit_Test__KN_GPU__Render( uJob_Data.ps->m_tiCXT_EXEC, uJob_Data.ps->m_tiCXT_SWAP, uJob_Data.ps->m_tiCXT_WORK, 3 );
    }
    else if (6 == uJob_Data.ps->m_uiWindow || 7 == uJob_Data.ps->m_uiWindow || 8 == uJob_Data.ps->m_uiWindow)
    {
        tgUnit_Test__KN_GPU__Render( uJob_Data.ps->m_tiCXT_EXEC, uJob_Data.ps->m_tiCXT_SWAP, uJob_Data.ps->m_tiCXT_WORK, 4 );
    }
    else
    {
        tgUnit_Test__KN_GPU__Render( uJob_Data.ps->m_tiCXT_EXEC, uJob_Data.ps->m_tiCXT_SWAP, uJob_Data.ps->m_tiCXT_WORK, 2 );
    }

#if defined(TgBUILD_OS__WINDOWS)
    /* Add the frame time to the windows title. */
    s_shWnd[uJob_Data.ps->m_uiWindow].m_fFrame_Elapsed_Time = tgTM_Query_Time() - fFrame_Start_Time;
    TgOS_TEXT_FCN(PrintF)( szBuffer, 256, TgOS_TEXT(" Frame Time: % 2.2fms"), (double)s_shWnd[uJob_Data.ps->m_uiWindow].m_fFrame_Elapsed_Time );
    tgKN_OS_Set_Window_Title(s_shWnd[uJob_Data.ps->m_uiWindow].m_iWnd, szBuffer, 256 );
/*# defined(TgBUILD_OS__WINDOWS) */
#endif

    TgSTD_ATOMIC(fetch_add)( &s_xuiRender_Counter, 1 );
    return (KTgS_OK);
}
/*# defined(TgBUILD_FEATURE__GRAPHICS) */
#endif


/* ---- UNIT_TEST__TEST__KN_GPU_Render_Simple ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__KN_GPU_Render_Simple )
{
#if defined(TgBUILD_FEATURE__GRAPHICS)
    STg2_KN_GPU_Init_Result             sGPU_Init_Result;
    STg2_Job                            asJob[KTgKN_GPU_MAX_SWAP_CONTEXT];
    union {
        TgUINT_E08_P                        pui;
        UT_KN_GPU_Render_Simple_Job_Data_P  ps;
    }                                   uJob_Data[KTgKN_GPU_MAX_SWAP_CONTEXT];
    TgRSIZE                             uiWindow;
    TgRSIZE                             uiSwap, nuiSwap, uiFrame_Counter_Start;
    TgBOOL                              bAll_Windows_Closed;
    TgFLOAT32                           afFrame_Elapsed_Time[31];
    TgRSIZE                             nuiFrame_Elapsed_Time = 0;

    TgSTD_ATOMIC(store)( &s_xuiRender_Counter, 0 );
    tgMM_Set_U08_0x00( &sGPU_Init_Result, sizeof( sGPU_Init_Result ) );
    Test__Expect_EQ( KTgS_OK, tgKN_GPU_Contexts__Init( &sGPU_Init_Result, &s_sSelect ) );

    /* Initialize the job data, and the render resources for to be used by the render job. */

    tgMM_Set_U08_0x00( &asJob, sizeof( asJob ) );
    for (uiSwap = 0; uiSwap < sGPU_Init_Result.m_nuiSWAP; ++uiSwap)
    {
        uJob_Data[uiSwap].pui = asJob[uiSwap].m_auiData;

        uJob_Data[uiSwap].ps->m_tiCXT_SWAP = sGPU_Init_Result.m_sSWAP[uiSwap].m_tiCXT_SWAP;
        uJob_Data[uiSwap].ps->m_tiCXT_EXEC = sGPU_Init_Result.m_sSWAP[uiSwap].m_tiCXT_EXEC;
        uJob_Data[uiSwap].ps->m_tiCXT_WORK.m_uiKI = KTgKN_GPU_CXT_WORK_ID__INVALID.m_uiKI;
        uJob_Data[uiSwap].ps->m_uiNodeMask = sGPU_Init_Result.m_sSWAP[uiSwap].m_uiNodeMask;
        uJob_Data[uiSwap].ps->m_fStart_Time= tgTM_Query_Time();
        uJob_Data[uiSwap].ps->m_uiLoopWait = KTgMAX_U32;
        uJob_Data[uiSwap].ps->m_uiWindow = KTgMAX_U32;

        asJob[uiSwap].m_pfnExecute = UNIT_TEST__TEST__KN_GPU_Render_Simple_Job;

        Test__Expect_NE(ETgKN_GPU_EXT_FORMAT__MAX, s_sSelect.m_sOutput[uiSwap].m_sMode.m_sBuffer.m_enFormat);
        tgUnit_Test__KN_GPU__Create_Resources( uJob_Data[uiSwap].ps->m_tiCXT_EXEC, uJob_Data[uiSwap].ps->m_tiCXT_SWAP, uJob_Data[uiSwap].ps->m_uiNodeMask );
    };

    /* Map the windows to output contexts based on the results. i.e. We selected which output context that we expected for each window in the select data structure, however, the
       context may have failed to be created. Thus, now we map the window to the completed output contexts. */

#if defined(TgBUILD_OS__WINDOWS)
    for (uiWindow = 0; uiWindow < s_nuiAppWindow; ++uiWindow)
    {
        for (uiSwap = 0; uiSwap < sGPU_Init_Result.m_nuiSWAP; ++uiSwap)
        {
            if (s_shWnd[uiWindow].m_uiOS_ID == sGPU_Init_Result.m_sSWAP[uiSwap].m_uiOS_ID)
            {
                s_shWnd[uiWindow].m_iOutput = (TgSINT_E32)uiSwap;
                uJob_Data[uiSwap].ps->m_uiWindow = (TgUINT_E32)uiWindow;
                break;
            }
        };
    };
/*# defined(TgBUILD_OS__WINDOWS) */
#endif

    bAll_Windows_Closed = false;
    for (s_uiFrame_Counter = 0; !bAll_Windows_Closed; ++s_uiFrame_Counter)
    {
        TgFLOAT32                           fFrame_Start_Time;
        TgKN_GPU_CXT_EXEC_ID                tiCXT_EXEC;
        TgKN_GPU_CXT_WORK_ID                tiCXT_WORK;
        TgKN_GPU_CXT_WORK_ID                atiCXT_WORK[KTgKN_GPU_MAX_SWAP_CONTEXT];
        TgRSIZE                             nuiCXT_WORK;

        tiCXT_EXEC.m_uiKI = 0;
        tiCXT_WORK.m_uiKI = 0;
        tgMM_Set_U08_0x00( atiCXT_WORK, sizeof(atiCXT_WORK) );
        nuiCXT_WORK = 0;

        /* Render based on all of the swap chain contexts. */
        fFrame_Start_Time = tgTM_Query_Time();

        /* Check to see if all the windows have been closed, to quit the application.
           Render the swap chains associated with any active window. */
        bAll_Windows_Closed = true;
        nuiSwap = 0;
        uiFrame_Counter_Start = TgSTD_ATOMIC(load)( &s_xuiRender_Counter );
        for (uiWindow = 0; uiWindow < s_nuiAppWindow; ++uiWindow)
        {
        #if defined(TgBUILD_OS__WINDOWS)
            if (ETgTHREAD_STATUS__INVALID == tgKN_OS_Query_Window_Thread_Status( s_shWnd[uiWindow].m_iWnd ))
                continue;
            bAll_Windows_Closed = false;
            uiSwap = (TgRSIZE)s_shWnd[uiWindow].m_iOutput;
        /*# defined(TgBUILD_OS__WINDOWS) */
        #endif

            ++nuiSwap;
            if (!s_bTest_Context_CMD_Per_Window)
            {
                uJob_Data[uiSwap].pui = asJob[uiSwap].m_auiData;

                if (tiCXT_EXEC.m_uiKI != uJob_Data[uiSwap].ps->m_tiCXT_EXEC.m_uiKI)
                {
                    tiCXT_EXEC.m_uiKI = uJob_Data[uiSwap].ps->m_tiCXT_EXEC.m_uiKI;
                    atiCXT_WORK[nuiCXT_WORK] = tgKN_GPU_EXT__Execute__Frame_Start( uJob_Data[uiSwap].ps->m_tiCXT_EXEC );
                    tiCXT_WORK = atiCXT_WORK[nuiCXT_WORK];
                    ++nuiCXT_WORK;
                }
                uJob_Data[uiSwap].ps->m_tiCXT_WORK = tiCXT_WORK;
            }

            if (s_bTest_Render_With_Jobs)
            {
                tgJM_Queue_Job( g_sJob_Queue__Render_Normal, asJob + uiSwap );
            }
            else
            {
                UNIT_TEST__TEST__KN_GPU_Render_Simple_Job( asJob + uiSwap );
            }
        }

        /* Wait for all of the jobs to finish, this will essentially be a no-op for the single-threaded mode. */
        while( uiFrame_Counter_Start + nuiSwap != TgSTD_ATOMIC(load)( &s_xuiRender_Counter ))
        {
            tgTR_Yield();
        };

        /* Close the frame, if we are using the single context test method. */
        for (uiSwap = 0; uiSwap < KTgKN_GPU_MAX_SWAP_CONTEXT; ++uiSwap)
        {
            if (atiCXT_WORK[uiSwap].m_uiKI != 0)
            {
                tgKN_GPU_EXT__Execute__Frame_End( atiCXT_WORK[uiSwap] );
                atiCXT_WORK[uiSwap].m_uiKI = 0;
            }
        }

        /* Finish measuring the time used for this frame (all windows / swap chains). */
        afFrame_Elapsed_Time[nuiFrame_Elapsed_Time % 31] = tgTM_Query_Time() - fFrame_Start_Time;
        tgCN_Update( afFrame_Elapsed_Time[nuiFrame_Elapsed_Time % 31] / 1000.0F );
        ++nuiFrame_Elapsed_Time;

        /* Calculate a smoothed total frame time. */
        s_fTotal_Elapse_Frame_Time = 0.0F;
        for (uiWindow = 0; uiWindow < 31; ++uiWindow)
        {
            s_fTotal_Elapse_Frame_Time += afFrame_Elapsed_Time[uiWindow];
        }
        s_fTotal_Elapse_Frame_Time /= 31.0F;
 
        //tgTR_Sleep( 150000 );
    };


    for (uiSwap = 0; uiSwap < s_sSelect.m_nuiOutput; ++uiSwap)
    {
        Test__Expect_EQ( KTgS_OK, tgUnit_Test__KN_GPU__Release_Resources( uJob_Data[uiSwap].ps->m_tiCXT_EXEC, uJob_Data[uiSwap].ps->m_tiCXT_SWAP ));
    };

    tgKN_GPU_Contexts__Free();

/*# defined(TgBUILD_FEATURE__GRAPHICS) */
#endif
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__KN_GPU_Render_Free -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__KN_GPU_Render_Free )
{
#if defined(TgBUILD_FEATURE__GRAPHICS)
/*# defined(TgBUILD_FEATURE__GRAPHICS) */
#endif
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__KN_GPU_Compute_Init ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__KN_GPU_Compute_Init )
{
#if defined(TgBUILD_FEATURE__GRAPHICS)
/*# defined(TgBUILD_FEATURE__GRAPHICS) */
#endif
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__KN_GPU_Compute ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__KN_GPU_Compute )
{
#if defined(TgBUILD_FEATURE__GRAPHICS)
/*# defined(TgBUILD_FEATURE__GRAPHICS) */
#endif
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__KN_GPU_Compute_Free ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__KN_GPU_Compute_Free )
{
#if defined(TgBUILD_FEATURE__GRAPHICS)
/*# defined(TgBUILD_FEATURE__GRAPHICS) */
#endif
    TEST_END_METHOD( KTgS_OK );
}


TgCLANG_WARN_DISABLE_POP(unused-variable)
