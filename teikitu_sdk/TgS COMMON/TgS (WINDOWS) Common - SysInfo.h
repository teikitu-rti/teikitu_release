/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (WINDOWS) Common - SysInfo.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_WINDOWS_COMMON_SYSINFO_H)
#define TGS_WINDOWS_COMMON_SYSINFO_H
#pragma once


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @brief Standard function: First part of initialization process.
    @return Result Code. */
TgEXTN TgRESULT
tgSI_Init( TgVOID );

/** @brief Standard function: Last part of initialization process. Used for setup and other necessary tasks prior to the use of the system information.
    @return Result Code. */
TgEXTN TgRESULT
tgSI_Boot( TgVOID );

/** @brief Standard function: Used as part of the shutdown process. System information may not be valid after this is executed.
    @return Result Code. */
TgEXTN TgRESULT
tgSI_Stop( TgVOID );

/** @brief Standard function: Final part of shutdown process. Release any remaining allocated memory, and reset state.
    @return Result Code. */
TgEXTN TgRESULT
tgSI_Free( TgVOID );


/** @brief Standard function: State query to determine if the system information is in the initialized or booted state.
    @return True if the module has been initialized, and false otherwise. */
TgEXTN TgBOOL
tgSI_Query_Init( TgVOID );

/** @brief Standard function: State query to determine if the system information is in a booted state.
    @return True if the module has been initialized and booted, and false otherwise. */
TgEXTN TgBOOL
tgSI_Query_Boot( TgVOID );


/** @brief Standard function: Recall the amount of global (static) memory used by system information.
    @return Amount of global (static) memory used by system information. This is hard coded and thus, not explicitly correct. */
TgEXTN TgRSIZE
    tgSI_Query_Fixed_Memory( TgVOID );


/** @brief Standard function: Output stat information related to system information. 
    @param [in,out] OUT0 Pointer to output structure used for writing. */
TgEXTN TgVOID
tgSI_Stats(
    STg2_Output_P OUT0 );


/** @brief Determine if a mouse can be used by the application.
    @return True if a mouse can be  used by the application, and false otherwise. */
TgEXTN TgBOOL
tgSI_SYSTEM_Has_Mouse( TgVOID );

/** @brief Determine if the hardware is a normal (standard) boot state.
    @return True if the OS was booted through the default (normal) process, and false otherwise. */
TgEXTN TgBOOL
tgSI_SYSTEM_Clean_Boot( TgVOID );

/** @brief OS Function to convert between seconds and CPU ticks.
    @return Float of the number of seconds per CPU tick. */
TgEXTN TgFLOAT64
tgSI_SYSTEM_Seconds_Per_CounterTick( TgVOID );

/** @brief Determine the number of bytes in the default (standard) memory page of the OS memory manager.
    @return Integer holding the number of bytes in the default (standard) memory page of the OS memory manager. */
TgEXTN TgUINT_E32
tgSI_SYSTEM_Page_Size( TgVOID );

/** @brief Determine the minimum number of bytes allocated by the OS allocator.
    @return Integer holding the minimum number of bytes allocated by the OS allocator. */
TgEXTN TgUINT_E32
tgSI_SYSTEM_Allocation_Granularity( TgVOID );

/** @brief Determine the number of processors directly available on the local hardware that can be used by the application.
    @return Integer representing the number of processors directly available on the local hardware that can be used by the application. */
TgEXTN TgUINT_E32
tgSI_SYSTEM_Number_Of_Processors( TgVOID );


/** @brief Determine if the available hardware supports the MMX instruction set.
    @return True if MMX is supported, FALSE otherwise. */
TgEXTN TgBOOL
tgSI_MATH_Has_MMX( TgVOID );

/** @brief Determine if the available hardware supports the XMM instruction set.
    @return True if XMM is supported, FALSE otherwise. */
TgEXTN TgBOOL
tgSI_MATH_Has_XMM( TgVOID );

/** @brief Determine if the available hardware supports the XMM2 instruction set.
    @return True if XMM2 is supported, FALSE otherwise. */
TgEXTN TgBOOL
tgSI_MATH_Has_XMM2( TgVOID );

/** @brief Determine if the available hardware supports the 3DNOW instruction set.
    @return True if 3DNOW is supported, FALSE otherwise. */
TgEXTN TgBOOL
tgSI_MATH_Has_3DNow( TgVOID );

/** @brief Determine if the application can use the RDTSC instruction.
    @return True if the RDTSC instruction can be used, and FALSE otherwise.*/
TgEXTN TgBOOL
tgSI_MATH_Has_RDTSC( TgVOID );


/** @brief Determine if a mouse wheel can be used by the application.
    @return True if a mouse wheel can be used by  the application, and false otherwise. */
TgEXTN TgBOOL
tgSI_INPUT_Has_Mouse_Wheel( TgVOID );


/** @brief Determine if the application is in a remote session.
    @return True if the application is in a remote session, and false otherwise. */
TgEXTN TgBOOL
tgSI_APP_Is_Remote_Session( TgVOID );


/** @brief Determine the local working path of the application.
    @return Pointer to a string holding the local working path of the application. */
TgEXTN TgCHAR_U8_CP
tgSI_Query_WorkPath( TgVOID );

/** @brief Determine the local system path.
    @return Pointer to a string holding the local system path. */
TgEXTN TgCHAR_U8_CP
tgSI_Query_SysPath( TgVOID );

/** @brief Determine the local windows (os) path.
    @return Pointer to a string holding the local windows (os) path. */
TgEXTN TgCHAR_U8_CP
tgSI_Query_WinPath( TgVOID );

/** @brief Determine the full path of the executable file of the application.
    @return Pointer to a string holding the full path of the executable file of the application. */
TgEXTN TgCHAR_U8_CP
tgSI_Query_ExePath( TgVOID );


/** @brief Determine the name of the local computer.
    @return Pointer to a string holding the name of the computer. */
TgEXTN TgCHAR_U8_CP
tgSI_Query_Computer_Name( TgVOID );

/** @brief Determine the name of the active user.
    @return Pointer to a string holding the name of the current (active) user. */
TgEXTN TgCHAR_U8_CP
tgSI_Query_User_Name( TgVOID );

/** @brief Determine if the local computer has a network connection that is accessible by the application.
    @return True if the local computer has a network connection that is accessible by the application, and false otherwise. */
TgEXTN TgBOOL
tgSI_SYSTEM_Has_Network( TgVOID );

/** @brief Output the current configuration of the system information.
    @param [in,out] ARG0 Pointer to output structure used for writing. */
TgEXTN TgVOID
tgSI_Print_Configuration(
    STg2_Output_P ARG0 );


#if !defined(TgBUILD_UNIVERSAL__UWP)

/** @brief Output all of the loaded modules (DLLs) being used by the application.
    @param [in,out] ARG0 Pointer to output structure used for writing. */
TgEXTN TgVOID
tgSI_Print_Modules(
    STg2_Output_P ARG0 );

/*# !defined(TgBUILD_UNIVERSAL__UWP) */
#endif


/* =============================================================================================================================================================================== */
#endif
