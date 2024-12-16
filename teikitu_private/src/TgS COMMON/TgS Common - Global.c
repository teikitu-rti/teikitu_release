/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Global.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Data                                                                                                                                                                */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

static TgCHAR_U8                            s_szCmdLN_Parsed[KTgMAX_CMD_LINE_SIZE];
static TgCHAR_U8                            s_szCmdLN[KTgMAX_CMD_LINE_SIZE];
static TgCHAR_U8_CP                         s_aszCmd[KTgMAX_CMD_LINE_COUNT];
static TgSINT_E32                           s_niCmd;
static TgFLOAT32                            s_fCurrent;
static TgSINT_E32                           s_iCurrent;

static TgUINT_E32                           s_uiVersion;
static TgFLOAT32                            s_fFrameTime;
static TgUINT_E32                           s_bfGlobal;
static TgUINT_E64_A                         s_uiUnique;
static ETgMODULE_STATE                      s_enGlobal_State;




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgGB_Init ---------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgGB_Init( TgVOID )
{
    TgSINT_PTR                          iFile;
#if TgCOMPILE__THREAD
    TgRSIZE                             uiIndex;
#endif

    s_enGlobal_State = ETgMODULE_STATE__INITIALIZING;

    s_fCurrent                          = 0.0F;
    s_iCurrent                          = 0;

    s_uiVersion                         =  (TGS_VERSION__MAJOR & 0xFF)
                                        | ((TGS_VERSION__MINOR & 0xFF) << 8)
                                        | ((TGS_VERSION__PATCH & 0xFF) << 16)
                                        | ((TGS_VERSION__TWEAK & 0xFF) << 24);
    s_fFrameTime                        = 0.0F;

    tgTXT_Set_Local_Global( "en_US.UTF-8" );

    TgSTD_ATOMIC(store)( &s_uiUnique, 0ULL) ;

    tgMM_Set_U08_0x00( s_szCmdLN_Parsed, sizeof( s_szCmdLN_Parsed ) );
    tgMM_Set_U08_0x00( s_szCmdLN, sizeof( s_szCmdLN ) );
    tgMM_Set_U08_0x00( (TgVOID_P)s_aszCmd, sizeof( s_aszCmd ) );

    s_niCmd                             = 0;

#if TgCOMPILE__THREAD
    tgMM_Set_U08_0x00( g_afnTR_Thread_Function, sizeof( g_afnTR_Thread_Function ) );
    tgMM_Set_U08_0xFF( g_auiTR_Thread_Param, sizeof( g_auiTR_Thread_Param ) );
    tgMM_Set_U08_0xFF( g_aenTR_Thread_Priority, sizeof( g_aenTR_Thread_Priority ) );
    for (uiIndex = 0; uiIndex < TgARRAY_COUNT(g_axtiTR_Thread_Singleton); ++uiIndex)
    {
        tgTHREAD_ID_Invalidate( g_axtiTR_Thread_Singleton + uiIndex );
        TgSTD_ATOMIC(store)( &g_auiTR_Thread_Stack[uiIndex], KTgMAX_RSIZE );
    };

    tgCM_UT_LF__SN__Init( &g_sTR_Lock.m_sLock );

#if TgCOMPILE__THREAD_INFO
    tgMM_Set_U08_0xFF( (TgVOID_P)g_aszTR_Name, sizeof( g_aszTR_Name ) );
#endif
    
/*# TgCOMPILE__THREAD */
#endif

    if (TgFAILED(tgGB_Init_OS()))
    {
        return (KTgE_FAIL);
    };

    tgTM_Init();

    do
    {
        if (TgFAILED( tgCN_Init() ))
            break;
        if (TgFAILED( tgCN_Boot() ))
            break;
        if (TgFAILED(tgMM_Init_MGR()))
            break;
        if (TgFAILED(tgSM_Init_MGR()))
            break;
        if (TgFAILED(tgSM_Boot_MGR()))
            break;

        /* Look for additional command line arguments in a flat file */
        tgUSZ_Append( s_szCmdLN, KTgMAX_CMD_LINE_SIZE, u8" ", KTgMAX_RSIZE );
        if (tgIO_File_Exists( u8"command_line.txt", KTgMAX_RSIZE ) && (0 != ( iFile = tgIO_File_Open( u8"command_line.txt", KTgMAX_RSIZE, ETgFILE_IO_ACCESS__READ | ETgFILE_IO_ACCESS__SHARED ) )))
        {
            TgRSIZE                             nbyCmdLN = tgUSZ_Length_U08( s_szCmdLN, KTgMAX_RSIZE );
            TgRSIZE                             niData = KTgMAX_CMD_LINE_SIZE - 1 - nbyCmdLN;

            niData = tgIO_File_Read( s_szCmdLN + nbyCmdLN, iFile, niData );
            tgIO_File_Close( iFile );
            s_szCmdLN[nbyCmdLN + niData] = 0;
        };

        if (0 != s_szCmdLN[0])
        {
            s_niCmd = (TgSINT_E32 )tgGB_Parse_Command_Line( s_aszCmd, KTgMAX_CMD_LINE_COUNT, s_szCmdLN );
        };

    #if defined(TgCOMPILE__PROFILE) && TgCOMPILE__PROFILE
        if (TgFAILED(tgPF_Init()))
            break;
        if (TgFAILED(tgPF_Boot()))
            break;
    /*# defined(TgCOMPILE__PROFILE) && TgCOMPILE__PROFILE */
    #endif

        if (TgFAILED(tgJM_Init_MGR()))
            break;

        if (TgFAILED(tgEM_Init_MGR()))
            break;

        s_enGlobal_State = ETgMODULE_STATE__INITIALIZED;
        return (KTgS_OK);

    }
    while (0);

    TgERROR(false);
    tgGB_Free();
    return (KTgE_FAIL);
}


