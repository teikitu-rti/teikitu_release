/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Console [Var].h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_CONSOLE_VAR_H)
#define TGS_COMMON_CONSOLE_VAR_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Constants                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

enum { KTgCN_VAR_INIT                      = 1 <<  0 }; /**< Read-Only variable that is used for initialization */
enum { KTgCN_VAR_READ_ONLY                 = 1 <<  1 }; /**< Write once */
enum { KTgCN_VAR_CONFIG                    = 1 <<  2 }; /**< Value is read and written to configuration files */
enum { KTgCN_VAR_SERVER                    = 1 <<  3 }; /**< Communication to client from server */
enum { KTgCN_VAR_DEVELOPMENT               = 1 <<  4 }; /**< Used during development - this is a cheat variable */


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Macro Definitions                                                                                                                                                              */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
#if TgCOMPILE__CONSOLE_VAR_DEV

#define TgCN_VAR_DEV_DEFINE( A, B, C ) TgEXTN TgCN_VAR_ID A

/*# TgCOMPILE__CONSOLE_VAR_DEV */
#else

#define TgCN_VAR_DEV_DEFINE( A, B, C ) static const B A = C

/*# TgCOMPILE__CONSOLE_VAR_DEV */
#endif


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @addtogroup TGS_COMMON_CONSOLE */
/** @{ */

/** @brief Load the configuration file from the input object
    @param [in] ARG0 Pointer to an input object
    @param [in] ARG1 Offset to begin reading fro the input object */
TgEXTN TgVOID
tgCN_Var_Load_Config(
    STg2_Input_PC ARG0, TgRSIZE_C ARG1 );

/** @brief Store the current configuration to the output object
    @param [in,out] ARG Pointer to an output object */
TgEXTN TgVOID
tgCN_Var_Save_Config(
    STg2_Output_PC ARG );

/** @brief Return the initialization state of the system to manage console variable
    @return True if the service is initialized and false otherwise */
TgEXTN TgBOOL
tgCN_Var_Query_Init( TgVOID );

/** @brief Return the boot state of the system to manage console variable
    @return True if the service is booted and false otherwise */
TgEXTN TgBOOL
tgCN_Var_Query_Boot( TgVOID );

/** @brief Return the amount of fixed memory used for the management of console variables
    @return The amount of fixed memory being used by the module  */
TgEXTN TgRSIZE
tgCN_Var_Query_Fixed_Memory( TgVOID );


/** @brief Output all of the console variables
    @param [in,out] ARG Pointer to an output object */
TgEXTN TgVOID
tgCN_Print_Command_Variables(
    STg2_Output_P ARG );

/** @brief Return the console variable identifier associated with the given text string
    @param [in] ARG0 String holding the variable name
    @param [in] ARG1 Maximum number of \b >bytes< in the string buffer at ARG0 */
TgEXTN TgCN_VAR_ID
tgCN_Var_Query_Id(
    TgCHAR_U8_CPC ARG0, TgRSIZE_C ARG1 );


/** @brief Create a new console variable from the function arguments
    @param [in] ARG0 Multibyte string used to set the name of the console variable
    @param [in] ARG1 Maximum number of \b >bytes< in the string buffer at ARG0
    @param [in] ARG2 Multibyte string used to set the description of the console variable
    @param [in] ARG3 Maximum number of \b >bytes< in the string buffer at ARG2
    @param [in] ARG4 Console variable flags
    @param [in] ARG5 Default value for the console variable
    @return Identifier for the resulting console variable (or Invalid identifier otherwise) */
TgEXTN TgCN_VAR_ID
tgCN_Var_Init_Bool(
    TgCHAR_U8_CPC ARG0, TgRSIZE_C ARG1, TgCHAR_U8_CPC ARG2, TgRSIZE_C ARG3, TgUINT_E16_C ARG4, TgBOOL_C ARG5 );

