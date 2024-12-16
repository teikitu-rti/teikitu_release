/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Physics [Unit Test].c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.21 | »GUID« AEEC8393-9780-4ECA-918D-E3E11F7E2744 */
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

TgEXTN TgRESULT
tgUnit_Test__PH__Render(
    TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC, TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP, TgKN_GPU_CXT_WORK_ID tiCXT_WORK, TgRSIZE_C uiTest_Level );

TgEXTN TgVOID
tgUnit_Test__PH__Setup_Scene_Constant_Buffer(
    STg2_KN_GPU_Render_Buffer_CPCU psRTBuffer );

/*# defined(TgBUILD_FEATURE__GRAPHICS) */
#endif

SceneConstantBuffer                 g_sSceneConstantBuffer;
TgPH_WORLD_ID                       g_tiPH_World;
TgPH_BODY_ID                        g_tiPH_BY0, g_tiPH_BY1, g_atiPH_BY2[KTgMAX_TEST_OBJECTS];
TgPH_FORM_ID                        g_atiPH_FM0[5], g_tiPH_FM1, g_atiPH_FM2[KTgMAX_TEST_OBJECTS];




/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

EXTN_METHOD_DECLARE( LINK_TEST__TEST__PH );

TEST_METHOD( UNIT_TEST__TEST__PH_GPU_Render_Enumeration );
TEST_METHOD( UNIT_TEST__TEST__PH_GPU_Render_Init_Select );
TEST_METHOD( UNIT_TEST__TEST__PH_GPU_Render_Init_Windows );
TEST_METHOD( UNIT_TEST__TEST__PH_GPU_Render_Simple );

#if defined(TgBUILD_FEATURE__GRAPHICS)
TgEXTN STg2_KN_GPU_Camera                   g_sCamera;
STg2_KN_GPU_Camera                          g_sCamera;
/*# defined(TgBUILD_FEATURE__GRAPHICS) */
#endif

#if defined(TgBUILD_FEATURE__GRAPHICS) && !defined(TgFEATURE_GRAPHICS__DX12)
TgRESULT tgUnit_Test__PH__Render( TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC, TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP, TgKN_GPU_CXT_WORK_ID tiCXT_WORK, TgRSIZE_C uiTest_Level ) {
    (void)tiCXT_EXEC; (void)tiCXT_SWAP; (void)tiCXT_WORK; (void)uiTest_Level;
    return KTgS_OK;
}
#endif




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

static Test_Set                             s_sSET__PHYSICS;
static Test_Case                            s_sCASE__Physics;

#if defined(TgBUILD_FEATURE__GRAPHICS) 
#if defined(TgBUILD_OS__WINDOWS)
static STg2_KN_OS_UNIT_TEST__UTIL__Window   s_shWnd[KTgKN_MAX_WINDOWS];
#endif

static TgRSIZE                              s_nuiAppWindow = 0; /* Minimum of 1 */
static STg2_KN_GPU_Select                   s_sSelect;

static TgUINT_E64                           s_uiFrame_Counter;
static TgUINT_E64_A                         s_xuiRender_Counter;
static TgFLOAT32                            s_fTotal_Elapse_Frame_Time;

static TgFLOAT32                            s_fCam_Dist_Max = 50.0F;
static TgFLOAT32                            s_fPhi = 3.141592653589793238462643383279F / 4.0F;
static TgFLOAT32                            s_fTheta = 0.0F;

/*# defined(TgBUILD_FEATURE__GRAPHICS) */
#endif

#if defined(TgBUILD_FEATURE__GRAPHICS) && defined(TgBUILD_OS__WINDOWS)
static TgBOOL
tgUT_IN_Gamepad_Camera(
    TgUINT_PTR_C ARG0, TgFLOAT32_C ARG1, STg2_IN_Event_CPC psIN_Event );