/* ---- tgGB_Boot ---------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgGB_Boot( TgVOID )
{
    /*  Quite obviously we cant use the memory manage to allocate memory at this point.  Use the C-standard allocator for these objects.  They should all be extremely small */
    /* and have no effect (should report back 100% error state). The reason for these is to allow any sub-system to die gracefully during initialization, giving back an */
    /* appropriate error rather than possible null-dereferences etc. */

    TgERROR(ETgMODULE_STATE__INITIALIZED == s_enGlobal_State || ETgMODULE_STATE__STOPPED == s_enGlobal_State);
    s_enGlobal_State = ETgMODULE_STATE__BOOTING;

    do
    {
        if (TgFAILED(tgGB_Boot_OS()))
            break;

        if (TgFAILED(tgMM_Boot_MGR()))
            break;

        if (TgFAILED(tgJM_Boot_MGR()))
            break;

        if (TgFAILED(tgEM_Boot_MGR()))
            break;

        if (tgGB_CMD_Query_Argument_Index( u8"-//stat/boot/command" ) >= 0)
        {
        #if TgS_STAT__COMMON
            tgGB_Stats( &g_sOutCon );
        /*# TgS_STAT__COMMON */
        #endif
            tgIO_PrintF( &g_sOutCon, u8"\n" );
        };

    #if !defined(TgCOMPILE__SYSTEM_INFORMATION)
        if (tgGB_CMD_Query_Argument_Index( "-//stat/boot/info" ) >= 0)
        {
            tgSI_Stats( &g_sOutCon );
        };
    /*# !defined(TgCOMPILE__SYSTEM_INFORMATION) */
    #endif

        if (tgGB_CMD_Query_Argument_Index( u8"-//stat/boot/console" ) >= 0)
        {
            tgCN_Print_Commands( &g_sOutCon );
        };

        if (TgS_DEBUG__COMMON || tgGB_CMD_Query_Argument_Index( u8"-//stat/boot/check_environment" ) >= 0)
        {
            tgUTM_Check_C11_Lock_Free_Status();
        };

        s_enGlobal_State = ETgMODULE_STATE__BOOTED;
        return (KTgS_OK);

    }
    while (0);

    TgERROR(false);
    tgGB_Stop();
    return (KTgE_FAIL);
}


/* ---- tgGB_Stop ---------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgGB_Stop( TgVOID )
{
    TgERROR(ETgMODULE_STATE__BOOTED == s_enGlobal_State);
    s_enGlobal_State = ETgMODULE_STATE__STOPPING;

    tgEM_Stop_MGR();
    tgJM_Stop_MGR();
    tgGB_Stop_OS();

    s_enGlobal_State = ETgMODULE_STATE__STOPPED;
}


/* ---- tgGB_Free ---------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgGB_Free( TgVOID )
{
#if TgCOMPILE__THREAD
    TgSINT_E32                          iIndex;
#endif

    TgERROR(ETgMODULE_STATE__STOPPED == s_enGlobal_State || ETgMODULE_STATE__INITIALIZED == s_enGlobal_State);
    s_enGlobal_State = ETgMODULE_STATE__FREEING;

    tgEM_Free_MGR();
    tgJM_Free_MGR();
#if TgCOMPILE__PROFILE
    tgPF_Stop();
    tgPF_Free();
/*# TgCOMPILE__PROFILE */
#endif

    tgCN_Stop();
    tgCN_Free();
    tgSM_Stop_MGR();
    tgSM_Free_MGR();
    tgMM_Free_MGR();

    tgGB_Free_OS();

    tgMM_Set_U08_0x00( s_szCmdLN, sizeof( s_szCmdLN ) );
    tgMM_Set_U08_0x00( (TgVOID_P)s_aszCmd, sizeof( s_aszCmd ) );

