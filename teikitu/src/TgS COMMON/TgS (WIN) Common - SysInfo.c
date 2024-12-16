/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (WIN) Common - SysInfo.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#pragma warning( push, 3 )
#include <malloc.h>
#include <time.h>
#pragma warning( pop )
#pragma warning(disable : 4201) /* nonstandard extension used: nameless struct/union */


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/*
*/
static TgRSIZE
INIT_Get_System_User_Strings( 
    TgCHAR_U8_P OUT0, TgRSIZE_C ARG1 );

/** @brief Initialize low-level time related variables to support timing functionality.
    @return Result Code. */
static TgRESULT
Init_Timer( TgVOID );

/** @brief Set Accessor: Set the local variable indicating the existence of a mouse.
    @param [in] ARG0 Boolean flag. */
TgINLINE TgVOID
SYSTEM_Set_Mouse(
    TgBOOL_C ARG0 );

/** @brief Set Accessor: Set the local variable indicating the existence of a network.
    @param [in] ARG0 Boolean flag. */
TgINLINE TgVOID
SYSTEM_Set_Network(
    TgBOOL_C ARG0 );

/** @brief Set Accessor: Set the local variable indicating a clean boot of the computer.
    @param [in] ARG0 Boolean flag. */
TgINLINE TgVOID
SYSTEM_Set_Clean_Boot(
    TgBOOL_C ARG0 );

/** @brief Get Accessor: Return if the application has access to a mouse.
    @return True if the application has access to a mouse, and false otherwise. */
TgINLINE TgBOOL
SYSTEM_Has_Mouse( TgVOID );

/** @brief Get Accessor: Return if the application has access to a network.
    @return True if the application has access to a network, and false otherwise. */
TgINLINE TgBOOL
SYSTEM_Has_Network( TgVOID );

/** @brief Get Accessor: Return if the local machine is in a clean (default,normal) booted state.
    @return True if the local machine is in a clean (default,normal) booted state, and false otherwise. */
TgINLINE TgBOOL
SYSTEM_Clean_Boot( TgVOID );

/** @brief Set Accessor: Set the local variable indicating the availability of MMX instruction set.
    @param [in] ARG0 Boolean flag. */
TgINLINE TgVOID
MATH_Set_MMX(
    TgBOOL_C ARG0 );

/** @brief Set Accessor: Set the local variable indicating the availability of XMM instruction set.
    @param [in] ARG0 Boolean flag. */
TgINLINE TgVOID
MATH_Set_XMM(
    TgBOOL_C ARG0 );

/** @brief Set Accessor: Set the local variable indicating the availability of XMM2 instruction set.
    @param [in] ARG0 Boolean flag. */
TgINLINE TgVOID
MATH_Set_XMM2(
    TgBOOL_C ARG0 );

/** @brief Set Accessor: Set the local variable indicating the availability of 3DNOW instruction set.
    @param [in] ARG0 Boolean flag. */
TgINLINE TgVOID
MATH_Set_3DNow(
    TgBOOL_C ARG0 );

/** @brief Set Accessor: Set the local variable indicating the availability of RDTSC instruction.
    @param [in] ARG0 Boolean flag. */
TgINLINE TgVOID
MATH_Set_RDTSC(
    TgBOOL_C ARG0 );

/** @brief Get Accessor: Return the availability of the MMX instruction set.
    @return True if the availability of the MMX instruction set, and false otherwise. */
TgINLINE TgBOOL
MATH_Has_MMX( TgVOID );

/** @brief Get Accessor: Return the availability of the XMM instruction set.
    @return True if the availability of the XMM instruction set, and false otherwise. */
TgINLINE TgBOOL
MATH_Has_XMM( TgVOID );

/** @brief Get Accessor: Return the availability of the XMM2 instruction set.
    @return True if the availability of the XMM2 instruction set, and false otherwise. */
TgINLINE TgBOOL
MATH_Has_XMM2( TgVOID );

/** @brief Get Accessor: Return the availability of the 3DNOW instruction set.
    @return True if the availability of the 3DNOW instruction set, and false otherwise. */
TgINLINE TgBOOL
MATH_Has_3DNow( TgVOID );

/** @brief Get Accessor: Return the availability of the RDTSC instruction.
    @return True if the availability of the RDTSC instruction, and false otherwise. */
TgINLINE TgBOOL
MATH_Has_RDTSC( TgVOID );

/** @brief Set Accessor: Set the local variable indicating the existence of a mouse wheel.
    @param [in] ARG0 Boolean flag. */
TgINLINE TgVOID
INPUT_Set_Mouse_Wheel(
    TgBOOL_C ARG0 );


/* Console Functions */
#if TgCOMPILE__CONSOLE

/** @brief Console function to output the configuration of the system.
    @param [in] ARG0 [unused] Integer holding the number of strings.
    @param [in,out] ARG1 [unused] Array of strings. */
static TgNOTHROW TgVOID
SI_CO_Print_Configuration(
    TgUINT_F32_C ARG0, TgCHAR_U8_CP ARG1[KTgMAX_CMD_LINE_COUNT] );

/** @brief Console function to output all of the loaded modules owned by the application.
    @param [in] ARG0 [unused] Integer holding the number of strings.
    @param [in,out] ARG1 [unused] Array of strings. */
static TgNOTHROW TgVOID
SI_CO_Print_Modules(
    TgUINT_F32_C ARG0, TgCHAR_U8_CP ARG1[KTgMAX_CMD_LINE_COUNT] );

/** @brief Console function to output all of the threads of the application.
    @param [in] ARG0 [unused] Integer holding the number of strings.
    @param [in,out] ARG1 [unused] Array of strings. */
static TgNOTHROW TgVOID
SI_CO_Print_Threads(
    TgUINT_F32_C ARG0, TgCHAR_U8_CP ARG1[KTgMAX_CMD_LINE_COUNT] );

/*# TgCOMPILE__CONSOLE */
#endif

static ETgMODULE_STATE                      s_enSI_State = ETgMODULE_STATE__FREED;

