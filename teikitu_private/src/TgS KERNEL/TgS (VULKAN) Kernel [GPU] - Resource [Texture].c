/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (VULKAN) Kernel [GPU] - Resource [Texture].c
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
#if defined (ENABLE_RELOAD_GUARD)

// -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. //
//  Internal Functions
// -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. //

/* ---- Resource - GPU - Texture - API ------------------------------------------------------------------------------------------------------------------------------------------- */

/* ---- T(tgKN_GPU_EXT_,__Execute_Load) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT T(tgKN_GPU_EXT_,__Execute_Load)(
    TgATTRIBUTE_UNUSED TgKN_FILE_ID_C ARG0, TgATTRIBUTE_UNUSED TgRSIZE_C ARG1, TgATTRIBUTE_UNUSED T(STg2_KN_GPU_,_DESC_CPC) ARG2,
    TgATTRIBUTE_UNUSED TgUINT_E64_C ARG3, TgATTRIBUTE_UNUSED T(TgKN_GPU_,_ID_C) ARG4 )
{
    return (KTgS_OK);
}


/* ---- T(tgKN_GPU_EXT_,__Execute_Free) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID T(tgKN_GPU_EXT_,__Execute_Free)( TgATTRIBUTE_UNUSED T(TgKN_GPU_,_ID_C) sID )
{

}


/* ---- T(tgKN_GPU_EXT__CMD__,_Inst__Init) --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT T(tgKN_GPU_EXT__CMD__,_Inst__Init)( STg2_KN_GPU_CMD_PC psCMD, T(TgKN_GPU_,_INST_ID_C) sID_Inst, TgCHAR_U8_CPCU uszName )
{
    UTg2_KN_GPU_CMD_C                           uCMD = { .ps = psCMD };
    TgRSIZE                             uiEXEC = (uCMD.psVLKN->m_sBase.m_tiCXT_WORK.m_uiI >> 16) & 0xFFFF;
    STg2_KN_GPU_CXT_EXEC_PC             psCXT_EXEC = g_asKN_GPU_CXT_EXEC + uiEXEC;
    STg2_KN_GPU_VLKN_CXT_EXEC_PC        psVLKN_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + uiEXEC;
    VkPhysicalDeviceMemoryProperties_C  sMemory_Properties = uCMD.psVLKN->m_sVLKN_Memory_Properties.memoryProperties;

    T(STg2_KN_GPU_VLKN_,_INST_DATA_P)   T(psEXT_,_INST);
    T(STg2_KN_GPU_,_DATA_P)             T(ps,);
    VkImageCreateInfo                   sImage_CI;
    VkMemoryRequirements                sMemory_Requirements;
    VkMemoryAllocateInfo                sAllocInfo;
    VkResult                            eResult;
    TgUINT_E32                          uiMemory_Type_Index;
    VkMemoryPropertyFlags               uiMemory_Property_Flags;
    TgUINT_E32                          uiIndex;
    VkImageViewCreateInfo               sImage_View_CI;

    TgPARAM_CHECK_KN_GPU_CMD(psCMD);
    TgVERIFY( sID_Inst.m_uiCXT == uiEXEC );

    /* Initialize the Vulkan instance data. */
    T(psEXT_,_INST) = psVLKN_CXT_EXEC->T(m_as,_INST) + sID_Inst.m_uiIndex;
    T(psEXT_,_INST)->m_sID = psCXT_EXEC->T(m_s,_Inst_LIB_DESC).m_psRS[sID_Inst.m_uiIndex];
    T(psEXT_,_INST)->m_bInitialized = false;
    T(ps,) = T(g_asKN_Lib_,_Data) + T(psEXT_,_INST)->m_sID.m_uiIndex;

    /* Create image */
    tgMM_Set_U08_0x00( &sImage_CI, sizeof(sImage_CI) );
    sImage_CI.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    sImage_CI.mipLevels = (TgUINT_E32)(T(ps,)->m_sTX.m_nuiMIP);
    sImage_CI.format = (VkFormat)(T(ps,)->m_sTX.m_enFormat);
    sImage_CI.tiling = VK_IMAGE_TILING_OPTIMAL;
    sImage_CI.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    sImage_CI.usage = tgKN_GPU_VLKN_Convert_Image_Usage(T(ps,)->m_sTX.m_uiResource_Descriptor);
    sImage_CI.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    sImage_CI.samples = VK_SAMPLE_COUNT_1_BIT;
TgCLANG_WARN_DISABLE_PUSH(invalid-token-paste)
    TgMACRO_ASSIGN_IMAGE_CREATE_INFO(sImage_CI, T(ps,));
