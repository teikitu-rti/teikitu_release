/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Console.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_CONSOLE_H)
#define TGS_COMMON_CONSOLE_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  DOXYGEN                                                                                                                                                                        */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @defgroup TGS_COMMON_CONSOLE Console
    @ingroup TGS_COMMON_COMMON
*/

    /** @defgroup TGS_COMMON_CONSOLE_MODULE Module Functions
        @ingroup TGS_COMMON_CONSOLE
    */


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Constants                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#if TgCOMPILE__CONSOLE

/* There are twenty-eight (28) console channels.  The first twelve (12) are system reserved (the below enumeration).  The remaining sixteen (16) are available to the user and can
   be assigned arbitrarily.  The first four bits are used to indicate the severity of the output (may only be valid for certain channels). */

enum { KTgCN_SEVERITY_BITS                      = 4 }; /**< Number of bits used to describe message severity (0-15) */
enum { KTgCN_CHANEL_BITS                        = 32 - KTgCN_SEVERITY_BITS }; /**< The remaining bits are used for the channel */

typedef enum TgATTRIBUTE_ENUM_FLAG
{
    KTgCN_SEVERITY_0                         = 0x0, /**< Highest severity (last to be filtered) */
    KTgCN_SEVERITY_1                         = 0x1,
    KTgCN_SEVERITY_2                         = 0x2,
    KTgCN_SEVERITY_3                         = 0x3,
    KTgCN_SEVERITY_4                         = 0x4,
    KTgCN_SEVERITY_5                         = 0x5,
    KTgCN_SEVERITY_6                         = 0x6,
    KTgCN_SEVERITY_7                         = 0x7,
    KTgCN_SEVERITY_8                         = 0x8,
    KTgCN_SEVERITY_9                         = 0x9,
    KTgCN_SEVERITY_A                         = 0xA,
    KTgCN_SEVERITY_B                         = 0xB,
    KTgCN_SEVERITY_C                         = 0xC,
    KTgCN_SEVERITY_D                         = 0xD,
    KTgCN_SEVERITY_E                         = 0xE,
    KTgCN_SEVERITY_F                         = 0xF,
    KTgCN_MAX_SEVERITY                       = 0xF, /**< (1 << KTgCN_SEVERITY_BITS) - 3 */
    KTgCN_SEVERITY_MASK                      = 0xF, /**< (1 << KTgCN_SEVERITY_BITS) - 1 */

    KTgCN_CHANEL_CONSOLE_INDEX              = 4,
    KTgCN_CHANEL_LOG_SCREEN_INDEX           = 5,
    KTgCN_CHANEL_LOG_INDEX                  = 6,
    KTgCN_CHANEL_LOG_FCN_INDEX              = 7,
    KTgCN_CHANEL_LOG_MEM_INDEX              = 8,
    KTgCN_CHANEL_MESSAGE_INDEX              = 9,
    KTgCN_CHANEL_WARNING_INDEX              = 10,
    KTgCN_CHANEL_ERROR_INDEX                = 11,
    KTgCN_CHANEL_CRITICAL_INDEX             = 12,
    KTgCN_CHANEL_INITIALIZE_INDEX           = 13,
    KTgCN_CHANEL_INITIALIZE_MEMORY_INDEX    = 14,
    KTgCN_CHANEL_LOADING_INDEX              = 15,
    KTgCN_CHANEL_USER_INDEX                 = 16,

    KTgCN_CHANEL_CONSOLE                     = 1 << KTgCN_CHANEL_CONSOLE_INDEX,
    KTgCN_CHANEL_LOG_SCREEN                  = 1 << KTgCN_CHANEL_LOG_SCREEN_INDEX,
    KTgCN_CHANEL_LOG                         = 1 << KTgCN_CHANEL_LOG_INDEX,
    KTgCN_CHANEL_LOG_FCN                     = 1 << KTgCN_CHANEL_LOG_FCN_INDEX,
    KTgCN_CHANEL_LOG_MEM                     = 1 << KTgCN_CHANEL_LOG_MEM_INDEX,
    KTgCN_CHANEL_MESSAGE                     = 1 << KTgCN_CHANEL_MESSAGE_INDEX,
    KTgCN_CHANEL_WARNING                     = 1 << KTgCN_CHANEL_WARNING_INDEX,
    KTgCN_CHANEL_ERROR                       = 1 << KTgCN_CHANEL_ERROR_INDEX,
    KTgCN_CHANEL_CRITICAL                    = 1 << KTgCN_CHANEL_CRITICAL_INDEX,
    KTgCN_CHANEL_INITIALIZE                  = 1 << KTgCN_CHANEL_INITIALIZE_INDEX,
    KTgCN_CHANEL_INITIALIZE_MEMORY           = 1 << KTgCN_CHANEL_INITIALIZE_MEMORY_INDEX,
    KTgCN_CHANEL_LOADING                     = 1 << KTgCN_CHANEL_LOADING_INDEX,
    KTgCN_CHANEL_USER                        = 1 << KTgCN_CHANEL_USER_INDEX, 
} KTgCN_CHANEL_SEVERITY;
TgTYPE_MODIFIER_DEFAULT(KTgCN_CHANEL_SEVERITY);

