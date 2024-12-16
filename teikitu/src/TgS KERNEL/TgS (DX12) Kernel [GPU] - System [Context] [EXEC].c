/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (DX12) Kernel - System [GPU] [Context] [EXEC].c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

static TgVOID
tgKN_GPU_EXT_Command_Queue_Init(
    STg2_KN_GPU_EXT_CMD_Queue_PC NONULL ARG0, ID3D12Device10_P ARG1, D3D12_COMMAND_LIST_TYPE ARG2, TgUINT_E32_C ARG3 );

static TgVOID
tgKN_GPU_EXT_Command_Queue_Free(
    STg2_KN_GPU_EXT_CMD_Queue_PC NONULL ARG0 );

static TgVOID
tgKN_GPU_EXT_Context_Command_Cmd_Allocators_Init(
    STg2_KN_GPU_EXT_CXT_CMD_PC NONULL ARG0 );

static TgVOID
tgKN_GPU_EXT_Context_Command_Cmd_Lists_Init(
    STg2_KN_GPU_EXT_CXT_CMD_PC NONULL ARG0 );

static TgRESULT
tgKN_GPU_EXT_Context_Command_Init(
    TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC, STg2_KN_GPU_EXT_CXT_CMD_PC NONULL ARG0 );

static TgVOID
tgKN_GPU_EXT_Context_Command_Free(
    STg2_KN_GPU_EXT_CXT_CMD_PC NONULL ARG0 );

static TgVOID
tgKN_GPU_EXT__Execute__Process_Resource_Release_List(
    TgKN_GPU_CXT_EXEC_ID_C ARG0 );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public GPU Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_GPU_EXT__Execute__Cmd_List_Flush ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_EXT__Execute__Cmd_List_Flush( TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC, ETgKN_GPU_EXT_COMMAND_C enCmd_List )
{
    STg2_KN_GPU_EXT_CXT_EXEC_PC         psEXT_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + tiCXT_EXEC.m_uiI;

    STg2_KN_GPU_EXT_CMD_Queue_P         psEXT_Queue;
    TgUINT_E64                          uiFence_Value;

    TgPARAM_CHECK_INDEX( tiCXT_EXEC.m_uiI, g_asKN_GPU_CXT_EXEC );
    TgPARAM_CHECK( tgKN_GPU_CXT_EXEC_ID_Is_Equal( &(g_asKN_GPU_CXT_EXEC[tiCXT_EXEC.m_uiI].m_tiCXT_EXEC_S), tiCXT_EXEC ) );
    TgPARAM_CHECK( enCmd_List >= D3D12_COMMAND_LIST_TYPE_DIRECT && enCmd_List <= D3D12_COMMAND_LIST_TYPE_VIDEO_ENCODE );

    psEXT_Queue = &psEXT_CXT_EXEC->m_sCmd_Queue[enCmd_List];

    uiFence_Value = atomic_fetch_add( &psEXT_Queue->m_xuiFence_Value, 1 );
    TgVERIFY( SUCCEEDED( ID3D12CommandQueue_Signal( psEXT_Queue->m_psDX12_Cmd_Queue, psEXT_Queue->m_psDX12_Fence, uiFence_Value ) ) );
    do {
        TgVERIFY( SUCCEEDED( ID3D12Fence_SetEventOnCompletion( psEXT_Queue->m_psDX12_Fence, uiFence_Value, psEXT_Queue->m_psFence_Event ) ) );
        g_pfnWaitForSingleObjectEx( psEXT_Queue->m_psFence_Event, 1, FALSE );
    } while (ID3D12Fence_GetCompletedValue( psEXT_Queue->m_psDX12_Fence ) < uiFence_Value);
    tgKN_GPU_EXT__Execute__Process_Resource_Release_List( tiCXT_EXEC );
}


/* ---- tgKN_GPU_EXT__Execute__Flush --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_EXT__Execute__Flush( TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC )
{
    STg2_KN_GPU_EXT_CXT_EXEC_PC         psEXT_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + tiCXT_EXEC.m_uiI;

    TgSINT_E32                          iIndex;

    TgPARAM_CHECK_INDEX( tiCXT_EXEC.m_uiI, g_asKN_GPU_CXT_EXEC );
    TgPARAM_CHECK( tgKN_GPU_CXT_EXEC_ID_Is_Equal( &(g_asKN_GPU_CXT_EXEC[tiCXT_EXEC.m_uiI].m_tiCXT_EXEC_S), tiCXT_EXEC ) );

    for (iIndex = D3D12_COMMAND_LIST_TYPE_DIRECT; iIndex <= D3D12_COMMAND_LIST_TYPE_VIDEO_ENCODE; ++iIndex)
    {
        STg2_KN_GPU_EXT_CMD_Queue_PC        psEXT_Queue = &psEXT_CXT_EXEC->m_sCmd_Queue[iIndex];
        TgUINT_E64                          uiFence_Value;

        if (nullptr == psEXT_Queue->m_psDX12_Cmd_Queue)
            continue;

        uiFence_Value = atomic_fetch_add( &psEXT_Queue->m_xuiFence_Value, 1 );
        TgVERIFY( SUCCEEDED( ID3D12CommandQueue_Signal( psEXT_Queue->m_psDX12_Cmd_Queue, psEXT_Queue->m_psDX12_Fence, uiFence_Value ) ) );
        do {
            TgVERIFY( SUCCEEDED( ID3D12Fence_SetEventOnCompletion( psEXT_Queue->m_psDX12_Fence, uiFence_Value, psEXT_Queue->m_psFence_Event ) ) );
            g_pfnWaitForSingleObjectEx( psEXT_Queue->m_psFence_Event, 1, FALSE );
        } while (ID3D12Fence_GetCompletedValue( psEXT_Queue->m_psDX12_Fence ) < uiFence_Value);
    }

    tgKN_GPU_EXT__Execute__Process_Resource_Release_List( tiCXT_EXEC );
}


/* ---- tgKN_GPU_EXT__Execute__Frame_Start --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgKN_GPU_CXT_WORK_ID tgKN_GPU_EXT__Execute__Frame_Start( TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC )
{
    TgPARAM_CHECK_INDEX( tiCXT_EXEC.m_uiI, g_asKN_GPU_CXT_EXEC );
    TgPARAM_CHECK( tgKN_GPU_CXT_EXEC_ID_Is_Equal( &(g_asKN_GPU_CXT_EXEC[tiCXT_EXEC.m_uiI].m_tiCXT_EXEC_S), tiCXT_EXEC ) );

    {
        STg2_KN_GPU_EXT_CXT_EXEC_PC         psEXT_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + tiCXT_EXEC.m_uiI;
        TgRSIZE                             uiContext_Command_Count = atomic_fetch_add( &psEXT_CXT_EXEC->m_xuiContext_Command_Index, 1 );
        TgRSIZE                             uiContext_Command_Index = uiContext_Command_Count % KTgKN_GPU_MAX_EXEC_CONTEXT_COMMAND;
        STg2_KN_GPU_EXT_CXT_CMD_PC          psEXT_CXT_CMD = psEXT_CXT_EXEC->m_sContext_Command + uiContext_Command_Index;
        ID3D12Device10_PC                   psDX12_Device = g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Adapter[psEXT_CXT_EXEC->m_uiAdapter_Index].m_psDX12_Device;

        D3D12_CPU_DESCRIPTOR_HANDLE         sDX12_CPU;
        UINT                                nuiDescriptors;
        TgSINT_E32                          iCmd_List;
        TgRSIZE                             uiIndex;

        tgPM_MT_SM_Wait_Block( &psEXT_CXT_CMD->m_sLock );

        /* Reset the work identifier to avoid (or at least detect) ABA or other stale pointer issues. */
        tgKN_GPU_CXT_WORK_ID_Init( &psEXT_CXT_CMD->m_tiCXT_WORK_S, (TgUINT_E32)(uiContext_Command_Index & 0xFFFF) | (TgUINT_E32)((tiCXT_EXEC.m_uiI << 16) & 0xFFFF0000) );
        psEXT_CXT_CMD->m_tiCXT_EXEC = tiCXT_EXEC;

        /* Check to see if the fence value has passed the terminating fence value for this set of command allocators and command lists. */
        for (iCmd_List = D3D12_COMMAND_LIST_TYPE_DIRECT; iCmd_List <= D3D12_COMMAND_LIST_TYPE_VIDEO_ENCODE; ++iCmd_List)
        {
            STg2_KN_GPU_EXT_CMD_Queue_PC        psEXT_Queue = &(psEXT_CXT_EXEC->m_sCmd_Queue[iCmd_List]);
            TgUINT_E64                          uiFence_Value;

            if (nullptr == psEXT_Queue->m_psDX12_Cmd_Queue)
                continue;

            uiFence_Value = psEXT_CXT_CMD->m_uiFence_Value_End_Of_Frame[iCmd_List];
            while (ID3D12Fence_GetCompletedValue( psEXT_Queue->m_psDX12_Fence ) < uiFence_Value)
            {
                TgVERIFY( SUCCEEDED( ID3D12Fence_SetEventOnCompletion( psEXT_Queue->m_psDX12_Fence, uiFence_Value, psEXT_Queue->m_psFence_Event ) ) );
                g_pfnWaitForSingleObjectEx( psEXT_Queue->m_psFence_Event, 1, FALSE );
            }
        }

        for (uiIndex = 0; uiIndex < TgARRAY_COUNT( psEXT_CXT_CMD->m_asCmd_Allocator__Direct ); ++uiIndex)
        {
            if (psEXT_CXT_CMD->m_asCmd_Allocator__Direct[uiIndex].m_psDX12)
                TgVERIFY( SUCCEEDED( ID3D12CommandAllocator_Reset( psEXT_CXT_CMD->m_asCmd_Allocator__Direct[uiIndex].m_psDX12 ) ) );
        };
        for (uiIndex = 0; uiIndex < TgARRAY_COUNT( psEXT_CXT_CMD->m_asCmd_Allocator__Bundle ); ++uiIndex)
        {
            if (psEXT_CXT_CMD->m_asCmd_Allocator__Bundle[uiIndex].m_psDX12)
                TgVERIFY( SUCCEEDED( ID3D12CommandAllocator_Reset( psEXT_CXT_CMD->m_asCmd_Allocator__Bundle[uiIndex].m_psDX12 ) ) );
        };
        for (uiIndex = 0; uiIndex < TgARRAY_COUNT( psEXT_CXT_CMD->m_asCmd_Allocator__Compute ); ++uiIndex)
        {
            if (psEXT_CXT_CMD->m_asCmd_Allocator__Compute[uiIndex].m_psDX12)
                TgVERIFY( SUCCEEDED( ID3D12CommandAllocator_Reset( psEXT_CXT_CMD->m_asCmd_Allocator__Compute[uiIndex].m_psDX12 ) ) );
        };
        for (uiIndex = 0; uiIndex < TgARRAY_COUNT( psEXT_CXT_CMD->m_asCmd_Allocator__Copy ); ++uiIndex)
        {
            if (psEXT_CXT_CMD->m_asCmd_Allocator__Copy[uiIndex].m_psDX12)
                TgVERIFY( SUCCEEDED( ID3D12CommandAllocator_Reset( psEXT_CXT_CMD->m_asCmd_Allocator__Copy[uiIndex].m_psDX12 ) ) );
        };
        for (uiIndex = 0; uiIndex < TgARRAY_COUNT( psEXT_CXT_CMD->m_asCmd_Allocator__Video_Decode ); ++uiIndex)
        {
            if (psEXT_CXT_CMD->m_asCmd_Allocator__Video_Decode[uiIndex].m_psDX12)
                TgVERIFY( SUCCEEDED( ID3D12CommandAllocator_Reset( psEXT_CXT_CMD->m_asCmd_Allocator__Video_Decode[uiIndex].m_psDX12 ) ) );
        };
        for (uiIndex = 0; uiIndex < TgARRAY_COUNT( psEXT_CXT_CMD->m_asCmd_Allocator__Video_Process ); ++uiIndex)
        {
            if (psEXT_CXT_CMD->m_asCmd_Allocator__Video_Process[uiIndex].m_psDX12)
                TgVERIFY( SUCCEEDED( ID3D12CommandAllocator_Reset( psEXT_CXT_CMD->m_asCmd_Allocator__Video_Process[uiIndex].m_psDX12 ) ) );
        };
        for (uiIndex = 0; uiIndex < TgARRAY_COUNT( psEXT_CXT_CMD->m_asCmd_Allocator__Video_Encode ); ++uiIndex)
        {
            if (psEXT_CXT_CMD->m_asCmd_Allocator__Video_Encode[uiIndex].m_psDX12)
                TgVERIFY( SUCCEEDED( ID3D12CommandAllocator_Reset( psEXT_CXT_CMD->m_asCmd_Allocator__Video_Encode[uiIndex].m_psDX12 ) ) );
        };

        tgKN_GPU_EXT_Context_Command_Cmd_Lists_Init( psEXT_CXT_CMD );

        ID3D12DescriptorHeap_GetCPUDescriptorHandleForHeapStart( psEXT_CXT_CMD->m_sCBV_SRV_UAV.m_psDX12_Heap, &psEXT_CXT_CMD->m_sCBV_SRV_UAV.m_sDX12_CPU_Handle );
        ID3D12DescriptorHeap_GetCPUDescriptorHandleForHeapStart( psEXT_CXT_EXEC->m_sSRV.m_psDX12_Heap, &sDX12_CPU );
        nuiDescriptors = KTgMACRO_KN_GPU_EXT_MAX_DEFAULT_SRV_CBE + KTgMACRO_KN_GPU_EXT_MAX_DEFAULT_SRV_VOL + KTgMACRO_KN_GPU_EXT_MAX_DEFAULT_SRV_IMG;

        ID3D12Device10_CopyDescriptorsSimple( psDX12_Device, nuiDescriptors, psEXT_CXT_CMD->m_sCBV_SRV_UAV.m_sDX12_CPU_Handle, sDX12_CPU, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV );
        psEXT_CXT_CMD->m_sCBV_SRV_UAV.m_sDX12_CPU_Handle.ptr += KTgKN_GPU_EXT_MAX_DEFAULT_SRV * psEXT_CXT_CMD->m_sCBV_SRV_UAV.m_uiDescriptor_Size;

        tgKN_GPU_EXT__Execute__Process_Resource_Release_List( tiCXT_EXEC );

    #if TgCOMPILE__RENDER_DEBUG_OUTPUT
        atomic_store( &psEXT_CXT_CMD->m_xuiDX12_CB_Text, 0 );
        atomic_store( &psEXT_CXT_CMD->m_xuiDX12_CB_UI, 0 );
        atomic_store( &psEXT_CXT_CMD->m_xuiDX12_CB_GEOM, 0 );
        atomic_store( &psEXT_CXT_CMD->m_xuiDX12_VB_LINE, 0 );
    /*# TgCOMPILE__RENDER_DEBUG_OUTPUT */
    #endif

        return (tgKN_GPU_CXT_WORK_ID_Query_Unsafe( &psEXT_CXT_CMD->m_tiCXT_WORK_S ));
    }
}


