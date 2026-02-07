/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (VULKAN) Kernel [GPU] - System [Context] [EXEC].c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.22 | »GUID« 7ECEAB43-40E4-4161-8F94-87AF31F5BA9A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    Models:     Claude 3.7, Claude 4.0
    ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

static TgVOID
tgKN_GPU_VLKN_Context_Command_Init__Cmd_Pool_Lock_Free_Stacks(
    STg2_KN_GPU_VLKN_CXT_CMD_PC TgANALYSIS_NO_NULL ARG0 );

static TgRESULT
tgKN_GPU_VLKN_Context_Command_Init(
    VkDevice_C ARG0, STg2_KN_GPU_VLKN_CXT_CMD_PC TgANALYSIS_NO_NULL ARG1 );

static TgVOID
tgKN_GPU_VLKN_Context_Command_Free(
    TgKN_GPU_CXT_EXEC_ID_C ARG0, STg2_KN_GPU_VLKN_CXT_CMD_PC TgANALYSIS_NO_NULL ARG1 );

/** @brief Create default vertex, index, storage, and uniform buffers
    @param [in] ARG0 Device handle
    @param [in] ARG1 Vulkan Execution context pointer
    @return Result Code. */
static TgRESULT
tgKN_GPU_VLKN__Execute__Init__Create_Buffers(
    VkDevice_C ARG0, STg2_KN_GPU_VLKN_CMD_PC TgANALYSIS_NO_NULL ARG1, STg2_KN_GPU_VLKN_CXT_EXEC_PC TgANALYSIS_NO_NULL ARG2 );

/** @brief Create default command pools
    @param [in] ARG0 Device handle
    @param [in] ARG1 Vulkan Execution context pointer
    @return Result Code. */
static TgRESULT
tgKN_GPU_VLKN__Execute__Init__Create_Descriptor_Pool(
    VkDevice_C ARG0,  STg2_KN_GPU_VLKN_CXT_EXEC_PC TgANALYSIS_NO_NULL ARG1 );

/** @brief Create default descriptor set layouts
    @param [in] ARG0 Device handle
    @param [in] ARG1 Index of the Vulkan Execution Context
    @return Result Code. */
static TgRESULT
tgKN_GPU_VLKN__Execute__Init__Create_Descriptor_Sets(
    VkDevice_C ARG0, TgRSIZE_C ARG1 );

/** @brief Free default pipeline resources
    @param [in] ARG0 Execution context ID
    @return Result Code. */
static TgRESULT
tgKN_GPU_VLKN__Execute__Free__Destroy_Default_Resources(
    TgKN_GPU_CXT_EXEC_ID_C ARG0 );

static TgVOID
tgKN_GPU_VLKN__Execute__Process_Resource_Release_List(
    TgKN_GPU_CXT_EXEC_ID_C ARG0 );

/** @brief Create a Vulkan descriptor pool for a Command Context (see tgKN_GPU_EXT__WORK__Acquire_Command)
    @param [out] OUT0 Descriptor pool handle
    @param [in] ARG1 Device handle
    @return Result Code. */
static TgRESULT
tgKN_GPU_VLKN__Command_Context__Create_Default_Descriptor_Pool(
    VkDescriptorPool_P TgANALYSIS_NO_NULL OUT0, VkDevice ARG1 );


/** @brief Acquire a command buffer from a command pool
    @param [out] OUT0 Pointer to a stack node containing the command pool handle
    @param [out] OUT1 Pointer to a stack node containing the command buffer handle
    @param [in] ARG2 Pointer to the Vulkan execution context
    @param [in] ARG3 Pointer to the Vulkan command context
    @param [in] ARG4 Command queue type (Graphics, Compute, Transfer, Present) */
static TgVOID
tgKN_GPU_VLKN_Acquire_Command_Pool_Buffer(
    STg2_KN_GPU_VLKN_Node_Cmd_Pool_PP TgANALYSIS_NO_NULL OUT0, STg2_KN_GPU_VLKN_Node_Cmd_Buffer_PP TgANALYSIS_NO_NULL OUT1,
    STg2_KN_GPU_VLKN_CXT_EXEC_PC TgANALYSIS_NO_NULL ARG2, STg2_KN_GPU_VLKN_CXT_CMD_PC TgANALYSIS_NO_NULL ARG3, ETgKN_GPU_EXT_COMMAND_C ARG4 );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public GPU Functions - Execute                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_GPU_EXT__Execute__Cmd_Buffer_Flush ---------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_EXT__Execute__Cmd_Buffer_Flush(
    TgKN_GPU_CXT_EXEC_ID_C                      tiCXT_EXEC,
    ETgKN_GPU_EXT_COMMAND_C                     enCmd_List_Request )
{
    STg2_KN_GPU_VLKN_CXT_EXEC_PC                psVLKN_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + tiCXT_EXEC.m_uiI;

    STg2_KN_GPU_VLKN_CMD_Queue_P                psCMD_Queue;

    TgPARAM_CHECK_INDEX( tiCXT_EXEC.m_uiI, g_asKN_GPU_CXT_EXEC );
    TgPARAM_CHECK( tgKN_GPU_CXT_EXEC_ID_Is_Equal( &(g_asKN_GPU_CXT_EXEC[tiCXT_EXEC.m_uiI].m_tiCXT_EXEC_S), tiCXT_EXEC ) );
    TgPARAM_CHECK( enCmd_List_Request >= ETgKN_GPU_EXT_COMMAND_START && enCmd_List_Request < ETgKN_GPU_EXT_COMMAND_MAX );

    psCMD_Queue = psVLKN_CXT_EXEC->m_apsCmd_Queue[enCmd_List_Request];

    if (VK_NULL_HANDLE == psCMD_Queue->m_hVLKN_Queue)
    {
        return;
    }

    tgCM_UT_LF__SN__Lock_Spin( &psCMD_Queue->m_sLock.m_sLock );
    vkQueueWaitIdle(psCMD_Queue->m_hVLKN_Queue);
    tgCM_UT_LF__SN__Signal( &psCMD_Queue->m_sLock.m_sLock );

    tgKN_GPU_VLKN__Execute__Process_Resource_Release_List( tiCXT_EXEC );
}


/* ---- tgKN_GPU_EXT__Execute__Flush --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_EXT__Execute__Flush(
    TgKN_GPU_CXT_EXEC_ID_C                      tiCXT_EXEC )
{
    STg2_KN_GPU_VLKN_CXT_EXEC_PC                psVLKN_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + tiCXT_EXEC.m_uiI;

    TgRSIZE                                     uiIndex;

    TgPARAM_CHECK_INDEX( tiCXT_EXEC.m_uiI, g_asKN_GPU_CXT_EXEC );
    TgPARAM_CHECK( tgKN_GPU_CXT_EXEC_ID_Is_Equal( &(g_asKN_GPU_CXT_EXEC[tiCXT_EXEC.m_uiI].m_tiCXT_EXEC_S), tiCXT_EXEC ) );

    /* Lock all command queues to prevent multithread access */

    for (uiIndex = 0; uiIndex < TgARRAY_COUNT(psVLKN_CXT_EXEC->m_asCmd_Queue_Family_Indexed); ++uiIndex)
    {
        STg2_KN_GPU_VLKN_CMD_Queue_PC       psCMD_Queue = psVLKN_CXT_EXEC->m_asCmd_Queue_Family_Indexed + uiIndex;

        if (VK_NULL_HANDLE == psCMD_Queue->m_hVLKN_Queue)
        {
            continue;
        }
        tgCM_UT_LF__SN__Lock_Spin( &psCMD_Queue->m_sLock.m_sLock );
    }

    vkDeviceWaitIdle(psVLKN_CXT_EXEC->m_hVLKN_Device);

    for (uiIndex = 0; uiIndex < TgARRAY_COUNT(psVLKN_CXT_EXEC->m_asCmd_Queue_Family_Indexed); ++uiIndex)
    {
        STg2_KN_GPU_VLKN_CMD_Queue_PC       psCMD_Queue = psVLKN_CXT_EXEC->m_asCmd_Queue_Family_Indexed + uiIndex;

        if (VK_NULL_HANDLE == psCMD_Queue->m_hVLKN_Queue)
        {
            continue;
        }
        tgCM_UT_LF__SN__Signal( &psCMD_Queue->m_sLock.m_sLock );
    }

    tgKN_GPU_VLKN__Execute__Process_Resource_Release_List( tiCXT_EXEC );
}


