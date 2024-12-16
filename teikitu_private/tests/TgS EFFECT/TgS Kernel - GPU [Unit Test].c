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
TEST_METHOD( UNIT_TEST__TEST__KN_GPU_Render_Init_Select_Windows );
TEST_METHOD( UNIT_TEST__TEST__KN_GPU_Render_Simple );
TEST_METHOD( UNIT_TEST__TEST__KN_GPU_Render_Free );
TEST_METHOD( UNIT_TEST__TEST__KN_GPU_Compute_Init );
TEST_METHOD( UNIT_TEST__TEST__KN_GPU_Compute );
TEST_METHOD( UNIT_TEST__TEST__KN_GPU_Compute_Free );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Data                                                                                                                                                                */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

static Test_Set                             s_sSET__EFFECT;
static Test_Case                            s_sCASE__Kernel_GPU_Render_Simple;
static Test_Case                            s_sCASE__Kernel_GPU_Compute;

#if defined(TgBUILD_OS__WINDOWS)
#define KTgMACRO_MAX_TOTAL_WINDOWS          9
static TgRSIZE_C                            s_nuiLimit_Windows = 9; /* Minimum of 1 */
static struct
{
    TgFLOAT32                           m_fFrame_Elapsed_Time;
    TgSINT_E32                          m_iWnd;
    TgSINT_E32                          m_iOutput;
    TgSINT_E32                          m_iPad;
    union
    {
        HWND                                m_hWnd;
        TgUINT_PTR                          m_uiOS_ID;
    };
}                                           s_shWnd[KTgMACRO_MAX_TOTAL_WINDOWS];

#if defined(TgBUILD_FEATURE__GRAPHICS)
static TgSINT_E64 __stdcall
tgUT_KN_GPU_Base_Window_Update(
    HWND hWnd, TgUINT_E32 uMessage, TgUINT_E64 wParam, TgSINT_E64 lParam );
/*# defined(TgBUILD_FEATURE__GRAPHICS) */
#endif
/*# defined(TgBUILD_OS__WINDOWS) */
#endif

#if defined(TgBUILD_FEATURE__GRAPHICS)
static TgRESULT
UNIT_TEST__TEST__KN_GPU_Render_Simple_Job(
    STg2_Job_PC psJob );

static ETgKN_GPU_EXT_FORMAT                 s_aenTarget[3] = { ETgKN_GPU_EXT_FORMAT_R8G8B8A8_UNORM, ETgKN_GPU_EXT_FORMAT_R10G10B10A2_UNORM, ETgKN_GPU_EXT_FORMAT_R16G16B16A16_FLOAT };
static STg2_KN_GPU_Select                   s_sSelect;
static TgUINT_E64                           s_uiFrame_Counter;
static TgUINT_E64_A                         s_xuiRender_Counter;
static TgFLOAT32                            s_fTotal_Elapse_Frame_Time;

static TgBOOL                               s_bTest_Context_CMD_Per_Window = false;
static TgBOOL                               s_bTest_Render_With_Jobs = true;

