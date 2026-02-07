/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Console [Var].c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "TgS Common - Console - Internal.h"
#include "TgS Common - Console.inl"


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Types                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TgTYPE_UNION( STg2_CN_Var_Data, )
{
    struct
    {
        TgUN_SCALAR m_sCurrent;
        TgUN_SCALAR m_sMin;
        TgUN_SCALAR m_sMax;
        TgUN_SCALAR m_sDefault;
    } m_sScalar;

    struct
    {
        TgUN_V128 m_uCurrent;
        TgUN_V128 m_uMin;
        TgUN_V128 m_uMax;
        TgUN_V128 m_uDefault;
    } m_sVector;

    struct
    {
        TgCHAR_U8_P m_pszCurrent;
        TgRSIZE m_uiMaxLength;
        TgCHAR_U8_CP m_pszDefault;
    } m_sString;
};
TgCOMPILER_ASSERT( sizeof( STg2_CN_Var_Data ) == 64, 0 );

TgTYPE_UNION(STg2_CN_Command_Variable,)
{
    STg2_UT_ST__ST_Node                         m_sNode_Stack;
    struct 
    {
        TgALIGN(TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE)
        STg2_CN_Command_Common                      m_sCommon;
        STg2_CN_Var_Data                            m_sData;
        TgCN_VAR_ID_SINGLETON                       m_xtiVar_Singleton;
    #if 0 != (120 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE)
        TgUINT_E08                                  m_uiPad0[120 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE];
    #endif
    };
    TgCXX_CONSTRUCTOR(STg2_CN_Command_Variable(): m_xtiVar_Singleton() {})
};




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

static STg2_CN_Command_Variable_P           tgCN_Init_Command_Variable( TgCHAR_U8_CPC, TgRSIZE_C, TgCHAR_U8_CPC, TgRSIZE_C, TgUINT_E16_C  );
static TgCN_VAR_ID                          tgCN_Insert_Command_Variable( STg2_CN_Command_Variable_P );

static ETgMODULE_STATE                      s_enCN_Command_Variable_State = ETgMODULE_STATE__FREED;

                                            /* Console Variable List */
static STg2_CN_Command_Variable             s_asCommand_Variable[KTgCN_MAX_COMMAND_VAR];
static STg2_UT_LF_ISO__ST                   s_sCommand_Variable_Stack;
static TgSINT_E32                           s_niCommand_Variable_Used;




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgCN_Var_Update ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgCN_Var_Update( TgATTRIBUTE_UNUSED TgFLOAT32_C fDT )
{
    return (KTgS_OK);
}