/* ---- tgKN_GPU_EXT__Execute__Frame_End ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_EXT__Execute__Frame_End( TgKN_GPU_CXT_WORK_ID_C tiCXT_WORK )
{
    TgRSIZE                             uiEXEC = (tiCXT_WORK.m_uiI >> 16) & 0xFFFF;
    TgRSIZE                             uiWORK = (tiCXT_WORK.m_uiI & 0xFFFF) % KTgKN_GPU_MAX_EXEC_CONTEXT_COMMAND;
    STg2_KN_GPU_EXT_CXT_EXEC_PC         psEXT_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + uiEXEC;

    TgPARAM_VAR(STg2_KN_GPU_CXT_EXEC_PC psCXT_EXEC = g_asKN_GPU_CXT_EXEC + uiEXEC;)
    TgPARAM_CHECK_INDEX( uiEXEC, g_asKN_GPU_EXT_CXT_EXEC );
    TgPARAM_CHECK_INDEX( uiWORK, g_asKN_GPU_EXT_CXT_EXEC[uiEXEC].m_sContext_Command );
    TgPARAM_CHECK( tgKN_GPU_CXT_WORK_ID_Is_Equal( &psEXT_CXT_EXEC->m_sContext_Command[uiWORK].m_tiCXT_WORK_S, tiCXT_WORK ) );
    TgPARAM_CHECK( tgKN_GPU_CXT_EXEC_ID_Is_Equal( &psCXT_EXEC->m_tiCXT_EXEC_S, psEXT_CXT_EXEC->m_sContext_Command[uiWORK].m_tiCXT_EXEC ) );

    {
        STg2_KN_GPU_EXT_CXT_CMD_PC          psEXT_CXT_CMD = psEXT_CXT_EXEC->m_sContext_Command + uiWORK;

        TgSINT_E32                          iCmd_List;

        for (iCmd_List = D3D12_COMMAND_LIST_TYPE_DIRECT; iCmd_List <= D3D12_COMMAND_LIST_TYPE_VIDEO_ENCODE; ++iCmd_List)
        {
            STg2_KN_GPU_EXT_CMD_Queue_PC        psEXT_Queue = &(psEXT_CXT_EXEC->m_sCmd_Queue[iCmd_List]);
            TgUINT_E64                          uiFence_Value, uiCompleted_Fence_Value;

            if (nullptr == psEXT_Queue->m_psDX12_Cmd_Queue)
                continue;

            uiCompleted_Fence_Value = ID3D12Fence_GetCompletedValue( psEXT_Queue->m_psDX12_Fence );
            uiFence_Value = atomic_fetch_add( &psEXT_Queue->m_xuiFence_Value, 1 );
            TgVERIFY(uiCompleted_Fence_Value < uiFence_Value);

            psEXT_CXT_CMD->m_uiFence_Value_End_Of_Frame[iCmd_List] = uiFence_Value;
            TgVERIFY( SUCCEEDED( ID3D12CommandQueue_Signal( psEXT_Queue->m_psDX12_Cmd_Queue, psEXT_Queue->m_psDX12_Fence, uiFence_Value ) ) );

            //uiFence_Value = atomic_fetch_add( &psEXT_Queue->m_xuiFence_Value, 1 );
            //TgVERIFY( SUCCEEDED( ID3D12CommandQueue_Wait( psEXT_Queue->m_psDX12_Cmd_Queue, psEXT_Queue->m_psDX12_Fence, uiFence_Value ) ) );
        };

#if !defined(TGS_FINAL)
    {
        STg2_UT_ST__ST_Node_P               psNode;
        TgSINT_E32                          iIndex;

        /* Validation - check that all allocators have been returned. */

        for (psNode = tgCM_UT_LF__ST__Pop( &psEXT_CXT_CMD->m_sCmd_Allocator_Free_Stack[D3D12_COMMAND_LIST_TYPE_DIRECT].m_sStack ), iIndex = 0; nullptr != psNode; ++iIndex)
            psNode = tgCM_UT_LF__ST__Pop( &psEXT_CXT_CMD->m_sCmd_Allocator_Free_Stack[D3D12_COMMAND_LIST_TYPE_DIRECT].m_sStack );
        TgVERIFY( TgARRAY_COUNT( psEXT_CXT_CMD->m_asCmd_Allocator__Direct ) == iIndex );
        for (psNode = tgCM_UT_LF__ST__Pop( &psEXT_CXT_CMD->m_sCmd_Allocator_Free_Stack[D3D12_COMMAND_LIST_TYPE_BUNDLE].m_sStack ), iIndex = 0; nullptr != psNode; ++iIndex)
            psNode = tgCM_UT_LF__ST__Pop( &psEXT_CXT_CMD->m_sCmd_Allocator_Free_Stack[D3D12_COMMAND_LIST_TYPE_BUNDLE].m_sStack );
        TgVERIFY( TgARRAY_COUNT( psEXT_CXT_CMD->m_asCmd_Allocator__Bundle ) == iIndex );
        for (psNode = tgCM_UT_LF__ST__Pop( &psEXT_CXT_CMD->m_sCmd_Allocator_Free_Stack[D3D12_COMMAND_LIST_TYPE_COMPUTE].m_sStack ), iIndex = 0; nullptr != psNode; ++iIndex)
            psNode = tgCM_UT_LF__ST__Pop( &psEXT_CXT_CMD->m_sCmd_Allocator_Free_Stack[D3D12_COMMAND_LIST_TYPE_COMPUTE].m_sStack );
        TgVERIFY( TgARRAY_COUNT( psEXT_CXT_CMD->m_asCmd_Allocator__Compute ) == iIndex );
        for (psNode = tgCM_UT_LF__ST__Pop( &psEXT_CXT_CMD->m_sCmd_Allocator_Free_Stack[D3D12_COMMAND_LIST_TYPE_COPY].m_sStack ), iIndex = 0; nullptr != psNode; ++iIndex)
            psNode = tgCM_UT_LF__ST__Pop( &psEXT_CXT_CMD->m_sCmd_Allocator_Free_Stack[D3D12_COMMAND_LIST_TYPE_COPY].m_sStack );
        TgVERIFY( TgARRAY_COUNT( psEXT_CXT_CMD->m_asCmd_Allocator__Copy ) == iIndex );
        for (psNode = tgCM_UT_LF__ST__Pop( &psEXT_CXT_CMD->m_sCmd_Allocator_Free_Stack[D3D12_COMMAND_LIST_TYPE_VIDEO_DECODE].m_sStack ), iIndex = 0; nullptr != psNode; ++iIndex)
            psNode = tgCM_UT_LF__ST__Pop( &psEXT_CXT_CMD->m_sCmd_Allocator_Free_Stack[D3D12_COMMAND_LIST_TYPE_VIDEO_DECODE].m_sStack );
        TgVERIFY( TgARRAY_COUNT( psEXT_CXT_CMD->m_asCmd_Allocator__Video_Decode ) == iIndex );
        for (psNode = tgCM_UT_LF__ST__Pop( &psEXT_CXT_CMD->m_sCmd_Allocator_Free_Stack[D3D12_COMMAND_LIST_TYPE_VIDEO_PROCESS].m_sStack ), iIndex = 0; nullptr != psNode; ++iIndex)
            psNode = tgCM_UT_LF__ST__Pop( &psEXT_CXT_CMD->m_sCmd_Allocator_Free_Stack[D3D12_COMMAND_LIST_TYPE_VIDEO_PROCESS].m_sStack );
        TgVERIFY( TgARRAY_COUNT( psEXT_CXT_CMD->m_asCmd_Allocator__Video_Process ) == iIndex );
        for (psNode = tgCM_UT_LF__ST__Pop( &psEXT_CXT_CMD->m_sCmd_Allocator_Free_Stack[D3D12_COMMAND_LIST_TYPE_VIDEO_ENCODE].m_sStack ), iIndex = 0; nullptr != psNode; ++iIndex)
            psNode = tgCM_UT_LF__ST__Pop( &psEXT_CXT_CMD->m_sCmd_Allocator_Free_Stack[D3D12_COMMAND_LIST_TYPE_VIDEO_ENCODE].m_sStack );
        TgVERIFY( TgARRAY_COUNT( psEXT_CXT_CMD->m_asCmd_Allocator__Video_Encode ) == iIndex );

        tgKN_GPU_EXT_Context_Command_Cmd_Allocators_Init( psEXT_CXT_CMD );
    }