/* ---- tgKN_GPU_EXT__Execute__Frame_Start --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgKN_GPU_CXT_WORK_ID tgKN_GPU_EXT__Execute__Frame_Start(
    TgKN_GPU_CXT_EXEC_ID_C                      tiCXT_EXEC )
{
    TgPARAM_CHECK_INDEX( tiCXT_EXEC.m_uiI, g_asKN_GPU_CXT_EXEC );
    TgPARAM_CHECK( tgKN_GPU_CXT_EXEC_ID_Is_Equal( &(g_asKN_GPU_CXT_EXEC[tiCXT_EXEC.m_uiI].m_tiCXT_EXEC_S), tiCXT_EXEC ) );

    {
        STg2_KN_GPU_VLKN_CXT_EXEC_PC                psVLKN_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + tiCXT_EXEC.m_uiI;
        TgRSIZE_C                                   uiContext_Command_Count = TgSTD_ATOMIC(fetch_add)( &psVLKN_CXT_EXEC->m_xuiContext_Command_Index, 1 );
        TgRSIZE_C                                   uiContext_Command_Index = uiContext_Command_Count % KTgKN_GPU_MAX_EXEC_CONTEXT_COMMAND;
        STg2_KN_GPU_VLKN_CXT_CMD_PC                 psVLKN_CXT_CMD = psVLKN_CXT_EXEC->m_sContext_Command + uiContext_Command_Index;

        STg2_KN_GPU_VLKN_Physical_Device_CP         psGPU_EXT_Physical_Device;
        VkDevice                                    hVLKN_Device;
        VkFence_P                                   ahVLKN_Queue_Fence_End_Of_Frame;
        TgUINT_E32                                  nuiQueue_Fence_End_Of_Frame;
        TgRSIZE                                     uiIndex;
        VkResult                                    eResult;
        TgRSIZE                                     uiSize;

        tgPM_MT_SM_Wait_Block( &psVLKN_CXT_CMD->m_sLock );

        /* Reset the work identifier to avoid (or at least detect) ABA or other stale pointer issues. */
        tgKN_GPU_CXT_WORK_ID_Init( &psVLKN_CXT_CMD->m_tiCXT_WORK_S, (TgUINT_E32)(uiContext_Command_Index & 0xFFFF) | (TgUINT_E32)((tiCXT_EXEC.m_uiI << 16) & 0xFFFF0000) );
        psVLKN_CXT_CMD->m_tiCXT_EXEC = tiCXT_EXEC;

        psGPU_EXT_Physical_Device = g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Physical_Device + psVLKN_CXT_EXEC->m_idxCXT_HOST_Physical_Device;
        hVLKN_Device = psGPU_EXT_Physical_Device->m_hVLKN_Device;
        ahVLKN_Queue_Fence_End_Of_Frame = psVLKN_CXT_CMD->m_ahVLKN_Queue_Fence_End_Of_Frame;
        nuiQueue_Fence_End_Of_Frame = (TgUINT_E32)(psVLKN_CXT_CMD->m_nuiQueue_Used_In_Frame);

        /* Wait for previous frame's command buffers to complete before resetting pools and allocators */

        if (nuiQueue_Fence_End_Of_Frame > 0)
        {
            eResult = vkWaitForFences(psVLKN_CXT_EXEC->m_hVLKN_Device, nuiQueue_Fence_End_Of_Frame, ahVLKN_Queue_Fence_End_Of_Frame, VK_TRUE, 1000000000);
            if (VK_SUCCESS != eResult)
            {
                TgERROR_MSGF(0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to wait for fence in Frame_Start: %d", eResult);
                /* Continue anyway - this is for safety but shouldn't fail in normal operation */
            }

            /* Reset the fence for reuse */
            eResult = vkResetFences(psVLKN_CXT_EXEC->m_hVLKN_Device, nuiQueue_Fence_End_Of_Frame, ahVLKN_Queue_Fence_End_Of_Frame);
            if (VK_SUCCESS != eResult)
            {
                TgERROR_MSGF(0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to reset fence in Frame_Start: %d", eResult);
            }

            psVLKN_CXT_CMD->m_nuiQueue_Used_In_Frame = 0;
        }

        tgKN_GPU_EXT__WORK__Query_And_Reset_Timestamp_Pool(tgKN_GPU_CXT_WORK_ID_Query_Unsafe(&psVLKN_CXT_CMD->m_tiCXT_WORK_S));

        for (uiIndex = 0; uiIndex < TgARRAY_COUNT( psVLKN_CXT_CMD->m_asCmd_Pool__Graphics ); ++uiIndex)
        {
            STg2_KN_GPU_VLKN_Node_Cmd_Pool_PC           psNode_Cmd_Pool = psVLKN_CXT_CMD->m_asCmd_Pool__Graphics + uiIndex;

            if (VK_NULL_HANDLE != psNode_Cmd_Pool->m_hVLKN_Command_Pool)
            {
                eResult = vkResetCommandPool( hVLKN_Device, psNode_Cmd_Pool->m_hVLKN_Command_Pool, 0 );
                TgVERIFY(VK_SUCCESS == eResult);
                tgCM_UT_ST__QU__Merge(&psNode_Cmd_Pool->m_sCmd_Buffer_Free_Queue, &psNode_Cmd_Pool->m_sCmd_Buffer_Used_Queue);
            }
        }

        for (uiIndex = 0; uiIndex < TgARRAY_COUNT( psVLKN_CXT_CMD->m_asCmd_Pool__Present ); ++uiIndex)
        {
            STg2_KN_GPU_VLKN_Node_Cmd_Pool_PC           psNode_Cmd_Pool = psVLKN_CXT_CMD->m_asCmd_Pool__Present + uiIndex;

            if (VK_NULL_HANDLE != psNode_Cmd_Pool->m_hVLKN_Command_Pool)
            {
                eResult = vkResetCommandPool(hVLKN_Device, psNode_Cmd_Pool->m_hVLKN_Command_Pool, 0);
                TgVERIFY(VK_SUCCESS == eResult);
                tgCM_UT_ST__QU__Merge(&psNode_Cmd_Pool->m_sCmd_Buffer_Free_Queue, &psNode_Cmd_Pool->m_sCmd_Buffer_Used_Queue);
            }
        }

        for (uiIndex = 0; uiIndex < TgARRAY_COUNT( psVLKN_CXT_CMD->m_asCmd_Pool__Compute ); ++uiIndex)
        {
            STg2_KN_GPU_VLKN_Node_Cmd_Pool_PC           psNode_Cmd_Pool = psVLKN_CXT_CMD->m_asCmd_Pool__Compute + uiIndex;

            if (VK_NULL_HANDLE != psNode_Cmd_Pool->m_hVLKN_Command_Pool)
            {
                eResult = vkResetCommandPool(hVLKN_Device, psNode_Cmd_Pool->m_hVLKN_Command_Pool, 0);
                TgVERIFY(VK_SUCCESS == eResult);
                tgCM_UT_ST__QU__Merge(&psNode_Cmd_Pool->m_sCmd_Buffer_Free_Queue, &psNode_Cmd_Pool->m_sCmd_Buffer_Used_Queue);
            }
        }

        for (uiIndex = 0; uiIndex < TgARRAY_COUNT( psVLKN_CXT_CMD->m_asCmd_Pool__Transfer ); ++uiIndex)
        {
            STg2_KN_GPU_VLKN_Node_Cmd_Pool_PC           psNode_Cmd_Pool = psVLKN_CXT_CMD->m_asCmd_Pool__Transfer + uiIndex;

            if (VK_NULL_HANDLE != psNode_Cmd_Pool->m_hVLKN_Command_Pool)
            {
                eResult = vkResetCommandPool(hVLKN_Device, psNode_Cmd_Pool->m_hVLKN_Command_Pool, 0);
                TgVERIFY(VK_SUCCESS == eResult);
                tgCM_UT_ST__QU__Merge(&psNode_Cmd_Pool->m_sCmd_Buffer_Free_Queue, &psNode_Cmd_Pool->m_sCmd_Buffer_Used_Queue);
            }
        }

        for (uiIndex = 0; uiIndex < TgARRAY_COUNT( psVLKN_CXT_CMD->m_asVLKN_Descriptor_Pool); ++uiIndex)
        {
            if (VK_NULL_HANDLE != psVLKN_CXT_CMD->m_asVLKN_Descriptor_Pool[uiIndex].m_hVLKN_Descriptor_Pool)
            {
                eResult = vkResetDescriptorPool( hVLKN_Device, psVLKN_CXT_CMD->m_asVLKN_Descriptor_Pool[uiIndex].m_hVLKN_Descriptor_Pool, 0 );
                TgVERIFY(VK_SUCCESS == eResult);
            }
        }

        tgCM_UT_LF__ST__Init_PreLoad( &psVLKN_CXT_CMD->m_sStack_DS_Pool_Free.m_sStack, psVLKN_CXT_CMD->m_asVLKN_Descriptor_Pool,
                                      sizeof(psVLKN_CXT_CMD->m_asVLKN_Descriptor_Pool[0]), TgARRAY_COUNT( psVLKN_CXT_CMD->m_asVLKN_Descriptor_Pool ) );

        tgKN_GPU_VLKN__Execute__Process_Resource_Release_List( tiCXT_EXEC );

        uiSize = KTgKN_GPU_MAX_RENDER_DESC_PER_FRAME * psVLKN_CXT_EXEC->m_uiUBO_Aligned_Render_DESC_Size;
        TgSTD_ATOMIC(store)( &psVLKN_CXT_CMD->m_xuiUBO_Render_DESC_Offset, uiContext_Command_Index * uiSize );
        psVLKN_CXT_CMD->m_uiUBO_Render_DESC_End = (uiContext_Command_Index + 1) * uiSize;

    #if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)
        tgKN_GPU_VLKN__CMD__Frame_Start_Debug( psVLKN_CXT_CMD, uiContext_Command_Index );
    /*# defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
    #endif

        return (tgKN_GPU_CXT_WORK_ID_Query_Unsafe( &psVLKN_CXT_CMD->m_tiCXT_WORK_S ));
    }
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public GPU Functions - WORK                                                                                                                                                    */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_GPU_EXT__WORK__Frame_End -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_EXT__WORK__Frame_End(
    TgKN_GPU_CXT_WORK_ID_C                      tiCXT_WORK )
{
    TgRSIZE                                     uiEXEC = (tiCXT_WORK.m_uiI >> 16) & 0xFFFF;
    TgRSIZE                                     uiWORK = (tiCXT_WORK.m_uiI & 0xFFFF) % KTgKN_GPU_MAX_EXEC_CONTEXT_COMMAND;
    STg2_KN_GPU_VLKN_CXT_EXEC_PC                psVLKN_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + uiEXEC;
    STg2_KN_GPU_VLKN_CXT_CMD_PC                 psVLKN_CXT_CMD = psVLKN_CXT_EXEC->m_sContext_Command + uiWORK;

    TgUINT_E64                                  uiUsed_Queue_Family_Mask;
    TgRSIZE                                     uiIndex;

    TgPARAM_CHECK_KN_EXEC_WORK(tiCXT_WORK);

    /* Submit fences for queues that had work this frame */
    uiUsed_Queue_Family_Mask = TgSTD_ATOMIC(exchange)(&psVLKN_CXT_CMD->m_xuiUsed_Queue_Family_Mask, 0);

    tgMM_Set_U08_0x00(psVLKN_CXT_CMD->m_ahVLKN_Queue_Fence_End_Of_Frame, sizeof(psVLKN_CXT_CMD->m_ahVLKN_Queue_Fence_End_Of_Frame));
    psVLKN_CXT_CMD->m_nuiQueue_Used_In_Frame = 0;

    for (uiIndex = 0; uiIndex < TgARRAY_COUNT(psVLKN_CXT_EXEC->m_asCmd_Queue_Family_Indexed); ++uiIndex)
    {
        /* Check if this queue family had work submitted this frame */
        if (0 != (uiUsed_Queue_Family_Mask & (1ULL << uiIndex)))
        {
            VkFence_C                               hVLKN_Fence = psVLKN_CXT_CMD->m_ahVLKN_Queue_Fence[uiIndex];
            STg2_KN_GPU_VLKN_CMD_Queue_PC           psCmd_Queue = psVLKN_CXT_EXEC->m_asCmd_Queue_Family_Indexed + uiIndex;

            VkSubmitInfo                            sVLKN_Submit_Info;
            VkResult                                eResult;

            /* Submit empty command buffer with fence to mark frame end for this queue */
            sVLKN_Submit_Info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
            sVLKN_Submit_Info.pNext = nullptr;
            sVLKN_Submit_Info.waitSemaphoreCount = 0;
            sVLKN_Submit_Info.pWaitSemaphores = nullptr;
            sVLKN_Submit_Info.pWaitDstStageMask = nullptr;
            sVLKN_Submit_Info.commandBufferCount = 0;
            sVLKN_Submit_Info.pCommandBuffers = nullptr;
            sVLKN_Submit_Info.signalSemaphoreCount = 0;
            sVLKN_Submit_Info.pSignalSemaphores = nullptr;

            /* Submit with fence - marks end of all frame work for this queue family */
            tgCM_UT_LF__SN__Lock_Spin( &psCmd_Queue->m_sLock.m_sLock );
            eResult = vkQueueSubmit(psCmd_Queue->m_hVLKN_Queue, 1, &sVLKN_Submit_Info, hVLKN_Fence);
            tgCM_UT_LF__SN__Signal( &psCmd_Queue->m_sLock.m_sLock );

            if (VK_SUCCESS != eResult)
            {
                TgERROR_MSGF(0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to submit end-of-frame fence");
            }
            else
            {
                psVLKN_CXT_CMD->m_ahVLKN_Queue_Fence_End_Of_Frame[psVLKN_CXT_CMD->m_nuiQueue_Used_In_Frame++] = hVLKN_Fence;
            }
        }
    }

#if !defined(TGS_FINAL)
    {
        STg2_UT_ST__ST_Node_P                       psNode;
        TgSINT_E32                                  iIndex;

        /* Validation - check that all allocators have been returned. */
        for (psNode = tgCM_UT_LF__ST__Pop( &psVLKN_CXT_CMD->m_sStack_Cmd_Pool_Free[ETgKN_GPU_EXT_COMMAND_GRAPHICS].m_sStack ), iIndex = 0; nullptr != psNode; ++iIndex)
        {
            psNode = tgCM_UT_LF__ST__Pop( &psVLKN_CXT_CMD->m_sStack_Cmd_Pool_Free[ETgKN_GPU_EXT_COMMAND_GRAPHICS].m_sStack );
        }
        TgVERIFY(TgARRAY_COUNT(psVLKN_CXT_CMD->m_asCmd_Pool__Graphics) == iIndex);

        for (psNode = tgCM_UT_LF__ST__Pop( &psVLKN_CXT_CMD->m_sStack_Cmd_Pool_Free[ETgKN_GPU_EXT_COMMAND_PRESENT].m_sStack ), iIndex = 0; nullptr != psNode; ++iIndex)
        {
            psNode = tgCM_UT_LF__ST__Pop( &psVLKN_CXT_CMD->m_sStack_Cmd_Pool_Free[ETgKN_GPU_EXT_COMMAND_PRESENT].m_sStack );
        }
        TgVERIFY(TgARRAY_COUNT(psVLKN_CXT_CMD->m_asCmd_Pool__Present) == iIndex);

        for (psNode = tgCM_UT_LF__ST__Pop( &psVLKN_CXT_CMD->m_sStack_Cmd_Pool_Free[ETgKN_GPU_EXT_COMMAND_COMPUTE].m_sStack ), iIndex = 0; nullptr != psNode; ++iIndex)
        {
            psNode = tgCM_UT_LF__ST__Pop( &psVLKN_CXT_CMD->m_sStack_Cmd_Pool_Free[ETgKN_GPU_EXT_COMMAND_COMPUTE].m_sStack );
        }
        TgVERIFY(TgARRAY_COUNT(psVLKN_CXT_CMD->m_asCmd_Pool__Compute) == iIndex);

        for (psNode = tgCM_UT_LF__ST__Pop( &psVLKN_CXT_CMD->m_sStack_Cmd_Pool_Free[ETgKN_GPU_EXT_COMMAND_TRANSFER].m_sStack ), iIndex = 0; nullptr != psNode; ++iIndex)
        {
            psNode = tgCM_UT_LF__ST__Pop( &psVLKN_CXT_CMD->m_sStack_Cmd_Pool_Free[ETgKN_GPU_EXT_COMMAND_TRANSFER].m_sStack );
        }
        TgVERIFY(TgARRAY_COUNT(psVLKN_CXT_CMD->m_asCmd_Pool__Transfer) == iIndex);

        tgKN_GPU_VLKN_Context_Command_Init__Cmd_Pool_Lock_Free_Stacks( psVLKN_CXT_CMD );
    }
/*# !defined(TGS_FINAL) */
#endif

    tgKN_GPU_CXT_WORK_ID_Invalidate( &psVLKN_CXT_CMD->m_tiCXT_WORK_S );
    tgPM_MT_SM_Signal( &psVLKN_CXT_CMD->m_sLock, 1 );
}


/* ---- tgKN_GPU_EXT__WORK__Acquire_Command -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
STg2_KN_GPU_CMD_P tgKN_GPU_EXT__WORK__Acquire_Command(
    TgKN_GPU_CXT_WORK_ID_C                      tiCXT_WORK,
    ETgKN_GPU_EXT_COMMAND_C                     enCmd_Queue,
    TgCHAR_U8_CPC                               uszDebug_Name )
{
    TgRSIZE                                     uiEXEC = (tiCXT_WORK.m_uiI >> 16) & 0xFFFF;
    TgRSIZE                                     uiWORK = (tiCXT_WORK.m_uiI & 0xFFFF) % KTgKN_GPU_MAX_EXEC_CONTEXT_COMMAND;
    STg2_KN_GPU_VLKN_CXT_EXEC_PC                psVLKN_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + uiEXEC;

    STg2_KN_GPU_VLKN_CXT_CMD_P                  psVLKN_CXT_CMD;
    VkDevice                                    hVLKN_Device;
    VkCommandBufferBeginInfo                    sBeginInfo;
    union
    {
        UTg2_KN_GPU_CMD                                 uCmd;
        STg2_UT_ST__ST_Node_P                           psNode;
    }                                           sCMD;
    union
    {
        STg2_KN_GPU_VLKN_Node_DS_Pool_P                 psNode_DS_Pool;
        STg2_UT_ST__ST_Node_P                           psNode;
    }                                           sDS_Pool;

    STg2_KN_GPU_VLKN_Node_Cmd_Pool_P            psNode_Cmd_Pool;
    STg2_KN_GPU_VLKN_Node_Cmd_Buffer_P          psNode_Cmd_Buffer;
    TgCHAR_U8                                   uszBuffer[128];

    TgPARAM_VAR(STg2_KN_GPU_CXT_EXEC_PC psCXT_EXEC = g_asKN_GPU_CXT_EXEC + uiEXEC;)
    TgPARAM_CHECK_INDEX( uiEXEC, g_asKN_GPU_EXT_CXT_EXEC );
    TgPARAM_CHECK_INDEX( uiWORK, g_asKN_GPU_EXT_CXT_EXEC[uiEXEC].m_sContext_Command );
    TgPARAM_CHECK( tgKN_GPU_CXT_WORK_ID_Is_Equal( &psVLKN_CXT_EXEC->m_sContext_Command[uiWORK].m_tiCXT_WORK_S, tiCXT_WORK ) );
    TgPARAM_CHECK( tgKN_GPU_CXT_EXEC_ID_Is_Equal( &psCXT_EXEC->m_tiCXT_EXEC_S, psVLKN_CXT_EXEC->m_sContext_Command[uiWORK].m_tiCXT_EXEC ) );
    TgPARAM_CHECK( enCmd_Queue >= ETgKN_GPU_EXT_COMMAND_GRAPHICS && enCmd_Queue <= ETgKN_GPU_EXT_COMMAND_TRANSFER );

    /* Acquire a command structure, allocator, and command list. */
    psVLKN_CXT_CMD = psVLKN_CXT_EXEC->m_sContext_Command + uiWORK;
    sCMD.psNode = tgCM_UT_LF__ST__Pop( &psVLKN_CXT_EXEC->m_sCommand_Free_Stack.m_sStack );

    if (nullptr == sCMD.psNode)
    {
        goto tgKN_GPU_EXT__Execute__Command_List_Acquire_FAIL_0;
    }

    sDS_Pool.psNode = tgCM_UT_LF__ST__Pop( &psVLKN_CXT_CMD->m_sStack_DS_Pool_Free.m_sStack );
    if (nullptr == sDS_Pool.psNode)
    {
        goto tgKN_GPU_EXT__Execute__Command_List_Acquire_FAIL_1;
    }

    tgKN_GPU_VLKN_Acquire_Command_Pool_Buffer( &psNode_Cmd_Pool, &psNode_Cmd_Buffer, psVLKN_CXT_EXEC, psVLKN_CXT_CMD, enCmd_Queue );

    if (nullptr == psNode_Cmd_Buffer)
    {
        goto tgKN_GPU_EXT__Execute__Command_List_Acquire_FAIL_2;
    }

    /* Check to see if we need to initialize a new allocator or command list. */
    hVLKN_Device = g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Physical_Device[psVLKN_CXT_EXEC->m_idxCXT_HOST_Physical_Device].m_hVLKN_Device;

    tgUSZ_PrintF(uszBuffer, sizeof(uszBuffer), u8"CMD BUF - %s", uszDebug_Name ? uszDebug_Name : u8"");
    (void)uszBuffer;
    TgMACRO_KN_GPU_VLKN_SET_NAME(hVLKN_Device, VK_OBJECT_TYPE_COMMAND_BUFFER, psNode_Cmd_Buffer->m_hVLKN_Command_Buffer, uszBuffer);

    if (nullptr == sDS_Pool.psNode_DS_Pool->m_hVLKN_Descriptor_Pool)
    {
        if (TgFAILED(tgKN_GPU_VLKN__Command_Context__Create_Default_Descriptor_Pool( &sDS_Pool.psNode_DS_Pool->m_hVLKN_Descriptor_Pool, hVLKN_Device )))
        {
            goto tgKN_GPU_EXT__Execute__Command_List_Acquire_FAIL_3;
        }
        TgMACRO_KN_GPU_VLKN_SET_NAME(hVLKN_Device, VK_OBJECT_TYPE_DESCRIPTOR_POOL, sDS_Pool.psNode_DS_Pool->m_hVLKN_Descriptor_Pool, u8"Execution Cmd DS Pool");
    }

    /* Begin recording */
    tgMM_Set_U08_0x00( &sBeginInfo, sizeof( sBeginInfo ) );
    sBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    sBeginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    vkBeginCommandBuffer(psNode_Cmd_Buffer->m_hVLKN_Command_Buffer, &sBeginInfo);

    /* Initialize the command structure. */

    tgMM_Set_U08_0x00( sCMD.uCmd.psVLKN, sizeof( STg2_KN_GPU_VLKN_CMD ) );

    sCMD.uCmd.psVLKN->m_enCmd_Queue = enCmd_Queue;
    sCMD.uCmd.psVLKN->m_sBase.m_tiCXT_WORK = tiCXT_WORK;

    sCMD.uCmd.psVLKN->m_hVLKN_Device = hVLKN_Device;
    sCMD.uCmd.psVLKN->m_sVLKN_Memory_Properties = g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Physical_Device[psVLKN_CXT_EXEC->m_idxCXT_HOST_Physical_Device].m_sVLKN_Memory_Properties;
    sCMD.uCmd.psVLKN->m_hVLKN_Command_Pool = psNode_Cmd_Pool->m_hVLKN_Command_Pool;
    sCMD.uCmd.psVLKN->m_hVLKN_Command_Buffer = psNode_Cmd_Buffer->m_hVLKN_Command_Buffer;
    sCMD.uCmd.psVLKN->m_hVLKN_Descriptor_Pool = sDS_Pool.psNode_DS_Pool->m_hVLKN_Descriptor_Pool;

    sCMD.uCmd.psVLKN->m_psNode_Command_Pool = psNode_Cmd_Pool;
    sCMD.uCmd.psVLKN->m_psNode_Command_Buffer = psNode_Cmd_Buffer;
    sCMD.uCmd.psVLKN->m_psNode_Descriptor_Pool = sDS_Pool.psNode_DS_Pool;

    sCMD.uCmd.psVLKN->m_uiUBO_Render_DESC_Offset = KTgMAX_U32;

#if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)
    {
        union {
            STg2_KN_GPU_CMD_DBG_P                       psCMD_DBG;
            STg2_KN_GPU_DBG_VLKN_CMD_P                  psCMD_DBG_VLKN;
        }                                           uCMD_DBG;

        if (TgSUCCEEDED(tgKN_GPU_EXT__CMD__Command_Debug(&uCMD_DBG.psCMD_DBG, sCMD.uCmd.ps)))
        {
            TgVERIFY(TgSUCCEEDED(tgCM_UT_LF__SN__Init( &uCMD_DBG.psCMD_DBG_VLKN->m_sCMD_DBG.m_sLine_Lock )));
            if (nullptr == uCMD_DBG.psCMD_DBG_VLKN->m_sCMD_DBG.m_psLine)
            {
                uCMD_DBG.psCMD_DBG_VLKN->m_sCMD_DBG.m_psLine = (STg2_KN_GPU_DBG_Line_P)TgRESERVE_VIRTUAL( sizeof( STg2_KN_GPU_DBG_Line ) * KTgKN_GPU_MAX_DBG_STORAGE_LINE );
                uCMD_DBG.psCMD_DBG_VLKN->m_sCMD_DBG.m_nuiLine_Page = 0;
            }

            tgMM_Set_U08_0x00( uCMD_DBG.psCMD_DBG_VLKN->m_ahVLKN_Pipeline_Graphics, sizeof( uCMD_DBG.psCMD_DBG_VLKN->m_ahVLKN_Pipeline_Graphics) );
            uCMD_DBG.psCMD_DBG_VLKN->m_uiUBO_Render_DESC_Offset = KTgMAX_U32;
        }
    }
/*# defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
#endif

    return (sCMD.uCmd.ps);

tgKN_GPU_EXT__Execute__Command_List_Acquire_FAIL_3:
    psNode_Cmd_Buffer->m_sNode_Queue.m_pNext_Node = nullptr;
    tgCM_UT_ST__QU__Enqueue( &psNode_Cmd_Pool->m_sCmd_Buffer_Free_Queue, &psNode_Cmd_Buffer->m_sNode_Queue );
    tgCM_UT_LF__ST__Push( &psVLKN_CXT_CMD->m_sStack_Cmd_Pool_Free[enCmd_Queue].m_sStack, &psNode_Cmd_Pool->m_sNode_Stack );
tgKN_GPU_EXT__Execute__Command_List_Acquire_FAIL_2:
    tgCM_UT_LF__ST__Push( &psVLKN_CXT_CMD->m_sStack_DS_Pool_Free.m_sStack, sDS_Pool.psNode );
tgKN_GPU_EXT__Execute__Command_List_Acquire_FAIL_1:
    tgCM_UT_LF__ST__Push( &psVLKN_CXT_EXEC->m_sCommand_Free_Stack.m_sStack, sCMD.psNode );
tgKN_GPU_EXT__Execute__Command_List_Acquire_FAIL_0:
    return (nullptr);
}


/* ---- tgKN_GPU_EXT__WORK__Submit_GPU_Timestamp --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_EXT__WORK__Submit_GPU_Timestamp(
    TgRSIZE_PC                                  puiTimestamp,
    TgKN_GPU_CXT_WORK_ID_C                      tiCXT_WORK )
{
    TgRSIZE                                     uiEXEC = (tiCXT_WORK.m_uiI >> 16) & 0xFFFF;
    TgRSIZE                                     uiWORK = (tiCXT_WORK.m_uiI & 0xFFFF) % KTgKN_GPU_MAX_EXEC_CONTEXT_COMMAND;
    STg2_KN_GPU_VLKN_CXT_EXEC_PC                psVLKN_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + uiEXEC;

    STg2_KN_GPU_VLKN_CXT_CMD_PC                 psVLKN_CXT_CMD = psVLKN_CXT_EXEC->m_sContext_Command + uiWORK;
    STg2_KN_GPU_VLKN_CMD_Queue_PC               psGraphics_Queue = psVLKN_CXT_EXEC->m_apsCmd_Queue[ETgKN_GPU_EXT_COMMAND_GRAPHICS];

    VkCommandBufferBeginInfo_C                  sBeginInfo = {
                                                    .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
                                                    .pNext = nullptr,
                                                    .flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
                                                    .pInheritanceInfo = nullptr,
                                                };

    STg2_KN_GPU_VLKN_Node_Cmd_Pool_P            psNode_Cmd_Pool;
    STg2_KN_GPU_VLKN_Node_Cmd_Buffer_P          psNode_Cmd_Buffer;
    TgUINT_E32                                  uiTimestamp;
    VkResult                                    eResult;

    TgPARAM_VAR(STg2_KN_GPU_CXT_EXEC_PC psCXT_EXEC = g_asKN_GPU_CXT_EXEC + uiEXEC;)
    TgPARAM_CHECK_INDEX( uiEXEC, g_asKN_GPU_EXT_CXT_EXEC );
    TgPARAM_CHECK_INDEX( uiWORK, g_asKN_GPU_EXT_CXT_EXEC[uiEXEC].m_sContext_Command );
    TgPARAM_CHECK( tgKN_GPU_CXT_WORK_ID_Is_Equal( &psVLKN_CXT_EXEC->m_sContext_Command[uiWORK].m_tiCXT_WORK_S, tiCXT_WORK ) );
    TgPARAM_CHECK( tgKN_GPU_CXT_EXEC_ID_Is_Equal( &psCXT_EXEC->m_tiCXT_EXEC_S, psVLKN_CXT_EXEC->m_sContext_Command[uiWORK].m_tiCXT_EXEC ) );
    TgPARAM_CHECK(nullptr != puiTimestamp);

    uiTimestamp = (TgUINT_E32)TgSTD_ATOMIC(fetch_add)( &psVLKN_CXT_CMD->m_xuiVLKN_Timestamp, 1 );
    *puiTimestamp = KTgMAX_UMAX;

    if (uiTimestamp >= TgARRAY_COUNT(psVLKN_CXT_CMD->m_auiTimestamps))
    {
        TgERROR_MSGF(0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Exceeded maximum number of GPU timestamps per command context");
        return (KTgE_FAIL);
    }

    tgKN_GPU_VLKN_Acquire_Command_Pool_Buffer(&psNode_Cmd_Pool, &psNode_Cmd_Buffer, psVLKN_CXT_EXEC, psVLKN_CXT_CMD, ETgKN_GPU_EXT_COMMAND_GRAPHICS);

    if (nullptr == psNode_Cmd_Pool || nullptr == psNode_Cmd_Buffer)
    {
        TgERROR_MSGF(0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Exceeded maximum number of GPU command buffers per command context");
        return (KTgE_FAIL);
    }

    TgMACRO_KN_GPU_VLKN_SET_NAME(psVLKN_CXT_EXEC->m_hVLKN_Device, VK_OBJECT_TYPE_COMMAND_BUFFER, psNode_Cmd_Buffer->m_hVLKN_Command_Buffer, u8"CMD BUF - GPU Timestamp");

    eResult = vkBeginCommandBuffer(psNode_Cmd_Buffer->m_hVLKN_Command_Buffer, &sBeginInfo);
    if (VK_SUCCESS != eResult)
    {
        TgERROR_MSGF(0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to begin command buffer for GPU timestamp");
        psNode_Cmd_Buffer->m_sNode_Queue.m_pNext_Node = nullptr;
        tgCM_UT_ST__QU__Enqueue(&psNode_Cmd_Pool->m_sCmd_Buffer_Free_Queue, &psNode_Cmd_Buffer->m_sNode_Queue);
        tgCM_UT_LF__ST__Push(&psVLKN_CXT_CMD->m_sStack_Cmd_Pool_Free[ETgKN_GPU_EXT_COMMAND_GRAPHICS].m_sStack, &psNode_Cmd_Pool->m_sNode_Stack);
        return (KTgE_FAIL);
    }

    /* Ensure all previous commands have completed before writing the timestamp */
    vkCmdPipelineBarrier(psNode_Cmd_Buffer->m_hVLKN_Command_Buffer, VK_PIPELINE_STAGE_ALL_COMMANDS_BIT, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, 0, 0, nullptr, 0, nullptr, 0, nullptr);

    vkCmdWriteTimestamp(psNode_Cmd_Buffer->m_hVLKN_Command_Buffer, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, psVLKN_CXT_CMD->m_hVLKN_Timestamp_Query_Pool, uiTimestamp);
    eResult = vkEndCommandBuffer(psNode_Cmd_Buffer->m_hVLKN_Command_Buffer);

    if (VK_SUCCESS != eResult)
    {
        TgERROR_MSGF(0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to end command buffer for GPU timestamp");
        psNode_Cmd_Buffer->m_sNode_Queue.m_pNext_Node = nullptr;
        tgCM_UT_ST__QU__Enqueue(&psNode_Cmd_Pool->m_sCmd_Buffer_Free_Queue, &psNode_Cmd_Buffer->m_sNode_Queue);
        tgCM_UT_LF__ST__Push(&psVLKN_CXT_CMD->m_sStack_Cmd_Pool_Free[ETgKN_GPU_EXT_COMMAND_GRAPHICS].m_sStack, &psNode_Cmd_Pool->m_sNode_Stack);
        return (KTgE_FAIL);
    }

    tgKN_GPU_VLKN_Submit_Semaphore_Timeline_For_Queue_With_Wait(nullptr, psGraphics_Queue, 1, &psNode_Cmd_Buffer->m_hVLKN_Command_Buffer, nullptr, 0 );

    /* Track which queue family had work submitted this frame */
    TgSTD_ATOMIC(fetch_or)(&psVLKN_CXT_CMD->m_xuiUsed_Queue_Family_Mask, (1ULL << psVLKN_CXT_EXEC->m_apsCmd_Queue[ETgKN_GPU_EXT_COMMAND_GRAPHICS]->m_uiQueue_Family_Index));

    tgCM_UT_LF__ST__Push(&psVLKN_CXT_CMD->m_sStack_Cmd_Pool_Free[ETgKN_GPU_EXT_COMMAND_GRAPHICS].m_sStack, &psNode_Cmd_Pool->m_sNode_Stack);
    *puiTimestamp = uiTimestamp;

    return (KTgS_OK);
}


/* ---- tgKN_GPU_EXT__WORK__Query_GPU_Timestamp ---------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgFLOAT32 tgKN_GPU_EXT__WORK__Query_GPU_Timestamp(
    TgKN_GPU_CXT_WORK_ID_C                      tiCXT_WORK,
    TgRSIZE                                     uiTimestamp_Start,
    TgRSIZE                                     uiTimestamp_End )
{
    TgRSIZE                                     uiEXEC = (tiCXT_WORK.m_uiI >> 16) & 0xFFFF;
    TgRSIZE                                     uiWORK = (tiCXT_WORK.m_uiI & 0xFFFF) % KTgKN_GPU_MAX_EXEC_CONTEXT_COMMAND;
    STg2_KN_GPU_VLKN_CXT_EXEC_PC                psVLKN_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + uiEXEC;
    STg2_KN_GPU_VLKN_CXT_CMD_PC                 psVLKN_CXT_CMD = psVLKN_CXT_EXEC->m_sContext_Command + uiWORK;
    STg2_KN_GPU_VLKN_Physical_Device_CP         psGPU_EXT_Physical_Device = g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Physical_Device + psVLKN_CXT_EXEC->m_idxCXT_HOST_Physical_Device;

    TgFLOAT32_C                                 fTimestamp_Period = psGPU_EXT_Physical_Device->m_sVLKN_Properties.limits.timestampPeriod;
    TgUINT_E64_C                                uiTimestamp_Delta = psVLKN_CXT_CMD->m_auiTimestamps[uiTimestamp_End] - psVLKN_CXT_CMD->m_auiTimestamps[uiTimestamp_Start];

    TgPARAM_CHECK_INDEX(uiTimestamp_Start, psVLKN_CXT_CMD->m_auiTimestamps);
    TgPARAM_CHECK_INDEX(uiTimestamp_End, psVLKN_CXT_CMD->m_auiTimestamps);

    /* Convert nanoseconds to milliseconds */
    return ((TgFLOAT32)uiTimestamp_Delta * fTimestamp_Period) / 1000000.0F;
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public GPU Functions - Command                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_GPU_EXT__CMD__Command_Buffer_Close_And_Submit_With_Wait ------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_EXT__CMD__Command_Buffer_Close_And_Submit_With_Wait(
    TgUINT_E64_P                                puiTimeline_Value,
    STg2_KN_GPU_CMD_PC                          psCMD,
    ETgKN_GPU_EXT_COMMAND_C                     enWait_Queue,
    TgUINT_E64_C                                uiTimleine_Wait_Value )
{
    UTg2_KN_GPU_CMD_C                           uCMD = { .ps = psCMD };
    TgRSIZE_C                                   uiEXEC = (uCMD.psVLKN->m_sBase.m_tiCXT_WORK.m_uiI >> 16) & 0xFFFF;
    TgRSIZE_C                                   uiWORK = (uCMD.psVLKN->m_sBase.m_tiCXT_WORK.m_uiI & 0xFFFF) % KTgKN_GPU_MAX_EXEC_CONTEXT_COMMAND;
    STg2_KN_GPU_VLKN_CXT_EXEC_PC                psVLKN_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + uiEXEC;

    STg2_KN_GPU_VLKN_CXT_CMD_P                  psVLKN_CXT_CMD;
    STg2_KN_GPU_VLKN_CMD_Queue_P                psCMD_Queue, psWait_CMD_Queue;
    VkResult                                    eResult;

    TgPARAM_CHECK_KN_GPU_CMD( psCMD );
    TgPARAM_CHECK( enWait_Queue >= ETgKN_GPU_EXT_COMMAND_NONE && enWait_Queue <= ETgKN_GPU_EXT_COMMAND_TRANSFER );

    psVLKN_CXT_CMD = psVLKN_CXT_EXEC->m_sContext_Command + uiWORK;
    psCMD_Queue = psVLKN_CXT_EXEC->m_apsCmd_Queue[uCMD.psVLKN->m_enCmd_Queue];
    psWait_CMD_Queue = enWait_Queue > ETgKN_GPU_EXT_COMMAND_NONE ? psVLKN_CXT_EXEC->m_apsCmd_Queue[enWait_Queue] : nullptr;

    /* Close and schedule the command list. */

    if (VK_NULL_HANDLE != uCMD.psVLKN->m_hVLKN_Command_Buffer)
    {
        eResult = vkEndCommandBuffer(uCMD.psVLKN->m_hVLKN_Command_Buffer);
        if (VK_SUCCESS != eResult)
        {
            TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to end command buffer" );
            uCMD.psVLKN->m_hVLKN_Command_Buffer = VK_NULL_HANDLE;
        }

        tgKN_GPU_VLKN_Submit_Semaphore_Timeline_For_Queue_With_Wait( puiTimeline_Value, psCMD_Queue, 1, &uCMD.psVLKN->m_hVLKN_Command_Buffer, psWait_CMD_Queue, uiTimleine_Wait_Value );
        uCMD.psVLKN->m_hVLKN_Command_Buffer = VK_NULL_HANDLE;
    }

    /* Track which queue family had work submitted this frame */
    TgSTD_ATOMIC(fetch_or)(&psVLKN_CXT_CMD->m_xuiUsed_Queue_Family_Mask, (1ULL << psCMD_Queue->m_uiQueue_Family_Index));

    /* Return the managers to their free|used lists. */

    uCMD.psVLKN->m_psNode_Command_Buffer->m_sNode_Queue.m_pNext_Node = nullptr;
    tgCM_UT_ST__QU__Enqueue(&uCMD.psVLKN->m_psNode_Command_Pool->m_sCmd_Buffer_Used_Queue, &uCMD.psVLKN->m_psNode_Command_Buffer->m_sNode_Queue);
    uCMD.psVLKN->m_psNode_Command_Buffer = nullptr;

    tgCM_UT_LF__ST__Push( &psVLKN_CXT_CMD->m_sStack_Cmd_Pool_Free[uCMD.psVLKN->m_enCmd_Queue].m_sStack, &uCMD.psVLKN->m_psNode_Command_Pool->m_sNode_Stack );
    uCMD.psVLKN->m_psNode_Command_Pool = nullptr;
    uCMD.psVLKN->m_hVLKN_Command_Pool = VK_NULL_HANDLE;

    tgCM_UT_LF__ST__Push( &psVLKN_CXT_CMD->m_sStack_DS_Pool_Free.m_sStack, &uCMD.psVLKN->m_psNode_Descriptor_Pool->m_sNode_Stack );
    uCMD.psVLKN->m_hVLKN_Descriptor_Pool = VK_NULL_HANDLE;
    uCMD.psVLKN->m_psNode_Descriptor_Pool = nullptr;

    uCMD.psVLKN->m_enCmd_Queue = ETgKN_GPU_EXT_COMMAND_NONE;

    tgCM_UT_LF__ST__Push( &psVLKN_CXT_EXEC->m_sCommand_Free_Stack.m_sStack, &uCMD.psVLKN->m_sNode_Stack );
}


/* ---- tgKN_GPU_EXT__CMD__Begin_Rendering --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_EXT__CMD__Begin_Rendering(
    STg2_KN_GPU_CMD_PC                          psCMD,
    TgKN_GPU_RENDER_TARGET_ID_C                 tiRender_Target,
    TgKN_GPU_CXT_SWAP_ID                        tiCXT_SWAP,
    STg2_KN_GPU_Clear_Target_CPC                psClear_Target,
    STg2_KN_GPU_Camera_CPC                      psCamera,
    STg2_KN_GPU_DBG_Render_DESC_CPC             psDBG_Render_DESC )
{
    UTg2_KN_GPU_CMD_C                           uCMD = { .ps = psCMD };
    TgRSIZE_C                                   uiEXEC = (uCMD.psVLKN->m_sBase.m_tiCXT_WORK.m_uiI >> 16) & 0xFFFF;
    STg2_KN_GPU_VLKN_CXT_EXEC_PC                psVLKN_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + uiEXEC;

    STg2_KN_GPU_VLKN_Render_Target_P            psRender_Target;
    VkRenderingInfo                             sVLKN_Rendering_Info;
    VkRenderingAttachmentInfo                   asVLKN_Colour_Attachment[KTgKN_GPU_MAX_SIMULTANEOUS_TARGET_COUNT];
    VkRenderingAttachmentInfo                   sVLKN_Depth_Stencil_Attachment;
    VkExtent2D                                  sVLKN_Extent;
    TgUINT_E32                                  uiIndex;

    TgPARAM_CHECK_KN_GPU_CMD( psCMD );

    if (TgFAILED(tgKN_GPU_VLKN__Render_Target__Get_Render_Target( &psRender_Target, tiCXT_SWAP, tiRender_Target, psVLKN_CXT_EXEC->m_tiCXT_EXEC )))
    {
        TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to acquire a render target to start rendering." );
        return (KTgE_FAIL);
    }

    /* Transition target to colour attachment and writeable */
    if (TgFAILED(tgKN_GPU_VLKN__CMD__Render_Target_Barrier( uCMD.psVLKN, psRender_Target, VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT, VK_ACCESS_2_COLOR_ATTACHMENT_WRITE_BIT )))
    {
        TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to transition render target to colour attachment." );
        return (KTgE_FAIL);
    }

    /* Cache the Scanout/Output device characteristics */
    psCMD->m_uiRender_Target_Width = (TgUINT_E32)psRender_Target->m_sRender_Target_DESC.m_uiWidth;
    psCMD->m_uiRender_Target_Height = (TgUINT_E32)psRender_Target->m_sRender_Target_DESC.m_uiHeight;

    /* Cache the pipeline handles */
    TgVERIFY(VK_NULL_HANDLE != psRender_Target->m_ahVLKN_Pipeline_Graphics[0]);
    tgMM_Copy( uCMD.psVLKN->m_ahVLKN_Pipeline_Graphics, sizeof(uCMD.psVLKN->m_ahVLKN_Pipeline_Graphics), psRender_Target->m_ahVLKN_Pipeline_Graphics,
               sizeof(psRender_Target->m_ahVLKN_Pipeline_Graphics) );

    sVLKN_Extent.width = (TgUINT_E32)psRender_Target->m_sRender_Target_DESC.m_uiWidth;
    sVLKN_Extent.height = (TgUINT_E32)psRender_Target->m_sRender_Target_DESC.m_uiHeight;
    TgVERIFY(0 != sVLKN_Extent.width && 0 != sVLKN_Extent.height);

    tgMM_Set_U08_0x00( &sVLKN_Rendering_Info, sizeof( sVLKN_Rendering_Info ) );
    tgMM_Set_U08_0x00( &asVLKN_Colour_Attachment, sizeof( asVLKN_Colour_Attachment ) );
    tgMM_Set_U08_0x00( &sVLKN_Depth_Stencil_Attachment, sizeof( sVLKN_Depth_Stencil_Attachment ) );

    /* Setup rendering info for dynamic rendering */

    sVLKN_Rendering_Info.sType = VK_STRUCTURE_TYPE_RENDERING_INFO;
    sVLKN_Rendering_Info.renderArea.extent = sVLKN_Extent;
    sVLKN_Rendering_Info.layerCount = 1;
    sVLKN_Rendering_Info.pColorAttachments = asVLKN_Colour_Attachment;

    /* Setup colour attachment descriptors for dynamic rendering */

    for (uiIndex = 0; uiIndex < psRender_Target->m_sRender_Target_DESC.m_nuiColour_Target; ++uiIndex)
    {
        if (VK_NULL_HANDLE == psRender_Target->m_ahVLKN_Colour_Image_View[uiIndex])
        {
            continue;
        }

        asVLKN_Colour_Attachment[sVLKN_Rendering_Info.colorAttachmentCount].sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO;
        asVLKN_Colour_Attachment[sVLKN_Rendering_Info.colorAttachmentCount].pNext = nullptr;
        asVLKN_Colour_Attachment[sVLKN_Rendering_Info.colorAttachmentCount].imageView = psRender_Target->m_ahVLKN_Colour_Image_View[uiIndex];
        asVLKN_Colour_Attachment[sVLKN_Rendering_Info.colorAttachmentCount].imageLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
        asVLKN_Colour_Attachment[sVLKN_Rendering_Info.colorAttachmentCount].resolveMode = VK_RESOLVE_MODE_NONE;
        asVLKN_Colour_Attachment[sVLKN_Rendering_Info.colorAttachmentCount].resolveImageView = VK_NULL_HANDLE;
        asVLKN_Colour_Attachment[sVLKN_Rendering_Info.colorAttachmentCount].resolveImageLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        asVLKN_Colour_Attachment[sVLKN_Rendering_Info.colorAttachmentCount].storeOp = VK_ATTACHMENT_STORE_OP_STORE;

        if (psClear_Target && (psClear_Target->m_uiColour_Clear & (1ULL << uiIndex)))
        {
            asVLKN_Colour_Attachment[sVLKN_Rendering_Info.colorAttachmentCount].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
            asVLKN_Colour_Attachment[sVLKN_Rendering_Info.colorAttachmentCount].clearValue.color.float32[0] = psClear_Target->m_avColour_Clear[uiIndex].x;
            asVLKN_Colour_Attachment[sVLKN_Rendering_Info.colorAttachmentCount].clearValue.color.float32[1] = psClear_Target->m_avColour_Clear[uiIndex].y;
            asVLKN_Colour_Attachment[sVLKN_Rendering_Info.colorAttachmentCount].clearValue.color.float32[2] = psClear_Target->m_avColour_Clear[uiIndex].z;
            asVLKN_Colour_Attachment[sVLKN_Rendering_Info.colorAttachmentCount].clearValue.color.float32[3] = psClear_Target->m_avColour_Clear[uiIndex].w;
        }
        else
        {
            asVLKN_Colour_Attachment[sVLKN_Rendering_Info.colorAttachmentCount].loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        }

        ++sVLKN_Rendering_Info.colorAttachmentCount;
    }

    /* Setup depth/stencil attachment descriptor for dynamic rendering */

    if (VK_NULL_HANDLE != psRender_Target->m_hVLKN_Depth_Stencil_View)
    {
        TgBOOL_C                            bDepth_ReverseZ = psClear_Target ? psClear_Target->m_bDepth_ReverseZ : false;
        TgBOOL_C                            bClear_Depth = psClear_Target ? psClear_Target->m_bDepth_Clear : false;
        TgBOOL_C                            bClear_Stencil = psClear_Target ? psClear_Target->m_bStencil_Clear : false;

        sVLKN_Depth_Stencil_Attachment.sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO;
        sVLKN_Depth_Stencil_Attachment.pNext = nullptr;
        sVLKN_Depth_Stencil_Attachment.imageView = psRender_Target->m_hVLKN_Depth_Stencil_View;
        sVLKN_Depth_Stencil_Attachment.imageLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
        sVLKN_Depth_Stencil_Attachment.resolveMode = VK_RESOLVE_MODE_NONE;
        sVLKN_Depth_Stencil_Attachment.resolveImageView = VK_NULL_HANDLE;
        sVLKN_Depth_Stencil_Attachment.resolveImageLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        sVLKN_Depth_Stencil_Attachment.loadOp = bClear_Depth ? VK_ATTACHMENT_LOAD_OP_CLEAR : VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        sVLKN_Depth_Stencil_Attachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
        sVLKN_Depth_Stencil_Attachment.clearValue.depthStencil.depth = bDepth_ReverseZ ? 0.0F : 1.0F;
        sVLKN_Depth_Stencil_Attachment.clearValue.depthStencil.stencil = psRender_Target->m_bStencil_Valid && bClear_Stencil;

        sVLKN_Rendering_Info.pDepthAttachment = &sVLKN_Depth_Stencil_Attachment;
        sVLKN_Rendering_Info.pStencilAttachment = psRender_Target->m_bStencil_Valid ? &sVLKN_Depth_Stencil_Attachment : nullptr;
    }

    vkCmdBeginRendering(uCMD.psVLKN->m_hVLKN_Command_Buffer, &sVLKN_Rendering_Info);

    if (KTgKN_GPU_CXT_SWAP_ID__INVALID.m_uiKI != tiCXT_SWAP.m_uiKI)
    {
        STg2_KN_GPU_CXT_SWAP_PC                     psCXT_SWAP = g_asKN_GPU_CXT_SWAP + tiCXT_SWAP.m_uiI;

        tgKN_GPU_EXT__CMD__Update_Render_DESC_Descriptor_Set( psCMD, psCamera, psDBG_Render_DESC, &psCXT_SWAP->m_sOutput_DESC );
    }
    else
    {
        tgKN_GPU_EXT__CMD__Update_Render_DESC_Descriptor_Set( psCMD, psCamera, psDBG_Render_DESC, nullptr );
    }

#if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)
    {
        STg2_KN_GPU_DBG_VLKN_CXT_SWAP_PC    psVLKN_DBG_CXT_SWAP = g_asKN_GPU_DBG_EXT_CXT_SWAP + tiCXT_SWAP.m_uiI;
        STg2_KN_GPU_DBG_VLKN_CXT_EXEC_PC    psDBG_VLKN_CXT_EXEC = g_asKN_GPU_DBG_EXT_CXT_EXEC + uiEXEC;

        STg2_KN_GPU_DBG_VLKN_Render_Target_P psDBG_VLKN_Render_Target;
        union {
            STg2_KN_GPU_CMD_DBG_P               psCMD_DBG;
            STg2_KN_GPU_DBG_VLKN_CMD_P          psCMD_DBG_VLKN;
        }                                   uCMD_DBG;

        if (tiRender_Target.m_uiKI != KTgKN_GPU_RENDER_TARGET_ID__INVALID.m_uiKI)
        {
            psDBG_VLKN_Render_Target = psDBG_VLKN_CXT_EXEC->m_asRender_Target + tiRender_Target.m_uiI;
        }
        else
        {
            psDBG_VLKN_Render_Target = &psVLKN_DBG_CXT_SWAP->m_sDBG_Back_Buffer__Render_Target;
        }

        if (TgSUCCEEDED(tgKN_GPU_EXT__CMD__Command_Debug(&uCMD_DBG.psCMD_DBG, psCMD)))
        {
            TgVERIFY(VK_NULL_HANDLE != psDBG_VLKN_Render_Target->m_ahVLKN_Pipeline_Graphics[0]);
            tgMM_Copy( uCMD_DBG.psCMD_DBG_VLKN->m_ahVLKN_Pipeline_Graphics, sizeof(uCMD_DBG.psCMD_DBG_VLKN->m_ahVLKN_Pipeline_Graphics),
                       psDBG_VLKN_Render_Target->m_ahVLKN_Pipeline_Graphics, sizeof(psDBG_VLKN_Render_Target->m_ahVLKN_Pipeline_Graphics) );
        }
    }
/*# defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
#endif

    return (KTgS_OK);
}


/* ---- tgKN_GPU_EXT__CMD__End_Rendering ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_EXT__CMD__End_Rendering(
    STg2_KN_GPU_CMD_PC                          psCMD )
{
    UTg2_KN_GPU_CMD_C                           uCMD = { .ps = psCMD };

#if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)
    /* Flush cached debug draw calls. */
    tgKN_GPU__CMD__Render_Debug_Line( psCMD );
    tgKN_GPU__CMD__Render_Console_Text( psCMD );
/*# defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
#endif

    vkCmdEndRendering(uCMD.psVLKN->m_hVLKN_Command_Buffer);
}


/* ---- tgKN_GPU_EXT__CMD__Clear_Targets ----------------------------------------------------------------------------------------------------------------------------------------- */
/* "Unlike other clear commands, vkCmdClearAttachments is not a transfer command. It performs its operations in rasterization order. "                                             */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_EXT__CMD__Clear_Targets(
    STg2_KN_GPU_CMD_PC                          psCMD,
    TgKN_GPU_CXT_SWAP_ID_C                      tiCXT_SWAP,
    STg2_KN_GPU_Clear_Target_CPC                psCT )
{
    UTg2_KN_GPU_CMD_C                           uCMD = { .ps = psCMD };
    STg2_KN_GPU_VLKN_CXT_SWAP_PC                psVLKN_CXT_SWAP = g_asKN_GPU_EXT_CXT_SWAP + tiCXT_SWAP.m_uiI;

    VkClearAttachment                           asVLKN_Clear_Attachments[KTgKN_GPU_MAX_SIMULTANEOUS_TARGET_COUNT + 1];
    VkClearRect                                 sVLKN_Clear_Rect;
    TgUINT_E32                                  uiIndex, nuiAttachments;

    TgPARAM_CHECK_KN_GPU_CMD( psCMD );

    tgMM_Set_U08_0x00( asVLKN_Clear_Attachments, sizeof( asVLKN_Clear_Attachments ) );
    nuiAttachments = 0;

    /* Colour Attachment */

    for (uiIndex = 0; uiIndex < KTgKN_GPU_MAX_SIMULTANEOUS_TARGET_COUNT; ++uiIndex)
    {
        if (!(psCT->m_uiColour_Clear & (1ULL << uiIndex)))
        {
            continue;
        }

        asVLKN_Clear_Attachments[nuiAttachments].aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        asVLKN_Clear_Attachments[nuiAttachments].colorAttachment = uiIndex;
        asVLKN_Clear_Attachments[nuiAttachments].clearValue.color.float32[0] = psCT->m_avColour_Clear[uiIndex].x;
        asVLKN_Clear_Attachments[nuiAttachments].clearValue.color.float32[1] = psCT->m_avColour_Clear[uiIndex].y;
        asVLKN_Clear_Attachments[nuiAttachments].clearValue.color.float32[2] = psCT->m_avColour_Clear[uiIndex].z;
        asVLKN_Clear_Attachments[nuiAttachments].clearValue.color.float32[3] = psCT->m_avColour_Clear[uiIndex].w;
        ++nuiAttachments;
    }

    /* Depth Stencil Attachment */

    asVLKN_Clear_Attachments[nuiAttachments].aspectMask = 0;

    if (psCT->m_bStencil_Clear)
    {
        asVLKN_Clear_Attachments[nuiAttachments].aspectMask |= VK_IMAGE_ASPECT_STENCIL_BIT;
        asVLKN_Clear_Attachments[nuiAttachments].clearValue.depthStencil.stencil = psCT->m_uiStencil_Clear_Value;
    }

    if (psCT->m_bDepth_Clear)
    {
        asVLKN_Clear_Attachments[nuiAttachments].aspectMask |= VK_IMAGE_ASPECT_DEPTH_BIT;
        asVLKN_Clear_Attachments[nuiAttachments].clearValue.depthStencil.depth = psCT->m_bDepth_ReverseZ ? 1.0F : 0.0F;
    }

    if (psCT->m_bStencil_Clear || psCT->m_bDepth_Clear)
    {
        ++nuiAttachments;
    }

    if (0 == nuiAttachments)
    {
        return (KTgE_FAIL);
    }

    sVLKN_Clear_Rect.rect.offset.x = 0;
    sVLKN_Clear_Rect.rect.offset.y = 0;
    sVLKN_Clear_Rect.rect.extent = psVLKN_CXT_SWAP->m_sVLKN_Selected_Extent;
    sVLKN_Clear_Rect.baseArrayLayer = 0;
    sVLKN_Clear_Rect.layerCount = 1;

    /* Clear within render pass */
    vkCmdClearAttachments(uCMD.psVLKN->m_hVLKN_Command_Buffer, nuiAttachments, asVLKN_Clear_Attachments, 1, &sVLKN_Clear_Rect);

    return (KTgS_OK);
}


/* ---- tgKN_GPU_VLKN__CMD__Register_Resource_For_Release ------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_VLKN__CMD__Register_Resource_For_Release(
    STg2_KN_GPU_CMD_PC                          psCMD,
    VkBuffer                                    hBuffer,
    VkDeviceMemory                              hMemory )
{
    UTg2_KN_GPU_CMD_C                           uCMD = { .ps = psCMD };
    TgRSIZE                                     uiEXEC = (uCMD.ps->m_tiCXT_WORK.m_uiI >> 16) & 0xFFFF;
    STg2_KN_GPU_VLKN_CXT_EXEC_PC                psVLKN_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + uiEXEC;

    TgPARAM_CHECK_KN_GPU_CMD( uCMD.ps );

    {
        STg2_KN_GPU_VLKN_Release_Resource_PC psEXT_Release_Resource = psVLKN_CXT_EXEC->m_asRelease_Resource + psVLKN_CXT_EXEC->m_uiRelease_Resource_Producer_Index;

        tgCM_UT_LF__SN__Lock_Spin( &psVLKN_CXT_EXEC->m_sRelease_Resource_Lock.m_sLock );

        /* If we have exceeded the size of the array, we will do an immediate flush and wait. */
        /* TODO: Appears to have an issue with it as created a reference leak. */
        if (VK_NULL_HANDLE != psEXT_Release_Resource->m_hVLKN_Memory || VK_NULL_HANDLE != psEXT_Release_Resource->m_hVLKN_Buffer)
        {
            TgUINT_E64                                  uiPrevious_Fence_Value = psEXT_Release_Resource->m_uiFence_Value;

            STg2_KN_GPU_VLKN_Physical_Device_CP         psGPU_EXT_Physical_Device;
            STg2_KN_GPU_VLKN_CMD_Queue_P                psCMD_Queue;
            TgUINT_E64                                  uiFence_Value;
            VkSemaphoreSignalInfo                       sSignal_Info;
            VkSemaphoreWaitInfo                         sSemaphore_Wait_Info;
            TgUINT_E64                                  uiCompleted_Fence_Value;
            VkResult                                    eResult;
        
            psGPU_EXT_Physical_Device = g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Physical_Device + psVLKN_CXT_EXEC->m_idxCXT_HOST_Physical_Device;

            psCMD_Queue = psVLKN_CXT_EXEC->m_apsCmd_Queue[uCMD.psVLKN->m_enCmd_Queue];

            uiFence_Value = TgSTD_ATOMIC(fetch_add)( &psCMD_Queue->m_xuiTimeline_Signal_Value, 1 );

            tgMM_Set_U08_0x00( &sSignal_Info, sizeof( sSignal_Info ) );
            sSignal_Info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_SIGNAL_INFO;
            sSignal_Info.pNext = nullptr;
            sSignal_Info.semaphore = psCMD_Queue->m_hVLKN_Timeline;
            sSignal_Info.value = uiFence_Value;
        
            eResult = vkSignalSemaphore( psGPU_EXT_Physical_Device->m_hVLKN_Device, &sSignal_Info );
            TgVERIFY( VK_SUCCESS == eResult );

            tgMM_Set_U08_0x00( &sSemaphore_Wait_Info, sizeof( sSemaphore_Wait_Info ) );
            sSemaphore_Wait_Info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO;
            sSemaphore_Wait_Info.semaphoreCount = 1;
            sSemaphore_Wait_Info.pSemaphores = &psCMD_Queue->m_hVLKN_Timeline;
            sSemaphore_Wait_Info.pValues = &uiFence_Value;
            sSemaphore_Wait_Info.pNext = nullptr;
            sSemaphore_Wait_Info.flags = 0;
        
            tgCM_UT_LF__SN__Lock_Spin( &psCMD_Queue->m_sLock.m_sLock );
            eResult = vkGetSemaphoreCounterValue( psGPU_EXT_Physical_Device->m_hVLKN_Device, psCMD_Queue->m_hVLKN_Timeline, &uiCompleted_Fence_Value );
            tgCM_UT_LF__SN__Signal( &psCMD_Queue->m_sLock.m_sLock );
            TgVERIFY( VK_SUCCESS == eResult );
        
            if (uiCompleted_Fence_Value < uiFence_Value)
            {
                vkWaitSemaphores( psGPU_EXT_Physical_Device->m_hVLKN_Device, &sSemaphore_Wait_Info, 1000000000 );
            }

            TgVERIFY( uiPrevious_Fence_Value <= uiFence_Value );

            vkDestroyBuffer(psGPU_EXT_Physical_Device->m_hVLKN_Device, psEXT_Release_Resource->m_hVLKN_Buffer, g_psKN_GPU_VLKN_Allocator);
            psEXT_Release_Resource->m_hVLKN_Buffer = VK_NULL_HANDLE;
            vkFreeMemory(psGPU_EXT_Physical_Device->m_hVLKN_Device, psEXT_Release_Resource->m_hVLKN_Memory, g_psKN_GPU_VLKN_Allocator);
            psEXT_Release_Resource->m_hVLKN_Memory = VK_NULL_HANDLE;
        }

        psEXT_Release_Resource->m_hVLKN_Buffer = hBuffer;
        psEXT_Release_Resource->m_hVLKN_Memory = hMemory;
        psEXT_Release_Resource->m_enCmd_Queue = uCMD.psVLKN->m_enCmd_Queue;
        psEXT_Release_Resource->m_uiFence_Value = TgSTD_ATOMIC(load)( &psVLKN_CXT_EXEC->m_apsCmd_Queue[uCMD.psVLKN->m_enCmd_Queue]->m_xuiTimeline_Signal_Value);

        psVLKN_CXT_EXEC->m_uiRelease_Resource_Producer_Index = (psVLKN_CXT_EXEC->m_uiRelease_Resource_Producer_Index + 1) % KTgKN_GPU_MAX_RELEASE_RESOURCE;

        tgCM_UT_LF__SN__Signal( &psVLKN_CXT_EXEC->m_sRelease_Resource_Lock.m_sLock );
    }
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_GPU_EXT__Execute__Init ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_EXT__Execute__Init(
    TgKN_GPU_CXT_EXEC_ID_C                      tiCXT_EXEC )
{
    STg2_KN_GPU_VLKN_CXT_EXEC_PC                psVLKN_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + tiCXT_EXEC.m_uiI;
    STg2_KN_GPU_CXT_EXEC_PC                     psCXT_EXEC = g_asKN_GPU_CXT_EXEC + tiCXT_EXEC.m_uiI;

    STg2_KN_GPU_VLKN_Physical_Device_CP         psGPU_EXT_Physical_Device;
    VkDevice                                    hVLKN_Device;
    VkDeviceQueueInfo2                          sDevice_Queue_Info2;
    TgRSIZE                                     uiIndex;
    TgCHAR_U8                                   uszBuffer[128];

    TgPARAM_CHECK_INDEX( tiCXT_EXEC.m_uiI, g_asKN_GPU_CXT_EXEC );
    TgPARAM_CHECK( tgKN_GPU_CXT_EXEC_ID_Is_Equal( &(g_asKN_GPU_CXT_EXEC[tiCXT_EXEC.m_uiI].m_tiCXT_EXEC_S), tiCXT_EXEC ) );

    (void)uszBuffer;

    psGPU_EXT_Physical_Device = g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Physical_Device + psCXT_EXEC->m_idxCXT_HOST_Physical_Device;
    hVLKN_Device = psGPU_EXT_Physical_Device->m_hVLKN_Device;
    TgPARAM_CHECK( psGPU_EXT_Physical_Device->m_nuiUnique_Queue_Family > 0 );

    tgMM_Set_U08_0x00( psVLKN_CXT_EXEC, sizeof( STg2_KN_GPU_VLKN_CXT_EXEC ) );

    psVLKN_CXT_EXEC->m_idxCXT_HOST_Physical_Device = psCXT_EXEC->m_idxCXT_HOST_Physical_Device;
    psVLKN_CXT_EXEC->m_hVLKN_Physical_Device = psGPU_EXT_Physical_Device->m_hVLKN_Physical_Device;
    psVLKN_CXT_EXEC->m_hVLKN_Device = hVLKN_Device;
    tgMM_Copy( psVLKN_CXT_EXEC->m_auiVLKN_Queue_Family_Index, sizeof(psVLKN_CXT_EXEC->m_auiVLKN_Queue_Family_Index), psGPU_EXT_Physical_Device->m_auiVLKN_Queue_Family_Index,
               sizeof(psGPU_EXT_Physical_Device->m_auiVLKN_Queue_Family_Index) );
    psVLKN_CXT_EXEC->m_tiCXT_EXEC = tiCXT_EXEC;

    /* Initialize the Command Queues. */

    tgMM_Set_U08_0x00( &sDevice_Queue_Info2, sizeof( sDevice_Queue_Info2 ) );
    sDevice_Queue_Info2.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_INFO_2;
    sDevice_Queue_Info2.queueIndex = 0;

    for (uiIndex = 0; uiIndex < psGPU_EXT_Physical_Device->m_nuiUnique_Queue_Family; ++uiIndex)
    {
        TgRSIZE_C                           uiFamily_Index = psGPU_EXT_Physical_Device->m_auiUnique_Queue_Family_Index[uiIndex];
        STg2_KN_GPU_VLKN_CMD_Queue_P        psVLKN_Queue = psVLKN_CXT_EXEC->m_asCmd_Queue_Family_Indexed + uiFamily_Index;

        TgVERIFY(VK_NULL_HANDLE == psVLKN_Queue->m_hVLKN_Timeline);
        if (TgFAILED(tgKN_GPU_VLKN_Create_Semaphore_Timeline( &psVLKN_Queue->m_hVLKN_Timeline, hVLKN_Device )))
        {
            return (KTgE_FAIL);
        }
        tgUSZ_PrintF( uszBuffer, sizeof( uszBuffer ), u8"Queue Timeline %u/%u", (TgUINT_E32)uiFamily_Index, (TgUINT_E32)uiIndex );
        TgMACRO_KN_GPU_VLKN_SET_NAME(hVLKN_Device, VK_OBJECT_TYPE_SEMAPHORE, psVLKN_Queue->m_hVLKN_Timeline, uszBuffer);

        sDevice_Queue_Info2.queueFamilyIndex = (TgUINT_E32)psGPU_EXT_Physical_Device->m_auiUnique_Queue_Family_Index[uiIndex];
        vkGetDeviceQueue2(hVLKN_Device, &sDevice_Queue_Info2, &psVLKN_Queue->m_hVLKN_Queue);
 
        psVLKN_Queue->m_uiQueue_Family_Index = sDevice_Queue_Info2.queueFamilyIndex;
        TgSTD_ATOMIC(store)(&psVLKN_Queue->m_xuiTimeline_Signal_Value, 1); /* The first timeline update has to be greater than the initialized value of zero. */
        tgCM_UT_LF__SN__Init( &psVLKN_Queue->m_sLock.m_sLock );
    }

    for (uiIndex = 0; uiIndex < TgARRAY_COUNT(psVLKN_CXT_EXEC->m_apsCmd_Queue); ++uiIndex)
    {
        psVLKN_CXT_EXEC->m_apsCmd_Queue[uiIndex] = psVLKN_CXT_EXEC->m_asCmd_Queue_Family_Indexed + psGPU_EXT_Physical_Device->m_auiVLKN_Queue_Family_Index[uiIndex];
    }

    /* Initialize the Frame Data lock free stacks for Command Allocators and Command Queues. */
    for (uiIndex = 0; uiIndex < KTgKN_GPU_MAX_EXEC_CONTEXT_COMMAND; ++uiIndex)
    {
        if (TgFAILED( tgKN_GPU_VLKN_Context_Command_Init( hVLKN_Device, psVLKN_CXT_EXEC->m_sContext_Command + uiIndex ) ))
        {
            tgKN_GPU_EXT__Execute__Free( tiCXT_EXEC );
            return (KTgE_FAIL);
        }
    }

    tgCM_UT_LF__SN__Init( &psVLKN_CXT_EXEC->m_sRelease_Resource_Lock.m_sLock );

    tgCM_UT_LF__ST__Init_PreLoad( &psVLKN_CXT_EXEC->m_sCommand_Free_Stack.m_sStack, psVLKN_CXT_EXEC->m_asCommand, sizeof( STg2_KN_GPU_VLKN_CMD ),
                                  TgARRAY_COUNT( psVLKN_CXT_EXEC->m_asCommand ) );

    return (KTgS_OK);
}


/* ---- tgKN_GPU_EXT__Execute__Init__Create_Default_Resources__Pass_0 ------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_EXT__Execute__Init__Create_Default_Resources__Pass_0(
    STg2_KN_GPU_CMD_PC                          psCMD )
{
    UTg2_KN_GPU_CMD_C                           uCMD = { .ps = psCMD };
    TgRSIZE_C                                   uiEXEC = (uCMD.psVLKN->m_sBase.m_tiCXT_WORK.m_uiI >> 16) & 0xFFFF;
    TgRSIZE                                     uiWORK = (uCMD.psVLKN->m_sBase.m_tiCXT_WORK.m_uiI & 0xFFFF) % KTgKN_GPU_MAX_EXEC_CONTEXT_COMMAND;
    STg2_KN_GPU_VLKN_CXT_EXEC_PC                psVLKN_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + uiEXEC;

    VkDevice                                    hVLKN_Device;

    TgPARAM_CHECK_KN_GPU_CMD( psCMD );

    hVLKN_Device = psVLKN_CXT_EXEC->m_hVLKN_Device;

    /* Create default pipeline dependencies */
    if (TgFAILED(tgKN_GPU_VLKN__Execute__Init__Create_Pipeline_Dependencies( uCMD.psVLKN )))
    {
        tgKN_GPU_VLKN__Execute__Free__Destroy_Default_Resources(psVLKN_CXT_EXEC->m_sContext_Command[uiWORK].m_tiCXT_EXEC);
        return (KTgE_FAIL);
    }

    /* Create buffers */
    if (TgFAILED(tgKN_GPU_VLKN__Execute__Init__Create_Buffers( hVLKN_Device, uCMD.psVLKN, psVLKN_CXT_EXEC )))
    {
        tgKN_GPU_VLKN__Execute__Free__Destroy_Default_Resources(psVLKN_CXT_EXEC->m_sContext_Command[uiWORK].m_tiCXT_EXEC);
        return (KTgE_FAIL);
    }

    /* Create default command pools */
    if (TgFAILED(tgKN_GPU_VLKN__Execute__Init__Create_Descriptor_Pool( hVLKN_Device, psVLKN_CXT_EXEC )))
    {
        tgKN_GPU_VLKN__Execute__Free__Destroy_Default_Resources(psVLKN_CXT_EXEC->m_sContext_Command[uiWORK].m_tiCXT_EXEC);
        return (KTgE_FAIL);
    }

    return (KTgS_OK);
}


/* ---- tgKN_GPU_EXT__Execute__Init__Create_Default_Resources__Pass_1 ------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_EXT__Execute__Init__Create_Default_Resources__Pass_1(
    STg2_KN_GPU_CMD_PC                          psCMD )
{
    UTg2_KN_GPU_CMD_C                           uCMD = { .ps = psCMD };
    TgRSIZE_C                                   uiEXEC = (uCMD.psVLKN->m_sBase.m_tiCXT_WORK.m_uiI >> 16) & 0xFFFF;
    TgRSIZE                                     uiWORK = (uCMD.psVLKN->m_sBase.m_tiCXT_WORK.m_uiI & 0xFFFF) % KTgKN_GPU_MAX_EXEC_CONTEXT_COMMAND;
    STg2_KN_GPU_VLKN_CXT_EXEC_PC                psVLKN_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + uiEXEC;

    VkDevice                                    hVLKN_Device;

    TgPARAM_CHECK_KN_GPU_CMD( psCMD );

    hVLKN_Device = psVLKN_CXT_EXEC->m_hVLKN_Device;

    /* Create compute pipelines - There are none at this point, and running with cause a null reference */
    if (TgFAILED(tgKN_GPU_VLKN__Execute__Init__Create_Compute_Pipelines(uCMD.psVLKN)))
    {
        tgKN_GPU_VLKN__Execute__Free__Destroy_Default_Resources(psVLKN_CXT_EXEC->m_sContext_Command[uiWORK].m_tiCXT_EXEC);
        return (KTgE_FAIL);
    }

    /* Create default descriptor sets */
    if (TgFAILED(tgKN_GPU_VLKN__Execute__Init__Create_Descriptor_Sets( hVLKN_Device, uiEXEC )))
    {
        tgKN_GPU_VLKN__Execute__Free__Destroy_Default_Resources(psVLKN_CXT_EXEC->m_sContext_Command[uiWORK].m_tiCXT_EXEC);
        return (KTgE_FAIL);
    }

    return (KTgS_OK);
}