/* System Parameters */
static TgUINT_F32                           s_uiSI_Page_Size = 0;
static TgFLOAT64                            s_fSI_Seconds_Per_CounterTick = 0.0;
static TgCHAR_U8_P                          s_szSI_System_Dir = nullptr;
static TgCHAR_U8_P                          s_szSI_Window_Dir = nullptr;
static TgCHAR_U8_P                          s_szSI_Current_Dir = nullptr;
static TgCHAR_U8_P                          s_szSI_Module_Dir = nullptr;
static TgCHAR_U8_P                          s_szSI_Computer_Name = nullptr;
static TgCHAR_U8_P                          s_szSI_User_Name = nullptr;
static TgCHAR_U8_P                          s_szSI_Hardware_Profile_GUID = nullptr;
static TgCHAR_U8_P                          s_szSI_Hardware_Profile_Name = nullptr;
static TgUINT_F32                           s_nuiSI_Processors = 0;

/* Input Parameters */
static TgUINT_F32                           s_uiSI_IN_Mouse_Bounds_X_Double_Click = 0;
static TgUINT_F32                           s_uiSI_IN_Mouse_Bounds_Y_Double_Click = 0;
static TgUINT_F32                           s_uiSI_IN_Mouse_Bounds_X_Drag = 0;
static TgUINT_F32                           s_uiSI_IN_Mouse_Bounds_Y_Drag = 0;

static TgUINT_F32                           s_uiSI_Bounds_Hover_Height = 0;
static TgUINT_F32                           s_uiSI_Bounds_Hover_Width = 0;
static TgUINT_F32                           s_uiSI_Bounds_Hover_Time = 0;
static TgCHAR_U8_P                          s_pszSI_String_Pool = 0;

static TgUINT_F32                           s_bfSystemChecks = 0;
static TgUINT_F32                           s_bfInputChecks = 0;




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* == Platform Implementation ==================================================================================================================================================== */

/* ---- tgSI_Init ---------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgSI_Init( TgVOID )
{
    TgRSIZE_C                           uiBuffer_Size_U8 = 4*1024*1024;
    TgCHAR_U8_P                         pBuffer_U8;
    TgRESULT                            iResult;
    TgRSIZE                             uiSize_08;
    SYSTEM_INFO                         siSystemInfo;

    /* Verify the state of the system */
    TgERROR(ETgMODULE_STATE__FREED == s_enSI_State);
    s_enSI_State = ETgMODULE_STATE__INITIALIZING;

    tgBF_Reset_U32( &s_bfSystemChecks );
    tgBF_Reset_U32( &s_bfInputChecks );

    g_pfnGetSystemInfo( &siSystemInfo );

    s_uiSI_Page_Size = siSystemInfo.dwPageSize;
    s_nuiSI_Processors = (TgUINT_E08)siSystemInfo.dwNumberOfProcessors;

#if !defined(TgBUILD_UNIVERSAL__UWP)
    SYSTEM_Set_Clean_Boot( 0 == g_pfnGetSystemMetrics( SM_CLEANBOOT ) );
    SYSTEM_Set_Mouse( 0 != g_pfnGetSystemMetrics( SM_MOUSEPRESENT ) );
    SYSTEM_Set_Network( 0 != g_pfnGetSystemMetrics( SM_NETWORK ) );
/*# !defined(TgBUILD_UNIVERSAL__UWP) */
#endif

    MATH_Set_MMX( 0 != g_pfnIsProcessorFeaturePresent( PF_MMX_INSTRUCTIONS_AVAILABLE ) );
    MATH_Set_XMM( 0 != g_pfnIsProcessorFeaturePresent( PF_XMMI_INSTRUCTIONS_AVAILABLE ) );
    MATH_Set_3DNow( 0 != g_pfnIsProcessorFeaturePresent( PF_3DNOW_INSTRUCTIONS_AVAILABLE ) );
    MATH_Set_RDTSC( 0 != g_pfnIsProcessorFeaturePresent( PF_RDTSC_INSTRUCTION_AVAILABLE ) );

#if !defined(TgBUILD_UNIVERSAL__UWP)
    s_uiSI_IN_Mouse_Bounds_X_Double_Click = (TgUINT_E08)g_pfnGetSystemMetrics( SM_CXDOUBLECLK );
    s_uiSI_IN_Mouse_Bounds_Y_Double_Click = (TgUINT_E08)g_pfnGetSystemMetrics( SM_CYDOUBLECLK );
    s_uiSI_IN_Mouse_Bounds_X_Drag = (TgUINT_E08)g_pfnGetSystemMetrics( SM_CXDRAG );
    s_uiSI_IN_Mouse_Bounds_Y_Drag = (TgUINT_E08)g_pfnGetSystemMetrics( SM_CYDRAG );

    g_pfnSystemParametersInfo( 0x0066, 0, &s_uiSI_Bounds_Hover_Time, 0 );
    g_pfnSystemParametersInfo( 0x0062, 0, &s_uiSI_Bounds_Hover_Height, 0 );
    g_pfnSystemParametersInfo( 0x0064, 0, &s_uiSI_Bounds_Hover_Width, 0 );

    INPUT_Set_Mouse_Wheel( 0 != g_pfnGetSystemMetrics( SM_MOUSEWHEELPRESENT ) );