TgCLANG_WARN_DISABLE_POP(invalid-token-paste)

    eResult = vkCreateImage(uCMD.psVLKN->m_hVLKN_Device, &sImage_CI, g_psKN_GPU_VLKN_Allocator, &T(psEXT_,_INST)->m_hVLKN_Image);
    if (eResult != VK_SUCCESS)
    {
        TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create image" );
        return (KTgE_FAIL);
    };

    /* Get memory requirements */
    vkGetImageMemoryRequirements(uCMD.psVLKN->m_hVLKN_Device, T(psEXT_,_INST)->m_hVLKN_Image, &sMemory_Requirements);

    /* Find suitable memory type */
    uiMemory_Type_Index = UINT32_MAX;
    uiMemory_Property_Flags = tgKN_GPU_VLKN_Convert_Memory_Properties(T(ps,)->m_sTX.m_uiResource_Descriptor);
    for (uiIndex = 0; uiIndex < sMemory_Properties.memoryTypeCount; ++uiIndex)
    {
        if ((sMemory_Requirements.memoryTypeBits & (1 << uiIndex)) && (sMemory_Properties.memoryTypes[uiIndex].propertyFlags & uiMemory_Property_Flags) == uiMemory_Property_Flags)
        {
            uiMemory_Type_Index = uiIndex;
        };
    };

    if (uiMemory_Type_Index == UINT32_MAX)
    {
        TgERROR_MSG( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to find suitable memory type" );
        vkDestroyImage(uCMD.psVLKN->m_hVLKN_Device, T(psEXT_,_INST)->m_hVLKN_Image, g_psKN_GPU_VLKN_Allocator);
        return (KTgE_FAIL);
    };

    /* Allocate memory */
    tgMM_Set_U08_0x00( &sAllocInfo, sizeof(sAllocInfo) );
    sAllocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    sAllocInfo.allocationSize = sMemory_Requirements.size;
    sAllocInfo.memoryTypeIndex = uiMemory_Type_Index;

    eResult = vkAllocateMemory(uCMD.psVLKN->m_hVLKN_Device, &sAllocInfo, g_psKN_GPU_VLKN_Allocator, &T(psEXT_,_INST)->m_hVLKN_Image_Memory);
    if (eResult != VK_SUCCESS)
    {
        TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to allocate image memory" );
        vkDestroyImage(uCMD.psVLKN->m_hVLKN_Device, T(psEXT_,_INST)->m_hVLKN_Image, g_psKN_GPU_VLKN_Allocator);
        return (KTgE_FAIL);
    };

    /* Bind memory to image */
    vkBindImageMemory(uCMD.psVLKN->m_hVLKN_Device, T(psEXT_,_INST)->m_hVLKN_Image, T(psEXT_,_INST)->m_hVLKN_Image_Memory, 0);

    tgMM_Set_U08_0x00( &sImage_View_CI, sizeof( sImage_View_CI ) );
    sImage_View_CI.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    sImage_View_CI.image = T(psEXT_,_INST)->m_hVLKN_Image;
    sImage_View_CI.format = sImage_CI.format;
    sImage_View_CI.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    sImage_View_CI.subresourceRange.baseMipLevel = 0;
    sImage_View_CI.subresourceRange.levelCount = sImage_CI.mipLevels;
    sImage_View_CI.subresourceRange.baseArrayLayer = 0;
TgCLANG_WARN_DISABLE_PUSH(invalid-token-paste)
    TgMACRO_ASSIGN_IMAGE_VIEW_CREATE_INFO(sImage_View_CI);
TgCLANG_WARN_DISABLE_POP(invalid-token-paste)

    eResult = vkCreateImageView(uCMD.psVLKN->m_hVLKN_Device, &sImage_View_CI, g_psKN_GPU_VLKN_Allocator, &T(psEXT_,_INST)->m_hVLKN_Image_View);
    if (eResult != VK_SUCCESS)
    {
        TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create image view" );
        T(tgKN_GPU_EXT__CMD__,_Inst__Free)( psCMD, sID_Inst );
        return (KTgE_FAIL);
    };

#if defined(TgCOMPILE__GPU_OBJECT_NAME) && TgCOMPILE__GPU_OBJECT_NAME
    {
        TgCHAR_U8                           uszDebugName[128];

        tgUSZ_PrintF( uszDebugName, sizeof( uszDebugName ), T_USZ(tgKN_GPU_EXT__CMD__,_Inst__Init) );
        if (uszName)
        {
            tgUSZ_AppendF( uszDebugName, sizeof( uszDebugName ), u8" (%s)", uszName );
        };
    TgMACRO_KN_GPU_VLKN_SET_NAME(uCMD.psVLKN->m_hVLKN_Device, VK_OBJECT_TYPE_IMAGE, T(psEXT_,_INST)->m_hVLKN_Image, uszDebugName);
    }
#else
    (void)uszName;
/*# defined(TgCOMPILE__GPU_OBJECT_NAME) && TgCOMPILE__GPU_OBJECT_NAME */
#endif

    return (KTgS_OK);
}


/* ---- T(tgKN_GPU_EXT__CMD__,_Inst__Free) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID T(tgKN_GPU_EXT__CMD__,_Inst__Free)( STg2_KN_GPU_CMD_PC psCMD, T(TgKN_GPU_,_INST_ID_C) sID_Inst )
{
    UTg2_KN_GPU_CMD_C                           uCMD = { .ps = psCMD };
    TgRSIZE                             uiEXEC = (uCMD.psVLKN->m_sBase.m_tiCXT_WORK.m_uiI >> 16) & 0xFFFF;
    STg2_KN_GPU_VLKN_CXT_EXEC_PC        psVLKN_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + uiEXEC;
    T(STg2_KN_GPU_VLKN_,_INST_DATA_PC)   T(psEXT_,_INST) = psVLKN_CXT_EXEC->T(m_as,_INST) + sID_Inst.m_uiIndex;

    if (VK_NULL_HANDLE != T(psEXT_,_INST)->m_hVLKN_Image_View)
    {
        vkDestroyImageView(uCMD.psVLKN->m_hVLKN_Device, T(psEXT_,_INST)->m_hVLKN_Image_View, g_psKN_GPU_VLKN_Allocator);
        T(psEXT_,_INST)->m_hVLKN_Image_View = VK_NULL_HANDLE;
    }

    if (VK_NULL_HANDLE != T(psEXT_,_INST)->m_hVLKN_Image_Memory)
    {
        vkFreeMemory(uCMD.psVLKN->m_hVLKN_Device, T(psEXT_,_INST)->m_hVLKN_Image_Memory, g_psKN_GPU_VLKN_Allocator);
        T(psEXT_,_INST)->m_hVLKN_Image_Memory = VK_NULL_HANDLE;
    }

    if (VK_NULL_HANDLE != T(psEXT_,_INST)->m_hVLKN_Image)
    {
        vkDestroyImage(uCMD.psVLKN->m_hVLKN_Device, T(psEXT_,_INST)->m_hVLKN_Image, g_psKN_GPU_VLKN_Allocator);
        T(psEXT_,_INST)->m_hVLKN_Image = VK_NULL_HANDLE;
    }

    T(psEXT_,_INST)->m_sID = T(KTgKN_GPU_,_ID__INVALID);
}


/* ---- T(tgKN_GPU_EXT__CMD__,__Fast_Lock) --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID T(tgKN_GPU_EXT__CMD__,__Fast_Lock)( STg2_KN_GPU_TX_LOCK_PCU psOUT, STg2_KN_GPU_CMD_PC psCMD, T(TgKN_GPU_,_INST_ID_C) sID_Inst )
{
    /* Fast functions not supported on PC: meant only to be used on hardware that supports unified memory. */
    T(tgKN_GPU_EXT__CMD__,__Lock)( psOUT, psCMD, sID_Inst );
}