/* ---- tgCN_Var_Load_Config ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgCN_Var_Load_Config( STg2_Input_PC psInput, TgRSIZE_C uiOffset )
{
    TgRSIZE                             uiPos;

    uiPos = uiOffset;
    while (!psInput->m_pfnEnd_Of_File( psInput, uiPos ))
    {
        TgCHAR_U8                           szBuffer[1024];
        TgCHAR_U8_P                         aszToken[8];
        TgSINT_E32                          niToken;
        TgCN_VAR_ID                         tiCN_Var;
        STg2_CN_Command_Variable_P          psCmd_Var;
        TgBOOL                              bRet;

        uiPos += tgIO_Read_Line( szBuffer, TgARRAY_COUNT( szBuffer ) - 1, psInput, uiPos );
        szBuffer[TgARRAY_COUNT( szBuffer ) - 1] = 0;
        niToken = tgUSZ_Token_List( aszToken, TgARRAY_COUNT( aszToken ), szBuffer, sizeof szBuffer );
        if (niToken <= 1)
        {
            continue;
        };

        tiCN_Var = tgCN_Var_Query_Id( aszToken[0], KTgMAX_RSIZE );

        psCmd_Var = s_asCommand_Variable + tiCN_Var.m_uiI;
        bRet = false;
        switch (psCmd_Var->m_sCommon.m_uiType)
        {
            case ETgCN_COMMAND__VAR_BOOL:
                bRet = tgCN_Var_Set_Bool( tiCN_Var, tgUSZ_To_Bool( aszToken[1], KTgMAX_RSIZE ) );
                break;

            case ETgCN_COMMAND__VAR_S08:
                bRet = tgCN_Var_Set_S08( tiCN_Var, tgUSZ_To_S08( aszToken[1], KTgMAX_RSIZE ) );
                break;

            case ETgCN_COMMAND__VAR_S16:
                bRet = tgCN_Var_Set_S16( tiCN_Var, tgUSZ_To_S16( aszToken[1], KTgMAX_RSIZE ) );
                break;

            case ETgCN_COMMAND__VAR_S32:
                bRet = tgCN_Var_Set_S32( tiCN_Var, tgUSZ_To_S32( aszToken[1], KTgMAX_RSIZE ) );
                break;

            case ETgCN_COMMAND__VAR_S64:
                bRet = tgCN_Var_Set_S64( tiCN_Var, tgUSZ_To_S64( aszToken[1], KTgMAX_RSIZE ) );
                break;

            case ETgCN_COMMAND__VAR_U08:
                bRet = tgCN_Var_Set_U08( tiCN_Var, tgUSZ_To_U08( aszToken[1], KTgMAX_RSIZE ) );
                break;

            case ETgCN_COMMAND__VAR_U16:
                bRet = tgCN_Var_Set_U16( tiCN_Var, tgUSZ_To_U16( aszToken[1], KTgMAX_RSIZE ) );
                break;

            case ETgCN_COMMAND__VAR_U32:
                bRet = tgCN_Var_Set_U32( tiCN_Var, tgUSZ_To_U32( aszToken[1], KTgMAX_RSIZE ) );
                break;

            case ETgCN_COMMAND__VAR_U64:
                bRet = tgCN_Var_Set_U64( tiCN_Var, tgUSZ_To_U64( aszToken[1], KTgMAX_RSIZE ) );
                break;

            case ETgCN_COMMAND__VAR_F32:
                bRet = tgCN_Var_Set_F32( tiCN_Var, tgUSZ_To_F32( aszToken[1], KTgMAX_RSIZE ) );
                break;

            case ETgCN_COMMAND__VAR_F32_04:
            {
                TgUN_V128                           uValue;

                if (niToken >= 5)
                {
                    uValue.m_vS_F32_04_1.x = tgUSZ_To_F32( aszToken[1], KTgMAX_RSIZE );
                    uValue.m_vS_F32_04_1.y = tgUSZ_To_F32( aszToken[2], KTgMAX_RSIZE );
                    uValue.m_vS_F32_04_1.z = tgUSZ_To_F32( aszToken[3], KTgMAX_RSIZE );
                    uValue.m_vS_F32_04_1.w = tgUSZ_To_F32( aszToken[4], KTgMAX_RSIZE );
                    bRet = tgCN_Var_Set_F32_04_1( tiCN_Var, uValue.m_vF32_04_1 );
                };
            };
            break;

            case ETgCN_COMMAND__VAR_STRING:
                bRet = tgCN_Var_Set_String( tiCN_Var, aszToken[1], KTgMAX_RSIZE );
                break;

            default:
                TgS_NO_DEFAULT( break );
        };

        if (!bRet)
        {
            TgWARNING_MSGF( 0, STD_MSG_LITERAL_3, STD_MSG_POST, u8"Failed to set (", aszToken[0], u8")." );
        };
    };
}


/* ---- tgCN_Var_Save_Config ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgCN_Var_Save_Config( STg2_Output_PC psOutput )
{
    TgSINT_E32                          iIndex;
    STg2_CN_Command_Variable_P          psCmd_Var;

    tgCM_UT_LF__RW__Enter_Read_Yield_Block( &g_sCN_Command_Name_Lock.m_sLock );

    for (iIndex = 0; iIndex < KTgCN_MAX_COMMAND_VAR; ++iIndex)
    {
        psCmd_Var = s_asCommand_Variable + iIndex;
        if (0 == (psCmd_Var->m_sCommon.m_uiFlags & KTgCN_CMD_FLAG_USED))
        {
            continue;
        };

        switch (psCmd_Var->m_sCommon.m_uiType)
        {
            case ETgCN_COMMAND__VAR_BOOL:
                tgIO_PrintF( psOutput, u8"%s %d\n", psCmd_Var->m_sCommon.m_mbzName, (TgUINT_E32)psCmd_Var->m_sData.m_sScalar.m_sCurrent.m_b );
                break;

            case ETgCN_COMMAND__VAR_S08:
                tgIO_PrintF( psOutput, u8"%s %d\n", psCmd_Var->m_sCommon.m_mbzName, psCmd_Var->m_sData.m_sScalar.m_sCurrent.m_iE08 );
                break;

            case ETgCN_COMMAND__VAR_S16:
                tgIO_PrintF( psOutput, u8"%s %d\n", psCmd_Var->m_sCommon.m_mbzName, psCmd_Var->m_sData.m_sScalar.m_sCurrent.m_iE16 );
                break;

            case ETgCN_COMMAND__VAR_S32:
                tgIO_PrintF( psOutput, u8"%s %d\n", psCmd_Var->m_sCommon.m_mbzName, psCmd_Var->m_sData.m_sScalar.m_sCurrent.m_iF32 );
                break;

            case ETgCN_COMMAND__VAR_S64:
                tgIO_PrintF( psOutput, u8"%s %I64d\n", psCmd_Var->m_sCommon.m_mbzName, psCmd_Var->m_sData.m_sScalar.m_sCurrent.m_iF64 );
                break;

            case ETgCN_COMMAND__VAR_U08:
                tgIO_PrintF( psOutput, u8"%s %d\n", psCmd_Var->m_sCommon.m_mbzName, psCmd_Var->m_sData.m_sScalar.m_sCurrent.m_uiE08 );
                break;

            case ETgCN_COMMAND__VAR_U16:
                tgIO_PrintF( psOutput, u8"%s %d\n", psCmd_Var->m_sCommon.m_mbzName, psCmd_Var->m_sData.m_sScalar.m_sCurrent.m_uiE16 );
                break;

            case ETgCN_COMMAND__VAR_U32:
                tgIO_PrintF( psOutput, u8"%s %d\n", psCmd_Var->m_sCommon.m_mbzName, psCmd_Var->m_sData.m_sScalar.m_sCurrent.m_uiF32 );
                break;

            case ETgCN_COMMAND__VAR_U64:
                tgIO_PrintF( psOutput, u8"%s %I64d\n", psCmd_Var->m_sCommon.m_mbzName, psCmd_Var->m_sData.m_sScalar.m_sCurrent.m_uiF64 );
                break;

            case ETgCN_COMMAND__VAR_F32:
                tgIO_PrintF( psOutput, u8"%s %f\n", psCmd_Var->m_sCommon.m_mbzName, (TgFLOAT64)psCmd_Var->m_sData.m_sScalar.m_sCurrent.m_f32 );
                break;

            case ETgCN_COMMAND__VAR_F32_04:
                tgIO_PrintF( psOutput, u8"%s %f %f %f %f\n", psCmd_Var->m_sCommon.m_mbzName,
                                (TgFLOAT64)psCmd_Var->m_sData.m_sVector.m_uCurrent.m_vS_F32_04_1.x,
                                (TgFLOAT64)psCmd_Var->m_sData.m_sVector.m_uCurrent.m_vS_F32_04_1.y,
                                (TgFLOAT64)psCmd_Var->m_sData.m_sVector.m_uCurrent.m_vS_F32_04_1.z,
                                (TgFLOAT64)psCmd_Var->m_sData.m_sVector.m_uCurrent.m_vS_F32_04_1.w );
                break;

            case ETgCN_COMMAND__VAR_STRING:
                tgIO_PrintF( psOutput, u8"%s %s\n", psCmd_Var->m_sCommon.m_mbzName, psCmd_Var->m_sData.m_sString.m_pszCurrent );
                break;

            default:
                TgS_NO_DEFAULT( break );
        };
    };

    tgCM_UT_LF__RW__Exit_Read( &g_sCN_Command_Name_Lock.m_sLock );
}


/* ---- tgCN_Var_Query_Init ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgCN_Var_Query_Init( TgVOID )
{
    return (ETgMODULE_STATE__INITIALIZED <= s_enCN_Command_Variable_State && s_enCN_Command_Variable_State <= ETgMODULE_STATE__STOPPED);
}


/* ---- tgCN_Var_Query_Boot ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgCN_Var_Query_Boot( TgVOID )
{
    return (ETgMODULE_STATE__BOOTED == s_enCN_Command_Variable_State);
}


/* ---- tgCN_Var_Query_Fixed_Memory ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRSIZE tgCN_Var_Query_Fixed_Memory( TgVOID )
{
    return ( 0
             + sizeof( s_enCN_Command_Variable_State )
             + sizeof( s_asCommand_Variable )
             + sizeof( s_sCommand_Variable_Stack )
             + sizeof( s_niCommand_Variable_Used )
    );
}


/* ---- tgCN_Print_Command_Variables --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgCN_Print_Command_Variables( STg2_Output_P psOUT )
{
    TgSINT_E32                          iIndex;
    STg2_CN_Command_Common_P            psCmd;

    tgCM_UT_LF__RW__Enter_Read_Yield_Block( &g_sCN_Command_Name_Lock.m_sLock );

    for (iIndex = 0; iIndex < KTgCN_MAX_COMMAND_VAR; ++iIndex)
    {
        psCmd = &s_asCommand_Variable[iIndex].m_sCommon;
        if (0 == (psCmd->m_uiFlags & KTgCN_CMD_FLAG_USED))
        {
            continue;
        }

        tgIO_PrintF( psOUT, STD_MSG_LITERAL_3, STD_MSG_POST, psCmd->m_mbzName, u8" - ", psCmd->m_mbzDesc );
    };

    tgCM_UT_LF__RW__Exit_Read( &g_sCN_Command_Name_Lock.m_sLock );
}


/* ---- tgCN_Var_Init_Bool ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgCN_VAR_ID tgCN_Var_Init_Bool( TgCHAR_U8_CPC mbzVar, TgRSIZE_C nbyMaxVar, TgCHAR_U8_CPC mbzDesc, TgRSIZE_C nbyMaxDesc, TgUINT_E16_C uiFlags, TgBOOL_C bDefault )
{
    STg2_CN_Command_Variable_P          psCmd_Var;

    psCmd_Var = tgCN_Init_Command_Variable( mbzVar, nbyMaxVar, mbzDesc, nbyMaxDesc, uiFlags );
    if (nullptr == psCmd_Var)
    {
        return (KTgCN_VAR_ID__INVALID);
    };

    psCmd_Var->m_sCommon.m_uiType = ETgCN_COMMAND__VAR_BOOL;
    psCmd_Var->m_sData.m_sScalar.m_sCurrent.m_b = bDefault;
    psCmd_Var->m_sData.m_sScalar.m_sDefault.m_b = bDefault;

    return (tgCN_Insert_Command_Variable( psCmd_Var ));
}


/* ---- tgCN_Var_Init_S08 -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgCN_VAR_ID tgCN_Var_Init_S08(
    TgCHAR_U8_CPC mbzVar, TgRSIZE_C nbyMaxVar, TgCHAR_U8_CPC mbzDesc, TgRSIZE_C nbyMaxDesc, TgUINT_E16_C uiFlags,
    TgSINT_E08_C iDefault, TgSINT_E08_C iMin, TgSINT_E08_C iMax )
{
    STg2_CN_Command_Variable_P          psCmd_Var;

    psCmd_Var = tgCN_Init_Command_Variable( mbzVar, nbyMaxVar, mbzDesc, nbyMaxDesc, uiFlags );
    if (nullptr == psCmd_Var)
    {
        return (KTgCN_VAR_ID__INVALID);
    };

    psCmd_Var->m_sCommon.m_uiType = ETgCN_COMMAND__VAR_S08;
    psCmd_Var->m_sData.m_sScalar.m_sCurrent.m_iE08 = iDefault;
    psCmd_Var->m_sData.m_sScalar.m_sMin.m_iE08 = iMin;
    psCmd_Var->m_sData.m_sScalar.m_sMax.m_iE08 = iMax;
    psCmd_Var->m_sData.m_sScalar.m_sDefault.m_iE08 = iDefault;

    return (tgCN_Insert_Command_Variable( psCmd_Var ));
}


/* ---- tgCN_Var_Init_S16 -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgCN_VAR_ID tgCN_Var_Init_S16(
    TgCHAR_U8_CPC mbzVar, TgRSIZE_C nbyMaxVar, TgCHAR_U8_CPC mbzDesc, TgRSIZE_C nbyMaxDesc, TgUINT_E16_C uiFlags,
    TgSINT_E16_C iDefault, TgSINT_E16_C iMin, TgSINT_E16_C iMax )
{
    STg2_CN_Command_Variable_P          psCmd_Var;

    psCmd_Var = tgCN_Init_Command_Variable( mbzVar, nbyMaxVar, mbzDesc, nbyMaxDesc, uiFlags );
    if (nullptr == psCmd_Var)
    {
        return (KTgCN_VAR_ID__INVALID);
    };

    psCmd_Var->m_sCommon.m_uiType = ETgCN_COMMAND__VAR_S16;
    psCmd_Var->m_sData.m_sScalar.m_sCurrent.m_iE16 = iDefault;
    psCmd_Var->m_sData.m_sScalar.m_sMin.m_iE16 = iMin;
    psCmd_Var->m_sData.m_sScalar.m_sMax.m_iE16 = iMax;
    psCmd_Var->m_sData.m_sScalar.m_sDefault.m_iE16 = iDefault;

    return (tgCN_Insert_Command_Variable( psCmd_Var ));
}


/* ---- tgCN_Var_Init_S32 -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgCN_VAR_ID tgCN_Var_Init_S32(
    TgCHAR_U8_CPC mbzVar, TgRSIZE_C nbyMaxVar, TgCHAR_U8_CPC mbzDesc, TgRSIZE_C nbyMaxDesc, TgUINT_E16_C uiFlags,
    TgSINT_E32_C iDefault, TgSINT_E32_C iMin, TgSINT_E32_C iMax )
{
    STg2_CN_Command_Variable_P          psCmd_Var;

    psCmd_Var = tgCN_Init_Command_Variable( mbzVar, nbyMaxVar, mbzDesc, nbyMaxDesc, uiFlags );
    if (nullptr == psCmd_Var)
    {
        return (KTgCN_VAR_ID__INVALID);
    };

    psCmd_Var->m_sCommon.m_uiType = ETgCN_COMMAND__VAR_S32;
    psCmd_Var->m_sData.m_sScalar.m_sCurrent.m_iF32 = iDefault;
    psCmd_Var->m_sData.m_sScalar.m_sMin.m_iF32 = iMin;
    psCmd_Var->m_sData.m_sScalar.m_sMax.m_iF32 = iMax;
    psCmd_Var->m_sData.m_sScalar.m_sDefault.m_iF32 = iDefault;

    return (tgCN_Insert_Command_Variable( psCmd_Var ));
}


/* ---- tgCN_Var_Init_S64 -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgCN_VAR_ID tgCN_Var_Init_S64(
    TgCHAR_U8_CPC mbzVar, TgRSIZE_C nbyMaxVar, TgCHAR_U8_CPC mbzDesc, TgRSIZE_C nbyMaxDesc, TgUINT_E16_C uiFlags,
    TgSINT_E64_C iDefault, TgSINT_E64_C iMin, TgSINT_E64_C iMax )
{
    STg2_CN_Command_Variable_P          psCmd_Var;

    psCmd_Var = tgCN_Init_Command_Variable( mbzVar, nbyMaxVar, mbzDesc, nbyMaxDesc, uiFlags );
    if (nullptr == psCmd_Var)
    {
        return (KTgCN_VAR_ID__INVALID);
    };

    psCmd_Var->m_sCommon.m_uiType = ETgCN_COMMAND__VAR_S64;
    psCmd_Var->m_sData.m_sScalar.m_sCurrent.m_iF64 = iDefault;
    psCmd_Var->m_sData.m_sScalar.m_sMin.m_iF64 = iMin;
    psCmd_Var->m_sData.m_sScalar.m_sMax.m_iF64 = iMax;
    psCmd_Var->m_sData.m_sScalar.m_sDefault.m_iF64 = iDefault;

    return (tgCN_Insert_Command_Variable( psCmd_Var ));
}


/* ---- tgCN_Var_Init_U08 -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgCN_VAR_ID tgCN_Var_Init_U08(
    TgCHAR_U8_CPC mbzVar, TgRSIZE_C nbyMaxVar, TgCHAR_U8_CPC mbzDesc, TgRSIZE_C nbyMaxDesc, TgUINT_E16_C uiFlags,
    TgUINT_E08_C uiDefault, TgUINT_E08_C uiMin, TgUINT_E08_C uiMax )
{
    STg2_CN_Command_Variable_P          psCmd_Var;

    psCmd_Var = tgCN_Init_Command_Variable( mbzVar, nbyMaxVar, mbzDesc, nbyMaxDesc, uiFlags );
    if (nullptr == psCmd_Var)
    {
        return (KTgCN_VAR_ID__INVALID);
    };

    psCmd_Var->m_sCommon.m_uiType = ETgCN_COMMAND__VAR_U08;
    psCmd_Var->m_sData.m_sScalar.m_sCurrent.m_uiE08 = uiDefault;
    psCmd_Var->m_sData.m_sScalar.m_sMin.m_uiE08 = uiMin;
    psCmd_Var->m_sData.m_sScalar.m_sMax.m_uiE08 = uiMax;
    psCmd_Var->m_sData.m_sScalar.m_sDefault.m_uiE08 = uiDefault;

    return (tgCN_Insert_Command_Variable( psCmd_Var ));
}


/* ---- tgCN_Var_Init_U16 -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgCN_VAR_ID tgCN_Var_Init_U16(
    TgCHAR_U8_CPC mbzVar, TgRSIZE_C nbyMaxVar, TgCHAR_U8_CPC mbzDesc, TgRSIZE_C nbyMaxDesc, TgUINT_E16_C uiFlags,
    TgUINT_E16_C uiDefault, TgUINT_E16_C uiMin, TgUINT_E16_C uiMax )
{
    STg2_CN_Command_Variable_P          psCmd_Var;

    psCmd_Var = tgCN_Init_Command_Variable( mbzVar, nbyMaxVar, mbzDesc, nbyMaxDesc, uiFlags );
    if (nullptr == psCmd_Var)
    {
        return (KTgCN_VAR_ID__INVALID);
    };

    psCmd_Var->m_sCommon.m_uiType = ETgCN_COMMAND__VAR_U16;
    psCmd_Var->m_sData.m_sScalar.m_sCurrent.m_uiE16 = uiDefault;
    psCmd_Var->m_sData.m_sScalar.m_sMin.m_uiE16 = uiMin;
    psCmd_Var->m_sData.m_sScalar.m_sMax.m_uiE16 = uiMax;
    psCmd_Var->m_sData.m_sScalar.m_sDefault.m_uiE16 = uiDefault;

    return (tgCN_Insert_Command_Variable( psCmd_Var ));
}


/* ---- tgCN_Var_Init_U32 -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgCN_VAR_ID tgCN_Var_Init_U32(
    TgCHAR_U8_CPC mbzVar, TgRSIZE_C nbyMaxVar, TgCHAR_U8_CPC mbzDesc, TgRSIZE_C nbyMaxDesc, TgUINT_E16_C uiFlags,
    TgUINT_E32_C uiDefault, TgUINT_E32_C uiMin, TgUINT_E32_C uiMax )
{
    STg2_CN_Command_Variable_P          psCmd_Var;

    psCmd_Var = tgCN_Init_Command_Variable( mbzVar, nbyMaxVar, mbzDesc, nbyMaxDesc, uiFlags );
    if (nullptr == psCmd_Var)
    {
        return (KTgCN_VAR_ID__INVALID);
    };

    psCmd_Var->m_sCommon.m_uiType = ETgCN_COMMAND__VAR_U32;
    psCmd_Var->m_sData.m_sScalar.m_sCurrent.m_uiF32 = uiDefault;
    psCmd_Var->m_sData.m_sScalar.m_sMin.m_uiF32 = uiMin;
    psCmd_Var->m_sData.m_sScalar.m_sMax.m_uiF32 = uiMax;
    psCmd_Var->m_sData.m_sScalar.m_sDefault.m_uiF32 = uiDefault;

    return (tgCN_Insert_Command_Variable( psCmd_Var ));
}


/* ---- tgCN_Var_Init_U64 -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgCN_VAR_ID tgCN_Var_Init_U64(
    TgCHAR_U8_CPC mbzVar, TgRSIZE_C nbyMaxVar, TgCHAR_U8_CPC mbzDesc, TgRSIZE_C nbyMaxDesc, TgUINT_E16_C uiFlags,
    TgUINT_E64_C uiDefault, TgUINT_E64_C uiMin, TgUINT_E64_C uiMax )
{
    STg2_CN_Command_Variable_P          psCmd_Var;

    psCmd_Var = tgCN_Init_Command_Variable( mbzVar, nbyMaxVar, mbzDesc, nbyMaxDesc, uiFlags );
    if (nullptr == psCmd_Var)
    {
        return (KTgCN_VAR_ID__INVALID);
    };

    psCmd_Var->m_sCommon.m_uiType = ETgCN_COMMAND__VAR_U64;
    psCmd_Var->m_sData.m_sScalar.m_sCurrent.m_uiF64 = uiDefault;
    psCmd_Var->m_sData.m_sScalar.m_sMin.m_uiF64 = uiMin;
    psCmd_Var->m_sData.m_sScalar.m_sMax.m_uiF64 = uiMax;
    psCmd_Var->m_sData.m_sScalar.m_sDefault.m_uiF64 = uiDefault;

    return (tgCN_Insert_Command_Variable( psCmd_Var ));
}


/* ---- tgCN_Var_Init_F32 -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgCN_VAR_ID tgCN_Var_Init_F32(
    TgCHAR_U8_CPC mbzVar, TgRSIZE_C nbyMaxVar, TgCHAR_U8_CPC mbzDesc, TgRSIZE_C nbyMaxDesc, TgUINT_E16_C uiFlags,
    TgFLOAT32_C fDefault, TgFLOAT32_C fMin, TgFLOAT32_C fMax )
{
    STg2_CN_Command_Variable_P          psCmd_Var;

    psCmd_Var = tgCN_Init_Command_Variable( mbzVar, nbyMaxVar, mbzDesc, nbyMaxDesc, uiFlags );
    if (nullptr == psCmd_Var)
    {
        return (KTgCN_VAR_ID__INVALID);
    };

    psCmd_Var->m_sCommon.m_uiType = ETgCN_COMMAND__VAR_F32;
    psCmd_Var->m_sData.m_sScalar.m_sCurrent.m_f32 = fDefault;
    psCmd_Var->m_sData.m_sScalar.m_sMin.m_f32 = fMin;
    psCmd_Var->m_sData.m_sScalar.m_sMax.m_f32 = fMax;
    psCmd_Var->m_sData.m_sScalar.m_sDefault.m_f32 = fDefault;

    return (tgCN_Insert_Command_Variable( psCmd_Var ));
}


/* ---- tgCN_Var_Init_F32_04 ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgCN_VAR_ID tgCN_Var_Init_F32_04_1(
    TgCHAR_U8_CPC mbzVar, TgRSIZE_C nbyMaxVar, TgCHAR_U8_CPC mbzDesc, TgRSIZE_C nbyMaxDesc, TgUINT_E16_C uiFlags,
    TgVEC_F32_04_1_C vDefault, TgVEC_F32_04_1_C vMin, TgVEC_F32_04_1_C vMax )
{
    STg2_CN_Command_Variable_P          psCmd_Var;

    psCmd_Var = tgCN_Init_Command_Variable( mbzVar, nbyMaxVar, mbzDesc, nbyMaxDesc, uiFlags );
    if (nullptr == psCmd_Var)
    {
        return (KTgCN_VAR_ID__INVALID);
    };

    psCmd_Var->m_sCommon.m_uiType = ETgCN_COMMAND__VAR_F32_04;
    psCmd_Var->m_sData.m_sVector.m_uCurrent.m_vF32_04_1 = vDefault;
    psCmd_Var->m_sData.m_sVector.m_uMin.m_vF32_04_1 = vMin;
    psCmd_Var->m_sData.m_sVector.m_uMax.m_vF32_04_1 = vMax;
    psCmd_Var->m_sData.m_sVector.m_uDefault.m_vF32_04_1 = vDefault;

    return (tgCN_Insert_Command_Variable( psCmd_Var ));
}


/* ---- tgCN_Var_Init_String ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgCN_VAR_ID tgCN_Var_Init_String(
    TgCHAR_U8_CPC mbzVar, TgRSIZE_C nbyMaxVar, TgCHAR_U8_CPC mbzDesc, TgRSIZE_C nbyMaxDesc, TgUINT_E16_C uiFlags,
    TgCHAR_U8_CPC mbzDefault, TgRSIZE_C nbyMaxDefault, TgCHAR_U8_PC mbzBuffer, TgRSIZE_C nbyMaxBuffer )
{
    STg2_CN_Command_Variable_P          psCmd_Var;

    psCmd_Var = tgCN_Init_Command_Variable( mbzVar, nbyMaxVar, mbzDesc, nbyMaxDesc, uiFlags );
    if (nullptr == psCmd_Var)
    {
        return (KTgCN_VAR_ID__INVALID);
    };

    psCmd_Var->m_sCommon.m_uiType = ETgCN_COMMAND__VAR_STRING;
    if (nullptr != mbzDefault)
    {
        tgUSZ_Copy( mbzBuffer, nbyMaxBuffer, mbzDefault, nbyMaxDefault );
    };
    psCmd_Var->m_sData.m_sString.m_pszCurrent = mbzBuffer;
    psCmd_Var->m_sData.m_sString.m_uiMaxLength = nbyMaxBuffer;
    psCmd_Var->m_sData.m_sString.m_pszDefault = mbzDefault;

    return (tgCN_Insert_Command_Variable( psCmd_Var ));
}


/* ---- tgCN_Var_Set_Bool -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgCN_Var_Set_Bool( TgCN_VAR_ID_C tiCN_Var, TgBOOL_C bValue )
{
    STg2_CN_Command_Variable_P          psCmd_Var;

    if (0 == tiCN_Var.m_uiKI)
        return (false);

    TgPARAM_CHECK_INDEX( tiCN_Var.m_uiI, s_asCommand_Variable );
    psCmd_Var = s_asCommand_Variable + tiCN_Var.m_uiI;
    TgERROR(tgCN_VAR_ID_Is_Equal( &psCmd_Var->m_xtiVar_Singleton, tiCN_Var ));

    if (ETgCN_COMMAND__VAR_BOOL != psCmd_Var->m_sCommon.m_uiType)
    {
        return (false);
    };

    psCmd_Var->m_sData.m_sScalar.m_sCurrent.m_b = bValue;
    return (true);
}


/* ---- tgCN_Var_Set_S08 --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgCN_Var_Set_S08( TgCN_VAR_ID_C tiCN_Var, TgSINT_E08_C iValue )
{
    STg2_CN_Command_Variable_P          psCmd_Var;

    if (0 == tiCN_Var.m_uiKI)
        return (false);

    TgPARAM_CHECK_INDEX( tiCN_Var.m_uiI, s_asCommand_Variable );
    psCmd_Var = s_asCommand_Variable + tiCN_Var.m_uiI;
    TgERROR(tgCN_VAR_ID_Is_Equal( &psCmd_Var->m_xtiVar_Singleton, tiCN_Var ));

    if (ETgCN_COMMAND__VAR_S08 != psCmd_Var->m_sCommon.m_uiType)
    {
        return (false);
    };

    psCmd_Var->m_sData.m_sScalar.m_sCurrent.m_iE08 = tgCM_CLP_S08( iValue, psCmd_Var->m_sData.m_sScalar.m_sMin.m_iE08, psCmd_Var->m_sData.m_sScalar.m_sMax.m_iE08 );
    return (true);
}


/* ---- tgCN_Var_Set_S16 --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgCN_Var_Set_S16( TgCN_VAR_ID_C tiCN_Var, TgSINT_E16_C iValue )
{
    STg2_CN_Command_Variable_P          psCmd_Var;

    if (0 == tiCN_Var.m_uiKI)
        return (false);

    TgPARAM_CHECK_INDEX( tiCN_Var.m_uiI, s_asCommand_Variable );
    psCmd_Var = s_asCommand_Variable + tiCN_Var.m_uiI;
    TgERROR(tgCN_VAR_ID_Is_Equal( &psCmd_Var->m_xtiVar_Singleton, tiCN_Var ));

    if (ETgCN_COMMAND__VAR_S16 != psCmd_Var->m_sCommon.m_uiType)
    {
        return (false);
    };

    psCmd_Var->m_sData.m_sScalar.m_sCurrent.m_iE16 = (TgSINT_E16)tgCM_CLP_S32( iValue, psCmd_Var->m_sData.m_sScalar.m_sMin.m_iE16, psCmd_Var->m_sData.m_sScalar.m_sMax.m_iE16 );
    return (true);
}


/* ---- tgCN_Var_Set_S32 --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgCN_Var_Set_S32( TgCN_VAR_ID_C tiCN_Var, TgSINT_E32_C iValue )
{
    STg2_CN_Command_Variable_P          psCmd_Var;

    if (0 == tiCN_Var.m_uiKI)
        return (false);

    TgPARAM_CHECK_INDEX( tiCN_Var.m_uiI, s_asCommand_Variable );
    psCmd_Var = s_asCommand_Variable + tiCN_Var.m_uiI;
    TgERROR(tgCN_VAR_ID_Is_Equal( &psCmd_Var->m_xtiVar_Singleton, tiCN_Var ));

    if (ETgCN_COMMAND__VAR_S32 != psCmd_Var->m_sCommon.m_uiType)
    {
        return (false);
    };

    psCmd_Var->m_sData.m_sScalar.m_sCurrent.m_iF32 = tgCM_CLP_S32( iValue, psCmd_Var->m_sData.m_sScalar.m_sMin.m_iF32, psCmd_Var->m_sData.m_sScalar.m_sMax.m_iF32 );
    return (true);
}


/* ---- tgCN_Var_Set_S64 --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgCN_Var_Set_S64( TgCN_VAR_ID_C tiCN_Var, TgSINT_E64_C iValue )
{
    STg2_CN_Command_Variable_P          psCmd_Var;

    if (0 == tiCN_Var.m_uiKI)
        return (false);

    TgPARAM_CHECK_INDEX( tiCN_Var.m_uiI, s_asCommand_Variable );
    psCmd_Var = s_asCommand_Variable + tiCN_Var.m_uiI;
    TgERROR(tgCN_VAR_ID_Is_Equal( &psCmd_Var->m_xtiVar_Singleton, tiCN_Var ));

    if (ETgCN_COMMAND__VAR_S64 != psCmd_Var->m_sCommon.m_uiType)
    {
        return (false);
    };

    psCmd_Var->m_sData.m_sScalar.m_sCurrent.m_iF64 = tgCM_CLP_S64( iValue, psCmd_Var->m_sData.m_sScalar.m_sMin.m_iF64, psCmd_Var->m_sData.m_sScalar.m_sMax.m_iF64 );
    return (true);
}


/* ---- tgCN_Var_Set_U08 --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgCN_Var_Set_U08( TgCN_VAR_ID_C tiCN_Var, TgUINT_E08_C uiValue )
{
    STg2_CN_Command_Variable_P          psCmd_Var;

    if (0 == tiCN_Var.m_uiKI)
        return (false);

    TgPARAM_CHECK_INDEX( tiCN_Var.m_uiI, s_asCommand_Variable );
    psCmd_Var = s_asCommand_Variable + tiCN_Var.m_uiI;
    TgERROR(tgCN_VAR_ID_Is_Equal( &psCmd_Var->m_xtiVar_Singleton, tiCN_Var ));

    if (ETgCN_COMMAND__VAR_U08 != psCmd_Var->m_sCommon.m_uiType)
    {
        return (false);
    };

    psCmd_Var->m_sData.m_sScalar.m_sCurrent.m_uiE08 = tgCM_CLP_U08( uiValue, psCmd_Var->m_sData.m_sScalar.m_sMin.m_uiE08, psCmd_Var->m_sData.m_sScalar.m_sMax.m_uiE08 );
    return (true);
}


/* ---- tgCN_Var_Set_U16 --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgCN_Var_Set_U16( TgCN_VAR_ID_C tiCN_Var, TgUINT_E16_C uiValue )
{
    STg2_CN_Command_Variable_P          psCmd_Var;

    if (0 == tiCN_Var.m_uiKI)
        return (false);

    TgPARAM_CHECK_INDEX( tiCN_Var.m_uiI, s_asCommand_Variable );
    psCmd_Var = s_asCommand_Variable + tiCN_Var.m_uiI;
    TgERROR(tgCN_VAR_ID_Is_Equal( &psCmd_Var->m_xtiVar_Singleton, tiCN_Var ));

    if (ETgCN_COMMAND__VAR_U16 != psCmd_Var->m_sCommon.m_uiType)
    {
        return (false);
    };

    psCmd_Var->m_sData.m_sScalar.m_sCurrent.m_uiE16 = (TgUINT_E16)tgCM_CLP_U32( uiValue, psCmd_Var->m_sData.m_sScalar.m_sMin.m_uiE16, psCmd_Var->m_sData.m_sScalar.m_sMax.m_uiE16 );
    return (true);
}


/* ---- tgCN_Var_Set_U32 --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgCN_Var_Set_U32( TgCN_VAR_ID_C tiCN_Var, TgUINT_E32_C uiValue )
{
    STg2_CN_Command_Variable_P          psCmd_Var;

    if (0 == tiCN_Var.m_uiKI)
        return (false);

    TgPARAM_CHECK_INDEX( tiCN_Var.m_uiI, s_asCommand_Variable );
    psCmd_Var = s_asCommand_Variable + tiCN_Var.m_uiI;
    TgERROR(tgCN_VAR_ID_Is_Equal( &psCmd_Var->m_xtiVar_Singleton, tiCN_Var ));

    if (ETgCN_COMMAND__VAR_U32 != psCmd_Var->m_sCommon.m_uiType)
    {
        return (false);
    };

    psCmd_Var->m_sData.m_sScalar.m_sCurrent.m_uiF32 = tgCM_CLP_U32( uiValue, psCmd_Var->m_sData.m_sScalar.m_sMin.m_uiF32, psCmd_Var->m_sData.m_sScalar.m_sMax.m_uiF32 );
    return (true);
}


/* ---- tgCN_Var_Set_U64 --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgCN_Var_Set_U64( TgCN_VAR_ID_C tiCN_Var, TgUINT_E64_C uiValue )
{
    STg2_CN_Command_Variable_P          psCmd_Var;

    if (0 == tiCN_Var.m_uiKI)
        return (false);

    TgPARAM_CHECK_INDEX( tiCN_Var.m_uiI, s_asCommand_Variable );
    psCmd_Var = s_asCommand_Variable + tiCN_Var.m_uiI;
    TgERROR(tgCN_VAR_ID_Is_Equal( &psCmd_Var->m_xtiVar_Singleton, tiCN_Var ));

    if (ETgCN_COMMAND__VAR_U64 != psCmd_Var->m_sCommon.m_uiType)
    {
        return (false);
    };

    psCmd_Var->m_sData.m_sScalar.m_sCurrent.m_uiF64 = tgCM_CLP_U64( uiValue, psCmd_Var->m_sData.m_sScalar.m_sMin.m_uiF64, psCmd_Var->m_sData.m_sScalar.m_sMax.m_uiF64 );
    return (true);
}


/* ---- tgCN_Var_Set_F32 --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgCN_Var_Set_F32( TgCN_VAR_ID_C tiCN_Var, TgFLOAT32_C fValue )
{
    STg2_CN_Command_Variable_P          psCmd_Var;

    if (0 == tiCN_Var.m_uiKI)
        return (false);

    TgPARAM_CHECK_INDEX( tiCN_Var.m_uiI, s_asCommand_Variable );
    psCmd_Var = s_asCommand_Variable + tiCN_Var.m_uiI;
    TgERROR(tgCN_VAR_ID_Is_Equal( &psCmd_Var->m_xtiVar_Singleton, tiCN_Var ));

    if (ETgCN_COMMAND__VAR_F32 != psCmd_Var->m_sCommon.m_uiType)
    {
        return (false);
    };

    psCmd_Var->m_sData.m_sScalar.m_sCurrent.m_f32 = tgCM_CLP_F32( fValue, psCmd_Var->m_sData.m_sScalar.m_sMin.m_f32, psCmd_Var->m_sData.m_sScalar.m_sMax.m_f32 );
    return (true);
}


/* ---- tgCN_Var_Set_F32_04 ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgCN_Var_Set_F32_04_1( TgCN_VAR_ID_C tiCN_Var, TgVEC_F32_04_1_C vValue )
{
    STg2_CN_Command_Variable_P          psCmd_Var;

    if (0 == tiCN_Var.m_uiKI)
        return (false);

    TgPARAM_CHECK_INDEX( tiCN_Var.m_uiI, s_asCommand_Variable );
    psCmd_Var = s_asCommand_Variable + tiCN_Var.m_uiI;
    TgERROR(tgCN_VAR_ID_Is_Equal( &psCmd_Var->m_xtiVar_Singleton, tiCN_Var ));

    if (ETgCN_COMMAND__VAR_F32_04 != psCmd_Var->m_sCommon.m_uiType)
    {
        return (false);
    };

    psCmd_Var->m_sData.m_sVector.m_uCurrent.m_vF32_04_1 = tgMH_CLP_F32_04_1( vValue, psCmd_Var->m_sData.m_sVector.m_uMin.m_vF32_04_1, psCmd_Var->m_sData.m_sVector.m_uMax.m_vF32_04_1 );
    return (true);
}


/* ---- tgCN_Var_Set_String ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgCN_Var_Set_String( TgCN_VAR_ID_C tiCN_Var, TgCHAR_U8_CPC mbzValue, TgRSIZE_C nbyMaxValue )
{
    STg2_CN_Command_Variable_P          psCmd_Var;

    if (0 == tiCN_Var.m_uiKI)
        return (false);

    TgPARAM_CHECK_INDEX( tiCN_Var.m_uiI, s_asCommand_Variable );
    psCmd_Var = s_asCommand_Variable + tiCN_Var.m_uiI;
    TgERROR(tgCN_VAR_ID_Is_Equal( &psCmd_Var->m_xtiVar_Singleton, tiCN_Var ));

    if (ETgCN_COMMAND__VAR_STRING != psCmd_Var->m_sCommon.m_uiType)
    {
        return (false);
    };

    tgUSZ_Copy( psCmd_Var->m_sData.m_sString.m_pszCurrent, psCmd_Var->m_sData.m_sString.m_uiMaxLength, mbzValue, nbyMaxValue );
    return (true);
}


/* ---- tgCN_Var_Query_Bool ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgCN_Var_Query_Bool( TgBOOL_P pbRet, TgCN_VAR_ID_C tiCN_Var )
{
    STg2_CN_Command_Variable_P          psCmd_Var;

    if (0 == tiCN_Var.m_uiKI)
        return (false);

    TgPARAM_CHECK_INDEX( tiCN_Var.m_uiI, s_asCommand_Variable );
    psCmd_Var = s_asCommand_Variable + tiCN_Var.m_uiI;
    TgERROR(tgCN_VAR_ID_Is_Equal( &psCmd_Var->m_xtiVar_Singleton, tiCN_Var ));

    if (!pbRet || (ETgCN_COMMAND__VAR_BOOL != psCmd_Var->m_sCommon.m_uiType))
    {
        return (false);
    };

    *pbRet = psCmd_Var->m_sData.m_sScalar.m_sCurrent.m_b;
    return (true);
}


/* ---- tgCN_Var_Query_S08 ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgCN_Var_Query_S08( TgSINT_E08_P piRet, TgCN_VAR_ID_C tiCN_Var )
{
    STg2_CN_Command_Variable_P          psCmd_Var;

    if (0 == tiCN_Var.m_uiKI)
        return (false);

    TgPARAM_CHECK_INDEX( tiCN_Var.m_uiI, s_asCommand_Variable );
    psCmd_Var = s_asCommand_Variable + tiCN_Var.m_uiI;
    TgERROR(tgCN_VAR_ID_Is_Equal( &psCmd_Var->m_xtiVar_Singleton, tiCN_Var ));

    if (!piRet || (ETgCN_COMMAND__VAR_S08 != psCmd_Var->m_sCommon.m_uiType))
    {
        return (false);
    };

    *piRet = psCmd_Var->m_sData.m_sScalar.m_sCurrent.m_iE08;
    return (true);
}


/* ---- tgCN_Var_Query_S16 ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgCN_Var_Query_S16( TgSINT_E16_P piRet, TgCN_VAR_ID_C tiCN_Var )
{
    STg2_CN_Command_Variable_P          psCmd_Var;

    if (0 == tiCN_Var.m_uiKI)
        return (false);

    TgPARAM_CHECK_INDEX( tiCN_Var.m_uiI, s_asCommand_Variable );
    psCmd_Var = s_asCommand_Variable + tiCN_Var.m_uiI;
    TgERROR(tgCN_VAR_ID_Is_Equal( &psCmd_Var->m_xtiVar_Singleton, tiCN_Var ));

    if (!piRet || (ETgCN_COMMAND__VAR_S16 != psCmd_Var->m_sCommon.m_uiType))
    {
        return (false);
    };

    *piRet = psCmd_Var->m_sData.m_sScalar.m_sCurrent.m_iE16;
    return (true);
}


/* ---- tgCN_Var_Query_S32 ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgCN_Var_Query_S32( TgSINT_E32_P piRet, TgCN_VAR_ID_C tiCN_Var )
{
    STg2_CN_Command_Variable_P          psCmd_Var;

    if (0 == tiCN_Var.m_uiKI)
        return (false);

    TgPARAM_CHECK_INDEX( tiCN_Var.m_uiI, s_asCommand_Variable );
    psCmd_Var = s_asCommand_Variable + tiCN_Var.m_uiI;
    TgERROR(tgCN_VAR_ID_Is_Equal( &psCmd_Var->m_xtiVar_Singleton, tiCN_Var ));

    if (!piRet || (ETgCN_COMMAND__VAR_S32 != psCmd_Var->m_sCommon.m_uiType))
    {
        return (false);
    };

    *piRet = psCmd_Var->m_sData.m_sScalar.m_sCurrent.m_iE32;
    return (true);
}


/* ---- tgCN_Var_Query_S64 ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgCN_Var_Query_S64( TgSINT_E64_P piRet, TgCN_VAR_ID_C tiCN_Var )
{
    STg2_CN_Command_Variable_P          psCmd_Var;

    if (0 == tiCN_Var.m_uiKI)
        return (false);

    TgPARAM_CHECK_INDEX( tiCN_Var.m_uiI, s_asCommand_Variable );
    psCmd_Var = s_asCommand_Variable + tiCN_Var.m_uiI;
    TgERROR(tgCN_VAR_ID_Is_Equal( &psCmd_Var->m_xtiVar_Singleton, tiCN_Var ));

    if (!piRet || (ETgCN_COMMAND__VAR_S64 != psCmd_Var->m_sCommon.m_uiType))
    {
        return (false);
    };

    *piRet = psCmd_Var->m_sData.m_sScalar.m_sCurrent.m_iF64;
    return (true);
}


/* ---- tgCN_Var_Query_U08 ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgCN_Var_Query_U08( TgUINT_E08_P puiRet, TgCN_VAR_ID_C tiCN_Var )
{
    STg2_CN_Command_Variable_P          psCmd_Var;

    if (0 == tiCN_Var.m_uiKI)
        return (false);

    TgPARAM_CHECK_INDEX( tiCN_Var.m_uiI, s_asCommand_Variable );
    psCmd_Var = s_asCommand_Variable + tiCN_Var.m_uiI;
    TgERROR(tgCN_VAR_ID_Is_Equal( &psCmd_Var->m_xtiVar_Singleton, tiCN_Var ));

    if (!puiRet || (ETgCN_COMMAND__VAR_U08 != psCmd_Var->m_sCommon.m_uiType))
    {
        return (false);
    };

    *puiRet = psCmd_Var->m_sData.m_sScalar.m_sCurrent.m_uiE08;
    return (true);
}


/* ---- tgCN_Var_Query_U16 ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgCN_Var_Query_U16( TgUINT_E16_P puiRet, TgCN_VAR_ID_C tiCN_Var )
{
    STg2_CN_Command_Variable_P          psCmd_Var;

    if (0 == tiCN_Var.m_uiKI)
        return (false);

    TgPARAM_CHECK_INDEX( tiCN_Var.m_uiI, s_asCommand_Variable );
    psCmd_Var = s_asCommand_Variable + tiCN_Var.m_uiI;
    TgERROR(tgCN_VAR_ID_Is_Equal( &psCmd_Var->m_xtiVar_Singleton, tiCN_Var ));

    if (!puiRet || (ETgCN_COMMAND__VAR_U16 != psCmd_Var->m_sCommon.m_uiType))
    {
        return (false);
    };

    *puiRet = psCmd_Var->m_sData.m_sScalar.m_sCurrent.m_uiE16;
    return (true);
}


/* ---- tgCN_Var_Query_U32 ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgCN_Var_Query_U32( TgUINT_E32_P puiRet, TgCN_VAR_ID_C tiCN_Var )
{
    STg2_CN_Command_Variable_P          psCmd_Var;

    if (0 == tiCN_Var.m_uiKI)
        return (false);

    TgPARAM_CHECK_INDEX( tiCN_Var.m_uiI, s_asCommand_Variable );
    psCmd_Var = s_asCommand_Variable + tiCN_Var.m_uiI;
    TgERROR(tgCN_VAR_ID_Is_Equal( &psCmd_Var->m_xtiVar_Singleton, tiCN_Var ));

    if (!puiRet || (ETgCN_COMMAND__VAR_U32 != psCmd_Var->m_sCommon.m_uiType))
    {
        return (false);
    };

    *puiRet = psCmd_Var->m_sData.m_sScalar.m_sCurrent.m_uiE32;
    return (true);
}


/* ---- tgCN_Var_Query_U64 ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgCN_Var_Query_U64( TgUINT_E64_P puiRet, TgCN_VAR_ID_C tiCN_Var )
{
    STg2_CN_Command_Variable_P          psCmd_Var;

    if (0 == tiCN_Var.m_uiKI)
        return (false);

    TgPARAM_CHECK_INDEX( tiCN_Var.m_uiI, s_asCommand_Variable );
    psCmd_Var = s_asCommand_Variable + tiCN_Var.m_uiI;
    TgERROR(tgCN_VAR_ID_Is_Equal( &psCmd_Var->m_xtiVar_Singleton, tiCN_Var ));

    if (!puiRet || (ETgCN_COMMAND__VAR_U64 != psCmd_Var->m_sCommon.m_uiType))
    {
        return (false);
    };

    *puiRet = psCmd_Var->m_sData.m_sScalar.m_sCurrent.m_uiF64;
    return (true);
}


/* ---- tgCN_Var_Query_F32 ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgCN_Var_Query_F32( TgFLOAT32_P pfRet, TgCN_VAR_ID_C tiCN_Var )
{
    STg2_CN_Command_Variable_P          psCmd_Var;

    if (0 == tiCN_Var.m_uiKI)
        return (false);

    TgPARAM_CHECK_INDEX( tiCN_Var.m_uiI, s_asCommand_Variable );
    psCmd_Var = s_asCommand_Variable + tiCN_Var.m_uiI;
    TgERROR(tgCN_VAR_ID_Is_Equal( &psCmd_Var->m_xtiVar_Singleton, tiCN_Var ));

    if (!pfRet || (ETgCN_COMMAND__VAR_F32 != psCmd_Var->m_sCommon.m_uiType))
    {
        return (false);
    };

    *pfRet = psCmd_Var->m_sData.m_sScalar.m_sCurrent.m_f32;
    return (true);
}


/* ---- tgCN_Var_Query_F32_04 ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgCN_Var_Query_F32_04_1( TgVEC_F32_04_1_P pvRet, TgCN_VAR_ID_C tiCN_Var )
{
    STg2_CN_Command_Variable_P          psCmd_Var;

    if (0 == tiCN_Var.m_uiKI)
        return (false);

    TgPARAM_CHECK_INDEX( tiCN_Var.m_uiI, s_asCommand_Variable );
    psCmd_Var = s_asCommand_Variable + tiCN_Var.m_uiI;
    TgERROR(tgCN_VAR_ID_Is_Equal( &psCmd_Var->m_xtiVar_Singleton, tiCN_Var ));

    if (!pvRet || (ETgCN_COMMAND__VAR_F32_04 != psCmd_Var->m_sCommon.m_uiType))
    {
        return (false);
    };

    *pvRet = psCmd_Var->m_sData.m_sVector.m_uCurrent.m_vF32_04_1;
    return (true);
}


/* ---- tgCN_Var_Query_String ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgCN_Var_Query_String( TgCHAR_U8_CPP ppszRet, TgCN_VAR_ID_C tiCN_Var )
{
    STg2_CN_Command_Variable_P          psCmd_Var;

    if (0 == tiCN_Var.m_uiKI)
        return (false);

    TgPARAM_CHECK_INDEX( tiCN_Var.m_uiI, s_asCommand_Variable );
    psCmd_Var = s_asCommand_Variable + tiCN_Var.m_uiI;
    TgERROR(tgCN_VAR_ID_Is_Equal( &psCmd_Var->m_xtiVar_Singleton, tiCN_Var ));

    if (!ppszRet || (ETgCN_COMMAND__VAR_STRING != psCmd_Var->m_sCommon.m_uiType))
    {
        return (false);
    };

    *ppszRet = psCmd_Var->m_sData.m_sString.m_pszCurrent;
    return (true);
}


/* ---- tgCN_Var_Query_Id -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgCN_VAR_ID tgCN_Var_Query_Id( TgCHAR_U8_CPC mbzName, TgRSIZE_C nbyMaxName )
{
    TgUINT_MAX                          uiHash;
    STg2_CN_Command_Common_P            psCmd;

    if (TgFAILED(tgUSZ_Hash( &uiHash, mbzName, nbyMaxName )))
    {
        return (KTgCN_VAR_ID__INVALID);
    };
    psCmd = tgCN_Find_Command_In_Hash( mbzName, uiHash );
    return (tgCN_Var_Query_Id_Internal( psCmd ));
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgCN_Var_Init ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* NOTE: Called prior to MM and SM Init */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgCN_Var_Init( TgVOID )
{
    /* Verify the state of the system */
    TgERROR(ETgMODULE_STATE__FREED == s_enCN_Command_Variable_State);
    s_enCN_Command_Variable_State = ETgMODULE_STATE__INITIALIZING;

    tgMM_Set_U08_0x00( s_asCommand_Variable, sizeof( s_asCommand_Variable ) );
    s_niCommand_Variable_Used = 0;
    tgCM_UT_LF__ST__Init_PreLoad( &s_sCommand_Variable_Stack.m_sStack, s_asCommand_Variable, sizeof( STg2_CN_Command_Variable ), KTgCN_MAX_COMMAND_VAR );

    s_enCN_Command_Variable_State = ETgMODULE_STATE__INITIALIZED;
    return (KTgS_OK);
}