/* ---- tgKN_GPU_VLKN__Execute__Init__Update_Default_Descriptor_Sets ------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_VLKN__Execute__Init__Update_Default_Descriptor_Sets(
    VkDevice_C                                  hVLKN_Device,
    TgRSIZE_C                                   uiEXEC )
{
    STg2_KN_GPU_VLKN_CXT_EXEC_PC                psVLKN_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + uiEXEC;

    VkDescriptorBufferInfo                      sVLKN_Buffer_Info = {
                                                    .buffer = psVLKN_CXT_EXEC->m_hVLKN_Buffer__Render_DESC,
                                                    .offset = 0,
                                                    .range = psVLKN_CXT_EXEC->m_uiUBO_Aligned_Render_DESC_Size
                                                };

    VkWriteDescriptorSet                        asVLKN_Descriptor_Writes[6];
    TgUINT_E32                                  nuiDescriptor_Writes;
    TgUINT_E32                                  nuiResource;

    TgVERIFY(VK_NULL_HANDLE != psVLKN_CXT_EXEC->m_hVLKN_Descriptor_Pool);

    nuiDescriptor_Writes = 0;

    /* Always add the render DESC uniform buffer */
    asVLKN_Descriptor_Writes[nuiDescriptor_Writes].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    asVLKN_Descriptor_Writes[nuiDescriptor_Writes].pNext = nullptr;
    asVLKN_Descriptor_Writes[nuiDescriptor_Writes].dstSet = psVLKN_CXT_EXEC->m_hVLKN_Descriptor_Set_Render_DESC;
    asVLKN_Descriptor_Writes[nuiDescriptor_Writes].dstBinding = KTgMACRO_KN_GPU_VLKN_BINDING_RENDER_DESC;
    asVLKN_Descriptor_Writes[nuiDescriptor_Writes].dstArrayElement = 0;
    asVLKN_Descriptor_Writes[nuiDescriptor_Writes].descriptorCount = 1;
    asVLKN_Descriptor_Writes[nuiDescriptor_Writes].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
    asVLKN_Descriptor_Writes[nuiDescriptor_Writes].pImageInfo = nullptr;
    asVLKN_Descriptor_Writes[nuiDescriptor_Writes].pBufferInfo = &sVLKN_Buffer_Info;
    asVLKN_Descriptor_Writes[nuiDescriptor_Writes].pTexelBufferView = nullptr;
    ++nuiDescriptor_Writes;

    nuiResource = (TgUINT_E32)TgSTD_ATOMIC(load)(&psVLKN_CXT_EXEC->m_xnuiRT_IMG);
    nuiResource = tgCM_MIN_U32(nuiResource, (TgUINT_E32)TgARRAY_COUNT(psVLKN_CXT_EXEC->m_asVLKN_DS_Info_RT_IMG));
    if (nuiResource > 0)
    {
        asVLKN_Descriptor_Writes[nuiDescriptor_Writes].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        asVLKN_Descriptor_Writes[nuiDescriptor_Writes].pNext = nullptr;
        asVLKN_Descriptor_Writes[nuiDescriptor_Writes].dstSet = psVLKN_CXT_EXEC->m_hVLKN_Descriptor_Set_Render_DESC;
        asVLKN_Descriptor_Writes[nuiDescriptor_Writes].dstBinding = KTgMACRO_KN_GPU_VLKN_BINDING_TX_IMG_IMAGE;
        asVLKN_Descriptor_Writes[nuiDescriptor_Writes].dstArrayElement = 0;
        asVLKN_Descriptor_Writes[nuiDescriptor_Writes].descriptorCount = nuiResource;
        asVLKN_Descriptor_Writes[nuiDescriptor_Writes].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
        asVLKN_Descriptor_Writes[nuiDescriptor_Writes].pImageInfo = psVLKN_CXT_EXEC->m_asVLKN_DS_Info_RT_IMG;
        asVLKN_Descriptor_Writes[nuiDescriptor_Writes].pBufferInfo = nullptr;
        asVLKN_Descriptor_Writes[nuiDescriptor_Writes].pTexelBufferView = nullptr;
        ++nuiDescriptor_Writes;
    }

    nuiResource = (TgUINT_E32)TgSTD_ATOMIC(load)(&psVLKN_CXT_EXEC->m_xnuiTX_IMG_INST);
    nuiResource = tgCM_MIN_U32(nuiResource, (TgUINT_E32)TgARRAY_COUNT(psVLKN_CXT_EXEC->m_asVLKN_DS_Info_TX_IMG));
    if (nuiResource > 0)
    {
        asVLKN_Descriptor_Writes[nuiDescriptor_Writes].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        asVLKN_Descriptor_Writes[nuiDescriptor_Writes].pNext = nullptr;
        asVLKN_Descriptor_Writes[nuiDescriptor_Writes].dstSet = psVLKN_CXT_EXEC->m_hVLKN_Descriptor_Set_Render_DESC;
        asVLKN_Descriptor_Writes[nuiDescriptor_Writes].dstBinding = KTgMACRO_KN_GPU_VLKN_BINDING_TX_IMG;
        asVLKN_Descriptor_Writes[nuiDescriptor_Writes].dstArrayElement = 0;
        asVLKN_Descriptor_Writes[nuiDescriptor_Writes].descriptorCount = nuiResource;
        asVLKN_Descriptor_Writes[nuiDescriptor_Writes].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        asVLKN_Descriptor_Writes[nuiDescriptor_Writes].pImageInfo = psVLKN_CXT_EXEC->m_asVLKN_DS_Info_TX_IMG;
        asVLKN_Descriptor_Writes[nuiDescriptor_Writes].pBufferInfo = nullptr;
        asVLKN_Descriptor_Writes[nuiDescriptor_Writes].pTexelBufferView = nullptr;
        ++nuiDescriptor_Writes;
    }

    nuiResource = (TgUINT_E32)TgSTD_ATOMIC(load)(&psVLKN_CXT_EXEC->m_xnuiTX_CBE_INST);
    nuiResource = tgCM_MIN_U32(nuiResource, (TgUINT_E32)TgARRAY_COUNT(psVLKN_CXT_EXEC->m_asVLKN_DS_Info_TX_CBE));
    if (nuiResource > 0)
    {
        asVLKN_Descriptor_Writes[nuiDescriptor_Writes].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        asVLKN_Descriptor_Writes[nuiDescriptor_Writes].pNext = nullptr;
        asVLKN_Descriptor_Writes[nuiDescriptor_Writes].dstSet = psVLKN_CXT_EXEC->m_hVLKN_Descriptor_Set_Render_DESC;
        asVLKN_Descriptor_Writes[nuiDescriptor_Writes].dstBinding = KTgMACRO_KN_GPU_VLKN_BINDING_TX_CBE;
        asVLKN_Descriptor_Writes[nuiDescriptor_Writes].dstArrayElement = 0;
        asVLKN_Descriptor_Writes[nuiDescriptor_Writes].descriptorCount = nuiResource;
        asVLKN_Descriptor_Writes[nuiDescriptor_Writes].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        asVLKN_Descriptor_Writes[nuiDescriptor_Writes].pImageInfo = psVLKN_CXT_EXEC->m_asVLKN_DS_Info_TX_CBE;
        asVLKN_Descriptor_Writes[nuiDescriptor_Writes].pBufferInfo = nullptr;
        asVLKN_Descriptor_Writes[nuiDescriptor_Writes].pTexelBufferView = nullptr;
        ++nuiDescriptor_Writes;
    }

    nuiResource = (TgUINT_E32)TgSTD_ATOMIC(load)(&psVLKN_CXT_EXEC->m_xnuiTX_VOL_INST);
    nuiResource = tgCM_MIN_U32(nuiResource, (TgUINT_E32)TgARRAY_COUNT(psVLKN_CXT_EXEC->m_asVLKN_DS_Info_TX_VOL));
    if (nuiResource > 0)
    {
        asVLKN_Descriptor_Writes[nuiDescriptor_Writes].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        asVLKN_Descriptor_Writes[nuiDescriptor_Writes].pNext = nullptr;
        asVLKN_Descriptor_Writes[nuiDescriptor_Writes].dstSet = psVLKN_CXT_EXEC->m_hVLKN_Descriptor_Set_Render_DESC;
        asVLKN_Descriptor_Writes[nuiDescriptor_Writes].dstBinding = KTgMACRO_KN_GPU_VLKN_BINDING_TX_VOL;
        asVLKN_Descriptor_Writes[nuiDescriptor_Writes].dstArrayElement = 0;
        asVLKN_Descriptor_Writes[nuiDescriptor_Writes].descriptorCount = nuiResource;
        asVLKN_Descriptor_Writes[nuiDescriptor_Writes].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        asVLKN_Descriptor_Writes[nuiDescriptor_Writes].pImageInfo = psVLKN_CXT_EXEC->m_asVLKN_DS_Info_TX_VOL;
        asVLKN_Descriptor_Writes[nuiDescriptor_Writes].pBufferInfo = nullptr;
        asVLKN_Descriptor_Writes[nuiDescriptor_Writes].pTexelBufferView = nullptr;
        ++nuiDescriptor_Writes;
    }

    vkUpdateDescriptorSets( hVLKN_Device, nuiDescriptor_Writes, asVLKN_Descriptor_Writes, 0, nullptr );

    return (KTgS_OK);
}