enum { KTgCN_OSCON_LINE_LENGTH                  = 512, /**< Maximum length of a console command | buffer | display line */
       KTgCN_OSCON_MAX_LINE                     = 256, /**< Number of console lines retained in the buffer */
       KTgCN_OSLOG_LINE_LENGTH                  = 128, /**< Maximum length of an on screen log line */
       KTgCN_OSLOG_MAX_LINE                     =  52, /**< Number of on screen log lines */
};

/*# TgCOMPILE__CONSOLE */
#endif


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Types                                                                                                                                                                   */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#if TgCOMPILE__CONSOLE

typedef TgVOID( *TgFCN_CONSOLE )( TgUINT_E32_C nuiArg, TgCHAR_U8_CP pArgV[KTgMAX_CMD_LINE_COUNT] );
TgTYPE_MODIFIER_DEFAULT( TgFCN_CONSOLE );
typedef TgVOID( *TgFCN_RENDER_CONSOLE )( KTgCN_CHANEL_SEVERITY_C, TgCHAR_U8_PP, TgRSIZE, TgRSIZE );
TgTYPE_MODIFIER_DEFAULT( TgFCN_RENDER_CONSOLE );

/*# TgCOMPILE__CONSOLE */
#endif


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Macro Definitions                                                                                                                                                              */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
#if TgCOMPILE__CONSOLE

#define TgLOG_MEM( ... )                                                                    \
if (tgCN_Query_Boot())                                                                      \
{                                                                                           \
    tgCN_PrintF( KTgCN_CHANEL_LOG_MEM, STD_MSG_PREFIX, STD_MSG_POST);                       \
    tgCN_PrintF( KTgCN_CHANEL_LOG_MEM, __VA_ARGS__ );                                       \
}

/*# TgCOMPILE__CONSOLE */
#else

#define TgLOG_MEM( A, ... )
#define tgCN_Print(...)
#define tgCN_PrintPrefix(...)
#define tgCN_PrintF(...)
#define tgCN_PrintPrefixF(...)
#define tgCN_UID_PrintF(...)
#define tgCN_UID_Print(...)
#define tgCN_Attach_Default_Break(...)
#define tgCN_Remove_Default_Break(...) 0
#define tgCN_Set_Severity_Filter(...) 0
#define tgCN_OS_Process_Input(...)
#define tgCN_Insert_Command_Function(...)
#define tgCN_Remove_Command_Function(...)

/*# TgCOMPILE__CONSOLE */
#endif


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @addtogroup TGS_COMMON_CONSOLE_MODULE */
/** @{ */

/** @brief Standard Module function: First part of initialization process. Set the state of the module.
    @return Result Code. */
TgEXTN TgRESULT
tgCN_Init( TgVOID );

/** @brief Standard Module function: Last part of initialization process. Used for setup and other necessary tasks prior to the use of the module.
    @return Result Code. */
TgEXTN TgRESULT
tgCN_Boot( TgVOID );

/** @brief Standard Module function: Used for close the module as part of the shutdown process. Module is not to be used after this is executed. */
TgEXTN TgVOID
tgCN_Stop( TgVOID );

