/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Global.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_GLOBAL_H)
#define TGS_COMMON_GLOBAL_H
#pragma once


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  DOXYGEN                                                                                                                                                                        */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @defgroup TGS_COMMON_GLOBAL Global
    @ingroup TGS_COMMON_COMMON
*/

    /** @defgroup TGS_COMMON_GLOBAL_MODULE Module Functions
        @ingroup TGS_COMMON_GLOBAL
    */


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Constants                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

enum { KTgMAX_CMD_LINE_COUNT                = 64 };
enum { KTgMAX_CMD_LINE_SIZE                 = 512 };


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @addtogroup TGS_COMMON_GLOBAL_MODULE */
/** @{ */

/** @brief Standard Module function: First part of initialization process. Set the state of the module.
    @return Result Code. */
TgEXTN TgRESULT
tgGB_Init( TgVOID );

/** @brief Standard Module function: Last part of initialization process. Used for setup and other necessary tasks prior to the use of the module.
    @return Result Code. */
TgEXTN TgRESULT
tgGB_Boot( TgVOID );

/** @brief Standard Module function: Used for close the module as part of the shutdown process. Module is not to be used after this is executed. */
TgEXTN TgVOID
tgGB_Stop( TgVOID );

/** @brief Standard Module function: Final part of shutdown process. Release any remaining allocated memory, and reset the state of the module. */
TgEXTN TgVOID
tgGB_Free( TgVOID );

/** @brief Standard Module function: Update the module, usually called on a per-frame basis, where the parameter is the forward time step amount.
    @param[in] ARG0 Amount of time to step forward the module in milliseconds
    @return Result Code. */
TgEXTN TgRESULT
tgGB_Update(
    TgFLOAT32_C ARG0 );

/** @brief Standard Module function: State query to determine if the module is in the initialized or booted state
    @return True if the module has been initialized, and false otherwise. */
TgEXTN TgBOOL
tgGB_Query_Init( TgVOID );

/** @brief Standard Module function: State query to determine if the module has been booted state
    @return True if the module has been initialized and booted, and false otherwise. */
TgEXTN TgBOOL
tgGB_Query_Boot( TgVOID );

/** @brief Standard Module function: Recall the amount of global (static) memory used by the module
    @return Amount of global (static) memory used by the module. This is hard coded and thus, not explicitly correct. */
TgEXTN TgRSIZE
tgGB_Query_Fixed_Memory( TgVOID );


/** @brief First part of operating system level initialization process.
    @return Result Code. */
TgEXTN TgRESULT
tgGB_Init_OS( TgVOID );

/** @brief Second part of operating system level initialization process.
    @return Result Code. */
TgEXTN TgRESULT
tgGB_Boot_OS( TgVOID );

/** @brief Used for closing operating system resources as part of the shutdown process. */
TgEXTN TgVOID
tgGB_Stop_OS( TgVOID );

/** @brief Final part of the operating system shutdown process. */
TgEXTN TgVOID
tgGB_Free_OS( TgVOID );


#if TgS_STAT__COMMON

/** @brief Standard Module function: Output relevant stats for the module.
    @param [in,out] OUT0 Pointer to an output object */
TgEXTN TgVOID
tgGB_Stats(
    STg2_Output_P OUT0 );

#endif

/** @} TGS_COMMON_GLOBAL_MODULE */


/** @addtogroup TGS_COMMON_GLOBAL */
/** @{ */

/** @brief Output an unique name into ARG0
    @param [out] OUT0 Destination String
    @param [in] ARG1 Maximum size in bytes of the string at ARG0
    @return True if the function was successful and false otherwise */
TgEXTN TgBOOL
tgGB_Get_Unique_Name(
    TgCHAR_U8_PCU OUT0, TgUINT_E32_C ARG1 );


/** @brief Parse the provided string as if it was the command line
    @param [out] OUT0 Destination for the argument list
    @param [in] ARG1 Maximum number of arguments that ARG0 can contain
    @param [in] ARG2 Source string for processing */
TgEXTN TgUINT_E32
tgGB_Parse_Command_Line(
    TgCHAR_U8_CPP OUT0, TgRSIZE_C ARG1, TgCHAR_U8_PC ARG2 );

/** @brief Copy the command line from the OS to the module for processing and use
    @param [in] ARG String containing the command line */
