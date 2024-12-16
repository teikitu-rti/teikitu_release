/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Kernel - File Job.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

static TgBOOL
tgKN_FS_Mount__Is_Valid(
    TgKN_FS_MOUNT_ID_C );

TgFORCEINLINE TgBOOL
tgKN_FS_Open_Command_Test(
    STg2_KN_File_Open_Command_CPCU );

static TgBOOL
tgKN_FS_Command_Test(
    TgKN_FILE_ID_C, ETgFILE_COMMAND_C );


TgFORCEINLINE STg2_KN_File_Job_P
tgKN_FS_Mount_Get_Job_Command( TgVOID );

static TgKN_FILE_ID
tgKN_FS_JB_Open_Internal(
    STg2_KN_File_Open_Command_CPCU, TgBOOL_C );

static TgKN_FILE_JOB_ID
tgKN_FS_JB_Read_Internal(
    STg2_KN_File_Read_Command_CPCU, TgBOOL_C );

static TgKN_FILE_JOB_ID
tgKN_FS_JB_Cache_Internal(
    STg2_KN_File_Cache_Command_CPCU, TgBOOL_C );

static TgKN_FILE_JOB_ID
tgKN_FS_JB_Write_Internal(
    STg2_KN_File_Write_Command_CPCU, TgBOOL_C );

static TgKN_FILE_JOB_ID
tgKN_FS_JB_Flush_Internal(
    TgKN_FILE_ID_C, TgBOOL_C );

static TgKN_FILE_JOB_ID
tgKN_FS_JB_Close_Internal(
    TgKN_FILE_ID_C, TgBOOL_C );


static TgVOID
tgKN_FS_BL_Read_Callback(
    STg2_KN_File_Read_Command_PCU );

static TgVOID
tgKN_FS_BL_Write_Callback(
    STg2_KN_File_Write_Command_PCU );


static TgVOID
tgKN_FS_Job_Queue(
    STg2_KN_File_Job_PCU, TgBOOL_C );


static TgVOID
tgKN_FS_Job_Complete_Final(
    STg2_KN_File_System_PC, STg2_KN_File_Job_P );

static TgVOID
tgKN_FS_Job_Execute(
    STg2_KN_File_System_PC );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Functions                                                                                                                                                               */
/*                                                                                                                                                                                 */
/* There is a single global pool of file jobs, that each function will pop from to create a command.  Once we have validated the file, file mount, and file system the command will
   be added to the file system queue.  We want to allow for multiple read | write commands to be in flight, but also maintain order of commands. This allows the user to submit (for
   example) a series of writes, and a flush, but be guaranteed the flush would occur after the completion of all the write commands.  (Ditto for a cache command followed by reads.)
   This is done by opportunistic concurrency.  On every command insertion, and command completion we will attempt to lock the file system queue for processing.  On a fail, the lock
   increments an attempt counter (atomically with the attempt to acquire the lock). Then on a signal (lock release), if there have been any lock attempts, the lock is not released,
   and the attempt count is returned to the caller.  This allows us to avoid a race condition that happens when we are processing the file system queue, and a command is added to
   one of the auxiliary processing queues (add queue).                                            */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_FS_BL_Open ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgKN_FILE_ID tgKN_FS_BL_Open( STg2_KN_File_Open_Command_CPCU psCmd )
{
    TgKN_FILE_ID                        tiFile;

    tiFile = tgKN_FS_JB_Open_Internal( psCmd, true );
    return (tiFile);
}