/*# !defined(TGS_FINAL) */
#endif
        tgKN_GPU_CXT_WORK_ID_Invalidate( &psEXT_CXT_CMD->m_tiCXT_WORK_S );
        tgPM_MT_SM_Signal( &psEXT_CXT_CMD->m_sLock, 1 );
    }
}


/* ---- tgKN_GPU_EXT_Render_Context__Command_List_Acquire ------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
UTg2_KN_GPU_CMD tgKN_GPU_EXT__Execute__Command_List_Acquire( TgKN_GPU_CXT_WORK_ID_C tiCXT_WORK, ETgKN_GPU_EXT_COMMAND_C enCmd_List )
{
    TgRSIZE                             uiEXEC = (tiCXT_WORK.m_uiI >> 16) & 0xFFFF;
    TgRSIZE                             uiWORK = (tiCXT_WORK.m_uiI & 0xFFFF) % KTgKN_GPU_MAX_EXEC_CONTEXT_COMMAND;
    STg2_KN_GPU_EXT_CXT_EXEC_PC         psEXT_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + uiEXEC;
    D3D12_COMMAND_LIST_TYPE const       enDX12_Cmd_List = (D3D12_COMMAND_LIST_TYPE)enCmd_List;

    STg2_KN_GPU_EXT_CXT_CMD_P           psEXT_CXT_CMD;
    ID3D12Device10_P                    psDX12_Device;
    TgUINT_E32                          uiNodeMask;
    union
    {
        UTg2_KN_GPU_CMD                         uCmd;
        STg2_UT_ST__ST_Node_P                   psNode;
    }                                   sCMD;
    union
    {
        STg2_KN_GPU_EXT_ST_Node_Cmd_Allocator_P psStack_Node;
        STg2_UT_ST__ST_Node_P                   psNode;
    }                                   sCmd_Allocator;
    union
    {
        STg2_KN_GPU_EXT_ST_Node_G_Cmd_List_P    psStack_Node;
        STg2_UT_ST__ST_Node_P                   psNode;
    }                                   sCmd_List;

    TgPARAM_VAR(STg2_KN_GPU_CXT_EXEC_PC psCXT_EXEC = g_asKN_GPU_CXT_EXEC + uiEXEC;)
    TgPARAM_CHECK_INDEX( uiEXEC, g_asKN_GPU_EXT_CXT_EXEC );
    TgPARAM_CHECK_INDEX( uiWORK, g_asKN_GPU_EXT_CXT_EXEC[uiEXEC].m_sContext_Command );
    TgPARAM_CHECK( tgKN_GPU_CXT_WORK_ID_Is_Equal( &psEXT_CXT_EXEC->m_sContext_Command[uiWORK].m_tiCXT_WORK_S, tiCXT_WORK ) );
    TgPARAM_CHECK( tgKN_GPU_CXT_EXEC_ID_Is_Equal( &psCXT_EXEC->m_tiCXT_EXEC_S, psEXT_CXT_EXEC->m_sContext_Command[uiWORK].m_tiCXT_EXEC ) );
    TgPARAM_CHECK( enCmd_List >= D3D12_COMMAND_LIST_TYPE_DIRECT && enCmd_List <= D3D12_COMMAND_LIST_TYPE_VIDEO_ENCODE );

    /* Acquire a command structure, allocator, and command list. */
    psEXT_CXT_CMD = psEXT_CXT_EXEC->m_sContext_Command + uiWORK;
    sCMD.psNode = tgCM_UT_LF__ST__Pop( &psEXT_CXT_EXEC->m_sCommand_Free_Stack.m_sStack );

    if (nullptr == sCMD.psNode)
    {
        goto tgKN_GPU_EXT__Execute__Command_List_Acquire_FAIL_0;
    };

    sCmd_Allocator.psNode = tgCM_UT_LF__ST__Pop( &psEXT_CXT_CMD->m_sCmd_Allocator_Free_Stack[enCmd_List].m_sStack );
    if (nullptr == sCmd_Allocator.psNode)
    {
        goto tgKN_GPU_EXT__Execute__Command_List_Acquire_FAIL_1;
    };

    sCmd_List.psNode = tgCM_UT_LF__ST__Pop( &psEXT_CXT_CMD->m_sCmd_List_Free_Stack[enCmd_List].m_sStack );
    if (nullptr == sCmd_List.psNode)
    {
        goto tgKN_GPU_EXT__Execute__Command_List_Acquire_FAIL_2;
    };

    /* Check to see if we need to initialize a new allocator or command list. */
    psDX12_Device = g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Adapter[psEXT_CXT_EXEC->m_uiAdapter_Index].m_psDX12_Device;
    uiNodeMask = psEXT_CXT_EXEC->m_uiNodeMask;
    if (nullptr == sCmd_Allocator.psStack_Node->m_psDX12)
    {
        ID3D12CommandAllocator_P            psDX12_Cmd_Allocator;

        if (FAILED( ID3D12Device10_CreateCommandAllocator( psDX12_Device, enDX12_Cmd_List, MS_REF IID_ID3D12CommandAllocator, (TgVOID_PP)(&psDX12_Cmd_Allocator) ) ))
        {
            goto tgKN_GPU_EXT__Execute__Command_List_Acquire_FAIL_3;
        };
        TgMACRO_KN_GPU_EXT_SET_NAME(psDX12_Cmd_Allocator,u8"Allocator: Execution Context, Command List Acquire")
        sCmd_Allocator.psStack_Node->m_psDX12 = psDX12_Cmd_Allocator;
    };

    if (nullptr == sCmd_List.psStack_Node->m_psDX12)
    {
        ID3D12GraphicsCommandList8_P        psDX12_Graphics_Cmd_List;

        if (FAILED( ID3D12Device10_CreateCommandList( psDX12_Device, uiNodeMask, enDX12_Cmd_List, sCmd_Allocator.psStack_Node->m_psDX12, nullptr,
                                                      MS_REF IID_ID3D12GraphicsCommandList8, (TgVOID_PP)(&psDX12_Graphics_Cmd_List) ) ))
        {
            goto tgKN_GPU_EXT__Execute__Command_List_Acquire_FAIL_3;
        };
        TgMACRO_KN_GPU_EXT_SET_NAME( psDX12_Graphics_Cmd_List, u8"Command List: Execution Context, Command List Acquire" );
        sCmd_List.psStack_Node->m_psDX12 = psDX12_Graphics_Cmd_List;
    }
    else
    {
        ID3D12GraphicsCommandList8_Reset( sCmd_List.psStack_Node->m_psDX12, sCmd_Allocator.psStack_Node->m_psDX12, nullptr );
    };

    /* Initialize the command structure. */
    sCMD.uCmd.psEXT->m_tiCXT_WORK = tiCXT_WORK;
    sCMD.uCmd.psEXT->m_enCmd = enCmd_List;
    sCMD.uCmd.psEXT->m_sEXT_Heap_RTV = psEXT_CXT_CMD->m_sRTV;
    sCMD.uCmd.psEXT->m_sEXT_Heap_CBV_SRV_UAV = psEXT_CXT_CMD->m_sCBV_SRV_UAV;
    sCMD.uCmd.psEXT->m_psDX12_Command_Allocator = sCmd_Allocator.psStack_Node->m_psDX12;
    sCMD.uCmd.psEXT->m_psNode_Command_Allocator = sCmd_Allocator.psNode;
    sCMD.uCmd.psEXT->m_psDX12_Graphics_Cmd_List = sCmd_List.psStack_Node->m_psDX12;
    sCMD.uCmd.psEXT->m_psNode_Graphics_Cmd_List = sCmd_List.psNode;
    sCMD.uCmd.psEXT->m_psDX12_Device =psDX12_Device;

    return (sCMD.uCmd);

tgKN_GPU_EXT__Execute__Command_List_Acquire_FAIL_3:
    tgCM_UT_LF__ST__Push( &psEXT_CXT_CMD->m_sCmd_List_Free_Stack[enCmd_List].m_sStack, sCmd_List.psNode );