/*# !defined(TgBUILD_UNIVERSAL__UWP) */
#endif

    /* Init String Data - Directories, Computer and User Name */
    pBuffer_U8 = (TgCHAR_U8_P)malloc(uiBuffer_Size_U8);
    uiSize_08 = INIT_Get_System_User_Strings( pBuffer_U8, uiBuffer_Size_U8 );
    if ((0 != uiSize_08) && (uiSize_08 < uiBuffer_Size_U8))
    {
        /* Concatenate all the Temp Buffers into one allocated permanent buffer */
        s_pszSI_String_Pool = (TgCHAR_U8_P)(malloc(uiSize_08));
        TgERROR(nullptr != s_pszSI_String_Pool);

        s_szSI_Current_Dir = s_pszSI_String_Pool + (s_szSI_Current_Dir - pBuffer_U8);
        s_szSI_System_Dir = s_pszSI_String_Pool + (s_szSI_System_Dir - pBuffer_U8);
        s_szSI_Window_Dir = s_pszSI_String_Pool + (s_szSI_Window_Dir - pBuffer_U8);
        s_szSI_Module_Dir = s_pszSI_String_Pool + (s_szSI_Module_Dir - pBuffer_U8);
        s_szSI_Computer_Name = s_pszSI_String_Pool + (s_szSI_Computer_Name - pBuffer_U8);
        s_szSI_User_Name = s_pszSI_String_Pool + (s_szSI_User_Name - pBuffer_U8);
        s_szSI_Hardware_Profile_GUID = s_pszSI_String_Pool + (s_szSI_Hardware_Profile_GUID - pBuffer_U8);
        s_szSI_Hardware_Profile_Name = s_pszSI_String_Pool + (s_szSI_Hardware_Profile_Name - pBuffer_U8);

        tgMM_Copy( s_pszSI_String_Pool, uiSize_08, pBuffer_U8, uiSize_08 );
    }
    else
    {
        /* Concatenate all the Temp Buffers into one allocated permanent buffer */
        s_pszSI_String_Pool = (TgCHAR_U8_P)(malloc(8));
        TgERROR(nullptr != s_pszSI_String_Pool);

        s_szSI_Current_Dir = s_pszSI_String_Pool + (0);
        s_szSI_System_Dir = s_pszSI_String_Pool + (1);
        s_szSI_Window_Dir = s_pszSI_String_Pool + (2);
        s_szSI_Module_Dir = s_pszSI_String_Pool + (3);
        s_szSI_Computer_Name = s_pszSI_String_Pool + (4);
        s_szSI_User_Name = s_pszSI_String_Pool + (5);
        s_szSI_Hardware_Profile_GUID = s_pszSI_String_Pool + (6);
        s_szSI_Hardware_Profile_Name = s_pszSI_String_Pool + (7);

        tgMM_Set_U08_0x00( s_pszSI_String_Pool, 8 );
    }
    free(pBuffer_U8);

    /* Init the CPU Counter to Real Time Translation */
    iResult = Init_Timer();
    s_enSI_State = ETgMODULE_STATE__INITIALIZED;

    if (TgFAILED( iResult ))
    {
        tgSI_Free();
        return (KTgE_FAIL);
    };
    return (KTgS_OK);
}

/* ---- tgSI_Boot ---------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgSI_Boot( TgVOID )
{
    /* Verify the state of the system */
    TgERROR(ETgMODULE_STATE__INITIALIZED == s_enSI_State);
    s_enSI_State = ETgMODULE_STATE__BOOTING;

#if TgCOMPILE__CONSOLE
    tgCN_Insert_Command_Function( u8"print_info_configuration", KTgMAX_RSIZE, SI_CO_Print_Configuration, u8"Print basic operating system information", KTgMAX_RSIZE );
    tgCN_Insert_Command_Function( u8"print_info_modules", KTgMAX_RSIZE, SI_CO_Print_Modules, u8"Print a list of modules current loads (DLLs)", KTgMAX_RSIZE );
    tgCN_Insert_Command_Function( u8"print_info_threads", KTgMAX_RSIZE, SI_CO_Print_Threads, u8"Print a list of all the active threads", KTgMAX_RSIZE );

    if (tgGB_CMD_Query_Argument_Index( u8"-//stat/boot/info" ) >= 0)
    {
        SI_CO_Print_Configuration( 0, nullptr );
        SI_CO_Print_Modules( 0, nullptr );
        SI_CO_Print_Threads( 0, nullptr );
    }
/*# TgCOMPILE__CONSOLE */
#endif

    s_enSI_State = ETgMODULE_STATE__BOOTED;
    return (KTgS_OK);
}


/* ---- tgSI_Stop ---------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgSI_Stop( TgVOID )
{
    if ((ETgMODULE_STATE__FREED == s_enSI_State) || (ETgMODULE_STATE__INITIALIZED == s_enSI_State))
    {
        return (KTgS_OK);
    };

    /* Verify the state of the system */
    TgERROR(ETgMODULE_STATE__BOOTED == s_enSI_State);
    s_enSI_State = ETgMODULE_STATE__STOPPING;

#if TgCOMPILE__CONSOLE
    tgCN_Remove_Command_Function( u8"print_info_threads", KTgMAX_RSIZE );
    tgCN_Remove_Command_Function( u8"print_info_modules", KTgMAX_RSIZE );
    tgCN_Remove_Command_Function( u8"print_info_configuration", KTgMAX_RSIZE );
/*# TgCOMPILE__CONSOLE */
#endif

    s_enSI_State = ETgMODULE_STATE__STOPPED;
    return (KTgS_OK);
}


/* ---- tgSI_Free ---------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgSI_Free( TgVOID )
{
    if (ETgMODULE_STATE__FREED == s_enSI_State)
    {
        return (KTgS_OK);
    };

    /* Verify the state of the system */
    TgERROR((ETgMODULE_STATE__STOPPED == s_enSI_State) || (ETgMODULE_STATE__INITIALIZED == s_enSI_State));
    s_enSI_State = ETgMODULE_STATE__FREEING;

    if (s_pszSI_String_Pool)
    {
        free( s_pszSI_String_Pool );
        s_pszSI_String_Pool = nullptr;
    }

    s_enSI_State = ETgMODULE_STATE__FREED;
    return (KTgS_OK);
}


