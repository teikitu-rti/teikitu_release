/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Effect [Unit Test].c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
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
tgUnit_Test__FX__Create_Resources(
    TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC, TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP, TgUINT_E32 uiNodeMask );

TgEXTN TgRESULT
tgUnit_Test__FX__Render(
    TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC, TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP, TgKN_GPU_CXT_WORK_ID_C tiCXT_WORK, TgRSIZE_C uiTest_Level );

TgEXTN TgRESULT
tgUnit_Test__FX__Release_Resources(
    TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC, TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP );

TgEXTN TgVOID
tgUnit_Test__FX__Setup_Scene_Constant_Buffer(
    STg2_KN_GPU_Render_Buffer_CPCU psRTBuffer );

/*# defined(TgBUILD_FEATURE__GRAPHICS) */
#endif

SceneConstantBuffer g_sSceneConstantBuffer;




/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TEST_METHOD( UNIT_TEST__TEST__FX_GPU_Render_Enumeration );
TEST_METHOD( UNIT_TEST__TEST__FX_GPU_Render_Init_Select );
TEST_METHOD( UNIT_TEST__TEST__FX_GPU_Render_Init_Windows );
TEST_METHOD( UNIT_TEST__TEST__FX_GPU_Render_Simple );

#if defined(TgBUILD_FEATURE__GRAPHICS)
TgEXTN STg2_KN_GPU_Camera                   g_sCamera;
STg2_KN_GPU_Camera                          g_sCamera;
/*# defined(TgBUILD_FEATURE__GRAPHICS) */
#endif




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

static Test_Set                             s_sSET__EFFECT;
static Test_Case                            s_sCASE__Effect_Effects;

#if defined(TgBUILD_FEATURE__GRAPHICS) 

#if defined(TgBUILD_OS__WINDOWS)
static TgRSIZE                              s_nuiAppWindow = 0; /* Minimum of 1 */
static STg2_KN_OS_UNIT_TEST__UTIL__Window   s_shWnd[KTgKN_MAX_WINDOWS];
/*# defined(TgBUILD_OS__WINDOWS) */
#endif

static STg2_KN_GPU_Select                   s_sSelect;

static TgVOID
tgUnit_Test__FX__Init_Billboard(
    TgUINT_E08_P puiBuffer );

static TgVOID
tgUnit_Test__FX__Init_Beam(
    TgUINT_E08_P puiBuffer );

static TgVOID
tgUnit_Test__FX__Init_Emitter(
    TgUINT_E08_P puiBuffer );

static TgVOID
tgUnit_Test__FX__Init_Particle(
    TgUINT_E08_P puiBuffer );

static TgVOID
tgUnit_Test__FX__Init_Trail(
    TgUINT_E08_P puiBuffer );

#if defined(TgBUILD_OS__WINDOWS)

static TgBOOL
tgUT_IN_Gamepad_Camera(
    TgUINT_PTR_C ARG0, TgFLOAT32_C ARG1, STg2_IN_Event_CPC psIN_Event );

/*# defined(TgBUILD_OS__WINDOWS) */
#endif

static TgFLOAT32                            s_fCam_Dist_Max[2] = { 50.0F, 50.0F };
static TgFLOAT32                            s_fPhi[2] = { 3.141592653589793238462643383279F / 4.0F, 3.141592653589793238462643383279F / 4.0F };
static TgFLOAT32                            s_fTheta[2] = { 0.0F, 0.0F };
static TgSINT_E32                           s_iCamera_Select = 0;


static TgRESULT
UNIT_TEST__TEST__FX_GPU_Render_Simple_Job(
    STg2_Job_CPC psJob );

static TgUINT_E64                           s_uiFrame_Counter;
static TgUINT_E64_A                         s_xuiRender_Counter;
static TgFLOAT32                            s_fTotal_Elapse_Frame_Time;

static TgBOOL                               s_bTest_Context_CMD_Per_Window = false;
static TgBOOL                               s_bTest_Render_With_Jobs = false;

TgTYPE_STRUCT( UT_KN_GPU_Render_Simple_Job_Data, )
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

TgVOID tgCM_Unit_Test_Register( TgVOID )
{
    /* Initialize the unit test structures */

    Unit_Test__Set_Init( &s_sSET__EFFECT );
    Unit_Test__Case_Init( &s_sCASE__Effect_Effects );



    /* Configure the test set */

    s_sSET__EFFECT.m_szSet = u8"Effect";



    /* Configure the test cases */

    s_sCASE__Effect_Effects.m_pszSet = s_sSET__EFFECT.m_szSet;
    s_sCASE__Effect_Effects.m_pszCase = u8"Render";
    s_sCASE__Effect_Effects.m_pfnTest[0] = UNIT_TEST__TEST__FX_GPU_Render_Enumeration;
    s_sCASE__Effect_Effects.m_apszTest[0] = u8"Enumeration";
    s_sCASE__Effect_Effects.m_pfnTest[1] = UNIT_TEST__TEST__FX_GPU_Render_Init_Windows;
    s_sCASE__Effect_Effects.m_apszTest[1] = u8"Init Windows";
    s_sCASE__Effect_Effects.m_pfnTest[2] = UNIT_TEST__TEST__FX_GPU_Render_Init_Select;
    s_sCASE__Effect_Effects.m_apszTest[2] = u8"Init Select";
    s_sCASE__Effect_Effects.m_pfnTest[3] = UNIT_TEST__TEST__FX_GPU_Render_Simple;
    s_sCASE__Effect_Effects.m_apszTest[3] = u8"Render";



    /* Register all of the test cases with the test set */
    Unit_Test__Set_Register_Case( &s_sSET__EFFECT, &s_sCASE__Effect_Effects );

    /* Register the test set with the unit test system */

    Unit_Test__Register( &s_sSET__EFFECT );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- UNIT_TEST__TEST__FX_GPU_Render_Enumeration ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__FX_GPU_Render_Enumeration )
{
#if defined(TgBUILD_FEATURE__GRAPHICS)

    STg2_KN_GPU_Physical_Device_CP      apPhysical_Device[KTgKN_GPU_MAX_PHYSICAL_DEVICE];

    /* Enumerate all the device and device instantiations (including software (WARP on DX12) adapters). */
    Test__Expect_EQ(KTgS_OK, tgKN_GPU_Enumerate());

    /* Unit Test validation that we pulled back at least one adapter, and the output list is legal (though potential empty). */
    Test__Expect_EQ(KTgS_OK, tgKN_GPU__Host__Query_Physical_Device_List( apPhysical_Device, KTgKN_GPU_MAX_PHYSICAL_DEVICE ));
    Test__Expect_NE(nullptr, apPhysical_Device[0]);

/*# defined(TgBUILD_FEATURE__GRAPHICS) */
#endif
    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__FX_GPU_Render_Init__Windows ----------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__FX_GPU_Render_Init_Windows )
{
#if defined(TgBUILD_FEATURE__GRAPHICS) && defined(TgBUILD_OS__WINDOWS)
    Test__Expect_EQ( 1, s_nuiAppWindow = tgKN_OS_UNIT_TEST__UTIL__Init_Windows( s_shWnd, KTgKN_MAX_WINDOWS, true ) );
/*# defined(TgBUILD_FEATURE__GRAPHICS) && defined(TgBUILD_OS__WINDOWS) */
#endif

    TEST_END_METHOD( KTgS_OK );
}


/* ---- UNIT_TEST__TEST__FX_GPU_Render_Init_Select ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__FX_GPU_Render_Init_Select )
{
#if defined(TgBUILD_FEATURE__GRAPHICS)

    /* Init the selection structure using a unit test utility for the number of windows created. */
    tgMM_Set_U08_0x00( &s_sSelect, sizeof( s_sSelect ) );
    Test__Expect_EQ(KTgS_OK, tgKN_GPU_UNIT_TEST__UTIL__Init_Select( &s_sSelect, true ));

#if defined(TgBUILD_OS__WINDOWS)
    s_sSelect.m_nuiOutput = tgCM_MIN_UMAX(s_nuiAppWindow,s_sSelect.m_nuiOutput);
    s_sSelect.m_sOutput[0].m_uiOS_ID = s_shWnd[0].m_uiOS_ID;