/* ---- tgKN_GPU_EXT__Execute__Free ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_EXT__Execute__Free(
    TgKN_GPU_CXT_EXEC_ID_C                      tiCXT_EXEC )
{
    STg2_KN_GPU_VLKN_CXT_EXEC_PC                psVLKN_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + tiCXT_EXEC.m_uiI;

    STg2_KN_GPU_VLKN_Physical_Device_CP         psGPU_EXT_Physical_Device;
    TgRSIZE                                     uiIndex;

    TgPARAM_CHECK_INDEX( tiCXT_EXEC.m_uiI, g_asKN_GPU_CXT_EXEC );
    TgPARAM_CHECK( tgKN_GPU_CXT_EXEC_ID_Is_Equal( &(g_asKN_GPU_CXT_EXEC[tiCXT_EXEC.m_uiI].m_tiCXT_EXEC_S), tiCXT_EXEC ) );

    psGPU_EXT_Physical_Device = g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Physical_Device + psVLKN_CXT_EXEC->m_idxCXT_HOST_Physical_Device;

    /* Wait for all operations to complete */
    if (VK_NULL_HANDLE != psGPU_EXT_Physical_Device->m_hVLKN_Device)
    {
        tgKN_GPU_EXT__Execute__Flush(tiCXT_EXEC);
    }

    tgKN_GPU_VLKN__Execute__Free__Destroy_Default_Resources( tiCXT_EXEC );

    for (uiIndex = 0; uiIndex < TgARRAY_COUNT(psVLKN_CXT_EXEC->m_sContext_Command); ++uiIndex)
    {
        tgKN_GPU_VLKN_Context_Command_Free( tiCXT_EXEC, psVLKN_CXT_EXEC->m_sContext_Command + uiIndex );
    }

    /* Free the Command Queues. */
    for (uiIndex = 0; uiIndex < psGPU_EXT_Physical_Device->m_nuiUnique_Queue_Family; ++uiIndex)
    {
        TgRSIZE_C                           uiFamily_Index = psGPU_EXT_Physical_Device->m_auiUnique_Queue_Family_Index[uiIndex];
        STg2_KN_GPU_VLKN_CMD_Queue_P        psVLKN_Queue = psVLKN_CXT_EXEC->m_asCmd_Queue_Family_Indexed + uiFamily_Index;

        if (VK_NULL_HANDLE != psVLKN_Queue->m_hVLKN_Timeline)
        {
            vkDestroySemaphore( psGPU_EXT_Physical_Device->m_hVLKN_Device, psVLKN_Queue->m_hVLKN_Timeline, g_psKN_GPU_VLKN_Allocator );
            psVLKN_Queue->m_hVLKN_Timeline = VK_NULL_HANDLE;
        }

        psVLKN_Queue->m_hVLKN_Queue = VK_NULL_HANDLE;
        tgCM_UT_LF__SN__Free_Unsafe( &psVLKN_Queue->m_sLock.m_sLock );
    }

    tgMM_Set_U08_0x00( psVLKN_CXT_EXEC, sizeof( STg2_KN_GPU_VLKN_CXT_EXEC ) );
}