/* ---- tgSI_Query_Init ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgSI_Query_Init( TgVOID )
{
    return (ETgMODULE_STATE__INITIALIZED <= s_enSI_State && s_enSI_State <= ETgMODULE_STATE__STOPPED);
}


/* ---- tgSI_Query_Boot ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgSI_Query_Boot( TgVOID )
{
    return (ETgMODULE_STATE__BOOTED == s_enSI_State);
}


/* ---- tgSI_Query_Fixed_Memory -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRSIZE tgSI_Query_Fixed_Memory( TgVOID )
{
    return (0
        + sizeof( s_uiSI_Page_Size )
        + sizeof( s_fSI_Seconds_Per_CounterTick )
        + sizeof( s_szSI_System_Dir )
        + sizeof( s_szSI_Window_Dir )
        + sizeof( s_szSI_Current_Dir )
        + sizeof( s_szSI_Module_Dir )
        + sizeof( s_szSI_Computer_Name )
        + sizeof( s_szSI_User_Name )
        + sizeof( s_szSI_Hardware_Profile_GUID )
        + sizeof( s_szSI_Hardware_Profile_Name )
        + sizeof( s_nuiSI_Processors )
        + sizeof( s_uiSI_IN_Mouse_Bounds_X_Double_Click )
        + sizeof( s_uiSI_IN_Mouse_Bounds_Y_Double_Click )
        + sizeof( s_uiSI_IN_Mouse_Bounds_X_Drag )
        + sizeof( s_uiSI_IN_Mouse_Bounds_Y_Drag )
        + sizeof( s_uiSI_Bounds_Hover_Height )
        + sizeof( s_uiSI_Bounds_Hover_Width )
        + sizeof( s_uiSI_Bounds_Hover_Time )
        + sizeof( s_pszSI_String_Pool )
        + sizeof( s_bfSystemChecks )
        + sizeof( s_bfInputChecks )
    );
}


/* ---- tgSI_Stats --------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgSI_Stats( STg2_Output_P pOutput )
{
    tgIO_PrintF( pOutput, u8"System Information --------------------------------------------------------------------------------"
                          u8"---------------------------------\n\n" );

    tgSI_Print_Configuration( pOutput );
#if !defined(TgBUILD_UNIVERSAL__UWP)
    tgSI_Print_Modules( pOutput );
    tgTR_Print_Threads( pOutput );
/*# !defined(TgBUILD_UNIVERSAL__UWP) */
#endif

    tgIO_PrintF( pOutput, u8"\nSystem Information ------------------------------------------------------------------------------"
                          u8"-----------------------------------\n\n" );
}


/* == Platform Specific Functions ================================================================================================================================================ */