/* ---- T(tgKN_GPU_EXT__CMD__,__Lock) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID T(tgKN_GPU_EXT__CMD__,__Lock)( STg2_KN_GPU_TX_LOCK_PCU psOUT, STg2_KN_GPU_CMD_PC psCMD, T(TgKN_GPU_,_INST_ID_C) sID_Inst )
{
    UTg2_KN_GPU_CMD_C                           uCMD = { .ps = psCMD };
    TgRSIZE                             uiEXEC = (uCMD.psVLKN->m_sBase.m_tiCXT_WORK.m_uiI >> 16) & 0xFFFF;
    STg2_KN_GPU_VLKN_CXT_EXEC_PC        psVLKN_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + uiEXEC;

    typedef struct
    {
        VkBuffer                            hStaging_Buffer;
        VkDeviceMemory                      hStaging_Memory;
    } VLKN_Buffer;

    union
    {
        TgUINT_E08_P                        puiTMP_Upload_Data;
        VLKN_Buffer*                        psVLKN_Buffer;
    }                                   uEXT_Resource;

    T(STg2_KN_GPU_VLKN_,_INST_DATA_P)   T(psEXT_,_INST);
    T(STg2_KN_GPU_,_DATA_P)             T(ps,);
    VkResult                            eResult;
    TgUINT_E64                          uiResource_Descriptor;

    TgPARAM_CHECK_KN_GPU_CMD(psCMD);
    TgVERIFY( sID_Inst.m_uiCXT == uiEXEC );
    TgCOMPILER_ASSERT(sizeof(uEXT_Resource) <= sizeof(((STg2_KN_GPU_TX_LOCK_P)0)->m_auiTMP_Upload_Data), 0);

    T(psEXT_,_INST) = psVLKN_CXT_EXEC->T(m_as,_INST) + sID_Inst.m_uiIndex;
    T(ps,) = T(g_asKN_Lib_,_Data) + T(psEXT_,_INST)->m_sID.m_uiIndex;

    TgPARAM_CHECK( T(ps,)->m_sTX.m_nuiMIP < 32 );

    tgMM_Set_U08_0x00( psOUT, sizeof( STg2_KN_GPU_TX_LOCK ) );
    T(tgKN_GPU_EXT_, _Init_Lock)( psOUT, T(ps, ) );
    uEXT_Resource.puiTMP_Upload_Data = psOUT->m_auiTMP_Upload_Data;

    /* Create a staging buffer for all mip levels */

    uiResource_Descriptor  = ETgKN_GPU_RESOURCE_DESCRIPTOR__UPLOAD_BUFFER;
    uiResource_Descriptor |= ETgKN_GPU_RESOURCE_DESCRIPTOR__MEMORY_HOST_VISIBLE;
    uiResource_Descriptor |= ETgKN_GPU_RESOURCE_DESCRIPTOR__MEMORY_HOST_COHERENT;

    if (TgFAILED(tgKN_GPU_VLKN__CMD__Create_Buffer( &uEXT_Resource.psVLKN_Buffer->hStaging_Buffer, &uEXT_Resource.psVLKN_Buffer->hStaging_Memory, uCMD.psVLKN, uiResource_Descriptor,
                                                    psOUT->m_nbyTotal, nullptr, 0)))
    {
        TgERROR_MSG( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create staging buffer" );
        return;
    }

    eResult = vkMapMemory(uCMD.psVLKN->m_hVLKN_Device, uEXT_Resource.psVLKN_Buffer->hStaging_Memory, 0, psOUT->m_nbyTotal, 0, (TgVOID_PP)(&psOUT->m_puiData));
    if (eResult != VK_SUCCESS)
    {
        TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to map memory" );
        return;
    }

#if defined(TgCOMPILE__GPU_OBJECT_NAME) && TgCOMPILE__GPU_OBJECT_NAME
    {
        TgCHAR_U8                           uszDebugName[128];

        tgUSZ_Append( uszDebugName, sizeof( uszDebugName ), u8" Locked Surface", KTgMAX_RSIZE );
        TgMACRO_KN_GPU_VLKN_SET_NAME( uCMD.psVLKN->m_hVLKN_Device, VK_OBJECT_TYPE_BUFFER, uEXT_Resource.psVLKN_Buffer->hStaging_Buffer, uszDebugName );
    }
/*# defined(TgCOMPILE__GPU_OBJECT_NAME) && TgCOMPILE__GPU_OBJECT_NAME */
#endif
}


/* ---- T(tgKN_GPU_EXT__CMD__,__Fast_Unlock) ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID T(tgKN_GPU_EXT__CMD__,__Fast_Unlock)( STg2_KN_GPU_CMD_PC psCMD, STg2_KN_GPU_TX_LOCK_PCU psSurface, T(TgKN_GPU_,_INST_ID_C) sID_Inst )
{
    /* Fast functions not supported on PC: meant only to be used on hardware that supports unified memory. */
    T(tgKN_GPU_EXT__CMD__,__Unlock)( psCMD, psSurface, sID_Inst );
}


