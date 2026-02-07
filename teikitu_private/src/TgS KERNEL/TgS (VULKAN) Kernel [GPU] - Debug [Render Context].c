/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (VULKAN) Kernel [GPU] - Debug [Pipeline].c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.22 | »GUID« 7ECEAB43-40E4-4161-8F94-87AF31F5BA9A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    Models:     Claude 3.7 - 4.5
    ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)

TgCLANG_WARN_DISABLE_PUSH(missing-variable-declarations)
TgMSVC_WARN_DISABLE_PUSH(5103)
#include "Default_VLKN_DBG_S_VW_vert.glsl.h"
#include "Default_VLKN_DBG_SC_VWC_vert.glsl.h"
#include "Default_VLKN_DBG_SN_VWNC_vert.glsl.h"
#include "Default_VLKN_DBG_SNC_VWNC_vert.glsl.h"
#include "Default_VLKN_DBG_UI_SUC_UC_vert.glsl.h"
#include "Default_VLKN_DBG_Text_SU_U_vert.glsl.h"
#include "Default_VLKN_DBG_SN_VWNC_I_vert.glsl.h"
#include "Default_VLKN_DBG_Line_task.glsl.h"
#include "Default_VLKN_DBG_Line_mesh.glsl.h"
#include "Default_VLKN_DBG_Line_frag.glsl.h"
#include "Default_VLKN_DBG_VW_frag.glsl.h"
#include "Default_VLKN_DBG_VWC_00_frag.glsl.h"
#include "Default_VLKN_DBG_VWC_01_frag.glsl.h"
#include "Default_VLKN_DBG_VWNC_frag.glsl.h"
#include "Default_VLKN_DBG_UC_00_frag.glsl.h"
#include "Default_VLKN_DBG_UC_01_frag.glsl.h"
#include "Default_VLKN_DBG_Text_U_frag.glsl.h"
TgMSVC_WARN_DISABLE_POP(5103)
TgCLANG_WARN_DISABLE_POP(missing-variable-declarations)


/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */


/** @brief Create debug default vertex, index, storage, and uniform buffers
    @param [in] ARG0 Device handle
    @param [in] ARG1 Vulkan Command pointer
    @param [in] ARG2 Vulkan Debug context pointer
    @return Result Code. */
static TgRESULT
tgKN_GPU_VLKN__Execute__Init_Debug__Create_Resources__Buffers(
    VkDevice_C ARG0, STg2_KN_GPU_VLKN_CMD_PC TgANALYSIS_NO_NULL ARG1, STg2_KN_GPU_DBG_VLKN_CXT_EXEC_PC TgANALYSIS_NO_NULL ARG2 );

/** @brief Create default descriptor set layouts
    @param [in] ARG0 Device handle
    @param [in] ARG1 Vulkan Debug context pointer
    @return Result Code. */
static TgRESULT
tgKN_GPU_VLKN__Execute__Init_Debug__Create_Resources__Descriptor_Set_Layout(
    VkDevice_C ARG0, STg2_KN_GPU_DBG_VLKN_CXT_EXEC_PC TgANALYSIS_NO_NULL ARG1 );

/** @brief Create default pipeline layouts
    @param [in] ARG0 Device handle
    @param [in] ARG1 Vulkan Debug context pointer
    @param [in] ARG2 Vulkan Execution context pointer
    @return Result Code. */
static TgRESULT
tgKN_GPU_VLKN__Execute__Init_Debug__Create_Resources__Pipeline_Layout(
    VkDevice_C ARG0, STg2_KN_GPU_DBG_VLKN_CXT_EXEC_PC TgANALYSIS_NO_NULL ARG1, STg2_KN_GPU_VLKN_CXT_EXEC_PC TgANALYSIS_NO_NULL ARG2 );

/** @brief Create default command pools
    @param [in] ARG0 Device handle
    @param [in] ARG1 Vulkan Debug context pointer
    @return Result Code. */
static TgRESULT
tgKN_GPU_VLKN__Execute__Init_Debug__Create_Default_Command_Pool(
    VkDevice_C ARG0,  STg2_KN_GPU_DBG_VLKN_CXT_EXEC_PC TgANALYSIS_NO_NULL ARG1 );

/** @brief Create default descriptor set layouts
    @param [in] ARG0 Device handle
    @param [in] ARG1 Vulkan Debug context pointer
    @return Result Code. */
static TgRESULT
tgKN_GPU_VLKN__Execute__Init_Debug__Create_Resources__Descriptor_Set(
    VkDevice_C ARG0, STg2_KN_GPU_DBG_VLKN_CXT_EXEC_PC TgANALYSIS_NO_NULL ARG1 );

/** @brief Destroy buffers created in tgKN_GPU_VLKN__Execute__Init_Debug__Create_Resources__Buffers
    @param [in] ARG0 Device handle
    @param [in] ARG1 Vulkan Debug context pointer */
static TgVOID
tgKN_GPU_VLKN__Execute__Init_Debug__Destroy_Resources__Buffers(
    VkDevice_C ARG0, STg2_KN_GPU_DBG_VLKN_CXT_EXEC_PC ARG1 );

/** @brief Create graphics pipelines for a render target
    @param [in] ARG0 Pointer to the render target
    @param [in] ARG1 Device handle 
    @param [in] ARG2 Index of the execution context
    @param [in] ARG3 Pointer to the standard render target
    @return Result Code. */
static TgRESULT
tgKN_GPU_VLKN__Render_Target_Debug__Create_Pipelines(
    STg2_KN_GPU_DBG_VLKN_Render_Target_PC ARG0, VkDevice_C ARG1, TgRSIZE_C ARG2, STg2_KN_GPU_VLKN_Render_Target_PC ARG3 );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Code Macros                                                                                                                                                                    */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