/*# defined(TgBUILD_OS__WINDOWS) */
#endif

/*# defined(TgBUILD_FEATURE__GRAPHICS) */
#endif

    TEST_END_METHOD( KTgS_OK );
}



/* ---- UNIT_TEST__TEST__FX_GPU_Render_Simple_Job -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if defined(TgBUILD_FEATURE__GRAPHICS)
static TgRESULT UNIT_TEST__TEST__FX_GPU_Render_Simple_Job( STg2_Job_CPC psJob )
{
    union { TgUINT_E08_CP pui; UT_KN_GPU_Render_Simple_Job_Data_CP ps; } const uJob_Data = { .pui = psJob->m_auiData };
    (void)uJob_Data;

    TgSTD_ATOMIC(fetch_add)( &s_xuiRender_Counter, 1 );
    return (KTgS_OK);
}
/*# defined(TgBUILD_FEATURE__GRAPHICS) */
#endif


#if defined(TgBUILD_FEATURE__GRAPHICS)
TgEXTN STg2_FX_Rnd_Output           g_sRN_Output;
TgEXTN TgUINT_E08_P                 g_pbyFX_Billboard_Test;
TgEXTN TgUINT_E08_P                 g_pbyFX_Beam_Test;
TgEXTN TgRSIZE                      g_nbyFX_Beam_Test;
TgEXTN TgUINT_E08_P                 g_pbyFX_Emitter_Test;
TgEXTN TgRSIZE                      g_nbyFX_Emitter_Test;
TgEXTN TgUINT_E08_P                 g_pbyFX_Particle_Test;
TgEXTN TgRSIZE                      g_nbyFX_Particle_Test;
TgEXTN TgUINT_E08_P                 g_pbyFX_Trail_Test;
TgEXTN TgRSIZE                      g_nbyFX_Trail_Test;

STg2_FX_Rnd_Output                  g_sRN_Output;
TgUINT_E08_P                        g_pbyFX_Billboard_Test;
TgUINT_E08_P                        g_pbyFX_Beam_Test;
TgRSIZE                             g_nbyFX_Beam_Test;
TgUINT_E08_P                        g_pbyFX_Emitter_Test;
TgRSIZE                             g_nbyFX_Emitter_Test;
TgUINT_E08_P                        g_pbyFX_Particle_Test;
TgRSIZE                             g_nbyFX_Particle_Test;
TgUINT_E08_P                        g_pbyFX_Trail_Test;
TgRSIZE                             g_nbyFX_Trail_Test;
/*# defined(TgBUILD_FEATURE__GRAPHICS) */
#endif


/* ---- UNIT_TEST__TEST__FX_GPU_Render_Simple ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD( UNIT_TEST__TEST__FX_GPU_Render_Simple )
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
    STg2_SE_Context                     sSE_Context;
    TgIN_CONSUMER_ID                    tiIN_GamePad;
    STg2_FX_Instance                    sInstance;
    TgFX_CLIENT_INST_ID                 tiTrail;


    tgMM_Set_U08_0x00( &sSE_Context, sizeof( sSE_Context ) );
    sSE_Context.m_asFrame_Mesh = (STg2_RN_Cxt_Mesh_P)TgMALLOC_POOL( sizeof(STg2_RN_Cxt_Mesh) * KTgRN_MAX_FRAME_MESH );
    sSE_Context.m_nuiFrame_Mesh_Max = KTgRN_MAX_FRAME_MESH;
    sSE_Context.m_asView[0].m_anuiFrame_Mesh_Inst_Max[ETgSE_DRAW_TYPE__OPAQUE] = KTgFX_MAX_RENDER_INSTANCE;
    sSE_Context.m_asView[0].m_apuiFrame_Mesh_Inst[ETgSE_DRAW_TYPE__OPAQUE] = (TgRSIZE_P)TgMALLOC_POOL( sizeof(TgRSIZE) * KTgFX_MAX_RENDER_INSTANCE );
    sSE_Context.m_asView[0].m_anuiFrame_Mesh_Inst_Max[ETgSE_DRAW_TYPE__TRANSPARENT] = KTgFX_MAX_RENDER_INSTANCE;
    sSE_Context.m_asView[0].m_apuiFrame_Mesh_Inst[ETgSE_DRAW_TYPE__TRANSPARENT] = (TgRSIZE_P)TgMALLOC_POOL( sizeof(TgRSIZE) * KTgFX_MAX_RENDER_INSTANCE );

    tgMM_Set_U08_0x00( &g_sRN_Output, sizeof( g_sRN_Output ) );
    g_sRN_Output.m_puiContext_To_Particle_Header_Index = (TgRSIZE_P)TgMALLOC_POOL( sizeof(TgRSIZE) * KTgFX_MAX_RENDER_INSTANCE );
    g_sRN_Output.m_psFX_Header = (STg2_RN_Particle_Header_P)TgMALLOC_POOL( sizeof(STg2_RN_Particle_Header) * KTgFX_MAX_RENDER_INSTANCE );
    g_sRN_Output.m_nuiFX_Header_Max = KTgFX_MAX_RENDER_INSTANCE;
    g_sRN_Output.m_puiBuffer = (TgUINT_E08_P)TgMALLOC_POOL( KTgRN_MAX_PRTCL_BUFFER_SIZE );
    g_sRN_Output.m_nbyUsed = 0;
    g_sRN_Output.m_nbyFree = KTgRN_MAX_PRTCL_BUFFER_SIZE;
    g_sRN_Output.m_psCamera = &g_sCamera;

    TgSTD_ATOMIC(store)( &s_xuiRender_Counter, 0 );
    tgMM_Set_U08_0x00( &sGPU_Init_Result, sizeof( sGPU_Init_Result ) );
    Test__Expect_EQ( KTgS_OK, tgKN_GPU_Contexts__Init( &sGPU_Init_Result, &s_sSelect ) );

#if defined(TgBUILD_OS__WINDOWS)
    tiIN_GamePad = tgIN_Insert_Consumer( ETgCONTROLLER_GAMEPAD_0, 0, tgUT_IN_Gamepad_Camera, 0 );
/*# defined(TgBUILD_OS__WINDOWS) */
#else
    tiIN_GamePad = KTgIN_CONSUMER_ID__INVALID;