/*# defined(TgBUILD_OS__WINDOWS) */
#endif




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TgVOID tgCM_Unit_Test_Register( TgVOID )
{
    /* Initialize the unit test structures */

    Unit_Test__Set_Init( &s_sSET__PHYSICS );
    Unit_Test__Case_Init( &s_sCASE__Physics );



    /* Configure the test set */

    s_sSET__PHYSICS.m_szSet = u8"Physics";



    /* Configure the test cases */

    s_sCASE__Physics.m_pszSet = s_sSET__PHYSICS.m_szSet;
    s_sCASE__Physics.m_pszCase = u8"Render";
    s_sCASE__Physics.m_pfnTest[0] = UNIT_TEST__TEST__PH_GPU_Render_Enumeration;
    s_sCASE__Physics.m_apszTest[0] = u8"Enumeration";
    s_sCASE__Physics.m_pfnTest[1] = UNIT_TEST__TEST__PH_GPU_Render_Init_Windows;
    s_sCASE__Physics.m_apszTest[1] = u8"Init Windows";
    s_sCASE__Physics.m_pfnTest[2] = UNIT_TEST__TEST__PH_GPU_Render_Init_Select;
    s_sCASE__Physics.m_apszTest[2] = u8"Init Select";
    s_sCASE__Physics.m_pfnTest[3] = UNIT_TEST__TEST__PH_GPU_Render_Simple;
    s_sCASE__Physics.m_apszTest[3] = u8"Render";
    //s_sCASE__Physics.m_pfnTest[4] = LINK_TEST__TEST__PH;
    //s_sCASE__Physics.m_apszTest[4] = u8"Link Test - Do not run";



    /* Register all of the test cases with the test set */
    Unit_Test__Set_Register_Case( &s_sSET__PHYSICS, &s_sCASE__Physics );

    /* Register the test set with the unit test system */

    Unit_Test__Register( &s_sSET__PHYSICS );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- UNIT_TEST__TEST__PH_GPU_Render_Enumeration ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__PH_GPU_Render_Enumeration )
{
#if defined(TgBUILD_FEATURE__GRAPHICS)

    STg2_KN_GPU_Adapter_CP              apAdapter[KTgKN_GPU_MAX_ADAPTER];

    /* Enumerate all the device and device instantiations (including software (WARP on DX12) adapters). */
    Test__Expect_EQ(KTgS_OK, tgKN_GPU_Enumerate());

    /* Unit Test validation that we pulled back at least one adapter, and the output list is legal (though potential empty). */
    Test__Expect_EQ(KTgS_OK, tgKN_GPU_Query_Adapter_List( apAdapter, KTgKN_GPU_MAX_ADAPTER ));

/*# defined(TgBUILD_FEATURE__GRAPHICS) */
#endif
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__PH_GPU_Render_Init__Windows ----------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__PH_GPU_Render_Init_Windows )
{
#if defined(TgBUILD_FEATURE__GRAPHICS) && defined(TgBUILD_OS__WINDOWS)
    Test__Expect_EQ( 1, s_nuiAppWindow = tgKN_OS_UNIT_TEST__UTIL__Init_Windows( s_shWnd, KTgKN_MAX_WINDOWS, true ) );
/*# defined(TgBUILD_FEATURE__GRAPHICS) && defined(TgBUILD_OS__WINDOWS) */
#endif

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__PH_GPU_Render_Init_Select ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__PH_GPU_Render_Init_Select )
{
#if defined(TgBUILD_FEATURE__GRAPHICS)

    /* Init the selection structure using a unit test utility for the number of windows created. */
    tgMM_Set_U08_0x00( &s_sSelect, sizeof( s_sSelect ) );
    Test__Expect_EQ(KTgS_OK, tgKN_GPU_UNIT_TEST__UTIL__Init_Select( &s_sSelect, true ));

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

/*# defined(TgBUILD_FEATURE__GRAPHICS) */
#endif

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__PH_GPU_Render_Simple ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__PH_GPU_Render_Simple )
{
#if defined(TgBUILD_FEATURE__GRAPHICS)
    STg2_KN_GPU_Init_Result             sGPU_Init_Result;
    TgRSIZE                             uiWindow;
    TgRSIZE                             uiSwap, nuiSwap, uiFrame_Counter_Start;
    TgBOOL                              bAll_Windows_Closed;
    TgFLOAT32                           afFrame_Elapsed_Time[31];
    TgRSIZE                             nuiFrame_Elapsed_Time = 0;
    TgIN_CONSUMER_ID                    tiIN_GamePad;
    STg2_PH_Mass                        sMass;
    UTg2_CO_Primitive_F32_04            uCollision;
    TgFLOAT32                           fΘ;
    TgRSIZE                             uiIndex;
    TgVEC_F32_04_3                      mIDX;

    TgSTD_ATOMIC(store)( &s_xuiRender_Counter, 0 );
    tgMM_Set_U08_0x00( &sGPU_Init_Result, sizeof( sGPU_Init_Result ) );
    Test__Expect_EQ( KTgS_OK, tgKN_GPU_Contexts__Init( &sGPU_Init_Result, &s_sSelect ) );

    tgCN_Set_Severity_Filter( KTgCN_CHANEL_LOG, KTgCN_SEVERITY_F );

#if defined(TgBUILD_OS__WINDOWS)
    tiIN_GamePad = tgIN_Insert_Consumer( ETgCONTROLLER_GAMEPAD_0, 0, tgUT_IN_Gamepad_Camera, 0 );
/*# defined(TgBUILD_OS__WINDOWS) */
#else
    tiIN_GamePad = KTgIN_CONSUMER_ID__INVALID;
/*# defined(TgBUILD_OS__WINDOWS) */
#endif

    for (uiSwap = 0; uiSwap < sGPU_Init_Result.m_nuiSWAP; ++uiSwap)
    {
        Test__Expect_NE(ETgKN_GPU_EXT_FORMAT__MAX, s_sSelect.m_sOutput[uiSwap].m_sMode.m_sBuffer.m_enFormat);
    };

    /* Map the windows to output contexts base don the results. i.e. We selected which output context that we expected for each window in the select data structure, however, the
       context may have failed to be created. Thus, now we map the window to the completed output contexts. */

#if defined(TgBUILD_OS__WINDOWS)
    for (uiWindow = 0; uiWindow < s_nuiAppWindow; ++uiWindow)
    {
        for (uiSwap = 0; uiSwap < sGPU_Init_Result.m_nuiSWAP; ++uiSwap)
        {
            if (s_shWnd[uiWindow].m_uiOS_ID == sGPU_Init_Result.m_sSWAP[uiSwap].m_uiOS_ID)
            {
                s_shWnd[uiWindow].m_iOutput = (TgSINT_E32)uiSwap;
                break;
            }
        };
    };
/*# defined(TgBUILD_OS__WINDOWS) */
#endif

    /* Physics Init */
    g_tiPH_World = tgPH_World_Query_World_Id( ETgPH_WORLD__SERVER_DEFAULT );
    Test__Expect_NE(KTgPH_WORLD_ID__INVALID.m_uiKI, g_tiPH_World.m_uiKI );

    g_tiPH_World = tgPH_World_Query_World_Id( ETgPH_WORLD__SERVER_DEFAULT );

    g_tiPH_BY0 = tgPH_Body_Init( g_tiPH_World );   Test__Expect_NE(KTgID__INVALID_VALUE, g_tiPH_BY0.m_uiKI );
    tgPH_Mass_Reset( &sMass );

    /* World Box */

    g_atiPH_FM0[0] = tgPH_Form_Init( g_tiPH_World );   Test__Expect_NE(KTgID__INVALID_VALUE, g_atiPH_FM0[0].m_uiKI );
    tgGM_PN_Init_NP_F32_04(&uCollision.m_sPN, tgMH_Init_Vector_ELEM_F32_04_1(0.0F,1.0F,0.0F), tgMH_Init_Point_ELEM_F32_04_1(.0F,0.0F,0.0F));
    tgPH_Form_Set_Collision_Primitive( g_atiPH_FM0[0], ETgPM_PN, &uCollision );
    tgPH_Form_Set_Material_ID( g_atiPH_FM0[0], tgPH_Material_Query_Default( ETgPH_MATERIAL__STEEL_1020 ) );
    tgPH_Form_Set_Scale( g_atiPH_FM0[0], tgMH_Init_ELEM_F32_04_1(40.0F,1.0F,40.0F,0.0F) );
    tgPH_Form_Set_Colour( g_atiPH_FM0[0], tgMH_Init_ELEM_F32_04_1(0.1F,0.1F,0.1F,1.0F) );
    tgPH_Form_Set_World_Collision( g_atiPH_FM0[0], true );

    g_atiPH_FM0[1] = tgPH_Form_Init( g_tiPH_World );   Test__Expect_NE(KTgID__INVALID_VALUE, g_atiPH_FM0[1].m_uiKI );
    tgPH_Form_Set_Collision_Primitive( g_atiPH_FM0[1], ETgPM_PN, &uCollision );
    tgPH_Form_Set_Material_ID( g_atiPH_FM0[1], tgPH_Material_Query_Default( ETgPH_MATERIAL__STEEL_1020 ) );
    tgPH_Form_Set_Position_B( g_atiPH_FM0[1], tgMH_Init_Point_ELEM_F32_04_1(30.0F,10.0F,0.0F) );
    tgPH_Form_Set_Rotation_B( g_atiPH_FM0[1], tgMH_QT_Vector_To_Vector_F32_04_1( tgMH_Init_Vector_ELEM_F32_04_1(0.0F,1.0F,0.0F), tgMH_Init_Vector_ELEM_F32_04_1(1.0F,0.0F,0.0F) ) );
    tgPH_Form_Set_Scale( g_atiPH_FM0[1], tgMH_Init_ELEM_F32_04_1(10.0F,1.0F,30.0F,0.0F) );
    tgPH_Form_Set_Colour( g_atiPH_FM0[1], tgMH_Init_ELEM_F32_04_1(0.2F,0.2F,0.2F,1.0F) );
    tgPH_Form_Set_World_Collision( g_atiPH_FM0[1], true );

    g_atiPH_FM0[2] = tgPH_Form_Init( g_tiPH_World );   Test__Expect_NE(KTgID__INVALID_VALUE, g_atiPH_FM0[2].m_uiKI );
    tgPH_Form_Set_Collision_Primitive( g_atiPH_FM0[2], ETgPM_PN, &uCollision );
    tgPH_Form_Set_Material_ID( g_atiPH_FM0[2], tgPH_Material_Query_Default( ETgPH_MATERIAL__STEEL_1020 ) );
    tgPH_Form_Set_Position_B( g_atiPH_FM0[2], tgMH_Init_Point_ELEM_F32_04_1(-30.0F,10.0F,0.0F) );
    tgPH_Form_Set_Rotation_B( g_atiPH_FM0[2], tgMH_QT_Vector_To_Vector_F32_04_1( tgMH_Init_Vector_ELEM_F32_04_1(0.0F,1.0F,0.0F), tgMH_Init_Vector_ELEM_F32_04_1(-1.0F,0.0F,0.0F) ) );
    tgPH_Form_Set_Scale( g_atiPH_FM0[2], tgMH_Init_ELEM_F32_04_1(10.0F,1.0F,30.0F,0.0F) );
    tgPH_Form_Set_Colour( g_atiPH_FM0[2], tgMH_Init_ELEM_F32_04_1(0.3F,0.3F,0.3F,1.0F) );
    tgPH_Form_Set_World_Collision( g_atiPH_FM0[2], true );

    g_atiPH_FM0[3] = tgPH_Form_Init( g_tiPH_World );   Test__Expect_NE(KTgID__INVALID_VALUE, g_atiPH_FM0[3].m_uiKI );
    tgPH_Form_Set_Collision_Primitive( g_atiPH_FM0[3], ETgPM_PN, &uCollision );
    tgPH_Form_Set_Material_ID( g_atiPH_FM0[3], tgPH_Material_Query_Default( ETgPH_MATERIAL__STEEL_1020 ) );
    tgPH_Form_Set_Position_B( g_atiPH_FM0[3], tgMH_Init_Point_ELEM_F32_04_1(0.0F,10.0F,30.0F) );
    tgPH_Form_Set_Rotation_B( g_atiPH_FM0[3], tgMH_QT_Vector_To_Vector_F32_04_1( tgMH_Init_Vector_ELEM_F32_04_1(0.0F,1.0F,0.0F), tgMH_Init_Vector_ELEM_F32_04_1(0.0F,0.0F,1.0F) ) );
    tgPH_Form_Set_Scale( g_atiPH_FM0[3], tgMH_Init_ELEM_F32_04_1(30.0F,1.0F,10.0F,0.0F) );
    tgPH_Form_Set_Colour( g_atiPH_FM0[3], tgMH_Init_ELEM_F32_04_1(0.4F,0.4F,0.4F,1.0F) );
    tgPH_Form_Set_World_Collision( g_atiPH_FM0[3], true );

    g_atiPH_FM0[4] = tgPH_Form_Init( g_tiPH_World );   Test__Expect_NE(KTgID__INVALID_VALUE, g_atiPH_FM0[4].m_uiKI );
    tgPH_Form_Set_Collision_Primitive( g_atiPH_FM0[4], ETgPM_PN, &uCollision );
    tgPH_Form_Set_Material_ID( g_atiPH_FM0[4], tgPH_Material_Query_Default( ETgPH_MATERIAL__STEEL_1020 ) );
    tgPH_Form_Set_Position_B( g_atiPH_FM0[4], tgMH_Init_Point_ELEM_F32_04_1(0.0F,10.0F,-30.0F) );
    tgPH_Form_Set_Rotation_B( g_atiPH_FM0[4], tgMH_QT_Vector_To_Vector_F32_04_1( tgMH_Init_Vector_ELEM_F32_04_1(0.0F,1.0F,0.0F), tgMH_Init_Vector_ELEM_F32_04_1(0.0F,0.0F,-1.0F) ) );
    tgPH_Form_Set_Scale( g_atiPH_FM0[4], tgMH_Init_ELEM_F32_04_1(30.0F,1.0F,10.0F,0.0F) );
    tgPH_Form_Set_Colour( g_atiPH_FM0[4], tgMH_Init_ELEM_F32_04_1(0.5F,0.5F,0.5F,1.0F) );
    tgPH_Form_Set_World_Collision( g_atiPH_FM0[4], true );

    tgMH_CLI_F32_04_3( &mIDX );

    (void)fΘ;
    (void)uiIndex;
    //for (uiIndex = 0, fΘ = 0; uiIndex < TgARRAY_COUNT(g_atiPH_BY2); ++uiIndex)
    //{
    //    TgFLOAT32                           fRadius;

    //    fRadius = 1.0f + 0.75F * fΘ / KTgPI_F32;
    //    g_atiPH_BY2[uiIndex] = tgPH_Body_Init( g_tiPH_World );   Test__Expect_NE(KTgID__INVALID_VALUE, g_atiPH_BY2[uiIndex].m_uiKI );
    //    g_atiPH_FM2[uiIndex] = tgPH_Form_Init( g_tiPH_World );   Test__Expect_NE(KTgID__INVALID_VALUE, g_atiPH_FM2[uiIndex].m_uiKI );
    //    tgGM_SP_Init_F32_04(&uCollision.m_sSP, tgMH_Init_Point_ELEM_F32_04_1(0.0F,0.0F,0.0F), tgMH_SET1_F32_04_1(0.5F));
    //    tgPH_Form_Set_Collision_Primitive( g_atiPH_FM2[uiIndex], ETgPM_SP, &uCollision );
    //    tgPH_Mass_Set_Mass( &sMass, 1, ETgPM_SP, &uCollision );
    //    tgPH_Form_Set_Material_ID( g_atiPH_FM2[uiIndex], tgPH_Material_Query_Default( ETgPH_MATERIAL__STEEL_1020 ) );
    //    tgPH_Form_Set_Colour( g_atiPH_FM2[uiIndex], tgMH_Init_ELEM_F32_04_1(0.0F,1.5F,2.5F,1.0F) );
    //    tgPH_Body_Add_Form( g_atiPH_BY2[uiIndex], g_atiPH_FM2[uiIndex], &sMass );
    //    tgPH_Body_Set_Position_W( g_atiPH_BY2[uiIndex], tgMH_Init_Point_ELEM_F32_04_1( fRadius*tgPM_COS_F32(fΘ), 5.0F + (TgFLOAT32)uiIndex * 0.25F, fRadius*tgPM_SIN_F32(fΘ) ) );
    //    fΘ += 1.25F / fRadius;

    //    ++uiIndex;
    //    fRadius = 1.0f + 0.75F * fΘ / KTgPI_F32;
    //    g_atiPH_BY2[uiIndex] = tgPH_Body_Init( g_tiPH_World );   Test__Expect_NE(KTgID__INVALID_VALUE, g_atiPH_BY2[uiIndex].m_uiKI );
    //    g_atiPH_FM2[uiIndex] = tgPH_Form_Init( g_tiPH_World );   Test__Expect_NE(KTgID__INVALID_VALUE, g_atiPH_FM2[uiIndex].m_uiKI );
    //    tgGM_BX_Init_F32_04(&uCollision.m_sBX, &mIDX, tgMH_Init_Vector_ELEM_F32_04_1(0.5F,0.5F,0.5F));
    //    tgPH_Mass_Set_Mass( &sMass, 1, ETgPM_BX, &uCollision );
    //    tgPH_Form_Set_Collision_Primitive( g_atiPH_FM2[uiIndex], ETgPM_BX, &uCollision );
    //    tgPH_Form_Set_Material_ID( g_atiPH_FM2[uiIndex], tgPH_Material_Query_Default( ETgPH_MATERIAL__ALUMINUM_6061 ) );
    //    tgPH_Form_Set_Colour( g_atiPH_FM2[uiIndex], tgMH_Init_ELEM_F32_04_1(0.0F,1.5F,2.5F,0.5F) );
    //    tgPH_Body_Add_Form( g_atiPH_BY2[uiIndex], g_atiPH_FM2[uiIndex], &sMass );
    //    tgPH_Body_Set_Position_W( g_atiPH_BY2[uiIndex], tgMH_Init_Point_ELEM_F32_04_1( fRadius*tgPM_COS_F32(fΘ), 5.0F + (TgFLOAT32)uiIndex * 0.25F, fRadius*tgPM_SIN_F32(fΘ) ) );
    //    fΘ += 1.25F / fRadius;

    //    //tgGM_SP_Init_F32_04(&uCollision.m_sSP, tgMH_Init_Point_ELEM_F32_04_1(0.0F,0.0F,0.0F), tgMH_SET1_F32_04_1(0.5F));
    //    //tgPH_Form_Set_Collision_Primitive( g_atiPH_FM2[uiIndex], ETgPM_SP, &uCollision );
    //}

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
            TgOSCHAR                            szBuffer[256];
            TgFLOAT32                           fFrame_Start_Time_Render;

        #if defined(TgBUILD_OS__WINDOWS)
            if (ETgTHREAD_STATUS__INVALID == tgKN_OS_Query_Window_Thread_Status( s_shWnd[uiWindow].m_iWnd ))
                continue;
            bAll_Windows_Closed = false;
            uiSwap = (TgRSIZE)s_shWnd[uiWindow].m_iOutput;
        /*# defined(TgBUILD_OS__WINDOWS) */
        #endif

            ++nuiSwap;

            atiCXT_WORK[nuiCXT_WORK] = tgKN_GPU_EXT__Execute__Frame_Start( sGPU_Init_Result.m_sSWAP[uiSwap].m_tiCXT_EXEC );
            tiCXT_WORK = atiCXT_WORK[nuiCXT_WORK];
            ++nuiCXT_WORK;

            fFrame_Start_Time_Render = tgTM_Query_Time();
            tgUnit_Test__PH__Render( sGPU_Init_Result.m_sSWAP[uiSwap].m_tiCXT_EXEC, sGPU_Init_Result.m_sSWAP[uiSwap].m_tiCXT_SWAP, tiCXT_WORK, 0 );

        #if defined(TgBUILD_OS__WINDOWS)
            /* Add the frame time to the windows title. */
            s_shWnd[uiWindow].m_fFrame_Elapsed_Time = tgTM_Query_Time() - fFrame_Start_Time_Render;
            TgOS_TEXT_FCN(PrintF)( szBuffer, 256, TgOS_TEXT(" Render Time: % 2.2fms, Update Time: % 2.2fms"), (double)s_shWnd[uiWindow].m_fFrame_Elapsed_Time,
                                   (double)s_fTotal_Elapse_Frame_Time );
            tgKN_OS_Set_Window_Title(s_shWnd[uiWindow].m_iWnd, szBuffer, 256 );
        /*# defined(TgBUILD_OS__WINDOWS) */
        #endif

            TgSTD_ATOMIC(fetch_add)( &s_xuiRender_Counter, 1 );
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
        tgGB_Update( afFrame_Elapsed_Time[nuiFrame_Elapsed_Time % 31] );
        tgCO_Module_Update( afFrame_Elapsed_Time[nuiFrame_Elapsed_Time % 31] );
        tgKN_Module_Update( afFrame_Elapsed_Time[nuiFrame_Elapsed_Time % 31] );
        tgIN_Module_Update( afFrame_Elapsed_Time[nuiFrame_Elapsed_Time % 31] );
        tgPH_Module_Update( afFrame_Elapsed_Time[nuiFrame_Elapsed_Time % 31] );

        tgPH__Server__Update( afFrame_Elapsed_Time[nuiFrame_Elapsed_Time % 31] );
        tgPH__Client__Update_PreInput( afFrame_Elapsed_Time[nuiFrame_Elapsed_Time % 31] );
        tgIN_Update__Client( afFrame_Elapsed_Time[nuiFrame_Elapsed_Time % 31] );
        tgPH__Client__Update_PostInput( afFrame_Elapsed_Time[nuiFrame_Elapsed_Time % 31] );

        if (!bAll_Windows_Closed)
        {
        }

        ++nuiFrame_Elapsed_Time;
        afFrame_Elapsed_Time[nuiFrame_Elapsed_Time % 31] = tgTM_Query_Time() - fFrame_Start_Time;

        /* Calculate a smoothed total frame time. */
        s_fTotal_Elapse_Frame_Time = 0.0F;
        for (uiWindow = 0; uiWindow < 31; ++uiWindow)
        {
            s_fTotal_Elapse_Frame_Time += afFrame_Elapsed_Time[uiWindow];
        }
        s_fTotal_Elapse_Frame_Time /= 31.0F;
    };


    tgKN_GPU_Contexts__Free();

    tgIN_Remove_Consumer( tiIN_GamePad );
    tiIN_GamePad.m_uiKI = KTgID__INVALID_VALUE;
    tgIN_Update__Client( 0.0F );

