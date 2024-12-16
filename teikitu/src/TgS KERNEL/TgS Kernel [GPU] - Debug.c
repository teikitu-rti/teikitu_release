/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Kernel [GPU] - Debug.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.20 | »GUID« DE461472-5528-4A5B-A7F4-09CCAD73387B */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_GPU__Execute__Init_Debug -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU__Execute__Init_Debug( TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC )
{
    TgPARAM_CHECK_INDEX( tiCXT_EXEC.m_uiI, g_asKN_GPU_CXT_EXEC );
    TgPARAM_CHECK( tgKN_GPU_CXT_EXEC_ID_Is_Equal( &(g_asKN_GPU_CXT_EXEC[tiCXT_EXEC.m_uiI].m_tiCXT_EXEC_S), tiCXT_EXEC ) );
    {
        STg2_KN_GPU_CXT_EXEC_EXTN_PC        psCXT_EXEC_EXTN = g_asKN_GPU_CXT_EXEC_EXT + tiCXT_EXEC.m_uiI;

    #if TgCOMPILE__RENDER_DEBUG_OUTPUT || TgS_DEBUG__KERNEL || TgS_DEBUG__RENDER
        TgKN_GPU_CXT_WORK_ID_C              tiCXT_WORK = tgKN_GPU_EXT__Execute__Frame_Start( tiCXT_EXEC );
        UTg2_KN_GPU_CMD_C                   uCMD = tgKN_GPU_EXT__Execute__Command_List_Acquire( tiCXT_WORK, ETgKN_GPU_EXT_COMMAND_DIRECT );
    //# TgCOMPILE__RENDER_DEBUG_OUTPUT || TgS_DEBUG__KERNEL || TgS_DEBUG__RENDER
    #endif

        /* Default font textures for debug text output. */

    #if TgCOMPILE__RENDER_DEBUG_OUTPUT
        psCXT_EXEC_EXTN->m_sID_Font_ROM__DOS_Font_Default = tgKN_GPU_TX_IMG_Inst__Font_ROM( uCMD, &g_sKN_GPU_STD_DOS_Font[ETgKN_GPU_DOS_FONT_ROM_DEFAULT] );
        if (KTgID__INVALID_VALUE == psCXT_EXEC_EXTN->m_sID_Font_ROM__DOS_Font_Default.m_uiKI)
            psCXT_EXEC_EXTN->m_sID_Font_ROM__DOS_Font_Default = tgKN_GPU_TX_IMG_Inst__IncRef( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Black_709 );
        tgKN_GPU_EXT_Register_Default_TX_IMG_Inst( psCXT_EXEC_EXTN->m_sID_Font_ROM__DOS_Font_Default );

        psCXT_EXEC_EXTN->m_sID_Font_ROM__DOS_Font_Future = tgKN_GPU_TX_IMG_Inst__Font_ROM( uCMD, &g_sKN_GPU_STD_DOS_Font[ETgKN_GPU_DOS_FONT_ROM_FUTURE] );
        if (KTgID__INVALID_VALUE == psCXT_EXEC_EXTN->m_sID_Font_ROM__DOS_Font_Future.m_uiKI)
            psCXT_EXEC_EXTN->m_sID_Font_ROM__DOS_Font_Future = tgKN_GPU_TX_IMG_Inst__IncRef( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Black_709 );
        tgKN_GPU_EXT_Register_Default_TX_IMG_Inst( psCXT_EXEC_EXTN->m_sID_Font_ROM__DOS_Font_Future );

        psCXT_EXEC_EXTN->m_sID_Font_ROM__DOS_Font_Block = tgKN_GPU_TX_IMG_Inst__Font_ROM( uCMD, &g_sKN_GPU_STD_DOS_Font[ETgKN_GPU_DOS_FONT_ROM_BLOCK] );
        if (KTgID__INVALID_VALUE == psCXT_EXEC_EXTN->m_sID_Font_ROM__DOS_Font_Block.m_uiKI)
            psCXT_EXEC_EXTN->m_sID_Font_ROM__DOS_Font_Block = tgKN_GPU_TX_IMG_Inst__IncRef( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Black_709 );
        tgKN_GPU_EXT_Register_Default_TX_IMG_Inst( psCXT_EXEC_EXTN->m_sID_Font_ROM__DOS_Font_Block );

        psCXT_EXEC_EXTN->m_sID_Font_ROM__DOS_Font_Marcio = tgKN_GPU_TX_IMG_Inst__Font_ROM( uCMD, &g_sKN_GPU_STD_DOS_Font[ETgKN_GPU_DOS_FONT_ROM_MARCIO] );
        if (KTgID__INVALID_VALUE == psCXT_EXEC_EXTN->m_sID_Font_ROM__DOS_Font_Marcio.m_uiKI)
            psCXT_EXEC_EXTN->m_sID_Font_ROM__DOS_Font_Marcio = tgKN_GPU_TX_IMG_Inst__IncRef( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Black_709 );
        tgKN_GPU_EXT_Register_Default_TX_IMG_Inst( psCXT_EXEC_EXTN->m_sID_Font_ROM__DOS_Font_Marcio );
    //# TgCOMPILE__RENDER_DEBUG_OUTPUT
    #else
        tgKN_GPU_EXT_Register_Default_TX_IMG_Inst( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Black_709 );
        tgKN_GPU_EXT_Register_Default_TX_IMG_Inst( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Black_709 );
        tgKN_GPU_EXT_Register_Default_TX_IMG_Inst( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Black_709 );
        tgKN_GPU_EXT_Register_Default_TX_IMG_Inst( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Black_709 );
    //# TgCOMPILE__RENDER_DEBUG_OUTPUT
    #endif

        /* Reference image to be used during testing. */

    #if TgS_DEBUG__KERNEL || TgS_DEBUG__RENDER
        psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Reference_G10_P709_00 = tgKN_GPU_TX_IMG__Load_TIFF_From_OS_File_System( uCMD, g_tiKN_FS_HDD__Mount_APP, nullptr,
                                                                                                                   u8"DeltaE_16bit_G10.tif",
                                                                                                                   ETgKN_GPU_ALLOCATOR__VIDEO_MEMORY_WRITEONLY );
        if (KTgID__INVALID_VALUE == psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Reference_G10_P709_00.m_uiKI)
            psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Reference_G10_P709_00 = tgKN_GPU_TX_IMG_Inst__IncRef( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Black_709 );
        tgKN_GPU_EXT_Register_Default_TX_IMG_Inst( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Reference_G10_P709_00 );

        psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_MIP_1024x1024 = tgKN_GPU_TX_IMG_Inst__Init_MIP( uCMD, 1024, 1024, u8"MIP 1024x1024");
        if (KTgID__INVALID_VALUE == psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_MIP_1024x1024.m_uiKI)
            psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_MIP_1024x1024 = tgKN_GPU_TX_IMG_Inst__IncRef( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Black_709 );
        tgKN_GPU_EXT_Register_Default_TX_IMG_Inst( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_MIP_1024x1024 );

        psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_MIP_0512x0512 = tgKN_GPU_TX_IMG_Inst__Init_MIP( uCMD, 512, 512, u8"MIP 512x512");
        if (KTgID__INVALID_VALUE == psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_MIP_0512x0512.m_uiKI)
            psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_MIP_0512x0512 = tgKN_GPU_TX_IMG_Inst__IncRef( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Black_709 );
        tgKN_GPU_EXT_Register_Default_TX_IMG_Inst( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_MIP_0512x0512 );

        psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_MIP_0256x0256 = tgKN_GPU_TX_IMG_Inst__Init_MIP( uCMD, 256, 256, u8"MIP 256x256");
        if (KTgID__INVALID_VALUE == psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_MIP_0256x0256.m_uiKI)
            psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_MIP_0256x0256 = tgKN_GPU_TX_IMG_Inst__IncRef( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Black_709 );
        tgKN_GPU_EXT_Register_Default_TX_IMG_Inst( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_MIP_0256x0256 );

        psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_MIP_0128x0128 = tgKN_GPU_TX_IMG_Inst__Init_MIP( uCMD, 128, 128, u8"MIP 128x128");
        if (KTgID__INVALID_VALUE == psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_MIP_0128x0128.m_uiKI)
            psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_MIP_0128x0128 = tgKN_GPU_TX_IMG_Inst__IncRef( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Black_709 );
        tgKN_GPU_EXT_Register_Default_TX_IMG_Inst( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_MIP_0128x0128 );

        psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_MIP_0064x0064 = tgKN_GPU_TX_IMG_Inst__Init_MIP( uCMD, 64, 64, u8"MIP 64x64");
        if (KTgID__INVALID_VALUE == psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_MIP_0064x0064.m_uiKI)
            psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_MIP_0064x0064 = tgKN_GPU_TX_IMG_Inst__IncRef( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Black_709 );
        tgKN_GPU_EXT_Register_Default_TX_IMG_Inst( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_MIP_0064x0064 );

        psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Gamma_Test = tgKN_GPU_TX_IMG_Inst__Init_Gamma_Test( uCMD, 256, 256, u8"Gamma Test");
        if (KTgID__INVALID_VALUE == psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Gamma_Test.m_uiKI)
            psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Gamma_Test = tgKN_GPU_TX_IMG_Inst__IncRef( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Black_709 );
        tgKN_GPU_EXT_Register_Default_TX_IMG_Inst( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Gamma_Test );

        psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Target = tgKN_GPU_TX_IMG_Inst__IncRef( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Black_709 );
        tgKN_GPU_EXT_Register_Default_TX_IMG_Inst( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Target );

        psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Error = tgKN_GPU_TX_IMG_Inst__Init_Checker_Pattern( uCMD, 64, 64, KTg_YELLOW_G10_P709_U32,  KTg_MAGENTA_G10_P709_U32, u8"Error");
        if (KTgID__INVALID_VALUE == psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Error.m_uiKI)
            psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Error = tgKN_GPU_TX_IMG_Inst__IncRef( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Black_709 );
        tgKN_GPU_EXT_Register_Default_TX_IMG_Inst( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Error );

        psCXT_EXEC_EXTN->m_sID_TX_CBE_INST_Error = tgKN_GPU_TX_CBE_Inst__IncRef( psCXT_EXEC_EXTN->m_sID_TX_CBE_INST_Black_709 );
        tgKN_GPU_EXT_Register_Default_TX_CBE_Inst( psCXT_EXEC_EXTN->m_sID_TX_CBE_INST_Error );

        psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Standard_1080 = tgKN_GPU_TX_IMG_Inst__IncRef( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Black_709 );
        tgKN_GPU_EXT_Register_Default_TX_IMG_Inst( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Standard_1080 );

        psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Standard_0720 = tgKN_GPU_TX_IMG_Inst__IncRef( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Black_709 );
        tgKN_GPU_EXT_Register_Default_TX_IMG_Inst( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Standard_0720 );

        psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Standard_NTSC = tgKN_GPU_TX_IMG_Inst__IncRef( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Black_709 );
        tgKN_GPU_EXT_Register_Default_TX_IMG_Inst( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Standard_NTSC );

        psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Standard_PAL = tgKN_GPU_TX_IMG_Inst__IncRef( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Black_709 );
        tgKN_GPU_EXT_Register_Default_TX_IMG_Inst( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Standard_PAL );
    //# TgS_DEBUG__KERNEL || TgS_DEBUG__RENDER
    #else
        tgKN_GPU_EXT_Register_Default_TX_IMG_Inst( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Black_709 );
        tgKN_GPU_EXT_Register_Default_TX_IMG_Inst( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Black_709 );
        tgKN_GPU_EXT_Register_Default_TX_IMG_Inst( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Black_709 );
        tgKN_GPU_EXT_Register_Default_TX_IMG_Inst( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Black_709 );
        tgKN_GPU_EXT_Register_Default_TX_IMG_Inst( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Black_709 );
        tgKN_GPU_EXT_Register_Default_TX_IMG_Inst( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Black_709 );
        tgKN_GPU_EXT_Register_Default_TX_IMG_Inst( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Black_709 );
        tgKN_GPU_EXT_Register_Default_TX_IMG_Inst( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Black_709 );
        tgKN_GPU_EXT_Register_Default_TX_IMG_Inst( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Black_709 );
        tgKN_GPU_EXT_Register_Default_TX_CBE_Inst( psCXT_EXEC_EXTN->m_sID_TX_CBE_INST_Black_709 );
        tgKN_GPU_EXT_Register_Default_TX_IMG_Inst( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Black_709 );
        tgKN_GPU_EXT_Register_Default_TX_IMG_Inst( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Black_709 );
        tgKN_GPU_EXT_Register_Default_TX_IMG_Inst( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Black_709 );
        tgKN_GPU_EXT_Register_Default_TX_IMG_Inst( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Black_709 );
    //# TgS_DEBUG__KERNEL || TgS_DEBUG__RENDER
    #endif

    #if TgCOMPILE__RENDER_DEBUG_OUTPUT
    {
        TgVOID                              (* const pfnInit_Mesh[])( TgKN_GPU_DBG_PM_Generate_PC ) = { tgKN_GPU_DBG_Init_Mesh_Plane,
                                                                                                        tgKN_GPU_DBG_Init_Mesh_Box,
                                                                                                        tgKN_GPU_DBG_Init_Mesh_Sphere,
                                                                                                        tgKN_GPU_DBG_Init_Mesh_Capsule,
                                                                                                        tgKN_GPU_DBG_Init_Mesh_Cone,
                                                                                                        tgKN_GPU_DBG_Init_Mesh_Cylinder,
                                                                                                        tgKN_GPU_DBG_Init_Mesh_Tube };
        ETgKN_GPU_DEBUG_PM                  enPM;

        for (enPM = ETgKN_GPU_DEBUG_PM_3D_START; enPM < ETgKN_GPU_DEBUG_PM_3D_END; ++enPM)
        {
            TgKN_GPU_DBG_PM_Generate            sGenerate;

            tgMM_Set_U08_0x00( &sGenerate, sizeof(sGenerate) );
            sGenerate.m_uiTessellate = 3;
            pfnInit_Mesh[enPM - ETgKN_GPU_DEBUG_PM_3D_START]( &sGenerate ); /* Calculate the size of the index pool needed. */
            sGenerate.m_puiIndex = (TgUINT_E16_P)TgMALLOC_POOL( sGenerate.m_nuiMax_Index * sizeof(TgUINT_E16) );
            pfnInit_Mesh[enPM - ETgKN_GPU_DEBUG_PM_3D_START]( &sGenerate ); /* Calculate the size of the vertex pool needed. */
            sGenerate.m_psVertex = (STg2_KN_GPU_Vertex_Geom_02_P)TgMALLOC_POOL( sGenerate.m_nuiMax_Vertex  * sizeof( STg2_KN_GPU_Vertex_Geom_02 ) );
            pfnInit_Mesh[enPM - ETgKN_GPU_DEBUG_PM_3D_START]( &sGenerate ); /* Calculate the final geometry. This is inefficient as tessellation is run twice. */

            tgKN_GPU_EXT__Execute__Register_Debug_Geometry( uCMD, enPM, &sGenerate );

            TgFREE_POOL(sGenerate.m_psVertex);
            TgFREE_POOL(sGenerate.m_puiIndex);
        }
    }
    //# TgCOMPILE__RENDER_DEBUG_OUTPUT
    #endif

    #if TgCOMPILE__RENDER_DEBUG_OUTPUT || TgS_DEBUG__KERNEL || TgS_DEBUG__RENDER
    {
        TgRESULT_C iRet = tgKN_GPU_EXT__Execute__Init_Debug( uCMD );
        tgKN_GPU_EXT__CMD__Command_List_Close( uCMD );
        tgKN_GPU_EXT__Execute__Frame_End( tiCXT_WORK );
        return (TgFAILED( iRet ) ? KTgE_FAIL : KTgS_OK);
    }
    //# TgCOMPILE__RENDER_DEBUG_OUTPUT || TgS_DEBUG__KERNEL || TgS_DEBUG__RENDER
    #else
        return (KTgS_OK);
    //# TgCOMPILE__RENDER_DEBUG_OUTPUT || TgS_DEBUG__KERNEL || TgS_DEBUG__RENDER
    #endif
    }
}