/*# defined(TgBUILD_OS__WINDOWS) */
#endif

    g_pbyFX_Billboard_Test = (TgUINT_E08_P)TgMALLOC_POOL( sizeof( STg2_FX_Billboard__File_Data ) + 2 * sizeof( STg2_FX_AnimData__Constant_F32_04 ) );
    tgUnit_Test__FX__Init_Billboard( g_pbyFX_Billboard_Test );

    tgMM_Set_U08_0x00( &sInstance, sizeof( sInstance ) );
    sInstance.m_vPos_N2W = tgMH_Init_ELEM_F32_04_1( 5.0F, 0.0F, 5.0F, 0.0F );
    sInstance.m_vScale = tgMH_SET1_F32_04_1( 1.0F );
    tgFX__Client__Inst_FX_RAW( ETgFX__BILLBOARD, g_pbyFX_Billboard_Test, nullptr, &sInstance, false );

    g_nbyFX_Beam_Test = sizeof( STg2_FX_Beam__File_Data ) + 10 * 2 * sizeof( TgVEC_F32_04_1 ) + 15 * 2 + 10 * 3 * sizeof( TgFLOAT32 );
    g_nbyFX_Beam_Test += sizeof( STg2_FX_AnimData__Constant_F32_04 ) + sizeof( STg2_FX_AnimData__Key_Frame_F32_02 ) + 60 * sizeof(TgFLOAT32);
    g_pbyFX_Beam_Test = (TgUINT_E08_P)TgMALLOC_POOL( g_nbyFX_Beam_Test );
    tgUnit_Test__FX__Init_Beam( g_pbyFX_Beam_Test );

    tgMM_Set_U08_0x00( &sInstance, sizeof( sInstance ) );
    sInstance.m_vPos_N2W = tgMH_Init_ELEM_F32_04_1( -5.0F, 0.0F, -5.0F, 0.0F );
    sInstance.m_qRot_N2W = KTgUNIT_W_F32_04_1;
    sInstance.m_vScale = tgMH_SET1_F32_04_1( 1.0F );
    tgFX__Client__Inst_FX_RAW( ETgFX__BEAM, g_pbyFX_Beam_Test, nullptr, &sInstance, false );

    g_nbyFX_Particle_Test = sizeof( STg2_FX_Particle__File_Data ) + 7 * sizeof( STg2_FX_AnimData__Constant_F32_04 ) + sizeof( STg2_FX_AnimData__Constant_UXX );
    g_pbyFX_Particle_Test = (TgUINT_E08_P)TgMALLOC_POOL( g_nbyFX_Particle_Test );
    tgUnit_Test__FX__Init_Particle( g_pbyFX_Particle_Test );

    g_nbyFX_Emitter_Test = sizeof( STg2_FX_Emitter__File_Data ) + 3 * sizeof( STg2_FX_AnimData__Constant_F32_04 );
    g_pbyFX_Emitter_Test = (TgUINT_E08_P)TgMALLOC_POOL( g_nbyFX_Emitter_Test );
    tgUnit_Test__FX__Init_Emitter( g_pbyFX_Emitter_Test );

    tgMM_Set_U08_0x00( &sInstance, sizeof( sInstance ) );
    sInstance.m_vPos_N2W = tgMH_Init_ELEM_F32_04_1( 0.0F, 10.0F, 0.0F, 0.0F );
    sInstance.m_qRot_N2W = KTgUNIT_W_F32_04_1;
    sInstance.m_vScale = tgMH_SET1_F32_04_1( 1.0F );
    tgFX__Client__Inst_FX_RAW( ETgFX__EMITTER, g_pbyFX_Emitter_Test, g_pbyFX_Particle_Test, &sInstance, false );

    g_nbyFX_Trail_Test = sizeof( STg2_FX_Beam__File_Data ) + 10 * 2 * sizeof( TgVEC_F32_04_1 ) + 15 * 2 + 10 * 3 * sizeof( TgFLOAT32 );
    g_nbyFX_Trail_Test += sizeof( STg2_FX_AnimData__Constant_F32_04 ) + sizeof( STg2_FX_AnimData__Key_Frame_F32_02 ) + 60 * sizeof(TgFLOAT32);
    g_pbyFX_Trail_Test = (TgUINT_E08_P)TgMALLOC_POOL( g_nbyFX_Trail_Test );
    tgUnit_Test__FX__Init_Trail( g_pbyFX_Trail_Test );

    tgMM_Set_U08_0x00( &sInstance, sizeof( sInstance ) );
    sInstance.m_vPos_N2W = tgMH_Init_ELEM_F32_04_1( -15.0F, 10.0F, 0.0F, 0.0F );
    sInstance.m_qRot_N2W = KTgUNIT_W_F32_04_1;
    sInstance.m_vScale = tgMH_SET1_F32_04_1( 1.0F );
    tiTrail = tgFX__Client__Inst_FX_RAW( ETgFX__TRAIL, g_pbyFX_Trail_Test, nullptr, &sInstance, false );

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

        asJob[uiSwap].m_pfnExecute = UNIT_TEST__TEST__FX_GPU_Render_Simple_Job;

        Test__Expect_NE(ETgKN_GPU_EXT_FORMAT_UNDEFINED, s_sSelect.m_sOutput[uiSwap].m_sMode.m_sBuffer.m_enFormat);
        tgUnit_Test__FX__Create_Resources( uJob_Data[uiSwap].ps->m_tiCXT_EXEC, uJob_Data[uiSwap].ps->m_tiCXT_SWAP, uJob_Data[uiSwap].ps->m_uiNodeMask );
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

        tgFX__Client__Wait_For_Render_Completion();

        /* Render based on all of the swap chain contexts. */
        fFrame_Start_Time = tgTM_Query_Time();

        /* Check to see if all the windows have been closed, to quit the application.
           Render the swap chains associated with any active window. */
        bAll_Windows_Closed = true;
        nuiSwap = 0;
        uiFrame_Counter_Start = TgSTD_ATOMIC(load)( &s_xuiRender_Counter );
    #if defined(TgBUILD_OS__WINDOWS)
        for (uiWindow = 0; uiWindow < s_nuiAppWindow; ++uiWindow)
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
                UNIT_TEST__TEST__FX_GPU_Render_Simple_Job( asJob + uiSwap );
            }
        }
    /*# defined(TgBUILD_OS__WINDOWS) */
    #endif

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
                tgKN_GPU_EXT__WORK__Frame_End( atiCXT_WORK[uiSwap] );
                atiCXT_WORK[uiSwap].m_uiKI = 0;
            }
        }

        /* Finish measuring the time used for this frame (all windows / swap chains). */
        tgGB_Update( afFrame_Elapsed_Time[nuiFrame_Elapsed_Time % 31] );
        tgIN_Update__Client( afFrame_Elapsed_Time[nuiFrame_Elapsed_Time % 31] );

        if (!bAll_Windows_Closed)
        {
            TgUN_V128                           uPos_N;

            tgFX_Module_Update( afFrame_Elapsed_Time[nuiFrame_Elapsed_Time % 31] );

            TgSTD_ATOMIC(store)( &sSE_Context.m_xnuiFrame_Mesh, 0 );
            TgSTD_ATOMIC(store)( sSE_Context.m_asView[0].m_axnuiFrame_Mesh_Inst + ETgSE_DRAW_TYPE__OPAQUE, 0 );
            TgSTD_ATOMIC(store)( sSE_Context.m_asView[0].m_axnuiFrame_Mesh_Inst + ETgSE_DRAW_TYPE__TRANSPARENT, 0 );

            TgSTD_ATOMIC(store)( &g_sRN_Output.m_xnuiFX_Header, 0 );
            g_sRN_Output.m_nbyUsed = 0;
            g_sRN_Output.m_nbyFree = KTgRN_MAX_PRTCL_BUFFER_SIZE;

            tgFX__Client__Update_1( afFrame_Elapsed_Time[nuiFrame_Elapsed_Time % 31] );
            tgFX__Client__Update_2( afFrame_Elapsed_Time[nuiFrame_Elapsed_Time % 31] );

                uPos_N.m_vF32_04_1 = KTgZERO_F32_04_1;
                tgPM_SINCOS_F32( &uPos_N.m_vS_F32_04_1.x, &uPos_N.m_vS_F32_04_1.z, KTgPI_F32 * tgTM_Query_Time() * 0.001F );
                uPos_N.m_vS_F32_04_1.x *= 5.0F;
                uPos_N.m_vS_F32_04_1.y = 5.0F;
                uPos_N.m_vS_F32_04_1.z *= 5.0F;
            tgFX__Client__Set_Position_From_External_Update( tiTrail, uPos_N.m_vF32_04_1 );
            tgFX__Client__Update_Finish();
            /* Normally called by Set Update (triggered by Rendering) */ tgFX__Client__Scene_Cull( &sSE_Context, 0 );

            tgMM_Set_U08_0x00( g_sRN_Output.m_psFX_Header, sizeof( STg2_RN_Particle_Header ) * KTgFX_MAX_RENDER_INSTANCE );
            tgMM_Set_U08_0x00( g_sRN_Output.m_puiBuffer, KTgRN_MAX_PRTCL_BUFFER_SIZE );
            /* Normally called by Render */ tgFX__Render__Update( &g_sRN_Output );
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

        //tgTR_Sleep( 7000000 );

    };


    /* Clean out all memory allocations by the FX system. */
    tgFX__Client__Kill_All( nullptr );
    tgFX_Module_Update( 0.0F );
    tgFX__Client__Update_1( 0.0F );
    tgFX__Client__Update_2( 0.0F );
    tgFX__Client__Update_Finish();

    for (uiSwap = 0; uiSwap < s_sSelect.m_nuiOutput; ++uiSwap)
    {
        Test__Expect_EQ( KTgS_OK, tgUnit_Test__FX__Release_Resources( uJob_Data[uiSwap].ps->m_tiCXT_EXEC, uJob_Data[uiSwap].ps->m_tiCXT_SWAP ));
    };

    tgKN_GPU_Contexts__Free();

    TgFREE_POOL(g_pbyFX_Trail_Test);
    TgFREE_POOL(g_pbyFX_Particle_Test);
    TgFREE_POOL(g_pbyFX_Emitter_Test);
    TgFREE_POOL(g_pbyFX_Beam_Test);
    TgFREE_POOL(g_pbyFX_Billboard_Test);

    tgIN_Remove_Consumer( tiIN_GamePad );
    tiIN_GamePad.m_uiKI = KTgID__INVALID_VALUE;
    tgIN_Update__Client( 0.0F );

    TgFREE_POOL( g_sRN_Output.m_puiBuffer  );
    TgFREE_POOL( g_sRN_Output.m_psFX_Header  );
    TgFREE_POOL( g_sRN_Output.m_puiContext_To_Particle_Header_Index  );

    TgFREE_POOL( sSE_Context.m_asFrame_Mesh  );
    TgFREE_POOL( sSE_Context.m_asView[0].m_apuiFrame_Mesh_Inst[ETgSE_DRAW_TYPE__OPAQUE]  );
    TgFREE_POOL( sSE_Context.m_asView[0].m_apuiFrame_Mesh_Inst[ETgSE_DRAW_TYPE__TRANSPARENT]  );

