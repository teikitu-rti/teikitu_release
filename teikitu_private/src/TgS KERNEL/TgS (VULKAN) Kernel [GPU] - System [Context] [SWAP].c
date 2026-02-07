/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (VULKAN) Kernel [GPU] - System [Context] [SWAP].c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.22 | »GUID« 7ECEAB43-40E4-4161-8F94-87AF31F5BA9A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    Models:     Claude 3.7, Claude 4.0
    ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "TgS KERNEL/TgS (VULKAN) Kernel [GPU] - Debug.inl"


/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Extertnal Function                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgEXTN TgRESULT
tgKN_OS_GPU_API_Create_Surface(
    TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP );



 
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgINLINE TgVOID
tgKN_GPU_EXT_CXT_SWAP_Free_For_Resize(
    STg2_KN_GPU_VLKN_CXT_SWAP_PC ARG0, VkDevice ARG1, VkSwapchainKHR ARG2 );

TgEXTN TgRESULT
tgKN_GPU_EXT_CXT_SWAP_Set_HDR_Metadata(
    TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public GPU Functions - Context Extension                                                                                                                                       */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_GPU_EXT__SwapChain__Acquire_Present_Buffer -------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_EXT__SwapChain__Acquire_Present_Buffer(
    TgKN_GPU_CXT_SWAP_ID_C                      tiCXT_SWAP,
    TgKN_GPU_CXT_WORK_ID_C                      tiCXT_WORK )
{
    STg2_KN_GPU_VLKN_CXT_SWAP_PC                psVLKN_CXT_SWAP = g_asKN_GPU_EXT_CXT_SWAP + tiCXT_SWAP.m_uiI;
    STg2_KN_GPU_CXT_SWAP_PC                     psCXT_SWAP = g_asKN_GPU_CXT_SWAP + tiCXT_SWAP.m_uiI;

    STg2_KN_GPU_VLKN_CXT_EXEC_P                 psVLKN_CXT_EXEC;
    STg2_KN_GPU_VLKN_CMD_Queue_P                psCMD_Queue;
    VkDevice                                    hVLKN_Device;
    STg2_KN_GPU_VLKN_Output_Sync_P              psOutput_Sync;
    TgUINT_E64                                  uiTimeline_Transition_To_Render_Counter;
    VkResult                                    eResult;

    TgPARAM_CHECK_KN_EXEC_SWAP(tiCXT_SWAP);
    TgPARAM_CHECK_KN_EXEC_WORK(tiCXT_WORK);

    tgPM_MT_SM_Wait_Block( &psVLKN_CXT_SWAP->m_sSwap_And_View_Lock );
    psVLKN_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + psCXT_SWAP->m_tiCXT_EXEC.m_uiI;
    hVLKN_Device = psVLKN_CXT_EXEC->m_hVLKN_Device;
    psCMD_Queue = psVLKN_CXT_EXEC->m_apsCmd_Queue[ETgKN_GPU_EXT_COMMAND_GRAPHICS];
    psOutput_Sync = &psVLKN_CXT_SWAP->m_sOutput_Sync[psVLKN_CXT_SWAP->m_uiCurrent_Image_Index];

    /* 1. Wait for previous frame's transition-to-render command to complete (timeline semaphore validation) */
    uiTimeline_Transition_To_Render_Counter = psOutput_Sync->m_uiTimeline_Transition_To_Render_Counter;
    if (uiTimeline_Transition_To_Render_Counter > 0)
    {
        if (TgFAILED(tgKN_GPU_VLKN_Wait_Semaphore_Timeline( hVLKN_Device, psCMD_Queue->m_hVLKN_Timeline, uiTimeline_Transition_To_Render_Counter )))
        {
            TgERROR_MSGF(0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to wait for semaphore");
            goto tgKN_GPU_EXT__SwapChain__Acquire_Present_Buffer_FAILED;
        }
    }

    /* 2. Acquire the next image from the swapchain, signal the semaphore when the image is available and record the image index. */
    eResult = vkAcquireNextImageKHR(
        hVLKN_Device,
        psVLKN_CXT_SWAP->m_hVLKN_Swapchain,
        UINT64_MAX,
        psOutput_Sync->m_hVLKN_Semaphore_Binary_Image_Available, /* Signal Semaphore when image is available */
        VK_NULL_HANDLE,
        &psVLKN_CXT_SWAP->m_uiCurrent_Image_Index
    );

    if (VK_ERROR_OUT_OF_DATE_KHR == eResult)
    {
        TgERROR_MSGF(0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Swapchain out of date, needs recreation");
        tgPM_MT_SM_Signal(&psVLKN_CXT_SWAP->m_sSwap_And_View_Lock, 1);
        tgKN_GPU_EXT__SwapChain__Init( tiCXT_SWAP, false, true );
        TgDEBUG_BREAK_AND_RETURN(KTgE_FAIL);
    }
    else if (VK_SUBOPTIMAL_KHR == eResult)
    {
        TgERROR_MSGF(0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to acquire swapchain image");
        goto tgKN_GPU_EXT__SwapChain__Acquire_Present_Buffer_FAILED;
    }
    else if (VK_SUCCESS != eResult)
    {
        /* If you are here, and it says NOT_READY - there is a chance you missed a present. */
        TgERROR_MSGF(0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to acquire swapchain image: ", eResult);
        goto tgKN_GPU_EXT__SwapChain__Acquire_Present_Buffer_FAILED;
    }
    else
    {
        TgUINT_E64                                  uiQueue_Timeline_Value;

        VkSemaphoreSubmitInfo_C                     sVLKN_Wait_Semaphore_Info = {
                                                        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
                                                        .pNext = nullptr,
                                                        .semaphore = psOutput_Sync->m_hVLKN_Semaphore_Binary_Image_Available,
                                                        .value = 0,
                                                        .stageMask = VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT,
                                                        .deviceIndex = 0,
                                                    };

        VkSemaphoreSubmitInfo                       sVLKN_Signal_Semaphore_Info = {
                                                        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
                                                        .pNext = nullptr,
                                                        .semaphore = psCMD_Queue->m_hVLKN_Timeline,
                                                        .value = 0, /* Will be set before submit */
                                                        .stageMask = VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT,
                                                        .deviceIndex = 0,
                                                    };

        VkCommandBufferSubmitInfo                   sVLKN_Command_Buffer_Info = {
                                                        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_SUBMIT_INFO,
                                                        .pNext = nullptr,
                                                        .commandBuffer = VK_NULL_HANDLE, /* Will be set later */
                                                        .deviceMask = 0,
                                                    };

        VkSubmitInfo2_C                             sVLKN_Transition_To_Render_Submit_Info = {
                                                        .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO_2,
                                                        .pNext = nullptr,
                                                        .flags = 0,
                                                        .waitSemaphoreInfoCount = 1,
                                                        .pWaitSemaphoreInfos = &sVLKN_Wait_Semaphore_Info,
                                                        .commandBufferInfoCount = 1,
                                                        .pCommandBufferInfos = &sVLKN_Command_Buffer_Info,
                                                        .signalSemaphoreInfoCount = 1,
                                                        .pSignalSemaphoreInfos = &sVLKN_Signal_Semaphore_Info,
                                                    };

        VkImageMemoryBarrier2_C                     sVLKN_Current_Frame_Barrier = {
                                                        .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2,
                                                        .pNext = nullptr,
                                                        .srcStageMask = VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT,
                                                        .srcAccessMask = 0, /* No previous access after present */
                                                        .dstStageMask = VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT,
                                                        .dstAccessMask = VK_ACCESS_2_COLOR_ATTACHMENT_WRITE_BIT, /* Ready for color attachment writes */
                                                        .oldLayout = VK_IMAGE_LAYOUT_UNDEFINED, /* Layout from previous present (or undefined on first frame) */
                                                        .newLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL, /* Ready for rendering */
                                                        .srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
                                                        .dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
                                                        .image = VK_NULL_HANDLE, /* Will be set later after acquire */
                                                        .subresourceRange = {
                                                            .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
                                                            .baseMipLevel = 0,
                                                            .levelCount = 1,
                                                            .baseArrayLayer = 0,
                                                            .layerCount = 1
                                                        }
                                                    };

        VkImageMemoryBarrier2_C                     sVLKN_Depth_Stencil_Barrier = {
                                                        .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2,
                                                        .pNext = nullptr,
                                                        .srcStageMask = VK_PIPELINE_STAGE_2_EARLY_FRAGMENT_TESTS_BIT,
                                                        .srcAccessMask = 0,
                                                        .dstStageMask = VK_PIPELINE_STAGE_2_EARLY_FRAGMENT_TESTS_BIT,
                                                        .dstAccessMask = VK_ACCESS_2_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT,
                                                        .oldLayout = VK_IMAGE_LAYOUT_UNDEFINED,
                                                        .newLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
                                                        .srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
                                                        .dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
                                                        .image = VK_NULL_HANDLE, /* Will be set later if depth stencil exists */
                                                        .subresourceRange = {
                                                            .aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT, /* Add stencil later if used. */
                                                            .baseMipLevel = 0,
                                                            .levelCount = 1,
                                                            .baseArrayLayer = 0,
                                                            .layerCount = 1
                                                        }
                                                    };

        STg2_KN_GPU_VLKN_Render_Target_PC           psRender_Target = psVLKN_CXT_SWAP->m_asBack_Buffer__Render_Target + psVLKN_CXT_SWAP->m_uiCurrent_Image_Index;

        UTg2_KN_GPU_CMD_MUTABLE                     uCMD;
        TgUINT_E32                                  uiBarrier_Count;
        VkImageMemoryBarrier2                       asVLKN_Barriers[2];
        VkDependencyInfo                            sVLKN_Dependency_Info;

        /* 3. Update the display output information from the operating system monitor information. */
        tgKN_OS_GPU_CXT_SWAP_Update_Output( tiCXT_SWAP, psCXT_SWAP->m_uiOS_ID, false );

        /* 4. Submit transition-to-render command buffer */
        uCMD.ps = tgKN_GPU_EXT__WORK__Acquire_Command(tiCXT_WORK, ETgKN_GPU_EXT_COMMAND_GRAPHICS, u8"CMD BUF: SWAP Acquire Present Buffer");
        if (nullptr == uCMD.ps)
        {
            TgERROR_MSGF(0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to acquire command buffer");
            goto tgKN_GPU_EXT__SwapChain__Acquire_Present_Buffer_FAILED;
        }
        TgMACRO_KN_GPU_VLKN_SET_NAME(hVLKN_Device, VK_OBJECT_TYPE_COMMAND_BUFFER, uCMD.psVLKN->m_hVLKN_Command_Buffer, u8"Swap Chain: Command Buffer: Transition To Render");

        sVLKN_Command_Buffer_Info.commandBuffer = uCMD.psVLKN->m_hVLKN_Command_Buffer;

        /* Execute the transition to prepare current frame for rendering */
        asVLKN_Barriers[0] = sVLKN_Current_Frame_Barrier;
        asVLKN_Barriers[0].image = psRender_Target->m_ahVLKN_Colour_Image[0];
        uiBarrier_Count = 1;

        /* Transition depth-stencil image if it exists */
        if (VK_NULL_HANDLE != psRender_Target->m_hVLKN_Depth_Stencil_Image)
        {
            asVLKN_Barriers[1] = sVLKN_Depth_Stencil_Barrier;
            asVLKN_Barriers[1].image = psRender_Target->m_hVLKN_Depth_Stencil_Image;
            uiBarrier_Count = 2;

            if (psRender_Target->m_bStencil_Valid)
            {
                asVLKN_Barriers[1].subresourceRange.aspectMask |= VK_IMAGE_ASPECT_STENCIL_BIT;
            }
        }

        tgMM_Set_U08_0x00( &sVLKN_Dependency_Info, sizeof( sVLKN_Dependency_Info ) );
        sVLKN_Dependency_Info.sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO;
        sVLKN_Dependency_Info.imageMemoryBarrierCount = uiBarrier_Count;
        sVLKN_Dependency_Info.pImageMemoryBarriers = asVLKN_Barriers;

        vkCmdPipelineBarrier2(uCMD.psVLKN->m_hVLKN_Command_Buffer, &sVLKN_Dependency_Info);

        /* End recording the command buffer. */
        vkEndCommandBuffer(uCMD.psVLKN->m_hVLKN_Command_Buffer);

        /* Set the timeline semaphore value to signal when this command completes.
           This creates the synchronization chain:
           1. vkAcquireNextImageKHR signals m_hVLKN_Semaphore_Binary_Image_Available
           2. This submit waits on that binary semaphore at COLOR_ATTACHMENT_OUTPUT_BIT
           3. This submit signals the timeline semaphore with the terminator value
           4. Future operations can wait on this timeline value for completion */

        /* Submit the command buffer to the graphics queue. */
        tgCM_UT_LF__SN__Lock_Spin( &psCMD_Queue->m_sLock.m_sLock );
        uiQueue_Timeline_Value = TgSTD_ATOMIC(fetch_add)( &psCMD_Queue->m_xuiTimeline_Signal_Value, 1 );
        sVLKN_Signal_Semaphore_Info.value = uiQueue_Timeline_Value;
        eResult = vkQueueSubmit2( psCMD_Queue->m_hVLKN_Queue, 1, &sVLKN_Transition_To_Render_Submit_Info, VK_NULL_HANDLE );
        tgCM_UT_LF__SN__Signal( &psCMD_Queue->m_sLock.m_sLock );

        uCMD.psVLKN->m_hVLKN_Command_Buffer = VK_NULL_HANDLE;

        tgKN_GPU_EXT__CMD__Command_Buffer_Close_And_Submit_With_Wait(nullptr, uCMD.ps, ETgKN_GPU_EXT_COMMAND_NONE, 0);

        if (VK_SUCCESS != eResult)
        {
            TgERROR_MSGF(0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to submit command buffer");
            goto tgKN_GPU_EXT__SwapChain__Acquire_Present_Buffer_FAILED;
        }

        psOutput_Sync->m_uiTimeline_Transition_To_Render_Counter = uiQueue_Timeline_Value;

        tgPM_MT_SM_Signal( &psVLKN_CXT_SWAP->m_sSwap_And_View_Lock, 1 );

        return KTgS_OK;
    };
tgKN_GPU_EXT__SwapChain__Acquire_Present_Buffer_FAILED:
    tgPM_MT_SM_Signal( &psVLKN_CXT_SWAP->m_sSwap_And_View_Lock, 1 );
    TgDEBUG_BREAK_AND_RETURN(KTgE_FAIL);
}


/* ---- tgKN_GPU_EXT__SwapChain__Query_Render_Target_DESC ------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_EXT__SwapChain__Query_Render_Target_DESC(
    STg2_KN_GPU_Render_Target_DESC_PC           psRender_Target_DESC,
    TgKN_GPU_CXT_SWAP_ID_C                      tiCXT_SWAP )
{
    STg2_KN_GPU_CXT_SWAP_PC                     psCXT_SWAP = g_asKN_GPU_CXT_SWAP + tiCXT_SWAP.m_uiI;

    TgPARAM_CHECK_KN_EXEC_SWAP(tiCXT_SWAP);
    TgPARAM_CHECK(psRender_Target_DESC);

    tgMM_Set_U08_0x00( psRender_Target_DESC, sizeof( STg2_KN_GPU_Render_Target_DESC ) );

    psRender_Target_DESC->m_aenColour_Format[0] = psCXT_SWAP->m_enFormat_RT;
    psRender_Target_DESC->m_nuiColour_Target = 1;
    psRender_Target_DESC->m_enDepth_Stencil_Format = psCXT_SWAP->m_enFormat_DS;
    psRender_Target_DESC->m_uiWidth = psCXT_SWAP->m_sMode.m_sBuffer.m_uiWidth;
    psRender_Target_DESC->m_uiHeight = psCXT_SWAP->m_sMode.m_sBuffer.m_uiHeight;

    return (KTgS_OK);
}


/* ---- tgKN_GPU_EXT__SwapChain__Query_Output_DESC ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_EXT__SwapChain__Query_Output_DESC(
    STg2_KN_GPU_Output_DESC_PC                  psOutput_DESC,
    TgKN_GPU_CXT_SWAP_ID_C                      tiCXT_SWAP )
{
    STg2_KN_GPU_CXT_SWAP_PC                     psCXT_SWAP = g_asKN_GPU_CXT_SWAP + tiCXT_SWAP.m_uiI;

    TgPARAM_CHECK_KN_EXEC_SWAP(tiCXT_SWAP);
    TgPARAM_CHECK(psOutput_DESC);

    *psOutput_DESC = psCXT_SWAP->m_sOutput_DESC;
    psOutput_DESC->m_iColour_Space = psCXT_SWAP->m_enColour_Space;

    return (KTgS_OK);
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public GPU Functions - WORK                                                                                                                                                   */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_GPU_EXT__WORK__Present ---------------------------------------------------------------------------------------------------------------------------------------------- */
/*  m_hVLKN_Semaphore_Binary_Transition_To_Present_Complete - used on the transition submit and present to hand off the back buffer.
    m_hVLKN_Timeline_Transition_To_Present - Used to track of the frame number to mark if its safe to reset frame resources                                                        */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_EXT__WORK__Present(
    TgKN_GPU_CXT_WORK_ID_C                      tiCXT_WORK,
    TgKN_GPU_CXT_SWAP_ID_C                      tiCXT_SWAP,
    ETgKN_GPU_EXT_COMMAND                       enWait_Queue,
    TgUINT_E64                                  uiTimleine_Wait_Value )
{
    UTg2_KN_GPU_CMD_MUTABLE                     uCMD;

    TgPARAM_CHECK_INDEX(tiCXT_SWAP.m_uiI, g_asKN_GPU_CXT_SWAP);
    TgPARAM_CHECK(tgKN_GPU_CXT_SWAP_ID_Is_Equal( &(g_asKN_GPU_CXT_SWAP[tiCXT_SWAP.m_uiI].m_tiCXT_SWAP_S), tiCXT_SWAP ));
    TgPARAM_CHECK_INDEX(g_asKN_GPU_CXT_SWAP[tiCXT_SWAP.m_uiI].m_tiCXT_EXEC.m_uiI, g_asKN_GPU_CXT_EXEC);
    TgPARAM_CHECK(tgKN_GPU_CXT_EXEC_ID_Is_Equal( &(g_asKN_GPU_CXT_EXEC[g_asKN_GPU_CXT_SWAP[tiCXT_SWAP.m_uiI].m_tiCXT_EXEC.m_uiI].m_tiCXT_EXEC_S),
                                                 g_asKN_GPU_CXT_SWAP[tiCXT_SWAP.m_uiI].m_tiCXT_EXEC ));

    /* 1. Optionally print out debug stats for the frame. */
#if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)
    uCMD.ps = tgKN_GPU_EXT__WORK__Acquire_Command( tiCXT_WORK, ETgKN_GPU_EXT_COMMAND_GRAPHICS, u8"CMD BUF: SWAP Final Debug Text" );
    if (uCMD.ps && TgSUCCEEDED(tgKN_GPU_EXT__CMD__Begin_Rendering( uCMD.ps, KTgKN_GPU_RENDER_TARGET_ID__INVALID, tiCXT_SWAP, nullptr, nullptr, nullptr )))
    {
        tgKN_GPU_EXT__CMD__Set_Viewport_and_Scissor( uCMD.ps, tiCXT_SWAP );
        tgKN_GPU__SwapChain__Present_Print_Debug_Stats( uCMD.ps, tiCXT_SWAP );
        tgKN_GPU_EXT__CMD__End_Rendering( uCMD.ps );
        tgKN_GPU_EXT__CMD__Command_Buffer_Close_And_Submit_With_Wait( &uiTimleine_Wait_Value, uCMD.ps, enWait_Queue, uiTimleine_Wait_Value );
        enWait_Queue = ETgKN_GPU_EXT_COMMAND_GRAPHICS;
    }
    /*# defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
#else
    (void)tiCXT_WORK; // -Wunused-parameter
    /*# defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
#endif

    {
        STg2_KN_GPU_VLKN_CXT_SWAP_PC                psVLKN_CXT_SWAP = g_asKN_GPU_EXT_CXT_SWAP + tiCXT_SWAP.m_uiI;
        STg2_KN_GPU_CXT_SWAP_PC                     psCXT_SWAP = g_asKN_GPU_CXT_SWAP + tiCXT_SWAP.m_uiI;
        STg2_KN_GPU_VLKN_CXT_EXEC_PC                psVLKN_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + psCXT_SWAP->m_tiCXT_EXEC.m_uiI;
        STg2_KN_GPU_VLKN_Output_Sync_PC             psOutput_Sync = &psVLKN_CXT_SWAP->m_sOutput_Sync[psVLKN_CXT_SWAP->m_uiCurrent_Image_Index];

        STg2_KN_GPU_VLKN_CMD_Queue_PC               psCMD_Queue_Wait = ETgKN_GPU_EXT_COMMAND_NONE != enWait_Queue ? psVLKN_CXT_EXEC->m_apsCmd_Queue[enWait_Queue] : nullptr;
        STg2_KN_GPU_VLKN_CMD_Queue_PC               psCMD_Queue = psVLKN_CXT_EXEC->m_apsCmd_Queue[ETgKN_GPU_EXT_COMMAND_GRAPHICS];

        VkSemaphoreSubmitInfo                       sVLKN_Wait_Render_Complete = {
                                                        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
                                                        .pNext = nullptr,
                                                        .semaphore = ETgKN_GPU_EXT_COMMAND_NONE != enWait_Queue ? psCMD_Queue_Wait->m_hVLKN_Timeline : VK_NULL_HANDLE,
                                                        .value = uiTimleine_Wait_Value,
                                                        .stageMask = VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT,
                                                        .deviceIndex = 0,
                                                    };

        VkSemaphoreSubmitInfo                       asVLKN_Signal_Semaphores[2] = {
                                                        {
                                                            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
                                                            .pNext = nullptr,
                                                            .semaphore = psOutput_Sync->m_hVLKN_Semaphore_Binary_Transition_To_Present_Complete,
                                                            .value = 0,
                                                            .stageMask = VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT,
                                                            .deviceIndex = 0,
                                                        },
                                                        {
                                                            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
                                                            .pNext = nullptr,
                                                            .semaphore = psCMD_Queue->m_hVLKN_Timeline,
                                                            .value = 0, /* Will be set before submit */
                                                            .stageMask = VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT,
                                                            .deviceIndex = 0,
                                                        }
                                                    };

        VkCommandBufferSubmitInfo                   sVLKN_Command_Buffer_Info = {
                                                        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_SUBMIT_INFO,
                                                        .pNext = nullptr,
                                                        .commandBuffer = VK_NULL_HANDLE, /* Will be set later */
                                                        .deviceMask = 0,
                                                    };

        VkSubmitInfo2                               sVLKN_Transition_To_Present_Submit_Info = {
                                                        .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO_2,
                                                        .pNext = nullptr,
                                                        .flags = 0,
                                                        .waitSemaphoreInfoCount = 1,
                                                        .pWaitSemaphoreInfos = ETgKN_GPU_EXT_COMMAND_NONE != enWait_Queue ? &sVLKN_Wait_Render_Complete : nullptr,
                                                        .commandBufferInfoCount = 1,
                                                        .pCommandBufferInfos = &sVLKN_Command_Buffer_Info,
                                                        .signalSemaphoreInfoCount = 2,
                                                        .pSignalSemaphoreInfos = asVLKN_Signal_Semaphores,
                                                    };

        VkImageMemoryBarrier2_C                     sVLKN_Present_Frame_Barrier = {
                                                        .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2,
                                                        .pNext = nullptr,
                                                        .srcStageMask = VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT,
                                                        .srcAccessMask = VK_ACCESS_2_COLOR_ATTACHMENT_WRITE_BIT,
                                                        .dstStageMask = VK_PIPELINE_STAGE_2_NONE,
                                                        .dstAccessMask = VK_ACCESS_2_NONE,
                                                        .oldLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
                                                        .newLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
                                                        .srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
                                                        .dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
                                                        .image = psVLKN_CXT_SWAP->m_asBack_Buffer__Render_Target[psVLKN_CXT_SWAP->m_uiCurrent_Image_Index].m_ahVLKN_Colour_Image[0],
                                                        .subresourceRange = {
                                                            .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
                                                            .baseMipLevel = 0,
                                                            .levelCount = 1,
                                                            .baseArrayLayer = 0,
                                                            .layerCount = 1
                                                        }
                                                    };

        VkDependencyInfo                            sVLKN_Dependency_Info = {
                                                        .sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO,
                                                        .pNext = nullptr,
                                                        .dependencyFlags = 0,
                                                        .memoryBarrierCount = 0,
                                                        .pMemoryBarriers = nullptr,
                                                        .bufferMemoryBarrierCount = 0,
                                                        .pBufferMemoryBarriers = nullptr,
                                                        .imageMemoryBarrierCount = 1,
                                                        .pImageMemoryBarriers = &sVLKN_Present_Frame_Barrier,
                                                    };

        VkPresentInfoKHR_C                          sVLKN_Present_Info = {
                                                        .sType              = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
                                                        .pNext              = nullptr,
                                                        .waitSemaphoreCount = 1,
                                                        .pWaitSemaphores    = &psOutput_Sync->m_hVLKN_Semaphore_Binary_Transition_To_Present_Complete,
                                                        .swapchainCount     = 1,
                                                        .pSwapchains        = &psVLKN_CXT_SWAP->m_hVLKN_Swapchain,
                                                        .pImageIndices      = &psVLKN_CXT_SWAP->m_uiCurrent_Image_Index,
                                                        .pResults           = nullptr,
                                                    };

        STg2_KN_GPU_VLKN_Physical_Device_P          psGPU_EXT_Physical_Device;
        VkDevice                                    hVLKN_Device;
        TgUINT_E64                                  uiTimeline_Transition_To_Present_Counter;
        VkResult                                    eResult;

        tgPM_MT_SM_Wait_Block( &psVLKN_CXT_SWAP->m_sSwap_And_View_Lock );

        psGPU_EXT_Physical_Device = g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Physical_Device + psVLKN_CXT_EXEC->m_idxCXT_HOST_Physical_Device;
        hVLKN_Device = psGPU_EXT_Physical_Device->m_hVLKN_Device;

        /* 2. Wait for previous frame's transition-to-present command to complete (timeline semaphore validation) */
        uiTimeline_Transition_To_Present_Counter = psOutput_Sync->m_uiTimeline_Transition_To_Present_Counter;
        if (uiTimeline_Transition_To_Present_Counter > 0)
        {
            if (TgFAILED(tgKN_GPU_VLKN_Wait_Semaphore_Timeline( hVLKN_Device, psCMD_Queue->m_hVLKN_Timeline, uiTimeline_Transition_To_Present_Counter )))
            {
                TgERROR_MSGF(0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to wait for semaphore");
                goto tgKN_GPU_EXT__WORK__Present_FAILED;
            }
        }

        /* 3. Reset transition-to-present command buffer */
        uCMD.ps = tgKN_GPU_EXT__WORK__Acquire_Command(tiCXT_WORK, ETgKN_GPU_EXT_COMMAND_GRAPHICS, u8"CMD BUF: Present Transition");
        if (nullptr == uCMD.ps)
        {
            TgERROR_MSGF(0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to acquire command buffer");
            goto tgKN_GPU_EXT__WORK__Present_FAILED;
        }
        TgMACRO_KN_GPU_VLKN_SET_NAME( hVLKN_Device, VK_OBJECT_TYPE_COMMAND_BUFFER, uCMD.psVLKN->m_hVLKN_Command_Buffer, u8"Swap Chain: Command Buffer: Transition To Present" );

        sVLKN_Command_Buffer_Info.commandBuffer = uCMD.psVLKN->m_hVLKN_Command_Buffer;

        /* Execute the transition to prepare current frame for present */
        vkCmdPipelineBarrier2( uCMD.psVLKN->m_hVLKN_Command_Buffer, &sVLKN_Dependency_Info );

        eResult = vkEndCommandBuffer( uCMD.psVLKN->m_hVLKN_Command_Buffer );
        if (VK_SUCCESS != eResult)
        {
            TgERROR_MSGF(0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to end command buffer");
        }
        else
        {
            /* 4. Submit transition-to-present command buffer */

            tgCM_UT_LF__SN__Lock_Spin( &psCMD_Queue->m_sLock.m_sLock );
            asVLKN_Signal_Semaphores[0].semaphore = psOutput_Sync->m_hVLKN_Semaphore_Binary_Transition_To_Present_Complete;
            asVLKN_Signal_Semaphores[0].value = 0;
            asVLKN_Signal_Semaphores[1].value = TgSTD_ATOMIC(fetch_add)( &psCMD_Queue->m_xuiTimeline_Signal_Value, 1 );
            eResult = vkQueueSubmit2( psCMD_Queue->m_hVLKN_Queue, 1, &sVLKN_Transition_To_Present_Submit_Info, VK_NULL_HANDLE );
            tgCM_UT_LF__SN__Signal( &psCMD_Queue->m_sLock.m_sLock );

            if (eResult != VK_SUCCESS)
            {
                TgERROR_MSGF(0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to submit command buffer: ", eResult);
            }

            psOutput_Sync->m_uiTimeline_Transition_To_Present_Counter = asVLKN_Signal_Semaphores[1].value;
        }

        uCMD.psVLKN->m_hVLKN_Command_Buffer = VK_NULL_HANDLE;
        tgKN_GPU_EXT__CMD__Command_Buffer_Close_And_Submit_With_Wait( nullptr, uCMD.ps, ETgKN_GPU_EXT_COMMAND_NONE, 0 );

        if (eResult != VK_SUCCESS)
        {
            goto tgKN_GPU_EXT__WORK__Present_FAILED;
        }

        /* 5. Present the current back buffer */
        tgCM_UT_LF__SN__Lock_Spin( &psVLKN_CXT_EXEC->m_apsCmd_Queue[ETgKN_GPU_EXT_COMMAND_PRESENT]->m_sLock.m_sLock );
        eResult = vkQueuePresentKHR( psVLKN_CXT_EXEC->m_apsCmd_Queue[ETgKN_GPU_EXT_COMMAND_PRESENT]->m_hVLKN_Queue, &sVLKN_Present_Info );
        tgCM_UT_LF__SN__Signal( &psVLKN_CXT_EXEC->m_apsCmd_Queue[ETgKN_GPU_EXT_COMMAND_PRESENT]->m_sLock.m_sLock );

        /* 6. Handle error states returned from the present call */
        if (eResult == VK_ERROR_OUT_OF_DATE_KHR || eResult == VK_SUBOPTIMAL_KHR)
        {
            TgWARNING_MSGF(0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Swapchain out of date, needs recreation: ", eResult);
            tgPM_MT_SM_Signal( &psVLKN_CXT_SWAP->m_sSwap_And_View_Lock, 1 );
            return (KTgE_FAIL);
        }
        else if (eResult == VK_SUBOPTIMAL_KHR)
        {
            TgERROR_MSGF(0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Swapchain not optimal: ", eResult);
            goto tgKN_GPU_EXT__WORK__Present_FAILED;
        }
        else if (eResult != VK_SUCCESS)
        {
            /* Handle other errors */
            goto tgKN_GPU_EXT__WORK__Present_FAILED;
        }

        /* 7. Advance to next frame */
        psVLKN_CXT_SWAP->m_uiCurrent_Image_Index = (psVLKN_CXT_SWAP->m_uiCurrent_Image_Index + 1) % KTgKN_GPU_MAX_BUFFER_IN_FLIP_CHAIN;

        /* 8. Track which queue family had work submitted this frame */
        TgSTD_ATOMIC(fetch_or)( &psVLKN_CXT_EXEC->m_sContext_Command[tiCXT_WORK.m_uiI].m_xuiUsed_Queue_Family_Mask,
                                (1ULL << psVLKN_CXT_EXEC->m_apsCmd_Queue[ETgKN_GPU_EXT_COMMAND_PRESENT]->m_uiQueue_Family_Index));

        tgPM_MT_SM_Signal( &psVLKN_CXT_SWAP->m_sSwap_And_View_Lock, 1 );

        return KTgS_OK;

    tgKN_GPU_EXT__WORK__Present_FAILED:
        tgPM_MT_SM_Signal( &psVLKN_CXT_SWAP->m_sSwap_And_View_Lock, 1 );
        TgDEBUG_BREAK_AND_RETURN(KTgE_FAIL);
    }
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public GPU Functions - Command                                                                                                                                                */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_GPU_EXT__CMD__Set_Viewport_and_Scissor ------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_EXT__CMD__Set_Viewport_and_Scissor(
    STg2_KN_GPU_CMD_PC                          psCMD,
    TgKN_GPU_CXT_SWAP_ID_C                      tiCXT_SWAP )
{
    UTg2_KN_GPU_CMD_C                           uCMD = { .ps = psCMD };
    STg2_KN_GPU_CXT_SWAP_PC                     psCXT_SWAP = g_asKN_GPU_CXT_SWAP + tiCXT_SWAP.m_uiI;
    VkViewport                                  vkViewport = {
                                                    .x        = (float)psCXT_SWAP->m_sViewport.m_iPosX,
                                                    .y        = (float)psCXT_SWAP->m_sViewport.m_iPosY,
                                                    .width    = (float)psCXT_SWAP->m_sViewport.m_iWidth,
                                                    .height   = (float)psCXT_SWAP->m_sViewport.m_iHeight,
                                                    .minDepth = psCXT_SWAP->m_sViewport.m_fMinZ,
                                                    .maxDepth = psCXT_SWAP->m_sViewport.m_fMaxZ,
                                                };
    VkRect2D                                    vkScissor = {
                                                    .offset = {
                                                        .x = psCXT_SWAP->m_sScissor_Rect.m_iLeft,
                                                        .y = psCXT_SWAP->m_sScissor_Rect.m_iTop,
                                                    },
                                                    .extent = {
                                                        .width  = (uint32_t)(psCXT_SWAP->m_sScissor_Rect.m_iRight - psCXT_SWAP->m_sScissor_Rect.m_iLeft),
                                                        .height = (uint32_t)(psCXT_SWAP->m_sScissor_Rect.m_iBottom - psCXT_SWAP->m_sScissor_Rect.m_iTop),
                                                    }
                                                };

    vkCmdSetViewport( uCMD.psVLKN->m_hVLKN_Command_Buffer, 0, 1, &vkViewport );
    vkCmdSetScissor( uCMD.psVLKN->m_hVLKN_Command_Buffer, 0, 1, &vkScissor );

    return (KTgS_OK);
}


/* ---- tgKN_GPU_EXT__CMD__Render_Target_To_Present_With_Colour_Correction ------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_EXT__CMD__Render_Target_To_Present_With_Colour_Correction(
    STg2_KN_GPU_CMD_P                           psCMD_Graphics,
    ETgKN_GPU_EXT_COMMAND_C                     enWait_Queue,
    TgUINT_E64                                  uiTimeline_Value,
    TgKN_GPU_CXT_WORK_ID_C                      tiCXT_WORK,
    TgKN_GPU_CXT_SWAP_ID_C                      tiCXT_SWAP,
    TgKN_GPU_RENDER_TARGET_ID_C                 tiRender_Target )
{
    UTg2_KN_GPU_CMD_C                           uCMD_Graphics = { .ps = psCMD_Graphics };
    TgRSIZE_C                                   uiEXEC = (uCMD_Graphics.psVLKN->m_sBase.m_tiCXT_WORK.m_uiI >> 16) & 0xFFFF;
    STg2_KN_GPU_VLKN_CXT_EXEC_PC                psVLKN_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + uiEXEC;

    STg2_KN_GPU_CMD_P                           psCMD_Compute;
    STg2_KN_GPU_Output_DESC                     sOutput_DESC;
    STg2_KN_GPU_VLKN_Render_Target_P            psRender_Target_Src;
    STg2_KN_GPU_VLKN_Render_Target_P            psRender_Target_Dest;

    /* Acquire the next available back buffer for a render target. */
    if (TgFAILED(tgKN_GPU_EXT__SwapChain__Acquire_Present_Buffer(tiCXT_SWAP, tiCXT_WORK)))
    {
        TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to acquire back buffer from swap chain." );
        goto tgUnit_Test__KN_GPU__Prepare_and_Present_Back_Buffer_FAIL0;
    }

    /* Query the output description for the swap chain, used to set the clear colour taking into account the back buffer colour space. (i.e. CPU colour correction) */
    if (TgFAILED(tgKN_GPU_EXT__SwapChain__Query_Output_DESC( &sOutput_DESC, tiCXT_SWAP )))
    {
        TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to query output description for swap chain." );
        goto tgUnit_Test__KN_GPU__Prepare_and_Present_Back_Buffer_FAIL0;
    }


    /* Validate that the render target is valid/current. */
    psRender_Target_Src = nullptr;
    if (TgFAILED(tgKN_GPU_VLKN__Render_Target__Get_Render_Target( &psRender_Target_Src, KTgKN_GPU_CXT_SWAP_ID__INVALID, tiRender_Target, psVLKN_CXT_EXEC->m_tiCXT_EXEC )))
    {
        TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to get render target (source)." );
        goto tgUnit_Test__KN_GPU__Prepare_and_Present_Back_Buffer_FAIL0;
    }
    if (VK_NULL_HANDLE == psRender_Target_Src->m_ahVLKN_Colour_Image[0])
    {
        TgERROR_MSGF(0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Source render target has invalid colour image");
        goto tgUnit_Test__KN_GPU__Prepare_and_Present_Back_Buffer_FAIL0;
    }

    /* Validate that the render target is valid/current. */
    psRender_Target_Dest = nullptr;
    if (TgFAILED(tgKN_GPU_VLKN__Render_Target__Get_Render_Target( &psRender_Target_Dest, tiCXT_SWAP, KTgKN_GPU_RENDER_TARGET_ID__INVALID, psVLKN_CXT_EXEC->m_tiCXT_EXEC )))
    {
        TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to get render target (destination)." );
        goto tgUnit_Test__KN_GPU__Prepare_and_Present_Back_Buffer_FAIL0;
    }
    if (VK_NULL_HANDLE == psRender_Target_Dest->m_ahVLKN_Colour_Image[0])
    {
        TgERROR_MSGF(0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Destination render target has invalid colour image");
        goto tgUnit_Test__KN_GPU__Prepare_and_Present_Back_Buffer_FAIL0;
    }


    /* Get an opaque pointer (handle) used for issuing GPU commands. Note: this has the side effect of potenially generating required pipelines. */
    psCMD_Compute = tgKN_GPU_EXT__WORK__Acquire_Command(tiCXT_WORK, ETgKN_GPU_EXT_COMMAND_COMPUTE, u8"Render_Target_To_Present_With_Colour_Correction (Compute)");
    if (nullptr == psCMD_Compute)
    {
        goto tgUnit_Test__KN_GPU__Prepare_and_Present_Back_Buffer_FAIL0;
    }


    /* Transition the image buffers access and queue ownership from graphics to compute */
    if (TgFAILED(tgKN_GPU_VLKN__CMD__Image_Barrier__Graphics_Write_To_Compute_Read( psCMD_Graphics, psCMD_Compute, psRender_Target_Src )))
    {
        goto tgUnit_Test__KN_GPU__Prepare_and_Present_Back_Buffer_FAIL1;
    }
    if (TgFAILED(tgKN_GPU_VLKN__CMD__Image_Barrier__Graphics_Swap_To_Compute_Write( psCMD_Graphics, psCMD_Compute, psRender_Target_Dest )))
    {
        goto tgUnit_Test__KN_GPU__Prepare_and_Present_Back_Buffer_FAIL1;
    }

    /* Submit the graphics command buffer which will provide the timeline semaphore marking "render complete" to use to signal the compute workload. */
    tgKN_GPU_EXT__CMD__Command_Buffer_Close_And_Submit_With_Wait(&uiTimeline_Value, psCMD_Graphics, enWait_Queue, uiTimeline_Value);
    psCMD_Graphics = nullptr;


    tgKN_GPU_EXT__CMD__Update_Render_DESC_Descriptor_Set(psCMD_Compute, nullptr, nullptr, &sOutput_DESC);
    tgKN_GPU_VLKN__CMD__Apply_Colour_Correction_Compute(psCMD_Compute, psRender_Target_Src, psRender_Target_Dest );


    /* Get an opaque pointer (handle) used for issuing GPU commands. Note: this has the side effect of potenially generating required pipelines. */
    psCMD_Graphics = tgKN_GPU_EXT__WORK__Acquire_Command(tiCXT_WORK, ETgKN_GPU_EXT_COMMAND_GRAPHICS, u8"Render_Target_To_Present_With_Colour_Correction (Graphics)");
    if (nullptr == psCMD_Graphics)
    {
        goto tgUnit_Test__KN_GPU__Prepare_and_Present_Back_Buffer_FAIL1;
    }

    /* Transition the image buffers access and queue ownership from graphics to compute */
    if (TgFAILED(tgKN_GPU_VLKN__CMD__Image_Barrier__Compute_Read_To_Graphics_Write( psCMD_Compute, psCMD_Graphics, psRender_Target_Src )))
    {
        goto tgUnit_Test__KN_GPU__Prepare_and_Present_Back_Buffer_FAIL2;
    }
    if (TgFAILED(tgKN_GPU_VLKN__CMD__Image_Barrier__Compute_Write_To_Graphics_Present( psCMD_Compute, psCMD_Graphics, psRender_Target_Dest )))
    {
        goto tgUnit_Test__KN_GPU__Prepare_and_Present_Back_Buffer_FAIL2;
    }

    /* Submit the compute workloads - wait on the completion of the graphics command buffer */
    tgKN_GPU_EXT__CMD__Command_Buffer_Close_And_Submit_With_Wait(&uiTimeline_Value, psCMD_Compute, ETgKN_GPU_EXT_COMMAND_GRAPHICS, uiTimeline_Value);
    psCMD_Compute = nullptr;

    /* Submit the graphics command buffer which will provide the timeline semaphore marking "render complete" to use to signal the compute workload. */
    tgKN_GPU_EXT__CMD__Command_Buffer_Close_And_Submit_With_Wait(&uiTimeline_Value, psCMD_Graphics, ETgKN_GPU_EXT_COMMAND_COMPUTE, uiTimeline_Value);
    psCMD_Graphics = nullptr;

    /* Tell the present routines to wait on the completion of the compute workload */
    tgKN_GPU_EXT__WORK__Present(tiCXT_WORK, tiCXT_SWAP, ETgKN_GPU_EXT_COMMAND_GRAPHICS, uiTimeline_Value);
    return (KTgS_OK);

tgUnit_Test__KN_GPU__Prepare_and_Present_Back_Buffer_FAIL2:
    tgKN_GPU_EXT__CMD__Command_Buffer_Close_And_Submit_With_Wait(nullptr, psCMD_Graphics, ETgKN_GPU_EXT_COMMAND_NONE, 0);
tgUnit_Test__KN_GPU__Prepare_and_Present_Back_Buffer_FAIL1:
    tgKN_GPU_EXT__CMD__Command_Buffer_Close_And_Submit_With_Wait(nullptr, psCMD_Compute, ETgKN_GPU_EXT_COMMAND_NONE, 0);
tgUnit_Test__KN_GPU__Prepare_and_Present_Back_Buffer_FAIL0:
    /* #TODO: Need to process a present in the fail case since we acquired the back buffer */
    return (KTgE_FAIL);
}


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_GPU_EXT__SwapChain__Init -------------------------------------------------------------------------------------------------------------------------------------------- */
/* Function needs to be reinteranted to handle the case where the swap chain is already created.                                                                                   */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_EXT__SwapChain__Init(
    TgKN_GPU_CXT_SWAP_ID_C                      tiCXT_SWAP,
    TgBOOL_C                                    bResize,
    TgBOOL_C                                    bForceInitSwapChain )
{
    STg2_KN_GPU_VLKN_CXT_SWAP_PC                psVLKN_CXT_SWAP = g_asKN_GPU_EXT_CXT_SWAP + tiCXT_SWAP.m_uiI;
    STg2_KN_GPU_CXT_SWAP_PC                     psCXT_SWAP = g_asKN_GPU_CXT_SWAP + tiCXT_SWAP.m_uiI;

    STg2_KN_GPU_VLKN_CXT_EXEC_P                 psVLKN_CXT_EXEC;
    STg2_KN_GPU_VLKN_Physical_Device_CP         psGPU_EXT_Physical_Device;

    VkDevice                                    hVLKN_Device;
    VkPhysicalDevice                            hVLKN_Physical_Device;
    VkSurfaceFormatKHR                          sVLKN_Selected_Surface_Format;
    VkPresentModeKHR                            enVLKN_Selected_Present_Mode;
    VkExtent2D                                  sVLKN_Selected_Extent;
    VkColorSpaceKHR                             enVLKN_Colour_Space;
    VkResult                                    eResult;

    TgUINT_F32                                  uiIndex;
    TgUINT_E32                                  uiVkUint32;
    TgRSIZE                                     uiSelected_Image_Count;
    TgBOOL                                      bCreate_Swapchain;

    TgPARAM_CHECK_INDEX(tiCXT_SWAP.m_uiI, g_asKN_GPU_EXT_CXT_SWAP);
    TgPARAM_CHECK(tgKN_GPU_CXT_SWAP_ID_Is_Equal( &(g_asKN_GPU_CXT_SWAP[tiCXT_SWAP.m_uiI].m_tiCXT_SWAP_S), tiCXT_SWAP ));

    TgERROR(VK_NULL_HANDLE != g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Physical_Device[psCXT_SWAP->m_idxCXT_HOST_Physical_Device].m_hVLKN_Physical_Device);
    TgERROR(VK_NULL_HANDLE != g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Physical_Device[psCXT_SWAP->m_idxCXT_HOST_Physical_Device].m_hVLKN_Device);

    TgPARAM_CHECK_INDEX(psCXT_SWAP->m_tiCXT_EXEC.m_uiI, g_asKN_GPU_EXT_CXT_EXEC);

    if (!bResize && !bForceInitSwapChain)
    {
        tgMM_Set_U08_0x00( psVLKN_CXT_SWAP, sizeof( STg2_KN_GPU_VLKN_CXT_SWAP ) );
    }

    psVLKN_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + psCXT_SWAP->m_tiCXT_EXEC.m_uiI;
    psGPU_EXT_Physical_Device = g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Physical_Device + psVLKN_CXT_EXEC->m_idxCXT_HOST_Physical_Device;
    hVLKN_Device = psGPU_EXT_Physical_Device->m_hVLKN_Device;
    hVLKN_Physical_Device = psGPU_EXT_Physical_Device->m_hVLKN_Physical_Device;

    /* Check for first time initialization of the swap chain. This function is re-entrant due to the need to resize the swap chain.*/
    if (VK_NULL_HANDLE == psVLKN_CXT_SWAP->m_hVLKN_Surface)
    {
        TgVERIFY(false == psCXT_SWAP->m_bInit);
        if (TgFAILED(tgKN_OS_GPU_API_Create_Surface(tiCXT_SWAP)))
        {
            TgERROR_MSGF(0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create Vulkan surface");
            TgDEBUG_BREAK_AND_RETURN(KTgE_FAIL);
        }

        tgPM_MT_SM_Init( &psVLKN_CXT_SWAP->m_sSwap_And_View_Lock, u8"VULKAN Swap Chain", 1, 1 );
    }

    /* There is still a race condition here if this function is called from multiple threads. */
    tgPM_MT_SM_Wait_Block( &psVLKN_CXT_SWAP->m_sSwap_And_View_Lock );

    if (!psCXT_SWAP->m_bInit)
    {
        /* Create synchronization objects ---------------------------------------------------------------------------------------------------------------------------------------- */

        TgSTD_ATOMIC(fetch_add)( &psVLKN_CXT_SWAP->m_xuiSemaphore_Timeline_Value, 1 );
        if (TgFAILED(tgKN_GPU_VLKN_Create_Semaphore_Timeline(&psVLKN_CXT_SWAP->m_hVLKN_Semaphore_Timeline, hVLKN_Device)))
        {
            TgERROR_MSGF(0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create semaphore");
            goto tgKN_GPU_EXT__SwapChain__Init_FAILED;
        }
        TgMACRO_KN_GPU_VLKN_SET_NAME( hVLKN_Device, VK_OBJECT_TYPE_SEMAPHORE, psVLKN_CXT_SWAP->m_hVLKN_Semaphore_Timeline, u8"Swap Chain: Timeline Semaphore" );

        /* Initialize the Command Sync Structures -------------------------------------------------------------------------------------------------------------------------------- */

        for (uiIndex = 0; uiIndex < TgARRAY_COUNT(psVLKN_CXT_SWAP->m_sOutput_Sync); ++uiIndex)
        {
            STg2_KN_GPU_VLKN_Output_Sync_PC     psOutput_Sync = psVLKN_CXT_SWAP->m_sOutput_Sync + uiIndex;

            psOutput_Sync->m_uiTimeline_Transition_To_Render_Counter = 0;
            psOutput_Sync->m_uiTimeline_Transition_To_Present_Counter = 0;

            if (TgFAILED(tgKN_GPU_VLKN_Create_Semaphore_Binary( &psOutput_Sync->m_hVLKN_Semaphore_Binary_Image_Available, hVLKN_Device )))
            {
                goto tgKN_GPU_EXT__SwapChain__Init_FAILED;
            }
            TgMACRO_KN_GPU_VLKN_SET_NAME( hVLKN_Device, VK_OBJECT_TYPE_SEMAPHORE, psOutput_Sync->m_hVLKN_Semaphore_Binary_Image_Available,
                                          u8"Swap Chain: Binary Semaphore: Image Available" );

            if (TgFAILED(tgKN_GPU_VLKN_Create_Semaphore_Binary( &psOutput_Sync->m_hVLKN_Semaphore_Binary_Transition_To_Present_Complete, hVLKN_Device )))
            {
                goto tgKN_GPU_EXT__SwapChain__Init_FAILED;
            }
            TgMACRO_KN_GPU_VLKN_SET_NAME( hVLKN_Device, VK_OBJECT_TYPE_SEMAPHORE, psOutput_Sync->m_hVLKN_Semaphore_Binary_Transition_To_Present_Complete,
                                          u8"Swap Chain: Binary Semaphore: Transition To Present Complete" );
        }
    }

    /* Query supported formats --------------------------------------------------------------------------------------------------------------------------------------------------- */
    /* We requery the surface formats here for the non-headless surface. */

    if (nullptr == psVLKN_CXT_SWAP->m_psVLKN_Surface_Format)
    {
        eResult = vkGetPhysicalDeviceSurfaceFormatsKHR( hVLKN_Physical_Device, psVLKN_CXT_SWAP->m_hVLKN_Surface, &uiVkUint32, nullptr );
        if (VK_SUCCESS != eResult)
        {
            TgERROR_MSGF(0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to get surface formats");
            goto tgKN_GPU_EXT__SwapChain__Init_FAILED;
        }
        psVLKN_CXT_SWAP->m_nuiVLKN_Surface_Format = uiVkUint32;

        psVLKN_CXT_SWAP->m_psVLKN_Surface_Format = (VkSurfaceFormatKHR_P)TgMALLOC_POOL( sizeof( VkSurfaceFormatKHR ) * uiVkUint32 );
        if (nullptr == psVLKN_CXT_SWAP->m_psVLKN_Surface_Format)
        {
            TgERROR_MSGF(0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to allocate memory for surface formats");
            goto tgKN_GPU_EXT__SwapChain__Init_FAILED;
        }

        eResult = vkGetPhysicalDeviceSurfaceFormatsKHR( hVLKN_Physical_Device, psVLKN_CXT_SWAP->m_hVLKN_Surface, &uiVkUint32, psVLKN_CXT_SWAP->m_psVLKN_Surface_Format );
        if (VK_SUCCESS != eResult)
        {
            TgERROR_MSGF(0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to get surface formats");
            goto tgKN_GPU_EXT__SwapChain__Init_FAILED;
        }
    }

    /* Query present modes ------------------------------------------------------------------------------------------------------------------------------------------------------- */
    if (nullptr == psVLKN_CXT_SWAP->m_penVLKN_Present_Mode)
    {
        eResult = vkGetPhysicalDeviceSurfacePresentModesKHR( hVLKN_Physical_Device, psVLKN_CXT_SWAP->m_hVLKN_Surface, &uiVkUint32, nullptr );
        if (VK_SUCCESS != eResult || uiVkUint32 == 0)
        {
            TgERROR_MSGF(0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to get present modes");
            goto tgKN_GPU_EXT__SwapChain__Init_FAILED;
        }
        psVLKN_CXT_SWAP->m_nuiVLKN_Present_Mode = uiVkUint32;

        psVLKN_CXT_SWAP->m_penVLKN_Present_Mode = (VkPresentModeKHR*)TgMALLOC_POOL( uiVkUint32 * sizeof( VkPresentModeKHR ) );
        if (!psVLKN_CXT_SWAP->m_penVLKN_Present_Mode)
        {
            TgERROR_MSGF(0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to allocate memory for present modes");
            goto tgKN_GPU_EXT__SwapChain__Init_FAILED;
        }

        eResult = vkGetPhysicalDeviceSurfacePresentModesKHR( hVLKN_Physical_Device, psVLKN_CXT_SWAP->m_hVLKN_Surface, &uiVkUint32, psVLKN_CXT_SWAP->m_penVLKN_Present_Mode );
        if (VK_SUCCESS != eResult || uiVkUint32 == 0)
        {
            TgERROR_MSGF(0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to get present modes");
            goto tgKN_GPU_EXT__SwapChain__Init_FAILED;
        }
    }

    /* Get surface capabilities -------------------------------------------------------------------------------------------------------------------------------------------------- */

    if (!psCXT_SWAP->m_bInit)
    {
        eResult = vkGetPhysicalDeviceSurfaceCapabilitiesKHR( hVLKN_Physical_Device, psVLKN_CXT_SWAP->m_hVLKN_Surface, &psVLKN_CXT_SWAP->m_sVLKN_Capabilities );
        if (eResult != VK_SUCCESS)
        {
            TgERROR_MSGF(0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to get surface capabilities");
            goto tgKN_GPU_EXT__SwapChain__Init_FAILED;
        }
    }

    /* Update the swap context with the most recent data from the output device that is displaying the majority of the render surface area (assuming a window) ------------------- */

    tgKN_OS_GPU_CXT_SWAP_Update_Output( tiCXT_SWAP, psCXT_SWAP->m_uiOS_ID, true );

    /* Select surface format ----------------------------------------------------------------------------------------------------------------------------------------------------- */

    /* Defaults to VK_COLOR_SPACE_BT709_NONLINEAR_EXT for LDR */
    sVLKN_Selected_Surface_Format = psVLKN_CXT_SWAP->m_psVLKN_Surface_Format[0];
    enVLKN_Colour_Space = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;

    /* Test to see if the swap chain is on a monitor that would support HDR. */
    if (psCXT_SWAP->m_bHDR_Supported && psCXT_SWAP->m_bHDR_Request)
    {
        if (ETgKN_GPU_EXT_FORMAT_R16G16B16A16_SFLOAT == psCXT_SWAP->m_enFormat_RT)
        {
            enVLKN_Colour_Space = VK_COLOR_SPACE_EXTENDED_SRGB_LINEAR_EXT; // HDR Linear
        }

        if (ETgKN_GPU_EXT_FORMAT_A2B10G10R10_UNORM_PACK32 == psCXT_SWAP->m_enFormat_RT)
        {
            enVLKN_Colour_Space = VK_COLOR_SPACE_HDR10_ST2084_EXT; // HDR10
        }
    }

    for (uiIndex = 0; uiIndex < psVLKN_CXT_SWAP->m_nuiVLKN_Surface_Format; ++uiIndex)
    {
        if (psVLKN_CXT_SWAP->m_psVLKN_Surface_Format[uiIndex].format == (VkFormat)psCXT_SWAP->m_enFormat_RT &&
            psVLKN_CXT_SWAP->m_psVLKN_Surface_Format[uiIndex].colorSpace == enVLKN_Colour_Space)
        {
            sVLKN_Selected_Surface_Format = psVLKN_CXT_SWAP->m_psVLKN_Surface_Format[uiIndex];
            break;
        }
    }

    if (uiIndex >= psVLKN_CXT_SWAP->m_nuiVLKN_Surface_Format)
    {
        TgERROR_MSGF(0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to find a matching surface format for the back buffer");
        goto tgKN_GPU_EXT__SwapChain__Init_FAILED;
    }

    /* Select present mode ------------------------------------------------------------------------------------------------------------------------------------------------------- */

    /* FIFO is always available and provides VSync */
    enVLKN_Selected_Present_Mode = VK_PRESENT_MODE_FIFO_KHR;

    if (0 != psCXT_SWAP->m_uiVSync)
    {
        /* Prefer mailbox (triple buffering) for low latency */
        for (uiIndex = 0; uiIndex < psVLKN_CXT_SWAP->m_nuiVLKN_Present_Mode; ++uiIndex)
        {
            if (VK_PRESENT_MODE_MAILBOX_KHR == psVLKN_CXT_SWAP->m_penVLKN_Present_Mode[uiIndex])
            {
                enVLKN_Selected_Present_Mode = VK_PRESENT_MODE_MAILBOX_KHR;
            };
        };

        /* Try immediate mode */
        for (uiIndex = 0; uiIndex < psVLKN_CXT_SWAP->m_nuiVLKN_Present_Mode; ++uiIndex)
        {
            if (VK_PRESENT_MODE_IMMEDIATE_KHR == psVLKN_CXT_SWAP->m_penVLKN_Present_Mode[uiIndex])
            {
                enVLKN_Selected_Present_Mode = VK_PRESENT_MODE_IMMEDIATE_KHR;
            };
        }
    }

    /* Determine image count ----------------------------------------------------------------------------------------------------------------------------------------------------- */

    uiSelected_Image_Count = psVLKN_CXT_SWAP->m_sVLKN_Capabilities.minImageCount + 1;

    if (psVLKN_CXT_SWAP->m_sVLKN_Capabilities.maxImageCount > 0 && uiSelected_Image_Count > psVLKN_CXT_SWAP->m_sVLKN_Capabilities.maxImageCount)
    {
        uiSelected_Image_Count = psVLKN_CXT_SWAP->m_sVLKN_Capabilities.maxImageCount;
    };

    /* Select extent ------------------------------------------------------------------------------------------------------------------------------------------------------------- */

    if (psVLKN_CXT_SWAP->m_sVLKN_Capabilities.currentExtent.width != UINT32_MAX)
    {
        sVLKN_Selected_Extent = psVLKN_CXT_SWAP->m_sVLKN_Capabilities.currentExtent;
    }
    else
    {
        sVLKN_Selected_Extent.width = psCXT_SWAP->m_sMode.m_sBuffer.m_uiWidth;
        sVLKN_Selected_Extent.height = psCXT_SWAP->m_sMode.m_sBuffer.m_uiHeight;
    }

    sVLKN_Selected_Extent.width = tgCM_CLP_U32( sVLKN_Selected_Extent.width, psVLKN_CXT_SWAP->m_sVLKN_Capabilities.minImageExtent.width,
                                                psVLKN_CXT_SWAP->m_sVLKN_Capabilities.maxImageExtent.width );
    sVLKN_Selected_Extent.height = tgCM_CLP_U32( sVLKN_Selected_Extent.height, psVLKN_CXT_SWAP->m_sVLKN_Capabilities.minImageExtent.height,
                                                 psVLKN_CXT_SWAP->m_sVLKN_Capabilities.maxImageExtent.height );

    /* Check if we need to create the swapchain ---------------------------------------------------------------------------------------------------------------------------------- */

    bCreate_Swapchain  = VK_NULL_HANDLE == psVLKN_CXT_SWAP->m_hVLKN_Swapchain;
    bCreate_Swapchain |= sVLKN_Selected_Surface_Format.format != psVLKN_CXT_SWAP->m_sVLKN_Selected_Surface_Format.format;
    bCreate_Swapchain |= sVLKN_Selected_Surface_Format.colorSpace != psVLKN_CXT_SWAP->m_sVLKN_Selected_Surface_Format.colorSpace;
    bCreate_Swapchain |= sVLKN_Selected_Extent.width != psVLKN_CXT_SWAP->m_sVLKN_Selected_Extent.width;
    bCreate_Swapchain |= sVLKN_Selected_Extent.height != psVLKN_CXT_SWAP->m_sVLKN_Selected_Extent.height;
    bCreate_Swapchain |= psVLKN_CXT_SWAP->m_uiSelected_Image_Count != psVLKN_CXT_SWAP->m_sVLKN_Capabilities.minImageCount + 1;
    bCreate_Swapchain |= enVLKN_Selected_Present_Mode != psVLKN_CXT_SWAP->m_enVLKN_Selected_Present_Mode;

    if (bCreate_Swapchain || bForceInitSwapChain)
    {
        TgUINT_E32                          auiQueueFamilyIndices[2];
        VkSwapchainCreateInfoKHR            sCreateInfo;

        /* Handle queue family indices */
        auiQueueFamilyIndices[0] = (TgUINT_E32)psGPU_EXT_Physical_Device->m_auiVLKN_Queue_Family_Index[ETgKN_GPU_EXT_COMMAND_GRAPHICS];
        auiQueueFamilyIndices[1] = (TgUINT_E32)psGPU_EXT_Physical_Device->m_auiVLKN_Queue_Family_Index[ETgKN_GPU_EXT_COMMAND_PRESENT];

        tgMM_Set_U08_0x00( &sCreateInfo, sizeof( sCreateInfo ) );
        sCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        sCreateInfo.pNext = nullptr;
        sCreateInfo.flags = 0;
        sCreateInfo.surface = psVLKN_CXT_SWAP->m_hVLKN_Surface;
        sCreateInfo.minImageCount = (TgUINT_E32)uiSelected_Image_Count;
        sCreateInfo.imageFormat = sVLKN_Selected_Surface_Format.format;
        sCreateInfo.imageColorSpace = sVLKN_Selected_Surface_Format.colorSpace;
        sCreateInfo.imageExtent = sVLKN_Selected_Extent;
        sCreateInfo.imageArrayLayers = 1;
        sCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_STORAGE_BIT;

        if (auiQueueFamilyIndices[0] != auiQueueFamilyIndices[1])
        {
            sCreateInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
            sCreateInfo.queueFamilyIndexCount = 2;
            sCreateInfo.pQueueFamilyIndices = auiQueueFamilyIndices;
        }
        else
        {
            sCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
            sCreateInfo.queueFamilyIndexCount = 0;
            sCreateInfo.pQueueFamilyIndices = nullptr;
        }

        sCreateInfo.preTransform = psVLKN_CXT_SWAP->m_sVLKN_Capabilities.currentTransform;
        sCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        sCreateInfo.presentMode = enVLKN_Selected_Present_Mode;
        sCreateInfo.clipped = VK_TRUE;
        sCreateInfo.oldSwapchain = psVLKN_CXT_SWAP->m_hVLKN_Swapchain;

        eResult = vkCreateSwapchainKHR( hVLKN_Device, &sCreateInfo, g_psKN_GPU_VLKN_Allocator, &psVLKN_CXT_SWAP->m_hVLKN_Swapchain );
        if (eResult != VK_SUCCESS)
        {
            TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create swap chain" );
            goto tgKN_GPU_EXT__SwapChain__Init_FAILED;
        }
        
        if (VK_NULL_HANDLE != sCreateInfo.oldSwapchain)
        {
            tgKN_GPU_EXT_CXT_SWAP_Free_For_Resize( psVLKN_CXT_SWAP, hVLKN_Device, sCreateInfo.oldSwapchain );
        }

        psVLKN_CXT_SWAP->m_sVLKN_Selected_Surface_Format = sVLKN_Selected_Surface_Format;
        psVLKN_CXT_SWAP->m_enVLKN_Selected_Present_Mode = enVLKN_Selected_Present_Mode;
        psVLKN_CXT_SWAP->m_uiSelected_Image_Count = uiSelected_Image_Count;
        psVLKN_CXT_SWAP->m_sVLKN_Selected_Extent = sVLKN_Selected_Extent;

        psCXT_SWAP->m_bHDR_Enabled = false;
        psCXT_SWAP->m_enColour_Space = ETgKN_GPU_HLSL_COLOUR_SPACE_G22_P709;
        if (psCXT_SWAP->m_bHDR_Supported && psCXT_SWAP->m_bHDR_Request)
        {
            if ((ETgKN_GPU_EXT_FORMAT_R16G16B16A16_SFLOAT == (TgSINT_E32)sVLKN_Selected_Surface_Format.format) &&
                (VK_COLOR_SPACE_EXTENDED_SRGB_LINEAR_EXT == (TgSINT_E32)sVLKN_Selected_Surface_Format.colorSpace))
            {
                psCXT_SWAP->m_bHDR_Enabled = true;
                psCXT_SWAP->m_enColour_Space = ETgKN_GPU_HLSL_COLOUR_SPACE_G10_P709;
            };

            if ((ETgKN_GPU_EXT_FORMAT_A2B10G10R10_UNORM_PACK32 == (TgSINT_E32)sVLKN_Selected_Surface_Format.format) &&
                (VK_COLOR_SPACE_HDR10_ST2084_EXT == (TgSINT_E32)sVLKN_Selected_Surface_Format.colorSpace))
            {
                psCXT_SWAP->m_bHDR_Enabled = true;
                psCXT_SWAP->m_enColour_Space = ETgKN_GPU_HLSL_COLOUR_SPACE_G2084_P2020;
            }
        }

        /* Initialize the Render Targets ----------------------------------------------------------------------------------------------------------------------------------------- */

        psVLKN_CXT_SWAP->m_asBack_Buffer__Render_Target[0].m_sRender_Target_DESC.m_uiWidth = psVLKN_CXT_SWAP->m_sVLKN_Selected_Extent.width;
        psVLKN_CXT_SWAP->m_asBack_Buffer__Render_Target[0].m_sRender_Target_DESC.m_uiHeight = psVLKN_CXT_SWAP->m_sVLKN_Selected_Extent.height;
        psVLKN_CXT_SWAP->m_asBack_Buffer__Render_Target[0].m_sRender_Target_DESC.m_enDepth_Stencil_Format = psCXT_SWAP->m_enFormat_DS;
        psVLKN_CXT_SWAP->m_asBack_Buffer__Render_Target[0].m_sRender_Target_DESC.m_aenColour_Format[0] = (ETgKN_GPU_EXT_FORMAT)sVLKN_Selected_Surface_Format.format;
        psVLKN_CXT_SWAP->m_asBack_Buffer__Render_Target[0].m_sRender_Target_DESC.m_nuiColour_Target = 1;
        psVLKN_CXT_SWAP->m_asBack_Buffer__Render_Target[0].m_sRender_Target_DESC.m_enColour_Space = psCXT_SWAP->m_enColour_Space;

        {   /* Copy in all of the back buffers to their corresponding render target wrappers */
            VkImage                             ahVLKN_Back_Buffer_Images[KTgKN_GPU_MAX_BUFFER_IN_FLIP_CHAIN];

            vkGetSwapchainImagesKHR( hVLKN_Device, psVLKN_CXT_SWAP->m_hVLKN_Swapchain, &uiVkUint32, nullptr );
            if (uiVkUint32 > KTgKN_GPU_MAX_BUFFER_IN_FLIP_CHAIN)
            {
                uiVkUint32 = KTgKN_GPU_MAX_BUFFER_IN_FLIP_CHAIN;
            }
            psVLKN_CXT_SWAP->m_nuiBack_Buffer_Image = uiVkUint32;

            vkGetSwapchainImagesKHR( hVLKN_Device, psVLKN_CXT_SWAP->m_hVLKN_Swapchain, &uiVkUint32, ahVLKN_Back_Buffer_Images );
            psVLKN_CXT_SWAP->m_asBack_Buffer__Render_Target[0].m_ahVLKN_Colour_Image[0] = ahVLKN_Back_Buffer_Images[0];

            /* Initialize the render target id and create all of the pipelines */
            if (TgFAILED( tgKN_GPU_VLKN__Render_Target__Init( psVLKN_CXT_SWAP->m_asBack_Buffer__Render_Target, hVLKN_Device, psVLKN_CXT_EXEC ) ))
            {
                TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to initialize render target for swap chain" );
                goto tgKN_GPU_EXT__SwapChain__Init_FAILED;
            }

            /* Initialize the depth buffer, and create the image views for the back buffers */
            if (TgFAILED( tgKN_GPU_VLKN__Render_Target__Create_Resources( psVLKN_CXT_SWAP->m_asBack_Buffer__Render_Target, hVLKN_Device, psVLKN_CXT_EXEC ) ))
            {
                TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to initialize render target resources for swap chain" );
                goto tgKN_GPU_EXT__SwapChain__Init_FAILED;
            }

            for (uiIndex = 1; uiIndex < psVLKN_CXT_SWAP->m_nuiBack_Buffer_Image; ++uiIndex)
            {
                tgMM_Copy( psVLKN_CXT_SWAP->m_asBack_Buffer__Render_Target + uiIndex, sizeof(psVLKN_CXT_SWAP->m_asBack_Buffer__Render_Target[uiIndex]),
                           psVLKN_CXT_SWAP->m_asBack_Buffer__Render_Target, sizeof(psVLKN_CXT_SWAP->m_asBack_Buffer__Render_Target[0]));
                psVLKN_CXT_SWAP->m_asBack_Buffer__Render_Target[uiIndex].m_ahVLKN_Colour_Image[0] = ahVLKN_Back_Buffer_Images[uiIndex];

                /* Initialize the image view for the specific back bufffer image */
                if (TgFAILED( tgKN_GPU_VLKN__Render_Target__Create_Resources( psVLKN_CXT_SWAP->m_asBack_Buffer__Render_Target, hVLKN_Device, psVLKN_CXT_EXEC ) ))
                {
                    TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to initialize render target resources for swap chain" );
                    goto tgKN_GPU_EXT__SwapChain__Init_FAILED;
                }
            }
        }
    }

    /* Set the HDR metadata */
    if (psCXT_SWAP->m_bHDR_Enabled)
    {
        VkHdrMetadataEXT hdrMetadata = {
            .sType = VK_STRUCTURE_TYPE_HDR_METADATA_EXT,
            .pNext = nullptr,

            // Display primaries (in normalized chromaticity coordinates)
            .displayPrimaryRed = {psCXT_SWAP->m_sOutput_DESC.m_fRed_Primary_0, psCXT_SWAP->m_sOutput_DESC.m_fRed_Primary_1},
            .displayPrimaryGreen = {psCXT_SWAP->m_sOutput_DESC.m_fGreen_Primary_0, psCXT_SWAP->m_sOutput_DESC.m_fGreen_Primary_1},
            .displayPrimaryBlue = {psCXT_SWAP->m_sOutput_DESC.m_fBlue_Primary_0, psCXT_SWAP->m_sOutput_DESC.m_fBlue_Primary_1},

            // White point (D65 for most displays)
            .whitePoint = {psCXT_SWAP->m_sOutput_DESC.m_fWhite_Point_0, psCXT_SWAP->m_sOutput_DESC.m_fWhite_Point_1},

            // Luminance values
            .maxLuminance = psCXT_SWAP->m_sOutput_DESC.m_fMax_Luminance,
            .minLuminance = psCXT_SWAP->m_sOutput_DESC.m_fMin_Luminance,
            .maxContentLightLevel = psCXT_SWAP->m_fMax_Content_Light_Level,
            .maxFrameAverageLightLevel = psCXT_SWAP->m_fMax_Frame_Average_Light_Level
        };
        
        vkSetHdrMetadataEXT( hVLKN_Device, 1, &psVLKN_CXT_SWAP->m_hVLKN_Swapchain, &hdrMetadata );
    }

    psCXT_SWAP->m_bInit = true;
    tgPM_MT_SM_Signal( &psVLKN_CXT_SWAP->m_sSwap_And_View_Lock, 1 );
    return (KTgS_OK);
tgKN_GPU_EXT__SwapChain__Init_FAILED:
    tgKN_GPU_EXT__SwapChain__Free( tiCXT_SWAP );
    tgPM_MT_SM_Signal( &psVLKN_CXT_SWAP->m_sSwap_And_View_Lock, 1 );
    TgDEBUG_BREAK_AND_RETURN( KTgE_FAIL );
}


/* ---- tgKN_GPU_EXT__SwapChain__Free -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_EXT__SwapChain__Free(
    TgKN_GPU_CXT_SWAP_ID_C                      tiCXT_SWAP )
{
    STg2_KN_GPU_VLKN_CXT_SWAP_PC                psVLKN_CXT_SWAP = g_asKN_GPU_EXT_CXT_SWAP + tiCXT_SWAP.m_uiI;
    STg2_KN_GPU_CXT_SWAP_PC                     psCXT_SWAP = g_asKN_GPU_CXT_SWAP + tiCXT_SWAP.m_uiI;

    STg2_KN_GPU_VLKN_CXT_EXEC_P                 psVLKN_CXT_EXEC;
    STg2_KN_GPU_VLKN_Physical_Device_P          psGPU_EXT_Physical_Device;
    TgRSIZE                                     uiIndex;

    TgPARAM_CHECK_INDEX( tiCXT_SWAP.m_uiI, g_asKN_GPU_CXT_SWAP );
    TgPARAM_CHECK( tgKN_GPU_CXT_SWAP_ID_Is_Equal( &(g_asKN_GPU_CXT_SWAP[tiCXT_SWAP.m_uiI].m_tiCXT_SWAP_S), tiCXT_SWAP ) );

    if (VK_NULL_HANDLE == psVLKN_CXT_SWAP->m_hVLKN_Surface)
    {
        return;
    }

    tgPM_MT_SM_Wait_Block( &psVLKN_CXT_SWAP->m_sSwap_And_View_Lock );

    TgPARAM_CHECK_INDEX( psCXT_SWAP->m_tiCXT_EXEC.m_uiI, g_asKN_GPU_EXT_CXT_EXEC );
    psVLKN_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + psCXT_SWAP->m_tiCXT_EXEC.m_uiI;

    psGPU_EXT_Physical_Device = g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Physical_Device + psVLKN_CXT_EXEC->m_idxCXT_HOST_Physical_Device;

    /* Wait for device to be idle */
    if (VK_NULL_HANDLE != psGPU_EXT_Physical_Device->m_hVLKN_Device)
    {
        tgKN_GPU_EXT__Execute__Flush( psCXT_SWAP->m_tiCXT_EXEC );
    }

    /* Release Resources associated with swap chain */
    tgKN_GPU_EXT_CXT_SWAP_Free_For_Resize( psVLKN_CXT_SWAP, psGPU_EXT_Physical_Device->m_hVLKN_Device, psVLKN_CXT_SWAP->m_hVLKN_Swapchain );

    /* Destroy render target - free the pipelines */
    tgKN_GPU_VLKN__Render_Target__Free( psVLKN_CXT_SWAP->m_asBack_Buffer__Render_Target, psGPU_EXT_Physical_Device->m_hVLKN_Device );

    /* Release heap allocations */
    TgFREE_POOL( psVLKN_CXT_SWAP->m_psVLKN_Surface_Format );
    TgFREE_POOL( psVLKN_CXT_SWAP->m_penVLKN_Present_Mode );

    /* Destroy output sync objects */
    for (uiIndex = 0; uiIndex < KTgKN_GPU_MAX_BUFFER_IN_FLIP_CHAIN; ++uiIndex)
    {
        STg2_KN_GPU_VLKN_Output_Sync_PC     psOutput_Sync = psVLKN_CXT_SWAP->m_sOutput_Sync + uiIndex;

        if (VK_NULL_HANDLE != psOutput_Sync->m_hVLKN_Semaphore_Binary_Image_Available)
        {
            vkDestroySemaphore( psGPU_EXT_Physical_Device->m_hVLKN_Device, psOutput_Sync->m_hVLKN_Semaphore_Binary_Image_Available, g_psKN_GPU_VLKN_Allocator );
        }

        if (VK_NULL_HANDLE != psOutput_Sync->m_hVLKN_Semaphore_Binary_Transition_To_Present_Complete)
        {
            vkDestroySemaphore( psGPU_EXT_Physical_Device->m_hVLKN_Device, psOutput_Sync->m_hVLKN_Semaphore_Binary_Transition_To_Present_Complete, g_psKN_GPU_VLKN_Allocator );
        }
    }

    /* Destroy timeline semaphore */
    if (VK_NULL_HANDLE != psVLKN_CXT_SWAP->m_hVLKN_Semaphore_Timeline)
    {
        vkDestroySemaphore( psGPU_EXT_Physical_Device->m_hVLKN_Device, psVLKN_CXT_SWAP->m_hVLKN_Semaphore_Timeline, g_psKN_GPU_VLKN_Allocator );
        psVLKN_CXT_SWAP->m_hVLKN_Semaphore_Timeline = VK_NULL_HANDLE;
    }

    /* Destroy surface */
    if (VK_NULL_HANDLE != psVLKN_CXT_SWAP->m_hVLKN_Surface)
    {
        vkDestroySurfaceKHR( g_sKN_GPU_EXT_CXT_HOST.m_hVLKN_Instance, psVLKN_CXT_SWAP->m_hVLKN_Surface, g_psKN_GPU_VLKN_Allocator );
        psVLKN_CXT_SWAP->m_hVLKN_Surface = VK_NULL_HANDLE;
    }

    tgPM_MT_SM_Free( &psVLKN_CXT_SWAP->m_sSwap_And_View_Lock );
    tgMM_Set_U08_0x00( psVLKN_CXT_SWAP, sizeof( STg2_KN_GPU_VLKN_CXT_SWAP ) );
    psVLKN_CXT_SWAP->m_tiID = KTgKN_GPU_CXT_SWAP_ID__INVALID;
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_GPU_EXT_CXT_SWAP_Free_For_Resize -----------------------------------------------------------------------------------------------------------------------------------  */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_EXT_CXT_SWAP_Free_For_Resize(
    STg2_KN_GPU_VLKN_CXT_SWAP_PC                psVLKN_CXT_SWAP,
    VkDevice                                    hVLKN_Device,
    VkSwapchainKHR                              hSwapchain )
{
    TgUINT_E32                                  uiIndex;

    /* Destroy the allocations made from the render target. */
    psVLKN_CXT_SWAP->m_asBack_Buffer__Render_Target[0].m_ahVLKN_Colour_Image[0] = VK_NULL_HANDLE;
    tgKN_GPU_VLKN__Render_Target__Destroy_Resources( psVLKN_CXT_SWAP->m_asBack_Buffer__Render_Target, hVLKN_Device );

    /* Some of the data was copied from the first render target to the ones wrapping the other buffers in the swap chain. */
    for (uiIndex = 1; uiIndex < psVLKN_CXT_SWAP->m_nuiBack_Buffer_Image; ++uiIndex)
    {
        psVLKN_CXT_SWAP->m_asBack_Buffer__Render_Target[uiIndex].m_hVLKN_Depth_Stencil_View = VK_NULL_HANDLE;
        psVLKN_CXT_SWAP->m_asBack_Buffer__Render_Target[uiIndex].m_hVLKN_Depth_Stencil_Memory = VK_NULL_HANDLE;
        psVLKN_CXT_SWAP->m_asBack_Buffer__Render_Target[uiIndex].m_hVLKN_Depth_Stencil_Image = VK_NULL_HANDLE;
        psVLKN_CXT_SWAP->m_asBack_Buffer__Render_Target[uiIndex].m_ahVLKN_Colour_Image[0] = VK_NULL_HANDLE;

        tgKN_GPU_VLKN__Render_Target__Destroy_Resources( psVLKN_CXT_SWAP->m_asBack_Buffer__Render_Target + uiIndex, hVLKN_Device );
    }

    for (uiIndex = 0; uiIndex < psVLKN_CXT_SWAP->m_nuiBack_Buffer_Image; ++uiIndex)
    {
        if (VK_NULL_HANDLE != psVLKN_CXT_SWAP->m_ahVLKN_History_Image_Views[uiIndex])
        {
            vkDestroyImageView( hVLKN_Device, psVLKN_CXT_SWAP->m_ahVLKN_History_Image_Views[uiIndex], g_psKN_GPU_VLKN_Allocator );
            psVLKN_CXT_SWAP->m_ahVLKN_History_Image_Views[uiIndex] = VK_NULL_HANDLE;
        }
    }

    /* Destroy swap chain */
    if (VK_NULL_HANDLE != hSwapchain)
    {
        vkDestroySwapchainKHR( hVLKN_Device, hSwapchain, g_psKN_GPU_VLKN_Allocator );
    }
}
