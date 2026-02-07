/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Kernel - File System - HDD.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Types                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgTYPE_STRUCT(STg2_KN_FS_HDD__Mount_File_Table,)
{
    TgALIGN(TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE)
    STg2_UT_LF__HT_RW                           m_asFile;
    TgSTRING_DICT_ID                            m_tiPathName;
#if 0 != (248 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE)
    TgUINT_E08                                  m_uiPad0[248 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE];
#endif
};

TgTYPE_STRUCT(STg2_KN_FS_HDD__Mount,)
{
    TgALIGN(TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE)
    TgKN_FS_MOUNT_ID                            m_tiFS_Mount;
    TgCHAR_U8                                   m_szMount_Root[KTgMAX_FILE_PATH];
    TgSINT_E32                                  m_iPad;
    TgUINT_E32                                  m_nuiFS_File_Table;
    STg2_KN_FS_HDD__Mount_File_Table_P          m_asFS_File_Table;
#if 0 != (TgSELECT_OS_WINDOW(232,248) % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE)
    TgUINT_E08                                  m_uiPad0[TgSELECT_OS_WINDOW(232,248) % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE];
#endif
    STg2_UT_LF__HT_RW                           m_sFS_Path_Table;
};




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

static TgVOID                               tgKN_FS_HDD__FQN( TgCHAR_U8_PC, TgRSIZE_C, STg2_KN_File_Job_PC, STg2_KN_FS_HDD__Mount_PC, TgBOOL_C bCreate );
static TgVOID                               tgKN_FS_HDD__Mount__Init_Table_Entry( TgKN_FS_MOUNT_ID_C, TgCHAR_U8_CP );

static STg2_KN_FS_HDD__Mount                s_asKN_FS_HDD__Mount[KTgKN_MAX_FILE_SYSTEM_MOUNT];
static TgSINT_PTR                           s_aiKN_HDD_File_Info[KTgKN_MAX_FILE_OPEN];




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_FS_HDD__Free_Space -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRSIZE tgKN_FS_HDD__Free_Space( TgATTRIBUTE_UNUSED_PARAM_CHECK TgKN_FS_MOUNT_ID_C tiFS_Mount )
{
#if TgCOMPILE_ASSERT && TgCOMPILE_ASSERT__ERROR
    STg2_KN_FS_Mount_P                  psFS_Mount;
    STg2_KN_FS_HDD__Mount_P             psFS_HDD_Mount;

    psFS_Mount = g_asKN_FS_Mount + tiFS_Mount.m_uiI;
    TgERROR( tgKN_FS_MOUNT_ID_Is_Equal( &psFS_Mount->m_tiFS_Mount_Singleton, tiFS_Mount ) );
    psFS_HDD_Mount = s_asKN_FS_HDD__Mount + tiFS_Mount.m_uiI;
    TgERROR( psFS_HDD_Mount->m_tiFS_Mount.m_uiKI == tiFS_Mount.m_uiKI );
/*# TgCOMPILE_ASSERT && TgCOMPILE_ASSERT__PARAM_CHECK */
#endif

    /* #IMPLEMENT */
    return (0);
}