/*# defined(TgBUILD_FEATURE__GRAPHICS) */
#endif

    TEST_END_METHOD( KTgS_OK );
}


/* ---- tgUnit_Test__FX__Setup_Scene_Constant_Buffer ----------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if defined(TgBUILD_FEATURE__GRAPHICS)
TgVOID tgUnit_Test__FX__Setup_Scene_Constant_Buffer( STg2_KN_GPU_Render_Buffer_CPCU psRTBuffer )
{
    TgFLOAT32_C                         fAspect_Ratio = (float)psRTBuffer->m_uiWidth / (float)psRTBuffer->m_uiHeight;
    TgFLOAT32_C                         fFoV = 35.0F * KTgPI_F32 / 180.0f;

    TgVEC_S_F32_04_1                    vEye, vAt, vUp;
    TgFLOAT32                           fCosTheta, fSinTheta, fCosPhi, fSinPhi;
    TgVEC_S_F32_04_4                    mS2C;

    tgMH_PProj_FoVLH_S_F32_04_4( &g_sSceneConstantBuffer.m_avC2S, fFoV, fAspect_Ratio, 0.01F, 1000.0F );
    tgMM_Copy( &g_sCamera.m_sCamera_Shared.m_avC2S, sizeof(g_sCamera.m_sCamera_Shared.m_avC2S), &g_sSceneConstantBuffer.m_avC2S, sizeof(g_sSceneConstantBuffer.m_avC2S) );
    tgMH_INV_S_F32_04_4( &mS2C, &g_sSceneConstantBuffer.m_avC2S );
    tgMM_Copy( &g_sCamera.m_sCamera_Shared.m_avS2C, sizeof(g_sCamera.m_sCamera_Shared.m_avS2C), &mS2C, sizeof(mS2C) );

    if (fAspect_Ratio < 1.0F)
    {
        TgFLOAT32_C                         fSwap = g_sSceneConstantBuffer.m_avC2S._11;

        g_sSceneConstantBuffer.m_avC2S._11 = g_sSceneConstantBuffer.m_avC2S._22 / fAspect_Ratio;
        g_sSceneConstantBuffer.m_avC2S._22 = fSwap * fAspect_Ratio;
    }

    tgPM_SINCOS_F32( &fSinTheta, &fCosTheta, s_fTheta[0] );
    tgPM_SINCOS_F32( &fSinPhi, &fCosPhi, s_fPhi[0] );

    vEye = tgMH_Init_Point_ELEM_S_F32_04_1( fCosTheta * fCosPhi * s_fCam_Dist_Max[0],
                                            fSinPhi * s_fCam_Dist_Max[0],
                                            fSinTheta * fCosPhi * s_fCam_Dist_Max[0] );

    vAt = tgMH_Init_Point_ELEM_S_F32_04_1( 0.0F, 0.0f, 0.0F );
    vUp = tgMH_Init_Vector_ELEM_S_F32_04_1( 0.0f, 1.0f, 0.0f );

    tgMH_LookLH_S_F32_04_4( &g_sSceneConstantBuffer.m_avW2C, vEye, vAt, vUp );
    tgMM_Copy( &g_sCamera.m_sCamera_Shared.m_avW2C, sizeof(g_sCamera.m_sCamera_Shared.m_avW2C), &g_sSceneConstantBuffer.m_avW2C, sizeof(g_sSceneConstantBuffer.m_avW2C) );

    g_sCamera.m_sConfiguration.m_uCamera_Position.m_vS_F32_04_1 = vEye;

    g_sCamera.m_sCamera_Shared.m_vCam_Forward = tgMH_Init_Vector_F32_04_1( g_sCamera.m_sCamera_Shared.m_avW2C.m_vC2 );
    g_sCamera.m_sCamera_Shared.m_vCam_Right = tgMH_Init_Vector_F32_04_1( g_sCamera.m_sCamera_Shared.m_avW2C.m_vC0 );
    g_sCamera.m_sCamera_Shared.m_vCam_Up = tgMH_Init_Vector_F32_04_1( g_sCamera.m_sCamera_Shared.m_avW2C.m_vC1 );

    if (1 == s_iCamera_Select)
    {
        tgPM_SINCOS_F32( &fSinTheta, &fCosTheta, s_fTheta[1] );
        tgPM_SINCOS_F32( &fSinPhi, &fCosPhi, s_fPhi[1] );

        vEye = tgMH_Init_Point_ELEM_S_F32_04_1( fCosTheta * fCosPhi * s_fCam_Dist_Max[1],
                                                fSinPhi * s_fCam_Dist_Max[1],
                                                fSinTheta * fCosPhi * s_fCam_Dist_Max[1] );

        vAt = tgMH_Init_Point_ELEM_S_F32_04_1( 0.0F, 0.0f, 0.0F );
        vUp = tgMH_Init_Vector_ELEM_S_F32_04_1( 0.0f, 1.0f, 0.0f );

        tgMH_LookLH_S_F32_04_4( &g_sSceneConstantBuffer.m_avW2C, vEye, vAt, vUp );
    }
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
    if (ETgCONTROLLER_GAMEPAD_0 != psIN_Event->m_enController)
        return (false);

    TgWARN_DISABLE_PUSH(4061 4062,switch-enum)
    switch (psIN_Event->m_enProp.GamePad) {
    case ETgPROP_GAMEPAD__A:
        s_iCamera_Select = 1;
        s_fTheta[1] = s_fTheta[0];
        s_fPhi[1] = s_fPhi[0];
        s_fCam_Dist_Max[1] = s_fCam_Dist_Max[0];
        break;
    case ETgPROP_GAMEPAD__B:
        s_iCamera_Select = 0;
        break;
    case ETgPROP_GAMEPAD__X:
    {
        STg2_FX_Instance                    sInstance;

        tgMM_Set_U08_0x00( &sInstance, sizeof( sInstance ) );
        sInstance.m_vPos_N2W = tgMH_Init_ELEM_F32_04_1( -5.0F, 0.0F, -5.0F, 1.0F );
        sInstance.m_qRot_N2W = KTgUNIT_W_F32_04_1;
        sInstance.m_vScale = tgMH_SET1_F32_04_1( 1.0F );
        tgFX__Client__Inst_FX_RAW( ETgFX__BEAM, g_pbyFX_Beam_Test, nullptr, &sInstance, false );
        break;
    }
    case ETgPROP_GAMEPAD__LTHUMB_X:
        s_fTheta[s_iCamera_Select] = tgPM_FMOD_F32( s_fTheta[s_iCamera_Select] + psIN_Event->m_fValue * 0.0025F, KTgTWO_PI_F32 );
        break;
    case ETgPROP_GAMEPAD__LTHUMB_Y:
        s_fPhi[s_iCamera_Select] = tgCM_CLP_F32( s_fPhi[s_iCamera_Select] + psIN_Event->m_fValue * 0.0005F, KTgPI_F32 / 16.0F, KTgPI_F32 * 7.0F / 16.0F );
        break;
    case ETgPROP_GAMEPAD__RTHUMB_Y:
        s_fCam_Dist_Max[s_iCamera_Select] = tgCM_CLP_F32( s_fCam_Dist_Max[s_iCamera_Select] - psIN_Event->m_fValue * 0.05F, 5.0F, 150.0F );
        break;
    default:
        break;
    };
    TgWARN_DISABLE_POP()
    return (true);
}
/*# defined(TgBUILD_FEATURE__GRAPHICS) && defined(TgBUILD_OS__WINDOWS) */
#endif