tgKN_GPU_EXT__Execute__Command_List_Acquire_FAIL_2:
    tgCM_UT_LF__ST__Push( &psEXT_CXT_CMD->m_sCmd_Allocator_Free_Stack[enCmd_List].m_sStack, sCmd_Allocator.psNode );
tgKN_GPU_EXT__Execute__Command_List_Acquire_FAIL_1:
    tgCM_UT_LF__ST__Push( &psEXT_CXT_EXEC->m_sCommand_Free_Stack.m_sStack, sCMD.psNode );
tgKN_GPU_EXT__Execute__Command_List_Acquire_FAIL_0:
    sCMD.uCmd.ps = nullptr;
    return (sCMD.uCmd);
}


/* ---- tgKN_GPU_EXT__CMD__Command_List_Close ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_EXT__CMD__Command_List_Close( UTg2_KN_GPU_CMD_C uCMD )
{
    TgRSIZE                             uiEXEC = (uCMD.psEXT->m_tiCXT_WORK.m_uiI >> 16) & 0xFFFF;
    TgRSIZE                             uiWORK = (uCMD.psEXT->m_tiCXT_WORK.m_uiI & 0xFFFF) % KTgKN_GPU_MAX_EXEC_CONTEXT_COMMAND;
    STg2_KN_GPU_EXT_CXT_EXEC_PC         psEXT_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + uiEXEC;
    STg2_KN_GPU_EXT_CXT_CMD_P           psEXT_CXT_CMD;

    TgPARAM_VAR(STg2_KN_GPU_CXT_EXEC_PC psCXT_EXEC = g_asKN_GPU_CXT_EXEC + uiEXEC;)
    TgPARAM_CHECK_INDEX( uiEXEC, g_asKN_GPU_EXT_CXT_EXEC );
    TgPARAM_CHECK_INDEX( uiWORK, g_asKN_GPU_EXT_CXT_EXEC[uiEXEC].m_sContext_Command );
    TgPARAM_CHECK( tgKN_GPU_CXT_WORK_ID_Is_Equal( &psEXT_CXT_EXEC->m_sContext_Command[uiWORK].m_tiCXT_WORK_S, uCMD.psEXT->m_tiCXT_WORK ) );
    TgPARAM_CHECK( tgKN_GPU_CXT_EXEC_ID_Is_Equal( &psCXT_EXEC->m_tiCXT_EXEC_S, psEXT_CXT_EXEC->m_sContext_Command[uiWORK].m_tiCXT_EXEC ) );
    TgPARAM_CHECK( uCMD.psEXT->m_enCmd <= D3D12_COMMAND_LIST_TYPE_VIDEO_ENCODE );

    psEXT_CXT_CMD = psEXT_CXT_EXEC->m_sContext_Command + uiWORK;

    /* Close and schedule the command list. */

    ID3D12GraphicsCommandList8_Close( uCMD.psEXT->m_psDX12_Graphics_Cmd_List );
    ID3D12CommandQueue_ExecuteCommandLists( psEXT_CXT_EXEC->m_sCmd_Queue[uCMD.psEXT->m_enCmd].m_psDX12_Cmd_Queue, 1,
                                            (ID3D12CommandList_PP)&uCMD.psEXT->m_psDX12_Graphics_Cmd_List );

    /* Return the resources to their free|used lists. */

    tgCM_UT_LF__ST__Push( &psEXT_CXT_CMD->m_sCmd_Allocator_Free_Stack[uCMD.psEXT->m_enCmd].m_sStack, uCMD.psEXT->m_psNode_Command_Allocator );
    tgCM_UT_LF__ST__Push( &psEXT_CXT_CMD->m_sCmd_List_Used_Stack[uCMD.psEXT->m_enCmd].m_sStack, uCMD.psEXT->m_psNode_Graphics_Cmd_List );

    uCMD.psEXT->m_enCmd = D3D12_COMMAND_LIST_TYPE_VIDEO_ENCODE + 1;
    uCMD.psEXT->m_psDX12_Command_Allocator = nullptr;
    uCMD.psEXT->m_psNode_Command_Allocator = nullptr;
    uCMD.psEXT->m_psDX12_Graphics_Cmd_List = nullptr;
    uCMD.psEXT->m_psNode_Graphics_Cmd_List = nullptr;

    tgCM_UT_LF__ST__Push( &psEXT_CXT_EXEC->m_sCommand_Free_Stack.m_sStack, &uCMD.ps->m_sNext );

}


/* ---- tgKN_GPU_EXT__Execute__Register_Resource_For_Release --------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_EXT__Execute__Register_Resource_For_Release( UTg2_KN_GPU_CMD_C uCMD, ID3D12Resource_P psDX12_Resource )
{
    TgRSIZE                             uiEXEC = (uCMD.psEXT->m_tiCXT_WORK.m_uiI >> 16) & 0xFFFF;
    STg2_KN_GPU_EXT_CXT_EXEC_PC         psEXT_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + uiEXEC;

    TgPARAM_VAR(STg2_KN_GPU_CXT_EXEC_PC psCXT_EXEC = g_asKN_GPU_CXT_EXEC + uiEXEC;)
    TgPARAM_VAR(TgRSIZE uiWORK = (uCMD.psEXT->m_tiCXT_WORK.m_uiI & 0xFFFF) % KTgKN_GPU_MAX_EXEC_CONTEXT_COMMAND;)
    TgPARAM_CHECK_INDEX( uiEXEC, g_asKN_GPU_EXT_CXT_EXEC );
    TgPARAM_CHECK_INDEX( uiWORK, g_asKN_GPU_EXT_CXT_EXEC[uiEXEC].m_sContext_Command );
    TgPARAM_CHECK( tgKN_GPU_CXT_WORK_ID_Is_Equal( &psEXT_CXT_EXEC->m_sContext_Command[uiWORK].m_tiCXT_WORK_S, uCMD.psEXT->m_tiCXT_WORK ) );
    TgPARAM_CHECK( tgKN_GPU_CXT_EXEC_ID_Is_Equal( &psCXT_EXEC->m_tiCXT_EXEC_S, psEXT_CXT_EXEC->m_sContext_Command[uiWORK].m_tiCXT_EXEC ) );
    TgPARAM_CHECK( uCMD.psEXT->m_enCmd <= D3D12_COMMAND_LIST_TYPE_VIDEO_ENCODE );

    {
        STg2_KN_GPU_EXT_Release_Resource_PC psEXT_Release_Resource = psEXT_CXT_EXEC->m_asRelease_Resource + psEXT_CXT_EXEC->m_uiRelease_Resource_Producer_Index;

        tgCM_UT_LF__SN__Lock_Spin( &psEXT_CXT_EXEC->m_sRelease_Resource_Lock.m_sLock );

        /* If we have exceeded the size of the array, we will do an immediate flush and wait. */
        if (nullptr != psEXT_Release_Resource->m_psDX12_Resource)
        {
            D3D12_COMMAND_LIST_TYPE             enCmd = (D3D12_COMMAND_LIST_TYPE)psEXT_Release_Resource->m_enCmd;
            TgUINT_E64                          uiPrevious_Fence_Value = psEXT_Release_Resource->m_uiFence_Value;

            STg2_KN_GPU_EXT_CMD_Queue_P         psEXT_Queue;
            TgUINT_E64                          uiFence_Value;

            psEXT_Queue = &psEXT_CXT_EXEC->m_sCmd_Queue[enCmd];

            uiFence_Value = atomic_fetch_add( &psEXT_Queue->m_xuiFence_Value, 1 );
            TgVERIFY( SUCCEEDED( ID3D12CommandQueue_Signal( psEXT_Queue->m_psDX12_Cmd_Queue, psEXT_Queue->m_psDX12_Fence, uiFence_Value ) ) );
            do {
                TgVERIFY( SUCCEEDED( ID3D12Fence_SetEventOnCompletion( psEXT_Queue->m_psDX12_Fence, uiFence_Value, psEXT_Queue->m_psFence_Event ) ) );
                g_pfnWaitForSingleObjectEx( psEXT_Queue->m_psFence_Event, 1, FALSE );
            } while (ID3D12Fence_GetCompletedValue( psEXT_Queue->m_psDX12_Fence ) < uiFence_Value);
            TgVERIFY( uiPrevious_Fence_Value <= uiFence_Value );
            TgVERIFY( ID3D12Fence_GetCompletedValue( psEXT_CXT_EXEC->m_sCmd_Queue[enCmd].m_psDX12_Fence ) == uiFence_Value );

            ID3D12Resource_Release( psEXT_Release_Resource->m_psDX12_Resource );
            psEXT_Release_Resource->m_psDX12_Resource = nullptr;
        };

        psEXT_Release_Resource->m_psDX12_Resource = psDX12_Resource;
        psEXT_Release_Resource->m_enCmd = uCMD.psEXT->m_enCmd;
        psEXT_Release_Resource->m_uiFence_Value = atomic_load( &psEXT_CXT_EXEC->m_sCmd_Queue[uCMD.psEXT->m_enCmd].m_xuiFence_Value );

        psEXT_CXT_EXEC->m_uiRelease_Resource_Producer_Index = (psEXT_CXT_EXEC->m_uiRelease_Resource_Producer_Index + 1) % KTgKN_GPU_MAX_RELEASE_RESOURCE;

        tgCM_UT_LF__SN__Signal( &psEXT_CXT_EXEC->m_sRelease_Resource_Lock.m_sLock );
    }
}


