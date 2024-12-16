/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Console.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_CONSOLE_INL)
#define TGS_COMMON_CONSOLE_INL
#pragma once


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions and Internal Data                                                                                                                                         */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgCN_Find_Command_In_Hash ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE STg2_CN_Command_Common_P tgCN_Find_Command_In_Hash( TgCHAR_U8_CPC mbzCmd, TgUINT_MAX_C uiHash )
{
    STg2_CN_Command_Common_P            psIter_Cmd;
    TgRSIZE                             uiHash_Index;
    TgSINT_F08                          iRet;

    uiHash_Index = uiHash % KTgCN_MAX_COMMAND_HASH_SET;
    TgERROR_INDEX( uiHash_Index, g_apsCN_Command_Hash_Set );

    psIter_Cmd = g_apsCN_Command_Hash_Set[uiHash_Index];
    while (nullptr != psIter_Cmd)
    {
        if (TgSUCCEEDED(tgUSZ_Compare( &iRet, mbzCmd, KTgMAX_RSIZE, 0, psIter_Cmd->m_mbzName, KTgMAX_RSIZE, 0 )) && (0 == iRet))
        {
            return (psIter_Cmd);
        };

        psIter_Cmd = psIter_Cmd->m_psNext_Hash;
    };

    return (nullptr);
}


/* ---- tgCN_Calc_Command_Lexical_Index ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgSINT_F32 tgCN_Calc_Command_Lexical_Index( TgCHAR_U8_CPC mbzCmd, TgRSIZE_C nbyMaxCmd )
{
    TgSINT_F32                          iLexical_Index;
    TgCHAR_U8                           mbLower[KTgMAX_MB_LEN+1];

    tgU8_To_Lower( mbLower, mbzCmd );
    iLexical_Index = tgCM_CLP_S32( 1 + (TgSINT_F32)mbLower[0] - 'a', 0, 27 );
    iLexical_Index *= 29;
    if (0 == mbzCmd[1])
    {
        iLexical_Index += 28;
    }
    else
    {
        tgU8_To_Lower( mbLower, tgUSZ_Query_At( mbzCmd, nbyMaxCmd, 1 ) );
        iLexical_Index += tgCM_CLP_S32( 1 + (TgSINT_F32)mbLower[0] - 'a', 0, 27 );
    };
    iLexical_Index *= 29;
    if ((0 == mbzCmd[1]) || (0 == mbzCmd[2]))
    {
        iLexical_Index += 28;
    }
    else
    {
        tgU8_To_Lower( mbLower, tgUSZ_Query_At( mbzCmd, nbyMaxCmd, 2 ) );
        iLexical_Index += tgCM_CLP_S32( 1 + (TgSINT_F32 )mbLower[0] - 'a', 0, 27 );
    };

    return (iLexical_Index);
}


/* ---- tgCN_Is_Command_Function ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL tgCN_Is_Command_Function( STg2_CN_Command_Common_CPCU psCmd )
{
    return (psCmd->m_uiType >= ETgCN_COMMAND__FCN_START && psCmd->m_uiType < ETgCN_COMMAND__FCN_END);
}


/* ---- tgCN_Is_Command_Variable ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL tgCN_Is_Command_Variable( STg2_CN_Command_Common_CPCU psCmd )
{
    return (psCmd->m_uiType >= ETgCN_COMMAND__VAR_START && psCmd->m_uiType < ETgCN_COMMAND__VAR_END);
}


/* =============================================================================================================================================================================== */
#endif