/* ---- tgSI_SYSTEM_Seconds_Per_CounterTick -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgFLOAT64 tgSI_SYSTEM_Seconds_Per_CounterTick( TgVOID )
{
    return (s_fSI_Seconds_Per_CounterTick);
}


/* ---- tgSI_SYSTEM_Page_Size ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgUINT_F32 tgSI_SYSTEM_Page_Size( TgVOID )
{
    return (s_uiSI_Page_Size);
}


/* ---- tgSI_SYSTEM_Number_Of_Processors ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgUINT_F32 tgSI_SYSTEM_Number_Of_Processors( TgVOID )
{
    return (s_nuiSI_Processors);
}


/* ---- tgSI_INPUT_Has_Mouse_Wheel ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgSI_INPUT_Has_Mouse_Wheel( TgVOID )
{
    return (tgBF_Test_Flag_U32( &s_bfInputChecks, 0 ));
}


/* ---- tgSI_APP_Is_Remote_Session ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgSI_APP_Is_Remote_Session( TgVOID )
{
    return (0 != g_pfnGetSystemMetrics( SM_REMOTESESSION ));
}


/* ---- tgSI_Query_WorkPath ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgCHAR_U8_CP tgSI_Query_WorkPath( TgVOID )
{
    return (s_szSI_Current_Dir);
}


/* ---- tgSI_Query_SysPath ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgCHAR_U8_CP tgSI_Query_SysPath( TgVOID )
{
    return (s_szSI_System_Dir);
}


/* ---- tgSI_Query_WinPath ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgCHAR_U8_CP tgSI_Query_WinPath( TgVOID )
{
    return (s_szSI_Window_Dir);
}


/* ---- tgSI_Query_ExePath ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgCHAR_U8_CP tgSI_Query_ExePath( TgVOID )
{
    return (s_szSI_Module_Dir);
}


/* ---- tgSI_Query_Computer_Name ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgCHAR_U8_CP tgSI_Query_Computer_Name( TgVOID )
{
    return (s_szSI_Computer_Name);
}


/* ---- tgSI_Query_User_Name ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgCHAR_U8_CP tgSI_Query_User_Name( TgVOID )
{
    return (s_szSI_User_Name);
}


/* ---- tgSI_Print_Configuration ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgSI_Print_Configuration( STg2_Output_P pOutput )
{
    MEMORYSTATUSEX                      sMemoryStatus;

    tgMM_Set_U08_0x00( &sMemoryStatus, sizeof( sMemoryStatus ) );
    sMemoryStatus.dwLength = sizeof( sMemoryStatus );
#if !defined(TgBUILD_UNIVERSAL__UWP)
    g_pfnGlobalMemoryStatusEx( &sMemoryStatus );
#endif

    tgIO_PrintF( pOutput, u8"% 25.25s: %d\n", u8"Number of Processors", s_nuiSI_Processors );
    tgIO_PrintF( pOutput, u8"% 25.25s: %.0f\n", u8"CPU Speed", (0.000001 / s_fSI_Seconds_Per_CounterTick) );
    tgIO_PrintF( pOutput, u8"% 25.25s: %s\n", u8"MMX Instructions", MATH_Has_MMX() ? "TRUE" : "FALSE" );
    tgIO_PrintF( pOutput, u8"% 25.25s: %s\n", u8"XMM Instructions", MATH_Has_XMM() ? "TRUE" : "FALSE" );
    tgIO_PrintF( pOutput, u8"% 25.25s: %s\n", u8"XMM2 Instructions", MATH_Has_XMM2() ? "TRUE" : "FALSE" );
    tgIO_PrintF( pOutput, u8"% 25.25s: %s\n", u8"3DNOW Instructions", MATH_Has_3DNow() ? "TRUE" : "FALSE" );
    tgIO_PrintF( pOutput, u8"% 25.25s: %s\n\n", u8"RDTSC Instruction", MATH_Has_RDTSC() ? "TRUE" : "FALSE" );

    tgIO_PrintF( pOutput, u8"% 25.25s: %d\n", u8"Memory in Use", sMemoryStatus.dwMemoryLoad );
    tgIO_PrintF( pOutput, u8"% 25.25s: %I64d KB\n", u8"Total Physical Memory", (sMemoryStatus.ullTotalPhys / 1024) );
    tgIO_PrintF( pOutput, u8"% 25.25s: %I64d KB\n", u8"Free Physical Memory", (sMemoryStatus.ullAvailPhys / 1024) );
    tgIO_PrintF( pOutput, u8"% 25.25s: %I64d KB\n", u8"Total Paging File", (sMemoryStatus.ullTotalPageFile / 1024) );
    tgIO_PrintF( pOutput, u8"% 25.25s: %I64d KB\n", u8"Free Paging File", (sMemoryStatus.ullAvailPageFile / 1024) );
    tgIO_PrintF( pOutput, u8"% 25.25s: %I64d KB\n", u8"Total Virtual Memory", (sMemoryStatus.ullTotalVirtual / 1024) );
    tgIO_PrintF( pOutput, u8"% 25.25s: %I64d KB\n", u8"Free Virtual Memory", (sMemoryStatus.ullAvailVirtual / 1024) );
    tgIO_PrintF( pOutput, u8"% 25.25s: %d\n\n", u8"Memory Page_Size", s_uiSI_Page_Size );

    tgIO_PrintF( pOutput, u8"\n% 25.25s: %s\n", u8"System Directory", s_szSI_System_Dir );
    tgIO_PrintF( pOutput, u8"% 25.25s: %s\n", u8"Windows Directory: ", s_szSI_Window_Dir );
    tgIO_PrintF( pOutput, u8"% 25.25s: %s\n", u8"Current Directory", s_szSI_Current_Dir );
    tgIO_PrintF( pOutput, u8"% 25.25s: %s\n\n", u8"Module Directory", s_szSI_Module_Dir );

    tgIO_PrintF( pOutput, u8"% 25.25s: %s\n", u8"Computer Name", s_szSI_Computer_Name );
    tgIO_PrintF( pOutput, u8"% 25.25s: %s\n", u8"User Name", s_szSI_User_Name );
    tgIO_PrintF( pOutput, u8"% 25.25s: %s\n", u8"Hardware Profile GUID", s_szSI_Hardware_Profile_GUID );
    tgIO_PrintF( pOutput, u8"% 25.25s: %s\n\n", u8"Hardware Profile Name", s_szSI_Hardware_Profile_Name );

    tgIO_PrintF( pOutput, u8"% 25.25s: %d %d\n", u8"Mouse DblClik Bounds", s_uiSI_IN_Mouse_Bounds_X_Double_Click, s_uiSI_IN_Mouse_Bounds_Y_Double_Click );
    tgIO_PrintF( pOutput, u8"% 25.25s: %d %d\n", u8"Mouse Drag Bounds", s_uiSI_IN_Mouse_Bounds_X_Drag, s_uiSI_IN_Mouse_Bounds_Y_Drag );
    tgIO_PrintF( pOutput, u8"% 25.25s: %d %d %d\n\n", u8"Mouse Hover Bounds", s_uiSI_Bounds_Hover_Width, s_uiSI_Bounds_Hover_Height, s_uiSI_Bounds_Hover_Time );
}


/* ---- tgSI_Print_Modules ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if !defined(TgBUILD_UNIVERSAL__UWP)
TgVOID tgSI_Print_Modules( STg2_Output_P pOutput )
{
    HINSTANCE                           hProcess;
    HINSTANCE                           hMods[1024];
    TgUINT_F32                          cbNeeded;

    hProcess = (HINSTANCE)g_pfnGetCurrentProcess();

    tgIO_PrintF( pOutput, u8"% 25.25s: %u\n", u8"Process ID", hProcess );

    if (g_pfnEnumProcessModulesEx( hProcess, hMods, sizeof( hMods ), &cbNeeded, 3 ))
    {
        TgOSCHAR_P                          poszModeName;
        TgCHAR_U8_P                         pszModeName;
        TgUINT_F32                          iIndex;

        poszModeName = (TgOSCHAR_P)TgMALLOC_TEMP(KTgMAX_FILE_PATH*sizeof(TgOSCHAR));
        pszModeName = (TgCHAR_U8_P)TgMALLOC_TEMP(KTgMAX_FILE_PATH*4);

        for (iIndex = 0; iIndex < (cbNeeded / sizeof( HINSTANCE )); ++iIndex)
        {
            if (g_pfnGetModuleFileNameEx( hProcess, hMods[iIndex], poszModeName, KTgMAX_FILE_PATH ))
            {
                TgOS_TEXT_CONVERT_FCN(tgUSZ_Convert)( pszModeName, KTgMAX_FILE_PATH*4, poszModeName, KTgMAX_FILE_PATH*sizeof(TgOSCHAR) );
                tgIO_PrintF( pOutput, u8"% 25.25s: 0x%08X %s\n", u8"Module", hMods[iIndex], pszModeName );
            };
        };

        TgFREE_TEMP(pszModeName);
        TgFREE_TEMP(poszModeName);
    };
}
/*# !defined(TgBUILD_UNIVERSAL__UWP) */
#endif




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- INIT_Get_System_User_Strings --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRSIZE INIT_Get_System_User_Strings( TgCHAR_U8_P pBuffer_U8, TgRSIZE_C uiBuffer_Size_U8 )
{
    TgRSIZE_C                           uiBuffer_Size_OS = 64*1024; /* 32K characters is the max path length on NTFS/REFS when long path is enabled. */
    TgOSCHAR_P                          pBuffer_OS;
    TgRSIZE                             uiBuffer_U8_Offset_08;
    HW_PROFILE_INFO                     siHardwareProfile;
    DWORD                               dwSize;

    pBuffer_OS = (TgOSCHAR_P)malloc( uiBuffer_Size_OS );
    uiBuffer_U8_Offset_08 = 0;

    s_szSI_Current_Dir = pBuffer_U8 + uiBuffer_U8_Offset_08;
    dwSize = g_pfnGetCurrentDirectory( uiBuffer_Size_OS, pBuffer_OS );
    if ((0 != dwSize) && (dwSize < uiBuffer_Size_OS))
    {
        if (FAILED(TgOS_TEXT_CONVERT_FCN(tgUSZ_Convert)( s_szSI_Current_Dir, uiBuffer_Size_U8 - uiBuffer_U8_Offset_08, pBuffer_OS, uiBuffer_Size_OS )))
        {
            free(pBuffer_OS);
            return (0);
        }
        uiBuffer_U8_Offset_08 += tgUSZ_Length_U08( s_szSI_Current_Dir, uiBuffer_Size_U8 - uiBuffer_U8_Offset_08 );
    }

    if (uiBuffer_U8_Offset_08 + 1 >= uiBuffer_Size_U8)
    {
        free(pBuffer_OS);
        return (0);
    }
    pBuffer_U8[uiBuffer_U8_Offset_08] = 0;
    uiBuffer_U8_Offset_08 += 1;

#if !defined(TgBUILD_UNIVERSAL__UWP)
    s_szSI_System_Dir = pBuffer_U8 + uiBuffer_U8_Offset_08;
    if (g_pfnGetSystemDirectory( pBuffer_OS, uiBuffer_Size_OS ) < uiBuffer_Size_OS)
    {
        if (FAILED(TgOS_TEXT_CONVERT_FCN(tgUSZ_Convert)( s_szSI_System_Dir, uiBuffer_Size_U8 - uiBuffer_U8_Offset_08, pBuffer_OS, uiBuffer_Size_OS )))
        {
            free(pBuffer_OS);
            return (0);
        }
        uiBuffer_U8_Offset_08 += tgUSZ_Length_U08( s_szSI_System_Dir, uiBuffer_Size_U8 - uiBuffer_U8_Offset_08 );
    }

    if (uiBuffer_U8_Offset_08 + 1 >= uiBuffer_Size_U8)
    {
        free(pBuffer_OS);
        return (0);
    }
    pBuffer_U8[uiBuffer_U8_Offset_08] = 0;
    uiBuffer_U8_Offset_08 += 1;

    s_szSI_Window_Dir = pBuffer_U8 + uiBuffer_U8_Offset_08;
    if (g_pfnGetWindowsDirectory( pBuffer_OS, uiBuffer_Size_OS ) < uiBuffer_Size_OS)
    {
        if (FAILED(TgOS_TEXT_CONVERT_FCN(tgUSZ_Convert)( s_szSI_Window_Dir, uiBuffer_Size_U8 - uiBuffer_U8_Offset_08, pBuffer_OS, uiBuffer_Size_OS )))
        {
            free(pBuffer_OS);
            return (0);
        }
        uiBuffer_U8_Offset_08 += tgUSZ_Length_U08( s_szSI_Window_Dir, uiBuffer_Size_U8 - uiBuffer_U8_Offset_08 );
    }

    if (uiBuffer_U8_Offset_08 + 1 >= uiBuffer_Size_U8)
    {
        free(pBuffer_OS);
        return (0);
    }
    pBuffer_U8[uiBuffer_U8_Offset_08] = 0;
    uiBuffer_U8_Offset_08 += 1;
/*# !defined(TgBUILD_UNIVERSAL__UWP) */
#else
    if (uiBuffer_U8_Offset_08 + 1 >= uiBuffer_Size_U8)
    {
        free(pBuffer_OS);
        return (0);
}
    pBuffer_U8[uiBuffer_U8_Offset_08] = 0;
    uiBuffer_U8_Offset_08 += 1;

    if (uiBuffer_U8_Offset_08 + 1 >= uiBuffer_Size_U8)
    {
        free(pBuffer_OS);
        return (0);
    }
    pBuffer_U8[uiBuffer_U8_Offset_08] = 0;
    uiBuffer_U8_Offset_08 += 1;
/*# !defined(TgBUILD_UNIVERSAL__UWP) */
#endif

    s_szSI_Module_Dir = pBuffer_U8 + uiBuffer_U8_Offset_08;
    if (0 != g_pfnGetModuleFileName( nullptr, pBuffer_OS, uiBuffer_Size_OS ))
    {
        if (FAILED(TgOS_TEXT_CONVERT_FCN(tgUSZ_Convert)( s_szSI_Module_Dir, uiBuffer_Size_U8 - uiBuffer_U8_Offset_08, pBuffer_OS, uiBuffer_Size_OS )))
        {
            free(pBuffer_OS);
            return (0);
        }
        uiBuffer_U8_Offset_08 += tgUSZ_Length_U08( s_szSI_Module_Dir, uiBuffer_Size_U8 - uiBuffer_U8_Offset_08 );
    }

    if (uiBuffer_U8_Offset_08 + 1 >= uiBuffer_Size_U8)
    {
        free(pBuffer_OS);
        return (0);
    }
    pBuffer_U8[uiBuffer_U8_Offset_08] = 0;
    uiBuffer_U8_Offset_08 += 1;

#if !defined(TgBUILD_UNIVERSAL__UWP)
    s_szSI_Computer_Name = pBuffer_U8 + uiBuffer_U8_Offset_08;
    dwSize = uiBuffer_Size_OS;
    if (0 != g_pfnGetComputerNameEx( ComputerNameDnsFullyQualified, pBuffer_OS, &dwSize ))
    {
        if (FAILED(TgOS_TEXT_CONVERT_FCN(tgUSZ_Convert)( s_szSI_Computer_Name, uiBuffer_Size_U8 - uiBuffer_U8_Offset_08, pBuffer_OS, uiBuffer_Size_OS )))
        {
            free(pBuffer_OS);
            return (0);
        }
        uiBuffer_U8_Offset_08 += tgUSZ_Length_U08( s_szSI_Computer_Name, uiBuffer_Size_U8 - uiBuffer_U8_Offset_08 );
    }

    if (uiBuffer_U8_Offset_08 + 1 >= uiBuffer_Size_U8)
    {
        free(pBuffer_OS);
        return (0);
    }
    pBuffer_U8[uiBuffer_U8_Offset_08] = 0;
    uiBuffer_U8_Offset_08 += 1;

    s_szSI_User_Name = pBuffer_U8 + uiBuffer_U8_Offset_08;
    dwSize = uiBuffer_Size_OS;
    if (0 != g_pfnGetUserName( pBuffer_OS, &dwSize ))
    {
        if (FAILED(TgOS_TEXT_CONVERT_FCN(tgUSZ_Convert)( s_szSI_User_Name, uiBuffer_Size_U8 - uiBuffer_U8_Offset_08, pBuffer_OS, uiBuffer_Size_OS )))
        {
            free(pBuffer_OS);
            return (0);
        }
        uiBuffer_U8_Offset_08 += tgUSZ_Length_U08( s_szSI_User_Name, uiBuffer_Size_U8 - uiBuffer_U8_Offset_08 );
    }

    if (uiBuffer_U8_Offset_08 + 1 >= uiBuffer_Size_U8)
    {
        free(pBuffer_OS);
        return (0);
    }
    pBuffer_U8[uiBuffer_U8_Offset_08] = 0;
    uiBuffer_U8_Offset_08 += 1;

    if (0 != g_pfnGetCurrentHwProfile( &siHardwareProfile ))
    {
        s_szSI_Hardware_Profile_GUID = pBuffer_U8 + uiBuffer_U8_Offset_08;
        if (FAILED(TgOS_TEXT_CONVERT_FCN(tgUSZ_Convert)(
            s_szSI_Hardware_Profile_GUID, uiBuffer_Size_U8 - uiBuffer_U8_Offset_08, siHardwareProfile.szHwProfileGuid, sizeof( siHardwareProfile.szHwProfileGuid ) )))
        {
            free(pBuffer_OS);
            return (0);
        }
        uiBuffer_U8_Offset_08 += tgUSZ_Length_U08( s_szSI_Hardware_Profile_GUID, uiBuffer_Size_U8 - uiBuffer_U8_Offset_08 );

        if (uiBuffer_U8_Offset_08 + 1 >= uiBuffer_Size_U8)
        {
            free(pBuffer_OS);
            return (0);
        }
        pBuffer_U8[uiBuffer_U8_Offset_08] = 0;
        uiBuffer_U8_Offset_08 += 1;

        s_szSI_Hardware_Profile_Name = pBuffer_U8 + uiBuffer_U8_Offset_08;
        if (FAILED(TgOS_TEXT_CONVERT_FCN(tgUSZ_Convert)(
            s_szSI_Hardware_Profile_Name, uiBuffer_Size_U8 - uiBuffer_U8_Offset_08, siHardwareProfile.szHwProfileName, sizeof( siHardwareProfile.szHwProfileName ) )))
        {
            free(pBuffer_OS);
            return (0);
        }
        uiBuffer_U8_Offset_08 += tgUSZ_Length_U08( s_szSI_Hardware_Profile_Name, uiBuffer_Size_U8 - uiBuffer_U8_Offset_08 );

        if (uiBuffer_U8_Offset_08 + 1 >= uiBuffer_Size_U8)
        {
            free(pBuffer_OS);
            return (0);
        }
        pBuffer_U8[uiBuffer_U8_Offset_08] = 0;
        uiBuffer_U8_Offset_08 += 1;
    }
    else
    {
        s_szSI_Hardware_Profile_GUID = pBuffer_U8 + uiBuffer_U8_Offset_08;
        if (uiBuffer_U8_Offset_08 + 1 >= uiBuffer_Size_U8)
        {
            free(pBuffer_OS);
            return (0);
        }
        pBuffer_U8[uiBuffer_U8_Offset_08] = 0;
        uiBuffer_U8_Offset_08 += 1;

        s_szSI_Hardware_Profile_Name = pBuffer_U8 + uiBuffer_U8_Offset_08;
        if (uiBuffer_U8_Offset_08 + 1 >= uiBuffer_Size_U8)
        {
            free(pBuffer_OS);
            return (0);
        }
        pBuffer_U8[uiBuffer_U8_Offset_08] = 0;
        uiBuffer_U8_Offset_08 += 1;
    };
/*# !defined(TgBUILD_UNIVERSAL__UWP) */
#else
    if (uiBuffer_U8_Offset_08 + 1 >= uiBuffer_Size_U8)
    {
        free(pBuffer_OS);
        return (0);
    }
    pBuffer_U8[uiBuffer_U8_Offset_08] = 0;
    uiBuffer_U8_Offset_08 += 1;

    if (uiBuffer_U8_Offset_08 + 1 >= uiBuffer_Size_U8)
    {
        free(pBuffer_OS);
        return (0);
    }
    pBuffer_U8[uiBuffer_U8_Offset_08] = 0;
    uiBuffer_U8_Offset_08 += 1;

    if (uiBuffer_U8_Offset_08 + 1 >= uiBuffer_Size_U8)
    {
        free(pBuffer_OS);
        return (0);
    }
    pBuffer_U8[uiBuffer_U8_Offset_08] = 0;
    uiBuffer_U8_Offset_08 += 1;

    if (uiBuffer_U8_Offset_08 + 1 >= uiBuffer_Size_U8)
    {
        free(pBuffer_OS);
        return (0);
    }
    pBuffer_U8[uiBuffer_U8_Offset_08] = 0;
    uiBuffer_U8_Offset_08 += 1;
/*# !defined(TgBUILD_UNIVERSAL__UWP) */
#endif

    free(pBuffer_OS);
    return (uiBuffer_U8_Offset_08);
}