/* ---- tgKN_GPU_EXT__Execute__Get_DX12_Device ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
ID3D12Device10_P tgKN_GPU_EXT__Execute__Get_DX12_Device( TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC )
{
    STg2_KN_GPU_CXT_EXEC_PC             psCXT_EXEC = g_asKN_GPU_CXT_EXEC + tiCXT_EXEC.m_uiI;
    TgPARAM_CHECK_INDEX( tiCXT_EXEC.m_uiI, g_asKN_GPU_CXT_EXEC );
    TgPARAM_CHECK( tgKN_GPU_CXT_EXEC_ID_Is_Equal( &(g_asKN_GPU_CXT_EXEC[tiCXT_EXEC.m_uiI].m_tiCXT_EXEC_S), tiCXT_EXEC ) );
    return (g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Adapter[psCXT_EXEC->m_uiAdapter_Index].m_psDX12_Device);
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal GPU Functions                                                                                                                                                         */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_GPU_EXT__Execute__Init ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_EXT__Execute__Init( TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC )
{
    STg2_KN_GPU_EXT_CXT_EXEC_PC         psEXT_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + tiCXT_EXEC.m_uiI;
    STg2_KN_GPU_CXT_EXEC_PC             psCXT_EXEC = g_asKN_GPU_CXT_EXEC + tiCXT_EXEC.m_uiI;

    ID3D12Device10_P                    psDX12_Device;
    TgRSIZE                             uiIndex;
    TgUINT_E32                          uiNodeMask;
    D3D12_DESCRIPTOR_HEAP_DESC          sDX12_Heap;
    HRESULT                             iRet;
    D3D12_CPU_DESCRIPTOR_HANDLE         sDX12_CPU, sDX12_CPU_Index;
    D3D12_SHADER_RESOURCE_VIEW_DESC     sDX12_SRV_Null;

    /* Create the standard DXGI and D3D12 resources needed for working with the GPU */

    TgPARAM_CHECK_INDEX( tiCXT_EXEC.m_uiI, g_asKN_GPU_CXT_EXEC );
    TgPARAM_CHECK( tgKN_GPU_CXT_EXEC_ID_Is_Equal( &(g_asKN_GPU_CXT_EXEC[tiCXT_EXEC.m_uiI].m_tiCXT_EXEC_S), tiCXT_EXEC ) );
    psDX12_Device = g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Adapter[psCXT_EXEC->m_uiAdapter_Index].m_psDX12_Device;
    uiNodeMask = psCXT_EXEC->m_uiNodeMask;

    tgMM_Set_U08_0x00( psEXT_CXT_EXEC, sizeof( STg2_KN_GPU_EXT_CXT_EXEC ) );

    psEXT_CXT_EXEC->m_tiID = tiCXT_EXEC;
    psEXT_CXT_EXEC->m_uiAdapter_Index = psCXT_EXEC->m_uiAdapter_Index;
    psEXT_CXT_EXEC->m_uiNodeMask = uiNodeMask;

    /* Frame Command Queues */
    for (uiIndex = D3D12_COMMAND_LIST_TYPE_DIRECT; uiIndex <= D3D12_COMMAND_LIST_TYPE_VIDEO_ENCODE; ++uiIndex)
    {
        tgKN_GPU_EXT_Command_Queue_Init( &psEXT_CXT_EXEC->m_sCmd_Queue[uiIndex], psDX12_Device, (D3D12_COMMAND_LIST_TYPE)uiIndex, uiNodeMask );
    #if defined(TgCOMPILE__GPU_OBJECT_NAME) && TgCOMPILE__GPU_OBJECT_NAME
        {
            TgCHAR_U8                           uszList[D3D12_COMMAND_LIST_TYPE_VIDEO_ENCODE+1][32] = { u8"DIRECT", u8"BUNDLE", u8"COMPUTE", u8"COPY", u8"VIDEO_DECODE",
                                                                                                        u8"VIDEO_PROCESS", u8"VIDEO_ENCODE" };
            TgCHAR_U8                           uszDebugName[128];

            if (psEXT_CXT_EXEC->m_sCmd_Queue[uiIndex].m_psDX12_Cmd_Queue)
            {
                tgUSZ_PrintF( uszDebugName, sizeof(uszDebugName), u8"Execution Context: Command Queue (%s) (%d)", uszList[uiIndex], tiCXT_EXEC.m_uiI );
                TgMACRO_KN_GPU_EXT_SET_NAME_WTH_VAR( psEXT_CXT_EXEC->m_sCmd_Queue[uiIndex].m_psDX12_Cmd_Queue, uszDebugName );
            };

            if (psEXT_CXT_EXEC->m_sCmd_Queue[uiIndex].m_psDX12_Fence)
            {
                tgUSZ_PrintF( uszDebugName, sizeof(uszDebugName), u8"Execution Context: Command Queue Fence (%s) (%d)", uszList[uiIndex], tiCXT_EXEC.m_uiI );
                TgMACRO_KN_GPU_EXT_SET_NAME_WTH_VAR( psEXT_CXT_EXEC->m_sCmd_Queue[uiIndex].m_psDX12_Fence, uszDebugName );
            };
        };
    /*# defined(TgCOMPILE__GPU_OBJECT_NAME) && TgCOMPILE__GPU_OBJECT_NAME */
    #endif
    };

    /* Initialize the Frame Data lock free stacks for Command Allocators and Command Queues. */
    for (uiIndex = 0; uiIndex < KTgKN_GPU_MAX_EXEC_CONTEXT_COMMAND; ++uiIndex)
    {
        if (TgFAILED( tgKN_GPU_EXT_Context_Command_Init( tiCXT_EXEC, psEXT_CXT_EXEC->m_sContext_Command + uiIndex ) ))
        {
            tgKN_GPU_EXT__Execute__Free( tiCXT_EXEC );
            return (KTgE_FAIL);
        };
    };

    tgCM_UT_LF__SN__Init( &psEXT_CXT_EXEC->m_sRelease_Resource_Lock.m_sLock );
    tgCM_UT_LF__ST__Init_PreLoad( &psEXT_CXT_EXEC->m_sCommand_Free_Stack.m_sStack, psEXT_CXT_EXEC->m_asComand, sizeof( STg2_KN_GPU_EXT_CMD ),
                                  TgARRAY_COUNT( psEXT_CXT_EXEC->m_asComand ) );

    tgKN_GPU_EXT_Create_Default_Root_Signature( tiCXT_EXEC );
    tgKN_GPU_EXT_Create_Default_PSO( tiCXT_EXEC );

    /* Create descriptor heaps. */

    tgMM_Set_U08_0x00( &sDX12_Heap, sizeof( sDX12_Heap ) );
    sDX12_Heap.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
    sDX12_Heap.NodeMask = psEXT_CXT_EXEC->m_uiNodeMask;
    sDX12_Heap.NumDescriptors = KTgMACRO_KN_GPU_EXT_MAX_DEFAULT_SRV_CBE + KTgMACRO_KN_GPU_EXT_MAX_DEFAULT_SRV_VOL + KTgMACRO_KN_GPU_EXT_MAX_DEFAULT_SRV_IMG;
    sDX12_Heap.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;

    iRet = ID3D12Device10_CreateDescriptorHeap( psDX12_Device, &sDX12_Heap, MS_REF IID_ID3D12DescriptorHeap, (TgVOID_PP)&psEXT_CXT_EXEC->m_sSRV.m_psDX12_Heap );
    TgVERIFY(SUCCEEDED(iRet));
    TgMACRO_KN_GPU_EXT_SET_NAME( psEXT_CXT_EXEC->m_sSRV.m_psDX12_Heap, u8"Execution Context: Default Heap CBV SRV UAV" );
    ID3D12DescriptorHeap_GetCPUDescriptorHandleForHeapStart( psEXT_CXT_EXEC->m_sSRV.m_psDX12_Heap, &sDX12_CPU );

    psEXT_CXT_EXEC->m_sSRV.m_uiDescriptor_Size = ID3D12Device10_GetDescriptorHandleIncrementSize( psDX12_Device, sDX12_Heap.Type );

    psEXT_CXT_EXEC->m_sSRV.m_anuiMax[KTgKN_GPU_SRV_TX_CBE] = (TgRSIZE)KTgMACRO_KN_GPU_EXT_MAX_DEFAULT_SRV_CBE;
    psEXT_CXT_EXEC->m_sSRV.m_asDX12_CPU[KTgKN_GPU_SRV_TX_CBE] = sDX12_CPU;
    psEXT_CXT_EXEC->m_sSRV.m_auiMax[KTgKN_GPU_SRV_TX_CBE]  = sDX12_CPU.ptr;
    psEXT_CXT_EXEC->m_sSRV.m_auiMax[KTgKN_GPU_SRV_TX_CBE] += psEXT_CXT_EXEC->m_sSRV.m_uiDescriptor_Size * psEXT_CXT_EXEC->m_sSRV.m_anuiMax[KTgKN_GPU_SRV_TX_CBE];

    psEXT_CXT_EXEC->m_sSRV.m_anuiMax[KTgKN_GPU_SRV_TX_VOL] = (TgRSIZE)KTgMACRO_KN_GPU_EXT_MAX_DEFAULT_SRV_VOL;
    psEXT_CXT_EXEC->m_sSRV.m_asDX12_CPU[KTgKN_GPU_SRV_TX_VOL].ptr = psEXT_CXT_EXEC->m_sSRV.m_auiMax[KTgKN_GPU_SRV_TX_CBE];
    psEXT_CXT_EXEC->m_sSRV.m_auiMax[KTgKN_GPU_SRV_TX_VOL]  = psEXT_CXT_EXEC->m_sSRV.m_asDX12_CPU[KTgKN_GPU_SRV_TX_VOL].ptr;
    psEXT_CXT_EXEC->m_sSRV.m_auiMax[KTgKN_GPU_SRV_TX_VOL] += psEXT_CXT_EXEC->m_sSRV.m_uiDescriptor_Size * psEXT_CXT_EXEC->m_sSRV.m_anuiMax[KTgKN_GPU_SRV_TX_VOL];

    psEXT_CXT_EXEC->m_sSRV.m_anuiMax[KTgKN_GPU_SRV_TX_IMG] = (TgRSIZE)KTgMACRO_KN_GPU_EXT_MAX_DEFAULT_SRV_IMG;
    psEXT_CXT_EXEC->m_sSRV.m_asDX12_CPU[KTgKN_GPU_SRV_TX_IMG].ptr = psEXT_CXT_EXEC->m_sSRV.m_auiMax[KTgKN_GPU_SRV_TX_VOL];
    psEXT_CXT_EXEC->m_sSRV.m_auiMax[KTgKN_GPU_SRV_TX_IMG]  = psEXT_CXT_EXEC->m_sSRV.m_asDX12_CPU[KTgKN_GPU_SRV_TX_IMG].ptr;
    psEXT_CXT_EXEC->m_sSRV.m_auiMax[KTgKN_GPU_SRV_TX_IMG] += psEXT_CXT_EXEC->m_sSRV.m_uiDescriptor_Size * psEXT_CXT_EXEC->m_sSRV.m_anuiMax[KTgKN_GPU_SRV_TX_IMG];

    tgMM_Set_U08_0x00( &sDX12_SRV_Null, sizeof( sDX12_SRV_Null ) );
    sDX12_SRV_Null.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
    sDX12_SRV_Null.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
    sDX12_SRV_Null.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sDX12_SRV_Null.Texture2D.MipLevels = 1;
    sDX12_SRV_Null.Texture2D.MostDetailedMip = 0;
    sDX12_SRV_Null.Texture2D.ResourceMinLODClamp = 0.0f;

    sDX12_CPU_Index = sDX12_CPU;
    for ( uiIndex = 0; uiIndex < psEXT_CXT_EXEC->m_sSRV.m_anuiMax[KTgKN_GPU_SRV_TX_CBE]; ++uiIndex, sDX12_CPU_Index.ptr += psEXT_CXT_EXEC->m_sSRV.m_uiDescriptor_Size)
    {
        ID3D12Device10_CreateShaderResourceView( psDX12_Device, nullptr, &sDX12_SRV_Null, sDX12_CPU_Index );
    };

    for ( uiIndex = 0; uiIndex < psEXT_CXT_EXEC->m_sSRV.m_anuiMax[KTgKN_GPU_SRV_TX_VOL]; ++uiIndex, sDX12_CPU_Index.ptr += psEXT_CXT_EXEC->m_sSRV.m_uiDescriptor_Size)
    {
        ID3D12Device10_CreateShaderResourceView( psDX12_Device, nullptr, &sDX12_SRV_Null, sDX12_CPU_Index );
    };

    for ( uiIndex = 0; uiIndex < psEXT_CXT_EXEC->m_sSRV.m_anuiMax[KTgKN_GPU_SRV_TX_IMG]; ++uiIndex, sDX12_CPU_Index.ptr += psEXT_CXT_EXEC->m_sSRV.m_uiDescriptor_Size)
    {
        ID3D12Device10_CreateShaderResourceView( psDX12_Device, nullptr, &sDX12_SRV_Null, sDX12_CPU_Index );
    };

    return (KTgS_OK);
}