/* ---- tgKN_GPU__Execute__Free_Debug -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU__Execute__Free_Debug( TgKN_GPU_CXT_EXEC_ID_C tiCXT_EXEC )
{
    TgPARAM_CHECK_INDEX( tiCXT_EXEC.m_uiI, g_asKN_GPU_CXT_EXEC );
    TgPARAM_CHECK( tgKN_GPU_CXT_EXEC_ID_Is_Equal( &(g_asKN_GPU_CXT_EXEC[tiCXT_EXEC.m_uiI].m_tiCXT_EXEC_S), tiCXT_EXEC ) );
    {
        STg2_KN_GPU_CXT_EXEC_EXTN_PC        psCXT_EXEC_EXTN = g_asKN_GPU_CXT_EXEC_EXT + tiCXT_EXEC.m_uiI;

        (void)psCXT_EXEC_EXTN;

    #if TgCOMPILE__RENDER_DEBUG_OUTPUT
        tgKN_GPU_TX_IMG_Inst__Release( psCXT_EXEC_EXTN->m_sID_Font_ROM__DOS_Font_Default );
        tgKN_GPU_TX_IMG_Inst__Release( psCXT_EXEC_EXTN->m_sID_Font_ROM__DOS_Font_Future );
        tgKN_GPU_TX_IMG_Inst__Release( psCXT_EXEC_EXTN->m_sID_Font_ROM__DOS_Font_Block );
        tgKN_GPU_TX_IMG_Inst__Release( psCXT_EXEC_EXTN->m_sID_Font_ROM__DOS_Font_Marcio );
    //# TgCOMPILE__RENDER_DEBUG_OUTPUT
    #endif

    #if TgS_DEBUG__KERNEL || TgS_DEBUG__RENDER
        tgKN_GPU_TX_IMG_Inst__Release( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Reference_G10_P709_00 );
        tgKN_GPU_TX_IMG_Inst__Release( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_MIP_1024x1024 );
        tgKN_GPU_TX_IMG_Inst__Release( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_MIP_0512x0512 );
        tgKN_GPU_TX_IMG_Inst__Release( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_MIP_0256x0256 );
        tgKN_GPU_TX_IMG_Inst__Release( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_MIP_0128x0128 );
        tgKN_GPU_TX_IMG_Inst__Release( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_MIP_0064x0064 );
        tgKN_GPU_TX_IMG_Inst__Release( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Gamma_Test );
        tgKN_GPU_TX_IMG_Inst__Release( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Target );
        tgKN_GPU_TX_IMG_Inst__Release( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Error );
        tgKN_GPU_TX_CBE_Inst__Release( psCXT_EXEC_EXTN->m_sID_TX_CBE_INST_Error );
        tgKN_GPU_TX_IMG_Inst__Release( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Standard_1080 );
        tgKN_GPU_TX_IMG_Inst__Release( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Standard_0720 );
        tgKN_GPU_TX_IMG_Inst__Release( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Standard_NTSC );
        tgKN_GPU_TX_IMG_Inst__Release( psCXT_EXEC_EXTN->m_sID_TX_IMG_INST_Standard_PAL );
    //# TgS_DEBUG__KERNEL || TgS_DEBUG__RENDER
    #endif

        tgKN_GPU_EXT__Execute__Free_Debug( tiCXT_EXEC );
    }
}