/* ---- InitTimer ---------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
MSVC_PRAGMA(optimize("",off))

static TgRESULT Init_Timer( TgVOID )
{
    LARGE_INTEGER                       liFreq, liCycles1, liCycles2;
    TgFLOAT64                           aTimeArray[TIME_MAXITERATIONS];
    TgFLOAT64                           dFrequency;
    TgUINT_F08                          nCount;

    /* Call the timeGetDevCaps function to determine the supported minimum timer resolution and the timeBeginPeriod function */

    if (!MATH_Has_RDTSC())
        return (KTgE_FAIL);

    if (!g_pfnQueryPerformanceFrequency( &liFreq ))
    {
        TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"CPU does not Support RDTSC." );
        return (KTgE_FAIL);
    };

    dFrequency = (TgFLOAT64)liFreq.QuadPart; /* Counts per second */

    for (nCount = 0; nCount < TIME_MAXITERATIONS; nCount++)
    {
        TgFLOAT64                           dSeconds1, dSeconds2;
        TgUINT_F08                          uiIndex;
        TgUINT_F64                          uiStart_Time;

        g_pfnQueryPerformanceCounter( &liCycles1 );

        uiStart_Time = g_pfnGetTickCount64();
        while (g_pfnGetTickCount64() - uiStart_Time < 10)
        {
        };

        g_pfnQueryPerformanceCounter( &liCycles2 );

        dSeconds1 = (TgFLOAT64)liCycles1.QuadPart / dFrequency;
        dSeconds2 = (TgFLOAT64)liCycles2.QuadPart / dFrequency;
        aTimeArray[nCount] = (dSeconds2 - dSeconds1) / (TgFLOAT64)(liCycles2.QuadPart - liCycles1.QuadPart);

        for (uiIndex = 0; uiIndex < nCount - 1; ++uiIndex)
        {
            if (aTimeArray[uiIndex] > aTimeArray[nCount])
            {
                tgCM_SWP_F64( aTimeArray + uiIndex, aTimeArray + nCount );
            };
        };
    }
    s_fSI_Seconds_Per_CounterTick = aTimeArray[(TIME_MAXITERATIONS - 1) / 2];

    return (KTgS_OK);
}
MSVC_PRAGMA(optimize("",on))