/** @brief Create a new console variable from the function arguments
    @param [in] ARG0 Multibyte string used to set the name of the console variable 
    @param [in] ARG1 Maximum number of \b >bytes< in the string buffer at ARG0
    @param [in] ARG2 Multibyte string used to set the description of the console variable
    @param [in] ARG3 Maximum number of \b >bytes< in the string buffer at ARG2
    @param [in] ARG4 Console variable flags
    @param [in] ARG5 Default value for the console variable
    @param [in] ARG6 Minimum range value for the console variable
    @param [in] ARG7 Maximum range value for the console variable
    @return Identifier for the resulting console variable (or Invalid identifier otherwise) */
TgEXTN TgCN_VAR_ID
tgCN_Var_Init_S08(
    TgCHAR_U8_CPC ARG0, TgRSIZE_C ARG1, TgCHAR_U8_CPC ARG2, TgRSIZE_C ARG3, TgUINT_E16_C ARG4, TgSINT_E08_C ARG5, TgSINT_E08_C ARG6, TgSINT_E08_C ARG7 );

/** @brief Create a new console variable from the function arguments
    @param [in] ARG0 Multibyte string used to set the name of the console variable
    @param [in] ARG1 Maximum number of \b >bytes< in the string buffer at ARG0
    @param [in] ARG2 Multibyte string used to set the description of the console variable
    @param [in] ARG3 Maximum number of \b >bytes< in the string buffer at ARG2
    @param [in] ARG4 Console variable flags
    @param [in] ARG5 Default value for the console variable
    @param [in] ARG6 Minimum range value for the console variable
    @param [in] ARG7 Maximum range value for the console variable
    @return Identifier for the resulting console variable (or Invalid identifier otherwise) */
TgEXTN TgCN_VAR_ID
tgCN_Var_Init_S16(
    TgCHAR_U8_CPC ARG0, TgRSIZE_C ARG1, TgCHAR_U8_CPC ARG2, TgRSIZE_C ARG3, TgUINT_E16_C ARG4, TgSINT_E16_C ARG5, TgSINT_E16_C ARG6, TgSINT_E16_C ARG7 );

/** @brief Create a new console variable from the function arguments
    @param [in] ARG0 Multibyte string used to set the name of the console variable
    @param [in] ARG1 Maximum number of \b >bytes< in the string buffer at ARG0
    @param [in] ARG2 Multibyte string used to set the description of the console variable
    @param [in] ARG3 Maximum number of \b >bytes< in the string buffer at ARG2
    @param [in] ARG4 Console variable flags
    @param [in] ARG5 Default value for the console variable
    @param [in] ARG6 Minimum range value for the console variable
    @param [in] ARG7 Maximum range value for the console variable
    @return Identifier for the resulting console variable (or Invalid identifier otherwise) */
TgEXTN TgCN_VAR_ID
tgCN_Var_Init_S32(
    TgCHAR_U8_CPC ARG0, TgRSIZE_C ARG1, TgCHAR_U8_CPC ARG2, TgRSIZE_C ARG3, TgUINT_E16_C ARG4, TgSINT_E32_C ARG5, TgSINT_E32_C ARG6, TgSINT_E32_C ARG7 );

/** @brief Create a new console variable from the function arguments
    @param [in] ARG0 Multibyte string used to set the name of the console variable
    @param [in] ARG1 Maximum number of \b >bytes< in the string buffer at ARG0
    @param [in] ARG2 Multibyte string used to set the description of the console variable
    @param [in] ARG3 Maximum number of \b >bytes< in the string buffer at ARG2
    @param [in] ARG4 Console variable flags
    @param [in] ARG5 Default value for the console variable
    @param [in] ARG6 Minimum range value for the console variable
    @param [in] ARG7 Maximum range value for the console variable
    @return Identifier for the resulting console variable (or Invalid identifier otherwise) */
TgEXTN TgCN_VAR_ID
tgCN_Var_Init_S64(
    TgCHAR_U8_CPC ARG0, TgRSIZE_C ARG1, TgCHAR_U8_CPC ARG2, TgRSIZE_C ARG3, TgUINT_E16_C ARG4, TgSINT_E64_C ARG5, TgSINT_E64_C ARG6, TgSINT_E64_C ARG7 );