TgTYPE_STRUCT(UT_KN_GPU_Render_Simple_Job_Data)
{
    TgKN_GPU_CXT_SWAP_ID                m_tiCXT_SWAP;
    TgKN_GPU_CXT_EXEC_ID                m_tiCXT_EXEC;
    TgKN_GPU_CXT_WORK_ID                m_tiCXT_WORK;
    TgUINT_E32                          m_uiNodeMask;
    TgUINT_E32                          m_uiWindow;
    TgUINT_E32                          m_uiLoopWait;
    TgUINT_E32                          m_uiPad;
    TgFLOAT32                           m_fStart_Time;
    TgFLOAT32                           m_fElapsed_Time;
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
    s_sCASE__Kernel_GPU_Render_Simple.m_pfnTest[3] = UNIT_TEST__TEST__KN_GPU_Render_Init_Select_Windows;
    s_sCASE__Kernel_GPU_Render_Simple.m_apszTest[3] = u8"Init Select Windows";
    s_sCASE__Kernel_GPU_Render_Simple.m_pfnTest[4] = UNIT_TEST__TEST__KN_GPU_Render_Simple;
    s_sCASE__Kernel_GPU_Render_Simple.m_apszTest[4] = u8"Render";
    s_sCASE__Kernel_GPU_Render_Simple.m_pfnTest[5] = UNIT_TEST__TEST__KN_GPU_Render_Free;
    s_sCASE__Kernel_GPU_Render_Simple.m_apszTest[5] = u8"Free Resources and Context";

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


/* ---- UNIT_TEST__TEST__KN_GPU_Render_Init__Windows ----------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__KN_GPU_Render_Init_Windows )
{
#if defined(TgBUILD_FEATURE__GRAPHICS) && defined(TgBUILD_OS__WINDOWS)

    STg2_KN_OS_Window_Configuration     sWin_Config;
    TgOSCHAR                            szBuffer[256];

    tgMM_Set_U08_0x00( &sWin_Config, sizeof(sWin_Config) );
    sWin_Config.m_pfnWndProc = tgUT_KN_GPU_Base_Window_Update;
    sWin_Config.m_bCenterOnMonitor = 1;
    sWin_Config.m_bIncludeDefaultInTitle = true;
    sWin_Config.m_bIncludeDimensionsInTitle = true;

    TgOS_TEXT_FCN(PrintF)( szBuffer, 256, TgOS_TEXT(" No Swap Chain, No Update") );

    Test__Expect_EQ(true, (s_shWnd[0].m_iWnd = tgKN_OS_Create_Window( &sWin_Config )) == 0);
    s_shWnd[0].m_hWnd = tgKN_OS_Query_Window_Handle( s_shWnd[0].m_iWnd );
    s_shWnd[0].m_iOutput = -1;
    tgKN_OS_Set_Window_Title(s_shWnd[0].m_iWnd, true, true, szBuffer, 256 );

    tgKN_OS_Query_Window_Configuration( &sWin_Config, 0 );
    sWin_Config.m_szDefault_Title[0] = sWin_Config.m_szTitle[0] = sWin_Config.m_szClass_Name[0] = 0;
    sWin_Config.m_bCenterOnMonitor = 0;

    {
        TgSINT_E32_C                        iWindow_X0 = sWin_Config.m_iWindow_X0 - (TgSINT_E32)sWin_Config.m_uiRender_Target_W - tgKN_Query_Window_PadX() - 25;
        TgSINT_E32_C                        iWindow_Y0 = sWin_Config.m_iWindow_Y0 - (TgSINT_E32)sWin_Config.m_uiRender_Target_H - tgKN_Query_Window_PadY() - 25;
        TgRSIZE                             uiIndex, nuiWnd;
            
        for (uiIndex = 0, nuiWnd = 1; nuiWnd < tgCM_MIN_UMAX(s_nuiLimit_Windows,KTgMACRO_MAX_TOTAL_WINDOWS); ++uiIndex)
        {
            if (4 == uiIndex)
                continue;

            sWin_Config.m_iWindow_X0 = iWindow_X0 + ((TgSINT_E32)uiIndex % 3)*((TgSINT_E32)sWin_Config.m_uiRender_Target_W + tgKN_Query_Window_PadX() + 25);
            sWin_Config.m_iWindow_Y0 = iWindow_Y0 + ((TgSINT_E32)uiIndex / 3)*((TgSINT_E32)sWin_Config.m_uiRender_Target_H + tgKN_Query_Window_PadY() + 25);
            Test__Expect_EQ(true, (s_shWnd[nuiWnd].m_iWnd = tgKN_OS_Create_Window( &sWin_Config )) > 0);
            s_shWnd[nuiWnd].m_hWnd = tgKN_OS_Query_Window_Handle( s_shWnd[nuiWnd].m_iWnd );
            s_shWnd[nuiWnd].m_iOutput = -1;
            tgKN_OS_Set_Window_Title(s_shWnd[nuiWnd].m_iWnd, true, true, szBuffer, 256 );

            ++nuiWnd;
        }
    }

/*# defined(TgBUILD_FEATURE__GRAPHICS) && defined(TgBUILD_OS__WINDOWS) */
#endif
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__KN_GPU_Render_Init_Select ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__KN_GPU_Render_Init_Select )
{
#if defined(TgBUILD_FEATURE__GRAPHICS)

    STg2_KN_GPU_Adapter_CP              apAdapter[KTgKN_GPU_MAX_ADAPTER];
    TgSINT_E32_C                        iSelect_Adapter = 2;
    STg2_KN_OS_Window_Configuration     sWin_Config;
    ETgKN_GPU_EXT_FORMAT                enFormat;
    TgRSIZE                             iIndex;

    /* Unit Test validation that we pulled back at least one adapter, and the output list is legal (though potential empty). */
    Test__Expect_EQ(KTgS_OK, tgKN_GPU_Query_Adapter_List( apAdapter, KTgKN_GPU_MAX_ADAPTER ));
    Test__Expect_NE(nullptr, apAdapter[0]);

    /* Test the initialization of the select from Kernel configuration.*/
    tgMM_Set_U08_0x00( &s_sSelect, sizeof( s_sSelect ) );
    tgKN_GPU_Select_Context__Init_From_Config( &s_sSelect );
    tgMM_Set_U08_0x00( &s_sSelect, sizeof( s_sSelect ) );

    /* Initialize the selection limits. For non-windows platforms, we will assume that we are doing a 1:1:1. */
    s_sSelect.m_nuiAdapter = 1;
    s_sSelect.m_nuiNode = 2;
    s_sSelect.m_nuiOutput = 1;

    /* Create GPU 0 w/ Node 0 */
    s_sSelect.m_uiEnumeration_Adapter_Index[0] = iSelect_Adapter;

    s_sSelect.m_sNode[0].m_uiAdapter_Index = 0;
    s_sSelect.m_sNode[0].m_uiAdapter_Node_Mask = 1;
    s_sSelect.m_sNode[0].m_nuiRender_Target_Max = 16;
    s_sSelect.m_sNode[0].m_nuiDepth_Stencil_Max = 16;
    s_sSelect.m_sNode[0].m_nuiData_Buffers_Max = 32;

    /* Swap chain on GPU 0::Node 0, primary window. */
    s_sSelect.m_sOutput[0].m_fMin_Mastering_Nits = 0.1000F;
    s_sSelect.m_sOutput[0].m_fMax_Mastering_Nits = 1000.0F;
    s_sSelect.m_sOutput[0].m_fMax_Content_Light_Level = 2000.0F;
    s_sSelect.m_sOutput[0].m_fMax_Frame_Average_Light_Level = 500.0F;
    s_sSelect.m_sOutput[0].m_uiNode_Index = 0;
    s_sSelect.m_sOutput[0].m_uiMSAA_Sample = 1;
    s_sSelect.m_sOutput[0].m_enFormat_DS = ETgKN_GPU_EXT_FORMAT_D32_FLOAT;
    s_sSelect.m_sOutput[0].m_uiOutput_Config.m_nuiSwap_Buffers = 2;
    s_sSelect.m_sOutput[0].m_uiOutput_Config.m_uiStereo = 0;
    s_sSelect.m_sOutput[0].m_uiOutput_Config.m_uiVSync = 0;
    s_sSelect.m_sOutput[0].m_uiOutput_Config.m_bHDR_Request = 1;
    s_sSelect.m_sOutput[0].m_uiOutput_Config.m_bFullscreen = 1 == s_nuiLimit_Windows ? 1 : 0;
    s_sSelect.m_sOutput[0].m_uiOS_ID = 0;

    /* Determine the allowable render target format and mode for the swap chain (scan out in full-screen). */

    enFormat = ETgKN_GPU_EXT_FORMAT__MAX;

    for (iIndex = 0; iIndex < TgARRAY_COUNT(s_aenTarget); ++iIndex)
    {
        if (!tgKN_GPU_Test_Output_ScanOut_Format_Support( iSelect_Adapter, s_aenTarget[iIndex] ))
        {
            s_aenTarget[iIndex] = ETgKN_GPU_EXT_FORMAT__MAX;
        }
    }

    if (ETgKN_GPU_EXT_FORMAT__MAX != s_aenTarget[1]) {
        enFormat = s_aenTarget[1];
    }
    else if (ETgKN_GPU_EXT_FORMAT__MAX != s_aenTarget[0]) {
        enFormat = s_aenTarget[0];
    }
    else {
        enFormat = s_aenTarget[2];
    }
    Test__Expect_NE( ETgKN_GPU_EXT_FORMAT__MAX, enFormat );

    tgKN_OS_Query_Window_Configuration( &sWin_Config, 0 );

    s_sSelect.m_sOutput[0].m_sMode.m_sBuffer.m_enFormat = enFormat;
    s_sSelect.m_sOutput[0].m_sMode.m_sBuffer.m_uiHeight = 0 == sWin_Config.m_uiRender_Target_H ? 480 : sWin_Config.m_uiRender_Target_H;
    s_sSelect.m_sOutput[0].m_sMode.m_sBuffer.m_uiWidth = 0 == sWin_Config.m_uiRender_Target_W ? 640: sWin_Config.m_uiRender_Target_W;
    s_sSelect.m_sOutput[0].m_sMode.m_uiRefresh_Rate__Denominator = 1;
    s_sSelect.m_sOutput[0].m_sMode.m_uiRefresh_Rate__Numerator = 60;

/*# defined(TgBUILD_FEATURE__GRAPHICS) */
#endif
    TEST_END_METHOD( KTgS_OK );
}