/* ---- tgKN_GPU_EXT__WORK__Query_And_Reset_Timestamp_Pool ----------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_EXT__WORK__Query_And_Reset_Timestamp_Pool(
    TgKN_GPU_CXT_WORK_ID_C                      tiCXT_WORK)
{
    TgRSIZE                                     uiEXEC = (tiCXT_WORK.m_uiI >> 16) & 0xFFFF;
    TgRSIZE                                     uiWORK = (tiCXT_WORK.m_uiI & 0xFFFF) % KTgKN_GPU_MAX_EXEC_CONTEXT_COMMAND;
    STg2_KN_GPU_VLKN_CXT_EXEC_PC                psVLKN_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + uiEXEC;
    STg2_KN_GPU_VLKN_CXT_CMD_PC                 psVLKN_CXT_CMD = psVLKN_CXT_EXEC->m_sContext_Command + uiWORK;
    TgUINT_E32_C                                uiTimestamp_Count = (TgUINT_E32)TgSTD_ATOMIC(load)( &psVLKN_CXT_CMD->m_xuiVLKN_Timestamp );

    TgPARAM_CHECK( uiTimestamp_Count <= KTgKN_GPU_VLKN_TIMESTAMP_QUERIES_PER_POOL );

    tgMM_Set_U08_0x00(psVLKN_CXT_CMD->m_auiTimestamps, sizeof(psVLKN_CXT_CMD->m_auiTimestamps ) );

    if (uiTimestamp_Count > 0)
    {
        vkGetQueryPoolResults(
            psVLKN_CXT_EXEC->m_hVLKN_Device,
            psVLKN_CXT_CMD->m_hVLKN_Timestamp_Query_Pool,
            0,
            uiTimestamp_Count,
            uiTimestamp_Count * sizeof(TgUINT_E64),
            psVLKN_CXT_CMD->m_auiTimestamps,
            sizeof(TgUINT_E64),
            VK_QUERY_RESULT_64_BIT | VK_QUERY_RESULT_WAIT_BIT
        );
    }
    
    /* Reset query pool for this frame */
    vkResetQueryPool(psVLKN_CXT_EXEC->m_hVLKN_Device, psVLKN_CXT_CMD->m_hVLKN_Timestamp_Query_Pool, 0, KTgKN_GPU_VLKN_TIMESTAMP_QUERIES_PER_POOL );
    TgSTD_ATOMIC(store)( &psVLKN_CXT_CMD->m_xuiVLKN_Timestamp, 0 );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_GPU_VLKN_Context_Command_Init__Cmd_Pool_Lock_Free_Stacks ------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgKN_GPU_VLKN_Context_Command_Init__Cmd_Pool_Lock_Free_Stacks(
    STg2_KN_GPU_VLKN_CXT_CMD_PC                 psVLKN_CXT_CMD )
{
    /* Add the command pool pools (ick) to the lock free stacks. */
    tgCM_UT_LF__ST__Init_PreLoad( &psVLKN_CXT_CMD->m_sStack_Cmd_Pool_Free[ETgKN_GPU_EXT_COMMAND_GRAPHICS].m_sStack, psVLKN_CXT_CMD->m_asCmd_Pool__Graphics,
                                  sizeof(psVLKN_CXT_CMD->m_asCmd_Pool__Graphics[0]), TgARRAY_COUNT(psVLKN_CXT_CMD->m_asCmd_Pool__Graphics));

    tgCM_UT_LF__ST__Init_PreLoad( &psVLKN_CXT_CMD->m_sStack_Cmd_Pool_Free[ETgKN_GPU_EXT_COMMAND_PRESENT].m_sStack, psVLKN_CXT_CMD->m_asCmd_Pool__Present,
                                  sizeof(psVLKN_CXT_CMD->m_asCmd_Pool__Present[0]), TgARRAY_COUNT( psVLKN_CXT_CMD->m_asCmd_Pool__Present ) );

    tgCM_UT_LF__ST__Init_PreLoad( &psVLKN_CXT_CMD->m_sStack_Cmd_Pool_Free[ETgKN_GPU_EXT_COMMAND_COMPUTE].m_sStack, psVLKN_CXT_CMD->m_asCmd_Pool__Compute,
                                  sizeof(psVLKN_CXT_CMD->m_asCmd_Pool__Compute[0]), TgARRAY_COUNT( psVLKN_CXT_CMD->m_asCmd_Pool__Compute ) );

    tgCM_UT_LF__ST__Init_PreLoad( &psVLKN_CXT_CMD->m_sStack_Cmd_Pool_Free[ETgKN_GPU_EXT_COMMAND_TRANSFER].m_sStack, psVLKN_CXT_CMD->m_asCmd_Pool__Transfer,
                                  sizeof(psVLKN_CXT_CMD->m_asCmd_Pool__Transfer[0]), TgARRAY_COUNT( psVLKN_CXT_CMD->m_asCmd_Pool__Transfer ) );
}