#if TgCOMPILE__THREAD
    for (iIndex = 1; iIndex < (TgSINT_E32 )TgARRAY_COUNT( g_axtiTR_Thread_Singleton ); ++iIndex)
    {
        TgERROR(!tgTHREAD_ID_Fetch_And_Is_Valid( nullptr, g_axtiTR_Thread_Singleton + iIndex ));
    };
    TgERROR(tgTHREAD_ID_Fetch_And_Is_Valid( nullptr, &(g_axtiTR_Thread_Singleton[iIndex]) ));
/*# TgCOMPILE__THREAD */
#endif

    tgTXT_Set_Local_Global( "" );
    s_enGlobal_State = ETgMODULE_STATE__FREED;
}


/* ---- tgGB_Update -------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgGB_Update( TgFLOAT32_C fDT )
{
    TgRESULT                            iResult = KTgS_OK;

    iResult |= tgMM_Update_MGR( fDT );
    iResult |= tgSM_Update_MGR( fDT );
    iResult |= tgEM_Update_MGR( fDT );
    iResult |= tgCN_Update( fDT );
#if TgCOMPILE__PROFILE
    iResult |= tgPF_Update( fDT );
#endif

    TgERROR(KTgS_OK == iResult);
    return (iResult);
}


/* ---- tgGB_Query_Init ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgGB_Query_Init( TgVOID )
{
    return ((ETgMODULE_STATE__INITIALIZED <= s_enGlobal_State) && (s_enGlobal_State <= ETgMODULE_STATE__STOPPED));
}


/* ---- tgGB_Query_Boot ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgGB_Query_Boot( TgVOID )
{
    return (ETgMODULE_STATE__BOOTED == s_enGlobal_State);
}


/* ---- tgGB_Query_Fixed_Memory -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRSIZE tgGB_Query_Fixed_Memory( TgVOID )
{
    return (0
        #if TgCOMPILE__THREAD
             + sizeof( g_auiTR_Thread_Stack )
             + sizeof( g_afnTR_Thread_Function )
             + sizeof( g_auiTR_Thread_Param )
             + sizeof( g_aenTR_Thread_Priority )
             + sizeof( g_axtiTR_Thread_Singleton )
             + sizeof( g_sTR_Lock )
        #if TgCOMPILE__THREAD_INFO
            + sizeof( g_aszTR_Name )
        #endif
        #endif
             + sizeof( s_szCmdLN )
             + sizeof( s_aszCmd )
             + sizeof( s_niCmd )
             + sizeof( s_fCurrent )
             + sizeof( s_iCurrent )
             + sizeof( s_uiVersion )
             + sizeof( s_fFrameTime )
             + sizeof( s_bfGlobal )
             + sizeof( s_uiUnique )
             + sizeof( s_enGlobal_State )
    );
}


/* ---- tgGB_Stats --------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if TgS_STAT__COMMON
TgVOID tgGB_Stats( TgATTRIBUTE_UNUSED STg2_Output_P psOutput )
{
    TgSINT_E32                          iIndex;

    for (iIndex = 0; iIndex < tgGB_CMD_Query_Argument_Count(); ++iIndex)
    {
        tgIO_PrintF( &g_sOutCon, u8"% 21.21s(% 2d): %s\n", u8"Cmd Line Arg", iIndex, tgGB_CMD_Query_Argument( iIndex ) );
    };
}
/*# TgS_STAT__COMMON */
#endif