/* ---- tgKN_FS_BL_Read ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_FS_BL_Read( STg2_KN_File_Read_Command_PCU psCmd )
{
    TgKN_FILE_JOB_ID                    tiFile_Job;
    TgKN_FILE_READ_CALLBACK             pfnRead_Callback;
    TgUINT_PTR                          uiParam;

    pfnRead_Callback = psCmd->m_pfnFinish;
    uiParam = psCmd->m_uiParam;
    psCmd->m_pfnFinish = tgKN_FS_BL_Read_Callback;
    psCmd->m_uiParam = (TgUINT_PTR)psCmd;

    tiFile_Job = tgKN_FS_JB_Read_Internal( psCmd, true );

    psCmd->m_pfnFinish = pfnRead_Callback;
    psCmd->m_uiParam = uiParam;

    if (nullptr != pfnRead_Callback)
    {
        pfnRead_Callback( psCmd );
    };

    return (KTgID__INVALID_VALUE != tiFile_Job.m_uiKI ? KTgS_OK : KTgE_FAIL);
}


/* ---- tgKN_FS_BL_Cache --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_FS_BL_Cache( STg2_KN_File_Cache_Command_CPCU psCmd )
{
    TgKN_FILE_JOB_ID                    tiFile_Job;

    tiFile_Job = tgKN_FS_JB_Cache_Internal( psCmd, true );
    return (KTgID__INVALID_VALUE != tiFile_Job.m_uiKI ? KTgS_OK : KTgE_FAIL);
}


/* ---- tgKN_FS_BL_Write --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_FS_BL_Write( STg2_KN_File_Write_Command_PCU psCmd )
{
    TgKN_FILE_JOB_ID                    tiFile_Job;
    TgKN_FILE_WRITE_CALLBACK            pfnWrite_Callback;
    TgUINT_PTR                          uiParam;

    pfnWrite_Callback = psCmd->m_pfnFinish;
    uiParam = psCmd->m_uiParam;
    psCmd->m_pfnFinish = tgKN_FS_BL_Write_Callback;
    psCmd->m_uiParam = (TgUINT_PTR)psCmd;

    tiFile_Job = tgKN_FS_JB_Write_Internal( psCmd, true );

    psCmd->m_pfnFinish = pfnWrite_Callback;
    psCmd->m_uiParam = uiParam;

    if (nullptr != pfnWrite_Callback)
    {
        pfnWrite_Callback( psCmd );
    };

    return (KTgID__INVALID_VALUE != tiFile_Job.m_uiKI ? KTgS_OK : KTgE_FAIL);
}


/* ---- tgKN_FS_BL_Flush --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_FS_BL_Flush( TgKN_FILE_ID_C tiFile )
{
    TgKN_FILE_JOB_ID                    tiFile_Job;

    tiFile_Job = tgKN_FS_JB_Flush_Internal( tiFile, true );
    return (KTgID__INVALID_VALUE != tiFile_Job.m_uiKI ? KTgS_OK : KTgE_FAIL);
}


/* ---- tgKN_FS_BL_Close --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_FS_BL_Close( TgKN_FILE_ID_C tiFile )
{
    TgKN_FILE_JOB_ID                    tiFile_Job;

    tiFile_Job = tgKN_FS_JB_Close_Internal( tiFile, true );
    return (KTgID__INVALID_VALUE != tiFile_Job.m_uiKI ? KTgS_OK : KTgE_FAIL);
}


/* ---- tgKN_FS_JB_Read ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgKN_FILE_JOB_ID tgKN_FS_JB_Read( STg2_KN_File_Read_Command_CPCU psCmd )
{
    return (tgKN_FS_JB_Read_Internal( psCmd, false ));
}


/* ---- tgKN_FS_JB_Cache --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgKN_FILE_JOB_ID tgKN_FS_JB_Cache( STg2_KN_File_Cache_Command_CPCU psCmd )
{
    return (tgKN_FS_JB_Cache_Internal( psCmd, false ));
}


/* ---- tgKN_FS_JB_Write --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgKN_FILE_JOB_ID tgKN_FS_JB_Write( STg2_KN_File_Write_Command_CPCU psCmd )
{
    return (tgKN_FS_JB_Write_Internal( psCmd, false ));
}


/* ---- tgKN_FS_JB_Flush --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgKN_FILE_JOB_ID tgKN_FS_JB_Flush( TgKN_FILE_ID_C tiFile )
{
    return (tgKN_FS_JB_Flush_Internal( tiFile, false ));
}


/* ---- tgKN_FS_JB_Close --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgKN_FILE_JOB_ID tgKN_FS_JB_Close( TgKN_FILE_ID_C tiFile )
{
    return (tgKN_FS_JB_Close_Internal( tiFile, false ));
}


/* ---- tgKN_FS_JB_Cancel -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_FS_JB_Cancel( TgKN_FILE_JOB_ID_C tiFile_Job )
{
    STg2_KN_File_Info_P                 psFile_Info;
    STg2_KN_File_System_P               psFS;
    STg2_KN_File_Job_P                  psJob;

    if (!tgKN_FILE_JOB_ID_Is_Equal( &g_asKN_File_Job[tiFile_Job.m_uiI].m_tiFile_Job_Singleton, tiFile_Job ))
    {
        return;
    };

    if (!tgKN_FS_Command_Test( g_asKN_File_Job[tiFile_Job.m_uiI].m_tiFile, ETgFILE_COMMAND__UNKNOWN ))
    {
        return;
    };

    psFile_Info = g_asKN_File_Info + g_asKN_File_Job[tiFile_Job.m_uiI].m_tiFile.m_uiI;
    psFS = g_asKN_FS + psFile_Info->m_tiFS.m_uiI;
    TgERROR( tgKN_FILE_SYSTEM_ID_Is_Equal( &psFS->m_tiFS_Singleton, psFile_Info->m_tiFS ) );

    psJob = tgKN_FS_Mount_Get_Job_Command();

    psJob->m_sCmd.m_sCancel.m_tiFile_Job = tiFile_Job;
    psJob->m_enCmd = ETgFILE_COMMAND__CANCEL;

    tgCM_UT_LF__ST__Push( &psFS->m_sComplete_Job.m_sStack, (STg2_UT_ST__ST_Node_P)psJob );
}


/* ---- tgKN_FS_JB_Status -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
ETgKN_IO_STATUS tgKN_FS_JB_Status( TgKN_FILE_JOB_ID_C tiFile_Job )
{
    if (!tgKN_FILE_JOB_ID_Is_Equal( &g_asKN_File_Job[tiFile_Job.m_uiI].m_tiFile_Job_Singleton, tiFile_Job ))
    {
        return (ETgKN_IO_STATUS__INVALID);
    };

    if (!tgKN_FS_Command_Test( g_asKN_File_Job[tiFile_Job.m_uiI].m_tiFile, ETgFILE_COMMAND__UNKNOWN ))
    {
        return (ETgKN_IO_STATUS__INVALID);
    };

    return ((ETgKN_IO_STATUS)atomic_load( &g_asKN_File_Job[tiFile_Job.m_uiI].m_xuiStatus ));
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_File__Info_Init ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgKN_FILE_ID tgKN_File__Info_Init( STg2_KN_File_Open_Command_CPCU psCmd )
{
    union
    {
        STg2_UT_ST__ST_Node_P               psNode;
        STg2_KN_File_Info_P                 ps;
    }                                   sFile_Info;

    sFile_Info.psNode = tgCM_UT_LF__ST__Pop( &g_sKN_File_Info__Free_Stack.m_sStack );
    if (nullptr == sFile_Info.psNode)
    {
        TgWARNING_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Too many files open." );
        return (KTgKN_FILE_ID__INVALID);
    };

    sFile_Info.ps->m_tiFS = g_asKN_FS_Mount[psCmd->m_tiFS_Mount.m_uiI].m_tiFS;
    sFile_Info.ps->m_tiFS_Mount = psCmd->m_tiFS_Mount;
    TgERROR(tgKN_FS_MOUNT_ID_Is_Equal( &g_asKN_FS_Mount[psCmd->m_tiFS_Mount.m_uiI].m_tiFS_Mount_Singleton, psCmd->m_tiFS_Mount ));
    sFile_Info.ps->m_uiPath = psCmd->m_uiPath;
    sFile_Info.ps->m_uiFile = psCmd->m_uiFile;
    sFile_Info.ps->m_uiSize = KTgMAX_RSIZE;
    sFile_Info.ps->m_uiPos = 0;
    sFile_Info.ps->m_uiCache_Pos = 0;
    sFile_Info.ps->m_uiCache_Size = 0;
    sFile_Info.ps->m_puiCache = nullptr;
    sFile_Info.ps->m_enMode = psCmd->m_enMode;
    sFile_Info.ps->m_niCmd = 0;
    sFile_Info.ps->m_niExecute = 0;

    tgKN_FILE_ID_Init( &sFile_Info.ps->m_tiFile_Singleton, (TgUINT_F32)(sFile_Info.ps - g_asKN_File_Info) );

    return (tgKN_FILE_ID_Query_Unsafe( &sFile_Info.ps->m_tiFile_Singleton ));
}


/* ---- tgKN_File__Info_Free ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_File__Info_Free( TgKN_FILE_ID_C tiFile )
{
    TgERROR(tgKN_FILE_ID_Is_Equal( &g_asKN_File_Info[tiFile.m_uiI].m_tiFile_Singleton, tiFile ));

    if (nullptr != g_asKN_File_Info[tiFile.m_uiI].m_puiCache)
    {
        TgFREE_POOL( g_asKN_File_Info[tiFile.m_uiI].m_puiCache );
        g_asKN_File_Info[tiFile.m_uiI].m_puiCache = nullptr;
    };

    g_asKN_File_Info[tiFile.m_uiI].m_tiFS = KTgKN_FILE_SYSTEM_ID__INVALID;
    g_asKN_File_Info[tiFile.m_uiI].m_tiFS_Mount = KTgKN_FS_MOUNT_ID__INVALID;
    tgKN_FILE_ID_Invalidate( &g_asKN_File_Info[tiFile.m_uiI].m_tiFile_Singleton );;
    tgCM_UT_LF__ST__Push( &g_sKN_File_Info__Free_Stack.m_sStack, (STg2_UT_ST__ST_Node_P)(g_asKN_File_Info + tiFile.m_uiI) );
}


/* ---- tgKN_FS_Job_Complete ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_FS_Job_Complete( STg2_KN_File_Job_PCU psJob )
{
    STg2_KN_File_Info_P                 psFile_Info;
    STg2_KN_File_System_P               psFS;

    TgPARAM_CHECK( nullptr != psJob );
    TgPARAM_CHECK_INDEX( psJob->m_tiFile.m_uiI, g_asKN_File_Info );

    psFile_Info = g_asKN_File_Info + psJob->m_tiFile.m_uiI;
    TgERROR( tgKN_FILE_ID_Is_Equal( &psFile_Info->m_tiFile_Singleton, psJob->m_tiFile ) );
    psFS = g_asKN_FS + psFile_Info->m_tiFS.m_uiI;
    TgERROR( tgKN_FILE_SYSTEM_ID_Is_Equal( &psFS->m_tiFS_Singleton, psFile_Info->m_tiFS ) );

    /* Execute the user completion call back function */
    if (ETgFILE_COMMAND__WRITE_ASYNC == psJob->m_enCmd  && psJob->m_sCmd.m_sWrite.m_pfnFinish)
    {
        psJob->m_sCmd.m_sWrite.m_pfnFinish( &psJob->m_sCmd.m_sWrite );
    }
    else if (ETgFILE_COMMAND__READ_ASYNC == psJob->m_enCmd && psJob->m_sCmd.m_sRead.m_pfnFinish)
    {
        psJob->m_sCmd.m_sRead.m_pfnFinish( &psJob->m_sCmd.m_sRead );
    };

    if (TgSUCCEEDED(tgCM_UT_LF__SN_CNT__Lock_Or_Increment_Count( &psFS->m_sProcess_Lock.m_sLock )))
    {
        tgKN_FS_Job_Complete_Final( psFS, psJob );
        tgKN_FS_Job_Execute( psFS ); /* Execute the next set of jobs */
    }
    else
    {
        tgCM_UT_LF__ST__Push( &psFS->m_sComplete_Job.m_sStack, (STg2_UT_ST__ST_Node_P)psJob );
    };
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_FS_Mount__Is_Valid -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* Validates the FS Mount ID, and make sure that the mount access mode support the requested file access                                                                  */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgBOOL tgKN_FS_Mount__Is_Valid( TgKN_FS_MOUNT_ID_C tiFS_Mount )
{
    /* Make sure that the chosen mount id is valid */
    TgERROR_MSGF( tiFS_Mount.m_uiI < KTgKN_MAX_FILE_SYSTEM_MOUNT, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Invalid Mount Point ID." );

    /* Make sure that the supporting file system id is valid */
    TgERROR_INDEX( tiFS_Mount.m_uiI, g_asKN_FS_Mount );
    TgERROR_MSGF( g_asKN_FS_Mount[tiFS_Mount.m_uiI].m_tiFS.m_uiI < KTgKN_MAX_FILE_SYSTEM, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Invalid File System ID." );

    /* Make sure that the supporting file system is valid */
    TgERROR_INDEX( g_asKN_FS_Mount[tiFS_Mount.m_uiI].m_tiFS.m_uiI, g_asKN_FS );
    TgERROR_MSGF( tgKN_FILE_SYSTEM_ID_Is_Equal( &g_asKN_FS[g_asKN_FS_Mount[tiFS_Mount.m_uiI].m_tiFS.m_uiI].m_tiFS_Singleton, g_asKN_FS_Mount[tiFS_Mount.m_uiI].m_tiFS ),
                  STD_MSG_LITERAL_1, STD_MSG_POST, u8"Invalid File System in Command." );

    /* Make sure that the chosen mount point is valid */
    if (!tgKN_FS_MOUNT_ID_Is_Equal( &g_asKN_FS_Mount[tiFS_Mount.m_uiI].m_tiFS_Mount_Singleton, tiFS_Mount ))
    {
        TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Invalid File System Mount in Command." );
        return (false);
    };

    return (true);
}


/* ---- tgKN_FS_Open_Command_Test ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* Validates the FS Mount ID, and make sure that the mount access mode support the requested file access                                                                  */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgFORCEINLINE TgBOOL tgKN_FS_Open_Command_Test( STg2_KN_File_Open_Command_CPCU psCmd )
{
    /* Make sure that the chosen mount point is valid */
    if (!tgKN_FS_Mount__Is_Valid( tgKN_FS_MOUNT_ID_Query_Unsafe( &g_asKN_FS_Mount[psCmd->m_tiFS_Mount.m_uiI].m_tiFS_Mount_Singleton ) ))
    {
        return (false);
    };

    /* Validate the request against the permission flags on the file system */
    if ((psCmd->m_enMode & ETgFILE_IO_ACCESS__ACCESS_MASK) != (psCmd->m_enMode & g_asKN_FS_Mount[psCmd->m_tiFS_Mount.m_uiI].m_enMode))
    {
        TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Invalid File Access Mode request for Mount Point." );
        return (false);
    };

    if (ETgFILE_IO_ACCESS__CREATE == (psCmd->m_enMode & ETgFILE_IO_ACCESS__CREATE))
    {
        if (nullptr == psCmd->m_pszFile_Name)
        {
            TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"No file name provided for open command with create." );
            return (false);
        };
    }
    else
    {
        if (nullptr != psCmd->m_pszFile_Name)
        {
            TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"File name provided for open command without create." );
            return (false);
        };

        if (KTgEMPTY_HASH == psCmd->m_uiFile)
        {
            TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"No hash provided for open command." );
            return (false);
        };
    };

    return (true);
}


