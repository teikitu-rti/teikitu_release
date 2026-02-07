/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Kernel - File IO.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_IF__Open ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_IF__Open( STg2_Input_File_PCU psIN_File, TgKN_FS_MOUNT_ID_C tiFS_Mount, TgUINT_E32_C uiPath, TgUINT_E32_C uiFile )
{
    STg2_KN_File_Open_Command           sOpen_Cmd;

    tgMM_Set_U08_0x00( psIN_File, sizeof( STg2_Input_File ) );

    sOpen_Cmd.m_tiFS_Mount = tiFS_Mount;
    sOpen_Cmd.m_uiPath = uiPath;
    sOpen_Cmd.m_uiFile = uiFile;
    sOpen_Cmd.m_uiMode = ETgFILE_IO_ACCESS__READ | ETgFILE_IO_ACCESS__SHARED;
    sOpen_Cmd.m_iCache = 0;
    sOpen_Cmd.m_pszFile_Name = nullptr;

    psIN_File->m_tiFile = tgKN_FS_BL_Open( &sOpen_Cmd );

    if (KTgID__INVALID_VALUE == psIN_File->m_tiFile.m_uiKI)
    {
        return (KTgE_FAIL);
    };

    /* Assign the base structure (v-table) */
    psIN_File->m_sInput.m_pfnRead = tgKN_IF__Read;
    psIN_File->m_sInput.m_pfnEnd_Of_File = tgKN_IF__End_Of_File;
    psIN_File->m_sInput.m_pfnClose = tgKN_IF__Close;

    return (KTgS_OK);
}


/* ---- tgKN_IF__Read ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRSIZE tgKN_IF__Read( TgVOID_P pData, TgRSIZE_C nbyData, STg2_Input_PC psIN, TgATTRIBUTE_UNUSED TgRSIZE_C uiOffset, TgRSIZE_C uiRead )
{
    union
    {
        STg2_Input_File_P                   psIN_File;
        STg2_Input_P                        psIN;
    }                                   sIN;
    STg2_KN_File_Read_Command           sRead_Cmd;

    sIN.psIN = psIN;

    sRead_Cmd.m_tiFile = sIN.psIN_File->m_tiFile;
    sRead_Cmd.m_pfnAllocator = 0;
    sRead_Cmd.m_pBuffer = pData;
    sRead_Cmd.m_nuiBuffer = tgCM_MIN_UMAX( nbyData, uiRead );
    sRead_Cmd.m_nuiResult = 0;
    sRead_Cmd.m_pfnFinish = 0;
    sRead_Cmd.m_uiParam = 0;

    tgKN_FS_BL_Read( &sRead_Cmd );

    return (sRead_Cmd.m_nuiResult);
}


/* ---- tgKN_IF__Close ----------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_IF__Close( STg2_Input_PC psIN )
{
    union
    {
        STg2_Input_File_P                   psIN_File;
        STg2_Input_P                        psIN;
    }                                   sIN;

    sIN.psIN = psIN;
    tgKN_FS_BL_Close( sIN.psIN_File->m_tiFile );
    sIN.psIN_File->m_tiFile = KTgKN_FILE_ID__INVALID;
    
    return (KTgS_OK);
}


/* ---- tgKN_IF__End_Of_File ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgKN_IF__End_Of_File( STg2_Input_PC psIN, TgRSIZE_C uiOffset )
{
    union
    {
        STg2_Input_File_P                   psIN_File;
        STg2_Input_P                        psIN;
    }                                   sIN;

    sIN.psIN = psIN;

    if (!tgKN_FILE_ID_Is_Equal( &g_asKN_File_Info[sIN.psIN_File->m_tiFile.m_uiI].m_tiFile_Singleton, sIN.psIN_File->m_tiFile ))
    {
        return (true);
    };

    return (uiOffset < g_asKN_File_Info[sIN.psIN_File->m_tiFile.m_uiI].m_uiSize ? false : true);
}


/* ---- tgKN_OF__Open ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_OF__Open( STg2_Output_File_PCU psOUT_File, TgKN_FS_MOUNT_ID_C tiFS_Mount, TgUINT_E32_C uiPath, TgUINT_E32_C uiFile )
{
    STg2_KN_File_Open_Command           sOpen_Cmd;

    /* Close down the file if it has a valid close function */
    if (nullptr != psOUT_File->m_sOutput.m_pfnClose)
    {
        psOUT_File->m_sOutput.m_pfnClose( &psOUT_File->m_sOutput );
    };

    /* Clear the structure */
    tgMM_Set_U08_0x00( psOUT_File, sizeof( STg2_Output_File ) );

    /* Open the file at the given path for write exclusive */
    sOpen_Cmd.m_tiFS_Mount = tiFS_Mount;
    sOpen_Cmd.m_uiPath = uiPath;
    sOpen_Cmd.m_uiFile = uiFile;
    sOpen_Cmd.m_uiMode = ETgFILE_IO_ACCESS__WRITE | ETgFILE_IO_ACCESS__SHARED;
    sOpen_Cmd.m_iCache = 0;
    sOpen_Cmd.m_pszFile_Name = nullptr;

    psOUT_File->m_tiFile = tgKN_FS_BL_Open( &sOpen_Cmd );

    if (KTgID__INVALID_VALUE == psOUT_File->m_tiFile.m_uiKI)
    {
        return (KTgE_FAIL);
    };

    /* Assign the base structure (v-table) */
    psOUT_File->m_sOutput.m_pfnWrite = tgKN_OF__Write;
    psOUT_File->m_sOutput.m_pfnClose = tgKN_OF__Close;

    return (KTgS_OK);
}


/* ---- tgKN_OF__Close ----------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_OF__Close( STg2_Output_PC psOUT )
{
    union
    {
        STg2_Output_File_P                  psOUT_File;
        STg2_Output_P                       psOUT;
    }                                   sOUT;

    sOUT.psOUT = psOUT;
    tgKN_FS_BL_Close( sOUT.psOUT_File->m_tiFile );
    sOUT.psOUT_File->m_tiFile = KTgKN_FILE_ID__INVALID;
    
    return (KTgS_OK);
}


/* ---- tgKN_OF__Write ----------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRSIZE tgKN_OF__Write( STg2_Output_PC psOUT, TgATTRIBUTE_UNUSED TgRSIZE_C uiOffset, TgVOID_CPC pbyData, TgRSIZE_C nuiData )
{
    union
    {
        STg2_Output_File_P                  psOUT_File;
        STg2_Output_P                       psOUT;
    }                                   sOUT;
    STg2_KN_File_Write_Command          sWrite_Cmd;

    sOUT.psOUT = psOUT;

    sWrite_Cmd.m_tiFile = sOUT.psOUT_File->m_tiFile;
    sWrite_Cmd.m_pBuffer = pbyData;
    sWrite_Cmd.m_nuiBuffer = nuiData;
    sWrite_Cmd.m_nuiResult = 0;
    sWrite_Cmd.m_pfnFinish = 0;
    sWrite_Cmd.m_uiParam = 0;

    tgKN_FS_BL_Write( &sWrite_Cmd );

    return (sWrite_Cmd.m_nuiResult);
}