/** @brief Create a new console variable from the function arguments
    @param [in] ARG0 Multibyte string used to set the name of the console variable
    @param [in] ARG1 Maximum number of \b >bytes< in the string buffer at ARG0
    @param [in] ARG2 Multibyte string used to set the description of the console variable
    @param [in] ARG3 Maximum number of \b >bytes< in the string buffer at ARG2
    @param [in] ARG4 Console variable flags
    @param [in] ARG5 Default value for the console variable
    @param [in] ARG6 Minimum range value for the console variable
    @param [in] ARG7 Maximum range value for the console variable
    @return Identifier for the resulting console variable (or Invalid identifier otherwise) */
TgEXTN TgCN_VAR_ID
tgCN_Var_Init_U08(
    TgCHAR_U8_CPC ARG0, TgRSIZE_C ARG1, TgCHAR_U8_CPC ARG2, TgRSIZE_C ARG3, TgUINT_E16_C ARG4, TgUINT_E08_C ARG5, TgUINT_E08_C ARG6, TgUINT_E08_C ARG7 );

/** @brief Create a new console variable from the function arguments
    @param [in] ARG0 Multibyte string used to set the name of the console variable
    @param [in] ARG1 Maximum number of \b >bytes< in the string buffer at ARG0
    @param [in] ARG2 Multibyte string used to set the description of the console variable
    @param [in] ARG3 Maximum number of \b >bytes< in the string buffer at ARG2
    @param [in] ARG4 Console variable flags
    @param [in] ARG5 Default value for the console variable
    @param [in] ARG6 Minimum range value for the console variable
    @param [in] ARG7 Maximum range value for the console variable
    @return Identifier for the resulting console variable (or Invalid identifier otherwise) */
TgEXTN TgCN_VAR_ID
tgCN_Var_Init_U16(
    TgCHAR_U8_CPC ARG0, TgRSIZE_C ARG1, TgCHAR_U8_CPC ARG2, TgRSIZE_C ARG3, TgUINT_E16_C ARG4, TgUINT_E16_C ARG5, TgUINT_E16_C ARG6, TgUINT_E16_C ARG7 );

/** @brief Create a new console variable from the function arguments
    @param [in] ARG0 Multibyte string used to set the name of the console variable
    @param [in] ARG1 Maximum number of \b >bytes< in the string buffer at ARG0
    @param [in] ARG2 Multibyte string used to set the description of the console variable
    @param [in] ARG3 Maximum number of \b >bytes< in the string buffer at ARG2
    @param [in] ARG4 Console variable flags
    @param [in] ARG5 Default value for the console variable
    @param [in] ARG6 Minimum range value for the console variable
    @param [in] ARG7 Maximum range value for the console variable
    @return Identifier for the resulting console variable (or Invalid identifier otherwise) */
TgEXTN TgCN_VAR_ID
tgCN_Var_Init_U32(
    TgCHAR_U8_CPC ARG0, TgRSIZE_C ARG1, TgCHAR_U8_CPC ARG2, TgRSIZE_C ARG3, TgUINT_E16_C ARG4, TgUINT_E32_C ARG5, TgUINT_E32_C ARG6, TgUINT_E32_C ARG7 );

/** @brief Create a new console variable from the function arguments
    @param [in] ARG0 Multibyte string used to set the name of the console variable
    @param [in] ARG1 Maximum number of \b >bytes< in the string buffer at ARG0
    @param [in] ARG2 Multibyte string used to set the description of the console variable
    @param [in] ARG3 Maximum number of \b >bytes< in the string buffer at ARG2
    @param [in] ARG4 Console variable flags
    @param [in] ARG5 Default value for the console variable
    @param [in] ARG6 Minimum range value for the console variable
    @param [in] ARG7 Maximum range value for the console variable
    @return Identifier for the resulting console variable (or Invalid identifier otherwise) */
TgEXTN TgCN_VAR_ID
tgCN_Var_Init_U64(
    TgCHAR_U8_CPC ARG0, TgRSIZE_C ARG1, TgCHAR_U8_CPC ARG2, TgRSIZE_C ARG3, TgUINT_E16_C ARG4, TgUINT_E64_C ARG5, TgUINT_E64_C ARG6, TgUINT_E64_C ARG7 );