CLANG_WARN_DISABLE_PUSH(unused-function)

/* ---- SYSTEM_Set_Mouse --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID SYSTEM_Set_Mouse( TgBOOL_C bFlag )
{
    tgBF_Set_Flag_U32( &s_bfSystemChecks, 0, bFlag );
}


/* ---- SYSTEM_Set_Network ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID SYSTEM_Set_Network( TgBOOL_C bFlag )
{
    tgBF_Set_Flag_U32( &s_bfSystemChecks, 1, bFlag );
}


/* ---- SYSTEM_Set_Clean_Boot ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID SYSTEM_Set_Clean_Boot( TgBOOL_C bFlag )
{
    tgBF_Set_Flag_U32( &s_bfSystemChecks, 6, bFlag );
}


/* ---- SYSTEM_Has_Mouse --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL SYSTEM_Has_Mouse( TgVOID )
{
    return (tgBF_Test_Flag_U32( &s_bfSystemChecks, 0 ));
}


/* ---- SYSTEM_Has_Network ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL SYSTEM_Has_Network( TgVOID )
{
    return (tgBF_Test_Flag_U32( &s_bfSystemChecks, 1 ));
}


/* ---- SYSTEM_Clean_Boot -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL SYSTEM_Clean_Boot( TgVOID )
{
    return (tgBF_Test_Flag_U32( &s_bfSystemChecks, 6 ));
}


/* ---- MATH_Set_MMX ------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID MATH_Set_MMX( TgBOOL_C bFlag )
{
    tgBF_Set_Flag_U32( &s_bfSystemChecks, 2, bFlag );
}


/* ---- MATH_Set_XMM ------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID MATH_Set_XMM( TgBOOL_C bFlag )
{
    tgBF_Set_Flag_U32( &s_bfSystemChecks, 3, bFlag );
}


/* ---- MATH_Set_XMM2 ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID MATH_Set_XMM2( TgBOOL_C bFlag )
{
    tgBF_Set_Flag_U32( &s_bfSystemChecks, 7, bFlag );
}


/* ---- MATH_Set_3DNow ----------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID MATH_Set_3DNow( TgBOOL_C bFlag )
{
    tgBF_Set_Flag_U32( &s_bfSystemChecks, 4, bFlag );
}


/* ---- MATH_Set_RDTSC ----------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID MATH_Set_RDTSC( TgBOOL_C bFlag )
{
    tgBF_Set_Flag_U32( &s_bfSystemChecks, 5, bFlag );
}


/* ---- MATH_Has_MMX ------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL MATH_Has_MMX( TgVOID )
{
    return (tgBF_Test_Flag_U32( &s_bfSystemChecks, 2 ));
}


/* ---- MATH_Has_XMM ------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL MATH_Has_XMM( TgVOID )
{
    return (tgBF_Test_Flag_U32( &s_bfSystemChecks, 3 ));
}


/* ---- MATH_Has_XMM2 ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL MATH_Has_XMM2( TgVOID )
{
    return (tgBF_Test_Flag_U32( &s_bfSystemChecks, 7 ));
}


/* ---- MATH_Has_3DNow ----------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL MATH_Has_3DNow( TgVOID )
{
    return (tgBF_Test_Flag_U32( &s_bfSystemChecks, 4 ));
}


/* ---- MATH_Has_RDTSC ----------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL MATH_Has_RDTSC( TgVOID )
{
    return (tgBF_Test_Flag_U32( &s_bfSystemChecks, 5 ));
}


/* ---- INPUT_Set_Mouse_Wheel ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID INPUT_Set_Mouse_Wheel( TgBOOL_C bFlag )
{
    tgBF_Set_Flag_U32( &s_bfInputChecks, 0, bFlag );
}
CLANG_WARN_DISABLE_POP(unused-function)


/* Console Functions */
#if TgCOMPILE__CONSOLE
/* ---- SI_CO_Print_Configuration ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgNOTHROW TgVOID SI_CO_Print_Configuration( TgUINT_F32_C UNUSED_PARAM nuiArg, TgCHAR_U8_CP UNUSED_PARAM pArgV[KTgMAX_CMD_LINE_COUNT] )
{
    tgSI_Print_Configuration( &g_sOutCon );
}
/*# TgCOMPILE__CONSOLE */
#endif


/* ---- SI_CO_Print_Modules ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if TgCOMPILE__CONSOLE
static TgNOTHROW TgVOID SI_CO_Print_Modules( TgUINT_F32_C UNUSED_PARAM nuiArg, TgCHAR_U8_CP UNUSED_PARAM pArgV[KTgMAX_CMD_LINE_COUNT] )
{
#if !defined(TgBUILD_UNIVERSAL__UWP)
    tgSI_Print_Modules( &g_sOutCon );
/*# !defined(TgBUILD_UNIVERSAL__UWP) */
#endif
}
/*# TgCOMPILE__CONSOLE */
#endif


/* ---- SI_CO_Print_Threads ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if TgCOMPILE__CONSOLE
static TgNOTHROW TgVOID SI_CO_Print_Threads( TgUINT_F32_C UNUSED_PARAM nuiArg, TgCHAR_U8_CP UNUSED_PARAM pArgV[KTgMAX_CMD_LINE_COUNT] )
{
#if !defined(TgBUILD_UNIVERSAL__UWP)
    tgTR_Print_Threads( &g_sOutCon );
/*# !defined(TgBUILD_UNIVERSAL__UWP) */
#endif
}
/*# TgCOMPILE__CONSOLE */
#endif