/* ---- tgCN_Var_Boot ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* NOTE: Called prior to MM and SM Init */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgCN_Var_Boot( TgVOID )
{
    /* Verify the state of the system */
    TgERROR(ETgMODULE_STATE__INITIALIZED == s_enCN_Command_Variable_State);
    s_enCN_Command_Variable_State = ETgMODULE_STATE__BOOTING;

    s_enCN_Command_Variable_State = ETgMODULE_STATE__BOOTED;
    return (KTgS_OK);
}


/* ---- tgCN_Var_Stop ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgCN_Var_Stop( TgVOID )
{
    if ((ETgMODULE_STATE__FREED == s_enCN_Command_Variable_State) || (ETgMODULE_STATE__INITIALIZED == s_enCN_Command_Variable_State))
    {
        return (KTgS_OK);
    };

    /* Verify the state of the system */
    TgERROR(ETgMODULE_STATE__BOOTED == s_enCN_Command_Variable_State);
    s_enCN_Command_Variable_State = ETgMODULE_STATE__STOPPING;

    s_enCN_Command_Variable_State = ETgMODULE_STATE__STOPPED;
    return (KTgS_OK);
}


/* ---- tgCN_Var_Free ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgCN_Var_Free( TgVOID )
{
    if (ETgMODULE_STATE__FREED == s_enCN_Command_Variable_State)
    {
        return (KTgS_OK);
    };

    /* Verify the state of the system */
    TgERROR((ETgMODULE_STATE__STOPPED == s_enCN_Command_Variable_State) || (ETgMODULE_STATE__INITIALIZED == s_enCN_Command_Variable_State));
    s_enCN_Command_Variable_State = ETgMODULE_STATE__FREEING;

    tgCM_UT_LF__ST__Free( &s_sCommand_Variable_Stack.m_sStack );

    s_enCN_Command_Variable_State = ETgMODULE_STATE__FREED;
    return (KTgS_OK);
}