/* ---- tgUnit_Test__FX__Init_Billboard ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if defined(TgBUILD_FEATURE__GRAPHICS)
static TgVOID tgUnit_Test__FX__Init_Billboard( TgUINT_E08_P pbyFX_Buffer )
{
    TgUINT_PTR                          uiBuffer;
    STg2_FX_Billboard__File_Data_P      psFX_Effect__Test__Billboard;
    UTg2_FX_AnimData                    uAnimData;

    psFX_Effect__Test__Billboard = (STg2_FX_Billboard__File_Data_P)pbyFX_Buffer;
    uiBuffer = (TgUINT_PTR)pbyFX_Buffer + sizeof( STg2_FX_Billboard__File_Data );

    // Spawn Data
    psFX_Effect__Test__Billboard->m_fTime_Total_MID = 32.0F;
    psFX_Effect__Test__Billboard->m_fTime_Total_RNG = 5.0F;
    psFX_Effect__Test__Billboard->m_fTime_Start_End_MID = 4.0F;
    psFX_Effect__Test__Billboard->m_fTime_Start_End_RNG = 2.0F;
    psFX_Effect__Test__Billboard->m_fTime_End_Start_MID = -1.0F;
    psFX_Effect__Test__Billboard->m_fTime_End_Start_RNG = 0.0F;
    psFX_Effect__Test__Billboard->m_uiHash_Material = 0;

    psFX_Effect__Test__Billboard->m_vPivot_X = tgMH_SET1_F32_04_1( 0.5F );
    psFX_Effect__Test__Billboard->m_vPivot_Y = tgMH_SET1_F32_04_1( 0.2F );
    psFX_Effect__Test__Billboard->m_vPlnX = tgMH_Init_ELEM_F32_04_1( 1.0F, 0.0F, 1.0F, 0.0F );
    psFX_Effect__Test__Billboard->m_vPlnY = tgMH_Init_ELEM_F32_04_1( 0.0F, 1.0F, 0.0F, 1.0F );
    psFX_Effect__Test__Billboard->m_vPlnZ = tgMH_Init_ELEM_F32_04_1( 0.0F, 1.0F, 0.0F, 1.0F );
    psFX_Effect__Test__Billboard->m_vFade_Start = tgMH_Init_ELEM_F32_04_1( 0.0F, 1.0F, 0.0F, 1.0F );
    psFX_Effect__Test__Billboard->m_vFade_RNG = tgMH_Init_ELEM_F32_04_1( 0.0F, 1.0F, 0.0F, 1.0F );
    psFX_Effect__Test__Billboard->m_fSpin_MID = 0.0F;
    psFX_Effect__Test__Billboard->m_fSpin_RNG = 0.0F;
    psFX_Effect__Test__Billboard->m_fSpin_Speed = 0.001F;

    // Fixed Data
    psFX_Effect__Test__Billboard->m_enOrientation = ETgFX_BILLBOARD_ORIENTATION__CAMERA_FACE_SPHERE__FIXED_Y;
    psFX_Effect__Test__Billboard->m_uiFlags = 0;
    psFX_Effect__Test__Billboard->m_uiSort_Order = 0;

    // Animation Data
    psFX_Effect__Test__Billboard->m_nbyData = 2 * sizeof( STg2_FX_AnimData__Constant_F32_04 );

    uAnimData.psAnimData = (STg2_FX_AnimData_P)uiBuffer;
    uiBuffer += sizeof( STg2_FX_AnimData__Constant_F32_04 );

    psFX_Effect__Test__Billboard->m_sAnim.m_sParameter.m_psColour = uAnimData.psAnimData;
    uAnimData.psConstant_F32_04->m_sParam.m_enType = ETgFX_ANIM_DATA__CONSTANT_F32_04;
    uAnimData.psConstant_F32_04->m_sParam.m_uiSize = sizeof( STg2_FX_AnimData__Constant_F32_04 );
    uAnimData.psConstant_F32_04->m_vParam = tgMH_Init_ELEM_F32_04_1( 1.0F, 1.0F, 0.0F, 0.5F );

    uAnimData.psAnimData = (STg2_FX_AnimData_P)uiBuffer;
    uiBuffer += sizeof( STg2_FX_AnimData__Constant_F32_04 );

    psFX_Effect__Test__Billboard->m_sAnim.m_sParameter.m_psSize = uAnimData.psAnimData;
    uAnimData.psConstant_F32_04->m_sParam.m_enType = ETgFX_ANIM_DATA__CONSTANT_F32_04;
    uAnimData.psConstant_F32_04->m_sParam.m_uiSize = sizeof( STg2_FX_AnimData__Constant_F32_04 );
    uAnimData.psConstant_F32_04->m_vParam = tgMH_SET1_F32_04_1( 1.0F );
}
/*# defined(TgBUILD_FEATURE__GRAPHICS) */
#endif


