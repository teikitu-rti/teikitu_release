/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Kernel [GPU] - Debug.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.20 | »GUID« DE461472-5528-4A5B-A7F4-09CCAD73387B */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/* == Kernel ===================================================================================================================================================================== */
#if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_GPU__Host__Init_Debug ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU__Host__Init_Debug( TgVOID )
{
    return (tgKN_GPU_EXT__Host__Init_Debug());
}


/* ---- tgKN_GPU__Host__Free_Debug ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU__Host__Free_Debug( TgVOID )
{
    TgRSIZE                             uiIndex;

    tgKN_GPU_EXT__Host__Free_Debug();

    for (uiIndex = 0; uiIndex < TgARRAY_COUNT(g_sKN_GPU_DBG_CXT_HOST.m_atiFS); ++uiIndex)
    {
        if (g_sKN_GPU_DBG_CXT_HOST.m_atiFS[uiIndex].m_uiKI) {
            tgKN_GPU_FS__Release(g_sKN_GPU_DBG_CXT_HOST.m_atiFS[uiIndex]);
            g_sKN_GPU_DBG_CXT_HOST.m_atiFS[uiIndex] = KTgKN_GPU_FS_ID__INVALID;
        }
    }

    for (uiIndex = 0; uiIndex < TgARRAY_COUNT(g_sKN_GPU_DBG_CXT_HOST.m_atiMS); ++uiIndex)
    {
        if (g_sKN_GPU_DBG_CXT_HOST.m_atiMS[uiIndex].m_uiKI) {
            tgKN_GPU_MS__Release(g_sKN_GPU_DBG_CXT_HOST.m_atiMS[uiIndex]);
            g_sKN_GPU_DBG_CXT_HOST.m_atiMS[uiIndex] = KTgKN_GPU_MS_ID__INVALID;
        }
    }

    for (uiIndex = 0; uiIndex < TgARRAY_COUNT(g_sKN_GPU_DBG_CXT_HOST.m_atiTS); ++uiIndex)
    {
        if (g_sKN_GPU_DBG_CXT_HOST.m_atiTS[uiIndex].m_uiKI) {
            tgKN_GPU_TS__Release(g_sKN_GPU_DBG_CXT_HOST.m_atiTS[uiIndex]);
            g_sKN_GPU_DBG_CXT_HOST.m_atiTS[uiIndex] = KTgKN_GPU_TS_ID__INVALID;
        }
    }

    for (uiIndex = 0; uiIndex < TgARRAY_COUNT(g_sKN_GPU_DBG_CXT_HOST.m_atiVS); ++uiIndex)
    {
        if (g_sKN_GPU_DBG_CXT_HOST.m_atiVS[uiIndex].m_uiKI) {
            tgKN_GPU_VS__Release(g_sKN_GPU_DBG_CXT_HOST.m_atiVS[uiIndex]);
            g_sKN_GPU_DBG_CXT_HOST.m_atiVS[uiIndex] = KTgKN_GPU_VS_ID__INVALID;
        }
    }
}


/* ---- tgKN_GPU__Execute__Init_Debug -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU__Execute__Init_Debug( TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC )
{
    return (tgKN_GPU_EXT__Execute__Init_Debug( tiCXT_EXEC ));
}


/* ---- tgKN_GPU__Execute__Free_Debug -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU__Execute__Free_Debug( TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC )
{
    tgKN_GPU_EXT__Execute__Free_Debug( tiCXT_EXEC );
}


/* ---- tgKN_GPU__Swap__Init_Debug ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU__Swap__Init_Debug( TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP )
{
    return (tgKN_GPU_EXT__Swap__Init_Debug( tiCXT_SWAP ));
}


/* ---- tgKN_GPU__Swap__Free_Debug ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU__Swap__Free_Debug( TgKN_GPU_CXT_SWAP_ID_C tiCXT_SWAP )
{
    tgKN_GPU_EXT__Swap__Free_Debug( tiCXT_SWAP );
}


/* ---- tgKN_GPU__Execute__Init_Debug__Create_Resources -------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU__Execute__Init_Debug__Create_Resources( STg2_KN_GPU_CMD_PC psCMD )
{
    TgRSIZE                                     uiEXEC = (psCMD->m_tiCXT_WORK.m_uiI >> 16) & 0xFFFF;
    STg2_KN_GPU_CXT_EXEC_EXTN_PC                psCXT_EXEC_EXTN = g_asKN_GPU_CXT_EXEC_EXTN + uiEXEC;
    STg2_KN_GPU_CXT_EXEC_PC                     psCXT_EXEC = g_asKN_GPU_CXT_EXEC + uiEXEC;

    TgKN_GPU_TX_IMG_INST_ID_P                   psEXTN_ID_Font;
    STg2_KN_GPU_FONT_P                          psROM_Font;

#if TgCOMPILE__CONSOLE
    tgMM_Set_U08_0x00( g_uszKN_GPU_LOG_Render_Buffer, sizeof(g_uszKN_GPU_LOG_Render_Buffer) );
    g_nuiKN_GPU_LOG_Line = 0;
    tgMM_Set_U08_0x00( g_uszKN_GPU_CON_Render_Buffer, sizeof(g_uszKN_GPU_CON_Render_Buffer) );
    g_nuiKN_GPU_CON_Line = 0;
/*# TgCOMPILE__CONSOLE */
#endif

    /* Default font textures for debug text output. */

    psEXTN_ID_Font = psCXT_EXEC_EXTN->m_sID_Font_ROM__DOS_Font + ETgKN_GPU_DOS_FONT_ROM_DEFAULT;
    psROM_Font = g_sKN_GPU_STD_DOS_Font + ETgKN_GPU_DOS_FONT_ROM_DEFAULT;
    *psEXTN_ID_Font = tgKN_GPU__CMD__TX_IMG_Inst__Font_ROM( psCMD, psROM_Font );
    if (KTgID__INVALID_VALUE == psEXTN_ID_Font->m_uiKI)
    {
        *psEXTN_ID_Font = tgKN_GPU_TX_IMG_Inst__IncRef( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Black_709 );
    }
    psCXT_EXEC->m_uiDOS_Font_Texture_Index[ETgKN_GPU_DOS_FONT_ROM_DEFAULT] =
        tgKN_GPU_EXT__CMD__Register_Default_TX_IMG_Inst( psCMD, *psEXTN_ID_Font, ETgKN_GPU_DEFAULT_SAMPLER__NEAREST_CLAMP );

    psEXTN_ID_Font = psCXT_EXEC_EXTN->m_sID_Font_ROM__DOS_Font + ETgKN_GPU_DOS_FONT_ROM_FUTURE;
    psROM_Font = g_sKN_GPU_STD_DOS_Font + ETgKN_GPU_DOS_FONT_ROM_FUTURE;
    *psEXTN_ID_Font = tgKN_GPU__CMD__TX_IMG_Inst__Font_ROM( psCMD, psROM_Font );
    if (KTgID__INVALID_VALUE == psEXTN_ID_Font->m_uiKI)
    {
        *psEXTN_ID_Font = tgKN_GPU_TX_IMG_Inst__IncRef( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Black_709 );
    }
    psCXT_EXEC->m_uiDOS_Font_Texture_Index[ETgKN_GPU_DOS_FONT_ROM_FUTURE] =
        tgKN_GPU_EXT__CMD__Register_Default_TX_IMG_Inst( psCMD, *psEXTN_ID_Font, ETgKN_GPU_DEFAULT_SAMPLER__NEAREST_CLAMP );

    psEXTN_ID_Font = psCXT_EXEC_EXTN->m_sID_Font_ROM__DOS_Font + ETgKN_GPU_DOS_FONT_ROM_BLOCK;
    psROM_Font = g_sKN_GPU_STD_DOS_Font + ETgKN_GPU_DOS_FONT_ROM_BLOCK;
    *psEXTN_ID_Font = tgKN_GPU__CMD__TX_IMG_Inst__Font_ROM( psCMD, psROM_Font );
    if (KTgID__INVALID_VALUE == psEXTN_ID_Font->m_uiKI)
    {
        *psEXTN_ID_Font = tgKN_GPU_TX_IMG_Inst__IncRef( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Black_709 );
    }
    psCXT_EXEC->m_uiDOS_Font_Texture_Index[ETgKN_GPU_DOS_FONT_ROM_BLOCK] =
        tgKN_GPU_EXT__CMD__Register_Default_TX_IMG_Inst( psCMD, *psEXTN_ID_Font, ETgKN_GPU_DEFAULT_SAMPLER__NEAREST_CLAMP );

    psEXTN_ID_Font = psCXT_EXEC_EXTN->m_sID_Font_ROM__DOS_Font + ETgKN_GPU_DOS_FONT_ROM_MARCIO;
    psROM_Font = g_sKN_GPU_STD_DOS_Font + ETgKN_GPU_DOS_FONT_ROM_MARCIO;
    *psEXTN_ID_Font = tgKN_GPU__CMD__TX_IMG_Inst__Font_ROM( psCMD, psROM_Font );
    if (KTgID__INVALID_VALUE == psEXTN_ID_Font->m_uiKI)
    {
        *psEXTN_ID_Font = tgKN_GPU_TX_IMG_Inst__IncRef( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Black_709 );
    }
    psCXT_EXEC->m_uiDOS_Font_Texture_Index[ETgKN_GPU_DOS_FONT_ROM_MARCIO] =
        tgKN_GPU_EXT__CMD__Register_Default_TX_IMG_Inst( psCMD, *psEXTN_ID_Font, ETgKN_GPU_DEFAULT_SAMPLER__NEAREST_CLAMP );

    /* Reference image to be used during testing. */

    psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Reference_G10_P709_00 = tgKN_GPU__CMD__TX_IMG__Load_TIFF_From_OS_File_System( psCMD, g_tiKN_FS_HDD__Mount_APP, nullptr,
                                                                                                                    u8"DeltaE_16bit_gamma1.0.tif",
                                                                                                                    ETgKN_GPU_RESOURCE_DESCRIPTOR__MEMORY_LOCAL );
    if (KTgID__INVALID_VALUE == psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Reference_G10_P709_00.m_uiKI)
    {
        psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Reference_G10_P709_00 = tgKN_GPU_TX_IMG_Inst__IncRef( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Black_709 );
    }
    tgKN_GPU_EXT__CMD__Register_Default_TX_IMG_Inst( psCMD, psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Reference_G10_P709_00, ETgKN_GPU_DEFAULT_SAMPLER__HIGH_QUALITY_ANISOTROPIC );

    psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_MIP_1024x1024 = tgKN_GPU__CMD__TX_IMG_Inst__Init_MIP( psCMD, 1024, 1024, u8"MIP 1024x1024" );
    if (KTgID__INVALID_VALUE == psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_MIP_1024x1024.m_uiKI)
    {
        psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_MIP_1024x1024 = tgKN_GPU_TX_IMG_Inst__IncRef( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Black_709 );
    }
    tgKN_GPU_EXT__CMD__Register_Default_TX_IMG_Inst( psCMD, psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_MIP_1024x1024, ETgKN_GPU_DEFAULT_SAMPLER__LINEAR_REPEAT );

    psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_MIP_0512x0512 = tgKN_GPU__CMD__TX_IMG_Inst__Init_MIP( psCMD, 512, 512, u8"MIP 512x512" );
    if (KTgID__INVALID_VALUE == psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_MIP_0512x0512.m_uiKI)
    {
        psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_MIP_0512x0512 = tgKN_GPU_TX_IMG_Inst__IncRef( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Black_709 );
    }
    tgKN_GPU_EXT__CMD__Register_Default_TX_IMG_Inst( psCMD, psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_MIP_0512x0512, ETgKN_GPU_DEFAULT_SAMPLER__LINEAR_REPEAT );

    psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_MIP_0256x0256 = tgKN_GPU__CMD__TX_IMG_Inst__Init_MIP( psCMD, 256, 256, u8"MIP 256x256" );
    if (KTgID__INVALID_VALUE == psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_MIP_0256x0256.m_uiKI)
    {
        psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_MIP_0256x0256 = tgKN_GPU_TX_IMG_Inst__IncRef( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Black_709 );
    }
    tgKN_GPU_EXT__CMD__Register_Default_TX_IMG_Inst( psCMD, psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_MIP_0256x0256, ETgKN_GPU_DEFAULT_SAMPLER__LINEAR_REPEAT );

    psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_MIP_0128x0128 = tgKN_GPU__CMD__TX_IMG_Inst__Init_MIP( psCMD, 128, 128, u8"MIP 128x128" );
    if (KTgID__INVALID_VALUE == psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_MIP_0128x0128.m_uiKI)
    {
        psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_MIP_0128x0128 = tgKN_GPU_TX_IMG_Inst__IncRef( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Black_709 );
    }
    tgKN_GPU_EXT__CMD__Register_Default_TX_IMG_Inst( psCMD, psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_MIP_0128x0128, ETgKN_GPU_DEFAULT_SAMPLER__LINEAR_REPEAT );

    psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_MIP_0064x0064 = tgKN_GPU__CMD__TX_IMG_Inst__Init_MIP( psCMD, 64, 64, u8"MIP 64x64" );
    if (KTgID__INVALID_VALUE == psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_MIP_0064x0064.m_uiKI)
    {
        psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_MIP_0064x0064 = tgKN_GPU_TX_IMG_Inst__IncRef( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Black_709 );
    }
    tgKN_GPU_EXT__CMD__Register_Default_TX_IMG_Inst( psCMD, psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_MIP_0064x0064, ETgKN_GPU_DEFAULT_SAMPLER__LINEAR_REPEAT );

    psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Gamma_Test = tgKN_GPU__CMD__TX_IMG_Inst__Init_Gamma_Test( psCMD, 256, 256, u8"Gamma Test" );
    if (KTgID__INVALID_VALUE == psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Gamma_Test.m_uiKI)
    {
        psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Gamma_Test = tgKN_GPU_TX_IMG_Inst__IncRef( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Black_709 );
    }
    tgKN_GPU_EXT__CMD__Register_Default_TX_IMG_Inst( psCMD, psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Gamma_Test, ETgKN_GPU_DEFAULT_SAMPLER__HIGH_QUALITY_ANISOTROPIC );

    psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Target = tgKN_GPU_TX_IMG_Inst__IncRef( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Black_709 );
    tgKN_GPU_EXT__CMD__Register_Default_TX_IMG_Inst( psCMD, psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Target, ETgKN_GPU_DEFAULT_SAMPLER__HIGH_QUALITY_ANISOTROPIC );

    psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Error = tgKN_GPU__CMD__TX_IMG_Inst__Init_Checker_Pattern( psCMD, 64, 64, KTg_YELLOW_G10_P709_U32, KTg_MAGENTA_G10_P709_U32, u8"Error" );
    if (KTgID__INVALID_VALUE == psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Error.m_uiKI)
    {
        psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Error = tgKN_GPU_TX_IMG_Inst__IncRef( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Black_709 );
    }
    tgKN_GPU_EXT__CMD__Register_Default_TX_IMG_Inst( psCMD, psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Error, ETgKN_GPU_DEFAULT_SAMPLER__HIGH_QUALITY_ANISOTROPIC );

    psCXT_EXEC_EXTN->m_sID_TX_CBE_INST_Error = tgKN_GPU_TX_CBE_Inst__IncRef( psCXT_EXEC_EXTN->m_sID_TX_CBE_INST_Black_709 );
    tgKN_GPU_EXT__CMD__Register_Default_TX_CBE_Inst( psCMD, psCXT_EXEC_EXTN->m_sID_TX_CBE_INST_Error, ETgKN_GPU_DEFAULT_SAMPLER__HIGH_QUALITY_ANISOTROPIC );

    psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Standard_1080 = tgKN_GPU_TX_IMG_Inst__IncRef( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Black_709 );
    tgKN_GPU_EXT__CMD__Register_Default_TX_IMG_Inst( psCMD, psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Standard_1080, ETgKN_GPU_DEFAULT_SAMPLER__HIGH_QUALITY_ANISOTROPIC );

    psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Standard_0720 = tgKN_GPU_TX_IMG_Inst__IncRef( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Black_709 );
    tgKN_GPU_EXT__CMD__Register_Default_TX_IMG_Inst( psCMD, psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Standard_0720, ETgKN_GPU_DEFAULT_SAMPLER__HIGH_QUALITY_ANISOTROPIC );

    psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Standard_NTSC = tgKN_GPU_TX_IMG_Inst__IncRef( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Black_709 );
    tgKN_GPU_EXT__CMD__Register_Default_TX_IMG_Inst( psCMD, psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Standard_NTSC, ETgKN_GPU_DEFAULT_SAMPLER__HIGH_QUALITY_ANISOTROPIC );

    psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Standard_PAL = tgKN_GPU_TX_IMG_Inst__IncRef( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Black_709 );
    tgKN_GPU_EXT__CMD__Register_Default_TX_IMG_Inst( psCMD, psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Standard_PAL, ETgKN_GPU_DEFAULT_SAMPLER__HIGH_QUALITY_ANISOTROPIC );

    {
        TgVOID                                      (* const pfnInit_Mesh[])( TgKN_GPU_DBG_PM_Generate_PC ) = {
                                                        tgKN_GPU_DBG_Init_Mesh_Box,
                                                        tgKN_GPU_DBG_Init_Mesh_Capsule_Cap_0,
                                                        tgKN_GPU_DBG_Init_Mesh_Capsule_Cap_1,
                                                        tgKN_GPU_DBG_Init_Mesh_Capsule_Tube,
                                                        tgKN_GPU_DBG_Init_Mesh_Cone,
                                                        tgKN_GPU_DBG_Init_Mesh_Cylinder,
                                                        tgKN_GPU_DBG_Init_Mesh_Plane,
                                                        tgKN_GPU_DBG_Init_Mesh_Sphere,
                                                        tgKN_GPU_DBG_Init_Mesh_Tube
                                                    };
        ETgKN_GPU_DEBUG_PM                          enPM;

        for (enPM = ETgKN_GPU_DEBUG_PM_3D_START; enPM < ETgKN_GPU_DEBUG_PM_3D_END; enPM = (ETgKN_GPU_DEBUG_PM)((TgSINT_E32)enPM + 1))
        {
            TgKN_GPU_DBG_PM_Generate            sGenerate;

            tgMM_Set_U08_0x00( &sGenerate, sizeof(sGenerate) );
            sGenerate.m_uiTessellate = 3;
            pfnInit_Mesh[enPM - ETgKN_GPU_DEBUG_PM_3D_START]( &sGenerate ); /* Calculate the size of the index pool needed. */
            sGenerate.m_puiIndex = (TgUINT_E16_P)TgMALLOC_POOL(sGenerate.m_nuiMax_Index * sizeof(TgUINT_E16));
            pfnInit_Mesh[enPM - ETgKN_GPU_DEBUG_PM_3D_START]( &sGenerate ); /* Calculate the size of the vertex pool needed. */
            sGenerate.m_psVertex = (STg2_KN_GPU_Vertex_Geom_02_P)TgMALLOC_POOL(sGenerate.m_nuiMax_Vertex * sizeof(STg2_KN_GPU_Vertex_Geom_02));
            pfnInit_Mesh[enPM - ETgKN_GPU_DEBUG_PM_3D_START]( &sGenerate ); /* Calculate the final geometry. This is inefficient as tessellation is run twice. */

            TgDIAG(sGenerate.m_nuiIndex <= sGenerate.m_nuiMax_Index);
            TgDIAG(sGenerate.m_nuiVertex <= sGenerate.m_nuiMax_Vertex);

            tgKN_GPU_EXT__CMD__Register_Debug_Geometry( psCMD, enPM, &sGenerate );

            TgFREE_POOL(sGenerate.m_psVertex);
            TgFREE_POOL(sGenerate.m_puiIndex);
        }
    }

    return (tgKN_GPU_EXT__Execute__Init_Debug__Create_Resources( psCMD ));
}


