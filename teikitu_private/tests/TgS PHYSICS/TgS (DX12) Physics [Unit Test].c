/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (DX12) Physics [Unit Test].c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */

#include "TgS KERNEL/TgS (DX12) Kernel [GPU].h"
#include "TgS KERNEL/TgS (DX12) Kernel [GPU] - Debug.inl"


/* ---- GPU - Unit Test ---------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgEXTN TgRESULT
tgUnit_Test__PH__Render(
    TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC, TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP, TgKN_GPU_CXT_WORK_ID tiCXT_WORK, TgRSIZE_C uiTest_Level );

TgEXTN TgVOID
tgUnit_Test__PH__Setup_Scene_Constant_Buffer(
    STg2_KN_GPU_Render_Buffer_CPCU psRTBuffer );

TgEXTN STg2_KN_GPU_Camera                   g_sCamera;




/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Types                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

#if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)
static STg2_KN_GPU_HLSL_CB_Debug_UI s_sUIConstantBuffer;
static STg2_KN_GPU_HLSL_CB_Debug_Model s_sModelConstantBuffer;
#endif




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgUnit_Test__PH__Render -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgUnit_Test__PH__Render( TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC, TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP, TgKN_GPU_CXT_WORK_ID tiCXT_WORK, TgRSIZE_C uiTest_Level )
{
    TgBOOL                              bEndFrame = false;

    UTg2_KN_GPU_CMD                     uCMD;
    STg2_KN_GPU_Render_Buffer           sRTBuffer, sDSBuffer;
    STg2_KN_GPU_HLSL_Output_DESC        sOutput_DESC;
    D3D12_CPU_DESCRIPTOR_HANDLE         shHeap_RTV;
    D3D12_CPU_DESCRIPTOR_HANDLE         shHeap_DSV;

    (void)uiTest_Level;

    if (KTgKN_GPU_CXT_WORK_ID__INVALID.m_uiKI == tiCXT_WORK.m_uiKI)
    {
        tiCXT_WORK = tgKN_GPU_EXT__Execute__Frame_Start( tiCXT_EXEC );
        bEndFrame = true;
    }
    uCMD = tgKN_GPU_EXT__Execute__Command_List_Acquire( tiCXT_WORK, (ETgKN_GPU_EXT_COMMAND)D3D12_COMMAND_LIST_TYPE_DIRECT );
    tgKN_GPU_EXT__CMD__Set_Graphics_Root_Signature_From_Default( uCMD, ETgKN_GPU_DEFAULT_ROOT_SIGNATURE_DEBUG );

    if (TgFAILED(tgKN_GPU_EXT__SwapChain__Get_Back_Buffer( &shHeap_RTV, &shHeap_DSV, &sOutput_DESC, tiCXT_SWAP )))
    {
        return (KTgE_FAIL);
    };
    tgKN_GPU__SwapChain__Get_Target_Buffers( &sRTBuffer, &sDSBuffer, tiCXT_SWAP );
    ID3D12GraphicsCommandList8_OMSetRenderTargets( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 1, &shHeap_RTV, FALSE, &shHeap_DSV );
    tgKN_GPU_EXT__SwapChain__Set_Viewport_and_Scissor( tiCXT_SWAP, uCMD );
    ID3D12GraphicsCommandList8_ClearDepthStencilView( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, shHeap_DSV, D3D12_CLEAR_FLAG_DEPTH, 1.0F, 0, 0, nullptr );

    tgUnit_Test__PH__Setup_Scene_Constant_Buffer( &sRTBuffer );

    /* Clear the render target using a full screen quad. */
    #if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)
    {
        PIXBeginEvent_ThatWorksInC_ID3D12GraphicsCommandList( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 0, "UNIT TEST: Draw UI - Clear Viewport" );
        tgKN_GPU_EXT__CMD__Set_State_From_Default( uCMD, ETgKN_GPU_DEFAULT_PSO_DEBUG_UI, sRTBuffer.m_enFormat, sDSBuffer.m_enFormat );
        s_sUIConstantBuffer.m_sDESC = sOutput_DESC;
        s_sUIConstantBuffer.m_vRect_UI.x = -1.0F;
        s_sUIConstantBuffer.m_vRect_UI.y =  1.0F;
        s_sUIConstantBuffer.m_vRect_UI.z =  1.0F;
        s_sUIConstantBuffer.m_vRect_UI.w = -1.0F;
        s_sUIConstantBuffer.m_vUI_Colour.r = 1.0F;
        s_sUIConstantBuffer.m_vUI_Colour.g = 1.0F;
        s_sUIConstantBuffer.m_vUI_Colour.b = 1.0F;
        s_sUIConstantBuffer.m_vUI_Colour.a = 1.0F;
        s_sUIConstantBuffer.m_uiSelect_Default_Texture_Index = 0;
        tgKN_GPU_EXT__CMD__Render_Debug_UI( uCMD, &s_sUIConstantBuffer );
        PIXEndEvent_ThatWorksInC_ID3D12GraphicsCommandList( uCMD.psEXT->m_psDX12_Graphics_Cmd_List );
    }
    #endif