#define _MACRO_LOAD_SHADER(A,B,C,D) \
{ \
    STg2_KN_GPU_##C##_DESC s##C##_DESC; \
    TgVERIFY(g_sKN_GPU_DBG_CXT_HOST.m_nui##C == (TgRSIZE)B); \
    s##C##_DESC.m_puiData = (TgUINT_E08_CP)g_uiDefault_VLKN_##A##_Compiled; \
    s##C##_DESC.m_nuiData = sizeof(g_uiDefault_VLKN_##A##_Compiled); \
    s##C##_DESC.m_uszName = u8##D; \
    g_sKN_GPU_DBG_CXT_HOST.m_ati##C[g_sKN_GPU_DBG_CXT_HOST.m_nui##C++] = tgKN_GPU_##C##__Load_From_Memory( & s##C##_DESC, ETgKN_GPU_RESOURCE_DESCRIPTOR__MAIN_MEMORY ); \
}

#define MACRO_LOAD_SHADER(A,B,C)        _MACRO_LOAD_SHADER(A,B,C,#B)

#define MACRO_LOAD_SHADER_VS(A,B)       MACRO_LOAD_SHADER(A,B,VS)
#define MACRO_LOAD_SHADER_TS(A,B)       MACRO_LOAD_SHADER(A,B,TS)
#define MACRO_LOAD_SHADER_MS(A,B)       MACRO_LOAD_SHADER(A,B,MS)
#define MACRO_LOAD_SHADER_FS(A,B)       MACRO_LOAD_SHADER(A,B,FS)

#define KTgMACRO_KN_GPU_VLKN__Execute__Init__Create_Pipeline_Dependencies_Create_Shader_Module(A)                                                                                   \
    for (uiIndex = 0; uiIndex < TgARRAY_COUNT(g_sKN_GPU_DBG_CXT_HOST.m_ati##A); ++uiIndex)                                                                                          \
    {                                                                                                                                                                               \
        if (0 != g_sKN_GPU_DBG_CXT_HOST.m_ati##A[uiIndex].m_uiKI)                                                                                                                   \
        {                                                                                                                                                                           \
            TgRSIZE_C                           ui##A##_Index = g_sKN_GPU_DBG_CXT_HOST.m_ati##A[uiIndex].m_uiIndex;                                                                 \
            STg2_KN_GPU_SH_DATA_CPC             ps##A##_SH  = &g_asKN_Lib_##A##_Data[ui##A##_Index].m_sSH;                                                                          \
                                                                                                                                                                                    \
            if ((0 != ps##A##_SH->m_nuiData) && (VK_NULL_HANDLE == psDBG_VLKN_CXT_EXEC->m_ahVLKN_##A[uiIndex]))                                                                     \
            {                                                                                                                                                                       \
                if (TgFAILED(tgKN_GPU_VLKN_Create_Shader_Module(psDBG_VLKN_CXT_EXEC->m_ahVLKN_##A + uiIndex, uCMD.psVLKN->m_hVLKN_Device, ps##A##_SH->m_puiConstData,               \
                                                                ps##A##_SH->m_nuiData)))                                                                                            \
                {                                                                                                                                                                   \
                    TgERROR_MSG( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create shader module." );                                                                         \
                    return (KTgE_FAIL);                                                                                                                                             \
                }                                                                                                                                                                   \
            }                                                                                                                                                                       \
        }                                                                                                                                                                           \
    }

#define KTgMACRO_KN_GPU_VLKN__Execute__Free__Destroy_Default_Pipeline_Dependencies_Create_Shader_Module(A)                                                                          \
    for (uiIndex = 0; uiIndex < TgARRAY_COUNT(psDBG_VLKN_CXT_EXEC->m_ahVLKN_##A); ++uiIndex)                                                                                        \
    {                                                                                                                                                                               \
        if (VK_NULL_HANDLE != psDBG_VLKN_CXT_EXEC->m_ahVLKN_##A[uiIndex])                                                                                                           \
        {                                                                                                                                                                           \
            vkDestroyShaderModule(hVLKN_Device, psDBG_VLKN_CXT_EXEC->m_ahVLKN_##A[uiIndex], g_psKN_GPU_VLKN_Allocator);                                                             \
            psDBG_VLKN_CXT_EXEC->m_ahVLKN_##A[uiIndex] = VK_NULL_HANDLE;                                                                                                            \
        }                                                                                                                                                                           \
    }




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_GPU_EXT__Host__Init_Debug ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_EXT__Host__Init_Debug( TgVOID )
{
    MACRO_LOAD_SHADER_VS( DBG_S_VW_VERT, ETgKN_GPU_DBG_SHADER_VS_VERTEX_GEOM_S_VW )
    MACRO_LOAD_SHADER_VS( DBG_SC_VWC_VERT, ETgKN_GPU_DBG_SHADER_VS_VERTEX_GEOM_SC_VWC )
    MACRO_LOAD_SHADER_VS( DBG_SN_VWNC_VERT, ETgKN_GPU_DBG_SHADER_VS_VERTEX_GEOM_SN_VWNC )
    MACRO_LOAD_SHADER_VS( DBG_SNC_VWNC_VERT, ETgKN_GPU_DBG_SHADER_VS_VERTEX_GEOM_SNC_VWNC )
    MACRO_LOAD_SHADER_VS( DBG_UI_SUC_UC_VERT, ETgKN_GPU_DBG_SHADER_VS_VERTEX_UI_SUC_UC )
    MACRO_LOAD_SHADER_VS( DBG_Text_SU_U_VERT, ETgKN_GPU_DBG_SHADER_VS_VERTEX_TEXT_SU_U )
    MACRO_LOAD_SHADER_VS( DBG_SN_VWNC_I_VERT, ETgKN_GPU_DBG_SHADER_VS_VERTEX_GEOM_SN_VWNC_I )

    MACRO_LOAD_SHADER_TS( DBG_Line_TASK, ETgKN_GPU_DBG_SHADER_TS_LINE )

    MACRO_LOAD_SHADER_MS( DBG_Line_MESH, ETgKN_GPU_DBG_SHADER_MS_LINE )

    MACRO_LOAD_SHADER_FS( DBG_Line_FRAG, ETgKN_GPU_DBG_SHADER_FS_LINE )
    MACRO_LOAD_SHADER_FS( DBG_VW_FRAG, ETgKN_GPU_DBG_SHADER_FS_VW )
    MACRO_LOAD_SHADER_FS( DBG_VWC_00_FRAG, ETgKN_GPU_DBG_SHADER_FS_VWC_00 )
    MACRO_LOAD_SHADER_FS( DBG_VWC_01_FRAG, ETgKN_GPU_DBG_SHADER_FS_VWC_01 )
    MACRO_LOAD_SHADER_FS( DBG_VWNC_FRAG, ETgKN_GPU_DBG_SHADER_FS_VWNC )
    MACRO_LOAD_SHADER_FS( DBG_UC_00_FRAG, ETgKN_GPU_DBG_SHADER_FS_UC_00 )
    MACRO_LOAD_SHADER_FS( DBG_UC_01_FRAG, ETgKN_GPU_DBG_SHADER_FS_UC_01 )
    MACRO_LOAD_SHADER_FS( DBG_Text_U_FRAG, ETgKN_GPU_DBG_SHADER_FS_TEXT_U )

    return (KTgS_OK);
}


/* ---- tgKN_GPU_EXT__Host__Free_Debug ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_EXT__Host__Free_Debug( TgVOID )
{
}


/* ---- tgKN_GPU_EXT__Execute__Init_Debug ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_EXT__Execute__Init_Debug( TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC )
{
    STg2_KN_GPU_VLKN_CXT_EXEC_PC        psVLKN_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + tiCXT_EXEC.m_uiI;
    STg2_KN_GPU_DBG_VLKN_CXT_EXEC_PC    psDBG_VLKN_CXT_EXEC = g_asKN_GPU_DBG_EXT_CXT_EXEC + tiCXT_EXEC.m_uiI;

    TgPARAM_CHECK_INDEX( tiCXT_EXEC.m_uiI, g_asKN_GPU_CXT_EXEC );
    TgPARAM_CHECK( tgKN_GPU_CXT_EXEC_ID_Is_Equal( &(g_asKN_GPU_CXT_EXEC[tiCXT_EXEC.m_uiI].m_tiCXT_EXEC_S), tiCXT_EXEC ) );

    tgMM_Set_U08_0x00(psDBG_VLKN_CXT_EXEC, sizeof(STg2_KN_GPU_DBG_VLKN_CXT_EXEC) );

    psDBG_VLKN_CXT_EXEC->m_idxCXT_HOST_Physical_Device = psVLKN_CXT_EXEC->m_idxCXT_HOST_Physical_Device;
    psDBG_VLKN_CXT_EXEC->m_hVLKN_Physical_Device = psVLKN_CXT_EXEC->m_hVLKN_Physical_Device;
    psDBG_VLKN_CXT_EXEC->m_hVLKN_Device = psVLKN_CXT_EXEC->m_hVLKN_Device;

    return (KTgS_OK);
}


/* ---- tgKN_GPU_EXT__Execute__Init_Debug__Create_Resources ---------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_EXT__Execute__Init_Debug__Create_Resources( STg2_KN_GPU_CMD_PC psCMD )
{
    UTg2_KN_GPU_CMD_C                           uCMD = { .ps = psCMD };
    TgRSIZE                             uiEXEC = (uCMD.psVLKN->m_sBase.m_tiCXT_WORK.m_uiI >> 16) & 0xFFFF;
    STg2_KN_GPU_DBG_VLKN_CXT_EXEC_PC    psDBG_VLKN_CXT_EXEC = g_asKN_GPU_DBG_EXT_CXT_EXEC + uiEXEC;
    STg2_KN_GPU_VLKN_CXT_EXEC_PC        psVLKN_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + uiEXEC;

    TgRSIZE                             uiIndex;

    TgPARAM_CHECK_KN_GPU_CMD( psCMD );

    if (TgFAILED(tgKN_GPU_VLKN__Execute__Init_Debug__Create_Resources__Buffers( uCMD.psVLKN->m_hVLKN_Device, uCMD.psVLKN, psDBG_VLKN_CXT_EXEC )))
    {
       TgERROR_MSG( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create debug buffers." );
        return (KTgE_FAIL);
    }

    if (TgFAILED(tgKN_GPU_VLKN__Execute__Init_Debug__Create_Resources__Descriptor_Set_Layout(uCMD.psVLKN->m_hVLKN_Device, psDBG_VLKN_CXT_EXEC )))
    {
       TgERROR_MSG( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create debug descriptor set layout." );
        return (KTgE_FAIL);
    }

    if (TgFAILED(tgKN_GPU_VLKN__Execute__Init_Debug__Create_Resources__Pipeline_Layout(uCMD.psVLKN->m_hVLKN_Device, psDBG_VLKN_CXT_EXEC, psVLKN_CXT_EXEC )))
    {
       TgERROR_MSG( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create debug pipeline layout." );
        return (KTgE_FAIL);
    }

    if (TgFAILED(tgKN_GPU_VLKN__Execute__Init_Debug__Create_Default_Command_Pool( uCMD.psVLKN->m_hVLKN_Device, psDBG_VLKN_CXT_EXEC )))
    {
        TgERROR_MSG(0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create debug descriptor pool.");
        return (KTgE_FAIL);
    }

    if (TgFAILED(tgKN_GPU_VLKN__Execute__Init_Debug__Create_Resources__Descriptor_Set(uCMD.psVLKN->m_hVLKN_Device, psDBG_VLKN_CXT_EXEC )))
    {
       TgERROR_MSG( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create debug descriptor sets." );
        return (KTgE_FAIL);
    }

    /* Create shaders */
    KTgMACRO_KN_GPU_VLKN__Execute__Init__Create_Pipeline_Dependencies_Create_Shader_Module(VS)
    KTgMACRO_KN_GPU_VLKN__Execute__Init__Create_Pipeline_Dependencies_Create_Shader_Module(TS)
    KTgMACRO_KN_GPU_VLKN__Execute__Init__Create_Pipeline_Dependencies_Create_Shader_Module(MS)
    KTgMACRO_KN_GPU_VLKN__Execute__Init__Create_Pipeline_Dependencies_Create_Shader_Module(FS)

    return (KTgS_OK);
}


/* ---- tgKN_GPU_EXT__Execute__Free_Debug ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_EXT__Execute__Free_Debug( TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC )
{
    (TgVOID)tiCXT_EXEC;
}


/* ---- tgKN_GPU_EXT__Execute__Free_Debug__Destroy_Resources --------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_EXT__Execute__Free_Debug__Destroy_Resources( STg2_KN_GPU_CMD_PC psCMD )
{
    UTg2_KN_GPU_CMD_C                           uCMD = { .ps = psCMD };
    TgRSIZE                             uiEXEC = (uCMD.psVLKN->m_sBase.m_tiCXT_WORK.m_uiI >> 16) & 0xFFFF;
    STg2_KN_GPU_DBG_VLKN_CXT_EXEC_PC    psDBG_VLKN_CXT_EXEC = g_asKN_GPU_DBG_EXT_CXT_EXEC + uiEXEC;

    VkDevice                            hVLKN_Device;
    TgRSIZE                             uiIndex;

    TgPARAM_CHECK_KN_GPU_CMD( psCMD );

    hVLKN_Device = psDBG_VLKN_CXT_EXEC->m_hVLKN_Device;

    /* Destroy shaders */
    KTgMACRO_KN_GPU_VLKN__Execute__Free__Destroy_Default_Pipeline_Dependencies_Create_Shader_Module(VS)
    KTgMACRO_KN_GPU_VLKN__Execute__Free__Destroy_Default_Pipeline_Dependencies_Create_Shader_Module(TS)
    KTgMACRO_KN_GPU_VLKN__Execute__Free__Destroy_Default_Pipeline_Dependencies_Create_Shader_Module(MS)
    KTgMACRO_KN_GPU_VLKN__Execute__Free__Destroy_Default_Pipeline_Dependencies_Create_Shader_Module(FS)

    if (psDBG_VLKN_CXT_EXEC->m_hVLKN_DBG_Descriptor_Set__Text)
    {
        vkFreeDescriptorSets(hVLKN_Device, psDBG_VLKN_CXT_EXEC->m_hVLKN_Descriptor_Pool, 1, &psDBG_VLKN_CXT_EXEC->m_hVLKN_DBG_Descriptor_Set__Text);
        psDBG_VLKN_CXT_EXEC->m_hVLKN_DBG_Descriptor_Set__Text = VK_NULL_HANDLE;
    }

    if (psDBG_VLKN_CXT_EXEC->m_hVLKN_DBG_Descriptor_Set__Line_Task_Mesh)
    {
        vkFreeDescriptorSets(hVLKN_Device, psDBG_VLKN_CXT_EXEC->m_hVLKN_Descriptor_Pool, 1, &psDBG_VLKN_CXT_EXEC->m_hVLKN_DBG_Descriptor_Set__Line_Task_Mesh);
        psDBG_VLKN_CXT_EXEC->m_hVLKN_DBG_Descriptor_Set__Line_Task_Mesh = VK_NULL_HANDLE;
    }

    if (psDBG_VLKN_CXT_EXEC->m_hVLKN_DBG_Descriptor_Set__Geom)
    {
        vkFreeDescriptorSets(hVLKN_Device, psDBG_VLKN_CXT_EXEC->m_hVLKN_Descriptor_Pool, 1, &psDBG_VLKN_CXT_EXEC->m_hVLKN_DBG_Descriptor_Set__Geom);
        psDBG_VLKN_CXT_EXEC->m_hVLKN_DBG_Descriptor_Set__Geom = VK_NULL_HANDLE;
    }    if (VK_NULL_HANDLE != psDBG_VLKN_CXT_EXEC->m_hVLKN_Descriptor_Pool)
    {
        vkDestroyDescriptorPool(hVLKN_Device, psDBG_VLKN_CXT_EXEC->m_hVLKN_Descriptor_Pool, g_psKN_GPU_VLKN_Allocator);
        psDBG_VLKN_CXT_EXEC->m_hVLKN_Descriptor_Pool = VK_NULL_HANDLE;
    }

    for (uiIndex = 0; uiIndex < TgARRAY_COUNT(psDBG_VLKN_CXT_EXEC->m_ahVLKN_Pipeline_Layout); ++uiIndex)
    {
        if (VK_NULL_HANDLE == psDBG_VLKN_CXT_EXEC->m_ahVLKN_Pipeline_Layout[uiIndex])
            continue;
        vkDestroyPipelineLayout(hVLKN_Device, psDBG_VLKN_CXT_EXEC->m_ahVLKN_Pipeline_Layout[uiIndex], g_psKN_GPU_VLKN_Allocator);
        psDBG_VLKN_CXT_EXEC->m_ahVLKN_Pipeline_Layout[uiIndex] = VK_NULL_HANDLE;
    }

    for (uiIndex = 0; uiIndex < TgARRAY_COUNT(psDBG_VLKN_CXT_EXEC->m_ahVLKN_Descriptor_Set_Layout); ++uiIndex)
    {
        if (VK_NULL_HANDLE == psDBG_VLKN_CXT_EXEC->m_ahVLKN_Descriptor_Set_Layout[uiIndex])
            continue;
        vkDestroyDescriptorSetLayout(hVLKN_Device, psDBG_VLKN_CXT_EXEC->m_ahVLKN_Descriptor_Set_Layout[uiIndex], g_psKN_GPU_VLKN_Allocator);
        psDBG_VLKN_CXT_EXEC->m_ahVLKN_Descriptor_Set_Layout[uiIndex] = VK_NULL_HANDLE;
    }

    tgKN_GPU_VLKN__Execute__Init_Debug__Destroy_Resources__Buffers( psDBG_VLKN_CXT_EXEC->m_hVLKN_Device, psDBG_VLKN_CXT_EXEC );
}


/* ---- tgKN_GPU_EXT__Swap__Init_Debug ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_EXT__Swap__Init_Debug( TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP )
{
    TgPARAM_CHECK_INDEX( tiCXT_SWAP.m_uiI, g_asKN_GPU_CXT_SWAP );
    TgPARAM_CHECK( tgKN_GPU_CXT_SWAP_ID_Is_Equal( &(g_asKN_GPU_CXT_SWAP[tiCXT_SWAP.m_uiI].m_tiCXT_SWAP_S), tiCXT_SWAP ) );

    {
        STg2_KN_GPU_DBG_VLKN_CXT_SWAP_PC    psVLKN_DBG_CXT_SWAP = g_asKN_GPU_DBG_EXT_CXT_SWAP + tiCXT_SWAP.m_uiI;
        STg2_KN_GPU_VLKN_CXT_SWAP_PC        psVLKN_CXT_SWAP = g_asKN_GPU_EXT_CXT_SWAP + tiCXT_SWAP.m_uiI;
        STg2_KN_GPU_VLKN_Render_Target_PC   psRender_Target = psVLKN_CXT_SWAP->m_asBack_Buffer__Render_Target;
        STg2_KN_GPU_CXT_SWAP_PC             psCXT_SWAP = g_asKN_GPU_CXT_SWAP + tiCXT_SWAP.m_uiI;
        TgRSIZE_C                           uiEXEC = psCXT_SWAP->m_tiCXT_EXEC.m_uiI;
        STg2_KN_GPU_VLKN_CXT_EXEC_PC        psVLKN_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + uiEXEC;

        tgMM_Set_U08_0x00(psVLKN_DBG_CXT_SWAP, sizeof( STg2_KN_GPU_DBG_VLKN_CXT_SWAP ) );

        if (TgFAILED(tgKN_GPU_DBG_VLKN__Render_Target__Init( &psVLKN_DBG_CXT_SWAP->m_sDBG_Back_Buffer__Render_Target, psRender_Target, psVLKN_CXT_EXEC->m_hVLKN_Device, uiEXEC )))
        {
            TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to begin rendering for render target" );
        }
    }

    return (KTgS_OK);
}


/* ---- tgKN_GPU_EXT__Swap__Free_Debug ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_EXT__Swap__Free_Debug( TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP )
{
    TgPARAM_CHECK_INDEX( tiCXT_SWAP.m_uiI, g_asKN_GPU_CXT_SWAP );
    TgPARAM_CHECK( tgKN_GPU_CXT_SWAP_ID_Is_Equal( &(g_asKN_GPU_CXT_SWAP[tiCXT_SWAP.m_uiI].m_tiCXT_SWAP_S), tiCXT_SWAP ) );

    {
        STg2_KN_GPU_DBG_VLKN_CXT_SWAP_PC    psVLKN_DBG_CXT_SWAP = g_asKN_GPU_DBG_EXT_CXT_SWAP + tiCXT_SWAP.m_uiI;
        STg2_KN_GPU_CXT_SWAP_PC             psCXT_SWAP = g_asKN_GPU_CXT_SWAP + tiCXT_SWAP.m_uiI;
        TgRSIZE_C                           uiEXEC = psCXT_SWAP->m_tiCXT_EXEC.m_uiI;
        STg2_KN_GPU_VLKN_CXT_EXEC_PC        psVLKN_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + uiEXEC;

        tgKN_GPU_DBG_VLKN__Render_Target__Free( &psVLKN_DBG_CXT_SWAP->m_sDBG_Back_Buffer__Render_Target, psVLKN_CXT_EXEC->m_hVLKN_Device );
    }
}


/* ---- tgKN_GPU_EXT__CMD__Command_Debug ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_EXT__CMD__Command_Debug(
    STg2_KN_GPU_CMD_DBG_PP                      ppCMD_DBG,
    STg2_KN_GPU_CMD_PC                          psCMD )
{
    UTg2_KN_GPU_CMD_C                           uCMD = { .ps = psCMD };
    TgRSIZE_C                                   uiEXEC = (uCMD.psVLKN->m_sBase.m_tiCXT_WORK.m_uiI >> 16) & 0xFFFF;
    STg2_KN_GPU_VLKN_CXT_EXEC_PC                psVLKN_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + uiEXEC;
    STg2_KN_GPU_DBG_VLKN_CXT_EXEC_PC            psDBG_VLKN_CXT_EXEC = g_asKN_GPU_DBG_EXT_CXT_EXEC + uiEXEC;
    TgSINT_PTR_C                                iCmd_Index = uCMD.psVLKN - psVLKN_CXT_EXEC->m_asCommand;

    *ppCMD_DBG = &psDBG_VLKN_CXT_EXEC->m_asComand_DBG[iCmd_Index].m_sCMD_DBG;
    return (KTgS_OK);
}


/* ---- tgKN_GPU_VLKN__CMD__Frame_Start_Debug ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_VLKN__CMD__Frame_Start_Debug( STg2_KN_GPU_VLKN_CXT_CMD_PC psVLKN_CXT_CMD, TgRSIZE_C uiContext_Command_Index )
{
    STg2_KN_GPU_DBG_VLKN_CXT_EXEC_PC    psDBG_VLKN_CXT_EXEC = g_asKN_GPU_DBG_EXT_CXT_EXEC + psVLKN_CXT_CMD->m_tiCXT_EXEC.m_uiI;
    STg2_KN_GPU_DBG_VLKN_CXT_CMD_PC     psVLKN_DBG_CXT_CMD = psDBG_VLKN_CXT_EXEC->m_asContext_Command_DBG + uiContext_Command_Index;
    TgRSIZE                             nbyFrame;

    nbyFrame = psDBG_VLKN_CXT_EXEC->m_sSBO__Text.m_uiSBO_Elements_Per_Frame * psDBG_VLKN_CXT_EXEC->m_sSBO__Text.m_uiAligned_SBO_Size_Element;
    TgSTD_ATOMIC(store)( &psVLKN_DBG_CXT_CMD->m_xuiSBO__Text_Offset, uiContext_Command_Index * nbyFrame );
    psVLKN_DBG_CXT_CMD->m_uiSBO__Text_End = (uiContext_Command_Index + 1) * nbyFrame;

    nbyFrame = psDBG_VLKN_CXT_EXEC->m_sSBO__Line__Input_Lines.m_uiSBO_Elements_Per_Frame * psDBG_VLKN_CXT_EXEC->m_sSBO__Line__Input_Lines.m_uiAligned_SBO_Size_Element;
    TgSTD_ATOMIC(store)( &psVLKN_DBG_CXT_CMD->m_xuiSBO__Line__Input_Lines_Offset, uiContext_Command_Index * nbyFrame );
    psVLKN_DBG_CXT_CMD->m_uiSBO__Line__Input_Lines_End = (uiContext_Command_Index + 1) * nbyFrame;

    nbyFrame = psDBG_VLKN_CXT_EXEC->m_sSBO__Geom.m_uiSBO_Elements_Per_Frame * psDBG_VLKN_CXT_EXEC->m_sSBO__Geom.m_uiAligned_SBO_Size_Element;
    TgSTD_ATOMIC(store)( &psVLKN_DBG_CXT_CMD->m_xuiSBO__Geom_Offset, uiContext_Command_Index * nbyFrame );
    psVLKN_DBG_CXT_CMD->m_uiSBO__Geom_End = (uiContext_Command_Index + 1) * nbyFrame;

    return (KTgS_OK);
}


/* ---- tgKN_GPU_DBG_VLKN__Render_Target__Init ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_DBG_VLKN__Render_Target__Init( STg2_KN_GPU_DBG_VLKN_Render_Target_PC psDBG_Render_Target, STg2_KN_GPU_VLKN_Render_Target_PC psRender_Target,
                                                 VkDevice_C hVLKN_Device, TgRSIZE_C uiEXEC )
{
    /* Create the graphics pipelines for this render target */
    if (TgFAILED(tgKN_GPU_VLKN__Render_Target_Debug__Create_Pipelines(psDBG_Render_Target, hVLKN_Device, uiEXEC, psRender_Target)))
    {
        TgERROR_MSG(0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create graphics pipelines in Begin_Rendering");
        return (KTgE_FAIL);
    }

    return (KTgS_OK);
}


/* ---- tgKN_GPU_DBG_VLKN__Render_Target__Free ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_DBG_VLKN__Render_Target__Free( STg2_KN_GPU_DBG_VLKN_Render_Target_PC psDBG_Render_Target, VkDevice_C hVLKN_Device )
{
    TgRSIZE                             uiIndex;

    TgVERIFY(VK_NULL_HANDLE != hVLKN_Device);
    TgVERIFY(nullptr != psDBG_Render_Target);

    for (uiIndex = 0; uiIndex < TgARRAY_COUNT(psDBG_Render_Target->m_ahVLKN_Pipeline_Graphics); ++uiIndex)
    {
        if (VK_NULL_HANDLE == psDBG_Render_Target->m_ahVLKN_Pipeline_Graphics[uiIndex])
        {
            continue;
        }
        vkDestroyPipeline(hVLKN_Device, psDBG_Render_Target->m_ahVLKN_Pipeline_Graphics[uiIndex], g_psKN_GPU_VLKN_Allocator );
        psDBG_Render_Target->m_ahVLKN_Pipeline_Graphics[uiIndex] = VK_NULL_HANDLE;
    }
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_GPU_VLKN__Execute__Init_Debug__Create_Resources__Buffers ------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT tgKN_GPU_VLKN__Execute__Init_Debug__Create_Resources__Buffers( VkDevice_C hVLKN_Device, STg2_KN_GPU_VLKN_CMD_PC psVLKN_CMD, 
                                                                               STg2_KN_GPU_DBG_VLKN_CXT_EXEC_PC psDBG_VLKN_CXT_EXEC )
{
    STg2_KN_GPU_VLKN_Physical_Device_CP psGPU_EXT_Physical_Device;
    TgRSIZE                             uiMin_Storage_Alignment, nonCoherentAtomSize, uiTotal_Size;
    TgUINT_E64                          uiResource_Properties;
    TgRESULT                            iRet;
    VkResult                            eResult;
    VkBuffer_P                          phVLKN_Buffer;
    VkDeviceMemory_P                    phVLKN_Memory;
    STg2_KN_GPU_SBO_DESC_P              psSBO;

    psGPU_EXT_Physical_Device = g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Physical_Device + psDBG_VLKN_CXT_EXEC->m_idxCXT_HOST_Physical_Device;
    uiMin_Storage_Alignment = psGPU_EXT_Physical_Device->m_sVLKN_Properties.limits.minStorageBufferOffsetAlignment;
    uiMin_Storage_Alignment  = uiMin_Storage_Alignment > 0 ? uiMin_Storage_Alignment : 1;
    nonCoherentAtomSize = psGPU_EXT_Physical_Device->m_sVLKN_Properties.limits.nonCoherentAtomSize;
    nonCoherentAtomSize  = nonCoherentAtomSize > 0 ? nonCoherentAtomSize : 1;
    TgVERIFY(nonCoherentAtomSize > uiMin_Storage_Alignment);
    TgVERIFY(nonCoherentAtomSize % uiMin_Storage_Alignment == 0);

    uiResource_Properties  = ETgKN_GPU_RESOURCE_DESCRIPTOR__VERTEX_BUFFER;
    uiResource_Properties |= ETgKN_GPU_RESOURCE_DESCRIPTOR__MEMORY_LOCAL;

    /* Text UBO Ring Buffer and Vertex Buffer */
    phVLKN_Buffer = &psDBG_VLKN_CXT_EXEC->m_hVLKN_VBO_Buffer__Text;
    phVLKN_Memory = &psDBG_VLKN_CXT_EXEC->m_hVLKN_VBO_Memory__Text;
    uiTotal_Size = sizeof(g_sVertex_Strip_Text);
    iRet = tgKN_GPU_VLKN__CMD__Create_Buffer_With_Data(phVLKN_Buffer, phVLKN_Memory, psVLKN_CMD, uiResource_Properties, g_sVertex_Strip_Text, uiTotal_Size);
    if (TgFAILED(iRet))
    {
       TgERROR_MSG( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create debug text vertex buffer" );
       return (KTgE_FAIL);
    }
    TgMACRO_KN_GPU_VLKN_SET_NAME(hVLKN_Device, VK_OBJECT_TYPE_BUFFER, *phVLKN_Buffer, u8"Execution Context Resource: VBO DBG Text");

    /* Quad Vertex Buffer */
    phVLKN_Buffer = &psDBG_VLKN_CXT_EXEC->m_hVLKN_VBO_Buffer__Quad;
    phVLKN_Memory = &psDBG_VLKN_CXT_EXEC->m_hVLKN_VBO_Memory__Quad;
    uiTotal_Size = sizeof(g_sVertex_Strip_Quad);
    iRet = tgKN_GPU_VLKN__CMD__Create_Buffer_With_Data(phVLKN_Buffer, phVLKN_Memory, psVLKN_CMD, uiResource_Properties, g_sVertex_Strip_Quad, uiTotal_Size);
    if (TgFAILED(iRet))
    {
       TgERROR_MSG( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create debug quad vertex buffer" );
       return (KTgE_FAIL);
    }
    TgMACRO_KN_GPU_VLKN_SET_NAME(hVLKN_Device, VK_OBJECT_TYPE_BUFFER, *phVLKN_Buffer, u8"Execution Context Resource: VBO DBG Quad");

    /* Gradient Vertex Buffer */
    phVLKN_Buffer = &psDBG_VLKN_CXT_EXEC->m_hVLKN_VBO_Buffer__Gradient;
    phVLKN_Memory = &psDBG_VLKN_CXT_EXEC->m_hVLKN_VBO_Memory__Gradient;
    uiTotal_Size = sizeof(g_sVertex_Strip_Gradient);
    iRet = tgKN_GPU_VLKN__CMD__Create_Buffer_With_Data(phVLKN_Buffer, phVLKN_Memory, psVLKN_CMD, uiResource_Properties, g_sVertex_Strip_Gradient, uiTotal_Size);
    if (TgFAILED(iRet))
    {
       TgERROR_MSG( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create debug gradient vertex buffer" );
       return (KTgE_FAIL);
    }
    TgMACRO_KN_GPU_VLKN_SET_NAME(hVLKN_Device, VK_OBJECT_TYPE_BUFFER, *phVLKN_Buffer, u8"Execution Context Resource: VBO DBG Gradient");


    /* Note: I tried to get dynamic storage buffers to work, but there instrinic design is not truly dynamic. It allows for a dynamic number of fixed sized allocations, and not
             dynamic sized allocations within a range. Not worth trying to get there crap to work, given the validation check does not take into account both the dynamic offset
             and the range of referenced. Simply not worth using in general except potentially for very narrow purposes. */

    uiResource_Properties  = ETgKN_GPU_RESOURCE_DESCRIPTOR__STORAGE_BUFFER;
    uiResource_Properties |= ETgKN_GPU_RESOURCE_DESCRIPTOR__MEMORY_LOCAL | ETgKN_GPU_RESOURCE_DESCRIPTOR__MEMORY_HOST_VISIBLE;

    /* Text Data Buffer */
    psSBO = &psDBG_VLKN_CXT_EXEC->m_sSBO__Text;
    psSBO->m_uiAligned_SBO_Alignment = nonCoherentAtomSize;
    psSBO->m_uiAligned_SBO_Size_Element = tgCM_CEL_ALGN_PW2_UMAX( sizeof(TgVEC_F32_04_1), uiMin_Storage_Alignment );
    psSBO->m_uiSBO_Elements_Per_Frame = KTgKN_GPU_MAX_DBG_STORAGE_TEXT;
    psSBO->m_uiAligned_SBO_Total_Range = KTgKN_GPU_MAX_EXEC_CONTEXT_COMMAND * psSBO->m_uiSBO_Elements_Per_Frame * psSBO->m_uiAligned_SBO_Size_Element;
    uiTotal_Size = psSBO->m_uiAligned_SBO_Total_Range;
    if (TgFAILED(tgKN_GPU_VLKN__CMD__Create_Buffer( &psSBO->m_hVLKN_SBO_Buffer, &psSBO->m_hVLKN_SBO_Memory, psVLKN_CMD, uiResource_Properties, uiTotal_Size, nullptr, 0 )))
    {
       TgERROR_MSG( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create debug text storage buffer" );
       return (KTgE_FAIL);
    }
    TgMACRO_KN_GPU_VLKN_SET_NAME(hVLKN_Device, VK_OBJECT_TYPE_BUFFER, psSBO->m_hVLKN_SBO_Buffer, u8"Execution Context Resource: SBO DBG Text");
    eResult = vkMapMemory( hVLKN_Device, psSBO->m_hVLKN_SBO_Memory, 0, VK_WHOLE_SIZE, 0, &psSBO->m_uSBO_Mapped.m_pVoid );
    if (VK_SUCCESS != eResult)
    {
       TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to map memory for debug text storage buffer." );
       return (KTgE_FAIL);
    }

    /* Geom Instance Data Buffer */
    psSBO = &psDBG_VLKN_CXT_EXEC->m_sSBO__Geom;
    psSBO->m_uiAligned_SBO_Alignment = nonCoherentAtomSize;
    psSBO->m_uiAligned_SBO_Size_Element = tgCM_CEL_ALGN_PW2_UMAX( sizeof(STg2_KN_GPU_DBG_Geom), uiMin_Storage_Alignment );
    psSBO->m_uiSBO_Elements_Per_Frame = KTgKN_GPU_MAX_DBG_STORAGE_GEOM_INSTANCE;
    psSBO->m_uiAligned_SBO_Total_Range = KTgKN_GPU_MAX_EXEC_CONTEXT_COMMAND * psSBO->m_uiSBO_Elements_Per_Frame * psSBO->m_uiAligned_SBO_Size_Element;
    uiTotal_Size = psSBO->m_uiAligned_SBO_Total_Range;
    if (TgFAILED(tgKN_GPU_VLKN__CMD__Create_Buffer( &psSBO->m_hVLKN_SBO_Buffer, &psSBO->m_hVLKN_SBO_Memory, psVLKN_CMD, uiResource_Properties, uiTotal_Size, nullptr, 0 )))
    {
       TgERROR_MSG( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create debug geom storage buffer" );
       return (KTgE_FAIL);
    }
    TgMACRO_KN_GPU_VLKN_SET_NAME(hVLKN_Device, VK_OBJECT_TYPE_BUFFER, psSBO->m_hVLKN_SBO_Buffer, u8"Execution Context Resource: SBO DBG Geom");
    eResult = vkMapMemory( hVLKN_Device, psSBO->m_hVLKN_SBO_Memory, 0, VK_WHOLE_SIZE, 0, &psSBO->m_uSBO_Mapped.m_pVoid );
    if (VK_SUCCESS != eResult)
    {
       TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to map memory for debug geom storage buffer." );
       return (KTgE_FAIL);
    }

    /* Line Data Buffer */
    psSBO = &psDBG_VLKN_CXT_EXEC->m_sSBO__Line__Input_Lines;
    psSBO->m_uiAligned_SBO_Alignment = nonCoherentAtomSize;
    psSBO->m_uiAligned_SBO_Size_Element = tgCM_CEL_ALGN_PW2_UMAX( sizeof(STg2_KN_GPU_DBG_Line), uiMin_Storage_Alignment );
    psSBO->m_uiSBO_Elements_Per_Frame = KTgKN_GPU_MAX_DBG_STORAGE_LINE;
    psSBO->m_uiAligned_SBO_Total_Range = KTgKN_GPU_MAX_EXEC_CONTEXT_COMMAND * psSBO->m_uiSBO_Elements_Per_Frame * psSBO->m_uiAligned_SBO_Size_Element;
    uiTotal_Size = psSBO->m_uiAligned_SBO_Total_Range;
    if (TgFAILED(tgKN_GPU_VLKN__CMD__Create_Buffer( &psSBO->m_hVLKN_SBO_Buffer, &psSBO->m_hVLKN_SBO_Memory, psVLKN_CMD, uiResource_Properties, uiTotal_Size, nullptr, 0 )))
    {
       TgERROR_MSG( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create debug line storage buffer" );
       return (KTgE_FAIL);
    }
    TgMACRO_KN_GPU_VLKN_SET_NAME(hVLKN_Device, VK_OBJECT_TYPE_BUFFER, psSBO->m_hVLKN_SBO_Buffer, u8"Execution Context Resource: SBO DBG Input Lines");
    eResult = vkMapMemory( hVLKN_Device, psSBO->m_hVLKN_SBO_Memory, 0, VK_WHOLE_SIZE, 0, &psSBO->m_uSBO_Mapped.m_pVoid );
    if (VK_SUCCESS != eResult)
    {
       TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to map memory for debug line storage buffer." );
       return (KTgE_FAIL);
    }

    /* Line Visible lines buffer (GPU-only) */
    uiResource_Properties  = ETgKN_GPU_RESOURCE_DESCRIPTOR__STORAGE_BUFFER_DYNAMIC;
    uiResource_Properties |= ETgKN_GPU_RESOURCE_DESCRIPTOR__MEMORY_LOCAL | ETgKN_GPU_RESOURCE_DESCRIPTOR__MEMORY_HOST_VISIBLE;
    phVLKN_Buffer = &psDBG_VLKN_CXT_EXEC->m_hVLKN_SBO_Buffer__Visible_Lines;
    phVLKN_Memory = &psDBG_VLKN_CXT_EXEC->m_hVLKN_SBO_Memory__Visible_Lines;
    if (TgFAILED(tgKN_GPU_VLKN__CMD__Create_Buffer( phVLKN_Buffer, phVLKN_Memory, psVLKN_CMD, uiResource_Properties, uiTotal_Size, nullptr, 0 )))
    {
       TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create visible lines buffer." );
       return (KTgE_FAIL);
    }
    TgMACRO_KN_GPU_VLKN_SET_NAME(hVLKN_Device, VK_OBJECT_TYPE_BUFFER, *phVLKN_Buffer, u8"Execution Context Resource: SBO DBG Visible Lines");

    return (KTgS_OK);
}


/* ---- tgKN_GPU_VLKN__Execute__Init_Debug__Create_Resources__Descriptor_Set_Layout ---------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT tgKN_GPU_VLKN__Execute__Init_Debug__Create_Resources__Descriptor_Set_Layout( VkDevice_C hVLKN_Device, STg2_KN_GPU_DBG_VLKN_CXT_EXEC_PC psDBG_VLKN_CXT_EXEC )
{
                                        /* ---- Descriptor Layout - Debug UBO ---------------------------------------------------------------------------------------------------- */
    VkDescriptorSetLayoutBinding_C      asVLKN_Default_Layout_Bindings__DBG_UBO[] = {
                                            /* Binding 21: Debug Uniform Buffer (supports both static and dynamic types) */
                                            {
                                                .binding = KTgMACRO_KN_GPU_VLKN_BINDING_DBG_UBO,
                                                .descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
                                                .descriptorCount = 1,
                                                .stageFlags = VK_SHADER_STAGE_VERTEX_BIT,
                                                .pImmutableSamplers = nullptr
                                            }
                                        };

    VkDescriptorBindingFlags_C          asVLKN_Default_Layout_Bindings_Flags__DBG_UBO[] = {
                                            /* Binding KTgMACRO_KN_GPU_VLKN_BINDING_DBG_UBO: Debug Uniform Buffer */
                                            0,
                                        };

                                        /* ---- Descriptor Layout - SBO ---------------------------------------------------------------------------------------------------------- */
    VkDescriptorSetLayoutBinding_C      asVLKN_Default_Layout_Bindings__DBG_SBO[] = {
                                            /* Binding 21: Debug Uniform Buffer (supports both static and dynamic types) */
                                            {
                                                .binding = KTgMACRO_KN_GPU_VLKN_BINDING_DBG_SBO,
                                                .descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
                                                .descriptorCount = 1,
                                                .stageFlags = VK_SHADER_STAGE_VERTEX_BIT,
                                                .pImmutableSamplers = nullptr
                                            }
                                        };

    VkDescriptorBindingFlags_C          asVLKN_Default_Layout_Bindings_Flags__DBG_SBO[] = {
                                            /* Binding KTgMACRO_KN_GPU_VLKN_BINDING_DBG_SBO: Debug Storage Buffer */
                                            0,
                                        };

                                        /* ---- Descriptor Layout - LINE TASK+MESH ----------------------------------------------------------------------------------------------- */
    VkDescriptorSetLayoutBinding_C      asVLKN_Default_Layout_Bindings__DBG_LINE_TASK_MESH[] = {
                                            /* Binding 22: Input Lines */
                                            {
                                                .binding = KTgMACRO_KN_GPU_VLKN_BINDING_DBG_LINE_SBO__INPUT_LINES,
                                                .descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
                                                .descriptorCount = 1,
                                                .stageFlags = VK_SHADER_STAGE_TASK_BIT_EXT,
                                                .pImmutableSamplers = nullptr
                                            },
                                            /* Binding 23: Visible Lines */
                                            {
                                                .binding = KTgMACRO_KN_GPU_VLKN_BINDING_DBG_LINE_SBO__VISIBLE_LINES,
                                                .descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
                                                .descriptorCount = 1,
                                                .stageFlags = VK_SHADER_STAGE_TASK_BIT_EXT | VK_SHADER_STAGE_MESH_BIT_EXT | VK_SHADER_STAGE_FRAGMENT_BIT,
                                                .pImmutableSamplers = nullptr
                                            }
                                        };

    VkDescriptorBindingFlags_C          asVLKN_Default_Layout_Bindings_Flags__DBG_LINE_TASK_MESH[] = {
                                            /* Binding KTgMACRO_KN_GPU_VLKN_BINDING_DBG_LINE_SBO__INPUT_LINES: Debug Storage Buffer */
                                            0,
                                            /* Binding KTgMACRO_KN_GPU_VLKN_BINDING_DBG_LINE_SBO__VISIBLE_LINES: Debug Storage Buffer */
                                            0,
                                        };

                                        /* ---- Descriptor Set Layout List ------------------------------------------------------------------------------------------------------- */

    VkDescriptorSetLayoutBindingFlagsCI_C asVLKN_Default_Descriptor_Set_Layout_Binding_Flags[] = {
                                            {
                                                .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO,
                                                .pNext = nullptr,
                                                .bindingCount  = TgARRAY_COUNT(asVLKN_Default_Layout_Bindings_Flags__DBG_UBO),
                                                .pBindingFlags  = asVLKN_Default_Layout_Bindings_Flags__DBG_UBO
                                            },
                                            {
                                                .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO,
                                                .pNext = nullptr,
                                                .bindingCount  = TgARRAY_COUNT(asVLKN_Default_Layout_Bindings_Flags__DBG_SBO),
                                                .pBindingFlags  = asVLKN_Default_Layout_Bindings_Flags__DBG_SBO
                                            },
                                            {
                                                .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO,
                                                .pNext = nullptr,
                                                .bindingCount  = TgARRAY_COUNT(asVLKN_Default_Layout_Bindings_Flags__DBG_LINE_TASK_MESH),
                                                .pBindingFlags  = asVLKN_Default_Layout_Bindings_Flags__DBG_LINE_TASK_MESH
                                            }
                                        };

                                        /* ---- Descriptor Set Layout List ------------------------------------------------------------------------------------------------------- */

    VkDescriptorSetLayoutCI_C           asVLKN_Default_Descriptor_Set_Layouts[] = {
                                            {
                                                .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
                                                .pNext = asVLKN_Default_Descriptor_Set_Layout_Binding_Flags + 0,
                                                .flags = VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT,
                                                .bindingCount = TgARRAY_COUNT(asVLKN_Default_Layout_Bindings__DBG_UBO),
                                                .pBindings = asVLKN_Default_Layout_Bindings__DBG_UBO
                                            },
                                            {
                                                .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
                                                .pNext = asVLKN_Default_Descriptor_Set_Layout_Binding_Flags + 1,
                                                .flags = VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT,
                                                .bindingCount = TgARRAY_COUNT(asVLKN_Default_Layout_Bindings__DBG_SBO),
                                                .pBindings = asVLKN_Default_Layout_Bindings__DBG_SBO
                                            },
                                            {
                                                .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
                                                .pNext = asVLKN_Default_Descriptor_Set_Layout_Binding_Flags + 2,
                                                .flags = VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT,
                                                .bindingCount = TgARRAY_COUNT(asVLKN_Default_Layout_Bindings__DBG_LINE_TASK_MESH),
                                                .pBindings = asVLKN_Default_Layout_Bindings__DBG_LINE_TASK_MESH
                                            }
                                        };

    TgCOMPILER_ASSERT( ETgKN_GPU_DBG_VLKN_DESCRIPTOR_SET_LAYOUT__SBO == ETgKN_GPU_DBG_VLKN_DESCRIPTOR_SET_LAYOUT__UBO + 1, 0 );
    TgCOMPILER_ASSERT( ETgKN_GPU_DBG_VLKN_DESCRIPTOR_SET_LAYOUT__LINE_TASK_MESH == ETgKN_GPU_DBG_VLKN_DESCRIPTOR_SET_LAYOUT__UBO + 2, 0 );

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
        psDBG_VLKN_CXT_EXEC->m_ahVLKN_Descriptor_Set_Layout[ETgKN_GPU_DBG_VLKN_DESCRIPTOR_SET_LAYOUT__UBO + uiIndex] = hVLKN_Descriptor_Set_Layout;
    }

    return (KTgS_OK);
}


/* ---- tgKN_GPU_VLKN__Execute__Init_Debug__Create_Resources__Pipeline_Layout ---------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT tgKN_GPU_VLKN__Execute__Init_Debug__Create_Resources__Pipeline_Layout( VkDevice_C hVLKN_Device, STg2_KN_GPU_DBG_VLKN_CXT_EXEC_PC psDBG_VLKN_CXT_EXEC,
                                                                                       STg2_KN_GPU_VLKN_CXT_EXEC_PC psVLKN_CXT_EXEC )
{
                                        /* ---- Push Constants - Debug ----------------------------------------------------------------------------------------------------------- */

                                        /* Push constants for depth rendering - Minimal data for maximum performance */
    VkPushConstantRange_C               asVLKN_Default_Push_Constant_Ranges__DBG_VS_FS[] = {
                                            {
                                                .stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT,
                                                .offset = 0,
                                                .size = 128
                                            }
                                        };

    VkPushConstantRange_C               asVLKN_Default_Push_Constant_Ranges__DBG_TS[] = {
                                            {
                                                .stageFlags = VK_SHADER_STAGE_TASK_BIT_EXT,
                                                .offset = 0,
                                                .size = 128
                                            }
                                        };

                                        /* --------------------------------------------------------------------------------------------------------------------------------------- */

    VkDescriptorSetLayout               asVLKN_Descriptor_Set_Layout__DBG_UBO[] = {
                                            psVLKN_CXT_EXEC->m_ahVLKN_Descriptor_Set_Layout[ETgKN_GPU_VLKN_DESCRIPTOR_SET_LAYOUT__BASE_SHARED], /* Set 0: Shared */
                                            psDBG_VLKN_CXT_EXEC->m_ahVLKN_Descriptor_Set_Layout[ETgKN_GPU_DBG_VLKN_DESCRIPTOR_SET_LAYOUT__UBO], /* Set 1: Debug */
                                        };

    VkDescriptorSetLayout               asVLKN_Descriptor_Set_Layout__DBG_SBO[] = {
                                            psVLKN_CXT_EXEC->m_ahVLKN_Descriptor_Set_Layout[ETgKN_GPU_VLKN_DESCRIPTOR_SET_LAYOUT__BASE_SHARED], /* Set 0: Shared */
                                            psDBG_VLKN_CXT_EXEC->m_ahVLKN_Descriptor_Set_Layout[ETgKN_GPU_DBG_VLKN_DESCRIPTOR_SET_LAYOUT__SBO], /* Set 1: Debug */
                                        };

    VkDescriptorSetLayout               asVLKN_Descriptor_Set_Layout__DBG_LINE_TASK_MESH[] = {
                                            psVLKN_CXT_EXEC->m_ahVLKN_Descriptor_Set_Layout[ETgKN_GPU_VLKN_DESCRIPTOR_SET_LAYOUT__BASE_SHARED],            /* Set 0: Shared */
                                            psDBG_VLKN_CXT_EXEC->m_ahVLKN_Descriptor_Set_Layout[ETgKN_GPU_DBG_VLKN_DESCRIPTOR_SET_LAYOUT__LINE_TASK_MESH], /* Set 1: Debug */
                                        };

    VkPipelineLayoutCI_C                asVLKN_Default_Graphics_Pipeline_Layout[] = {
                                            {   /* Debug None - ETgKN_GPU_DBG_PIPELINE_LAYOUT__NONE */
                                                .sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
                                                .pNext = nullptr,
                                                .flags = 0,
                                                .setLayoutCount = 1,
                                                .pSetLayouts = psVLKN_CXT_EXEC->m_ahVLKN_Descriptor_Set_Layout + ETgKN_GPU_VLKN_DESCRIPTOR_SET_LAYOUT__BASE_SHARED,
                                                .pushConstantRangeCount = TgARRAY_COUNT(asVLKN_Default_Push_Constant_Ranges__DBG_VS_FS),
                                                .pPushConstantRanges = asVLKN_Default_Push_Constant_Ranges__DBG_VS_FS,
                                            },
                                            {   /* Debug UBO - ETgKN_GPU_DBG_PIPELINE_LAYOUT__UBO */
                                                .sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
                                                .pNext = nullptr,
                                                .flags = 0,
                                                .setLayoutCount = TgARRAY_COUNT(asVLKN_Descriptor_Set_Layout__DBG_UBO),
                                                .pSetLayouts = asVLKN_Descriptor_Set_Layout__DBG_UBO,
                                                .pushConstantRangeCount = TgARRAY_COUNT(asVLKN_Default_Push_Constant_Ranges__DBG_VS_FS),
                                                .pPushConstantRanges = asVLKN_Default_Push_Constant_Ranges__DBG_VS_FS,
                                            },
                                            {   /* Debug SBO - ETgKN_GPU_DBG_PIPELINE_LAYOUT__SBO */
                                                .sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
                                                .pNext = nullptr,
                                                .flags = 0,
                                                .setLayoutCount = TgARRAY_COUNT(asVLKN_Descriptor_Set_Layout__DBG_SBO),
                                                .pSetLayouts = asVLKN_Descriptor_Set_Layout__DBG_SBO,
                                                .pushConstantRangeCount = TgARRAY_COUNT(asVLKN_Default_Push_Constant_Ranges__DBG_VS_FS),
                                                .pPushConstantRanges = asVLKN_Default_Push_Constant_Ranges__DBG_VS_FS,
                                            },
                                            {   /* Debug LINE - ETgKN_GPU_DBG_PIPELINE_LAYOUT__LINE_TASK_MESH */
                                                .sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
                                                .pNext = nullptr,
                                                .flags = 0,
                                                .setLayoutCount = TgARRAY_COUNT(asVLKN_Descriptor_Set_Layout__DBG_LINE_TASK_MESH),
                                                .pSetLayouts = asVLKN_Descriptor_Set_Layout__DBG_LINE_TASK_MESH,
                                                .pushConstantRangeCount = TgARRAY_COUNT(asVLKN_Default_Push_Constant_Ranges__DBG_TS),
                                                .pPushConstantRanges = asVLKN_Default_Push_Constant_Ranges__DBG_TS,
                                            }
                                        };

    TgCOMPILER_ASSERT( ETgKN_GPU_DBG_PIPELINE_LAYOUT__UBO == ETgKN_GPU_DBG_PIPELINE_LAYOUT__NONE + 1, 0 );
    TgCOMPILER_ASSERT( ETgKN_GPU_DBG_PIPELINE_LAYOUT__SBO == ETgKN_GPU_DBG_PIPELINE_LAYOUT__NONE + 2, 0 );
    TgCOMPILER_ASSERT( ETgKN_GPU_DBG_PIPELINE_LAYOUT__LINE_TASK_MESH == ETgKN_GPU_DBG_PIPELINE_LAYOUT__NONE + 3, 0 );

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
        psDBG_VLKN_CXT_EXEC->m_ahVLKN_Pipeline_Layout[ETgKN_GPU_DBG_PIPELINE_LAYOUT__NONE + uiIndex] = hVLKN_Pipeline_Layout;
    }

    TgMACRO_KN_GPU_VLKN_SET_NAME_FROM_ENUM(hVLKN_Device, VK_OBJECT_TYPE_PIPELINE_LAYOUT, psDBG_VLKN_CXT_EXEC->m_ahVLKN_Pipeline_Layout[0], ETgKN_GPU_DBG_PIPELINE_LAYOUT__UBO)
    TgMACRO_KN_GPU_VLKN_SET_NAME_FROM_ENUM(hVLKN_Device, VK_OBJECT_TYPE_PIPELINE_LAYOUT, psDBG_VLKN_CXT_EXEC->m_ahVLKN_Pipeline_Layout[1], ETgKN_GPU_DBG_PIPELINE_LAYOUT__SBO)
    TgMACRO_KN_GPU_VLKN_SET_NAME_FROM_ENUM(
        hVLKN_Device, VK_OBJECT_TYPE_PIPELINE_LAYOUT, psDBG_VLKN_CXT_EXEC->m_ahVLKN_Pipeline_Layout[2], ETgKN_GPU_DBG_PIPELINE_LAYOUT__LINE_TASK_MESH)

    return (KTgS_OK);
}


/* ---- tgKN_GPU_VLKN__Execute__Init_Debug__Create_Default_Command_Pool ---------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT tgKN_GPU_VLKN__Execute__Init_Debug__Create_Default_Command_Pool( VkDevice_C hVLKN_Device, STg2_KN_GPU_DBG_VLKN_CXT_EXEC_PC psDBG_VLKN_CXT_EXEC )
{
    VkDescriptorPoolSize_C              asVLKN_Pool_Sizes[] = {
                                            {
                                                .type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC,
                                                .descriptorCount = KTgKN_GPU_VLKN_DBG_ALLOC_PER_FRAME,
                                            },
                                            {
                                                .type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC,
                                                .descriptorCount = KTgKN_GPU_VLKN_DBG_ALLOC_PER_FRAME,
                                            },
                                            {
                                                .type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
                                                .descriptorCount = KTgKN_GPU_VLKN_DBG_ALLOC_PER_FRAME,
                                            },
                                            {
                                                .type = VK_DESCRIPTOR_TYPE_SAMPLER,
                                                .descriptorCount = KTgKN_GPU_VLKN_DBG_ALLOC_PER_FRAME,
                                            },
                                            {
                                                .type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER ,
                                                .descriptorCount = KTgKN_GPU_VLKN_DBG_ALLOC_PER_FRAME,
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

    eResult = vkCreateDescriptorPool( hVLKN_Device, &sVLKN_Pool_CI, g_psKN_GPU_VLKN_Allocator, &psDBG_VLKN_CXT_EXEC->m_hVLKN_Descriptor_Pool );
    if (VK_SUCCESS != eResult)
    {
        TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create descriptor pool for Execution Context" );
        psDBG_VLKN_CXT_EXEC->m_hVLKN_Descriptor_Pool = VK_NULL_HANDLE;
        return( KTgE_FAIL );
    };
    return (KTgS_OK);
}


/* ---- tgKN_GPU_VLKN__Execute__Init_Debug__Create_Resources__Descriptor_Set ----------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT tgKN_GPU_VLKN__Execute__Init_Debug__Create_Resources__Descriptor_Set( VkDevice_C hVLKN_Device, STg2_KN_GPU_DBG_VLKN_CXT_EXEC_PC psDBG_VLKN_CXT_EXEC )
{
    VkDescriptorSetAllocateInfo         sVLKN_Alloc_Info = {
                                            .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
                                            .pNext = nullptr,
                                            .descriptorPool = psDBG_VLKN_CXT_EXEC->m_hVLKN_Descriptor_Pool,
                                            .descriptorSetCount = 1,
                                            .pSetLayouts = nullptr,
                                        };

    VkDescriptorBufferInfo              asVLKN_Buffer_Info[2];
    VkWriteDescriptorSet                asVLKN_Write_Descriptor[2];
    VkDescriptorSet                     hVLKN_Descriptor_Set;
    VkResult                            eResult;
    TgRSIZE                             uiIndex;

    TgCOMPILER_ASSERT( TgARRAY_COUNT(asVLKN_Buffer_Info) == TgARRAY_COUNT(asVLKN_Write_Descriptor), 0 );

    /* Update descriptor sets */
    tgMM_Set_U08_0x00( asVLKN_Buffer_Info, sizeof( asVLKN_Buffer_Info ) );
    tgMM_Set_U08_0x00( asVLKN_Write_Descriptor, sizeof( asVLKN_Write_Descriptor ) );

    for (uiIndex = 0; uiIndex < TgARRAY_COUNT(asVLKN_Write_Descriptor); ++uiIndex)
    {
        asVLKN_Write_Descriptor[uiIndex].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        asVLKN_Write_Descriptor[uiIndex].descriptorCount = 1;
        asVLKN_Write_Descriptor[uiIndex].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
        asVLKN_Write_Descriptor[uiIndex].pBufferInfo = asVLKN_Buffer_Info + uiIndex;
    }

    /* Text */
    sVLKN_Alloc_Info.pSetLayouts = psDBG_VLKN_CXT_EXEC->m_ahVLKN_Descriptor_Set_Layout + ETgKN_GPU_DBG_VLKN_DESCRIPTOR_SET_LAYOUT__SBO;
    eResult = vkAllocateDescriptorSets( hVLKN_Device, &sVLKN_Alloc_Info, &hVLKN_Descriptor_Set );
    if (eResult != VK_SUCCESS)
    {
        TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to allocate descriptor set" );
        return (KTgE_FAIL);
    }
    TgMACRO_KN_GPU_VLKN_SET_NAME(hVLKN_Device, VK_OBJECT_TYPE_DESCRIPTOR_SET, hVLKN_Descriptor_Set, u8"DBG Descriptor Set Text");
    asVLKN_Buffer_Info[0].buffer = psDBG_VLKN_CXT_EXEC->m_sSBO__Text.m_hVLKN_SBO_Buffer;
    asVLKN_Buffer_Info[0].range = psDBG_VLKN_CXT_EXEC->m_sSBO__Text.m_uiAligned_SBO_Total_Range;
    asVLKN_Write_Descriptor[0].dstSet = hVLKN_Descriptor_Set;
    asVLKN_Write_Descriptor[0].dstBinding = KTgMACRO_KN_GPU_VLKN_BINDING_DBG_SBO;
    vkUpdateDescriptorSets( hVLKN_Device, 1, asVLKN_Write_Descriptor, 0, nullptr );
    psDBG_VLKN_CXT_EXEC->m_hVLKN_DBG_Descriptor_Set__Text = hVLKN_Descriptor_Set;

    /* Geom Instance */
    sVLKN_Alloc_Info.pSetLayouts = psDBG_VLKN_CXT_EXEC->m_ahVLKN_Descriptor_Set_Layout + ETgKN_GPU_DBG_VLKN_DESCRIPTOR_SET_LAYOUT__SBO;
    eResult = vkAllocateDescriptorSets( hVLKN_Device, &sVLKN_Alloc_Info, &hVLKN_Descriptor_Set );
    if (eResult != VK_SUCCESS)
    {
        TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to allocate descriptor set" );
        return (KTgE_FAIL);
    }
    TgMACRO_KN_GPU_VLKN_SET_NAME(hVLKN_Device, VK_OBJECT_TYPE_DESCRIPTOR_SET, hVLKN_Descriptor_Set, u8"DBG Descriptor Set Geom Instance");
    asVLKN_Buffer_Info[0].buffer = psDBG_VLKN_CXT_EXEC->m_sSBO__Geom.m_hVLKN_SBO_Buffer;
    asVLKN_Buffer_Info[0].range = psDBG_VLKN_CXT_EXEC->m_sSBO__Geom.m_uiAligned_SBO_Total_Range;
    asVLKN_Write_Descriptor[0].dstSet = hVLKN_Descriptor_Set;
    asVLKN_Write_Descriptor[0].dstBinding = KTgMACRO_KN_GPU_VLKN_BINDING_DBG_SBO;
    vkUpdateDescriptorSets( hVLKN_Device, 1, asVLKN_Write_Descriptor, 0, nullptr );
    psDBG_VLKN_CXT_EXEC->m_hVLKN_DBG_Descriptor_Set__Geom = hVLKN_Descriptor_Set;

    /* Line Render */
    sVLKN_Alloc_Info.pSetLayouts = psDBG_VLKN_CXT_EXEC->m_ahVLKN_Descriptor_Set_Layout + ETgKN_GPU_DBG_VLKN_DESCRIPTOR_SET_LAYOUT__LINE_TASK_MESH;
    eResult = vkAllocateDescriptorSets( hVLKN_Device, &sVLKN_Alloc_Info, &hVLKN_Descriptor_Set );
    if (eResult != VK_SUCCESS)
    {
        TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to allocate descriptor set" );
        return (KTgE_FAIL);
    }
    TgMACRO_KN_GPU_VLKN_SET_NAME(hVLKN_Device, VK_OBJECT_TYPE_DESCRIPTOR_SET, hVLKN_Descriptor_Set, u8"DBG Descriptor Set Line Culling");
    asVLKN_Buffer_Info[0].buffer = psDBG_VLKN_CXT_EXEC->m_sSBO__Line__Input_Lines.m_hVLKN_SBO_Buffer;
    asVLKN_Buffer_Info[0].range = psDBG_VLKN_CXT_EXEC->m_sSBO__Line__Input_Lines.m_uiAligned_SBO_Total_Range;
    asVLKN_Write_Descriptor[0].dstSet = hVLKN_Descriptor_Set;
    asVLKN_Write_Descriptor[0].dstBinding = KTgMACRO_KN_GPU_VLKN_BINDING_DBG_LINE_SBO__INPUT_LINES;

    asVLKN_Buffer_Info[1].buffer = psDBG_VLKN_CXT_EXEC->m_hVLKN_SBO_Buffer__Visible_Lines;
    asVLKN_Buffer_Info[1].range = psDBG_VLKN_CXT_EXEC->m_sSBO__Line__Input_Lines.m_uiAligned_SBO_Total_Range;
    asVLKN_Write_Descriptor[1].dstSet = hVLKN_Descriptor_Set;
    asVLKN_Write_Descriptor[1].dstBinding = KTgMACRO_KN_GPU_VLKN_BINDING_DBG_LINE_SBO__VISIBLE_LINES;

    vkUpdateDescriptorSets( hVLKN_Device, 2, asVLKN_Write_Descriptor, 0, nullptr );
    psDBG_VLKN_CXT_EXEC->m_hVLKN_DBG_Descriptor_Set__Line_Task_Mesh = hVLKN_Descriptor_Set;

    return (KTgS_OK);
}


/* ---- tgKN_GPU_VLKN__Execute__Init_Debug__Destroy_Resources__Buffers ----------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgKN_GPU_VLKN__Execute__Init_Debug__Destroy_Resources__Buffers( VkDevice_C hVLKN_Device, STg2_KN_GPU_DBG_VLKN_CXT_EXEC_PC psDBG_VLKN_CXT_EXEC )
{
    TgRSIZE                             uiIndex, uiResource;

    for (uiIndex = 0; uiIndex < TgARRAY_COUNT(psDBG_VLKN_CXT_EXEC->m_asComand_DBG); ++uiIndex)
    {
        if (nullptr != psDBG_VLKN_CXT_EXEC->m_asComand_DBG[uiIndex].m_sCMD_DBG.m_psLine)
        {
            TgFREE_VIRTUAL( psDBG_VLKN_CXT_EXEC->m_asComand_DBG[uiIndex].m_sCMD_DBG.m_psLine );
        }
    }

    if (psDBG_VLKN_CXT_EXEC->m_hVLKN_VBO_Buffer__Text)
    {
        vkDestroyBuffer(hVLKN_Device, psDBG_VLKN_CXT_EXEC->m_hVLKN_VBO_Buffer__Text, g_psKN_GPU_VLKN_Allocator);
        vkFreeMemory(hVLKN_Device, psDBG_VLKN_CXT_EXEC->m_hVLKN_VBO_Memory__Text, g_psKN_GPU_VLKN_Allocator);
        psDBG_VLKN_CXT_EXEC->m_hVLKN_VBO_Buffer__Text = VK_NULL_HANDLE;
        psDBG_VLKN_CXT_EXEC->m_hVLKN_VBO_Memory__Text = VK_NULL_HANDLE;
    }

    if (psDBG_VLKN_CXT_EXEC->m_sSBO__Text.m_hVLKN_SBO_Buffer)
    {
        vkDestroyBuffer(hVLKN_Device, psDBG_VLKN_CXT_EXEC->m_sSBO__Text.m_hVLKN_SBO_Buffer, g_psKN_GPU_VLKN_Allocator);
        vkFreeMemory(hVLKN_Device, psDBG_VLKN_CXT_EXEC->m_sSBO__Text.m_hVLKN_SBO_Memory, g_psKN_GPU_VLKN_Allocator);
        psDBG_VLKN_CXT_EXEC->m_sSBO__Text.m_hVLKN_SBO_Buffer = VK_NULL_HANDLE;
        psDBG_VLKN_CXT_EXEC->m_sSBO__Text.m_hVLKN_SBO_Memory = VK_NULL_HANDLE;
    }

    if (psDBG_VLKN_CXT_EXEC->m_hVLKN_VBO_Buffer__Quad)
    {
        vkDestroyBuffer(hVLKN_Device, psDBG_VLKN_CXT_EXEC->m_hVLKN_VBO_Buffer__Quad, g_psKN_GPU_VLKN_Allocator);
        vkFreeMemory(hVLKN_Device, psDBG_VLKN_CXT_EXEC->m_hVLKN_VBO_Memory__Quad, g_psKN_GPU_VLKN_Allocator);
        psDBG_VLKN_CXT_EXEC->m_hVLKN_VBO_Buffer__Quad = VK_NULL_HANDLE;
        psDBG_VLKN_CXT_EXEC->m_hVLKN_VBO_Memory__Quad = VK_NULL_HANDLE;
    }

    if (psDBG_VLKN_CXT_EXEC->m_hVLKN_VBO_Buffer__Gradient)
    {
        vkDestroyBuffer(hVLKN_Device, psDBG_VLKN_CXT_EXEC->m_hVLKN_VBO_Buffer__Gradient, g_psKN_GPU_VLKN_Allocator);
        vkFreeMemory(hVLKN_Device, psDBG_VLKN_CXT_EXEC->m_hVLKN_VBO_Memory__Gradient, g_psKN_GPU_VLKN_Allocator);
        psDBG_VLKN_CXT_EXEC->m_hVLKN_VBO_Buffer__Gradient = VK_NULL_HANDLE;
        psDBG_VLKN_CXT_EXEC->m_hVLKN_VBO_Memory__Gradient = VK_NULL_HANDLE;
    }

    if (psDBG_VLKN_CXT_EXEC->m_sSBO__Line__Input_Lines.m_hVLKN_SBO_Buffer)
    {
        vkDestroyBuffer(hVLKN_Device, psDBG_VLKN_CXT_EXEC->m_sSBO__Line__Input_Lines.m_hVLKN_SBO_Buffer, g_psKN_GPU_VLKN_Allocator);
        vkFreeMemory(hVLKN_Device, psDBG_VLKN_CXT_EXEC->m_sSBO__Line__Input_Lines.m_hVLKN_SBO_Memory, g_psKN_GPU_VLKN_Allocator);
        psDBG_VLKN_CXT_EXEC->m_sSBO__Line__Input_Lines.m_hVLKN_SBO_Buffer = VK_NULL_HANDLE;
        psDBG_VLKN_CXT_EXEC->m_sSBO__Line__Input_Lines.m_hVLKN_SBO_Memory = VK_NULL_HANDLE;
    }

    if (psDBG_VLKN_CXT_EXEC->m_hVLKN_SBO_Buffer__Visible_Lines)
    {
        vkDestroyBuffer(hVLKN_Device, psDBG_VLKN_CXT_EXEC->m_hVLKN_SBO_Buffer__Visible_Lines, g_psKN_GPU_VLKN_Allocator);
        vkFreeMemory(hVLKN_Device, psDBG_VLKN_CXT_EXEC->m_hVLKN_SBO_Memory__Visible_Lines, g_psKN_GPU_VLKN_Allocator);
        psDBG_VLKN_CXT_EXEC->m_hVLKN_SBO_Buffer__Visible_Lines = VK_NULL_HANDLE;
        psDBG_VLKN_CXT_EXEC->m_hVLKN_SBO_Memory__Visible_Lines = VK_NULL_HANDLE;
    }

    for (uiResource = 0; uiResource < ETgKN_GPU_DEBUG_PM_3D_COUNT; ++uiResource)
    {
        if (psDBG_VLKN_CXT_EXEC->m_ahVLKN_VBO_Buffer__Geom[uiResource])
        {
            vkDestroyBuffer(hVLKN_Device, psDBG_VLKN_CXT_EXEC->m_ahVLKN_VBO_Buffer__Geom[uiResource], g_psKN_GPU_VLKN_Allocator);
            vkFreeMemory(hVLKN_Device, psDBG_VLKN_CXT_EXEC->m_ahVLKN_VBO_Memory__Geom[uiResource], g_psKN_GPU_VLKN_Allocator);
            psDBG_VLKN_CXT_EXEC->m_ahVLKN_VBO_Buffer__Geom[uiResource] = VK_NULL_HANDLE;
            psDBG_VLKN_CXT_EXEC->m_ahVLKN_VBO_Memory__Geom[uiResource] = VK_NULL_HANDLE;
        }

        if (psDBG_VLKN_CXT_EXEC->m_ahVLKN_IBO_Buffer__Geom[uiResource])
        {   
            vkDestroyBuffer(hVLKN_Device, psDBG_VLKN_CXT_EXEC->m_ahVLKN_IBO_Buffer__Geom[uiResource], g_psKN_GPU_VLKN_Allocator);
            vkFreeMemory(hVLKN_Device, psDBG_VLKN_CXT_EXEC->m_ahVLKN_IBO_Memory__Geom[uiResource], g_psKN_GPU_VLKN_Allocator);
            psDBG_VLKN_CXT_EXEC->m_ahVLKN_IBO_Buffer__Geom[uiResource] = VK_NULL_HANDLE;
            psDBG_VLKN_CXT_EXEC->m_ahVLKN_IBO_Memory__Geom[uiResource] = VK_NULL_HANDLE;
            psDBG_VLKN_CXT_EXEC->m_nbyVLKN_IBO__Geom[uiResource] = 0;
        }
    };

    if (psDBG_VLKN_CXT_EXEC->m_sSBO__Geom.m_hVLKN_SBO_Buffer)
    {
        vkDestroyBuffer(hVLKN_Device, psDBG_VLKN_CXT_EXEC->m_sSBO__Geom.m_hVLKN_SBO_Buffer, g_psKN_GPU_VLKN_Allocator);
        vkFreeMemory(hVLKN_Device, psDBG_VLKN_CXT_EXEC->m_sSBO__Geom.m_hVLKN_SBO_Memory, g_psKN_GPU_VLKN_Allocator);
        psDBG_VLKN_CXT_EXEC->m_sSBO__Geom.m_hVLKN_SBO_Buffer = VK_NULL_HANDLE;
        psDBG_VLKN_CXT_EXEC->m_sSBO__Geom.m_hVLKN_SBO_Memory = VK_NULL_HANDLE;
     }
}


/* ---- tgKN_GPU_VLKN__Render_Target_Debug__Create_Pipelines --------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT tgKN_GPU_VLKN__Render_Target_Debug__Create_Pipelines(
    STg2_KN_GPU_DBG_VLKN_Render_Target_PC       psDBG_Render_Target,
    VkDevice_C                                  hVLKN_Device,
    TgRSIZE_C                                   uiEXEC,
    STg2_KN_GPU_VLKN_Render_Target_PC           psRender_Target )
{
    STg2_KN_GPU_DBG_VLKN_CXT_EXEC_PC            psDBG_VLKN_CXT_EXEC = g_asKN_GPU_DBG_EXT_CXT_EXEC + uiEXEC;
    STg2_KN_GPU_VLKN_CXT_EXEC_PC                psVLKN_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + uiEXEC;
    VkPipeline_PC                               ahVLKN_Pipeline = psDBG_Render_Target->m_ahVLKN_Pipeline_Graphics;
    TgRSIZE_C                                   nuiVLKN_Pipeline = TgARRAY_COUNT(psDBG_Render_Target->m_ahVLKN_Pipeline_Graphics);
    VkFormat                                    enVLKN_Depth_Stencil_Format = (VkFormat)psRender_Target->m_sRender_Target_DESC.m_enDepth_Stencil_Format;

    STg2_KN_GPU_VLKN_Graphics_Pipeline_CI       sVLKN_Pipeline_CI;

    tgMM_Set_U08_0x00(&sVLKN_Pipeline_CI, sizeof(sVLKN_Pipeline_CI));

    sVLKN_Pipeline_CI.m_psPipeline_DESC = (STg2_KN_GPU_Graphics_Pipeline_CP)&g_asKN_GPU_DBG_Graphics_Pipeline;
    sVLKN_Pipeline_CI.m_nuiPipeline_DESC = TgARRAY_COUNT(g_asKN_GPU_DBG_Graphics_Pipeline);

    sVLKN_Pipeline_CI.m_ptiVS = g_sKN_GPU_DBG_CXT_HOST.m_atiVS;
    sVLKN_Pipeline_CI.m_nuiVS = TgARRAY_COUNT(g_sKN_GPU_DBG_CXT_HOST.m_atiVS);
    sVLKN_Pipeline_CI.m_ptiTS = g_sKN_GPU_DBG_CXT_HOST.m_atiTS;
    sVLKN_Pipeline_CI.m_nuiTS = TgARRAY_COUNT(g_sKN_GPU_DBG_CXT_HOST.m_atiTS);
    sVLKN_Pipeline_CI.m_ptiMS = g_sKN_GPU_DBG_CXT_HOST.m_atiMS;
    sVLKN_Pipeline_CI.m_nuiMS = TgARRAY_COUNT(g_sKN_GPU_DBG_CXT_HOST.m_atiMS);
    sVLKN_Pipeline_CI.m_ptiFS = g_sKN_GPU_DBG_CXT_HOST.m_atiFS;
    sVLKN_Pipeline_CI.m_nuiFS = TgARRAY_COUNT(g_sKN_GPU_DBG_CXT_HOST.m_atiFS);

    sVLKN_Pipeline_CI.m_phVLKN_VS = psDBG_VLKN_CXT_EXEC->m_ahVLKN_VS;
    sVLKN_Pipeline_CI.m_phVLKN_TS = psDBG_VLKN_CXT_EXEC->m_ahVLKN_TS;
    sVLKN_Pipeline_CI.m_phVLKN_MS = psDBG_VLKN_CXT_EXEC->m_ahVLKN_MS;
    sVLKN_Pipeline_CI.m_phVLKN_FS = psDBG_VLKN_CXT_EXEC->m_ahVLKN_FS;

    sVLKN_Pipeline_CI.m_phVLKN_Pipeline_Layout = psDBG_VLKN_CXT_EXEC->m_ahVLKN_Pipeline_Layout;
    sVLKN_Pipeline_CI.m_hVLKN_Device = hVLKN_Device;
    sVLKN_Pipeline_CI.m_psVLKN_CXT_EXEC = psVLKN_CXT_EXEC;
    sVLKN_Pipeline_CI.m_enColour_Space = psRender_Target->m_sRender_Target_DESC.m_enColour_Space;

    sVLKN_Pipeline_CI.m_sVLKN_Pipeline_Rendering_CI.sType = VK_STRUCTURE_TYPE_PIPELINE_RENDERING_CREATE_INFO_KHR;
    sVLKN_Pipeline_CI.m_sVLKN_Pipeline_Rendering_CI.pNext = nullptr;
    sVLKN_Pipeline_CI.m_sVLKN_Pipeline_Rendering_CI.colorAttachmentCount = (TgUINT_E32)psRender_Target->m_sRender_Target_DESC.m_nuiColour_Target;
    sVLKN_Pipeline_CI.m_sVLKN_Pipeline_Rendering_CI.pColorAttachmentFormats = (VkFormat_P)psRender_Target->m_sRender_Target_DESC.m_aenColour_Format;
    sVLKN_Pipeline_CI.m_sVLKN_Pipeline_Rendering_CI.depthAttachmentFormat = enVLKN_Depth_Stencil_Format;
    sVLKN_Pipeline_CI.m_sVLKN_Pipeline_Rendering_CI.stencilAttachmentFormat = psRender_Target->m_bStencil_Valid ? enVLKN_Depth_Stencil_Format : VK_FORMAT_UNDEFINED;
    sVLKN_Pipeline_CI.m_sVLKN_Pipeline_Rendering_CI.viewMask = 0;

    if (TgFAILED(tgKN_GPU_VLKN_Create_Graphic_Pipelines(ahVLKN_Pipeline, nuiVLKN_Pipeline, &sVLKN_Pipeline_CI)))
    {
        TgERROR_MSGF(0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create default pipelines");
        return (KTgE_FAIL);
    }

    return (KTgS_OK);
}


/* =============================================================================================================================================================================== */

/*# defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
#endif