/* ---- tgKN_FS_HDD__Mount ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_FS_HDD__Mount( TgKN_FS_MOUNT_ID_C tiFS_Mount, TgCHAR_U8_CPCU mbzMountPath )
{
    STg2_Find_File                      sFind_File;
    STg2_KN_FS_Mount_P                  psFS_Mount;
    STg2_KN_FS_HDD__Mount_P             psFS_HDD_Mount;

    psFS_Mount = g_asKN_FS_Mount + tiFS_Mount.m_uiI;
    TgERROR( tgKN_FS_MOUNT_ID_Is_Equal( &psFS_Mount->m_tiFS_Mount_Singleton, tiFS_Mount ) );
    psFS_HDD_Mount = s_asKN_FS_HDD__Mount + tiFS_Mount.m_uiI;

    psFS_HDD_Mount->m_tiFS_Mount = tgKN_FS_MOUNT_ID_Query_Unsafe( &psFS_Mount->m_tiFS_Mount_Singleton );

    tgCM_Path_Copy( psFS_HDD_Mount->m_szMount_Root, TgARRAY_COUNT( psFS_HDD_Mount->m_szMount_Root ), mbzMountPath, KTgMAX_RSIZE );
    psFS_HDD_Mount->m_nuiFS_File_Table = 0;
    psFS_HDD_Mount->m_asFS_File_Table = (STg2_KN_FS_HDD__Mount_File_Table_P)TgRESERVE_VIRTUAL( KTgKN_MAX_FILE_FOLDERS * sizeof( STg2_KN_FS_HDD__Mount_File_Table ) );
    TgVERIFY(TgSUCCEEDED(tgCM_UT_LF__HT_RW__Init_Virtual( &psFS_HDD_Mount->m_sFS_Path_Table, sizeof(TgRSIZE), 1, KTgKN_MAX_FILE_FOLDERS )));

    tgCM_Path_Copy( sFind_File.m_szFind, TgARRAY_COUNT( sFind_File.m_szFind ), psFS_HDD_Mount->m_szMount_Root, TgARRAY_COUNT( psFS_HDD_Mount->m_szMount_Root ) );
    tgCM_Path_Append( sFind_File.m_szFind, TgARRAY_COUNT( sFind_File.m_szFind ), u8"\\*", KTgMAX_RSIZE );

    tgKN_FS_HDD__Mount__Init_Table_Entry( tiFS_Mount, u8"" );

    if (TgFAILED(tgIO_Folder_Find_First( &sFind_File )))
    {
        return;
    };

    do
    {
        tgKN_FS_HDD__Mount__Init_Table_Entry( tiFS_Mount, sFind_File.m_szResult );
    }
    while (TgSUCCEEDED(tgIO_Folder_Find_Next( &sFind_File )));

    tgIO_Folder_Find_Close( &sFind_File );
}


/* ---- tgKN_FS_HDD__Execute_Job ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_FS_HDD__Execute_Job( STg2_KN_File_Job_P psJob )
{
    STg2_KN_File_Info_P                 psFile_Info;
    STg2_KN_FS_HDD__Mount_P             psFS_HDD_Mount;
    TgUINT_E32                          uiFile;
    TgBOOL                              bCreate;
    TgCHAR_U8                           szFull_Path[KTgMAX_FILE_PATH];
    TgRSIZE                             uiFile_Size;

    psFile_Info = g_asKN_File_Info + psJob->m_tiFile.m_uiI;
    TgERROR( tgKN_FILE_ID_Is_Equal( &psFile_Info->m_tiFile_Singleton, psJob->m_tiFile ) );
    psFS_HDD_Mount = s_asKN_FS_HDD__Mount + psFile_Info->m_tiFS_Mount.m_uiI;
    TgERROR( psFile_Info->m_tiFS_Mount.m_uiKI == psFS_HDD_Mount->m_tiFS_Mount.m_uiKI );

#if TgCOMPILE_ASSERT && TgCOMPILE_ASSERT__ERROR
    {
        STg2_KN_FS_Mount_P                  psFS_Mount;
        STg2_KN_File_System_P               psFS;

        psFS_Mount = g_asKN_FS_Mount + psFile_Info->m_tiFS_Mount.m_uiI;
        TgERROR( tgKN_FS_MOUNT_ID_Is_Equal( &psFS_Mount->m_tiFS_Mount_Singleton, psFile_Info->m_tiFS_Mount ) );
        psFS = g_asKN_FS + psFile_Info->m_tiFS.m_uiI;
        TgERROR( tgKN_FILE_SYSTEM_ID_Is_Equal( &psFS->m_tiFS_Singleton, psFile_Info->m_tiFS ) );
    }
/*# TgCOMPILE_ASSERT && TgCOMPILE_ASSERT__PARAM_CHECK */
#endif

    uiFile = psJob->m_tiFile.m_uiI;

    switch (psJob->m_enCmd)
    {
        case ETgFILE_COMMAND__OPEN:
            /* Generate a text string containing the full path for the file */
            bCreate = ETgFILE_IO_ACCESS__CREATE == (psJob->m_sCmd.m_sOpen.m_uiMode & ETgFILE_IO_ACCESS__CREATE);
            tgKN_FS_HDD__FQN( szFull_Path, TgARRAY_COUNT( szFull_Path ), psJob, psFS_HDD_Mount, bCreate );
            if (0 == szFull_Path[0])
            {
                TgSTD_ATOMIC(store)( &psJob->m_xuiStatus, ETgKN_IO_STATUS__INVALID );
                break;
            };

            s_aiKN_HDD_File_Info[uiFile] = tgIO_File_Open( szFull_Path, sizeof(szFull_Path), g_asKN_File_Info[uiFile].m_uiMode );
            if (s_aiKN_HDD_File_Info[uiFile] < 0)
            {
                TgSTD_ATOMIC(store)( &psJob->m_xuiStatus, ETgKN_IO_STATUS__INVALID );
                break;
            };

            uiFile_Size = tgIO_File_Size( s_aiKN_HDD_File_Info[uiFile] );
            TgERROR( uiFile_Size < (TgRSIZE)KTgMAX_S32 );

            g_asKN_File_Info[uiFile].m_uiSize = uiFile_Size;
            g_asKN_File_Info[uiFile].m_uiPos = 0;

            if (psJob->m_sCmd.m_sOpen.m_iCache > 0)
            {
                g_asKN_File_Info[uiFile].m_puiCache = (TgUINT_E08_P)TgMALLOC_POOL( (TgRSIZE)psJob->m_sCmd.m_sOpen.m_iCache );
                TgCRITICAL_MSGF( nullptr != g_asKN_File_Info[uiFile].m_puiCache, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to allocate memory." );
                g_asKN_File_Info[uiFile].m_uiCache_Size = (TgRSIZE)psJob->m_sCmd.m_sOpen.m_iCache;
            };
            TgSTD_ATOMIC(store)( &psJob->m_xuiStatus, ETgKN_IO_STATUS__DONE );
            tgKN_FS_Job_Complete( psJob );
            break;

        case ETgFILE_COMMAND__READ_ASYNC:
            if (g_asKN_File_Info[psJob->m_tiFile.m_uiI].m_uiSize <= g_asKN_File_Info[psJob->m_tiFile.m_uiI].m_uiPos)
            {
                TgSTD_ATOMIC(store)( &psJob->m_xuiStatus, ETgKN_IO_STATUS__INVALID );
                break;
            };

            /* Check to see if a buffer should be allocated.  All memory management is the responsibility of the call back function.  Obviously, all allocator functions */
            /* would have to be multi-thread and concurrent safe. */
            if ((0 == psJob->m_sCmd.m_sRead.m_pBuffer) && (0 != psJob->m_sCmd.m_sRead.m_pfnAllocator))
            {
                psJob->m_sCmd.m_sRead.m_nuiBuffer = g_asKN_File_Info[uiFile].m_uiSize - g_asKN_File_Info[uiFile].m_uiPos;
                psJob->m_sCmd.m_sRead.m_pBuffer = psJob->m_sCmd.m_sRead.m_pfnAllocator( psJob->m_sCmd.m_sRead.m_nuiBuffer );
            };

            if (nullptr == psJob->m_sCmd.m_sRead.m_pBuffer)
            {
                TgSTD_ATOMIC(store)( &psJob->m_xuiStatus, ETgKN_IO_STATUS__INVALID );
                break;
            };

            TgERROR( 0 < psJob->m_sCmd.m_sRead.m_nuiBuffer );

            psJob->m_sCmd.m_sRead.m_nuiResult = tgIO_File_Read( psJob->m_sCmd.m_sRead.m_pBuffer, s_aiKN_HDD_File_Info[uiFile], psJob->m_sCmd.m_sRead.m_nuiBuffer );

            g_asKN_File_Info[uiFile].m_uiPos += psJob->m_sCmd.m_sRead.m_nuiResult;

            TgSTD_ATOMIC(store)( &psJob->m_xuiStatus, ETgKN_IO_STATUS__DONE );
            tgKN_FS_Job_Complete( psJob );
            break;

        case ETgFILE_COMMAND__WRITE_ASYNC:
            TgERROR( 0 != psJob->m_sCmd.m_sWrite.m_pBuffer );
            TgERROR( 0 < psJob->m_sCmd.m_sWrite.m_nuiBuffer );

            /* Copy the data from the cache into the read buffer */
            if (psFile_Info->m_uiCache_Size - psFile_Info->m_uiCache_Pos < psJob->m_sCmd.m_sWrite.m_nuiBuffer)
            {
                /* Need to flush out the cache before writing the parameter data */
                if (psFile_Info->m_uiCache_Pos > 0)
                {
                    psFile_Info->m_uiPos += tgIO_File_Write( s_aiKN_HDD_File_Info[uiFile], psFile_Info->m_puiCache, psFile_Info->m_uiCache_Pos );
                    psFile_Info->m_uiCache_Pos = 0;
                };

                psJob->m_sCmd.m_sWrite.m_nuiResult = tgIO_File_Write( s_aiKN_HDD_File_Info[uiFile], psJob->m_sCmd.m_sWrite.m_pBuffer, psJob->m_sCmd.m_sWrite.m_nuiBuffer );

                psFile_Info->m_uiPos += psJob->m_sCmd.m_sWrite.m_nuiResult;
            }
            else
            {
                /* Add the write request into the cache (write combining) */
                tgMM_Copy( psFile_Info->m_puiCache + psFile_Info->m_uiCache_Pos, KTgMAX_RSIZE, psJob->m_sCmd.m_sWrite.m_pBuffer, psJob->m_sCmd.m_sWrite.m_nuiBuffer );
                psFile_Info->m_uiCache_Pos += psJob->m_sCmd.m_sWrite.m_nuiBuffer;
                psJob->m_sCmd.m_sWrite.m_nuiResult = psJob->m_sCmd.m_sWrite.m_nuiBuffer;
            };

            TgSTD_ATOMIC(store)( &psJob->m_xuiStatus, ETgKN_IO_STATUS__DONE );
            tgKN_FS_Job_Complete( psJob );
            break;

        case ETgFILE_COMMAND__FLUSH:
            if (psFile_Info->m_uiCache_Pos > 0)
            {
                psFile_Info->m_uiPos += tgIO_File_Write( s_aiKN_HDD_File_Info[uiFile], psFile_Info->m_puiCache, psFile_Info->m_uiCache_Pos );
                psFile_Info->m_uiCache_Pos = 0;
            };

            /* If the file flush failed for any reason - emit a warning to the console and return the failure state. */
            if (TgFAILED( tgIO_File_Flush( s_aiKN_HDD_File_Info[uiFile] ) ))
            {
                TgWARNING_MSGF( 0, STD_MSG_PREFIX u8"File handle is invalid (thread).\n", STD_MSG_POST );
            };

            TgSTD_ATOMIC(store)( &psJob->m_xuiStatus, ETgKN_IO_STATUS__DONE );
            tgKN_FS_Job_Complete( psJob );
            break;

        case ETgFILE_COMMAND__CLOSE:
            /* Write back any data in the cache before closing the file */
            if (psFile_Info->m_uiCache_Pos > 0)
            {
                psFile_Info->m_uiPos += tgIO_File_Write( s_aiKN_HDD_File_Info[uiFile], psFile_Info->m_puiCache, psFile_Info->m_uiCache_Pos );
                psFile_Info->m_uiCache_Pos = 0;
            };

            /* If the file flush failed for any reason - emit a warning to the console and return the failure state. */
            if (TgFAILED( tgIO_File_Close( s_aiKN_HDD_File_Info[uiFile] ) ))
            {
                TgWARNING_MSGF( 0, STD_MSG_PREFIX u8"File handle is invalid (thread).\n", STD_MSG_POST );
            };

            s_aiKN_HDD_File_Info[uiFile] = -1;
            TgSTD_ATOMIC(store)( &psJob->m_xuiStatus, ETgKN_IO_STATUS__DONE );
            tgKN_FS_Job_Complete( psJob );
            break;

        case ETgFILE_COMMAND__UNKNOWN:
        case ETgFILE_COMMAND__CACHE:
        case ETgFILE_COMMAND__CANCEL:
            TgS_NO_DEFAULT( break );
    };

    tgKN_FILE_JOB_ID_Invalidate( &psJob->m_tiFile_Job_Singleton );
}