/** @brief Create a new console variable from the function arguments
    @param [in] ARG0 Multibyte string used to set the name of the console variable
    @param [in] ARG1 Maximum number of \b >bytes< in the string buffer at ARG0
    @param [in] ARG2 Multibyte string used to set the description of the console variable
    @param [in] ARG3 Maximum number of \b >bytes< in the string buffer at ARG2
    @param [in] ARG4 Console variable flags
    @param [in] ARG5 Default value for the console variable
    @param [in] ARG6 Minimum range value for the console variable
    @param [in] ARG7 Maximum range value for the console variable
    @return Identifier for the resulting console variable (or Invalid identifier otherwise) */
TgEXTN TgCN_VAR_ID
tgCN_Var_Init_F32(
    TgCHAR_U8_CPC ARG0, TgRSIZE_C ARG1, TgCHAR_U8_CPC ARG2, TgRSIZE_C ARG3, TgUINT_E16_C ARG4, TgFLOAT32_C ARG5, TgFLOAT32_C ARG6, TgFLOAT32_C ARG7 );

/** @brief Create a new console variable from the function arguments
    @param [in] ARG0 Multibyte string used to set the name of the console variable
    @param [in] ARG1 Maximum number of \b >bytes< in the string buffer at ARG0
    @param [in] ARG2 Multibyte string used to set the description of the console variable
    @param [in] ARG3 Maximum number of \b >bytes< in the string buffer at ARG2
    @param [in] ARG4 Console variable flags
    @param [in] ARG5 Default value for the console variable
    @param [in] ARG6 Minimum range value for the console variable
    @param [in] ARG7 Maximum range value for the console variable
    @return Identifier for the resulting console variable (or Invalid identifier otherwise) */
TgEXTN TgCN_VAR_ID
tgCN_Var_Init_F32_04_1(
    TgCHAR_U8_CPC ARG0, TgRSIZE_C ARG1, TgCHAR_U8_CPC ARG2, TgRSIZE_C ARG3, TgUINT_E16_C ARG4, TgVEC_F32_04_1_C ARG5, TgVEC_F32_04_1_C ARG6, TgVEC_F32_04_1_C ARG7 );

/** @brief Create a new console variable from the function arguments
    @param [in] ARG0 Multibyte string used to set the name of the console variable
    @param [in] ARG1 Maximum number of \b >bytes< in the string buffer at ARG0
    @param [in] ARG2 Multibyte string used to set the description of the console variable
    @param [in] ARG3 Maximum number of \b >bytes< in the string buffer at ARG2
    @param [in] ARG4 Console variable flags
    @param [in] ARG5 Default string for the console variable
    @param [in] ARG6 Maximum number of \b >bytes< in the string buffer at ARG5
    @param [in] ARG7 Buffer to hold the data for this console variable
    @param [in] ARG8 Maximum number of \b >bytes< in the string buffer at ARG7
    @return Identifier for the resulting console variable (or Invalid identifier otherwise) */
TgEXTN TgCN_VAR_ID
tgCN_Var_Init_String(
    TgCHAR_U8_CPC ARG0, TgRSIZE_C ARG1, TgCHAR_U8_CPC ARG2, TgRSIZE_C ARG3, TgUINT_E16_C ARG4, TgCHAR_U8_CPC ARG5, TgRSIZE_C ARG6, TgCHAR_U8_PC ARG7, TgRSIZE_C ARG8 );


/** @brief Assign a new value to the console variable
    @param [in] ARG0 Console variable identifier
    @param [in] ARG1 New value to assign to the console variable
    @return True if the function is successful and false otherwise */
TgEXTN TgBOOL
tgCN_Var_Set_Bool(
    TgCN_VAR_ID_C ARG0, TgBOOL_C ARG1 );

/** @brief Assign a new value to the console variable
    @param [in] ARG0 Console variable identifier
    @param [in] ARG1 New value to assign to the console variable
    @return True if the function is successful and false otherwise */
TgEXTN TgBOOL
tgCN_Var_Set_S08(
    TgCN_VAR_ID_C ARG0, TgSINT_E08_C ARG1 );