/* ---- T(tgKN_GPU_EXT__CMD__,__Unlock) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID T(tgKN_GPU_EXT__CMD__,__Unlock)( STg2_KN_GPU_CMD_PC psCMD, STg2_KN_GPU_TX_LOCK_PCU psSurface, T(TgKN_GPU_,_INST_ID_C) sID_Inst )
{
    typedef struct
    {
        VkBuffer                            hStaging_Buffer;
        VkDeviceMemory                      hStaging_Memory;
    } VLKN_Buffer;

    union
    {
        TgUINT_E08_P                        puiTMP_Upload_Data;
        VLKN_Buffer*                        psVLKN_Buffer;
    } const                             uEXT_Resource = { .puiTMP_Upload_Data = psSurface->m_auiTMP_Upload_Data };
    UTg2_KN_GPU_CMD_C                           uCMD = { .ps = psCMD };
    TgRSIZE_C                           uiEXEC = (uCMD.psVLKN->m_sBase.m_tiCXT_WORK.m_uiI >> 16) & 0xFFFF;
    STg2_KN_GPU_VLKN_CXT_EXEC_PC        psVLKN_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + uiEXEC;

    T(STg2_KN_GPU_VLKN_,_INST_DATA_P)    T(psEXT_,_INST);
    T(STg2_KN_GPU_,_DATA_P)             T(ps,);
    VkImageLayout                       enVLKN_Old_Layout;
    VkBufferImageCopy                   asVLKN_Copy_Regions[32];
    TgRSIZE                             nuiCopy_Regions;

    TgPARAM_CHECK_KN_GPU_CMD(psCMD);
    TgVERIFY( sID_Inst.m_uiCXT == uiEXEC );

    T(psEXT_,_INST) = psVLKN_CXT_EXEC->T(m_as,_INST) + sID_Inst.m_uiIndex;
    T(ps,) = T(g_asKN_Lib_,_Data) + T(psEXT_,_INST)->m_sID.m_uiIndex;

    vkUnmapMemory(uCMD.psVLKN->m_hVLKN_Device, uEXT_Resource.psVLKN_Buffer->hStaging_Memory);

    enVLKN_Old_Layout = T(psEXT_,_INST)->m_bInitialized ?  VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL : VK_IMAGE_LAYOUT_UNDEFINED;
    tgKN_GPU_EXT__CMD__Transition_Image_Layout(
         psCMD, T(psEXT_,_INST)->m_hVLKN_Image, &T(ps,)->m_sTX, enVLKN_Old_Layout, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL );

    T(tgKN_GPU_EXT_,_MIP_Regions)( asVLKN_Copy_Regions, &nuiCopy_Regions, TgARRAY_COUNT(asVLKN_Copy_Regions), T(ps,) );
    
    // Perform the copy operation for all mip levels at once
    vkCmdCopyBufferToImage(
        uCMD.psVLKN->m_hVLKN_Command_Buffer,
        uEXT_Resource.psVLKN_Buffer->hStaging_Buffer,
        T(psEXT_,_INST)->m_hVLKN_Image,
        VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
        (uint32_t)nuiCopy_Regions,
        asVLKN_Copy_Regions
    );
    
    tgKN_GPU_EXT__CMD__Transition_Image_Layout(
        psCMD, T(psEXT_,_INST)->m_hVLKN_Image, &T(ps,)->m_sTX, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL );

    T(psEXT_,_INST)->m_bInitialized = true;

    tgKN_GPU_VLKN__CMD__Register_Resource_For_Release( psCMD, uEXT_Resource.psVLKN_Buffer->hStaging_Buffer, uEXT_Resource.psVLKN_Buffer->hStaging_Memory );
}




// -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. //
//  Internal Functions
// -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. //

/* ---- T(tgKN_GPU_EXT__CMD__Register_Default_,_Inst) ---------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRSIZE T(tgKN_GPU_EXT__CMD__Register_Default_,_Inst)( STg2_KN_GPU_CMD_PC psCMD, T(TgKN_GPU_,_INST_ID_C) sID_Inst, ETgKN_GPU_DEFAULT_SAMPLER_C enSampler )
{
    UTg2_KN_GPU_CMD_C                           uCMD = { .ps = psCMD };
    TgRSIZE                             uiEXEC = (uCMD.psVLKN->m_sBase.m_tiCXT_WORK.m_uiI >> 16) & 0xFFFF;
    STg2_KN_GPU_VLKN_CXT_EXEC_PC        psVLKN_CXT_EXEC = g_asKN_GPU_EXT_CXT_EXEC + uiEXEC;
    T(STg2_KN_GPU_VLKN_,_INST_DATA_PC)  T(psEXT_,_INST) = psVLKN_CXT_EXEC->T(m_as,_INST) + sID_Inst.m_uiIndex;
    TgRSIZE_C                           uiIndex = TgSTD_ATOMIC(fetch_add)(&psVLKN_CXT_EXEC->T(m_xnui, _INST), 1);
    
    if (uiIndex >= T(KTgKN_GPU_MAX_, _INST))
    {
        TgERROR_MSGF(0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Texture index exceeds maximum default texture count");
        return (0);
    }

    // Set up descriptor image info
    psVLKN_CXT_EXEC->T(m_asVLKN_DS_Info_)[uiIndex].imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    psVLKN_CXT_EXEC->T(m_asVLKN_DS_Info_)[uiIndex].imageView = T(psEXT_,_INST)->m_hVLKN_Image_View;
    psVLKN_CXT_EXEC->T(m_asVLKN_DS_Info_)[uiIndex].sampler = psVLKN_CXT_EXEC->m_ahVLKN_Sampler[enSampler];

    return (uiIndex);
}

#else

// -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. //
//  File Local Functions
// -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. //

static TgVOID
tgKN_GPU_EXT__CMD__Transition_Image_Layout(
     STg2_KN_GPU_CMD_PC ARG0, VkImage ARG1, TgANALYSIS_NO_NULL STg2_KN_TX_CPC ARG2, VkImageLayout ARG3, VkImageLayout ARG4 );

static TgVOID
tgKN_GPU_EXT_TX_CBE_Init_Lock(
    TgANALYSIS_NO_NULL STg2_KN_GPU_TX_LOCK_PCU psOUT, TgANALYSIS_NO_NULL STg2_KN_GPU_TX_CBE_DATA_CPC ARG1 );

static TgVOID
tgKN_GPU_EXT_TX_IMG_Init_Lock(
    TgANALYSIS_NO_NULL STg2_KN_GPU_TX_LOCK_PCU psOUT, TgANALYSIS_NO_NULL STg2_KN_GPU_TX_IMG_DATA_CPC ARG1 );

static TgVOID
tgKN_GPU_EXT_TX_VOL_Init_Lock(
    TgANALYSIS_NO_NULL STg2_KN_GPU_TX_LOCK_PCU psOUT, TgANALYSIS_NO_NULL STg2_KN_GPU_TX_VOL_DATA_CPC ARG1 );

static TgVOID
tgKN_GPU_EXT_TX_CBE_MIP_Regions(
    TgANALYSIS_NO_NULL VkBufferImageCopy_PC OUT0, TgANALYSIS_NO_NULL TgRSIZE_PC OUT1, TgRSIZE_C ARG2, STg2_KN_GPU_TX_CBE_DATA_CPC ARG3 );

static TgVOID
tgKN_GPU_EXT_TX_IMG_MIP_Regions(
    TgANALYSIS_NO_NULL VkBufferImageCopy_PC OUT0, TgANALYSIS_NO_NULL TgRSIZE_PC OUT1, TgRSIZE_C ARG2, STg2_KN_GPU_TX_IMG_DATA_CPC ARG3 );

static TgVOID
tgKN_GPU_EXT_TX_VOL_MIP_Regions(
    TgANALYSIS_NO_NULL VkBufferImageCopy_PC OUT0, TgANALYSIS_NO_NULL TgRSIZE_PC OUT1, TgRSIZE_C ARG2, STg2_KN_GPU_TX_VOL_DATA_CPC ARG3 );




// -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. //
//  File Local Functions
// -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. //

/* ---- tgKN_GPU_EXT__CMD__Transition_Image_Layout ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgKN_GPU_EXT__CMD__Transition_Image_Layout( STg2_KN_GPU_CMD_PC psCMD, VkImage hImage, STg2_KN_TX_CPC psTX, VkImageLayout enOldLayout, VkImageLayout enNewLayout )
{
    UTg2_KN_GPU_CMD_C                           uCMD = { .ps = psCMD };

    VkImageMemoryBarrier                sMemory_Barrier;
    VkPipelineStageFlags                enSourceStage;
    VkPipelineStageFlags                enDestinationStage;

    // Transition image layout to transfer destination
    tgMM_Set_U08_0x00( &sMemory_Barrier, sizeof( VkImageMemoryBarrier ) );
    sMemory_Barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    sMemory_Barrier.oldLayout = enOldLayout;
    sMemory_Barrier.newLayout = enNewLayout;
    sMemory_Barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    sMemory_Barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    sMemory_Barrier.image = hImage;
    sMemory_Barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    sMemory_Barrier.subresourceRange.baseMipLevel = 0;
    sMemory_Barrier.subresourceRange.levelCount = psTX->m_nuiMIP;
    sMemory_Barrier.subresourceRange.baseArrayLayer = 0;
    sMemory_Barrier.subresourceRange.layerCount = 1;

    /* Handle depth/stencil formats */
    if (enNewLayout == VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL)
    {
        sMemory_Barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
        if (psTX->m_enFormat == ETgKN_GPU_EXT_FORMAT_D24_UNORM_S8_UINT)
        {
            sMemory_Barrier.subresourceRange.aspectMask |= VK_IMAGE_ASPECT_STENCIL_BIT;
        }
    }

    /* Determine access masks and pipeline stages */
    if (enOldLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL && enNewLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL)
    {
        sMemory_Barrier.srcAccessMask = VK_ACCESS_SHADER_READ_BIT;
        sMemory_Barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        enSourceStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
        enDestinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
    }
    else if (enOldLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && enNewLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL)
    {
        sMemory_Barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        sMemory_Barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
        enSourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
        enDestinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
    }
    else if (enOldLayout == VK_IMAGE_LAYOUT_UNDEFINED && enNewLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL)
    {
        sMemory_Barrier.srcAccessMask = 0;
        sMemory_Barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        enSourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
        enDestinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
    }
    else
    {
        /* Generic transition */
        sMemory_Barrier.srcAccessMask = 0;
        sMemory_Barrier.dstAccessMask = 0;
        enSourceStage = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT;
        enDestinationStage = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT;
    }

    vkCmdPipelineBarrier(uCMD.psVLKN->m_hVLKN_Command_Buffer, enSourceStage, enDestinationStage, 0, 0, nullptr, 0, nullptr, 1, &sMemory_Barrier);
}