/** @brief Standard Module function: Final part of shutdown process. Release any remaining allocated memory, and reset the state of the module. */
TgEXTN TgVOID
tgCN_Free( TgVOID );

/** @brief Standard Module function: Update the module, usually called on a per-frame basis, where the parameter is the forward time step amount.
    @param[in] ARG0 Amount of time to step forward the module in milliseconds
    @return Result Code. */
TgEXTN TgRESULT
tgCN_Update(
    TgFLOAT32_C ARG0 );


/** @brief Standard Module function: State query to determine if the module is in the initialized or booted state
    @return True if the module has been initialized, and false otherwise. */
TgEXTN TgBOOL
tgCN_Query_Init( TgVOID );

/** @brief Standard Module function: State query to determine if the module has been booted state
    @return True if the module has been initialized and booted, and false otherwise. */
TgEXTN TgBOOL
tgCN_Query_Boot( TgVOID );

/** @brief Standard Module function: Recall the amount of global (static) memory used by the module
    @return Amount of global (static) memory used by the module. This is hard coded and thus, not explicitly correct. */
TgEXTN TgRSIZE
tgCN_Query_Fixed_Memory( TgVOID );

/** @} TGS_COMMON_CONSOLE_MODULE */


/** @addtogroup TGS_COMMON_CONSOLE */
/** @{ */

/** @brief Print all command functions and console variables through the output object at ARG
    @param [in] ARG Pointer to an output object */
TgEXTN TgVOID
tgCN_Print_Commands(
    STg2_Output_P TgANALYSIS_NO_NULL ARG );

/** @brief Execute the given command
    @param [in] ARG0 Command line to execute (command and associated parameters)
    @param [in] ARG1 Size in bytes of the buffer at ARG0 */
TgEXTN TgBOOL
tgCN_Execute_Command(
    TgCHAR_U8_CPC TgANALYSIS_NO_NULL ARG0, TgRSIZE_C ARG1 );

#if TgCOMPILE__CONSOLE

/** @brief Add the output object at ARG1 to the channels with a set bit in ARG0
    @note Console output works like a stack. The last output object attached to a channel is the first one to receive the data stream.
            No output object should filter data to the next object in the stack. Thus, order does not matter when adding stream objects.
    @param [in] ARG0 Channel mask
    @param [in] ARG1 Pointer to output object
    @return Value is channel mask of succeeded attaches */
TgEXTN TgUINT_E32
tgCN_Attach_Output(
    TgUINT_E32_C ARG0, STg2_Output_PC TgANALYSIS_NO_NULL ARG1 );

/** @brief Add a function that will cause an execution "break" when called to the channels with a set bit in ARG0.
    @param [in] ARG0 Channel mask
    @return Value is channel mask of succeeded attaches */
TgEXTN TgUINT_E32
tgCN_Attach_Default_Break(
    TgUINT_E32_C ARG0 );

/** @brief Add a function that will cause an execution "abort" when called to the channels with a set bit in ARG0.
    @param [in] ARG0 Channel mask
    @return Value is channel mask of succeeded attaches */
TgEXTN TgUINT_E32
tgCN_Attach_Default_Abort(
    TgUINT_E32_C ARG0 );

/** @brief Remove the output object at ARG1 from the channels with a set bit in ARG0
    @param [in] ARG0 Channel mask
    @param [in] ARG1 Pointer to output object
    @return Value is channel mask of succeeded removes */
TgEXTN TgUINT_E32
tgCN_Remove_Output(
    TgUINT_E32_C ARG0, STg2_Output_PC TgANALYSIS_NO_NULL ARG1 );

/** @brief Remove a function that causes an execution "break" from the channels with a set bit in ARG0.
    @param [in] ARG0 Channel mask
    @return Value is channel mask of succeeded removes */
TgEXTN TgUINT_E32
tgCN_Remove_Default_Break(
    TgUINT_E32_C ARG0 );

/** @brief Remove a function that causes an execution "abort" from the channels with a set bit in ARG0.
    @param [in] ARG0 Channel mask
    @return Value is channel mask of succeeded removes */
