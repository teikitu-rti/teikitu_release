/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Physics - Ragdoll.c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.21 | »GUID« AEEC8393-9780-4ECA-918D-E3E11F7E2744 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
//# TgS Physics - Ragdoll.c

#include "TgS Physics - Internal.inl"


/* == Physics ==================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Macros                                                                                                                                                              */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

#define PHYSICS_FUNCTION_QUERY_RAGDOLL_BONE_DEFINITION(FCN_NAME,OBJ_NAME,OBJ_ID,ATTRIBUTE_TYPE,FIELD)                                                                               \
TgRESULT tgPH_##FCN_NAME( ATTRIBUTE_TYPE * const pVal, TgPH_##OBJ_ID##_ID_C tiID, TgRSIZE_C uiBone )                                                                                \
{                                                                                                                                                                                   \
    STg2_PH_##OBJ_NAME##_P              ps##OBJ_NAME;                                                                                                                               \
    STg2_PH_##OBJ_NAME##_Bone_P         ps##OBJ_NAME##_Bone;                                                                                                                        \
                                                                                                                                                                                    \
    ps##OBJ_NAME = tgPH_##OBJ_NAME##_Get_##OBJ_NAME##_From_ID( tiID );                                                                                                              \
                                                                                                                                                                                    \
    if ((nullptr == pVal) || (nullptr == ps##OBJ_NAME) || (uiBone >= KTgPH_MAX_BONES))                                                                                              \
    {                                                                                                                                                                               \
        TgPARAM_CHECK( nullptr != pVal );                                                                                                                                           \
        return (KTgE_FAIL);                                                                                                                                                         \
    };                                                                                                                                                                              \
                                                                                                                                                                                    \
    ps##OBJ_NAME##_Bone = ps##OBJ_NAME->m_asBone[uiBone];                                                                                                                           \
                                                                                                                                                                                    \
    if (nullptr == ps##OBJ_NAME##_Bone)                                                                                                                                             \
    {                                                                                                                                                                               \
        return (KTgE_FAIL);                                                                                                                                                         \
    };                                                                                                                                                                              \
                                                                                                                                                                                    \
    tgMM_Copy( pVal, sizeof( ATTRIBUTE_TYPE ), &ps##OBJ_NAME##_Bone->FIELD, sizeof( ps##OBJ_NAME##_Bone->FIELD ) );                                                                 \
                                                                                                                                                                                    \
    return (KTgS_OK);                                                                                                                                                               \
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Generic, Internal and File Local Command Functions                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgPH_Ragdoll_Init_Do_Command --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Ragdoll_Init_Do_Command( TgVOID_CPC pCommand_Buffer, TgRSIZE_C nbyCommand_Buffer )
{
    typedef struct {
        TgPH_RAGDOLL_ID tiID;
    } STg2_FCN_Command;
    union { STg2_FCN_Command const * const pCommand; TgVOID_CPC pCommand_Buffer; } const uCMD = { .pCommand_Buffer = pCommand_Buffer };

    STg2_PH_Ragdoll_P                   psRL;

    TgPARAM_CHECK( sizeof( STg2_FCN_Command ) == nbyCommand_Buffer );
    TgPARAM_CHECK( uCMD.pCommand );
    (void)nbyCommand_Buffer;

    /* Acquire the form, assuming the identifier is still valid. */
    psRL = tgPH_Ragdoll_Get_Ragdoll_From_ID( uCMD.pCommand->tiID );

    if (nullptr == psRL)
    {
        TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Stale Ragdoll ID submitted for init." );
        return;
    };

    TgPARAM_CHECK(KTgID__INVALID_VALUE != psRL->m_tiRagdoll.m_uiKI)

    /* Initialize to default values. */

    psRL->m_uiUsed_Index = TgSTD_ATOMIC(fetch_add_explicit)( g_axnuiPH_Ragdoll_Total__Used + psRL->m_tiRagdoll.m_uiWorld, 1, TgSTD_MEMORY_ORDER(relaxed) );
}


/* ---- tgPH_Ragdoll_Reset_Do_Command -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Ragdoll_Reset_Do_Command( TgVOID_CPC pCommand_Buffer, TgRSIZE_C nbyCommand_Buffer )
{
    typedef struct {
        TgPH_RAGDOLL_ID tiID;
    } STg2_FCN_Command;
    union { STg2_FCN_Command const * const pCommand; TgVOID_CPC pCommand_Buffer; } const uCMD = { .pCommand_Buffer = pCommand_Buffer };

    STg2_PH_Ragdoll_P                   psRL;

    TgPARAM_CHECK( sizeof( STg2_FCN_Command ) == nbyCommand_Buffer );
    TgPARAM_CHECK( uCMD.pCommand );
    (void)nbyCommand_Buffer;

    /* Acquire the form, assuming the identifier is still valid. */
    psRL = tgPH_Ragdoll_Get_Ragdoll_From_ID( uCMD.pCommand->tiID );

    if (nullptr == psRL)
    {
        TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Stale Ragdoll ID submitted for reset." );
        return;
    };

    TgPARAM_CHECK(KTgID__INVALID_VALUE != psRL->m_tiRagdoll.m_uiKI)

    /* Reset the data to zero or its equivalents and return it to the free stack. */

    TgSTD_ATOMIC(fetch_sub_explicit)( g_axnuiPH_Ragdoll_Total__Used + psRL->m_tiRagdoll.m_uiWorld, 1, TgSTD_MEMORY_ORDER(relaxed) );

    tgMM_Set_U08_0x00( psRL, sizeof(STg2_PH_Ragdoll) );
    tgCM_UT_LF__ST__Push( &g_asPH_Ragdoll_Free_Stack[uCMD.pCommand->tiID.m_uiWorld].m_sStack, &psRL->m_sNode_Stack );
    TgSTD_ATOMIC(fetch_sub_explicit)( g_axnuiPH_Ragdoll + uCMD.pCommand->tiID.m_uiWorld, 1, TgSTD_MEMORY_ORDER(relaxed) );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Macro Functions                                                                                                                                                         */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

PHYSICS_FUNCTION_ACCESSOR_DEFINITION__SET_DEFER__ASSIGN(Ragdoll,RAGDOLL,Context,TgUINT_PTR,m_uiContext)
PHYSICS_FUNCTION_QUERY_DEFINITION__ASSIGN(Ragdoll,RAGDOLL,Number_Of_Bones,TgRSIZE,m_nuiBone)

PHYSICS_FUNCTION_QUERY_RAGDOLL_BONE_DEFINITION(Ragdoll_Query_Bone_Position_R,Ragdoll,RAGDOLL,TgVEC_F32_04_1,m_vPos_O2R)
PHYSICS_FUNCTION_QUERY_RAGDOLL_BONE_DEFINITION(Ragdoll_Query_Bone_Final_Transform_R,Ragdoll,RAGDOLL,TgVEC_F32_04_3,m_mLocal_O2R)
PHYSICS_FUNCTION_QUERY_RAGDOLL_BONE_DEFINITION(Ragdoll_Query_Bone_Skeleton_Parent_Index,Ragdoll,RAGDOLL,TgUINT_E32,m_idxParent)
PHYSICS_FUNCTION_QUERY_RAGDOLL_BONE_DEFINITION(Ragdoll_Query_Bone_Skeleton_Index,Ragdoll,RAGDOLL,TgUINT_E32,m_idxBone)
PHYSICS_FUNCTION_QUERY_RAGDOLL_BONE_DEFINITION(Ragdoll_Query_Bone_Form_ID,Ragdoll,RAGDOLL,TgPH_FORM_ID,m_tiFM)
PHYSICS_FUNCTION_QUERY_RAGDOLL_BONE_DEFINITION(Ragdoll_Query_Bone_Body_ID,Ragdoll,RAGDOLL,TgPH_BODY_ID,m_tiBY)
PHYSICS_FUNCTION_QUERY_RAGDOLL_BONE_DEFINITION(Ragdoll_Query_Bone_Constraint_ID,Ragdoll,RAGDOLL,TgPH_CONSTRAINT_ID,m_tiCT)
PHYSICS_FUNCTION_QUERY_RAGDOLL_BONE_DEFINITION(Ragdoll_Query_Bone_Motor_ID,Ragdoll,RAGDOLL,TgPH_MOTOR_ID,m_tiMR)




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Generic Object Memory Management                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgPH_Module_Ragdoll_Init_Internal ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Module_Ragdoll_Init_Internal( TgVOID )
{
#if defined(TgBUILD_FEATURE__CLIENT)
    g_anuiPH_Ragdoll_Increase_Commit[ETgPH_WORLD__CLIENT_FX] = 10;
    g_anuiPH_Ragdoll_Total_Commit[ETgPH_WORLD__CLIENT_FX] = 0;
    g_anuiPH_Ragdoll_Total_Reserve[ETgPH_WORLD__CLIENT_FX] = 10000;

    g_anuiPH_Ragdoll_Increase_Commit[ETgPH_WORLD__CLIENT_UI] = 10;
    g_anuiPH_Ragdoll_Total_Commit[ETgPH_WORLD__CLIENT_UI] = 0;
    g_anuiPH_Ragdoll_Total_Reserve[ETgPH_WORLD__CLIENT_UI] = 10000;
/*# defined(TgBUILD_FEATURE__CLIENT) */
#endif

#if defined(TgBUILD_FEATURE__SERVER)
    g_anuiPH_Ragdoll_Increase_Commit[ETgPH_WORLD__SERVER_DEFAULT] = 10;
    g_anuiPH_Ragdoll_Total_Commit[ETgPH_WORLD__SERVER_DEFAULT] = 0;
    g_anuiPH_Ragdoll_Total_Reserve[ETgPH_WORLD__SERVER_DEFAULT] = 100000;
/*# defined(TgBUILD_FEATURE__SERVER) */
#endif
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Debug Functions                                                                                                                                                       */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
#if defined(TgS_DEBUG__PHYSICS) && TgS_DEBUG__PHYSICS

/* ---- tgPH_Ragdoll_Validate ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Ragdoll_Validate( STg2_Output_PC psOUT, TgPH_RAGDOLL_ID_C tiWorld )
{
    (void)psOUT;
    (void)tiWorld;

}

/*# defined(TgS_DEBUG__PHYSICS) && TgS_DEBUG__PHYSICS */
#endif