TgEXTN TgVOID
tgGB_CMD_Set_Command_Line(
    TgCHAR_U8_CPCU ARG );

/** @brief Return the number of arguments on the command line
    @return The number of arguments on the command line */
TgEXTN TgSINT_E32
tgGB_CMD_Query_Argument_Count( TgVOID );

/** @brief Return the argument at the given index
    @param [in] ARG Argument Index
    @return The argument at the given index */
TgEXTN TgCHAR_U8_CP
tgGB_CMD_Query_Argument(
    TgSINT_E32_C ARG );

/** @brief Return index of the given argument (returning the first occurrence)
    @param [in] ARG String containing the argument to search for in the command line
    @return The index of the given argument (returning the first occurrence) */
TgEXTN TgSINT_E32
tgGB_CMD_Query_Argument_Index(
    TgCHAR_U8_CPC ARG );

/** @brief Add new arguments to the internal copy of the command line
    @param [in] ARG String containing the new argument(s) to be added to the internal command line */
TgEXTN TgVOID
tgGB_CMD_Push_Argument(
    TgCHAR_U8_CPC ARG );


/** @brief Reset the accumulated reported time since execution start or last reset */
TgEXTN TgVOID
tgGB_Reset_Frame_Time( TgVOID );

/** @brief Force the internal  time tracker to a specific value
    @param [in] ARG Time Value */
TgEXTN TgVOID
tgGB_Set_Frame_Time(
    TgFLOAT32_C ARG );

/** @brief Increment the internal time tracker by a specific amount
    @param [in] ARG Time Value */
TgEXTN TgVOID
tgGB_Inc_Frame_Time(
    TgFLOAT32_C ARG );

/** @brief Validate if the version of the argument matches the version at compile time
    @param [in] ARG Version
    @return true if the argument version matches the compile time version and false otherwise */
TgEXTN TgBOOL
tgGB_Verify_Version(
    TgUINT_E32_C ARG );


/** @brief Return the current time associated with the current frame
    @return The current time associated with the current frame */
TgEXTN TgFLOAT32
tgGB_Query_Frame_Time( TgVOID );

/** @brief Return the total time spent in active frames
    @return Total time spent in active frames */
TgEXTN TgSINT_E32
tgGB_Query_Total_Frame( TgVOID );

/** @brief Return the total time spent since application start
    @return Total time spent since application start */
TgEXTN TgFLOAT32
tgGB_Query_Total_Time( TgVOID );

/** @brief Determine if the current application is running as a client
    @return True if the current application is considered to be a client and false otherwise */
TgEXTN TgBOOL
tgGB_Query_Client( TgVOID );

/** @brief Determine if the current application is running as a server
    @return True if the current application is considered to be a server and false otherwise */
TgEXTN TgBOOL
tgGB_Query_Server( TgVOID );

/** @brief Determine if the current hardware platform is considered to be a console (embedded device)
    @return True if the current hardware platform is considered to be a console (embedded device) and false otherwise */
TgEXTN TgBOOL
tgGB_Query_Console_HW( TgVOID );

/** @brief Determine how allocated resources will be treated on application exit
    @return True when all resources reserved by the platform will be freed on application exit and false otherwise */
TgEXTN TgBOOL
tgGB_Query_Free_On_Quit( TgVOID );

/** @} TGS_COMMON_GLOBAL */

/* Flag functions - the set version should only be used by the internal engine code.  Calling these within the game code will most likely break the engine processes and */
/* cause catastrophic failure. */

/** @brief Used to set the intended application usage as a client
    @param [in] ARG Boolean Flag */
TgEXTN TgVOID
tgGB_Set_Client(
    TgBOOL_C ARG );

/** @brief Used to set the intended application usage as a server
    @param [in] ARG Boolean Flag */
TgEXTN TgVOID
tgGB_Set_Server(
    TgBOOL_C ARG );

/** @brief Used to set the current hardware as being a console (embedded device)
    @param [in] ARG Boolean Flag */
TgEXTN TgVOID
tgGB_Set_Console_HW(
    TgBOOL_C ARG );

/** @brief Used to tell the platform to free all reserved resources on application exist
    @param [in] ARG Boolean Flag */
TgEXTN TgVOID
tgGB_Set_Free_On_Quit(
    TgBOOL_C ARG );


/* =============================================================================================================================================================================== */
#endif
