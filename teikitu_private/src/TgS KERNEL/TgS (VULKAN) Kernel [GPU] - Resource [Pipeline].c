/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (VULKAN) Kernel [GPU] - Resource [Pipeline].c
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

/** @brief Create default descriptor set layouts
    @param [in] ARG0 Device handle
    @param [in] ARG1 Vulkan Execution context pointer
    @return Result Code. */
static TgRESULT
tgKN_GPU_VLKN__Execute__Init__Create_Pipeline_Dependencies__Descriptor_Set_Layout(
    VkDevice_C ARG0, STg2_KN_GPU_VLKN_CXT_EXEC_PC TgANALYSIS_NO_NULL ARG1 );

/** @brief Create default pipeline layouts
    @param [in] ARG0 Device handle
    @param [in] ARG1 Vulkan Execution context pointer
    @return Result Code. */
static TgRESULT
tgKN_GPU_VLKN__Execute__Init__Create_Pipeline_Dependencies_Pipeline_Layout(
    VkDevice_C ARG0, STg2_KN_GPU_VLKN_CXT_EXEC_PC TgANALYSIS_NO_NULL ARG1 );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Code Macros                                                                                                                                                                    */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
#define KTgMACRO_KN_GPU_VLKN__Execute__Init__Create_Pipeline_Dependencies_Create_Shader_Module(A)                                                                                   \
    for (uiIndex = 0; uiIndex < TgARRAY_COUNT(g_sKN_GPU_CXT_HOST.m_ati##A); ++uiIndex)                                                                                              \
    {                                                                                                                                                                               \
        if (0 != g_sKN_GPU_CXT_HOST.m_ati##A[uiIndex].m_uiKI)                                                                                                                       \
        {                                                                                                                                                                           \
            TgRSIZE_C                           ui##A##_Index = g_sKN_GPU_CXT_HOST.m_ati##A[uiIndex].m_uiIndex;                                                                     \
            STg2_KN_GPU_SH_DATA_CPC             ps##A##_SH  = &g_asKN_Lib_##A##_Data[ui##A##_Index].m_sSH;                                                                          \
                                                                                                                                                                                    \
            if ((0 != ps##A##_SH->m_nuiData) && (VK_NULL_HANDLE == psVLKN_CXT_EXEC->m_ahVLKN_##A[uiIndex]))                                                                         \
            {                                                                                                                                                                       \
                if (TgFAILED(tgKN_GPU_VLKN_Create_Shader_Module(psVLKN_CXT_EXEC->m_ahVLKN_##A + uiIndex, hVLKN_Device, ps##A##_SH->m_puiConstData, ps##A##_SH->m_nuiData)))         \
                {                                                                                                                                                                   \
                    tgKN_GPU_VLKN__Execute__Free__Destroy_Pipeline_Dependencies(psVLKN_CXT_EXEC->m_sContext_Command[uiWORK].m_tiCXT_EXEC);                                          \
                    return (KTgE_FAIL);                                                                                                                                             \
                }                                                                                                                                                                   \
            }                                                                                                                                                                       \
        }                                                                                                                                                                           \
    }

#define KTgMACRO_KN_GPU_VLKN__Execute__Free__Destroy_Default_Pipeline_Dependencies_Create_Shader_Module(A)                                                                          \
    for (uiIndex = 0; uiIndex < TgARRAY_COUNT(psVLKN_CXT_EXEC->m_ahVLKN_##A); ++uiIndex)                                                                                            \
    {                                                                                                                                                                               \
        if (VK_NULL_HANDLE != psVLKN_CXT_EXEC->m_ahVLKN_##A[uiIndex])                                                                                                               \
        {                                                                                                                                                                           \
            vkDestroyShaderModule(hVLKN_Device, psVLKN_CXT_EXEC->m_ahVLKN_##A[uiIndex], g_psKN_GPU_VLKN_Allocator);                                                                 \
            psVLKN_CXT_EXEC->m_ahVLKN_##A[uiIndex] = VK_NULL_HANDLE;                                                                                                                \
        }                                                                                                                                                                           \
    }




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_GPU_EXT__CMD__Update_Render_DESC_Descriptor_Set --------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_EXT__CMD__Update_Render_DESC_Descriptor_Set(
    STg2_KN_GPU_CMD_PC                          psCMD,
    STg2_KN_GPU_Camera_CPC                      psCamera,
    STg2_KN_GPU_DBG_Render_DESC_CPC             psDBG_Render_DESC,
    STg2_KN_GPU_Output_DESC_CPC                 psOutput_DESC )
{
    UTg2_KN_GPU_CMD_C                           uCMD = { .ps = psCMD };
    TgRSIZE_C                                   uiEXEC = (uCMD.psVLKN->m_sBase.m_tiCXT_WORK.m_uiI >> 16) & 0xFFFF;
    TgRSIZE_C                                   uiWORK = (uCMD.psVLKN->m_sBase.m_tiCXT_WORK.m_uiI & 0xFFFF) % KTgKN_GPU_MAX_EXEC_CONTEXT_COMMAND;
    STg2_KN_GPU_VLKN_CXT_EXEC_PC                psVLKN_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + uiEXEC;

    STg2_KN_GPU_VLKN_CXT_CMD_P                  psVLKN_CXT_CMD;
    TgRSIZE                                     uiUBO_Render_DESC_Offset;
    TgUN_POINTER                                uUBO_Render_DESC_Mapped;
    STg2_KN_GPU_Render_DESC                     sRender_DESC;

    TgPARAM_CHECK_KN_GPU_CMD( psCMD );
    TgPARAM_CHECK(psVLKN_CXT_EXEC->m_uiUBO_Aligned_Render_DESC_Size >= sizeof(sRender_DESC));
    (void)psDBG_Render_DESC; /* Final Builds */

    tgMM_Set_U08_0x00( &sRender_DESC, sizeof(sRender_DESC) );

    psVLKN_CXT_CMD = psVLKN_CXT_EXEC->m_sContext_Command + uiWORK;

    /* Acquire the shared memory for a GPU UBO */
    uiUBO_Render_DESC_Offset = TgSTD_ATOMIC(fetch_add)(&psVLKN_CXT_CMD->m_xuiUBO_Render_DESC_Offset, psVLKN_CXT_EXEC->m_uiUBO_Aligned_Render_DESC_Size);
    TgVERIFY(0 == (uiUBO_Render_DESC_Offset % 16));
    if (uiUBO_Render_DESC_Offset >= psVLKN_CXT_CMD->m_uiUBO_Render_DESC_End || nullptr == psVLKN_CXT_EXEC->m_uUBO_Mapped_Render_DESC.m_pVoid)
    {
        TgERROR_GEN_MSGF(false, u8"UI uniform buffer pool exhausted: %zu/%zu", uiUBO_Render_DESC_Offset, psVLKN_CXT_CMD->m_uiUBO_Render_DESC_End);
        return (KTgE_FAIL);
    }

    /* Set the camera details */
    if (nullptr == psCamera) {
        tgMM_Set_U08_0x00(&sRender_DESC.m_sCamera_Shared, sizeof(sRender_DESC.m_sCamera_Shared));
        sRender_DESC.m_vCamera_Position = tgMH_SET1_F32_04_1(0.0F);
    } else {
        tgMM_Copy(&sRender_DESC.m_sCamera_Shared, sizeof(sRender_DESC.m_sCamera_Shared), &psCamera->m_sCamera_Shared, sizeof(psCamera->m_sCamera_Shared));
        sRender_DESC.m_vCamera_Position = psCamera->m_sConfiguration.m_uCamera_Position.m_vF32_04_1;
    }

    /* Set the output description needed for colour grading */
    if (nullptr == psOutput_DESC) {
        tgMM_Set_U08_0x00(&sRender_DESC.m_sOutput_DESC, sizeof(sRender_DESC.m_sOutput_DESC));
    } else {
        tgMM_Copy(&sRender_DESC.m_sOutput_DESC, sizeof(sRender_DESC.m_sOutput_DESC), psOutput_DESC, sizeof(STg2_KN_GPU_Output_DESC));
    }

#if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)
    /* Set the debug rendering description */
    if (nullptr == psDBG_Render_DESC) {
        tgKN_GPU__CMD__Init_DBG_Render_DESC(&sRender_DESC.m_sDBG_Render_DESC, psCMD, psCamera);
    } else {
        tgMM_Copy(&sRender_DESC.m_sDBG_Render_DESC, sizeof(sRender_DESC.m_sDBG_Render_DESC), psDBG_Render_DESC, sizeof(STg2_KN_GPU_DBG_Render_DESC));
    }
/*# defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
#endif

    /* Upload the render description into the reserved GPU UBO */
    uUBO_Render_DESC_Mapped = psVLKN_CXT_EXEC->m_uUBO_Mapped_Render_DESC;
    uUBO_Render_DESC_Mapped.m_pui08 += uiUBO_Render_DESC_Offset;
    tgMM_Copy(uUBO_Render_DESC_Mapped.m_pVoid, psVLKN_CXT_EXEC->m_uiUBO_Aligned_Render_DESC_Size, &sRender_DESC, sizeof(sRender_DESC));

    /* Flush the mapped memory range to ensure the host writes are visible to the device */
    {
        VkMappedMemoryRange                         sVLKN_Mapped_Memory_Range;

        tgMM_Set_U08_0x00(&sVLKN_Mapped_Memory_Range, sizeof(sVLKN_Mapped_Memory_Range));
        sVLKN_Mapped_Memory_Range.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
        sVLKN_Mapped_Memory_Range.memory = psVLKN_CXT_EXEC->m_hVLKN_Memory__Render_DESC;
        sVLKN_Mapped_Memory_Range.offset = uiUBO_Render_DESC_Offset;
        sVLKN_Mapped_Memory_Range.size = psVLKN_CXT_EXEC->m_uiUBO_Aligned_Render_DESC_Size;

        vkFlushMappedMemoryRanges(uCMD.psVLKN->m_hVLKN_Device, 1, &sVLKN_Mapped_Memory_Range);
    }

    uCMD.psVLKN->m_hVLKN_Buffer__Render_DESC = psVLKN_CXT_EXEC->m_hVLKN_Buffer__Render_DESC;
    uCMD.psVLKN->m_uiUBO_Render_DESC_Offset = (TgUINT_E32)uiUBO_Render_DESC_Offset;

    /* The memory is not host coherent so we need a barrier here to make sure that the copied data is available on the GPU for the next command instruction */
    {
        VkBufferMemoryBarrier2                      sVLKN_Buffer_Barrier;
        VkDependencyInfo                            sVLKN_Dependency_Info;

        tgMM_Set_U08_0x00(&sVLKN_Buffer_Barrier, sizeof(sVLKN_Buffer_Barrier));
        sVLKN_Buffer_Barrier.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER_2;
        sVLKN_Buffer_Barrier.srcStageMask = VK_PIPELINE_STAGE_2_HOST_BIT;
        sVLKN_Buffer_Barrier.srcAccessMask = VK_ACCESS_2_HOST_WRITE_BIT;
        sVLKN_Buffer_Barrier.dstStageMask = VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT;
        sVLKN_Buffer_Barrier.dstAccessMask = VK_ACCESS_2_UNIFORM_READ_BIT;
        sVLKN_Buffer_Barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        sVLKN_Buffer_Barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        sVLKN_Buffer_Barrier.buffer = psVLKN_CXT_EXEC->m_hVLKN_Buffer__Render_DESC;
        sVLKN_Buffer_Barrier.offset = uiUBO_Render_DESC_Offset;
        sVLKN_Buffer_Barrier.size = psVLKN_CXT_EXEC->m_uiUBO_Aligned_Render_DESC_Size;

        tgMM_Set_U08_0x00(&sVLKN_Dependency_Info, sizeof(sVLKN_Dependency_Info));
        sVLKN_Dependency_Info.sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO;
        sVLKN_Dependency_Info.bufferMemoryBarrierCount = 1;
        sVLKN_Dependency_Info.pBufferMemoryBarriers = &sVLKN_Buffer_Barrier;

        vkCmdPipelineBarrier2(uCMD.psVLKN->m_hVLKN_Command_Buffer, &sVLKN_Dependency_Info);
    }

#if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)
    {
        union {
            STg2_KN_GPU_CMD_DBG_P                       psCMD_DBG;
            STg2_KN_GPU_DBG_VLKN_CMD_P                  psCMD_DBG_VLKN;
        }                                           uCMD_DBG;

        if (TgFAILED(tgKN_GPU_EXT__CMD__Command_Debug(&uCMD_DBG.psCMD_DBG, psCMD)))
        {
            return (KTgE_FAIL);
        }

        uCMD_DBG.psCMD_DBG_VLKN->m_uiUBO_Render_DESC_Offset = (TgUINT_E32)uiUBO_Render_DESC_Offset;
    }
/*# defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
#endif

    return (KTgS_OK);
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal VLKN Functions                                                                                                                                                        */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_GPU_VLKN__Execute__Init__Create_Pipeline_Dependencies --------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_VLKN__Execute__Init__Create_Pipeline_Dependencies( STg2_KN_GPU_VLKN_CMD_PC psVLKN_CMD )
{
    TgRSIZE_C                           uiEXEC = (psVLKN_CMD->m_sBase.m_tiCXT_WORK.m_uiI >> 16) & 0xFFFF;
    TgRSIZE_C                           uiWORK = (psVLKN_CMD->m_sBase.m_tiCXT_WORK.m_uiI & 0xFFFF) % KTgKN_GPU_MAX_EXEC_CONTEXT_COMMAND;
    STg2_KN_GPU_VLKN_CXT_EXEC_PC        psVLKN_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + uiEXEC;

    VkDevice                            hVLKN_Device;
    TgRSIZE                             uiIndex;
    VkResult                            eResult;

    TgPARAM_CHECK_KN_GPU_VLKN_CMD( psVLKN_CMD );

    hVLKN_Device = psVLKN_CXT_EXEC->m_hVLKN_Device;

    /* Create the samplers */
    for (uiIndex = 0; uiIndex < TgARRAY_COUNT(g_asKN_GPU_VLKN_Default_Sampler_Create_Info); ++uiIndex)
    {
        VkSampler                           hVLKN_Sampler;

        eResult = vkCreateSampler( hVLKN_Device, g_asKN_GPU_VLKN_Default_Sampler_Create_Info + uiIndex, g_psKN_GPU_VLKN_Allocator, &hVLKN_Sampler );
        if (VK_SUCCESS != eResult)
        {
            TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create sampler" );
            tgKN_GPU_VLKN__Execute__Free__Destroy_Pipeline_Dependencies(psVLKN_CXT_EXEC->m_sContext_Command[uiWORK].m_tiCXT_EXEC);
            return (KTgE_FAIL);
        }
        psVLKN_CXT_EXEC->m_ahVLKN_Sampler[uiIndex] = hVLKN_Sampler;
    }

    /* Create the descriptor set layouts */
    if (TgFAILED(tgKN_GPU_VLKN__Execute__Init__Create_Pipeline_Dependencies__Descriptor_Set_Layout( hVLKN_Device, psVLKN_CXT_EXEC )))
    {
        tgKN_GPU_VLKN__Execute__Free__Destroy_Pipeline_Dependencies(psVLKN_CXT_EXEC->m_sContext_Command[uiWORK].m_tiCXT_EXEC);
        return (KTgE_FAIL);
    }

    /* Create the pipeline layouts */
    if (TgFAILED(tgKN_GPU_VLKN__Execute__Init__Create_Pipeline_Dependencies_Pipeline_Layout( hVLKN_Device, psVLKN_CXT_EXEC )))
    {
        tgKN_GPU_VLKN__Execute__Free__Destroy_Pipeline_Dependencies(psVLKN_CXT_EXEC->m_sContext_Command[uiWORK].m_tiCXT_EXEC);
        return (KTgE_FAIL);
    }

    /* Create shaders */
    KTgMACRO_KN_GPU_VLKN__Execute__Init__Create_Pipeline_Dependencies_Create_Shader_Module(VS);
    KTgMACRO_KN_GPU_VLKN__Execute__Init__Create_Pipeline_Dependencies_Create_Shader_Module(FS);
    KTgMACRO_KN_GPU_VLKN__Execute__Init__Create_Pipeline_Dependencies_Create_Shader_Module(CS);

    return (KTgS_OK);
}


/* ---- tgKN_GPU_VLKN__Execute__Free__Destroy_Pipeline_Dependencies ------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_VLKN__Execute__Free__Destroy_Pipeline_Dependencies( TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC )
{
    STg2_KN_GPU_VLKN_CXT_EXEC_PC        psVLKN_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + tiCXT_EXEC.m_uiI;

    VkDevice                            hVLKN_Device;
    TgRSIZE                             uiIndex;

    TgPARAM_CHECK_INDEX( tiCXT_EXEC.m_uiI, g_asKN_GPU_CXT_EXEC );
    TgPARAM_CHECK( tgKN_GPU_CXT_EXEC_ID_Is_Equal( &(g_asKN_GPU_CXT_EXEC[tiCXT_EXEC.m_uiI].m_tiCXT_EXEC_S), tiCXT_EXEC ) );

    hVLKN_Device = psVLKN_CXT_EXEC->m_hVLKN_Device;

    for (uiIndex = 0; uiIndex < TgARRAY_COUNT(psVLKN_CXT_EXEC->m_ahVLKN_Pipeline_Layout); ++uiIndex)
    {
        if (VK_NULL_HANDLE == psVLKN_CXT_EXEC->m_ahVLKN_Pipeline_Layout[uiIndex])
            continue;
        vkDestroyPipelineLayout(hVLKN_Device, psVLKN_CXT_EXEC->m_ahVLKN_Pipeline_Layout[uiIndex], g_psKN_GPU_VLKN_Allocator);
        psVLKN_CXT_EXEC->m_ahVLKN_Pipeline_Layout[uiIndex] = VK_NULL_HANDLE;
    }

    for (uiIndex = 0; uiIndex < TgARRAY_COUNT(psVLKN_CXT_EXEC->m_ahVLKN_Descriptor_Set_Layout); ++uiIndex)
    {
        if (VK_NULL_HANDLE == psVLKN_CXT_EXEC->m_ahVLKN_Descriptor_Set_Layout[uiIndex])
            continue;
        vkDestroyDescriptorSetLayout(hVLKN_Device, psVLKN_CXT_EXEC->m_ahVLKN_Descriptor_Set_Layout[uiIndex], g_psKN_GPU_VLKN_Allocator);
        psVLKN_CXT_EXEC->m_ahVLKN_Descriptor_Set_Layout[uiIndex] = VK_NULL_HANDLE;
    }

    for (uiIndex = 0; uiIndex < TgARRAY_COUNT(psVLKN_CXT_EXEC->m_ahVLKN_Sampler); ++uiIndex)
    {
        if (VK_NULL_HANDLE == psVLKN_CXT_EXEC->m_ahVLKN_Sampler[uiIndex])
            continue;
        vkDestroySampler( hVLKN_Device, psVLKN_CXT_EXEC->m_ahVLKN_Sampler[uiIndex], g_psKN_GPU_VLKN_Allocator );
        psVLKN_CXT_EXEC->m_ahVLKN_Sampler[uiIndex] = VK_NULL_HANDLE;
    }

    KTgMACRO_KN_GPU_VLKN__Execute__Free__Destroy_Default_Pipeline_Dependencies_Create_Shader_Module(VS);
    KTgMACRO_KN_GPU_VLKN__Execute__Free__Destroy_Default_Pipeline_Dependencies_Create_Shader_Module(FS);
    KTgMACRO_KN_GPU_VLKN__Execute__Free__Destroy_Default_Pipeline_Dependencies_Create_Shader_Module(CS);
}


/* ---- tgKN_GPU_VLKN__Execute__Init__Create_Compute_Pipelines -------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_VLKN__Execute__Init__Create_Compute_Pipelines( STg2_KN_GPU_VLKN_CMD_PC psVLKN_CMD )
{
    (TgVOID)psVLKN_CMD;
    // TgRSIZE_C                           uiEXEC = (psVLKN_CMD->m_sBase.m_tiCXT_WORK.m_uiI >> 16) & 0xFFFF;
    // STg2_KN_GPU_VLKN_CXT_EXEC_PC        psVLKN_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + uiEXEC;

    // VkDevice                            hVLKN_Device;
    // VkComputePipelineCreateInfo         sCompute_Pipeline_Info;
    // TgRSIZE                             uiPipeline;

    // TgPARAM_CHECK_KN_GPU_VLKN_CMD( psVLKN_CMD );

    // hVLKN_Device = psVLKN_CXT_EXEC->m_hVLKN_Device;

    // tgMM_Set_U08_0x00( &sCompute_Pipeline_Info, sizeof( sCompute_Pipeline_Info ) );

    // sCompute_Pipeline_Info.stage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    // sCompute_Pipeline_Info.stage.stage = VK_SHADER_STAGE_COMPUTE_BIT;
    // sCompute_Pipeline_Info.stage.pName = "main";

    // sCompute_Pipeline_Info.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;

    // for (uiPipeline = 0; uiPipeline < ETgKN_GPU_COMPUTE_PIPELINE_COUNT; ++uiPipeline)
    // {
    //     STg2_KN_GPU_Compute_Pipeline_CPC    psDefault_Pipeline_DESC = g_asKN_GPU_Compute_Pipeline + uiPipeline;
    //     TgRSIZE_C                           uiCS_Index = g_sKN_GPU_CXT_HOST.m_atiCS[uiPipeline].m_uiIndex;

    //     VkPipeline                          hVLKN_Pipeline;
    //     VkResult                            eResult;

    //     /* Default Pipeline Layouts are created prior to pipeline creation. This is a logic/process error. */
    //     if (VK_NULL_HANDLE == psVLKN_CXT_EXEC->m_ahVLKN_Pipeline_Layout[psDefault_Pipeline_DESC->m_uiPipeline_Layout])
    //     {
    //         TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Pipeline layout was not created prior to creating a pipeline." );
    //         continue;
    //     }

    //     sCompute_Pipeline_Info.stage.module = psVLKN_CXT_EXEC->m_ahVLKN_CS[uiCS_Index];
    //     sCompute_Pipeline_Info.layout = psVLKN_CXT_EXEC->m_ahVLKN_Pipeline_Layout[psDefault_Pipeline_DESC->m_uiPipeline_Layout];

    //     eResult = vkCreateComputePipelines( hVLKN_Device, VK_NULL_HANDLE, 1, &sCompute_Pipeline_Info, g_psKN_GPU_VLKN_Allocator, &hVLKN_Pipeline );
    //     if (VK_SUCCESS != eResult)
    //     {
    //         TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create compute pipeline." );
    //         psVLKN_CXT_EXEC->m_ahVLKN_Pipeline_Compute[uiPipeline] = VK_NULL_HANDLE;
    //         continue;
    //     }

    //     psVLKN_CXT_EXEC->m_ahVLKN_Pipeline_Compute[uiPipeline] = hVLKN_Pipeline;

    //     #if defined(TgCOMPILE__GPU_OBJECT_NAME) && TgCOMPILE__GPU_OBJECT_NAME
    //     {
    //         TgCHAR_U8                           uszDebugName[KTgKN_RESOURCE_NAME_MAX];
    //         TgCHAR_U8                           uszMessage[128];

    //         tgUSZ_PrintF( uszDebugName, sizeof( uszDebugName ), u8"%s", g_asKN_GPU_Compute_Pipeline[uiPipeline].m_uszName );
    //         TgMACRO_KN_GPU_VLKN_SET_NAME( hVLKN_Device, VK_OBJECT_TYPE_PIPELINE, hVLKN_Pipeline, uszDebugName );

    //         tgUSZ_PrintF( uszMessage, sizeof(uszMessage), u8"Vulkan Pipeline: %s", uszDebugName );
    //         tgCN_PrintF( KTgCN_CHANEL_LOADING|KTgCN_SEVERITY_F, STD_MSG_LITERAL_1, STD_MSG_POST, uszMessage );
    //     }
    //     /*# defined(TgCOMPILE__GPU_OBJECT_NAME) && TgCOMPILE__GPU_OBJECT_NAME */
    //     #endif
    // }

    return (KTgS_OK);
}


/* ---- tgKN_GPU_VLKN__Execute__Free__Destroy_Compute_Pipelines ---------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_VLKN__Execute__Free__Destroy_Compute_Pipelines( TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC )
{
    (TgVOID)tiCXT_EXEC;
    //STg2_KN_GPU_VLKN_CXT_EXEC_PC        psVLKN_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + tiCXT_EXEC.m_uiI;

    //VkDevice                            hVLKN_Device;
    //TgRSIZE                             uiIndex;

    //TgPARAM_CHECK_INDEX( tiCXT_EXEC.m_uiI, g_asKN_GPU_CXT_EXEC );
    //TgPARAM_CHECK( tgKN_GPU_CXT_EXEC_ID_Is_Equal( &(g_asKN_GPU_CXT_EXEC[tiCXT_EXEC.m_uiI].m_tiCXT_EXEC_S), tiCXT_EXEC ) );

    //hVLKN_Device = psVLKN_CXT_EXEC->m_hVLKN_Device;

    //for (uiIndex = 0; uiIndex < TgARRAY_COUNT(psVLKN_CXT_EXEC->m_ahVLKN_Pipeline_Compute); ++uiIndex)
    //{
    //    if (VK_NULL_HANDLE == psVLKN_CXT_EXEC->m_ahVLKN_Pipeline_Compute[uiIndex])
    //        continue;
    //    vkDestroyPipeline( hVLKN_Device, psVLKN_CXT_EXEC->m_ahVLKN_Pipeline_Compute[uiIndex], g_psKN_GPU_VLKN_Allocator );
    //    psVLKN_CXT_EXEC->m_ahVLKN_Pipeline_Compute[uiIndex] = VK_NULL_HANDLE;
    //}
}


/* ---- tgKN_GPU_VLKN_Create_Graphic_Pipelines ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_VLKN_Create_Graphic_Pipelines( VkPipeline_PC ahVLKN_Pipeline, TgRSIZE_C nuiVLKN_Pipeline, STg2_KN_GPU_VLKN_Graphics_Pipeline_CI_CPC psVLKN_Pipeline_CI )
{
    TgBOOL_C                            bUse_HDR_G22_P709 = (ETgKN_GPU_HLSL_COLOUR_SPACE_G22_P709 == psVLKN_Pipeline_CI->m_enColour_Space);
    TgBOOL_C                            bUse_HDR_G2084_P2020 = (ETgKN_GPU_HLSL_COLOUR_SPACE_G2084_P2020 == psVLKN_Pipeline_CI->m_enColour_Space);
    TgBOOL_C                            bUse_HDR_G10_P709 = (ETgKN_GPU_HLSL_COLOUR_SPACE_G10_P709 == psVLKN_Pipeline_CI->m_enColour_Space);

    typedef struct {
        uint32_t                            HDR_G22_P709;
        uint32_t                            HDR_G2084_P2020;
        uint32_t                            HDR_G10_P709;
        uint32_t                            DBG_USE_LIGHTING;
    } Specialization_Data;
    Specialization_Data                 sSpecialization_Data = { bUse_HDR_G22_P709, bUse_HDR_G2084_P2020, bUse_HDR_G10_P709, false };

    VkSpecializationMapEntry const      asVLKN_Specialization_Entries[] = {
                                            { KTgMACRO_KN_GPU_VLKN_CONSTANT_ID_USE_G22_P709, offsetof( Specialization_Data, HDR_G22_P709 ), sizeof( uint32_t ) },
                                            { KTgMACRO_KN_GPU_VLKN_CONSTANT_ID_USE_G2084_P2020, offsetof( Specialization_Data, HDR_G2084_P2020 ), sizeof( uint32_t ) },
                                            { KTgMACRO_KN_GPU_VLKN_CONSTANT_ID_USE_G10_P709, offsetof( Specialization_Data, HDR_G10_P709 ), sizeof( uint32_t ) },
                                            { KTgMACRO_KN_GPU_VLKN_CONSTANT_ID_DBG_USE_LIGHTING, offsetof( Specialization_Data, DBG_USE_LIGHTING ), sizeof( uint32_t ) },
                                        };

    VkSpecializationInfo                sVLKN_Specialization_Info = {
                                            TgARRAY_COUNT( asVLKN_Specialization_Entries ),
                                            asVLKN_Specialization_Entries,
                                            sizeof( sSpecialization_Data ),
                                            &sSpecialization_Data
                                        };

    struct {
        VkSpecializationInfo                sVLKN_Specialization_Info;
        VkPipelineShaderStageCI             asVLKN_Shader_Stage_CI[5];
        VkPipelineVertexInputStateCI        sVLKN_Vertex_Input_CI;
        VkPipelineInputAssemblyStateCI      sVLKN_Input_Assembly_CI;
        VkPipelineViewportStateCI           sVLKN_Viewport_CI;
        VkPipelineRasterizationStateCI      sVLKN_Rasterization_CI;
        VkPipelineMultisampleStateCI        sVLKN_Multisample_CI;
        VkPipelineDepthStencilStateCI       sVLKN_Depth_Stencil_CI;
        VkPipelineColorBlendStateCI         sVLKN_Colour_Blend_CI;
        VkPipelineDynamicStateCI            sVLKN_Dynamic_CI;
        VkDynamicState                      asVLKN_Dynamic_States[4];
    }                                   sVLKN_Pipeline_CI_Data;
    VkGraphicsPipelineCI                sVLKN_Pipeline_CI;
    TgRSIZE                             uiPipeline, uiShader;

    /* Initialize a PSO (Graphics Pipeline) for each of the enumerated PSO states. */

    tgMM_Set_U08_0x00( &sVLKN_Pipeline_CI, sizeof( sVLKN_Pipeline_CI ) );

    sVLKN_Pipeline_CI.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    sVLKN_Pipeline_CI.pNext = &psVLKN_Pipeline_CI->m_sVLKN_Pipeline_Rendering_CI;
    sVLKN_Pipeline_CI.pStages = sVLKN_Pipeline_CI_Data.asVLKN_Shader_Stage_CI;
    sVLKN_Pipeline_CI.pViewportState = &sVLKN_Pipeline_CI_Data.sVLKN_Viewport_CI;
    sVLKN_Pipeline_CI.pRasterizationState = &sVLKN_Pipeline_CI_Data.sVLKN_Rasterization_CI;
    sVLKN_Pipeline_CI.pMultisampleState = &sVLKN_Pipeline_CI_Data.sVLKN_Multisample_CI;
    sVLKN_Pipeline_CI.pDepthStencilState = &sVLKN_Pipeline_CI_Data.sVLKN_Depth_Stencil_CI;
    sVLKN_Pipeline_CI.pColorBlendState = &sVLKN_Pipeline_CI_Data.sVLKN_Colour_Blend_CI;
    sVLKN_Pipeline_CI.pDynamicState = &sVLKN_Pipeline_CI_Data.sVLKN_Dynamic_CI;
    sVLKN_Pipeline_CI.basePipelineHandle = VK_NULL_HANDLE;
    sVLKN_Pipeline_CI.basePipelineIndex = -1;

    TgVERIFY(psVLKN_Pipeline_CI->m_nuiPipeline_DESC <= nuiVLKN_Pipeline);

    for (uiPipeline = 0; uiPipeline < psVLKN_Pipeline_CI->m_nuiPipeline_DESC; ++uiPipeline)
    {
        STg2_KN_GPU_Graphics_Pipeline_CPC   psPipeline_DESC = psVLKN_Pipeline_CI->m_psPipeline_DESC + uiPipeline;
        VkPipeline                          hVLKN_Pipeline;
        VkResult                            eResult;

        sVLKN_Pipeline_CI.pVertexInputState = nullptr;
        sVLKN_Pipeline_CI.pInputAssemblyState = nullptr;
        sVLKN_Pipeline_CI.stageCount = 0;

        tgMM_Set_U08_0x00( &sVLKN_Pipeline_CI_Data, sizeof( sVLKN_Pipeline_CI_Data ) );

        sSpecialization_Data.DBG_USE_LIGHTING = psPipeline_DESC->m_bUnlit ? 0u : 1u;

        for (uiShader = 0; uiShader < TgARRAY_COUNT(sVLKN_Pipeline_CI_Data.asVLKN_Shader_Stage_CI); ++uiShader)
        {
            sVLKN_Pipeline_CI_Data.asVLKN_Shader_Stage_CI[uiShader].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
            sVLKN_Pipeline_CI_Data.asVLKN_Shader_Stage_CI[uiShader].pName = "main";
            sVLKN_Pipeline_CI_Data.asVLKN_Shader_Stage_CI[uiShader].pSpecializationInfo = &sVLKN_Specialization_Info;
        }

        /* Dynamic State */
        sVLKN_Pipeline_CI_Data.asVLKN_Dynamic_States[0] = VK_DYNAMIC_STATE_VIEWPORT;
        sVLKN_Pipeline_CI_Data.asVLKN_Dynamic_States[1] = VK_DYNAMIC_STATE_SCISSOR;
        sVLKN_Pipeline_CI_Data.sVLKN_Dynamic_CI.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
        sVLKN_Pipeline_CI_Data.sVLKN_Dynamic_CI.pDynamicStates = sVLKN_Pipeline_CI_Data.asVLKN_Dynamic_States;
        sVLKN_Pipeline_CI_Data.sVLKN_Dynamic_CI.dynamicStateCount = 2;

        /* Vertex Shader */
        if ((nullptr != psVLKN_Pipeline_CI->m_ptiVS) && (psVLKN_Pipeline_CI->m_nuiVS != psPipeline_DESC->m_uiVS))
        {
            sVLKN_Pipeline_CI_Data.asVLKN_Shader_Stage_CI[sVLKN_Pipeline_CI.stageCount].module = psVLKN_Pipeline_CI->m_phVLKN_VS[psPipeline_DESC->m_uiVS];
            sVLKN_Pipeline_CI_Data.asVLKN_Shader_Stage_CI[sVLKN_Pipeline_CI.stageCount].stage = VK_SHADER_STAGE_VERTEX_BIT;
            TgVERIFY(nullptr != sVLKN_Pipeline_CI_Data.asVLKN_Shader_Stage_CI[sVLKN_Pipeline_CI.stageCount].module);
            ++sVLKN_Pipeline_CI.stageCount;

            /* Vertex Input State */
            sVLKN_Pipeline_CI.pVertexInputState = &sVLKN_Pipeline_CI_Data.sVLKN_Vertex_Input_CI;
            sVLKN_Pipeline_CI_Data.sVLKN_Vertex_Input_CI = g_asKN_GPU_VLKN_Vertex_Input_State[psPipeline_DESC->m_enInput_Layout];

            /* Input Assembly State */
            sVLKN_Pipeline_CI.pInputAssemblyState = &sVLKN_Pipeline_CI_Data.sVLKN_Input_Assembly_CI;
            sVLKN_Pipeline_CI_Data.sVLKN_Input_Assembly_CI.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
            sVLKN_Pipeline_CI_Data.sVLKN_Input_Assembly_CI.topology = (VkPrimitiveTopology)psPipeline_DESC->m_enTopology;
            sVLKN_Pipeline_CI_Data.sVLKN_Input_Assembly_CI.primitiveRestartEnable = VK_FALSE;

            sVLKN_Pipeline_CI_Data.asVLKN_Dynamic_States[2] = VK_DYNAMIC_STATE_PRIMITIVE_TOPOLOGY;
            ++sVLKN_Pipeline_CI_Data.sVLKN_Dynamic_CI.dynamicStateCount;
        }

        /* Tessellation Control Shader */
        if ((nullptr != psVLKN_Pipeline_CI->m_ptiTCS) && (psVLKN_Pipeline_CI->m_nuiTCS != psPipeline_DESC->m_uiTCS))
        {
            sVLKN_Pipeline_CI_Data.asVLKN_Shader_Stage_CI[sVLKN_Pipeline_CI.stageCount].module = psVLKN_Pipeline_CI->m_phVLKN_TCS[psPipeline_DESC->m_uiTCS];
            sVLKN_Pipeline_CI_Data.asVLKN_Shader_Stage_CI[sVLKN_Pipeline_CI.stageCount].stage = VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT;
            TgVERIFY(nullptr != sVLKN_Pipeline_CI_Data.asVLKN_Shader_Stage_CI[sVLKN_Pipeline_CI.stageCount].module);
            ++sVLKN_Pipeline_CI.stageCount;
        }

        /* Tessellation Evaluation Shader */
        if ((nullptr != psVLKN_Pipeline_CI->m_ptiTES) && (psVLKN_Pipeline_CI->m_nuiTES != psPipeline_DESC->m_uiTES))
        {
            sVLKN_Pipeline_CI_Data.asVLKN_Shader_Stage_CI[sVLKN_Pipeline_CI.stageCount].module = psVLKN_Pipeline_CI->m_phVLKN_TES[psPipeline_DESC->m_uiTES];
            sVLKN_Pipeline_CI_Data.asVLKN_Shader_Stage_CI[sVLKN_Pipeline_CI.stageCount].stage = VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT;
            TgVERIFY(nullptr != sVLKN_Pipeline_CI_Data.asVLKN_Shader_Stage_CI[sVLKN_Pipeline_CI.stageCount].module);
            ++sVLKN_Pipeline_CI.stageCount;
        }

        /* Geometry Shader */
        if ((nullptr != psVLKN_Pipeline_CI->m_ptiGS) && (psVLKN_Pipeline_CI->m_nuiGS != psPipeline_DESC->m_uiGS))
        {
            sVLKN_Pipeline_CI_Data.asVLKN_Shader_Stage_CI[sVLKN_Pipeline_CI.stageCount].module = psVLKN_Pipeline_CI->m_phVLKN_GS[psPipeline_DESC->m_uiGS];
            sVLKN_Pipeline_CI_Data.asVLKN_Shader_Stage_CI[sVLKN_Pipeline_CI.stageCount].stage = VK_SHADER_STAGE_GEOMETRY_BIT;
            TgVERIFY(nullptr != sVLKN_Pipeline_CI_Data.asVLKN_Shader_Stage_CI[sVLKN_Pipeline_CI.stageCount].module);
            ++sVLKN_Pipeline_CI.stageCount;
        }

        /* Task Shader */
        if ((nullptr != psVLKN_Pipeline_CI->m_ptiTS) && (psVLKN_Pipeline_CI->m_nuiTS != psPipeline_DESC->m_uiTS))
        {
            sVLKN_Pipeline_CI_Data.asVLKN_Shader_Stage_CI[sVLKN_Pipeline_CI.stageCount].module = psVLKN_Pipeline_CI->m_phVLKN_TS[psPipeline_DESC->m_uiTS];
            sVLKN_Pipeline_CI_Data.asVLKN_Shader_Stage_CI[sVLKN_Pipeline_CI.stageCount].stage = VK_SHADER_STAGE_TASK_BIT_EXT;
            TgVERIFY(nullptr != sVLKN_Pipeline_CI_Data.asVLKN_Shader_Stage_CI[sVLKN_Pipeline_CI.stageCount].module);
            ++sVLKN_Pipeline_CI.stageCount;
        }

        /* Mesh Shader */
        if ((nullptr != psVLKN_Pipeline_CI->m_ptiMS) && (psVLKN_Pipeline_CI->m_nuiMS != psPipeline_DESC->m_uiMS))
        {
            sVLKN_Pipeline_CI_Data.asVLKN_Shader_Stage_CI[sVLKN_Pipeline_CI.stageCount].module = psVLKN_Pipeline_CI->m_phVLKN_MS[psPipeline_DESC->m_uiMS];
            sVLKN_Pipeline_CI_Data.asVLKN_Shader_Stage_CI[sVLKN_Pipeline_CI.stageCount].stage = VK_SHADER_STAGE_MESH_BIT_EXT;
            TgVERIFY(nullptr != sVLKN_Pipeline_CI_Data.asVLKN_Shader_Stage_CI[sVLKN_Pipeline_CI.stageCount].module);
            ++sVLKN_Pipeline_CI.stageCount;
        }

        /* Fragment Shader */
        if ((nullptr != psVLKN_Pipeline_CI->m_ptiFS) && (psVLKN_Pipeline_CI->m_nuiFS != psPipeline_DESC->m_uiFS))
        {
            sVLKN_Pipeline_CI_Data.asVLKN_Shader_Stage_CI[sVLKN_Pipeline_CI.stageCount].module = psVLKN_Pipeline_CI->m_phVLKN_FS[psPipeline_DESC->m_uiFS];
            sVLKN_Pipeline_CI_Data.asVLKN_Shader_Stage_CI[sVLKN_Pipeline_CI.stageCount].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
            TgVERIFY(nullptr != sVLKN_Pipeline_CI_Data.asVLKN_Shader_Stage_CI[sVLKN_Pipeline_CI.stageCount].module);
            ++sVLKN_Pipeline_CI.stageCount;
        }

        /* Tessellation State */

        /* Viewport State (Dynamic) */
        sVLKN_Pipeline_CI_Data.sVLKN_Viewport_CI.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        sVLKN_Pipeline_CI_Data.sVLKN_Viewport_CI.viewportCount = 1;
        sVLKN_Pipeline_CI_Data.sVLKN_Viewport_CI.scissorCount = 1;

        /* Rasterization State */
        sVLKN_Pipeline_CI_Data.sVLKN_Rasterization_CI = g_asKN_GPU_VLKN_Default_Rasterizer_CI[psPipeline_DESC->m_enRasterizer_State];

        /* Multisample State */
        sVLKN_Pipeline_CI_Data.sVLKN_Multisample_CI.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
        sVLKN_Pipeline_CI_Data.sVLKN_Multisample_CI.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

        /* Depth Stencil State */
        sVLKN_Pipeline_CI_Data.sVLKN_Depth_Stencil_CI = g_asKN_GPU_VLKN_Default_Depth_Stencil_CI[psPipeline_DESC->m_enDepth_State];

        /* Colour Blend State */
        sVLKN_Pipeline_CI_Data.sVLKN_Colour_Blend_CI.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
        sVLKN_Pipeline_CI_Data.sVLKN_Colour_Blend_CI.logicOp = VK_LOGIC_OP_COPY;
        sVLKN_Pipeline_CI_Data.sVLKN_Colour_Blend_CI.attachmentCount = 1;
        sVLKN_Pipeline_CI_Data.sVLKN_Colour_Blend_CI.pAttachments = g_asKN_GPU_VLKN_Default_Blend_Attachment + psPipeline_DESC->m_enBlend_State;

        /* Default Pipeline Layouts are created prior to pipeline creation. This is a logic/process error. */
        if (VK_NULL_HANDLE == psVLKN_Pipeline_CI->m_phVLKN_Pipeline_Layout[psPipeline_DESC->m_uiPipeline_Layout])
        {
            TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Pipeline layout was not created prior to creating a pipeline." );
            continue;
        }

        sVLKN_Pipeline_CI.layout = psVLKN_Pipeline_CI->m_phVLKN_Pipeline_Layout[psPipeline_DESC->m_uiPipeline_Layout];
        
        /* Create a graphics pipeline */
        eResult = vkCreateGraphicsPipelines(psVLKN_Pipeline_CI->m_hVLKN_Device, VK_NULL_HANDLE, 1, &sVLKN_Pipeline_CI, g_psKN_GPU_VLKN_Allocator, &hVLKN_Pipeline );
        if (VK_SUCCESS != eResult)
        {
            TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create graphics pipeline." );
            ahVLKN_Pipeline[uiPipeline] = VK_NULL_HANDLE;
            continue;
        }
        ahVLKN_Pipeline[uiPipeline] = hVLKN_Pipeline;

    #if defined(TgCOMPILE__GPU_OBJECT_NAME) && TgCOMPILE__GPU_OBJECT_NAME
        {
            TgCHAR_U8                           uszDebugName[KTgKN_RESOURCE_NAME_MAX];
            TgCHAR_U8                           uszMessage[128];

            tgUSZ_PrintF( uszDebugName, sizeof( uszDebugName ), u8"%s", g_asKN_GPU_Graphics_Pipeline[uiPipeline].m_uszName );
            TgMACRO_KN_GPU_VLKN_SET_NAME(psVLKN_Pipeline_CI->m_hVLKN_Device, VK_OBJECT_TYPE_PIPELINE, hVLKN_Pipeline, uszDebugName );

            tgUSZ_PrintF( uszMessage, sizeof(uszMessage), u8"Vulkan Pipeline: %s", uszDebugName );
            tgCN_PrintF( KTgCN_CHANEL_LOADING|KTgCN_SEVERITY_F, STD_MSG_LITERAL_1, STD_MSG_POST, uszMessage );
        }
    /*# defined(TgCOMPILE__GPU_OBJECT_NAME) && TgCOMPILE__GPU_OBJECT_NAME */
    #endif
    }

    return (KTgS_OK);
}


/* ---- tgKN_GPU_VLKN_Create_Compute_Pipelines ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_VLKN_Create_Compute_Pipelines( VkPipeline_PC ahVLKN_Pipeline, TgRSIZE_C nuiVLKN_Pipeline, STg2_KN_GPU_VLKN_Compute_Pipeline_CI_CPC psVLKN_Pipeline_CI )
{
    TgBOOL_C                            bUse_HDR_G22_P709 = (ETgKN_GPU_HLSL_COLOUR_SPACE_G22_P709 == psVLKN_Pipeline_CI->m_enColour_Space);
    TgBOOL_C                            bUse_HDR_G2084_P2020 = (ETgKN_GPU_HLSL_COLOUR_SPACE_G2084_P2020 == psVLKN_Pipeline_CI->m_enColour_Space);
    TgBOOL_C                            bUse_HDR_G10_P709 = (ETgKN_GPU_HLSL_COLOUR_SPACE_G10_P709 == psVLKN_Pipeline_CI->m_enColour_Space);

    typedef struct {
        uint32_t                            HDR_G22_P709;
        uint32_t                            HDR_G2084_P2020;
        uint32_t                            HDR_G10_P709;
        uint32_t                            DBG_USE_LIGHTING;
    } Specialization_Data;
    Specialization_Data                 sSpecialization_Data = { bUse_HDR_G22_P709, bUse_HDR_G2084_P2020, bUse_HDR_G10_P709, false };

    VkSpecializationMapEntry const      asVLKN_Specialization_Entries[] = {
                                            { KTgMACRO_KN_GPU_VLKN_CONSTANT_ID_USE_G22_P709, offsetof(Specialization_Data, HDR_G22_P709), sizeof(uint32_t) },
                                            { KTgMACRO_KN_GPU_VLKN_CONSTANT_ID_USE_G2084_P2020, offsetof(Specialization_Data, HDR_G2084_P2020), sizeof(uint32_t) },
                                            { KTgMACRO_KN_GPU_VLKN_CONSTANT_ID_USE_G10_P709, offsetof(Specialization_Data, HDR_G10_P709), sizeof(uint32_t) },
                                            { KTgMACRO_KN_GPU_VLKN_CONSTANT_ID_DBG_USE_LIGHTING, offsetof(Specialization_Data, DBG_USE_LIGHTING), sizeof(uint32_t) },
                                        };

    VkSpecializationInfo                sVLKN_Specialization_Info = {
                                            TgARRAY_COUNT(asVLKN_Specialization_Entries),
                                            asVLKN_Specialization_Entries,
                                            sizeof(sSpecialization_Data),
                                            &sSpecialization_Data
                                        };

    VkComputePipelineCreateInfo         sCompute_Pipeline_Info;
    TgRSIZE                             uiPipeline;

    /* Initialize a PSO (Compute Pipeline) for each of the enumerated PSO states. */

    tgMM_Set_U08_0x00( &sCompute_Pipeline_Info, sizeof( sCompute_Pipeline_Info ) );

    sCompute_Pipeline_Info.stage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    sCompute_Pipeline_Info.stage.stage = VK_SHADER_STAGE_COMPUTE_BIT;
    sCompute_Pipeline_Info.stage.pName = "main";
    sCompute_Pipeline_Info.stage.pSpecializationInfo = &sVLKN_Specialization_Info;

    sCompute_Pipeline_Info.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;

    TgVERIFY(psVLKN_Pipeline_CI->m_nuiPipeline_DESC <= nuiVLKN_Pipeline);

    for (uiPipeline = 0; uiPipeline < psVLKN_Pipeline_CI->m_nuiPipeline_DESC; ++uiPipeline)
    {
        STg2_KN_GPU_Compute_Pipeline_CPC    psDefault_Pipeline_DESC = psVLKN_Pipeline_CI->m_psPipeline_DESC + uiPipeline;
        TgRSIZE_C                           uiCS_Index = g_sKN_GPU_CXT_HOST.m_atiCS[uiPipeline].m_uiIndex;

        VkPipeline                          hVLKN_Pipeline;
        VkResult                            eResult;

        /* Default Pipeline Layouts are created prior to pipeline creation. This is a logic/process error. */
        if (VK_NULL_HANDLE == psVLKN_Pipeline_CI->m_phVLKN_Pipeline_Layout[psDefault_Pipeline_DESC->m_uiPipeline_Layout])
        {
            TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Pipeline layout was not created prior to creating a pipeline." );
            continue;
        }

        sCompute_Pipeline_Info.stage.module = psVLKN_Pipeline_CI->m_phVLKN_CS[uiCS_Index];
        sCompute_Pipeline_Info.layout = psVLKN_Pipeline_CI->m_phVLKN_Pipeline_Layout[psDefault_Pipeline_DESC->m_uiPipeline_Layout];

        eResult = vkCreateComputePipelines( psVLKN_Pipeline_CI->m_hVLKN_Device, VK_NULL_HANDLE, 1, &sCompute_Pipeline_Info, g_psKN_GPU_VLKN_Allocator, &hVLKN_Pipeline );
        if (VK_SUCCESS != eResult)
        {
            TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create compute pipeline." );
            ahVLKN_Pipeline[uiPipeline] = VK_NULL_HANDLE;
            continue;
        }
        ahVLKN_Pipeline[uiPipeline] = hVLKN_Pipeline;

        #if defined(TgCOMPILE__GPU_OBJECT_NAME) && TgCOMPILE__GPU_OBJECT_NAME
        {
            TgCHAR_U8                           uszDebugName[KTgKN_RESOURCE_NAME_MAX];
            TgCHAR_U8                           uszMessage[128];

            tgUSZ_PrintF( uszDebugName, sizeof( uszDebugName ), u8"%s", g_asKN_GPU_Compute_Pipeline_For_Rendering[uiPipeline].m_uszName );
            TgMACRO_KN_GPU_VLKN_SET_NAME(psVLKN_Pipeline_CI->m_hVLKN_Device, VK_OBJECT_TYPE_PIPELINE, hVLKN_Pipeline, uszDebugName );

            tgUSZ_PrintF( uszMessage, sizeof(uszMessage), u8"Vulkan Pipeline: %s", uszDebugName );
            tgCN_PrintF( KTgCN_CHANEL_LOADING|KTgCN_SEVERITY_F, STD_MSG_LITERAL_1, STD_MSG_POST, uszMessage );
        }
        /*# defined(TgCOMPILE__GPU_OBJECT_NAME) && TgCOMPILE__GPU_OBJECT_NAME */
        #endif
    }

    return (KTgS_OK);
}


/* ---- tgKN_GPU_VLKN_Create_TST_Descriptor_Set ---------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_VLKN_Create_TST_Descriptor_Set( VkDescriptorSet_PC phVLKN_Descriptor_Set, STg2_KN_GPU_CMD_PC psCMD, VkBuffer hVLKN_UBO )
{
    (void)phVLKN_Descriptor_Set;
    (void)psCMD;
    (void)hVLKN_UBO;
    return (KTgE_FAIL);
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_GPU_VLKN__Execute__Init__Create_Pipeline_Dependencies__Descriptor_Set_Layout ---------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT tgKN_GPU_VLKN__Execute__Init__Create_Pipeline_Dependencies__Descriptor_Set_Layout( VkDevice_C hVLKN_Device, STg2_KN_GPU_VLKN_CXT_EXEC_PC psVLKN_CXT_EXEC )
{
                                        /* ---- Descriptor Layout - Base Descriptor Set Layout ----------------------------------------------------------------------------------- */
    VkDescriptorSetLayoutBinding_C      asVLKN_Default_Layout_Bindings__Base_Shared[] = {
                                            /* Binding KTgMACRO_KN_GPU_VLKN_BINDING_IMMUTABLE_SAMPLERS: Immutable Samplers - Zero CPU overhead */
                                            {
                                                .binding = KTgMACRO_KN_GPU_VLKN_BINDING_IMMUTABLE_SAMPLERS,
                                                .descriptorType = VK_DESCRIPTOR_TYPE_SAMPLER,
                                                .descriptorCount = ETgKN_GPU_DEFAULT_SAMPLER_COUNT,
                                                .stageFlags = VK_SHADER_STAGE_ALL_GRAPHICS,
                                                .pImmutableSamplers = psVLKN_CXT_EXEC->m_ahVLKN_Sampler
                                            },
                                            /* Binding KTgMACRO_KN_GPU_VLKN_BINDING_RENDER_DESC: Render DESC Uniform Buffer */
                                            {
                                                .binding = KTgMACRO_KN_GPU_VLKN_BINDING_RENDER_DESC,
                                                .descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC,
                                                .descriptorCount = 1,
                                                .stageFlags = VK_SHADER_STAGE_ALL,
                                                .pImmutableSamplers = nullptr
                                            },
                                            /* Binding KTgMACRO_KN_GPU_VLKN_BINDING_TX_IMG_IMAGE: Images */
                                            {
                                                .binding = KTgMACRO_KN_GPU_VLKN_BINDING_TX_IMG_IMAGE,
                                                .descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE,
                                                .descriptorCount = KTgKN_GPU_MAX_RENDER_TARGET_IMAGE,
                                                .stageFlags = VK_SHADER_STAGE_COMPUTE_BIT,
                                                .pImmutableSamplers = nullptr
                                            },
                                            /* Binding KTgMACRO_KN_GPU_VLKN_BINDING_TX_IMG: Textures 2D */
                                            {
                                                .binding = KTgMACRO_KN_GPU_VLKN_BINDING_TX_IMG,
                                                .descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
                                                .descriptorCount = KTgKN_GPU_MAX_TX_IMG_INST,
                                                .stageFlags = VK_SHADER_STAGE_ALL_GRAPHICS,
                                                .pImmutableSamplers = nullptr
                                            },
                                            /* Binding KTgMACRO_KN_GPU_VLKN_BINDING_TX_CBE: Texture Cubes */
                                            {
                                                .binding = KTgMACRO_KN_GPU_VLKN_BINDING_TX_CBE,
                                                .descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
                                                .descriptorCount = KTgKN_GPU_MAX_TX_CBE_INST,
                                                .stageFlags = VK_SHADER_STAGE_ALL_GRAPHICS,
                                                .pImmutableSamplers = nullptr
                                            },
                                            /* Binding KTgMACRO_KN_GPU_VLKN_BINDING_TX_VOL: Textures 3D */
                                            {
                                                .binding = KTgMACRO_KN_GPU_VLKN_BINDING_TX_VOL,
                                                .descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
                                                .descriptorCount = KTgKN_GPU_MAX_TX_VOL_INST,
                                                .stageFlags = VK_SHADER_STAGE_ALL_GRAPHICS,
                                                .pImmutableSamplers = nullptr
                                            },
                                        };

    VkDescriptorBindingFlags_C          asVLKN_Default_Layout_Bindings_Flags__Base_Shared[] = {
                                            /* Binding 0: Immutable Samplers - Zero CPU overhead */
                                            0,
                                            /* Binding KTgMACRO_KN_GPU_VLKN_BINDING_RENDER_DESC */
                                            0,
                                            /* Binding KTgMACRO_KN_GPU_VLKN_BINDING_TX_IMG_IMAGE */
                                            VK_DESCRIPTOR_BINDING_PARTIALLY_BOUND_BIT,
                                            /* Binding KTgMACRO_KN_GPU_VLKN_BINDING_TX_IMG */
                                            VK_DESCRIPTOR_BINDING_PARTIALLY_BOUND_BIT,
                                            /* Binding KTgMACRO_KN_GPU_VLKN_BINDING_TX_CBE */
                                            VK_DESCRIPTOR_BINDING_PARTIALLY_BOUND_BIT,
                                            /* Binding KTgMACRO_KN_GPU_VLKN_BINDING_TX_VOL */
                                            VK_DESCRIPTOR_BINDING_PARTIALLY_BOUND_BIT
                                        };

                                        /* ---- Descriptor Layout - Unit Test ---------------------------------------------------------------------------------------------------- */
    VkDescriptorSetLayoutBinding_C      asVLKN_Default_Layout_Bindings__Unit_Test[] = {
                                            /* Binding 1: Per-Draw Instance Data */
                                            {
                                                .binding = KTgMACRO_KN_GPU_VLKN_BINDING_UNIT_TEST_INSTANCE_DATA,
                                                .descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC,
                                                .descriptorCount = 1,
                                                .stageFlags = VK_SHADER_STAGE_ALL_GRAPHICS,
                                                .pImmutableSamplers = nullptr
                                            },
                                            /* Binding 2: Unit Test Scene Data */
                                            {
                                                .binding = KTgMACRO_KN_GPU_VLKN_BINDING_UNIT_TEST_SCENE_DATA,
                                                .descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC,
                                                .descriptorCount = 1,
                                                .stageFlags = VK_SHADER_STAGE_ALL_GRAPHICS,
                                                .pImmutableSamplers = nullptr
                                            }
                                        };

    VkDescriptorBindingFlags_C          asVLKN_Default_Layout_Bindings_Flags__Unit_Test[] = {
                                            /* Binding 1: Per-Draw Instance Data */
                                            0,
                                            /* Binding 2: Unit Test Scene Data */
                                            0,
                                        };

                                        /* ---- Descriptor Layout - Post Process ------------------------------------------------------------------------------------------------- */
    VkDescriptorSetLayoutBinding_C      asVLKN_Default_Layout_Bindings__Post_Process[] = {
                                            /* Binding KTgMACRO_KN_GPU_VLKN_BINDING_LUMINANCE_HISTOGRAM: Luminance Histogram (Legacy) */
                                            {
                                                .binding = KTgMACRO_KN_GPU_VLKN_BINDING_LUMINANCE_HISTOGRAM,
                                                .descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
                                                .descriptorCount = 1,
                                                .stageFlags = VK_SHADER_STAGE_COMPUTE_BIT,
                                                .pImmutableSamplers = nullptr
                                            }
                                        };

    VkDescriptorBindingFlags_C          asVLKN_Default_Layout_Bindings_Flags__Post_Process[] = {
                                            /* Binding KTgMACRO_KN_GPU_VLKN_BINDING_LUMINANCE_HISTOGRAM: Luminance Histogram (Legacy) */
                                            0,
                                        };

                                        /* ---- Descriptor Set Layout List ------------------------------------------------------------------------------------------------------- */

    VkDescriptorSetLayoutBindingFlagsCI_C asVLKN_Default_Descriptor_Set_Layout_Binding_Flags[] = {
                                            {
                                                .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO,
                                                .pNext = nullptr,
                                                .bindingCount  = TgARRAY_COUNT(asVLKN_Default_Layout_Bindings_Flags__Base_Shared),
                                                .pBindingFlags  = asVLKN_Default_Layout_Bindings_Flags__Base_Shared
                                            },
                                            {
                                                .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO,
                                                .pNext = nullptr,
                                                .bindingCount  = TgARRAY_COUNT(asVLKN_Default_Layout_Bindings_Flags__Unit_Test),
                                                .pBindingFlags  = asVLKN_Default_Layout_Bindings_Flags__Unit_Test
                                            },
                                            {
                                                .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO,
                                                .pNext = nullptr,
                                                .bindingCount  = TgARRAY_COUNT(asVLKN_Default_Layout_Bindings_Flags__Post_Process),
                                                .pBindingFlags  = asVLKN_Default_Layout_Bindings_Flags__Post_Process
                                            }
                                        };

                                        /* ---- Descriptor Set Layout List ------------------------------------------------------------------------------------------------------- */

    VkDescriptorSetLayoutCI_C           asVLKN_Default_Descriptor_Set_Layouts[] = {
                                            {
                                                .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
                                                .pNext = asVLKN_Default_Descriptor_Set_Layout_Binding_Flags + 0,
                                                .flags = VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT,
                                                .bindingCount = TgARRAY_COUNT(asVLKN_Default_Layout_Bindings__Base_Shared),
                                                .pBindings = asVLKN_Default_Layout_Bindings__Base_Shared
                                            },
                                            {
                                                .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
                                                .pNext = asVLKN_Default_Descriptor_Set_Layout_Binding_Flags + 1,
                                                .flags = VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT,
                                                .bindingCount = TgARRAY_COUNT(asVLKN_Default_Layout_Bindings__Unit_Test),
                                                .pBindings = asVLKN_Default_Layout_Bindings__Unit_Test
                                            },
                                            {
                                                .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
                                                .pNext = asVLKN_Default_Descriptor_Set_Layout_Binding_Flags + 2,
                                                .flags = VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT,
                                                .bindingCount = TgARRAY_COUNT(asVLKN_Default_Layout_Bindings__Post_Process),
                                                .pBindings = asVLKN_Default_Layout_Bindings__Post_Process
                                            }
                                        };

    TgCOMPILER_ASSERT( ETgKN_GPU_VLKN_DESCRIPTOR_SET_LAYOUT__BASE_SHARED == 0, 0 );
    TgCOMPILER_ASSERT( ETgKN_GPU_VLKN_DESCRIPTOR_SET_LAYOUT__UNIT_TEST == 1, 0 );
    TgCOMPILER_ASSERT( ETgKN_GPU_VLKN_DESCRIPTOR_SET_LAYOUT__POST_PROCESS_COMPUTE == 2, 0 );

    TgRSIZE                             uiIndex;
    VkResult                            eResult;

    for (uiIndex = 0; uiIndex < TgARRAY_COUNT(asVLKN_Default_Descriptor_Set_Layouts); ++uiIndex)
    {
        VkDescriptorSetLayout               hVLKN_Descriptor_Set_Layout;

        eResult = vkCreateDescriptorSetLayout(hVLKN_Device, asVLKN_Default_Descriptor_Set_Layouts + uiIndex, g_psKN_GPU_VLKN_Allocator, &hVLKN_Descriptor_Set_Layout);
        if (eResult != VK_SUCCESS)
        {
            TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create descriptor set layout" );
            return (KTgE_FAIL);
        }
        
        /* Store in the context for later use */
        psVLKN_CXT_EXEC->m_ahVLKN_Descriptor_Set_Layout[uiIndex] = hVLKN_Descriptor_Set_Layout;
    }

    return (KTgS_OK);
}


/* ---- tgKN_GPU_VLKN__Execute__Init__Create_Pipeline_Dependencies_Pipeline_Layout ----------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT tgKN_GPU_VLKN__Execute__Init__Create_Pipeline_Dependencies_Pipeline_Layout( VkDevice_C hVLKN_Device, STg2_KN_GPU_VLKN_CXT_EXEC_PC psVLKN_CXT_EXEC )
{
                                        /* ---- Push Constants - Unit Test ------------------------------------------------------------------------------------------------------- */

                                        /* Push constants for ultra-high frequency data - Zero CPU allocation overhead */
    VkPushConstantRange_C               asVLKN_Default_Push_Constant_Ranges__Unit_Test[] = {
                                            {
                                                .stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT,
                                                .offset = 0,
                                                .size = 128
                                            }
                                        };

                                        /* Push constants for ultra-high frequency data - Zero CPU allocation overhead */
    VkPushConstantRange_C               asVLKN_Default_Push_Constant_Ranges__Post_Process_Compute[] = {
                                            {
                                                .stageFlags = VK_SHADER_STAGE_COMPUTE_BIT,
                                                .offset = 0,
                                                .size = 128
                                            }
                                        };

                                        /* --------------------------------------------------------------------------------------------------------------------------------------- */

    VkDescriptorSetLayout               asVLKN_Descriptor_Set_Layouts__Unit_Test[] = {
                                            psVLKN_CXT_EXEC->m_ahVLKN_Descriptor_Set_Layout[ETgKN_GPU_VLKN_DESCRIPTOR_SET_LAYOUT__BASE_SHARED],  /* Set 0: Base Shared */
                                            psVLKN_CXT_EXEC->m_ahVLKN_Descriptor_Set_Layout[ETgKN_GPU_VLKN_DESCRIPTOR_SET_LAYOUT__UNIT_TEST],    /* Set 1: Unit Test */
                                        };

    VkDescriptorSetLayout               asVLKN_Descriptor_Set_Layouts__Post_Process_Compute[] = {
                                            psVLKN_CXT_EXEC->m_ahVLKN_Descriptor_Set_Layout[ETgKN_GPU_VLKN_DESCRIPTOR_SET_LAYOUT__BASE_SHARED],  /* Set 0: Base Shared */
                                            psVLKN_CXT_EXEC->m_ahVLKN_Descriptor_Set_Layout[ETgKN_GPU_VLKN_DESCRIPTOR_SET_LAYOUT__POST_PROCESS_COMPUTE],  /* Set 1: Post Process */
                                        };

    VkPipelineLayoutCI_C                asVLKN_Default_Graphics_Pipeline_Layout[] = {
                                            {   /* Unit Test - ETgKN_GPU_PIPELINE_LAYOUT__UNIT_TEST */
                                                .sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
                                                .pNext = nullptr,
                                                .flags = 0,
                                                .setLayoutCount = TgARRAY_COUNT(asVLKN_Descriptor_Set_Layouts__Unit_Test),
                                                .pSetLayouts = asVLKN_Descriptor_Set_Layouts__Unit_Test,
                                                .pushConstantRangeCount = TgARRAY_COUNT(asVLKN_Default_Push_Constant_Ranges__Unit_Test),
                                                .pPushConstantRanges = asVLKN_Default_Push_Constant_Ranges__Unit_Test,
                                            },

                                            {   /* ETgKN_GPU_PIPELINE_LAYOUT__POST_PROCESS_COMPUTE */
                                                .sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
                                                .pNext = nullptr,
                                                .flags = 0,
                                                .setLayoutCount = TgARRAY_COUNT(asVLKN_Descriptor_Set_Layouts__Post_Process_Compute),
                                                .pSetLayouts = asVLKN_Descriptor_Set_Layouts__Post_Process_Compute,
                                                .pushConstantRangeCount = TgARRAY_COUNT(asVLKN_Default_Push_Constant_Ranges__Post_Process_Compute),
                                                .pPushConstantRanges = asVLKN_Default_Push_Constant_Ranges__Post_Process_Compute,
                                            }
                                        };

    TgCOMPILER_ASSERT( ETgKN_GPU_PIPELINE_LAYOUT__UNIT_TEST == 0, 0 );
    TgCOMPILER_ASSERT( ETgKN_GPU_PIPELINE_LAYOUT__POST_PROCESS_COMPUTE == 1, 0 );

    TgRSIZE                             uiIndex;
    VkResult                            eResult;

    for (uiIndex = 0; uiIndex < TgARRAY_COUNT(asVLKN_Default_Graphics_Pipeline_Layout); ++uiIndex)
    {
        VkPipelineLayout                    hVLKN_Pipeline_Layout;

        eResult = vkCreatePipelineLayout(hVLKN_Device, asVLKN_Default_Graphics_Pipeline_Layout + uiIndex, g_psKN_GPU_VLKN_Allocator, &hVLKN_Pipeline_Layout);
        if (eResult != VK_SUCCESS)
        {
            TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Vulkan Error" );
            return (KTgE_FAIL);
        }

        /* Store in the context for later use */
        psVLKN_CXT_EXEC->m_ahVLKN_Pipeline_Layout[uiIndex] = hVLKN_Pipeline_Layout;
    }

    TgMACRO_KN_GPU_VLKN_SET_NAME_FROM_ENUM(hVLKN_Device, VK_OBJECT_TYPE_PIPELINE_LAYOUT, psVLKN_CXT_EXEC->m_ahVLKN_Pipeline_Layout[0], ETgKN_GPU_PIPELINE_LAYOUT__UNIT_TEST)
    TgMACRO_KN_GPU_VLKN_SET_NAME_FROM_ENUM(
        hVLKN_Device, VK_OBJECT_TYPE_PIPELINE_LAYOUT, psVLKN_CXT_EXEC->m_ahVLKN_Pipeline_Layout[1], ETgKN_GPU_PIPELINE_LAYOUT__POST_PROCESS_COMPUTE)

    return (KTgS_OK);
}