/* ---- tgKN_GPU_EXT_TX_CBE_Init_Lock -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgKN_GPU_EXT_TX_CBE_Init_Lock( STg2_KN_GPU_TX_LOCK_PCU psOUT, STg2_KN_GPU_TX_CBE_DATA_CPC psTX_CBE )
{
    for (psOUT->m_nbyTotal = 0, psOUT->m_nuiMip_Levels_Locked = 0; psOUT->m_nuiMip_Levels_Locked < psTX_CBE->m_sTX.m_nuiMIP; ++psOUT->m_nuiMip_Levels_Locked) {
        VkDeviceSize_C                      uiEdge = tgCM_MAX_UMAX(psTX_CBE->m_uiEdge >> psOUT->m_nuiMip_Levels_Locked, 1u);

        psOUT->m_asLayout[psOUT->m_nuiMip_Levels_Locked].m_nuiRow = uiEdge;
        psOUT->m_asLayout[psOUT->m_nuiMip_Levels_Locked].m_nbyRow = uiEdge * tgKN_GPU_FMT_Bytes_Per_Pixel(psTX_CBE->m_sTX.m_enFormat);
        psOUT->m_asLayout[psOUT->m_nuiMip_Levels_Locked].m_nbyRow_Pitch = psOUT->m_asLayout[psOUT->m_nuiMip_Levels_Locked].m_nbyRow;
        psOUT->m_nbyTotal += psOUT->m_asLayout[psOUT->m_nuiMip_Levels_Locked].m_nuiRow * psOUT->m_asLayout[psOUT->m_nuiMip_Levels_Locked].m_nbyRow * 6;
    }
}


/* ---- tgKN_GPU_EXT_TX_IMG_Init_Lock -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgKN_GPU_EXT_TX_IMG_Init_Lock( STg2_KN_GPU_TX_LOCK_PCU psOUT, STg2_KN_GPU_TX_IMG_DATA_CPC psTX_IMG )
{
    for (psOUT->m_nbyTotal = 0, psOUT->m_nuiMip_Levels_Locked = 0; psOUT->m_nuiMip_Levels_Locked < psTX_IMG->m_sTX.m_nuiMIP; ++psOUT->m_nuiMip_Levels_Locked) {
        VkDeviceSize_C                      uiWidth = tgCM_MAX_UMAX(psTX_IMG->m_uiWidth >> psOUT->m_nuiMip_Levels_Locked, 1u);
        VkDeviceSize_C                      uiHeight = tgCM_MAX_UMAX(psTX_IMG->m_uiHeight >> psOUT->m_nuiMip_Levels_Locked, 1u);

        psOUT->m_asLayout[psOUT->m_nuiMip_Levels_Locked].m_nuiRow = uiHeight;
        psOUT->m_asLayout[psOUT->m_nuiMip_Levels_Locked].m_nbyRow = uiWidth * tgKN_GPU_FMT_Bytes_Per_Pixel(psTX_IMG->m_sTX.m_enFormat);
        psOUT->m_asLayout[psOUT->m_nuiMip_Levels_Locked].m_nbyRow_Pitch = psOUT->m_asLayout[psOUT->m_nuiMip_Levels_Locked].m_nbyRow;
        psOUT->m_nbyTotal += psOUT->m_asLayout[psOUT->m_nuiMip_Levels_Locked].m_nuiRow * psOUT->m_asLayout[psOUT->m_nuiMip_Levels_Locked].m_nbyRow;
    }
}


/* ---- tgKN_GPU_EXT_TX_VOL_Init_Lock -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgKN_GPU_EXT_TX_VOL_Init_Lock( STg2_KN_GPU_TX_LOCK_PCU psOUT, STg2_KN_GPU_TX_VOL_DATA_CPC psTX_VOL )
{
    for (psOUT->m_nbyTotal = 0, psOUT->m_nuiMip_Levels_Locked = 0; psOUT->m_nuiMip_Levels_Locked < psTX_VOL->m_sTX.m_nuiMIP; ++psOUT->m_nuiMip_Levels_Locked) {
        VkDeviceSize_C                      uiWidth = tgCM_MAX_UMAX(psTX_VOL->m_uiWidth >> psOUT->m_nuiMip_Levels_Locked, 1u);
        VkDeviceSize_C                      uiHeight = tgCM_MAX_UMAX(psTX_VOL->m_uiHeight >> psOUT->m_nuiMip_Levels_Locked, 1u);
        VkDeviceSize_C                      uiDepth = tgCM_MAX_UMAX(psTX_VOL->m_uiDepth >> psOUT->m_nuiMip_Levels_Locked, 1u);

        psOUT->m_asLayout[psOUT->m_nuiMip_Levels_Locked].m_nuiRow = uiHeight;
        psOUT->m_asLayout[psOUT->m_nuiMip_Levels_Locked].m_nbyRow = uiWidth * tgKN_GPU_FMT_Bytes_Per_Pixel(psTX_VOL->m_sTX.m_enFormat);
        psOUT->m_asLayout[psOUT->m_nuiMip_Levels_Locked].m_nbyRow_Pitch = psOUT->m_asLayout[psOUT->m_nuiMip_Levels_Locked].m_nbyRow;
        psOUT->m_nbyTotal += psOUT->m_asLayout[psOUT->m_nuiMip_Levels_Locked].m_nuiRow * psOUT->m_asLayout[psOUT->m_nuiMip_Levels_Locked].m_nbyRow * uiDepth;
    }
}


/* ---- tgKN_GPU_EXT_TX_CBE_MIP_Regions ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgKN_GPU_EXT_TX_CBE_MIP_Regions( VkBufferImageCopy_PC asCopy_Regions, TgRSIZE_PC puiMIP, TgRSIZE_C nuiCopy_Regions, STg2_KN_GPU_TX_CBE_DATA_CPC psTX_CBE )
{
    TgRSIZE                             uiMIP, uiFace, uiCopy_Region, uiOffset;

    for (uiCopy_Region = 0, uiMIP = 0, uiOffset = 0; uiMIP < psTX_CBE->m_sTX.m_nuiMIP; ++uiMIP) {
        VkDeviceSize_C                      uiEdge = tgCM_MAX_UMAX(psTX_CBE->m_uiEdge >> uiMIP, 1u);

        for (uiFace = 0; uiFace < 6 && uiCopy_Region < nuiCopy_Regions; ++uiFace, ++uiCopy_Region) {
            tgMM_Set_U08_0x00( asCopy_Regions + uiCopy_Region, sizeof( asCopy_Regions[0] ) );
            asCopy_Regions[uiCopy_Region].bufferOffset = uiOffset;
            asCopy_Regions[uiCopy_Region].bufferRowLength = 0;
            asCopy_Regions[uiCopy_Region].bufferImageHeight = 0;
            asCopy_Regions[uiCopy_Region].imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            asCopy_Regions[uiCopy_Region].imageSubresource.mipLevel = (uint32_t)uiMIP;
            asCopy_Regions[uiCopy_Region].imageSubresource.baseArrayLayer = (uint32_t)uiFace;
            asCopy_Regions[uiCopy_Region].imageSubresource.layerCount = 1;
            asCopy_Regions[uiCopy_Region].imageOffset.x = 0;
            asCopy_Regions[uiCopy_Region].imageOffset.y = 0;
            asCopy_Regions[uiCopy_Region].imageOffset.z = 0;
            asCopy_Regions[uiCopy_Region].imageExtent.width = (uint32_t)uiEdge;
            asCopy_Regions[uiCopy_Region].imageExtent.height = (uint32_t)uiEdge;
            asCopy_Regions[uiCopy_Region].imageExtent.depth = 1;

            uiOffset += uiEdge * uiEdge * 4;  // 4 bytes per pixel
        }
    }

    *puiMIP = uiMIP;
}


/* ---- tgKN_GPU_EXT_TX_IMG_MIP_Regions ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgKN_GPU_EXT_TX_IMG_MIP_Regions( VkBufferImageCopy_PC asCopy_Regions, TgRSIZE_PC puiMIP, TgRSIZE_C nuiCopy_Regions, STg2_KN_GPU_TX_IMG_DATA_CPC psTX_IMG )
{
    TgRSIZE                             uiMIP, uiCopy_Region, uiOffset;

    /* Copy buffer to image for each mip level. There is a wacky consideration if the undelying texture descripotion changes after the lock and before the unlock.*/
    for (uiCopy_Region = 0, uiMIP = 0, uiOffset = 0; uiMIP < psTX_IMG->m_sTX.m_nuiMIP && uiCopy_Region < nuiCopy_Regions; ++uiMIP, ++uiCopy_Region) {
        VkDeviceSize_C                      uiWidth = tgCM_MAX_UMAX(psTX_IMG->m_uiWidth >> uiMIP, 1u);
        VkDeviceSize_C                      uiHeight = tgCM_MAX_UMAX(psTX_IMG->m_uiHeight >> uiMIP, 1u);

        tgMM_Set_U08_0x00( asCopy_Regions + uiMIP, sizeof( asCopy_Regions[0] ) );
        asCopy_Regions[uiCopy_Region].bufferOffset = uiOffset;
        asCopy_Regions[uiCopy_Region].bufferRowLength = 0;
        asCopy_Regions[uiCopy_Region].bufferImageHeight = 0;
        asCopy_Regions[uiCopy_Region].imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        asCopy_Regions[uiCopy_Region].imageSubresource.mipLevel = (uint32_t)uiMIP;
        asCopy_Regions[uiCopy_Region].imageSubresource.baseArrayLayer = 0;
        asCopy_Regions[uiCopy_Region].imageSubresource.layerCount = 1;
        asCopy_Regions[uiCopy_Region].imageOffset.x = 0;
        asCopy_Regions[uiCopy_Region].imageOffset.y = 0;
        asCopy_Regions[uiCopy_Region].imageOffset.z = 0;
        asCopy_Regions[uiCopy_Region].imageExtent.width = (uint32_t)uiWidth;
        asCopy_Regions[uiCopy_Region].imageExtent.height = (uint32_t)uiHeight;
        asCopy_Regions[uiCopy_Region].imageExtent.depth = 1;

        uiOffset += uiWidth * uiHeight * 4;  // 4 bytes per pixel
    }

    *puiMIP = uiMIP;
}