/*# defined(TgBUILD_FEATURE__GRAPHICS) */
#endif

    TEST_END_METHOD( KTgS_OK );
}


/* ---- tgUnit_Test__PH__Setup_Scene_Constant_Buffer ----------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if defined(TgBUILD_FEATURE__GRAPHICS)
TgVOID tgUnit_Test__PH__Setup_Scene_Constant_Buffer( STg2_KN_GPU_Render_Buffer_CPCU psRTBuffer )
{
    TgFLOAT32_C                         fAspect_Ratio = (float)psRTBuffer->m_uiWidth / (float)psRTBuffer->m_uiHeight;
    TgFLOAT32_C                         fFoV = 35.0F * KTgPI_F32 / 180.0f;

    TgVEC_S_F32_04_1                    vEye, vUp;
    TgFLOAT32                           fCosTheta, fSinTheta, fCosPhi, fSinPhi;
    TgVEC_S_F32_04_4                    mS2C;

    tgMH_PProj_FoVLH_S_F32_04_4( &g_sSceneConstantBuffer.m_mC2S, fFoV, fAspect_Ratio, 0.01F, 1000.0F );
    tgMM_Copy( &g_sCamera.m_xFrustum_C2S, sizeof(g_sCamera.m_xFrustum_C2S), &g_sSceneConstantBuffer.m_mC2S, sizeof(g_sSceneConstantBuffer.m_mC2S) );
    tgMH_INV_S_F32_04_4( &mS2C, &g_sSceneConstantBuffer.m_mC2S );
    tgMM_Copy( &g_sCamera.m_xFrustum_S2C, sizeof(g_sCamera.m_xFrustum_S2C), &mS2C, sizeof(mS2C) );

    if (fAspect_Ratio < 1.0F)
    {
        TgFLOAT32_C                         fSwap = g_sSceneConstantBuffer.m_mC2S._11;

        g_sSceneConstantBuffer.m_mC2S._11 = g_sSceneConstantBuffer.m_mC2S._22 / fAspect_Ratio;
        g_sSceneConstantBuffer.m_mC2S._22 = fSwap * fAspect_Ratio;
    }

    if (g_tiPH_BY1.m_uiKI != 0ULL)
    {
        tgPH_Body_Query_Position_W( &g_sCamera.m_sCamera.m_uCam_Target.m_vF32_04_1, g_tiPH_BY1 );
    }

    tgPM_SINCOS_F32( &fSinTheta, &fCosTheta, s_fTheta );
    tgPM_SINCOS_F32( &fSinPhi, &fCosPhi, s_fPhi );

    vEye = tgMH_Init_Point_ELEM_S_F32_04_1( fCosTheta * fCosPhi * s_fCam_Dist_Max,
                                            fSinPhi * s_fCam_Dist_Max,
                                            fSinTheta * fCosPhi * s_fCam_Dist_Max );
    vEye = tgMH_ADD_S_F32_04_1( vEye, g_sCamera.m_sCamera.m_uCam_Target.m_vS_F32_04_1 );

    vUp = tgMH_Init_Vector_ELEM_S_F32_04_1( 0.0f, 1.0f, 0.0f );

    tgMH_LookLH_S_F32_04_4( &g_sSceneConstantBuffer.m_mW2C, vEye, g_sCamera.m_sCamera.m_uCam_Target.m_vS_F32_04_1, vUp );
    tgMM_Copy( &g_sCamera.m_xFrustum_W2C, sizeof(g_sCamera.m_xFrustum_W2C), &g_sSceneConstantBuffer.m_mW2C, sizeof(g_sSceneConstantBuffer.m_mW2C) );

    g_sCamera.m_sCamera.m_uCam_Position.m_vS_F32_04_1 = vEye;

    g_sCamera.m_vCam_Forward = tgMH_Init_Vector_F32_04_1( g_sCamera.m_xFrustum_W2C.m_vC2 );
    g_sCamera.m_vCam_Right = tgMH_Init_Vector_F32_04_1( g_sCamera.m_xFrustum_W2C.m_vC0 );
    g_sCamera.m_vCam_Up = tgMH_Init_Vector_F32_04_1( g_sCamera.m_xFrustum_W2C.m_vC1 );
}
/*# defined(TgBUILD_FEATURE__GRAPHICS) */
#endif




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgUT_IN_Gamepad_Camera --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if defined(TgBUILD_FEATURE__GRAPHICS) && defined(TgBUILD_OS__WINDOWS)
static TgBOOL tgUT_IN_Gamepad_Camera( TgATTRIBUTE_UNUSED TgUINT_PTR_C ARG0, TgATTRIBUTE_UNUSED TgFLOAT32_C ARG1, STg2_IN_Event_CPC psIN_Event )
{
    static TgBOOL bChange_Camera_Target = false;
    static TgSINT_E32 iPM_To_Create = 1;

    if (ETgCONTROLLER_GAMEPAD_0 != psIN_Event->m_enController)
        return (false);

    TgWARN_DISABLE_PUSH(4061 4062,switch-enum)
    switch (psIN_Event->m_enProp.GamePad) {
    case ETgPROP_GAMEPAD__A:
        tgPH_World_Set_Simulation_Enable( g_tiPH_World, psIN_Event->m_fValue > 0.5F );
        break;
    case ETgPROP_GAMEPAD__B:
        if (psIN_Event->m_fValue > 0.5F)
        {
            TgBOOL                              bState;

            if (TgSUCCEEDED(tgPH_World_Query_Collision_Simple_Override( &bState, g_tiPH_World )))
            {
                tgPH_World_Set_Collision_Simple_Override( g_tiPH_World, !bState );
            }
        };
        break;
    case ETgPROP_GAMEPAD__X:
        if (g_tiPH_BY1.m_uiKI == KTgID__INVALID_VALUE)
        {
            STg2_PH_Mass                        sMass;
            UTg2_CO_Primitive_F32_04            uCollision;

            g_tiPH_BY1 = tgPH_Body_Init( g_tiPH_World );
            g_tiPH_FM1 = tgPH_Form_Init( g_tiPH_World );

            tgPH_Form_Set_Material_ID( g_tiPH_FM1, tgPH_Material_Query_Default( ETgPH_MATERIAL__ALUMINUM_6061 ) );
            tgPH_Mass_Reset( &sMass );
            tgPH_Form_Set_Scale( g_tiPH_FM1, tgMH_Init_ELEM_F32_04_1(1.0F,1.0F,1.0F,0.0F) );
            tgPH_Form_Set_Colour( g_tiPH_FM1, tgMH_Init_ELEM_F32_04_1(0.0F,2.5F,2.5F,1.0F) );
            switch (iPM_To_Create) {
            case 2: {
                TgVEC_F32_04_3                      mFM;

                tgMH_Init_Euler_F32_04_3( &mFM, tgMH_Init_ELEM_F32_04_1(90.0F * KTgTWO_PI_F32 / 360.0F, 0.0F, 45.0F * KTgTWO_PI_F32 / 360.0F, 0.0F ) );
                tgGM_TB_Init_F32_04(&uCollision.m_sTB, &mFM, tgMH_SET1_F32_04_1(5.0F), tgMH_SET1_F32_04_1(1.0F));
                tgPH_Form_Set_Collision_Primitive( g_tiPH_FM1, ETgPM_CP, &uCollision );
                tgPH_Mass_Set_Mass( &sMass, 10, ETgPM_CP, &uCollision );
                tgPH_Body_Set_Position_W( g_tiPH_BY1, tgMH_Init_Point_ELEM_F32_04_1( 22.0F, 1.0F, 22.0F ) );
                tgPH_Body_Set_Linear_Velocity( g_tiPH_BY1, tgMH_Init_Vector_ELEM_F32_04_1( -9.0F, 0.0F, -9.0F ) );
            } break;
            case 1: {
                TgVEC_F32_04_3                      mIDX;

                tgMH_CLI_F32_04_3( &mIDX );
                tgGM_BX_Init_F32_04(&uCollision.m_sBX, &mIDX, tgMH_Init_Vector_ELEM_F32_04_1(0.5F,0.5F,0.5F));
                tgPH_Mass_Set_Mass( &sMass, 1, ETgPM_BX, &uCollision );
                tgPH_Form_Set_Collision_Primitive( g_tiPH_FM1, ETgPM_BX, &uCollision );
                tgPH_Form_Set_Material_ID( g_tiPH_FM1, tgPH_Material_Query_Default( ETgPH_MATERIAL__ALUMINUM_6061 ) );
                tgPH_Form_Set_Colour( g_tiPH_FM1, tgMH_Init_ELEM_F32_04_1(0.0F,1.5F,2.5F,0.5F) );
                tgPH_Body_Set_Position_W( g_tiPH_BY1, tgMH_Init_Point_ELEM_F32_04_1( 0.0F, 5.0F, 0.0F ) );
            } break;
            default:
                tgGM_SP_Init_F32_04(&uCollision.m_sSP, tgMH_Init_Point_ELEM_F32_04_1(0.0F,0.0F,0.0F), tgMH_SET1_F32_04_1(2.0F));
                tgPH_Form_Set_Collision_Primitive( g_tiPH_FM1, ETgPM_SP, &uCollision );
                tgPH_Mass_Set_Mass( &sMass, 1, ETgPM_SP, &uCollision );
                tgPH_Body_Set_Position_W( g_tiPH_BY1, tgMH_Init_Point_ELEM_F32_04_1( 0.0F, 15.0F, 0.0F ) );
                break;
            }

            tgPH_Body_Add_Form( g_tiPH_BY1, g_tiPH_FM1, &sMass );
            tgPH_Body_Set_Force_Field_Factor( g_tiPH_BY1, tgMH_SET1_F32_04_1( 10.0F ) );
        };
        break;
    case ETgPROP_GAMEPAD__Y:
        if (g_tiPH_BY1.m_uiKI != KTgID__INVALID_VALUE)
        {
            tgPH_Body_Reset( g_tiPH_BY1 );
            g_tiPH_BY1.m_uiKI = KTgID__INVALID_VALUE;
            g_tiPH_FM1.m_uiKI = KTgID__INVALID_VALUE;
        };
        break;
    case ETgPROP_GAMEPAD__LTHUMB_X:
        if (bChange_Camera_Target)
        {
            g_sCamera.m_sCamera.m_uCam_Target.m_vF32_04_1 = tgMH_MAD_F32_04_1( g_sCamera.m_vCam_Right, tgMH_SET1_F32_04_1( psIN_Event->m_fValue * 0.0025F ), g_sCamera.m_sCamera.m_uCam_Target.m_vF32_04_1 );
        }
        else
        {
            s_fTheta = tgPM_FMOD_F32( s_fTheta + psIN_Event->m_fValue * 0.0025F, KTgTWO_PI_F32 );
        }
        break;
    case ETgPROP_GAMEPAD__LTHUMB_Y:
        if (bChange_Camera_Target)
        {
            g_sCamera.m_sCamera.m_uCam_Target.m_vF32_04_1 = tgMH_MAD_F32_04_1( g_sCamera.m_vCam_Up, tgMH_SET1_F32_04_1( psIN_Event->m_fValue * 0.0025F ), g_sCamera.m_sCamera.m_uCam_Target.m_vF32_04_1 );
        }
        else
        {
            s_fPhi = tgCM_CLP_F32( s_fPhi + psIN_Event->m_fValue * 0.0005F, KTgPI_F32 / 16.0F, KTgPI_F32 * 7.0F / 16.0F );
        }
        break;
    case ETgPROP_GAMEPAD__RTHUMB_Y:
        if (bChange_Camera_Target)
        {
            g_sCamera.m_sCamera.m_uCam_Target.m_vS_F32_04_1.y += psIN_Event->m_fValue * 0.0025F;
        }
        else
        {
            s_fCam_Dist_Max = tgCM_CLP_F32( s_fCam_Dist_Max - psIN_Event->m_fValue * 0.05F, 5.0F, 150.0F );
        }
        break;
    case ETgPROP_GAMEPAD__RSHOULDER: TgATTRIBUTE_FALLTHROUGH
    case ETgPROP_GAMEPAD__LSHOULDER:
        bChange_Camera_Target = psIN_Event->m_fValue > 0.5F;
        break;

    default:
        break;
    };
    TgWARN_DISABLE_POP()
    return (true);
}
/*# defined(TgBUILD_FEATURE__GRAPHICS) */
#endif


TgCLANG_WARN_DISABLE_POP(unused-variable)