/* ---- tgCN_Var_Query_Id_Internal ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgCN_VAR_ID tgCN_Var_Query_Id_Internal( STg2_CN_Command_Common_CPC psCmdP )
{
    union
    {
        STg2_CN_Command_Common_CP           psCommon;
        STg2_CN_Command_Variable_CP         psVar;
    }                                   psCmd;

    if (nullptr == psCmdP || (!tgCN_Is_Command_Variable( psCmdP )))
    {
        return (KTgCN_VAR_ID__INVALID);
    };

    psCmd.psCommon = psCmdP;
    return (tgCN_VAR_ID_Query_Unsafe( &psCmd.psVar->m_xtiVar_Singleton ));
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgCN_Init_Command_Variable ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static STg2_CN_Command_Variable_P tgCN_Init_Command_Variable( TgCHAR_U8_CPC mbzName, TgRSIZE_C nbyMaxName, TgCHAR_U8_CPC mbzDesc, TgRSIZE_C nbyMaxDest, TgUINT_E16_C uiFlags )
{
    union
    {
        STg2_CN_Command_Variable_P          psVar;
        STg2_UT_ST__ST_Node_P               psNode;
        
    }                                   psCmd;
    TgSTRING_DICT_ID                    tiString;

    TgPARAM_CHECK(nullptr != mbzName && mbzName[0]);

    psCmd.psNode = tgCM_UT_LF__ST__Pop( &s_sCommand_Variable_Stack.m_sStack );
    if (nullptr == psCmd.psVar)
    {
        TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Exceeded number of console command functions." );
        return (nullptr);
    };

    tgMM_Set_U08_0x00( psCmd.psVar, sizeof( STg2_CN_Command_Variable ) );

    if (TgFAILED(tgUSZ_Hash( &psCmd.psVar->m_sCommon.m_uiHash, mbzName, nbyMaxName )))
    {
        return (nullptr);
    };

    tiString = tgSM_Dict_Insert_String_Hash( mbzName, tgUSZ_Length_U08( mbzName, nbyMaxName ), psCmd.psVar->m_sCommon.m_uiHash );
    if (tiString.m_uiKI == KTgID__INVALID_VALUE)
    {
        tgCM_UT_LF__ST__Push( &s_sCommand_Variable_Stack.m_sStack, psCmd.psNode );
        return (nullptr);
    };
    tgSM_Dict_Query_String( &psCmd.psVar->m_sCommon.m_mbzName, &psCmd.psVar->m_sCommon.m_nbyName, tiString );
    if (nullptr != mbzDesc)
    {
        TgUINT_MAX                          uiHash;

        if (TgFAILED(tgUSZ_Hash( &uiHash, mbzDesc, nbyMaxDest )))
        {
            return (nullptr);
        };

        tiString = tgSM_Dict_Insert_String_Hash( mbzDesc, tgUSZ_Length_U08( mbzDesc, nbyMaxDest ), uiHash );
        if (tiString.m_uiKI != KTgID__INVALID_VALUE)
        {
            tgSM_Dict_Query_String( &psCmd.psVar->m_sCommon.m_mbzDesc, &psCmd.psVar->m_sCommon.m_nbyDesc, tiString );
        };
    }
    else
    {
        psCmd.psVar->m_sCommon.m_mbzDesc = nullptr;
    };

    tgCN_VAR_ID_Init( &psCmd.psVar->m_xtiVar_Singleton, (TgUINT_E32)(psCmd.psVar - s_asCommand_Variable) );
    psCmd.psVar->m_sCommon.m_uiFlags = uiFlags | (TgUINT_E32)KTgCN_CMD_FLAG_USED;

    return (psCmd.psVar);
}


/* ---- tgCN_Insert_Command_Variable --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgCN_VAR_ID tgCN_Insert_Command_Variable( STg2_CN_Command_Variable_P psCmd_Var )
{
    union
    {
        STg2_CN_Command_Common_P            psRet;
        STg2_CN_Command_Variable_P          psVar;
    }                                   psCmd;
    TgRESULT                            iRet;
    TgCN_VAR_ID                         tiVar;

    tgCM_UT_LF__RW__Enter_Write_Yield_Block( &g_sCN_Command_Name_Lock.m_sLock );

    iRet = tgCN_Insert_Command( &psCmd.psRet, &psCmd_Var->m_sCommon );
    if (TgSUCCEEDED( iRet ))
    {
        tiVar = tgCN_VAR_ID_Query_Unsafe( &psCmd_Var->m_xtiVar_Singleton );
        tgCM_UT_LF__RW__Exit_Write( &g_sCN_Command_Name_Lock.m_sLock );
        return (tiVar);
    }
    else if (KTgW_DUPLICATE == iRet)
    {
        tiVar = tgCN_VAR_ID_Query_Unsafe( &psCmd.psVar->m_xtiVar_Singleton );
        tgCM_UT_LF__RW__Exit_Write( &g_sCN_Command_Name_Lock.m_sLock );
        TgWARNING_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Duplicate console variable (first values retained)." );

        tgMM_Set_U08_0x00( psCmd_Var, sizeof( STg2_CN_Command_Variable ) );
        tgCM_UT_LF__ST__Push( &s_sCommand_Variable_Stack.m_sStack, &psCmd_Var->m_sNode_Stack );
        return (tiVar);
    };

    tgCM_UT_LF__RW__Exit_Write( &g_sCN_Command_Name_Lock.m_sLock );

    TgWARNING_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Console command name already used." );
    tgMM_Set_U08_0x00( psCmd_Var, sizeof( STg2_CN_Command_Variable ) );
    tgCM_UT_LF__ST__Push( &s_sCommand_Variable_Stack.m_sStack, &psCmd_Var->m_sNode_Stack );

    tiVar = KTgCN_VAR_ID__INVALID;
    return (tiVar);
}
