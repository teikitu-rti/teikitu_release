/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Console - Internal.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_CONSOLE_INTERNAL_H)
#define TGS_COMMON_CONSOLE_INTERNAL_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Constants                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

enum { KTgCN_MAX_COMMAND_FCN               = 512,  /**< Maximum number of functions that can be registered with the console */
       KTgCN_MAX_COMMAND_VAR               = 2048, /**< Maximum number of variables that can be registered with the console */
       KTgCN_MAX_COMMAND_ALL               = KTgCN_MAX_COMMAND_FCN + KTgCN_MAX_COMMAND_VAR };
enum { KTgCN_MAX_COMMAND_HASH_SET          = KTgHASH_LG_SIZE };
enum { KTgCN_MAX_COMMAND_LEXICAL_LIST      = 29 * 29 * 29 };
enum { KTgCN_CMD_FLAG_USED                 = 1 };

typedef enum TgATTRIBUTE_ENUM
{
    ETgCN_COMMAND__UNKNOWN,         ETgCN_COMMAND__FCN,             ETgCN_COMMAND__VAR_BOOL,        ETgCN_COMMAND__VAR_S08,         ETgCN_COMMAND__VAR_S16,
    ETgCN_COMMAND__VAR_S32,         ETgCN_COMMAND__VAR_S64,         ETgCN_COMMAND__VAR_U08,         ETgCN_COMMAND__VAR_U16,         ETgCN_COMMAND__VAR_U32,
    ETgCN_COMMAND__VAR_U64,         ETgCN_COMMAND__VAR_F32,         ETgCN_COMMAND__VAR_F32_04,      ETgCN_COMMAND__VAR_STRING,

    ETgCN_COMMAND__FCN_START = ETgCN_COMMAND__FCN,
    ETgCN_COMMAND__FCN_END = ETgCN_COMMAND__FCN + 1,
    ETgCN_COMMAND__FCN_COUNT = ETgCN_COMMAND__FCN_END - ETgCN_COMMAND__FCN_START,

    ETgCN_COMMAND__VAR_START = ETgCN_COMMAND__VAR_BOOL,
    ETgCN_COMMAND__VAR_END = ETgCN_COMMAND__VAR_STRING + 1,
    ETgCN_COMMAND__VAR_COUNT = ETgCN_COMMAND__VAR_END - ETgCN_COMMAND__VAR_START,

    ETgCN_COMMAND_COUNT = ETgCN_COMMAND__FCN_COUNT + ETgCN_COMMAND__VAR_COUNT
} ETgCN_COMMAND;
TgTYPE_MODIFIER_DEFAULT(ETgCN_COMMAND);



/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Types                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TgTYPE_STRUCT(STg2_CN_Command_Common, )
{
    TgCHAR_U8_CP                                m_mbzName;
    TgRSIZE                                     m_nbyName;
    TgCHAR_U8_CP                                m_mbzDesc;
    TgRSIZE                                     m_nbyDesc;
    TgUINT_MAX                                  m_uiHash;
    STg2_CN_Command_Common_P                    m_psNext_Hash;
    STg2_CN_Command_Common_P                    m_psNext_Lexical;
    TgUINT_E32                                  m_uiType; /**< ETgCN_COMMAND */
    TgUINT_E32                                  m_uiFlags;
};


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions and Data                                                                                                                                                    */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TgEXTN TgRESULT
tgCN_Var_Init( TgVOID );

TgEXTN TgRESULT
tgCN_Var_Boot( TgVOID );

TgEXTN TgRESULT
tgCN_Var_Stop( TgVOID );

TgEXTN TgRESULT
tgCN_Var_Free( TgVOID );

TgEXTN TgRESULT
tgCN_Var_Update(
    TgFLOAT32_C );

TgEXTN TgCN_VAR_ID
tgCN_Var_Query_Id_Internal(
    STg2_CN_Command_Common_CPC );

/* Must be under a write lock from the calling function */
TgEXTN TgRESULT
tgCN_Insert_Command(
    STg2_CN_Command_Common_PP, STg2_CN_Command_Common_P );

TgEXTN TgVOID
tgCN_Init_Unit_Test(
    TgVOID_PP, TgRSIZE_P );

TgEXTN TgVOID
tgCN_Start_Unit_Test( TgVOID );

TgEXTN TgVOID
tgCN_Stop_Unit_Test(
    STg2_Output_P );

TgINLINE STg2_CN_Command_Common_P
tgCN_Find_Command_In_Hash(
    TgCHAR_U8_CPC, TgUINT_MAX_C );

TgINLINE TgSINT_E32
tgCN_Calc_Command_Lexical_Index(
    TgCHAR_U8_CPC, TgRSIZE_C );

TgINLINE TgBOOL
tgCN_Is_Command_Function(
    STg2_CN_Command_Common_CPCU );

TgINLINE TgBOOL
tgCN_Is_Command_Variable(
    STg2_CN_Command_Common_CPCU );


/** @internal Used to adjust the point in the console log where we start rendering it
    @param [in] ARG0 Integer to adjust the starting line by a count of lines
    @param [in] ARG1 Integer to adjust the starting line by a count of pages */
TgEXTN TgVOID
tgCN_Scroll_Display(
   TgSINT_E32_C ARG0, TgSINT_E32_C ARG1);

#if TgCOMPILE__CONSOLE

TgEXTN STg1_MT_MX                           g_sCN_OS_Lock; /* Lock for the On Screen Buffers */
TgEXTN TgCHAR_U8                            g_szOS_Console_Buffer[KTgCN_OSCON_MAX_LINE][KTgCN_OSCON_LINE_LENGTH];
TgEXTN TgRSIZE                              g_uiOS_Console_Buffer_Index;
TgEXTN TgRSIZE                              g_uiOS_Console_Cmd_Index;
TgEXTN TgRSIZE                              g_uiOS_Console_Display_Index;
TgEXTN TgRSIZE                              g_uiOS_Console_Cmd_History_Index;
TgEXTN TgBOOL                               g_bOS_Console_Render;
TgEXTN TgRSIZE                              g_nuiOS_Console_Render_Page_Height;

/*# TgCOMPILE__CONSOLE */
#endif

TgEXTN STg2_UT_LF_ISO__RW                   g_sCN_Command_Name_Lock;
TgEXTN STg2_CN_Command_Common_P             g_apsCN_Command_Hash_Set[KTgCN_MAX_COMMAND_HASH_SET];
TgEXTN STg2_CN_Command_Common_P             g_apsCommand_Lexical_Set[KTgCN_MAX_COMMAND_LEXICAL_LIST];


/* =============================================================================================================================================================================== */
#endif