TgEXTN TgUINT_E32
tgCN_Remove_Default_Abort(
    TgUINT_E32_C ARG0 );


/** @brief The string must remain valid for as long as the channel is being used.
    @param [in] ARG0 Channel index
    @param [in] ARG1 Pointer to a string to be used as a prefix for all output on the given index
    @param [in] ARG2 Size in bytes of the buffer at ARG1 */
TgEXTN TgVOID
tgCN_Set_Prefix(
    TgUINT_E32_C ARG0, TgCHAR_U8_CPC ARG1, TgRSIZE_C ARG2 );

/** @brief Limit output to a specific literal (class | system).
    @param [in] ARG0 Channel mask (the set of channels the filter will be set).
    @param [in] ARG1 UID to filter out. */
TgEXTN TgVOID
tgCN_Set_UID_Filter(
    TgUINT_E32_C ARG0, TgSINT_E32_C ARG1 );

/** @brief Limit the output to a specific severity level or lower.
    @param [in] ARG0 Channel mask
    @param [in] ARG1 Integer representing the first severity level to filter out.
    @return Previous severity level, or MAX otherwise. */
TgEXTN TgUINT_E32
tgCN_Set_Severity_Filter(
    TgUINT_E32_C ARG0, TgUINT_E32_C ARG1 );


/** @brief Output the argument string to the given channel
    @param [in] ARG0 A severity-channel(s) value
    @param [in] ARG1 String literal to output
    @param [in] ARG2 Maximum number of bytes in ARG1 */
TgEXTN TgVOID
tgCN_Print(
    TgUINT_E32_C ARG0, TgCHAR_U8_CP TgANALYSIS_NO_NULL ARG1, TgRSIZE_C ARG2 );

/** @brief Output the argument string to the given channel
    @param [in] ARG0 A severity-channel(s) value
    @param [in] ARG1 String literal used to prefix every output line
    @param [in] ARG2 String literal to output
    @param [in] ARG3 Maximum number of bytes in ARG2 */
TgEXTN TgVOID
tgCN_PrintPrefix(
    TgUINT_E32_C ARG0, TgCHAR_U8_CP TgANALYSIS_NO_NULL ARG1, TgCHAR_U8_CP TgANALYSIS_NO_NULL ARG2, TgRSIZE_C ARG3 );

/** @brief Output the printf formatted string to the given channel
    @param [in] ARG0 A severity-channel(s) value
    @param [in] ARG1 String literal to output
    @param [in] ... Optional list of arguments for use in ARG1 printf processing */
TgEXTN TgVOID CDECL
tgCN_PrintF(
    TgUINT_E32_C ARG0, TgCHAR_U8_CP TgANALYSIS_NO_NULL ARG1, ... );

/** @brief Output the printf formatted string to the given channel
    @param [in] ARG0 A severity-channel(s) value
    @param [in] ARG1 String literal used to prefix every output line
    @param [in] ARG2 String literal to output
    @param [in] ... Optional list of arguments for use in ARG1 printf processing */
TgEXTN TgVOID CDECL
tgCN_PrintPrefixF(
    TgUINT_E32_C ARG0, TgCHAR_U8_CP TgANALYSIS_NO_NULL ARG1, TgCHAR_U8_CP TgANALYSIS_NO_NULL ARG2, ... );

/** @brief Output the argument string for the given UID to the given channel
    @param [in] ARG0 UID to associate with this function call
    @param [in] ARG1 Channel mask
    @param [in] ARG2 String literal to output
    @param [in] ARG3 Maximum number of bytes in ARG1 */
TgEXTN TgVOID
tgCN_UID_Print(
    TgSINT_E32_C ARG0, TgUINT_E32_C ARG1, TgCHAR_U8_CP TgANALYSIS_NO_NULL ARG2, TgRSIZE_C ARG3 );

/** @brief Output the printf formatted string for the given to the given channel
    @param [in] ARG0 UID to associate with this function call
    @param [in] ARG1 Channel mask
    @param [in] ARG2 String literal to output
    @param [in] ... Optional list of arguments for use in ARG1 printf processing */