/* ---- tgKN_GPU_EXT_TX_VOL_MIP_Regions ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgKN_GPU_EXT_TX_VOL_MIP_Regions( VkBufferImageCopy_PC asCopy_Regions, TgRSIZE_PC puiMIP, TgRSIZE_C nuiCopy_Regions, STg2_KN_GPU_TX_VOL_DATA_CPC psTX_VOL )
{
    TgRSIZE                             uiMIP, uiCopy_Region, uiOffset;

    /* Copy buffer to image for each mip level. Volume textures copy entire mip level at once. */
    for (uiCopy_Region = 0, uiMIP = 0, uiOffset = 0; uiMIP < psTX_VOL->m_sTX.m_nuiMIP && uiCopy_Region < nuiCopy_Regions; ++uiMIP, ++uiCopy_Region) {
        VkDeviceSize_C                      uiMipWidth = tgCM_MAX_UMAX(psTX_VOL->m_uiWidth >> uiMIP, 1u);
        VkDeviceSize_C                      uiMipHeight = tgCM_MAX_UMAX(psTX_VOL->m_uiHeight >> uiMIP, 1u);
        VkDeviceSize_C                      uiMipDepth = tgCM_MAX_UMAX(psTX_VOL->m_uiDepth >> uiMIP, 1u);

        tgMM_Set_U08_0x00( asCopy_Regions + uiCopy_Region, sizeof( asCopy_Regions[0] ) );
        asCopy_Regions[uiCopy_Region].bufferOffset = uiOffset;
        asCopy_Regions[uiCopy_Region].bufferRowLength = 0;
        asCopy_Regions[uiCopy_Region].bufferImageHeight = 0;
        asCopy_Regions[uiCopy_Region].imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        asCopy_Regions[uiCopy_Region].imageSubresource.mipLevel = (uint32_t)uiMIP;
        asCopy_Regions[uiCopy_Region].imageSubresource.baseArrayLayer = 0;
        asCopy_Regions[uiCopy_Region].imageSubresource.layerCount = 1;
        asCopy_Regions[uiCopy_Region].imageOffset.x = 0;
        asCopy_Regions[uiCopy_Region].imageOffset.y = 0;
        asCopy_Regions[uiCopy_Region].imageOffset.z = 0;
        asCopy_Regions[uiCopy_Region].imageExtent.width = (uint32_t)uiMipWidth;
        asCopy_Regions[uiCopy_Region].imageExtent.height = (uint32_t)uiMipHeight;
        asCopy_Regions[uiCopy_Region].imageExtent.depth = (uint32_t)uiMipDepth;

        uiOffset += uiMipWidth * uiMipHeight * uiMipDepth * 4;  // 4 bytes per pixel
    }

    *puiMIP = uiMIP;
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Generic Implementations                                                                                                                                                        */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

    #define ENABLE_RELOAD_GUARD
    #define T(A,...) TgMACRO_CONCAT3V(A,TgMACRO_BUILD_RESOURCE_TYPE,__VA_ARGS__)