/* ---- UNIT_TEST__TEST__KN_GPU_Render_Init_Select_Windows ----------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__KN_GPU_Render_Init_Select_Windows )
{
#if defined(TgBUILD_FEATURE__GRAPHICS) && defined(TgBUILD_OS__WINDOWS)

    STg2_KN_GPU_Adapter_CP              apAdapter[KTgKN_GPU_MAX_ADAPTER];
    TgRSIZE                             uiAdapter;
    TgRSIZE                             uiNode,uiNodeIndex;
    TgRSIZE                             uiOutput;

    /* Unit Test validation that we pulled back at least one adapter, and the output list is legal (though potential empty). */
    Test__Expect_EQ(KTgS_OK, tgKN_GPU_Query_Adapter_List( apAdapter, KTgKN_GPU_MAX_ADAPTER ));
    Test__Expect_NE(nullptr, apAdapter[0]);

    /* Count up all of the GPU nodes that were enumerated. */
    for (s_sSelect.m_nuiAdapter = 0, s_sSelect.m_nuiNode = 0; 0 != apAdapter[s_sSelect.m_nuiAdapter]; ++s_sSelect.m_nuiAdapter)
    {
        if (s_sSelect.m_nuiAdapter >= KTgKN_GPU_MAX_DEVC_CONTEXT)
            break;
        if (s_sSelect.m_nuiNode >= KTgKN_GPU_MAX_EXEC_CONTEXT)
            break;
        if (s_sSelect.m_nuiNode + apAdapter[s_sSelect.m_nuiAdapter]->m_nuiNode > KTgKN_GPU_MAX_EXEC_CONTEXT)
        {
            s_sSelect.m_nuiNode = KTgKN_GPU_MAX_EXEC_CONTEXT;
        }
        else
        {
            s_sSelect.m_nuiNode += apAdapter[s_sSelect.m_nuiAdapter]->m_nuiNode;
        }
    }

    /* Initialize all of the nodes that were enumerated. */
    for (uiAdapter = 0, uiNode = 0; uiAdapter < s_sSelect.m_nuiAdapter; ++uiAdapter)
    {
        s_sSelect.m_uiEnumeration_Adapter_Index[uiAdapter] = uiAdapter;
        for (uiNodeIndex = 0; uiNodeIndex < apAdapter[uiAdapter]->m_nuiNode; ++uiNodeIndex, ++uiNode)
        {
            s_sSelect.m_sNode[uiNode].m_uiAdapter_Index = uiAdapter;
            s_sSelect.m_sNode[uiNode].m_uiAdapter_Node_Mask = 1u << uiNodeIndex;
            s_sSelect.m_sNode[uiNode].m_nuiRender_Target_Max = 16;
            s_sSelect.m_sNode[uiNode].m_nuiDepth_Stencil_Max = 16;
            s_sSelect.m_sNode[uiNode].m_nuiData_Buffers_Max = 32;
        }
    }

    /* Create a swap-chain per window (i.e. not associated with an output device) based on the original window. */
    s_sSelect.m_sOutput[0].m_uiOS_ID = s_shWnd[0].m_uiOS_ID;
    for (uiOutput = 0; s_sSelect.m_nuiOutput < tgCM_MIN_UMAX(s_nuiLimit_Windows,KTgMACRO_MAX_TOTAL_WINDOWS); ++uiOutput)
    {
        ETgKN_GPU_EXT_FORMAT_C              enFormat = *(s_aenTarget + tgCM_MIN_UMAX( uiOutput % 3, TgARRAY_COUNT( s_aenTarget ) ));

        if (ETgKN_GPU_EXT_FORMAT__MAX == enFormat || 4 == uiOutput)
            continue;

        tgMM_Copy( s_sSelect.m_sOutput + s_sSelect.m_nuiOutput, sizeof(s_sSelect.m_sOutput[0]), s_sSelect.m_sOutput, sizeof(s_sSelect.m_sOutput[0]) );
        s_sSelect.m_sOutput[s_sSelect.m_nuiOutput].m_sMode.m_sBuffer.m_enFormat = enFormat;
        s_sSelect.m_sOutput[s_sSelect.m_nuiOutput].m_uiNode_Index = (uiOutput >=6 ? 1 : 0) % s_sSelect.m_nuiNode;
        s_sSelect.m_sOutput[s_sSelect.m_nuiOutput].m_uiOutput_Config.m_bHDR_Request = 0 == (uiOutput % 3) ? 0u : 1u;
        s_sSelect.m_sOutput[s_sSelect.m_nuiOutput].m_uiOS_ID = s_shWnd[uiOutput > 4 ? uiOutput : uiOutput + 1].m_uiOS_ID;
        ++s_sSelect.m_nuiOutput;
    }

    Test__Expect_EQ( KTgS_OK, tgKN_GPU_Select_Context__Validate( &s_sSelect ) );