/* ---- tgKN_GPU_EXT__Execute__Free ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_EXT__Execute__Free( TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC )
{
    STg2_KN_GPU_EXT_CXT_EXEC_PC         psEXT_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + tiCXT_EXEC.m_uiI;
    TgSINT_E32                          iIndex;

    TgPARAM_CHECK_INDEX( tiCXT_EXEC.m_uiI, g_asKN_GPU_CXT_EXEC );
    TgPARAM_CHECK( tgKN_GPU_CXT_EXEC_ID_Is_Equal( &(g_asKN_GPU_CXT_EXEC[tiCXT_EXEC.m_uiI].m_tiCXT_EXEC_S), tiCXT_EXEC ) );

    /* PSO */
    for (iIndex = 0; iIndex < (TgSINT_E32)TgARRAY_COUNT(psEXT_CXT_EXEC->m_psDX12_PSO); ++iIndex)
    {
        TgRSIZE                             uiRTScanOut;

        for (uiRTScanOut = 0; uiRTScanOut < TgARRAY_COUNT(psEXT_CXT_EXEC->m_psDX12_PSO[iIndex]); ++uiRTScanOut)
        {
            TgRSIZE                             uiDSScanOut;

            for (uiDSScanOut = 0; uiDSScanOut < TgARRAY_COUNT(psEXT_CXT_EXEC->m_psDX12_PSO[iIndex][uiRTScanOut]); ++uiDSScanOut)
            {
                if (nullptr == psEXT_CXT_EXEC->m_psDX12_PSO[iIndex][uiRTScanOut][uiDSScanOut])
                    continue;
                ID3D12PipelineState_Release( psEXT_CXT_EXEC->m_psDX12_PSO[iIndex][uiRTScanOut][uiDSScanOut] );
            }
        }
    }

    /* Root Signatures */
    for (iIndex = 0; iIndex < (TgSINT_E32)TgARRAY_COUNT(psEXT_CXT_EXEC->m_asRoot_Signature); ++iIndex)
    {
        if (nullptr == psEXT_CXT_EXEC->m_asRoot_Signature[iIndex].m_psDX12_Root_Signature)
            continue;
        TgVERIFY(0 == ID3D12RootSignature_Release( psEXT_CXT_EXEC->m_asRoot_Signature[iIndex].m_psDX12_Root_Signature ));
    }

    /* Frame Data */
    for (iIndex = 0; iIndex < KTgKN_GPU_MAX_EXEC_CONTEXT_COMMAND; ++iIndex)
    {
        tgKN_GPU_EXT_Context_Command_Free( psEXT_CXT_EXEC->m_sContext_Command + iIndex );
    };

    /* Command Queues */
    for (iIndex = D3D12_COMMAND_LIST_TYPE_DIRECT; iIndex <= D3D12_COMMAND_LIST_TYPE_VIDEO_ENCODE; ++iIndex)
    {
        tgKN_GPU_EXT_Command_Queue_Free( &psEXT_CXT_EXEC->m_sCmd_Queue[iIndex] );
    };

    /* Descriptor heaps. */

    if (psEXT_CXT_EXEC->m_sSRV.m_psDX12_Heap)
    {
        ID3D12DescriptorHeap_Release( psEXT_CXT_EXEC->m_sSRV.m_psDX12_Heap );
    }

    tgMM_Set_U08_0x00( psEXT_CXT_EXEC, sizeof( STg2_KN_GPU_EXT_CXT_EXEC ) );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_GPU_EXT_Command_Queue_Init ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgKN_GPU_EXT_Command_Queue_Init( STg2_KN_GPU_EXT_CMD_Queue_PC psCmd_Queue, ID3D12Device10_P psDX12_Device, D3D12_COMMAND_LIST_TYPE enCmd_List,
                                               TgUINT_E32_C uiNodeMask )
{
    D3D12_COMMAND_QUEUE_DESC            sDX12_Queue;
    TgUINT_E64                          uiFence_Value;

    TgPARAM_CHECK( nullptr != psCmd_Queue );
    TgPARAM_CHECK( enCmd_List <= D3D12_COMMAND_LIST_TYPE_VIDEO_ENCODE );

    if (D3D12_COMMAND_LIST_TYPE_BUNDLE == enCmd_List)
        return;

    tgMM_Set_U08_0x00( &sDX12_Queue, sizeof( sDX12_Queue ) );

    sDX12_Queue.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    sDX12_Queue.NodeMask = uiNodeMask;
    sDX12_Queue.Type = enCmd_List;

    if (SUCCEEDED( ID3D12Device10_CreateCommandQueue( psDX12_Device, &sDX12_Queue, MS_REF IID_ID3D12CommandQueue, (TgVOID_PP)&psCmd_Queue->m_psDX12_Cmd_Queue ) ))
    {
        uiFence_Value = atomic_fetch_add( &psCmd_Queue->m_xuiFence_Value, 1 );
        TgVERIFY( SUCCEEDED( ID3D12Device10_CreateFence( psDX12_Device, uiFence_Value, D3D12_FENCE_FLAG_NONE, MS_REF IID_ID3D12Fence, (TgVOID_PP)&psCmd_Queue->m_psDX12_Fence ) ) );
        psCmd_Queue->m_psFence_Event = g_pfnCreateEvent( nullptr, FALSE, FALSE, nullptr );
    };
}


/* ---- tgKN_GPU_EXT_Command_Queue_Free ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgKN_GPU_EXT_Command_Queue_Free( STg2_KN_GPU_EXT_CMD_Queue_PC psCmd_Queue )
{
    if (nullptr != psCmd_Queue->m_psDX12_Cmd_Queue)
        TgVERIFY( 0 == ID3D12CommandQueue_Release( psCmd_Queue->m_psDX12_Cmd_Queue ) );
    if (nullptr != psCmd_Queue->m_psDX12_Fence)
        TgVERIFY( 0 == ID3D12Fence_Release( psCmd_Queue->m_psDX12_Fence ) );
    if (nullptr != psCmd_Queue->m_psFence_Event)
        g_pfnCloseHandle( psCmd_Queue->m_psFence_Event );
}


/* ---- tgKN_GPU_EXT_Context_Command_Cmd_Allocators_Init ------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgKN_GPU_EXT_Context_Command_Cmd_Allocators_Init( STg2_KN_GPU_EXT_CXT_CMD_PC psEXT_CXT_CMD )
{
    /* Add the allocator pools to the lock free stacks. */
    tgCM_UT_LF__ST__Init_PreLoad( &psEXT_CXT_CMD->m_sCmd_Allocator_Free_Stack[D3D12_COMMAND_LIST_TYPE_DIRECT].m_sStack, psEXT_CXT_CMD->m_asCmd_Allocator__Direct,
                                  sizeof( STg2_KN_GPU_EXT_ST_Node_Cmd_Allocator ), TgARRAY_COUNT( psEXT_CXT_CMD->m_asCmd_Allocator__Direct ) );

    tgCM_UT_LF__ST__Init_PreLoad( &psEXT_CXT_CMD->m_sCmd_Allocator_Free_Stack[D3D12_COMMAND_LIST_TYPE_BUNDLE].m_sStack, psEXT_CXT_CMD->m_asCmd_Allocator__Bundle,
                                  sizeof( STg2_KN_GPU_EXT_ST_Node_Cmd_Allocator ), TgARRAY_COUNT( psEXT_CXT_CMD->m_asCmd_Allocator__Bundle ) );

    tgCM_UT_LF__ST__Init_PreLoad( &psEXT_CXT_CMD->m_sCmd_Allocator_Free_Stack[D3D12_COMMAND_LIST_TYPE_COMPUTE].m_sStack, psEXT_CXT_CMD->m_asCmd_Allocator__Compute,
                                  sizeof( STg2_KN_GPU_EXT_ST_Node_Cmd_Allocator ), TgARRAY_COUNT( psEXT_CXT_CMD->m_asCmd_Allocator__Compute ) );

    tgCM_UT_LF__ST__Init_PreLoad( &psEXT_CXT_CMD->m_sCmd_Allocator_Free_Stack[D3D12_COMMAND_LIST_TYPE_COPY].m_sStack, psEXT_CXT_CMD->m_asCmd_Allocator__Copy,
                                  sizeof( STg2_KN_GPU_EXT_ST_Node_Cmd_Allocator ), TgARRAY_COUNT( psEXT_CXT_CMD->m_asCmd_Allocator__Copy ) );

    tgCM_UT_LF__ST__Init_PreLoad( &psEXT_CXT_CMD->m_sCmd_Allocator_Free_Stack[D3D12_COMMAND_LIST_TYPE_VIDEO_DECODE].m_sStack, psEXT_CXT_CMD->m_asCmd_Allocator__Video_Decode,
                                  sizeof( STg2_KN_GPU_EXT_ST_Node_Cmd_Allocator ), TgARRAY_COUNT( psEXT_CXT_CMD->m_asCmd_Allocator__Video_Decode ) );

    tgCM_UT_LF__ST__Init_PreLoad( &psEXT_CXT_CMD->m_sCmd_Allocator_Free_Stack[D3D12_COMMAND_LIST_TYPE_VIDEO_PROCESS].m_sStack, psEXT_CXT_CMD->m_asCmd_Allocator__Video_Process,
                                  sizeof( STg2_KN_GPU_EXT_ST_Node_Cmd_Allocator ), TgARRAY_COUNT( psEXT_CXT_CMD->m_asCmd_Allocator__Video_Process ) );

    tgCM_UT_LF__ST__Init_PreLoad( &psEXT_CXT_CMD->m_sCmd_Allocator_Free_Stack[D3D12_COMMAND_LIST_TYPE_VIDEO_ENCODE].m_sStack, psEXT_CXT_CMD->m_asCmd_Allocator__Video_Encode,
                                  sizeof( STg2_KN_GPU_EXT_ST_Node_Cmd_Allocator ), TgARRAY_COUNT( psEXT_CXT_CMD->m_asCmd_Allocator__Video_Encode ) );
}