/** @brief Assign a new value to the console variable
    @param [in] ARG0 Console variable identifier
    @param [in] ARG1 New value to assign to the console variable
    @return True if the function is successful and false otherwise */
TgEXTN TgBOOL
tgCN_Var_Set_S16(
    TgCN_VAR_ID_C ARG0, TgSINT_E16_C ARG1 );

/** @brief Assign a new value to the console variable
    @param [in] ARG0 Console variable identifier
    @param [in] ARG1 New value to assign to the console variable
    @return True if the function is successful and false otherwise */
TgEXTN TgBOOL
tgCN_Var_Set_S32(
    TgCN_VAR_ID_C ARG0, TgSINT_E32_C ARG1 );

/** @brief Assign a new value to the console variable
    @param [in] ARG0 Console variable identifier
    @param [in] ARG1 New value to assign to the console variable
    @return True if the function is successful and false otherwise */
TgEXTN TgBOOL
tgCN_Var_Set_S64(
    TgCN_VAR_ID_C ARG0, TgSINT_E64_C ARG1 );

/** @brief Assign a new value to the console variable
    @param [in] ARG0 Console variable identifier
    @param [in] ARG1 New value to assign to the console variable
    @return True if the function is successful and false otherwise */
TgEXTN TgBOOL
tgCN_Var_Set_U08(
    TgCN_VAR_ID_C ARG0, TgUINT_E08_C ARG1 );

/** @brief Assign a new value to the console variable
    @param [in] ARG0 Console variable identifier
    @param [in] ARG1 New value to assign to the console variable
    @return True if the function is successful and false otherwise */
TgEXTN TgBOOL
tgCN_Var_Set_U16(
    TgCN_VAR_ID_C ARG0, TgUINT_E16_C ARG1 );

/** @brief Assign a new value to the console variable
    @param [in] ARG0 Console variable identifier
    @param [in] ARG1 New value to assign to the console variable
    @return True if the function is successful and false otherwise */
TgEXTN TgBOOL
tgCN_Var_Set_U32(
    TgCN_VAR_ID_C ARG0, TgUINT_E32_C ARG1 );

/** @brief Assign a new value to the console variable
    @param [in] ARG0 Console variable identifier
    @param [in] ARG1 New value to assign to the console variable
    @return True if the function is successful and false otherwise */
TgEXTN TgBOOL
tgCN_Var_Set_U64(
    TgCN_VAR_ID_C ARG0, TgUINT_E64_C ARG1 );

/** @brief Assign a new value to the console variable
    @param [in] ARG0 Console variable identifier
    @param [in] ARG1 New value to assign to the console variable
    @return True if the function is successful and false otherwise */
TgEXTN TgBOOL
tgCN_Var_Set_F32(
    TgCN_VAR_ID_C ARG0, TgFLOAT32_C ARG1 );

/** @brief Assign a new value to the console variable
    @param [in] ARG0 Console variable identifier
    @param [in] ARG1 New value to assign to the console variable
    @return True if the function is successful and false otherwise */
TgEXTN TgBOOL
tgCN_Var_Set_F32_04_1(
    TgCN_VAR_ID_C ARG0, TgVEC_F32_04_1_C ARG1 );

/** @brief Assign a new value to the console variable
    @param [in] ARG0 Console variable identifier
    @param [in] ARG1 New value to assign to the console variable
    @param [in] ARG2 Maximum size in bytes of the buffer at ARG1
    @return True if the function is successful and false otherwise */
TgEXTN TgBOOL
tgCN_Var_Set_String(
    TgCN_VAR_ID_C ARG0, TgCHAR_U8_CPC ARG1, TgRSIZE_C ARG2 );


/** @brief Store the current value of a console variable
    @param [out] OUT0 Destination pointer that will hold the current value of the console variable
    @param [in] ARG1 Console variable identifier
    @return True if the function is successful and false otherwise */
TgEXTN TgBOOL
tgCN_Var_Query_Bool(
    TgBOOL_P OUT0, TgCN_VAR_ID_C ARG1 );