/* ---- tgKN_GPU_VLKN_Context_Command_Init --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT tgKN_GPU_VLKN_Context_Command_Init(
    VkDevice_C                                  hVLKN_Device,
    STg2_KN_GPU_VLKN_CXT_CMD_PC                 psVLKN_CXT_CMD )
{
    VkQueryPoolCreateInfo_C                     sVLKN_Query_Pool_Create_Info = {
                                                    .sType = VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO,
                                                    .pNext = nullptr,
                                                    .flags = 0,
                                                    .queryType = VK_QUERY_TYPE_TIMESTAMP,
                                                    .queryCount = KTgKN_GPU_VLKN_TIMESTAMP_QUERIES_PER_POOL,
                                                    .pipelineStatistics = 0
                                                };

    TgRSIZE                                     uiIndex;
    VkResult                                    eResult;

    /* Create semaphores for frame synchronization */
    tgPM_MT_SM_Init( &psVLKN_CXT_CMD->m_sLock, nullptr, 1, 1 );

    /* Initialize queue family mask - tracks which queues had work this frame */
    TgSTD_ATOMIC(store)(&psVLKN_CXT_CMD->m_xuiUsed_Queue_Family_Mask, 0);

    /* Create fences for each queue family */
    for (uiIndex = 0; uiIndex < TgARRAY_COUNT(psVLKN_CXT_CMD->m_ahVLKN_Queue_Fence); ++uiIndex)
    {
        VkFenceCreateInfo           sFenceCreateInfo;

        tgMM_Set_U08_0x00(&sFenceCreateInfo, sizeof(sFenceCreateInfo));
        sFenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;

        eResult = vkCreateFence(hVLKN_Device, &sFenceCreateInfo, g_psKN_GPU_VLKN_Allocator, psVLKN_CXT_CMD->m_ahVLKN_Queue_Fence + uiIndex);
        if (VK_SUCCESS != eResult)
        {
            TgERROR_MSGF(0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create fence for queue family %zu: %d", uiIndex, eResult);
            return (KTgE_FAIL);
        }
    }

    /* Create timestamp query pool for GPU frame time measurement */
    eResult = vkCreateQueryPool(hVLKN_Device, &sVLKN_Query_Pool_Create_Info, g_psKN_GPU_VLKN_Allocator, &psVLKN_CXT_CMD->m_hVLKN_Timestamp_Query_Pool);
    if (VK_SUCCESS != eResult)
    {
        TgERROR_MSGF(false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create timestamp query pool: ", eResult);
        return (KTgE_FAIL);
    }
    vkResetQueryPool(hVLKN_Device, psVLKN_CXT_CMD->m_hVLKN_Timestamp_Query_Pool, 0, KTgKN_GPU_VLKN_TIMESTAMP_QUERIES_PER_POOL);
    TgSTD_ATOMIC(store)(&psVLKN_CXT_CMD->m_xuiVLKN_Timestamp, 0);

    tgKN_GPU_VLKN_Context_Command_Init__Cmd_Pool_Lock_Free_Stacks( psVLKN_CXT_CMD );

    /* Add the command buffer pools to the lock free stacks. */
    tgCM_UT_LF__ST__Init_PreLoad( &psVLKN_CXT_CMD->m_sStack_Cmd_Buffer.m_sStack, psVLKN_CXT_CMD->m_asCmd_Buffer, sizeof(psVLKN_CXT_CMD->m_asCmd_Buffer[0]),
                                  TgARRAY_COUNT(psVLKN_CXT_CMD->m_asCmd_Buffer) );

    tgCM_UT_LF__ST__Init_PreLoad( &psVLKN_CXT_CMD->m_sStack_DS_Pool_Free.m_sStack, psVLKN_CXT_CMD->m_asVLKN_Descriptor_Pool, sizeof(psVLKN_CXT_CMD->m_asVLKN_Descriptor_Pool[0]),
                                  TgARRAY_COUNT(psVLKN_CXT_CMD->m_asVLKN_Descriptor_Pool) );

    return (KTgS_OK);
}


/* ---- tgKN_GPU_VLKN_Context_Command_Free --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgKN_GPU_VLKN_Context_Command_Free(
    TgKN_GPU_CXT_EXEC_ID_C                      tiCXT_EXEC,
    STg2_KN_GPU_VLKN_CXT_CMD_PC                 psVLKN_CXT_CMD )
{
    STg2_KN_GPU_VLKN_CXT_EXEC_PC                psVLKN_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + tiCXT_EXEC.m_uiI;

    STg2_KN_GPU_VLKN_Physical_Device_CP         psGPU_EXT_Physical_Device;
    TgRSIZE                                     uiIndex;

    TgPARAM_CHECK_INDEX( tiCXT_EXEC.m_uiI, g_asKN_GPU_CXT_EXEC );
    TgPARAM_CHECK( tgKN_GPU_CXT_EXEC_ID_Is_Equal( &(g_asKN_GPU_CXT_EXEC[tiCXT_EXEC.m_uiI].m_tiCXT_EXEC_S), tiCXT_EXEC ) );

    psGPU_EXT_Physical_Device = g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Physical_Device + psVLKN_CXT_EXEC->m_idxCXT_HOST_Physical_Device;

    /* Destroy fences for each queue family */
    for (uiIndex = 0; uiIndex < TgARRAY_COUNT(psVLKN_CXT_CMD->m_ahVLKN_Queue_Fence); ++uiIndex)
    {
        if (VK_NULL_HANDLE != psVLKN_CXT_CMD->m_ahVLKN_Queue_Fence[uiIndex])
        {
            vkDestroyFence(psGPU_EXT_Physical_Device->m_hVLKN_Device, psVLKN_CXT_CMD->m_ahVLKN_Queue_Fence[uiIndex], g_psKN_GPU_VLKN_Allocator);
            psVLKN_CXT_CMD->m_ahVLKN_Queue_Fence[uiIndex] = VK_NULL_HANDLE;
        }
    }

    /* Destroy timestamp query pool */
    if (VK_NULL_HANDLE != psVLKN_CXT_CMD->m_hVLKN_Timestamp_Query_Pool)
    {
        vkDestroyQueryPool(psGPU_EXT_Physical_Device->m_hVLKN_Device, psVLKN_CXT_CMD->m_hVLKN_Timestamp_Query_Pool, g_psKN_GPU_VLKN_Allocator);
        psVLKN_CXT_CMD->m_hVLKN_Timestamp_Query_Pool = VK_NULL_HANDLE;
    }

    for (uiIndex = 0; uiIndex < TgARRAY_COUNT(psVLKN_CXT_CMD->m_asVLKN_Descriptor_Pool); ++uiIndex)
    {
        if (VK_NULL_HANDLE != psVLKN_CXT_CMD->m_asVLKN_Descriptor_Pool[uiIndex].m_hVLKN_Descriptor_Pool)
        {
            vkDestroyDescriptorPool(psGPU_EXT_Physical_Device->m_hVLKN_Device, psVLKN_CXT_CMD->m_asVLKN_Descriptor_Pool[uiIndex].m_hVLKN_Descriptor_Pool, g_psKN_GPU_VLKN_Allocator);
            psVLKN_CXT_CMD->m_asVLKN_Descriptor_Pool[uiIndex].m_hVLKN_Descriptor_Pool = VK_NULL_HANDLE;
        }
    }

    for (uiIndex = 0; uiIndex < TgARRAY_COUNT( psVLKN_CXT_CMD->m_asCmd_Buffer); ++uiIndex)
    {
        psVLKN_CXT_CMD->m_asCmd_Buffer[uiIndex].m_hVLKN_Command_Buffer = VK_NULL_HANDLE;
    }

    for (uiIndex = 0; uiIndex < TgARRAY_COUNT(psVLKN_CXT_CMD->m_asCmd_Pool__Graphics); ++uiIndex)
    {
        if (VK_NULL_HANDLE != psVLKN_CXT_CMD->m_asCmd_Pool__Graphics[uiIndex].m_hVLKN_Command_Pool)
        {
            vkDestroyCommandPool(psGPU_EXT_Physical_Device->m_hVLKN_Device, psVLKN_CXT_CMD->m_asCmd_Pool__Graphics[uiIndex].m_hVLKN_Command_Pool, g_psKN_GPU_VLKN_Allocator);
            psVLKN_CXT_CMD->m_asCmd_Pool__Graphics[uiIndex].m_hVLKN_Command_Pool = VK_NULL_HANDLE;
        }
    }

    for (uiIndex = 0; uiIndex < TgARRAY_COUNT(psVLKN_CXT_CMD->m_asCmd_Pool__Present); ++uiIndex)
    {
        if (VK_NULL_HANDLE != psVLKN_CXT_CMD->m_asCmd_Pool__Present[uiIndex].m_hVLKN_Command_Pool)
        {
            vkDestroyCommandPool(psGPU_EXT_Physical_Device->m_hVLKN_Device, psVLKN_CXT_CMD->m_asCmd_Pool__Present[uiIndex].m_hVLKN_Command_Pool, g_psKN_GPU_VLKN_Allocator);
            psVLKN_CXT_CMD->m_asCmd_Pool__Present[uiIndex].m_hVLKN_Command_Pool = VK_NULL_HANDLE;
        }
    }

    for (uiIndex = 0; uiIndex < TgARRAY_COUNT(psVLKN_CXT_CMD->m_asCmd_Pool__Compute); ++uiIndex)
    {
        if (VK_NULL_HANDLE != psVLKN_CXT_CMD->m_asCmd_Pool__Compute[uiIndex].m_hVLKN_Command_Pool)
        {
            vkDestroyCommandPool(psGPU_EXT_Physical_Device->m_hVLKN_Device, psVLKN_CXT_CMD->m_asCmd_Pool__Compute[uiIndex].m_hVLKN_Command_Pool, g_psKN_GPU_VLKN_Allocator);
            psVLKN_CXT_CMD->m_asCmd_Pool__Compute[uiIndex].m_hVLKN_Command_Pool = VK_NULL_HANDLE;
        }
    }

    for (uiIndex = 0; uiIndex < TgARRAY_COUNT(psVLKN_CXT_CMD->m_asCmd_Pool__Transfer); ++uiIndex)
    {
        if (VK_NULL_HANDLE != psVLKN_CXT_CMD->m_asCmd_Pool__Transfer[uiIndex].m_hVLKN_Command_Pool)
        {
            vkDestroyCommandPool(psGPU_EXT_Physical_Device->m_hVLKN_Device, psVLKN_CXT_CMD->m_asCmd_Pool__Transfer[uiIndex].m_hVLKN_Command_Pool, g_psKN_GPU_VLKN_Allocator);
            psVLKN_CXT_CMD->m_asCmd_Pool__Transfer[uiIndex].m_hVLKN_Command_Pool = VK_NULL_HANDLE;
        }
    }

    tgPM_MT_SM_Free( &psVLKN_CXT_CMD->m_sLock );
}


