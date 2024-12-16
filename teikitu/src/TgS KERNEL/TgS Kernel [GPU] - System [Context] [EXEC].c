/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Kernel - System [GPU] [Context] [EXEC].c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgKN_GPU__Execute__Init -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU__Execute__Init( STg2_KN_GPU_Init_Result_PCU psResult, STg2_KN_GPU_Select_CPCU psSelect, TgRSIZE_C uiExec_Index, TgKN_GPU_CXT_DEVC_ID_C tiCXT_DEVC )
{
    TgRSIZE                             uiExecute_Index_In_Host_Context;
    TgRSIZE                             uiIndex;
    TgKN_GPU_CXT_EXEC_ID                tiCXT_EXEC;
    STg2_KN_GPU_CXT_DEVC_P              psCXT_DEVC;
    union
    {
        STg2_KN_GPU_CXT_EXEC_P              ps;
        STg2_UT_ST__ST_Node_P               pNode;
    }                                   sCXT_EXEC;
    TgKN_GPU_CXT_WORK_ID                tiCXT_WORK;
    UTg2_KN_GPU_CMD                     uCMD;
    STg2_KN_GPU_CXT_EXEC_EXTN_P         psCXT_EXEC_EXTN;

    /* Find an empty slot in the host context for the execution context. */
    for (uiExecute_Index_In_Host_Context = 0; uiExecute_Index_In_Host_Context < KTgKN_GPU_MAX_EXEC_CONTEXT; ++uiExecute_Index_In_Host_Context)
    {
        if (g_sKN_GPU_CXT_HOST.m_atiCXT_EXEC[uiExecute_Index_In_Host_Context].m_uiKI == KTgKN_GPU_CXT_EXEC_ID__INVALID.m_uiKI)
        {
            break;
        };
    };

    /* Theoretically impossible, however range checking is still good practice. */
    if (uiExecute_Index_In_Host_Context >= KTgKN_GPU_MAX_EXEC_CONTEXT)
    {
        return (KTgE_FAIL);
    };

    /* Validate that the parent device context identifiers match. */
    psCXT_DEVC = g_asKN_GPU_CXT_DEVC + tiCXT_DEVC.m_uiI;
    if (!tgKN_GPU_CXT_DEVC_ID_Is_Equal( &psCXT_DEVC->m_tiCXT_DEVC_S, tiCXT_DEVC))
    {
        return (KTgE_FAIL);
    };

    /* Take a context from the free list. */
    sCXT_EXEC.pNode = tgCM_UT_LF__ST__Pop( &g_sKN_GPU_CXT_EXEC_Free_Stack.m_sStack );
    if (nullptr == sCXT_EXEC.pNode)
    {
        return (KTgE_FAIL);
    };

    /* Initialize the context. */
    tgMM_Set_U08_0x00( sCXT_EXEC.pNode, sizeof( STg2_KN_GPU_CXT_EXEC ) );
    tgKN_GPU_CXT_EXEC_ID_Init( &sCXT_EXEC.ps->m_tiCXT_EXEC_S, (TgUINT_E32)(sCXT_EXEC.ps - g_asKN_GPU_CXT_EXEC) );
    tgKN_GPU_CXT_EXEC_ID_Load( &tiCXT_EXEC, &sCXT_EXEC.ps->m_tiCXT_EXEC_S );

    sCXT_EXEC.ps->m_tiCXT_DEVC = tiCXT_DEVC;
    sCXT_EXEC.ps->m_uiAdapter_Index = psCXT_DEVC->m_uiAdapter_Index;
    TgPARAM_CHECK_INDEX(psSelect->m_sNode[uiExec_Index].m_uiAdapter_Index, psSelect->m_uiEnumeration_Adapter_Index);
    TgVERIFY(psCXT_DEVC->m_uiAdapter_Index == psSelect->m_uiEnumeration_Adapter_Index[psSelect->m_sNode[uiExec_Index].m_uiAdapter_Index]);

    sCXT_EXEC.ps->m_uiNodeMask = psSelect->m_sNode[uiExec_Index].m_uiAdapter_Node_Mask;
    sCXT_EXEC.ps->m_nuiMax_Render_Target_View = psSelect->m_sNode[uiExec_Index].m_nuiRender_Target_Max;
    sCXT_EXEC.ps->m_nuiMax_Depth_Stencil_View = psSelect->m_sNode[uiExec_Index].m_nuiDepth_Stencil_Max;
    sCXT_EXEC.ps->m_nuiMax_Shader_Resource_View = psSelect->m_sNode[uiExec_Index].m_nuiData_Buffers_Max;

    /* Initialize the resource libraries - resources that are resident (accessible) to the GPU node. */

    tgKN_GPU_TX_IMG_Inst_LIB__Init( tiCXT_EXEC );
    tgKN_GPU_TX_CBE_Inst_LIB__Init( tiCXT_EXEC );
    tgKN_GPU_TX_VOL_Inst_LIB__Init( tiCXT_EXEC );

    if (TgFAILED(tgKN_GPU_EXT__Execute__Init( tiCXT_EXEC )))
    {
        goto tgKN_GPU__Execute__Init_FAIL_0;
    };

    /* Initialize all of the output contexts associated with this execution context. */
    for (uiIndex = 0; uiIndex < psSelect->m_nuiOutput; ++uiIndex)
    {
        if (psSelect->m_sOutput[uiIndex].m_uiNode_Index != uiExec_Index)
            continue;
        if ((uiIndex < KTgKN_GPU_MAX_SWAP_CONTEXT) && TgFAILED(tgKN_GPU__SwapChain__Init( psResult, psSelect, uiIndex, tiCXT_EXEC )))
        {
            goto tgKN_GPU__Execute__Init_FAIL_1;
        };
    };

    /* Create a set of standard colour textures in the 709 colour space. */

    tiCXT_WORK = tgKN_GPU_EXT__Execute__Frame_Start( tiCXT_EXEC );
    uCMD = tgKN_GPU_EXT__Execute__Command_List_Acquire( tiCXT_WORK, ETgKN_GPU_EXT_COMMAND_DIRECT );
    psCXT_EXEC_EXTN = g_asKN_GPU_CXT_EXEC_EXT + tiCXT_EXEC.m_uiI;
    tgMM_Set_U08_0x00( psCXT_EXEC_EXTN, sizeof( STg2_KN_GPU_CXT_EXEC_EXTN ) );

    /* Default cube textures */

    psCXT_EXEC_EXTN->m_sID_TX_CBE_INST_Black_709 = tgKN_GPU_TX_CBE_Inst__Init_Colour( uCMD, KTg_BLACK_G10_P709_U32, u8"LIB_BLACK" );
    TgVERIFY(KTgID__INVALID_VALUE != psCXT_EXEC_EXTN->m_sID_TX_CBE_INST_Black_709.m_uiKI);
    tgKN_GPU_EXT_Register_Default_TX_CBE_Inst( psCXT_EXEC_EXTN->m_sID_TX_CBE_INST_Black_709 );

    psCXT_EXEC_EXTN->m_sID_TX_CBE_INST_White_709 = tgKN_GPU_TX_CBE_Inst__Init_Colour( uCMD, KTg_WHITE_G10_P709_U32, u8"LIB_WHITE" );
    TgVERIFY(KTgID__INVALID_VALUE != psCXT_EXEC_EXTN->m_sID_TX_CBE_INST_White_709.m_uiKI);
    tgKN_GPU_EXT_Register_Default_TX_CBE_Inst( psCXT_EXEC_EXTN->m_sID_TX_CBE_INST_White_709 );

    /* Default volume textures */

    psCXT_EXEC_EXTN->m_sID_TX_VOL_INST_Black_709 = tgKN_GPU_TX_VOL_Inst__Init_Colour( uCMD, KTg_BLACK_G10_P709_U32, u8"LIB_BLACK" );
    TgVERIFY(KTgID__INVALID_VALUE != psCXT_EXEC_EXTN->m_sID_TX_VOL_INST_Black_709.m_uiKI);
    tgKN_GPU_EXT_Register_Default_TX_VOL_Inst( psCXT_EXEC_EXTN->m_sID_TX_VOL_INST_Black_709 );

    psCXT_EXEC_EXTN->m_sID_TX_VOL_INST_White_709 = tgKN_GPU_TX_VOL_Inst__Init_Colour( uCMD, KTg_WHITE_G10_P709_U32, u8"LIB_WHITE" );
    TgVERIFY(KTgID__INVALID_VALUE != psCXT_EXEC_EXTN->m_sID_TX_VOL_INST_White_709.m_uiKI);
    tgKN_GPU_EXT_Register_Default_TX_VOL_Inst( psCXT_EXEC_EXTN->m_sID_TX_VOL_INST_White_709 );

    /* Default image textures */

    psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Black_709 = tgKN_GPU_TX_IMG_Inst__Init_Colour( uCMD, KTg_BLACK_G10_P709_U32, u8"LIB_BLACK" );
    TgVERIFY(KTgID__INVALID_VALUE != psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Black_709.m_uiKI);
    tgKN_GPU_EXT_Register_Default_TX_IMG_Inst( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Black_709 );

    psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_White_709 = tgKN_GPU_TX_IMG_Inst__Init_Colour( uCMD, KTg_WHITE_G10_P709_U32, u8"LIB_WHITE" );
    TgVERIFY(KTgID__INVALID_VALUE != psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_White_709.m_uiKI);
    tgKN_GPU_EXT_Register_Default_TX_IMG_Inst( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_White_709 );

    psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Red_709 = tgKN_GPU_TX_IMG_Inst__Init_Colour( uCMD, KTg_RED_G10_P709_U32, u8"LIB_RED" );
    TgVERIFY(KTgID__INVALID_VALUE != psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Red_709.m_uiKI);
    tgKN_GPU_EXT_Register_Default_TX_IMG_Inst( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Red_709 );

    psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Green_709 = tgKN_GPU_TX_IMG_Inst__Init_Colour( uCMD, KTg_GREEN_G10_P709_U32, u8"LIB_GREEN" );
    TgVERIFY(KTgID__INVALID_VALUE != psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Green_709.m_uiKI);
    tgKN_GPU_EXT_Register_Default_TX_IMG_Inst( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Green_709 );

    psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Blue_709 = tgKN_GPU_TX_IMG_Inst__Init_Colour( uCMD, KTg_BLUE_G10_P709_U32, u8"LIB_BLUE" );
    TgVERIFY(KTgID__INVALID_VALUE != psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Blue_709.m_uiKI);
    tgKN_GPU_EXT_Register_Default_TX_IMG_Inst( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Blue_709 );

    psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Yellow_709 = tgKN_GPU_TX_IMG_Inst__Init_Colour( uCMD, KTg_YELLOW_G10_P709_U32, u8"LIB_YELLOW" );
    TgVERIFY(KTgID__INVALID_VALUE != psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Yellow_709.m_uiKI);
    tgKN_GPU_EXT_Register_Default_TX_IMG_Inst( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Yellow_709 );

    psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Magenta_709 = tgKN_GPU_TX_IMG_Inst__Init_Colour( uCMD, KTg_MAGENTA_G10_P709_U32, u8"LIB_MAGENTA" );
    TgVERIFY(KTgID__INVALID_VALUE != psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Magenta_709.m_uiKI);
    tgKN_GPU_EXT_Register_Default_TX_IMG_Inst( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Magenta_709 );

    psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Cyan_709 = tgKN_GPU_TX_IMG_Inst__Init_Colour( uCMD, KTg_CYAN_G10_P709_U32, u8"LIB_CYAN" );
    TgVERIFY(KTgID__INVALID_VALUE != psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Cyan_709.m_uiKI);
    tgKN_GPU_EXT_Register_Default_TX_IMG_Inst( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Cyan_709 );

    psCXT_EXEC_EXTN->m_tiTX_IMG_Normal = tgKN_GPU_TX_IMG_Inst__IncRef( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Black_709 );
    tgKN_GPU_EXT_Register_Default_TX_IMG_Inst( psCXT_EXEC_EXTN->m_tiTX_IMG_Normal );
    psCXT_EXEC_EXTN->m_tiTX_IMG_Noise = tgKN_GPU_TX_IMG_Inst__IncRef( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Black_709 );
    tgKN_GPU_EXT_Register_Default_TX_IMG_Inst( psCXT_EXEC_EXTN->m_tiTX_IMG_Noise );
    psCXT_EXEC_EXTN->m_tiTX_IMG_Peturbation = tgKN_GPU_TX_IMG_Inst__IncRef( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Black_709 );
    tgKN_GPU_EXT_Register_Default_TX_IMG_Inst( psCXT_EXEC_EXTN->m_tiTX_IMG_Peturbation );

    tgKN_GPU_EXT__CMD__Command_List_Close( uCMD );
    uCMD.ps = nullptr;
    tgKN_GPU_EXT__Execute__Frame_End( tiCXT_WORK );

    g_sKN_GPU_CXT_HOST.m_atiCXT_EXEC[uiExecute_Index_In_Host_Context] = tiCXT_EXEC;

    psResult->m_sEXEC[psResult->m_nuiEXEC].m_tiCXT_EXEC = tiCXT_EXEC;
    psResult->m_sEXEC[psResult->m_nuiEXEC].m_uiNodeMask = sCXT_EXEC.ps->m_uiNodeMask;
    psResult->m_sEXEC[psResult->m_nuiEXEC].m_uiEnumeration_Adapter_Index = sCXT_EXEC.ps->m_uiAdapter_Index;
    ++psResult->m_nuiEXEC;

    if (TgFAILED( tgKN_GPU__Execute__Init_Debug( tiCXT_EXEC ) ))
    {
        tgKN_GPU_EXT__Execute__Free( tiCXT_EXEC );
        return (KTgE_FAIL);
    };

    return (KTgS_OK);

tgKN_GPU__Execute__Init_FAIL_1:
    for (;;)
    {
        if (0 == psResult->m_nuiSWAP || psResult->m_sSWAP[psResult->m_nuiSWAP-1].m_tiCXT_EXEC.m_uiKI != tiCXT_EXEC.m_uiKI)
            break;
        tgKN_GPU__SwapChain__Free( psResult->m_sSWAP[psResult->m_nuiSWAP-1].m_tiCXT_SWAP );
        --psResult->m_nuiSWAP;
    };
tgKN_GPU__Execute__Init_FAIL_0:
    tgKN_GPU__Execute__Free( tiCXT_EXEC );
    return (KTgE_FAIL);
}