/** @brief Store the current value of a console variable
    @param [out] OUT0 Destination pointer that will hold the current value of the console variable
    @param [in] ARG1 Console variable identifier
    @return True if the function is successful and false otherwise */
TgEXTN TgBOOL
tgCN_Var_Query_S08(
    TgSINT_E08_P OUT0, TgCN_VAR_ID_C ARG1 );

/** @brief Store the current value of a console variable
    @param [out] OUT0 Destination pointer that will hold the current value of the console variable
    @param [in] ARG1 Console variable identifier
    @return True if the function is successful and false otherwise */
TgEXTN TgBOOL
tgCN_Var_Query_S16(
    TgSINT_E16_P OUT0, TgCN_VAR_ID_C ARG1 );

/** @brief Store the current value of a console variable
    @param [out] OUT0 Destination pointer that will hold the current value of the console variable
    @param [in] ARG1 Console variable identifier
    @return True if the function is successful and false otherwise */
TgEXTN TgBOOL
tgCN_Var_Query_S32(
    TgSINT_E32_P OUT0, TgCN_VAR_ID_C ARG1 );

/** @brief Store the current value of a console variable
    @param [out] OUT0 Destination pointer that will hold the current value of the console variable
    @param [in] ARG1 Console variable identifier
    @return True if the function is successful and false otherwise */
TgEXTN TgBOOL
tgCN_Var_Query_S64(
    TgSINT_E64_P OUT0, TgCN_VAR_ID_C ARG1 );

/** @brief Store the current value of a console variable
    @param [out] OUT0 Destination pointer that will hold the current value of the console variable
    @param [in] ARG1 Console variable identifier
    @return True if the function is successful and false otherwise */
TgEXTN TgBOOL
tgCN_Var_Query_U08(
    TgUINT_E08_P OUT0, TgCN_VAR_ID_C ARG1 );

/** @brief Store the current value of a console variable
    @param [out] OUT0 Destination pointer that will hold the current value of the console variable
    @param [in] ARG1 Console variable identifier
    @return True if the function is successful and false otherwise */
TgEXTN TgBOOL
tgCN_Var_Query_U16(
    TgUINT_E16_P OUT0, TgCN_VAR_ID_C ARG1 );

/** @brief Store the current value of a console variable
    @param [out] OUT0 Destination pointer that will hold the current value of the console variable
    @param [in] ARG1 Console variable identifier
    @return True if the function is successful and false otherwise */
TgEXTN TgBOOL
tgCN_Var_Query_U32(
    TgUINT_E32_P OUT0, TgCN_VAR_ID_C ARG1 );

/** @brief Store the current value of a console variable
    @param [out] OUT0 Destination pointer that will hold the current value of the console variable
    @param [in] ARG1 Console variable identifier
    @return True if the function is successful and false otherwise */
TgEXTN TgBOOL
tgCN_Var_Query_U64(
    TgUINT_E64_P OUT0, TgCN_VAR_ID_C ARG1 );

/** @brief Store the current value of a console variable
    @param [out] OUT0 Destination pointer that will hold the current value of the console variable
    @param [in] ARG1 Console variable identifier
    @return True if the function is successful and false otherwise */
TgEXTN TgBOOL
tgCN_Var_Query_F32(
    TgFLOAT32_P OUT0, TgCN_VAR_ID_C ARG1 );

/** @brief Store the current value of a console variable
    @param [out] OUT0 Destination pointer that will hold the current value of the console variable
    @param [in] ARG1 Console variable identifier
    @return True if the function is successful and false otherwise */
TgEXTN TgBOOL
tgCN_Var_Query_F32_04_1(
    TgVEC_F32_04_1_P OUT0, TgCN_VAR_ID_C ARG1 );

/** @brief Store the current value of a console variable
    @param [out] OUT0 Destination pointer that will hold the current value of the console variable
    @param [in] ARG1 Console variable identifier
    @return True if the function is successful and false otherwise */
TgEXTN TgBOOL
tgCN_Var_Query_String(
    TgCHAR_U8_CPP OUT0, TgCN_VAR_ID_C ARG1 );

/** @} TGS_COMMON_CONSOLE */


/* =============================================================================================================================================================================== */
#endif