/* ---- tgKN_GPU_VLKN__Execute__Init__Create_Buffers ----------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT tgKN_GPU_VLKN__Execute__Init__Create_Buffers(
    VkDevice_C                                  hVLKN_Device,
    STg2_KN_GPU_VLKN_CMD_PC                     psVLKN_CMD,
    STg2_KN_GPU_VLKN_CXT_EXEC_PC                psVLKN_CXT_EXEC )
{
    STg2_KN_GPU_VLKN_Physical_Device_CP         psGPU_EXT_Physical_Device;
    TgRSIZE                                     uiMin_UBO_Alignment, nonCoherentAtomSize;
    TgUINT_E64                                  uiResource_Descriptor_UBO;
    VkResult                                    eResult;
    VkBuffer_P                                  phVLKN_Buffer;
    VkDeviceMemory_P                            phVLKN_Memory;
    TgRSIZE                                     uiBuffer_Size;
    TgUINT_E32                                  auiQueue[2];

    psGPU_EXT_Physical_Device = g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Physical_Device + psVLKN_CXT_EXEC->m_idxCXT_HOST_Physical_Device;
    uiMin_UBO_Alignment = psGPU_EXT_Physical_Device->m_sVLKN_Properties.limits.minUniformBufferOffsetAlignment;
    uiMin_UBO_Alignment = uiMin_UBO_Alignment > 0 ? uiMin_UBO_Alignment : 1;
    nonCoherentAtomSize = psGPU_EXT_Physical_Device->m_sVLKN_Properties.limits.nonCoherentAtomSize;
    nonCoherentAtomSize  = nonCoherentAtomSize > 0 ? nonCoherentAtomSize : 1;
    TgVERIFY(nonCoherentAtomSize >= uiMin_UBO_Alignment);
    TgVERIFY(nonCoherentAtomSize % uiMin_UBO_Alignment == 0);

    uiResource_Descriptor_UBO  = ETgKN_GPU_RESOURCE_DESCRIPTOR__UNIFORM_BUFFER_DYNAMIC;
    uiResource_Descriptor_UBO |= ETgKN_GPU_RESOURCE_DESCRIPTOR__MEMORY_LOCAL;
    uiResource_Descriptor_UBO |= ETgKN_GPU_RESOURCE_DESCRIPTOR__MEMORY_HOST_VISIBLE;

    /* Create Buffers */
    auiQueue[0] = (TgUINT_E32)psVLKN_CXT_EXEC->m_auiVLKN_Queue_Family_Index[ETgKN_GPU_EXT_COMMAND_GRAPHICS];
    auiQueue[1] = (TgUINT_E32)psVLKN_CXT_EXEC->m_auiVLKN_Queue_Family_Index[ETgKN_GPU_EXT_COMMAND_COMPUTE];
    psVLKN_CXT_EXEC->m_uiUBO_Aligned_Render_DESC_Size = tgCM_CEL_ALGN_PW2_UMAX(sizeof(STg2_KN_GPU_Render_DESC), nonCoherentAtomSize);
    phVLKN_Buffer = &psVLKN_CXT_EXEC->m_hVLKN_Buffer__Render_DESC;
    phVLKN_Memory = &psVLKN_CXT_EXEC->m_hVLKN_Memory__Render_DESC;
    uiBuffer_Size = KTgKN_GPU_MAX_RENDER_DESC_PER_FRAME * KTgKN_GPU_MAX_EXEC_CONTEXT_COMMAND * psVLKN_CXT_EXEC->m_uiUBO_Aligned_Render_DESC_Size;
    if (TgFAILED(tgKN_GPU_VLKN__CMD__Create_Buffer( phVLKN_Buffer, phVLKN_Memory, psVLKN_CMD, uiResource_Descriptor_UBO, uiBuffer_Size, auiQueue, TgARRAY_COUNT(auiQueue) )))
    {
        TgERROR_MSG( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create debug render targets uniform buffer" );
        return (KTgE_FAIL);
    }
    TgMACRO_KN_GPU_VLKN_SET_NAME(hVLKN_Device, VK_OBJECT_TYPE_BUFFER, psVLKN_CXT_EXEC->m_hVLKN_Buffer__Render_DESC, u8"Execution Context Resource: UBO Render DESC");
    eResult = vkMapMemory( hVLKN_Device, *phVLKN_Memory, 0, VK_WHOLE_SIZE, 0, &psVLKN_CXT_EXEC->m_uUBO_Mapped_Render_DESC.m_pVoid );
    if (VK_SUCCESS != eResult)
    {
        TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to map memory for debug render targets uniform buffer." );
        return (KTgE_FAIL);
    }

    return (KTgS_OK);
}


/* ---- tgKN_GPU_VLKN__Execute__Init__Create_Descriptor_Pool --------------------------------------------------------------------------------------------------------------------- */
/* This pool is used for internal allocations  - primarily the shared descriptor set 0                                                                                             */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT tgKN_GPU_VLKN__Execute__Init__Create_Descriptor_Pool(
    VkDevice_C                          hVLKN_Device,
    STg2_KN_GPU_VLKN_CXT_EXEC_PC        psVLKN_CXT_EXEC )
{
    TgRSIZE_C                           nuiTotal_Image_Samplers = KTgKN_GPU_MAX_TX_IMG_INST + KTgKN_GPU_MAX_TX_CBE_INST + KTgKN_GPU_MAX_TX_VOL_INST;
    VkDescriptorPoolSize_C              asVLKN_Pool_Sizes[] = {
                                            {
                                                .type = VK_DESCRIPTOR_TYPE_SAMPLER,
                                                .descriptorCount = KTgKN_GPU_MAX_RENDER_TARGET_PER_FRAME * (TgRSIZE)ETgKN_GPU_DEFAULT_SAMPLER_COUNT,
                                            },
                                            {
                                                .type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC,
                                                .descriptorCount = KTgKN_GPU_MAX_RENDER_TARGET_PER_FRAME,
                                            },
                                            {
                                                .type = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE,
                                                .descriptorCount = KTgKN_GPU_MAX_RENDER_TARGET_PER_FRAME * KTgKN_GPU_MAX_RENDER_TARGET_IMAGE * 2,
                                            },
                                            {
                                                .type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
                                                .descriptorCount = KTgKN_GPU_MAX_RENDER_TARGET_PER_FRAME * nuiTotal_Image_Samplers,
                                            }
                                        };

    VkDescriptorPoolCI_C                sVLKN_Pool_CI = {
                                            .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
                                            .pNext = nullptr,
                                            .flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT  | VK_DESCRIPTOR_POOL_CREATE_UPDATE_AFTER_BIND_BIT,
                                            .maxSets = 1024,
                                            .poolSizeCount = TgARRAY_COUNT(asVLKN_Pool_Sizes),
                                            .pPoolSizes = asVLKN_Pool_Sizes
                                        };

    VkResult                            eResult;

    eResult = vkCreateDescriptorPool( hVLKN_Device, &sVLKN_Pool_CI, g_psKN_GPU_VLKN_Allocator, &psVLKN_CXT_EXEC->m_hVLKN_Descriptor_Pool );
    if (VK_SUCCESS != eResult)
    {
        TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create descriptor pool for Execution Context" );
        psVLKN_CXT_EXEC->m_hVLKN_Descriptor_Pool = VK_NULL_HANDLE;
        return( KTgE_FAIL );
    };
    return (KTgS_OK);
}