/* ---- tgKN_FS_HDD__Mount_Free -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_FS_HDD__Mount_Free( TgKN_FS_MOUNT_ID_C tiFS_Mount )
{
    STg2_KN_FS_HDD__Mount_P             psFS_HDD_Mount;
    TgUINT_E32                          uiIndex;

#if TgCOMPILE_ASSERT && TgCOMPILE_ASSERT__ERROR
    {
        STg2_KN_FS_Mount_P                  psFS_Mount;

        psFS_Mount = g_asKN_FS_Mount + tiFS_Mount.m_uiI;
        TgERROR( tgKN_FS_MOUNT_ID_Is_Equal( &psFS_Mount->m_tiFS_Mount_Singleton, tiFS_Mount ) );
    }
/*# TgCOMPILE_ASSERT && TgCOMPILE_ASSERT__PARAM_CHECK */
#endif

    psFS_HDD_Mount = s_asKN_FS_HDD__Mount + tiFS_Mount.m_uiI;
    TgERROR( psFS_HDD_Mount->m_tiFS_Mount.m_uiKI == tiFS_Mount.m_uiKI );

    for (uiIndex = 0; uiIndex < psFS_HDD_Mount->m_nuiFS_File_Table; ++uiIndex)
    {
        tgCM_UT_LF__HT_RW__Free( &psFS_HDD_Mount->m_asFS_File_Table[uiIndex].m_asFile );
    };

    TgFREE_VIRTUAL(psFS_HDD_Mount->m_asFS_File_Table);

    psFS_HDD_Mount->m_tiFS_Mount = KTgKN_FS_MOUNT_ID__INVALID;
    psFS_HDD_Mount->m_szMount_Root[0] = 0;
    psFS_HDD_Mount->m_nuiFS_File_Table = 0;
    psFS_HDD_Mount->m_asFS_File_Table = nullptr;

    tgCM_UT_LF__HT_RW__Free( &psFS_HDD_Mount->m_sFS_Path_Table );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_FS_HDD__FQN --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgKN_FS_HDD__FQN( TgCHAR_U8_PC mbzFull_Path, TgRSIZE_C nuiFullPath, STg2_KN_File_Job_PC psJob, STg2_KN_FS_HDD__Mount_PC psFS_HDD_Mount, TgBOOL_C bCreate )
{
    TgUN_SCALAR                         uFile_Table;
    TgUN_SCALAR                         uFile_Name;

    TgPARAM_CHECK( nullptr != mbzFull_Path );
    TgPARAM_CHECK( nuiFullPath > 0 );
    TgPARAM_CHECK( nullptr != psJob );
    TgPARAM_CHECK( nullptr != psFS_HDD_Mount );

    mbzFull_Path[0] = 0;

    if ((ETgFILE_COMMAND__OPEN == psJob->m_enCmd) && (bCreate))
    {
        TgSTRING_DICT_ID                    tiFileName;
        TgUINT_MAX                          uiHash;

        tgCM_Path_Copy( mbzFull_Path, nuiFullPath, psFS_HDD_Mount->m_szMount_Root, sizeof(psFS_HDD_Mount->m_szMount_Root) );
        tgCM_Path_Append( mbzFull_Path, nuiFullPath, psJob->m_sCmd.m_sOpen.m_pszFile_Name, KTgMAX_RSIZE );
        tiFileName = tgSM_Dict_Insert_String( psJob->m_sCmd.m_sOpen.m_pszFile_Name, tgUSZ_Length_U08( psJob->m_sCmd.m_sOpen.m_pszFile_Name, KTgMAX_RSIZE ) );
        TgERROR(KTgID__INVALID_VALUE != tiFileName.m_uiKI);
        TgVERIFY(TgSUCCEEDED(tgUSZ_Hash( &uiHash, psJob->m_sCmd.m_sOpen.m_pszFile_Name, KTgMAX_RSIZE )));

        TgVERIFY(TgSUCCEEDED(tgCM_UT_LF__HT_RW__Find_Spin( &uFile_Table.m_uiPTR, &psFS_HDD_Mount->m_sFS_Path_Table, psJob->m_sCmd.m_sOpen.m_uiPath )));
        TgERROR( uFile_Table.m_uiPTR < psFS_HDD_Mount->m_nuiFS_File_Table );

        uFile_Name.m_uiPTR = tiFileName.m_uiKI;
        TgVERIFY(TgSUCCEEDED(tgCM_UT_LF__HT_RW__Insert_Spin( &psFS_HDD_Mount->m_asFS_File_Table[uFile_Table.m_uiPTR].m_asFile, uiHash, &uFile_Name.m_uiPTR )));
    }
    else
    {
        TgRESULT                            iResult;
        TgSTRING_DICT_ID                    tiFileName;
        TgCHAR_U8_CP                        mbzPath;
        TgCHAR_U8_CP                        mbzFile;

        TgCOMPILER_ASSERT( sizeof( tiFileName.m_uiKI ) == sizeof( TgUINT_PTR ), 1 );

        uFile_Table.m_uiPTR = 0;
        iResult = tgCM_UT_LF__HT_RW__Find_Spin( &uFile_Table.m_uiPTR, &psFS_HDD_Mount->m_sFS_Path_Table, psJob->m_sCmd.m_sOpen.m_uiPath );
        TgVERIFY(TgSUCCEEDED(iResult));
        if (TgFAILED(iResult))
        {
            return;
        }
        TgERROR( uFile_Table.m_uiPTR < psFS_HDD_Mount->m_nuiFS_File_Table );

        uFile_Name.m_uiPTR = 0;
        iResult = tgCM_UT_LF__HT_RW__Find_Spin( &uFile_Name.m_uiPTR, &psFS_HDD_Mount->m_asFS_File_Table[uFile_Table.m_uiPTR].m_asFile, psJob->m_sCmd.m_sOpen.m_uiFile );
        TgVERIFY(TgSUCCEEDED(iResult));
        if (TgFAILED(iResult))
        {
            return;
        }
        tiFileName.m_uiKI = uFile_Name.m_uiPTR;

        mbzPath = nullptr;
        tgSM_Dict_Query_String( &mbzPath, nullptr, psFS_HDD_Mount->m_asFS_File_Table[uFile_Table.m_uiPTR].m_tiPathName );
        mbzFile = nullptr;
        tgSM_Dict_Query_String( &mbzFile, nullptr, tiFileName );

        tgCM_Path_Copy( mbzFull_Path, nuiFullPath, psFS_HDD_Mount->m_szMount_Root, sizeof(psFS_HDD_Mount->m_szMount_Root) );
        tgCM_Path_Append( mbzFull_Path, nuiFullPath, mbzPath, KTgMAX_RSIZE );
        tgCM_Path_Append( mbzFull_Path, nuiFullPath, mbzFile, KTgMAX_RSIZE );
    };
}