#if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)
    s_sModelConstantBuffer.m_sDESC = sOutput_DESC;
    tgMM_Copy( &s_sModelConstantBuffer.m_mW2C, sizeof(s_sModelConstantBuffer.m_mW2C), &g_sSceneConstantBuffer.m_mW2C, sizeof(g_sSceneConstantBuffer.m_mW2C) );
    tgMM_Copy( &s_sModelConstantBuffer.m_mC2S, sizeof(s_sModelConstantBuffer.m_mC2S), &g_sSceneConstantBuffer.m_mC2S, sizeof(g_sSceneConstantBuffer.m_mC2S) );
    s_sModelConstantBuffer.m_uModel_Colour.m_vS_F32_04_1 = tgMH_Init_ELEM_S_F32_04_1( 1.0F, 1.0F, 1.0F, 1.0F );
    s_sModelConstantBuffer.m_vLight_Ambient = tgMH_Init_ELEM_S_F32_04_1( 0.1F, 0.1F, 0.1F, 1.0F );
    s_sModelConstantBuffer.m_vLight_Direction = tgMH_Init_ELEM_S_F32_04_1( -1.0F/1.73205081F, 1.0F/1.73205081F, -1.0F/1.73205081F, 0.0F );
    s_sModelConstantBuffer.m_vLight_Direction_Colour = tgMH_Init_ELEM_S_F32_04_1( 0.4F, 0.6F, 0.6F, 1.0F );
#endif

    #if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)
    {
        /* Draw a sphere at the camera location. */
        PIXBeginEvent_ThatWorksInC_ID3D12GraphicsCommandList( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 0, "UNIT TEST: Draw Debug Geometry" );
        tgKN_GPU_EXT__CMD__Set_State_From_Default( uCMD, ETgKN_GPU_DEFAULT_PSO_DEBUG_GEOM_02, sRTBuffer.m_enFormat, sDSBuffer.m_enFormat );

        //tgMH_CLI_S_F32_04_4( &s_sModelConstantBuffer.m_vModel_Transform );
        //s_sModelConstantBuffer.m_vModel_Transform._11 = 0.25F;
        //s_sModelConstantBuffer.m_vModel_Transform._22 = 0.25F;
        //s_sModelConstantBuffer.m_vModel_Transform._33 = 0.25F;
        //s_sModelConstantBuffer.m_vModel_Transform._41 = g_sCamera.m_sCamera.m_uCam_Position.m_vS_F32_04_1.x;
        //s_sModelConstantBuffer.m_vModel_Transform._42 = g_sCamera.m_sCamera.m_uCam_Position.m_vS_F32_04_1.y;
        //s_sModelConstantBuffer.m_vModel_Transform._43 = g_sCamera.m_sCamera.m_uCam_Position.m_vS_F32_04_1.z;
        //tgKN_GPU_EXT__CMD__Render_Debug_Geom( uCMD, ETgKN_GPU_DEBUG_PM_3D_SPHERE, &s_sModelConstantBuffer );

        /* Draw a sphere at the camera location. */
        tgMH_CLI_S_F32_04_4( &s_sModelConstantBuffer.m_vModel_Transform );
        s_sModelConstantBuffer.m_vModel_Transform._11 = 0.25F;
        s_sModelConstantBuffer.m_vModel_Transform._22 = 0.25F;
        s_sModelConstantBuffer.m_vModel_Transform._33 = 0.25F;
        s_sModelConstantBuffer.m_vModel_Transform._41 = g_sCamera.m_sCamera.m_uCam_Target.m_vS_F32_04_1.x;
        s_sModelConstantBuffer.m_vModel_Transform._42 = g_sCamera.m_sCamera.m_uCam_Target.m_vS_F32_04_1.y;
        s_sModelConstantBuffer.m_vModel_Transform._43 = g_sCamera.m_sCamera.m_uCam_Target.m_vS_F32_04_1.z;
        tgKN_GPU_EXT__CMD__Render_Debug_Geom( uCMD, ETgKN_GPU_DEBUG_PM_3D_SPHERE, &s_sModelConstantBuffer );

        PIXEndEvent_ThatWorksInC_ID3D12GraphicsCommandList( uCMD.psEXT->m_psDX12_Graphics_Cmd_List );
    }
    #endif

    #if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)
    {
        TgPH_WORLD_ID                       tiPH_World;

        PIXBeginEvent_ThatWorksInC_ID3D12GraphicsCommandList( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 0, "UNIT TEST: Draw Debug Geometry" );
        tiPH_World = tgPH_World_Query_World_Id( ETgPH_WORLD__SERVER_DEFAULT );
        tgPH_Form_Visualize_Render( uCMD, &s_sModelConstantBuffer, tiPH_World, sRTBuffer.m_enFormat, sDSBuffer.m_enFormat );
        PIXEndEvent_ThatWorksInC_ID3D12GraphicsCommandList( uCMD.psEXT->m_psDX12_Graphics_Cmd_List );
    }
    #endif

    #if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) && TgCOMPILE__PROFILE
    {
        PIXBeginEvent_ThatWorksInC_ID3D12GraphicsCommandList( uCMD.psEXT->m_psDX12_Graphics_Cmd_List, 0, "Physics Performance Stats" );
        tgPH_Debug_Render_Performance_Stats( uCMD, &sOutput_DESC, &sRTBuffer, &sDSBuffer );
        PIXEndEvent_ThatWorksInC_ID3D12GraphicsCommandList( uCMD.psEXT->m_psDX12_Graphics_Cmd_List );
    }
    #endif


    tgKN_GPU_EXT__CMD__Command_List_Close( uCMD );
    uCMD.ps = nullptr;
    tgKN_GPU_EXT__SwapChain__Present( tiCXT_WORK, tiCXT_SWAP );
    if (bEndFrame)
    {
        tgKN_GPU_EXT__Execute__Frame_End( tiCXT_WORK );
    }
    return (KTgS_OK);
}