/*# defined(TgBUILD_FEATURE__GRAPHICS) && defined(TgBUILD_OS__WINDOWS) */
#endif
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__KN_GPU_Render_Simple_Job -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if defined(TgBUILD_FEATURE__GRAPHICS)
static TgRESULT UNIT_TEST__TEST__KN_GPU_Render_Simple_Job( STg2_Job_PC psJob )
{
    union { TgUINT_E08_P pui; UT_KN_GPU_Render_Simple_Job_Data_P ps; } const uJob_Data = { .pui = psJob->m_auiData };

    TgOSCHAR                            szBuffer[256];
    TgFLOAT32                           fFrame_Start_Time;

    uJob_Data.ps->m_fElapsed_Time = tgTM_Query_Time() - uJob_Data.ps->m_fStart_Time;

    fFrame_Start_Time = tgTM_Query_Time();
    if (0 == uJob_Data.ps->m_uiWindow || 4 == uJob_Data.ps->m_uiWindow || 5 == uJob_Data.ps->m_uiWindow)
    {
        tgUnit_Test__KN_GPU__Render( uJob_Data.ps->m_tiCXT_EXEC, uJob_Data.ps->m_tiCXT_SWAP, uJob_Data.ps->m_tiCXT_WORK, 5 );
    }
    else if (1 == uJob_Data.ps->m_uiWindow || 8 == uJob_Data.ps->m_uiWindow)
    {
        tgUnit_Test__KN_GPU__Render( uJob_Data.ps->m_tiCXT_EXEC, uJob_Data.ps->m_tiCXT_SWAP, uJob_Data.ps->m_tiCXT_WORK, 3 );
    }
    else if (3 == uJob_Data.ps->m_uiWindow || 6 == uJob_Data.ps->m_uiWindow)
    {
        tgUnit_Test__KN_GPU__Render( uJob_Data.ps->m_tiCXT_EXEC, uJob_Data.ps->m_tiCXT_SWAP, uJob_Data.ps->m_tiCXT_WORK, 4 );
    }
    else
    {
        tgUnit_Test__KN_GPU__Render( uJob_Data.ps->m_tiCXT_EXEC, uJob_Data.ps->m_tiCXT_SWAP, uJob_Data.ps->m_tiCXT_WORK, 2 );
    }
    s_shWnd[uJob_Data.ps->m_uiWindow].m_fFrame_Elapsed_Time = tgTM_Query_Time() - fFrame_Start_Time;

    /* Add the frame time to the windows title. */
    TgOS_TEXT_FCN(PrintF)( szBuffer, 256, TgOS_TEXT(" Frame Time: % 2.2fms"), s_shWnd[uJob_Data.ps->m_uiWindow].m_fFrame_Elapsed_Time );
    tgKN_OS_Set_Window_Title(s_shWnd[uJob_Data.ps->m_uiWindow].m_iWnd, true, true, szBuffer, 256 );

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
    TgJOB_THREAD_ID                     atiJob_Thread[KTgMAX_NUM_THREAD + 1];
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

    /* Map the windows to output contexts base don the results. i.e. We selected which output context that we expected for each window in the select data structure, however, the
       context may have failed to be created. Thus, now we map the window to the completed output contexts. */

    for (uiWindow = 0; uiWindow < s_nuiLimit_Windows; ++uiWindow)
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

    {
        TgJOB_QUEUE_ID                      atiQueueList[3];
        TgRSIZE                             uiJobThread;

        atiQueueList[0] = g_sJob_Queue__Render_Normal;
        atiQueueList[1] = KTgJOB_QUEUE_ID__INVALID;

        for (uiJobThread = 0; uiJobThread < sGPU_Init_Result.m_nuiSWAP; ++uiJobThread)
        {
            atiJob_Thread[uiJobThread] = tgJM_Spawn_Job_Thread( atiQueueList, 4, ETgTHREAD_PRIORITY__NORMAL, u8"Render Normal" );
            Test__Expect_NE(KTgID__INVALID_VALUE, atiJob_Thread[uiJobThread].m_uiKI);
        };
    };

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
        for (uiWindow = 0; uiWindow < s_nuiLimit_Windows; ++uiWindow)
        {
            if (ETgTHREAD_STATUS__INVALID == tgKN_OS_Query_Window_Thread_Status( s_shWnd[uiWindow].m_iWnd ))
                continue;
            bAll_Windows_Closed = false;

            uiSwap = (TgRSIZE)s_shWnd[uiWindow].m_iOutput;
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


    {
        TgRSIZE                             uiJobThread;

        for (uiJobThread = 0; uiJobThread < sGPU_Init_Result.m_nuiSWAP; ++uiJobThread)
        {
            tgJM_Stop_Job_Thread( atiJob_Thread[uiJobThread] );
        };
    }

    for (uiSwap = 0; uiSwap < s_sSelect.m_nuiOutput; ++uiSwap)
    {
        Test__Expect_EQ( KTgS_OK, tgUnit_Test__KN_GPU__Release_Resources( uJob_Data[uiSwap].ps->m_tiCXT_EXEC, uJob_Data[uiSwap].ps->m_tiCXT_SWAP ));
    };

    tgKN_GPU_Contexts__Free();

#elif defined(TgBUILD_OS__WINDOWS) /*# defined(TgBUILD_FEATURE__GRAPHICS) */

    TgBOOL                              bAll_Windows_Closed;
    TgRSIZE                             uiLoopWait;

    bAll_Windows_Closed = false;
    for (uiLoopWait = 0; !bAll_Windows_Closed; ++uiLoopWait)
    {
        TgRSIZE                             uiOutput;

        bAll_Windows_Closed = true;
        for (uiOutput = 0; uiOutput < s_nuiLimit_Windows; ++uiOutput)
        {
            if (ETgTHREAD_STATUS__INVALID == tgKN_OS_Query_Window_Thread_Status( s_shWnd[uiOutput].m_iWnd ))
                continue;
            bAll_Windows_Closed = false;
        }
        tgTR_Sleep( 15000 );
    };

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


#if defined(TgBUILD_FEATURE__GRAPHICS) && defined(TgBUILD_OS__WINDOWS)
/* ---- tgUT_KN_GPU_Base_Window_Update ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgSINT_E64 __stdcall tgUT_KN_GPU_Base_Window_Update( HWND hWnd, TgUINT_E32 uMessage, TgUINT_E64 wParam, TgSINT_E64 lParam )
{
    WNDPROC                             pfnDefault_Function = tgKN_OS_Query_Default_WndProc();

#if TgCOMPILE__CONSOLE
    switch (uMessage)
    {
        case WM_KEYDOWN:
            tgCN_OS_Process_Input( wParam, false );
            break;
        default:
            break;
    };
/*# TgCOMPILE__CONSOLE */
#endif

    if (pfnDefault_Function)
    {
        return (pfnDefault_Function( hWnd, uMessage, wParam, lParam ));
    }
    else
    {
        return (-1);
    };
}
/*# defined(TgBUILD_FEATURE__GRAPHICS) && defined(TgBUILD_OS__WINDOWS) */
#endif


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Main Execution                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgCLANG_WARN_SUPPRESS(missing-prototypes)
TgVOID tgCM_Unit_Test_Register( TgVOID )
{
    /* Initialize the unit test structures */

    Unit_Test__Set_Init( &s_sSET__EFFECT );


    /* Configure the test set */

    s_sSET__EFFECT.m_szSet = u8"Effect";


    /* Configure the test cases */


    /* Register all of the test cases with the test set */

    /* Register the test set with the unit test system */

    Unit_Test__Register( &s_sSET__EFFECT );
}