/* ---- tgKN_FS_HDD__Mount__Init_Table_Entry ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgKN_FS_HDD__Mount__Init_Table_Entry( TgKN_FS_MOUNT_ID_C tiFS_Mount, TgCHAR_U8_CP mbzRelPath )
{
    STg2_Find_File                      sFind_File;
    STg2_KN_FS_HDD__Mount_P             psFS_HDD_Mount;
    TgUINT_MAX                          uiHash;
    STg2_KN_FS_HDD__Mount_File_Table_P  psTable;
    TgSTRING_DICT_ID                    tiFileName;
    TgUN_SCALAR                         uInsert;

#if TgCOMPILE_ASSERT && TgCOMPILE_ASSERT__ERROR
    {
        STg2_KN_FS_Mount_P                  psFS_Mount;

        psFS_Mount = g_asKN_FS_Mount + tiFS_Mount.m_uiI;
        TgERROR( tgKN_FS_MOUNT_ID_Is_Equal( &psFS_Mount->m_tiFS_Mount_Singleton, tiFS_Mount ) );
    }
/*# TgCOMPILE_ASSERT && TgCOMPILE_ASSERT__PARAM_CHECK */
#endif

    psFS_HDD_Mount = s_asKN_FS_HDD__Mount + tiFS_Mount.m_uiI;

    tgCM_Path_Copy( sFind_File.m_szFind, TgARRAY_COUNT( sFind_File.m_szFind ), psFS_HDD_Mount->m_szMount_Root, sizeof(psFS_HDD_Mount->m_szMount_Root) );
    tgCM_Path_Append( sFind_File.m_szFind, TgARRAY_COUNT( sFind_File.m_szFind ), mbzRelPath, KTgMAX_RSIZE );
    tgCM_Path_Append( sFind_File.m_szFind, TgARRAY_COUNT( sFind_File.m_szFind ), u8"\\*", 3 );
    tgCN_PrintF( KTgCN_CHANEL_INITIALIZE | KTgCN_SEVERITY_A, STD_MSG_PREFIX u8"Mount: %32.32s\n", STD_MSG_POST, sFind_File.m_szFind );

    /* Add the path to the path table to reference the needed file table */
    TgVERIFY(TgSUCCEEDED(tgUSZ_Hash( &uiHash, mbzRelPath, KTgMAX_RSIZE )));
    uInsert.m_uiPTR = psFS_HDD_Mount->m_nuiFS_File_Table;
    TgVERIFY(TgSUCCEEDED(tgCM_UT_LF__HT_RW__Insert_Spin( &psFS_HDD_Mount->m_sFS_Path_Table, uiHash, &uInsert.m_uiPTR )));

    /* Commit the memory necessary for a new table */
    psTable = psFS_HDD_Mount->m_asFS_File_Table + psFS_HDD_Mount->m_nuiFS_File_Table;
    ++psFS_HDD_Mount->m_nuiFS_File_Table;
    psFS_HDD_Mount->m_asFS_File_Table = (STg2_KN_FS_HDD__Mount_File_Table_P)TgCOMMIT_VIRTUAL( psFS_HDD_Mount->m_asFS_File_Table, 0,
                                                                                              psFS_HDD_Mount->m_nuiFS_File_Table * sizeof( STg2_KN_FS_HDD__Mount_File_Table ));

    /* Add the path name and the file names to the file table */
    psTable->m_tiPathName = tgSM_Dict_Insert_String( mbzRelPath, tgUSZ_Length_U08( mbzRelPath, KTgMAX_RSIZE ) );
    TgVERIFY(TgSUCCEEDED(tgCM_UT_LF__HT_RW__Init_Virtual( &psTable->m_asFile, sizeof(TgUINT_E64), 1, KTgKN_MAX_FILE_PER_FOLDER )));

    if (TgFAILED(tgIO_File_Find_First( &sFind_File )))
    {
        return;
    };

    do
    {
        tgCN_PrintF( KTgCN_CHANEL_INITIALIZE | KTgCN_SEVERITY_A, STD_MSG_PREFIX u8"Found File: %32.32s\n", STD_MSG_POST, sFind_File.m_szResult );

        TgVERIFY(TgSUCCEEDED(tgUSZ_Hash( &uiHash, sFind_File.m_szResult, sizeof(sFind_File.m_szResult) )));
        tiFileName = tgSM_Dict_Insert_String( sFind_File.m_szResult, tgUSZ_Length_U08( sFind_File.m_szResult, sizeof(sFind_File.m_szResult) ) );
        TgVERIFY(KTgSTRING_DICT_ID__INVALID.m_uiKI != tiFileName.m_uiKI);
        TgVERIFY(TgSUCCEEDED(tgCM_UT_LF__HT_RW__Insert_Spin( &psTable->m_asFile, uiHash, &tiFileName.m_uiKI )));
    }
    while (TgSUCCEEDED(tgIO_File_Find_Next( &sFind_File )));

    tgIO_File_Find_Close( &sFind_File );
}