/* ---- tgUnit_Test__FX__Init_Beam ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if defined(TgBUILD_FEATURE__GRAPHICS)
static TgVOID tgUnit_Test__FX__Init_Beam( TgUINT_E08_P pbyFX_Buffer )
{
    TgUINT_PTR                          uiBuffer;
    STg2_FX_Beam__File_Data_P           psFX_Effect__Test__Beam;
    UTg2_FX_AnimData                    uAnimData;
    TgRSIZE                             uiIndex;

    psFX_Effect__Test__Beam = (STg2_FX_Beam__File_Data_P)pbyFX_Buffer;
    uiBuffer = (TgUINT_PTR)pbyFX_Buffer + sizeof( STg2_FX_Beam__File_Data );

    // Spawn Data
    psFX_Effect__Test__Beam->m_fTime_Total_MID = 32000.0F;
    psFX_Effect__Test__Beam->m_fTime_Total_RNG = 5000.0F;
    psFX_Effect__Test__Beam->m_fTime_Start_End_MID = 4000.0F;
    psFX_Effect__Test__Beam->m_fTime_Start_End_RNG = 2000.0F;
    psFX_Effect__Test__Beam->m_fTime_End_Start_MID = 5000.0F;
    psFX_Effect__Test__Beam->m_fTime_End_Start_RNG = 3000.0F;
    psFX_Effect__Test__Beam->m_uiHash_Material = 0;
    psFX_Effect__Test__Beam->m_vEnd_Position_MID = tgMH_Init_ELEM_F32_04_1( 1.0F, 0.0F, 1.0F, 0.0F );
    psFX_Effect__Test__Beam->m_vEnd_Position_RNG = tgMH_Init_ELEM_F32_04_1( 10.0F, 0.0F, 10.0F, 0.0F );
    psFX_Effect__Test__Beam->m_vScale_U = tgMH_Init_ELEM_F32_04_1( 1.0F, 0.0F, 1.0F, 0.0F );
    psFX_Effect__Test__Beam->m_vScale_V = tgMH_Init_ELEM_F32_04_1( 0.0F, 1.0F, 0.0F, 1.0F );

    // Fixed Data
    psFX_Effect__Test__Beam->m_uiSort_Order = 0;

    // Shape Data
    psFX_Effect__Test__Beam->m_nuiPoints = 10;

    psFX_Effect__Test__Beam->m_sShape.m_sData.m_pvShape_Colour = (TgVEC_F32_04_1_P)((uiBuffer+15ULL) & ~15ULL);
    uiBuffer += (((uiBuffer+15ULL) & ~15ULL) - uiBuffer) + psFX_Effect__Test__Beam->m_nuiPoints * sizeof( TgVEC_F32_04_1 );
    psFX_Effect__Test__Beam->m_sShape.m_sData.m_pvShape_Offset = (TgVEC_F32_04_1_P)((uiBuffer+15ULL) & ~15ULL);
    uiBuffer += (((uiBuffer+15ULL) & ~15ULL) - uiBuffer) + psFX_Effect__Test__Beam->m_nuiPoints * sizeof( TgVEC_F32_04_1 );
    psFX_Effect__Test__Beam->m_sShape.m_sData.m_pfShape_Width = (TgFLOAT32_P)uiBuffer;
    uiBuffer += psFX_Effect__Test__Beam->m_nuiPoints * sizeof( TgFLOAT32 );
    psFX_Effect__Test__Beam->m_sShape.m_sData.m_pfShape_Fraction = (TgFLOAT32_P)uiBuffer;
    uiBuffer += psFX_Effect__Test__Beam->m_nuiPoints * sizeof( TgFLOAT32 );
    psFX_Effect__Test__Beam->m_sShape.m_sData.m_pfShape_Normalized_T = (TgFLOAT32_P)uiBuffer;
    uiBuffer += psFX_Effect__Test__Beam->m_nuiPoints * sizeof( TgFLOAT32 );

    psFX_Effect__Test__Beam->m_sShape.m_sData.m_pvShape_Colour[0] = tgMH_Init_ELEM_F32_04_1( 1.0F, 0.0F, 0.0F, 1.0F );
    psFX_Effect__Test__Beam->m_sShape.m_sData.m_pvShape_Offset[0] = KTgZERO_F32_04_1;
    psFX_Effect__Test__Beam->m_sShape.m_sData.m_pfShape_Width[0]  = 0.1F;
    psFX_Effect__Test__Beam->m_sShape.m_sData.m_pfShape_Fraction[0]  = 0.0F;
    psFX_Effect__Test__Beam->m_sShape.m_sData.m_pfShape_Normalized_T[0] = 0.0F;

    for (uiIndex = 1; uiIndex < psFX_Effect__Test__Beam->m_nuiPoints; ++uiIndex)
    {
        psFX_Effect__Test__Beam->m_sShape.m_sData.m_pvShape_Colour[uiIndex] = tgMH_Init_ELEM_F32_04_1( 1.0F, 0.0F, 0.0F, 1.0F );
        psFX_Effect__Test__Beam->m_sShape.m_sData.m_pvShape_Offset[uiIndex] = tgMH_SET1_F32_04_1( 0.0F );
        psFX_Effect__Test__Beam->m_sShape.m_sData.m_pfShape_Width[uiIndex] = 0.1F + (TgFLOAT32)uiIndex / (TgFLOAT32)(psFX_Effect__Test__Beam->m_nuiPoints - 1u);
        psFX_Effect__Test__Beam->m_sShape.m_sData.m_pfShape_Fraction[uiIndex] = (TgFLOAT32)uiIndex / (TgFLOAT32)(psFX_Effect__Test__Beam->m_nuiPoints - 1u);
        psFX_Effect__Test__Beam->m_sShape.m_sData.m_pfShape_Normalized_T[uiIndex] = (TgFLOAT32)uiIndex / (TgFLOAT32)(psFX_Effect__Test__Beam->m_nuiPoints - 1u);
    }


    // Animation Data
    psFX_Effect__Test__Beam->m_nbyData = sizeof( STg2_FX_AnimData__Constant_F32_04 ) + sizeof( STg2_FX_AnimData__Key_Frame_F32_04 ) + 60 * sizeof(TgFLOAT32);

    uAnimData.psAnimData = (STg2_FX_AnimData_P)uiBuffer;
    uiBuffer += sizeof( STg2_FX_AnimData__Constant_F32_04 );

    psFX_Effect__Test__Beam->m_sAnim.m_sParameter.m_psEnd_Position = uAnimData.psAnimData;
    uAnimData.psConstant_F32_04->m_sParam.m_enType = ETgFX_ANIM_DATA__CONSTANT_F32_04;
    uAnimData.psConstant_F32_04->m_sParam.m_uiSize = sizeof( STg2_FX_AnimData__Constant_F32_04 );
    uAnimData.psConstant_F32_04->m_vParam = tgMH_Init_ELEM_F32_04_1( -10.F, 1.F, 10.F, 1.0F );;

    uAnimData.psAnimData = (STg2_FX_AnimData_P)uiBuffer;
    uiBuffer += sizeof( STg2_FX_AnimData__Key_Frame_F32_02 );

    psFX_Effect__Test__Beam->m_sAnim.m_sParameter.m_psSG0_SG1 = uAnimData.psAnimData;
    uAnimData.psKey_Frame->m_sParam.m_enType = ETgFX_ANIM_DATA__KEY_FRAME_F32_02;
    uAnimData.psKey_Frame->m_sParam.m_uiSize = sizeof( STg2_FX_AnimData__Key_Frame_F32_02 );
    uAnimData.psKey_Frame->m_nuiKey_Frame = 20;
    uAnimData.psKey_Frame->m_pfTime = (TgFLOAT32_P)uiBuffer;
    uiBuffer += 20 * sizeof( TgFLOAT32 );

    uAnimData.psKey_Frame_F32_02->m_pfVal = (TgFLOAT32_P)uiBuffer;
    uiBuffer += 40 * sizeof( TgFLOAT32 );

    for (uiIndex = 0; uiIndex < uAnimData.psKey_Frame->m_nuiKey_Frame; ++uiIndex)
    {
        TgFLOAT32_C                         fFraction = tgCM_MAX_F32( 0.0F, (float)uiIndex / (float)(uAnimData.psKey_Frame->m_nuiKey_Frame-1) );

        uAnimData.psKey_Frame_F32_02->m_pfVal[uiIndex*2 + 0] = fFraction;
        uAnimData.psKey_Frame_F32_02->m_pfVal[uiIndex*2 + 1] = tgCM_MIN_F32( 1.0F, 0.05F + fFraction );
        uAnimData.psKey_Frame->m_pfTime[uiIndex] = fFraction;
    }
}
/*# defined(TgBUILD_FEATURE__GRAPHICS) */
#endif