TgEXTN TgVOID
tgCN_UID_PrintF(
    TgSINT_E32_C ARG0, TgUINT_E32_C ARG1, TgCHAR_U8_CP TgANALYSIS_NO_NULL ARG2, ... );


/** @brief This will process input for the console display
    @param [in] ARG0 Character to be processed
    @param [in] ARG1 True if ctrl is being held down */
TgEXTN TgVOID
tgCN_OS_Process_Input(
    TgUINT_E64 ARG0, TgBOOL ARG1 );


/** @brief Add a new console command (function)
    @param [in] ARG0 String with the command keyword to be associated with this function
    @param [in] ARG1 Maximum number of bytes at ARG0
    @param [in] ARG2 Console command function
    @param [in] ARG3 String with a description of the command (used in help text)
    @param [in] ARG4 Maximum number of bytes at ARG3
    @return True on success and false otherwise */
TgEXTN TgBOOL
tgCN_Insert_Command_Function(
    TgCHAR_U8_CPC ARG0, TgRSIZE ARG1, TgFCN_CONSOLE ARG2, TgCHAR_U8_CPC TgANALYSIS_NO_NULL ARG3, TgRSIZE_C ARG4 );

/** @brief Remove a console command (function)
    @param [in] ARG0 String with the command keyword to remove
    @param [in] ARG1 Maximum number of bytes at ARG0
    @return True on success and false otherwise */
TgEXTN TgBOOL
tgCN_Remove_Command_Function(
    TgCHAR_U8_CPC TgANALYSIS_NO_NULL ARG0, TgRSIZE ARG1 );

/** @brief Print all registered command keywords
    @param [in,out] ARG Pointer to an output object */
TgEXTN TgVOID
tgCN_Print_Command_Functions(
    STg2_Output_P TgANALYSIS_NO_NULL ARG );

/** @brief Register the render function for the on-screen log and debug console. */
TgEXTN TgVOID
tgCN_Register_Render_Callback(
    TgFCN_RENDER_CONSOLE TgANALYSIS_OK_NULL ARG0 );

/*  @brief Helper function for creating Console Commands. Accepts command to set the value
    @param [out] OUT0
    @param [in] ARG1
    @param [in] ARG2
    @param [in] ARG3 */
TgEXTN TgVOID
tgRN_CN_Helper__Bool_Command(
    TgBOOL_PC TgANALYSIS_NO_NULL OUT0, TgUINT_E32_C ARG1, TgCHAR_U8_CPC ARG2[], TgCHAR_U8_CPCU TgANALYSIS_NO_NULL ARG3 );

/*  @brief Helper function for creating Console Commands. Accepts command to set the value
    @param [out] OUT0
    @param [out] OUT1
    @param [in] ARG2
    @param [in] ARG3
    @param [in] ARG4 */
TgEXTN TgVOID
tgRN_CN_Helper__F1_Command(
    TgBOOL_PC TgANALYSIS_NO_NULL OUT0, TgFLOAT32_PC TgANALYSIS_NO_NULL OUT1, TgUINT_E32_C ARG2, TgCHAR_U8_CPC ARG3[], TgCHAR_U8_CPCU TgANALYSIS_NO_NULL ARG4 );

/*  @brief Helper function for creating Console Commands. Accepts command to set the value
    @param [out] OUT0
    @param [out] OUT1
    @param [out] OUT2
    @param [out] OUT3
    @param [in] ARG4
    @param [in] ARG5
    @param [in] ARG6 */
TgEXTN TgVOID
tgRN_CN_Helper__F3_Command(
    TgBOOL_PC TgANALYSIS_NO_NULL OUT0, TgFLOAT32_PC TgANALYSIS_NO_NULL OUT1, TgFLOAT32_PC TgANALYSIS_NO_NULL OUT2, TgFLOAT32_PC TgANALYSIS_NO_NULL OUT3, TgUINT_E32_C ARG4,
    TgCHAR_U8_CPC ARG5[], TgCHAR_U8_CPCU TgANALYSIS_NO_NULL ARG6 );

/*# TgCOMPILE__CONSOLE */
#endif

/** @} TGS_COMMON_CONSOLE */


/* =============================================================================================================================================================================== */
#endif
