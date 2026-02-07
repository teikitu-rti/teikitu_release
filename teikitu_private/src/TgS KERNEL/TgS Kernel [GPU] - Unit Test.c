/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Kernel [GPU] - Unit Test.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_GPU_UNIT_TEST__UTIL__Init_Select ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_UNIT_TEST__UTIL__Init_Select( STg2_KN_GPU_Select_PC psSelect, TgBOOL bSingle )
{
#if defined(TgBUILD_FEATURE__GRAPHICS)

    STg2_KN_GPU_Physical_Device_CP      apPhysical_Device[KTgKN_GPU_MAX_PHYSICAL_DEVICE];
    TgRSIZE                             uiPhysical_Device;
    TgRSIZE                             uiNode,uiNodeIndex;
    TgRSIZE                             uiOutput;

    TgPARAM_CHECK( nullptr != psSelect );

    if (TgFAILED(tgKN_GPU__Host__Query_Physical_Device_List( apPhysical_Device, KTgKN_GPU_MAX_PHYSICAL_DEVICE )) || nullptr == apPhysical_Device[0])
    {
        return (KTgE_FAIL);
    }

    /* Count up all of the GPU nodes that were enumerated. */

    for (psSelect->m_nuiPhysical_Device = 0, psSelect->m_nuiNode = 0;
         KTgKN_GPU_MAX_PHYSICAL_DEVICE > psSelect->m_nuiPhysical_Device && 0 != apPhysical_Device[psSelect->m_nuiPhysical_Device];
         ++psSelect->m_nuiPhysical_Device)
    {
        if (psSelect->m_nuiPhysical_Device >= KTgKN_GPU_MAX_DEVC_CONTEXT)
            break;
        if (psSelect->m_nuiNode >= KTgKN_GPU_MAX_EXEC_CONTEXT)
            break;
        if (psSelect->m_nuiNode + apPhysical_Device[psSelect->m_nuiPhysical_Device]->m_nuiNode > KTgKN_GPU_MAX_EXEC_CONTEXT)
        {
            psSelect->m_nuiNode = KTgKN_GPU_MAX_EXEC_CONTEXT;
        }
        else
        {
            psSelect->m_nuiNode += apPhysical_Device[psSelect->m_nuiPhysical_Device]->m_nuiNode;
        }
    }

    /* Initialize all of the nodes that were enumerated. */

    for (uiPhysical_Device = 0, uiNode = 0; uiPhysical_Device < psSelect->m_nuiPhysical_Device; ++uiPhysical_Device)
    {
        psSelect->m_uiEnumeration_Physical_Device_Index[uiPhysical_Device] = uiPhysical_Device;
        for (uiNodeIndex = 0; uiNodeIndex < apPhysical_Device[uiPhysical_Device]->m_nuiNode; ++uiNodeIndex, ++uiNode)
        {
            psSelect->m_sNode[uiNode].m_idxCXT_HOST_Physical_Device = uiPhysical_Device;
            psSelect->m_sNode[uiNode].m_uiPhysical_Device_Node_Mask = 1u << uiNodeIndex;
            psSelect->m_sNode[uiNode].m_nuiRender_Target_Max = 16;
            psSelect->m_sNode[uiNode].m_nuiDepth_Stencil_Max = 16;
            psSelect->m_sNode[uiNode].m_nuiData_Buffers_Max = 32;
        }
    }

    /* Create a swap-chain per window (i.e. not associated with an output device) based on the original window. */

    bSingle |= 9 > KTgKN_GPU_MAX_SWAP_CONTEXT;
    for (uiOutput = bSingle ? 4u : 0u; (bSingle || uiOutput < KTgKN_MAX_WINDOWS) && psSelect->m_nuiOutput < KTgKN_GPU_MAX_SWAP_CONTEXT; ++uiOutput)
    {
        TgRSIZE                             uiNode_Index = 0;//(uiOutput >= 6 ? 1 : 0) % psSelect->m_nuiNode; // Test multiple nodes

        ETgKN_GPU_EXT_FORMAT                aenTarget[3] = { ETgKN_GPU_EXT_FORMAT_R8G8B8A8_UNORM, ETgKN_GPU_EXT_FORMAT_A2B10G10R10_UNORM_PACK32, ETgKN_GPU_EXT_FORMAT_R16G16B16A16_SFLOAT };
        ETgKN_GPU_EXT_FORMAT                enFormat;

        enFormat = *(aenTarget + tgCM_MIN_UMAX( uiOutput % 3, TgARRAY_COUNT( aenTarget ) ));

        if (ETgKN_GPU_EXT_FORMAT_UNDEFINED == enFormat)
        {
            if (bSingle)
            {
                break;
            }
            else
            {
                continue;
            }
        }

        psSelect->m_sOutput[psSelect->m_nuiOutput].m_fMin_Mastering_Nits = 0.1000F;
        psSelect->m_sOutput[psSelect->m_nuiOutput].m_fMax_Mastering_Nits = 1000.0F;
        psSelect->m_sOutput[psSelect->m_nuiOutput].m_fMax_Content_Light_Level = 2000.0F;
        psSelect->m_sOutput[psSelect->m_nuiOutput].m_fMax_Frame_Average_Light_Level = 500.0F;
        psSelect->m_sOutput[psSelect->m_nuiOutput].m_uiNode_Index = uiNode_Index;
        psSelect->m_sOutput[psSelect->m_nuiOutput].m_uiMSAA_Sample = 1;
        psSelect->m_sOutput[psSelect->m_nuiOutput].m_enFormat_DS = ETgKN_GPU_EXT_FORMAT_D32_SFLOAT;
        psSelect->m_sOutput[psSelect->m_nuiOutput].m_uiOutput_Config.m_nuiSwap_Buffers = 2;
        psSelect->m_sOutput[psSelect->m_nuiOutput].m_uiOutput_Config.m_uiStereo = 0;
        psSelect->m_sOutput[psSelect->m_nuiOutput].m_uiOutput_Config.m_uiVSync = 0;
        psSelect->m_sOutput[psSelect->m_nuiOutput].m_uiOutput_Config.m_bHDR_Request = 0 == (uiOutput % 3) ? 0u : 1u; // Test HDR / LDR
        psSelect->m_sOutput[psSelect->m_nuiOutput].m_uiOutput_Config.m_bFullscreen = 0;
        psSelect->m_sOutput[psSelect->m_nuiOutput].m_uiOS_ID = 0;
        psSelect->m_sOutput[psSelect->m_nuiOutput].m_sMode.m_sBuffer.m_enFormat = enFormat;
        psSelect->m_sOutput[psSelect->m_nuiOutput].m_sMode.m_sBuffer.m_uiHeight = 768;
        psSelect->m_sOutput[psSelect->m_nuiOutput].m_sMode.m_sBuffer.m_uiWidth = 1024;
        psSelect->m_sOutput[psSelect->m_nuiOutput].m_sMode.m_uiRefresh_Rate__Denominator = 1;
        psSelect->m_sOutput[psSelect->m_nuiOutput].m_sMode.m_uiRefresh_Rate__Numerator = 60;

        ++psSelect->m_nuiOutput;

        if (bSingle)
        {
            break;
        }
    }

    if (0 == psSelect->m_nuiOutput)
    {
        return (KTgE_FAIL);
    }

/*# defined(TgBUILD_FEATURE__GRAPHICS) */
#endif
    return (KTgS_OK);
}