/* ---- tgKN_GPU_EXT_Context_Command_Cmd_Lists_Init ------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgKN_GPU_EXT_Context_Command_Cmd_Lists_Init( STg2_KN_GPU_EXT_CXT_CMD_PC psEXT_CXT_CMD )
{
    TgSINT_E32                          iIndex;

    /* Initialize the used stacks. */
    for (iIndex = D3D12_COMMAND_LIST_TYPE_DIRECT; iIndex <= D3D12_COMMAND_LIST_TYPE_VIDEO_ENCODE; ++iIndex)
    {
        tgCM_UT_LF__ST__Init( &psEXT_CXT_CMD->m_sCmd_List_Used_Stack[iIndex].m_sStack );
    };

    /* Add the command list pools to the lock free stacks. */
    tgCM_UT_LF__ST__Init_PreLoad( &psEXT_CXT_CMD->m_sCmd_List_Free_Stack[D3D12_COMMAND_LIST_TYPE_DIRECT].m_sStack, psEXT_CXT_CMD->m_asCmd_List__Direct,
                                  sizeof( STg2_KN_GPU_EXT_ST_Node_G_Cmd_List ), TgARRAY_COUNT( psEXT_CXT_CMD->m_asCmd_List__Direct ) );

    tgCM_UT_LF__ST__Init_PreLoad( &psEXT_CXT_CMD->m_sCmd_List_Free_Stack[D3D12_COMMAND_LIST_TYPE_BUNDLE].m_sStack, psEXT_CXT_CMD->m_asCmd_List__Bundle,
                                  sizeof( STg2_KN_GPU_EXT_ST_Node_G_Cmd_List ), TgARRAY_COUNT( psEXT_CXT_CMD->m_asCmd_List__Bundle ) );

    tgCM_UT_LF__ST__Init_PreLoad( &psEXT_CXT_CMD->m_sCmd_List_Free_Stack[D3D12_COMMAND_LIST_TYPE_COMPUTE].m_sStack, psEXT_CXT_CMD->m_asCmd_List__Compute,
                                  sizeof( STg2_KN_GPU_EXT_ST_Node_G_Cmd_List ), TgARRAY_COUNT( psEXT_CXT_CMD->m_asCmd_List__Compute ) );

    tgCM_UT_LF__ST__Init_PreLoad( &psEXT_CXT_CMD->m_sCmd_List_Free_Stack[D3D12_COMMAND_LIST_TYPE_COPY].m_sStack, psEXT_CXT_CMD->m_asCmd_List__Copy,
                                  sizeof( STg2_KN_GPU_EXT_ST_Node_G_Cmd_List ), TgARRAY_COUNT( psEXT_CXT_CMD->m_asCmd_List__Copy ) );

    tgCM_UT_LF__ST__Init_PreLoad( &psEXT_CXT_CMD->m_sCmd_List_Free_Stack[D3D12_COMMAND_LIST_TYPE_VIDEO_DECODE].m_sStack, psEXT_CXT_CMD->m_asCmd_List__Video_Decode,
                                  sizeof( STg2_KN_GPU_EXT_ST_Node_G_Cmd_List ), TgARRAY_COUNT( psEXT_CXT_CMD->m_asCmd_List__Video_Decode ) );

    tgCM_UT_LF__ST__Init_PreLoad( &psEXT_CXT_CMD->m_sCmd_List_Free_Stack[D3D12_COMMAND_LIST_TYPE_VIDEO_PROCESS].m_sStack, psEXT_CXT_CMD->m_asCmd_List__Video_Process,
                                  sizeof( STg2_KN_GPU_EXT_ST_Node_G_Cmd_List ), TgARRAY_COUNT( psEXT_CXT_CMD->m_asCmd_List__Video_Process ) );

    tgCM_UT_LF__ST__Init_PreLoad( &psEXT_CXT_CMD->m_sCmd_List_Free_Stack[D3D12_COMMAND_LIST_TYPE_VIDEO_ENCODE].m_sStack, psEXT_CXT_CMD->m_asCmd_List__Video_Encode,
                                  sizeof( STg2_KN_GPU_EXT_ST_Node_G_Cmd_List ), TgARRAY_COUNT( psEXT_CXT_CMD->m_asCmd_List__Video_Encode ) );
}


/* ---- tgKN_GPU_EXT_Context_Command_Init ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT tgKN_GPU_EXT_Context_Command_Init( TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC, STg2_KN_GPU_EXT_CXT_CMD_PC psEXT_CXT_CMD )
{
    STg2_KN_GPU_EXT_CXT_EXEC_PC         psEXT_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + tiCXT_EXEC.m_uiI;
    STg2_KN_GPU_CXT_EXEC_PC             psCXT_EXEC = g_asKN_GPU_CXT_EXEC + tiCXT_EXEC.m_uiI;

    D3D12_DESCRIPTOR_HEAP_DESC          sDX12_Heap;
    ID3D12Device10_P                    psDX12_Device;

    tgPM_MT_SM_Init( &psEXT_CXT_CMD->m_sLock, nullptr, 1, 1 );

    psDX12_Device = g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Adapter[psCXT_EXEC->m_uiAdapter_Index].m_psDX12_Device;

    /* Create descriptor heaps. */

    psEXT_CXT_CMD->m_sRTV.m_nuiMax = psCXT_EXEC->m_nuiMax_Render_Target_View;
    psEXT_CXT_CMD->m_sCBV_SRV_UAV.m_nuiMax = psCXT_EXEC->m_nuiMax_Shader_Resource_View;

    tgMM_Set_U08_0x00( &sDX12_Heap, sizeof( sDX12_Heap ) );
    sDX12_Heap.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
    sDX12_Heap.NodeMask = psEXT_CXT_EXEC->m_uiNodeMask;
    sDX12_Heap.NumDescriptors = (UINT)psEXT_CXT_CMD->m_sRTV.m_nuiMax;
    sDX12_Heap.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;

    if (FAILED( ID3D12Device10_CreateDescriptorHeap( psDX12_Device, &sDX12_Heap, MS_REF IID_ID3D12DescriptorHeap, (TgVOID_PP)&psEXT_CXT_CMD->m_sRTV.m_psDX12_Heap ) ))
    {
        return (KTgE_FAIL);
    };
    TgMACRO_KN_GPU_EXT_SET_NAME( psEXT_CXT_CMD->m_sRTV.m_psDX12_Heap, u8"tgKN_GPU_EXT_Context_Command_Init: RTV" );
    psEXT_CXT_CMD->m_sRTV.m_uiDescriptor_Size = ID3D12Device10_GetDescriptorHandleIncrementSize( psDX12_Device, sDX12_Heap.Type );
    ID3D12DescriptorHeap_GetCPUDescriptorHandleForHeapStart( psEXT_CXT_CMD->m_sRTV.m_psDX12_Heap, &psEXT_CXT_CMD->m_sRTV.m_sDX12_CPU_Handle );
    psEXT_CXT_CMD->m_sRTV.m_uiMax  = psEXT_CXT_CMD->m_sRTV.m_sDX12_CPU_Handle.ptr;
    psEXT_CXT_CMD->m_sRTV.m_uiMax += psEXT_CXT_CMD->m_sRTV.m_uiDescriptor_Size * psEXT_CXT_CMD->m_sRTV.m_nuiMax;

    tgMM_Set_U08_0x00( &sDX12_Heap, sizeof( sDX12_Heap ) );
    sDX12_Heap.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
    sDX12_Heap.NodeMask = psEXT_CXT_EXEC->m_uiNodeMask;
    sDX12_Heap.NumDescriptors = (UINT)psEXT_CXT_CMD->m_sCBV_SRV_UAV.m_nuiMax + (UINT)KTgKN_GPU_EXT_MAX_DEFAULT_SRV;
    sDX12_Heap.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;

    if (FAILED( ID3D12Device10_CreateDescriptorHeap( psDX12_Device, &sDX12_Heap, MS_REF IID_ID3D12DescriptorHeap, (TgVOID_PP)&psEXT_CXT_CMD->m_sCBV_SRV_UAV.m_psDX12_Heap ) ))
    {
        return (KTgE_FAIL);
    };
    TgMACRO_KN_GPU_EXT_SET_NAME( psEXT_CXT_CMD->m_sCBV_SRV_UAV.m_psDX12_Heap, u8"tgKN_GPU_EXT_Context_Command_Init: CBV SRV UAV" );
    psEXT_CXT_CMD->m_sCBV_SRV_UAV.m_uiDescriptor_Size = ID3D12Device10_GetDescriptorHandleIncrementSize( psDX12_Device, sDX12_Heap.Type );
    ID3D12DescriptorHeap_GetCPUDescriptorHandleForHeapStart( psEXT_CXT_CMD->m_sCBV_SRV_UAV.m_psDX12_Heap, &psEXT_CXT_CMD->m_sCBV_SRV_UAV.m_sDX12_CPU_Handle );
    psEXT_CXT_CMD->m_sCBV_SRV_UAV.m_uiMax = psEXT_CXT_CMD->m_sCBV_SRV_UAV.m_sDX12_CPU_Handle.ptr;
    psEXT_CXT_CMD->m_sCBV_SRV_UAV.m_uiMax += psEXT_CXT_CMD->m_sCBV_SRV_UAV.m_uiDescriptor_Size * psEXT_CXT_CMD->m_sCBV_SRV_UAV.m_nuiMax;

    tgKN_GPU_EXT_Context_Command_Cmd_Allocators_Init( psEXT_CXT_CMD );
    tgKN_GPU_EXT_Context_Command_Cmd_Lists_Init( psEXT_CXT_CMD );

    return (KTgS_OK);
}