/* ---- tgKN_GPU__Execute__Free_Debug__Destroy_Resources ------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU__Execute__Free_Debug__Destroy_Resources( STg2_KN_GPU_CMD_PC psCMD )
{
    TgRSIZE                             uiEXEC = (psCMD->m_tiCXT_WORK.m_uiI >> 16) & 0xFFFF;
    STg2_KN_GPU_CXT_EXEC_EXTN_PC        psCXT_EXEC_EXTN = g_asKN_GPU_CXT_EXEC_EXTN + uiEXEC;

    TgPARAM_CHECK_INDEX(uiEXEC, g_asKN_GPU_CXT_EXEC);

    tgKN_GPU_EXT__Execute__Free_Debug__Destroy_Resources( psCMD );

    tgKN_GPU__CMD__TX_IMG_Inst__Release( psCMD, psCXT_EXEC_EXTN->m_sID_Font_ROM__DOS_Font[ETgKN_GPU_DOS_FONT_ROM_DEFAULT] );
    tgKN_GPU__CMD__TX_IMG_Inst__Release( psCMD, psCXT_EXEC_EXTN->m_sID_Font_ROM__DOS_Font[ETgKN_GPU_DOS_FONT_ROM_FUTURE] );
    tgKN_GPU__CMD__TX_IMG_Inst__Release( psCMD, psCXT_EXEC_EXTN->m_sID_Font_ROM__DOS_Font[ETgKN_GPU_DOS_FONT_ROM_BLOCK] );
    tgKN_GPU__CMD__TX_IMG_Inst__Release( psCMD, psCXT_EXEC_EXTN->m_sID_Font_ROM__DOS_Font[ETgKN_GPU_DOS_FONT_ROM_MARCIO] );

    tgKN_GPU__CMD__TX_IMG_Inst__Release( psCMD, psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Reference_G10_P709_00 );
    tgKN_GPU__CMD__TX_IMG_Inst__Release( psCMD, psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_MIP_1024x1024 );
    tgKN_GPU__CMD__TX_IMG_Inst__Release( psCMD, psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_MIP_0512x0512 );
    tgKN_GPU__CMD__TX_IMG_Inst__Release( psCMD, psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_MIP_0256x0256 );
    tgKN_GPU__CMD__TX_IMG_Inst__Release( psCMD, psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_MIP_0128x0128 );
    tgKN_GPU__CMD__TX_IMG_Inst__Release( psCMD, psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_MIP_0064x0064 );
    tgKN_GPU__CMD__TX_IMG_Inst__Release( psCMD, psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Gamma_Test );
    tgKN_GPU__CMD__TX_IMG_Inst__Release( psCMD, psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Target );
    tgKN_GPU__CMD__TX_IMG_Inst__Release( psCMD, psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Error );
    tgKN_GPU__CMD__TX_CBE_Inst__Release( psCMD, psCXT_EXEC_EXTN->m_sID_TX_CBE_INST_Error );
    tgKN_GPU__CMD__TX_IMG_Inst__Release( psCMD, psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Standard_1080 );
    tgKN_GPU__CMD__TX_IMG_Inst__Release( psCMD, psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Standard_0720 );
    tgKN_GPU__CMD__TX_IMG_Inst__Release( psCMD, psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Standard_NTSC );
    tgKN_GPU__CMD__TX_IMG_Inst__Release( psCMD, psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Standard_PAL );
}

/* =============================================================================================================================================================================== */
/*# defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
#endif