/* ---- tgUnit_Test__FX__Init_Emitter -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if defined(TgBUILD_FEATURE__GRAPHICS)
static TgVOID tgUnit_Test__FX__Init_Emitter( TgUINT_E08_P pbyFX_Buffer )
{
    TgUINT_PTR                          uiBuffer;
    STg2_FX_Emitter__File_Data_P        psFX_Effect__Test__Emitter;
    UTg2_FX_AnimData                    uAnimData;

    psFX_Effect__Test__Emitter = (STg2_FX_Emitter__File_Data_P)pbyFX_Buffer;
    uiBuffer = (TgUINT_PTR)pbyFX_Buffer + sizeof( STg2_FX_Emitter__File_Data );

    // Spawn Data
    psFX_Effect__Test__Emitter->m_fTime_Total_MID = 32000.0F;
    psFX_Effect__Test__Emitter->m_fTime_Total_RNG = 5000.0F;
    psFX_Effect__Test__Emitter->m_fTime_Start_End_MID = 4000.0F;
    psFX_Effect__Test__Emitter->m_fTime_Start_End_RNG = 2000.0F;
    psFX_Effect__Test__Emitter->m_fTime_End_Start_MID = -1.0F;
    psFX_Effect__Test__Emitter->m_fTime_End_Start_RNG = 0.0F;
    psFX_Effect__Test__Emitter->m_uiHash_Material = 0;
    psFX_Effect__Test__Emitter->m_fEmission_Pivot_X = 0.0F;
    psFX_Effect__Test__Emitter->m_fEmission_Pivot_Y = 0.0F;
    psFX_Effect__Test__Emitter->m_anuiEmission_Max_Particle[0] = 1000;
    psFX_Effect__Test__Emitter->m_anuiEmission_Max_Particle[1] = 4000;
    psFX_Effect__Test__Emitter->m_afEmission_Interval_MID[0] = 72.F;
    psFX_Effect__Test__Emitter->m_afEmission_Interval_MID[1] = 72.F;
    psFX_Effect__Test__Emitter->m_afEmission_Interval_RNG[0] = 0.0F;
    psFX_Effect__Test__Emitter->m_afEmission_Interval_RNG[1] = 0.0F;
    psFX_Effect__Test__Emitter->m_afEmission_Quantity_MID[0] = 11.1F;
    psFX_Effect__Test__Emitter->m_afEmission_Quantity_MID[1] = 11.1F;
    psFX_Effect__Test__Emitter->m_afEmission_Quantity_RNG[0] = 0.0F;
    psFX_Effect__Test__Emitter->m_afEmission_Quantity_RNG[1] = 0.0F;
    
    // Fixed Data
    psFX_Effect__Test__Emitter->m_vL_Vel_Acceleration_W = tgMH_Init_ELEM_F32_04_1( 0.F, 0.F, 0.F, 0.F );
    psFX_Effect__Test__Emitter->m_enEmission_Shape = ETgFX_EMISSION_SHAPE__CIRCLE;
    psFX_Effect__Test__Emitter->m_fEmitter_Attraction = 0.0F;
    psFX_Effect__Test__Emitter->m_uiFlags = 0;
    psFX_Effect__Test__Emitter->m_uiSort_Order = 0;

    // Animation Data
    psFX_Effect__Test__Emitter->m_nbyData = 3 * sizeof( STg2_FX_AnimData__Constant_F32_04 );

    uAnimData.psAnimData = (STg2_FX_AnimData_P)uiBuffer;
    uiBuffer += sizeof( STg2_FX_AnimData__Constant_F32_04 );

    psFX_Effect__Test__Emitter->m_sAnim.m_sParameter.m_psEmitter_LVel_N = uAnimData.psAnimData;
    uAnimData.psConstant_F32_04->m_sParam.m_enType = ETgFX_ANIM_DATA__CONSTANT_F32_04;
    uAnimData.psConstant_F32_04->m_sParam.m_uiSize = sizeof( STg2_FX_AnimData__Constant_F32_04 );
    uAnimData.psConstant_F32_04->m_vParam = tgMH_Init_ELEM_F32_04_1( 0.F, 0.F, 0.F, 0.F );

    uAnimData.psAnimData = (STg2_FX_AnimData_P)uiBuffer;
    uiBuffer += sizeof( STg2_FX_AnimData__Constant_F32_04 );

    psFX_Effect__Test__Emitter->m_sAnim.m_sParameter.m_psEmitter_Rot_N = uAnimData.psAnimData;
    uAnimData.psConstant_F32_04->m_sParam.m_enType = ETgFX_ANIM_DATA__CONSTANT_F32_04;
    uAnimData.psConstant_F32_04->m_sParam.m_uiSize = sizeof( STg2_FX_AnimData__Constant_F32_04 );
    uAnimData.psConstant_F32_04->m_vParam = tgMH_Init_ELEM_F32_04_1( 0.F, 0.F, 0.F, 1.F );

    uAnimData.psAnimData = (STg2_FX_AnimData_P)uiBuffer;
    uiBuffer += sizeof( STg2_FX_AnimData__Constant_F32_04 );

    psFX_Effect__Test__Emitter->m_sAnim.m_sParameter.m_psEmission_Shape = uAnimData.psAnimData;
    uAnimData.psConstant_F32_04->m_sParam.m_enType = ETgFX_ANIM_DATA__CONSTANT_F32_04;
    uAnimData.psConstant_F32_04->m_sParam.m_uiSize = sizeof( STg2_FX_AnimData__Constant_F32_04 );
    uAnimData.psConstant_F32_04->m_vParam = tgMH_Init_ELEM_F32_04_1( 1.F, 1.F, 1.F, 0.F );
}
/*# defined(TgBUILD_FEATURE__GRAPHICS) */
#endif


/* ---- tgUnit_Test__FX__Init_Particle ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if defined(TgBUILD_FEATURE__GRAPHICS)
static TgVOID tgUnit_Test__FX__Init_Particle( TgUINT_E08_P pbyFX_Buffer )
{
    TgUINT_PTR                          uiBuffer;
    STg2_FX_Particle__File_Data_P       psFX_Effect__Test__Particle;
    UTg2_FX_AnimData                    uAnimData;

    psFX_Effect__Test__Particle = (STg2_FX_Particle__File_Data_P)pbyFX_Buffer;
    uiBuffer = (TgUINT_PTR)pbyFX_Buffer + sizeof( STg2_FX_Particle__File_Data );

    // Spawn Data
    psFX_Effect__Test__Particle->m_vPivot_X = tgMH_SET1_F32_04_1( 0.0F );
    psFX_Effect__Test__Particle->m_vPivot_Y = tgMH_SET1_F32_04_1( 0.0F );
    psFX_Effect__Test__Particle->m_vL_Vel_Acceleration_W = tgMH_Init_ELEM_F32_04_1( 0.F, -0.0000981F, 0.F, 0.F );
    psFX_Effect__Test__Particle->m_vLVel_Variance_MID = tgMH_Init_ELEM_F32_04_1( 0.F, 0.F, 0.F, 0.F );
    psFX_Effect__Test__Particle->m_vLVel_Variance_RNG = tgMH_Init_ELEM_F32_04_1( 0.F, 0.F, 0.F, 0.F );
    psFX_Effect__Test__Particle->m_vRot_Variance_MID = tgMH_SET1_F32_04_1( 0.0F );
    psFX_Effect__Test__Particle->m_vRot_Variance_RNG = tgMH_SET1_F32_04_1( 0.0F );
    psFX_Effect__Test__Particle->m_vSize_Variance_MID = tgMH_Init_ELEM_F32_04_1( 0.1F, 0.1F, 0.F, 0.F );
    psFX_Effect__Test__Particle->m_vSize_Variance_RNG = tgMH_Init_ELEM_F32_04_1( 0.05F, 0.05F, 0.F, 0.F );
    psFX_Effect__Test__Particle->m_vRVel_Acceleration_MID = tgMH_SET1_F32_04_1( 0.0F );
    psFX_Effect__Test__Particle->m_vRVel_Acceleration_RNG = tgMH_SET1_F32_04_1( 0.0F );
    psFX_Effect__Test__Particle->m_fTime_MID = 1000.0F;
    psFX_Effect__Test__Particle->m_fTime_RNG = 0000.0F;
    psFX_Effect__Test__Particle->m_fContact_Restitution_MID = 0.0F;
    psFX_Effect__Test__Particle->m_fContact_Restitution_RNG = 0.0F;
    
    // Fixed Data
    psFX_Effect__Test__Particle->m_enOrientation = ETgFX_PARTICLE_ORIENTATION__CAMERA_FACE_SPHERE;
    psFX_Effect__Test__Particle->m_uiCollision_New_Effect_Hash = 0;

    // Animation Data
    psFX_Effect__Test__Particle->m_nbyData = 7 * sizeof( STg2_FX_AnimData__Constant_F32_04 ) + sizeof( STg2_FX_AnimData__Constant_UXX );

    uAnimData.psAnimData = (STg2_FX_AnimData_P)uiBuffer;
    uiBuffer += sizeof( STg2_FX_AnimData__Constant_F32_04 );

    psFX_Effect__Test__Particle->m_sAnim.m_sParameter.m_psPos_N = uAnimData.psAnimData;
    uAnimData.psConstant_F32_04->m_sParam.m_enType = ETgFX_ANIM_DATA__CONSTANT_F32_04;
    uAnimData.psConstant_F32_04->m_sParam.m_uiSize = sizeof( STg2_FX_AnimData__Constant_F32_04 );
    uAnimData.psConstant_F32_04->m_vParam = tgMH_Init_ELEM_F32_04_1( -10.F, 5.F, 10.F, 0.F );
    psFX_Effect__Test__Particle->m_sAnim.m_sParameter.m_psPos_N = nullptr;

    uAnimData.psAnimData = (STg2_FX_AnimData_P)uiBuffer;
    uiBuffer += sizeof( STg2_FX_AnimData__Constant_F32_04 );

    psFX_Effect__Test__Particle->m_sAnim.m_sParameter.m_psRot_N = uAnimData.psAnimData;
    uAnimData.psConstant_F32_04->m_sParam.m_enType = ETgFX_ANIM_DATA__CONSTANT_F32_04;
    uAnimData.psConstant_F32_04->m_sParam.m_uiSize = sizeof( STg2_FX_AnimData__Constant_F32_04 );
    uAnimData.psConstant_F32_04->m_vParam = tgMH_Init_ELEM_F32_04_1( 0.F, 0.F, 0.F, 1.F );
    psFX_Effect__Test__Particle->m_sAnim.m_sParameter.m_psRot_N = nullptr;

    uAnimData.psAnimData = (STg2_FX_AnimData_P)uiBuffer;
    uiBuffer += sizeof( STg2_FX_AnimData__Constant_F32_04 );

    psFX_Effect__Test__Particle->m_sAnim.m_sParameter.m_psLVel_N = uAnimData.psAnimData;
    uAnimData.psConstant_F32_04->m_sParam.m_enType = ETgFX_ANIM_DATA__CONSTANT_F32_04;
    uAnimData.psConstant_F32_04->m_sParam.m_uiSize = sizeof( STg2_FX_AnimData__Constant_F32_04 );
    uAnimData.psConstant_F32_04->m_vParam = tgMH_SET1_F32_04_1( 0.001F );

    uAnimData.psAnimData = (STg2_FX_AnimData_P)uiBuffer;
    uiBuffer += sizeof( STg2_FX_AnimData__Constant_F32_04 );

    psFX_Effect__Test__Particle->m_sAnim.m_sParameter.m_psSpin = uAnimData.psAnimData;
    uAnimData.psConstant_F32_04->m_sParam.m_enType = ETgFX_ANIM_DATA__CONSTANT_F32_04;
    uAnimData.psConstant_F32_04->m_sParam.m_uiSize = sizeof( STg2_FX_AnimData__Constant_F32_04 );
    uAnimData.psConstant_F32_04->m_vParam = tgMH_Init_ELEM_F32_04_1( 0.F, 0.F, 0.F, 1.F );

    uAnimData.psAnimData = (STg2_FX_AnimData_P)uiBuffer;
    uiBuffer += sizeof( STg2_FX_AnimData__Constant_F32_04 );

    psFX_Effect__Test__Particle->m_sAnim.m_sParameter.m_psTurbulence = uAnimData.psAnimData;
    uAnimData.psConstant_F32_04->m_sParam.m_enType = ETgFX_ANIM_DATA__CONSTANT_F32_04;
    uAnimData.psConstant_F32_04->m_sParam.m_uiSize = sizeof( STg2_FX_AnimData__Constant_F32_04 );
    uAnimData.psConstant_F32_04->m_vParam = tgMH_Init_ELEM_F32_04_1( 0.F, 0.F, 0.F, 0.F );

    uAnimData.psAnimData = (STg2_FX_AnimData_P)uiBuffer;
    uiBuffer += sizeof( STg2_FX_AnimData__Constant_F32_04 );

    psFX_Effect__Test__Particle->m_sAnim.m_sParameter.m_psSize = uAnimData.psAnimData;
    uAnimData.psConstant_F32_04->m_sParam.m_enType = ETgFX_ANIM_DATA__CONSTANT_F32_04;
    uAnimData.psConstant_F32_04->m_sParam.m_uiSize = sizeof( STg2_FX_AnimData__Constant_F32_04 );
    uAnimData.psConstant_F32_04->m_vParam = tgMH_Init_ELEM_F32_04_1( 0.2F, 0.2F, 0.F, 0.F );

    uAnimData.psAnimData = (STg2_FX_AnimData_P)uiBuffer;
    uiBuffer += sizeof( STg2_FX_AnimData__Constant_F32_04 );

    psFX_Effect__Test__Particle->m_sAnim.m_sParameter.m_psColour = uAnimData.psAnimData;
    uAnimData.psConstant_F32_04->m_sParam.m_enType = ETgFX_ANIM_DATA__CONSTANT_F32_04;
    uAnimData.psConstant_F32_04->m_sParam.m_uiSize = sizeof( STg2_FX_AnimData__Constant_F32_04 );
    uAnimData.psConstant_F32_04->m_vParam = tgMH_Init_ELEM_F32_04_1( 0.5F, 0.5F, 0.F, 0.F );

    uAnimData.psAnimData = (STg2_FX_AnimData_P)uiBuffer;
    uiBuffer += sizeof( STg2_FX_AnimData__Constant_UXX );

    psFX_Effect__Test__Particle->m_sAnim.m_sParameter.m_psNew_Effect_Hash = uAnimData.psAnimData;
    uAnimData.psConstant_UXX->m_sParam.m_enType = ETgFX_ANIM_DATA__CONSTANT_UXX;
    uAnimData.psConstant_UXX->m_sParam.m_uiSize = sizeof( STg2_FX_AnimData__Constant_UXX );
    uAnimData.psConstant_UXX->m_uiVal = KTgEMPTY_HASH;
}
/*# defined(TgBUILD_FEATURE__GRAPHICS) */
#endif