/* ---- tgKN_GPU_EXT_Context_Command_Free ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgKN_GPU_EXT_Context_Command_Free( STg2_KN_GPU_EXT_CXT_CMD_PC psEXT_CXT_CMD )
{
    TgRSIZE                             uiIndex;

    for (uiIndex = 0; uiIndex < TgARRAY_COUNT( psEXT_CXT_CMD->m_asCmd_Allocator__Direct ); ++uiIndex)
    {
        if (psEXT_CXT_CMD->m_asCmd_Allocator__Direct[uiIndex].m_psDX12)
            TgVERIFY( 0 == ID3D12CommandAllocator_Release( psEXT_CXT_CMD->m_asCmd_Allocator__Direct[uiIndex].m_psDX12 ) );
    };
    for (uiIndex = 0; uiIndex < TgARRAY_COUNT( psEXT_CXT_CMD->m_asCmd_Allocator__Bundle ); ++uiIndex)
    {
        if (psEXT_CXT_CMD->m_asCmd_Allocator__Bundle[uiIndex].m_psDX12)
            TgVERIFY( 0 == ID3D12CommandAllocator_Release( psEXT_CXT_CMD->m_asCmd_Allocator__Bundle[uiIndex].m_psDX12 ) );
    };
    for (uiIndex = 0; uiIndex < TgARRAY_COUNT( psEXT_CXT_CMD->m_asCmd_Allocator__Compute ); ++uiIndex)
    {
        if (psEXT_CXT_CMD->m_asCmd_Allocator__Compute[uiIndex].m_psDX12)
            TgVERIFY( 0 == ID3D12CommandAllocator_Release( psEXT_CXT_CMD->m_asCmd_Allocator__Compute[uiIndex].m_psDX12 ) );
    };
    for (uiIndex = 0; uiIndex < TgARRAY_COUNT( psEXT_CXT_CMD->m_asCmd_Allocator__Copy ); ++uiIndex)
    {
        if (psEXT_CXT_CMD->m_asCmd_Allocator__Copy[uiIndex].m_psDX12)
            TgVERIFY( 0 == ID3D12CommandAllocator_Release( psEXT_CXT_CMD->m_asCmd_Allocator__Copy[uiIndex].m_psDX12 ) );
    };
    for (uiIndex = 0; uiIndex < TgARRAY_COUNT( psEXT_CXT_CMD->m_asCmd_Allocator__Video_Decode ); ++uiIndex)
    {
        if (psEXT_CXT_CMD->m_asCmd_Allocator__Video_Decode[uiIndex].m_psDX12)
            TgVERIFY( 0 == ID3D12CommandAllocator_Release( psEXT_CXT_CMD->m_asCmd_Allocator__Video_Decode[uiIndex].m_psDX12 ) );
    };
    for (uiIndex = 0; uiIndex < TgARRAY_COUNT( psEXT_CXT_CMD->m_asCmd_Allocator__Video_Process ); ++uiIndex)
    {
        if (psEXT_CXT_CMD->m_asCmd_Allocator__Video_Process[uiIndex].m_psDX12)
            TgVERIFY( 0 == ID3D12CommandAllocator_Release( psEXT_CXT_CMD->m_asCmd_Allocator__Video_Process[uiIndex].m_psDX12 ) );
    };
    for (uiIndex = 0; uiIndex < TgARRAY_COUNT( psEXT_CXT_CMD->m_asCmd_Allocator__Video_Encode ); ++uiIndex)
    {
        if (psEXT_CXT_CMD->m_asCmd_Allocator__Video_Encode[uiIndex].m_psDX12)
            TgVERIFY( 0 == ID3D12CommandAllocator_Release( psEXT_CXT_CMD->m_asCmd_Allocator__Video_Encode[uiIndex].m_psDX12 ) );
    };

    for (uiIndex = 0; uiIndex < TgARRAY_COUNT( psEXT_CXT_CMD->m_asCmd_List__Direct ); ++uiIndex)
    {
        if (psEXT_CXT_CMD->m_asCmd_List__Direct[uiIndex].m_psDX12)
            TgVERIFY( 0 == ID3D12GraphicsCommandList8_Release( psEXT_CXT_CMD->m_asCmd_List__Direct[uiIndex].m_psDX12 ) );
    };
    for (uiIndex = 0; uiIndex < TgARRAY_COUNT( psEXT_CXT_CMD->m_asCmd_List__Bundle ); ++uiIndex)
    {
        if (psEXT_CXT_CMD->m_asCmd_List__Bundle[uiIndex].m_psDX12)
            TgVERIFY( 0 == ID3D12GraphicsCommandList8_Release( psEXT_CXT_CMD->m_asCmd_List__Bundle[uiIndex].m_psDX12 ) );
    };
    for (uiIndex = 0; uiIndex < TgARRAY_COUNT( psEXT_CXT_CMD->m_asCmd_List__Compute ); ++uiIndex)
    {
        if (psEXT_CXT_CMD->m_asCmd_List__Compute[uiIndex].m_psDX12)
            TgVERIFY( 0 == ID3D12GraphicsCommandList8_Release( psEXT_CXT_CMD->m_asCmd_List__Compute[uiIndex].m_psDX12 ) );
    };
    for (uiIndex = 0; uiIndex < TgARRAY_COUNT( psEXT_CXT_CMD->m_asCmd_List__Copy ); ++uiIndex)
    {
        if (psEXT_CXT_CMD->m_asCmd_List__Copy[uiIndex].m_psDX12)
            TgVERIFY( 0 == ID3D12GraphicsCommandList8_Release( psEXT_CXT_CMD->m_asCmd_List__Copy[uiIndex].m_psDX12 ) );
    };
    for (uiIndex = 0; uiIndex < TgARRAY_COUNT( psEXT_CXT_CMD->m_asCmd_List__Video_Decode ); ++uiIndex)
    {
        if (psEXT_CXT_CMD->m_asCmd_List__Video_Decode[uiIndex].m_psDX12)
            TgVERIFY( 0 == ID3D12GraphicsCommandList8_Release( psEXT_CXT_CMD->m_asCmd_List__Video_Decode[uiIndex].m_psDX12 ) );
    };
    for (uiIndex = 0; uiIndex < TgARRAY_COUNT( psEXT_CXT_CMD->m_asCmd_List__Video_Process ); ++uiIndex)
    {
        if (psEXT_CXT_CMD->m_asCmd_List__Video_Process[uiIndex].m_psDX12)
            TgVERIFY( 0 == ID3D12GraphicsCommandList8_Release( psEXT_CXT_CMD->m_asCmd_List__Video_Process[uiIndex].m_psDX12 ) );
    };
    for (uiIndex = 0; uiIndex < TgARRAY_COUNT( psEXT_CXT_CMD->m_asCmd_List__Video_Encode ); ++uiIndex)
    {
        if (psEXT_CXT_CMD->m_asCmd_List__Video_Encode[uiIndex].m_psDX12)
            TgVERIFY( 0 == ID3D12GraphicsCommandList8_Release( psEXT_CXT_CMD->m_asCmd_List__Video_Encode[uiIndex].m_psDX12 ) );
    };

    if (nullptr != psEXT_CXT_CMD->m_sCBV_SRV_UAV.m_psDX12_Heap)
        TgVERIFY( 0 == ID3D12DescriptorHeap_Release( psEXT_CXT_CMD->m_sCBV_SRV_UAV.m_psDX12_Heap ) );
    if (nullptr != psEXT_CXT_CMD->m_sRTV.m_psDX12_Heap)
        TgVERIFY( 0 == ID3D12DescriptorHeap_Release( psEXT_CXT_CMD->m_sRTV.m_psDX12_Heap ) );

    tgPM_MT_SM_Free( &psEXT_CXT_CMD->m_sLock );
}


/* ---- tgKN_GPU_EXT__Execute__Process_Resource_Release_List --------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgKN_GPU_EXT__Execute__Process_Resource_Release_List( TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC )
{
    STg2_KN_GPU_EXT_CXT_EXEC_PC         psEXT_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + tiCXT_EXEC.m_uiI;

    TgRSIZE                             nuiLoop;

    TgPARAM_CHECK_INDEX( tiCXT_EXEC.m_uiI, g_asKN_GPU_EXT_CXT_EXEC );
    TgPARAM_CHECK( tgKN_GPU_CXT_EXEC_ID_Is_Equal( &(g_asKN_GPU_CXT_EXEC[tiCXT_EXEC.m_uiI].m_tiCXT_EXEC_S), tiCXT_EXEC ) );

    tgCM_UT_LF__SN__Lock_Spin( &psEXT_CXT_EXEC->m_sRelease_Resource_Lock.m_sLock );

    for (nuiLoop = 0; nuiLoop < KTgKN_GPU_MAX_RELEASE_RESOURCE; ++nuiLoop)
    {
        ID3D12Resource_P                    psDX12_Resource = psEXT_CXT_EXEC->m_asRelease_Resource[psEXT_CXT_EXEC->m_uiRelease_Resource_Consumer_Index].m_psDX12_Resource;
        D3D12_COMMAND_LIST_TYPE             enCmd = (D3D12_COMMAND_LIST_TYPE)psEXT_CXT_EXEC->m_asRelease_Resource[psEXT_CXT_EXEC->m_uiRelease_Resource_Consumer_Index].m_enCmd;
        TgUINT_E64                          uiFence_Value = psEXT_CXT_EXEC->m_asRelease_Resource[psEXT_CXT_EXEC->m_uiRelease_Resource_Consumer_Index].m_uiFence_Value;

        TgUINT_E64                          uiCompleted_Fence_Value = ID3D12Fence_GetCompletedValue( psEXT_CXT_EXEC->m_sCmd_Queue[enCmd].m_psDX12_Fence );

        if (nullptr == psDX12_Resource || uiFence_Value > uiCompleted_Fence_Value)
            break;

        ID3D12Resource_Release( psDX12_Resource );
        psEXT_CXT_EXEC->m_asRelease_Resource[psEXT_CXT_EXEC->m_uiRelease_Resource_Consumer_Index].m_psDX12_Resource = nullptr;

        psEXT_CXT_EXEC->m_uiRelease_Resource_Consumer_Index = (psEXT_CXT_EXEC->m_uiRelease_Resource_Consumer_Index + 1) % KTgKN_GPU_MAX_RELEASE_RESOURCE;
    };

    tgCM_UT_LF__SN__Signal( &psEXT_CXT_EXEC->m_sRelease_Resource_Lock.m_sLock );
}