#if defined(TgCOMPILE__GPU_OBJECT_NAME) && TgCOMPILE__GPU_OBJECT_NAME
    #define T_USZ(A,...) TgMACRO_CONCAT3V_USZ(A,TgMACRO_BUILD_RESOURCE_TYPE,__VA_ARGS__)
#endif

    #define TgMACRO_ASSIGN_IMAGE_CREATE_INFO(A,B)           TgMACRO_ASSIGN_IMAGE_CREATE_INFO_(A,B)
    #define TgMACRO_ASSIGN_IMAGE_VIEW_CREATE_INFO(A)        TgMACRO_ASSIGN_IMAGE_VIEW_CREATE_INFO_(A)

    #define TgMACRO_ASSIGN_IMAGE_CREATE_INFO_(A,B)          A.imageType = VK_IMAGE_TYPE_2D; \
                                                            A.flags = VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT; \
                                                            A.extent.width = B->m_uiEdge; \
                                                            A.extent.height = B->m_uiEdge; \
                                                            A.extent.depth = 1; \
                                                            A.arrayLayers = 6

    #define TgMACRO_ASSIGN_IMAGE_VIEW_CREATE_INFO_(A)       A.subresourceRange.layerCount = 6; \
                                                            A.viewType = VK_IMAGE_VIEW_TYPE_CUBE

    #define TgMACRO_BUILD_RESOURCE_TYPE TX_CBE
        #include __FILE__
    #undef TgMACRO_BUILD_RESOURCE_TYPE

    #undef TgMACRO_ASSIGN_BINDING_INDEX_
    #undef TgMACRO_ASSIGN_IMAGE_VIEW_CREATE_INFO_
    #undef TgMACRO_ASSIGN_IMAGE_CREATE_INFO_

    #define TgMACRO_ASSIGN_IMAGE_CREATE_INFO_(A,B)          A.imageType = VK_IMAGE_TYPE_2D; \
                                                            A.extent.width = B->m_uiWidth; \
                                                            A.extent.height = B->m_uiHeight; \
                                                            A.extent.depth = 1; \
                                                            A.arrayLayers = 1

    #define TgMACRO_ASSIGN_IMAGE_VIEW_CREATE_INFO_(A)       A.subresourceRange.layerCount = 1; \
                                                            A.viewType = VK_IMAGE_VIEW_TYPE_2D

    #define TgMACRO_BUILD_RESOURCE_TYPE TX_IMG
        #include __FILE__
    #undef TgMACRO_BUILD_RESOURCE_TYPE

    #undef TgMACRO_ASSIGN_BINDING_INDEX_
    #undef TgMACRO_ASSIGN_IMAGE_VIEW_CREATE_INFO_
    #undef TgMACRO_ASSIGN_IMAGE_CREATE_INFO_

    #define TgMACRO_ASSIGN_IMAGE_CREATE_INFO_(A,B)          A.imageType = VK_IMAGE_TYPE_3D; \
                                                            A.extent.width = B->m_uiWidth; \
                                                            A.extent.height = B->m_uiHeight; \
                                                            A.extent.depth = (TgUINT_E16)B->m_uiDepth; \
                                                            A.arrayLayers = 1

    #define TgMACRO_ASSIGN_IMAGE_VIEW_CREATE_INFO_(A)       A.subresourceRange.layerCount = 1; \
                                                            A.viewType = VK_IMAGE_VIEW_TYPE_3D

    #define TgMACRO_BUILD_RESOURCE_TYPE TX_VOL
        #include __FILE__
    #undef TgMACRO_BUILD_RESOURCE_TYPE

    #undef TgMACRO_ASSIGN_BINDING_INDEX_
    #undef TgMACRO_ASSIGN_IMAGE_VIEW_CREATE_INFO_
    #undef TgMACRO_ASSIGN_IMAGE_CREATE_INFO_

    #undef TgMACRO_ASSIGN_IMAGE_VIEW_CREATE_INFO
    #undef TgMACRO_ASSIGN_IMAGE_CREATE_INFO

#if defined(TgCOMPILE__GPU_OBJECT_NAME) && TgCOMPILE__GPU_OBJECT_NAME
    #undef T_USZ
#endif

    #undef T
    #undef ENABLE_RELOAD_GUARD

/*# !defined(ENABLE_RELOAD_GUARD) */
#endif
