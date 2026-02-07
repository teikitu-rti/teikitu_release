/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (VULKAN) Kernel [GPU] - Debug.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.22 | »GUID« 7ECEAB43-40E4-4161-8F94-87AF31F5BA9A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    Models:     Claude 3.7, Claude 4.0
    ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if defined(TgS_DEBUG__RENDER)

/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_GPU_EXT__DBG__Begin_Event ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_EXT__DBG__Begin_Event( STg2_KN_GPU_CMD_PC psCMD, TgCHAR_U8_CPC uszName, TgRSIZE_C nbyName, TgFLOAT32_CPC pfColor )
{
    UTg2_KN_GPU_CMD_C                           uCMD = { .ps = psCMD };
    VkDebugUtilsLabelEXT                        sLabel;

    TgPARAM_CHECK_KN_GPU_CMD( psCMD );

    if (!vkCmdBeginDebugUtilsLabelEXT || !uszName)
    {
        return;
    }

    tgMM_Set_U08_0x00( &sLabel, sizeof(sLabel) );

    sLabel.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT;
    sLabel.pLabelName = (const char*)uszName;
    if (pfColor)
    {
        sLabel.color[0] = pfColor[0];
        sLabel.color[1] = pfColor[1];
        sLabel.color[2] = pfColor[2];
        sLabel.color[3] = pfColor[3];
    }
    else
    {
        sLabel.color[0] = 1.0f;
        sLabel.color[1] = 1.0f;
        sLabel.color[2] = 1.0f;
        sLabel.color[3] = 1.0f;
    }

    (void)nbyName;
    vkCmdBeginDebugUtilsLabelEXT(uCMD.psVLKN->m_hVLKN_Command_Buffer, &sLabel);
}


/* ---- tgKN_GPU_EXT__DBG__End_Event --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_EXT__DBG__End_Event( STg2_KN_GPU_CMD_PC psCMD)
{
    UTg2_KN_GPU_CMD_C                           uCMD = { .ps = psCMD };

    if (!vkCmdEndDebugUtilsLabelEXT)
    {
        return;
    }

    vkCmdEndDebugUtilsLabelEXT(uCMD.psVLKN->m_hVLKN_Command_Buffer);
}


/* ---- tgKN_GPU_EXT__DBG__Insert_Marker ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_EXT__DBG__Insert_Marker( STg2_KN_GPU_CMD_PC psCMD, TgCHAR_U8_CPC uszName, TgRSIZE_C nbyName, TgFLOAT32_CPC pfColor )
{
    UTg2_KN_GPU_CMD_C                           uCMD = { .ps = psCMD };
    VkDebugUtilsLabelEXT                        sLabel;

    if (!vkCmdInsertDebugUtilsLabelEXT || !uszName)
    {
        return;
    }

    tgMM_Set_U08_0x00( &sLabel, sizeof(sLabel) );

    sLabel.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT;
    sLabel.pLabelName = (const char*)uszName;
    if (pfColor)
    {
        sLabel.color[0] = pfColor[0];
        sLabel.color[1] = pfColor[1];
        sLabel.color[2] = pfColor[2];
        sLabel.color[3] = pfColor[3];
    }
    else
    {
        sLabel.color[0] = 1.0f;
        sLabel.color[1] = 1.0f;
        sLabel.color[2] = 1.0f;
        sLabel.color[3] = 1.0f;
    }

    (void)nbyName;
    vkCmdInsertDebugUtilsLabelEXT(uCMD.psVLKN->m_hVLKN_Command_Buffer, &sLabel);
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_GPU_VLKN_Debug_Set_Object_Name -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_VLKN_Debug_Set_Object_Name( TgVOID_P pDevice, TgUINT_E32 objectType, TgUINT_E64 objectHandle, TgCHAR_U8_CPC pszName )
{
    VkDevice                                    sDevice = (VkDevice)pDevice;
    VkDebugUtilsObjectNameInfoEXT               sNameInfo;

    tgMM_Set_U08_0x00( &sNameInfo, sizeof(sNameInfo) );
    if (!vkSetDebugUtilsObjectNameEXT || !pszName)
    {
        return;
    }

    sNameInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT;
    sNameInfo.objectType = (VkObjectType)objectType;
    sNameInfo.objectHandle = objectHandle;
    sNameInfo.pObjectName = (const char*)pszName;

    vkSetDebugUtilsObjectNameEXT(sDevice, &sNameInfo);
}


/* =============================================================================================================================================================================== */

/*# TgS_DEBUG__RENDER */
#endif
