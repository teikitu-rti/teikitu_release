/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Physics - Internal - Macro.h
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.21 | »GUID« AEEC8393-9780-4ECA-918D-E3E11F7E2744 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_PHYSICS_INTERNAL_MACRO_H)
#if !defined (ENABLE_RELOAD_GUARD)

/* == Physics ==================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Macros Code Helpers                                                                                                                                                            */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

#define PHYSICS_FUNCTION_QUERY_DEFINITION(FCN_NAME,OBJ_NAME,OBJ_ID,ATTRIBUTE,ATTRIBUTE_TYPE,...)                                                                                    \
TgRESULT tgPH_##FCN_NAME( ATTRIBUTE_TYPE * const pVal, TgPH_##OBJ_ID##_ID_C tiID )                                                                                                  \
{                                                                                                                                                                                   \
    STg2_PH_##OBJ_NAME##_P              ps##OBJ_NAME;                                                                                                                               \
                                                                                                                                                                                    \
    ps##OBJ_NAME = tgPH_##OBJ_NAME##_Get_##OBJ_NAME##_From_ID( tiID );                                                                                                              \
                                                                                                                                                                                    \
    if ((nullptr == pVal) || (nullptr == ps##OBJ_NAME))                                                                                                                             \
    {                                                                                                                                                                               \
        TgPARAM_CHECK( nullptr != pVal );                                                                                                                                           \
        return (KTgE_FAIL);                                                                                                                                                         \
    };                                                                                                                                                                              \
                                                                                                                                                                                    \
    __VA_ARGS__                                                                                                                                                                     \
                                                                                                                                                                                    \
    return (KTgS_OK);                                                                                                                                                               \
}

#define PHYSICS_FUNCTION_SET_DEFINITION(FCN_NAME,OBJ_NAME,OBJ_ID,ATTRIBUTE,ATTRIBUTE_TYPE,...)                                                                                      \
TgRESULT tgPH_##FCN_NAME( TgPH_##OBJ_ID##_ID_C tiID, ATTRIBUTE_TYPE const Val )                                                                                                     \
{                                                                                                                                                                                   \
    STg2_PH_##OBJ_NAME##_P              ps##OBJ_NAME;                                                                                                                               \
                                                                                                                                                                                    \
    ps##OBJ_NAME = tgPH_##OBJ_NAME##_Get_##OBJ_NAME##_From_ID( tiID );                                                                                                              \
                                                                                                                                                                                    \
    if (nullptr == ps##OBJ_NAME)                                                                                                                                                    \
    {                                                                                                                                                                               \
        return (KTgE_FAIL);                                                                                                                                                         \
    };                                                                                                                                                                              \
                                                                                                                                                                                    \
    __VA_ARGS__                                                                                                                                                                     \
                                                                                                                                                                                    \
    return (KTgS_OK);                                                                                                                                                               \
}

#define PHYSICS_FUNCTION_DEFINITION__COMMAND(FCN_NAME,OBJ_NAME,OBJ_ID,ATTRIBUTE_TYPE,...)                                                                                           \
TgWARN_DISABLE_PUSH(4820,padded)                                                                                                                                                    \
static TgVOID tgPH_##FCN_NAME##_Do_Command( TgVOID_CPC TgANALYSIS_NO_NULL pCommand_Buffer, TgRSIZE_C nbyCommand_Buffer )                                                            \
{                                                                                                                                                                                   \
    typedef struct {                                                                                                                                                                \
        TgPH_##OBJ_ID##_ID TgALIGN(16) tiID;                                                                                                                                        \
        ATTRIBUTE_TYPE Val;                                                                                                                                                         \
    } STg2_FCN_Command;                                                                                                                                                             \
    union { STg2_FCN_Command const * const pCommand; TgVOID_CPC pCommand_Buffer; } const uCMD = { .pCommand_Buffer = pCommand_Buffer };                                             \
    STg2_PH_##OBJ_NAME##_P              ps##OBJ_NAME;                                                                                                                               \
                                                                                                                                                                                    \
    TgPARAM_CHECK(sizeof(STg2_FCN_Command) == nbyCommand_Buffer)                                                                                                                    \
    (void)nbyCommand_Buffer;                                                                                                                                                        \
                                                                                                                                                                                    \
    if (nullptr == uCMD.pCommand)                                                                                                                                                   \
    {                                                                                                                                                                               \
        return;                                                                                                                                                                     \
    };                                                                                                                                                                              \
                                                                                                                                                                                    \
    ps##OBJ_NAME = tgPH_##OBJ_NAME##_Get_##OBJ_NAME##_From_ID( uCMD.pCommand->tiID );                                                                                               \
                                                                                                                                                                                    \
    if (nullptr == ps##OBJ_NAME)                                                                                                                                                    \
    {                                                                                                                                                                               \
        return;                                                                                                                                                                     \
    };                                                                                                                                                                              \
                                                                                                                                                                                    \
    __VA_ARGS__                                                                                                                                                                     \
}                                                                                                                                                                                   \
TgWARN_DISABLE_POP()

#define PHYSICS_FUNCTION_DEFINITION__DEFER_COMMAND_ASSIGN(FCN_NAME,OBJ_NAME,OBJ_ID,ATTRIBUTE_TYPE)                                                                                  \
TgWARN_DISABLE_PUSH(4820,padded)                                                                                                                                                    \
TgRESULT tgPH_##FCN_NAME( TgPH_##OBJ_ID##_ID_C tiID, ATTRIBUTE_TYPE const Val )                                                                                                     \
{                                                                                                                                                                                   \
    struct {                                                                                                                                                                        \
        TgPH_##OBJ_ID##_ID_C tiID;                                                                                                                                                  \
        ATTRIBUTE_TYPE Val;                                                                                                                                                         \
    } sCommand = { tiID, Val };                                                                                                                                                     \
                                                                                                                                                                                    \
    return tgCM_UT__CMD_BUF__Queue_Command( g_asPH_Command_To_World + tiID.m_uiWorld, tgPH_##FCN_NAME##_Do_Command, sizeof(sCommand), &sCommand );                                  \
}                                                                                                                                                                                   \
TgWARN_DISABLE_POP()

#define PHYSICS_FUNCTION_DEFINITION__DEFER_COMMAND_COPY(FCN_NAME,OBJ_NAME,OBJ_ID,ATTRIBUTE_TYPE)                                                                                    \
TgWARN_DISABLE_PUSH(4820,padded)                                                                                                                                                    \
TgRESULT tgPH_##FCN_NAME( TgPH_##OBJ_ID##_ID_C tiID, ATTRIBUTE_TYPE const * pVal )                                                                                                  \
{                                                                                                                                                                                   \
    struct {                                                                                                                                                                        \
        TgPH_##OBJ_ID##_ID TgALIGN(16) tiID;                                                                                                                                        \
        ATTRIBUTE_TYPE Val;                                                                                                                                                         \
    } sCommand;                                                                                                                                                                     \
                                                                                                                                                                                    \
    sCommand.tiID.m_uiKI = tiID.m_uiKI;                                                                                                                                             \
    tgMM_Copy( (TgVOID_P)&sCommand.Val, sizeof( ATTRIBUTE_TYPE ), (TgVOID_CP)pVal, sizeof( ATTRIBUTE_TYPE ) );                                                                      \
                                                                                                                                                                                    \
    return tgCM_UT__CMD_BUF__Queue_Command( g_asPH_Command_To_World + tiID.m_uiWorld, tgPH_##FCN_NAME##_Do_Command, sizeof(sCommand), &sCommand );                                  \
}                                                                                                                                                                                   \
TgWARN_DISABLE_POP()


/* Definition for non-deferred query and set. */

#define PHYSICS_FUNCTION_QUERY_DEFINITION__ASSIGN(OBJ_NAME,OBJ_ID,ATTRIBUTE,ATTRIBUTE_TYPE,FIELD)                                                                                   \
    PHYSICS_FUNCTION_QUERY_DEFINITION(OBJ_NAME##_Query_##ATTRIBUTE,OBJ_NAME,OBJ_ID,ATTRIBUTE,ATTRIBUTE_TYPE,*pVal = ps##OBJ_NAME->FIELD;)

#define PHYSICS_FUNCTION_QUERY_DEFINITION__COPY(OBJ_NAME,OBJ_ID,ATTRIBUTE,ATTRIBUTE_TYPE,FIELD)                                                                                     \
    PHYSICS_FUNCTION_QUERY_DEFINITION(OBJ_NAME##_Query_##ATTRIBUTE,OBJ_NAME,OBJ_ID,ATTRIBUTE,ATTRIBUTE_TYPE,                                                                        \
        tgMM_Copy( pVal, sizeof( ATTRIBUTE_TYPE ), &ps##OBJ_NAME->FIELD, sizeof( ps##OBJ_NAME->FIELD ) ); )

#define PHYSICS_FUNCTION_SET_DEFINITION__ASSIGN(OBJ_NAME,OBJ_ID,ATTRIBUTE,ATTRIBUTE_TYPE,FIELD)                                                                                     \
    PHYSICS_FUNCTION_SET_DEFINITION(OBJ_NAME##_Set_##ATTRIBUTE,OBJ_NAME,OBJ_ID,ATTRIBUTE,ATTRIBUTE_TYPE,ps##OBJ_NAME->FIELD = Val;)

#define PHYSICS_FUNCTION_SET_DEFINITION__COPY(OBJ_NAME,OBJ_ID,ATTRIBUTE,ATTRIBUTE_TYPE,FIELD)                                                                                       \
    PHYSICS_FUNCTION_SET_DEFINITION(OBJ_NAME##_Set_##ATTRIBUTE,OBJ_NAME,OBJ_ID,ATTRIBUTE,ATTRIBUTE_TYPE*,                                                                           \
        if (nullptr == Val)                                                                                                                                                         \
        {                                                                                                                                                                           \
            TgPARAM_CHECK( nullptr != Val );                                                                                                                                        \
            return (KTgE_FAIL);                                                                                                                                                     \
        };                                                                                                                                                                          \
        tgMM_Copy( &ps##OBJ_NAME->FIELD, sizeof( ps##OBJ_NAME->FIELD ), Val, sizeof( ATTRIBUTE_TYPE ) ); )

#define PHYSICS_FUNCTION_ACCESSOR_DEFINITION__ASSIGN(OBJ_NAME,OBJ_ID,ATTRIBUTE,ATTRIBUTE_TYPE,FIELD)                                                                                \
    PHYSICS_FUNCTION_QUERY_DEFINITION__ASSIGN(OBJ_NAME,OBJ_ID,ATTRIBUTE,ATTRIBUTE_TYPE,FIELD)                                                                                       \
    PHYSICS_FUNCTION_SET_DEFINITION__ASSIGN(OBJ_NAME,OBJ_ID,ATTRIBUTE,ATTRIBUTE_TYPE,FIELD)

#define PHYSICS_FUNCTION_ACCESSOR_DEFINITION__COPY(OBJ_NAME,OBJ_ID,ATTRIBUTE,ATTRIBUTE_TYPE,FIELD)                                                                                  \
    PHYSICS_FUNCTION_QUERY_DEFINITION__COPY(OBJ_NAME,OBJ_ID,ATTRIBUTE,ATTRIBUTE_TYPE,FIELD)                                                                                         \
    PHYSICS_FUNCTION_SET_DEFINITION__COPY(OBJ_NAME,OBJ_ID,ATTRIBUTE,ATTRIBUTE_TYPE,FIELD)


/* Definition for non-deferred query and deferred set. */

#define PHYSICS_FUNCTION_SET_DEFER_DEFINITION__ASSIGN(OBJ_NAME,OBJ_ID,ATTRIBUTE,ATTRIBUTE_TYPE,FIELD)                                                                               \
    PHYSICS_FUNCTION_DEFINITION__COMMAND(OBJ_NAME##_Set_##ATTRIBUTE,OBJ_NAME,OBJ_ID,ATTRIBUTE_TYPE, ps##OBJ_NAME->FIELD = uCMD.pCommand->Val;)                                      \
    PHYSICS_FUNCTION_DEFINITION__DEFER_COMMAND_ASSIGN(OBJ_NAME##_Set_##ATTRIBUTE,OBJ_NAME,OBJ_ID,ATTRIBUTE_TYPE)

#define PHYSICS_FUNCTION_SET_DEFER_DEFINITION__COPY(OBJ_NAME,OBJ_ID,ATTRIBUTE,ATTRIBUTE_TYPE,FIELD)                                                                                 \
    PHYSICS_FUNCTION_DEFINITION__COMMAND(OBJ_NAME##_Set_##ATTRIBUTE,OBJ_NAME,OBJ_ID,ATTRIBUTE_TYPE,                                                                                 \
        tgMM_Copy( (TgVOID_P)&ps##OBJ_NAME->FIELD, sizeof( ps##OBJ_NAME->FIELD ), (TgVOID_CP)&uCMD.pCommand->Val, sizeof( ATTRIBUTE_TYPE ) );)                                      \
    PHYSICS_FUNCTION_DEFINITION__DEFER_COMMAND_COPY(OBJ_NAME##_Set_##ATTRIBUTE,OBJ_NAME,OBJ_ID,ATTRIBUTE_TYPE)

#define PHYSICS_FUNCTION_ACCESSOR_DEFINITION__SET_DEFER__ASSIGN(OBJ_NAME,OBJ_ID,ATTRIBUTE,ATTRIBUTE_TYPE,FIELD)                                                                     \
    PHYSICS_FUNCTION_QUERY_DEFINITION__ASSIGN(OBJ_NAME,OBJ_ID,ATTRIBUTE,ATTRIBUTE_TYPE,FIELD)                                                                                       \
    PHYSICS_FUNCTION_SET_DEFER_DEFINITION__ASSIGN(OBJ_NAME,OBJ_ID,ATTRIBUTE,ATTRIBUTE_TYPE,FIELD)

#define PHYSICS_FUNCTION_ACCESSOR_DEFINITION__SET_DEFER__COPY(OBJ_NAME,OBJ_ID,ATTRIBUTE,ATTRIBUTE_TYPE,FIELD)                                                                       \
    PHYSICS_FUNCTION_QUERY_DEFINITION__COPY(OBJ_NAME,OBJ_ID,ATTRIBUTE,ATTRIBUTE_TYPE,FIELD)                                                                                         \
    PHYSICS_FUNCTION_SET_DEFER_DEFINITION__COPY(OBJ_NAME,OBJ_ID,ATTRIBUTE,ATTRIBUTE_TYPE,FIELD)


/* Definition for a deferred custom set. */

#define PHYSICS_FUNCTION_DEFER_DEFINITION__ASSIGN(FCN_NAME,OBJ_NAME,OBJ_ID,ATTRIBUTE_TYPE,...)                                                                                      \
    PHYSICS_FUNCTION_DEFINITION__COMMAND(FCN_NAME,OBJ_NAME,OBJ_ID,ATTRIBUTE_TYPE, __VA_ARGS__)                                                                                      \
    PHYSICS_FUNCTION_DEFINITION__DEFER_COMMAND_ASSIGN(FCN_NAME,OBJ_NAME,OBJ_ID,ATTRIBUTE_TYPE)

#define PHYSICS_FUNCTION_DEFER_DEFINITION__COPY(FCN_NAME,OBJ_NAME,OBJ_ID,ATTRIBUTE_TYPE,...)                                                                                        \
    PHYSICS_FUNCTION_DEFINITION__COMMAND(FCN_NAME,OBJ_NAME,OBJ_ID,ATTRIBUTE_TYPE, __VA_ARGS__)                                                                                      \
    PHYSICS_FUNCTION_DEFINITION__DEFER_COMMAND_COPY(FCN_NAME,OBJ_NAME,OBJ_ID,ATTRIBUTE_TYPE)




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Generic Macros                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

#define __PARENT_FILE__ "TgS Physics - Internal - Macro.h"
#define ENABLE_RELOAD_GUARD
#include "TgS PHYSICS/TgS Physics - Object [INC].h"
#undef ENABLE_RELOAD_GUARD
#undef __PARENT_FILE__

#define TGS_PHYSICS_INTERNAL_MACRO_H

/*# defined (ENABLE_RELOAD_GUARD) */
#else

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Generic Macros                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */









/*# defined (ENABLE_RELOAD_GUARD) */
#endif

/* =============================================================================================================================================================================== */
/*# defined (TGS_PHYSICS_INTERNAL_MACROS_H) */
#endif