/* ---- tgKN_GPU_VLKN__Execute__Init__Create_Descriptor_Sets --------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT tgKN_GPU_VLKN__Execute__Init__Create_Descriptor_Sets(
    VkDevice_C                                  hVLKN_Device,
    TgRSIZE_C                                   uiEXEC )
{
    STg2_KN_GPU_VLKN_CXT_EXEC_PC                psVLKN_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + uiEXEC;

    VkDescriptorSetAllocateInfo                 sVLKN_Alloc_Info;
    VkDescriptorSet                             hVLKN_Descriptor_Set;
    VkResult                                    eResult;

    TgVERIFY(VK_NULL_HANDLE != psVLKN_CXT_EXEC->m_hVLKN_Descriptor_Pool);

    sVLKN_Alloc_Info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    sVLKN_Alloc_Info.pNext = nullptr;
    sVLKN_Alloc_Info.descriptorPool = psVLKN_CXT_EXEC->m_hVLKN_Descriptor_Pool;
    sVLKN_Alloc_Info.descriptorSetCount = 1;
    sVLKN_Alloc_Info.pSetLayouts = psVLKN_CXT_EXEC->m_ahVLKN_Descriptor_Set_Layout + ETgKN_GPU_VLKN_DESCRIPTOR_SET_LAYOUT__BASE_SHARED;

    eResult = vkAllocateDescriptorSets( hVLKN_Device, &sVLKN_Alloc_Info, &hVLKN_Descriptor_Set );

    if (eResult != VK_SUCCESS)
    {
        TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to allocate descriptor set" );
        return (KTgE_FAIL);
    }
    else
    {
        TgMACRO_KN_GPU_VLKN_SET_NAME(hVLKN_Device, VK_OBJECT_TYPE_DESCRIPTOR_SET, hVLKN_Descriptor_Set, u8"Render Descriptor Set");
        psVLKN_CXT_EXEC->m_hVLKN_Descriptor_Set_Render_DESC = hVLKN_Descriptor_Set;

    #if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)
        g_asKN_GPU_DBG_EXT_CXT_EXEC[uiEXEC].m_hVLKN_Descriptor_Set_Render_DESC = hVLKN_Descriptor_Set;
    /*# defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
    #endif

        return (tgKN_GPU_VLKN__Execute__Init__Update_Default_Descriptor_Sets(hVLKN_Device, uiEXEC));
    }
}


/* ---- tgKN_GPU_VLKN__Execute__Free__Destroy_Default_Resources ------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT tgKN_GPU_VLKN__Execute__Free__Destroy_Default_Resources(
    TgKN_GPU_CXT_EXEC_ID_C                      tiCXT_EXEC )
{
    STg2_KN_GPU_VLKN_CXT_EXEC_PC                psVLKN_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + tiCXT_EXEC.m_uiI;

    VkDevice                                    hVLKN_Device;

    TgPARAM_CHECK_INDEX( tiCXT_EXEC.m_uiI, g_asKN_GPU_CXT_EXEC );
    TgPARAM_CHECK( tgKN_GPU_CXT_EXEC_ID_Is_Equal( &(g_asKN_GPU_CXT_EXEC[tiCXT_EXEC.m_uiI].m_tiCXT_EXEC_S), tiCXT_EXEC ) );

    hVLKN_Device = psVLKN_CXT_EXEC->m_hVLKN_Device;

    if (VK_NULL_HANDLE != psVLKN_CXT_EXEC->m_hVLKN_Descriptor_Set_Render_DESC)
    {
        vkFreeDescriptorSets(hVLKN_Device, psVLKN_CXT_EXEC->m_hVLKN_Descriptor_Pool, 1, &psVLKN_CXT_EXEC->m_hVLKN_Descriptor_Set_Render_DESC);
        psVLKN_CXT_EXEC->m_hVLKN_Descriptor_Set_Render_DESC = VK_NULL_HANDLE;
    }

    if (VK_NULL_HANDLE != psVLKN_CXT_EXEC->m_hVLKN_Descriptor_Pool)
    {
        vkDestroyDescriptorPool(hVLKN_Device, psVLKN_CXT_EXEC->m_hVLKN_Descriptor_Pool, g_psKN_GPU_VLKN_Allocator);
        psVLKN_CXT_EXEC->m_hVLKN_Descriptor_Pool = VK_NULL_HANDLE;
    }

    if (VK_NULL_HANDLE != psVLKN_CXT_EXEC->m_hVLKN_Buffer__Render_DESC)
    {
        vkDestroyBuffer(hVLKN_Device, psVLKN_CXT_EXEC->m_hVLKN_Buffer__Render_DESC, g_psKN_GPU_VLKN_Allocator);
        vkFreeMemory(hVLKN_Device, psVLKN_CXT_EXEC->m_hVLKN_Memory__Render_DESC, g_psKN_GPU_VLKN_Allocator);
        psVLKN_CXT_EXEC->m_uiUBO_Aligned_Render_DESC_Size = 0;
        psVLKN_CXT_EXEC->m_uUBO_Mapped_Render_DESC.m_pVoid = nullptr;
    }

    tgKN_GPU_VLKN__Execute__Free__Destroy_Compute_Pipelines( tiCXT_EXEC );
    tgKN_GPU_VLKN__Execute__Free__Destroy_Pipeline_Dependencies( tiCXT_EXEC );

    return (KTgS_OK);
}


/* ---- tgKN_GPU_VLKN__Execute__Process_Resource_Release_List -------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgKN_GPU_VLKN__Execute__Process_Resource_Release_List(
    TgKN_GPU_CXT_EXEC_ID_C                      tiCXT_EXEC )
{
    STg2_KN_GPU_VLKN_CXT_EXEC_PC                psVLKN_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + tiCXT_EXEC.m_uiI;

    STg2_KN_GPU_VLKN_Physical_Device_CP         psGPU_EXT_Physical_Device;
    TgRSIZE                                     nuiLoop;
    VkResult                                    eResult;

    TgPARAM_CHECK_INDEX( tiCXT_EXEC.m_uiI, g_asKN_GPU_EXT_CXT_EXEC );
    TgPARAM_CHECK( tgKN_GPU_CXT_EXEC_ID_Is_Equal( &(g_asKN_GPU_CXT_EXEC[tiCXT_EXEC.m_uiI].m_tiCXT_EXEC_S), tiCXT_EXEC ) );

    tgCM_UT_LF__SN__Lock_Spin( &psVLKN_CXT_EXEC->m_sRelease_Resource_Lock.m_sLock );

    psGPU_EXT_Physical_Device = g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Physical_Device + psVLKN_CXT_EXEC->m_idxCXT_HOST_Physical_Device;

    for (nuiLoop = 0; nuiLoop < KTgKN_GPU_MAX_RELEASE_RESOURCE; ++nuiLoop)
    {
        VkBuffer                            hBuffer = psVLKN_CXT_EXEC->m_asRelease_Resource[psVLKN_CXT_EXEC->m_uiRelease_Resource_Consumer_Index].m_hVLKN_Buffer;
        VkDeviceMemory                      hMemory = psVLKN_CXT_EXEC->m_asRelease_Resource[psVLKN_CXT_EXEC->m_uiRelease_Resource_Consumer_Index].m_hVLKN_Memory;
        ETgKN_GPU_EXT_COMMAND               enCmd = psVLKN_CXT_EXEC->m_asRelease_Resource[psVLKN_CXT_EXEC->m_uiRelease_Resource_Consumer_Index].m_enCmd_Queue;
        TgUINT_E64                          uiFence_Value = psVLKN_CXT_EXEC->m_asRelease_Resource[psVLKN_CXT_EXEC->m_uiRelease_Resource_Consumer_Index].m_uiFence_Value;
        STg2_KN_GPU_VLKN_CMD_Queue_P        psCMD_Queue = psVLKN_CXT_EXEC->m_apsCmd_Queue[enCmd];

        TgUINT_E64                          uiCompleted_Fence_Value;

        tgCM_UT_LF__SN__Lock_Spin( &psCMD_Queue->m_sLock.m_sLock );
        eResult = vkGetSemaphoreCounterValue( psGPU_EXT_Physical_Device->m_hVLKN_Device, psCMD_Queue->m_hVLKN_Timeline, &uiCompleted_Fence_Value );
        tgCM_UT_LF__SN__Signal( &psCMD_Queue->m_sLock.m_sLock );
        
        TgVERIFY( VK_SUCCESS == eResult );
    
        if (VK_NULL_HANDLE == hMemory || uiFence_Value > uiCompleted_Fence_Value)
            break;

        vkDestroyBuffer(psGPU_EXT_Physical_Device->m_hVLKN_Device, hBuffer, g_psKN_GPU_VLKN_Allocator);
        psVLKN_CXT_EXEC->m_asRelease_Resource[psVLKN_CXT_EXEC->m_uiRelease_Resource_Consumer_Index].m_hVLKN_Buffer = VK_NULL_HANDLE;
        vkFreeMemory(psGPU_EXT_Physical_Device->m_hVLKN_Device, hMemory, g_psKN_GPU_VLKN_Allocator);
        psVLKN_CXT_EXEC->m_asRelease_Resource[psVLKN_CXT_EXEC->m_uiRelease_Resource_Consumer_Index].m_hVLKN_Memory = VK_NULL_HANDLE;

        psVLKN_CXT_EXEC->m_uiRelease_Resource_Consumer_Index = (psVLKN_CXT_EXEC->m_uiRelease_Resource_Consumer_Index + 1) % KTgKN_GPU_MAX_RELEASE_RESOURCE;
    }

    tgCM_UT_LF__SN__Signal( &psVLKN_CXT_EXEC->m_sRelease_Resource_Lock.m_sLock );
}


/* ---- tgKN_GPU_VLKN__Command_Context__Create_Default_Descriptor_Pool ----------------------------------------------------------------------------------------------------------- */
/* These pools are created according to user configuration as they will be used by the user.                                                                                       */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT tgKN_GPU_VLKN__Command_Context__Create_Default_Descriptor_Pool(
    VkDescriptorPool_P                          phPool,
    VkDevice_C                                  hVLKN_Device )
{
    VkDescriptorPoolSize_C                      asVLKN_Pool_Sizes[] = {
                                                    {
                                                        .type = VK_DESCRIPTOR_TYPE_SAMPLER,
                                                        .descriptorCount = 1,
                                                    },
                                                    {
                                                        .type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC,
                                                        .descriptorCount = 1,
                                                    },
                                                    {
                                                        .type = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE,
                                                        .descriptorCount = 1,
                                                    },
                                                    {
                                                        .type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC,
                                                        .descriptorCount = 1,
                                                    },
                                                    {
                                                        .type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
                                                        .descriptorCount = 1,
                                                    }
                                                };

    VkDescriptorPoolCI_C                        sVLKN_Pool_CI = {
                                                    .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
                                                    .pNext = nullptr,
                                                    .flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT  | VK_DESCRIPTOR_POOL_CREATE_UPDATE_AFTER_BIND_BIT,
                                                    .maxSets = 1024,
                                                    .poolSizeCount = TgARRAY_COUNT(asVLKN_Pool_Sizes),
                                                    .pPoolSizes = asVLKN_Pool_Sizes
                                                };

    VkResult                                    eResult;

    eResult = vkCreateDescriptorPool( hVLKN_Device, &sVLKN_Pool_CI, g_psKN_GPU_VLKN_Allocator, phPool );
    if (VK_SUCCESS != eResult)
    {
        TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create descriptor pool for Command Context" );
        *phPool = VK_NULL_HANDLE;
        return( KTgE_FAIL );
    };
    return (KTgS_OK);
}


/* ---- tgKN_GPU_VLKN_Acquire_Command_Pool_Buffer -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgKN_GPU_VLKN_Acquire_Command_Pool_Buffer(
    STg2_KN_GPU_VLKN_Node_Cmd_Pool_PP           psCommand_Pool,
    STg2_KN_GPU_VLKN_Node_Cmd_Buffer_PP         psCommand_Buffer,
    STg2_KN_GPU_VLKN_CXT_EXEC_PC                psVLKN_CXT_EXEC,
    STg2_KN_GPU_VLKN_CXT_CMD_PC                 psVLKN_CXT_CMD,
    ETgKN_GPU_EXT_COMMAND_C                     enCmd_Queue )
{
    VkDevice                                    hVLKN_Device;
    union
    {
        STg2_KN_GPU_VLKN_Node_Cmd_Pool_P                psNode_Cmd_Pool;
        STg2_UT_ST__ST_Node_P                           psNode_Stack;
    }                                           sCmd_Pool;
    union
    {
        STg2_KN_GPU_VLKN_Node_Cmd_Buffer_P              psNode_Cmd_Buffer;
        STg2_UT_ST__QU_Node_P                           psNode_Queue; /* Cmd Buffer node from the Queue structure */
        STg2_UT_ST__ST_Node_P                           psNode_Stack; /* Cmd Buffer node from Execution Context */
    }                                           sCmd_Buffer;

    TgVERIFY(nullptr != psCommand_Pool && nullptr != psCommand_Buffer && nullptr != psVLKN_CXT_EXEC && nullptr != psVLKN_CXT_CMD);

    *psCommand_Pool = nullptr;
    *psCommand_Buffer = nullptr;

    hVLKN_Device = g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Physical_Device[psVLKN_CXT_EXEC->m_idxCXT_HOST_Physical_Device].m_hVLKN_Device;

    sCmd_Pool.psNode_Stack = tgCM_UT_LF__ST__Pop( &psVLKN_CXT_CMD->m_sStack_Cmd_Pool_Free[enCmd_Queue].m_sStack ); /* Multi-threaded, Lock-Free */
    if (nullptr == sCmd_Pool.psNode_Stack)
    {
        return;
    }

    /* Check to see if we need to initialize a new command pool. */
    if (VK_NULL_HANDLE == sCmd_Pool.psNode_Cmd_Pool->m_hVLKN_Command_Pool)
    {
        TgRSIZE_C                           uiQueue_Family_Index = psVLKN_CXT_EXEC->m_auiVLKN_Queue_Family_Index[enCmd_Queue];

        if (TgSUCCEEDED(tgKN_GPU_VLKN_Create_Command_Pool(&sCmd_Pool.psNode_Cmd_Pool->m_hVLKN_Command_Pool, hVLKN_Device, uiQueue_Family_Index)))
        {
            TgMACRO_KN_GPU_VLKN_SET_NAME(hVLKN_Device, VK_OBJECT_TYPE_COMMAND_POOL, sCmd_Pool.psNode_Cmd_Pool->m_hVLKN_Command_Pool, u8"Execution Cmd Pool");
            tgCM_UT_ST__QU__Init(&sCmd_Pool.psNode_Cmd_Pool->m_sCmd_Buffer_Free_Queue);
            tgCM_UT_ST__QU__Init(&sCmd_Pool.psNode_Cmd_Pool->m_sCmd_Buffer_Used_Queue);
        }
        else
        {
            tgCM_UT_LF__ST__Push(&psVLKN_CXT_CMD->m_sStack_Cmd_Pool_Free[enCmd_Queue].m_sStack, sCmd_Pool.psNode_Stack);
            return;
        }
    }

    sCmd_Buffer.psNode_Queue = tgCM_UT_ST__QU__Dequeue( &sCmd_Pool.psNode_Cmd_Pool->m_sCmd_Buffer_Free_Queue ); /* Single-threaded */
    if (nullptr == sCmd_Buffer.psNode_Queue)
    {
        sCmd_Buffer.psNode_Stack = tgCM_UT_LF__ST__Pop(&psVLKN_CXT_CMD->m_sStack_Cmd_Buffer.m_sStack); /* Multi-threaded, Lock-Free */
        if (nullptr == sCmd_Buffer.psNode_Stack)
        {
            tgCM_UT_LF__ST__Push(&psVLKN_CXT_CMD->m_sStack_Cmd_Pool_Free[enCmd_Queue].m_sStack, sCmd_Pool.psNode_Stack);
            return;
        }
    }

    /* Check to see if we need to initialize a new command buffer. */
    if (VK_NULL_HANDLE == sCmd_Buffer.psNode_Cmd_Buffer->m_hVLKN_Command_Buffer)
    {
        if (TgSUCCEEDED(tgKN_GPU_VLKN_Create_Command_Buffer( &sCmd_Buffer.psNode_Cmd_Buffer->m_hVLKN_Command_Buffer, hVLKN_Device, sCmd_Pool.psNode_Cmd_Pool->m_hVLKN_Command_Pool )))
        {
            TgMACRO_KN_GPU_VLKN_SET_NAME(hVLKN_Device, VK_OBJECT_TYPE_COMMAND_BUFFER, sCmd_Buffer.psNode_Cmd_Buffer->m_hVLKN_Command_Buffer, u8"Execution Cmd Buffer");
        }
        else
        {
            sCmd_Buffer.psNode_Queue->m_pNext_Node = nullptr;
            tgCM_UT_ST__QU__Enqueue(&sCmd_Pool.psNode_Cmd_Pool->m_sCmd_Buffer_Free_Queue, sCmd_Buffer.psNode_Queue);
            tgCM_UT_LF__ST__Push(&psVLKN_CXT_CMD->m_sStack_Cmd_Pool_Free[enCmd_Queue].m_sStack, sCmd_Pool.psNode_Stack);
            return;
        }
    }

    *psCommand_Pool = sCmd_Pool.psNode_Cmd_Pool;
    *psCommand_Buffer = sCmd_Buffer.psNode_Cmd_Buffer;
}