/* ---- tgKN_GPU__Execute__Free -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU__Execute__Free( TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC )
{
    TgRSIZE                             uiIndex;
    union
    {
        STg2_KN_GPU_CXT_EXEC_P              ps;
        STg2_UT_ST__ST_Node_P               pNode;
    }                                   sCXT_EXEC = { .ps = g_asKN_GPU_CXT_EXEC + tiCXT_EXEC.m_uiI };
    STg2_KN_GPU_CXT_EXEC_EXTN_PC        psCXT_EXEC_EXTN = g_asKN_GPU_CXT_EXEC_EXT + tiCXT_EXEC.m_uiI;

    TgPARAM_CHECK_INDEX( tiCXT_EXEC.m_uiI, g_asKN_GPU_CXT_EXEC );
    TgPARAM_CHECK( tgKN_GPU_CXT_EXEC_ID_Is_Equal( &(g_asKN_GPU_CXT_EXEC[tiCXT_EXEC.m_uiI].m_tiCXT_EXEC_S), tiCXT_EXEC ) );

    tgKN_GPU_EXT__Execute__Flush( tiCXT_EXEC );

    tgKN_GPU__Execute__Free_Debug( tiCXT_EXEC );

    if (KTgID__INVALID_VALUE != psCXT_EXEC_EXTN->m_tiTX_IMG_Peturbation.m_uiKI)
        tgKN_GPU_TX_IMG_Inst__Release( psCXT_EXEC_EXTN->m_tiTX_IMG_Peturbation );
    if (KTgID__INVALID_VALUE != psCXT_EXEC_EXTN->m_tiTX_IMG_Noise.m_uiKI)
        tgKN_GPU_TX_IMG_Inst__Release( psCXT_EXEC_EXTN->m_tiTX_IMG_Noise );
    if (KTgID__INVALID_VALUE != psCXT_EXEC_EXTN->m_tiTX_IMG_Normal.m_uiKI)
        tgKN_GPU_TX_IMG_Inst__Release( psCXT_EXEC_EXTN->m_tiTX_IMG_Normal );

    if (KTgID__INVALID_VALUE != psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Cyan_709.m_uiKI)
        tgKN_GPU_TX_IMG_Inst__Release( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Cyan_709 );
    if (KTgID__INVALID_VALUE != psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Magenta_709.m_uiKI)
        tgKN_GPU_TX_IMG_Inst__Release( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Magenta_709 );
    if (KTgID__INVALID_VALUE != psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Yellow_709.m_uiKI)
        tgKN_GPU_TX_IMG_Inst__Release( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Yellow_709 );
    if (KTgID__INVALID_VALUE != psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Blue_709.m_uiKI)
        tgKN_GPU_TX_IMG_Inst__Release( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Blue_709 );
    if (KTgID__INVALID_VALUE != psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Green_709.m_uiKI)
        tgKN_GPU_TX_IMG_Inst__Release( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Green_709 );
    if (KTgID__INVALID_VALUE != psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Red_709.m_uiKI)
        tgKN_GPU_TX_IMG_Inst__Release( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Red_709 );
    if (KTgID__INVALID_VALUE != psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_White_709.m_uiKI)
        tgKN_GPU_TX_IMG_Inst__Release( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_White_709 );
    if (KTgID__INVALID_VALUE != psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Black_709.m_uiKI)
        tgKN_GPU_TX_IMG_Inst__Release( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Black_709 );

    if (KTgID__INVALID_VALUE != psCXT_EXEC_EXTN->m_sID_TX_VOL_INST_Black_709.m_uiKI)
        tgKN_GPU_TX_VOL_Inst__Release( psCXT_EXEC_EXTN->m_sID_TX_VOL_INST_Black_709 );
    if (KTgID__INVALID_VALUE != psCXT_EXEC_EXTN->m_sID_TX_VOL_INST_White_709.m_uiKI)
        tgKN_GPU_TX_VOL_Inst__Release( psCXT_EXEC_EXTN->m_sID_TX_VOL_INST_White_709 );

    if (KTgID__INVALID_VALUE != psCXT_EXEC_EXTN->m_sID_TX_CBE_INST_Black_709.m_uiKI)
        tgKN_GPU_TX_CBE_Inst__Release( psCXT_EXEC_EXTN->m_sID_TX_CBE_INST_Black_709 );
    if (KTgID__INVALID_VALUE != psCXT_EXEC_EXTN->m_sID_TX_CBE_INST_White_709.m_uiKI)
        tgKN_GPU_TX_CBE_Inst__Release( psCXT_EXEC_EXTN->m_sID_TX_CBE_INST_White_709 );

    tgKN_GPU_TX_VOL_Inst_LIB__Free( tiCXT_EXEC );
    tgKN_GPU_TX_CBE_Inst_LIB__Free( tiCXT_EXEC );
    tgKN_GPU_TX_IMG_Inst_LIB__Free( tiCXT_EXEC );

    tgKN_GPU_EXT__Execute__Free( tiCXT_EXEC );

    tgMM_Set_U08_0x00( sCXT_EXEC.ps, sizeof( STg2_KN_GPU_CXT_EXEC ) );
    tgCM_UT_LF__ST__Push( &g_sKN_GPU_CXT_EXEC_Free_Stack.m_sStack, sCXT_EXEC.pNode );

    /* Remove the context id from the host list. */
    for (uiIndex = 0; uiIndex < KTgKN_GPU_MAX_EXEC_CONTEXT; ++uiIndex)
    {
        if (g_sKN_GPU_CXT_HOST.m_atiCXT_EXEC[uiIndex].m_uiKI == tiCXT_EXEC.m_uiKI)
        {
            g_sKN_GPU_CXT_HOST.m_atiCXT_EXEC[uiIndex] = KTgKN_GPU_CXT_EXEC_ID__INVALID;
            break;
        };
    };
}