/* ---- tgUnit_Test__FX__Init_Trail ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if defined(TgBUILD_FEATURE__GRAPHICS)
static TgVOID tgUnit_Test__FX__Init_Trail( TgUINT_E08_P pbyFX_Buffer )
{
    TgUINT_PTR                          uiBuffer;
    STg2_FX_Trail__File_Data_P          psFX_Effect__Test__Trail;
    UTg2_FX_AnimData                    uAnimData;

    psFX_Effect__Test__Trail = (STg2_FX_Trail__File_Data_P)pbyFX_Buffer;
    uiBuffer = (TgUINT_PTR)pbyFX_Buffer + sizeof( STg2_FX_Trail__File_Data );

    // Spawn Data
    psFX_Effect__Test__Trail->m_fTime_Total_MID = 32000.0F;
    psFX_Effect__Test__Trail->m_fTime_Total_RNG = 5000.0F;
    psFX_Effect__Test__Trail->m_fTime_Start_End_MID = 4000.0F;
    psFX_Effect__Test__Trail->m_fTime_Start_End_RNG = 2000.0F;
    psFX_Effect__Test__Trail->m_fTime_End_Start_MID = -1.0F;
    psFX_Effect__Test__Trail->m_fTime_End_Start_RNG = 0.0F;
    psFX_Effect__Test__Trail->m_uiHash_Material = 0;
    psFX_Effect__Test__Trail->m_vScale_U = tgMH_SET1_F32_04_1( 1.0F );
    psFX_Effect__Test__Trail->m_vScale_V = tgMH_SET1_F32_04_1( 1.0F );
    
    // Fixed Data
    psFX_Effect__Test__Trail->m_fFollow_Fraction = 1.0F;
    psFX_Effect__Test__Trail->m_nuiMax_Points = 80;
    psFX_Effect__Test__Trail->m_uiSort_Order = 0;
    psFX_Effect__Test__Trail->m_enTex = 0;

    // Animation Data
    psFX_Effect__Test__Trail->m_nbyData = 2 * sizeof( STg2_FX_AnimData__Constant_F32_04 );

    uAnimData.psAnimData = (STg2_FX_AnimData_P)uiBuffer;
    uiBuffer += sizeof( STg2_FX_AnimData__Constant_F32_04 );

    psFX_Effect__Test__Trail->m_sAnim.m_sParameter.m_psColour = uAnimData.psAnimData;
    uAnimData.psConstant_F32_04->m_sParam.m_enType = ETgFX_ANIM_DATA__CONSTANT_F32_04;
    uAnimData.psConstant_F32_04->m_sParam.m_uiSize = sizeof( STg2_FX_AnimData__Constant_F32_04 );
    uAnimData.psConstant_F32_04->m_vParam = tgMH_Init_ELEM_F32_04_1( 1.F, 1.F, 1.F, 1.F );

    uAnimData.psAnimData = (STg2_FX_AnimData_P)uiBuffer;
    uiBuffer += sizeof( STg2_FX_AnimData__Constant_F32_04 );

    psFX_Effect__Test__Trail->m_sAnim.m_sParameter.m_psWidth = uAnimData.psAnimData;
    uAnimData.psConstant_F32_04->m_sParam.m_enType = ETgFX_ANIM_DATA__CONSTANT_F32_04;
    uAnimData.psConstant_F32_04->m_sParam.m_uiSize = sizeof( STg2_FX_AnimData__Constant_F32_04 );
    uAnimData.psConstant_F32_04->m_vParam = tgMH_Init_ELEM_F32_04_1( 0.5F, 0.5F, 0.F, 0.F );
}
/*# defined(TgBUILD_FEATURE__GRAPHICS) */
#endif


TgCLANG_WARN_DISABLE_POP(unused-variable)