/* ---- tgGB_CMD_Set_Command_Line ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgGB_CMD_Set_Command_Line( TgCHAR_U8_CPCU szCmdLN )
{
    if (nullptr == szCmdLN)
    {
        s_szCmdLN[0] = 0;
    }
    else
    {
        tgUSZ_Copy( s_szCmdLN_Parsed, KTgMAX_CMD_LINE_SIZE, szCmdLN, KTgMAX_CMD_LINE_SIZE );
        tgUSZ_Copy( s_szCmdLN, KTgMAX_CMD_LINE_SIZE, szCmdLN, KTgMAX_CMD_LINE_SIZE );
        s_niCmd = (TgSINT_E32)tgGB_Parse_Command_Line( s_aszCmd, KTgMAX_CMD_LINE_COUNT, s_szCmdLN_Parsed );
    }
}


/* ---- tgGB_CMD_Query_Argument_Count -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgSINT_E32 tgGB_CMD_Query_Argument_Count( TgVOID )
{
    return (s_niCmd);
}


/* ---- tgGB_CMD_Query_Argument -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgCHAR_U8_CP tgGB_CMD_Query_Argument( TgSINT_E32_C uiArg )
{
    return ((uiArg >= 0 && uiArg < s_niCmd) ? s_aszCmd[uiArg] : nullptr);
}


/* ---- tgGB_CMD_Query_Argument_Index -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgSINT_E32 tgGB_CMD_Query_Argument_Index( TgCHAR_U8_CPC mbzArgument )
{
    TgSINT_E32                          uiIndex;
    TgSINT_E08                          iRet;

    TgPARAM_CHECK(nullptr != mbzArgument);

    for (uiIndex = 0; uiIndex < s_niCmd; ++uiIndex)
    {
        if (TgSUCCEEDED(tgUSZ_Compare( &iRet, s_aszCmd[uiIndex], KTgMAX_RSIZE, 0, mbzArgument, KTgMAX_RSIZE, 0 )) && (0 == iRet))
        {
            return (uiIndex);
        };
    };

    return (-1);
}


/* ---- tgGB_CMD_Push_Argument --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgGB_CMD_Push_Argument( TgCHAR_U8_CPC mbzArgument )
{
    tgUSZ_AppendF( s_szCmdLN, KTgMAX_CMD_LINE_SIZE, u8" %s ", mbzArgument );
    tgUSZ_Copy( s_szCmdLN_Parsed, KTgMAX_CMD_LINE_SIZE, s_szCmdLN, KTgMAX_CMD_LINE_SIZE );
    s_niCmd = (TgSINT_E32)tgGB_Parse_Command_Line( s_aszCmd, KTgMAX_CMD_LINE_COUNT, s_szCmdLN_Parsed );
}


/* ---- tgGB_Reset_Frame_Time ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgGB_Reset_Frame_Time( TgVOID )
{
    s_fFrameTime = 0.0F;
    s_fCurrent = 0.0F;
    s_iCurrent = 0;
}


/* ---- tgGB_Set_Frame_Time ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgGB_Set_Frame_Time( TgFLOAT32_C fTime )
{
    TgERROR(!tgPM_NAN_F32( fTime ));
    s_fFrameTime = 0.0F;
    s_fCurrent = fTime;
}


/* ---- tgGB_Inc_Frame_Time ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgGB_Inc_Frame_Time( TgFLOAT32_C fTime )
{
    TgERROR(!tgPM_NAN_F32( fTime ));
    s_fFrameTime = fTime;
    s_fCurrent += fTime;
    ++s_iCurrent;
}


/* ---- tgGB_Set_Client ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgGB_Set_Client( TgBOOL_C bFlag )
{
    tgBF_Set_Flag_U32( &s_bfGlobal, 1, bFlag );
}


/* ---- tgGB_Set_Server ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgGB_Set_Server( TgBOOL_C bFlag )
{
    tgBF_Set_Flag_U32( &s_bfGlobal, 2, bFlag );
}


/* ---- tgGB_Set_Console_HW ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgGB_Set_Console_HW( TgBOOL_C bFlag )
{
    tgBF_Set_Flag_U32( &s_bfGlobal, 3, bFlag );
}


/* ---- tgGB_Set_Free_On_Quit ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgGB_Set_Free_On_Quit( TgBOOL_C bFlag )
{
    tgBF_Set_Flag_U32( &s_bfGlobal, 4, bFlag );
}


/* ---- tgGB_Get_Unique_Name ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgGB_Get_Unique_Name( TgCHAR_U8_PCU szDest, TgUINT_E32_C nbyDest )
{
    TgUINT_E64                          uiUnique, nbyUnique;
    TgCHAR_U8                           mbzNumber[32];

    uiUnique = TgSTD_ATOMIC(fetch_add)( &s_uiUnique, 1 );

    tgUSZ_From_U64( mbzNumber, 32, uiUnique );
    nbyUnique = tgUSZ_Length_U08( mbzNumber, sizeof mbzNumber );

    if (nbyUnique + 12 <= nbyDest)
    {
        tgUSZ_Copy( szDest, nbyDest, u8"UniqueName", KTgMAX_RSIZE );
        tgUSZ_Append( szDest, nbyDest, mbzNumber, sizeof mbzNumber );
        return (true);
    };

    return (false);
}


/* ---- tgGB_Query_Frame_Time ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgFLOAT32 tgGB_Query_Frame_Time( TgVOID )
{
    return (s_fFrameTime);
}


/* ---- tgGB_Query_Total_Frame --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgSINT_E32 tgGB_Query_Total_Frame( TgVOID )
{
    return (s_iCurrent);
}


/* ---- tgGB_Query_Total_Time ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgFLOAT32 tgGB_Query_Total_Time( TgVOID )
{
    return (s_fCurrent);
}


/* ---- tgGB_Query_Client -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgGB_Query_Client( TgVOID )
{
    return (tgBF_Test_Flag_U32( &s_bfGlobal, 1 ));
}


/* ---- tgGB_Query_Server -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgGB_Query_Server( TgVOID )
{
    return (tgBF_Test_Flag_U32( &s_bfGlobal, 2 ));
}


/* ---- tgGB_Query_Console_HW ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgGB_Query_Console_HW( TgVOID )
{
    return (tgBF_Test_Flag_U32( &s_bfGlobal, 3 ));
}


/* ---- tgGB_Query_Free_On_Quit -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgGB_Query_Free_On_Quit( TgVOID )
{
    return (tgBF_Test_Flag_U32( &s_bfGlobal, 4 ));
}


/* ---- tgGB_Parse_Command_Line -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgUINT_E32 tgGB_Parse_Command_Line( TgCHAR_U8_CPP aszArg, TgRSIZE_C uiMaxArg, TgCHAR_U8_PC mbzCmdLN )
{
    TgUINT_E32                          uiIndex;
    TgUINT_E32                          nuiCmd = 0;

    TgPARAM_CHECK(nullptr != mbzCmdLN);
    TgPARAM_CHECK(nullptr != aszArg && uiMaxArg);

    /* We have a command line - parse it out. */
    tgCN_PrintF( KTgCN_CHANEL_MESSAGE | KTgCN_SEVERITY_D, u8"Command Line: %s\n", mbzCmdLN );

    for (uiIndex = 0; 0 != mbzCmdLN[uiIndex]; ++uiIndex)
    {
        /* Ignore white space command line tokens */

        if ((' ' == mbzCmdLN[uiIndex]) || ('\t' == mbzCmdLN[uiIndex]))
        {
            mbzCmdLN[uiIndex] = 0;
            continue;
        };

        if (nuiCmd + 1 >= uiMaxArg)
        {
            TgWARNING_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Insufficient argument storage." );
            aszArg[nuiCmd] = 0; /**< Null terminate the list of command line tokens */
            return (nuiCmd);
        }

        aszArg[nuiCmd++] = mbzCmdLN + uiIndex;

        for (; (0 != mbzCmdLN[uiIndex]) && (' ' != mbzCmdLN[uiIndex]) && ('\t' != mbzCmdLN[uiIndex]); ++uiIndex)
        {
            /* Do not attempt to parse text with quotes */

            if ('\"' != mbzCmdLN[uiIndex])
            {
                continue;
            };

            /* Process until the end of the string or the next quotation */

            for (++uiIndex; (0 != mbzCmdLN[uiIndex]) && ('\"' != mbzCmdLN[uiIndex]); ++uiIndex);

            if (0 == mbzCmdLN[uiIndex])
            {
                TgWARNING_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unbalanced quotation marks in command line." );
                aszArg[nuiCmd] = 0; /**< Null terminate the list of command line tokens */
                return (nuiCmd);
            };
        };

        if (0 == mbzCmdLN[uiIndex])
        {
            tgCN_PrintF( KTgCN_CHANEL_MESSAGE | KTgCN_SEVERITY_D, u8"    Argument(%d) %s\n", nuiCmd, aszArg[nuiCmd - 1] );
            aszArg[nuiCmd] = 0; /**< Null terminate the list of command line tokens */
            return (nuiCmd);
        }

        mbzCmdLN[uiIndex] = 0;
        tgCN_PrintF( KTgCN_CHANEL_MESSAGE | KTgCN_SEVERITY_D, u8"    Argument(%d) %s\n", nuiCmd, aszArg[nuiCmd - 1] );
    };

    aszArg[nuiCmd] = 0; /**< Null terminate the list of command line tokens */
    return (nuiCmd);
}


/* ---- tgGB_Verify_Version ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgGB_Verify_Version( TgUINT_E32_C uiVersion )
{
    return (s_uiVersion == uiVersion);
}