/* ---- tgKN_FS_Command_Test ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* Note: this is not thread safe, in that the file could be closed during execution of this function (or other commands) - caveat emptor                                  */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgBOOL tgKN_FS_Command_Test( TgKN_FILE_ID_C tiFile, ETgFILE_COMMAND_C enFile_Operation )
{
    /* Make sure that the chosen mount id is KTgKN_MAX_FILE_OPEN */
    TgERROR_MSGF( tiFile.m_uiI < KTgKN_MAX_FILE_OPEN, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Invalid File ID." );

    /* Make sure that the chosen mount point is valid */
    TgERROR_INDEX( tiFile.m_uiI, g_asKN_File_Info );
    if (!tgKN_FILE_ID_Is_Equal( &g_asKN_File_Info[tiFile.m_uiI].m_tiFile_Singleton, tiFile ))
    {
        TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Invalid File in Command." );
        return (false);
    };

    /* Make sure that the chosen mount point is valid */
    if (!tgKN_FS_Mount__Is_Valid( g_asKN_File_Info[tiFile.m_uiI].m_tiFS_Mount ))
    {
        return (false);
    };

    /* See if the file has a job request to be closed */
    if ((ETgFILE_COMMAND__CLOSE != enFile_Operation) && (ETgFILE_IO_ACCESS__CLOSING == (ETgFILE_IO_ACCESS__CLOSING & g_asKN_File_Info[tiFile.m_uiI].m_enMode)))
    {
        return (false);
    };

    switch (enFile_Operation)
    {
        case ETgFILE_COMMAND__READ_ASYNC:
            if (ETgFILE_IO_ACCESS__READ != (ETgFILE_IO_ACCESS__READ & g_asKN_File_Info[tiFile.m_uiI].m_enMode))
            {
                TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Invalid Request to Non-Read File." );
                return (false);
            };
            break;

        case ETgFILE_COMMAND__FLUSH:
        SWITCH_FALLTHROUGH case ETgFILE_COMMAND__WRITE_ASYNC:
            if (ETgFILE_IO_ACCESS__WRITE != (ETgFILE_IO_ACCESS__WRITE & g_asKN_File_Info[tiFile.m_uiI].m_enMode))
            {
                TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Invalid Request to Non-Write File." );
                return (false);
            };
            break;

        case ETgFILE_COMMAND__UNKNOWN:
        SWITCH_FALLTHROUGH case ETgFILE_COMMAND__OPEN:
        SWITCH_FALLTHROUGH case ETgFILE_COMMAND__CACHE:
        SWITCH_FALLTHROUGH case ETgFILE_COMMAND__CLOSE:
            break;

        case ETgFILE_COMMAND__CANCEL:
        SWITCH_FALLTHROUGH default:
            TgS_NO_DEFAULT(break);
    };

    return (true);
}


/* ---- tgKN_FS_Mount_Get_Job_Command -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgFORCEINLINE STg2_KN_File_Job_P tgKN_FS_Mount_Get_Job_Command( TgVOID )
{
    union
    {
        STg2_UT_ST__ST_Node_P               psNode;
        STg2_KN_File_Job_P                  ps;
    }                                   sJob;

    sJob.psNode = tgCM_UT_LF__ST__Pop( &g_sKN_File_Job__Free_Stack.m_sStack );
    if (nullptr == sJob.psNode)
    {
        TgWARNING_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Too many file requests." );
        sJob.psNode = tgCM_UT_LF__ST__Pop_Wait_Yield( &g_sKN_File_Job__Free_Stack.m_sStack );
    };

    tgKN_FILE_JOB_ID_Init( &sJob.ps->m_tiFile_Job_Singleton, (TgUINT_F32)(sJob.ps - g_asKN_File_Job) );
    sJob.ps->m_sFS_Node.m_pNext_Node = nullptr;
    sJob.ps->m_enCmd = ETgFILE_COMMAND__UNKNOWN;
    sJob.ps->m_tiFile = KTgKN_FILE_ID__INVALID;
    sJob.ps->m_pmxBL = nullptr;
    atomic_store( &sJob.ps->m_xuiStatus, ETgKN_IO_STATUS__INVALID );

    return (sJob.ps);
}


/* ---- tgKN_FS_JB_Open_Internal ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* NOTE: There is no Job version of this command - because I do not like the idea of allowing the user to queue a bunch of commands on a file that fails to open.  This   */
/* function exists for consistency - but is only ever called in as a blocking call (note the error check on it).                                                          */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgKN_FILE_ID tgKN_FS_JB_Open_Internal( STg2_KN_File_Open_Command_CPCU psCmd, TgBOOL_C bBlocking )
{
    STg2_KN_File_Job_P                  psJob;
    TgKN_FILE_ID                        tiFile;

    TgPARAM_CHECK( nullptr != psCmd );
    TgPARAM_CHECK( bBlocking );

    /* Validate the file parameters from the command */
    if (!tgKN_FS_Open_Command_Test( psCmd ))
    {
        return (KTgKN_FILE_ID__INVALID);
    };

    /* Attempt to acquire a kernel file data structure for the request */
    tiFile = tgKN_File__Info_Init( psCmd );

    if (KTgID__INVALID_VALUE == tiFile.m_uiKI)
    {
        return (KTgKN_FILE_ID__INVALID);
    };

    psJob = tgKN_FS_Mount_Get_Job_Command();

    psJob->m_sCmd.m_sOpen = *psCmd;
    psJob->m_enCmd = ETgFILE_COMMAND__OPEN;
    psJob->m_tiFile = tiFile;

    tgKN_FS_Job_Queue( psJob, bBlocking );

    if (!tgKN_FILE_ID_Is_Equal( &g_asKN_File_Info[tiFile.m_uiI].m_tiFile_Singleton, tiFile ) || ETgKN_IO_STATUS__INVALID == atomic_load( &psJob->m_xuiStatus) )
    {
        tgKN_File__Info_Free( tiFile );
        tiFile = KTgKN_FILE_ID__INVALID;
    };

    return (tiFile);
}


/* ---- tgKN_FS_JB_Read_Internal ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgKN_FILE_JOB_ID tgKN_FS_JB_Read_Internal( STg2_KN_File_Read_Command_CPCU psCmd, TgBOOL_C bBlocking )
{
    STg2_KN_File_Job_P                  psJob;
    TgKN_FILE_JOB_ID                    tiFile_Job;

    TgPARAM_CHECK( nullptr != psCmd );

    if (!tgKN_FS_Command_Test( psCmd->m_tiFile, ETgFILE_COMMAND__READ_ASYNC ))
    {
        return (KTgKN_FILE_JOB_ID__INVALID);
    };

    psJob = tgKN_FS_Mount_Get_Job_Command();

    psJob->m_sCmd.m_sRead = *psCmd;
    psJob->m_tiFile = psCmd->m_tiFile;
    psJob->m_enCmd = ETgFILE_COMMAND__READ_ASYNC;

    tiFile_Job = tgKN_FILE_JOB_ID_Query_Unsafe( &psJob->m_tiFile_Job_Singleton );
    tgKN_FS_Job_Queue( psJob, bBlocking );

    return (tiFile_Job);
}


/* ---- tgKN_FS_JB_Cache_Internal ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgKN_FILE_JOB_ID tgKN_FS_JB_Cache_Internal( STg2_KN_File_Cache_Command_CPCU psCmd, TgBOOL_C bBlocking )
{
    STg2_KN_File_Job_P                  psJob;
    TgKN_FILE_JOB_ID                    tiFile_Job;

    TgPARAM_CHECK( nullptr != psCmd );

    if (!tgKN_FS_Command_Test( psCmd->m_tiFile, ETgFILE_COMMAND__CACHE ))
    {
        return (KTgKN_FILE_JOB_ID__INVALID);
    };

    psJob = tgKN_FS_Mount_Get_Job_Command();

    psJob->m_sCmd.m_sCache = *psCmd;
    psJob->m_tiFile = psCmd->m_tiFile;
    psJob->m_enCmd = ETgFILE_COMMAND__CACHE;

    tiFile_Job = tgKN_FILE_JOB_ID_Query_Unsafe( &psJob->m_tiFile_Job_Singleton );
    tgKN_FS_Job_Queue( psJob, bBlocking );

    return (tiFile_Job);
}


/* ---- tgKN_FS_JB_Write_Internal ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgKN_FILE_JOB_ID tgKN_FS_JB_Write_Internal( STg2_KN_File_Write_Command_CPCU psCmd, TgBOOL_C bBlocking )
{
    STg2_KN_File_Job_P                  psJob;
    TgKN_FILE_JOB_ID                    tiFile_Job;

    TgPARAM_CHECK( nullptr != psCmd );

    if (!tgKN_FS_Command_Test( psCmd->m_tiFile, ETgFILE_COMMAND__WRITE_ASYNC ))
    {
        return (KTgKN_FILE_JOB_ID__INVALID);
    };

    psJob = tgKN_FS_Mount_Get_Job_Command();

    psJob->m_sCmd.m_sWrite = *psCmd;
    psJob->m_tiFile = psCmd->m_tiFile;
    psJob->m_enCmd = ETgFILE_COMMAND__WRITE_ASYNC;

    tiFile_Job = tgKN_FILE_JOB_ID_Query_Unsafe( &psJob->m_tiFile_Job_Singleton );
    tgKN_FS_Job_Queue( psJob, bBlocking );

    return (tiFile_Job);
}


/* ---- tgKN_FS_JB_Flush_Internal ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgKN_FILE_JOB_ID tgKN_FS_JB_Flush_Internal( TgKN_FILE_ID_C tiFile, TgBOOL_C bBlocking )
{
    STg2_KN_File_Job_P                  psJob;
    TgKN_FILE_JOB_ID                    tiFile_Job;

    TgPARAM_CHECK( KTgID__INVALID_VALUE != tiFile.m_uiKI );

    if (!tgKN_FS_Command_Test( tiFile, ETgFILE_COMMAND__FLUSH ))
    {
        return (KTgKN_FILE_JOB_ID__INVALID);
    };

    psJob = tgKN_FS_Mount_Get_Job_Command();

    psJob->m_enCmd = ETgFILE_COMMAND__FLUSH;
    psJob->m_tiFile = tiFile;

    tiFile_Job = tgKN_FILE_JOB_ID_Query_Unsafe( &psJob->m_tiFile_Job_Singleton );
    tgKN_FS_Job_Queue( psJob, bBlocking );

    return (tiFile_Job);
}


/* ---- tgKN_FS_JB_Close_Internal ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgKN_FILE_JOB_ID tgKN_FS_JB_Close_Internal( TgKN_FILE_ID_C tiFile, TgBOOL_C bBlocking )
{
    STg2_KN_File_Job_P                  psJob;
    TgKN_FILE_JOB_ID                    tiFile_Job;

    TgPARAM_CHECK( KTgID__INVALID_VALUE != tiFile.m_uiKI );

    if (!tgKN_FS_Command_Test( tiFile, ETgFILE_COMMAND__CLOSE ))
    {
        return (KTgKN_FILE_JOB_ID__INVALID);
    };

    psJob = tgKN_FS_Mount_Get_Job_Command();

    psJob->m_enCmd = ETgFILE_COMMAND__CLOSE;
    psJob->m_tiFile = tiFile;

    tiFile_Job = tgKN_FILE_JOB_ID_Query_Unsafe( &psJob->m_tiFile_Job_Singleton );
    tgKN_FS_Job_Queue( psJob, bBlocking );

    return (tiFile_Job);
}


/* ---- tgKN_FS_BL_Read_Callback ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgKN_FS_BL_Read_Callback( STg2_KN_File_Read_Command_PCU psCmd )
{
    STg2_KN_File_Read_Command_P         psBL_Cmd;

    psBL_Cmd = (STg2_KN_File_Read_Command_P)psCmd->m_uiParam;
    psBL_Cmd->m_nuiBuffer = psCmd->m_nuiBuffer;
    psBL_Cmd->m_nuiResult = psCmd->m_nuiResult;
    psBL_Cmd->m_pBuffer = psCmd->m_pBuffer;
}


/* ---- tgKN_FS_BL_Write_Callback ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgKN_FS_BL_Write_Callback( STg2_KN_File_Write_Command_PCU psCmd )
{
    STg2_KN_File_Write_Command_P        psBL_Cmd;

    psBL_Cmd = (STg2_KN_File_Write_Command_P)psCmd->m_uiParam;
    psBL_Cmd->m_nuiResult = psCmd->m_nuiResult;
}


/* ---- tgKN_FS_Job_Queue -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgKN_FS_Job_Queue( STg2_KN_File_Job_PCU psJob, TgBOOL_C bBlocking )
{
    STg2_KN_File_Info_P                 psFile_Info;
    STg2_KN_File_System_P               psFS;
    STg1_MT_MX                          mxWait;

    TgPARAM_CHECK( nullptr != psJob );
    TgPARAM_CHECK_INDEX( psJob->m_tiFile.m_uiI, g_asKN_File_Info );

    psFile_Info = g_asKN_File_Info + psJob->m_tiFile.m_uiI;
    TgERROR( tgKN_FILE_ID_Is_Equal( &psFile_Info->m_tiFile_Singleton, psJob->m_tiFile ) );
    psFS = g_asKN_FS + psFile_Info->m_tiFS.m_uiI;
    TgERROR( tgKN_FILE_SYSTEM_ID_Is_Equal( &psFS->m_tiFS_Singleton, psFile_Info->m_tiFS ) );

    if (bBlocking)
    {
        tgPM_MT_MX_Init( &mxWait, TgOS_TEXT("") );
        psJob->m_pmxBL = &mxWait;
    };

    tgCM_UT_LF__SN__Lock_Spin( &psFS->m_sAdd_Lock.m_sLock );
    atomic_store( &psJob->m_xuiStatus, ETgKN_IO_STATUS__QUEUED );
    tgCM_UT_ST__QU__Enqueue( &psFS->m_sAdd_Queue, &psJob->m_sFS_Node );
    ++psFile_Info->m_niCmd;
    atomic_thread_fence( cxx__memory_order_seq_cst );
    tgCM_UT_LF__SN__Signal( &psFS->m_sAdd_Lock.m_sLock );

    if (TgSUCCEEDED(tgCM_UT_LF__SN_CNT__Lock_Or_Increment_Count( &psFS->m_sProcess_Lock.m_sLock )))
    {
        tgKN_FS_Job_Execute( psFS );
    };

    if (bBlocking)
    {
        tgPM_MT_MX_Wait_Block( &mxWait );
        tgPM_MT_MX_Free( &mxWait );
    };
}


/* ---- tgKN_FS_Job_Complete_Final ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ASSUME: File System Process Lock has been Acquired                                                                                                                              */
/* FUNC: Used to cancel jobs that are queued, decrement the execution count on the file, and file system, and restore the overlapped state for the file                   */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgKN_FS_Job_Complete_Final( STg2_KN_File_System_PC psFS, STg2_KN_File_Job_P psJob )
{
    STg2_KN_File_Info_P                 psFile_Info;

    if (ETgFILE_COMMAND__CANCEL == psJob->m_enCmd)
    {
        do
        {
            TgKN_FILE_JOB_ID                    tiFile_Job;
            TgRSIZE                             uiStatus_Expected;

            tiFile_Job = psJob->m_sCmd.m_sCancel.m_tiFile_Job;

            /* Cancel job request refers to an invalid job - may have completed */
            if (!tgKN_FILE_JOB_ID_Is_Equal( &g_asKN_File_Job[tiFile_Job.m_uiI].m_tiFile_Job_Singleton, tiFile_Job ))
            {
                break;
            };

            /* Only Cancel jobs that are in the queued state */
            uiStatus_Expected = ETgKN_IO_STATUS__QUEUED;
            if (!atomic_compare_exchange_strong( &g_asKN_File_Job[tiFile_Job.m_uiI].m_xuiStatus, &uiStatus_Expected, ETgKN_IO_STATUS__CANCEL ))
            {
                break;
            };

            if (g_asKN_File_Job[tiFile_Job.m_uiI].m_sCmd.m_sCancel.m_pfnFinish)
            {
                g_asKN_File_Job[tiFile_Job.m_uiI].m_sCmd.m_sCancel.m_pfnFinish( &g_asKN_File_Job[tiFile_Job.m_uiI].m_sCmd.m_sCancel );
            };

        } while (0);

        tgCM_UT_LF__ST__Push( &g_sKN_File_Job__Free_Stack.m_sStack, (STg2_UT_ST__ST_Node_P)psJob );
        return;
    };

    psFile_Info = g_asKN_File_Info + psJob->m_tiFile.m_uiI;
    TgERROR( psFS == g_asKN_FS + psFile_Info->m_tiFS.m_uiI );

    /* Decrement the execution counters */
    switch (psJob->m_enCmd)
    {
        case ETgFILE_COMMAND__CACHE:
            --psFile_Info->m_niExecute;
            --psFS->m_niExecute;
        SWITCH_FALLTHROUGH case ETgFILE_COMMAND__OPEN:
        SWITCH_FALLTHROUGH case ETgFILE_COMMAND__FLUSH:
            psFile_Info->m_enMode |= ETgFILE_IO_ACCESS__OVERLAPPED;
            break;

        case ETgFILE_COMMAND__WRITE_ASYNC:
        SWITCH_FALLTHROUGH case ETgFILE_COMMAND__READ_ASYNC:
            --psFile_Info->m_niExecute;
            --psFS->m_niExecute;
            break;

        case ETgFILE_COMMAND__CLOSE:
            break;

        case ETgFILE_COMMAND__CANCEL:
        SWITCH_FALLTHROUGH case ETgFILE_COMMAND__UNKNOWN:
        SWITCH_FALLTHROUGH default:
            TgS_NO_DEFAULT( break );
    };

    TgERROR( psFile_Info->m_niExecute >= 0 );
    TgERROR( psFS->m_niExecute >= 0 );

    if (ETgFILE_COMMAND__CLOSE == psJob->m_enCmd)
    {
        tgKN_File__Info_Free( psJob->m_tiFile );
        psJob->m_tiFile = KTgKN_FILE_ID__INVALID;
    };

    if (nullptr != psJob->m_pmxBL)
    {
        tgPM_MT_MX_Release( psJob->m_pmxBL );
        psJob->m_pmxBL = nullptr;
    };

    tgCM_UT_LF__ST__Push( &g_sKN_File_Job__Free_Stack.m_sStack, (STg2_UT_ST__ST_Node_P)psJob);
}


/* ---- tgKN_FS_Job_Execute ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ASSUME: File System Process Lock has been Acquired                                                                                                                              */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgKN_FS_Job_Execute( STg2_KN_File_System_PC psFS )
{
    do
    {
        union
        {
            STg2_UT_ST__ST_Node_P               psNode;
            STg2_UT_ST__QU_Node_P               psQU_Node;
            STg2_KN_File_Job_P                  ps;
        }                                   sJob;
        STg2_UT_ST__QU                      sQueue;

        while (1)
        {
            sJob.psNode = tgCM_UT_LF__ST__Pop( &psFS->m_sComplete_Job.m_sStack );
            if (nullptr == sJob.psNode)
            {
                break;
            };
            tgKN_FS_Job_Complete_Final( psFS, sJob.ps );
        };

        /* Add the Add Queue to the process Queue */
        tgCM_UT_LF__SN__Lock_Spin( &psFS->m_sAdd_Lock.m_sLock );
        tgCM_UT_ST__QU__Merge( &psFS->m_sProcess_Queue, &psFS->m_sAdd_Queue );
        tgCM_UT_LF__SN__Signal( &psFS->m_sAdd_Lock.m_sLock );

        /* Process all available jobs */
        tgCM_UT_ST__QU__Init( &sQueue );
        do
        {
            STg2_KN_File_Info_P                 psFile_Info;

            sJob.psQU_Node = tgCM_UT_ST__QU__Dequeue( &psFS->m_sProcess_Queue );
            if (nullptr == sJob.psNode)
            {
                break;
            };

            psFile_Info = g_asKN_File_Info + sJob.ps->m_tiFile.m_uiI;

            if (!tgKN_FS_MOUNT_ID_Is_Equal( &g_asKN_FS_Mount[psFile_Info->m_tiFS_Mount.m_uiI].m_tiFS_Mount_Singleton, psFile_Info->m_tiFS_Mount ))
            {
                atomic_store( &sJob.ps->m_xuiStatus, ETgKN_IO_STATUS__INVALID );
                tgKN_FS_Job_Complete_Final( psFS, sJob.ps );
                continue;
            };

            switch (sJob.ps->m_enCmd)
            {
                case ETgFILE_COMMAND__CLOSE:
                case ETgFILE_COMMAND__OPEN:
                case ETgFILE_COMMAND__FLUSH:
                    psFile_Info->m_enMode &= ~ETgFILE_IO_ACCESS__OVERLAPPED;
                    if (0 == psFile_Info->m_niExecute)
                    {
                        TgRSIZE                             uiKN_IO_Status;

                        TgERROR( psFile_Info->m_niCmd >= 1 );
                        --psFile_Info->m_niCmd;
                        uiKN_IO_Status = ETgKN_IO_STATUS__QUEUED;
                        if (atomic_compare_exchange_strong( &sJob.ps->m_xuiStatus, &uiKN_IO_Status, ETgKN_IO_STATUS__EXECUTE ))
                        {
                            psFS->m_pfnExecute_Job( sJob.ps );
                        }
                        else
                        {
                            TgERROR( ETgKN_IO_STATUS__CANCEL == uiKN_IO_Status );
                            tgKN_FS_Job_Complete_Final( psFS, sJob.ps );
                        };
                    }
                    else
                    {
                        tgCM_UT_ST__QU__Enqueue( &sQueue, sJob.psQU_Node );
                    };
                    break;

                case ETgFILE_COMMAND__WRITE_ASYNC:
                case ETgFILE_COMMAND__CACHE:
                case ETgFILE_COMMAND__READ_ASYNC:
                    if (psFS->m_niExecute >= psFS->m_niMax_Execute)
                    {
                        tgCM_UT_ST__QU__Enqueue( &sQueue, sJob.psQU_Node );
                        sJob.psNode = nullptr; /* Not entirely correct, we could continue processing to fill IO queues on other file systems but ... */
                        break;
                    };

                    if (ETgFILE_IO_ACCESS__OVERLAPPED == (psFile_Info->m_enMode & ETgFILE_IO_ACCESS__OVERLAPPED))
                    {
                        TgRSIZE                             uiKN_IO_Status;

                        --psFile_Info->m_niCmd;
                        uiKN_IO_Status = ETgKN_IO_STATUS__QUEUED;
                        if (atomic_compare_exchange_strong( &sJob.ps->m_xuiStatus, &uiKN_IO_Status, ETgKN_IO_STATUS__EXECUTE ))
                        {
                            if (ETgFILE_COMMAND__CACHE == sJob.ps->m_enCmd)
                            {
                                /* #IMPLEMENT */
                                psFile_Info->m_enMode &= ~ETgFILE_IO_ACCESS__OVERLAPPED;
                            };
                            ++psFile_Info->m_niExecute;
                            ++psFS->m_niExecute;
                            psFS->m_pfnExecute_Job( sJob.ps );
                        }
                        else
                        {
                            TgERROR( ETgKN_IO_STATUS__CANCEL == uiKN_IO_Status );
                            tgKN_FS_Job_Complete_Final( psFS, sJob.ps );
                        };
                    }
                    else
                    {
                        tgCM_UT_ST__QU__Enqueue( &sQueue, sJob.psQU_Node );
                    };
                    break;

                case ETgFILE_COMMAND__CANCEL:
                case ETgFILE_COMMAND__UNKNOWN:
                default:
                    TgS_NO_DEFAULT( break );
            };
        }
        while (nullptr != sJob.psNode);

        tgCM_UT_ST__QU__Merge( &sQueue, &psFS->m_sProcess_Queue );
        tgCM_UT_ST__QU__Init( &psFS->m_sProcess_Queue );
        tgCM_UT_ST__QU__Merge( &psFS->m_sProcess_Queue, &sQueue );
    }
    while (0 != tgCM_UT_LF__SN_CNT__Signal_Or_Reset_Count( &psFS->m_sProcess_Lock.m_sLock ));
}
